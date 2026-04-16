

#include	"stdafx.h"

#include	<string.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
	#include	<fcntl.h>
	#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#ifndef  __WINCE__
#pragma include_alias( "dxtrans.h", "myqedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__

	//  #include	<Qedit.h>
	#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>

#include	"qmcDmoPublic.h"
#ifndef  __WINCE__
	#include	"qmcVideoCapture_dx.h"
#endif
#include	"myfourcc.h"

#include	"qyCusResTemp.h"

//  #include	"qyMc.h"
#include	"qyGuiCommProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecordPublic.h"

//#include	"myresource.h"

//#include	"DlgShareDynBmps.h"
#include	"dlgshareDynBmpsProc.h"

#include	"qyOpenShellCommon.h"
#include	"dlgTalkProc.h"
#include	"qmcCmdProc.h"

//  #include	"DlgProgress.h"
#include	"tmpCeLib.h"

#include	"qyComPortEx.h"
#include	"qmcGpsProc.h"

#include	"myDb.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

//#include	"dlgRtspUrl.h"
#include	"wallTalkers.h"
#include	"remoteStorageCfg.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliExPublic.h"

#include	"ctxMcThread.h"
#include	"qisPipe_open.h"
//
#include	"qisOnvifCommProc_open.h"
#include	"qisMsg_open.h"

//
 extern "C" DWORD WINAPI shareDynBmps_threadProc( LPVOID lpParameter );

 //
 int  doShareDynBmpsProc_noMsg(  HWND  hDlgShareDynBmps,  DLG_shareDynBmps_var  *  pDlgVar,  CTX_mc_shareDynBmpsThread  *  pCtx  );
 int  doShareDynBmpsProc_msg(  HWND  hDlgShareDynBmps,  DLG_shareDynBmps_var  *  pDlgVar,  OnvifMsg_common  *  pMsg,  unsigned  int  msgLen,  CTX_mc_shareDynBmpsThread  *  pCtx  );

 //
 int  doOnvifRule_discovery(  HWND  hDlgShareDynBmps,  DLG_shareDynBmps_var  *  pDlgVar,  CTX_mc_shareDynBmpsThread  *  pCtx,  int  index_rule  );
 int  doOnvifRule_probe(  HWND  hDlgShareDynBmps,  DLG_shareDynBmps_var  *  pDlgVar,  CTX_mc_shareDynBmpsThread  *  pCtx,  int  index_rule  );


 
//
int  askOnvifCliToQuit(  ShareDynBmps_threadProcInfo  *  pRtsp,  QIS_pipe  *  pQisPipe  )
{
	int  iErr  =  -1;
	DWORD  dwRet;		 
	//
	TCHAR	evtName[256];		
	HANDLE	hEvent  =  NULL;		 
	int  i;

	if  (  !pRtsp->hProcess_onvifCli  )  return  0;
		
	//  2016/07/25
	OnvifMsg_quit	msgQuit  =  {0};
	msgQuit.uiType  =  CONST_qisMsgType_onvif;
	msgQuit.iSubtype  =  CONST_onvifMsg_subtype_quit;
	qisPipe_writeMsg(  &msgQuit,  sizeof(  msgQuit  ),  pQisPipe  );

	//
	_sntprintf(  evtName,  mycountof(  evtName  ),  _T(  "%s%d"  ),  CONST_evtNamePrefix_rtspCliSyncQuit,  pRtsp->tn_onvifCliPipe  );	
	hEvent  =  CreateEvent(  NULL,  FALSE,  FALSE,  evtName  );
	
	//	
	if  (  hEvent  )  SetEvent(  hEvent  );

	 
	iErr  =  0;

errLabel:

	
	if  (  hEvent  )  CloseHandle(  hEvent  );

	return  iErr;
}


//
int  createOnvifCli(  ShareDynBmps_threadProcInfo  *  pSt  )
{
	int			iErr	=	-1;
	MC_VAR_common  *  pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	//
	QY_MC	*	pQyMc	=	(  QY_MC  *  )pProcInfo->pQyMc;//QY_GET_GBUF(  );
	if  (  !pQyMc  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "createRtspCliHelp failed, pQyMc is null"  )  );
		#endif
		return  -1;
	}
	//
	STARTUPINFO				si;
	PROCESS_INFORMATION		pi;
	BOOL						bProcessCreated				=		FALSE;
	TCHAR						tmpExeName[MAX_PATH  +  1]	=	_T(  ""  );
	
	if  (  pSt->hProcess_onvifCli  )  return  0;

	memset(  &si,  0,  sizeof(  si  )  );	
	memset(  &pi,  0,  sizeof(  pi  )  );
	
	traceLogA(  (char*)  "Now start qwm "  );	
	memset(  &si,  0,  sizeof(  STARTUPINFO  )  );
	si.cb  =  sizeof(  STARTUPINFO  );
#if  0
	si.dwFlags  =  STARTF_USESHOWWINDOW;	//
	si.wShowWindow  =  SW_HIDE;
#endif
	si.dwFlags  =  STARTF_FORCEOFFFEEDBACK;
	
#define  CONST_subDir_toolsOnvifCli	_T(  "tools\\onvifCli\\"  )
	_sntprintf(  tmpExeName,  mycountof(  tmpExeName  ),  _T(  "%s%s%s"  ),  pQyMc->cfg.installDir,  CONST_subDir_toolsOnvifCli,  _T(  "onvifCli.exe"  )  );	
	//
#ifdef  __DEBUG__
		#if  1
			 traceLog((TCHAR*)  _T(  "TEST: create onvifCli from bin"  )  );
			 _sntprintf(  tmpExeName,  mycountof(  tmpExeName  ),  _T(  "%s%s%s"  ),  pQyMc->cfg.installDir,  _T(  "bin\\"  ),  _T(  "onvifCli.exe"  )  );	
		#endif
#endif
	//
	if  (  tQyQuoteFileName(  tmpExeName,  mycountof(  tmpExeName  )  )  )  goto  errLabel;

	//
	_sntprintf(  tmpExeName,  mycountof(  tmpExeName  ),  _T(  "%s -a%s -tn=%d"  ),  tmpExeName,  pProcInfo->get_appObjPrefix(  ),  pSt->tn_onvifCliPipe  );
	//_sntprintf(  tmpExeName,  mycountof(  tmpExeName  ),  _T(  "%s -t %s"  ),  tmpExeName,  pRtsp->url  );
	
	DWORD  dwCreationFlags;dwCreationFlags = CREATE_NO_WINDOW;
	QMC_debugStatusInfo* pCfg_debugStatusInfo;pCfg_debugStatusInfo = pProcInfo->get_qmc_debugStatusInfo();
	if  (  pCfg_debugStatusInfo
		//&&  pCfg_debugStatusInfo->ucbShowRtspCliControl  
		)  		
	{
			dwCreationFlags  =  0;
	}
	//
	if  (  !CreateProcess(  NULL,  tmpExeName,  NULL,  NULL,  0,  dwCreationFlags,  NULL,  NULL,  &si,  &pi  )  )  goto  errLabel;	 	
	bProcessCreated  =  TRUE;

