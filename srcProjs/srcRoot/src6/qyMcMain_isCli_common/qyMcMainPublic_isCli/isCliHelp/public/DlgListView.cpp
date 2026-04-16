// DlgListView.cpp : implementation file
//

#include "stdafx.h"
#include	"qyMcMainCommon.h"

#include	"myresource.h"

#include "DlgListView.h"
#include	"ctxQmc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


  __declspec(  dllexport  )  int viewDlgListView(  int  iWndContentType,  void  *  pSelParam  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int								iErr					=	-1;
	QY_MC					*		pQyMc					=	QY_GET_GBUF(  );
	int								iServiceId				=	CONST_qyServiceId_mis;
	MC_VAR_isCli  			*		pProcInfo				=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	CDlgListView			*		pDlg					=	NULL;
	RECT							rect;

	HWND					*		phWnd_lv				=	NULL;

	QY_MC_SEL				*		pSel					=	(  QY_MC_SEL  *  )pSelParam;

#if  0
	switch  (  iWndContentType  )  {
			case  CONST_qyWndContentType_qList:
				  //  phWnd_lv  =  &pProcInfo->hWnd_status_qList;
				  break;
			default:
					goto  errLabel;
					break;
	}
#endif

	//
	if  (  phWnd_lv  )  {
		if  (  IsWindow(  *phWnd_lv  )  )  {
			MACRO_SetForegroundWindow(  *phWnd_lv  );
			iErr  =  0;  goto  errLabel;
		}

		*phWnd_lv  =  NULL;
	}

	//
	pDlg  =  new  CDlgListView(  CWnd::GetDesktopWindow(  )  );
	if  (  !pDlg  )  goto  errLabel;

	//
	if  (  !pDlg->bSetQyMcDoc(  pSel  )  )  goto  errLabel;
	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	pDlg->ShowWindow(  SW_SHOW  );


	//
	if  (  phWnd_lv  )  *phWnd_lv  =  pDlg->m_hWnd;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}
	if  (  !iErr  )  {
	}

	//  traceLogA(  "viewMediaControl leaves, iErr is %d",  iErr  );

	return  iErr;
}

// CDlgListView dialog

IMPLEMENT_DYNAMIC(CDlgListView, CDialog)

CDlgListView::CDlgListView(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgListView::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.m_pParent = pParent;
	m_var.m_nID = CDlgListView::IDD;
	m_var.iIDC_list  =  IDC_list;

}

