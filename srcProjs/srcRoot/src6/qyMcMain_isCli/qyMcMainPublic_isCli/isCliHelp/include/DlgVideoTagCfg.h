#pragma once

#include	"subtitles.h"


//
typedef  struct  __dlgGuiDataVideoTagCfg_t							{
				 BOOL												bInited;


				 int												iw_org,  ih_org;
				 int												iIDC_CHECK_showVideoHint;
				 RECT												rcIDC_CHECK_showVideoHint;

				 int												iIDC_CHECK_effectiveImmediately;
				 RECT												rcIDC_CHECK_effectiveImmediately;

				 int												iIDC_BUTTON_useDefault;
				 RECT												rcIDC_BUTTON_useDefault;
				 
				 int												iIDC_BUTTON_file;
				 RECT												rcIDC_BUTTON_file;

				 int												iIDC_BUTTON_subtitlesSettings;
				 RECT												rcIDC_BUTTON_subtitlesSettings;

				 struct												{
					 //
					 int											iIDC_STATIC_subtitle;
					 RECT											rcIDC_STATIC_subtitle;
					 int											iIDC_EDIT_subtitle;
					 RECT											rcIDC_EDIT_subtitle;
		 
				 }													mems[MAX_subtitlesCfg_mems];


				 int												iIDOK;
				 RECT												rcIDOK;
				 int												iIDCANCEL;
				 RECT												rcIDCANCEL;
				 int												iIDC_BUTTON_emptyTxt;
				 RECT												rcIDC_BUTTON_emptyTxt;

				 //
				 int												iIDC_LIST_subtitles;
				 RECT												rcIDC_LIST_subtitles;


}		 DLG_guiData_subtitleCfg;

// CDlgVideoTagCfg dialog

class CDlgVideoTagCfg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVideoTagCfg)

public:
	CDlgVideoTagCfg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgVideoTagCfg();

// Dialog Data
	enum { IDD = IDD_videoTagCfg };

	struct			{
			CWnd					*		m_pParent;
			int								m_nID;
			//  BOOL							bInfoSet;
			BOOL							bCreated;					//  这个标志位用来表明是否Create(  )成功了。成功了，则将资源的释放留给了dlg自己(在PostNcDestroy(  )中delete)

			//
			int								iSharedObjType;
			int								iCapType;
			int								iCapSubType;
			int								iUsage;
			HWND							hDlgTalk_mgr;

			//
			DLG_guiData_subtitleCfg			guiData;
			
			//SUBTITLES_cfg				*	pCurCfg;
			
			SUBTITLES_cfg					old_tagCfgs;
			SUBTITLES_cfg					tagCfgs;
			
			//
			int								iCurLineIndex;

			//
			BOOL							bFileGot;
			
			//
			DLG_syncFlgs					syncFlgs;

	}										m_var;

	BOOL	bSetInfo(  int  iSharedObjType,  int  iCapType,  int  iCapSubType,  int  iUsage  );
	BOOL Create(const RECT& rect);
	BOOL  bQuitDlg(  );		
	
	BOOL	bShowInfo(  );
	BOOL	bShowInfo_mem(  int  index  );
	BOOL	bShowInfo_btn_subtitlesSettings(  );
	int		sizeAllControls(  float  fxSize,  float  fySize);

	int  doOnEnChangeEditsubtitle(  int  index  );
	int  doOnBnClickedButtonselect(  int  index  );

	//		
	int  mysubtitlesCfg_modify(  SUBTITLES_cfg  *  pCfg,  DWORD  dwTickCnt,  BOOL  bForce  );


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	afx_msg void OnClose();
	virtual void OnCancel();
	afx_msg void OnBnClickedButtonemptytxt();
	afx_msg void OnBnClickedCheckeffectiveimmediately();
	afx_msg void OnBnClickedCheckshowvideohint();
	afx_msg void OnBnClickedButtonusedefault();
	afx_msg void OnBnClickedButtonfile();
	afx_msg void OnLbnSelchangeListsubtitles();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//  afx_msg void OnBnClickedButtonmore();
#if  0
	afx_msg void OnBnClickedButtonselect0();
	afx_msg void OnBnClickedButtonselect1();
	afx_msg void OnBnClickedButtonselect2();
	afx_msg void OnBnClickedButtonselect3();
	afx_msg void OnBnClickedButtonselect4();
	afx_msg void OnBnClickedButtonselect5();
	afx_msg void OnBnClickedButtonselect6();
	afx_msg void OnBnClickedButtonselect7();
	afx_msg void OnBnClickedButtonselect8();
	afx_msg void OnBnClickedButtonselect9();
	afx_msg void OnBnClickedButtonselect10();
	afx_msg void OnBnClickedButtonselect11();
#endif
	afx_msg void OnEnChangeEditsubtitle0();
	afx_msg void OnEnChangeEditsubtitle1();
	afx_msg void OnEnChangeEditsubtitle2();
	afx_msg void OnEnChangeEditsubtitle3();
	afx_msg void OnEnChangeEditsubtitle4();
	afx_msg void OnEnChangeEditsubtitle5();
	afx_msg void OnEnChangeEditsubtitle6();
	afx_msg void OnEnChangeEditsubtitle7();
	afx_msg void OnEnChangeEditsubtitle8();
	afx_msg void OnEnChangeEditsubtitle9();
	afx_msg void OnEnChangeEditsubtitle10();
	afx_msg void OnEnChangeEditsubtitle11();
	afx_msg void OnEnSetfocusEditsubtitle0();
	afx_msg void OnBnClickedButtonsubtitlessettings();
	afx_msg void OnEnSetfocusEditsubtitle1();
	afx_msg void OnEnSetfocusEditsubtitle2();
	afx_msg void OnEnSetfocusEditsubtitle3();
	afx_msg void OnEnSetfocusEditsubtitle4();
	afx_msg void OnEnSetfocusEditsubtitle5();
	afx_msg void OnEnSetfocusEditsubtitle6();
	afx_msg void OnEnSetfocusEditsubtitle7();
	afx_msg void OnEnSetfocusEditsubtitle8();
	afx_msg void OnEnSetfocusEditsubtitle9();
	afx_msg void OnEnSetfocusEditsubtitle10();
	afx_msg void OnEnSetfocusEditsubtitle11();
};
