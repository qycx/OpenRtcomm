#include "CPopUPWindow.h"

/*
CPopUPWindow::CPopUPWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

CPopUPWindow::~CPopUPWindow()
{}
*/



CPopUPWindow::CPopUPWindow(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->move((m_desktop.availableGeometry().width() - this->width()), m_desktop.availableGeometry().height());//初始化位置到右下角
	ui.textEdit->setStyleSheet("background-color:transparent;border: none;");
	QFont t_font("微软雅黑", 12);
	ui.textEdit->setFont(t_font);
	/*initTitleBar();*/
	//显示弹出框动画
	m_animation = new QPropertyAnimation(this, "pos");//动画属性名按点移动
	m_animation->setDuration(2000);	//设置弹出框显示2秒、在弹回去

	QPoint start(this->x(), this->y());
	QPoint end((m_desktop.availableGeometry().width() - this->width()), (m_desktop.availableGeometry().height() - this->height()));

	//m_animation->setStartValue(QPoint(this->x(), this->y()));
	//m_animation->setEndValue(QPoint((m_desktop.availableGeometry().width() - this->width()), (m_desktop.availableGeometry().height() - this->height())));
	m_animation->setStartValue(start);
	m_animation->setEndValue(end);
	m_remainTimer = new QTimer();
	connect(m_animation, SIGNAL(finished()), this, SLOT(clearAll()));
	connect(m_remainTimer, SIGNAL(timeout()), this, SLOT(closeAnimation()));
}

CPopUPWindow::~CPopUPWindow()
{
	if (m_animation != nullptr) {
		delete m_animation;
		m_animation = nullptr;
	}
	if (m_remainTimer != nullptr) {
		delete m_remainTimer;
		m_remainTimer = nullptr;
	}
	/*if (m_titleBar != nullptr) {
		delete m_titleBar;
		m_titleBar = nullptr;
	}*/
	emit sigFinished();
}


void CPopUPWindow::showAnimation()
{
	if (m_animation->state() == QAbstractAnimation::Running) {
		return;
	}

	m_animation->start();
	if (!m_remainTimer->isActive()) {
		ui.textEdit->clear();
		m_remainTimer->start(8000);//弹出动画2S,停留2S回去
	}
}

void CPopUPWindow::closeAnimation()
{
	//清除Timer指针和信号槽
	m_remainTimer->stop();
	//弹出框回去动画
	QPoint start(this->x(), this->y());
	QPoint end((m_desktop.availableGeometry().width() - this->width()), m_desktop.availableGeometry().height());
	m_animation->setStartValue(start);
	m_animation->setEndValue(end);
	m_animation->start();

}

void CPopUPWindow::clearAll()
{
	closeAnimation();
	hide();
	m_animation->stop();
}

void CPopUPWindow::addNewMessage(QString str)
{
	QString t_str = QString::fromLocal8Bit("震源车%1上线").arg(str);
	ui.textEdit->append(t_str);
}
