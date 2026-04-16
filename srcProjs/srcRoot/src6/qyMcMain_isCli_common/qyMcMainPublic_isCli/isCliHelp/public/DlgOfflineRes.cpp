// DlgOfflineRes.cpp : implementation file
//

#include "stdafx.h"

#define  __noDbg_new__

#include	"qyMcMainCommon.h"
#include	"myresource.h"

#include	"DlgVideoTagCfg.h"
#include	"afxdialogex.h"

#include	"qyCusResTemp.h"

//  #include	"DlgSubtitleSelect.h"

#include	"qmcCmdProc.h"

#include	"qyOpenShellCommon.h"
//  #include	"DlgTalk.h"
#include	"dlgTalkProc.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"isCliD3dPublic.h"



#include "DlgOfflineRes.h"
#include "afxdialogex.h"

#include	"qmcDynBmp.h"
#include	"qmcCommFunc_isCli.h"


//
__declspec(  dllexport  )  int  getOfflineResTaskStatus(  HWND   hOfflineRes,  DFT_sendTask  *  pTask  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	CDlgOfflineRes  *  pDlg  =  (  CDlgOfflineRes  *  )CWnd::FromHandlePermanent(  hOfflineRes  );
	if  (  !pDlg  )  return  -1;

	int  i;
	for  (  i  =  0;  i  <  pDlg->m_var.reses_beingProced.usCnt;  i  ++  )  {
		 RES_inProcess  *  pMem  =  &pDlg->m_var.reses_beingProced.mems[i];
		 //
		 if  (  pMem->usSubtype  ==  CONST_procOfflineResSubtype_upload			
			 &&  pDlg->m_var.idInfo.ui64Id  ==  pTask->cfg.idInfo_dst.ui64Id
			 &&  !_tcsicmp(  pMem->res.name,  pTask->cfg.file_fullName  )  )
		 {
			 //
			 if  (  pMem->iStatus  )  {
				 pTask->iStatus  =  pMem->iStatus;			
				 pTask->dwTickCnt_modified  =  pMem->dwTickCnt_modified;
				 pTask->transferFileStatus  =  pMem->transferFileStatus;
			 }
			 //
			 return  0;
		 }
	}
	
	
	return  -1;
}





//
__declspec(  dllexport  )  int  viewDlgOfflineRes_talk(  HWND  hParent,  HWND  hCurTalk,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phTool  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	//  
	CDlgOfflineRes			*		pDlg					=	NULL;
	RECT							rect;

	HWND					*		phWnd_lv				=	NULL;

	//
	HWND							hTool					=	NULL;

	//
	CHelp_getDlgTalkVar  help_getDlgTalkVar;
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;

	//
	DLG_TALK_var  *  pCurVar  =  NULL;
	DLG_TALK_var  *  pMgrVar  =  NULL;
	//
	HWND	hMgr	=	NULL;

	//
	showInfo_open0(  0,  0,  _T(  "viewDlgOfflineRes_talk called"  )  );

	//
	pCurVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hCurTalk  );
	if  (  !pCurVar  )  goto  errLabel;
	if  (  isTalkerShadowMgr(  pCurVar->addr  )  )  hMgr  =  hCurTalk;
	else  {
		  TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pCurVar->pShadowInfo;
		  if  (  !pShadow  )  goto  errLabel;
		  hMgr  =  pShadow->hMgr;
	}
	//
	pMgrVar  =   (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
	if  (  !pMgrVar  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

	//  2017/09/24
	if  (  pMgrVar->bShouldQuit1  )  {
		showInfo_open0(  0,  0,  _T(  "viewDlgOfflineRes_talk failed, pMgrVar->bShouldQuit true"  )  );
		goto  errLabel;
	}

	//
	phWnd_lv  =  &pCurVar->offlineRes.hTool_offlineRes;	//  &pProcInfo->subtitles.hWnd_videoTagCfg;

	if  (  phWnd_lv  )  {
		if  (  IsWindow(  *phWnd_lv  )  )  {
			if  (  bActivateWnd  )  {
				MACRO_SetForegroundWindow(  *phWnd_lv  );
				}
			else  {
				  if  (  !bNeedNotShowWnd  )  {
					  if  (  !IsWindowVisible(  *phWnd_lv  )  )  ShowWindow(  *phWnd_lv,  SW_SHOW  );  
				  }
			}
			//
			hTool  =  *phWnd_lv;
			//
			iErr  =  0;  goto  errLabel;
		}

		*phWnd_lv  =  NULL;
	}

	//
	if  (  pShadowMgr->offlineRes.hTool_offlineRes  )  {
		if  (  IsWindow(  pShadowMgr->offlineRes.hTool_offlineRes  )  )  {
			SendMessage(  pShadowMgr->offlineRes.hTool_offlineRes,  WM_CLOSE,  0,  0  );
		}
		if  (  IsWindow(  pShadowMgr->offlineRes.hTool_offlineRes  )  )  goto  errLabel;
	}
	memset(  &pMgrVar->offlineRes,  0,  sizeof(  pMgrVar->offlineRes  )  );
	
	//
	pDlg  =  new  CDlgOfflineRes(  CWnd::FromHandle(  hParent  )  );
	if  (  !pDlg  )  goto  errLabel;

	if  (  !pDlg->bSetDlgInfo(  0,  0,  _T(  "offline Res"  )  )  )  goto  errLabel;
	pDlg->m_var.idInfo.ui64Id  =  pMgrVar->addr.idInfo.ui64Id;
	pDlg->m_var.hCurTalk  =  hCurTalk;
	pDlg->m_var.hDlgTalk_mgr  =  hMgr;	//  hCurTalk;
		//
	if  (  pShadowMgr->av.ucbMeConfMgr  &&  pMgrVar->addr.uiObjType  ==  CONST_objType_imGrp  )  pDlg->m_var.ucbConfMgr  =  TRUE;

	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	if  (  !bNeedNotShowWnd  )  {
		pDlg->ShowWindow(  SW_SHOW  );
	}

	//
	if  (  phWnd_lv  )  *phWnd_lv  =  pDlg->m_hWnd;
	pShadowMgr->offlineRes.hTool_offlineRes  =  pDlg->m_hWnd;

	//
	hTool  =  pDlg->m_hWnd;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}
	if  (  !iErr  )  {
		if  (  phTool  )  *phTool  =  hTool;
	}

	//
	TCHAR  tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "viewDlgOfflineRes_talk leaves, iErr %d"  ),  iErr  );
	showInfo_open0(  0,  0,  tBuf  );


	//
	return  iErr;
}



//  2015/08/06
__declspec(  dllexport  )  int  viewDlgOfflineRes_me(  HWND  hParent,  OfflineRes_var  *  pVar,  PARAM_viewOfflineRes  *  pParam  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	//  FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );

	CDlgOfflineRes			*		pDlg					=	NULL;
	RECT							rect;

	HWND					*		phWnd_lv				=	NULL;

	//
	PARAM_viewOfflineRes  param  =  {0};
	if  (  pParam  )  param  =  *pParam;


	//
	phWnd_lv  =  &pVar->hTool_offlineRes;	//  &pProcInfo->subtitles.hWnd_videoTagCfg;

	if  (  phWnd_lv  )  {
		if  (  IsWindow(  *phWnd_lv  )  )  {
			MACRO_SetForegroundWindow(  *phWnd_lv  );
			iErr  =  0;  goto  errLabel;
		}

		*phWnd_lv  =  NULL;
	}

	
	//
	pDlg  =  new  CDlgOfflineRes(  CWnd::FromHandle(  hParent  )  );
	if  (  !pDlg  )  goto  errLabel;

	if  (  !pDlg->bSetDlgInfo(  0,  0,  _T(  "offline Res"  )  )  )  goto  errLabel;
	pDlg->m_var.hDlgTalk_mgr  =  NULL;	//  hCurTalk;
	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	//
	if  (  param.bNoBorder  )  {
		makeWndNoBorder(  pDlg->m_hWnd,  FALSE,  NULL,  NULL  );
	}
	//
	pDlg->ShowWindow(  SW_SHOW  );


	//
	if  (  phWnd_lv  )  *phWnd_lv  =  pDlg->m_hWnd;


	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}



	return  iErr;
}





//
#define		CONST_edge_l							10
#define		CONST_edge_t							10
#define		CONST_iX_spacing						5
#define		CONST_iY_spacing						1

