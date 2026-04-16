#pragma once


		//
		typedef  struct  __dlgGuiData_test_isCli_t						{

			int							iw_org,  ih_org;

			int							iIDC_STATIC_pic0;
			int							iIDC_STATIC_testAvHint;
			int							iIDC_BUTTON_aDev;
			int							iIDC_STATIC_aDev;
			int							iIDC_BUTTON_vDev;
			int							iIDC_STATIC_vDev;
			int							iIDC_BUTTON_cfgCapturePin_v;
			int							iIDC_BUTTON_testAv;
			int							iIDCANCEL;

			RECT						rcIDC_STATIC_pic0;
			RECT						rcIDC_STATIC_testAvHint;
			RECT						rcIDC_BUTTON_aDev;
			RECT						rcIDC_STATIC_aDev;
			RECT						rcIDC_BUTTON_vDev;
			RECT						rcIDC_STATIC_vDev;
			RECT						rcIDC_BUTTON_cfgCapturePin_v;
			RECT						rcIDC_BUTTON_testAv;
			RECT						rcIDCANCEL;
			
		}								DLG_guiData_test_isCli;


// CDlgTest_isCli dialog

class CDlgTest_isCli : public CDialog
{
	DECLARE_DYNAMIC(CDlgTest_isCli)

public:
	CDlgTest_isCli(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgTest_isCli();

// Dialog Data
	enum { IDD = IDD_test_isCli };

	struct								{

		CWnd					*		m_pParent;		
		int								m_nID;
		BOOL							bIncludeACap;						//  2013/03/19
		
		BOOL							bCreated;					//  这个标志位用来表明是否Create(  )成功了。成功了，则将资源的释放留给了dlg自己(在PostNcDestroy(  )中delete)
		BOOL							bInited;					//  表明htmlEdit和对话都初始化完了.

		int								iWndContentType;
		TCHAR							title[128  +  1];
		int								iResId_menu;


		DLG_guiData_test_isCli			guiData;

		//  2014/04/06
		unsigned  char					ucbAutoClip;

		//
		int								iW_pic,  iH_pic;
				
		int								idc;		
		HDC								hDc;
		CAP_IMAGES						images;

		//  2013/10/02
		ZONE_PARAM						zoneParam;

		//		
		void					*		pCapStuff;							//  2009/09/09/16
		//
		int								iMenuId_selectedAudio;				//  2013/04/04			
		int								iMenuId_selectedVideo;
					
		//
		BOOL							bGot_sharedObjIndex_localAv;		//  2009/12/28		
		int								iIndex_sharedObj_localAv;

		//
		MIS_MSGU				*		pMsgBuf_doWnd_guiMsgArrive;			//  2009/12/08

	}									m_var;


	//
	BOOL  bSetDlgInfo(  int  iWndContentType,  int  iSubType,  LPCTSTR  title,  int  iResId_menu  );
	BOOL Create(const RECT& rect);
	BOOL  bQuitDlg(  );		
	int  sizeAllControls(  );
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonadev();
	afx_msg void OnBnClickedButtonvdev();
	afx_msg void OnBnClickedButtoncfgcapturepinv();
	afx_msg void OnBnClickedButtontestav();
	afx_msg void OnDestroy();
	
	virtual  afx_msg LRESULT OnQyComm( WPARAM, LPARAM );
	virtual  afx_msg LRESULT OnQyPostComm( WPARAM, LPARAM );

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnIsCmd(  UINT nID  );
	afx_msg void OnUpdateIsCmd(CCmdUI *pCmdUI);

	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
};
