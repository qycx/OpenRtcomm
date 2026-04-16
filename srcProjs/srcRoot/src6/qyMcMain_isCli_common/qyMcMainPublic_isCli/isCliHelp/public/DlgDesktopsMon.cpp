// DlgDesktopsMon.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"myresource.h"
//  #include	"qymc.h"
#include	"tmpCeLib.h"
#include	"DlgDesktopsMon.h"
#include	".\dlgdesktopsmon.h"
#include	"qyCusResTemp.h"
#include	"qySqlFunc.h"
#include	"isCliHelpPublic.h"
#include	"makedynamenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


	 int  setAllRemoteDesktopCanceled(  void  *  pDb,  void  *  p1,  unsigned  char  ucbMonDesktop  )
 {
	 return  -1;
 }




 QY_DMITEM  CONST_monIdcTable[]  =
{
	{	0,		(  TCHAR  *  )IDC_STATIC_pic0,	(  TCHAR  *  )IDC_STATIC30,	},
	{	1,		(  TCHAR  *  )IDC_STATIC_pic1,	(  TCHAR  *  )IDC_STATIC31,	},
	{	2,		(  TCHAR  *  )IDC_STATIC_pic2,	(  TCHAR  *  )IDC_STATIC32,	},
	{	3,		(  TCHAR  *  )IDC_STATIC_pic3,	(  TCHAR  *  )IDC_STATIC33,	},
	{	4,		(  TCHAR  *  )IDC_STATIC_pic4,	(  TCHAR  *  )IDC_STATIC34,	},
	{	5,		(  TCHAR  *  )IDC_STATIC_pic5,	(  TCHAR  *  )IDC_STATIC35,	},
	{	6,		(  TCHAR  *  )IDC_STATIC_pic6,	(  TCHAR  *  )IDC_STATIC36,	},
	{	7,		(  TCHAR  *  )IDC_STATIC_pic7,	(  TCHAR  *  )IDC_STATIC37,	},
	{	8,		(  TCHAR  *  )IDC_STATIC_pic8,	(  TCHAR  *  )IDC_STATIC38,	},
	{	9,		(  TCHAR  *  )IDC_STATIC_pic9,	(  TCHAR  *  )IDC_STATIC39,	},
	{	10,		(  TCHAR  *  )IDC_STATIC_pic10,	(  TCHAR  *  )IDC_STATIC40,	},
	{	11,		(  TCHAR  *  )IDC_STATIC_pic11,	(  TCHAR  *  )IDC_STATIC41,	},
	{	12,		(  TCHAR  *  )IDC_STATIC_pic12,	(  TCHAR  *  )IDC_STATIC42,	},
	{	13,		(  TCHAR  *  )IDC_STATIC_pic13,	(  TCHAR  *  )IDC_STATIC43,	},
	{	14,		(  TCHAR  *  )IDC_STATIC_pic14,	(  TCHAR  *  )IDC_STATIC44,	},
	{	15,		(  TCHAR  *  )IDC_STATIC_pic15,	(  TCHAR  *  )IDC_STATIC45,	},
	{	-1,									},
};


  __declspec(  dllexport  )  void  *  getDlgDesktopsMonVar(  HWND  hDlgDesktopsMon  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if  (  !IsWindow(  hDlgDesktopsMon  )  )  return  NULL;
	CDlgDesktopsMon  *  pDlg  =  (  CDlgDesktopsMon  *  )CDlgDesktopsMon::FromHandlePermanent(  hDlgDesktopsMon  );
	if  (  !pDlg  )  return  NULL;

	return  &pDlg->m_var;
}



/////////////////////////////////////////////////////////////////////////////
// CDlgDesktopsMon dialog


CDlgDesktopsMon::CDlgDesktopsMon(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDesktopsMon::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDesktopsMon)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	memset(  &m_var,  0,  sizeof(  m_var  )  );
	//
	if  (  pParent  )  m_var.m_hParent = pParent->m_hWnd;
	m_var.m_nID = CDlgDesktopsMon::IDD;

	//
#if  0  //  2017/01/10
	m_var.layoutParam.iEdge_l						=	10;
	m_var.layoutParam.iEdge_t						=	10;
	m_var.layoutParam.iEdge_r						=	10;
	m_var.layoutParam.iEdge_b						=	10;
	//
	m_var.layoutParam.iX_spacing					=	10;			//  
	m_var.layoutParam.iY_spacing					=	10;
	//
	m_var.layoutParam.iH_static						=	30;			//  
	//
	m_var.layoutParam.iY_spacing_pic_static			=	2;			//  
	m_var.layoutParam.iY_spacing_static_pic			=	4;			

	//  2008/04/14
	m_var.layoutParam.iW_btn						=  0;			//  10
	m_var.layoutParam.iH_btn						=  0;			//  10
	m_var.layoutParam.iY_spacing_static_btn			=  0;			//  10
