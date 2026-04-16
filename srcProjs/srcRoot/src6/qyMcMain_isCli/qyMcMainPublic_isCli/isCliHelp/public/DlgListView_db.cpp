// DlgListView.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"

#include	"DlgListView_db.h"
#include	"funcsForIsCliHelp.h"

#include	"ctxqmc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#if  10
  __declspec(  dllexport  )  int viewDlgListView_db(  HWND  hParent,  int  iWndContentType,  void  *  pSelParam  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int								iErr					=	-1;
	QY_MC					*		pQyMc					=	QY_GET_GBUF(  );
	int								iServiceId				=	CONST_qyServiceId_mis;
	MC_VAR_isCli  			*		pProcInfo				=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	CDlgListView_db			*		pDlg					=	NULL;
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
	CWnd  *  pParent  =  CWnd::GetDesktopWindow(  );
	if  (  IsWindow(  hParent  )  )  {
		pParent  =  CWnd::FromHandle(  hParent  );
	}
	pDlg  =  new  CDlgListView_db(  pParent  );
	if  (  !pDlg  )  goto  errLabel;

	//
	if  (  !pDlg->bSetQyMcDoc(  pSel  )  )  goto  errLabel;
	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	pDlg->ShowWindow(  SW_SHOW  );

	//
	pSel->u.query.hFrame  =  pDlg->m_hWnd;		//  2009/09/03

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
#endif


// CDlgListView_db dialog

IMPLEMENT_DYNAMIC(CDlgListView_db, CDialog)

CDlgListView_db::CDlgListView_db(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgListView_db::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.m_pParent = pParent;
	m_var.m_nID = CDlgListView_db::IDD;
	m_var.iIDC_list  =  IDC_list;

}

CDlgListView_db::~CDlgListView_db()
{
}

 BOOL  CDlgListView_db::bSetQyMcDoc(  QY_MC_SEL  *  pSel  )
{
	 BOOL			bRet	=	FALSE;
 	 QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	 MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
		 FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return  FALSE;

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

				   if  (  !(  pObj  =  pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pSel->u.query.iDsnIndex  )  )  )  {
					   traceLogA(  "iDsnIndex error"  );  goto  errLabel;
				   }
				   if  (  !pObj->ucbLoaded  )  {
					   traceLogA(  "dsn is unloaded"  );  goto  errLabel;
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

  BOOL CDlgListView_db::bDocAvail(  )
{
	 BOOL  bRet  =  FALSE;
	 
	  switch  (  this->m_docStruct.iDocType  )  {
			  case  QY_DOCTYPE_MC:
				    goto  errLabel;
			  case  QY_DOCTYPE_MCSITE:
			  case  QY_DOCTYPE_MCWEB:
				    if  (  !this->m_docStruct.m_pMcObj  )  goto  errLabel;
				    break;
			  case  QY_DOCTYPE_MCQUERY:
				    if  (  !m_rs.IsOpen(  )  )  goto  errLabel;
				    break;
			  default:
				      break;		
	  }

	  bRet  =  TRUE;

errLabel:
		return  bRet;
}

 void  CDlgListView_db::qySetTitle(  LPCTSTR  name  )
{
	m_title  =  CString(  m_docStruct.dsnName  )  +  (  m_docStruct.dsnName[0]  ?  CString(  " : "  )  :  CString(  ""  )  )  +  CString(  this->m_docStruct.preDocName  )  +  CString(  name  )  +  CString(  this->m_docStruct.postDocName  );	
}

  BOOL  CDlgListView_db::bSortData(  LPCTSTR  sortStr  )
{
	 BOOL		bRet	=	FALSE;
	 QY_MC	*	pQyMc	=	(  QY_MC  *  )QY_GET_GBUF(  );

	 if  (  m_docStruct.iDocType  !=  QY_DOCTYPE_MCQUERY  )  goto  errLabel;

	 try  {
		  m_rs.SetSort(  sortStr  );
		  _sntprintf(  this->m_docStruct.u.query.sortPart,  sizeof(  m_docStruct.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  sortStr  )  );
		 }
	 catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CQyMcDoc::bSortData failed."  )  );
		   goto  errLabel;
	 }
		
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}



BOOL CDlgListView_db::Create(const RECT& rect)
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


 BOOL  CDlgListView_db::bQuitDlg(  )		
{		
	traceLogA(  "CDlgListView_db(  )::bQuitDlg enters"  );


	//  2009/05/01
	DestroyWindow();				  
		
//  errLabel:

	traceLogA(  "CDlgListView_db(  )::bQuitDlg leaves"  );

	return  TRUE;
}

 int  CDlgListView_db::list(  )
 {
	 int		iErr	=	-1;

	 QY_MC						*		pQyMc					=			QY_GET_GBUF(  );
	 unsigned  int						index					=			0;
	 unsigned  int						nFields					=			0;
	 int								tmpiRet					=			-1;
	 unsigned  int						uiRcdCnt				=			0;
	 CDBVariant							varVals[128];
	 int								nVarVals				=			mycountof(  varVals  );
	CListCtrl		&	ListCtrl	=	*(  CListCtrl  *  )GetDlgItem(  m_var.iIDC_list  );	//  GetListCtrl();

	ListCtrl.DeleteAllItems(  );

	 try  {		
					   
		  nFields  =  m_rs.GetODBCFieldCount(  );
		  if  (  nFields  >  nVarVals  )  {
			  traceLogA(  "bEnumSqlQuery failed: countof pVarVals is not enough"  );  goto  errLabel;
		  }		
		  //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
		  if  (  m_rs.IsBOF(  )  &&  m_rs.IsEOF(  )  )  {
			  #ifdef  __DEBUG__
					  traceLog(  _T(  "dlgListView_db::list: no record"  )  );
			  #endif
			  iErr  =  0;  goto  errLabel;
		  }
		  m_rs.MoveFirst(  );
		  for  (  ;  !m_rs.IsEOF(  );  m_rs.MoveNext(  )  )  {
		  
			   //for  (  index  =  0;  index  <  nFields;  index  ++  )  m_rs.GetFieldValue(  index,  varVals[index]  );

#if  10
			   //
			  CQyRcdset		*	pRecordset  =	(  CQyRcdset  *  )&m_rs;
			   QY_MC_QUERY		*	pQuery		=	&this->m_docStruct.u.query;
			   TCHAR				szValue[QY_MAXPATHLEN + 1];
			   long				index		=	uiRcdCnt;
			   CString				str;

			   int  iSubItem;
			   for  (  iSubItem  =  0;  iSubItem  <  nFields;  iSubItem  ++  )
			   {
				int	i	=	iSubItem;
			
				lstrcpyn(  szValue,  _T(  ""  ),  sizeof(  szValue  )  /  sizeof(  szValue[0]  )  );
				switch  (  pRecordset->m_nDataType[i]  )  {
					
						case  SQL_BIT:
							  if  (  *( ( BOOL * )pRecordset->m_arrayValue[i]  )  )	lstrcpyn(  szValue, _T(  "TRUE"  ),  sizeof(  szValue  )  /  sizeof(  szValue[0]  )  );
				  			  else	lstrcpyn(  szValue, _T(  "FALSE"  ),  sizeof(  szValue  )  /  sizeof(  szValue[0]  )  );
							  break;
						case  SQL_TINYINT:
							  _sntprintf(  szValue,  sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "%c"  ),  *( ( BYTE * )pRecordset->m_arrayValue[i]  )  );
							  break;
						case  SQL_SMALLINT:
							  _sntprintf(  szValue,   sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "%d"  ),  *( ( int * )pRecordset->m_arrayValue[i]  )  );
							  break;
						case  SQL_INTEGER:
							  _sntprintf(  szValue,  sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "%d"  ),  *( ( long * )pRecordset->m_arrayValue[i]  )  );
							  break;
						case  SQL_REAL:
							  _sntprintf(  szValue,  sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "%f"  ),  *( ( float * )pRecordset->m_arrayValue[i]  )  );
							  break;
						case  SQL_FLOAT:
						case  SQL_DOUBLE:
							  _sntprintf(  szValue,  sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "%f"  ),  *( ( double * )pRecordset->m_arrayValue[i]  )  );
							  break;
						case  SQL_DATE:
						case  SQL_TIME:
						case  SQL_TIMESTAMP:
							  _sntprintf(  szValue,  sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "%s"  ), ( ( CTime * )pRecordset->m_arrayValue[i]  )->Format( "%A, %B %d, %Y" )  );
							  break;
						case  SQL_BINARY:
						case  SQL_VARBINARY:
							  _sntprintf(  szValue,  sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "A binary or varBinary."  )  );
							  break;
						case  SQL_DECIMAL:
						case  SQL_NUMERIC:
						case  SQL_CHAR:
						case  SQL_VARCHAR:
							  str  =  *( ( CString * )pRecordset->m_arrayValue[i]  );
							  _sntprintf(  szValue,  sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "%s"  ),  *( ( CString * )pRecordset->m_arrayValue[i]  )  );
							  break;
						case  SQL_LONGVARCHAR:
						case  SQL_LONGVARBINARY:
							  _sntprintf(  szValue,  sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "A long varChar or longVarBinary."  )  );
							  break;
						default:
								MACRO_qyAssert(  0,  _T(  "Serious error:  CQyVirutalListView::OnGetdispinfo(  ): dataType error"  )  );
								break;
				}
				
				TCHAR   pszText[256];       // used if idString is zero
				int  cchTextMax  =  mycountof(  pszText  );

				if  (  m_var.data2DisplayProc  )  m_var.data2DisplayProc(  pQyMc,  pQuery,  pRecordset,  iSubItem,  pszText,  cchTextMax  );
				else  lstrcpyn(  pszText,  CString(  szValue  ),  cchTextMax  );	//  set item text


				int  nImage  =  0;
				{
					//  设置显示图标
					if  (  pQuery->type  ==  CONST_qyQueryType_netMcEventList  ||  pQuery->type  ==  CONST_qyQueryType_netDevEventList  )  nImage  =  0;		//  set image to first in list
					else  if  (  pQuery->type  ==  CONST_qyQueryType_netMcScannedIpList  )  nImage  =  4;
					else  nImage  =  2;
				}
			
				if  (  !iSubItem  )  ListCtrl.InsertItem(  index,  pszText,  nImage  );
				else  ListCtrl.SetItemText(  index,  iSubItem,  pszText  );	

			}
			   #endif


			   uiRcdCnt  ++  ;
			 
		  }
				 	
			}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  L"Is",  0,  L"",  L"",  L"enumSqlQuery failed."  );
		   goto  errLabel;
	}


	 iErr  =  0;

