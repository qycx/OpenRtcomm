

#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	<time.h>
#include	<stddef.h>
#include	<ShellAPI.h>

#include	"qymcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"

#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"


#include	"tmpCeLib.h"
#include	"qyWnd.h"

#include	"qyRtcCommProc.h"
#ifndef  __WINCE__
#include	"dlgVideosProc.h"
#endif
#include	<assert.h>
#include	"qmcDxSurfacePublic.h"
#ifndef  __WINCE__
#include	"qmcConferenceWall.h"
#include	"isCliHelpPublic.h"
#endif
#include	"qmcCmdProc.h"

#include	"policyAvParams.h"

#include	"dlgTalkProc.h"
#include	"qmcSharePublic.h"

#include	"DlgWalls.h"

#include	"gpsCommProc.h"
#include	"qmcGpsProc.h"


#include	"qmcVWall.h"
#include	"dlgDesktopsMonProc.h"

#include	"sp.h"
#include	"myDb.h"
#include	"isCliHelpPublic.h"

#include	"imgProcessPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"dlgMsgToolProc.h"
#include	"qmcVideoCapture_rtsp.h"
#include	"qmcDynBmp.h"

#include	"qyCusResTemp.h"
#include	"qmcTaskInfo.h"
#include	"syncMtCnt.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliD3dPublic.h"

#include	"ctxmcThread.h"

//
 extern "C" DWORD WINAPI mcThreadProc_talkerProc( LPVOID lpParameter );
 int  doTalkerProc_noMsg(  CTX_mc_talkerThread  *  pCtx,  HWND  hDlgTalk_mgr,  DLG_TALK_var  *  pMgrVar  );
 int  doTalkerProc_msg(  CTX_mc_talkerThread  *  pCtx,  HWND  hDlgTalk_mgr,  DLG_TALK_var  *  pMgrVar,  void  *  pMsg  );
 //
 




//
 __declspec(  dllexport  )  int  initTalkerThread(  MC_VAR_common  *  pProcInfo,  HWND  hDlgTalk_mgr,  DLG_TALK_var  *  pMgrVar,  TALKER_threadProcInfo  *  p  )
{
	int  iErr  =  -1;
		
	GENERIC_Q_CFG		tmpCfg;
		
	CCtxQmcTmpl  *  pCtx  =  pProcInfo;	
	RW_lock_param  *  pQyMc_rwLockParam  =  pCtx->get_qyMc_rwLockParam(  );
	if  (  !pQyMc_rwLockParam  )  return -1;
	QMC_cfg  *  pQmcCfg  = (  QMC_cfg  *  )pCtx->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;
	GENERIC_Q_CFG  *  p_cfg_talkerThreadQ  =  &pQmcCfg->talkerThreadQ;//Ctx->get_cfg_transformQ(  );
	if  (  !p_cfg_talkerThreadQ  )  return  -1;
	QMC_status  *  pStatus  =  pCtx->get_qmc_status(  );
	if  (  !pStatus  )  return  -1;


	//
	if  (  !hDlgTalk_mgr  ||  !pMgrVar  )  return  -1;
	if  (  !p  )  return  -1;

	//
	p->hDlgTalk_mgr  =  hDlgTalk_mgr;
	p->pMgrVarParam  =  pMgrVar;

		
	//	
	//  2014/0804		
	{
			  memcpy(  &tmpCfg,  p_cfg_talkerThreadQ,  sizeof(  tmpCfg  )  );
			  _sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-%I64u"  ),  tmpCfg.name,  pMgrVar->addr.idInfo.ui64Id  );
			  _sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-%I64u"  ),  tmpCfg.mutexName_prefix,  pMgrVar->addr.idInfo.ui64Id  );
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
				 p->hThread  =  CreateThread(  NULL,  0,  mcThreadProc_talkerProc,  p,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
				 if  (  !p->hThread  )  goto  errLabel;					
				 p->dwThreadId  =  dwThreadDaemonId;			
				 if  (  ResumeThread(  p->hThread  )  ==  -1  )  goto  errLabel;	

				 //  2012/03/25
				 InterlockedIncrement(  &pStatus->nThreads_talkerProc  );

			 }
		 }
#endif


		  //

		  iErr  =  0;
errLabel:
		  return  iErr;

}


 //
 __declspec(  dllexport  )  int  exitTalkerThread(  MC_VAR_common  *  pProcInfo,  TALKER_threadProcInfo	*	p  )
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
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  "Failed"  ),  _T(  "WaitFor talkerThread"  )  );
			}
		else  InterlockedDecrement(  &pStatus->nThreads_talkerProc  );		 
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
			 else  InterlockedDecrement(  &pStatus->nThreads_talkerProc  );
		 }	


	
	//  2014/08/04	
	if  (  p->bQInited  )  {
			 exitQyQ2(  &p->q2  );
			 p->bQInited  =  FALSE;		 
	}
	
	return  0;
}


