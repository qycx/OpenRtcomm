// DlgPolicyAv.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qyMc.h"
#include	"myresource.h"
#include	"DlgPolicyAv.h"
#include	"qyCusResTemp.h"
//
//  #include	"DlgVideoCompressors.h"
//#include	"qmshell_open.h"
#include	"policyAvParams.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"
#include	"policyIsClientFunc.h"

//extern    int  getDefaultPolicyAvLevel(  unsigned  int  uiCapType,  unsigned int uiSubCapType,  BOOL  bReply  );


__declspec(  dllexport  )  int  showDlgPolicyAv(  HWND  hParent,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int		iRet	=	-1;
	
	CDlgPolicyAv	dlg(  CWnd::FromHandle(  hParent  )  );
	dlg.bSetDlgInfo(  uiCapType,  uiSubCapType,  iCapUsage  );
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	iRet  =  IDOK;
errLabel:
	return  iRet;
}

// CDlgPolicyAv dialog

IMPLEMENT_DYNAMIC(CDlgPolicyAv, CDialog)

CDlgPolicyAv::CDlgPolicyAv(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPolicyAv::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

}

CDlgPolicyAv::~CDlgPolicyAv()
{
}


#if  0
BOOL  CDlgPolicyAv::bSetDlgInfo(  int  level  )
{
	m_var.level  =  level;
	return  TRUE;
}
#endif

BOOL  CDlgPolicyAv::bSetDlgInfo(  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage  )
{
	m_var.uiCapType  =  uiCapType;
	m_var.uiSubCapType  =  uiSubCapType;
	m_var.iCapUsage  =  iCapUsage;
	//  m_var.bReply  =  bReply;

	return  TRUE;
}


BOOL  CDlgPolicyAv::bShowPolicy(  )
{
	QY_MC			*	pQyMc				=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo			=	QY_GET_procInfo_isCli(  );
	PolicyAvParams	&	gAvParams			=	*pProcInfo->p_gAvParams;	//  QY_GET_PolicyAvParams(  );

	/////////////
	QY_REG				reg;
	TCHAR			*	pRegVal				=	NULL;
	TCHAR				tBuf[128]			=  _T(  ""  );
	TCHAR				tRootKey[256]		=	_T(  ""  );
	TCHAR			*   pT					=   NULL;
	CComboBox		*	pCb			=	NULL;
	//  long				lVal;
	int					level;
	int					idc			=	0;
	QY_DMITEM		*	pTable		=	NULL;
	QY_DMITEM		*	pItem		=	NULL;
	//  unsigned  char		ucCmd		=	0;
	//


#if  0
	if  (  bReply  )  level  =  pProcInfo->cfg.policy.iPolicyAvLevel_reply;
	else  if  (  !level  )  level  =  pProcInfo->cfg.policy.iPolicyAvLevel_req;
	if  (  !qyGetDesByType(  getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable  ),  level  )  )  level  =  CONST_policyAvLevel_240p;
#endif



	//
	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	//  safeStrnCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
	//  AV_COMPRESSOR_CFG	avCompressor;

	switch  (  m_var.uiCapType  )  {
			case  CONST_capType_screen:
			case  CONST_capType_mediaDevice:
			case  CONST_capType_mediaFile:
			case  CONST_capType_av:
				  //  2015/03/11
				  if  (  m_var.uiCapType  ==  CONST_capType_screen
					  ||  (  m_var.uiCapType  ==  CONST_capType_mediaDevice  &&  m_var.uiSubCapType  ==  CONST_subCapType_unresizable  )  )
				  {
				  if (  m_var.uiCapType  ==  CONST_capType_screen  )  pTable  =  getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable_screen  );
				  else  if  (  m_var.uiCapType  ==  CONST_capType_mediaDevice  &&  m_var.uiSubCapType  ==  CONST_subCapType_unresizable  )  pTable =  getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable_unresizable  );
				  idc  =  IDC_COMBO_req;
				  pRegVal  =  CONST_regValName_policyAvLevel_req;
				  pCb  =  (  CComboBox  *  )GetDlgItem(  idc  );
				  pCb->ResetContent(  );
				  for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  pCb->AddString(  CQyString(  pItem->des  )  );

				  level  =  m_var.iPolicyAvLevel_req;
				  if  (  !level  )  level  =  getDefaultPolicyAvLevel(  pQyMc,  m_var.uiCapType,  m_var.uiSubCapType,  0  );
				  //
				  pCb->SelectString(  -1,  CQyString(  qyGetDesByType1(  pTable, level  )  )  );
				  //
				  level  =  CONST_policyAvLevel_dev_2fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  0,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev2fpsSettings,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_5fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  0,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev5fpsSettings,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_5fps1;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  0,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev5fpsSettings1,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_5fps2;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  0,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev5fpsSettings2,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  break;
				  }
				  //
				  {
					int  iResId  =  gAvParams.iResId_policyAvLevelTable;
					switch(  m_var.uiCapType  )  {
						case  CONST_capType_mediaFile:
							iResId  =  gAvParams.iResId_policyAvLevelTable_mediaFile;
							break;
						case  CONST_capType_mediaDevice:
							if  (  m_var.uiSubCapType  ==  CONST_subCapType_unresizable  )  {
								iResId  =  gAvParams.iResId_policyAvLevelTable_unresizable;
								break;
							}
							iResId  =  gAvParams.iResId_policyAvLevelTable_mediaDevice;
							break;
						case  CONST_capType_av:
						default:
							if  (  m_var.uiSubCapType  ==  CONST_subCapType_webcam  )  iResId  =  gAvParams.iResId_policyAvLevelTable_webcam;
							break;
					}
						//  pTable  =  getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable  );
						pTable  =  getResTable(  0,  &pQyMc->cusRes,  iResId  );
						idc  =  IDC_COMBO_req;
						pRegVal  =  CONST_regValName_policyAvLevel_req;
						pCb  =  (  CComboBox  *  )GetDlgItem(  idc  );
						level = CONST_policyAvLevel_480p;// DEFAULT_policyAvLevel_req;
						pCb->ResetContent(  );
						for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  pCb->AddString(  CQyString(  pItem->des  )  );
#if  0
						//  if  (  pProcInfo->cfg.policy.iPolicyAvLevel_req  &&  qyGet)
						_sntprintf(  tRootKey,  mycountof(  tRootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  qyGetDesByType(  CONST_capTypeTable,  m_var.uiCapType  )  );
						if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  tRootKey,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )
							&&  _ttol(  tBuf  )  
							&&  qyGetDesByType(  pTable,  _ttol(  tBuf  )  )	 )
						{
							level  =  (  unsigned  char  )_ttol(  tBuf  );
						}
