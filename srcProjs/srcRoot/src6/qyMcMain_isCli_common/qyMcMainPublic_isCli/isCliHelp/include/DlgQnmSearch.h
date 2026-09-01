#if !defined(AFX_DLGQNMSEARCH_H__9D7713AB_3280_475A_8A9F_835258633A9A__INCLUDED_)
#define AFX_DLGQNMSEARCH_H__9D7713AB_3280_475A_8A9F_835258633A9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmSearch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmSearch dialog

class CDlgQnmSearch : public CDialog
{
// Construction
public:
	CDlgQnmSearch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQnmSearch)
	enum { IDD = IDD_qnmSearch };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct				{
			int			iQueryType;
	}					m_var;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmSearch)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMSEARCH_H__9D7713AB_3280_475A_8A9F_835258633A9A__INCLUDED_)
