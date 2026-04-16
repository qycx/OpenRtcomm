// DlgPolicyIsClient.cpp : implementation file
//

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

#include	"DlgPolicyIsClient.h"

#ifndef  __WINCE__
//  #include	"DlgVideoCompressors.h"
#endif

#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qyCusResTemp.h"
#ifndef  __WINCE__
	#include	"qyPs.h"
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


 //  
 extern  QY_DMITEM  CONST_audioCompressorsTable_sd[];
 extern  QY_DMITEM  CONST_videoCompressorsTable_sd[];
 extern  QY_DMITEM  CONST_audioCompressorsTable_hd[];
 extern  QY_DMITEM  CONST_videoCompressorsTable_hd[];
 extern  QY_DMITEM  CONST_audioCompressorsTable_fullHd[]; 
 extern  QY_DMITEM  CONST_videoCompressorsTable_fullHd[];


 //
 extern QY_DMITEM	CONST_ruleIfMsgArriveTable[];


//
//
//
#define		DEFAULT_iW_webcam_winCe									160
#define		DEFAULT_iH_webcam_winCe									120
//
#define		DEFAULT_iW_webcam_ts									640					//  2011/03/27
#define		DEFAULT_iH_webcam_ts									480

////////////////////////////////////


 





//
int  getDefault_audioPlayCfg(  int  level,  AUDIO_PLAY_CFG  *  pAudioPlayCfg  );

__declspec(  dllexport  )  int  showDlgPolicyIsClient(  HWND  hParent  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int		iRet	=	-1;
	
	CDlgPolicyIsClient	dlg(  CWnd::FromHandle(  hParent  )  );
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	iRet  =  IDOK;
errLabel:
	return  iRet;
}

#if 0 
 //  2012/06/25
 BOOL  bUseCuda(  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );

	//
#if  0
	if  (  pProcInfo->cfg.policy.ucbPreferCuda  )  return  TRUE;
	if  (  bSupported_mediaSdk(  )  )  return  FALSE;
	return  TRUE;
#endif
#ifdef  __DEBUG__
		traceLog(  _T(  "暂时不使用cuda"  )  );
