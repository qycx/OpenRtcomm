// DlgMyHtmlEdit.cpp : implementation file
//

#include "stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	"qymcMainCommon.h"
#include	"myresource.h"


#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"

#ifdef  __SUPPORT_HTMLEDIT__
	#include	"myHtmlEditCtrl.h"
#endif

#include	"tmpCeLib.h"

#include	"qyOpenShellCommon.h"
#include	"DlgTalk.h"
#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"

#include	"DlgInstantAssistant.h"

#include	<assert.h>
#ifndef  __WINCE__
	#include	"qyPs.h"
#endif
#include	"qmcDxSurfacePublic.h"
#include	"qmcConferenceWall.h"

#include	"isCliHelpPublic.h"
#include	"qmcCmdProc.h"
#include	"isCmdConst.h"

#include	"funcsForIsCliHelp.h"
#include	"isCliD3dPublic.h"
#include	"wallTalkers.h"


//
#include "DlgMsgTool.h"
#include "afxdialogex.h"

#include	"dlgtalkproc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


__declspec(  dllexport  )  int  dlgMsgTool_OnInitDialog_createHtmlEdits(  HWND  hDlgMsgTool,  DLG_msgTool_var  *  pDlgMsgToolVar  ); 
  __declspec(  dllexport  )  int  dlgMsgTool_OnQyPostComm_idcInited(  QY_MC *pQyMc,  HWND  hDlgMsgTool,  DLG_msgTool_var  *  pDlgMsgToolVar,  UINT  wParam,  LONG  lParam  );
  int  sizeAllControls_dlgMsgTool(  HWND  hDlg,  DLG_msgTool_var  &  m_var  );


__declspec(  dllexport  )  int  viewDlgMsgTool_talk(  HWND  hParent,  HWND  hCurTalk,  BOOL  bUseHtmlEdit  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );

	CDlgMsgTool			*		pDlg					=	NULL;
	RECT							rect;

	HWND					*		phWnd_lv				=	NULL;

#if  0		
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "viewDlgHtmlEdit_talk not finished."  )  );
	return  0;
#endif

#if  10
		

	//
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hCurTalk  );
	if  (  !pCurVar  )  goto  errLabel;


	//
	phWnd_lv  =  &pCurVar->msgTool.hWnd_msgTool;	//  &pProcInfo->subtitles.hWnd_videoTagCfg;

	if  (  phWnd_lv  )  {
		if  (  IsWindow(  *phWnd_lv  )  )  {
			MACRO_SetForegroundWindow(  *phWnd_lv  );
			iErr  =  0;  goto  errLabel;
		}

		*phWnd_lv  =  NULL;
	}

	//
#if  0
	if  (  pShadowMgr->subtitles.hWnd_subtitles  )  {
		if  (  IsWindow(  pShadowMgr->subtitles.hWnd_subtitles  )  )  {
			SendMessage(  pShadowMgr->subtitles.hWnd_subtitles,  WM_CLOSE,  0,  0  );
		}
		if  (  IsWindow(  pShadowMgr->subtitles.hWnd_subtitles  )  )  goto  errLabel;
	}
	memset(  &pMgrVar->subtitles,  0,  sizeof(  pMgrVar->subtitles  )  );
#endif
	
	//
	pDlg  =  new  CDlgMsgTool(  CWnd::FromHandle(  hParent  )  );
	if  (  !pDlg  )  goto  errLabel;

	if  (  !pDlg->bSetInfo(  bUseHtmlEdit  )  )  goto  errLabel;
	pDlg->m_var.hDlgTalk  =  hCurTalk;
	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	//  setMsgToolPos(  hCurTalk  );
	//pDlg->ShowWindow(  SW_SHOW  );


	//
	if  (  phWnd_lv  )  *phWnd_lv  =  pDlg->m_hWnd;


	//
	//  2017/07/07
	//
	refreshTalkToInfo(  hCurTalk  );



#endif

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}



	return  iErr;
}

  __declspec(  dllexport  )  void  *  getDlgMsgToolVar(  HWND  hDlgMsgTool  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if  (  !IsWindow(  hDlgMsgTool  )  )  return  NULL;
	CDlgMsgTool  *  pDlg  =  (  CDlgMsgTool  *  )CDlgMsgTool::FromHandlePermanent(  hDlgMsgTool  );
	if  (  !pDlg  )  return  NULL;

	return  &pDlg->m_var;
}


