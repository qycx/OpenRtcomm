#pragma once

#include <QDialog>
#include "ui_CDlgControlPtzLocal.h"



#define IDC_BUTTON_UP                   2280
#define IDC_BUTTON_DOWN                 2281
#define IDC_BUTTON_LEFT                 2282
#define IDC_BUTTON_RIGHT                2283
#define IDC_BUTTON_TOP_LEFT             2284
#define IDC_BUTTON_TOP_RIGHT            2285
#define IDC_BUTTON_BOTTOM_LEFT          2286
#define IDC_BUTTON_BOTTOM_RIGHT         2287
#define IDC_BUTTON_AUTO_SCAN            2288
#define IDC_BUTTON_IRIS_OUT             2269
#define IDC_BUTTON_FOCUS_IN             2270
#define IDC_BUTTON_IRIS_IN              2271
#define IDC_BUTTON_ZOOM_OUT             2272
#define IDC_BUTTON_ZOOM_IN              2273
#define IDC_BUTTON_FOCUS_OUT            2260
#define IDC_BUTTON_noop                 2402

#define		CONST_ptzCmd_null					0
#define		CONST_ptzCmd_up						1
#define		CONST_ptzCmd_down					2
#define		CONST_ptzCmd_left					3
#define		CONST_ptzCmd_right					4
#define		CONST_ptzCmd_topLeft				5
#define		CONST_ptzCmd_topRight				6
#define		CONST_ptzCmd_bottomLeft				7
#define		CONST_ptzCmd_bottomRight			8
#define		CONST_ptzCmd_noop					9
#define		CONST_ptzCmd_focusIn				10
#define		CONST_ptzCmd_focusOut				11
#define		CONST_ptzCmd_irisIn					12
#define		CONST_ptzCmd_irisOut				13
#define		CONST_ptzCmd_zoomIn					14
#define		CONST_ptzCmd_zoomOut				15


class CDlgControlPtzLocal : public QDialog
{
	Q_OBJECT

public:
	CDlgControlPtzLocal(QWidget *parent = nullptr);
	~CDlgControlPtzLocal();


	void dlg_YTBtn_remote(unsigned  char  ucMouseStatus,bool is_local = false);
	

	int getPtzCmdByResourceId(int nResourceID);



	//QIS_ptz_wnd* pPtzWnd;



private:
	Ui::CDlgControlPtzLocalClass* ui;
};
