

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

#include	"qmcVideoCapture.h"
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
//#include	"soundProc_msAec/include/msAecCommon.h"


//
//#include	"isCliHelpPublic.h"
#include	"qycusResTemp.h"
#include	"qmcCFg.h"


//
 BOOL  bSupported_aec(  )
{
	BOOL  bRet  =  FALSE;

	//  2017/09/24
	if  (  bLikeXp(  )  )  {
		return  FALSE;
	}


	//  Figure out what os version we're on. We currently support echo-cancellation only on windows vista and 7.
#if 0
	OSVERSIONINFOEX  osvi;
	ZeroMemory(  &osvi,  sizeof(  OSVERSIONINFOEX  )  );
	osvi.dwOSVersionInfoSize  =  sizeof(  OSVERSIONINFOEX  );
	if  (  !GetVersionEx(  (  OSVERSIONINFO  *  )  &osvi  )  )  
	{
		printf(  "\t...  cannot determine platform;assuming AEC is unsupported:0x%1xL\n",  GetLastError(  )  );
		//  AEC_SUPPORTED  =  0;
	}
	else if  (  osvi.dwMajorVersion  >=  6  )  {
		if  (  osvi.dwMajorVersion  ==  6  &&  osvi.dwMinorVersion  ==  0  )  {
			printf(  "\t...  AEC  is supported on this platform(  Windows Vista  )\n"  );
		}
		else  {
			printf(  "\t...  AEC  is supported on this platform(  Windows 7  or  later  )\n"  );
		}

		//  AEC_SUPPORTED  =  1;
		bRet  =  TRUE;
	}
	else  {
		printf(  "\t...  AEC is not supported on Windows xp and earlier\n"  );
		//  AEC_SUPPORTED  =  0;
	}

#ifdef  __DEBUG__
		#if  0
			bRet  =  FALSE;
			traceLog(  (TCHAR*)_T(  "TEST: aec disabed"  )  );
		#endif
#endif

#endif

			bRet = true;

	return  bRet;
}


//

   //
 __declspec(  dllexport  )  int  getCamCapType(  MC_VAR_common  *  pProcInfo  )
{
	if  (  !pProcInfo  )  return  -1;
	QY_MC	*	pQyMc		=	(  QY_MC  *  )pProcInfo->pQyMc;//
	if  (  !pQyMc  )  return  -1;
	int			iCamCapType	=	0;

	//  2014/12/12
	if  (  pQyMc->appParams.rtspUrl[0]  )  {
		iCamCapType  =  CONST_camCapType_rtsp;
		return  iCamCapType;
	}

	//
	#ifndef  __WINCE__
			 iCamCapType  =  CONST_camCapType_directX;
	#else	 
			iCamCapType  =  CONST_camCapType_custom;
	#endif

	#ifdef  __DEBUG__
			#if  0
				#if  0
					 iCamCapType  =  CONST_camCapType_directX;					 
				#elif  0
					iCamCapType  =  CONST_camCapType_rtsp;		//  2014/02/23
				#elif  0
					 iCamCapType  =  CONST_camCapType_vfw;					 
				#else
					 iCamCapType  =  CONST_camCapType_custom;
				#endif
			#endif
	#endif

	TCHAR	tBuf[255  +  1]		=	_T(  ""  );
	QY_REG	reg;
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	lstrcpyn(  reg.rootKey,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  mycountof(  reg.rootKey  )  );

	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  (TCHAR*)_T(  CONST_regValName_camCapType  ),  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		iCamCapType  =  _ttol(  tBuf  );
	}

	//
	switch  (  iCamCapType  )  {
			case  CONST_camCapType_directX:
			case  CONST_camCapType_rtsp:
			case  CONST_camCapType_vfw:
			case  CONST_camCapType_custom:
				  break;
			default:
				    iCamCapType  =  CONST_camCapType_directX;
					break;
	}

errLabel:
	return   iCamCapType;
}


