


#include	"stdafx.h"
//
#include <CMainFrame.h>

//
#include	"qyMcMainCommon_qt.h"
#include <string>
#include <ctxQmc_sm.h>
#include <qyMcMainWndProc.h>
#include <GuiShare.h>
#include    "myDb.h"
#include "MessageSignalCenter.h"
#include "DlgAvAccept.h"

#include    "CDeviceBinding.h"
#include <infraredInstruct.h>
#include <CQmcLogin.h>

extern bool compareSpecalObjName(const QString& objName);

//
HWND  gethWndWork()
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CMainFrame* pMainFrame = (CMainFrame*)CMainFrame::find((WId)pQyMc->gui.hMainWnd);
    if (!pMainFrame) return mynull;

    HWND  hWndWork = mynull;

    if (IsWindow(pMainFrame->hWnd_curWorking)) {
        hWndWork = pMainFrame->hWnd_curWorking;
    }
    else {
        hWndWork = pQyMc->gui.hMainWnd;
    }

    //


    //
    return  hWndWork;
}


//
void mainWnd_recvInfraredInstruct(CMainFrame  *  pMainFrame,  TCHAR* instruct, qint64 port)
{
    //
    QString str = QString::fromUtf16((char16_t*)_T("mainWnd_recvInfraredInstruct called"));
    showInfo_open0(0, 0, (TCHAR*)str.utf16());


    //
#ifdef  __DEBUG__
    if (0) {
        static bool sb = false;
        if (!sb) {
            sb = true;
            //
            mainWnd_recvInfraredInstruct(pMainFrame, (TCHAR*)_T("2"), port);
        }
    }
#endif

    //
    DWORD  dwTickCnt = myGetTickCount(nullptr);
    //
    if (pMainFrame->_instruct_num == 0) {
        pMainFrame->_instruct_first_tickCnt = dwTickCnt;
    }
    else {
        int  iDiffInMs = dwTickCnt - pMainFrame->_instruct_first_tickCnt;
        if (abs(iDiffInMs) > 500) {
            pMainFrame->_instruct_num = 0;
            pMainFrame->_instruct = nullptr;
            //
            showInfo_open0(0, 0, _T("mainWnd_recvInfra.74, clear _instruct"));
            //
            pMainFrame->_instruct_first_tickCnt = dwTickCnt;
        }
    }

    //
    pMainFrame->_instruct_num += 1;
    pMainFrame->_instruct = pMainFrame->_instruct + QString::fromStdWString(instruct).simplified();


    //暂定接收3次 
    if (pMainFrame->_instruct_num < 3 ) {
        return;
    }

    pMainFrame->_instruct_num = 0;

    //
    str = QString::fromUtf16((char16_t*)_T("recvInfraredInstruct--------")) + pMainFrame->_instruct;
    showInfo_open0(0, 0, (TCHAR*)str.utf16());
    
    //
#ifdef  __DEBUG__
    traceLog((TCHAR*)_T("mainWnd_infraredInstruct"));
#endif

    //
    HWND  hWndWork = gethWndWork();
    if (!hWndWork) {
        showInfo_open0(0, 0, _T("mainWnd.recvInfra failed, 73. hWndWork is null"));
        return;
    }
    HWND  hCurr = hWndWork;

    //
    QWidget* pWin = QWidget::find((WId)hWndWork);
    if (!pWin) {
        showInfo_open0(0, 0, _T("mainWnd.recvInfra failed, 81, find(hWndWork) is null"));
        return;
    }


    //调用菜单
    if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_MENU) {

        //
        qDebug() << pWin->objectName();
        QString str;
        str = QString::fromUtf16((char16_t*)_T("mainWnd.recvInfra: 89, win.objName "))  +  pWin->objectName();
        showInfo_open0(0, 0, QStringToTCHAR(str));       
        
        //
        if (pWin->objectName() == "CDeviceBindingClass") {
            mainWnd_infraredMenu(pMainFrame, "CDeviceBind");
        }
        else if (pWin->objectName() == "CMainFrame") {
            mainWnd_infraredMenu(pMainFrame, "index");
        }
        else if (pWin->objectName() == "CDlgTalk_qt") {

            mainWnd_infraredMenu(pMainFrame, "cdlgtalk");
        }
        else if (pWin->objectName() == "CQmcLogin") {
            mainWnd_infraredMenu(pMainFrame, "login");
        }
        else {
            mainWnd_infraredMenu(pMainFrame, "CDeviceBind");
        }
    
    }

    //菜单退出
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_MENU_QUIT)
    {
        QWidget* myWidget = QApplication::focusWidget();
       

        mainWnd_infraredMenu_quit(pMainFrame);

    }

    //下箭头
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_NEXT) {
        qDebug() << pWin->objectName();

        //初始化页面
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_down();
        }
        //视频页面
        if (pWin->objectName() == "CDlgTalk_qt") {
            CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
            if (pWin_cdlgtalk == mynull) {
                return;
            }
            pWin_cdlgtalk->Infrared_down();
        }


        
        if (pWin->objectName() == "CQmcLogin") {
            CQmcLogin* pWin_qmc = (CQmcLogin*)QWidget::find((WId)hCurr);
            if (pWin_qmc == mynull) {
                return;
            }
            pWin_qmc->Infrared_down();
        }

        

        //用户登录页
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_user = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_user == mynull) {
                return;
            }
            pWin_user->Infrared_down();
        }
        //主窗口
        if (pWin->objectName() == "CMainFrame") {
            CMainFrame* pWin_main = (CMainFrame*)QWidget::find((WId)hCurr);
            if (pWin_main == mynull) {
                return;
            }
            pWin_main->Infrared_down();
        }

        //
        QString objName = pWin->objectName();
        int  ii = 0;



    }
    //上箭头
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_UP) {
        qDebug() << pWin->objectName();


        if (pWin->objectName() == "CQmcLogin") {
            CQmcLogin* pWin_qmc = (CQmcLogin*)QWidget::find((WId)hCurr);
            if (pWin_qmc == mynull) {
                return;
            }
            pWin_qmc->Infrared_up();
        }
        
        //视频页面
        if (pWin->objectName() == "CDlgTalk_qt") {
            CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
            if (pWin_cdlgtalk == mynull) {
                return;
            }
            pWin_cdlgtalk->Infrared_up();
        }

        
        //初始化页面
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_up();
        }
       
        //用户登录页
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_user = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_user == mynull) {
                return;
            }
            pWin_user->Infrared_up();
        }
        //主窗口
        if (pWin->objectName() == "CMainFrame") {
            CMainFrame* pWin_main = (CMainFrame*)QWidget::find((WId)hCurr);
            if (pWin_main == mynull) {
                return;
            }
            pWin_main->Infrared_up();
        }
    }
    //确认键
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_OK) {


      /*  QWidget* myWidget = QWidget::find((WId)hWndWork);
        if (!myWidget) return;*/


        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {

            //视频窗口
            if (pWin->objectName() == "CDlgTalk_qt") {
                CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
                pWin_cdlgtalk->Infrared_ok("");

            }
            pMainFrame->_instruct = nullptr; //清空本次指令

            return;
        }
        QString objName = myWidget->objectName();

        //初始化页面
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            if (myWidget->objectName() == "btn") {
                pWin_device->on_btn_clicked(myWidget->objectName());
            }
            else if (myWidget->objectName() == "btnGetTag") {
                pWin_device->on_btnGetTag_clicked(myWidget->objectName());
            }
            else if (myWidget->objectName() == "checkBox_cert") {
                pWin_device->slot_checkBoxCert_click(myWidget->objectName());
            }
            else if (myWidget->objectName() == "btnCancel") {
                pWin_device->on_btnCancel_clicked(myWidget->objectName());
            }

            else if (myWidget->objectName() == "btnRet") {
                pWin_device->on_closePortSetting_slots();
            }

            else if (myWidget->objectName() == "boxVga") {
                pWin_device->doBoxPort("boxVga");
            }
            else if (myWidget->objectName() == "boxHdmi") {
                pWin_device->doBoxPort("boxHdmi");
            }
            else if (myWidget->objectName() == "boxDvi") {
                pWin_device->doBoxPort("boxDvi");
            }
            else if (myWidget->objectName() == "boxUsb1") {
                pWin_device->doBoxPort("boxUsb1");
            }
            else if (myWidget->objectName() == "boxUsb2") {
                pWin_device->doBoxPort("boxUsb2");
            }
            else if (myWidget->objectName() == "boxAudioOut") {
                pWin_device->doBoxPort("boxAudioOut");
            }
            else if (myWidget->objectName() == "boxUsb3") {
                pWin_device->doBoxPort("boxUsb3");
            }
            else if (myWidget->objectName() == "boxLan") {
                pWin_device->doBoxPort("boxLan");
            }

            else if (myWidget->objectName() == "boxNvrEna") {
                pWin_device->doBoxNvr("boxNvrEna");
            }
            else if (myWidget->objectName() == "boxNvrDh") {
                pWin_device->doBoxNvr("boxNvrDh");
            }
            else if (myWidget->objectName() == "boxNvrHik") {
                pWin_device->doBoxNvr("boxNvrHik");
            }
            else if (myWidget->objectName() == "boxNvrD4k") {
                pWin_device->doBoxNvr("boxNvrD4k");
            }
            else if (myWidget->objectName() == "boxRtsp") {
                pWin_device->doBoxNvr("boxRtsp");
            }
            else if (compareSpecalObjName(myWidget->objectName())) {
                pWin_device->doBoxNvr(myWidget->objectName());
            }
            else if (myWidget->objectName() == "btnOk") {
                pWin_device->doBoxNvr("btnOk");
            }
            else if (myWidget->objectName() == "pushButton_detect") {
                pWin_device->doBoxNvr("pushButton_detect");
            }
            else if (myWidget->objectName() == "treeWidget_wifi") {
                pWin_device->doBoxNvr("treeWidget_wifi");
            }
            else if (myWidget->objectName() == "pushButton_conn") {
                pWin_device->doBoxNvr("pushButton_conn");
            }           
            else {
                pWin_device->Infrared_ok(myWidget->objectName());
            }
        }
        
        //用户登录页
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_user = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_user == mynull) {
                return;
            }
          //  pWin_user->on_loginUserBtn_clicked(myWidget->objectName());
           
            if (myWidget->objectName() == "loginUserBtn") {
                pWin_user->on_loginUserBtn_clicked(myWidget->objectName());
           //     emit pMainFrame->to_userLogin_signal();
                //pWin_user->on_loginUserBtn_clicked();
            }
            else {
                pWin_user->Infrared_ok(myWidget->objectName());
            }

        }
        //
        if (pWin->objectName() == "CQmcLogin") {
            CQmcLogin* pWin_qmc = (CQmcLogin*)QWidget::find((WId)hCurr);
            if (pWin_qmc == mynull) {
                return;
            }
            
            pWin_qmc->Infrared_ok(myWidget->objectName());
        }
        //视频窗口
        if (pWin->objectName() == "CDlgTalk_qt") {
            CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
            if (pWin_cdlgtalk == mynull) {
                return;
            }
           if (myWidget->objectName() == "btnRet") {
                pWin_cdlgtalk->on_closePortSetting_slots();
            }

            else if (myWidget->objectName() == "boxVga") {
                pWin_cdlgtalk->doBoxPort("boxVga");
            }
            else if (myWidget->objectName() == "boxHdmi") {
                pWin_cdlgtalk->doBoxPort("boxHdmi");
            }
            else if (myWidget->objectName() == "boxDvi") {
                pWin_cdlgtalk->doBoxPort("boxDvi");
            }
            else if (myWidget->objectName() == "boxUsb1") {
                pWin_cdlgtalk->doBoxPort("boxUsb1");
            }
            else if (myWidget->objectName() == "boxUsb2") {
                pWin_cdlgtalk->doBoxPort("boxUsb2");
            }
            else if (myWidget->objectName() == "boxAudioOut") {
               pWin_cdlgtalk->doBoxPort("boxAudioOut");
           }
            else if (myWidget->objectName() == "boxUsb3") {
                pWin_cdlgtalk->doBoxPort("boxUsb3");
            }
            else if (myWidget->objectName() == "boxLan") {
                pWin_cdlgtalk->doBoxPort("boxLan");
           }
            else if (myWidget->objectName().contains("btnAmp")) {
               pWin_cdlgtalk->doVideoAmpClick(myWidget->objectName());
           }
            else if (myWidget->objectName().contains("btnBall")) {
               pWin_cdlgtalk->doBallheadCameraClick(myWidget->objectName());
           }
            else if (myWidget->objectName().contains("btnPtz")) {
               pWin_cdlgtalk->doControlPtzClick(myWidget->objectName());
           }
            else if (myWidget->objectName().contains("btnChair")) {
               pWin_cdlgtalk->doChairmanClick(myWidget->objectName());
           }
            else {
               pWin_cdlgtalk->Infrared_ok(myWidget->objectName());
           }
            
          
        }

        //主窗口
        if (pWin->objectName() == "CMainFrame") {
            CMainFrame* pWin_main = (CMainFrame*)QWidget::find((WId)hCurr);
            if (pWin_main == mynull) {
                return;
            }
            if (myWidget->objectName() == "btnMeeting") {
                pWin_main->on_btnMeeting_clicked(myWidget->objectName());
            }
            else if (myWidget->objectName() == "btnMeeting2") {
                pWin_main->on_btnMeeting2_clicked(myWidget->objectName());
            }
            else if (myWidget->objectName() == "btnRet") {
                pWin_main->on_closePortSetting_slots();
            }

            else if (myWidget->objectName() == "boxVga") {
                pWin_main->doBoxPort("boxVga");
            }
            else if (myWidget->objectName() == "boxHdmi") {
                pWin_main->doBoxPort("boxHdmi");
            }
            else if (myWidget->objectName() == "boxDvi") {
                pWin_main->doBoxPort("boxDvi");
            }
            else if (myWidget->objectName() == "boxUsb1") {
                pWin_main->doBoxPort("boxUsb1");
            }
            else if (myWidget->objectName() == "boxUsb2") {
                pWin_main->doBoxPort("boxUsb2");
            }
            else if (myWidget->objectName() == "boxAudioOut") {
                pWin_main->doBoxPort("boxAudioOut");
            }
            else if (myWidget->objectName() == "boxUsb3") {
                pWin_main->doBoxPort("boxUsb3");
            }
            else if (myWidget->objectName() == "boxLan") {
                pWin_main->doBoxPort("boxLan");
            }

            else if (myWidget->objectName().contains("btnP2p")) {
                pWin_main->doBtnClick(myWidget->objectName());
            }

            else if (myWidget->objectName() == "btn_consent") {
                pWin_main->doP2pMsg(myWidget->objectName());
            }
            else if (myWidget->objectName() == "btn_repulse") {
                pWin_main->doP2pMsg(myWidget->objectName());
            }

            //其他设置窗口
            else if (myWidget->objectName().contains("outAudioDeviceBtn")) {
                pWin_main->doOtherMsg(myWidget->objectName());
            }
            else if (myWidget->objectName().contains("inAudioDeviceBtn")) {
                pWin_main->doOtherMsg(myWidget->objectName());
            }
            else if (myWidget->objectName() == "restNvrBtn") {
                pWin_main->doOtherMsg(myWidget->objectName());
            }
            else if (myWidget->objectName() == "otherBtnRet") {
                pWin_main->on_closeOther_slots();
            }

            else {
                pWin_main->Infrared_ok(myWidget->objectName());
            }
        }
    }
    //左箭头
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_LEFT) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            //视频窗口
            if (pWin->objectName() == "CDlgTalk_qt") {
                CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
                if (pWin_cdlgtalk == mynull) {
                    return;
                }
                pWin_cdlgtalk->Infrared_input_left_right("", true);
            }
            pMainFrame->_instruct = nullptr; //清空本次指令
            return;
        }
        //初始化页面表单
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input_left_right(myWidget->objectName(), true);
        }
        //用户登录页面表单
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input_left_right(myWidget->objectName(), true);
        }
        //主界面
        if (pWin->objectName() == "CMainFrame") {
            CMainFrame* pWin_main = (CMainFrame*)QWidget::find((WId)hCurr);
            if (pWin_main == mynull) {
                return;
            }

            pWin_main->Infrared_input_left_right(myWidget->objectName(), true);
        }
        //视频窗口
        if (pWin->objectName() == "CDlgTalk_qt") {
            CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
            if (pWin_cdlgtalk == mynull) {
                return;
            }
            pWin_cdlgtalk->Infrared_input_left_right(myWidget->objectName(), true);
        }
    }
    //右箭头
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_RIGHT) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {

            //视频窗口
            if (pWin->objectName() == "CDlgTalk_qt") {
                CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
                if (pWin_cdlgtalk == mynull) {
                    return;
                }
                pWin_cdlgtalk->Infrared_input_left_right("", false);
            }
            pMainFrame->_instruct = nullptr; //清空本次指令

            return;
        }
        //初始化页面表单
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input_left_right(myWidget->objectName(), false);
        }
        //用户登录页面表单
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input_left_right(myWidget->objectName(), false);
        }
        //主界面
        if (pWin->objectName() == "CMainFrame") {
            CMainFrame* pWin_main = (CMainFrame*)QWidget::find((WId)hCurr);
            if (pWin_main == mynull) {
                return;
            }
            
            pWin_main->Infrared_input_left_right(myWidget->objectName() , false);
        }

        //视频窗口
        if (pWin->objectName() == "CDlgTalk_qt") {
            CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
            if (pWin_cdlgtalk == mynull) {
                return;
            }
            pWin_cdlgtalk->Infrared_input_left_right(myWidget->objectName(), false);
        }


    }
    //退格键
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_BACKSPACE) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input_backspace(myWidget->objectName());
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input_backspace(myWidget->objectName());
        }
    }

    //1键
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_ONE) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        QString value = "1";
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }

    }
    //2键
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_TWO) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        QString value = "2";
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }

    }
    //3键
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_THREE) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        QString value = "3";
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }
    //4键
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_FOUR) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        QString value = "4";
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }
    //5键
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_FIVE) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        QString value = "5";
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }
    //6键
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_SIX) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        QString value = "6";
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }
    //7键
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_SEVEN) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        QString value = "7";
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }
    //8键
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_EIGHT) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        QString value = "8";
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }
    //9键
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_NINE) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        QString value = "9";
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }
    //0键
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_ZERO) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        QString value = "0";
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }    
    }
    //点键
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_DOT) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = ".";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = ".";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }

    //大小写切换
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_CAPSLOCK_CUT) {
        
        if (pMainFrame->_instruct_is_capsLock) {
            pMainFrame->_instruct_is_capsLock = false;
        }
        else {
            pMainFrame->_instruct_is_capsLock = true;
        }
    }
    //下划线
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_ZHONGHUAXIAN) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "_";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "_";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }
    //星号 *
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_XINGHAO) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "*";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "*";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }

    //#号
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_JINGHAO) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "#";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "#";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }
    //?号
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_WENHAO) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "?";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "?";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }
    //@号
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_AHAO) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "@";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "@";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }
    //,号
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_DOUHAO) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = ",";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = ",";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }
    //%号
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_BAIFENHAO) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "%";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "%";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }
    //+号
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_JIAHAO) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "+";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "+";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }
    //减号
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_JIANHAO) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "-";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "-";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }

    //冒号 :
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_MAOHAO) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = ":";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = ":";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }

    //斜杠 \ 
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_XIEGANG) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "\\";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "\\";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }
    
    //反斜杠 /
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_FANXIEGANG) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "/";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "/";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }
    //空格
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_KONGGE) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = " ";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = " ";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }
    //引号 '
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_YINHAO) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "'";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            QString value = "'";
            pWin_device->Infrared_input(myWidget->objectName(), value);
        }
    }

    //发言 
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_FAYAN) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        
        //
        if (pWin->objectName() == "CDlgTalk_qt") {
            //视频窗口
            CDlgTalk_qt* pWin_device = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->on_SpeakBtn_click(true,true);

        }

    }

    //停止发言
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_TUIHUI) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }

       

        //
        if (pWin->objectName() == "CDlgTalk_qt") {
            //视频窗口
            CDlgTalk_qt* pWin_device = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->on_SpeakBtn_click(true , false);

        }
        

    }
    //Tab
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_TAB) {
        QString value = u8"遥控器暂不支持【Tab】按键操作";
        //
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        //用户登录
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CQmcLogin") {
            //双向认证
            CQmcLogin* pWin_device = (CQmcLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CDlgTalk_qt") {
            //视频窗口
            CDlgTalk_qt* pWin_device = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            //先注释掉  海光不兼容
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CMainFrame") {
            //首页
            CMainFrame* pWin_device = (CMainFrame*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
    }

    //中英文切换
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_EN_CN) {
        QString value = u8"遥控器暂不支持【中/英】按键操作";
        //
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        //用户登录
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CQmcLogin") {
            //双向认证
            CQmcLogin* pWin_device = (CQmcLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CDlgTalk_qt") {
            //视频窗口
            CDlgTalk_qt* pWin_device = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            //先注释掉  海光不兼容
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CMainFrame") {
            //首页
            CMainFrame* pWin_device = (CMainFrame*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        } 

    }
    
    //摄像头
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_SXT) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }


         //
        if (pWin->objectName() == "CDlgTalk_qt") {
            //视频窗口
            CDlgTalk_qt* pWin_device = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->on_VideoBtn_click(true);

        }


    }

    //麦克风
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_MKF) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //
        if (pWin->objectName() == "CDlgTalk_qt") {
            //视频窗口
            CDlgTalk_qt* pWin_device = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->on_AudioBtn_click(true);

        }
    }

    //辅流
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_FL) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //
        if (pWin->objectName() == "CDlgTalk_qt") {
            //视频窗口
            CDlgTalk_qt* pWin_device = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->slot_device_screen(true);

        }
    }

    //录制
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_LZ) {
        QString value = u8"遥控器暂不支持【录制】按键操作";
        //
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        //用户登录
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CQmcLogin") {
            //双向认证
            CQmcLogin* pWin_device = (CQmcLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CDlgTalk_qt") {
            //视频窗口
            CDlgTalk_qt* pWin_device = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            //先注释掉  海光不兼容
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CMainFrame") {
            //首页
            CMainFrame* pWin_device = (CMainFrame*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
    }

    //电源
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_POWER) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        // todo 

    }

    //喇叭静音
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_LABA_WU) {

        QString value = u8"遥控器暂不支持【喇叭静音】按键操作";
        //
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        //用户登录
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CQmcLogin") {
            //双向认证
            CQmcLogin* pWin_device = (CQmcLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CDlgTalk_qt") {
            //视频窗口
            CDlgTalk_qt* pWin_device = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            //先注释掉  海光不兼容
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CMainFrame") {
            //首页
            CMainFrame* pWin_device = (CMainFrame*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
   
    }

    //喇叭加
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_LABA_JIA) {
           QString value = u8"遥控器暂不支持【喇叭音量增加】按键操作";
        //
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        //用户登录
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CQmcLogin") {
            //双向认证
            CQmcLogin* pWin_device = (CQmcLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CDlgTalk_qt") {
            //视频窗口
            CDlgTalk_qt* pWin_device = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            //先注释掉  海光不兼容
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CMainFrame") {
            //首页
            CMainFrame* pWin_device = (CMainFrame*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
    }

    //喇叭减
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_LABA_JIAN) {
          QString value = u8"遥控器暂不支持【喇叭音量减小】按键操作";
        //
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        //初始化页面表单
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        //用户登录
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CQmcLogin") {
            //双向认证
            CQmcLogin* pWin_device = (CQmcLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CDlgTalk_qt") {
            //视频窗口
            CDlgTalk_qt* pWin_device = (CDlgTalk_qt*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            //先注释掉  海光不兼容
            pWin_device->showHint(value);
        }
        else if (pWin->objectName() == "CMainFrame") {
            //首页
            CMainFrame* pWin_device = (CMainFrame*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->showHint(value);
        }
    }

    //字母输入  a b c
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_ABC) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        qint64 tmp_time =  QDateTime::currentMSecsSinceEpoch();
        

        if (pMainFrame->_instruct_one_letter_count >= 3) {
            pMainFrame->_instruct_one_letter_count = 0;
        }

        if ((tmp_time - pMainFrame->_instruct_one_time) < pMainFrame->_instruct_interval_time)
        {
            pMainFrame->_instruct_one_letter_count += 1;
        }
        else {
            //
            pMainFrame->_instruct_one_letter_count = 0;
        }

        QString value = mynull;
        bool is_replace = false;
        if (pMainFrame->_instruct_one_letter_count == 1 || pMainFrame->_instruct_one_letter_count == 0) {
            if (pMainFrame->_instruct_one_letter_count == 1) {
                is_replace = true;
            }
            else {
                pMainFrame->_instruct_one_letter_count += 1;
            }
             if (pMainFrame->_instruct_is_capsLock) {
                 value = "A";
            }
            else {
                 value = "a";
            }
        }else if(pMainFrame->_instruct_one_letter_count == 2)
        {
            is_replace = true;
            if (pMainFrame->_instruct_is_capsLock) {
                value = "B";
               
            }
            else {
                value = "b";
            }
        }else if(pMainFrame->_instruct_one_letter_count == 3)
        {
            is_replace = true;
            if (pMainFrame->_instruct_is_capsLock) {
                value = "C";
            }
            else {
                value = "c";
            }
        }
       

        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input_leeter(myWidget->objectName(), value , is_replace);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input_leeter(myWidget->objectName(), value, is_replace);
        }

        pMainFrame->_instruct_one_time = QDateTime::currentMSecsSinceEpoch();//本次记录时间
    }
    //字母输入  d e f
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_DEF) {
    QWidget* myWidget = QApplication::focusWidget();
    if (!myWidget) {
        return;
    }
    qint64 tmp_time = QDateTime::currentMSecsSinceEpoch();

    if (pMainFrame->_instruct_two_letter_count >= 3) {
        pMainFrame->_instruct_two_letter_count = 0;
    }

    if ((tmp_time - pMainFrame->_instruct_two_time) < pMainFrame->_instruct_interval_time)
    {
        pMainFrame->_instruct_two_letter_count += 1;
    }
    else {
        //
        pMainFrame->_instruct_two_letter_count = 0;
    }

    QString value = mynull;
    bool is_replace = false;
    if (pMainFrame->_instruct_two_letter_count == 1 || pMainFrame->_instruct_two_letter_count == 0) {
        if (pMainFrame->_instruct_two_letter_count == 1) {
            is_replace = true;
        }
        else {
            pMainFrame->_instruct_two_letter_count += 1;
        }
        if (pMainFrame->_instruct_is_capsLock) {
            value = "D";
        }
        else {
            value = "d";
        }
    }
    else if (pMainFrame->_instruct_two_letter_count == 2)
    {
        is_replace = true;
        if (pMainFrame->_instruct_is_capsLock) {
            value = "E";

        }
        else {
            value = "e";
        }
    }
    else if (pMainFrame->_instruct_two_letter_count == 3)
    {
        is_replace = true;
        if (pMainFrame->_instruct_is_capsLock) {
            value = "F";
        }
        else {
            value = "f";
        }
    }

    //初始化页面表单输入
    if (pWin->objectName() == "CDeviceBindingClass") {
        CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
        if (pWin_device == mynull) {
            return;
        }
        pWin_device->Infrared_input_leeter(myWidget->objectName(), value, is_replace);
    }
    //用户登录输入
    if (pWin->objectName() == "CUserLoginClass") {
        CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
        if (pWin_device == mynull) {
            return;
        }
        pWin_device->Infrared_input_leeter(myWidget->objectName(), value , is_replace);
    }

    pMainFrame->_instruct_two_time = QDateTime::currentMSecsSinceEpoch();//本次记录时间
    }
    //字母输入  g h i
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_GHI) {
    QWidget* myWidget = QApplication::focusWidget();
    if (!myWidget) {
        return;
    }
    qint64 tmp_time = QDateTime::currentMSecsSinceEpoch();

    if (pMainFrame->_instruct_three_letter_count >= 3) {
        pMainFrame->_instruct_three_letter_count = 0;
    }

    if ((tmp_time - pMainFrame->_instruct_three_time) < pMainFrame->_instruct_interval_time)
    {
        pMainFrame->_instruct_three_letter_count += 1;
    }
    else {
        //
        pMainFrame->_instruct_three_letter_count = 0;
    }

    QString value = mynull;
    bool is_replace = false;
    if (pMainFrame->_instruct_three_letter_count == 1 || pMainFrame->_instruct_three_letter_count == 0) {
        if (pMainFrame->_instruct_three_letter_count == 1) {
            is_replace = true;
        }
        else {
            pMainFrame->_instruct_three_letter_count += 1;
        }
        if (pMainFrame->_instruct_is_capsLock) {
            value = "G";
        }
        else {
            value = "g";
        }
    }
    else if (pMainFrame->_instruct_three_letter_count == 2)
    {
        is_replace = true;
        if (pMainFrame->_instruct_is_capsLock) {
            value = "H";

        }
        else {
            value = "h";
        }
    }
    else if (pMainFrame->_instruct_three_letter_count == 3)
    {
        is_replace = true;
        if (pMainFrame->_instruct_is_capsLock) {
            value = "I";
        }
        else {
            value = "i";
        }
    }

    //初始化页面表单输入
    if (pWin->objectName() == "CDeviceBindingClass") {
        CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
        if (pWin_device == mynull) {
            return;
        }
        pWin_device->Infrared_input_leeter(myWidget->objectName(), value, is_replace);
    }
    //用户登录输入
    if (pWin->objectName() == "CUserLoginClass") {
        CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
        if (pWin_device == mynull) {
            return;
        }
        pWin_device->Infrared_input_leeter(myWidget->objectName(), value , is_replace);
    }

    pMainFrame->_instruct_three_time = QDateTime::currentMSecsSinceEpoch();//本次记录时间
    }
    //字母输入  j k l
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_JKL) {
    QWidget* myWidget = QApplication::focusWidget();
    if (!myWidget) {
        return;
    }
    qint64 tmp_time = QDateTime::currentMSecsSinceEpoch();

    if (pMainFrame->_instruct_four_letter_count >= 3) {
        pMainFrame->_instruct_four_letter_count = 0;
    }

    if ((tmp_time - pMainFrame->_instruct_four_time) < pMainFrame->_instruct_interval_time)
    {
        pMainFrame->_instruct_four_letter_count += 1;
    }
    else {
        //
        pMainFrame->_instruct_four_letter_count = 0;
    }

    QString value = mynull;
    bool is_replace = false;
    if (pMainFrame->_instruct_four_letter_count == 1 || pMainFrame->_instruct_four_letter_count == 0) {
        if (pMainFrame->_instruct_four_letter_count == 1) {
            is_replace = true;
        }
        else {
            pMainFrame->_instruct_four_letter_count += 1;
        }
        if (pMainFrame->_instruct_is_capsLock) {
            value = "J";
        }
        else {
            value = "j";
        }
    }
    else if (pMainFrame->_instruct_four_letter_count == 2)
    {
        is_replace = true;
        if (pMainFrame->_instruct_is_capsLock) {
            value = "K";

        }
        else {
            value = "k";
        }
    }
    else if (pMainFrame->_instruct_four_letter_count == 3)
    {
        is_replace = true;
        if (pMainFrame->_instruct_is_capsLock) {
            value = "L";
        }
        else {
            value = "l";
        }
    }

    //初始化页面表单输入
    if (pWin->objectName() == "CDeviceBindingClass") {
        CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
        if (pWin_device == mynull) {
            return;
        }
        pWin_device->Infrared_input_leeter(myWidget->objectName(), value, is_replace);
    }
    //用户登录输入
    if (pWin->objectName() == "CUserLoginClass") {
        CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
        if (pWin_device == mynull) {
            return;
        }
        pWin_device->Infrared_input_leeter(myWidget->objectName(), value , is_replace);
    }

    pMainFrame->_instruct_four_time = QDateTime::currentMSecsSinceEpoch();//本次记录时间
    }
    //字母输入  m n o
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_MNO) {
    QWidget* myWidget = QApplication::focusWidget();
    if (!myWidget) {
        return;
    }
    qint64 tmp_time = QDateTime::currentMSecsSinceEpoch();

    if (pMainFrame->_instruct_five_letter_count >= 3) {
        pMainFrame->_instruct_five_letter_count = 0;
    }

    if ((tmp_time - pMainFrame->_instruct_five_time) < pMainFrame->_instruct_interval_time)
    {
        pMainFrame->_instruct_five_letter_count += 1;
    }
    else {
        //
        pMainFrame->_instruct_five_letter_count = 0;
    }

    QString value = mynull;
    bool is_replace = false;
    if (pMainFrame->_instruct_five_letter_count == 1 || pMainFrame->_instruct_five_letter_count == 0) {
        if (pMainFrame->_instruct_five_letter_count == 1) {
            is_replace = true;
        }
        else {
            pMainFrame->_instruct_five_letter_count += 1;
        }
        if (pMainFrame->_instruct_is_capsLock) {
            value = "M";
        }
        else {
            value = "m";
        }
    }
    else if (pMainFrame->_instruct_five_letter_count == 2)
    {
        is_replace = true;
        if (pMainFrame->_instruct_is_capsLock) {
            value = "N";

        }
        else {
            value = "n";
        }
    }
    else if (pMainFrame->_instruct_five_letter_count == 3)
    {
        is_replace = true;
        if (pMainFrame->_instruct_is_capsLock) {
            value = "O";
        }
        else {
            value = "o";
        }
    }

    //初始化页面表单输入
    if (pWin->objectName() == "CDeviceBindingClass") {
        CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
        if (pWin_device == mynull) {
            return;
        }
        pWin_device->Infrared_input_leeter(myWidget->objectName(), value, is_replace);
    }
    //用户登录输入
    if (pWin->objectName() == "CUserLoginClass") {
        CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
        if (pWin_device == mynull) {
            return;
        }
        pWin_device->Infrared_input_leeter(myWidget->objectName(), value ,is_replace);
    }

    pMainFrame->_instruct_five_time = QDateTime::currentMSecsSinceEpoch();//本次记录时间
    }
    //字母输入  p q r s
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_PQRS) {
    QWidget* myWidget = QApplication::focusWidget();
    if (!myWidget) {
        return;
    }
    qint64 tmp_time = QDateTime::currentMSecsSinceEpoch();

    if (pMainFrame->_instruct_sex_letter_count >= 4) {
        pMainFrame->_instruct_sex_letter_count = 0;
    }

    if ((tmp_time - pMainFrame->_instruct_six_time) < pMainFrame->_instruct_interval_time)
    {
        pMainFrame->_instruct_sex_letter_count += 1;
    }
    else {
        //
        pMainFrame->_instruct_sex_letter_count = 0;
    }

    QString value = mynull;
    bool is_replace = false;
    if (pMainFrame->_instruct_sex_letter_count == 1 || pMainFrame->_instruct_sex_letter_count == 0) {
        if (pMainFrame->_instruct_sex_letter_count == 1) {
            is_replace = true;
        }
        else {
            pMainFrame->_instruct_sex_letter_count += 1;
        }
        if (pMainFrame->_instruct_is_capsLock) {
            value = "P";
        }
        else {
            value = "p";
        }
    }
    else if (pMainFrame->_instruct_sex_letter_count == 2)
    {
        is_replace = true;
        if (pMainFrame->_instruct_is_capsLock) {
            value = "Q";

        }
        else {
            value = "q";
        }
    }
    else if (pMainFrame->_instruct_sex_letter_count == 3)
    {
        is_replace = true;
        if (pMainFrame->_instruct_is_capsLock) {
            value = "R";
        }
        else {
            value = "r";
        }
    }
    else if (pMainFrame->_instruct_sex_letter_count == 4)
    {
        is_replace = true;
        if (pMainFrame->_instruct_is_capsLock) {
            value = "S";
        }
        else {
            value = "s";
        }
    }

    //初始化页面表单输入
    if (pWin->objectName() == "CDeviceBindingClass") {
        CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
        if (pWin_device == mynull) {
            return;
        }
        pWin_device->Infrared_input_leeter(myWidget->objectName(), value, is_replace);
    }
    //用户登录输入
    if (pWin->objectName() == "CUserLoginClass") {
        CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
        if (pWin_device == mynull) {
            return;
        }
        pWin_device->Infrared_input_leeter(myWidget->objectName(), value , is_replace);
    }

    pMainFrame->_instruct_six_time = QDateTime::currentMSecsSinceEpoch();//本次记录时间
    }
    //字母输入  t u v
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_TUV) {
    QWidget* myWidget = QApplication::focusWidget();
    if (!myWidget) {
        return;
    }
    qint64 tmp_time = QDateTime::currentMSecsSinceEpoch();

    if (pMainFrame->_instruct_seven_letter_count >= 3) {
        pMainFrame->_instruct_seven_letter_count = 0;
    }

    if ((tmp_time - pMainFrame->_instruct_seven_time) < pMainFrame->_instruct_interval_time)
    {
        pMainFrame->_instruct_seven_letter_count += 1;
    }
    else {
        //
        pMainFrame->_instruct_seven_letter_count = 0;
    }

    QString value = mynull;
    bool is_replace = false;
    if (pMainFrame->_instruct_seven_letter_count == 1 || pMainFrame->_instruct_seven_letter_count == 0) {
        if (pMainFrame->_instruct_seven_letter_count == 1) {
            is_replace = true;
        }
        else {
            pMainFrame->_instruct_seven_letter_count += 1;
        }
        if (pMainFrame->_instruct_is_capsLock) {
            value = "T";
        }
        else {
            value = "t";
        }
    }
    else if (pMainFrame->_instruct_seven_letter_count == 2)
    {
        is_replace = true;
        if (pMainFrame->_instruct_is_capsLock) {
            value = "U";

        }
        else {
            value = "u";
        }
    }
    else if (pMainFrame->_instruct_seven_letter_count == 3)
    {
        is_replace = true;
        if (pMainFrame->_instruct_is_capsLock) {
            value = "V";
        }
        else {
            value = "v";
        }
    }

    //初始化页面表单输入
    if (pWin->objectName() == "CDeviceBindingClass") {
        CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
        if (pWin_device == mynull) {
            return;
        }
        pWin_device->Infrared_input_leeter(myWidget->objectName(), value, is_replace);
    }
    //用户登录输入
    if (pWin->objectName() == "CUserLoginClass") {
        CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
        if (pWin_device == mynull) {
            return;
        }
        pWin_device->Infrared_input_leeter(myWidget->objectName(), value , is_replace);
    }

    pMainFrame->_instruct_seven_time = QDateTime::currentMSecsSinceEpoch();//本次记录时间
    }
    //字母输入  wxyz
    else if (pMainFrame->_instruct == DEFAULT_INFRARED_INSTRUCT_CMD_WXYZ) {
        QWidget* myWidget = QApplication::focusWidget();
        if (!myWidget) {
            return;
        }
        qint64 tmp_time = QDateTime::currentMSecsSinceEpoch();

        if (pMainFrame->_instruct_eight_letter_count >= 4) {
            pMainFrame->_instruct_eight_letter_count = 0;
        }

        if ((tmp_time - pMainFrame->_instruct_eight_time) < pMainFrame->_instruct_interval_time)
        {
            pMainFrame->_instruct_eight_letter_count += 1;
        }
        else {
            //
            pMainFrame->_instruct_eight_letter_count = 0;
        }

        QString value = mynull;
        bool is_replace = false;
        if (pMainFrame->_instruct_eight_letter_count == 1 || pMainFrame->_instruct_eight_letter_count == 0) {
            if (pMainFrame->_instruct_eight_letter_count == 1) {
                is_replace = true;
            }
            else {
                pMainFrame->_instruct_eight_letter_count += 1;
            }
            if (pMainFrame->_instruct_is_capsLock) {
                value = "W";
            }
            else {
                value = "w";
            }
        }
        else if (pMainFrame->_instruct_eight_letter_count == 2)
        {
            is_replace = true;
            if (pMainFrame->_instruct_is_capsLock) {
                value = "X";

            }
            else {
                value = "x";
            }
        }
        else if (pMainFrame->_instruct_eight_letter_count == 3)
        {
            is_replace = true;
            if (pMainFrame->_instruct_is_capsLock) {
                value = "Y";
            }
            else {
                value = "y";
            }
        }
        else if (pMainFrame->_instruct_eight_letter_count == 4)
        {
            is_replace = true;
            if (pMainFrame->_instruct_is_capsLock) {
                value = "Z";
            }
            else {
                value = "z";
            }
        }

        //初始化页面表单输入
        if (pWin->objectName() == "CDeviceBindingClass") {
            CDeviceBinding* pWin_device = (CDeviceBinding*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input_leeter(myWidget->objectName(), value, is_replace);
        }
        //用户登录输入
        if (pWin->objectName() == "CUserLoginClass") {
            CUserLogin* pWin_device = (CUserLogin*)QWidget::find((WId)hCurr);
            if (pWin_device == mynull) {
                return;
            }
            pWin_device->Infrared_input_leeter(myWidget->objectName(), value , is_replace);
        }

        pMainFrame->_instruct_eight_time = QDateTime::currentMSecsSinceEpoch();//本次记录时间
    }
  

    pMainFrame->_instruct = nullptr; //清空本次指令
    

    return;
}


