
//#define  __noDbg__
#define  __noDbg_new__

#include "ui_CDlgTalk_qt.h"
#include "CDlgTalk_qt.h"
#include <QMenu>
#include "WinBasic.h"
#include "funcsForIsCliHelp.h"
#include "ctxQmc_qt.h"
#include "isCmdConst.h"
#include <QTextEdit>
#include <QTextBlock>
#include <QFileDialog>
#include <QDebug>

#include "MessageSignalCenter.h"
#include <QMessageBox>
#include "WinTalkList.h"
#include "DBManager.h"
#include "WinTitle.h"
#include "QualitySelSetDialog.h"
#include "CDlgTalkMoreMenu.h"
#include <qyCusResTemp.h>
#include "CloudDiskWidget.h"
#include "DeviceSelectDialog.h"
#include "ScreenDeviceSelect.h"
#include "CDlgTalk_grp_members.h"
#include <CDlgTalk_speaker_list.h>
#include <WinRuleSet.h>
#include "WinMsgQTextEdit.h"
#include <CMainFrame.h>
#include<QtConcurrent/QtConcurrent>
#include <CDlgTalk_invite_hint.h>

#include	"smCommProc.h"
#include <tmpRegFunc_open.h>

//
#include    "oldConfs.h"

#include "CDlgControlPtz.h"
#include "CDlgBallheadCamera.h"


#include "CDlgObjs_ts_qt.h"
#include "CDlgRemoteVideo.h"

#include "CDlgRemoteVideoMix.h"

#include "mLogger.h"

#include <QMessageBox>
#include <ptzFunc.h>
//
namespace {
    const int kMouseRegionLeft = 10;
    const int kMouseRegionTop = 10;
    const int kMouseRegionButtom = 10;
    const int kMouseRegionRight = 10;
    //标题栏的长度
    const static int pos_min_x = 0;
    const static int pos_max_x = 0;
    const static int pos_min_y = 0;
    const static int pos_max_y = 0;

    const static int DEFAULT_VIDEO_WIDTH = 625;//484;// 450;
    const static int DEFAULT_VIDEO_HEIGHT = 900;

    const static int DEFAULT_VIDEO_WIDTH_768 = 490;//450;// 450;
    const static int DEFAULT_VIDEO_HEIGHT_768 = 580;
}
//
CDlgTalk_qt::CDlgTalk_qt(QWidget* parent)
    : WinBasic(false, parent)
    , ui(new Ui::CDlgTalk_qt)
    , m_event(
        std::make_unique<QMouseEvent>(QEvent::MouseButtonPress, QPoint(100, 100), QPoint(50, 50), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier))
{
    ui->setupUi(this);
    ////以下为测试
    //QString s = "你好呀！&#x23333;wwwerrrrr";
    //QString t = separateEmotion(s);
    //
    ui->widgetMsgShow->m_msgHtmlObj->m_hTalk = (HWND)this->winId();
    //
    this->setMouseTracking(true);	//打开鼠标追踪
   // setAttribute(Qt::WA_TransparentForMouseEvents, true);
   // ui->widgetMsgArea->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    initControl();
    ui->widgetVideoShow->installEventFilter(this);
    ui->peerDesc->installEventFilter(this);
    ui->tableWidget->installEventFilter(this);
    bottom_bar_hide_timer_ = new QTimer(this);
    bottom_bar_hide_timer_->setInterval(5000);
    bottom_bar_hide_timer_->setSingleShot(true);
    connect(bottom_bar_hide_timer_, &QTimer::timeout, [this]()
    {
        ui->bottomMenu->setVisible(false);
    });
    
    bottom_bar_hide_timer_->start();


    video_ing_timer_ = new QTimer(this);
    video_ing_timer_->setInterval(3000);
    connect(video_ing_timer_, &QTimer::timeout, [this]()
        {
            QString currentId = currentUser.idinfo;

            //检测是否有正在运行的任务
            ui->iTaskId_lab->setText("");
            ui->video_ing_widget->hide();
            OldConfs  oldConfs = { 0 };
            if (!findOldRecvdConfsActive(&oldConfs))
            {
                for (int i = 0; i < oldConfs.usCnt; i++) {
                    OldConfMem* pMem = &oldConfs.mems[i];
                    if (pMem->idInfo_peer.ui64Id == currentId.toInt())
                    {
                        ui->video_ing_widget->show();
                        ui->iTaskId_lab->setText(QString::number(pMem->iTaskId));
                        break;
                    }

                }
            }
        });

    video_ing_timer_->start();
  

     
    //
    HWND  hDlgTalk = (HWND)this->winId();
    //
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
    //
    this->iIndex_talkerInfo = -1;
    //
    int  iTalkerDataType = CONST_objVarDataType_dlgTalk;
    this->iIndex_talkerInfo = newQmcObjVarInfoIndex(pProcInfo, iTalkerDataType, 0);
    if (this->iIndex_talkerInfo < 0)  return;
    //
    DLG_TALK_var* pm_var = this->get_pm_var();
    if (!pm_var)  return;
    DLG_TALK_var& m_var = *pm_var;

    //
    m_var.pQyMc = pQyMc;

    //
    m_var.iIndex_talkerInfo = this->iIndex_talkerInfo;

    //
    //  m_var.m_hParent = pParent  ?  pParent->m_hWnd  :  NULL;
    m_var.m_hParent = (HWND)(parent ? parent->winId() : NULL);

    //  2013/03/19
    m_var.bIncludeACap = pProcInfo->cfg.policy.audio.uiRecordType == CONST_recordType_directX;

    //
    m_var.loopCtrl_timer = 9;

    //
#if 0
    QWidget::paintEngine();
    setAttribute(Qt::WA_NativeWindow);
    setAttribute(Qt::WA_PaintOnScreen);
    //setRenderHint(QPainter::Antialiasing);
#endif

    //
    //startTimer(100);
    this->setAcceptDrops(true);
     
    m_clickTimer = new QTimer();
    connect(m_clickTimer, &QTimer::timeout, this, &CDlgTalk_qt::onClickTimeout);
    m_clickTimer->setSingleShot(true);

  
    connect(this, &CDlgTalk_qt::clicked, this, &CDlgTalk_qt::onClicked);
    connect(this, &CDlgTalk_qt::doubleClicked, this, &CDlgTalk_qt::onDoubleClicked);

#ifdef  __DEBUG__
    traceLog((TCHAR*)_T("CDlgTalk_qt::CDlgTalk_qt() called"));
#endif 
}

void CDlgTalk_qt::onClickTimeout() {

    //
    //qDebug() << "onClickTimeout";

	//emit clicked(event);

    if (!m_dbClick) {
        onClicked(m_event.get());
    }
}

CDlgTalk_qt::~CDlgTalk_qt()
{
    delete ui;

    if (bottom_bar_hide_timer_) {
        delete bottom_bar_hide_timer_;
        bottom_bar_hide_timer_ = nullptr;
    }
    
    if (video_ing_timer_) {
        delete video_ing_timer_;
        video_ing_timer_ = nullptr;
    }

    if (m_pRemoteVideo) {
        delete m_pRemoteVideo;
        m_pRemoteVideo = nullptr;
    }

    if (m_pRemoteVideoMix) {
        delete m_pRemoteVideoMix;
        m_pRemoteVideoMix = nullptr;
    }

    //
    if (scroll_bar_update_timer_) {
        delete scroll_bar_update_timer_;
        scroll_bar_update_timer_ = nullptr;
    }

       
	if (m_pControlPtz)
	{
		m_pControlPtz->close();
		delete m_pControlPtz;
		m_pControlPtz = nullptr;
	}
	
	if (m_pBallheadCamera)
	{
		m_pBallheadCamera->close();
		delete m_pBallheadCamera;
		m_pBallheadCamera = nullptr;
	}
    
    if (m_pWinTitle)
    {
        delete m_pWinTitle;
        m_pWinTitle = nullptr;
    }
    if (m_emotionWindow)
    {
        delete m_emotionWindow;
        m_emotionWindow = nullptr;
    }

    if (m_menuBall) {
        delete m_menuBall;
        m_menuBall = nullptr;
    }
    //
    clearScrollBar();
    //
    OutputDebugString(_T("CDlgTalk_qt::~CDlgTalk_qt(  ) enters\n"));
    //
    HWND  hDlgTalk = (HWND)this->winId();
    //
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    if (!pProcInfo)  return;

    //
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var)  return;
    DLG_TALK_var& m_var = *pm_var;

    dlgTalk_OnDestroy(hDlgTalk, pm_var);
    //
    dlgTalk_PostNcDestroy(pm_var);

    //
    TCHAR  tBuf[128];
    _sntprintf(tBuf, mycountof(tBuf), _T("~CDlgTalk_qt(). %I64u, tn %d"), pm_var->addr.idInfo.ui64Id, pm_var->addr.uiTranNo_shadow);
    showInfo_open0(0, _T(""), tBuf);
    //	
    freeQmcObjVarInfoIndex(pProcInfo, this->iIndex_talkerInfo);

    OutputDebugString(_T("CDlgTalk_qt::~CDlgTalk_qt(  ) leaves\n"));
}

QWidget* CDlgTalk_qt::getTalkWidget()
{
    ui->widgetMsgArea->setParent(nullptr);
    return ui->widgetMsgArea;
}

void CDlgTalk_qt::initControl()
{
    isLeftDalk = false;
    setWindowFlags(Qt::FramelessWindowHint);
    QFile file(":/Resources/QSS/CDlgTalk_qt.css");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        this->setStyleSheet("");
        QString qsstyleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(qsstyleSheet);
    }
    file.close();

    ui->sendMsg->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->sendMsg, &QTextEdit::customContextMenuRequested, this, &CDlgTalk_qt::RightShowMenu);

    connect(ui->toolBtnMore, SIGNAL(clicked()), this, SLOT(on_MoreBtn_clicked()));
    connect(ui->toolBtnSpeak, SIGNAL(clicked()), this, SLOT(on_SpeakBtn_click()));
    connect(ui->BtnEndAv, SIGNAL(clicked()), this, SLOT(on_EndAvBtn_click()));
    connect(ui->toolBtnScreen, SIGNAL(clicked()), this, SLOT(on_toolBtnScreen_click()));
    connect(ui->toolBtnHome, SIGNAL(clicked()), this, SLOT(on_toolBtnHome_click()));
    connect(ui->toolBtnBall, SIGNAL(clicked()), this, SLOT(on_toolBtnBall_click()));
    connect(ui->toolBtnControl, SIGNAL(clicked()), this, SLOT(on_toolBtnControl_click()));


    m_menuBall = new QMenu(ui->toolBtnBall);
    

    //connect(ui->toolBtnBall, &QPushButton::clicked, m_menuBall, &QMenu::show);
    

    this->setWindowIcon(QIcon(":/Resources/Images/Login/qmClient.png"));
    m_pWinTitle = new WinTitle(ui->widgetTitle);
    m_pWinTitle->setButtonType(MIN_MAX_BUTTON);
    m_pWinTitle->move(0, 0);
    m_pWinTitle->setParent(true);
    connect(m_pWinTitle, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
    connect(m_pWinTitle, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));
    connect(m_pWinTitle, SIGNAL(signalButtonRestoreClicked()), this, SLOT(onButtonRestoreClicked()));
    connect(m_pWinTitle, SIGNAL(signalButtonMaxClicked()), this, SLOT(onButtonMaxClicked()));
    m_WinMove = true;
    connect(ui->widgetMsgShow, &QWebEngineView::loadFinished, this, &CDlgTalk_qt::slot_web_loadFinished);

    connect(ui->sendMsg , &QTextEdit::currentCharFormatChanged, this, &CDlgTalk_qt::currentCharFormatChanged);

    //切换联系人信息按钮
    ui->btnContactsInfo->setIcon(QIcon(":/Resources/Images/WinMain/contactsInfoBtn.png"));
    ui->btnContactsInfo->setIconSize(QSize(40, 20));
    //联系人信息
    
    ui->headIcoBtn->setIcon(QIcon(":/Resources/Images/WinMain/headMax.png"));

    ui->headIcoBtn->setIconSize(QSize(55, 55));
    ui->labelName->setText(u8"");
    ui->labelGroup->setText(u8"");
    ui->labelMsgID->setText(u8"Messenger ID:");

    QMenu* menu = new QMenu(this);
    menu->setWindowFlags(menu->windowFlags() | Qt::FramelessWindowHint);
    menu->setAttribute(Qt::WA_TranslucentBackground);
    menu->setObjectName("senMenu");
    m_sendAction = menu->addAction(u8"按Enter键，发送消息", this, SLOT(onEnterAction()));
    m_ctrlSendAction = menu->addAction(u8"按Enter+Ctrl键，发送消息", this, SLOT(onEnterCtrlAction()));

    QActionGroup* actiongroup = new QActionGroup(this);
    m_sendAction->setCheckable(true);
    m_ctrlSendAction->setCheckable(true);
    m_sendAction->setChecked(true);
    actiongroup->addAction(m_sendAction);
    actiongroup->addAction(m_ctrlSendAction);
    ui->btnSendImg->setMenu(menu);

    ui->sendMsg->installEventFilter(this);
    ui->titleId->setVisible(false);
    ui->btnFace->setIcon(QIcon(":/Resources/Images/WinMain/qy-icon-emoji-l.png"));
    ui->btnFace->setIconSize(QSize(26, 26));
    //ui->btnCutSceen->setIcon(QIcon(":/Resources/Images/WinMain/aio_quickbar_cut_hover.png"));
    //ui->btnCutSceen->setIconSize(QSize(20, 20));
    ui->btnFileSend->setIcon(QIcon(":/Resources/Images/WinMain/qy-icon-wenjian-l.png"));
    ui->btnFileSend->setIconSize(QSize(26,26));
    ui->btnVideo->setIcon(QIcon(":/Resources/Images/WinMain/aio_video_hover.png"));
    ui->btnVideo->setIconSize(QSize(26,26));
    ui->btnDisk->setIcon(QIcon(":/Resources/Images/WinMain/qy-icon-yunpan-l.png"));
    ui->btnDisk->setIconSize(QSize(26, 26));

    ui->btnRemoteVideo->setIcon(QIcon(":/Resources/Images/WinMain/aio_this_video.png"));
    ui->btnRemoteVideo->setIconSize(QSize(26, 26));



    //来电提示
    ui->video_ing_lab->setText(u8"检测到该组有视频任务正在进行");
    ui->video_in_do->setText(u8"点击进入>");
    QPixmap pix1(":/Resources/Images/WinMain/aio_video_ing.png");
    ui->ico_video_ing->setPixmap(pix1);
    ui->video_ing_widget->hide();//默认不显示
    ui->iTaskId_lab->setVisible(false);


    onFontSizecurrentIndexChanged("10");

    connect(ui->sendMsg, &WinMsgQTextEdit::signal_file_drag, this, &CDlgTalk_qt::procSendFile_qt);
    connect(ui->widgetMsgShow, &WinMsgShow::signal_file_drag, this, &CDlgTalk_qt::procSendFile_qt);

    m_emotionWindow = new WinEmotion;
    m_emotionWindow->hide();
    connect(m_emotionWindow, SIGNAL(signalEmotionItemClicked(QString)), this, SLOT(onEmotionItemClicked(QString)));
    // 
    ui->toolBtnChat->setIcon(QIcon(":/Resources/Images/WinMain/talk.png"));
    ui->toolBtnChat->setIconSize(QSize(64, 64));
    ui->toolBtnChat->setText(u8"聊 天");
    ui->toolBtnChat->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
#if 0 
    ui->toolBtnRemoteVideo->setIcon(QIcon(":/Resources/Images/WinMain/remoteVideo.png"));
    ui->toolBtnRemoteVideo->setIconSize(QSize(64, 64));
    ui->toolBtnRemoteVideo->setText(u8"远程视频");
    ui->toolBtnRemoteVideo->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    ui->toolBtnThis->setIcon(QIcon(":/Resources/Images/WinMain/aio_this_video.png"));
    ui->toolBtnThis->setIconSize(QSize(64, 64));
    ui->toolBtnThis->setText(u8"本地视频");
    ui->toolBtnThis->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
#endif
    ui->toolBtnSpeak->setIcon(QIcon(":/Resources/Images/WinMain/aio_spokes.png"));
    ui->toolBtnSpeak->setIconSize(QSize(64, 64));
    ui->toolBtnSpeak->setText(u8"发言");
    ui->toolBtnSpeak->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui->toolBtnScreen->setIcon(QIcon(":/Resources/Images/WinMain/aio_screen.png"));
    ui->toolBtnScreen->setIconSize(QSize(64, 64));
    ui->toolBtnScreen->setText(u8"屏幕共享");
    ui->toolBtnScreen->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui->toolBtnHome->setIcon(QIcon(":/Resources/Images/WinMain/home.png"));
    ui->toolBtnHome->setIconSize(QSize(64, 64));
    ui->toolBtnHome->setText(u8"主页");
    ui->toolBtnHome->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui->toolBtnBall->setIcon(QIcon(":/Resources/Images/WinMain/list.png"));
    ui->toolBtnBall->setIconSize(QSize(64, 64));
    ui->toolBtnBall->setText(u8"列表");
    ui->toolBtnBall->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui->toolBtnControl->setIcon(QIcon(":/Resources/Images/WinMain/yt.png"));
    ui->toolBtnControl->setIconSize(QSize(64, 64));
    ui->toolBtnControl->setText(u8"云台");
    ui->toolBtnControl->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui->toolBtnMore->setIcon(QIcon(":/Resources/Images/WinMain/aio_more.png"));
    ui->toolBtnMore->setIconSize(QSize(64, 64));
    ui->toolBtnMore->setText(u8"更多");
    ui->toolBtnMore->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    auto widgets = ui->widgetVideoShow->findChildren<QWidget*>();
    for (int i = 0; i < widgets.size(); i++)
    {
        widgets[i]->setMouseTracking(true);
    }
    ui->lineSearch->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    // HWND wid = StartShareScreen();



    

	
}

void CDlgTalk_qt::slot_web_loadFinished(bool successed)
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();
    DBManager* pDm = (DBManager*)pProcInfo->m_var.pDBManager;
    //
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var)return;
    if (isTalkerShadowMgr(pm_var->addr))  return;
    //
    int page = 0;
    int pageCount = COUNT_chat_count;
    QList<MessageData> Mess = pDm->getMessages(currentUser.idinfo, page, pageCount);
    if (Mess.size() == 0)
    {
        return;
    }
    for (int i = Mess.size() - 1; i >= 0; i--)
    {
        int isMore = 0;
        if (i == pageCount - 1) {
            isMore = 3;
        }
        MessageData msg = Mess[i];
        if (msg.type == MessageTypes::TextMessage)
        {
            addShowMsg(msg.content, msg.fromUserId.toLong(), msg.messageTime, msg.messageId, 0, 0, 0, msg.chatType, isMore);
        }
        else if (msg.type == MessageTypes::FileMessage) {
            int fileStatus = 0; //文件状态 
            if (msg.is_rece == 1) {
                fileStatus = 1; //传输成功
            }
            else if (msg.cancel == 1) {
                fileStatus = 2; // 传输取消
            }
            else if (msg.cancel == 1 && msg.is_activeProcess == 0) {
                fileStatus = 2; // 传输取消
            }
            else if (msg.cancel == 0 && msg.is_activeProcess == 0)
            {
                fileStatus = 2; // 传输取消
            }

            addShowMsg(msg.content, msg.fromUserId.toLong(), msg.messageTime, msg.messageId, 1, 0, fileStatus, msg.chatType, isMore, msg.fileSize);
        }
        //else if (msg.type == MessageTypes::FileMessage) {
        //    int fileStatus = 0; //文件状态 
        //    if (msg.is_rece == 1) {
        //        fileStatus = 1; //传输成功
        //    }
        //    
        //    else if(msg.cancel == 0 && msg.is_activeProcess == 0)
        //    {
        //        fileStatus = 2; // 传输取消
        //    }
        //    addShowMsg(msg.content, msg.fromUserId.toLong(), msg.messageTime, msg.messageId, 1, 0, fileStatus, msg.chatType, isMore);
        //}
        else if (msg.type == MessageTypes::MeetingMessage) {

            addShowMsg(msg.content, msg.fromUserId.toLong(), msg.messageTime, msg.messageId, 2, 0, 0, msg.chatType, isMore);
        }
        
    }
}

void CDlgTalk_qt::more_loadFinished(int page, int pageCount)
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();
    DBManager* pDm = (DBManager*)pProcInfo->m_var.pDBManager;

    QList<MessageData> Mess = pDm->getMessages(currentUser.idinfo, page, pageCount);
    if (Mess.size() == 0)
    {
        //已经没有更多内容了
        ui->widgetMsgShow->MoreEnd();
        return;
    }
    //for (int i = Mess.size() - 1; i >= 0; i--)
    for (int i = 0; i <= Mess.size() - 1; i++)
    {
        int isMore = 1;
        if (i == pageCount - 1) {
            isMore = 3;
        }
        MessageData msg = Mess[i];
        if (msg.type == MessageTypes::TextMessage)
        {
            addShowMsg(msg.content, msg.fromUserId.toLong(), msg.messageTime, msg.messageId, 0, 0, 0, msg.chatType, isMore);
        }
        else if (msg.type == MessageTypes::FileMessage) {
            int fileStatus = 0; //文件状态 
            if (msg.is_rece == 1) {
                fileStatus = 1; //传输成功
            }
            else if (msg.cancel == 1) {
                fileStatus = 2; // 传输取消
            }
            else if (msg.cancel == 0 && msg.is_activeProcess == 0)
            {
                fileStatus = 2; // 传输取消
            }
            addShowMsg(msg.content, msg.fromUserId.toLong(), msg.messageTime, msg.messageId, 1, 0, fileStatus, msg.chatType, isMore, msg.fileSize);
        }
        //else if (msg.type == MessageTypes::FileMessage) {
        //    int fileStatus = 0; //文件状态 
        //    if (msg.is_rece == 1) {
        //        fileStatus = 1; //传输成功
        //    }
        //    else if (msg.cancel == 1) {
        //        fileStatus = 2; // 传输取消
        //    }
        //    else if (msg.cancel == 0 && msg.is_activeProcess == 0)
        //    {
        //        fileStatus = 2; // 传输取消
        //    }
        //    addShowMsg(msg.content, msg.fromUserId.toLong(), msg.messageTime, msg.messageId, 1, 0, fileStatus, msg.chatType, isMore);
        //}
        else if (msg.type == MessageTypes::MeetingMessage) {

            addShowMsg(msg.content, msg.fromUserId.toLong(), msg.messageTime, msg.messageId, 2, 0, 0, msg.chatType, isMore);
        }

    }
}

//显示用户消息
void CDlgTalk_qt::ShowMsgInfo(WinObjUser user)
{
    currentUser = user;
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

    //
    TCHAR grpName[128] = _T("");
    TCHAR dw[128]  =  _T(  ""  );
    TCHAR bm[128]  =  _T(  ""  );
    TCHAR syr[128] = _T("");
    unsigned  int  uiObjType = 0;
    QY_MESSENGER_ID pidInfo_creator;
    QY_MESSENGER_ID  idInfo;
    pidInfo_creator.ui64Id = 0;
    idInfo.ui64Id = user.idinfo.toInt();
    ui->labCreator->setVisible(false);
    if (idInfo.ui64Id) {
    
        getTalkerDesc(idInfo, &uiObjType, grpName, mycountof(grpName), &pidInfo_creator, dw, mycountof(dw), bm, mycountof(bm), syr, mycountof(syr));
        if (uiObjType == CONST_objType_imGrp) 
        {
            ui->headIcoBtn->setIcon(QIcon(":/Resources/Images/WinMain/group.png"));
            user.name = QString::fromStdWString(grpName);
                if (pidInfo_creator.ui64Id) {
                    ui->headIcoBtn->setIcon(QIcon(":/Resources/Images/WinMain/tmp_group.png"));
              }
                ui->labCreator->setVisible(true);
                ui->labCreator->setText(u8"创建者ID：" + QString::number(pidInfo_creator.ui64Id));
                if (pidInfo_creator.ui64Id == pMisCnt->idInfo.ui64Id) {
                    ui->btnGrpDel->setEnabled(true);
                    ui->btnGrpDel->setStyleSheet("color:red;");
                }
          
        }
        else 
        {
            ui->btnMem->setVisible(false);
            ui->headIcoBtn->setIcon(QIcon(":/Resources/Images/WinMain/person.png"));
            ui->btnGrpDel->setVisible(false);
            user.bm = QString::fromStdWString(bm);
            user.dw = QString::fromStdWString(dw);
            user.name = QString::fromStdWString(syr);
        }
    }

    //
    //ui->labelContactsInfo->setFont(QFont("SimHei", 16, 16));
    //ui->labelContactsInfo->setText(user.dw + " " + user.bm + " " + user.name);
    ui->labelContactsInfo_chat->setFont(QFont("SimHei", 16, 16));
    //
    //ui->labelContactsInfo_chat->setText(user.dw + " " + user.bm + " " + user.name);
    QString qstr;
    QString isQstr;
    if (uiObjType == CONST_objType_imGrp)
    {
        qstr = QString::fromUtf16((char16_t*)grpName);
        isQstr = QString::fromUtf16((char16_t*)grpName);
    }
    else 
    {
        qstr = QString::fromUtf16((char16_t*)dw) + (" ") + QString::fromUtf16((char16_t*)bm) + " " + QString::fromUtf16((char16_t*)syr);
        isQstr = QString::fromUtf16((char16_t*)syr);
    }
    //
    if (isQstr. isEmpty())
    {
        ui->labelContactsInfo_chat->setText(user.idinfo);
    }
    else 
    {

        ui->labelContactsInfo_chat->setText(qstr);
    }
    //
    ui->labelName->setText(user.name);
    ui->labelGroup->setText(user.bm);
    ui->labelMsgID->setText(u8"Messenger ID:" + user.idinfo);
    
    



    if (!user.idinfo.isNull()) {
        user.name = user.name + " (" + user.idinfo + ")";
    }
    ui->titleName->setText(user.name);


   /* DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var)return;
    if (isTalkerShadowMgr(pm_var->addr))  return;*/
    //
     //判断当前视频有没有正在开启
    

    
}

//点击进入会议
void CDlgTalk_qt::on_video_in_do_clicked() {
    QString iTaskId = ui->iTaskId_lab->text();
    if (iTaskId.isEmpty()) {
        return;
    }
    //入会
    CCtxQyMc* pQyMc = g_pQyMc;
    /*CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    HWND  hMainWnd = pQyMc->gui.hMainWnd;
    CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
    QY_MC_mainWndVar& var = pMainWnd->var.common;*/

    //
    HWND  hTool = (HWND)this->winId();



    //
    int  iTaskId_activeTaskAv = 0;
    if (bExists_activeTaskAv(pQyMc, &iTaskId_activeTaskAv, mynull)) {
        //
        if (QString::number(iTaskId_activeTaskAv) != iTaskId) {
            //
            qyMessageBox(hTool, _T("已有一个会议在进行，不能开始新会议"), _T("qycx.com"), MB_OK, 3, mynull);
            return;
        }
        return;
    }
    //
    int res = acceptTaskAv(iTaskId.toInt());
    if (res == -1) {
        ui->video_ing_widget->hide();
        return;
    }

    
}

bool CDlgTalk_qt::bEnableScrollBar(bool bEnable, int  iw_scroll, int  ih_scroll)
{
    bool  bRet = false;

    QWidget* peerDesc = ui->peerDesc;// this->findChild<QWidget*>("peerDesc");
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var)return  false;
    DLG_TALK_var& m_var = *pm_var;

    //
#ifdef  __DEBUG__
    traceLog((TCHAR*)_T("dlgTalk.bEnableScrollbar: %d"), bEnable);

    //
    HWND  hCurTalk = (HWND)this->winId();
    DLG_TALK_var* pCurVar = &m_var;
    HWND  hMgr = mynull;
    DLG_TALK_var* pMgrVar = mynull;
    if (isTalkerShadowMgr(pCurVar->addr)) {
        hMgr = hCurTalk;
    }
    else {
        TALKER_shadow* pShadowInfo = (TALKER_shadow*)pCurVar->pShadowInfo;
        hMgr = pShadowInfo->hMgr;
    }
    CHelp_getDlgTalkVar getDlgTalkVar_mgr;
    pMgrVar = (DLG_TALK_var*)getDlgTalkVar_mgr.getVar(hMgr);
    if (pMgrVar == mynull)goto  errLabel;

    if (pMgrVar->av.taskInfo.mosaicTrans.status.ucb2Streams) {
        if (bEnable) {
            int  ii = 0;
        }
    }