#ifdef  __DEBUG__
	traceLogA(  (char*)  "CreateProcess %s succeeded,  new processId is %d,  new threadId is %d.",  tmpExeName,  pi.dwProcessId,  pi.dwThreadId  );
	qyShowInfo(  pQyMc->pShowInfoStruct,  CONST_qyShowType_qwmComm,  0,  (char*)"",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "create %s ok"  ),  tmpExeName  );
#endif


	//
	iErr  =  0;

errLabel:
	
	if  (  bProcessCreated  )  {
		 if  (  pi.hThread  )  {  CloseHandle(  pi.hThread  );  pi.hThread  =  NULL;  }
		 if  (  pi.hProcess  )  pSt->hProcess_onvifCli  =  pi.hProcess;
	 }

	if  (  iErr  )  {
		qyShowInfo(  pQyMc->pShowInfoStruct,  CONST_qyShowType_qwmComm,  0,  (char*)"",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "createOnvifCli failed, %s"  ),  tmpExeName  );
	}

	return  iErr;

}


int  closeOnvifCli(  ShareDynBmps_threadProcInfo  *  pRtsp,  QIS_pipe  *  pQisPipe  )
{
	int  iErr  =  -1;
	MC_VAR_common  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	DWORD  dwRet;		 
	//
	int  i;

	if  (  !pRtsp->hProcess_onvifCli  )  return  0;
			
	
	//	
	for  (  i  =  0;  i  <  30;  i  ++  )  {		
		 //
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (char*)"",  pProcInfo->who_showInfo,  0,  _T(  "closeOnvifCli:"  ),  _T(  ""  ),  _T(  "askOnvifCliToQuit,  %d"  ),  i  );
		//
		askOnvifCliToQuit(  pRtsp,  pQisPipe  );
		 //
		 dwRet  =  WaitForSingleObject(  pRtsp->hProcess_onvifCli,  1000  );
		 if  (  dwRet  !=  WAIT_FAILED  &&  dwRet  !=  WAIT_TIMEOUT  )  {
			 CloseHandle(  pRtsp->hProcess_onvifCli  );  pRtsp->hProcess_onvifCli  =  NULL;
			 break;
		 }		
		 if  (  i  >=  1  )  {
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (char*)"",  pProcInfo->who_showInfo,  0,  _T(  "closeOnvifCli:"  ),  _T(  ""  ),  _T(  "too long to wait, terminate onvifCli"  )  );
			 TerminateProcess(  pRtsp->hProcess_onvifCli,  -1  );
		 }
	}

	//	
	if  (  pRtsp->hProcess_onvifCli  )  {	//  即使没回收，也要关闭了
#ifdef  __DEBUG__
			 myMessageBox(  NULL,  _T(  "即使没回收，也要关闭了. 这里没做好，应该onvifCli赶紧退出的"  ),  0,  0  );
#endif
			 //
			 CloseHandle(  pRtsp->hProcess_onvifCli  );  pRtsp->hProcess_onvifCli  =  NULL;		
	}
	 
	iErr  =  0;

errLabel:

	return  iErr;
}




//
 __declspec(  dllexport  )  int  initShareDynBmpsThread(  MC_VAR_common  *  pProcInfo,  HWND  hDlgShareDynBmps,  DLG_shareDynBmps_var  *  pDlgVar,  ShareDynBmps_threadProcInfo  *  p  )
{
	int  iErr  =  -1;
		
	GENERIC_Q_CFG		tmpCfg;
		
	CCtxQmcTmpl  *  pCtx  =  pProcInfo;	
	RW_lock_param  *  pQyMc_rwLockParam  =  pCtx->get_qyMc_rwLockParam(  );
	if  (  !pQyMc_rwLockParam  )  return -1;
	QMC_cfg  *  pQmcCfg  = (  QMC_cfg  *  )pCtx->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;
	GENERIC_Q_CFG  *  p_cfg_shareDynBmpsQ  =  &pQmcCfg->shareDynBmpsQ;//Ctx->get_cfg_transformQ(  );
	if  (  !p_cfg_shareDynBmpsQ  )  return  -1;
	QMC_status  *  pStatus  =  pCtx->get_qmc_status(  );
	if  (  !pStatus  )  return  -1;


	//
	if  (  !hDlgShareDynBmps  ||  !pDlgVar  )  return  -1;
	if  (  !p  )  return  -1;

	//
	p->hDlgShareDynBmps  =  hDlgShareDynBmps;
	p->pDlgVarParam  =  pDlgVar;

		
	//	
	//  2014/0804		
	{
			  memcpy(  &tmpCfg,  p_cfg_shareDynBmpsQ,  sizeof(  tmpCfg  )  );
			  //_sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-%I64u"  ),  tmpCfg.name,  pMgrVar->addr.idInfo.ui64Id  );
			  //_sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-%I64u"  ),  tmpCfg.mutexName_prefix,  pMgrVar->addr.idInfo.ui64Id  );
			  //  
			  if  (  initQyQ2(  &tmpCfg,  pQyMc_rwLockParam,  mycountof(  p->q2.hEvents  ),  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  NULL,  &p->q2  )  )  goto  errLabel;
			  p->bQInited  =  TRUE;			  
	}

		  //		 
		  //  2014/08/04
#if  10
		 {
			 DWORD  dwThreadDaemonId;
			 //
			 if  (  !p->hThread  )  {
				 //
				 p->bQuit  =  FALSE;
				 p->hThread  =  CreateThread(  NULL,  0,  shareDynBmps_threadProc,  p,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
				 if  (  !p->hThread  )  goto  errLabel;					
				 p->dwThreadId  =  dwThreadDaemonId;			
				 if  (  ResumeThread(  p->hThread  )  ==  -1  )  goto  errLabel;	

				 //  2012/03/25
				 InterlockedIncrement(  &pStatus->nThreads_shareDynBmps  );

			 }
		 }
#endif


		  //

		  iErr  =  0;
errLabel:
		  return  iErr;

}


__declspec(  dllexport  )  int  exitShareDynBmsThread(  MC_VAR_common  *  pProcInfo,  ShareDynBmps_threadProcInfo	*	p  )
{
	
	CCtxQmcTmpl  *  pCtx  =  pProcInfo;
	if  (  !pCtx  )  return  -1;
	QMC_status  *  pStatus  =  pCtx->get_qmc_status(  );
	if  (  !pStatus  )  return  -1;
	TCHAR  tBuf[128]  =  _T(  "exitTalkerThread"  );

	//2014/08/04	
	if  (  p->hThread  )  {
		p->bQuit  =  TRUE;			
		//
		SetEvent(  p->q2.hEvents[0]  );
		waitForObject(  &p->hThread,  20000  );		
		//
		if  (  p->hThread  )  {
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  "Failed"  ),  _T(  "WaitFor talkerThread"  )  );
			}
		else  InterlockedDecrement(  &pStatus->nThreads_shareDynBmps  );		 
	}	
	if  (  p->hThread  )  {
			 p->bQuit  =  TRUE;
			 //
			 SetEvent(  p->q2.hEvents[0]  );
			 waitForObject(  &p->hThread,  20000  );
			 //
			 //tmp_getHint_video(  pTask,  p,  tBuf,  mycountof(  tBuf  )  );
			 //
			 if  (  p->hThread  )  {
				 qyExitProcess(  tBuf  );
			 }
			 else  InterlockedDecrement(  &pStatus->nThreads_shareDynBmps  );
		 }	


	
	//  2014/08/04	
	if  (  p->bQInited  )  {
			 exitQyQ2(  &p->q2  );
			 p->bQInited  =  FALSE;		 
	}
	
	return  0;
}


