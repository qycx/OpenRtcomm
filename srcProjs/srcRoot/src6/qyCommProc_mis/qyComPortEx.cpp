
#include	"stdafx.h"
#include	<vfw.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyCommProc.h"
#include	"qnmPcComm.h"
#include	"qnmCommProc.h"
#include	"qyq2.h"

#include	"qmOpenCommon.h"
#include	"qyMsgFunc.h"


#include	"qnmCommProc_mis.h"

//
#include	"qyComPortEx.h"
//
#include	"gpsCommProc.h"

#include <assert.h>

 



//
// Constructor
//
CComPortEx::CComPortEx()
{
	m_hComm = NULL;

	// initialize overlapped structure members to zero
	m_ov.Offset = 0;
	m_ov.OffsetHigh = 0;

	// create events
	m_ov.hEvent = NULL;
	m_hWriteEvent = NULL;
	m_hShutdownEvent = NULL;

	
#if 10  // 2012/04/16
	m_bCsCommunicationSyncInitialized  =  FALSE;	//  2008/01/04
#endif
	m_bThreadAlive = FALSE;
	m_bBlockRead  =  FALSE;

	//
	//  m_pOwner  =  NULL;

	//
	m_var.m_szWriteBuffer  =  NULL;

#if 10  // 2012/04/16
	memset(  &m_var,  0,  sizeof(  m_var  )  );
#endif

#if  0
	//  m_var.endChar  =  13;	//  2008/01/04
	m_var.endChar  =  '\n';
#endif

	
}

//
// Delete dynamic memory
//
 CComPortEx::~CComPortEx()
{
	do  {
		SetEvent(m_hShutdownEvent);
	} while (m_bThreadAlive);
	//  2012/08/15
	MACRO_qyNullThread(  m_var.hThread  );

	delete [] m_var.m_szWriteBuffer;
	delete [] m_var.m_szReadBuf;

	//  2012/04/20
	MACRO_safeFree(  m_var.pMsgBuf  );

#if 10  // 2012/04/16
	//  2008/01/04, 应该关掉句柄
	if  (  isHandleValid(  this->m_hComm  )  )  {
		CloseHandle(  this->m_hComm  );  this->m_hComm  =  NULL;
	}


	if  (  m_ov.hEvent  !=  NULL  )  {		
		CloseHandle(  m_ov.hEvent  );  m_ov.hEvent  =  NULL;
	}
	if  (  m_hWriteEvent  !=  NULL  )  {		
		CloseHandle(  m_hWriteEvent  );  m_hWriteEvent  =  NULL;
	}
	if  (  m_hShutdownEvent  !=  NULL  )  {
		CloseHandle(  m_hShutdownEvent  );  m_hShutdownEvent  =  NULL;
	}

	//  2008/01/08
	//  if  (  m_var.bToBeDelMsgIndexQInited  )  exitGenericQ(  &m_var.toBeDelMsgIndexQ  );

#if  0
	delete [] m_var.szWriteBuf;
	delete [] m_var.szReadBuf;
#endif

	if  (  this->m_bCsCommunicationSyncInitialized  )  {
		DeleteCriticalSection(  &m_csCommunicationSync  );  this->m_bCsCommunicationSyncInitialized  =  FALSE;
	}

	//  TRACE(  _T(  "Thread ended, portNo is %d\n"),  this->m_var.nPortNo  );
#endif


	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "free %s"  ),  m_var.szPort  );

}