//

 //
 int  getDefaultRecordType()
 {
	 QY_MC* pQyMc = g_pQyMc;//
	 if (!pQyMc)  return  -1;

	 int			iType = 0;


	 //
	 iType = CONST_recordType_webRtc;


#if 0
	 if (pQyMc->b__USE_aec3__) {
		 iType = CONST_recordType_coreAudio;
		 traceLog((TCHAR*)_T("getRecordType_default: set recordType to coreAudio"));
	 }
#endif


	 //
	return   iType;
}


   //
   int  getDefaultAPlayType(  QY_MC  *  pQyMc,  int  *  piAPlayType_16kMono16  )
   {
	   //
	   //CCtxQyMc* pQyMc = QY_GET_GBUF();
	   if (pQyMc->appParams.bConfServer) {
		   //
		   *piAPlayType_16kMono16 = CONST_aPlayType_dSound;
		   //
		   return  CONST_aPlayType_dSound;
	   }


	   //
	   *piAPlayType_16kMono16  =  CONST_aPlayType_webRtc;



		return  CONST_aPlayType_dSound;
   }




     // ¶ÁÈ¡ºÍ¶Ô»°ÕßÏà¶ÔÓ¦µÄÊÓÆµ»áÒé²¼¾Ö
__declspec(  dllexport  ) int  getVideoConferenceCfg(  HKEY  hKeyRoot0,  LPCTSTR  pRootKey_qnmScheduler,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  VIDEO_CONFERENCE_CFG  *  pCfg  )
{
	TCHAR	tBuf[256]	=	_T(  ""  );

	if  (  !pRootKey_qnmScheduler  ||  !pCfg  )  return  -1;

	memset(  pCfg,  0,  sizeof(  pCfg[0]  )  );

	/*
	pCfg->iRows				=	2;
	pCfg->iCols				=	2;

	pCfg->iWidth_pic		=	640;
	pCfg->iHeight_pic		=	480;
	*/

	TCHAR			*	pRegVal;
	unsigned  long		usCnt_monPics_row			=  0;
	unsigned  long		usCnt_monPics_col			=  0;
	int					nTotal						=  0;
	unsigned  short		usMaxSpeakers				=  0;

	//
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_monPics_row  );
	if  (  !qyGetRegCfgT(  hKeyRoot0,  pRootKey_qnmScheduler,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  )  )  {
		usCnt_monPics_row  =  _ttol(  tBuf  );
	}
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_monPics_col  );
	if  (  !qyGetRegCfgT(  hKeyRoot0,  pRootKey_qnmScheduler,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  )  )  {
		usCnt_monPics_col  =  _ttol(  tBuf  );
	}
	usCnt_monPics_col  =  1;	//  2008/11/01, ÒòÎª²¼¾ÖÏÖÔÚÊÇ¶¯Ì¬µÄ¡£ËùÒÔ£¬ÕâÀï¹Ì¶¨Îª1

	nTotal  =  usCnt_monPics_row  *  usCnt_monPics_col;
	if  (  !nTotal  ||  nTotal  >  MAX_mems_taskAv  )  {
		//  
		usCnt_monPics_row	=	DEFAULT_mems_taskAv;	//  
		usCnt_monPics_col  =  1;
		//
		nTotal  =  usCnt_monPics_row  *  usCnt_monPics_col;
	}

	//  2009/02/19
	usMaxSpeakers  =  DEFAULT_usMaxSpeakers;
	//
#if 0
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_usMaxSpeakers  );
	if  (  !qyGetRegCfgT(  hKeyRoot0,  pRootKey_qnmScheduler,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  )  )  {
		usMaxSpeakers  =  (  unsigned  short  )_ttol(  tBuf  );
	}