//
 extern "C" DWORD WINAPI shareDynBmps_threadProc( LPVOID lpParameter )
{
	 int										iErr						=	-1;

	 //
	 ShareDynBmps_threadProcInfo			*	pSt							=	(  ShareDynBmps_threadProcInfo  *  )lpParameter;

	 //
	 HWND  hDlgShareDynBmps  =  pSt->hDlgShareDynBmps;
	 if  (  !hDlgShareDynBmps  )  return  -1;
	 DLG_shareDynBmps_var					*	pDlgVar						=	(  DLG_shareDynBmps_var  *  )pSt->pDlgVarParam;
	 if  (  !pDlgVar  )  return  -1;

	 //
	 MC_VAR_isCli							*	pProcInfo  =  QY_GET_procInfo_isCli(  );
	 QY_MC									*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;

	 int										i;


	 //
	 #define		DEFAULT_dwToInMs_talkerProc		1000
	 DWORD										dwToInMs						=	DEFAULT_dwToInMs_talkerProc;

	 DWORD										dwTickCnt_lastVideoData			=	GetTickCount(  );;						// 
	 	 
	 CQyCoInit									coInit;		//  2010/06/07

	 CTX_mc_shareDynBmpsThread					ctx;		//  2014/03/07
	 TCHAR										tBuf[128];

	 CQyMalloc									mallocObj_pMsg;
	 int										len_pMsg						=	sizeof(  RTSP_msg  );
	 void									*	pMsg							=	mallocObj_pMsg.mallocf(  len_pMsg  );
	 if  (  !pMsg  )  return  -1;

	 //
	 memset(  &ctx,  0,  sizeof(  ctx  )  );
	 ctx.pShareDynBmps_threadProcInfo  =  pSt;
	 ctx.common.common.dwThreadId9  =  GetCurrentThreadId(  );

#ifdef  __DEBUG__
	 traceLogA(  (char*)  "mcThreadProc_shareDynBmpsProc enters"  );
#endif
	 	 
	 MACRO_setStep(  pSt->debugStep,  CONST_threadStep_start  );
	 

	 //  2014/05/08
	 _sntprintf(  pSt->debugStep.showInfo.tWhere,  mycountof(  pSt->debugStep.showInfo.tWhere  ),  _T(  "sharedynBmpsThreadProc :"  )  );
	 pSt->debugStep.showInfo.uiStep  =  0;

	 //  2016/07/03
	 pSt->tn_onvifCliPipe  =  getuiNextTranNo(  0,  0,  0  );

	//
	 if  (  pQyMc->appParams.ucbDbgOnvif  )  {
		//
		 pSt->tn_onvifCliPipe  =  64;
		//traceLog((TCHAR*)  _T(  "TEST: tn_rtspCliPipe is set to 10"  )  );
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "-dbgOnvif tn_rtspCliPipe is set to %d"  ),  pSt->tn_onvifCliPipe  );
		showInfo_open0(  0,  0,  tBuf  );
		//
	}


	 //
	 pSt->bRunning  =  TRUE;
	 //  memset(  &pSave->m_var,  0,  sizeof(  pSave->m_var  )  );

#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "Note: "  )  );
#endif

	 //

	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  pSt->debugStep.showInfo.tWhere,  _T(  ""  ),  _T(  "%s starts"  ),  pSt->q2.cfg.name  );

	 #if  10

	 for  (  ;  !pSt->bQuit;  )  {
		  
		  if  (  !dwToInMs  )  {			  
			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning: mcThreadProc_sharedynBmpsProc: dwToInMs %d"  ),  dwToInMs  );
			  dwToInMs  =  DEFAULT_dwToInMs_talkerProc;
		  }

		  //  2009/07/14
		  MACRO_setStep(  pSt->debugStep,  CONST_threadStep_toWait  );

		  //
		  DWORD  dwTickCnt0  =  GetTickCount(  );
		  DWORD  dwTickCnt;
		  DWORD  dwEvt  =  MsgWaitForMultipleObjects(
			  				 pSt->q2.cfg.usCnt_hEvents,		// mycountof(  pSave->hEvents  ),		// Number of events.
							 pSt->q2.hEvents,				// Location of handles.
                             FALSE,										// Wait for all?
                             dwToInMs,									// How long to wait?
                             0  );										// Any message is an 
																		// event.
		  if  (  dwEvt  ==  WAIT_FAILED  )  {
			  iErr  =  -110;
			  goto  errLabel;
		  }
	      //
		  dwTickCnt =   GetTickCount(  );

		  if  (  dwEvt  !=  WAIT_TIMEOUT  )  {
			  dwEvt -= WAIT_OBJECT_0;
			  switch  (  dwEvt  )  {
					  case  0:
						     dwTickCnt_lastVideoData  =  dwTickCnt;		//  audio data received
							 break;
					  case  1:
						     traceLogA(  (char*)  "shareDynBmps: event 1."  );
							 break;
					  default:
						     traceLogA(  (char*)  "unknown event"  );	
							 iErr  =  -120;
		  					 goto  errLabel;
							 break;
			  }
		  }

		  //
		  if  (  isQ2Empty(  &pSt->q2  )  )  {
			  doShareDynBmpsProc_noMsg(  hDlgShareDynBmps,  pDlgVar,  &ctx  );
			  continue;
		  }

		  BOOL  bExists_svp  =  FALSE;
		  for  (  ;  !pSt->bQuit;  )  {

			   //
			   MACRO_setStep(  pSt->debugStep,  CONST_threadStep_toGetMsg  );

			   //
			   unsigned  int  len  =  len_pMsg;
			   if  (  q2GetMsg(  &pSt->q2,  pMsg,  &len,  _T(  "shareDynBmps_threadProc"  )))  break;
			   //
			   OnvifMsg_common  *  pMsgCommon  =  (  OnvifMsg_common  *  )pMsg;
			   //
			   switch  (  pMsgCommon->uiType  )  {
					   case  CONST_qisMsgType_onvif:

						     doShareDynBmpsProc_msg(  hDlgShareDynBmps,  pDlgVar,  pMsgCommon,  len,  &ctx  );			   
							 
						     break;
					   default:
							   showInfo_open0(  0,  0,  _T(  "sharedynBmps_thread: unprocessed onvifMsgType"  )  );
							   break;
			   }
		  
			   //
			   continue;
		  }
	 }
#endif



	 //
	 iErr  =  0;

