
// avConsoleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "avConsole.h"
#include "avConsoleDlg.h"
#include "afxdialogex.h"
//
#include	"qyDefs_open.h"

//
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//
#define		CONST_myWm_postComm					(  WM_USER  +  30  )	//  主要用PostMessenger(  )发送，用wParam, lParam来表示发送信息


//
#define		CONST_wParam_null					0
#define		CONST_wParam_retrieveUsrs			1
#define		CONST_wParam_retrieveDynBmps		2

//
int  g_iLogon  =  0;

int  doCmd_initMsg(  int  iLogon,  HWND  hParent  );


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CavConsoleDlg dialog



CavConsoleDlg::CavConsoleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CavConsoleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CavConsoleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CavConsoleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON4, &CavConsoleDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_retrieveUsrs, &CavConsoleDlg::OnBnClickedButtonretrieveusrs)
	ON_WM_COPYDATA()
	ON_MESSAGE(CONST_myWm_postComm, OnMyPostComm)

	ON_BN_CLICKED(IDC_BUTTON_retrieveDynBmps, &CavConsoleDlg::OnBnClickedButtonretrievedynbmps)
	ON_BN_CLICKED(IDC_BUTTON_move104webcam1, &CavConsoleDlg::OnBnClickedButtonmove104webcam1)
	ON_BN_CLICKED(IDC_BUTTON_move104screen1, &CavConsoleDlg::OnBnClickedButtonmove104screen1)
	ON_BN_CLICKED(IDC_BUTTON_view104screen1_full, &CavConsoleDlg::OnBnClickedButtonview104screen1full)
	ON_BN_CLICKED(IDC_BUTTON_close104screen1, &CavConsoleDlg::OnBnClickedButtonclose104screen1)
	ON_BN_CLICKED(IDC_BUTTON_view104screen1_normal, &CavConsoleDlg::OnBnClickedButtonview104screen1normal)
	ON_BN_CLICKED(IDC_BUTTON_view104Webcam_full, &CavConsoleDlg::OnBnClickedButtonview104webcamfull)
	ON_BN_CLICKED(IDC_BUTTON_close104webcam1, &CavConsoleDlg::OnBnClickedButtonclose104webcam1)
	ON_BN_CLICKED(IDC_BUTTON_view104webcam1_normal, &CavConsoleDlg::OnBnClickedButtonview104webcam1normal)
	ON_BN_CLICKED(IDC_BUTTON_move104screen1_full, &CavConsoleDlg::OnBnClickedButtonmove104screen1full)
	ON_BN_CLICKED(IDC_BUTTON_move104webcam1_full, &CavConsoleDlg::OnBnClickedButtonmove104webcam1full)
	ON_BN_CLICKED(IDC_BUTTON_move104screen1_hide, &CavConsoleDlg::OnBnClickedButtonmove104screen1hide)
	ON_BN_CLICKED(IDC_BUTTON_move104webcam1_hide, &CavConsoleDlg::OnBnClickedButtonmove104webcam1hide)
	ON_BN_CLICKED(IDC_BUTTON_view104av, &CavConsoleDlg::OnBnClickedButtonview104av)
	ON_BN_CLICKED(IDC_BUTTON_close104AvTalk, &CavConsoleDlg::OnBnClickedButtonclose104avtalk)
	ON_BN_CLICKED(IDC_BUTTON_sendTo104, &CavConsoleDlg::OnBnClickedButtonsendto104)
	ON_BN_CLICKED(IDC_BUTTON_view3DWallFull, &CavConsoleDlg::OnBnClickedButtonview3dwallfull)
	ON_BN_CLICKED(IDOK, &CavConsoleDlg::OnBnClickedOk)
END_MESSAGE_MAP()


//
 void  SetClientSize(  HWND  hWnd,  int  clientWidth,  int  clientHeight  )
{
	if  (  IsWindow(  hWnd  )  )
	{
		DWORD  dwStyle  =  GetWindowLongPtr(  hWnd,  GWL_STYLE  );
		DWORD  dwExStyle  =  GetWindowLongPtr(  hWnd,  GWL_EXSTYLE  );
		HMENU  menu  =  GetMenu(  hWnd  );

		RECT  rc  =  {  0,  0,  clientWidth,  clientHeight  };

		if  (  !AdjustWindowRectEx(  &rc,  dwStyle,  menu  ?  TRUE  :FALSE,  dwExStyle  )  )
			MessageBox(  NULL,  L"AdjustWindowRectEx Failed",  L"error",  MB_OK  );

		SetWindowPos(  hWnd,  NULL,  0,  0,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  SWP_NOZORDER  |  SWP_NOMOVE  );

#ifdef  _DEBUG
		RECT  newClientRC;
		GetClientRect(  hWnd,  &newClientRC  );
		assert(  (  newClientRC.right  -  newClientRC.left  )  ==  clientWidth  );
		assert(  (  newClientRC.bottom  -  newClientRC.top  )  ==  clientHeight  );
#endif
	}
}


// CavConsoleDlg message handlers

BOOL CavConsoleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
	//SetClientSize(  m_hWnd,  640,  480  );

	//
	SetWindowText(  _T(  "独一无二的窗口题头"  )  );
	//
	SetDlgItemInt(  IDC_EDIT_iLogon,  0  );		//  2

	//
	int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );

	//
	doCmd_initMsg(  iLogon,  m_hWnd  );


	//
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CavConsoleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CavConsoleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CavConsoleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//
#include	"avConsole_open.h"



