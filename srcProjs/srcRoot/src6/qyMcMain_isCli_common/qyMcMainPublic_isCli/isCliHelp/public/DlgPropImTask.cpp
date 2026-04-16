// DlgPropImTask.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qymc.h"
#include	"myresource.h"
#include	"DlgPropImTask.h"
#include	"myDb.h"
#include	"ctxQmc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

__declspec(  dllexport  )  int  showDlgPropImTask(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  BOOL  bHisTab,  int  id  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int  iRet  =  -1;
	
	CDlgPropImTask		dlg;
	if  (  !dlg.bSetDlgInfo(  pObjDb,  bHisTab,  id  )  )  goto  errLabel;
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	iRet  =  IDOK;


errLabel:
	return  iRet;
}
/////////////////////////////////////////////////////////////////////////////
// CDlgPropImTask dialog


CDlgPropImTask::CDlgPropImTask(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPropImTask::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPropImTask)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgPropImTask::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPropImTask)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPropImTask, CDialog)
	//{{AFX_MSG_MAP(CDlgPropImTask)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPropImTask message handlers

 BOOL  CDlgPropImTask::bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  BOOL  bHisTab,  int  id  )
{
	this->m_var.pObjDb  =  pObjDb;
	m_var.bHisTab  =  bHisTab;
	m_var.id  =  id;

	return  TRUE;
}


BOOL CDlgPropImTask::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int				iErr		=		-1;	
	QY_MC		*	pQyMc		=		QY_GET_GBUF(  );
	IM_TASK_RCD		rcd;
	TCHAR			tBuf[256]	=		_T(  ""  );
	char			buf[256]	=		"";
	char			buf1[256]	=		"";

	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );
	
	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  goto  errLabel;

	if  (  !g_dbFuncs.pf_bGetImTaskRcdBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  m_var.bHisTab,  NULL,  0,  0,  0,  m_var.id,  &rcd  )  )  {
		memset(  &rcd,  0,  sizeof(  rcd  )  );
	}

	SetDlgItemText(  IDC_STATIC_type,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  rcd.uiType  )  );  
	SetDlgItemText(  IDC_STATIC_imTaskStatus,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyStatusTable  ),  rcd.iStatus  )  );
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
	getTimeStr(  rcd.tRecvTime,  buf,  mycountof(  buf  )  );
	qyDisplayTime(  buf,  buf1,  mycountof(  buf1  )  );  
	SetDlgItemText(  IDC_STATIC_recvTime,  CString(  buf1  )  );


	//
	SetDlgItemText(  IDC_STATIC_subject,  rcd.subject  );
	SetDlgItemText(  IDC_STATIC_content,  rcd.content  );


errLabel:
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
