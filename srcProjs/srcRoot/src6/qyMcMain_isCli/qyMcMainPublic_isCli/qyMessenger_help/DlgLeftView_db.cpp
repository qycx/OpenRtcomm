// DlgLeftView_db.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"


#include	"myresource.h"

#include	"qyMcMainWndProc.h"

#include	"qyMessenger_help.h"

#include	"DlgLeftView_db.h"
#include	"afxdialogex.h"


#include	"funcsForIsCliHelp.h"
#include	"isCliHelpPublic.h"
#include	"dlgtalkproc.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcCmdProc.h"
#include	"qyAvRecordPublic.h"
#include	"tmpCeLib.h"

#include	"myDb.h"

#include	"qyDynLib.h"
#include	"qyCusResTemp.h"
#include	"qmcSharePublic.h"
#include	"funcsForIsCliHelp.h"
#include	"isCliD3dPublic.h"
#include	"imgProcessPublic.h"
#include	"genericHash.h"
#include	"imObjHash.h"

#include	"qmcCommFunc_isCli.h"
#include	"qmcCopyData.h"
#include	"rtspUsrData.h"

#include	"qisPipe_open.h"

//
#include	"objType_tmp.h"
#include	"qyMessengerHelpPublic.h"
#include	"isCliExPublic.h"
#include	"GuiShare.h"


//
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
#ifdef  __DEBUG__
	    int  testSndRtspMsg(  );
#endif


#if  10
  __declspec(  dllexport  )  int viewDlgLeftView_db(  HWND  hParent,  int  iWndContentType,  void  *  pSelParam  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int								iErr					=	-1;
	QY_MC					*		pQyMc					=	QY_GET_GBUF(  );
	int								iServiceId				=	CONST_qyServiceId_mis;
	MC_VAR_isCli  			*		pProcInfo				=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	CDlgLeftView_db			*		pDlg					=	NULL;
	RECT							rect;

	HWND					*		phWnd_lv				=	NULL;

	QY_MC_SEL				*		pSel					=	(  QY_MC_SEL  *  )pSelParam;

	//
	showInfo_open0(  0,  0,  _T(  "viewDlgLeftView_db enters"  )  );

	//
	switch  (  iWndContentType  )  {
			case  CONST_qyWndContentType_imObjView_cli:					//  2017/01/04
				  phWnd_lv  =  &pProcInfo->hWnd_imObjView;
				  break;
			default:
					goto  errLabel;
					break;
	}

	//
	if  (  phWnd_lv  )  {
		if  (  IsWindow(  *phWnd_lv  )  )  {
			MACRO_SetForegroundWindow(  *phWnd_lv  );
			iErr  =  0;  goto  errLabel;
		}

		*phWnd_lv  =  NULL;
	}

	//
	CWnd  *  pParent  =  CWnd::GetDesktopWindow(  );
	if  (  IsWindow(  hParent  )  )  {
		pParent  =  CWnd::FromHandle(  hParent  );
	}
	pDlg  =  new  CDlgLeftView_db(  pParent  );
	if  (  !pDlg  )  goto  errLabel;

	//
	pDlg->m_var.iWndContentType  =  iWndContentType;
	if  (  !pDlg->bSetQyMcDoc(  pSel  )  )  goto  errLabel;
	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	//  pDlg->ShowWindow(  SW_SHOW  );

	//  2019/04/10		
	if  (  qyGetCustomId(  )  ==  CONST_qyCustomId_hbwj  )  {
		pDlg->ShowWindow(  SW_HIDE  );
		pDlg->ModifyStyleEx(  WS_EX_APPWINDOW,  WS_EX_TOOLWINDOW  );
		//  pDlg->ModifyStyleEx(  WS_EX_APPWINDOW,0);
		}
		
	pDlg->ShowWindow(  SW_SHOW  );


	//
	pSel->u.query.hFrame  =  pDlg->m_hWnd;		//  2009/09/03

	//
	if  (  phWnd_lv  )  *phWnd_lv  =  pDlg->m_hWnd;

	//
		 CDlgLeftView_db  *  pView  =  (  CDlgLeftView_db  *  )CWnd::FromHandlePermanent(  pProcInfo->hWnd_imObjView  );
	 if  (  !pView  )  goto  errLabel;




	//
	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}
	if  (  !iErr  )  {
	}

	//  traceLogA(  "viewMediaControl leaves, iErr is %d",  iErr  );
	showInfo_open0(  0,  0,  _T(  "viewDlgLeftView_db leaves"  )  );


	return  iErr;
}
#endif


 //
 int viewQnmStatus(  ) 
{
	 int						iRet						=		-1;
	 QY_MC					*	pQyMc						=		QY_GET_GBUF(  );
	 TCHAR						tmpExeName[MAX_PATH  +  1];
	 STARTUPINFO				si;
	 PROCESS_INFORMATION		pi;
	 BOOL						bProcessCreated				=		FALSE;
	 DWORD						dwRet;
	 
	 traceLogA(  "installDir is [%s]",  pQyMc->cfg.installDir  );

	 HWND hWnd;
	 if  (  hWnd  =  FindWindow(  NULL,  (  pQyMc->iAppType  !=  CONST_qyAppType_client  )  ?  CONST_qnmStatusWndTitle  :  CONST_qnmStatusWndTitle_client  )  )  {
		 MACRO_SetForegroundWindow(  hWnd  );
		 goto  errLabel;
	 }
 
	 if  (  pQyMc->gui.hProcessStatusTool  )  {
		 dwRet  =  ::WaitForSingleObject(  pQyMc->gui.hProcessStatusTool,  200  );
		 if  (  dwRet  !=  WAIT_TIMEOUT  &&  dwRet  !=  WAIT_FAILED  )  {
			 CloseHandle(  pQyMc->gui.hProcessStatusTool  );  pQyMc->gui.hProcessStatusTool  =  NULL;
		 }
	 }

	 memset(  &si,  0,  sizeof(  si  )  );
	 memset(  &pi,  0,  sizeof(  pi  )  );
		 
	 traceLogA(  "Now start qwm "  );
	 memset(  &si,  0,  sizeof(  STARTUPINFO  )  );
 	 si.cb  =  sizeof(  STARTUPINFO  );
 	 si.dwFlags  =  STARTF_FORCEOFFFEEDBACK;
	 
	 _sntprintf(  tmpExeName,  mycountof(  tmpExeName  ),  _T(  "%sbin\\%s"  ),  pQyMc->cfg.installDir,  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  ?  _T(  "qyStatusTool_client.exe"  )  :  _T(  "qyStatusTool_main.exe"  )  );
	 if  (  tQyQuoteFileName(  tmpExeName,  mycountof(  tmpExeName  )  )  )  goto  errLabel;
	 
	 if  (  !CreateProcess(  NULL,  CString(  tmpExeName  ).GetBuffer(  0  ),  NULL,  NULL,  0,  0,  NULL,  NULL,  &si,  &pi  )  )  goto  errLabel;
	 bProcessCreated  =  TRUE;
	 traceLogA(  "CreateProcess %s succeeded,  new processId is %d,  new threadId is %d.",  tmpExeName,  pi.dwProcessId,  pi.dwThreadId  );

	 iRet  =  0;

errLabel:

	 if  (  bProcessCreated  )  {
		 if  (  pi.hThread  )  {  CloseHandle(  pi.hThread  );  pi.hThread  =  NULL;  }
		 if  (  pi.hProcess  )  pQyMc->gui.hProcessStatusTool  =  pi.hProcess;
	 }

	 return  iRet;
}


// CDlgLeftView_db dialog

IMPLEMENT_DYNAMIC(CDlgLeftView_db, CDialogEx)

CDlgLeftView_db::CDlgLeftView_db(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLeftView_db::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

	m_var.m_pParent = pParent;
	m_var.m_nID = CDlgLeftView_db::IDD;
	m_var.iIDC_tree  =  IDC_imObjTree;
	
	this->m_TreeCtrl  =  NULL;

	memset(  &m_docStruct,  0,  sizeof(  m_docStruct  )  );
	

}

CDlgLeftView_db::~CDlgLeftView_db()
{
	int  ii = 0;
}


