#include "CInfraredMenu.h"
#include <QGraphicsDropShadowEffect>
#include <qDebug>
//
//#include <QDesktopWidget>
#include	<qscreen.h>

#include <QFile>

CInfraredMenu::CInfraredMenu(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CInfraredMenuClass)
{

	_uiList << "menu1" << "menu2";

	
	
	this->setWindowFlags(Qt::FramelessWindowHint);
	ui->setupUi(this);

	
	//
	sheetBackgroundImage();

	QRect rc = QApplication::desktop()->screenGeometry();
	int aa = this->maximumHeight();
	int bb = this->height();
	move(((rc.width() - this->width()) / 2) - 150 , this->height() + 200);
}

void CInfraredMenu::sheetBackgroundImage() 
{
	QRect rc = QApplication::desktop()->screenGeometry();

	if (rc.width() > 3500) {
		ui->widget->setFixedWidth(858);
		ui->menuBtn1->setFixedSize(858, 200);
		ui->menuBtn2->setFixedSize(858, 200);
		ui->menuBtn3->setFixedSize(858, 200);
		ui->menuBtn4->setFixedSize(858, 200);
		ui->widget->setStyleSheet("QPushButton{border-bottom:1px solid #eee;background:#287FAA;font-size:68px;color:#fff;font-family: Microsoft YaHei;}QPushButton:hover{font-family: Microsoft YaHei;background:#fff;color:#2C9AD0}QPushButton:focus {font-family: Microsoft YaHei;background:#fff;color:#2C9AD0}");
		//ui->label_title->setStyleSheet("font-size:84px;color:#fff;font-weight:bold;background:none;font-family: Microsoft YaHei;");
		//ui->widget->setContentsMargins(20, 20, 20, 20);
		
	}
	else {
		ui->widget->setFixedWidth(429);
		ui->menuBtn1->setFixedSize(429,100);
		ui->menuBtn2->setFixedSize(429,100);
		ui->menuBtn3->setFixedSize(429,100);
		ui->menuBtn4->setFixedSize(429,100);
		ui->widget->setStyleSheet("QPushButton{border-bottom:1px solid #eee;background:#287FAA;font-size:34px;color:#fff;font-family: Microsoft YaHei;}QPushButton:hover{font-family: Microsoft YaHei;background:#fff;color:#2C9AD0}QPushButton:focus {font-family: Microsoft YaHei;background:#fff;color:#2C9AD0}");
		//ui->label_title->setStyleSheet("font-size:42px;color:#fff;font-weight:bold;background:none;font-family: Microsoft YaHei;");
		//ui->widget->setContentsMargins(20, 20, 20, 20);
		
		
	}

}

CInfraredMenu::~CInfraredMenu()
{}
//下箭头
void CInfraredMenu::Infrared_down()
{
	this->focusNextPrevChild(true);
}

//下箭头
void CInfraredMenu::Infrared_up()
{
	this->focusNextPrevChild(false);
}

//点击按钮1
void CInfraredMenu::on_menuBtn1_clicked() 
{
	qDebug() << "menu1";
}
//点击按钮2
void CInfraredMenu::on_menuBtn2_clicked()
{
	qDebug() << "menu2";
}
//点击按钮3
void CInfraredMenu::on_menuBtn3_clicked()
{
	qDebug() << "menu3";
}
//点击按钮4
void CInfraredMenu::on_menuBtn4_clicked()
{
	qDebug() << "menu4";
}