// CDlgMsgTool dialog

IMPLEMENT_DYNAMIC(CDlgMsgTool, CDialogEx)

CDlgMsgTool::CDlgMsgTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMsgTool::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

	//
	m_var.m_hParent = pParent->m_hWnd;
	m_var.m_nID = CDlgMsgTool::IDD;


	//  2012/05/18
	m_var.guiData.iIDC_LIST_task  =  IDC_LIST_task;
	m_var.guiData.iIDC_STATIC_instantStatus  =  IDC_STATIC_instantStatus;
	m_var.guiData.iIDC_STATIC_recentMsgList  =  IDC_STATIC_recentMsgList;
	m_var.guiData.iIDC_STATIC_input  =  IDC_STATIC_input;

}

CDlgMsgTool::~CDlgMsgTool()
{
	//  2013/07/04
	if  (  m_var.pm_LargeImageList  )  {
		myImageList_free(  m_var.pm_LargeImageList  );
		m_var.pm_LargeImageList  =  NULL;
	}
	if  (  m_var.pm_SmallImageList  )  {
		myImageList_free(  m_var.pm_SmallImageList  );
		m_var.pm_SmallImageList  =  NULL;
	}

}


	
BOOL  CDlgMsgTool::bSetInfo(  BOOL  bUseHtmlEdit  )
{
	m_var.ucbUseHtmlEdit  =  bUseHtmlEdit;

	return  TRUE;
}

	BOOL CDlgMsgTool::Create(const RECT& rect)
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




BOOL  CDlgMsgTool::bQuitDlg(  )		
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


void CDlgMsgTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMsgTool, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_MESSAGE(CONST_qyWm_comm, OnQyComm)
	ON_MESSAGE(CONST_qyWm_postComm, OnQyPostComm)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_task, &CDlgMsgTool::OnLvnItemchangedListtask)
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CDlgMsgTool message handlers



BOOL CDlgMsgTool::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	int  iErr  =  -1;

	//
	makeWndNoBorder(  m_hWnd,  FALSE,  NULL,  NULL  );

	//
	m_var.pm_LargeImageList  =  myImageList_new( IDB_LARGEICONS, 32, 1, RGB( 255, 255, 255 ) );
	m_var.pm_SmallImageList  =  myImageList_new( IDB_qnmIcons, 16, 1, RGB( 255, 255, 255 ) );
	if  (  !m_var.pm_LargeImageList  ||  !m_var.pm_SmallImageList  )  goto  errLabel;


	//
	if  (  m_var.ucbUseHtmlEdit  )  {

		if  (  dlgMsgTool_OnInitDialog_createHtmlEdits(  m_hWnd,  &m_var  )  )  goto  errLabel;

		//  2014/01/24
		//  if  (  viewDlgMsgTool_talk(  m_hWnd,  m_var.hDlgTalk,  m_var.ucbUseHtmlEdit  )  )  goto  errLabel;

		}
	else  {		//  2012/05/17
		  m_var.guiData.bFinished_createCtrls  =  TRUE;
	}

	//
	sizeAllControls_dlgMsgTool(  m_hWnd,  m_var  );

	//
	iErr  =  0;
	
errLabel:


	if  (  iErr  )  {
		m_var.bInitFailed  =  TRUE;
		
		//  2012/05/17
		if  (  !m_var.ucbUseHtmlEdit  )  {
			PostMessage(  WM_CLOSE,  0,  0  );
		}
	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMsgTool::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//  CDialogEx::OnCancel();
	bQuitDlg(  );
}

void CDlgMsgTool::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//  CDialogEx::OnClose();
	bQuitDlg(  );
}