#endif
						level  =  m_var.iPolicyAvLevel_req;
						if  (  !level  )  level  =  getDefaultPolicyAvLevel(  pQyMc,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage  );
						//
						pCb->SelectString(  -1,  CQyString(  qyGetDesByType1(  pTable, level  )  )  );

#if  0
						//
						pTable  =  getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable  );
						idc  =  IDC_COMBO_reply;
						//pRegVal  =  CONST_regValName_policyAvLevel_conf;
						pCb  =  (  CComboBox  *  )GetDlgItem(  idc  );
						level  =  getDefaultPolicyAvLevel(  CONST_capType_av,  0,  CONST_capUsage_conf  );
						pCb->ResetContent(  );
						for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  pCb->AddString(  CQyString(  pItem->des  )  );
#if  0
						_sntprintf(  tRootKey,  mycountof(  tRootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  qyGetDesByType(  CONST_capTypeTable,  CONST_capType_av  )  );
						if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  tRootKey,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )
							&&  _ttol(  tBuf  )  
							&&  qyGetDesByType(  pTable,  _ttol(  tBuf  )  )	 )
						{
							level  =  (  unsigned  char  )_ttol(  tBuf  );
						}
#endif
						level  =  m_var.iPolicyAvLevel_reply;							
						if  (  !level  )  level  =  getDefaultPolicyAvLevel(  m_var.uiCapType,  m_var.uiSubCapType,  CONST_capUsage_conf  );
						//
						pCb->SelectString(  -1,  CQyString(  qyGetDesByType1(  pTable, level  )  )  );
#endif
						//
						level  =  CONST_policyAvLevel_240p;
						//idc  =  IDC_STATIC_ldSettings;
						idc  =  IDC_STATIC_240pSettings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
						//  2012/03/16
#if  0
						level  =  CONST_policyAvLevel_ld1;
						idc  =  IDC_STATIC_ld1Settings;						
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
#endif
					    //
#if  0
						level  =  CONST_policyAvLevel_sd;
						idc  =  IDC_STATIC_sdSettings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
#endif
						level  =  CONST_policyAvLevel_480p;
						//idc  =  IDC_STATIC_sd1Settings;
						idc  =  IDC_STATIC_480pSettings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
#if  0
						level  =  CONST_policyAvLevel_sd2;
						idc  =  IDC_STATIC_sd2Settings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
#endif
						level  =  CONST_policyAvLevel_576p;
						//idc  =  IDC_STATIC_sd3Settings;
						idc  =  IDC_STATIC_576pSettings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
						//
#if  0
					    level  =  CONST_policyAvLevel_hd;
						idc  =  IDC_STATIC_hdSettings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
						level  =  CONST_policyAvLevel_hd1;
						idc  =  IDC_STATIC_hd1Settings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
#endif
						level  =  CONST_policyAvLevel_720p;
						//idc  =  IDC_STATIC_hd2Settings;
						idc  =  IDC_STATIC_720pSettings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
#if  0
					    level  =  CONST_policyAvLevel_hd3;
						idc  =  IDC_STATIC_hd3Settings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
#endif
#if  0
					    //
						level  =  CONST_policyAvLevel_fullHd;
						idc  =  IDC_STATIC_fullHdSettings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
						level  =  CONST_policyAvLevel_fullHd1;
						idc  =  IDC_STATIC_fullHd1Settings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
#endif
						level  =  CONST_policyAvLevel_1080p;
						//idc  =  IDC_STATIC_fullHd2Settings;
						idc  =  IDC_STATIC_1080pSettings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
#if  0
						level  =  CONST_policyAvLevel_fullHd3;
						idc  =  IDC_STATIC_fullHd3Settings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
#endif
				   }
				  break;
			default:
					break;
	}

	return  TRUE;
}


void CDlgPolicyAv::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPolicyAv, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgPolicyAv::OnBnClickedOk)
#if  0
	ON_BN_CLICKED(IDC_BUTTON_avCompressor, &CDlgPolicyAv::OnBnClickedButtonavcompressor)
	ON_BN_CLICKED(IDC_BUTTON_screenCompressor, &CDlgPolicyAv::OnBnClickedButtonscreencompressor)
	ON_BN_CLICKED(IDC_BUTTON_mediaFileCompressor, &CDlgPolicyAv::OnBnClickedButtonmediafilecompressor)
	ON_BN_CLICKED(IDC_BUTTON_mediaDeviceCompressor, &CDlgPolicyAv::OnBnClickedButtonmediadevicecompressor)
	ON_BN_CLICKED(IDC_BUTTON_webcamCompressor, &CDlgPolicyAv::OnBnClickedButtonwebcamcompressor)
