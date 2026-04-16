#if !defined(AFX_DLGPROPIMTASK_H__D6960289_4F00_4FE1_8382_A36B24B39193__INCLUDED_)
#define AFX_DLGPROPIMTASK_H__D6960289_4F00_4FE1_8382_A36B24B39193__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPropImTask.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPropImTask dialog

class CDlgPropImTask : public CDialog
{
// Construction
public:
	CDlgPropImTask(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPropImTask)
	enum { IDD = IDD_prop_imTask };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct													{ 
		QY_OBJ_DB								*			pObjDb;
		BOOL												bHisTab;
		int													id;
	}														m_var;

	BOOL  bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  BOOL  bHisTab,  int  id  );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPropImTask)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPropImTask)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROPIMTASK_H__D6960289_4F00_4FE1_8382_A36B24B39193__INCLUDED_)
