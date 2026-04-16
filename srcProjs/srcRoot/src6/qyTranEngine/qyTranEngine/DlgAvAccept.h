#pragma once

#include <QWidget>
#include "ui_DlgAvAccept.h"
#include <QMediaPlayer>

class DlgAvAccept : public QWidget
{
	Q_OBJECT

	//
	struct {
		bool  bQuit;

		//
		bool bDone_tryToAutoAccept;
		//
		unsigned  __int64	id_logicalPeer;
		//
	}  m_var;

	//
	QTimer* m_pWinTimer;


public:
	DlgAvAccept(QWidget *parent = Q_NULLPTR);
	~DlgAvAccept();

	//
	bool  bQuitDlg(int iVal);
	int tryToAutoAccept();

private:
	Ui::DlgAvAccept ui;

	//
	QMediaPlayer* m_pMediaPlayer;
	QMediaPlaylist* m_pMediaPlaylist;

	//ÍÏ×§´°¿Ú
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	bool        m_bDrag;
	QPoint      mouseStartPoint;
	QPoint      windowTopLeftPoint;

public:
	bool nativeEvent(const QByteArray& eventType, void* message, long* result);
	bool postMessageQt(MSG* message, long* result);
	void paintEvent(QPaintEvent* event);
	void closeEvent(QCloseEvent* ev);

private slots:
	//
	void on_timer_winMethod();
	//
	void on_btnAccept_clicked(bool);
	void on_btnCancel_clicked(bool);



};