#endif
	return  FALSE;
}
#endif



 //  AUDIO_PLAY_CFG		CONST_audioPlayCfg_15s;
 //  AUDIO_PLAY_CFG		CONST_audioPlayCfg_1s,CONST_audioPlayCfg_07s,CONST_audioPlayCfg_05s;





 //  2013/03/07























  //



 

 void  deleteCfgOfIsClient_level(   QY_REG  reg,  int  iResId  )
{	
	int					iErr			=	-1;
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	TCHAR			*	pRegVal			=	NULL;
	//	int				idc;
	unsigned  char		ucCmd			=	0;
	TCHAR				tBuf[1024];
	//
	QY_DMITEM		*	pItemI			=	NULL;
	TCHAR			*	name;
	TCHAR			*	pT;
	TCHAR			*   pTable;
	//


	//  2014/04/26
	pRegVal  =  _T(  CONST_regValName_ucbSetDevResolution  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  _T(  CONST_regValName_iDevWidth  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  _T(  CONST_regValName_iDevHeight  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );



	//
	for  (  pItemI  =  getResTable(  0,  &pQyMc->cusRes,  iResId  );  pItemI->type  !=  -1;  pItemI ++  )  {
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\level%d"  ),  reg.rootKey,  pItemI->type  );
		 //
		 pRegVal  =  CONST_regValName_uiMinTimeInMsOfAudioDataPlaying;
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  CONST_regValName_uiAudioDataAddedToPlayEveryTime;
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  CONST_regValName_uiNotifyIntervalInMs_needMoreAudioData;
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );
		
		 //  2012/01/27
		 pRegVal  =  CONST_regValName_uiMinTimeInMsToPlay;
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  CONST_regValName_uiMaxTimeInMsToPlay;
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  CONST_regValName_uiMaxTimeInMsToBeRemoved;
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  _T(  CONST_regValName_iWidth_pic  );
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  _T(  CONST_regValName_iHeight_pic  );
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  _T(  CONST_regValName_audioCompressorName  );
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  _T(  CONST_regValName_audioCompressors  );
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  CONST_regValName_uiBytesRecorded_perBlockAlign;
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  CONST_regValName_ucbOrgAudioFmt;
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  CONST_regValName_uiChannel;
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  CONST_regValName_uiSample;
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  CONST_regValName_uiBit;
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  CONST_regValName_audio_avgBitrate;
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  _T(  CONST_regValName_usMaxFps_toShareBmp  );
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  _T(  CONST_regValName_usMinFps_toShareBmp  );
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  _T(  CONST_regValName_videoCompressors  );
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  _T(  CONST_regValName_videoCompressorName  );
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  _T(  CONST_regValName_v_fourccStr  );
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );
		 //  2012/02/08
		 pRegVal  =  _T(  CONST_regValName_videoEffect  );
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );
		 //  2012/06/27
		 pRegVal  =  _T(  CONST_regValName_avgBitrate  );
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );
		 //
		 pRegVal  =  _T(  CONST_regValName_wfx_enc_wFormatTag  );
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  _T(  CONST_regValName_wfx_enc_nChannels  );
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  _T(  CONST_regValName_wfx_enc_nSamplesPerSec  );
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );
	
		 pRegVal  =  _T(  CONST_regValName_wfx_enc_nAvgBytesPerSec  );
	 	 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );
		
	 	 pRegVal  =  _T(  CONST_regValName_wfx_enc_wBitsPerSample  );
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 pRegVal  =  _T(  CONST_regValName_ucSeconds_perFrame  );
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 //	idc			=	IDC_EDIT_ucSeconds_perFrame;
		 pRegVal		=	CONST_regValName_ucSeconds_perFrame_videoConference;
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );

		 //	idc			=	IDC_EDIT_usFrames_perSecond;
		 pRegVal		=	CONST_regValName_usFps_videoConference;
		 qyDelRegCfgT(  reg.hKeyRoot0,  tBuf,  CQyString(  pRegVal  )  );


		 if  (  ERROR_SUCCESS  !=  RegDeleteKey(  reg.hKeyRoot0,  tBuf  )  )  iErr  =  -1;
		 else  iErr  =  0;

	 }

	return;
}


 void  deleteCfgOfIsClient_capUsage(   unsigned int uiCapType,  unsigned int  uiSubCapType  )
{	
	int					iErr			=	-1;
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	PolicyAvParams	&	gAvParams		=	*pProcInfo->p_gAvParams;	//  QY_GET_PolicyAvParams(  );

	QY_REG				reg;
	TCHAR			*	pRegVal			=	NULL;
	//	int				idc;
	//  unsigned  char		ucCmd			=	0;
	//  TCHAR				tBuf[1024];
	//
	QY_DMITEM		*	pItemI			=	NULL;
	//  TCHAR			*	name;
	//  TCHAR			*	pT;
	QY_DMITEM		*   pTable;
	//

	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;

	//
	pTable  =  CONST_capUsageTable;
	for  (  pItemI  =  pTable;  pItemI->type  !=  -1;  pItemI ++  )  {
		 //
		 if  (  getRegRootKey_qmc(  uiCapType,  uiSubCapType,  pItemI->type,  reg.rootKey,  mycountof(  reg.rootKey  )  )  )  continue;

		 //
		 deleteCfgOfIsClient_level(  reg,  gAvParams.iResId_policyAvLevelTable  );

		 pRegVal  =  CONST_regValName_policyAvLevel_req;
		 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CQyString(  pRegVal  )  );


		 if  (  ERROR_SUCCESS  !=  RegDeleteKey(  reg.hKeyRoot0,  reg.rootKey  )  )  iErr  =  -1;
		 else  iErr  =  0;

	 }

	return;
}


 void  deleteCfgOfIsClient(  )
{	
	int					iErr			=	-1;
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	PolicyAvParams	&	gAvParams		=	*pProcInfo->p_gAvParams;	//  QY_GET_PolicyAvParams(  );
	TCHAR			*	pRegVal			=	NULL;
	//	int				idc;
	unsigned  char		ucCmd			=	0;
	TCHAR				tBuf[1024];
	//
	QY_DMITEM		*	pItemJJ			=	NULL;
	QY_DMITEM		*	pItemQQ			=	NULL;
	QY_DMITEM		*	pItemYY			=	NULL;
	QY_DMITEM		*	pItemI			=	NULL;
	TCHAR			*	name;
	TCHAR			*	pT;
	TCHAR			*	pU;
	int					level			=	0;		
	unsigned  int		uiCapType		=	0;
	//
	QY_REG				reg;
	CQyString			rootKeyStr_capType,  rootKeyStr_level;

	//
	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	//  safeStrnCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );

	pRegVal  =  _T(  CONST_regValName_bNotUseDb  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	pRegVal  =  _T(  CONST_regValName_ucbRunAsAdvertisingPlayer  );
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );

	pRegVal		=  _T(  CONST_regValName_ucbUseGlobalVWall  );
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );

	//	idc			=	IDC_COMBO_ruleIfMsgArrive;
	pRegVal		=	_T(  CONST_regValName_ruleIfMsgArrive  );
	//	qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  _ltot(  ucCmd,  tBuf,  10  )  );
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );

	pRegVal		=	_T(  CONST_regValName_ucHardwareAccl  );
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );

	//	idc			=	IDC_EDIT_dirToSaveFile;
	pRegVal		=	_T(  CONST_regValName_dirToSaveFile  );
	//	qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CONST_regValName_dirToSaveFile,  m_var.policy.dirToSaveFile  );
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );

	//  2014/04/26
	pRegVal  =  _T(  CONST_regValName_ucbSaveMsg  );
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );
	
	//  2014/04/26
	pRegVal  =  _T(  CONST_regValName_dirToSaveMsg  );
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );
	
	//
	pRegVal  =  _T(  CONST_regValName_timeOfVideoFileInS  );
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );

	//  2014/08/07
	pRegVal  =  _T(  CONST_regValName_dirToSaveVideo  );
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );
	
	//
	pRegVal  =  CONST_regValName_remoteStorageUsers;
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );
	

	//	idc			=	IDC_CHECK_ucbOnlyNetSm;
	pRegVal		=	_T(  CONST_regValName_ucbOnlyNetSm  );
	//	qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CONST_regValName_ucbOnlyNetSm,  m_var.policy.ucbOnlyNetSm  ?  _T(  "1"  )  :  _T(  ""  )  );
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );

	//	idc			=	IDC_CHECK_ucbOnlyPhoneMsgr;
	pRegVal		=	_T(  CONST_regValName_ucbOnlyPhoneMsgr  );
	//	qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CONST_regValName_ucbOnlyPhoneMsgr,  m_var.policy.ucbOnlyPhoneMsgr  ?  _T(  "1"  )  :  _T(  ""  )  );
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );

	//  2012/03/23
	pRegVal	    =	_T(  CONST_regValName_ucbNotUseDmo  );
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );

	//	idc			=	IDC_EDIT_baud;
	pRegVal		=	CONST_regValName_baud;
	//	qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CONST_regValName_baud, _ltot(  m_var.policy.baud,  tBuf,  10  )  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	//	idc			=	IDC_CHECK_ucbPermitOtherSm;
	pRegVal		=	CONST_regValName_ucbPermitOtherSm;
	//	qySetRegCfgT(  HKEY_LOCAL_MACHINE,  CQyString(  reg.rootKey  ),  CONST_regValName_ucbPermitOtherSm,  m_var.policy.ucbPermitOtherSm  ?  _T(  "1"  )  :  _T(  ""  )  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	//  2012/08/02
	pRegVal		=	CONST_regValName_ptzProtoType;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal		=	CONST_regValName_ptzAddr;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal		=	CONST_regValName_comName;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal		=	CONST_regValName_comBaud;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal		=	CONST_regValName_comParity;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal		=	CONST_regValName_comData;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal		=	CONST_regValName_comStopBit;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	//
	pRegVal		=	CONST_regValName_remotePtzUsers;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );


	pRegVal  =  CONST_regValName_snmpbShowMsgBox;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  CONST_regValName_ucbShowNotification;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  CONST_regValName_ucbPreferCuda;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  CONST_regValName_ucbLooping_mediaFile;											//  2012/11/06
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	
	//	idc  =  IDC_EDIT_usTimeoutInMsToSwitch;
	pRegVal  =  CONST_regValName_usTimeoutInMsToSwitch;
	//	qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CONST_regValName_usTimeoutInMsToSwitch, _ltot(  m_var.policy.usTimeoutInMsToSwitch,  tBuf,  10  )  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	//	idc  =  IDC_EDIT_usTimeoutInMsToSwitch_rt;
	pRegVal  =  CONST_regValName_usTimeoutInMsToSwitch_rt;
	//	qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CONST_regValName_usTimeoutInMsToSwitch_rt, _ltot(  m_var.policy.usTimeoutInMsToSwitch_rt,  tBuf,  10  )  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	//  2009/11/11		
	pRegVal  =  _T(  CONST_regValName_monPics_row  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	pRegVal  =  _T(  CONST_regValName_monPics_col  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	pRegVal  =  _T(  CONST_regValName_usMaxSpeakers  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	//  2013/05/25
	pRegVal  =  _T(  CONST_regValName_bUseAec  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	//  2014/08/17
	pRegVal  =  _T(  CONST_regValName_bFeatrModeOn  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	pRegVal  =  _T(  CONST_regValName_bNoiseSup  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	pRegVal  =  _T(  CONST_regValName_bAGC  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	pRegVal  =  _T(  CONST_regValName_bCntrClip  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	//  2014/05/02
	pRegVal  =  _T(  CONST_regValName_recordType  );
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );

	//  2014/07/31
	pRegVal  =  _T(  CONST_regValName_ucbNot_selectDefaultRecorder  );
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );

	//  2011/10/25
	pRegVal  =  _T(  CONST_regValName_recorder_selected  );
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );

	//  2014/05/02
	pRegVal  =  _T(  CONST_regValName_camCapType  );
	qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );

	//
	pRegVal  =  _T(  CONST_regValName_webcam_selected  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	//  2014/05/02
	pRegVal  =  _T(  CONST_regValName_rtspUrl_selected  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );


	//  2009/07/27,	idc	 =  IDC_CHECK_ucbManullyPermitToSpeakOnVideoConference;
	pRegVal  =  CONST_regValName_ucbManullyPermitToSpeakOnVideoConference;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	//  2012/04/07
	pRegVal  =  CONST_regValName_ucbScrollForEnlagedImg;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	//  2016/02/15
	pRegVal  =  CONST_regValName_usAutoAnswer_av;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	//	2011/08/07, idc  =  IDC_EDIT_req;
	pRegVal  =  CONST_regValName_policyAvLevel_req;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	//	idc  =  IDC_EDIT_reply;
#if  0
	pRegVal  =  CONST_regValName_policyAvLevel_conf;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
#endif

	//	idc			=	IDC_EDIT_usMaxFPS_toShareBmp;
	//	idc  =  IDC_EDIT_usMaxFPS_capScreen;
	//  不熟悉这个参数，没有测试
	//	idc  =  IDC_EDIT_iTimeoutInMs_channelIdle;
	pRegVal  =  CONST_regValName_iTimeoutInMs_channelIdle_others;
	//	qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CONST_regValName_iTimeoutInMs_channelIdle,  _ltot(  iTimeoutInMs_channelIdle,  tBuf,  10  )  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	pRegVal  =  _T(  CONST_regValName_usMax_nPlayers  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	pRegVal  =  _T(  CONST_regValName_usMax_nThreads_dec  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	pRegVal  =  _T(  CONST_regValName_uiMaxQNodes_vwRuleQ  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	//  2013/10/03
	pRegVal  =  CONST_regValName_keyCfg_usCnt;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  CONST_regValName_keyCfg_bUseKey;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  CONST_regValName_keyCfg_minS;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  CONST_regValName_keyCfg_minL;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  CONST_regValName_keyCfg_maxL;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
#if 0
	pRegVal  =  CONST_regValName_keyCfg_bStartSmooth;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	pRegVal  =  CONST_regValName_keyCfg_r_f;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	pRegVal  =  CONST_regValName_keyCfg_r_rgb;
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
#endif

	pRegVal  =  CONST_regValName_noPrompt_selAvCompressor;				//  2014/04/08
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );
	//
	pRegVal  =  CONST_regValName_noPrompt_selConfCtrl;					//  2017/07/19
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	pRegVal  =  CONST_regValName_ucbLetConfMgrSetMicOn;					//  2017/07/19
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );

	//
	pRegVal  =  _T(  CONST_regValName_conf_fourcc  );
	qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CQyString(  pRegVal  )  );


	//
	for  (  pItemJJ  =  CONST_capTypeTable; pItemJJ->type  !=  -1;  pItemJJ  ++  )  {
		 if  (  !(  name  =  qyGetDesByType(  CONST_capTypeTable,  pItemJJ->type  )  )  )  continue;
		 switch  (  pItemJJ->type  )  {
			 case  CONST_capType_av:   {
				   for  (  pItemQQ  =  CONST_subCapTypeTable;  pItemQQ->type  !=  -1;  pItemQQ  ++  )  {
					   if  (  !(  pT  =  qyGetDesByType(  CONST_subCapTypeTable,  pItemQQ->type  )  )  )  continue;
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\%s.%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  name,  pT  );
					   _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  tBuf  );
					   deleteCfgOfIsClient_level(  reg,  gAvParams.iResId_policyAvLevelTable_webcam  );
					   //  2014/05/02
					   deleteCfg_rtspUrlList(  );
					   //  2014/11/20
					   deleteCfgOfIsClient_capUsage(  pItemJJ->type,  pItemQQ->type  );
					   //
					   pRegVal  =  CONST_regValName_policyAvLevel_req;
					   qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CQyString(  pRegVal  )  );
					   //
					   if  (  ERROR_SUCCESS  !=  RegDeleteKey(  reg.hKeyRoot0,  reg.rootKey  )  )  iErr  =  -1;
					   else  iErr  =  0;
				   }					   
				   
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  name  );
				   _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  tBuf  );
				   deleteCfgOfIsClient_level(  reg,  gAvParams.iResId_policyAvLevelTable  );
				   //
				   deleteSubtitlesCfg(  pItemJJ->type,  0,  0  );
				   deleteSubtitlesCfg(  pItemJJ->type,  CONST_subCapType_webcam,  0  );
				   //
				   //pRegVal  =  CONST_regValName_policyAvLevel_conf;
				   //qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CQyString(  pRegVal  )  );
				   pRegVal  =  CONST_regValName_policyAvLevel_req;
				   qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CQyString(  pRegVal  )  );
				   //  2014/10/07
				   pRegVal  =  CONST_regValName_usPollingIntervalInS;
				   qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CQyString(  pRegVal  )  );
