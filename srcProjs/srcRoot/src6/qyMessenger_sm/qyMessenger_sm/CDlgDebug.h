#pragma once

#include <QDialog>
#include "ui_CDlgDebug.h"
#include <QTimer>
#include "CDlgTalk_qt.h"
//#include <QAudioDeviceInfo>

class CDlgDebug : public QDialog
{
	Q_OBJECT

public:
	CDlgDebug(QWidget *parent = nullptr, QString m_status = nullptr);
	~CDlgDebug();
	void sheetBackgroundImage();
	void getDiskSize();

	QTimer* m_pWinTimer = nullptr;
	QWidget* m_pParent = nullptr;
	
	qint64 sumSize = 0;
	qint64 availableSize = 0;
	// 获取当前正在使用的喇叭设备名称  默认通信设备
	QString getDefaultCommunicationSpeakerDevice();
	// 获取默认通信输入音频设备名称   
	QString getDefaultCommunicationMicrophoneDevice();


public slots:
	void refreshData();
	void refResolution();

private:
	Ui::CDlgDebugClass* ui;
};
