#pragma once

#include <QDialog>
#include "ui_CDlgChairmanLayout.h"

class CDlgChairmanLayout : public QDialog
{
	Q_OBJECT

public:
	CDlgChairmanLayout(QWidget *parent = nullptr);
	~CDlgChairmanLayout();

	void send_selLayoutType(QString str);

	void pageLoadData(bool is_up);

	void sheetBackgroundImage();
	void Infrared_down();
	void Infrared_up();

public slots:
	void loadData();

	void on_btnChair_up_clicked();
	void on_btnChair_tile_clicked();
	void on_btnChair_2_clicked();
	void on_btnChair_3_clicked();
	void on_btnChair_4_clicked();
	void on_btnChair_5_clicked();
	void on_btnChair_6_clicked();
	void on_btnChair_7_clicked();
	void on_btnChair_8_clicked();
	void on_btnChair_9_clicked();
	void on_btnChair_down_clicked();
	void on_btnChair_close_clicked();


private:
	Ui::CDlgChairmanLayoutClass *ui;

	int _pageCur = 1; //当前页  页码
	int _pageCount = 8; //每页显示数量

	QWidget* m_pParent = nullptr;
	QList<QString> _dataList;
	QList<QString> _dataList_ui; //显示用
};