//
int  doCmd_view(  int  iLogon,  __int64  i64Id,  unsigned  int  uiObjType,  unsigned  short  usIndex_obj,  BOOL  bDesktop,  HWND  hParent,  int  x,  int  y,  int  w,  int  h,  BOOL  bFullScreen  )
{
		//TCHAR  *  title  =  _T(  "Qycx Video Conference"  );
	TCHAR  title[128]  =  _T(  ""  );
	//
	_sntprintf_s(  title,  mycountof(  title  ),  _T(  "%s%d"  ),  CONST_wndTitle_qisTsMain_prefix,  iLogon  );
	//
	HWND  hWall  =  ::FindWindow(  0,  title  );
	if  (  hWall  )  {
		int  ii;
		ii  =  9;
		//		
		AvConsole_req_view  req  =  {0};
		
		//
		req.iType  =  CONST_qisMsgType_avConsole;		
		//
		req.usCmd  =  CONST_avConsole_cmd_view;
		//
		req.ui64Id  =  i64Id;
		req.uiObjType  =  uiObjType;
		req.usIndex_obj  =  usIndex_obj;
		//
		req.bDesktop  =  bDesktop;
		if  (  !bDesktop  )  {
			GetWindowText(  hParent,  req.unique_wndTitle_parent,  mycountof(  req.unique_wndTitle_parent  )  );
		}
		//
		req.x  =  x;
		req.y  =  y;
		req.w  =  w;
		req.h  =  h;
		req.bFullScreen  =  bFullScreen;

		//
		COPYDATASTRUCT		tmpCopyData;

		tmpCopyData.lpData  =  &req;		 
		tmpCopyData.cbData  =  sizeof(  req  );
		int  iRet  =  ::SendMessage( hWall,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
		
		//
		TCHAR  tBuf[128];
		_sntprintf_s(  tBuf,  mycountof(  tBuf  ),  _T(  "iRet  %d\n"  ),  iRet  );
		OutputDebugString(  tBuf  );

		//		 
		ii  =  0;
	}

	return  0;
}


//  2017/06/13
int  doCmd_move(  int  iLogon,  __int64  i64Id,  unsigned  int  uiObjType,  unsigned  short  usIndex_obj,  BOOL  bDesktop,  HWND  hParent,  BOOL  bHide,  int  x,  int  y,  int  w,  int  h,  BOOL  bFullScreen  )
{
		//TCHAR  *  title  =  _T(  "Qycx Video Conference"  );
	TCHAR  title[128]  =  _T(  ""  );
	//
	_sntprintf_s(  title,  mycountof(  title  ),  _T(  "%s%d"  ),  CONST_wndTitle_qisTsMain_prefix,  iLogon  );
	//
	HWND  hWall  =  ::FindWindow(  0,  title  );
	if  (  hWall  )  {
		int  ii;
		ii  =  9;
		//		
		AvConsole_req_move  req  =  {0};
		
		//
		req.iType  =  CONST_qisMsgType_avConsole;		
		//
		req.usCmd  =  CONST_avConsole_cmd_move;
		//
		req.ui64Id  =  i64Id;
		req.uiObjType  =  uiObjType;
		req.usIndex_obj  =  usIndex_obj;
		//
		req.bDesktop  =  bDesktop;
		if  (  !bDesktop  )  {
			GetWindowText(  hParent,  req.unique_wndTitle_parent,  mycountof(  req.unique_wndTitle_parent  )  );
		}
		//
		req.bHide  =  bHide;
		req.x  =  x;
		req.y  =  y;
		req.w  =  w;
		req.h  =  h;
		req.bFullScreen  =  bFullScreen;

		//
		COPYDATASTRUCT		tmpCopyData;

		tmpCopyData.lpData  =  &req;		 
		tmpCopyData.cbData  =  sizeof(  req  );
		int  iRet  =  ::SendMessage( hWall,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
		
		//
		TCHAR  tBuf[128];
		_sntprintf_s(  tBuf,  mycountof(  tBuf  ),  _T(  "iRet  %d\n"  ),  iRet  );
		OutputDebugString(  tBuf  );

		//		 
		ii  =  0;
	}

	return  0;
}



//
int  doCmd_close(  int  iLogon,  __int64  i64Id,  unsigned  int  uiObjType,  unsigned  short  usIndex_obj  )
{
		//TCHAR  *  title  =  _T(  "Qycx Video Conference"  );
	TCHAR  title[128]  =  _T(  ""  );
	//
	_sntprintf_s(  title,  mycountof(  title  ),  _T(  "%s%d"  ),  CONST_wndTitle_qisTsMain_prefix,  iLogon  );
	//
	HWND  hWall  =  ::FindWindow(  0,  title  );
	if  (  hWall  )  {
		int  ii;
		ii  =  9;
		//		
		AvConsole_req_close  req  =  {0};
		
		//
		req.iType  =  CONST_qisMsgType_avConsole;		
		//
		req.usCmd  =  CONST_avConsole_cmd_close;
		//
		req.ui64Id  =  i64Id;
		req.uiObjType  =  uiObjType;
		req.usIndex_obj  =  usIndex_obj;

		//
		COPYDATASTRUCT		tmpCopyData;

		tmpCopyData.lpData  =  &req;		 
		tmpCopyData.cbData  =  sizeof(  req  );
		int  iRet  =  ::SendMessage( hWall,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
		
		//
		TCHAR  tBuf[128];
		_sntprintf_s(  tBuf,  mycountof(  tBuf  ),  _T(  "iRet  %d\n"  ),  iRet  );
		OutputDebugString(  tBuf  );

		//		 
		ii  =  0;
	}

	return  0;
}

//
int  doCmd_closeAll(  int  iLogon  )
{
		//TCHAR  *  title  =  _T(  "Qycx Video Conference"  );
	TCHAR  title[128]  =  _T(  ""  );
	//
	_sntprintf_s(  title,  mycountof(  title  ),  _T(  "%s%d"  ),  CONST_wndTitle_qisTsMain_prefix,  iLogon  );
	//
	HWND  hWall  =  ::FindWindow(  0,  title  );
	if  (  hWall  )  {
		int  ii;
		ii  =  9;
		//		
		AvConsole_req_closeAll  req  =  {0};
		
		//
		req.iType  =  CONST_qisMsgType_avConsole;		
		//
		req.usCmd  =  CONST_avConsole_cmd_closeAll;

		//
		COPYDATASTRUCT		tmpCopyData;

		tmpCopyData.lpData  =  &req;		 
		tmpCopyData.cbData  =  sizeof(  req  );
		int  iRet  =  ::SendMessage( hWall,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
		
		//
		TCHAR  tBuf[128];
		_sntprintf_s(  tBuf,  mycountof(  tBuf  ),  _T(  "iRet  %d\n"  ),  iRet  );
		OutputDebugString(  tBuf  );

		//		 
		ii  =  0;
	}

	return  0;
}


//
//  2017/06/13
int  doCmd_avTalk(  int  iLogon,  __int64  i64Id,  BOOL  bDesktop,  HWND  hParent,  BOOL  bHide,  int  x,  int  y,  int  w,  int  h,  BOOL  bFullScreen  )
{
		//TCHAR  *  title  =  _T(  "Qycx Video Conference"  );
	TCHAR  title[128]  =  _T(  ""  );
	//
	_sntprintf_s(  title,  mycountof(  title  ),  _T(  "%s%d"  ),  CONST_wndTitle_qisTsMain_prefix,  iLogon  );
	//
	HWND  hWall  =  ::FindWindow(  0,  title  );
	if  (  hWall  )  {
		int  ii;
		ii  =  9;
		//		
		AvConsole_req_avTalk  req  =  {0};
		
		//
		req.iType  =  CONST_qisMsgType_avConsole;		
		//
		req.usCmd  =  CONST_avConsole_cmd_avTalk;
		//
		req.ui64Id  =  i64Id;
		//
		req.bDesktop  =  bDesktop;
		if  (  !bDesktop  )  {
			GetWindowText(  hParent,  req.unique_wndTitle_parent,  mycountof(  req.unique_wndTitle_parent  )  );
		}
		//
		req.bHide  =  bHide;
		req.x  =  x;
		req.y  =  y;
		req.w  =  w;
		req.h  =  h;
		req.bFullScreen  =  bFullScreen;

		//
		COPYDATASTRUCT		tmpCopyData;

		tmpCopyData.lpData  =  &req;		 
		tmpCopyData.cbData  =  sizeof(  req  );
		int  iRet  =  ::SendMessage( hWall,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
		
		//
		TCHAR  tBuf[128];
		_sntprintf_s(  tBuf,  mycountof(  tBuf  ),  _T(  "iRet  %d\n"  ),  iRet  );
		OutputDebugString(  tBuf  );

		//		 
		ii  =  0;
	}

	return  0;
}

//
int  doCmd_closeAvTalk(  int  iLogon,  __int64  i64Id  )
{
		//TCHAR  *  title  =  _T(  "Qycx Video Conference"  );
	TCHAR  title[128]  =  _T(  ""  );
	//
	_sntprintf_s(  title,  mycountof(  title  ),  _T(  "%s%d"  ),  CONST_wndTitle_qisTsMain_prefix,  iLogon  );
	//
	HWND  hWall  =  ::FindWindow(  0,  title  );
	if  (  hWall  )  {
		int  ii;
		ii  =  9;
		//		
		AvConsole_req_closeAvTalk  req  =  {0};
		
		//
		req.iType  =  CONST_qisMsgType_avConsole;		
		//
		req.usCmd  =  CONST_avConsole_cmd_closeAvTalk;
		//
		req.ui64Id  =  i64Id;
		//

		//
		COPYDATASTRUCT		tmpCopyData;

		tmpCopyData.lpData  =  &req;		 
		tmpCopyData.cbData  =  sizeof(  req  );
		int  iRet  =  ::SendMessage( hWall,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
		
		//
		TCHAR  tBuf[128];
		_sntprintf_s(  tBuf,  mycountof(  tBuf  ),  _T(  "iRet  %d\n"  ),  iRet  );
		OutputDebugString(  tBuf  );

		//		 
		ii  =  0;
	}

	return  0;
}


//
//  
//  接收消息前必须先发此消息
int  doCmd_initMsg(  int  iLogon,  HWND  hParent  )
{
		//TCHAR  *  title  =  _T(  "Qycx Video Conference"  );
	TCHAR  title[128]  =  _T(  ""  );
	//
	_sntprintf_s(  title,  mycountof(  title  ),  _T(  "%s%d"  ),  CONST_wndTitle_qisTsMain_prefix,  iLogon  );
	//
	HWND  hWall  =  ::FindWindow(  0,  title  );
	if  (  hWall  )  {
		int  ii;
		ii  =  9;
		//		
		AvConsole_req_initMsg  req  =  {0};
		
		//
		req.iType  =  CONST_qisMsgType_avConsole;		
		//
		req.usCmd  =  CONST_avConsole_cmd_initMsg;
		//
		GetWindowText(  hParent,  req.unique_wndTitle_parent,  mycountof(  req.unique_wndTitle_parent  )  );
		
		//
		COPYDATASTRUCT		tmpCopyData;

		tmpCopyData.lpData  =  &req;		 
		tmpCopyData.cbData  =  sizeof(  req  );
		int  iRet  =  ::SendMessage( hWall,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
		
		//
		TCHAR  tBuf[128];
		_sntprintf_s(  tBuf,  mycountof(  tBuf  ),  _T(  "iRet  %d\n"  ),  iRet  );
		OutputDebugString(  tBuf  );

		//		 
		ii  =  0;
	}

	return  0;
}



//
//
int  doCmd_msg(  int  iLogon,  __int64  i64Id_dst,  HWND  hParent,  TCHAR  *  tTxt  )
{
		//TCHAR  *  title  =  _T(  "Qycx Video Conference"  );
	TCHAR  title[128]  =  _T(  ""  );
	//
	_sntprintf_s(  title,  mycountof(  title  ),  _T(  "%s%d"  ),  CONST_wndTitle_qisTsMain_prefix,  iLogon  );
	//
	HWND  hWall  =  ::FindWindow(  0,  title  );
	if  (  hWall  )  {
		int  ii;
		ii  =  9;
		//		
		AvConsole_req_msg  req  =  {0};
		
		//
		req.iType  =  CONST_qisMsgType_avConsole;		
		//
		req.usCmd  =  CONST_avConsole_cmd_msg;
		//
		GetWindowText(  hParent,  req.unique_wndTitle_parent,  mycountof(  req.unique_wndTitle_parent  )  );
		
		//
		req.ui64Id_dst  =  i64Id_dst;
		//
		lstrcpyn(  req.tTxt,  tTxt,  sizeof(  req.tTxt  )  /  sizeof(  req.tTxt[0]  )  );

		//
		COPYDATASTRUCT		tmpCopyData;

		tmpCopyData.lpData  =  &req;		 
		tmpCopyData.cbData  =  sizeof(  req  );
		int  iRet  =  ::SendMessage( hWall,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
		
		//
		TCHAR  tBuf[128];
		_sntprintf_s(  tBuf,  mycountof(  tBuf  ),  _T(  "iRet  %d\n"  ),  iRet  );
		OutputDebugString(  tBuf  );

		//		 
		ii  =  0;
	}

	return  0;
}


//
//
int  doCmd_view3dWall(  int  iLogon,  HWND  hParent  )
{
		//TCHAR  *  title  =  _T(  "Qycx Video Conference"  );
	TCHAR  title[128]  =  _T(  ""  );
	//
	_sntprintf_s(  title,  mycountof(  title  ),  _T(  "%s%d"  ),  CONST_wndTitle_qisTsMain_prefix,  iLogon  );
	//
	HWND  hWall  =  ::FindWindow(  0,  title  );
	if  (  hWall  )  {
		int  ii;
		ii  =  9;
		//		
		AvConsole_req_view3dWall  req  =  {0};
		
		//
		req.iType  =  CONST_qisMsgType_avConsole;		
		//
		req.usCmd  =  CONST_avConsole_cmd_view3dWall;
		//
		GetWindowText(  hParent,  req.unique_wndTitle_parent,  mycountof(  req.unique_wndTitle_parent  )  );
		
		//

		//
		COPYDATASTRUCT		tmpCopyData;

		tmpCopyData.lpData  =  &req;		 
		tmpCopyData.cbData  =  sizeof(  req  );
		int  iRet  =  ::SendMessage( hWall,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
		
		//
		TCHAR  tBuf[128];
		_sntprintf_s(  tBuf,  mycountof(  tBuf  ),  _T(  "iRet  %d\n"  ),  iRet  );
		OutputDebugString(  tBuf  );

		//		 
		ii  =  0;
	}

	return  0;
}



//
AvConsole_req_retrieveUsrs  g_Reply_retrieveUsrs;
//
int  doCmd_retrieveUsrs(  int  iLogon,  HWND  hWnd_recv,  unsigned  __int64  ui64Id_lastRecvd  )
{
	int  iErr  =  -1;
		//TCHAR  *  title  =  _T(  "Qycx Video Conference"  );
	TCHAR  title[128]  =  _T(  ""  );
	//
	_sntprintf_s(  title,  mycountof(  title  ),  _T(  "%s%d"  ),  CONST_wndTitle_qisTsMain_prefix,  iLogon  );
	//
	HWND  hWall  =  ::FindWindow(  0,  title  );
	if  (  hWall  )  {
		int  ii;
		ii  =  9;
		//
		{
			 //				
			 AvConsole_req_retrieveUsrs  req  =  {0};
				
			 //		
			 req.iType  =  CONST_qisMsgType_avConsole;				
			 //		
			 req.usCmd  =  CONST_avConsole_cmd_retrieveUsrs;		
			 //		
			 GetWindowText(  hWnd_recv,  req.unique_wndTitle_parent,  mycountof(  req.unique_wndTitle_parent  )  );
			 //
			 req.ui64Id_lastRecvd  =  ui64Id_lastRecvd;
			 		
			 //		
			 memset(  &g_Reply_retrieveUsrs,  0,  sizeof(  g_Reply_retrieveUsrs  )  );
			 		
			 //	
			 COPYDATASTRUCT		tmpCopyData;
			 		
			 tmpCopyData.lpData  =  &req;		 
			 tmpCopyData.cbData  =  sizeof(  req  );		
			 int  iRet  =  ::SendMessage( hWall,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
				
			 //		
			 TCHAR  tBuf[128];
		
			 _sntprintf_s(  tBuf,  mycountof(  tBuf  ),  _T(  "iRet  %d\n"  ),  iRet  );	
			 OutputDebugString(  tBuf  );


		}

		//		 
		ii  =  0;
	}

	iErr  =  0;
errLabel:

	return  iErr;
}



//
AvConsole_req_retrieveDynBmps  g_Reply_retrieveDynBmps;
//
int  doCmd_retrieveDynBmps(  int  iLogon,  HWND  hWnd_recv,  unsigned  __int64  ui64Id_toBeRetrieved  )
{
	int  iErr  =  -1;
		//TCHAR  *  title  =  _T(  "Qycx Video Conference"  );
	TCHAR  title[128]  =  _T(  ""  );
	//
	_sntprintf_s(  title,  mycountof(  title  ),  _T(  "%s%d"  ),  CONST_wndTitle_qisTsMain_prefix,  iLogon  );
	//
	HWND  hWall  =  ::FindWindow(  0,  title  );
	if  (  hWall  )  {
		int  ii;
		ii  =  9;
		//
		{
			 //				
			 AvConsole_req_retrieveDynBmps  req  =  {0};
				
			 //		
			 req.iType  =  CONST_qisMsgType_avConsole;				
			 //		
			 req.usCmd  =  CONST_avConsole_cmd_retrieveDynBmps;		
			 //		
			 GetWindowText(  hWnd_recv,  req.unique_wndTitle_parent,  mycountof(  req.unique_wndTitle_parent  )  );
			 
			 //
			 if  (  !ui64Id_toBeRetrieved  )  goto  errLabel;
			 req.ui64Id_toBeRetrieved  =  ui64Id_toBeRetrieved;


			 //		
			 memset(  &g_Reply_retrieveDynBmps,  0,  sizeof(  g_Reply_retrieveDynBmps  )  );
			 		
			 //	
			 COPYDATASTRUCT		tmpCopyData;
			 		
			 tmpCopyData.lpData  =  &req;		 
			 tmpCopyData.cbData  =  sizeof(  req  );		
			 int  iRet  =  ::SendMessage( hWall,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
				
			 //		
			 TCHAR  tBuf[128];
		
			 _sntprintf_s(  tBuf,  mycountof(  tBuf  ),  _T(  "iRet  %d\n"  ),  iRet  );	
			 OutputDebugString(  tBuf  );


		}

		//		 
		ii  =  0;
	}

	iErr  =  0;
errLabel:

	return  iErr;
}




//

















void CavConsoleDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
		int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );


	doCmd_closeAll(  iLogon  );
}


void CavConsoleDlg::OnBnClickedButtonretrieveusrs()
{
	// TODO: Add your control notification handler code here
	int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );

	g_iLogon  =  iLogon;

	//
	unsigned  __int64  ui64Id_lastRecvd  =  0;
	//
	doCmd_retrieveUsrs(  iLogon,  m_hWnd,  ui64Id_lastRecvd  );

}


BOOL CavConsoleDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: Add your message handler code here and/or call default

	//
	OutputDebugString(  _T(  "OnCopyData\n"  )  );
	int  i;

	//
	AvConsole_req_head  *  pReqHead  =  (  AvConsole_req_head  *  )pCopyDataStruct->lpData;
	//
	switch  (  pReqHead->usCmd  )  {
			case  CONST_avConsole_cmd_retrieveUsrs:  {
				  AvConsole_req_retrieveUsrs  *  pReq  =  (  AvConsole_req_retrieveUsrs  *  )pReqHead;
				  
				  //
				  int  size  =  min(  pCopyDataStruct->cbData,  sizeof(  g_Reply_retrieveUsrs  )  );
				  //
				  memcpy(  &g_Reply_retrieveUsrs,  pCopyDataStruct->lpData,  size  );
				  //
				  PostMessage(  CONST_myWm_postComm,  CONST_wParam_retrieveUsrs,  0  );
				  }				  
				  break;
			case  CONST_avConsole_cmd_retrieveDynBmps:  {
				  AvConsole_req_retrieveDynBmps  *  pReq  =  (  AvConsole_req_retrieveDynBmps  *  )pReqHead;
				  //
				  //
				  int  size  =  min(  pCopyDataStruct->cbData,  sizeof(  g_Reply_retrieveDynBmps  )  );
				  //
				  memcpy(  &g_Reply_retrieveDynBmps,  pCopyDataStruct->lpData,  size  );
				  //
				  PostMessage(  CONST_myWm_postComm,  CONST_wParam_retrieveDynBmps,  0  );

				  }
				  break;
			case  CONST_avConsole_cmd_msg:  {
				  AvConsole_req_msg  *  pReq  =  (  AvConsole_req_msg  *  )pReqHead;
				  //
				  TCHAR  tBuf[256]  =  _T(  ""  );
				  //
				  _sntprintf_s(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%I64u: %s"  ),  pReq->ui64Id_from,  pReq->tTxt  );
				  SetDlgItemText(  IDC_STATIC_recv,  tBuf  );
				  }
				  break;
			default:
					break;
	}
		

	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}



//
LRESULT CavConsoleDlg::OnMyPostComm(  WPARAM  w, LPARAM  l  )
{
	OutputDebugString(  _T(  "OnMyPostComm\n"  )  );

	switch  (  w  )  {
			case  CONST_wParam_retrieveUsrs:  {
	  			  //			
				  if  (  !g_Reply_retrieveUsrs.ucbReply  )  goto  errLabel;			 
				  if  (  !g_Reply_retrieveUsrs.usCnt  )  {	
					  OutputDebugString(  _T(  "retrieveUsrs end.\n"  )  );
					  //  no more				 
					  break;			 
				  }
				  
				  //
				  TCHAR  tBuf[256];
			 	  int  i;			 
				  for  (  i  =  0;  i  <  g_Reply_retrieveUsrs.usCnt;  i  ++  )  {				 
					   _sntprintf_s(  tBuf,  mycountof(  tBuf  ),  _T(  "[%d] %I64u: %s %s %s\n"  ),  i,  g_Reply_retrieveUsrs.mems[i].ui64Id,  g_Reply_retrieveUsrs.mems[i].dw,  g_Reply_retrieveUsrs.mems[i].bm,  g_Reply_retrieveUsrs.mems[i].syr  );				 
					   OutputDebugString(  tBuf  );
				  }
				  			
				  //		
				  unsigned  __int64  ui64Id_lastRecvd  =  g_Reply_retrieveUsrs.mems[g_Reply_retrieveUsrs.usCnt  -  1].ui64Id;
				  //
				  doCmd_retrieveUsrs(  g_iLogon,  m_hWnd,  ui64Id_lastRecvd  );			 

				  }
				  
				  break;
			case  CONST_wParam_retrieveDynBmps:  {
	  			  //			
				  if  (  !g_Reply_retrieveDynBmps.ucbReply  )  goto  errLabel;			 
				  if  (  !g_Reply_retrieveDynBmps.usCnt  )  {	
					  OutputDebugString(  _T(  "retrieveDynBmps end.\n"  )  );
					  //  no more				 
					  break;			 
				  }
				  
				  //
				  TCHAR  tBuf[256];
			 	  int  i;			 
				  AvConsole_req_retrieveDynBmps  *  pReply  =  &g_Reply_retrieveDynBmps;
				  //
				  for  (  i  =  0;  i  <  pReply->usCnt;  i  ++  )  {				 
					  _sntprintf_s(  tBuf,  mycountof(  tBuf  ),  _T(  "[%d] %I64u: %d %d %d %s %dX%d\n"  ),  i,  pReply->ui64Id_toBeRetrieved,  pReply->mems[i].uiObjType,  (  int  )pReply->mems[i].usIndex_obj,  (  int  )pReply->mems[i].usHelp_subIndex,  pReply->mems[i].cusName,  pReply->mems[i].w,  pReply->mems[i].h  );				 
					   OutputDebugString(  tBuf  );
				  }

				  }
				  break;
			default:
					break;
	}


errLabel:

	return  0;
}




void CavConsoleDlg::OnBnClickedButtonretrievedynbmps()
{
	// TODO: Add your control notification handler code here
		int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );

	g_iLogon  =  iLogon;

	//
	unsigned  __int64  ui64Id_toBeRetrieved  =  105;//104;
	//
	doCmd_retrieveDynBmps(  iLogon,  m_hWnd,  ui64Id_toBeRetrieved  );

}




void CavConsoleDlg::OnBnClickedButtonmove104screen1()
{
	// TODO: Add your control notification handler code here
		int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );

	//
	__int64 i64Id  =  104;
	unsigned int  uiObjType  =  CONST_objType_screen;
	unsigned short usIndex_obj  =  1;


	BOOL  bDesktop  =  TRUE;
	HWND  hParent  =  m_hWnd;
	//
	int  x  =  0;	//320;
	int  y  =  0;
	int  w  =  1440;	//1280;	//  1920;	//320;
	int  h  =  900;		//720;	//1080;	// 240;
	BOOL  bFullScreen  =  TRUE;	//  FALSE;


#if  10  //  正常窗口
	//
	x  =  320;
	y  = 240;
	w  =  320;
	h  =  240;
	bFullScreen  =  FALSE;
#endif

	//
	doCmd_move(  iLogon,  i64Id,  uiObjType,  usIndex_obj,  bDesktop,  hParent,  false,  x,  y,  w,  h,  bFullScreen  );

}


void CavConsoleDlg::OnBnClickedButtonmove104screen1full()
{
	// TODO: Add your control notification handler code here
		int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );

	//
	__int64 i64Id  =  104;
	unsigned int  uiObjType  =  CONST_objType_screen;
	unsigned short usIndex_obj  =  1;


	BOOL  bDesktop  =  TRUE;
	HWND  hParent  =  m_hWnd;
	//
	int  x  =  0;	//320;
	int  y  =  0;
	int  w  =  1440;	//1280;	//  1920;	//320;
	int  h  =  900;		//720;	//1080;	// 240;
	BOOL  bFullScreen  =  TRUE;	//  FALSE;

	//
	doCmd_move(  iLogon,  i64Id,  uiObjType,  usIndex_obj,  bDesktop,  hParent,  false,  x,  y,  w,  h,  bFullScreen  );

}

void CavConsoleDlg::OnBnClickedButtonmove104screen1hide()
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
		int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );

	//
	__int64 i64Id  =  104;
	unsigned int  uiObjType  =  CONST_objType_screen;
	unsigned short usIndex_obj  =  1;


	BOOL  bDesktop  =  TRUE;
	HWND  hParent  =  m_hWnd;
	//
	BOOL  bHide  =  TRUE;
	int  x  =  0;	//320;
	int  y  =  0;
	int  w  =  1440;	//1280;	//  1920;	//320;
	int  h  =  900;		//720;	//1080;	// 240;
	BOOL  bFullScreen  =  TRUE;	//  FALSE;

	//
	doCmd_move(  iLogon,  i64Id,  uiObjType,  usIndex_obj,  bDesktop,  hParent,  bHide,  x,  y,  w,  h,  bFullScreen  );

}




void CavConsoleDlg::OnBnClickedButtonview104screen1full()
{
	// TODO: Add your control notification handler code here
	//
	int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );
	//
	__int64  i64Id  =  104;
	unsigned  int  uiObjType  =  CONST_objType_screen;
	unsigned  short  usIndex_obj  =  1;
	//
	BOOL  bDesktop  =  TRUE;
	HWND  hParent  =  m_hWnd;
	//
	int  x  =  0;
	int  y  =  0;
	int  w  =  1440;	//  1366;	//1920;	//1440;	//  320;
	int  h  =  900;		//  768;	//1080;	//900;		//  240;
	BOOL  bFullScreen  =  TRUE;
	//
	doCmd_view(  iLogon,  i64Id,  uiObjType,  usIndex_obj,  bDesktop,  hParent,  x,  y,  w,  h,  bFullScreen  );

errLabel:
	return;
}



void CavConsoleDlg::OnBnClickedButtonclose104screen1()
{
	// TODO: Add your control notification handler code here
		int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );

	//
	__int64 i64Id  =  104;
	unsigned int  uiObjType  =  CONST_objType_screen;
	unsigned short usIndex_obj  =  1;

	doCmd_close(  iLogon,  i64Id,  uiObjType,  usIndex_obj  );


}


void CavConsoleDlg::OnBnClickedButtonview104screen1normal()
{
	// TODO: Add your control notification handler code here
	//
	int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );
	//
	__int64  i64Id  =  104;
	unsigned  int  uiObjType  =  CONST_objType_screen;
	unsigned  short  usIndex_obj  =  1;
	//
	BOOL  bDesktop  =  TRUE;
	HWND  hParent  =  m_hWnd;
	//
	int  x  =  100;
	int  y  =  100;
	int  w  =  320;	//  1366;	//1920;	//1440;	//  320;
	int  h  =  240;		//  768;	//1080;	//900;		//  240;
	BOOL  bFullScreen  =  FALSE;
	//
	doCmd_view(  iLogon,  i64Id,  uiObjType,  usIndex_obj,  bDesktop,  hParent,  x,  y,  w,  h,  bFullScreen  );

errLabel:
	return;
}



