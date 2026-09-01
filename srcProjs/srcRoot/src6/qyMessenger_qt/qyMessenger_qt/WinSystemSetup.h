#pragma once

#include <QWidget>
#include "ui_WinSystemSetup.h"
#include "WinBasic.h"
#define CONT_SYSTEM 0
class WinSystemSetup : public WinBasic
{
	Q_OBJECT

public:
	//
	struct {
	} m_var;

public:
	WinSystemSetup(QWidget *parent = Q_NULLPTR);
	~WinSystemSetup();


	//初始化
	void initControl();
	void paintEvent(QPaintEvent* event);
	void painterMenu(const QString pushBtnName);


public slots:
	//关闭
	void on_pushBtnSystem_close();
	//常规设置
	void on_btnRule_click();
	//修改密码
	void on_btnPwd_click();
	//调试
	void on_btnDebug_click();
	//使用指南
	void on_btnGuide_click();
	void on_btnOther_click();
	//关于
	//void on_btnAbout_click();

	void changeEvent(QEvent* event)override;

private:
	Ui::WinSystemSetup* ui;
	
};
