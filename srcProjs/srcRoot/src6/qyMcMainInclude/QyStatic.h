
#if !defined( __QYSTATIC_H__ )
#define __QYSTATIC_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QyStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQyStatic window

class CQyStatic : public CStatic
{
// Construction
public:
	CQyStatic();

// Attributes
public:

	struct					{
		int					idc;
		PF_commonHandler	pf_OnPaint;			//  CWnd  *  pParent,  CWnd  *  pCtrl,  CDC  *  pDc
	}						m_var;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQyStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CQyStatic)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};

typedef  class  CQyStatic  *		LP_QyStatic;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(  __QYSTATIC_H__  )