//
void mainWnd_infraredMenu(CMainFrame  *  pMainFrame,  QString s_status)
{
    HWND  hWndWork = gethWndWork();
    if (!hWndWork) return;

    //
    QWidget* pWidget = QWidget::find((WId)hWndWork);
    if (!pWidget) return;
    qDebug() << pWidget->objectName();

    //
    showInfo_open0(0, 0, _T("mainWnd_infraredMenu 2204"));

    //
    if (pWidget->objectName() == "CDlgTalk_qt") {

        CDlgTalk_qt* pTalk = (CDlgTalk_qt*)pWidget;
        //
        DLG_TALK_var* pm_var = pTalk->get_pm_var();
        //
        int  ii = pm_var->iTalkerSubType;
        //
        pTalk->on_infraredMenu();
    }
    else if (pWidget->objectName() == "CUserLoginClass") {
        emit pMainFrame->to_sendUserLoginWork_signal();
    }
    else if(pWidget->objectName() == "CMainFrame") {
      //  emit pMainFrame->to_sendMainFrameWork_signal();
        pMainFrame->on_infraredMenu();
    }
    else if(pWidget->objectName() == "CDeviceBindingClass") {
        emit pMainFrame->to_sendDeviceBindWork_signal();
    }
    else if (pWidget->objectName() == "CQmcLogin") {
        //
        emit  pMainFrame->to_sendQmcLoginWork_signal();
    }
    //
    return;
}


