// DlgImObjRule.cpp : implementation file
//

#include	"stdafx.h"

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
//  #include	"qyMc.h"
#include	"myresource.h"
#include	"DlgImObjRule.h"
//  #include	"DlgProgress.h"
#include	"isCliHelpPublic.h"
#include	"qyCusResTemp.h"
#include	"myDb.h"

#include	"dlgTalkProc.h"
#include	"funcsForIsCliHelp.h"


__declspec(  dllexport  )  int  showDlgImObjRule(  HWND  hParent,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int		iRet	=	-1;

	//
	CDlgImObjRule					dlg(  CWnd::FromHandle(  hParent  )  );	
	if  (  !dlg.bSetDlgInfo(  misServName,  pIdInfo  )  )  goto  errLabel;
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	iRet  =  IDOK;

errLabel:
	return  iRet;
}

//
__declspec(  dllexport  )  int  showDlgImObjRule(  HWND  hParent,  HWND  hCurTalk  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int		iRet	=	-1;

	//
	//
	CDlgImObjRule					dlg(  CWnd::FromHandle(  hParent  )  );	
	if  (  !dlg.bSetDlgInfo(  hCurTalk  )  )  goto  errLabel;
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	iRet  =  IDOK;

errLabel:
	return  iRet;
}


//
int  tmpSetRect(  RECT  &  rc  )	
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	//
	G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )pFuncs->pf_get_g_guiData(  );

	rc.left  *=  pGuiData->fx;
	rc.right  *=  pGuiData->fx;
	rc.bottom  *=  pGuiData->fy;
	rc.top  *=  pGuiData->fy;
	return  0;
}

// CDlgImObjRule dialog

IMPLEMENT_DYNAMIC(CDlgImObjRule, CDialog)

CDlgImObjRule::CDlgImObjRule(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgImObjRule::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgImObjRule::~CDlgImObjRule()
{
}


BOOL  CDlgImObjRule::bSetDlgInfo(  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  )
{
		MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;

	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;

	//m_var.pMisCnt  =  pFuncs->pf_getMisCntByName(  pProcInfo,  misServName  );
	m_var.idInfo.ui64Id  =  pIdInfo->ui64Id;
	return  TRUE;
}


//
BOOL  CDlgImObjRule::bSetDlgInfo(  HWND  hCurTalk  )
{
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );

	//
	m_var.m_hCurTalk  =  hCurTalk;
	
	//
	CHelp_getDlgTalkVar		help_getDlgTalkVar;
	DLG_TALK_var		*	pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  m_var.m_hCurTalk  );
	if  (  !pDlgTalkVar  )  return  FALSE;



	//
	//m_var.pMisCnt  =  pFuncs->pf_getMisCntByName(  pProcInfo,  _T(  ""  )  );
	m_var.idInfo.ui64Id  =  pDlgTalkVar->addr.idInfo.ui64Id;

	return  TRUE;
}




void CDlgImObjRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImObjRule, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgImObjRule::OnBnClickedOk)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHECK_shareWebcamInConference, &CDlgImObjRule::OnBnClickedChecksharewebcaminconference)
	ON_BN_CLICKED(IDC_BUTTON_selectAvCompressor, &CDlgImObjRule::OnBnClickedButtonselectavcompressor)
END_MESSAGE_MAP()



int  dlgSetFont_imObjRule(  HWND  hDlg  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	CDlgImObjRule	*	pDlg	=	(  CDlgImObjRule  *  )CWnd::FromHandle(  hDlg  );
	if  (  !pDlg  )  return  -1;

	DLG_guiData_imObjRule	*	p	=	&pDlg->m_var.guiData;
		G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )pFuncs->pf_get_g_guiData(  );

		int		idc;
		HWND	hCtrl;

		idc  =  p->iIDC_STATIC_hint_imObjRule;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_STATIC_autoAnswer_av;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_COMBO_autoAnswer_av;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_STATIC_autoAnswer_screen;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_COMBO_autoAnswer_screen;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_STATIC_autoAnswer_mediaFile;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDC_COMBO_autoAnswer_mediaFile;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDCANCEL;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		idc  =  p->iIDOK;
		hCtrl	=	::GetDlgItem(  hDlg,  idc  );
		if  (  hCtrl  )  {
			if  (  pGuiData->hFont_btn  )  {
				::SendMessage(  hCtrl,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_btn,  TRUE  );
			}
		}

		return  0;

}
// CDlgImObjRule message handlers

