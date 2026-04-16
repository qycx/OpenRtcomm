// DlgCfgVideoConference.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qymc.h"
#include	"myresource.h"
#include	"DlgCfgVideoConference.h"
#include	"qmCommonFunc_mis.h"
#include	"qyCusResTemp.h"
//#include	"qmshell_open.h"

#include	"msAecCommon.h"
#include	"isCliHelpPublic.h"
#include	"FuncsForIsCliHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgVideoConference dialog


CDlgCfgVideoConference::CDlgCfgVideoConference(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgVideoConference::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgVideoConference)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	memset(  &m_var,  0,  sizeof(  m_var  )  );

}


void CDlgCfgVideoConference::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgVideoConference)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgVideoConference, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgVideoConference)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgVideoConference message handlers

__declspec(  dllexport  )  int  showDlgCfgVideoConference(  HWND  hParent  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int  iRet  =  -1;

	CDlgCfgVideoConference	dlg(  CWnd::FromHandle(  hParent  )  );
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	iRet  =  IDOK;

errLabel:
	return  iRet;

}
void CDlgCfgVideoConference::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	QY_MC					*	pQyMc	=	QY_GET_GBUF(  );
	VIDEO_CONFERENCE_CFG		cfg;
	int							idc;

	memset(  &cfg,  0,  sizeof(  cfg  )  );


	idc  =  IDC_EDIT_conference_row;
	cfg.iRows  =  GetDlgItemInt(  idc  );
	if  (  !cfg.iRows  )  {
		GetDlgItem(  idc  )->SetFocus(  );  return;
	}

	idc  =  IDC_EDIT_conference_col;
	cfg.iCols  =  GetDlgItemInt(  idc  );
	if  (  !cfg.iCols  )  {
		GetDlgItem(  idc  )->SetFocus(  );  return;
	}

	if  (  cfg.iRows  *  cfg.iCols  >  MAX_mems_taskAv  )  {
		qyShowHint1(  this->m_hWnd,  _T(  "%s %d"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_invalidNumberAndMaxIs  ),  MAX_mems_taskAv  );
		idc  =  IDC_EDIT_conference_row;
		GetDlgItem(  idc  )->SetFocus(  );  return;
	}

	idc  =  IDC_EDIT_usCntLimit_activeMems_from;
	cfg.usMaxSpeakers  =  GetDlgItemInt(  idc  );
	if  (  !cfg.usMaxSpeakers  )  {
		GetDlgItem(  idc  )->SetFocus(  );  return;
	}
	if  (  cfg.usMaxSpeakers  >  MAX_speakers_taskAv  )  {
		qyShowHint1(  this->m_hWnd,  _T(  "%s %d"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_invalidNumberAndMaxIs  ),  MAX_speakers_taskAv  );
		GetDlgItem(  idc  )->SetFocus(  );  return;
	}

	//
	idc  =  IDC_CHECK_bUseAec;
	cfg.aecCfg.bUseAec  =  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  ?  1  :  0;

	idc  =  IDC_CHECK_bFeatrModeOn;
	cfg.aecCfg.bFeatrModeOn  =  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  ?  1  :  0;

	if  (  cfg.aecCfg.bFeatrModeOn  ==  FALSE  )  {
		cfg.aecCfg.bNoiseSup  =  0;
		cfg.aecCfg.bAGC  =  0;
		cfg.aecCfg.bCntrClip  =  0;
	}
	else
	{
		idc  =  IDC_CHECK_bNoiseSup;
		cfg.aecCfg.bNoiseSup  =  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  ?  1  :  0;
		idc  =  IDC_CHECK_bAGC;
		cfg.aecCfg.bAGC  =  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  ?  1  :  0;
		idc  =  IDC_CHECK_bCntrClip;
		cfg.aecCfg.bCntrClip  =  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  ?  1  :  0;
	}

	if  (  memcmp(  &cfg,  &m_var.videoConferenceCfg,  sizeof(  cfg  )  )  )  {
		HKEY		hKeyRoot0  =  HKEY_CURRENT_USER;
		TCHAR	*	pRootKey_qnmScheduler	=	pQyMc->cfg.pSysCfg->rootKey_qnmScheduler;
		char	*	pRegVal;
		TCHAR		tBuf[256]	=	_T(  ""  );

		pRegVal  =  CONST_regValName_monPics_row;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  cfg.iRows  );		
		qySetRegCfgT(  hKeyRoot0,  CString(  pRootKey_qnmScheduler  ),  CString(  pRegVal  ),  tBuf  );
		
		pRegVal  =  CONST_regValName_monPics_col;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  cfg.iCols  );		
		qySetRegCfgT(  hKeyRoot0,  CString(  pRootKey_qnmScheduler  ),  CString(  pRegVal  ),  tBuf  );
		
		//  2009/02/25
		pRegVal  =  CONST_regValName_usMaxSpeakers;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  cfg.usMaxSpeakers  );		
		qySetRegCfgT(  hKeyRoot0,  CString(  pRootKey_qnmScheduler  ),  CString(  pRegVal  ),  tBuf  );
		
		//
#if  0
		pRegVal  =  CONST_regValName_iWidth_pic;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  cfg.iWidth_pic  );		
		qySetRegCfgT(  hKeyRoot0,  CString(  pRootKey_qnmScheduler  ),  CString(  pRegVal  ),  tBuf  );
		
		pRegVal  =  CONST_regValName_iHeight_pic;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  cfg.iHeight_pic  );		
		qySetRegCfgT(  hKeyRoot0,  CString(  pRootKey_qnmScheduler  ),  CString(  pRegVal  ),  tBuf  );
