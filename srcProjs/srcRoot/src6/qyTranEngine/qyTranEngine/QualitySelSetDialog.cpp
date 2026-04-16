#include "QualitySelSetDialog.h"
#include <QListView>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QtCore>

//
#if  10
#include    "qyMcMainCommon_qt.h"
#include    "qmcSharedObj.h"
#include    "ctxQmc.h"
#include <policyIsClientFunc.h>
#include <qmcCommFunc_mis.h>
#include    "ctxQmc_qt.h"
#endif
#include <qyCusResTemp.h>
#include <tmpRegFunc_open.h>


//
#define SHADOW_WIDTH 10 // 阴影边框宽度;
QualitySelSetDialog::QualitySelSetDialog(QWidget *parent)
    : WinBaseDialog(parent)
{
    ui.setupUi(this);
    ui.comboBox->setView(new QListView());
    ui.comboBox_codec->setView(new QListView());
    ui.comboBox_usMaxSpeakers->setView(new QListView());
    ui.Btn_480p->setChecked(true);
    QIcon syscloseI(":/Resources/Images/Title/sysbtn_close_normal.png");
    ui.closeBtn->setIcon(syscloseI);
    ui.label_err->setText("");
    //
    memset(&m_var, 0, sizeof(m_var));

    //
#if  10
    CCtxQyMc* pQyMc = QY_GET_GBUF();



    //
    AV_COMPRESSOR_CFG  compressor = { 0 };

    //
    m_var.uiCapType = CONST_capType_av;
    m_var.uiSubCapType = 0;
    m_var.iCapUsage = 0;
    m_var.b3D = true;

    //
    

    //
    int level = 0;
    if (!level)  level = getPolicyAvLevel(pQyMc, m_var.uiCapType, m_var.uiSubCapType, m_var.iCapUsage);
    //if (!qyGetDesByType(getResTable(0, &pQyMc->cusRes, iResId), level))    level = getDefaultPolicyAvLevel(pQyMc, uiCapType, uiSubCapType, iCapUsage);

    //
    getCompressorCfg(NULL, m_var.uiCapType, m_var.uiSubCapType, m_var.iCapUsage, level, &compressor);


    //
    switch  (  level  )  {
            case  CONST_policyAvLevel_240p:
                  ui.Btn_240p->setChecked(true);
                  break;
            case  CONST_policyAvLevel_480p:
            case  CONST_policyAvLevel_848x480:
            case  CONST_policyAvLevel_576p:
                  ui.Btn_480p->setChecked(true);
                  break;
            case  CONST_policyAvLevel_720p:
                  ui.Btn_720p->setChecked(true);
                  break;
            case  CONST_policyAvLevel_1080p:
                  ui.Btn_1080p->setChecked(true);
                  break;
            default:
                    break;
    }


    //
    CQyString str = getCompressorDesc(m_var.uiCapType, &compressor);
    QString qstr = QString::fromUtf16(( const char16_t*)str.GetBuffer());
    ui.label_desc->setText(qstr);

    QString rootKey_qt_av = CONST_rootKey_qt_av;
    QSettings* regQt = new QSettings(rootKey_qt_av, QSettings::NativeFormat);
   
    QString  ucb2Streams = regQt->value("ucb2Streams").toString();

    if (ucb2Streams == "1") {
        ui.checkDouble->setChecked(true);
    }
    else {
        ui.checkDouble->setChecked(false);
    }

    delete regQt;
    //
    int  conf_iFourcc = get_conf_iFourcc();
    ushort  usMaxSpeakers = get_conf_usMaxSpeakers();

    //
    char fourcc[4 + 1];
    iFourcc2Str(conf_iFourcc, fourcc, mycountof(fourcc));
    ui.comboBox_codec->setCurrentText( fourcc  );

    char buf[128];
    itoa(usMaxSpeakers, buf, 10);
    ui.comboBox_usMaxSpeakers->setCurrentText(buf);
#endif


    //
    bRefresh_lab7();
    
    
}

QualitySelSetDialog::~QualitySelSetDialog()
{
}


//
bool  QualitySelSetDialog::bRefresh_lab7()
{
    QString qstr = ui.comboBox_codec->currentText();
    char fourcc[4 + 1];
    myTChar2Utf8((TCHAR*)qstr.utf16(), fourcc, mycountof(fourcc));
    int iFourcc = fourccStr2i(fourcc);

    TCHAR  *  pT_prefix = (TCHAR*)_T("最大发言人数");
    TCHAR  tBuf[128];
    int  iMin = 1;
    int  iMax = 9;// 6;
    QString  qstr1;
    //
    switch (iFourcc) {
    case  CONST_fourcc_vp80:
        iMax = 16;
        break;
    case  CONST_fourcc_h264:
        break;
    default:
        break;
    }
    _sntprintf(tBuf, mycountof(tBuf), _T("%s(%d-%d)"), pT_prefix, iMin, iMax);
    ui.label_7->setText(QString::fromUtf16((char16_t*)tBuf));


    return  true;
}




void QualitySelSetDialog::slot_resulation_toggled(bool b)
{
    if (!b)
    {
        return;
    }
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString des;

    //
    int level = 0;

    //
    if (button->text() == u8"全高清")
    {
        des = u8"xxxxx";
        level = CONST_policyAvLevel_1080p;
    }
    else if (button->text() == u8"高清")
    {
        des = u8"xxxx";
        level = CONST_policyAvLevel_720p;
    }
    
    else if (button->text() == u8"480p")
    {
        des = u8"xxxx";
        level = CONST_policyAvLevel_480p;

    }
    else if (button->text() == u8"240p")
    {
        des = u8"xxxx";
        level = CONST_policyAvLevel_240p;
    }
    //TODO:设置 和修改 描述

    //
    AV_COMPRESSOR_CFG  compressor = { 0 };

    //
    m_var.level = level;

    //
    getCompressorCfg(NULL, m_var.uiCapType, m_var.uiSubCapType, m_var.iCapUsage, level, &compressor);
    CQyString str;
    str = getCompressorDesc(m_var.uiCapType, &compressor);
    des = QString::fromUtf16((char16_t*)str.GetBuffer());
    
    //
    ui.label_desc->setText(des);
}

