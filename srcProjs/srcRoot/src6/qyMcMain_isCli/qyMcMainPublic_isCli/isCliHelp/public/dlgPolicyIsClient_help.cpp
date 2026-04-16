
#include	"stdafx.h"
#include	<tchar.h>
#ifndef  __WINCE__
#include	<vfw.h>
#else
#ifdef  __TEST__
#include	<vfw.h>
#endif
#include	<mmreg.h>
#include	<msacm.h>
#endif

#include	<shlobj.h>

#include	"qyMcMainCommon.h"
#include	"myresource.h"

#include	"tmpCeLib.h"

//#include	"DlgPolicyIsClient.h"

#ifndef  __WINCE__
//  #include	"DlgVideoCompressors.h"
#endif

#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qyCusResTemp.h"
#ifndef  __WINCE__
//#include	"qyPs.h"
#endif
#include	"qmcDmoPublic.h"
#include	"myfourcc.h"

//  #include	"DlgPolicyAv.h"

#include	"policyAvParams.h"
#include	"policyIsClientFunc.h"


//
#include	"msAecCommon.h"


//
#include	"isCliHelpPublic.h"
#include	"qycusResTemp.h"

//  2014/07/24

#define		DEFAULT_LD_videoCompressors_av					CONST_videoCompressors_vp8		//CONST_videoCompressors_hwAccl	//  CONST_videoCompressors_dmo
#define		DEFAULT_LD_videoFourccStr_av					DEFAULT_fourccStr_vp8			//DEFAULT_fourccStr_mediaSdk		//  DEFAULT_fourccStr_dmo_video
#define		DEFAULT_LD_usMaxFps_toShareBmp					30	//5
#define		DEFAULT_LD_usFps_toShareBmp_videoConference		30	//5
#define		DEFAULT_LD_usMaxFps_webcam						30	//5

//
#define		DEFAULT_SD1_videoCompressors_av					CONST_videoCompressors_vp8		//CONST_videoCompressors_hwAccl	//CONST_videoCompressors_dmo	//  CONST_videoCompressors_ipp
#define		DEFAULT_SD1_videoFourccStr_av					DEFAULT_fourccStr_vp8			//DEFAULT_fourccStr_mediaSdk	//  DEFAULT_fourccStr_ipp	

//
#define		DEFAULT_SD3_videoCompressors_av					CONST_videoCompressors_hwAccl	// CONST_videoCompressors_dmo	//  CONST_videoCompressors_ipp
#define		DEFAULT_SD3_videoFourccStr_av					DEFAULT_fourccStr_mediaSdk		//DEFAULT_fourccStr_dmo_video	//  DEFAULT_fourccStr_ipp

#define		DEFAULT_SD_videoCompressors_mosaic_video		CONST_videoCompressors_vp8
#define		DEFAULT_SD_videoFourccStr_mosaic_video			DEFAULT_fourccStr_vp8	

//  2016/04/06
#define		DEFAULT_LD_videoCompressors_slave_video			CONST_videoCompressors_vp8
#define		DEFAULT_LD_videoFourccStr_slave_video			DEFAULT_fourccStr_vp8	
//
#define		DEFAULT_SD_videoCompressors_slave_video			CONST_videoCompressors_vp8
#define		DEFAULT_SD_videoFourccStr_slave_video			DEFAULT_fourccStr_vp8	


//
#define		DEFAULT_DEV2FPS_videoCompressors				CONST_videoCompressors_dmo
#define		DEFAULT_DEV2FPS_videoFourccStr_av				DEFAULT_fourccStr_dmo_video
//
#if  0
#define		DEFAULT_DEV5FPS_videoCompressors				CONST_videoCompressors_hwAccl	//  
#define		DEFAULT_DEV5FPS_videoFourccStr_av				DEFAULT_fourccStr_mediaSdk		// 
#else
#define		DEFAULT_DEV5FPS_videoCompressors				CONST_videoCompressors_vp8		//  
#define		DEFAULT_DEV5FPS_videoFourccStr_av				DEFAULT_fourccStr_vp8			// 
#endif

	//  2014/12/01
#define		DEFAULT_DEV5FPS_videoCompressors_mosaic_resource		CONST_videoCompressors_hwAccl	//  CONST_videoCompressors_vp8	//  CONST_videoCompressors_ipp
#define		DEFAULT_DEV5FPS_videoFourccStr_mosaic_resource			DEFAULT_fourccStr_mediaSdk		//  DEFAULT_fourccStr_vp8	//  DEFAULT_fourccStr_ipp



QY_DMITEM  CONST_audioCompressorsTable_sd[] =
{
	{	CONST_audioCompressors_acm,		_T("acm"),	},
	{	CONST_audioCompressors_dmo,		_T("dmo"),	},
#ifdef  __SUPPORT_CUSMODULE_vorbis__
	{	CONST_audioCompressors_vorbis,	_T("vorbis"),	},
#endif
#ifdef  __SUPPORT_CUSMODULE_compress__
	{	CONST_audioCompressors_custom,	_T("custom"),	},			//  2010/04/28
#endif

	{	-1,		},
};


QY_DMITEM  CONST_videoCompressorsTable_sd[] =
{
	{	CONST_videoCompressors_vcm,		_T("vcm"),	},
	{	CONST_videoCompressors_dmo,		_T("dmo"),	},
	//  {	CONST_videoCompressors_ipp,		_T(  "h264"  ),	},				//  2011/07/31

#if  1
	{	CONST_videoCompressors_vp8,		_T("VP8"),	},				//  2014/07/19
#endif

#ifdef  __SUPPORT_CUSMODULE_compress__
	{	CONST_videoCompressors_custom,	_T("custom"),	},			//  2010/04/28
#endif	
	{	-1,		},
};


