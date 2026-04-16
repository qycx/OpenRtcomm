#pragma once

#include <QDialog>
#include "ui_CDlgControlPtz.h"

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

class CDlgControlPtz : public QDialog
{
	Q_OBJECT

public:
	CDlgControlPtz(bool b3dLocation, QWidget *parent = nullptr);
	~CDlgControlPtz();


	void set3D(bool flag);

	void sheetBackgroundImage();
	void Infrared_down();
	void Infrared_up();
	void Infrared_input_left_right(QString name, bool isLeft); //×óÓÒ¼ýÍ·

	void dlg_YTBtn_remote(unsigned  char  ucMouseStatus);


	void check_btn_upDown_event();

public slots:
	void on_btnPtz_3d_clicked();
	//void on_btnPtz_up_clicked();
	//void on_btnPtz_down_clicked();
	//void on_btnPtz_left_clicked();
	//void on_btnPtz_right_clicked();
	//void on_btnPtz_zoomUp_clicked();
	//void on_btnPtz_zoomDown_clicked();
	void on_btnPtz_focusUp_clicked();
	void on_btnPtz_focusDown_clicked();
	void on_btnPtz_haloUp_clicked();
	void on_btnPtz_haloDown_clicked();
	void on_btnPtz_close_clicked();


	bool eventFilter(QObject* watched, QEvent* event);
private:
	Ui::CDlgControlPtzClass *ui;

	QWidget* m_pParent = nullptr;



	bool is_btnUPDown_up = false;
	bool is_btnUPDown_down = false;
	bool is_btnUPDown_left = false;
	bool is_btnUPDown_right = false;

	bool is_btnUPDown_zoomUp = false;
	bool is_btnUPDown_zoomDown = false;

	bool m_3dLocation = false;


};