int  sizeAllControls_offlineRes(  HWND  hDlg,   DLG_guiData_offlineRes  *  pGuiData  )
{
	int				iErr		=  -1;

	HDWP			hDwp;
	int				idc;
	int				x, y, iW, iH;
	RECT			rc;

	int				iEdge_l							=	CONST_edge_l;
	int				iEdge_t							=	CONST_edge_t;
	int				iEdge_r							=	CONST_edge_l;
	int				iEdge_b							=	CONST_edge_t;
	//
	int				iX_spacing						=	CONST_iX_spacing;			//  
	int				iY_spacing						=	CONST_iY_spacing;			//  
	//
	int				iW_static						=	0;
	int				iH_static						=	0;

	int				iW_edit							=	0;
	int				iH_edit							=	0;

	GetClientRect(  hDlg,  &rc  );

	int  iw_cur,  ih_cur;
	iw_cur  =  rc.right  -  rc.left;
	ih_cur  =  rc.bottom  -  rc.top;

	float  fx  =  1.0  *  iw_cur  /  pGuiData->iw_org;
	float  fy  =  1.0  *  ih_cur  /  pGuiData->ih_org;

	iW  =  iw_cur  -  iEdge_l  -  iEdge_r;
	iH  =  ih_cur  -  iEdge_t  -  iEdge_b;


	iW_static  =  min  (  iW  *  0.1,  30  );
	iH_static  =  iH  /  16;

	iW_edit  =  iW  -  iW_static  -  iX_spacing  -  iEdge_l;
	iH_edit  =  iH  /  16;

	hDwp  =  M_BeginDeferWindowPos(  14  );
	if  (  hDwp  )  {

		//  
		idc  =  pGuiData->iIDC_BUTTON_delete;
		rc  =  pGuiData->rcIDC_BUTTON_delete;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		//  
		idc  =  pGuiData->iIDC_BUTTON_download;
		rc  =  pGuiData->rcIDC_BUTTON_download;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		//  
		idc  =  pGuiData->iIDC_BUTTON_refresh;
		rc  =  pGuiData->rcIDC_BUTTON_refresh;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		//  
		idc  =  pGuiData->iIDC_BUTTON_upload;
		rc  =  pGuiData->rcIDC_BUTTON_upload;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		//  
		idc  =  pGuiData->iIDC_LIST_offlineRes;
		rc  =  pGuiData->rcIDC_LIST_offlineRes;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		//  
		//  2015/08/12
		idc  =  pGuiData->iIDC_BUTTON_page1;
		rc  =  pGuiData->rcIDC_BUTTON_page1;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		idc  =  pGuiData->iIDC_BUTTON_nextPage;
		rc  =  pGuiData->rcIDC_BUTTON_nextPage;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		idc  =  pGuiData->iIDC_BUTTON_prevPage;
		rc  =  pGuiData->rcIDC_BUTTON_prevPage;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		idc  =  pGuiData->iIDC_EDIT_pageNo;
		rc  =  pGuiData->rcIDC_EDIT_pageNo;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		idc  =  pGuiData->iIDC_BUTTON_go;
		rc  =  pGuiData->rcIDC_BUTTON_go;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		idc  =  pGuiData->iIDC_STATIC_filterKeywords;
		rc  =  pGuiData->rcIDC_STATIC_filterKeywords;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		idc  =  pGuiData->iIDC_EDIT_filterKeywords;
		rc  =  pGuiData->rcIDC_EDIT_filterKeywords;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		//
		idc  =  pGuiData->iIDC_BUTTON_showAllDownloads;
		rc  =  pGuiData->rcIDC_BUTTON_showAllDownloads;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		//
		idc  =  pGuiData->iIDCANCEL;
		rc  =  pGuiData->rcIDCANCEL;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );


		EndDeferWindowPos(  hDwp  );
	}

	iErr  =  0;
errLabel:

	return  iErr;
}



// CDlgOfflineRes dialog

IMPLEMENT_DYNAMIC(CDlgOfflineRes, CDialogEx)

CDlgOfflineRes::CDlgOfflineRes(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgOfflineRes::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

	m_var.guiData.iIDC_BUTTON_delete  =  IDC_BUTTON_delete;
	m_var.guiData.iIDC_BUTTON_download  =  IDC_BUTTON_download;
	m_var.guiData.iIDC_BUTTON_refresh  =  IDC_BUTTON_refresh;
	m_var.guiData.iIDC_BUTTON_upload  =  IDC_BUTTON_upload;
	m_var.guiData.iIDC_LIST_offlineRes  =  IDC_LIST_offlineRes;
	//
	m_var.guiData.iIDC_BUTTON_page1  =  IDC_BUTTON_page1;
	m_var.guiData.iIDC_BUTTON_nextPage  =  IDC_BUTTON_nextPage;
	m_var.guiData.iIDC_BUTTON_prevPage  =  IDC_BUTTON_prevPage;
	m_var.guiData.iIDC_EDIT_pageNo  =  IDC_EDIT_pageNo;
	m_var.guiData.iIDC_BUTTON_go  =  IDC_BUTTON_go;
	m_var.guiData.iIDC_STATIC_filterKeywords  =  IDC_STATIC_filterKeywords;
	m_var.guiData.iIDC_EDIT_filterKeywords  =  IDC_EDIT_filterKeywords;
	//
	m_var.guiData.iIDC_BUTTON_showAllDownloads  =  IDC_BUTTON_showAllDownloads;
	//  2016/07/27
	m_var.guiData.iIDCANCEL  =  IDCANCEL;  

	if (pParent) {
		m_var.m_hParent = pParent->m_hWnd;
	}
	m_var.m_nID  =  this->IDD;


}

CDlgOfflineRes::~CDlgOfflineRes()
{
}


BOOL  CDlgOfflineRes::bSetDlgInfo(  int  iWndContentType,  int  iSubType,  LPCTSTR  title  )
{
	BOOL	bRet	=	FALSE;


	m_var.iWndContentType  =  iWndContentType;
	m_var.iWndContentSubType  =  iSubType;
	safeTcsnCpy(  title,  m_var.title,  mycountof(  m_var.title  )  );

	bRet  =  TRUE;

	return  bRet;
}