#endif
}




 //  
 BOOL  CDlgDesktopsMon::bSetDlgInfo(  int  iWndContentType,  int  iSubtype,  int  iResId_menu,  unsigned  short  usCnt_row,  unsigned  short  usCnt_col,  unsigned  int  uiInitW_pic,  unsigned  int  uiInitH_pic  )
{
	BOOL			bRet	=	FALSE;
	if  (  !usCnt_row  ||  !usCnt_col  )  return  FALSE;
	if  (  usCnt_row  *  usCnt_col  >  CONST_maxMonedDesktops  )  return  FALSE;

	m_var.iWndContentType  =  iWndContentType;
	m_var.iSubtype  =  iSubtype;
	m_var.iResId_menu  =  iResId_menu;												

	//
	m_var.usCnt_row  =  usCnt_row;
	m_var.usCnt_col  =  usCnt_col;
	m_var.uiInitW_pic  =  uiInitW_pic;
	m_var.uiInitH_pic  =  uiInitH_pic;

	m_var.pIdcTable  =  CONST_monIdcTable;

	//  2016/01/04

	//
	m_var.bInfoSet  =  TRUE;

	return  TRUE;
}

 //
int  CDlgDesktopsMon::getWndContentType(  )
{
	return  m_var.iWndContentType;
}

//  2012/04/02
int  CDlgDesktopsMon::getWndContentSubtype(  )
{
	return  m_var.iSubtype;
}

	
BOOL CDlgDesktopsMon::Create(const RECT& rect)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;

	
	if  (  !m_var.bInfoSet  )  {
		traceLog(  _T(  "CDlgDesktopsMon::Create(  ) failed: bInfoSet is false"  )  );
		return  FALSE;
	}
	

	if  (  !CDialog::Create(  this->m_var.m_nID, CWnd::FromHandle(  m_var.m_hParent  )  )  )  goto  errLabel;

	//

	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}

BOOL  CDlgDesktopsMon::bEnableScrollBar(  BOOL  bEnable  )
{
	m_var.bScrollBarEnabled  =  bEnable;
		
	//  doLayout(  );

	return  TRUE;
}

 int  CDlgDesktopsMon::SetPicRect(  int  w,  int  h,  BOOL  bMoveWindow  )
{
	int  iErr  =  -1;

	if  (  !w  ||  !h  )  return  -1;

	{
		unsigned  int					uiInitW		=	0;
		unsigned  int					uiInitH		=	0;
		RECT							rect,  clientRect;

		//		
		uiInitW  =  w  *  m_var.usCnt_col  +  (  m_var.usCnt_col  -  1  )  *  m_var.layoutParam.iX_spacing  +  m_var.layoutParam.iEdge_l  +  m_var.layoutParam.iEdge_r;
		uiInitH  =  h  *  m_var.usCnt_row  +  m_var.layoutParam.iEdge_t  +  m_var.layoutParam.iEdge_b  +  m_var.layoutParam.iH_btn  +  m_var.layoutParam.iY_spacing_static_btn  +  (  m_var.usCnt_row  -  1  )  *  m_var.layoutParam.iY_spacing_static_pic  +  m_var.usCnt_row  *  (  m_var.layoutParam.iH_static  +  m_var.layoutParam.iY_spacing_pic_static  );
		
		//  m_rect.SetRect(  0,  0,  uiInitW,  uiInitH  );
		SetRect(  &m_var.m_rect,  0,  0,  uiInitW,  uiInitH  );
		  
		//  2012/05/14
		CDlgDesktopsMon  *  pDlg  =  this;
		int  index;
		int  i,  j;
		int  iW_pic  =  w;
		int  iH_pic  =  h;
		int  x,  y,  iW,  iH;
		for  (  i  =  0;  i  <  pDlg->m_var.usCnt_row;  i  ++  )  {

			  for  (  j  =  0;  j  <  pDlg->m_var.usCnt_col;  j  ++  )  {
				   index  =  i  *  pDlg->m_var.usCnt_col  +  j;
				   //		 
				   x  =  pDlg->m_var.layoutParam.iEdge_l  +  j  *  (  iW_pic  +  pDlg->m_var.layoutParam.iX_spacing  );
				   y  =  pDlg->m_var.layoutParam.iEdge_t  +  i  *  (  iH_pic  +  pDlg->m_var.layoutParam.iY_spacing_pic_static  +  pDlg->m_var.layoutParam.iH_static  +  pDlg->m_var.layoutParam.iY_spacing_static_pic  );
		 		   //
		 		   iW  =  iW_pic;  iH  =  iH_pic;
				   {	//  2012/04/24
					   pDlg->m_var.mems_org[index].iX  =  x;
					   pDlg->m_var.mems_org[index].iY  =  y;
					   pDlg->m_var.mems_org[index].iW  =  iW;
					   pDlg->m_var.mems_org[index].iH  =  iH;
				   }
			  }
		}
		
	    //
		if  (  bMoveWindow  )  {

#if  0
			if  (  uiInitW  >  DEFAULT_uiInitW_dlgDesktopsMon  ||  uiInitH  >  DEFAULT_uiInitH_dlgDesktopsMon  )  {	//  ÕâÊÇÒòÎª²»ÄÜ´°¿Ú¹ý´ó
				uiInitW  =  DEFAULT_uiInitW_dlgDesktopsMon;
				uiInitH  =  DEFAULT_uiInitH_dlgDesktopsMon;
			}
#endif
		  
			//
			GetWindowRect(  &rect  );		
			GetClientRect(  &clientRect  );
			MoveWindow(  rect.left,  rect.top,  uiInitW  + (  (  rect.right  -  rect.left  )  -  (  clientRect.right  -  clientRect.left  )  ),  uiInitH  +  (  (  rect.bottom  -  rect.top  )  -  (  clientRect.bottom  -  clientRect.top  )  )  );  		
		}
	}

	//  doLayout(  );

	iErr  =  0;
errLabel:
	 return  iErr;
}

