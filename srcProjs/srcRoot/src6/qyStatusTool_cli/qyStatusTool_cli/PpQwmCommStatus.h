#if !defined(AFX_PPQWMCOMMSTATUS_H__A79F75B2_926A_44DD_A52B_ED564EB8F2FE__INCLUDED_)
#define AFX_PPQWMCOMMSTATUS_H__A79F75B2_926A_44DD_A52B_ED564EB8F2FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpQwmCommStatus.h : header file
//
#include	"qyStatusTool.h"

/////////////////////////////////////////////////////////////////////////////
// CPpQwmCommStatus dialog

class CPpQwmCommStatus : public CPropertyPage
{
	DECLARE_DYNCREATE(CPpQwmCommStatus)

// Construction
public:
	CPpQwmCommStatus();
	~CPpQwmCommStatus();

	struct					{
		BOOL				bAutoClearup;
		int					nItems;
		//
		unsigned  long		ulClientIp0;
		//unsigned  long		ulClientIp1;
		TCHAR				filter0Buf[255  +  1];
		TCHAR				filter1Buf[255  +  1];
		//
		MY_filters			filters;
		//
		int					iCurSel;
	}						m_var;

// Dialog Data
	//{{AFX_DATA(CPpQwmCommStatus)
	enum { IDD = IDD_qwmCommStatus };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpQwmCommStatus)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpQwmCommStatus)
	afx_msg void OnSelchangeCOMBOselect();
	afx_msg void OnCHECKautoClearup();
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm(  WPARAM  wParam,  LPARAM  lParam  );
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPQWMCOMMSTATUS_H__A79F75B2_926A_44DD_A52B_ED564EB8F2FE__INCLUDED_)
