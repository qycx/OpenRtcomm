

#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyMcMainCusModule.h"
#include	"qyCusResTemp.h"
#include	"qyVDev.h"
#include	"myresource.h"
#include	"qyCustom.h"
#include	"module_qisCamCap.h"
#include	"qdcLyraPublic.h"


//  2015/10/03
#include	"qyDynLib.h"

#ifdef  __isCli__
#include	"get_pf_createDXGIFactory1.h"
		#include	"ctxQmc.h"
#endif

//
 extern  "C"  __declspec(  dllexport  )  int  decNv_qdcInit(  QDC_MGR  *  p  );
 extern  "C"  int  __declspec(  dllexport  )decNv_qdcExit(  QDC_MGR  *  p  );

 extern  "C"  int  __declspec(  dllexport  )decNv_qdcInitDecompressVideo(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_compress,  QY_VIDEO_HEADER  *  pVh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  );
 extern  "C"  int  __declspec(  dllexport  )decNv_qdcExitDecompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );
 extern  "C"  int  __declspec(  dllexport  )decNv_qdcDecompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs  );

 //
 extern  "C"  int  __declspec(  dllexport  )decNv_qdcDecompressVideoAndOutput(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  BITMAPINFO  *  pBmpInfo_output,  BYTE  *  pOutput  );
 extern  "C"  int  __declspec(  dllexport  )  decNv_qdcDecompressVideoRun(  QDC_OBJ_INFO  *  pQdcObjInfo  );
 //
 extern  "C"  int  __declspec(  dllexport  )decNv_qdcGetOutputByIndex(  QDC_OBJ_INFO  *  pQdcObjInfo,  int  index,  BYTE *  pbOutData,  unsigned  int  *  puiDataSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  pui_rtTimeLen  );
 extern  "C"  int  __declspec(  dllexport  )decNv_qdcClearOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  );

 //
 extern  "C"  __declspec(  dllexport  )  int  encNv_qdcInit(  QDC_MGR  *  p  );
 extern  "C"  int  __declspec(  dllexport  )encNv_qdcExit(  QDC_MGR  *  p  );

 extern  "C"  int  __declspec(  dllexport  )encNv_qdcGetCompressVideoCfg(  char  *  fourccStr,  unsigned  int  size  );

 extern  "C"  int  __declspec(  dllexport  )encNv_qdcInitCompressVideo(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_decompress,  QY_VIDEO_HEADER  *  pVh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  );
 extern  "C"  int  __declspec(  dllexport  )encNv_qdcExitCompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );
 extern  "C"  int  __declspec(  dllexport  )encNv_qdcCompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs  );
 extern  "C"  int  __declspec(  dllexport  )  encNv_qdcCompressVideoRun(  QDC_OBJ_INFO  *  pQdcObjInfo  );
 extern  "C"  __declspec(  dllexport  )  int  encNv_qdcGetSpsPps(  QDC_OBJ_INFO  *  pQdcObjInfo,  char  *  spsBuf,  unsigned  int  *  puiSpsSize,  char  *  ppsBuf,  unsigned  int  *  puiPpsSize,  char  *  kk,  unsigned  int  *  puiKkSize  );


 //
 extern  "C"  int  __declspec(  dllexport  )encNv_qdcGetOutputByIndex(  QDC_OBJ_INFO  *  pQdcObjInfo,  int  index,  BYTE *  pbOutData,  unsigned  int  *  puiDataSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  pui_rtTimeLen  );
 extern  "C"  int  __declspec(  dllexport  )encNv_qdcClearOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  );


 //  2015/10/03
 //void  *  get_pf_CreateDXGIFactory1(  QY_ENV  *  pEnv  );

