#pragma once

#include <QDialog>
#include "ui_CDlgOther.h"
#include <QRadioButton>
#include "noticewidget.h"
#include "CInfraredDialogMenu.h"
//#include <QAudioDeviceInfo>

struct MicrophoneDevice {
	QString name;        // 设备友好名称
	QString id;          // 设备唯一标识符  
	bool isDefault;      // 是否为默认设备
	bool isDefaultComm;  // 是否为默认通信设备
	bool isSelected;     // 根据规则最终选中的设备
};

class CDlgOther : public QDialog
{
	Q_OBJECT

public:
	CDlgOther(QWidget* parent = nullptr);
	~CDlgOther();
	void sheetBackgroundImage();

	void audioOutDeviceList();//音频输出设备列表

	void audioInDeviceList();//音频输入设备列表

	//遥控
	void Infrared_down();
	void Infrared_up();
	//void Infrared_ok(QString objname = nullptr);		//确认键
	//
	CInfraredDialogMenu* m_pInfraredMenu = nullptr;

public slots:

	//确认键
	void on_otherBtnRet_clicked(QString objname = nullptr);
	void on_restNvrBtn_clicked();  //重启NVR

	//void setupAudioOutputButtons();
	void clearLayout(QLayout* layout);
	//QList<QPair<QString, QString>> getAudioOutputDevices();
	void onAudioOutputSelected();
	void onAudioInputSelected();

	void on_infraredMenu();
	void infraredMenu_quit();




	void showHint(QString msg, QString fontColor = "#f60", qint64 out_time = 3000);
signals:
	void to_returnMain_signal();
private:
	Ui::CDlgOtherClass* ui;
	//
	QList<QRadioButton*> dev_audios_;
	QList<QRadioButton*> dev_videos_;

	//
	QButtonGroup* m_btnGroup_a_out;

	//
	QList<QPair<QString, QString>> out_device;
	//
	QList<MicrophoneDevice> in_device;

	//
	int m_outAudioselectedIndex;    // 存储当前选中的按钮索引
	QList<QPushButton*> m_audioButtons; // 存储所有音频输出按钮

	//
	int m_inAudioselectedIndex;    // 存储当前选中的按钮索引
	QList<QPushButton*> m_inAudioButtons; // 存储所有音频输出按钮
};