//
BOOL  CDlgLeftView_db::bSetQyMcDoc(  QY_MC_SEL  *  pSel  )
{
	 BOOL			bRet	=	FALSE;
 	 QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	 CDBVariant		varVal[1];
	 BAR_CFG	*	pBarCfg	=	NULL;
	 CString		tmpCStr;
	 QY_OBJ_DB	*	pObj	=	NULL;

	 switch  (  pSel->type  )  {
			 
			 case  CONST_qySelType_mcQuery:

				   if  (  !pSel->u.query.nFields  )  goto  errLabel;

				   m_docStruct.iDocType  =  CONST_qyDocType_mcQuery;
				   memcpy(  &m_docStruct.u.query,  &pSel->u.query,  sizeof(  pSel->u.query  )  );

				   //  traceLog(  _T(  "bSetQyMcDoc(  ),  sqlStr is %s %s %s %s %s %s"  ),  pSel->u.query.selectPart,  pSel->u.query.fromPart,  pSel->u.query.wherePart[0]  ?  _T(  "where"  )  :  _T(  ""  ),  pSel->u.query.wherePart,  pSel->u.query.sortPart[0]  ?  _T(  "order by"  )  :  _T(  ""  ),  pSel->u.query.sortPart  );

				   if  (  1  )  {	//  2006/08/12, 增加了一点打印信息
					   OutputDebugString(  pSel->u.query.selectPart  );
					   OutputDebugString(  _T(  " "  )  );
					   OutputDebugString(  pSel->u.query.fromPart  );
					   OutputDebugString(  _T(  " "  )  );
					   OutputDebugString(  pSel->u.query.wherePart[0]  ?  _T(  "where"  )  :  _T(  ""  )  );
					   OutputDebugString(  _T(  " "  )  );
					   OutputDebugString(  pSel->u.query.wherePart  );
					   OutputDebugString(  _T(  " "  )  );
					   OutputDebugString(  pSel->u.query.sortPart[0]  ?  _T(  "order by"  )  :  _T(  ""  )  );
					   OutputDebugString(  _T(  " "  )  );
					   OutputDebugString(  pSel->u.query.sortPart  );
					   OutputDebugString(  _T(  "\n"  )  );
				   }

				   if  (  !(  pObj  =  getProcedObjDb(  pQyMc,  0,  pSel->u.query.iDsnIndex  )  )  )  {
					   traceLogA(  "iDsnIndex error"  );  
					   goto  errLabel;
				   }
				   if  (  !pObj->ucbLoaded  )  {
					   traceLogA(  "dsn is unloaded"  );  
					   goto  errLabel;
				   }

				   try  {
					    if  (  this->m_rs.Initialize(  pObj->pDb,  CString(  pSel->u.query.selectPart  )  +  CString(  " "  )   +  CString(  pSel->u.query.fromPart  ),  pSel->u.query.wherePart,  pSel->u.query.sortPart,  pSel->u.query.nSqlFields,  pSel->u.query.sqlColumns  )  )  goto  errLabel;
					    m_rs.SetFilter(  pSel->u.query.wherePart  );
					   }
				   catch  (  CException  *  e  )  {
						  e->Delete(  );
		   				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CQyMcDoc::bSetQyMcDoc failed."  )  );
						  goto  errLabel;
				   }
					   
				   lstrcpyn(  m_docStruct.dsnName,  pObj->cfg.sysName,  mycountof(  m_docStruct.dsnName  )  );

				   if  (  pSel->u.query.type  ==  CONST_qyQueryType_general  )  lstrcpyn(  m_docStruct.postDocName,  _T(  "query"  ),  sizeof(  m_docStruct.postDocName  )  /  sizeof(  TCHAR  )  );				   						
				   else  if  (  pSel->u.query.type  ==  CONST_qyQueryType_mcCfgUrlList  )  lstrcpyn(  m_docStruct.postDocName,  _T(  "url cfg"  ),  sizeof(  m_docStruct.postDocName  )  /  sizeof(  TCHAR  )  );					   		 
				   else  {
					     lstrcpyn(  m_docStruct.preDocName,  pSel->u.query.preDocName,  sizeof(  m_docStruct.preDocName  )  /  sizeof(  TCHAR  )  );	
						 lstrcpyn(  m_docStruct.docName,  pSel->u.query.docName,  sizeof(  m_docStruct.docName  )  /  sizeof(  TCHAR  )  );
						 lstrcpyn(  m_docStruct.postDocName,  pSel->u.query.postDocName,  sizeof(  m_docStruct.postDocName  )  /  sizeof(  TCHAR  )  );
				   }
				   this->qySetTitle(  CString(  pSel->u.query.docName  )  );
				   
				   break;

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

void  CDlgLeftView_db::qySetTitle(  LPCTSTR  name  )
{
}


BOOL CDlgLeftView_db::Create(const RECT& rect)
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


 BOOL  CDlgLeftView_db::bQuitDlg(  )		
{
	BOOL		bRet	=	FALSE;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs   ) return  -1;

#if 0
	HWND  hMainWnd  =  m_hWnd;
	
	if  (  !pQyMc->bGuiQuit  )  {	
		pFuncs->mainWnd.pf_mainWnd_OnQyQuitMainWnd(  hMainWnd,  &m_var  );	
		return  FALSE;		
	}

	if  (  pFuncs->mainWnd.pf_mainWnd_OnClose(  hMainWnd,  &m_var  )  )  return  FALSE;
#endif

	//
	BOOL  bGuiWnd  =  FALSE;
	//
	if  (  bUse_imObjView_as_guiWnd(  )  )  {
		if  (  pQyMc->gui.hGuiWnd  ==  m_hWnd  )  {
			bGuiWnd  =  TRUE;
		}
	}

	//
	::DestroyWindow(  m_hWnd  );


	//
	if  (  bGuiWnd  )  {
		::PostMessage(  pQyMc->gui.hMainWnd,  WM_COMMAND,  MAKEWPARAM(  ID_qyQuitMainWnd,  0  ),  0  );
	}


	//
	bRet  =  TRUE;	
errLabel:
	return  bRet;
}


 #ifdef  __DEBUG__
 void  CDlgLeftView_db::showItem(  HTREEITEM  htItem  )
{
	 CString	str;
	 DWORD		dwData;

	 if  (  htItem  )  {
		 
		 str  =  m_TreeCtrl->GetItemText(  htItem  );
		 dwData  =  m_TreeCtrl->GetItemData(  htItem  );

		 traceLogA(  "该节点 %s, 数据 %d",  str.GetBuffer(  0  ),  dwData  );
	 }
}
#endif



 //
  int CDlgLeftView_db::bInitialDisplay( )
{
	 BOOL				bRet				=				FALSE;
 	 QY_MC		*		pQyMc				=				QY_GET_GBUF( );
	 //  unsigned  int		len;
	 //  CQyMcDoc	*		pDoc				=				GetDocument(  );


	 //
	 //
	 TCHAR  *  wndName  =  m_docStruct.docName;
	 wndName  =  _T(  "DlgLeftView_db"  );
	 if  (  initMcCtxDisplayedWnd(  pQyMc,  this->m_hWnd,  wndName,  &m_var.displayCtx  )  )  goto  errLabel;
	 m_var.bDisplayCtxInited  =  TRUE;

	 //  2014/04/14
#define	CONST_tblSize_imObjTree		10000
#define  MAX_tbl_total_imObjTree	CONST_tblSize_imObjTree  *  3			
#ifdef  __DEBUG__
		//#define  MAX_tbl_total_imObjTree	10			
#endif
	 m_var.pHashTbl_tree  =  newHashTbl(  CONST_tblSize_imObjTree,  MAX_tbl_total_imObjTree,  imObj_hash,  imObj_hash_bSame,  imObj_hash_copy,  imObj_hash_free  );
	 if  (  !m_var.pHashTbl_tree  )  goto  errLabel;


	 //
	 m_TreeCtrl  =  (  CTreeCtrl  *  )GetDlgItem(  m_var.iIDC_tree  );	//  &GetTreeCtrl(  );

	 // Create the image list for the tree control
	 //  m_ImageList.Create(  IDB_qnmIcons,  16,  1,  RGB(  0,  255,  0  )  );
	 m_ImageList.Create(  IDB_qnmIcons,  16,  1,  0  );		//  2003/10/21修改
	 m_TreeCtrl->SetImageList(  &m_ImageList,  TVSIL_NORMAL  );

	 this->m_var.htMyRootItem  =  m_TreeCtrl->InsertItem(  CString(  pQyMc->cfg.name  )  );
	 m_TreeCtrl->SetItemState(  this->m_var.htMyRootItem,  TVIS_BOLD,  TVIS_BOLD  );
	 this->m_var.bInitialized  =  TRUE;

	 bRet  =  TRUE;
errLabel:
	 if  (  !bRet  )  {
		 //
		 if  (  m_var.bDisplayCtxInited  )  {
			 exitMcCtxDisplayedWnd(  pQyMc,  this->m_hWnd,  &m_var.displayCtx  );  m_var.bDisplayCtxInited  =  FALSE;
		 }
	 }

	 return  bRet;

}


   BOOL  CDlgLeftView_db::bDisplayContent(  )
{
	 BOOL					bRet				=				FALSE;
	 QY_MC				*	pQyMc				=				QY_GET_GBUF(  );
	 //  CQyMcDoc			*	pDoc				=				GetDocument(  );
	 if  (  m_docStruct.iDocType  !=  CONST_qyDocType_mcRootTree  )  return  FALSE;

	 //  2004/07/26增加了对显示的重定义
	 if  (  m_docStruct.u.treeList.tree.pfDisplayContent  )  return  (  m_docStruct.u.treeList.tree.pfDisplayContent(  this,  0,  0  )  ?  FALSE  :  TRUE  );



	 bRet				=				TRUE;

errLabel:

	//  if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	return  bRet;		

}


 BOOL  CDlgLeftView_db::bRefreshItem(  HTREEITEM  htItem  )
{
	 BOOL					bRet				=	FALSE;
	 QY_MC				*	pQyMc				=	QY_GET_GBUF(  );
	 //  CQyMcDoc			*	pDoc				=				GetDocument(  );
	 if  (  m_docStruct.iDocType  !=  CONST_qyDocType_mcRootTree  )  return  FALSE;

	 //  2013/11/01
#if  0
	 if  (  pQyMc->cfg.db.iDbType  ==  CONST_dbType_myDb  )  {
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "dlgLeftView_db::bRefreshItem:not supported with myDb"  )  );
		 #endif
		 return  FALSE;
	 }
#endif

	 //
	 QY_OBJ_DB			*	pObjDb				=				getProcedObjDb(  pQyMc,  0,  m_docStruct.u.treeList.tree.iDsnIndex  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	 //
	 int					iObjId;
	 //QY_SWITCHPORT_RCD		switchPort;
	 QY_OBJINDEX_RCD		objIndex;
	 //CRecordset				rs( ( CDatabase * )pObjDb->pDb );
	 //CDBVariant				varVals[10];
	 //int					index,  nFields;
	 //TCHAR					sqlBuf[1024];
	 //int					nImage,  nSelectedImage;
	 //HTREEITEM				tmphtItem			=				NULL;
	 //TCHAR					displayName[512]	=				_T(  ""  );		
	 //TCHAR				*	pStopString;
	 TCHAR					tBuf[256];

	 QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	 traceLogA(  "CLeftView::bRefreshItem enters"  );

	 //  2004/07/26
	 if  (  m_docStruct.u.treeList.tree.pfRefreshItem  )  return  (  m_docStruct.u.treeList.tree.pfRefreshItem(  this,  htItem,  0  )  ?  FALSE  :  TRUE  );

	 
	 if  (  htItem  ==  m_var.htMyRootItem  )  goto  errLabel;

	 iObjId  =  m_TreeCtrl->GetItemData(  htItem  );
	 if  (  g_dbFuncs.pf_getObjIndex(  pObjDb,  iObjId,  &objIndex  )  )  goto  errLabel;
	 
	 
	 bRet  =  TRUE;

errLabel:
	 return  bRet;
}


// GetLastItem  - Gets last item in the branch
// Returns      - Last item
// hItem        - Node identifying the branch. NULL will 
//                return the last item in outine

HTREEITEM CDlgLeftView_db::GetLastItem( HTREEITEM hItem )
{
        // Last child of the last child of the last child ...
        HTREEITEM htiNext;

        if( hItem == NULL ){
                // Get the last item at the top level
                htiNext = m_TreeCtrl->GetRootItem();
                while( htiNext ){
                        hItem = htiNext;
                        htiNext = m_TreeCtrl->GetNextSiblingItem( htiNext );
                }
        }

        while( m_TreeCtrl->ItemHasChildren( hItem ) ){
                htiNext = m_TreeCtrl->GetChildItem( hItem );
                while( htiNext ){
                        hItem = htiNext;
                        htiNext = m_TreeCtrl->GetNextSiblingItem( htiNext );
                }
        }

        return hItem;
}



// GetNextItem  - Get next item as if outline was completely expanded
// Returns      - The item immediately below the reference item
// hItem        - The reference item
HTREEITEM CDlgLeftView_db::GetNextItem( HTREEITEM hItem )
{
        HTREEITEM       hti;

        if( m_TreeCtrl->ItemHasChildren( hItem ) )
                return m_TreeCtrl->GetChildItem( hItem );           // return first child
        else{
                // return next sibling item
                // Go up the tree to find a parent's sibling if needed.
                while( (hti = m_TreeCtrl->GetNextSiblingItem( hItem )) == NULL ){
                        if( (hItem = m_TreeCtrl->GetParentItem( hItem ) ) == NULL )
                                return NULL;
                }
        }
        return hti;
}

// GetNextItem  - Get previous item as if outline was completely expanded
// Returns              - The item immediately above the reference item
// hItem                - The reference item
HTREEITEM CDlgLeftView_db::GetPrevItem( HTREEITEM hItem )
{
        HTREEITEM       hti;

        hti = m_TreeCtrl->GetPrevSiblingItem(hItem);
        if( hti == NULL )
                hti = m_TreeCtrl->GetParentItem(hItem);
        else
                hti = GetLastItem(hti);
        return hti;
}


// FindItem			- Finds an item that contains the search string
// Returns			- Handle to the item or NULL
// str				- String to search for
// bCaseSensitive	- Should the search be case sensitive
// bDownDir			- Search direction - TRUE for down
// bWholeWord		- True if search should match whole words
// hItem			- Item to start searching from. NULL for
//					- currently selected item
 HTREEITEM  CDlgLeftView_db::FindItem(  CString	&	str, 
								  BOOL			bCaseSensitive  /*=  FALSE  */, 
								  BOOL			bDownDir		/*=  TRUE   */, 
								  BOOL			bWholeWord		/*=  FALSE  */, 
								  HTREEITEM		hItem			/*=	 NULL	*/  )
{
	int lenSearchStr = str.GetLength();
	if( lenSearchStr == 0 ) return NULL;

	HTREEITEM htiSel = hItem ? hItem : m_TreeCtrl->GetSelectedItem();
	HTREEITEM htiCur = bDownDir ?GetNextItem( htiSel ) : GetPrevItem( htiSel );
	CString sSearch = str;

	if( htiCur == NULL )
	{
		if( bDownDir )  htiCur = m_TreeCtrl->GetRootItem();
		else htiCur = GetLastItem( NULL );
	}

	if( !bCaseSensitive )
		sSearch.MakeLower();

	while( htiCur && htiCur != htiSel )
	{
		CString sItemText = m_TreeCtrl->GetItemText( htiCur );
		if( !bCaseSensitive )
			sItemText.MakeLower();

		int n;
		while( (n = sItemText.Find( sSearch )) != -1 )
		{
			// Search string found
			if( bWholeWord )
			{
				// Check preceding char
				if( n != 0 )
				{
					if( isalpha(sItemText[n-1]) || 
					    	sItemText[n-1] == '_' ){
						// Not whole word
						sItemText = sItemText.Right(
							sItemText.GetLength() - n - 
							lenSearchStr );
						continue;
					}
				}

				// Check succeeding char
				if( sItemText.GetLength() > n + lenSearchStr
					&& ( isalpha(sItemText[n+lenSearchStr]) ||
					sItemText[n+lenSearchStr] == '_' ) )
				{
					// Not whole word
					sItemText = sItemText.Right( sItemText.GetLength() 
							- n - sSearch.GetLength() );
					continue;
				}
			}
			
			if( IsFindValid( htiCur ) )
				return htiCur;
			else break;
		}


		htiCur = bDownDir ? GetNextItem( htiCur ) : GetPrevItem( htiCur );
		if( htiCur == NULL )
		{
			if( bDownDir )  htiCur = m_TreeCtrl->GetRootItem();
			else htiCur = GetLastItem( NULL );
		}
	}
	return NULL;
}

