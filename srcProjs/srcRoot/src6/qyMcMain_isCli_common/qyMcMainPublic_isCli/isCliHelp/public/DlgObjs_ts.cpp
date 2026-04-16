// DlgObjs_ts.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qyMc_touchscreen.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"

#include	"DlgObjs_ts.h"
#include	"tmpCeLib.h"


int  dlgLayout_objs(  HWND  hDlg,  DLG_guiData_objs  *  p  );
int  sizeAllControls_dlgObjs(  HWND  hDlg,  DLG_guiData_objs  *  p  );

// CDlgObjs_ts dialog

IMPLEMENT_DYNAMIC(CDlgObjs_ts, CDialog)

CDlgObjs_ts::CDlgObjs_ts(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgObjs_ts::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	//  2016/08/10
	if  (  pParent  )  m_var.m_hParent  =  pParent->m_hWnd;

}

CDlgObjs_ts::~CDlgObjs_ts()
{
	if  (  m_var.pData_items  )  free(  m_var.pData_items  );
	MACRO_safeFree(  m_var.pData  );	//  2014/05/13  
}


#if  0
  void  CDlgObjs_ts::endFullScreen(  )
{
	if  (  m_var.m_bFullScreen  )  {
		m_var.m_bFullScreen  =  FALSE;
		ShowWindow(  SW_HIDE  );
		memcpy(  &m_var.layoutParam,  &m_var.m_oldLayoutParam,  sizeof(  m_var.layoutParam  )  );
		mySetWindowPlacement(  this->GetSafeHwnd(  ),  &m_var.m_oldWndPlacement  );
		ShowWindow(  SW_RESTORE  );				
	}

	return;
}
#endif

void CDlgObjs_ts::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgObjs_ts, CDialog)
#if  0  //  ndef  __DEBUG__
	ON_BN_CLICKED(IDC_BUTTON_contact, &CDlgObjs_ts::OnBnClickedButtoncontact)
	ON_BN_CLICKED(IDC_BUTTON_group, &CDlgObjs_ts::OnBnClickedButtongroup)
	ON_BN_CLICKED(IDC_BUTTON_status, &CDlgObjs_ts::OnBnClickedButtonstatus)
#endif
	ON_BN_CLICKED(IDCANCEL, &CDlgObjs_ts::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDlgObjs_ts::OnBnClickedOk)
	ON_WM_SIZE()
	ON_WM_MOVING()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND_RANGE(  ID_MENU_isCmd_min,  ID_MENU_isCmd_max,  OnIsCmd  )
	ON_UPDATE_COMMAND_UI_RANGE(  ID_MENU_isCmd_min,  ID_MENU_isCmd_max,  OnUpdateIsCmd  )
	ON_LBN_SELCHANGE(IDC_LIST0, &CDlgObjs_ts::OnLbnSelchangeList0)
END_MESSAGE_MAP()


// CDlgObjs_ts message handlers

