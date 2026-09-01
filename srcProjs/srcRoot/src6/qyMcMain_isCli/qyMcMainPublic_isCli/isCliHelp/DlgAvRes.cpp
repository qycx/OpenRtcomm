// DlgAvRes.cpp : implementation file
//

#include "stdafx.h"

#define  __noDbg_new__

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"

#include	"myresource.h"
#include	"qmcVWall.h"
#include	"WallTalkers.h"
#include	"DlgDynBmps.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyVk.h"

#include	"qmcDxSurfacePublic.h"

#include	"qyCusResTemp.h"

#include	"qyAvRecordPublic.h"

#include	"sp.h"
#include	"qmcCommFunc_isCli.h"
#include	"qyMessengerHelpPublic.h"

#include	"myDb.h"
#include	"funcsForIsCliHelp.h"
#include	"qmcLayout.h"

//
#include "DlgAvRes.h"
#include "afxdialogex.h"


//
int  tmp_addTvItem(  CDlgAvRes  *  pDlg,  QY_MESSENGER_ID  *  pIdInfo_mem,  HTREEITEM	   htRoot,  BOOL  bConn,  BOOL  *  pbInserted  );
int  tmp_addTvItem_res(  CDlgAvRes  *  pDlg,  QY_MESSENGER_ID  *  pIdInfo_mem,  HTREEITEM	   htRoot  );
BOOL  bTonglian(  QY_MESSENGER_ID  *  pIdInfo  );
int  getIdInfo_superAdmin(  QY_MESSENGER_ID  *  pIdInfo  );
BOOL  isActiveMem(  CDlgAvRes  *  pDlgAvRes,  QY_MESSENGER_ID  *  pIdInfo  );




//
#define  CONST_str_avResTitle	_T(  "Resource"  )



//
//
BOOL  g_fDragging  =  FALSE;
HIMAGELIST g_hDragImageList   =  NULL;


//
  //

//
int  avRes_proc_applyForOrgReq(  HWND  hBar,  IM_GRP_EX  *  p,  QY_MESSENGER_ID  *  pIdInfo_from  )
{
	int  iErr  =  -1;

	CDlgAvRes  *  pDlg  =  (  CDlgAvRes  *  )CWnd::FromHandlePermanent(  hBar  );
	if  (  !pDlg  )  return  -1;


	return pDlg->proc_applyForOrgReq(  p,  pIdInfo_from  );

	iErr  =  0;
errLabel:

	return  iErr;
}

//
 int  refreshAvResGrpInfo(  HWND  hBar,  IM_GRP_EX  *  p  )
{
	int  iErr  =  -1;

	CDlgAvRes  *  pDlg  =  (  CDlgAvRes  *  )CWnd::FromHandlePermanent(  hBar  );
	if  (  !pDlg  )  return  -1;


	return pDlg->refreshAvResGrpInfo(  p  );

	iErr  =  0;
errLabel:

	return  iErr;
}


 int  refreshAvResConfAccepted(  HWND  hBar  )
 {
	 int  iErr  =  -1;
	CDlgAvRes  *  pDlg  =  (  CDlgAvRes  *  )CWnd::FromHandlePermanent(  hBar  );
	if  (  !pDlg  )  return  -1;


	return pDlg->refreshAvResCallStatus(  );

	iErr  =  0;
errLabel:

	return  iErr;

 }

//
//
 //(  HWND  hParent,  HWND  hDlgDynBmps,  HWND  *  phWnd  )
 __declspec(  dllexport  )  int viewDlgAvRes(  HWND  hWndEvent,  int  iWndContentType,  int  xPos_screen,  int  yPos_screen,  HWND  hDlgDynBmps,  void  *  pDLG_wall_var,  BOOL  bNoDelayToView  )  
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int								iErr					=	-1;
	QY_MC					*		pQyMc					=	QY_GET_GBUF(  );
	MC_VAR_isCli			*		pProcInfo				=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	//
	int		iIDD  =  IDD_avRes;

	//
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;
#if 10
	if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hzj  )  {

		int  iRole  =  0;
		getRole_byIdInfo(  &pMisCnt->idInfo,  &iRole  );
		if  (  iRole  ==  CONST_imObjRole_superAdmin  )  {
			iIDD  =  IDD_avRes_mgr_hzj;
			}
		else  {
			iIDD  =  IDD_avRes_mem_hzj;
		}
		
	}
#endif


	//
	//  if  (  pProcInfo->g_hVWall  !=  hDlgWalls  )  return  -1;

	//  ZONE_objs_info	*	pVar	=	(  ZONE_objs_info  *  )getDlgWallsVar(  hDlgWalls  );
	if  (  !pDLG_wall_var  )  return  -1;
	ZONE_objs_info	&	m_var	=	*(  ZONE_objs_info  *  )pDLG_wall_var;

	//
	m_var.dwTickCnt_lastMouseMove  =  GetTickCount(  );


	CDlgAvRes				*		pDlg					=	NULL;
	int								iStatus_ia				=	0;
	BOOL							bMin					=	FALSE;

	//  traceLogA(  "viewInstantAssistant enters"  );

#ifdef  __DEBUG__
		int  i  =  sizeof(  int  );
		//  traceLog(  _T(  "viewIa, xPos %d, yPos %d"  ),  xPos,  yPos  );
		//  goto  errLabel;
#endif


#if  10

	if  (  !bNoDelayToView  )  {	
		if  (  xPos_screen  ==  m_var.param_viewBar.xPos_screen  &&  yPos_screen  ==  m_var.param_viewBar.yPos_screen  )  {
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
	m_var.param_viewBar.xPos_screen  =  xPos_screen;
	m_var.param_viewBar.yPos_screen  =  yPos_screen;
#endif


	if  (  IsWindow(  m_var.hBar  )  )  {
		//
		if  (  !IsWindowVisible(  m_var.hBar  )  )  {
			setWallsBarPos(  hDlgDynBmps,  pDLG_wall_var,  m_var.hBar,  m_var.iBarType  );
		}
		//
		MACRO_SetForegroundWindow(  m_var.hBar  );
		//
		iErr  =  0;  goto  errLabel;
	}

	m_var.hBar  =  NULL;


//

		 //  2010/12/18
		 HWND	hFore	=	GetForegroundWindow(  );
		 HWND	hAbove  =	NULL;	//  findWndAbove(  hParent  );

		 //
		 RECT							rect;

		 HWND	hParent  =  hWndEvent;	//  hDlgWalls;
		 pDlg  =  new  CDlgAvRes(  CWnd::FromHandle(hParent)  );
		 if  (  !pDlg  )  goto  errLabel;

		 pDlg->m_var.iWndContentType  =  CONST_qyBarType_avRes;
		 pDlg->m_var.guiData.hDlgDynBmps  =  hDlgDynBmps;		//  2012/05/24
		 //pDlg->m_var.guiData.iVwSubtype  =  iVwSubtype;		//  2018/12/18
		 pDlg->m_var.m_nID  =  iIDD;

		 {
			 CDlgDynBmps  *  pDlgDynBmps  =  (  CDlgDynBmps  *  )CWnd::FromHandlePermanent(  hDlgDynBmps  );
			 if  (  !pDlgDynBmps  )  goto  errLabel;
			 pDlg->m_var.guiData.iVwSubtype  =  pDlgDynBmps->getWndContentSubtype(  );
		 }

		 //
		 if  (  !pDlg->Create(  rect  )  )  goto  errLabel;

		 //
		 setWallsBarPos(  hDlgDynBmps,  pDLG_wall_var,  pDlg->m_hWnd,  CONST_qyBarType_avRes  );

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
	m_var.hBar  =  pDlg->m_hWnd;
	m_var.iBarType  =  pDlg->m_var.iWndContentType;
	
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


//
__declspec(  dllexport  )  int  hideDlgAvRes(  HWND  hWnd  )
{
	//
	if  (  g_fDragging   )  return  -1;

	if  (  IsWindowVisible(  hWnd  )  )  {
		//
					
					  //if  (
					  CDlgAvRes  *  pDlg  =  (  CDlgAvRes  *  )CWnd::FromHandlePermanent(  hWnd  );
					  if  (  !pDlg  )  return  -1;
		
					  //			  
					  if  (  pDlg->m_var.bLocked  )  return  -1;
					  

		//
		ShowWindow(  hWnd,  SW_HIDE  );
	}
	return  0;
}


// CDlgAvRes dialog

IMPLEMENT_DYNAMIC(CDlgAvRes, CDialogEx)

CDlgAvRes::CDlgAvRes(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAvRes::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

	//
	m_var.guiData.iIDC_COMBO_layout  =  IDC_COMBO_layout;
	m_var.guiData.iIDC_COMBO_grp  =  IDC_COMBO_grp;
	m_var.guiData.iIDC_tree  =  IDC_avResTree;
			
	//
	if  (  pParent  )  m_var.m_hParent = pParent->m_hWnd;
	m_var.m_nID = CDlgAvRes::IDD;

}

CDlgAvRes::~CDlgAvRes()
{
}


//

 BOOL  CDlgAvRes::bQuitDlg(  )
 {

	//
	DestroyWindow(  );
	return  TRUE;

 }
	
	
 BOOL  CDlgAvRes::Create(const RECT& rect)
 {
	 	BOOL						bRet		=	FALSE;


#if  0
	if  (  !m_var.bInfoSet  )  {
		traceLog(  _T(  "CDlgDesktopsMon::Create(  ) failed: bInfoSet is false"  )  );
		return  FALSE;
	}'
#endif
	

	if  (  !CDialog::Create(  this->m_var.m_nID, CWnd::FromHandle(  m_var.m_hParent  )  )  )  goto  errLabel;

	//
	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;

 }



 // 	
 BOOL	CDlgAvRes::bInitialDisplay(  )
{
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	
	//
	 m_TreeCtrl  =  (  CTreeCtrl  *  )GetDlgItem(  m_var.guiData.iIDC_tree  );	//  &GetTreeCtrl(  );

	 //
	 m_TreeCtrl->ModifyStyle(0,TVS_HASBUTTONS  );


	 // Create the image list for the tree control
	 //  m_ImageList.Create(  IDB_qnmIcons,  16,  1,  RGB(  0,  255,  0  )  );
	 m_ImageList.Create(  IDB_qnmIcons,  16,  1,  0  );		//  2003/10/21修改
	 m_TreeCtrl->SetImageList(  &m_ImageList,  TVSIL_NORMAL  );

#if  0
	 if  (  pQyMc->iCustomId  !=  CONST_qyCustomId_hzj  )  {
		 this->m_var.htMyRootItem  =  m_TreeCtrl->InsertItem(  CString(  pQyMc->cfg.name  )  );
		 m_TreeCtrl->SetItemState(  this->m_var.htMyRootItem,  TVIS_BOLD,  TVIS_BOLD  );
	 }
	 else  {

		   //
		   this->m_var.htMyRootItem0  =  m_TreeCtrl->InsertItem(  CString(  _T(  "会议成员"  )  )  );
		   m_TreeCtrl->SetItemState(  this->m_var.htMyRootItem0,  TVIS_BOLD,  TVIS_BOLD  );

		   //		 
		   this->m_var.htMyRootItem  =  m_TreeCtrl->InsertItem(  CString(  _T(  "其他成员"  )  )  );		 
		   m_TreeCtrl->SetItemState(  this->m_var.htMyRootItem,  TVIS_BOLD,  TVIS_BOLD  );

	 }
#endif
	 resetRootItems(  );



	 //
	 this->m_var.bInitialized  =  TRUE;

	return  TRUE;
 }

 //
 int  CDlgAvRes::resetRootItems(  )
 {
	 QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	 m_TreeCtrl->DeleteAllItems(  );
	 if  (  pQyMc->iCustomId  !=  CONST_qyCustomId_hzj  )  {
		 this->m_var.htMyRootItem  =  m_TreeCtrl->InsertItem(  CString(  pQyMc->cfg.name  )  );
		 m_TreeCtrl->SetItemState(  this->m_var.htMyRootItem,  TVIS_BOLD,  TVIS_BOLD  );
	 }
	 else  {

		   //
		   this->m_var.htMyRootItem0  =  m_TreeCtrl->InsertItem(  CString(  _T(  "会议成员"  )  )  );
		   m_TreeCtrl->SetItemState(  this->m_var.htMyRootItem0,  TVIS_BOLD,  TVIS_BOLD  );

		   //		 
		   this->m_var.htMyRootItem  =  m_TreeCtrl->InsertItem(  CString(  _T(  "其他成员"  )  )  );		 
		   m_TreeCtrl->SetItemState(  this->m_var.htMyRootItem,  TVIS_BOLD,  TVIS_BOLD  );

	 }

	 return  0;
 }

 //
 int  tmpHandler_avRes_displayImGrpMem(  void  *  p0,  void *  p1,  void  *  p2  )
 {
	 int  iErr  =  -1;
	 CDlgAvRes  *  pLeftView  =  (  CDlgAvRes  *  )p0;
	 //  p1
	 COMMON_PARAM  *  pCommonParam  =  (  COMMON_PARAM  *  )p1;
	 IM_GRP_MEM		*	pQMem										=	(  IM_GRP_MEM  *  )p2;

	 //
	 QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli( );
	 MIS_CNT  *  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 CTreeCtrl *  m_TreeCtrl  =  pLeftView->m_TreeCtrl;

	 //
	 CQnmDb				db;
			 
	 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
	 //	
	 CMyDb			*	pDb											=	(  CMyDb  *  )db.m_pDbMem->pDb;
		
	  //
	 QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	 if  (  !pDbFuncs  )  goto  errLabel;
	 QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;
	
	   	 

	 //
	 if  (  pQMem->idInfo_grp.ui64Id  ==  pLeftView->m_var.idInfo_grp_sel.ui64Id  )  {

		 //>
		 #if  0

		   //
		   //  下面增加一个我节点
		   //
		   //iObjType  =  CONST_objType_me;
		   //myTChar2Utf8(  _T(  "me"  ),  buf,  mycountof(  buf  )  );
		 int  iObjId  =  pQMem->idInfo_mem.ui64Id;	//  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );
		   if  (  iObjId  <  0  )  goto  errLabel;

		   QY_MESSENGER_REGINFO  regInfo;
		   QY_MESSENGER_REGINFO  *pRegInfo  =  &regInfo;
		   TCHAR  tBuf[128];
		   TCHAR  displayName[128];
		   TCHAR  talkerDesc[128];
		   MY_REG_DESC  desc;
		   
		   QM_OBJQ_MEM				mem;
		   unsigned  short			usRunningStatus  =  0;
		   int  nImage,  nSelectedImage;
		   HTREEITEM  tmphtItem;
		   
		   //
		   //
					//
					int  iDbType  =  CONST_dbType_myDb;
					if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pDb,  iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  _T(  ""  ),  &pQMem->idInfo_mem,  0,  &regInfo  )  )  {
						memset(  &regInfo,  0,  sizeof(  regInfo  )  );
					}

				    
					//						
					//
					if  (  regInfo2Desc(  0,  pRegInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  displayName,  mycountof(  displayName  )  )  )  goto  errLabel;
			 	
		   
		   
		   //
		   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s(%I64u)"  ),  displayName,  pQMem->idInfo_mem.ui64Id  );
		   //
		   if  (  findQMemByKey(  0,  pMisCnt->pObjQ,  &pMisCnt->idInfo,  &mem  )  )  usRunningStatus  =  CONST_usRunningStatus_offline;
		   else  {
			     QMEM_MESSENGER_CLI	*	pQMem;
			     pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
				 usRunningStatus  =  pQMem->usRunningStatus;
		   }
		   //
		   getMessengerImages(  pQyMc,  usRunningStatus,  &nImage,  &nSelectedImage  );
				
		   if  (  !(  tmphtItem  =  treeCtrl_FindItemData(  pLeftView->m_TreeCtrl,  iObjId,  TRUE,  pLeftView->m_var.htMyRootItem  )  )  )  {
			   tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
													  displayName,  
													  nImage,  
													  nSelectedImage,  
													  TVIS_EXPANDPARTIAL,  
													  TVIS_STATEIMAGEMASK, 
													  iObjId,  
													  pLeftView->m_var.htMyRootItem,  
													  TVI_LAST  );
			   //  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );  //  
				   

				}
		   else  {				  
			     //  只刷新展开节点
				 TVITEM				tvItem;
				 
				 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
				 tvItem.hItem  =  tmphtItem;
				 tvItem.pszText  =  tBuf;
				 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				 m_TreeCtrl->GetItem(  &tvItem  );
				 
				 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
					 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
					 tvItem.iImage  =  nImage;
					 tvItem.iSelectedImage  =  nSelectedImage;
					 m_TreeCtrl->SetItem(  &tvItem  );
				 }


		   }