//
 extern "C" DWORD WINAPI mcThreadProc_talkerProc( LPVOID lpParameter )
{
	 int								iErr						=	-1;

	 //
	 TALKER_threadProcInfo			*	pTpi						=	(  TALKER_threadProcInfo  *  )lpParameter;

	 //
	 HWND  hDlgTalk_mgr  =  pTpi->hDlgTalk_mgr;
	 if  (  !hDlgTalk_mgr  )  return  -1;
	 DLG_TALK_var					*	pMgrVar						=	(  DLG_TALK_var  *  )pTpi->pMgrVarParam;
	 if  (  !pMgrVar  )  return  -1;
	 if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
		 return  -1;
	 }




	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 QY_MC							*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;
	 //  int								i;

	 int								i;


	 //
	 #define		DEFAULT_dwToInMs_talkerProc		1000
	 DWORD								dwToInMs						=	DEFAULT_dwToInMs_talkerProc;

	 DWORD								dwTickCnt_lastVideoData			=	GetTickCount(  );;						// 




	 BOOL								bPktsRedirected;

	 CQyCoInit							coInit;		//  2010/06/07

	 CTX_mc_talkerThread				ctx;		//  2014/03/07

	 //
	 memset(  &ctx,  0,  sizeof(  ctx  )  );
	 ctx.common.common.dwThreadId9  =  GetCurrentThreadId(  );

#ifdef  __DEBUG__
	 traceLogA(  "mcThreadProc_talkerProc enters"  );
#endif
	 
	 //
	 MACRO_setStep(  pTpi->debugStep,  CONST_threadStep_start  );
	 

	 //  2014/05/08
	 _sntprintf(  pTpi->debugStep.showInfo.tWhere,  mycountof(  pTpi->debugStep.showInfo.tWhere  ),  _T(  "talkerThreadProc %I64u:"  ),  pMgrVar->addr.idInfo.ui64Id  );
	 pTpi->debugStep.showInfo.uiStep  =  0;

	 //

	 //
	 pTpi->bRunning  =  TRUE;
	 //  memset(  &pSave->m_var,  0,  sizeof(  pSave->m_var  )  );

#ifdef  __DEBUG__
		traceLog(  _T(  "Note: "  )  );
#endif

	 //

	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  pTpi->debugStep.showInfo.tWhere,  _T(  ""  ),  _T(  "%s starts"  ),  pTpi->q2.cfg.name  );

	 #if  10

	 for  (  ;  !pTpi->bQuit;  )  {
		  
		  if  (  !dwToInMs  )  {			  
			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning: mcThreadProc_talkerProc: dwToInMs %d"  ),  dwToInMs  );
			  dwToInMs  =  DEFAULT_dwToInMs_talkerProc;
		  }

		  //  2009/07/14
		  MACRO_setStep(  pTpi->debugStep,  CONST_threadStep_toWait  );

		  //
		  DWORD  dwTickCnt0  =  GetTickCount(  );
		  DWORD  dwTickCnt;
		  DWORD  dwEvt  =  MsgWaitForMultipleObjects(
			  				 pTpi->q2.cfg.usCnt_hEvents,		// mycountof(  pSave->hEvents  ),		// Number of events.
							 pTpi->q2.hEvents,				// Location of handles.
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
						     traceLogA(  "transformVideo: event 1."  );
							 break;
					  default:
						     traceLogA(  "unknown event"  );	
							 iErr  =  -120;
		  					 goto  errLabel;
							 break;
			  }
		  }

		  //
		  if  (  isQ2Empty(  &pTpi->q2  )  )  {
			  doTalkerProc_noMsg(  &ctx,  hDlgTalk_mgr,  pMgrVar  );
			  continue;
		  }

		  BOOL  bExists_svp  =  FALSE;
		  for  (  ;  !pTpi->bQuit;  )  {

			   //
			   MACRO_setStep(  pTpi->debugStep,  CONST_threadStep_toGetMsg  );


			   doTalkerProc_msg(  &ctx,  hDlgTalk_mgr,  pMgrVar,  NULL  );
			   //if  (  bExists_svp  )  continue;

			   if  (  isQ2Empty(  &pTpi->q2  )  )  break;

		  }
	 }
