#pragma once



// CDlgProgress dialog

class CDlgProgress : public CDialog
{
	DECLARE_DYNAMIC(CDlgProgress)

public:
	CDlgProgress(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgProgress();

// Dialog Data
	enum { IDD = IDD_progress };

	//
	struct					{
		//
		QY_PROGRESS		*	pProgress;
		QNM_CUSRES_INFO	*	pCusResInfo;

		//
		TCHAR				title[128];
		TCHAR				progressTxt[128];
		int					nStep_finished;
		BOOL				canUsrOk;
		int					iIndex_shmCmd;
		unsigned  int		uiTranNo;
		PF_commonHandler	pf_doProgress;

		unsigned  int		uiTimerId;

		int					iProgress;

	}						m_var;

	//
	BOOL	bSetDlgInfo(  LPCTSTR  title,  LPCTSTR  progressTxt,  int  nStep_finished,  int  iIndex_shmCmd,  unsigned  int  uiTranNo  =  0,  BOOL  canUsrOk  =  FALSE,  PF_commonHandler  pf_doProgress  =  NULL  );
	BOOL	bQuitDlg(  int  nResult  );


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnQyPostComm(  WPARAM, LPARAM  );

};
