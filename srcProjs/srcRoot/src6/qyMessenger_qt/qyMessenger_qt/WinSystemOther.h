#pragma once

#include <QWidget>
#include "ui_WinSystemOther.h"
#include <QFocusEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class WinSystemOtherClass; };
QT_END_NAMESPACE

class WinSystemOther : public QWidget
{
	Q_OBJECT

public:
	WinSystemOther(QWidget *parent = nullptr);
	~WinSystemOther();

	void Init();
	void reload();
protected:
	void selectDirectory();
	void save();

	//void showEvent(QShowEvent* event) override {
	//	reload();
	//}

	//void focusInEvent(QFocusEvent* event) override {
	//	
	//	reload();
	//}
	//
	//void changeEvent(QEvent* event)override {
	//	if (event->type() == QEvent::ZOrderChange) {
	//		//qDebug() << "Z-order changed (brought to front)";
	//	}
	//	reload();

	//	QWidget::changeEvent(event);
	//}

private:
	Ui::WinSystemOtherClass *ui;

	bool m_isSave = false;
};