#ifdef  __isCli__
#include	"tmpFfmpegPublic.h"
#include	"tmpAACPublic.h"
#endif
#include <gpuFunc.h>
#include <nvHelpPublic.h>
 //






 




 

  

  //
  int  initCusModules(void* pQyMcParam)
  {
	  int						iErr = -1;

	  QY_MC* pQyMc = (QY_MC*)pQyMcParam;
	  if (!pQyMc)  return  -1;
	  MC_VAR_common* pProcInfo = (MC_VAR_common*)pQyMc->get_pProcInfo();
	  if (!pProcInfo)  return  -1;

	  //
	  int						index = 0;
	  CUS_MODULE_U* pModule = NULL;

	  CQyRWLock		syncObj;
	  //
#if  0
	  if (syncObj.wLock(pQyMc->cfg.cusModules.mutexName, pQyMc->cfg.cusModules.uiMilliSeconds_mutex_w, pQyMc->hSema_syncCusModules, pQyMc->cfg.cusModules.uiMilliSeconds_sema_w, pQyMc->cfg.cusModules.uiInitCnt_sema))  return  -1;
#else
	  if (syncObj.wLock(pQyMc->pRw_syncCusModules, pQyMc->cfg.cusModules.uiMilliSeconds_sema_w))  return  -1;
#endif


	  for (index = 0; index < pQyMc->cusModules.usCnt; index++) {
		  pModule = &pQyMc->cusModules.mems[index];
		  //
		  //  if  (  !pModule->common.hModule  )  continue;
		  if (!pModule->common.bLoaded)  continue;

		  switch (pModule->common.uiType) {
		  case  CONST_moduleType_vDev:
			  if (pModule->vDev.pf_qyVDev_getCfg && pModule->vDev.pf_qyVDev_getCfg(0, 0, 0))  goto  errLabel;
			  if (pModule->vDev.pf_qyVDev_chkBeforeInit && pModule->vDev.pf_qyVDev_chkBeforeInit(0, 0, 0))  goto  errLabel;
			  if (pModule->vDev.pf_qyVDev_init && pModule->vDev.pf_qyVDev_init(0, 0, 0))  goto  errLabel;
			  pModule->vDev.ucbVDevInited = TRUE;
			  if (pModule->vDev.pf_qyVDev_chkAfterInit && pModule->vDev.pf_qyVDev_chkAfterInit(0, 0, 0))  goto  errLabel;
			  break;
		  case  CONST_moduleType_camCap: {
			  MODULE_camCap* pCamCap = (MODULE_camCap*)pModule;
			  if (pCamCap->pf_setGuiOpen)  pCamCap->pf_setGuiOpen(&pQyMc->guiOpen);
		  }
									   break;

		  case  CONST_moduleType_compress:
		  case  CONST_moduleType_ipp:
			  //
		  case  CONST_moduleType_mediaSdk_dec:
		  case  CONST_moduleType_mediaSdk_enc:
		  case  CONST_moduleType_mediaSdk_enc_conf:
			  //
		  case  CONST_moduleType_dec_nv:
		  case  CONST_moduleType_decD3d_nv:
		  case  CONST_moduleType_enc_nv:
		  case  CONST_moduleType_encD3d_nv:
			  //
		  case  CONST_moduleType_dec_amf:
		  case  CONST_moduleType_enc_amf:
			  //
		  case  CONST_moduleType_qdc_vorbis_dec:
		  case  CONST_moduleType_qdc_vorbis_enc:
			  //
		  case  CONST_moduleType_dec_vp8:
		  case  CONST_moduleType_enc_vp8:
			  //
		  case CONST_moduleType_ffmpeg:
			  //

		  default:
			  //
			  if (pModule->common.uiType == CONST_moduleType_decD3d_nv) {
				  int jj = 0;
			  }

			  //
			  pModule->compress.mgr.pGuiOpen = &pQyMc->guiOpen;
			  //
			  if (pModule->compress.pf_qdcInit && pModule->compress.pf_qdcInit(&pModule->compress.mgr))  goto  errLabel;
			  pModule->compress.ucbInited = TRUE;
			  break;
		  }
	  }


	  for (index = 0; index < pQyMc->cusModules.usCnt; index++) {
		  pModule = &pQyMc->cusModules.mems[index];
		  //
		  switch (pModule->common.uiType) {
		  case  CONST_moduleType_vDev:
			  if (pModule->vDev.ucbVDevInited) {
				  QY_VDEV* pVDev;

				  if (!(pVDev = (QY_VDEV*)pModule->vDev.pf_qyVDev_getPtrProperty(0, (void*)CONST_qyPropertyId_vDev, 0)))  goto  errLabel;

				  if (pQyMc->iServiceId == CONST_qyServiceId_is) {
#if  0
					  MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)pSci->pVar;
					  if (!pProcInfo)  goto  errLabel;

					  //  此标志的存在，是为了决定是否PhoneMsgrList下载。2008/02/01
					  if (pModule->vDev.pf_qyVDev_isSendable && pModule->vDev.pf_qyVDev_isSendable(0, (void*)CONST_objType_phoneMessenger, NULL))  pProcInfo->bPhoneModuleLoaded = TRUE;
					  //
#endif
				  }
				  break;
			  }
		  }
	  }

	  //  2014/12/06