QY_DMITEM  CONST_audioCompressorsTable_hd[] =
{
	{	CONST_audioCompressors_acm,		_T("acm"),	},
	{	CONST_audioCompressors_dmo,		_T("dmo"),	},
#ifdef  __SUPPORT_CUSMODULE_vorbis__
	{	CONST_audioCompressors_vorbis,	_T("vorbis"),	},
#endif
	{	CONST_audioCompressors_ipp,		_T("mp3"),	},
	{	CONST_audioCompressors_ffmpeg,		_T("ffmpeg mp3"),	},
	{	CONST_audioCompressors_aac,		_T("aac"),	},
#ifdef  __SUPPORT_CUSMODULE_compress__
	{	CONST_audioCompressors_custom,	_T("custom"),	},			//  2010/04/28
#endif

	{	-1,		},
};

QY_DMITEM  CONST_videoCompressorsTable_hd[] =
{
	{	CONST_videoCompressors_vcm,		_T("vcm"),	},
	{	CONST_videoCompressors_dmo,		_T("dmo"),	},
	//{	CONST_videoCompressors_ipp,		_T(  "h264"  ),	},				//  2011/07/31

	//
	{	CONST_videoCompressors_vp8,		_T("VP8"),	},				//  2014/07/19

	//
	{	CONST_videoCompressors_hwAccl,_T("hwAccel"),	},			//  2011/07/31
	//{	CONST_videoCompressors_cuda,	_T(  "cuda"  ),	},				//  2012/06/17

#ifdef  __SUPPORT_CUSMODULE_compress__
	{	CONST_videoCompressors_custom,	_T("custom"),	},			//  2010/04/28
#endif	
	{	-1,		},
};


QY_DMITEM  CONST_audioCompressorsTable_fullHd[] =
{
	{	CONST_audioCompressors_acm,		_T("acm"),	},
	{	CONST_audioCompressors_dmo,		_T("dmo"),	},
#ifdef  __SUPPORT_CUSMODULE_vorbis__
	{	CONST_audioCompressors_vorbis,	_T("vorbis"),	},
#endif
	{	CONST_audioCompressors_ipp,		_T("mp3"),	},				//  2012/01/19
	{	CONST_audioCompressors_ffmpeg,		_T("ffmpeg mp3"),	},
	{	CONST_audioCompressors_aac,		_T("aac"),	},
#ifdef  __SUPPORT_CUSMODULE_compress__
	{	CONST_audioCompressors_custom,	_T("custom"),	},			//  2010/04/28
#endif

	{	-1,		},
};


QY_DMITEM  CONST_videoCompressorsTable_fullHd[] =
{
	{	CONST_videoCompressors_vcm,		_T("vcm"),	},
	{	CONST_videoCompressors_dmo,		_T("dmo"),	},
	//{	CONST_videoCompressors_ipp,		_T(  "h264"  ),	},				//  2011/07/31
	//
	{	CONST_videoCompressors_vp8,		_T("VP8"),	},				//  2014/07/19
	//
	{	CONST_videoCompressors_hwAccl,_T("hwAccel"),	},			//  2011/07/31
	//{	CONST_videoCompressors_cuda,	_T(  "cuda"  ),	},				//  2012/06/17


#ifdef  __SUPPORT_CUSMODULE_compress__
	{	CONST_videoCompressors_custom,	_T("custom"),	},			//  2010/04/28
#endif	
	{	-1,		},
};



QY_DMITEM	CONST_ruleIfMsgArriveTable[] =
{
	{	CONST_ruleIfMsgArrive_flash,			_T("Flicker the chat windows while minimized"),				},
	{	CONST_ruleIfMsgArrive_popup,			_T("New chat windows poping up"),	},
	{	-1,									NULL,					},

};


//
__declspec(dllexport)  int  setSaveMsgFlg(BOOL  bEnable)
{

	int  iErr = -1;
	// TODO: Add your control notification handler code here
	int  idc;

	QY_REG	reg;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo1 = QY_GET_procInfo_isCli();

	memset(&reg, 0, sizeof(reg));
	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	//  safeStrnCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	lstrcpyn(reg.rootKey, CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), mycountof(reg.rootKey));

	TCHAR* pRegVal = _T(CONST_regValName_ucbSaveMsg);

	POLICY_isClient* pPolicy = &pProcInfo1->cfg.policy;

	if (bEnable) {

		qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, _T("1"));
		pPolicy->ucbSaveMsg = TRUE;
		//
		if (pPolicy->dirToSaveMsg[0]) {
			if (!bDir(pPolicy->dirToSaveMsg)) {
				pRegVal = _T(CONST_regValName_dirToSaveMsg);
				qyDelRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal);
				pPolicy->dirToSaveMsg[0] = 0;
			}
		}
		if (!pPolicy->dirToSaveMsg[0]) {
			if (!SHGetSpecialFolderPath(NULL, pPolicy->dirToSaveMsg, CSIDL_PERSONAL, TRUE))  goto  errLabel;
			if (trailDir(pPolicy->dirToSaveMsg, mycountof(pPolicy->dirToSaveMsg)))  goto  errLabel;
			_sntprintf(pPolicy->dirToSaveMsg, mycountof(pPolicy->dirToSaveMsg), _T("%s%s"), pPolicy->dirToSaveMsg, _T(CONST_subDir_msg));
			if (!bDir(pPolicy->dirToSaveMsg)) {
				BOOL  bRet = CreateDirectory(pPolicy->dirToSaveMsg, NULL);
				if (!bRet && GetLastError() != ERROR_ALREADY_EXISTS) {
					//qyDisplayLastError(  "Creating msgDir"  );  
					goto  errLabel;
				}
			}
		}
		//
	}
	else {
		qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, _T("0"));
		pPolicy->ucbSaveMsg = FALSE;
	}

	iErr = 0;

errLabel:
	return  iErr;
}

