
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
#include	"qvcfDefs.h"
#include    "GuiShare.h"

extern "C"
{
#include "libavutil\samplefmt.h"
#include "libavutil\channel_layout.h"
}


 //int  prepareForOpeningRtsp(  int  iIndex_sharedObj  )
 int  prepareForOpeningRtsp(  MC_VAR_common  *  pProcInfoCommon,  int  iIndex_sharedObj  )
{
	int  iErr  =  -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	MC_VAR_isCli  *  pProcInfo  =  (CCtxQmc  *  )pProcInfoCommon;//
	QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  return  -1;

	if  (  pSharedObj->pTransInfo_stream  )  return  -1;

#if  10
	//  2014/03/15	
	int  size  =  sizeof(  TRANSINFO_stream  );		
	if  (  !pSharedObj->pTransInfo_stream  )  {
		pSharedObj->pTransInfo_stream  =  mymalloc(  size  );
		if  (  !pSharedObj->pTransInfo_stream  )  goto  errLabel;
		memset(  pSharedObj->pTransInfo_stream,  0,  size  );					  		
		//
		TRANSINFO_stream  *  pTransInfo  =  (  TRANSINFO_stream  *  )pSharedObj->pTransInfo_stream;			
		
		//
		{
			void* pDb = NULL;
#ifndef  __NOTSUPPORT_DB__
			CQnmDb		db;
			if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
			pDb = db.m_pDbMem->pDb;
#endif
			int  tmp_iTaskId;

			tmp_iTaskId = newTaskId(pDb, pQyMc->cfg.db.iDbType);
			pTransInfo->iTaskId = tmp_iTaskId;

		}
		HWND  hWnd_task = NULL;
		pTransInfo->index_taskInfo = newTaskInfoIndex(pProcInfo, CONST_taskDataType_conf, hWnd_task, pTransInfo->iTaskId, _T(""));
		if (pTransInfo->index_taskInfo < 0) {
			showInfo_open0(0, 0, _T("doCmd_startAvCall: for rtsp: newTaskInfoIndex failed"));
			goto  errLabel;
		}		
		//
		pTransInfo->myTask.ucbLocalSource_rtspStream  =  TRUE;			
		//
		pTransInfo->myTask.iIndex_taskInfo = pTransInfo->index_taskInfo;
		//
		pTransInfo->myTask.usCntLimit_transforms  =  1;			
		if  (  initTransforms(  pProcInfo,  &pTransInfo->addr_logicalPeer,  0,  0,  &pTransInfo->tranInfo,  &pTransInfo->myTask,  NULL  )  )  goto  errLabel;
		//
		QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, pTransInfo->index_taskInfo);
		if (!pTaskInfo)  goto  errLabel;
		QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
		pTc->videoConference.usCntLimit_activeMems_from = 1;
		//
		pTransInfo->myTask.usCntLimit_mems_from  =  1;			
		size  =  sizeof(  TASK_AV_FROM  )  *  pTransInfo->myTask.usCntLimit_mems_from;
		pTransInfo->myTask.pMems_from  =  (  TASK_AV_FROM  *  )mymalloc(  size  );
		if  (  !pTransInfo->myTask.pMems_from  )  goto  errLabel;
		memset(  pTransInfo->myTask.pMems_from,  0,  size  );						  
	}
#endif

	iErr  =  0;

errLabel:
	return  iErr;

 }

 //
#ifdef  __DEBUG__
 bool  b__DBG_rtspCli__();
#endif 


//  2014/09/11
 int  openLocalVideo_rtsp(  MC_VAR_common  *  pProcInfoCommon,  LPCTSTR  url,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressorParam,  int  iIndex_sharedObj  )
{
	int  iErr  =  -1;

	TCHAR  tHint[128]  =  _T(  ""  );  

	//  2015/01/28
	unsigned  int  uiRtspType  =  0;
	int  tn_rtspCliPipe  =  getuiNextTranNo(  0,  0,  0  );
	//
#ifdef  __DEBUG__
	//
	if (b__DBG_rtspCli__()) {
		tn_rtspCliPipe = 883;
	}
#endif 
	

	// 
	//  2015/10/11
	BOOL  bCapDev  =  TRUE;
	//
	if  (  openLocalVideo_rtsp_step0(  pProcInfoCommon,  uiRtspType,  url,  tn_rtspCliPipe,  pVideoCompressorParam,  tHint,  bCapDev,  iIndex_sharedObj  )  )  goto  errLabel;
	if  (  openLocalVideo_rtsp_step1(  pProcInfoCommon,  url,  TRUE,  tHint,  iIndex_sharedObj  )  )  goto  errLabel;
	if  (  openLocalVideo_rtsp_step2(  pProcInfoCommon,  url,  tHint,  iIndex_sharedObj  )  )  goto  errLabel;


	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		closeLocalVideo(  pProcInfoCommon,  iIndex_sharedObj  );
	}

	return  iErr;
 }



//  2014/09/11
 int  openLocalVideo_rtsp_step0(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiRtspType,  LPCTSTR  url,  int  tn_rtspCliPipe,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressorParam,  LPCTSTR  tHint,  BOOL  bCapDev,  int  iIndex_sharedObj  )
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
	unsigned  int  uiCamCapType  =  CONST_camCapType_rtsp;  

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
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfoCommon->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "openLocalVideo_rtsp_step0: %s. index_sharedObj %d. %s"  ),  url,  iIndex_sharedObj,  tHint  );
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
		//  pSharedObj->bCapDev  =  TRUE;
		pSharedObj->bCapDev  =  bCapDev;  //  2015/10/11

		//
		int	iIndex_sharedObj_used; iIndex_sharedObj_used = -1;
		if  (  pProcInfo->bWebcamUsing(  uiCamCapType,  0,  url,  NULL,  &iIndex_sharedObj_used  )
			&&  iIndex_sharedObj_used  !=  iIndex_sharedObj  )  
		{
			#ifdef  __DEBUG__
					traceLogA(  (char*)  "openLocalVideo failed. webcam is already used."  );
			#endif

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
	if  (  uiCamCapType  !=  CONST_camCapType_rtsp  )  {	//  2014/02/23
		traceLog((TCHAR*)  _T(  "openLocalVideo failed: unknown uiCamCapType %d"  ),  uiCamCapType  );
		goto  errLabel;
	}
			
	//
	if  (  initVideoCapDev_rtsp(  pProcInfoCommon,  uiRtspType,  url,  tn_rtspCliPipe,  &pVc->policy.bih,  FALSE,  pProcInfo->get_hMainWnd(  ),  iIndex_sharedObj,  NULL,  &pVc->capDev.pVideoCapDev  )  )  goto  errLabel;	
	pVc->bCapDevConnected  =  TRUE;

	iErr  =  0;

errLabel:

	//MACRO_safeRelease(  pMoniker  );

	if  (  iErr  )  {
	}
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfoCommon->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "openLocalVideo_rtsp_step0 %s"  ),  (  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  )  )  );

#ifdef  __DEBUG__
	traceLogA(  (char*)  "openLocalVideo_rtsp_step0 leaves with %s",  iErr  ?  "Failed"  :  "OK"  );
#endif

	return  iErr;

}

//
 int  openLocalVideo_rtsp_step1(  MC_VAR_common  *  pProcInfoCommon,  LPCTSTR  url,  BOOL bWait,  LPCTSTR  tHint,  int  iIndex_sharedObj  )
{
	int								iErr				=		-1;

	//
	CCtxQmcTmpl  *  pCtx  =  pProcInfoCommon;
	if  (  !pCtx  )  return  -1;
	QNM_CUSRES_INFO  *  pCusRes1  =  pCtx->get_qyMc_cusRes(  );
	if  (  !pCusRes1  )  {
		//  return  -1;
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "openLocalVideo_rtsp_step1: pCusRes is null"  )  );
#endif
	}

	//
	//QY_MC					*		pQyMc				=		(  QY_MC  *  )pProcInfoCommon->pQyMcParam;
	PolicyAvParams			*		pAvParams			=		(  PolicyAvParams  *  )pProcInfoCommon->getPolicyAvParams(  );  //  QY_GET_PolicyAvParams(  );
	if  (  !pAvParams  )  return  -1;

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
	//if  (  isQmCmd(  )  )  return  -1;
	
	
	//
	if  (  !tHint  )  tHint  =  _T(  ""  );

	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfoCommon->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "openLocalVideo_rtsp_step1: %s. index_sharedObj %d. %s"  ),  url,  iIndex_sharedObj,  tHint  );
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "openLocalVideo_rtsp_step1 enters [%s], index_sharedObj %d"  ),  url,  iIndex_sharedObj  );
#endif

	
		MC_VAR_common	*	pProcInfo	=	(  MC_VAR_common  *  )pProcInfoCommon;
		QY_SHARED_OBJ			*		pSharedObj			=		NULL;
		CAP_procInfo_video  *  pVc  =  NULL;

	
	//
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );	
	if  (  !pSharedObj  )  goto  errLabel;

	//	
	iIndex_capBmp  =  pSharedObj->iIndex_capBmp;		
	uiTranNo_sharedObj  =  pSharedObj->uiTranNo;		//  2011/05/31
	
	//	
	pVc  =  (  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );		
	if  (  !pVc  )  goto  errLabel;

	//
	VIDEO_COMPRESSOR_CFG* pVideoCompressor; pVideoCompressor = &pVc->compressVideo.compressor;


	//
	if  (  !bGetCapturePara_rtsp(  pProcInfoCommon,  iIndex_capBmp,  BufferCB_av,  sizeof(  MIS_MSGU  ),  bWait,  pVc->capDev.pVideoCapDev,  &pVc->vh_org  )  )  {
					  #ifdef  __DEBUG__
							  traceLog((TCHAR*)  _T(  "openLocalVideo_rtsp_step1 failed, bGetCapPara failed"  )  );
					  #endif
					  myShowInfo(  pProcInfo,  0,  _T(  "openLocalVideo_rtsp_step1 failed, bGetCapPara failed"  )  );
					  goto  errLabel;		
	}
	
	
	//
	BOOL  bChkBih; bChkBih = TRUE;
	if  (  pSharedObj->uiType1  ==  CONST_sharedObjType_qvcf  )  {
		bChkBih  =  FALSE;
	}
	

	if  (  bChkBih  )  {
		//  2011/08/13
		if  (  pVc->policy.bih.biWidth  &&  pVc->policy.bih.biHeight  )  {
			if  (  //pVc->vh_org.bih.biWidth  !=  pVc->policy.bih.biWidth ||  
				pVc->vh_org.bih.biHeight  !=  pVc->policy.bih.biHeight  )
			{
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: %dx%d"  ),  getResStr(  0,  pCusRes1,  CONST_resId_cantSupportResolution  ),  pVc->policy.bih.biWidth,  pVc->policy.bih.biHeight  );
				showNotification(  NULL,  NULL,  NULL,  0,  0,  0,  tBuf  );
			}
		}
	}

	//	
	if (pVc->bCapDevConnected) {
		if (startCapture(pProcInfo, pVc)) {
			_sntprintf(tBuf, mycountof(tBuf), _T("Can't use the camera. Maybe it's used by others"));
			showNotification_open(0, 0, 0, tBuf);
		}
	}

	//
	iErr  =  0;