void QualitySelSetDialog::slot_checkbox_checked(bool b)
{
#if 0
    if (sender() == ui.checkBox)
    {
        //TODO:会议控制
    }
    else   if (sender() == ui.checkBox_2)
    {
        //TODO:不再提示
    }
#endif
}


//
void QualitySelSetDialog::on_comboBox_codec_currentIndexChanged(int index)
{
    bRefresh_lab7();
}



void QualitySelSetDialog::slot_button_ok()
{
    //TODO:确认
    //
    CCtxQyMc* pQyMc = g_pQyMc;

    TCHAR* pRegVal;
    QY_REG  reg;  
    
    //双流
    unsigned  char ucb2Streams;

    memset(&reg, 0, sizeof(reg));
    reg.hKeyRoot0 = HKEY_CURRENT_USER;

    //
    TCHAR  tBuf[128];

    //
    QString qstr = ui.comboBox_codec->currentText();
    char fourcc[4 + 1];
    myTChar2Utf8((TCHAR*)qstr.utf16(), fourcc, mycountof(fourcc));
    myUtf82TChar(fourcc, tBuf, mycountof(tBuf));
    qySetRegCfgT(HKEY_CURRENT_USER, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, _T(CONST_regValName_conf_fourcc), tBuf);

    //
    int  conf_iFourcc = get_conf_iFourcc();

    //
//if (m_var.ucbStarter) 
    {
        int  conf_iFourcc = get_conf_iFourcc();
        switch (conf_iFourcc) {
        case  CONST_fourcc_vp80:
            if (m_var.level >= CONST_policyAvLevel_720p) {
                //  qyShowHint(  _T(  "vp8 can't support hd"  )  );
                //ui.label_err->setText(QString::fromUtf16((char16_t*)getResStr(0, &pQyMc->cusRes, CONST_resId_vp8)));
                ui.label_err->setText(u8"错误：vp8不支持高清");
                return;
            }
            break;
        default:
            break;
        }
    }
    
  
    if (ui.checkDouble->isChecked())
    { 
        ucb2Streams = 1;
    }
    else {
        ucb2Streams = 0;
    }

  


    //
    qstr = ui.comboBox_usMaxSpeakers->currentText();
    int  iVal = _ttol((TCHAR*)qstr.utf16());
    //
    int  iMax = MAX_real_speakers_taskAv_h264;
    switch (conf_iFourcc) {
    case  CONST_fourcc_vp80:
        iMax = MAX_real_speakers_taskAv_vp8;
        break;
    }
    if (iVal <= 0) {
        _sntprintf(tBuf, mycountof(tBuf), _T("错误：%S的最大发言人数必须>0"), fourcc);
        ui.label_err->setText(QString::fromUtf16((char16_t*)tBuf));
        return;
    }
     if  (  iVal > iMax) {
        _sntprintf(tBuf, mycountof(tBuf), _T("错误：%S的最大发言人数必须<=%d"), fourcc, iMax);
        ui.label_err->setText(QString::fromUtf16((char16_t*)tBuf));
        return;
    }
    //
    if (iVal > 0 && iVal <= iMax) {
        _sntprintf(tBuf, mycountof(tBuf), _T("%d"), iVal);
        qySetRegCfgT(HKEY_CURRENT_USER, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, _T(CONST_regValName_conf_usMaxSpeakers), tBuf);
    }


    //
    if (m_var.uiCapType == CONST_capType_av && m_var.uiSubCapType == 0) {
        //
        int  iCapUsage = m_var.b3D ? CONST_capUsage_3dConf : CONST_capUsage_conf;
        //
        getRegRootKey_qmc(m_var.uiCapType, m_var.uiSubCapType, iCapUsage, reg.rootKey, mycountof(reg.rootKey));
        pRegVal = (TCHAR*)CONST_regValName_policyAvLevel_req;
        qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, _ltot(m_var.level, tBuf, 10));		//  level_conf和原来的reply当一个用
    }
    getRegRootKey_qmc(m_var.uiCapType, m_var.uiSubCapType, m_var.iCapUsage, reg.rootKey, mycountof(reg.rootKey));
    //
    pRegVal = (TCHAR*)CONST_regValName_policyAvLevel_req;
    qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, _ltot(m_var.level, tBuf, 10));

    //状态记录
        pRegVal = (TCHAR*)CONST_regValName_ucb2Streams;
        _sntprintf(tBuf, mycountof(tBuf), _T("%d"), ucb2Streams);
        qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, tBuf);
    
  
    //
    this->accept();
}
void QualitySelSetDialog::slot_button_set()
{
    //TODO:设置
    this->reject();
}
//关闭
void QualitySelSetDialog::slat_button_close() {
    
}
void QualitySelSetDialog::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH), QBrush(Qt::white));

    QColor color(0, 0, 0, 10);
    for (int i = 0; i < SHADOW_WIDTH; i++)
    {
        color.setAlpha(120 - qSqrt(i) * 40);
        painter.setPen(color);
        // 方角阴影边框;
     // painter.drawRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2);
        // 圆角阴影边框;
        painter.drawRoundedRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2, 4, 4);
    }
}



