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
#include "ctxQmc_qt.h"
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
#include <QSoundEffect>
#include <windows.h>
#include <WinSystemAbout.h>

//
#define     CONST_str_2screens      u8"双屏显示(会议双流)"




int search_fill_contact(QList<SearchInfoData >& m_infoList);
int search_fill_grp(QList<SearchInfoData >& m_infoList);
int search_fill_msg(QList<SearchInfoData >& m_infoList, QString str);




//
namespace {
    const int kMouseRegionLeft = 10;
    const int kMouseRegionTop = 10;
    const int kMouseRegionButtom = 10;
    const int kMouseRegionRight = 10;
     QSoundEffect* _sound=nullptr;
     HWND  HWND_MAIN_ID=0;
}
CMainFrame::CMainFrame(QWidget* parent)
    : WinBasic(true, parent)
    , ui(new Ui::CMainFrame)
{
#ifdef  __DEBUG__
    traceLog((TCHAR*)_T("mainFrame::CMainFrame() enters"));
#endif

    ui->setupUi(this);


    // ui->stackedWidgetInfo->setAttribute(Qt::WA_TransparentForMouseEvents, true);
     //ui->stackedWidgetContact->setAttribute(Qt::WA_TransparentForMouseEvents, true);
     //
    memset(&var, 0, sizeof(var));
    initControl();
    updateMsgCount();
    ui->userName->installEventFilter(this);
    ui->signName->installEventFilter(this);
   // ui->infoInfo->installEvenFilter(this);
    ui->redCount->installEventFilter(this);

    //
    QRect rc = QApplication::desktop()->screenGeometry();
    int dis_height = COUNT_display_height_value;
    int dis_width = COUNT_display_width_value;

    if (rc.height() < dis_height && rc.width() > dis_width) {
    //if (rc.height() < 800 && rc.width() > 900) {
        int rx = (rc.width() - 900) / 2;
        int ry = (rc.height() - 640) / 2;
        QRect rc1 = QRect(rx , ry ,900 , 640);

        this->setGeometry(rc1);

    }

    //
    CCtxQyMc* pQyMc = QY_GET_GBUF();
    CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();

    //
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

    m_pWinTimer = new QTimer(this);
    connect(m_pWinTimer, SIGNAL(timeout()), this, SLOT(on_timer_winMethod()));
    m_pWinTimer->setInterval(1000);
    m_pWinTimer->start();

    //
    pQyMc->dbg.dwTickCnt_mainFrame_inited = myGetTickCount(null);
    int  iElapseInMs = pQyMc->dbg.dwTickCnt_mainFrame_inited - pQyMc->dbg.dwTickCnt_start;
    int  ii = 0;


    //
errLabel:

    //auto_do();
    return;


#ifdef  __DEBUG__
    traceLog((TCHAR*)_T("mainFrame::CMainFrame() leaves"));
#endif
}

void CMainFrame::auto_do() 
{
    //ui->toolBtnContact->click();
}