#endif


	 //
	 iErr  =  0;

errLabel:

	 //
	 MACRO_setStep(  pTpi->debugStep,  CONST_threadStep_toExit  );
	 pTpi->debugStep.iErr_thread  =  iErr;

#if  0
	 //  2014/03/04
	qdcExitSplInfo(  &g_splInfo  );
	bInited_splInfo  =  FALSE;
#endif

	 //
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s ends."  ),  pTpi->q2.cfg.name  );
	 

	 pTpi->bRunning  =  FALSE;

	 //  2015/05/09
	 
	 //
	 MACRO_setStep(  pTpi->debugStep,  CONST_threadStep_end  );

	 traceLogA(  "mcThreadProc_talkerThreadProc %S leaves",  pTpi->q2.cfg.name  );

	 return  0;
}





//
 //
 int  confStarter_chkBgWall(  CTX_mc_talkerThread  *  pCtx,  HWND  hDlgTalk,  DLG_TALK_var  *  pm_var  )
{
	int		iErr	=	-1;
	DLG_TALK_var  &  m_var  =  *pm_var;

	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	CQySyncCnt			syncCnt;
	PARAM_task_info		param;
	int					i;
	int					tmpIndex;
	

	//
	if  (  !isTalkerShadowMgr(  pm_var->addr  )  )  return  -1;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pm_var->pShadowInfo;

	//
#ifdef  __DEBUG__
#if  10
	if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
		traceLog(_T("confStart_chkBgWall called"));
	}
