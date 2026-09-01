#pragma once

#include	"qmcStruct_defs.h"
#include	"dlgDesktopsMon.h"

// CDlgNotification dialog



class CDlgNotification : public CDlgDesktopsMon
{

public:
	CDlgNotification(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgNotification();

	struct								{
		//
		unsigned  short					usTimeInMsToPop;
		int								nTimerIntervalInMs;
		
		//
		MIS_CNT					*		pMisCnt;

		//
		int								idc;
		HDC								hDc;
		CAP_IMAGES						images;

		int								idcHint;
		CAP_RECT						rectHint;

		GENERIC_Q						q;
		BOOL							bInited_q;

		//		
		DWORD							dwTickCnt_initDialog;
		BOOL							bWaiting;

		//
		DWORD							dwTickCnt_allDisplayed;
		BOOL							bClosing;

		//
		int								nHeight;


	}									m_var;

	CBrush								m_brush_bk;
	CQyStatic							m_static_hint;

#ifdef  __DEBUG__
		int								printQ(  );
#endif

	BOOL								mybVideoExists(  );
	BOOL								bAddNotification(  MIS_MSG_taskStatus  *  pStatus  );
	BOOL								bRemoveNotification(  QY_MESSENGER_ID	*	pIdInfo_logicalPeer  );


	//  virtual  int	sizeAllControls_dlgDesktopsMon(  RECT  &rc  );
	virtual  int	sizeAllControls(  RECT  rc  );

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