BOOL CComPortEx::bInitPort(  HWND				hPortOwner,		// the owner (CWnd) of the port (receives message)
						   UINT					portNo,				// portnumber (1..4)
						   UINT					baud,				// baudrate
						   char					parity,				// parity 
						   UINT					databits,			// databits 
						   UINT					stopbits,			// stopbits 
						   DWORD				dwCommEvents,		// EV_RXCHAR, EV_CTS etc
						   UINT					nWriteBufSize, 		// size to the writebuffer
						   int					iComPortType,		//  2012/08/04
						   int					iUsrData  )
{
	BOOL			bRet						=	FALSE;
	BOOL			bCriticalSectionEntered		=	FALSE;
	//	
	BOOL			bResult						=	FALSE;
	TCHAR			szBaud[50]					=	_T(  ""  );
	TCHAR			tBuf[128]					=	_T(  ""  );

#if  0
	assert(  portNo  >  0  &&  portNo  <  256  );
	assert(  IsWindow(  hPortOwner  )  );
#endif

	if  (  !portNo  ||  portNo  >  256  )  return  FALSE;
	if  (  !IsWindow(  hPortOwner  )  )  return  FALSE;


	//  if  ther thread is alive :Kill
	if  (  m_bThreadAlive  )
	{
		do
		{
			SetEvent(  m_hShutdownEvent  );
		}  while(  m_bThreadAlive  );
		//  TRACE(  "Thread ended\n"  );
		traceLog((TCHAR*)  _T(  "Thread ended\n"  )  );
	}
	//  2012/08/15
	MACRO_qyNullThread(  m_var.hThread  );

	//  create events
	if  (  m_ov.hEvent  !=  NULL  )  {
		ResetEvent(  m_ov.hEvent  );  CloseHandle(  m_ov.hEvent  );  m_ov.hEvent  =  NULL;
	}
	m_ov.hEvent  =  CreateEvent(  NULL,  TRUE,  FALSE,  NULL  );

	if  (  m_hWriteEvent  !=  NULL  )  {
		ResetEvent(  m_hWriteEvent  );  CloseHandle(  m_hWriteEvent  );  m_hWriteEvent  =  NULL;
	}
	m_hWriteEvent  =  CreateEvent(  NULL,  TRUE,  FALSE,  NULL  );

	if  (  m_hShutdownEvent  !=  NULL  )  {
		ResetEvent(  m_hShutdownEvent  );  CloseHandle(  m_hShutdownEvent  );  m_hShutdownEvent  =  NULL;
	}
	m_hShutdownEvent  =  CreateEvent(  NULL,  TRUE,  FALSE,  NULL  );

	//  initialize the event objects
	m_hEventArray[0]  =  m_hShutdownEvent;		//  highest priority
	m_hEventArray[1]  =  m_ov.hEvent;
	m_hEventArray[2]  =  m_hWriteEvent;

	// initialize critical section
	if  (  !this->m_bCsCommunicationSyncInitialized  )  {
		InitializeCriticalSection(  &m_csCommunicationSync  );
		this->m_bCsCommunicationSyncInitialized  =  TRUE;
	}

	// set buffersize for writing and save the owner
	m_var.hWndOwner  =  hPortOwner;

	if  (  m_var.m_szWriteBuffer  !=  NULL  )  {
		delete  []  m_var.m_szWriteBuffer;  m_var.m_szWriteBuffer  =  NULL;
	}
	if  (  m_var.m_szReadBuf  )  {
		delete  []  m_var.m_szReadBuf;  m_var.m_szReadBuf  =  NULL;
	}

	m_var.m_szWriteBuffer  =  new BYTE[nWriteBufSize];
	if  (  !m_var.m_szWriteBuffer  )  goto  errLabel;
	m_var.m_nWriteBufferSize  =  nWriteBufSize;

	m_var.m_nReadBufSize  =  512;
	m_var.m_szReadBuf  =  new  BYTE[m_var.m_nReadBufSize];
	if  (  !m_var.m_szReadBuf  )  goto  errLabel;

	//  2012/04/20
	MACRO_safeFree(  m_var.pMsgBuf  );
	m_var.pMsgBuf  =  mymalloc(  sizeof(  MIS_MSGU  )  );
	if  (  !m_var.pMsgBuf  )  goto  errLabel;

	//
	m_nPortNo  =  portNo;

	m_dwCommEvents  =  dwCommEvents;

	//  2012/04/20
	m_var.iComPortType  =  iComPortType;
	m_var.iUsrData  =  iUsrData;


	//  now it critical!
	EnterCriticalSection(  &m_csCommunicationSync  );
	bCriticalSectionEntered  =  TRUE;


	//  if  the port is already opened: close it
	if  (  isHandleValid(  m_hComm  )  )
	{
		CloseHandle(  m_hComm  );  m_hComm  =  NULL;
	}

	//  prepare port strings
	_sntprintf(  m_var.szPort,  mycountof(  m_var.szPort  ),  _T(  "\\\\.\\COM%d"  ), portNo  );
	_sntprintf(  szBaud,  mycountof(  szBaud  ),  _T(  "baud=%d parity=%c data=%d stop=%d"  ), baud, parity, databits, stopbits);


	//  get a handle to the port
	m_hComm  =  CreateFile(  m_var.szPort,
							 GENERIC_READ | GENERIC_WRITE,
							 0,
							 NULL,
							 OPEN_EXISTING,
							 FILE_FLAG_OVERLAPPED,
							 0  );

	if  (  m_hComm  ==  INVALID_HANDLE_VALUE  )  {
		// port not found
		goto  errLabel;	
	}

	// set the timeout values
	m_CommTimeouts.ReadIntervalTimeout  =  1000;
	m_CommTimeouts.ReadTotalTimeoutMultiplier  =  1000;
	m_CommTimeouts.ReadTotalTimeoutConstant  =  1000;
	m_CommTimeouts.WriteTotalTimeoutMultiplier  =  1000;
	m_CommTimeouts.WriteTotalTimeoutConstant  =  1000;

#if  0
	//  configure
	if  (  SetCommTimeouts(  m_hComm,  &m_CommTimeouts  )  )
	{
		if  (  SetCommMask(  m_hComm,  dwCommEvents  )  )
		{
			if  (  GetCommState(  m_hComm,  &m_dcb  )  )
			{
				m_dcb.fRtsControl  =  RTS_CONTROL_ENABLE;
				if  (  BuildCommDCB(  (  LPCWSTR  )szBaud,  &m_dcb  )  )
				{
					if  (  SetCommState(  m_hComm,  &m_dcb  )  )
						;  //  normal operation,  .. continue
					else 
						ProcessErrorMessage(  _T(  "SetCommState(  )"  )  );
				}
				else
					ProcessErrorMessage(  _T(  "BuildCommDCB(  )"  )  );
			}
			else  
				ProcessErrorMessage(  _T(  "GetCommState(  )"  )  );
		}
		else  
			ProcessErrorMessage(  _T(  "SetCommState(  )"  )  ); 
	}
	else 
		ProcessErrorMessage(  _T(  "SetCommTimeouts(  )"  )  );

	
	// flush the port
	PurgeComm(  m_hComm,  PURGE_RXCLEAR  |  PURGE_TXCLEAR  |  PURGE_RXABORT  |  PURGE_TXABORT  );

#endif

	HANDLE	m_hHandle; m_hHandle = m_hComm;
	SetCommMask(  m_hHandle,  EV_RXCHAR  );
	SetupComm(  m_hHandle,  4096,  4096  );
	PurgeComm(  m_hHandle,  PURGE_TXABORT  |  PURGE_RXABORT  |  PURGE_TXCLEAR  |  PURGE_RXCLEAR  );

	if  (  !SetCommTimeouts(  m_hHandle,  &m_CommTimeouts  )  )  {
		goto  errLabel;
	}

	{
		DCB& portDcb = m_dcb;
		if (!GetCommState(m_hHandle, &portDcb)) {
			goto  errLabel;
		}
		portDcb.DCBlength = sizeof(DCB);
		portDcb.BaudRate = baud;
		portDcb.ByteSize = databits;
		portDcb.Parity = parity;
		portDcb.StopBits = stopbits;
		if (!SetCommState(m_hHandle, &portDcb)) {
			goto  errLabel;
		}
	}



	bRet  =  TRUE;

errLabel:

	if  (  bCriticalSectionEntered  )  {
		// release critical section
		LeaveCriticalSection(  &m_csCommunicationSync  );
	}

	m_var.ucbComExists  =  bRet;	//  2008/01/03

	traceLog((TCHAR*)  _T(  "Init for communicationport %d completed. \nUse Startmonitor to communicate.\n"  ),  portNo  );
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Init com%d %s."  ),  portNo,  bRet  ?  _T(  "OK"  )  :  _T(  "failed"  )  );

	return  bRet;
}
// 
//  The CommThread Function.
//
UINT CComPortEx::CommThread(LPVOID pParam)
{
	// Cast the void pointer passed to the thread back to
	// a pointer of CComPortEx class
	CComPortEx *port = (CComPortEx*)pParam;
	
	// Set the status variable in the dialog class to
	// TRUE to indicate the thread is running.
	port->m_bThreadAlive = TRUE;	
		
	// Misc. variables
	DWORD			BytesTransfered			=	0; 
	DWORD			Event					=	0;
	DWORD			CommEvent				=	0;
	DWORD			dwError					=	0;
	COMSTAT			comstat;
	BOOL			bResult					=	TRUE;
	
#if 10  // 2012/04/16
	//  2008/01/11
	memset(  &comstat,  0,  sizeof(  comstat  )  );
#endif

	// Clear comm buffers at startup
	if (port->m_hComm)		// check if the port is opened
		PurgeComm(port->m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	// begin forever loop.  This loop will run as long as the thread is alive.
	for (;;) 
	{ 

		// Make a call to WaitCommEvent().  This call will return immediatly
		// because our port was created as an async port (FILE_FLAG_OVERLAPPED
		// and an m_OverlappedStructerlapped structure specified).  This call will cause the 
		// m_OverlappedStructerlapped element m_OverlappedStruct.hEvent, which is part of the m_hEventArray to 
		// be placed in a non-signeled state if there are no bytes available to be read,
		// or to a signeled state if there are bytes available.  If this event handle 
		// is set to the non-signeled state, it will be set to signeled when a 
		// character arrives at the port.

		// we do this for each port!

		bResult = WaitCommEvent(port->m_hComm, &Event, &port->m_ov);

		if (!bResult)  
		{ 
			// If WaitCommEvent() returns FALSE, process the last error to determin
			// the reason..
			switch (dwError = GetLastError()) 
			{ 
			case ERROR_IO_PENDING: 	
				{ 
					// This is a normal return value if there are no bytes
					// to read at the port.
					// Do nothing and continue
					break;
				}
			case 87:
				{
					// Under Windows NT, this value is returned for some reason.
					// I have not investigated why, but it is also a valid reply
					// Also do nothing and continue.
					break;
				}
			default:
				{
					// All other error codes indicate a serious error has
					// occured.  Process this error.
					port->ProcessErrorMessage(  (TCHAR*)_T(  "WaitCommEvent()")  );
					//
					break;
				}
			}
		}
		else
		{
			// If WaitCommEvent() returns TRUE, check to be sure there are
			// actually bytes in the buffer to read.  
			//
			// If you are reading more than one byte at a time from the buffer 
			// (which this program does not do) you will have the situation occur 
			// where the first byte to arrive will cause the WaitForMultipleObjects() 
			// function to stop waiting.  The WaitForMultipleObjects() function 
			// resets the event handle in m_OverlappedStruct.hEvent to the non-signelead state
			// as it returns.  
			//
			// If in the time between the reset of this event and the call to 
			// ReadFile() more bytes arrive, the m_OverlappedStruct.hEvent handle will be set again
			// to the signeled state. When the call to ReadFile() occurs, it will 
			// read all of the bytes from the buffer, and the program will
			// loop back around to WaitCommEvent().
			// 
			// At this point you will be in the situation where m_OverlappedStruct.hEvent is set,
			// but there are no bytes available to read.  If you proceed and call
			// ReadFile(), it will return immediatly due to the async port setup, but
			// GetOverlappedResults() will not return until the next character arrives.
			//
			// It is not desirable for the GetOverlappedResults() function to be in 
			// this state.  The thread shutdown event (event 0) and the WriteFile()
			// event (Event2) will not work if the thread is blocked by GetOverlappedResults().
			//
			// The solution to this is to check the buffer with a call to ClearCommError().
			// This call will reset the event handle, and if there are no bytes to read
			// we can loop back through WaitCommEvent() again, then proceed.
			// If there are really bytes to read, do nothing and proceed.
		
			bResult = ClearCommError(port->m_hComm, &dwError, &comstat);

			if (comstat.cbInQue == 0)
				continue;
		}	// end if bResult

		// Main wait function.  This function will normally block the thread
		// until one of nine events occur that require action.
		Event = WaitForMultipleObjects(3, port->m_hEventArray, FALSE, INFINITE);

		switch (Event)
		{
		case 0:
			{
				// Shutdown event.  This is event zero so it will be
				// the higest priority and be serviced first.

			 	port->m_bThreadAlive = FALSE;
				
				// Kill this thread.  break is not needed, but makes me feel better.
				//  AfxEndThread(100);
				goto  errLabel;
				break;
			}
		case 1:	// read event
			{
				GetCommMask(port->m_hComm, &CommEvent);
				
				#if  0	//  2012/04/17. 不能用SendMessage, 当管理窗口正在delete pPort时,如果正有SendMessage,那么就要死锁了
					if (CommEvent & EV_CTS)
						::SendMessage(port->m_pOwner->m_hWnd, WM_COMM_CTS_DETECTED, (WPARAM) 0, (LPARAM) port->m_nPortNo  );
					if (CommEvent & EV_RXFLAG)
						::SendMessage(port->m_pOwner->m_hWnd, WM_COMM_RXFLAG_DETECTED, (WPARAM) 0, (LPARAM) port->m_nPortNo  );
					if (CommEvent & EV_BREAK)
						::SendMessage(port->m_pOwner->m_hWnd, WM_COMM_BREAK_DETECTED, (WPARAM) 0, (LPARAM) port->m_nPortNo  );
					if (CommEvent & EV_ERR)
						::SendMessage(port->m_pOwner->m_hWnd, WM_COMM_ERR_DETECTED, (WPARAM) 0, (LPARAM) port->m_nPortNo  );
					if (CommEvent & EV_RING)
						::SendMessage(port->m_pOwner->m_hWnd, WM_COMM_RING_DETECTED, (WPARAM) 0, (LPARAM) port->m_nPortNo  );
				#endif


				
#if 0  // 2012/04/16
				// Receive character event from port.					
				if (CommEvent & EV_RXCHAR) ReceiveChar(port, comstat);
#endif
				if (CommEvent & EV_RXCHAR) 
					//
					if  (  !port->m_bBlockRead  )
						ReceiveChar(port, comstat);
					
				break;
			}  
		case 2: // write event
			{
				// Write character event from port
				WriteChar(port);
				break;
			}

		} // end switch

	} // close forever loop

errLabel:

	//  2012/08/15
	port->m_bThreadAlive = FALSE;

	return 0;
}

//
// start comm watching
//
BOOL CComPortEx::bStartMonitoring()
{
	BOOL	bRet	=	FALSE;
	DWORD	dwThreadDaemonId;

	if  (  !isHandleValid(  this->m_hComm  )  )  return  FALSE;
	if  (  m_var.ucbStarted  )  return  FALSE;		//  已经启动了

	//  if (!(m_Thread = AfxBeginThread(CommThread, this)))  return FALSE;
	m_var.hThread  =  CreateThread(  NULL,  0,  (  LPTHREAD_START_ROUTINE  )CommThread,  (  LPVOID  )this,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
	if  (  !m_var.hThread  )  goto  errLabel;
	m_var.dwThreadId  =  dwThreadDaemonId;	//  2007/03/29, 为了引入这个标记，以便mtCliSockThreadProc能够在pMtSock里找到存放的物理位置，故要先挂起一下，然后再恢复
	if  (  ResumeThread(  m_var.hThread  )  ==  -1  )  goto  errLabel;

	//  2012/08/15
	int  i;
	for  (  i  =  0;  i  <  100;  i  ++  )  {
		 if  (  this->m_bThreadAlive  )  break;
		 Sleep(  5  );
	}
	if  (  !this->m_bThreadAlive  )  goto  errLabel;


	//
	m_var.ucbStarted  =  TRUE;
	
	//
	traceLog((TCHAR*)  _T(  "Thread started\n")  );

	//
	bRet  =  TRUE;

errLabel:

	return bRet;	
}


//
// Suspend the comm thread
//
#if  0
BOOL CComPortEx::bStopMonitoring()
{

	TRACE(  _T(  "StopMonitoring\n")  );

	do  {
		SetEvent(m_hShutdownEvent);
	} while (m_bThreadAlive);

	//  2008/01/04, 应该关掉句柄
	if  (  isHandleValid(  this->m_hComm  )  )  {
		CloseHandle(  this->m_hComm  );  this->m_hComm  =  NULL;
	}

	//
	m_var.ucbStarted  =  FALSE;


	return TRUE;	
}
#endif


//
// If there is a error, give the right message
//
void CComPortEx::ProcessErrorMessage(TCHAR* ErrorText)
{
	//
	m_var.ucbSeriousErr = true;
	showInfo_open0(0, 0, _T("comPortEx.ProcessError"));

	//
	TCHAR *Temp = new TCHAR[200];
	if  (  !Temp  )  return;

	LPVOID lpMsgBuf  =  NULL;

	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);

#if  0
	_sntprintf(Temp, 200,  _T(  "WARNING:  %s Failed with the following error: \n%s\nPort: %d\n"  ), ErrorText, lpMsgBuf, m_var.nPortNo  ); 
	MessageBox(NULL, Temp, _T(  "Application Error"  ), MB_ICONSTOP);
#endif

	if  (  lpMsgBuf  )  LocalFree(lpMsgBuf);
	delete[] Temp;
}

//
// Write a character.
//
 void CComPortEx::WriteChar(CComPortEx* port)
{
	BOOL	bWrite		=	TRUE;
	BOOL	bResult		=	TRUE;

	BOOL	bCriticalSectionEntered	=	FALSE;

	DWORD	BytesSent	=	0;

#ifdef  __DEBUG__
		//  traceLog((TCHAR*)  _T(  "comport::WriteChar enters"  )  );
#endif

	//
	ResetEvent(  port->m_hWriteEvent  );

	//  2012/08/04
	if  (  !port->m_var.m_nToSend  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "ComPort::WriteChar, no data to be sent"  )  );
		return;
	}

	// Gain ownership of the critical section
	
	TCHAR	tBuf[256]	=	_T(  ""  );
	EnterCriticalSection(&port->m_csCommunicationSync);  bCriticalSectionEntered  =  TRUE;

	if (bWrite)
	{
		// Initailize variables
		port->m_ov.Offset = 0;
		port->m_ov.OffsetHigh = 0;

		// Clear buffer
		PurgeComm(port->m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

		bResult = WriteFile(port->m_hComm,							// Handle to COMM Port
							port->m_var.m_szWriteBuffer,					// Pointer to message buffer in calling finction
							port->m_var.m_nToSend,						// Length of message to send
							&BytesSent,								// Where to store the number of bytes sent
							&port->m_ov);							// Overlapped structure
		// deal with any error codes
		if (!bResult)  
		{
			DWORD dwError = GetLastError();
			switch (dwError)
			{
				case ERROR_IO_PENDING:
					{
						// continue to GetOverlappedResults()
						BytesSent = 0;
						bWrite = FALSE;
						break;
					}
				default:
					{
						// all other error codes
						port->ProcessErrorMessage(  (TCHAR*)_T(  "WriteFile()")  );
					}
			}
		} 
		else
		{
			LeaveCriticalSection(&port->m_csCommunicationSync);  bCriticalSectionEntered  =  FALSE;
		}
	} // end if(bWrite)
	if (!bWrite)
	{
		bWrite = TRUE;
	
		bResult = GetOverlappedResult(port->m_hComm,	// Handle to COMM port 
									  &port->m_ov,		// Overlapped structure
									  &BytesSent,		// Stores number of bytes sent
									  TRUE); 			// Wait flag

		LeaveCriticalSection(&port->m_csCommunicationSync);  bCriticalSectionEntered  =  FALSE;

		// deal with the error code 
		if (!bResult)  
		{
			port->ProcessErrorMessage(  (TCHAR*)_T(  "GetOverlappedResults() in WriteFile()")  );
		}	
	} // end if (!bWrite)

	// Verify that the data size send equals what we tried to send
	if  (  BytesSent  !=  port->m_var.m_nToSend  )  {
		traceLog((TCHAR*)  _T(  "WARNING: WriteFile(  ) error..Bytes Sent:%d; Message Length: %d\n"  ), BytesSent,  strlen(  (  char  *  )port->m_var.m_szWriteBuffer  )  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "ComPort::WriteChar failed, Byte !=  m_nToSend"  )  );
		}
	else  {  //  2012/08/04
		  port->m_var.m_nToSend  =  0;
	}

