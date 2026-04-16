
#ifndef __COMPORT_H__
#define __COMPORT_H__




#define WM_COMM_BREAK_DETECTED		WM_USER+1				// A break was detected on input.
#define WM_COMM_CTS_DETECTED		WM_USER+2				// The CTS (clear-to-send) signal changed state. 
#define WM_COMM_DSR_DETECTED		WM_USER+3				// The DSR (data-set-ready) signal changed state. 
#define WM_COMM_ERR_DETECTED		WM_USER+4				// A line-status error occurred. Line-status errors are CE_FRAME, CE_OVERRUN, and CE_RXPARITY. 
#define WM_COMM_RING_DETECTED		WM_USER+5				// A ring indicator was detected. 
#define WM_COMM_RLSD_DETECTED		WM_USER+6				// The RLSD (receive-line-signal-detect) signal changed state. 
//
#define CONST_wmComm_EV_RXCHAR		WM_USER+7				// A character was received and placed in the input buffer. 
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




class CComPort
{														 
public:
		// contruction and destruction
		CComPort();
		virtual					~CComPort();

		// port initialisation											
		BOOL					InitPort(  void  *  pVDev,  unsigned  int  uiComIndex,  HWND  hWndPortOwner,  char  *  smsc,  UINT portNo = 1, UINT baud = 9600, TCHAR parity = _T(  'N'  ), UINT databits = 8, UINT stopsbits = 1, DWORD dwCommEvents = EV_RXCHAR | EV_CTS,  BOOL  bReadLine  =  TRUE,  UINT  nWriteBufSize = 512,  UINT  nReadBufSize  =  4096  );
		BOOL					InitPort(  void  *  pVDev  )  {  return  InitPort(  pVDev,  m_var.uiComIndex,  m_var.hWndOwner,  m_var.smscBuf,  m_var.nPortNo,  m_var.baud  );  }

		int						setOwnerWnd(  HWND  hWndPortOwner  )  {  m_var.hWndOwner  =  hWndPortOwner;  return  0;  }
		int						setDebugOn(  BOOL  bOnOff  )  {  m_var.bDebug  =  bOnOff;  return  0;  }

		// start/stop comm watching
		BOOL					StartMonitoring();
		BOOL					StopMonitoring();

		DWORD					GetWriteBufSize();
		DWORD					GetCommEvents();
		DCB						GetDCB();

		int						WriteToPort(char* string);

protected:
	// protected memberfunctions
		void					ProcessErrorMessage(TCHAR* ErrorText);
		static UINT				CommThread(LPVOID pParam);
		static void				ReceiveChar(CComPort* port, COMSTAT comstat);
		static void				WriteChar(CComPort* port);
	
		// thread
		CWinThread	*			m_Thread;

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
		DCB						m_dcb;

	//

public:
	struct						{						//  2008/01/03
		//
		void				*	pVDev;
		unsigned  int			uiComIndex;
		// owner window
		HWND					hWndOwner;
		BOOL					bDebug;

		// misc
		UINT					nPortNo;
		UINT					baud;
		DWORD					dwCommEvents;
		//
		TCHAR					szPort[50];

		//
		char					smscBuf[64  +  1];		//  2008/01/05, 应该从sim卡里读一下
		char					modelBuf[256];			//  2008/01/24, 型号
		//
		struct					{
            QY_MESSENGER_ID		idInfo_contact;			//  短信收发的联系人。为0表明不指定
			TCHAR				cusName[96  +  1];		//  从服务器下载的别名, 用于辨认。
			time_t				tLastModifiedTime;
		}						smPolicy;
		//		

		//
		char				*	szWriteBuf;
		DWORD					nWriteBufSize;
		//
		char				*	szReadBuf;
		DWORD					nReadBufSize;
		//
		BOOL					bReadLine;				//  2008/01/04, 是否读完一行再提交. 
		unsigned  char			endChar;				//  结束符为13.
		//
		DWORD					nRead;					//  已读到的字节数
		//
		unsigned  char			ucbComExists;
		unsigned  char			ucbStarted;
		//
		unsigned  char			ucbSending;				//  数据尚在发送之中。所以，调用WriteToPort(  )将failed.
		//
		unsigned  char			ucbReadyForPdu;			//  如果，此标志为1，则进入消息内容接收。需要得到的响应码为"\r\n> "
		unsigned  char			ucbNewSmArrived;		//  是否新的sm来了
		//
		//
		GENERIC_Q				toBeDelMsgIndexQ;		//  将删除的消息索引的队列  
		BOOL					bToBeDelMsgIndexQInited;

		//  2008/11/25, 下面2个是发送成功了，请发送一个响应回去
		HWND					hWnd_notify;
		int						iUsrData;


	}							m_var;

};

#endif __SERIALPORT_H__


