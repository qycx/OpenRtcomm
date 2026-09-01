

#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>

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

#include	"qmcCommFunc_isCli.h"

//
#include	"qmcVideoCapture_rtsp.h"




//
int  getModuleTypeBySth_toEnc(  CCtxQmc  *  pProcInfo,  unsigned  char  ucCompressors    )
{
	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;
	CCtxQyMc* pQyMc = g_pQyMc;

	//
	unsigned  int  uiModuleType  =  0;

	//	
	switch  (  ucCompressors  )  {
				  case  CONST_videoCompressors_ipp:		//  2011/07/31
						//  
					    uiModuleType  =  CONST_moduleType_ipp;
						//
						break;
				  case  CONST_videoCompressors_hwAccl:
					    //  
					    uiModuleType  =  CONST_moduleType_mediaSdk_enc;
						//
						//
						if (1) {
							TCHAR  tBuf[128];
							_sntprintf(tBuf, mycountof(tBuf), _T("qmcCfg.policy.ucHw %d, confReq.ucHw %d"), (int)pQmcCfg->policy.ucHardwareAccl, (int)pProcInfo->av.doConf.confReq.ucHardwareAccl);
							showInfo_open0(0, 0, tBuf);
						}
						//  2014/07/05
						//switch  (  pQmcCfg->policy.ucHardwareAccl  )  
						switch  (  get_ucHardwareAccl(pQyMc)  ){
							    case  0:						
							    case  CONST_hdAccl_nv:
									  uiModuleType  =  CONST_moduleType_enc_nv;				
									  //
									  if (pQyMc->appParams.bUse_encD3d_nv) {
										  uiModuleType = CONST_moduleType_encD3d_nv;
									  }
									  //
									  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Adjusted: for nv, use nv to enc haccl h264."  )  );				   
									  break;
								case  CONST_hdAccl_amf:
									  uiModuleType  =  CONST_moduleType_enc_amf;
									  //
									  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Adjusted: for amf, use amf to enc haccl h264."  )  );				   
									  break;
								default:
										break;					   
						}
						//
						break;
#if  0
				  case  CONST_videoCompressors_cuda:	//  2012/06/18
					    //  
					    uiModuleType  =  CONST_moduleType_enc_nv;	
					    break;
#endif
				  case  CONST_videoCompressors_vp8:		//  2014/07/19
					    //
					    uiModuleType  =  CONST_moduleType_enc_vp8;	
					    break;
				  case  CONST_videoCompressors_custom:
					    //  
					    uiModuleType  =  CONST_moduleType_compress;
					    break;
				  default:
						#ifdef  __DEBUG__
								traceLogA(  (char*)  "initCompressVideo: ucCompressors err: %d",  ucCompressors  );
						#endif
						qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initCompressVideo: ucCompressors err: %d"  ),  ucCompressors  );
						goto  errLabel;
						break;
		  }

errLabel:

	return  uiModuleType;
}







 //  2014/09/28
 //
 int  toShareDynBmp(  CCtxQmc  *  pProcInfo,  HWND  m_hWnd,  void  **  ppCapStuff,  int  iTaskId_suggested,  AV_COMPRESSOR_CFG  *  pCompressor_suggested,  int  iFourcc_suggested,  TASK_av_props  *  pTaskAvProps,  SHARE_dyn_bmp  *  pDynBmpMem  )
{
	
	int								iErr					=	-1;

	if  (  !pProcInfo  )  return  -1;
	QY_MC						*	pQyMc					=	pProcInfo->pQyMc;
	//
	int								iIndex_sharedObj		=	-1;
	int								iIndex_sharedObjUsr		=	-1;
	QY_SHARED_OBJ				*	pSharedObj				=	NULL;
	int								iIndex_capBmp			=	-1;
	CAP_procInfo_bmpCommon		*	pCapBmp					=	NULL;
	COMPRESS_VIDEO				*	pCompressVideo			=	NULL;	
	//  2015/05/18
	int								iIndex_capAudio;
	CAP_procInfo_audioCommon	*	pCapAudio				=	NULL;
	COMPRESS_AUDIO				*	pCompressAudio			=	NULL;
	//
#if  0
	int								iIndex_shmCmd			=	-1;
	QM_SHM_CMD					*	pShmCmd					=	NULL;
#endif
	//
	//  VIDEO_COMPRESSOR_CFG			videoCompressor;
	AV_COMPRESSOR_CFG				avCompressor;						//  2015/05/18
	//
	unsigned  int					uiTaskType				=	0;
	unsigned  int					uiSharedObjType			=	0;		//  2014/12/01
	unsigned  int					uiCapType				=	0;
	unsigned  int					uiSubCapType			=	0;
	int								iCapUsage				=	0;		//  2014/11/14

	//
	if  (  !pDynBmpMem  )  return  -1;
		
	//
	if  (  pDynBmpMem->var.internalProcess.bInProcess  )  {
		showInfo_open0(  0,  0,  _T(  "dlgShareDynBmps_toShareDynBmp failed: bInProcess true"  )  );
		return  -1;
	}
	
	//
	unsigned  int  uiObjType  =  pDynBmpMem->resObj.uiObjType;
	//
	uiSharedObjType  =  CONST_sharedObjType_webcam_vOnly;
	uiCapType  =  CONST_capType_av;
	uiSubCapType  =  CONST_subCapType_webcam;


	//
	switch  (  uiObjType  )  {
			case  CONST_objType_webcam:
				  if  (  !pDynBmpMem->iMenuId  )  {
						#ifdef  __DEBUG__
								traceLog((TCHAR*)  _T(  "dlgShareDynBmps_toShareDynBmp failed, iMenuId err"  )  );
						#endif
						goto  errLabel;				 
				  }
				  //
				  uiSharedObjType  =  CONST_sharedObjType_webcam_av;	//  2015/05/18
				  //					
				  break;
			case  CONST_objType_rtspStream:
				  uiSharedObjType  =  CONST_sharedObjType_rtsp;			//  2015/10/11
				  break;
			case  CONST_objType_smallStream:								//  2014/09/29
				  uiCapType  =  CONST_capType_slave;					//  2016/04/06
				  uiSubCapType  =  CONST_subCapType_slave_video;		//  2016/04/06
				  break;
			case  CONST_objType_ic:
				  uiSharedObjType = CONST_sharedObjType_ic;
				  break;
			case  CONST_objType_mosaicStream_video:
				  uiSharedObjType  =  CONST_sharedObjType_mosaic;
				  uiCapType  =  CONST_capType_mosaic;
				  uiSubCapType  =  CONST_subCapType_mosaic_video;
				  break;
			case  CONST_objType_mosaicStream_resource:
				  uiSharedObjType  =  CONST_sharedObjType_mosaic;
				  uiCapType  =  CONST_capType_mosaic;
				  uiSubCapType  =  CONST_subCapType_mosaic_resource;
				  break;
			case  CONST_objType_qvcf:	//  2015/05/09		
				  uiSharedObjType  =  CONST_sharedObjType_qvcf;
				  uiCapType  =  CONST_capType_qvcf;	//  2015/05/25
				  break;
			default:
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "dlgShareDynBmps_toShareDynBmp: uiObjType %d err"  ),  uiObjType  );
							MACRO_qyAssert(  0,  _T(  "toShareDynBmp failed, objType err"  )  );
					#endif
					return  -1;
					break;
	}

	
	#ifdef  __DEBUG__
	#endif
	
	iIndex_sharedObj  =  newSharedObjIndex(  pProcInfo,  m_hWnd,  uiSharedObjType,  &iIndex_sharedObjUsr,  NULL  );
	if  (  iIndex_sharedObj  <  0  )  goto  errLabel;
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	//  pSharedObj->uiCapType  =  CONST_capType_av;
	//pSharedObj->uiType  =  uiSharedObjType;	//  _webcam;
	iIndex_capBmp  =  newCapProcInfoBmpIndex(  pProcInfo,  iIndex_sharedObj  );
	pCapBmp  =  (  CAP_procInfo_bmpCommon  *  )getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );
	if  (  !pCapBmp  )  goto  errLabel;
	pCapBmp->uiType  =  uiCapType;		//  CONST_capType_av;
	pCapBmp->uiSubtype = uiSubCapType;
	pCapBmp->iIndex_sharedObj  =  iIndex_sharedObj;
	pCapBmp->uiTranNo_sharedObj  =  pSharedObj->uiTranNo;
	pCompressVideo  =  &pCapBmp->compressVideo;
	//  2015/05/18
	iIndex_capAudio  =  newCapProcInfoAudioIndex(  pProcInfo,  iIndex_sharedObj  );
	pCapAudio  =  (  CAP_procInfo_audioCommon  *  )getCapAudioBySth(  pProcInfo,  iIndex_capAudio,  0  );
	if  (  !pCapAudio  )  goto  errLabel;
	pCapAudio->uiType  =  uiCapType;
	pCapAudio->iIndex_sharedObj  =  iIndex_sharedObj;
	pCapAudio->uiTranNo_sharedObj  =  pSharedObj->uiTranNo;
	pCompressAudio  =  &pCapAudio->compressAudio;
	//
