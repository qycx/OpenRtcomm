



#include	"stdafx.h"

#define  __noDbg_new__

#include "WinTalkList.h"
#include "ui_WinTalkList.h" 
#include "qyMcMainCommon_qt.h"
#include	"qmcCommFunc_mis.h"
#include "CMainFrame.h"
#include	"ctxQmc_qt.h"
#include "MessageSignalCenter.h"
#include <QAbstractItemView>
#include "CDlgTalk_qt.h"
#include "DBManager.h"
#include "QSystemTrayIconEx.h"
//
#include    "oldConfs.h"
#include "mLogger.h"
#pragma execution_character_set("UTF-8")

WinTalkList::WinTalkList(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::WinTalkList)
{
    //this->parent = parent;
    ui->setupUi(this);

    
   // ui->listWidgetMsg->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    
    initControl();

    this->setStyleSheet("");
    this->setStyleSheet("QWidget#listWidgetMsg { border-bottom: 1px solid rgba(22, 154, 218, 100);  border:none;} "\
        "listWidgetMsg::item:selected{background:rgba(22, 154, 218, 50); }");
    ui->listWidgetMsg->verticalScrollBar()->setStyleSheet("QScrollBar{width:10px;}");
    QScrollBar * verticalScrollBar = ui->listWidgetMsg->verticalScrollBar();

    connect(verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(onScrollBarValueChanged(int)));
    
  

    List_video_ing_timer_ = new QTimer(this);
    List_video_ing_timer_->setInterval(3000);
    connect(List_video_ing_timer_, &QTimer::timeout, [this]()
        {
            _videoIng.clear();
            OldConfs  oldConfs = { 0 };
            if (!findOldRecvdConfsActive(&oldConfs))
            {
                for (int i = 0; i < oldConfs.usCnt; i++) {
                    OldConfMem* pMem = &oldConfs.mems[i];
                    videoIng tmp_videoIng;
                    tmp_videoIng.idInfo_peer = pMem->idInfo_peer.ui64Id;
                    tmp_videoIng.iTaskId = pMem->iTaskId;

                    _videoIng.append(tmp_videoIng);
                }
            }
        });

    List_video_ing_timer_->start();

}

//捕捉滚动条事件
void WinTalkList::onScrollBarValueChanged(int value)
{
    onLineStatusUp();
}

WinTalkList::~WinTalkList()
{
    delete ui;

     if (List_video_ing_timer_) {
      delete List_video_ing_timer_;
      List_video_ing_timer_ = nullptr;
  }
  
}

void WinTalkList::initControl()
{
    connect(&MessageSignalCenter::Instance(), &MessageSignalCenter::signal_recv_new_message, this, &WinTalkList::slot_recv_new_message);


#if 0
   
    //connect(ui->listWidgetMsg, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(on_ListWidget_clicked(QListWidgetItem*)));
#endif
}

void WinTalkList::load_initList() 
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();
    DBManager* pDm = (DBManager*)pProcInfo->m_var.pDBManager;


      
#if 1
    //查询库记录

    QList<SessionInfo> siList = pDm->getSessions();

    if (siList.size() == 0)
    {
#if 0
        CMainFrame* pMainWnd = (CMainFrame*)CMainFrame::find((WId)pQyMc->gui.hMainWnd);
        if (pMainWnd) {
            pMainWnd->switchToContact();
        }
#endif

        //
        return;
    }
    
    //
    for (int i = 0 ;  i <= siList.size() - 1; i++)
    {
        
        unsigned  int  uiObjType = 0;
        QString name = QString::fromUtf16((char16_t*)siList[i].session_name);
        QString info = QString::fromUtf16((char16_t*)siList[i].content);
        char		bufTime[256] = "";
        QString pTime = "";
        QString ctime = QString::number(siList[i].time_stamp);

        QListWidgetItem* pChild = new QListWidgetItem();
        pChild->setSizeHint(QSize(80, 80));
        WinObjUser user;
        user.name = name;
        user.idinfo = QString::number(siList[i].session_id);
        //  user.dw = dw;
         // user.bm = bm;
        pChild->setData(Qt::UserRole, QString::number(siList[i].session_id));
        pChild->setData(Qt::UserRole + 1, QVariant::fromValue(user));
        WinContactItem* pContactItem = new WinContactItem(user.idinfo, ui->listWidgetMsg);
      

        if (siList[i].chat_type == 0) {
            pContactItem->setHeadPixmap(QPixmap(":/Resources/Images/WinMain/person.png"));
      
        }
        else {
            if (siList[i].grp_creator) {
                pContactItem->setHeadPixmap(QPixmap(":/Resources/Images/WinMain/tmp_group.png"));
            }
            else {
                pContactItem->setHeadPixmap(QPixmap(":/Resources/Images/WinMain/group.png"));
            }
            
        }
        
        
        
pContactItem->setUserName(name);
        pContactItem->isTimeShow(true);
        pContactItem->setSignName(info);
        
        displayShortTime(siList[i].time_stamp, bufTime, mycountof(bufTime));
        QString str(bufTime);
        pTime = bufTime;

        pContactItem->setSendTime(pTime);
       // qDebug() << "winContactItem" << siList[i].session_id;
        pContactItem->setObjectName("winContactItem" + siList[i].session_id);
        ui->listWidgetMsg->insertItem(i, pChild);
        ui->listWidgetMsg->setItemWidget(pChild, pContactItem);
    }
    if (ui->listWidgetMsg->count() > 0)
    {
        ui->listWidgetMsg->setCurrentRow(0);
    }