#endif
#endif

	//
	//if  (  !pm_var->m_layout.ucbShowBgWall_starter  )  		
	if  (  !pShadowMgr->bgWall.bgWallCfg.useBgWall  &&  !pShadowMgr->bgWall.bgWallCfg.ucbAddBgWallToConf  )  
	{
		return  confStarter_stopConfWall(  hDlgTalk,  pm_var  );
	}

	//
	if  (  syncToGetTaskInfo(  &m_var,  syncCnt,  param  )  )  goto  errLabel;

	QMC_taskData_conf  *  pTaskData  =  param.pTaskData;

	if  (  !pTaskData->bInited  )  {
		goto  errLabel;
	}


	//
	pTaskData->usMaxToDisplay  =  pShadowMgr->bgWall.bgWallCfg.bgWallLayoutCfg.usRows_bg  *  pShadowMgr->bgWall.bgWallCfg.bgWallLayoutCfg.usCols_bg;
	pTaskData->usMaxToDisplay  =  min(  pTaskData->usCnt_pMems,  pTaskData->usMaxToDisplay  );
	pTaskData->usPollingIntervalInS  =  pShadowMgr->bgWall.bgWallCfg.usPollingIntervalInS;

	//
	if  (  !pTaskData->usMaxToDisplay  )  {
		showInfo_open0(  0,  0,  _T(  "confStarter_chkBgWall failed: usMaxToDisplay is 0"  )  );
		goto  errLabel;
	}
	if  (  !pTaskData->usPollingIntervalInS  )  {
		pTaskData->usPollingIntervalInS  =  DEFAULT_usPollingIntervalInS;
		showInfo_open0(  0,  0,  _T(  "confStarter_chkBgWall: usPollingIntervalInS 0, err, set to be default 10"  )  );
	}

	//
	BOOL	bNeedChk  =  FALSE;

	//
	DWORD  dwTickCnt_now  =  GetTickCount(  );
	if  (  dwTickCnt_now  -  pTaskData->cur_toDisplay.dwTickCnt_adjustWhichToBeDisplayed  >=  pTaskData->usPollingIntervalInS  *  1000  )  {
		pTaskData->cur_toDisplay.dwTickCnt_adjustWhichToBeDisplayed  =  dwTickCnt_now;
		
		//
		#ifdef  __DEBUG__
				//traceLog(  _T(  "confStart_chkBgWall: time to adjust"  )  );
		#endif
		
		//
		unsigned  short  usStartMemIndex  =  pTaskData->cur_toDisplay.usStartMemIndex  +  pTaskData->cur_toDisplay.usCnt;
		unsigned  short  usCnt  =  0;

		//
		unsigned  short  usCnt_grpMems  =  pShadowMgr->confCtrl.grpConfCtrl.usCnt;
		if  (  !usCnt_grpMems  )  {
			goto  errLabel;
		}
		if  (  usStartMemIndex  >=  usCnt_grpMems  )  {
			usStartMemIndex  =  usStartMemIndex  %  usCnt_grpMems;
		}
		usCnt  =  min(  pTaskData->usMaxToDisplay,  usCnt_grpMems  -  usStartMemIndex  );

		//
		if  (  usStartMemIndex  !=  pTaskData->cur_toDisplay.usStartMemIndex  ||  usCnt  !=  pTaskData->cur_toDisplay.usCnt  )  {
			
			//
			#ifdef  __DEBUG__
					traceLog(  _T(  "confStarter_chkBgWall: adjusted----------------------------------------------------------------"  )  );
			#endif

			//
			for  (  i  =  0;  i  <  pTaskData->cur_toDisplay.usCnt;  i  ++  )  {
				 tmpIndex  =  i;
				 if  (  tmpIndex  >=  pTaskData->usCnt_pMems  )  break;
				 //
				 CONF_mem  *  pConfWallMem  =  &pTaskData->pMems[tmpIndex];
				 //
				 if  (  i  >=  mycountof(  m_var.av.bgWall.mems  )  )  goto  errLabel;
				 myZONE  *  pZone  =  &m_var.av.bgWall.mems[i];
				 memset(  &pZone->rule,  0,  sizeof(  pZone->rule  )  );
				 timestamp_renew(  &pCtx->common.common,  &pZone->ts_zone,_T("confStarter_chkBgWall.l477"));
				 				
				 //				
				 if  (  !pConfWallMem->view.mem.talkerDynBmp.taskInfo.iTaskId  )  continue;

						
				 MSGR_ADDR  addr;				
				 memset(  &addr,  0,  sizeof(  addr  )  );								 
				 addr.idInfo.ui64Id  =  pConfWallMem->idInfo.ui64Id;
				 if  (  !addr.idInfo.ui64Id  ||  addr.idInfo.ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  )  {
					 continue;
				 }
				 //
				 QY_MESSENGER_ID  idInfo_grp_related;
				 idInfo_grp_related.ui64Id = 0;								
				 //
				 BOOL  bOutputDirectly  =  TRUE;				
				 LPCTSTR  tmppHint  =  _T(  "starter_chkBgWall: "  ); 
				 procSendTaskProcReq(  m_var.pMisCnt,  CONST_qyCmd_sendMedia,  CONST_imOp_stopSending,  0,  0,  0,  idInfo_grp_related, pConfWallMem->view.mem.talkerDynBmp.taskInfo.iTaskId,  0,  &pConfWallMem->dynBmps.mem,  CONST_channelType_media,  bOutputDirectly,  tmppHint,  &addr  );  

				 //
				 cleanTalkerRuleTask(  hDlgTalk,  &pConfWallMem->view.mem.talkerDynBmp,  FALSE,  _T(  ""  )  );
			}

			//
			pTaskData->cur_toDisplay.usStartMemIndex  =  usStartMemIndex;
			pTaskData->cur_toDisplay.usCnt  =  usCnt;

			
			//  2016/03/20
			//m_var.d3d_talkerData_cfg.dwModifiedTickCnt_bgWallLayout  =  GetTickCount(  );

			//
			qmcApplyForChkingTasks_gui(  pQyMc  );

			//
			bNeedChk  =  TRUE;
		}

		//  2017/10/05
		//
		for  (  i  =  0;  i  <  pTaskData->cur_toDisplay.usCnt;  i  ++  )  {
			 tmpIndex  =  pTaskData->cur_toDisplay.usStartMemIndex  +  i;
			 if  (  tmpIndex  >=  pShadowMgr->confCtrl.grpConfCtrl.usCnt  )  break;
			 //
			 if  (  i  >=  pTaskData->usCnt_pMems  )  goto  errLabel;
			 CONF_mem  *  pConfMem  =  &pTaskData->pMems[i];
			 //
			 pConfMem->idInfo.ui64Id  =  pShadowMgr->confCtrl.grpConfCtrl.pMems[tmpIndex].idInfo.ui64Id;
			 //
			 if  (  i  >=  mycountof(  m_var.av.bgWall.mems  )  )  goto  errLabel;
			 myZONE  *  pZone  =  &m_var.av.bgWall.mems[i];
			 //
			 VW_ruleU  rule  =  {0};
			 rule.common.uiType  =  CONST_vwRuleType_bgMemVideo;
			 rule.bgMemVideo.idInfo.ui64Id  =  pConfMem->idInfo.ui64Id;
			 //
			 if  (  memcmp(  &rule,  &pZone->rule,  sizeof(  rule  )  )  )  {
				 pZone->rule  =  rule;
				 timestamp_renew(  &pCtx->common.common,  &pZone->ts_zone,_T("confStarter_chkBgWall.l533"));

				 //
				 bNeedChk  =  TRUE;
			 }
		}

		//
		if  (  bNeedChk  )  {
			//
			//  2016/03/15
			PostMessage(  hDlgTalk,  CONST_qyWm_postComm,  CONST_qyWmParam_invalidate_bgWall,  0  );
		}
	}
	
	//
	if  (  !pTaskData->cur_toDisplay.usCnt  ||  pTaskData->cur_toDisplay.usCnt  >  pTaskData->usCnt_pMems  )  goto  errLabel;

	if  (  dwTickCnt_now  -  pTaskData->cur_toDisplay.dwTickCnt_chkIfActive  >  5000  )  {
		bNeedChk  =  TRUE;
	}

	//
