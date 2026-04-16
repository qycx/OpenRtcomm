#if !defined(AFX_DLGIP_H__4FD66133_CCAF_42A0_A464_2DD95750F886__INCLUDED_)
#define AFX_DLGIP_H__4FD66133_CCAF_42A0_A464_2DD95750F886__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIp dialog

class CDlgIp : public CDialog
{
// Construction
public:
	CDlgIp(CWnd* pParent = NULL);   // standard constructor

	struct				{
		int				type;
		HWND			hParent;
		TCHAR			title[256  +  1];
		TCHAR			okName[64  +  1];
		TCHAR			cancelName[64  +  1];
		char			ipBuf[CONST_qyMaxIpLen  +  1];
	}					m_var;

	BOOL			bSetDlgInfo(  int  type,  HWND  hParent,  LPCTSTR  title,  LPCTSTR  okName,  LPCTSTR  cancelName  );

// Dialog Data
	//{{AFX_DATA(CDlgIp)
	enum { IDD = IDD_ip };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIp)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIP_H__4FD66133_CCAF_42A0_A464_2DD95750F886__INCLUDED_)