#endif
	//ON_BN_CLICKED(IDC_BUTTON_setLdSettings, &CDlgPolicyAv::OnBnClickedButtonsetldsettings)
	ON_BN_CLICKED(IDC_BUTTON_set240pSettings, &CDlgPolicyAv::OnBnClickedButtonset240pSettings)
	//ON_BN_CLICKED(IDC_BUTTON_setLd1Settings, &CDlgPolicyAv::OnBnClickedButtonsetld1settings)
	//ON_BN_CLICKED(IDC_BUTTON_setSdSettings, &CDlgPolicyAv::OnBnClickedButtonsetsdsettings)
	//ON_BN_CLICKED(IDC_BUTTON_setSd1Settings, &CDlgPolicyAv::OnBnClickedButtonsetsd1settings)
	ON_BN_CLICKED(IDC_BUTTON_set480pSettings, &CDlgPolicyAv::OnBnClickedButtonset480pSettings)
	//ON_BN_CLICKED(IDC_BUTTON_setSd2Settings, &CDlgPolicyAv::OnBnClickedButtonsetsd2settings)
	//ON_BN_CLICKED(IDC_BUTTON_setSd3Settings, &CDlgPolicyAv::OnBnClickedButtonsetsd3settings)
	ON_BN_CLICKED(IDC_BUTTON_set576pSettings, &CDlgPolicyAv::OnBnClickedButtonset576pSettings)
#if  0
	ON_BN_CLICKED(IDC_BUTTON_setHdSettings, &CDlgPolicyAv::OnBnClickedButtonsethdsettings)
	ON_BN_CLICKED(IDC_BUTTON_setHd1Settings, &CDlgPolicyAv::OnBnClickedButtonsethd1settings)
#endif
	//ON_BN_CLICKED(IDC_BUTTON_setHd2Settings, &CDlgPolicyAv::OnBnClickedButtonsethd2settings)
	ON_BN_CLICKED(IDC_BUTTON_set720pSettings, &CDlgPolicyAv::OnBnClickedButtonset720pSettings)
#if  0
	ON_BN_CLICKED(IDC_BUTTON_setHd3Settings, &CDlgPolicyAv::OnBnClickedButtonsethd3settings)
#endif
	//ON_BN_CLICKED(IDC_BUTTON_setFullHdSettings, &CDlgPolicyAv::OnBnClickedButtonsetfullhdsettings)
	//ON_BN_CLICKED(IDC_BUTTON_setFullHd1Settings, &CDlgPolicyAv::OnBnClickedButtonsetfullhd1settings)
	//ON_BN_CLICKED(IDC_BUTTON_setFullHd2Settings, &CDlgPolicyAv::OnBnClickedButtonsetfullhd2settings)
	ON_BN_CLICKED(IDC_BUTTON_set1080pSettings, &CDlgPolicyAv::OnBnClickedButtonset1080pSettings)
	//ON_BN_CLICKED(IDC_BUTTON_setFullHd3Settings, &CDlgPolicyAv::OnBnClickedButtonsetfullhd3settings)
	ON_BN_CLICKED(IDC_BUTTON_setDev2fpsSettings, &CDlgPolicyAv::OnBnClickedButtonsetdev2fpssettings)
	ON_BN_CLICKED(IDC_BUTTON_setDev5fpsSettings, &CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings)
	ON_BN_CLICKED(IDC_BUTTON_setDev5fpsSettings1, &CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings1)
#if  0
	ON_BN_CLICKED(IDC_BUTTON_setDev5fpsSettings2, &CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings2)
	ON_BN_CLICKED(IDC_BUTTON_setDev5fpsSettings3, &CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings3)
	ON_BN_CLICKED(IDC_BUTTON_setDev5fpsSettings4, &CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings4)
	ON_BN_CLICKED(IDC_BUTTON_setDev5fpsSettings5, &CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings5)
#endif

END_MESSAGE_MAP()


// CDlgPolicyAv message handlers

#if  10
#define		M_tmpMoveLine(  idc_l,  idc_r  )  {																	\
				idc  =  idc_l;																					\
				GetWindowRect(  GetDlgItem(  pDlg->m_hWnd,  idc  ),  &rc  );									\
				MapWindowPoints(  NULL,  pDlg->m_hWnd,  (  LPPOINT  )&rc,  2  );								\
				iX  =  rc.left;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;						\
				MoveWindow(  GetDlgItem(  pDlg->m_hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );					\
				idc  =  idc_r;																					\
				GetWindowRect(  GetDlgItem(  pDlg->m_hWnd,  idc  ),  &rc  );									\
				MapWindowPoints(  NULL,  pDlg->m_hWnd,  (  LPPOINT  )&rc,  2  );								\
				iX  =  rc.left;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;						\
				MoveWindow(  GetDlgItem(  pDlg->m_hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );					\
				iY  +=  iH_btn  +  iY_space;																	\
			}

#else

	#define		M_tmpMoveLine(  idc_l,  idc_r  )  {										\
					}

#endif