#endif



#if 0
    QMap<int, QString> talkMap;
    const QString&& path = QApplication::applicationDirPath() + "/" + QString("infoconf.ini");
    QSettings settings(path, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    QStringList groupList = settings.childGroups();
    foreach(QString group, groupList)
    {
        int rownum = settings.value(QString("/%1/%2").arg(group).arg("rownum")).toInt();
        talkMap.insert((rownum * (-1)), group);
    }
    QMap<int, QString>::Iterator it = talkMap.begin();
    int row = 0;
    while (it != talkMap.end())
    {
        QString name = settings.value(QString("/%1/%2").arg(it.value()).arg("name")).toString();
        QString dw = settings.value(QString("/%1/%2").arg(it.value()).arg("dw")).toString();
        QString bm = settings.value(QString("/%1/%2").arg(it.value()).arg("bm")).toString();
        QString info = settings.value(QString("/%1/%2").arg(it.value()).arg("info")).toString();
        QString ctime = settings.value(QString("/%1/%2").arg(it.value()).arg("time")).toString();

        QListWidgetItem* pChild = new QListWidgetItem();
        pChild->setSizeHint(QSize(50, 62));
        WinObjUser user;
        user.idinfo = it.value();
        user.name = name;
        user.dw = dw;
        user.bm = bm;
        pChild->setData(Qt::UserRole, it.value());
        pChild->setData(Qt::UserRole + 1, QVariant::fromValue(user));
        WinContactItem* pContactItem = new WinContactItem(user.idinfo, ui->listWidgetMsg);
        unsigned  int  uiObjType_from = 0;

        //getTalkerDesc(user.idinfo, &uiObjType_from, null, 0, null, null, 0, null, 0, null,0);

        int  m_nContactsIndex = 0;
        CMainFrame* pMainWnd = (CMainFrame*)this->parent();
        if (pMainWnd != NULL) {
            m_nContactsIndex = pMainWnd->m_nContactsIndex;
        }
        if (m_nContactsIndex == 0)
        {
            //群组信息
            pContactItem->setHeadPixmap(QPixmap(":/Resources/Images/WinMain/group.png"));
        }
        else if (m_nContactsIndex == 1)
        {

            pContactItem->setHeadPixmap(QPixmap(":/Resources/Images/WinMain/tmp_group.png"));
        }
        else if (m_nContactsIndex == 2)
        {
            //联系人信息
            pContactItem->setHeadPixmap(QPixmap(":/Resources/Images/WinMain/person.png"));
        }
        pContactItem->setUserName(name);
        pContactItem->isTimeShow(true);
        pContactItem->setSignName(info);
        pContactItem->setSendTime(ctime);
        qDebug() << "winContactItem" << it.value();
        pContactItem->setObjectName("winContactItem" + it.value());
        ui->listWidgetMsg->insertItem(row, pChild);
        ui->listWidgetMsg->setItemWidget(pChild, pContactItem);
        row++;
        it++;
}
    if (ui->listWidgetMsg->count() > 0)
    {
        ui->listWidgetMsg->setCurrentRow(0);
    }
#endif
}


