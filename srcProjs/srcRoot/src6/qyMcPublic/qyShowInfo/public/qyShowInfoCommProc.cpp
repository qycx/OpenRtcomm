
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<assert.h>
#include	<stddef.h>
#include	<tchar.h>
#include	<stdlib.h>
//#include	<mmeapi.h>
#include	<MMSystem.h>

#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmPcComm.h"
#include	"qnmAssetsCommProc.h"
#include	"qnmSpCommProc.h"
#include	"qwmNetworkStatusCommProc.h"
#include	"qyTCharCommProc.h"
#include	"qnmCustom.h"
#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"
#include	"tmpCeLib.h"
#include	"qyShowInfoCommon.h"
#include	"qy_qBuf2_defs.h"




#if  0
static  struct						{
				BOOL				bInited;
				//
				TCHAR				errHintWndCls[512];
				PF_qyShowInfo0		errHintPf;
				//
				DWORD				dwThreadId;
				HANDLE				hThread;
				BOOL				bQuit;
				//
				BOOL				bShowMore;
				//
				TCHAR				mutexName_syncQ[32];
				//
				BOOL				bUsePipe;			//  2012/02/03
				//
				BOOL				bQInited;
				//
				RW_lock_param		rwLockParam;		//  2009/05/14
	 
				//  GENERIC_Q		q;
				QY_Q2				q2;
				//
}
#endif

static  ShowInfo_struct  sShowInfoStruct  =	{		FALSE,
									//
									_T(  ""  ),
									NULL,
									//
									0,
									NULL,
									FALSE,
									//
									FALSE,
									//
									_T(  "syncQ_showInfo"  ),
									//
									FALSE,	
									//
									FALSE,
									
							};

//
ShowInfo_struct  *  g_pShowInfoStruct  =  &sShowInfoStruct;//NULL;

extern  "C"  __declspec(dllexport) void resetShowInfoServIp(const char* servIp, int port) {
	strncpy(sShowInfoStruct.servIp, servIp, sizeof(sShowInfoStruct.servIp) - 1);
	sShowInfoStruct.usPort = port;
	sShowInfoStruct.bResetServ = true;
}


//
#if  0
extern  "C"  __declspec(  dllexport  )  void  *  get_pShowInfoStruct(  )
{
	return  &sShowInfoStruct;
}
#endif

//
 extern  "C"  __declspec(  dllexport  )  int  setErrHintWndCls(  LPCTSTR  title  )
{
	 if  (  lstrlen(  title  )  >=  mycountof(  sShowInfoStruct.errHintWndCls  )  )  return  -1;

	 lstrcpyn(  sShowInfoStruct.errHintWndCls,  title,  mycountof(  sShowInfoStruct.errHintWndCls  )  );
	 return  0;
}


 extern  "C"  int  setErrHintPf(  PF_qyShowInfo0  pf  )
{
	 sShowInfoStruct.errHintPf  =  pf;

	 return  0;
}

 extern  "C"  int  setShowMoreOn(  BOOL  bShowMore  )
{
	 sShowInfoStruct.bShowMore  =  bShowMore;

	 return  0;
}

 extern  "C"  __declspec(  dllexport  )  int  bShowMore(  )
{
	 return  sShowInfoStruct.bShowMore;
}

  extern  "C"  __declspec(  dllexport  )  void  exitShowInfo(  void  **  ppCtx_showInfo  )
{
	 CQySyncObj		syncObj;
	 
	 if  (  !ppCtx_showInfo  )  return;
	 if  (  !*ppCtx_showInfo  )  return;

	 //
	 traceLog(  _T(  "exitShowInfo enters"  )  );

	 //
	 clear_q_showInfo(  );

	 //
	 int  i;
	 for  (  i  =  0;  i  <  10;  i  ++  )  {
		 if  (sShowInfoStruct.pq2->is_Q2Empty(    )  )  break;
		 Sleep(  10  );
		 continue;
	 }
	 //
	 sShowInfoStruct.bQuit  =  TRUE;
	 sShowInfoStruct.pq2->q2PostMsgAndTrigger(  mynull,NULL,  0,    _T(  "exitShowInfo"  )  );
	 MACRO_qyNullThread(  sShowInfoStruct.hThread  );

	 if  (  sShowInfoStruct.bQInited  )  {
		 sShowInfoStruct.pq2->exitQyQ2(    );  sShowInfoStruct.bQInited  =  FALSE;
	 }
	 //  2015/08/23
	 if  (  sShowInfoStruct.bQInited_state  )  {
		 sShowInfoStruct.pstate_q2->exitQyQ2(   );  sShowInfoStruct.bQInited_state  =  FALSE;
	 }
	 MACRO_safeDelete(sShowInfoStruct.pq2);
	 MACRO_safeDelete(sShowInfoStruct.pstate_q2);

	 //
	 qyTcpEnd();

	 //
	 sShowInfoStruct.bInited  =  FALSE;
	 //
	 *ppCtx_showInfo  =  NULL;

	 //
	 traceLog(  _T(  "exitShowInfo leaves"  )  );


}

 DWORD  WINAPI  showInfoThreadProc(  LPVOID  lpParameter  );






 //
