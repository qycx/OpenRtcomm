
// avConsoleDlg.h : header file
//

#pragma once


// CavConsoleDlg dialog
class CavConsoleDlg : public CDialogEx
{
// Construction
public:
	CavConsoleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_AVCONSOLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButtonretrieveusrs();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg LRESULT OnMyPostComm(  WPARAM, LPARAM  );

	afx_msg void OnBnClickedButtonretrievedynbmps();

	afx_msg void OnBnClickedButtonview104screen1full();
	afx_msg void OnBnClickedButtonclose104screen1();
	afx_msg void OnBnClickedButtonview104screen1normal();
	afx_msg void OnBnClickedButtonmove104screen1();
	afx_msg void OnBnClickedButtonmove104screen1full();
	afx_msg void OnBnClickedButtonmove104screen1hide();

	afx_msg void OnBnClickedButtonview104webcamfull();
	afx_msg void OnBnClickedButtonclose104webcam1();
	afx_msg void OnBnClickedButtonview104webcam1normal();
	afx_msg void OnBnClickedButtonmove104webcam1();
	afx_msg void OnBnClickedButtonmove104webcam1full();
	afx_msg void OnBnClickedButtonmove104webcam1hide();
	afx_msg void OnBnClickedButtonview104av();
	afx_msg void OnBnClickedButtonclose104avtalk();
	afx_msg void OnBnClickedButtonsendto104();
	afx_msg void OnBnClickedButtonview3dwallfull();
	afx_msg void OnBnClickedOk();
};