#endif
	//  usCntLimit_activeMems_from  =  min(  nTotal,  min(  (  bLikeXp(  )  ?  MAX_activeMems_taskAv_xp  :  MAX_speakers_taskAv  ),  usCntLimit_activeMems_from  )  );
	//usMaxSpeakers  =  min(  nTotal,  min(  MAX_speakers_taskAv,  usMaxSpeakers  )  );
	//
	usMaxSpeakers  =  min(  MAX_speakers_taskAv,  usMaxSpeakers  );


	//
	pCfg->iRows  =  (  unsigned  short  )usCnt_monPics_row;
	pCfg->iCols  =  (  unsigned  short  )usCnt_monPics_col;
	pCfg->usMaxSpeakers  =  usMaxSpeakers;//  +  MAX_mosaicMems_taskAv  +  MAX_resourceMems_taskAv;


	//
	getAecCfg(  hKeyRoot0,  pRootKey_qnmScheduler,  &pCfg->aecCfg  );  



	return  0;
}

//
 //  2014/08/17
 __declspec(  dllexport  ) int  getAecCfg(  HKEY  hKeyRoot0,  LPCTSTR  pRootKey_qnmScheduler,  AEC_cfg  *  pCfg  )
{
	TCHAR	tBuf[256]	=	_T(  ""  );

	if  (  !pRootKey_qnmScheduler  ||  !pCfg  )  return  -1;

	memset(  pCfg,  0,  sizeof(  pCfg[0]  )  );

	TCHAR			*	pRegVal;

	//
	BOOL				bUseAec						=	DEFAULT_bUseAec;	//  2013/05/25
	BOOL				bFeatrModeOn				=	DEFAULT_bFeatrModeOn;	//  2014/08/17
	BOOL				bNoiseSup					=	DEFAULT_bNoiseSup;	//  2014/08/17
	BOOL				bAGC						=	DEFAULT_bAGC;			//  2014/08/17
	BOOL				bCntrClip					=	DEFAULT_bCntrClip;	//  2014/08/17

	//  2013/05/25
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_bUseAec  );
	if  (  !qyGetRegCfgT(  hKeyRoot0,  pRootKey_qnmScheduler,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  )  )  {
		bUseAec  =  _ttol(  tBuf  );
	}
	if  (   !bSupported_aec(  )  )  bUseAec  =  FALSE;

	//
	pCfg->bUseAec  =  bUseAec;
	

	//  2014/08/17
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_bFeatrModeOn  );
	if  (  !qyGetRegCfgT(  hKeyRoot0,  pRootKey_qnmScheduler,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  )  )  {
		bFeatrModeOn  =  _ttol(  tBuf  );
	}
	pCfg->bFeatrModeOn  =  bFeatrModeOn;

	if  (  pCfg->bFeatrModeOn  )  {

		pRegVal  =  (TCHAR*)_T(  CONST_regValName_bNoiseSup  );
		if  (  !qyGetRegCfgT(  hKeyRoot0,  pRootKey_qnmScheduler,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  )  )  {
			bNoiseSup  =  _ttol(  tBuf  );
		}
		pCfg->bNoiseSup  =  bNoiseSup;

		pRegVal  =  (TCHAR*)_T(  CONST_regValName_bAGC  );
		if  (  !qyGetRegCfgT(  hKeyRoot0,  pRootKey_qnmScheduler,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  )  )  {
			bAGC  =  _ttol(  tBuf  );
		}
		pCfg->bAGC  =  bAGC;

		pRegVal  =  (TCHAR*)_T(  CONST_regValName_bCntrClip  );
		if  (  !qyGetRegCfgT(  hKeyRoot0,  pRootKey_qnmScheduler,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  )  )  {
			bCntrClip  =  _ttol(  tBuf  );
		}
		pCfg->bCntrClip  =  bCntrClip;
	}
	else  {
		pCfg->bNoiseSup  =  0;
		pCfg->bAGC  =  0;
		pCfg->bCntrClip  =  0;
	}

	return  0;
}