#if  10			//  
				   traceLog(  _T(  "-----------------------------------unfinished!"  ) );
				   pRegVal  =  CONST_regValName_layout;
				   qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CQyString(  pRegVal  )  );
#endif
#if 0
				   _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s.%d"  ),  reg.rootKey,  CONST_capUsage_conf  );
				   pRegVal  =  CONST_regValName_policyAvLevel_req;
				   qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CQyString(  pRegVal  )  );				   
#endif
				   //
				   if  (  ERROR_SUCCESS  !=  RegDeleteKey(  reg.hKeyRoot0,  reg.rootKey  )  )  iErr  =  -1;
				   else  iErr  =  0;		 	
				   }
				   break;
			 case  CONST_capType_screen:
#if  0
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  name  );
				   _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  tBuf  );
#endif
				   getRegRootKey_qmc( pItemJJ->type,  0,  0,  reg.rootKey,  mycountof(  reg.rootKey  )  );				   
				   deleteCfgOfIsClient_level(  reg,  gAvParams.iResId_policyAvLevelTable_screen  );
				   //
				   deleteSubtitlesCfg(  pItemJJ->type,  0,  0  );
				   //
				   if  (  ERROR_SUCCESS  !=  RegDeleteKey(  reg.hKeyRoot0,  reg.rootKey  )  )  iErr  =  -1;
				   else  iErr  =  0;
				   break;
			 case  CONST_capType_mediaFile:
#if  0
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  name  );
				   _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  tBuf  );
#endif
				   getRegRootKey_qmc( pItemJJ->type,  0,  0,  reg.rootKey,  mycountof(  reg.rootKey  )  );
				   deleteCfgOfIsClient_level(  reg,  gAvParams.iResId_policyAvLevelTable_mediaFile  );
				   //
				   pRegVal  =  CONST_regValName_policyAvLevel_req;
				   qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CQyString(  pRegVal  )  );
				   //
				   if  (  ERROR_SUCCESS  !=  RegDeleteKey(  reg.hKeyRoot0,  reg.rootKey  )  )  iErr  =  -1;
				   else  iErr  =  0;
				   break;
			 case  CONST_capType_mediaDevice:
#if  0
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  name  );
				   _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  tBuf  );
#endif
				   getRegRootKey_qmc( pItemJJ->type,  0,  0,  reg.rootKey,  mycountof(  reg.rootKey  )  );				   
				   deleteCfgOfIsClient_level(  reg,  gAvParams.iResId_policyAvLevelTable_mediaDevice  );
				   //
				   pRegVal  =  CONST_regValName_policyAvLevel_req;
				   qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CQyString(  pRegVal  )  );
				   //
				   if  (  ERROR_SUCCESS  !=  RegDeleteKey(  reg.hKeyRoot0,  reg.rootKey  )  )  iErr  =  -1;
				   else  iErr  =  0;
				   break;
			 case  CONST_capType_mosaic:
				   deleteSubtitlesCfg(  pItemJJ->type,  0,  0  );
				   break;
			default:
				break;
		 }
	}

	return;
}


#ifndef  __WINCE__


/////////////////////////////////////////////////////////////////////////////
// CDlgPolicyIsClient dialog


CDlgPolicyIsClient::CDlgPolicyIsClient(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPolicyIsClient::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPolicyIsClient)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


 BOOL  CDlgPolicyIsClient::bShowPolicy(  )
{
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci	=	getServiceGuiInfo(  pQyMc,  pQyMc->iServiceId  );
	if  (  !pSci  )  return  FALSE;
	if  (  !(  m_var.pProcInfo  =  (  MC_VAR_isCli  *  )pSci->pVar  )  )  return  FALSE;
	PolicyAvParams		&	gAvParams			=	*m_var.pProcInfo->p_gAvParams;	//  QY_GET_PolicyAvParams(  );


	//
	memcpy(  &m_var.policy,  &m_var.pProcInfo->cfg.policy,  sizeof(  m_var.policy  )  );

	//
	CComboBox		*	pCb			=	NULL;
	CListBox		*	pLb			=	NULL;
	int					nCurSel		=	0;
	//  int					i;
	int					idc			=	0;
	QY_DMITEM		*	pTable		=	NULL;
	QY_DMITEM		*	pItem		=	NULL;
	TCHAR			*	pRegVal		=	NULL;
	unsigned  char		ucCmd		=	0;
	//
	QY_REG				reg;
	char				buf[128];
	int					level;
	TCHAR				tBuf[256]	=  _T(  ""  );
	TCHAR				rootKeyStr[256]  =  _T(  ""  );
	unsigned int		uiCapType;

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	//  safeStrnCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );

	//  
	pTable		=	CONST_ruleIfMsgArriveTable;
	idc			=	IDC_COMBO_ruleIfMsgArrive;
	pRegVal		=	_T(  CONST_regValName_ruleIfMsgArrive  );
	pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
	ucCmd		=	DEFAULT_ruleIfMsgArrive;

	pCb->ResetContent(  );
	for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  pCb->AddString(  CQyString(  pItem->des  )  );
	ucCmd  =  m_var.policy.ucRuleIfMsgArrive;
	pCb->SelectString(  -1,  CQyString(  qyGetDesByType1(  pTable,  ucCmd  )  )  );  

	//
	//  2014/03/29
	pTable		=	CONST_hdAccl_table;
	idc			=	IDC_COMBO_hardwareAccl;
	pRegVal		=	_T(  CONST_regValName_ucHardwareAccl  );
	pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
	ucCmd		=	DEFAULT_hdAccl;

	pCb->ResetContent(  );
	for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  pCb->AddString(  CQyString(  pItem->des  )  );
	ucCmd  =  m_var.policy.ucHardwareAccl;
	pCb->SelectString(  -1,  CQyString(  qyGetDesByType1(  pTable,  ucCmd  )  )  );  

	//  2013/11/14
	idc			=  IDC_CHECK_ucbRunAsAdvertisingPlayer;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.policy.ucbRunAsAdvertisingPlayer  ?  1  :  0  );

	//  2012/04/02
	idc			=  IDC_CHECK_ucbUseGlobalVWall;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.policy.ucbUseGlobalVWall  ?  1  :  0  );
	//
	SetDlgItemText(  IDC_EDIT_dirToSaveFile,  m_var.policy.dirToSaveFile  );

	//  2013/04/27
	idc  =  IDC_CHECK_ucbSaveMsg;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.policy.ucbSaveMsg  ?  1  :  0  );
	//
	SetDlgItemText(  IDC_EDIT_dirToSaveMsg,  m_var.policy.dirToSaveMsg  );
	if  (  m_var.policy.ucbSaveMsg  )  {
		::EnableWindow(  ::GetDlgItem(  m_hWnd,  IDC_EDIT_dirToSaveMsg  ),  TRUE  );
		::EnableWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_browseMsgDir  ),  TRUE  );
		}
	else  {
		::EnableWindow(  ::GetDlgItem(  m_hWnd,  IDC_EDIT_dirToSaveMsg  ),  FALSE  );
		::EnableWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_browseMsgDir  ),  FALSE  );
	}

	//  2014/08/03
	SetDlgItemInt(  IDC_EDIT_timeOfVideoFile,  m_var.policy.uiTimeOfVideoFileInS  );
	SetDlgItemText(  IDC_EDIT_dirToSaveVideo,  m_var.policy.dirToSaveVideo  );
	


