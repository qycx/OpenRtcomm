
#include	"stdafx.h"
#include	<vfw.h>
#include	"qyCommon.h"
#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyCommProc.h"
#include	"qnmPcComm.h"
#include	"qnmCommProc.h"
#include	"qyCommProc_open.h"
#include	"qyq2.h"
#include	"qyVDevCommProc_open.h"
#include	"qdcCommProc_open.h"
#include	"qnmCommProc_mis.h"
//
#include	"qyComPort.h"
//

#include <assert.h>

 
int  postMsg2Mgr_vDevComs(  void  *  pVDev,  unsigned  int  uiMsgType,  unsigned  int  uiCliIndex,  char  *  data,  unsigned  int  dataLen  );

//
#define		CONST_mutexName_syncComPort		_T(  "syncComPort"  )

//
// Constructor
//
CComPort::CComPort()
{
	m_hComm = NULL;

	// initialize overlapped structure members to zero
	m_ov.Offset = 0;
	m_ov.OffsetHigh = 0;

	// create events
	m_ov.hEvent = NULL;
	m_hWriteEvent = NULL;
	m_hShutdownEvent = NULL;

	m_bCsCommunicationSyncInitialized  =  FALSE;	//  2008/01/04

	m_bThreadAlive = FALSE;

	memset(  &m_var,  0,  sizeof(  m_var  )  );

	//  m_var.endChar  =  13;	//  2008/01/04
	m_var.endChar  =  '\n';

	
}

//
// Delete dynamic memory
//
 CComPort::~CComPort()
{
	do  {
		SetEvent(m_hShutdownEvent);
	} while (m_bThreadAlive);

	//  2008/01/04, 应该关掉句柄
	if  (  isHandleValid(  this->m_hComm  )  )  {
		CloseHandle(  this->m_hComm  );  this->m_hComm  =  NULL;
	}

	//  2008/01/08
	if  (  m_var.bToBeDelMsgIndexQInited  )  exitGenericQ(  &m_var.toBeDelMsgIndexQ  );

	delete [] m_var.szWriteBuf;
	delete [] m_var.szReadBuf;

	if  (  this->m_bCsCommunicationSyncInitialized  )  {
		DeleteCriticalSection(  &m_csCommunicationSync  );  this->m_bCsCommunicationSyncInitialized  =  FALSE;
	}

	TRACE(  _T(  "Thread ended, portNo is %d\n"),  this->m_var.nPortNo  );

}

