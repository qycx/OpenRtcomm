// qyVDevSampleDlg.h : header file
//

#if !defined(AFX_QYVDEVSAMPLEDLG_H__10107475_684B_47FC_8368_535B6E2DA6EC__INCLUDED_)
#define AFX_QYVDEVSAMPLEDLG_H__10107475_684B_47FC_8368_535B6E2DA6EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CQyVDevSampleDlg dialog

class CQyVDevSampleDlg : public CDialog
{
// Construction
public:
	CQyVDevSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CQyVDevSampleDlg)
	enum { IDD = IDD_QYVDEVSAMPLE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyVDevSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CQyVDevSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnButton1();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QYVDEVSAMPLEDLG_H__10107475_684B_47FC_8368_535B6E2DA6EC__INCLUDED_)
