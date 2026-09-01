#pragma once

#include <QWidget>
#include "ui_CInfraredMenu.h"

class CInfraredMenu : public QWidget
{
	Q_OBJECT

public:
	CInfraredMenu(QWidget *parent = nullptr);
	~CInfraredMenu();

	void Infrared_down();
	void Infrared_up();

	void sheetBackgroundImage();

	QList<QString> _uiList;
	QString _doUi;

public slots:
	void on_menuBtn1_clicked();
	void on_menuBtn2_clicked();
	void on_menuBtn3_clicked();
	void on_menuBtn4_clicked();

private:
	Ui::CInfraredMenuClass *ui;
};