#define		CONST_ver_dec_vp8			"02650115"	//"02620301"
#define		CONST_ver_enc_vp8			"02650115"	//"02620301"

	  TCHAR  tBuf[128];
	  if (strcmp(pQyMc->cusModules.pDec_vp8->compress.mgr.ver, CONST_ver_dec_vp8)) {
		  _sntprintf(tBuf, mycountof(tBuf), _T("decVp8 ver err: loaded is %s. correct is %s"), CQyString(pQyMc->cusModules.pDec_vp8->compress.mgr.ver), CQyString((char*)CONST_ver_dec_vp8));
		  showNotification_open(0, 0, 0, tBuf);
	  }
	  if (strcmp(pQyMc->cusModules.pEnc_vp8->compress.mgr.ver, CONST_ver_enc_vp8)) {
		  _sntprintf(tBuf, mycountof(tBuf), _T("encVp8 ver err: loaded is %s. correct is %s"), CQyString(pQyMc->cusModules.pEnc_vp8->compress.mgr.ver), CQyString((char*)CONST_ver_enc_vp8));
		  showNotification_open(0, 0, 0, tBuf);
	  }

	  //
#define		CONST_ver_dec_msdk			"02660251"	//  2017/1007	//  "02650115"	//	2016/04/10,2015/11/02,2015/10/18	//  2015/10/08	//  "02622836"	//"02620301"
//
#define		CONST_ver_enc_msdk			"02660254"	//"02660251"	//  2017/10/07	//  "02650115"	//  2016/04/10	//  "02630246"	//	2015/11/02,2015/10/17	//  2015/10/04	//  "02617701"

//
#define		CONST_ver_ipp				"02660142"	//  2017/08/20	"02650115"	//  2015/11/02,2015/10/05	//  "02620301"	//	2014/05/13,"025982";		// 2014/02/27,"02592301";		//  2013/03/06,"02550501";  2012/11/12

	//
#define		CONST_ver_dec_nv			"02660777"	//  2017/12/19	"02650115"	//  2015/11/02,2015/10/18	//  2015/10/08,		"02622853"	//  2015/04/30
#define		CONST_ver_enc_nv			"02660777"	//  2017/12/19	"02650115"	//  2015/11/02,2015/10/18	//  2015/10/08,		"02622853"	//  2015/04/30

	//
#define		CONST_ver_dec_amf			"02650115"	//  2015/11/02,2015/10/18	//  2015/10/08,		"02622853"	//  2015/04/30
#define		CONST_ver_enc_amf			"02650115"	//  2015/11/02,2015/10/18	//  2015/10/08,		"02622853"	//  2015/04/30

