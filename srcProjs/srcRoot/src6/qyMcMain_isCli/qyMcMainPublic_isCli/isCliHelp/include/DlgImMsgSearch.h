#if !defined(AFX_DLGIMMSGSEARCH_H__4710AEE0_F7F4_4FC3_A159_D6AF0121F676__INCLUDED_)
#define AFX_DLGIMMSGSEARCH_H__4710AEE0_F7F4_4FC3_A159_D6AF0121F676__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgImMsgSearch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgImMsgSearch dialog

class CDlgImMsgSearch : public CDialog
{
// Construction
public:
	CDlgImMsgSearch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgImMsgSearch)
	enum { IDD = IDD_imMsgSearch };
	CDateTimeCtrl	m_startTimeCtrl;
	CDateTimeCtrl	m_startDateCtrl;
	CDateTimeCtrl	m_endTimeCtrl;
	CDateTimeCtrl	m_endDateCtrl;
	//}}AFX_DATA

	struct							{
			MY_DB_BUF			*	pDbBufs;

			int						iQueryType;
				
			TCHAR					wherePart[CONST_maxSqlBufLen  +  1];
	}								m_var;

	BOOL  bSetDlgInfo(  MY_DB_BUF  *  pDbBufs,  int  iQueryType  );
	int getWherePart(  int  iDbType  );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgImMsgSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgImMsgSearch)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIMMSGSEARCH_H__4710AEE0_F7F4_4FC3_A159_D6AF0121F676__INCLUDED_)
