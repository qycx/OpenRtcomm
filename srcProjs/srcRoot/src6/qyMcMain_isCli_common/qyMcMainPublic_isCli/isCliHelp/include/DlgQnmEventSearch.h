#if !defined(AFX_DLGQNMEVENTSEARCH_H__FB0F7766_91C4_4E93_9CA3_6DABD8137413__INCLUDED_)
#define AFX_DLGQNMEVENTSEARCH_H__FB0F7766_91C4_4E93_9CA3_6DABD8137413__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmEventSearch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmEventSearch dialog

class CDlgQnmEventSearch : public CDialog
{
// Construction
public:
	CDlgQnmEventSearch(CWnd* pParent = NULL);   // standard constructor

	CQyRestrictEdit		m_edits[CONST_qnmMaxSearchFields];

// Dialog Data
	//{{AFX_DATA(CDlgQnmEventSearch)
	enum { IDD = IDD_qnmEventSearch };
	CDateTimeCtrl	m_startTimeCtrl;
	CDateTimeCtrl	m_endTimeCtrl;
	CDateTimeCtrl	m_endDateCtrl;
	CDateTimeCtrl	m_startDateCtrl;
	CIPAddressCtrl	m_ip;
	CString	m_mac;
	//}}AFX_DATA

	struct				{

		MY_DB_BUF	*	pDbBufs;

		int				iQueryType;
		//  TCHAR			tabName[256];
		int				iEventType;
		TCHAR			eventTypeName[256];
		TCHAR			wherePart[CONST_qyMaxSqlClauseLen  +  1];
		TCHAR			sortPart[CONST_qyMaxSqlClauseLen  +  1];

		QY_IDCITEM	*	pEventListSearchTable0;
		QY_DMITEM	*	pEventTypeTable;
		QY_IDCITEM	**	pEventListSearchCb0Tables;
		QY_IDCITEM  **	pEventListSearchCb1Tables;

	}					m_var;

	BOOL  bSetDlgInfo(  MY_DB_BUF  *  pDbBuf,  int  iQueryType  );
	int  getWherePart(  int  iDbType  ); 



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmEventSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmEventSearch)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeCombo0();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMEVENTSEARCH_H__FB0F7766_91C4_4E93_9CA3_6DABD8137413__INCLUDED_)