#define		CONST_ver_vorbis_dec			"02650117"	//  2016/12/16
#define		CONST_ver_vorbis_enc			"02650117"	//  2016/12/16
	//  2015/04/28
	//  这里差了nv的版本比较

	//  2014/12/24
	  if (pQyMc->cusModules.pMediaSdk_dec && pQyMc->cusModules.pMediaSdk_dec->common.bLoaded) {
		  if (strcmp(pQyMc->cusModules.pMediaSdk_dec->compress.mgr.ver, CONST_ver_dec_msdk)) {
			  _sntprintf(tBuf, mycountof(tBuf), _T("dec_msdk ver err:"));
			  showNotification_open(0, 0, 0, tBuf);
		  }
	  }
	  if (pQyMc->cusModules.pMediaSdk_enc && pQyMc->cusModules.pMediaSdk_enc->common.bLoaded) {
		  if (strcmp(pQyMc->cusModules.pMediaSdk_enc->compress.mgr.ver, CONST_ver_enc_msdk)) {
			  _sntprintf(tBuf, mycountof(tBuf), _T("enc_msdk ver err:"));
			  showNotification_open(0, 0, 0, tBuf);
		  }
	  }
#if  0
	  if (pQyMc->cusModules.pMediaSdk_enc_conf && pQyMc->cusModules.pMediaSdk_enc_conf->common.bLoaded) {
		  if (strcmp(pQyMc->cusModules.pMediaSdk_enc_conf->compress.mgr.ver, CONST_ver_enc_conf_msdk)) {
			  _sntprintf(tBuf, mycountof(tBuf), _T("enc_conf_msdk ver err:"));
			  showNotification_open(0, 0, 0, tBuf);
		  }	  
	  }
#endif 
	  //  2017/01/08
	  if (pQyMc->cusModules.pDec_nv && pQyMc->cusModules.pDec_nv->common.bLoaded) {
		  if (strcmp(pQyMc->cusModules.pDec_nv->compress.mgr.ver, CONST_ver_dec_nv)) {
			  _sntprintf(tBuf, mycountof(tBuf), _T("dec_nv ver err:"));
			  //showNotification_open(  0,  0,  0,  tBuf  );
			  showInfo_open0(0, 0, tBuf);
		  }
	  }
	  if (pQyMc->cusModules.pEnc_nv && pQyMc->cusModules.pEnc_nv->common.bLoaded) {
		  if (strcmp(pQyMc->cusModules.pEnc_nv->compress.mgr.ver, CONST_ver_enc_nv)) {
			  _sntprintf(tBuf, mycountof(tBuf), _T("enc_nv ver err:"));
			  //showNotification_open(  0,  0,  0,  tBuf  );
			  showInfo_open0(0, 0, tBuf);
		  }
	  }
	  //
#define		CONST_ver_decD3d_nv		"02661256"
#define		CONST_ver_encD3d_nv		"02661256"
	  //
	  if (pQyMc->cusModules.pDecD3d_nv && pQyMc->cusModules.pDecD3d_nv->common.bLoaded) {
		  if (strcmp(pQyMc->cusModules.pDecD3d_nv->compress.mgr.ver, CONST_ver_decD3d_nv)) {
			  _sntprintf(tBuf, mycountof(tBuf), _T("decD3d_nv ver err:"));
			  //showNotification_open(  0,  0,  0,  tBuf  );
			  showInfo_open0(0, 0, tBuf);
		  }
	  }
	  //
	  if (pQyMc->cusModules.pEncD3d_nv && pQyMc->cusModules.pEncD3d_nv->common.bLoaded) {
		  if (strcmp(pQyMc->cusModules.pEncD3d_nv->compress.mgr.ver, CONST_ver_encD3d_nv)) {
			  _sntprintf(tBuf, mycountof(tBuf), _T("encD3d_nv ver err:"));
			  //showNotification_open(  0,  0,  0,  tBuf  );
			  showInfo_open0(0, 0, tBuf);
		  }
	  }


	  //  2015/04/30
	  if (pQyMc->cusModules.pDec_amf && pQyMc->cusModules.pDec_amf->common.bLoaded) {
		  if (strcmp(pQyMc->cusModules.pDec_amf->compress.mgr.ver, CONST_ver_dec_amf)) {
			  _sntprintf(tBuf, mycountof(tBuf), _T("dec_amf ver err:"));
			  showNotification_open(0, 0, 0, tBuf);
		  }
	  }
	  if (pQyMc->cusModules.pEnc_amf && pQyMc->cusModules.pEnc_amf->common.bLoaded) {
		  if (strcmp(pQyMc->cusModules.pEnc_amf->compress.mgr.ver, CONST_ver_enc_amf)) {
			  _sntprintf(tBuf, mycountof(tBuf), _T("enc_amf ver err:"));
			  showNotification_open(0, 0, 0, tBuf);
		  }
	  }

	  //