// IsFindValid	- Virtual function used by FindItem to allow this
//		  function to filter the result of FindItem
// Returns	- True if item matches the criteria
// Arg		- Handle of the item
 BOOL CDlgLeftView_db::IsFindValid( HTREEITEM )
{
	return TRUE;
}

 // 执行此函数须通过SetItemData( )设置数据，条目掩码中须包括TVIF_PARAM.
 // 注：未测试，摘自《Visual C++ 图形用户界面开发指南》P277.
 HTREEITEM CDlgLeftView_db::FindItemData( DWORD lParam, BOOL bDownDir, HTREEITEM hItem )
{
	 HTREEITEM htiSel = hItem ? hItem : m_TreeCtrl->GetSelectedItem( );
	 HTREEITEM htiCur = bDownDir ? GetNextItem( htiSel ) : GetPrevItem( htiSel );
	 if ( htiCur == NULL ) {
		 if ( bDownDir ) 
			 htiCur = m_TreeCtrl->GetRootItem( );
		 else
			 htiCur = GetLastItem( NULL );
	 }
	 while ( htiCur && htiCur != htiSel ) {

		 DWORD sItemData = m_TreeCtrl->GetItemData( htiCur );
		 
		 if ( sItemData == lParam )
			 return htiCur;
		 htiCur = bDownDir ? GetNextItem( htiCur ) : GetPrevItem( htiCur );
		 if ( htiCur == NULL ) {
			 if ( bDownDir )
				 htiCur = m_TreeCtrl->GetRootItem( );
			 else
				 htiCur = GetLastItem( NULL );
		 }
	 }
	 return NULL;
}


 
 // 此函数在调用前确保有子节点。
 BOOL CDlgLeftView_db::bGetNodePath( HTREEITEM h, char *path, unsigned int size )
{
	 BOOL					bRet			=		FALSE;
	 CTreeCtrl		&		treeCtrl		=		*this->m_TreeCtrl;	//  GetTreeCtrl( );
	 HTREEITEM				tmph;
	 CString				tmpCStr, tmpCStr1;

	 if ( !path ) goto errLabel;
	 if ( !h ) goto errLabel;
	 if ( size <= QIM_FULLNAMELEN ) goto errLabel;

	 tmph			=		treeCtrl.GetParentItem( h );
	 if ( !tmph ) {
		 if ( !( *path ) ) strcpy( path, "" );
		 bRet = TRUE;
		 goto errLabel;
	 }

	 tmpCStr1		=		treeCtrl.GetItemText( tmph );
	 if ( !( *path ) )
	 	 sprintf( path, "%s", tmpCStr1 );
	 else {
		 tmpCStr	=		tmpCStr1 + CString(  "/"  ) + CString( path ) ;
		 sprintf( path, "%s", tmpCStr );
	 }

	 if ( !bGetNodePath( tmph, path, size ) ) goto errLabel;

	 bRet = TRUE;

errLabel:

	 return bRet;

}


 



 
BOOL  CDlgLeftView_db::bRootTreeGetSel(  CTreeCtrl &	treeCtrl,  HTREEITEM  hRoot,  HTREEITEM  hCur,  QY_MC_SEL  *  pCurSel  )
{
	 BOOL						bRet			=	FALSE;
	 QY_MCROOTTREE_SEL		*	pRootTreeSel	=	NULL;
	 
	 memset(	pCurSel,  0,  sizeof(  pCurSel[0]  )  );

	 pCurSel->type		=			QY_SELTYPE_MCROOTTREE;
	 pRootTreeSel		=		&	pCurSel->u.rootTree;
		
	if ( hCur == hRoot ) {	
		pRootTreeSel->bRoot					=					TRUE;	
		}
	else  {
		pRootTreeSel->iHelpId					=					treeCtrl.GetItemData(  hCur  );
		
	}
	 bRet		=		TRUE;
//  errLabel:
	 return		bRet;
}






//
void CDlgLeftView_db::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgLeftView_db, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_COMMAND(ID_HELP, OnHelp)
	
	ON_MESSAGE(  WM_HOTKEY, OnQyHotKey )
	ON_MESSAGE(  QY_WM_COMM, OnQyComm)
	ON_MESSAGE(  CONST_qyWm_postComm,  OnQyPostComm  )
	ON_MESSAGE(  CONST_qyWm_trayNotify,  OnQyTrayNotify  )
	ON_MESSAGE(  CONST_qyWm_graphNotify_mediaFile,  OnQyGraphNotify_mediaFile  )
	ON_MESSAGE(  CONST_qyWm_graphNotify_mediaDevice,  OnQyGraphNotify_mediaDevice  )

	ON_COMMAND_RANGE(  ID_MENU_isCmd_min,  ID_MENU_isCmd_max,  OnIsCmd  )
	ON_UPDATE_COMMAND_UI_RANGE(  ID_MENU_isCmd_min,  ID_MENU_isCmd_max,  OnUpdateIsCmd  )	
	
	ON_NOTIFY(TVN_SELCHANGED, IDC_imObjTree, &CDlgLeftView_db::OnTvnSelchangedimobjtree)
	ON_NOTIFY(NM_RCLICK, IDC_imObjTree, &CDlgLeftView_db::OnNMRClickimobjtree)
	ON_NOTIFY(NM_DBLCLK, IDC_imObjTree, &CDlgLeftView_db::OnNMDblclkimobjtree)

	ON_WM_SIZE()
	ON_WM_INITMENUPOPUP()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON_fileTransfer, &CDlgLeftView_db::OnBnClickedButtonfiletransfer)
	ON_WM_LBUTTONUP()
	ON_WM_NCACTIVATE()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCPAINT()
END_MESSAGE_MAP()


//
 int  getMenuStatus_frame(  QY_MC  *  pQyMc,  void  *  p0,  void  *  p1,  void  *  piStatusParam  );


//
int  getMenuStatus_imObjView_cli(  QY_MC  *  pQyMc,  void  *  p0,  void  *  p1,  void  *  piStatusParam  )
{
	 int						iErr		=	-1;
	 //  p0;
	 int						iMenuId		=	(  int  )p1;
	 int				*		piStatus	=	(  int  *  )piStatusParam;
	 
	 if  (  !pQyMc  )  return  -1;
	 if  (  !piStatus  )  return  -1;

	 return  getMenuStatus_frame(  pQyMc,  p0,  p1,  piStatusParam  );


	 iErr  =  0;
errLabel:
	 return  iErr;
 }

 




// CDlgLeftView_db message handlers


BOOL CDlgLeftView_db::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here BOOL CqyMc_dlg::OnInitDialog()


	// Add "About..." menu item to system menu.

#if  0
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
#endif
#ifdef  __USE_skin__
	HINSTANCE  hInst  =  get_my_hInst(  );
	HICON  hIcon  =  LoadIcon(  hInst,  MAKEINTRESOURCE(  IDI_SMALL  )  );
	SetClassLongPtr(  m_hWnd,  GCLP_HICON,  (  LONG  )hIcon  );
#endif

	// TODO: Add extra initialization here
	//
	//  set_m_pMainWnd(  this  );

	// TODO: Add extra initialization here
	int  iErr  =  -1;
	QY_MC		*	pQyMc	=  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs   ) return  -1;

	//
	QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  &pQyMc->cusRes  );
	 if  (  !pResMem  )  goto  errLabel;

	 //	
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	//
	memset(  &m_skinProc,  0,  sizeof(  m_skinProc  )  );

	//
	RECT	rc;


#ifdef  __DEBUG__

#endif



		//
		HMENU				hMenu	=	::GetMenu(  m_hWnd  );
		if  (  !hMenu  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "dlgTalk_OnInitDialog failed, hMenu is null"  )  );
			#endif
			goto  errLabel;
		}


		QY_DMITEM		*	pItem;
		
		//
		if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  CONST_resId_mainMenu  )  )  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "dlgTalk_OnInitDialog failed, pItem CONST_resId_popupMenu is null"  )  );
			#endif
			goto  errLabel;
		}
		if  (	 makeDynaMenu(  &pQyMc->cusRes,  hMenu,  (  QY_DMITEM  *  )pItem,  getMenuStatus_imObjView_cli,  pQyMc,  0  )  )  goto  errLabel;

		//		
		//  2017/06/21	 
		if  (  qyGetSubSystemId_isCli(  pQyMc  )  ==  CONST_subSystemId_basic  )  {
					
			//		 
			TCHAR  tBuf[128];
			HMENU  hMainMenu  =  hMenu;
		 
			//		 
			HMENU  hSubMenu  =  GetSubMenu(  hMainMenu,  0  );		 
			if  (  hSubMenu  )  {
			 
				DeleteMenu(  hSubMenu,  4,  MF_BYPOSITION  );	//  2D wall
				//
				DeleteMenu(  hSubMenu,  11,  MF_BYPOSITION  );	//  共享
				//
				DeleteMenu(  hSubMenu,  11,  MF_BYPOSITION  );	//  ---
				

		 
			}
		 
			//
		 
			//RemoveMenu(  hMainMenu,  8,  MF_BYPOSITION  );

	 
		}



	//  2013/08/23. 让窗口重新调整下菜单大小
	//  GetWindowRect(  &rc  );
	//  MoveWindow(  rc.left,  rc.top,  rc.right  -  rc.left  +  1,  rc.bottom  -  rc.top  );

	//  2017/01/11
	{		//  2007/03/03 
		int		iCxScreen	=  0;
		int		iCyScreen	=	0;
		int		iX			=	0;
		int		iY			=	0;
		int		iWidth		=	250;	//  180;
		int		iHeight		=	500;
		
#if  0	//  def  __APP_qyMc_touchscreen__
		//  iWidth  =  210;		
		iWidth  =  280;
#endif

		iCxScreen  =  GetSystemMetrics(  SM_CXSCREEN  );		//  2005/08/19
		iCyScreen  =  GetSystemMetrics(  SM_CYSCREEN  );		//  2005/08/19
		if  (  !iCxScreen  ||  !iCyScreen  )  goto  errLabel;

		//
		if  (  bUse_imObjView_as_guiWnd(  )  )  {
			iX  =  iCxScreen  -  iWidth  -  60;
			iY	=  (  iCyScreen  -  iHeight  )  /2  -  40;  
			}
		else  {
			iWidth  =  iCxScreen  /  2;
			iHeight  =  iCyScreen  /  2;
			//
			iX  =  (  iCxScreen  -  iWidth  )  /  2;
			iY  =  (  iCyScreen  -  iHeight  )  /  2;
		}
		
		//
#ifdef  __DEBUG__
		if (pQyMc->appParams.bMcu) {
			iX -= 300;
		}
#endif

		//
		::MoveWindow(  m_hWnd,  iX,  iY,  iWidth,  iHeight,  0  );
	}

	
	//  2011/03/23
	MIS_CNT	*	pMisCnt	=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	TCHAR		tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u, %s. ( Menu )"  ),  pMisCnt->idInfo.ui64Id,  pMisCnt->talkerDesc  );
	//::SetDlgItemText(  m_hWnd,  p->iIDC_BUTTON_bar,  tBuf  );
	//
	if  (  bSupported_devAuth(  )  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMisCnt->idInfo.ui64Id  );
		if  (  pMisCnt->talkerDesc[0]  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %s"  ),  tBuf,  pMisCnt->talkerDesc  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  pQyMc->cfg.qyMcTitle  );
		}
	else  {
		  safeWcsnCpy(  pQyMc->cfg.qyMcTitle,  tBuf,  mycountof(  tBuf  )  );
	}
#if  0
	if  (  qyGetAppAvLevel_qyMc(  pQyMc  )  !=  pQyMc->usAppAvLevel_default  /*qyGetAppAvLevel_default(  )*/  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( %s  )"  ),  tBuf,  getTableResStr(  0,  CONST_qyAppAvLevelTable_en,  &pQyMc->cusRes,  qyGetAppAvLevel_qyMc(  pQyMc  )  )  );
	}