#endif
		   BOOL  bConn  =  FALSE;
		   BOOL  bInserted  =  FALSE;

		   //
#ifdef  __DEBUG__
		   //if  (  pQMem->idInfo_mem.ui64Id  == 104  )  bConn  =  TRUE;
#endif
		   bConn  =  bTonglian(  &pQMem->idInfo_mem  );
		   BOOL  bActiveMem  =  FALSE;//isMemFromActive(  );


		   //if  (  pLeftView->m_var.guiData.hDlgDynBmps  
		   //
		   tmp_addTvItem(  pLeftView,  &pQMem->idInfo_mem,  pLeftView->m_var.htMyRootItem,  bConn,  &bInserted  );

		   if  (  bInserted  )  {
			   //
		       tmp_addTvItem_res(  pLeftView,  &pQMem->idInfo_mem,  pLeftView->m_var.htMyRootItem  );
		   }


	 }


	 //
	 iErr  =  0;

errLabel:
	 return  iErr;

 }


 //
#if 0
 int  tmpHandler_avRes_displayImGrpMem_res(  void  *  p0,  void *  p1,  void  *  p2  )
 {
	 int  iErr  =  -1;
	 CDlgAvRes  *  pLeftView  =  (  CDlgAvRes  *  )p0;
	 //  p1
	 COMMON_PARAM  *  pCommonParam  =  (  COMMON_PARAM  *  )p1;
	 IM_GRP_MEM		*	pQMem										=	(  IM_GRP_MEM  *  )p2;

	 //
	 QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli( );
	 MIS_CNT  *  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 CTreeCtrl *  m_TreeCtrl  =  pLeftView->m_TreeCtrl;

	 //
	 CQnmDb				db;
			 
	 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
	 //	
	 CMyDb			*	pDb											=	(  CMyDb  *  )db.m_pDbMem->pDb;
		
	  //
	 QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	 if  (  !pDbFuncs  )  goto  errLabel;
	 QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;
	
	   	 

	 //
	 if  (  pQMem->idInfo_grp.ui64Id  ==  pLeftView->m_var.idInfo_grp_sel.ui64Id  )  {

#if  0
		   //
		   //
		   int  iObjId  =  0;
		   
		   TCHAR  tBuf[128];
		   TCHAR  displayName[128];
		   
		   int  nImage,  nSelectedImage;
		   HTREEITEM  tmphtItem;
		   
		   //
		   //
		   //
		   //getMessengerImages(  pQyMc,  usRunningStatus,  &nImage,  &nSelectedImage  );
		   HTREEITEM  htItem_msgr  =  treeCtrl_FindItemData(  pLeftView->m_TreeCtrl,  pQMem->idInfo_mem.ui64Id,  TRUE,  pLeftView->m_var.htMyRootItem  );
		   if  (  !htItem_msgr  )  goto  errLabel;

		   //
		   //int  tmp_i  =  pLeftView->m_TreeCtrl->GetItemData(  htItem_msgr  );

		   //
		   int  iObjType  =  CONST_objType_screen;
		   iObjId  =  iObjType;
		   //iObjId  =  CONST_objType_webcam;
		
		   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),   iObjType  )  ); 
		   //
		   //_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s%I64u"  ),  displayName,  pQMem->idInfo_mem.ui64Id  );
		   //
		   nImage  =  pQyMc->cfg.image.nImage_screen;  //16;//pQyMc->cfg.image.normal.nImage_pcNormal;	//  
		   nSelectedImage  =  nImage;

		   //
		   if  (  !(  tmphtItem  =  treeCtrl_FindChildItemData(  pLeftView->m_TreeCtrl,  iObjId,  TRUE,  htItem_msgr  )  )  )  {
			   tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
													  displayName,  
													  nImage,  
													  nSelectedImage,  
													  TVIS_EXPANDPARTIAL,  
													  TVIS_STATEIMAGEMASK, 
													  iObjId,  
													  htItem_msgr,  
													  TVI_LAST  );
			   //  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );  //  
				   

				}
		   else  {				  
			     //  只刷新展开节点
				 TVITEM				tvItem;
				 
				 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
				 tvItem.hItem  =  tmphtItem;
				 tvItem.pszText  =  tBuf;
				 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				 m_TreeCtrl->GetItem(  &tvItem  );
				 
				 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
					 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
					 tvItem.iImage  =  nImage;
					 tvItem.iSelectedImage  =  nSelectedImage;
					 m_TreeCtrl->SetItem(  &tvItem  );
				 }


		   }


		   //
		   iObjType  =  CONST_objType_webcam;
		   iObjId  =  iObjType;
		   //iObjId  =  CONST_objType_webcam;
		
		   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),   iObjType  )  ); 
		   //
		   //_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s%I64u"  ),  displayName,  pQMem->idInfo_mem.ui64Id  );
		   //
		   nImage  =  pQyMc->cfg.image.nImage_webcam;
		   nSelectedImage  =  nImage;

		   //
		   if  (  !(  tmphtItem  =  treeCtrl_FindChildItemData(  pLeftView->m_TreeCtrl,  iObjId,  TRUE,  htItem_msgr  )  )  )  {
			   tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
													  displayName,  
													  nImage,  
													  nSelectedImage,  
													  TVIS_EXPANDPARTIAL,  
													  TVIS_STATEIMAGEMASK, 
													  iObjId,  
													  htItem_msgr,  
													  TVI_LAST  );
			   //  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );  //  
				   

				}
		   else  {				  
			     //  只刷新展开节点
				 TVITEM				tvItem;
				 
				 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
				 tvItem.hItem  =  tmphtItem;
				 tvItem.pszText  =  tBuf;
				 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				 m_TreeCtrl->GetItem(  &tvItem  );
				 
				 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
					 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
					 tvItem.iImage  =  nImage;
					 tvItem.iSelectedImage  =  nSelectedImage;
					 m_TreeCtrl->SetItem(  &tvItem  );
				 }


		   }

		   //

#endif
		   //
		   tmp_addTvItem_res(  pLeftView,  &pQMem->idInfo_mem,  pLeftView->m_var.htMyRootItem   );
	 }


	 //
	 iErr  =  0;

errLabel:
	 return  iErr;

 }
#endif



 //
 int  avRes_displayContent_imObjs_isClient_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int							iRet				=				-1;
	 QY_MC						*	pQyMc				=				QY_GET_GBUF(  );
	 CDlgAvRes			*	pLeftView			=				(  CDlgAvRes  *  )p0;
	 CTreeCtrl					*	m_TreeCtrl			=				pLeftView->m_TreeCtrl;	//  GetTreeCtrl(  );
	 //  CQyMcDoc					*	pDoc				=				pLeftView->GetDocument(  );
	 
	 int						iServiceId				=				CONST_qyServiceId_mis;
	 QY_SERVICEGUI_INFO		*	pSci					=				getServiceGuiInfo(  pQyMc,  iServiceId  );
	 if  (  !pSci  )  return  -1;
	 MC_VAR_isCli				*	pProcInfo				=				(  MC_VAR_isCli  *  )pSci->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 MIS_CNT				*	pMisCnt					=				getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 if  (  !pMisCnt  )  return  -1;


	 
	 //
	 if  (  pQyMc->cfg.db.iDbType  !=  CONST_dbType_myDb  )  {
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "only supported with myDb"  )  );
		 #endif
		 return  -1;
	 }


	 HTREEITEM					tmphtItem				=				NULL;
	 TCHAR						displayName[512]		=				_T(  ""  );		
	 int						iObjId					=				0;
	 int						nImage,  nSelectedImage;
	 int						iTopFieldId				=				0;
	 char						topLevelColName[128]	=				"'";
	 char					*	p						=				NULL;
	 int						i;
	 int						iObjType				=				0;
	 COMMON_PARAM				commonParam;
	 TCHAR						tBuf[1024];
	 char						buf[256];



	 QY_OBJ_DB					*	pObjDb				=				getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;



	 //
	 CMyDb				*	pDb	=	(  CMyDb  *  )pObjDb->pDb;

	 //  2014/05/27
	 //qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayContent_imObjs_isClient_myDb, addObjRegInfo starts ..."  )  );

	 //  下面增加新增的节点	
	 //
	 //  先将注册用户的单位放入视图
	 QY_MESSENGER_REGINFO	regInfo;
	 //
	 MACRO_makeCommonParam3(  0,  0,  &regInfo,  commonParam  );
	 qTraverse(  pDb->m_var.pQ_qyImGrpMemTab,  tmpHandler_avRes_displayImGrpMem,  pLeftView,  &commonParam  );

	 //
	 //MACRO_makeCommonParam3(  0,  0,  &regInfo,  commonParam  );
	 //qTraverse(  pDb->m_var.pQ_qyImGrpMemTab,  tmpHandler_avRes_displayImGrpMem_res,  pLeftView,  &commonParam  );

	 	
	 //
	 m_TreeCtrl->Expand(  pLeftView->m_var.htMyRootItem,  TVE_EXPAND  );
	 m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );

	 //  2014/05/27
	 //qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayContent_imObjs_isClient_myDb, addObjRegInfo ends."  )  );

	 		



#if  0

		   //
		   //  下面增加一个我节点
		   //
		   iObjType  =  CONST_objType_me;
		   myTChar2Utf8(  _T(  "me"  ),  buf,  mycountof(  buf  )  );
		   iObjId  =  9;	//  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );
		   if  (  iObjId  <  0  )  goto  errLabel;

		   
		   QM_OBJQ_MEM				mem;
		   unsigned  short			usRunningStatus;
		   //
		   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s(%I64u)"  ),  pMisCnt->displayName,  pMisCnt->idInfo.ui64Id  );
		   if  (  findQMemByKey(  0,  pMisCnt->pObjQ,  &pMisCnt->idInfo,  &mem  )  )  usRunningStatus  =  CONST_usRunningStatus_offline;
		   else  {
			     QMEM_MESSENGER_CLI	*	pQMem;
			     pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
				 usRunningStatus  =  pQMem->usRunningStatus;
		   }
		   //
		   getMessengerImages(  pQyMc,  usRunningStatus,  &nImage,  &nSelectedImage  );
				
		   if  (  !(  tmphtItem  =  treeCtrl_FindItemData(  pLeftView->m_TreeCtrl,  iObjId,  TRUE,  pLeftView->m_var.htMyRootItem  )  )  )  {
			   tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
													  displayName,  
													  nImage,  
													  nSelectedImage,  
													  TVIS_EXPANDPARTIAL,  
													  TVIS_STATEIMAGEMASK, 
													  iObjId,  
													  pLeftView->m_var.htMyRootItem,  
													  TVI_LAST  );
			   //  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );  //  
				   

				}
		   else  {				  
			     //  只刷新展开节点
				 TVITEM				tvItem;
				 
				 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
				 tvItem.hItem  =  tmphtItem;
				 tvItem.pszText  =  tBuf;
				 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				 m_TreeCtrl->GetItem(  &tvItem  );
				 
				 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
					 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
					 tvItem.iImage  =  nImage;
					 tvItem.iSelectedImage  =  nSelectedImage;
					 m_TreeCtrl->SetItem(  &tvItem  );
				 }


		   }
