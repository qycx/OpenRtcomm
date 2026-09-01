#if !defined(AFX_DLGPROPIMGRP_H__AFFD4753_8AB9_4868_85E5_DD22477E154D__INCLUDED_)
#define AFX_DLGPROPIMGRP_H__AFFD4753_8AB9_4868_85E5_DD22477E154D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPropImGrp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPropImGrp dialog

class CDlgPropImGrp : public CDialog
{
// Construction
public:
	CDlgPropImGrp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPropImGrp)
	enum { IDD = IDD_prop_imGrp };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct										{
		    QY_OBJ_DB						*	pObjDb;

			TCHAR								misServName[CONST_maxMisServNameLen  +  1];
			QY_MESSENGER_ID						idInfo;

	}											m_var;

	BOOL		bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPropImGrp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPropImGrp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROPIMGRP_H__AFFD4753_8AB9_4868_85E5_DD22477E154D__INCLUDED_)