BOOL CDlgImObjRule::OnInitDialog()
{
	CDialog::OnInitDialog();

	int			iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	QM_dbFuncs  &  g_dbFuncs  =  *pQyMc->p_g_dbFuncs;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;

	//
	CQnmDb		db;	
	if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;

	int				iX  =  0,  iY  =  0;

	int				idc;
	HWND			hWnd;
	RECT			rc;
	CRect			rcDialog;
	HWND			hDlg										=	this->m_hWnd;

	//  2011/03/30
	if  (  setModalWnd(  pQyMc,  m_hWnd  )  )  goto  errLabel;

	#ifdef  __APP_qyMc_touchscreen__
			::SetWindowPos(  m_hWnd,  HWND_TOPMOST,  0,  0,  0,  0,  SWP_NOMOVE  |  SWP_NOSIZE  );
	#endif

	// TODO:  Add extra initialization here

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );



	//
	if  (  !pQyMc  ||  !pQyMc->cfg.pGuiCfg  )  goto  errLabel;
	if  (  !pProcInfo  )  goto  errLabel;
	DLG_guiData_imObjRule	*	p	=	&m_var.guiData;


	::GetClientRect(  hDlg,  &rc  );
	p->w_org  =  rc.right  -  rc.left;
	p->h_org  =  rc.bottom  -  rc.top;

	if  (  !p->w_org  ||  !p->h_org  )  goto  errLabel;

	p->iIDC_STATIC_hint_imObjRule  =  IDC_STATIC_hint_imObjRule;
	p->iIDC_STATIC_autoAnswer_av  =  IDC_STATIC_autoAnswer_av;
	p->iIDC_COMBO_autoAnswer_av  =  IDC_COMBO_autoAnswer_av;
	p->iIDC_STATIC_autoAnswer_screen  =  IDC_STATIC_autoAnswer_screen;
	p->iIDC_COMBO_autoAnswer_screen  =  IDC_COMBO_autoAnswer_screen;
	p->iIDC_STATIC_autoAnswer_mediaFile  =  IDC_STATIC_autoAnswer_mediaFile;
	p->iIDC_COMBO_autoAnswer_mediaFile  =  IDC_COMBO_autoAnswer_mediaFile;
	p->iIDCANCEL  =  IDCANCEL;
	p->iIDOK  =  IDOK;
	
#if  10
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_STATIC_hint_imObjRule  ),  &p->rcIDC_STATIC_hint_imObjRule  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_hint_imObjRule,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_STATIC_autoAnswer_av  ),  &p->rcIDC_STATIC_autoAnswer_av  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_autoAnswer_av,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_COMBO_autoAnswer_av  ),  &p->rcIDC_COMBO_autoAnswer_av  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_COMBO_autoAnswer_av,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_STATIC_autoAnswer_screen  ),  &p->rcIDC_STATIC_autoAnswer_screen  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_autoAnswer_screen,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_COMBO_autoAnswer_screen  ),  &p->rcIDC_COMBO_autoAnswer_screen  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_COMBO_autoAnswer_screen,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_STATIC_autoAnswer_mediaFile  ),  &p->rcIDC_STATIC_autoAnswer_mediaFile  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_autoAnswer_mediaFile,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_COMBO_autoAnswer_mediaFile  ),  &p->rcIDC_COMBO_autoAnswer_mediaFile  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_COMBO_autoAnswer_mediaFile,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDCANCEL  ),  &p->rcIDCANCEL  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDCANCEL,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDOK  ),  &p->rcIDOK  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDOK,  2  );

#endif 