#if  0
	iIndex_shmCmd  =  newShmCmdIndex(  pProcInfo,  iIndex_sharedObj  );
	pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  iIndex_shmCmd  );
	if  (  !pShmCmd  )  goto  errLabel;
#endif

	//
	pSharedObj->iIndex_capBmp  =  iIndex_capBmp;
	pSharedObj->iIndex_capAudio  =  iIndex_capAudio;
	//pSharedObj->iIndex_shmCmd  =  iIndex_shmCmd;

#if  10  //  2015/10/11
	BOOL  bAudio; bAudio = TRUE;
	if  (  newstartQThreadToShareAv(  pProcInfo,  iIndex_sharedObj,  bAudio  )  )  {
		goto  errLabel;		
	}	
#endif

	//  2015/10/11
#ifdef  __DEBUG__
		#if  0
			 traceLog((TCHAR*)  _T(  "No use, sleep( 10000  )"  )  );
			 Sleep(  10000  );
		#endif
#endif


	//
	uiTaskType  =  CONST_imTaskType_shareDynBmp;

	if  (  pCompressor_suggested  )  {
		memcpy(  &avCompressor,  pCompressor_suggested,  sizeof(  avCompressor  )  );
		}
	else  {	
		  //  2011/08/07
		  //AV_COMPRESSOR_CFG	webcamCompressor;
		  memset(  &avCompressor,  0,  sizeof(  avCompressor  )  );
		  
		  //  if  (  myGetAvCompressorCfg(  CONST_capType_av,  CONST_subCapType_webcam,  iCapUsage,  0,  &webcamCompressor  )  )  goto  errLabel;
		  if  (  myGetAvCompressorCfg(  uiCapType,  uiSubCapType,  iCapUsage,  0,  &avCompressor  )  )  {
			  #ifdef  __DEBUG__
					  traceLog((TCHAR*)  _T(  "toShareDynBmp failed, myGetAvCompressorCfg failed"  )  );
			  #endif
			  goto  errLabel;
		  }

		  if (CONST_objType_rtspStream == uiObjType) {
			  avCompressor.video.common.ucCompressors = CONST_videoCompressors_hwAccl;
			  avCompressor.video.common.iWidth_pic = 1920;
			  avCompressor.video.common.iHeight_pic = 1080;
			  iFourcc2Str(CONST_fourcc_HEVC, avCompressor.video.common.fourccStr, mycountof(avCompressor.video.common.fourccStr));
			  avCompressor.video.common.iAvgBitrate = 1500000;
		  }

		  //
		  if  (  iFourcc_suggested  )  {
			  iFourcc2Str(  iFourcc_suggested,  avCompressor.video.common.fourccStr,  mycountof(  avCompressor.video.common.fourccStr  )  );
			  switch  (  iFourcc_suggested  )  {
					  case  CONST_fourcc_vp80:
						    avCompressor.video.common.ucCompressors  =  CONST_videoCompressors_vp8;
						    break;
					  default:
							  break;
			  }
		  }
		  
		  //  2009/06/04
		  //memcpy(  &videoCompressor,  &webcamCompressor.video,  sizeof(  videoCompressor  )  );
	}
	//  2012/06/12
	avCompressor.video.common.uiCapType  =  uiCapType;			//  CONST_capType_av;
	avCompressor.video.common.uiSubCapType  =  uiSubCapType;	//  CONST_subCapType_webcam;

	//
