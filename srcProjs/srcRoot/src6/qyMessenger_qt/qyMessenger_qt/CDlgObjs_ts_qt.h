#pragma once

#include <QDialog>
#include "ui_CDlgObjs_ts_qt.h"

#include	"stdafx.h"

#include	<tchar.h>

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#ifdef  __useMfc__
#include	<afxmt.h>
#include	<afxdb.h>
#endif
//#include	<WinSock2.h>
//
//#include	"qyCommon.h"
//
//#include "qyCommProc.h"
//#include "qnmCommProc.h"
//#include "qnmCommProc_mis.h"
//#include "qyDefs.h"
//#include "qyObjs.h"
//#include "qyTypes.h"

#include "qyMcMainCommon.h"
#include "qyCfg.h"
#include "qyWmComm.h"
#include "qyCommProc.h"



//#include "commonSock.h"
#include "qyDefs_open.h"



//#include "qyAuthCommon.h"
//#include "qyCommonFunc5.h"
#include "qnmCommProc.h"


#include "qnmCommProc_mis.h"

#include "qyMcMainCommon.h"
#include "ctxQmc.h"
#include "qyCusResTemp.h"
#include "qmcStruct_defs.h"

#include "funcsForIsCliHelp.h"

#include <QTimer>

#include "dlgobjsproc.h"
#include "dlgtalkproc.h"

extern void showDlgObjs_ts(HWND hCurTalk, DLG_TALK_var* pMgrVar, QY_wmBuf_command* pWmBuf, TALKER_shadow_mgr* pShadowMgr, HWND	hMgr, HWND	hShow);

QT_BEGIN_NAMESPACE
namespace Ui { class CDlgObjs_ts_qtClass; };
QT_END_NAMESPACE

class CDlgObjs_ts_qt : public QDialog
{
	Q_OBJECT

public:
	CDlgObjs_ts_qt(HWND hWndParent, QDialog* parent = nullptr);
	~CDlgObjs_ts_qt();

	bool OnInitDialog();

	DLG_objs_var	m_var;

	int dlgObjs_OnLbnSelchangeList0(/*HWND  hDlg, void* pVarParam*/);
	int dlgObjs_OnOK(HWND  hDlg, void* pVarParam);

	



public slots:
	void onBtnOkClicked();
	void OnBnClickedCancel();

private:
	Ui::CDlgObjs_ts_qtClass *ui;
};