errLabel:

	//MACRO_safeRelease(  pMoniker  );

	if  (  iErr  )  {
	}
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfoCommon->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "openLocalVideo_rtsp_step1 %s"  ),  (  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  )  )  );

	traceLogA(  (char*)  "openLocalVideo_rtsp_step1 leaves with %s",  iErr  ?  "Failed"  :  "OK"  );

	return  iErr;

}


 int  openLocalVideo_rtsp_step2(  MC_VAR_common  *  pProcInfoCommon,  LPCTSTR  url,  LPCTSTR  tHint,  int  iIndex_sharedObj  )
{
	int								iErr				=		-1;
	//QY_MC					*		pQyMc				=		(  QY_MC  *  )pProcInfoCommon->pQyMcParam;
	PolicyAvParams			*		pAvParams			=		(  PolicyAvParams  *  )pProcInfoCommon->getPolicyAvParams(  );//QY_GET_PolicyAvParams(  );
	if  (  !pAvParams  )  return  -1;
	CUS_MODULES  *  pModules  =  (  CUS_MODULES  *  )pProcInfoCommon->getCusModules(  );
	if  (  !pModules  )  return  -1;

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
	//if  (  isQmCmd(  )  )  return  -1;
	

	//
	if  (  !tHint  )  tHint  =  _T(  ""  );
	
	//
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfoCommon->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "openLocalVideo_rtsp_step2: %s. index_sharedObj %d. %s"  ),  url,  iIndex_sharedObj,  tHint  );
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "openLocalVideo_rtsp_step2 enters [%s], index_sharedObj %d"  ),  url,  iIndex_sharedObj  );
#endif

	
		MC_VAR_common	*	pProcInfo	=	(  MC_VAR_common  *  )pProcInfoCommon;
		QY_SHARED_OBJ			*		pSharedObj			=		NULL;
		CAP_procInfo_video  *  pVc  =  NULL;

	//
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );	
	if  (  !pSharedObj  )  goto  errLabel;

	//	
	iIndex_capBmp  =  pSharedObj->iIndex_capBmp;		
	uiTranNo_sharedObj  =  pSharedObj->uiTranNo;		//  2011/05/31
	
	//	
	pVc  =  (  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );		
	if  (  !pVc  )  goto  errLabel;

	//
	VIDEO_COMPRESSOR_CFG* pVideoCompressor; pVideoCompressor = &pVc->compressVideo.compressor;
	


	//
	if  (  pVc->vh_org.bih.biCompression  !=  BI_RGB  ||  pVc->vh_org.bih.biBitCount  !=  24  )  {
		if  (  initOrg2RgbBuf(  pProcInfoCommon,  (  CAP_procInfo_bmpCommon  *  )pVc  )  )  {
			traceLogA(  (char*)  "initOrg2RgbBuf failed."  );
			goto  errLabel;		
		}
	}

	//
	QY_VIDEO_HEADER	*	pVh_rgb;
	pVh_rgb  =  pVc->bOrg2RgbBufInited  ?  &pVc->vh_rgb  :  &pVc->vh_org;

	//
	//  2010/09/13
	//
	
		//  2014/04/03
		pVideoCompressor->common.pVideoQ2  =  &pVc->thread.q2;
		pVideoCompressor->common.pParent_transform  =  pVc;
		//
		unsigned  int  uiCapType; uiCapType = CONST_capType_av;
		if  (  pSharedObj->uiType1  ==  CONST_sharedObjType_qvcf  )  {	//  2015/05/25
			uiCapType  =  CONST_capType_qvcf;
		}
		//
		if  (  pProcInfoCommon->initCompressVideo(  (  BITMAPINFO  *  )&pVh_rgb->bih,  uiCapType,  pVideoCompressor,  TRUE,  0,  &pVc->compressVideo  )  )  
		{
			TCHAR	tBuf[128]  =  _T(  ""  );
			CUS_MODULE_U  *  pModule  =  NULL;

			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "openLocalVideo: initCompressVideo failed, %s, fourcc %s."  ),  qyGetDesByType1(  pAvParams->pVideoCompressorsTable,  pVideoCompressor->common.ucCompressors  ),  CQyString(  pVideoCompressor->common.fourccStr  )  );  
			if  (  pVideoCompressor->common.ucCompressors  ==  CONST_videoCompressors_hwAccl  )  {
				pModule  =  pModules->pMediaSdk_enc;
				if  (  pModule
					&&  pModule->common.hModule  
					&&  pModule->compress.mgr.ucbNotSupported_hw  )
				{
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s Hardware accelerator not supported"  ),  tBuf  );
				}
			}
			//  qyShowHint(  _T(  "%s"  ),  tBuf  );  
			myMessageBox(  NULL,  tBuf,  _T(  "www.qycx.com"  ),  MB_OK  );
			goto  errLabel;
		}


	

	//
	char  fourccStr_stream[5  +  1];  fourccStr_stream[0]  =  0;
	//  iFourcc2Str(  pVc->vh_org.bih.biCompression,  fourccStr_org,  mycountof(  fourccStr_org  )  );
	iFourcc2Str(  pVc->compressVideo.vh_stream.dwFourcc,  fourccStr_stream,  mycountof(  fourccStr_stream  )  );
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "w [%d], h [%d], pic [%s],  org [%d]"  ),  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight, CQyString(  fourccStr_stream  ),  pVc->vh_org.bih.biSizeImage  );
	//  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "rgb [%d]"  ),  pVc->vh_rgb.bih.biSizeImage  );
	//  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "fourcc [%s], com [%d], Quality [%d]"  ),  CQyString(  pVc->compressVideo.compressor.common.fourccStr  ),  pVc->compressVideo.iCompressBufSize,  pVc->compressVideo.u.vcm.iQuality  );


	{
		CAP_procInfo_audioCommon* pVcAudio = (CAP_procInfo_audioCommon*)getCapAudioBySth(pProcInfo, pSharedObj->iIndex_capBmp, 0);
		if (pVcAudio) {

			AUDIO_COMPRESSOR_CFG* pAudioCompressor = &pVcAudio->compressAudio.compressor;


			//AUDIO_COMPRESSOR_CFG	audioCompressor;
		
			//memset(&audioCompressor, 0, sizeof(audioCompressor));
			////  audioCompressor.ucCompressors  =  pCompressor->audio.ucCompressors;
			//memcpy(&audioCompressor, &pCompressor->audio, sizeof(audioCompressor));
			//memcpy(&audioCompressor.wf_decompress_default, &pVcAudio->wf_org, sizeof(audioCompressor.wf_decompress_default));
			////
			//memset(&audioCompressor.wf_compress, 0, sizeof(audioCompressor.wf_compress));	//  2011/02/02
			//audioCompressor.wf_compress.wFormatTag = pCompressor->audio.wf_compress.wFormatTag;
			//audioCompressor.wf_compress.nChannels = pVcAudio->wf_org.nChannels;
			//audioCompressor.wf_compress.nSamplesPerSec = pVcAudio->wf_org.nSamplesPerSec;
			//audioCompressor.wf_compress.wBitsPerSample = pVcAudio->wf_org.wBitsPerSample;
			//
			////
			////  2016/12/10
			//AUDIO_COMPRESSOR_CFG* pCompressor = &audioCompressor;

			pAudioCompressor->common.pAudioQ2 = &pVcAudio->thread.q2;
			pAudioCompressor->common.pParent_transform = pVcAudio;

			pVcAudio->wf_org.wFormatTag = WAVE_FORMAT_PCM;
			pVcAudio->wf_org.nChannels = 1;
			pVcAudio->wf_org.wBitsPerSample = 16;
			pVcAudio->wf_org.cbSize = 0;
			pVcAudio->wf_org.nSamplesPerSec = 16000;

			pVcAudio->wf_org.nBlockAlign = (pVcAudio->wf_org.wBitsPerSample / 8) * pVcAudio->wf_org.nChannels;
			pVcAudio->wf_org.nAvgBytesPerSec = pVcAudio->wf_org.nSamplesPerSec * pVcAudio->wf_org.nBlockAlign;

			pVcAudio->compressAudio.compressor.common.ucCompressors = CONST_audioCompressors_ffmpeg;
			//
			if (initCompressAudio(pProcInfo, &pVcAudio->wf_org, pAudioCompressor, &pVcAudio->compressAudio)) {
				showNotification(NULL, 0, 0, 0, 0, 0, _T("Initialize audio compress failed!"));
				
			}

			TRANSINFO_stream* pTransInfo = (TRANSINFO_stream*)pSharedObj->pTransInfo_stream;
			if (!pTransInfo->myTask.pMems_from)  goto  errLabel;
			TASK_AV_FROM* pFrom = &pTransInfo->myTask.pMems_from[0];

			//	
			

			if (pFrom->audio.ta_recvd.compressor.common.sample_fmt != 16000) {
				__int64 src_ch_layout = AV_CH_LAYOUT_MONO;
				int src_rate = pFrom->audio.ta_recvd.compressor.common.sample_fmt;


				AVSampleFormat src_sample_fmt = AV_SAMPLE_FMT_S16;
				//int src_nb_samples = src_rate / 100;
				int src_nb_samples = 1024;
				__int64  dst_ch_layout = AV_CH_LAYOUT_MONO;
				int  dst_rate = 16000;
				AVSampleFormat  dst_sample_fmt = AV_SAMPLE_FMT_S16;
				int  dst_nb_samples;





				if (GuiShare.pf_initResample(src_ch_layout, src_rate, src_sample_fmt, src_nb_samples, dst_ch_layout, dst_rate,
					dst_sample_fmt, &pVcAudio->ctxResample)) {
					showNotification(NULL, 0, 0, 0, 0, 0, _T("Initialize audio resample failed!"));
				}
			}
			else {

				int i = 5;

			}

			/*if (initResampleAudio(pProcInfo, &pVcAudio->wf_org, pAudioCompressor, &pVcAudio->resampleAudio)) {
				showNotification(NULL, 0, 0, 0, 0, 0, _T("Initialize audio resample failed!"));

			}*/

			



		}//
		

	}


	iErr  =  0;

