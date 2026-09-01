#include "CMainFrame.h"
#include "ui_CMainFrame.h"
#include "qyCusResTemp.h" 
#include "ctxQmc.h" 
#include "qmcCommFunc_isCli.h"
#include "qyMcMainCommon_qt.h"
#include "qyMcMainObj.h"
#include "ctxQyMc.h" 
#include "myDb.h"
#include "QTreeWidgetItem"
#include "ui_CMainFrame.h"
#include <myresource.h> 
#include <funcsForIsCliHelp.h>
#include "ctxQmc_sm.h"
#include "WinTalkList.h" 
#include "WinContactsList.h"
#include "WinTitle.h"
#include "WinFullPicture.h"
#include "CDlgTalk_msgr_detail.h"
#include "CDlgTalk_imGrp_detail.h"
#include "WinAdvancedSet.h"
#include <QHoverEvent>
#include <QMouseEvent>
#include "DBManager.h"
#include "UserInfoDialog.h"
#include "AddGroupMemberDialog.h"
#include <QMenu>
#include "DeviceSelectDialog.h"
#include "SearchMsgRecord.h"
#include "CDeviceBinding.h"
#include <QSoundEffect>
#include <windows.h>
#include <WinSystemAbout.h>

#include "CDlgShareDynBmps_qt.h"

#include    "infraredInstruct.h"
#include    "oldConfs.h"



int search_fill_contact(QList<SearchInfoData >& m_infoList);
int search_fill_grp(QList<SearchInfoData >& m_infoList);
int search_fill_msg(QList<SearchInfoData >& m_infoList, QString str);

namespace {
    const int kMouseRegionLeft = 10;
    const int kMouseRegionTop = 10;
    const int kMouseRegionButtom = 10;
    const int kMouseRegionRight = 10;
    QSoundEffect* _sound = nullptr;
    HWND  HWND_MAIN_ID = 0;
    const int MIN_DISPLAY = 1280;
}

CMainFrame* winCl = NULL;
CMainFrame::CMainFrame(QWidget* parent)
    : WinBasic(true, parent)
    // :QWidget()
    , ui(new Ui::CMainFrame)
{
#ifdef  __DEBUG__
    traceLog((TCHAR*)_T("mainFrame::CMainFrame() enters"));
#endif

    ui->setupUi(this);

    //
    this->setAttribute(Qt::WA_NativeWindow);

    //
    CCtxQyMc* pQyMc = QY_GET_GBUF();
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();


    if (!pProcInfo->m_var.b_app_showNormal) {
        this->showFullScreen();
    }
    // ui->stackedWidgetInfo->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    // ui->stackedWidgetContact->setAttribute(Qt::WA_TransparentForMouseEvents, true);
     //
    memset(&var, 0, sizeof(var));
       

    //
    QRect rc = QApplication::primaryScreen()->geometry();

    
    if (rc.width() <= MIN_DISPLAY) {
        //显示分辨率小于1280分辨率 调整一次
        system_resolution();
    }

    initControl();
    
    // updateMsgCount();
    winCl = this;

    this->setWindowFlags(Qt::FramelessWindowHint);


    // //切换主界面状态
    // 
    ui->widget_29->setVisible(true); //无会议
    ui->widget_item1->setVisible(false); //1个会议
    ui->widget_item2->setVisible(false); //2个会议
    ui->widget_item3->setVisible(false); //3个会议

    //

    ui->port_err->setVisible(false); //端口关闭提示信息
    ui->port_err->setWordWrap(true);

    // //



    this->layout()->setSizeConstraint(QLayout::SetMinimumSize);
    this->setFixedHeight(0);

    //setAttribute(Qt::WA_ShowWithoutActivating, true);

    //
    
    int dis_height = COUNT_display_height_value;
    int dis_width = COUNT_display_width_value;

    //记录分辨率
    pProcInfo->m_var.displayWidth = rc.width();
    pProcInfo->m_var.displayHeight = rc.height();

    //
    if (rc.height() < dis_height && rc.width() > dis_width) {
        //if (rc.height() < 800 && rc.width() > 900) {
        int rx = (rc.width() - 900) / 2;
        int ry = (rc.height() - 640) / 2;
        QRect rc1 = QRect(rx, ry, 900, 640);

        this->setGeometry(rc1);

    }




    //
#ifdef  __DEBUG__
#if  0
    HWND  hWnd = (HWND)this->winId();
    ::MoveWindow(hWnd, 0, 0, 100, 100, true);

#endif
#endif


    ////
    _sound = new QSoundEffect();
    QString sndFile = QString::fromUtf16((char16_t*)pProcInfo->m_var.installDir_qt) + "/resource/Sounds/msg.wav";
    if (bFileExists((TCHAR*)sndFile.utf16())) {
        _sound->setSource(QUrl::fromLocalFile(sndFile));// ":/Resources/Sounds/9450.wav"));
    }
    HWND_MAIN_ID = (HWND)this->winId();
    //
#if 10
    pQyMc->gui.hMainWnd = (HWND)this->winId();
    var.common.pQyMc = pQyMc;
    //
    HWND  m_hWnd = (HWND)this->winId();
    if (initVar_onCreate_mainFrame(0, m_hWnd, &this->var)) {
        goto  errLabel;
    }

#endif 


    //QDesktopWidget* desktopwidget = QApplication::desktop();
   
   // QScreen* desktopwidget; desktopwidget = QApplication::primaryScreen();
    // connect(desktopwidget, SIGNAL(resized(int)), this, SLOT(refResolution()));
    QScreen* pScreen; pScreen = QApplication::primaryScreen();
   
    connect(pScreen, &QScreen::geometryChanged, this, &CMainFrame::refResolution);


    m_pWinTimer = new QTimer(this);
    connect(m_pWinTimer, SIGNAL(timeout()), this, SLOT(on_timer_winMethod()));
    connect(m_pWinTimer, SIGNAL(timeout()), this, SLOT(on_time_update()));
    connect(m_pWinTimer, SIGNAL(timeout()), this, SLOT(sxrzStatus()));
    connect(m_pWinTimer, SIGNAL(timeout()), this, SLOT(portStatus()));

    m_pWinTimer->setInterval(1000);
    m_pWinTimer->start();


    m_pWaitMeetingTimer = new QTimer(this);
    connect(m_pWaitMeetingTimer, SIGNAL(timeout()), this, SLOT(on_time_upWaitMeetingList()));

    m_pWaitMeetingTimer->setInterval(5000);
    m_pWaitMeetingTimer->start();


    ////
    pQyMc->dbg.dwTickCnt_mainFrame_inited = myGetTickCount(mynull);
    int  iElapseInMs; iElapseInMs = pQyMc->dbg.dwTickCnt_mainFrame_inited - pQyMc->dbg.dwTickCnt_start;
    //int  ii = 0;

    ui->lab_tishi->installEventFilter(this);
    //
errLabel:
    return;


#ifdef  __DEBUG__
    traceLog((TCHAR*)_T("mainFrame::CMainFrame() leaves"));
#endif
}

//显示提示窗8
void CMainFrame::showHint(QString msg, QString fontColor, qint64 out_time) {

    NoticeWidget::showNotice(this, msg, fontColor, out_time);

}

//手动入会
void CMainFrame::on_btnMeeting_clicked(QString objname) {

    if (m_pInfraredMenu) {
        //按钮1
        if (objname == "menuBtn1") {
            m_pInfraredMenu->on_menuBtn1_clicked();
        }
        //按钮2
        if (objname == "menuBtn2") {
            m_pInfraredMenu->on_menuBtn2_clicked();
        }
        //按钮3
        if (objname == "menuBtn3") {
            m_pInfraredMenu->on_menuBtn3_clicked();
        }
        //按钮4
        if (objname == "menuBtn4") {
            m_pInfraredMenu->on_menuBtn4_clicked();
        }
        //
        if (objname == "btnVideo") {
            m_pInfraredMenu->on_btnVideo_clicked();
        }
        if (objname == "btnAudio") {
            m_pInfraredMenu->on_btnAudio_clicked();
        }
        //显示隐藏状态栏
        if (objname == "menuBtn5") {
            m_pInfraredMenu->on_menuBtn5_clicked();
        }
        //关机
        if (objname == "menuShutdown") {
            m_pInfraredMenu->on_menuShutdown_clicked();
        }
        //重启
        if (objname == "menuRestart") {
            m_pInfraredMenu->on_menuRestart_clicked();
        }
        //初始化设置
        if (objname == "menuSetting") {
            m_pInfraredMenu->on_menuSetting_clicked();
        }
        //退出登录
        if (objname == "btnLogOut") {
            m_pInfraredMenu->on_btnLogOut_clicked();
        }

        //显示调试窗
        if (objname == "menuDebug") {
            m_pInfraredMenu->on_menuDebug_clicked();
        }
        return;
    }

    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

    if (_isDoTaskId == 0) {
        return;
    }

    //
    int index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, _isDoTaskId);
    if (index_taskInfo < 0)  return;


    //判断终端类型

    if (pProcInfo->uiTerminalType != CONST_terminalType_mon) {
        //
        int  iTaskId_activeTaskAv = 0;
        if (bExists_activeTaskAv(pQyMc, &iTaskId_activeTaskAv, mynull)) {
            if (iTaskId_activeTaskAv != _isDoTaskId) {

                //qyMessageBox(hTool, _T("111已有一个会议在进行，不能开始新会议"), _T("qycx.com"), MB_OK, 3, null);
                showInfo_open0(0, 0, _T("已有一个会议在进行，不能开始新会议"));
                return;
            }
            return;
        }
    }
 

    //
    acceptTaskAv(_isDoTaskId);


    //
    //memset(&var.notifyTaskStatus, 0, sizeof(var.notifyTaskStatus));

    //
    return;
}

//手动入会第二个会议
void CMainFrame::on_btnMeeting2_clicked(QString objname) 
{
    if (m_pInfraredMenu) {
        //按钮1
        if (objname == "menuBtn1") {
            m_pInfraredMenu->on_menuBtn1_clicked();
        }
        //按钮2
        if (objname == "menuBtn2") {
            m_pInfraredMenu->on_menuBtn2_clicked();
        }
        //按钮3
        if (objname == "menuBtn3") {
            m_pInfraredMenu->on_menuBtn3_clicked();
        }
        //按钮4
        if (objname == "menuBtn4") {
            m_pInfraredMenu->on_menuBtn4_clicked();
        }
        //
        if (objname == "btnVideo") {
            m_pInfraredMenu->on_btnVideo_clicked();
        }
        if (objname == "btnAudio") {
            m_pInfraredMenu->on_btnAudio_clicked();
        }
        //显示隐藏状态栏
        if (objname == "menuBtn5") {
            m_pInfraredMenu->on_menuBtn5_clicked();
        }
        //关机
        if (objname == "menuShutdown") {
            m_pInfraredMenu->on_menuShutdown_clicked();
        }
        //重启
        if (objname == "menuRestart") {
            m_pInfraredMenu->on_menuRestart_clicked();
        }
        //初始化设置
        if (objname == "menuSetting") {
            m_pInfraredMenu->on_menuSetting_clicked();
        }
        //退出登录
        if (objname == "btnLogOut") {
            m_pInfraredMenu->on_btnLogOut_clicked();
        }

        //显示调试窗
        if (objname == "menuDebug") {
            m_pInfraredMenu->on_menuDebug_clicked();
        }
        return;
    }

    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

    //
    if (_isDoTaskId_2 == 0) {
        return;
    }

    //
    int index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, _isDoTaskId_2);
    if (index_taskInfo < 0)  return;
    
    //判断终端类型
    if (pProcInfo->uiTerminalType != CONST_terminalType_mon) {
        //
        int  iTaskId_activeTaskAv = 0;
        if (bExists_activeTaskAv(pQyMc, &iTaskId_activeTaskAv, mynull)) {
            if (iTaskId_activeTaskAv != _isDoTaskId_2) {

                //qyMessageBox(hTool, _T("111已有一个会议在进行，不能开始新会议"), _T("qycx.com"), MB_OK, 3, null);
                showInfo_open0(0, 0, _T("已有一个会议在进行，不能开始新会议"));
                return;
            }
            return;
        }
    }


    //
    acceptTaskAv(_isDoTaskId_2);


    //
    //memset(&var.notifyTaskStatus, 0, sizeof(var.notifyTaskStatus));

    //
    return;

}

//检查端口开启状态
void CMainFrame::portStatus() {

    CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
    QString err_txt = "";
    bool  is_err = false; //是否显示错误信息
    bool  is_sys_err = false; //是否是系统错误信息
    //hdmi int
    if (pProcInfo->av.hk.portStatus.bDisable_hdmiIn_vga) {
        err_txt = err_txt + u8"[HDMI IN]";
        is_err = true;
    }
    //hdmi2 out
    if (pProcInfo->av.hk.portStatus.bDisable_hdmi2Out_dvi) {
        err_txt = err_txt + u8"[HDMI2 OUT]";
        is_err = true;
    }
    if (pProcInfo->av.hk.portStatus.bDisable_hdmi1Out_hdmi) {
        err_txt = err_txt + u8"[HDMI1 OUT]";
        is_err = true;
    }
    if (pProcInfo->av.hk.portStatus.bDisable_usb_sxt_usb1) {
        err_txt = err_txt + u8"[USB 摄像头]";
        is_err = true;
    }if (pProcInfo->av.hk.portStatus.bDisable_usb_mkf_usb2) {
        err_txt = err_txt + u8"[USB 音频输入接口]";
        is_err = true;
    }if (pProcInfo->av.hk.portStatus.bDisable_lb_out) {
        err_txt = err_txt + u8"[USB 音频输出接口]";
        is_err = true;
    }if (pProcInfo->av.hk.portStatus.bDisable_usb_key_usb3) {
        err_txt = err_txt + u8"[USB UKEY]";
        is_err = true;
    }if (pProcInfo->av.hk.portStatus.bDisable_network) {
        err_txt = err_txt + u8"[LAN]";
        is_err = true;
    }

    //自动检测摄像头是否正常
    if (pProcInfo->av.localAv.chkCamera.mTimes_noCamera) {
        err_txt = u8"摄像头设备检测异常，请检查接口连接！";
        is_err = true;
        is_sys_err = true;
    }


#ifndef  __DEBUG__
    QY_REG  reg;
    TCHAR  tBuf[128];

    memset(&reg, 0, sizeof(reg));
    reg.hKeyRoot0 = HKEY_CURRENT_USER;
    lstrcpyn(reg.rootKey, _T(CONST_qyRootKey_qnmScheduler_misClient), mycountof(reg.rootKey));


    TCHAR* pRegVal = (TCHAR*)_T(CONST_regValName_sm_memOverTimes);
    unsigned  int  uiType = 0;
    if (!qyGetRegCfgT(reg.hKeyRoot0, CQyString(reg.rootKey), pRegVal, (char*)tBuf, sizeof(tBuf), &uiType)) {
        int  tmp_times = _ttol(tBuf);

        if (tmp_times) {
            err_txt = err_txt + u8"内存不足，请检查系统内存占用！";
            is_err = true;
            is_sys_err = true;
        }       
    }   

#endif

    if (is_err) {
        //判断属于系统错误信息的就直接报
        if (!is_sys_err) {
            err_txt = err_txt + u8"端口已被禁用，请及时打开！";
        }
        ui->port_err->setText(err_txt);
        ui->port_err->setVisible(true);
    }
    else {

        ui->port_err->setVisible(false);
    }


}

//认证状态检测
void CMainFrame::sxrzStatus()
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
    QRect rc = QApplication::primaryScreen()->geometry();



    if (rc.width() > 3500) {

        if (pProcInfo->xt.nTimes_waitForXtResp <= 1)
        {
            ui->lab_img2->setStyleSheet("border:none;background-image:url(':/Resources/Images/Sm/t9@2x.png');background-repeat:no-repeat;");
            ui->label_status->setStyleSheet("font-size:32px;color:#2C9AD0;");
            ui->label_status->setText(u8"认证正常");
        }
        else if (pProcInfo->xt.nTimes_waitForXtResp == 2) {
            ui->lab_img2->setStyleSheet("border:none;background-image:url(':/Resources/Images/Sm/t20@2x.png');background-repeat:no-repeat;");
            ui->label_status->setStyleSheet("font-size:32px;color:red;");
            ui->label_status->setText(u8"认证异常,正在重连!");
        }
        else if (pProcInfo->xt.nTimes_waitForXtResp == 3) {
            ui->lab_img2->setStyleSheet("border:none;background-image:url(':/Resources/Images/Sm/t20@2x.png');background-repeat:no-repeat;");
            ui->label_status->setStyleSheet("font-size:32px;color:red;");
            ui->label_status->setText(u8"认证失败,即将退出!");
           
        }
    }
    else {

        if (pProcInfo->xt.nTimes_waitForXtResp <= 1)
        {
            ui->lab_img2->setStyleSheet("border:none;background-image:url(':/Resources/Images/Sm/t9.png');background-repeat:no-repeat;");
            ui->label_status->setStyleSheet("font-size:16px;color:#2C9AD0;");
            ui->label_status->setText(u8"认证正常");
        }
        else if (pProcInfo->xt.nTimes_waitForXtResp == 2) {
            ui->lab_img2->setStyleSheet("border:none;background-image:url(':/Resources/Images/Sm/t20.png');background-repeat:no-repeat;");
            ui->label_status->setStyleSheet("font-size:16px;color:red;");
            ui->label_status->setText(u8"认证异常,正在重连!");
        }
        else if (pProcInfo->xt.nTimes_waitForXtResp == 3) {
            ui->lab_img2->setStyleSheet("border:none;background-image:url(':/Resources/Images/Sm/t20.png');background-repeat:no-repeat;");
            ui->label_status->setStyleSheet("font-size:16px;color:red;");
            ui->label_status->setText(u8"认证失败,即将退出!");
            
            
        }
    }


    //显示器分辨率检测
    auto screens = QGuiApplication::screens();


    //
    TCHAR  tBuf[128];
    _sntprintf(tBuf, mycountof(tBuf), _T("Display: %d,DISPLAY: %d-----%d,DISPLAYDISPLAY: %d ===%d"), screens.count(), pProcInfo->m_var.displayWidth , pProcInfo->m_var.displayHeight , rc.width() , rc.height());
    showInfo_open0(0, 0, tBuf);

    qDebug() << "width:-----" << ui->widget_4->width() <<"height:-----" << ui->widget_4->height();

    if (screens.count() >=1 && pProcInfo->m_var.displayWidth != rc.width() && pProcInfo->m_var.displayHeight != rc.height()) {
    
        closeDlgAvAccept();
        //
        HWND  m_hWnd = (HWND)this->winId();
        ::PostMessage(m_hWnd, WM_COMMAND, MAKEWPARAM(ID_qyQuitMainWnd, 0), 0);
        //
        pProcInfo->m_var.displayWidth = rc.width();
        pProcInfo->m_var.displayHeight = rc.height();
    }

   

    //显示用户信息
    ui->username->setText(QString::fromUtf16((char16_t*)pProcInfo->av.confLayout.login_userName));
    ui->terminalName->setText(QString::fromUtf16((char16_t*)pProcInfo->av.confLayout.login_termialName));


    //检测点对点呼叫状态
    Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
    if (!pCtxSm)  return;
    Ctx_sm& ctxSm = *pCtxSm;


    if (ctxSm.hg.p2pWarn.bWarn) {

        QString str = QString::fromUtf16((char16_t*)ctxSm.hg.p2pWarn.p2pContent);

        showHint(str, "red", 3000);

        qmcLogForHg(0, (wchar_t*)str.utf16(), false);


        ctxSm.hg.p2pWarn.bWarn = false;
    }

    if (ctxSm.hg.p2pMsg.bMsg) {

        QString str = QString::fromUtf16((char16_t*)ctxSm.hg.p2pMsg.formTermName);


        ctxSm.hg.p2pMsg.bMsg = false;

        CCtxQyMc* pQyMc = QY_GET_GBUF();
        if (!pQyMc) return;
        CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
        if (!pProcInfo)  return;
        //只在登陆状态打开
        if (!pProcInfo->xt.bUsrLogined) {
            return;
        }


        //
        if (!m_pP2pMsg)
        {
            m_pP2pMsg = new CDlgP2pMsg(this);

        }

        //
        if (!m_pP2pMsg->isVisible()) {

            //窗口只打开一次
            m_pP2pMsg->show();


        }
        else {
            m_pP2pMsg->close();
            if (m_pP2pMsg)
            {
                delete m_pP2pMsg;
                m_pP2pMsg = nullptr;
            }
        }


    }




}