//  2012/04/24
int  CDlgDesktopsMon::getPicRect(  int  idc,  RECT  *  pRc  )
{
	int					iErr	=	-1;
	CDlgDesktopsMon  *  pBase	=  this;
	int					i;

	for  (  i  =  0;  i  <  pBase->m_var.usCnt_row  *  pBase->m_var.usCnt_col;  i  ++  )  {
		 QY_DMITEM		*	pItem;
		 int					idcHint;

		 pItem  =  &pBase->m_var.pIdcTable[i];
		 if  (  idc  ==  (  int  )pItem->des  )  {
			 pRc->left  =  m_var.mems_org[i].iX;
			 pRc->right  =  m_var.mems_org[i].iX  +  m_var.mems_org[i].iW;
			 pRc->top  =  m_var.mems_org[i].iY;
			 pRc->bottom  =  m_var.mems_org[i].iY  +  m_var.mems_org[i].iH;

			 iErr  =  0;  goto  errLabel;
		 }
	}

errLabel:
	return  iErr;
}


void CDlgDesktopsMon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDesktopsMon)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDesktopsMon, CDialog)
	//{{AFX_MSG_MAP(CDlgDesktopsMon)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_stopScrollBar, &CDlgDesktopsMon::Onstopscrollbar)
	ON_UPDATE_COMMAND_UI(ID_stopScrollBar, &CDlgDesktopsMon::OnUpdatestopscrollbar)
	ON_COMMAND(ID_startScrollBar, &CDlgDesktopsMon::Onstartscrollbar)
	ON_UPDATE_COMMAND_UI(ID_startScrollBar, &CDlgDesktopsMon::OnUpdatestartscrollbar)
	ON_MESSAGE( QY_WM_COMM, OnQyComm )
	ON_MESSAGE(  CONST_qyWm_postComm,  OnQyPostComm  )
	ON_COMMAND(ID_fullScreen, &CDlgDesktopsMon::Onfullscreen)
	ON_UPDATE_COMMAND_UI(ID_fullScreen, &CDlgDesktopsMon::OnUpdatefullscreen)
#ifndef  __WINCE__
	ON_WM_GETMINMAXINFO()
#endif
	ON_WM_CLOSE()
	ON_WM_MOVE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDesktopsMon message handlers

void CDlgDesktopsMon::PostNcDestroy()
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	CDialog::PostNcDestroy();

	if  (  m_var.bCreated  )  {
		traceLogA(  "CDlgDesktopsMon::PostNcDestroy(  ), delete this"  );
		delete  this;
	}

	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	qmcApplyForChkingTasks_gui(  pQyMc  );	//  2009/09/10

}




BOOL CDlgDesktopsMon::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯
	int				iErr	=	-1;
	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	CWnd		*	pCtrl;
	int				idc;
	RECT			rc;

	QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  &pQyMc->cusRes  );
	if  (  !pResMem  )  goto  errLabel;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  m_var.iResId_menu  )  {		
		CMenu			*	pMenu	=	this->GetMenu(  );
		QY_DMITEM		*	pItem;
		unsigned  int		nPos	=	m_var.iResId_menu;		//  CONST_resId_menu_dlgVideos;

		if  (  !pMenu  )  goto  errLabel;
#if  1  //  def  __SUPPORT_wndMenu__
		if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  CONST_resId_popupMenu  )  )  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "CDlgDesktopsMon::OnInitDialog failed, pItem CONST_resId_popupMenu is null"  )  );
			#endif
			goto  errLabel;
		}
		if  (  !(  pItem  =  qyGetDmItemByType(  pItem,  nPos,  sizeof(  QY_DMITEM  )  )  )  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "DlgDesktopsMon::OnInitDialog: qyGetDmItemByType failed, nPos %d"  ),  nPos  );
			#endif
			goto  errLabel;
		}
		if  (	 makeDynaMenu(  &pQyMc->cusRes,  pMenu->m_hMenu,  (  QY_DMITEM  *  )pItem->pData,  0,  pQyMc,  0  )  )  goto  errLabel;		
#endif

	}

	SCROLLINFO	si;
	si.cbSize  =  sizeof(  SCROLLINFO  );
	si.fMask  =  SIF_ALL;
	si.nMin  =  0;
	si.nMax  =  0;
	si.nPage  =  si.nMax  /  10;
	si.nPos  =  0;
	SetScrollInfo(  SB_HORZ,  &si,  TRUE  );
	SetScrollInfo(  SB_VERT,  &si,  TRUE  );