void WinTalkList::initWinTalkListInfo()
{
   // qDebug() << "----------------" << ui->listWidgetMsg->count();
    if (ui->listWidgetMsg->count() > 0)
    {
        QListWidgetItem* currentItem = ui->listWidgetMsg->currentItem();
        QVariant variant = currentItem->data(Qt::UserRole + 1);
        WinObjUser user = variant.value<WinObjUser>();
        onLineStatusUp();
        emit toShowContactMsg(user);

        //emit toCDlgTalk(user);
        //emit toCDlgTalkInfo(user);
    }
}

void WinTalkList::on_listWidgetMsg_itemClicked(QListWidgetItem* item)
{ 
   
    QVariant variant = item->data(Qt::UserRole + 1);
    WinObjUser user = variant.value<WinObjUser>();
    WinContactItem* pContactItem = qobject_cast<WinContactItem*>(ui->listWidgetMsg->itemWidget(item));
    CCtxQyMc* pQyMc = g_pQyMc; 
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();  

    //removeSession();
    if (pContactItem)
    { 
        int msgCount = pContactItem->GetMsgCount();
        pContactItem->Clear();   
        QWidget* qMainWnd = this->topLevelWidget(); 
        CMainFrame* cMainFrame = qobject_cast<CMainFrame*>(qMainWnd);
        cMainFrame->UpMsgCount(msgCount); 
    }
    //
    onLineStatusUp();
    emit toShowContactMsg(user);
  //  WinMsgShow * aaa = new WinMsgShow();
   
    //
    //emit toCDlgTalk(user);
    //emit toCDlgTalkInfo(user);
}

//void WinTalkList::do_addTalkInfoList(QString idinfo, QString info) 
//{
//	for (int i = 0; i < ui->listWidget->count(); i++) 
//	{
//		QListWidgetItem* widgetItem = ui->listWidget->item(i);
//		QString idinfo_d = widgetItem->data(Qt::UserRole).toString();
//		if (idinfo == idinfo_d) 
//		{
//			QListWidget* listWidget = widgetItem->listWidget();
//			WinContactItem* winContactItem = listWidget->findChild<WinContactItem*>("winContactItem" + idinfo);
//			winContactItem->setSignName(info);
//			break;
//		}
//	}
//}


int  WinTalkList::onLineStatusUp()
{
    QY_MC* pQyMc = QY_GET_GBUF();
    QY_MESSENGER_ID  idInfo;

    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return  -1;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (!pMisCnt)  return  -1;
    int height_s = ui->listWidgetMsg->height();
    for (int j = 0; j < ui->listWidgetMsg->count(); j++)
    {
        QListWidgetItem* item = ui->listWidgetMsg->item(j);
        QRect rc = ui->listWidgetMsg->visualItemRect(item);
       // qDebug() << "item[" << j << "]," << rc.x() << "," << rc.y() << "," << rc.top() << "," << rc.bottom() << ",";
        if (rc.bottom() < height_s && rc.top() >= 0) {
            QVariant variant = item->data(Qt::UserRole + 1);
            WinObjUser user = variant.value<WinObjUser>();

            idInfo.ui64Id = user.idinfo.toInt();
            postRecentFriend(pMisCnt, idInfo, 0);

        }
        //
        continue;
    }
    pMisCnt->refreshRecentFriends.bRefreshAtOnce = true;

    return 0;
}

