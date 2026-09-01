#pragma once

#include <QWidget>
#include "ui_WinSystemPwd.h"

class WinSystemPwd : public QWidget
{
	Q_OBJECT

public:
	WinSystemPwd(QWidget *parent = Q_NULLPTR);
	~WinSystemPwd();

private slots:
	void on_pushButton_clicked();

private:
	Ui::WinSystemPwd ui;
};