errLabel:

	 return  iErr;
 }


 static  void  sizeDlg(  CDlgListView_db  *  pDlg  )
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
		//  y  =  pDlg->m_var.iTop_list  -  23;
		y  =  pDlg->m_var.iEdge_list_y;
		iW  =  iWidth  -  2  *  pDlg->m_var.iEdge_list_x;
		//  iH  =  iHeight  -  pDlg->m_var.iTop_list;
		iH  =  iHeight  -  2  *  pDlg->m_var.iEdge_list_y;

		DeferWindowPos(  hDwp,  pCtrl->m_hWnd,  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		EndDeferWindowPos(  hDwp  );
	}

errLabel:
	return;
}


void CDlgListView_db::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgListView_db, CDialog)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_list, &CDlgListView_db::OnLvnColumnclicklist)
	ON_NOTIFY(NM_RCLICK, IDC_list, &CDlgListView_db::OnNMRClicklist)
	ON_MESSAGE(  QY_WM_COMM,  OnQyComm  )
	ON_NOTIFY(NM_DBLCLK, IDC_list, &CDlgListView_db::OnNMDblclklist)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDlgListView_db message handlers

BOOL CDlgListView_db::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
#if  0
	
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	QY_COLUMNINFO	*	pColumnInfo	=	NULL;
	int					i,nFields;
	CListCtrl		*	pListCtrl	=  (  CListCtrl  *  )GetDlgItem(  m_var.iIDC_list  );
	SetWindowText(  getResStr(  0,  &pQyMc->cusRes,  this->IDD  )  );

	pListCtrl->ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
	pListCtrl->SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );

	pColumnInfo		=	(  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_qListColumns  );

	CString			str;
	LV_COLUMN		lvc;
	lvc.mask  =  LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
	for (  i = 0; pColumnInfo[i].type  != -1; i ++  ) {
		lvc.iSubItem  =  i;
		lvc.pszText  =  pColumnInfo[i].label;
		lvc.cx  =  pColumnInfo[i].width;
		lvc.fmt  =  pColumnInfo[i].fmt;
		pListCtrl->InsertColumn(  i,  &lvc  );
	}
	nFields  =  i;

	pListCtrl->DeleteAllItems(  );
