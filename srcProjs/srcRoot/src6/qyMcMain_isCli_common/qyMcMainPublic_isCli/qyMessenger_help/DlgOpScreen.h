#pragma once


// CDlgOpScreen dialog

class CDlgOpScreen : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOpScreen)

public:
	CDlgOpScreen(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgOpScreen();

// Dialog Data
	enum { IDD = IDD_opScreen };

	//
	//
	struct				{
		HWND			hDlg_shareDynBmps;
		
		int				index_obj_selected;
		//
		
	}					m_var;

	//
	int  refreshCtrlStatus(  );




protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtontoshare();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
