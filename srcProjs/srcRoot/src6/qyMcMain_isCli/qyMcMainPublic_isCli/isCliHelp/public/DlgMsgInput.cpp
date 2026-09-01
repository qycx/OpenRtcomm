// DlgMsgInput.cpp : implementation file
//

#include "stdafx.h"

#define  __noDbg_new__

#include	<windowsx.h>
#include	<math.h>
#include	"qymcMainCommon.h"
#include	"myresource.h"
//
#include	"ctxQmc.h"


#include "DlgMsgInput.h"
#include "afxdialogex.h"

#include	"funcsforisCliHelp.h"

#include	"dlgtalkproc.h"



//
__declspec(  dllexport  )  int  viewDlgMsgInput_talk(  HWND  hParent,  HWND  hCurTalk,  HWND  *  phWnd_msgInput  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	CDlgMsgInput			*		pDlg					=	NULL;
	RECT							rect;

	//
	pDlg  =  new  CDlgMsgInput(  CWnd::FromHandle(  hParent  )  );
	if  (  !pDlg  )  goto  errLabel;

	if  (  !pDlg->bSetInfo(    )  )  goto  errLabel;
	pDlg->m_var.hDlgTalk  =  hCurTalk;
	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	//  
	pDlg->ShowWindow(  SW_SHOW  );


	//
	if  (  phWnd_msgInput  )  *phWnd_msgInput  =  pDlg->m_hWnd;


	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}



	return  iErr;
}


//
__declspec(  dllexport  )  BOOL  setMsgInputPos(  HWND  hWnd_msgInput,  int  iX_screen,  int  iY_screen,  int  iW,  int  iH  )
{
	BOOL			bRet							=	FALSE;

	
	if  (  !IsWindow(  hWnd_msgInput  )  )  return  FALSE;

	RECT	rc;
#if  0
	rc  =  pCurTalkerVar->msgTool.rc;
	MapWindowPoints(  hCurTalker,  NULL,  (  LPPOINT  )&rc,  2  );
#endif
	//
	SetRect(  &rc,  iX_screen,  iY_screen,  iX_screen  +  iW,  iY_screen  +  iH  );

	//
	//  MoveWindow(  pCurTalkerVar->msgTool.hWnd_msgTool,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  TRUE  );
	UINT  uFlags;
	uFlags  =  SWP_SHOWWINDOW;
	SetWindowPos(  hWnd_msgInput,  NULL,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  uFlags  );

	 bRet  =  TRUE;
	 return  bRet;
}





// CDlgMsgInput dialog

IMPLEMENT_DYNAMIC(CDlgMsgInput, CDialogEx)

CDlgMsgInput::CDlgMsgInput(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMsgInput::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

	//
	//
	m_var.m_hParent = pParent->m_hWnd;
	m_var.m_nID = CDlgMsgInput::IDD;


	//  2012/05/18
	m_var.guiData.iIDC_EDIT_input  =  IDC_EDIT_input;

}

CDlgMsgInput::~CDlgMsgInput()
{
}



	
BOOL  CDlgMsgInput::bSetInfo(  )
{

	return  TRUE;
}

	BOOL CDlgMsgInput::Create(const RECT& rect)
	{

	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProc		=	NULL;

	/*
	if  (  !m_var.bInfoSet  )  {
		traceLogA(  "CDlgTalk::Create(  ): ÔÚ´´½¨¶Ô»°¿òÖ®Ç°Ó¦ÏÈÉèÖÃ³õÊ¼Êý¾Ý"  );
		return  FALSE;
	}
	*/

	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  FALSE;
	

	//
	if  (  !CDialog::Create(  this->m_var.m_nID, CWnd::FromHandle(  m_var.m_hParent  )  )  )  goto  errLabel;

	//
	m_var.guiData.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}




BOOL  CDlgMsgInput::bQuitDlg(  )		
{		
	traceLogA(  "CDlgVideoTagCfg(  )::bQuitDlg enters"  );

	M_syncFlg_bQuitDlg_start(  &m_var.syncFlgs.bInSequence,  m_hWnd,  _T(  "CDlgVideoTagCfg::bQuitDlg failed, bLocked already."  )  );

#if  0
	{
		CQySyncFlg	syncFlg;
		if  (  syncFlg.sync(  &m_var.syncFlgs.bInSequence  )  )  goto  errLabel;
	}
#endif


	//  2009/05/01
	DestroyWindow();				  
		
errLabel:

	M_syncFlg_bQuitDlg_end

	traceLogA(  "CDlgVideoTagCfg(  )::bQuitDlg leaves"  );

	return  TRUE;
}


//
void CDlgMsgInput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMsgInput, CDialogEx)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


//
int  sizeAllControls_dlgMsgInput(  HWND  hDlg,  DLG_msgInput_var  &  m_var  )
{
	 int			iErr							=	-1;
	 HDWP			hDwp;
	 RECT			rc;
	 //
	 int			iEdge_l							=	CONST_edge_l_dlgTalk_wall;
	 int			iEdge_t							=	CONST_edge_l_dlgTalk_wall;
	 int			iEdge_r							=	CONST_edge_l_dlgTalk_wall;
	 int			iEdge_b							=	CONST_edge_l_dlgTalk_wall;
	 //
	 int			iX_spacing						=	CONST_iX_spacing_dlgTalk_wall;			//  
	 int			iY_spacing						=	CONST_iY_spacing_dlgTalk_wall;			//  
	 
	 //
	 int			iW_input						=	10;
	 int			iH_input						=	48;			//  24; 因为超过1行时出现的滑动条会占用这个空间,必须多留1行才可以容纳滑动条
	 
	 //
	 int			x, y;
	 int			iW,  iH;
	 int			idc;
	 HWND			hCtrl;

	 //
	 ::GetClientRect(  hDlg,  &rc  );

	 //
	 iW_input  =  rc.right  -  rc.left;
	 iH_input  =  rc.bottom  -  rc.top;

	 //
	 hDwp  =  M_BeginDeferWindowPos(  1  );
	 if  (  hDwp  )  {		 
		 			   
		 x  =  0;		 		 
		 y  =  0;		//  +  iH_dlgDesc;		 		 
		 //
		 idc  =  IDC_EDIT_input;
		 iW  =  iW_input;  iH  =  iH_input;
		 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_SHOWWINDOW  );

		 //
		 M_EndDeferWindowPos(  hDwp  );


	 }



	 iErr  =  0;


	 return  iErr;

}



// CDlgMsgInput message handlers

BOOL CDlgMsgInput::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	//
	sizeAllControls_dlgMsgInput(  m_hWnd,  m_var  );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgMsgInput::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	sizeAllControls_dlgMsgInput(  m_hWnd,  m_var  );

}


void CDlgMsgInput::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


void CDlgMsgInput::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::PostNcDestroy();

	//
	//
	delete  this;

}


void CDlgMsgInput::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	int  i;
	i  =  0;
	//
	TCHAR  tBuf[256]  =  _T(  ""  );
	GetDlgItemText(  IDC_EDIT_input,  tBuf,  mycountof(  tBuf  )  );
	//
	procTalkTo(  m_var.hDlgTalk,  CONST_qyWndContentType_talker,  tBuf  );
	//
	SetDlgItemText(  IDC_EDIT_input,  _T(  ""  )  );

	//CDialogEx::OnOK();
}


void CDlgMsgInput::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	int  i;
	i  =  0;

	//CDialogEx::OnCancel();
}


void CDlgMsgInput::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	bQuitDlg(  );

	//CDialogEx::OnClose();
}