CDlgListView::~CDlgListView()
{
}


 BOOL  CDlgListView::bSetQyMcDoc(  QY_MC_SEL  *  pSel  )
{
	 BOOL			bRet	=	FALSE;
 	 QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	 CDBVariant		varVal[1];
	 BAR_CFG	*	pBarCfg	=	NULL;
	 CString		tmpCStr;
	 QY_OBJ_DB	*	pObj	=	NULL;

	 switch  (  pSel->type  )  {

			 case  CONST_qySelType_mcRootTree:
				   m_docStruct.iDocType  =  CONST_qyDocType_mcRootTree;
				   memcpy(  &m_docStruct.u.treeList.tree,  &pSel->u.rootTree,  sizeof(  pSel->u.rootTree  )  );
				   break;
			 case  CONST_qySelType_mcView:
				   m_docStruct.iDocType  =  CONST_qyDocType_mcView;
				   memcpy(  &m_docStruct.u.mcView,  &pSel->u.mcView,  sizeof(  m_docStruct.u.mcView  )  );		//  2006/12/24

				   this->qySetTitle(  pSel->u.mcView.docName  );

				   break;
			 default:
					goto  errLabel;

	 }

	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}

   BOOL CDlgListView::bDocAvail(  )
{
	 BOOL  bRet  =  FALSE;
	 
	  switch  (  this->m_docStruct.iDocType  )  {
			  case  QY_DOCTYPE_MC:
				    goto  errLabel;
			  case  QY_DOCTYPE_MCSITE:
			  case  QY_DOCTYPE_MCWEB:
				    if  (  !this->m_docStruct.m_pMcObj  )  goto  errLabel;
				    break;
			  default:
				      break;		
	  }

	  bRet  =  TRUE;

errLabel:
		return  bRet;
}

 void  CDlgListView::qySetTitle(  LPCTSTR  name  )
{
	m_title  =  CString(  m_docStruct.dsnName  )  +  (  m_docStruct.dsnName[0]  ?  CString(  " : "  )  :  CString(  ""  )  )  +  CString(  this->m_docStruct.preDocName  )  +  CString(  name  )  +  CString(  this->m_docStruct.postDocName  );	
}


 BOOL CDlgListView::Create(const RECT& rect)
{

	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProc		=	NULL;

	/*
	if  (  !m_var.bInfoSet  )  {
		traceLogA(  "CDlgTalk::Create(  ): 在创建对话框之前应先设置初始数据"  );
		return  FALSE;
	}
	*/

	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  FALSE;
	

	//
	if  (  !CDialog::Create(  this->m_var.m_nID, m_var.m_pParent  )  )  goto  errLabel;

	//
	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 BOOL  CDlgListView::bQuitDlg(  )		
{		
	traceLogA(  "CDlgListView_db(  )::bQuitDlg enters"  );


	//  2009/05/01
	DestroyWindow();				  
		
//  errLabel:

	traceLogA(  "CDlgListView_db(  )::bQuitDlg leaves"  );

	return  TRUE;
}

 BOOL  CDlgListView::bDisplayContent(  )
 {
	 CListCtrl	&	ListCtrl	=	*(  CListCtrl  *  )GetDlgItem(  m_var.iIDC_list  );
	 BOOL			bRet	=	FALSE;
	 int			nItem	=	0;
	 int			cnt;


	 if  (  m_docStruct.iDocType  ==  CONST_qyDocType_mcView  )  {	//  2006/12/24
		 void  *  pCfgParam  =  NULL;
		 if  (  m_docStruct.u.mcView.pfDisplayListContent  )  bRet  =  m_docStruct.u.mcView.pfDisplayListContent(  &ListCtrl,  pCfgParam,  &m_docStruct.u.mcView  );
		
		 cnt  =  ListCtrl.GetItemCount(  );						//  2008/01/02
		 if  (  cnt  <  0  )  cnt  =  0;

		 nItem  =  m_docStruct.u.mcView.curnItem;
		 if  (  nItem  >=  cnt  )  nItem  =  cnt  -  1;						//  2003/9/5.
		 if  (  nItem  >= 0  )  {
			 ListView_EnsureVisible(  this->m_hWnd, nItem,  FALSE  );
			 ListCtrl.SetItemState(  nItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
			 ListCtrl.Update(  nItem  );
		 }

		 return  bRet;
	 }

#if  0
	 if  (  m_docStruct.u.treeList.tree.pfDisplayListContent  )  return  (  m_docStruct.u.treeList.tree.pfDisplayListContent(  this,  pCfgParam,  &pDoc->m_docStruct.u.treeList.tree  )  ?  FALSE  :  TRUE  );

	 return  bDisplayMcRootContent(  this,  pCfgParam,  &pDoc->m_docStruct.u.treeList.tree  );
#endif

	 return  FALSE;
 }

  static  void  sizeDlg(  CDlgListView  *  pDlg  )
{
	int  iWidth = 0,  iHeight  = 0;
	int  x, y;
	RECT  rect;
	int  iW  = 0,  iH  =  0;
	CWnd  *  pCtrl;

	pDlg->GetClientRect(  &rect  );
	iWidth  =  rect.right  -  rect.left;  
	iHeight  =  rect.bottom  -  rect.top;
	if  (  iWidth  <  10  ||  iHeight  <  10  )  goto errLabel;

	pCtrl  =  pDlg->GetDlgItem(  IDC_list  );
	if  (  !pCtrl  )  goto  errLabel;

	HDWP	hDwp;
	int  nTotal;  nTotal  =  1;

	hDwp  =  BeginDeferWindowPos(  nTotal  );
	if  (  hDwp  )  {
		x  =  pDlg->m_var.iEdge_list_x;
		y  =  pDlg->m_var.iTop_list  -  23;
		iW  =  iWidth  -  2  *  pDlg->m_var.iEdge_list_x;
		iH  =  iHeight  -  pDlg->m_var.iTop_list;

		DeferWindowPos(  hDwp,  pCtrl->m_hWnd,  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		EndDeferWindowPos(  hDwp  );
	}

errLabel:
	return;
}


void CDlgListView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgListView, CDialog)
	ON_WM_SIZE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgListView message handlers

BOOL CDlgListView::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	QY_MC			*	pQyMc		=	(  QY_MC  *  )QY_GET_GBUF(  );
	QY_MC_DOCSTRUCT	*	pDocStruct	=	&m_docStruct;
	QY_MC_QUERY		*	pQuery		=	NULL;
	int					iErr		=	-1;
	CListCtrl		&	ListCtrl	=	*(  CListCtrl  *  )GetDlgItem(  m_var.iIDC_list  );	//  GetListCtrl();
	int					i;
	DWORD				dwStyle		=	0;



	if  (  m_docStruct.iDocType  ==  CONST_qyDocType_mcView  )  {	//  2006/12/24
		dwStyle  =  LVS_REPORT  |  LVS_SHOWSELALWAYS;
		if  (  !m_docStruct.u.mcView.ucbMultiSel  )  dwStyle  |=  LVS_SINGLESEL;		//  2007/08/24, 准备支持多选
		}
	else  dwStyle  =  LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL;

	ModifyStyle(  LVS_TYPEMASK,  dwStyle  );						//  ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
	ListCtrl.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );

	m_LargeImageList.Create( IDB_LARGEICONS, 32, 1, RGB( 255, 255, 255 ) );
	//  m_SmallImageList.Create( IDB_SMALLICONS, 16, 1, RGB( 255, 255, 255 ) );
	m_SmallImageList.Create( IDB_qnmIcons, 16, 1, RGB( 255, 255, 255 ) );
	// m_LargeImageList.SetOverlayImage(  NUM_ITEMS,  1  );
	// m_SmallImageList.SetOverlayImage(  NUM_ITEMS,  1  );
	ListCtrl.SetImageList(  &m_LargeImageList,  LVSIL_NORMAL  );
	ListCtrl.SetImageList(  &m_SmallImageList,  LVSIL_SMALL  );

	//
	int		iW,iH;
	RECT	rect,rc_list;

	GetWindowRect(  &rect  );
	iW  =  rect.right  -  rect.left;
	iH  =  rect.bottom  -  rect.top;

	GetDlgItem(  m_var.iIDC_list  )->GetWindowRect(  &rc_list  );
	m_var.iEdge_list_x  =  (  iW  -  (  rc_list.right  -  rc_list.left  )  )  /  2;
	m_var.iTop_list  =  rc_list.top;

	sizeDlg(  this  );
	//

	bDisplayContent(  );

	//  SetTimer(  1,  1000,  NULL  );

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		PostMessage(  WM_CLOSE,  0,  0  );
	}



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgListView::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	sizeDlg(  this  );
}

void CDlgListView::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//  CDialog::OnClose();
	bQuitDlg(  );
}

void CDlgListView::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();

	delete  this;
}