#if  0
	//
	idc			=	IDC_CHECK_ucbOnlyNetSm;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.policy.ucbOnlyNetSm  ?  1  :  0  );

	//
	idc			=	IDC_CHECK_ucbOnlyPhoneMsgr;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.policy.ucbOnlyPhoneMsgr  ?  1  :  0  );

	//
	idc			=	IDC_EDIT_baud;
	SetDlgItemInt(  idc,  m_var.policy.baud,  FALSE  );

	idc  =  IDC_CHECK_ucbPermitOtherSm;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.policy.ucbPermitOtherSm  ?  1  :  0  );
#endif

	//
	GetDlgItem(  IDC_STATIC_staticRuleIfMsgArrive  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_COMBO_ruleIfMsgArrive  )->ShowWindow(  SW_HIDE  );

	//
	idc  =  IDC_CHECK_showMsgBox;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.policy.dlgTalk.snmpbShowMsgBox  ==  CONST_snmpTrue  ?  1  :  0  );
	idc  =  IDC_CHECK_showNotification;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.policy.ucbShowNotification  ?  1  :  0  );
#ifndef  __APP_qyMc_touchscreen__
		 #if  0
			idc  =  IDC_CHECK_showMsgBox;
			GetDlgItem(  idc  )->EnableWindow(  FALSE  );
		 #endif
		#if  0
		 idc  =  IDC_CHECK_showNotification;
		 GetDlgItem(  idc  )->EnableWindow(  FALSE  );		 
		#endif
#endif

#if  0
	idc  =  IDC_CHECK_showVideoHint;	//  2011/08/02
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.policy.ucbShowVideoHint  ?  1  :  0  );
#endif

	//
	idc  =  IDC_CHECK_ucbPreferCuda;	//  2012/06/25
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.policy.ucbPreferCuda  ?  1  :  0  );

#if  defined(  __isCli__  )  ||  defined(  __APP_qyMc_touchscreen__  )
	idc  =  IDC_CHECK_ucbLooping_mediaFile;		//  2012/11/06
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.policy.ucbLooping_mediaFile  ?  1  :  0  );
#endif

	//
	SetDlgItemInt(  IDC_EDIT_usTimeoutInMsToSwitch,  m_var.policy.usTimeoutInMsToSwitch  );
	SetDlgItemInt(  IDC_EDIT_usTimeoutInMsToSwitch_rt,  m_var.policy.usTimeoutInMsToSwitch_rt  );
	//
	SetDlgItemInt(  IDC_EDIT_iTimeoutInMs_channelIdle,  pQyMc->cfg.iTimeoutInMs_channelIdle_others  );
	//
	SetDlgItemInt(  IDC_EDIT_usMax_nPlayers,  m_var.policy.usMax_nPlayers  );
	SetDlgItemInt(  IDC_EDIT_usMax_nThreads_dec,  m_var.policy.usMax_nThreads_dec  );
	SetDlgItemInt(  IDC_EDIT_uiMaxQNodes_vwRuleQ,  m_var.policy.uiMaxQNodes_vwRuleQ  );


	//  2011/10/15
#if  0
	idc			=	IDC_CHECK_shareWebcamInConference;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.policy.ucbShareWebcamInConference  ?  1  :  0  );
	idc  =  IDC_EDIT_conferenceId_shareWebcam;
	_snprintf(  buf,  mycountof(  buf  ),  "%I64u",  m_var.policy.conferenceId_shareWebcam.ui64Id  );
	SetDlgItemText(  idc,  CString(  buf  )  );
	idc			=	IDC_CHECK_noLocalVideoInThisConference;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.policy.ucbNoLocalVideoInThisConference  ?  1  :  0  );
	idc  =  IDC_CHECK_distinguishSharedWebcams;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.policy.ucbDistinguishSharedWebcams  ?  1  :  0  );
#endif

	//
	idc			=	IDC_CHECK_ucbManullyPermitToSpeakOnVideoConference;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.policy.ucbManullyPermitToSpeakOnVideoConference  ?  1  :  0  );

	//  2012/04/07
	idc			=  IDC_CHECK_ucbScrollForEnlagedImg;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.policy.ucbScrollForEnlagedImg  ?  1  :  0  );

	//  2016/02/15
	pTable		=	getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleCmdTable_autoAnswer_av  );
	idc			=	IDC_COMBO_autoAnswer_av;
	pRegVal		=	CONST_regValName_usAutoAnswer_av;
	pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
	ucCmd		=	CONST_ruleCmd_permit;

	pCb->ResetContent(  );
	for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  pCb->AddString(  CQyString(  pItem->des  )  );
	ucCmd  =  m_var.policy.avRules.uiCmd_autoAnswer_av;
	pCb->SelectString(  -1,  CQyString(  qyGetDesByType1(  pTable,  ucCmd  )  )  );  

	//  2017/07/11
	idc  =  IDC_CHECK_letConfMgrSetMicOn;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.policy.avRules.ucbLetConfMgrSetMicOn  ?  1  :  0  );

	//
	AV_COMPRESSOR_CFG	compressor;

	//
	uiCapType  =  CONST_capType_av;
	myGetAvCompressorCfg(  uiCapType,  0,  CONST_capUsage_3dConf,  0,  &compressor  );
	SetDlgItemText(  IDC_STATIC_avCompressorVal_req_3d,  getCompressorDesc(  uiCapType,  &compressor  )  );
	
	//
	uiCapType  =  CONST_capType_av;
	myGetAvCompressorCfg(  uiCapType,  0,  0,  0,  &compressor  );
	SetDlgItemText(  IDC_STATIC_avCompressorVal_req,  getCompressorDesc(  uiCapType,  &compressor  )  );

	/*
	uiCapType  =  CONST_capType_av;
	myGetAvCompressorCfg(  uiCapType,  0,  CONST_capUsage_conf,  0,  &compressor  );
	SetDlgItemText(  IDC_STATIC_avCompressorVal_reply,  getCompressorDesc(  CONST_capType_av,  &compressor  )  );
	*/
	//
	uiCapType  =  CONST_capType_av;
	myGetAvCompressorCfg(  uiCapType,  CONST_subCapType_webcam,  0,  0,  &compressor  );
	SetDlgItemText(  IDC_STATIC_webcamCompressorVal,  getCompressorDesc(  CONST_capType_av,  &compressor  )  );
	//
	uiCapType  =  CONST_capType_screen;
	myGetAvCompressorCfg(  uiCapType,  0,  FALSE,  0,  &compressor  );
	SetDlgItemText(  IDC_STATIC_screenCompressorVal,  getCompressorDesc(  CONST_capType_screen,  &compressor  )  );
	//
	uiCapType  =  CONST_capType_mediaFile;
	myGetAvCompressorCfg(  uiCapType,  0,  FALSE,  0,  &compressor  );
	SetDlgItemText(  IDC_STATIC_mediaFileCompressorVal,  getCompressorDesc(  CONST_capType_mediaFile,  &compressor  )  );
	//
	uiCapType  =  CONST_capType_mediaDevice;
	myGetAvCompressorCfg(  uiCapType,  0,  FALSE,  0,  &compressor  );
	SetDlgItemText(  IDC_STATIC_mediaDeviceCompressorVal,  getCompressorDesc(  CONST_capType_mediaDevice,  &compressor  )  );
	//
	//
	uiCapType  =  CONST_capType_mediaDevice;
	myGetAvCompressorCfg(  uiCapType,  CONST_subCapType_unresizable,  FALSE,  0,  &compressor  );
	SetDlgItemText(  IDC_STATIC_unresizableCompressorVal,  getCompressorDesc(  CONST_capType_mediaDevice,  &compressor  )  );
	

	

	//  2014/05/08