#if 10
 extern  "C"  __declspec(  dllexport  )  int  initShowInfo(  void  *  p0,  LPCTSTR  mutexName_syncQ,  LPCTSTR  errHintWndCls,  BOOL  bUsePipe,   BOOL  bCli,  void  **  ppCtx_showInfo   )
{
	return  initShowInfo_func(  p0,  mutexName_syncQ,  errHintWndCls,  bUsePipe,  false,  NULL,  bCli,  ppCtx_showInfo  );
}
#endif


  //
 extern  "C"  __declspec(  dllexport  )  int  initShowInfo_cli(  void  *  p0,  LPCTSTR  mutexName_syncQ,  char  *  servIp,  void  **  ppCtx_showInfo   )
{
	bool  bUsePipe  =  true;
	bool  bUseSock  =  false;
	
	//
#if  10
	 bUsePipe  =  false;
	 bUseSock  =  true;
#endif

	//
	return  initShowInfo_func(  p0,  mutexName_syncQ,  _T(  "unused"  ),  bUsePipe,  bUseSock,  servIp,  true,  ppCtx_showInfo  );  
}


 //
 extern "C" __declspec(dllexport ) int  initShowInfo_func(  void  *  p0,  LPCTSTR  mutexName_syncQ,  LPCTSTR  errHintWndCls,  BOOL  bUsePipe,   BOOL  bUseSock,  char  *  servIp,  BOOL  bCli,  void  **  ppCtx_showInfo   )
{
	 int	iErr  =  -1;
	 DWORD	dwThreadDaemonId;

	 if  (  sShowInfoStruct.bInited  )  return  -1;
	 //
	 if  (  !ppCtx_showInfo  )  return  -1;		//  2014/03/19
	 if  (  *ppCtx_showInfo  )  return  -1;		//  2014/03/19
	 //
	 if  (  !mutexName_syncQ  ||  !mutexName_syncQ[0]  )  return  -1;
	 if  (  !errHintWndCls  ||  !errHintWndCls[0]  )  return  -1;

	 //
	 memset(  &sShowInfoStruct,  0,  sizeof(  sShowInfoStruct  )  );

	 //
	 qyTcpStart();

	 //
	 lstrcpyn(  sShowInfoStruct.mutexName_syncQ,  mutexName_syncQ,  mycountof(  sShowInfoStruct.mutexName_syncQ  )  );
	 if  (  setErrHintWndCls(  errHintWndCls  )  )  goto  errLabel;
	 sShowInfoStruct.bUsePipe  =  bUsePipe;
	 //
	 if  (  !sShowInfoStruct.bUsePipe  )  {
		 sShowInfoStruct.bUseSock  =  bUseSock;
	 }
	 if  (  sShowInfoStruct.bUseSock  )  {
		 safeStrnCpy(  servIp,  sShowInfoStruct.servIp,  mycountof(  sShowInfoStruct.servIp  )  );
		 if ( bCli){
			sShowInfoStruct.usPort  =  DEFAULT_qyPort_showInfo_cli;
			}
		 else {
			sShowInfoStruct.usPort  =  DEFAULT_qyPort_showInfo_serv;
		 }
	 }

	 //
	 sShowInfoStruct.bCli  =  bCli;
	 
	 //  memset(  &rwLockParam,  0,  sizeof(  rwLockParam  )  );
	 sShowInfoStruct.rwLockParam.uiMaxCnt_sema			=	CONST_uiInitCnt_sema_q2SyncFlg;
	 sShowInfoStruct.rwLockParam.uiInitCnt_sema			=	sShowInfoStruct.rwLockParam.uiMaxCnt_sema  -  1;
	 sShowInfoStruct.rwLockParam.uiMilliSeconds_mutex_r	=	10000;
	 sShowInfoStruct.rwLockParam.uiMilliSeconds_sema_r	=	10000;
	 sShowInfoStruct.rwLockParam.uiMilliSeconds_mutex_w	=	10000;
	 sShowInfoStruct.rwLockParam.uiMilliSeconds_sema_w	=	10000;


	 //
	 GENERIC_Q_CFG	qCfg;
	 memset(  &qCfg,  0,  sizeof(  qCfg  )  );
	 _sntprintf(  qCfg.name,  mycountof(  qCfg.name  ),  _T(  "%s"  ),  _T(  "showInfoQ"  )  );
	 _sntprintf(  qCfg.mutexName_prefix,  mycountof(  qCfg.mutexName_prefix  ),  _T(  "%s"  ),  sShowInfoStruct.mutexName_syncQ  );
	 //  qCfg.uiMaxCnt_semaTrigger  =  CONST_maxCnt_sema_showInfoQ_is;
	 qCfg.uiMaxQNodes  =  bCli  ?  CONST_uiMaxQNodes_showInfoQ_is_cli  :  CONST_uiMaxQNodes_showInfoQ_is_mgr;
	 //
	 qCfg.m_qType=CONST_qType_showInfo;
	 
	 //
	 try {
		 sShowInfoStruct.pq2 = new QY_qBuf2();
		 sShowInfoStruct.pstate_q2 = new QY_qBuf2();
	 }
	 catch (...) {
		 goto  errLabel;
	 }

	 // 
	 int maxDataBufLen = (int)(qCfg.uiMaxQNodes * sizeof(QY_SHOW_STRUCT));

	 //if  (  initQyQ2(  &qCfg,  &sShowInfoStruct.rwLockParam,  1,  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  NULL,  &sShowInfoStruct.q2  )  )  goto  errLabel;
	 if (sShowInfoStruct.pq2->initQyQ2(qCfg.m_qType, qCfg.uiMaxQNodes,maxDataBufLen, sShowInfoStruct.rwLockParam, true,_T("showInfo.q2" )))  goto  errLabel;
	 sShowInfoStruct.bQInited  =  TRUE;

	 //  2015/08/23
	 memset(  &qCfg,  0,  sizeof(  qCfg  )  );
	 _sntprintf(  qCfg.name,  mycountof(  qCfg.name  ),  _T(  "%s"  ),  _T(  "showInfo_state_Q"  )  );
	 _sntprintf(  qCfg.mutexName_prefix,  mycountof(  qCfg.mutexName_prefix  ),  _T(  "%s_state"  ),  sShowInfoStruct.mutexName_syncQ  );
	 //  qCfg.uiMaxCnt_semaTrigger  =  CONST_maxCnt_sema_showInfoQ_is;
	 qCfg.uiMaxQNodes  =  bCli  ?  CONST_uiMaxQNodes_showInfoQ_state_is_cli  :  CONST_uiMaxQNodes_showInfoQ_state_is_mgr;
	 //
 	 qCfg.m_qType=CONST_qType_showInfo;

	 
	 // 
	 maxDataBufLen = (int)(qCfg.uiMaxQNodes * sizeof(QY_SHOW_STRUCT));

	 //if  (  initQyQ2(  &qCfg,  &sShowInfoStruct.rwLockParam,  1,  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  NULL,  &sShowInfoStruct.state_q2  )  )  goto  errLabel;
	 if (sShowInfoStruct.pstate_q2->initQyQ2(qCfg.m_qType, qCfg.uiMaxQNodes, maxDataBufLen, sShowInfoStruct.rwLockParam, true, _T(  "showInfo.state_q2"  )))  goto  errLabel;
	 sShowInfoStruct.bQInited_state  =  TRUE;



	 //  2014/03/23
#if  0
	 sShowInfoStruct.pf_q2PostMsgAndTrigger  =  (  PF_q2PostMsgAndTrigger  )q2PostMsgAndTrigger;
#endif

	 //
	 sShowInfoStruct.hThread  =  CreateThread(  NULL,  0,  showInfoThreadProc,  (  LPVOID  )0,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
	 if  (  !sShowInfoStruct.hThread  )  goto  errLabel;
	 sShowInfoStruct.dwThreadId  =  dwThreadDaemonId;	//  2007/03/29, 为了引入这个标记，以便mtCliSockThreadProc能够在pMtSock里找到存放的物理位置，故要先挂起一下，然后再恢复
	 if  (  ResumeThread(  sShowInfoStruct.hThread  )  ==  -1  )  goto  errLabel;
 
	 sShowInfoStruct.bInited  =  TRUE;

	 //  2013/07/31
	 //set_g_pShowInfoStruct(  &sShowInfoStruct  );
	 //
	 *ppCtx_showInfo  =  &sShowInfoStruct;

	 //
	 set_q_showInfo(  showInfo_open0  );

	 //
	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {

		 exitShowInfo(  ppCtx_showInfo  );
		 
	 }

	 return  iErr;
}


#if 0
 DWORD  WINAPI  iishowInfoThreadProc(  LPVOID  lpParameter  )
{
	 DWORD				dwRet;
	 QY_SHOW_STRUCT		showStruct;
	 unsigned  int		len;
	 HWND				firstWnd			=		NULL;
	 BOOL				bUsePipe			=		sShowInfoStruct.bUsePipe;
	 HANDLE				hPipe				=		NULL;
	 //
	 //LPTSTR				lpszPipename		=		sShowInfoStruct.bCli  ?  CONST_statusPipeName_cli  :  CONST_statusPipeName_serv;
	 LPTSTR				lpszPipename		=		sShowInfoStruct.bCli  ?  CONST_statusPipeName_cli_pipeCli  :  CONST_statusPipeName_serv_pipeCli;
	 //
	 BOOL				fSuccess			=		FALSE; 
	 DWORD				cbRead  =  0, cbWritten  =  0, dwMode  =  0; 
	 //
	 DWORD				dwTickCnt_lastData	=		GetTickCount(  );

	 //
	 	 QY_SOCK					sock;
		 QY_COMM_SESSION			session;	memset(&session, 0, sizeof(session));
	 BOOL						bSessionOpen		=		FALSE;
	 SOCK_TIMEOUT				to;

	 //
	 int setSockTimeout( SOCK_TIMEOUT *p );

	 setSockTimeout(  &to  );
	 	 

	 //
	 traceLogA(  "showInfoThreadProc starts"  );
	 

	 //
	 while  (  !sShowInfoStruct.bQuit  )  {

		   //  2006/06/03
		   //dwRet  =  WaitForSingleObject(  sShowInfoStruct.q2.hEvents[0],  5000  );
		 dwRet = WaitForSingleObject(sShowInfoStruct.pq2->hEvent0, 5000);
		   if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
		   //  超时也要接着处理，以getMsg为准
		   
		   for  (  ;  !sShowInfoStruct.bQuit;  )  {

			    //q2AvoidTriggerTooHigh(  0,  sShowInfoStruct.pq2  );
				
				//
				BOOL  bMsgGot  =  FALSE;

				if  (  !sShowInfoStruct.pstate_q2->is_Q2Empty(    )  )  {
					HeadData_showInfo  headData;
					len  =  sizeof(  showStruct  );
					if  (sShowInfoStruct.pstate_q2->q2GetMsg( &headData, &showStruct,  &len,  _T(  "showInfoThreadProc.state_q2"  )  )  )  break;
					bMsgGot  =  TRUE;

					//
					unsigned char ucPercent = 0;
					int nQNodes= sShowInfoStruct.pstate_q2->get_Q2Nodes();
					ucPercent=nQNodes  *  100. / (  sShowInfoStruct.pstate_q2->cfg.uiMaxQNodes  *  2  );
					//
					showStruct.ucPercent_showInfoQ=ucPercent;
				}

				if  (  !bMsgGot  )  {
					//
					HeadData_showInfo headData;
				    len  =  sizeof(  showStruct  );
					if  (sShowInfoStruct.pq2->q2GetMsg(  &headData,&showStruct,  &len,  _T(  "showInfoThreadProc.q2"  )  )  )  break;
					
					//
					unsigned char ucPercent = 0;
					int nQNodes= sShowInfoStruct.pq2->get_Q2Nodes();
					ucPercent=nQNodes  *  100. / (  sShowInfoStruct.pq2->cfg.uiMaxQNodes  *  2  );
					//
					showStruct.ucPercent_showInfoQ=ucPercent;
				}
				

				//
				if  (  bUsePipe  )  {

			#ifdef  __WINCE__
					traceLogA(  "pipe is not supported in ce"  );
			#else
					//
					DWORD  dwTickCnt  =  GetTickCount(  );
					if  (  dwTickCnt  -  dwTickCnt_lastData  >  MAX_pipeCli_idleInMs  )  {
						if  (  isHandleValid(  hPipe  )  )  {
							CloseHandle(  hPipe  );  hPipe  =  NULL;
						}
					}
					dwTickCnt_lastData  =  dwTickCnt;

					//
					if  (  !isHandleValid(  hPipe  )  )  {
						hPipe = CreateFile( 
							lpszPipename,   // pipe name 
							GENERIC_READ |  // read and write access 
							GENERIC_WRITE, 
							0,              // no sharing 
							NULL,           // default security attributes
							OPEN_EXISTING,  // opens existing pipe 
							0,              // default attributes 
							NULL);          // no template file   
						if (  hPipe == INVALID_HANDLE_VALUE  )  {
							DWORD  dwErr  =  GetLastError(  );
							continue; 
						}
						
						traceLogA(  "showInfoThreadProc: pipe created"  );

						dwMode = PIPE_READMODE_MESSAGE; 
						fSuccess = SetNamedPipeHandleState( 
							hPipe,    // pipe handle 
							&dwMode,  // new pipe mode 
							NULL,     // don't set maximum bytes 
							NULL);    // don't set maximum time 
						if (!fSuccess)  {
							qyDisplayLastError(  "SetNamedPipeHandleState failed"  ); 
							CloseHandle(  hPipe  );  hPipe  =  NULL;
							continue;
						} 
					}

					fSuccess = WriteFile( 
						hPipe,                  // pipe handle 
						&showStruct,             // message 
						sizeof(  showStruct  ), // message length 
						&cbWritten,             // bytes written 
						NULL);                  // not overlapped 
					if  (  !fSuccess  )  {
						traceLogA("WriteFile failed"); 
						CloseHandle(  hPipe  );  hPipe  =  NULL;
						continue;
					}

			#endif

					continue;
				}
				if  (  sShowInfoStruct.bUseSock  )  {

					//
					DWORD  dwTickCnt  =  GetTickCount(  );
					if  (  dwTickCnt  -  dwTickCnt_lastData  >  MAX_pipeCli_idleInMs  )  {
						if  (  bSessionOpen  )  {
							qnmCloseSession(  &session,  &sock,  &to  );
							bSessionOpen  =  false;
						}
					}
					dwTickCnt_lastData  =  dwTickCnt;


					if  (  !bSessionOpen  )  {
						QWM_MACS_INFO  macsInfo;
						memset(&macsInfo,  0,  sizeof(  macsInfo  )  );
						macsInfo.nMacs  =  1;
						if  (  qnmOpenSession(  sShowInfoStruct.servIp,  sShowInfoStruct.usPort,  &macsInfo,  0,  CONST_qyServiceId_showInfo,  "",  NULL,  &session,  &sock,  &to,  NULL,  NULL  )  )  {
							continue;
						}
						bSessionOpen  =  true;

						//
#ifdef  __DEBUG__
						TCHAR  tBuf[128];
						_sntprintf(tBuf, mycountof(tBuf), _T("showInfo: connect to %S:%d ok"), sShowInfoStruct.servIp, sShowInfoStruct.usPort);
						traceLog(tBuf);
#endif
					}
					//
					//
					if  (  qySendReq(  &session,  &sock,  &to,  CONST_qyCmd_showInfo,  (char*)&showStruct,  sizeof(  showStruct  )  )  )  {
						qnmCloseSession(  &session,  &sock,  &to  );
						bSessionOpen  =  false;
						continue;
					}
					continue;
				}



				//
				if  (  sShowInfoStruct.errHintWndCls[0]  )  {

					if  (  !IsWindow(  firstWnd  )  )  {
						firstWnd  =  FindWindow(  sShowInfoStruct.errHintWndCls,  NULL  );
					}
					if  (  firstWnd  )  {
						COPYDATASTRUCT	tmpCopyData;
						LRESULT			lRet			=	0;
			
						tmpCopyData.lpData  =  &showStruct;
						tmpCopyData.cbData  =  sizeof(  showStruct  );
						lRet  =  SendMessage( firstWnd,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );

						//  traceLogA(  "lRet is %d",  lRet  );
						//  OutputDebugString(  _T(  "kk\n"   )  );
					}

					//  traceLogA(  "%s %s %s %s %s",  showStruct.when,  showStruct.who,  showStruct.where,  showStruct.doStr,  showStruct.what  );

				}
						   
		   
		   }
	
		   
	}
  
errLabel:

	if  (  isHandleValid(  hPipe  )  )  {
		CloseHandle(  hPipe  );  hPipe  =  NULL;
	}
	if  (  bSessionOpen  )  {
		qnmCloseSession(&session,&sock,&to  );
	}

	//
	traceLogA(  "showInfoThreadProc ends"  );

	return  0;
}
#endif


//
DWORD  WINAPI  showInfoThreadProc(LPVOID  lpParameter)
{
	DWORD				dwRet;
	QY_SHOW_STRUCT		showStruct;
	unsigned  int		len;
	HWND				firstWnd = NULL;
	BOOL				bUsePipe = sShowInfoStruct.bUsePipe;
	HANDLE				hPipe = NULL;
	//
	//LPTSTR				lpszPipename		=		sShowInfoStruct.bCli  ?  CONST_statusPipeName_cli  :  CONST_statusPipeName_serv;
	LPTSTR				lpszPipename = sShowInfoStruct.bCli ? CONST_statusPipeName_cli_pipeCli : CONST_statusPipeName_serv_pipeCli;
	//
	BOOL				fSuccess = FALSE;
	DWORD				cbRead = 0, cbWritten = 0, dwMode = 0;
	//
	DWORD				dwTickCnt_lastData = GetTickCount();

	//
	QY_SOCK					sock;		memset(&sock, 0, sizeof(sock)); sock.sockFd = -1;
	QY_COMM_SESSION			session;	memset(&session, 0, sizeof(session));
	BOOL						bSessionOpen = FALSE;
	SOCK_TIMEOUT				to;

	//
	int setSockTimeout(SOCK_TIMEOUT * p);

	setSockTimeout(&to);


	//
	traceLogA("showInfoThreadProc starts");


	//
	while (!sShowInfoStruct.bQuit) {

		//  2006/06/03
		//dwRet  =  WaitForSingleObject(  sShowInfoStruct.q2.hEvents[0],  5000  );
		dwRet = WaitForSingleObject(sShowInfoStruct.pq2->hEvent0, 5000);
		if (dwRet == WAIT_FAILED)  goto  errLabel;
		//  超时也要接着处理，以getMsg为准

		for (; !sShowInfoStruct.bQuit; ) {

			//q2AvoidTriggerTooHigh(  0,  sShowInfoStruct.pq2  );

			if (sShowInfoStruct.bUseSock) {


				//
				BOOL  bMsgGot = FALSE;

				if (!sShowInfoStruct.pstate_q2->is_Q2Empty()) {
					HeadData_showInfo  headData;
					len = sizeof(showStruct);
					if (!sShowInfoStruct.pstate_q2->q2GetMsg(&headData, &showStruct, &len, _T("showInfoThreadProc.state_q2"))) {
						bMsgGot = TRUE;

						//
						unsigned char ucPercent = 0;
						int nQNodes = sShowInfoStruct.pstate_q2->get_Q2Nodes();
						ucPercent = nQNodes * 100. / (sShowInfoStruct.pstate_q2->cfg.uiMaxQNodes * 2);
						//
						showStruct.ucPercent_showInfoQ = ucPercent;
					}
				}

				if (!bMsgGot) {
					//
					HeadData_showInfo headData;
					len = sizeof(showStruct);
					if (!sShowInfoStruct.pq2->q2GetMsg(&headData, &showStruct, &len, _T("showInfoThreadProc.q2"))) {

						bMsgGot = true;

						//
						unsigned char ucPercent = 0;
						int nQNodes = sShowInfoStruct.pq2->get_Q2Nodes();
						ucPercent = nQNodes * 100. / (sShowInfoStruct.pq2->cfg.uiMaxQNodes * 2);
						//
						showStruct.ucPercent_showInfoQ = ucPercent;
					}
				}

				if (!bMsgGot) {
					break;
				}

				//
				DWORD  dwTickCnt = GetTickCount();

				//			
		
				//
				if (dwTickCnt - dwTickCnt_lastData > MAX_pipeCli_idleInMs) {
					if (bSessionOpen) {
						qnmCloseSession(&session, &sock, &to);
						bSessionOpen = false;
					}
				}

				dwTickCnt_lastData = dwTickCnt;

				//
				TCHAR  tBuf[128];

				if (!bSessionOpen || sShowInfoStruct.bResetServ) {
					QWM_MACS_INFO  macsInfo;
					memset(&macsInfo, 0, sizeof(macsInfo));
					macsInfo.nMacs = 1;
					if (qnmOpenSession(sShowInfoStruct.servIp, sShowInfoStruct.usPort, &macsInfo, 0, CONST_qyServiceId_showInfo, "", NULL, &session, &sock, &to, NULL, NULL)) {
						Sleep(100);
#ifdef  __DEBUG__
						//
						if (0) {
							_sntprintf(tBuf, mycountof(tBuf), _T("showInfo: connect to %S:%d failed"), sShowInfoStruct.servIp, sShowInfoStruct.usPort);
							traceLog(tBuf);
						}
#endif
						continue;
					}
					bSessionOpen = true;

					if (sShowInfoStruct.bResetServ)
						sShowInfoStruct.bResetServ = false;

					//
#ifdef  __DEBUG__
					if (0) {
						_sntprintf(tBuf, mycountof(tBuf), _T("showInfo: connect to %S:%d ok"), sShowInfoStruct.servIp, sShowInfoStruct.usPort);
						traceLog(tBuf);
					}
#endif
				}

				//
				//
				int sizeShowStruct = sizeof(showStruct);
				if (qySendReq(&session, &sock, &to, CONST_qyCmd_showInfo, (char*)&showStruct, sizeShowStruct)) {
					qnmCloseSession(&session, &sock, &to);
					bSessionOpen = false;
					continue;
				}

				//
				continue;
			}

			//
			continue;
		}

		//
		continue;
	}

errLabel:

	if (isHandleValid(hPipe)) {
		CloseHandle(hPipe);  hPipe = NULL;
	}
	if (bSessionOpen) {
		qnmCloseSession(&session, &sock, &to);
	}

	//
	traceLogA("showInfoThreadProc ends");

	return  0;
}




 /*

*/




   extern  "C"  int  errLog(  char *  fmt,  ...  )
{		 
	va_list		args;
	//  char		filenamebuf[257];
	//  char		timebuf[50];
	FILE	*	fperr				=		NULL;
	int			fileLen				=		0;
#ifndef  __WINCE__
	int			errnoBuf;
#endif
	char		buf[256];
	HWND		firstWnd			=		NULL;

#ifndef  __WINCE__
	errnoBuf  =  errno;
#endif

	va_start(  args,  fmt  );

	_vsnprintf(  buf,  sizeof(  buf  )  -  1,  fmt,  args  );
	buf[sizeof(  buf  )  -  1]  =  0;

	if  (  sShowInfoStruct.errHintWndCls[0]  )  {
	
		firstWnd  =  FindWindow(  sShowInfoStruct.errHintWndCls,  NULL  );
		if  (  firstWnd  )  {
			COPYDATASTRUCT	tmpCopyData;
			
			tmpCopyData.lpData  =  buf;
			tmpCopyData.cbData  =  sizeof(  buf  )  -  1;
			SendMessage( firstWnd,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
		}
	}

	traceLogA(  "errLog: %s, %s",  buf,  !sShowInfoStruct.errHintWndCls[0]  ?  ""  :  (  firstWnd  ?  ""  :  "status window is not active"  )  );


	/*
	if  (  sErrLogFile[0]  ) {

		#ifdef  WIN32
			sprintf(  filenamebuf,  "%s",  sErrLogFile  );
		#else
			sprintf(  filenamebuf,  "%s/%s%d",  LOGDIR,  COMMONERRLOGFILE,  getpid(  )  );
		#endif

		getcurtime(  timebuf  );

		if  (  !(  fperr  =  fopen(  filenamebuf,  "a"  )  )  )  {
			traceLogA(  "Can't open a file to show error info."  );
			}
		else  {
			  fprintf(  fperr,  "%s|%s: ",  timebuf,  sErrLogHint  );
			  vfprintf(  fperr,  fmt,  args  );
			  fprintf(  fperr,  "\n"  );
			  fflush(  fperr  );
			  fclose(  fperr  );
		}

		fileLen  =  getFileLen(  filenamebuf  );
		if  (   fileLen  >  MAX_ERR_LOG_FILE_LEN  )  {
			traceLogA(  "%s is too long, so is to be truncated.",  filenamebuf  );
			if  (  !truncFileHead(  fileLen  -  MAX_ERR_LOG_FILE_LEN / 2,  filenamebuf  )  )  {
				traceLogA(  "%s is truncated.",  filenamebuf  );
				}
			else  {
				  traceLogA(  "%s can't be truncated, is to be deleted.",  filenamebuf  );
				  DeleteFile( filenamebuf );
			}
		}

	}
	*/
	
	va_end(  args  );

#ifndef  __WINCE__
	errno  =  errnoBuf;
#endif

	return  0;

}



