#if !defined(AFX_PPSCANNINGIPSTATUS_H__D15D89AF_510B_4E11_B331_6BBA260FDE3B__INCLUDED_)
#define AFX_PPSCANNINGIPSTATUS_H__D15D89AF_510B_4E11_B331_6BBA260FDE3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpScanningIpStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpScanningIpStatus dialog

class CPpScanningIpStatus : public CPropertyPage
{
	DECLARE_DYNCREATE(CPpScanningIpStatus)

// Construction
public:
	CPpScanningIpStatus();
	~CPpScanningIpStatus();

// Dialog Data
	//{{AFX_DATA(CPpScanningIpStatus)
	enum { IDD = IDD_scanningIpStatus };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpScanningIpStatus)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpScanningIpStatus)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm(  WPARAM  wParam,  LPARAM  lParam  );
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPSCANNINGIPSTATUS_H__D15D89AF_510B_4E11_B331_6BBA260FDE3B__INCLUDED_)
