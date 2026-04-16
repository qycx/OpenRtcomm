
#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//  #include	"qmcVideoCapture_isCli.h"
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

//#include	"isCliHelpPublic.h"
//#include	"dlgShareDynBmpsProc.h"
//#include	"isClid3dpublic.h"
#include	"qmcTaskPublic.h"

//#include	"qmcCommFunc_isCli.h"
#include	"qmcCfg.h"
#include	"tmpGuiOpenFunc.h"
#include	"funcsForIsCliHelp.h"
#include <av1_defs.h>






//
__declspec(dllexport)  int  initCompressVideo(  void  *  pProcInfoParam,  BITMAPINFO  *  pBmpInfo_input,  unsigned  int  uiCapType,  VIDEO_COMPRESSOR_CFG  *  pCompressor,  BOOL  bCapDev,  unsigned  int  uiBufSize_pData,  COMPRESS_VIDEO  *  pCompressVideo  )
{
	int					iErr			=	-1;
	CCtxQmc		*	pProcInfo0		=	(  CCtxQmc  *  )pProcInfoParam;
	if  (  !pProcInfo0  )  return  -1;
	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo0->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	if  (  !pQyMc  )  return  -1;
	//
	CUS_MODULES		*	pCusModules		=	(  CUS_MODULES  *  )pProcInfo0->getCusModules(  );
	if  (  !pCusModules  )  return  -1;
	//
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo0);

	//
	DWORD				iFourcc		=	0;
	BITMAPINFO		*	pBmpInfo		=	NULL;
	int					iFormatSize		=	0;
	DWORD				biSizeImage		=	0;
	int					iRet;
	unsigned  char		ucbResizable	=	FALSE;
	unsigned  char		ucbResizeByEncoder	=	FALSE;		//  2014/05/03
	int					iW_org			=  0; 
	int					iH_org			=  0;
	
	//  2016/04/02
	if  (  !pCompressVideo  )  return  -1;

	//  2016/04/02
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo0->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initCompressVideo enters. %s"  ),  pCompressVideo->tag_dbg  );

	//  2014/04/07
#if  0
	if  (  pBmpInfo_input  )  {  
		if  (  !bSupported_avLevel(  0,  pBmpInfo_input,  pCompressor  )  )  {
			showNotification(  0,  0,  0,  0,  0,  0,  _T(  "Not supported in this version"  )  );
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Not supported in this version"  )  );
			goto  errLabel;
		}
	}
#endif

	//
	if  (  pCompressVideo->bVideoCompressInited1  )  {
		iErr  =  0;  goto  errLabel;			//  Õâ±íÃ÷ÒÑ¾­ºÃÁË
	}

	//  2009/04/19
	//  pCompressVideo->usMaxFps_toShareBmp  =  (  bCapDev  ?  pProcInfo0->cfg.policy.video.usMaxFps_toShareBmp  :  pProcInfo0->cfg.policy.video.usFps_capScreen  );
	//  pCompressVideo->usMaxFps_toShareBmp  =  pCompressor->usMaxFps_toShareBmp;
	if  (  memcmp(  pCompressor,  &pCompressVideo->compressor,  sizeof(  pCompressor[0]  )  )  )  memcpy(  &pCompressVideo->compressor,  pCompressor,  sizeof(  pCompressVideo->compressor  )  );
	if  (  !pCompressVideo->compressor.common.usMinFps_toShareBmp  )  {
		//  pCompressVideo->compressor.common.usMinFps_toShareBmp  =  1;
		pCompressVideo->compressor.common.usMinFps_toShareBmp  =  pCompressVideo->compressor.common.usMaxFps_toShareBmp;	//  2011/07/25
	}
	//pCompressVideo->compressor.common.ucbScreenSharing  =  (  uiCapType  ==  CONST_capType_screen  );
	pCompressVideo->compressor.common.uiCapType  =  uiCapType;												//  2012/02/08

	//  2014/03/29
	pCompressVideo->compressor.common.ucHardwareAccl  =  pQmcCfg->policy.ucHardwareAccl;

	//
	pCompressVideo->usFrames_perSecond_expected  =  pCompressVideo->compressor.common.usMinFps_toShareBmp;
	//
	if  (  !pCompressVideo->usFrames_perSecond_expected  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo0->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initCompressVideo failed: usFrames_perSecond_expected is 0"  )  );
		goto  errLabel;
	}
	//
	pCompressVideo->ucTimeoutInS_showFrameInfoResp  =  MAX_ucTimeoutInS_showFrameInfoResp;						//  È±Ê¡³¬Ê±ÓÃ30Ãë
	//
	pCompressVideo->tLastTime_sendVideo  =  0;
	pCompressVideo->tLastTime_showFrameInfo  =  0;
	pCompressVideo->tFirstTime_showFrameInfo_withoutResp  =  0;
	pCompressVideo->tRecvTime_resp_fromCli  =  0;

	//
#if  0
	if  (  pBmpInfo_input  )  memcpy(  &pCompressVideo->vh_decompress.bih,  pBmpInfo_input,  sizeof(  pCompressVideo->vh_decompress.bih  )  );
	else  pBmpInfo_input  =  (  BITMAPINFO  *  )&pCompressVideo->vh_decompress.bih;