void CDlgMsgTool::OnDestroy()
{
#ifdef  __SUPPORT_HTMLEDIT__
	 traceLogA(  "destroy 2 htmlEdits"  );	//  ÔÚ¹Ø±Õtalk´°¿ÚÊ±£¬×ÜÊÇÓÐÒì³££¬»³ÒÉÊÇhtmlEditºÍdlgµÄÍ¬²½ÓÐÎÊÌâ¡£ÔÝÊ±ÏÈÔÚÕâÀïÏÈdestroy. 2008/10/22

	 if  (  m_var.msgToolCommon.m_pHtmlEdit_input  )  {
		 if  (  IsWindow(  m_var.msgToolCommon.m_pHtmlEdit_input->m_hWnd  )  )  {
			 m_var.msgToolCommon.m_pHtmlEdit_input->m_dropTarget.Revoke(  );
			 m_var.msgToolCommon.m_pHtmlEdit_input->DestroyWindow(  );
		 }
	 }
	 if  (  m_var.msgToolCommon.m_pHtmlEdit_recentMsgList  )  {
		 if  (  IsWindow(  m_var.msgToolCommon.m_pHtmlEdit_recentMsgList->m_hWnd  )  )  {
			 m_var.msgToolCommon.m_pHtmlEdit_recentMsgList->m_dropTarget.Revoke(  );
			 m_var.msgToolCommon.m_pHtmlEdit_recentMsgList->DestroyWindow(  );
		 }
	 }
#endif


	//
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


void CDlgMsgTool::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::PostNcDestroy();
	
	//
	if  (  m_var.msgToolCommon.m_pHtmlEdit_input  )  {  
		try  {
			 delete  m_var.msgToolCommon.m_pHtmlEdit_input;  m_var.msgToolCommon.m_pHtmlEdit_input  =  NULL;	
			 }
		catch  (  ...  )  {
			   #ifdef  __DEBUG__
					   traceLog(  _T(  "Exception here"  )  );
			   #endif
		}
	}
	if  (  m_var.msgToolCommon.m_pHtmlEdit_recentMsgList  )  {  
		delete  m_var.msgToolCommon.m_pHtmlEdit_recentMsgList;  m_var.msgToolCommon.m_pHtmlEdit_recentMsgList  =  NULL;	
	}
	
	//
	delete  this;
}



LRESULT CDlgMsgTool::OnQyComm(  WPARAM  wParam, LPARAM  lParam  )
{
	LONG				lRet			=	-1;
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	QY_WMBUF_COMM	*	pComm			=	(  QY_WMBUF_COMM  *  )lParam;
	TCHAR				tBuf[512]		=	_T(  ""  );
	HWND				hDlg			=	m_hWnd;
#ifndef  __WINCE__
	//  CListCtrl		*	pListCtrl		=	(  CListCtrl  *  )CWnd::FromHandle(  GetDlgItem(  hDlg,  m_var.idcList_task  )  );
	HWND				hListCtrl		=	::GetDlgItem(  hDlg,  m_var.msgToolCommon.idcList_task  );
#endif
	
	if  (  !pComm  )  return  -1;

#ifdef  __SUPPORT_HTMLEDIT__
	switch  (  pComm->uiType  )  {
			case  CONST_qyWmParam_getDropTarget:  

				  if  (  dlgMsgTool_OnQyComm_getDropTarget(  hDlg,  &m_var,  wParam,  lParam  )  )  goto  errLabel;

				  lRet  =  CONST_qyWmRc_ok;  
				  goto  errLabel;

				  break;
			default:
					break;
	}
#endif

	MSGR_ADDR	addr;
	addr.idInfo.ui64Id  =  0;
	if  (  !m_var.guiData.bFinished_createCtrls  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "CDlgTalk::OnQyComm(  ) failed: bFinished_createCtrls is false, %I64u"  ),  addr.idInfo.ui64Id  );
		#endif
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::OnQyComm failed, bFinished_createCtrls false.%I64u"  ),  addr.idInfo.ui64Id  );
		goto  errLabel;
	}


	switch  (  pComm->uiType  )  {		
			default:
					#ifdef  __DEBUG__
							traceLog(  _T(  "dlgTalk_OnQyComm failed, unknown commType %d"  ),  pComm->uiType  );
					#endif
				    goto  errLabel;
	}
	lRet  =  CONST_qyWmRc_ok;