#if  0
	if  (  m_var.uiInitW_pic  &&  m_var.uiInitH_pic  )  {
		unsigned  int					uiInitW		=	0;
		unsigned  int					uiInitH		=	0;
		RECT							rect,  clientRect;

		//		
		uiInitW  =  m_var.uiInitW_pic  *  m_var.usCnt_col  +  (  m_var.usCnt_col  -  1  )  *  m_var.layoutParam.iX_spacing  +  m_var.layoutParam.iEdge_l  +  m_var.layoutParam.iEdge_r;
		uiInitH  =  m_var.uiInitH_pic  *  m_var.usCnt_row  +  m_var.layoutParam.iEdge_t  +  m_var.layoutParam.iEdge_b  +  m_var.layoutParam.iH_btn  +  m_var.layoutParam.iY_spacing_static_btn  +  (  m_var.usCnt_row  -  1  )  *  m_var.layoutParam.iY_spacing_static_pic  +  m_var.usCnt_row  *  (  m_var.layoutParam.iH_static  +  m_var.layoutParam.iY_spacing_pic_static  );
		
		m_rect.SetRect(  0,  0,  uiInitW,  uiInitH  );
		//

		if  (  uiInitW  >  DEFAULT_uiInitW_dlgDesktopsMon  ||  uiInitH  >  DEFAULT_uiInitH_dlgDesktopsMon  )  {	//  ÕâÊÇÒòÎª²»ÄÜ´°¿Ú¹ý´ó
			uiInitW  =  DEFAULT_uiInitW_dlgDesktopsMon;
			uiInitH  =  DEFAULT_uiInitH_dlgDesktopsMon;
		}
		  
		//
		GetWindowRect(  &rect  );		
		GetClientRect(  &clientRect  );
		MoveWindow(  rect.left,  rect.top,  uiInitW  + (  (  rect.right  -  rect.left  )  -  (  clientRect.right  -  clientRect.left  )  ),  uiInitH  +  (  (  rect.bottom  -  rect.top  )  -  (  clientRect.bottom  -  clientRect.top  )  )  );  
		}
	else  {
		  GetClientRect(  &m_rect  );
	}
#endif
	if  (  !m_var.uiInitW_pic  ||  !m_var.uiInitH_pic  )  {
		m_var.uiInitW_pic  =  DEFAULT_uiInitW_pic_dlgDesktopsMon;
		m_var.uiInitH_pic  =  DEFAULT_uiInitH_pic_dlgDesktopsMon;
	}
	BOOL  bMove  =  TRUE;
	//
	if  (  m_var.param_bValid_pos  )  
	{
		//bMove  =  FALSE;
	}
	//
	if  (  SetPicRect(  m_var.uiInitW_pic,  m_var.uiInitH_pic,  bMove  )  )  goto  errLabel;

	//
	m_var.bDlgInited  =  TRUE;

	//  2008/11/06
	doLayout(  );

	//
	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		EndDialog(  -1  );		//  2010/09/04. 实际上不能采用EndDialog来删除无模式对话框。有时间要修改掉。
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}




 void CDlgDesktopsMon::OnDestroy()
{
	traceLogA(  "CDlgDesktopsMon::OnDestroy(  )"  );


	CDialog::OnDestroy();

}




BOOL  CDlgDesktopsMon::bQuitDlg(  )
{
	//
	DestroyWindow(  );
	return  TRUE;
}
	