errLabel:

	 //
	 MACRO_setStep(  pSt->debugStep,  CONST_threadStep_toExit  );
	 pSt->debugStep.iErr_thread  =  iErr;

	 //
	 if  (  isHandleValid(  pSt->hProcess_onvifCli  )  )  {
		 closeOnvifCli(  pSt,  ctx.pQisPipe  );
	 }
	 
	 //	
	 if  (  ctx.pQisPipe  )  {
		qisPipeFree(  &ctx.pQisPipe  );	
	 }
	 
	 //
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s ends."  ),  pSt->q2.cfg.name  );
	 

	 pSt->bRunning  =  FALSE;

	 //  2015/05/09
	 
	 //
	 MACRO_setStep(  pSt->debugStep,  CONST_threadStep_end  );

	 traceLogA(  (char*)  "mcThreadProc_talkerThreadProc %S leaves",  pSt->q2.cfg.name  );

	 return  0;
}


//
int  shareDynBmps_noStoreTask(  ShareDynBmps_threadProcInfo  *  pSdt,  LPCTSTR  hint  )
{
	if  (  !hint  )  hint  =  _T(  ""  );

	//
#if  0
	TCHAR  tBuf[128]  =  _T(  ""  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "tn_task %d. %s"  ),  pSdt->taskInfo.uiTranNo_task,  hint  );
	showInfo2_open(  0,  0,  _T(  "shareDynBmps_noStoreTask"  ),  tBuf  );
#endif

	//pSdt->taskInfo.index_rule  
	memset(  &pSdt->taskInfo,  0,  sizeof(  pSdt->taskInfo  )  );

	return  0;
}


//
//
int  shareDynBmps_storeTask(  DLG_shareDynBmps_var  *  pDlgVar,  int  index_rule,  unsigned  int  tranNo_task    )
{
	ShareDynBmps_threadProcInfo  *  pSt  =  &pDlgVar->shareDynBmpsThreadInfo;
	ShareDynBmpsThread_onvif  *  pOnvif  =  &pSt->onvif;
		

	if  (  pSt->taskInfo.bTaskExists  )  {
		showInfo_open0(  0,  0,  _T(  "shareDynBmps_storeTask failed, task still exits"  )  );
		return  -1;
	}
	//
	ShareDynBmps_onvif_rulesInfo  &  rulesInfo  =  pOnvif->rulesInfo;

	//
	if  (  index_rule  <  0  ||  index_rule  >=  mycountof(  rulesInfo.mems  )  )  return  -1;
	Onvif_rule  *  pRule  =  &rulesInfo.mems[index_rule];

	//
	pSt->taskInfo.rule_beingProcessed  =  *pRule;
	//pSt->taskInfo.index_rule  =  index_rule;
	//
	pSt->taskInfo.uiTranNo_task  =  tranNo_task;
	//
	pSt->taskInfo.dwTickCnt_start  =  GetTickCount(  );
	pSt->taskInfo.bTaskExists  =  TRUE;

	//
#if  0
	TCHAR  tBuf[128]  =  _T(  ""  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "tn_task %d"  ),  tranNo_task  );
	showInfo2_open(  0,  0,  _T(  "shareDynBmps_storeTask"  ),  tBuf  );
#endif

	return  0;
}



//
int  shareDynBmps_qisPipe_onRead(  QIS_pipe  *  pQisPipe,  void  *  pMsg,  unsigned  int  msgLen,  void  *  p0,  void  *  p1  )
{	
	int  iErr  =  -1;
	unsigned  int    dwByte  =  msgLen;
	//
	ShareDynBmps_threadProcInfo  *  pSt  =  (  ShareDynBmps_threadProcInfo  *  )p0;
	//  p1
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	
	//	
	if  (  dwByte  <  sizeof(  OnvifMsg_common  )  )  {		
		showInfo_open0(  0,  0,  _T(  "shareDynBmps_qisPipe_onRead err: read too small bytes < sizeof(  Onvif_msg_common  )"  )  );
		return  -1;		   
	}
	//
	OnvifMsg_common  *  pMsgCommon  =  (  OnvifMsg_common  *  )pMsg;

		  
	if  (  pMsgCommon->uiType  !=  CONST_qisMsgType_onvif  )  return  -1;

	//
	TCHAR  tBuf[128];
	
	//
	if  (  pProcInfo->cfg.debugStatusInfo.ucbShow_onvif  )  {
		switch  (  pMsgCommon->iSubtype  )  {
				case  CONST_onvifMsg_subtype_ipCams:  {
					  OnvifMsg_ipCams  *  pRes  =  (  OnvifMsg_ipCams  *  )pMsg;
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "shareDynBmps_qisPipe_onRead: ipCams, cnt %d, %S. deviceServiceAddr %S. tn_task %d"  ),  (  int  )pRes->usCnt,  pRes->mems[0].urls[0].rtspUrl.url,  pRes->mems[0].deviceServiceAddr,  pRes->uiTranNo );	
					  showInfo_open0(  0,  0,  tBuf  );	
					  }
					  break;
				default:
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "shareDynBmps_qisPipe_onRead: unprocessed onvifMsg.subtype %d, onvifMsg"  ),  pMsgCommon->iSubtype  );	
					  showInfo_open0(  0,  0,  tBuf  );					     
					  break;
		}
	}
	//
#ifdef  __DEBUG__
		#if  0
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "shareDynBmps_qisPipe_onRead: unprocessed onvifMsg.subtype %d, onvifMsg"  ),  pMsgCommon->iSubtype  );	
					  showInfo_open0(  0,  0,  tBuf  );					     
		#endif
#endif
	
	//
	if  (  q2PostMsgAndTrigger(  pMsg,  msgLen,  &pSt->q2,  _T(  "shareDynBmps_qisPipe_onR"  ))) {
		showInfo_open0(  0,  0,  _T(  "shareDynBmps_qisPipe_onRead failed, q2PostMsg failed"  )  );
		goto  errLabel;
	}

	//
	iErr  =  0;
errLabel:

	//
	return  iErr;

}


