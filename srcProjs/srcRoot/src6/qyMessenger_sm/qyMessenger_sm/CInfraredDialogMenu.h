#pragma once

#include <QDialog>
#include "ui_CInfraredDialogMenu.h"

class CInfraredDialogMenu : public QDialog
{
	Q_OBJECT

public:
	CInfraredDialogMenu(QWidget* parent = nullptr, QString m_status = nullptr);
	~CInfraredDialogMenu();

	void Infrared_down();
	void Infrared_up();

	//void mainWnd_infraredMenu(QString s_status);

	void sheetBackgroundImage();



	QString _instruct = nullptr; //红外指令
	int _instruct_num = 0; //指令次数
	qint64 _instruct_time = 0; //接收指令时间

signals:
	void to_speak_signal(); //申请发言

	void to_video_signal(); //开启摄像头

	void to_audio_signal();  //开启麦克风

	void to_this_video_signal();//显示隐藏本地视频

	void to_this_info_signal();

	void to_device_screen_signal(); //发送辅流

	void to_EndAvBtn_signal();  // 结束会议

	void to_showStatus_signal(); // 显示隐藏状态栏

	void to_showDeviceBinding_signal(); //调用设置窗口

	void to_showDebugDlg_signal(); //调试窗
	void to_openShareDlg_signal(); 

	void to_showP2pDlg_signal();//点对点会议

	void to_amplifier_signal(); //画面放大

	void to_amplifier_close_signal(); //取消画面放大



	void to_chairman_signal(); //主席布局





	void to_LogOut_signal(); //退出登录

	void to_sendCdlgTalkWork_signal();
	void to_sendMainFrameWork_signal();
	void to_sendQmcLoginWork_signal();
	void to_sendDeviceBindWork_signal();
	void to_sendUserLoginWork_signal();
	void to_showPortSetting_signal();
	//
	void to_showOtherSetting_signal(); //其它设置



public slots:
	void on_menuBtn1_clicked();
	void on_menuBtn2_clicked();
	void on_menuBtn3_clicked();
	void on_menuInfo_clicked();
	void on_menuBtn4_clicked();
	void on_menuBtn5_clicked();
	void on_btnVideo_clicked();
	void on_btnAudio_clicked();
	void on_menuShutdown_clicked(); //关机
	void on_menuRestart_clicked();
	void on_menuBtnAmplifier_clicked(); //画面放大
	void on_menuBtnAmplifier_close_clicked();
	void on_menuResolution_clicked();

	void on_menuChairman_clicked();  // 主席布局

	void on_menuSetting_clicked(); //初始设置
	void on_PortSetting_clicked(); //端口设置
	void on_btnLogOut_clicked(); //注销
	void on_menuOther_clicked(); //其它设置
	void on_menuDebug_clicked();//开启关闭调试窗
	void on_menuShare_clicked();
	void on_menuP2p_clicked();//点对点会议

	void refResolution();

public:
	Ui::CInfraredDialogMenuClass* ui;
};
