#pragma once

#include <QWidget>
#include "ui_CDlgTalkMoreMenu.h"
#include "WinBasic.h"


class CDlgTalkMoreMenu : public WinBasic
{
	Q_OBJECT

public:
	struct {
		unsigned  __int64	  peer_idInfo;
	} m_var;

public:
	static CDlgTalkMoreMenu* showDialog(QPoint pt=QPoint(), bool device_screen_status = false, QWidget* parent = Q_NULLPTR);
	void paintEvent(QPaintEvent* event);
	void isShowBtnMake(bool isShow);
	void isShowBtnMember(bool isShow);
	void isShowBtnController(bool isShow);
	
	bool _is_open = false;

private:
	CDlgTalkMoreMenu( QWidget* parent = Q_NULLPTR);
	~CDlgTalkMoreMenu();
signals:
	void signal_full_screen();
	void signal_this_video();
	void signal_device_select();
	void signal_grp_members();
	void signal_dish_select();
	void signal_make_list();
	void signal_controller();
	void signal_device_screen();
	void signal_device_screen_close();
private slots:
	void on_toolBtnFullScreen_clicked();
	void on_toolBtnThis_clicked();
	void on_toolBtnDish_clicked();
	void on_toolBtnFacility_clicked();
	void on_toolBtnDeviceCap_clicked();
	void on_toolBtnMember_clicked();
	void on_toolBtnMake_clicked();
	void on_toolBtnController_clicked();
	void up_device_screen_status(bool is_open);
private:
	virtual bool eventFilter(QObject* watched, QEvent* event);
	virtual bool canResize() { return false; }
private:
	Ui::CDlgTalkMoreMenu ui;

};