//系统时间  丢包率
void CMainFrame::on_time_update()
{

 

    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

    //CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    //
    TCHAR  tBuf[128];

    ui->label_time->setText(u8"     当前时间：" + QDateTime::currentDateTime().toString(u8"yyyy年MM月dd日 hh:mm:ss"));


    //丢包率
    _sntprintf(tBuf, mycountof(tBuf), _T("%.02f%%"), pMisCnt->status.fDiscards * 100.);
    ui->lab_packet->setText(QString::fromUtf16((char16_t*)tBuf));

    //
    ui->lab_rate->setText(u8"下行：" + QString::number(pProcInfo->status.netStat.ins.uiInSpeedInKbps) + u8"，上行：" + QString::number(pProcInfo->status.netStat.ins.uiOutSpeedInKbps) + " kbps");


}

bool CMainFrame::isShareOpen()
{
    if (m_Share)
        return true;
    else
        return false;
}
//样式
void CMainFrame::sheetBackgroundImage() {
    QRect rc = QApplication::primaryScreen()->geometry();

    if (rc.width() > 3500) {
        ui->widget_4->setStyleSheet("#widget_4{border-image:url(':/Resources/Images/Sm/t10@2x.png');}");
        ui->widget_8->setStyleSheet("background-position:center;background-image:url(':/Resources/Images/Sm/t19@2x.png');background-repeat:no-repeat;");
        ui->widget_6->setStyleSheet("background-position:center;background-image:url(':/Resources/Images/Sm/t18@2x.png');background-repeat:no-repeat;");
        // ui->pushButton->setStyleSheet("color:#2C9AD0;font-size:36px;background-image:url(':/Resources/Images/Sm/t1@2x.png');background-repeat:100%;border:0px;border-raudia:5px;qproperty-icon:url(':/Resources/Images/Sm/t2@2x.png')");

         //三个item
        ui->widget_item1->setStyleSheet("background-image:url(':/Resources/Images/Sm/t5@2x.png');background-repeat:no-repeat;");
        ui->widget_item2->setStyleSheet("background-image:url(':/Resources/Images/Sm/t5@2x.png');background-repeat:no-repeat;");
        ui->widget_item3->setStyleSheet("background-image:url(':/Resources/Images/Sm/t5@2x.png');background-repeat:no-repeat;");
        ui->lab_title1->setStyleSheet("font-size:56px;font-weight:bold;color:#2C9AD0");
        ui->lab_t2->setStyleSheet("font-size:36px;color:#1F3D5B");
        ui->lab_t1->setStyleSheet("font-size:36px;color:#1F3D5B");
        ui->lab_t3->setStyleSheet("font-size:36px;color:#1F3D5B");
        ui->lab_t4->setStyleSheet("font-size:36px;color:#1F3D5B");
        ui->lab_t20->setStyleSheet("font-size:36px;color:#1F3D5B");
        ui->start_time1->setStyleSheet("font-size:56px;font-weight:bold;color:#2C9AD0");
        ui->bur_bumen1->setStyleSheet("font-size:36px;color:#fff");
        ui->security1->setStyleSheet("font-size:36px;color:#fff");
        ui->sponsor1->setStyleSheet("font-size:36px;color:#fff");
        ui->meetingId1->setStyleSheet("font-size:36px;color:#fff");
        ui->btnMeeting->setStyleSheet("QPushButton{font-size:50px;color:#fff;background:#5C8CFC;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

        //2item
        ui->lab_title2->setStyleSheet("font-size:56px;font-weight:bold;color:#2C9AD0");
        ui->lab_t5->setStyleSheet("font-size:36px;color:#1F3D5B");
        ui->lab_t6->setStyleSheet("font-size:36px;color:#1F3D5B");
        ui->lab_t7->setStyleSheet("font-size:36px;color:#1F3D5B");
        ui->lab_t8->setStyleSheet("font-size:36px;color:#1F3D5B");
        ui->lab_t21->setStyleSheet("font-size:36px;color:#1F3D5B");
        ui->btnMeeting2->setStyleSheet("QPushButton{font-size:50px;color:#fff;background:#5C8CFC;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

        ui->start_time2->setStyleSheet("font-size:56px;font-weight:bold;color:#2C9AD0");
        ui->bur_bumen2->setStyleSheet("font-size:36px;color:#fff");
        ui->security2->setStyleSheet("font-size:36px;color:#fff");
        ui->sponsor2->setStyleSheet("font-size:36px;color:#fff");
        ui->meetingId2->setStyleSheet("font-size:36px;color:#fff");

        //3item
        ui->lab_title3->setStyleSheet("font-size:56px;font-weight:bold;color:#2C9AD0");
        ui->lab_t9->setStyleSheet("font-size:36px;color:#1F3D5B");
        ui->lab_t10->setStyleSheet("font-size:36px;color:#1F3D5B");
        ui->lab_t11->setStyleSheet("font-size:36px;color:#1F3D5B");
        ui->lab_t12->setStyleSheet("font-size:36px;color:#1F3D5B");
        ui->lab_t22->setStyleSheet("font-size:36px;color:#1F3D5B");
        ui->start_time3->setStyleSheet("font-size:56px;font-weight:bold;color:#2C9AD0");
        ui->bur_bumen3->setStyleSheet("font-size:36px;color:#fff");
        ui->security3->setStyleSheet("font-size:36px;color:#fff");
        ui->sponsor3->setStyleSheet("font-size:36px;color:#fff");
        ui->meetingId3->setStyleSheet("font-size:36px;color:#fff");


        //底部
        ui->footer->setStyleSheet("#footer{border-image:url(':/Resources/Images/Sm/t7@2x.png');}");
        ui->terminalName->setStyleSheet("font-size:35px;color:#fff;");
        ui->username->setStyleSheet("font-size:35px;color:#fff;");
        //ui->label_ver->setStyleSheet("font-size:32px;color:#fff;");
        ui->lab_n1->setStyleSheet("font-size:32px;color:#1F3D5B;");
        ui->lab_n5->setStyleSheet("font-size:32px;color:#1F3D5B;");
        ui->lab_n2->setStyleSheet("font-size:32px;color:#1F3D5B;");
        ui->lab_n3->setStyleSheet("font-size:32px;color:#1F3D5B;");
        ui->lab_rate->setStyleSheet("font-size:32px;color:#1F3D5B;");
        ui->lab_packet->setStyleSheet("font-size:32px;color:#1F3D5B;");
        ui->label_status->setStyleSheet("font-size:32px;color:#2C9AD0;");
        ui->label_time->setStyleSheet("font-size:32px;color:#2C9AD0;");
        ui->lab_img1->setStyleSheet("border:none;background-image:url(':/Resources/Images/Sm/t8@2x.png');background-repeat:no-repeat;");
        ui->lab_img2->setStyleSheet("border:none;background-image:url(':/Resources/Images/Sm/t9@2x.png');background-repeat:no-repeat;");

        //无会议状态
        ui->lab_img3->setStyleSheet("background-image:url(':/Resources/Images/Sm/t11@2x.png');background-repeat:no-repeat;border:none");
        ui->lab_tishi->setStyleSheet("font-size:96px;font-weight:bold;color:#fff");

        ui->port_err->setStyleSheet("font-size:32px;color:red");


        ui->widget_item1->setContentsMargins(17, 30, 7, 140); // 80  186
        ui->widget_item2->setContentsMargins(17, 30, 7, 140);
        ui->widget_item3->setContentsMargins(17, 30, 7, 140);
        ui->lab_img2->setFixedSize(46, 46);
        ui->lab_img1->setFixedSize(52, 40);
        ui->btnMeeting->setFixedSize(400, 100);
        ui->btnMeeting2->setFixedSize(400, 100);
    }
    else {

        ui->widget_4->setStyleSheet("#widget_4{background-image:url(':/Resources/Images/Sm/t10.png');}");
        ui->widget_8->setStyleSheet("background-position:center;background-image:url(':/Resources/Images/Sm/t19.png');background-repeat:no-repeat;");
        ui->widget_6->setStyleSheet("background-position:center;background-image:url(':/Resources/Images/Sm/t18.png');background-repeat:no-repeat;");
        // ui->pushButton->setStyleSheet("color:#2C9AD0;font-size:36px;background-image:url(':/Resources/Images/Sm/t1@2x.png');background-repeat:100%;border:0px;border-raudia:5px;qproperty-icon:url(':/Resources/Images/Sm/t2@2x.png')");

        // //三个item
        ui->widget_item1->setStyleSheet("#widget_item1{border-image:url(':/Resources/Images/Sm/t5.png');background-repeat:no-repeat;}");
        ui->widget_item2->setStyleSheet("#widget_item2{border-image:url(':/Resources/Images/Sm/t5.png');background-repeat:no-repeat;}");
        ui->widget_item3->setStyleSheet("#widget_item3{border-image:url(':/Resources/Images/Sm/t5.png');background-repeat:no-repeat;}");
        ui->lab_title1->setStyleSheet("font-size:28px;font-weight:bold;color:#2C9AD0");
        ui->lab_t2->setStyleSheet("font-size:18px;color:#1F3D5B");
        ui->lab_t1->setStyleSheet("font-size:18px;color:#1F3D5B");
        ui->lab_t3->setStyleSheet("font-size:18px;color:#1F3D5B");
        ui->lab_t4->setStyleSheet("font-size:18px;color:#1F3D5B");
        ui->lab_t20->setStyleSheet("font-size:18px;color:#1F3D5B");
        ui->start_time1->setStyleSheet("font-size:28px;font-weight:bold;color:#2C9AD0");
        ui->bur_bumen1->setStyleSheet("font-size:18px;color:#fff");
        ui->security1->setStyleSheet("font-size:18px;color:#fff");
        ui->sponsor1->setStyleSheet("font-size:18px;color:#fff");
        ui->meetingId1->setStyleSheet("font-size:18px;color:#fff");
        ui->btnMeeting->setStyleSheet("QPushButton{font-size:23px;color:#fff;background:#5C8CFC;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

        ////2item
        ui->lab_title2->setStyleSheet("font-size:28px;font-weight:bold;color:#2C9AD0");
        ui->lab_t5->setStyleSheet("font-size:18px;color:#1F3D5B");
        ui->lab_t6->setStyleSheet("font-size:18px;color:#1F3D5B");
        ui->lab_t7->setStyleSheet("font-size:18px;color:#1F3D5B");
        ui->lab_t8->setStyleSheet("font-size:18px;color:#1F3D5B");
        ui->lab_t21->setStyleSheet("font-size:18px;color:#1F3D5B");
        ui->start_time2->setStyleSheet("font-size:28px;font-weight:bold;color:#2C9AD0");
        ui->bur_bumen2->setStyleSheet("font-size:18px;color:#fff");
        ui->security2->setStyleSheet("font-size:18px;color:#fff");
        ui->sponsor2->setStyleSheet("font-size:18px;color:#fff");
        ui->meetingId2->setStyleSheet("font-size:18px;color:#fff");
        ui->btnMeeting2->setStyleSheet("QPushButton{font-size:23px;color:#fff;background:#5C8CFC;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

        ////3item
        ui->lab_title3->setStyleSheet("font-size:28px;font-weight:bold;color:#2C9AD0");
        ui->lab_t9->setStyleSheet("font-size:18px;color:#1F3D5B");
        ui->lab_t10->setStyleSheet("font-size:18px;color:#1F3D5B");
        ui->lab_t11->setStyleSheet("font-size:18px;color:#1F3D5B");
        ui->lab_t12->setStyleSheet("font-size:18px;color:#1F3D5B");
        ui->lab_t22->setStyleSheet("font-size:18px;color:#1F3D5B");
        ui->start_time3->setStyleSheet("font-size:28px;font-weight:bold;color:#2C9AD0");
        ui->bur_bumen3->setStyleSheet("font-size:18px;color:#fff");
        ui->security3->setStyleSheet("font-size:18px;color:#fff");
        ui->sponsor3->setStyleSheet("font-size:18px;color:#fff");
        ui->meetingId3->setStyleSheet("font-size:18px;color:#fff");


        ////底部
        ui->footer->setStyleSheet("#footer{border-image:url(':/Resources/Images/Sm/t7.png');background-repeat:no-repeat;}");
        ui->username->setStyleSheet("font-size:19px;color:#fff;");
        ui->terminalName->setStyleSheet("font-size:19px;color:#fff;");
        //ui->label_ver->setStyleSheet("font-size:16px;color:#fff;");
        ui->lab_n1->setStyleSheet("font-size:16px;color:#1F3D5B;");
        ui->lab_n5->setStyleSheet("font-size:16px;color:#1F3D5B;");
        ui->lab_n2->setStyleSheet("font-size:16px;color:#1F3D5B;");
        ui->lab_n3->setStyleSheet("font-size:16px;color:#1F3D5B;");
        ui->lab_rate->setStyleSheet("font-size:16px;color:#1F3D5B;");
        ui->lab_packet->setStyleSheet("font-size:16px;color:#1F3D5B;");
        ui->label_status->setStyleSheet("font-size:16px;color:#2C9AD0;");
        ui->label_time->setStyleSheet("font-size:16px;color:#2C9AD0;");

        ui->port_err->setStyleSheet("font-size:18px;color:red");

        ui->lab_img1->setStyleSheet("border:none;border-image:url(':/Resources/Images/Sm/t8.png');background-repeat:no-repeat;");
        ui->lab_img2->setStyleSheet("border:none;border-image:url(':/Resources/Images/Sm/t9.png');background-repeat:no-repeat;");

        ////无会议状态
        ui->lab_img3->setStyleSheet("background-image:url(':/Resources/Images/Sm/t11.png');background-repeat:no-repeat;border:none");
        ui->lab_tishi->setStyleSheet("font-size:48px;font-weight:bold;color:#fff");

        ui->widget_8->setFixedSize(1640, 702);
        //ui->widget_6->setFixedHeight(76);
        ui->widget_item1->setFixedSize(483, 451);
        ui->widget_item2->setFixedSize(483, 451);
        ui->widget_item3->setFixedSize(483, 451);
        ui->lab_img3->setFixedSize(239, 262);
        ui->lab_img2->setFixedSize(23, 23);
        ui->lab_img1->setFixedSize(26, 20);
        ui->btnMeeting->setFixedSize(200, 50);
        ui->btnMeeting2->setFixedSize(200, 50);


        ui->lab_t1->setFixedWidth(80);
        ui->lab_t4->setFixedWidth(80);

        ui->lab_t3->setFixedWidth(80);
        ui->lab_t5->setFixedWidth(80);
        ui->lab_t6->setFixedWidth(80);
        ui->lab_t7->setFixedWidth(80);
        ui->lab_t10->setFixedWidth(80);
        ui->lab_t11->setFixedWidth(80);
        ui->lab_t12->setFixedWidth(80);
        //ui->widget_9->setFixedWidth(100);
        ui->footer->setFixedHeight(80);


        ui->widget_item1->setContentsMargins(17, 10, 7, 30);
        ui->widget_item2->setContentsMargins(17, 10, 7, 30);
        ui->widget_item3->setContentsMargins(17, 10, 7, 30);

        /*  QSize a = ui->widget->size();
          QSize aa = ui->widget_4->size(); */
        
    }
    ui->widget_4->setFixedWidth(rc.width());
    ui->widget_4->setFixedHeight(rc.height());
}

//更新待开会数据
void CMainFrame::on_time_upWaitMeetingList()
{
    //检测下分辨率再
    //sheetBackgroundImage();

    //清空
    ui->widget_29->setVisible(true); //无会议
    ui->widget_item1->setVisible(false); //1个会议
    ui->widget_item2->setVisible(false); //2个会议
    ui->widget_item3->setVisible(false); //3个会议

    //
    _q_grp.clear();
    toContactList();


    _q_grp;
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
    _isDoTaskId = 0;


    if (pProcInfo->m_var.usrInput.dwLastTickCnt_usrLoginFinished) {
        OldConfs  oldConfs = { 0 };
    
            if (!findOldRecvdConfsActive(&oldConfs))
            {
                //
                int  i;
                for (i = 0; i < oldConfs.usCnt; i++) {
                    OldConfMem* pMem = &oldConfs.mems[i];

                    if (pMem->idInfo_peer.ui64Id == pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingId) {

                        _isDoTaskId = pMem->iTaskId;

                      
                    }

                    //  _sntprintf(tBuf, mycountof(tBuf), _T("oldConfs[%d]: %I64u, e_lastRefreshed %dms"), i, pMem->idInfo_peer.ui64Id, pMem->uiElapseInms_lastRefreshed);

                }
            }

        


    

    }


    
    //零信任版本先隐藏  
    if (qyGetCustomId() != CONST_qyCustomId_business) 
    {
        if (pProcInfo->m_var.usrInput.dwLastTickCnt_usrLoginFinished) {
            OldConfs  oldConfs = { 0 };
            //零信任版本先隐藏  
            if (qyGetCustomId() != CONST_qyCustomId_business) {

                if (!findOldRecvdConfsActive(&oldConfs))
                {
                    //借用下隐藏
                    ui->username->setVisible(false);
                    ui->lab_n1->setVisible(false);

                    //
                    int  i;

                    //会议名
                    QString meetName = "";

                    //会议id
                    qint64 meetId = 0;

                    _q_grp_ing.clear();

                    
                    for (i = 0; i < oldConfs.usCnt; i++) {
                        OldConfMem* pMem = &oldConfs.mems[i];

                        //判断终端类型  强制自动入会
                        if (pProcInfo->uiTerminalType == CONST_terminalType_mon || pProcInfo->uiTerminalType == CONST_terminalType_conf) {

                            //
                            int index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, pMem->iTaskId);
                            if (index_taskInfo < 0)  return;

                            //
                            static DWORD  sdwLastTickCnt_accept = 0;
                            DWORD  tickCnt = myGetTickCount(mynull);
                            int  iDiffInMs = tickCnt - sdwLastTickCnt_accept;
                            if (abs(iDiffInMs) > 20000) {
                                //
                                sdwLastTickCnt_accept = tickCnt;

                                //如有多余窗口 直接关闭
                                on_closeOther_slots();
                                on_closePortSetting_slots();
                                on_P2pMsg_close();

                                //
                                acceptTaskAv(pMem->iTaskId);
                            }

                        }


                        //if (pMem->idInfo_peer.ui64Id == pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingId) {
                        if (i == 0) {
                            _isDoTaskId = pMem->iTaskId;
                        }
                        else if(i == 1) {
                            _isDoTaskId_2 = pMem->iTaskId;
                        }

                            
                            myFriendInfo tmp_grpInfo;
                            //meetId = pMem->idInfo_peer.ui64Id;
                             tmp_grpInfo.userId = pMem->idInfo_peer.ui64Id;

                            for (int ii = 0; ii < _q_grp.size(); ii++) {
                                if (pMem->idInfo_peer.ui64Id == _q_grp[ii].userId)
                                {
                                    tmp_grpInfo.grpName = _q_grp[ii].grpName;
                                }
                            }
                            _q_grp_ing.append(tmp_grpInfo);
                       // }
                    }
                    
                    if (_isDoTaskId) {
                        MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
                        if (pMisCnt && isQEmpty(&pMisCnt->talkingFriendQ)) {
                            //有活跃的会
                            ui->widget_29->setVisible(false); //无会议
                            ui->widget_item1->setVisible(true); //1个会议
                            QString startTime = "";
                            int index = 0;
                            ui->lab_title1->setText(_q_grp_ing[0].grpName);
                            ui->start_time1->setText(startTime);
                            ui->bur_bumen1->setText("");
                            ui->security1->setText(u8"");
                            ui->meetingId1->setText(QString::number(_q_grp_ing[0].userId));
                            ui->sponsor1->setText(u8"已开始");
                            ui->lab_t20->setText(u8"会议ID:");
                            ui->lab_t4->setText(u8"状态：");
                            //ui->widget_14->setVisible(false);
                            ui->widget_17->setVisible(false);
                            ui->widget_15->setVisible(false);
                            ui->widget_16->setVisible(false);
                            ui->widget_btn->setVisible(true);


                            //两个会议
                            index = 1;
                            if (index < _q_grp_ing.size()) {
                                ui->lab_title2->setText(_q_grp_ing[index].grpName);

                                ui->start_time2->setText(startTime);

                                ui->bur_bumen2->setText("");

                                ui->security2->setText(u8"");
                                //
                                ui->meetingId2->setText(QString::number(_q_grp_ing[index].userId));



                                ui->sponsor2->setText(u8"已开始");
                                ui->lab_t21->setText(u8"会议ID:");
                                ui->lab_t7->setText(u8"状态：");

                                ui->widget_item3->setVisible(true); //2个会议
                                ui->widget_19->setVisible(false);
                                ui->widget_18->setVisible(false);
                                ui->widget_21->setVisible(false);
                            }

                            index = 3;
                            //三个会议                     


                        }                     
                        


                    } 
                    
                }
            }
        }
            
    
    }else {
        
        if (QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingName) != "")
        {
            ui->widget_29->setVisible(false); //无会议
            ui->widget_item1->setVisible(true); //1个会议
            QString startTime = QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingData) + " " + QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingTime);

            ui->lab_title1->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingName));
            ui->start_time1->setText(startTime);
            ui->bur_bumen1->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingDepartment));
            if (pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingLevel == -1)
            {
                ui->security1->setText(u8"公开");
            }
            else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingLevel == 1)
            {
                ui->security1->setText(u8"内部");
            }
            else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingLevel == 2)
            {
                ui->security1->setText(u8"秘密");
            }
            else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingLevel == 3)
            {
                ui->security1->setText(u8"机密");
            }

            ui->meetingId1->setText(QString::number(pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingId));
            ui->sponsor1->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingConvener));


            //判断会议是否已开始
            QDateTime tmp_time = QDateTime::fromString(startTime, "yyyy-MM-dd hh:mm:ss");
            int startMeetingTime = tmp_time.toSecsSinceEpoch();// .toTime_t();
            int timeStamp = QDateTime::currentDateTime().toSecsSinceEpoch();// .toTime_t();

            if (startMeetingTime > timeStamp) {
                ui->widget_btn->setVisible(false);

            }

        }
        
    }
    

    

    if (QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingName) != "")
    {
        //sm藏掉
        ui->widget_btn2->setVisible(false);
        //
        ui->lab_title2->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingName));

        ui->start_time2->setText(QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingData) + " " + QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingTime));

        ui->bur_bumen2->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingDepartment));
        if (pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingLevel == -1)
        {
            ui->security2->setText(u8"公开");
        }
        else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingLevel == 1)
        {
            ui->security2->setText(u8"内部");
        }
        else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingLevel == 2)
        {
            ui->security2->setText(u8"秘密");
        }
        else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingLevel == 3)
        {
            ui->security2->setText(u8"机密");
        }


        ui->meetingId2->setText(QString::number(pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingId));

        ui->sponsor2->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingConvener));

        ui->widget_item3->setVisible(true); //2个会议

    }

    if (QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingName) != "")
    {


        // //
        ui->lab_title3->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingName));
        ui->start_time3->setText(QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingData) + " " + QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingTime));
        ui->bur_bumen3->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingDepartment));

        if (pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingLevel == -1)
        {
            ui->security3->setText(u8"公开");
        }
        else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingLevel == 1)
        {
            ui->security3->setText(u8"内部");
        }
        else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingLevel == 2)
        {
            ui->security3->setText(u8"秘密");
        }
        else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingLevel == 3)
        {
            ui->security3->setText(u8"机密");
        }
        ui->meetingId3->setText(QString::number(pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingId));
        ui->sponsor3->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingConvener));
        ui->widget_item2->setVisible(true); //3个会议
    }





    /*

    if (QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingName) != "")
    {
        ui->widget_29->setVisible(false); //无会议
        ui->widget_item1->setVisible(true); //1个会议
        QString startTime = QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingData) + " " + QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingTime);

        ui->lab_title1->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingName));
        ui->start_time1->setText(startTime);
        ui->bur_bumen1->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingDepartment));
        if (pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingLevel == -1)
        {
            ui->security1->setText(u8"公开");
        }
        else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingLevel == 1)
        {
            ui->security1->setText(u8"内部");
        }
        else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingLevel == 2)
        {
            ui->security1->setText(u8"秘密");
        }
        else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingLevel == 3)
        {
            ui->security1->setText(u8"机密");
        }

        ui->meetingId1->setText(QString::number(pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingId));
        ui->sponsor1->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[0].meetingConvener));


        //判断会议是否已开始
        QDateTime tmp_time = QDateTime::fromString(startTime,"yyyy-MM-dd hh:mm:ss");
        int startMeetingTime = tmp_time.toTime_t();
        int timeStamp = QDateTime::currentDateTime().toTime_t();

        if (startMeetingTime > timeStamp) {
            ui->widget_btn->setVisible(false);

        }

    }

    if (QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingName) != "")
    {

        //
        ui->lab_title2->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingName));

        ui->start_time2->setText(QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingData) + " " + QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingTime));

        ui->bur_bumen2->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingDepartment));
        if (pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingLevel == -1)
        {
            ui->security2->setText(u8"公开");
        }
        else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingLevel == 1)
        {
            ui->security2->setText(u8"内部");
        }
        else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingLevel == 2)
        {
            ui->security2->setText(u8"秘密");
        }
        else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingLevel == 3)
        {
            ui->security2->setText(u8"机密");
        }


        ui->meetingId2->setText(QString::number(pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingId));

        ui->sponsor2->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[1].meetingConvener));

        ui->widget_item3->setVisible(true); //2个会议

    }

    if (QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingName) != "")
    {


        // //
        ui->lab_title3->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingName));
        ui->start_time3->setText(QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingData) + " " + QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingTime));
        ui->bur_bumen3->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingDepartment));

        if (pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingLevel == -1)
        {
            ui->security3->setText(u8"公开");
        }
        else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingLevel == 1)
        {
            ui->security3->setText(u8"内部");
        }
        else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingLevel == 2)
        {
            ui->security3->setText(u8"秘密");
        }
        else if (pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingLevel == 3)
        {
            ui->security3->setText(u8"机密");
        }
        ui->meetingId3->setText(QString::number(pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingId));
        ui->sponsor3->setText(QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[2].meetingConvener));
        ui->widget_item2->setVisible(true); //3个会议
    }
    */
    

    if (!m_pPortSetting) {
        ui->btnMeeting->setFocus();
    }
}


