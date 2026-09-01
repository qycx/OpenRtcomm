#include  "stdafx.h"
//#include  "YT.h"
#include  "BitmapBtn.h"
#include  "resource.h"
//#include  "YTDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef  THIS_FILE
static char THIS_FILE[]  =  __FILE__;
#endif


void dlg_YTBtnDown(  HWND  hDlg,  int  nResourceID  );
void dlg_YTBtnUp(  HWND  hDlg,  int  nResourceID  );
//  void dlg_YTCHECKBtn(  HWND  hDlg,  int  nResourceID  );




CZBitmap::CZBitmap()
{
	m_bDown  =  FALSE;
	m_toolTip.m_hWnd  =  NULL;
}
CZBitmap::~CZBitmap()
{
}

BEGIN_MESSAGE_MAP(  CZBitmap,  CBitmapButton  )
	//  {{  AFX_MSG_MAP(  CZBitmap  )
	//  }}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

//  功能：按下按钮，执行云台对应的操作
void  CZBitmap::OnLButtonDown(  UINT  nFlags,  CPoint  point  )
{
	if  (  !m_bDown  )	{
		m_bDown  =  TRUE;
		//  (  (  CYTDlg  *  )AfxGetMainWnd(  )  )->YTBtnDown(  GetDlgCtrlID(  )  );
		dlg_YTBtnDown(  ::GetParent(  m_hWnd  ),  GetDlgCtrlID(  )  );
	}
	CBitmapButton::OnLButtonDown(  nFlags,  point  );
}

void  CZBitmap::OnLButtonUp(  UINT  nFlags,  CPoint  point  )
{
	if  (  m_bDown  )  {
		m_bDown  =  FALSE;
		//  (  (  CYTDlg  *  )AfxGetMainWnd(  )  )->YTBtnUp(  GetDlgCtrlID(  )  );
		dlg_YTBtnUp(  ::GetParent(  m_hWnd  ),  GetDlgCtrlID(  )  );
	}
	CBitmapButton::OnLButtonUp(  nFlags,  point  );
}

void  CZBitmap::initToolTip(  )
{
	if  (  m_toolTip.m_hWnd  ==  NULL  ){
		m_toolTip.Create(  this  );
		m_toolTip.Activate(  FALSE  );
		m_toolTip.SendMessage(  TTM_SETMAXTIPWIDTH,  0,  400  );
		m_toolTip.SetTipTextColor(  RGB(  255,0,  0  )  );
	}
}

BOOL  CZBitmap::PreTranslateMessage(  MSG  *  pMsg  )
{
	initToolTip(  );
	m_toolTip.RelayEvent(  pMsg  );
	return  CButton::PreTranslateMessage(  pMsg  );
}

void  CZBitmap::setToolTipText(  int  nText,  BOOL  bActivate  )
{
	CString  sText;
	sText.LoadStringW(  nText  );
	if  (  sText.IsEmpty(  )  ==  FALSE  )  setToolTipText(  (  LPCTSTR  )sText,  bActivate  );
}

void  CZBitmap::setToolTipText(  LPCTSTR  lpszText,  BOOL  bActivate  )
{
	if  (  lpszText  ==  NULL  )  return;

	initToolTip(  );

	if  (  m_toolTip.GetToolCount(  )  ==  0  )  {
		CRect  rectBtn;
		GetClientRect(  rectBtn  );
		m_toolTip.AddTool(  this,  lpszText,  rectBtn,  1  );
	}
	m_toolTip.UpdateTipText(  lpszText,  this,  1  );
	m_toolTip.Activate(  bActivate  );
}

void  CZBitmap::activateToolTip(  BOOL  bEnable  )
{
	if  (  m_toolTip.GetToolCount(  )  ==  0  )  return;
	m_toolTip.Activate(  bEnable  );
}