#endif
	if  (  tBuf[0]  )  {
		::SetWindowText(  m_hWnd,  tBuf  );
	}

	//
	::SetForegroundWindow(  this->m_hWnd  );

	//		
	// TODO:  Add extra initialization here
	//  this->m_brush_fullScreen_dlg.CreateSolidBrush(  CONST_bkColor_fullScreen_walls  );

	//
	//p->bInited  =  TRUE;

	//
	if  (  !this->bInitialDisplay(  )  )  {
		goto  errLabel;
	}	

	//
	this->bDisplayContent(  );

	//
	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().

	m_TreeCtrl->Expand(  this->m_var.htMyRootItem,  TVE_EXPAND  );

	if  (  m_var.htInitialItem  &&  m_var.htInitialItem  !=  m_var.htMyRootItem  )  {
		m_TreeCtrl->SetItemState(  m_var.htInitialItem,  TVIS_SELECTED,  TVIS_SELECTED  );
		m_TreeCtrl->SetItemText(  m_var.htMyRootItem,  CString(  "Related"  )  );
	}  
	
	QY_MC_SEL		curSel;

	memset( &curSel, 0, sizeof( curSel ) );
	curSel.type  =  QY_SELTYPE_MCROOTTREE;
	curSel.u.rootTree.type  =  m_docStruct.u.treeList.tree.type;
	curSel.u.rootTree.iDsnIndex  =  m_docStruct.u.treeList.tree.iDsnIndex;	//  2007/01/02
	
	if  (  !m_var.htInitialItem  )  curSel.u.rootTree.bRoot  =  TRUE;	
	else  {
		  curSel.u.rootTree.iHelpId  =  m_TreeCtrl->GetItemData(  m_var.htInitialItem  );
		  _snprintf(  curSel.u.rootTree.selectedMac,  sizeof(  curSel.u.rootTree.selectedMac  ),  "%s",  m_docStruct.u.treeList.tree.selectedMac  );
	}
	if  (  m_docStruct.u.treeList.tree.pfProcTreeSel  )  m_docStruct.u.treeList.tree.pfProcTreeSel(  pQyMc,  &curSel,  0  );

	//  2017/06/09
	if  (  pProcInfo->cfg.policy.ucbDlgShareDynBmps_autopopupandhideOnStartup  )  {
		PostMessage(  WM_COMMAND,  MAKEWPARAM(  ID_shareDynBmps,  0  ),  0  );
	}

	//
	SetDlgItemText(  IDC_BUTTON_fileTransfer,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_file  )  );  //_T(  "File"  )  );

	//
#if  0
	if  (  pQyMc->appParams.bConfServer  )  {
		//
		if  (  GuiShare.pf_doPre_createConsoleWall  )  GuiShare.pf_doPre_createConsoleWall(  NULL,  NULL,  NULL  );
		//
		dyn_createConsoleWall(  pQyMc->pGBuf_d3d  );

		//
		pProcInfo->status.confServerStatus.bDone_createConsoleWall = true;

	}
#endif


	//
	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		::PostMessage(  m_hWnd,  WM_CLOSE,  0,  0  );
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}





void CDlgLeftView_db::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//  CDialogEx::OnCancel();
}

void CDlgLeftView_db::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//  CDialogEx::OnClose();
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs   ) return;

	//if  (  pFuncs->mainWnd.pf_mainWnd_OnClose(  this->m_hWnd,  &m_var  )  )  return;

	//  2017/01/05
	if  (  bUse_imObjView_as_guiWnd(  )  )  {
		if  (  !pQyMc->bGuiQuit  )  {					  					  			
			::SendMessage(  m_hWnd,  WM_SYSCOMMAND,  SC_MINIMIZE,  0  );						  
			return;						  
		}					
	}						  
		

	//
	bQuitDlg(  );

}

void CDlgLeftView_db::OnDestroy()
{
	QY_MC			*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs   ) return;

	debugLog(  "CMainFrame::OnDestroy(  ) enters."  );

	//
	if  (  m_var.bDisplayCtxInited  )  {
		exitMcCtxDisplayedWnd(  pQyMc,  this->m_hWnd,  &m_var.displayCtx  );  m_var.bDisplayCtxInited  =  FALSE;
	}

	//  2014/04/14
	if  (  m_var.pHashTbl_tree  )  {
		freeHashTbl(  (  void  **  )&m_var.pHashTbl_tree  );
	}

	//
	{
		G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )pFuncs->pf_get_g_guiData(  );
		if  (  pGuiData->hFont_list  )  {
			DeleteObject(  pGuiData->hFont_list  );  pGuiData->hFont_list  =  NULL;
		}
#if  0
		if  (  pGuiData->hFont_list_text  )  {
			DeleteObject(  pGuiData->hFont_list_text  );  pGuiData->hFont_list_text  =  NULL;
		}
#endif
		//  2017/10/01
		if  (  pGuiData->hFont_list_dlgTalk_peerInfo  )  {
			DeleteObject(  pGuiData->hFont_list_dlgTalk_peerInfo  );  pGuiData->hFont_list_dlgTalk_peerInfo  =  NULL;
		}
		//
		if  (  pGuiData->hFont_static  )  {
			DeleteObject(  pGuiData->hFont_static  );  pGuiData->hFont_static  =  NULL;
		}
		if  (  pGuiData->hFont_btn  )  {
			DeleteObject(  pGuiData->hFont_btn  );  pGuiData->hFont_btn  =  NULL;
		}
		if  (  pGuiData->hFont_bar  )  {
			DeleteObject(  pGuiData->hFont_bar  );  pGuiData->hFont_bar  =  NULL;
		}
		if  (  pGuiData->hFont_menu  )  {
			DeleteObject(  pGuiData->hFont_menu  );  pGuiData->hFont_menu  =  NULL;
		}
	}

	//pFuncs->mainWnd.pf_exitVar_onDestroy_mainFrame(  0,  this->m_hWnd,  &this->m_var  );

	traceLogA(  "CMainFrame::OnDestroy(  ): "  );

	//
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	debugLog(  "CMainFrame::OnDestroy(  ) leaves."  );

}


void CDlgLeftView_db::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs   ) return;
		
	if  (  pFuncs->mainWnd.pf_mainWnd_OnTimer(  this->m_hWnd,  &m_var,  nIDEvent  )  )  return;

	//
#if  0
	if  (  !m_var.wall.guiData.ucbHideBar  )  {
		if  (  m_var.wall.m_bFullScreen  )  
		{
			if  (  GetTickCount(  )  -  m_var.wall.dwTickCnt_lastMouseMove  >  10000  )  {
				traceLog(  _T(  "OnTimer: before hideBar"  )  );
				m_var.wall.guiData.ucbHideBar  =  TRUE;
				m_var.wall.dwTickCnt_hide_bar  =  GetTickCount(  );

				int  iWndContentType  =  0;	//  this->getWndContentType(  );
				iWndContentType  =  m_var.iWndContentType;

				sizeAllControls_dlgWalls(  this->m_hWnd,  iWndContentType,  &m_var.wall  );

				traceLog(  _T(  "OnTimer: after hideBar"  )  );
			}
		}
	}
#endif

	//
	MIS_CNT* pMisCnt = getMisCntByName(pProcInfo, _T(""));

	//
	if  (  bSupported_devAuth(  )  )  {
		if  (  !pMisCnt->retrieveImObjList.ulbContactExists
			&&  !pMisCnt->retrieveImObjList.ulbImGrpExists
			&&  !pProcInfo->customerService.objs[0].idInfo.ui64Id  )
		{
			if  (  pMisCnt->retrieveCustomerServiceObjList.dwLastTickCnt  
				&&  GetTickCount(  )  -  pMisCnt->retrieveCustomerServiceObjList.dwLastTickCnt  >  10000    )  
			{
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "no imGrp, no contact, no customer serivce, quit now"  )  );
				::PostMessage(  m_hWnd,  WM_COMMAND,  MAKEWPARAM(  ID_qyQuitMainWnd,  0  ),  0  );			
			}			
		}
	}
	//  2014/05/27
	// __declspec(  dllexport  )  int  hashTbl_getInfo(  LP_hashTbl  H,  int  *  piCnt  )
	hashTbl_getInfo(  m_var.pHashTbl_tree,  &pProcInfo->status.hashTbl_leftView_db.maxiTotal,  &pProcInfo->status.hashTbl_leftView_db.nTotal  );


		//
#ifdef  __DEBUG__
		testSndRtspMsg(  );		
#endif

	

	//  CDialogEx::OnTimer(nIDEvent);
}


 LRESULT CDlgLeftView_db::OnQyHotKey(  WPARAM  wParam,  LPARAM  lParam  )
 {
	 LONG	lRet			=		-1;
	 int	idHotKey		=		(  int  )wParam;				// identifier of hot key 
	 UINT	fuModifiers		=		(  UINT  )LOWORD(  lParam  );	// key-modifier flags 
	 UINT	uVirtKey		=		(  UINT  )HIWORD(  lParam  );   // virtual-key code 

#if  0
	 switch  (  idHotKey  )  {
			 case  ID_HKF5:
				   qyMcRefreshAll(  );
				   //  bGuestRegister(  );
				   break;
			 // case  ID_HKF6:
			 //	   bGuestUnregister(  );
			 //	   break;
			 // case  ID_HKF7:
			 //	   bGuestWalker(  );
			 //	   break;
			 default:
				     break;
	 }
#endif
	 

	 lRet  =  0;

	 return  lRet;

 }


  int  tmpHandler_bRefreshContactsStatus_leftView(  void  *  pElemParam,  void  *  pMemParam,  void  *  pLeftViewParam  )
{
	 int								iErr							=	-1;
	 DISPLAYEDELEM_U				*	pElem							=	(  DISPLAYEDELEM_U  *  )pElemParam;
	 REFRESH_RECENTFRIEND_RESP_h		*	pMem							=	(  REFRESH_RECENTFRIEND_RESP_h  *  )pMemParam;
	 CDlgLeftView_db				*	pLeftView						=	(  CDlgLeftView_db  *  )pLeftViewParam;
	 //
	 QY_MC							*	pQyMc							=	QY_GET_GBUF(  );
	 //
	 TCHAR								tBuf[256]						=	_T(  ""  );
	 TCHAR								displayName[256  +  1]			=	_T(  ""  );	
	 int								nImage,  nSelectedImage;
	 //
	 HANDLE								hTreeItem						=	NULL;;

	 switch  (  pElem->uiType  )  {
			 case  CONST_displayedElemType_messengerTree:
				   hTreeItem  =  (  HTREEITEM  )pElem->messengerTree.hItem;
				   break;
			 case  CONST_displayedElemType_meTree:
				   hTreeItem  =  (  HTREEITEM  )pElem->meTree.hItem;
				   break;
			 default:	
					goto  errLabel;
	 }


	 //  只刷新展开节点
	 TVITEM								tvItem;
			 
	 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
	 tvItem.hItem  =  (  HTREEITEM  )hTreeItem;
	 tvItem.pszText  =  tBuf;
	 tvItem.cchTextMax  =  mycountof(  tBuf  );
	 if  (  !pLeftView->m_TreeCtrl->GetItem(  &tvItem  )  )  {
		 traceLogA(  "bRefreshFriendsStatus_leftView: GetItem failed, 可能是此节点已经被删除了"  );
		 iErr  =  0;  goto  errLabel;				  
	 }

	 switch  (  pElem->uiType  )  {
			 case  CONST_displayedElemType_meTree:  {
				    MIS_CNT						*	pMisCnt					=	(  MIS_CNT  *  )pElem->meTree.pMisCnt;

					_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s(%I64u)"  ),  pMisCnt->displayName,  pMisCnt->idInfo.ui64Id  );
					if  (  pMisCnt->taskStat.uiCnt_unprocedTasks  )  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s - %s %d"  ),  displayName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_unfinished  ),  pMisCnt->taskStat.uiCnt_unprocedTasks  );
					if  (  pMisCnt->taskStat.uiCnt_processingTasks  )  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s - %s %d"  ),  displayName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_beingProcessed  ),  pMisCnt->taskStat.uiCnt_processingTasks  );
					if  (  pMisCnt->taskStat.uiCnt_processBreakTasks  )  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s - %s %d"  ),  displayName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_interrupted  ),  pMisCnt->taskStat.uiCnt_processBreakTasks  );
					//
					getMessengerImages(  pQyMc,  pMisCnt->status.usRunningStatus,  &nImage,  &nSelectedImage  );
					}
					break;
			 case  CONST_displayedElemType_messengerTree:
			 default:
				     lstrcpyn(  displayName,  tBuf,  mycountof(  tBuf  )  );  //  这里故意让displayName指向tBuf, 是因为这里暂时只需要变化图标
					 //
					 getMessengerImages(  pQyMc,  pMem->usRunningStatus,  &nImage,  &nSelectedImage  );
					 //
				     break;					
	 }
	
				
	 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  displayName  );
		 tvItem.iImage  =  nImage;
		 tvItem.iSelectedImage  =  nSelectedImage;
		 pLeftView->m_TreeCtrl->SetItem(  &tvItem  );
	 }

	 iErr  =  0;

