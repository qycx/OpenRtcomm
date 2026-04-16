#pragma once

#include <QWidget>
#include <QTimer>
#include "ui_CDlgTalk_invite_hint.h"

class CDlgTalk_invite_hint : public QWidget
{
	Q_OBJECT
		//
		struct {
		bool  bQuit;

		//
	}  m_var;

	
public:
	CDlgTalk_invite_hint(QWidget *parent = nullptr);
	~CDlgTalk_invite_hint();

	void closeEvent(QCloseEvent* ev);
	bool bQuitDlg(int iVal);

	//ÍÏ×§´°¿Ú
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	bool        m_bDrag;
	QPoint      mouseStartPoint;
	QPoint      windowTopLeftPoint;
	void paintEvent(QPaintEvent* event);
	//
	HWND  _hDlgTalk;
public slots:
	void on_btnConsent_clicked();
	void on_btnRefuse_clicked();

private:
	Ui::CDlgTalk_invite_hintClass ui;
	QTimer* timer;
	QTimer* time_timer;
	int m_time  ;

};
