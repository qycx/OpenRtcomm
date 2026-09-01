#pragma once

#include	"dlgObjsProc.h"

// CDlgObjs_ts dialog

class CDlgObjs_ts : public CDialog
{
	DECLARE_DYNAMIC(CDlgObjs_ts)

public:
	CDlgObjs_ts(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgObjs_ts();

// Dialog Data
	enum { IDD = IDD_objs };

	DLG_objs_var	m_var;

	//  void			endFullScreen(  );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtoncontact();
	afx_msg void OnBnClickedButtongroup();
	afx_msg void OnBnClickedButtonstatus();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//  afx_msg void Onfullscreen();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);

	afx_msg void OnIsCmd(  UINT nID  );
	afx_msg void OnUpdateIsCmd(CCmdUI *pCmdUI);

	afx_msg void OnLbnSelchangeList0();
};
