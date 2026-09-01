#pragma once

#include <QWidget>
#include "ui_WinRuleSet.h"
#include "WinBasic.h"
#include	"stdafx.h"
#include	"qyMcMainCommon_qt.h"

#include	"dlgImObjRuleProc.h"
#include <QRadioButton>

class WinRuleSet : public QDialog
{
	Q_OBJECT


	//
public:
	DLG_imObjRule_var	m_var;

	QRadioButton* av_radAuto;
	QRadioButton* av_radManual;

public:
	WinRuleSet(QWidget *parent = Q_NULLPTR);
	~WinRuleSet();
	void paintEvent(QPaintEvent* event);
	

	//
	static int showDialog(QWidget* parent, unsigned  __int64  ui64Id );

	//
	int init();

	//
	virtual void closeEvent(QCloseEvent* ev);

	
public slots:
	void onVideoRule(bool b);
	void on_btnAccept_clicked();

private:
	Ui::WinRuleSet ui;
};