void CDlgDesktopsMon::OnCancel()
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	if  (  pQyMc->iServiceId  ==  CONST_qyServiceId_netMc  )  {

		if  (  myMessageBox(  NULL,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cancelMonDesktop  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		//
		setAllRemoteDesktopCanceled(  pQyMc->gui.pDb,  0,  TRUE  );  
	}

	//
	bQuitDlg(  );
}


 

 //  
int  CDlgDesktopsMon::sizeAllControls(  RECT  rc  )
{
	 int					iErr							=	-1;
	 CDlgDesktopsMon  *		pDlg							=	this;  
	 HDWP					hDwp;
	 //
	 int					iW_pic							=	10;
	 int					iH_pic							=	10;
	 //
	 int					iW_static						=	10;
	 //
	 int					idc;
	 unsigned  int			nTotal							=	0;
	 //
	 int					i,  j;
	 QY_DMITEM			*	pItem;
	 int					x,y;
	 int					iH,  iW;
	 //
	 int					index;

	 if  (  !pDlg  )  return  -1;
	 if  (  !pDlg->m_var.bInfoSet  )  return  -1;
	 if  (  pDlg->m_var.usCnt_row  *  pDlg->m_var.usCnt_col  >  getnItems(  pDlg->m_var.pIdcTable  )  )  return  -1;
	 if  (  !pDlg->m_var.bDlgInited  )  return  -1;	 
     
	 //  2012/04/24
	 //  BOOL	bOrg  =  m_rect.EqualRect(  &rc  );

	 //
	 iW_pic  =  (  rc.right  -  rc.left  -  pDlg->m_var.layoutParam.iEdge_l  -  pDlg->m_var.layoutParam.iEdge_r  -  (  pDlg->m_var.usCnt_col  -  1  )  *  pDlg->m_var.layoutParam.iX_spacing  )  /  pDlg->m_var.usCnt_col;
	 iH_pic  =  (  rc.bottom  -  rc.top  -  pDlg->m_var.layoutParam.iEdge_t  -  pDlg->m_var.layoutParam.iEdge_b  -  pDlg->m_var.layoutParam.iH_btn  -  pDlg->m_var.layoutParam.iY_spacing_static_btn  -  (  pDlg->m_var.usCnt_row  -  1  )  *  pDlg->m_var.layoutParam.iY_spacing_static_pic  -  pDlg->m_var.usCnt_row  *  (  pDlg->m_var.layoutParam.iH_static  +  pDlg->m_var.layoutParam.iY_spacing_pic_static  )  )  /  pDlg->m_var.usCnt_row;

	 //
	 iW_static  =  iW_pic;

	 nTotal  =  pDlg->m_var.usCnt_row  *  pDlg->m_var.usCnt_col  *  2;

	 hDwp  =  BeginDeferWindowPos(  nTotal  );
	 if  (  hDwp  )  {		 

		 for  (  i  =  0;  i  <  pDlg->m_var.usCnt_row;  i  ++  )  {

			  for  (  j  =  0;  j  <  pDlg->m_var.usCnt_col;  j  ++  )  {
				   index  =  i  *  pDlg->m_var.usCnt_col  +  j;
				   //		 
				   pItem  =  &pDlg->m_var.pIdcTable[index];
				   idc  =  (  int  )pItem->des;
				   //
				   x  =  pDlg->m_var.layoutParam.iEdge_l  +  j  *  (  iW_pic  +  pDlg->m_var.layoutParam.iX_spacing  );
				   y  =  pDlg->m_var.layoutParam.iEdge_t  +  i  *  (  iH_pic  +  pDlg->m_var.layoutParam.iY_spacing_pic_static  +  pDlg->m_var.layoutParam.iH_static  +  pDlg->m_var.layoutParam.iY_spacing_static_pic  );
		 		   //
		 		   iW  =  iW_pic;  iH  =  iH_pic;
		 		   DeferWindowPos(  hDwp,  pDlg->GetDlgItem(  idc  )->m_hWnd,  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
				   //
#if  0
				   if  (  bOrg  )  
				   {	//  2012/04/24
					   pDlg->m_var.mems_org[index].iX  =  x;
					   pDlg->m_var.mems_org[index].iY  =  y;
					   pDlg->m_var.mems_org[index].iW  =  iW;
					   pDlg->m_var.mems_org[index].iH  =  iH;
				   }
#endif
				   //  2012/05/04
				   pDlg->m_var.mems[index].iX  =  x;
				   pDlg->m_var.mems[index].iY  =  y;
				   pDlg->m_var.mems[index].iW  =  iW;
				   pDlg->m_var.mems[index].iH  =  iH;

				   //
				   idc  =  (  int  )pItem->pData;
				   //
				   y  +=  iH  +  pDlg->m_var.layoutParam.iY_spacing_pic_static;
				   //
				   iW  =  iW_static;  iH  =  pDlg->m_var.layoutParam.iH_static;
		 		   DeferWindowPos(  hDwp,  pDlg->GetDlgItem(  idc  )->m_hWnd,  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );

			  }

		 }
		 
		 EndDeferWindowPos(  hDwp  );
	 }

	 for  (  i  =  0;  i  <  pDlg->m_var.usCnt_row;  i  ++  )  {
		  for  (  j  =  0;  j  <  pDlg->m_var.usCnt_col;  j  ++  )  {
			   pItem  =  &pDlg->m_var.pIdcTable[i  *  pDlg->m_var.usCnt_col  +  j];

			   if  (  !pDlg->m_var.ucbHideStatic_idc  )  {	//  2013/03/01
				   idc  =  (  int  )pItem->des;
				   ::ShowWindow(  ::GetDlgItem(  pDlg->GetSafeHwnd(  ),  idc  ),  SW_SHOW  );			   
			   }
			   
			   if  (  !pDlg->m_var.ucbHideStatic_idcHint  )  {
				   idc  =  (  int  )pItem->pData;
				   ::ShowWindow(  ::GetDlgItem(  pDlg->GetSafeHwnd(  ),  idc  ),  SW_SHOW  );			   			   
			   }

			   continue;
		  }
	 }

	 iErr  =  0;
//  errLabel:
	return  iErr;
}



 void  CDlgDesktopsMon::doLayout(    )
{
	int			cx,  cy;
	RECT		rc;
	SCROLLINFO	si;
	int			nScrollMax  =  0;

	if  (  !m_var.bDlgInited  )  return;

	traceLogA(  "doLayout called."  );


	// TODO: ÔÚ´Ë´¦Ìí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂë
	if  (  !m_var.bScrollBarEnabled  )  {	

		si.cbSize  =  sizeof(  SCROLLINFO  );
		si.fMask  =  SIF_ALL;
		si.nMin  =  0;
		si.nMax  =  0;
		si.nPage  =  si.nMax  /  10;
		si.nPos  =  0;
		SetScrollInfo(  SB_HORZ,  &si,  TRUE  );
		SetScrollInfo(  SB_VERT,  &si,  TRUE  );

		//
		GetClientRect(  &rc  );	//  2008/11/08

		//  sizeAllControls_dlgDesktopsMon(  rc  );
		sizeAllControls(  rc  );
		return;
	}

	//
	GetClientRect(  &rc  );	//  2008/11/08

	cx  =  rc.right  -  rc.left;
	cy  =  rc.bottom  -  rc.top;

	if  (  !cx  ||  !cy  )  return;

	m_var.m_nCurWidth  =  cx;
	m_var.m_nCurHeight  =  cy;

	//
	int  m_rect_iW  =  m_var.m_rect.right  -  m_var.m_rect.left;
	int  m_rect_iH  =  m_var.m_rect.bottom  -  m_var.m_rect.top;

	//
	nScrollMax  =  0;
	if  (  cx  <  m_rect_iW  )  {
		nScrollMax  =  m_rect_iW  -  cx;
	}
	m_var.m_nScrollPos_h  =  0;
	//
	si.cbSize  =  sizeof(  SCROLLINFO  );
	si.fMask  =  SIF_ALL;
	si.nMin  =  0;
	si.nMax  =  nScrollMax;
	si.nPage  =  si.nMax  /  10;
	si.nPos  =  m_var.m_nScrollPos_h;
	SetScrollInfo(  SB_HORZ,  &si,  TRUE  );


	nScrollMax  =  0;
	if  (  cy  <  m_rect_iH  )  {
		nScrollMax  =  m_rect_iH  -  cy;
	}
	m_var.m_nScrollPos_v  =  0;
	//
	si.cbSize  =  sizeof(  SCROLLINFO  );
	si.fMask  =  SIF_ALL;
	si.nMin  =  0;
	si.nMax  =  nScrollMax;
	si.nPage  =  si.nMax  /  10;
	si.nPos  =  m_var.m_nScrollPos_v;
	SetScrollInfo(  SB_VERT,  &si,  TRUE  );

	sizeAllControls(  m_var.m_rect  );

	return;
}


 void  CDlgDesktopsMon::endFullScreen(  )
{
	if  (  m_var.m_bFullScreen  )  {
		m_var.m_bFullScreen  =  FALSE;

		//  2012/07/07
		restoreWndBorder(  m_hWnd,  &m_var.m_fullScreenInfo.hOldMenu,  &m_var.m_fullScreenInfo.lOldStyle  );

		//
		ShowWindow(  SW_HIDE  );
		memcpy(  &m_var.layoutParam,  &m_var.m_oldLayoutParam,  sizeof(  m_var.layoutParam  )  );
		mySetWindowPlacement(  this->GetSafeHwnd(  ),  &m_var.m_oldWndPlacement  );
		ShowWindow(  SW_RESTORE  );				
	}

	return;
}



void CDlgDesktopsMon::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	//  2012/05/04
	if  (  !m_var.bDlgInited  )  return;

	//
	doLayout(  );

	//  sizeAllControls(  );

	if  (  m_var.pf_OnSize  )  m_var.pf_OnSize(  (  LPVOID  )this->m_hWnd,  (  LPVOID  )cx,  (  LPVOID  )cy  );

}




void CDlgDesktopsMon::OnOK()
{
	// TODO: 
#ifdef  __DEBUG__
	traceLogA(  "OnOK"  );
#endif
	//  CDialog::OnOK();
}


 LRESULT  CDlgDesktopsMon::OnQyComm( WPARAM wParam, LPARAM lParam )
{
	long				lRet				=					-1;
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	
	if  (  !pComm  )  return  -1;

	switch  (  pComm->uiType  )  {
			case  QY_WMPARAM_GETDOCINFO:
				  break;
			default:
					break;
	}

	lRet  =  QY_RC_WMOK;

//  errLabel:

	return  lRet;

}

 LRESULT  CDlgDesktopsMon::OnQyPostComm( WPARAM wParam, LPARAM lParam )
{
	long				lRet				=					-1;

	lRet  =  QY_RC_WMOK;

//  errLabel:

	return  lRet;

}



void CDlgDesktopsMon::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//  traceLogA(  "OnHScroll"  );

	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	int		m_rect_iW  =  m_var.m_rect.right  -  m_var.m_rect.left;

	int		nDelta;
	int		nMaxPos  =  m_rect_iW  -  m_var.m_nCurWidth;

	switch  (  nSBCode  )  {
			case  SB_LINEDOWN:
				  if  (  m_var.m_nScrollPos_h  >=  nMaxPos  )  return;
				  nDelta  =  min(  nMaxPos  /  100,  nMaxPos  -  m_var.m_nScrollPos_h  );
				  break;
			case  SB_LINEUP:
				  if  (  m_var.m_nScrollPos_h  <=  0  )  return;
				  nDelta  =  -min(  nMaxPos  /  100,  m_var.m_nScrollPos_h  );
				  break;
			case  SB_PAGEDOWN:
				  if  (  m_var.m_nScrollPos_h  >=  nMaxPos  )  return;
				  nDelta  =  min(  nMaxPos  /  10,  nMaxPos  -  m_var.m_nScrollPos_h  );
				  break;
			case  SB_PAGEUP:
				  if  (  m_var.m_nScrollPos_h  <=  0  )  return;
				  nDelta  =  -min(  nMaxPos  /  10,  m_var.m_nScrollPos_h  );
				  break;
			case  SB_THUMBPOSITION:
				  nDelta  =  (  int  )nPos  -  m_var.m_nScrollPos_h;
				  break;
			default:
					return;
	}
	m_var.m_nScrollPos_h  +=  nDelta;
	SetScrollPos(  SB_HORZ,  m_var.m_nScrollPos_h,  TRUE  );
	ScrollWindow(  -nDelta,  0  );

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDlgDesktopsMon::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//  traceLogA(  "OnVScroll"  );

	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	int		m_rect_iH  =  m_var.m_rect.bottom  -  m_var.m_rect.top;

	int		nDelta;
	int		nMaxPos  =  m_rect_iH  -  m_var.m_nCurHeight;

	switch  (  nSBCode  )  {
			case  SB_LINEDOWN:
				  if  (  m_var.m_nScrollPos_v  >=  nMaxPos  )  return;
				  nDelta  =  min(  nMaxPos  /  100,  nMaxPos  -  m_var.m_nScrollPos_v  );
				  break;
			case  SB_LINEUP:
				  if  (  m_var.m_nScrollPos_v  <=  0  )  return;
				  nDelta  =  -min(  nMaxPos  /  100,  m_var.m_nScrollPos_v  );
				  break;
			case  SB_PAGEDOWN:
				  if  (  m_var.m_nScrollPos_v  >=  nMaxPos  )  return;
				  nDelta  =  min(  nMaxPos  /  10,  nMaxPos  -  m_var.m_nScrollPos_v  );
				  break;
			case  SB_PAGEUP:
				  if  (  m_var.m_nScrollPos_v  <=  0  )  return;
				  nDelta  =  -min(  nMaxPos  /  10,  m_var.m_nScrollPos_v  );
				  break;
			case  SB_THUMBPOSITION:
				  nDelta  =  (  int  )nPos  -  m_var.m_nScrollPos_v;
				  break;
			default:
					return;
	}
	m_var.m_nScrollPos_v  +=  nDelta;
	SetScrollPos(  SB_VERT,  m_var.m_nScrollPos_v,  TRUE  );
	ScrollWindow(  0,  -nDelta  );

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

 //  2008/11/07, ÕâÀïÓÃÀ´ÈÃ¶Ô»°¿òµÄ²Ëµ¥µ¯³öÊ±ÄÜ±ä»Ò¡£
 void CDlgDesktopsMon::OnInitMenuPopup(CMenu* pMenu, UINT nIndex, BOOL bSysMenu)
{
	//  CDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	// TODO: ÔÚ´Ë´¦Ìí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂë
	ASSERT(pMenu != NULL);
	
	// check the enabled state of various menu items

	CCmdUI state;
	state.m_pMenu = pMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	// determine if menu is popup in top-level menu and set m_pOther to
	//  it if so (m_pParentMenu == NULL indicates that it is secondary popup)
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pMenu->m_hMenu)
		state.m_pParentMenu = pMenu;    // parent == child for tracking popup
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = GetTopLevelParent();
			// child windows don't have menus -- need to go to the top!
		if (pParent != NULL &&
			(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pMenu->m_hMenu)
				{
					// when popup is found, m_pParentMenu is containing menu
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}

	state.m_nIndexMax = pMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
	  state.m_nIndex++)
	{
		state.m_nID = pMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // menu separator or invalid cmd - ignore it

		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			// possibly a popup menu, route to first item of that popup
			state.m_pSubMenu = pMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue;       // first item of popup can't be routed to
			}
			state.DoUpdate(this, FALSE);    // popups are never auto disabled
		}
		else
		{
			// normal menu item
			// Auto enable/disable if frame window has 'm_bAutoMenuEnable'
			//    set and command is _not_ a system command.
			state.m_pSubMenu = NULL;
			BOOL  tmp_m_bAutoMenuEnable  =  TRUE;
			state.DoUpdate(this, tmp_m_bAutoMenuEnable && state.m_nID < 0xF000);
		}

		// adjust for menu deletions and additions
		UINT nCount = pMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}

}



 void CDlgDesktopsMon::Onstopscrollbar()
 {
	 // TODO: Add your command handler code here
	 bEnableScrollBar(  FALSE  );

	 doLayout(  );

	 //  sizeAllControls(  );
	 //
	 InvalidateRect(  NULL,  TRUE  );
	 UpdateWindow(  );

 }

 void CDlgDesktopsMon::OnUpdatestopscrollbar(CCmdUI *pCmdUI)
 {
	 // TODO: Add your command update UI handler code here
	 if  (  m_var.notOnOffScrollBar  )  pCmdUI->Enable(  FALSE  );
	 if  (  !m_var.bScrollBarEnabled  )  pCmdUI->Enable(  FALSE  );

 }

 void CDlgDesktopsMon::Onstartscrollbar()
 {
	 // TODO: Add your command handler code here	 
	 bEnableScrollBar(  TRUE  );

	 doLayout(  );
	 
	 //  sizeAllControls(  );
	 //
	 InvalidateRect(  NULL,  TRUE  );
	 UpdateWindow(  );
 }

 void CDlgDesktopsMon::OnUpdatestartscrollbar(CCmdUI *pCmdUI)
 {
	 // TODO: Add your command update UI handler code here
	 if  (  m_var.notOnOffScrollBar  )  pCmdUI->Enable(  FALSE  );
	 if  (  m_var.bScrollBarEnabled  )  pCmdUI->Enable(  FALSE  );
 }