BOOL CDlgObjs_ts::OnInitDialog()
{
	int		iErr	=	-1;

	#ifdef  __APP_qyMc_touchscreen__
			//  2011/03/12
			makeDlgResizable(  this->m_hWnd  );
	#endif

	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	#ifdef  __APP_qyMc_touchscreen__
			::SetWindowPos(  m_hWnd,  HWND_TOPMOST,  0,  0,  0,  0,  SWP_NOMOVE  |  SWP_NOSIZE  );
	#endif

	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	HWND	hDlg  =  this->m_hWnd;
	dlgLayout_objs(  hDlg,  &m_var.guiData  );

	if  (  setModalWnd(  pQyMc,  hDlg  )  )  goto  errLabel;


	//  HWND	hDlg	=	this->m_hWnd;
#ifdef  __APP_qyMc_touchscreen__
	{
		RECT	rc;
		int		w, h;
		HWND	hFrame	=	pQyMc->gui.hMainWnd;
		if  (  !hFrame  )  goto  errLabel;
		::GetWindowRect(  hFrame,  &rc  );
		w  =  rc.right  -  rc.left;
		h  =  rc.bottom  -  rc.top;
		::MoveWindow(  hDlg,  rc.left,  rc.top,  w,  h,  TRUE  );
		
	}
#else
#if  10
	{
		RECT	rc;
		int		w, h;
		int		x;
		::GetWindowRect(  m_hWnd,  &rc  );
		x  =  rc.left;
		w  =  rc.right  -  rc.left;
		h  =  rc.bottom  -  rc.top;
#if  10
		if  (  w  <  640  )  {
			x  =  rc.left;	//    -  (  640  -  w  )  /  2;
			w  =  640;
		}
		if  (  h  <  480  )  {
			h  =  480;
		}
#endif
		::MoveWindow(  hDlg,  x,  rc.top,  w,  h,  TRUE  );
	}
#endif
#endif
	
	//  sizeAllControls_dlgObjs(  hDlg,  &m_var.guiData  );

	//  SetWindowText(  _T(  "Select"  )  );
	cusDlgRes(  0,  &pQyMc->cusRes,  hDlg,  IDD_objs  );

	m_var.guiData.bInited  =  TRUE;


	// TODO:  Add extra initialization here
	DLG_guiData_objs  *  pGuiData  =  &m_var.guiData;
	if  (  !dlgObjs_bFillContent(  hDlg,  &m_var,  pGuiData->param.uiType  )  )  goto  errLabel;

	iErr  =  0;

errLabel:

	if  (  !m_var.guiData.bInited  ||  iErr  )  {
		//  EndDialog(  -1  );
		PostMessage(  WM_CLOSE  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgObjs_ts::OnBnClickedButtoncontact()
{
	// TODO: Add your control notification handler code here
	HWND	hDlg  =  this->m_hWnd;
	dlgObjs_bFillContent(  hDlg,  &m_var,  CONST_objType_messenger  );
}

void CDlgObjs_ts::OnBnClickedButtongroup()
{
	// TODO: Add your control notification handler code here
	HWND	hDlg  =  this->m_hWnd;
	dlgObjs_bFillContent(  hDlg,  &m_var,  CONST_objType_imGrp  );
}

void CDlgObjs_ts::OnBnClickedButtonstatus()
{
	// TODO: Add your control notification handler code here
	HWND	hDlg  =  this->m_hWnd;
	dlgObjs_bFillContent(  hDlg,  &m_var,  0  );

}

void CDlgObjs_ts::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CDlgObjs_ts::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	HWND	hDlg  =  this->m_hWnd;

	if  (  dlgObjs_OnOK(  hDlg,  &m_var  )  )  return;

	OnOK();
}

void CDlgObjs_ts::OnMoving(UINT fwSide, LPRECT pRect)
{
	CDialog::OnMoving(fwSide, pRect);

	// TODO: Add your message handler code here
	sizeAllControls_dlgObjs(  this->m_hWnd,  &m_var.guiData  );

}


void CDlgObjs_ts::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	sizeAllControls_dlgObjs(  this->m_hWnd,  &m_var.guiData  );

}

#if  0
 void CDlgObjs_ts::Onfullscreen()
 {
	 // TODO: Add your command handler code here
	 if  (  m_var.m_bFullScreen  )  return;

	 myGetWindowPlacement(  this->GetSafeHwnd(  ),  &m_var.m_oldWndPlacement  );
	 memcpy(  &m_var.m_oldLayoutParam,  &m_var.layoutParam,  sizeof(  m_var.m_oldLayoutParam  )  );
	 memset(  &m_var.layoutParam,  0,  sizeof(  m_var.layoutParam  )  );
	 //
	 CRect	wndRect;
	 GetWindowRect(  &wndRect  );
	 CRect	clientRect;
	 RepositionBars(  0,  0xffff,  AFX_IDW_PANE_FIRST,  reposQuery,  &clientRect  );
	 ClientToScreen(  &clientRect  );
	 //
	 int  nFullWidth  =  GetSystemMetrics(  SM_CXSCREEN  );
	 int  nFullHeight  =  GetSystemMetrics(  SM_CYSCREEN  );
	 m_var.m_fullScreenRect.left  =  wndRect.left  -  clientRect.left;
	 m_var.m_fullScreenRect.top  =  wndRect.top  -  clientRect.top;
	 m_var.m_fullScreenRect.right  =  wndRect.right  -  clientRect.right  +  nFullWidth;
	 m_var.m_fullScreenRect.bottom  =  wndRect.bottom  -  clientRect.bottom  +  nFullHeight;
	 //
	 m_var.m_bFullScreen  =  TRUE;
	 //
	 WINDOWPLACEMENT	wndPl;
	 wndPl.length  =  sizeof(  WINDOWPLACEMENT  );
	 wndPl.flags  =  0;
	 wndPl.showCmd  =  SW_SHOWNORMAL;
	 wndPl.rcNormalPosition  =  m_var.m_fullScreenRect;
	 mySetWindowPlacement(  this->GetSafeHwnd(  ),  &wndPl  ); 

}
#endif

 BOOL CDlgObjs_ts::PreTranslateMessage(MSG* pMsg)
 {
	 // TODO: Add your specialized code here and/or call the base class
#if  0
	 switch  (  pMsg->message  )  {
			 case  WM_KEYDOWN:  {
				   UINT	nChar  =  pMsg->wParam;
				   if  (  nChar  ==  VK_ESCAPE  )  {
					   if  (  m_var.m_bFullScreen  )  {
						   endFullScreen(  );
						   return  TRUE;
					   }
				   }
				   }
				   break;
			 default:
					break;
	 }
#endif

	 return CDialog::PreTranslateMessage(pMsg);
 }

 void CDlgObjs_ts::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
 {
	 // TODO: Add your message handler code here and/or call default
#if  0
	 if  (  m_var.m_bFullScreen  )  {
		 lpMMI->ptMaxSize.x  =  m_var.m_fullScreenRect.right  -  m_var.m_fullScreenRect.left;
		 lpMMI->ptMaxSize.y  =  m_var.m_fullScreenRect.bottom  -  m_var.m_fullScreenRect.top;

		 lpMMI->ptMaxPosition.x  =  m_var.m_fullScreenRect.right  -  m_var.m_fullScreenRect.left;
		 lpMMI->ptMaxPosition.y  =  m_var.m_fullScreenRect.bottom  -  m_var.m_fullScreenRect.top;

		 lpMMI->ptMaxTrackSize.x  =  m_var.m_fullScreenRect.right  -  m_var.m_fullScreenRect.left;
		 lpMMI->ptMaxTrackSize.y  =  m_var.m_fullScreenRect.bottom  -  m_var.m_fullScreenRect.top;
	 }
#endif

#ifndef  __WINCE__
	 CDialog::OnGetMinMaxInfo(lpMMI);
#endif

 }
void CDlgObjs_ts::OnIsCmd(  UINT nID  )
{
	switch  (  nID  )  {
			case  ID_fullScreen:
				  //  if  (  m_var.m_bFullScreen  )  this->endFullScreen(  );
				  //  else  this->Onfullscreen(  );
				  break;
			default:
					break;
	}
}


void CDlgObjs_ts::OnUpdateIsCmd(CCmdUI *pCmdUI)
{

}

void CDlgObjs_ts::OnLbnSelchangeList0()
{
	// TODO: Add your control notification handler code here
	dlgObjs_OnLbnSelchangeList0(  this->m_hWnd,  &m_var  );

}