CMainFrame::~CMainFrame()
{
    delete ui;
    if (m_pWinTimer)
    {
        delete m_pWinTimer;
        m_pWinTimer = nullptr;
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
    //
    if (_sound) {
        delete _sound;
        _sound = nullptr;
    }


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

void CMainFrame::Init()
{
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

#if  0
    qint64 uid = pMisCnt->idInfo.ui64Id;
    DBManager::Instance().initDB(QString::number(uid));
#endif


    //
    init_tray_icon(this->windowIcon());
    //
   // WinTalkList* winTalkList = null;
    //winTalkList = (WinTalkList* )QWidget::find((WId));
    QWidget* pWnd = ui->stackedWidgetContact->widget(0);
    if (pWnd == null)  goto  errLabel;
    if (pWnd->objectName() != "WinTalkList")goto  errLabel;
    WinTalkList* pTalkList = (WinTalkList*)pWnd;
    if (pTalkList == null)  goto  errLabel;

    pTalkList->load_initList();
 
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
        return;
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
    
    QAction* act_menu;
    /*act_menu = new QAction();
    act_menu->setText(u8"主窗口");
    act_menu->setObjectName(QString("act_menu_main"));
    //act_menu->setIcon(this->windowIcon());
    connect(act_menu, &QAction::triggered, this, &CMainFrame::on_tray_menu);
    mSysTrayIcon_->AddMenu(act_menu);
    */


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

    QWidget* pWnd = ui->stackedWidgetContact->widget(0);
    if (pWnd == null)  goto  errLabel;
    if (pWnd->objectName() != "WinTalkList")goto  errLabel;
    WinTalkList* pTalkList = (WinTalkList*)pWnd;
    if (pTalkList == null)  goto  errLabel;

    wou.idinfo = QString::number(userId);

    pTalkList->selListWidget(wou);



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
            return;
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
            CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();
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
   // setWindowFlags(Qt::FramelessWindowHint);

   // setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->setWindowIcon(QIcon(":/Resources/Images/Login/qmClient.png"));
    ui->headIcoBtn->setIcon(QIcon(":/Resources/Images/WinMain/headMax.png"));
   
    //
    ui->labTitle->setText(QString::fromUtf16((char16_t*)pQyMc->cfg.qyMcTitle));
    //
    ui->headIcoBtn->setIconSize(QSize(55, 55));
    QAction* pActLeft = new QAction(this);
    pActLeft->setIcon(QIcon(":/Resources/Images/WinMain/search_icon.png"));
    ui->searchLineEdit->addAction(pActLeft, QLineEdit::LeadingPosition);

    ui->moreMenu->setIcon(QIcon(":/Resources/Images/WinMain/aio_more.png"));

    QMenu* moreMenu = new QMenu();
    QAction* more_newGroup_action = new QAction(moreMenu);
    more_newGroup_action->setText(u8"新建群组");

    QAction* more_myDisk_action = new QAction(moreMenu);
    more_myDisk_action->setText(u8"我的网盘");

    QAction* more_2screen_action = new QAction(moreMenu);
    more_2screen_action->setText(CONST_str_2screens);

    QAction* more_writeOff_action = new QAction(moreMenu);
    more_writeOff_action->setText(u8"退出");

    moreMenu->addAction(more_newGroup_action);
    moreMenu->addSeparator();
    moreMenu->addAction(more_myDisk_action);
    moreMenu->addSeparator();
    moreMenu->addAction(more_2screen_action);
    moreMenu->addSeparator();
    moreMenu->addAction(more_writeOff_action);


    ui->moreMenu->setMenu(moreMenu);
    ui->moreMenu->setStyleSheet("QPushButton::menu-indicator{image:None;border:none}");

    connect(moreMenu, SIGNAL(triggered(QAction*)), this, SLOT(trigerMenu(QAction*)));

    

    painterMenu("toolBtnMsg");
    QFile file(":/Resources/QSS/CMainFrame.css");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        this->setStyleSheet("");
        QString qsstyleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(qsstyleSheet);
    }
    file.close();

    m_pWinTitle = new WinTitle(ui->titleWidget);
    m_pWinTitle->setButtonType(MIN_MAX_BUTTON);
    //m_pWinTitle->setWindowFlag(Qt::WindowStaysOnBottomHint);
    //m_pWinTitle->move(0, 0);
    m_pWinTitle->setParent(true);
    connect(m_pWinTitle, SIGNAL(signalButtonMinClicked()), this, SLOT(on_ButtonMin_clicked()));
    connect(m_pWinTitle, SIGNAL(signalButtonCloseClicked()), this, SLOT(on_ButtonClose_clicked()));
    connect(m_pWinTitle, SIGNAL(signalButtonRestoreClicked()), this, SLOT(on_ButtonRestore_clicked()));
    connect(m_pWinTitle, SIGNAL(signalButtonMaxClicked()), this, SLOT(on_ButtonMax_clicked()));

    searchListView_ = new QListView(ui->widget_2);
    connect(searchListView_, &QListView::clicked, this, &CMainFrame::slot_list_activated);
    verticalScrollBar = searchListView_->verticalScrollBar();
    connect(verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(onScrollBarValueChanged(int)));
    searchListMoudle_ = new SearchListModel(this);
    SearchListDelegate* itemdelegate = new SearchListDelegate(searchListMoudle_, this);
    //ui.listView->setResizeMode(QListView::Adjust);
    searchListView_->setModel(searchListMoudle_);
    searchListView_->setItemDelegate(itemdelegate);
    searchListView_->setVisible(false);

    searchListView_->verticalScrollBar()->setStyleSheet("QScrollBar{width:10px;}");

    QWidget* pCur = ui->stackedWidgetInfo->currentWidget();
    if (pCur != NULL) {
        QString name = pCur->objectName();
        if (pCur->objectName() == "CDlgTalk_qt") {
            CDlgTalk_qt* pDlg = (CDlgTalk_qt*)pCur;
            connect(pDlg, SIGNAL(to_closeTalkInfo(QString)), this, SLOT(slot_closeTalk(QString)));
        }
    }

   


    //必须在界面初始化之前置为nullptr
    h_cdlgTalkqt = nullptr;
    //消息列表
    WinTalkList* pTalkList = new WinTalkList(this);
    ui->stackedWidgetContact->addWidget(pTalkList);
    connect(pTalkList, SIGNAL(toShowContactMsg(WinObjUser)), this, SLOT(on_Contact_Msg(WinObjUser)));
    /*connect(pTalkList, SIGNAL(toCDlgTalk(WinObjUser)), this, SLOT(createCDlgTalk(WinObjUser)));*/
    //联系人列表
    WinContactsList* pContactsList = new WinContactsList();
    ui->stackedWidgetContact->addWidget(pContactsList);
    ui->stackedWidgetContact->setCurrentIndex(CONT_TALKLIST);
    connect(pContactsList, SIGNAL(toShowContactsInfo(WinObjUser)), this, SLOT(on_Contacts_Info(WinObjUser)));

    

    //0-消息 临时
    QWidget* pWidget = new QWidget;
    pWidget->setObjectName("temp");
    ui->stackedWidgetInfo->addWidget(pWidget);

    //1-联系人信息
    CDlgTalk_msgr_detail* pContactsInfo = new CDlgTalk_msgr_detail();
    ui->stackedWidgetInfo->addWidget(pContactsInfo);
    connect(pContactsInfo, SIGNAL(toSendMsg(WinObjUser)), this, SLOT(on_SendMsg_clicked(WinObjUser)));
    //connect(pContactsInfo, SIGNAL(toSendMeeting(WinObjUser)), this, SLOT(on_SendMeeting_clicked(WinObjUser)));
    //2-群组信息
    CDlgTalk_imGrp_detail* pContactsGroupInfo = new CDlgTalk_imGrp_detail();
    ui->stackedWidgetInfo->addWidget(pContactsGroupInfo);
    WinObjUser user;
    user.dataType = 2;
    user.name = "null";
    pContactsGroupInfo->ShowContactsGroupInfo(user);
    connect(pContactsGroupInfo, SIGNAL(toSendMsg(WinObjUser)), this, SLOT(on_SendMsg_clicked(WinObjUser)));
    //connect(pContactsGroupInfo, SIGNAL(toSendMeeting(WinObjUser)), this, SLOT(on_SendMeeting_clicked(WinObjUser)));
    //3-高级设置
#if 0
    WinAdvancedSet* pWinAdvancedSet = new WinAdvancedSet;
    ui->stackedWidgetInfo->addWidget(pWinAdvancedSet);
    ui->stackedWidgetInfo->setCurrentIndex(INFO_MSG);
    m_nContactsIndex = 0;
#endif
    QDesktopWidget* pDesk = QApplication::desktop();
    QRect screenRect = QApplication::desktop()->screenGeometry(this);
    this->setGeometry((screenRect.width() - this->width()) / 2, (screenRect.height() - this->height()) / 2, this->width() - 10, this->height());
    
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
    ui->redCount->setText(msgCount > 99 ? "99" : QString::number(msgCount));
    ui->redCount->setVisible(msgCount != 0);
}



void CMainFrame::trigerMenu(QAction* act)
{
    if (act->text() == u8"新建群组")
    {
        on_newGroupBtn_clicked();
    }
    if (act->text() == u8"我的网盘") {

        HWND  hParent = null;// (HWND)this->winId();
        //HWND  hCurTalk = (HWND)this->winId();

        MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();

        PARAM_viewOfflineRes  param = { 0 };
        param.bNoBorder = TRUE;

        viewDlgOfflineRes_me(hParent, &pProcInfo->offlineRes, NULL);


    }
    if (act->text() == CONST_str_2screens) {
        viewDlg2ndScreen_qt();
    }
    if (act->text() == u8"退出")
    {
        CCtxQyMc* pQyMc = g_pQyMc;
        CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();
        DBManager* pDm = (DBManager*)pProcInfo->m_var.pDBManager;
        pDm->setAllUserActiveProcess(0);
        closeDlgAvAccept();


        //
        HWND  m_hWnd = (HWND)this->winId();
        ::PostMessage(m_hWnd, WM_COMMAND, MAKEWPARAM(ID_qyQuitMainWnd, 0), 0);
    }
}


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

void CMainFrame::autoSet() {

    WinContactsList* pContactsList = (WinContactsList*)ui->stackedWidgetContact->widget(1);
    pContactsList->autoSet();
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

        WinTalkList* pTalkList = (WinTalkList*)ui->stackedWidgetContact->widget(0);
        pTalkList->addListWidget(user);

        on_Contact_Msg(user);

        //联系人列表
        WinContactsList* pContactsList = (WinContactsList*)ui->stackedWidgetContact->widget(1);
        pContactsList->addTmpContactItem(req.common.idInfo.ui64Id);
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
    QWidget* pCur = ui->stackedWidgetContact->currentWidget();

    if (pCur != NULL) {
        QString name = pCur->objectName();
        //
        //traceLog((TCHAR*)_T("%s"), name.utf16());
        //
        if (pCur->objectName() == "WinContactsList") {
            WinContactsList* pList = (WinContactsList*)pCur;
            //
            //pList->dbg_testFunc();
        }
        else if (pCur->objectName() == "WinTalkList") {
            //
            WinTalkList* pTalkList = (WinTalkList*)pCur;
            //pTalkList->dbg_testFunc();
        }
    }



#endif

    //
    return  0;
}

int CMainFrame::onLineStatus()
{

    //
    //int  count = ui.copWnd->uself.treeWidget.topLevelItemCount()
    QWidget* pCur = ui->stackedWidgetContact->currentWidget();

    if (pCur != NULL) {
        QString name = pCur->objectName();
        //
        //traceLog((TCHAR*)_T("%s"), name.utf16());
        //
        if (pCur->objectName() == "WinContactsList") {
            WinContactsList* pList = (WinContactsList*)pCur;
            //
            pList->onLineStatusUp();
        }
        else if (pCur->objectName() == "WinTalkList") {
            //
            WinTalkList* pTalkList = (WinTalkList*)pCur;
            pTalkList->onLineStatusUp();
        }
    }
    //
    return  0;
}


//关闭窗口
void CMainFrame::on_timer_winMethod()
{
    // TODO: Add your message handler code here and/or call default
    CCtxQyMc* pQyMc = QY_GET_GBUF();
    if (!pQyMc) return;
    //MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return;
    
    //void* p = pProcInfo->pFuncs_for_isCliHelp;

    FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
    if (!pFuncs) return;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (!pMisCnt)return;

    //
    HWND  m_hWnd = pQyMc->gui.hMainWnd;

    //
    if (pFuncs->mainWnd.pf_mainWnd_OnTimer(m_hWnd, &var, 0))  return;

    //
    if (!(var.common.loopCtrl % 3)) {
        QString tag = m_myName + (bMeOnline(pQyMc) ? "" : u8" (离线)");
        if (tag != ui->userName->text()) {
            ui->userName->setText(tag);
        }
    }
    
    //
    if (!(var.common.loopCtrl % 20)) {
        onLineStatus();
    }


    //
#ifdef  __DEBUG__
        //testSndRtspMsg();
        //
        dbg_testFunc();
        //    
        //traceLog((TCHAR*)_T("haha"));
#endif



    //  
}

//消息
void CMainFrame::on_toolBtnMsg_clicked()
{
    painterMenu("toolBtnMsg");
    ui->centerWidget->show();
    ui->stackedWidgetContact->setCurrentIndex(CONT_TALKLIST);

    //QWidget* pWidget = ui->stackedWidgetInfo->widget(0);
    //if (pWidget->objectName() == "temp")
    //{
    //	return;
    //}
    ui->stackedWidgetInfo->setCurrentIndex(INFO_MSG);
    ui->searchLineEdit->clear();
    onLineStatus();
}

bool CMainFrame::isMsgSel() {
    if (ui->stackedWidgetContact->currentIndex() == CONT_TALKLIST) {
        return true;
    }
    return false;
}

int CMainFrame::getCurIdInfo(QY_MESSENGER_ID  * pIdInfo) 
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
        WinContactsList* pContactsList = (WinContactsList*)ui->stackedWidgetContact->widget(1);
        pContactsList->toContactList();

        //
        QApplication::restoreOverrideCursor();

        //
#ifdef  __DEBUG__
        showInfo_open0(0, null, _T("after toContactList"));
        //
        pQyMc->dbg.dwTickCnt_after_toContactList = myGetTickCount(null);
        int  iDiffInMs1 = pQyMc->dbg.dwTickCnt_after_toContactList - pQyMc->dwTickCnt_logon;
        int  iii = 0;
#endif
        //
    }


    //
    painterMenu("toolBtnContact");
    ui->searchLineEdit->clear();
    ui->centerWidget->show();
    ui->stackedWidgetContact->setCurrentIndex(1);
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

    //
    //close();
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
    //this->showNormal();
}

