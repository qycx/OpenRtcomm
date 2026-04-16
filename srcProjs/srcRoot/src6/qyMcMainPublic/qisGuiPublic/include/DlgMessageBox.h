#pragma once


// CDlgMessageBox dialog

class CDlgMessageBox : public CDialog
{
	DECLARE_DYNAMIC(CDlgMessageBox)

public:
	CDlgMessageBox(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMessageBox();

// Dialog Data
	enum { IDD = IDD_messageBox };

	struct					{
		TCHAR				title[64];
		TCHAR				hint[256];
		UINT				uType;
		//
		UINT				nTimeoutInS;
		//
		BOOL				m_b_willReturn_qyId;
		TCHAR				txt_cancel_btn[128];
		
		//
		BOOL				m_bShow_noPrompt;
		BOOL				m_b_check_noPrompt;

		//
		unsigned  int		uiTimerId;

		UINT				uProgress;

	}						m_var;

	BOOL  bSetDlgInfo(  LPCTSTR  lpText,  LPCTSTR  lpCaption,  UINT  uType,  UINT  nTimeoutInS  );
	BOOL	bQuitDlg(  int  nResult  );

	//
	int  check(  );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonok();
	afx_msg void OnBnClickedButtonno();
	afx_msg void OnBnClickedButtoncancel();
};
