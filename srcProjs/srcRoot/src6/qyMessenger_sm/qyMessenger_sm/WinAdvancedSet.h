#pragma once

#include <QWidget>
#include "ui_WinAdvancedSet.h"

class WinAdvancedSet : public QWidget
{
	Q_OBJECT

public:
	WinAdvancedSet(QWidget *parent = Q_NULLPTR);
	~WinAdvancedSet();

private:
	Ui::WinAdvancedSet ui;
};