//
// Initialize the port. This can be port 1 to 4.
//
BOOL CComPort::InitPort(  void				*	pVDev,
						   unsigned  int		uiComIndex,
						   HWND					hWndPortOwner,		// the owner (CWnd) of the port (receives message)
						   char				*	smscBuf,
						   UINT					portNo,				// portnumber (1..4)
						   UINT					baud,				// baudrate
						   TCHAR				parity,				// parity 
						   UINT					databits,			// databits 
						   UINT					stopbits,			// stopbits 
						   DWORD				dwCommEvents,		// EV_RXCHAR, EV_CTS etc
						   BOOL					bReadLine,
						   UINT					nWriteBufSize,		// size to the writebuffer
						   UINT					nReadBufSize  )		//  
{
	BOOL			bRet						=	FALSE;
	BOOL			bCriticalSectionEntered		=	FALSE;
	//	
	BOOL			bResult						=	FALSE;
	TCHAR			szBaud[50]					=	_T(  ""  );
	TCHAR			tBuf[128]					=	_T(  ""  );

	if  (  !portNo  ||  portNo  >  256  )  return  FALSE;
	if  (  !smscBuf  ||  !smscBuf[0]  )  return  FALSE;

	//  2008/01/14
	CQySyncObj		syncObj;
	if  (  syncObj.sync(  CONST_mutexName_syncComPort  )  <  0  )  return  FALSE;


	// if the thread is alive: Kill
	if  (  m_bThreadAlive  )  {
		do  {
			SetEvent(m_hShutdownEvent);
		}  while (m_bThreadAlive);
		TRACE(  _T(  "Thread ended\n")  );
	}

	// create events
	if  (  m_ov.hEvent  !=  NULL  )  {
		ResetEvent(  m_ov.hEvent  );  CloseHandle(  m_ov.hEvent  );  m_ov.hEvent  =  NULL;
	}
	m_ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if  (  m_hWriteEvent  !=  NULL  )  {
		ResetEvent(m_hWriteEvent);  CloseHandle(  m_hWriteEvent  );  m_hWriteEvent  =  NULL;
	}
	m_hWriteEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	
	if  (  m_hShutdownEvent  !=  NULL  )  {
		ResetEvent(m_hShutdownEvent);  CloseHandle(  m_hShutdownEvent  );  m_hShutdownEvent  =  NULL;
	}
	m_hShutdownEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	// initialize the event objects
	m_hEventArray[0] = m_hShutdownEvent;	// highest priority
	m_hEventArray[1] = m_ov.hEvent;
	m_hEventArray[2] = m_hWriteEvent;

	if  (  !this->m_bCsCommunicationSyncInitialized  )  {
		//  initialize critical section
		InitializeCriticalSection(&m_csCommunicationSync);
		this->m_bCsCommunicationSyncInitialized  =  TRUE;
	}
	
	m_var.pVDev  =  pVDev;
	m_var.uiComIndex  =  uiComIndex;
	// 
	safeStrnCpy(  smscBuf,  m_var.smscBuf,  mycountof(  m_var.smscBuf  )  );
	m_var.hWndOwner = hWndPortOwner;
	//
	if  (  m_var.bToBeDelMsgIndexQInited  )  {  //  2008/01/08
		emptyGenericQ(  &m_var.toBeDelMsgIndexQ  );
		}
	else  {
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "beDelMsgQ%d"  ),  m_var.uiComIndex  );
		  if  (  initGenericQ(  tBuf,  tBuf,  0,  1000,  malloc,  free,  &m_var.toBeDelMsgIndexQ  )  )  goto  errLabel;
		  m_var.bToBeDelMsgIndexQInited  =  TRUE;		  
	}

	if  (  m_var.szWriteBuf  )  delete  []  m_var.szWriteBuf;
	if  (  m_var.szReadBuf  )  delete  []  m_var.szReadBuf;
	//
	m_var.szWriteBuf = new char[nWriteBufSize];
	m_var.nWriteBufSize = nWriteBufSize;
	m_var.szReadBuf  =  new  char[nReadBufSize];
	m_var.nReadBufSize  =  nReadBufSize;
	if  (  !m_var.szWriteBuf  ||  !m_var.szReadBuf  )  goto  errLabel;
	//
	memset(  m_var.szWriteBuf,  0,  m_var.nWriteBufSize  );
	memset(  m_var.szReadBuf,  0,  m_var.nReadBufSize  );

	m_var.nPortNo = portNo;
	m_var.baud  =  baud;

	m_var.dwCommEvents = dwCommEvents;
	m_var.bReadLine  =  bReadLine;

	// now it critical!
	EnterCriticalSection(&m_csCommunicationSync);
	bCriticalSectionEntered  =  TRUE;

	// if the port is already opened: close it
	if  (  isHandleValid(  m_hComm  )  )  {
		CloseHandle(m_hComm);  m_hComm = NULL;
	}

	// prepare port strings
	_sntprintf(  m_var.szPort,  mycountof(  m_var.szPort  ),  _T(  "\\\\.\\COM%d"  ), portNo  );
	_sntprintf(  szBaud,  mycountof(  szBaud  ),  _T(  "baud=%d parity=%c data=%d stop=%d"  ), baud, parity, databits, stopbits);

	// get a handle to the port
	m_hComm = CreateFile(m_var.szPort,						// communication port string (COMX)
					     GENERIC_READ | GENERIC_WRITE,	// read/write types
					     0,								// comm devices must be opened with exclusive access
					     NULL,							// no security attributes
					     OPEN_EXISTING,					// comm devices must use OPEN_EXISTING
					     FILE_FLAG_OVERLAPPED,			// Async I/O
					     0);							// template must be 0 for comm devices

	if (m_hComm == INVALID_HANDLE_VALUE)  {
		// port not found
		goto  errLabel;
	}

	// set the timeout values
	m_CommTimeouts.ReadIntervalTimeout = 1000;
	m_CommTimeouts.ReadTotalTimeoutMultiplier = 1000;
	m_CommTimeouts.ReadTotalTimeoutConstant = 1000;
	m_CommTimeouts.WriteTotalTimeoutMultiplier = 1000;
	m_CommTimeouts.WriteTotalTimeoutConstant = 1000;

	// configure
	if (SetCommTimeouts(m_hComm, &m_CommTimeouts))
	{						   
		if (SetCommMask(m_hComm, dwCommEvents))
		{
			if (GetCommState(m_hComm, &m_dcb))
			{
				m_dcb.fRtsControl = RTS_CONTROL_ENABLE;		// set RTS bit high!
				if (BuildCommDCB(szBaud, &m_dcb))
				{
					if (SetCommState(m_hComm, &m_dcb))
						; // normal operation... continue
					else
						ProcessErrorMessage(  _T(  "SetCommState()")  );
				}
				else
					ProcessErrorMessage(  _T(  "BuildCommDCB()")  );
			}
			else
				ProcessErrorMessage(  _T(  "GetCommState()")  );
		}
		else
			ProcessErrorMessage(  _T(  "SetCommMask()")  );
	}
	else
		ProcessErrorMessage(  _T(  "SetCommTimeouts()")  );

	// flush the port
	PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	bRet  =  TRUE;

