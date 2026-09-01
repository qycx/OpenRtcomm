// DlgToolboxSketchpad.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"
#include	"DlgToolboxSketchpad.h"

#include	"qmcVWall.h"
//#include	"DlgDynBmps.h"
#include	"dlgdynBmpsProc.h"

#include	"sp.h"
#include	"funcsForIsCliHelp.h"

#include	"ctxQmc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


 QY_DMITEM  CONST_idcBmpTable[]  =
 {
	 {	IDC_CHECK_select,		(  TCHAR  *  )IDB_select,		},	
	 {	IDC_CHECK_rectangle,	(  TCHAR  *  )IDB_rectangle,	},
	 //
	 {	IDC_CHECK_point,		(  TCHAR  *  )IDB_rectangle,	},
	 {	IDC_CHECK_segment,		(  TCHAR  *  )IDB_rectangle,	},
	 {	IDC_CHECK_circle,		(  TCHAR  *  )IDB_rectangle,	},


	 {	-1,				},
 };


//   int  viewToolbox_sketchpad(  void  *  pDlgParentParam  )
  __declspec(  dllexport  )  int  viewToolbox_sketchpad(  HWND  hDlgParent,  void  *  pDLG_dynBmps_var  )

{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int								iErr					=	-1;
	//  CDlgDynBmps				*		pDlgParent				=	(  CDlgDynBmps  *  )pDlgParentParam;
	DLG_dynBmps_var			*		pDlgParentVar			=	(  DLG_dynBmps_var  *  )pDLG_dynBmps_var;
	if  (  !pDlgParentVar  )  return  -1;
	QY_MC					*		pQyMc					=	QY_GET_GBUF(  );
	int								iServiceId				=	CONST_qyServiceId_mis;
	QY_SERVICEGUI_INFO		*		pSci					=	getServiceGuiInfo(  pQyMc,  iServiceId  );
	if  (  !pSci  )  return  -1;
	MC_VAR_isCli				*		pProcInfo				=	(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;

	CDlgToolboxSketchPad	*		pDlg					=	NULL;
	RECT							rect;

	traceLogA(  "viewToolbox_sketchpad enters"  );

	if  (  IsWindow(  pDlgParentVar->pWall->m_var.hWnd_spToolbox  )  )  {
		MACRO_SetForegroundWindow(  pDlgParentVar->pWall->m_var.hWnd_spToolbox  );
		iErr  =  0;  goto  errLabel;
	}
	
	pDlgParentVar->pWall->m_var.hWnd_spToolbox  =  NULL;

	pDlg  =  new  CDlgToolboxSketchPad(  hDlgParent  );
	if  (  !pDlg  )  goto  errLabel;

	//
	pDlg->m_var.m_pParentVar  =  pDlgParentVar;

	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;

	RECT  rect_parent;
	GetWindowRect(  hDlgParent,  &rect_parent  );
	GetWindowRect(  pDlg->m_hWnd,  &rect  );
	rect.left  =  rect_parent.right  -  (  rect.right  -  rect.left  );
	rect.right  =  rect_parent.right;
	MoveWindow(  pDlg->m_hWnd,  rect.left,  rect.top,  rect.right  -  rect.left,  rect.bottom  -  rect.top,  FALSE  );

	pDlg->ShowWindow(  SW_SHOW  );

	//  
	pDlgParentVar->pWall->m_var.hWnd_spToolbox  =  pDlg->m_hWnd;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}
	if  (  !iErr  )  {
	}

	traceLogA(  "viewToolbox_sketchpad leaves, iErr is %d",  iErr  );

	return  iErr;
}

// CDlgToolboxSketchPad dialog

IMPLEMENT_DYNAMIC(CDlgToolboxSketchPad, CDialog)

CDlgToolboxSketchPad::CDlgToolboxSketchPad(HWND  hParent /*=NULL*/)
: CDialog(CDlgToolboxSketchPad::IDD, CWnd::FromHandle(  hParent  ))
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.m_hParent  =  hParent;

}

CDlgToolboxSketchPad::~CDlgToolboxSketchPad()
{
}


BOOL CDlgToolboxSketchPad::Create(const RECT& rect)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;
	
	if  (  !m_var.m_hParent  )  goto  errLabel;

	if  (  !CDialog::Create(  this->IDD,  CWnd::FromHandle(  m_var.m_hParent  )  )  )  goto  errLabel;

	//
	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}