//放大
void CMainFrame::on_ButtonMax_clicked()
{
    this->showMaximized();
    //QRect desktopRect = QApplication::desktop()->availableGeometry();
    //QRect FactRect = QRect(desktopRect.x(), desktopRect.y(), desktopRect.width(), desktopRect.height());
    //setGeometry(FactRect);
}

//显示用户消息
void CMainFrame::on_Contact_Msg(WinObjUser user)
{
    ui->stackedWidgetContact->setCurrentIndex(CONT_TALKLIST);
    ui->stackedWidgetInfo->setCurrentIndex(INFO_MSG);
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

    ui->stackedWidgetContact->setCurrentIndex(CONT_TALKLIST);
    WinTalkList* pTalkList = (WinTalkList*)ui->stackedWidgetContact->widget(0);
    pTalkList->addListWidget(user);
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
        
    if (null != cdlgTalkqt)
    {

        DLG_TALK_var* pm_var = cdlgTalkqt->get_pm_var();
        if (QString::number(pm_var->addr.idInfo.ui64Id) == idInfo) {
            ui->stackedWidgetInfo->removeWidget(cdlgTalkqt);
            cdlgTalkqt->closeCDlgTalk_qt();

        }

      
    }
    
}

void CMainFrame::delTalkerList(QString idInfo) {
    WinTalkList* pTalkList = (WinTalkList*)ui->stackedWidgetContact->widget(0);
    pTalkList->delListWidget(idInfo);
}
void CMainFrame::delContactList(QString idInfo) {
    WinContactsList* pContactList = (WinContactsList*)ui->stackedWidgetContact->widget(1);
    pContactList->delTmpContactItem(idInfo);
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
       

        if (null != cdlgTalkqt)
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

    CDlgTalk_qt* shadow_cdlgTalkqt = (CDlgTalk_qt*)getObjAddr(h_cdlgTalkqt);
    if (!shadow_cdlgTalkqt)
    {
        goto errLabel;
    }
    shadow_cdlgTalkqt->ShowMsgInfo(user);
    shadow_cdlgTalkqt->hideWidget(user);
    shadow_cdlgTalkqt->setCanResize(false);
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
bool CMainFrame::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
    Q_UNUSED(eventType);
    MSG* msg = reinterpret_cast<MSG*>(message);
    UINT m = msg->message;
    if (m == WM_COMMAND || m == CONST_qyWm_comm || m == CONST_qyWm_postComm)
    {
        return postMessageQt(msg, result);
    }
    /*else if (m == WM_NCHITTEST)
    {
        return dealHTEvent((MSG*)message,result);
    }*/
    //
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
    //
    return WinBasic::nativeEvent(eventType, message, result);
}
//
bool CMainFrame::postMessageQt(MSG* message, long* result)
{
    if (message->message == WM_COMMAND)
    {
        int id = LOWORD(message->wParam);
        if (id == ID_qyRefresh)
        {
            //


            switchToContact();

            autoSet();

#ifdef  __DEBUG__
            showInfo_open0(0, null, _T("mainWnd. get ID_qyRefresh"));
#endif 

            QY_MC* pQyMc = QY_GET_GBUF();
            CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();
            if (!pProcInfo)  return  true;
            MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
            if (!pMisCnt) return true;
            //
            if (bDone_retrieveAllImObjRules(pMisCnt) && loadInfoFinishInit == FALSE)
            {
                //
#ifdef  __DEBUG__
                showInfo_open0(0, null, _T("before initCMainFrameInfo"));
                pQyMc->dbg.dwTickCnt_bDone_retrieveAllImObjRules = myGetTickCount(NULL);
                int  iDiffInMs = pQyMc->dbg.dwTickCnt_bDone_retrieveAllImObjRules - pQyMc->dwTickCnt_logon;
                int  ii = 0;
#endif

                //
                loadInfoFinishInit = TRUE;
                initCMainFrameInfo();

#ifdef  __DEBUG__
                showInfo_open0(0, null, _T("after initCMainFrameInfo"));
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

    //
    return false;
}

//

void CMainFrame::painterMenu(const QString pushBtnName)
{
    //消息
    if (pushBtnName.contains("toolBtnMsg"))
    {
        ui->toolBtnMsg->setIcon(QIcon(":/Resources/Images/WinMain/icon_last_hover.png"));
        ui->toolBtnMsg->setIconSize(QSize(39, 39));
        ui->toolBtnMsg->setText(u8"消息");
        ui->toolBtnMsg->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    }
    else
    {
        ui->toolBtnMsg->setIcon(QIcon(":/Resources/Images/WinMain/icon_last_normal.png"));
        ui->toolBtnMsg->setIconSize(QSize(39, 39));
        ui->toolBtnMsg->setText(u8"消息");
        ui->toolBtnMsg->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    }
    //联系人
    if (pushBtnName.contains("toolBtnContact"))
    {
        QPixmap infoMsgBtnPixmap(":/Resources/Images/WinMain/icon_group_hover.png");
        ui->toolBtnContact->setIcon(QIcon(":/Resources/Images/WinMain/icon_group_hover.png"));
        ui->toolBtnContact->setIconSize(QSize(39, 39));
        ui->toolBtnContact->setText(u8"联系人");
        ui->toolBtnContact->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    }
    else
    {
        ui->toolBtnContact->setIcon(QIcon(":/Resources/Images/WinMain/icon_group_normal.png"));
        ui->toolBtnContact->setIconSize(QSize(39, 39));
        ui->toolBtnContact->setText(u8"联系人");
        ui->toolBtnContact->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    }
    //系统设置
    if (pushBtnName.contains("toolBtnSystem"))
    {
        ui->toolBtnSystem->setIcon(QIcon(":/Resources/Images/WinMain/icon_set_hover.png"));
        ui->toolBtnSystem->setIconSize(QSize(39, 39));
        ui->toolBtnSystem->setText(u8"设置");
        ui->toolBtnSystem->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    }
    else
    {
        ui->toolBtnSystem->setIcon(QIcon(":/Resources/Images/WinMain/icon_set_normal.png"));
        ui->toolBtnSystem->setIconSize(QSize(39, 39));
        ui->toolBtnSystem->setText(u8"设置");
       
        ui->toolBtnSystem->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    }
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
        m_myName=("("+ QString::number(ui64Id) + ")");
    }
    else {
        m_myName=(pSyr);
    }
    ui->userName->setText(m_myName);
   
    //
    ui->signName->setText(pDw + " " + pBm);

    //
    showInfo_open0(0, null, _T("CMainFrame::initCMainFrameInfo, set userName"));

    //
    WinTalkList* pTalkList = (WinTalkList*)ui->stackedWidgetContact->widget(0);
    if (pTalkList)
    {
        pTalkList->initWinTalkListInfo();
    }
    return iRet;
}

#if 0
void CMainFrame::mouseMoveEvent(QMouseEvent* event)
{
    //最大化状态时不能拉伸
    if (isMaximized())
    {
        return;
    }
    //根据位置设置鼠标样式
    qDebug() << "x====" << event->pos().x() << "y===========" << event->pos().y();
    SetMouseCursor(event->pos().x(), event->pos().y());

    if ((event->buttons() == Qt::LeftButton) && left_button_pressed_)
    {

        QPoint point_offset = event->globalPos() - last_position_;
        if (mouse_press_region_ == kMousePositionMid)
        {

            setCursor(Qt::ArrowCursor);
            move(point_offset + last_point_);
        }
        else
        {

            QRect rect = geometry();
            switch (mouse_press_region_)
            {

            case kMousePositionLeftTop:
                rect.setTopLeft(rect.topLeft() + point_offset);
                break;
            case kMousePositionTop:
                rect.setTop(rect.top() + point_offset.y());
                break;
            case kMousePositionRightTop:
                rect.setTopRight(rect.topRight() + point_offset);
                break;
            case kMousePositionRight:
                rect.setRight(rect.right() + point_offset.x());
                break;
            case kMousePositionRightButtom:
                rect.setBottomRight(rect.bottomRight() + point_offset);
                break;
            case kMousePositionButtom:
                rect.setBottom(rect.bottom() + point_offset.y());
                break;
            case kMousePositionLeftButtom:
                rect.setBottomLeft(rect.bottomLeft() + point_offset);
                break;
            case kMousePositionLeft:
                rect.setLeft(rect.left() + point_offset.x());
                break;
            default:
                break;
            }
            setGeometry(rect);
            last_position_ = event->globalPos();
        }
    }
}


void CMainFrame::mouseReleaseEvent(QMouseEvent*)
{

    left_button_pressed_ = false;
}

void CMainFrame::mousePressEvent(QMouseEvent* event)
{

    if (event->buttons() == Qt::LeftButton) {

        left_button_pressed_ = true;
        last_point_ = pos();
        last_position_ = event->globalPos();
        mouse_press_region_ = GetMouseRegion(event->pos().x(), event->pos().y());
    }
}

void CMainFrame::SetMouseCursor(int x, int y)
{

    Qt::CursorShape cursor;
    int region = GetMouseRegion(x, y);
    // qDebug() << "region----------------" << region;
    switch (region)
    {

    case kMousePositionLeftTop:
    case kMousePositionRightButtom:
        cursor = Qt::SizeFDiagCursor; break;
    case kMousePositionRightTop:
    case kMousePositionLeftButtom:
        cursor = Qt::SizeBDiagCursor; break;
    case kMousePositionLeft:
    case kMousePositionRight:
        cursor = Qt::SizeHorCursor; break;
    case kMousePositionTop:
    case kMousePositionButtom:
        cursor = Qt::SizeVerCursor; break;
    case kMousePositionMid:
        cursor = Qt::ArrowCursor; break;
    default:
        break;
    }
    setCursor(cursor);
}

int CMainFrame::GetMouseRegion(int x, int y)
{

    int region_x = 0, region_y = 0;
    if (x < kMouseRegionLeft)
    {

        region_x = 1;
    }
    else if (x > (width() - kMouseRegionRight))
    {

        region_x = 3;
    }
    else
    {

        region_x = 2;
    }
    if (y < kMouseRegionTop)
    {

        region_y = 1;
    }
    else if (y > (height() - kMouseRegionButtom))
    {

        region_y = 3;
    }
    else
    {

        region_y = 2;
    }
    return region_y * 10 + region_x;
}
#endif

bool CMainFrame::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == ui->signName || obj == ui->userName)
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
    }
    return QWidget::eventFilter(obj, event);
}

