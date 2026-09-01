#pragma once

#include <QWidget>
#include "ui_CDlgShareDynBmps_qt.h"

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
//



#include "dlgShareDynBmpsProc.h"

//class SHARE_dynBmps;


QT_BEGIN_NAMESPACE
namespace Ui { class CDlgShareDynBmps_qtClass; };
QT_END_NAMESPACE

class CDlgShareDynBmps_qt : public QWidget
{
	Q_OBJECT

public:
	CDlgShareDynBmps_qt(const std::string& rtspUrl, QWidget *parent = nullptr);
	~CDlgShareDynBmps_qt();

	int  toShareScreen_func(int  index_pShare_mem);
	SHARE_dynBmps* getShareDynBmpsBySth(int  uiObjType);

	int  refreshShareCfg_screen(unsigned  int  uiObjType, int  index_obj);
	int  refreshShareCfg_webcam(unsigned  int  uiObjType, int  index_obj);


	int  refreshShareStatus(unsigned  int  uiObjType);

	int  reloadOnvifList();
	int  reloadOnvifList_bak();

	int  displayOnvifList();

	int  toShareScreen(int  index_pShare_mem);

	int  refreshCtrlStatus(int index_obj_selected);

	int  closeTaskAv(unsigned  int  uiObjType, int  index_pShare_mem);

	int  sizeAllControls();

	BOOL dlgShareDynBmps_Create(const RECT& rect);
	//int  dlgTalk_OnInitDialog(HWND  hDlgTalk, void* pDLG_TALK_var);
	int  dlgShareDynBmps_OnDestroy();
	int  dlgShareDynBmps_OnInitDialog();
	int  dlgShareDynBmps_OnQyComm(HWND  hDlg, void* pDLG_Share_var, WPARAM  wParam, LPARAM  lParam);
	int  dlgShareDynBmps_OnQyPostComm(HWND  pDlg, void* pDLG_Share_var, WPARAM  wParam, LPARAM  lParam);

	int  refreshIpDevs();

	bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result);

	

	void onTimer();

	HWND m_hWnd;

	DLG_shareDynBmps_var								m_var;

	QTimer* timer = nullptr;

	struct {
		int				objType;

		//
		HWND			hDlg_shareDynBmps;
		void* pCapStuff;
		int				index_obj_selected;
		//
		BOOL			bUnresizable;
		//
		BOOL			bHide_idcCheck_unresizable;

	}					m_varAVDev;

protected:
	int  toShareWebcam(int objType, int  index_pShare_mem);
	int  toShareWebcam_func(int  objType, int  index_pShare_mem, void** ppCapStuff, int  iMenuId_v, BOOL  bUnresizable);

	int shareWebcam(int objType, int  index_pShare_mem);

private slots:
	void onShareScreenButtonClicked();
	void onWebcam1ButtonClicked();
	void onIcButtonClicked();

private:
	Ui::CDlgShareDynBmps_qtClass *ui;

	std::string m_rtspUrl;

	
};
