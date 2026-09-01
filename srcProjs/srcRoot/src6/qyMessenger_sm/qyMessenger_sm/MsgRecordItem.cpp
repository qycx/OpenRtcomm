#include "MsgRecordItem.h"
#include <QIcon>

MsgRecordItem::MsgRecordItem(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.btnHead->setIcon(QIcon(":/Resources/Images/WinMain/headMax.png"));
}

void MsgRecordItem::setName(QString strName) {
	ui.labName->setText(strName);
}

void MsgRecordItem::setMsg(QString strMsg) {
	ui.labMsg->setText(strMsg);
}

void MsgRecordItem::set_on() {
	ui.widget->setStyleSheet("background:#eee;");
	ui.labMsg->setStyleSheet("font-weight:bold;font-size:18px; ");
}

void MsgRecordItem::setCursor() {
	ui.widget->setCursor(Qt::PointingHandCursor);
}

MsgRecordItem::~MsgRecordItem()
{
}