void CMainFrame::on_headIcoBtn_clicked()
{
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    qint64 uid = pMisCnt->idInfo.ui64Id;
    QString userName = ui->userName->text();
    QString dw = ui->signName->text();

    UserInfoDialog::showDialog(QString::number(uid), userName, dw);
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
        QString name = QString::fromUtf16((char16_t*)desc.pDw) + "  " + QString::fromUtf16((char16_t*)desc.pBm) + "  " + QString::fromUtf16((char16_t*)desc.pSyr) + "(" + QString::number(pQMem->messengerInfo.idInfo.ui64Id) + ")";
        int of_res = name.indexOf(pStr, 0, Qt::CaseInsensitive);
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
    if (!pDbFuncs)  goto  errLabel;
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
        int of_res = name.indexOf(pStr, 0, Qt::CaseInsensitive);
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
    QRect rec = ui->stackedWidgetContact->geometry();
    searchListView_->setGeometry(ui->stackedWidgetContact->geometry());
    searchListView_->show();



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

        QModelIndex s = searchListView_->model()->index(j,0);
     
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
    for (int i = 0; i < _searchList.size();i++) 
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
    WinTalkList* pTalkList = (WinTalkList*)ui->stackedWidgetContact->widget(0);
   
    
    pTalkList->addListWidget(user);
    on_Contact_Msg(user);
    painterMenu("toolBtnMsg");
}