//
//                     
int  shareDynBmps_chkOnvifRules(  CTX_mc_shareDynBmpsThread  *  pCtx,  ShareDynBmps_onvif_rulesInfo  *  pRulesInfo,  ShareDynBmps_ipDevsInfo  *  pIpDevsInfo  )
{
	int  i;
	int  j;
	int  index;

	//
	if  (  !pRulesInfo  ||  !pIpDevsInfo  )  return  -1;

	//
	ShareDynBmps_threadProcInfo  *  pSt  =  (  ShareDynBmps_threadProcInfo  *  )pCtx->pShareDynBmps_threadProcInfo;
	if  (  !pSt  )  return  -1;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	//
	ShareDynBmps_onvif_rulesInfo  &  rulesInfo  =  *pRulesInfo;
	ShareDynBmps_ipDevsInfo  &  ipDevsInfo  =  *pIpDevsInfo;

	//
	DWORD  dwTickCnt  =  GetTickCount(  );

	//
	BOOL  bChanged  =  FALSE;

	//
	int  cnt  =  0;
	for  (  i  =  0;  i  <  mycountof(  ipDevsInfo.mems  );  i  ++  )  {
		 IP_dev  *  pIpDev  =  &ipDevsInfo.mems[i];
		 //
		 if  (  !pIpDev->rule.usIndex_obj  )  continue;
		 //
		 for  (  j  =  0;  j  <  rulesInfo.usCnt;  j  ++  )  {
			 if  (  rulesInfo.mems[j].usIndex_obj  ==  pIpDev->rule.usIndex_obj  )  break;			  
		 }
		 if  (  j  ==  rulesInfo.usCnt  )  {
			 //  removed
			 memset(  pIpDev,  0,  sizeof(  pIpDev[0]  )  );
			 //
			 bChanged  =  TRUE;

		 }
		 //
		 continue;
	}
	
	//
	for  (  i  =  0;  i  <  rulesInfo.usCnt;  i  ++  )  {
		 Onvif_rule  *  pRule  =  &rulesInfo.mems[i];		
		 //
		 if  (  !pRule->usIndex_obj  )  continue;
				
		 //		
		 IP_dev  *  pIpDev  =  NULL;
		 				
		 //					
		 switch  (  pRule->iOnvifRuleType  )  {
				 case  CONST_onvifRuleType_rtspUrl:
					   //
					   for  (  j  =  0;  j  <  mycountof(  ipDevsInfo.mems  );  j  ++  )  {
						    pIpDev  =  &ipDevsInfo.mems[j];
						    if  (  pIpDev->rule.usIndex_obj  ==  pRule->usIndex_obj  )  break;
					   }
					   if  (  j  ==  mycountof(  ipDevsInfo.mems  )  )  {
						   // add a new					   
						   //
						   for  (  index  =  0;  index  <  mycountof(  ipDevsInfo.mems  );  index  ++  )  {						    
							    pIpDev  =  &ipDevsInfo.mems[index];						    
								if  (  !pIpDev->rule.usIndex_obj  )  break;					  
						   }
						   if  (  index  ==  mycountof(  ipDevsInfo.mems  )  )  {						  
							   showInfo_open0(  0,  0,  _T(  "chkOnvifRules: too many ipDevs, err. skipped"  )  );
							   continue;					  
						   }
						   //						  
						   memset(  pIpDev,  0,  sizeof(  pIpDev[0]  )  );
						   //
						   pIpDev->rule  =  *pRule; 
						   pIpDev->iType  =  CONST_ipDevType_rtspUrl;
						   //						  
						   safeStrnCpy(  pRule->url,  pIpDev->urls[0].rtspUrl.url,  mycountof(  pIpDev->urls[0].rtspUrl.url  )  );						  
						   pIpDev->ucCnt_urls  =  1;						  

						   //  added						  
						   //pIpDev->status.dwLastProcessedTickCnt  =  dwTickCnt;			

						   //
						   bChanged  =  TRUE;

						   //
						   continue;						  
					   }
					   if  (  isSame_onvifRule(  &pIpDev->rule,  pRule  )  )  {
						   continue;
					   }
					   pIpDev->rule  =  *pRule;

					   //
					   bChanged  =  TRUE;

					   break;		

				 case  CONST_onvifRuleType_discovery:
				 case  CONST_onvifRuleType_probe:
					   // do nothing
					   break;

				 default:
						    //
						    showInfo_open0(  0,  0,  _T(  "chkOnvifRules: unprocessed onvifRuleType, err. skipped"  )  );
							break;
			
		 }		
		 //		
		 //		
		 continue;
	}

	//
	if  (  bChanged  )  {
		timestamp_renew(  (  CTX_qm_thread  *  )&pCtx->common,  &ipDevsInfo.ts_ipDevsInfo,_T("shareDynBmps_chkOnvifRules.l832"));
		
		//				
		syncMtCnt_start(  &pSt->onvif.syncMtCnt_ipDevsInfo,  pFuncs->isCliHelp.pf_getuiNextTranNo  );
	}

	//
	return  0;
}




//
 int  doShareDynBmpsProc_noMsg(  HWND  hDlgShareDynBmps,  DLG_shareDynBmps_var  *  pDlgVar,  CTX_mc_shareDynBmpsThread  *  pCtx  )
{
	int  iErr  =  -1;

	//
	DLG_shareDynBmps_var  &  m_var  =  *pDlgVar;
	//int  i;
	ShareDynBmps_threadProcInfo  *  pSt  =  (  ShareDynBmps_threadProcInfo  *  )pCtx->pShareDynBmps_threadProcInfo;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
	TCHAR  tBuf[128];
	
	//
	if  (  pSt->taskInfo.bTaskExists  )  {
		DWORD  dwTickCnt  =  GetTickCount(  );
		//
		int  maxIntervalInMs  =  20000;		//  10000;	//  5000;
		//
		if  (  dwTickCnt  -  pSt->taskInfo.dwTickCnt_start  <  maxIntervalInMs  )  {
			iErr  =  0;  goto  errLabel;
		}
		//
		shareDynBmps_noStoreTask(  pSt,  _T(  "task already exists"  )  );		
		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "shareDynBmps_noMsg: tn_task %d. task too long, cleared"  ),  pSt->taskInfo.uiTranNo_task  );
		showInfo_open0(  0,  0,  tBuf  );
	}
#ifdef  __DEBUG__
		#if  0
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "tn_task %d. task too long, cleared"  ),  pSt->taskInfo.uiTranNo_task  );
			 showInfo2_open(  0,  0,  _T(  "shareDynBmps_noMsg"  ),  tBuf  );
		#endif
#endif

	//
			 DlgShareDynBmps_onvif* pDlgOnvif;pDlgOnvif = &pDlgVar->onvif;

	//
	BOOL  bScanImmediately;bScanImmediately = FALSE;

	//  2016/07/04. 这里将界面线程的RULESINFO复制到线程环境里。
	if  (  !timestamp_isSame(  &pDlgOnvif->rulesInfo.ts_rulesInfo,  &pSt->onvif.rulesInfo.ts_rulesInfo  )  )  {
		//
		{		
			CQySyncCnt  syncCnt;
			if  (  syncMtCnt_rLock(  &pDlgOnvif->syncMtCnt_cur_rulesInfo,  &syncCnt,  _T(  ""  )  )  )  goto  errLabel;	
			//
			pSt->onvif.rulesInfo  =  pDlgOnvif->rulesInfo;
		}
		//
		showInfo_open0(  0,  0,  _T(  "shareDynBmpsThread: refresh rules"  )  );
		//
		shareDynBmps_chkOnvifRules(  pCtx,  &pSt->onvif.rulesInfo,  &pSt->onvif.ipDevsInfo  );
		//
		bScanImmediately  =  TRUE;
	}

	//  2016/07/26
	if  (  pSt->scanCtrl.bScanExists  )  {
		bScanImmediately  =  TRUE;
	}

	//
	//  2016/03/15
	int  nLoops_scan;nLoops_scan = 20;
#ifdef  __DEBUG__
		nLoops_scan  =  10;