void CavConsoleDlg::OnBnClickedButtonview104webcamfull()
{
	// TODO: Add your control notification handler code here
		int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );

	//
	__int64 i64Id  =  104;
	unsigned int  uiObjType  =  CONST_objType_webcam;
	unsigned short usIndex_obj  =  1;


	BOOL  bDesktop  =  TRUE;
	HWND  hParent  =  m_hWnd;
	//
	int  x  =  0;	//320;
	int  y  =  0;
	int  w  =  1440;	//1280;	//  1920;	//320;
	int  h  =  900;		//720;	//1080;	// 240;
	BOOL  bFullScreen  =  TRUE;	//  FALSE;
	//
	doCmd_view(  iLogon,  i64Id,  uiObjType,  usIndex_obj,  bDesktop,  hParent,  x,  y,  w,  h,  bFullScreen  );


}


void CavConsoleDlg::OnBnClickedButtonclose104webcam1()
{
	// TODO: Add your control notification handler code here
		int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );

	//
	__int64 i64Id  =  104;
	unsigned int  uiObjType  =  CONST_objType_webcam;
	unsigned short usIndex_obj  =  1;

	doCmd_close(  iLogon,  i64Id,  uiObjType,  usIndex_obj  );


}


void CavConsoleDlg::OnBnClickedButtonview104webcam1normal()
{
	// TODO: Add your control notification handler code here
		int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );

	//
	__int64 i64Id  =  104;
	unsigned int  uiObjType  =  CONST_objType_webcam;
	unsigned short usIndex_obj  =  1;


	BOOL  bDesktop  =  TRUE;
	HWND  hParent  =  m_hWnd;
	//
	int  x  =  0;	//320;
	int  y  =  0;
	int  w  =  320;	//1280;	//  1920;	//320;
	int  h  =  240;		//720;	//1080;	// 240;
	BOOL  bFullScreen  =  FALSE;
	//
	doCmd_view(  iLogon,  i64Id,  uiObjType,  usIndex_obj,  bDesktop,  hParent,  x,  y,  w,  h,  bFullScreen  );


}