#endif

    //
    if (!scrollArea_)
    {
        scrollArea_ = new QScrollArea(peerDesc);
        scrollArea_->verticalScrollBar()->setStyleSheet("width:12px");
        scrollArea_->horizontalScrollBar()->setStyleSheet("height:12px");
        scrollArea_->setMouseTracking(true);
        scrollArea_->setGeometry(0, 0, peerDesc->width(), peerDesc->height());
        scrollArea_->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        QLabel* lab_ = new QLabel();
        lab_->setMouseTracking(true);
        //lab_->setStyleSheet("background:red;");
        //lab_->setFixedSize(1920, 1080);
        //lab_->show();
        scrollArea_->setWidget(lab_);
        scrollArea_->show();
        scrollArea_->lower();

        //
        m_var.av.hCtrl_peer = (HWND)scrollArea_->widget()->winId();
    }

    //
    QLabel* pLabel; pLabel = (QLabel*)scrollArea_->widget();
    if (pLabel == mynull)  goto  errLabel;

    //
    if (!bEnable) {
        //
        //pLabel->setFixedSize(peerDesc->width() - 2, peerDesc->height() - 2);
        pLabel->setFixedSize(peerDesc->width(), peerDesc->height());
        pLabel->show();
        //
        scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    }
    else {
        pLabel->setFixedSize(iw_scroll, ih_scroll);
        pLabel->show();
        //
        if ( this->isFullScreen()) {
            scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
            scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        }
        else {
            scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
            scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        }
    }


    //
    bRet = true;
errLabel:
    return  bRet;
}

void CDlgTalk_qt::clearScrollBar()
{
    HWND  hDlgTalk = (HWND)this->winId();
    DLG_TALK_var* pm_var = get_pm_var();
    if (pm_var == mynull)return;
    DLG_TALK_var& m_var = *pm_var;

    if (pm_var->av.taskInfo.bTaskExists) {

        //
        freeCapImages(hDlgTalk, m_var.av.hCtrl_peer, &m_var.av.peerZone.images, mynull, &m_var.av.hDc_peer);

    }

    //
    if (scrollArea_)
    {
        delete scrollArea_;
        scrollArea_ = nullptr;
    }
}

//
void CDlgTalk_qt::on_btnMem_clicked() 
{
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var)return;

    //CDlgTalk_grp_members::showDialog(this);
    CDlgTalk_grp_members::getDialog(this);
    CDlgTalk_grp_members::showWnd();
    CDlgTalk_grp_members::setContent(QString::number(pm_var->addr.idInfo.ui64Id));
}

//
int CDlgTalk_qt::on_btnGrpDel_clicked() 
{
    int						iErr = -1;
    CCtxQyMc* pQyMcc = g_pQyMc;
    CCtxQmc_qt* pProcInfoc = (CCtxQmc_qt*)pQyMcc->get_pProcInfo();
    DBManager* pDm = (DBManager*)pProcInfoc->m_var.pDBManager;

     QMessageBox MBox;
    MBox.setWindowTitle(u8"提示");
    MBox.setText(u8"确定要删除该群组吗?");
    MBox.setWindowIcon(QIcon(":/Resources/Images/Title/qmClientTitle.png"));
    //MBox.setIconPixmap(QPixmap());
    QPushButton* agreeBut = MBox.addButton(u8"确认", QMessageBox::AcceptRole);
    QPushButton* cancel =  MBox.addButton(u8"取消", QMessageBox::AcceptRole);
    MBox.exec();
    if (MBox.clickedButton() != (QAbstractButton*)agreeBut) {
        //在 Qt Creator 的输出窗口中输出指定字符串
        return -1;
    }
    



    
    QY_MC* pQyMc = (QY_MC*)g_pQyMc;
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    if (!pProcInfo)  return  -1;
    FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
    if (!pFuncs) return  -1;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    //				   
   // if (AfxMessageBox(getResStr(0, &pQyMc->cusRes, CONST_resId_reallyToDelete), MB_YESNO | MB_DEFBUTTON2) != IDYES)  goto  errLabel;

    HWND  hCurTalk = (HWND)this->winId();
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var)return -1;
   
   
   //
    //
    MACRO_prepareForTran();

    //
    IM_GRP_EX	req = { 0 };
    {
        CQyMalloc					mallocObj;
        IM_L_STREAM* pStream = NULL;

        if (!(pStream = (IM_L_STREAM*)mallocObj.mallocf(sizeof(IM_L_STREAM)))) {
            //traceLogA("sndDevInfo_qmc . malloc failed.");
            goto  errLabel;
        }

        unsigned  int		len;
        char				buf[256];

        //
        IM_GRP_INFO* pReq = &req.common;

        //
        memset(&req, 0, sizeof(req));
        req.common.uiType = CONST_imCommType_imGrp;
        req.common.idInfo.ui64Id = pm_var->addr.idInfo.ui64Id;// messengerInfo.idInfo.ui64Id;
        //
        req.usOp = CONST_imOp_del;

        //  2010/08/14
        pFuncs->pf_startProgress(&pQyMc->gui.progress, uiTranNo);

        //
        MACRO_memset_imLStream(pStream);
        pStream->uiType = CONST_imCommType_lStream;
        pStream->uiContentType = req.common.uiType;
        len = sizeof(pStream->buf);
        if (imGrpEx2Stream(pStream->uiContentType, &req, pStream->buf, &len))  goto  errLabel;
        pStream->ulStreamLen = len;
        len += offsetof(IM_L_STREAM, buf);
        //
        postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_refreshImObjListReq, tStartTran, uiTranNo, 0, (char*)pStream, len, NULL, 0, 0, NULL, 0);

    }

    //  pProcInfo->bInProgress_toSetPasswd  =  TRUE;
    if (showProgress(&pQyMc->gui.progress, &pQyMc->cusRes, hCurTalk, _T("Please waiting"), NULL, 30, -1, uiTranNo) != IDOK) {
        goto  errLabel;
    }

  
    HWND  hMainWnd; hMainWnd = pQyMc->gui.hMainWnd;
    CMainFrame* pMainWnd_s;
    pMainWnd_s = (CMainFrame*)getObjAddr(hMainWnd);

    //
    del_imGrp_isCli(pQyMc,&req.common.idInfo);

    //
    //删库
    pDm->deleteSession( QString::number(pm_var->addr.idInfo.ui64Id));


    pMainWnd_s->delTalkerList(QString::number(pm_var->addr.idInfo.ui64Id));
    pMainWnd_s->delContactList(QString::number(pm_var->addr.idInfo.ui64Id));
    //关闭窗口
    pMainWnd_s->slot_closeTalk(QString::number(pm_var->addr.idInfo.ui64Id));
    
   

#if  0
    memset(&wmBuf, 0, sizeof(wmBuf));
    wmBuf.uiType = CONST_qyWmParam_delItem;
    wmBuf.hItem = pSel->u.rootTree.hItem;
    SendMessage(pEventInfo->hWnd, CONST_qyWm_comm, 0, (LPARAM)&wmBuf);
#endif

    //
    iErr = 0;  goto  errLabel;
errLabel:

    return  iErr;
}


//
int CDlgTalk_qt::doTask_av(int iCmd, int iTaskId)
{
    int  iErr = -1;
    DLG_TALK_var* pm_var = get_pm_var();
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

    ///
    switch (iCmd) {
    case  IDC_av: {
        PARAM_startAvCall  param = { 0 };
        HWND  hCurTalk = (HWND)this->winId();
        int level = 0;
        //
        bool b3D = true;
        if (pm_var->addr.uiObjType != CONST_objType_imGrp)b3D = false;
        //
#ifdef  __DEBUG__
        //
        if (1) {
            param.talkerPolicy.usConfType = CONST_usConfType_emergencyCommand;
            traceLog((TCHAR*)_T("for test: set confType to emergencyCommand"));
        }
#endif 
        //
        pProcInfo->doCmd_startAvCall(mynull, hCurTalk, level, b3D, false, &param);
    }
                break;
    default:
        break;
    }

    iErr = 0;
errLabel:
    return iErr;
}

//
DLG_TALK_var* CDlgTalk_qt::get_pm_var()
{
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    if (!pProcInfo)  return  NULL;

    DLG_TALK_var* pm_var = NULL;
    QMC_objVar_info* pTalkerInfo = getQmcObjVarInfoByIndex(pProcInfo, this->iIndex_talkerInfo);
    if (!pTalkerInfo)  return  NULL;
    if (!pTalkerInfo->bUsed)  return  NULL;

    pm_var = (DLG_TALK_var*)pTalkerInfo->var.pData;
    if (!pm_var)  return  NULL;
    if (pm_var->uiType != CONST_objVarDataType_dlgTalk)  return  NULL;

    

    return  pm_var;
}

//关闭
void CDlgTalk_qt::closeCDlgTalk_qt()
{
    isLeftDalk = true;
    HWND dlgHwnd = (HWND)this->winId();
    dlgTalk_bQuitDlg(dlgHwnd, get_pm_var(), FALSE);

    DeviceSelectDialog::closeDialog();

}


//
void  CDlgTalk_qt::refreshBtns()
{
    CCtxQyMc* pQyMc = g_pQyMc;
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    if (!pProcInfo)  return;
    FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
    if (!pFuncs)  return;

    //
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var) return;
    if (isTalkerShadowMgr(pm_var->addr)) return;
    TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
    HWND  hMgr = pShadowInfo->hMgr;

    //
    CHelp_getDlgTalkVar	help_getDlgTalkVar;
    DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hMgr, _T("dlgIa::OnBnClickedrequest"));
    if (!pDlgTalkVar)  return;
    TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pDlgTalkVar->pShadowInfo;

    //
    if (!pDlgTalkVar->av.taskInfo.bTaskExists)  return;


    QString qstr;
    qstr = dlgTalk_canSpeak(hMgr) ? u8"静音" : u8"发言";
    ui->toolBtnSpeak->setText(qstr);

    //
    if (pShadowMgr->resourcesInfo.info_send.nScreens > 0)  qstr = QString::fromUtf16((char16_t*)getResStr(0, &pQyMc->cusRes, CONST_resId_cancelScreenSharing));
    else  qstr = QString::fromUtf16((char16_t*)getResStr(0, &pQyMc->cusRes, CONST_resId_screenSharing));
    ui->toolBtnScreen->setText(qstr);



    //
    return;
}

//
int  CDlgTalk_qt::do_closeTaskAv_afterTaskClosed()
{
    int  iErr = -1;
    CCtxQyMc* pQyMc = g_pQyMc;
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var)return  -1;

    if (!isTalkerShadowMgr(pm_var->addr))  return  -1;

    int talkerSubtype = CONST_talkerSubtype_video;

    HWND  hShadow = mynull;
    if (findTalker_shadow(pQyMc, pm_var->addr.idInfo.ui64Id, talkerSubtype, &hShadow))  goto  errLabel;

    showInfo_open0(0, mynull, _T("do_closeTaskAv_afterTaskClosed: close talk_video shadow now"));
    PostMessage(hShadow, WM_CLOSE, 0, 0);

    iErr = 0;
errLabel:
    return  iErr;
}



//消息界面进来
void CDlgTalk_qt::hideWidget(WinObjUser user )
{
    m_WinMove = false;
    //消息widget显示
    isTopDalk = false;
    ui->widgetMsgArea->show();
    ui->stackedWidgetInfo->hide();

    ui->ContactsInfo_chat->show();
    // ui->widgetTitle->show();
     //视频widget隐藏
    ui->titleId->hide();
    ui->titleName->hide();
    ui->widgetTitle->hide();
    ui->widgetVideoShow->hide();
    ui->conferenceController->hide();
    // ui->ContactsInfo_chat->hide();
     /*ui->widget_2->hide();
     ui->widget_2->setMaximumWidth(0);*/
    ui->bottomMenu->hide();



    
    //检测是否有正在运行的任务
    ui->iTaskId_lab->setText("");
    OldConfs  oldConfs = { 0 };
    if (!findOldRecvdConfsActive(&oldConfs))
    {
        for (int i = 0; i < oldConfs.usCnt; i++) {
            OldConfMem* pMem = &oldConfs.mems[i];
            if (pMem->idInfo_peer.ui64Id == user.idinfo.toInt())
            {
               ui->video_ing_widget->show();
               ui->iTaskId_lab->setText(QString::number(pMem->iTaskId));
               break;
            }

        }
    }

}

//联系人信息
void CDlgTalk_qt::on_btnContactsInfo_clicked()
{
    //
    if (!m_bShown_contactInfo)
    {
        ui->stackedWidgetInfo->setCurrentIndex(0);
        ui->stackedWidgetInfo->show();
        m_bShown_contactInfo = true;
    }
    else
    {
        ui->stackedWidgetInfo->hide();
        m_bShown_contactInfo = false;
    }
}

//视频界面进来
void CDlgTalk_qt::showWidget(WinObjUser user, bool move)
{
    isTopDalk = true;
    //设置背景色
    QPalette p = this->palette();
    p.setBrush(this->backgroundRole(), QBrush(QColor(22, 154, 218)));
    this->setPalette(p);
    this->setAutoFillBackground(true);
    //消息widget隐藏
    ui->widgetMsgArea->hide();
   // qDebug() << ui->conferenceController->isVisible();
    ui->conferenceController->setVisible(ui->conferenceController->isVisible());

    ui->widgetMsgArea->setFixedWidth(0);
  
    //视频widget显示
    ui->titleId->show();
    ui->titleName->show();
    if (!this->isFullScreen())
    {
        ui->widgetTitle->show();
    }
    ui->widgetVideoShow->show();
    ui->bottomMenu->show();
   
    if (move)
    {
        this->sizeOriginalVideo();
    }


}

//主持人设置自动打开会议控制
void CDlgTalk_qt::viewCompereControl() 
{
    HWND hDlgTalk = (HWND)this->winId();
    DLG_TALK_var* pCurVar = get_pm_var();
    DLG_TALK_var* pMgrVar = pCurVar;

    HWND  hMgr = hDlgTalk;
    CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
    if (!isTalkerShadowMgr(pMgrVar->addr)) {
        TALKER_shadow* pTalkerShadow = (TALKER_shadow*)pMgrVar->pShadowInfo;
        hMgr = pTalkerShadow->hMgr;
        pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
        if (!pMgrVar)  return;
    }
    //判断主持人  todo
    //QY_MESSENGER_ID compereIdinfo = dlgTalk_get_idInfo_compere(hDlgTalk);
    bool  bIAmCompere = dlgTalk_bIAmConfCompere(hDlgTalk);

    //
    QY_MC* pQyMc = QY_GET_GBUF();
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (pMgrVar->av.taskInfo.idInfo_initiator.ui64Id == pMisCnt->idInfo.ui64Id) 
    {
        return ;
    }

    //if (pMisCnt->idInfo.ui64Id == compereIdinfo.ui64Id)
    if  (  bIAmCompere)
    {
        if (!ui->conferenceController->isVisible()) {
            slot_conference_controller();
        }
    }
    //else if (pMisCnt->idInfo.ui64Id != compereIdinfo.ui64Id && pMgrVar->av.taskInfo.idInfo_initiator.ui64Id != pMisCnt->idInfo.ui64Id) 
    else if (!bIAmCompere && pMgrVar->av.taskInfo.idInfo_initiator.ui64Id != pMisCnt->idInfo.ui64Id)
    {
        if (ui->conferenceController->isVisible()) {
            slot_conference_controller();
        }
    }
}


//聊天
void CDlgTalk_qt::on_toolBtnChat_clicked()
{
    DLG_TALK_var* pm_var = get_pm_var();
    if (pm_var == mynull)return;

    //
    if (ui->widgetMsgArea->isVisible())
    {
        //ui->widgetMsgArea->hide();
        WinObjUser user;
        user.idinfo = ui->labelMsgID->text();
        user.name = ui->labelName->text();
        ui->widgetTitle->hide();

        this->showWidget(user, false);
        if (scrollArea_)
        {
            scrollArea_->setGeometry(0, 0, ui->peerDesc->width(), ui->peerDesc->height());
        }
        //
#ifdef  __DEBUG__
        int  iW = ui->peerDesc->width();
        int  iH = ui->peerDesc->height();
#endif
        //
        if (this->windowState() == Qt::WindowState::WindowMaximized || this->windowState() == Qt::WindowState::WindowFullScreen)
        {
            if (this->windowState() == Qt::WindowState::WindowFullScreen && scrollArea_)
            {
                //scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
                //scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
            }
            //
#ifdef  __DEBUG__
            HWND  hCtrl = pm_var->av.hCtrl_peer;
            RECT  rc_peer;
            GetClientRect(hCtrl, &rc_peer);
            int  ii = 0;
#endif
            //
            return;
        }
        QTimer::singleShot(50, [this]() {
            this->move(this->pos().x() + 400, this->pos().y());
            this->resize(this->width() - 400, this->height());
        });
        //this->resize(this->size() - QSize(1, 1));
        //this->sizeOriginalVideo();
    }
    else
    {
        //ui->widgetVideoShow->move(400, 0);

        QSize sz = this->size();
        ui->widgetMsgArea->setFixedWidth(400);
        ui->widgetMsgArea->show();
        ui->ContactsInfo_chat->hide();
        ui->btnVideo->hide();
        //ui->widgetMenu->hide();
        ui->stackedWidgetInfo->hide();
        //
#ifdef  __DEBUG__
        int iW = ui->peerDesc->width();
        int  iH = ui->peerDesc->height();
#endif
        //
        if (scrollArea_)
        {
            scrollArea_->setGeometry(0, 0, ui->peerDesc->width(), ui->peerDesc->height());
        }
        //
        refreshLayout();
        //
        if (this->windowState() == Qt::WindowState::WindowMaximized || this->windowState() == Qt::WindowState::WindowFullScreen)
        {
            if (scrollArea_)
            {
                scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
                scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
            }
            return;
        }
        qDebug() << this->pos().x() << "-------" << this->pos().y();
        this->resize(sz.width() + 400, sz.height());
        this->move(this->pos().x() - 400, this->pos().y());
    }
    auto rect = this->geometry();
    QRect rc = QApplication::primaryScreen()->geometry();
    if (rect.right() > rc.width())
    {
        this->move(rc.width() - rect.width(), rect.y());
    }
}

int  procTalkTo_qt(HWND  hParent, int  iWndContentType_hParent, LPCTSTR  inputStr)
{
    int						iErr = -1;
    QY_MC* pQyMc = QY_GET_GBUF();
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    if (!pProcInfo)  return  -1;
    FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
    if (!pFuncs)  return  -1;

    CQyString				str;
    TCHAR					txtContent[1024];
    BOOL					bNothing = FALSE;
    MIS_CNT* pMisCnt = NULL;
    TCHAR* pT = NULL;
    TCHAR					tBuf[255 + 1] = _T("");
    char					buf[255 + 1] = "";

    //
    CHelp_getDlgTalkVar		help_getDlgTalkVar;
    DLG_TALK_var* pCurVar = NULL;

    CQyMalloc				mallocObj_pMsgBuf;
    MIS_MSGU* pMsgBuf = NULL;

    //  
    HWND  hCurTalk = NULL;
    MSG_tool_common* pMsgToolCommon = NULL;

    //
    CHelp_getDlgTalkVar   help_getDlgTalkVar_mgr;
    QY_MESSENGER_ID		idInfo_dst;

#ifdef  __DEBUG__
    //  traceLog(  _T(  "Not finished"  )  );
#endif

    switch (iWndContentType_hParent)
    {
    case  CONST_qyWndContentType_talker:
        hCurTalk = hParent;
        break;

        break;
    default:
        goto  errLabel;
    }


    if (!hCurTalk)  return  -1;
    //
    pCurVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hCurTalk);
    if (!pCurVar)  return  -1;
    //  DLG_TALK_var		&	m_var				=	*pm_var;
    pMsgBuf = (MIS_MSGU*)mallocObj_pMsgBuf.mallocf(sizeof(MIS_MSGU));
    if (!pMsgBuf)  return  -1;
    //
    HWND					hMgr; hMgr = hCurTalk;
    DLG_TALK_var* pMgrVar; pMgrVar = pCurVar;
    if (!isTalkerShadowMgr(pCurVar->addr))
    {
        TALKER_shadow* pShadow = (TALKER_shadow*)pCurVar->pShadowInfo;
        if (!pShadow)  goto  errLabel;
        hMgr = pShadow->hMgr;
        pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
        if (!pMgrVar)  goto  errLabel;
    }
    TALKER_shadow_mgr* pShadowMgr; pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
    if (!pShadowMgr)  goto  errLabel;


    //
    if (!(pMisCnt = pCurVar->pMisCnt))  goto  errLabel;
    //
#ifdef  __SUPPORT_HTMLEDIT__

    //
    if (pMsgToolCommon) {
        MSG_tool_common& msgToolCommon = *pMsgToolCommon;

        //
        IHTMLDocument2* pDoc = NULL;
        IHTMLElement* pBody = NULL;
        if (!msgToolCommon.m_pHtmlEdit_input->GetDHtmlDocument(&pDoc))  goto  errLabel;

        if (SUCCEEDED(pDoc->get_body(&pBody))) {
            BSTR  bstr = NULL;
            if (SUCCEEDED(pBody->get_innerText(&bstr))) {
                str = bstr;
                SysFreeString(bstr);
            }
            //  MACRO_CStringTrim(  str  );
            str.Trim();
            if (!str.GetLength())  bNothing = TRUE;

            if (!pCurVar->addr.bInNoticeMode) {	//  
                if (SUCCEEDED(pBody->get_innerHTML(&bstr))) {
                    str = bstr;
                    SysFreeString(bstr);
                }
            }

            pBody->Release();
        }

        //
#ifdef  __DEBUG__
        printHtmlEdit(msgToolCommon.m_pHtmlEdit_input);
#endif
    }
    else {
        if (!inputStr)  goto  errLabel;
        str = inputStr;
        str.Trim();
        if (!str[0])  bNothing = TRUE;
}

#else
    if (!inputStr)  goto  errLabel;
    str = inputStr;
    str.Trim();
    if (!str[0])  bNothing = TRUE;
#endif

    if (bNothing) {
#ifdef  __DEBUG__
        traceLogA((char*)"procTalkTo failed: nothing input");
#endif
        goto  errLabel;
    }

    if (pCurVar->addr.bInNoticeMode) {
#ifndef  __WINCE__
        //if (myMessageBox(hCurTalk, CQyString("Whether to send \"") + str + _T("\""), _T(""), MB_YESNO | MB_DEFBUTTON2) != IDYES)  goto  errLabel;
#else
        traceLog(_T("Not supported in ce"));
        goto  errLabel;
#endif
    }

    unsigned  char		ucFlg;
    IM_HTML_CONTENT		content;
    int					lenInBytes;
    //
    ucFlg = 0;
    //
    memset(&content, 0, sizeof(content));
    content.uiType = CONST_imCommType_htmlContent;
    lstrcpyn(content.wBuf, str, mycountof(content.wBuf));
    lenInBytes = offsetof(IM_HTML_CONTENT, wBuf) + (lstrlen(content.wBuf) + 1) * sizeof(content.wBuf[0]);
    //
    MSG_ROUTE	route;
    memset(&route, 0, sizeof(route));
    //
    route.idInfo_from.ui64Id = pMisCnt->idInfo.ui64Id;
    //
    route.idInfo_to.ui64Id = pCurVar->addr.idInfo.ui64Id;
    route.uiDevType_to = pCurVar->addr.uiDevType;
    //
    if (pMgrVar->addr.uiObjType != CONST_objType_imGrp
        || !pMgrVar->av.taskInfo.bTaskExists
        || !pMgrVar->av.taskInfo.ucbConfCtrl)
    {
        MACRO_prepareForTran();

        if (postMsg2Mgr_mc(pMisCnt, &route, CONST_misMsgType_talk, ucFlg, CONST_qyCmd_talkTo, tStartTran, uiTranNo, 0, (char*)&content, lenInBytes, &pMgrVar->addr.idInfo, &pMgrVar->addr.idInfo, 0, pMsgBuf, TRUE))  goto  errLabel;
    }
    else  if (pMgrVar->av.taskInfo.ucbStarter
        || pShadowMgr->av.ucbMeConfMgr)
    {
        idInfo_dst.ui64Id = pCurVar->confMgr_grpMemListInfo.idInfo_talkTo.ui64Id;
        if (idInfo_dst.ui64Id == pMisCnt->idInfo.ui64Id) {
            showNotification(0, 0, 0, 0, 0, 0, _T("Can't talk to me"));
            goto  errLabel;
        }
        if (!idInfo_dst.ui64Id)  idInfo_dst.ui64Id = pCurVar->addr.idInfo.ui64Id;
        //
        if (idInfo_dst.ui64Id != pCurVar->addr.idInfo.ui64Id)  content.idInfo_logicalPeer.ui64Id = pCurVar->addr.idInfo.ui64Id;
        //
        MACRO_prepareForTran();

        if (postMsg2Mgr_mc(pMisCnt, &route, CONST_misMsgType_talk, ucFlg, CONST_qyCmd_talkTo, tStartTran, uiTranNo, 0, (char*)&content, lenInBytes, &pCurVar->addr.idInfo, &idInfo_dst, 0, pMsgBuf, TRUE))  goto  errLabel;

    }
    else
    {
        int  i;

        //
        content.idInfo_logicalPeer.ui64Id = pMgrVar->addr.idInfo.ui64Id;

        //
        idInfo_dst.ui64Id = pMgrVar->av.taskInfo.idInfo_starter.ui64Id;
        //
        MACRO_prepareForTran();

        if (postMsg2Mgr_mc(pMisCnt, &route, CONST_misMsgType_talk, ucFlg, CONST_qyCmd_talkTo, tStartTran, uiTranNo, 0, (char*)&content, lenInBytes, &pMgrVar->addr.idInfo, &idInfo_dst, 0, pMsgBuf, TRUE))  goto  errLabel;

        //
        for (i = 0; i < pShadowMgr->av.confMgrInfo.usCnt; i++)
        {
            idInfo_dst.ui64Id = pShadowMgr->av.confMgrInfo.mems[i].idInfo.ui64Id;
            if (idInfo_dst.ui64Id == pMgrVar->av.taskInfo.idInfo_starter.ui64Id)  continue;
            //
            MACRO_prepareForTran();

            if (postMsg2Mgr_mc(pMisCnt, &route, CONST_misMsgType_talk, ucFlg, CONST_qyCmd_talkTo, tStartTran, uiTranNo, 0, (char*)&content, lenInBytes, &pMgrVar->addr.idInfo, &idInfo_dst, 0, pMsgBuf, TRUE))  goto  errLabel;

        }
    }

    // 
    //  postImMsg2Log(  pMisCnt->cfg.misServName,  &pMisCnt->idInfo,  pMisCnt->talkerDesc,  tStartTran,  uiTranNo,  &m_var.addr.idInfo,  m_var.talkerDesc,  content.uiType,  str,  txtContent,  0,  &pProcInfo->schedulerQ  );    

    pFuncs->pf_dlgTalk_qPostMsg(hMgr, pMsgBuf, sizeof(MIS_MSGU));
    PostMessage(hMgr, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);

#ifdef  __SUPPORT_HTMLEDIT__
    if (pMsgToolCommon) {
        MSG_tool_common& msgToolCommon = *pMsgToolCommon;
        //
        IHTMLDocument2* pDoc = NULL;
        IHTMLElement* pBody = NULL;
        //
        if (msgToolCommon.m_pHtmlEdit_input->GetDHtmlDocument(&pDoc)) {
            if (SUCCEEDED(pDoc->get_body(&pBody))) {
                BSTR  bstr = NULL;
                //  str  =  CString(  ""  );
                //  bstr  =  str.AllocSysString(  );
                bstr = SysAllocString(_T(""));
                if (bstr) {
                    pBody->put_innerHTML(bstr);
                    SysFreeString(bstr);
                }
                pBody->Release();
            }
        }
    }
#else
    //  SetDlgItemText(  hDlgTalk,  m_var.guiData.iIDC_EDIT_input,  _T(  ""  )  );
#endif

    iErr = 0;

errLabel:
    return  iErr;
}


void CDlgTalk_qt::RightShowMenu()
{
    QMenu menu(this);// = new QMenu(this);
    QStringList list;
    list << u8"粘贴";
    QList<QAction*> actList;
    for (int i = 0; i < list.count(); i++)
        actList.append(new QAction(list.at(i)));
   // connect(actList.at(0), &QAction::triggered, this, &CDlgTalk_qt::CopyAction);
    connect(actList.at(0), &QAction::triggered, this, &CDlgTalk_qt::PasteAction);

    menu.addActions(actList);
    menu.exec(QCursor::pos());
    //
    //delete  menu;
}
//复制 todo
void CDlgTalk_qt::CopyAction()
{
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(ui->sendMsg->textCursor().selectedText());
}
//粘贴
void CDlgTalk_qt::PasteAction()
{
    QClipboard* clipboard = QApplication::clipboard();
    QString text = clipboard->text();
   
    ui->sendMsg->insertPlainText(text);
    //ui->sendMsg->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
}