#if  0
	if  (  pCapBmp->bCapDevConnected  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgSharedWebcams::toShareWebcam failed, bCapDevConntected true."  )  );
		goto  errLabel;
	}
#endif

	//  		
	//  2014/04/06		
	unsigned  int  uiCamCapType; uiCamCapType = CONST_camCapType_directX;
	switch  (  uiObjType  )  {
			case  CONST_objType_rtspStream:  
				  uiCamCapType  =  CONST_camCapType_rtsp;
				  break;
			case  CONST_objType_smallStream:	//  2014/09/29
				  uiCamCapType  =  CONST_camCapType_slave;
				  break;
			case  CONST_objType_mosaicStream_video:		//  2014/10/30
			case  CONST_objType_mosaicStream_resource:	//  2014/10/30
				  uiCamCapType  =  CONST_camCapType_mosaic;
				  break;
			case  CONST_objType_qvcf:					//  2015/05/09
				  uiCamCapType  =  CONST_camCapType_qvcf;
				  break;
			case  CONST_objType_ic:
				  uiCamCapType = CONST_camCapType_ic;
				  break;
			default:
					break;
	}

	//  2015/10/21
	BOOL  bSupported_pktResType_sharedTex; bSupported_pktResType_sharedTex = FALSE;
	if  (  uiCamCapType  ==  CONST_camCapType_mosaic  )  {  //  it means pkt of source can be sharedTex
		//
		unsigned short  usPktResType_src  =  CONST_pktResType_sharedTex;
		unsigned int  uiModuleType  =  getModuleTypeBySth_toEnc(  pProcInfo,  avCompressor.video.common.ucCompressors  );
		//
		unsigned  short  usPktResType_suggested  =  0;	//  pProcInfo->get_pktResType_suggested(  CONST_pktUsage_enc,  uiModuleType  );
		if  (  pProcInfo->get_pktResType_toEnc(  usPktResType_src,  uiModuleType,  fourccStr2i(  avCompressor.video.common.fourccStr  ),  &usPktResType_suggested  )  )  {
			goto  errLabel;
		}
		//
		//  2017/10/13
		TCHAR  tBuf[128];
		
		//
		_sntprintf(tBuf, mycountof(tBuf), _T("toShareDynBmp: mosaic: moduleType %d, "), uiModuleType);
		showInfo_open0(0, 0, tBuf);
		
		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "mosaic: pktResType_src %d, fourcc %S, pktResType_suggest %d......"  ),  (  int  )usPktResType_src,  avCompressor.video.common.fourccStr,  (  int  )usPktResType_suggested  );
		showInfo_open0(  0,  0,  tBuf  );
		//
#if  0
		if  (  usPktResType_suggested  ==  CONST_pktResType_sharedTex  )  {
			//
			int  propId  =  CONST_qdcPropId_bSupport_sharedTex_enc;
			//
			BOOL  bVal  =  FALSE;
			if  (  !getVal_bSupported_pktResType_sharedTex(  pProcInfo,  uiModuleType,  propId,  &bVal  )  
				&&  bVal  )
			{
				bSupported_pktResType_sharedTex  =  TRUE;
				//  2015/11/01
				avCompressor.video.common.usPktResType_suggested  =  CONST_pktResType_sharedTex;
			}
		}
