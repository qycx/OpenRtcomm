// qyVDevSampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "qyVDevSample.h"
#include "qyVDevSampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQyVDevSampleDlg dialog

CQyVDevSampleDlg::CQyVDevSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQyVDevSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQyVDevSampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQyVDevSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQyVDevSampleDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CQyVDevSampleDlg, CDialog)
	//{{AFX_MSG_MAP(CQyVDevSampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_COPYDATA()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQyVDevSampleDlg message handlers


typedef  int  (  *  PF_qvdSendSm  )(  void  *  p0,  WCHAR  *  sm,  char  *  phoneNo,  HWND  hWnd_notify,  int  iUsrData  );


 HINSTANCE		gInstance	=	NULL;
 PF_qvdSendSm	gpf			=	NULL;

 int  initQvd(  void  *  p0,  LPCWSTR  dllPath,  void  *  p2  )
{
	 int	iErr	=	-1;

	 if  (  !gInstance  )  {
		 gInstance  =  LoadLibrary(  CString(  dllPath  )   );
		 if  (  !gInstance  )  goto  errLabel;
	 }
	 if  (  !gpf  )  {
		 gpf  =  (  PF_qvdSendSm  )GetProcAddress(  gInstance,  "qvdSendSm"  );
		 if  (  !gpf  )  goto  errLabel;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}

 void  exitQvd(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 if  (  gInstance  )  {
		 FreeLibrary(  gInstance  );  gInstance  =  NULL;
	 }
	 return;
}



BOOL CQyVDevSampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	initQvd(  0,  CString(  ".\\qyVDevApi.dll"  ),  0  );
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CQyVDevSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CQyVDevSampleDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CQyVDevSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CQyVDevSampleDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	exitQvd(  0,  0,  0  );
	
}

typedef  struct  __qvdSmResp_t									{
				 int											id;
				 int											iErr;
}		 QVD_SM_RESP;


void CQyVDevSampleDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString		smStr;
	char		phone[256];
	static	int	id	=	0;

	GetDlgItemText(  IDC_EDIT1,  smStr  );
	GetDlgItemTextA(  this->m_hWnd,  IDC_EDIT2,  phone,  sizeof(  phone  ) );

	id  ++  ;

	if  (  gpf  )  gpf(  0,  smStr.GetBuffer(  0  ),  phone,  this->m_hWnd,  id  );
	
}

BOOL CQyVDevSampleDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	// TODO: Add your message handler code here and/or call default
	QVD_SM_RESP	*	pResp	=	(  QVD_SM_RESP  *  )pCopyDataStruct->lpData;
	TCHAR			tBuf[128];

	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "Short message [%d] has been sent."  ),  pResp->id  );
	SetWindowText(  tBuf  );

	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}
