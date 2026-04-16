// DlgQyMenu.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"


#include	"qyCusResPublic.h"
#include	"qyOpenShellCommon.h"
#include	"qmOpenCommon.h"
//  #include	"qmShell_open.h"

#include	"tmpCeLib.h"

#include	"DlgWalls.h"

//  #include	"DlgMenuIsCli.h"
#include	"myresource.h"

#include	"qyCusResTemp.h"

//  #include	"DlgPolicyIsClient.h"
//  #include	"DlgCfgVideoConference.h"


#include	"wallTalkers.h"

#include	"DlgQyMenu.h"
#include	"qmcVWall.h"
#include	"funcsForIsCliHelp.h"
#include	"qmcCommFunc_isCli.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//  #ifdef  __APP_qyMc__

 __declspec(  dllexport  )  int  viewWallsMenu(  int  xPos_screen,  int  yPos_screen,  HWND  hDlgWalls,  int  iWndContentType,  BOOL  bNoDelayToView,  RECT  *  pRect_zone,  void  *  pVwRuleU  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	int								iErr					=	-1;
	QY_MC					*		pQyMc					=	QY_GET_GBUF(  );
	MC_VAR_isCli			*		pProcInfo				=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	VW_ruleU				*		pRule					=	(  VW_ruleU  *  )pVwRuleU;

	//		
	if  (  bApp_ts(  pQyMc  )  )  return  -1;


	//
	if  (  !pRect_zone  ||  !pRule  )  return  -1;

	//
	if  (  pProcInfo->g_hVWall  !=  hDlgWalls  )  return  -1;

	ZONE_objs_info	*	pVar	=	(  ZONE_objs_info  *  )pFuncs->pf_getZoneObjsInfo(  pProcInfo,  hDlgWalls,  iWndContentType,  0  );
	if  (  !pVar  )  return  -1;
	ZONE_objs_info	&	m_var	=	*pVar;

	//
	m_var.dwTickCnt_lastMouseMove  =  GetTickCount(  );


	CDlgQyMenu				*		pDlg					=	NULL;
	int								iIDD					=	-1;
	int								iStatus_ia				=	0;
	BOOL							bMin					=	FALSE;

	//  traceLogA(  "viewInstantAssistant enters"  );

#ifdef  __DEBUG__
		int  i  =  sizeof(  int  );
		//  traceLog(  _T(  "viewIa, xPos %d, yPos %d"  ),  xPos,  yPos  );
#endif



	if  (  !bNoDelayToView  )  {	
		if  (  xPos_screen  ==  m_var.param_viewMenu.xPos_screen  &&  yPos_screen  ==  m_var.param_viewMenu.yPos_screen  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "viewInstantAssistant: mouse pos has not changed, skipped"  )  );
			#endif
			iErr  =  0;  goto  errLabel;
		}
		//  2011/03/26. 这里的防delay似乎没意义，原来是担心在窗口关闭后，又莫名其妙的被触发了一个mousemove事件，现在看来，是xPos_screen, yPos_screen没有过滤造成的。
		//  
#if 0
		if  (  GetTickCount(  )  -  sdwTickCnt_close_instantAssistant  <  pQyMc->cfg.usDelayInMsToViewToolbar  )  {
			iErr  =  0;  goto  errLabel;
		}
#endif
	}
	m_var.param_viewMenu.xPos_screen  =  xPos_screen;
	m_var.param_viewMenu.yPos_screen  =  yPos_screen;

	//
	//  viewWallsBar(  xPos_screen,  yPos_screen,  pProcInfo->g_hVWall,  bNoDelayToView  );

#if  1
	#ifdef  __DEBUG__
			//  traceLog(  _T(  "viewWallsMenu: not supported now"  )  );
	#endif
	goto  errLabel;