errLabel:

	//MACRO_safeRelease(  pMoniker  );

	if  (  iErr  )  {
	}
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfoCommon->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "openLocalVideo_rtsp_step2 %s"  ),  (  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  )  )  );

	traceLogA(  (char*)  "openLocalVideo_rtsp_step2 leaves with %s",  iErr  ?  "Failed"  :  "OK"  );

	return  iErr;

}



/////////////////////////////////////////////////////







 //  2014/08/08
QY_DMITEM  CONST_nalTypeTable_h264_en[]  =  
{
	{		5,		(TCHAR*)_T(  "IDR"  ),	},
	{		7,		(TCHAR*)_T(  "SPS"  ),	},
	{		8,		(TCHAR*)_T(  "PPS"  ),	},
	{		-1,		},
};






//
QY_DMITEM  CONST_nalTypeTable_h265_en[]  =
{
	{		32,		(TCHAR*)_T(  "VPS"  ),	},	//  NAL_UNIT_VPS, // 32
	{		33,		(TCHAR*)_T(  "SPS"  ),  },	//  NAL_UNIT_SPS, // 33
	{		34,		(TCHAR*)_T(  "PPS"  ),	},	//  NAL_UNIT_PPS, // 34
	{		-1,			},
};



//
BOOL  bStartCodeExistsFunc(  unsigned  char  *  fBuffer,  int  frameSize  )
{
	BOOL	bStartCodeExists  =  FALSE;
	
	  if  (  frameSize  >=  4  )  {
		  if  (  fBuffer[0]  ==  0
			  &&  fBuffer[1]  ==  0  )
		  {
			  if  (  fBuffer[2]  ==  1  )  {
				  bStartCodeExists  =  TRUE;
				  }
			  else  if  (  fBuffer[2]  ==  0
						&&  fBuffer[3]  ==  1  )
			  {
				  bStartCodeExists  =  TRUE;
			  }
		  }
	  }

	  return  bStartCodeExists;
}

//
int  searchNalType(  MC_VAR_common  *  pProcInfo,  int  iFourcc,  unsigned  char  *  pInput,  unsigned  int  len  )
{
	int		i;
	TCHAR	tBuf[256]  =  _T(  "search: "  );

	//
	if  (  iFourcc  ==  CONST_fourcc_h264  )  {


	//
	for  (  i  =  0;  i  <  len  ;  i  ++  )  {
		 if  (  bStartCodeExistsFunc(  pInput  +  i,  len  -  i  )  )  {
			 int  nalType  =  M_nalType_h264(  pInput  +  i  );
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  (TCHAR*)_T(  "%s, [%d]=%d,%s"  ),  tBuf,  i,  nalType,  qyGetDesByType1(  CONST_nalTypeTable_h264_en,  nalType  )  );
			 i  +=  3;
			 continue;
		 }
	}

	}

	//
	myShowInfo(  pProcInfo,  0,  tBuf  );
	return  0;
}

