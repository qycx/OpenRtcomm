#if !defined(AFX_PPCLEARUPEVENTCOND_H__70F60406_5F1C_4FFF_AB7C_83F7C159AC52__INCLUDED_)
#define AFX_PPCLEARUPEVENTCOND_H__70F60406_5F1C_4FFF_AB7C_83F7C159AC52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpClearupEventCond.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpClearupEventCond dialog

class CPpClearupEventCond : public CPropertyPage
{
	DECLARE_DYNCREATE(CPpClearupEventCond)

// Construction
public:
	CPpClearupEventCond();
	~CPpClearupEventCond();

// Dialog Data
	//{{AFX_DATA(CPpClearupEventCond)
	enum { IDD = IDD_clearupEventCond };
	CDateTimeCtrl	m_startTimeCtrl;
	CDateTimeCtrl	m_startDateCtrl;
	CDateTimeCtrl	m_endTimeCtrl;
	CDateTimeCtrl	m_endDateCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpClearupEventCond)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpClearupEventCond)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPCLEARUPEVENTCOND_H__70F60406_5F1C_4FFF_AB7C_83F7C159AC52__INCLUDED_)