errLabel:

	if  (  bCriticalSectionEntered  )  {
		LeaveCriticalSection(&port->m_csCommunicationSync);  bCriticalSectionEntered  =  FALSE;
	}

#ifdef  __DEBUG__
		//  traceLog((TCHAR*)  _T(  "comport::WriteChar leaves"  )  );
#endif

}

//
// Character received. Inform the owner
//
 void CComPortEx::ReceiveChar(CComPortEx* port, COMSTAT comstat)
{
	BOOL				bRead			=	TRUE; 
	BOOL				bResult			=	TRUE;
	DWORD				dwError			=	0;
	DWORD				BytesRead		=	0;
	unsigned char		RXBuff			=	0;

#if  10

	//  traceLogA(  "ReceiveChar enters"  );

	for (;;) 
	{ 
		// Gain ownership of the comm port critical section.
		// This process guarantees no other part of this program 
		// is using the port object. 
		
		EnterCriticalSection(&port->m_csCommunicationSync);

		// ClearCommError() will update the COMSTAT structure and
		// clear any other errors.
		
		bResult = ClearCommError(port->m_hComm, &dwError, &comstat);

		LeaveCriticalSection(&port->m_csCommunicationSync);

		// start forever loop.  I use this type of loop because I
		// do not know at runtime how many loops this will have to
		// run. My solution is to start a forever loop and to
		// break out of it when I have processed all of the
		// data available.  Be careful with this approach and
		// be sure your loop will exit.
		// My reasons for this are not as clear in this sample 
		// as it is in my production code, but I have found this 
		// solutiion to be the most efficient way to do this.
		
		if (comstat.cbInQue == 0)
		{
			// break out when all bytes have been read
			break;
		}
						
		EnterCriticalSection(&port->m_csCommunicationSync);

		if (bRead)
		{
			bResult = ReadFile(port->m_hComm,		// Handle to COMM port 
							   &RXBuff,				// RX Buffer Pointer
							   1,					// Read one byte
							   &BytesRead,			// Stores number of bytes read
							   &port->m_ov);		// pointer to the m_ov structure
			// deal with the error code 
			if (!bResult)  
			{ 
				switch (dwError = GetLastError()) 
				{ 
					case ERROR_IO_PENDING: 	
						{ 
							// asynchronous i/o is still in progress 
							// Proceed on to GetOverlappedResults();
							bRead = FALSE;
							break;
						}
					default:
						{
							// Another error has occured.  Process this error.
							port->ProcessErrorMessage(  (TCHAR*)_T(  "ReadFile()")  );
							break;
						} 
				}
			}
			else
			{
				// ReadFile() returned complete. It is not necessary to call GetOverlappedResults()
				bRead = TRUE;
			}
		}  // close if (bRead)

		if (!bRead)
		{
			bRead = TRUE;
			bResult = GetOverlappedResult(port->m_hComm,	// Handle to COMM port 
										  &port->m_ov,		// Overlapped structure
										  &BytesRead,		// Stores number of bytes read
										  TRUE); 			// Wait flag

			// deal with the error code 
			if (!bResult)  
			{
				port->ProcessErrorMessage(  (TCHAR*)_T(  "GetOverlappedResults() in ReadFile()")  );
			}	
		}  // close if (!bRead)
				
		LeaveCriticalSection(&port->m_csCommunicationSync);

		// notify parent that a byte was received
		#if  0
			::SendMessage(port->m_pOwner->m_hWnd, CONST_wmComm_EV_RXCHAR, (WPARAM) RXBuff, (LPARAM) port->m_nPortNo);
		#endif
		//  2012/04/17
		if  (  port->m_var.nRead  >=  port->m_var.m_nReadBufSize  -  1  )  {	//  这里数据还没提交错了，清空. 
			port->m_var.nRead  =  0;
		}
		//  加到缓冲尾部
		port->m_var.m_szReadBuf[port->m_var.nRead]  =  RXBuff;
		port->m_var.nRead  ++  ;

		if  (  port->m_var.iComPortType  ==  CONST_iComPortType_gps  )  {
			//
			if  (  port->m_var.m_szReadBuf[0]  !=  '$'  )  {
				//  丢弃无效数据
				port->m_var.nRead  =  0;
			    }
			else  {
				  if  (  RXBuff  ==  0x0a  
					  &&  port->m_var.nRead  >  3  
					  &&  port->m_var.m_szReadBuf[port->m_var.nRead  -  2]  ==  0x0d				  
					  )  
				  {
					  port->m_var.m_szReadBuf[port->m_var.nRead]  =  0;
	
					  //
					  #ifdef  __DEBUG__
							  MACRO_qyAssert(  port->m_var.pf_parseGpsStr,  _T(  "pf_parseGpsStr null"  )  );
					  #endif
					  if  (  port->m_var.pf_parseGpsStr  )  {
						  port->m_var.pf_parseGpsStr(  (  void  *  )port,  (  char  *  )port->m_var.m_szReadBuf  );
					  }

					  //  处理完了,该清空了
					  port->m_var.nRead  =  0;
				  }		  
			}
		}
		else  if (port->m_var.iComPortType == CONST_iComPortType_infrared) {
				 //
			     TCHAR  tBuf[128];
				 _sntprintf(tBuf, mycountof(tBuf), _T("ComPortEx.Receive [%x]"), (int)RXBuff);
				 showInfo_open0(0, 0, tBuf);
				 //
				 ::PostMessage(port->m_var.hWndOwner, CONST_wmComm_EV_RXCHAR, (WPARAM)RXBuff, (LPARAM)port->m_nPortNo);
				 //  清空
				 port->m_var.nRead = 0;
		}

	}//end forever loop

#endif

	//  2012/08/01
	port->m_var.dwTickCnt_lastRead  =  GetTickCount(  );

	//  traceLogA(  "ReceiveChar leaves"  );

}

