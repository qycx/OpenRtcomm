
#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"colorSpaceFunc.h"
#include	"qmcVideoCapture.h"
//#include	"qmcVideoCapture_isCli.h"
//#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
//  #include	"myfourcc.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

#include	"qmcVideoCapture_rtsp.h"

//#include	"isCliHelpPublic.h"
//#include	"rtspCliHelpPublic.h"

#include	"ctxQmcTmpl.h"
#include	"qmcCfg.h"

//


 //
 int  openLocalQvcf_rtsp_step0(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiRtspType,  LPCTSTR  url,  int  tn_rtspCliPipe,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressorParam,  LPCTSTR  tHint,  int  iIndex_sharedObj  )
{
	int								iErr				=		-1;
	//QY_MC					*		pQyMc				=		(  QY_MC  *  )pProcInfoCommon->pQyMcParam;
	PolicyAvParams			*		pAvParams			=		(  PolicyAvParams  *  )pProcInfoCommon->getPolicyAvParams(  );//QY_GET_PolicyAvParams(  );
	if  (  !pAvParams  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "openLocalVideo_rtsp_step0 failed, pAvParams is null"  )  );
		#endif
		return  -1;
	}

	//
	unsigned  int  uiCamCapType  =  CONST_camCapType_qvcf;  

	//
	int								usCapDriverIndex	=		0;
	TCHAR							devName[100]		=		_T(  ""  );
	TCHAR							devVersion[100]		=		_T(  ""  );
	//  
	int								iIndex_capBmp		=		-1;
	unsigned  int					uiTranNo_sharedObj	=		0;
	//

	TCHAR							tBuf[128]			=  _T(  ""  );

	// 
	if  (  !url  )  return  -1;
	if  (  !tn_rtspCliPipe  )  {
		return  -1;
	}

#if  0
	if  (  isQmCmd(  )  )  return  -1;
#endif

	//
	if  (  !tHint  )  tHint  =  _T(  ""  );

	//
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfoCommon->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "openLocalQvcf_rtsp_step0: %s. index_sharedObj %d. %s"  ),  url,  iIndex_sharedObj,  tHint  );
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "openLocalVideo_rtsp_step0 enters [%s]. index_sharedObj %d"  ),  url,  iIndex_sharedObj  );
#endif

	
		MC_VAR_common			*	pProcInfo	=	(  MC_VAR_common  *  )pProcInfoCommon;
		QY_SHARED_OBJ			*	pSharedObj			=		NULL;
		CAP_procInfo_video		*  pVc  =  NULL;


		pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
		if  (  !pSharedObj  )  {
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "openLocalVideo_rtsp_step0 failed, getSharedObjByIndex returns null"  )  );
			#endif
			goto  errLabel;
		}
		//pSharedObj->bCapDev  =  TRUE;

		int	iIndex_sharedObj_used; iIndex_sharedObj_used = -1;
		if  (  pProcInfo->bWebcamUsing(  uiCamCapType,  0,  url,  NULL,  &iIndex_sharedObj_used  )
			&&  iIndex_sharedObj_used  !=  iIndex_sharedObj  )  
		{
			traceLogA(  (char*)  "openLocalVideo failed. webcam is already used."  );

			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Failed: webcam is used"  )  );
			showNotification(  NULL,  NULL,  NULL,  0,  0,  0,  tBuf  );

			goto  errLabel;
		}
	
		//
		iIndex_capBmp  =  pSharedObj->iIndex_capBmp;
		uiTranNo_sharedObj  =  pSharedObj->uiTranNo;		//  2011/05/31

		//
		pVc  =  (  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
		if  (  !pVc  )  {
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "openLocalVideo failed, getCapBmpBySth returns null"  )  );
			#endif
			goto  errLabel;
		}
		

	//
	if  (  pVc->bCapDevConnected  )  {
		traceLogA(  (char*)  "openAv: capDriver already is connected"  );
		goto  errLabel;
	}

	pVc->uiType  =  CONST_capType_av;
	pVc->iIndex_sharedObj  =  iIndex_sharedObj;
	pVc->uiCamCapType  =  uiCamCapType;

	//  2014/09/10
	memcpy(  &pVc->compressVideo.compressor,  pVideoCompressorParam,  sizeof(  pVc->compressVideo.compressor  )  );
	VIDEO_COMPRESSOR_CFG* pVideoCompressor; pVideoCompressor = &pVc->compressVideo.compressor;
	

	//  if  (  !pVc->policy.bih.biWidth  ||  !pVc->policy.bih.biHeight  )  
	{
		refreshWebCamSettings(  pVideoCompressor,  pVc  );
	}
	

	//
	if  (  uiCamCapType  !=  CONST_camCapType_qvcf  )  {	//  2014/02/23
		traceLog((TCHAR*)  _T(  "openLocalVideo failed: unknown uiCamCapType %d"  ),  uiCamCapType  );
		goto  errLabel;
	}
			
	//
	if  (  initQvcf_rtsp(  pProcInfoCommon,  uiRtspType,  url,  tn_rtspCliPipe,  &pVc->policy.bih,  FALSE,  pProcInfo->get_hMainWnd(  ),  iIndex_sharedObj,  &pSharedObj->pShareMediaObj  )  )  goto  errLabel;	
	pVc->bCapDevConnected  =  TRUE;

	iErr  =  0;