#endif
	if  (  bScanImmediately
		||  !(  m_var.nCtrls  %  nLoops_scan  )  )  
	{
		//
		unsigned  short  usCnt  =  min(  mycountof(  pSt->onvif.rulesInfo.mems  ),  pSt->onvif.rulesInfo.usCnt  );
		int  index_rule;
		int  i;

		Onvif_rule  *  pRule  =  NULL;

		//
		for  (  i  =  0;  i  <  usCnt;  i  ++  )  {			
			 //
			 if  (  !pSt->scanCtrl.bScanExists  )  {
				 index_rule  =  0;
				 pSt->scanCtrl.bScanExists  =  TRUE;
				 pSt->scanCtrl.last_index_rule  =  index_rule;
				 }
			 else  {
				   index_rule  =  pSt->scanCtrl.last_index_rule  +  1;			  
				   pSt->scanCtrl.last_index_rule  =  index_rule;
			 }
			 
			 //		
			 if  (  index_rule  >=  usCnt  )  {			
				 pSt->scanCtrl.bScanExists  =  FALSE;
				 iErr  =  0;  goto  errLabel;			  		
			 }
			 		
			 //		
			 //					
			 if  (  pSt->bQuit  )  goto  errLabel;			
		
			 //
			 pRule  =  &pSt->onvif.rulesInfo.mems[index_rule];					
			 //
			 switch  (  pRule->iOnvifRuleType  )  {
					 case  CONST_onvifRuleType_discovery:
					 case  CONST_onvifRuleType_probe:
						   break;
					 case  CONST_onvifRuleType_rtspUrl:						   
					 default:
						    //  skipped
						    continue;
							break;					
			 }

			 //  a scanning rule 
			 break;
		}
		//
		if  (  !pRule  )  {
			//  no need to scan
			pSt->scanCtrl.bScanExists  =  FALSE;
			iErr  =  0;  goto  errLabel;			  		
		}					
					
		//		
		if  (  !pCtx->pQisPipe  )  {
				 pCtx->pQisPipe  =  qisPipeNew(  );
				 //
				 if  (  !pCtx->pQisPipe  )  goto  errLabel;		  
				 //
				 GENERIC_Q_CFG  qCfg  =  {0};
				 TCHAR   pipeName[128]  =  _T(  ""  );
				 //
				 //
				 _sntprintf(  qCfg.name,  mycountof(  qCfg.name  ),  _T(  "qisPipe"  )  );
				 _sntprintf(  qCfg.mutexName_prefix,  mycountof(  qCfg.mutexName_prefix  ),  _T(  "qiqPipe"  )  );
				 qCfg.uiMaxQNodes  =  CONST_uiMaxQNodes_outputQ_256;
		  		 
				 //		  		  
				 M_get_pipeName(  CONST_rtspCliPipePrefix,  pProcInfo->get_appObjPrefix(  ),  pSt->tn_onvifCliPipe,  pipeName  );
			 
				 //
				 PARAM_initQisPipe  param  =  {0};
				 param.pf_onRead  =  shareDynBmps_qisPipe_onRead;
				 param.p0  =  pSt;
				 //
				 if  (  initQisPipe(  &qCfg,  pipeName,  TRUE,  _T(  "qisPipeStarter"  ),  &param,  pCtx->pQisPipe  )  )  {
					 goto  errLabel;
				 }			
		}

			 
		//		
		//  to run onvifCli			
		waitForObject(  &pSt->hProcess_onvifCli,  0  );			
		//				
		if  (  !pQyMc->appParams.ucbDbgOnvif  )  {				 
				 //
				 if  (  !isHandleValid(  pSt->hProcess_onvifCli  )  )  {
					 createOnvifCli(  pSt  );
				 }
				 }
		else  {  //  2016/04/27
			       _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "-dbgOnvif"  )  );			   
				   showInfo_open0(  0,  0,  tBuf  );		 			 
		}
		
		
		//		
		switch  (  pRule->iOnvifRuleType  )  {
					 case  CONST_onvifRuleType_discovery:
						   //
						   if  (  doOnvifRule_discovery(  hDlgShareDynBmps,  pDlgVar,  pCtx,  index_rule  )  )  {
							   goto  errLabel;
						   }
						   break;
					 case  CONST_onvifRuleType_probe:
						   //
						   if  (  doOnvifRule_probe(  hDlgShareDynBmps,  pDlgVar,  pCtx,  index_rule  )  )  {
							   goto  errLabel;
						   }
						   break;
					 default:
							break;			
		}

		//		
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doShareDynBmpsProc_noMsg, start scanning rules[%d], index_obj %d"  ),  index_rule,  pRule->usIndex_obj  );
		if  (  pSt->taskInfo.bTaskExists  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, tn_task %d"  ),  tBuf,  pSt->taskInfo.uiTranNo_task  );
		}
		showInfo_open0(  0,  0,  tBuf  );


	}

	//
	iErr  =  0;
errLabel:
	
	if  (  iErr  )  {
		if  (  pCtx->pQisPipe  )  {
			qisPipeFree(  &pCtx->pQisPipe  );
		}
	}

	return  iErr;
}


