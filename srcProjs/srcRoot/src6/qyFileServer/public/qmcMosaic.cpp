
#include	"stdafx.h"
#include	<time.h>

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

#include	"myresource.h"

#include	"qyOpenShellCommon.h"
#include	"wallTalkers.h"
#include	"DlgShareDynBmpsProc.h"

#include	"dlgTalkProc.h"
#include	"qmcCmdProc.h"

//  #include	"DlgProgress.h"
#include	"tmpCeLib.h"

#include	"qyComPortEx.h"
#include	"qmcGpsProc.h"

#include	"myDb.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"isCliD3dPublic.h"
#include	"qmcMosaic.h"


//
int  makeMosaicStream(  HWND  hDlg,  int  iTaskId,  int  level,  AV_COMPRESSOR_CFG  *  pCompressor_conf,  AV_COMPRESSOR_CFG  *  pCompressor_resource,  int  iFourcc_resource,  QMC_mosaic_maker  *  pMosaic  )
{
	int		iErr	=	-1;
	
	//
	QY_MC						*	pQyMc					=	QY_GET_GBUF(  );
	MC_VAR_isCli				*	pProcInfo				=	QY_GET_procInfo_isCli(  );


	#ifdef  __DEBUG__
			traceLog(  _T(  "makeMosaicStream called"  )  );
	#endif

	//
	if  (  pMosaic->bInited  )  return  -1;

	//
	unsigned  int  uiObjType  =  CONST_objType_mosaicStream_video;
	//
	SHARE_dyn_bmp  *  pShareDynBmp  =  &pMosaic->video;
	//
	pShareDynBmp->resObj.uiObjType  =  uiObjType;
	pShareDynBmp->resObj.usIndex_obj  =  CONST_usIndex_photomosaic_video;
	//
	int  iW_mosaic  =  DEFAULT_iW_mosaic_sd;
	int  iH_mosaic  =  DEFAULT_iH_mosaic_sd;
	//
	if  (  pCompressor_conf->video.common.iHeight_pic  <=  DEFAULT_iH_mosaic_ld  )  {
		iW_mosaic  =  DEFAULT_iW_mosaic_ld;
		iH_mosaic  =  DEFAULT_iH_mosaic_ld;
		}
	else  if  (  pCompressor_conf->video.common.iHeight_pic  <  DEFAULT_iH_mosaic_hd  )  {
			  iW_mosaic  =  DEFAULT_iW_mosaic_sd;	
			  iH_mosaic  =  DEFAULT_iH_mosaic_sd;
	}
	else  if  (  pCompressor_conf->video.common.iHeight_pic  <  DEFAULT_iH_mosaic_fullHd  )  {
			  iW_mosaic  =  DEFAULT_iW_mosaic_hd;	
			  iH_mosaic  =  DEFAULT_iH_mosaic_hd;
			  }
	else  if  (  pCompressor_conf->video.common.iHeight_pic  <  DEFAULT_iH_mosaic_video4k  )  {
		  iW_mosaic  =  DEFAULT_iW_mosaic_fullHd;	
		  iH_mosaic  =  DEFAULT_iH_mosaic_fullHd;
	}
	else {
		iW_mosaic = DEFAULT_iW_mosaic_video4k;
		iH_mosaic = DEFAULT_iH_mosaic_video4k;
	}

	//
	makeBmpInfoHeader_rgb(  24,  iW_mosaic,  iH_mosaic,  &pShareDynBmp->bih_mosaic  );
	//
	if  (  toShareDynBmp(  pProcInfo,  hDlg,  NULL,  iTaskId,  pCompressor_conf,  0, NULL,  pShareDynBmp  )  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "makeSlaveStream failed: toShareDynBmp failed"  )  );
		#endif
		goto  errLabel;
	}

	//
	QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pShareDynBmp->var.iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	pSharedObj->usSubtype  =  CONST_sharedObjSubtype_mosaic;

	//  2014/11/13
	uiObjType  =  CONST_objType_mosaicStream_resource;
	//
	pShareDynBmp  =  &pMosaic->resource;
	//
	pShareDynBmp->resObj.uiObjType  =  uiObjType;
	pShareDynBmp->resObj.usIndex_obj  =  CONST_usIndex_photomosaic_resource;
	//  2008/11/16
	//
	unsigned  int  maxxScreen  =  0;
	unsigned  int  maxyScreen  =  0;
	//