int	CDlgToolboxSketchPad::refreshBtns(  )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	int		idc  =  0;
	//  CDlgDynBmps	*	pParent	=	(  CDlgDynBmps  *  )m_var.m_pParent;
	DLG_dynBmps_var  *  pParentVar  =  (  DLG_dynBmps_var  *  )m_var.m_pParentVar;
	//  SP_STRUCT	&	gSp  =  *(  SP_STRUCT  *  )pParentVar->pWall->getCurSp(  );
	SP_STRUCT	&	gSp  =  *(  SP_STRUCT  *  )pFuncs->pf_vw_getCurSp(  pParentVar->pWall  );
	

	switch  (  gSp.sysStatus  )  {
			case  STATUS_SELECT:
				  idc  =  IDC_CHECK_select;
				  break;
			case  STATUS_CREATE_A_RECTANGLE:
				  idc  =  IDC_CHECK_rectangle;
				  break;
			case  STATUS_CREATE_A_POINT:
				  idc  =  IDC_CHECK_point;
				  break;
			case  STATUS_CREATE_A_SEGMENT:
				  idc  =  IDC_CHECK_segment;
				  break;
		    case  STATUS_CREATE_A_CIRCLE:
				  idc  =  IDC_CHECK_circle;
				  break;
			default:
					break;
	}
	QY_DMITEM	*	pItem;
	CWnd		*	pCtrl;
	for  (  pItem  =  CONST_idcBmpTable;  pItem->type  !=  -1;  pItem  ++  )  {
		 pCtrl  =  GetDlgItem(  pItem->type  );
		 if  (  !pCtrl  )  continue;
		 (  (  CButton  *  )pCtrl  )->SetCheck(  pItem->type  ==  idc  ?  BST_CHECKED  :  BST_UNCHECKED  );
	}


	return  0;
}


void CDlgToolboxSketchPad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgToolboxSketchPad, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK_select, &CDlgToolboxSketchPad::OnBnClickedCheckselect)
	ON_BN_CLICKED(IDC_CHECK_rectangle, &CDlgToolboxSketchPad::OnBnClickedCheckrectangle)
	ON_BN_CLICKED(IDC_CHECK_point, &CDlgToolboxSketchPad::OnBnClickedCheckpoint)
	ON_BN_CLICKED(IDC_CHECK_segment, &CDlgToolboxSketchPad::OnBnClickedChecksegment)
	ON_BN_CLICKED(IDC_CHECK_circle, &CDlgToolboxSketchPad::OnBnClickedCheckcircle)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgToolboxSketchPad message handlers

void CDlgToolboxSketchPad::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();

	if  (  m_var.bCreated  )  {
		traceLogA(  "CDlgToolboxSketchPad::PostNcDestroy(  ), delete this"  );
		delete  this;
	}

}



BOOL CDlgToolboxSketchPad::OnInitDialog()
{
	CDialog::OnInitDialog();

#ifdef  __WINCE__
		return  FALSE;
#else

	// TODO:  Add extra initialization here
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	CWinApp  *  pApp	=	AfxGetApp(  );
	int			i		=	0;
	CButton  *  pBtn;
	int			idc;
	QY_DMITEM	*	pItem;

	for  (  pItem  =  CONST_idcBmpTable;  pItem->type  !=  -1;  pItem  ++  )  {
		 idc  =  pItem->type;
		 pBtn  =  (  CButton  *  )GetDlgItem(  idc  );
		 if  (  pBtn->GetBitmap()  ==  NULL  )  {
			 m_var.hBmp_btns[i]  =  ::LoadBitmap(  pApp->m_hInstance, MAKEINTRESOURCE(  (  int  )pItem->des  )  );
			 pBtn->SetBitmap(  m_var.hBmp_btns[i]  );

			 this->m_toolTips[i].Create(  this  );
			 this->m_toolTips[i].Activate(  TRUE  );

			 this->m_toolTips[i].AddTool(  pBtn,  getResStr(  0,  &pQyMc->cusRes,  pItem->type  )  );

			 i  ++  ;
		 }
		_ASSERT(  i  <=  mycountof(  m_var.hBmp_btns  )  );
	}
	m_var.usCnt_btns  =  i;
	

	this->refreshBtns(  );

#if  1
	GetDlgItem(  IDC_CHECK_point  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_CHECK_segment  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_CHECK_circle  )->ShowWindow(  SW_HIDE  );
#endif

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE

#endif
}