//
BOOL CDlgOfflineRes::Create(const RECT& rect)
{

	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	//MC_VAR_isMgr			*	pProc		=	NULL;

	/*
	if  (  !m_var.bInfoSet  )  {
		traceLogA(  "CDlgTalk::Create(  ): 在创建对话框之前应先设置初始数据"  );
		return  FALSE;
	}
	*/

	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  FALSE;
	//if  (  !m_var.iWndContentType  )  return  FALSE;
	

	//
	CWnd* pParent = mynull;
	if (m_var.m_hParent)pParent = CWnd::FromHandle(m_var.m_hParent);
	if  (  !CDialog::Create(  this->m_var.m_nID, pParent  )  )  goto  errLabel;

	//
	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 BOOL  CDlgOfflineRes::bQuitDlg(  )		
{		
	traceLogA(  "CDlgStatusCli(  )::bQuitDlg enters"  );


	//  2009/05/01
	DestroyWindow();				  
		
//  errLabel:

	traceLogA(  "CDlgStatusCli(  )::bQuitDlg leaves"  );

	return  TRUE;
}


 int  CDlgOfflineRes::sizeAllControls(  )
{

	int								iErr  =  -1;

	DLG_guiData_offlineRes		*	p	=  &m_var.guiData;

	if  (  !p->iw_org  ||  !p->ih_org  )  goto  errLabel;

	sizeAllControls_offlineRes(  m_hWnd,  p  );


	iErr  =  0;

errLabel:

	return  iErr;
}

 //
 BOOL  CDlgOfflineRes::bRefresh(  )
 {
	 BOOL  bRet  =  FALSE;

	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	RECT				rc;
	//int  idc;
	//RECT			*	pRc;

	//
	QY_MESSENGER_ID		idInfo_logicalPeer  =  {0};
	unsigned  char		ucbP2p  =  FALSE;
	QY_MESSENGER_ID		idInfo_req  =  {0};
	
	//
	FUNCS_for_isCliHelp	*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto  errLabel;

	//
	MIS_CNT  *  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
	if  (  !pMisCnt  )  goto  errLabel;

	HWND  hParent  =  m_hWnd;

	 	//
	HWND  hTalker_res  =  NULL;
	if  (  pFuncs->pf_talkToMessenger(  pMisCnt->procOfflineRes.idInfo_resServ.ui64Id,  0,  TRUE,  FALSE,  &hTalker_res  )  )  {
		goto  errLabel;
	}



	//
	if  (  m_var.hDlgTalk_mgr  )
	{
		CHelp_getDlgTalkVar  help_getDlgTalkVar;
		DLG_TALK_var  *  pDlgTalkVar;
		pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  m_var.hDlgTalk_mgr  );
		if  (  !pDlgTalkVar  )  goto  errLabel;
		//
		if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  goto  errLabel;

		//
		idInfo_logicalPeer.ui64Id  =  pDlgTalkVar->addr.idInfo.ui64Id;
		if  (  pDlgTalkVar->addr.uiObjType  !=  CONST_objType_imGrp  )  ucbP2p  =  TRUE;
		idInfo_req.ui64Id  =  pDlgTalkVar->addr.idInfo.ui64Id;

	}
	else  {  //  me
	}



		//
		//
		PROC_offlineRes_retrieve	req;
		memset(  &req,  0,  sizeof(  req  )  );
		req.uiType  =  CONST_imCommType_procOfflineRes;
		req.usSubtype  =  CONST_procOfflineResSubtype_retrieve;
		req.hTool_offlineRes  =  m_hWnd;
		//
		req.req.idInfo_logicalPeer.ui64Id  =  idInfo_logicalPeer.ui64Id;
		req.req.ucbP2p  =  ucbP2p;
		//
		req.req.usIndex_page  =  m_var.usIndex_page;
		req.req.max_usCnt  =  mycountof(  m_var.reses_retrieved.mems  );
		//
		GetDlgItemText(  m_var.guiData.iIDC_EDIT_filterKeywords,  req.req.keyword,  mycountof(  req.req.keyword  )  );
		tTrim(  req.req.keyword  );
		//		
		unsigned  int  uiTranNo_wait  =  0;
		{
			MACRO_prepareForTran(  );
			uiTranNo_wait  =  uiTranNo;
		}

		//
		startProgress(  &pQyMc->gui.progress,  uiTranNo_wait  );
		
		//
		QY_WMBUF_COMM	wmBuf;
		memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
		wmBuf.uiType  =  CONST_qyWmParam_procOfflineRes;
		wmBuf.u.procOfflineRes.ui64Id_req  =  idInfo_req.ui64Id;
		wmBuf.u.procOfflineRes.pPROC_offlineRes_u  =  &req;
		wmBuf.u.procOfflineRes.uiTranNo_wait  =  uiTranNo_wait;
		if  (  !SendMessageTimeout(  hTalker_res,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf,  0,  1000,  NULL  )  )  goto  errLabel;
		//
		//
		int  nStep_finished  =  5;  //  30;
		if  (  showProgress(  &pQyMc->gui.progress,  &pQyMc->cusRes,  hParent,  _T(  "Please waiting"  ),  NULL,  nStep_finished,  -1,  uiTranNo_wait  )  !=  IDOK  )  {		
			goto  errLabel;					  			
		}
		//


		bRefreshBtns(  );


	 bRet  =  TRUE;

errLabel:

	 return  bRet;
 }



 


 int  CDlgOfflineRes::getDisplayStr_res_retrieved(  RES_inProcess  *  pMem,  TCHAR  *  tBuf,  int  cnt  )
 {
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return  -1;

	 _sntprintf(  tBuf,  cnt,  _T(  "%s  ( size: %I64u ) ( %I64u )"  ),  pMem->res.name,  pMem->res.ui64FileLen,  pMem->res.res.idInfo.ui64Id  );		

	 //
	 char  timeBuf[128];
	 char  displayBuf[128];
	 getTimeStr(  pMem->res.tCreationTime,  timeBuf,  mycountof(  timeBuf  )  );
	 qyDisplayTime(  timeBuf,  displayBuf,  mycountof(  displayBuf  )  );
	 _sntprintf(  tBuf,  cnt,  _T(  "%s %S"  ),  tBuf,  displayBuf  );


#if  0
	 _sntprintf(  tBuf,  cnt,  _T(  "%s  ( size: %I64u ) "  ),  pMem->res.name,  pMem->res.ui64FileLen  );				
	 //
	 int  leftBytes  =  50;
	 //
	 int  len  =  lstrlen(  tBuf  );
	 if  (  cnt  >  leftBytes  &&  len  <  leftBytes  )  {
		 int  i;
		 for  (  i  =  len;  i  <  leftBytes;  i  ++  )  {
			  tBuf[i]  =  ' ';
		 }
		 tBuf[leftBytes  -  1]  =  0;
	 }
	 //
	 TCHAR  talkerDesc[128]  =  _T(  ""  );
	 pFuncs->pf_getTalkerDesc(  m_var.pMisCnt,  &pMem->res.res.idInfo,  talkerDesc,  mycountof(  talkerDesc  ),  NULL,  0  );
	 _sntprintf(  tBuf,  cnt,  _T(  "%s     %s ( %I64u )"  ),  tBuf,  talkerDesc,  pMem->res.res.idInfo.ui64Id  );

#endif

	 return  0;

 }


  int  CDlgOfflineRes::getDisplayStr_res_beingProced(  RES_inProcess  *  pMem,  TCHAR  *  tBuf,  int  cnt  )
 {
	 QY_MC  *  pQyMc  =  QY_GET_GBUF(  );


	 tBuf[0]  =  0;
	 if  (  pMem->iStatus  )  {
		 _sntprintf(  tBuf,  cnt,  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskStatusTable  ),  pMem->iStatus  )  );							
		 //
		 if  (  pMem->iStatus  ==  CONST_qyStatus_err  )  {
			 if  (  pMem->usSubtype  ==  CONST_procOfflineResSubtype_del  )  {
				 _sntprintf(  tBuf,  cnt,  _T(  "%s ( %s )"  ),  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_mayBeLocked  )  );
			 }
		 }
	 }
	 //
	 _sntprintf(  tBuf,  cnt,  _T(  "%s %s %s (%I64u)"  ),  tBuf,  qyGetDesByType1(  CONST_procOfflineResSubtypeTable,  pMem->usSubtype  ),  pMem->res.name,  pMem->res.res.idInfo.ui64Id  );					   
	 //

	 
	 return  0;
 }


 BOOL  CDlgOfflineRes::bDisplay(  )
 {
	 int  i;
	 int  tmpiRet;

	TCHAR							tBuf[256]			=	_T(  ""  );
	int								nItems				=	0;
	int								iCurSel				=	0;

	//
	CListCtrl  *  pLv  =  (  CListCtrl  *  )GetDlgItem(  m_var.guiData.iIDC_LIST_offlineRes  );
	if  (  !pLv  )  goto  errLabel;
	pLv->DeleteAllItems(  );


	//
	LVITEM				lvItem;

	memset(  &lvItem,  0,  sizeof(  lvItem  )  );
	lvItem.mask  =  LVIF_TEXT  |  LVIF_IMAGE  |  LVIF_STATE;
	lvItem.iItem  =  nItems;
	lvItem.pszText  =  tBuf;
	lvItem.cchTextMax  =  mycountof(  tBuf  );

	int  index  =  0;
	//
	for  (  i = 0; i < m_var.reses_retrieved.usCnt; i ++  )  {
		RES_inProcess  *  pMem  =  &m_var.reses_retrieved.mems[i];
		
		getDisplayStr_res_retrieved(  pMem,  tBuf,  mycountof(  tBuf  )  );

		lvItem.pszText  =  tBuf;
		lvItem.cchTextMax  =  mycountof(  tBuf  );
		lvItem.iItem  =  i;

		//  tmpiRet  =  ::SendMessage(  hCtrl,  LB_INSERTSTRING,  (  WPARAM  )index,  (  LPARAM  )m_var.reses_retrieved.mems[i].res.name  );
		if (ListView_InsertItem(m_var.listCtrl.hListCtrl, &lvItem) == -1  )  goto  errLabel;

		//
		pMem->index  =  lvItem.iItem;

	}

	for  (  i  =  0;  i<  m_var.reses_beingProced.usCnt;  i  ++  )  {
		 //
		 RES_inProcess  *  pMem  =  &m_var.reses_beingProced.mems[i];
		 //
		 getDisplayStr_res_beingProced(  pMem,  tBuf,  mycountof(  tBuf  )  );
		 lvItem.pszText  =  tBuf;
		 lvItem.cchTextMax  =  mycountof(  tBuf  );
		 lvItem.iItem  =  i  +  m_var.reses_retrieved.usCnt;		 
		 //
		 //  tmpiRet  =  ::SendMessage(  hCtrl,  LB_INSERTSTRING,  (  WPARAM  )index,  (  LPARAM  )tBuf  );
		 if  (  ListView_InsertItem(  m_var.listCtrl.hListCtrl,  &lvItem  )  ==  -1  )  goto  errLabel;

		 //
		 pMem->index  =  lvItem.iItem;

	}




errLabel:

	 return  TRUE;
 }