#endif


	 //
	 iRet  =  0;
errLabel:

	return  iRet;
 }


 BOOL	CDlgAvRes::bDisplayContent(  )
 {
	 //
	 avRes_displayContent_imObjs_isClient_myDb(  this,  0,  0  );

	 return  TRUE;
 }



 BOOL	CDlgAvRes::bRefreshItem(  HTREEITEM  hItem  )
 {
	 return  TRUE;
 }

 //
 int  CDlgAvRes::proc_applyForOrgReq(  IM_GRP_EX  *  p,  QY_MESSENGER_ID  *  pIdInfo_from  )
 {
	 int  iErr  =  -1;
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli();

	 		 MIS_CNT  *  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
		 MACRO_prepareForTran();
		 int  iTaskId =  0;
		 int  uiTaskType  =  0;
		 unsigned  int  uiChannelType  =  0;
		 
		 QY_MESSENGER_ID  idInfo_dst;
			  //
		 idInfo_dst.ui64Id  =  pIdInfo_from->ui64Id;
			  if  (  idInfo_dst.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  goto  errLabel;
			  
			  if  (  p->common.idInfo.ui64Id  !=  m_var.hzj.imGrpEx.common.idInfo.ui64Id  )  goto  errLabel;
			  IM_GRP_EX  req  =  m_var.hzj.imGrpEx;
			  //
			  req.usOp  =  CONST_imOp_refresh;
			  
			  //
			  if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  iTaskId,  uiTaskType,  (  char  *  )&req,  sizeof(  req  ),  0,  0,  0,  &idInfo_dst,  uiChannelType,  NULL,  FALSE  )  )  goto  errLabel;


	 iErr  =  0;
errLabel:

	 return  iErr;
 }


  int  CDlgAvRes::refreshAvResGrpInfo(  IM_GRP_EX  *  p  )
  {
	  int  iErr  =  -1;

	  	if  (  m_var.m_nID  !=  IDD_avRes_mem_hzj  )  return  -1;

	if  (  !m_var.bInitialized  )  return  -1;

	resetRootItems(  );

	int  i;
	IM_GRP_EX  &  req  =  *p;
		//
	for  (  i  =  0;  i  <  req.usCnt;  i  ++  )  {
		 //
		BOOL  bConn  =  FALSE;
		BOOL  bActiveMem  =  FALSE;
		BOOL  bInserted  =  FALSE;
		 
		tmp_addTvItem(  this,  &req.mems[i].grpMmem_idInfo,  m_var.htMyRootItem0,  bConn,  &bInserted  );

		if  (  bInserted  )  {
			tmp_addTvItem_res(  this,  &req.mems[i].grpMmem_idInfo,  m_var.htMyRootItem0  );
		}

	}
	//
	m_TreeCtrl->Expand(  m_var.htMyRootItem0,  TVE_EXPAND  );
	m_TreeCtrl->SortChildren(  m_var.htMyRootItem0  );

	avRes_displayContent_imObjs_isClient_myDb(  this,  0,  0  );

	//
	memcpy(  &m_var.hzj.imGrpEx,  p,  sizeof(  m_var.hzj.imGrpEx  )  );


	iErr  =  0;

errLabel:

	return  iErr;

  }


  //
  int  CDlgAvRes::refreshAvResCallStatus(  )
  {
	  int  iErr  =  -1;
	  if  (  m_var.m_nID  !=  IDD_avRes_mem_hzj  )  return  -1;

	  //
	  SetDlgItemText(  IDC_BUTTON_call,  _T(  "申请发言"  )  );


	  iErr  =  0;

	  return  iErr;
  }


//
void CDlgAvRes::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgAvRes, CDialogEx)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO_grp, &CDlgAvRes::OnCbnSelchangeCombogrp)
	ON_NOTIFY(TVN_BEGINDRAG, IDC_avResTree, &CDlgAvRes::OnTvnBegindragavrestree)
	
	ON_CBN_SELCHANGE(IDC_COMBO_layout, &CDlgAvRes::OnCbnSelchangeCombolayout)
	ON_WM_NCLBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_av, &CDlgAvRes::OnBnClickedButtonav)
	ON_BN_CLICKED(IDC_BUTTON_cfgConf, &CDlgAvRes::OnBnClickedButtoncfgconf)
	ON_BN_CLICKED(IDC_BUTTON_call, &CDlgAvRes::OnBnClickedButtoncall)
	ON_WM_TIMER()
	ON_NOTIFY(NM_RCLICK, IDC_avResTree, &CDlgAvRes::OnNMRClickavrestree)
END_MESSAGE_MAP()


// CDlgAvRes message handlers


void CDlgAvRes::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::PostNcDestroy();

	//
	if  (  m_var.bCreated  )  {
		traceLogA(  "CDlgAvRes::PostNcDestroy(  ), delete this"  );
		delete  this;
	}

}

//
int  sizeAllControls_avRes_mgr_hzj(  HWND  hDlg  );
int  sizeAllControls_avRes_mem_hzj(  HWND  hDlg  );


	//
	int  iEdge_l  =  10;
	int  iEdge_t  =  10;
	int  iSpace_x  =  5;
	int  iSpace_y  =  5;

//
int  sizeAllControls_avRes(  HWND  hDlg,  int  iIDD  )
{
	//
	if  (  iIDD  ==  IDD_avRes_mgr_hzj  )  return  sizeAllControls_avRes_mgr_hzj(  hDlg  );
	if  (  iIDD  ==  IDD_avRes_mem_hzj  )  return  sizeAllControls_avRes_mem_hzj(  hDlg  );
	
	//
	HDWP			hDwp;

	int				idc;
	int				x, y, iW, iH;

	RECT			rc;
	GetClientRect(  hDlg,  &rc  );

	int  iW_dlg,  iH_dlg;

	iW_dlg  =  rc.right  -  rc.left;
	iH_dlg  =  rc.bottom  -  rc.top;
	
	int  iH_layout  =  20;

	int  iH_grp  =  20;
	int  iH_status  =  20;




	//
	hDwp  =  BeginDeferWindowPos(  4  );
	if  (  hDwp  )  {		 
		//
		idc  =  IDC_COMBO_layout;
		x  =  iEdge_l;
		y  =  iEdge_t;
		iW  =  iW_dlg  -  2  *  iEdge_l;
		iH  =  iH_layout;
		DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		y  +=  iH;
		

		idc  =  IDC_COMBO_grp;
		x  =  iEdge_l;
		y  +=  iSpace_y;
		iW  =  iW_dlg  -  2  *  iEdge_l;
		iH  =  iH_grp;
		DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		y  +=  iH;
		
		idc  =  IDC_avResTree;
		x  =  iEdge_l;
		y  +=  iSpace_y;
		iH  =  iH_dlg  -  2  *  iEdge_t  -  iH_layout  -  iSpace_y  -  iH_grp  -  iSpace_y  -  iH_status  -  iSpace_y;
		DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		y  +=  iH;

		//
		idc  =  IDC_STATIC_status;
		x  =  iEdge_l;
		y  +=  iSpace_y;
		iW  =  iW_dlg  -  2  *  iEdge_l;
		iH  =  iH_status;
		DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		y  +=  iH;
		

		EndDeferWindowPos(  hDwp  );
	}

	return  0;
}


//
int  sizeAllControls_avRes_mgr_hzj(  HWND  hDlg  )
{
	HDWP			hDwp;

	int				idc;
	int				x, y, iW, iH;

	RECT			rc;
	GetClientRect(  hDlg,  &rc  );

	int  iW_dlg,  iH_dlg;

	iW_dlg  =  rc.right  -  rc.left;
	iH_dlg  =  rc.bottom  -  rc.top;

	
	int  iH_layout  =  20;

	int  iH_grp  =  20;
	int  iH_status  =  20;

	int  iW_cfgConf  =  30;



	//
	hDwp  =  BeginDeferWindowPos(  6  );
	if  (  hDwp  )  {		 
		//
		idc  =  IDC_BUTTON_av;
		x  =  iEdge_l;
		y  =  iEdge_t;
		iW  =  iW_dlg  -  2  *  iEdge_l  -  iSpace_x  -  iW_cfgConf;
		iH  =  iH_layout;
		DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		
		idc  =  IDC_BUTTON_cfgConf;
		x  +=  iW  +  iSpace_x;
		iW  =  iW_cfgConf;
		DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		y  +=  iH;
		

		//
		idc  =  IDC_COMBO_layout;
		x  =  iEdge_l;
		y  +=  iSpace_y;
		iW  =  iW_dlg  -  2  *  iEdge_l;
		iH  =  iH_layout;
		DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		y  +=  iH;
		

		idc  =  IDC_COMBO_grp;
		x  =  iEdge_l;
		y  +=  iSpace_y;
		iW  =  iW_dlg  -  2  *  iEdge_l;
		iH  =  iH_grp;
		DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		y  +=  iH;
		
		idc  =  IDC_avResTree;
		x  =  iEdge_l;
		y  +=  iSpace_y;
		iH  =  iH_dlg  -  2  *  iEdge_t  -  iH_layout  -  iSpace_y  -  iH_layout  -  iSpace_y  -  iH_grp  -  iSpace_y  -  iH_status  -  iSpace_y;
		DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		y  +=  iH;

		//
		idc  =  IDC_STATIC_status;
		x  =  iEdge_l;
		y  +=  iSpace_y;
		iW  =  iW_dlg  -  2  *  iEdge_l;
		iH  =  iH_status;
		DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		y  +=  iH;
		

		EndDeferWindowPos(  hDwp  );
	}

	return  0;
}

//
int  sizeAllControls_avRes_mem_hzj(  HWND  hDlg  )
{
	HDWP			hDwp;

	int				idc;
	int				x, y, iW, iH;

	RECT			rc;
	GetClientRect(  hDlg,  &rc  );

	int  iW_dlg,  iH_dlg;

	iW_dlg  =  rc.right  -  rc.left;
	iH_dlg  =  rc.bottom  -  rc.top;

	
	int  iH_layout  =  20;

	int  iH_grp  =  20;
	int  iH_status  =  20;

	


	//
	hDwp  =  BeginDeferWindowPos(  5  );
	if  (  hDwp  )  {		 
		//
		idc  =  IDC_BUTTON_call;
		x  =  iEdge_l;
		y  =  iEdge_t;
		iW  =  iW_dlg  -  2  *  iEdge_l;
		iH  =  iH_layout;
		DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		y  +=  iH;
		

		//
		idc  =  IDC_COMBO_layout;
		x  =  iEdge_l;
		y  +=  iSpace_y;
		iW  =  iW_dlg  -  2  *  iEdge_l;
		iH  =  iH_layout;
		DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		y  +=  iH;
		

		idc  =  IDC_COMBO_grp;
		x  =  iEdge_l;
		y  +=  iSpace_y;
		iW  =  iW_dlg  -  2  *  iEdge_l;
		iH  =  iH_grp;
		DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		y  +=  iH;
		
		idc  =  IDC_avResTree;
		x  =  iEdge_l;
		y  +=  iSpace_y;
		iH  =  iH_dlg  -  2  *  iEdge_t  -  iH_layout  -  iSpace_y  -  iH_layout  -  iSpace_y  -  iH_grp  -  iSpace_y  -  iH_status  -  iSpace_y;
		DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		y  +=  iH;

		//
		idc  =  IDC_STATIC_status;
		x  =  iEdge_l;
		y  +=  iSpace_y;
		iW  =  iW_dlg  -  2  *  iEdge_l;
		iH  =  iH_status;
		DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		y  +=  iH;
		

		EndDeferWindowPos(  hDwp  );
	}

	return  0;
}

//
void CDlgAvRes::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	sizeAllControls_avRes(  m_hWnd,  m_var.m_nID  );
}



void CDlgAvRes::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//CDialogEx::OnClose();

	m_var.bLocked  =  FALSE;
	SetWindowText(  CONST_str_avResTitle  );

	//
	hideDlgAvRes(  m_hWnd  );

}


void CDlgAvRes::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialogEx::OnCancel();

	//bQuitDlg();
}







