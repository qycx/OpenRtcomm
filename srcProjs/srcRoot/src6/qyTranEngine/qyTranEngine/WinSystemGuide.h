#pragma once

#include <QWidget>
#include "ui_WinSystemGuide.h"

class WinSystemGuide : public QWidget
{
	Q_OBJECT

public:
	WinSystemGuide(QWidget *parent = Q_NULLPTR);
	~WinSystemGuide();

private:
	Ui::WinSystemGuide ui;
};
