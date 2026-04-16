#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDlgMediaControl dialog

class CDlgMediaControl : public CDialog
{
	DECLARE_DYNAMIC(CDlgMediaControl)

public:
	CDlgMediaControl(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMediaControl();

// Dialog Data
	enum { IDD = IDD_mediaControl };

	struct									{
			MC_VAR_common				*	pProcInfo;
			int								iIndex_capBmp;
			int								iIndex_capAudio;
			
			CWnd						*	m_pParent;

			BOOL							bCreated;

#if  0
			CAP_procInfo_mediaFileBmp	*	pCapBmp;
			CAP_procInfo_mediaFileAudio	*	pCapAudio;

			QY_SHARED_OBJ				*	pSharedObj;
#endif
			QM_SHM_CMD					*	pShmCmd;

			//			
			DWORD							dwTickCnt_lastMouseMove;			//  200811/22

			//
			TCHAR							pathBuf[MAX_PATH];

			UINT_PTR						wTimerID;
			int								m_nCurrentFileSelection;
			REFERENCE_TIME					g_rtTotalTime;


	}										m_var;

	BOOL Create(const RECT& rect);

	void  **  get_ppShareMediaFile(  );

	BOOL  CanStep(void);
	void  ConfigureSeekbar();
	void  StartSeekTimer();
	void  StopSeekTimer();
	void  ReadMediaPosition(  );
	void  UpdatePosition(REFERENCE_TIME rtNow);
	void  HandleTrackbar(WPARAM wReq);
	void  FillFileList(LPTSTR pszRootDir);
	void  SelectFile();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	virtual void PostNcDestroy();
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonFramestep();
	afx_msg void OnBnClickedCheckPlaythrough();
	afx_msg void OnBnClickedCheckLoop();
	afx_msg void OnBnClickedCheckMute();
	CSliderCtrl m_Seekbar;
	CComboBox m_ListFiles;
	afx_msg void OnDestroy();
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCbnSelchangeCombomediafile();
};