int	sizeControls(  CDlgPolicyAv  *  pDlg  )
{
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	RECT	rc;
	int		idc;
	int		iY_t  =  0;
	int		iH_btn  =  0;
	int		iY_space  =  20;
	int		iX,  iY, iW,  iH;
	int		iEdge_b;
	
	//idc  =  IDC_BUTTON_setLdSettings;
	idc  =  IDC_BUTTON_set240pSettings;
	GetWindowRect(  GetDlgItem(  pDlg->m_hWnd,  idc  ),  &rc  );
	MapWindowPoints(  NULL,  pDlg->m_hWnd,  (  LPPOINT  )&rc,  2  );
	iY_t  =  rc.top;
	iH_btn  =  rc.bottom  -  rc.top;

#if  10
	//idc  =  IDC_BUTTON_setSd1Settings;
	idc  =  IDC_BUTTON_set480pSettings;
	GetWindowRect(  GetDlgItem(  pDlg->m_hWnd,  idc  ),  &rc  );
	MapWindowPoints(  NULL,  pDlg->m_hWnd,  (  LPPOINT  )&rc,  2  );
	iY_space  =  rc.top  -  (  iY_t  +  iH_btn  );
#endif

	idc  =  IDOK;
	GetWindowRect(  GetDlgItem(  pDlg->m_hWnd,  idc  ),  &rc  );
	RECT	rcDlg;
	GetWindowRect(  pDlg->m_hWnd,  &rcDlg  );
	iEdge_b  =  rcDlg.bottom  -  rc.bottom;
	
	
	//
	iY  =  iY_t;

#if  10
	//switch  (  qyGetAppAvLevel_qyMc(  pQyMc  )  )  
	{
				  switch  (  pDlg->m_var.uiCapType  )  {
						  case  CONST_capType_mediaFile:
						  case  CONST_capType_av:{
								{
								    //M_tmpMoveLine(  IDC_BUTTON_setLdSettings,  IDC_STATIC_ldSettings  );
								    M_tmpMoveLine(  IDC_BUTTON_set240pSettings,  IDC_STATIC_240pSettings  );
								    //M_tmpMoveLine(  IDC_BUTTON_setSdSettings,  IDC_STATIC_sdSettings  );
									//M_tmpMoveLine(  IDC_BUTTON_setSd1Settings,  IDC_STATIC_sd1Settings  );
									M_tmpMoveLine(  IDC_BUTTON_set480pSettings,  IDC_STATIC_480pSettings  );
								    //M_tmpMoveLine(  IDC_BUTTON_setSd2Settings,  IDC_STATIC_sd2Settings  );
								    //M_tmpMoveLine(  IDC_BUTTON_setSd3Settings,  IDC_STATIC_sd3Settings  );
								    M_tmpMoveLine(  IDC_BUTTON_set576pSettings,  IDC_STATIC_576pSettings  );
								    //M_tmpMoveLine(  IDC_BUTTON_setHdSettings,  IDC_STATIC_hdSettings  );
									//M_tmpMoveLine(  IDC_BUTTON_setHd1Settings,  IDC_STATIC_hd1Settings  );
									//M_tmpMoveLine(  IDC_BUTTON_setHd2Settings,  IDC_STATIC_hd2Settings  );
									M_tmpMoveLine(  IDC_BUTTON_set720pSettings,  IDC_STATIC_720pSettings  );
									//M_tmpMoveLine(  IDC_BUTTON_setHd3Settings,  IDC_STATIC_hd3Settings  );
									//M_tmpMoveLine(  IDC_BUTTON_setFullHdSettings,  IDC_STATIC_fullHdSettings  );
									//M_tmpMoveLine(  IDC_BUTTON_setFullHd1Settings,  IDC_STATIC_fullHd1Settings  );
									//M_tmpMoveLine(  IDC_BUTTON_setFullHd2Settings,  IDC_STATIC_fullHd2Settings  );
									M_tmpMoveLine(  IDC_BUTTON_set1080pSettings,  IDC_STATIC_1080pSettings  );
									//M_tmpMoveLine(  IDC_BUTTON_setFullHd3Settings,  IDC_STATIC_fullHd3Settings  );
								}
								}
							    break;
						  case  CONST_capType_mediaDevice:
						  case  CONST_capType_screen:
							    M_tmpMoveLine(  IDC_BUTTON_setDev2fpsSettings,  IDC_STATIC_setDev2fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings,  IDC_STATIC_setDev5fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings1,  IDC_STATIC_setDev5fpsSettings1  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings2,  IDC_STATIC_setDev5fpsSettings2  );
#if  0
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings4,  IDC_STATIC_setDev5fpsSettings4  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings5,  IDC_STATIC_setDev5fpsSettings5  );
#endif
								break;
#if  0
						  case  CONST_capType_mediaFile:
							    M_tmpMoveLine(  IDC_BUTTON_setDev2fpsSettings,  IDC_STATIC_setDev2fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings1,  IDC_STATIC_setDev5fpsSettings1  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings2,  IDC_STATIC_setDev5fpsSettings2  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings3,  IDC_STATIC_setDev5fpsSettings3  );
							    M_tmpMoveLine(  IDC_BUTTON_setDevSd24fpsSettings,  IDC_STATIC_setDevSd24fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDevSd25fpsSettings,  IDC_STATIC_setDevSd25fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDevSd30fpsSettings,  IDC_STATIC_setDevSd30fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev24fpsSettings,  IDC_STATIC_setDev24fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev25fpsSettings,  IDC_STATIC_setDev25fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev30fpsSettings,  IDC_STATIC_setDev30fpsSettings  );
							    break;
#endif
						  default:
							     break;
				  }
	}


