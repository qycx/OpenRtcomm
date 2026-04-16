#include "ScreenDeviceSelect.h"
#include <QDebug>
#include    <qbuttongroup.h>
#include    "stdafx.h"
#include "qyMcMainCommon_qt.h"
#include <qyAvRecordPublic.h>
#include <QBitmap>
#include <QPainter>
#include <isCliHelpPublic.h>
#include <tmpRegFunc_open.h>
#include <QtCore/qsettings.h>
//


//
namespace {
    ScreenDeviceSelect* dlg = nullptr;
}
ScreenDeviceSelect::ScreenDeviceSelect(QWidget *parent)
	: WinBaseDialog(parent)
{
    ui.setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::Dialog);
    this->setAttribute(Qt::WA_DeleteOnClose);
    
    //设置关于窗体为圆角
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(), 20, 20);
    setMask(bmp);

    QString qstr;

    //
    memset(&m_var, 0, sizeof(m_var));
    list_devices_v(&m_var.vd);
    list_devices_a(true, &m_var.ad);

    TCHAR  v_sel[256];
    TCHAR a_sel[256];

    v_sel[0] = 0;
    a_sel[0] = 0;

    getChosenDevice(a_sel, mycountof(a_sel), v_sel, mycountof(v_sel), mynull, 0, mynull, mynull);

    HWND hDlgTalk = (HWND)parent->winId();
    TCHAR currCameraName[256];

    getCurrentCameraName(hDlgTalk, currCameraName, mycountof(currCameraName));
    //
    this->m_btnGroup_v = new QButtonGroup;
    //this->m_btnGroup_a = new QButtonGroup;
    QString rootKey_qt_av = CONST_rootKey_sm_init;
    QSettings* regQt = new QSettings(rootKey_qt_av, QSettings::NativeFormat);
    QString currCapture = regQt->value(CONST_regValName_capture_selected).toString();
    //
    for (int i = 0; i < m_var.vd.iNumVDevices; i++)
    {

        QString tmp_currCameraName = QString::fromStdWString(std::wstring(currCameraName));

        if (tmp_currCameraName == QString::fromUtf16((char16_t*)m_var.vd.mems[i].names_video)) {
            continue;
        }

        QRadioButton* radio = new QRadioButton(this);
        qstr = QString::number(i) + ": " + QString::fromUtf16((char16_t*)m_var.vd.mems[i].names_video);
        radio->setText(qstr);
       
      
       
        ////
        if (QString::fromUtf16((char16_t*)m_var.vd.mems[i].names_video) == currCapture) {
            radio->setChecked(true);
        //    //
            m_var.v_index_sel = i;
        }
        ////
        connect(radio, &QRadioButton::toggled, this, &ScreenDeviceSelect::onVideoToggled);
        dev_videos_ << radio;
        ui.verticalLayout_5->addWidget(radio);

        ////
        m_btnGroup_v->addButton(radio);
    }
    delete regQt;
    //
#if  0
    QRadioButton* radio = new QRadioButton(this);
    qstr = QString::number(0) + ":" + u8"选择默认麦克风";
    radio->setText(qstr);
    radio->setChecked(true);
    connect(radio, &QRadioButton::toggled, this, &ScreenDeviceSelect::onAudioToggled);
    dev_audios_ << radio;
    ui.verticalLayout_6->addWidget(radio);
    //
    m_btnGroup_a->addButton(radio);

    //
    for (int i = 0; i < m_var.ad.iNumADevices; i++)
    {
        QRadioButton* radio = new QRadioButton(this);
        qstr = QString::number(i + 1) + ":" + QString::fromUtf16((char16_t*)m_var.ad.mems[i].names_audio);
        radio->setText(qstr);
        radio->setEnabled(false);
        connect(radio, &QRadioButton::toggled, this, &ScreenDeviceSelect::onAudioToggled);
        dev_audios_ << radio;
        ui.verticalLayout_6->addWidget(radio);
        //
        m_btnGroup_a->addButton(radio);
    }
#endif
}