//
__declspec(  dllexport  ) int  getPolicyIsClient(  MC_VAR_common  *  pProcInfo,  POLICY_isClient  * p   )
{
	int					iErr				=	-1;
	QY_MC			*	pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;//
	if  (  !pQyMc  )  return  -1;
	PolicyAvParams	*	pAvParams			=	(  PolicyAvParams  *  )pProcInfo->getPolicyAvParams(  );
	if  (  !pAvParams  )  return  -1;
	PolicyAvParams	&	gAvParams			=	*pAvParams;	//  *QY_GET_PolicyAvParams(  );
	//
	QMC_cfg  *  pCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pCfg  )  return  -1;
	//
	TCHAR			*	pRegVal				=	NULL;
	char				buf[256];
	QY_REG				reg;
	unsigned  char		ucCmd;
	unsigned  int		uiCapType;
	TCHAR				tBuf[255  +  1]		=	_T(  ""  );
	TCHAR			*	pT;
	long				lVal;
	TCHAR				rootKeyStr[256]		=  _T(  ""  );

	if  (  !p  )  return  -1;

	memset(  p,  0,  sizeof(  p[0]  )  );

	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );

	//  2013/11/14
#ifdef  __DEBUG__
		p->ucbRunAsAdvertisingPlayer  =  TRUE;
		traceLog(  (TCHAR*)_T(  "Note: getPolicyIsClient, ucbRunAsAdvertisingPlayer is 1"  )  );
#endif

	//
	ucCmd  =  DEFAULT_ruleIfMsgArrive;
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_ruleIfMsgArrive  );
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )
		&&  atol(  buf  )  )
	{
		ucCmd  =  (  unsigned  char  )atol(  buf  );
	}
	p->ucRuleIfMsgArrive  =  ucCmd;

	//  2014/03/29
	ucCmd  =  DEFAULT_hdAccl;
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_ucHardwareAccl  );
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )
		&&  atol(  buf  )  )
	{
		ucCmd  =  (  unsigned  char  )atol(  buf  );
	}
	p->ucHardwareAccl  =  ucCmd;
	//
	if (bFileExists(pQyMc->cfg.smCfgFile)) {
		unsigned  char  tmp_ucHardwareAccl = 0;
		if (!getCfgValByNameT(pQyMc->cfg.smCfgFile, (TCHAR*)_T(CONST_cfgName_ucHardwareAccl), tBuf, mycountof(tBuf))) {
			tmp_ucHardwareAccl = _ttol(tBuf);
		}
		if (tmp_ucHardwareAccl) {
			p->ucHardwareAccl = tmp_ucHardwareAccl;
		}
	}

	//  2013/11/14
	ucCmd  =  FALSE;
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_ucbRunAsAdvertisingPlayer  );
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )buf,  sizeof(  buf  ),  0  )  &&  atol(  buf  )  )  ucCmd  =  TRUE;
	p->ucbRunAsAdvertisingPlayer  =  ucCmd;

	//  2017/06/09
	ucCmd  =  FALSE;
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_dlgShareDynBmps_autopopupandhideOnStartup  );
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )buf,  sizeof(  buf  ),  0  )  &&  atol(  buf  )  )  ucCmd  =  TRUE;
	p->ucbDlgShareDynBmps_autopopupandhideOnStartup  =  ucCmd;
	
	//  2012/04/02
	ucCmd  =  FALSE;
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_ucbUseGlobalVWall  );
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )buf,  sizeof(  buf  ),  0  )  &&  atol(  buf  )  )  ucCmd  =  TRUE;
	p->ucbUseGlobalVWall  =  ucCmd;

	pRegVal  =  (TCHAR*)_T(  CONST_regValName_dirToSaveFile  );
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  (  char  *  )p->dirToSaveFile,  sizeof(  p->dirToSaveFile  ),  0  )  )  p->dirToSaveFile[0]  =  0;
	tTrim(  p->dirToSaveFile  );
	if  (  !p->dirToSaveFile[0]  )  {	//  ²»ÉèµÄ»°¾Í°Ñ°Ñ½ÓÊÕµ½µÄÎÄ¼þ¶¼´æÔÚmy documentsÄ¿Â¼Àï
		//  if  (  !SUCCEEDED(  mySHGetFolderPathW(  &pQyMc->env,  NULL,  CSIDL_PERSONAL  |  CSIDL_FLAG_CREATE,  NULL,  0,  p->dirToSaveFile  )  )  )  goto  errLabel;
		if  (  !pQyMc->appParams.bMcu  )  {
			if  (  !SHGetSpecialFolderPath(  NULL,  p->dirToSaveFile,  CSIDL_PERSONAL,  TRUE  )  )  goto  errLabel;
			traceLogA(  (char*)  "saveDir is %S",  p->dirToSaveFile  );
		}
	}
	if  (  p->dirToSaveFile[0]  )  {
		if  (  tTrailDir(  p->dirToSaveFile,  mycountof(  p->dirToSaveFile  )  )  )  goto  errLabel;
	}

	//  2014/04/26
	p->ucbSaveMsg  =  bEnable_saveMsgFlg(  pProcInfo,  NULL  );
	//
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_dirToSaveMsg  );
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  (  char  *  )p->dirToSaveMsg,  sizeof(  p->dirToSaveMsg  ),  0  )  )  p->dirToSaveMsg[0]  =  0;
	tTrim(  p->dirToSaveMsg  );
	if  (  !p->dirToSaveMsg[0]  )  {	//  ²»ÉèµÄ»°¾Í°Ñ°Ñ½ÓÊÕµ½µÄÎÄ¼þ¶¼´æÔÚmy documentsÄ¿Â¼Àï
		if  (  !pQyMc->appParams.bMcu  )  {
			if  (  !SHGetSpecialFolderPath(  NULL,  p->dirToSaveMsg,  CSIDL_PERSONAL,  TRUE  )  )  goto  errLabel;
			if  (  trailDir(  p->dirToSaveMsg,  mycountof(  p->dirToSaveMsg  )  )  )  goto  errLabel;
			_sntprintf(  p->dirToSaveMsg,  mycountof(  p->dirToSaveMsg  ),  (TCHAR*)_T(  "%s%s"  ),  p->dirToSaveMsg,  (TCHAR*)_T(  CONST_subDir_msg  )  );
		}
	}
	if  (  p->dirToSaveMsg[0]  )  {
		if  (  trailDir(  p->dirToSaveMsg,  mycountof(  p->dirToSaveMsg  )  )  )  goto  errLabel;
	}

	//  2012/08/02
	//  getPtzSettings(  &p->comPort_ptz  );

	//  2014/08/03
