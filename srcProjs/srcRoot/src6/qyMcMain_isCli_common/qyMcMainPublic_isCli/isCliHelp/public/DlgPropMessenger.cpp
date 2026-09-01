// DlgPropMessenger.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qymc.h"
#include	"myresource.h"
#include	"DlgPropMessenger.h"
#include	"myDb.h"
#include	"ctxQmc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


__declspec(  dllexport  )  int  showDlgPropMessenger(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  int  iObjType,  QY_MESSENGER_ID  *  pIdInfo  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int		iRet	=	-1;

	//
	CDlgPropMessenger					dlg(  CWnd::FromHandle(  hParent  )  );	
	if  (  !dlg.bSetDlgInfo(  pObjDb,  misServName,  iObjType,  pIdInfo  )  )  goto  errLabel;
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	iRet  =  IDOK;

errLabel:
	return  iRet;
}

__declspec(  dllexport  )  int  showDlgPropMessenger(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  MSGR_ADDR  *  pAddr  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int		iRet	=	-1;

	//
	CDlgPropMessenger					dlg(  CWnd::FromHandle(  hParent  )  );	
	if  (  !dlg.bSetDlgInfo(  pObjDb,  pAddr  )  )  goto  errLabel;
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	iRet  =  IDOK;

errLabel:
	return  iRet;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgPropMessenger dialog

//	extern  QY_IDCITEM	 CONST_pcPropertiesTable0[];
int  setPcPropertiesLayout(  QNM_CUSTOM_COMM  *  pCustom,  QY_IDCITEM  *  pTable0  );
void  qisSizePcPropertiesControls(  QNM_CUSRES_INFO  *  pCusRes,  HWND  hDlg,  QY_MESSENGER_REGINFO  *  pRegInfo  );



CDlgPropMessenger::CDlgPropMessenger(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPropMessenger::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPropMessenger)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgPropMessenger::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPropMessenger)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPropMessenger, CDialog)
	//{{AFX_MSG_MAP(CDlgPropMessenger)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL  CDlgPropMessenger::bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  int  iObjType,  QY_MESSENGER_ID  *  pIdInfo  )
{
	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	if  (  !bMessengerIdValid(  pIdInfo  )  )  return  FALSE;
	
	m_var.pObjDb  =  pObjDb;
	m_var.iObjType  =  iObjType;

	lstrcpyn(  m_var.u.messenger.addr.misServName,  misServName,  mycountof(  m_var.u.messenger.addr.misServName  )  );
	m_var.u.messenger.addr.idInfo.ui64Id  =  pIdInfo->ui64Id;

	return  TRUE;

}


 BOOL  CDlgPropMessenger::bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  MSGR_ADDR  *  pAddr  )
{
	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	if  (  !pAddr  )  return  FALSE;

	m_var.pObjDb  =  pObjDb;
	m_var.iObjType  =  pAddr->uiObjType;
	memcpy(  &m_var.u.messenger.addr,  pAddr,  sizeof(  m_var.u.messenger.addr  )  );

	return  TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CDlgPropMessenger message handlers

 BOOL CDlgPropMessenger::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	int				iErr				=		-1;	
	QY_MC		*	pQyMc				=		QY_GET_GBUF(  );
	TCHAR			tBuf[255  +  1]		=		_T(  ""  );
	char			buf[256]			=		"";
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;
	
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	
	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  goto  errLabel;

	setPcPropertiesLayout(  &pQyMc->cfg.custom,  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_pcPropertiesTable0  )  );

	switch  (  m_var.iObjType  )  {
			case  CONST_objType_phoneGuest:
				  if  (  !g_dbFuncs.pf_bGetImOtherRegInfoBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImOtherRegInfoTab,  &m_var.u.messenger.addr,  0,  &m_var.u.messenger.regInfo  )  )  memset(  &m_var.u.messenger.regInfo,  0,  sizeof(  m_var.u.messenger.regInfo  )  );
				  break;
			default:
					if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDbFuncs,  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  m_var.u.messenger.addr.misServName,  &m_var.u.messenger.addr.idInfo,  0,  &m_var.u.messenger.info, NULL,  NULL,  NULL  )  )  memset(  &m_var.u.messenger.info,  0,  sizeof(  m_var.u.messenger.info  )  );
					if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  m_var.u.messenger.addr.misServName,  &m_var.u.messenger.addr.idInfo,  0,  &m_var.u.messenger.regInfo  )  )  memset(  &m_var.u.messenger.regInfo,  0,  sizeof(  m_var.u.messenger.regInfo  )  );
					break;
	}
	
	MY_REG_DESC  desc;
	regInfo2Desc(  0,  &m_var.u.messenger.regInfo,  &desc,  0,  0,  0,  0  );
	qisSizePcPropertiesControls(  &pQyMc->cusRes,  this->m_hWnd,  &m_var.u.messenger.regInfo  );

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  m_var.u.messenger.addr.idInfo.ui64Id  );
	SetDlgItemText(  IDC_STATIC_messengerId,  tBuf  );  
				   //  SetDlgItemText(  IDC_pcName,  CString(  m_var.u.messenger.info.pcName  )  );
				   //  SetDlgItemText(  IDC_IP,  CString(  m_var.u.messenger.info.ip  )  );
				   /*
				   SetDlgItemText(  IDC_mac0,  CString(  m_var.u.pc.info.macs[0]  )  );	SetDlgItemText(  IDC_ip0,  CString(  bulIpValid(  inet_addr(  m_var.u.pc.info.ips[0]  )  )  ?  m_var.u.pc.info.ips[0]  :  ""  )  );
				   SetDlgItemText(  IDC_mac1,  CString(  m_var.u.pc.info.macs[1]  )  );	SetDlgItemText(  IDC_ip1,  CString(  bulIpValid(  inet_addr(  m_var.u.pc.info.ips[1]  )  )  ?  m_var.u.pc.info.ips[1]  :  ""  )  );
				   SetDlgItemText(  IDC_mac2,  CString(  m_var.u.pc.info.macs[2]  )  );	SetDlgItemText(  IDC_ip2,  CString(  bulIpValid(  inet_addr(  m_var.u.pc.info.ips[2]  )  )  ?  m_var.u.pc.info.ips[2]  :  ""  )  );
				   SetDlgItemText(  IDC_osName,  CString(  m_var.u.pc.info.osName  )  );
				   SetDlgItemText(  IDC_servicePack,  CString(  m_var.u.pc.info.servicePack  )  );
				   SetDlgItemText(  IDC_curUsrName,  CString(  m_var.u.pc.info.curUsrName  )  );
				   SetDlgItemText(  IDC_proxyServer,  CString(  m_var.u.pc.info.proxyServer  )  );
				   if  (  !qyDisplayTime(  m_var.u.pc.info.startTime,  buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
				   SetDlgItemText(  IDC_STARTTIME,  CString(  buf  )  );
				   if  (  !qyDisplayTime(  m_var.u.pc.info.lastCommTime,  buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
				   SetDlgItemText(  IDC_lastCommTime,  CString(  buf  )  );
				   if  (  !qyDisplayTime(  m_var.u.pc.regInfo.auditTime,  buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
				   SetDlgItemText(  IDC_auditTime,  CString(  buf  )  );
				   if  (  !qyDisplayTime(  m_var.u.pc.regInfo.regTime,  buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
				   SetDlgItemText(  IDC_regTime,  CString(  buf  )  );
				   SetDlgItemText(  IDC_qwmVer,  CString(  m_var.u.pc.info.qwmVer  )  );
				   */

    switch  (  m_var.iObjType  )  {
			case  CONST_objType_phoneGuest:
				  QY_IDCITEM  *  pItem;
				  for  (  pItem  =  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_pcPropertiesTable0  );  pItem->idc  !=  -1;  pItem  ++  )  {
					  if  (  pItem->uiFieldId  !=  CONST_fieldId_jqlx  )  continue;
					  if  (  pItem->idc  !=  -1  )  {
						  CWnd  *  pCtrl  =  NULL;
						  if  (  (  pCtrl  =  GetDlgItem(  pItem->lIdc  )  )  )  pCtrl->ShowWindow(  SW_HIDE  );
						  if  (  (  pCtrl  =  GetDlgItem(  pItem->idc  )  )  )  pCtrl->ShowWindow(  SW_HIDE  );
					  }
				  }
				  break;
			default:
					break;
	}



	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		EndDialog(  FALSE  );
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