#endif



	//
	iY  =  iY_t  +  13  *  (  iH_btn  +  iY_space  );
	iY  +=  4  *  iY_space;
	M_tmpMoveLine(  IDOK,  IDCANCEL  );


	GetWindowRect(  pDlg->m_hWnd,  &rc  );
	//
	RECT	rcClient;
	GetClientRect(  pDlg->m_hWnd,  &rcClient  );
	int  iH_notClient  =  rc.bottom  -  rc.top  -  (  rcClient.bottom  -  rcClient.top  );
	//
	MoveWindow(  pDlg->m_hWnd,  rc.left,  rc.top,  rc.right  -  rc.left,  iH_notClient  +  iY  +  iEdge_b,  TRUE  );
	
	return  0;
}

BOOL CDlgPolicyAv::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int		iErr	=	-1;
	QY_MC		*	pQyMc	= QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  m_hWnd,  IDD_policyAv  );

#if  0
	int	iAppAvLevel  =  qyGetAppAvLevel_qyMc(  pQyMc  );
	switch  (  iAppAvLevel  )  {
			case  CONST_qyAppAvLevel_hd:
				  //  2012/03/16
#if  0
				  GetDlgItem(  IDC_BUTTON_setLd1Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_ld1Settings  )->ShowWindow(  SW_HIDE  );
#endif
				  //
#if  0
				  GetDlgItem(  IDC_BUTTON_setHd1Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_STATIC_hd1Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_BUTTON_setHd2Settings  )->ShowWindow(  SW_HIDE  );	//  2012/01/28
				  GetDlgItem(  IDC_STATIC_hd2Settings  )->ShowWindow(  SW_HIDE  );	//  2012/01/28
				  GetDlgItem(  IDC_BUTTON_setHd3Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_hd3Settings  )->ShowWindow(  SW_HIDE  );
#endif
#if  0
				  GetDlgItem(  IDC_BUTTON_setFullHdSettings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_STATIC_fullHdSettings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_BUTTON_setFullHd1Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_STATIC_fullHd1Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
#endif
				  //GetDlgItem(  IDC_BUTTON_setFullHd2Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_BUTTON_set1080pSettings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  //GetDlgItem(  IDC_STATIC_fullHd2Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_STATIC_1080pSettings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
#if  0
				  GetDlgItem(  IDC_BUTTON_setFullHd3Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_fullHd3Settings  )->ShowWindow(  SW_HIDE  );
#endif
				  //  2012/03/04
#if  0
				  GetDlgItem(  IDC_BUTTON_setDev24fpsSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev24fpsSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setDev30fpsSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev30fpsSettings  )->ShowWindow(  SW_HIDE  );
#endif
				  break;
			case  CONST_qyAppAvLevel_fullHd:
				  //  GetDlgItem(  IDC_BUTTON_setLdSettings  )->ShowWindow(  SW_HIDE  );
				  //  GetDlgItem(  IDC_STATIC_ldSettings  )->ShowWindow(  SW_HIDE  );
				  //  2012/03/16
#if  0
				  GetDlgItem(  IDC_BUTTON_setLd1Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_ld1Settings  )->ShowWindow(  SW_HIDE  );
#endif
				  break;
			default:
				  //	case  CONST_qyAppAvLevel_sd:
				  //
#if  0
				  GetDlgItem(  IDC_BUTTON_set576pSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_576pSettings  )->ShowWindow(  SW_HIDE  );
#endif
				  //
				  //GetDlgItem(  IDC_BUTTON_setHd2Settings  )->ShowWindow(  SW_HIDE  );	//  2012/01/28
				  GetDlgItem(  IDC_BUTTON_set720pSettings  )->ShowWindow(  SW_HIDE  );	//  2012/01/28
				  //GetDlgItem(  IDC_STATIC_hd2Settings  )->ShowWindow(  SW_HIDE  );	//  2012/01/28
				  GetDlgItem(  IDC_STATIC_720pSettings  )->ShowWindow(  SW_HIDE  );	//  2012/01/28

				  //GetDlgItem(  IDC_BUTTON_setFullHd2Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_BUTTON_set1080pSettings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  //GetDlgItem(  IDC_STATIC_fullHd2Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_STATIC_1080pSettings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27

/*				  //  2012/03/04
				  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev5fpsSettings  )->ShowWindow(  SW_HIDE  );
*/				  //  2012/10/29
				  //GetDlgItem(  IDC_BUTTON_setDev5fpsSettings1  )->ShowWindow(  SW_HIDE  );
				  //GetDlgItem(  IDC_STATIC_setDev5fpsSettings1  )->ShowWindow(  SW_HIDE  );

#if  0
				  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings2  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev5fpsSettings2  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings3  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev5fpsSettings3  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings4  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev5fpsSettings4  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings5  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev5fpsSettings5  )->ShowWindow(  SW_HIDE  );
#endif

#if  0
				  GetDlgItem(  IDC_BUTTON_setDev24fpsSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev24fpsSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setDev30fpsSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev30fpsSettings  )->ShowWindow(  SW_HIDE  );
#endif
				  break;
	}
