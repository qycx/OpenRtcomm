
#include	"stdafx.h"

#include	<time.h>
#include	<stddef.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qmcAcm.h"
//#include	"qyAvRecordPublic.h" 
#include	"qyVk.h"
#include	"qyMcMainInternalBak.h"
#include	<assert.h>
#include	"qmcDmoPublic.h"
#include	"tmpCeLib.h"

#include	"myDb.h"
 
//  
//#include	"isCliHelpPublic.h"
#include	"saveAvProc_open.h"
#include	"qmcCfg.h"
//#include	"ctxQmc.h"



//  2015/10/07
//
 BOOL  isPkt_sharedTex(  QY_TRANSFORM  *  pTransform  )
{
	BOOL  bRet  =  FALSE;
	CCtxQyMc* pQyMc = g_pQyMc;


	//
 	if  (  pTransform->video.tv.compressor.common.ucCompressors  !=  CONST_videoCompressors_vcm
		&&  pTransform->video.tv.compressor.common.ucCompressors  !=  CONST_videoCompressors_dmo
		&&  pTransform->video.u.qoi.myQoi.common.var.usPktResType_dec  ==  CONST_pktResType_sharedTex  )
	{
		bRet  =  TRUE;
	}

	//



	//
	return  bRet;
 }




//
 int  tmp_getHint_video(  PROC_TASK_AV  *  pTask,  QY_TRANSFORM  *  p,  TCHAR  *  tBuf,  unsigned  int  cnt  )
{
	char	buf[128]	=	"";

	if  (  !cnt  )  return  -1;

	_sntprintf(  tBuf,  cnt,  _T(  "stopTransformThreads: "  )  );
	if  (  p->pAddr_logicalPeer  )  _sntprintf(  tBuf,  cnt,  _T(  "%s %I64u."  ),  tBuf,  p->pAddr_logicalPeer->idInfo.ui64Id  );
	iFourcc2Str(  p->video.tv.vh_compress.bih.biCompression,  buf,  mycountof(  buf  )  );
	_sntprintf(  tBuf,  cnt,  _T(  "%s wait for video thread, %I64u, %d, %S"  ),  tBuf,  p->video.idInfo.ui64Id,  p->video.tv.compressor.common.ucCompressors,  buf  );
	_sntprintf(  tBuf,  cnt,  _T(  "%s nStep %d, elapse %dms"  ),  tBuf,  p->video.debugStep.nStep_debug,  GetTickCount(  )  -  p->video.debugStep.dwTickCnt_step_debug  );
	//		
	if  (  p->video.tv.compressor.common.ucCompressors  ==  CONST_videoCompressors_dmo  )  {	
		_sntprintf(  tBuf,  cnt,  _T(  "%s, fg: elapse_quit %dms, nStep %d, elapse %dms "  ),  tBuf,  GetTickCount(  )  -  p->video.debugStep.fg.dwTickCnt_startToQuit,  p->video.debugStep.fg.FillBuffer.nStep_debug,  GetTickCount(  )  -  p->video.debugStep.fg.FillBuffer.dwTickCnt_step_debug  );
		_sntprintf(  tBuf,  cnt,  _T(  "%s, bInited %d, bStarted %d, hr_start %d, fs_start %d, bRun %d, hr_run %d, hr_stop %d, fs_stop %d"  ),  tBuf,  p->video.debugStep.fg.bInited,  p->video.debugStep.fg.bStarted,  p->video.debugStep.fg.hr_GetState_beforeStart,  p->video.debugStep.fg.fs_beforeStart,  p->video.debugStep.fg.bBeforeRun,  p->video.debugStep.fg.hr_run,  p->video.debugStep.fg.hr_GetState_beforeStop,  p->video.debugStep.fg.fs_beforeStop  );
		_sntprintf(  tBuf,  cnt,  _T(  "%s, FillBuffer.hr %x, bPktGot %d, bQuit %d,bFailed %d"  ),  tBuf,  p->video.debugStep.fg.FillBuffer.hr,  p->video.debugStep.fg.FillBuffer.bPktGot,  p->video.debugStep.fg.FillBuffer.bParentQuit,  p->video.debugStep.fg.FillBuffer.bFailed  );
		//  _sntprintf(  tBuf,  cnt,  _T(  "%s  errs: notAccept %d, Input %d, output %d, index %d."  ),  tBuf,  p->video.debugStep.uiCnt_DMO_E_NOTACCEPTING,  p->video.debugStep.nErrs_ProcessInput,  p->video.debugStep.nErrs_ProcessOutput,  p->video.debugStep.nErrs_pOutputBuffers_index  ); 
	}
	_sntprintf(  tBuf,  cnt,  _T(  "%s %s"  ),  tBuf,  pTask->debugHint  );
	tBuf[cnt  -  1]  =  0;			
	OutputDebugString(  tBuf  );  OutputDebugString(  _T(  "\n"  )  );

	return  0;
}


