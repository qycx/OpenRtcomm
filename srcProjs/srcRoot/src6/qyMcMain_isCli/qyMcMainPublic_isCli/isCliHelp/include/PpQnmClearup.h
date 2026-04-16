#if !defined(AFX_PPQNMCLEARUP_H__7FDCC4B4_8737_4170_A273_51CE5B59ACBB__INCLUDED_)
#define AFX_PPQNMCLEARUP_H__7FDCC4B4_8737_4170_A273_51CE5B59ACBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpQnmClearup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpQnmClearup dialog

class CPpQnmClearup : public CPropertyPage
{
	DECLARE_DYNCREATE(CPpQnmClearup)

// Construction
public:
	CPpQnmClearup();
	~CPpQnmClearup();

// Dialog Data
	//{{AFX_DATA(CPpQnmClearup)
	enum { IDD = IDD_qnmClearup };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpQnmClearup)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpQnmClearup)
	afx_msg void OnRADIOclearupScannedIp();
	afx_msg void OnRADIOclearupEvent();
	afx_msg void OnRADIOprocModuleKnowlege();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedRadioprocregistryknowlege();
//	afx_msg void OnBnClickedRadioprocimmsg();
	afx_msg void OnBnClickedRadioprocimmsg();
	afx_msg void OnBnClickedRadioprocimhistask();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPQNMCLEARUP_H__7FDCC4B4_8737_4170_A273_51CE5B59ACBB__INCLUDED_)