#if  0
	if  (  !bAppX64(  )  )  {
		::EnableWindow(  ::GetDlgItem(  m_hWnd,  IDC_EDIT_usMax_nThreads_dec  ),  FALSE  );
	}
#endif
	::EnableWindow(  ::GetDlgItem(  m_hWnd,  IDC_CHECK_ucbPreferCuda  ),  FALSE  );


	/////////////

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}



void CDlgPolicyIsClient::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPolicyIsClient)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPolicyIsClient, CDialog)
	//{{AFX_MSG_MAP(CDlgPolicyIsClient)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_browseDir, OnBnClickedButtonbrowsedir)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_restoreDefaultSettings, &CDlgPolicyIsClient::OnBnClickedButtonrestoredefaultsettings)
	ON_BN_CLICKED(IDC_BUTTON_avCompressor_req_3d, &CDlgPolicyIsClient::OnBnClickedButtonavcompressorreq3d)
	ON_BN_CLICKED(IDC_BUTTON_avCompressor_req, &CDlgPolicyIsClient::OnBnClickedButtonavcompressorreq)
	ON_BN_CLICKED(IDC_BUTTON_screenCompressor, &CDlgPolicyIsClient::OnBnClickedButtonscreencompressor)
	ON_BN_CLICKED(IDC_BUTTON_mediaFileCompressor, &CDlgPolicyIsClient::OnBnClickedButtonmediafilecompressor)
	ON_BN_CLICKED(IDC_BUTTON_mediaDeviceCompressor, &CDlgPolicyIsClient::OnBnClickedButtonmediadevicecompressor)
	ON_BN_CLICKED(IDC_BUTTON_webcamCompressor, &CDlgPolicyIsClient::OnBnClickedButtonwebcamcompressor)

	#ifdef  __isCli__
			ON_BN_CLICKED(IDC_BUTTON_ptzSettings, &CDlgPolicyIsClient::OnBnClickedButtonptzsettings)
	#endif

			ON_BN_CLICKED(IDC_BUTTON_videoConferenceCfg, &CDlgPolicyIsClient::OnBnClickedButtonvideoconferencecfg)
			//  ON_BN_CLICKED(IDC_BUTTON_videoTagCfg, &CDlgPolicyIsClient::OnBnClickedButtonvideotagcfg)
			ON_BN_CLICKED(IDC_CHECK_ucbSaveMsg, &CDlgPolicyIsClient::OnBnClickedCheckucbsavemsg)
			ON_BN_CLICKED(IDC_BUTTON_browseMsgDir, &CDlgPolicyIsClient::OnBnClickedButtonbrowsemsgdir)
			ON_BN_CLICKED(IDC_BUTTON_browseVideoDir, &CDlgPolicyIsClient::OnBnClickedButtonbrowsevideodir)
			ON_BN_CLICKED(IDC_BUTTON_unresizableCompressor, &CDlgPolicyIsClient::OnBnClickedButtonunresizablecompressor)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPolicyIsClient message handlers


 
 BOOL CDlgPolicyIsClient::OnInitDialog()
{
	CDialog::OnInitDialog();

	int			iErr	=	-1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	#ifdef  __APP_qyMc_touchscreen__
			//  2011/03/26
			::SetWindowPos(  m_hWnd,  HWND_TOPMOST,  0,  0,  0,  0,  SWP_NOMOVE  |  SWP_NOSIZE  );
	#endif

	if  (  setModalWnd(  pQyMc,  m_hWnd  )  )  goto  errLabel;

	//  GetDlgItem(  IDC_BUTTON_setAdvancedSettings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27

	bShowPolicy(  );

	#ifdef  __APP_qyMc_touchscreen__
			//  2011/03/26
#if  0
			GetDlgItem(  IDC_STATIC  )->ShowWindow(  SW_HIDE  );								//  2011/10/26
#endif
			HWND	hCtrl;
			hCtrl  =  ::GetDlgItem(  m_hWnd,  IDC_CHECK_ucbUseGlobalVWall  );
			::EnableWindow(  hCtrl,  FALSE  );
			hCtrl  =  ::GetDlgItem(  m_hWnd,  IDC_CHECK_ucbScrollForEnlagedImg  );
			::EnableWindow(  hCtrl,  FALSE  );

			GetDlgItem(  IDC_BUTTON_ptzSettings  )->ShowWindow(  SW_HIDE  );

			GetDlgItem(  IDC_BUTTON_webcamCompressor  )->ShowWindow(  SW_HIDE  );
			GetDlgItem(  IDC_STATIC_webcamCompressorVal  )->ShowWindow(  SW_HIDE  );
			GetDlgItem(  IDC_STATIC_mediaDeviceCompressorVal  )->ShowWindow(  SW_HIDE  );
			GetDlgItem(  IDC_BUTTON_mediaDeviceCompressor  )->ShowWindow(  SW_HIDE  );

	#endif


#if  0
	int	iAppAvLevel  =  qyGetAppAvLevel_qyMc(  pQyMc  );
	switch  (  iAppAvLevel  )  {
			case  CONST_qyAppAvLevel_mini:
				  GetDlgItem(  IDC_BUTTON_ptzSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_CHECK_ucbPreferCuda  )->ShowWindow(  SW_HIDE  );
				  //
				  break;
			case  CONST_qyAppAvLevel_sd:
			case  CONST_qyAppAvLevel_hd:
				  //
				  GetDlgItem(  IDC_CHECK_ucbPreferCuda  )->ShowWindow(  SW_HIDE  );
				  //
				  break;
			case  CONST_qyAppAvLevel_fullHd:
			default:
					break;
	}
#endif

#if 0
	//  2017/07/11
	SetDlgItemText(  IDC_CHECK_letConfMgrSetMicOn,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_remoteMicOnOff  )  );
#endif

	//  2014/08/07
	if  (  !bSupported_remoteStorage(  pQyMc  )  )  {
		::EnableWindow(  ::GetDlgItem(  m_hWnd,  IDC_EDIT_dirToSaveVideo  ),  FALSE  );
		::EnableWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_browseVideoDir  ),  FALSE  );
		
	}

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		EndDialog(  -1  );
	}

	return  TRUE;
 }