errLabel:
	 return  iErr;
 }


 LRESULT CDlgLeftView_db::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	LONG				lRet			=	-1;
	QY_WMBUF_COMM	*	pComm			=	(  QY_WMBUF_COMM  *  )lParam;
	char				buf[1024]		=	"";

	switch  (  pComm->uiType  )  {			  
			case  CONST_qyWmParam_show:  
				  break;

			case  CONST_misMsgType_refreshContactsStatus_qmc:  {
				   MIS_MSG_REFRESHCONTACTSSTATUS_QMC  *  pMsg  =  (  MIS_MSG_REFRESHCONTACTSSTATUS_QMC  *  )pComm;
				   //
				   bRefreshContactsStatus_wnd(  pMsg,  &this->m_var.displayCtx,  tmpHandler_bRefreshContactsStatus_leftView,  this  ); 
				   
				   }
				   break;
			 case  CONST_misMsgType_refreshMeStatus_qmc:  {
				   MIS_MSG_REFRESHMESTATUS_QMC  *  pMsg  =  (  MIS_MSG_REFRESHMESTATUS_QMC  *  )pComm;
				   //
				   bRefreshMeStatus_wnd(  pMsg,  &this->m_var.displayCtx,  tmpHandler_bRefreshContactsStatus_leftView,  this  );				

				   }
				   break;

				   //
			 case  CONST_qyWmParam_delItem:			{
				   //QY_MC_DOCSTRUCT		*	pDocStruct	=	&GetDocument(  )->m_docStruct;
				   QY_WMBUF_PROCTV		*	pProcTv  =  (  QY_WMBUF_PROCTV  *  )pComm;
				   QY_MC_SEL				curSel;
				   QY_WMBUF_PUTDATA			tmpPutData;
				   HTREEITEM				htItemWillFocusOn;
					 
#if  10
				   if  (  pProcTv->hItem  ==  m_var.htMyRootItem  )  {
					   #ifdef  __DEBUG__
							   traceLogA(  "错误：试图删除跟节点"  );  
					   #endif
					   goto  errLabel;
				   }
				   if  (  !(  htItemWillFocusOn  =  m_TreeCtrl->GetParentItem(  (  HTREEITEM  )pProcTv->hItem  )  )  )  goto  errLabel;

				   BOOL  tmpbRet;
				   tmpbRet  =  this->m_TreeCtrl->DeleteItem(  (  HTREEITEM  )pProcTv->hItem  );

				   m_TreeCtrl->SelectItem(  htItemWillFocusOn  );

				   #ifdef	__DEBUG__
							showItem(  htItemWillFocusOn  );
							int  iii  =  0;
				   #endif

				   bRefreshItem(  htItemWillFocusOn  );
		
#if  0
				   memset( &curSel, 0, sizeof( curSel ) );
				   curSel.type  =  QY_SELTYPE_MCROOTTREE;
				   curSel.u.rootTree.type	=  pDocStruct->u.treeList.tree.type;
				   if  (  !(  curSel.u.rootTree.bRoot  =  (  htItemWillFocusOn  ==  m_var.htMyRootItem  )  )  )  {
					   curSel.u.rootTree.hItem  =  htItemWillFocusOn;
				   	   curSel.u.rootTree.iHelpId  =  m_TreeCtrl->GetItemData(  htItemWillFocusOn  );
				   }
				   if  (  pDoc->m_docStruct.u.treeList.tree.pfProcTreeSel  )  pDoc->m_docStruct.u.treeList.tree.pfProcTreeSel(  pQyMc,  &curSel,  0  );
					
				   memset(  &tmpPutData,  0,  sizeof(  tmpPutData  )  );
				   tmpPutData.uiType  =  QY_WMPARAM_MCPUTROOTDISPLAYDATA;
				   MACRO_qyAssert(  sizeof(  tmpPutData.u  )  >=  sizeof(  curSel  ),  _T(  "wmBuf to put data is too small."  )  );
				   memcpy(  &tmpPutData.u,	 &curSel,  sizeof(  curSel  )  );
				   getMgrWnd(  )->SendMessage(  CONST_qyWm_comm,  (  WPARAM  )this->m_hWnd,  (  LPARAM  )&tmpPutData  );
#endif

#endif
				   						 
					}
				   break;


			default:
				    goto  errLabel;
	}
	lRet  =  QY_RC_WMOK;
errLabel:
	return	lRet;
}


LRESULT  CDlgLeftView_db::OnQyPostComm( WPARAM  wParam, LPARAM  lParam )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )   return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs   ) return  -1;

	return  pFuncs->mainWnd.pf_mainWnd_OnQyPostComm(  this->m_hWnd,  &this->m_var,  wParam,  lParam  );
}

 LRESULT CDlgLeftView_db::OnQyTrayNotify(  WPARAM  wParam,  LPARAM  lParam  )
{

	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  ) return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs   ) return  -1;

	pFuncs->mainWnd.pf_mainWnd_OnQyTrayNotify(  m_hWnd,  &m_var,  wParam,  lParam  );

	return  0;
}


   LRESULT CDlgLeftView_db::OnQyGraphNotify_mediaFile(  WPARAM  wParam,  LPARAM  lParam  )
{
	int						iErr			=	-1;
	QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  return  -1;
	MC_VAR_isCli			*	pProcInfo		=	(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs   ) return  -1;

	int						iIndex_sharedObj	=	(  int  )lParam;

	QY_SHARED_OBJ		*	pSharedObj	=	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	CAP_procInfo_bmpU	*	pCapBmp	=	getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  CONST_capType_mediaFile  );
	if  (  !pCapBmp  )  goto  errLabel;
#if  0
	QM_SHM_CMD			*	pShmCmd	=	getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pSharedObj->iIndex_shmCmd  );
	if  (  !pShmCmd  )  goto  errLabel;
#endif

	bool  bLooping  =  true;
	bool  bPlayThrough  =  true;
	//
	pFuncs->mainWnd.pf_handleGraphEvent_mediaFile(  pSharedObj->pShareMediaObj,  TRUE,  bLooping,  bPlayThrough  );

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		traceLogA(  "CMainFrame::OnQyGraphNotify failed"  );
	}

	return  0;
}

 LRESULT CDlgLeftView_db::OnQyGraphNotify_mediaDevice(  WPARAM  wParam,  LPARAM  lParam  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs   ) return  -1;

	return  pFuncs->mainWnd.pf_mainWnd_OnQyGraphNotify_mediaDevice(  g_pQyMc,  m_hWnd,  &m_var,  wParam,  lParam  );
}


void CDlgLeftView_db::OnHelp() 
{
	int				iErr							=	-1;
	QY_MC		*	pQyMc							=	QY_GET_GBUF(  );
	TCHAR			helpFileName[MAX_PATH  +  1]	=	_T(  ""  );
    

	if  (  pQyMc->iServiceId  ==  CONST_qyServiceId_netMc  )  {
		if  (  pQyMc->cusRes.suffix[0]  )  {
			_sntprintf(  helpFileName,  mycountof(  helpFileName  ),  _T(  "%s%s%s.%s.chm"  ),  CString(  pQyMc->cfg.installDir  ),  CString(  CONST_qyHelpSubDir  ),  CString(  pQyMc->cfg.pGuiCfg->helpPureFile  ),  pQyMc->cusRes.suffix  );
			if  (  GetFileAttributes(  helpFileName  )  ==  INVALID_FILE_ATTRIBUTES  )  helpFileName[0]  =  0;
		}
		if  (  !helpFileName[0]  )	{
			_sntprintf(  helpFileName,  mycountof(  helpFileName  ),  _T(  "%s%s%s.chm"  ),  CString(  pQyMc->cfg.installDir  ),  CString(  CONST_qyHelpSubDir  ),  CString(  pQyMc->cfg.pGuiCfg->helpPureFile  )  );
		}
		//if  (  !lstrcmpi(  pQyMc->cusRes.suffix,  _T(  "jt"  )  )  )  _sntprintf(  helpFileName,  mycountof(  helpFileName  ),  _T(  "%s%s"  ),  helpFileName,  _T(  "::/html/Ä¿Â¼.html"  )  );
		//  else  
		_sntprintf(  helpFileName,  mycountof(  helpFileName  ),  _T(  "%s%s"  ),  helpFileName,  _T(  "::/html/index.htm"  )  );

		// 	helpFile += "Help\\Dect.chm::/Ä¿Â¼.htm";
	
		::HtmlHelp(  NULL,  CString(  helpFileName  ),  HH_DISPLAY_TOPIC,  0  );	

		iErr  =  0;  goto  errLabel;

	}

	if  (  pQyMc->iServiceId  ==  CONST_qyServiceId_is  )  {

		_sntprintf(  helpFileName,  mycountof(  helpFileName  ),  _T(  "http://www.qycx.com/products/is/qm/help/index.html"  )  );

		ShellExecute(  NULL,  _T(  "open"  ),  helpFileName,  _T(  ""  ),  NULL,  SW_SHOW  );

		iErr  =  0;  goto  errLabel;
	}

	iErr  =  0;
errLabel:

	return;

}


//
#ifdef  __DEBUG__

static  QIS_pipe  *  spQisPipe  =  NULL;

//
void	  doQyTest(  )
{
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  !pQyMc  )  return;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;

	//
	//createGeneralWall(  pQyMc->g_hInst,  _T(  "d3d wnd"  ),  NULL,  NULL,  0,  0  );

	IM_GRP_EX  req;
	//
	createTmpGrp( pQyMc->gui.hGuiWnd,  &req  );

	//


errLabel:

	//
	return;
}


//
int  testSndRtspMsg(  )
{
	CQyMalloc  mallocObj;
	int  size  =  sizeof(  RTSP_msg  );
	RTSP_msg  *  pMsg  =  (  RTSP_msg  *  )mallocObj.mallocf(  size  );
	if  (  !pMsg  )  return  -1;
	
	memset(  pMsg,  0,  offsetof(  RTSP_msg,  buf  )  );
	//
	static  int  i  =  0;  i  ++  ;
	//
	_snprintf(  pMsg->buf,  mycountof(  pMsg->buf  ),  "hello test. %d",  i  );
	//
	pMsg->uiLen  =  strlen(  pMsg->buf  );

	int  msgLen  =  offsetof(  RTSP_msg,  buf  )  +  pMsg->uiLen;
	//
	qisPipe_writeMsg(  pMsg,  msgLen,  spQisPipe  );

	return  0;

}


#endif



///
void CDlgLeftView_db::OnIsCmd(  UINT nID  )
{
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs   ) return;
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	//
	if  (  nID  ==  ID_qyRefresh  )  {		
		bRefreshImObjView_isCli(  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  )  );
		return;
	}

	//
	switch  (  nID  )  {
			case  ID_about:
				  myOnAppAbout(  m_hWnd  );
				  break;
#if  0	//  2014/04/26
			case  ID_qyRefresh:		
				  Onqyrefresh(  );
				  break;
#endif
			case  ID_qySearch:
				  Onqysearch(  );
				  break;
			case  ID_retrieveAll:
				  traceLogA(  "retrieve contact list"  );
				  break;
				  //
				  //
			case  ID_notTestGps:  {		//  2012/05/15
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  
				  if  (  !pProcInfo->cfg.ucbTestGps  )  break;

				  //
				  exitTestGps(  );

				  pProcInfo->cfg.ucbTestGps  =  FALSE;
				  }
				  break;
			case  ID_testGps:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  if  (  pProcInfo->cfg.ucbTestGps  )  break;

				  //
				  initTestGps(  );

				  pProcInfo->cfg.ucbTestGps  =  TRUE;
				  }
				  break;
				  //
			case  ID_qyShowWnd:
				  MACRO_SetForegroundWindow(  m_hWnd  );
				  break;
			case  ID_qyQuitMainWnd:  {
				  //pFuncs->mainWnd.pf_mainWnd_OnQyQuitMainWnd(  this->m_hWnd,  &m_var  );
				  //  2017/01/04
				  QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

				  ::PostMessage(  pQyMc->gui.hMainWnd,  WM_COMMAND,  MAKEWPARAM(  ID_qyQuitMainWnd,  0  ),  0  );
				  }
				  break;

			case  ID_imTaskList_unproced:
				  g_dbFuncs.pf_bViewImTaskList_unproced(   getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  );
				  break;

			case  ID_imTaskList_cur:
				  //  bViewImTaskListFunc(   getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_current  ),  _T(  ""  ),  FALSE  );
				  g_dbFuncs.pf_bViewImTaskList_cur(   getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_current  ),  _T(  ""  )  );
				  break;
			case  ID_imTaskList_his:
				  //  bViewImTaskListFunc(  getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_history  ),  _T(  ""  ),  TRUE  );
				  g_dbFuncs.pf_bViewImTaskList_his(  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_history  ),  _T(  ""  )  );
				  break;

			case  ID_qwmSvrList:
				  bViewClientList(  pQyMc,  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  )  );	
				  break;

			case  ID_viewQnmStatus:
				  viewQnmStatus(  ); 
