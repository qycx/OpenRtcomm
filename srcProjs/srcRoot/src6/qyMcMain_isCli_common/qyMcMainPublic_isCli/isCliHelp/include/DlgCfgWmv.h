#pragma once


// CDlgCfgWmv dialog

class CDlgCfgWmv : public CDialog
{
	DECLARE_DYNAMIC(CDlgCfgWmv)

public:
	CDlgCfgWmv(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgCfgWmv();

// Dialog Data
	enum { IDD = IDD_cfgWmv };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