#endif

	switch  (  m_var.uiCapType  )  {
		case  CONST_capType_screen:
		case  CONST_capType_mediaDevice:
		case  CONST_capType_mediaFile:
		case  CONST_capType_av:
			  //  2015/03/11
			  if  (  m_var.uiCapType  ==  CONST_capType_screen
					 ||  (  m_var.uiCapType  ==  CONST_capType_mediaDevice  &&  m_var.uiSubCapType  ==  CONST_subCapType_unresizable  )  )
			  {
				  GetDlgItem(  IDC_BUTTON_set240pSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_240pSettings  )->ShowWindow(  SW_HIDE  );
				  //  2012/03/16
				  GetDlgItem(  IDC_BUTTON_set480pSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_480pSettings  )->ShowWindow(  SW_HIDE  );
				  //  2012/03/16
				  GetDlgItem(  IDC_BUTTON_set576pSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_576pSettings  )->ShowWindow(  SW_HIDE  );
				  //
				  GetDlgItem(  IDC_BUTTON_set720pSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_720pSettings  )->ShowWindow(  SW_HIDE  );
				  //
				  GetDlgItem(  IDC_BUTTON_set1080pSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_1080pSettings  )->ShowWindow(  SW_HIDE  );

				  break;
			  }
			  //
			  GetDlgItem(  IDC_BUTTON_setDev2fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev2fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev5fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings1  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev5fpsSettings1  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings2  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev5fpsSettings2  )->ShowWindow(  SW_HIDE  );
#if  0
			  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings3  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev5fpsSettings3  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings4  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev5fpsSettings4  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings5  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev5fpsSettings5  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev5fpsSettings5  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setDevSd24fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDevSd24fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setDevSd25fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDevSd25fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setDevSd30fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDevSd30fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setDev24fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev24fpsSettings  )->ShowWindow(  SW_HIDE  );
#endif
#if  0
			  GetDlgItem(  IDC_BUTTON_setDev25fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev25fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setDev30fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev30fpsSettings  )->ShowWindow(  SW_HIDE  );
#endif
#if 0
			  if  (  m_var.uiCapType  !=  CONST_capType_av  ){
				  //
				  GetDlgItem(  IDC_STATIC_reply  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_COMBO_reply  )->ShowWindow(  SW_HIDE  );
			  }
			  else if  (  m_var.uiSubCapType  ==  CONST_subCapType_webcam  ){
				  GetDlgItem(  IDC_STATIC_reply  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_COMBO_reply  )->ShowWindow(  SW_HIDE  );
#if  0
				  //
  				  GetDlgItem(  IDC_BUTTON_set240pSettings  )->ShowWindow(  SW_SHOW  );
				  GetDlgItem(  IDC_STATIC_240pSettings  )->ShowWindow(  SW_SHOW  );
				  //  2012/03/16
				  //
				  GetDlgItem(  IDC_BUTTON_set480pSettings  )->ShowWindow(  SW_SHOW  );
				  GetDlgItem(  IDC_STATIC_480pSettings  )->ShowWindow(  SW_SHOW  );
				  //  2012/03/16
				  //GetDlgItem(  IDC_BUTTON_set576pSettings  )->ShowWindow(  (  iAppAvLevel  <=  CONST_qyAppAvLevel_sd  ) ?  SW_HIDE  :  SW_SHOW  );		//  2012/06/12
				  //GetDlgItem(  IDC_STATIC_576pSettings  )->ShowWindow(  (  iAppAvLevel  <=  CONST_qyAppAvLevel_sd  ) ?  SW_HIDE  :  SW_SHOW  );			//  2012/06/12
				  //					
				  GetDlgItem(  IDC_BUTTON_set720pSettings  )->ShowWindow(  SW_SHOW  );
				  GetDlgItem(  IDC_STATIC_720pSettings  )->ShowWindow(  SW_SHOW  );
#endif
			  }
#endif
			  break;
		default:
			break;
	}

	//
	m_var.iPolicyAvLevel_req  =  getPolicyAvLevel(  pQyMc,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage  );
	//  m_var.iPolicyAvLevel_reply  =  getPolicyAvLevel(  m_var.uiCapType,  m_var.uiSubCapType,  CONST_capUsage_conf  );
	

	//
	sizeControls(  this  );
	bShowPolicy(  );

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		EndDialog(  -1  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPolicyAv::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	QY_MC			*	pQyMc					=  QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo				=	QY_GET_procInfo_isCli(  );
	PolicyAvParams	&	gAvParams				=	*pProcInfo->p_gAvParams;	//  QY_GET_PolicyAvParams(  );
	QY_REG				reg;	
	TCHAR			*	pRegVal					=	NULL;
	TCHAR				tBuf[128]				=  _T(  ""  );
	TCHAR			*   pT;
	int					idc						=	0;
	unsigned  char		ucbAsked				=	FALSE;
	TCHAR				tRootKey_av[256]		=	_T(  ""  );
	TCHAR				tRootKey_screen[256]	=	_T(  ""  );
	TCHAR				tRootKey_mediaFile[256]	=	_T(  ""  );
	TCHAR				tRootKey_webcam[256]	=	_T(  ""  );
	unsigned short		usTmp					=   0;
	TCHAR				name[128]				=	_T(  ""  );
	unsigned  char		ucCmd		=	0;
	CString				tmpCStr;

	CComboBox		*	pCb						=	NULL;
	QY_DMITEM		*	pTable		=	NULL;


	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
#if  0
	 if  (  !(  pT  =  qyGetDesByType(  CONST_capTypeTable,  m_var.uiCapType  )  )  )  return;		 
	 if  (  !pT[0]  )  return;
	 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s"  ),  pT  );
	 if  (  m_var.uiSubCapType  )  {
		 if  (  !(  pT  =  qyGetDesByType(  CONST_subCapTypeTable,  m_var.uiSubCapType  )  )  )  return;
		 if  (  !pT[0]  )  return;
		 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s.%s"  ),  name,  pT  );
	 }


	 lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );

	 _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  name  );