#endif
	if  (  !pBmpInfo_input  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo0->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initCompressVideo failed: pBmpInfo_input is null"  )  );
		goto  errLabel;
	}

	//		
	iW_org  =  pBmpInfo_input->bmiHeader.biWidth;							
	iH_org  =  pBmpInfo_input->bmiHeader.biHeight;

	//
	if  (  pCompressor->common.iWidth_pic  		
		&&  pCompressor->common.iHeight_pic  )
	{
		if  (  pCompressor->common.iWidth_pic  <  pBmpInfo_input->bmiHeader.biWidth  
			||  pCompressor->common.iHeight_pic  <  pBmpInfo_input->bmiHeader.biHeight  )
		{
#if  0
			if  (  pCompressor->common.ucCompressors  ==  CONST_videoCompressors_hwAccl  
				&&  !pProcInfo0->cfg.ucb__USE_hdEnc_conf__  		
				)  	
			{
				ucbResizable  =  TRUE;		
				ucbResizeByEncoder  =  TRUE;	//  2014/05/03
				}		
			else  
#endif
			{  // resize others in vpp. 2014/04/24
				  switch  (  uiCapType  )  {
						  case  CONST_capType_av:
						  case  CONST_capType_mediaFile:
						  case  CONST_capType_mediaDevice:
							    ucbResizable  =  TRUE;
								break;
						  case  CONST_capType_screen:
						  case  CONST_capType_qvcf:		//  2015/05/25
								#ifdef  __DEBUG__
										#if  0
											traceLog((TCHAR*)  _T(  "For test, screen is resizable"  )  );
											ucbResizable  =  TRUE;
										#endif
								#endif
							    break;
						  default:
								 #ifdef  __DEBUG__
										 traceLog((TCHAR*)  _T(  "Not finished: initCompressVideo: unResizable capType %d"  ),  uiCapType  );
										 MACRO_qyAssert(  0,  _T(  "Not finished: initCompressVideo: unResizable capType"  )  );
								 #endif
								 break;		  
				  }	
			}
		}
	}

	//
	if  (  !ucbResizable  )  {
		memcpy(  &pCompressVideo->vh_decompress.bih,  pBmpInfo_input,  sizeof(  pCompressVideo->vh_decompress.bih  )  );
		}
	else  {
				//
				unsigned  char  ucbAutoClip  =  FALSE;

				int  iX  =  0;
				int  iY  =  0;
				int  iW  =  pCompressor->common.iWidth_pic;
				int  iH  =  pCompressor->common.iHeight_pic;
				unsigned  int  iW_i,  iH_i;
				int  iX_src_i,  iY_src_i;
				int  iX_dst,  iY_dst;
				unsigned  int  iW_dst,  iH_dst;

				//
#if 0
				myGetImageInfo_2d(  0,  ucbAutoClip,  iW_org,  iH_org,  iX,  iY,  iW,  iH,
									&iW_i,  &iH_i,  &iX_src_i,  &iY_src_i, 
									  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );	//  这个函数需要修改，在4X3的分辨率时，也需要调整分辨率为4的倍数。以便压缩.
#else
				unsigned  char  ucb3d  =  TRUE;					  
			
				myGetImageInfo(  0,										//  
					    ucbAutoClip,									//  根据目标矩形自动裁剪，使目标矩形被充满
						ucb3d,											//  2014/11/14
						iW_org,  iH_org,  
						iX,  iY,  iW,  iH,  
						&iW_i,  &iH_i,
						&iX_src_i,  &iY_src_i,  
						&iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

#endif
				//
				iW_dst  =  iW_dst  /  4  *  4;
				iH_dst  =  iH_dst  /  4  *  4;
				//
				if  (  !iW_dst  ||  !iH_dst  )  {
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo0->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initCompressVideo failed: iW_dst or iH_dst is 0"  )  );
					goto  errLabel;
				}
				MACRO_qyAssert(  !(  iW_dst  %  4  ),  _T(  ""  )  );
				MACRO_qyAssert(  !(  iH_dst  %  4  ),  _T(  ""  )  );
				//
				makeBmpInfoHeader_rgb(  24,  iW_dst,  iH_dst,  &pCompressVideo->vh_decompress.bih  );

				//  下面还要在enc模块里加上resize处理。要把bResizable参数从compressor带进去，
		  
	}
	//  2014/05/03
	pCompressVideo->ucbResizeByEncoder  =  ucbResizeByEncoder;

	//  2014/05/11
	if  (  1  )  {  
		if  (  !bSupported_avLevel(  pProcInfo0->pQyMc,  uiCapType,  (  BITMAPINFO  *  )&pCompressVideo->vh_decompress.bih,  pCompressor  )  )  {
			showNotification(  0,  0,  0,  0,  0,  0,  _T(  "Not supported in this version"  )  );
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Not supported in this version"  )  );
			goto  errLabel;
		}
	}


	//
	iFourcc  =  fourccStr2i(  pCompressVideo->compressor.common.fourccStr  );

	//pCompressVideo->usCapDriverIndex  =  usCapDriverIndex;

	//  2014/04/02		 
	//  2014/03/23	 	
	 GENERIC_Q_cfgEx	qCfgEx;	//  2012/11/10
	 GENERIC_Q_CFG		tmpCfg;

	TCHAR	tBuf[128];
#define		CONST_mutexNamePrefix_encV	_T(  "mtxEncV"  )
	int		tn  =  GetTickCount(  );
	int size  =  sizeof(  GENERIC_Q  );
	pCompressVideo->pInDataCacheQ  =  (  GENERIC_Q  *  )mymalloc(  size  );
	if  (  !pCompressVideo->pInDataCacheQ  )  goto  errLabel;
	memset(  pCompressVideo->pInDataCacheQ,  0,  size  );
	size  =  sizeof(  GENERIC_Q  );
	pCompressVideo->pTmpDataQ  =  (  GENERIC_Q  *  )mymalloc(  size  );
	if  (  !pCompressVideo->pTmpDataQ  )  goto  errLabel;
	memset(  pCompressVideo->pTmpDataQ,  0,  size  );


	//
	memset(  &tmpCfg,  0,  sizeof(  tmpCfg  )  );
	_sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-in-%d"  ),  CONST_mutexNamePrefix_encV,  tn  );
	_sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-in-%d"  ),  CONST_mutexNamePrefix_encV,  tn  );
	tmpCfg.uiMaxQNodes  =  100;
	
	memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );		
	memcpy(  &qCfgEx.common,  &tmpCfg,  sizeof(  qCfgEx.common  )  );	
	qCfgEx.pfQElemNewEx  =  mallocMemory;
	qCfgEx.pfQElemNew  =  mymalloc;
	qCfgEx.pfQElemFreeEx  =  freeMemory;
	qCfgEx.pfQElemFree  =  myfree;
	qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_myDRAW_VIDEO_DATA;
	qCfgEx.pfQElemRemove  =  ( PF_qElemRemove  )clean_myDRAW_VIDEO_DATA;

	if  (  initGenericQ(  &qCfgEx,  (  GENERIC_Q  *  )pCompressVideo->pInDataCacheQ  )  )  goto  errLabel;

		//
	memset(  &tmpCfg,  0,  sizeof(  tmpCfg  )  );
	_sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-tmp-%d"  ),  CONST_mutexNamePrefix_encV,  tn  );
	_sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-tmp-%d"  ),  CONST_mutexNamePrefix_encV,  tn  );
	tmpCfg.uiMaxQNodes  =  100;
	
	memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );		
	memcpy(  &qCfgEx.common,  &tmpCfg,  sizeof(  qCfgEx.common  )  );	
	qCfgEx.pfQElemNewEx  =  mallocMemory;
	qCfgEx.pfQElemNew  =  mymalloc;
	qCfgEx.pfQElemFreeEx  =  freeMemory;
	qCfgEx.pfQElemFree  =  myfree;
	qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_myDRAW_VIDEO_DATA;
	qCfgEx.pfQElemRemove  =  ( PF_qElemRemove  )clean_myDRAW_VIDEO_DATA;

	if  (  initGenericQ(  &qCfgEx,  pCompressVideo->pTmpDataQ  )  )  goto  errLabel;
		
	//
	size  =  sizeof(  myDRAW_VIDEO_DATA  );
	pCompressVideo->pCurPkt  =  (  myDRAW_VIDEO_DATA  *  )mymalloc(  size  );
	if  (  !pCompressVideo->pCurPkt  )  goto  errLabel;
	memset(  pCompressVideo->pCurPkt,  0,  size  );

	//
	memset(&pCompressVideo->encInfo, 0, sizeof(pCompressVideo->encInfo));

	//  
	if  (  pCompressVideo->compressor.common.ucCompressors  ==  CONST_videoCompressors_vcm  )  {
#ifndef  __WINCE__
		if  (  !(  pCompressVideo->u.vcm.hicLocal  =  ICOpen(  ICTYPE_VIDEO,  iFourcc,  ICMODE_FASTCOMPRESS  )  )  )  {
			#ifdef  __DEBUG__
					traceLogA(  (char*)  "initCompressVideo: ICOpen failed, fourcc %s",  pCompressVideo->compressor.common.fourccStr  );
			#endif
			goto  errLabel;
		}

		iFormatSize  =  ICCompressGetFormat(  pCompressVideo->u.vcm.hicLocal,  pBmpInfo_input,  NULL  );
		if  (  iFormatSize  <=  0  )  goto  errLabel;
		if  (  !(  pBmpInfo  =  (  BITMAPINFO  *  )mymalloc(  iFormatSize  )  )  )  goto  errLabel;
		if  (  ICCompressGetFormat(  pCompressVideo->u.vcm.hicLocal,  pBmpInfo_input,  pBmpInfo  )  !=  ICERR_OK  )  goto  errLabel;
		memcpy(  &pCompressVideo->vh_compress.bih,  pBmpInfo,  min(  sizeof(  pCompressVideo->vh_compress.bih  ),  iFormatSize  )  );
		//
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo0->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "iFormatSize_compress_video %d"  ),  iFormatSize  );
		//
		if  (  (  iRet  =  ICCompressQuery(  pCompressVideo->u.vcm.hicLocal,  pBmpInfo_input,  &pCompressVideo->vh_compress.bih  )  )  !=  ICERR_OK  )  goto  errLabel;

		ICINFO	icInfo;
		int		iQuality;
		pCompressVideo->u.vcm.bVIDCF_QUALITY  =  FALSE;
		pCompressVideo->u.vcm.iQuality  =  0;
		if  (  ICGetInfo(  pCompressVideo->u.vcm.hicLocal,  &icInfo,  sizeof(  icInfo  )  )  )  {
			if  (  icInfo.dwFlags  &  VIDCF_QUALITY  )  {
				pCompressVideo->u.vcm.bVIDCF_QUALITY  =  TRUE;
				iQuality  =  ICGetDefaultQuality(  pCompressVideo->u.vcm.hicLocal  );
				if  (  iQuality  >=  0  ||  iQuality  <=  10000  )  pCompressVideo->u.vcm.iQuality  =  iQuality;
				traceLogA(  (char*)  "initCompressVideo: iQuality %d",  iQuality  );
			}
		}	

		pCompressVideo->iCompressBufSize  =  ICCompressGetSize(  pCompressVideo->u.vcm.hicLocal,  pBmpInfo_input,  &pCompressVideo->vh_compress.bih  );