#endif

	//
	if  (  IsWindow(  m_var.hMenu  )  )  {
		if  (  !memcmp(  &m_var.param_viewMenu.rc_zone,  pRect_zone,  sizeof(  RECT  )  )  )  {
			iErr  =  0;  goto  errLabel;
		}
		SendMessage(  m_var.hMenu,  WM_CLOSE,  0,  0  );
	}
	m_var.hMenu  =  NULL;

	//  2012/04/07
	m_var.param_viewMenu.rc_zone  =  *pRect_zone;

	//
	//  2011/03/04. 这是为了只有一个功能窗口
	if  (  IsWindow(  pQyMc->gui.hWnd_popupTool  )  )  {	
		SendMessage(  pQyMc->gui.hWnd_popupTool,  WM_CLOSE,  0,  0  );
	}

	switch  (  pRule->common.uiType  )  {
			case  CONST_vwRuleType_dynBmp:
				  break;
			default:
					//  其他的都不显示菜单					
					#ifdef  __DEBUG__
							traceLog(  _T(  "showWallsMenu: no menu for the rule"  )  );
					#endif
					goto  errLabel;
	}

		 //  2010/12/18
		 HWND	hFore	=	GetForegroundWindow(  );
		 HWND	hAbove  =	NULL;	//  findWndAbove(  hParent  );

		 //
		 RECT							rect;

		 HWND	hParent  =  hDlgWalls;
		 pDlg  =  new  CDlgQyMenu(  hParent  );
		 if  (  !pDlg  )  goto  errLabel;
#if  0
		 //
		 pDlg->m_var.guiData.param.hDlgTalk  =  hDlgTalk;
		 //
		 pDlg->m_var.guiData.param.iIDD  =  iIDD;
		 pDlg->m_var.guiData.param.iStatus  =  iStatus_ia;		//  2012/04/04
		 pDlg->m_var.guiData.param.bMin  =  bMin;
		 //
		 pDlg->m_var.guiData.param.xPos_screen  =  xPos_screen;
		 pDlg->m_var.guiData.param.yPos_screen  =  yPos_screen;

		 pDlg->m_var.guiData.iIDC_request  =  IDC_request;
		 pDlg->m_var.guiData.iIDC_talkerList  =  IDC_talkerList;
		 pDlg->m_var.guiData.iIDC_BUTTON_msgBox  =  IDC_BUTTON_msgBox;
		 pDlg->m_var.guiData.iIDC_COMBO_usLayoutType  =  IDC_COMBO_usLayoutType;
		 pDlg->m_var.guiData.iIDC_STATIC_status  =  IDC_STATIC_status;
		 pDlg->m_var.guiData.iIDC_BUTTON_av  =  IDC_BUTTON_av;
		 pDlg->m_var.guiData.iIDC_BUTTON_shareScreen  =  IDC_BUTTON_shareScreen;
		 pDlg->m_var.guiData.iIDC_BUTTON_rule  =  IDC_BUTTON_rule;
		 pDlg->m_var.guiData.iIDC_BUTTON_close  =  IDC_BUTTON_close;
		 pDlg->m_var.guiData.iIDC_BUTTON_av_accept  =  IDC_BUTTON_av_accept;
		 pDlg->m_var.guiData.iIDC_BUTTON_av_deny  =  IDC_BUTTON_av_deny;
		 pDlg->m_var.guiData.iIDC_BUTTON_more  =  IDC_BUTTON_more;

#ifndef  __APP_qyMc_touchscreen__	//  2011/10/04
		 pDlg->m_var.guiData.iIDC_BUTTON_fullScreen  =  IDC_BUTTON_fullScreen;
#endif

		 pDlg->m_var.guiData.iIDC_BUTTON_msg  =  IDC_BUTTON_msg;
		 pDlg->m_var.guiData.iIDC_BUTTON_nonexclusive  =  IDC_BUTTON_nonexclusive;
		 pDlg->m_var.guiData.iIDC_BUTTON_shareMediaFile  =  IDC_BUTTON_shareMediaFile;
