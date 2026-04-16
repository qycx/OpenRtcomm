#include "WinSystemSetup.h"
#include <QIcon>
#include	"stdafx.h"
//
#include <CMainFrame.h>
#include	"qyMcMainCommon_qt.h"
#include <string>
#include <ctxQmc_qt.h>
#include <QDebug>
#include "WinSystemRule.h"
#include "WinSystemPwd.h"
#include "WinSystemDebug.h"
#include "WinSystemAbout.h"
#include "WinSystemGuide.h"
//
#define SHADOW_WIDTH 6 // 阴影边框宽度;
WinSystemSetup::WinSystemSetup(QWidget *parent)
	: WinBasic(true,parent)
	,ui(new Ui::WinSystemSetup)
{
	ui->setupUi(this);

	//
	memset(&m_var, 0, sizeof(m_var));
	
	//this->setWindowFlags(Qt::FramelessWindowHint);

	//
	initControl();
}

void WinSystemSetup::initControl()
{
	QRect rc = QApplication::desktop()->screenGeometry();
	if (rc.height() < 800 && rc.width() > 900) {
		int rx = (rc.width() - 700) / 2;
		int ry = (rc.height() - 584) / 2;
		QRect rc1 = QRect(rx, ry, 700, 584);

		this->setGeometry(rc1);
	}


	ui->BtnClose->setIcon(QIcon(":/Resources/Images/Title/sysbtn_close_normal.png"));
	connect(ui->BtnClose,SIGNAL(clicked()),this,SLOT(on_pushBtnSystem_close()));
	
	ui->BtnRule->setText(u8"常规设置");
	connect(ui->BtnRule, SIGNAL(clicked()), this, SLOT(on_btnRule_click()));

	ui->BtnPwd->setText(u8"修改密码");
	connect(ui->BtnPwd, SIGNAL(clicked()), this, SLOT(on_btnPwd_click()));

	ui->BtnDebug->setText(u8"调 试 ");
	connect(ui->BtnDebug, SIGNAL(clicked()), this, SLOT(on_btnDebug_click()));

	ui->BtnGuide->setText(u8"使用指南");
	connect(ui->BtnGuide, SIGNAL(clicked()), this, SLOT(on_btnGuide_click()));

	/*ui->BtnAbout->setText(u8"关 于 ");
	connect(ui->BtnAbout, SIGNAL(clicked()), this, SLOT(on_btnAbout_click()));*/

	//ui->BtnRule->setVisible(false);

	//常规
	WinSystemRule* SystemRule = new WinSystemRule();
	ui->SystemstackedWidget->addWidget(SystemRule);


	//
	ui->SystemstackedWidget->setCurrentIndex(0);

	//修改密码
	WinSystemPwd* SystemPwd = new WinSystemPwd();
	ui->SystemstackedWidget->addWidget(SystemPwd);
	
	//调试
	WinSystemDebug* systemDebug = new WinSystemDebug();
	ui->SystemstackedWidget->addWidget(systemDebug);

	//指南
	WinSystemGuide* systemGuide = new WinSystemGuide();
	ui->SystemstackedWidget->addWidget(systemGuide);
	painterMenu("BtnRule");

	//关于
	/*WinSystemAbout* systemAbout = new WinSystemAbout();
	ui->SystemstackedWidget->addWidget(systemAbout);
	painterMenu("BtnRule");*/
}

WinSystemSetup::~WinSystemSetup()
{
	int  ii = 0;
}

//常规设置
void WinSystemSetup::on_btnRule_click() 
{
	
	ui->SystemstackedWidget->setCurrentIndex(0);
	painterMenu("BtnRule");
}
//修改密码
void WinSystemSetup::on_btnPwd_click() 
{
	ui->SystemstackedWidget->setCurrentIndex(1);

	painterMenu("BtnPwd");
}
//调试
void WinSystemSetup::on_btnDebug_click()
{
	painterMenu("BtnDebug");
	ui->SystemstackedWidget->setCurrentIndex(2);
}
//使用指南
void WinSystemSetup::on_btnGuide_click()
{

	painterMenu("BtnGuide");
	ui->SystemstackedWidget->setCurrentIndex(3);
//	QWidget* weig = new QWidget();
//	QLabel* lab = new QLabel(weig);
//	lab->setText("请访问https://bbs.qycx.com 获取帮助");
////	weig->addAction(lab);
//	ui->SystemstackedWidget->addWidget(weig);
	//调用网页
}
//关于
//void WinSystemSetup::on_btnAbout_click()
//{
//	painterMenu("BtnAbout");
//	ui->SystemstackedWidget->setCurrentIndex(3);
//}


void WinSystemSetup::painterMenu(const QString pushBtnName)
{
	//常规
	if (pushBtnName.contains("BtnRule"))
	{
		ui->BtnRule->setStyleSheet("color:rgb(22, 154, 218);font-weight:500;");
	}
	else
	{
		ui->BtnRule->setStyleSheet("color:#000;font-weight:none;");
	}
	//修改密码
	if (pushBtnName.contains("BtnPwd"))
	{
		ui->BtnPwd->setStyleSheet("color:rgb(22, 154, 218);font-weight:500;");
	}
	else
	{
		ui->BtnPwd->setStyleSheet("color:#000;font-weight:none;");
	}
	//调试
	if (pushBtnName.contains("BtnDebug"))
	{
		ui->BtnDebug->setStyleSheet("color:rgb(22, 154, 218);font-weight:500;");
	}
	else
	{
		ui->BtnDebug->setStyleSheet("color:#000;font-weight:none;");

	}
	//指南
	if (pushBtnName.contains("BtnGuide"))
	{
		ui->BtnGuide->setStyleSheet("color:rgb(22, 154, 218);font-weight:500;");
	}
	else
	{
		ui->BtnGuide->setStyleSheet("color:#000;font-weight:none;");

	}
	//关于
	/*if (pushBtnName.contains("BtnAbout"))
	{
		ui->BtnAbout->setStyleSheet("color:rgb(22, 154, 218);font-weight:500;");
	}
	else
	{
		ui->BtnAbout->setStyleSheet("color:#000;font-weight:none;");

	}*/
}

//关闭
void WinSystemSetup::on_pushBtnSystem_close() 
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	HWND  hMainWnd = pQyMc->gui.hMainWnd;
	CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
	
	//
	//

	//pMainWnd->isSystemShow = false;
	close();
}


void WinSystemSetup::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH), QBrush(Qt::white));

	QColor color(0, 0, 0, 10);
	for (int i = 0; i < SHADOW_WIDTH; i++)
	{
		color.setAlpha(120 - qSqrt(i) * 40);
		painter.setPen(color);
		// 方角阴影边框;
	  painter.drawRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2);
		// 圆角阴影边框;
		//painter.drawRoundedRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2, 4, 4);
	}
}