#if  0
	  if (pQyMc->cusModules.pIpp && pQyMc->cusModules.pIpp->common.bLoaded) {
		  if (strcmp(pQyMc->cusModules.pIpp->compress.mgr.ver, CONST_ver_ipp)) {
			  _sntprintf(tBuf, mycountof(tBuf), _T("ipp ver err: loaded is %s. correct is %s"), CQyString(pQyMc->cusModules.pIpp->compress.mgr.ver), CQyString((char*)CONST_ver_ipp));
			  showNotification_open(0, 0, 0, tBuf);
		  }
	  }
#endif 

	  //  2016/12/16
	  if (pQyMc->cusModules.pQdc_vorbis_dec && pQyMc->cusModules.pQdc_vorbis_dec->common.bLoaded) {
		  if (strcmp(pQyMc->cusModules.pQdc_vorbis_dec->compress.mgr.ver, CONST_ver_vorbis_dec)) {
			  _sntprintf(tBuf, mycountof(tBuf), _T("vorbis_dec ver err: loaded is %s. correct is %s"), CQyString(pQyMc->cusModules.pQdc_vorbis_dec->compress.mgr.ver), CQyString((char*)CONST_ver_vorbis_dec));
			  showNotification_open(0, 0, 0, tBuf);
		  }
	  }
	  if (pQyMc->cusModules.pQdc_vorbis_enc && pQyMc->cusModules.pQdc_vorbis_enc->common.bLoaded) {
		  if (strcmp(pQyMc->cusModules.pQdc_vorbis_enc->compress.mgr.ver, CONST_ver_vorbis_enc)) {
			  _sntprintf(tBuf, mycountof(tBuf), _T("vorbis_enc ver err: loaded is %s. correct is %s"), CQyString(pQyMc->cusModules.pQdc_vorbis_enc->compress.mgr.ver), CQyString((char*)CONST_ver_vorbis_enc));
			  showNotification_open(0, 0, 0, tBuf);
		  }
	  }



#ifdef  __DEBUG__

