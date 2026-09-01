// DlgPropImMsg.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qymc.h"
#include	"myresource.h"
#include	"DlgPropImMsg.h"
#include ".\dlgpropimmsg.h"
#include	"qyCusResTemp.h"

#include	"myDb.h"

#include	"ctxQmc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

__declspec(  dllexport  )  int  showDlgPropImMsg(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  int  id  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int		iRet	=	-1;

	//
	CDlgPropImMsg					dlg(  CWnd::FromHandle(  hParent  )  );	
	if  (  !dlg.bSetDlgInfo(  pObjDb,  id  )  )  goto  errLabel;
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	iRet  =  IDOK;

errLabel:
	return  iRet;
}


/////////////////////////////////////////////////////////////////////////////
// CDlgPropImMsg dialog


CDlgPropImMsg::CDlgPropImMsg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPropImMsg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPropImMsg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}



BOOL  CDlgPropImMsg::bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  int  id  )
{
	m_var.pObjDb  =  pObjDb;
	m_var.id  =  id;
	return  TRUE;
}


void CDlgPropImMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPropImMsg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPropImMsg, CDialog)
	//{{AFX_MSG_MAP(CDlgPropImMsg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPropImMsg message handlers

BOOL CDlgPropImMsg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int				iErr		=		-1;	
	QY_MC		*	pQyMc		=		QY_GET_GBUF(  );
	IM_MSG_RCD		rcd;
	TCHAR			tBuf[256]	=		_T(  ""  );
	char			buf[256]	=		"";
	char			buf1[256]	=		"";
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	
	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  goto  errLabel;

	if  (  !g_dbFuncs.pf_bGetImMsgRcdBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  m_var.id,  &rcd  )  )  {
		memset(  &rcd,  0,  sizeof(  rcd  )  );
	}

	SetDlgItemText(  IDC_STATIC_type,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_message  )  );  
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  rcd.idInfo_send.ui64Id  );
	SetDlgItemText(  IDC_STATIC_idInfo_send,  CString(  tBuf  )  );
	SetDlgItemText(  IDC_STATIC_senderDesc,  rcd.senderDesc  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  rcd.idInfo_recv.ui64Id  );
	SetDlgItemText(  IDC_STATIC_idInfo_recv,  CString(  tBuf  )  );
	SetDlgItemText(  IDC_STATIC_receiverDesc,  rcd.receiverDesc  );
	//
	getTimeStr(  rcd.tSendTime,  buf,  mycountof(  buf  )  );
	qyDisplayTime(  buf,  buf1,  mycountof(  buf1  )  );  
	SetDlgItemText(  IDC_STATIC_sendTime,  CString(  buf1  )  );
	getTimeStr(  (  time_t  )rcd.tRecvTime,  buf,  mycountof(  buf  )  );
	qyDisplayTime(  buf,  buf1,  mycountof(  buf1  )  );  
	SetDlgItemText(  IDC_STATIC_recvTime,  CString(  buf1  )  );

	GetDlgItem(  IDC_STATIC_staticRecvTime  )->ShowWindow(  SW_HIDE  );
	GetDlgItem(  IDC_STATIC_recvTime  )->ShowWindow(  SW_HIDE  );

	//
	if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  SetDlgItemText(  IDC_EDIT_content,  rcd.content  );
	else  SetDlgItemText(  IDC_EDIT_content,  rcd.content  );

	
errLabel:


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgPropImMsg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