//
int tmpHandler_getContactList_sm(void* p0, void* p1, void* p2)
{
    int  iRet = -1;
    COMMON_PARAM* pCommonParam0 = (COMMON_PARAM*)p0;
    //
    CMyDb* pDb = (CMyDb*)pCommonParam0->p0;
    //  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
    //HWND				hListCtrl = (HWND)pCommonParam->p1;
    //if (!hListCtrl)  goto  errLabel;
    int				iItem = (int)pCommonParam0->p2;
    //
    //BOOL				bUnprocedOnly = (BOOL)p1;
    COMMON_PARAM* pCommonParam1 = (COMMON_PARAM*)p1;
    QList<myFriendInfo>* pq_grp = (QList<myFriendInfo>*)pCommonParam1->p0;
    QList<myFriendInfo>* pq_tmpGrp = (QList<myFriendInfo>*)pCommonParam1->p1;
    QList<myFriendInfo>* pq_contact = (QList<myFriendInfo>*)pCommonParam1->p2;


    //
    QMEM_qyImObj* pQMem = (QMEM_qyImObj*)p2;

    int				index = 0;
    QY_MC* pQyMc = QY_GET_GBUF();

    QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable);

    QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
    if (!pDbFuncs)  return  -1;// goto  errLabel;
    QM_dbFuncs& g_dbFuncs = *pDbFuncs;

    if (pQMem->messengerInfo.iStatus == CONST_qyStatus_ok)
    {
        winCl->addToContactList_main(pDb, pCommonParam1, pQMem);
    }
    iRet = 0;
errLabel:
    return  iRet;
}


int CMainFrame::toContactList()
{
    int  iRet = -1;
    QY_MC* pQyMc = QY_GET_GBUF();
    int	 iServiceId = CONST_qyServiceId_mis;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return  -1;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (!pMisCnt)  return  -1;
    //
    if (pQyMc->cfg.db.iDbType != CONST_dbType_myDb)
    {
        return  -1;
    }
    HTREEITEM				tmphtItem = NULL;
    TCHAR					displayName[512] = _T("");
    int						iObjId = 0;
    int						nImage, nSelectedImage;
    int						iTopFieldId = 0;
    char					topLevelColName[128] = "'";
    char* p = NULL;
    int						i;
    int						iObjType = 0;
    TCHAR					tBuf[1024];
    char					buf[256];

    QY_OBJ_DB* pObjDb = getProcedObjDb(pQyMc, 0, pQyMc->iDsnIndex_mainSys);
    if (!bObjDbAvail(pObjDb)) return -1;
    //
    CMyDb* pDb = (CMyDb*)pObjDb->pDb;
    int cnt = 0;
    COMMON_PARAM	commonParam0;
    MACRO_makeCommonParam3(pDb, 0, (void*)cnt, commonParam0);
    //_q_grp;
    QList <myFriendInfo>q_tmpGrp;
    QList<myFriendInfo>q_contact;
    COMMON_PARAM commonParam1;
    MACRO_makeCommonParam3(&_q_grp, &q_tmpGrp, &q_contact, commonParam1);

    //qTraverse(pDb->m_var.pQ_qyImObjTab, getContactList, &commonParam0, NULL);
    qTraverse(pDb->m_var.pQ_qyImObjTab, tmpHandler_getContactList_sm, &commonParam0, &commonParam1);

    //
    //群组排序
    //qSort(q_grp.begin(), q_grp.end(), q_grpListSort);
    //qSort(q_tmpGrp.begin(), q_tmpGrp.end(), q_grpListSort);
    ////联系人排序

    //qSort(q_contact.begin(), q_contact.end(), q_contactListSort);
    //
  /*  fillGrp(q_grp);
  /*  fillGrp(q_grp);
    fillTmpGrp(q_tmpGrp);
    fillContact(q_contact);*/

    int iiiii = 0;
    //
    //this->m_pRootFriendItemFriend->setExpanded(true);


    //
    iRet = 0;
errLabel:
    return  iRet;
}

//
void CMainFrame::addToContactList_main(CMyDb* pDb, COMMON_PARAM* pCommonParam1, QMEM_qyImObj* pQMem)
{
    QList<myFriendInfo>* pq_grp = (QList<myFriendInfo>*)pCommonParam1->p0;
    QList<myFriendInfo>* pq_tmpGrp = (QList<myFriendInfo>*)pCommonParam1->p1;
    QList<myFriendInfo>* pq_contact = (QList<myFriendInfo>*)pCommonParam1->p2;

    QY_MC* pQyMc = QY_GET_GBUF();
    MY_REG_DESC					desc;
    TCHAR						tBuf[256];
    QY_MESSENGER_REGINFO		regInfo;
    QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
    QM_dbFuncs& g_dbFuncs = *pDbFuncs;
    TCHAR						grpIdBuf[256];
    memset(&regInfo, 0, sizeof(regInfo));
    IM_GRP_INFO					grp_info;
    memset(&grp_info, 0, sizeof(grp_info));

    _sntprintf(tBuf, mycountof(tBuf), _T("%I64u"), pQMem->messengerInfo.idInfo.ui64Id);
    if (pQMem->messengerInfo.iStatus == CONST_qyStatus_ok)
    {
        if (pQMem->messengerInfo.uiType != CONST_objType_imGrp)
        {
            if (!g_dbFuncs.pf_bGetMessengerRegInfoBySth(pDb, CONST_dbType_myDb, getResTable(0, &pQyMc->cusRes, CONST_resId_fieldIdTable), CONST_tabName_qyImObjRegInfoTab, pQMem->messengerInfo.misServName, &pQMem->messengerInfo.idInfo, 0, &regInfo))
            {
                memset(&regInfo, 0, sizeof(regInfo));
            }
            int		tmpiRet;
            TCHAR	talkerDesc[128] = _T("");
            regInfo2Desc(0, &regInfo, &desc, talkerDesc, mycountof(talkerDesc), NULL, 0);
            QString pdw = QString::fromWCharArray(desc.pDw).trimmed();
            QString pBm = QString::fromWCharArray(desc.pBm).trimmed();
            QString pSyr = QString::fromWCharArray(desc.pSyr).trimmed();
            QString idinfo = QString::fromWCharArray(tBuf);
            //
            myFriendInfo fi;
            fi.userId = pQMem->messengerInfo.idInfo.ui64Id;
            fi.dw = pdw;
            fi.bm = pBm;
            if (pSyr.isEmpty()) {
                fi.syr = QString::number(pQMem->messengerInfo.idInfo.ui64Id);
            }
            else {
                fi.syr = pSyr;
            }

            CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
            if (!pProcInfo)  return;
            MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
            QY_MESSENGER_ID  idInfo;
            //
            idInfo.ui64Id = idinfo.toInt();
            //isCli_addTo_qmObjQ(idInfo);


            pq_contact->append(fi);

        }
        else if (pQMem->messengerInfo.uiType == CONST_objType_imGrp)
        {
            if (!g_dbFuncs.pf_bGetImGrpInfoBySth(pDb, CONST_dbType_myDb, pQMem->messengerInfo.misServName, &pQMem->messengerInfo.idInfo, &grp_info))
            {
                memset(&grp_info, 0, sizeof(grp_info));
            };
            _sntprintf(grpIdBuf, mycountof(grpIdBuf), _T("%I64u"), grp_info.idInfo.ui64Id);
            QString pdw = QString::fromWCharArray(grp_info.name).trimmed();
            QString idinfo = QString::fromWCharArray(tBuf);
            QString idInfo_creator = QString::number(grp_info.idInfo_creator.ui64Id);// :fromWCharArray(grpIdBuf);
            //if (!pdw.isEmpty())
            {
                if (pdw.isEmpty()) {
                    pdw = QString::number(pQMem->messengerInfo.idInfo.ui64Id);
                }

                //
                if (grp_info.idInfo_creator.ui64Id) {
                    myFriendInfo  fi;
                    fi.userId = pQMem->messengerInfo.idInfo.ui64Id;
                    fi.grpName = pdw;
                    pq_tmpGrp->append(fi);
                }
                else {
                    myFriendInfo fi;
                    fi.userId = pQMem->messengerInfo.idInfo.ui64Id;
                    fi.grpName = pdw;
                    pq_grp->append(fi);
                }

                //if (grpInfoMap.isEmpty() || grpInfoMap.value(grp_info.idInfo.ui64Id).isEmpty())
                {
                    //grpInfoMap.insert(grp_info.idInfo.ui64Id, pdw);


                }
            }
        }
    }
}

//刷新分辨率
void CMainFrame::refResolution()
{
    QRect rc = QApplication::primaryScreen()->geometry();
    //
    ui->widget_4->setFixedWidth(rc.width());
    ui->widget_4->setFixedHeight(rc.height());
    sheetBackgroundImage();
}

void CMainFrame::on_infraredMenu()
{
    //
    if (!m_pInfraredMenu)
    {
        m_pInfraredMenu = new CInfraredDialogMenu(this, "index");

    }

    //

    if (!m_pInfraredMenu->isVisible()) {
        //窗口只打开一次

        m_pInfraredMenu->show();

        //判断状态栏
        if (b_isMenuDebug)
        {
            m_pInfraredMenu->ui->menuDebug->setText(u8"关闭调试窗");
        }
        else {
            m_pInfraredMenu->ui->menuDebug->setText(u8"打开调试窗");
        }


        ////退出登录
        connect(m_pInfraredMenu, SIGNAL(to_LogOut_signal()), this, SLOT(on_LogOut_slots()));
        return;



    }
}

void CMainFrame::infraredMenu_quit()
{
    if (!m_pInfraredMenu)
    {
        return;
    }

    //if (m_pInfraredMenu->isVisible()) 
    {

        m_pInfraredMenu->close();
        if (m_pInfraredMenu)
        {
            delete m_pInfraredMenu;
            m_pInfraredMenu = nullptr;
        }

    }
    if (!m_pPortSetting) {
        ui->btnMeeting->setFocus();
    }
    else {
        m_pPortSetting->activateWindow();
        m_pPortSetting->ui->boxVga->setFocus();
    }
    return;
}


