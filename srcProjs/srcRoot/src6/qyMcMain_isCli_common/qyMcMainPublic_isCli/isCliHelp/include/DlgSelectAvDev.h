#pragma once


// CDlgSelectAvDev dialog

class CDlgSelectAvDev : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelectAvDev)

public:
	CDlgSelectAvDev(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSelectAvDev();

// Dialog Data
	enum { IDD = IDD_selectAvDev };

	struct				{
		void  *			pCapStuff;
		int				iMenuId_selected;
		//
		BOOL			bUnresizable;
		//
		BOOL			bHide_idcCheck_unresizable;

	}					m_var;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnCbnSelchangeComboadev();
	afx_msg void OnCbnSelchangeCombovdev();
	afx_msg void OnBnClickedButtoncfgcapturefilterv();
	afx_msg void OnBnClickedButtoncfgcapturepinv();
	afx_msg void OnBnClickedButtoncfgcrossbarv();
};