errLabel:

	if  (  bCriticalSectionEntered  )  {
		// release critical section
		LeaveCriticalSection(&m_csCommunicationSync);
	}

	m_var.ucbComExists  =  bRet;	//  2008/01/03

	if  (  bRet  )  TRACE(  _T(  "Initialisation for communicationport %d completed.\nUse Startmonitor to communicate.\n"  ), portNo  );
	else  TRACE(  _T(  "Initialisation for communicationport %d failed.\n"  ), portNo  );

	return  bRet;
}

// 
//  The CommThread Function.
//
UINT CComPort::CommThread(LPVOID pParam)
{
	// Cast the void pointer passed to the thread back to
	// a pointer of CComPort class
	CComPort *port = (CComPort*)pParam;
	
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
	
	//  2008/01/11
	memset(  &comstat,  0,  sizeof(  comstat  )  );

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
					port->ProcessErrorMessage(  _T(  "WaitCommEvent()")  );
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
				AfxEndThread(100);
				break;
			}
		case 1:	// read event
			{
				GetCommMask(port->m_hComm, &CommEvent);
				if (CommEvent & EV_CTS)
					::SendMessage(port->m_var.hWndOwner, WM_COMM_CTS_DETECTED, (WPARAM) 0, (LPARAM) port->m_var.uiComIndex  );
				if (CommEvent & EV_RXFLAG)
					::SendMessage(port->m_var.hWndOwner, WM_COMM_RXFLAG_DETECTED, (WPARAM) 0, (LPARAM) port->m_var.uiComIndex  );
				if (CommEvent & EV_BREAK)
					::SendMessage(port->m_var.hWndOwner, WM_COMM_BREAK_DETECTED, (WPARAM) 0, (LPARAM) port->m_var.uiComIndex  );
				if (CommEvent & EV_ERR)
					::SendMessage(port->m_var.hWndOwner, WM_COMM_ERR_DETECTED, (WPARAM) 0, (LPARAM) port->m_var.uiComIndex  );
				if (CommEvent & EV_RING)
					::SendMessage(port->m_var.hWndOwner, WM_COMM_RING_DETECTED, (WPARAM) 0, (LPARAM) port->m_var.uiComIndex  );
				
				// Receive character event from port.					
				if (CommEvent & EV_RXCHAR) ReceiveChar(port, comstat);
					
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

	return 0;
}