#endif
		//
		if  (  usPktResType_suggested  ==  CONST_pktResType_sharedTex  )  {
				bSupported_pktResType_sharedTex  =  TRUE;
				//  2015/11/01
				avCompressor.video.common.usPktResType_suggested  =  CONST_pktResType_sharedTex;
		}

	}


	//
	pDynBmpMem->var.iIndex_sharedObj  =  iIndex_sharedObj;		
	pDynBmpMem->var.iIndex_sharedObjUsr  =  iIndex_sharedObjUsr;	//  2014/09/11
	pDynBmpMem->var.uiTaskType  =  uiTaskType;						//  2014/09/11
	pDynBmpMem->var.ucbUsed_iIndex_sharedObj  =  TRUE;				//  2014/09/11
	//
	pDynBmpMem->var.bSupported_pktResType_sharedTex3  =  bSupported_pktResType_sharedTex;	//  2015/10/21
	//
	if  (  pTaskAvProps  )  {  //  2015/10/23
		memcpy(  &pDynBmpMem->var.taskAvProps,  pTaskAvProps,  sizeof(  pDynBmpMem->var.taskAvProps  )  );
	}
	//
	pDynBmpMem->var.dwTickCnt_start  =  GetTickCount(  );			//  2014/09/12

	//  2015/05/18
	pDynBmpMem->bVideoExists  =  TRUE;

	//
	switch  (  uiCamCapType  )  {
			case  CONST_camCapType_rtsp:  {

				  if  (  prepareForOpeningRtsp(  pProcInfo,  iIndex_sharedObj  )  )  goto  errLabel;

				  pDynBmpMem->bAudioExists = true;

				  //
				  unsigned  int  uiRtspType  =  0;
				  TCHAR  *  url  =  pDynBmpMem->name;	//  pShare->mems[index_pShare_mem].name;		
				  int  tn_rtspCliPipe  =  getuiNextTranNo(  0,  0,  0  );
				  //
				  //  2015/05/09
				  if  (  pDynBmpMem->resObj.uiObjType  ==  CONST_objType_qvcf  )  {
					  uiRtspType  =  CONST_rtspType_qvcf;
				  }

				  //  2014/09/11
				  TCHAR  tHint[128];
				  _sntprintf(  tHint,  mycountof(  tHint  ),  _T(  "ind_share_mem %d"  ),  0  );
				  //
				  BOOL  bCapDev  =  FALSE;  //  2015/10/11
				  //
				  if  (  openLocalVideo_rtsp_step0(  (  MC_VAR_common  *  )pProcInfo,  uiRtspType,  url,  tn_rtspCliPipe,  &avCompressor.video,  tHint,  bCapDev,  iIndex_sharedObj  )  )  {						
					  #ifdef  __DEBUG__
							  traceLogA(  (char*)  "CDlgSharedWebcamps::toShare: openLocalVideo_rtsp failed."  );
					  #endif							
					  goto  errLabel;		
				  }
				  memset(  &pDynBmpMem->var.internalProcess,  0,  sizeof(  pDynBmpMem->var.internalProcess  )  );
				  pDynBmpMem->var.internalProcess.bInProcess  =  TRUE;
				  pDynBmpMem->var.internalProcess.dwTickCnt_start  =  GetTickCount(  );
				  pDynBmpMem->var.internalProcess.nStep  =  CONST_shareDynBmpMem_step_0;
				  //
				  pDynBmpMem->var.internalProcess.iTaskId_suggested = iTaskId_suggested;
				  
				  //  中间要退出了，等异步处理		
				  iErr  =  0;  goto  errLabel;
		
				  }			
				  break;
				  //
			case  CONST_camCapType_qvcf:  {		//  2015/05/11

				  if  (  prepareForOpeningRtsp(  pProcInfo,  iIndex_sharedObj  )  )  goto  errLabel;

				  //
				  unsigned  int  uiRtspType  =  0;
				  TCHAR  *  url  =  pDynBmpMem->name;	//  pShare->mems[index_pShare_mem].name;		
				  int  tn_rtspCliPipe  =  getuiNextTranNo(  0,  0,  0  );
				  //
				  //  2015/05/09
				  if  (  pDynBmpMem->resObj.uiObjType  ==  CONST_objType_qvcf  )  {
					  uiRtspType  =  CONST_rtspType_qvcf;
				  }

				  //  2014/09/11
				  TCHAR  tHint[128];
				  _sntprintf(  tHint,  mycountof(  tHint  ),  _T(  "ind_share_mem %d"  ),  0  );
				  if  (  openLocalQvcf_rtsp_step0(  (  MC_VAR_common  *  )pProcInfo,  uiRtspType,  url,  tn_rtspCliPipe,  &avCompressor.video,  tHint,  iIndex_sharedObj  )  )  {						
					  #ifdef  __DEBUG__
							  traceLogA(  (char*)  "CDlgSharedWebcamps::toShare: openLocalVideo_rtsp failed."  );
					  #endif							
					  goto  errLabel;		
				  }
#if  0
				  memset(  &pDynBmpMem->var.internalProcess,  0,  sizeof(  pDynBmpMem->var.internalProcess  )  );
				  pDynBmpMem->var.internalProcess.bInProcess  =  TRUE;
				  pDynBmpMem->var.internalProcess.dwTickCnt_start  =  GetTickCount(  );
				  pDynBmpMem->var.internalProcess.nStep  =  CONST_shareDynBmpMem_step_0;
				  
				  //  中间要退出了，等异步处理		
				  iErr  =  0;  goto  errLabel;
#endif
				  if  (  openLocalVideo_rtsp_step1(  pProcInfo,  url,  TRUE,  _T(  ""  ),  iIndex_sharedObj  )  )  {
					  goto  errLabel;
				  }				  
				  if  (  openLocalVideo_rtsp_step2(  pProcInfo,  url,  tHint,  iIndex_sharedObj  )  )  {
					  goto  errLabel;
				  }

		
				  }			
				  break;
				  //
			case  CONST_camCapType_directX:  {
				   #ifdef  __useMfc__
						    CWaitCursor		cur;
				   #endif
				   //
				   if  (  !ppCapStuff  )  goto  errLabel;
							
				   //
				   TCHAR	displayName[MAX_monikerDisplayNameLen  +  1]	=	_T(  ""  );		
				   if  (  !bWebcamUsing(  pProcInfo,  0,  getMoniker_v(  *ppCapStuff,  pDynBmpMem->iMenuId  ),  NULL,  NULL,  NULL  )  )  {
					   if  (  getMonikerDisplayName(  getMoniker_v(  *ppCapStuff,  pDynBmpMem->iMenuId  ),  displayName,  mycountof(  displayName  )  )  )  displayName[0]  =  0;			  
				   }
		  
				   if  (  !displayName[0]  )  goto  errLabel;
		  	  		  
				   //
#if  0
				   if  (  openLocalVideo(  (  MC_VAR_common  *  )pProcInfo,  uiCamCapType,  displayName,  NULL,  &avCompressor.video,  iIndex_sharedObj  )  )  {
					   #ifdef  __DEBUG__
							   traceLogA(  (char*)  "CDlgSharedWebcamps::toShare: openLocalVideo failed."  );
					   #endif		
					   goto  errLabel;					  
				   }
#endif
				   //  2015/05/18
				   	AV_COMPRESSOR_CFG	*	pCompressor  =  &avCompressor;
					
					BOOL	bAudio  =  CAP_STUFF_bAudio(  *ppCapStuff  );
					BOOL	bVideo  =  CAP_STUFF_bVideo(  *ppCapStuff  );
					
					//
					if  (  !bVideo  )  {
						showInfo_open0(  0,  0,  _T(  "toShareBmp failed, bVideo is false"  )  );
						goto  errLabel;
					}
					pDynBmpMem->bAudioExists  =  bAudio;
					pDynBmpMem->bVideoExists  =  bVideo;

					//
					BITMAPINFOHEADER  bih_suggested;
					//  2015/08/28
					makeBmpInfoHeader_rgb(  24,  pCompressor->video.common.iWidth_pic,  pCompressor->video.common.iHeight_pic,  &bih_suggested  );
					//
					if  (  initShareMediaDevice(  ppCapStuff,  &pCompressor->audio,  &bih_suggested,  pQyMc->gui.hMainWnd,  iIndex_sharedObj,  &pSharedObj->pShareMediaObj  )  )  goto  errLabel;
					//  pCapBmp->bCapDevConnected  =  TRUE;	//  2012/02/24
					
					//  
					if  (  !bGetCapturePara_shareMediaDevice(  (  MC_VAR_common  *  )pProcInfo,  iIndex_capAudio,  iIndex_capBmp,  pSharedObj->pShareMediaObj,  &pCapAudio->wf_org,  &pCapBmp->vh_org,  NULL  )  )  goto  errLabel;
						
					//
					if  (  bVideo  )  {
						CAP_procInfo_bmpCommon	*	pVc  =  pCapBmp;
								
						//
						if  (  pVc->vh_org.bih.biCompression  !=  BI_RGB  ||  pVc->vh_org.bih.biBitCount  !=  24  )  {
							if  (  initOrg2RgbBuf(  (  MC_VAR_common  *  )pProcInfo,  (  CAP_procInfo_bmpCommon  *  )pVc  )  )  {
								traceLogA(  (char*)  "initOrg2RgbBuf failed."  );
								goto  errLabel;					
							}		
						}
						
						QY_VIDEO_HEADER	*	pVh_rgb;
						pVh_rgb  =  pVc->bOrg2RgbBufInited  ?  &pVc->vh_rgb  :  &pVc->vh_org;
						QY_VIDEO_HEADER  vh_dec  =  *pVh_rgb;
						if  (  pVc->vh_org.bih.biCompression  ==  CONST_fourcc_MJPG  )  {
							makeBmpInfoHeader_i420(  12,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight,  &vh_dec.bih  );	
						}

						//
						//  2014/04/03
						pCompressor->video.common.pVideoQ2  =  &pVc->thread.q2;
						pCompressor->video.common.pParent_transform  =  pVc;
						//
						if  (  initCompressVideo(  pProcInfo,  (  BITMAPINFO  *  )&vh_dec.bih,  uiCapType,  &pCompressor->video,  FALSE,  0,  pCompressVideo  )  )  {
							showNotification(  NULL,  0,  0,  0,  0,  0,  _T(  "Initialize video compress failed!"  )  );  
							goto  errLabel;		
						}	
						//  2017/06/11
						if  (  pDynBmpMem  )  {  //  2017/06/11
							pDynBmpMem->usW  =  pVh_rgb->bih.biWidth;
							pDynBmpMem->usH  =  pVh_rgb->bih.biHeight;
						}
					}
					
					if  (  bAudio  )  {
						AUDIO_COMPRESSOR_CFG	audioCompressor;
						if  (  pCompressor->audio.common.ucCompressors  ==  CONST_audioCompressors_acm  )  {
							memcpy(  &audioCompressor,  &pCompressor->audio,  sizeof(  audioCompressor  )  );			
						}		
						else  {
							   memset(  &audioCompressor,  0,  sizeof(  audioCompressor  )  );		
							   //  audioCompressor.ucCompressors  =  pCompressor->audio.ucCompressors;
							   memcpy(  &audioCompressor,  &pCompressor->audio,  sizeof(  audioCompressor  )  );
							   memcpy(  &audioCompressor.wf_decompress_default,  &pCapAudio->wf_org,  sizeof(  audioCompressor.wf_decompress_default  )  );			  
							   //
							   memset(  &audioCompressor.wf_compress,  0,  sizeof(  audioCompressor.wf_compress  )  );	//  2011/02/02
							   audioCompressor.wf_compress.wFormatTag  =  pCompressor->audio.wf_compress.wFormatTag;
							   audioCompressor.wf_compress.nChannels  =  pCapAudio->wf_org.nChannels;
							   audioCompressor.wf_compress.nSamplesPerSec  =  pCapAudio->wf_org.nSamplesPerSec;
							   audioCompressor.wf_compress.wBitsPerSample  =  pCapAudio->wf_org.wBitsPerSample;		
						}
						//
						//  2016/12/10
						AUDIO_COMPRESSOR_CFG  *  pCompressor  =  &audioCompressor;	
						pCompressor->common.pAudioQ2  =  &pCapAudio->thread.q2;	
						pCompressor->common.pParent_transform  =  pCapAudio;
						//
						if  (  initCompressAudio(  pProcInfo,  &pCapAudio->wf_org,  &audioCompressor,  pCompressAudio  )  )  {
							showNotification(  NULL,  0,  0,  0,  0,  0,  _T(  "Initialize audio compress failed!"  )  );  
							goto  errLabel;		
						}	
					}
					
					//
					pCapBmp->curhWnd  =  m_hWnd;


				   }
				   break;	
				   //
				   			case  CONST_camCapType_ic: {
								//
								TCHAR	displayName[MAX_monikerDisplayNameLen + 1] = _T("");

								//
								safeTcsnCpy(_T("ic"), displayName, mycountof(displayName));

								//
								if (!displayName[0])  goto  errLabel;

								//
								//  2015/05/18
								AV_COMPRESSOR_CFG* pCompressor = &avCompressor;

								BOOL	bAudio = false;// CAP_STUFF_bAudio(*ppCapStuff);
								BOOL	bVideo = true;// CAP_STUFF_bVideo(*ppCapStuff);

								//
								if (!bVideo) {
									showInfo_open0(0, 0, _T("toShareBmp failed, bVideo is false"));
									goto  errLabel;
								}
								pDynBmpMem->bAudioExists = bAudio;
								pDynBmpMem->bVideoExists = bVideo;

								//
								BITMAPINFOHEADER  bih_suggested_unused; 
								//  2015/08/28
								makeBmpInfoHeader_rgb(24, pCompressor->video.common.iWidth_pic, pCompressor->video.common.iHeight_pic, &bih_suggested_unused);
								//
								if (initShareIc(ppCapStuff, &pCompressor->audio, &bih_suggested_unused, pQyMc->gui.hMainWnd, iIndex_sharedObj, &pSharedObj->pIcObj))  goto  errLabel;
								//  pCapBmp->bCapDevConnected  =  TRUE;	//  2012/02/24

								//  
								if (!bGetCapturePara_shareIc((MC_VAR_common*)pProcInfo, iIndex_capAudio, iIndex_capBmp, pSharedObj->pIcObj, &pCapAudio->wf_org, &pCapBmp->vh_org))  goto  errLabel;

								//
								if (isAvFlg_unresizable(pTaskAvProps->v.ucAvFlg)) {
									pCompressor->video.common.iWidth_pic = pCapBmp->vh_org.bih.biWidth;
									pCompressor->video.common.iHeight_pic = pCapBmp->vh_org.bih.biHeight;
								}


								//
								if (bVideo) {
									CAP_procInfo_bmpCommon* pVc = pCapBmp;

									//
									if (pVc->vh_org.bih.biCompression != BI_RGB || pVc->vh_org.bih.biBitCount != 24) {
										if (initOrg2RgbBuf((MC_VAR_common*)pProcInfo, (CAP_procInfo_bmpCommon*)pVc)) {
											traceLogA((char*)"initOrg2RgbBuf failed.");
											goto  errLabel;
										}
									}

									QY_VIDEO_HEADER* pVh_rgb;
									pVh_rgb = pVc->bOrg2RgbBufInited ? &pVc->vh_rgb : &pVc->vh_org;
									QY_VIDEO_HEADER  vh_dec = *pVh_rgb;
									if (pVc->vh_org.bih.biCompression == CONST_fourcc_MJPG) {
										makeBmpInfoHeader_i420(12, pVc->vh_org.bih.biWidth, pVc->vh_org.bih.biHeight, &vh_dec.bih);
									}

									//
									//  2014/04/03
									pCompressor->video.common.pVideoQ2 = &pVc->thread.q2;
									pCompressor->video.common.pParent_transform = pVc;
									//
									if (initCompressVideo(pProcInfo, (BITMAPINFO*)&vh_dec.bih, uiCapType, &pCompressor->video, FALSE, 0, pCompressVideo)) {
										showNotification(NULL, 0, 0, 0, 0, 0, _T("Initialize video compress failed!"));
										goto  errLabel;
									}
									//  2017/06/11
									if (pDynBmpMem) {  //  2017/06/11
										pDynBmpMem->usW = pVh_rgb->bih.biWidth;
										pDynBmpMem->usH = pVh_rgb->bih.biHeight;
									}
								}

								if (bAudio) {
									AUDIO_COMPRESSOR_CFG	audioCompressor;
									if (pCompressor->audio.common.ucCompressors == CONST_audioCompressors_acm) {
										memcpy(&audioCompressor, &pCompressor->audio, sizeof(audioCompressor));
									}
									else {
										memset(&audioCompressor, 0, sizeof(audioCompressor));
										//  audioCompressor.ucCompressors  =  pCompressor->audio.ucCompressors;
										memcpy(&audioCompressor, &pCompressor->audio, sizeof(audioCompressor));
										memcpy(&audioCompressor.wf_decompress_default, &pCapAudio->wf_org, sizeof(audioCompressor.wf_decompress_default));
										//
										memset(&audioCompressor.wf_compress, 0, sizeof(audioCompressor.wf_compress));	//  2011/02/02
										audioCompressor.wf_compress.wFormatTag = pCompressor->audio.wf_compress.wFormatTag;
										audioCompressor.wf_compress.nChannels = pCapAudio->wf_org.nChannels;
										audioCompressor.wf_compress.nSamplesPerSec = pCapAudio->wf_org.nSamplesPerSec;
										audioCompressor.wf_compress.wBitsPerSample = pCapAudio->wf_org.wBitsPerSample;
									}
									//
									//  2016/12/10
									AUDIO_COMPRESSOR_CFG* pCompressor = &audioCompressor;
									pCompressor->common.pAudioQ2 = &pCapAudio->thread.q2;
									pCompressor->common.pParent_transform = pCapAudio;
									//
									if (initCompressAudio(pProcInfo, &pCapAudio->wf_org, &audioCompressor, pCompressAudio)) {
										showNotification(NULL, 0, 0, 0, 0, 0, _T("Initialize audio compress failed!"));
										goto  errLabel;
									}
								}

								//
								pCapBmp->curhWnd = m_hWnd;


							}
														  break;

			case  CONST_camCapType_slave:
				  if  (   openLocalVideo_slave(  (  MC_VAR_common  *  )pProcInfo,  uiCamCapType,  pDynBmpMem->iIndex_sharedObj_master,  &avCompressor.video,  iIndex_sharedObj  )  )  {
					   #ifdef  __DEBUG__
							   traceLogA(  (char*)  "CDlgSharedWebcamps::toShare: openLocalVideo_slave failed."  );
					   #endif		
					  goto  errLabel;
				  }
				  break;
			case  CONST_camCapType_mosaic:
				  //
				  if  (   pProcInfo->openLocalVideo_mosaic(  (  MC_VAR_common  *  )pProcInfo,  uiCamCapType,  &pDynBmpMem->bih_mosaic,  &avCompressor.video,  iIndex_sharedObj  )  )  {
					   #ifdef  __DEBUG__
							   traceLogA(  (char*)  "CDlgSharedWebcamps::toShare: openLocalVideo_slave failed."  );
					   #endif		
					  goto  errLabel;
				  }
				  break;
			default:
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "Unknown camCapType"  )  );
					#endif
					goto  errLabel;
					break;
	}

	//		
	pDynBmpMem->var.ucbLocalVideoOpen  =  TRUE;
	
	//