BOOL CDlgAvRes::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	//
	switch  (  pMsg->message  )  {
			case  WM_MOUSEMOVE:  {
				  DWORD dwPos = GetMessagePos();
			
				  long  lParam  =  dwPos;			
				  POINT	point;
				  point.x = GET_X_LPARAM(lParam); 
				  point.y = GET_Y_LPARAM(lParam);
				  
				  //
				  RECT  rc;
				  ::GetWindowRect(  m_hWnd,  &rc  );
				  BOOL  bNeedClose  =  FALSE;

				  //
				  POINT  pnt_screen  =  point;
				  //::MapWindowPoints(  m_hWnd,  NULL,  &pnt_screen,  1  );

				  if  (  pnt_screen.x  >=  rc.right  -  CONST_avRes_space_toClose  )  bNeedClose  =  TRUE;
				  if  (  pnt_screen.y  <  rc.top  +  CONST_avRes_space_toClose  )  bNeedClose  =  TRUE;
				  if  (  pnt_screen.y  >  rc.bottom  -  CONST_avRes_space_toClose  )  bNeedClose  =  TRUE;

				  //
				  if  (  bNeedClose  )  {
					  hideDlgAvRes(  m_hWnd  );					  
				  }

				  //
				  //



				  traceLog(  _T(  "avRes.preTranslateMsg, mousemove, mouse %d,%d. rc.bottom %d"  ),  point.x,  point.y,  rc.bottom  );
				  }
				  break;
			case  WM_NCMOUSEMOVE:  {
				  DWORD dwPos = GetMessagePos();
			
				  long  lParam  =  dwPos;			
				  POINT	point;
				  point.x = GET_X_LPARAM(lParam); 
				  point.y = GET_Y_LPARAM(lParam);
				  
				  //
				  RECT  rc;
				  ::GetWindowRect(  m_hWnd,  &rc  );
				  BOOL  bNeedClose  =  FALSE;

				  //
				  POINT  pnt_screen  =  point;
				  //::MapWindowPoints(  m_hWnd,  NULL,  &pnt_screen,  1  );

				  if  (  pnt_screen.x  >=  rc.right  -  CONST_avRes_space_toClose  )  bNeedClose  =  TRUE;
				  if  (  pnt_screen.y  <  rc.top  +  CONST_avRes_space_toClose  )  bNeedClose  =  TRUE;
				  if  (  pnt_screen.y  >  rc.bottom  -  CONST_avRes_space_toClose  )  bNeedClose  =  TRUE;

				  //
				  if  (  bNeedClose  )  {
					  hideDlgAvRes(  m_hWnd  );
				  }

				  //
				  #ifdef  __DEBUG__
				  traceLog(  _T(  "dlgAvRes: ncmouseMove: x,y %d,%d. rc.t,b %d,%d"  ),  point.x,  point.y,  rc.top,  rc.bottom  );
						  //
						
				  #endif

				  //
				  }
				  //
				  break;
			case  WM_LBUTTONUP:  {
				  int  i  =  0;
				  //

				  }
				  
				  break;


			default:
				//traceLog(  _T(  "avRes.preTranslateMsg called, message %d"  ),  pMsg->message  );
					break;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

//
using namespace std;
#include	<vector>
#include	<algorithm>

//
bool  tmp_comp(  const CString &a, const CString &b )
{
	return  a<b;
}

//
int  fillLayout(  HWND  hWnd,  DLG_avRes_var  *  pm_var  )
{
	int  iErr  =  -1;
	
	//
	TCHAR  qvwDir[MAX_PATH]  =  _T(  ""  );
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	_sntprintf(  qvwDir,  mycountof(  qvwDir  ),  _T(  "%s%s"  ),  pQyMc->cfg.installDir,  _T(  CONST_qvwSubDir  )  );
	_sntprintf(  qvwDir,  mycountof(  qvwDir  ),  _T(  "%s*"  ),  qvwDir  );
	//
	WIN32_FIND_DATA FindData;          
	HANDLE fh =  NULL;

	//
	vector<CString> v;


	//	SendMessage(  ::GetDlgItem(  hWnd,  pm_var->guiData.iIDC_COMBO_layout  ),  CB_INSERTSTRING,  -1,  (  LPARAM  )pItem->des  );
	
	
	//
	 fh  =  FindFirstFile(  qvwDir,  &FindData  );
	 if  (  fh  ==  INVALID_HANDLE_VALUE  )  goto  errLabel;
	 do  {


         tTrim(  FindData.cFileName  );
		 //
		 traceLog(  _T(  "fillLayout: 搜索到%s"  ),  FindData.cFileName  ); 
		 
		 if  (  !_tcsicmp(  FindData.cFileName,  _T(  "."  )  ) 
			 ||  !_tcsicmp(  FindData.cFileName,  _T(  ".."  )  )
				)  
		 {
			 continue;
		 }
		 
		 //
		 TCHAR  tBuf[MAX_PATH];
		 lstrcpyn(  tBuf,  FindData.cFileName,  mycountof(  tBuf  )  );

		 //
		 if  (  bDir(  FindData.cFileName  )  )  continue;

		 //
		 TCHAR  *  pT;
		 pT  =  _tcsrchr(  tBuf,  _T(  '.'  )  );
		 if  (  !pT  )  continue;
		 if  (  lstrcmpi(  pT  +  1,  _T(  "qvw"  )  )  )  continue;
		 *pT  =  0;

		 //
		 v.push_back(  CString(  tBuf  )  );
	

		 //
	}  while  (  FindNextFile(  fh,  &FindData  )  ||  GetLastError() != ERROR_NO_MORE_FILES  );
 
	 //
	 sort(  v.begin(), v.end(), tmp_comp  );

	 //
	 for  (  vector<CString>::const_iterator it = v.begin(); it < v.end(); it  ++  )  {
		 //
		 SendMessage(  ::GetDlgItem(  hWnd,  pm_var->guiData.iIDC_COMBO_layout  ),  CB_INSERTSTRING,  -1,  (  LPARAM  )(  (  LPCTSTR  )(*it)  )  );
	 }
	 
	 //

	 //
	 iErr  =  0;

errLabel:

	 if  (  isHandleValid(  fh  )  )  FindClose(  fh  );

	


	return  0;
}
	

//
 int  tmpHandler_avRes_fillImObjs_grp_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;

	QY_MC	*	pQyMc  =  QY_GET_GBUF(  );

	COMMON_PARAM		*	pCommonParam1	=		(  COMMON_PARAM  *  )p1;
	//
	HWND					hDlg			=		(  HWND  )pCommonParam1->p0;
	DLG_avRes_var		&	m_var			=		*(  DLG_avRes_var  *  )pCommonParam1->p1;
	CMyDb				*   pMyDb			=		(  CMyDb  *  )pCommonParam1->p2;
	//
	QMEM_qyImObj		*   pQMem			=		(  QMEM_qyImObj  *  )p2;

	//  MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	IM_GRP_INFO					grpInfo;

	
	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;



	if  (  pQMem->messengerInfo.uiType  ==  CONST_objType_imGrp  )
	{
		if  (  !g_dbFuncs.pf_bGetImGrpInfoBySth(  pMyDb,  CONST_dbType_myDb,  pQMem->messengerInfo.misServName,  &pQMem->messengerInfo.idInfo,  &grpInfo  )  )  {
			memset(  &grpInfo,  0,  sizeof(  grpInfo  )  );
		}
		
		HWND	hCtl	=	GetDlgItem(  hDlg,  m_var.guiData.iIDC_COMBO_grp  );
		//  TCHAR	tBuf[256];
		int		tmpiRet;

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u %s"  ),  pQMem->messengerInfo.idInfo.ui64Id,  grpInfo.name  );
		if  (  grpInfo.usSubtype  ==  CONST_imGrpSubtype_msg  )  {
			iRet  =  0;  goto  errLabel;
		}
		else  {
			if  (  grpInfo.usSubtype  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%s)"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imGrpSubtypeTable  ),  grpInfo.usSubtype  ));
			else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%s)"  ),  tBuf, getResStr(  0,  &pQyMc->cusRes,  CONST_resId_imGrps_av  )  );
		}
		tmpiRet  =  SendMessage(  hCtl,  CB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    

		//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\t%d,  %s, idInfo is %I64u, talkerDesc %s"  ),  m_var.usItemCount,  qyGetDesByType1(  pTable,  uiType  ),  grpInfo.idInfo.ui64Id,  grpInfo.name  );
		OutputDebugString(  tBuf  );
		OutputDebugString(  _T(  "\n"  )  );
	}

	iRet  =  0;

errLabel:
	return  iRet;
}


//
 int  tmpHandler_avRes_fillImObjs_grp_myDb_mgr_hzj(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;

	QY_MC	*	pQyMc  =  QY_GET_GBUF(  );

	COMMON_PARAM		*	pCommonParam1	=		(  COMMON_PARAM  *  )p1;
	//
	HWND					hDlg			=		(  HWND  )pCommonParam1->p0;
	DLG_avRes_var		&	m_var			=		*(  DLG_avRes_var  *  )pCommonParam1->p1;
	CMyDb				*   pMyDb			=		(  CMyDb  *  )pCommonParam1->p2;
	//
	QMEM_qyImObj		*   pQMem			=		(  QMEM_qyImObj  *  )p2;

	//  MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	IM_GRP_INFO					grpInfo;

	
	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;



	if  (  pQMem->messengerInfo.uiType  ==  CONST_objType_imGrp  )
	{
		if  (  !g_dbFuncs.pf_bGetImGrpInfoBySth(  pMyDb,  CONST_dbType_myDb,  pQMem->messengerInfo.misServName,  &pQMem->messengerInfo.idInfo,  &grpInfo  )  )  {
			memset(  &grpInfo,  0,  sizeof(  grpInfo  )  );
		}
		
		HWND	hCtl	=	GetDlgItem(  hDlg,  m_var.guiData.iIDC_COMBO_grp  );
		//  TCHAR	tBuf[256];
		int		tmpiRet;

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u %s"  ),  pQMem->messengerInfo.idInfo.ui64Id,  grpInfo.name  );
		if  (  grpInfo.usSubtype  ==  CONST_imGrpSubtype_msg  )  {
			iRet  =  0;  goto  errLabel;
		}
		if  (  grpInfo.usSubtype  !=  CONST_imGrpSubtype_initConf  )  {
			iRet  =  0;  goto  errLabel;
		}
		//
		{
			if  (  grpInfo.usSubtype  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%s)"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imGrpSubtypeTable  ),  grpInfo.usSubtype  ));
			else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%s)"  ),  tBuf, getResStr(  0,  &pQyMc->cusRes,  CONST_resId_imGrps_av  )  );
		}
		tmpiRet  =  SendMessage(  hCtl,  CB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    

		//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\t%d,  %s, idInfo is %I64u, talkerDesc %s"  ),  m_var.usItemCount,  qyGetDesByType1(  pTable,  uiType  ),  grpInfo.idInfo.ui64Id,  grpInfo.name  );
		OutputDebugString(  tBuf  );
		OutputDebugString(  _T(  "\n"  )  );
	}

	iRet  =  0;

errLabel:
	return  iRet;
}




//
 void  avRes_fillImObjs_grp_myDb(  HWND  hDlgAvRes,  DLG_avRes_var  *  pVar,  void  *  pDb  )
{
	CMyDb  *  pMyDb  =  (  CMyDb  *  )pDb;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	DLG_avRes_var  &m_var  =  *pVar;

	CDlgDynBmps  *  pDlgDynBmps  =  (  CDlgDynBmps  *  )CWnd::FromHandlePermanent(  m_var.guiData.hDlgDynBmps  );
	if  (  !pDlgDynBmps  )  return;
	DLG_dynBmps_var  *  pDynBmpsVar  =  pDlgDynBmps->get_pm_var(  );
	if  (  !pDynBmpsVar  )  goto  errLabel;
		
	//
	COMMON_PARAM				commonParam1;

	//
	int  iVwSubtype  =  pDlgDynBmps->getWndContentSubtype(  );

	//
	if  (  iVwSubtype  ==  CONST_vwSubtype_avStream  )  {

		TCHAR						tBuf[256];
		IM_GRP_INFO					grpInfo;
	
		QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
		if  (  !pDbFuncs  )  goto  errLabel;
		QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;



		if  (  !g_dbFuncs.pf_bGetImGrpInfoBySth(  pMyDb,  CONST_dbType_myDb,  _T(  ""  ),  &pDynBmpsVar->vWall.idInfo_grp_avStream,  &grpInfo  )  )  {
			memset(  &grpInfo,  0,  sizeof(  grpInfo  )  );
		}
		
		HWND	hCtl	=	GetDlgItem(  hDlgAvRes,  m_var.guiData.iIDC_COMBO_grp  );
		//  TCHAR	tBuf[256];
		int		tmpiRet;

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u %s"  ),  pDynBmpsVar->vWall.idInfo_grp_avStream.ui64Id,  grpInfo.name  );
		//
		{
			if  (  grpInfo.usSubtype  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%s)"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imGrpSubtypeTable  ),  grpInfo.usSubtype  ));
			else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%s)"  ),  tBuf, getResStr(  0,  &pQyMc->cusRes,  CONST_resId_imGrps_av  )  );
		}
		tmpiRet  =  SendMessage(  hCtl,  CB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    



		return;
	}




	//
	MACRO_makeCommonParam3(  hDlgAvRes,  pVar,  pDb,  commonParam1  );	

	if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hzj  )  {
		  qTraverse(  pMyDb->m_var.pQ_qyImObjTab,  tmpHandler_avRes_fillImObjs_grp_myDb_mgr_hzj,  NULL,  &commonParam1  );
		}
	else  {
		  qTraverse(  pMyDb->m_var.pQ_qyImObjTab,  tmpHandler_avRes_fillImObjs_grp_myDb,  NULL,  &commonParam1  );
	}

#if  0
	TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];
	CDBVariant		varVals[10];

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImObjTab.idStr,qyImObjTab.uiType,qyImGrpInfoTab.name from (qyImObjTab left join qyImGrpInfoTab on(qyImObjTab.misServName=qyImGrpInfoTab.misServName and qyImObjTab.idStr=qyImGrpInfoTab.idStr ) )"  )  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s where qyImObjTab.uiType in(%d)"  ),  sqlBuf,  CONST_objType_imGrp  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s order by qyImObjTab.idStr"  ),  sqlBuf  );

	enumSqlQuery(  pDb,  sqlBuf,  (  PF_commonHandler  )tmpHandler_fillImObjs_imGrp,  hDlg,  pVar,  varVals,  mycountof(  varVals  ),  NULL  );	
#endif

errLabel:
	return;
}