errLabel:

	//MACRO_safeRelease(  pMoniker  );

	if  (  iErr  )  {
	}
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfoCommon->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "openLocalQvcf_rtsp_step0 %s"  ),  (  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  )  )  );

#ifdef  __DEBUG__
	traceLogA(  (char*)  "openLocalQvcf_rtsp_step0 leaves with %s",  iErr  ?  "Failed"  :  "OK"  );
#endif

	return  iErr;

}


//
int  initQvcf_rtsp(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiRtspType,  LPCTSTR  url_selected,  int  tn_rtspCliPipe,  BITMAPINFOHEADER  *  pBih_suggested,  BOOL  bForConfig,  HWND hWnd_notify,  int  iIndex_sharedObj,  void  **  ppQvcfParam  )
{
	int									iErr	=	-1;
	//
	MC_VAR_common				*		pProcInfo	=	pProcInfoCommon;//
	HRESULT								hr;
	QVCF_rtsp				*	p		=	NULL;
	
	RW_lock_param  *  pQyMc_cfg_rwLockParam  =  pProcInfo->get_qyMc_rwLockParam(  );
	if  (  !pQyMc_cfg_rwLockParam  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "initVideoCapDev_rtsp failed, get_qyMc_rwLockParam returns null"  )  );
		#endif
		return  -1;
	}
	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;
	GENERIC_Q_CFG  *  pCfg_transformQ  =  &pQmcCfg->transformQ;//  ProcInfo->get_cfg_transformQ(  );
	if  (  !pCfg_transformQ  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "initVideoCapdev_rtsp failed, get_cfg_transQ returns null"  )  );
		#endif
		return  -1;
	}
	QMC_status  *  pStatus  =  pProcInfo->get_qmc_status(  );
	if  (  !pStatus  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "initVideoCapdev_rtsp failed, get_qmc_status returns null"  )  );
		#endif
		return  -1;
	}

	//
	if  (  !ppQvcfParam  )  return  -1;
	if  (  *ppQvcfParam  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initVideoCapDev_rtsp failed, *ppVideoCapDevParam is not null"  )  );
		return  -1;
	}
	
	QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	CAP_procInfo_video* pVc; pVc = (CAP_procInfo_video*)pProcInfo->getCapBmpBySth(pSharedObj->iIndex_capBmp, 0);
	if  (  !pVc  )  goto  errLabel;


	//
	p  =  (  QVCF_rtsp  *  )mymalloc(  sizeof(  QVCF_rtsp  )  );
	if  (  !p  )  goto  errLabel;
	memset(  p,  0,  sizeof(  QVCF_rtsp  )  );

	//
	p->uiType  =  uiRtspType;
	//  2015/01/24
	p->pProcInfoCommon  =  pProcInfoCommon;
	//  2015/01/28
	safeTcsnCpy(  url_selected,  p->url,  mycountof(  p->url  )  );
	p->iIndex_sharedObj  =  iIndex_sharedObj;

	//  2015/01/28
	p->tn_rtspCliPipe  =  tn_rtspCliPipe;


	//  2015/02/01
	if  (  p->uiType  ==  CONST_rtspType_decV  )  {
		//
		GENERIC_Q_CFG		tmpCfg;
					
		memcpy(  &tmpCfg,  &pQmcCfg->transformQ,  sizeof(  tmpCfg  )  );		
		//  2015/02/10
		tmpCfg.uiMaxQNodes  =  15;
		//
		_sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-dvt-%d"  ),  tmpCfg.name,  p->iIndex_sharedObj  );
		_sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-dvt-%d"  ),  tmpCfg.mutexName_prefix,  p->iIndex_sharedObj  );		
		if  (  initQyQ2(  &tmpCfg,  pQyMc_cfg_rwLockParam,  mycountof(  p->cacheQ2_dvt_decV.hEvents  ),  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myDRAW_VIDEO_DATA,  &p->cacheQ2_dvt_decV  )  )  goto  errLabel;
		p->bQInited_dvt_decV  =  TRUE;	
	}

	//
	DWORD  dwThreadDaemonId;
		
	//
	TRANSINFO_stream* pTransInfo; pTransInfo = (TRANSINFO_stream*)pSharedObj->pTransInfo_stream;
	if  (  !pTransInfo  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "initVideoCapdev_rtsp failed, pSharedObj->pTransInfo_stream is null"  )  );
		#endif
		goto  errLabel;
	}
	if  (  !pTransInfo->myTask.pTransforms  )  goto  errLabel;
	QY_TRANSFORM* pTransform; pTransform = &pTransInfo->myTask.pTransforms[0];

	//  2014/03/25
	pTransform->pCapDev_rtsp  =  p;

	//
