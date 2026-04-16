#if !defined(AFX_DLGSHHGPCPROPERTIES_H__418C5550_376F_4317_A1F8_48911EB7D05A__INCLUDED_)
#define AFX_DLGSHHGPCPROPERTIES_H__418C5550_376F_4317_A1F8_48911EB7D05A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgShhgPcProperties.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgShhgPcProperties dialog

class CDlgShhgPcProperties : public CDialog
{
// Construction
public:
	CDlgShhgPcProperties(CWnd* pParent = NULL);   // standard constructor

	struct  {
			QY_OBJ_DB						*	pObjDb;
			int									iObjType;

			union								{
                struct							{
					char						mac[12  +  1];
					//  
					QNM_PC_INFO					info;
					QNM_REG_INFO				regInfo;
				}								pc;

			}							u;

	}									m_var;

	BOOL  bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  int  iObjType,  char  *  mac0  );

// Dialog Data
	//{{AFX_DATA(CDlgShhgPcProperties)
	enum { IDD = IDD_shhgPcProperties };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgShhgPcProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgShhgPcProperties)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSHHGPCPROPERTIES_H__418C5550_376F_4317_A1F8_48911EB7D05A__INCLUDED_)
