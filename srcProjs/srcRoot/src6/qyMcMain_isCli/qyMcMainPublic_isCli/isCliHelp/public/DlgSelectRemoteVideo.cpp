// DlgSelectRemoteVideo.cpp : implementation file
//

#include "stdafx.h"
#include	"qyMcMainCommon.h"
#include	"myresource.h"
#include "DlgSelectRemoteVideo.h"
#include "afxdialogex.h"

#include	"qmShellPublic.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"


__declspec(  dllexport  )  int  showDlgSelect_remoteVideo(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  int  iSelectType,  int  iObjType,  LPCTSTR  hint,  void  *  p0,  void  *  p1,  void  *  pU  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int		iRet	=	-1;
	
	DlgSelect_isCli_o_U  *  pO_U  =  (  DlgSelect_isCli_o_U  *  )pU;

	CDlgSelectRemoteVideo	dlg(  CWnd::FromHandle(  hParent  )  );
	if  (  !dlg.bSetDlgInfo(  pObjDb,  iSelectType,  iObjType,  hint,  p0,  p1  )  )  goto  errLabel; 
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	memcpy(  pO_U,  &dlg.m_var.u,  sizeof(  DlgSelect_isCli_o_U  )  );


	iRet  =  IDOK;

errLabel:
	return  iRet;
}

// CDlgSelectRemoteVideo dialog

IMPLEMENT_DYNAMIC(CDlgSelectRemoteVideo, CDialogEx)

CDlgSelectRemoteVideo::CDlgSelectRemoteVideo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSelectRemoteVideo::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

 BOOL  CDlgSelectRemoteVideo::bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  int  iSelectType,  int  iObjType,  LPCTSTR  hint,  void  *  p0,  void  *  p1  )
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

	switch  (  iObjType  )  {
			case  CONST_objType_messenger:  {
				  if  (  p0  )  lstrcpyn(  m_var.u.selectMessenger.misServName,  (  LPCTSTR  )p0,  mycountof(  m_var.u.selectMessenger.misServName  )  );
				  }
				  break;
			default:
					break;
	}


	bRet  =  TRUE;
errLabel:
	return  bRet;
}


CDlgSelectRemoteVideo::~CDlgSelectRemoteVideo()
{
}

void CDlgSelectRemoteVideo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSelectRemoteVideo, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgSelectRemoteVideo::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSelectRemoteVideo message handlers

BOOL CDlgSelectRemoteVideo::OnInitDialog()
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


	switch  (  m_var.iObjType  )  {
		    case  CONST_objType_messenger:
				  
				  if  (  g_dbFuncs.pf_iSelectImObj_dlgSelect_isCli(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_misServName,  m_var.u.selectImGrp.misServName  ),  hDlg  )  <  0  )  goto  errLabel;

				  break;
			case  CONST_objType_webcam:
			case  CONST_objType_screen:
			case  CONST_objType_rtspStream:

				  if  (  g_dbFuncs.pf_iSelectDynBmp_dlgSelect_isCli(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  0,  hDlg  )  <  0  )  goto  errLabel;

				  break;
			default:
					break;
	}

	//
	QY_DMITEM	*	pTable	=	getResTable(  0,  &pQyMc->cusRes,  CONST_resId_dynBmpTypeTable  );
	QY_DMITEM	*	pItem;
	CComboBox	*	pCombo;

	pCombo	=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_remoteVideo_type  );
	for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  {
		 pCombo->InsertString(  -1,  pItem->des  );
	}
	m_var.iSelectType  =  CONST_objType_webcam;
	pCombo->SelectString(  -1,  qyGetDesByType1(  pTable,  m_var.iSelectType  )  );

	//
	if  (  !bSupported_remoteStorage(  pQyMc  )  )  {
		int  idc  =  IDC_CHECK_ucbSaveVideo;
		::EnableWindow(  ::GetDlgItem(  m_hWnd,  idc  ),  FALSE  );
	}

	//
	iErr  =  0;

errLabel:

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgSelectRemoteVideo::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
	CDlgSelectRemoteVideo::OnOK(  );
}

void CDlgSelectRemoteVideo::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	int				idc;
	int				iIndex;
	TCHAR			tBuf[128]	=  _T(  ""  );
	char			buf[128]	=  "";
	CString			str;
	TCHAR		*	pT;
	TCHAR		*	pT1;
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	QY_DMITEM	*	pTable		=	getResTable(  0,  &pQyMc->cusRes,  CONST_resId_dynBmpTypeTable  );

	DlgSelect_isCli_o_U		curU;

	memset(  &curU.selectDynBmp,  0,  sizeof(  curU.selectDynBmp  )  );

	idc  =  IDC_EDIT_remoteVideo_index;
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );
	curU.selectDynBmp.dynBmp.qisResObj.resObj.usIndex_obj  =  _ttol(  tBuf  );

	idc  =  IDC_COMBO_remoteVideo_type;
	GetDlgItemText(  idc,  str  );
	curU.selectDynBmp.dynBmp.qisResObj.resObj.uiObjType  =  qyGetTypeByDes(  pTable,  str  );

	idc  =  IDC_COMBO_objList;
	GetDlgItemText(  idc,  tBuf,  mycountof(  tBuf  )  );
	tTrim(  tBuf  );
	if  (  !tBuf[0]  )  return;
	if  (  !(  pT  =  _tcschr(  tBuf,  _T(  '-'  )  )  )  )  goto  errLabel;
	*pT  =  0;	
	tTrim(  tBuf  );				
	myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );				  
	idStr2Info(  buf,  &curU.selectDynBmp.dynBmp.qisResObj.idInfo  );

	//  2014/08/03
	idc			=  IDC_CHECK_ucbSaveVideo;
	if  (  (  (  CButton  *  )GetDlgItem(  idc  )  )->GetCheck(  )  ==  BST_CHECKED  )  curU.selectDynBmp.ucbSaveVideo  =  TRUE;
	
	//
	if  (  memcmp(  &m_var.u.selectDynBmp,  &curU.selectDynBmp,  sizeof(  m_var.u.selectDynBmp  )  )  ){
		memcpy(  &m_var.u.selectDynBmp,  &curU.selectDynBmp,  sizeof(  m_var.u.selectDynBmp  )  );
	}


errLabel:

	CDialogEx::OnOK();
}