#if  10
	if  (  toShareDynBmp_step3(  pProcInfo,  m_hWnd,  iTaskId_suggested,  pDynBmpMem  )  )  goto  errLabel;
#endif

	iErr  =  0;

errLabel:
	
	if  (  iErr  )  {
		askSharedObjToStop(  pProcInfo,  pSharedObj,  pQyMc->gui.hMainWnd,  _T(  "toShareDynBmp"  )  );
		if  (  pDynBmpMem  )  {
			pDynBmpMem->var.ucbLocalVideoOpen  =  FALSE;
			//  2014/09/11
			pDynBmpMem->var.ucbUsed_iIndex_sharedObj  =  FALSE;
		}
	}

#if  0
	dlgShareDynBmps_refreshShareStatus(  m_hWnd,  &m_var,  uiObjType  );
#endif

	return  iErr;
}


//  2014/09/28
//int  toShareDynBmp_step3(  HWND  m_hWnd,  int  iTaskId_suggested,  SHARE_dyn_bmp  *  pDynBmpMem  )
int  toShareDynBmp_step3(  CCtxQmc  *  pProcInfo,  HWND  m_hWnd,  int  iTaskId_suggested,  SHARE_dyn_bmp  *  pDynBmpMem  )
{	
	int								iErr					=	-1;

	if  (  !pProcInfo  )  return  -1;
	QY_MC						*	pQyMc					=	pProcInfo->pQyMc;
	MIS_CNT						*	pMisCnt					=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	
	CAP_procInfo_bmpCommon		*	pCapBmp					=	NULL;
	COMPRESS_VIDEO				*	pCompressVideo			=	NULL;	

	//  2015/05/18
	CAP_procInfo_audioCommon	*	pCapAudio				=	NULL;
	COMPRESS_AUDIO				*	pCompressAudio			=	NULL;

	//
	if  (  !pDynBmpMem  )  return  -1;

	unsigned  int  uiObjType  =  pDynBmpMem->resObj.uiObjType;  

	if (!pDynBmpMem->var.ucbLocalVideoOpen)  return  -1;// goto  errLabel;

	int  iIndex_sharedObj  =  pDynBmpMem->var.iIndex_sharedObj;
	int  iIndex_sharedObjUsr  =  pDynBmpMem->var.iIndex_sharedObjUsr;
	unsigned  int  uiTaskType  =  pDynBmpMem->var.uiTaskType;

	QY_SHARED_OBJ* pSharedObj; pSharedObj = getSharedObjByIndex(pProcInfo, iIndex_sharedObj);
	if  (  !pSharedObj  )  goto  errLabel;
	//  2014/11/08
	SHARED_OBJ_USR* pSharedObjUsr; pSharedObjUsr = getSharedObjUsr(pSharedObj, iIndex_sharedObjUsr);
	if  (  !pSharedObjUsr  )  goto  errLabel;
	
	//  2015/05/18
	if  (  pDynBmpMem->bAudioExists  )  {
		int  iIndex_capAudio  =  pSharedObj->iIndex_capAudio;

		pCapAudio  =  (  CAP_procInfo_audioCommon  *  )getCapAudioBySth(  pProcInfo,  iIndex_capAudio,  0  );
		if  (  !pCapAudio  )  goto  errLabel;

		pCompressAudio  =  &pCapAudio->compressAudio;
	}
	
	//
	int  iIndex_capBmp; iIndex_capBmp = pSharedObj->iIndex_capBmp;
	
	pCapBmp  =  (  CAP_procInfo_bmpCommon  *  )getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );
	if  (  !pCapBmp  )  goto  errLabel;

	pCompressVideo  =  &pCapBmp->compressVideo;




