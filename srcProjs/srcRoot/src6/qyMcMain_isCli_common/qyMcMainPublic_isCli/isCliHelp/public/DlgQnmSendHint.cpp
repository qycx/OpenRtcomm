// DlgQnmSendHint.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qymc.h"
#include	"myresource.h"
#include	"DlgQnmSendHint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmSendHint dialog


CDlgQnmSendHint::CDlgQnmSendHint(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmSendHint::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmSendHint)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgQnmSendHint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmSendHint)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmSendHint, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmSendHint)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDlgQnmSendHint::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmSendHint message handlers

void CDlgQnmSendHint::OnOK() 
{

	GetDlgItemText(  IDC_EDIT_hint,  m_var.hint,  mycountof(  m_var.hint  )  );  
	tTrim(  m_var.hint  );
	if  (  !m_var.hint[0]  )  {
		GetDlgItem(  IDC_EDIT_hint  )->SetFocus(  );
		return;
	}

	//  qyShowHint(  qySendHint(  m_var.ipBuf,  hintBuf  )  ?  _T(  "发送失败"  )  :  _T(  "发送成功"  )   );
		
	CDialog::OnOK();
}

void CDlgQnmSendHint::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

BOOL CDlgQnmSendHint::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	SetDlgItemText(  IDC_STATIC_hint,  m_var.staticHint  );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