//
void CMainFrame::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        //
        if (!m_pInfraredMenu)
        {
            m_pInfraredMenu = new CInfraredDialogMenu(this, "index");
        }

        //
    //	if  (  m_pInfraredMenu->winId()  !=  pQyMc)

        //
        if (!m_pInfraredMenu->isVisible())
        {
            //窗口只打开一次

            m_pInfraredMenu->show();

            //判断状态栏
            if (b_isMenuDebug)
            {
                m_pInfraredMenu->ui->menuDebug->setText(u8"关闭调试窗");
            }
            else {
                m_pInfraredMenu->ui->menuDebug->setText(u8"打开调试窗");
            }

            if (m_Share)
            {
                m_pInfraredMenu->ui->menuShare->setText(u8"关闭共享");
            }
            else {
                m_pInfraredMenu->ui->menuShare->setText(u8"打开共享");
            }

            return;

        }
        else {
            m_pInfraredMenu->close();
            if (m_pInfraredMenu)
            {
                delete m_pInfraredMenu;
                m_pInfraredMenu = nullptr;
            }
        }
    }


}

void CMainFrame::ExitMenu() {
    
    if (m_pInfraredMenu)
    {
        m_pInfraredMenu->close();
        delete m_pInfraredMenu;
        m_pInfraredMenu = nullptr;
    }
}



void CMainFrame::Infrared_down() {
    if (m_pInfraredMenu) {
        m_pInfraredMenu->Infrared_down();
        return;
    }
    if (m_pPortSetting) {
        m_pPortSetting->Infrared_down();
        return;
    }
    if (m_pP2pDlg) {
        m_pP2pDlg->Infrared_down();
        return;
    }
    if (m_pOther) {
        m_pOther->Infrared_down();
        return;
    }

    this->focusNextPrevChild(true);
    return;
}

void CMainFrame::Infrared_up() {
    if (m_pInfraredMenu) {
        m_pInfraredMenu->Infrared_up();
        return;
    }
    if (m_pPortSetting) {
        m_pPortSetting->Infrared_up();
        return;
    }
    if (m_pP2pDlg) {
        m_pP2pDlg->Infrared_up();
        return;
    }
    if (m_pOther) {
        m_pOther->Infrared_up();
        return;
    }


    this->focusNextPrevChild(false);
    return;
}

void CMainFrame::Infrared_input_left_right(QString name, bool isLeft)
{
    if (m_pP2pMsg) {
        m_pP2pMsg->Infrared_input_left_right(name, isLeft);
        return;
    }
    if (isLeft) {
        this->focusNextPrevChild(false);
    }
    else {
        this->focusNextPrevChild(true);
    }
    return;
}



void CMainFrame::Infrared_ok(QString objname) {

    if (m_pInfraredMenu) {
        //按钮1
        if (objname == "menuBtn1") {
            m_pInfraredMenu->on_menuBtn1_clicked();
        }
        //按钮2
        if (objname == "menuBtn2") {
            m_pInfraredMenu->on_menuBtn2_clicked();
        }
        //按钮3
        if (objname == "menuBtn3") {
            m_pInfraredMenu->on_menuBtn3_clicked();
        }
        //按钮4
        if (objname == "menuBtn4") {
            m_pInfraredMenu->on_menuBtn4_clicked();
        }
        //
        if (objname == "btnVideo") {
            m_pInfraredMenu->on_btnVideo_clicked();
        }
        if (objname == "btnAudio") {
            m_pInfraredMenu->on_btnAudio_clicked();
        }
        //显示隐藏状态栏
        if (objname == "menuBtn5") {
            m_pInfraredMenu->on_menuBtn5_clicked();
        }
        //关机
        if (objname == "menuShutdown") {
            m_pInfraredMenu->on_menuShutdown_clicked();
        }
        //重启
        if (objname == "menuRestart") {
            m_pInfraredMenu->on_menuRestart_clicked();
        }
        //初始化设置
        if (objname == "menuSetting") {
            m_pInfraredMenu->on_menuSetting_clicked();
        }
        //端口设置
        if (objname == "PortSetting") {
            m_pInfraredMenu->on_PortSetting_clicked();
        }
        //退出登录
        if (objname == "btnLogOut") {
            m_pInfraredMenu->on_btnLogOut_clicked();
        }
        //显示调试窗
        if (objname == "menuDebug") {
            m_pInfraredMenu->on_menuDebug_clicked();
        }
        //点对点列表
        if (objname == "menuP2p") {
            m_pInfraredMenu->on_menuP2p_clicked();
        }
        //分辨率设置
        if (objname == "menuResolution") {
            m_pInfraredMenu->on_menuResolution_clicked();
        }
        //其他设置
        if (objname == "menuOther") {
            m_pInfraredMenu->on_menuOther_clicked();
        }

        return;
    }



    return;
}


//
int CMainFrame::exit(TCHAR* hint)
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
    //sm版没用
    //DBManager* pDm = (DBManager*)pProcInfo->m_var.pDBManager;
    //pDm->setAllUserActiveProcess(0);

    //
    if (!hint)  hint = (TCHAR*)_T("");

    //
    TCHAR  tBuf[128];
    _sntprintf(tBuf, mycountof(tBuf), _T("mainFrame.exit %s"), hint);
    showInfo_open0(0, 0, tBuf);

    //
    closeDlgAvAccept();

    //
    if (this->m_pUserLogin) {
        delete this->m_pUserLogin;
    }

    //
    HWND  m_hWnd = (HWND)this->winId();
    ::PostMessage(m_hWnd, WM_COMMAND, MAKEWPARAM(ID_qyQuitMainWnd, 0), 0);


    //
    return  0;
}


//注销登录
void CMainFrame::on_LogOut_slots() {
    CCtxQyMc* pQyMc = QY_GET_GBUF();
    if (!pQyMc) return;
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return;

    infraredMenu_quit();

    pProcInfo->m_var.usrInput.bNeedRestart_noUsrInput = true;

}

//显示初始化窗口
void CMainFrame::on_showDeviceBinding_slots()
{
    int i = 1;

    if (m_Share) {
        CloseRestartShareTimer();

        delete m_Share;
        m_Share = nullptr;

    }

    //
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

    

    //
    setNeedCfgOn_smTerminalInitCfg(true);

    //
    exit((TCHAR*)_T("mainFrame.on_showDeviceBinding"));

    return;

}

//显示点对点列表窗口
void CMainFrame::on_showP2pDlg_slots()
{
    CCtxQyMc* pQyMc = QY_GET_GBUF();
    if (!pQyMc) return;
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return;
    //只在登陆状态打开
    if (!pProcInfo->xt.bUsrLogined) {
        return;
    }

    //
    if (!m_pP2pDlg)
    {
        m_pP2pDlg = new CDlgP2p(this);

    }

    //
    if (!m_pP2pDlg->isVisible()) {

        //窗口只打开一次
        m_pP2pDlg->show();

    }
    else {
        m_pP2pDlg->close();
        if (m_pP2pDlg)
        {
            delete m_pP2pDlg;
            m_pP2pDlg = nullptr;
        }

        // on_closePortSetting_slots();
    }
    //
    infraredMenu_quit();

}

//关闭邀请
void CMainFrame::on_P2pMsg_close() {
    if (m_pP2pMsg) {
        m_pP2pMsg->close();
        if (m_pP2pMsg)
        {
            delete m_pP2pMsg;
            m_pP2pMsg = nullptr;
        }
    }
}

//关闭点对点
void CMainFrame::on_P2pDlg_close() {
    if (m_pP2pDlg)
    {
        m_pP2pDlg->close();
        if (m_pP2pDlg)
        {
            delete m_pP2pDlg;
            m_pP2pDlg = nullptr;
        }
    }
}



//显示端口设置窗口
void CMainFrame::on_showPortSetting_slots()
{
    //
    if (!m_pPortSetting)
    {
        m_pPortSetting = new CDlgPortSetting(this);

    }

    //
    if (!m_pPortSetting->isVisible()) {

        //窗口只打开一次
        m_pPortSetting->show();




    }
    else {


        on_closePortSetting_slots();
    }

    //
    infraredMenu_quit();
}

//关闭端口设置窗口
void CMainFrame::on_closePortSetting_slots()
{
    if (!m_pPortSetting)
    {
        return;
    }

    {
        m_pPortSetting->close();
        if (m_pPortSetting)
        {
            delete m_pPortSetting;
            m_pPortSetting = nullptr;
        }

    }

    return;
}



//显示其他设置窗口
void CMainFrame::on_showOther_slots()
{
    //
    if (!m_pOther)
    {
        m_pOther = new CDlgOther(this);

    }

    //
    if (!m_pOther->isVisible()) {

        //窗口只打开一次
        m_pOther->show();




    }
    else {


        on_closeOther_slots();
    }

    //
    infraredMenu_quit();
}

//关闭其它设置窗口
void CMainFrame::on_closeOther_slots()
{
    if (!m_pOther)
    {
        return;
    }

    {
        m_pOther->close();
        if (m_pOther)
        {
            delete m_pOther;
            m_pOther = nullptr;
        }

    }

    return;
}



//显示调试窗
void CMainFrame::on_showDebug_slots() {
    //
 //
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)QY_GET_procInfo_isCli();

    if (!IsWindow(pProcInfo->m_var.hWnd_dbg)) {
        viewDlgDbg((HWND)this->winId());
        b_isMenuDebug = true;
    }
    else {
        closeDlgDbg();
        b_isMenuDebug = false;
    }

    //
    infraredMenu_quit();
}

void CMainFrame::OpenRestartShareTimer() {

    if (m_timerRestartShare)
        return;

    m_startTime = QDateTime::currentDateTime();

    m_timerRestartShare = new QTimer(this);
    connect(m_timerRestartShare, &QTimer::timeout, this, &CMainFrame::on_restartShare_slots);

    //m_timerRestartShare->start(24 * 60 * 60 * 1000);
    m_timerRestartShare->start(2 * 60 * 1000);
    showInfo_open0(0, _T("restart_share"), _T("timer start"));
}

void CMainFrame::CloseRestartShareTimer() {
    showInfo_open0(0, _T("restart_share"), _T("timer stop"));

    if (m_timerRestartShare) {
        m_timerRestartShare->stop();
        delete m_timerRestartShare;
        m_timerRestartShare = nullptr;
    }
}

void CMainFrame::on_restartShare_slots()
{
    showInfo_open0(0, _T("restart_share"), _T("on_restartShare_slots"));

    QDateTime currentTime = QDateTime::currentDateTime();
    qint64 uptimeSeconds = m_startTime.secsTo(currentTime);
    qint64 uptimeHours = uptimeSeconds / 3600;

    CCtxQyMc* pQyMc = g_pQyMc;
    //CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    if (!pProcInfo)
        return;

    if (m_Share) {
        bool signalDetected = pProcInfo->m_bHikRecvOk;

        if (signalDetected) {
            m_failureCount = 0;
            pProcInfo->m_bHikRecvOk = false;
        }
        else {
            m_failureCount++;
        }
    }


    if (uptimeHours < 24 && m_failureCount < 3) {
        TCHAR  tBuf[128];
        _sntprintf(tBuf, mycountof(tBuf), _T("on_restartShare_slots:uptimeHours=%d, m_failureCount=%d"), uptimeHours, m_failureCount);
        showInfo_open0(0, _T("restart_share"), tBuf);

        return;
    }

    showInfo_open0(0, _T("restart_share"), _T("on_restartShare_slots exec"));


    m_startTime = QDateTime::currentDateTime();
    m_failureCount = 0;

    if (m_Share) {
        delete m_Share;
        m_Share = nullptr;
    }

   

    m_Share = new CDlgShareDynBmps_qt(pProcInfo->cfg.shareProcInitCfg.rtspUrl, this);
    RECT rect;
    m_Share->dlgShareDynBmps_Create(rect);
    m_Share->dlgShareDynBmps_OnInitDialog();

    m_Share->show();
    m_Share->raise();
}

void CMainFrame::on_openShare_slots() {
    //
     MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
     if (!pProcInfo)
         return;
 //
    if (m_Share == nullptr) {

        m_Share = new CDlgShareDynBmps_qt(pProcInfo->cfg.shareProcInitCfg.rtspUrl, this);
        RECT rect;
        m_Share->dlgShareDynBmps_Create(rect);
        m_Share->dlgShareDynBmps_OnInitDialog();

        m_Share->show();
        m_Share->raise();

        OpenRestartShareTimer();
    }
    else {
        CloseRestartShareTimer();

        delete m_Share;
        m_Share = nullptr;
    }


    infraredMenu_quit();
}


void CMainFrame::doP2pMsg(QString objname) {

    if (objname == "btn_repulse") {
        m_pP2pMsg->on_btn_repulse_clicked();
    }
    else if (objname == "btn_consent")
    {
        m_pP2pMsg->on_btn_consent_clicked();
    }
}


//遥控器指令下发   其他设置窗口接收
void CMainFrame::doOtherMsg(QString objname) {

    if (objname.contains("outAudioDeviceBtn")) {
        //m_pOther->onAudioOutputSelected();
        QPushButton* targetButton = findChild<QPushButton*>(objname);
        if (targetButton) {
            targetButton->click(); // 模拟点击
        }
    }
    //麦克风
    if (objname.contains("inAudioDeviceBtn")) {
        //m_pOther->onAudioOutputSelected();
        QPushButton* targetButton = findChild<QPushButton*>(objname);
        if (targetButton) {
            targetButton->click(); // 模拟点击
        }
    }

    if (objname == "restNvrBtn") {
        m_pOther->on_restNvrBtn_clicked();
    }
}

//端口开关遥控器控制
void CMainFrame::doBoxPort(QString objname) {
    if (m_pPortSetting) {

        if (objname == "boxVga")
        {
            m_pPortSetting->slot_boxVga_click(objname);
        }
        else if (objname == "boxHdmi")
        {
            m_pPortSetting->slot_boxHdmi_click(objname);
        }
        else if (objname == "boxDvi")
        {
            m_pPortSetting->slot_boxDvi_click(objname);
        }
        else if (objname == "boxUsb1")
        {
            m_pPortSetting->slot_boxUsb1_click(objname);
        }
        else if (objname == "boxUsb2")
        {
            m_pPortSetting->slot_boxUsb2_click(objname);
        }
        else if (objname == "boxAudioOut")
        {
            m_pPortSetting->slot_boxAudioOut_click(objname);
        }
        else if (objname == "boxUsb3")
        {
            m_pPortSetting->slot_boxUsb3_click(objname);
        }
        else if (objname == "boxLan")
        {
            m_pPortSetting->slot_boxLan_click(objname);
        }

    }
}

//遥控器按下点对点开关遥控器控制
void CMainFrame::doBtnClick(QString objname) {

    if (objname == "btnP2p_up") {
        m_pP2pDlg->on_btnP2p_up_clicked();
    }
    else if (objname == "btnP2p_2")
    {
        m_pP2pDlg->on_btnP2p_2_clicked();
    }
    else if (objname == "btnP2p_3")
    {
        m_pP2pDlg->on_btnP2p_3_clicked();
    }
    else if (objname == "btnP2p_4")
    {
        m_pP2pDlg->on_btnP2p_4_clicked();
    }
    else if (objname == "btnP2p_5")
    {
        m_pP2pDlg->on_btnP2p_5_clicked();
    }
    else if (objname == "btnP2p_6")
    {
        m_pP2pDlg->on_btnP2p_6_clicked();
    }
    else if (objname == "btnP2p_7")
    {
        m_pP2pDlg->on_btnP2p_7_clicked();
    }
    else if (objname == "btnP2p_8")
    {
        m_pP2pDlg->on_btnP2p_8_clicked();
    }
    else if (objname == "btnP2p_9")
    {
        m_pP2pDlg->on_btnP2p_9_clicked();
    }
    else if (objname == "btnP2p_down")
    {
        m_pP2pDlg->on_btnP2p_down_clicked();
    }
    else if (objname == "btnP2p_close")
    {
        on_showP2pDlg_slots();
    }

}

CMainFrame::~CMainFrame()
{
    delete ui;
    if (m_pWinTimer)
    {
        delete m_pWinTimer;
        m_pWinTimer = nullptr;
    }

    if (m_pWaitMeetingTimer)
    {
        delete m_pWaitMeetingTimer;
        m_pWaitMeetingTimer = nullptr;
    }

    if (m_pWinTitle)
    {
        delete m_pWinTitle;
        m_pWinTitle = nullptr;
    }
    if (systemSetup)
    {
        delete systemSetup;
        systemSetup = nullptr;
    }

    if (m_pUserLogin)
    {
        delete m_pUserLogin;
        m_pUserLogin = nullptr;
    }

    CloseRestartShareTimer();


    if (m_Share) {
        delete m_Share;
        m_Share = nullptr;
    }

    //
    if (this->m_pInfraredMenu)
    {
        delete  this->m_pInfraredMenu;
        this->m_pInfraredMenu = nullptr;
    }


    //
    if (this->m_pPortSetting)
    {
        delete  this->m_pPortSetting;
        this->m_pPortSetting = nullptr;
    }
    //
    if (this->m_pP2pDlg)
    {
        delete  this->m_pP2pDlg;
        this->m_pP2pDlg = nullptr;
    }

    //
    if (this->m_pOther)
    {
        delete  this->m_pOther;
        this->m_pOther = nullptr;
    }

    //
    if (this->m_pP2pMsg)
    {
        delete  this->m_pP2pMsg;
        this->m_pP2pMsg = nullptr;
    }

    //
    if (_sound) {
        delete _sound;
        _sound = nullptr;
    }

    if (m_moreMenu) {
        delete m_moreMenu;
        m_moreMenu = nullptr;
    }

    //
    stopChkingUsrKey();

    //
    HWND  m_hWnd = (HWND)this->winId();
    exitVar_onDestroy_mainFrame(0, m_hWnd, &var);
}
void CMainFrame::playReciveSound(int loop)
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

    //
    if (pProcInfo->status.avStatus.bExists_meeting)  return;

    //
    _sound->setLoopCount(loop);
    _sound->play();
}

void CMainFrame::flashTaskWindow()
{
    FLASHWINFO info;
    info.cbSize = sizeof(info);
    info.hwnd = HWND_MAIN_ID;
    info.dwFlags = FLASHW_TRAY;
    info.dwTimeout = 500;
    info.uCount = 5;
    FlashWindowEx(&info);
}

void CMainFrame::AutoStartShare() 
{
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    if (pProcInfo) {
        if (pProcInfo->cfg.shareProcInitCfg.m_bEnableShare && pProcInfo->cfg.shareProcInitCfg.m_bAutoShare) {
            if (m_Share == nullptr) {
                m_Share = new CDlgShareDynBmps_qt(pProcInfo->cfg.shareProcInitCfg.rtspUrl, this);
                RECT rect;
                m_Share->dlgShareDynBmps_Create(rect);
                m_Share->dlgShareDynBmps_OnInitDialog();

            
                m_Share->show();
                m_Share->raise();

                OpenRestartShareTimer();
            }
        }
    }
}

