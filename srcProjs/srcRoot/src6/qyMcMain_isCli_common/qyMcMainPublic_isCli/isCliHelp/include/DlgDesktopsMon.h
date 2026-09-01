#if !defined(AFX_DLGDESKTOPSMON_H__8BE1FDE2_2F7E_4742_88D7_83A7F31DA55D__INCLUDED_)
#define AFX_DLGDESKTOPSMON_H__8BE1FDE2_2F7E_4742_88D7_83A7F31DA55D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDesktopsMon.h : header file
//

#include	"dlgDesktopsMonProc.h"


/////////////////////////////////////////////////////////////////////////////
// CDlgDesktopsMon dialog

class CDlgDesktopsMon : public CDialog
{
// Construction
public:
	CDlgDesktopsMon(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDesktopsMon)
	enum { IDD = IDD_desktopsMon };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	//
	DLG_desktopsMon_var	m_var;

	//  
	BOOL			bSetDlgInfo(  int  iWndContentType,  int  iSubtype,  int  iResId_menu,  unsigned  short  usCnt_row,  unsigned  short  usCnt_col,  unsigned  int  uiInitW_pic,  unsigned  int  uiInitH_pic  );
	int				getWndContentType(  );  
	int				getWndContentSubtype(  );
		
	virtual  BOOL  	bQuitDlg(  );
	
	BOOL			Create(const RECT& rect);

	BOOL			bEnableScrollBar(  BOOL  bEnable  );
	int				SetPicRect(  int  w,  int  h,  BOOL  bMoveWindow  );
	int				getPicRect(  int  idc,  RECT  *  pRc  );  

	//
	virtual  int	sizeAllControls(  RECT  rc  );
	void			doLayout(  );

	void			endFullScreen(  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDesktopsMon)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	virtual void PostNcDestroy();


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDesktopsMon)
		// NOTE: the ClassWizard will add member functions here
public:
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void Onstopscrollbar();
	afx_msg void OnUpdatestopscrollbar(CCmdUI *pCmdUI);
	afx_msg void Onstartscrollbar();
	afx_msg void OnUpdatestartscrollbar(CCmdUI *pCmdUI);
	//}}AFX_MSG
	virtual  afx_msg LRESULT OnQyComm( WPARAM, LPARAM );
	virtual  afx_msg LRESULT OnQyPostComm(  WPARAM, LPARAM  );
	DECLARE_MESSAGE_MAP()
	afx_msg void Onfullscreen();
	afx_msg void OnUpdatefullscreen(CCmdUI *pCmdUI);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg void OnMove(int x, int y);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDESKTOPSMON_H__8BE1FDE2_2F7E_4742_88D7_83A7F31DA55D__INCLUDED_)
