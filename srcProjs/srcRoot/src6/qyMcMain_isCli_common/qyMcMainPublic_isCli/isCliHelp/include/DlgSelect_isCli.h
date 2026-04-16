#if !defined(AFX_DLGSELECT_H__22763F59_962F_41C7_BB0D_4F96B2FDD27A__INCLUDED_)
#define AFX_DLGSELECT_H__22763F59_962F_41C7_BB0D_4F96B2FDD27A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelect.h : header file
//

#include	"dlgSelect_isCli_public.h"



/////////////////////////////////////////////////////////////////////////////
// CDlgSelect_isCli dialog

class CDlgSelect_isCli : public CDialog
{
// Construction
public:
	CDlgSelect_isCli(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSelect_isCli)
	enum { IDD = IDD_select_isCli };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct								{
		int								iSelectType;
		int								iObjType;
		QY_OBJ_DB					*	pObjDb;
		TCHAR							hint[255  +  1];

		//
		TCHAR							misServName[CONST_maxMisServNameLen  +  1];
		union							{
			struct						{
				QY_MESSENGER_ID			idInfo_grp;
			}							selectImGrpMem;
		}								inputU;

		//
		DlgSelect_isCli_o_U				u;
		
	}									m_var;
	
	BOOL			bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  int  iSelectType,  int  iObjType,  LPCTSTR  hint,  void  *  p0,  void  *  p1  );  

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSelect_isCli)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSelect_isCli)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSELECT_H__22763F59_962F_41C7_BB0D_4F96B2FDD27A__INCLUDED_)