//
// Write a string to the port
//

 int CComPortEx::WriteToPort(  BYTE *string,  int nLength )
{


	//
	if  (  m_hComm  ==  0  )
	{
		//  ::AfxMessageBox(  _T(  "error strange"  )  );
		return  -1;
	}

	if  (  m_var.m_nWriteBufferSize  <  nLength  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "ComPort::Write failed, buf to small"  )  );
		return  -1;
	}

	if  (  m_var.m_nToSend  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "ComPort::Write failed, m_nToSend is not 0"  )  );
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "comport::WriteToPort failed, m_nToSend is not 0"  )  );
		#endif

		//  set event for write
		SetEvent(  m_hWriteEvent  );

		return  -1;
	}

	DWORD	dwTickCnt  =  GetTickCount(  );
	if  (  m_var.iComPortType  ==  CONST_iComPortType_ptz  )  {		//  这里限制了发送的速度
		int	iDiff  =  dwTickCnt  -  m_var.dwTickCnt_lastWrite;
		if  (  iDiff  <  20  )  
		{
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "ComPort::Write failed, too quickly, iDiff %dms"  ),  iDiff  );
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "comport::WriteToPort failed, too quickly, iDiff %d"  ),  iDiff  );
			#endif

			return  -1;
		}
	}


	memset(  m_var.m_szWriteBuffer,  0,  m_var.m_nWriteBufferSize  );
	memcpy(  m_var.m_szWriteBuffer,  string,  nLength  );
	m_var.m_nToSend  =  nLength;

	//  set event for write
	SetEvent(  m_hWriteEvent  );

	//  2012/08/01
	m_var.dwTickCnt_lastWrite  =  GetTickCount(  );

	return  0;
}
//
// Return the device control block
//
DCB CComPortEx::GetDCB()
{
	return m_dcb;
}