//搜索框滚动条事件
void CMainFrame::onScrollBarValueChanged(int value)
{
    onLineStatusUp();
}

void CMainFrame::cut_talk_list(WinObjUser user) {
    WinTalkList* pTalkList = (WinTalkList*)ui->stackedWidgetContact->widget(0);
    pTalkList->addListWidget(user);
    on_Contact_Msg(user);
    painterMenu("toolBtnMsg");
    this->activateWindow();
}

int  CMainFrame::displayRecentFriends(MIS_MSG_displayRecentFriends_qmc* pMsg)
{
    WinTalkList* pTalkList = (WinTalkList*)ui->stackedWidgetContact->widget(0);
    for (int j = 0; j < pMsg->resp.usCnt; j++)
    {
        if (pMsg->resp.mems[j].usRunningStatus != CONST_usRunningStatus_online) {
            pTalkList->updateTalkItem(pMsg->resp.mems[j].idInfo.ui64Id, pMsg->resp.mems[j].usRunningStatus);
        }
        else if (pMsg->resp.mems[j].usRunningStatus == CONST_usRunningStatus_online) {
            pTalkList->updateTalkItem(pMsg->resp.mems[j].idInfo.ui64Id, pMsg->resp.mems[j].usRunningStatus);
        }
    }

    WinContactsList* pContactsList = (WinContactsList*)ui->stackedWidgetContact->widget(1);
    for (int i = 0; i < pMsg->resp.usCnt; i++) 
    {
        if (pMsg->resp.mems[i].usRunningStatus != CONST_usRunningStatus_online) {
            pContactsList->updateContactItem(pMsg->resp.mems[i].idInfo.ui64Id , pMsg->resp.mems[i].usRunningStatus);
        }
        else if (pMsg->resp.mems[i].usRunningStatus == CONST_usRunningStatus_online) {
            pContactsList->updateContactItem(pMsg->resp.mems[i].idInfo.ui64Id , pMsg->resp.mems[i].usRunningStatus);
        }
    }

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