//   int  refreshWebCamSettings(  CAP_procInfo_video  *  pVc  )
__declspec(dllexport) int  refreshWebCamSettings(VIDEO_COMPRESSOR_CFG* pVideoCompressorCfg, CAP_procInfo_video* pVc)
{
	QY_MC* pQyMc = QY_GET_GBUF();

	memset(&pVc->policy, 0, sizeof(pVc->policy));

	if (pVideoCompressorCfg->dev.ucbSetDevResolution) {	//  2014/04/26
		pVc->policy.bih.biWidth = pVideoCompressorCfg->dev.iWidth;
		pVc->policy.bih.biHeight = pVideoCompressorCfg->dev.iHeight;
	}
	else {
		pVc->policy.bih.biWidth = pVideoCompressorCfg->common.iWidth_pic;
		pVc->policy.bih.biHeight = pVideoCompressorCfg->common.iHeight_pic;
	}



#if  0
	pVc->policy.bih.biCompression = CONST_fourcc_I420;	//  YUY2;
	myMessageBox(NULL, _T("Warning: refreshWebCampSettings. video format is fixed."), _T("Qycx"), MB_OK);
#endif

	return  0;
}

//  __declspec(  dllexport  ) int  myGetAvCompressorCfg(  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  BOOL  bConf,  int  level,  AV_COMPRESSOR_CFG  *  pCompressor  )
__declspec(dllexport) int  myGetAvCompressorCfg(unsigned  int  uiCapType, unsigned  int  uiSubCapType, int  iCapUsage, int  level, AV_COMPRESSOR_CFG* pCompressor)
{
	int					iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	PolicyAvParams& gAvParams = *pProcInfo->p_gAvParams;	//  QY_GET_PolicyAvParams(  );
	QY_REG				reg;
	TCHAR* pRegVal = NULL;
	TCHAR				tBuf[128] = _T("");
	TCHAR				tRootKey_av[256] = _T("");
	TCHAR* pT = NULL;
	long				lVal;

	int  iResId = 0;
	//  BOOL  bConf  =  iCapUsage  ==  CONST_capUsage_conf;

	//
	switch (uiCapType) {
	case  CONST_capType_av:
		switch (uiSubCapType) {
		case  CONST_subCapType_webcam:
			iResId = gAvParams.iResId_policyAvLevelTable_webcam;
			break;
		default:
#if 0
			if (bConf) {
				iResId = gAvParams.iResId_policyAvLevelTable;
			}
			else
#endif
			{
				iResId = gAvParams.iResId_policyAvLevelTable;
			}
			break;
		}
		break;
	case  CONST_capType_screen:
		iResId = gAvParams.iResId_policyAvLevelTable_screen;
		break;
	case  CONST_capType_mediaFile:
		iResId = gAvParams.iResId_policyAvLevelTable_mediaFile;
		break;
	case  CONST_capType_mediaDevice:
		if (uiSubCapType == CONST_subCapType_unresizable) {
			iResId = gAvParams.iResId_policyAvLevelTable_unresizable;
			break;
		}
		iResId = gAvParams.iResId_policyAvLevelTable_mediaDevice;
		break;
	case  CONST_capType_mosaic:
		if (uiSubCapType == CONST_subCapType_mosaic_video) {
			iResId = gAvParams.iResId_policyAvLevelTable_mosaic_video;
		}
		else if (uiSubCapType == CONST_subCapType_mosaic_resource) {
			iResId = gAvParams.iResId_policyAvLevelTable_mosaic_resource;
		}
		break;
	case  CONST_capType_slave:  //  2016/04/06
		iResId = gAvParams.iResId_policyAvLevelTable_slave_video;
		break;
	case  CONST_capType_qvcf:  //  2015/05/25
		break;

	default:
		_sntprintf(tBuf, mycountof(tBuf), _T("Err: myGetAvCompressorCfg failed, unprocessed capType %d"), uiCapType);
#ifdef  __DEBUG__
		traceLog(_T("%s"), tBuf);
#endif
		showInfo_open0(0, 0, tBuf);
		goto  errLabel;
		break;
	}

	//
	if (!level) {
		level = getPolicyAvLevel(pQyMc, uiCapType, uiSubCapType, iCapUsage);
	}

	//if (!qyGetDesByType(getResTable(0, &pQyMc->cusRes, iResId), level))    level = getDefaultPolicyAvLevel(pQyMc, uiCapType, uiSubCapType, iCapUsage);

	//
	getCompressorCfg(NULL, uiCapType, uiSubCapType, iCapUsage, level, pCompressor);

	iErr = 0;
errLabel:
	return  iErr;
}

int  getDefault_audioPlayCfg(int  level, AUDIO_PLAY_CFG* pAudioPlayCfg)
{
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	PolicyAvParams& gAvParams = *pProcInfo->p_gAvParams;	//  QY_GET_PolicyAvParams(  );
	AUDIO_PLAY_CFG  audioPlayCfg;

	if (!pAudioPlayCfg)  return  -1;

	memset(&audioPlayCfg, 0, sizeof(audioPlayCfg));
	switch (level) {

#if  0
	case  CONST_policyAvLevel_240p:
		audioPlayCfg = CONST_audioPlayCfg_1s;
		break;
#endif

	default:
#if  0
		if (!b4Core())  audioPlayCfg = gAvParams.CONST_audioPlayCfg_1s;
		else  audioPlayCfg = gAvParams.CONST_audioPlayCfg_07s;
#endif

		//  2014/07/13
		if (b4Core())  audioPlayCfg = gAvParams.CONST_audioPlayCfg_07s;	//gAvParams.CONST_audioPlayCfg_07s;
		else  if (b2Core())  audioPlayCfg = gAvParams.CONST_audioPlayCfg_07s;
		else  audioPlayCfg = gAvParams.CONST_audioPlayCfg_1s;

		break;
	}

	memcpy(pAudioPlayCfg, &audioPlayCfg, sizeof(AUDIO_PLAY_CFG));

	return  0;
}