//  
//  int  BufferCB_v_rtsp(  MC_VAR_common  *  pProcInfo,  void  *  pGBUF_rtspCliHelp,  int  iIndex_capProcInfo,  int  iMediumType,  int  iCodecType,  int  iSampleTimeInMs,  unsigned  int  uiPts,  unsigned  char  *  pBuffer,  long  BufferLen,  bool  bSpsPps,  int  index_spsPps,  bool  bFinished_spsPps,  CB_rtsp_res  *  pRes  )
int  BufferCB_v_rtsp(  MC_VAR_common  *  pProcInfo,  void  *  pGBUF_rtspCliHelp,  int  iIndex_capProcInfo,  int  iMediumType,  int  iDataType,  int  iCodecType,  int  iSampleTimeInMs,  unsigned  int  uiPts,  unsigned  char  *  pBuffer,  long  BufferLen,  bool  bSpsPps,  int  index_spsPps,  bool  bFinished_spsPps,  CB_rtsp_res  *  pRes  )
{
	HRESULT						hr					=	-1;
	//  
	QY_SHARED_OBJ			*	pSharedObj			=	NULL;


	CQyMalloc					mallocObj;
	CAP_procInfo_video		*	pVc1;

#if  10
	pVc1				=	(  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  iIndex_capProcInfo,  0  );
	if  (  !pVc1  )  goto  errLabel;
	pSharedObj			=	getSharedObjByIndex(  pProcInfo,  pVc1->iIndex_sharedObj  );		//  ÕâÀïÒªÓÃindexÀ´»ñÈ¡
	if  (  !pSharedObj  )  goto  errLabel;
	if  (  !pSharedObj->pTransInfo_stream  )  goto  errLabel;
	TRANSINFO_stream* pTransInfo; pTransInfo = (TRANSINFO_stream*)pSharedObj->pTransInfo_stream;
	if  (  !pTransInfo->myTask.pMems_from  )  goto  errLabel;
	TASK_AV_FROM* pFrom; pFrom = &pTransInfo->myTask.pMems_from[0];

	//	
	QY_TRANSFORM* pTransform; pTransform = &pTransInfo->myTask.pTransforms[0];



	#ifdef  __DEBUG__
#if  0
			if  (  pProcInfo->cfg.debugStatusInfo.ucbPrint_rtsp  )  {
				traceLogA(  (char*)  "Grab_rtsp: video data, len %d, SampleTime %d",  BufferLen, iSampleTimeInMs  );
			}
#endif
	#endif

		//  
		#if  0  //  def  __WINCE__
				if  (  pProcInfo->hWnd_testWebcam  !=  pSharedObj->hWnd_starter  )  {
					//  for winCe, localVideo don't need to be displayed
					goto  errLabel;
				}
		#endif

		if  (  iMediumType  !=  CONST_mediumType_video  )  goto  errLabel;
		//if  (  iCodecType  !=  CONST_codecType_h264  )  goto  errLabel;
		
		//  2014/02/25
		switch  (  iDataType  )  {
				case  CONST_vcfDataType_ucCompressors:
					  unsigned  char  ucCompressors;  ucCompressors  =  pBuffer[0];
					  pFrom->video.tv_recvd.compressor.common.ucCompressors  =  ucCompressors;
					  hr  =  S_OK;  goto  errLabel;
					  break;
				case  CONST_vcfDataType_vh:
					  QY_VIDEO_HEADER  *  pVh;  pVh  =  (  QY_VIDEO_HEADER  *  )pBuffer;
					  switch  (  pVh->bih.biCompression  )  {
							  case  BI_RGB:  
							  case  CONST_fourcc_YV12:
							  case  CONST_fourcc_I420:	//  2014/07/21
								    pFrom->video.tv_recvd.vh_decompress  =  *pVh;
									break;
							  default:
									  pFrom->video.tv_recvd.vh_compress  =  *pVh;
									  break;
					  }
					  //
					  if  (  !pFrom->video.tv_recvd.uiTranNo_openAvDev  )  {
						  pFrom->video.tv_recvd.uiTranNo_openAvDev  =  getuiNextTranNo(  0,  0,  0  );
					  }
					  //
					  if  (  pFrom->video.tv_recvd.vh_compress.bih.biCompression  
						  &&  pFrom->video.tv_recvd.vh_decompress.bih.biWidth  
						  &&  pFrom->video.tv_recvd.vh_decompress.bih.biHeight  )
					  {
						  //  for vp8. 
						  pFrom->video.bGot_vh_stream  =  TRUE;			
					  }

					  //
					  hr  =  S_OK;  goto  errLabel;			
					  break;

					  break;
				default:
						break;
		}


		//  2014/02/25
		if  (  bSpsPps  )  {	//  把sps pps存起来
			switch  (  iCodecType  )  {
					case  CONST_codecType_h264:
						  pFrom->video.tv_recvd.vh_stream.dwFourcc  =  CONST_fourcc_h264;
						  break;
					case  CONST_codecType_HEVC:  //  2017/10/08
						  pFrom->video.tv_recvd.vh_stream.dwFourcc  =  CONST_fourcc_HEVC;						
						  break;
					default:
						    TCHAR  tBuf[128];
							_sntprintf(  tBuf,  mycountof(  tBuf  ),  (TCHAR*)_T(  "BufferCB_v_rtsp failed, unsupported iCodecType %d"  ),  iCodecType  );
							showInfo_open0(  0,  0,  tBuf  );
							goto  errLabel;
			}
			if  (  !bFinished_spsPps  )  {
				//
				if  (  index_spsPps  >=  mycountof(  pFrom->video.tv_recvd.vh_stream.mems  )  )  goto  errLabel;
				//
				if  (  sizeof(  pFrom->video.tv_recvd.vh_stream.mems[index_spsPps].spsPps  )  <  BufferLen  )  goto  errLabel;
				memcpy(  pFrom->video.tv_recvd.vh_stream.mems[index_spsPps].spsPps,  pBuffer,  BufferLen  );
				pFrom->video.tv_recvd.vh_stream.mems[index_spsPps].usLen  =  BufferLen;		
					}
			else  {
				  if  (  index_spsPps  >  mycountof(  pFrom->video.tv_recvd.vh_stream.mems  )  )  goto  errLabel;
				  pFrom->video.tv_recvd.vh_stream.usCnt  =  index_spsPps;
				  pFrom->video.bGot_vh_stream  =  TRUE;			
				  //
				  pFrom->video.tv_recvd.compressor.common.ucCompressors = CONST_videoCompressors_hwAccl;// CONST_videoCompressors_stream;
				  //  2017/10/08
				  iFourcc2Str(  pFrom->video.tv_recvd.vh_stream.dwFourcc,  pFrom->video.tv_recvd.compressor.common.fourccStr,  mycountof(  pFrom->video.tv_recvd.compressor.common.fourccStr  )  );  
				  //
				  pFrom->video.tv_recvd.uiTranNo_openAvDev  =  getuiNextTranNo(  0,  0,  0  );

				  //
				  QMC_TASK_INFO* pTaskInfo = (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex((CCtxQmc  *  )pProcInfo, pTransInfo->index_taskInfo);
				  if (!pTaskInfo)  goto  errLabel;
				  QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
				  if (!pTc)  goto  errLabel;
				  if (pTc->common.uiType != CONST_taskDataType_conf)  goto  errLabel;

				  DLG_TALK_videoConferenceActiveMemFrom* pActiveMem = &pTc->videoConference.activeMems_from[0];
				  pActiveMem->avStream.obj.tranInfo.video = pFrom->video.tv_recvd;

				  //  暂时定义为这个
				  int  iW_dec = 1280;
				  int  iH_dec = 720;
				  //
				  iW_dec = 1920;
				  iH_dec = 1080;
				  //
				  pActiveMem->avStream.obj.tranInfo.video.vh_decompress.bih.biWidth = iW_dec;// 1280;// 640;
				  pActiveMem->avStream.obj.tranInfo.video.vh_decompress.bih.biHeight = iH_dec;// 720;// 480;
				  //makeBmpInfoHeader_i420(12, 1280, 720, &pActiveMem->avStream.obj.tranInfo.video.vh_decompress.bih);
				  makeBmpInfoHeader_i420(12, iW_dec, iH_dec, &pActiveMem->avStream.obj.tranInfo.video.vh_decompress.bih);
				  //
				  makeBmpInfoHeader_i420(12, iW_dec, iH_dec, &pActiveMem->avStream.obj.tranInfo.video.vh_compress.bih);


			}
			//
			hr  =  S_OK;  goto  errLabel;
		}

		//  2017/10/10
		int  iFourcc; iFourcc = 0;
		switch  (  iCodecType  )  {
				case  CONST_codecType_h264:
					  iFourcc  =  CONST_fourcc_h264;
					  break;
				case  CONST_codecType_HEVC:
					  iFourcc  =  CONST_fourcc_HEVC;
					  break;
				default:
						break;
		}

		//  2014/08/08
#if  0
		QMC_cfg_debugStatusInfo  *  pCfg_debugStatusInfo  =  pProcInfo->get_qmc_cfg_debugStatusInfo(  );
		if  (  pCfg_debugStatusInfo  
			&&  pCfg_debugStatusInfo->ucbShowRtspCliControl  )  
		{
			int  nalType  =  M_nalType_h264(  pBuffer  );
			TCHAR  tBuf[128];
			//
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  (TCHAR*)_T(  "nalType %d, %s"  ),  nalType,  qyGetDesByType1(  CONST_nalTypeTable_h264_en,  nalType  )  );
			myShowInfo(  pProcInfo,  0,  tBuf  );
			//
			//if  (  !pFrom->video.vh_stream_recvd.usCnt  )  
			{
			searchNalType(  pProcInfo,  iFourcc,  pBuffer,  BufferLen  );
			}
		}
#endif 


		//  2015/01/29
#ifdef  __DEBUG__
		#ifdef  __DUMP_h264_rtsp__
			    TCHAR  *  pDir  =  (TCHAR*)_T(  "c:\\tttbbb\\dd\\"  );		  						  		  
				TCHAR  *  fn  =  (TCHAR*)_T(  "kk_dvt_r.264"  );		

				static  BOOL  bFileHeadWritten  =  FALSE;
				if  (  !bFileHeadWritten  )  {
					bFileHeadWritten  =  TRUE;
					//
				    static  BOOL  bReset  =  FALSE;
					int  i;
					for  (  i  =  0;  i  <  pFrom->video.tv_recvd.vh_stream.usCnt;  i  ++  )  {
						 dumpVideo_init(  &bReset,  pDir,  fn,  pFrom->video.tv_recvd.vh_stream.mems[i].spsPps,  pFrom->video.tv_recvd.vh_stream.mems[i].usLen  );						  
					}
				}
				//
				dumpVideo(  pDir,  fn,  (  char  *  )pBuffer,  BufferLen  );
		#endif
		

#endif


#if  0
		//
	SHARED_OBJ_USR	*	pSharedObjUsr	=	getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
	if  (  !pSharedObjUsr  )  goto  errLabel;

	//
	if  (  !pVc->bCaptureStarted  )  {
#ifdef  __DEBUG__
		traceLog((TCHAR*)  (TCHAR*)_T(  "BufferCB_av_rtsp failed, bCaptureStarted is false"  )  );
#endif
		goto  errLabel;
	}
#endif


		//
		//CAP_procInfo_video	*	pCapProcInfo	=	pVc;
		myDRAW_VIDEO_DATA	*	p;
		int						len;

		//  len  =  offsetof(  myDRAW_VIDEO_DATA,  buf  )  +  pCapProcInfo->vh_org.bih.biSizeImage;
		len  =  sizeof(  myDRAW_VIDEO_DATA  );
#if  0
		if  (  len  >  m_var.uiBufSize_pBuf  ||  !m_var.pBuf  )  {
			showNotification(  NULL,  0,  0,  0,  0,  0,  (TCHAR*)_T(  "pBuf is null or buf too small, need allocated in bGetCapturePara(  ) first"  )  );
			traceLog((TCHAR*)  (TCHAR*)_T(  "pBuf is null or buf too small, need allocated in bGetCapturePara(  ) first"  )  );
			goto  errLabel;
		}
#endif
		myDRAW_VIDEO_DATA	tmp_myDRAW_VIDEO_DATA;
		p  =  &tmp_myDRAW_VIDEO_DATA;	//  (  myDRAW_VIDEO_DATA  *  )m_var.pBuf;
		if  (  !p  )  goto  errLabel;
		memset(  p,  0,  sizeof(  myDRAW_VIDEO_DATA  )  );	//  memset(  p,  0,  m_var.uiBufSize_pBuf  );
#if  0	//  def  __DEBUG__
		if  (  m_var.uiBufSize_pBuf  !=  sizeof(  myDRAW_VIDEO_DATA  )  )  {
			traceLog((TCHAR*)  (TCHAR*)_T(  "BufferCB_av, uiBufSize_pBuf is not correct"  )  );
			goto  errLabel;
		}
#endif

		//
#if  0
		if  (  setPktInputInfo(  (  CAP_procInfo_bmpCommon  *  )pVc1,  TRUE,  p  )  )  {
			#ifdef  __DEBUG__
					//  traceLog((TCHAR*)  (TCHAR*)_T(  "BufferCB_av: setPktInputInfo failed, skipped"  )  );
			#endif
			goto  errLabel;
		}
#endif
		//  2015/03/14
		p->input.bRtsp  =  TRUE;

		//
		BYTE* pInput; pInput = pBuffer;
		BITMAPINFO* pBmpInfo_input; pBmpInfo_input = (BITMAPINFO*)&pVc1->vh_org.bih;
		//
		unsigned  int  uiSize_dec; uiSize_dec = 0;
		//
		BOOL  bPkt_sharedTex; bPkt_sharedTex = FALSE;		//  2015/10/07
		//
		if  (  isPkt_sharedTex(  pTransform  )  )  {
			bPkt_sharedTex  =  TRUE;
		}

		//
		if  (  !bPkt_sharedTex  )  {
			//
			if  (  pVc1->vh_org.bih.biSizeImage  )  uiSize_dec  =  max(  pVc1->vh_org.bih.biSizeImage,  BufferLen  );
			else  {		//  2014/09/12
				  uiSize_dec  =  M_rgb24SizeImage(  pTransform->video.tv.vh_decompress.bih.biWidth,  pTransform->video.tv.vh_decompress.bih.biHeight  );
				  uiSize_dec  =  max(  uiSize_dec,  BufferLen  );
			}
			if  (  pVc1->bOrg2RgbBufInited  )  uiSize_dec  =  max(  uiSize_dec,  pVc1->vh_rgb.bih.biSizeImage  );
			//  2013/10/06
			//  uiSize_dec  =  max(  uiSize_dec,  M_sizeImage(  32,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight  )  );
		}

		//  2011/12/06
		unsigned  int  uiSize_enc; uiSize_enc = sizeof(TRANSFER_VIDEO_DATA);

		//
		p->head.uiLen  =  uiSize_dec  +  uiSize_enc;		//  pBmpInfo_input->bmiHeader.biSizeImage;	
		p->head.uiSampleTimeInMs  =  iSampleTimeInMs;
		p->head.uiPts  =  uiPts;	//  2015/02/09
		//
		p->uiSize_dec  =  uiSize_dec;
		//
		if  (  !mallocObj.mallocf(  CONST_iAllocType_video,  uiSize_dec  +  uiSize_enc  )  )  goto  errLabel;
		if  (  mallocObj.get(  &p->memory  )  )  goto  errLabel;

	    //  2011/12/04
		//  memcpy(  &p->bih,  &pVc->vh_org.bih,  sizeof(  p->bih  )  );
		p->bih.biCompression  =  CONST_fourcc_h264;
		TRANSFER_VIDEO_DATA* pReq; pReq = (TRANSFER_VIDEO_DATA*)(p->memory.m_pBuf + p->uiSize_dec);
		if  (  sizeof(  pReq->buf  )  <  BufferLen  )  goto  errLabel;
		memcpy(  pReq->buf,  pBuffer,  BufferLen  );  
		p->uiOffset_enc  =  offsetof(  TRANSFER_VIDEO_DATA,  buf  ); 
		p->uiLen_enc  =  BufferLen;

#if  0	//  在doEncVideo里有清0 
		TRANSFER_VIDEO_DATA  *  pReq  =  (  TRANSFER_VIDEO_DATA  *  )(  p->memory.m_pBuf  +  p->uiSize_dec  );
		memset(  pReq,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );
#endif

	    #if  1
			 p->debugInfo.dwTickCnt_start  =  GetTickCount(  );
			 M_pkt_setNo(  m_var.tn_pktNo,  m_var.lLastPktNo,  *p  );
		#endif
		//  2014/03/26
		M_set_pktId_alloc(  p  );

		//  2015/02/24
		if  (  pRes  )  {
			p->debugInfo.dwTickCnt_doPretrans  =  pRes->dwTickCnt_doPretrans;
		}


#ifdef  __DEBUG__
				 if  (  !p->input.tStartTran  )  {
#if  0
					 if  (  pCfg_debugStatusInfo
						 &&  pCfg_debugStatusInfo->ucbPrint_rtsp  )  
					 {
						 traceLog((TCHAR*)  (TCHAR*)_T(  "kk"  )  );
					 }
#endif 
				 }
				 //
		#if  0
				 TCHAR  tBuf[128];
				 _sntprintf(  tBuf,  mycountof(  tBuf  ),  (TCHAR*)_T(  "BufferCB_v_rtsp: uiSize_dec %d"  ),  uiSize_dec  );
				 _sntprintf(  tBuf,  mycountof(  tBuf  ),  (TCHAR*)_T(  "%s ucCompressors %d"  ),  tBuf,  (  int  )pTransform->video.tv.compressor.common.ucCompressors  );
				 _sntprintf(  tBuf,  mycountof(  tBuf  ),  (TCHAR*)_T(  "%s pktResType %d"  ),  tBuf,  (  int  )pTransform->video.u.qdcObjInfo.var.usPktResType_dec  );
				 showInfo_open0(  0,  0,  tBuf  );
		#endif

#endif


		//
		//  if  (  q2PostMsgAndTrigger(  p,  len,  &pCapProcInfo->thread.q2  )  )  goto  errLabel;
		if  (  q2PostMsgAndTrigger(  p,  len,  &pTransform->video.q2,  _T(  "BufferCB_v_rtsp"  )))  goto  errLabel;
		mallocObj.detach(    );

#endif

	hr  =  S_OK;

errLabel:
		
	return  hr;
}





