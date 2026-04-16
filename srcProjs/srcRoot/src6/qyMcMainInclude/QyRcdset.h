#if !defined(AFX_QYRCDSET_H__E7A32686_060D_4361_AC0B_138C05CA95F2__INCLUDED_)
#define AFX_QYRCDSET_H__E7A32686_060D_4361_AC0B_138C05CA95F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QyRcdset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQyRcdset recordset

class CQyRcdset : public CRecordset
{
public:
	CQyRcdset(CDatabase* pDatabase = NULL);
	~CQyRcdset(  );
	DECLARE_DYNAMIC(CQyRcdset)

	CString						m_sqlStr;		// select * from tables
	CStringArray				m_arrayName;
	//  int						m_nColsWidth[QY_MAXCOLS];
	int							m_nDataType[QY_MAXCOLS];
	CArray	< void *, void * >	m_arrayValue;
	
	int		Initialize(  void  *  pDb,  CString  sqlStr,  CString  whereStr,  CString  sortStr,  unsigned  int  nSqlFields,  QY_COLUMNINFO  *  pSqlColumns  );
	void	SetFilter(  CString  whereStr  );
	void    SetSort(  CString  sortStr  );


// Field/Param Data
	//{{AFX_FIELD(CQyRcdset, CRecordset)
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyRcdset)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QYRCDSET_H__E7A32686_060D_4361_AC0B_138C05CA95F2__INCLUDED_)