void CDlgToolboxSketchPad::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	DestroyWindow(  );
}

void CDlgToolboxSketchPad::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//  CDialog::OnClose();
	DestroyWindow(  );
}



void CDlgToolboxSketchPad::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	int  i;
	for  (  i  =  0;  i  <  mycountof(  m_var.hBmp_btns  );  i  ++  )  {
		 if  (  m_var.hBmp_btns[i]  )  DeleteObject(  m_var.hBmp_btns[i]  );
	}
}

BOOL CDlgToolboxSketchPad::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
#ifndef  __WINCE__
	int  i;
	for  (  i  =  0;  i  <  m_var.usCnt_btns;  i  ++  )  {
		 this->m_toolTips[i].RelayEvent(  pMsg  );
	}
#endif

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgToolboxSketchPad::OnBnClickedCheckselect()
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	// TODO: Add your control notification handler code here
	//  CDlgDynBmps	*	pParent	=	(  CDlgDynBmps  *  )m_var.m_pParent;
	DLG_dynBmps_var  *  pParentVar  =  (  DLG_dynBmps_var  *  )m_var.m_pParentVar;
	//  SP_STRUCT	&	gSp  =  *(  SP_STRUCT  *  )pParentVar->pWall->getCurSp(  );
	SP_STRUCT	&	gSp  =  *(  SP_STRUCT  *  )pFuncs->pf_vw_getCurSp(  pParentVar->pWall  );

	gSp.sysStatus  =  STATUS_SELECT;
	this->refreshBtns(  );
}

void CDlgToolboxSketchPad::OnBnClickedCheckrectangle()
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	// TODO: Add your control notification handler code here
	//  CDlgDynBmps	*	pParent	=	(  CDlgDynBmps  *  )m_var.m_pParent;
	DLG_dynBmps_var  *  pParentVar  =  (  DLG_dynBmps_var  *  )m_var.m_pParentVar;
	SP_STRUCT	&	gSp  =  *(  SP_STRUCT  *  )pFuncs->pf_vw_getCurSp(  pParentVar->pWall  );

	gSp.sysStatus  =  STATUS_CREATE_A_RECTANGLE;
	this->refreshBtns(  );
}

void CDlgToolboxSketchPad::OnBnClickedCheckpoint()
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	// TODO: Add your control notification handler code here
	//  CDlgDynBmps	*	pParent	=	(  CDlgDynBmps  *  )m_var.m_pParent;
		DLG_dynBmps_var  *  pParentVar  =  (  DLG_dynBmps_var  *  )m_var.m_pParentVar;

		SP_STRUCT	&	gSp  =  *(  SP_STRUCT  *  )pFuncs->pf_vw_getCurSp(  pParentVar->pWall  );

	gSp.sysStatus  =  STATUS_CREATE_A_POINT;
	this->refreshBtns(  );
}

void CDlgToolboxSketchPad::OnBnClickedChecksegment()
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
		FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	// TODO: Add your control notification handler code here
	//  CDlgDynBmps	*	pParent	=	(  CDlgDynBmps  *  )m_var.m_pParent;
		DLG_dynBmps_var  *  pParentVar  =  (  DLG_dynBmps_var  *  )m_var.m_pParentVar;

	SP_STRUCT	&	gSp  =  *(  SP_STRUCT  *  )pFuncs->pf_vw_getCurSp(  pParentVar->pWall  );

	gSp.sysStatus  =  STATUS_CREATE_A_SEGMENT;
	this->refreshBtns(  );
}

void CDlgToolboxSketchPad::OnBnClickedCheckcircle()
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	// TODO: Add your control notification handler code here
	//  CDlgDynBmps	*	pParent	=	(  CDlgDynBmps  *  )m_var.m_pParent;
		DLG_dynBmps_var  *  pParentVar  =  (  DLG_dynBmps_var  *  )m_var.m_pParentVar;

		SP_STRUCT	&	gSp  =  *(  SP_STRUCT  *  )pFuncs->pf_vw_getCurSp(  pParentVar->pWall  );

	gSp.sysStatus  =  STATUS_CREATE_A_CIRCLE;
	this->refreshBtns(  );
}