#ifdef  __DEBUG__				  	
		#if  1
				  startToParse(  );				
		#endif
#endif
				  break;
			case  ID_cliModule0:
			case  ID_cliModule1:
			case  ID_cliModule2:
			case  ID_cliModule3:
			case  ID_cliModule4:  {
				  CUS_MODULE_U	*	pModule	=	NULL;
				  int					i;

				  for  (  i  =  0;  i  <  pQyMc->cusModules.usCnt;  i  ++  )  {
					   pModule  =  &pQyMc->cusModules.mems[i];
					   switch  (  pModule->common.uiType  )  {
							   case  CONST_moduleType_vDev:
								     if  (  pModule->vDev.uiCmd  ==  nID  )  {
										 if  (  pModule->vDev.pf_qyVDev_op  )  pModule->vDev.pf_qyVDev_op(  0,  0,  0  );
									 }
									 break;							   
							   default:
									   break;
					   }
				  }	
				  
				  }
				  break;

			case  ID_2dVWall_new:  	//  2012/04/02
				  //  Onnewvirtualwall(  );
				  int  iWndContentType;
				  iWndContentType  =  CONST_qyWndContentType_vWall;
				  //viewVWall(  ::GetDesktopWindow(  ),  _T(  ""  ),  0,  TRUE,  NULL,  FALSE,  NULL  );
				  viewVWall(  ::GetDesktopWindow(  ),  _T(  ""  ),  0,  FALSE,  NULL,  FALSE,  NULL  );
				  break;
			case  ID_2dVWall_global:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  if  (  IsWindow(  pProcInfo->g_hVWall  )  )  {
					  MACRO_SetForegroundWindow(  pProcInfo->g_hVWall  );
					  break;
				  }
				  viewGlobalVWall(  ::GetDesktopWindow(  ),  _T(  ""  ),  NULL,  FALSE  );				  
				  }
				  break;
			case  ID_globalGpsVWall:  {
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;

				  if  (  IsWindow(  pProcInfo->g_hVWall  )  )  {
					  MACRO_SetForegroundWindow(  pProcInfo->g_hVWall  );
					  break;
				  }
				  viewGlobalGpsVWall(  ::GetDesktopWindow(  ),  _T(  ""  )  );				  
				  }break;
			case  ID_gpsVWall:	{  //  2012/04/22
				  viewGpsVWall(  ::GetDesktopWindow(  ), _T(  ""  )  );
				  }				  
				  break;
			case  ID_3dVWall_console:  {
				  //
				  if (GuiShare.pf_doPre_createConsoleWall)  GuiShare.pf_doPre_createConsoleWall(NULL, NULL, NULL);
				  //
				  dyn_createConsoleWall(  pQyMc->pGBuf_d3d  );
				  }
				  break;
			case ID_3dVWall_new:  {
				  dyn_createGeneralWall(  pQyMc->g_hInst,  _T(  "d3d wnd"  ),  NULL,  NULL,  0,  0  );
				  }
				  break;
			case  ID_qyMessengerList:  {		//  2012/07/19
				  #if 0
					bViewMessengerList(  getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),	_T(  ""  )  );
				  #else		//  2014/04/27
					g_dbFuncs.pf_bViewImObjList(  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyMessengerList  ),  _T(  ""  )  );
				  #endif
				  }
			      break;
			case  ID_qyImGrpList:  {		//  2012/07/21
				  #if 0
					bViewImGrpList(  getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),	_T(  ""  )  );
				  #else
					g_dbFuncs.pf_bViewImGrpList(  pQyMc,  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyImGrpList  ),  _T(  ""  )  );
				  #endif
			      }
				  break;
			case  ID_qyImGrpMemList:  {	//  2012/07/21
				  #if  0
					bViewImGrpMemList_isClient(  getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),	_T(  ""  )  );
				  #else
					g_dbFuncs.pf_bViewImGrpMemList_isClient(  pQyMc,getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),	_T(  ""  )  );
				  #endif
				  }
				  break;
			case  ID_imObjRuleList:
				  #if  0
					bViewImObjRuleList_is(  getProcedObjDb(  0,  g_pQyMc->iDsnIndex_mainSys  )  );
				  #else
					g_dbFuncs.pf_bViewImObjRuleList_is(  pQyMc,  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  )  );
				  #endif
				  break;
				  //
			case  ID_createTmpGrp:  {  //  2017/07/31
				  IM_GRP_EX  req;
				  createTmpGrp(  m_hWnd,  &req  );
				  //
				  //
				  int  iObjType;
				  char  buf[128];
				  int  iObjId;
				  int  getObjId_myDb(  LP_hashTbl  pHashTbl_tree,  int  iObjType,  char  *  pKeyStr  );
				  CDlgLeftView_db  *  pLeftView  =  this;
				  TCHAR  displayName[128];
				  int  nImage,  nSelectedImage;
				  HTREEITEM  tmphtItem;

				  //					
				  iObjType  =  CONST_objType_imGrps_tmp;
				  myTChar2Utf8(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_imGrps_tmp  ),  buf,  mycountof(  buf  )  );
				  iObjId  =  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );
				  if  (  iObjId  <  0  )  goto  errLabel;;

				  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_imGrps_tmp  )  )  );
				  nImage  =  pQyMc->cfg.image.nImage_imGrps;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedImGrps;

				  if  (  !(  tmphtItem  =  pLeftView->FindItemData(  iObjId,  TRUE,  pLeftView->m_var.htMyRootItem  )  )  )  {
					  }
				  else  {			  
					    this->bRefreshItem(  tmphtItem  );		  
				  }

				  }
				  break;
				  //
				  //
			case  ID_subtitle_webcam:
				  viewDlgSubtitles(  0,  CONST_capType_av,  CONST_subCapType_webcam,  m_hWnd  );				  
				  break;
			case  ID_shareDynBmps:{	//  2012/07/21
				  viewDlgShareDynBmps_isCli(  FALSE  );
				  }
				  break;
			case  ID_viewOfflineRes:  {			//  2015/08/05
				  HWND  hParent  =  m_hWnd;
				  viewDlgOfflineRes_me(  hParent,  &pProcInfo->offlineRes,  NULL  );				  
				  }
				  break;
			case  ID_playQvcf:  {				//  2015/05/15
				  //
				  LPCTSTR							lpszDefExt  =	TEXT("qvcf\0");
				  LPCTSTR							lpszFilter	=	_T(  "Qycf file(*.qvcf)\0\*.qvcf\0\0"  );
				  LPCTSTR							title		=	TEXT("Open Qvcf File...\0");
				  TCHAR								pathStr[MAX_PATH]  =  _T(  ""  );
				  DWORD								dwFlags     =	OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;
				  //
				  if  (  qyBrowseForFile1(  m_hWnd,  TRUE,  lpszDefExt,  dwFlags,  lpszFilter,  title,  NULL,  pQyMc,  pathStr,  mycountof(  pathStr  )  )  )  break;
				  if  (  !pathStr[0]  )  break;
				  //
				  viewQvcf(  m_hWnd,  pathStr  );
				  }
				  break;
			case  ID_qyStartLocalVideo:  {	//  2012/07/21
				  testLocalAv(  m_hWnd  );
				  }
				  break;
			case  ID_localPtzControl:	{		//  2012/08/01
				  //
				  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  //
				  unsigned  int  uiObjType_camera  =  0;
				  //
				  PARAM_viewLocalPtzControl  param  =  {0};
				  //
				  QIS_ptz_wnd  *  pPtzWnd  =  &pProcInfo->ptzWnd;
				  //
				  BOOL  bManual  =  TRUE;		//  2014/10/14
				  viewLocalPtzControl(  m_hWnd,  bManual,  uiObjType_camera,  0,  0,  &param,  pPtzWnd  );
				  }
				  break;
			case  ID_chromaKeyCfg:	//  2013/09/27
				  //  viewChromaKeyCfg(  m_hWnd  );
				  viewDlgImg(  m_hWnd,  CONST_dlgImgSubtype_chromaKey,  _T(  "Chroma Key"  )  );
				  break;
			case  ID_qyMsgToday:{	//  2012/07/21
				  bViewImMsgToday(  pQyMc,  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  NULL  );
				  }
				  break;
			case  ID_qyMsgList:  {	//  2012/07/21
				  bViewImMsgListFunc(  pQyMc,  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  NULL,  NULL  );
				  }
				  break;
			case  ID_qyEventAll:  {  //  2012/07/21
				  bViewAllEventList(  pQyMc,  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  )  );
				  }
				  break;
			case  ID_qyOpEventAll:	{	//  2012/07/21
				  bViewAllOpEventList(  pQyMc,  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  )  );	
				  }
				  break;
			case  ID_cfgRasOptions:  {	//  2012/07/22
#if  0
				  CDlgPolicyIsClient	dlg;
                  #ifndef  __WINCE__
				           dlg.DoModal(  );
                  #else
				       DialogBoxParam(  g_hInst,  MAKEINTRESOURCE(  dlg.IDD  ),  this->m_hWnd,  dlgProc_policyIsClient,  (  LPARAM  )&dlg  );
                  #endif
#endif
				  showDlgPolicyIsClient(  m_hWnd  );
				  }
				  break;
			case  ID_cfgOptions:  {		// 2012/07/22
				  pFuncs->mainWnd.pf_showDlgQnmCfgOptionsIsClient(  pQyMc->g_hInst,  0,  0,  pQyMc  );
				  }
				  break;
			case  ID_notPlayRemoteAudio:{										
				  MC_VAR_isCli	*	pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  pProcInfo->cfg.ucbPlayRemoteAudio_viewDynBmp  =  FALSE;										
				  }				   
				  break;
			case  ID_playRemoteAudio:{										
				  MC_VAR_isCli	*	pProcInfo  =  QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  break;
				  pProcInfo->cfg.ucbPlayRemoteAudio_viewDynBmp  =  TRUE;										
				  }				   
				  break;
			case  ID_setPasswd:  {	//  2012/07/22
				  setPasswd_isClient(  m_hWnd  );
			      }
				  break;
			case  ID_qyPcUsrList:  {	//  2012/07/23
				  //  bViewObjRegInfoList(  getProcedObjDb(  0,  g_pQyMc->iDsnIndex_mainSys  )  );	
				  //  bViewMessengerRegInfoList(  getProcedObjDb(  0,  g_pQyMc->iDsnIndex_mainSys  )  );
				  g_dbFuncs.pf_bViewRegInfoList(  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyPcUsrList2  ),  _T(  ""  )  );
				  }
				  break;
			case  ID_qyPcUsrInTab1List:  {	//  2012/07/23
				  bViewObjRegInfoInTab1List(  pQyMc,  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  )  );
				  }
				  break;
			case  ID_qyClearUp:  
				  OnqyClearUp(  );
				  break;
			case  ID_qyTest:
				  #ifdef  __DEBUG__  
				{
						  doQyTest(  );
						  //
						  int  iObjType;
						  char  buf[128];
						  int  iObjId;
						   int  getObjId_myDb(  LP_hashTbl  pHashTbl_tree,  int  iObjType,  char  *  pKeyStr  );
						   CDlgLeftView_db  *  pLeftView  =  this;
						   TCHAR  displayName[128];
						   int  nImage,  nSelectedImage;
						   HTREEITEM  tmphtItem;


						  						  
						  //
						  iObjType  =  CONST_objType_imGrps_tmp;
		  myTChar2Utf8(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_imGrps_tmp  ),  buf,  mycountof(  buf  )  );
		  iObjId  =  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );
		  if  (  iObjId  <  0  )  goto  errLabel;;

		  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_imGrps_tmp  )  )  );
		  nImage  =  pQyMc->cfg.image.nImage_imGrps;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedImGrps;
				
		  if  (  !(  tmphtItem  =  pLeftView->FindItemData(  iObjId,  TRUE,  pLeftView->m_var.htMyRootItem  )  )  )  {
		  }

		  else  {
			  this->bRefreshItem(  tmphtItem  );
		  }
				}
				  #endif
				  break;

			default:
					break;
	}

	//
	if  (  (  nID  >  ID_viewDebugStatus_minCmd  )  &&  (  nID  <  ID_viewDebugStatus_maxCmd  )  )  {
		//OnViewDebugStatus(  nID  );
		debugStatusInfo_OnIsCmd(nID,  &pQyMc->env,  &pProcInfo->cfg.debugStatusInfo  );
	}