//
#if  0
int  get_new_index_obj(  ShareDynBmps_ipDevsInfo  *  pIpDevsInfo  )
{
	int  j;

	//
	int  index_obj;
	//
	for  (  index_obj  =  MAX_usIndex_obj_rtspUrl  +  1;  index_obj  <  MAX_usIndex_obj_rtspUrl  +  1000;  index_obj  ++  )  {
		 //		
		 for  (  j  =  0;  j  <  mycountof(  pIpDevsInfo->mems  );  j  ++  )  {
			  IP_dev  *  pIpDev  =  &pIpDevsInfo->mems[j];						
			  //
			  if  (  !pIpDev->iType  )  continue;
			  //
			  if  (  pIpDev->usIndex_obj  ==  index_obj  )  break;
		 }
		 if  (  j  ==  mycountof(  pIpDevsInfo->mems  )  )  {
			 return  index_obj;
			 break;
		 }
	}
	//
	return  -1;
}
#endif



 //
 int  doShareDynBmpsProc_msg(  HWND  hDlgShareDynBmps,  DLG_shareDynBmps_var  *  pDlgVar,  OnvifMsg_common  *  pMsgCommon,  unsigned  int  msgLen,  CTX_mc_shareDynBmpsThread  *  pCtx  )
{
	int  iErr  =  -1;
	TCHAR  tBuf[128]  =  _T(  ""  );
	ShareDynBmps_threadProcInfo  *  pSt  =  &pDlgVar->shareDynBmpsThreadInfo;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	//
	if  (  pMsgCommon->uiType  !=  CONST_qisMsgType_onvif  )  {
		showInfo_open0(  0,  0,  _T(  "doShareDynBmpsProc_msg failed, msgCommon.type != msg_onvif"  )  );
		return  -1;
	}

	//
	switch  (  pMsgCommon->iSubtype  )  {
			case  CONST_onvifMsg_subtype_ipCams:  {
				  OnvifMsg_ipCams  *  pMsgIpCams  =  (  OnvifMsg_ipCams  *  )pMsgCommon;
				  //
				  if  (  msgLen  >  sizeof(  OnvifMsg_ipCams  )  )  {
					  showInfo_open0(  0,  0,  _T(  "doShareDynBmpsProc_msg failed, ipCams, msgLen too big"  )  );
					  goto  errLabel;
				  }
				  if  (  !pMsgIpCams->ucbResp  )  {
					  showInfo_open0(  0,  0,  _T(  "doShareDynBmpsProc_msg failed, ipCams, ucbResp false"  )  );					  
					  goto  errLabel;
				  }
				  if  (  pMsgIpCams->iErrCode  )  
				  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doShareDynBmpsProc_msg failed, ipCams, iErrCode %d"  ),  pMsgIpCams->iErrCode  );
					  showInfo_open0(  0,  0,  tBuf  );
					  goto  errLabel;
				  }
				  if  (  !pSt->taskInfo.bTaskExists  )  {
					  showInfo_open0(  0,  0,  _T(  "doShareDynBmpsProc_msg failed, ipCams, taskExists false"  )  );					  
					  goto  errLabel;
				  }
				  if  (  pMsgIpCams->uiTranNo  !=  pSt->taskInfo.uiTranNo_task  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doShareDynBmpsProc_msg failed, ipCams, msg.tn %d != task.tn %d"  ),  pMsgIpCams->uiTranNo,  pSt->taskInfo.uiTranNo_task  );					  
					  showInfo_open0(  0,  0,  tBuf  );
					  goto  errLabel;
				  }
				  //
				  #ifdef  __DEBUG__
						  #if  0
	  							_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doShareDynBmpsProc_msg failed, ipCams, msg.tn %d != task.tn %d"  ),  pMsgIpCams->uiTranNo,  pSt->taskInfo.uiTranNo_task  );					  
								showInfo_open0(  0,  0,  tBuf  );
						  #endif
				  #endif
				  //
				  OnvifMsg_ipCams  *  pRes  =  (  OnvifMsg_ipCams  *  )pMsgIpCams;
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doShareDynBmpsProc_msg: ipCams, cnt %d, %S. tn_task %d"  ),  (  int  )pRes->usCnt,  pRes->mems[0].urls[0].rtspUrl.url,  pRes->uiTranNo  );	
				  showInfo_open0(  0,  0,  tBuf  );	
				  
				  //
				  int  rule_usIndex_obj  =  pSt->taskInfo.rule_beingProcessed.usIndex_obj;
				  //
				  BOOL  bChanged  =  FALSE;
				  DWORD  dwTickCnt  =  GetTickCount(  );
				  //
				  IP_dev  *  pIpDev  =  NULL;
				  int  i, j;
				  for  (  i  =  0;  i  <  pRes->usCnt;  i  ++  )  {
					   Onvif_ipCam  *  pIpCam  =  &pRes->mems[i];
					   //
					   for  (  j  =  0;  j  <  mycountof(  pSt->onvif.ipDevsInfo.mems  );  j  ++  )  {
						    pIpDev  =  &pSt->onvif.ipDevsInfo.mems[j];
							//
							if  (  !pIpDev->iType  )  continue;
							if  (  rule_usIndex_obj  !=  pIpDev->rule.usIndex_obj  )  continue;
							//
							if  (  isSame_onvifRule(  &pSt->taskInfo.rule_beingProcessed,  &pIpDev->rule  )  //i  ==  pIpDev->usHelp_subIndex
								&&  !_stricmp(  pIpCam->ip,  pIpDev->ip  )
								&&  !_stricmp(  pIpCam->urls[0].token,  pIpDev->urls[0].token  )
								&&  !_stricmp(  pIpCam->urls[0].rtspUrl.url,  pIpDev->urls[0].rtspUrl.url  )
								&&  !_stricmp(  pIpCam->urls[1].token,  pIpDev->urls[1].token  )
								&&  !_stricmp(  pIpCam->urls[1].rtspUrl.url,  pIpDev->urls[1].rtspUrl.url  )
								&&  !_stricmp(  pIpCam->urls[2].token,  pIpDev->urls[2].token  )
								&&  !_stricmp(  pIpCam->urls[2].rtspUrl.url,  pIpDev->urls[2].rtspUrl.url  )  
								&&  !_stricmp(  pIpCam->deviceServiceAddr,  pIpDev->deviceServiceAddr  )
								)
							{
								break;
							}
					   }
					   //
					   if  (  j  <  mycountof(  pSt->onvif.ipDevsInfo.mems  )  )  {
						   pIpDev->status.dwLastProcessedTickCnt  =  dwTickCnt;
						   continue;
					   }
					   //  new ipDev. add to ipDevsInfo.
					   for  (  j  =  0;  j  <  mycountof(  pSt->onvif.ipDevsInfo.mems  );  j  ++  )  {
						    pIpDev  =  &pSt->onvif.ipDevsInfo.mems[j];
							if  (  !pIpDev->iType  )  break;
					   }
					   //
					   if  (  j  ==  mycountof(  pSt->onvif.ipDevsInfo.mems  )  )  {
						   showInfo_open0(  0,  0,  _T(  "Err: too many ipdevs"  )  );
						   continue;
					   }
					   //
					   int  tmp_index_obj  =  rule_usIndex_obj;  //  get_new_index_obj(  &pSt->onvif.ipDevsInfo  );
					   if  (  tmp_index_obj  <  0  )  {
						   continue;
					   }

					   {
						   CQySyncObj  syncObj;						   
						   //
						   if(  syncMtCnt_wLock_wait(  &pSt->onvif.syncMtCnt_ipDevsInfo,  _T(  ""  ),  &syncObj,  NULL,  _T(  ""  )  )  )  {
							   goto  errLabel;		
						   }

						   //  2016/08/01
						   int  tmp_subIndex  =  0;
						   //
						   if  (  pSt->taskInfo.rule_beingProcessed.iOnvifRuleType  !=  CONST_onvifRuleType_probe  )  {  //  2016/11/11
							   //
							   for  (  tmp_subIndex  =  0;  tmp_subIndex  <  1000;  tmp_subIndex  ++  )  {
								    //
								    int  k;
								    for  (  k  =  0;  k  <  mycountof(  pSt->onvif.ipDevsInfo.mems  );  k  ++  )  {
										 IP_dev  *  pMem  =  &pSt->onvif.ipDevsInfo.mems[k];
										 if  (  !pMem->iType  )  continue;
										 if  (  pMem->rule.usIndex_obj  !=  rule_usIndex_obj  )  continue;
										 //
										 if  (  pMem->usHelp_subIndex  ==  tmp_subIndex  )  break;
									}
									if  (  k  <  mycountof(  pSt->onvif.ipDevsInfo.mems  )  )  continue;
									//
									break;
							   }
						   //
						   }

						   //
						   pIpDev->rule  =  pSt->taskInfo.rule_beingProcessed;
						   //
						   pIpDev->iType  =  CONST_ipDevType_ipCam;
						   //
						   pIpDev->usHelp_subIndex  =  tmp_subIndex;	//  2016/08/01	//  i;	//  i  +  1;
						   //
						   pIpDev->urls[0]  =  pIpCam->urls[0];
						   pIpDev->urls[1]  =  pIpCam->urls[1];
						   pIpDev->urls[2]  =  pIpCam->urls[2];
						   //
						   safeStrnCpy(  pIpCam->deviceServiceAddr,  pIpDev->deviceServiceAddr,  mycountof(  pIpDev->deviceServiceAddr  )  );
						   //
						   //  to  calc cnt_urls
						   pIpDev->ucCnt_urls  =  0;
						   for  (  j  =  0;  j  <  mycountof(  pIpDev->urls  );  j  ++  )  {
							   if  (  pIpDev->urls[j].rtspUrl.url[0]  )  pIpDev->ucCnt_urls  ++  ;
						   }
						   //
						   pIpDev->status.dwLastProcessedTickCnt  =  dwTickCnt;
					   
					   }
					   //
					   bChanged  =  TRUE;
					   //
					   continue;
				  }

				  //
				  for  (  j  =  0;  j  <  mycountof(  pSt->onvif.ipDevsInfo.mems  );  j  ++  )  {
					   pIpDev  =  &pSt->onvif.ipDevsInfo.mems[j];
					   if  (  !pIpDev->iType  )  continue;					   
					   if  (  rule_usIndex_obj  !=  pIpDev->rule.usIndex_obj  )  continue;
					   //
					   int  iDiffInMs  =  dwTickCnt  -  pIpDev->status.dwLastProcessedTickCnt;			   

					   //
					   if  (  !iDiffInMs  )  continue;
					   
					   //
					   BOOL  bNeedRemove  =  FALSE;
					   


					   //
					   if  (  pSt->taskInfo.rule_beingProcessed.iOnvifRuleType  ==  CONST_onvifRuleType_discovery  )  {
						   //int  maxElapseInMs  =  60  *  1000;
						   //
						   //if  (  abs(  iDiffInMs  )  >  maxElapseInMs  )  
						   {
							   bNeedRemove  =  TRUE;
							   //
						   }
						   //
						   }
					   else  if  (  pIpDev->status.dwLastProcessedTickCnt  !=  dwTickCnt  )  {
							     bNeedRemove  =  TRUE;
					   }
					   //
					   if  (  bNeedRemove  )
					   {
						   CQySyncObj  syncObj;						   
						   //
						   if(  syncMtCnt_wLock_wait(  &pSt->onvif.syncMtCnt_ipDevsInfo,  _T(  ""  ),  &syncObj,  NULL,  _T(  ""  )  )  )  {
							   goto  errLabel;		
						   }
						   
						   //					   	
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "ipDev[%d] needs be removed, elapseInMs %d"  ),  j,  iDiffInMs  );						
						   showInfo_open0(  0,  _T(  "shareDynBmps_msg"  ),  tBuf  );
						   //
						   #ifdef  __DEBUG__
								   traceLog((TCHAR*)  _T(  "ipdev[%d] removed"  ),  j  );
						   #endif
						   //
						   memset(  pIpDev,  0,  sizeof(  pIpDev[0]  )  );

						   //
						   bChanged  =  TRUE;
					   }
				  }

				  //
				  if  (  bChanged  )  {
					  timestamp_renew(  (  CTX_qm_thread  *  )&pCtx->common,  &pSt->onvif.ipDevsInfo.ts_ipDevsInfo,_T("doShareDynBmpsProc_msg.l1311"));
					  //		
					  syncMtCnt_start(  &pSt->onvif.syncMtCnt_ipDevsInfo,  pFuncs->isCliHelp.pf_getuiNextTranNo  );
				  }

				  //  2016/07/25
				  shareDynBmps_noStoreTask(  pSt,  _T(  "resp. ipCams"  )  );


				  }
				  break;
			case  CONST_onvifMsg_subtype_ptz:  {
				  OnvifMsg_ptz  *  pMsgPtz  =  (  OnvifMsg_ptz  *  )pMsgCommon;
				  //
				  qisPipe_writeMsg(  pMsgPtz,  sizeof(  OnvifMsg_ptz  ),  pCtx->pQisPipe  );

				  }
				  break;

			default:  {
				      showInfo_open0(  0,  0,  _T(  "doShareDynBmpsProc_msg: unprocessed onvifMsg"  )  );
					  break;
			}
	}

	iErr  =  0;
