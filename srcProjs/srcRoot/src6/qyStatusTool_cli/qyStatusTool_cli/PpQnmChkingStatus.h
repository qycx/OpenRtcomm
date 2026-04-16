#if !defined(AFX_PPQNMCHKINGSTATUS_H__84E71CD9_1BC6_41BA_978D_23A2F177A78E__INCLUDED_)
#define AFX_PPQNMCHKINGSTATUS_H__84E71CD9_1BC6_41BA_978D_23A2F177A78E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpQnmChkingStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpQnmChkingStatus dialog

class CPpQnmChkingStatus : public CPropertyPage
{
	DECLARE_DYNCREATE(CPpQnmChkingStatus)

// Construction
public:
	CPpQnmChkingStatus();
	~CPpQnmChkingStatus();

	struct					{
		BOOL				bAutoClearup;
		int					nItems;
		//  unsigned  long		ulSelectedIp;
		TCHAR				selectedWho[128];
		int					iCurSel;
	}						m_var;


// Dialog Data
	//{{AFX_DATA(CPpQnmChkingStatus)
	enum { IDD = IDD_qnmChkingStatus };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpQnmChkingStatus)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpQnmChkingStatus)
	afx_msg void OnCHECKautoClearup();
	afx_msg void OnSelchangeCOMBOselect();
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm(  WPARAM  wParam,  LPARAM  lParam  );
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPQNMCHKINGSTATUS_H__84E71CD9_1BC6_41BA_978D_23A2F177A78E__INCLUDED_)