__declspec(dllexport) int  initPolicyAvParams()	//  要在登陆后立即运行此函数. 2011/10/22
{
	//MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return  -1;
	//QY_MC* pQyMc = pProcInfo->pQyMc;
	//
	PolicyAvParams& gAvParams = *pProcInfo->p_gAvParams;	//  QY_GET_PolicyAvParams(  );
	PolicyAvParams* p = &gAvParams;
	int					level;

	memset(p, 0, sizeof(PolicyAvParams));

	//  1s
	p->CONST_audioPlayCfg_1s.usMinTimeInMsOfAudioDataPlaying = CONST_uiMinTimeInMsOfAudioDataPlaying_1s;					//  500;
	p->CONST_audioPlayCfg_1s.usAudioDataAddedToPlayEveryTime = CONST_uiAudioDataAddedToPlayEveryTime_1s;					//  200;
	p->CONST_audioPlayCfg_1s.usNotifyIntervalInMs_needMoreAudioData = CONST_uiNotifyIntervalInMs_needMoreAudioData_1s;		//  70;
	p->CONST_audioPlayCfg_1s.usMinTimeInMsToPlay = CONST_uiMinTimeInMsToPlay_1s;											//  2012/01/27
	p->CONST_audioPlayCfg_1s.usMaxTimeInMsToPlay = CONST_uiMaxTimeInMsToPlay_1s;											//  500;
	p->CONST_audioPlayCfg_1s.usMaxTimeInMsToBeRemoved = CONST_uiMaxTimeInMsToBeRemoved_1s;									//  200;
	//  0.7s
	p->CONST_audioPlayCfg_07s.usMinTimeInMsOfAudioDataPlaying = CONST_uiMinTimeInMsOfAudioDataPlaying_07s;
	p->CONST_audioPlayCfg_07s.usAudioDataAddedToPlayEveryTime = CONST_uiAudioDataAddedToPlayEveryTime_07s;
	p->CONST_audioPlayCfg_07s.usNotifyIntervalInMs_needMoreAudioData = CONST_uiNotifyIntervalInMs_needMoreAudioData_07s;
	p->CONST_audioPlayCfg_07s.usMinTimeInMsToPlay = CONST_uiMinTimeInMsToPlay_07s;
	p->CONST_audioPlayCfg_07s.usMaxTimeInMsToPlay = CONST_uiMaxTimeInMsToPlay_07s;
	p->CONST_audioPlayCfg_07s.usMaxTimeInMsToBeRemoved = CONST_uiMaxTimeInMsToBeRemoved_07s;
	//  0.5s
	p->CONST_audioPlayCfg_05s.usMinTimeInMsOfAudioDataPlaying = CONST_uiMinTimeInMsOfAudioDataPlaying_05s;
	p->CONST_audioPlayCfg_05s.usAudioDataAddedToPlayEveryTime = CONST_uiAudioDataAddedToPlayEveryTime_05s;
	p->CONST_audioPlayCfg_05s.usNotifyIntervalInMs_needMoreAudioData = CONST_uiNotifyIntervalInMs_needMoreAudioData_05s;
	p->CONST_audioPlayCfg_05s.usMinTimeInMsToPlay = CONST_uiMinTimeInMsToPlay_05s;
	p->CONST_audioPlayCfg_05s.usMaxTimeInMsToPlay = CONST_uiMaxTimeInMsToPlay_05s;
	p->CONST_audioPlayCfg_05s.usMaxTimeInMsToBeRemoved = CONST_uiMaxTimeInMsToBeRemoved_05s;





	//
	//  p->DEFAULT_audioPlayCfg_webcam  =  p->CONST_audioPlayCfg_1s;	
	getDefault_audioPlayCfg(0, &p->DEFAULT_audioPlayCfg_webcam);

	//
	level = CONST_policyAvLevel_256x144;
	//getDefault_audioPlayCfg(level, &p->audioPlayCfg_240p);	//  2013/03/08  

	p->QCIF.videoCompressors_av = CONST_videoCompressors_hwAccl;	//  CONST_videoCompressors_dmo;
	//safeStrnCpy(CONST_fourcc_HEVC, p->QCIF.videoFourccStr_av, mycountof(p->QCIF.videoFourccStr_av));
	iFourcc2Str(CONST_fourcc_HEVC, p->QCIF.videoFourccStr_av, mycountof(p->QCIF.videoFourccStr_av));
	p->QCIF.usMaxFps_toShareBmp = 30;					//24;				//  DEFAULT_LD_usMaxFps_toShareBmp;	//  5;
	p->QCIF.usFps_toShareBmp_videoConference = 30;		//24;	//  DEFAULT_LD_usFps_toShareBmp_videoConference;	//  5;
	p->QCIF.iW_av = CONST_w_256x144;	//  320;
	p->QCIF.iH_av = CONST_h_256x144;	//  240;



	//
	level = CONST_policyAvLevel_240p;
	//  p->audioPlayCfg_240p  =  CONST_audioPlayCfg_1s;			
	getDefault_audioPlayCfg(level, &p->audioPlayCfg_240p);	//  2013/03/08  

	p->LD.videoCompressors_av = DEFAULT_LD_videoCompressors_av;	//  CONST_videoCompressors_dmo;
	//  p->LD.videoFourccStr_av  =  DEFAULT_LD_videoFourccStr_av;				//  DEFAULT_fourccStr_dmo_video;
	safeStrnCpy(DEFAULT_LD_videoFourccStr_av, p->LD.videoFourccStr_av, mycountof(p->LD.videoFourccStr_av));
	p->LD.usMaxFps_toShareBmp = 30;					//24;				//  DEFAULT_LD_usMaxFps_toShareBmp;	//  5;
	p->LD.usFps_toShareBmp_videoConference = 30;		//24;	//  DEFAULT_LD_usFps_toShareBmp_videoConference;	//  5;
	p->LD.iW_av = CONST_w_240p;	//  320;
	p->LD.iH_av = CONST_h_240p;	//  240;

	//
	p->LD_av = p->LD;
	p->LD_av.usMaxFps_toShareBmp = DEFAULT_LD_usMaxFps_toShareBmp;
	p->LD_av.usFps_toShareBmp_videoConference = DEFAULT_LD_usFps_toShareBmp_videoConference;

	//
	//p->LD_webcam  =  p->LD;



	//  sd1
	level = CONST_policyAvLevel_480p;
	//	
	//  p->audioPlayCfg_480p  =  CONST_audioPlayCfg_1s;
	getDefault_audioPlayCfg(level, &p->audioPlayCfg_480p);

	p->SD1.videoCompressors_av = DEFAULT_SD1_videoCompressors_av;	//  CONST_videoCompressors_ipp;
	safeStrnCpy(DEFAULT_SD1_videoFourccStr_av, p->SD1.videoFourccStr_av, mycountof(p->SD1.videoFourccStr_av));	//  2014/07/13
	p->SD1.usMaxFps_toShareBmp = 30;					//24;
	p->SD1.usFps_toShareBmp_videoConference = 30;		//24;
	p->SD1.iW_av = CONST_w_480p;	//  640;
	p->SD1.iH_av = CONST_h_480p;	//  480;

	//  2014/07/13
	p->SD1_av = p->SD1;
	p->SD1_av.usMaxFps_toShareBmp = 30;				//10;
	p->SD1_av.usFps_toShareBmp_videoConference = 30;	//10;


	//  sd3
	level = CONST_policyAvLevel_576p;
	//
	//  p->audioPlayCfg_576p  =  CONST_audioPlayCfg_1s;
	getDefault_audioPlayCfg(level, &p->audioPlayCfg_576p);

	p->SD3.videoCompressors_av = DEFAULT_SD3_videoCompressors_av;	//  CONST_videoCompressors_ipp;			  
	safeStrnCpy(DEFAULT_SD3_videoFourccStr_av, p->SD3.videoFourccStr_av, mycountof(p->SD3.videoFourccStr_av));	//  2014/07/13
	p->SD3.usMaxFps_toShareBmp = 30;					//25;
	p->SD3.usFps_toShareBmp_videoConference = 30;		//25;
	p->SD3.iW_av = 720;
	p->SD3.iH_av = 576;
	//p->SD3_iW_webcam  =  720;												//  2012/06/12
	//  p->SD3_iH_webcam  =  576;												//  2012/06/12
	//p->SD3_usMaxFps_webcam  =  25;											//  2012/06/12
	//p->SD3_videoCompressors_webcam  =  CONST_videoCompressors_ipp;			//  2012/06/12
	//p->SD3_videoFourccStr_webcam  =  DEFAULT_fourccStr_ipp;					//  2012/06/12

	//  2014/07/13
	p->SD3_av = p->SD3;
	p->SD3_av.usMaxFps_toShareBmp = 30;				//10;
	p->SD3_av.usFps_toShareBmp_videoConference = 30;	//10;


	//  hd2,  2012/03/17
	level = CONST_policyAvLevel_720p;
	//
	//  p->audioPlayCfg_720p  =  CONST_audioPlayCfg_1s;
	getDefault_audioPlayCfg(level, &p->audioPlayCfg_720p);

	p->HD.videoCompressors_av = CONST_videoCompressors_hwAccl;	//  bUseCuda(  )  ?  CONST_videoCompressors_cuda  :  CONST_videoCompressors_hwAccl;
	safeStrnCpy(DEFAULT_fourccStr_mediaSdk, p->HD.videoFourccStr_av, mycountof(p->HD.videoFourccStr_av));	//  bUseCuda(  )  ?  DEFAULT_fourccStr_cuda  :  DEFAULT_fourccStr_mediaSdk;
	p->HD.usMaxFps_toShareBmp = 30;					//25;
	p->HD.usFps_toShareBmp_videoConference = 30;		//25;
	p->HD.iW_av = 1280;
	p->HD.iH_av = 720;

	//  2014/10/16
	p->HD_av = p->HD;
	p->HD_av.usMaxFps_toShareBmp = 30;					//25;
	p->HD_av.usFps_toShareBmp_videoConference = 30;		//25;
	//  2014/12/05. vlc存储的文件如果是h264 10fps,就会出现快进现象。所以都改成25fps算了
	p->HD_webcam = p->HD;		//  2015/02/10


	//  fullHd2
	level = CONST_policyAvLevel_1080p;
	//
	//  p->audioPlayCfg_fullHd2  =  CONST_audioPlayCfg_1s;
	getDefault_audioPlayCfg(level, &p->audioPlayCfg_1080p);

	p->fullHD.videoCompressors_av = CONST_videoCompressors_hwAccl;	//  bUseCuda(  )  ?  CONST_videoCompressors_cuda  :  CONST_videoCompressors_hwAccl;
	safeStrnCpy(DEFAULT_fourccStr_mediaSdk, p->fullHD.videoFourccStr_av, mycountof(p->fullHD.videoFourccStr_av));	//  bUseCuda(  )  ?  DEFAULT_fourccStr_cuda  :  DEFAULT_fourccStr_mediaSdk;
	p->fullHD.usMaxFps_toShareBmp = 30;					// 25;
	p->fullHD.usFps_toShareBmp_videoConference = 30;		// 25;
	p->fullHD.iW_av = 1920;
	p->fullHD.iH_av = 1080;

	//  2014/10/16
	p->fullHD_av = p->fullHD;
	p->fullHD_av.usMaxFps_toShareBmp = 30;				// 25;
	p->fullHD_av.usFps_toShareBmp_videoConference = 30;	// 25;
	//  2015/02/10
	p->fullHD_webcam = p->fullHD;

	//
	p->fullHD60.videoCompressors_av = CONST_videoCompressors_hwAccl;	//  bUseCuda(  )  ?  CONST_videoCompressors_cuda  :  CONST_videoCompressors_hwAccl;
	safeStrnCpy(DEFAULT_fourccStr_video4k, p->fullHD60.videoFourccStr_av, mycountof(p->fullHD60.videoFourccStr_av));	//  bUseCuda(  )  ?  DEFAULT_fourccStr_cuda  :  DEFAULT_fourccStr_mediaSdk;
	p->fullHD60.usMaxFps_toShareBmp = 60;					// 25;
	p->fullHD60.usFps_toShareBmp_videoConference = 60;		// 25;
	p->fullHD60.iW_av = 1920;
	p->fullHD60.iH_av = 1080;

	//
	p->video4k.videoCompressors_av = CONST_videoCompressors_hwAccl;	//  bUseCuda(  )  ?  CONST_videoCompressors_cuda  :  CONST_videoCompressors_hwAccl;
	safeStrnCpy(DEFAULT_fourccStr_video4k, p->video4k.videoFourccStr_av, mycountof(p->video4k.videoFourccStr_av));	//  bUseCuda(  )  ?  DEFAULT_fourccStr_cuda  :  DEFAULT_fourccStr_mediaSdk;
	p->video4k.usMaxFps_toShareBmp = 30;					// 25;
	p->video4k.usFps_toShareBmp_videoConference = 30;		// 25;
	p->video4k.iW_av = 1920 * 2;
	p->video4k.iH_av = 1080 * 2;


	//
	p->video4k60.videoCompressors_av = CONST_videoCompressors_hwAccl;	//  bUseCuda(  )  ?  CONST_videoCompressors_cuda  :  CONST_videoCompressors_hwAccl;
	safeStrnCpy(DEFAULT_fourccStr_video4k, p->video4k60.videoFourccStr_av, mycountof(p->video4k60.videoFourccStr_av));	//  bUseCuda(  )  ?  DEFAULT_fourccStr_cuda  :  DEFAULT_fourccStr_mediaSdk;
	p->video4k60.usMaxFps_toShareBmp = 60;					// 25;
	p->video4k60.usFps_toShareBmp_videoConference = 60;		// 25;
	p->video4k60.iW_av = 1920 * 2;
	p->video4k60.iH_av = 1080 * 2;






	//  dev2fps;video:screen,mediaDevice
	p->DEV2FPS_usMaxFps = 2;
	p->DEV2FPS_videoCompressors_screen = CONST_videoCompressors_dmo;
	p->DEV2FPS_videoFourccStr_screen = DEFAULT_fourccStr_dmo_screen;
	//
	p->DEV2FPS_videoCompressors_mediaFile = DEFAULT_DEV2FPS_videoCompressors;		//  CONST_videoCompressors_dmo;
	p->DEV2FPS_videoFourccStr_mediaFile = DEFAULT_DEV5FPS_videoFourccStr_av;
	p->DEV2FPS_videoCompressors_mediaDevice = DEFAULT_DEV2FPS_videoCompressors;
	p->DEV2FPS_videoFourccStr_mediaDevice = DEFAULT_DEV5FPS_videoFourccStr_av;

	//  dev5fps
	p->DEV5FPS_usMaxFps = 5;
	p->DEV5FPS_videoCompressors_screen = DEFAULT_DEV5FPS_videoCompressors;		//  CONST_videoCompressors_ipp;
	p->DEV5FPS_videoFourccStr_screen = DEFAULT_DEV5FPS_videoFourccStr_av;			//  DEFAULT_fourccStr_ipp;

	//  mosaic,  2014/11/15
	level = CONST_policyAvLevel_848x480;
	p->SD_mosaic_video.videoCompressors_av = DEFAULT_SD_videoCompressors_mosaic_video;
	safeStrnCpy(DEFAULT_SD_videoFourccStr_mosaic_video, p->SD_mosaic_video.videoFourccStr_av, mycountof(p->SD_mosaic_video.videoFourccStr_av));
	p->SD_mosaic_video.usMaxFps_toShareBmp = 10;
	p->SD_mosaic_video.usFps_toShareBmp_videoConference = 10;
	p->SD_mosaic_video.iW_av = 848;
	p->SD_mosaic_video.iH_av = 480;
	//  mosaic_resource
	p->DEV5FPS_usMaxFps_mosaic_resource = 5;
	p->DEV5FPS_videoCompressors_mosaic_resource = DEFAULT_DEV5FPS_videoCompressors_mosaic_resource;
	p->DEV5FPS_videoFourccStr_mosaic_resource = DEFAULT_DEV5FPS_videoFourccStr_mosaic_resource;


	//  2012/10/29		
	//p->DEV5FPS_350kb  =  350  *  1000;
	p->DEV5FPS_500kb = 500 * 1000;
	p->DEV5FPS_700kb = 700 * 1000;

	//  2016/04/06
	level = CONST_policyAvLevel_240p;
	p->LD_slave_video.videoCompressors_av = DEFAULT_LD_videoCompressors_slave_video;
	safeStrnCpy(DEFAULT_LD_videoFourccStr_slave_video, p->LD_slave_video.videoFourccStr_av, mycountof(p->LD_slave_video.videoFourccStr_av));
	p->LD_slave_video.usMaxFps_toShareBmp = 10;
	p->LD_slave_video.usFps_toShareBmp_videoConference = 10;
	p->LD_slave_video.iW_av = 320;
	p->LD_slave_video.iH_av = 240;
	//
	p->SD_slave_video.videoCompressors_av = DEFAULT_SD_videoCompressors_slave_video;
	safeStrnCpy(DEFAULT_SD_videoFourccStr_slave_video, p->SD_slave_video.videoFourccStr_av, mycountof(p->SD_slave_video.videoFourccStr_av));
	p->SD_slave_video.usMaxFps_toShareBmp = 10;
	p->SD_slave_video.usFps_toShareBmp_videoConference = 10;
	p->SD_slave_video.iW_av = 640;
	p->SD_slave_video.iH_av = 480;


	//
	p->pAudioCompressorsTable = CONST_audioCompressorsTable_hd;					//  2012/01/19
	p->pVideoCompressorsTable = CONST_videoCompressorsTable_hd;
	p->iResId_policyAvLevelTable = CONST_resId_policyAvLevelTable_standard;
	//
	p->iResId_policyAvLevelTable_mosaic_video = CONST_resId_policyAvLevelTable_mosaic_video;
	p->iResId_policyAvLevelTable_mosaic_resource = CONST_resId_policyAvLevelTable_mosaic_resource;
	//
	p->iResId_policyAvLevelTable_slave_video = CONST_resId_policyAvLevelTable_slave_video;			//  2016/04/06
	//
	p->iResId_policyAvLevelTable_screen = CONST_resId_policyAvLevelTable_screen_standard;
	//
	p->iResId_policyAvLevelTable_mediaFile = CONST_resId_policyAvLevelTable_standard;
	//
	p->iResId_policyAvLevelTable_mediaDevice = CONST_resId_policyAvLevelTable_standard;
	p->iResId_policyAvLevelTable_unresizable = CONST_resId_policyAvLevelTable_screen_standard;		//  2015/03/11
	//
	//  p->iResId_policyAvLevelTable_webcam  =  CONST_resId_policyAvLevelTable_webcam_basic;
	p->iResId_policyAvLevelTable_webcam = CONST_resId_policyAvLevelTable_basic;

	//
	//int  iAppAvLevel  =  qyGetAppAvLevel_qyMc(  pQyMc  );
	//switch  (  iAppAvLevel  )  
	{
#if  0
	case  CONST_qyAppAvLevel_hd:
		//
		p->pAudioCompressorsTable = CONST_audioCompressorsTable_hd;			//  2012/01/19
		p->pVideoCompressorsTable = CONST_videoCompressorsTable_hd;
		p->iResId_policyAvLevelTable = CONST_resId_policyAvLevelTable_standard;
		//  p->iResId_policyAvLevelTable_webcam  =  CONST_resId_policyAvLevelTable_webcam_standard;		//  2012/06/12
		p->iResId_policyAvLevelTable_webcam = CONST_resId_policyAvLevelTable_standard;		//  2012/06/12
		//
#if  0
		p->LD_webcam.videoCompressors_av = DEFAULT_LD_videoCompressors_av;		//  CONST_videoCompressors_ipp;
		safeStrnCpy(DEFAULT_LD_videoFourccStr_av, p->LD_webcam.videoFourccStr_av, mycountof(p->LD_webcam.videoFourccStr_av));			//  DEFAULT_fourccStr_ipp;
#endif
						  //
		p->SD1.videoCompressors_av = DEFAULT_SD1_videoCompressors_av;		//  CONST_videoCompressors_ipp;
		//  p->SD1.videoFourccStr_av  =  DEFAULT_SD1_videoFourccStr_av;		//  DEFAULT_fourccStr_ipp;
		//  safeStrnCpy(  DEFAULT_fourccStr_ipp,  p->SD1.videoFourccStr_av,  mycountof(  p->SD1.videoFourccStr_av  )  );
		safeStrnCpy(DEFAULT_SD1_videoFourccStr_av, p->SD1.videoFourccStr_av, mycountof(p->SD1.videoFourccStr_av));
		p->SD1.usMaxFps_toShareBmp = 24;
		p->SD1.usFps_toShareBmp_videoConference = 24;
		break;
	case  CONST_qyAppAvLevel_fullHd:
#endif
		//
		p->pAudioCompressorsTable = CONST_audioCompressorsTable_fullHd;
		p->pVideoCompressorsTable = CONST_videoCompressorsTable_fullHd;
		p->iResId_policyAvLevelTable = CONST_resId_policyAvLevelTable_high;
		p->iResId_policyAvLevelTable_screen = CONST_resId_policyAvLevelTable_screen_high;
		//  p->iResId_policyAvLevelTable_mediaDevice  =  CONST_resId_policyAvLevelTable_mediaDevice_high;
		p->iResId_policyAvLevelTable_mediaDevice = CONST_resId_policyAvLevelTable_high;
		p->iResId_policyAvLevelTable_unresizable = CONST_resId_policyAvLevelTable_screen_high;		//  2015/03/11
		//  p->iResId_policyAvLevelTable_webcam  =  CONST_resId_policyAvLevelTable_standard;		//  2012/06/12
		p->iResId_policyAvLevelTable_webcam = CONST_resId_policyAvLevelTable_high;		//  2014/04/25
		//  p->iResId_policyAvLevelTable_mediaFile  =  CONST_resId_policyAvLevelTable_mediaFile_high;
		p->iResId_policyAvLevelTable_mediaFile = CONST_resId_policyAvLevelTable_high;
		//
#if  0
		p->LD_webcam.videoCompressors_av = DEFAULT_LD_videoCompressors_av;		//  CONST_videoCompressors_ipp;
		safeStrnCpy(DEFAULT_LD_videoFourccStr_av, p->LD_webcam.videoFourccStr_av, mycountof(p->LD_webcam.videoFourccStr_av));			//  DEFAULT_fourccStr_ipp;
#endif
						  //
						  //p->DEV25FPS_videoCompressors_mediaDevice  =  bUseCuda(  )  ?  CONST_videoCompressors_cuda  :  CONST_videoCompressors_hwAccl;
						  //p->DEV25FPS_videoFourccStr_mediaDevice  =  bUseCuda(  )  ?  DEFAULT_fourccStr_cuda  :  DEFAULT_fourccStr_mediaSdk;
#if  0
		break;
	default:
		//  case  CONST_qyAppAvLevel_sd:
		p->pAudioCompressorsTable = CONST_audioCompressorsTable_sd;
		p->pVideoCompressorsTable = CONST_videoCompressorsTable_sd;
		p->iResId_policyAvLevelTable = CONST_resId_policyAvLevelTable_basic;
		p->iResId_policyAvLevelTable_screen = CONST_resId_policyAvLevelTable_screen_basic;
		//  p->iResId_policyAvLevelTable_mediaDevice  =  CONST_resId_policyAvLevelTable_mediaDevice_basic;
		p->iResId_policyAvLevelTable_mediaDevice = CONST_resId_policyAvLevelTable_basic;
		p->iResId_policyAvLevelTable_unresizable = CONST_resId_policyAvLevelTable_screen_basic;		//  2015/03/11
		p->iResId_policyAvLevelTable_mediaFile = CONST_resId_policyAvLevelTable_basic;
		//
		//
		//p->DEFAULT_usFps_mediaDevice  =  2;								//  2012/01/06
		// 
#if  0
		p->SD1.videoCompressors_av = DEFAULT_SD1_videoCompressors_av;	//  CONST_videoCompressors_dmo;
		//  p->SD1.videoFourccStr_av  =  DEFAULT_fourccStr_dmo_video;
		//  safeStrnCpy(  DEFAULT_fourccStr_dmo_video,  p->SD1.videoFourccStr_av,  mycountof(  p->SD1.videoFourccStr_av  )  );
		safeStrnCpy(DEFAULT_SD1_videoFourccStr_av, p->SD1.videoFourccStr_av, mycountof(p->SD1.videoFourccStr_av));
		p->SD1.usMaxFps_toShareBmp = 25;
		p->SD1.usFps_toShareBmp_videoConference = 10;
#endif
		//
		break;
#endif
	}

	return  0;
}