#if  0
	ucCmd  =  FALSE;
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_ucbSaveVideo  );
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  ucCmd  =  atol(  buf  );
	p->ucbSaveVideo  =  ucCmd;
#endif
	//
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_timeOfVideoFileInS  );
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	p->uiTimeOfVideoFileInS  =  _ttol(  tBuf  );
	if  (  p->uiTimeOfVideoFileInS  <  1  ||  p->uiTimeOfVideoFileInS  >  24  *  3600  )  p->uiTimeOfVideoFileInS  =  3600;
	//
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_dirToSaveVideo  );
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  (  char  *  )p->dirToSaveVideo,  sizeof(  p->dirToSaveVideo  ),  0  )  )  p->dirToSaveVideo[0]  =  0;
	tTrim(  p->dirToSaveVideo  );
	if  (  p->dirToSaveVideo[0]  )  {
		if  (  tTrailDir(  p->dirToSaveVideo,  mycountof(  p->dirToSaveVideo  )  )  )  goto  errLabel;
	}
	
	
	//
	ucCmd  =  TRUE;
	pRegVal  =  (TCHAR*)CONST_regValName_ucbShowNotification;
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  ucCmd  =  atol(  buf  );
	p->ucbShowNotification  =  ucCmd;

#if  0
	//  2011/08/02
	ucCmd  =  TRUE;
	pRegVal  =  CONST_regValName_ucbShowVideoHint;
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  ucCmd  =  atol(  buf  );
	p->ucbShowVideoHint  =  ucCmd;