//
int  initTransform(  MC_VAR_common  *  pProcInfo,  MSGR_ADDR  *  pAddr_logicalPeer,  int  iTaskId,  unsigned  int  uiTaskType,  AV_TRAN_INFO  *  pTranInfo_unused,  PROC_TASK_AV  *  pTask,  MIS_MSG_TASK  *  pMsgTask,  int  i,  QY_TRANSFORM  *  p  ) 
{
	int  iErr  =  -1;
	//QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	
		  GENERIC_Q_CFG		tmpCfg;

		  CCtxQmcTmpl  *  pCtx  =  pProcInfo;
		  RW_lock_param  *  pQyMc_rwLockParam  =  pCtx->get_qyMc_rwLockParam(  );
		  if  (  !pQyMc_rwLockParam  )  return -1;
		  QMC_cfg  *  pQmcCfg  = (  QMC_cfg  *  )pCtx->get_qmc_cfg(  );
		  if  (  !pQmcCfg  )  return  -1;
		  GENERIC_Q_CFG  *  p_cfg_transformQ  =  &pQmcCfg->transformQ;//Ctx->get_cfg_transformQ(  );
		  if  (  !p_cfg_transformQ  )  return  -1;

		  //
		  memcpy(  &tmpCfg,  p_cfg_transformQ,  sizeof(  tmpCfg  )  );
		  _sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-a-%d-%d"  ),  tmpCfg.name,  iTaskId,  i  );
		  _sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-a-%d-%d"  ),  tmpCfg.mutexName_prefix,  iTaskId,  i  );
		  //  if  (  initGenericQ(  &tmpCfg,  mymalloc,  0,  0,  free,  &p->audio.q  )  )  goto  errLabel;
		  if  (  initQyQ2(  &tmpCfg,  pQyMc_rwLockParam,  mycountof(  p->audio.q2.hEvents  ),  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  NULL,  &p->audio.q2  )  )  goto  errLabel;
		  p->audio.bQInited  =  TRUE;
		  
		  //
		  //
		  p->audio.qBuf2 = new QY_qBuf2();
		  int maxDataBufLen = 128000 * 3 / 8;//  3 secends mp3
		  if (0 != p->audio.qBuf2->initQyQ2(CONST_qType_decA, tmpCfg.uiMaxQNodes, maxDataBufLen, *pQyMc_rwLockParam, true, (tmpCfg.name))) goto errLabel;


		  
		  //
		  memcpy(  &tmpCfg,  p_cfg_transformQ,  sizeof(  tmpCfg  )  );
		  _sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-v-%d-%d"  ),  tmpCfg.name,  iTaskId,  i  );
		  _sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-v-%d-%d"  ),  tmpCfg.mutexName_prefix,  iTaskId,  i  );
		  //  if  (  initGenericQ(  &tmpCfg,  mymalloc,  0,  0,  myfree,  &p->video.q  )  )  goto  errLabel;
		  if  (  initQyQ2(  &tmpCfg,  pQyMc_rwLockParam,  mycountof(  p->video.q2.hEvents  ),  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myDRAW_VIDEO_DATA,  &p->video.q2  )  )  goto  errLabel;
		  p->video.bQInited  =  TRUE;	
		  //
		  
		  //  2011/12/09
		  //  memcpy(  &tmpCfg,  &pProcInfo->cfg.preTransformQ,  sizeof(  tmpCfg  )  );
		  memcpy(  &tmpCfg,  p_cfg_transformQ,  sizeof(  tmpCfg  )  );
		  _sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-pv-%d-%d"  ),  tmpCfg.name,  iTaskId,  i  );
		  _sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-pv-%d-%d"  ),  tmpCfg.mutexName_prefix,  iTaskId,  i  );
		  //  
		  if  (  initQyQ2(  &tmpCfg,  pQyMc_rwLockParam,  mycountof(  p->v_preTransThread.q2.hEvents  ),  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  NULL,  &p->v_preTransThread.q2  )  )  goto  errLabel;
		  p->v_preTransThread.bQInited  =  TRUE;	

		  //  2014/0804

		  //
		  p->pProcInfo  =  pProcInfo;
		  p->pAddr_logicalPeer  =  pAddr_logicalPeer;
		  p->iTaskId  =  iTaskId;
		  p->uiTaskType  =  uiTaskType;	//  2012/03/25
		  p->pTranInfo_unused  =  pTranInfo_unused;		//  2014/11/11
		  p->pTask  =  pTask;
		  p->pMsgTask  =  pMsgTask;		//  2014/08/27
		  //
		  p->index_activeMems_from  =  i;

		  iErr  =  0;
errLabel:
		  return  iErr;

}