#else
		traceLog((TCHAR*)  _T(  "vcm is not supported in winCe"  )  );
		goto  errLabel;
#endif
		}
	else  if  (  pCompressVideo->compressor.common.ucCompressors  ==  CONST_videoCompressors_dmo  )  {
			  //  2010/09/06
			  setEncodingDefaults_video(  uiCapType,  pCompressVideo->compressor.common.usMaxFps_toShareBmp,  fourccStr2i(  pCompressVideo->compressor.common.fourccStr  ),  &pCompressVideo->compressor.params  );					  
			  //
		      if  (  initCompressVideo_dmo(  &pCompressVideo->compressor,  &pCompressVideo->vh_decompress,  &pCompressVideo->vh_compress,  &pCompressVideo->u.dmo  )  )  goto  errLabel;
			  pCompressVideo->iCompressBufSize  =  pCompressVideo->vh_compress.bih.biSizeImage;
			  }
	else  if  (  pCompressVideo->compressor.common.ucCompressors  ==  CONST_videoCompressors_stream  )  {	
			  //
			  #ifdef  __DEBUG__
					  //  从源里直接得到压缩数据，所以不需要压缩. 2014/02/24
					  traceLog((TCHAR*)  _T(  "videoCompressors_stream"  )  );
			  #endif		     
			  }
	else  {
		  CUS_MODULE_U	*	pModule		=  NULL;
		  unsigned  int		uiModuleType	=	0;				//  2012/09/09

		  //
#if  0
		  if (0) {
			  //
			  switch (pCompressVideo->compressor.common.ucCompressors) {
			  case  CONST_videoCompressors_ipp:		//  2011/07/31
				  //  
				  uiModuleType = CONST_moduleType_ipp;
				  //
				  break;
			  case  CONST_videoCompressors_hwAccl:
				  //  
				  uiModuleType = CONST_moduleType_mediaSdk_enc;
				  //
				  //  2014/07/05
				  unsigned  char  ucHardwareAccl;
				  ucHardwareAccl = get_ucHardwareAccl(pQyMc);
				  //
				  switch (ucHardwareAccl) {
				  case  CONST_hdAccl_msdk_hardware:
					  //
					  uiModuleType = CONST_moduleType_mediaSdk_enc;
					  //
					  break;
				  case  0:
				  case  CONST_hdAccl_nv:
					  uiModuleType = CONST_moduleType_enc_nv;
					  //
					  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", _T("IsClient"), 0, _T(""), _T(""), _T("Adjusted: for nv, use nv to enc haccl h264."));
					  break;
				  case  CONST_hdAccl_amf:
					  uiModuleType = CONST_moduleType_enc_amf;
					  //
					  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", _T("IsClient"), 0, _T(""), _T(""), _T("Adjusted: for amf, use amf to enc haccl h264."));
					  break;
				  default:
					  break;
				  }
				  //
				  break;
#if  0
			  case  CONST_videoCompressors_cuda:	//  2012/06/18
				  //  
				  uiModuleType = CONST_moduleType_enc_nv;
				  break;
#endif
			  case  CONST_videoCompressors_vp8:		//  2014/07/19
				  //
				  uiModuleType = CONST_moduleType_enc_vp8;
				  break;
			  case  CONST_videoCompressors_custom:
				  //  
				  uiModuleType = CONST_moduleType_compress;
				  break;
			  default:
#ifdef  __DEBUG__
				  traceLogA((char*)"initCompressVideo: ucCompressors err: %d", pCompressVideo->compressor.common.ucCompressors);
#endif
				  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo0->who_showInfo, 0, _T(""), _T(""), _T("initCompressVideo: ucCompressors err: %d"), pCompressVideo->compressor.common.ucCompressors);
				  goto  errLabel;
				  break;
			  }

			  //
			  adjustModuleType_encV(&uiModuleType);

		  }