unsigned int buf_to_uint32(const unsigned char* buf, int offset) {
	unsigned int value;
	memcpy(&value, buf + offset, sizeof(unsigned int));
	return value;
}


/////////////////
int  BufferCB_a_rtsp(  MC_VAR_common  *  pProcInfo,  void  *  pGBUF_rtspCliHelp,  int  iIndex_capProcInfo,  int  iMediumType,  int  iDataType, 
	int  iCodecType,  int  iSampleTimeInMs,  unsigned  int  uiPts,  unsigned  char  *  pBuffer,  long  BufferLen,  void  *  pMsgTaskBufParam,
	CB_rtsp_res  *  pRes  )
{
	HRESULT						hr					=	-1;
	//  
	QY_SHARED_OBJ			*	pSharedObj			=	NULL;


	CAP_procInfo_audioCommon		*	pCapAudio;

#if  1

	pCapAudio				=	(  CAP_procInfo_audioCommon  *  )getCapAudioBySth(  pProcInfo,  iIndex_capProcInfo,  0  );
	if  (  !pCapAudio  )  goto  errLabel;
	pSharedObj			=	getSharedObjByIndex(  pProcInfo,  pCapAudio->iIndex_sharedObj  );		//  ÕâÀïÒªÓÃindexÀ´»ñÈ¡
	if  (  !pSharedObj  )  goto  errLabel;
	if  (  !pSharedObj->pTransInfo_stream  )  goto  errLabel;
	TRANSINFO_stream* pTransInfo; pTransInfo = (TRANSINFO_stream*)pSharedObj->pTransInfo_stream;
	if  (  !pTransInfo->myTask.pMems_from  )  goto  errLabel;
	TASK_AV_FROM* pFrom; pFrom = &pTransInfo->myTask.pMems_from[0];

	//	
	QY_TRANSFORM* pTransform; pTransform = &pTransInfo->myTask.pTransforms[0];



	#ifdef  __DEBUG__
#if  0
			if  (  pProcInfo->cfg.debugStatusInfo.ucbPrint_rtsp  )  {
				traceLogA(  (char*)  "Grab_rtsp: video data, len %d, SampleTime %d",  BufferLen, iSampleTimeInMs  );
			}
#endif
	#endif

		//  

		if  (  iMediumType  !=  CONST_mediumType_audio  )  goto  errLabel;
		//  if  (  iCodecType  !=  CONST_codecType_h264  )  goto  errLabel;

		//  2014/02/25
		switch  (  iDataType  )  {
				case  CONST_vcfDataType_ucCompressors:
					  unsigned  char  ucCompressors;  ucCompressors  =  pBuffer[0];
						  pFrom->audio.ta_recvd.compressor.common.ucCompressors = ucCompressors;
						  pFrom->audio.ta_recvd.compressor.common.sample_fmt = ntohl(buf_to_uint32(pBuffer, 1));
						  //pCapAudio->ctxResample
						  pFrom->audio.ta_recvd.compressor.common.iAvgBitrateInKbps = ntohl(buf_to_uint32(pBuffer, 5));
						  					
					 
					  //pFrom->audio.uiModuleType_toDec
					  //QY_TRANSFORM;
					  if (!pFrom->audio.ta_recvd.uiTranNo_openAvDev) {
						  pFrom->audio.ta_recvd.uiTranNo_openAvDev = getuiNextTranNo(0, 0, 0);
					  }
					  hr  =  S_OK;  goto  errLabel;
					  break;
				case  CONST_vcfDataType_ah:
					  QY_AUDIO_HEADER  *  pAh;  pAh  =  (  QY_AUDIO_HEADER  *  )pBuffer;
					  if  (  pAh->wfx.wFormatTag  ==  WAVE_FORMAT_PCM  )  pFrom->audio.ta_recvd.ah_decompress  =  *pAh;
					  else  pFrom->audio.ta_recvd.ah_compress  =  *pAh;
					  //
					  if  (  pFrom->audio.ta_recvd.ah_decompress.wfx.wFormatTag  
						  &&  pFrom->audio.ta_recvd.ah_compress.wfx.wFormatTag
						  )
					  {
					  }
					  //
					  if  (  !pFrom->audio.ta_recvd.uiTranNo_openAvDev  )  {
						  pFrom->audio.ta_recvd.uiTranNo_openAvDev  =  getuiNextTranNo(  0,  0,  0  );
					  }

					  //
					  hr  =  S_OK;  goto  errLabel;			
					  break;
				default:
						break;
		}


		//  2014/08/08
		/*QMC_cfg_debugStatusInfo  *  pCfg_debugStatusInfo  =  pProcInfo->get_qmc_cfg_debugStatusInfo(  );
		if  (  pCfg_debugStatusInfo  
			&&  pCfg_debugStatusInfo->ucbShowRtspCliControl  )  
		{
		}*/


		//  2015/05/20
		{
			MIS_MSG_TASK* pMsgTaskBuf = (MIS_MSG_TASK*)pMsgTaskBufParam;
			MACRO_memset_misMsgTask(pMsgTaskBuf);
			//
			pMsgTaskBuf->uiType = CONST_misMsgType_task;
			//
			pMsgTaskBuf->pMisCnt = pProcInfo->getMisCntByName((TCHAR*)_T(""));


			//
			IM_CONTENTU* pContent = NULL;
			MIS_MSGU* pMsg = (MIS_MSGU*)pMsgTaskBuf;
			pContent = (IM_CONTENTU*)pMsg->task.data.buf;
			TRANSFER_AUDIO_DATA* pReq; pReq = &pContent->transferAudioData;
			memset(pReq, 0, offsetof(TRANSFER_AUDIO_DATA, buf));
			pReq->uiType = CONST_imCommType_transferAudioData;
			//
			pReq->uiTranNo_openAvDev = pFrom->audio.ta_recvd.uiTranNo_openAvDev;
			//
			if (BufferLen > sizeof(pReq->buf))  goto  errLabel;
			memcpy(pReq->buf, pBuffer, BufferLen);
			pReq->mems[0].uiSampleTimeInMs = iSampleTimeInMs;
			pReq->mems[0].uiLen = BufferLen;
			pReq->mems[0].idInfo.ui64Id = pProcInfo->pQyMc->curUsrInfo.common.id;
			pReq->uiLen = pReq->mems[0].uiLen;
			pReq->usCnt = 1;


			QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex((CCtxQmc*)pProcInfo, pTransInfo->index_taskInfo);
			if (!pTaskInfo)  goto  errLabel;
			QMC_taskData_conf* pTc; pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
			if (!pTc)  goto  errLabel;
			if (pTc->common.uiType != CONST_taskDataType_conf)  goto  errLabel;

			DLG_TALK_videoConferenceActiveMemFrom* pActiveMem; pActiveMem = &pTc->videoConference.activeMems_from[0];
			pActiveMem->avStream.obj.tranInfo.audio = pFrom->audio.ta_recvd;

			int						len;

			//  len  =  offsetof(  myDRAW_VIDEO_DATA,  buf  )  +  pCapProcInfo->vh_org.bih.biSizeImage;
			len = offsetof(TRANSFER_AUDIO_DATA, buf) + pReq->uiLen;

			pMsg->task.lenInBytes = offsetof(MIS_MSG_routeTalkData, buf) + len;
			//
			len = offsetof(MIS_MSG_TASK, data) + pMsg->task.lenInBytes;


			//
			if (q2PostMsgAndTrigger(pMsg, len, &pTransform->audio.q2, _T("BufferCB_a_rtsp")))  goto  errLabel;

		}

#endif

	hr  =  S_OK;

errLabel:
		
	return  hr;
}