//
 BOOL  CDlgOfflineRes::bRefreshBtns(  )
 {
	BOOL  bRet  =  FALSE;

	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	RECT				rc;
	int  idc;
	RECT			*	pRc;

	//
	QY_MESSENGER_ID		idInfo_logicalPeer  =  {0};
	unsigned  char		ucbP2p  =  FALSE;
	unsigned  char		ucbGrp  =  FALSE;
	QY_MESSENGER_ID		idInfo_req  =  {0};
	QY_MESSENGER_ID		idInfo_me  =  {0};
	
	//
	FUNCS_for_isCliHelp	*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto  errLabel;

	//
	MIS_CNT  *  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
	if  (  !pMisCnt  )  goto  errLabel;
	idInfo_me.ui64Id  =  pMisCnt->idInfo.ui64Id;

	HWND  hParent  =  m_hWnd;

	if  (  m_var.hDlgTalk_mgr  )
	{
		CHelp_getDlgTalkVar  help_getDlgTalkVar;
		DLG_TALK_var  *  pDlgTalkVar;
		pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  m_var.hDlgTalk_mgr  );
		if  (  !pDlgTalkVar  )  goto  errLabel;
		//
		if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  goto  errLabel;

		//
		idInfo_logicalPeer.ui64Id  =  pDlgTalkVar->addr.idInfo.ui64Id;
		if  (  pDlgTalkVar->addr.uiObjType  !=  CONST_objType_imGrp  )  ucbP2p  =  TRUE;
		else  ucbGrp  =  TRUE;
		idInfo_req.ui64Id  =  pDlgTalkVar->addr.idInfo.ui64Id;

	}

	 //
	 BOOL  bResSelected  =  FALSE;
	 BOOL  bTaskSelected  =  FALSE;

	 if  (  m_var.listCtrl.iSelectItem  >=0  &&  m_var.listCtrl.iSelectItem  <  m_var.reses_retrieved.usCnt  )  {
		 bResSelected  =  TRUE;
	 }
	 else  if  (  m_var.listCtrl.iSelectItem  >=0  &&  m_var.listCtrl.iSelectItem  <  (  m_var.reses_beingProced.usCnt  +  m_var.reses_retrieved.usCnt  )  ) {
		       bTaskSelected  =  TRUE;
	 }


	 if  (  !m_var.hDlgTalk_mgr  ){
		 if  (  m_var.listCtrl.iSelectItem  <  0  ||  m_var.listCtrl.iSelectItem  >  (  m_var.reses_beingProced.usCnt  +  m_var.reses_retrieved.usCnt  )  )  {
			 GetDlgItem(  m_var.guiData.iIDC_BUTTON_delete  )->EnableWindow(  FALSE  );
			 GetDlgItem(  m_var.guiData.iIDC_BUTTON_download  )->EnableWindow(  FALSE  );
		 }
		 else  {
			 GetDlgItem(  m_var.guiData.iIDC_BUTTON_delete  )->EnableWindow(  TRUE  );
			 GetDlgItem(  m_var.guiData.iIDC_BUTTON_download  )->EnableWindow(  TRUE  );
		 }
		 GetDlgItem(  m_var.guiData.iIDC_BUTTON_refresh  )->EnableWindow(  TRUE  );
		 GetDlgItem(  m_var.guiData.iIDC_BUTTON_showAllDownloads  )->EnableWindow(  TRUE  );
		 GetDlgItem(  m_var.guiData.iIDC_BUTTON_upload  )->EnableWindow(  FALSE  );
		 
		 bRet  =  TRUE;  goto errLabel;
	 }

	 if  (  bTaskSelected  )  {
		GetDlgItem(  m_var.guiData.iIDC_BUTTON_delete  )->EnableWindow(  TRUE  );
		GetDlgItem(  m_var.guiData.iIDC_BUTTON_download  )->EnableWindow(  TRUE  );
		GetDlgItem(  m_var.guiData.iIDC_BUTTON_refresh  )->EnableWindow(  TRUE  );
		GetDlgItem(  m_var.guiData.iIDC_BUTTON_showAllDownloads  )->EnableWindow(  TRUE  );
		GetDlgItem(  m_var.guiData.iIDC_BUTTON_upload  )->EnableWindow(  TRUE  );
		bRet  =  TRUE;  goto  errLabel;
	 }

	if  (  bResSelected  )  {

		if  (  ucbGrp  )  {
			if  (  m_var.ucbConfMgr  )  {
				GetDlgItem(  m_var.guiData.iIDC_BUTTON_delete  )->EnableWindow(  TRUE  );
			}
			else  {
			      RES_inProcess  *  pMem  =  &m_var.reses_retrieved.mems[m_var.listCtrl.iSelectItem];
				  if  (  pMem->res.res.idInfo.ui64Id  ==  idInfo_me.ui64Id  ) {
					  GetDlgItem(  m_var.guiData.iIDC_BUTTON_delete  )->EnableWindow(  TRUE  );
				  }
				  else  {
					  GetDlgItem(  m_var.guiData.iIDC_BUTTON_delete  )->EnableWindow(  FALSE  );
				  }
			}
		}
		else  {
			  GetDlgItem(  m_var.guiData.iIDC_BUTTON_delete  )->EnableWindow(  TRUE  );
		}
		GetDlgItem(  m_var.guiData.iIDC_BUTTON_download  )->EnableWindow(  TRUE  );
		GetDlgItem(  m_var.guiData.iIDC_BUTTON_refresh  )->EnableWindow(  TRUE  );
		GetDlgItem(  m_var.guiData.iIDC_BUTTON_showAllDownloads  )->EnableWindow(  TRUE  );
		GetDlgItem(  m_var.guiData.iIDC_BUTTON_upload  )->EnableWindow(  TRUE  );
		bRet  =  TRUE;  goto  errLabel;
	}


		 
	//  not sel
	{
		GetDlgItem(  m_var.guiData.iIDC_BUTTON_delete  )->EnableWindow(  FALSE  );
		GetDlgItem(  m_var.guiData.iIDC_BUTTON_download  )->EnableWindow(  FALSE  );
		GetDlgItem(  m_var.guiData.iIDC_BUTTON_refresh  )->EnableWindow(  TRUE  );
		GetDlgItem(  m_var.guiData.iIDC_BUTTON_showAllDownloads  )->EnableWindow(  TRUE  );
		GetDlgItem(  m_var.guiData.iIDC_BUTTON_upload  )->EnableWindow(  TRUE  );
	 }


	bRet  =  TRUE;

errLabel:

	 return  bRet;
 }

 
 //
 BOOL  CDlgOfflineRes::bDisplay_usIndex_page(  )
 {
	 SetDlgItemInt(  m_var.guiData.iIDC_EDIT_pageNo,  m_var.usIndex_page  +  1  );
	 return  TRUE;
 }

//
void CDlgOfflineRes::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgOfflineRes, CDialogEx)
	ON_MESSAGE(CONST_qyWm_comm, OnQyComm)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_upload, &CDlgOfflineRes::OnBnClickedButtonupload)
	ON_BN_CLICKED(IDC_BUTTON_download, &CDlgOfflineRes::OnBnClickedButtondownload)
	ON_BN_CLICKED(IDC_BUTTON_delete, &CDlgOfflineRes::OnBnClickedButtondelete)
	ON_NOTIFY(NM_CLICK, IDC_LIST_offlineRes, &CDlgOfflineRes::OnNMClickListofflineres)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_offlineRes, &CDlgOfflineRes::OnLvnItemchangedListofflineres)
	ON_BN_CLICKED(IDC_BUTTON_refresh, &CDlgOfflineRes::OnBnClickedButtonrefresh)
	ON_BN_CLICKED(IDC_BUTTON_showAllDownloads, &CDlgOfflineRes::OnBnClickedButtonshowalldownloads)
	ON_BN_CLICKED(IDC_BUTTON_page1, &CDlgOfflineRes::OnBnClickedButtonpage1)
	ON_BN_CLICKED(IDC_BUTTON_nextPage, &CDlgOfflineRes::OnBnClickedButtonnextpage)
	ON_BN_CLICKED(IDC_BUTTON_prevPage, &CDlgOfflineRes::OnBnClickedButtonprevpage)
	ON_BN_CLICKED(IDC_BUTTON_go, &CDlgOfflineRes::OnBnClickedButtongo)
	ON_EN_CHANGE(IDC_EDIT_filterKeywords, &CDlgOfflineRes::OnEnChangeEditfilterkeywords)
	ON_BN_CLICKED(IDCANCEL, &CDlgOfflineRes::OnBnClickedCancel)
END_MESSAGE_MAP()



void CDlgOfflineRes::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//  CDialogEx::OnClose();
	bQuitDlg(  );
}


void CDlgOfflineRes::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//  CDialogEx::OnCancel();
	bQuitDlg(  );
}