#ifdef  __APP_qyMc_touchscreen__
	{
		G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )get_g_guiData(  );

		p->w_org  *=  pGuiData->fx;
		p->h_org  *=  pGuiData->fy;

		tmpSetRect(  p->rcIDC_STATIC_hint_imObjRule  );
		tmpSetRect(  p->rcIDC_STATIC_autoAnswer_av  );
		tmpSetRect(  p->rcIDC_COMBO_autoAnswer_av  );
		tmpSetRect(  p->rcIDC_STATIC_autoAnswer_screen  );
		tmpSetRect(  p->rcIDC_COMBO_autoAnswer_screen  );
		tmpSetRect(  p->rcIDC_STATIC_autoAnswer_mediaFile  );
		tmpSetRect(  p->rcIDC_COMBO_autoAnswer_mediaFile  );
		tmpSetRect(  p->rcIDCANCEL  );
		tmpSetRect(  p->rcIDOK  );
	}
	//
	int		w, h;
	HWND	hParent	=	::GetParent(  hDlg  );
	if  (  !hParent  )  goto  errLabel;
	::GetWindowRect(  hParent,  &rc  );
	w  =  rc.right  -  rc.left;
	h  =  rc.bottom  -  rc.top;

	iX  =  (  rc.left  +  rc.right  )  /  2  -  p->w_org  /  2;
	iY  =  (  rc.top  +  rc.bottom  )  /  2  -  p->h_org  /  2;		
	::MoveWindow(  hDlg,  iX,  iY,  p->w_org,  p->h_org,  TRUE  );

	dlgSetFont_imObjRule(  m_hWnd  );