//发送消息
void CDlgTalk_qt::on_btnSendImg_clicked()
{
    QString msg = ui->sendMsg->toPlainText().trimmed();
    if (msg.isEmpty())
    {
        QToolTip::showText(this->mapToGlobal(QPoint(300, 600)), QStringLiteral("发送消息不能为空"), this, QRect(0, 0, 120, 100), 2000);
        return;
    }
    DLG_TALK_var* pm_var = get_pm_var();
    QY_MC* pQyMc = QY_GET_GBUF();
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

    QList<SendContent> listImgSend;
    // 获取文本内容
    QString info = ui->sendMsg->toPlainText();
    // 如果有很复杂的富文本，遍历富文本内容，解析出自己的数据
    QTextDocument* doc = ui->sendMsg->document();
    // 获取每一个段落
    QTextBlock cur_block = doc->begin();
    while (cur_block.isValid())
    {
        // 获取每一个分段
        for (QTextBlock::iterator iter = cur_block.begin(); iter != cur_block.end(); iter++)
        {
            QTextFragment cur_fragment = iter.fragment();
            QTextFormat format = cur_fragment.charFormat();
            if (format.isImageFormat())
            {
                // 图片信息
                QTextImageFormat img_format = format.toImageFormat();
                // 图片的本地路径
                QString img_path = img_format.stringProperty(QTextFormat::ImageName);
                if (img_path.startsWith("emoj"))
                {
                    QStringList lst = img_path.split(":");
                    if (lst.size() > 1)
                    {
                        QString face = "&#x" + lst[1] + ";";
                        if (listImgSend.size() == 0)
                        {
                            listImgSend.push_back(SendContent(SendType::Text, face));
                        }
                        else
                        {
                            auto& ls = listImgSend.last();
                            if (ls.type == SendType::Text)
                            {
                                ls.content += face;
                            }
                        }
                    }
                }
                else
                {
                    listImgSend.push_back(SendContent(SendType::Image, img_path));
                }
            }
            else if (format.isCharFormat())
            {
                // 文本内容
                QString info = cur_fragment.text();
                if (listImgSend.size() == 0)
                {
                    listImgSend.push_back(SendContent(SendType::Text, info));
                }
                else
                {
                    auto& ls = listImgSend.last();
                    ls.content += info;
                }
            }
        }
        cur_block = cur_block.next();
    }
    // 获取当前时间
    QDateTime timeCurrent = QDateTime::currentDateTime();
    //
    time_t timeT = timeCurrent.toSecsSinceEpoch();
    //
    unsigned  int puiObjType;
    SendData sd;
    memset(&sd, 0, sizeof(sd));
    sd.from_id = pMisCnt->idInfo;
    sd.peer_id = pm_var->addr.idInfo;
    //TODO:这块后续需要改成  兼容 文本 和图片
    for (size_t i = 0; i < listImgSend.size(); i++)
    {
        if (listImgSend[i].type == SendType::Text)
        {
            msg = listImgSend[i].content;
            break;
        }
    }
    QByteArray ba = msg.toLocal8Bit();
    const char* szName = ba.constData();
    //QString 转 LPCWSTR
    safeTcsnCpy(reinterpret_cast<LPCWSTR>(msg.data()), sd.msg, mycountof(sd.msg));
    sd.send_time = timeT;

    emit MessageSignalCenter::Instance().signal_recv_new_message(sd);
    QString html = ui->sendMsg->document()->toHtml();
    ui->sendMsg->clear();
    ui->sendMsg->deleteAllEmotionImage();
    HWND  hDlgTalk = (HWND)this->winId();

    //记录一条 
 /*   SessionInfo si;
    getTalkerDesc(pm_var->addr.idInfo, &puiObjType, null, 0, null, null, 0, null, 0, null, 0);
    if (puiObjType == CONST_objType_imGrp) {
        si.chat_type = ChatType::GroupChat;
    }
    else {
        si.chat_type = ChatType::OneChat;
    }
    si.content = msg;
    si.header_url = ":/Resources/Images/WinMain/tmp_group.png";
    si.msg_type = MessageTypes::TextMessage;
    si.session_id = QString::number(pm_var->addr.idInfo.ui64Id);
    si.session_name = QString::fromStdWString(pm_var->talkerDesc);
    si.time_stamp = timeT;
    DBManager::Instance().insertSession(si);*/

    if (0 != procTalkTo_qt(hDlgTalk, CONST_qyWndContentType_talker, msg.toStdWString().c_str()))
    {
        return;
    }

}

//
int  removeTaskAvOfPeer(QY_MESSENGER_ID  idInfo_peer)
{
    QY_MC* pQyMc = QY_GET_GBUF();
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    int  index_taskInfo;
    QMC_TASK_INFO* pTaskInfo;

    //
    if (idInfo_peer.ui64Id == 0)  return  -1;

    //
    for (index_taskInfo = 0; index_taskInfo < pProcInfo->cfg.usMaxCnt_taskInfos; index_taskInfo++) {
        pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
        if (!pTaskInfo->bUsed)  continue;
        QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;
        MIS_MSG_TASK* pMsgTask = &pTaskData->msgU.task;
        if (pMsgTask->uiType != CONST_misMsgType_task)  continue;
        IM_CONTENTU* pContent = M_getMsgContent(pMsgTask->ucFlg, &pMsgTask->data);
        if (pContent->uiType != CONST_imCommType_transferAvInfo)  continue;
        
        //
        QY_MESSENGER_ID  tmp_idInfo_peer = pMsgTask->addr_logicalPeer.idInfo;

        //
        if (tmp_idInfo_peer.ui64Id == idInfo_peer.ui64Id) {
            freeTaskInfo(pProcInfo, index_taskInfo, _T("removeTaskAvOfGrp"));
        }
      
        //
        continue;
    }

    return  0;
}


//
int  talk_doAv(HWND  hParent, QY_MESSENGER_ID idInfo, bool  bStartConf)
{
    int  iErr = -1;
    QY_MC* pQyMc = QY_GET_GBUF();
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    //HWND  hCurTalk = (HWND)this->winId();
    //
#if  0
    CDlgTalk_qt* pCurTalk = (CDlgTalk_qt*)CDlgTalk_qt::find((WId)hCurTalk);
    if (!pCurTalk)return;
    DLG_TALK_var* pm_var = pCurTalk->get_pm_var();
    QY_MESSENGER_ID idInfo = pm_var->addr.idInfo;
#endif

    //
    //if (isTalkerShadowMgr(pm_var->addr)) return;
    unsigned  int  uiObjType = 0;
    if (getTalkerDesc(idInfo, &uiObjType, mynull, 0, mynull, mynull, 0, mynull, 0, mynull, 0))  return  -1;

    do {
        HWND  hWnd;
        int  iTalkSubtype = CONST_talkerSubtype_video;
        HWND  m_hWnd_shadow;
        bool  bOldRecvdTaskAvExists = false;

        //
        if (isImGrp(uiObjType)) {
            
            //
            if (!bStartConf) {
                //
                if (!findTalker_shadow(pQyMc, idInfo.ui64Id, iTalkSubtype, &m_hWnd_shadow))
                {
                    SetForegroundWindow(m_hWnd_shadow);
                    iErr = 0;  goto  errLabel;
                }

                //
                QY_MESSENGER_ID idInfo_taskAv;
                if (bExists_activeTaskAv(pQyMc, mynull, &idInfo_taskAv)) {
                    //  MessageBox(hParent, _T("已有一个会议在进行，不能开始新会议"), _T("qycx.com"), MB_OK);
                    showInfo_open0(0, 0, _T("已有一个会议在进行，不能开始新会议"));
                    goto  errLabel;
                }

                //
                HWND  hMgr = mynull;
                findTalker(pQyMc, &idInfo, &hMgr);


                //
                //int  iTaskId = 0;

                if (hMgr && ::IsWindow(hMgr) && ::IsWindowVisible(hMgr)) {
#if  0
                    if (0 == findOldRecvdConfActive(hMgr, &iTaskId)) {
                        bOldRecvdTaskAvExists = true;
                    }
#endif 
                    //
                    removeTaskAvOfPeer(idInfo);
                    WriteLog("Exist Meet not kill");
                    //
                    pProcInfo->av.talk_doAv_info.idInfo_peer = idInfo;
                    pProcInfo->av.talk_doAv_info.dwTickCnt_last = myGetTickCount(mynull);

                    //
                    unsigned  short  usOp = CONST_imOp_applyForConf;
                    sendConfReq(0, hMgr, idInfo, usOp, 0, 0, mynull, mynull);
                    iErr = 0;  break;

                }

                //
                //break;

            }
        }
        else {

            //                          
            //            
            if (!findTalker_shadow(pQyMc, idInfo.ui64Id, iTalkSubtype, &m_hWnd_shadow))
            {
                SetForegroundWindow(m_hWnd_shadow);
                iErr = 0;  goto  errLabel;
            }

            //
            QY_MESSENGER_ID idInfo_taskAv;
            if (bExists_activeTaskAv(pQyMc, mynull, &idInfo_taskAv)) {
                //  MessageBox(hParent, _T("已有一个会议在进行，不能开始新会议"), _T("qycx.com"), MB_OK);
                showInfo_open0(0, 0, _T("已有一个会议在进行，不能开始新会议"));
                goto  errLabel;
            }

            //
            HWND  hMgr = mynull;
            findTalker(pQyMc, &idInfo, &hMgr);


            //
            //int  iTaskId = 0;

            if (hMgr) {
                //
                removeTaskAvOfPeer(idInfo);

                //
                pProcInfo->av.talk_doAv_info.idInfo_peer = idInfo;
                pProcInfo->av.talk_doAv_info.dwTickCnt_last = myGetTickCount(mynull);


            }



        }

        //   
        if (!bOldRecvdTaskAvExists) {
            //
            bool  b3D = false;
            if (uiObjType == CONST_objType_imGrp) {
                b3D = true;
            }
            WriteLog("Meeting !Exists");
            //
            if (pProcInfo->viewDlgSelectAvCompressor(hParent, idInfo, CONST_capType_av, 0, 0, b3D, 0) != IDOK) {
                goto  errLabel;
            }
        }

        //
        pProcInfo->tryToTalkToMessenger_any(mynull, idInfo.ui64Id, iTalkSubtype, FALSE, FALSE, &hWnd);

        if (findTalker_shadow(pQyMc, idInfo.ui64Id, iTalkSubtype, &m_hWnd_shadow))
        {
            goto  errLabel;
        }
        CDlgTalk_qt* video_cdlgTalkqt = (CDlgTalk_qt*)getObjAddr(m_hWnd_shadow);
        if (!video_cdlgTalkqt)
        {
            goto  errLabel;
        }
        {
            WinObjUser user;
            user.name = video_cdlgTalkqt->ui->titleName->text();
            //        user.idinfo = video_cdlgTalkqt->ui->titleId->text();
            user.idinfo = QString::number(idInfo.ui64Id);
            video_cdlgTalkqt->ShowMsgInfo(user);
            video_cdlgTalkqt->showWidget(user);
            video_cdlgTalkqt->show();
        }

        //QDesktopWidget* pDesk = QApplication::desktop();
        QScreen* pDesk;pDesk= QApplication::primaryScreen();
        QRect rc = pDesk->geometry();
        int c_left;
        int c_top;
        //QRect r;
        int dis_height = COUNT_display_height_value;
        int dis_width = COUNT_display_width_value;

        if (rc.height() < dis_height && rc.width() > dis_width) {
            //  if (rc.height() < COUNT_display_height_value && rc.width() > COUNT_display_width_value) {
            c_left = rc.width() - DEFAULT_VIDEO_WIDTH_768 - 1;
            c_top = (rc.height() - DEFAULT_VIDEO_HEIGHT_768) / 2;
            //
            if (c_top > 80)  c_top -= 80;
            else  c_top = 0;
            //
            video_cdlgTalkqt->setGeometry(c_left, c_top, DEFAULT_VIDEO_WIDTH_768, DEFAULT_VIDEO_HEIGHT_768);
        }
        else {
            c_left = rc.width() - DEFAULT_VIDEO_WIDTH;
            c_top = (rc.height() - DEFAULT_VIDEO_HEIGHT) / 2;
            //
            if (c_top > 100)c_top -= 100;
            else  c_top = 0;
            //
            video_cdlgTalkqt->setGeometry(c_left, c_top, DEFAULT_VIDEO_WIDTH, DEFAULT_VIDEO_HEIGHT);
        }






        /*rc.left = screenSize.width() - DEFAULT_VIDEO_WIDTH - 1;
        rc.right = rc.left + DEFAULT_VIDEO_WIDTH;
        rc.top = (screenSize.height() - DEFAULT_VIDEO_HEIGHT) / 2;
        rc.bottom = rc.top + DEFAULT_VIDEO_HEIGHT;*/

        if (bOldRecvdTaskAvExists) {
#if  0
            doAvRecover(iTaskId);
            acceptTaskAv(iTaskId);
            gui_notify_clearTask(iTaskId);
#endif 
    }
        else
        {
            //
            DLG_TALK_var* video_pm_var = video_cdlgTalkqt->get_pm_var();
            if (video_pm_var == NULL) goto  errLabel;
            video_pm_var->m_iCmd = IDC_av;
            //
            video_cdlgTalkqt->doTask_av(video_pm_var->m_iCmd, 0);
        }

        iErr = 0;

} while (false);


errLabel:

    return  iErr;
}









//发送视频
void CDlgTalk_qt::on_btnVideo_clicked()
{
    HWND  hTalk = (HWND)this->winId();
    DLG_TALK_var* pm_var = get_pm_var();

    talk_doAv(hTalk, pm_var->addr.idInfo,false);
}


//笑脸
void CDlgTalk_qt::on_btnFace_clicked()
{
    m_emotionWindow->setVisible(!m_emotionWindow->isVisible());
    QPoint emotionPoint = ((QWidget*)sender())->mapToGlobal(QPoint(0, 0));
    emotionPoint.setX(emotionPoint.x() - m_emotionWindow->width() / 2);
    emotionPoint.setY(emotionPoint.y() - m_emotionWindow->height() - 20);
    m_emotionWindow->move(emotionPoint);
}

//发送文件
void CDlgTalk_qt::on_btnFileSend_clicked()
{
    QString strFileName;
    QFileDialog* pFilename = new QFileDialog(this, Qt::Dialog);
    if (pFilename == NULL) return;

    pFilename->setDirectory("C:/");//设置打开的默认目录.       ////////  需要修改
    pFilename->setNameFilter(tr("*"));//设置限定文件类型
    pFilename->setOption(QFileDialog::DontResolveSymlinks);//可以加载链接路径而不会跳转

    if (pFilename->exec() == QFileDialog::Accepted)
    {
        strFileName = pFilename->selectedFiles().first();
    }

    delete pFilename;

    if (strFileName.isEmpty())
    {
        QMessageBox::information(this, "Error Message", "No File Selected");
        return;
    }

   // qDebug() << "----------------------" << strFileName;
    procSendFile_qt(strFileName);
   
}

void CDlgTalk_qt::procSendFile_qt(QString strFileName)
{
    TCHAR* fileName = (TCHAR*)strFileName.utf16();
    HWND  hCurTalk = (HWND)this->winId();
    DLG_TALK_var* pCurVar = get_pm_var();
    int  iTaskId;

    //
    HWND  hMgr = mynull;
    DLG_TALK_var* pMgrVar = mynull;
    if (isTalkerShadowMgr(pCurVar->addr))  return;
    TALKER_shadow* pTalkerShadow = (TALKER_shadow*)pCurVar->pShadowInfo;
    hMgr = pTalkerShadow->hMgr;
    CHelp_getDlgTalkVar getDlgTalkVar_mgr;
    pMgrVar = (DLG_TALK_var*)getDlgTalkVar_mgr.getVar(hMgr);
    if (pMgrVar == NULL)goto  errLabel;


    //
    TCHAR* finalName; finalName = _tcsrchr(fileName, _T('/'));
    if (finalName == mynull)return;
    finalName++;


    //
    procSendFile(fileName, finalName, mynull, hMgr, pMgrVar, &iTaskId);

    //

    //addShowMsg(QString::fromLocal8Bit(finalName), )

errLabel:
    return;
}



//笑脸传到消息发送区
void CDlgTalk_qt::onEmotionItemClicked(QString code)
{
    ui->sendMsg->setFocus();
    ui->sendMsg->addEmotionUrl(code);
}

//
int  CDlgTalk_qt::do_afterInit()
{
    CCtxQyMc* pQyMc = g_pQyMc;
    //
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var)  return  -1;
    DLG_TALK_var& m_var = *pm_var;

    //
    if (!isTalkerShadowMgr(pm_var->addr)) {
        if (pm_var->iTalkerSubType == 0) {
            this->isChatTalk = true;
        }
    }
    //
    if (pm_var->iTalkerSubType == CONST_talkerSubtype_video) {
        WinObjUser user;
        user.name = ui->titleName->text();
        user.idinfo = ui->titleId->text();
        this->showWidget(user);
        this->sizeOriginalVideo();
        /*pm_var = get_pm_var();
        HWND  hCurTalk = (HWND)this->winId();
        this->sizeAllControls_dlgTalk(hCurTalk, pm_var,);*/
#if  0
        CDlgTalk_qt* video_cdlgTalkqt = this;
        //
        WinObjUser user;
        user.name = ui->titleName->text();
        user.idinfo = ui->titleId->text();
        video_cdlgTalkqt->ShowMsgInfo(user);
        video_cdlgTalkqt->showWidget(user);
        video_cdlgTalkqt->show();
#endif

    }


    //
    refreshLayout();

    //    
    //
    if (isTalkerShadowMgr(m_var.addr)) {
        pQyMc->dbg.dwTickCnt_dlgTalk_0_inited = myGetTickCount(mynull);
        int  iElapseInMs = pQyMc->dbg.dwTickCnt_dlgTalk_0_inited - pQyMc->dwTickCnt_logon;
        int  ii = 0;
    }
    else {
        pQyMc->dbg.dwTickCnt_dlgTalk_1_inited = myGetTickCount(mynull);
        int  iElapseInMs = pQyMc->dbg.dwTickCnt_dlgTalk_1_inited - pQyMc->dwTickCnt_logon;
        int  ii = 0;
    }

    //
    if (isImGrp(m_var.addr.uiObjType)) {  //  对分组，没有远程视频的按钮
        //
        ui->btnRemoteVideo->setVisible(false);
    }


    //
    return  0;
}

//点击网盘
void CDlgTalk_qt::on_btnDisk_clicked() {
    //CloudDiskWidget::ShowDialog();
    HWND  hParent = mynull;// (HWND)this->winId();
    HWND  hCurTalk = (HWND)this->winId();

    viewDlgOfflineRes_talk(hParent, hCurTalk, false, true, mynull);
}

void CDlgTalk_qt::on_remotevideo_resize()
{
    if (m_pRemoteVideo) {
        QRect rect = m_pRemoteVideo->geometry();
        DLG_TALK_var* pm_var = get_pm_var();
        pm_var->av.remoteVideoZone.iW = rect.width();
        pm_var->av.remoteVideoZone.iH = rect.height();

        getCapImages(0, pm_var->av.remoteVideoZone.iX, pm_var->av.remoteVideoZone.iY, pm_var->av.remoteVideoZone.iW, pm_var->av.remoteVideoZone.iH, NULL, &pm_var->av.remoteVideoZone.images);
    }

    if (m_pRemoteVideoMix) {
        QRect rect = m_pRemoteVideoMix->GetVideoGeometry();
        DLG_TALK_var* pm_var = get_pm_var();
        pm_var->av.remoteVideoZone.iW = rect.width();
        pm_var->av.remoteVideoZone.iH = rect.height();

        getCapImages(0, pm_var->av.remoteVideoZone.iX, pm_var->av.remoteVideoZone.iY, pm_var->av.remoteVideoZone.iW, pm_var->av.remoteVideoZone.iH, NULL, &pm_var->av.remoteVideoZone.images);
    }

}

void CDlgTalk_qt::on_remotevideo_close()
{
    if (m_pRemoteVideoMix) {
        //DLG_TALK_var* pm_var = get_pm_var();
        //pm_var->av.hCtrl_RemoteVideo = nullptr;
        //pm_var->av.hWnd_dst_RemoteVideo = nullptr;
        //m_pRemoteVideoMix->close();
        ////delete m_pRemoteVideoMix;

        //m_pRemoteVideoMix->deleteLater();
        //m_pRemoteVideoMix = nullptr;

        m_pRemoteVideoMix->setVisible(false);
    }
}

#if 1
void CDlgTalk_qt::on_btnRemoteVideo_clicked() {

    //if (m_pRemoteVideoMix == nullptr) {
    //    m_pRemoteVideoMix = new CDlgRemoteVideoMix();
    //    m_pRemoteVideoMix->resize(1100, 750);
    //    m_pRemoteVideoMix->show();
    //    //hShow = (HWND)m_pRemoteVideo->winId();

    //    //pm_var->av.hRemoteVideo = hShow;
    //    //pm_var->av.remoteVideoZone.iX = 0;
    //    //pm_var->av.remoteVideoZone.iY = 0;

    //    //QRect rect = m_pRemoteVideo->geometry();

    //    //pm_var->av.remoteVideoZone.iW = rect.width();
    //    //pm_var->av.remoteVideoZone.iH = rect.height();

    //    //connect(m_pRemoteVideoMix, &CDlgRemoteVideo::to_remotevideo_resize, this, &CDlgTalk_qt::on_remotevideo_resize);
    //}
    //else {
    //    //hShow = (HWND)m_pRemoteVideo->winId();

    //    m_pRemoteVideoMix->show();
    //}


    HWND  hCurTalk = (HWND)this->winId();

    //viewDlgOfflineRes_talk(hParent, hCurTalk, false, true, null);

    DLG_TALK_var* pm_var = get_pm_var();
    CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;

    HWND				hMgr = hCurTalk;
    DLG_TALK_var* pMgrVar = pm_var;
    if (!isTalkerShadowMgr(pm_var->addr)) {
        TALKER_shadow* pTalkerShadow = (TALKER_shadow*)pm_var->pShadowInfo;
        if (!pTalkerShadow)  goto  errLabel;
        if (!IsWindow(pTalkerShadow->hMgr))  goto  errLabel;
        hMgr = pTalkerShadow->hMgr;		//  2013/02/15
        pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(pTalkerShadow->hMgr);
        if (!pMgrVar)  goto  errLabel;
    }

    do {

        HWND hShow = nullptr;
        if (m_pRemoteVideoMix == nullptr) {
            m_pRemoteVideoMix = new CDlgRemoteVideoMix(this);
            m_pRemoteVideoMix->resize(1100, 750);
            m_pRemoteVideoMix->show();
            hShow = (HWND)m_pRemoteVideoMix->GetVideoWindow();

            pm_var->av.hCtrl_RemoteVideo = hShow;
            pm_var->av.hWnd_dst_RemoteVideo = pm_var->av.hCtrl_RemoteVideo;// (HWND)m_pRemoteVideoMix->winId();
            pm_var->av.remoteVideoZone.iX = 0;
            pm_var->av.remoteVideoZone.iY = 0;

            QRect rect = m_pRemoteVideoMix->GetVideoGeometry();

            pm_var->av.remoteVideoZone.iW = rect.width();
            pm_var->av.remoteVideoZone.iH = rect.height();

            TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;

            m_pRemoteVideoMix->Init(hCurTalk, pMgrVar, mynull, pShadowMgr, hMgr, hShow);
            if (!m_pRemoteVideoMix->OnInitDialog()) {
                //
                showNotification_open(0, 0, 0, _T("该用户没找到工业相机"));
                //
                MACRO_safeDelete(m_pRemoteVideoMix);
                //
                break;
            }

            connect(m_pRemoteVideoMix, &CDlgRemoteVideoMix::to_remotevideo_close, this, &CDlgTalk_qt::on_remotevideo_close);
            connect(m_pRemoteVideoMix, &CDlgRemoteVideoMix::to_remotevideo_resize, this, &CDlgTalk_qt::on_remotevideo_resize);
        }
        else {
            hShow = (HWND)m_pRemoteVideoMix->winId();
            m_pRemoteVideoMix->setVisible(true);

            m_pRemoteVideoMix->show();
        }

    } while (false);


    /* DLG_TALK_var* pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
     if (!pMgrVar)return;*/
    

    //showDlgObjs_ts(hCurTalk, pMgrVar, null, pShadowMgr, hMgr, hShow);

errLabel:
    return;
}

#endif

#if 0
void CDlgTalk_qt::on_btnRemoteVideo_clicked() {
    //CloudDiskWidget::ShowDialog();
    //HWND  hParent = null;// (HWND)this->winId();
    HWND  hCurTalk = (HWND)this->winId();

    //viewDlgOfflineRes_talk(hParent, hCurTalk, false, true, null);

    DLG_TALK_var* pm_var = get_pm_var();
    CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;

    HWND				hMgr		= hCurTalk;
    DLG_TALK_var  *		pMgrVar		=	pm_var;
    if (!isTalkerShadowMgr(pm_var->addr)) {
        TALKER_shadow* pTalkerShadow = (TALKER_shadow*)pm_var->pShadowInfo;
        if (!pTalkerShadow)  goto  errLabel;
        if (!IsWindow(pTalkerShadow->hMgr))  goto  errLabel;
        hMgr = pTalkerShadow->hMgr;		//  2013/02/15
        pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(pTalkerShadow->hMgr);
        if (!pMgrVar)  goto  errLabel;
    }


    HWND hShow = nullptr;
    if (m_pRemoteVideo == nullptr) {
        m_pRemoteVideo = new CDlgRemoteVideo();
        m_pRemoteVideo->resize(600, 400);
        m_pRemoteVideo->show();
        hShow = (HWND)m_pRemoteVideo->winId();

        pm_var->av.hCtrl_RemoteVideo = hShow;
        pm_var->av.remoteVideoZone.iX = 0;
        pm_var->av.remoteVideoZone.iY = 0;

        QRect rect = m_pRemoteVideo->geometry();

        pm_var->av.remoteVideoZone.iW = rect.width();
        pm_var->av.remoteVideoZone.iH = rect.height();

        connect(m_pRemoteVideo, &CDlgRemoteVideo::to_remotevideo_resize, this, &CDlgTalk_qt::on_remotevideo_resize);
    }
    else {
        hShow = (HWND)m_pRemoteVideo->winId();

        m_pRemoteVideo->show();
    }

   

   /* DLG_TALK_var* pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
    if (!pMgrVar)return;*/
    TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;

    showDlgObjs_ts(hCurTalk, pMgrVar, null, pShadowMgr, hMgr, hShow);

errLabel:
    return;
}

#endif

