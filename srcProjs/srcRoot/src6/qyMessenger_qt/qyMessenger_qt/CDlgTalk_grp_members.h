#pragma once

#include <QWidget>
#include "ui_CDlgTalk_grp_members.h"
#include "WinBasic.h"
#include "WinBaseDialog.h"

class CDlgTalk_grp_members : public WinBaseDialog
{
	Q_OBJECT

public:
		struct 
	{
			unsigned  __int64	 peer_idInfo;
	
	} m_var;
public:
	CDlgTalk_grp_members(QWidget *parent = Q_NULLPTR);
	~CDlgTalk_grp_members();

	void closeEvent(QCloseEvent* ev);
	//static void showDialog(QWidget* parent = Q_NULLPTR);
	void paintEvent(QPaintEvent* event);
	void closeDialog();
	void clearTableWidget(QTableWidget* table);
	
	static void setContent(QString peer_id);
	static void getDialog(QWidget* parent);
	static void showWnd();
public slots:
	void slot_onTableClicked(int row, int col);
	

public:
	Ui::CDlgTalk_grp_members ui;
};