//
LRESULT CDlgOfflineRes::OnQyComm(WPARAM wParam, LPARAM  lParam)
{

	long							lRet				=	-1;
	QY_MC						*	pQyMc				=	QY_GET_GBUF(  );
	MC_VAR_isCli				*	pProcInfo			=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )pDlgTalkVar->pMisCnt->pProcInfoParam;
	FUNCS_for_isCliHelp			*	pFuncs				=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
		
	
	QY_WMBUF_COMM				*	pComm				=	(  QY_WMBUF_COMM  *  )lParam;
	TCHAR  tBuf_status[128]  =  _T(  ""  );

	 				
	if  (  !pComm  )  return  -1;

	switch  (  pComm->uiType  )  {
			case  CONST_misMsgType_input:  {
				  MIS_MSG_INPUT				*	pMsg				=   (  MIS_MSG_INPUT  *  )pComm;
				  IM_CONTENTU					*	pContent			=	NULL;	
				  int								i;
				  int								tmpiRet;
				  
				  //
				  if  (  isUcFlgRouteTalkData(  pMsg->ucFlg  )  
					  //||  isUcFlgTalkData(  pMsg->ucFlg  )  
					  )  pContent  =  (  IM_CONTENTU  * )pMsg->data.buf;		
				  else  pContent  =  (  IM_CONTENTU  *  )&pMsg->data;

				  //
				  if  (  pContent->uiType  !=  CONST_imCommType_procOfflineRes  )  goto  errLabel;

				  //
				  if  (  pContent->procOfflineResU.common.usSubtype  ==  CONST_procOfflineResSubtype_retrieve  )  {
					
					  //
					  m_var.reses_retrieved.usCnt  =  0;
					  int  n  =  min(  pContent->procOfflineResU.retrieve.resp.usCnt,  mycountof(  pContent->procOfflineResU.retrieve.resp.mems  )  );
					  for  (  i  =  0;  i  <  n;  i  ++  )  {
						  m_var.reses_retrieved.mems[i].res  =  pContent->procOfflineResU.retrieve.resp.mems[i];
					  }
					  m_var.reses_retrieved.usCnt  =  n;

					  //				
					  bDisplay(  );
					  break;
				  }
				  if  (  pContent->procOfflineResU.common.usSubtype  ==  CONST_procOfflineResSubtype_del  )  {
					  //
					  RES_inProcess  *  pMem_task  =  NULL;
					  //
					  if  (  !isUcFlgResp(  pMsg->ucFlg  )  )  {
						  #ifdef  __DEBUG__
								  traceLog(  _T(  "CDlgOfflineRes_OnQyComm_msgInput_profOfflineRes_del failed, not resp"  )  );
						  #endif
						  goto  errLabel;
					  }
					  //
					  for  (  i  =  0;  i  <  m_var.reses_beingProced.usCnt;  i  ++  )  {
						   pMem_task  =  &m_var.reses_beingProced.mems[i];
						   //
						   if  (  pMem_task->uiTranNo_real  !=  pMsg->uiTranNo  )  continue;
						   //
						   if  (  isRcOk(  pMsg->usCode  )  )  pMem_task->iStatus  =  CONST_imTaskStatus_sendFinished;
						   else  pMem_task->iStatus  =  CONST_qyStatus_err;
						   //
						   break;
					  }
					  if  (  i  ==  m_var.reses_beingProced.usCnt  )  goto  errLabel;
					  //					  		
					  TCHAR  tBuf_mem[128]  =  _T(  ""  );
					  this->getDisplayStr_res_beingProced(  pMem_task,  tBuf_mem,  mycountof(  tBuf_mem  )  );				  
					  //

				  
					  //			
					  CListCtrl  *  pLv  =  (  CListCtrl  *  )GetDlgItem(  m_var.guiData.iIDC_LIST_offlineRes  );
					  if  (  !pLv  )  goto  errLabel;
					  				  
					  pLv->SetItemText(  pMem_task->index,  0,  tBuf_mem  );

					  break;
				  }

			
				  }
				  break;
			case  CONST_misMsgType_taskStatus:  {
				  MIS_MSG_taskStatus  *  pMsgTaskStatus  =  (  MIS_MSG_taskStatus  *  )pComm;
				  //
				  RES_inProcess  *  pMem;
				  int  i;
				  for  (  i  =  0;  i  <  m_var.reses_beingProced.usCnt;  i  ++  )  {
					   pMem  =  &m_var.reses_beingProced.mems[i];
					   if  (  pMem->iTaskId  ==  pMsgTaskStatus->iTaskId  )  {
						   break;
					   }
				  }
				  if  (  i  ==  m_var.reses_beingProced.usCnt  )  {
					  showInfo_open0(  0,  0,  _T(  "offlineRes: taskStatus err, not a being processed task"  )  );
					  goto  errLabel;
				  }
				  //
				  pMem->iStatus  =  pMsgTaskStatus->iStatus;
				  pMem->dwTickCnt_modified  =  GetTickCount(  );
				  //
				  switch  (  pMsgTaskStatus->iStatus  )  {	
						  case  CONST_imTaskStatus_sending:
						  case  CONST_imTaskStatus_receiving:
							    M_getTransferFileStatus_str(  pMsgTaskStatus->u.transferFileStatus,  tBuf_status,  mycountof(  tBuf_status  )  );
								//
								pMem->transferFileStatus  =  pMsgTaskStatus->u.transferFileStatus; 
								//
							    break;
								//
						  case  CONST_imTaskStatus_sendFinished:						
						  case  CONST_imTaskStatus_recvFinished:
						  case  CONST_imTaskStatus_canceledBySender:
						  case  CONST_imTaskStatus_canceledByReceiver:
						  case  CONST_imTaskStatus_autoCanceledByReceiver:	//  2014/07/30
						  default:
							     //
							     //
							     _sntprintf(  tBuf_status,  mycountof(  tBuf_status  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskStatusTable  ),  pMsgTaskStatus->iStatus  )  );							
								 //
								 #ifdef   __DEBUG__
										  showInfo_open0(  0,   _T(  "OfflineRes.Comm"  ),  tBuf_status  );
								 #endif
								 //
								 break;
				  }
				  //
				  TCHAR  tBuf_mem[128]  =  _T(  ""  );
				  this->getDisplayStr_res_beingProced(  pMem,  tBuf_mem,  mycountof(  tBuf_mem  )  );
				  //
				  TCHAR  tBuf1[128];
				  _sntprintf( tBuf1,  mycountof(  tBuf1  ),  _T(  "%s %s"  ),  tBuf_status,  tBuf_mem  );
				  //
				  CListCtrl  *  pLv  =  (  CListCtrl  *  )GetDlgItem(  m_var.guiData.iIDC_LIST_offlineRes  );
				  if  (  !pLv  )  goto  errLabel;

				  pLv->SetItemText(  pMem->index,  0,  tBuf1  );
				  }
				  break;
			case  CONST_misMsgType_task:  {
				  MIS_MSG_TASK  *  pMsgTask  =  (  MIS_MSG_TASK  *  )pComm;
				  //
				  IM_CONTENTU  *  pContent  =  M_getMsgContent(  pMsgTask->ucFlg,  &pMsgTask->data  );
				  //
				  if  (  pContent->uiType  ==  CONST_imCommType_transferFileReq  )  {
					  int  i;
					  for  (  i  =  0;  i  <  m_var.reses_beingProced.usCnt;  i  ++  )  {
						   RES_inProcess  *  pMem  =  &m_var.reses_beingProced.mems[i];
						   if  (  pMem->iTaskId  )  continue;
						   if  (  !lstrcmpi(  pMem->res.name,  pContent->transferFileReq.fileName  )  )  {
							   pMem->iTaskId  =  pMsgTask->iTaskId;
							   //
							   break;
						   }					  
					  }
					  if  (  i  ==  m_var.reses_beingProced.usCnt  )  {
						  goto  errLabel;
					  }
					  }
				  else  {
					    goto  errLabel;
				  }

				  }
				  break;
			default:
					break;
		
	}


	lRet  =  QY_RC_WMOK;

errLabel:

#ifdef  __DEBUG__
	    if   (  lRet  !=  QY_RC_WMOK  )  {
			 int  ii  =  0;
		}
		//
		traceLogA(  "CDlgOfflineRes::OnQyComm leaves with iErr %d",  lRet  );
#endif

	return  lRet;
}


void CDlgOfflineRes::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::PostNcDestroy();

	if  (  m_var.hDlgTalk_mgr  )  {
		//  ::PostMessage(  m_var.hDlgTalk_mgr,  WM_SIZE,  0,  0  );
		askToRefreshSize_mgr(  m_var.hDlgTalk_mgr  );
	}

	delete  this;
}



BOOL CDlgOfflineRes::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	int					iErr			=	-1;
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	RECT				rc;
	int  idc;
	RECT			*	pRc;

	//
	QY_MESSENGER_ID		idInfo_logicalPeer  =  {0};
	unsigned  char		ucbP2p  =  FALSE;
	QY_MESSENGER_ID		idInfo_req  =  {0};
	
	//
	FUNCS_for_isCliHelp	*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto  errLabel;


	cusDlgRes(  0,  &pQyMc->cusRes,  m_hWnd,  IDD  );

	DLG_guiData_offlineRes  *  p  =  &m_var.guiData;

	::GetClientRect(  m_hWnd,  &rc  );

	p->iw_org  =  rc.right  -  rc.left;  
	p->ih_org  =  rc.bottom  -  rc.top;

	if  (  !p->iw_org  ||  !p->ih_org  )  goto  errLabel;

	idc  =  p->iIDC_BUTTON_delete;
	pRc  =  &p->rcIDC_BUTTON_delete;	
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  pRc  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )pRc,  2  );

	idc  =  p->iIDC_BUTTON_download;
	pRc  =  &p->rcIDC_BUTTON_download;	
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  pRc  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )pRc,  2  );

	idc  =  p->iIDC_BUTTON_refresh;
	pRc  =  &p->rcIDC_BUTTON_refresh;	
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  pRc  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )pRc,  2  );

	idc  =  p->iIDC_BUTTON_upload;
	pRc  =  &p->rcIDC_BUTTON_upload;	
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  pRc  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )pRc,  2  );

	idc  =  p->iIDC_LIST_offlineRes;
	pRc  =  &p->rcIDC_LIST_offlineRes;
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  pRc  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )pRc,  2  );

	//  2015/08/12
	idc  =  p->iIDC_BUTTON_page1;
	pRc  =  &p->rcIDC_BUTTON_page1;
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  pRc  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )pRc,  2  );

	idc  =  p->iIDC_BUTTON_nextPage;
	pRc  =  &p->rcIDC_BUTTON_nextPage;
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  pRc  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )pRc,  2  );

	idc  =  p->iIDC_BUTTON_prevPage;
	pRc  =  &p->rcIDC_BUTTON_prevPage;
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  pRc  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )pRc,  2  );

	idc  =  p->iIDC_EDIT_pageNo;
	pRc  =  &p->rcIDC_EDIT_pageNo;
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  pRc  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )pRc,  2  );

	idc  =  p->iIDC_BUTTON_go;
	pRc  =  &p->rcIDC_BUTTON_go;
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  pRc  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )pRc,  2  );

	idc  =  p->iIDC_STATIC_filterKeywords;
	pRc  =  &p->rcIDC_STATIC_filterKeywords;
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  pRc  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )pRc,  2  );

	idc  =  p->iIDC_EDIT_filterKeywords;
	pRc  =  &p->rcIDC_EDIT_filterKeywords;
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  pRc  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )pRc,  2  );
	//
	idc  =  p->iIDC_BUTTON_showAllDownloads;
	pRc  =  &p->rcIDC_BUTTON_showAllDownloads;	
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  pRc  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )pRc,  2  );
	//
	idc  =  p->iIDCANCEL;
	pRc  =  &p->rcIDCANCEL;
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  pRc  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )pRc,  2  );


	//  2015/08/04
#ifndef  __DEBUG__
		 
