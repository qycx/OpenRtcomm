#include "DeviceSelectDialog.h"
#include <QDebug>
#include    <qbuttongroup.h>
#include    "stdafx.h"
#include "qyMcMainCommon_qt.h"
#include <qyAvRecordPublic.h>

//


//
namespace {
    DeviceSelectDialog* dlg = nullptr;
}

DeviceSelectDialog::DeviceSelectDialog(QWidget* parent)
    : WinBaseDialog(parent)
{
    ui.setupUi(this);
    this->setWindowFlags(this->windowFlags()| Qt::Dialog);
    this->setAttribute(Qt::WA_DeleteOnClose);


    QString qstr;

    //
    memset(&m_var, 0, sizeof(m_var));
    list_devices_v(&m_var.vd);  
    list_devices_a(true, &m_var.ad);

    TCHAR  v_sel[256];
    TCHAR a_sel[256];

    v_sel[0] = 0;
    a_sel[0] = 0;
    
    getChosenDevice(a_sel, mycountof(a_sel), v_sel, mycountof(v_sel), null, 0, null, null);


    //
    this->m_btnGroup_v = new QButtonGroup;
    this->m_btnGroup_a = new QButtonGroup;


    //
    for (int i = 0; i < m_var.vd.iNumVDevices; i++)
    {
        QRadioButton* radio = new QRadioButton(this);
        qstr = QString::number(i)+": "+QString::fromUtf16((char16_t*)m_var.vd.mems[i].names_video);
        radio->setText(qstr);
        //
        if (!_tcsicmp(v_sel, m_var.vd.mems[i].monikerDisplayName)) {
            radio->setChecked(true);
            //
            m_var.v_index_sel = i;
        }
        //
        connect(radio, &QRadioButton::toggled, this, &DeviceSelectDialog::onVideoToggled);
        dev_videos_ << radio;
        ui.verticalLayout_5->addWidget(radio);

        //
        m_btnGroup_v->addButton(radio);
    }

    //
#if  10
    QRadioButton* radio = new QRadioButton(this);
    qstr = QString::number(0) + ":" + u8"选择默认麦克风";
    radio->setText(qstr);
    radio->setChecked(true);
    connect(radio, &QRadioButton::toggled, this, &DeviceSelectDialog::onAudioToggled);
    dev_audios_ << radio;
    ui.verticalLayout_6->addWidget(radio);
    //
    m_btnGroup_a->addButton(radio);
    
    //
    for (int i = 0; i < m_var.ad.iNumADevices; i++)
    {
        QRadioButton* radio = new QRadioButton(this);
        qstr = QString::number(i  +  1)+":"+QString::fromUtf16((char16_t*)m_var.ad.mems[i].names_audio);
        radio->setText(qstr);
        radio->setEnabled(false);
        connect(radio, &QRadioButton::toggled, this, &DeviceSelectDialog::onAudioToggled);
        dev_audios_ << radio;
        ui.verticalLayout_6->addWidget(radio);
        //
        m_btnGroup_a->addButton(radio);
    }
#endif

}

DeviceSelectDialog::~DeviceSelectDialog()
{
    //
    if (this->m_btnGroup_a)  delete this->m_btnGroup_a;
    if (this->m_btnGroup_v)delete this->m_btnGroup_v;

    //
    dlg = nullptr;


}

void DeviceSelectDialog::showDialog(QWidget* parent)
{
    if (!dlg)
    {
        dlg = new DeviceSelectDialog(parent);

    }
    dlg->show();
    dlg->activateWindow();
}

void DeviceSelectDialog::closeDialog() {
    if (dlg) {
        dlg->close();
    }
}

void DeviceSelectDialog::closeEvent(QCloseEvent* ev)
{
    this->hide();
    ev->accept();
}

void DeviceSelectDialog::onVideoToggled(bool b)
{
    int  iErr = -1;

    if (!b)
    {
        return;
    }
    //TODO:选中了一个视频设备
    QRadioButton* button = (QRadioButton*)sender();
    QString str = button->text();
    TCHAR tBuf[256];
    safeTcsnCpy((TCHAR*)str.utf16(), tBuf, mycountof(tBuf));
    TCHAR* pT;
    pT = _tcschr(tBuf, _T(':'));
    if (!pT) goto  errLabel;
    *pT = 0;
    int index = _ttol(tBuf);

    //
    m_var.v_index_sel = index;

    iErr = 0;
    //
errLabel:
    return;

}

void DeviceSelectDialog::onAudioToggled(bool b)
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
    int index = _ttol(tBuf);

    //


    //
    iErr = 0;
errLabel:
    return;

}


int  selectDefaultADevice()
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
void DeviceSelectDialog::on_btnAccept_clicked() {
    //点击确认
    qDebug() << "111";

    CCtxQyMc* pQyMc = g_pQyMc;
    QY_REG			reg;
    memset(&reg, 0, sizeof(reg));
    reg.hKeyRoot0 = HKEY_CURRENT_USER;
    lstrcpyn(reg.rootKey, CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), mycountof(reg.rootKey));

    if (m_var.v_index_sel >= m_var.vd.iNumVDevices)  return;
    qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, _T(CONST_regValName_webcam_selected), m_var.vd.mems[m_var.v_index_sel].monikerDisplayName);

    //
    selectDefaultADevice();

}

