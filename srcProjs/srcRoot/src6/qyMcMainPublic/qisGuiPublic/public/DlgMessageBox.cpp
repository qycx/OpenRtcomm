// DlgMessageBox.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyCommon.h"
#include	"myresource.h"
#include	"DlgMessageBox.h"
#include	"afxdialogex.h"

//#include	"qyMcMainCommon.h"
#include	"qisGuiPublic_public.h"

#include	"qnmResDefs.h"

#include	"qyCusResTemp.h"
#include	"qyLangCommProc.h"


__declspec(  dllexport  )  int  WINAPI  qyMessageBox(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType,  UINT  nTimeoutInS,  BOOL  *  pbSyncFlg  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int				iRet	=	IDCANCEL;
	CDlgMessageBox	dlg(  CWnd::FromHandle(  hWnd  )  );

	if  (  pbSyncFlg  )  {
		if  (  *pbSyncFlg  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "qyMessageBox failed, syncFlg err"  )  );
			#endif				
			return  IDCANCEL;
		}
		*pbSyncFlg  =  TRUE;
	}

	//
	if  (  !nTimeoutInS  )  {
		nTimeoutInS  =  10;
	}
#ifdef  __DEBUG__
		//nTimeoutInS  =  30;
	DWORD tid = GetCurrentThreadId();
#endif

	dlg.bSetDlgInfo(  lpText,  lpCaption,  uType,  nTimeoutInS  );
	iRet  =  dlg.DoModal(  );

errLabel:

	if  (  pbSyncFlg  )  {
		*pbSyncFlg  =  FALSE;
	}
	return  iRet;
}


//
//__declspec(  dllexport  )  int  WINAPI  qyMessageBox_custom(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  LPCTSTR  txt_cancel_btn,  UINT uType,  UINT  nTimeoutInS,  BOOL  *  pbSyncFlg  )
__declspec(  dllexport  )  int  WINAPI  qyMessageBox_custom(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType,  UINT  nTimeoutInS,  BOOL  *  pbSyncFlg,  PARAM_qyMessengeBox  *  pParam  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int				iRet	=	IDCANCEL;
	CDlgMessageBox	dlg(  CWnd::FromHandle(  hWnd  )  );

	//
	if  (  !pParam  )  return  -1;

	//
	if  (  pbSyncFlg  )  {
		if  (  *pbSyncFlg  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "qyMessageBox failed, syncFlg err"  )  );
			#endif				
			return  IDCANCEL;
		}
		*pbSyncFlg  =  TRUE;
	}

	//
	nTimeoutInS  =  10;
#ifdef  __DEBUG__
		nTimeoutInS  =  30;
#endif

	dlg.bSetDlgInfo(  lpText,  lpCaption,  uType,  nTimeoutInS  );
	dlg.m_var.m_b_willReturn_qyId  =  TRUE;
	//safeTcsnCpy(  txt_cancel_btn,  dlg.m_var.txt_cancel_btn,  mycountof(  dlg.m_var.txt_cancel_btn  )  );

	//
	dlg.m_var.m_bShow_noPrompt  =  pParam->bShow_noPrompt;

	//
	iRet  =  dlg.DoModal(  );

	//
	pParam->bCheck_noPropmt  =  dlg.m_var.m_b_check_noPrompt;


errLabel:

	if  (  pbSyncFlg  )  {
		*pbSyncFlg  =  FALSE;
	}
	return  iRet;
}


// CDlgMessageBox dialog

IMPLEMENT_DYNAMIC(CDlgMessageBox, CDialog)

CDlgMessageBox::CDlgMessageBox(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMessageBox::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgMessageBox::~CDlgMessageBox()
{
}


BOOL  CDlgMessageBox::bSetDlgInfo(  LPCTSTR  lpText,  LPCTSTR  lpCaption,  UINT  uType,  UINT  nTimeoutInS  )		
{
	BOOL	bRet	=	FALSE;

	if  (  !nTimeoutInS  ||  nTimeoutInS  >  30  )  nTimeoutInS  =  30;

	safeTcsnCpy(  lpText,  m_var.hint,  mycountof(  m_var.hint  )  );
	safeTcsnCpy(  lpCaption,  m_var.title,  mycountof(  m_var.title  )  );
	m_var.uType  =  uType;
	//
	m_var.nTimeoutInS  =  nTimeoutInS;


	bRet  =  TRUE;
errLabel:

	return  bRet;

}


BOOL  CDlgMessageBox::bQuitDlg(  int  nResult  )
{
	EndDialog(  nResult  );
	return  TRUE;
}


//
int  CDlgMessageBox::check(  )
{
	m_var.m_b_check_noPrompt  =  (  (  (  CButton  *  )GetDlgItem(  IDC_CHECK_noPrompt  )  )->GetCheck(  )  ==  BST_CHECKED  );
	
	return  0;
}


void CDlgMessageBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMessageBox, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_ok, &CDlgMessageBox::OnBnClickedButtonok)
	ON_BN_CLICKED(IDC_BUTTON_no, &CDlgMessageBox::OnBnClickedButtonno)
	ON_BN_CLICKED(IDC_BUTTON_cancel, &CDlgMessageBox::OnBnClickedButtoncancel)