void CMainFrame::Init()
{
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

#if  0
    qint64 uid = pMisCnt->idInfo.ui64Id;
    DBManager::Instance().initDB(QString::number(uid));
#endif
    on_ButtonMax_clicked();
    sheetBackgroundImage();

    //就非要给隐藏  20240816
    ui->widget_12->setVisible(false);
    ui->lab_img2->setVisible(false);
    ui->label_status->setVisible(false);


    //
   // init_tray_icon(this->windowIcon());
    //
    qmcChkStatusLogFile();

    AutoStartShare();


    // WinTalkList* winTalkList = null;
    //winTalkList = (WinTalkList* )QWidget::find((WId));
 /*   QWidget* pWnd = ui->stackedWidgetContact->widget(0);
    if (pWnd == null)  goto  errLabel;
    if (pWnd->objectName() != "WinTalkList")goto  errLabel;
    WinTalkList* pTalkList = (WinTalkList*)pWnd;
    if (pTalkList == null)  goto  errLabel;

    pTalkList->load_initList();*/
    //
#ifdef  __DEBUG__
    traceLog((TCHAR*)_T("mainWnd.Init ok"));
#endif

errLabel:
    return;

}


//
int CMainFrame::switchToContact()
{
    this->on_toolBtnContact_clicked();
    return  0;
}


#pragma region 托盘



void CMainFrame::init_tray_icon(QIcon icon)
{
    mSysTrayIcon_ = new QSystemTrayIconEx(icon, this);
    connect(mSysTrayIcon_, &QSystemTrayIconEx::LButton_Click, [this]()
        {
#if defined (Q_OS_MAC)
            if (notify)
            {
                notify->show_wnd();
            }
#endif
            if (!this->isVisible())
            {
                this->setVisible(true);
            }
            if (this->windowState() == Qt::WindowState::WindowMinimized)
            {
                this->setWindowState(Qt::WindowState::WindowNoState);
            }
            this->show();
            this->activateWindow();
            this->raise();
        });
    connect(mSysTrayIcon_, &QSystemTrayIconEx::open_session, [this](qint64 sid, QString sname)
        {
            //TODO:点击某一项后打开对应聊天窗口
            if (!this->isVisible()) {
                this->show();
            }
            if (this->isMinimized()) {
                this->showNormal();
            }
            //切换菜单
            painterMenu("toolBtnMsg");

#if 0
            WinObjUser user;
            user.idinfo = QString::number(sid);


            cut_talk_list(user);
#endif
            //
            this->tray_open_session(sid);


        });
    QAction* act_menu = new QAction();
    act_menu->setText(u8"主窗口");
    act_menu->setObjectName(QString("act_menu_main"));
    //act_menu->setIcon(this->windowIcon());
    connect(act_menu, &QAction::triggered, this, &CMainFrame::on_tray_menu);
    mSysTrayIcon_->AddMenu(act_menu);


    act_menu = new QAction();
    act_menu->setText(u8"关于");
    act_menu->setObjectName(QString("act_menu_about"));
    //act_menu->setIcon(this->windowIcon());
    connect(act_menu, &QAction::triggered, this, &CMainFrame::on_tray_menu);
    mSysTrayIcon_->AddMenu(act_menu);

    act_menu = new QAction();
    act_menu->setObjectName(QString("act_menu_exit"));
    act_menu->setText(u8"退出");
    connect(act_menu, &QAction::triggered, this, &CMainFrame::on_tray_menu);
    mSysTrayIcon_->AddMenu(act_menu);
}


//
int CMainFrame::tray_open_session(qint64 userId)
{
    int  iErr = -1;
    WinObjUser wou;


    if (userId == 0)return  -1;

    /*   QWidget* pWnd = ui->stackedWidgetContact->widget(0);
       if (pWnd == null)  goto  errLabel;
       if (pWnd->objectName() != "WinTalkList")goto  errLabel;
       WinTalkList* pTalkList = (WinTalkList*)pWnd;
       if (pTalkList == null)  goto  errLabel;

       wou.idinfo = QString::number(userId);

       pTalkList->selListWidget(wou);*/



    iErr = 0;
errLabel:
    return  iErr;
}



void CMainFrame::on_tray_menu()
{
    QAction* act_menu = (QAction*)sender();
    if (act_menu)
    {
        if (act_menu->objectName().compare("act_menu_main") == 0)
        {
            if (!this->isVisible())
            {
                this->setVisible(true);
            }
            if (this->windowState() == Qt::WindowState::WindowMinimized)
            {
                this->setWindowState(Qt::WindowState::WindowNoState);
            }
            this->show();
            this->activateWindow();
            this->raise();
        }

        else if (act_menu->objectName().compare("act_menu_about") == 0) {
            WinSystemAbout aboutDialog;
            aboutDialog.show();
            aboutDialog.exec();
        }

        else if (act_menu->objectName().compare("act_menu_exit") == 0)
        {
            CCtxQyMc* pQyMc = g_pQyMc;
            CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
            DBManager* pDm = (DBManager*)pProcInfo->m_var.pDBManager;
            pDm->setAllUserActiveProcess(0);

            closeDlgAvAccept();


            //
            HWND  m_hWnd = (HWND)this->winId();
            ::PostMessage(m_hWnd, WM_COMMAND, MAKEWPARAM(ID_qyQuitMainWnd, 0), 0);
        }
    }
}


#pragma endregion

//初始化控件
void CMainFrame::initControl()
{
    CCtxQyMc* pQyMc = g_pQyMc;

    //m_border = 4;	
   // this->setMouseTracking(true);	//打开鼠标追踪	
    //setMouseTracking(true);
   // this->setWindowFlags(Qt::FramelessWindowHint);   //设置窗口无边框

   // setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->setWindowIcon(QIcon(":/Resources/Images/Login/qmClient.png"));
    //ui->headIcoBtn->setIcon(QIcon(":/Resources/Images/WinMain/headMax.png"));

    //
   // ui->labTitle->setText(QString::fromUtf16((char16_t*)pQyMc->cfg.qyMcTitle));
    //
   // ui->headIcoBtn->setIconSize(QSize(55, 55));
    QAction* pActLeft = new QAction(this);
    // pActLeft->setIcon(QIcon(":/Resources/Images/WinMain/search_icon.png"));
    // ui->searchLineEdit->addAction(pActLeft, QLineEdit::LeadingPosition);

    // ui->moreMenu->setIcon(QIcon(":/Resources/Images/WinMain/aio_more.png"));

    m_moreMenu = new QMenu();
    QAction* more_newGroup_action = new QAction(m_moreMenu);
    more_newGroup_action->setText(u8"新建群组");

    QAction* more_myDisk_action = new QAction(m_moreMenu);
    more_myDisk_action->setText(u8"我的网盘");


    QAction* more_writeOff_action = new QAction(m_moreMenu);
    more_writeOff_action->setText(u8"退出");
    m_moreMenu->addAction(more_newGroup_action);
    m_moreMenu->addSeparator();
    m_moreMenu->addAction(more_myDisk_action);
    m_moreMenu->addSeparator();
    m_moreMenu->addAction(more_writeOff_action);


    /*ui->moreMenu->setMenu(moreMenu);
    ui->moreMenu->setStyleSheet("QPushButton::menu-indicator{image:None;border:none}");*/

    connect(m_moreMenu, SIGNAL(triggered(QAction*)), this, SLOT(trigerMenu(QAction*)));



    //painterMenu("toolBtnMsg");
    /*QFile file(":/Resources/QSS/CMainFrame.css");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        this->setStyleSheet("");
        QString qsstyleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(qsstyleSheet);
    }
    file.close();*/

    // m_pWinTitle = new WinTitle(ui->titleWidget);
   //  m_pWinTitle->setButtonType(MIN_MAX_BUTTON);
     //m_pWinTitle->setWindowFlag(Qt::WindowStaysOnBottomHint);
     //m_pWinTitle->move(0, 0);
    // m_pWinTitle->setParent(true);
    // connect(m_pWinTitle, SIGNAL(signalButtonMinClicked()), this, SLOT(on_ButtonMin_clicked()));
    // connect(m_pWinTitle, SIGNAL(signalButtonCloseClicked()), this, SLOT(on_ButtonClose_clicked()));
    // connect(m_pWinTitle, SIGNAL(signalButtonRestoreClicked()), this, SLOT(on_ButtonRestore_clicked()));
    // connect(m_pWinTitle, SIGNAL(signalButtonMaxClicked()), this, SLOT(on_ButtonMax_clicked()));

     //searchListView_ = new QListView(ui->widget_2);
     //connect(searchListView_, &QListView::clicked, this, &CMainFrame::slot_list_activated);
     //verticalScrollBar = searchListView_->verticalScrollBar();
     //connect(verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(onScrollBarValueChanged(int)));
     //searchListMoudle_ = new SearchListModel(this);
     //SearchListDelegate* itemdelegate = new SearchListDelegate(searchListMoudle_, this);
     ////ui.listView->setResizeMode(QListView::Adjust);
     //searchListView_->setModel(searchListMoudle_);
     //searchListView_->setItemDelegate(itemdelegate);
     //searchListView_->setVisible(false);

    // searchListView_->verticalScrollBar()->setStyleSheet("QScrollBar{width:10px;}");

    /* QWidget* pCur = ui->stackedWidgetInfo->currentWidget();
     if (pCur != NULL) {
         QString name = pCur->objectName();
         if (pCur->objectName() == "CDlgTalk_qt") {
             CDlgTalk_qt* pDlg = (CDlgTalk_qt*)pCur;
             connect(pDlg, SIGNAL(to_closeTalkInfo(QString)), this, SLOT(slot_closeTalk(QString)));
         }
     }*/




     //必须在界面初始化之前置为nullptr
    h_cdlgTalkqt = nullptr;




#if 0
    WinAdvancedSet* pWinAdvancedSet = new WinAdvancedSet;
    ui->stackedWidgetInfo->addWidget(pWinAdvancedSet);
    ui->stackedWidgetInfo->setCurrentIndex(INFO_MSG);
    m_nContactsIndex = 0;
#endif
    /*QDesktopWidget* pDesk = QApplication::desktop();
    QRect screenRect = QApplication::desktop()->screenGeometry(this);
    this->setGeometry((screenRect.width() - this->width()) / 2, (screenRect.height() - this->height()) / 2, this->width() - 10, this->height());*/
    //显示共享流窗口
    showShareStreamWidget();
    screenNum = QGuiApplication::screens().count();
}

//扩展屏显示
void CMainFrame::showShareStreamWidget()
{
    //
#ifdef  __DEBUG__
    if (1) {
        //
        //  traceLog(  )for test: 
        //
        return;
    }
#endif 


    //
    if (!shareStreamWidget)
    {
        QList<QScreen*> screen_list = QGuiApplication::screens();
        for (int i = 0; i < screen_list.count(); i++)
        {
            if (QGuiApplication::primaryScreen() != screen_list.at(i))
            {
                shareStreamWidget = new ShareStreamWidget(this);
                shareStreamWidget->setGeometry(screen_list.at(i)->geometry());
                shareStreamWidget->show();

                refResolution();
                break;
            }

        }
    }
}

//扩展屏关闭
void CMainFrame::closeShareStreamWidget()
{
    if (shareStreamWidget) {
        shareStreamWidget->close();
        shareStreamWidget = nullptr;

        refResolution();
    }
}

//
DWORD  tmpThreadProc_ca_usr(LPVOID pParam);


//
int CMainFrame::chkUsrKey()
{
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)QY_GET_procInfo_isCli();
    Var_ca_usr_qmc* pVc = &pProcInfo->m_var.ctxSm.ca_usr;

    if (!pProcInfo->m_var.ctxSm.usrLogin_sm.bUsrLogined)  return -1;
    if (!pProcInfo->m_var.ctxSm.usrLogin_sm.loginState.bExists_usrKey) {
        return  -1;
    }

    //
    waitForObject(&m_chkUsrKey.m_hThread_ca, 0);

    do {
        //
        if (!m_chkUsrKey.m_hThread_ca) {
            if (pVc->bExists_usrKey) {
                m_chkUsrKey.nTimes_noUsrKey = 0;
            }
            else {
                m_chkUsrKey.nTimes_noUsrKey++;
            }
        }

        //
        if (!m_chkUsrKey.m_hThread_ca) {
            DWORD  dwThreadDaemonId;

            pVc->bTryToChkUsrKey = true;


            m_chkUsrKey.m_hThread_ca = CreateThread(NULL, 0, tmpThreadProc_ca_usr, 0, CREATE_SUSPENDED, &dwThreadDaemonId);
            if (!m_chkUsrKey.m_hThread_ca)  break;
            //gBuf_rtspCliHelp.dwThreadId_spl = dwThreadDaemonId;
            if (ResumeThread(m_chkUsrKey.m_hThread_ca) == -1)  break;
        }

        //
    } while (false);




    //
    return  0;
}

//
int CMainFrame::stopChkingUsrKey()
{
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)QY_GET_procInfo_isCli();
    Var_ca_usr_qmc* pVc = &pProcInfo->m_var.ctxSm.ca_usr;
    //
    if (m_chkUsrKey.m_hThread_ca) {
        pVc->toolCa.bNeedQuit = true;
        //
        waitForObject(&m_chkUsrKey.m_hThread_ca, INFINITE);
    }

    //
    return  0;
}




void CMainFrame::AddNewMsgCount(int count)
{
    msgCount += count;
    updateMsgCount();
}

void CMainFrame::UpMsgCount(int count)
{
    msgCount = msgCount - count;
    updateMsgCount();
}

void CMainFrame::Clear()
{
    msgCount = 0;
    updateMsgCount();
}

void CMainFrame::updateMsgCount()
{
    /* ui->redCount->setText(msgCount > 99 ? "99" : QString::number(msgCount));
     ui->redCount->setVisible(msgCount != 0);*/
}



void CMainFrame::trigerMenu(QAction* act)
{
    if (act->text() == u8"新建群组")
    {
        on_newGroupBtn_clicked();
    }
    if (act->text() == u8"我的网盘") {

        HWND  hParent = mynull;// (HWND)this->winId();
        HWND  hCurTalk = (HWND)this->winId();

        MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();

        PARAM_viewOfflineRes  param = { 0 };
        param.bNoBorder = TRUE;

        viewDlgOfflineRes_me(hParent, &pProcInfo->offlineRes, NULL);


    }
    if (act->text() == u8"退出")
    {
        CCtxQyMc* pQyMc = g_pQyMc;
        CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
        DBManager* pDm = (DBManager*)pProcInfo->m_var.pDBManager;
        pDm->setAllUserActiveProcess(0);
        closeDlgAvAccept();


        //
        HWND  m_hWnd = (HWND)this->winId();
        ::PostMessage(m_hWnd, WM_COMMAND, MAKEWPARAM(ID_qyQuitMainWnd, 0), 0);
    }
}

#if 0
int  tmpHandler_printContactList_newGroup(void* p0, void* p1, void* p2)
{
    int  iRet = -1;
    COMMON_PARAM* pCommonParam = (COMMON_PARAM*)p0;
    COMMON_PARAM* pCommonParam1 = (COMMON_PARAM*)p1;
    //
    CMyDb* pDb = (CMyDb*)pCommonParam->p0;
    //  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
    //HWND				hListCtrl = (HWND)pCommonParam->p1;
    //if (!hListCtrl)  goto  errLabel;
    int				iItem = (int)pCommonParam->p2;
    //
    //BOOL				bUnprocedOnly = (BOOL)p1;
    QList<FriendInfo>* pList = (QList<FriendInfo>*)pCommonParam1->p0;
    //
    QMEM_qyImObj* pQMem = (QMEM_qyImObj*)p2;
    int				index = 0;
    QY_MC* pQyMc = QY_GET_GBUF();

    QY_MESSENGER_REGINFO		regInfo;
    MY_REG_DESC					desc;
    TCHAR						tBuf[256];
    QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable);


    memset(&regInfo, 0, sizeof(regInfo));

    QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
    if (!pDbFuncs)  goto  errLabel;
    QM_dbFuncs& g_dbFuncs = *pDbFuncs;


    if (pQMem->messengerInfo.iStatus == CONST_qyStatus_ok
        && pQMem->messengerInfo.uiType != CONST_objType_imGrp)
    {

        _sntprintf(tBuf, mycountof(tBuf), _T("%I64u"), pQMem->messengerInfo.idInfo.ui64Id);

        if (!g_dbFuncs.pf_bGetMessengerRegInfoBySth(pDb, CONST_dbType_myDb, getResTable(0, &pQyMc->cusRes, CONST_resId_fieldIdTable), CONST_tabName_qyImObjRegInfoTab, pQMem->messengerInfo.misServName, &pQMem->messengerInfo.idInfo, 0, &regInfo)) {
            memset(&regInfo, 0, sizeof(regInfo));
        }
        int		tmpiRet;
        TCHAR	talkerDesc[128] = _T("");
        regInfo2Desc(0, &regInfo, &desc, talkerDesc, mycountof(talkerDesc), NULL, 0);

        traceLog((TCHAR*)_T("contact %I64u, %s %s %s "), pQMem->messengerInfo.idInfo.ui64Id, desc.pDw, desc.pBm, desc.pSyr);



        FriendInfo fi;
        fi.dw = QString::fromUtf16((char16_t*)desc.pDw);
        fi.name = QString::fromUtf16((char16_t*)desc.pDw) + "  " + QString::fromUtf16((char16_t*)desc.pBm) + "  " + QString::fromUtf16((char16_t*)desc.pSyr) + "(" + QString::number(pQMem->messengerInfo.idInfo.ui64Id) + ")";
        fi.userId = QString::number(pQMem->messengerInfo.idInfo.ui64Id);

        //
        pList->append(fi);
    }

    iRet = 0;



errLabel:
    return  iRet;
}
#endif

//
__declspec(dllexport)  int  createTmpGrp_qt(HWND  hParent, IM_GRP_EX* p);

void CMainFrame::tray_infrom(SessionInfo si) {
    if (mSysTrayIcon_)
    {
        mSysTrayIcon_->tray_time_star(this, true);


        /*mSysTrayIcon_->add_new_session(si);

        si.session_id = 23;
        lstrcpyn(si.header_url, _T(":/Resources/Images/WinMain/tmp_group.png"), mycountof(si.header_url));
        lstrcpyn(si.session_name, _T("里斯"), mycountof(si.session_name));
        si.unread_count = 1;*/

        mSysTrayIcon_->add_new_session(si);
    }
}

