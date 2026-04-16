#pragma once


#include	"qyStatic.h"

//  #include	"dlgTalkProc.h"

//
//#include	"myresource.h"

#include	"dlgmsgToolProc.h"


// CDlgMsgTool dialog

class CDlgMsgTool : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMsgTool)

public:
	CDlgMsgTool(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMsgTool();

// Dialog Data
	enum { IDD = IDD_msgTool };

	//
	DLG_msgTool_var							m_var;


	BOOL  bSetInfo(  BOOL  bUseHtmlEdit  );
	BOOL Create(const RECT& rect);
	BOOL  bQuitDlg(  );		



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual void PostNcDestroy();
	afx_msg LRESULT OnQyComm(  WPARAM, LPARAM  );
	afx_msg LRESULT OnQyPostComm(  WPARAM, LPARAM  );

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLvnItemchangedListtask(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