#endif

	m_var.guiData.bInited  =  TRUE;

	//
	REFRESH_imObjRules_req	req;
	QY_MESSENGER_ID			idInfo_related;

	//  先取全局策略
	idInfo_related.ui64Id  =  0;
	if  (  g_dbFuncs.pf_bGetImObjRulesReq(  db.m_pDbMem->pDb,  pQyMc->cfg.db.iDbType,  _T(  ""  ),  0,  &idInfo_related,  NULL,  0,  &req  )  )  {
		pFuncs->pf_imObjRulesReq2ImRules(  &req,  &m_var.imRules  );
	}

	//  再取messenger的策略
	if  (  g_dbFuncs.pf_bGetImObjRulesReq(  db.m_pDbMem->pDb,  pQyMc->cfg.db.iDbType,  _T(  ""  ),  0,  &m_var.idInfo,  NULL,  0,  &req  )  )  {
		pFuncs->pf_imObjRulesReq2Rules(  &req,  &m_var.idInfo,  &m_var.rules  );
	}

	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	if  (  memcmp(  &pMisCnt->imRules,  &m_var.imRules,  sizeof(  pMisCnt->imRules  )  )  )  {
		memcpy(  &pMisCnt->imRules,  &m_var.imRules,  sizeof(  pMisCnt->imRules  )  );
		#ifdef  __DEBUG__
				traceLog(  _T(  "Warning: dlgImObjRule: imRules not correct"  )  );
		#endif
	}

	//  2010/09/24
	QM_OBJQ_MEM				mem;		
	QMEM_MESSENGER_CLI	*	pQMem;
	if  (  !pFuncs->pf_findQMemByKey(  0,  pMisCnt->pObjQ,  &m_var.idInfo,  &mem  )  )  {
		pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
		if  (  pQMem  )  {
			if  (  memcmp(  &pQMem->rules,  &m_var.rules,  sizeof(  pQMem->rules  )  )  )  {
				memcpy(  &pQMem->rules,  &m_var.rules,  sizeof(  pQMem->rules  )  );
				#ifdef  __DEBUG__
						traceLog(  _T(  "Warning: dlgImObjRule: rules is not correct"  )  );
				#endif
			}
		}
	}

	char	buf[128];

	idc			=	IDC_CHECK_shareWebcamInConference;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.imRules.conferenceId_shareWebcam.ui64Id  ==  m_var.idInfo.ui64Id  ?  1  :  0  );
	idc  =  IDC_EDIT_conferenceId_shareWebcam;
	_snprintf(  buf,  mycountof(  buf  ),  "%I64u",  m_var.imRules.conferenceId_shareWebcam.ui64Id  );
	SetDlgItemText(  idc,  CString(  buf  )  );
	idc			=	IDC_CHECK_noLocalVideoInThisConference;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.imRules.ucbNoLocalVideoInThisConference  ?  1  :  0  );
	idc  =  IDC_CHECK_distinguishSharedWebcams;
	(  (  CButton  *  )GetDlgItem(  idc  )  )->SetCheck(  m_var.imRules.ucbDistinguishSharedWebcams  ?  1  :  0  );

	idc  =  IDC_EDIT_conferenceId_shareWebcam;
	GetDlgItem(  idc  )->EnableWindow(  FALSE  );

	//
	QY_DMITEM	*	pTable	=	getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleCmdTable_autoAnswer  );
	QY_DMITEM	*	pItem;
	CComboBox	*	pCombo;

	pCombo	=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_autoAnswer_av  );
	for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  {
		 pCombo->InsertString(  -1,  pItem->des  );
	}
	pCombo->SelectString(  -1,  qyGetDesByType1(  pTable,  m_var.rules.uiCmd_autoAnswer_av  )  );

	pCombo	=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_autoAnswer_screen  );
	for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  {
		 pCombo->InsertString(  -1,  pItem->des  );
	}
	pCombo->SelectString(  -1,  qyGetDesByType1(  pTable,  m_var.rules.uiCmd_autoAnswer_screen  )  );

	pCombo	=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_autoAnswer_mediaFile  );
	for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  {
		 pCombo->InsertString(  -1,  pItem->des  );
	}
	pCombo->SelectString(  -1,  qyGetDesByType1(  pTable,  m_var.rules.uiCmd_autoAnswer_mediaFile  )  );

	//
	#ifdef  __APP_qyMc_touchscreen__
			GetDlgItem(  IDC_CHECK_shareWebcamInConference  )->ShowWindow(  SW_HIDE  );
			GetDlgItem(  IDC_STATIC_conferenceId_shareWebcam  )->ShowWindow(  SW_HIDE  );
			GetDlgItem(  IDC_EDIT_conferenceId_shareWebcam  )->ShowWindow(  SW_HIDE  );
			GetDlgItem(  IDC_CHECK_noLocalVideoInThisConference  )->ShowWindow(  SW_HIDE  );
			GetDlgItem(  IDC_CHECK_distinguishSharedWebcams  )->ShowWindow(  SW_HIDE  );
			GetDlgItem(  IDC_STATIC_group  )->ShowWindow(  SW_HIDE  );
	#endif

	iErr   =  0;