#if  10
	if  (  bNeedChk  )  {
		pTaskData->cur_toDisplay.dwTickCnt_chkIfActive  =  dwTickCnt_now;

		//
		for  (  i  =  0;  i  <  pTaskData->cur_toDisplay.usCnt;  i  ++  )  {
			 //tmpIndex  =  pTaskData->cur_toDisplay.usStartMemIndex  +  i;
			 //if  (  tmpIndex  >=  pTaskData->usCnt_pMems  )  break;
			 //
			 if  (  i  >=  pTaskData->usCnt_pMems  )  goto  errLabel;
			 CONF_mem  *  pConfWallMem  =  &pTaskData->pMems[i];
			 //
			 if  (  i  >=  mycountof(  m_var.av.bgWall.mems  )  )  goto  errLabel;
			 myZONE  *  pZone  =  &m_var.av.bgWall.mems[i];

			 //
			 #ifdef  __DEBUG__
					 traceLog(  _T(  "process confWallMem %d, index_toDisplay %d"  ),  (  int  )i,  i  );
			 #endif
			 //
			 procBgWallMem(  hDlgTalk,  pm_var,  pConfWallMem,  pZone  );	
		}

	
	}
#endif


	iErr  =  0;
errLabel:
	return  iErr;
}


//
 int  doTalkerProc_noMsg(  CTX_mc_talkerThread  *  pCtx,  HWND  hDlgTalk_mgr,  DLG_TALK_var  *  pMgrVar  )
{
	int  iErr  =  -1;

	//
	DLG_TALK_var  &  m_var  =  *pMgrVar;

	//
	//  2016/03/15
	if  (  !(  m_var.loopCtrl_timer  %  10  )  )  {
		if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
			CQySyncCnt  syncCnt_taskInfo;
			if  (  !syncMtCnt_rLock(  &pMgrVar->av.syncMtCnt_taskInfo,  &syncCnt_taskInfo,  _T(  "dlTalkerProc_noMsg"  )  )  )  {

				//  2014/09/25
				if  (  m_var.av.taskInfo.bTaskExists  &&  m_var.av.taskInfo.ucbStarter  &&  m_var.av.taskInfo.ucbVideoConference  )  {
					confStarter_chkBgWall(  pCtx,  hDlgTalk_mgr,  &m_var  );
				}
			}

		}
	}

	//
	iErr  =  0;
errLabel:
	
	return  iErr;
}



 //
 int  doTalkerProc_msg(  CTX_mc_talkerThread  *  pCtx,  HWND  hDlgTalk_mgr,  DLG_TALK_var  *  pMgrVar,  void  *  pMsg  )
{
	showInfo_open0(  0,  0,  _T(  "doTalkerProc_msg"  )  );

	return  0;
}