#endif

		 //  pDlg->m_var.guiData.

		 if  (  !pDlg->Create(  rect  )  )  goto  errLabel;

		 //
		 setWallsMenuPos(  hDlgWalls,  pDlg->m_hWnd,  pRect_zone  );

		 //	ShowWindow(  pDlg->m_hWnd,  SW_SHOW  );
		 // 
		 #ifdef  __APP_qyMc_touchscreen__
				 //  traceLog(  _T(  "before AnimateWindow"  )  );
				 DWORD  dwTimeInMs  =  300;
				 DWORD	dwFlags  =  AW_SLIDE  |  AW_VER_NEGATIVE;
				 if  (  !AnimateWindow(  pDlg->m_hWnd,  dwTimeInMs,  dwFlags  )  )  {		
					 traceLog(  _T(  "AnimateWindow failed"  )  );
				 }
				 //  traceLog(  _T(  "after AnimateWindow"  )  );
		 #endif
			
		 int  flg  =  SWP_NOMOVE  |  SWP_NOSIZE  |  SWP_NOACTIVATE  |  SWP_SHOWWINDOW;
		 SetWindowPos(  pDlg->m_hWnd,  hAbove,  0,  0,  0,  0,  flg  );
		 //
		 #ifndef  __APP_qyMc_touchscreen__
				  if  (  IsWindow(  hFore  )  )  SetForegroundWindow(  hFore  );
		 #endif


	 //
	 pDlg->m_var.dwTickCnt_lastMouseMove  =  GetTickCount(  );

	//  
	m_var.hMenu  =  pDlg->m_hWnd;
	pQyMc->gui.hWnd_popupTool  =  pDlg->m_hWnd;		//  2011/03/04

	
	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}
	if  (  !iErr  )  {
	}

	//  traceLogA(  "viewInstantAssistant leaves, iErr is %d",  iErr  );

	return  iErr;
}


__declspec(  dllexport  )  int  setWallsMenuPos(  HWND  hDlgWalls,  HWND  hMenu,  RECT  *  pRect_zone  )
{
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	if  (  bApp_ts(  pQyMc  )  )  return  -1;

	if  (  !pRect_zone  )  return  -1;

	int  iX,  iY,  iW,  iH;

	RECT	rc;
	GetClientRect(  hMenu,  &rc  );

	iW  =  rc.right  -  rc.left;
	iH  =  rc.bottom  -  rc.top;
	iX  =  pRect_zone->right  -  iW;
	iY  =  pRect_zone->top;

	SetWindowPos(  hMenu,  0,  iX,  iY,  iW,  iH,  SWP_NOACTIVATE  );

	return  0;
}



//  #endif



// CDlgQyMenu dialog

IMPLEMENT_DYNAMIC(CDlgQyMenu, CDialog)

CDlgQyMenu::CDlgQyMenu(HWND hParent /*=NULL*/)
	: CDialog(CDlgQyMenu::IDD, CWnd::FromHandle(  hParent  ))
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.guiData.hParent  =  hParent;


}

CDlgQyMenu::~CDlgQyMenu()
{
}

 BOOL CDlgQyMenu::Create(const RECT& rect) 
{
	BOOL	bRet	=	FALSE;

	if  (  !CDialog::Create(  this->IDD,  CWnd::FromHandle(  m_var.guiData.hParent  )  )  )  goto  errLabel;

	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;

errLabel:

	return  bRet;
}

 BOOL  CDlgQyMenu::bQuitDlg(  )
{
	traceLogA(  "CDlgQyMenu(  )::bQuitDlg enters"  );


	//
	DestroyWindow(  );


	//
	traceLogA(  "CDlgQyMenu(  )::bQuitDlg leaves"  );

	return  TRUE;
}



void CDlgQyMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgQyMenu, CDialog)
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CDlgQyMenu message handlers