void CMainFrame::on_newGroupBtn_clicked()
{
    QY_MC* pQyMc = QY_GET_GBUF();
    HWND  m_hWnd = (HWND)this->winId();
    IM_GRP_EX  req;
    int newGrpRes = createTmpGrp_qt(m_hWnd, &req);
    if (newGrpRes == 0) {
        WinObjUser user;
        user.idinfo = QString::number(req.common.idInfo.ui64Id);

        /*WinTalkList* pTalkList = (WinTalkList*)ui->stackedWidgetContact->widget(0);
        pTalkList->addListWidget(user);*/

        on_Contact_Msg(user);

        //联系人列表
       /* WinContactsList* pContactsList = (WinContactsList*)ui->stackedWidgetContact->widget(1);
        pContactsList->addTmpContactItem(req.common.idInfo.ui64Id);*/
    }
#if  0
    int  iObjType;
    char  buf[128];
    int  iObjId;
    int  getObjId_myDb(LP_hashTbl  pHashTbl_tree, int  iObjType, char* pKeyStr);
    CDlgLeftView_db* pLeftView = this;
    TCHAR  displayName[128];
    int  nImage, nSelectedImage;
    HTREEITEM  tmphtItem;

    //					
    iObjType = CONST_objType_imGrps_tmp;
    myTChar2Utf8(getResStr(0, &pQyMc->cusRes, CONST_resId_objIdStr_imGrps_tmp), buf, mycountof(buf));
    iObjId = getObjId_myDb(pLeftView->m_var.pHashTbl_tree, iObjType, buf);
    if (iObjId < 0)  goto  errLabel;;

    _sntprintf(displayName, mycountof(displayName), _T("%s"), CString(getResStr(0, &pQyMc->cusRes, CONST_resId_objIdStr_imGrps_tmp)));
    nImage = pQyMc->cfg.image.nImage_imGrps;  nSelectedImage = pQyMc->cfg.image.nImage_selectedImGrps;

    if (!(tmphtItem = pLeftView->FindItemData(iObjId, TRUE, pLeftView->m_var.htMyRootItem))) {
    }
    else {
        this->bRefreshItem(tmphtItem);
    }'
        '
#endif


#if  0

        CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (!pMisCnt)  return;



    //
    if (pQyMc->cfg.db.iDbType != CONST_dbType_myDb) {
#ifdef  __DEBUG__
        traceLog((TCHAR*)_T("only supported with myDb"));
#endif
        return;
    }
    QY_OBJ_DB* pObjDb = getProcedObjDb(pQyMc, 0, pQyMc->iDsnIndex_mainSys);
    if (!bObjDbAvail(pObjDb))  return;


    QList<QString> members;
    AddGroupMemberDialog addMemberDlg(members);
    QList<FriendInfo> friends;
    FriendInfo fs;
    QList<FriendInfo>* pList = &friends;


    //
    CMyDb* pDb = (CMyDb*)pObjDb->pDb;
    int cnt = 0;
    COMMON_PARAM	commonParam;
    COMMON_PARAM  commonParam1;
    //  MACRO_makeCommonParam3(  pDb,  pListCtrl,  (  void  *  )cnt,  commonParam  );
    MACRO_makeCommonParam3(pDb, 0, (void*)cnt, commonParam);
    MACRO_makeCommonParam3(pList, 0, 0, commonParam1);

    qTraverse(pDb->m_var.pQ_qyImObjTab, tmpHandler_printContactList_newGroup, &commonParam, &commonParam1);

    // //设置好友列表
    addMemberDlg.setAllFriends(friends);



    //
    if (addMemberDlg.exec() == 1)
    {
        //TODO:执行建群
        //成员id  英文逗号 分隔 
        QString ids = addMemberDlg.friendIds;
        //群名称
        QString groupName = addMemberDlg.groupName;
    }

#endif

}

bool CMainFrame::isCurInStackWidget(const char* widgetType, QStackedWidget* stackWidget)
{
    bool ret = false;
    QWidget* widget = stackWidget->currentWidget();
    if (widget && widget->inherits(widgetType))
    {
        ret = true;
    }
    else //当前widget不是需要的类型时，在stackWidget找到并设置为当前widget
    {
        for (int i = 0; i < stackWidget->count(); i++)
        {
            widget = stackWidget->widget(i);
            if (widget && widget->inherits(widgetType))
            {
                stackWidget->setCurrentWidget(widget);
                ret = true;
                break;
            }
        }
    }
    return ret;
}



//
int CMainFrame::dbg_testFunc()
{
#ifdef  __DEBUG__
    //
    //int  count = ui.copWnd->uself.treeWidget.topLevelItemCount()
   // QWidget* pCur = ui->stackedWidgetContact->currentWidget();

    //if (pCur != NULL) {
    //    QString name = pCur->objectName();
    //    traceLog((TCHAR*)_T("%s"), name.utf16());
    //    if (pCur->objectName() == "WinContactsList") {
    //        WinContactsList* pList = (WinContactsList*)pCur;
    //        //
    //        //pList->dbg_testFunc();
    //    }
    //    else if (pCur->objectName() == "WinTalkList") {
    //        //
    //        WinTalkList* pTalkList = (WinTalkList*)pCur;
    //        //pTalkList->dbg_testFunc();
    //    }
    //}



#endif

    //
    return  0;
}

int CMainFrame::onLineStatus()
{

    //
    //int  count = ui.copWnd->uself.treeWidget.topLevelItemCount()
    //QWidget* pCur = ui->stackedWidgetContact->currentWidget();

    //if (pCur != NULL) {
    //    QString name = pCur->objectName();
    //    traceLog((TCHAR*)_T("%s"), name.utf16());
    //    if (pCur->objectName() == "WinContactsList") {
    //        WinContactsList* pList = (WinContactsList*)pCur;
    //        //
    //        pList->onLineStatusUp();
    //    }
    //    else if (pCur->objectName() == "WinTalkList") {
    //        //
    //        WinTalkList* pTalkList = (WinTalkList*)pCur;
    //        pTalkList->onLineStatusUp();
    //    }
    //}
    //
    return  0;
}


#ifdef __DEBUG__

int  tmpHandler_printTalks(void* p0, void* p1, MIS_MSGU* pMsgElem)
{
	COMMON_PARAM* pCommonParam = (COMMON_PARAM*)p0;
	// p1;

	int& iPos = *(int*)pCommonParam->p0;
	SYSTEMTIME& when = *(SYSTEMTIME*)pCommonParam->p1;


	TCHAR		tBuf[512] = _T("");
	int			i = 0;
	char		timeBuf[CONST_qyTimeLen + 1] = "";
	char		displayBuf[255 + 1] = "";
	int			j;
	QY_MC* pQyMc = QY_GET_GBUF();


	if (pMsgElem->uiType == CONST_misMsgType_talkingFriend_qmc) {
		HWND			hDlgTalk = pMsgElem->talkingFriend_qmc.hWnd;
		//  CDlgTalk	*	pDlg	=	(  CDlgTalk  *  )CWnd::FromHandle(  pMsg->talkingFriend_qmc.hWnd  );
		CHelp_getDlgTalkVar	help_getDlgTalkVar;
		DLG_talk_var* pDlgTalkVar = (DLG_talk_var*)help_getDlgTalkVar.getVar(hDlgTalk);
		if (!pDlgTalkVar)  goto  errLabel;
		DLG_talk_var& m_var = *pDlgTalkVar;

		//
		_sntprintf(tBuf, mycountof(tBuf), _T("talk %I64u, tn %d"), m_var.addr.idInfo.ui64Id, m_var.addr.uiTranNo_shadow);
        traceLog(tBuf);

	}

errLabel:
	return  0;
}

#endif


//关闭窗口
void CMainFrame::on_timer_winMethod()
{
    // TODO: Add your message handler code here and/or call default
    CCtxQyMc* pQyMc = QY_GET_GBUF();
    if (!pQyMc) return;
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return;
    FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
    if (!pFuncs) return;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (!pMisCnt)return;


    Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
    if (!pCtxSm)  return;
    Ctx_sm& ctxSm = *pCtxSm;


    TCHAR  tBuf[128];

    //  2026/03/04
    WId  tmp_wid = this->winId();
    if (tmp_wid != (WId)pQyMc->gui.hMainWnd) {
        showInfo_open(0, 0, 0, _T("mainWnd.on_timer_winMethod: winId changed"));
        //
        pQyMc->gui.hMainWnd = (HWND)tmp_wid;
    }

    //
    HWND  m_hWnd = pQyMc->gui.hMainWnd;

    //
    if (pFuncs->mainWnd.pf_mainWnd_OnTimer(m_hWnd, &var, 0))  return;

    //
  /*  if (!(var.common.loopCtrl % 3)) {
        QString tag = m_myName + (bMeOnline(pQyMc) ? "" : u8" (离线)");
        if (tag != ui->userName->text()) {
            ui->userName->setText(tag);
        }
    }*/

    //
#ifdef  __DEBUG__
    if (0) {
        traceLog((TCHAR*)_T("mainWnd.loopCtrl %d"), var.common.loopCtrl);
    }

	COMMON_PARAM commonParam;
    int iPos = 0;
    int when = 0;
	MACRO_makeCommonParam3(&iPos, &when, 0, commonParam);
	qTraverse(&pMisCnt->talkingFriendQ, (PF_commonHandler)tmpHandler_printTalks, &commonParam, 0);

    //
    if (0) {
        QRect rc = this->geometry();
        _sntprintf(tBuf, mycountof(tBuf), _T("on_timer_winMethod width=%d,hight=%d"), rc.width(), rc.height());
        traceLog(tBuf);
    }

#endif

    if (!(var.common.loopCtrl % 10)) {
        auto screens = QGuiApplication::screens();
        if (screens.count() > 1)
        {
            qDebug() << u8"有扩展屏加入";
            showShareStreamWidget();
        }
        else
        {
            qDebug() << u8"无扩展屏移除";
            closeShareStreamWidget();
        }
    }

    //
    if (!(var.common.loopCtrl % 4)) {
        chkUsrKey();

        //
        if (pProcInfo->m_var.ctxSm.usrLogin_sm.bUsrLogined
            && pProcInfo->m_var.ctxSm.usrLogin_sm.loginState.bExists_usrKey)
        {

            if (m_chkUsrKey.nTimes_noUsrKey == 0) {

                pProcInfo->xt.bUsrUkeyed = true;
                //tmp_keyStatus = u8"检测到UKEY已拔出";
            }
            else {
                pProcInfo->xt.bUsrUkeyed = false;


                //拔key离会
                pProcInfo->m_var.bNetworkFailded = true;

                QString tmp_keyStatus = u8"检测到UKEY已拔出";

                QString log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + tmp_keyStatus;

                showHint(tmp_keyStatus, "red", 300);
               // qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);
            }

            //
#ifdef  __DEBUG__
            _sntprintf(tBuf, mycountof(tBuf), _T("nTimes_noUsrKey %d"), m_chkUsrKey.nTimes_noUsrKey);
            traceLog(tBuf);
#endif
            //
            if (m_chkUsrKey.nTimes_noUsrKey > 5) {
                exit((TCHAR*)_T("nTimes_noUsrKey too big"));

                //
                QString log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + u8"：检测到UKEY拔出，退出登录；登录方式：UKEY登录";

                qmcLogForHg(0, (wchar_t*)log_txt.utf16(), true);

                return;
            }
        }
        else {
            pProcInfo->xt.bUsrUkeyed = false;

        }
    }



    //
    if (!(var.common.loopCtrl % 20)) {
        onLineStatus();
    }

    //
    if (!(var.common.loopCtrl % CONST_intervalInS_xt)) 
    {
        if (pProcInfo->m_var.ctxSm.ca_dev.flgs.sxrz.bDone_sqm) {
            send_xt(var.common.loopCtrl);
        }
    }

    send_fy(var.common.loopCtrl);
    //
    chkXtResp();
    if (pProcInfo->xt.bNeedRestart_noXtResp
        || pProcInfo->xt.bNeedRestart_mjChanged)
    {
        TCHAR* hint = (TCHAR*)_T("");
        if (pProcInfo->xt.bNeedRestart_noXtResp) {
            showInfo_open0(0, 0, _T("bNeedRestart_noXtResp is true, so restart app"));
            hint = (TCHAR*)_T("bneedRestart_noXtResp true");
        }
        else {
            showInfo_open0(0, 0, _T("bNeedRestart_mjChanged is true, so restart app"));
            hint = (TCHAR*)_T("bneedRestart_mjChanged true");

            QString tmp_keyStatus = u8"离线";
            QString log_txt = QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_termialName)) + tmp_keyStatus;
            qmcLogForHg(0, (wchar_t*)log_txt.utf16(), true);

        }

        //


        //
        exit((TCHAR*)hint);
        return;
    }

    //
    int  maxTimes_noCamera = 10;
#ifdef  __DEBUG__
    if (1) {
        maxTimes_noCamera = 2;
    }
#endif 
    if (pProcInfo->av.localAv.chkCamera.mTimes_noCamera > maxTimes_noCamera) {

        qmcLogStatus(_T("mainWnd.on_timer"), 0, _T("摄像头多次没有正常工作, 准备重启"));
        //
        pProcInfo->av.localAv.chkCamera.bNeedRestart_noCamera = true;
        //
        exit((TCHAR*)_T("摄像头异常"));
        return;
    }


    //
    int  maxTimeoutInMs_noUsrInput = 10 * 60 * 1000;
    //
    maxTimeoutInMs_noUsrInput = ctxSm.hg.systemConfig.intervalInS_over * 1000;

    if (maxTimeoutInMs_noUsrInput <= 0 || maxTimeoutInMs_noUsrInput >= 10 * 60 * 1000) { maxTimeoutInMs_noUsrInput = 10 * 60 * 1000; }


    //
    DWORD  curTickCnt = myGetTickCount(mynull);
    if (!isQEmpty(&pMisCnt->talkingFriendQ)) {
        pProcInfo->m_var.usrInput.dwLastTickCnt_talkerExists = curTickCnt;
    }
    if (pProcInfo->m_var.usrInput.dwLastTickCnt_usrLoginFinished) {
        int iElapseInMs_infrared = curTickCnt - pProcInfo->m_var.usrInput.dwLastTickCnt_infrareadRecvd;
        int iElapseInMs_usrLogin = curTickCnt - pProcInfo->m_var.usrInput.dwLastTickCnt_usrLoginFinished;
        int iElapseInMs_talkerExists = curTickCnt - pProcInfo->m_var.usrInput.dwLastTickCnt_talkerExists;
        if (iElapseInMs_infrared < maxTimeoutInMs_noUsrInput
            || iElapseInMs_usrLogin < maxTimeoutInMs_noUsrInput
            || iElapseInMs_talkerExists < maxTimeoutInMs_noUsrInput)
        {
            pProcInfo->m_var.usrInput.nTimes_waitForUsrInput = 0;
            //
#ifdef  __DEBUG__
            if (0) {
                _sntprintf(tBuf, mycountof(tBuf), _T("mainframe: usrInput exists, nTimes_waitForUsrInput set to 0. e_infrared %dms, e_login %dms, e_talker %dms"),
                    iElapseInMs_infrared, iElapseInMs_usrLogin, iElapseInMs_talkerExists);
                traceLog(tBuf);
            }
#endif  
        }
        else {
            pProcInfo->m_var.usrInput.nTimes_waitForUsrInput++;

            showHint(u8"长时间无会议动作，即将退出登录！！", "red", 3000);

            //
#ifdef  __DEBUG__
            if (0) {
                _sntprintf(tBuf, mycountof(tBuf), (TCHAR*)_T("mainframe: usrInput not exists, nTimes_waitForUsrInput set to %d"), pProcInfo->m_var.usrInput.nTimes_waitForUsrInput);
                traceLog(tBuf);
            }
#endif

        }
        if (pProcInfo->m_var.usrInput.nTimes_waitForUsrInput > 3) {
            pProcInfo->m_var.usrInput.bNeedRestart_noUsrInput = true;


            QString log_txt = u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"登录超时自动退出登录";

            qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);
        }
        if (pProcInfo->m_var.usrInput.bNeedRestart_noUsrInput) {
            showInfo_open0(0, 0, _T("bNeedRestart_noUsrInput is true, so restart app"));
            exit((TCHAR*)_T("bNeedRestart_noUsrInput true"));
            return;
        }
    }


    //
    if (pProcInfo->m_var.ctxSm.bNeedRestart) {
        pProcInfo->m_var.ctxSm.nTimes_beforeRestart++;

        //
        showHint(u8"会管强制下线！！", "red", 3000);
        //
        //
        if (pProcInfo->m_var.ctxSm.nTimes_beforeRestart > 5) {
            showInfo_open0(0, 0, _T("ctxSm.bNeedRestart is true, so restart app"));

            //

            QString log_txt = u8"终端用户：" + QString::fromUtf16(((ushort*)pProcInfo->av.confLayout.login_userName)) + u8"会管强制退出登录";

            qmcLogForHg(0, (wchar_t*)log_txt.utf16(), false);

            exit((TCHAR*)_T("ctxSm.bNeedRestart true"));
        }
        return;
    }


    //
    netflow_main();

    //
    {
        MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
        if (pMisCnt) {
            if (isQEmpty(&pMisCnt->talkingFriendQ)) {
                pProcInfo->xt.bAudioDevOk = true;
                pProcInfo->xt.bVideoDevOk = true;
            }
        }
    }
    //
#ifdef  __DEBUG__
    if (pProcInfo->m_var.usrInput.dwLastTickCnt_usrLoginFinished) {
        OldConfs  oldConfs = { 0 };
        if (!findOldRecvdConfsActive(&oldConfs)) {
            //
            int  i;
            for (i = 0; i < oldConfs.usCnt; i++) {
                OldConfMem* pMem = &oldConfs.mems[i];
                _sntprintf(tBuf, mycountof(tBuf), _T("oldConfs[%d]: %I64u, e_lastRefreshed %dms"), i, pMem->idInfo_peer.ui64Id, pMem->uiElapseInms_lastRefreshed);
                traceLog(tBuf);
            }
        }

    }

    //
    if (0) {
        

    }

#endif


    //
#ifdef  __DEBUG__
        //testSndRtspMsg();
        //
    dbg_testFunc();
    //    
    {
        //
        if (pProcInfo->m_var.b_app_testSize_forDebug) {
            HWND  hWnd = (HWND)this->winId();
            //::MoveWindow(hWnd, 0, 0, 500, 300, true);
            ::MoveWindow(hWnd, 0, 0, 800, 800, true);

        }
    }

#endif



    //  
}


//消息
void CMainFrame::on_toolBtnMsg_clicked()
{
    painterMenu("toolBtnMsg");
    // ui->centerWidget->show();
   //  ui->stackedWidgetContact->setCurrentIndex(CONT_TALKLIST);

     //QWidget* pWidget = ui->stackedWidgetInfo->widget(0);
     //if (pWidget->objectName() == "temp")
     //{
     //	return;
     //}
    ui->stackedWidgetInfo->setCurrentIndex(INFO_MSG);
    //  ui->searchLineEdit->clear();
    onLineStatus();
}

bool CMainFrame::isMsgSel() {
    /* if (ui->stackedWidgetContact->currentIndex() == CONT_TALKLIST) {
         return true;
     }*/
    return false;
}