//  2014/03/05
#ifdef  __DEBUG__


//typedef int  (*PF_BufferCB_rtsp)(void* pGBUF_rtspCliHelp, int  iIndex_capProcInfo, int  iMediumType, int  iCodecType, int  iSampleTimeInMs, unsigned  int  uiPts, int  iDataType, unsigned  char* pBuffer, long  BufferLen, bool  bSpsPps, int  index_spsPps, bool  bFinished_spsPps, bool  bNeedResp, CB_rtsp_res* pRes);

//int  BufferCB_av_rtsp_test_mp2t(  void  *  pGBUF_rtspCliHelp,  int  iIndex_capProcInfo,  int  iMediumType,  int  iCodecType,  int  iSampleTimeInMs,  unsigned  char  *  pBuffer,  long  BufferLen,  bool  bSpsPps,  int  index_spsPps,  bool  bFinished_spsPps,  CB_rtsp_res  *  pRes  )
int  BufferCB_av_rtsp_test_mp2t(void* pGBUF_rtspCliHelp, int  iIndex_capProcInfo, int  iMediumType, int  iCodecType, int  iSampleTimeInMs, unsigned  int  uiPts, int  iDataType, unsigned  char* pBuffer, long  BufferLen, bool  bSpsPps, int  index_spsPps, bool  bFinished_spsPps, bool  bNeedResp, CB_rtsp_res* pRes)
{
	HRESULT						hr					=	-1;
	//  
	QY_SHARED_OBJ			*	pSharedObj			=	NULL;


	CQyMalloc					mallocObj;
	
	CAP_procInfo_video		*	pVc1;

#if  0

	pVc1				=	(  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  iIndex_capProcInfo,  0  );
	if  (  !pVc1  )  goto  errLabel;
	pSharedObj			=	getSharedObjByIndex(  pProcInfo,  pVc1->iIndex_sharedObj  );		//  ÕâÀïÒªÓÃindexÀ´»ñÈ¡
	if  (  !pSharedObj  )  goto  errLabel;
	if  (  !pSharedObj->pTransInfo_stream  )  goto  errLabel;
	TRANSINFO_stream  *  pTransInfo  =  (  TRANSINFO_stream  *  )pSharedObj->pTransInfo_stream;
	if  (  !pTransInfo->myTask.pMems_from  )  goto  errLabel;
	TASK_AV_FROM  *  pFrom  =  &pTransInfo->myTask.pMems_from[0];


	#ifdef  __DEBUG__
			  traceLogA(  (char*)  "Grab_rtsp: video data, len %d, SampleTime %d",  BufferLen, iSampleTimeInMs  );
	#endif

		//  
		#if  0  //  def  __WINCE__
				if  (  pProcInfo->hWnd_testWebcam  !=  pSharedObj->hWnd_starter  )  {
					//  for winCe, localVideo don't need to be displayed
					goto  errLabel;
				}
		#endif

		DWORD  dwFourcc  =  0;
		if  (  iMediumType  !=  CONST_mediumType_video  )  goto  errLabel;

		switch  (  iCodecType  )  {
				case  CONST_codecType_h264:
					  dwFourcc  =  CONST_fourcc_h264;
					  break;
#if  0
				case  CONST_codecType_MP2T:
					  dwFourcc  =  CONST_fourcc_MP2T;
					  break;
#endif
				default:
					   goto  errLabel;
		}

		//  2014/02/25
		if  (  bSpsPps  )  {	//  把sps pps存起来
			pFrom->video.tv_recvd.vh_stream.dwFourcc  =  dwFourcc;
			if  (  !bFinished_spsPps  )  {
				//
				if  (  index_spsPps  >=  mycountof(  pFrom->video.tv_recvd.vh_stream.mems  )  )  goto  errLabel;
				//
				if  (  sizeof(  pFrom->video.tv_recvd.vh_stream.mems[index_spsPps].spsPps  )  <  BufferLen  )  goto  errLabel;
				memcpy(  pFrom->video.tv_recvd.vh_stream.mems[index_spsPps].spsPps,  pBuffer,  BufferLen  );
				pFrom->video.tv_recvd.vh_stream.mems[index_spsPps].usLen  =  BufferLen;			
				}
			else  {
				  if  (  index_spsPps  >  mycountof(  pFrom->video.tv_recvd.vh_stream.mems  )  )  goto  errLabel;
				  pFrom->video.tv_recvd.vh_stream.usCnt  =  index_spsPps;
				  pFrom->video.bGot_vh_stream  =  TRUE;			
				  pFrom->video.tv_recvd.compressor.common.ucCompressors  =  CONST_videoCompressors_stream;
				  pFrom->video.tv_recvd.uiTranNo_openAvDev  =  getuiNextTranNo(  0,  0,  0  );
				  //
				  #ifdef  __DUMP_h264_rtsp__
  						  static  BOOL  bReset  =  FALSE;

#if  0
						  char  *  fn  =  "c:\\tttbbb\\test\\kk.264";
						  FILE  *  fp  =  NULL;
						  if  (  !bReset  )  {
							  fp  =  fopen(  fn,  "w"  );
							  if  (  fp  )  {
								  fclose(  fp  );							
							  }
							  bReset  =  TRUE;							
						  }
						  fp  =  fopen(  fn,  "ab+"  );
						  if  (  fp  )  {
							  int  i;
							  for  (  i  =  0;  i  <  pFrom->video.vh_stream_recvd.usCnt;  i  ++  )  {
								   fwrite(  pFrom->video.vh_stream_recvd.mems[i].spsPps,  pFrom->video.vh_stream_recvd.mems[i].usLen,  1,  fp  );
							  }
							  fclose(  fp  );
						  }
#else
						  TCHAR  *  pDir  =  (TCHAR*)_T(  "c:\\tttbbb\\dd\\"  );
						  TCHAR  *  fn  =  (TCHAR*)_T(  "kk.264"  );
						  int  i;
						  for  (  i  =  0;  i  <  pFrom->video.tv_recvd.vh_stream.usCnt;  i  ++  )  {
							  dumpVideo_init(  &bReset,  pDir,  fn,  pFrom->video.tv_recvd.vh_stream.mems[i].spsPps,  pFrom->video.tv_recvd.vh_stream.mems[i].usLen  );
						  }

#endif

				  #endif

			}
			//
			hr  =  S_OK;  goto  errLabel;
		}

#ifdef  __DUMP_h264_rtsp__
#if  0
		char  *  fn  =  "c:\\tttbbb\\test\\kk.264";
		FILE  *  fp  =  NULL;
		fp  =  fopen(  fn,  "ab+"  );
		if  (  fp  )  {
		    fwrite(  pBuffer,  BufferLen,  1,  fp  );							
			fclose(  fp  );			
		}
		static  int  uiCnt_fn  =  0;
		uiCnt_fn  ++  ;
		if  (  uiCnt_fn  ==  2000  )  {
			int  i;
			i  =  1;
		}
#else

				TCHAR  *  pDir  =  (TCHAR*)_T(  "c:\\tttbbb\\dd\\"  );
				TCHAR  *  fn  =  (TCHAR*)_T(  "kk.264"  );

				
				dumpVideo(  pDir,  fn,  (  char  *  )pBuffer,  BufferLen  );

#endif
#if  1
		hr  =  S_OK;  goto  errLabel;
#endif
#endif

		//
		//CAP_procInfo_video	*	pCapProcInfo	=	pVc;
		myDRAW_VIDEO_DATA	*	p;
		int						len;

		//  len  =  offsetof(  myDRAW_VIDEO_DATA,  buf  )  +  pCapProcInfo->vh_org.bih.biSizeImage;
		len  =  sizeof(  myDRAW_VIDEO_DATA  );
#if  0
		if  (  len  >  m_var.uiBufSize_pBuf  ||  !m_var.pBuf  )  {
			showNotification(  NULL,  0,  0,  0,  0,  0,  (TCHAR*)_T(  "pBuf is null or buf too small, need allocated in bGetCapturePara(  ) first"  )  );
			traceLog((TCHAR*)  (TCHAR*)_T(  "pBuf is null or buf too small, need allocated in bGetCapturePara(  ) first"  )  );
			goto  errLabel;
		}
#endif
		myDRAW_VIDEO_DATA	tmp_myDRAW_VIDEO_DATA;
		p  =  &tmp_myDRAW_VIDEO_DATA;	//  (  myDRAW_VIDEO_DATA  *  )m_var.pBuf;
		if  (  !p  )  goto  errLabel;
		memset(  p,  0,  sizeof(  myDRAW_VIDEO_DATA  )  );	//  memset(  p,  0,  m_var.uiBufSize_pBuf  );
#if  0	//  def  __DEBUG__
		if  (  m_var.uiBufSize_pBuf  !=  sizeof(  myDRAW_VIDEO_DATA  )  )  {
			traceLog((TCHAR*)  (TCHAR*)_T(  "BufferCB_av, uiBufSize_pBuf is not correct"  )  );
			goto  errLabel;
		}
#endif

		//
#if  0
		if  (  setPktInputInfo(  (  CAP_procInfo_bmpCommon  *  )pVc1,  TRUE,  p  )  )  {
			#ifdef  __DEBUG__
					//  traceLog((TCHAR*)  (TCHAR*)_T(  "BufferCB_av: setPktInputInfo failed, skipped"  )  );
			#endif
			goto  errLabel;
		}
#endif
		//  p->input.bRtsp  =  TRUE;
		//
		BYTE			*	pInput						=	pBuffer;			  
		BITMAPINFO		*	pBmpInfo_input				=	(  BITMAPINFO  *  )&pVc1->vh_org.bih;
		//
		unsigned  int  uiSize_dec  =  0;
#if  10
		uiSize_dec  =  max(  pVc1->vh_org.bih.biSizeImage,  BufferLen  );
		if  (  pVc1->bOrg2RgbBufInited  )  uiSize_dec  =  max(  uiSize_dec,  pVc1->vh_rgb.bih.biSizeImage  );
		//  if  (  pVc->iPicBufSize  )  uiSize_dec  =  max(  uiSize_dec,  pVc->vh_pic.bih.biSizeImage  );
		//  2013/10/06
		//  uiSize_dec  =  max(  uiSize_dec,  M_sizeImage(  32,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight  )  );
#endif

		//  2011/12/06
		unsigned  int  uiSize_enc  =  sizeof(  TRANSFER_VIDEO_DATA  );

		//
		p->head.uiLen  =  uiSize_dec  +  uiSize_enc;		//  pBmpInfo_input->bmiHeader.biSizeImage;	
		p->head.uiSampleTimeInMs  =  iSampleTimeInMs;
		//
		p->uiSize_dec  =  uiSize_dec;
		//
		if  (  !mallocObj.mallocf(  CONST_iAllocType_video,  uiSize_dec  +  uiSize_enc  )  )  goto  errLabel;
		if  (  mallocObj.get(  &p->memory  )  )  goto  errLabel;

	    //  2011/12/04
		//  memcpy(  &p->bih,  &pVc->vh_org.bih,  sizeof(  p->bih  )  );
		p->bih.biCompression  =  dwFourcc;
		TRANSFER_VIDEO_DATA  *  pReq  =  (  TRANSFER_VIDEO_DATA  *  )(  p->memory.m_pBuf  +  p->uiSize_dec  );
		if  (  sizeof(  pReq->buf  )  <  BufferLen  )  goto  errLabel;
		memcpy(  pReq->buf,  pBuffer,  BufferLen  );  
		p->uiOffset_enc  =  offsetof(  TRANSFER_VIDEO_DATA,  buf  );
		p->uiLen_enc  =  BufferLen;

#if  0	//  在doEncVideo里有清0 
		TRANSFER_VIDEO_DATA  *  pReq  =  (  TRANSFER_VIDEO_DATA  *  )(  p->memory.m_pBuf  +  p->uiSize_dec  );
		memset(  pReq,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );
#endif

	    #if  1
			 p->debugInfo.dwTickCnt_start  =  GetTickCount(  );
			 M_pkt_setNo(  m_var.tn_pktNo,  m_var.lLastPktNo,  *p  );
		#endif
 		//  2014/03/26
		M_set_pktId_alloc(  p  );



#ifdef  __DEBUG__
				 if  (  !p->input.tStartTran  )  {
					 traceLog((TCHAR*)  (TCHAR*)_T(  "kk"  )  );
				 }
#endif

		QY_TRANSFORM  *  pTransform  =  &pTransInfo->myTask.pTransforms[0];

		//
		if  (  q2PostMsgAndTrigger(  p,  len,  &pTransform->video.q2  )  )  goto  errLabel;
		mallocObj.detach(    );
#endif
	

	hr  =  S_OK;

errLabel:
		
#ifdef  __DEBUG__
		hr  =  S_OK;
		//  for test
#endif

	return  hr;
}
#endif