//
// start comm watching
//
BOOL CComPort::StartMonitoring()
{
	CQySyncObj	syncObj;
	if  (  syncObj.sync(  CONST_mutexName_syncComPort  )  <  0  )  return  FALSE;

	if  (  !isHandleValid(  this->m_hComm  )  )  return  FALSE;
	if  (  m_var.ucbStarted  )  return  FALSE;		//  已经启动了

	if (!(m_Thread = AfxBeginThread(CommThread, this)))  return FALSE;
	//
	m_var.ucbStarted  =  TRUE;
	//
	TRACE(  _T(  "Thread started\n")  );
	return TRUE;	
}



//
// Suspend the comm thread
//
BOOL CComPort::StopMonitoring()
{
	CQySyncObj	syncObj;
	if  (  syncObj.sync(  CONST_mutexName_syncComPort  )  <  0  )  return  FALSE;

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
	//
	return TRUE;	
}


//
// If there is a error, give the right message
//
void CComPort::ProcessErrorMessage(TCHAR* ErrorText)
{
	TCHAR *Temp = new TCHAR[200];
	
	LPVOID lpMsgBuf;

	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);

	_sntprintf(Temp, 200,  _T(  "WARNING:  %s Failed with the following error: \n%s\nPort: %d\n"  ), ErrorText, lpMsgBuf, m_var.nPortNo  ); 
	MessageBox(NULL, Temp, _T(  "Application Error"  ), MB_ICONSTOP);

	LocalFree(lpMsgBuf);
	delete[] Temp;
}

//
// Write a character.
//
 void CComPort::WriteChar(CComPort* port)
{
	BOOL	bWrite		=	TRUE;
	BOOL	bResult		=	TRUE;
	DWORD	BytesSent	=	0;
	TCHAR	tBuf[256]	=	_T(  ""  );

	traceLogA(  "WriteChar enters, [%s]",  port->m_var.szWriteBuf  );

	if  (  port->m_var.bDebug  )  SendMessage(  port->m_var.hWndOwner,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )_T(  "WriteChar enters."  ),  port->m_var.uiComIndex  );

	ResetEvent(port->m_hWriteEvent);

	// Gain ownership of the critical section
	EnterCriticalSection(&port->m_csCommunicationSync);

	if (bWrite)
	{
		// Initailize variables
		port->m_ov.Offset = 0;
		port->m_ov.OffsetHigh = 0;

		// Clear buffer
		PurgeComm(port->m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

		bResult = WriteFile(port->m_hComm,							// Handle to COMM Port
							port->m_var.szWriteBuf,					// Pointer to message buffer in calling finction
							strlen((char*)port->m_var.szWriteBuf),	// Length of message to send
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
						port->ProcessErrorMessage(  _T(  "WriteFile()")  );
					}
			}
		} 
		else
		{
			LeaveCriticalSection(&port->m_csCommunicationSync);
		}
	} // end if(bWrite)

	if (!bWrite)
	{
		bWrite = TRUE;
	
		bResult = GetOverlappedResult(port->m_hComm,	// Handle to COMM port 
									  &port->m_ov,		// Overlapped structure
									  &BytesSent,		// Stores number of bytes sent
									  TRUE); 			// Wait flag

		LeaveCriticalSection(&port->m_csCommunicationSync);

		// deal with the error code 
		if (!bResult)  
		{
			port->ProcessErrorMessage(  _T(  "GetOverlappedResults() in WriteFile()")  );
		}	
	} // end if (!bWrite)

	// Verify that the data size send equals what we tried to send
	if  (  BytesSent  !=  strlen(  (char*)port->m_var.szWriteBuf  )  )  {
		
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "WARNING: WriteFile() error.. Bytes Sent: %d; Message Length: %d"  ),  BytesSent,  strlen(  (  char  *  )port->m_var.szWriteBuf  )  );
		TRACE(  _T(  "%s\n"  ), tBuf  );

		if  (  port->m_var.bDebug  )  SendMessage(  port->m_var.hWndOwner,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )tBuf,  port->m_var.uiComIndex  );
		}
	else  {
		  if  (  port->m_var.bDebug  )  SendMessage(  port->m_var.hWndOwner,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )_T(  "WriteChar finished."  ),  port->m_var.uiComIndex  );		  

		  //  2008/11/15. 如果有报告窗口，则将结果反馈到报告窗口
		  if  (  IsWindow(  port->m_var.hWnd_notify  )  )  {
			  QVD_SM_RESP	resp;
			  memset(  &resp,  0,  sizeof(  resp  )  );
			  resp.iUsrData  =  port->m_var.iUsrData;

			  traceLogA(  "Short message %d has been sent.",  resp.iUsrData  );

			  COPYDATASTRUCT	tmpCopyData;
			  tmpCopyData.cbData  =  sizeof(  resp  );
			  tmpCopyData.lpData  =  &resp;
			  SendMessage(  port->m_var.hWnd_notify,  WM_COPYDATA,  0,  (  LPARAM  )&tmpCopyData  );
		  }
	}

	postMsg2Mgr_vDevComs(  port->m_var.pVDev,  CONST_misMsgType_sendFinished,  port->m_var.uiComIndex,  NULL,  0  );

	//  开放标志位待机。
	port->m_var.ucbSending  =  FALSE;

	//
	traceLogA(   "WriteChar leaves"  );

}

