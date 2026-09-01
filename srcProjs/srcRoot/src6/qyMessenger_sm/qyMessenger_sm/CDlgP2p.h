#pragma once

#include <QDialog>
#include <QTimer>
#include "ui_CDlgP2p.h"


class CDlgP2p : public QDialog
{
	Q_OBJECT

public:
	CDlgP2p(QWidget *parent = nullptr);
	~CDlgP2p();
	void Infrared_down();
	void Infrared_up();

	void sheetBackgroundImage();



	void on_btnP2p_up_clicked();
	void on_btnP2p_2_clicked();
	void on_btnP2p_3_clicked();
	void on_btnP2p_4_clicked();
	void on_btnP2p_5_clicked();
	void on_btnP2p_6_clicked();
	void on_btnP2p_7_clicked();
	void on_btnP2p_8_clicked();
	void on_btnP2p_9_clicked();
	void on_btnP2p_down_clicked();
	void on_btnP2p_close_clicked();

	void do_close();
	void send_askforP2p(int index);

	void pageLoadData(bool is_up);


public slots:
	void loadData();
	void on_timer_winMethod();

private:
	Ui::CDlgP2pClass *ui;

	bool _bLoad = false;
	QTimer* m_pWinTimer = nullptr;
	int _pageCur = 1; //当前页
	int _pageCount = 8; //显示条数
};