#endif

	ucCmd  =  FALSE;
	pRegVal  =  (TCHAR*)CONST_regValName_ucbPreferCuda;
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  ) ucCmd  =  atol(  buf  );
	p->ucbPreferCuda  =  ucCmd;

	//  2012/11/06
	ucCmd  =  TRUE;		// FALSE, 2013/11/18.
	pRegVal  =  (TCHAR*)CONST_regValName_ucbLooping_mediaFile;
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  ) ucCmd  =  atol(  buf  );
	p->ucbLooping_mediaFile  =  ucCmd;

	//  2009/03/20
	p->video.uiCamCapType  =  getCamCapType(  pProcInfo  );
	p->audio.uiRecordType  =  getDefaultRecordType( );		//  2010/08/02
	//
#ifdef  __DEBUG__
		traceLogA(  (char*)  "getPolicyIsClient: uiCamCapType %d, uiRecordType %d",  p->video.uiCamCapType,  p->audio.uiRecordType  );
#endif

	//  2014/07/31
	ucCmd  =  FALSE;
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_ucbNot_selectDefaultRecorder  );
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  ucCmd  =  atol(  buf  );
	p->audio.ucbNot_selectDefaultRecorder  =  ucCmd;

	//  2008/11/20
	p->usTimeoutInMsToSwitch  =  DEFAULT_usTimeoutInMsToSwitch_isClient;							//  2008/10/28, ¶ÔmediaºÍrealTimeMediaÍ¨µÀ£¬°üÔÚ daemon ÖÐµÄ¶ÁÈëºÍ·¢³ö£¬²»ÄÜ³¬¹ýÕâ¸öÊ±¼ä¡£·ñÔò£¬¶ªÆú¡£
	pRegVal  =  (TCHAR*)CONST_regValName_usTimeoutInMsToSwitch;
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	lVal  =  (  short  )_tcstol(  tBuf,  &pT,  10  );
	if  (  lVal  )  p->usTimeoutInMsToSwitch  =  (  unsigned  short  )lVal;

	//  2008/11/22
	p->usTimeoutInMsToSwitch_rt  =  DEFAULT_usTimeoutInMsToSwitch_rt_isClient;							//  2008/10/28, ¶ÔmediaºÍrealTimeMediaÍ¨µÀ£¬°üÔÚ daemon ÖÐµÄ¶ÁÈëºÍ·¢³ö£¬²»ÄÜ³¬¹ýÕâ¸öÊ±¼ä¡£·ñÔò£¬¶ªÆú¡£
	pRegVal  =  (TCHAR*)CONST_regValName_usTimeoutInMsToSwitch_rt;
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	lVal  =  (  short  )_tcstol(  tBuf,  &pT,  10  );
	if  (  lVal  )  p->usTimeoutInMsToSwitch_rt  =  (  unsigned  short  )lVal;

	//
	p->usTimeoutInMsToSwitch_file  =  DEFAULT_usTimeoutInMsToSwitch_file_isClient;  


	 //  2012/03/31
	 //  #define		MAX_nThreads_dec_basic		90
	 #define		MAX_nThreads_dec			100
	 #define		MAX_nThreads_dec_x64		200				//  2014/10/14
#if  0
	#define		CONST_uiMaxQNodes_vwRuleQ		256
#else
	#define		CONST_uiMaxQNodes_vwRuleQ		50
