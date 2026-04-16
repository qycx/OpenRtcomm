#pragma once

#include <QDialog>
#include "ui_DeviceSelectDialog.h"
#include "WinBaseDialog.h"
#include <QRadioButton>

#include    "mmDeviceProc.h"


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


public:
    static void showDialog(QWidget* parent = Q_NULLPTR);
    
    static void closeDialog();
private:
    DeviceSelectDialog(QWidget *parent = Q_NULLPTR);
    ~DeviceSelectDialog();
private:
    virtual bool canResize() { return false; }
    virtual void closeEvent(QCloseEvent* ev);
private slots:
    void onVideoToggled(bool b);
    void onAudioToggled(bool b);
    void on_btnAccept_clicked();
private:
    Ui::DeviceSelectDialog ui;
    QList<QRadioButton*> dev_videos_;
    QList<QRadioButton*> dev_audios_;
};