errLabel:
	return	lRet;
}


 LRESULT CDlgMsgTool::OnQyPostComm(  WPARAM  wParam, LPARAM  lParam  )
 {
	 	LONG				lRet			=	-1;
	//  DLG_TALK_var	&	m_var			=	*(  DLG_TALK_var  *  )pDLG_TALK_var;

	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	char				buf[1024]		=	"";
	//
	PARAM_PROC_ROW		param;
	HWND				hDlg			=	m_hWnd;
	
	memset(  &param,  0,  sizeof(  param  )  );
	
	switch  (  wParam  )  {
			case  CONST_qyWmParam_idcInited:  

				  if  (  dlgMsgTool_OnQyPostComm_idcInited(  pQyMc,  hDlg,  &m_var,  wParam,  lParam  )  )  goto  errLabel;

				  //  2012/05/17
				  lRet  =  CONST_qyWmRc_ok;  
				  goto  errLabel;

				  break;
			case  CONST_qyWmParam_setActiveWindow:
				  #ifndef  __WINCE__
						   //  SetActiveWindow(  hDlg  );
						   MACRO_SetForegroundWindow(  hDlg  );
				  #else
						   SetForegroundWindow(  hDlg  );
				  #endif

			      //  2012/05/17
				  lRet  =  CONST_qyWmRc_ok;  
				  goto  errLabel;

				  break;
			default:
					break;					
		
	}

	//  2012/05/17
	if  (  !m_var.guiData.bFinished_createCtrls  )  {
		MSGR_ADDR	addr;
		addr.idInfo.ui64Id  =  0;
		#ifdef  __DEBUG__
				traceLog(  _T(  "CDlgTalk::OnQyPostComm(  ) failed: bFinished_createCtrls is false, %I64u"  ),  addr.idInfo.ui64Id  );
		#endif
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::OnQyPostComm failed, bFinished_createCtrls false.%I64u"  ),  addr.idInfo.ui64Id  );
		goto  errLabel;
	}

	lRet  =  QY_RC_WMOK;

errLabel:

	return	lRet;

}


int  sizeAllControls_dlgMsgTool(  HWND  hDlg,  DLG_msgTool_var  &  m_var  )
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

#ifdef  __APP_qyMc__
		if  (  !m_var.ucbOnGlobalVWall  )  {			
			iEdge_l							=	CONST_edge_l_dlgTalk_desktop;
			iEdge_t							=	CONST_edge_t_dlgTalk_desktop;
			iEdge_r							=	CONST_edge_l_dlgTalk_desktop;
			iEdge_b							=	CONST_edge_b_dlgTalk_desktop;
			//
			iX_spacing						=	CONST_iX_spacing_dlgTalk_desktop;			//  
			iY_spacing						=	CONST_iY_spacing_dlgTalk_desktop;			//  
		}