//
#if  0		//  2013/03/07
#define		DEFAULT_uiMinTimeInMsOfAudioDataPlaying				gAvParams.audioPlayCfg_sd.usMinTimeInMsOfAudioDataPlaying
#define		DEFAULT_uiAudioDataAddedToPlayEveryTime				gAvParams.audioPlayCfg_sd.usAudioDataAddedToPlayEveryTime
#define		DEFAULT_uiNotifyIntervalInMs_needMoreAudioData		gAvParams.audioPlayCfg_sd.usNotifyIntervalInMs_needMoreAudioData
#define		DEFAULT_uiMinTimeInMsToPlay							gAvParams.audioPlayCfg_sd.usMinTimeInMsToPlay			//  2012/01/27
#define		DEFAULT_uiMaxTimeInMsToPlay							gAvParams.audioPlayCfg_sd.usMaxTimeInMsToPlay
#define		DEFAULT_uiMaxTimeInMsToBeRemoved					gAvParams.audioPlayCfg_sd.usMaxTimeInMsToBeRemoved
#endif

#define		DEFAULT_uiMinTimeInMsOfAudioDataPlaying				gAvParams.audioPlayCfg_240p.usMinTimeInMsOfAudioDataPlaying
#define		DEFAULT_uiAudioDataAddedToPlayEveryTime				gAvParams.audioPlayCfg_240p.usAudioDataAddedToPlayEveryTime
#define		DEFAULT_uiNotifyIntervalInMs_needMoreAudioData		gAvParams.audioPlayCfg_240p.usNotifyIntervalInMs_needMoreAudioData
#define		DEFAULT_uiMinTimeInMsToPlay							gAvParams.audioPlayCfg_240p.usMinTimeInMsToPlay			//  2012/01/27
#define		DEFAULT_uiMaxTimeInMsToPlay							gAvParams.audioPlayCfg_240p.usMaxTimeInMsToPlay
#define		DEFAULT_uiMaxTimeInMsToBeRemoved					gAvParams.audioPlayCfg_240p.usMaxTimeInMsToBeRemoved



