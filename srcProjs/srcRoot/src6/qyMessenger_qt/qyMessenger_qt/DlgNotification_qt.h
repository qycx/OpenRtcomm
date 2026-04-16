#pragma once

#include <QWidget>
#include "ui_DlgNotification_qt.h"
#include	"stdafx.h"
#include <qyMcMainCommon_qt.h>
#include	"ctxQmc.h"

#include <intsafe.h>

class DlgNotification_qt : public QWidget
{
	Q_OBJECT

public:
	DlgNotification_qt(QWidget *parent = Q_NULLPTR);
	~DlgNotification_qt();
	struct {
		//
		unsigned  short					usTimeInMsToPop;
		int								nTimerIntervalInMs;

		//
		MIS_CNT* pMisCnt;

		//
		int								idc;
		HDC								hDc;
		CAP_IMAGES						images;

		int								idcHint;
		CAP_RECT						rectHint;

		//GENERIC_Q						q;
		//BOOL							bInited_q;

		//
		TCHAR							tBuf[128];

		//		
		DWORD							dwTickCnt_initDialog;
		BOOL							bWaiting;

		//
		DWORD							dwTickCnt_allDisplayed;
		BOOL							bClosing;

		//
		int								nHeight;


	}									m_var;

	//
	QTimer* m_pWinTimer;

	//
	BOOL		bAddNotification_qt( MIS_MSG_taskStatus * pStatus );

//protected:
//
//	DECLARE_MESSAGE_MAP();
public:
//	virtual bool OnInitDialog();
	 void OnTimer(UINT_PTR nIDEvent);
//	 void OnPaint();
//	 HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	 void OnDestroy();
//	 void OnLButtonDown(UINT nFlags, CPoint point);

private slots:
	void on_timer_winMethod();


private:
	Ui::DlgNotification_qt ui;
};
