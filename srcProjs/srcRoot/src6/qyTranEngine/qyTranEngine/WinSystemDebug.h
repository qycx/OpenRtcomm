#pragma once

#include <QWidget>
#include "ui_WinSystemDebug.h"

class WinSystemDebug : public QWidget
{
	Q_OBJECT

public:
	WinSystemDebug(QWidget *parent = Q_NULLPTR);
	~WinSystemDebug();

public slots:
	 void on_pushButton_clicked();

private:
	Ui::WinSystemDebug ui;
};
