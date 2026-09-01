#if !defined(AFX_DLGQNMSENDHINT_H__D23A2498_F65B_47F2_994B_0D0319162322__INCLUDED_)
#define AFX_DLGQNMSENDHINT_H__D23A2498_F65B_47F2_994B_0D0319162322__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmSendHint.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmSendHint dialog

class CDlgQnmSendHint : public CDialog
{
// Construction
public:
	CDlgQnmSendHint(CWnd* pParent = NULL);   // standard constructor

	struct			{
		TCHAR		staticHint[255  +  1];
		//
		TCHAR		hint[255  +  1];
	}				m_var;

// Dialog Data
	//{{AFX_DATA(CDlgQnmSendHint)
	enum { IDD = IDD_qnmSendHint };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmSendHint)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmSendHint)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMSENDHINT_H__D23A2498_F65B_47F2_994B_0D0319162322__INCLUDED_)
