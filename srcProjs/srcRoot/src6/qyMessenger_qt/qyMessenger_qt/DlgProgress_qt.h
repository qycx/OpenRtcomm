#pragma once

#include <QWidget>
#include	<qdialog.h>
#include "ui_DlgProgress_qt.h"

#include	"stdafx.h"
#include	"qyMcMainCommon_qt.h"


class DlgProgress_qt : public QDialog
{
	Q_OBJECT

	//
		//
public:
	struct {
		//
		QY_PROGRESS* pProgress;
		QNM_CUSRES_INFO* pCusResInfo;

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

		//
		int					iRet;

	}						m_var;

	//
	QTimer * m_pWinTimer;

	//
public:
	BOOL	bSetDlgInfo(LPCTSTR  title, LPCTSTR  progressTxt, int  nStep_finished, int  iIndex_shmCmd, unsigned  int  uiTranNo = 0, BOOL  canUsrOk = FALSE, PF_commonHandler  pf_doProgress = NULL);
	BOOL	bQuitDlg(int  nResult);


public:
	DlgProgress_qt(QWidget *parent = Q_NULLPTR);
	~DlgProgress_qt();


	bool nativeEvent(const QByteArray& eventType, void* message, long* result);
	bool postMessageQt(MSG* message, long* result);

	//
	LRESULT OnQyPostComm(WPARAM, LPARAM);

private slots:
	//
	void on_timer_winMethod();


private:
	Ui::DlgProgress_qt *ui;
};