#endif
	 getRegRootKey_qmc(  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  reg.rootKey,  mycountof(  reg.rootKey  )  );


	//  2012/02/15
	switch  (  m_var.uiCapType  )  {
		case  CONST_capType_av:  {
			if  (  m_var.uiSubCapType  ==  CONST_subCapType_webcam  )  {
			  idc			=	IDC_COMBO_req;
			  pRegVal		=	CONST_regValName_policyAvLevel_req;
			  pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
			  pTable		=	getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable_webcam  );
			  ucCmd			=	DEFAULT_policyAvLevel_req_webcam;
			  //		
			  pCb->GetLBText(  pCb->GetCurSel(  ),  tmpCStr  );  
			  ucCmd  =  qyGetTypeByDes(  pTable,  tmpCStr  );
			  //  if  (  ucCmd  !=  pProcInfo->cfg.policy.iPolicyAvLevel_webcam  )  
			  if  (  ucCmd  !=  m_var.iPolicyAvLevel_req  )  
			  {
				  if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
				  ucbAsked  =  TRUE;
				  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  ucCmd,  tBuf,  10  )  );
			  }
			  //  pProcInfo->cfg.policy.iPolicyAvLevel_webcam  =  ucCmd;			  
			  m_var.iPolicyAvLevel_req  =  ucCmd;
			}
			else {
			  idc			=	IDC_COMBO_req;
			  pRegVal		=	CONST_regValName_policyAvLevel_req;
			  pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
			  pTable		=	getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable  );
			  //  ucCmd			=	DEFAULT_policyAvLevel_req;
			  ucCmd			=	getDefaultPolicyAvLevel(  pQyMc,  CONST_capType_av,  0,  m_var.iCapUsage  );
			  //		
			  pCb->GetLBText(  pCb->GetCurSel(  ),  tmpCStr  );  
			  ucCmd  =  qyGetTypeByDes(  pTable,  tmpCStr  );
			  //  if  (  ucCmd  !=  pProcInfo->cfg.policy.iPolicyAvLevel_req  )  
			  if  (  ucCmd  !=  m_var.iPolicyAvLevel_req  )  
			  {
				  if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
				  ucbAsked  =  TRUE;
				  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  ucCmd,  tBuf,  10  )  );
			  }
			  //  pProcInfo->cfg.policy.iPolicyAvLevel_req  =  ucCmd;
			  m_var.iPolicyAvLevel_req  =  ucCmd;
			  
#if  0  //  2014/12/15
			  //
			  getRegRootKey_qmc(  CONST_capType_av,  0,  CONST_capUsage_conf,  reg.rootKey,  mycountof(  reg.rootKey  )  );
			  idc			=	IDC_COMBO_reply;
			  pRegVal		=	CONST_regValName_policyAvLevel_req;
			  pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
			  pTable		=	getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable  );
			  ucCmd		=	getDefaultPolicyAvLevel(  CONST_capType_av,  0,  CONST_capUsage_conf  );
			  //		
			  pCb->GetLBText(  pCb->GetCurSel(  ),  tmpCStr  );  
			  ucCmd  =  qyGetTypeByDes(  pTable,  tmpCStr  );
			  //  if  (  ucCmd  !=  pProcInfo->cfg.policy.iPolicyAvLevel_reply  )  
			  if  (  ucCmd  !=  m_var.iPolicyAvLevel_reply  )  
			  {
				  if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
				  ucbAsked  =  TRUE;
				  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  ucCmd,  tBuf,  10  )  );
			  }
			  //  pProcInfo->cfg.policy.iPolicyAvLevel_reply  =  ucCmd;
			  m_var.iPolicyAvLevel_reply  =  ucCmd;
#endif
			}
			}
			break;
		case CONST_capType_screen:{
			  idc			=	IDC_COMBO_req;
			  pRegVal		=	CONST_regValName_policyAvLevel_req;
			  pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
			  pTable		=   getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable_screen  );
			  ucCmd			=	DEFAULT_policyAvLevel_req_screen;
			  //		
			  pCb->GetLBText(  pCb->GetCurSel(  ),  tmpCStr  );  
			  ucCmd  =  qyGetTypeByDes(  pTable,  tmpCStr  );
			  //  if  (  ucCmd  !=  pProcInfo->cfg.policy.iPolicyAvLevel_screen  )  
			  if  (  ucCmd  !=  m_var.iPolicyAvLevel_req  )  
			  {
				  if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
				  ucbAsked  =  TRUE;
				  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  ucCmd,  tBuf,  10  )  );
			  }
			  //  pProcInfo->cfg.policy.iPolicyAvLevel_screen  =  ucCmd;
			  m_var.iPolicyAvLevel_req  =  ucCmd;
			}
			break;
		case CONST_capType_mediaFile:{
			  idc			=	IDC_COMBO_req;
			  pRegVal		=	CONST_regValName_policyAvLevel_req;
			  pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
			  pTable		=   getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable_mediaFile  );
			  ucCmd			=	DEFAULT_policyAvLevel_req_mediaFile;
			  //		
			  pCb->GetLBText(  pCb->GetCurSel(  ),  tmpCStr  );  
			  ucCmd  =  qyGetTypeByDes(  pTable,  tmpCStr  );
			  //  if  (  ucCmd  !=  pProcInfo->cfg.policy.iPolicyAvLevel_mediaFile  )  
			  if  (  ucCmd  !=  m_var.iPolicyAvLevel_req  )  
			  {
				  if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
				  ucbAsked  =  TRUE;
				  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  ucCmd,  tBuf,  10  )  );
			  }
			  //  pProcInfo->cfg.policy.iPolicyAvLevel_mediaFile  =  ucCmd;
			  m_var.iPolicyAvLevel_req  =  ucCmd;
			}
			break;
		case CONST_capType_mediaDevice:{
			  idc			=	IDC_COMBO_req;
			  pRegVal		=	CONST_regValName_policyAvLevel_req;
			  pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );

			  if  (  m_var.uiSubCapType  ==  CONST_subCapType_unresizable  )  {
				  pTable		=   getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable_unresizable  );
				  ucCmd			=	DEFAULT_policyAvLevel_req_unresizable;
			  }
			  else  {
				  pTable		=   getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable_mediaDevice  );
				  ucCmd			=	DEFAULT_policyAvLevel_req_mediaDevice;
			  }
			  //		
			  pCb->GetLBText(  pCb->GetCurSel(  ),  tmpCStr  );  
			  ucCmd  =  qyGetTypeByDes(  pTable,  tmpCStr  );
			  //  if  (  ucCmd  !=  pProcInfo->cfg.policy.iPolicyAvLevel_mediaDevice  )  
			  if  (  ucCmd  !=  m_var.iPolicyAvLevel_req  )  
			  {
				  if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
				  ucbAsked  =  TRUE;
				  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  ucCmd,  tBuf,  10  )  );
			  }
			  //  pProcInfo->cfg.policy.iPolicyAvLevel_mediaDevice  =  ucCmd;
			  m_var.iPolicyAvLevel_req  =  ucCmd;
			}
			break;
		default:
			break;
	}


	OnOK();
}