void WinTalkList::updateTalkItem(qint64 idInfo, unsigned  short status) 
{
    unsigned  int  uiObjType = 0;
    QY_MESSENGER_ID ui_idInfo;

    ui_idInfo.ui64Id = idInfo;
    getTalkerDesc(ui_idInfo, &uiObjType, mynull, mynull, mynull, mynull, mynull, mynull, mynull, mynull, mynull);
    if (uiObjType == CONST_objType_imGrp) {
        //检测有没有任务组再运行
        for (int i = 0; i < ui->listWidgetMsg->count(); i++)
        {
            QListWidgetItem* listItem = ui->listWidgetMsg->item(i);
            QString itemIdInfo = listItem->data(Qt::UserRole).toString();

            WinContactItem* winItem = (WinContactItem*)ui->listWidgetMsg->itemWidget(listItem);
            //
            winItem->isIconVideoIng(false);
            for (int v_i = 0; v_i < _videoIng.size(); v_i++) {

                if (itemIdInfo.toInt() == _videoIng[v_i].idInfo_peer) {
                    winItem->isIconVideoIng(true);
                }
            }
        }
    }

    for (int i = 0; i < ui->listWidgetMsg->count(); i++)
    {
        QListWidgetItem* listItem = ui->listWidgetMsg->item(i);
        QString itemIdInfo = listItem->data(Qt::UserRole).toString();
       
        if (itemIdInfo.toInt() == idInfo)
        {
            //ui->listWidgetMsg->removeItemWidget(listItem);
            WinContactItem* winItem = (WinContactItem*)ui->listWidgetMsg->itemWidget(listItem);
            //QPixmap pix1(":/Resources/Images/WinMain/person.png");

            if (status != CONST_usRunningStatus_online) {
                winItem->isOnLine(false);
            }
            else {
                winItem->isOnLine(true);
            }
        }
    }
}



void WinTalkList::doNotify(SendData sd, SessionInfo si, WinContactItem * pContactItem)
    {
    if (g_pMainWndInstance == nullptr) {
        return;
    }
    NotifyMsgEvent* event = new NotifyMsgEvent(sd, si, pContactItem);

    QApplication::postEvent(g_pMainWndInstance, event);
  
 /*

    CCtxQyMc* pQyMc = g_pQyMc;
    HWND hMainWnd = pQyMc->gui.hMainWnd;
    PlaySoundEvent* event = new PlaySoundEvent();
    CMainFrame* pMainWnd_s = (CMainFrame*)getObjAddr(hMainWnd);


    if (pMainWnd_s == nullptr) {
        QWidget* pWidget = QWidget::find((WId)hMainWnd);
        if (pWidget) {
            QApplication::postEvent(pWidget, new PlaySoundEvent());
             WriteLog("Notify: Event posted to main thread.");
        }
        else {
             WriteLog("Notify: Failed to find widget from HWND.");
        }

        return;
    }


    //CCtxQyMc* pQyMc = g_pQyMc;
    //HWND  hMainWnd = pQyMc->gui.hMainWnd;
    //CMainFrame* pMainWnd_s;
    //pMainWnd_s = (CMainFrame*)getObjAddr(hMainWnd);
    ////if (pMainWnd_s == nullptr) {
    ////    char logBuf[256];
    ////    sprintf_s(logBuf, "pMainWnd_s is null. hMainWnd Value: %p ", hMainWnd);
    ////    WriteLog(logBuf);
    ////    return;
    ////}


    //if (pMainWnd_s == nullptr) {
    //    return;
    //}
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

    ////
    bool isMainWndVisible = pMainWnd_s->isVisible();
    bool isMainMini = pMainWnd_s->isMinimized();
    bool isMsgSel = pMainWnd_s->isMsgSel();
    QY_MESSENGER_ID curIdInfo;
    pMainWnd_s->getCurIdInfo(&curIdInfo);


    if (sd.from_id.ui64Id != pMisCnt->idInfo.ui64Id) {
        //提示音 以及闪烁
        pMainWnd_s->playReciveSound();
        // if (isTaskWindows) {
        pMainWnd_s->flashTaskWindow();
        //}

        if (!isMainWndVisible || isMainMini || !isMsgSel || curIdInfo.ui64Id!=sd.peer_id.ui64Id) {



            pContactItem->AddNewMsgCount(1);
            pMainWnd_s->AddNewMsgCount(1);

            //托盘
            pMainWnd_s->tray_infrom(si);
        }
    }

 */

}

