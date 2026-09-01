#if !defined(AFX_DLGTALK_H__5D6C714C_9AA6_4A2E_983F_E387EE0F80D4__INCLUDED_)
#define AFX_DLGTALK_H__5D6C714C_9AA6_4A2E_983F_E387EE0F80D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTalk.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTalk dialog

#include	"qyStatic.h"

#include	"dlgTalkProc.h"

#include	"skinProc_mfc.h"


 
//
class CDlgTalk : public CDialog
{
// Construction
public:
	//  CDlgTalk(CWnd* pParent = NULL);   // standard constructor
	CDlgTalk(QY_MC* pQyMc, HWND hParent = NULL);   // standard constructor

public:
	virtual ~CDlgTalk();

// Dialog Data
	//{{AFX_DATA(CDlgTalk)
	enum { IDD = IDD_talk };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	//
public:	
	
	//  2015/11/12	
	int												iIndex_talkerInfo;						//  2015/11/12
	
	//
	//DLG_TALK_var							m_var;

	//
	CBrush									m_brush_hangingUp_dlg;
	//
	CBrush									m_brush_dlgDesc;				//  2011/03/16. 指没有av活动的
	CBrush									m_brush_applyToRecv_dlgDesc;	//  2011/03/28. 等待接收.
	CBrush									m_brush_av_dlgDesc;				//  2011/03/12
	CBrush									m_brush_hangingUp_dlgDesc;

	CBrush									m_brush_meDesc;					//  2014/10/02

	CBrush									m_brush_fullScreen_dlg;			//  2011/03/16

	//
	SKIN_proc								m_skinProc;

	//
#if  0
	CImageList								m_LargeImageList;
	CImageList								m_SmallImageList;
#endif

private:

	//
	friend	int  tmpHandler_displayTalker(  void  *  p0,  void  *  pCommonParam1Param,  void  *  pQElem  );
	friend	int  printQ_mis(  void  *  pQ,  int  bNetworkData  );


public:

	//  2015/11/13
	DLG_TALK_var  *  get_pm_var();

	//
	BOOL	Create(const RECT& rect);
	BOOL	bQuitDlg(  BOOL  bCancelTasks  );

	//
	BOOL			bEnableScrollBar(  BOOL  bEnable  );
	int				SetPicRect(  int  w,  int  h,  BOOL  bMoveWindow  );
	int				getPicRect(  int  idc,  RECT  *  pRc  );  

	//
	virtual  int	sizeAllControls(  RECT  rc  );
	void			doLayout(  );

	//
	void			endFullScreen(  );



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTalk)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	//
	int				sendKeyEvent(  unsigned  int  key, unsigned  char  ucbDown  );
	virtual  int	processKeyEvent(  UINT  nChar, DWORD  keyData  );
	int				resetKeyEvent(  );

	//
	BOOL  bRefreshBtns_talkerList(  );
	BOOL  bRefreshBtns_listMembers(  );


protected:


	// Generated message map functions
	//{{AFX_MSG(CDlgTalk)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	afx_msg void OnDestroy();
	afx_msg void OnClose();

	//afx_msg void OnItemchangedLISTtask(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkLISTmembers(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickLISTmembers(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm(  WPARAM, LPARAM  );
	afx_msg LRESULT OnQyPostComm(  WPARAM, LPARAM  );
	DECLARE_MESSAGE_MAP()
public:
	
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void Onfullscreen();
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
public:
//	afx_msg void OnLvnItemActivateListtask(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnIsCmd(  UINT nID  );
	afx_msg void OnUpdateIsCmd(CCmdUI *pCmdUI);

	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnBnClickedCancel();
	// afx_msg void OnStnDblclickStaticpeerdesc();
	//  afx_msg void OnStnDblclickStaticmedesc();
	afx_msg void OnMove(int x, int y);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnEnChangeEditfilter();
	afx_msg void OnNMClicktalkerlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedtalkerlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonmicoff();	
	afx_msg void OnNMClickListmembers(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListmembers(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonpermittospeak();
	afx_msg void OnBnClickedButtonnospeaking();
	afx_msg void OnBnClickedButtonsharescreen();
	afx_msg void OnBnClickedButtoncontroldesktop();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNcPaint();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnPaint();
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.





#endif // !defined(AFX_DLGTALK_H__5D6C714C_9AA6_4A2E_983F_E387EE0F80D4__INCLUDED_)
