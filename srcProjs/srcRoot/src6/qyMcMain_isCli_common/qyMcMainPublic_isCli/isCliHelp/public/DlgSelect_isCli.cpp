// DlgSelect.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qymc.h"
#include	"myresource.h"
#include	"DlgSelect_isCli.h"
#include	"qyCusResTemp.h"
#include	"myDb.h"

#include	"qmcVWall.h"
//#include	"qmshell_open.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


__declspec(  dllexport  )  int  showDlgSelect_isCli(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  int  iSelectType,  int  iObjType,  LPCTSTR  hint,  void  *  p0,  void  *  p1,  void  *  pU  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int		iRet	=	-1;
	
	DlgSelect_isCli_o_U  *  pO_U  =  (  DlgSelect_isCli_o_U  *  )pU;

	CDlgSelect_isCli	dlg(  CWnd::FromHandle(  hParent  )  );
	if  (  !dlg.bSetDlgInfo(  pObjDb,  iSelectType,  iObjType,  hint,  p0,  p1  )  )  goto  errLabel; 
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	memcpy(  pO_U,  &dlg.m_var.u,  sizeof(  DlgSelect_isCli_o_U  )  );


	iRet  =  IDOK;

errLabel:
	return  iRet;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgSelect_isCli dialog


CDlgSelect_isCli::CDlgSelect_isCli(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelect_isCli::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSelect_isCli)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );

}

 BOOL  CDlgSelect_isCli::bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  int  iSelectType,  int  iObjType,  LPCTSTR  hint,  void  *  p0,  void  *  p1  )
{
	BOOL	bRet	=	FALSE;

	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp		*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;

	//
	m_var.pObjDb  =  pObjDb;
	m_var.iSelectType  =  iSelectType;
	m_var.iObjType  =  iObjType;
	if  (  hint  )  lstrcpyn(  m_var.hint,  hint,  mycountof(  m_var.hint  )  );

	switch  (  iSelectType  )  {
			case  CONST_qyQueryType_sharedDynBmpList:
				  bRet  =  TRUE;  goto  errLabel;
				  break;
			case  CONST_qyQueryType_imGrpMemList:
				  if  (  p0  )  lstrcpyn(  m_var.u.selectMessenger.misServName,  (  LPCTSTR  )p0,  mycountof(  m_var.u.selectMessenger.misServName  )  );
				  if  (  !p1  )  goto  errLabel;
				  memcpy(  &m_var.inputU.selectImGrpMem.idInfo_grp,  p1,  sizeof(  m_var.inputU.selectImGrpMem.idInfo_grp  )  );
				  bRet  =  TRUE;  goto  errLabel;
				  break;
			default:
					break;
	}

	switch  (  iObjType  )  {
			case  CONST_objType_messenger:  {
				  if  (  p0  )  lstrcpyn(  m_var.u.selectMessenger.misServName,  (  LPCTSTR  )p0,  mycountof(  m_var.u.selectMessenger.misServName  )  );
				  }
				  break;
			case  CONST_objType_imGrp:
				  if  (  p0  )  lstrcpyn(  m_var.u.selectImGrp.misServName,  (  LPCTSTR  )p0,  mycountof(  m_var.u.selectImGrp.misServName  )  );
				  break;
			case  CONST_objType_toPath:  {
				  QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
				  QY_SERVICEGUI_INFO	*	pSci  =  getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
				  if  (  !pSci  )  goto  errLabel;
				  //
				  if  (  p0  )  lstrcpyn(  m_var.u.selectToPath.misServName,  (  LPCTSTR  )p0,  mycountof(  m_var.u.selectToPath.misServName  )  );
				  m_var.u.selectToPath.bPhoneGuest  =  (  BOOL  )p1;
				  //
				  if  (  !(  m_var.u.selectToPath.pProcInfo  =  (  MC_VAR_isCli  *  )pSci->pVar  )  )  goto  errLabel;
				  if  (  !(  m_var.u.selectToPath.pMisCnt  =  pFuncs->pf_getMisCntByName(  pProcInfo,  m_var.u.selectToPath.misServName  )  )  )  goto  errLabel;
				  }
				  break;
			default:
					break;
	}

	bRet  =  TRUE;
errLabel:
	return  bRet;
}

void CDlgSelect_isCli::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelect_isCli)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelect_isCli, CDialog)
	//{{AFX_MSG_MAP(CDlgSelect_isCli)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSelect_isCli message handlers

BOOL CDlgSelect_isCli::OnInitDialog()
{
	CDialog::OnInitDialog();
	int			iErr								=	-1;
	QY_MC	*	pQyMc								=	QY_GET_GBUF(  );
	QM_dbFuncs  &  g_dbFuncs						=  *pQyMc->p_g_dbFuncs;
	TCHAR		sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	TCHAR		tBuf[255  +  1]						=	_T(  ""  );
	HWND		hDlg;
	int			i;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	SetWindowText(  m_var.hint  );

	hDlg  =  GetDlgItem(  IDC_COMBO_objList  )->m_hWnd;

	switch  (  m_var.iSelectType  )  {
			case  CONST_qyQueryType_sharedDynBmpList:
#if  0
				  if  (  g_dbFuncs.pf_iSelectImObjAuth_dlgSelect_isCli(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_misServName,  m_var.u.selectImGrp.misServName  ),  hDlg,  varVals,  mycountof(  varVals  )  )  <  0  )  goto  errLabel;
#endif
				  iErr  =  0;  goto  errLabel;
				  break;
			case  CONST_qyQueryType_imGrpMemList:

				  if  (  g_dbFuncs.pf_iSelectImGrpMem_dlgSelect_isCli(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_misServName,  m_var.misServName  ),  &m_var.inputU.selectImGrpMem.idInfo_grp,  hDlg  )  <  0  )  goto  errLabel;
				  iErr  =  0;  goto  errLabel;
				  break;
			default:
					break;
	}				  

	// TODO:  在此添加额外的初始化
	switch  (  m_var.iObjType  )  {
		    case  CONST_objType_messenger:
				  
				  if  (  g_dbFuncs.pf_iSelectImObj_dlgSelect_isCli(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_misServName,  m_var.u.selectImGrp.misServName  ),  hDlg  )  <  0  )  goto  errLabel;

				  break;
			case  CONST_objType_imGrp:
#if  0
				  if  (  g_dbFuncs.pf_iSelectImObjAuth2_dlgSelect_isCli(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_misServName,  m_var.u.selectImGrp.misServName  ),  hDlg  )  <  0  )  goto  errLabel;
#endif
				  break;
			case  CONST_objType_toPath:  {
				  MIS_CNT	*	pMisCnt  =  m_var.u.selectToPath.pMisCnt;
				  if  (  !pMisCnt  )  goto  errLabel;

				  for  (  i  =  0;  i  <  pMisCnt->toPaths.usCnt;  i  ++  )  {
					   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s://%s/%I64u/%s - %s"  ),  CONST_str_im,  m_var.u.selectToPath.misServName,  pMisCnt->toPaths.mems[i].idInfo_vDev.ui64Id,  pMisCnt->toPaths.mems[i].wDevIdStr,  pMisCnt->toPaths.mems[i].cusName  );
					  ::SendMessage(  GetDlgItem(  IDC_COMBO_objList  )->m_hWnd,  CB_ADDSTRING,  0,  (  LPARAM  )sqlBuf  );
				  }
				  //
#if  0
				  if  (  m_var.u.selectToPath.pProcInfo->bPhoneModuleLoaded  &&  m_var.u.selectToPath.bPhoneGuest  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_localToPaths  )  );
					  (  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_objList  )  )->InsertString(  -1,  tBuf  );
				  }
#endif
				  //
				  }				  
				  break;
			case  CONST_objType_webcam:
			case  CONST_objType_screen:

				  if  (  g_dbFuncs.pf_iSelectDynBmp_dlgSelect_isCli(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  0,  hDlg  )  <  0  )  goto  errLabel;

				  break;
			default:
					break;
	}

	iErr  =  0;

errLabel:

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgSelect_isCli::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	QY_MC	*	pQyMc				=	QY_GET_GBUF(  );
	TCHAR		tBuf[255  +  1]		=	_T(  ""  );
	TCHAR	*	pT;
	TCHAR	*	pT1;
	char		buf[255  +  1]		=	"";

	GetDlgItemText(  IDC_COMBO_objList,  tBuf,  mycountof(  tBuf  )  );
	tTrim(  tBuf  );
	if  (  !tBuf[0]  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_needToSelect  )  );  return;
	}

	switch  (  m_var.iObjType  )  {
			case  CONST_objType_messenger:
				  if  (  !(  pT  =  _tcschr(  tBuf,  _T(  '-'  )  )  )  )  goto  errLabel;
				  *pT  =  0;
				  tTrim(  tBuf  );
				  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
				  idStr2Info(  buf,  &m_var.u.selectMessenger.idInfo_selected  );				  				  
				  break;
			case  CONST_objType_imGrp:
				  if  (  !(  pT  =  _tcschr(  tBuf,  _T(  '-'  )  )  )  )  goto  errLabel;
				  *pT  =  0;
				  tTrim(  tBuf  );
				  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
				  idStr2Info(  buf,  &m_var.u.selectImGrp.idInfo_selected  );				  
				  break;
			case  CONST_objType_toPath:
				  if  (  !_tcsicmp(  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_localToPaths  )  )  )  {
					  _sntprintf(  m_var.u.selectToPath.toPath,  mycountof(  m_var.u.selectToPath.toPath  ),  _T(  "%s:///0/"  ),  CONST_str_im  );
					  }
				  else  {
					    if  (  !(  pT  =  _tcschr(  tBuf,  _T(  '-'  )  )  )  )  goto  errLabel;
						*pT  =  0;
						tTrim(  tBuf  );
						//
						safeWcsnCpy(  tBuf,  m_var.u.selectToPath.toPath,  mycountof(  m_var.u.selectToPath.toPath  )  );
				  }
				  //
				  break;
			case  CONST_objType_webcam:
			case  CONST_objType_screen:
				  if  (  !(  pT  =  _tcschr(  tBuf,  _T(  '-'  )  )  )  )  goto  errLabel;
				  *pT  =  0;
				  tTrim(  tBuf  );
				  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
				  idStr2Info(  buf,  &m_var.u.selectDynBmp.dynBmp.qisResObj.idInfo  );				  
				  pT  ++  ;
				  if  (  !(  pT1  =  _tcsrchr(  pT,  _T(  ','  )  )  )  )  goto  errLabel;
				  *pT1  =  0;
				  pT1  ++  ;  tTrim(  pT1  );
				  m_var.u.selectDynBmp.dynBmp.qisResObj.resObj.usIndex_obj  =  (  unsigned  short  )_ttol(  pT1  );
				  if  (  !(  pT1  =  _tcsrchr(  pT,  _T(  ','  )  )  )  )  goto  errLabel;
				  *pT1  =  0;
				  pT1  ++  ;  tTrim(  pT1  );
				  m_var.u.selectDynBmp.dynBmp.qisResObj.resObj.uiObjType  =  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),  pT1  );
				  break;
			default:
					break;
	}



errLabel:
	CDialog::OnOK();
}

void CDlgSelect_isCli::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