#ifdef OVERRIDE_DECAUDIO_FUNCTION
#define decAudio_function_ mcThreadProc_decAudioRtsp
#else
DWORD WINAPI decAudio_function_(LPVOID lpParameter) {
	return 0;
}
#endif

//  2015/10/16
//  int  initVideoCapDev_rtsp(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiRtspType,  LPCTSTR  url_selected,  int  tn_rtspCliPipe,  BITMAPINFOHEADER  *  pBih_suggested,  BOOL  bForConfig,  HWND hWnd_notify,  int  iIndex_sharedObj,  void  **  ppVideoCapDevParam  )
int  initVideoCapDev_rtsp(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiRtspType,  LPCTSTR  url_selected,  int  tn_rtspCliPipe, 
	BITMAPINFOHEADER  *  pBih_suggested,  BOOL  bForConfig,  HWND hWnd_notify,  int  iIndex_sharedObj,  PARAM_initVideoCapDev_rtsp  *  pParam,  
	void  **  ppVideoCapDevParam  )
{
	int									iErr	=	-1;
	//
	MC_VAR_common				*		pProcInfo	=	pProcInfoCommon;	//
	HRESULT								hr;
	VIDEO_capDev_rtsp				*	p		=	NULL;
	
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
	if  (  !ppVideoCapDevParam  )  return  -1;
	if  (  *ppVideoCapDevParam  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initVideoCapDev_rtsp failed, *ppVideoCapDevParam is not null"  )  );
		return  -1;
	}


	//
	p  =  (  VIDEO_capDev_rtsp  *  )mymalloc(  sizeof(  VIDEO_capDev_rtsp  )  );
	if  (  !p  )  goto  errLabel;
	memset(  p,  0,  sizeof(  VIDEO_capDev_rtsp  )  );

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
	if  (  p->uiType  ==  CONST_rtspType_encV  )  {  //  2015/10/16
		if  (  pParam  )  {
			p->pQdcObjInfo  =  pParam->pQdcObjInfo;
		}
	}

	//
	DWORD  dwThreadDaemonId;
		
	//
	QY_SHARED_OBJ* pSharedObj; pSharedObj = getSharedObjByIndex(pProcInfo, iIndex_sharedObj);
	if  (  pSharedObj  )  {

		//
		TRANSINFO_stream  *  pTransInfo  =  (  TRANSINFO_stream  *  )pSharedObj->pTransInfo_stream;
		if  (  !pTransInfo  )  {
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "initVideoCapdev_rtsp failed, pSharedObj->pTransInfo_stream is null"  )  );
			#endif
			goto  errLabel;
		}
		if  (  !pTransInfo->myTask.pTransforms  )  goto  errLabel;
		QY_TRANSFORM  *  pTransform  =  &pTransInfo->myTask.pTransforms[0];

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
			showInfo_open0(  0,  0,  _T(  "initVideoCapDev_rtsp failed, trans.v.bQInited is false"  )  );
			goto  errLabel;
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

		if (!pTransform->audio.hThread) {
			//
			pTransform->audio.bQuit = FALSE;
			pTransform->audio.hThread = CreateThread(NULL, 0, decAudio_function_/*mcThreadProc_decAudio*/, pTransform, CREATE_SUSPENDED, &dwThreadDaemonId);

			if (pTransform->audio.hThread == NULL) {
				DWORD error = GetLastError();
				printf("CreateThread failed with error %d\n", error);
			}

			if (!pTransform->audio.hThread)  goto  errLabel;
			pTransform->audio.dwThreadId = dwThreadDaemonId;
			if (ResumeThread(pTransform->audio.hThread) == -1)  goto  errLabel;

			//  2012/03/25		
			InterlockedIncrement(&pStatus->nThreads_aTrans);
		}

	}

	//  2015/06/23
	p->hEvent_syncThreadQuit_recvRtsp  =  CreateEvent(  NULL,  FALSE,  FALSE,  NULL  );
	if  (  !p->hEvent_syncThreadQuit_recvRtsp  )  goto  errLabel;

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
		exitVideoCapDev_rtsp(  pProcInfoCommon,  (  void  **  )&p  );
	}
	if  (  !iErr  )  {
		*ppVideoCapDevParam  =  p;
	}


	 return  iErr;
}


 //int  exitVideoCapDev_rtsp(  void  **  ppVideoCapDevParam  )
 int  exitVideoCapDev_rtsp(  MC_VAR_common  *  pProcInfoCommon,  void  **  ppVideoCapDevParam  )
 {
	 //  
	 MC_VAR_common  *  pProcInfo  =  pProcInfoCommon;
	 //
	 VIDEO_capDev_rtsp  *  p	=	NULL;
	 TCHAR					tBuf[128]	=	_T(  "exitVideoCapDev_rtsp"  );

	if  (  !ppVideoCapDevParam  )  return  0;
	if  (  !*ppVideoCapDevParam  )  return  0;

	p  =  (  VIDEO_capDev_rtsp  *  )*ppVideoCapDevParam;


	//
	QMC_status  *  pStatus  =  pProcInfo->get_qmc_status(  );
	if  (  !pStatus  )  return  -1;


	//
	showInfo_open0(  0,  0,  _T(  "exitVideoCapDev_rtsp: to wait for thread_recvRtsp"  )  );

	//		
	if  (  p->hThread_recvRtsp  )  {			
		p->bQuit  =  TRUE;			
		//			 
		//  2015/06/22
		SetEvent(  p->hEvent_syncThreadQuit_recvRtsp  );
		//
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
	//  2015/06/23
	if  (  p->hEvent_syncThreadQuit_recvRtsp  )  {
		CloseHandle(  p->hEvent_syncThreadQuit_recvRtsp  );  p->hEvent_syncThreadQuit_recvRtsp  =  NULL;
	}

	//
	//
	QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  p->iIndex_sharedObj  );
	if  (  pSharedObj  )  {

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
						else  {
							  InterlockedDecrement(  &pStatus->nThreads_vTrans  );		 
						}
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
					else  {
						  InterlockedDecrement(  &pStatus->nThreads_vTrans  );		 
					}
				}	

				//
				if  (  pTransform->video.bQInited  )  exitQyQ2(  &pTransform->video.q2  );	
			}
		}
	}

	//
	if  (  p->bQInited_dvt_decV  )  {
		exitQyQ2(  &p->cacheQ2_dvt_decV  );  p->bQInited_dvt_decV  =  FALSE;
	}

	
