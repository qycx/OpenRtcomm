#pragma once

#include <QDialog>
#include "ui_DeviceSelectDialog.h"
#include "WinBaseDialog.h"
#include <QRadioButton>

#include    "mmDeviceProc.h"

// 音频设备信息结构体
struct AudioDeviceInfo {
    QString id;       // 设备唯一标识
    QString name;     // 设备显示名称
    bool isDefault;   // 是否为默认设备
    bool isActive;    // 是否为当前使用设备
};


class DeviceSelectDialog : public WinBaseDialog
{
    Q_OBJECT

    //
    struct {
        OLD_videoDevices  vd;
        OLD_audioDevices  ad;

        //
        int v_index_sel;


        //
    }  m_var;

    //
    QButtonGroup* m_btnGroup_v;
    QButtonGroup* m_btnGroup_a;
    QButtonGroup* m_btnGroup_a_out;

public:
    static void showDialog(QWidget* parent = Q_NULLPTR);
    
    static void closeDialog();
private:
    DeviceSelectDialog(QWidget *parent = Q_NULLPTR);
    ~DeviceSelectDialog();

    ////获取当前音频播放设备
    QList<AudioDeviceInfo> getAudioOutputDevicesData();


private:
    virtual bool canResize() { return false; }
    virtual void closeEvent(QCloseEvent* ev);
private slots:
    void onVideoToggled(bool b);
    void onAudioToggled(bool b);
    void onOutAudioToggled(bool b);
    void on_btnAccept_clicked();
private:
    Ui::DeviceSelectDialog ui;
    QList<QRadioButton*> dev_videos_;
    QList<QRadioButton*> dev_audios_;

    QList<QPair<QString, QString>> out_device;
};