void CDlgPolicyIsClient::OnOK()
{
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	if  (  !m_var.pProcInfo  )  return;

	CComboBox		*	pCb			=	NULL;
	CListBox		*	pLb			=	NULL;
	int					nCurSel		=	0;
	int					idc			=	0;
	QY_DMITEM		*	pTable		=	NULL;
	QY_DMITEM		*	pItem		=	NULL;
	TCHAR			*	pRegVal		=	NULL;
	unsigned  char		ucCmd		=	0;
	CString				tmpCStr;
	//  
	TCHAR				tBuf[1024];
	char				buf[256];
	//  
	unsigned  char		ucbAsked	=	FALSE;
	//
	unsigned  char		ucbVal		=  FALSE;
	long				lVal		=	0;


	// TODO: 
	QY_REG				reg;

	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	//  safeStrnCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );

	//  ÏûÏ¢µ½´ïÊ±µÄ²ßÂÔ
	idc			=	IDC_COMBO_ruleIfMsgArrive;
	pRegVal		=	_T(  CONST_regValName_ruleIfMsgArrive  );
	pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
	pTable		=	CONST_ruleIfMsgArriveTable;
	ucCmd		=	DEFAULT_ruleIfMsgArrive;
	//		
	pCb->GetLBText(  pCb->GetCurSel(  ),  tmpCStr  );  
	ucCmd  =  qyGetTypeByDes(  pTable,  tmpCStr  );
	if  (  ucCmd  !=  m_var.policy.ucRuleIfMsgArrive  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  _ltot(  ucCmd,  tBuf,  10  )  );
	}
	m_var.policy.ucRuleIfMsgArrive  =  ucCmd;


	//  2014/03/29
	idc			=	IDC_COMBO_hardwareAccl;
	pRegVal		=	_T(  CONST_regValName_ucHardwareAccl  );
	pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
	pTable		=	CONST_hdAccl_table;
	ucCmd		=	DEFAULT_hdAccl;
	//		
	pCb->GetLBText(  pCb->GetCurSel(  ),  tmpCStr  );  
	ucCmd  =  qyGetTypeByDes(  pTable,  tmpCStr  );
	if  (  ucCmd  !=  m_var.policy.ucHardwareAccl  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  _ltot(  ucCmd,  tBuf,  10  )  );
	}
	m_var.policy.ucHardwareAccl  =  ucCmd;

	//  2013/11/14
	idc  =  IDC_CHECK_ucbRunAsAdvertisingPlayer;
	m_var.policy.ucbRunAsAdvertisingPlayer  =  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  ?  1  :  0;
	if  (  m_var.pProcInfo->cfg.policy.ucbRunAsAdvertisingPlayer  !=  m_var.policy.ucbRunAsAdvertisingPlayer  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_ucbRunAsAdvertisingPlayer  ),  m_var.policy.ucbRunAsAdvertisingPlayer  ?  _T(  "1"  )  :  _T(  ""  )  );
	}


	//  2012/04/02
	idc  =  IDC_CHECK_ucbUseGlobalVWall;
	m_var.policy.ucbUseGlobalVWall  =  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  ?  1  :  0;
	if  (  m_var.pProcInfo->cfg.policy.ucbUseGlobalVWall  !=  m_var.policy.ucbUseGlobalVWall  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_ucbUseGlobalVWall  ),  m_var.policy.ucbUseGlobalVWall  ?  _T(  "1"  )  :  _T(  ""  )  );
	}

	//
	GetDlgItemText(  IDC_EDIT_dirToSaveFile,  m_var.policy.dirToSaveFile,  mycountof(  m_var.policy.dirToSaveFile  )  );
	tTrim(  m_var.policy.dirToSaveFile  );
	if  (  m_var.policy.dirToSaveFile[0]  )  {
		if  (  !bDir(  m_var.policy.dirToSaveFile  )  )  {
			qyShowHint(  _T(  "The directory to save file does not exist"  )  );  return;
		}
	}	
	if  (  lstrcmpi(  m_var.policy.dirToSaveFile,  m_var.pProcInfo->cfg.policy.dirToSaveFile  )  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_dirToSaveFile  ),  m_var.policy.dirToSaveFile  );
	}
	
	//  2014/04/26
	GetDlgItemText(  IDC_EDIT_dirToSaveMsg,  m_var.policy.dirToSaveMsg,  mycountof(  m_var.policy.dirToSaveMsg  )  );
	tTrim(  m_var.policy.dirToSaveMsg  );
	if  (  m_var.policy.ucbSaveMsg  )  {	
		if  (  !bDir(  m_var.policy.dirToSaveMsg  )  )  {
			qyShowHint(  _T(  "The directory to save msg does not exist"  )  );  return;
		}	
	}
	if  (  lstrcmpi(  m_var.policy.dirToSaveMsg,  m_var.pProcInfo->cfg.policy.dirToSaveMsg  )  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_dirToSaveMsg  ),  m_var.policy.dirToSaveMsg  );
	}

	//  2014/08/03
#if  0
	idc			=  IDC_CHECK_ucbSaveVideo;
	m_var.policy.ucbSaveVideo  =  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  ?  1  :  0;
	if  (  m_var.pProcInfo->cfg.policy.ucbSaveVideo  !=  m_var.policy.ucbSaveVideo  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_ucbSaveVideo  ),  m_var.policy.ucbSaveVideo  ?  _T(  "1"  )  :  _T(  ""  )  );
	}
#endif
	m_var.policy.uiTimeOfVideoFileInS  =  GetDlgItemInt(  IDC_EDIT_timeOfVideoFile  );
	if  (  m_var.policy.uiTimeOfVideoFileInS  <  1  ||  m_var.policy.uiTimeOfVideoFileInS  >  24  *  3600  )  m_var.policy.uiTimeOfVideoFileInS  =  3600;
	if  (  m_var.policy.uiTimeOfVideoFileInS  !=  m_var.pProcInfo->cfg.policy.uiTimeOfVideoFileInS  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_timeOfVideoFileInS  ),  _ltot(  m_var.policy.uiTimeOfVideoFileInS,  tBuf,  10  )  );
	}
	//  2014/08/03
	GetDlgItemText(  IDC_EDIT_dirToSaveVideo,  m_var.policy.dirToSaveVideo,  mycountof(  m_var.policy.dirToSaveVideo  )  );
	tTrim(  m_var.policy.dirToSaveVideo  );
	if  (  m_var.policy.dirToSaveVideo[0]  )  {	
		if  (  !bDir(  m_var.policy.dirToSaveVideo  )  )  {
			qyShowHint(  _T(  "The directory to save video does not exist"  )  );  return;
		}	
	}
	if  (  lstrcmpi(  m_var.policy.dirToSaveVideo,  m_var.pProcInfo->cfg.policy.dirToSaveVideo  )  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_dirToSaveVideo  ),  m_var.policy.dirToSaveVideo  );
	}




	//  2011/03/28
	idc  =  IDC_CHECK_showMsgBox;
	m_var.policy.dlgTalk.snmpbShowMsgBox  =  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  ?  CONST_snmpTrue  :  CONST_snmpFalse;
	if  (  m_var.pProcInfo->cfg.policy.dlgTalk.snmpbShowMsgBox  !=  m_var.policy.dlgTalk.snmpbShowMsgBox  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		//  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbShowMsgBox,  m_var.policy.ucbShowMsgBox  ?  _T(  "1"  )  :  _T(  ""  )  );
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_snmpbShowMsgBox,  _ltot(  m_var.policy.dlgTalk.snmpbShowMsgBox,  tBuf,  10  )  );
	}
	//
	idc  =  IDC_CHECK_showNotification;
	m_var.policy.ucbShowNotification  =  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  );
	if  (  m_var.pProcInfo->cfg.policy.ucbShowNotification  !=  m_var.policy.ucbShowNotification  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbShowNotification,  m_var.policy.ucbShowNotification  ?  _T(  "1"  )  :  _T(  ""  )  );
	}
	//  2011/08/02
#if  0
	idc  =  IDC_CHECK_showVideoHint;
	m_var.policy.ucbShowVideoHint  =  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  );
	if  (  m_var.pProcInfo->cfg.policy.ucbShowVideoHint  !=  m_var.policy.ucbShowVideoHint  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbShowVideoHint,  m_var.policy.ucbShowVideoHint  ?  _T(  "1"  )  :  _T(  ""  )  );
	}
#endif

	//  2012/06/25
	idc  =  IDC_CHECK_ucbPreferCuda;
	m_var.policy.ucbPreferCuda  =  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED;
	if  (  m_var.pProcInfo->cfg.policy.ucbPreferCuda  !=  m_var.policy.ucbPreferCuda  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbPreferCuda,  m_var.policy.ucbPreferCuda  ?  _T(  "1"  )  :  _T(  ""  )  );
	}

#if  defined(  __isCli__  )  ||  defined(  __APP_qyMc_touchscreen__  )
	//  2012/11/06
	idc  =  IDC_CHECK_ucbLooping_mediaFile;
	m_var.policy.ucbLooping_mediaFile  =  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED;
	if  (  m_var.pProcInfo->cfg.policy.ucbLooping_mediaFile  !=  m_var.policy.ucbLooping_mediaFile  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbLooping_mediaFile,  m_var.policy.ucbLooping_mediaFile  ?  _T(  "1"  )  :  _T(  ""  )  );
	}