#endif

	//
	m_var.listCtrl.hListCtrl  =  ::GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_LIST_offlineRes  );
	myListCtrl_ModifyStyle( m_var.listCtrl.hListCtrl,  LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL,  0   );
	myListCtrl_SetExtendedStyle( m_var.listCtrl.hListCtrl,  LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );
	int					i;

	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvc.iSubItem	=	0;
	lvc.pszText		=	_T(  "Files"  );
	lvc.cx			=	1000;//  LVS_EX_AUTOSIZECOLUMNS;               // Width of column in pixels.
	lvc.fmt			=	LVCFMT_LEFT;
	myListCtrl_InsertColumn(  m_var.listCtrl.hListCtrl,  0,  &lvc  );
	
	m_var.listCtrl.iSelectItem  =  -1;
	//
	p->bInited  =  TRUE;

	if  (  IsWindow(  m_var.hDlgTalk_mgr  )  )  {
		 makeWndNoBorder(  m_hWnd,  FALSE,  NULL,  NULL  );
	}

	MIS_CNT  *  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
	if  (  !pMisCnt  )  goto  errLabel;
	//m_var.pMisCnt  =  pMisCnt;
	//
	HWND  hParent  =  m_hWnd;


	//
	unsigned  int  uiTranNo  =  0;	
	if  (  sndProcOfflineResReq_qmc(  pMisCnt,  TRUE,  &uiTranNo  )  )  {
		showInfo_open0(  0,  0,  _T(  "dlgOfflineRes.OnInitDialog failed, sndProcOfflineResReq failed"  )  );
		goto  errLabel;
	}

	//
	if  (  showProgress(  &pQyMc->gui.progress,  &pQyMc->cusRes,  hParent,  _T(  "Please waiting"  ),  NULL,  30,  -1,  uiTranNo  )  !=  IDOK  )  {		
		//  2017/09/23
		showInfo_open0(  0,  0,  _T(  "dlgOfflineRes.OnInitDialog failed, showProgress failed"  )  );
		goto  errLabel;					  		
	}
	
	if  (  !pMisCnt->procOfflineRes.idInfo_resServ.ui64Id  )  {
		myMessageBox(  hParent,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotConnectFileServer  ),  _T(  "www.qycx.com"  ),  MB_OK  );		//  _T(  "无法获取通知或文件，因为无法连接文件服务器！"  )
		goto  errLabel;
	}
	//
#ifdef  __DEBUG__
		
#endif

	//
	m_var.usIndex_page  =  0;
	this->bDisplay_usIndex_page(  );

	//
	bRefresh(  );



	iErr  =  0;

errLabel:


	if  (  !m_var.guiData.bInited  ||  iErr  )  {
		//  EndDialog(  -1  );
		PostMessage(  WM_CLOSE  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgOfflineRes::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	DLG_guiData_offlineRes		*	p	=  &m_var.guiData;

	if  (  !p->iw_org  ||  !p->ih_org  )  return;
	sizeAllControls_offlineRes(  m_hWnd,  p  );

}


//
#if  0
void CDlgOfflineRes::iiOnBnClickedButtonupload()
{
	// TODO: Add your control notification handler code here
	int					iErr  =  -1;		
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	RECT				rc;
	int  idc;
	RECT			*	pRc;
	CQyString			pathCStr;

	//
	FUNCS_for_isCliHelp	*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto  errLabel;
	
	MIS_CNT  *  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
	if  (  !pMisCnt  )  goto  errLabel;	
	//
	HWND  hParent  =  m_hWnd;


	//
	HWND  hTalker_res  =  NULL;
	if  (  pFuncs->pf_talkToMessenger(  pMisCnt->procOfflineRes.idInfo_resServ.ui64Id,  TRUE,  FALSE,  &hTalker_res  )  )  {
		goto  errLabel;
	}



	//
					  LPCTSTR							lpszDefExt  =	TEXT("*\0");
				  LPCTSTR							lpszFilter	=	CONST_FILE_FILTER_allFiles;
				  LPCTSTR							title		=	TEXT("Send File...\0");
				  DWORD								dwFlags     =	OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;

				  
				  //  2015/06/06					
				  if  (  !bUse_imObjView_as_guiWnd(  )  )  {
					  if  (  bApp_ts_3d(  pQyMc  )  )  {
						  GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
						  if  (  !IsWindow(  pGBuf->hWall_d3d  )  )  goto  errLabel;
						  hParent  =  pGBuf->hWall_d3d;					  
					  }
				  }


				  //
				  if  (  qyBrowseForFile(  hParent,  TRUE,  lpszDefExt,  dwFlags,  CONST_FILE_FILTER_allFiles,  title,  NULL,  pQyMc,  pathCStr  )  )  goto  errLabel;



	//
	{
		CHelp_getDlgTalkVar  help_getDlgTalkVar;
		DLG_TALK_var  *  pDlgTalkVar;
		pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  m_var.hDlgTalk_mgr  );
		if  (  !pDlgTalkVar  )  goto  errLabel;
		//
		if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  goto  errLabel;
		//
		//
		PROC_offlineRes_upload	req;
		memset(  &req,  0,  sizeof(  req  )  );
		req.uiType  =  CONST_imCommType_procOfflineRes;
		req.usSubtype  =  CONST_procOfflineResSubtype_upload;
		req.hTool_offlineRes  =  m_hWnd;
		//
		safeTcsnCpy(  pathCStr,  req.fullFileName,  mycountof(  req.fullFileName  )  );
		//
		req.idInfo_logicalPeer.ui64Id  =  pDlgTalkVar->addr.idInfo.ui64Id;
		//
		
		//
		if  (  m_var.reses_beingProced.usCnt  >=  mycountof(  m_var.reses_beingProced.mems  )  )  goto  errLabel;
		RES_inProcess  *  pMem  =  &m_var.reses_beingProced.mems[m_var.reses_beingProced.usCnt];
		memset(  pMem,  0,  sizeof(  pMem[0]  )  );
		safeTcsnCpy(  req.fullFileName,  pMem->res.name,  mycountof(  pMem->res.name  )  );
		pMem->usSubtype  =  req.usSubtype;
		m_var.reses_beingProced.usCnt  ++  ;
		//
		int  index  =  m_var.reses_retrieved.usCnt  +  m_var.reses_beingProced.usCnt  -  1;
		HWND  hCtrl  =  ::GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_LIST_offlineRes  );
		::SendMessage(  hCtrl,  LB_INSERTSTRING,  (  WPARAM  )index,  (  LPARAM  )pMem->res.name  );
		
		//
		QY_WMBUF_COMM	wmBuf;
		memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
		wmBuf.uiType  =  CONST_qyWmParam_procOfflineRes;
		wmBuf.u.procOfflineRes.ui64Id_req  =  pDlgTalkVar->addr.idInfo.ui64Id;
		wmBuf.u.procOfflineRes.pPROC_offlineRes_u  =  &req;
		wmBuf.u.procOfflineRes.uiTranNo_wait  =  0;
		if  (  !SendMessageTimeout(  hTalker_res,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf,  0,  1000,  NULL  )  )  goto  errLabel;
		//
		pMem->iTaskId  =  wmBuf.u.procOfflineRes.iTaskId;		
		//
		int  i;
		i  =  0;


	}

	//
	bDisplay(  );
	
	//
	iErr  =  0;

errLabel:
		return;
}

#else


//
__declspec(  dllexport  )  void  dlgOfflineRes_upload(  HWND  hParent,  HWND  hDlg_offlineRes,  LPCTSTR  fileName  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your control notification handler code here
	int					iErr  =  -1;		
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	RECT				rc;
	int  idc;
	RECT			*	pRc;

	//
	FUNCS_for_isCliHelp	*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto  errLabel;
	
	MIS_CNT  *  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
	if  (  !pMisCnt  )  goto  errLabel;	

	//
	CDlgOfflineRes  *  pDlg  =  (  CDlgOfflineRes  *  )CWnd::FromHandlePermanent(  hDlg_offlineRes  );
	if  (  !pDlg  )  goto  errLabel;

	HWND  m_hWnd  =  hDlg_offlineRes;
	DlgOfflineRes_var  &m_var  =  pDlg->m_var;

	//
	HWND  hTalker_res  =  NULL;
	if  (  pFuncs->pf_talkToMessenger(  pMisCnt->procOfflineRes.idInfo_resServ.ui64Id, 0, TRUE,  FALSE,  &hTalker_res  )  )  {
		goto  errLabel;
	}
	
	//
	{
		CHelp_getDlgTalkVar  help_getDlgTalkVar;
		DLG_TALK_var  *  pDlgTalkVar;
		pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  m_var.hDlgTalk_mgr  );
		if  (  !pDlgTalkVar  )  goto  errLabel;
		//
		if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  goto  errLabel;
		//
		//
		PROC_offlineRes_upload	req;
		memset(  &req,  0,  sizeof(  req  )  );
		req.uiType  =  CONST_imCommType_procOfflineRes;
		req.usSubtype  =  CONST_procOfflineResSubtype_upload;
		req.hTool_offlineRes  =  m_hWnd;
		//
		safeTcsnCpy(  fileName,  req.fullFileName,  mycountof(  req.fullFileName  )  );
		//
		req.idInfo_logicalPeer.ui64Id  =  pDlgTalkVar->addr.idInfo.ui64Id;
		//
		
		//
		if  (  m_var.reses_beingProced.usCnt  >=  mycountof(  m_var.reses_beingProced.mems  )  )  goto  errLabel;
		RES_inProcess  *  pMem  =  &m_var.reses_beingProced.mems[m_var.reses_beingProced.usCnt];
		memset(  pMem,  0,  sizeof(  pMem[0]  )  );
		safeTcsnCpy(  req.fullFileName,  pMem->res.name,  mycountof(  pMem->res.name  )  );
		pMem->usSubtype  =  req.usSubtype;
		m_var.reses_beingProced.usCnt  ++  ;
		//
		int  index  =  m_var.reses_retrieved.usCnt  +  m_var.reses_beingProced.usCnt  -  1;
		HWND  hCtrl  =  ::GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_LIST_offlineRes  );
		::SendMessage(  hCtrl,  LB_INSERTSTRING,  (  WPARAM  )index,  (  LPARAM  )pMem->res.name  );
		
		//
		QY_WMBUF_COMM	wmBuf;
		memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
		wmBuf.uiType  =  CONST_qyWmParam_procOfflineRes;
		wmBuf.u.procOfflineRes.ui64Id_req  =  pDlgTalkVar->addr.idInfo.ui64Id;
		wmBuf.u.procOfflineRes.pPROC_offlineRes_u  =  &req;
		wmBuf.u.procOfflineRes.uiTranNo_wait  =  0;
		if  (  !SendMessageTimeout(  hTalker_res,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf,  0,  1000,  NULL  )  )  goto  errLabel;
		//
		pMem->iTaskId  =  wmBuf.u.procOfflineRes.iTaskId;		
		//
		int  i;
		i  =  0;


	}

	//
	pDlg->bDisplay(  );
	
	//
	iErr  =  0;