#endif


	 int			iW_taskList						=	10;
	 int			iH_taskList						=	10;
	 //
	 int			iW_instantStatus				=	50;
	 int			iH_instantStatus				=	15;			//  20;		//  2012/05/17, 因为gps墙上小talk的缘故，希望talk标签小一点
	 //
	 int			iW_confStatus					=	50;
	 int			iH_confStatus					=	15;	
	 //
	 int			iW_recentMsgList				=	10;
	 int			iH_recentMsgList				=	10;
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
	 iW_taskList  =  rc.right  -  rc.left;
	 iW_recentMsgList  =  iW_taskList;
	 iW_instantStatus  =  iW_recentMsgList;
	 iW_input  =  iW_recentMsgList;
	 iW_confStatus  =  iW_recentMsgList;

	 //
	 iH  =  rc.bottom  -  rc.top;

	 if  (  iW_taskList  )  {
		 //  iH_input
	 	 iH  =  iH  -  (  iH_input  );
		 if  (  iH  <  0  )  iH  =  0;

		 iH  -=  iH_instantStatus;
		 if  (  iH  <  0  )  iH  =  0;

		 iH  -=  iH_confStatus;
		 if  (  iH  <  0  )  iH  =  0;

		 //
		 iH_recentMsgList  =  iH  /  2;
		 iH_taskList  =    iH  -  iH_recentMsgList;
		 if  (  iH_taskList  <  0  )  iH_taskList  =  0;
		 }
	 else  {
		 iH_input  =  0;
		 iH_recentMsgList  =  0;
		 iH_instantStatus  =  0;
		 iH_confStatus  =  0;
		 iH_taskList  =  0;
	 }


	 //
	 hDwp  =  M_BeginDeferWindowPos(  5  );
	 if  (  hDwp  )  {		 
		 			   
		 x  =  0;		 		 
		 y  =  0;		//  +  iH_dlgDesc;		 		 
		 //
		 idc  =  IDC_LIST_task;
		 iW  =  iW_taskList;  iH  =  iH_taskList;
		 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_SHOWWINDOW  );
		 //
		 idc  =  IDC_STATIC_confStatus;
		 y  +=  iH;
		 iW  =  iW_confStatus;  iH  =  iH_confStatus;
		 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_SHOWWINDOW  );
		 

		 //  4
		 idc  =  m_var.guiData.iIDC_STATIC_recentMsgList;
		 y  +=  iH;  
		 iW  =  iW_recentMsgList;  iH  =  iH_recentMsgList;
		 hCtrl  =  m_var.msgToolCommon.m_pHtmlEdit_recentMsgList  ?  m_var.msgToolCommon.m_pHtmlEdit_recentMsgList->m_hWnd  :  GetDlgItem(  hDlg,  idc  );
		 M_DeferWindowPos(  hDwp,  hCtrl,  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		 //  3rd
		 idc  =  IDC_STATIC_instantStatus;
		 y  +=  iH;
		 iW  =  iW_instantStatus;  iH  =  iH_instantStatus;
		 M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		 //  5
		 idc  =  m_var.guiData.iIDC_STATIC_input;
		 y  +=  iH;
		 iW  =  iW_input;  iH  =  iH_input;
		 hCtrl  =  m_var.msgToolCommon.m_pHtmlEdit_input  ?  m_var.msgToolCommon.m_pHtmlEdit_input->m_hWnd  :  GetDlgItem(  hDlg,  idc  );
		 M_DeferWindowPos(  hDwp,  hCtrl,  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );



		 //
		 M_EndDeferWindowPos(  hDwp  );


	 }



	 iErr  =  0;


	 return  iErr;

}



 void CDlgMsgTool::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	sizeAllControls_dlgMsgTool(  m_hWnd,  m_var  );
 }


 void CDlgMsgTool::OnLvnItemchangedListtask(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;


	if  (  pNMListView->iItem  >= 0 
		&&  (  pNMListView->uNewState  &  (  LVIS_SELECTED | LVIS_FOCUSED  )  )  ==  (  LVIS_SELECTED | LVIS_FOCUSED  )  )
	{
		CListCtrl			*	pListCtrl								=	(  CListCtrl  *  )GetDlgItem(  m_var.msgToolCommon.idcList_task  );
		TCHAR					rowIdStr[64  +  1]						=	_T(  ""  );
		
		
		pListCtrl->GetItemText(  pNMListView->iItem,  1,  rowIdStr,  mycountof(  rowIdStr  )  );		
		activateRowByRowId(  m_var.hDlgTalk,  rowIdStr  );	
	}


	*pResult = 0;
}


 HBRUSH CDlgMsgTool::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	DLG_TALK_var  *  pMgrVar  =  NULL;
	//
	CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  m_var.hDlgTalk  );
	if  (  !pDlgTalk  )  goto  errLabel;
	
	//		
	HWND  hMgr  =  m_var.hDlgTalk;		
	pMgrVar  =  pDlgTalk->get_pm_var();
	if  (  !pMgrVar  )  goto  errLabel;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
			TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pMgrVar->pShadowInfo;
			if  (  !pShadow  )  goto  errLabel;
			hMgr  =  pShadow->hMgr;
			pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
			if  (  !pMgrVar  )  goto  errLabel;		
	}
		
	//	
	if  (  nCtlColor  ==  CTLCOLOR_STATIC  )  {
		int	idc  =  pWnd->GetDlgCtrlID(  );
		//
		if  (  idc  ==  m_var.guiData.iIDC_STATIC_instantStatus  )  {

			
			if  (  pMgrVar->av.taskInfo.bTaskExists  )  {
				QY_SHARED_OBJ		*	pSharedObj	=	getSharedObjByIndex( pProcInfo,  pMgrVar->av.iIndex_sharedObj_localAv  );
				if  (  pSharedObj  &&  pSharedObj->iIndex_curUsr  !=  pMgrVar->av.iIndex_usr_localAv  )  {
					pDC->SetBkMode(  TRANSPARENT  );
					return  pDlgTalk->m_brush_hangingUp_dlg;
				}
				
			}
		}
	}

	


errLabel:

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}




 

 BOOL CDlgMsgTool::PreTranslateMessage(MSG* pMsg)
 {
	 // TODO: Add your specialized code here and/or call the base class
	 //
	 switch  (  pMsg->message  )  {
			 case  WM_MOUSEMOVE:  {
				   
				   //traceLog(  _T(  "msgTool.pretrans.mouseMove"  )  );
				   //
				   msgTool_proc_mouseMove(  m_hWnd,  CONST_qyWndContentType_dlgMsgTool  );

				   }
				   break;
			 default:
					 break;
	 }

	 return CDialogEx::PreTranslateMessage(pMsg);
 }