#if  10
	//  2011/07/29		
	BOOL  bAudio; bAudio = FALSE;
	bAudio  =  pDynBmpMem->bAudioExists;
	//
	//  2015/10/11
	if  (  bAudio  )  {
		if  (  !pCapAudio  )  goto  errLabel;
		if  (  !pCapAudio->thread.bQInited  )  {
			#ifdef  __DEBUG__
					MACRO_qyAssert(  0,  _T(  "toShareDynBmp_step3 failed, capA.bQInited is false"  )  );
			#endif
			showInfo_open0(  0,  0,  _T(  "toShareDynBmp_step3 failed, capA.bQInited is false"  )  );
			goto  errLabel;
		}
	}
	if  (  !pCapBmp->postThread.bQInited  )  {
			#ifdef  __DEBUG__
					MACRO_qyAssert(  0,  _T(  "toShareDynBmp_step3 failed, capV.bQInited is false"  )  );
			#endif
			showInfo_open0(  0,  0,  _T(  "toShareDynBmp_step3 failed, capV.bQInited is false"  )  );
			goto  errLabel;
	}

#if  0
	if  (  pCapBmp->bCapDevConnected  )  {
		pCapBmp->curhWnd  =  m_hWnd;
	}
#endif
	
	//
	pCompressVideo		=	&pCapBmp->compressVideo;

	//
	switch  (  uiObjType  )  {
			case  CONST_objType_mosaicStream_video:
			case  CONST_objType_mosaicStream_resource:

				  if  (  pCompressVideo  &&  pCompressVideo->uiTranNo_openAvDev_org  )  {	//  
					  pSharedObjUsr->uiTranNo_openAvDev_v  =  pCompressVideo->uiTranNo_openAvDev_org  +  iIndex_sharedObjUsr;	//  pSharedObj->iIndex_curUsr;		  
				  }
				  //
				  pSharedObjUsr->iTaskId  =  iTaskId_suggested;

				  break;
			default:				{
					//
					TALKER_dynBmp	rule_dynBmp;
					//  QIS_dynBmp_info	dynBmp;
					memset(  &rule_dynBmp,  0,  sizeof(  rule_dynBmp  )   );
					rule_dynBmp.uiType1  =  CONST_talkerObjType_dynBmp;
					rule_dynBmp.dynBmpRule.dynBmp.resObj.uiObjType  =  uiObjType;
					//  rule_dynBmp.dynBmp.usIndex_obj  =  index;
					rule_dynBmp.dynBmpRule.dynBmp.resObj.usIndex_obj  =  pDynBmpMem->resObj.usIndex_obj;	//  2014/06/01
					int  tmp_iTaskId  =  iTaskId_suggested;	//  0;
					//
					PARAM_startAvCall param = { 0 };
					if  (  procSendAvInfo(  pMisCnt,  m_hWnd,  FALSE,  uiTaskType,  &param, pCompressVideo,  pCompressAudio,  iIndex_sharedObj,  iIndex_sharedObjUsr,  &rule_dynBmp,  NULL,  &tmp_iTaskId,  NULL,  NULL  )  )  goto  errLabel;
					pDynBmpMem->var.iTaskId  =  tmp_iTaskId;
					}
					break;
	}
	
	//  2010/09/09
	setCurSharedObjUsr(  pProcInfo,  iIndex_sharedObj, iIndex_sharedObjUsr);

	//
#if  0	//  ndef  __SUPPORT_subProcessToStartAvCall__
	if  (  pCapBmp->bCapDevConnected  )  {
		startCapture(  pProcInfo,  pCapBmp  );  
	}
#endif
	if  (  runSharedMediaObj(  pProcInfo,  pSharedObj  )  )  {
		goto  errLabel;
	}

	//mytime(  &m_var.tLastModifiedTime  );
#endif

	iErr  =  0;

errLabel:
	return  iErr;

}




