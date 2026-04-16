#pragma once

#include  "myButton.h"

// CDlgSelectAvCompressor dialog

class CDlgSelectAvCompressor : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSelectAvCompressor)

public:
	CDlgSelectAvCompressor(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSelectAvCompressor();

// Dialog Data
	enum { IDD = IDD_selectAvCompressor };

	struct											{
		//HWND										hCurTalk;
		QY_MESSENGER_ID								idInfo;
		unsigned  char								ucbStarter;				//  2014/10/08
		unsigned  int								uiCapType;				//  2014/04/23
		unsigned  int								uiSubCapType;
		int											iCapUsage;				//  2014/11/19
		//
		BOOL										b3D;					//  2014/12/15
		//
		unsigned  short								usConfType;				//  2017/08/25

		//
		unsigned  int								uiObjType;

		//
		int											level;
		//int											level_conf;				//  2014/8/15
		//AV_COMPRESSOR_CFG							compressor;

		//
		TALKER_policy								policy;
		unsigned  char								ucb2Streams;
		//
		int											timeoutInS;
		//
		struct										{			
			int										xPos_screen;  
			int										yPos_screen;
			//
		}											param_mousemove;
		//
		DWORD										dwTickCnt_lastMouseMove;			//  2010/08/29
		//
		TCHAR										title[128];

		//  2014/10/07
		BOOL										bInited_buStatus;
	}												m_var;

	//
	CMyButton	m_buStatus_video4k;
	CMyButton	m_buStatus_1080p;
	CMyButton	m_buStatus_720p;
	CMyButton	m_buStatus_576p;
	CMyButton	m_buStatus_480p;
	CMyButton	m_buStatus_240p;
	CMyButton	m_buStatus_144p;


	//
	BOOL  bSetDlgInfo(  QY_MESSENGER_ID idInfo,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage,  BOOL  b3D,  unsigned  short  usConfType  );
	//
	int  get_iCapUsage_toDisplay(  );
	int  get_level_toDisplay(  );
	//
	BOOL  bShowInfo(  );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtoncfg();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnCbnSelchangeCombocategory();
	afx_msg void OnStnClickedStaticprefer();
	afx_msg void OnBnClickedCheckusebgwall();
	afx_msg void OnBnClickedChecknoprompt();
	afx_msg void OnBnClickedCheckucbmanuallyconfCtrl();
	afx_msg void OnCbnSelchangeCombovideocodec();
	afx_msg void OnEnChangeEditusmaxspeakers();
	afx_msg void OnBnClickedCheck2streams();
	afx_msg void OnBnClickedCheckblyra();
	afx_msg void OnBnClickedButton144p();
	afx_msg void OnBnClickedButton240p();
};