int CMainFrame::getCurIdInfo(QY_MESSENGER_ID* pIdInfo)
{
    QY_MESSENGER_ID  idInfo;
    idInfo.ui64Id = 0;

    QWidget* pCur = ui->stackedWidgetInfo->currentWidget();
    if (pCur != NULL) {
        QString name = pCur->objectName();
        if (pCur->objectName() == "CDlgTalk_qt") {
            CDlgTalk_qt* pDlg = (CDlgTalk_qt*)pCur;
            DLG_TALK_var* pm_var = pDlg->get_pm_var();
            idInfo.ui64Id = pm_var->addr.idInfo.ui64Id;
        }
    }

    *pIdInfo = idInfo;
    return  0;


}


//联系人
void CMainFrame::on_toolBtnContact_clicked()
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (!pMisCnt) return;
    //
    if (!bDone_retrieveAllImObjRules(pMisCnt))return;

    //
    static bool sbInited_contactList = false;
    if (!sbInited_contactList) {
        sbInited_contactList = true;

        //
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

        //
       /* WinContactsList* pContactsList = (WinContactsList*)ui->stackedWidgetContact->widget(1);
        pContactsList->toContactList();*/

        //
        QApplication::restoreOverrideCursor();

        //
#ifdef  __DEBUG__
        showInfo_open0(0, mynull, _T("after toContactList"));
        //
        pQyMc->dbg.dwTickCnt_after_toContactList = myGetTickCount(mynull);
        int  iDiffInMs1 = pQyMc->dbg.dwTickCnt_after_toContactList - pQyMc->dwTickCnt_logon;
        int  iii = 0;
#endif
        //
    }


    //
    painterMenu("toolBtnContact");
    //ui->searchLineEdit->clear();
    //ui->centerWidget->show();
   // ui->stackedWidgetContact->setCurrentIndex(1);
    if (m_nContactsIndex == 0 || m_nContactsIndex == 1)
    {
        //群组信息
        ui->stackedWidgetInfo->setCurrentIndex(INFO_CONTACTS_GROUP_INFO);
    }
    else if (m_nContactsIndex == 2)
    {
        //联系人信息
        ui->stackedWidgetInfo->setCurrentIndex(INFO_CONTACTS_INFO);
    }
    onLineStatus();
    //if (initGroupBtn == 0)
    //{
    //	ui->rightStackedWidget->setCurrentWidget(winFullPicture);
    //}
    //else if (initGroupBtn == 1)
    //{
    //	ui->rightStackedWidget->setCurrentWidget(winContactsInfo);
    //}
    //else if (initGroupBtn == 2)
    //{
    //	ui->rightStackedWidget->setCurrentWidget(winContactsGroupInfo);
    //}
}

//系统设置
void CMainFrame::on_toolBtnSystem_clicked()
{


    if (!systemSetup) {
        systemSetup = new WinSystemSetup();
    }

    //
    systemSetup->show();
    systemSetup->activateWindow();
}


//缩小
void CMainFrame::on_ButtonMin_clicked()
{
    showMinimized();
}

//关闭
void CMainFrame::on_ButtonClose_clicked()
{
    //
    this->hide();

}

//
void CMainFrame::closeEvent(QCloseEvent* ev)
{
    CCtxQyMc* pQyMc = g_pQyMc;
    if (pQyMc) {
        if (pQyMc->bGuiQuit
            || pQyMc->bQuit)
        {
            QApplication::exit();
            return;
        }
    }
#if  10
    this->hide();
    ev->ignore();
#endif

}









//还原
void CMainFrame::on_ButtonRestore_clicked()
{/*
    QPoint windowPos;
    QSize windowSize;
    this->setGeometry(QRect(windowPos, windowSize));
    QDesktopWidget* pDesk = QApplication::desktop();
    this->setGeometry((pDesk->width() - this->width()) / 2, (pDesk->height() - this->height()) / 2, this->width() - 10, this->height());*/
    this->showNormal();
}

//放大 显示
void CMainFrame::on_ButtonMax_clicked()
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

    if (pProcInfo->m_var.b_app_showNormal) {
        //
        this->showNormal();

        //
    }
    else {

        //    
        this->showMaximized();
    }
    //QRect FactRect = QRect(desktopRect.x(), desktopRect.y(), , );
    //setGeometry(FactRect);
}

//显示用户消息
void CMainFrame::on_Contact_Msg(WinObjUser user)
{
    //ui->stackedWidgetContact->setCurrentIndex(CONT_TALKLIST);
    //ui->stackedWidgetInfo->setCurrentIndex(INFO_MSG);
    createCDlgTalk(user);

    //
    if (mSysTrayIcon_) {
        mSysTrayIcon_->remove_session(user.idinfo.toInt());
    }

    return;
}

//显示用户信息
void CMainFrame::on_Contacts_Info(WinObjUser user)
{
    if (user.dataType == 1)//群组
    {
        m_nContactsIndex = 0;
        ui->stackedWidgetInfo->setCurrentIndex(INFO_CONTACTS_GROUP_INFO);
        //群组信息
        if (isCurInStackWidget("CDlgTalk_imGrp_detail", ui->stackedWidgetInfo))
        {
            CDlgTalk_imGrp_detail* pContactsGroupInfo = (CDlgTalk_imGrp_detail*)ui->stackedWidgetInfo->currentWidget();
            pContactsGroupInfo->ShowContactsGroupInfo(user);
        }
    }
    else if (user.dataType == 2)//临时组
    {
        m_nContactsIndex = 1;
        ui->stackedWidgetInfo->setCurrentIndex(INFO_CONTACTS_GROUP_INFO);
        if (isCurInStackWidget("CDlgTalk_imGrp_detail", ui->stackedWidgetInfo))
        {
            CDlgTalk_imGrp_detail* pContactsGroupInfo = (CDlgTalk_imGrp_detail*)ui->stackedWidgetInfo->currentWidget();
            pContactsGroupInfo->ShowContactsGroupInfo(user);
        }
    }
    else if (user.dataType == 3)//好友
    {
        //ui->WidgetContactInfo->hide();
        m_nContactsIndex = 2;
        //联系人信息
        ui->stackedWidgetInfo->setCurrentIndex(INFO_MSG);
        if (isCurInStackWidget("CDlgTalk_msgr_detail", ui->stackedWidgetInfo))
        {
            CDlgTalk_msgr_detail* pContactsInfo = (CDlgTalk_msgr_detail*)ui->stackedWidgetInfo->currentWidget();
            pContactsInfo->ShowContactsListInfo(user);
        }
    }
}


//发送消息
void CMainFrame::on_SendMsg_clicked(WinObjUser user)
{
    painterMenu("toolBtnMsg");

    //  ui->stackedWidgetContact->setCurrentIndex(CONT_TALKLIST);
    /*  WinTalkList* pTalkList = (WinTalkList*)ui->stackedWidgetContact->widget(0);
      pTalkList->addListWidget(user);*/
    ui->stackedWidgetInfo->setCurrentIndex(INFO_MSG);
    createCDlgTalk(user);
    //ui->stackedWidget->setCurrentWidget(winTalkList);
    //ui->widgetContactInfo->show();
    //m_pDlgTalkInfo->setCDlgTalkInfo(user);
}


#if  0
//发起会议
void CMainFrame::on_SendMeeting_clicked(WinObjUser user)
{
    int64_t idInfo = user.idinfo.toInt();
    QY_MC* pQyMc = QY_GET_GBUF();
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    HWND  hWnd;
    int  iTalkSubtype = CONST_talkerSubtype_video;
    HWND  m_hWnd_shadow;

    //



#if  0
    if (!findTalker_shadow(pQyMc, idInfo, iTalkSubtype, &m_hWnd_shadow))
    {
        SetForegroundWindow(m_hWnd_shadow);
        return;
    }
    //
    pProcInfo->tryToTalkToMessenger_any(null, idInfo, iTalkSubtype, FALSE, FALSE, &hWnd);

    if (findTalker_shadow(pQyMc, idInfo, iTalkSubtype, &m_hWnd_shadow))
    {
        goto errLabel;
    }
    CDlgTalk_qt* video_cdlgTalkqt = (CDlgTalk_qt*)getObjAddr(m_hWnd_shadow);
    if (!video_cdlgTalkqt)
    {
        goto errLabel;
    }
    video_cdlgTalkqt->ShowMsgInfo(user);
    video_cdlgTalkqt->showWidget(user);
    //
    DLG_TALK_var* video_pm_var = video_cdlgTalkqt->get_pm_var();
    if (video_pm_var == NULL) goto errLabel;
    video_pm_var->m_iCmd = IDC_av;
    video_cdlgTalkqt->doTask_av(video_pm_var->m_iCmd, 0);
#endif


errLabel:

    qDebug() << "onSendVideoClicked error.";
}
#endif


//关闭指定Talker
void CMainFrame::slot_closeTalk(QString idInfo)
{

    CDlgTalk_qt* cdlgTalkqt = (CDlgTalk_qt*)getObjAddr(h_cdlgTalkqt);

    if (mynull != cdlgTalkqt)
    {

        DLG_TALK_var* pm_var = cdlgTalkqt->get_pm_var();
        if (QString::number(pm_var->addr.idInfo.ui64Id) == idInfo) {
            ui->stackedWidgetInfo->removeWidget(cdlgTalkqt);
            cdlgTalkqt->closeCDlgTalk_qt();

        }


    }

}

void CMainFrame::delTalkerList(QString idInfo) {
    /* WinTalkList* pTalkList = (WinTalkList*)ui->stackedWidgetContact->widget(0);
     pTalkList->delListWidget(idInfo);*/
}
void CMainFrame::delContactList(QString idInfo) {
    /* WinContactsList* pContactList = (WinContactsList*)ui->stackedWidgetContact->widget(1);
     pContactList->delTmpContactItem(idInfo);*/
}


//消息视频
void CMainFrame::createCDlgTalk(WinObjUser user)
{
    int  iErr = -1;
    QWidget* pCur = ui->stackedWidgetInfo->currentWidget();

    if (pCur != NULL) {
        QString name = pCur->objectName();
        if (pCur->objectName() == "CDlgTalk_qt") {
            CDlgTalk_qt* pDlg = (CDlgTalk_qt*)pCur;
            DLG_TALK_var* pm_var = pDlg->get_pm_var();
            if (pm_var->addr.idInfo.ui64Id == user.idinfo.toInt()) {
                return;
            }
        }
    }
#if 1   
    if (h_cdlgTalkqt)
    {
        CDlgTalk_qt* cdlgTalkqt = (CDlgTalk_qt*)getObjAddr(h_cdlgTalkqt);


        if (mynull != cdlgTalkqt)
        {
            ui->stackedWidgetInfo->removeWidget(cdlgTalkqt);
            cdlgTalkqt->closeCDlgTalk_qt();
        }
        h_cdlgTalkqt = nullptr;
    }
    else
    {
        if (ui->stackedWidgetInfo->count() > 0)
        {
            QWidget* pWidget = ui->stackedWidgetInfo->widget(0);
            if (pWidget->objectName() == "temp")
            {
                ui->stackedWidgetInfo->removeWidget(pWidget);
                pWidget->deleteLater();
            }
        }
    }
    HWND  m_hWnd = (HWND)this->winId();
    int64_t idInfo = user.idinfo.toInt();
    QY_MC* pQyMc = QY_GET_GBUF();
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    HWND  hWnd;
    int  iTalkSubtype = 0;
    if (pProcInfo->tryToTalkToMessenger_any(m_hWnd, idInfo, iTalkSubtype, FALSE, FALSE, &hWnd))
    {
        goto errLabel;
    }

    if (findTalker_shadow(pQyMc, idInfo, 0, &h_cdlgTalkqt))
    {
        goto  errLabel;
    }

    CDlgTalk_qt* shadow_cdlgTalkqt; shadow_cdlgTalkqt = (CDlgTalk_qt*)getObjAddr(h_cdlgTalkqt);
    if (!shadow_cdlgTalkqt)
    {
        goto errLabel;
    }
    shadow_cdlgTalkqt->ShowMsgInfo(user);
    shadow_cdlgTalkqt->hideWidget(user);
    // shadow_cdlgTalkqt->setCanResize(false);
    ui->stackedWidgetInfo->insertWidget(0, shadow_cdlgTalkqt);
    ui->stackedWidgetInfo->setCurrentIndex(0);
#endif // 0
#if 0   

    if (cdlgTalkqt) {
        ui->rightStackedWidget->removeWidget(cdlgTalkqt);
        cdlgTalkqt->close();
        cdlgTalkqt = nullptr;
    }
    cdlgTalkqt = new CDlgTalk_qt(this);
    cdlgTalkqt->hideWidget(user);
    ui->rightStackedWidget->addWidget(cdlgTalkqt);
    ui->rightStackedWidget->setCurrentWidget(cdlgTalkqt);
#endif   

    //ui->nameLabel->setText(user.name);
    //ui->dwLabel->setText(user.dw + " " + user.bm);

    iErr = 0;
errLabel:
    if (iErr) {
        qDebug() << "createCDlgTalk error.";
    }
}

//
bool CMainFrame::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
{
    Q_UNUSED(eventType);
    MSG* msg = reinterpret_cast<MSG*>(message);
    UINT m = msg->message;
    if (m == WM_COMMAND || m == CONST_qyWm_comm || m == CONST_qyWm_postComm || m == CONST_wmComm_EV_RXCHAR)
    {
        return postMessageQt(msg, result);
    }
    /*else if (m == WM_NCHITTEST)
    {
        return dealHTEvent((MSG*)message,result);
    }*/
    //

    if (m == CONST_qyWm_postRaiseShare) {
        if (m_Share) {
            m_Share->show();
            m_Share->raise();
        }


    }

    if (m == WM_CLOSE) {
        CCtxQyMc* pQyMc = g_pQyMc;
        if (pQyMc) {
            if (!pQyMc->bGuiQuit) {
                return  true;
            }
        }
        if (!pQyMc->bQuit) {
            return true;
        }
    }
    //  if (m == WM_DEVICECHANGE)
    //  {
    ////      showShareStreamWidget();
    //      QTimer::singleShot(1000, [this]() { showShareStreamWidget(); });
    //  }

    if (eventType == QByteArray("windows_generic_MSG"))
    {
        MSG* pMsg = reinterpret_cast<MSG*>(message);
        if (pMsg->message == WM_DEVICECHANGE)
        {
            auto screens = QGuiApplication::screens();
            if (screenNum != screens.count())
            {
                if (screens.count() > screenNum)
                {
                    qDebug() << u8"检测到扩展屏加入";
                    showShareStreamWidget();
                }
                else
                {
                    qDebug() << u8"检测到扩展屏移除";
                    closeShareStreamWidget();
                }
                screenNum = screens.count();
            }
        }
    }

    /* if (eventType == QByteArray("windows_generic_MSG"))
     {
         MSG* pMsg = reinterpret_cast<MSG*>(message);
         if (pMsg->message == WM_DEVICECHANGE)
         {
             auto screens = QGuiApplication::screens();
             if (screens !=  screens.count() )
             {

             }
         }
     }*/



     //
    return QWidget::nativeEvent(eventType, message, result);
}
//
bool CMainFrame::postMessageQt(MSG* message, qintptr* result)
{
    if (message->message == WM_COMMAND)
    {
        int id = LOWORD(message->wParam);
        if (id == ID_qyRefresh)
        {
            //
#ifdef  __DEBUG__
            showInfo_open0(0, mynull, _T("mainWnd. get ID_qyRefresh"));
#endif 

            QY_MC* pQyMc = QY_GET_GBUF();
            CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
            if (!pProcInfo)  return  true;
            MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
            if (!pMisCnt) return true;

            BOOL ret = bDone_retrieveAllImObjRules(pMisCnt);
            if (ret && loadInfoFinishInit == FALSE)
            {
                //
#ifdef  __DEBUG__
                showInfo_open0(0, mynull, _T("before initCMainFrameInfo"));
                pQyMc->dbg.dwTickCnt_bDone_retrieveAllImObjRules = myGetTickCount(NULL);
                int  iDiffInMs = pQyMc->dbg.dwTickCnt_bDone_retrieveAllImObjRules - pQyMc->dwTickCnt_logon;
                int  ii = 0;
#endif

                //
                loadInfoFinishInit = TRUE;
                initCMainFrameInfo();



#ifdef  __DEBUG__
                showInfo_open0(0, mynull, _T("after initCMainFrameInfo"));
                pQyMc->dbg.dwTickCnt_after_initCMainFrameInfo = myGetTickCount(NULL);
                iDiffInMs = pQyMc->dbg.dwTickCnt_after_initCMainFrameInfo - pQyMc->dwTickCnt_logon;
                ii = 0;

#endif

                //
#if  0
                //
                WinContactsList* pContactsList = (WinContactsList*)ui->stackedWidgetContact->widget(1);
                pContactsList->toContactList();

#ifdef  __DEBUG__
                showInfo_open0(0, null, _T("after toContactList"));
                //
                pQyMc->dbg.dwTickCnt_after_toContactList = myGetTickCount(null);
                int  iDiffInMs1 = pQyMc->dbg.dwTickCnt_after_toContactList - pQyMc->dwTickCnt_logon;
                int  iii = 0;
#endif
                //

                
#endif
                
                if (pProcInfo->getAuthType() == CONST_authType_logon) {
                    pProcInfo->cfg.bSkip_sm_usrLogin = true;
                }
                else {
                    pProcInfo->cfg.bSkip_sm_usrLogin = false;
                }

                //
                if (!m_pUserLogin) {
                    m_pUserLogin = new CUserLogin(mynull);
                }
                //
                this->hWnd_curWorking = (HWND)m_pUserLogin->winId();

                //
                connect(m_pUserLogin, SIGNAL(to_userLoginFinished_signal()), this, SLOT(on_userLoginFinished()));

                //cLogin.setWindowFlags(Qt::Window);
               // if (!pProcInfo->cfg.bSkip_sm_usrLogin) {
                    m_pUserLogin->show();
                //}

               
                // m_pUserLogin->showMaximized();
                // m_pUserLogin->activateWindow();
                 //
                {
                    DBManager* pDm = (DBManager*)pProcInfo->m_var.pDBManager;
                    QList<SessionInfo> siList = pDm->getSessions();

                    if (siList.size() == 0)
                    {
                        switchToContact();
                    }
                }


            }


            //
            return true;
        }
        if (id == ID_qyQuitMainWnd)
        {
            HWND  m_hWnd = (HWND)this->winId();
            mainWnd_OnQyQuitMainWnd(m_hWnd, &var);
            return true;
        }
        if (id == ID_qyShowWnd) {
            HWND  m_hWnd = (HWND)this->winId();
            //
            //ShowWindow(m_hWnd, SW_NORMAL);
            //SetForegroundWindow(m_hWnd);
            //SetForegroundWindow(GetLastActivePopup(hPrevWnd));

            if (!this->isVisible())
            {
                this->setVisible(true);
            }
            if (this->windowState() == Qt::WindowState::WindowMinimized)
            {
                this->setWindowState(Qt::WindowState::WindowNoState);
            }
            this->show();
            this->activateWindow();
            this->raise();

            //
            return  true;
        }

    }
    else if (message->message == CONST_qyWm_comm)
    {
        //
        HWND  hMainWnd = (HWND)this->winId();
        //
        QY_WMBUF_COMM* pWmBuf = (QY_WMBUF_COMM*)message->lParam;
        if (message->wParam == CONST_qyWmParam_getObjAddr)
        {
            pWmBuf->u.getObjAddr.pObjAddr = this;
            *result = CONST_qyWmRc_ok;
            return  true;
        }
        // 
    }
    else if (message->message == CONST_qyWm_postComm)
    {
        //emit toSendMsgHandle();
        HWND  hMainWnd = (HWND)this->winId();
        mainWnd_OnQyPostComm(hMainWnd, &var, message->wParam, message->lParam);
        return  true;
    }
    else  if (message->message == CONST_wmComm_EV_RXCHAR) {
        //
        QY_MC* pQyMc = QY_GET_GBUF();
        CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
        if (!pProcInfo)  return  true;
        // 
        pProcInfo->infrared_recvChar(message->wParam, message->lParam);
        //
        pProcInfo->m_var.usrInput.dwLastTickCnt_infrareadRecvd = myGetTickCount(nullptr);
        //
        return  true;

    }

    //
    return false;
}