//
BOOL CDlgAvRes::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	int  iErr  =  -1;
		QY_MC					*	pQyMc	=	QY_GET_GBUF(  );
	QM_dbFuncs				&	g_dbFuncs  =  *pQyMc->p_g_dbFuncs;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	QY_OBJ_DB				*	pObjDb  =  pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );
	if  (  !pObjDb  )  return  -1;

	//
	m_dropTree.SubclassDlgItem(  m_var.guiData.iIDC_tree,  this  );
	m_dropTree.m_var.iSubtype  =  CONST_tvSubtype_avRes;

	//
	fillLayout(  m_hWnd,  &m_var  );
	
	
	
	//
	avRes_fillImObjs_grp_myDb(  m_hWnd,  &m_var,  pObjDb->pDb  );



	//
	bInitialDisplay();

	//
	bDisplayContent();
	//
	m_TreeCtrl->Expand(  this->m_var.htMyRootItem,  TVE_EXPAND  );

	//
	SetWindowText(  CONST_str_avResTitle  );

	//
		CComboBox  *  pCb  =  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_grp  );
		pCb->SetCurSel(  0  );
		//
		this->OnCbnSelchangeCombogrp(  );
		//
		pCb  =  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_layout  );
		pCb->SetCurSel(  0  );
		//
		this->OnCbnSelchangeCombolayout(  );

	if  (  m_var.m_nID  ==  IDD_avRes_mgr_hzj
		||  m_var.m_nID  ==  IDD_avRes_mem_hzj  )  
	{
			
		//
		if  (  m_var.m_nID  ==  IDD_avRes_mgr_hzj  )  {
			if  (  pProcInfo->hzj.bConfStarted  )  SetDlgItemText(  IDC_BUTTON_av,  _T(  "取消会议"  )  );
			else  SetDlgItemText(  IDC_BUTTON_av,  _T(  "启动会议"  )  );
		}
		else  if  (  m_var.m_nID  ==  IDD_avRes_mem_hzj  )  {
				  this->refreshAvResCallStatus(  );
		}

	}

	//
	SetTimer(  1,  500,  NULL  );

	//
	iErr  =  0;

errLabel:

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgAvRes::OnCbnSelchangeCombogrp()
{
	// TODO: Add your control notification handler code here
	TCHAR  tBuf[128]  =  _T(  "77 8"  );
	int  k  =  _ttof(  tBuf  );

	GetDlgItemText(  m_var.guiData.iIDC_COMBO_grp,  tBuf,  _countof(  tBuf  )  );
	unsigned  __int64  ui64Id  =  _ttof(  tBuf  );
	if  (  !ui64Id  )  return;

	//
	m_var.idInfo_grp_sel.ui64Id  =  ui64Id;

	//
	treeCtrl_DelAllChildOfItem(  m_TreeCtrl,  m_var.htMyRootItem  );

	//
	bDisplayContent(  );

	//



errLabel:
	return;
}




//
void CDlgAvRes::OnTvnBegindragavrestree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	HTREEITEM  hBeforeDraw  =  (  (LPNMTREEVIEW)pNMHDR)->itemOld.hItem;

	//
	*pResult = 0;
}













void CDlgAvRes::OnCbnSelchangeCombolayout()
{
	// TODO: Add your control notification handler code here
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	CString  str;
	GetDlgItemText(  m_var.guiData.iIDC_COMBO_layout,  str  );
	//
	str.Trim(  );
	if  (  !str.GetLength(  )  )  return;
	//
	TCHAR  tBuf[MAX_PATH];
	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s%s.qvw"  ),  pQyMc->cfg.installDir,  _T(  CONST_qvwSubDir  ),  str  );
	//
	int  ii  =  0;
	//
	dynBmps_openFile(  tBuf,  m_var.guiData.hDlgDynBmps  );

}




void CDlgAvRes::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//
	if  (  nHitTest  ==  HTCAPTION  )  {
	
		int  ii  =  0;
		//
		m_var.bLocked  =  TRUE;
		//
		SetWindowText(  _T(  "Locked"  )  );
	}

	//
	CDialogEx::OnNcLButtonDown(nHitTest, point);
}






//
int  tmp_addTvItem(  CDlgAvRes  *  pDlg,  QY_MESSENGER_ID  *  pIdInfo_mem,  HTREEITEM	   htRoot,  BOOL  bConn,  BOOL  *  pbInserted  )
{
	int  iErr  =  0;

		 //
	 QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli( );
	 MIS_CNT  *  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 //  CTreeCtrl *  m_TreeCtrl  =  pLeftView->m_TreeCtrl;
	 CTreeCtrl  *  m_TreeCtrl  =  pDlg->m_TreeCtrl;
	 //HTREEITEM	   htRoot = pDlg->m_var.htMyRootItem0;	

	 BOOL  bInserted  =  FALSE;

	 //
	 CQnmDb				db;
			 
	 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
	 //	
	 CMyDb			*	pDb											=	(  CMyDb  *  )db.m_pDbMem->pDb;
		
	  //
	 QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	 if  (  !pDbFuncs  )  goto  errLabel;
	 QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;



		 //>
		 #if  10

		   //
		   //  下面增加一个我节点
		   //
		   //iObjType  =  CONST_objType_me;
		   //myTChar2Utf8(  _T(  "me"  ),  buf,  mycountof(  buf  )  );
		   int  iObjId  =  pIdInfo_mem->ui64Id;	//  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );
		   if  (  iObjId  <  0  )  goto  errLabel;

		   QY_MESSENGER_REGINFO  regInfo;
		   QY_MESSENGER_REGINFO  *pRegInfo  =  &regInfo;
		   TCHAR  tBuf[128];
		   TCHAR  displayName[128];
		   TCHAR  talkerDesc[128];
		   MY_REG_DESC  desc;
		   
		   QM_OBJQ_MEM				mem;
		   unsigned  short			usRunningStatus  =  0;
		   int  nImage,  nSelectedImage;
		   HTREEITEM  tmphtItem;
		   
		   //
		   //
					//
					int  iDbType  =  CONST_dbType_myDb;
					if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pDb,  iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  _T(  ""  ),  pIdInfo_mem,  0,  &regInfo  )  )  {
						memset(  &regInfo,  0,  sizeof(  regInfo  )  );
					}

				    
					//						
					//
					if  (  regInfo2Desc(  0,  pRegInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  displayName,  mycountof(  displayName  )  )  )  goto  errLabel;
			 	
		   
		   
		   //
		   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s(%I64u)"  ),  displayName,  pIdInfo_mem->ui64Id  );
		   //
		   if  (  findQMemByKey(  0,  pMisCnt->pObjQ,  &pMisCnt->idInfo,  &mem  )  )  usRunningStatus  =  CONST_usRunningStatus_offline;
		   else  {
			     QMEM_MESSENGER_CLI	*	pQMem;
			     pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
				 usRunningStatus  =  pQMem->usRunningStatus;
		   }
		   //
		   getMessengerImages(  pQyMc,  usRunningStatus,  &nImage,  &nSelectedImage  );
			
		   //
		   if  (  pDlg->m_var.guiData.iVwSubtype  ==  CONST_vwSubtype_avStream  )  {
			   if  (  isActiveMem(  pDlg,  pIdInfo_mem  )  )  {
					 //  nImage  =  pQyMc->cfg.image.nImage_connectedDev;
				     nImage  =  pQyMc->cfg.image.nImage_mic;
				     //  nSelectedImage  =  pQyMc->cfg.image.nImage_connectedDev;
					 nSelectedImage  =  pQyMc->cfg.image.nImage_mic;
			   }
			   }
		   else  {
			     if  (  bConn  )  {
					 nImage  =  pQyMc->cfg.image.nImage_connectedDev;
				     nSelectedImage  =  pQyMc->cfg.image.nImage_connectedDev;
				 }
		   }

		   //
		   if  (  !(  tmphtItem  =  treeCtrl_FindItemData(  m_TreeCtrl,  iObjId,  TRUE,  htRoot  )  )  )  {
			   tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
													  displayName,  
													  nImage,  
													  nSelectedImage,  
													  TVIS_EXPANDPARTIAL,  
													  TVIS_STATEIMAGEMASK, 
													  iObjId,  
													  htRoot,  
													  TVI_LAST  );
			   //  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );  //  
			
			   //
			   bInserted  =  TRUE;

				}
		   else  {				  
			     //  只刷新展开节点
				 TVITEM				tvItem;
				 
				 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
				 tvItem.hItem  =  tmphtItem;
				 tvItem.pszText  =  tBuf;
				 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				 m_TreeCtrl->GetItem(  &tvItem  );
				 
				 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
					 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
					 tvItem.iImage  =  nImage;
					 tvItem.iSelectedImage  =  nSelectedImage;
					 m_TreeCtrl->SetItem(  &tvItem  );
				 }


		   }
#endif


		   iErr  =  0;

errLabel:

		   //
		   if  (  pbInserted  )  *pbInserted  =  bInserted;

		   return  iErr;
}






//
//
int  tmp_refreshTvItem(  CDlgAvRes  *  pDlg,  QY_MESSENGER_ID  *  pIdInfo_mem,  HTREEITEM	   htRoot,  BOOL  bConn  )
{
	int  iErr  =  0;

		 //
	 QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli( );
	 MIS_CNT  *  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 //  CTreeCtrl *  m_TreeCtrl  =  pLeftView->m_TreeCtrl;
	 CTreeCtrl  *  m_TreeCtrl  =  pDlg->m_TreeCtrl;
	 //HTREEITEM	   htRoot = pDlg->m_var.htMyRootItem0;	


	 //
	 CQnmDb				db;
			 
	 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
	 //	
	 CMyDb			*	pDb											=	(  CMyDb  *  )db.m_pDbMem->pDb;
		
	  //
	 QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	 if  (  !pDbFuncs  )  goto  errLabel;
	 QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;



		 //>
		 #if  10

		   //
		   //  下面增加一个我节点
		   //
		   //iObjType  =  CONST_objType_me;
		   //myTChar2Utf8(  _T(  "me"  ),  buf,  mycountof(  buf  )  );
		   int  iObjId  =  pIdInfo_mem->ui64Id;	//  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );
		   if  (  iObjId  <  0  )  goto  errLabel;

		   QY_MESSENGER_REGINFO  regInfo;
		   QY_MESSENGER_REGINFO  *pRegInfo  =  &regInfo;
		   TCHAR  tBuf[128];
		   TCHAR  displayName[128];
		   TCHAR  talkerDesc[128];
		   MY_REG_DESC  desc;
		   
		   QM_OBJQ_MEM				mem;
		   unsigned  short			usRunningStatus  =  0;
		   int  nImage,  nSelectedImage;
		   HTREEITEM  tmphtItem;
		   
		   //
		   //
					//
					int  iDbType  =  CONST_dbType_myDb;
					if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pDb,  iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  _T(  ""  ),  pIdInfo_mem,  0,  &regInfo  )  )  {
						memset(  &regInfo,  0,  sizeof(  regInfo  )  );
					}

				    
					//						
					//
					if  (  regInfo2Desc(  0,  pRegInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  displayName,  mycountof(  displayName  )  )  )  goto  errLabel;
			 	
		   
		   
		   //
		   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s(%I64u)"  ),  displayName,  pIdInfo_mem->ui64Id  );
		   //
		   if  (  findQMemByKey(  0,  pMisCnt->pObjQ,  &pMisCnt->idInfo,  &mem  )  )  usRunningStatus  =  CONST_usRunningStatus_offline;
		   else  {
			     QMEM_MESSENGER_CLI	*	pQMem;
			     pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
				 usRunningStatus  =  pQMem->usRunningStatus;
		   }
		   //
		   getMessengerImages(  pQyMc,  usRunningStatus,  &nImage,  &nSelectedImage  );
			
		   //
		   if  (  bConn  )  {
			   nImage  =  pQyMc->cfg.image.nImage_connectedDev;
			   nSelectedImage  =  pQyMc->cfg.image.nImage_connectedDev;
		   }
		   //
		   if  (  !(  tmphtItem  =  treeCtrl_FindItemData(  m_TreeCtrl,  iObjId,  TRUE,  htRoot  )  )  )  {

				}
		   else  {				  
			     //  只刷新展开节点
				 TVITEM				tvItem;
				 
				 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
				 tvItem.hItem  =  tmphtItem;
				 tvItem.pszText  =  tBuf;
				 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				 m_TreeCtrl->GetItem(  &tvItem  );
				 
				 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
					 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
					 tvItem.iImage  =  nImage;
					 tvItem.iSelectedImage  =  nSelectedImage;
					 m_TreeCtrl->SetItem(  &tvItem  );
				 }


		   }
#endif


		   iErr  =  0;

errLabel:

		
		   return  iErr;
}