//接收到QTextEdit上的消息发送到widgetMsgShow去显示
void CDlgTalk_qt::addShowMsg(QString msg, int64_t idinfo, int msgTime, QString msgid, int msgtype, int  iTaskId, int fileStatus, int chatType, int isMore ,int filesize)
{
    QString info = "";
    QString pDw = "";
    QString pBm = "";
    QString pSyr = "";
    QString pTime = "";
    QY_MC* pQyMc = QY_GET_GBUF();
    DLG_TALK_var* pm_var = get_pm_var();
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (!pMisCnt)  return;
    QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
    QY_MESSENGER_REGINFO		regInfo;
    MY_REG_DESC	 desc;
    QY_OBJ_DB* pObjDb = getProcedObjDb(pQyMc, 0, pQyMc->iDsnIndex_mainSys);
    if (!bObjDbAvail(pObjDb)) return;
    CMyDb* pDb = (CMyDb*)pObjDb->pDb;
    LPCTSTR misServName = _T("");
    TCHAR	talkerDesc[128] = _T("");
    QY_MESSENGER_ID msgidinfo;
    msgidinfo.ui64Id = idinfo;
    if (!pQyMc->p_g_dbFuncs->pf_bGetMessengerRegInfoBySth(pDb, CONST_dbType_myDb, getResTable(0, &pQyMc->cusRes, CONST_resId_fieldIdTable),
        CONST_tabName_qyImObjRegInfoTab, misServName, &msgidinfo, 0, &regInfo))
    {
        memset(&regInfo, 0, sizeof(regInfo));
    }
    regInfo2Desc(0, &regInfo, &desc, talkerDesc, mycountof(talkerDesc), NULL, 0);

    pDw = QString::fromWCharArray(desc.pDw).trimmed();
    pBm = QString::fromWCharArray(desc.pBm).trimmed();
    pSyr = QString::fromWCharArray(desc.pSyr).trimmed();
    char		bufTime[256] = "";
    QDateTime timeCurrent = QDateTime::currentDateTime();
    time_t tRecvTime = 0;
    // 获取当前时间
    if (msgTime == 0) {
        tRecvTime = timeCurrent.toSecsSinceEpoch(); ;
    }
    else {

        tRecvTime = msgTime;
    }
    displayShortTime(tRecvTime, bufTime, mycountof(bufTime));
    QString str(bufTime);
    pTime = bufTime;

    const QString path = QApplication::applicationDirPath() + "/" + QString("infoconf.ini");
    QSettings settings(path, QSettings::IniFormat);
    //
    //settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    //
    if (msg.length() < 20)
    {
        info = pSyr + ": " + msg;
    }
    else
    {
        info = pSyr + ": " + msg.mid(0, 20);
    }
    if (pSyr.isEmpty()) {
        pSyr = "(" + QString::number(idinfo) + ")";
    }

    settings.setValue(QString("/%1/%2").arg(pm_var->addr.idInfo.ui64Id).arg("info"), info);
    settings.setValue(QString("/%1/%2").arg(pm_var->addr.idInfo.ui64Id).arg("time"), pTime);

    emit to_addTalkInfoList(ui->titleId->text(), info);


    //
    if (idinfo == pMisCnt->idInfo.ui64Id)
    {
        pSyr = pTime + "  " + pSyr;
        ui->widgetMsgShow->sendMsg(msg, pSyr, msgid, msgtype, fileStatus, chatType, isMore , filesize , idinfo);

    }
    else
    {
        pSyr = pSyr + "  " + pTime;
        ui->widgetMsgShow->receiveMsg(msg, pSyr, msgid, msgtype, fileStatus, chatType, isMore , filesize , idinfo);

    }
}



//掉用文件显示进度条
void CDlgTalk_qt::showFileProgress(QString msgid, QString Progress, int iStatus , qint64 idinfo_to) {
    DLG_TALK_var* pCurVar = get_pm_var();
    if (pCurVar == NULL)  return ;
    QString userid = QString::number(pCurVar->addr.idInfo.ui64Id);
    QY_MESSENGER_ID idInfo_to;
    QY_MESSENGER_ID userId_type;
    userId_type.ui64Id = userid.toInt();
    idInfo_to.ui64Id = idinfo_to;
    TCHAR idinfoto_name[125];
    unsigned int uiObjType = 0;
    int isObjType = 0;
    //判断群组
    getTalkerDesc(userId_type, &uiObjType, mynull, mynull, mynull, mynull, mynull, mynull, mynull, mynull,mynull);
    if (  uiObjType == CONST_objType_imGrp)
    {
        isObjType = 1;
    }

    /*if (isTalkerShadowMgr(pCurVar->addr))  return;*/
    getTalkerDesc(idInfo_to, mynull, mynull, mynull, mynull, mynull, mynull, mynull, mynull, idinfoto_name, mycountof(idinfoto_name));
    if (CONST_imTaskStatus_sendFinished == iStatus || CONST_imTaskStatus_recvFinished == iStatus)
    {
        Progress =  u8"接收完毕";
    }
    else if (CONST_imTaskStatus_canceledBySender == iStatus)
    {
        Progress = u8"发送者已取消";
    }
    else if (CONST_imTaskStatus_canceledByReceiver == iStatus) {
        Progress = u8"接收者已取消";
    }
    else {
        Progress = QString::fromStdWString(idinfoto_name) + u8"接收" + Progress;
       
    }
    ui->widgetMsgShow->setFileProgress(msgid, Progress, iStatus , userid,isObjType);
}

//
int  CDlgTalk_qt::refreshLayout()
{
    int  iErr = -1;
    HWND  hCur = (HWND)this->winId();
    DLG_TALK_var* pCurVar = get_pm_var();
    if (pCurVar == NULL)  return  -1;
    HWND  hMgr = mynull;
    DLG_TALK_var* pMgrVar = mynull;
    CHelp_getDlgTalkVar  getDlgTalkVar_mgr;
    TCHAR grpName_peer[125];
    TCHAR srcName_peer[125];

    //
    QWidget* otherDesc = this->findChild<QWidget*>("otherDesc");
    QWidget* meDesc = this->findChild<QWidget*>("meDesc");
    QWidget* peerDesc = this->findChild<QWidget*>("peerDesc");


    //
    if (isTalkerShadowMgr(pCurVar->addr)) {
        hMgr = hCur;
        pMgrVar = pCurVar;
    }
    else {
        TALKER_shadow* pShadowInfo = (TALKER_shadow*)pCurVar->pShadowInfo;
        hMgr = pShadowInfo->hMgr;
        pMgrVar = (DLG_TALK_var*)getDlgTalkVar_mgr.getVar(hMgr);
        if (pMgrVar == mynull) goto  errLabel;
    }


    //    
    //
    if (pMgrVar->addr.uiObjType == CONST_objType_messenger) {       //  个人
        ui->toolBtnSpeak->hide();
    }

    //
    if (!pMgrVar->av.taskInfo.bTaskExists) {
        otherDesc->hide();
        //
        iErr = 0;  goto  errLabel;
    }




    //
    /*if (pMgrVar->addr.uiObjType == CONST_objType_imGrp) {
        otherDesc->hide();
    }*/
    if (pMgrVar->addr.uiObjType != CONST_objType_messenger) {   //  imGrp, tmpMsgr(临时组)
        otherDesc->hide();

        getTalkerDesc(pCurVar->addr.idInfo, NULL, grpName_peer, mycountof(grpName_peer), mynull, mynull, 0, mynull, 0, NULL, 0);
        ui->titleName->setText(QString::fromStdWString(grpName_peer) + "(" + QString::number(pCurVar->addr.idInfo.ui64Id) + ")");

        //

    }
    else {  // 个人
        //
            //        
    //
        int  nScreens = 0, nMediaFiles = 0;
        int  nMediaFiles_unresizable = 0;											//  2015/03/12
        int  iW_unresizable = 0, iH_unresizable = 0;
        BOOL	bExists_recvdResource = FALSE;
        //
        int  nScreens_sendingResource = 0, nMediaFiles_sendingResource = 0;	//  2015/03/12
        int  nMediaFiles_unresizable_sendingResource = 0;
        int  iW_unresizable_sendingResource = 0, iH_unresizable_sendingResource = 0;	//  2015/03/12
        BOOL	bExists_sharingResource = FALSE;	//  2014/11/14


        //
        bExists_recvdResource = bTaskExists_recvResource(pMgrVar, &nScreens, &nMediaFiles, &nMediaFiles_unresizable, &iW_unresizable, &iH_unresizable, NULL);

        //
        if (nScreens > 0) {
            otherDesc->show();
        }
        else {
            otherDesc->hide();
        }


        //
        getTalkerDesc(pCurVar->addr.idInfo, NULL, mynull, 0, mynull, mynull, 0, mynull, 0, srcName_peer, mycountof(srcName_peer));
        ui->titleName->setText(QString::fromStdWString(srcName_peer) + "(" + QString::number(pCurVar->addr.idInfo.ui64Id) + ")");

        //
#if  0
        if (nScreens == 1) {
            //  滚动，
            int  ii = 0;
            bEnableScrollBar(true, iW_unresizable, iH_unresizable);
        }
        else {  //  停止滚动
            bEnableScrollBar(false, 0, 0);

        }
#endif

    }
    
        

    //     
    //
    HWND  hDlgTalk; hDlgTalk = (HWND)this->winId();
    DLG_TALK_var* pm_var; pm_var = get_pm_var();
    RECT rc;
    GetClientRect(hDlgTalk, &rc);
    sizeAllControls_dlgTalk(hDlgTalk, pm_var, &rc);




    //
    iErr = 0;
    //
errLabel:
    return  iErr;
}


//显示io
int CDlgTalk_qt::doTimerProc()
{

#if  10
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    TCHAR  tBuf[128];

    ui->lab_io->setText(u8"下行：" + QString::number( pProcInfo->status.netStat.ins.uiInSpeedInKbps) + u8"，上行："+ QString::number(pProcInfo->status.netStat.ins.uiOutSpeedInKbps) + " kbps");
   // _sntprintf(tBuf, mycountof(tBuf), _T("%s: %d, %s: %d kbps "), _T("下行"), pProcInfo->status.netStat.ins.uiInSpeedInKbps, _T("上行"), pProcInfo->status.netStat.ins.uiOutSpeedInKbps);
    // SetDlgItemText(hDlgTalk, m_var.guiData.iIDC_STATIC_status, tBuf);
#endif

    return  0;
}


//远程视频
void CDlgTalk_qt::on_toolBtnRemoteVideo_clicked(bool checked)
{

}


void CDlgTalk_qt::onFontSizecurrentIndexChanged(const QString& size)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(size.toInt());
    mergeFormatOnWordOrSelection(fmt);
    ui->sendMsg->setFontPointSize(size.toInt());
    ui->sendMsg->setFocus();
}

void CDlgTalk_qt::mergeFormatOnWordOrSelection(const QTextCharFormat& format)
{
    QTextCursor cursor = ui->sendMsg->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::Document);
    cursor.mergeCharFormat(format);
    ui->sendMsg->mergeCurrentCharFormat(format);
}

void CDlgTalk_qt::currentCharFormatChanged(const QTextCharFormat& format)
{
    QTextCharFormat fmt;
    fmt.setBackground(Qt::transparent);
    mergeFormatOnWordOrSelection(fmt);
}

void CDlgTalk_qt::onEnterAction()
{
    m_sendAction->setChecked(true);
}
void CDlgTalk_qt::onEnterCtrlAction()
{
    m_ctrlSendAction->setChecked(true);
}

void CDlgTalk_qt::keyPressEvent(QKeyEvent* event)
{
    __super::keyPressEvent(event);
}

//最小化
void CDlgTalk_qt::onButtonMinClicked()
{
    showMinimized();
}

//关闭窗体
void CDlgTalk_qt::onButtonCloseClicked()
{
    DLG_TALK_var* pm_var = get_pm_var();

    if (pm_var->iTalkerSubType == CONST_talkerSubtype_video) {
        this->doEndAv();
    }

    //
    closeCDlgTalk_qt();
}

//还原
void CDlgTalk_qt::onButtonRestoreClicked()
{
    this->showNormal();
    //QPoint windowPos;
    //QSize windowSize;
    //m_pWinTitle->getRestoreInfo(windowPos, windowSize);
    //this->setGeometry(QRect(windowPos, windowSize));
}

//最大化
void CDlgTalk_qt::onButtonMaxClicked()
{
    
    this->showMaximized();
    //m_pWinTitle->saveRestoreInfo(this->pos(), QSize(this->width(), this->height()));
    //QRect desktopRect = QApplication::desktop()->availableGeometry();
    //QRect FactRect = QRect(desktopRect.x(), desktopRect.y(), desktopRect.width(), desktopRect.height());
    //setGeometry(FactRect);
}

//实时监控消息
bool CDlgTalk_qt::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
{
    Q_UNUSED(eventType);
    MSG* msg = reinterpret_cast<MSG*>(message);

    //
    switch (msg->message)
    {
    case  CONST_qyWm_comm:
    {
        //
        HWND  hDlgTalk = (HWND)this->winId();
        DLG_TALK_var* pm_var = get_pm_var();

        //
        QY_WMBUF_COMM* pWmBuf = (QY_WMBUF_COMM*)msg->lParam;
        if (msg->wParam == CONST_qyWmParam_getObjAddr) {
            pWmBuf->u.getObjAddr.pObjAddr = this;
            *result = CONST_qyWmRc_ok;
            return  true;
        }
        //
        if (pWmBuf->uiType == CONST_misMsgType_input) {

            MIS_MSG_INPUT* pMsg = (MIS_MSG_INPUT*)pWmBuf;
            IM_CONTENTU* pContent = NULL;
            int					i;
            //
            if (isUcFlgRouteTalkData(pMsg->ucFlg) 
                //|| isUcFlgTalkData(pMsg->ucFlg)
                )  pContent = (IM_CONTENTU*)pMsg->data.buf;
            else  pContent = (IM_CONTENTU*)&pMsg->data;

            if (pContent->uiType == CONST_imCommType_confReq) {
                if (isUcFlgResp(pMsg->ucFlg)) {
                    //
                    HWND  hTalk = (HWND)this->winId();
                    //
                    if (!isRcOk(pMsg->usCode)) {
                        talk_doAv(hTalk, pm_var->addr.idInfo, true);
                    }
                    //
                    *result = CONST_qyWmRc_ok;
                    return  true;
                }
            }

        }
        //
        *result = dlgTalk_OnQyComm(hDlgTalk, pm_var, msg->wParam, msg->lParam);

    }
    //						 
    return  true;
    break;
    case CONST_qyWm_postVideoAmplifierOk:
    {        
      
        DLG_TALK_var* pm_var = get_pm_var();        

        if (pm_var && isTalkerShadowMgr(pm_var->addr)) {
        }
        else {      
            //ShowListMenu();
            _isVideoAmplifier = true;        

        }
    }
    break;

	case CONST_qyWm_postVideoAmplifierCancel:
	{

		DLG_TALK_var* pm_var = get_pm_var();

		if (pm_var && isTalkerShadowMgr(pm_var->addr)) {
		}
		else {
			_isVideoAmplifier = false;
		}
	}
	break;
    case  CONST_qyWm_postComm:
    {
        //
        HWND  hDlgTalk = (HWND)this->winId();
        DLG_TALK_var* pm_var = get_pm_var();
        //
        *result = dlgTalk_OnQyPostComm(hDlgTalk, pm_var, msg->wParam, msg->lParam);
    }
    //
    return  true;
    break;
    case  WM_CLOSE:
        this->closeCDlgTalk_qt();
        return  true;
        break;
    default:
        //
        if (msg->message == WM_MOUSEMOVE)
        {
            int  i = 0;
        }
        //
        break;
    }

    return  WinBasic::nativeEvent(eventType, message, result);
}

//界面尺寸变化重绘
void CDlgTalk_qt::resizeEvent(QResizeEvent* event)
{
    HWND  hDlgTalk = (HWND)this->winId();
    DLG_TALK_var& m_var = *(DLG_TALK_var*)get_pm_var();
    //
    RECT rc;
    GetClientRect(hDlgTalk, &rc);
    sizeAllControls_dlgTalk(hDlgTalk, &m_var, &rc);
#if  10
    if (scrollArea_)
    {
        scrollArea_->setGeometry(0, 0, ui->peerDesc->width(), ui->peerDesc->height());
    }
#endif
    QWidget::resizeEvent(event);
}


//
int  CDlgTalk_qt::sizeAllControls_dlgTalk(HWND  hDlg, void* pDLG_TALK_var, RECT* pRect)
{
    DLG_TALK_var& m_var = *(DLG_TALK_var*)get_pm_var();

    //  2012/04/18
    DLG_talk_layout	layout;
    RECT				rc;
    GetClientRect(hDlg, &rc);
    if (dlgTalk_calculateLayout(hDlg, &m_var, &rc, &layout))  goto  errLabel;
    if (mySizeAllControls_dlgTalk_peer(hDlg, m_var, &layout, pRect))  goto  errLabel;
    //if (mySizeAllControls_dlgTalk_tools(hDlg, m_var, &layout, &rc))  goto  errLabel;
    if (mySizeAllControls_dlgTalk_me_other(hDlg, m_var, &layout, &rc))  goto  errLabel;

errLabel:
    return 0;
}
int  CDlgTalk_qt::mySizeAllControls_dlgTalk_peer(HWND  hDlg, DLG_TALK_var& m_var, DLG_talk_layout* pLayout, RECT* pRect)
{
    int			iErr = -1;
    HDWP			hDwp;
    RECT			cliRc;

#ifdef  __DEBUG__
    traceLog((TCHAR*)_T("mySizeAllControls_dlgTalk_peer called"));
#endif

    //
    int			iEdge_l = CONST_edge_l_dlgTalk_wall;
    int			iEdge_t = CONST_edge_l_dlgTalk_wall;
    int			iEdge_r = CONST_edge_l_dlgTalk_wall;
    int			iEdge_b = CONST_edge_l_dlgTalk_wall;
    //
    int			iX_spacing = CONST_iX_spacing_dlgTalk_wall;			//  
    int			iY_spacing = CONST_iY_spacing_dlgTalk_wall;			//  
    //

#ifdef  __APP_qyMc__
    if (!m_var.ucbOnGlobalVWall) {
        iEdge_l = CONST_edge_l_dlgTalk_desktop;
        iEdge_t = CONST_edge_t_dlgTalk_desktop;
        iEdge_r = CONST_edge_l_dlgTalk_desktop;
        iEdge_b = CONST_edge_b_dlgTalk_desktop;
        //
        iX_spacing = CONST_iX_spacing_dlgTalk_desktop;			//  
        iY_spacing = CONST_iY_spacing_dlgTalk_desktop;			//  
}
#endif





    int			iW_dlgDesc = 0;
    int			iH_dlgDesc = 0;
    //
    int			iW_memberList = CONST_iW_memberList;
    int			iH_memberList = 10;
    //
    int			iW_taskList = 10;
    int			iH_taskList = 10;
    //
    int			iW_instantStatus = 50;
    int			iH_instantStatus = 15;			//  20;		//  2012/05/17, 因为gps墙上小talk的缘故，希望talk标签小一点
    //
    int			iW_recentMsgList = 10;
    int			iH_recentMsgList = 10;
    //
    int			iW_input = 10;
    int			iH_input = 24;
    //
    int			iW_ptz = 0;				//  2012/09/05
    int			iH_ptz = 0;
    BOOL			bShowPtz = false;//dlgTalk_bPtzShown(hDlg);
    //
    int			iW_peerDesc = 10;
    int			iH_peerDesc = 10;
    //
    int			iW_meDesc = 0;			//  2008/03/27
    int			iH_meDesc = 0;
    //
    int			iW_otherDesc = 0;
    int			iH_otherDesc = 0;
    //
    int			x, y;
    //  CWnd		*	pWnd;
    HWND			hWnd;
    int			idc;
    //	 
    int			iW_pRect, iH_pRect;
    int			iW_cliRc, iH_cliRc;
    //  int			tmpiX,tmpiY;

    //
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();

    HWND				hCtrl;
    UINT			uFlags;


    QWidget* peerDesc = ui->peerDesc;// this->findChild<QWidget*>("peerDesc");
    //
    //
    HWND  hCurTalk = (HWND)this->winId();
    DLG_TALK_var* pCurVar = &m_var;
    HWND  hMgr = mynull;
    DLG_TALK_var* pMgrVar = mynull;
    if (isTalkerShadowMgr(pCurVar->addr)) {
        hMgr = hCurTalk;
    }
    else {
        TALKER_shadow* pShadowInfo = (TALKER_shadow*)pCurVar->pShadowInfo;
        hMgr = pShadowInfo->hMgr;
    }
    CHelp_getDlgTalkVar getDlgTalkVar_mgr;
    pMgrVar = (DLG_TALK_var*)getDlgTalkVar_mgr.getVar(hMgr);
    if (pMgrVar == mynull)return -1;// goto  errLabel;

    //
    int  nScreens = 0, nMediaFiles = 0;
    int  nMediaFiles_unresizable = 0;											//  2015/03/12
    int  iW_unresizable,iH_unresizable; iW_unresizable = 0, iH_unresizable = 0;
    BOOL	bExists_recvdResource; bExists_recvdResource = FALSE;
    //
    int  nScreens_sendingResource,nMediaFiles_sendingResource; nScreens_sendingResource = 0, nMediaFiles_sendingResource = 0;	//  2015/03/12
    int  nMediaFiles_unresizable_sendingResource; nMediaFiles_unresizable_sendingResource = 0;
    int  iW_unresizable_sendingResource, iH_unresizable_sendingResource; iW_unresizable_sendingResource = 0, iH_unresizable_sendingResource = 0;	//  2015/03/12
    BOOL	bExists_sharingResource; bExists_sharingResource = FALSE;	//  2014/11/14


    //
    if (pMgrVar->addr.uiObjType == CONST_objType_imGrp) {
    
        int index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, pMgrVar->av.taskInfo.iTaskId);
        QMC_TASK_INFO* pTaskInfo = (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(pProcInfo,  index_taskInfo);
        if (pTaskInfo == mynull)  goto  errLabel;
        QMC_taskData_conf* pTc = (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;
        if (pTc == mynull)goto  errLabel;
        if (pTc->common.uiType != CONST_taskDataType_conf)goto  errLabel;
        DLG_TALK_videoConference* videoConference = &pTc->videoConference;
        
        if (pMgrVar->av.taskInfo.mosaicTrans.status.ucb2Streams) {
            bEnableScrollBar(false, 0, 0);
            }
        else {
            //
            DLG_TALK_videoConferenceActiveMemFrom* pActiveMem = &videoConference->activeMems_from[0];

            //
            if (pActiveMem->avStream.obj.resObj.uiObjType == CONST_objType_mosaicStream_resource) {
                bEnableScrollBar(false, pActiveMem->avStream.obj.tranInfo.video.vh_decompress.bih.biWidth, pActiveMem->avStream.obj.tranInfo.video.vh_decompress.bih.biHeight);
            }
            else {
                bEnableScrollBar(false, 0, 0);
            }
        }

    }
    else {
        bExists_recvdResource = bTaskExists_recvResource(pMgrVar, &nScreens, &nMediaFiles, &nMediaFiles_unresizable, &iW_unresizable, &iH_unresizable, NULL);


        //
        if (nScreens == 1) {
            bEnableScrollBar(true, iW_unresizable, iH_unresizable);
        }
        else {
            bEnableScrollBar(false, 0, 0);
        }
    }

    //
    m_var.av.idc_peer = m_var.guiData.iIDC_STATIC_peerDesc;
    //m_var.av.hCtrl_peer = (HWND)scrollArea_->widget()->winId();
    m_var.av.hWnd_dst_peer = m_var.av.hCtrl_peer;

    hCtrl = m_var.av.hCtrl_peer;//GetDlgItem(hDlg, m_var.av.idc_me);
    if (!hCtrl)  goto  errLabel;
    InvalidateRect(hCtrl, NULL, TRUE);

    //m_var.guiData.peerCapRect.iX  =  0;  m_var.guiData.peerCapRect.iY  =  0;
    m_var.av.peerZone.iX = 0;  m_var.av.peerZone.iY = 0;

    qDebug() << ui->peerDesc->height() << "=========" << ui->peerDesc->width();

    //
    RECT rc_peer;
    GetClientRect(hCtrl, &rc_peer);
    m_var.av.peerZone.iW = rc_peer.right - rc_peer.left;
    m_var.av.peerZone.iH = rc_peer.bottom - rc_peer.top;


    //
    getCapImages(m_var.ucbAutoClip, m_var.av.peerZone.iX, m_var.av.peerZone.iY, m_var.av.peerZone.iW, m_var.av.peerZone.iH, NULL, &m_var.av.peerZone.images);

   /* if (m_var.av.peerZone.images.head.usCnt > 0) {
        m_iX_dst = m_var.av.peerZone.images.mems[0].iX_dst;
        m_iY_dst = m_var.av.peerZone.images.mems[0].iY_dst;
        m_iW_dst = m_var.av.peerZone.images.mems[0].iW_dst;
        m_iH_dst = m_var.av.peerZone.images.mems[0].iH_dst;

        m_iW_org = m_var.av.peerZone.images.mems[0].iW_org;
        m_iH_org = m_var.av.peerZone.images.mems[0].iH_org;
        
    }*/

    //
    iErr = 0;
errLabel:
    return  iErr;
}
int  CDlgTalk_qt::mySizeAllControls_dlgTalk_me_other(HWND  hDlg, DLG_TALK_var& m_var, DLG_talk_layout* pLayout, RECT* pRect)
{
#ifdef  __DEBUG__
    traceLog((TCHAR*)_T("mySizeAllControls_dlgTalk_me_other called"));
#endif

    int			iErr = -1;
    HDWP			hDwp;
    RECT			cliRc;
    //
    int			iEdge_l = CONST_edge_l_dlgTalk_wall;
    int			iEdge_t = CONST_edge_l_dlgTalk_wall;
    int			iEdge_r = CONST_edge_l_dlgTalk_wall;
    int			iEdge_b = CONST_edge_l_dlgTalk_wall;
    //
    int			iX_spacing = CONST_iX_spacing_dlgTalk_wall;			//  
    int			iY_spacing = CONST_iY_spacing_dlgTalk_wall;			//  
    //






    int			iW_dlgDesc = 0;
    int			iH_dlgDesc = 0;
    //
    int			iW_memberList = CONST_iW_memberList;
    int			iH_memberList = 10;
    //
    int			iW_taskList = 10;
    int			iH_taskList = 10;
    //
    int			iW_instantStatus = 50;
    int			iH_instantStatus = 15;			//  20;		//  2012/05/17, 因为gps墙上小talk的缘故，希望talk标签小一点
    //
    int			iW_recentMsgList = 10;
    int			iH_recentMsgList = 10;
    //
    int			iW_input = 10;
    int			iH_input = 24;
    //
    int			iW_ptz = 0;				//  2012/09/05
    int			iH_ptz = 0;
    BOOL			bShowPtz = 0;//dlgTalk_bPtzShown(hDlg);
    int			iW_subtitles = 0;											//  2014/10/03
    int			iH_subtitles = 0;
    BOOL			bShowSubtitles = 0;//dlgTalk_bSubtitlesShown(hDlg);			//  TRUE;				//  
    BOOL			bShowOfflineRes = 0;//dlgTalk_bOfflineResShown(hDlg);			//  2015/08/01
    //
    int			iW_peerDesc = 10;
    int			iH_peerDesc = 10;
    //
    int			iW_meDesc = 0;				//  2008/03/27
    int			iH_meDesc = 0;
    //  2017/10/02
    int			iW_status = 0;
    int			iH_status = 0;
    //
    int			iW_bgWall = 0;				//  2014/10/01
    int			iH_bgWall = 0;				//  2014/10/01
    //
    //int			iW_bg							=	0;				//  2014/10/01
    //int			iH_bg							=	0;				//  2014/10/01
    //
    int			iW_otherDesc = 0;
    int			iH_otherDesc = 0;
    //
    int			x, y;
    //  CWnd		*	pWnd;
    HWND			hWnd;
    int			idc;
    //	 
    int			iW_pRect, iH_pRect;
    int			iW_cliRc, iH_cliRc;
    //  int			tmpiX,tmpiY;
    int			iW_right = 0;
    //
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();

    HWND				hCtrl;
    UINT			uFlags;


#if 0
    //
    if (!pLayout)  return  -1;
    if (!pRect)  return  -1;

    //
    idc = m_var.guiData.iIDC_STATIC_dlgDesc;
    hCtrl = GetDlgItem(hDlg, idc);
    if (!hCtrl)  goto  errLabel;


    //
    GetClientRect(hDlg, &cliRc);
    //  rc  =  *pRect;

    DLG_talk_layout& layout = *pLayout;

    //
    iW_memberList = layout.iW_memberList;
    //
    iW_taskList = layout.iW_taskList;
    iW_recentMsgList = iW_taskList;
    iW_instantStatus = iW_recentMsgList;
    iW_input = iW_recentMsgList;
    //
    iW_ptz = layout.iW_ptz;
    iW_subtitles = layout.iW_subtitles;

    //
    iW_cliRc = cliRc.right - cliRc.left - iEdge_l - iEdge_r;
    iW_pRect = pRect->right - pRect->left - iEdge_l - iEdge_r;


    //
    iW_peerDesc = iW_pRect - iW_taskList - iW_memberList - iW_ptz - iW_subtitles - pLayout->iW_offlineRes;
    if (iW_peerDesc < 0)  iW_peerDesc = 0;

    //  2011/03/03
    if (m_var.guiData.ucbShowDlgDesc) {
        iW_dlgDesc = iW_cliRc;
        iH_dlgDesc = CONST_iH_dlgDesc;	//  iH_instantStatus;
    }


    //
    //  peerDesc meDesc
    iH_cliRc = cliRc.bottom - cliRc.top - iEdge_t - iEdge_b - iH_dlgDesc;
    iH_pRect = pRect->bottom - pRect->top - iEdge_t - iEdge_b - iH_dlgDesc;

    if (iH_cliRc < 0)  iH_cliRc = 0;

    iW_right = (iW_cliRc - iW_taskList - iW_memberList - iW_ptz - iW_subtitles - pLayout->iW_offlineRes);

    //  2014/12/03
    calc_me_bgWall_rect(&layout, iW_right, iH_cliRc, &iW_meDesc, &iH_meDesc, &iW_bgWall, &iH_bgWall);

    //  2017/08/22
    if (layout.ucbShow_peer_tool) {
        iW_meDesc = layout.iW_peerInfo;
        iH_meDesc = iH_cliRc - layout.iH_staticPeerInfo - layout.iH_peerInfo - layout.iH_shareScreen;
    }

    //  2017/10/02
    if (layout.ucbShowMeDesc) {
        iW_status = max(iW_meDesc, MIN_iW_status);
        iH_status = CONST_iH_status;
        //
        iH_meDesc -= iH_status;
    }

    //  2017/08/31
    m_var.m_layout.iW_meDesc = iW_meDesc;
    m_var.m_layout.iH_meDesc = iH_meDesc;


    //
    if (layout.ucbShowOtherDesc) {
        float  fVal = 3;
        //
        fVal = 4;
        //
        iW_otherDesc = (iW_cliRc - iW_taskList - iW_memberList - iW_ptz - iW_subtitles - pLayout->iW_offlineRes) / fVal;
        iH_otherDesc = iH_cliRc / fVal;

        //
        float  fW = 1024.;
        float  fH = 768.;
        //
        fW = 1280;
        fH = 720;
        //
        float  fx = iW_otherDesc / fW;
        float  fy = iH_otherDesc / fH;
        float  f = min(fx, fy);

        iW_otherDesc = f * fW;
        iH_otherDesc = f * fH;
    }
    else {
        iW_otherDesc = 0;
        iH_otherDesc = 0;
    }

    //  2010/09/10

    //  
    hDwp = M_BeginDeferWindowPos(4);
    if (hDwp) {
        int			iW, iH;

        //  8
        idc = IDC_STATIC_meDesc;			//  
        x = cliRc.right - cliRc.left - iEdge_r - iEdge_l - iW_meDesc;  //  -  layout.iW_peer_tool;
        y = cliRc.bottom - cliRc.top - iEdge_b - iH_meDesc - iH_dlgDesc - iH_status;
        iW = iW_meDesc;  iH = iH_meDesc;
        //
        uFlags = SWP_NOZORDER | SWP_HIDEWINDOW;
        if (layout.ucbShowMeDesc)  uFlags = SWP_SHOWWINDOW;
        M_DeferWindowPos(hDwp, GetDlgItem(hDlg, idc), NULL, x, y, iW, iH, uFlags);
        //
        //m_var.guiData.meCapRect.iX  =  x;  m_var.guiData.meCapRect.iY  =  y;
        //m_var.guiData.meCapRect.iW  =  iW;  m_var.guiData.meCapRect.iH  =  iH;
        m_var.av.meZone.iX = x;  m_var.av.meZone.iY = y;
        m_var.av.meZone.iW = iW;  m_var.av.meZone.iH = iH;

        //  2017/10/02
        idc = IDC_STATIC_status;
        x = cliRc.right - cliRc.left - iEdge_r - iEdge_l - iW_status;  //  -  layout.iW_peer_tool;
        y = cliRc.bottom - cliRc.top - iEdge_b - iH_dlgDesc - iH_status;
        iW = iW_status;  iH = iH_status;
        //
        uFlags = SWP_NOZORDER | SWP_HIDEWINDOW;
        if (layout.ucbShowMeDesc)  uFlags = SWP_SHOWWINDOW;
        M_DeferWindowPos(hDwp, GetDlgItem(hDlg, idc), NULL, x, y, iW, iH, uFlags);


        //  2014/09/30
        //  9
        idc = IDC_STATIC_bgWall_conf;			//  
        //x  =  cliRc.right  -  cliRc.left  -  iEdge_r  -  iEdge_l  -  iW_meDesc  -  iW_bgWall;
        x = iEdge_l + layout.iW_memberList + layout.iW_taskList + layout.iW_ptz + layout.iW_subtitles + layout.iW_offlineRes;
        y = cliRc.bottom - cliRc.top - iEdge_b - iH_bgWall - iH_dlgDesc;
        iW = iW_bgWall;  iH = iH_bgWall;
        //
        uFlags = SWP_NOZORDER | SWP_HIDEWINDOW;
        //if  (  layout.ucbShowBgWall_starter  )  
        if (dlgTalk_bShowBgWall(hDlg))
        {
            uFlags = SWP_SHOWWINDOW;
        }
        M_DeferWindowPos(hDwp, GetDlgItem(hDlg, idc), NULL, x, y, iW, iH, uFlags);
        //
        //m_var.guiData.bgWallCapRect.iX  =  x;  m_var.guiData.bgWallCapRect.iY  =  y;
        //m_var.guiData.bgWallCapRect.iW  =  iW;  m_var.guiData.bgWallCapRect.iH  =  iH;
        m_var.av.bgWall.iX = x;  m_var.av.bgWall.iY = y;
        m_var.av.bgWall.iW = iW;  m_var.av.bgWall.iH = iH;


        //  10
        idc = IDC_STATIC_otherDesc;
        if (layout.ucbShowOtherDesc) {
            x = cliRc.right - cliRc.left - iEdge_r - iEdge_l - iW_otherDesc - layout.iW_peerInfo;
            y = iEdge_t;
            iW = iW_otherDesc;  iH = iH_otherDesc;
            M_DeferWindowPos(hDwp, GetDlgItem(hDlg, idc), NULL, x, y, iW, iH, SWP_NOZORDER | SWP_SHOWWINDOW);
        }
        else {
            y += iH;
            iW = iW_otherDesc;  iH = iH_otherDesc;
            M_DeferWindowPos(hDwp, GetDlgItem(hDlg, idc), NULL, x, y, iW, iH, SWP_NOZORDER | SWP_HIDEWINDOW);
        }
        //
        //m_var.guiData.otherCapRect.iX  =  x;  m_var.guiData.otherCapRect.iY  =  y;
        //m_var.guiData.otherCapRect.iW  =  iW;  m_var.guiData.otherCapRect.iH  =  iH;
        m_var.av.otherZone.iX = x;  m_var.av.otherZone.iY = y;
        m_var.av.otherZone.iW = iW;  m_var.av.otherZone.iH = iH;
        //
        M_EndDeferWindowPos(hDwp);
}
#endif

    //
    //QTextEdit* msgList = this->findChild<QTextEdit*>("showMsg");
    //msgList->hide();


    //
    QWidget* meDesc = this->findChild<QWidget*>("meDesc");

    //
    m_var.av.idc_me = m_var.guiData.iIDC_STATIC_meDesc;
    m_var.av.hCtrl_me = (HWND)meDesc->winId();//GetDlgItem(hDlg, m_var.av.idc_me);
    hCtrl = m_var.av.hCtrl_me;//GetDlgItem(hDlg, m_var.av.idc_me);
    if (!hCtrl)  goto  errLabel;
    InvalidateRect(hCtrl, NULL, TRUE);
    //  2013/02/23. 注意,peer当背景画,直接画在对话框上. me画控件上. 所以要把meCapRect转成控件坐标
    //m_var.guiData.meCapRect.iX  =  0;  m_var.guiData.meCapRect.iY  =  0;
    m_var.av.meZone.iX = 0;  m_var.av.meZone.iY = 0;

    //
    RECT rc_me;
    GetClientRect(hCtrl, &rc_me);
    m_var.av.meZone.iW = rc_me.right - rc_me.left;
    m_var.av.meZone.iH = rc_me.bottom - rc_me.top;


    //
    unsigned  char  ucbAutoClip; ucbAutoClip = m_var.ucbAutoClip_me;	//  2016/02/17
    //
    getCapImages(ucbAutoClip, m_var.av.meZone.iX, m_var.av.meZone.iY, m_var.av.meZone.iW, m_var.av.meZone.iH, NULL, &m_var.av.meZone.images);

#if 0
    //  2014/10/01
    m_var.av.idc_bgWall_conf = m_var.guiData.iIDC_STATIC_bgWall_conf;
    m_var.av.hCtrl_bgWall_conf = GetDlgItem(hDlg, m_var.av.idc_bgWall_conf);
    hCtrl = GetDlgItem(hDlg, m_var.av.idc_bgWall_conf);
    if (!hCtrl)  goto  errLabel;
    InvalidateRect(hCtrl, NULL, TRUE);
    //m_var.guiData.bgWallCapRect.iX  =  0;  m_var.guiData.bgWallCapRect.iY  =  0;
    m_var.av.bgWall.iX = 0;  m_var.av.bgWall.iY = 0;
    getCapImages_bgWall(hDlg, &m_var, m_var.ucbAutoClip, m_var.av.bgWall.iX, m_var.av.bgWall.iY, m_var.av.bgWall.iW, m_var.av.bgWall.iH, &pLayout->bgWallLayoutCfg, &pLayout->bgWallLayout);
    //
    memcpy(&m_var.m_layout.bgWallLayout, &pLayout->bgWallLayout, sizeof(m_var.m_layout.bgWallLayout));
#endif

    //  2013/02/25
    QWidget* otherDesc; otherDesc = this->findChild<QWidget*>("otherDesc");


#if  10
    m_var.av.idc_other = m_var.guiData.iIDC_STATIC_otherDesc;
    m_var.av.hCtrl_other = (HWND)otherDesc->winId();
    hCtrl = m_var.av.hCtrl_other;
    if (!hCtrl)  goto  errLabel;
    InvalidateRect(hCtrl, NULL, TRUE);
    //m_var.guiData.otherCapRect.iX  =  0;  m_var.guiData.otherCapRect.iY  =  0;
    m_var.av.otherZone.iX = 0;  m_var.av.otherZone.iY = 0;

    //
    RECT rc_other;
    GetClientRect(hCtrl, &rc_other);
    m_var.av.otherZone.iW = rc_other.right - rc_other.left;
    m_var.av.otherZone.iH = rc_other.bottom - rc_other.top;

    getCapImages(m_var.ucbAutoClip, m_var.av.otherZone.iX, m_var.av.otherZone.iY, m_var.av.otherZone.iW, m_var.av.otherZone.iH, NULL, &m_var.av.otherZone.images);
#endif

    //
    iErr = 0;
errLabel:
    return  iErr;
}

void CDlgTalk_qt::send_selLayoutType(int x, int y) {

    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (!pMisCnt)  return;

    ConfLayoutParam  confLayoutParam = { 0 };
    //confLayoutParam = pTc->videoConference.confLayoutParam;
    //if (!confLayoutParam.ui64Id)  break;
    //

    confLayoutParam.phoneEnlargeParam.x = x;
    confLayoutParam.phoneEnlargeParam.y = y;

     /*
    if (str.isEmpty()) return;
    QStringList list = str.split("|");

    confLayoutParam.enlargeParam.usEnlargeType = CONST_enlargeType_img;
    confLayoutParam.enlargeParam.ui64Id = pProcInfo->m_ipcProc.op.idInfo.ui64Id;
    confLayoutParam.ipcParam.iChannel = list[0].toInt();
    pProcInfo->m_ipcProc.op.iChannel = list[0].toInt();*/

    CHelp_getDlgTalkVar help_getDlgTalkVar;
    CDlgTalk_qt* pWin_cdlgtalk = this;

    DLG_TALK_var* pm_var = pWin_cdlgtalk->get_pm_var();
    if (!pm_var)return;
    if (isTalkerShadowMgr(pm_var->addr)) return;
    TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
    HWND  hMgr = pShadowInfo->hMgr;

    do {

        //DLG_TALK_var* pDlgTalkVar = pWin_cdlgtalk->get_pm_var();
        DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hMgr);
        if (!pDlgTalkVar)break;
        if (!isTalkerShadowMgr(pDlgTalkVar->addr)) break;
        if (!pDlgTalkVar->av.taskInfo.bTaskExists) break;

        QY_MESSENGER_ID  idInfo_to = pDlgTalkVar->av.taskInfo.idInfo_starter;

        //
        QY_MESSENGER_ID  idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
        QY_MESSENGER_ID  idInfo_requester = pMisCnt->idInfo;

        //
        sendConfLayout(false, 0, CONST_imOp_phone_enlargeImg, &confLayoutParam, idInfo_imGrp_related, idInfo_requester, idInfo_to, _T(""));

        //

    } while (false);


   
}