void CavConsoleDlg::OnBnClickedButtonmove104webcam1()
{
	// TODO: Add your control notification handler code here
		int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );

	//
	__int64 i64Id  =  104;
	unsigned int  uiObjType  =  CONST_objType_webcam;
	unsigned short usIndex_obj  =  1;


	BOOL  bDesktop  =  TRUE;
	HWND  hParent  =  m_hWnd;
	//
	int  x  =  0;	//320;
	int  y  =  0;
	int  w  =  1440;	//1280;	//  1920;	//320;
	int  h  =  900;		//720;	//1080;	// 240;
	BOOL  bFullScreen  =  TRUE;	//  FALSE;


#if  10  //  正常窗口
	//
	x  =  320;
	y  = 240;
	w  =  320;
	h  =  240;
	bFullScreen  =  FALSE;
#endif

	//
	doCmd_move(  iLogon,  i64Id,  uiObjType,  usIndex_obj,  bDesktop,  hParent,  false,  x,  y,  w,  h,  bFullScreen  );

}



void CavConsoleDlg::OnBnClickedButtonmove104webcam1full()
{
	// TODO: Add your control notification handler code here
		int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );

	//
	__int64 i64Id  =  104;
	unsigned int  uiObjType  =  CONST_objType_webcam;
	unsigned short usIndex_obj  =  1;


	BOOL  bDesktop  =  TRUE;
	HWND  hParent  =  m_hWnd;
	//
	int  x  =  0;	//320;
	int  y  =  0;
	int  w  =  1440;	//1280;	//  1920;	//320;
	int  h  =  900;		//720;	//1080;	// 240;
	BOOL  bFullScreen  =  TRUE;	//  FALSE;



	//
	doCmd_move(  iLogon,  i64Id,  uiObjType,  usIndex_obj,  bDesktop,  hParent,  false,  x,  y,  w,  h,  bFullScreen  );

}