errLabel:

	//
	free(  p  );
	*ppVideoCapDevParam  =  NULL;
	
	 return  0;
 }


 //
 BOOL  bGetCapturePara_rtsp(  void  *  pProcInfoParam,  int  iIndex_capBmp,  PF_BufferCB_av  pf,  unsigned  int  uiBufSize_pMsgBuf,  BOOL  bWait,  void  *  pVideoCapDevParam,  QY_VIDEO_HEADER  *  pVh_org  )
 {
	 BOOL	bRet  =  FALSE;
	 int	i;
	 CCtxQyMc* pQyMc = g_pQyMc;
	 MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pProcInfoParam;
	 CAP_procInfo_video  *  pVc1  =  NULL;
	 QY_SHARED_OBJ  *  pSharedObj  =  NULL;
	 DWORD				dwIntervalInMs_getVhStream  =  0;
	 
#if  10
	 pVc1				=	(  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );
	if  (  !pVc1  )  goto  errLabel;
	pSharedObj			=	getSharedObjByIndex(  pProcInfo,  pVc1->iIndex_sharedObj  );		//  ÕâÀïÒªÓÃindexÀ´»ñÈ¡
	if  (  !pSharedObj  )  goto  errLabel;
	if  (  !pSharedObj->pTransInfo_stream  )  goto  errLabel;
	TRANSINFO_stream* pTransInfo; pTransInfo = (TRANSINFO_stream*)pSharedObj->pTransInfo_stream;
	if  (  !pTransInfo->myTask.pMems_from  )  goto  errLabel;
	QY_TRANSFORM* pTransform; pTransform = &pTransInfo->myTask.pTransforms[0];
	TASK_AV_FROM* pFrom; pFrom = &pTransInfo->myTask.pMems_from[0];

	//  2015/01/28
#ifdef  __DEBUG__
#if  0
		for  (  i  =  0;  i  <  6000;  i  ++  )  {
			 if  (  pFrom->video.bGot_vh_stream  )  break;
			 Sleep(  1000  );
			 traceLog((TCHAR*)  _T(  "TEST: wait to get vh_stream"  )  );
		}
#endif
#endif
			 	 

	 //
		DWORD  dwTickCnt_last; dwTickCnt_last = GetTickCount();
	 //  等待6秒吧
	 int  maxWaits; maxWaits = 60;
#ifdef  __DEBUG__
	 if (0) {
		 maxWaits = 600000;
		 showInfo_open0(0, 0, _T("for test: bGetCapturePara_rtsp: maxWaits is 600000"));
	 }
#endif 
	 for  (  i  =  0;  i  <  maxWaits;  i  ++  )  {
		 if  (    pFrom->video.bGot_vh_stream  )  break;
		 //  2014/09/11
		 if  (  !bWait  )  goto  errLabel;
		 //
		 Sleep(  100  );
	 }
	 dwIntervalInMs_getVhStream  =  GetTickCount(  )  -  dwTickCnt_last;
	 if  (  !pFrom->video.bGot_vh_stream  )  {
		 myShowInfo(  pProcInfo,  0,  _T(  "bGetCapPara_rtsp failed: vh_stream not got"  )  );
		 goto  errLabel;
	 }
	 TCHAR  tBuf[128];
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "bGetCapPara_rtsp: vh_stream got, %dms"  ),  dwIntervalInMs_getVhStream  );
	 myShowInfo(  pProcInfo,  0,  tBuf  );


	 //
	 BOOL  bGot; bGot = FALSE;
	 //
	 dwTickCnt_last  =  GetTickCount(  );
	 for  (  i  =  0;  i  <  120;  i  ++  )  {
		  #ifdef  __DEBUG__
				  traceLog((TCHAR*)  _T(  "wait %d: w,h %d,%d"  ),i,  pTransform->video.tv.vh_decompress.bih.biWidth,  pTransform->video.tv.vh_decompress.bih.biHeight    );
		  #endif
		  if  (  pTransform->video.tv.vh_decompress.bih.biWidth  &&  pTransform->video.tv.vh_decompress.bih.biHeight  )  {			
			  bGot  =  TRUE;
			  break;			
		  }		  
		  //  2014/09/11
		  if  (  !bWait  )  goto  errLabel;
		  //
		  Sleep(  100  );
	 }
	 DWORD  dwIntervalInMs_get_wh; dwIntervalInMs_get_wh = GetTickCount() - dwTickCnt_last;
	 if  (  !bGot  )  {
		 myShowInfo(  pProcInfo,  0,  _T(  "bGetCapPara_rtsp failed: w, h not got"  )  );
		 goto  errLabel;
	 }
	 //
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "bGetCapPara_rtsp: wh %dx%d, %dms"  ),  pTransform->video.tv.vh_decompress.bih.biWidth,  pTransform->video.tv.vh_decompress.bih.biHeight,  dwIntervalInMs_get_wh  );
	 myShowInfo(  pProcInfo,  0,  tBuf  );
	 //
	 switch  (  pFrom->video.tv_recvd.vh_stream.dwFourcc  )  {
			 case  CONST_fourcc_h264:
			 case  CONST_fourcc_HEVC:  {
				   makeBmpInfoHeader_yv12(  12,  pTransform->video.tv.vh_decompress.bih.biWidth,  pTransform->video.tv.vh_decompress.bih.biHeight,  &pVh_org->bih  );
				   //
				   unsigned  char  ucHardwareAccl = get_ucHardwareAccl(pQyMc);
				   //
				   if (ucHardwareAccl == CONST_hdAccl_nv) {
					   makeBmpInfoHeader_yuv(CONST_fourcc_NV12,  12, pTransform->video.tv.vh_decompress.bih.biWidth, pTransform->video.tv.vh_decompress.bih.biHeight, &pVh_org->bih);
				   }
				   //
				   }
				   break;
			 default:
				     if  (  pFrom->video.tv_recvd.vh_compress.bih.biCompression  ==  CONST_fourcc_vp80  )  {		
						 makeBmpInfoHeader_i420(  12,  pTransform->video.tv.vh_decompress.bih.biWidth,  pTransform->video.tv.vh_decompress.bih.biHeight,  &pVh_org->bih  );
						 break;
					 }
					 //
					 myShowInfo(  pProcInfo,  0,  _T(  "bGetCapPara_rtsp failed: not h264 or h265 or vp8"  )  );
					 goto  errLabel;
	 }

#endif

	 bRet  =  TRUE;
errLabel:


	 return  bRet;
 }

  int  startCapture_rtsp(  void  *  pVideoCapDevParam  )
  {
	  int		iErr	=	-1;

	  iErr  =  0;

		return  iErr;
  }

 
  int  stopCapture_rtsp(  void  *  pVideoCapDevParam  )
 {
	 int		iErr	=	-1;

	 iErr  =  0;

	 return  iErr;
 }