errLabel:

	if  (  iErr  )  {
		EndDialog(  -1  );
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

#if  0
 int  tmp_getnFromRules(  QY_imObj_rules  *  pRules  )
{
	int	n	=	0;

	if  (  pRules->uiCmd_autoAnswer_av  )  n  ++  ;
	if  (  pRules->uiCmd_autoAnswer_screen  )  n  ++  ;
	if  (  pRules->uiCmd_autoAnswer_mediaFile  )  n  ++  ;
	return  n;
}
#endif


 void CDlgImObjRule::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	int				iErr		=	-1;
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	FUNCS_for_isCliHelp  *  pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );  

	CComboBox	*	pCombo		=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_autoAnswer_av  );
	QY_DMITEM	*	pTable		=	getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleCmdTable_autoAnswer  );
	//  QY_DMITEM	*	pItem;
	CString			str;
	QY_im_rules		imRules;
	QY_imObj_rules	rules;
	int				i;
	int				iRuleType	=	0;
	unsigned  int	uiCmd		=	0;
	int				idc;
	TCHAR			tBuf[256];
	char			buf[128];
	unsigned  char	ucbVal;

	memset(  &imRules,  0,  sizeof(  imRules  )  );
	memset(  &rules,  0,  sizeof(  rules  )  );

	//
	idc  =  IDC_EDIT_conferenceId_shareWebcam;
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );  myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
	idStr2Info(  buf,  &imRules.conferenceId_shareWebcam  );

	idc  =  IDC_CHECK_noLocalVideoInThisConference;
	ucbVal  =  FALSE;
	if  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  {	
		ucbVal  =  TRUE;
	}
	imRules.ucbNoLocalVideoInThisConference  =  ucbVal;

	idc  =  IDC_CHECK_distinguishSharedWebcams;
	ucbVal  =  FALSE;
	if  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  {	
		ucbVal  =  TRUE;
	}
	imRules.ucbDistinguishSharedWebcams  =  ucbVal;

	//
	idc  =  IDC_COMBO_autoAnswer_av;
	GetDlgItemText(  idc,  str  );
	rules.uiCmd_autoAnswer_av  =  qyGetTypeByDes(  pTable,  str  );

	idc  =  IDC_COMBO_autoAnswer_screen;
	GetDlgItemText(  idc,  str  );
	rules.uiCmd_autoAnswer_screen  =  qyGetTypeByDes(  pTable,  str  );

	idc  =  IDC_COMBO_autoAnswer_mediaFile;
	GetDlgItemText(  idc,  str  );
	rules.uiCmd_autoAnswer_mediaFile  =  qyGetTypeByDes(  pTable,  str  );

	//
	if  (  memcmp(  &imRules,  &m_var.imRules,  sizeof(  imRules  )  )
		||  memcmp(  &rules,  &m_var.rules,  sizeof(  rules  )  )  )  
	{
		CQyMalloc					mallocObj_pStream;
		IM_L_STREAM			*	pStream			=	(  IM_L_STREAM  *  )mallocObj_pStream.mallocf(  sizeof(  IM_L_STREAM  )  );
		if  (  !pStream  )  goto  errLabel;

		REFRESH_imObjRules_req	req;
		MACRO_prepareForTran(  );
		int					len;

		if  (  !pFuncs->pf_bMessengerOnline(  (  QY_MC  *  )pProcInfo->pQyMc  )  )  {
			myMessageBox(  m_hWnd,  _T(  "Failed: Messenger is offline"  ),  _T(  ""  ),  MB_OK  );
			return;
		}

		//
		memset(  &req,  0,  sizeof(  req  )  );
		req.uiType  =  CONST_imCommType_refreshImObjRulesReq;
		i  =  0;

		if  (  imRules.conferenceId_shareWebcam.ui64Id  !=  m_var.imRules.conferenceId_shareWebcam.ui64Id  )  {
			if  (  i  >=  mycountof(  req.mems  )  )  {
				qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_autoAnswerlimited  )  );
				goto  errLabel;
			}
			//
			iRuleType  =  CONST_ruleType_conferenceId_shareWebcam;
			uiCmd  =  imRules.conferenceId_shareWebcam.ui64Id  ?  CONST_ruleCmd_permit  :  0;
			//
			req.mems[i].idInfo_related.ui64Id  =  0;
			req.mems[i].uiRuleType  =  iRuleType;
			req.mems[i].uiCmd  =  uiCmd;
			//  req.mems[i].l64Val  =  imRules.conferenceId_shareWebcam.ui64Id;
			_sntprintf(  req.mems[i].wDesc,  mycountof(  req.mems[i].wDesc  ),  _T(  "%I64u"  ),  imRules.conferenceId_shareWebcam.ui64Id  );
			i  ++  ;
		}
		if  (  imRules.ucbNoLocalVideoInThisConference  !=  m_var.imRules.ucbNoLocalVideoInThisConference  )  {
			if  (  i  >=  mycountof(  req.mems  )  )  {
				qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_autoAnswerlimited  )  );
				goto  errLabel;
			}
			//
			iRuleType  =  CONST_ruleType_ucbNoLocalVideoInThisConference;
			uiCmd  =  imRules.ucbNoLocalVideoInThisConference  ?  CONST_ruleCmd_permit  :  0;
			//
			req.mems[i].idInfo_related.ui64Id  =  0;
			req.mems[i].uiRuleType  =  iRuleType;
			req.mems[i].uiCmd  =  uiCmd;
			i  ++  ;
		}
		if  (  imRules.ucbDistinguishSharedWebcams  !=  m_var.imRules.ucbDistinguishSharedWebcams  )  {
			if  (  i  >=  mycountof(  req.mems  )  )  {
				qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_autoAnswerlimited  )  );
				goto  errLabel;
			}
			//
			iRuleType  =  CONST_ruleType_ucbDistinguishSharedWebcams;
			uiCmd  =  imRules.ucbDistinguishSharedWebcams  ?  CONST_ruleCmd_permit  :  0;
			//
			req.mems[i].idInfo_related.ui64Id  =  0;
			req.mems[i].uiRuleType  =  iRuleType;
			req.mems[i].uiCmd  =  uiCmd;
			i  ++  ;
		}

		if  (  rules.uiCmd_autoAnswer_av  !=  m_var.rules.uiCmd_autoAnswer_av  )  {

			if  (  i  >=  mycountof(  req.mems  )  )  {
				qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_autoAnswerlimited  )  );
				goto  errLabel;
			}

			//
			iRuleType  =  CONST_ruleType_autoAnswer_av;
			uiCmd  =  rules.uiCmd_autoAnswer_av;
			//
			req.mems[i].idInfo_related.ui64Id  =  m_var.idInfo.ui64Id;
			req.mems[i].uiRuleType  =  iRuleType;
			req.mems[i].uiCmd  =  uiCmd;
			i  ++  ;
		}

		if  (  rules.uiCmd_autoAnswer_screen  !=  m_var.rules.uiCmd_autoAnswer_screen  )  {
			
			if  (  i  >=  mycountof(  req.mems  )  )  {
				qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_autoAnswerlimited  )  );
				goto  errLabel;
			}

			//
			iRuleType  =  CONST_ruleType_autoAnswer_screen;
			uiCmd  =  rules.uiCmd_autoAnswer_screen;
			//
			req.mems[i].idInfo_related.ui64Id  =  m_var.idInfo.ui64Id;
			req.mems[i].uiRuleType  =  iRuleType;
			req.mems[i].uiCmd  =  uiCmd;
			i  ++  ;
		}

		if  (  rules.uiCmd_autoAnswer_mediaFile  !=  m_var.rules.uiCmd_autoAnswer_mediaFile  )  {

			if  (  i  >=  mycountof(  req.mems  )  )  {
				qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_autoAnswerlimited  )  );
				goto  errLabel;
			}

			//
			iRuleType  =  CONST_ruleType_autoAnswer_mediaFile;
			uiCmd  =  rules.uiCmd_autoAnswer_mediaFile;
			//
			req.mems[i].idInfo_related.ui64Id  =  m_var.idInfo.ui64Id;
			req.mems[i].uiRuleType  =  iRuleType;
			req.mems[i].uiCmd  =  uiCmd;
			i  ++  ;
		}

		MACRO_qyAssert(  i  <  mycountof(  req.mems  ),  _T(  "too many rules"  )  );
		//
		req.usCnt  =  i;


		//  2010/08/14
		pFuncs->pf_startProgress(  &pQyMc->gui.progress,  uiTranNo  );

		//
		MACRO_memset_imLStream(  pStream  );
		pStream->uiType  =  CONST_imCommType_lStream;
		pStream->uiContentType  =  req.uiType;
		len  =  sizeof(  pStream->buf  );
		if  (  refreshImObjRulesReq2Stream(  pStream->uiContentType,  &req,  pStream->buf,  (  unsigned  int  *  )&len  )  )  goto  errLabel;
		pStream->ulStreamLen  =  len;
		len  +=  offsetof(  IM_L_STREAM,  buf  ); 

		MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
		//
		postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_refreshImObjListReq,  tStartTran,  uiTranNo,  0,  (  char  *  )pStream,  len,  NULL,  0,  0,  NULL,  0  ); 

