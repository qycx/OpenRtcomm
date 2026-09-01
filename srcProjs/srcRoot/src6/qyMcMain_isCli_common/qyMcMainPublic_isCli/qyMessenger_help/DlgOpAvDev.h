#pragma once


// CDlgOpAvDev dialog

class CDlgOpAvDev : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOpAvDev)

public:
	CDlgOpAvDev(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgOpAvDev();

// Dialog Data
	enum { IDD = IDD_opAvDev };

	//
	struct				{
		HWND			hDlg_shareDynBmps;
		void  *			pCapStuff;
		int				index_obj_selected;
		//
		BOOL			bUnresizable;
		//
		BOOL			bHide_idcCheck_unresizable;

	}					m_var;

	//
	int  refreshCtrlStatus(  );


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnCbnSelchangeComboadev();
	afx_msg void OnCbnSelchangeCombovdev();
	afx_msg void OnBnClickedButtoncfgcapturefilterv();
	afx_msg void OnBnClickedButtoncfgcapturepinv();
	afx_msg void OnBnClickedButtoncfgcrossbarv();
	afx_msg void OnBnClickedButtontoshare();

	afx_msg void OnBnClickedCheckucbunresizable();
	afx_msg void OnBnClickedCheckautoopenonstartup();
	afx_msg void OnBnClickedCancel();
};