void CavConsoleDlg::OnBnClickedButtonmove104webcam1hide()
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
		int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );

	//
	__int64 i64Id  =  104;
	unsigned int  uiObjType  =  CONST_objType_webcam;
	unsigned short usIndex_obj  =  1;


	BOOL  bDesktop  =  TRUE;
	HWND  hParent  =  m_hWnd;
	//
	BOOL  bHide  =  TRUE;
	int  x  =  0;	//320;
	int  y  =  0;
	int  w  =  1440;	//1280;	//  1920;	//320;
	int  h  =  900;		//720;	//1080;	// 240;
	BOOL  bFullScreen  =  TRUE;	//  FALSE;



	//
	doCmd_move(  iLogon,  i64Id,  uiObjType,  usIndex_obj,  bDesktop,  hParent,  bHide,  x,  y,  w,  h,  bFullScreen  );

}


void CavConsoleDlg::OnBnClickedButtonview104av()
{
	// TODO: Add your control notification handler code here
	int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );

	__int64  i64Id  =  104;

	//
	BOOL  bDesktop  =  TRUE;
	HWND  hParent  =  m_hWnd;
	//
	BOOL  bHide  =  TRUE;
	int  x  =  0;	//320;
	int  y  =  0;
	int  w  =  320;	//1280;	//  1920;	//320;
	int  h  =  240;		//720;	//1080;	// 240;
	BOOL  bFullScreen  =  FALSE;	//  FALSE;


	//
	doCmd_avTalk(  iLogon,  i64Id,  bDesktop,  hParent,  bHide,  x,  y,  w,  h,  bFullScreen  );

	return;
}


void CavConsoleDlg::OnBnClickedButtonclose104avtalk()
{
	// TODO: Add your control notification handler code here
	int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );

	__int64  i64Id  =  104;

	doCmd_closeAvTalk(  iLogon,  i64Id  );


}






void CavConsoleDlg::OnBnClickedButtonsendto104()
{
	// TODO: Add your control notification handler code here
	int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );

	__int64  i64Id_dst  =  104;

	//
	HWND  hParent  =  m_hWnd;

	//
	TCHAR  tTxt[128] =  _T(  ""  );
	GetDlgItemText(  IDC_EDIT_sendTo104,  tTxt,  sizeof(  tTxt  )  /  sizeof(  tTxt[0]  )  );

	//
	doCmd_msg(  iLogon,  i64Id_dst,  hParent,  tTxt  );  

}


void CavConsoleDlg::OnBnClickedButtonview3dwallfull()
{
	// TODO: Add your control notification handler code here
	int  iLogon  =  GetDlgItemInt(  IDC_EDIT_iLogon  );


	//
	HWND  hParent  =  m_hWnd;

	doCmd_view3dWall(  iLogon,  hParent  );

}


void CavConsoleDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