#endif 
		  //
		  getModuleType_encV(&pCompressVideo->compressor.common, &uiModuleType);

		  //
		  M_getCompressModule(  pCusModules,  uiModuleType,  pModule  );	//  2012/09/09
		  if  (  !pModule  ||  !pModule->common.bLoaded  ||  !pModule->compress.pf_qdcInitCompressVideo  )  {
			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo0->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initCompressVideo failed, pModule or initDecompressVideo is null."  )  );
			  goto  errLabel;
		  }
		  pCompressVideo->uiModuleType_toEnc  =  uiModuleType;

		  //  2015/10/13
		  if  (  pProcInfo0->bSupported_evt(  uiModuleType  )  )  {
			  pCompressVideo->ucbUseEvt  =  TRUE;
		  }

		  //
		  bool  bUse_oldYuvReader = false;
		  switch (uiModuleType) {
				 case  CONST_moduleType_mediaSdk_enc:
				 case  CONST_moduleType_enc_vp8:
				 case  CONST_moduleType_ipp:
					 bUse_oldYuvReader = true;
					   break;
				 default:
					 break;
		  }

		  //
		  _sntprintf(tBuf,  mycountof(tBuf),  _T("441.initCompressV. uiModuleType %d"),  uiModuleType);
		  showInfo_open0(0, 0, tBuf);

		  //
		  //  2014/04/02
		  VIDEO_COMPRESSOR_CFG  compressor;			 
		  memcpy(  &compressor,  &pCompressVideo->compressor,  sizeof(  compressor  )  );		  		  
		  compressor.common.pCurPkt  =  pCompressVideo->pCurPkt;
		  compressor.common.size_pCurPkt  =  sizeof(  pCompressVideo->pCurPkt[0]  );
		  compressor.common.pInDataCacheQ  =  pCompressVideo->pInDataCacheQ;
		  compressor.common.pVideoQ2  =  pCompressVideo->compressor.common.pVideoQ2;	//  2014/04/03. pVideoQ2这时尚未初始化。等数据流运行时，pVideoQ2已经ready
		  if  (  !compressor.common.pVideoQ2  )  {
			  showInfo_open0(  0,  0,  _T(  "initCompressVideo failed, pVideoQ2 is null"  )  );
			  goto  errLabel;
		  }
		  compressor.common.pTmpDataQ  =  pCompressVideo->pTmpDataQ;
		  //
		  compressor.common.pParent_transform  =  pCompressVideo->compressor.common.pParent_transform;
		  if  (  !compressor.common.pParent_transform  )  {
			  goto  errLabel;
		  }
		  compressor.common.uiTransformType_pParent  =  CONST_uiTransformType_encVideo;
		  //
		  compressor.common.pf_bTransformVideoQuit  =  bCapBmpQuit;
		  compressor.common.pf_transformGetSpsPps  =  capBmpGetSpsPps;
		  compressor.common.pf_transformGetBih  =  (  PF_commonHandler  )capBmpGetBih;
		  compressor.common.pf_getNextVPkt  =  (  PF_commonHandler  )getNextVPkt;
		  //compressor.common.pf_parseVPkt_i  =  enc_parseOrgVPkt_i;
		  compressor.common.pf_parseDecVPkt_o  =  parseDecVPkt_o;

		  compressor.common.pf_detachPkt  =  detachVPkt;
		  compressor.common.pf_clean_myDRAW_VIDEO_DATA  =  (  PF_clean_myDRAW_VIDEO_DATA  )clean_myDRAW_VIDEO_DATA;

		  //
		  //compressor.common.enc.ucb__USE_hdEnc_conf__  =  pProcInfo0->cfg.ucb__USE_hdEnc_conf__;
		  compressor.common.enc.ucbResizable  =  ucbResizeByEncoder;	//  ucbResizable;	//  2014/04/20
		  compressor.common.enc.iW_org  =  iW_org;
		  compressor.common.enc.iH_org  =  iH_org;
		  //
		  compressor.common.enc.pf_smplYUVReader_LoadNextFrame = smplYUVReader_LoadNextFrame;
		  if (bUse_oldYuvReader) {
			  compressor.common.enc.pf_smplYUVReader_LoadNextFrame = (PF_smplYUVReader_LoadNextFrame)old_smplYUVReader_LoadNextFrame;
		  }
		  //
		  compressor.common.enc.pf_doPostEnc  =  doPostEnc_mediaSdk_new;

		  //  2014/03/29
		  compressor.common.ucHardwareAccl  =  pQmcCfg->policy.ucHardwareAccl;

		  //
		  if  (  pCompressVideo->ucbUseEvt  )  {
			  // unsupported
			  goto  errLabel;

			  }
		  else  {

			  //
			  #ifdef  __DEBUG__
					  #if  0
							compressor.common.iAvgBitrate  =  0;
							showInfo_open0(  0,  0,  _T(  "TEST: iAvgBitrate is 0"  )  );
					  #endif
			  #endif
			  
			  //
			  //  2016/04/26				
			  pProcInfo0->set_qoi_funcs(  &pCompressVideo->u.qoi.myQoi  );
			  
			  
			  //
			  if  (  pModule->compress.pf_qdcSetProp  )  {
				  bool  bWin7  =  bLeWin7(  );
				  pModule->compress.pf_qdcSetProp(  CONST_qdcPropId_bWin7,  &bWin7,  mynull  );
				  //
				  bool bWinService = pQyMc->appParams.bService;
				  pModule->compress.pf_qdcSetProp(CONST_qdcPropId_bWinService, &bWinService, mynull);

				  //
				  PF_saveTex12  pf;  pf = nullptr;
				  pf = pFuncs->isCliD3d.pf_saveTex12;
				  pModule->compress.pf_qdcSetProp(CONST_qdcPropId_PF_saveTex12, pf, mynull);

				  //
				  void* pQisSharedTexInfos = pProcInfo0->m_pQisSharedTexInfos;
				  pModule->compress.pf_qdcSetProp(CONST_qdcPropId_pQisSharedTexInfos, pQisSharedTexInfos, mynull);
			  }

			  //
			  if (1) {
				  _sntprintf(tBuf,mycountof(tBuf),_T("599.initCompressV: %dkbps %dx%d"),  compressor.common.iAvgBitrate/1000,compressor.common.iWidth_pic,  compressor.common.iHeight_pic);
				  showInfo_open0(0, 0, tBuf);
			  }

			  //
			  QDC_OBJ_INFO* pQdcObjInfo;
			  pQdcObjInfo = &pCompressVideo->u.qoi.myQoi.common;
			  if (pModule->compress.pf_qdcInitCompressVideo(&compressor, &pCompressVideo->vh_decompress, &pCompressVideo->vh_compress, pQdcObjInfo)) {
				  showInfo_open0(0, 0, _T("module.initCompressV failed"));
				  goto  errLabel;
			  }
			  pCompressVideo->iCompressBufSize  =  pCompressVideo->vh_compress.bih.biSizeImage;
		
			  #ifdef  __DEBUG__		//  2014/10/10
					  char  fourcc_dec[4  +  1]  =  "";
					  char  fourcc_enc[4  +  1]  =  "";
					  iFourcc2Str(  pCompressVideo->vh_decompress.bih.biCompression,  fourcc_dec,  mycountof(  fourcc_dec  )  );
					  iFourcc2Str(  pCompressVideo->vh_compress.bih.biCompression,  fourcc_enc,  mycountof(  fourcc_enc  )  );
					  traceLog((TCHAR*)  _T(  "fourcc_dec %S, fourcc_enc %S"  ),  fourcc_dec,  fourcc_enc  );
			  #endif

			  //
			  //
			  if (pModule->compress.pf_qdcSetProp) {

						  //
						  TCHAR  dbgName[128] = _T("enc");
						  safeTcsnCpy(pCompressVideo->tag_dbg, dbgName, mycountof(dbgName));
						  COMMON_PARAM  commonParam;
						  MACRO_makeCommonParam3(&pCompressVideo->u.qoi.myQoi.common, dbgName, 0, commonParam);
						  pModule->compress.pf_qdcSetProp(CONST_qdcPropId_dbgName, &commonParam, mynull);
						  //
						  bool* g_pbMon = &pQmcCfg->debugStatusInfo.bMon_encV;
						  pModule->compress.pf_qdcSetProp(CONST_qdcPropId_pbMon, g_pbMon, mynull);

						  //
			  }

			  


			  //
			  if  (  pModule->compress.pf_qdcGetSpsPps  )  {
				  memset(  &pCompressVideo->vh_stream,  0,  sizeof(  pCompressVideo->vh_stream  )  );
				  VH_stream  *  pVh_stream  =  &pCompressVideo->vh_stream;
				  //
				  unsigned  int  vpsLen  =  0;	//  2017/10/10
				  char  *  pVps  =  NULL;
				  unsigned  int  spsLen  =  0;
				  char  *  pSps  =  NULL;
				  unsigned  int  ppsLen  =  0;								
				  char  *  pPps  =  NULL;
				 
				  //
				  switch  (  iFourcc  )  {
						  case  CONST_fourcc_HEVC:
							  {
							    //
							    int  k  =  0;
								vpsLen  =  sizeof(  pVh_stream->mems[k].spsPps  );  pVps  =  pVh_stream->mems[k].spsPps;  k  ++  ;
								spsLen  =  sizeof(  pVh_stream->mems[k].spsPps  );  pSps  =  pVh_stream->mems[k].spsPps;  k  ++  ;
								ppsLen  =  sizeof(  pVh_stream->mems[k].spsPps  );  pPps  =  pVh_stream->mems[k].spsPps;				  
								//				  
								//
								if  (  pModule->compress.pf_qdcGetSpsPps(  &pCompressVideo->u.qoi.myQoi.common,  pSps,  &spsLen,  pPps,  &ppsLen,  pVps,  &vpsLen  )  )  {
					  				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo0->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initCompressVideo failed, qdcGetSpsPps failed."  )  );
					  				goto  errLabel;  				  
								}				  
								//				  
								k  =  0;
								pVh_stream->mems[k].usLen  =  vpsLen;  k  ++  ;
								pVh_stream->mems[k].usLen  =  spsLen;  k  ++  ;				  
								pVh_stream->mems[k].usLen  =  ppsLen;  k  ++  ;				  
								pVh_stream->usCnt  =  k;				  
								
							    
								}
								break;
						  case  CONST_fourcc_AV01:
						  {
							  int  k = 0;
							  spsLen = sizeof(pVh_stream->mems[k].spsPps);  pSps = pVh_stream->mems[k].spsPps;  k++;
							  ppsLen = sizeof(pVh_stream->mems[k].spsPps);  pPps = pVh_stream->mems[k].spsPps;  k++;
							  //
							  if (pModule->compress.pf_qdcGetSpsPps(&pCompressVideo->u.qoi.myQoi.common, pSps, &spsLen, pPps, &ppsLen, NULL, NULL)) {
								  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo0->who_showInfo, 0, _T(""), _T(""), _T("initCompressVideo failed, qdcGetSpsPps failed."));
								  goto  errLabel;
							  }
							  //				  
							  k = 0;
							  pVh_stream->mems[k].usLen = spsLen;  k++;
							  pVh_stream->usCnt = k;
						  }
						  break;
								//
						  case  CONST_fourcc_h264:
						  default:
							     {				
									 int  k  =  0;							
									 spsLen  =  sizeof(  pVh_stream->mems[k].spsPps  );  pSps  =  pVh_stream->mems[k].spsPps;  k  ++  ;								
									 ppsLen  =  sizeof(  pVh_stream->mems[k].spsPps  );  pPps  =  pVh_stream->mems[k].spsPps;  k  ++  ;				  
									 //
									 if  (  pModule->compress.pf_qdcGetSpsPps(  &pCompressVideo->u.qoi.myQoi.common,  pCompressVideo->vh_stream.mems[0].spsPps,  &spsLen,  pVh_stream->mems[1].spsPps,  &ppsLen,  NULL,  NULL  )  )  {
										 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo0->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initCompressVideo failed, qdcGetSpsPps failed."  )  );
										 goto  errLabel;  				  
									 }				  
									 //				  
									 pVh_stream->mems[0].usLen  =  spsLen;				  
									 pVh_stream->mems[1].usLen  =  ppsLen;				  
									 pVh_stream->usCnt  =  2;
								 }
								 break;
				  }
				  //
				  pVh_stream->dwFourcc  =  pCompressVideo->vh_compress.bih.biCompression;
				  //  2014/05/02
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo0->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qdcGetSpsPps: vps %d, spsLen %d, ppsLen %d"  ),  vpsLen,  spsLen,  ppsLen  );
				  //
				  #ifdef  __DEBUG__
					  if  (  pQmcCfg->debugStatusInfo.ucb__Dump_h265_enc__  )  {
						  static  BOOL  bReset  =  FALSE;
						  if (iFourcc == CONST_fourcc_AV01) {
							  //
							  Param_anDumpVideo param = { 0 };
							  param.iFourcc = iFourcc;
							  param.iW = pCompressVideo->vh_decompress.bih.biWidth;
							  param.iH = pCompressVideo->vh_decompress.bih.biHeight;
							  //
							  char seqHeader[256];
							  unsigned int seqHeaderLen; seqHeaderLen = sizeof(seqHeader);
							  makeSpsPps(pVh_stream, seqHeader, &seqHeaderLen);
							  //
							  {
								  //
								  Param_parseIvfFrame param = { 0 };
								  parse_obu((const uint8_t*)seqHeader, seqHeaderLen, &param);


							  }
							  //
							  seqHeaderLen = 0;
							  //
							  dumpVideo_init(&param, &bReset, _T("c:\\tttbbb\\"), _T("kk.ivf"), seqHeader, seqHeaderLen, &pCompressVideo->dumpVideoObj);

						  }
						  else {
							  char* fn = (char*)CONST_fn_dump_h265_enc;
							  FILE* fp = NULL;
							  if (!bReset) {
								  fp = fopen(fn, "w");
								  if (fp) {
									  fclose(fp);
								  }
								  bReset = TRUE;
							  }
							  fp = fopen(fn, "ab+");
							  if (fp) {
								  int  i;
								  for (i = 0; i < pVh_stream->usCnt; i++) {
									  fwrite(pVh_stream->mems[i].spsPps, pVh_stream->mems[i].usLen, 1, fp);
								  }
								  fclose(fp);
							  }

						  }

					  }
				  #endif
			  }

		  //
		  }

	}


	//		
	if  (  !pCompressVideo->ucbUseEvt  )  {
		if  (  pCompressVideo->compressor.common.ucCompressors  !=  CONST_videoCompressors_stream  )  {
			if  (  pCompressVideo->iCompressBufSize  <=  0  )  goto  errLabel;
			if  (  !(  pCompressVideo->pCompressBuf  =  (  char  *  )mymalloc(  pCompressVideo->iCompressBufSize  )  )  )  goto  errLabel;
		}
	}

	//
	size  =  sizeof(  TRANSFER_VIDEO_DATA  );
	if  (  !(  pCompressVideo->pReqBuf_myVideoCapture  =  (  TRANSFER_VIDEO_DATA  *  )mymalloc(  size  )  )  )  goto  errLabel;
	memset(  pCompressVideo->pReqBuf_myVideoCapture,  0,  size  );