//
// Character received. Inform the owner
//
 void CComPort::ReceiveChar(CComPort* port, COMSTAT comstat)
{
	BOOL				bRead			=	TRUE; 
	BOOL				bResult			=	TRUE;
	DWORD				dwError			=	0;
	DWORD				BytesRead		=	0;
	unsigned char		RXBuff			=	0;

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
							port->ProcessErrorMessage(  _T(  "ReadFile()")  );
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
				port->ProcessErrorMessage(  _T(  "GetOverlappedResults() in ReadFile()")  );
			}	
		}  // close if (!bRead)
				
		LeaveCriticalSection(&port->m_csCommunicationSync);

		// notify parent that a byte was received
		//  ::SendMessage((port->m_hOwner), WM_COMM_RXCHAR, (WPARAM) RXBuff, (LPARAM) port->m_nPortNr);
		
		if  (  port->m_var.nRead  >=  port->m_var.nReadBufSize  -  1  )  {	//  这里数据还没提交错了，清空
			port->m_var.nRead  =  0;
		}
		//  加到缓冲尾部
		port->m_var.szReadBuf[port->m_var.nRead]  =  RXBuff;
		port->m_var.nRead  ++  ;

		if  (  port->m_var.bDebug  )  {
			TCHAR	tBuf[256]	=	_T(  ""  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "RXChar is 0x%02x - [%c]"  ),  RXBuff,  RXBuff  );
			SendMessage(  port->m_var.hWndOwner,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )tBuf,  port->m_var.uiComIndex  );
			//  traceLogA(  "RXChar is [%c]",  (  char  )RXBuff  );
		}

		BOOL	bSubmit  =  FALSE;

		if  (  !port->m_var.bReadLine  )  bSubmit  =  TRUE;
		else  {
			  if  (  !port->m_var.ucbReadyForPdu  )  {
				  if  (  RXBuff  ==  port->m_var.endChar  )  bSubmit  =  TRUE;				
			  }
			  if  (  port->m_var.ucbReadyForPdu  )  {
				  if  (  port->m_var.nRead  >=  4  )  {
					  if  (  !strnicmp(  port->m_var.szReadBuf  +  port->m_var.nRead  -  4,  CONST_gsmResp_readyForPdu,  4  )  )  {
						  traceLogA(  "输入提示符得到了"  );  
						  bSubmit  =  TRUE;
						  port->m_var.ucbReadyForPdu  =  FALSE;
					  }
				  }				  
			}
		}
		
		if  (  bSubmit  )  {
				  
			port->m_var.szReadBuf[port->m_var.nRead]  =  0;
			//
			SendMessage(  port->m_var.hWndOwner,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )CString(  port->m_var.szReadBuf  ).GetBuffer(  0  ),  (  LPARAM  )port->m_var.uiComIndex  );
			//
			traceLogA(  "这里，准备向mgr发送接收到的数据了, [%s]",  port->m_var.szReadBuf  );
			IM_DATA_CONTENT		dataContent;
			memset(  &dataContent,  0,  sizeof(  dataContent  )  );
			dataContent.uiType  =  CONST_imCommType_dataContent;
			dataContent.ulLen  =  min(  port->m_var.nRead  +  1,  sizeof(  dataContent.buf  )  );
			safeStrnCpy(  port->m_var.szReadBuf,  dataContent.buf,  dataContent.ulLen  );
			//
			postMsg2Mgr_vDevComs(  port->m_var.pVDev,  CONST_misMsgType_input,  port->m_var.uiComIndex,  (  char  *  )&dataContent,  offsetof(  IM_DATA_CONTENT,  buf  )  +  dataContent.ulLen  );
			//
			port->m_var.nRead  =  0;			
		}		

	} // end forever loop

	//  traceLogA(  "ReceiveChar leaves"  );

}

