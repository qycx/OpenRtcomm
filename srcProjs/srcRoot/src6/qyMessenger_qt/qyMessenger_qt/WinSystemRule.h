#pragma once

#include <QWidget>
#include "ui_WinSystemRule.h"

class WinSystemRule : public QWidget
{
	Q_OBJECT

public:
	WinSystemRule(QWidget* parent = Q_NULLPTR);
	~WinSystemRule();
	void writeRegistryValue(const QString& path, const QString& key, const QString& value);
	QString readRegistryValue(const QString& path, const QString& key);
	void reload();
private slots:
	void on_saveBtn_clicked();
private:
	Ui::WinSystemRule ui;

	int _displayCardBox_index;
};