#endif

	QY_MC			*	pQyMc		=	(  QY_MC  *  )QY_GET_GBUF(  );
	QY_MC_DOCSTRUCT	*	pDocStruct	=	&m_docStruct;
	QY_MC_QUERY		*	pQuery		=	NULL;
	//  
	int					iErr		=	-1;
	CListCtrl		&	ListCtrl	=	*(  CListCtrl  *  )GetDlgItem(  m_var.iIDC_list  );	//  GetListCtrl();
	int					i;
	DWORD				dwStyle		=	0;

	traceLogA(  "CDlgListView_db::OnInitialUpdate(  )."  );

	if  (  pDocStruct->iDocType  !=  CONST_qyDocType_mcQuery  )  goto  errLabel;				
	if  (  !bDocAvail(  )  )  goto  errLabel;
	SetWindowText(  m_title  );

	pQuery		=	&m_docStruct.u.query;
	
	try  {

		 i  =  SendMessage(  TCM_GETUNICODEFORMAT,  0,  0  );

		//  由于记录集中的数据要经过处理，变换才能显示，不一定列数一致，故去掉这一项判断
		//  if  (  pRs->GetODBCFieldCount(  )  !=  pQuery->nFields  )  goto  errLabel;
		
		m_var.data2DisplayProc  =  pQuery->data2DisplayProc;
		m_var.display2DataProc  =  pQuery->display2DataProc;

		dwStyle  =  LVS_REPORT  |  LVS_SHOWSELALWAYS;
		if  (  !pQuery->ucbMultiSel  )  dwStyle  |=  LVS_SINGLESEL;		//  2007/08/24, 准备支持多选
		ModifyStyle(  LVS_TYPEMASK,  dwStyle  );						//  ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
		//
		ListCtrl.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );
		
		m_LargeImageList.Create( IDB_LARGEICONS, 32, 1, RGB( 255, 255, 255 ) );
		m_SmallImageList.Create( IDB_SMALLICONS, 16, 1, RGB( 255, 255, 255 ) );
		ListCtrl.SetImageList( &m_LargeImageList, LVSIL_NORMAL );
		ListCtrl.SetImageList( &m_SmallImageList, LVSIL_SMALL );

		LV_COLUMN	lvcolumn;
		lvcolumn.mask	=	LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvcolumn.fmt	=	LVCFMT_LEFT;
		lvcolumn.cx		=	120;
		
		for  (  i  =  0;  i  <  pQuery->nFields; i  ++  )  {
					 
			 lvcolumn.fmt				=	pQuery->columns[i].fmt;
			 lvcolumn.cx				=	pQuery->columns[i].width;
			 lvcolumn.pszText			=	pQuery->columns[i].label;
			 
			 ListCtrl.InsertColumn(  i,  &lvcolumn  );		//  insert column
			 
		}

		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CQyVirtualListView::OnInitialUpdate failed."  )  );
		   goto  errLabel;
	}




	//
	int		iW,iH;
	RECT	rect,rc_list;

	GetWindowRect(  &rect  );
	iW  =  rect.right  -  rect.left;
	iH  =  rect.bottom  -  rect.top;

	GetDlgItem(  m_var.iIDC_list  )->GetWindowRect(  &rc_list  );
	m_var.iEdge_list_x  =  (  iW  -  (  rc_list.right  -  rc_list.left  )  )  /  2;
	m_var.iEdge_list_y  =  (  iH  -  (  rc_list.bottom  -  rc_list.top  )  )  /  2;

	sizeDlg(  this  );
	//

	list(  );


	//  SetTimer(  1,  1000,  NULL  );

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		PostMessage(  WM_CLOSE,  0,  0  );
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgListView_db::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	sizeDlg(  this  );
}