#endif

		//  2013/05/25
		pRegVal  =  CONST_regValName_bUseAec;
		qySetRegCfgT(  hKeyRoot0,  CString(  pRootKey_qnmScheduler  ),  _T(  CONST_regValName_bUseAec  ),  cfg.aecCfg.bUseAec  ?  _T(  "1"  )  :  _T(  ""  )  );

		pRegVal  =  CONST_regValName_bFeatrModeOn;
		qySetRegCfgT(  hKeyRoot0,  CString(  pRootKey_qnmScheduler  ),  _T(  CONST_regValName_bFeatrModeOn  ),  cfg.aecCfg.bFeatrModeOn ?  _T(  "1"  )  :  _T(  ""  )  );

		pRegVal  =  CONST_regValName_bNoiseSup;
		qySetRegCfgT(  hKeyRoot0,  CString(  pRootKey_qnmScheduler  ),  _T(  CONST_regValName_bNoiseSup  ),  cfg.aecCfg.bNoiseSup ?  _T(  "1"  )  :  _T(  ""  )  );
		pRegVal  =  CONST_regValName_bAGC;
		qySetRegCfgT(  hKeyRoot0,  CString(  pRootKey_qnmScheduler  ),  _T(  CONST_regValName_bAGC  ),  cfg.aecCfg.bAGC ?  _T(  "1"  )  :  _T(  ""  )  );
		pRegVal  =  CONST_regValName_bCntrClip;
		qySetRegCfgT(  hKeyRoot0,  CString(  pRootKey_qnmScheduler  ),  _T(  CONST_regValName_bCntrClip  ),  cfg.aecCfg.bCntrClip ?  _T(  "1"  )  :  _T(  ""  )  );

		//  refresh video settings. 2009/07/27
		QY_SERVICEGUI_INFO	*	pSci				=	getServiceGuiInfo(  pQyMc,  pQyMc->iServiceId  );
		if  (  !pSci  )  goto  errLabel;
		MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pSci->pVar;
		if  (  !pProcInfo  )  goto  errLabel;
		/*
		memset(  &pProcInfo->av.localAv.videoCaptureProcInfo.policy.bih,  0,  sizeof(  pProcInfo->av.localAv.videoCaptureProcInfo.policy.bih  )  );
		pProcInfo->av.localAv.videoCaptureProcInfo.policy.bih.biWidth  =  cfg.iWidth_pic;
		pProcInfo->av.localAv.videoCaptureProcInfo.policy.bih.biHeight  =  cfg.iHeight_pic;
		*/
		//  refreshWebCamSettings(  &pProcInfo->av.localAv.videoCaptureProcInfo  );
	}

errLabel:
	OnOK();
}

BOOL CDlgCfgVideoConference::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int							iErr		=	-1;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	int							idc;

	//  if  (  setModalWnd(  m_hWnd  )  )  goto  errLabel;

#ifdef  __APP_qyMc_touchscreen__
		//  2011/03/26
		::SetWindowPos(  m_hWnd,  HWND_TOPMOST,  0,  0,  0,  0,  SWP_NOMOVE  |  SWP_NOSIZE  );
#endif

	//
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	getVideoConferenceCfg(  HKEY_CURRENT_USER,  CString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  NULL,  NULL,  &m_var.videoConferenceCfg  );

	SetDlgItemInt(  IDC_EDIT_conference_row,  m_var.videoConferenceCfg.iRows  );
	SetDlgItemInt(  IDC_EDIT_conference_col,  m_var.videoConferenceCfg.iCols  );

	SetDlgItemInt(  IDC_EDIT_usCntLimit_activeMems_from,  m_var.videoConferenceCfg.usMaxSpeakers  );

#if  0
	SetDlgItemInt(  IDC_EDIT_iWidth,  m_var.videoConferenceCfg.iWidth_pic  );
	SetDlgItemInt(  IDC_EDIT_iHeight,  m_var.videoConferenceCfg.iHeight_pic  );
#endif

	//
	idc			=  IDC_CHECK_bUseAec; 
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.videoConferenceCfg.aecCfg.bUseAec  ?  1  :  0  );

	idc			=  IDC_CHECK_bFeatrModeOn;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.videoConferenceCfg.aecCfg.bFeatrModeOn  ?  1  :  0  );

	if  (  m_var.videoConferenceCfg.aecCfg.bFeatrModeOn  )  {
		idc  =  IDC_CHECK_bNoiseSup;
		(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.videoConferenceCfg.aecCfg.bNoiseSup  ?  1  :  0  );
		idc  =  IDC_CHECK_bAGC;
		(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.videoConferenceCfg.aecCfg.bAGC  ?  1  :  0  );
		idc  =  IDC_CHECK_bCntrClip;
		(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.videoConferenceCfg.aecCfg.bCntrClip  ?  1  :  0  );
	}
	else  {		
		idc  =  IDC_CHECK_bNoiseSup;
		(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  FALSE  );
		idc  =  IDC_CHECK_bAGC;
		(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  FALSE  );
		idc  =  IDC_CHECK_bCntrClip;
		(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  FALSE  );
	} 
	

	//
	GetDlgItem(  IDC_STATIC_conference_col  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_EDIT_conference_col  )->ShowWindow(  SW_HIDE  );

	//
	if  (  !bSupported_aec(  )  )  GetDlgItem(  IDC_CHECK_bUseAec  )->EnableWindow(  FALSE  );

	//
	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		EndDialog(  -1  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