void CDlgTalk_qt::video_curr_info(void* pContent) {

    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var)return;
    HWND  hMgr = mynull;
    if (isTalkerShadowMgr(pm_var->addr)) {
        hMgr = (HWND)this->winId();
    }
    else {
        TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
        hMgr = pShadowInfo->hMgr;
    }
    CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
    DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
    //  pDlgTalkVar->selDeviceId = pContentNew->confLayout.confLayoutParam.resp.curr_idinfo;


    IM_CONTENTU* pContent_new = (IM_CONTENTU*)pContent;
    if (pContent_new->confLayout.usOp == CONST_imOp_loseSel) {
        //说明是焦点取消了
        //is_curr = false;
        pDlgTalkVar->is_curr = false;
    }
    else {
        pDlgTalkVar->curr_idinfo = pContent_new->confLayout.confLayoutParam.resp.curr_idinfo;

        pDlgTalkVar->is_curr = true;
    }

    //  pContent_new->confLayout.confLayoutParam.resp.curr_idinfo;
     // int ii = 0;


}

//按键抓取
bool CDlgTalk_qt::eventFilter(QObject* target, QEvent* event)
{
#ifdef  __DEBUG__
#if 0
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var) return false;
    CCtxQyMc* pQyMc = g_pQyMc;
    int  iTalkSubtype = pm_var->iTalkerSubType;// CONST_talkerSubtype_video;
    HWND  m_hWnd_shadow;

    
    bool  bPrint = true;
    //
    if (isTalkerShadowMgr(pm_var->addr))bPrint = false;
    else {
        if (iTalkSubtype == 0) bPrint = false;
        else  if (iTalkSubtype == CONST_talkerSubtype_video) {
        }
        else {
            int  ii = 0;
        }
    }
    if (event->type() == QEvent::LayoutRequest)bPrint = false;
    if (event->type() == QEvent::Timer)bPrint = false;
    if (event->type() == QEvent::WindowDeactivate)bPrint = false;
    if (event->type() == QEvent::ShortcutOverride)bPrint = false;
    if (event->type() == QEvent::Paint)bPrint = false;
    if (event->type() == QEvent::Leave)bPrint = false;
    if (event->type() == QEvent::UpdateRequest)bPrint = false;
    if (event->type() == QEvent::Enter)bPrint = false;
 
    //  if (findTalker_shadow(pQyMc, pm_var->addr.idInfo.ui64Id, iTalkSubtype, &m_hWnd_shadow)) bPrint = false; 

       

    
    if  ( bPrint)
    {
        qDebug() << target;
        qDebug() << event->type();
    }

#endif

#endif

    static int i = 1;
	static QPoint pos;
	static QSize size;
   
    //
    if (event->type() == QEvent::KeyRelease) {
        if (target == this
            || target == ui->widgetVideoShow
            || target == ui->tableWidget
            )
        {
            if (record_widget.isEmpty())return false;

                QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
                int  int_item = ui->tableWidget->currentRow();
                if (int_item < 0)return false;

                if (keyEvent->key() == Qt::Key_Up)
                {
                    upDownKeyTable(record_widget, true);
                    return true;
                }
                else if (keyEvent->key() == Qt::Key_Down)
                {
                    upDownKeyTable(record_widget, false);
                    return true;
                }
            
        }
    }

    if (target == ui->sendMsg)
    {
      
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = (QKeyEvent*)event;
            if (keyEvent->key() == Qt::Key_Return && m_sendAction->isChecked())
            {
                on_btnSendImg_clicked();
                return true;
            }
            if (keyEvent->key() == Qt::Key_Return && (keyEvent->modifiers() & Qt::ControlModifier)
                && m_ctrlSendAction->isChecked())
            {
                on_btnSendImg_clicked();
                return true;
            }
        }
    }
    if (target == ui->widgetVideoShow)
    {
        //qDebug() << "widgetVideoShow:" << event->type();
     
        if (event->type() == QEvent::Resize)
        {

            ui->peerDesc->setGeometry(0, 0, ui->widgetVideoShow->width(), ui->widgetVideoShow->height());
            if (ui->bottomMenu->isVisible())
            {
                //ui->bottomMenu->setGeometry(ui->widgetVideoShow->width() - DEFAULT_VIDEO_WIDTH + 11, ui->widgetVideoShow->height() - ui->bottomMenu->height() - 24, DEFAULT_VIDEO_WIDTH - 24, ui->bottomMenu->height());
                ui->bottomMenu->setGeometry(ui->widgetVideoShow->width() - DEFAULT_VIDEO_WIDTH + 2, ui->widgetVideoShow->height() - ui->bottomMenu->height() - 24, DEFAULT_VIDEO_WIDTH - 6, ui->bottomMenu->height());
            }
            if (scrollArea_)
            {
                scrollArea_->setGeometry(0, 0, ui->peerDesc->width(), ui->peerDesc->height());
            }
        }
        
        /*
        if (event->type() == QEvent::MouseButtonDblClick)//当为双击事件时
        {
            i++;
            if (i % 2 == 0) //此处为双击一次全屏，再双击一次退出
            {
				pos = ui->peerDesc->pos();
				size = ui->peerDesc->size();

                //ui->peerDesc->setWindowFlags(Qt::Dialog);
                ui->peerDesc->showFullScreen();//全屏显示   

           }
            else
            {
                
                //ui->peerDesc->setWindowFlags(Qt::SubWindow);
                QRect rect;
                rect.setX(pos.x());
                rect.setY(pos.y());
                rect.setWidth(size.width());
                rect.setHeight(size.height());
                ui->peerDesc->setGeometry(rect);
                
                ui->peerDesc->showNormal();//退出全屏
            };

            //return true;

        }
        */
        
    }
    if (target == ui->peerDesc) {    
        
        if (event->type() == QEvent::MouseButtonPress)
        {
            record_widget = nullptr;
           
            DLG_TALK_var* pm_var = get_pm_var();

            //pm_var->av.peerZone.images.head.usCnt

            //pm_var->av.peerZone.images;

            
            //int width = ui->peerDesc->width();
            //int height = ui->peerDesc->height();

            //int widthShow = ui->widgetVideoShow->width();
            //int heightShow = ui->widgetVideoShow->height();

            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::RightButton) {

                /*
                
                MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
                if (pProcInfo) {
                    if (pProcInfo->m_ipcProc.op.idInfo.ui64Id > 0) {

                        MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
                        if (pMisCnt) {
                            //pProcInfo->m_ipcProc.op.idInfo.ui64Id = pMisCnt->idInfo.ui64Id;
                        }

                        on_showBallheadCamera_slots();
                    }
                }
                */
                

            }/* else if (mouseEvent->button() == Qt::LeftButton) {
                MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
                if (pProcInfo) {

                    if (pProcInfo->m_ipcProc.op.idInfo.ui64Id == 0)
                    {  

                        QPoint globalPos = mouseEvent->globalPos(); // 全局坐标
                        QPoint localPos = mouseEvent->pos(); // 部件内局部坐标
                        qDebug() << "Global Mouse Position: " << globalPos;
                        qDebug() << "Local Mouse Position: " << localPos;

                        DLG_TALK_var& m_var = *(DLG_TALK_var*)get_pm_var();
                        //m_var.av.peerZone.images;

                        //if (m_iW_dst > 0 && m_iH_dst > 0) {
                        //    int realX = (localPos.x() - m_iX_dst) * m_iW_org / m_iW_dst;
                        //    int realY = (localPos.y() - m_iY_dst) * m_iH_org / m_iH_dst;
                        //
                        //    qDebug() << "Video Position: " << realX << "," << realY;
                        //}

                        if (m_var.av.peerZone.images.head.usCnt > 0) {

                            if (m_var.av.peerZone.images.mems[0].iW_dst > 0 && m_var.av.peerZone.images.mems[0].iH_dst > 0) {
                                int realX = (localPos.x() - m_var.av.peerZone.images.mems[0].iX_dst) * m_var.av.peerZone.images.mems[0].iW_org / m_var.av.peerZone.images.mems[0].iW_dst;
                                int realY = (localPos.y() - m_var.av.peerZone.images.mems[0].iY_dst) * m_var.av.peerZone.images.mems[0].iH_org / m_var.av.peerZone.images.mems[0].iH_dst;

                                qDebug() << "Video Position: " << realX << "," << realY;

                                send_selLayoutType(realX, realY);

                                _isVideoAmplifier = true;

                                ui->toolBtnBall->setEnabled(true);
                            }

                        }
                    }
                }

                
            }*///

        }
        

        /*
        if (event->type() == QEvent::MouseButtonDblClick)
        {
            int width = ui->peerDesc->width();
            int height = ui->peerDesc->height();

            int widthShow = ui->widgetVideoShow->width();
            int heightShow = ui->widgetVideoShow->height();



            QMessageBox::StandardButton response = QMessageBox::question(nullptr, "标题", "这是一个消息框。",
                QMessageBox::Yes | QMessageBox::No);

            if (response == QMessageBox::Yes) {
                // 用户点击了"是"
            }
            else {
                // 用户点击了"否"
            }
        }
        */

        //
        if (event->type() == QEvent::Resize) {
            int  ii = 0;
            //
            refreshLayout();
        }
    }
    if (scrollArea_  )  {
#if  0
        if (target == scrollArea_) {
            int  ii = 0;
        }
        if (scrollArea_->widget() == target) {
            int  ii = 0;
        }
#endif
    }


    //
    return QWidget::eventFilter(target, event);
}

bool CDlgTalk_qt::event(QEvent* ev)
{
    if (ev->type() == QEvent::MouseMove)
    {
        bottom_bar_hide_timer_->stop();
        bottom_bar_hide_timer_->start();
        if (!ui->bottomMenu->isVisible())
        {
            //
            refreshBtns();
            //
            ui->bottomMenu->setVisible(true);
            //ui->bottomMenu->setGeometry(ui->widgetVideoShow->width() - DEFAULT_VIDEO_WIDTH + 11, ui->widgetVideoShow->height() - ui->bottomMenu->height() - 14, DEFAULT_VIDEO_WIDTH - 24, ui->bottomMenu->height());
            ui->bottomMenu->setGeometry(ui->widgetVideoShow->width() - DEFAULT_VIDEO_WIDTH + 2, ui->widgetVideoShow->height() - ui->bottomMenu->height() - 14, DEFAULT_VIDEO_WIDTH - 6, ui->bottomMenu->height());
        }
    }

    return QWidget::event(ev);
}

//
void CDlgTalk_qt::upDownKeyTable(QString record_widget , bool isUp)
{
    if (record_widget == "tableWidget") {
        if (isUp) {
            int  int_item = ui->tableWidget->currentRow();

            ui->tableWidget->selectRow(int_item - 1);
        }
        else {
            int  int_item = ui->tableWidget->currentRow();

            ui->tableWidget->selectRow(int_item + 1);
        }
    }
    else if (record_widget == "speakList") {
        if (isUp) {
            int  int_item = ui->speakList->currentRow();

            ui->speakList->selectRow(int_item - 1);
        }
        else {
            int  int_item = ui->speakList->currentRow();

            ui->speakList->selectRow(int_item + 1);
        }
    }
}


//双击全屏
/*
void CDlgTalk_qt::mouseDoubleClickEvent(QMouseEvent* event)
{
    DLG_TALK_var* pm_var = get_pm_var();
    if (pm_var->iTalkerSubType != CONST_talkerSubtype_video) return;

    static int i = 1;

	i++;
	if (i % 2 == 0) //此处为双击一次全屏，再双击一次退出
	{		
		ui->peerDesc->showFullScreen();//全屏显示   
	}
	else {	

		ui->peerDesc->showNormal();//退出全屏
	};


    slot_full_screen();
}

void CDlgTalk_qt::mousePressEvent(QMouseEvent* event)
{
    QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

    if (mouseEvent->button() == Qt::LeftButton) {
        MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
        if (pProcInfo) {

            if (pProcInfo->m_ipcProc.op.idInfo.ui64Id == 0)
            {

                QPoint globalPos = mouseEvent->globalPos(); // 全局坐标
                QPoint localPos = mouseEvent->pos(); // 部件内局部坐标
                qDebug() << "Global Mouse Position: " << globalPos;
                qDebug() << "Local Mouse Position: " << localPos;

                DLG_TALK_var& m_var = *(DLG_TALK_var*)get_pm_var();
                //m_var.av.peerZone.images;

                //if (m_iW_dst > 0 && m_iH_dst > 0) {
                //    int realX = (localPos.x() - m_iX_dst) * m_iW_org / m_iW_dst;
                //    int realY = (localPos.y() - m_iY_dst) * m_iH_org / m_iH_dst;
                //
                //    qDebug() << "Video Position: " << realX << "," << realY;
                //}

                if (m_var.av.peerZone.images.head.usCnt > 0) {

                    if (m_var.av.peerZone.images.mems[0].iW_dst > 0 && m_var.av.peerZone.images.mems[0].iH_dst > 0) {
                        int realX = (localPos.x() - m_var.av.peerZone.images.mems[0].iX_dst) * m_var.av.peerZone.images.mems[0].iW_org / m_var.av.peerZone.images.mems[0].iW_dst;
                        int realY = (localPos.y() - m_var.av.peerZone.images.mems[0].iY_dst) * m_var.av.peerZone.images.mems[0].iH_org / m_var.av.peerZone.images.mems[0].iH_dst;

                        qDebug() << "Video Position: " << realX << "," << realY;

                        send_selLayoutType(realX, realY);

                        _isVideoAmplifier = true;

                        ui->toolBtnBall->setEnabled(true);
                    }

                }
            }
        }


    }
}*/


void CDlgTalk_qt::mousePressEvent(QMouseEvent* event)
{
    
    if (event->pos().y() > 20) {

        if (event->button() == Qt::LeftButton) {
            if (m_clickTimer->isActive()) {
                m_clickTimer->stop();  // 如果定时器已经在运行，停止它并认为是双击
                qDebug() << "doubleClicked";
                m_dbClick = true;
                emit doubleClicked(event);  // 触发双击信号
            }
            else {
                //
                //qDebug() << "start click timer";
                //
                // Qt6中可以使用clone()方法
                m_event.reset(event->clone());  // 需要将m_event声明为QScopedPointer或std::unique_ptr
                //
                m_clickTimer->start(350);  // 否则启动定时器，等待400毫秒判断是否为双击
            }
        }
    }
    else {
        WinBasic::mousePressEvent(event);
    }
    
}

void CDlgTalk_qt::mouseReleaseEvent(QMouseEvent* event) {
    if (event->pos().y() > 20) {
        //
        //qDebug() << "mouseReleaseEvent";
        //
        if (event->button() == Qt::LeftButton && !m_clickTimer->isActive() && !m_dbClick) {
            //
            //qDebug() << "clicked";
            //emit clicked(event);
        }

        //
        m_dbClick = false;
    }
    else {
        WinBasic::mouseReleaseEvent(event);
    }
}


//



//
int  CDlgTalk_qt::sendRemotePtzCmd_3ddw(PTZ_cmdParam_3ddw  *  pParam)
{
    int  iErr = -1;
    CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

    //
    unsigned  int  uiObjType = 0;
    unsigned  short  usIndex_obj = 0;
    unsigned  short  usHelp_subIndex = 0;
    //
    unsigned  char	ucCmd = 0;
    unsigned  char  ucParam = 0;
    TCHAR	tBuf[128];
    //unsigned  char  ucMouseStatus = CONST_mouseStatus_lBtnDown;

    //  2016/07/19


    //
    QY_MESSENGER_ID  idInfo; idInfo = pProcInfo->m_ipcProc.op.idInfo;
    int  iChannel = pProcInfo->m_ipcProc.op.iChannel;

    int nResourceID = pProcInfo->m_ipcProc.op.nID;


    //
    QY_MESSENGER_ID  idInfo_imGrp_related = { 0 };

    //
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var)  return  -1;

    //
    QY_MESSENGER_ID  idInfo_to = pm_var->addr.idInfo;
    idInfo_to = pProcInfo->m_ipcProc.op.idInfo;

    do {

        //
        if (idInfo_to.ui64Id == pMisCnt->idInfo.ui64Id) {
            //  发送到mcu上去
            //HWND  hCurTalk = (HWND)m_pParent;
            HWND  hCurTalk = (HWND)this->winId();
            CHelp_getDlgTalkVar help_getDlgTalkVar;
            DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hCurTalk);
            if (!pCurVar)  break;
            HWND  hMgr = nullptr;
            if (isTalkerShadowMgr(pCurVar->addr)) {
                hMgr = hCurTalk;
            }
            else {
                TALKER_shadow* pShadow = (TALKER_shadow*)pCurVar->pShadowInfo;
                if (!pShadow) break;
                hMgr = pShadow->hMgr;
            }
            CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
            DLG_TALK_var* pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
            if (!pMgrVar)  break;
            //
            if (!pMgrVar->av.taskInfo.bTaskExists)  break;
            if (!pMgrVar->av.taskInfo.ucbVideoConference)  break;
            //
            idInfo_imGrp_related.ui64Id = pMgrVar->addr.idInfo.ui64Id;
            //
            idInfo_to = pMgrVar->av.taskInfo.idInfo_starter;

            //
        }

        //
        unsigned  char  ucMouseStatus = 0;

        //
        ucCmd = CONST_ptzCmd_3ddw;
        sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, (PTZ_cmdParamU*)pParam, idInfo_imGrp_related, idInfo_to);

        //
        iErr = 0;

    }  while (false);


    
    return  iErr;
}