#if  0
	HDC hScreenDC=::GetDC(NULL);
	maxxScreen = GetDeviceCaps(hScreenDC,HORZRES);
	maxyScreen = GetDeviceCaps(hScreenDC,VERTRES);		
	::ReleaseDC(NULL,hScreenDC);		
#endif
	PARAM_getScreenRes  param_getScreenRes  =  {0};
	param_getScreenRes.bService  =  pQyMc->appParams.bService;
	getScreenRes(  &param_getScreenRes,  &maxxScreen,  &maxyScreen  );
	//
	int  iW  =  maxxScreen;
	int  iH  =  maxyScreen;
	//
	//  2017/10/10
	//	
	iW  =  (  iW  /  4  )  *  4;		 		
	iH  =  (  iH  /  4  )  *  4;
	//
	makeBmpInfoHeader_rgb(  24,  iW,  iH,  &pShareDynBmp->bih_mosaic  );
	//
	if  (  toShareDynBmp(  pProcInfo,  hDlg,  NULL,  iTaskId,  pCompressor_resource,  iFourcc_resource,  NULL,  pShareDynBmp  )  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "makeSlaveStream failed: toShareDynBmp failed"  )  );
		#endif
		goto  errLabel;
	}

	//
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pShareDynBmp->var.iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	pSharedObj->usSubtype  =  CONST_sharedObjSubtype_mosaic;


	//
	//pMosaic->hEvent_syncQuit  =  CreateEvent(  NULL,  FALSE,  FALSE,  NULL  );
	//if  (  !pMosaic->hEvent_syncQuit  )  goto  errLabel;

	//
	pMosaic->param.iTaskId  =  iTaskId;

	//
	pMosaic->ucCnt_threads  =  mycountof(  pMosaic->threads  );
	int  i;
	for  (  i  =  0;  i  <  pMosaic->ucCnt_threads;  i  ++  )  {
		 //
		 QMC_mosaic_thread* pMosaicThread = &pMosaic->threads[i];
		 
		 //

		 //
		 pMosaicThread->hEvent_syncQuit  =  CreateEvent(  NULL,  FALSE,  FALSE,  NULL  );	
		 if  (  !pMosaicThread->hEvent_syncQuit  )  goto  errLabel;

		 //
		 DWORD  dwThreadDaemonId;
		 pMosaicThread->hThread  =  CreateThread(  NULL,  0,  mcThreadProc_readRtt,  pMosaic,  CREATE_SUSPENDED,  &dwThreadDaemonId  );		
		 if  (  !pMosaicThread->hThread  )  {
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "startQThread failed. CreateThread failed"  )  );
			 goto  errLabel;			
		 }
		 pMosaicThread->dwThreadId  =  dwThreadDaemonId;			
		 if  (  ResumeThread(  pMosaicThread->hThread  )  ==  -1  )  goto  errLabel;
	}

	//  2016/02/14
	pMosaic->bInited  =  TRUE;

	//
	iErr  =  0;

errLabel:


	return  iErr;
				  
}