errLabel:

	return  iErr;
}



 ////////////////////////////
 int  doOnvifRule_discovery(  HWND  hDlgShareDynBmps,  DLG_shareDynBmps_var  *  pDlgVar,  CTX_mc_shareDynBmpsThread  *  pCtx,  int  index_rule  ) 
 {
	 int  iErr  =  -1;
	 int  i;
	 ShareDynBmps_threadProcInfo  *  pSt  =  (  ShareDynBmps_threadProcInfo  *  )pCtx->pShareDynBmps_threadProcInfo;
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	 //
	 //for  (  i  =  0;  i  <  1000;  i  ++  )

	
	//
	if  (  pSt->bQuit  )  goto  errLabel;

	//
	OnvifMsg_discovery msg;
	memset(&msg,0,sizeof(msg));
	msg.uiType  =  CONST_qisMsgType_onvif;
	msg.iSubtype  =  CONST_onvifMsg_subtype_discovery;
	msg.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSt->status.lTranNo_doOnvifRule  );
	//
	if  (  pProcInfo->cfg.debugStatusInfo.ucbShow_onvif  )  msg.ucbDbg  =  TRUE;
	
	//
	if  (  qisPipe_writeMsg(  &msg,  sizeof(  msg  ),  pCtx->pQisPipe  )  )  {
		goto  errLabel;
	}
		
	//
	shareDynBmps_storeTask(  pDlgVar,  index_rule,  msg.uiTranNo  );

	 iErr  =  0;
errLabel:
	 return  iErr;
 }


 //
  int  doOnvifRule_probe(  HWND  hDlgShareDynBmps,  DLG_shareDynBmps_var  *  pDlgVar,  CTX_mc_shareDynBmpsThread  *  pCtx,  int  index_rule  ) 
 {
	 int  iErr  =  -1;
	 int  i;
	 ShareDynBmps_threadProcInfo  *  pSt  =  (  ShareDynBmps_threadProcInfo  *  )pCtx->pShareDynBmps_threadProcInfo;
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	
	//
	if  (  pSt->bQuit  )  goto  errLabel;

	//
	OnvifMsg_probe msg;
	memset(&msg,0,sizeof(msg));
	msg.uiType  =  CONST_qisMsgType_onvif;
	msg.iSubtype  =  CONST_onvifMsg_subtype_probe;
	msg.uiTranNo  =  getuiNextTranNo(  0,  0,  &pSt->status.lTranNo_doOnvifRule  );
	//
	if  (  pProcInfo->cfg.debugStatusInfo.ucbShow_onvif  )  msg.ucbDbg  =  TRUE;
	
	//
	if  (  index_rule  <  0  ||  index_rule  >=  mycountof(  pSt->onvif.rulesInfo.mems  )  )  goto  errLabel;
	Onvif_rule* pRule;pRule = &pSt->onvif.rulesInfo.mems[index_rule];

	//
	char* pUri;pUri = pRule->url;
	safeStrnCpy(  pUri,  msg.uri,  mycountof(  msg.uri  )  );


	//
	if  (  qisPipe_writeMsg(  &msg,  sizeof(  msg  ),  pCtx->pQisPipe  )  )  {
		goto  errLabel;
	}
		
	//
	shareDynBmps_storeTask(  pDlgVar,  index_rule,  msg.uiTranNo  );

	 iErr  =  0;
errLabel:
	 return  iErr;
 }