errLabel:

	return;
}

//
void CDlgOfflineRes::OnBnClickedButtonupload()
{
	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	CQyString			pathCStr;
	
	LPCTSTR							lpszDefExt  =	TEXT("*\0");
	LPCTSTR							lpszFilter	=	CONST_FILE_FILTER_allFiles;
	LPCTSTR							title		=	TEXT("Send File...\0");
	DWORD								dwFlags     =	OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;
	
	//
	HWND  hParent  =  m_hWnd;
	
	//  2015/06/06					
	if  (  !pProcInfo->bUse_imObjView_as_guiWnd(  )  )  {
					  if  (  bApp_ts_3d(  pQyMc  )  )  {
						  GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
						  if  (  !IsWindow(  pGBuf->hWall_d3d  )  )  goto  errLabel;
						  hParent  =  pGBuf->hWall_d3d;					  
					  }
	}
		
	//
	if  (  qyBrowseForFile(  hParent,  TRUE,  lpszDefExt,  dwFlags,  CONST_FILE_FILTER_allFiles,  title,  NULL,  pQyMc,  pathCStr  )  )  goto  errLabel;

	//
	dlgOfflineRes_upload(  hParent,  m_hWnd,  pathCStr  );

	iErr  =  0;

errLabel:
		
	return;
}

//
#endif

//
void CDlgOfflineRes::OnBnClickedButtondownload()
{
	// TODO: Add your control notification handler code here
	int					iErr  =  -1;		
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	RECT				rc;
	int  idc;
	RECT			*	pRc;
	
		//
	QY_MESSENGER_ID		idInfo_logicalPeer  =  {0};
	unsigned  char		ucbP2p  =  FALSE;
	QY_MESSENGER_ID		idInfo_req  =  {0};


	//
	FUNCS_for_isCliHelp	*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto  errLabel;
	
	MIS_CNT  *  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
	if  (  !pMisCnt  )  goto  errLabel;	
	//
	HWND  hParent  =  m_hWnd;

	TCHAR							tBuf[128];
	int								nItems				=	0;

	//
	LVITEM				lvItem;

	memset(  &lvItem,  0,  sizeof(  lvItem  )  );
	lvItem.mask  =  LVIF_TEXT  |  LVIF_IMAGE  |  LVIF_STATE;
	lvItem.iItem  =  nItems;
	lvItem.pszText  =  tBuf;
	lvItem.cchTextMax  =  mycountof(  tBuf  );

	if  (  m_var.listCtrl.iSelectItem  <  0  ||  m_var.listCtrl.iSelectItem  >=  m_var.reses_retrieved.usCnt  )  goto  errLabel;
	RES_inProcess  *  pMem  =  &m_var.reses_retrieved.mems[m_var.listCtrl.iSelectItem];

	//
	HWND  hTalker_res  =  NULL;
	BOOL  bNeedNotShowWnd  =  TRUE;
#ifdef  __DEBUG__
		//bNeedNotShowWnd  =  FALSE;
#endif
	//
	if  (  pFuncs->pf_talkToMessenger(  pMisCnt->procOfflineRes.idInfo_resServ.ui64Id,  0,  bNeedNotShowWnd,  FALSE,  &hTalker_res  )  )  {
		goto  errLabel;
	}
	
	

	//
	if  (  m_var.hDlgTalk_mgr  )
	{
		CHelp_getDlgTalkVar  help_getDlgTalkVar;
		DLG_TALK_var  *  pDlgTalkVar;
		pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  m_var.hDlgTalk_mgr  );
		if  (  !pDlgTalkVar  )  goto  errLabel;
		//
		if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  goto  errLabel;

		//
		idInfo_logicalPeer.ui64Id  =  pDlgTalkVar->addr.idInfo.ui64Id;
		if  (  pDlgTalkVar->addr.uiObjType  !=  CONST_objType_imGrp  )  ucbP2p  =  TRUE;
		idInfo_req.ui64Id  =  pDlgTalkVar->addr.idInfo.ui64Id;

	}
	else  {
	}


		//
		//
		PROC_offlineRes_download	req;
		memset(  &req,  0,  sizeof(  req  )  );
		req.uiType  =  CONST_imCommType_procOfflineRes;
		req.usSubtype  =  CONST_procOfflineResSubtype_download;
		req.hTool_offlineRes  =  m_hWnd;
		//
		safeTcsnCpy(  pMem->res.name,  req.fileName,  mycountof(  req.fileName  )  );
		req.idInfo_sender.ui64Id  =  pMem->res.res.idInfo.ui64Id;
		req.tCreationTime  =  pMem->res.tCreationTime;
		//
		req.idInfo_logicalPeer.ui64Id  =  idInfo_logicalPeer.ui64Id;
		
		//
		{
		if  (  m_var.reses_beingProced.usCnt  >=  mycountof(  m_var.reses_beingProced.mems  )  )  goto  errLabel;
		RES_inProcess  *  pMem  =  &m_var.reses_beingProced.mems[m_var.reses_beingProced.usCnt];
		memset(  pMem,  0,  sizeof(  pMem[0]  )  );
		safeTcsnCpy(  req.fileName,  pMem->res.name,  mycountof(  pMem->res.name  )  );
		pMem->usSubtype  =  CONST_procOfflineResSubtype_download;
		m_var.reses_beingProced.usCnt  ++  ;
		}

		//
		QY_WMBUF_COMM	wmBuf;
		memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
		wmBuf.uiType  =  CONST_qyWmParam_procOfflineRes;
		wmBuf.u.procOfflineRes.ui64Id_req  =  idInfo_req.ui64Id;
		wmBuf.u.procOfflineRes.pPROC_offlineRes_u  =  &req;
		wmBuf.u.procOfflineRes.uiTranNo_wait  =  0;
		if  (  !SendMessageTimeout(  hTalker_res,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf,  0,  1000,  NULL  )  )  goto  errLabel;
		//
		int  i;
		i  =  0;

		//
		bDisplay(  );

	
	
	//
	iErr  =  0;

errLabel:
		return;

}

void CDlgOfflineRes::OnBnClickedButtonrefresh()
{
	// TODO: Add your control notification handler code here
	//
	bRefresh(  );
}


