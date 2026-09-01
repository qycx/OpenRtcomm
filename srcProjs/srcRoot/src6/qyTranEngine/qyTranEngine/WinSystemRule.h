#pragma once

#include <QWidget>
#include "ui_WinSystemRule.h"

class WinSystemRule : public QWidget
{
	Q_OBJECT

public:
	WinSystemRule(QWidget *parent = Q_NULLPTR);
	~WinSystemRule();

private:
	Ui::WinSystemRule ui;
};
