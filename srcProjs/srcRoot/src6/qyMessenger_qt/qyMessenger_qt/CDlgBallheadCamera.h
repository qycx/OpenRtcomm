#pragma once

#include <QDialog>
#include "ui_CDlgBallheadCamera.h"

class CDlgBallheadCamera : public QDialog
{
	Q_OBJECT

public:
	CDlgBallheadCamera(QWidget *parent = nullptr);
	~CDlgBallheadCamera();

	void send_selLayoutType(QString str);
	void send_selLayoutTypeCancle();

	void pageLoadData(bool is_up);

	void sheetBackgroundImage();
	void Infrared_down();
	void Infrared_up();

public slots:
	void loadData();

	void on_btnBall_up_clicked();
	void on_btnBall_Amp_off_clicked();
	void on_btnBall_2_clicked();
	void on_btnBall_3_clicked();
	void on_btnBall_4_clicked();
	void on_btnBall_5_clicked();
	void on_btnBall_6_clicked();
	void on_btnBall_7_clicked();
	void on_btnBall_8_clicked();
	void on_btnBall_9_clicked();
	void on_btnBall_down_clicked();
	void on_btnBall_close_clicked();




private:
	Ui::CDlgBallheadCameraClass* ui;

	int _pageCur = 1; //当前页  页码
	int _pageCount = 8; //每页显示数量

	QWidget* m_pParent = nullptr;
	QList<QString> _dataList;
	QList<QString> _dataList_ui;
};