//
void CDlgTalk_qt::onClicked(QMouseEvent* event)
{
	QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

    //
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var)  return;
    DLG_TALK_var& m_var = *pm_var;

    //
	if (mouseEvent->button() == Qt::LeftButton) {
		MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
		if (pProcInfo) {

            //
			//if (pProcInfo->m_ipcProc.op.idInfo.ui64Id == 0)
			{
				QPoint localPos = mouseEvent->pos(); // 部件内局部坐标

                //
                localPos = ui->peerDesc->mapFrom(this, localPos);

                //
#ifdef  __DEBUG__
#endif 


                //
				if (m_var.av.peerZone.images.head.usCnt > 0) {

                    CAP_image* pImg = &m_var.av.peerZone.images.mems[0];

					if (m_var.av.peerZone.images.mems[0].iW_dst > 0 && m_var.av.peerZone.images.mems[0].iH_dst > 0) {
						int realX = (localPos.x() - m_var.av.peerZone.images.mems[0].iX_dst) * m_var.av.peerZone.images.mems[0].iW_org / m_var.av.peerZone.images.mems[0].iW_dst;
						int realY = (localPos.y() - m_var.av.peerZone.images.mems[0].iY_dst) * m_var.av.peerZone.images.mems[0].iH_org / m_var.av.peerZone.images.mems[0].iH_dst;

						
                        TCHAR  tBuf[128];
                        _sntprintf(tBuf, mycountof(tBuf), _T("CDlgTalk_qt::onClicked realX=%d localPos.x()=%d iX_dst=%d; iW_org=%d iW_dst=%d"), 
                            realX, localPos.x(), m_var.av.peerZone.images.mems[0].iX_dst, m_var.av.peerZone.images.mems[0].iW_org , m_var.av.peerZone.images.mems[0].iW_dst);
                        showInfo_open0(0, 0, tBuf);
                        _sntprintf(tBuf, mycountof(tBuf), _T("CDlgTalk_qt::onClicked realY=%d localPos.y()=%d; iY_dst=%d iH_org=%d iH_dst=%d"), 
                            realY, localPos.y(), m_var.av.peerZone.images.mems[0].iY_dst, m_var.av.peerZone.images.mems[0].iH_org, m_var.av.peerZone.images.mems[0].iH_dst);
                        showInfo_open0(0, 0, tBuf);

                        //
                        if (bSupported_aiResize()) {
                            realX = realX / 4;
                            realY = realY / 4;
                        }


#ifdef  __DEBUG__
                        if (0) {
                            int realX1 = (localPos.x() - pImg->iX_dst) * pImg->iW_org / pImg->iW_i;
                            int realY1 = (localPos.y() - pImg->iY_dst) * pImg->iH_org / pImg->iH_i;

                            //if (this->isFullScreen()) 
                            {
                                //qDebug() << "Video Position: " << realX << "," << realY;
                                TCHAR  tBuf[128];
                                _sntprintf(tBuf, mycountof(tBuf), _T("Pos: realX %d, realY %d. realX1 %d, realY1 %d"), realX, realY, realX1, realY1);
                                showInfo_open0(0, 0, tBuf);
                            }

                        }
#endif 

                        //
						send_selLayoutType(realX, realY);

						_isVideoAmplifier = true;

						ui->toolBtnBall->setEnabled(true);
					}

				}
			}
		}


	}

    //
    if (m_b3ddw) {
        do  {
        QPoint localPos = mouseEvent->pos(); // 部件内局部坐标
        qDebug() << "clicked: Mouse Position: " << localPos;
        //
        QPoint peerPos  =  ui->peerDesc->mapFrom(this, localPos);
        //
        qDebug() << "peer Position: " << peerPos;

        //
        CAP_IMAGES* pImgs = &m_var.av.peerZone.images;
        qDebug() << "cnt " << pImgs->head.usCnt << " iX_dst " << pImgs->mems[0].iX_dst << " iY_dst " << pImgs->mems[0].iY_dst;
        //
        if (pImgs->head.usCnt > 0) {

            if (pImgs->mems[0].iW_dst > 0 && pImgs->mems[0].iH_dst > 0) {
                int realX = (peerPos.x() - pImgs->mems[0].iX_dst) * pImgs->mems[0].iW_org / pImgs->mems[0].iW_dst;
                int realY = (peerPos.y() - pImgs->mems[0].iY_dst) * pImgs->mems[0].iH_org / pImgs->mems[0].iH_dst;

                qDebug() << "myVideo Position: " << realX << "," << realY;

                //
                if (realX < 0 || realY < 0)  break;
                if (realX > pImgs->mems[0].iW_org)  break;
                if (realY > pImgs->mems[0].iH_org)  break;

                //
                PTZ_cmdParam_3ddw  param = { 0 };

                //
                param.sW_video = pImgs->mems[0].iW_org;
                param.sH_video = pImgs->mems[0].iH_org;

                //                
                param.xTop = realX - 20;  if (param.xTop < 0)  param.xTop = 0;
                param.yTop = realY - 20;  if (param.yTop < 0)  param.yTop = 0;
                param.xBottom = realX + 20;  if (param.xBottom > param.sW_video)  param.xBottom = param.sW_video;
                param.yBottom = realY + 20;  if (param.yBottom > param.sH_video)  param.yBottom = param.sH_video;//方框结束点的y坐标


                //send_selLayoutType(realX, realY);

                sendRemotePtzCmd_3ddw(&param);


                //



            }
        }

        } while (false);


    }

    return;
}

void CDlgTalk_qt::onDoubleClicked(QMouseEvent* event)
{
	DLG_TALK_var* pm_var = get_pm_var();
	if (pm_var->iTalkerSubType != CONST_talkerSubtype_video) return;

	static int i = 1;

	i++;
	if (i % 2 == 0) //此处为双击一次全屏，再双击一次退出
	{
		ui->peerDesc->showFullScreen();//全屏显示   
	}
	else {

		ui->peerDesc->showNormal();//退出全屏
	};


	slot_full_screen();
}

void CDlgTalk_qt::sizeOriginalVideo()
{
    QRect rc = QApplication::primaryScreen()->geometry();
    int ry;
    int rx;
    QRect r;

    int dis_height =  COUNT_display_height_value;
    int dis_width =  COUNT_display_width_value;

    if (rc.height() < dis_height && rc.width() > dis_width) {
        rx = rc.width() - DEFAULT_VIDEO_WIDTH_768;
        ry = (rc.height() - DEFAULT_VIDEO_HEIGHT_768) / 2;
        //
        if (ry > 80)  ry -= 80;
        else  ry = 0;
        //
        r = QRect(rx, ry, DEFAULT_VIDEO_WIDTH_768, DEFAULT_VIDEO_HEIGHT_768);
    }
    else {

        int rx = rc.width()- DEFAULT_VIDEO_WIDTH-1;
        int ry = (rc.height() - DEFAULT_VIDEO_HEIGHT) / 2;
        //
        if (ry > 100)ry -= 100;
        else  ry = 0;

        r = QRect(rx, ry, DEFAULT_VIDEO_WIDTH, DEFAULT_VIDEO_HEIGHT);
    }

    setVisible(true);
    this->setGeometry(r);
    /*QPoint windowPos;
    QSize windowSize;
    m_pWinTitle->getRestoreInfo(windowPos, windowSize);
    this->setGeometry(QRect(windowPos, windowSize));*/
}

//
QString CDlgTalk_qt::separateEmotion(QString allmsg)
{
    QString gap = "&#";
    QRegularExpression r;
#ifndef  __DEBUG__
    //r.setPatternSyntax(QRegExp::RegExp);
#endif
    //
    r.setPattern("&#[A-Za-z0-9][A-Za-z0-9][A-Za-z0-9][A-Za-z0-9][A-Za-z0-9][A-Za-z0-9];");
    QString result = "";
    QStringList strList = allmsg.split(gap); // &#x1f9d0;
    QString sprefix = "<span class=\"emo\">";
    QString snfix = "</span>";
    if (strList.size() > 0)
    {
        result += strList[0];
    }
    if (strList.size() > 1)
    {
        for (int i = 1; i < strList.size(); i++)
        {
            strList[i] = gap + strList[i];
            int pos = 0;
            QString temp_mid = strList[i].mid(pos, 9);
            QString temp_right = strList[i].mid(pos + 9);
            result += sprefix + temp_mid + snfix + temp_right;
        }
    }
    return result;
}

//申请发言
void CDlgTalk_qt::on_SpeakBtn_click() {
    //


        // TODO: Add your control notification handler code here
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    if (!pProcInfo)  return;
    FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
    if (!pFuncs)  return;

    //
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var) return;
    if (isTalkerShadowMgr(pm_var->addr)) return;
    TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
    HWND  hMgr = pShadowInfo->hMgr;

    //
    CHelp_getDlgTalkVar	help_getDlgTalkVar;
    DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hMgr, _T("dlgIa::OnBnClickedrequest"));
    if (!pDlgTalkVar)  return;

    if (!pDlgTalkVar->av.taskInfo.bTaskExists)  return;

    //  2014/07/26
    //CWaitCursor	cur;

    //  2010/09/02
    pFuncs->pf_setCurSharedObjUsr_localAv(pProcInfo, pDlgTalkVar->av.iIndex_sharedObj_localAv, pDlgTalkVar->av.iIndex_usr_localAv);

    //
    bool  canSpeak = dlgTalk_canSpeak(hMgr);


    //
    //  requestToSpeak(  !m_var.canSpeak  );
    pFuncs->pf_dlgTalk_requestToSpeak(hMgr, !canSpeak,  true);
    
    //
    QString qstr;
    qstr = canSpeak ? u8"发言" : u8"静音";
   /* WinPromptDlgBox promptBox;
    promptBox.setMsg(u8"测试信息");
    QTimer::singleShot(5000, &promptBox, SLOT(close()));
    promptBox.show();
    promptBox.exec();*/

    ui->toolBtnSpeak->setText(qstr);


    //
#ifdef  __DEBUG__
        //traceLog(_T("m_var.canSpeak %d. dlgTalk.canSpeak %d"), m_var.canSpeak, dlgTalk_canSpeak(m_var.guiData.param.hMgrTalk));
#endif



}

int getTitleBarHeight(const QWidget* widget) {
    const int titleBarHeight = widget->style()->pixelMetric(QStyle::PM_TitleBarHeight);
    return titleBarHeight;
}

void CDlgTalk_qt::moveEvent(QMoveEvent* event) {  
    

    if (m_pControlPtz)
    {
        int titleHeight = getTitleBarHeight(this);

        QPoint parentTopRight = this->geometry().topRight(); // 获取父窗口右上角的位置
        QRect rect = m_pControlPtz->geometry();
        QPoint popupPosition(parentTopRight.x() - rect.width(), parentTopRight.y() + titleHeight); // 计算弹出窗口的位置，这里可能需要调整以避免超出屏幕边界

        // 设置弹出窗口的几何属性
        QSize size;
        size.setWidth(rect.width());
        size.setHeight(rect.height());
        m_pControlPtz->setGeometry(QRect(popupPosition, size));
    }

    // 你可以在这里添加更多的处理代码
}

//显示远程云台控制窗口
void CDlgTalk_qt::on_showControlPtz_slots(const QString& name) {

    //
    if (!m_pControlPtz)
    {
        if (name.contains(u8"3D")) {
            m_b3ddw = true;
        }

        m_pControlPtz = new CDlgControlPtz(m_b3ddw, this);

        int titleHeight = getTitleBarHeight(this);

        QPoint parentTopRight = this->geometry().topRight(); // 获取父窗口右上角的位置
        QRect rect = m_pControlPtz->geometry();
        QPoint popupPosition(parentTopRight.x() - rect.width(), parentTopRight.y() + titleHeight); // 计算弹出窗口的位置，这里可能需要调整以避免超出屏幕边界

        // 设置弹出窗口的几何属性
        QSize size;
        size.setWidth(rect.width());
        size.setHeight(rect.height());
        m_pControlPtz->setGeometry(QRect(popupPosition, size));


        m_pControlPtz->show();
#if 0
        //本地
        m_pControlPtzLocal = new CDlgControlPtzLocal();
#endif 



    }

}

void CDlgTalk_qt::on_click3dPtz_slots(bool state)
{
    m_b3ddw = state;
}

//关闭云台控制窗口
void CDlgTalk_qt::on_closeControlPtz_slots()
{
    if (m_pControlPtz)
    {
        m_pControlPtz->close();
        if (m_pControlPtz)
        {
            delete m_pControlPtz;
            m_pControlPtz = nullptr;
        }
    }
    /*if (m_pControlPtzLocal)
    {
        m_pControlPtzLocal->close();
        delete m_pControlPtzLocal;
        m_pControlPtzLocal = nullptr;
    }*/

}



//显示球机列表窗口 
void CDlgTalk_qt::on_showBallheadCamera_slots()
{
    //
    if (!m_pBallheadCamera)
    {
        m_pBallheadCamera = new CDlgBallheadCamera(this);

    }

    //
    if (!m_pBallheadCamera->isVisible()) {

        //窗口只打开一次
        m_pBallheadCamera->show();

        //_is_infrared = true;
        //
       // infraredMenu_quit();

    }
    else {
        m_pBallheadCamera->close();
        if (m_pBallheadCamera)
        {
            delete m_pBallheadCamera;
            m_pBallheadCamera = nullptr;
        }
        //_is_infrared = false;
        // on_closePortSetting_slots();
    }
    //

}
//关闭球机列表窗口
void CDlgTalk_qt::on_closeBallheadCamera_slots()
{
    if (m_pBallheadCamera)
    {
        m_pBallheadCamera->close();
        if (m_pBallheadCamera)
        {
            delete m_pBallheadCamera;
            m_pBallheadCamera = nullptr;
        }
    }
    //
    //_is_infrared = false;
}


void  CDlgTalk_qt::doEndAv()
{
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    if (!pProcInfo)  return;
    FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
    if (!pFuncs)  return;

    //
    HWND  hCur = (HWND)this->winId();

    //
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var)return;
    if (isTalkerShadowMgr(pm_var->addr)) return;
    TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
    HWND  hMgr = pShadowInfo->hMgr;

    CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
    DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
    if (!pDlgTalkVar)return;

    if (!pDlgTalkVar->av.taskInfo.bTaskExists)  return;

    //
    HWND  hDlgTalk = hMgr;


    //    
    int  iTaskId = pDlgTalkVar->guiData.av.iTaskId;
    int  iStatus = pDlgTalkVar->guiData.av.iStatus;
    switch (iStatus) {
    case  CONST_imTaskStatus_req:
    case  CONST_imTaskStatus_acceptedByReceiver:
    case  CONST_imTaskStatus_dualByReceiver: {
#if  0
        G_guiData_qyMc* pGuiData = pFuncs->pf_get_g_guiData();
        PF_MessageBox	pf = (PF_MessageBox)pGuiData->pf_MessageBox;
        MACRO_qyAssert(pf, _T("pf_MessageBox is null"));
        if (pf(hDlg, getResStr(0, &pQyMc->cusRes, CONST_resId_areYouSure), _T("www.qycx.com"), MB_OKCANCEL) != IDOK)  goto  errLabel;
#endif
        //QMessageBox()

        //
        PARAM_dlgTalk_procTask  param;
        memset(&param, 0, sizeof(param));
        pFuncs->pf_dlgTalk_procTask1(hDlgTalk, iTaskId, CONST_imOp_send_cancel, NULL, &param);

        //

    }
                                           break;
    case  CONST_imTaskStatus_applyToRecv:
    case  CONST_imTaskStatus_waitToRecv:
    case  CONST_imTaskStatus_resp: 
    //
    case  CONST_imTaskStatus_canceledByReceiver:
    {
#if 0
        G_guiData_qyMc* pGuiData = pFuncs->pf_get_g_guiData();
        PF_MessageBox	pf = (PF_MessageBox)pGuiData->pf_MessageBox;
        MACRO_qyAssert(pf, _T("pf_MessageBox is null"));
        if (pf(hDlg, getResStr(0, &pQyMc->cusRes, CONST_resId_areYouSure), _T("www.qycx.com"), MB_OKCANCEL) != IDOK)  goto  errLabel;
#endif

        PARAM_dlgTalk_procTask  param;
        memset(&param, 0, sizeof(param));
        pFuncs->pf_dlgTalk_procTask1(hDlgTalk, iTaskId, CONST_imOp_recv_cancel, NULL, &param);


    }
                                 break;
    default:
        break;

    }

    return;
}



//结束会议
void  CDlgTalk_qt::on_EndAvBtn_click() {
    //
    HWND  hCur = (HWND)this->winId();

    //
    doEndAv();

    //
    showInfo_open0(0, mynull, _T("endAv: close talk_video now"));
    PostMessage(hCur, WM_CLOSE, 0, 0);

    //
    return;
}

void CDlgTalk_qt::send_selLayoutTypeCancel() {

    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (!pMisCnt)  return;

    ConfLayoutParam  confLayoutParam = { 0 };
    //confLayoutParam = pTc->videoConference.confLayoutParam;
    //if (!confLayoutParam.ui64Id)  break;
    //

    confLayoutParam.phoneEnlargeParam.x = 0;
    confLayoutParam.phoneEnlargeParam.y = 0;

    /*
   if (str.isEmpty()) return;
   QStringList list = str.split("|");

   confLayoutParam.enlargeParam.usEnlargeType = CONST_enlargeType_img;
   confLayoutParam.enlargeParam.ui64Id = pProcInfo->m_ipcProc.op.idInfo.ui64Id;
   confLayoutParam.ipcParam.iChannel = list[0].toInt();
   pProcInfo->m_ipcProc.op.iChannel = list[0].toInt();*/

    CHelp_getDlgTalkVar help_getDlgTalkVar;
    CDlgTalk_qt* pWin_cdlgtalk = this;

    DLG_TALK_var* pm_var = pWin_cdlgtalk->get_pm_var();
    if (!pm_var)return;
    if (isTalkerShadowMgr(pm_var->addr)) return;
    TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
    HWND  hMgr = pShadowInfo->hMgr;

    do {

        //DLG_TALK_var* pDlgTalkVar = pWin_cdlgtalk->get_pm_var();
        DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hMgr);
        if (!pDlgTalkVar)break;
        if (!isTalkerShadowMgr(pDlgTalkVar->addr)) break;
        if (!pDlgTalkVar->av.taskInfo.bTaskExists) break;

        QY_MESSENGER_ID  idInfo_to = pDlgTalkVar->av.taskInfo.idInfo_starter;

        //
        QY_MESSENGER_ID  idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
        QY_MESSENGER_ID  idInfo_requester = pMisCnt->idInfo;

        //
        sendConfLayout(false, 0, CONST_imOp_phone_cancelEnlargeImg, &confLayoutParam, idInfo_imGrp_related, idInfo_requester, idInfo_to, _T(""));

        //

    } while (false);

    _isVideoAmplifier = false; //记录菜单变化

    //on_showBallheadCamera_slots();
    if(m_pBallheadCamera)
        m_pBallheadCamera->close();

    pWin_cdlgtalk->on_closeControlPtz_slots(); //关闭云台窗口

}

void CDlgTalk_qt::on_toolBtnHome_click() {

    if (_isVideoAmplifier) {
        send_selLayoutTypeCancel();
        ui->toolBtnBall->setEnabled(false);
        ui->toolBtnControl->setEnabled(false);
    }
    else {
         send_selLayoutTypeCancel();
    }

    

}

#define		CONST_ALL_Txt			u8"切换布局"


void CDlgTalk_qt::send_selLayoutType(QString str) {

    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (!pMisCnt)  return;

    ConfLayoutParam  confLayoutParam = { 0 };
    //confLayoutParam = pTc->videoConference.confLayoutParam;
    //if (!confLayoutParam.ui64Id)  break;
    //
    if (str.isEmpty()) return;
    QStringList list = str.split("|");

    confLayoutParam.enlargeParam.usEnlargeType = CONST_enlargeType_img;
    confLayoutParam.enlargeParam.ui64Id = pProcInfo->m_ipcProc.op.idInfo.ui64Id;
    confLayoutParam.ipcParam.iChannel = list[0].toInt();
    pProcInfo->m_ipcProc.op.iChannel = list[0].toInt();

    CHelp_getDlgTalkVar help_getDlgTalkVar;
    CDlgTalk_qt* pWin_cdlgtalk = this;

    DLG_TALK_var* pm_var = pWin_cdlgtalk->get_pm_var();
    if (!pm_var)return;
    if (isTalkerShadowMgr(pm_var->addr)) return;
    TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
    HWND  hMgr = pShadowInfo->hMgr;

    do {

        //DLG_TALK_var* pDlgTalkVar = pWin_cdlgtalk->get_pm_var();
        DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hMgr);
        if (!pDlgTalkVar)break;
        if (!isTalkerShadowMgr(pDlgTalkVar->addr)) break;
        if (!pDlgTalkVar->av.taskInfo.bTaskExists) break;

        QY_MESSENGER_ID  idInfo_to = pDlgTalkVar->av.taskInfo.idInfo_starter;

        //
        QY_MESSENGER_ID  idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
        QY_MESSENGER_ID  idInfo_requester = pMisCnt->idInfo;

        //CONST_imOp_phone_enlargeChannel
        //sendConfLayout(false ,0, CONST_imOp_enlargeChannel, &confLayoutParam, idInfo_imGrp_related, idInfo_requester, idInfo_to, _T(""));
        sendConfLayout(false, 0, CONST_imOp_enlargeChannel, &confLayoutParam, idInfo_imGrp_related, idInfo_requester, idInfo_to, _T(""));

        //

    } while (false);


    //on_btnBall_close_clicked();


    QString tmp_str = list[2];
    //调出云台窗口
    if (tmp_str.contains(u8"球机") || tmp_str.contains(u8"3D") || tmp_str.contains(u8"布控球")) {
        pWin_cdlgtalk->on_showControlPtz_slots(tmp_str);
        //ui->toolBtnBall->setEnabled(true);
        ui->toolBtnControl->setEnabled(true);
       
    }
    else {
        //ui->toolBtnBall->setEnabled(false);
        pWin_cdlgtalk->on_closeControlPtz_slots();
        ui->toolBtnControl->setEnabled(false);
    }
}


void CDlgTalk_qt::ShowListMenu() {
    m_menuBall->hide();
    m_menuBall->clear();

    TCHAR  tBuf[256];


    QY_MC* pQyMc = QY_GET_GBUF();
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

    NvrInfo* pNvrInfo = &pProcInfo->m_ipcProc.op.nvrInfo;

    if (pNvrInfo->usCnt > 0) {
        QAction* actionAll = m_menuBall->addAction(CONST_ALL_Txt);
        _sntprintf(tBuf, mycountof(tBuf), _T("%d|%S|%s"), -1, "", _T("(所有)"));
        actionAll->setData(QVariant::fromValue(QString::fromWCharArray(tBuf)));

        QObject::connect(actionAll, &QAction::triggered, [=]() {
            QVariant data = actionAll->data();
            QString val = data.toString();
            send_selLayoutType(val);
            });
    }


    for (int i = 0; i < pNvrInfo->usCnt; i++) {
        IpcInfo* pMem = &pNvrInfo->mems[i];

        _sntprintf(tBuf, mycountof(tBuf), _T("%s"), pMem->name);
        QString qstring = QString::fromWCharArray(tBuf);
        QAction* action = m_menuBall->addAction(qstring);

        _sntprintf(tBuf, mycountof(tBuf), _T("%d|%S|%s"), pMem->iChannel, pMem->ip, pMem->name);
        action->setData(QVariant::fromValue(QString::fromWCharArray(tBuf)));

        QObject::connect(action, &QAction::triggered, [=]() {
            QVariant data = action->data();
            QString val = data.toString();
            send_selLayoutType(val);
            });
    }

    QPoint pos;
    pos.setX(0);
    pos.setY(-m_menuBall->sizeHint().height() - 6);

    //m_menuBall->exec(ui->toolBtnBall->mapToGlobal(pos));
    //QPoint pos2 = ui->toolBtnBall->mapToGlobal(QPoint(0, ui->toolBtnBall->height()));

    m_menuBall->popup(ui->toolBtnBall->mapToGlobal(pos));
}

void CDlgTalk_qt::on_toolBtnBall_click() {
   
    ShowListMenu();
    
}

void CDlgTalk_qt::on_toolBtnControl_click() {

    if (!m_pControlPtz)
    {
        m_pControlPtz = new CDlgControlPtz(m_b3ddw, this);

        int titleHeight = getTitleBarHeight(this);

        QPoint parentTopRight = this->geometry().topRight(); // 获取父窗口右上角的位置
        QRect rect = m_pControlPtz->geometry();
        QPoint popupPosition(parentTopRight.x() - rect.width(), parentTopRight.y() + titleHeight); // 计算弹出窗口的位置，这里可能需要调整以避免超出屏幕边界

        // 设置弹出窗口的几何属性
        QSize size;
        size.setWidth(rect.width());
        size.setHeight(rect.height());
        m_pControlPtz->setGeometry(QRect(popupPosition, size));


        m_pControlPtz->show();
#if 0
        //本地
        m_pControlPtzLocal = new CDlgControlPtzLocal();
#endif 



    }
    else {
        m_pControlPtz->close();
        if (m_pControlPtz)
        {
            delete m_pControlPtz;
            m_pControlPtz = nullptr;
        }
    }

}



//屏幕共享
void CDlgTalk_qt::on_toolBtnScreen_click() {

    CCtxQyMc* pQyMc = g_pQyMc;
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    if (!pProcInfo)  return;
    FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
    if (!pFuncs)  return;

    //
    HWND  hCurTalk = (HWND)this->winId();

    //
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var)return;
    if (isTalkerShadowMgr(pm_var->addr)) return;
    TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
    HWND  hMgr = pShadowInfo->hMgr;

    CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
    DLG_TALK_var* pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
    if (!pMgrVar)return;
    TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;

    HWND  hDlgTalk = hMgr;
    QString qstr;

    //
    if (!pMgrVar->av.taskInfo.bTaskExists) {
        //  qyMessageBox(  hDlg,  _T(  "Please start meeting, before sharing screen"  ),  _T(  "qyMessenger"  ),  MB_OK,  5,  NULL  );
        //qyMessageBox(hDlg, getResStr(0, &pQyMc->cusRes, CONST_resId_startMeetingFirstly), _T("qyMessenger"), MB_OK, 5, NULL);
        goto  errLabel;// break;
    }

    //

    //
    if (!pShadowMgr->resourcesInfo.info_send.nScreens) {
        //	
        TCHAR  tBuf[128];
        if (isActiveMemsFull(pMgrVar->av.taskInfo.iTaskId, false))
        {
            _sntprintf(tBuf, mycountof(tBuf), _T("too many speakers. you cant share screen now"));
            showNotification(0, 0, 0, 0, 0, 0, tBuf);
            goto  errLabel;
        }

        //
#if  0
        BOOL				bNoPrompt = bNoPrompt_selectAvCompressor(CONST_capType_screen, 0);
        //  2014/05/05
        if (!bNoPrompt) {
            if (pProcInfo->viewDlgSelectAvCompressor(hCurTalk, hCurTalk, CONST_capType_screen, 0, FALSE, FALSE, 0) != IDOK)  goto  errLabel;
        }
#endif
        //
        pFuncs->pf_toSelectRegion1(hDlgTalk, TRUE, FALSE, FALSE, 0, -1);
        //  2019/05/06
        PostMessage(hCurTalk, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
        //PostMessage(pQyMc->gui.hGuiWnd, WM_CLOSE, 0, NULL);
        PostMessage(pQyMc->gui.hMainWnd, WM_SYSCOMMAND, SC_MINIMIZE, NULL);

        //
        qstr = QString::fromUtf16((char16_t*)getResStr(0, &pQyMc->cusRes, CONST_resId_cancelScreenSharing));
        ui->toolBtnScreen->setText(qstr);

        }
    else {
        PARAM_dlgTalk_procTask  param;
        memset(&param, 0, sizeof(param));

        //pFuncs->pf_dlgTalk_procTask1(  hDlgTalk,  pMsgTask->iTaskId,  CONST_imOp_send_cancel,  NULL,  &param  );						
        pFuncs->pf_dlgTalk_procCmd(hDlgTalk, ID_menuItemIdc_shareFullScreen, 0, CONST_imOp_send_cancel, NULL, &param);

        //        
        qstr = QString::fromUtf16((char16_t*)getResStr(0, &pQyMc->cusRes, CONST_resId_screenSharing));
        ui->toolBtnScreen->setText(qstr);
    }

errLabel:

    return;
    }

