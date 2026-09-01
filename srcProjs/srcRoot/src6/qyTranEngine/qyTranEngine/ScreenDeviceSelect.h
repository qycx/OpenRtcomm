#pragma once

#include <QDialog>
#include "ui_ScreenDeviceSelect.h"
#include "WinBaseDialog.h"
#include <QRadioButton>

#include    "mmDeviceProc.h"

class ScreenDeviceSelect : public WinBaseDialog
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

    QString _currCapture = nullptr;


signals:
    void signals_screen_device_selecct_ok();

public:
    static ScreenDeviceSelect* showDialog(QWidget* parent = Q_NULLPTR);

    static void closeDialog();
public:
	ScreenDeviceSelect(QWidget *parent = nullptr);
	~ScreenDeviceSelect();

private:
    virtual bool canResize() { return false; }
    virtual void closeEvent(QCloseEvent* ev);
private slots:
    void onVideoToggled(bool b);
    void onAudioToggled(bool b);
    void on_btnAccept_clicked();
private:
	Ui::ScreenDeviceSelectClass ui;
    QList<QRadioButton*> dev_videos_;
    QList<QRadioButton*> dev_audios_;
};