//
// Return the communication event masks
//
DWORD CComPortEx::GetCommEvents()
{
#if 0  // 2012/04/16
	return m_var.dwCommEvents;
#endif
	return m_dwCommEvents;
}

//
// Return the output buffer size
//
DWORD CComPortEx::GetWriteBufSize()
{
#if 10  // 2012/04/16
	return m_var.m_nWriteBufferSize;
#endif
	//  return m_nWriteBufferSize;
}

#if  0
BYTE* CComPortEx::ReadBlock(  CComPortEx  * port, int &readLen  )
{
	COMSTAT		comstat;
	BOOL		bRead		=  TRUE;
	BOOL		bResult		=  TRUE;
	DWORD		dwError		=  0;
	DWORD		ByteRead	=  0;
	DWORD		BytesToRead;
	BYTE	*	pRec;

	EnterCriticalSection(  &port->m_csCommunicationSync  );

	bResult  =  ClearCommError(  port->m_hComm,  &dwError,  &comstat  );

	LeaveCriticalSection(  &port->m_csCommunicationSync  );

	if  (  comstat.cbInQue  ==  0  )
	{
		//  break out when all bytes have been read
		readLen  =  0;
		return  NULL;
	}

	BytesToRead  =  comstat.cbInQue;
	pRec  =  new BYTE[BytesToRead];

	EnterCriticalSection(  &port->m_csCommunicationSync  );

	if  (  bRead  )
	{
		bResult  =  ReadFile(	port->m_hComm,
								pRec,
								BytesToRead,
								&ByteRead,
								&port->m_ov  );
		//  deal with error code
		if  (  !bResult  )
		{
			switch(  dwError  =  GetLastError( )  )
			{
			case  ERROR_IO_PENDING:
				{
					bRead  =  FALSE;
					break;
				}
			default:
				{
					port->ProcessErrorMessage(  _T(  "ReadFile( )"  )  );
					break;
				}
			}
		}
		else  
		{
			bRead  =  TRUE;
		}
	}

	if  (  !bRead  )
	{
		bRead  =  TRUE;
		bResult  =  GetOverlappedResult(	port->m_hComm,
											&port->m_ov,
											&ByteRead,
											TRUE  );

		//  deal with error code
		if  (  !bResult  )
		{
			port->ProcessErrorMessage(  _T(  "GetOverLappedResults() in ReadFile()")  );
		}
	}  //  close if(  !bRead  )

	LeaveCriticalSection(  &port->m_csCommunicationSync  );

	readLen  =  ByteRead;
	return  pRec;
}
#endif