#endif
	//  2008/11/20
	if  (  GetDlgItemInt(  IDC_EDIT_usTimeoutInMsToSwitch,  NULL,  FALSE  )  !=  DEFAULT_usTimeoutInMsToSwitch_isClient  )  {
		m_var.policy.usTimeoutInMsToSwitch  =  GetDlgItemInt(  IDC_EDIT_usTimeoutInMsToSwitch,  NULL,  FALSE  );
		qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CONST_regValName_usTimeoutInMsToSwitch, _ltot(  m_var.policy.usTimeoutInMsToSwitch,  tBuf,  10  )  );
	}
	if  (  GetDlgItemInt(  IDC_EDIT_usTimeoutInMsToSwitch_rt,  NULL,  FALSE  )  !=  DEFAULT_usTimeoutInMsToSwitch_rt_isClient  )  {
		m_var.policy.usTimeoutInMsToSwitch_rt  =  GetDlgItemInt(  IDC_EDIT_usTimeoutInMsToSwitch_rt,  NULL,  FALSE  );
		qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CONST_regValName_usTimeoutInMsToSwitch_rt, _ltot(  m_var.policy.usTimeoutInMsToSwitch_rt,  tBuf,  10  )  );
	}
	//  2008/12/06



	//  2009/02/25
	idc			=	IDC_CHECK_ucbManullyPermitToSpeakOnVideoConference;
	if  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  {
		m_var.policy.ucbManullyPermitToSpeakOnVideoConference  =  TRUE;
		if  (  m_var.pProcInfo->cfg.policy.ucbManullyPermitToSpeakOnVideoConference  !=  m_var.policy.ucbManullyPermitToSpeakOnVideoConference  )  {
			if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
			ucbAsked  =  TRUE;
			qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CONST_regValName_ucbManullyPermitToSpeakOnVideoConference,  m_var.policy.ucbManullyPermitToSpeakOnVideoConference  ?  _T(  "1"  )  :  _T(  ""  )  );
		}
	}
	else  {
		m_var.policy.ucbManullyPermitToSpeakOnVideoConference  =  FALSE;
		if  (  m_var.pProcInfo->cfg.policy.ucbManullyPermitToSpeakOnVideoConference  !=  m_var.policy.ucbManullyPermitToSpeakOnVideoConference  )  {
			if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
			ucbAsked  =  TRUE;
			qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CONST_regValName_ucbManullyPermitToSpeakOnVideoConference  );
		}
	}

	idc			=  IDC_CHECK_ucbScrollForEnlagedImg;
	if  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  {
		m_var.policy.ucbScrollForEnlagedImg  =  TRUE;
		if  (  m_var.pProcInfo->cfg.policy.ucbScrollForEnlagedImg  !=  m_var.policy.ucbScrollForEnlagedImg  )  {
			if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
			ucbAsked  =  TRUE;
			qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CONST_regValName_ucbScrollForEnlagedImg,  m_var.policy.ucbScrollForEnlagedImg  ?  _T(  "1"  )  :  _T(  ""  )  );
		}
	}
	else  {
		m_var.policy.ucbScrollForEnlagedImg  =  FALSE;
		if  (  m_var.pProcInfo->cfg.policy.ucbScrollForEnlagedImg  !=  m_var.policy.ucbScrollForEnlagedImg  )  {
			if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
			ucbAsked  =  TRUE;
			qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CONST_regValName_ucbScrollForEnlagedImg  );
		}
	}

	
	//  2014/03/29
	idc			=	IDC_COMBO_autoAnswer_av;
	pRegVal		=	CONST_regValName_usAutoAnswer_av;
	pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
	pTable		=	getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleCmdTable_autoAnswer_av  );
	ucCmd		=	CONST_ruleCmd_null;
	//		
	pCb->GetLBText(  pCb->GetCurSel(  ),  tmpCStr  );  
	ucCmd  =  qyGetTypeByDes(  pTable,  tmpCStr  );
	if  (  ucCmd  !=  m_var.policy.avRules.uiCmd_autoAnswer_av  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  _ltot(  ucCmd,  tBuf,  10  )  );
	}
	m_var.policy.avRules.uiCmd_autoAnswer_av  =  ucCmd;

	//  2017/07/11
	idc			=  IDC_CHECK_letConfMgrSetMicOn;
	if  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  {
		m_var.policy.avRules.ucbLetConfMgrSetMicOn  =  TRUE;
		}
	else  {
		  m_var.policy.avRules.ucbLetConfMgrSetMicOn  =  FALSE;
	}
	if  (  m_var.pProcInfo->cfg.policy.avRules.ucbLetConfMgrSetMicOn  !=  m_var.policy.avRules.ucbLetConfMgrSetMicOn  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		if  (  m_var.policy.avRules.ucbLetConfMgrSetMicOn  !=  m_var.pProcInfo->cfg.envVar.default_ucbLetConfMgrSetMicOn  )  {
			qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CONST_regValName_ucbLetConfMgrSetMicOn,  m_var.policy.avRules.ucbLetConfMgrSetMicOn  ?  _T(  "1"  )  :  _T(  ""  )  );
			}
		else  {
			  qyDelRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CONST_regValName_ucbLetConfMgrSetMicOn  );
		}
	}


	//
	int  iTimeoutInMs_channelIdle;
	idc  =  IDC_EDIT_iTimeoutInMs_channelIdle;
	iTimeoutInMs_channelIdle  =  GetDlgItemInt(  idc  );
	if  (  iTimeoutInMs_channelIdle  <=  MIN_iTimeoutInMs_channelIdle  ||  iTimeoutInMs_channelIdle  >  MAX_iTimeoutInMs_channelIdle  )  {
		iTimeoutInMs_channelIdle  =  DEFAULT_iTimeoutInMs_channelIdle_others;
	}
	if  (  iTimeoutInMs_channelIdle  !=  pQyMc->cfg.iTimeoutInMs_channelIdle_others  )  {
		qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  CONST_regValName_iTimeoutInMs_channelIdle_others,  _ltot(  iTimeoutInMs_channelIdle,  tBuf,  10  )  );
	}

	//  2012/03/30
	int  iTmp;
	//
	idc  =  IDC_EDIT_usMax_nPlayers;
	iTmp  =  GetDlgItemInt(  idc  );  
	if  (  iTmp  !=  m_var.policy.usMax_nPlayers  )  {
		if  (  iTmp  >=  5  &&  iTmp  <  200  )  qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  _T(  CONST_regValName_usMax_nPlayers  ),  _ltot(  iTmp,  tBuf,  10  )  );
	}

	idc  =  IDC_EDIT_usMax_nThreads_dec;
	iTmp  =  GetDlgItemInt(  idc  );  
	if  (  iTmp  !=  m_var.policy.usMax_nThreads_dec  )  {
		if  (  iTmp  >=  5  &&  iTmp  <  200  )  qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  _T(  CONST_regValName_usMax_nThreads_dec  ),  _ltot(  iTmp,  tBuf,  10  )  );
	}

	idc  =  IDC_EDIT_uiMaxQNodes_vwRuleQ;
	iTmp  =  GetDlgItemInt(  idc  );  
	if  (  iTmp  !=  m_var.policy.uiMaxQNodes_vwRuleQ  )  {
		if  (  iTmp  >=  5  &&  iTmp  <  200  )  qySetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  _T(  CONST_regValName_uiMaxQNodes_vwRuleQ  ),  _ltot(  iTmp,  tBuf,  10  )  );
	}



	//  ÖØÐÂ¶ÁÈëÈ«¾Ö²ßÂÔÇø
	if  (  getPolicyIsClient(  m_var.pProcInfo,  &m_var.policy  )  )  memset(  &m_var.policy,  0,  sizeof(  m_var.policy  )  );
	//
	if  (  memcmp(  &m_var.policy,  &m_var.pProcInfo->cfg.policy,  sizeof(  m_var.policy  )  )  )  {
		memcpy(  &m_var.pProcInfo->cfg.policy,  &m_var.policy,  sizeof(  m_var.pProcInfo->cfg.policy  )  );
	}


	CDialog::OnOK();
}




void CDlgPolicyIsClient::OnBnClickedButtonbrowsedir()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	CString		path;
	CQyString	dirStr;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	int			idc		=  IDC_EDIT_dirToSaveFile;

	GetDlgItemText(  idc,  path  );
	qyBrowseForDir(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectFolder  ),  path,  dirStr  );
	path  =  CQyString(  dirStr.GetBuffer(  0  )  );
	if  (  path.GetLength(  )  )  {
		SetDlgItemText(  idc,  path  );
	}

}


