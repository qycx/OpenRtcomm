#pragma once

#include <QWidget>
#include "ui_WinFullPicture.h"

class WinFullPicture : public QWidget
{
	Q_OBJECT

public:
	WinFullPicture(QWidget *parent = Q_NULLPTR);
	~WinFullPicture();

private:
	Ui::WinFullPicture ui;
};