int  stopMosaicThreads(  QMC_mosaic_maker  *  pMosaic  )
{
	int  i;

	//
	pMosaic->bQuit  =  TRUE;
	
	//
	for  (  i  =  0;  i  <  pMosaic->ucCnt_threads;  i  ++  )  {
		QMC_mosaic_thread* pMosaicThread = &pMosaic->threads[i];
		//
		SetEvent(  pMosaicThread->hEvent_syncQuit  );
	}
	//
	BOOL  bThreadExists  =  FALSE;
	int  j;
	for  (  j  =  0;  j  <  20;  j  ++  )  { 
		 bThreadExists  =  FALSE;
		for  (  i  =  0;  i  <  pMosaic->ucCnt_threads;  i  ++  )  {
			 QMC_mosaic_thread* pMosaicThread = &pMosaic->threads[i];
			 if  (  pMosaicThread->hThread  )  {
				 SetEvent(  pMosaicThread->hEvent_syncQuit  );
				 waitForObject(  &pMosaicThread->hThread,  200  );
				 if  (  pMosaicThread->hThread  )  {
					 bThreadExists  =  TRUE;
				 }
			 }
		}
		if  (  !bThreadExists  )  break;
	}
	//
	for (i = 0; i < pMosaic->ucCnt_threads; i++) {
		QMC_mosaic_thread* pMosaicThread = &pMosaic->threads[i];
		if (pMosaicThread->hEvent_syncQuit) {
			CloseHandle(pMosaicThread->hEvent_syncQuit);  pMosaicThread->hEvent_syncQuit = NULL;
		}
	}

	//
	if  (  bThreadExists  )  {
		qyExitProcess(  _T(  "stopMosaicThreads failed"  )  );
	}

	//
	return  0;

}

 int  openLocalVideo_mosaic(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiCamCapType,  BITMAPINFOHEADER  *  pBih_photomosaic,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressorParam,  int  iIndex_sharedObj  )
{
	int		iErr	=	-1;

	//
	QY_MC						*	pQyMc					=	QY_GET_GBUF(  );
	MC_VAR_isCli				*	pProcInfo				=	QY_GET_procInfo_isCli(  );
	int								iIndex_sharedObjUsr		=	0;
	QY_SHARED_OBJ				*	pSharedObj				=	NULL;
	int								iIndex_capBmp;
	CAP_procInfo_bmpCommon		*	pCapBmp					=	NULL;
	COMPRESS_VIDEO				*	pCompressVideo			=	NULL;
	unsigned  int					uiCapType				=	pVideoCompressorParam->common.uiCapType;

	//
	if  (  !pBih_photomosaic  )  return  -1;
	if  (  pBih_photomosaic->biWidth  <  MIN_iW_mosaic  ||  pBih_photomosaic->biWidth  >  MAX_iW_mosaic  )   return  -1;



	#ifdef  __DEBUG__
			traceLog(  _T(  "openLocalVideo_mosaic"  )  );
	#endif

	//
	

	//
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	iIndex_capBmp  =  pSharedObj->iIndex_capBmp;
	pCapBmp  =  (  CAP_procInfo_bmpCommon  *  )getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );
	if  (  !pCapBmp  )  goto  errLabel;
	pCompressVideo  =  &pCapBmp->compressVideo;
	

	
	//  2014/09/10
	memcpy(  &pCompressVideo->compressor,  pVideoCompressorParam,  sizeof(  pCompressVideo->compressor  )  );
	VIDEO_COMPRESSOR_CFG  *  pVideoCompressor  =  &pCompressVideo->compressor;

	//
	pVideoCompressor->common.iWidth_pic  =  min(  1920  *  2,  pBih_photomosaic->biWidth  );		
	pVideoCompressor->common.iHeight_pic  =  min(  1080  *  2,  pBih_photomosaic->biHeight  );
	
	//
	BOOL	bAudio  =  FALSE;	//  CAP_STUFF_bAudio(  *ppCapStuff  );
	BOOL	bVideo  =  TRUE;	//  CAP_STUFF_bVideo(  *ppCapStuff  );

	//  2014/09/23
	//memcpy(  &pCapBmp->vh_org.bih,  &pCapBmp_master->compressVideo.vh_decompress.bih,  sizeof(  pCapBmp->vh_org.bih  )  );
	makeBmpInfoHeader_rgb(  24,  pBih_photomosaic->biWidth,  pBih_photomosaic->biHeight,  &pCapBmp->vh_org.bih  );


	//
	if  (  bVideo  )  {
		CAP_procInfo_bmpCommon	*	pVc  =  pCapBmp;

		//
		if  (  pVc->vh_org.bih.biCompression  !=  BI_RGB  ||  pVc->vh_org.bih.biBitCount  !=  24  )  {
			if  (  initOrg2RgbBuf(  (  MC_VAR_common  *  )pProcInfo,  pVc  )  )  {
				traceLogA(  "initOrg2RgbBuf failed."  );
				goto  errLabel;		
			}
		}

		QY_VIDEO_HEADER	*	pVh_rgb;
		pVh_rgb  =  pVc->bOrg2RgbBufInited  ?  &pVc->vh_rgb  :  &pVc->vh_org;
		//
		QY_VIDEO_HEADER  vh_dec  =  *pVh_rgb;
		//
		switch  (  pCompressVideo->compressor.common.ucCompressors  )  {
				case  CONST_videoCompressors_hwAccl:
					  unsigned  char  ucHardwareAccl;
					  ucHardwareAccl  =  get_ucHardwareAccl(pQyMc  );
					  if  (  ucHardwareAccl  ==  CONST_hdAccl_nv  )  {
						  makeBmpInfoHeader_i420(  12,  pVh_rgb->bih.biWidth,  pVh_rgb->bih.biHeight,  &vh_dec.bih  );
					  }
					  break;
				default:
						break;
		}

		//
		pVideoCompressor->adapterLuid_LowPart = pProcInfo->av.gpu.adapterLuid_LowPart;
		pVideoCompressor->adapterLuid_HighPart = pProcInfo->av.gpu.adapterLuid_HighPart;

		//
		//  2014/04/03
		pVideoCompressor->common.pVideoQ2  =  &pVc->thread.q2;
		pVideoCompressor->common.pParent_transform  =  pVc;
		//  2016/04/02
		_sntprintf(  pCompressVideo->tag_dbg,  mycountof(  pCompressVideo->tag_dbg  ),  _T(  "capBmp%d mosaic"  ),  iIndex_capBmp  );
		//
		if  (  initCompressVideo(  pProcInfo,  (  BITMAPINFO  *  )&vh_dec.bih,  uiCapType,  pVideoCompressor,  FALSE,  0,  pCompressVideo  )  )  {
			showNotification(  NULL,  0,  0,  0,  0,  0,  _T(  "open mosaic: init video compress failed!"  )  );  
			goto  errLabel;
		}
	}
		
	
	//
	iErr  =  0;