//设备共享
void CDlgTalk_qt::slot_device_screen() {
        CCtxQyMc* pQyMc = g_pQyMc;
        MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
        if (!pProcInfo)  return;
        FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
        if (!pFuncs)  return;

        //
        HWND  hCurTalk = (HWND)this->winId();

        //
        DLG_TALK_var* pm_var = get_pm_var();
        if (!pm_var)return;
        if (isTalkerShadowMgr(pm_var->addr)) return;
        TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
        HWND  hMgr = pShadowInfo->hMgr;

        CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
        DLG_TALK_var* pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
        if (!pMgrVar)return;
        TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;

        HWND  hDlgTalk = hMgr;
        QString qstr;

        //
        if (!pMgrVar->av.taskInfo.bTaskExists) {
            //  qyMessageBox(  hDlg,  _T(  "Please start meeting, before sharing screen"  ),  _T(  "qyMessenger"  ),  MB_OK,  5,  NULL  );
            //qyMessageBox(hDlg, getResStr(0, &pQyMc->cusRes, CONST_resId_startMeetingFirstly), _T("qyMessenger"), MB_OK, 5, NULL);
            goto  errLabel;// break;
        }

            //
        int iMenuId; iMenuId = ID_startShareMediaDevice_unresizable;

            //
            if (!pShadowMgr->resourcesInfo.info_send.nMediaFiles_unresizable) {

                //	
                TCHAR  tBuf[128];
                if (isActiveMemsFull(pMgrVar->av.taskInfo.iTaskId, false))
                {
                    _sntprintf(tBuf, mycountof(tBuf), _T("too many speakers. you cant share screen now"));
                    showNotification(0, 0, 0, 0, 0, 0, tBuf);
                    goto  errLabel;
                }

                //
                TCHAR  tDev[256];  tDev[0] = 0;

                /*getCfgValByNameT(pProcInfo->cfg.smCfgFile, (TCHAR*)CONST_cfgName_sm_devAsScreen, tDev, mycountof(tDev));
                tTrim(tDev);*/
                QString rootKey_qt_av = CONST_rootKey_sm_init;
                QSettings* regQt = new QSettings(rootKey_qt_av, QSettings::NativeFormat);
                QString currCapture =  regQt->value(CONST_regValName_capture_selected).toString();
                 safeTcsnCpy((TCHAR*)currCapture.utf16(), tDev, mycountof(tDev));
                delete regQt;

                //
                dlgTalk_shareMediaDevice(hDlgTalk, 0, CONST_subCapType_unresizable, tDev);

                //
                _is_device_screen = true;
                emit to_device_screen_status(true);
            }
            else {
                PARAM_dlgTalk_procTask  param;
                memset(&param, 0, sizeof(param));

                //pFuncs->pf_dlgTalk_procTask1(  hDlgTalk,  pMsgTask->iTaskId,  CONST_imOp_send_cancel,  NULL,  &param  );						
                pFuncs->pf_dlgTalk_procCmd(hDlgTalk, iMenuId, 0, CONST_imOp_send_cancel, NULL, &param);
                _is_device_screen = false;
                emit to_device_screen_status(false);
            }
        
    errLabel:

        return;

}

//点击更多菜单
void CDlgTalk_qt::on_MoreBtn_clicked() {


    QToolButton* button = ui->toolBtnMore;
    QPoint pt = button->mapToGlobal(QPoint{ 0,0 });
    pt.setX(pt.x() + button->width() / 2);
    pt.setY(pt.y() - 2);

    CDlgTalkMoreMenu* dlg = CDlgTalkMoreMenu::showDialog(pt,_is_device_screen);
    connect(dlg, &CDlgTalkMoreMenu::signal_full_screen, this, &CDlgTalk_qt::slot_full_screen);
    connect(dlg, &CDlgTalkMoreMenu::signal_this_video, this, &CDlgTalk_qt::slot_this_video);
    connect(dlg, &CDlgTalkMoreMenu::signal_device_select, this, &CDlgTalk_qt::slot_device_select);
    connect(dlg, &CDlgTalkMoreMenu::signal_grp_members, this, &CDlgTalk_qt::slot_grp_members);
    connect(dlg, &CDlgTalkMoreMenu::signal_dish_select, this, &CDlgTalk_qt::on_btnDisk_clicked);
    connect(dlg, &CDlgTalkMoreMenu::signal_make_list, this, &CDlgTalk_qt::slot_make_list);
    connect(dlg, &CDlgTalkMoreMenu::signal_controller, this, &CDlgTalk_qt::slot_conference_controller);
    connect(dlg, &CDlgTalkMoreMenu::signal_device_screen_close, this, &CDlgTalk_qt::slot_device_screen);
    connect(dlg, &CDlgTalkMoreMenu::signal_device_screen, this, &CDlgTalk_qt::slot_devic_screen_select);
    connect(this, SIGNAL(to_device_screen_status(bool)), dlg, SLOT(up_device_screen_status(bool)));


    //判断个人还是群组
    DLG_TALK_var* pm_var = get_pm_var();
    
    unsigned  int  uiObjType = 0;

    getTalkerDesc(pm_var->addr.idInfo,&uiObjType,mynull,0,mynull,0,0,mynull,mynull,mynull,mynull);
    if (uiObjType != CONST_objType_imGrp)
    {
        dlg->isShowBtnMake(false); 
        dlg->isShowBtnMember(false);
        dlg->isShowBtnController(false);
    }
    
}

void CDlgTalk_qt::slot_full_screen()
{
    if (this->isFullScreen())
    {
        ui->widgetTitle->setVisible(true);
        ui->widgetTitle->show();
        ui->verticalLayout->setContentsMargins(1, 1, 1, 1);
        this->showNormal();
        //
#if 0
        if (scrollArea_)
        {
            scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
            scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        }
#endif
        //
        return;
    }
    ui->widgetTitle->setVisible(false);
  //  ui->widgetMsgArea->setVisible(false);
   // ui->conferenceController->setVisible(false);
    if (scrollArea_)
    {
        scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    }
    ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
    this->showFullScreen();
}

//显示本地隐藏
void  CDlgTalk_qt::slot_this_video()
{
    if (ui->meDesc->isVisible())
    {
        ui->meDesc->setVisible(false);
        ui->lab_io->setVisible(false);
    }
    else {
        ui->meDesc->setVisible(true);
        ui->lab_io->setVisible(true);
    }
}

//摄像头麦克风设备列表
void CDlgTalk_qt::slot_device_select()
{
    DeviceSelectDialog::showDialog(this);
}

//设备屏幕共享设备列表
void  CDlgTalk_qt::slot_devic_screen_select() 
{
   ScreenDeviceSelect * device_dlg =  ScreenDeviceSelect::showDialog(this);
   connect(device_dlg, &ScreenDeviceSelect::signals_screen_device_selecct_ok, this, &CDlgTalk_qt::slot_device_screen);

}

//点击群成员
void CDlgTalk_qt::slot_grp_members() 
{
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var)return ;
    
    //CDlgTalk_grp_members::showDialog(this);
    CDlgTalk_grp_members::getDialog(this);
    CDlgTalk_grp_members::showWnd();
    CDlgTalk_grp_members::setContent(QString::number(pm_var->addr.idInfo.ui64Id));
 
}

//显示发言人列表
void CDlgTalk_qt::slot_make_list() {
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var)return;

    CDlgTalk_speaker_list::getDialog(this);
    CDlgTalk_speaker_list::showWnd();
    CDlgTalk_speaker_list::setContent(QString::number(pm_var->addr.idInfo.ui64Id));
}

//会议控制
void CDlgTalk_qt::slot_conference_controller() 
{
    if (ui->conferenceController->isVisible()) {
        ui->conferenceController->setVisible(false);
        disconnect(ui->speakList, 0, 0, 0);
        disconnect(ui->tableWidget, 0, 0, 0);
        if (scroll_bar_update_timer_) {
            delete scroll_bar_update_timer_;
            scroll_bar_update_timer_ = nullptr;
        }
        if (scrollArea_)
        {
            scrollArea_->setGeometry(0, 0, ui->peerDesc->width(), ui->peerDesc->height());
        }

        //
        if (this->windowState() == Qt::WindowState::WindowMaximized || this->windowState() == Qt::WindowState::WindowFullScreen)
        {
            if (this->windowState() == Qt::WindowState::WindowFullScreen && scrollArea_)
            {
                //scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
                //scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
            }
            return;
        }


        QTimer::singleShot(50, [this]() {
            this->move(this->pos().x() + 400, this->pos().y());
            this->resize(this->width() - 400, this->height());
            });
    }
    else {
        QSize sz = this->size();

        //
        CCtxQyMc* pQyMc = g_pQyMc;
        CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();

        if (!pProcInfo)  return;
        MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
        //
        pProcInfo->m_var.hTalk_video = (HWND)this->winId();
        //
        ui->conferenceController->setFixedWidth(400);
        CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
        // QtConcurrent::run(this,&CDlgTalk_qt::initconfMem);
        // QMetaObject::invokeMethod(this, "initconfMem", Qt::DirectConnection);

        //ui->label_staticInitiator->setText(u8"发起人：");
        //ui->label_staticCompere->setText(u8"主持人：");
        HWND  hDlgTalk = (HWND)this->winId();

        DLG_TALK_var* pCurVar = get_pm_var();
        DLG_TALK_var* pMgrVar = pCurVar;
        HWND  hMgr = hDlgTalk;

        if (!isTalkerShadowMgr(pMgrVar->addr)) {
            TALKER_shadow* pTalkerShadow = (TALKER_shadow*)pMgrVar->pShadowInfo;
            hMgr = pTalkerShadow->hMgr;
            pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
            if (!pMgrVar)  return;
        }
        QTimer::singleShot(1, this, [=] {
            //想要执行的代码
            initConfMem();
            });
        initConfSpeakerList();
          
        //
#ifdef  __DEBUG__.
        if (scroll_bar_update_timer_) {
            int  ii = 0;
            //goto  errLabel;
        }
#endif
        //
        if (!scroll_bar_update_timer_) {
            scroll_bar_update_timer_ = new QTimer(this);
        }
        scroll_bar_update_timer_->setInterval(10000);
        connect(scroll_bar_update_timer_, &QTimer::timeout, [this]()
            {
                onMyScrollMoved(0);
            });
        scroll_bar_update_timer_->start();
       
        QString qstr;
        TCHAR dw[128];
        TCHAR bm[128];
        TCHAR syr[128];


        ui->labCompere->setText(u8" 主持人 ");
        ui->labInitiator->setText(u8" 发起人 ");
        ui->labCompere->setVisible(false);
        ui->labInitiator->setVisible(false);

        
        //最大发言人数
        int index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, pMgrVar->av.taskInfo.iTaskId);
        QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
        if (pTaskInfo == mynull)  goto  errLabel;
        QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
        if (pTc == mynull)goto  errLabel;

        ui->labMaxCount->setText(QString::number(pTc->videoConference.usMaxSpeakers));
        
        //主持人

        //QY_MESSENGER_ID compereIdinfo = dlgTalk_get_idInfo_compere(hDlgTalk);
        bool  bIAmCompere = dlgTalk_bIAmConfCompere(hDlgTalk);
        //getTalkerDesc(compereIdinfo, null, null, 0, null, dw, mycountof(dw), bm, mycountof(bm), syr, mycountof(syr));
        //qstr = QString::fromUtf16((char16_t*)dw) + " " + QString::fromUtf16((char16_t*)bm) + " " + QString::fromUtf16((char16_t*)syr) + "(" + QString::number(compereIdinfo.ui64Id) + ")";

        //ui->labCompere->setText(qstr);
        //if (pMisCnt->idInfo.ui64Id == compereIdinfo.ui64Id) 
        if  (  bIAmCompere)
        {
            ui->labCompere->setVisible(true);
        }
        
        //发起人

        //qstr = QString::number(pMgrVar->av.taskInfo.idInfo_initiator.ui64Id);
        //getTalkerDesc(pMgrVar->av.taskInfo.idInfo_initiator, null, null, 0, null, dw, mycountof(dw), bm, mycountof(bm), syr, mycountof(syr));
        //qstr = QString::fromUtf16((char16_t*)dw) + " " + QString::fromUtf16((char16_t*)bm) + " " + QString::fromUtf16((char16_t*)syr) + " (" + QString::number(pMgrVar->av.taskInfo.idInfo_initiator.ui64Id) + ")";

        if (pMisCnt->idInfo.ui64Id == pMgrVar->av.taskInfo.idInfo_initiator.ui64Id) 
        {
            ui->labInitiator->setVisible(true);
        }
        
        //ui->labInitiator->setText(qstr);
        ui->conferenceController->setVisible(true);


        //tableWidget属性设置为自定义菜单
        ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(ui->tableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
        
        ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QScrollBar* scrolbar = ui->tableWidget->verticalScrollBar();
        QObject::connect((QWidget*)scrolbar, SIGNAL(valueChanged(int)),
            this, SLOT(onMyScrollMoved(int)));

        //listWidget属性设置为自定义菜单
        ui->speakList->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(ui->speakList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(listMenuRequest(QPoint)));

        connect(ui->tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(tableWidgetDellClick(QTableWidgetItem*)));
        connect(ui->speakList, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(speakDellClick(QTableWidgetItem*)));

        if (scrollArea_)
        {
            scrollArea_->setGeometry(0, 0, ui->peerDesc->width(), ui->peerDesc->height());
        }
        
        //refreshLayout();
        if (this->windowState() == Qt::WindowState::WindowMaximized || this->windowState() == Qt::WindowState::WindowFullScreen)
        {
            if (scrollArea_)
            {
                scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
                scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
            }
            return;
        }
        this->resize(sz.width()+ 400, sz.height());
        this->move(this->pos().x() - 400, this->pos().y());

       
    }

    //
    {
        auto rect = this->geometry();
        QRect rc = QApplication::primaryScreen()->geometry();
        if (rect.right() > rc.width())
        {
            this->move(rc.width() - rect.width(), rect.y());
        }
    }
   
errLabel:
    return;
}


//
void CDlgTalk_qt::tableWidgetDellClick(QTableWidgetItem* item) 
{
    record_widget = "tableWidget";
}

//
void CDlgTalk_qt::speakDellClick(QTableWidgetItem* item)
{
    record_widget = "speakList";
}

//滚动分组成员状态
void CDlgTalk_qt::onMyScrollMoved(int a)
{

    QY_MESSENGER_ID  idInfo;
    int row = ui->tableWidget->rowCount();
    int height_s = ui->tableWidget->height();
    QY_MC* pQyMc = QY_GET_GBUF();
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (!pMisCnt)  return;
    for (int i = 0; i < row; i++)
    {
        QTableWidgetItem* item = ui->tableWidget->item(i, 3);
        QRect rc = ui->tableWidget->visualItemRect(item);
        if (rc.bottom() < height_s && rc.top() >= 0)
        {
            // qDebug() << "item[" << item->text() << "]," << rc.x() << "," << rc.y() << "," << rc.top() << "," << rc.bottom() << ",";
            idInfo.ui64Id = item->text().toInt();
            postRecentFriend(pMisCnt, idInfo, 0);
        }
    }
    pMisCnt->refreshRecentFriends.bRefreshAtOnce = true;
}

//分组成员在线状态更新
void CDlgTalk_qt::updateMemStatus(qint64 idInfo, unsigned  short status)
{
    int row = ui->tableWidget->rowCount();
    QY_MESSENGER_ID  idInfo_on;
    QString qstr;
    TCHAR dw[128];
    TCHAR bm[128];
    TCHAR syr[128];
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

    for (int i = 0; i < row; i++)
    {
        QTableWidgetItem* idInfo_item = ui->tableWidget->item(i, 3);
       
        if (idInfo_item->text() == QString::number(idInfo) || pMisCnt->idInfo.ui64Id == idInfo_item->text().toInt())
        {
            idInfo_on.ui64Id = idInfo_item->text().toInt();
            getTalkerDesc(idInfo_on, mynull, mynull, 0, mynull, dw, mycountof(dw), bm, mycountof(bm), syr, mycountof(syr));
            qstr = QString::fromUtf16((char16_t*)dw) + " " + QString::fromUtf16((char16_t*)bm) + " " + QString::fromUtf16((char16_t*)syr);

            if (status == CONST_usRunningStatus_online || pMisCnt->idInfo.ui64Id == idInfo_item->text().toInt()) {
                QTableWidgetItem* item = new QTableWidgetItem;
                item->setSizeHint(QSize(50, 50));
                item->setIcon(QIcon(":/Resources/Images/WinMain/person_on.png"));
                item->setText(qstr);

                ui->tableWidget->setItem(i, 0, item);

                //更新在线状态
                for (int j = 0; j < _memList.size();j++) 
                {
                    if (idInfo_item->text() == _memList[j].userId) {
                        _memList[j].online = true;
                    }
                }
                for (int j = 0; j < _memSearchList.size(); j++)
                {
                    if (idInfo_item->text() == _memSearchList[j].userId) {
                        _memSearchList[j].online = true;
                    }
                }
            }
        }
    }

}


void CDlgTalk_qt::on_btnRule_clicked() 
{
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var)return;
    
    WinRuleSet::showDialog(this,pm_var->addr.idInfo.ui64Id);
}



//装载发言人数据
void CDlgTalk_qt::initConfSpeakerList() 
{

    ui->speakList->setVerticalScrollMode(QTableWidget::ScrollPerPixel);
    ui->speakList->setFocusPolicy(Qt::NoFocus);
    ui->speakList->horizontalHeader()->setFixedHeight(40);
    ui->speakList->horizontalHeader()->setStretchLastSection(true);
    ui->speakList->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui.tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->speakList->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->speakList->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    ui->speakList->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    ui->speakList->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
    ui->speakList->setIconSize(QSize(50, 50));
    //ui.tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框
    ui->speakList->setStyleSheet("selection-background-color: rgba(82,115,204,50%)");
    ui->speakList->setShowGrid(false); //设置不显示格子线
    ui->speakList->verticalHeader()->setVisible(false);
    ui->speakList->verticalHeader()->setDefaultSectionSize(50); //设置行高

    ui->speakList->setColumnWidth(0, 270);
    ui->speakList->setColumnWidth(1, 70);
    ui->speakList->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeMode::Interactive);

    //ui.tableWidget->setColumnWidth(1, 380);
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeMode::Fixed);
   // ui->tableWidget->setColumnWidth(3, 5);

    //清空列表
    for (int i = ui->speakList->rowCount() - 1; i >= 0; i--)
    {
        ui->speakList->removeRow(i);
    }


   
    QList<SpeakInfo> speakList;
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

    CHelp_getDlgTalkVar  getDlgTalkVar_mgr;


    int i = 1;
    QY_MESSENGER_ID idInfo;
    DLG_TALK_var* pm_var = this->get_pm_var();
    
    if (pm_var == mynull)goto  errLabel;
    
    idInfo.ui64Id = pm_var->addr.idInfo.ui64Id;

    if (isTalkerShadowMgr(pm_var->addr))  goto  errLabel;
   
    //
    HWND  hMgr; hMgr = NULL;
    TALKER_shadow* pShadowInfo; pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
    hMgr = pShadowInfo->hMgr;
    DLG_TALK_var* pMgrVar; pMgrVar = NULL;
    
    pMgrVar = (DLG_TALK_var*)getDlgTalkVar_mgr.getVar(hMgr);
    if (!pMgrVar)goto  errLabel;
    //
    if (!pMgrVar->av.taskInfo.bTaskExists) goto  errLabel;
    
    QMC_TASK_INFO* pTaskInfo; pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, pMgrVar->av.taskInfo.iIndex_taskInfo);
    QMC_taskData_conf* pTc; pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
    if (pTc->common.uiType != CONST_taskDataType_conf)goto  errLabel;
    DLG_TALK_videoConference* videoConference; videoConference = &pTc->videoConference;
   

    for (i = 0; i < videoConference->usCntLimit_activeMems_from; i++) {
        DLG_TALK_videoConferenceActiveMemFrom* pActiveMem = &videoConference->activeMems_from[i];
        if (!pActiveMem->avStream.idInfo.ui64Id) continue;
        //
        traceLog((TCHAR*)_T("act[%d]: %I64u, %d,%d"), i, pActiveMem->avStream.idInfo.ui64Id, pActiveMem->avStream.obj.resObj.uiObjType, pActiveMem->avStream.obj.resObj.usIndex_obj);
       
        int row;
        row = ui->speakList->rowCount();
        ui->speakList->insertRow(row);
        SpeakInfo data;
        
        data.userInfo = QString::fromStdWString(pActiveMem->desc);
        data.userId = pActiveMem->avStream.idInfo.ui64Id;
        data.type = QString::number(pActiveMem->avStream.obj.resObj.uiObjType);
        data.index = QString::number(pActiveMem->avStream.obj.resObj.usIndex_obj);
        
        speakList.append(data);


      //  QListWidgetItem* item = new QListWidgetItem(QString::number(i) + ": " + QString::fromStdWString(pActiveMem->desc) + "  " + QString::number(pActiveMem->avStream.idInfo.ui64Id) + "  " + QString::number(pActiveMem->avStream.obj.resObj.uiObjType) + "  " + QString::number(pActiveMem->avStream.obj.resObj.usIndex_obj));

        //QSize sz = item->sizeHint();
        //sz.setHeight(24);
        //item->setSizeHint(sz);//设置每个item的大小
        //item->setIcon(QIcon(":/Resources/Images/WinMain/aio_spokes.png"));
       // ui->speakList->addItem(item);

    }

    for (int i = 0; i <= speakList.size() - 1; i++) {
        QTableWidgetItem* item;
            item = new QTableWidgetItem;
            item->setSizeHint(QSize(50, 50));
            item->setIcon(QIcon(":/Resources/Images/WinMain/aio_spokes.png"));
            item->setText(speakList[i].userInfo);
            ui->speakList->setItem(i, 0, item);

       // ui->speakList->setItem(i, 0, new QTableWidgetItem(speakList[i].userInfo));
        ui->speakList->setItem(i, 1, new QTableWidgetItem(QString::number(speakList[i].userId)));
        ui->speakList->setItem(i, 2, new QTableWidgetItem(speakList[i].type));
        ui->speakList->setItem(i, 3, new QTableWidgetItem(speakList[i].index));
    }

errLabel:
    return;
}

//

int CDlgTalk_qt::refreshConfSpeakerList()
{
    //  不能重新把所有的成员都insert一遍。要判断是否内容变了，如果变了，就改变内容。
    //  如果需要新行，才能插入新行  

    initConfSpeakerList();
    return  0;
}

//
int  CDlgTalk_qt::do_confKeyChanged()
{

    refreshConfSpeakerList();


    return  0;
}





//
int subDevListSortContr(const MemberInfo& info1, const MemberInfo& info2)
{
    int iRet = _tcsicmp((wchar_t*)(info1.name).utf16(), (wchar_t*)(info2.name).utf16());  //升序排列  
    if (iRet < 0) return true;
    return false;

    //return info1->posid < info2->posid;     //降序排列  
}

int  tmpHandler_printImGrpMemList_grpMembers_contr(void* p0, void* p1, void* p2)
{
    int  iRet = -1;
    COMMON_PARAM* pCommonParam = (COMMON_PARAM*)p0;
    COMMON_PARAM* pCommonParam1 = (COMMON_PARAM*)p1;

    //
    CMyDb* pDb = (CMyDb*)pCommonParam->p0;

    //
    QString* pSearStr = (QString*)pCommonParam->p1;

    //  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
    //HWND				hListCtrl = (HWND)pCommonParam->p1;
    //if (!hListCtrl)  goto  errLabel;
    int				iItem = (int)pCommonParam->p2;
    //
    //BOOL				bUnprocedOnly = (BOOL)p1;
    CDlgTalk_qt* pDlg = (CDlgTalk_qt*)pCommonParam1->p0;
    QString* pPeer_id = (QString*)pCommonParam1->p1;
    QList<MemberInfo>* pMemList = (QList<MemberInfo>*)pCommonParam1->p2;
#if  10

    //
    IM_GRP_MEM* pQMem = (IM_GRP_MEM*)p2;
    int				index = 0;
    QY_MC* pQyMc = QY_GET_GBUF();


    QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
    if (!pDbFuncs)  return -1;// goto  errLabel;
    QM_dbFuncs& g_dbFuncs = *pDbFuncs;


    QY_MESSENGER_REGINFO		regInfo;
    MY_REG_DESC					desc;
    TCHAR						tBuf[256];
    QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable);

    memset(&regInfo, 0, sizeof(regInfo));

    /*DLG_TALK_var* pm_var = (DLG_TALK_var*)pDLG_TALK_var;
    pm_var = cdlgTalkqt->get_pm_var();*/
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));


    //  if  (  pQMem->uiType  ==  CONST_objType_imGrp  )
    {
#if  0
        _sntprintf(tBuf, mycountof(tBuf), _T(""));
        index = 0;  myListCtrl_InsertItem(hListCtrl, iItem, tBuf);

        _sntprintf(tBuf, mycountof(tBuf), _T("%s"), qyGetDesByType1(getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable), CONST_objType_imGrp));
        index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

        _sntprintf(tBuf, mycountof(tBuf), _T("%I64u"), pQMem->idInfo_grp.ui64Id);
        index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

        //
        IM_GRP_INFO  grpInfo;
        if (!g_dbFuncs.pf_bGetImGrpInfoBySth(pDb, pQyMc->cfg.db.iDbType, _T(""), &pQMem->idInfo_grp, &grpInfo))  memset(&grpInfo, 0, sizeof(grpInfo));

        _sntprintf(tBuf, mycountof(tBuf), _T("%s"), grpInfo.name);
        index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

        _sntprintf(tBuf, mycountof(tBuf), _T("%I64u"), pQMem->idInfo_mem.ui64Id);
        index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

        if (!g_dbFuncs.pf_bGetMessengerRegInfoBySth(pDb, CONST_dbType_myDb, getResTable(0, &pQyMc->cusRes, CONST_resId_fieldIdTable), CONST_tabName_qyImObjRegInfoTab, pQMem->misServName, &pQMem->idInfo_mem, 0, &regInfo)) {
            memset(&regInfo, 0, sizeof(regInfo));
        }

        MY_REG_DESC  desc;
        regInfo2Desc(0, &regInfo, &desc, NULL, 0, NULL, 0);

        _sntprintf(tBuf, mycountof(tBuf), _T("%s"), desc.pDw);
        index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);
        _sntprintf(tBuf, mycountof(tBuf), _T("%s"), desc.pBm);
        index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);
        _sntprintf(tBuf, mycountof(tBuf), _T("%s"), desc.pSyr);
        index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

        //
        _sntprintf(tBuf, mycountof(tBuf), _T("%s"), qyGetDesByType1(getResTable(0, &pQyMc->cusRes, CONST_resId_imGrpMemRoleTable), pQMem->iRole));
        index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);


        //
        _sntprintf(tBuf, mycountof(tBuf), _T(""));
        index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);


        _sntprintf(tBuf, mycountof(tBuf), _T("%s"), (pQMem->iStatus ? _T("Del") : _T("Ok")));
        index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);
