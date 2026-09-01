#if !defined(AFX_DLGPROPIMMSG_H__8838435A_7ED9_410B_ADCE_8554F9955DBE__INCLUDED_)
#define AFX_DLGPROPIMMSG_H__8838435A_7ED9_410B_ADCE_8554F9955DBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPropImMsg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPropImMsg dialog

class CDlgPropImMsg : public CDialog
{
// Construction
public:
	CDlgPropImMsg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPropImMsg)
	enum { IDD = IDD_prop_imMsg };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	struct													{ 
		QY_OBJ_DB								*			pObjDb;
		int													id;
	}														m_var;

	BOOL  bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  int  id  );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPropImMsg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPropImMsg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROPIMMSG_H__8838435A_7ED9_410B_ADCE_8554F9955DBE__INCLUDED_)