#if  0
		{	
			CDlgProgress	dlg(  this  );
			dlg.bSetDlgInfo(  _T(  "Please waiting"  ),  NULL,  30,  -1,  uiTranNo  ); 

			//  traceLogA(  "if task is not ready, cancel the task by clear shmCmd, and the subprocess will quit when it read the shmCmd."  );
			if  (  dlg.DoModal(  )  !=  IDOK  )  {
				goto  errLabel;
			}
		}
#endif
		if  (  showProgress(  &pQyMc->gui.progress,  &pQyMc->cusRes,  this->m_hWnd,  _T(  "Please waiting"  ),  NULL,  30,  -1,  uiTranNo  )  !=  IDOK  )  {
			goto  errLabel;
		}

		//
		CQnmDb				db;
		if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;

		recoverImObjRules(  pQyMc->p_g_dbFuncs,  db.m_pDbMem->pDb,  pQyMc->cfg.db.iDbType,  _T(  ""  ),  &pMisCnt->idInfo,  &req,  0  );

		//  2011/11/17
		if  (  memcmp(  &pMisCnt->imRules,  &imRules,  sizeof(  pMisCnt->imRules  )  )  )  {
			memcpy(  &pMisCnt->imRules,  &imRules,  sizeof(  pMisCnt->imRules  )  );
		}

		QM_OBJQ_MEM				mem;		
		QMEM_MESSENGER_CLI	*	pQMem;
		if  (  !pFuncs->pf_findQMemByKey(  0,  pMisCnt->pObjQ,  &m_var.idInfo,  &mem  )  )  {
			pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
			if  (  pQMem  )  {
				memcpy(  &pQMem->rules,  &rules,  sizeof(  pQMem->rules  )  );
			}
		}
	}

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		return;
	}

	OnOK();
}