void  exitTransform(  PROC_TASK_AV  *  pTask,  QY_TRANSFORM	*	p  )
{

		 //  2011/12/09
		 if  (  p->v_preTransThread.bQInited  )  {
			 exitQyQ2(  &p->v_preTransThread.q2  );
			 p->v_preTransThread.bQInited  =  FALSE;
		 }

		 //
		 if (p->audio.qBuf2 != mynull)
		 {
			 p->audio.qBuf2->exitQyQ2();
			 //
			 MACRO_safeDelete( p->audio.qBuf2);
		 }

		 //
		 if  (  p->audio.bQInited  )  {
			 exitQyQ2(  &p->audio.q2  );
			 p->audio.bQInited  =  FALSE;
		 }
		 if  (  p->video.bQInited  )  {
			 exitQyQ2(  &p->video.q2  );		 
			 p->video.bQInited  =  FALSE;
		 }

		 return;
}


 //void  exitTransforms(  PROC_TASK_AV  *  pTask  );

// int  initTransforms(  MC_VAR_isCli  *  pProcInfo,  MSGR_ADDR  *  pAddr_logicalPeer,  int  iTaskId,  unsigned  int  uiTaskType,  AV_TRAN_INFO  *  pTranInfo,  PROC_TASK_AV  *  pTask  )
 int  initTransforms(  void  *  pMC_VAR_common,  MSGR_ADDR  *  pAddr_logicalPeer,  int  iTaskId,  unsigned  int  uiTaskType,  AV_TRAN_INFO  *  pTranInfo_unused,  PROC_TASK_AV  *  pTask,  MIS_MSG_TASK  *  pMsgTask  ) 
{
	int			iErr	=	-1;

	//
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pMC_VAR_common;

	//QY_MC	*	pQyMc	=	(  QY_MC  *  )pProcInfo->pQyMc;
	int			i;
	int			len;
	//  DWORD		dwThreadDaemonId;

	if  (  !pTask->usCntLimit_transforms  )  return  0;
	if  (  pTask->pTransforms  )  {
		traceLogA(  (char*)  "initTransforms failed, pTransforms is not null"  );
		return  -1;
	}

	len  =  pTask->usCntLimit_transforms  *  sizeof(  QY_TRANSFORM  );
	if  (  !(  pTask->pTransforms  =  (  QY_TRANSFORM  *  )mymalloc(  len  )  )  )  goto  errLabel;
	memset(  pTask->pTransforms,  0,  len  );
	

	for  (  i  =  0;  i  <  pTask->usCntLimit_transforms;  i  ++  )  {
		  QY_TRANSFORM	*	p		=	&pTask->pTransforms[i];

		  if  (  initTransform(  pProcInfo,  pAddr_logicalPeer,  iTaskId,  uiTaskType,  pTranInfo_unused,  pTask,  pMsgTask,  i,  p  )  )  goto  errLabel;
	 }

	//  2014/11/11
	if  (  pTask->ucbVideoConference  
		&&  !pTask->ucbVideoConferenceStarter  )  
	{
#if  0
		//  2014/11/11
		if  (  initTransform(  pProcInfo,  pAddr_logicalPeer,  iTaskId,  uiTaskType,  pTranInfo_unused,  pTask,  pMsgTask,  0,  &pTask->confMosaicTrans.confMosaic_video.transform  )  )  goto  errLabel;
		pTask->confMosaicTrans.confMosaic_video.transform.bMosaicVideo  =  TRUE;

		//
		if  (  initTransform(  pProcInfo,  pAddr_logicalPeer,  iTaskId,  uiTaskType,  pTranInfo_unused,  pTask,  pMsgTask,  0,  &pTask->confMosaicTrans.confMosaic_resource.transform  )  )  goto  errLabel;
		pTask->confMosaicTrans.confMosaic_resource.transform.bMosaicResource  =  TRUE;

		//
		pTask->confMosaicTrans.bExists_confMosaic  =  TRUE;
#endif
	}





	//  
	iErr  =  0;

errLabel:
	if  (  iErr  )  {
		exitTransforms(  pProcInfo,  pTask  );
	}

	return  iErr;
}

 void  exitTransforms(  void  *  pMC_VAR_common,  PROC_TASK_AV  *  pTask  )
{
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pMC_VAR_common;
	int	i;

	if  (  !pTask->usCntLimit_transforms  )  return;
	if  (  !pTask->pTransforms  )  return;

	stopTransformThreads(  pProcInfo,  pTask  );

	//  2014/11/11
#if  0
	exitTransform(  pTask,  &pTask->confMosaicTrans.confMosaic_video.transform  );
	exitTransform(  pTask,  &pTask->confMosaicTrans.confMosaic_resource.transform  );
#endif

	//
	for  (  i  =  0;  i  <  pTask->usCntLimit_transforms;  i  ++  )  {
		 QY_TRANSFORM	*	p	=	&pTask->pTransforms[i];

#if  0  //  2014/11/11
		 //  2014/08/04
		 if  (  pTask->pTransforms[i].saveThread.bQInited  )  exitQyQ2(  &pTask->pTransforms[i].saveThread.q2  );

		 //  2011/12/09
		 if  (  pTask->pTransforms[i].v_preTransThread.bQInited  )  exitQyQ2(  &pTask->pTransforms[i].v_preTransThread.q2  );

		 //
		 if  (  pTask->pTransforms[i].audio.bQInited  )  exitQyQ2(  &pTask->pTransforms[i].audio.q2  );
		 if  (  pTask->pTransforms[i].video.bQInited  )  exitQyQ2(  &pTask->pTransforms[i].video.q2  );		 
#endif
		 exitTransform(  pTask,  p  );
	}

	free(  pTask->pTransforms  );  pTask->pTransforms  =  NULL;

	//
			 //  2014/08/04




	//
	return;
}



 


 ///////////////

  //
 int  stopTransformThread(  MC_VAR_common  *  pProcInfoParam,  PROC_TASK_AV  *  pTask,  QY_TRANSFORM  *  p  )
{
	//MC_VAR_isCli  *  pProcInfo	=	QY_GET_procInfo_isCli(  );
	int				i;
	TCHAR			tBuf[512];
	//  char			buf[128];

	CCtxQmc* pProcInfo = (CCtxQmc*)pProcInfoParam;
	CCtxQmcTmpl  *  pCtx  =  pProcInfo;
	if  (  !pCtx  )  return  -1;
	QMC_status  *  pStatus  =  pCtx->get_qmc_status(  );
	if  (  !pStatus  )  return  -1;

	
	//  2012/03/20
	//for  (  i  =  0;  i  <  pTask->usCntLimit_transforms;  i  ++  )  
	{
		 //QY_TRANSFORM	*	p	=	&pTask->pTransforms[i];

		 //  2011/12/09
		 if  (  p->v_preTransThread.hThread  )  {
			 p->v_preTransThread.bQuit  =  TRUE;
		 }
		 if  (  p->audio.hThread  )  {
			 p->audio.bQuit  =  TRUE;
		 }
		 if  (  p->video.hThread  )  {
			 p->video.bQuit  =  TRUE;
		 }
#if 0
		 if  (  p->saveThread.hThread  )  {	//  2014/08/04
			 p->saveThread.bQuit  =  TRUE;
		 }
#endif
	}
	

	//
	//for  (  i  =  0;  i  <  pTask->usCntLimit_transforms;  i  ++  )  
	{
	//	 QY_TRANSFORM	*	p	=	&pTask->pTransforms[i];

		 //  2011/12/09
		 if  (  p->v_preTransThread.hThread  )  {
			 p->v_preTransThread.bQuit  =  TRUE;
			 //
			 SetEvent(  p->v_preTransThread.q2.hEvents[0]  );
			 waitForObject(  &p->v_preTransThread.hThread,  20000  );
			 //			
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "stopTransformThreads: wait for v_preTrans thread %d, nStep %d, elapse %dms. "  ),  p->v_preTransThread.dwThreadId,  p->v_preTransThread.debugStep.nStep_debug,  GetTickCount(  )  -  p->v_preTransThread.debugStep.dwTickCnt_step_debug  );
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s  errs: notAccept %d, Input %d, output %d, index %d."  ),  tBuf,  p->v_preTransThread.debugStep.uiCnt_DMO_E_NOTACCEPTING,  p->v_preTransThread.debugStep.nErrs_ProcessInput,  p->v_preTransThread.debugStep.nErrs_ProcessOutput,  p->v_preTransThread.debugStep.nErrs_pOutputBuffers_index  ); 
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  pTask->debugHint  );
			 tBuf[mycountof(  tBuf  )  -  1]  =  0;
			 OutputDebugString(  tBuf  );  OutputDebugString(  _T(  "\n"  )  );
			 //
			 if  (  p->v_preTransThread.hThread  )  {
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  "Failed"  ),  tBuf  );
			 }
			 else  InterlockedDecrement(  &pStatus->nThreads_dec  );
		 }	
		 if  (  p->v_preTransThread.hThread  )  {
			 p->v_preTransThread.bQuit  =  TRUE;
			 //
			 SetEvent(  p->v_preTransThread.q2.hEvents[0]  );
			 waitForObject(  &p->v_preTransThread.hThread,  20000  );
			 //
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "stopTransformThreads: wait for v_preTrans thread %d, nStep %d, elapse %dms. "  ),  p->v_preTransThread.dwThreadId,  p->v_preTransThread.debugStep.nStep_debug,  GetTickCount(  )  -  p->v_preTransThread.debugStep.dwTickCnt_step_debug  );
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s  errs: notAccept %d, Input %d, output %d, index %d."  ),  tBuf,  p->v_preTransThread.debugStep.uiCnt_DMO_E_NOTACCEPTING,  p->v_preTransThread.debugStep.nErrs_ProcessInput,  p->v_preTransThread.debugStep.nErrs_ProcessOutput,  p->v_preTransThread.debugStep.nErrs_pOutputBuffers_index  ); 
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  pTask->debugHint  );
			 tBuf[mycountof(  tBuf  )  -  1]  =  0;
			 OutputDebugString(  tBuf  );  OutputDebugString(  _T(  "\n"  )  );
			 //
			 if  (  p->v_preTransThread.hThread  )  {
				 qyExitProcess(  tBuf  );
			 }
			 else  InterlockedDecrement(  &pStatus->nThreads_dec  );

		 }	


		 //
		 if  (  p->audio.hThread  )  {
			 p->audio.bQuit  =  TRUE;
			 //
			 if (pProcInfo->cfg.b_useAudioQ2_toDecA) {
				 SetEvent(p->audio.q2.hEvents[0]);
			 }
			 else {
				 SetEvent(p->audio.qBuf2->hEvent0);
			 }
			 waitForObject(  &p->audio.hThread,  20000  );
			 //
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "stopTransformThreads: wait for audio thread %d, nStep %d, elapse %dms."  ),  p->audio.dwThreadId,  p->audio.debugStep.nStep_debug,  GetTickCount(  )  -  p->audio.debugStep.dwTickCnt_step_debug  );
			 tBuf[mycountof(  tBuf  )  -  1]  =  0;
			 OutputDebugString(  tBuf  );  OutputDebugString(  _T(  "\n"  )  );
			 //
			 if  (  p->audio.hThread  )  {
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  "Failed"  ),  tBuf  );
			 }
			 else  InterlockedDecrement(  &pStatus->nThreads_dec  );

		 }
		 if  (  p->audio.hThread  )  {		//  2009/07/09. retry to wait for audio thread.
			 p->audio.bQuit  =  TRUE;
			 //
			 if (pProcInfo->cfg.b_useAudioQ2_toDecA) {
				 SetEvent(p->audio.q2.hEvents[0]);
			 }
			 else {
				 SetEvent(p->audio.qBuf2->hEvent0);
			 }
			 waitForObject(  &p->audio.hThread,  20000  );
			 //
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "stopTransformThreads: wait for audio thread %d, nStep %d, elapse %dms."  ),  p->audio.dwThreadId,  p->audio.debugStep.nStep_debug,  GetTickCount(  )  -  p->audio.debugStep.dwTickCnt_step_debug  );
			 tBuf[mycountof(  tBuf  )  -  1]  =  0;
			 OutputDebugString(  tBuf  );  OutputDebugString(  _T(  "\n"  )  );
			 //
			 if  (  p->audio.hThread  )  {
				 qyExitProcess(  tBuf  );
			 }
			 else  InterlockedDecrement(  &pStatus->nThreads_dec  );
		 }

		 if  (  p->video.hThread  )  {
			 p->video.bQuit  =  TRUE;
			 //
			 SetEvent(  p->video.q2.hEvents[0]  );
			 waitForObject(  &p->video.hThread,  20000  );
			 //
			 tmp_getHint_video(  pTask,  p,  tBuf,  mycountof(  tBuf  )  );
			 //
			 if  (  p->video.hThread  )  {
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  "Failed"  ),  tBuf  );
			 }
			 else  InterlockedDecrement(  &pStatus->nThreads_dec  );

		 }	
		 if  (  p->video.hThread  )  {
			 p->video.bQuit  =  TRUE;
			 //
			 SetEvent(  p->video.q2.hEvents[0]  );
			 waitForObject(  &p->video.hThread,  20000  );
			 //
			 tmp_getHint_video(  pTask,  p,  tBuf,  mycountof(  tBuf  )  );
			 //
			 if  (  p->video.hThread  )  {
				 qyExitProcess(  tBuf  );
			 }
			 else  InterlockedDecrement(  &pStatus->nThreads_dec  );
		 }	



		 //////////////


	}

	OutputDebugString(  _T(  "stopTransformThreads\n"  )  );

	return  0;
}



 //
 int  stopTransformThreads(  MC_VAR_common  *  pProcInfo,  PROC_TASK_AV  *  pTask  )
{
	//  MC_VAR_isCli  *  pProcInfo	=	QY_GET_procInfo_isCli(  );
	int				i;
	TCHAR			tBuf[512];
	//  char			buf[128];

	CCtxQmcTmpl  *  pCtx  =  pProcInfo;
	if  (  !pCtx  )  return  -1;
	QMC_status* pStatus = pCtx->get_qmc_status();
	if (!pStatus)  return  -1;



	//  2014/11/11
	for  (  i  =  0;  i  <  pTask->usCntLimit_transforms;  i  ++  )  {
		 QY_TRANSFORM	*	p	=	&pTask->pTransforms[i];

		 stopTransformThread(  pCtx,  pTask,  p  );
	}
	
	//  2014/11/11
#if  0
	stopTransformThread(  pCtx,  pTask,  &pTask->confMosaicTrans.confMosaic_video.transform  );
	stopTransformThread(  pCtx,  pTask,  &pTask->confMosaicTrans.confMosaic_resource.transform  );
#endif



	//
#ifdef  __DEBUG__
	OutputDebugString(  _T(  "stopTransformThreads\n"  )  );
#endif

	//
	return  0;
}

