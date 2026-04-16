// DlgMsgList.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"myresource.h"
#include	"DlgMsgList.h"
#include	"qyCusResTemp.h"

#include	"myDb.h"		//  2013/02/08

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

void  *  displayQnmElement_ts(  void * pVoid,  void  *  pQueryParam,  void  *  pQyRcdset,  int  nSubItem,  TCHAR * output,  unsigned  int  size  );		//  2013/02/08

__declspec(  dllexport  )  int  showDlgMsgList(  HWND  hParent,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int		iRet	=	-1;
	
	CDlgMsgList		dlg(  CWnd::FromHandle(  hParent  )  );
	if  (  pIdInfo  )  {
		dlg.bSetDlgInfo(  misServName,  pIdInfo  );
	}
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	iRet  =  IDOK;
errLabel:
	return  iRet;
}


int  dlgLayout_msgList(  HWND  hDlg,  DLG_guiData_msgList  *  p  )
{
		MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=		QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	G_guiData_qyMc	*  pGuiData   =  pFuncs->pf_get_g_guiData(  );
	cusDlgRes(  0,  pGuiData->pCusRes,  hDlg,  IDD_msgList  );  


#if  1  //  defined(  __WINCE__  )  ||  defined(  __APP_qyMc_touchscreen__  )  
     //  return 0;
	if  (  !p  )  goto  errLabel;

	RECT	rc;
	GetClientRect(  hDlg,  &rc  );
	p->w_org  =  rc.right  -  rc.left;
	p->h_org  =  rc.bottom  -  rc.top;

	if  (  !p->w_org  ||  !p->h_org  )  goto  errLabel;

	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_LIST_msg  ),  &p->rcIDC_LIST_msg  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_LIST_msg,  2  );
		
	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_BUTTON_export  ),  &p->rcIDC_BUTTON_export  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_export,  2  );
	
	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_BUTTON_clear  ),  &p->rcIDC_BUTTON_clear  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_clear,  2  );
	
	GetWindowRect(  GetDlgItem(  hDlg,  p->iIDCANCEL  ),  &p->rcIDCANCEL  );
	MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDCANCEL,  2  );

	int	w, h;

#ifdef  __WINCE__		//  这个移动，其实应该移到dlg_OnInitDialog(  )中去
	HDC hScreenDC=::GetDC(NULL);
	int  maxxScreen = GetDeviceCaps(hScreenDC,HORZRES);
	int  maxyScreen = GetDeviceCaps(hScreenDC,VERTRES);
	::ReleaseDC(NULL,hScreenDC);		


	w  =  maxxScreen;  h  =  maxyScreen;
	MoveWindow(  hDlg,  0,  0,  w,  h,  TRUE  );
#endif

#if  0
	//
	HWND	hList  =  GetDlgItem(  hDlg,  p->iIDC_LIST_msg  );
	if  (  hList  )  {
		//  G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )g_getGuiData(  );
		G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )get_g_guiData(  );
		if  (  pGuiData->hFont_list  )  {
			SendMessage(  hList,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_list,  TRUE  );
		}
	}
#endif

#endif

errLabel:

	return  0;

}

 int  sizeAllControls_dlgMsgList(  HWND  hDlg,  DLG_guiData_msgList  *  p  )
 {
	 if  (  !p->w_org  ||  !p->h_org  )  return  -1;

	 RECT	rc;
	 int	w,  h;

	GetClientRect(  hDlg,  &rc  );
	w  =  rc.right  -  rc.left;
	h  =  rc.bottom  -  rc.top;

	int	idc;
	int  iX,  iY,  iW,  iH;
	float  fx,  fy;
	fx  =  1.  *  w  /  p->w_org;
	fy  =  1.  *  h  /  p->h_org;

	idc  =  p->iIDC_LIST_msg;
	rc  =  p->rcIDC_LIST_msg;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_export;
	rc  =  p->rcIDC_BUTTON_export;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  	
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_clear;
	rc  =  p->rcIDC_BUTTON_clear;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  	
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDCANCEL;
	rc  =  p->rcIDCANCEL;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  	
	MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  


	 return  0;
}


// CDlgMsgList dialog

IMPLEMENT_DYNAMIC(CDlgMsgList, CDialog)

