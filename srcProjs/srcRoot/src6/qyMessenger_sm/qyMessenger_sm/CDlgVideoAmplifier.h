#pragma once

#include <QDialog>
#include "ui_CDlgVideoAmplifier.h"





class CDlgVideoAmplifier : public QDialog
{
	Q_OBJECT

public:
	CDlgVideoAmplifier(QWidget *parent = nullptr);
	~CDlgVideoAmplifier();


	void sheetBackgroundImage();
	void Infrared_down();
	void Infrared_up();



	void send_selLayoutType(QString str);

	void pageLoadData(bool is_up);

	
signals:
	void to_VideoAmpClose_signal();

public slots:
	void loadData();

	void on_btnAmp_up_clicked();
	void on_btnAmp_2_clicked();
	void on_btnAmp_3_clicked();
	void on_btnAmp_4_clicked();
	void on_btnAmp_5_clicked();
	void on_btnAmp_6_clicked();
	void on_btnAmp_7_clicked();
	void on_btnAmp_8_clicked();
	void on_btnAmp_9_clicked();
	void on_btnAmp_down_clicked();
	void on_btnAmp_close_clicked();

private:
	Ui::CDlgVideoAmplifierClass* ui;
	
	int _pageCur = 1; //当前页  页码
	int _pageCount = 8; //每页显示数量

	QWidget* m_pParent = nullptr;
	QList<QString> _dataList;
};