__declspec(dllexport) int  fixPlayCfg(MC_VAR_isCli* pProcInfo, AUDIO_PLAY_CFG* pPlayCfg)
{
	if (!pProcInfo)  return  -1;
	PolicyAvParams& gAvParams = *pProcInfo->p_gAvParams;	//  QY_GET_PolicyAvParams(  );

	int		iNotifyInterval = 0;

	if (pPlayCfg->usMinTimeInMsOfAudioDataPlaying  <  MIN_uiMinTimeInMsOfAudioDataPlaying || pPlayCfg->usMinTimeInMsOfAudioDataPlaying  >  MAX_uiMinTimeInMsOfAudioDataPlaying)
		pPlayCfg->usMinTimeInMsOfAudioDataPlaying = DEFAULT_uiMinTimeInMsOfAudioDataPlaying;
	if (pPlayCfg->usAudioDataAddedToPlayEveryTime  <  MIN_uiAudioDataAddedToPlayEveryTime || pPlayCfg->usAudioDataAddedToPlayEveryTime  >  MAX_uiAudioDataAddedToPlayEveryTime)
		pPlayCfg->usAudioDataAddedToPlayEveryTime = DEFAULT_uiAudioDataAddedToPlayEveryTime;

	iNotifyInterval = pPlayCfg->usNotifyIntervalInMs_needMoreAudioData;
	if (iNotifyInterval  <  MIN_uiNotifyIntervalInMs_needMoreAudioData || iNotifyInterval  >  MAX_uiNotifyIntervalInMs_needMoreAudioData)
		iNotifyInterval = DEFAULT_uiNotifyIntervalInMs_needMoreAudioData;
	pPlayCfg->usNotifyIntervalInMs_needMoreAudioData = iNotifyInterval;

	if (!pPlayCfg->usMinTimeInMsToPlay)  pPlayCfg->usMinTimeInMsToPlay = DEFAULT_uiMinTimeInMsToPlay;			//  2012/01/27
	if (!pPlayCfg->usMaxTimeInMsToPlay)  pPlayCfg->usMaxTimeInMsToPlay = DEFAULT_uiMaxTimeInMsToPlay;
	if (!pPlayCfg->usMaxTimeInMsToBeRemoved)  pPlayCfg->usMaxTimeInMsToBeRemoved = DEFAULT_uiMaxTimeInMsToBeRemoved;

	return  0;
}