//
void CMainFrame::on_userLoginFinished()
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

    //
    if (bNeedReinit()) {
        exit((TCHAR*)_T("on_usrLoginFinished.bNeedReinit true"));
        return;
    }

    //
    pProcInfo->m_var.usrInput.dwLastTickCnt_usrLoginFinished = myGetTickCount(nullptr);
    //
    pProcInfo->xt.bUsrLogined = true;

    //if (pProcInfo->m_var.b_app_showNormal) {
    //    //
    //    this->showNormal();

    //    //
    //    }
    //else {
        //
    this->on_ButtonMax_clicked();
    // }

     //
    return;

}



//

void CMainFrame::painterMenu(const QString pushBtnName)
{


}

int CMainFrame::initCMainFrameInfo()
{
    int  iRet = 0;
    QY_MC* pQyMc = QY_GET_GBUF();
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return  -1;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (!pMisCnt)  return  -1;

    QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
    QM_dbFuncs& g_dbFuncs = *pDbFuncs;

    QY_MESSENGER_REGINFO		regInfo;
    MY_REG_DESC	 desc;

    QY_OBJ_DB* pObjDb = getProcedObjDb(pQyMc, 0, pQyMc->iDsnIndex_mainSys);
    if (!bObjDbAvail(pObjDb)) return -1;
    CMyDb* pDb = (CMyDb*)pObjDb->pDb;
    LPCTSTR misServName = _T("");

    if (!g_dbFuncs.pf_bGetMessengerRegInfoBySth(pDb, CONST_dbType_myDb, getResTable(0, &pQyMc->cusRes, CONST_resId_fieldIdTable),
        CONST_tabName_qyImObjRegInfoTab, misServName, &pMisCnt->idInfo, 0, &regInfo)) {
        memset(&regInfo, 0, sizeof(regInfo));
    }

    TCHAR	talkerDesc[128] = _T("");
    regInfo2Desc(0, &regInfo, &desc, talkerDesc, mycountof(talkerDesc), NULL, 0);
    QString pDw = QString::fromWCharArray(desc.pDw).trimmed();
    QString pBm = QString::fromWCharArray(desc.pBm).trimmed();
    QString pSyr = QString::fromWCharArray(desc.pSyr).trimmed();
    qint64 ui64Id = pMisCnt->idInfo.ui64Id;

    //
    if (pSyr == "") {
        m_myName = ("(" + QString::number(ui64Id) + ")");
    }
    else {
        m_myName = (pSyr);
    }


    //
  //  ui->signName->setText(pDw + " " + pBm);

    //
    showInfo_open0(0, mynull, _T("CMainFrame::initCMainFrameInfo, set userName"));

    //
   /* WinTalkList* pTalkList = (WinTalkList*)ui->stackedWidgetContact->widget(0);
    if (pTalkList)
    {
        pTalkList->initWinTalkListInfo();
    }*/
    return iRet;
}



bool CMainFrame::eventFilter(QObject* obj, QEvent* event)
{

    /* if (event->type() == QEvent::MouseButtonPress)
     {
         int i = 121;
     }*/
     /*if (obj == ui->signName || obj == ui->userName)
     {
         if (event->type() == QEvent::MouseButtonPress)
         {
             on_headIcoBtn_clicked();
         }
     }
     if (obj == ui->redCount)
     {
         if (event->type() == QEvent::MouseButtonPress)
         {
             on_toolBtnMsg_clicked();
         }
     }*/

   
   /* if (obj == ui->lab_tishi && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {   
            qDebug() << "Label clicked!";

            if (m_Share == nullptr) {
                m_Share = new CDlgShareDynBmps_qt(this);
                RECT rect;
                m_Share->dlgShareDynBmps_Create(rect);
                m_Share->dlgShareDynBmps_OnInitDialog();

            }
            m_Share->show();
            m_Share->raise();
            return true; 
        }
    }*/
    return QWidget::eventFilter(obj, event);
}

void CMainFrame::on_headIcoBtn_clicked()
{
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    qint64 uid = pMisCnt->idInfo.ui64Id;
    //QString userName = ui->userName->text();
   // QString dw = ui->signName->text();

   // UserInfoDialog::showDialog(QString::number(uid), userName, "dw");
}






int  tmpHandler_printContactList_search(void* p0, void* p1, void* p2)
{
    int  iRet = -1;
    COMMON_PARAM* pCommonParam = (COMMON_PARAM*)p0;
    COMMON_PARAM* pCommonParam1 = (COMMON_PARAM*)p1;
    //
    CMyDb* pDb = (CMyDb*)pCommonParam->p0;
    //  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
    //HWND				hListCtrl = (HWND)pCommonParam->p1;
    //if (!hListCtrl)  goto  errLabel;
    int				iItem = (int)pCommonParam->p2;
    //
    QList<SearchInfoData>* pList = (QList<SearchInfoData>*)pCommonParam1->p0;
    QString* pStr = (QString*)pCommonParam1->p1;
    //BOOL				bUnprocedOnly = (BOOL)p1;
    //
    QMEM_qyImObj* pQMem = (QMEM_qyImObj*)p2;
    int				index = 0;
    QY_MC* pQyMc = QY_GET_GBUF();

    QY_MESSENGER_REGINFO		regInfo;
    MY_REG_DESC					desc;
    TCHAR						tBuf[256];
    QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable);

    memset(&regInfo, 0, sizeof(regInfo));

    QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
    if (!pDbFuncs)  return  -1;// goto  errLabel;
    QM_dbFuncs& g_dbFuncs = *pDbFuncs;


    if (pQMem->messengerInfo.iStatus == CONST_qyStatus_ok
        && pQMem->messengerInfo.uiType != CONST_objType_imGrp)
    {

        _sntprintf(tBuf, mycountof(tBuf), _T("%I64u"), pQMem->messengerInfo.idInfo.ui64Id);

        if (!g_dbFuncs.pf_bGetMessengerRegInfoBySth(pDb, CONST_dbType_myDb, getResTable(0, &pQyMc->cusRes, CONST_resId_fieldIdTable), CONST_tabName_qyImObjRegInfoTab, pQMem->messengerInfo.misServName, &pQMem->messengerInfo.idInfo, 0, &regInfo)) {
            memset(&regInfo, 0, sizeof(regInfo));
        }
        int		tmpiRet;
        TCHAR	talkerDesc[128] = _T("");
        regInfo2Desc(0, &regInfo, &desc, talkerDesc, mycountof(talkerDesc), NULL, 0);

        traceLog((TCHAR*)_T("contact %I64u, %s %s %s "), pQMem->messengerInfo.idInfo.ui64Id, desc.pDw, desc.pBm, desc.pSyr);
        QString name = QString::fromUtf16((char16_t*)desc.pDw) + "  " + QString::fromUtf16((char16_t*)desc.pBm) + "  " + QString::fromUtf16((char16_t*)desc.pSyr) + "(" + QString::number(pQMem->messengerInfo.idInfo.ui64Id) + ")";
        int of_res = name.indexOf(*pStr, 0, Qt::CaseInsensitive);
        if (of_res != -1) {

            SearchInfoData data;
            data.userId = QString::number(pQMem->messengerInfo.idInfo.ui64Id);
            data.url = ":/Resources/Images/WinMain/person.png";
            data.name = name;
            pList->append(data);
        }
    }

    iRet = 0;
errLabel:
    return  iRet;
}


int  tmpHandler_printImGrpList_search(void* p0, void* p1, void* p2)
{
    int  iRet = -1;
    COMMON_PARAM* pCommonParam = (COMMON_PARAM*)p0;
    COMMON_PARAM* pCommonParam1 = (COMMON_PARAM*)p1;
    //
    CMyDb* pDb = (CMyDb*)pCommonParam->p0;
    //  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
    //HWND				hListCtrl = (HWND)pCommonParam->p1;
    //if (!hListCtrl)  goto  errLabel;
    int				iItem = (int)pCommonParam->p2;
    //
    // 
    QList<SearchInfoData>* pList = (QList<SearchInfoData>*)pCommonParam1->p0;
    QString* pStr = (QString*)pCommonParam1->p1;
    // BOOL				bUnprocedOnly = (BOOL)p1;
     //
    IM_GRP_INFO* pQMem = (IM_GRP_INFO*)p2;
    int				index = 0;
    QY_MC* pQyMc = QY_GET_GBUF();

    QY_MESSENGER_REGINFO		regInfo;
    MY_REG_DESC					desc;
    TCHAR						tBuf[256];
    QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable);

    memset(&regInfo, 0, sizeof(regInfo));

    QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
    if (!pDbFuncs)  return -1;// goto  errLabel;
    QM_dbFuncs& g_dbFuncs = *pDbFuncs;


    //  if  (  pQMem->uiType  ==  CONST_objType_imGrp  )
    {

#if  0
        _sntprintf(tBuf, mycountof(tBuf), _T("%I64u"), pQMem->idInfo.ui64Id);
        index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

        _sntprintf(tBuf, mycountof(tBuf), _T("%s"), pQMem->name);
        index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

        _sntprintf(tBuf, mycountof(tBuf), _T("%s"), qyGetDesByType1(getResTable(0, &pQyMc->cusRes, CONST_resId_imGrpSubtypeTable), pQMem->usSubtype));
        index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

        _sntprintf(tBuf, mycountof(tBuf), _T("%I64u"), pQMem->idInfo_creator.ui64Id);
        index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);
#endif

        //
        traceLog((TCHAR*)_T("Grp %I64u, %s, created by %I64u"), pQMem->idInfo.ui64Id, pQMem->name, pQMem->idInfo_creator.ui64Id);
        QString name = QString::fromUtf16((char16_t*)pQMem->name) + "(" + QString::number(pQMem->idInfo.ui64Id) + ")";
        int of_res = name.indexOf(*pStr, 0, Qt::CaseInsensitive);
        if (of_res != -1) {
            SearchInfoData data;
            data.userId = QString::number(pQMem->idInfo.ui64Id);
            data.url = ":/Resources/Images/WinMain/group.png";
            data.name = name;
            pList->append(data);
        }
    }

    iRet = 0;
errLabel:
    return  iRet;
}




void CMainFrame::slot_search_text_changed(QString str)
{
    if (str.isEmpty())
    {
        searchListMoudle_->clear();
        searchListView_->setVisible(false);
        return;
    }

    searchListView_->setVisible(true);
    /* QRect rec = ui->stackedWidgetContact->geometry();
     searchListView_->setGeometry(ui->stackedWidgetContact->geometry());
     searchListView_->show();*/



    QList<SearchInfoData > m_infoList;
    QList<SearchInfoData>* pList = &m_infoList;
    QString* pStr = &str;
    {
        SearchInfoData data;
        data.isGourp = true;
        data.name = QStringLiteral("联系人");
        m_infoList.append(data);

    }

    QY_MC* pQyMc = QY_GET_GBUF();
    //
    QY_OBJ_DB* pObjDb = getProcedObjDb(pQyMc, 0, pQyMc->iDsnIndex_mainSys);
    if (!bObjDbAvail(pObjDb))  return;

    //	//
    CMyDb* pDb = (CMyDb*)pObjDb->pDb;
    int cnt = 0;
    COMMON_PARAM	commonParam;
    COMMON_PARAM    commonParam1;
    //  MACRO_makeCommonParam3(  pDb,  pListCtrl,  (  void  *  )cnt,  commonParam  );
    MACRO_makeCommonParam3(pDb, 0, (void*)cnt, commonParam);
    MACRO_makeCommonParam3(pList, pStr, 0, commonParam1);

    qTraverse(pDb->m_var.pQ_qyImObjTab, tmpHandler_printContactList_search, &commonParam, &commonParam1);
    //

    {
        SearchInfoData data;
        data.isGourp = true;
        data.name = QStringLiteral("群聊");
        m_infoList.append(data);
    }
    //
    qTraverse(pDb->m_var.pQ_qyImGrpInfoTab, tmpHandler_printImGrpList_search, &commonParam, &commonParam1);


    //search_fill_grp(m_infoList);
    {
        SearchInfoData data;
        data.isGourp = true;
        data.name = QStringLiteral("聊天记录");
        m_infoList.append(data);
    }

    search_fill_msg(m_infoList, str);
    _keyword = str;
    _searchList = m_infoList;
    searchListMoudle_->setMoudleData(m_infoList);
    //
    onLineStatusUp();
}

int  CMainFrame::onLineStatusUp()
{
    QY_MC* pQyMc = QY_GET_GBUF();
    QY_MESSENGER_ID  idInfo;

    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return  -1;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (!pMisCnt)  return  -1;
    int height_s = searchListView_->height();
    int rowCount = searchListView_->model()->rowCount();
    for (int j = 0; j < rowCount; j++)
    {

        QModelIndex s = searchListView_->model()->index(j, 0);

        QRect rc = searchListView_->visualRect(s);

        if (rc.bottom() < height_s && rc.top() >= 0) {
            //       qDebug() << "item[" << j << "]," << rc.x() << "," << rc.y() << "," << rc.top() << "," << rc.bottom() << ",";
            SearchInfoData  tmp_data = searchListMoudle_->at(j);
            if (!tmp_data.userId.isEmpty()) {
                idInfo.ui64Id = tmp_data.userId.toInt();
                postRecentFriend(pMisCnt, idInfo, 0);
            }
        }
    }
    pMisCnt->refreshRecentFriends.bRefreshAtOnce = true;

    return 0;
}
//修改搜索结果的在线状态
void CMainFrame::updateSearchItem(qint64 idInfo, unsigned  short status)
{
    //
    for (int i = 0; i < _searchList.size(); i++)
    {
        if (_searchList[i].userId.toInt() == idInfo) {

            if (status == CONST_usRunningStatus_online) {
                _searchList[i].url = ":/Resources/Images/WinMain/person_on.png";
            }

        }
    }
    searchListMoudle_->setMoudleData(_searchList);

}

void CMainFrame::slot_list_activated(QModelIndex idx)
{
    SearchListModel* model = (SearchListModel*)searchListView_->model();
    auto item = model->at(idx.row());
    if (item.isGourp)
    {
        return;
    }
    if (item.isMsg)
    {
        QPoint pt = searchListView_->mapToGlobal(QPoint(0, 0));
        pt.setX(pt.x() + searchListView_->width());

        // SearchMsgRecord::closeDialog();

        SearchMsgRecord::getDialog();
        SearchMsgRecord::setContent(item.userId, _keyword);
        //
        SearchMsgRecord::showWnd(pt);
        return;
    }
    QString userId = item.userId;
    //TODO:点击了 选中的一项
    WinObjUser user;
    user.idinfo = userId;
    /* WinTalkList* pTalkList = (WinTalkList*)ui->stackedWidgetContact->widget(0);


     pTalkList->addListWidget(user);*/
    on_Contact_Msg(user);
    painterMenu("toolBtnMsg");
}

//搜索框滚动条事件
void CMainFrame::onScrollBarValueChanged(int value)
{
    onLineStatusUp();
}

void CMainFrame::cut_talk_list(WinObjUser user) {
    /* WinTalkList* pTalkList = (WinTalkList*)ui->stackedWidgetContact->widget(0);
     pTalkList->addListWidget(user);*/
    on_Contact_Msg(user);
    painterMenu("toolBtnMsg");
    this->activateWindow();
}


int  CMainFrame::displayRecentFriends(MIS_MSG_displayRecentFriends_qmc* pMsg)
{
    // WinTalkList* pTalkList = (WinTalkList*)ui->stackedWidgetContact->widget(0);
   /*  for (int j = 0; j < pMsg->resp.usCnt; j++)
     {
         if (pMsg->resp.mems[j].usRunningStatus != CONST_usRunningStatus_online) {
             pTalkList->updateTalkItem(pMsg->resp.mems[j].idInfo.ui64Id, pMsg->resp.mems[j].usRunningStatus);
         }
         else if (pMsg->resp.mems[j].usRunningStatus == CONST_usRunningStatus_online) {
             pTalkList->updateTalkItem(pMsg->resp.mems[j].idInfo.ui64Id, pMsg->resp.mems[j].usRunningStatus);
         }
     }*/

     /* WinContactsList* pContactsList = (WinContactsList*)ui->stackedWidgetContact->widget(1);
      for (int i = 0; i < pMsg->resp.usCnt; i++)
      {
          if (pMsg->resp.mems[i].usRunningStatus != CONST_usRunningStatus_online) {
              pContactsList->updateContactItem(pMsg->resp.mems[i].idInfo.ui64Id , pMsg->resp.mems[i].usRunningStatus);
          }
          else if (pMsg->resp.mems[i].usRunningStatus == CONST_usRunningStatus_online) {
              pContactsList->updateContactItem(pMsg->resp.mems[i].idInfo.ui64Id , pMsg->resp.mems[i].usRunningStatus);
          }
      }*/

    for (int i = 0; i < pMsg->resp.usCnt; i++)
    {
        if (pMsg->resp.mems[i].usRunningStatus != CONST_usRunningStatus_online) {
            this->updateSearchItem(pMsg->resp.mems[i].idInfo.ui64Id, pMsg->resp.mems[i].usRunningStatus);
        }
        else if (pMsg->resp.mems[i].usRunningStatus == CONST_usRunningStatus_online) {
            this->updateSearchItem(pMsg->resp.mems[i].idInfo.ui64Id, pMsg->resp.mems[i].usRunningStatus);
        }
    }


    return  0;
}


void CMainFrame::system_resolution()
{
    DEVMODE devMode;
    devMode.dmSize = sizeof(DEVMODE);
    devMode.dmPelsWidth = 1920;
    devMode.dmPelsHeight = 1080;
    devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

    LONG result = ChangeDisplaySettings(&devMode, CDS_TEST);
    if (result == DISP_CHANGE_SUCCESSFUL) {
        result = ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
        if (result != DISP_CHANGE_SUCCESSFUL) {
            // 恢复原来的显示设置
            ChangeDisplaySettings(NULL, 0);
            return;
        }
        //
        exit((TCHAR*)_T("mainFrame.on_showDeviceBinding"));
        return;
    }

    return;
}
