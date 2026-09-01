
#ifndef __COMPORTEX_H__
#define __COMPORTEX_H__




#define WM_COMM_BREAK_DETECTED		WM_USER+1				// A break was detected on input.
#define WM_COMM_CTS_DETECTED		WM_USER+2				// The CTS (clear-to-send) signal changed state. 
#define WM_COMM_DSR_DETECTED		WM_USER+3				// The DSR (data-set-ready) signal changed state. 
#define WM_COMM_ERR_DETECTED		WM_USER+4				// A line-status error occurred. Line-status errors are CE_FRAME, CE_OVERRUN, and CE_RXPARITY. 
#define WM_COMM_RING_DETECTED		WM_USER+5				// A ring indicator was detected. 
#define WM_COMM_RLSD_DETECTED		WM_USER+6				// The RLSD (receive-line-signal-detect) signal changed state. 
//
//#define CONST_wmComm_EV_RXCHAR		WM_USER+7				// A character was received and placed in the input buffer. 
//
#define WM_COMM_RXFLAG_DETECTED		WM_USER+8				// The event character was received and placed in the input buffer.  
#define WM_COMM_TXEMPTY_DETECTED	WM_USER+9				// The last character in the output buffer was sent.  


#define		CONST_gsmResp_readyForPdu		"\r\n> "
#define		CONST_gsmResp_ok				"OK\r\n"
#define		CONST_gsmRespPhrase_cmgl		"+CMGL:"
//
#define		CONST_gsmPhrase_cmti			"+CMTI:"	//  自动提醒
//
#define		CONST_gsmRespPhrase_pduErr		"ERROR"
#define		CONST_gsmRespPhrase_err			"+CMS ERROR"


#include	"gpsCommProc.h"

//
#define		CONST_mutexName_syncComPort		_T(  "syncComPort"  )


//
#define		CONST_iComPortType_null					0
#define		CONST_iComPortType_gsm					1
#define		CONST_iComPortType_gps					2
#define		CONST_iComPortType_ptz					3
#define		CONST_iComPortType_infrared				4


//
class CComPortEx
{														 
public:
		// contruction and destruction
		CComPortEx();
		virtual					~CComPortEx();

		// port initialisation											
		//  BOOL					bInitPort(  HWND  hPortOwner,  UINT  portNo  = 1,  UINT  baud  =  19200,  char  parity  =  'N',  UINT  databits  =  8,  UINT  stopsbits  =  1,  DWORD  dwCommEvents  =  EV_RXCHAR  |  EV_CTS,  UINT  nBufferSize  =  512,  int  iUsrData  =  0  );
		BOOL					bInitPort(  HWND  hPortOwner,  UINT  portNo  = 1,  UINT  baud  =  19200,  char  parity  =  NOPARITY,  UINT  databits  =  8,  UINT  stopsbits  =  ONESTOPBIT,  DWORD  dwCommEvents  =  EV_RXCHAR  |  EV_CTS,  UINT  nBufferSize  =  512,  int  iComPortType  =  0,  int  iUsrData  =  0  );

#if  10
		int						setOwnerWnd(  HWND  hWndPortOwner  )  {  m_var.hWndOwner  =  hWndPortOwner;  return  0;  }
		int						setDebugOn(  BOOL  bOnOff  )  {  m_var.bDebug  =  bOnOff;  return  0;  }
#endif

		// start/stop comm watching
		BOOL					bStartMonitoring();
#if  0
		BOOL					bStopMonitoring();
#endif

		DWORD					GetWriteBufSize();
		DWORD					GetCommEvents();
		DCB						GetDCB();

public:
		int						WriteToPort(BYTE* string,  int  nLength  );

		//  2012/08/01
public:
		BOOL					bThreadAlive(  )  {  return  m_bThreadAlive;  };

protected:
	// protected memberfunctions
		void					ProcessErrorMessage(TCHAR* ErrorText);
		static UINT				CommThread(LPVOID pParam);
		static void				ReceiveChar(CComPortEx* port, COMSTAT comstat);
		static void				WriteChar(CComPortEx* port);
	
		// thread
		//  CWinThread	*			m_Thread;

		//  synchronisation objects
		CRITICAL_SECTION		m_csCommunicationSync;
		BOOL					m_bCsCommunicationSyncInitialized;		//  2008/01/04

		BOOL					m_bThreadAlive;

		// handles
		HANDLE					m_hShutdownEvent;
		HANDLE					m_hComm;
		HANDLE					m_hWriteEvent;

		// Event array. 
		// One element is used for each event. There are two event handles for each port.
		// A Write event and a receive character event which is located in the overlapped structure (m_ov.hEvent).
		// There is a general shutdown when the port is closed. 
		HANDLE					m_hEventArray[3];

		// structures
		OVERLAPPED				m_ov;
		COMMTIMEOUTS			m_CommTimeouts;
		
public:
		//  CWnd				*	m_pOwner;
		//  misc
		UINT					m_nPortNo;
		DWORD					m_dwCommEvents;
		DCB						m_dcb;
		BOOL					m_bBlockRead;

		//
#if  0
		static  BYTE	*		ReadBlock(  CComPortEx  *  port,  int  & readLen  );
#endif

public:
	struct						{						//  2008/01/03

		//  2012/08/15
		DWORD				dwThreadId;
		HANDLE				hThread;


		// owner window
		HWND					hWndOwner;
		BOOL					bDebug;

		int						iComPortType;
		int						iUsrData;

		TCHAR					szPort[50];

		unsigned  char			ucbComExists;
		unsigned  char			ucbStarted;

		//
		unsigned  char			ucbSeriousErr;			//  遇到了严重故障

		//
		BYTE				*	m_szWriteBuffer;
		DWORD					m_nWriteBufferSize;

		BYTE				*	m_szReadBuf;
		DWORD					m_nReadBufSize;

		//
		DWORD					nRead;					//  已读到的字节数
		int						m_nToSend;

		//  2012/08/01
		DWORD					dwTickCnt_lastRead;
		DWORD					dwTickCnt_lastWrite;

		//
		myGPS_POSITION			gpsPos;
		DWORD					dwTickCnt_modified_gpsPos;

		//
		void				*	pMsgBuf;


		//  2012/05/24
		DWORD					dwTickCnt_toShareGps;

		//  2012/04/26
		time_t					tLastTime_sendGps;
		time_t					tLastTime_showFrameInfo;

		//
		PF_parseGpsStr			pf_parseGpsStr;

	}							m_var;

};

#endif __SERIALPORT_H__