errLabel:

	//  2013/03/01
	//  sizeAllControls_dlgTalk(  hDlg,  m_var,  NULL  );					//  µ÷ÕûÒ»ÏÂ²¼¾Ö
	//askToRefreshLayout_mgr(  hDlg  );

	return  iErr;
				  
}




extern "C" DWORD WINAPI mcThreadProc_readRtt( LPVOID lpParameter )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_doProc_readRtt(  lpParameter  );

}



//2014/11/16
 int  setFlg_inConfMosaic(  HWND  hDlg,  int  iWndContentType,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr  )
{
	int  iErr  =  -1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  return  -1;

	if  (  iWndContentType  ==  CONST_qyWndContentType_talker  )  {
		CHelp_getDlgTalkVar	help_getDlgTalkVar;
		DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlg  );
		if  (  !pDlgTalkVar  )  goto  errLabel;
		DLG_TALK_var  &  m_var  =  *pDlgTalkVar;

		//
		if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
			if  (  m_var.av.taskInfo.bTaskExists  &&  m_var.av.taskInfo.mosaicMaker.video.resObj.uiObjType  )  {
				SHARED_OBJ_USR	*	pSharedObjUsr			=	NULL;
		  		
				pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  iIndex_sharedObjUsr  );
				if  (  !pSharedObjUsr  )  goto  errLabel;

				//
				pSharedObjUsr->ucbInConfMosaic  =  TRUE;
			}
		}

	}

	iErr  =  0;

errLabel:
	return  iErr;
}