#if  0
	if  (  !pTransform->video.bQInited  )  {
		//  2014/03/15
		GENERIC_Q_CFG		tmpCfg;

		memcpy(  &tmpCfg,  pCfg_transformQ,  sizeof(  tmpCfg  )  );
		_sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-rtsp-%d"  ),  tmpCfg.name,  iIndex_sharedObj  );
		_sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-rtsp-%d"  ),  tmpCfg.mutexName_prefix,  iIndex_sharedObj  );
		//  if  (  initGenericQ(  &tmpCfg,  mymalloc,  0,  0,  myfree,  &pTask->pTransforms[i].video.q  )  )  goto  errLabel;
		if  (  initQyQ2(  &tmpCfg,  pQyMc_cfg_rwLockParam,  mycountof(  pTransform->video.q2.hEvents  ),  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myDRAW_VIDEO_DATA,  &pTransform->video.q2  )  )  goto  errLabel;
		pTransform->video.bQInited  =  TRUE;	
	}
#endif
	if  (  !pTransform->video.bQInited  )  {
		showInfo_open0(  0,  0,  _T(  "initQvcf_rtsp failed, trans.v.bQInited is false"  )  );
		goto  errLabel;
	}

	//  2015/05/20
	if  (  !pTransform->audio.hThread  )  {
		//
		pTransform->audio.bQuit  =  FALSE;				 
		pTransform->audio.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_decAudio,  pTransform,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
		if  (  !pTransform->audio.hThread  )  goto  errLabel;					
		pTransform->audio.dwThreadId  =  dwThreadDaemonId;							 
		if  (  ResumeThread(  pTransform->audio.hThread  )  ==  -1  )  goto  errLabel;									 
		
		//  2012/03/25		
		InterlockedIncrement(  &pStatus->nThreads_aTrans  );			 
	}				


	//
	if  (  !pTransform->video.hThread  )  {			
		//
		pTransform->video.bQuit  =  FALSE;				   
		pTransform->video.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_decVideo,  pTransform,  CREATE_SUSPENDED,  &dwThreadDaemonId  );				   
		if  (  !pTransform->video.hThread  )  goto  errLabel;					
		pTransform->video.dwThreadId  =  dwThreadDaemonId;			
		if  (  ResumeThread(  pTransform->video.hThread  )  ==  -1  )  goto  errLabel;	
		
		//  2012/03/25		
		InterlockedIncrement(  &pStatus->nThreads_vTrans  );			   
	}			   


	//
	p->bQuit  =  FALSE;
	p->hThread_recvRtsp  =  CreateThread(  NULL,  0,  mcThreadProc_recvRtsp,  p,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
	if  (  !p->hThread_recvRtsp  )  goto  errLabel;					
	p->dwThreadId  =  dwThreadDaemonId;					
	if  (  ResumeThread(  p->hThread_recvRtsp  )  ==  -1  )  goto  errLabel;									 
	

	//
	iErr  =  0;

errLabel:

	
	if  (  iErr  )  {
		exitQvcf_rtsp(  pProcInfoCommon,  (  void  **  )&p  );
	}
	if  (  !iErr  )  {
		*ppQvcfParam  =  p;
	}


	 return  iErr;
}