//
int  tmp_addTvItem_res(  CDlgAvRes  *  pDlg,  QY_MESSENGER_ID  *  pIdInfo_mem,  HTREEITEM	   htRoot  )
{
	int  iErr  =  0;

		 //
	 QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli( );
	 MIS_CNT  *  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 //  CTreeCtrl *  m_TreeCtrl  =  pLeftView->m_TreeCtrl;
	 CTreeCtrl  *  m_TreeCtrl  =  pDlg->m_TreeCtrl;
	 //HTREEITEM	   htRoot = pDlg->m_var.htMyRootItem0;	


	 //
	 CQnmDb				db;
			 
	 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
	 //	
	 CMyDb			*	pDb											=	(  CMyDb  *  )db.m_pDbMem->pDb;
		
	  //
	 QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	 if  (  !pDbFuncs  )  goto  errLabel;
	 QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;


		   //
		   //
		   int  iObjId  =  0;
		   
		   TCHAR  tBuf[128];
		   TCHAR  displayName[128];
		   
		   int  nImage,  nSelectedImage;
		   HTREEITEM  tmphtItem;
		   
		   //
		   //
		   //
		   //getMessengerImages(  pQyMc,  usRunningStatus,  &nImage,  &nSelectedImage  );
		   HTREEITEM  htItem_msgr  =  treeCtrl_FindItemData(  m_TreeCtrl,  pIdInfo_mem->ui64Id,  TRUE,  htRoot  );
		   if  (  !htItem_msgr  )  goto  errLabel;

		   //
		   //int  tmp_i  =  pLeftView->m_TreeCtrl->GetItemData(  htItem_msgr  );

		   //
		   int  iObjType  =  CONST_objType_screen;
		   iObjId  =  iObjType;
		   //iObjId  =  CONST_objType_webcam;
		
		   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),   iObjType  )  ); 
		   //
		   //_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s%I64u"  ),  displayName,  pQMem->idInfo_mem.ui64Id  );
		   //
		   nImage  =  pQyMc->cfg.image.nImage_screen;  //16;//pQyMc->cfg.image.normal.nImage_pcNormal;	//  
		   nSelectedImage  =  nImage;

		   //
		   if  (  !(  tmphtItem  =  treeCtrl_FindChildItemData(  m_TreeCtrl,  iObjId,  TRUE,  htItem_msgr  )  )  )  {
			   tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
													  displayName,  
													  nImage,  
													  nSelectedImage,  
													  TVIS_EXPANDPARTIAL,  
													  TVIS_STATEIMAGEMASK, 
													  iObjId,  
													  htItem_msgr,  
													  TVI_LAST  );
			   //  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );  //  
				   

				}
		   else  {				  
			     //  只刷新展开节点
				 TVITEM				tvItem;
				 
				 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
				 tvItem.hItem  =  tmphtItem;
				 tvItem.pszText  =  tBuf;
				 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				 m_TreeCtrl->GetItem(  &tvItem  );
				 
				 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
					 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
					 tvItem.iImage  =  nImage;
					 tvItem.iSelectedImage  =  nSelectedImage;
					 m_TreeCtrl->SetItem(  &tvItem  );
				 }


		   }


		   //
		   iObjType  =  CONST_objType_webcam;
		   iObjId  =  iObjType;
		   //iObjId  =  CONST_objType_webcam;
		
		   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),   iObjType  )  ); 
		   //
		   //_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s%I64u"  ),  displayName,  pQMem->idInfo_mem.ui64Id  );
		   //
		   nImage  =  pQyMc->cfg.image.nImage_webcam;
		   nSelectedImage  =  nImage;

		   //
		   if  (  !(  tmphtItem  =  treeCtrl_FindChildItemData(  m_TreeCtrl,  iObjId,  TRUE,  htItem_msgr  )  )  )  {
			   tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
													  displayName,  
													  nImage,  
													  nSelectedImage,  
													  TVIS_EXPANDPARTIAL,  
													  TVIS_STATEIMAGEMASK, 
													  iObjId,  
													  htItem_msgr,  
													  TVI_LAST  );
			   //  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );  //  
				   

				}
		   else  {				  
			     //  只刷新展开节点
				 TVITEM				tvItem;
				 
				 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
				 tvItem.hItem  =  tmphtItem;
				 tvItem.pszText  =  tBuf;
				 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				 m_TreeCtrl->GetItem(  &tvItem  );
				 
				 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
					 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
					 tvItem.iImage  =  nImage;
					 tvItem.iSelectedImage  =  nSelectedImage;
					 m_TreeCtrl->SetItem(  &tvItem  );
				 }


		   }

		   //


	 

		   iErr  =  0;

errLabel:

		   return  iErr;
}



 int  tmpHandler_get_tmpGrp_idInfo(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int  iRet  =  -1;
	 COMMON_PARAM	*	pCommonParam	=  (  COMMON_PARAM  *  )p0;
	 //
	 QY_MESSENGER_ID  *  pIdInfo_tmpGrp  =  (  QY_MESSENGER_ID  *  )pCommonParam->p2;
	 //
	 BOOL				bUnprocedOnly	=	(  BOOL  )p1;
	 //
	 IM_GRP_INFO	*	pQMem			=  (  IM_GRP_INFO  *  )p2;
	 int				index			=  0;
	 QY_MC			*	pQyMc			=	QY_GET_GBUF();

	 QY_MESSENGER_ID  idInfo_superAdmin;
	 if  (  getIdInfo_superAdmin(  &idInfo_superAdmin  )  )  goto  errLabel;

	 if  (  pQMem->idInfo_creator.ui64Id  ==  idInfo_superAdmin.ui64Id  )  {
		 pIdInfo_tmpGrp->ui64Id  =  pQMem->idInfo.ui64Id;
		 iRet  =  1;  goto  errLabel;
	 }


	 iRet  =  0;
errLabel:
	 return  iRet;
 }


    int  tmpHandler_enumImGrpMemList(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int  iRet  =  -1;
	 COMMON_PARAM	*	pCommonParam	=  (  COMMON_PARAM  *  )p0;
	 //
	 IM_GRP_EX  *  pImGrpEx  =  (  IM_GRP_EX  *  )pCommonParam->p2;
	 //
	 BOOL				bUnprocedOnly	=	(  BOOL  )p1;
	 
	 
	 //
	 IM_GRP_MEM	*	pQMem			=  (  IM_GRP_MEM  *  )p2;
	 int				index			=  0;
	 QY_MC			*	pQyMc			=	QY_GET_GBUF();

	 if  (  pImGrpEx->common.idInfo.ui64Id  ==  pQMem->idInfo_grp.ui64Id  )  {
		 if  (  pImGrpEx->usCnt  <  mycountof(  pImGrpEx->mems  )  )  {
			 pImGrpEx->mems[pImGrpEx->usCnt].grpMmem_idInfo.ui64Id  =  pQMem->idInfo_mem.ui64Id;
			 pImGrpEx->usCnt  ++  ;
		 }
	 }

	 iRet   =  0;
errLabel:
	 return  iRet;
	
	
}

//
int  get_tmpGrp_idInfo(  IM_GRP_EX  *  p  )
{
	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	 QY_OBJ_DB					*	pObjDb				=				getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;

	 //
	 CMyDb				*	pDb	=	(  CMyDb  *  )pObjDb->pDb;


	 memset(  p,  0,  sizeof(  p[0]  )  );

	 //
	 QY_MESSENGER_ID  idInfo_tmpGrp  =  {0};
	 COMMON_PARAM  commonParam;
	 //
	 MACRO_makeCommonParam3(  0,  0,  &idInfo_tmpGrp,  commonParam  );
	 //if  (  qTraverse(  pDb->m_var.pQ_qyImObjTab,  tmpHandler_getIdInfo_superAdmin,  0,  &commonParam  )  <=  0  )  goto  errLabel;

	 if  (  qTraverse(  pDb->m_var.pQ_qyImGrpInfoTab,  tmpHandler_get_tmpGrp_idInfo,  &commonParam,  NULL  )  <=  0  )  goto  errLabel;

	 //
	 p->common.idInfo.ui64Id  =  idInfo_tmpGrp.ui64Id;

	 //
	 MACRO_makeCommonParam3(  0,  0,  p,  commonParam  );
	 //
	 qTraverse(  pDb->m_var.pQ_qyImGrpMemTab,  tmpHandler_enumImGrpMemList,  &commonParam,  NULL  );


	 //if  (  pIdInfo  )  pIdInfo->ui64Id  =  idInfo.ui64Id;

	 iErr  =  0;
errLabel:

	 return  iErr;

}




//
void CDlgAvRes::OnBnClickedButtonav()
{
	// TODO: Add your control notification handler code here
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli();
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
		 	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	int  i  =  0;

	if  (  !pProcInfo->hzj.bConfStarted  )  {

	IM_GRP_EX  req;
	memset(  &req, 0, sizeof( req )  );

	//
	IM_GRP_EX  imGrpEx  =  {0};
	if  (  get_tmpGrp_idInfo(  &imGrpEx  )
		||  0  )  {
		//	
		if  (  createTmpGrp(m_hWnd,  &req)  )  return;
	}
	else  {
		  if  (  modifyTmpGrp(  m_hWnd,  &imGrpEx  )  )  return;
		  req  =  imGrpEx;
	}
	//
	resetRootItems(  );
	//
	for  (  i  =  0;  i  <  req.usCnt;  i  ++  )  {
		 //
		BOOL  bConn  =  FALSE;
		BOOL  bActiveMem  =  FALSE;
		BOOL  bInserted  =  FALSE;
		 
		tmp_addTvItem(  this,  &req.mems[i].grpMmem_idInfo,  m_var.htMyRootItem0,  bConn,  &bInserted  );

		if  (  bInserted  )  {
			tmp_addTvItem_res(  this,  &req.mems[i].grpMmem_idInfo,  m_var.htMyRootItem0  );
		}

	}
	//
	m_TreeCtrl->Expand(  m_var.htMyRootItem0,  TVE_EXPAND  );
	m_TreeCtrl->SortChildren(  m_var.htMyRootItem0  );

		 avRes_displayContent_imObjs_isClient_myDb(  this,  0,  0  );

		 MIS_CNT  *  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
		 MACRO_prepareForTran();
		 int  iTaskId =  0;
		 int  uiTaskType  =  0;
		 unsigned  int  uiChannelType  =  0;
		 for  (  i  =  0;  i  <  req.usCnt;  i  ++  )  {
			  QY_MESSENGER_ID  idInfo_dst;
			  //
			  idInfo_dst.ui64Id  =  req.mems[i].grpMmem_idInfo.ui64Id;
			  if  (  idInfo_dst.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  continue;
			  
			  //
			  req.usOp  =  CONST_imOp_refresh;
			  
			  //
			  if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  iTaskId,  uiTaskType,  (  char  *  )&req,  sizeof(  req  ),  0,  0,  0,  &idInfo_dst,  uiChannelType,  NULL,  FALSE  )  )  goto  errLabel;

		 }

		 //
		 m_var.hzj.imGrpEx  =  req;


#if 10
		 //
		 int  index_sharedObj_localAv  =  getSharedObjIndex_localAv(  );
		 QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  index_sharedObj_localAv  );
		 SHARED_OBJ_USR  *  pSharedObjUsr  =  NULL;
		 for  (  i  =  0;  i  <  mycountof(  pSharedObj->usrs  );  i  ++  )  {
			  pSharedObjUsr  =  &pSharedObj->usrs[i];
			  if  (  IsWindow(  pSharedObjUsr->hWnd_starter  )  &&  pSharedObjUsr->iTaskId  )  {
				  HWND  hDlgTalk  =  pSharedObjUsr->hWnd_starter;					//  2018/11/16. 这里的处理是错的。发起任务不仅是talk
																					//  还有shareDynBmps, testLocalAv等。
				  int  iTaskId  =  pSharedObjUsr->iTaskId;
				  //
				  CHelp_getDlgTalkVar  help;
				  DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help.getVar(  hDlgTalk  );
				  unsigned  short  usOp  =  CONST_imOp_recv_cancel;
				  if  (  pDlgTalkVar  &&  pDlgTalkVar->av.taskInfo.bTaskExists  &&  pDlgTalkVar->av.taskInfo.ucbStarter  )  {
					  usOp  =  CONST_imOp_send_cancel;
				  }
				  //
			  	  PARAM_dlgTalk_procTask  param;
				  memset(  &param,  0,  sizeof(  param  )  );
				  pFuncs->pf_dlgTalk_procTask1(  hDlgTalk,  iTaskId,  usOp,  NULL,  &param  );  								    						    

			  }

		 }
		 //
		 pFuncs->pf_tryToFreeSharedObjs(  pProcInfo  );
#endif


		 ////////////
		 //
		 HWND  hTalk  =  NULL;
		 
		 BOOL  bNeedNotShowWnd  =  TRUE;
		 //
		 // bNeedNotShowWnd  =  FALSE;
		 //
		 talkToMessenger(  req.common.idInfo.ui64Id,  0,  bNeedNotShowWnd,  FALSE,  &hTalk  );
		 //
		 pProcInfo->doCmd_startAvCall(  NULL,  hTalk,  0,  0,  FALSE,  mynull  );

		 //
		 pProcInfo->hzj.idInfo_tmpGrp.ui64Id  =  req.common.idInfo.ui64Id;

		 pProcInfo->hzj.bConfStarted  =  TRUE;

		 SetDlgItemText(  IDC_BUTTON_av,  _T(  "取消会议"  )  );

	}
	else  {
		  HWND  hTalk;
		  if  (  !findTalker(  pQyMc,  &pProcInfo->hzj.idInfo_tmpGrp,  &hTalk  )  )  {
			  //dlgTalk_procTask1(
			  //PostMe
			  CHelp_getDlgTalkVar  help;
			  DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help.getVar(  hTalk  );
			  if  (  !pDlgTalkVar  )  goto  errLabel;
			  if  (  pDlgTalkVar->av.taskInfo.bTaskExists  )  {
				  int  iTaskId  =  pDlgTalkVar->av.taskInfo.iTaskId;


				  PARAM_dlgTalk_procTask  param;
				  memset(  &param,  0,  sizeof(  param  )  );
				  pFuncs->pf_dlgTalk_procTask1(  hTalk,  iTaskId,  CONST_imOp_send_cancel,  NULL,  &param  );  
			  }
		  }
		  //
		  pProcInfo->hzj.idInfo_tmpGrp.ui64Id  =  0;
		  pProcInfo->hzj.bConfStarted  =  FALSE;
		  //
		  SetDlgItemText(  IDC_BUTTON_av,  _T(  "启动会议"  )  );

	}







errLabel:

	return;

}