//void CDlgPolicyAv::OnBnClickedButtonsetldsettings()
void CDlgPolicyAv::OnBnClickedButtonset240pSettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_240p;
	//idc  =  IDC_STATIC_ldSettings;
	idc  =  IDC_STATIC_240pSettings;

	if  (  m_var.iCapUsage  ==  CONST_capUsage_conf  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

#if  0
void CDlgPolicyAv::OnBnClickedButtonsetld1settings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;
	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_ld1;
	idc  =  IDC_STATIC_ld1Settings;

	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}
#endif

#if  0
void CDlgPolicyAv::OnBnClickedButtonsetsdsettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_sd;
	idc  =  IDC_STATIC_sdSettings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}
#endif

//void CDlgPolicyAv::OnBnClickedButtonsetsd1settings()
void CDlgPolicyAv::OnBnClickedButtonset480pSettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_480p;
	//idc  =  IDC_STATIC_sd1Settings;
	idc  =  IDC_STATIC_480pSettings;


	if  (  m_var.iCapUsage  ==  CONST_capUsage_conf  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

#if  0
void CDlgPolicyAv::OnBnClickedButtonsetsd2settings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;
	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_sd2;
	idc  =  IDC_STATIC_sd2Settings;

	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}
#endif

//void CDlgPolicyAv::OnBnClickedButtonsetsd3settings()
void CDlgPolicyAv::OnBnClickedButtonset576pSettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;
	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_576p;
	//idc  =  IDC_STATIC_sd3Settings;
	idc  =  IDC_STATIC_576pSettings;

	if  (  m_var.iCapUsage  ==  CONST_capUsage_conf  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

#if  0
void CDlgPolicyAv::OnBnClickedButtonsethdsettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_hd;
	idc  =  IDC_STATIC_hdSettings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}
#endif

#if  0
void CDlgPolicyAv::OnBnClickedButtonsethd1settings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_hd1;
	idc  =  IDC_STATIC_hd1Settings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}
#endif

//void CDlgPolicyAv::OnBnClickedButtonsethd2settings()
void CDlgPolicyAv::OnBnClickedButtonset720pSettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_720p;
	//idc  =  IDC_STATIC_hd2Settings;
	idc  =  IDC_STATIC_720pSettings;

	if  (  m_var.iCapUsage  ==  CONST_capUsage_conf  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

#if  0
void CDlgPolicyAv::OnBnClickedButtonsethd3settings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_hd3;
	idc  =  IDC_STATIC_hd3Settings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}
#endif

#if  0
void CDlgPolicyAv::OnBnClickedButtonsetfullhdsettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_fullHd;
	idc  =  IDC_STATIC_fullHdSettings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}
#endif

#if  0
void CDlgPolicyAv::OnBnClickedButtonsetfullhd1settings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_fullHd1;
	idc  =  IDC_STATIC_fullHd1Settings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}
#endif

//void CDlgPolicyAv::OnBnClickedButtonsetfullhd2settings()
void CDlgPolicyAv::OnBnClickedButtonset1080pSettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_1080p;
	//idc  =  IDC_STATIC_fullHd2Settings;
	idc  =  IDC_STATIC_1080pSettings;


	if  (  m_var.iCapUsage  ==  CONST_capUsage_conf  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

#if  0
void CDlgPolicyAv::OnBnClickedButtonsetfullhd3settings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_fullHd3;
	idc  =  IDC_STATIC_fullHd3Settings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}
#endif


void CDlgPolicyAv::OnBnClickedButtonsetdev2fpssettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_dev_2fps;
	idc  =  IDC_STATIC_setDev2fpsSettings;


	if  (  m_var.iCapUsage  ==  CONST_capUsage_conf  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_dev_5fps;
	idc  =  IDC_STATIC_setDev5fpsSettings;


	if  (  m_var.iCapUsage  ==  CONST_capUsage_conf  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings1()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_dev_5fps1;
	idc  =  IDC_STATIC_setDev5fpsSettings1;


	if  (  m_var.iCapUsage  ==  CONST_capUsage_conf  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.iCapUsage,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}