#if  0	//  2012/06/26
 void CDlgDesktopsMon::Onfullscreen()
 {
	 if  (  m_var.m_bFullScreen  )  {
		 endFullScreen(  );				//  2011/10/10
		 return;
	 }

	 // TODO: Add your command handler code here
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

  //  2012/06/26
 void CDlgDesktopsMon::Onfullscreen()
 {
	 if  (  m_var.m_bFullScreen  )  {
		 endFullScreen(  );				//  2011/10/10
		 return;
	 }

	 //  2012/07/07
	 makeWndNoBorder(  m_hWnd,  FALSE,  &m_var.m_fullScreenInfo.hOldMenu,  &m_var.m_fullScreenInfo.lOldStyle  );

	 // TODO: Add your command handler code here
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

	 //
	 HMONITOR	hMonitor;
	 POINT		point;
	 point.x  =  (  wndRect.left  +  wndRect.right  )  /  2;
	 point.y  =  (  wndRect.top  +  wndRect.bottom  )  /  2;
	 hMonitor  =  MonitorFromPoint(  point,  MONITOR_DEFAULTTONEAREST  );

	 MONITORINFO mi;
	 mi.cbSize = sizeof(mi);
	 GetMonitorInfo(hMonitor, &mi);

	 RECT	rc;
#if  0
    if (flags & MONITOR_WORKAREA)
		 rc = mi.rcWork;
		 tBuf[0]  =  0;
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "mi.rcWork:l-%d,t-%d,r-%d,b-%d"  ),  rc.left,  rc.top,  rc.right,  rc.bottom  );
		 myMessageBox(  NULL,  tBuf,  _T( "mi.rcWork"  ),  MB_YESNO  );
	else