void CDlgImObjRule::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	DLG_guiData_imObjRule	*	p	=	&m_var.guiData;

	if  (  !p->w_org  ||  !p->h_org  )  return;

	RECT	rc;
	GetClientRect(  &rc  );
	int  w,  h;
	w  =  rc.right  -  rc.left;
	h  =  rc.bottom  -  rc.top;


	//  
	int	idc;
	int  iX,  iY,  iW,  iH;
	float  fx,  fy;
	fx  =  1.  *  w  /  p->w_org;
	fy  =  1.  *  h  /  p->h_org;

	//	
	idc  =  p->iIDC_STATIC_autoAnswer_av;
	rc  =  p->rcIDC_STATIC_autoAnswer_av;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_COMBO_autoAnswer_av;
	rc  =  p->rcIDC_COMBO_autoAnswer_av;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_STATIC_autoAnswer_screen;
	rc  =  p->rcIDC_STATIC_autoAnswer_screen;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_COMBO_autoAnswer_screen;
	rc  =  p->rcIDC_COMBO_autoAnswer_screen;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_STATIC_autoAnswer_mediaFile;
	rc  =  p->rcIDC_STATIC_autoAnswer_mediaFile;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_COMBO_autoAnswer_mediaFile;
	rc  =  p->rcIDC_COMBO_autoAnswer_mediaFile;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDCANCEL;
	rc  =  p->rcIDCANCEL;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDOK;
	rc  =  p->rcIDOK;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	return;
}

void CDlgImObjRule::OnBnClickedChecksharewebcaminconference()
{
	// TODO: Add your control notification handler code here
	int		idc;
	TCHAR	tBuf[128];

	idc			=	IDC_CHECK_shareWebcamInConference;
	if  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  {
		//  (  m_var.imRules.conferenceId_shareWebcam.ui64Id  ==  m_var.idInfo.ui64Id  ?  1  :  0  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  m_var.idInfo.ui64Id  );
		SetDlgItemText(  IDC_EDIT_conferenceId_shareWebcam,  tBuf  );
	}
	else  {
		  SetDlgItemText(  IDC_EDIT_conferenceId_shareWebcam,  _T(  ""  )  );
	}


}