#endif

	 //  2012/03/30
	 p->usMax_nPlayers  =  isWinCe(  )  ?  DEFAULT_maxusCnt_players_ce  :  DEFAULT_maxusCnt_players;	//  64;
	 p->usMax_nPlayers_gps  =  isWinCe(  )  ?  DEFAULT_maxusCnt_players_gps_ce  :  DEFAULT_maxusCnt_players_gps;	//  2012/05/07
	 //
	 //  if  (  qyGetAppAvLevel_qyMc(  )  <  CONST_qyAppAvLevel_hd  )  
	 if  (  bAppX64(  )  )  
	 {	//  2014/05/09
		 //  p->usMax_nThreads_dec  =  MAX_nThreads_dec_basic;
		 p->usMax_nThreads_dec  =  MAX_nThreads_dec_x64;
		 }
	 else  {
		   p->usMax_nThreads_dec  =  MAX_nThreads_dec;
	 }
	 //
	 p->uiMaxQNodes_vwRuleQ  =  CONST_uiMaxQNodes_vwRuleQ;

	 tBuf[0]  =  0;
	 qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  (TCHAR*)_T(  CONST_regValName_usMax_nPlayers  ),  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  );
	 if  (  _ttol(  tBuf  )  >=  5  &&  _ttol(  tBuf  )  <  200  )  p->usMax_nPlayers  =  _ttol(  tBuf  );

	 tBuf[0];
	 qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  (TCHAR*)_T(  CONST_regValName_usMax_nThreads_dec  ),  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  );
	 if  (  _ttol(  tBuf  )  >=  5  &&  _ttol(  tBuf  )  <  200  )  p->usMax_nThreads_dec  =  _ttol(  tBuf  );

	 tBuf[0]  =  0;
	 qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  (TCHAR*)_T(  CONST_regValName_uiMaxQNodes_vwRuleQ  ),  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  );
	 if  (  _ttol(  tBuf  )  >=  5  &&  _ttol(  tBuf  )  <  200  )  p->uiMaxQNodes_vwRuleQ  =  _ttol(  tBuf  );



	//  2009/02/25
	ucCmd  =  FALSE;
	pRegVal  =  (TCHAR*)CONST_regValName_ucbManullyPermitToSpeakOnVideoConference;
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )buf,  sizeof(  buf  ),  0  )  &&  atol(  buf  )  )  ucCmd  =  TRUE;
	p->ucbManullyPermitToSpeakOnVideoConference  =  ucCmd;

	//  2016/02/15
	p->avRules.uiCmd_autoAnswer_av  =  CONST_ruleCmd_permit;
	pRegVal  =  (TCHAR*)CONST_regValName_usAutoAnswer_av;
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	lVal  =  (  short  )_tcstol(  tBuf,  &pT,  10  );
	if  (  lVal  )  p->avRules.uiCmd_autoAnswer_av  =  (  unsigned  short  )lVal;
	
	//  2017/07/11;
	ucCmd  =  pCfg->envVar.default_ucbLetConfMgrSetMicOn;//pProcInfo->cfg.  //FALSE;
	pRegVal  =  (TCHAR*)CONST_regValName_ucbLetConfMgrSetMicOn;
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )buf,  sizeof(  buf  ),  0  )  )  ucCmd  =  atol(  buf  );
	p->avRules.ucbLetConfMgrSetMicOn  =  ucCmd;


	//  2012/04/07;
	ucCmd  =  FALSE;
	pRegVal  =  (TCHAR*)CONST_regValName_ucbScrollForEnlagedImg;
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )buf,  sizeof(  buf  ),  0  )  &&  atol(  buf  )  )  ucCmd  =  TRUE;
	p->ucbScrollForEnlagedImg  =  ucCmd;

	//  2009/02/26
	pRegVal  =  (TCHAR*)CONST_regValName_iTimeoutInMs_channelIdle_others;
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	lVal  =  _tcstol(  tBuf,  &pT,  10  );
	if  (  lVal  <=  MIN_iTimeoutInMs_channelIdle  ||  lVal  >  MAX_iTimeoutInMs_channelIdle  )  lVal  =  DEFAULT_iTimeoutInMs_channelIdle_others;
	if  (  lVal  !=  pQyMc->cfg.iTimeoutInMs_channelIdle_others  )  pQyMc->cfg.iTimeoutInMs_channelIdle_others    =  lVal;

	//  2010/08/25
	traceLog(  (TCHAR*)_T(  "Not finished: getPolicyIsClient: get cfg of notification"  )  );
	p->notification.iW_pic  =  160;
	p->notification.iH_pic  =  120;
#if  0
	p->notification.iH_static  =  60;
#else
	#ifdef  __DEBUG__
			traceLog(  (TCHAR*)_T(  "Warning: 这里把notification.iH_static设太大了，把iH_pic给遮住了"  )  );
	#endif
	p->notification.iH_static  =  120;