//
int  exitQvcf_rtsp(  MC_VAR_common  *  pProcInfoCommon,  void  **  ppQvcfParam  )
 {
	 //  
	 MC_VAR_common  *  pProcInfo  =  pProcInfoCommon;
	 //
	 QVCF_rtsp  *  p	=	NULL;
	 TCHAR					tBuf[128]	=	_T(  "exitVideoCapDev_rtsp"  );

#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "exitQvcf enters"  )  );
#endif

	 //
	if  (  !ppQvcfParam  )  return  0;
	if  (  !*ppQvcfParam  )  return  0;

	p  =  (  QVCF_rtsp  *  )*ppQvcfParam;


	//
	QMC_status  *  pStatus  =  pProcInfo->get_qmc_status(  );
	if  (  !pStatus  )  return  -1;

	//
	QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  p->iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	CAP_procInfo_video* pVc; pVc = (CAP_procInfo_video*)pProcInfo->getCapBmpBySth(pSharedObj->iIndex_capBmp, 0);
	if  (  !pVc  )  goto  errLabel;


	//		
	if  (  p->hThread_recvRtsp  )  {			
		p->bQuit  =  TRUE;			
		//			 
		//SetEvent(  p->audio.q2.hEvents[0]  );			
		waitForObject(  &p->hThread_recvRtsp,  20000  );
		if  (  p->hThread_recvRtsp  )  {				 
			//  qyExitProcess(  _T(  "exitVideoCapDev_rtsp failed: can't wait for rtsp thread."  )  );				
			//
			//  2015/02/07
			LPCTSTR  hint  =  _T(  "exitVideoCapDev_rtsp failed: can't wait for rtsp thread."  );
			BOOL  bNoGui  =  TRUE;
			//
			qyExitProcessEx(  hint,  bNoGui  );
			}			 
		else  {
			  #ifdef  __DEBUG__
					  traceLog((TCHAR*)  _T(  "exitVideoCapDev_rtsp: waiting for thread ok"  )  );
			  #endif
		}		
	}

	if  (  pSharedObj->pTransInfo_stream  )  {
		TRANSINFO_stream  *  pTransInfo  =  (  TRANSINFO_stream  *  )pSharedObj->pTransInfo_stream;
		if  (  pTransInfo->myTask.pTransforms  )  {
			QY_TRANSFORM  *  pTransform  =  &pTransInfo->myTask.pTransforms[0];
			//
			//	  2014/03/15
			int  i;
			for  (  i  =  0;  ;  i  ++  )  {
				 if  (  !pTransform->video.hThread  )  break;
				 //
				 if  (  i  >  20  )  {
					 //  if  (  pQyMc->bQuit  )  break;
					 if  (  pProcInfo->b_qyMc_quit(  )  )  break;
				 }
				 //
				if  (  pTransform->video.hThread  )  {
					pTransform->video.bQuit  =  TRUE;			
					//
					SetEvent(  pTransform->video.q2.hEvents[0]  );			
					waitForObject(  &pTransform->video.hThread,  1000  );			 
					//
					if  (  pTransform->video.hThread  )  {
						qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  "exitViCap_rtsp"  ),  _T(  "Failed: "  ),  _T(  ""  )  );			 
					}
					else  InterlockedDecrement(  &pStatus->nThreads_vTrans  );		 
				}	
				//  2014/07/17
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "wait for video_hThread. i %d. nStep %d, elapse %dms"  ),  i,  pTransform->video.debugStep.dec.nStep_debug, GetTickCount(  )  -  pTransform->video.debugStep.dec.dwTickCnt_step_debug  );
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. sts_run %d, bException %d"  ),  tBuf,  pTransform->video.debugStep.dec.sts_run,  pTransform->video.debugStep.dec.bException  );	//  2014/07/17
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  "exitVCap_rtsp:"  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );

			}
			if  (  pTransform->video.hThread  )  {
				pTransform->video.bQuit  =  TRUE;			 
				//
				SetEvent(  pTransform->video.q2.hEvents[0]  );
				waitForObject(  &pTransform->video.hThread,  20000  );			 
				//
				if  (  pTransform->video.hThread  )  {
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "exitVideoCapDev_rtsp waiting for video.hThread failed"  )  );
					qyExitProcess(  tBuf  );			 
				}			
				else  InterlockedDecrement(  &pStatus->nThreads_vTrans  );		 
			}	

			//////////////////  2015/05/20
			for  (  i  =  0;  ;  i  ++  )  {
				 if  (  !pTransform->audio.hThread  )  break;
				 //
				 if  (  i  >  20  )  {
					 //  if  (  pQyMc->bQuit  )  break;
					 if  (  pProcInfo->b_qyMc_quit(  )  )  break;
				 }
				 //
				if  (  pTransform->audio.hThread  )  {
					pTransform->audio.bQuit  =  TRUE;			
					//
					SetEvent(  pTransform->audio.q2.hEvents[0]  );			
					waitForObject(  &pTransform->audio.hThread,  1000  );			 
					//
					if  (  pTransform->audio.hThread  )  {
						qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  "exitViCap_rtsp"  ),  _T(  "Failed: "  ),  _T(  ""  )  );			 
					}
					else  InterlockedDecrement(  &pStatus->nThreads_aTrans  );		 
				}	
				//  2014/07/17
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "wait for audio_hThread. i %d. nStep %d, elapse %dms"  ),  i,  pTransform->audio.debugStep.dec.nStep_debug, GetTickCount(  )  -  pTransform->audio.debugStep.dec.dwTickCnt_step_debug  );
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. sts_run %d, bException %d"  ),  tBuf,  pTransform->audio.debugStep.dec.sts_run,  pTransform->audio.debugStep.dec.bException  );	//  2014/07/17
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  "exitVCap_rtsp:"  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );

			}
			if  (  pTransform->audio.hThread  )  {
				pTransform->audio.bQuit  =  TRUE;			 
				//
				SetEvent(  pTransform->audio.q2.hEvents[0]  );
				waitForObject(  &pTransform->audio.hThread,  20000  );			 
				//
				if  (  pTransform->audio.hThread  )  {
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "exitVideoCapDev_rtsp waiting for audio.hThread failed"  )  );
					qyExitProcess(  tBuf  );			 
				}			
				else  InterlockedDecrement(  &pStatus->nThreads_aTrans  );		 
			}	
			
			//
			//if  (  pTransform->video.bQInited  )  exitQyQ2(  &pTransform->video.q2  );	
		}
	}

	//
	if  (  p->bQInited_dvt_decV  )  {
		exitQyQ2(  &p->cacheQ2_dvt_decV  );  p->bQInited_dvt_decV  =  FALSE;
	}

	
errLabel:

	//
	free(  p  );
	*ppQvcfParam  =  NULL;
	

#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "exitQvcf leaves"  )  );
#endif


	 return  0;
 }



 