void WinTalkList::slot_recv_new_message(SendData sd)
{
    //MIS_MSG_TALK* pMsg = (MIS_MSG_TALK*)talk;
    //IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->data.buf;
    //
    int iErr = -1;
    QY_MESSENGER_ID addr_logicalPeer_idInfo = sd.peer_id;
    QY_MESSENGER_ID  idInfo_from = sd.from_id;

    unsigned  int  uiObjType_peer = 0;
    unsigned  int  uiObjType_from = 0;
    TCHAR grpName_peer[128] = _T("");
    TCHAR srcName_peer[128] = _T("");

    TCHAR grpName_from[128] = _T("");
    TCHAR srcName_from[128] = _T("");

    char		bufTime[256] = "";
    time_t tRecvTime = sd.send_time;

    WinObjUser user;

    displayShortTime(tRecvTime, bufTime, mycountof(bufTime));
        QString str(bufTime);
    QY_MESSENGER_ID  idInfo_creator;
   
    
    getTalkerDesc(addr_logicalPeer_idInfo, &uiObjType_peer, grpName_peer, mycountof(grpName_peer), &idInfo_creator, mynull, 0, mynull, 0, srcName_peer, mycountof(srcName_peer));
   
    getTalkerDesc(idInfo_from, &uiObjType_from, grpName_from, mycountof(grpName_from), &idInfo_creator, mynull, 0, mynull, 0, srcName_from, mycountof(srcName_from));
     
   
    //TCHAR转QString
    QString msg = QString::fromStdWString(std::wstring(sd.msg));
    //
   /* switch (pContent->uiType)
    {
    case CONST_imCommType_htmlContent:
    {
        msg = QString::fromStdWString(std::wstring(pContent->html.wBuf));
    }
    break;
    }*/

    CCtxQyMc* pQyMc = g_pQyMc;
    HWND  hMainWnd = pQyMc->gui.hMainWnd;
    CMainFrame* pMainWnd_s;
    pMainWnd_s = (CMainFrame*)getObjAddr(hMainWnd);
    unsigned  int puiObjType;

    CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();
    DBManager* pDm = (DBManager*)pProcInfo->m_var.pDBManager;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    QString qstr;

    //记录一条 
    SessionInfo si;
    memset(&si, 0, sizeof(si));
    if (uiObjType_peer == CONST_objType_imGrp) {
        si.chat_type = ChatType::GroupChat;
        si.grp_creator = idInfo_creator.ui64Id;
        //si.session_name = QString::fromStdWString(grpName_peer);
        lstrcpyn(si.session_name, grpName_peer, mycountof(si.session_name));
    }
    else {
        si.chat_type = ChatType::OneChat;
        //si.session_name = QString::fromStdWString(srcName_peer);
        lstrcpyn(si.session_name, srcName_peer, mycountof(si.session_name));
    }

    //si.content = QString::fromStdWString(srcName_from) + "：" + msg;
    _sntprintf(si.content, mycountof(si.content), _T("%s: %s"), srcName_from, sd.msg);
    //si.header_url = ":/Resources/Images/WinMain/tmp_group.png";
    lstrcpyn(si.header_url, _T( ":/Resources/Images/WinMain/tmp_group.png"),mycountof( si.header_url));
    si.msg_type = MessageTypes::TextMessage;
    //si.session_id = QString::number(sd.peer_id.ui64Id);
    si.session_id = sd.peer_id.ui64Id;
  
    //
    si.time_stamp = sd.send_time;

    if (si.session_name[0] == _T('\0')) {
        //lstrcpyn(si.session_name , (wchar_t * )sd.peer_id.ui64Id,mycountof(si.session_name));
        //si.session_name = sd.peer_id.ui64Id;
        lstrcpyn(si.session_name, (wchar_t*)(QString::number(sd.peer_id.ui64Id)).utf16(), mycountof(si.session_name));
    }

  
    
  
    for (int i = 0; i < ui->listWidgetMsg->count(); i++)
    {
        QListWidgetItem* item = ui->listWidgetMsg->item(i);
        WinContactItem* pContactItem = qobject_cast<WinContactItem*>(ui->listWidgetMsg->itemWidget(item));
        //
        qstr = pContactItem->ID();
       // if (pContactItem && pContactItem->ID() == QString::number(idInfo_from.ui64Id))
        if (pContactItem && pContactItem->ID() == QString::number(addr_logicalPeer_idInfo.ui64Id))
        {
           
            if (sd.iTaskId) 
            {
                if (pContactItem->m_iTaskId == sd.iTaskId) {
                    pContactItem->setSendTime(bufTime);
                    if (uiObjType_peer == CONST_objType_imGrp) {
                        pContactItem->setSignName(QString::fromStdWString(srcName_from) + ": " + msg);
                    }
                    else {
                        pContactItem->setSignName(msg);
                    }
                   
                    iErr = 0;  goto  errLabel;
                }
            }
            pDm->insertSession(si);

            //
            if (sd.from_id.ui64Id != pMisCnt->idInfo.ui64Id) {
                //提示音 以及闪烁
                pMainWnd_s->playReciveSound();
                pMainWnd_s->flashTaskWindow();
            }

            //ui->listWidgetMsg->setItemWidget(item, null);
            bool isSelected = item->isSelected();

            if (i == 0) {
                pContactItem->setSendTime(bufTime);
                pContactItem->setSignName(msg);
                if (sd.iTaskId) {
                    pContactItem->m_iTaskId = sd.iTaskId;
                }
                //
                this->doNotify(sd,si,pContactItem);
                //
                iErr = 0;  goto  errLabel;
            }

           // pContactItem->setSignName(msg);
            item = new QListWidgetItem();
            item->setSizeHint(QSize(80, 80));
          
            pContactItem->setSendTime(bufTime);
            pContactItem->m_iTaskId = sd.iTaskId;
            pContactItem->isTimeShow(true);
            WinObjUser user;
            SessionInfo si;
            memset(&si, 0, sizeof(si));
            if (uiObjType_peer == CONST_objType_imGrp) {
                user.idinfo = QString::number(addr_logicalPeer_idInfo.ui64Id);
                user.name = QString::fromStdWString(grpName_peer);
                pContactItem->setSignName(QString::fromStdWString(srcName_from) + ": " + msg);
               // pContactItem->setUserName(QString::fromStdWString(grpName_peer));

                lstrcpyn(si.header_url, _T(":/Resources/Images/WinMain/group.png"), mycountof(si.header_url));
                
            }
            else {
                user.idinfo = QString::number(addr_logicalPeer_idInfo.ui64Id);
                user.name = QString::fromStdWString(srcName_peer);
                pContactItem->setSignName(msg);
                
                lstrcpyn(si.header_url, _T(":/Resources/Images/WinMain/person.png"), mycountof(si.header_url));
                
                
            }
            if (user.name.isEmpty()) 
            {
                user.name = user.idinfo;
            }

              
            pContactItem->setUserName(user.name);
            item->setData(Qt::UserRole, user.idinfo);
            item->setData(Qt::UserRole + 1, QVariant::fromValue(user));
            ui->listWidgetMsg->insertItem(0, item);
            ui->listWidgetMsg->setItemWidget(item, pContactItem);
            ui->listWidgetMsg->takeItem(i + 1);
         

            si.session_id = user.idinfo.toInt();
            // si.session_name = user.name;
            lstrcpyn(si.session_name, (wchar_t*)(user.name).utf16(), mycountof(si.session_name));
            si.unread_count = 1;
            //
            this->doNotify(sd, si, pContactItem);

            return;
        }

    }
    QListWidgetItem* item;
    item = new QListWidgetItem();
    item->setSizeHint(QSize(80, 80));
 
    user.idinfo = QString::number(addr_logicalPeer_idInfo.ui64Id);
    if (grpName_peer[0] != _T('\0')) {
        user.name = QString::fromStdWString(grpName_peer);
    }
    else {
        user.name = QString::fromStdWString(srcName_peer);
    }
   
    item->setData(Qt::UserRole, user.idinfo);
    item->setData(Qt::UserRole + 1, QVariant::fromValue(user));
    
    //
    if (uiObjType_peer == CONST_objType_imGrp) {
        WinContactItem* pContactItem;
        pContactItem = new WinContactItem(QString::number(addr_logicalPeer_idInfo.ui64Id), ui->listWidgetMsg);
        if (sd.from_id.ui64Id != pMisCnt->idInfo.ui64Id) {

            //
            SessionInfo si;
            memset(&si,0,sizeof(si));
            si.session_id = addr_logicalPeer_idInfo.ui64Id;
            lstrcpyn(si.header_url, _T(":/Resources/Images/WinMain/group.png"), mycountof(si.header_url));
            lstrcpyn(si.session_name, (wchar_t*)(user.name).utf16(), mycountof(si.session_name));
            // si.session_name = user.name;
            si.unread_count = 1;

            //pMainWnd_s->tray_infrom(si);
            doNotify(sd, si, pContactItem);
        }

        pContactItem->setUserName(QString::fromStdWString(grpName_peer));
        pContactItem->setObjectName("winContactItem" + QString::number(addr_logicalPeer_idInfo.ui64Id));
        pContactItem->setSignName(QString::fromStdWString(srcName_from) + ": " + msg);
        pContactItem->setSendTime(bufTime);
        pContactItem->isTimeShow(true);
        pContactItem->m_iTaskId = sd.iTaskId;
        pContactItem->setHeadPixmap(QPixmap(":/Resources/Images/WinMain/person.png"));
        ui->listWidgetMsg->insertItem(0, item);
        ui->listWidgetMsg->setItemWidget(item, pContactItem);
    }
    else {
        WinContactItem* pContactItem;
        pContactItem = new WinContactItem(QString::number(addr_logicalPeer_idInfo.ui64Id), ui->listWidgetMsg);
        
        if (sd.from_id.ui64Id != pMisCnt->idInfo.ui64Id) {

            SessionInfo si;
            memset(&si, 0 ,sizeof(si));
            si.session_id = idInfo_from.ui64Id;
            lstrcpyn(si.header_url, _T(":/Resources/Images/WinMain/person.png"), mycountof(si.header_url));
            lstrcpyn(si.session_name, (wchar_t*)(user.name).utf16(), mycountof(si.session_name));
            // si.session_name = user.name;
            si.unread_count = 1;

            //pMainWnd_s->tray_infrom(si);
            doNotify(sd, si, pContactItem);
        }
        
        pContactItem->setUserName(QString::fromStdWString(srcName_peer));
        pContactItem->setObjectName("winContactItem" + QString::number(idInfo_from.ui64Id));
        pContactItem->isTimeShow(true);
        pContactItem->m_iTaskId = sd.iTaskId;
        pContactItem->setSignName(QString::fromStdWString(srcName_from) + ": " + msg);
        pContactItem->setSendTime(bufTime);
        pContactItem->setHeadPixmap(QPixmap(":/Resources/Images/WinMain/person.png"));
        
        ui->listWidgetMsg->insertItem(0, item);
        ui->listWidgetMsg->setItemWidget(item, pContactItem);
    }
errLabel:
    return ;
}