END_MESSAGE_MAP()


// CDlgMessageBox message handlers

int  sizeAllControls_1(  CDlgMessageBox  *  pDlg,  int  idc  )
{
	RECT	rc;
	pDlg->GetClientRect(  &rc  );
	//  GetWindowRect(  pDlg->m_hWnd,  &rc  );
	RECT  rc_ctrl;
	HWND	hCtrl  =  GetDlgItem(  pDlg->m_hWnd,  idc  );  
	GetWindowRect(  hCtrl,  &rc_ctrl  );
	MapWindowPoints(  NULL,  pDlg->m_hWnd,  (  LPPOINT  )&rc_ctrl,  2  );

	int  l_edge,  t_edge;
	l_edge  =  (  rc.right  -  rc.left  -  (  rc_ctrl.right  -  rc_ctrl.left   )  )  /  2;
	//t_edge  =  (  rc.bottom  -  rc.top  -  (  rc_ctrl.bottom  -  rc_ctrl.top  )   )  /  2;
	t_edge  =  rc_ctrl.top  -  rc.top;


	MoveWindow(  hCtrl,  l_edge,  t_edge,  (  rc_ctrl.right  -  rc_ctrl.left  ),  (  rc_ctrl.bottom  -  rc_ctrl.top  ),  FALSE  );

	return  0;
}

int  sizeAllControls_2(  CDlgMessageBox  *  pDlg,  int  idc0,  int  idc1  )
{
	RECT	rc;
	pDlg->GetClientRect(  &rc  );
	//  GetWindowRect(  pDlg->m_hWnd,  &rc  );
	RECT  rc_ctrl;
	HWND	hCtrl0  =  GetDlgItem(  pDlg->m_hWnd,  idc0  );  
	HWND	hCtrl1  =  GetDlgItem(  pDlg->m_hWnd,  idc1  );
	int		iW_ctrl  =  0;
	int		iH_ctrl  =  0;

	GetWindowRect(  hCtrl0,  &rc_ctrl  );
	MapWindowPoints(  NULL,  pDlg->m_hWnd,  (  LPPOINT  )&rc_ctrl,  2  );
	iW_ctrl  =  rc_ctrl.right  -  rc_ctrl.left;

	int  l_edge,  t_edge;
	l_edge  =  (  rc.right  -  rc.left  -  2  *  iW_ctrl  )  /  3;
	t_edge  =  rc_ctrl.top  -  rc.top;


	MoveWindow(  hCtrl0,  l_edge,  t_edge,  (  rc_ctrl.right  -  rc_ctrl.left  ),  (  rc_ctrl.bottom  -  rc_ctrl.top  ),  FALSE  );
	MoveWindow(  hCtrl1,  l_edge  +  iW_ctrl  +  l_edge,  t_edge,  (  rc_ctrl.right  -  rc_ctrl.left  ),  (  rc_ctrl.bottom  -  rc_ctrl.top  ),  FALSE  );


	return  0;
}