#endif
	p->notification.usTimeInMsToPop  =  200;
	p->notification.ucbBeep  =  TRUE;

	//  2010/09/03
	p->dlgTalk.ucbShowImGrpMems  =  FALSE;

		//
	//if  (  bApp_ts(  pQyMc  )  ) 
	if  (  !pProcInfo->bUse_imObjView_as_guiWnd(  )  )  {
		if  (  pQyMc->ucbApp_ts  )
		{  
			ucCmd  =  CONST_snmpFalse;
			}
		}
	else  //  #else
	{
		ucCmd  =  CONST_snmpTrue;
	}	//  #endif
	pRegVal  =  (TCHAR*)CONST_regValName_snmpbShowMsgBox;
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  ucCmd  =  atol(  buf  );
	p->dlgTalk.snmpbShowMsgBox  =  ucCmd;


	//  2018/10/30
	if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hzj  )  {
		p->ucbDlgShareDynBmps_autopopupandhideOnStartup  =  TRUE;
		//
		p->ucbRunAsAdvertisingPlayer  =  TRUE;
	}
	//		
	p->ucbDlgShareDynBmps_autopopupandhideOnStartup  =  TRUE;
	

	//
	iErr  =  0;

errLabel:
	
	return  iErr;
}


  BOOL  bEnable_saveMsgFlg(  MC_VAR_common  *  pProcInfo,  bool  *  pbFlgSetAlready  )
  {
	  if  (  !pProcInfo  )  return  FALSE;
	  QY_MC	*	pQyMc	=	(  QY_MC  *  )pProcInfo->pQyMc;//
	  if  (  !pQyMc  )  return  FALSE;

	  unsigned  char  ucCmd;
	  QY_REG	reg;
	  TCHAR	*	pRegVal;
	  char  buf[128];
	  BOOL	bFlgSetAlready  =  FALSE;

	  memset(  &reg,  0,  sizeof(  reg  )  );
	  reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );

  	ucCmd  =  FALSE;
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_ucbSaveMsg  );
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  (  char  *  )buf,  sizeof(  buf  ),  0  )  )  {
		//
		bFlgSetAlready  =  TRUE;
		//
		if  (  atol(  buf  )  )  ucCmd  =  TRUE;
	}

	if  (  pbFlgSetAlready  )  {
		*pbFlgSetAlready  =  bFlgSetAlready;
	}

	return  ucCmd;
  }


  //
   //
  bool bGetMcuInitCfg(TCHAR* cfgFileName, Mcu_initCfg* pCfg)
  {
	  bool  bRet = false;

	  TCHAR  tBuf[256];
	  char  buf[256];

	  //
	  if (!pCfg)  return  bRet;
	  memset(pCfg, 0, sizeof(pCfg[0]));

	  //
	  if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_saveAvUrl_prefix), tBuf, mycountof(tBuf))) {
		  tBuf[0] = 0;
	  }
	  myTChar2Utf8(tBuf, buf, mycountof(buf));
	  safeStrnCpy(buf, pCfg->saveAvUrl_prefix, mycountof(pCfg->saveAvUrl_prefix));

	  //
	  if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_ffmpegPath), tBuf, mycountof(tBuf))) {
		  tBuf[0] = 0;
	  }
	  safeTcsnCpy(tBuf, pCfg->tFfmpegPath, mycountof(pCfg->tFfmpegPath));

	  //
	  //
	  if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_bDraw3dFps), tBuf, mycountof(tBuf))) {
		  tBuf[0] = 0;
	  }
	  pCfg->bDraw3dFps = _ttol(tBuf);

	  //										   CONSST_cfgName_bNoSaveAv_conf
	  if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_bSaveAv_conf), tBuf, mycountof(tBuf))) {
		  tBuf[0] = 0;
	  }
	  pCfg->bSaveAv_conf = _ttol(tBuf);
	  //
	  if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_bSaveAv_trans), tBuf, mycountof(tBuf))) {
		  tBuf[0] = 0;
	  }
	  pCfg->bSaveAv_trans = _ttol(tBuf);




	  //
	  bRet = true;
	  return  bRet;
  }