void CDlgAvRes::OnBnClickedButtoncfgconf()
{
	// TODO: Add your control notification handler code here
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli();
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
		 	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	int  i  =  0;

	if  (  !pProcInfo->hzj.bConfStarted  )  return;
	

	IM_GRP_EX  req;
	memset(  &req, 0, sizeof( req )  );

	//
	IM_GRP_EX  imGrpEx  =  {0};
	imGrpEx  =  m_var.hzj.imGrpEx;
	{
		  if  (  modifyTmpGrp(  m_hWnd,  &imGrpEx  )  )  return;
		  req  =  imGrpEx;
	}
	//
	resetRootItems(  );
	//
	for  (  i  =  0;  i  <  req.usCnt;  i  ++  )  {
		 //
		BOOL  bConn  =  FALSE;
		BOOL  bActiveMem  =  FALSE;
		BOOL  bInserted  =  FALSE;
		 
		tmp_addTvItem(  this,  &req.mems[i].grpMmem_idInfo,  m_var.htMyRootItem0,  bConn,  &bInserted  );

		if  (  bInserted  )  {
			tmp_addTvItem_res(  this,  &req.mems[i].grpMmem_idInfo,  m_var.htMyRootItem0  );
		}

	}
	//
	m_TreeCtrl->Expand(  m_var.htMyRootItem0,  TVE_EXPAND  );
	m_TreeCtrl->SortChildren(  m_var.htMyRootItem0  );

		 avRes_displayContent_imObjs_isClient_myDb(  this,  0,  0  );


		 MACRO_prepareForTran();
		 int  iTaskId =  0;
		 int  uiTaskType  =  0;
		 unsigned  int  uiChannelType  =  0;
		 for  (  i  =  0;  i  <  req.usCnt;  i  ++  )  {
			  QY_MESSENGER_ID  idInfo_dst;
			  //
			  idInfo_dst.ui64Id  =  req.mems[i].grpMmem_idInfo.ui64Id;
			  if  (  idInfo_dst.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  continue;
			  
			  //
			  req.usOp  =  CONST_imOp_refresh;
			  
			  //
			  if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  iTaskId,  uiTaskType,  (  char  *  )&req,  sizeof(  req  ),  0,  0,  0,  &idInfo_dst,  uiChannelType,  NULL,  FALSE  )  )  goto  errLabel;

		 }

		 //
		 m_var.hzj.imGrpEx  =  req;

errLabel:

		 return;
}


//
int  tmpHandler_getIdInfo_superAdmin(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iErr  =  -1;
	COMMON_PARAM  *  pCommonParam  =  (  COMMON_PARAM  *  )p1;
	QY_MESSENGER_ID  *  pIdInfo  =  (  QY_MESSENGER_ID  *  )pCommonParam->p2;

	QMEM_qyImObj		*   pQMem			=		(  QMEM_qyImObj  *  )p2;

	if  (  pQMem->messengerInfo.uiType  !=  CONST_objType_imGrp
		&&  pQMem->messengerInfo.iRole  ==  CONST_imObjRole_superAdmin  )  
	{
		pIdInfo->ui64Id  =  pQMem->messengerInfo.idInfo.ui64Id;
		iErr  =  1;  goto  errLabel;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}

//
int  getIdInfo_superAdmin(  QY_MESSENGER_ID  *  pIdInfo  )
{
	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	 QY_OBJ_DB					*	pObjDb				=				getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;



	 //
	 CMyDb				*	pDb	=	(  CMyDb  *  )pObjDb->pDb;

	 //  2014/05/27
	 //qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayContent_imObjs_isClient_myDb, addObjRegInfo starts ..."  )  );

	 //  下面增加新增的节点	
	 //
	 //  先将注册用户的单位放入视图
	 //QY_MESSENGER_REGINFO	regInfo;
	 QY_MESSENGER_ID  idInfo  =  {0};
	 COMMON_PARAM  commonParam;
	 //
	 MACRO_makeCommonParam3(  0,  0,  &idInfo,  commonParam  );
	 if  (  qTraverse(  pDb->m_var.pQ_qyImObjTab,  tmpHandler_getIdInfo_superAdmin,  0,  &commonParam  )  <=  0  )  goto  errLabel;

	 if  (  pIdInfo  )  pIdInfo->ui64Id  =  idInfo.ui64Id;

	 iErr  =  0;
errLabel:

	 return  iErr;

}



void CDlgAvRes::OnBnClickedButtoncall()
{
	// TODO: Add your control notification handler code here
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli();
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );

	//
	QY_MESSENGER_ID  idInfo_superAdmin;
	if  (  getIdInfo_superAdmin(  &idInfo_superAdmin  )  )  return;

	int  ii  =  0;
			 	 
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	
	
	BOOL  bConfStarted  =  FALSE;
	BOOL  bCanSpeak  =  FALSE;
	BOOL  bConnStarted  =  FALSE;
		//
	
		getCallStatus(  &bConfStarted,  &bCanSpeak,  &bConnStarted  );

		if  (  bConfStarted  )  {
			HWND  hTalk  =  NULL;
			if  (  !findTalker(  pQyMc,  &pProcInfo->hzj.idInfo_tmpGrp,  &hTalk  )  )  {
				//
				CHelp_getDlgTalkVar  help;
				DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help.getVar(  hTalk  );
				if  (  !pDlgTalkVar  )  goto  errLabel;
				//
				pFuncs->pf_setCurSharedObjUsr_localAv(  pProcInfo,  pDlgTalkVar->av.iIndex_sharedObj_localAv,  pDlgTalkVar->av.iIndex_usr_localAv  );

				if  (  bCanSpeak  )  dlgTalk_requestToSpeak(  hTalk,  FALSE  );
				else  dlgTalk_requestToSpeak(  hTalk,  TRUE  );
			}
			}
		else  {
			  HWND  hTalk  =  NULL;
		 		 
			  if  (  bConnStarted  )  {
				  if  (  !findTalker(  pQyMc,  &idInfo_superAdmin,  &hTalk  )  )  {
					  CHelp_getDlgTalkVar  help;
					  DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help.getVar(  hTalk  );
					  if  (  pDlgTalkVar  &&  pDlgTalkVar->av.taskInfo.bTaskExists  )  {
						  int  iTaskId  =  pDlgTalkVar->av.taskInfo.iTaskId;

						  
						  PARAM_dlgTalk_procTask  param;
						  memset(  &param,  0,  sizeof(  param  )  );				
						  
						  unsigned  short  usOp  =  pDlgTalkVar->av.taskInfo.ucbStarter  ?  CONST_imOp_send_cancel  :  CONST_imOp_recv_cancel;
						  
						  pFuncs->pf_dlgTalk_procTask1(  hTalk,  iTaskId,  usOp,  NULL,  &param  );  
		
					  }

					  //::PostMessage(  hTalk,  WM_CLOSE,  0,  0  );
				  }
				  //
				  }
			  else  {
		 
					BOOL  bNeedNotShowWnd  =  TRUE;
		 
					//
					//bNeedNotShowWnd  =  FALSE;
		
					//
					talkToMessenger(  idInfo_superAdmin.ui64Id,  0,  bNeedNotShowWnd,  FALSE,  &hTalk  );
					//
					pProcInfo->doCmd_startAvCall(  NULL,  hTalk,  0,  0,  FALSE,  mynull  );
			  }
		}


errLabel:
	return;
}


//
int  CDlgAvRes::getCallStatus(  BOOL  *  pbConfStarted,  BOOL  *  pbCanSpeak,  BOOL  *  pbConnStarted  )
{
	int  iErr  =  -1;
		MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );

	//
	BOOL  bConfStarted  =  FALSE;
	BOOL  bCanSpeak  =  FALSE;
	BOOL  bConnStarted  =  FALSE;

	//
	if  (  m_var.m_nID  ==  IDD_avRes_mem_hzj  )  {
		HWND  hTalk  =  0;
		//
		//
		if  (  pProcInfo->hzj.idInfo_tmpGrp.ui64Id  )  {
			int  ii  =  0;
			//
			if  (  !findTalker(  pQyMc,  &pProcInfo->hzj.idInfo_tmpGrp,  &hTalk  )  )  {
				CHelp_getDlgTalkVar  help;
				DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help.getVar(  hTalk  );
				if  (  pDlgTalkVar  &&  pDlgTalkVar->av.taskInfo.bTaskExists  )  {
					bConfStarted  =  TRUE;
					//
					bCanSpeak  =  dlgTalk_canSpeak(  hTalk  );
					//)  SetDlgItemText(  IDC_BUTTON_call,  _T(  "停止发言"  )  );
					//else  SetDlgItemText(  IDC_BUTTON_call,  _T(  "申请发言"  )  );
				}
			}
		}
		
		//		
		if  (  !bConfStarted  )  {
				QY_MESSENGER_ID  idInfo_superAdmin  =  {0};
				getIdInfo_superAdmin(  &idInfo_superAdmin  );
				//
				if  (  !findTalker(  pQyMc,  &idInfo_superAdmin,  &hTalk  )  )  {
					CHelp_getDlgTalkVar  help;
					DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help.getVar(  hTalk  );
					if  (  pDlgTalkVar  &&  pDlgTalkVar->av.taskInfo.bTaskExists  )  {
						bConnStarted  =  TRUE;
					}
				}
				//
				//if  (  bConnStarted  )  SetDlgItemText(  IDC_BUTTON_call,  _T(  "取消通联"  )  );
				//else  SetDlgItemText(  IDC_BUTTON_call,  _T(  "通联"  )  );
		}
		
	}

	
	iErr  =  0;
errLabel:

	if  (  !iErr  )  {
		*pbConfStarted  =  bConfStarted;
		*pbCanSpeak  =  bCanSpeak;
		*pbConnStarted  =  bConnStarted;
	}

	return  iErr;
}



void CDlgAvRes::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	TCHAR  tBuf[128];
	//
	static  int  loopCtrl  =  0;  loopCtrl  ++  ;

	//
	if  (  m_var.m_nID  ==  IDD_avRes_mem_hzj  )  {
		//
		BOOL  bConfStarted  =  FALSE;
		BOOL  bCanSpeak  =  FALSE;
		BOOL  bConnStarted  =  FALSE;
		//
	
		getCallStatus(  &bConfStarted,  &bCanSpeak,  &bConnStarted  );

		
		if  (  bConfStarted  )  {
			if  (  bCanSpeak  )  SetDlgItemText(  IDC_BUTTON_call,  _T(  "停止发言"  )  );
			else  SetDlgItemText(  IDC_BUTTON_call,  _T(  "申请发言"  )  );

			//
			if  (  !m_var.hzj.imGrpEx.usCnt  )  {
				IM_GRP_EX  req  =  {0};
				//
				//CONST_imOp_recv_applyForOrgReq
				req.common.uiType  =  CONST_imCommType_imGrp;
				req.common.idInfo.ui64Id  =  pProcInfo->hzj.idInfo_tmpGrp.ui64Id;
				req.usOp  =  CONST_imOp_recv_applyForOrgReq;

				int  iTaskId  =  0;
				unsigned  int  uiTaskType  =  0;
				QY_MESSENGER_ID  idInfo_dst;
				getIdInfo_superAdmin(  &idInfo_dst  );
				unsigned  int  uiChannelType  =  0;
			  
				MACRO_prepareForTran(  );
			  //
			  if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  iTaskId,  uiTaskType,  (  char  *  )&req,  sizeof(  req  ),  0,  0,  0,  &idInfo_dst,  uiChannelType,  NULL,  FALSE  )  )  goto  errLabel;

			  //
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "send apply to retrieve imGrp %I64u info"  ),  req.common.idInfo.ui64Id  );
			  showInfo_open0(  0,  0,  tBuf  );
			}
			//
			}
		else  {
			  if  (  bConnStarted  )  SetDlgItemText(  IDC_BUTTON_call,  _T(  "取消通联"  )  );
			  else  SetDlgItemText(  IDC_BUTTON_call,  _T(  "通联"  )  );
		}
		
	}
	if  (  m_var.m_nID  ==  IDD_avRes_mgr_hzj  )  {
		if  (  !(  loopCtrl  %  6  )  )  {  
			//
			avRes_displayContent_imObjs_isClient_myDb(  this,  0,  0  );
		}

	}
	if  (  m_var.m_nID  ==  IDD_avRes  )  {  //  2018/12/20
		if  (  !(  loopCtrl  %  6  )  )  {  
			//
			avRes_displayContent_imObjs_isClient_myDb(  this,  0,  0  );
		}
	}

errLabel:

	CDialogEx::OnTimer(nIDEvent);
}


//
  int  getMenuStatus_avRes(  QY_MC  *  pQyMc,  void  *  p0,  void  *  p1,  void  *  piStatusParam  )
{
	 int						iErr		=	-1;
	 QY_MC_SEL		*		pSel			=	(  QY_MC_SEL  *  )p0;
	 CDlgAvRes		*		pDlg		=	(  CDlgAvRes  *  )pSel->pWnd;
	 int						iMenuId		=	(  int  )p1;
	 int				*		piStatus	=	(  int  *  )piStatusParam;
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );

	 if  (  !pQyMc  )  return  -1;
	 if  (  !piStatus  )  return  -1;

 	DLG_avRes_var  &m_var  =  pDlg->m_var;


	QY_MESSENGER_ID  idInfo_superAdmin  =  {0};
	getIdInfo_superAdmin(  &idInfo_superAdmin  );
	if  (  pMisCnt->idInfo.ui64Id  !=  idInfo_superAdmin.ui64Id  )  {
		*piStatus  =  -1;
		iErr  =  0;  goto  errLabel;
	}


	//
	QY_MESSENGER_ID  idInfo_sel;
	idInfo_sel.ui64Id  =  pSel->u.rootTree.iHelpId;
	

	//
	switch  (  iMenuId  )  {
			case  ID_tonglian:
				  //
				  if  (  idInfo_sel.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					  *piStatus  =  -1;
					  iErr  =  0;  goto  errLabel;
				  }
				  //				  
				  if  (  bTonglian(  &idInfo_sel  )  )  *piStatus  =  -1;
				  break;
			case  ID_cancelTonglian:
				  //
				  if  (  idInfo_sel.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					  *piStatus  =  -1;
					  iErr  =  0;  goto  errLabel;
				  }
				  //
				  if  (  !bTonglian(  &idInfo_sel  )  )  *piStatus  =   -1;
				  break;
			case  ID_requestToSpeak:
				  if  (  isActiveMem(  pDlg,  &idInfo_sel  )  )  *piStatus  =  -1;
				  break;
			case  ID_stopSpeaking:
				  if  (  !isActiveMem(  pDlg,  &idInfo_sel  )  )  *piStatus  =  -1;
				  break;
			default:
					break;
	}


	 iErr  =  0;