void CDlgImObjRule::OnBnClickedButtonselectavcompressor()
{
	// TODO: Add your control notification handler code here
	int								iErr					=	-1;

	HWND							hMgr					=	NULL;
	DLG_TALK_var				*	pMgrVar					=	NULL;

	DLG_TALK_var				*	pCurVar					=	NULL;

	CHelp_getDlgTalkVar				help_getDlgTalkVar_cur;	
	CHelp_getDlgTalkVar				help_getDlgTalkVar_mgr;
		
	//  
	QY_MC						*	pQyMc					=	QY_GET_GBUF(  );
	MC_VAR_isCli				*	pProcInfo				=	QY_GET_procInfo_isCli(  );
	FUNCS_for_isCliHelp			*	pFuncs					=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	MIS_CNT  *  pMisCnt  =  pFuncs->pf_getMisCntByName(  pProcInfo,  _T(  ""  )  );
	if  (  !pMisCnt  )  return;

	//
	HWND  hCurTalk  =  m_var.m_hCurTalk;

	//
	pCurVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_cur.getVar(  hCurTalk  );
	if  (  !pCurVar  )  return;

	//
	if  (  !isTalkerShadowMgr(  pCurVar->addr  )  )  {
		TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pCurVar->pShadowInfo;
		if  (  !pTalkerShadow  )  goto  errLabel;
		if  (  !IsWindow(  pTalkerShadow->hMgr  )  )  goto  errLabel;
		hMgr  =  pTalkerShadow->hMgr;		//  2013/02/15
		pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pTalkerShadow->hMgr  );
		if  (  !pMgrVar  )  goto  errLabel;
		}
	else  {
		  //
		  hMgr  =  hCurTalk;
		  pMgrVar  =  pCurVar;
	}

	//

	//
	{
			HWND  hCurTalker  =  hCurTalk;
	DLG_TALK_var  *  pm_var  =  pMgrVar;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

	//
				  //
				  if  (  pProcInfo->viewDlgSelectAvCompressor(  m_hWnd,  pMgrVar->addr.idInfo,  CONST_capType_av,  0,  FALSE,  FALSE,  0  )  !=  IDOK  )  goto  errLabel;
				  				
				  TALKER_policy  policy;
				  getTalkerPolicy(  &pm_var->addr.idInfo,  &policy  );
				  //
#if  0
				  pm_var->m_layout.ucbShowBgWall_starter  =  policy.ucbShowBgWall_starter;
				  //
				  pm_var->m_layout.ucbNeverJoinInBgWall  =  policy.ucbNeverJoinInBgWall;
				  pm_var->m_layout.ucbShowBgWall_confMem  =  ucbShowBgWall_confMem;
#endif
				  //
				  //pm_var->m_layout.usPollingIntervalInS  =  policy.usPollingIntervalInS;
				  //
#if  0
				  pm_var->m_layout.bgWallLayout.usRows_bg  =  policy.bgWallLayout.usRows_bg;
				  pm_var->m_layout.bgWallLayout.usCols_bg  =  policy.bgWallLayout.usCols_bg;
#endif
				  //
				  if  (  !pm_var->av.taskInfo.ucbStarter  )  {
#if  0
					  if  (  pm_var->av.taskInfo.bTaskExists  &&  !pm_var->m_layout.ucbNeverJoinInBgWall  )  {
						  if  (  pm_var->m_layout.ucbShowBgWall_confMem  )  {
							  pShadowMgr->av.joinInBgWall.idcRet_joinInBgWall  =  ID_qyOk;
							  pFuncs->pf_setCurSharedObjUsr_localAv(  pProcInfo,  pm_var->av.iIndex_sharedObj_localAv,  hMgr  );  
						  }
						  else  {
								  pShadowMgr->av.joinInBgWall.idcRet_joinInBgWall  =  ID_qyCancel;
						  }
					  }
#endif
				  }
				  //
				  dlgTalk_doLayout(  hCurTalker  );
				  }


errLabel:
	return;

}
