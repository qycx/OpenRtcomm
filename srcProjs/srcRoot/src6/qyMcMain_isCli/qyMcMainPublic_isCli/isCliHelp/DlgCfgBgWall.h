#pragma once



// CDlgCfgBgWall dialog

class CDlgCfgBgWall : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCfgBgWall)

public:
	CDlgCfgBgWall(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgCfgBgWall();

// Dialog Data
	enum { IDD = IDD_cfgBgWall };

	struct		{
			//
			CWnd					*		m_pParent;
			int								m_nID;
			//  BOOL							bInfoSet;
			BOOL							bCreated;					//  这个标志位用来表明是否Create(  )成功了。成功了，则将资源的释放留给了dlg自己(在PostNcDestroy(  )中delete)
			BOOL							bInited;					//  表明htmlEdit和对话都初始化完了.

			//
			struct							{
				//
				int							iIDC_EDIT_bgWallFile;
				int							iIDC_BUTTON_bgWallFile;
				//
				int							iIDC_EDIT_rows;
				int							iIDC_EDIT_cols;
				int							iIDC_EDIT_pollingInterval;

			}								guiData;

			//
			CButton					*		pBtn_useBgWall;
			CButton					*		pBtn_addBgWallToConf;
			CButton					*		pBtn_joinInBgWall;
			//
			CButton					*		pBtn_autoLayout;
			CButton					*		pBtn_useBgWallFile;

			//
			BgWall_cfg						cfg;
	
			//
			HWND							hDlgTalk_mgr;

	}										m_var;

	//
	BOOL								bSetDlgInfo(  HWND  hDlgTalk_mgr  );
	
	//
	int									get_cfg(  BgWall_cfg  *  pCfg  );
	int									do_get_cfg(  );
	int									refreshCtrls(  );

	//
	BOOL Create(const RECT& rect);
	BOOL  bQuitDlg(  );		


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheckusebgwall();
	afx_msg void OnBnClickedCheckaddbgwalltoconf();
	afx_msg void OnBnClickedCheckjoininbgwall();
	afx_msg void OnBnClickedRadioautolayout();
	afx_msg void OnBnClickedRadiousebgwallfile();
	afx_msg void OnBnClickedButtonbgwallfile();
};