void CDlgListView_db::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//  CDialog::OnClose();
	bQuitDlg(  );
}

void CDlgListView_db::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();

	delete  this;
}

void CDlgListView_db::OnLvnColumnclicklist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	int					iSubItem	=	pNMLV->iSubItem;
	TCHAR				buf[1024];
	QY_MC_QUERY		*	pQuery		=	NULL;	
	// TODO: Add your control notification handler code here

	traceLogA(  "OnColumnclick: iItem is %d, iSubItem is %d",  pNMLV->iItem,  pNMLV->iSubItem  );

	if  (  m_docStruct.iDocType  !=  QY_DOCTYPE_MCQUERY  )  goto  errLabel;
	pQuery  =  &m_docStruct.u.query;
	if  (  pNMLV->iItem  !=  -1  )  goto  errLabel;
	if  (  pNMLV->iSubItem  >=  m_docStruct.u.query.nSqlFields  )  goto  errLabel;

	//  没有数据库对应项，也不能排序
	if  (  !m_docStruct.u.query.sqlColumns[iSubItem].label[0]  )  goto  errLabel;

	if  (  m_var.m_nColSelected  ==  iSubItem  )  m_var.bDesc  =  !m_var.bDesc;
	else  {
		m_var.m_nColSelected  =  iSubItem;
		m_var.bDesc  =  FALSE;
	}
	
	_sntprintf(  buf,  sizeof(  buf  )  /  sizeof(  buf[0]  ),  _T(  "%s %s"  ),  pQuery->sqlColumns[iSubItem].label,  m_var.bDesc  ?  _T(  "Desc"  )  :  _T(  "Asc"  )  );
	bSortData(  buf  );
	//  pDoc->UpdateAllViews(  NULL  );
	this->list(  );