ScreenDeviceSelect::~ScreenDeviceSelect()
{
    //
    //if (this->m_btnGroup_a)  delete this->m_btnGroup_a;
    if (this->m_btnGroup_v)delete this->m_btnGroup_v;

    //
    dlg = nullptr;
}
ScreenDeviceSelect* ScreenDeviceSelect::showDialog(QWidget* parent)
{
    if (!dlg)
    {
        dlg = new ScreenDeviceSelect(parent);

    }
    dlg->show();
    dlg->activateWindow();

    return dlg;
}

void ScreenDeviceSelect::closeDialog() {
    if (dlg) {
        dlg->close();
    }
}

void ScreenDeviceSelect::closeEvent(QCloseEvent* ev)
{
    this->hide();
    ev->accept();
}

void ScreenDeviceSelect::onVideoToggled(bool b)
{
    int  iErr = -1;

    if (!b)
    {
        return;
    }
    //TODO:选中了一个视频设备
    QRadioButton* button = (QRadioButton*)sender();
    QString str = button->text();
    
    _currCapture = str.mid(str.indexOf(": ") + 2);
    TCHAR tBuf[256];
    safeTcsnCpy((TCHAR*)str.utf16(), tBuf, mycountof(tBuf));
    TCHAR* pT;
    pT = _tcschr(tBuf, _T(':'));
    if (!pT) goto  errLabel;

   

    *pT = 0;
    int index; index = _ttol(tBuf);

    //
    m_var.v_index_sel = index;

    iErr = 0;
    //
errLabel:
    return;

}

void ScreenDeviceSelect::onAudioToggled(bool b)
{
    int  iErr = -1;

    if (!b)
    {
        return;
    }
    //TODO:选中了一个音频设备
    QRadioButton* button = (QRadioButton*)sender();
    QString str = button->text();
    TCHAR tBuf[256];
    safeTcsnCpy((TCHAR*)str.utf16(), tBuf, mycountof(tBuf));
    TCHAR* pT;
    pT = _tcschr(tBuf, _T(':'));
    if (!pT) goto  errLabel;
    *pT = 0;
    int index; index = _ttol(tBuf);

    //


    //
    iErr = 0;
errLabel:
    return;

}


int  selectDefaultADeviceScreen()
{
    //  2014/7/31
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();



    //
    QY_REG  reg;
    memset(&reg, 0, sizeof(reg));

    reg.hKeyRoot0 = HKEY_CURRENT_USER;
    lstrcpyn(reg.rootKey, (pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), mycountof(reg.rootKey));

    qyDelRegCfgT(reg.hKeyRoot0, reg.rootKey, _T(CONST_regValName_ucbNot_selectDefaultRecorder));
    pProcInfo->cfg.policy.audio.ucbNot_selectDefaultRecorder = FALSE;

    //
    return  0;


}



//
void ScreenDeviceSelect::on_btnAccept_clicked() {
    //点击确认


    CCtxQyMc* pQyMc = g_pQyMc;
    QY_REG			reg;
    memset(&reg, 0, sizeof(reg));
  //  reg.hKeyRoot0 = HKEY_CURRENT_USER;
    lstrcpyn(reg.rootKey, CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), mycountof(reg.rootKey));

    if (m_var.v_index_sel >= m_var.vd.iNumVDevices)  return;
    if (_currCapture != nullptr) {
        QString rootKey_qt_av = CONST_rootKey_sm_init;
        QSettings* regQt = new QSettings(rootKey_qt_av, QSettings::NativeFormat);
        regQt->setValue(CONST_regValName_capture_selected, _currCapture);
        delete regQt;
    }
   // QString path =  QString::fromStdWString(std::wstring(reg.rootKey)) . CONST_regValName_capture_selected;
   // qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, _T(CONST_regValName_capture_selected), m_var.vd.mems[m_var.v_index_sel].captureDisplayName);

    emit signals_screen_device_selecct_ok();

#if 0 
   

    //
    selectDefaultADeviceScreen();
#endif
}