errLabel:
	return;
}


void CDlgLeftView_db::OnUpdateIsCmd(CCmdUI *pCmdUI)
{
	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );

	if  (  !pProcInfo  )  return;

	//  traceLogA(  "OnUpdateIsCmd: %d",  pCmdUI->m_nID  );
	switch  (  pCmdUI->m_nID  )  {
			case  ID_notPlayRemoteAudio:
				  if  (  !pProcInfo->cfg.ucbPlayRemoteAudio_viewDynBmp  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_playRemoteAudio:
				  if  (  pProcInfo->cfg.ucbPlayRemoteAudio_viewDynBmp  )  pCmdUI->Enable(  FALSE  );
				  break;

			case  ID_qyQuitMainWnd:
				  break;
			case  ID_qwmSvrList:
				  if  (  !bQnmCmdEnable(  ID_qwmSvrList  )  )  {
					  pCmdUI->Enable(  FALSE  );  return;
				  }
				  break;
			case  ID_pcRuleList0:
			case  ID_pcRuleList1:
				  if  (  !bQnmCmdEnable(  pCmdUI->m_nID  )  )  {
					  pCmdUI->Enable(  FALSE  );  return;
				  }
				  break;
			case  ID_viewQnmStatus:
				#if  0
				  if  (  !bQnmCmdEnable(  pCmdUI->m_nID  )  )  {
					  pCmdUI->Enable(  FALSE  );  return;
				  }
				#endif
				  break;
			case  ID_cliModule0:
			case  ID_cliModule1:
			case  ID_cliModule2:
			case  ID_cliModule3:
			case  ID_cliModule4:  {
				  CUS_MODULE_U	*	pModule	=	NULL;
				  int				i;

				  for  (  i  =  0;  i  <  pQyMc->cusModules.usCnt;  i  ++  )  {
					   pModule  =  &pQyMc->cusModules.mems[i];
		 			   switch  (  pModule->common.uiType  )  {
							   case  CONST_moduleType_vDev:
								     if  (  pModule->vDev.uiCmd  ==  pCmdUI->m_nID  )  {
										 if  (  !pModule->vDev.ucbVDevInited  )  pCmdUI->Enable(  FALSE  );
									 }
									 break;
							   default:
									   break;
					   }
				  }
				  
				  }
				  break;
			case  ID_2dVWall_new:
				  break;
			case  ID_2dVWall_global:  {
				  MIS_CNT	*	pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
				  if  (  !pMisCnt  )  goto  errLabel;
				  if  (  findSubWnd(  &pMisCnt->subWnds,  CONST_qyWndContentType_vWall,  CONST_vwSubtype_globalGps  )  )  pCmdUI->Enable(  FALSE  );
				  }
				  break;
			case  ID_globalGpsVWall:  {
				  MIS_CNT	*	pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
				  if  (  !pMisCnt  )  goto  errLabel;
				  if  (  findSubWnd(  &pMisCnt->subWnds,  CONST_qyWndContentType_vWall,  CONST_vwSubtype_confWall  )  )  pCmdUI->Enable(  FALSE  );
				  }
				  break;
			case  ID_gpsVWall:  
				  break;
			case  ID_3dVWall_console:	//  2013/12/27								  
				  if  (  bLikeXp(  )  )  pCmdUI->Enable(  FALSE  );				  
				  break;
			case  ID_3dVWall_new:
				  if  (  bLikeXp(  )  )  {
					  pCmdUI->Enable(  FALSE  );
					  break;
				  }
				  //
				  GBuf_d3d_isCli  *  pGBuf;
				  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
				  if  (  !pGBuf  )  goto  errLabel;
				  if  (  !IsWindow(  pGBuf->hWall_d3d  )  )  {
					  pCmdUI->Enable(  FALSE  );
					  break;
				  }
				  //
				  break;

			case  ID_qyMessengerList:
			case  ID_qyImGrpList:  
			case  ID_qyImGrpMemList:  
			//case  ID_sharedDynBmpList:  
			case  ID_shareDynBmps:
			case  ID_qyMsgList:  
				  break;
			case  ID_qyStartLocalVideo:{
#if  0
				  QY_SHARED_OBJ		*	pSharedObj		=	getSharedObjByIndex(  pProcInfo,  getSharedObjIndex_localAv(  )  );
				  if  (  !pSharedObj  )  goto  errLabel;
				  
				  if  (  IsWindow(  pProcInfo->hWnd_testWebcam  )  )  {
					  pCmdUI->Enable(  FALSE  );
					  goto  errLabel;
				  }
#endif
				  }
				  break;
			case  ID_qyMsgToday:{	//  2012/07/21
				#if  0
				  if  (  !bQnmCmdEnable(  ID_qyMsgToday  )  )  {
					  pCmdUI->Enable(  FALSE  );  goto  errLabel;
				  }
				#endif
				  }
				  break;
			case  ID_qyEventAll:    
			case  ID_qyOpEventAll:	
				  break;


			case  ID_notTestGps:
				  if  (  !pProcInfo->cfg.ucbTestGps  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_testGps:
				  if  (  pProcInfo->cfg.ucbTestGps  )  pCmdUI->Enable(  FALSE  );
				  break;


			default:
					break;
	}	

	//
	if  (  (  pCmdUI->m_nID  >  ID_viewDebugStatus_minCmd  )  &&  (  pCmdUI->m_nID  <  ID_viewDebugStatus_maxCmd  )  )  {
		//OnUpdateViewDebugStatus(  pCmdUI  );
		debugStatusInfo_OnUpdateIsCmd(  &pQyMc->env,  &pProcInfo->cfg.debugStatusInfo,  pCmdUI  );
		//
#ifdef  __DEBUG__				 
		{				
			int  ii  =  0;
			CString str;
			if  (  pCmdUI->m_pMenu  )  {
				pCmdUI->m_pMenu->GetMenuString(pCmdUI->m_nID,  str,  0  );
				int  jj  =  0;
			}			
		}
#endif
		}
	else  {
#ifdef  __DEBUG__		  		
		{		
			int  ii  =  0;		
			CString str;						
			if  (  pCmdUI->m_pMenu  )  {	
				pCmdUI->m_pMenu->GetMenuString(pCmdUI->m_nID,  str,  0  );	
				int  jj  =  0;						
			}				
		}
#endif

	}

errLabel:

	return;
}




 



  void CDlgLeftView_db::Onqysearch()
  {
	  // TODO: Add your command handler code here
	  doQnmSearch(  -1  );
  }






   void CDlgLeftView_db::OnqyClearUp() 
{
	mainFrm_OnqyClearUp(  m_hWnd  );
}

void CDlgLeftView_db::OnUpdateqyClearUp(CCmdUI* pCmdUI) 
{
	if  (  !bQnmCmdEnable(  ID_qyClearUp  )  )  {
		pCmdUI->Enable(  FALSE  );  return;
	}
	
}




void CDlgLeftView_db::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::PostNcDestroy();

	OutputDebugString(  _T(  "DlgLeftView_db::PostNcDestroy: delete this\n"  )  );

	delete  this;

}


void CDlgLeftView_db::OnTvnSelchangedimobjtree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	
	//  NM_TREEVIEW				*		pNMTreeView		=		(NM_TREEVIEW*)pNMHDR;
	CTreeCtrl				&		treeCtrl		=		*this->m_TreeCtrl;	//  GetTreeCtrl( );
	HTREEITEM						hRoot			=		NULL;
	HTREEITEM						hCur			=		pNMTreeView->itemNew.hItem;
	HTREEITEM						hOld			=		pNMTreeView->itemOld.hItem;
	QY_MC					*		pQyMc			=		QY_GET_GBUF(  );
	//  CQyMcDoc				*		pDoc			=		GetDocument(  );
	QY_MC_SEL						curSel;
	QY_WMBUF_PUTDATA				tmpPutData;
	
	CWaitCursor						waitCursor;

	traceLogA(  "CLeftView::OnSelChanged"  );

	if  (  !hCur  )	 return;
	if  (  !(  hRoot  =  treeCtrl.GetRootItem(  )  )  )		return;
	//  if  (  !hOld  )	 return;
	if  (  hOld  ==  hCur  )	{
		qyDebugHint(  _T(  "CLeftView::OnSelchanged( ): how strange! hOld = hCur!" )  );
		return;
	}
	
	bRefreshItem(  hCur  );
	
	memset( &curSel, 0, sizeof( curSel ) );
	curSel.type  =  QY_SELTYPE_MCROOTTREE;
	curSel.u.rootTree.iDsnIndex  =  m_docStruct.u.treeList.tree.iDsnIndex;	//  2007/01/02
	curSel.u.rootTree.hItem  =  hCur;
	if  (  hCur  ==  hRoot  )  curSel.u.rootTree.bRoot  =  TRUE;	
	else  curSel.u.rootTree.iHelpId  =  treeCtrl.GetItemData(  hCur  );
	if  (  m_docStruct.u.treeList.tree.pfProcTreeSel  )  m_docStruct.u.treeList.tree.pfProcTreeSel(  pQyMc,  &curSel,  0  );

#if  0
	memset(  &tmpPutData,  0,  sizeof(  tmpPutData  )  );
	tmpPutData.uiType  =  QY_WMPARAM_MCPUTROOTDISPLAYDATA;
	MACRO_qyAssert(  MAX_QY_WMBUF_PUTDATALEN  >=  sizeof(  curSel  ),  _T(  "wmBuf to put data is too small."  )  );
	memcpy(  &tmpPutData.u,	 &curSel,  sizeof(  curSel  )  );

	getMgrWnd(  )->SendMessage(  CONST_qyWm_comm,  (  WPARAM  )this->m_hWnd,  (  LPARAM  )&tmpPutData  );
#endif

//  errLabel:

	*pResult  =  0;

}


void CDlgLeftView_db::OnNMRClickimobjtree(NMHDR *pNMHDR, LRESULT *pResult)
{	
	// TODO: Add your control notification handler code here
	QY_MC			*		pQyMc			=		QY_GET_GBUF(  );
	//  CQyMcDoc		*		pDoc			=		GetDocument(  );
	// POINT					point;
	CTreeCtrl		&		treeCtrl		=		*m_TreeCtrl;	//  GetTreeCtrl( );
	QY_MC_SEL				curSel;
	HTREEITEM				hRoot			=		NULL;
	HTREEITEM				hCur			=		NULL;
	QY_EVENTINFO			tmpEventInfo;
	
	traceLogA(  "CLeftView::OnRclick enters"  );

	/* Get the mouse cursor position */
	DWORD dwPos = GetMessagePos();

	/* Convert the co-ords into a CPoint structure */
	CPoint point( GET_X_LPARAM( dwPos ), GET_Y_LPARAM( dwPos ) ), spt;
	spt = point;

	if ( !( hRoot = treeCtrl.GetRootItem( ) ) )		goto errLabel;
	
	/* Convert to screen co-ords for hittesting */
	treeCtrl.ScreenToClient( &spt );

	UINT test;
	hCur = treeCtrl.HitTest( spt, &test );
	
	/* Did the click occur on an item */
	if ( !hCur || !( test & ( TVHT_ONITEM | TVHT_ONITEMRIGHT ) ) )  goto errLabel;
			
	memset( &curSel, 0, sizeof( curSel ) );
	curSel.type		=		QY_SELTYPE_MCROOTTREE;
	curSel.u.rootTree.type  =  m_docStruct.u.treeList.tree.type;				//  2007/08/06
	curSel.u.rootTree.iDsnIndex  =  m_docStruct.u.treeList.tree.iDsnIndex;	//  2007/01/02
	curSel.u.rootTree.hItem  =  hCur;		
	if  (  hCur  ==  hRoot  )  curSel.u.rootTree.bRoot		=		TRUE;	
	else  curSel.u.rootTree.iHelpId		=			treeCtrl.GetItemData(  hCur  );
	if  (  m_docStruct.u.treeList.tree.pfProcTreeSel  &&  m_docStruct.u.treeList.tree.pfProcTreeSel(  pQyMc,  &curSel,  0  )  )  goto  errLabel;
	
	memset(  &tmpEventInfo,  0,  sizeof(  tmpEventInfo  )  );
	tmpEventInfo.type  =  CONST_qyEventType_rClick;
	tmpEventInfo.hWnd  =  this->m_hWnd;
	tmpEventInfo.click.x  =  point.x;
	tmpEventInfo.click.y  =  point.y;
  	
	if  (  m_docStruct.u.treeList.tree.pfProcEvent  )  m_docStruct.u.treeList.tree.pfProcEvent(  pQyMc,  &curSel,  &tmpEventInfo  );

errLabel:
	
	*pResult = 0;

}