void WinTalkList::addListWidget(WinObjUser user)
{
    QY_MESSENGER_ID idinfo;
    unsigned  int  uiObjType = 0;

    TCHAR grpName_from[128] = _T("");
    TCHAR srcName_from[128] = _T("");
    QString username;
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();
    DBManager* pDm = (DBManager*)pProcInfo->m_var.pDBManager;
    SessionInfo si;
    memset(&si, 0, sizeof(si));
    idinfo.ui64Id = user.idinfo.toInt();
    //delete
    for (int i = 0; i < ui->listWidgetMsg->count(); i++)
    {
        QListWidgetItem* listItem = ui->listWidgetMsg->item(i);
        QString itemIdInfo = listItem->data(Qt::UserRole).toString();
        if (itemIdInfo == user.idinfo)
        {
            ui->listWidgetMsg->removeItemWidget(listItem);
            delete listItem;
            break;
        }
    }

  
   
    

    QY_MESSENGER_ID idInfo_creator;
    getTalkerDesc(idinfo, &uiObjType, grpName_from, mycountof(grpName_from), &idInfo_creator, mynull, 0, mynull, 0, srcName_from, mycountof(srcName_from));
    QString head = "";

  

    si.session_id = user.idinfo.toInt();
   
    if (uiObjType == CONST_objType_imGrp) {
        if (idInfo_creator.ui64Id != 0) {
            si.grp_creator = idInfo_creator.ui64Id;
        }
        username = QString::fromStdWString(grpName_from);
        si.chat_type = ChatType::GroupChat;
        if (idInfo_creator.ui64Id) {
            head = ":/Resources/Images/WinMain/tmp_group.png";
            }
        else {
            head = ":/Resources/Images/WinMain/group.png";
        }
    }
    else {
        si.chat_type = ChatType::OneChat;
        username = QString::fromStdWString(srcName_from);
        head = ":/Resources/Images/WinMain/person.png";
    }

    if (username.isEmpty()) {
        username = user.idinfo;
    }



    lstrcpyn(si.header_url, (wchar_t*)(head).utf16(), mycountof(si.header_url));
    lstrcpyn(si.session_name, (wchar_t*)(username).utf16(), mycountof(si.session_name));
    lstrcpyn(si.content, _T(""), mycountof(si.content));
   

    


    //获取序号 
    const QString&& syspath = QApplication::applicationDirPath() + "/" + QString("qysysinfo.ini");
    QSettings syssettings(syspath, QSettings::IniFormat);
    QString talkListMaxNum_S = syssettings.value(QString("/%1/%2").arg("talkInfo").arg("talkListMaxNum")).toString();
    int talkListMaxNum = 1;
    if (talkListMaxNum_S.isEmpty())
    {
        talkListMaxNum = 1;
    }
    else
    {
        talkListMaxNum = talkListMaxNum_S.toInt() + 1;
    }
    syssettings.setValue(QString("/%1/%2").arg("talkInfo").arg("talkListMaxNum"), talkListMaxNum);

    const QString&& path = QApplication::applicationDirPath() + "/" + QString("infoconf.ini");
    QSettings settings(path, QSettings::IniFormat);
    //
    //settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    //
    QString msginfo = settings.value(QString("/%1/%2").arg(user.idinfo).arg("info")).toString();
    QString ctime = settings.value(QString("/%1/%2").arg(user.idinfo).arg("time")).toString();
    settings.remove(user.idinfo);

    si.time_stamp = ctime.toInt();
    QListWidgetItem* pChild = new QListWidgetItem();
    pChild->setSizeHint(QSize(80, 80));
    pChild->setData(Qt::UserRole, user.idinfo);
    pChild->setData(Qt::UserRole + 1, QVariant::fromValue(user));
    WinContactItem* pContactItem = new WinContactItem(user.idinfo, ui->listWidgetMsg);
    if (user.idinfo.contains("0"))
    {
        pContactItem->setHeadPixmap(QPixmap(head));
    }
    else
    {
        pContactItem->setHeadPixmap(QPixmap(head));
    }
    if (username.isEmpty()) {
        pContactItem->setUserName(user.idinfo);
    }
    else {
        pContactItem->setUserName(username);
    }
   
    pContactItem->setSignName(msginfo);
    pContactItem->isTimeShow(true);
    pContactItem->setSendTime(ctime);
    pContactItem->setObjectName("winContactItem" + user.idinfo);
    ui->listWidgetMsg->insertItem((talkListMaxNum * (-1)), pChild);
    ui->listWidgetMsg->setItemWidget(pChild, pContactItem);
    ui->listWidgetMsg->setCurrentRow(0);



    //
     pDm->insertSession(si);


    //添加到消息队列    
    settings.setValue(QString("/%1/%2").arg(user.idinfo).arg("name"), username);
    settings.setValue(QString("/%1/%2").arg(user.idinfo).arg("dw"), user.dw);
    settings.setValue(QString("/%1/%2").arg(user.idinfo).arg("bm"), user.bm);
    settings.setValue(QString("/%1/%2").arg(user.idinfo).arg("info"), "");
    settings.setValue(QString("/%1/%2").arg(user.idinfo).arg("rownum"), talkListMaxNum);


    //更新状态
    onLineStatusUp();
}

void WinTalkList::delListWidget(QString idInfo) {
    //delete
    for (int i = 0; i < ui->listWidgetMsg->count(); i++)
    {
        QListWidgetItem* listItem = ui->listWidgetMsg->item(i);
        QString itemIdInfo = listItem->data(Qt::UserRole).toString();
        if (itemIdInfo == idInfo)
        {
            ui->listWidgetMsg->removeItemWidget(listItem);
            delete listItem;
            break;
        }
    }
}

//
void WinTalkList::selListWidget(WinObjUser user)
{
    QY_MESSENGER_ID idinfo;
    unsigned  int  uiObjType = 0;

    TCHAR grpName_from[128] = _T("");
    TCHAR srcName_from[128] = _T("");
    QString username;

    idinfo.ui64Id = user.idinfo.toInt();
    //delete
    for (int i = 0; i < ui->listWidgetMsg->count(); i++)
    {
        QListWidgetItem* listItem = ui->listWidgetMsg->item(i);
        QString itemIdInfo = listItem->data(Qt::UserRole).toString();
        if (itemIdInfo == user.idinfo)
        {
            //
            this->on_listWidgetMsg_itemClicked(listItem);
            listItem->setSelected(true);
            //
            break;
        }
    }

 }