errLabel:
	 return  iErr;
}


  //
BOOL  bTonglian(  QY_MESSENGER_ID  *  pIdInfo  )
{
	BOOL  bRet  =  FALSE;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );

	HWND  hTalk  =  NULL;

	if  (  !findTalker(  pQyMc,  pIdInfo,  &hTalk  )  )  {
	
		CHelp_getDlgTalkVar  help;
		DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help.getVar(  hTalk  );
		if  (  pDlgTalkVar  &&  pDlgTalkVar->av.taskInfo.bTaskExists  )  {
			bRet  =  TRUE;  goto  errLabel;
		}

	}

errLabel:
	return  bRet;
}


  //
int  doTonglian(  QY_MESSENGER_ID  *  pIdInfo  )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	HWND  hTalk  =  NULL;
			BOOL  bNeedNotShowWnd  =  TRUE;
		 
					//
					//bNeedNotShowWnd  =  FALSE;
		
					//
					talkToMessenger(  pIdInfo->ui64Id,  0,  bNeedNotShowWnd,  FALSE,  &hTalk  );
					//
					pProcInfo->doCmd_startAvCall(  NULL,  hTalk,  0,  0,  FALSE,  mynull  );


					return  0;
			
}


int  doCancelTonglian(  QY_MESSENGER_ID  *  pIdInfo  )
{
	int   iErr  =  -1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	HWND  hTalk  =  NULL;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  "" )    );


	if  (  !findTalker(  pQyMc,  pIdInfo,  &hTalk  )  )  {
			  //PostMe
			  CHelp_getDlgTalkVar  help;
			  DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help.getVar(  hTalk  );
			  if  (  !pDlgTalkVar  )  goto  errLabel;
			  if  (  pDlgTalkVar->av.taskInfo.bTaskExists  )  {
				  int  iTaskId  =  pDlgTalkVar->av.taskInfo.iTaskId;
				  
				  PARAM_dlgTalk_procTask  param;
				  memset(  &param,  0,  sizeof(  param  )  );

				  unsigned  short  usOp  =  pDlgTalkVar->av.taskInfo.ucbStarter  ?  CONST_imOp_send_cancel  :  CONST_imOp_recv_cancel;
				  //pFuncs->pf_dlgTalk_procTask1(  hTalk,  iTaskId,  CONST_imOp_send_cancel,  NULL,  &param  );  
				  pFuncs->pf_dlgTalk_procTask1(  hTalk,  iTaskId,  usOp,  NULL,  &param  );  
			  }
	}

	iErr  =  0;
errLabel:

	return  iErr;
}

//
BOOL  isActiveMem(  CDlgAvRes  *  pDlgAvRes,  QY_MESSENGER_ID  *  pIdInfo  )
{
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );

	CDlgDynBmps  *  pDlgDynBmps  =  (  CDlgDynBmps  *  )CWnd::FromHandlePermanent(  pDlgAvRes->m_var.guiData.hDlgDynBmps  );
	int  vwSubtype  =  pDlgDynBmps->getWndContentSubtype(  );

	if  (  vwSubtype  !=  CONST_vwSubtype_avStream  )  return  false;
	DLG_dynBmps_var  *  pm_var  =  pDlgDynBmps->get_pm_var(  );
	if  (  !pm_var  )  return  false;
	QY_MESSENGER_ID  idInfo_grp  =  pm_var->vWall.idInfo_grp_avStream;
	HWND  hMgr;
	if  (  findTalker(  pQyMc,  &idInfo_grp,  &hMgr  )  )  return  false;
	CHelp_getDlgTalkVar  help;
	DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help.getVar(  hMgr  );
	if  (  !pDlgTalkVar  )  return  false;

	//
	if  (  !pDlgTalkVar->av.taskInfo.bTaskExists  )  return false;
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pDlgTalkVar->av.taskInfo.iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  false;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  false;
	QMC_taskData_conf *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;



	return  isMemFromActive(  &pTc->videoConference,  pIdInfo,  mynull,  NULL  );
}

//
void CDlgAvRes::OnNMRClickavrestree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	QY_MC			*		pQyMc			=		QY_GET_GBUF(  );
	//
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
		FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	//
	//  CQyMcDoc		*		pDoc			=		GetDocument(  );
	// POINT					point;
	CTreeCtrl		&		treeCtrl		=		*m_TreeCtrl;	//  GetTreeCtrl( );
	QY_MC_SEL				curSel;
	//HTREEITEM				hRoot			=		NULL;
	HTREEITEM				hCur			=		NULL;
	QY_EVENTINFO			tmpEventInfo;

		//
	CMenu				tmpMenu;
	CMenu			*	tmppPopupMenu		=		NULL;


	traceLogA(  "CLeftView::OnRclick enters"  );

	/* Get the mouse cursor position */
	DWORD dwPos = GetMessagePos();

	/* Convert the co-ords into a CPoint structure */
	CPoint point( GET_X_LPARAM( dwPos ), GET_Y_LPARAM( dwPos ) ), spt;
	spt = point;

	//if ( !( hRoot = treeCtrl.GetRootItem( ) ) )		goto errLabel;
	
	/* Convert to screen co-ords for hittesting */
	treeCtrl.ScreenToClient( &spt );

	UINT test;
	hCur = treeCtrl.HitTest( spt, &test );
	
	/* Did the click occur on an item */
	if ( !hCur || !( test & ( TVHT_ONITEM | TVHT_ONITEMRIGHT ) ) )  goto errLabel;


	memset( &curSel, 0, sizeof( curSel ) );
	curSel.type		=		QY_SELTYPE_MCROOTTREE;
	curSel.u.rootTree.type  =  7;	//m_docStruct.u.treeList.tree.type;				//  2007/08/06
	curSel.u.rootTree.iDsnIndex  =  pQyMc->iDsnIndex_mainSys;	//m_docStruct.u.treeList.tree.iDsnIndex;	//  2007/01/02
	curSel.u.rootTree.hItem  =  hCur;		
	if  (  hCur  ==  m_var.htMyRootItem  ||  hCur  ==  m_var.htMyRootItem0  )  curSel.u.rootTree.bRoot		=		TRUE;	
	else  curSel.u.rootTree.iHelpId		=			treeCtrl.GetItemData(  hCur  );
	//
	curSel.pWnd  =  this;
	//
	HTREEITEM  hParentItem  =  treeCtrl.GetParentItem(  hCur  );
	if  (  hParentItem  !=  m_var.htMyRootItem
		&&  hParentItem  !=  m_var.htMyRootItem0  )  
	{
		goto  errLabel;
	}


	//if  (  m_docStruct.u.treeList.tree.pfProcTreeSel  &&  m_docStruct.u.treeList.tree.pfProcTreeSel(  pQyMc,  &curSel,  0  )  )  goto  errLabel;
#if  0
	pFuncs->pf_netMc_procTreeSel(  pQyMc,  &curSel,  NULL  );
	
	memset(  &tmpEventInfo,  0,  sizeof(  tmpEventInfo  )  );
	tmpEventInfo.type  =  CONST_qyEventType_rClick;
	tmpEventInfo.hWnd  =  this->m_hWnd;
	tmpEventInfo.click.x  =  point.x;
	tmpEventInfo.click.y  =  point.y;
  	
	//if  (  m_docStruct.u.treeList.tree.pfProcEvent  )  m_docStruct.u.treeList.tree.pfProcEvent(  pQyMc,  &curSel,  &tmpEventInfo  );
	pFuncs->pf_netMc_procTreeEvent(  pQyMc,  &curSel,  &tmpEventInfo  );
#endif

	//
	int					nPos				=		0;					//  2006/12/31
	QY_DMITEM		*	pItem;
		//
	unsigned  int		uCmd				=		0;

	QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  &pQyMc->cusRes  );
	if  (  !pResMem  )  return;

	 nPos  =  CONST_resId_popup_avRes;
	 if  (  m_var.guiData.iVwSubtype  ==  CONST_vwSubtype_avStream  )  nPos  =  CONST_resId_popup_instantAssistantMem;
				

	 	if  (  !nPos  )  goto  errLabel;

	if  (  !(  tmpMenu.CreatePopupMenu(  )  )  )  goto  errLabel;
	if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  CONST_resId_popupMenu  )  )  )  goto  errLabel;
	if  (  !(  pItem  =  qyGetDmItemByType(  pItem,  nPos,  sizeof(  QY_DMITEM  )  )  )  )  goto  errLabel;
	if  (	 makeDynaMenu(  &pQyMc->cusRes,  tmpMenu.m_hMenu,  (  QY_DMITEM  *  )pItem->pData,  getMenuStatus_avRes,  pQyMc,  &curSel  )  )  goto  errLabel;
	tmppPopupMenu  = &tmpMenu;

	if (tmppPopupMenu == NULL)  goto  errLabel;

	//  uCmd  =  ::TrackPopupMenu(  tmppPopupMenu->m_hMenu,  TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON  |  TPM_NONOTIFY,  screenPoint.x, screenPoint.y, 0,  this->m_hWnd, NULL);
	uCmd  =  ::TrackPopupMenuEx(  tmppPopupMenu->m_hMenu,  TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON  |  TPM_NONOTIFY,  point.x, point.y, this->m_hWnd, NULL);

	switch  (  uCmd  )  {
			case  ID_tonglian:  {
				  QY_MESSENGER_ID  idInfo_dst;
				  idInfo_dst.ui64Id  =  curSel.u.rootTree.iHelpId;
				  doTonglian( &idInfo_dst );
				  //
				  tmp_refreshTvItem(  this,  &idInfo_dst,  m_var.htMyRootItem0,  bTonglian(  &idInfo_dst  )  );
				  }
				  break;
			case  ID_cancelTonglian:  {
				  QY_MESSENGER_ID  idInfo_dst;
				  idInfo_dst.ui64Id  =  curSel.u.rootTree.iHelpId;
				  doCancelTonglian( &idInfo_dst );
				  //
				  tmp_refreshTvItem(  this,  &idInfo_dst,  m_var.htMyRootItem0,  bTonglian(  &idInfo_dst  )  );
				  
				  }
				  break;
			case  ID_requestToSpeak:  {
				  QY_MESSENGER_ID  idInfo_sel;
				  idInfo_sel.ui64Id  =  curSel.u.rootTree.iHelpId;
				  //
				  CHelp_getDlgTalkVar  help;
				  //
				  if  (  m_var.guiData.iVwSubtype  !=  CONST_vwSubtype_avStream  )  goto  errLabel;
				  CDlgDynBmps  *  pDlgDynBmps;
				  pDlgDynBmps  =  (  CDlgDynBmps  *  )CWnd::FromHandlePermanent(  m_var.guiData.hDlgDynBmps  );
				  if  (  !pDlgDynBmps  )  goto  errLabel;
				  DLG_dynBmps_var  *  pDynBmpsVar  =  (  DLG_dynBmps_var  *  )pDlgDynBmps->get_pm_var(  );
				  //
				  HWND  hMgr;
				  if  (  findTalker(  pQyMc,  &pDynBmpsVar->vWall.idInfo_grp_avStream,  &hMgr  )  )  goto  errLabel;
				  DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )help.getVar(  hMgr  );
				  if  (  !pMgrVar  )  goto  errLabel;
				  //				  	
				  if  (  idInfo_sel.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					  if  (  pMgrVar->av.taskInfo.ucbStarter  )  {
						  pProcInfo->confStarter_requestToSpeak(  hMgr,  &idInfo_sel,  NULL,  NULL,  TRUE  );
						  }		
					  else  {			  
						    //			  
						  confOthers_requestToSpeak(  hMgr,  pMgrVar->av.iIndex_sharedObj_localAv,  mynull,  TRUE  );		
					  }		
					  }	
				  else  {		  
					    //		  
					    confMgr_permitToSpeak(  hMgr,  &idInfo_sel,  TRUE  );	
				  }
				  //
				  }
				  break;
			case  ID_stopSpeaking:  {
				  QY_MESSENGER_ID  idInfo_sel;
				  idInfo_sel.ui64Id  =  curSel.u.rootTree.iHelpId;
				  //
				  CHelp_getDlgTalkVar  help;
				  //
				  if  (  m_var.guiData.iVwSubtype  !=  CONST_vwSubtype_avStream  )  goto  errLabel;
				  CDlgDynBmps  *  pDlgDynBmps;
				  pDlgDynBmps  =  (  CDlgDynBmps  *  )CWnd::FromHandlePermanent(  m_var.guiData.hDlgDynBmps  );
				  if  (  !pDlgDynBmps  )  goto  errLabel;
				  DLG_dynBmps_var  *  pDynBmpsVar  =  (  DLG_dynBmps_var  *  )pDlgDynBmps->get_pm_var(  );
				  //
				  HWND  hMgr;
				  if  (  findTalker(  pQyMc,  &pDynBmpsVar->vWall.idInfo_grp_avStream,  &hMgr  )  )  goto  errLabel;
				  DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )help.getVar(  hMgr  );
				  if  (  !pMgrVar  )  goto  errLabel;
				  //				  
				  if  (  idInfo_sel.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					  //		
					  dlgTalk_requestToSpeak(  hMgr,  FALSE  );
					  }	
				  else  {		  
					    //	
		  			    confMgr_permitToSpeak(  hMgr,  &idInfo_sel,  FALSE  );	
				  }
				  //
				  }
				  break;
			default:
					break;
	}




errLabel:


	*pResult = 0;
}
