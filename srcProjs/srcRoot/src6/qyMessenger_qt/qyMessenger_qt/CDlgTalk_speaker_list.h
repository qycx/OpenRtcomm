#pragma once

#include <QWidget>
#include "ui_CDlgTalk_speaker_list.h"
#include "WinBaseDialog.h"

class CDlgTalk_speaker_list : public WinBaseDialog
{
	Q_OBJECT

public:
	CDlgTalk_speaker_list(QWidget* parent = Q_NULLPTR);
	~CDlgTalk_speaker_list();

	static void setContent(QString peerId);
	static void getDialog(QWidget* parent);
	static void showWnd();
	static void closeDialog();
	void closeEvent(QCloseEvent* ev);
	void removeProessAll();
	void paintEvent(QPaintEvent* event);
	
private:
	Ui::CDlgTalk_speaker_list ui;
};