errLabel:

	*pResult = 0;
}

void CDlgListView_db::OnNMRClicklist(NMHDR *pNMHDR, LRESULT *pResult)
{
	//  LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	QY_MC			*	pQyMc		=		QY_GET_GBUF(  );
	CListCtrl		&	listCtrl	=		*(  CListCtrl  *  )GetDlgItem(  m_var.iIDC_list  );
	//  CQyMcDoc		*	pDoc		=		GetDocument(  );
	int					iCurItem;
	QY_EVENTINFO		tmpEventInfo;
	
	DWORD  dwPos  =  GetMessagePos(  );

	// Convert the co-ords into a CPoint structure 
	CPoint  point(  GET_X_LPARAM(  dwPos  ),  GET_Y_LPARAM(  dwPos  )  ),  spt;
	spt  =  point;
	
	// Convert to screen co-ords for hittesting 
	listCtrl.ScreenToClient(  &spt  );

	UINT  test;
	iCurItem  =  listCtrl.HitTest(  spt,  &test  );

	memset(  &tmpEventInfo,  0,  sizeof(  tmpEventInfo  )  );
	tmpEventInfo.type  =  CONST_qyEventType_rClick;
	tmpEventInfo.hWnd  =  this->m_hWnd;
	tmpEventInfo.hFrom  =  pNMHDR->hwndFrom;
	tmpEventInfo.bDlg  =  TRUE;
	//  tmpEventInfo.hCtrl  =  listCtrl.m_hWnd;
	tmpEventInfo.click.x  =  point.x;
	tmpEventInfo.click.y  =  point.y;

	// Did the click occur on an item 
	if  (  iCurItem  <  0  ||  !(  test  &  (  TVHT_ONITEM  |  TVHT_ONITEMRIGHT  )  )  )  {		//  2006/04/16, 修改，为使点击列表空白处时能弹出特殊的菜单
		tmpEventInfo.ucbNotSelected  =  TRUE;
		if  (  !m_docStruct.u.query.nSubMenuPos_notSel  )  goto  errLabel;
	}	

	//  2007/08/24, 要考虑一下多选中的情况
	if  (  listCtrl.GetSelectedCount(  )  >  1  )  {
		tmpEventInfo.ucbMultiSelected  =  TRUE;	
		if  (  !m_docStruct.u.query.nSubMenuPos_multiSel  )  goto  errLabel;
	}

#if  0
	if  (  m_docStruct.u.query.pfProcEvent  )  {
		void  *  pDoc  =  NULL;
		m_docStruct.u.query.pfProcEvent(  pQyMc,  pDoc,  &tmpEventInfo  );
	}
#endif
	if  (  m_docStruct.u.query.pfProcEvent_new  )  {
		m_docStruct.u.query.pfProcEvent_new(  pQyMc,  &this->m_docStruct,  &tmpEventInfo  );
	}


errLabel:


	*pResult = 0;
}

 static  int  sGetDisplayStr(  CArray  < void *, void * >  *	 pArrayValue,  int  i,  int  iDataType,  char  *  szValue,  unsigned  int  size  )
{
	 szValue[0]  =  0;
	 switch  (  iDataType  )  {
							
			 case  SQL_BIT:
				   if  (  *( ( BOOL * )(  *pArrayValue  )[i]  )  )	strcpy(  szValue, "TRUE"  );
				   else	 strcpy(  szValue, "FALSE"  );
				   break;
			 case  SQL_TINYINT:
				   sprintf(  szValue, "%c",  *( ( BYTE * )(  *pArrayValue  )[i]  )  );
				   break;
			 case  SQL_SMALLINT:
				   sprintf(  szValue,  "%d",  *( ( int * )(  *pArrayValue  )[i]  )  );
				   break;
			 case  SQL_INTEGER:
				   sprintf(  szValue,  "%d",  *( ( long * )(  *pArrayValue  )[i]  )  );
				   break;
			 case  SQL_REAL:
				   sprintf(  szValue,  "%f",  *( ( float * )(  *pArrayValue  )[i]  )  );
				   break;
			 case  SQL_FLOAT:
			 case  SQL_DOUBLE:
				   sprintf(  szValue,  "%f",  *( ( double * )(  *pArrayValue  )[i]  )  );
				   break;
			 case  SQL_DATE:
			 case  SQL_TIME:
			 case  SQL_TIMESTAMP:
				   sprintf(  szValue,  "%s", ( ( CTime * )(  *pArrayValue  )[i]  )->Format( "%A, %B %d, %Y" )  );
				   break;
			 case  SQL_BINARY:
			 case  SQL_VARBINARY:
				   sprintf(  szValue,  "A binary or varBinary."  );
				   break;
			 case  SQL_DECIMAL:
			 case  SQL_NUMERIC:
			 case  SQL_CHAR:
			 case  SQL_VARCHAR:
				   sprintf(  szValue,  "%s",  *( ( CString * )(  *pArrayValue  )[i]  )  );
				   break;
			 case  SQL_LONGVARCHAR:
			 case  SQL_LONGVARBINARY:
				   sprintf(  szValue,  "A long varChar or longVarBinary."  );
				   break;
			 default:
					 traceLogA(  "Serious error:  CQyVirutalListView::OnGetdispinfo(  ): dataType error."  );
					 break;
	 }
	
	 return  0;
}