void CDlgPolicyIsClient::OnBnClickedCheckucbsavemsg()
{
	// TODO: Add your control notification handler code here
	int  idc;

	QY_REG	reg;
	QY_MC   *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	
	//
	idc			=  IDC_CHECK_ucbSaveMsg;
	if  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  {
		if  (  qyMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_saveMsgAsText  ),  _T(  "www.qycx.com"  ),  MB_YESNO,  30  *  1000,  NULL  )  !=  IDYES  )  {
			(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  0  );
			return;
		}
	
		setSaveMsgFlg(  TRUE  );
		//
		}
	else  {
		  setSaveMsgFlg(  FALSE  );
	}

		
	//
	m_var.policy.ucbSaveMsg  =  pProcInfo->cfg.policy.ucbSaveMsg;		
	safeTcsnCpy(  pProcInfo->cfg.policy.dirToSaveMsg,  m_var.policy.dirToSaveMsg,  mycountof(  m_var.policy.dirToSaveMsg  )  );
	SetDlgItemText(  IDC_EDIT_dirToSaveMsg,  m_var.policy.dirToSaveMsg  );

	//
	GetDlgItem(  IDC_EDIT_dirToSaveMsg  )->EnableWindow(  m_var.policy.ucbSaveMsg  );
	GetDlgItem(  IDC_BUTTON_browseMsgDir  )->EnableWindow(  m_var.policy.ucbSaveMsg  );


errLabel:
	return;
}


void CDlgPolicyIsClient::OnBnClickedButtonbrowsemsgdir()
{
	// TODO: Add your control notification handler code here
	CString		path;
	CQyString	dirStr;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	int			idc		=  IDC_EDIT_dirToSaveMsg;

	GetDlgItemText(  idc,  path  );
	qyBrowseForDir(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectFolder  ),  path,  dirStr  );
	path  =  CQyString(  dirStr.GetBuffer(  0  )  );
	if  (  path.GetLength(  )  )  {
		SetDlgItemText(  idc,  path  );
	}
}


void CDlgPolicyIsClient::OnBnClickedButtonbrowsevideodir()
{
	// TODO: Add your control notification handler code here
	CString		path;
	CQyString	dirStr;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	int			idc		=  IDC_EDIT_dirToSaveVideo;

	GetDlgItemText(  idc,  path  );
	qyBrowseForDir(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectFolder  ),  path,  dirStr  );
	path  =  CQyString(  dirStr.GetBuffer(  0  )  );
	if  (  path.GetLength(  )  )  {
		SetDlgItemText(  idc,  path  );
	}
}


void CDlgPolicyIsClient::OnBnClickedOk()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	OnOK();
}


/*
*/









void CDlgPolicyIsClient::OnBnClickedButtonrestoredefaultsettings()
{
	int					iErr		=	-1;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	TCHAR			*	pRegVal		=	NULL;
	//	int				idc;
	unsigned  char		ucCmd		=	0;
	//  TCHAR				tBuf[1024];
	//
	TCHAR			*	name;
	unsigned  int		uiCapType;
	//
	QY_REG				reg;
	CQyString				rootKeyStr;

	if  (  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_restoreAccess  ),  _T(  ""  ),  MB_YESNO  |  MB_DEFBUTTON2   )  !=  IDYES  )  return;

	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	//  safeStrnCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );

	//
	deleteCfgOfIsClient(  );

	//
	if  (  getPolicyIsClient(  m_var.pProcInfo,  &m_var.policy  )  )  memset(  &m_var.policy,  0,  sizeof(  m_var.policy  )  );

#if  0
	POLICY_av	policyAv;
	getPolicyAv(  0,  0,  &policyAv  );
	refreshWebCamSettings(  &policyAv.avCompressor.video,  &m_var.pProcInfo->av.localAv.videoCaptureProcInfo  );
#endif
	AV_COMPRESSOR_CFG	tmpAvCompressor;
	myGetAvCompressorCfg(  CONST_capType_av,  0,  0,  0,  &tmpAvCompressor  );
	refreshWebCamSettings(  &tmpAvCompressor.video,  &m_var.pProcInfo->av.localAv.videoCaptureProcInfo  );
	//
	if  (  memcmp(  &m_var.policy,  &m_var.pProcInfo->cfg.policy,  sizeof(  m_var.policy  )  )  )  {
		memcpy(  &m_var.pProcInfo->cfg.policy,  &m_var.policy,  sizeof(  m_var.pProcInfo->cfg.policy  )  );
	}
	this->bShowPolicy(  );

	return;
}


#else


CDlgPolicyIsClient::CDlgPolicyIsClient(  HWND  hParent /*=NULL*/)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


INT_PTR CALLBACK dlgProc_policyIsClient(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	return  FALSE;
}

#endif


//  2014/12/15
void CDlgPolicyIsClient::OnBnClickedButtonavcompressorreq3d()
{
	// TODO: Add your control notification handler code here
	if  (  showDlgPolicyAv(  m_hWnd,  CONST_capType_av,  0,  CONST_capUsage_3dConf  )  ==  IDOK  )
	{
		bShowPolicy(  );
	}

}


void CDlgPolicyIsClient::OnBnClickedButtonavcompressorreq()
{
	// TODO: Add your control notification handler code here
#if  0
	CDlgPolicyAv		dlg(  this  );
	dlg.bSetDlgInfo(  CONST_capType_av,  0,  FALSE  );
	if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
	if  (  showDlgPolicyAv(  m_hWnd,  CONST_capType_av,  0,  0  )  ==  IDOK  )
	{
		bShowPolicy(  );
	}
}


void CDlgPolicyIsClient::OnBnClickedButtonscreencompressor()
{
	// TODO: Add your control notification handler code here
#if  0
	CDlgPolicyAv		dlg(  this  );
	dlg.bSetDlgInfo(  CONST_capType_screen,  0,  FALSE  );
	if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
	if  (  showDlgPolicyAv(  m_hWnd,  CONST_capType_screen,  0,  0  )  ==  IDOK  )
	{
		bShowPolicy(  );
	}
}

void CDlgPolicyIsClient::OnBnClickedButtonmediafilecompressor()
{
	// TODO: Add your control notification handler code here
#if  0
	CDlgPolicyAv		dlg(  this  );
	dlg.bSetDlgInfo(  CONST_capType_mediaFile,  0,  FALSE  );
	if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
	if  (  showDlgPolicyAv(  m_hWnd,  CONST_capType_mediaFile,  0,  0  )  ==  IDOK  )
	{
		bShowPolicy(  );
	}
}

void CDlgPolicyIsClient::OnBnClickedButtonmediadevicecompressor()
{
	// TODO: Add your control notification handler code here
#if  0
	CDlgPolicyAv		dlg(  this  );
	dlg.bSetDlgInfo(  CONST_capType_mediaDevice,  0,  FALSE  );
	if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
	if  (  showDlgPolicyAv(  m_hWnd,  CONST_capType_mediaDevice,  0,  0  )  ==  IDOK  )
	{
		bShowPolicy(  );
	}
}

void CDlgPolicyIsClient::OnBnClickedButtonunresizablecompressor()
{
	// TODO: Add your control notification handler code here
	if  (  showDlgPolicyAv(  m_hWnd,  CONST_capType_mediaDevice,  CONST_subCapType_unresizable,  0  )  ==  IDOK  )
	{
		bShowPolicy(  );
	}
}

void CDlgPolicyIsClient::OnBnClickedButtonwebcamcompressor()
{
	// TODO: Add your control notification handler code here
#if  0
	CDlgPolicyAv		dlg(  this  );
	dlg.bSetDlgInfo(  CONST_capType_av,  CONST_subCapType_webcam,  FALSE  );
	if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
	if  (  showDlgPolicyAv(  m_hWnd,  CONST_capType_av,  CONST_subCapType_webcam,  0  )  ==  IDOK  )
	{
		bShowPolicy(  );
	}
}

#ifdef  __isCli__
void CDlgPolicyIsClient::OnBnClickedButtonptzsettings()
{
	// TODO: Add your control notification handler code here
#if  0
	CPtzSettings		dlg;
	dlg.DoModal(  );
#endif
	showDlgPtzSettings(  m_hWnd  );

}
#endif


void CDlgPolicyIsClient::OnBnClickedButtonvideoconferencecfg()
{
	// TODO: Add your control notification handler code here
#if  0
	CDlgCfgVideoConference	dlg;

	dlg.DoModal(  );
#endif

	showDlgCfgVideoConference(  m_hWnd  );

}


#if  0
void CDlgPolicyIsClient::OnBnClickedButtonvideotagcfg()
{
	// TODO: Add your control notification handler code here
	CDlgVideoTagCfg	dlg(  this  );


	dlg.DoModal(  );

}
#endif