CDlgMsgList::CDlgMsgList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMsgList::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.guiData.iIDC_LIST_msg  =  IDC_LIST_msg;
	m_var.guiData.iIDC_BUTTON_export  =  IDC_BUTTON_export;
	m_var.guiData.iIDC_BUTTON_clear  =  IDC_BUTTON_clear;
	m_var.guiData.iIDCANCEL  =  IDCANCEL;

}

CDlgMsgList::~CDlgMsgList()
{
}


BOOL  CDlgMsgList::bSetDlgInfo(  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	FUNCS_for_isCliHelp		*	pFuncs	=		QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;
	
	m_var.pMisCnt  =  pFuncs->pf_getMisCntByName(  pProcInfo,  misServName  );
	m_var.idInfo.ui64Id  =  pIdInfo->ui64Id;
	return  TRUE;
}



int  CDlgMsgList::listObjs(  )
{
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	QM_dbFuncs  &  g_dbFuncs  =  *pQyMc->p_g_dbFuncs;

	CListCtrl				*	pListCtrl	=	NULL;
	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );
	pListCtrl->DeleteAllItems(  );

	g_dbFuncs.pf_listObjs_dlgMsgList(  m_var.pObjDb->pDb,  &m_var.query,  pListCtrl->m_hWnd,  &m_var.idInfo  );


	 return  0;
}

void CDlgMsgList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMsgList, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_export, &CDlgMsgList::OnBnClickedButtonexport)
	ON_BN_CLICKED(IDC_BUTTON_clear, &CDlgMsgList::OnBnClickedButtonclear)
	ON_BN_CLICKED(IDCANCEL, &CDlgMsgList::OnBnClickedCancel)
	ON_WM_SIZE()
	ON_MESSAGE(  QY_WM_COMM,  OnQyComm  )
END_MESSAGE_MAP()


// CDlgMsgList message handlers

BOOL CDlgMsgList::OnInitDialog()
{
	#ifdef  __APP_qyMc_touchscreen__
			//  2011/03/12
			::SetWindowPos(  m_hWnd,  HWND_TOPMOST,  0,  0,  0,  0,  SWP_NOMOVE  |  SWP_NOSIZE  );
  
			makeDlgResizable(  this->m_hWnd  );
	#endif

	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int							iErr		=	-1;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp		*	pFuncs	=		QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;

	CListCtrl				*	pListCtrl	=	NULL;

	if  (  setModalWnd(  pQyMc,  m_hWnd  )  )  goto  errLabel;

	HWND	hDlg  =  this->m_hWnd;
	dlgLayout_msgList(  hDlg,  &m_var.guiData  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  IDD_msgList  );

	//
	if  (  !m_var.pMisCnt  )  m_var.pMisCnt  =  pFuncs->pf_getMisCntByName(  pProcInfo,  _T(  ""  )  );
	m_var.pObjDb  =  pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );

	//  ÏÂÃæÏÔÊ¾ÅäÖÃÍø¶ÎÁÐ±í
	m_var.idcList  =  IDC_LIST_msg;
	pListCtrl	=	(  CListCtrl  *  )GetDlgItem(  m_var.idcList  );

	//  GetDlgItem(  IDC_DEL  )->EnableWindow(  FALSE  );

	pListCtrl->ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
	pListCtrl->SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );


	TCHAR	wherePart[256]  =  _T(  ""  );
	char	idStr[CONST_qyMessengerIdStrLen  +  1];
	if  (  m_var.idInfo.ui64Id  )  {
		idInfo2Str(  &m_var.idInfo,  idStr,  mycountof(  idStr  )  );
		_sntprintf(  wherePart,  mycountof(  wherePart  ),  _T(  "qyImMsgTab.misServName=%s and (qyImMsgTab.idStr_send='%s' or qyImMsgTab.idStr_recv='%s')"  ),  getDbValStr(  m_var.pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  _T(  ""  )  ),  CString(  idStr  ),  CString(  idStr  )  );
	}
				   
	pFuncs->pf_fillQyMcQuery(  pQyMc,  m_var.pObjDb,  CONST_qyQueryType_imMsgList,  0,  wherePart,  &m_var.query  );

	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  (  m_var.pObjDb->cfg.iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_gpImMsgListQueryStruct_isClient  :  CONST_resId_gpImMsgListQueryStruct_isMgr  );
	m_var.pColumns  =  pQueryStruct->pDisplay;	//  (  QY_COLUMNINFO  *  )getResColumnInfo(  0, &pQyMc->cusRes,  CONST_resId_cfgStandardNameColumns  );
	


	int  i;

	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
	for  (  i  =  0;  m_var.pColumns[i].type  !=  -1;  i  ++  )  {
		   lvc.iSubItem		=	i;
		   lvc.pszText		=	m_var.pColumns[i].label;
		   lvc.cx			=	m_var.pColumns[i].width;
		   lvc.fmt			=	m_var.pColumns[i].fmt;
		   pListCtrl->InsertColumn(  i,  &lvc  );
	}
	m_var.nFields  =  i;
	

