// DlgMessengerIsClient.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qyMc.h"
#include	"myresource.h"
#include	"DlgMessengerIsClient.h"
#include	"qyCusResTemp.h"
#include	"qmcVideoCapture_isCli.h"

//  #include	"DlgProgress.h"
#include	"isCliHelpPublic.h"
#include	"tmpCeLib.h"
#include	"qyOpenShellCommon.h"
#include	"funcsForIsCliHelp.h"
#include	"qmcCommFunc_isCli.h"

 __declspec(  dllexport  )  int  setPasswd_isClient(  HWND  hParent  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int			iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	if  (  pQyMc->iAppType  !=  CONST_qyAppType_client  )  return  -1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	MIS_CNT	*	pMisCnt	=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;

	CDlgMessengerIsClient	dlg(  CWnd::FromHandle(  hParent  )  );

	//  dlg.m_var.iDlgType  =  CONST_qyDlgType_modify;
	dlg.DoModal(  );

	iErr  =  0;

	return  iErr;
}


// CDlgMessengerIsClient dialog

IMPLEMENT_DYNAMIC(CDlgMessengerIsClient, CDialog)

CDlgMessengerIsClient::CDlgMessengerIsClient(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMessengerIsClient::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgMessengerIsClient::~CDlgMessengerIsClient()
{
}

void CDlgMessengerIsClient::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMessengerIsClient, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgMessengerIsClient::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgMessengerIsClient message handlers


BOOL CDlgMessengerIsClient::OnInitDialog()
{
	CDialog::OnInitDialog();

	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	// TODO:  Add extra initialization here
	if  (  !m_var.pMisCnt  )  m_var.pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );	

	QY_MC	*			pQyMc				=	QY_GET_GBUF(  );
	TCHAR				tBuf[255  +  1]		=	_T(  ""  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	SetDlgItemText(  IDC_STATIC_hint1,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_setPassword  )  );

	SetDlgItemText(  IDC_EDIT_name,  pProcInfo->authInfo.messengerName  );

	GetDlgItem(  IDC_EDIT_name  )->EnableWindow(  FALSE  );

	GetDlgItem(  IDC_EDIT_name  )->SendMessage(  EM_SETLIMITTEXT,  MAX_messengerNameLen,  0  );
	GetDlgItem(  IDC_EDIT_passwd0  )->SendMessage(  EM_SETLIMITTEXT,  MAX_messengerPasswdLen,  0  );
	GetDlgItem(  IDC_EDIT_passwd1  )->SendMessage(  EM_SETLIMITTEXT,  MAX_messengerPasswdLen,  0  );


//  errLabel:
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

#if  0
 int  doProgress_toSetPasswd(  void  *  p0,  void  *  pDlgParam,  void  *  pDlgProgressParam  )
{
	//  p0
	CDlgMessengerIsClient  *  pDlg  =  (  CDlgMessengerIsClient  *  )pDlgParam;
	CDlgProgress  *  pDlgProgress  =  (  CDlgProgress  *  )pDlgProgressParam;
	//
	if  (  !pDlg->m_var.pMisCnt  )  return  -1;
	MC_VAR_isCli	*	pProcInfo  =  (  MC_VAR_isCli  *  )pDlg->m_var.pMisCnt->pProcInfoParam;
	
	if  (  !pProcInfo->bInProgress_toSetPasswd  )  {
		pDlgProgress->bQuitDlg(  IDOK  );
		return  1;
	}

	return  0;
}
#endif

void CDlgMessengerIsClient::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	int						iErr									=	-1;
	QY_MC				*	pQyMc									=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp	*	pFuncs									=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	CString					nameStr;
	static  BOOL			bFirstPrompted							=	FALSE;
	CString					passwd0,  passwd1;
	int						idc;

	idc  =  IDC_EDIT_name;
	GetDlgItemText(  idc,  nameStr  );
	MACRO_CStringTrim(  nameStr  );
	if  (  !nameStr.GetLength(  )  )  {
		AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_messengerNameCannotEmpty  )/*_T(  "请输入组名以方便识别"  )*/  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}
	idc  =  IDC_EDIT_passwd0;
	GetDlgItemText(  idc,  passwd0  );
	MACRO_CStringTrim(  passwd0  );
	if  (  !passwd0.GetLength(  )  )  {
		AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_passwdCannotEmpty  )/*_T(  "请输入组名以方便识别"  )*/  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}
	idc  =  IDC_EDIT_passwd1;
	GetDlgItemText(  idc,  passwd1  );
	MACRO_CStringTrim(  passwd1  );
	if  (  !passwd1.GetLength(  )  )  {
		AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_passwdCannotEmpty  )/*_T(  "请输入组名以方便识别"  )*/  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}
	idc  =  IDC_EDIT_passwd0;
	if  (  passwd0  !=  passwd1  )  {
		AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_passwdNotConfirmed  )/*_T(  "请输入组名以方便识别"  )*/  );
		GetDlgItem(  idc  )->SetFocus(  );
		return;
	}

	MACRO_prepareForTran(  );

	{
		CQyMalloc					mallocObj;
		IM_L_STREAM				*	pStream								=	NULL;

		if  (  !(  pStream  =  (  IM_L_STREAM  *  )mallocObj.mallocf(  sizeof(  IM_L_STREAM  )  )  )  )  {
			traceLogA(  "sndDevInfo_qmc . malloc failed."  );  goto  errLabel;
		}

		QY_MESSENGER_ACCOUNT	req;
		unsigned  int		len;
		char				buf[256];

		memset(  &req,  0,  sizeof(  req  )  );
		req.uiType  =  CONST_imCommType_messengerAccount;
		myTChar2Utf8(  passwd0,  buf,  mycountof(  buf  )  );
		len  =  mycountof(  req.messengerPasswd  );
		if  (  !bQyGetStrMd5_x(  buf,  req.messengerPasswd,  &len  )  )  goto  errLabel;

		//  2010/08/14
		pFuncs->pf_startProgress(  &pQyMc->gui.progress,  uiTranNo  );

		//
		MACRO_memset_imLStream(  pStream  );
		pStream->uiType  =  CONST_imCommType_lStream;
		pStream->uiContentType  =  req.uiType;
		len  =  sizeof(  pStream->buf  );
		if  (  messengerAccount2Stream(  pStream->uiContentType,  &req,  pStream->buf,  &len  )  )  goto  errLabel;
		pStream->ulStreamLen  =  len;
		len  +=  offsetof(  IM_L_STREAM,  buf  ); 
		//
		postMsg2Mgr_mc(  m_var.pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_refreshImObjListReq,  tStartTran,  uiTranNo,  0,  (  char  *  )pStream,  len,  NULL,  0,  0,  NULL,  0  ); 
	}

	//  pProcInfo->bInProgress_toSetPasswd  =  TRUE;

	{
#if  0
		CDlgProgress	dlg(  this  );
		dlg.bSetDlgInfo(  _T(  "Please waiting"  ),  NULL,  30,  -1,  uiTranNo  ); 

		//  traceLogA(  "if task is not ready, cancel the task by clear shmCmd, and the subprocess will quit when it read the shmCmd."  );
		if  (  dlg.DoModal(  )  !=  IDOK  )  {
			goto  errLabel;
		}
#endif
		if  (  showProgress(  &pQyMc->gui.progress,  &pQyMc->cusRes,  this->m_hWnd,  _T(  "Please waiting"  ),  NULL,  30,  -1,  uiTranNo  )  !=  IDOK  )  {
			goto  errLabel;
		}

		//
		AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_restart  )  );	 
	}

	traceLogA(  "kk"  );

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		return;
	}

	OnOK();
}