void CDlgLeftView_db::OnNMDblclkimobjtree(NMHDR *pNMHDR, LRESULT *pResult)
{

	// TODO: Add your control notification handler code here
	QY_MC			*		pQyMc			=		QY_GET_GBUF(  );
	//  CQyMcDoc		*		pDoc			=		GetDocument(  );
	// POINT					point;
	CTreeCtrl		&		treeCtrl		=		*m_TreeCtrl;	//  GetTreeCtrl( );
	QY_MC_SEL				curSel;
	HTREEITEM				hRoot			=		NULL;
	HTREEITEM				hCur			=		NULL;
	QY_EVENTINFO			tmpEventInfo;

	traceLogA(  "CLeftView::OnDblclk: enters"  );
	
	/* Get the mouse cursor position */
	DWORD dwPos = GetMessagePos();

	/* Convert the co-ords into a CPoint structure */
	CPoint point( GET_X_LPARAM( dwPos ), GET_Y_LPARAM( dwPos ) ), spt;
	spt = point;

	if ( !( hRoot = treeCtrl.GetRootItem( ) ) )		goto errLabel;
	
	/* Convert to screen co-ords for hittesting */
	treeCtrl.ScreenToClient( &spt );

	UINT test;
	hCur = treeCtrl.HitTest( spt, &test );
	
	/* Did the click occur on an item */
	if ( !hCur || !( test & ( TVHT_ONITEM | TVHT_ONITEMRIGHT ) ) )  goto errLabel;
			
	memset( &curSel, 0, sizeof( curSel ) );
	curSel.type		=		QY_SELTYPE_MCROOTTREE;
	curSel.u.rootTree.iDsnIndex  =  m_docStruct.u.treeList.tree.iDsnIndex;	//  2007/01/02
	curSel.u.rootTree.hItem  =  hCur;		
	if  (  hCur  ==  hRoot  )  curSel.u.rootTree.bRoot		=		TRUE;	
	else  curSel.u.rootTree.iHelpId		=			treeCtrl.GetItemData(  hCur  );
	if  (  m_docStruct.u.treeList.tree.pfProcTreeSel  &&  m_docStruct.u.treeList.tree.pfProcTreeSel(  pQyMc,  &curSel,  0  )  )  goto  errLabel;
	
	memset(  &tmpEventInfo,  0,  sizeof(  tmpEventInfo  )  );
	tmpEventInfo.type  =  CONST_qyEventType_dblClick;
	tmpEventInfo.hWnd  =  this->m_hWnd;
	tmpEventInfo.click.x  =  point.x;
	tmpEventInfo.click.y  =  point.y;
  	
	if  (  m_docStruct.u.treeList.tree.pfProcEvent  )  m_docStruct.u.treeList.tree.pfProcEvent(  pQyMc,  &curSel,  &tmpEventInfo  );


errLabel:
	
	*pResult = 0;
}







void CDlgLeftView_db::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	 HDWP			hDwp;
	
	 int  iEdge_l  =  1;
	 int  iEdge_r  =  0;
	 int  iEdge_t  =  1;
	 int  iEdge_b  =  0;
	 //
	 int  iSpace_x  =  0;
	 //
	 int  iW_btn  =  50;
	 int  iH_btn  =  50;

	 //
	 RECT	rc;
	 GetClientRect(  &rc  );

	 int  x,y,iW,iH;
	 int  idc;
	 unsigned  int  uFlags;
	 HWND  hDlg  =  m_hWnd;

	 //
	 int  iCustomId  =  qyGetCustomId(  );

	 //
	 switch  (  iCustomId  )  {
			 case  CONST_qyCustomId_bjyz:  {
				   //
				   hDwp  =  M_BeginDeferWindowPos(  2  );
				   if  (  hDwp  )  {
					   int			iW,  iH;
					   	
					   //
		 			   idc  =  IDC_BUTTON_fileTransfer;
		 			   x  =  iEdge_l;
		 			   y  =  iEdge_t;
		 			   iW  =  iW_btn;
		 			   iH  =  iH_btn;
		 			   uFlags  =  SWP_NOZORDER;
		 			   M_DeferWindowPos(  hDwp,  ::GetDlgItem(  hDlg,  idc  ),  HWND_BOTTOM,  x,  y,  iW,  iH,  uFlags  );
		 
		 			   //  7
		 			   idc  =  m_var.iIDC_tree;
		 			   x  +=  iW  +  iSpace_x;
		 			   //  y;
		 			   iW  =  rc.right  -  rc.left  -  (  iEdge_l  +  iEdge_r  )  -  iW_btn  -  iSpace_x;
		 			   iH  =  rc.bottom  -  rc.top  -  (  iEdge_t  +  iEdge_b  );
		 			   //
		 			   uFlags  =  SWP_NOZORDER;
		 			   M_DeferWindowPos(  hDwp,  ::GetDlgItem(  hDlg,  idc  ),  HWND_BOTTOM,  x,  y,  iW,  iH,  uFlags  );
		 			   //
		 			   M_EndDeferWindowPos(  hDwp  );	 
				   }
				   //
				   }
				   break;
			 default:  {
				   //
				   iEdge_l  =  0;

				   //
				   hDwp  =  M_BeginDeferWindowPos(  2  );
				   if  (  hDwp  )  {
					   int			iW,  iH;
					   	
					   //
		 			   idc  =  IDC_BUTTON_fileTransfer;
		 			   x  =  iEdge_l;
		 			   y  =  iEdge_t;
		 			   iW  =  0;
		 			   iH  =  0;
					   uFlags  =  SWP_NOZORDER  |  SWP_HIDEWINDOW;
		 			   M_DeferWindowPos(  hDwp,  ::GetDlgItem(  hDlg,  idc  ),  HWND_BOTTOM,  x,  y,  iW,  iH,  uFlags  );
		 
		 			   //  7
		 			   idc  =  m_var.iIDC_tree;
		 			   //  x;
		 			   //  y;
		 			   iW  =  rc.right  -  rc.left  -  (  iEdge_l  +  iEdge_r  );
		 			   iH  =  rc.bottom  -  rc.top  -  (  iEdge_t  +  iEdge_b  );
		 			   //
		 			   uFlags  =  SWP_NOZORDER;
		 			   M_DeferWindowPos(  hDwp,  ::GetDlgItem(  hDlg,  idc  ),  HWND_BOTTOM,  x,  y,  iW,  iH,  uFlags  );

		 			   //
		 			   M_EndDeferWindowPos(  hDwp  );	 
				   }
				}
				break;
	 }

	 //
	 return;
					 
}


void CDlgLeftView_db::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CDialogEx::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	// TODO: Add your message handler code here

	// TODO: ÔÚ´Ë´¦Ìí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂë		
	ASSERT(pPopupMenu != NULL);
	
	// check the enabled state of various menu items

	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	// determine if menu is popup in top-level menu and set m_pOther to
	//  it if so (m_pParentMenu == NULL indicates that it is secondary popup)
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
		state.m_pParentMenu = pPopupMenu;    // parent == child for tracking popup
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
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
				{
					// when popup is found, m_pParentMenu is containing menu
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}

	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
	  state.m_nIndex++)
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // menu separator or invalid cmd - ignore it

		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			// possibly a popup menu, route to first item of that popup
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
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
			//  state.DoUpdate(this, m_bAutoMenuEnable && state.m_nID < 0xF000);	//  2007/10/04
			state.DoUpdate(  this,  state.m_nID  <  0xF000  );
		}

		// adjust for menu deletions and additions
		UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}

}

int  locateMainWnd_default(  HWND  hMainWnd  )
{
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	
		//  2007/03/03, ÏÂÃæÎªqyMsgµÄÖ÷²Ù×÷½çÃæµÄÏÔÊ¾
		int		iCxScreen	=  0;
		int		iCyScreen	=	0;
		int		iX			=	0;
		int		iY			=	0;
		int		iWidth		=	250;	//  180;
		int		iHeight		=	500;
		
#if  0	//  def  __APP_qyMc_touchscreen__
		//  iWidth  =  210;		
		iWidth  =  280;
#endif

		iCxScreen  =  GetSystemMetrics(  SM_CXSCREEN  );		//  2005/08/19
		iCyScreen  =  GetSystemMetrics(  SM_CYSCREEN  );		//  2005/08/19
		if  (  !iCxScreen  ||  !iCyScreen  )  goto  errLabel;

		//
		if  (  !bApp_ts(  pQyMc  )  )  {
			iX  =  iCxScreen  -  iWidth  -  60;
			iY	=  (  iCyScreen  -  iHeight  )  /2  -  40;  
			}
		else  {
			  iWidth  =  iCxScreen  /  2;	
			  iHeight  =  iCyScreen  /  2;
			  //
			  iX  =  (  iCxScreen  -  iWidth  )  /  2;
			  iY  =  (  iCyScreen  -  iHeight  )  /  2;
		}
		
		::MoveWindow(  pQyMc->gui.hMainWnd,  iX,  iY,  iWidth,  iHeight,  TRUE  );
	
errLabel:
		return  0;
}

void CDlgLeftView_db::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default

	//
	CDialogEx::OnSysCommand(nID, lParam);

	//  2014/04/14
	switch  (  GET_SC_WPARAM(  nID  )  )  {
			case  SC_RESTORE:  {

				  if  (  bLikeXp(  )  )  {
					  locateMainWnd_default(  m_hWnd  );
					  				  
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgLeftView_db::OnSysCommand: restore"  )  );
				  }

				  }				  
				  break;
			default:
					break;
	}

errLabel:

	return;
}




void CDlgLeftView_db::OnBnClickedButtonfiletransfer()
{
	// TODO: Add your control notification handler code here
	//

	//
	viewDlgFileTransfer(  m_hWnd  );



}





void CDlgLeftView_db::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

#ifdef  __USE_skin__
	M_myOnLButtonUp(  this,  nFlags,  point,  (&this->m_skinProc)  );

#else
	CDialogEx::OnLButtonUp(nFlags, point);
#endif
		
		//

}


BOOL CDlgLeftView_db::OnNcActivate(BOOL bActive)
{
	// TODO: Add your message handler code here and/or call default

#ifdef   __USE_skin__
	M_myOnNcPaint(  this,  (&m_skinProc)  );

#else
	return CDialogEx::OnNcActivate(bActive);
#endif

		//	
	
errLabel:

	return  TRUE;

}


LRESULT CDlgLeftView_db::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default

#ifdef   __USE_skin__
		M_myOnNcHitTest(  this,  point,  (&this->m_skinProc)  );
#else
	return CDialogEx::OnNcHitTest(point);
#endif

}


void CDlgLeftView_db::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if  (  IsIconic(  )  )  {
		PostMessage(WM_SYSCOMMAND,SC_RESTORE,NULL );	
		return;
	}

#ifdef  __USE_skin__
	M_myOnNcLButtonDown(  this,  nHitTest, point,(&this->m_skinProc  )  );
#else
	CDialogEx::OnNcLButtonDown(nHitTest, point);
#endif
	
}


void CDlgLeftView_db::OnNcPaint()
{
	// TODO: Add your message handler code here
#ifdef  __USE_skin__
		M_myOnNcPaint(  this,  (&m_skinProc)  );
#else
	// Do not call CDialogEx::OnNcPaint() for painting messages
	CDialogEx::OnNcPaint();
#endif

}