//
// Write a string to the port
//
 int CComPort::WriteToPort(char* string)
{
	int			iErr		=	-1;
	CQySyncObj	obj;
	TCHAR		tBuf[128]	=	_T(  ""  );
	
	traceLogA(  "WriteToPort enters"  );

	if  (  !isHandleValid(  m_hComm  )  )  return  -1;
	if  (  !m_var.ucbStarted  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Write failed: port is not started"  )  );
		SendMessage(  m_var.hWndOwner,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )CString(  tBuf  ).GetBuffer(  0  ),  m_var.uiComIndex  );
		return  -1;
	}

	if  (  m_var.bDebug  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "WriteToPort: %d bytes. [%s]"  ),  strlen(  string  ),  CString(  string  )  );
		SendMessage(  m_var.hWndOwner,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )CString(  tBuf  ).GetBuffer(  0  ),  m_var.uiComIndex  );
	}	

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "syncComW%d"  ),  m_var.uiComIndex  );
	if  (  obj.sync(  tBuf  )  )  return  -1;

	if  (  m_var.ucbSending  )  {
		SendMessage(  m_var.hWndOwner,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )_T(  "Write failed: Sth is being sent."  ),  m_var.uiComIndex  );
		return  -1;		//  尚有数据在发送之中。2008/01/04
	}

	if  (  m_var.nWriteBufSize  <=  strlen(  string  )  )  return  -1;

	memset(m_var.szWriteBuf, 0,   m_var.nWriteBufSize);
	strcpy(m_var.szWriteBuf, string);

#define		CONST_gsmCmd_cmgs	"AT+CMGS="
	//
	m_var.ucbReadyForPdu  =  !strnicmp(  string,  CONST_gsmCmd_cmgs,  strlen(  CONST_gsmCmd_cmgs  )  );
	if  (  m_var.ucbReadyForPdu  )  {
		traceLogA(  "将准备接收数据"  );
	}
	
	m_var.ucbSending  =  TRUE;					//  这里设置发送状态位。2008/01/05

	//  set event for write
	SetEvent(m_hWriteEvent);
	
	iErr  =  0;

//  errLabel:

	traceLogA(  "WriteToPort leaves"  );

	return  iErr;
}

//
// Return the device control block
//
DCB CComPort::GetDCB()
{
	return m_dcb;
}

//
// Return the communication event masks
//
DWORD CComPort::GetCommEvents()
{
	return m_var.dwCommEvents;
}

//
// Return the output buffer size
//
DWORD CComPort::GetWriteBufSize()
{
	return m_var.nWriteBufSize;
}