#if  0
	pCompressVideo->uiTranNo_openAvDev  =  getuiNextTranNo(  0,  0,  0  );
#endif
	pCompressVideo->uiTranNo_openAvDev_org  =  getuiNextTranNo(  0,  MAX_sharedObjUsrs,  0  );	//  2010/09/04


	if  (  uiBufSize_pData  )  {
		if  (  !(  pCompressVideo->pData  =  mymalloc(  uiBufSize_pData  )  )  )  goto  errLabel;
		memset(  pCompressVideo->pData,  0,  uiBufSize_pData  );
	}

	

	//
	pCompressVideo->bVideoCompressInited1  =  TRUE;
	

	//
	iErr  =  0;
errLabel:
	if  (  pBmpInfo  )  free(  pBmpInfo  );
	if  (  iErr  )  {
		exitCompressVideo(  pProcInfo0,  bCapDev,  pCompressVideo  );
	}	

	//  2012/11/06	
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo0->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initCompressVideo leaves with %s. %s"  ),  (  iErr  ?  _T(  "Failed"  )  :  _T(  "OK"  )  ),  pCompressVideo->tag_dbg  );

	return  iErr;
}


//
__declspec(dllexport)  int  exitCompressVideo(  void  *  pProcInfoParam,  BOOL  bCapDev,  COMPRESS_VIDEO  *  pCompressVideo  )
{
	int			iErr		=	-1;
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	//QY_MC	*	pQyMc		=	(  QY_MC  *  )pProcInfo->pQyMc;//
	CUS_MODULES  *  pCusModules  =  (  CUS_MODULES  *  )pProcInfo->getCusModules(  );
	if  (  !pCusModules  )  return  -1;

	if  (  !pCompressVideo  )    return  -1;

	//		
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "exitCompressVideo enters. %s"  ),  pCompressVideo->tag_dbg  );

	//  2015/10/11
	if  (  pCompressVideo->ucbUseEvt  )  {
		if  (  !pProcInfo->m_pf_qdcExitCompressVideo_evtCli  )  {
			showInfo_open0(  0,  0,  _T(  "Serious err, exitCompressVideo, m_pf_qdcExitCompressvideo_evtCli is null"  )  );
			}
		else  {
			  pProcInfo->m_pf_qdcExitCompressVideo_evtCli(  &pCompressVideo->u.qoi.myQoi.common  );
		}
		}
	else  {
		//
		if  (  !pCompressVideo->compressor.common.ucCompressors  )  ;
		else  if  (  pCompressVideo->compressor.common.ucCompressors  ==  CONST_videoCompressors_vcm  )  {
				  if  (  pCompressVideo->u.vcm.hicLocal  )  {
					  ICClose(  pCompressVideo->u.vcm.hicLocal  );  pCompressVideo->u.vcm.hicLocal  =  NULL;
				  }		
				  }
		else  if  (  pCompressVideo->compressor.common.ucCompressors  ==  CONST_videoCompressors_dmo  )  {
				  exitCompressVideo_dmo(  &pCompressVideo->u.dmo  );
				  }

		else  {
			  CUS_MODULE_U	*	pModule  =  NULL;

			  M_getCompressModule(  pCusModules,  pCompressVideo->uiModuleType_toEnc,  pModule  );	//  2012/09/09

			  if  (  pModule  &&  pModule->compress.pf_qdcExitCompressVideo  )  {
				  pModule->compress.pf_qdcExitCompressVideo(  &pCompressVideo->u.qoi.myQoi.common  );
			  }		
		}
		//
	}

	//
	dumpVideo_exit(&pCompressVideo->dumpVideoObj);

	//
	//  2014/03/25
	 clean_myDRAW_VIDEO_DATA(  pCompressVideo->pCurPkt,  _T(  "exitCompressVideo"  )  );
	 MACRO_safeFree(  pCompressVideo->pCurPkt  );

	//	 
	 //  2014/03/24
	 if  (  pCompressVideo->pInDataCacheQ  )  {
		 genericQFree(  pCompressVideo->pInDataCacheQ  );  pCompressVideo->pInDataCacheQ  =  NULL;
	 }
	 if  (  pCompressVideo->pTmpDataQ  )  {
		 genericQFree(  pCompressVideo->pTmpDataQ  );  pCompressVideo->pTmpDataQ  =  NULL;
	 }

	//
	if  (  pCompressVideo->pReqBuf_myVideoCapture  )  {
		free(  pCompressVideo->pReqBuf_myVideoCapture  );  pCompressVideo->pReqBuf_myVideoCapture  =  NULL;
	}
	if  (  pCompressVideo->pCompressBuf  )  {
		free(  pCompressVideo->pCompressBuf  );  pCompressVideo->pCompressBuf  =  NULL;
	}


#if  0
	//  2011/12/05
	MACRO_safeFree(  pCompressVideo->pVppBuf  );
	pCompressVideo->iVppBufSize  =  0;
#endif

	//
	if  (  pCompressVideo->pData  )  {

		if  (  !bCapDev  )  {
			exitAvRecord(  pCompressVideo  );
		}

		free(  pCompressVideo->pData  );  pCompressVideo->pData  =  NULL;
	}

	//  pCompressVideo->uiTranNo_openAvDev  =  0;	//  ×¢ÒâÇå0
	//  pCompressVideo->bVideoCompressInited  =  FALSE;		//  ×¢Òâ¿ª¹ØÁ¿¡£

	memset(  pCompressVideo,  0,  sizeof(  pCompressVideo[0]  )  );

	iErr  =  0;

//  errLabel:

	
	//		
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "exitCompressVideo leaves. %s"  ),  pCompressVideo->tag_dbg  );


	return  iErr;

}

