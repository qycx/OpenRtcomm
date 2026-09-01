#pragma once

#include <QDialog>
#include "ui_WinSystemAbout.h"


class WinSystemAbout : public QDialog
{
	Q_OBJECT

public:
	WinSystemAbout(QWidget *parent = Q_NULLPTR);
	~WinSystemAbout();

private:
	Ui::WinSystemAbout ui;
};