void CDlgOfflineRes::OnBnClickedButtondelete()
{
	// TODO: Add your control notification handler code here
		int					iErr  =  -1;		
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	RECT				rc;
	int  idc;
	RECT			*	pRc;
	
		//
	QY_MESSENGER_ID		idInfo_logicalPeer  =  {0};
	unsigned  char		ucbP2p  =  FALSE;
	QY_MESSENGER_ID		idInfo_req  =  {0};


	//
	FUNCS_for_isCliHelp	*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto  errLabel;
	
	MIS_CNT  *  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
	if  (  !pMisCnt  )  goto  errLabel;	
	//
	HWND  hParent  =  m_hWnd;

	TCHAR							tBuf[128];
	int								nItems				=	0;
		
	//
	HWND  hTalker_res  =  NULL;
	if  (  pFuncs->pf_talkToMessenger(  pMisCnt->procOfflineRes.idInfo_resServ.ui64Id,  0,  TRUE,  FALSE,  &hTalker_res  )  )  {
		goto  errLabel;
	}



	//
	if  (  m_var.hDlgTalk_mgr  )
	{
		CHelp_getDlgTalkVar  help_getDlgTalkVar;
		DLG_TALK_var  *  pDlgTalkVar;
		pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  m_var.hDlgTalk_mgr  );
		if  (  !pDlgTalkVar  )  goto  errLabel;
		//
		if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  goto  errLabel;

		//
		idInfo_logicalPeer.ui64Id  =  pDlgTalkVar->addr.idInfo.ui64Id;
		if  (  pDlgTalkVar->addr.uiObjType  !=  CONST_objType_imGrp  )  ucbP2p  =  TRUE;
		idInfo_req.ui64Id  =  pDlgTalkVar->addr.idInfo.ui64Id;

	}
	else  {  //  me
	}






	//
	LVITEM				lvItem;

	memset(  &lvItem,  0,  sizeof(  lvItem  )  );
	lvItem.mask  =  LVIF_TEXT  |  LVIF_IMAGE  |  LVIF_STATE;
	lvItem.iItem  =  nItems;
	lvItem.pszText  =  tBuf;
	lvItem.cchTextMax  =  mycountof(  tBuf  );

	if  (  m_var.listCtrl.iSelectItem  >=  0  &&  m_var.listCtrl.iSelectItem  <  m_var.reses_retrieved.usCnt  )  {
		RES_inProcess  *  pMem_res  =  &m_var.reses_retrieved.mems[m_var.listCtrl.iSelectItem];
		//
		if  (  myMessageBox(  hParent,  _T(  "Are you sure to delete?"  ),  _T(  "www.qycx.com"  ),  MB_YESNO  )  !=  IDYES  )  goto  errLabel;
		//

				//
		//
		PROC_offlineRes_del	req;
		memset(  &req,  0,  sizeof(  req  )  );
		req.uiType  =  CONST_imCommType_procOfflineRes;
		req.usSubtype  =  CONST_procOfflineResSubtype_del;
		req.hTool_offlineRes  =  m_hWnd;
		//
		req.idInfo_logicalPeer.ui64Id  =  idInfo_logicalPeer.ui64Id;
		//
		safeTcsnCpy(  pMem_res->res.name,  req.fileName,  mycountof(  req.fileName  )  );
		req.idInfo_sender.ui64Id  =  pMem_res->res.res.idInfo.ui64Id;
		req.tCreationTime  =  pMem_res->res.tCreationTime;
		
		
		//
		RES_inProcess  *  pMem_task  =  NULL;
		
		if  (  m_var.reses_beingProced.usCnt  >=  mycountof(  m_var.reses_beingProced.mems  )  )  goto  errLabel;
		pMem_task  =  &m_var.reses_beingProced.mems[m_var.reses_beingProced.usCnt];
		memset(  pMem_task,  0,  sizeof(  pMem_task[0]  )  );
		safeTcsnCpy(  req.fileName,  pMem_task->res.name,  mycountof(  pMem_task->res.name  )  );
		pMem_task->res.res.idInfo.ui64Id  =  req.idInfo_sender.ui64Id;
		//
		pMem_task->usSubtype  =  CONST_procOfflineResSubtype_del;
		m_var.reses_beingProced.usCnt  ++  ;
		



		//		
		unsigned  int  uiTranNo_wait  =  0;
		{
			MACRO_prepareForTran(  );
			uiTranNo_wait  =  uiTranNo;
		}

		//
		startProgress(  &pQyMc->gui.progress,  uiTranNo_wait  );
		
		//
		QY_WMBUF_COMM	wmBuf;
		memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
		wmBuf.uiType  =  CONST_qyWmParam_procOfflineRes;
		wmBuf.u.procOfflineRes.ui64Id_req  =  idInfo_req.ui64Id;
		wmBuf.u.procOfflineRes.pPROC_offlineRes_u  =  &req;
		wmBuf.u.procOfflineRes.uiTranNo_wait  =  uiTranNo_wait;
		if  (  !SendMessageTimeout(  hTalker_res,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf,  0,  1000,  NULL  )  )  goto  errLabel;
		//
		if  (  !wmBuf.u.procOfflineRes.uiTranNo_real  )  goto  errLabel;
		pMem_task->uiTranNo_real  =  wmBuf.u.procOfflineRes.uiTranNo_real;
		//
		if  (  showProgress(  &pQyMc->gui.progress,  &pQyMc->cusRes,  hParent,  _T(  "Please waiting"  ),  NULL,  30,  -1,  uiTranNo_wait  )  !=  IDOK  )  {		
			goto  errLabel;					  			
		}

	}
	else  if  (  m_var.listCtrl.iSelectItem  >=  m_var.reses_retrieved.usCnt  &&  m_var.listCtrl.iSelectItem  <  m_var.reses_retrieved.usCnt  +  m_var.reses_beingProced.usCnt  )  {
			  //
			  if  (  myMessageBox(  hParent,  _T(  "Are you sure to cancel the task?"  ),  _T(  "www.qycx.com"  ),  MB_YESNO  )  !=  IDYES  )  goto  errLabel;
			  //
			  int  i;
			  i  =  m_var.listCtrl.iSelectItem  -  m_var.reses_retrieved.usCnt;
			  for  (  ;  i  <  m_var.reses_beingProced.usCnt  -  1;  i  ++  )  {
				   RES_inProcess  *  pMem  =  &m_var.reses_beingProced.mems[i]; 			
				   pMem[0]  =  pMem[1];
			  }
			  m_var.reses_beingProced.usCnt  --  ;
			  //

	}


	//
	if  (  m_var.listCtrl.iSelectItem  < 0  ||  m_var.listCtrl.iSelectItem  >=  m_var.reses_retrieved.usCnt  +  m_var.reses_beingProced.usCnt  )  {
		m_var.listCtrl.iSelectItem  =  -1;
	}



			  //
			  bDisplay(  );





errLabel:
	return;
}


void CDlgOfflineRes::OnBnClickedButtonshowalldownloads()
{
	// TODO: Add your control notification handler code here
	int  iErr  =  -1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  goto  errLabel;

	//
	TCHAR  *  pDir  =  pProcInfo->cfg.policy.dirToSaveFile;
	
	if  (  bDir(  pDir  )  )  {		//  
		ShellExecute(  NULL,  _T(  "open"  ),  pDir,  _T(  ""  ),  NULL,  SW_SHOW  );			
	}

	iErr  =  0;

errLabel:
	return;
}


void CDlgOfflineRes::OnNMClickListofflineres(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	//
	LPNMITEMACTIVATE pNMLV  =  pNMItemActivate;

	//
	if  (  (  pNMLV->iItem  >= 0  )  )  {
		m_var.listCtrl.iSelectItem  =  pNMLV->iItem;
		}
	else  m_var.listCtrl.iSelectItem  =  -1;

	bRefreshBtns(  );
	*pResult = 0;
}

void CDlgOfflineRes::OnLvnItemchangedListofflineres(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

#if  0
	if  (  (  pNMLV->iItem  >= 0  )
		 &&	 (  pNMLV->uNewState  ==  (  LVIS_SELECTED | LVIS_FOCUSED  )  )  )  {
			 m_var.listCtrl.iSelectItem  =  pNMLV->iItem;
	 }
	else  m_var.listCtrl.iSelectItem  =  -1;
#endif

	//
	CListCtrl  *  pListCtrl  =  (  CListCtrl  *  )GetDlgItem(  m_var.guiData.iIDC_LIST_offlineRes  );		
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if  (  pos  ==  NULL  )   {
		TRACE0("No items were selected!\n");
		m_var.listCtrl.iSelectItem  =  -1;
		}
	else  {			     
		  int  nItem  =  pListCtrl->GetNextSelectedItem(pos);
		  m_var.listCtrl.iSelectItem  =  nItem;
	}

	//
	bRefreshBtns(  );

	*pResult = 0;
}


void CDlgOfflineRes::OnBnClickedButtonpage1()
{
	// TODO: Add your control notification handler code here
	m_var.usIndex_page  =  0;
	this->bDisplay_usIndex_page(  );
	//
	bRefresh(  );
}


void CDlgOfflineRes::OnBnClickedButtonnextpage()
{
	// TODO: Add your control notification handler code here
	m_var.usIndex_page  ++  ;
	this->bDisplay_usIndex_page(  );
	//
	bRefresh(  );

}


void CDlgOfflineRes::OnBnClickedButtonprevpage()
{
	// TODO: Add your control notification handler code here
	//
	if  (  m_var.usIndex_page  ==  0  )  return;
	//
	m_var.usIndex_page  --  ;
	this->bDisplay_usIndex_page(  );
	//
	bRefresh(  );


}




void CDlgOfflineRes::OnBnClickedButtongo()
{
	// TODO: Add your control notification handler code here
	//
	m_var.usIndex_page  =  GetDlgItemInt(  m_var.guiData.iIDC_EDIT_pageNo  );			
	if  (  m_var.usIndex_page  )  m_var.usIndex_page  --  ;
	//
	this->bDisplay_usIndex_page(  );
	//
	this->bRefresh(  );
}


void CDlgOfflineRes::OnEnChangeEditfilterkeywords()     
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	m_var.usIndex_page  =  0;
	this->bDisplay_usIndex_page(  );
}

//
void CDlgOfflineRes::OnBnClickedCancel()
{
	this->OnCancel(  );
}


BOOL CDlgOfflineRes::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	//
	switch  (  pMsg->message  )  {
			case  WM_MOUSEMOVE:  {
				  #ifdef  __DEBUG__
						  traceLog(  _T(  "dlgOfflineRes: mouse move"  )  );
				  #endif

				  int  xPos = LOWORD(pMsg->lParam); 
				  int  yPos = HIWORD(pMsg->lParam);

				  //
				  if  (  m_var.hCurTalk  )  {
					  POINT	tmpPoint;
					  tmpPoint.x  =  xPos;
					  tmpPoint.y  =  yPos;
					  ::MapWindowPoints(  this->m_hWnd,  NULL,  &tmpPoint,  1  );

					  //
					  //viewInstantAssistant(  this->m_hWnd,  0,  tmpPoint.x,  tmpPoint.y,  m_var.hCurTalk,  FALSE  );
				  }

				  }
				  //
				  break;
			default:
					break;
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}


