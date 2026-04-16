#pragma once

#include <QDialog>
#include "ui_QualitySelSetDialog.h"
#include "WinBaseDialog.h"

class QualitySelSetDialog : public WinBaseDialog
{
    Q_OBJECT

    //
    struct {
        unsigned  int  uiCapType;
        unsigned  int  uiSubCapType;
        int            iCapUsage;
        //
        bool            b3D;

        //
        int             level;

    }  m_var;


    //
public:
    QualitySelSetDialog(QWidget *parent = Q_NULLPTR);
    ~QualitySelSetDialog();

    //
    bool  bRefresh_lab7();

private:
    virtual bool canResize() { return false; }
    void paintEvent(QPaintEvent* event);
private slots:
    void slot_resulation_toggled(bool b);
    void slot_checkbox_checked(bool b);
    void slot_button_ok();
    void slot_button_set();
    void slat_button_close();
    void on_comboBox_codec_currentIndexChanged(int index);

private:
    Ui::QualitySelSetDialog ui;
};
