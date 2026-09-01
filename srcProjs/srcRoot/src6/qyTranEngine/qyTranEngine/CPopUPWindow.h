#pragma once

#include <QDialog>
#include "ui_CPopUPWindow.h"

#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QPoint>
#include <QTimer>
#include <QFont>

class CPopUPWindow : public QDialog
{
	Q_OBJECT

public:
	CPopUPWindow(QWidget *parent = nullptr);
	~CPopUPWindow();

	void showAnimation();
	void addNewMessage(QString str);
private slots:
	void closeAnimation();
	void clearAll();
signals:
	void sigFinished();


private:
	Ui::CPopUPWindowClass ui;

	QDesktopWidget			m_desktop;
	QPropertyAnimation* m_animation;
	QTimer* m_remainTimer;
};