void CDlgQyMenu::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();

	if  (  m_var.bCreated  )  {
		traceLogA(  "CDlgQyMenu::PostNcDestroy, delete this"  );
		delete  this;
	}

}

BOOL CDlgQyMenu::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect			rcDialog;
	int				idc;
	HWND			hWnd;
	RECT			rc_btn;
	RECT			rc_cur;
	HDWP			hDwp;
	int				x,y,iW,iH,iX,iY;


	GetWindowRect(  &rcDialog  );
	m_var.oldLayout.iW_dlg  =  rcDialog.right  -  rcDialog.left;
	m_var.oldLayout.iH_dlg  =  rcDialog.bottom  -  rcDialog.top;

	idc  =  IDC_BUTTON_makeBigger;
	hWnd  =  GetDlgItem(  idc  )->m_hWnd;
	if  (  !hWnd  )  goto  errLabel;
	::GetWindowRect(  hWnd,  &rc_btn  );
	m_var.oldLayout.iEdge_t  =  rc_btn.top  -  rcDialog.top;
	m_var.oldLayout.iEdge_l  =  rc_btn.left  -  rcDialog.left;
	m_var.oldLayout.iW_btn  =  rc_btn.right  -  rc_btn.left;
	m_var.oldLayout.iH_btn  =  rc_btn.bottom  -  rc_btn.top;

	m_var.oldLayout.iH_dlg  =  m_var.oldLayout.iEdge_t
								+  m_var.oldLayout.iH_btn
								+  m_var.oldLayout.iY_spacing
								+  m_var.oldLayout.iEdge_t;
	m_var.oldLayout.iW_dlg  =  m_var.oldLayout.iEdge_l
								+  m_var.oldLayout.iW_btn
								+  m_var.oldLayout.iX_spacing
								+  m_var.oldLayout.iEdge_l;

	{
		::GetClientRect(  m_var.guiData.hParent,  &rc_cur  );
		::MapWindowPoints(  m_var.guiData.hParent,  NULL,  (  LPPOINT  )&rc_cur,  2  );
		//
		iX  =  rc_cur.right  -  m_var.oldLayout.iW_dlg;			//  2012/04/04
		iY  =  rc_cur.top;	//    +  40;
	}

	::MoveWindow(  this->m_hWnd,  iX,  iY,  m_var.oldLayout.iW_dlg,  m_var.oldLayout.iH_dlg,  TRUE  );

errLabel:
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgQyMenu::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//  CDialog::OnClose();
	bQuitDlg(  );
}

void CDlgQyMenu::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//  CDialog::OnCancel();
	bQuitDlg(  );
}

BOOL CDlgQyMenu::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnEraseBkgnd(pDC);

	CRect rect;
	GetClientRect(rect);

#if  10
	TRIVERTEX        vert[2] ;
	GRADIENT_RECT    gRect;
	vert [0] .x      = 0;
	vert [0] .y      = 0;
	vert [0] .Red    = 0x5100;
	vert [0] .Green  = 0xf500;
	vert [0] .Blue   = 0x0a00;
	vert [0] .Alpha  = 0x0000;

	vert [1] .x      = rect.right;
	vert [1] .y      = rect.bottom; 
	vert [1] .Red    = 0x0700;
	vert [1] .Green  = 0xf800;
	vert [1] .Blue   = 0xf100;
	vert [1] .Alpha  = 0x0000;

	gRect.UpperLeft  = 0;
	gRect.LowerRight = 1;
	GradientFill(  pDC->m_hDC,vert,2,&gRect,1,GRADIENT_FILL_RECT_H);
#endif

	return  TRUE;
}


void CDlgQyMenu::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnLButtonDown(nFlags, point);

	//send WM_NCLBUTTONDOWN information
	//then we can move the window
	PostMessage(WM_NCLBUTTONDOWN,
		HTCAPTION,
		MAKELPARAM(point.x,point.y));

}
