#pragma once

#include <QDialog>
#include "ui_CDlgControlPtzLocal.h"

//
#include	<tchar.h>
#include	"qyMcMainCommon_qt.h"


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

class CDlgControlPtzLocal : public QDialog
{
	Q_OBJECT

public:
	CDlgControlPtzLocal(QWidget* parent = nullptr);
	~CDlgControlPtzLocal();


	void dlg_YTBtn_remote(unsigned  char  ucMouseStatus, bool is_local = false);
	void sheetBackgroundImage();

	int getPtzCmdByResourceId(int nResourceID);

	void dlg_YTBtn_remote_3ddw(PTZ_control_cmd* pPtzControlCmd);



	//QIS_ptz_wnd* pPtzWnd;

public slots:
	void on_btnPtz_up_clicked();
	void on_btnPtz_down_clicked();
	void on_btnPtz_left_clicked();
	void on_btnPtz_right_clicked();
	void on_btnPtz_zoomUp_clicked();
	void on_btnPtz_zoomDown_clicked();
	void on_btnPtz_focusUp_clicked();
	void on_btnPtz_focusDown_clicked();
	void on_btnPtz_haloUp_clicked();
	void on_btnPtz_haloDown_clicked();
	void on_btnPtz_close_clicked();

private:
	Ui::CDlgControlPtzLocalClass* ui;
};