#endif
     rc = mi.rcMonitor;

	 nFullWidth  =  rc.right  -  rc.left;
	 nFullHeight  =  rc.bottom  -  rc.top;


	 //
	 m_var.m_fullScreenRect.left  =  wndRect.left  -  clientRect.left  +  rc.left;
	 m_var.m_fullScreenRect.top  =  wndRect.top  -  clientRect.top;
	 m_var.m_fullScreenRect.right  =  wndRect.right  -  clientRect.right  +  rc.left  +  nFullWidth;
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



 void CDlgDesktopsMon::OnUpdatefullscreen(CCmdUI *pCmdUI)
 {
	 // TODO: Add your command update UI handler code here
 }

 void CDlgDesktopsMon::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
 {
	 // TODO: Add your message handler code here and/or call default
	 if  (  m_var.m_bFullScreen  )  {
		 lpMMI->ptMaxSize.x  =  m_var.m_fullScreenRect.right  -  m_var.m_fullScreenRect.left;
		 lpMMI->ptMaxSize.y  =  m_var.m_fullScreenRect.bottom  -  m_var.m_fullScreenRect.top;

		 lpMMI->ptMaxPosition.x  =  m_var.m_fullScreenRect.right  -  m_var.m_fullScreenRect.left;
		 lpMMI->ptMaxPosition.y  =  m_var.m_fullScreenRect.bottom  -  m_var.m_fullScreenRect.top;

		 lpMMI->ptMaxTrackSize.x  =  m_var.m_fullScreenRect.right  -  m_var.m_fullScreenRect.left;
		 lpMMI->ptMaxTrackSize.y  =  m_var.m_fullScreenRect.bottom  -  m_var.m_fullScreenRect.top;
	 }

#ifndef  __WINCE__
	 CDialog::OnGetMinMaxInfo(lpMMI);
#endif
 }

 BOOL CDlgDesktopsMon::PreTranslateMessage(MSG* pMsg)
 {
	 // TODO: Add your specialized code here and/or call the base class
	 switch  (  pMsg->message  )  {
			 case  WM_KEYDOWN:  {
				   UINT	nChar  =  pMsg->wParam;
				   if  (  nChar  ==  VK_ESCAPE  )  {
					   //
					   #if  1
							qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "Client"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "DlgDesktopsMon: VK_ESCAPE. %d"  ),  m_var.iWndContentType  );
					   #endif

					   //
					   if  (  m_var.m_bFullScreen  )  {
						   endFullScreen(  );
						   return  TRUE;
					   }
					   //  2018/07/10
					   return  TRUE;
				   }
				   }
				   break;
			 default:
					break;
	 }


	 return CDialog::PreTranslateMessage(pMsg);
 }

 void CDlgDesktopsMon::OnClose()
 {
	 // TODO: Add your message handler code here and/or call default
	 QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	if  (  pQyMc->iServiceId  ==  CONST_qyServiceId_netMc  )  {

		if  (  myMessageBox(  NULL,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cancelMonDesktop  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		//
		setAllRemoteDesktopCanceled(  pQyMc->gui.pDb,  0,  TRUE  );  
	}

	 //  CDialog::OnClose();
	 bQuitDlg(  );
 }

 void CDlgDesktopsMon::OnMove(int x, int y)
 {
	 CDialog::OnMove(x, y);

	 // TODO: Add your message handler code here
	 if  (  m_var.pf_OnMove  )  m_var.pf_OnMove(  (  LPVOID  )this->m_hWnd,  (  LPVOID  )x,  (  LPVOID  )y  );

 }
