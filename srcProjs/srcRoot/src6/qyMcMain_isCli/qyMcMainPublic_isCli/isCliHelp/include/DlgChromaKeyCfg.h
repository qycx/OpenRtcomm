#pragma once

#include	"imgProcessPublic.h"
#include	"qystatic.h"
#include "afxcmn.h"


// CDlgChromaKeyCfg dialog

class CDlgChromaKeyCfg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgChromaKeyCfg)

public:
	CDlgChromaKeyCfg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgChromaKeyCfg();

// Dialog Data
	enum { IDD = IDD_chromaKeyCfg };

	struct		{
			CWnd					*		m_pParent;
			int								m_nID;
			BOOL							bInfoSet;
			BOOL							bCreated;					//  这个标志位用来表明是否Create(  )成功了。成功了，则将资源的释放留给了dlg自己(在PostNcDestroy(  )中delete)
			BOOL							bInited;					//  表明htmlEdit和对话都初始化完了.

			//
			HWND							hWnd_img;
			int								idc_img;					//  2013/09/29;

			//
			int								iWndContentType;
			int								iWndContentSubType;
			//
			TCHAR							title[64];

			//
			int								idcColor;
			int								idcColor_org;
			int								idcColor_keyed;

			//
			COLORREF						color_org;
			COLORREF						color_keyed;


			//
			HBITMAP							hBmp_btns[1];

			//
			BOOL							bKeyingAFrame;	//  InTheWindow;
			BOOL							bPickColor;
			int								iCurIdc;
			unsigned int					x,y;
			unsigned short					usKeyIndex;
			IMG_key							curKey;
			IMG_process_cfg					cfg;


	}			m_var;

	//
	CQyStatic	m_static_color;
	CQyStatic	m_static_color_org;
	CQyStatic	m_static_color_keyed;

	//
	BOOL  bSetDlgInfo(  int  iWndContentType,  int  iSubType,  LPCTSTR  title  );
	BOOL  bShowPolicy(  );	
	//
	BOOL Create(const RECT& rect);
	BOOL  bQuitDlg(  );		
	int  sizeAllControls(  );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeListchromakey();

	afx_msg void OnEnSetfocusEditkeyr();
	afx_msg void OnEnSetfocusEditkeyg();
	afx_msg void OnEnSetfocusEditkeyb();
	afx_msg void OnEnSetfocusEditkeytola();
	afx_msg void OnEnSetfocusEditkeydistance();
	afx_msg void OnEnSetfocusEditminrgb();
	afx_msg void OnEnSetfocusEditmins();
	afx_msg void OnEnSetfocusEditminl();
	afx_msg void OnEnSetfocusEditmaxl();
	afx_msg void OnEnSetfocusEditfr();
	afx_msg void OnEnSetfocusEditedgedistance();
	afx_msg void OnEnChangeEditkeyr();
	afx_msg void OnEnChangeEditkeyg();
	afx_msg void OnEnChangeEditkeyb();
	afx_msg void OnEnChangeEditkeytola();
	afx_msg void OnEnChangeEditkeydistance();
	afx_msg void OnEnChangeEditminrgb();
	afx_msg void OnEnChangeEditmins();
	afx_msg void OnEnChangeEditminl();
	afx_msg void OnEnChangeEditmaxl();
#if 0
	afx_msg void OnBnClickedChecksmooth();
	afx_msg void OnEnChangeEditfr();
	afx_msg void OnEnChangeEditedgedistance();
	afx_msg void OnBnClickedCheckedgecolor();
#endif
	afx_msg void OnEnChangeEditx();
	afx_msg void OnEnChangeEdity();

	afx_msg void OnDeltaposSpinplusint(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinplusfloat(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedCheckusechromakey();
	afx_msg void OnBnClickedCheckkeyingaframe();
	afx_msg void OnBnClickedCheckpick();

	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedButtonsave();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonrestoredefaultsettings();
	afx_msg void OnEnSetfocusEditx();
	afx_msg void OnEnSetfocusEdity();
	afx_msg void OnNMCustomdrawSliderpreblur(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderpostblur(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slider_preBlur;
	CSliderCtrl m_slider_postBlur;
	afx_msg void OnNMCustomdrawSliderkeytola(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderkeytolb(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slider_key_tola;
	CSliderCtrl m_slider_key_tolb;
	afx_msg void OnNMCustomdrawSlidergamma(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slider_gamma;
};