BOOL CDlgMessageBox::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int  iErr  =  -1;
	//QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	QNM_CUSRES_INFO  *  pCusRes  =  get_cur_pQnmCusResInfo(  );
	if  (  !pCusRes  )  goto  errLabel;
	cusDlgRes(  0,  pCusRes,  this->m_hWnd,  this->IDD  );

	switch  (  m_var.uType  &  0xff  )  {
			case  MB_YESNOCANCEL:
				  SetDlgItemText(  IDC_BUTTON_ok,  getResStr(  0,  pCusRes,  CONST_resId_y  )  ); 
				  SetDlgItemText(  IDC_BUTTON_no,  getResStr(  0,  pCusRes,  CONST_resId_n  )  ); 
				  SetDlgItemText(  IDC_BUTTON_cancel,  getResStr(  0,  pCusRes,  CONST_resId_cancel  )  ); 
				  //
				  if  (  m_var.m_b_willReturn_qyId  )  {
					  SetDlgItemText(  IDC_BUTTON_cancel,  m_var.txt_cancel_btn  ); 
				  }
				  break;
			case  MB_YESNO:
				  SetDlgItemText(  IDOK,  getResStr(  0,  pCusRes,  CONST_resId_y  )  ); 
				  SetDlgItemText(  IDC_BUTTON_no,  getResStr(  0,  pCusRes,  CONST_resId_n  )  ); 
				  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_cancel  ),  SW_HIDE  );
				  //
				  sizeAllControls_2(  this,  IDC_BUTTON_ok,  IDC_BUTTON_no  );
				  //
				  GetDlgItem(  IDC_BUTTON_no  )->SetFocus(  );
				  break;
			case  MB_OKCANCEL:
				  SetDlgItemText(  IDC_BUTTON_ok,  getResStr(  0,  pCusRes,  CONST_resId_ok  )  ); 
				  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_no  ),  SW_HIDE  );
				  SetDlgItemText(  IDC_BUTTON_cancel,  getResStr(  0,  pCusRes,  CONST_resId_cancel  )  ); 
				  //
				  sizeAllControls_2(  this,  IDC_BUTTON_ok,  IDC_BUTTON_cancel  );
				  break;
			default:
				  SetDlgItemText(  IDC_BUTTON_ok,  getResStr(  0,  pCusRes,  CONST_resId_ok  )  ); 
				  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_no  ),  SW_HIDE  );
				  ::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_cancel  ),  SW_HIDE  );
				  //
				  sizeAllControls_1(  this,  IDC_BUTTON_ok  );
				  break;
	}

	switch  (  m_var.uType  &  0xf00  )  {
			case  MB_DEFBUTTON2:
				  if  (  ::IsWindowVisible(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_no  )  )  )  ::SetFocus(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_no  )  );
				  else  ::SetFocus(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_cancel  )  );
				  break;
			case  MB_DEFBUTTON3:
				  ::SetFocus(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_cancel  )  );
				  break;
			case  MB_DEFBUTTON1:
			default:
					break;
	}

	//
	TCHAR	tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s...Auto canceled  after %d seconds.."  ),  m_var.title,  m_var.nTimeoutInS  -  m_var.uProgress  );
	SetWindowText(  tBuf  );

	SetDlgItemText(  IDC_STATIC_hint,  m_var.hint  );


	//
	SetDlgItemText(  IDC_CHECK_noPrompt,  getResStr(  0,  pCusRes,  CONST_resId_noPrompt  )  );
	

	//  2017/07/17
	::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_CHECK_noPrompt  ),  m_var.m_bShow_noPrompt  ?  SW_SHOW  :  SW_HIDE  );  

	//
	m_var.uiTimerId  =  SetTimer(  1,  1000,  NULL  );

	//
	iErr  =  0;

errLabel:

	//  2015/07/01
	if  (  iErr  )  {
		PostMessage(  WM_CLOSE  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgMessageBox::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	m_var.uProgress  ++  ;

	if  (  m_var.uProgress  >=  m_var.nTimeoutInS  )  {
		bQuitDlg(  IDCANCEL  );
		return;
	}

	TCHAR	tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s...Auto canceled  after %d seconds.."  ),  m_var.title,  m_var.nTimeoutInS  -  m_var.uProgress  );
	SetWindowText(  tBuf  );


	CDialog::OnTimer(nIDEvent);
}


void CDlgMessageBox::OnBnClickedButtonok()
{
	//
	check(  );

	// TODO: Add your control notification handler code here
	if  (  m_var.m_b_willReturn_qyId  )  {
		bQuitDlg(  ID_qyOk  );
		return;
	}
	//
	switch  (  m_var.uType  &  0xff  )  {
			case  MB_YESNOCANCEL:
			case  MB_YESNO:
				  bQuitDlg(  IDYES  );
				  return;
				  break;
			default:
				  break;
	}

	CDialog::OnOK();
}



void CDlgMessageBox::OnBnClickedButtonno()
{
	//
	check(  );

	// TODO: Add your control notification handler code here
	if  (  m_var.m_b_willReturn_qyId  )  {
		bQuitDlg(  ID_qyNo  );
		return;
	}
	//
	bQuitDlg(  IDNO  );
}


void CDlgMessageBox::OnBnClickedButtoncancel()
{
	//
	check(  );

	// TODO: Add your control notification handler code here
	if  (  m_var.m_b_willReturn_qyId  )  {
		bQuitDlg(  ID_qyCancel  );
		return;
	}
	bQuitDlg(  IDCANCEL  );
}
