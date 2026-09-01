#pragma once

#include <QDialog>
#include <QTimer>
#include "ui_CDlgP2pMsg.h"

class CDlgP2pMsg : public QDialog
{
	Q_OBJECT

public:
	CDlgP2pMsg(QWidget *parent = nullptr);
	~CDlgP2pMsg();


	void sheetBackgroundImage();
	void Infrared_input_left_right(QString name, bool isLeft); //左右箭头.


	void on_btn_consent_clicked();
	void on_btn_repulse_clicked();
	
	//
	void do_close();


public slots:
	void on_win_close();

private:
	Ui::CDlgP2pMsgClass *ui;

 	QTimer* m_pWinTimer = nullptr;
	int _closeTime = 30;
};