//
void mainWnd_infraredMenu_quit(CMainFrame*pMainFrame)
{
    HWND  hWndWork = gethWndWork();
    if (!hWndWork) return;

    //
    QWidget* pWidget = QWidget::find((WId)hWndWork);
    if (!pWidget) return;
    qDebug() << pWidget->objectName();

    if (pWidget->objectName() == "CDlgTalk_qt") {
        CDlgTalk_qt* pTalk = (CDlgTalk_qt*)pWidget;
        //
        DLG_TALK_var* pm_var = pTalk->get_pm_var();
        //
        int  ii = pm_var->iTalkerSubType;
        //
        pTalk->infraredMenu_quit();
        //
        pTalk->on_closePortSetting_slots();
        //
        pTalk->on_closeVideoAmpLifier_slots();
        //
        pTalk->on_closeChairman_slots();
        //
        pTalk->on_closeBallheadCamera_slots();

    }
    else if (pWidget->objectName() == "CUserLoginClass") {
        
        emit pMainFrame->to_sendUserLoginWork_quit_signal();

    }
    else if (pWidget->objectName() == "CMainFrame") {
        pMainFrame->infraredMenu_quit();

        pMainFrame->on_closeOther_slots();

        pMainFrame->on_closePortSetting_slots();

        pMainFrame->on_P2pDlg_close();

    }
    else if (pWidget->objectName() == "CDeviceBindingClass") {
        emit pMainFrame->to_sendDeviceBindWork_quit_signal();
        //
        emit pMainFrame->to_sendDevicePort_quit_signal();
        //
        emit pMainFrame->to_sendNvr_quit_signal();
        emit pMainFrame->to_sendWifi_quit_signal();
        emit pMainFrame->to_sendShare_quit_signal();
    }
    else if (pWidget->objectName() == "CQmcLogin") {
        //
        emit  pMainFrame->to_sendQmcLoginWork_quit_signal();
    }

    return;
 
}