#ifdef  __APP_qyMc_touchscreen__
	//  HWND	hDlg	=	this->m_hWnd;
	{
		RECT	rc;
		int		w, h;
		HWND	hFrame	=	pQyMc->gui.hMainWnd;
		if  (  !hFrame  )  goto  errLabel;
		::GetWindowRect(  hFrame,  &rc  );
		w  =  rc.right  -  rc.left;
		h  =  rc.bottom  -  rc.top;
		::MoveWindow(  hDlg,  rc.left,  rc.top,  w,  h,  TRUE  );
		
	}
#endif
	
	//  sizeAllControls_dlgObjs(  hDlg,  &m_var.guiData  );

	//  SetWindowText(  _T(  "Message"  )  );

	//  m_var.guiData.bInited  =  TRUE;


	listObjs(  );

	iErr  =  0;

errLabel:
	
	if  (  iErr  )  {
		PostMessage(  WM_CLOSE,  0,  0  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMsgList::OnBnClickedButtonexport()
{
	// TODO: Add your control notification handler code here
	int					iErr			=	-1;
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	
	FUNCS_for_isCliHelp		*	pFuncs	=		QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	QY_IMEXPORTINFO		imExportInfo;
	CQyString			pathCStr;
	BOOL				bRet;

	memset(  &imExportInfo,  0,  sizeof(  imExportInfo  )  );	
	imExportInfo.pDb  =  pQyMc->gui.pDb;		
	imExportInfo.hCurWnd  =  m_hWnd;		
	
	qyBrowseForFile(  m_hWnd,  FALSE,  NULL,  0,  NULL,  NULL,  NULL,  pQyMc,  pathCStr  );
	if  (  !pathCStr.GetLength(  )  )  goto  errLabel;
	if  (  pathCStr.GetLength(  )  >=  mycountof(  imExportInfo.fileName   )  )  goto  errLabel;
	lstrcpyn(  imExportInfo.fileName,  pathCStr.GetBuffer(  0  ),  mycountof(  imExportInfo.fileName  )  );
	{
		CWaitCursor			cursor;
		bRet  =  pFuncs->pf_bQnmExportCurQuery(  &imExportInfo  );
		//  2006/02/25
	}

	iErr  =  0;
errLabel:
	return;
}



void CDlgMsgList::OnBnClickedButtonclear()
{
	// TODO: Add your control notification handler code here
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	QM_dbFuncs  &  g_dbFuncs  =  *pQyMc->p_g_dbFuncs;

	if  (  myMessageBox(  m_hWnd,  _T(  "Are you sure?"  ),  _T(  "www.qycx.com"  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  return;

	g_dbFuncs.pf_bClearupImMsg_isCli(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  m_var.query.wherePart  );

	listObjs(  );
}

void CDlgMsgList::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CDlgMsgList::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	sizeAllControls_dlgMsgList(  this->m_hWnd,  &m_var.guiData  );

}



 int  dlgMsgList_OnQyComm_export(  QY_OBJ_DB  *  pObjDb,  HWND  hDlg,  int  idcLv,  int  nFields,  QY_COLUMNINFO  *	pColumns,  QNM_WMBUF_EXPORT	*	pWmExport,  LPCTSTR  title  )
{
	int	iErr	=	-1;
	
	int						i;	
	QY_MC				*	pQyMc				=					QY_GET_GBUF(  );

				  char					szValue[QY_MAXPATHLEN + 1];
				  char					buf[1024];
				  int					j			=  0;
				  CFile					file;
				  char					fileBuf[1024];
				  TCHAR					tBuf[1024];
				  CListCtrl		*		pListCtrl		=	(  CListCtrl  *  )CWnd::FromHandle(  GetDlgItem(  hDlg,  idcLv  )  );
				  if  (  !pListCtrl  )  goto  errLabel;
		

				  //  È¡Ò»ÏÂÎÄµµµÄ±êÌâ
				  _sntprintf(  pWmExport->exportInfo.docTitle,  mycountof(  pWmExport->exportInfo.docTitle  ),  _T(  "%s"  ),  title  );	//  2006/02/25

				  if  (  !file.Open(  CString(  pWmExport->exportInfo.fileName  ),  CFile::modeCreate | CFile::modeWrite  )  )  goto  errLabel;

				  try		{
				  				  
					  
					  //  Ð´ÎÄ¼þ¿ªÍ·
					  switch  (  pWmExport->exportInfo.iFileType  )  {
							  case  CONST_qyFileType_excel:
								    buf[0]  =  (  char  )0xff;  buf[1]  =  (  char  )0xfe;
								    file.Write(  buf,  2  );
									//
								    for  (  j  =  0;  j  <  nFields;  j  ++  )  {
										 //  myTChar2Str(  pQuery->columns[j].label,  buf,  sizeof(  buf  )  );
										 //  file.Write(  buf,  strlen(  buf  )  );
										 file.Write(  pColumns[j].label, lstrlen(  pColumns[j].label  )  *  sizeof(   TCHAR  )  ); 
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
									_snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<tr><th colspan=%d><b>%s</b></th></tr>\r\n",  nFields,  myTChar2Utf8(  title,  buf,  sizeof(  buf  )  )  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									_snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<tr>"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									for  (  j  =  0;   j  <  nFields;  j  ++  )  {
										 _snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<th><b>%s</b></th>",  myTChar2Utf8(  pColumns[j].label,  buf,  sizeof(  buf  )  )  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									}
									_snprintf(  fileBuf,  sizeof(  fileBuf  ),  "</tr>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									break;
							  default:
									  break;
					  }

					  //  ÎÄ¼þÌå
					  int  cnt  =  pListCtrl->GetItemCount(  );
					  for  (  i  =  0;  i  <  cnt;  i  ++  )  
					  {
						   
						   //  ÐÐÍ·
						   switch  (  pWmExport->exportInfo.iFileType  )  {
								   case  CONST_qyFileType_html:
									     _snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<tr>"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
										 break;
								   default:
											break;
						   }

						   //  
						   for  (  j  =  0;  j  <  nFields;  j  ++  )  {
								
							   //  displayQnmElement_ts(  pQyMc,  pQuery,  pRecordset,  j,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
							   pListCtrl->GetItemText(  i,  j,  tBuf,  mycountof(  tBuf  )  );
							   

								switch  (  pWmExport->exportInfo.iFileType  )  {
										case  CONST_qyFileType_excel:
											  filterStr2Display(  tBuf,  -1  );
											  if  (  tBuf[0]  ==  _T(  '-'  )  )  {	//  2006/09/07, ÔÚexcelÖÐ-ËÆºõÊÇÌØÊâ×Ö·û£¬ÐèÒª¼Ó¸ö¿Õ¸ñÔÚÇ°Ãæ
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
						   //  ÐÐÎ²
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
				  
					  //  ÎÄ¼þÎ²
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
				   
					iErr  =  0;
errLabel:
					return  iErr;
}

 LRESULT CDlgMsgList::OnQyComm(  WPARAM wParam,  LPARAM lParam  )
{
	long					lRet				=					-1;
	QY_WMBUF_COMM		*	pComm				=					( QY_WMBUF_COMM * )lParam;
	QY_MC_QUERY			*	pQuery				=					NULL;
	int						i;
	QY_MC				*	pQyMc				=					QY_GET_GBUF(  );

	if  (  !pComm  )  goto  errLabel;

	switch  (  pComm->uiType  )  {
			case  CONST_qyWmParam_export:  
				  dlgMsgList_OnQyComm_export(  m_var.pObjDb,  m_hWnd,  m_var.idcList,  m_var.nFields,  m_var.pColumns,  (  QNM_WMBUF_EXPORT  *  )pComm,  m_var.pMisCnt->talkerDesc  );
				  break;
			default:
					goto  errLabel;
	}

	lRet	=	QY_RC_WMOK;

errLabel:
	return  lRet;

}