LRESULT CDlgListView_db::OnQyComm(  WPARAM wParam,  LPARAM lParam  )
{
	long					lRet				=					-1;
	QY_WMBUF_COMM		*	pComm				=					( QY_WMBUF_COMM * )lParam;
	QY_MC_QUERY			*	pQuery				=					NULL;
	int						i;
	QY_MC				*	pQyMc				=					QY_GET_GBUF(  );

	if  (  !pComm  )  goto  errLabel;

	switch  (  pComm->uiType  )  {
			case  QY_WMPARAM_REFRESHDATA:
				  if  (  m_docStruct.iDocType  ==  CONST_qyDocType_mcQuery  )  {
					  pQuery			=	&m_docStruct.u.query;
					  pQuery->curnItem  =	pComm->u.refreshData.curnRow;
				  }														//  2003/9/5
#if  0
				  GetDocument(  )->bRefreshData( TRUE  );
				  GetDocument(  )->UpdateAllViews(  NULL  );
#endif
				  break;
			case  CONST_qyWmParam_getnCol:
				  pQuery		=	&m_docStruct.u.query;
				  for  (  i  =  0;  pQuery->columns[i].type  !=  -1;  i  ++  )  {
					   if  (  !lstrcmpi(  pQuery->columns[i].label,  CString(  pComm->u.getnCol.colName  )  )  )  break;
				  }
				  if  (  pQuery->columns[i].type  ==  -1  )  goto  errLabel;
				  pComm->u.getnCol.nCol  =  i;
				  break;
			case  CONST_qyWmParam_export:  {
				  CQyRcdset			*	pRecordset  =	(  CQyRcdset  *  )&m_rs;
				  QY_MC_QUERY		*	pQuery		=	&m_docStruct.u.query;
				  QNM_WMBUF_EXPORT	*	pWmExport	=	(  QNM_WMBUF_EXPORT  *  )pComm;
				  char					szValue[QY_MAXPATHLEN + 1];
				  char					buf[1024];
				  int					j			=  0;
				  int					cnt			=  0;
				  CFile					file;
				  char					fileBuf[1024];
				  TCHAR					tBuf[1024];

				  //  取一下文档的标题
				  _sntprintf(  pWmExport->exportInfo.docTitle,  mycountof(  pWmExport->exportInfo.docTitle  ),  _T(  "%s"  ),  m_title  );	//  2006/02/25

				  if  (  !file.Open(  CString(  pWmExport->exportInfo.fileName  ),  CFile::modeCreate | CFile::modeWrite  )  )  goto  errLabel;

				  try		{
					  				  
					  cnt  =  pRecordset->GetRecordCount(  );
					  
					  //  写文件开头
					  switch  (  pWmExport->exportInfo.iFileType  )  {
							  case  CONST_qyFileType_excel:
								    buf[0]  =  (  char  )0xff;  buf[1]  =  (  char  )0xfe;
								    file.Write(  buf,  2  );
									//
								    for  (  j  =  0;  j  <  pQuery->nFields;  j  ++  )  {
										 //  myTChar2Str(  pQuery->columns[j].label,  buf,  sizeof(  buf  )  );
										 //  file.Write(  buf,  strlen(  buf  )  );
										 file.Write(  pQuery->columns[j].label, lstrlen(  pQuery->columns[j].label  )  *  sizeof(   TCHAR  )  ); 
										 file.Write(  _T(  "\t"  ),  1  *  sizeof(  TCHAR  )  );
					  				}
					  				file.Write(  _T(  "\r\n"  ),  2  *  sizeof(  TCHAR  )  );
									file.Write(  _T(  "\r\n"  ),  2  *  sizeof(  TCHAR  )  );
									break;
							  case  CONST_qyFileType_html:
								    _snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<html>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									_snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<HEAD><META http-equiv=Content-Type content=\"text/html; charset=utf-8\"></HEAD>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									_snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<body>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									_snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<table border style='border-collapse:collapse'>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									_snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<tr><th colspan=%d><b>%s</b></th></tr>\r\n",  pQuery->nFields,  myTChar2Utf8(  CString(  m_title  ).GetBuffer(  0  ),  buf,  sizeof(  buf  )  )  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									_snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<tr>"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									for  (  j  =  0;   j  <  pQuery->nFields;  j  ++  )  {
										 _snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<th><b>%s</b></th>",  myTChar2Utf8(  pQuery->columns[j].label,  buf,  sizeof(  buf  )  )  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									}
									_snprintf(  fileBuf,  sizeof(  fileBuf  ),  "</tr>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									break;
							  default:
									  break;
					  }

					  //  文件体
					  for  (  i  =  0;  i  <  cnt;  i  ++  )  {
						   if  (  !i  )	 pRecordset->MoveFirst(  );
						   else  pRecordset->MoveNext(  );
						   if  (  pRecordset->IsEOF(  )  )  break;
						   
						   //  行头
						   switch  (  pWmExport->exportInfo.iFileType  )  {
								   case  CONST_qyFileType_html:
									     _snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<tr>"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
										 break;
								   default:
											break;
						   }

						   //  记录
						   for  (  j  =  0;  j  <  pQuery->nFields;  j  ++  )  {
							    sGetDisplayStr(  &pRecordset->m_arrayValue,  j,  pRecordset->m_nDataType[j],  szValue,  sizeof(  szValue  )  );
								if  (  m_var.data2DisplayProc  )  m_var.data2DisplayProc(  pQyMc,  pQuery,  pRecordset,  j,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
								else  lstrcpyn(  tBuf,  CString(  szValue  ),  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );	//  set item text
								switch  (  pWmExport->exportInfo.iFileType  )  {
										case  CONST_qyFileType_excel:
											  filterStr2Display(  tBuf,  -1  );
											  if  (  tBuf[0]  ==  _T(  '-'  )  )  {	//  2006/09/07, 在excel中-似乎是特殊字符，需要加个空格在前面
												  TCHAR	*	pT  =  _T(  " "  );
												  file.Write(  pT,  lstrlen(  pT  )  *  sizeof(  TCHAR  )  );
											  }
											  file.Write(  tBuf,  lstrlen(  tBuf  )  *  sizeof(  TCHAR  )  );
											  file.Write(  _T(  "\t"  ),  1  *  sizeof(  TCHAR  )  );											  
											  break;
										case  CONST_qyFileType_html:
											  myTChar2Utf8(  tBuf,  buf,  sizeof(  buf  )  );
											  _snprintf(  fileBuf,  sizeof(  buf  ),  "<td>%s</td>",  buf  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
											  break;											  
										default:
												traceLogA(  "rcd[%d][%d] is %s",  i,  j,  buf  );
												break;
								}
								
						   }
						   //  行尾
						   switch  (  pWmExport->exportInfo.iFileType  )  {
								   case  CONST_qyFileType_excel:
									     file.Write(  _T(  "\r\n"  ),  2  *  sizeof(  TCHAR  )  );
										 break;
								   case  CONST_qyFileType_html:
									     _snprintf(  fileBuf,  sizeof(  fileBuf  ),  "</tr>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
										 break;
								   default:
											break;
						   }						   
					  }
				  
					  //  文件尾
					  switch  (  pWmExport->exportInfo.iFileType  )  {
							  case  CONST_qyFileType_html:
								    _snprintf(  fileBuf,  sizeof(  fileBuf  ),  "</table>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									_snprintf(  fileBuf,  sizeof(  fileBuf  ),  "</body>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
								    _snprintf(  fileBuf,  sizeof(  fileBuf  ),  "</html>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									break;
							  default:
										break;
					  }


					}

					catch  (  CException  *  e  )  {
						e->Delete(  );
						qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CQyVirtualListView::OnQyComm failed."  )  );
						goto  errLabel;
					}
	
					file.Close(  );
				   }
				  break;


			default:
					goto  errLabel;
	}

	lRet	=	QY_RC_WMOK;

errLabel:

	return  lRet;

}


void CDlgListView_db::OnNMDblclklist(NMHDR *pNMHDR, LRESULT *pResult)
{
	//  LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	QY_MC		*		pQyMc		=		QY_GET_GBUF(  );
	CListCtrl		&	listCtrl	=		*(  CListCtrl  *  )GetDlgItem(  m_var.iIDC_list  );	//  GetListCtrl(  );
	//  CQyMcDoc		*	pDoc		=		GetDocument(  );
	int					iCurItem;
	QY_EVENTINFO		tmpEventInfo;

	DWORD dwPos = GetMessagePos();

	/* Convert the co-ords into a CPoint structure */
	CPoint point( GET_X_LPARAM( dwPos ), GET_Y_LPARAM( dwPos ) ), spt;
	spt = point;
	
	/* Convert to screen co-ords for hittesting */
	listCtrl.ScreenToClient( &spt );

	UINT test;
	iCurItem = listCtrl.HitTest( spt, &test );
	
	/* Did the click occur on an item */
	if ( iCurItem < 0 || !( test & ( TVHT_ONITEM | TVHT_ONITEMRIGHT ) ) )  goto errLabel;

	memset(  &tmpEventInfo,  0,  sizeof(  tmpEventInfo  )  );
	tmpEventInfo.type  =  CONST_qyEventType_dblClick;
	tmpEventInfo.hWnd  =  this->m_hWnd;
	tmpEventInfo.hFrom  =  pNMHDR->hwndFrom;
	tmpEventInfo.bDlg  =  TRUE;
	tmpEventInfo.click.x  =  point.x;
	tmpEventInfo.click.y  =  point.y;
	tmpEventInfo.uiDefaultCmd  =  m_docStruct.u.query.uiDefaultCmd;

#if  0
	if  (  m_docStruct.u.query.pfProcEvent  )  {
		m_docStruct.u.query.pfProcEvent(  pQyMc,  pDoc,  &tmpEventInfo  );
	}
#endif

	if  (  m_docStruct.u.query.pfProcEvent_new  )  {
		m_docStruct.u.query.pfProcEvent_new(  pQyMc,  &this->m_docStruct,  &tmpEventInfo  );
	}

		
errLabel:	


	*pResult = 0;
}

void CDlgListView_db::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}