#endif

	  iErr = 0;
  errLabel:
	  return  iErr;

  }



  int  startCusModules(void* pQyMcParam)
  {
	  int					iErr = -1;
	  int					index = 0;
	  QY_MC* pQyMc = (QY_MC*)pQyMcParam;
	  CUS_MODULE_U* pModule = NULL;

	  CQyRWLock		syncObj;
	  //
#if  0
	  if (syncObj.wLock(pQyMc->cfg.cusModules.mutexName, pQyMc->cfg.cusModules.uiMilliSeconds_mutex_w, pQyMc->hSema_syncCusModules, pQyMc->cfg.cusModules.uiMilliSeconds_sema_w, pQyMc->cfg.cusModules.uiInitCnt_sema))  return  -1;
#else
	  if (syncObj.wLock(pQyMc->pRw_syncCusModules, pQyMc->cfg.cusModules.uiMilliSeconds_sema_w))  return  -1;
#endif

	  for (index = 0; index < pQyMc->cusModules.usCnt; index++) {
		  pModule = &pQyMc->cusModules.mems[index];
		  //
		  //  if  (  !pModule->common.hModule  )  continue;
		  if (!pModule->common.bLoaded)  continue;

		  switch (pModule->common.uiType) {
		  case  CONST_moduleType_vDev:
			  if (pModule->vDev.ucbVDevStarted)  continue;
			  if (!pModule->vDev.ucbVDevInited)  goto  errLabel;
			  //
			  if (pModule->vDev.pf_qyVDev_start && pModule->vDev.pf_qyVDev_start(0, 0, 0))  goto  errLabel;
			  pModule->vDev.ucbVDevStarted = TRUE;
			  break;
		  default:
			  break;
		  }
	  }


	  iErr = 0;
  errLabel:
	  return  iErr;
  }

  int  stopCusModules(void* pQyMcParam)
  {
	  int					iErr = -1;
	  int					index = 0;
	  QY_MC* pQyMc = (QY_MC*)pQyMcParam;
	  CUS_MODULE_U* pModule = NULL;

	  CQyRWLock		syncObj;
	  //
#if  0
	  if (syncObj.wLock(pQyMc->cfg.cusModules.mutexName, pQyMc->cfg.cusModules.uiMilliSeconds_mutex_w, pQyMc->hSema_syncCusModules, pQyMc->cfg.cusModules.uiMilliSeconds_sema_w, pQyMc->cfg.cusModules.uiInitCnt_sema))  return  -1;
#else
	  if (syncObj.wLock(pQyMc->pRw_syncCusModules, pQyMc->cfg.cusModules.uiMilliSeconds_sema_w))  return  -1;
#endif

	  for (index = 0; index < pQyMc->cusModules.usCnt; index++) {
		  pModule = &pQyMc->cusModules.mems[index];
		  //
		  //  if  (  !pModule->common.hModule  )  continue;
		  if (!pModule->common.bLoaded)  continue;


		  switch (pModule->common.uiType) {
		  case  CONST_moduleType_vDev:
			  if (pModule->vDev.ucbVDevStarted) {
				  if (pModule->vDev.pf_qyVDev_stop && pModule->vDev.pf_qyVDev_stop(0, 0, 0))  goto  errLabel;
				  pModule->vDev.ucbVDevStarted = FALSE;
			  }
			  break;
		  default:
			  break;
		  }
	  }


	  iErr = 0;
  errLabel:
	  return  iErr;
  }


  int  unloadCusModules(void* pQyMcParam)
  {
	  int					index = 0;
	  QY_MC* pQyMc = (QY_MC*)pQyMcParam;
	  CUS_MODULE_U* pModule = NULL;

	  stopCusModules(pQyMcParam);

	  CQyRWLock		syncObj;
	  //
#if  0
	  if (syncObj.wLock(pQyMc->cfg.cusModules.mutexName, pQyMc->cfg.cusModules.uiMilliSeconds_mutex_w, pQyMc->hSema_syncCusModules, pQyMc->cfg.cusModules.uiMilliSeconds_sema_w, pQyMc->cfg.cusModules.uiInitCnt_sema))  return  -1;
#else
	  if (syncObj.wLock(pQyMc->pRw_syncCusModules, pQyMc->cfg.cusModules.uiMilliSeconds_sema_w))  return  -1;
#endif

	  //
	  for (index = 0; index < pQyMc->cusModules.usCnt; index++) {
		  pModule = &pQyMc->cusModules.mems[index];
		  //
		  //  if  (  !pModule->common.hModule  )  continue;
		  if (!pModule->common.bLoaded)  continue;

		  switch (pModule->common.uiType) {
		  case  CONST_moduleType_vDev:
			  //
			  if (pModule->vDev.ucbVDevInited) {
				  if (pModule->vDev.pf_qyVDev_exit)  pModule->vDev.pf_qyVDev_exit(0, 0, 0);
				  pModule->vDev.ucbVDevInited = FALSE;
			  }
			  break;
		  case  CONST_moduleType_compress:
		  case  CONST_moduleType_ipp:
		  case  CONST_moduleType_mediaSdk_dec:
		  case  CONST_moduleType_mediaSdk_enc:
		  case  CONST_moduleType_mediaSdk_enc_conf:
			  //case  CONST_moduleType_cuda:
		  case  CONST_moduleType_dec_nv:
		  case  CONST_moduleType_enc_nv:
			  //
		  case  CONST_moduleType_dec_amf:	//  2015/04/30
		  case  CONST_moduleType_enc_amf:
			  //
		  case  CONST_moduleType_dec_vp8:
		  case  CONST_moduleType_enc_vp8:
			  //
		  case CONST_moduleType_ffmpeg:
		  case CONST_moduleType_aac:
			  //
		  default:
			  //
			  if (pModule->compress.ucbInited) {
				  if (pModule->compress.pf_qdcExit)  pModule->compress.pf_qdcExit(&pModule->compress.mgr);
				  pModule->compress.ucbInited = FALSE;
			  }
			  break;

		  }

		  if (pModule->common.hModule) {
			  FreeLibrary(pModule->common.hModule);  pModule->common.hModule = NULL;
		  }
		  pModule->common.bLoaded = FALSE;	//  2014/06/19
	  }

	  return  0;
  }



 


 //
 int  myVDev_postStr2Dev(  void  *  pQyMcParam,  char  *  idStr_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  LPCTSTR  str,  unsigned  int  uiDevType_to,  WCHAR  *  wDevIdStr_to,  WCHAR  *  wForwardPath,  HWND  hWnd_notify,  int  iUsrData  )
{
	int					iErr		=	-1;
	QY_MC			*	pQyMc		=	(  QY_MC  *  )pQyMcParam;//
	CUS_MODULE_U	*	pModule		=	NULL;

	CQyRWLock		syncObj;
	//
#if  0
	if  (  syncObj.rLock(  pQyMc->cfg.cusModules.mutexName,  pQyMc->cfg.cusModules.uiMilliSeconds_mutex_r,  pQyMc->hSema_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_r  )  )  return  -1;
#else
	if  (  syncObj.rLock(  pQyMc->pRw_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_r  )  )  return  -1;
#endif

	if  (  !(  pModule  =  getCusModule(  &pQyMc->cusModules,  CONST_moduleType_vDev,  0,  uiDevType_to,  wDevIdStr_to  )  )  )  goto  errLabel;

	if  (  pModule->vDev.pf_qyVDev_postStr2Dev  &&  pModule->vDev.pf_qyVDev_postStr2Dev(  idStr_from,  tStartTime,  uiTranNo,  uiSeqNo,  str,  uiDevType_to,  wDevIdStr_to,  wForwardPath,  hWnd_notify,  iUsrData  )  )  goto  errLabel;
	
	iErr  =  0;
errLabel:
	return  iErr;

}
  


 int  myVDev_postData2Dev(  void  *  pQyMcParam,  unsigned  int  uiVDevId,  char  *  idStr_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  void  *  pQyVDevData,  unsigned  int  uiDataLen,  unsigned  int  uiDevType_to,  WCHAR  *  wDevIdStr_to,  unsigned  int  uiDevIndex  )
{
	int					iErr		=	-1;
	QY_MC			*	pQyMc		=	(  QY_MC  *  )pQyMcParam;//
	CUS_MODULE_U	*	pModule		=	NULL;

	CQyRWLock		syncObj;
	//
#if  0
	if  (  syncObj.rLock(  pQyMc->cfg.cusModules.mutexName,  pQyMc->cfg.cusModules.uiMilliSeconds_mutex_r,  pQyMc->hSema_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_r  )  )  return  -1;
#else
	if  (  syncObj.rLock(  pQyMc->pRw_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_r  )  )  return  -1;
#endif
	
	if  (  !(  pModule  =  getCusModule(  &pQyMc->cusModules,  CONST_moduleType_vDev,  uiVDevId,  0,  0  )  )  )  goto  errLabel;

	if  (  pModule->vDev.pf_qyVDev_postData2Dev  &&  pModule->vDev.pf_qyVDev_postData2Dev(   idStr_from,  tStartTime,  uiTranNo,  uiSeqNo,  pQyVDevData,  uiDataLen,  uiDevType_to,  wDevIdStr_to,  uiDevIndex  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;

}