#endif


        //
        traceLog((TCHAR*)_T("grp %I64u, mem %I64u"), pQMem->idInfo_grp.ui64Id, pQMem->idInfo_mem.ui64Id);

        if (QString::number(pQMem->idInfo_grp.ui64Id) == *pPeer_id) {

            TCHAR grpName_mem[125];
            TCHAR srcName_mem[125];
            TCHAR dw[125];
            TCHAR bm[125];


            getTalkerDesc(pQMem->idInfo_mem, NULL, grpName_mem, mycountof(grpName_mem), mynull, dw, mycountof(dw), bm, mycountof(bm), srcName_mem, mycountof(srcName_mem));
            MemberInfo data;

            QString mem_name = QString::fromStdWString(srcName_mem);// +" " + QString::number(pQMem->idInfo_mem.ui64Id);
            QString mem_dw = QString::fromStdWString(dw);
            QString mem_bm = QString::fromStdWString(bm);
         
           
           // QTableWidgetItem* item = new QTableWidgetItem;
            
            if (!mem_name.isNull()) {

                data.name = mem_dw + " " + mem_bm + " " + mem_name;

            }
            else {

                data.name = " (" + QString::number(pQMem->idInfo_mem.ui64Id) + ")";

            }
            data.userId = QString::number(pQMem->idInfo_mem.ui64Id);
            HWND  hDlgTalk = (HWND)pDlg->winId();

            DLG_TALK_var* pCurVar = pDlg->get_pm_var();
            DLG_TALK_var* pMgrVar = pCurVar;
            HWND  hMgr = hDlgTalk;
            CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
            if (!isTalkerShadowMgr(pMgrVar->addr)) {
                TALKER_shadow* pTalkerShadow = (TALKER_shadow*)pMgrVar->pShadowInfo;
                hMgr = pTalkerShadow->hMgr;
                pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
                if (!pMgrVar)  return -1;
            }

            //QY_MESSENGER_ID compereIdinfo = dlgTalk_get_idInfo_compere(hDlgTalk);
            bool  bCompere = dlgTalk_bConfCompere(hDlgTalk, pQMem->idInfo_mem);

            //
            if (pMisCnt->idInfo.ui64Id == pQMem->idInfo_mem.ui64Id) {
                data.status = u8"我";

            }

            //if (compereIdinfo.ui64Id == pQMem->idInfo_mem.ui64Id) 
            if  (  bCompere  )
            {
                if (data.status.isEmpty()) {
                    data.status = u8"主";
                }
                else {
                    data.status.append(u8",主");
                }

            }
            
            if (pMgrVar->av.taskInfo.idInfo_initiator.ui64Id == pQMem->idInfo_mem.ui64Id) {
                if (data.status.isEmpty()) {
                    data.status = u8"发";
                }
                else {
                    data.status.append(u8",发");
                }
            }
 
            int row = pDlg->ui->tableWidget->rowCount();
            if (pSearStr->isEmpty()) 
            {
                
                pDlg->ui->tableWidget->insertRow(row);
                pMemList->append(data);
            }
            else 
            {
              
                if (data.name.contains(*pSearStr)) {
                    pDlg->ui->tableWidget->insertRow(row);
                    pMemList->append(data);
                }
            
            }
        }
    }

#endif

    iRet = 0;
errLabel:
    return  iRet;
}



//装载会议控制列表数据
void CDlgTalk_qt::initConfMem(QString searchStr) {

    ui->tableWidget->setVerticalScrollMode(QTableWidget::ScrollPerPixel);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->horizontalHeader()->setFixedHeight(40);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui.tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
    ui->tableWidget->setIconSize(QSize(50, 50));
    //ui.tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框
    ui->tableWidget->setStyleSheet("selection-background-color: rgba(82,115,204,50%)");
    ui->tableWidget->setShowGrid(false); //设置不显示格子线
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(50); //设置行高

    ui->tableWidget->setColumnWidth(0, 270);
    ui->tableWidget->setColumnWidth(1, 60);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeMode::Interactive);

    ui->tableWidget->setColumnWidth(2, 80);
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeMode::Fixed);
   // ui->tableWidget->setColumnWidth(3, 5);
   
    //清空列表
    for (int i = ui->tableWidget->rowCount() - 1; i >= 0; i--)
    {
        ui->tableWidget->removeRow(i);
    }

    //获取成员数据
    QY_MC* pQyMc = QY_GET_GBUF();
    //
    QY_OBJ_DB* pObjDb = getProcedObjDb(pQyMc, 0, pQyMc->iDsnIndex_mainSys);
    if (!bObjDbAvail(pObjDb))  return;

    DLG_TALK_var* pm_var = this->get_pm_var();

    if (pm_var == mynull) return ;
    QString peer_id = QString::number(pm_var->addr.idInfo.ui64Id);
    QString* pPeer_id = &peer_id;
    QList<MemberInfo> memList;
    QList<MemberInfo>* pMemList = &memList;
    QString* pSearStr = &searchStr;
    //	//
    CMyDb* pDb = (CMyDb*)pObjDb->pDb;
    int cnt = 0;
    COMMON_PARAM	commonParam;
    COMMON_PARAM    commonParam1;
    //  MACRO_makeCommonParam3(  pDb,  pListCtrl,  (  void  *  )cnt,  commonParam  );
    MACRO_makeCommonParam3(pDb, pSearStr, (void*)cnt, commonParam);
    MACRO_makeCommonParam3(this, pPeer_id, pMemList, commonParam1);
    //
    qTraverse(pDb->m_var.pQ_qyImGrpMemTab, tmpHandler_printImGrpMemList_grpMembers_contr, &commonParam, &commonParam1);
   
    std::sort(memList.begin(), memList.end(), subDevListSortContr);
    QList<MemberInfo> tmp_list = reloadMemList(memList);
    _memList = tmp_list;
    updateMemTable(_memList);
    ui->labLoad->setText(u8"成员列表");

    onMyScrollMoved(0);
}


//分组成员发言状态
void CDlgTalk_qt::reloadMemsDoSpeak() 
{
    if (_memList.size() == 0 ) {
        return;
    }

    for (int i = 0; i < ui->speakList->rowCount(); i++ )
    {
        QTableWidgetItem* idInfo_item = ui->speakList->item(i , 1 );
        if (!idInfo_item)return;
        QString idInfo_speak = idInfo_item->text();
        for (int j = 0; j < _memList.size(); j++) 
        {
            if (_memList[j].userId == idInfo_speak) {
                _memList[j].do_spokes = u8"发言";
            }
        }
        //搜索的
        for (int j = 0; j < _memSearchList.size(); j++)
        {
            if (_memSearchList[j].userId == idInfo_speak) {
                _memSearchList[j].do_spokes = u8"发言";
            }

        }
    }

    _memList = reloadMemList(_memList);
    _memSearchList = reloadMemList(_memSearchList);
    //updateMemTable(_memList);

}

//表格右键菜单`   
void CDlgTalk_qt::contextMenuRequest(QPoint pos)
{
    QTableWidgetItem* item = ui->tableWidget->currentItem();
    if (item == mynull) {
        return;
    }
    int row = ui->tableWidget->row(item);
    QTableWidgetItem* idInfo_item = ui->tableWidget->item(row, 3);

    HWND  hDlgTalk = (HWND)this->winId();
    //判断是否为主持人
    //QY_MESSENGER_ID compereIdinfo = unused_dlgTalk_get_idInfo_compere(hDlgTalk);

    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

    //发起人
    DLG_TALK_var* pCurVar = get_pm_var();
    DLG_TALK_var* pMgrVar = pCurVar;
    HWND  hMgr = hDlgTalk;
    
        CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;

    if (!isTalkerShadowMgr(pMgrVar->addr)) {
        TALKER_shadow* pTalkerShadow = (TALKER_shadow*)pMgrVar->pShadowInfo;
        hMgr = pTalkerShadow->hMgr;
        pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
        if (!pMgrVar)  return;
    }


    if (ui->tableWidget->itemAt(pos) != nullptr) {
        QMenu menu(this);// = new QMenu(this);
        QStringList list;
        list << u8"设为主持人" << u8"邀请发言" << u8"私聊";
        QList<QAction*> actList;    
        for (int i = 0; i < list.count(); i++)
            actList.append(new QAction(list.at(i)));
        connect(actList.at(0), &QAction::triggered, this, &CDlgTalk_qt::setCompere);
        connect(actList.at(1), &QAction::triggered, this, &CDlgTalk_qt::confCompere_inviteToSpeak);
        connect(actList.at(2), &QAction::triggered, this, &CDlgTalk_qt::cut_talk );

        //if (pMisCnt->idInfo.ui64Id != compereIdinfo.ui64Id ) 
        if  (  !dlgTalk_bConfCompere(hDlgTalk,pMisCnt->idInfo))
        {
           
            actList.at(1)->setEnabled(false);
        }
        //判断发起人有设为主持人的权限
        if (pMisCnt->idInfo.ui64Id != pMgrVar->av.taskInfo.idInfo_initiator.ui64Id) {
            actList.at(0)->setEnabled(false);
        }
        for (int j = 0; j < ui->speakList->rowCount();j++) {
            if (idInfo_item->text() == ui->speakList->item(j,1)->text()) {
                actList.at(1)->setEnabled(false);
            }
        }

        if (idInfo_item->text().toInt() == pMisCnt->idInfo.ui64Id) {
            actList.at(2)->setEnabled(false);
        }


        menu.addActions(actList);
        menu.exec(QCursor::pos());
    }
   
}


//私聊切换
void CDlgTalk_qt::cut_talk() 
{
    //
    QTableWidgetItem* item = ui->tableWidget->currentItem();
    if (item == mynull) {
        return;
    }
    int row = ui->tableWidget->row(item);

    QTableWidgetItem* idInfo_item = ui->tableWidget->item(row, 3);
    

    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    HWND  hMainWnd = pQyMc->gui.hMainWnd;
    CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);


    WinObjUser user;
    user.idinfo = idInfo_item->text();
    pMainWnd->cut_talk_list(user);
    
}


//发言人右键菜单
void CDlgTalk_qt::listMenuRequest(QPoint pos)
{
    HWND  hDlgTalk = (HWND)this->winId();
    //判断是否为主持人
    //QY_MESSENGER_ID compereIdinfo = dlgTalk_get_idInfo_compere(hDlgTalk);
    bool  bIAmCompere = dlgTalk_bIAmConfCompere(hDlgTalk);


    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

    //只有当item不为空时才添加右键菜单
    if (ui->speakList->itemAt(pos) != nullptr)
    {
        QMenu menu(this);// = new QMenu(this);
        QStringList list;
        list << u8"停止发言" ;
        QList<QAction*> actList;
        for (int i = 0; i < list.count(); i++)
            actList.append(new QAction(list.at(i)));
        connect(actList.at(0), &QAction::triggered, this, &CDlgTalk_qt::confCompere_stopSpeaking);
        //if (pMisCnt->idInfo.ui64Id != compereIdinfo.ui64Id) 
        if  (  !bIAmCompere)
        {
            actList.at(0)->setEnabled(false);
        }

        menu.addActions(actList);
        menu.exec(QCursor::pos());
    }
}


//
 
//分组搜索
void CDlgTalk_qt::on_lineSearch_textChanged(QString str)
{
    
     //清空列表
    for (int i = ui->tableWidget->rowCount() - 1; i >= 0; i--)
    {
        ui->tableWidget->removeRow(i);
    }
    QList<MemberInfo> searMemList;

    int row = ui->tableWidget->rowCount();
    //筛选数据
    for (int i = 0; i < _memList.size(); i ++ )
    {
        if (_memList[i].name.contains(str)) {
            
            ui->tableWidget->insertRow(row);
            searMemList.append(_memList[i]);
        }
    }

    _memSearchList = searMemList;
    updateMemTable(searMemList);
    onMyScrollMoved(0);
}



//设为主持人
void CDlgTalk_qt::setCompere()
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

    //
    QTableWidgetItem* item = ui->tableWidget->currentItem();
    if (item == mynull) {
        return;
    }
    int row = ui->tableWidget->row(item);

    QTableWidgetItem* idInfo_item = ui->tableWidget->item(row, 3);

    //qDebug() << u8"设为主持人:" << idInfo->text();

    QY_MESSENGER_ID  idInfo_compere;
    idInfo_compere.ui64Id = idInfo_item->text().toLongLong();

    //
    HWND  hDlgTalk = (HWND)this->winId();

    //
    if (!dlgTalk_bIAmConfInitiator(hDlgTalk)) return;


    //
    confInitiator_setCompere(hDlgTalk, idInfo_compere);
}


//
int  confInitiator_setCompere(HWND  hDlgTalk,  QY_MESSENGER_ID  idInfo_compere)
{
    int  iErr = -1;
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

    CHelp_getDlgTalkVar  getDlgTalkVar_cur;
    DLG_TALK_var* pCurVar = (DLG_TALK_var*)getDlgTalkVar_cur.getVar(hDlgTalk);
    HWND  hMgr = hDlgTalk;
    DLG_TALK_var* pMgrVar = pCurVar;
    CHelp_getDlgTalkVar  getDlgTalkVar_mgr;
    if (!isTalkerShadowMgr(pCurVar->addr)) {
        TALKER_shadow* pShadow = (TALKER_shadow*)pCurVar->pShadowInfo;
        hMgr = pShadow->hMgr;
        pMgrVar = (DLG_TALK_var*)getDlgTalkVar_mgr.getVar(hMgr);
    }

     //
     TASK_INTERACTION_REQ	req;
     int						lenInBytes = 0;

     memset(&req, 0, sizeof(req));
     req.uiType = CONST_imCommType_taskInteractionReq;
     req.usOp = CONST_imOp_setCompere;
     req.idInfo_compere = idInfo_compere;

     //
     DLG_TALK_var& m_var = *pMgrVar;
        //
     if (m_var.av.taskInfo.ucbVideoConference)  req.idInfo_imGrp_related.ui64Id = m_var.addr.idInfo.ui64Id;
     //	
     lenInBytes = sizeof(req);
     //					
     MACRO_prepareForTran();
     //
     QY_MESSENGER_ID  idInfo_starter = pMgrVar->av.taskInfo.idInfo_starter;
     //
     if (postMsgTask2Mgr_mc(m_var.pMisCnt, CONST_misMsgType_task, 0, CONST_qyCmd_sendTask, tStartTran, uiTranNo, 0, 0, 0, (char*)&req, lenInBytes, NULL, NULL, NULL, &idInfo_starter, 0, NULL, FALSE))  goto  errLabel;

     //
     qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("setCompere") );


     iErr = 0;

     errLabel:
     //
     return  iErr;


}


//邀请发言
void CDlgTalk_qt::confCompere_inviteToSpeak() {

    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    TCHAR  tBuf[128];

    CHelp_getDlgTalkVar  help_getDlgTalkVar_cur;
    CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;

    //
    HWND  hDlgTalk = (HWND)this->winId();

    //
    HWND  hCur = (HWND)hDlgTalk;
    DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar_cur.getVar(hCur);
    if (!pCurVar)goto  errLabel;
    HWND  hMgr; hMgr = hCur;
    DLG_TALK_var* pMgrVar; pMgrVar = pCurVar;
    if (!isTalkerShadowMgr(pCurVar->addr)) {
        TALKER_shadow* pShadow = (TALKER_shadow*)pCurVar->pShadowInfo;
        hMgr = pShadow->hMgr;
        pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
        if (!pMgrVar)  goto  errLabel;
    }

    //
    if (pMgrVar->av.taskInfo.ucbVideoConference
        && !pMgrVar->av.taskInfo.ucbStarter)
    {
        //
        if (isActiveMemsFull(pMgrVar->av.taskInfo.iTaskId, true)) {
            //_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "already too many speakers. you cant speak now"  )  );
            _sntprintf(tBuf, mycountof(tBuf), _T("现在发言人已经满了"));
            showNotification(0, 0, 0, 0, 0, 0, tBuf);
            //goto  errLabel;
            return;
        }

    }

    QTableWidgetItem* item; item = ui->tableWidget->currentItem();
    if (item == mynull) {
        return;
    }
    int row; row = ui->tableWidget->row(item);

    QTableWidgetItem* idInfo_item; idInfo_item = ui->tableWidget->item(row, 3);
    qDebug() << u8"邀请发言:" << idInfo_item->text();

    QY_MESSENGER_ID  idInfo_sel;
    idInfo_sel.ui64Id = idInfo_item->text().toLongLong();


    MIS_CNT* pMisCnt; pMisCnt = pProcInfo->getMisCntByName(_T(""));

    //判断当前自己
    if (pMisCnt->idInfo.ui64Id == idInfo_sel.ui64Id) {
        on_SpeakBtn_click();
        
        return;
    }

   
    //
    if (!dlgTalk_bIAmConfCompere(hDlgTalk)) {
        showNotification_open(0, 0, 0, _T("Err: not compere"));
        goto  errLabel;
    }
    //
    if (idInfo_sel.ui64Id == pMisCnt->idInfo.ui64Id) {

        if (pMgrVar->av.taskInfo.ucbStarter) {
            goto  errLabel;
        }
        else {
            //
            confOthers_requestToSpeak(hMgr, pMgrVar->av.iIndex_sharedObj_localAv, mynull, TRUE);

        }

    }
    else {
        //	
        //confMgr_permitToSpeak(hMgr, &idInfo_sel, TRUE);
        confCompere_pleaseSpeak(hMgr, &idInfo_sel, true);
    }




    //
errLabel:
    return;
}

//停止发言
void CDlgTalk_qt::confCompere_stopSpeaking() {
    QTableWidgetItem* item = ui->speakList->currentItem();
    if (item == mynull) {
        return;
    }
    int row = ui->speakList->row(item);

    QTableWidgetItem* idInfo_item = ui->speakList->item(row, 1);

    qDebug() << u8"停止发言:" << idInfo_item->text();

    QY_MESSENGER_ID  idInfo_sel;
    idInfo_sel.ui64Id= idInfo_item->text().toLongLong();

    //
    CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;

    //
    HWND  hDlgTalk = (HWND)this->winId();

    //
    if (!dlgTalk_bIAmConfCompere(hDlgTalk)) {
        showNotification_open(0, 0, 0, _T("not conf compere"));
        goto  errLabel;
    }
    
        // TODO: Add your control notification handler code here
        //
    MC_VAR_isCli* pProcInfo; pProcInfo = QY_GET_procInfo_isCli();
        FUNCS_for_isCliHelp* pFuncs; pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
        if (!pFuncs)  return;
        MIS_CNT* pMisCnt; pMisCnt = pProcInfo->getMisCntByName(_T(""));
        //
        HWND  hCur; hCur = (HWND)this->winId();
        DLG_TALK_var* pCurVar; pCurVar = get_pm_var();
        DLG_TALK_var* pMgrVar; pMgrVar = pCurVar;
        HWND  hMgr; hMgr = hCur;

        //
        if (!isTalkerShadowMgr(pMgrVar->addr)) {
            TALKER_shadow* pTalkerShadow = (TALKER_shadow*)pMgrVar->pShadowInfo;
            hMgr = pTalkerShadow->hMgr;
            pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
            if (!pMgrVar)  goto  errLabel;
        }
        //
        if (!idInfo_sel.ui64Id)  goto  errLabel;


        if (idInfo_sel.ui64Id == pMisCnt->idInfo.ui64Id) {

            dlgTalk_requestToSpeak(hMgr, FALSE);

        }
        else {
            //
            if (pMgrVar->av.taskInfo.ucbStarter) {
                goto  errLabel;
            }
            else {
                confMgr_requestToSpeak(hMgr, &idInfo_sel, FALSE);

            }

            //	
            //confMgr_permitToSpeak(hMgr, &idInfo_sel, FALSE);
            confCompere_pleaseSpeak(hMgr, &idInfo_sel, false);

        }
        //这有一丢丢小问题 需要优化
        ui->toolBtnSpeak->setText(u8"发言");

        //
        errLabel:
    
    //
    return;
}


//更新 菜单权限及主持人
void CDlgTalk_qt::updateMenuComper() 
{

    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    HWND  hDlgTalk = (HWND)this->winId();

    DLG_TALK_var* pCurVar = get_pm_var();
    DLG_TALK_var* pMgrVar = pCurVar;
    HWND  hMgr = hDlgTalk;
    CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
    if (!isTalkerShadowMgr(pMgrVar->addr)) {
        TALKER_shadow* pTalkerShadow = (TALKER_shadow*)pMgrVar->pShadowInfo;
        hMgr = pTalkerShadow->hMgr;
        pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
        if (!pMgrVar)  return ;
    }
    QString qstr;
    TCHAR dw[128];
    TCHAR bm[128];
    TCHAR syr[128];
   
    //更新主持人显示  
    //QY_MESSENGER_ID compereIdinfo = dlgTalk_get_idInfo_compere(hDlgTalk);
    bool  bIAmCompere = dlgTalk_bIAmConfCompere(hDlgTalk);
  //  getTalkerDesc(compereIdinfo, null, null, 0, null, dw, mycountof(dw), bm, mycountof(bm), syr, mycountof(syr));
   // qstr = QString::fromUtf16((char16_t*)dw) + " " + QString::fromUtf16((char16_t*)bm) + " " + QString::fromUtf16((char16_t*)syr) + "(" + QString::number(compereIdinfo.ui64Id) + ")";
    
    //if (pMisCnt->idInfo.ui64Id == compereIdinfo.ui64Id) 
    if (bIAmCompere)
    {
        ui->labCompere->setVisible(true);
    }
    else {
        ui->labCompere->setVisible(false);
    }
    
     //更新列表
    int rowCount = ui->tableWidget->rowCount();
    for(int i = 0; i < rowCount; i ++)
    {
        QString tmp_qstr = mynull;
        QTableWidgetItem* item =  ui->tableWidget->item(i, 3);

        QTableWidgetItem* item_identity = ui->tableWidget->item(i, 2);

        item_identity->setText("");

        if (pMisCnt->idInfo.ui64Id == item->text().toInt()) 
        {
            tmp_qstr = u8"我";
        }

        //
        QY_MESSENGER_ID  tmp_idInfo;
        tmp_idInfo.ui64Id = item->text().toInt();


        //if (item->text() == QString::number( compereIdinfo.ui64Id )) 
        if  (  dlgTalk_bConfCompere(hDlgTalk, tmp_idInfo))
        {
            if (!tmp_qstr.isEmpty()) {
                tmp_qstr.append(u8",");
            }
             tmp_qstr.append(u8"主");
        }

        if (item->text() == QString::number(pMgrVar->av.taskInfo.idInfo_initiator.ui64Id))
        {
            if (!tmp_qstr.isEmpty()) {
                tmp_qstr.append(u8",");
            }
            tmp_qstr.append(u8"发");
        }
        
        item_identity->setText(tmp_qstr);
    }

    //清空状态
    for (int i = 0; i < _memList.size(); i++)
    {
        _memList[i].status = "";
    }

    //更新数据
    for (int i = 0; i < _memList.size(); i++) 
    {
        if (pMisCnt->idInfo.ui64Id == _memList[i].userId.toInt())
        {
            _memList[i].status = u8"我";
        }

        //
        QY_MESSENGER_ID  tmp_idInfo;
        tmp_idInfo.ui64Id = _memList[i].userId.toInt();

        //if (_memList[i].userId.toInt() == compereIdinfo.ui64Id ) 
        if  (  dlgTalk_bConfCompere(hDlgTalk,tmp_idInfo))
        {
            if (!_memList[i].status.isEmpty()) {
                _memList[i].status.append(u8",");
            }
            _memList[i].status.append(u8"主");
        }

        if (_memList[i].userId.toInt() == pMgrVar->av.taskInfo.idInfo_initiator.ui64Id)
        {
            if (!_memList[i].status.isEmpty()) {
                _memList[i].status.append(u8",");
            }
            _memList[i].status.append(u8"发");
        }

    }

    //新主持人自动展示窗口
    viewCompereControl();
}


//分组成员待发言状态
int CDlgTalk_qt::do_confMemKeyChanged(HWND hDlgTalk)
{
    //
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
    DLG_TALK_var* pm_var = get_pm_var();
    if (!pm_var)return  false;
    DLG_TALK_var& m_var = *pm_var;

     QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, m_var.av.taskInfo.iIndex_taskInfo);
     if (!pTaskInfo)  return -1;
     if (!pTaskInfo->var.pTaskData) return -1;
     if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  return -1;
     QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
     DLG_TALK_videoConference* pVc = &pTc->videoConference;

    
     int  iTalkSubtype = CONST_talkerSubtype_video;
     HWND  m_hWnd_shadow;

     if (findTalker_shadow(pQyMc, pm_var->addr.idInfo.ui64Id, iTalkSubtype, &m_hWnd_shadow))
     {
         return -1 ;
     }
     CDlgTalk_qt* video_cdlgTalkqt = (CDlgTalk_qt*)getObjAddr(m_hWnd_shadow);
     if (!video_cdlgTalkqt)
     {
         return -1;
     }


    int rowCount = video_cdlgTalkqt->ui->tableWidget->rowCount();
    for (int i = 0; i < rowCount; i++)
    {
        video_cdlgTalkqt->ui->tableWidget->item(i, 1)->setText("");
    }
    

    for (int i = 0; i < rowCount; i++) 
    {
        QTableWidgetItem* id_item = video_cdlgTalkqt->ui->tableWidget->item(i,3);

        QTableWidgetItem* status_item = video_cdlgTalkqt->ui->tableWidget->item(i, 1);
        
        for (int j = 0; j <= mycountof(pVc->requestingMems_from); j++) {

            QTableWidgetItem* status_item = video_cdlgTalkqt->ui->tableWidget->item(i, 1);
          
            if (id_item->text().toInt() == pVc->requestingMems_from[j].avStream.idInfo.ui64Id) 
            {  
                status_item->setText(u8"申请");
            }
        }
    }

    
    if (video_cdlgTalkqt->_memList.size() == 0) {
        return -1;
    }

    //清空状态
    for (int i = 0; i < video_cdlgTalkqt->_memList.size(); i++)
    {
        video_cdlgTalkqt->_memList[i].do_spokes = "";
    }

    for (int i = 0; i < video_cdlgTalkqt->_memSearchList.size(); i++)
    {
        video_cdlgTalkqt->_memSearchList[i].do_spokes = "";
    }
     
    
    //更新状态
    for (int i = 0; i < video_cdlgTalkqt->_memList.size(); i++)
    {
        for (int j = 0; j < mycountof(pVc->requestingMems_from); j++) {
          
            if (video_cdlgTalkqt->_memList[i].userId.toInt() == pVc->requestingMems_from[j].avStream.idInfo.ui64Id)
            {
                video_cdlgTalkqt->_memList[i].do_spokes = u8"申请";
            }
        }
    }

    for (int i = 0; i < video_cdlgTalkqt->_memSearchList.size(); i++)
    {
        for (int j = 0; j < mycountof(pVc->requestingMems_from); j++) {

            if (video_cdlgTalkqt->_memSearchList[i].userId.toInt() == pVc->requestingMems_from[j].avStream.idInfo.ui64Id)
            {
                video_cdlgTalkqt->_memSearchList[i].do_spokes = u8"申请";
            }
        }
    }

    //变动位置
    video_cdlgTalkqt->_memList = reloadMemList(video_cdlgTalkqt->_memList);
    video_cdlgTalkqt->_memSearchList = reloadMemList(video_cdlgTalkqt->_memSearchList);
   


    //更新发言状态
    video_cdlgTalkqt->reloadMemsDoSpeak();
    
    
    video_cdlgTalkqt->updateMemTable(video_cdlgTalkqt->_memList);
    
   
}

//重组分组列表数据
QList<MemberInfo> CDlgTalk_qt::reloadMemList(QList<MemberInfo> memDat)
{

    QList<MemberInfo> tmp_list;

    for (int i = 0; i < memDat.size(); i++)
    {
        if (!memDat[i].do_spokes.isEmpty() && memDat[i].status.isEmpty())
        {
            tmp_list.append(memDat[i]);
        }
        if (!memDat[i].do_spokes.isEmpty() && !memDat[i].status.isEmpty())
        {
            tmp_list.append(memDat[i]);
        }
    }
    for (int i = 0; i < memDat.size(); i++)
    {
        if (!memDat[i].status.isEmpty() && memDat[i].do_spokes.isEmpty())
        {
            tmp_list.append(memDat[i]);
        }
    }
    for (int i = 0; i < memDat.size(); i++)
    {
        if (memDat[i].do_spokes.isEmpty() && memDat[i].status.isEmpty())
        {
            tmp_list.append(memDat[i]);
        }

        
    }
    return tmp_list;
}


//装载分组成员列表
void CDlgTalk_qt::updateMemTable(QList<MemberInfo> memData) {
    if (!ui->lineSearch->text().isEmpty()) {
        memData = _memSearchList;
    }
   
   
    for (int i = 0; i <= memData.size() - 1; i++) {
        QTableWidgetItem* item = new QTableWidgetItem;
        item->setSizeHint(QSize(50, 50));
        if (memData[i].online) {
            item->setIcon(QIcon(":/Resources/Images/WinMain/person_on.png"));
        }
        else {
            item->setIcon(QIcon(":/Resources/Images/WinMain/person.png"));
        }
      
        item->setText(memData[i].name);
        ui->tableWidget->setItem(i, 0, item);
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(memData[i].status));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(memData[i].userId));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(memData[i].do_spokes));
    }
}


