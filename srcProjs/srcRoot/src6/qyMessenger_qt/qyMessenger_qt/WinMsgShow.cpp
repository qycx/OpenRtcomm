
#include    "stdafx.h"
#include "WinMsgShow.h" 
#include <QFile>
#include <QCoreApplication>
#include "MessageSignalCenter.h"
#include <QDebug>;
#include    "qyMcMainCommon_qt.h"
#include "CDlgTalk_qt.h"
#include "MessageData.h"
#include "DBManager.h"
#include <ShlObj_core.h>
#include <QtCore/qprocess.h>
#include    "ctxQmc_qt.h"
#include "CDlgTalk_head_msgInfo.h"
#include "QClipboard.h"
#include <QRegularExpression.h>  



bool WinQWebEnginePage::acceptNavigationRequest(const QUrl& url, QWebEnginePage::NavigationType type, bool isMainFrame)
{
    // Only allow qrc:/*.html.
    if (url.scheme() == QString("qrc"))
        return true;
    QDesktopServices::openUrl(url);
    return false;
}

MsgHtmlObj::MsgHtmlObj(QObject* parent) : QObject(parent)
{
    //m_hTalk = hTalk;
    //
    QFile file0(":/Resources/MsgHtml/msgleftTmpl.html");
    file0.open(QFile::ReadOnly);
    if (file0.isOpen())
    {
        m_msgLHtmlTmpl = QLatin1String(file0.readAll());
    }
    file0.close();
    QFile file1(":/Resources/MsgHtml/msgrightTmpl.html");
    file1.open(QFile::ReadOnly);
    if (file1.isOpen())
    {
        m_msgRHtmlTmpl = QLatin1String(file1.readAll());
    }
    file1.close();
    QFile file2(":/Resources/MsgHtml/msgrightFile.html");
    file2.open(QFile::ReadOnly);
    if (file2.isOpen())
    {
        m_msgRHtmlFile = QLatin1String(file2.readAll());
    }
    file2.close();
    QFile file3(":/Resources/MsgHtml/msgLeftFile.html");
    file3.open(QFile::ReadOnly);
    if (file3.isOpen())
    {
        m_msgLHtmlFile = QLatin1String(file3.readAll());
    }
    file3.close();
}

void MsgHtmlObj::fileRecv(QString msgid)
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();
    DBManager* pDm = (DBManager*)pProcInfo->m_var.pDBManager;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

    //点击接受按钮操作
    CDlgTalk_qt* cdlgTalkqt = mynull;
    cdlgTalkqt = (CDlgTalk_qt*)QWidget::find((WId)m_hTalk);
    DLG_TALK_var* pm_var = cdlgTalkqt->get_pm_var();

    QList<MessageData> iTaskIdFind;

    QList<MessageData> messFind = pDm->getMessagesMidFind(QString::number(pm_var->addr.idInfo.ui64Id), msgid);
    int  iTaskId = 0;
    if (messFind.size() > 0) {
        iTaskId = messFind[0].iTaskId.toInt();
    }
    if (!iTaskId)goto  errLabel;
    iTaskIdFind = pDm->getMessagesFind(QString::number(pm_var->addr.idInfo.ui64Id), iTaskId);
    if (iTaskIdFind.size() == 0)goto  errLabel;
    TCHAR tBuf[128];
    safeTcsnCpy((TCHAR*)iTaskIdFind[0].messageId.utf16(), tBuf, mycountof(tBuf));
    TCHAR* pT;
    pT = _tcschr(tBuf, _T('-'));
    if (!pT)  goto  errLabel;
    *pT = 0;
    QY_MESSENGER_ID  idInfo_from;
    idInfo_from.ui64Id = _ttol(tBuf);
    pT++;
    TCHAR* pT1;
    pT1 = _tcschr(pT, _T('-'));
    if (!pT1)goto  errLabel;
    *pT1 = 0;
    __int64 tStartTime;
    tStartTime = _tcstoui64(pT, mynull, 10);
    pT1++;
    unsigned  int  uiTranNo;
    uiTranNo = _ttol(pT1);

    //
    {
        CQyMalloc mallocObj;
        int  size = sizeof(MIS_MSG_TASK);
        MIS_MSG_TASK* pMsgTask = (MIS_MSG_TASK*)mallocObj.mallocf(size);
        memset(pMsgTask, 0, size);
        pMsgTask->uiType = CONST_misMsgType_task;
        pMsgTask->data.route.idInfo_from = idInfo_from;
        pMsgTask->data.route.idInfo_to.ui64Id = pMisCnt->idInfo.ui64Id;
        pMsgTask->addr_logicalPeer.idInfo.ui64Id = pm_var->addr.idInfo.ui64Id;
        pMsgTask->ucFlg = CONST_commFlg_routeTalkData;
        IM_CONTENTU* pContent = M_getMsgContent(pMsgTask->ucFlg, &pMsgTask->data);
        pContent->uiType = CONST_imCommType_transferFileReq;

        lstrcpyn(pContent->transferFileReq.fileName, (wchar_t*)(iTaskIdFind[0].fileName).utf16(), mycountof(pContent->transferFileReq.fileName));
        pContent->transferFileReq.ui64FileLen = iTaskIdFind[0].fileSize;
        pContent->transferFileReq.uiSizePerSnd_suggest = iTaskIdFind[0].sizePerSnd_suggest;
        //
        pMsgTask->iTaskId = iTaskId;
        if (!pMsgTask->iTaskId)goto  errLabel;
        //
        pMsgTask->tStartTime = tStartTime;
        pMsgTask->uiTranNo = uiTranNo;
        //
        pMsgTask->lenInBytes = offsetof(MIS_MSG_routeTalkData, buf) + sizeof(pContent->transferFileReq);

        //
        pMsgTask->idInfo_taskSender = idInfo_from;
        //
        pMsgTask->pMisCnt = pMisCnt;

        //
        if (isTalkerShadowMgr(pm_var->addr))  goto  errLabel;
        TALKER_shadow* pShadow = (TALKER_shadow*)pm_var->pShadowInfo;
        if (!pShadow)goto  errLabel;
        HWND  hMgr = pShadow->hMgr;
        CDlgTalk_qt* pMgr = (CDlgTalk_qt*)CDlgTalk_qt::find((WId)hMgr);
        if (!pMgr)goto  errLabel;
        DLG_TALK_var* pMgrVar = pMgr->get_pm_var();
        if (!pMgrVar)goto  errLabel;
        //
        dlgTalk_qPostMsg(hMgr, pMsgTask, sizeof(MIS_MSG_TASK));
        //
    }
    //
    PARAM_dlgTalk_procTask  param;
    memset(&param, 0, sizeof(param));
    dlgTalk_procTask1(m_hTalk, iTaskId, CONST_imOp_recv_accept, mynull, &param);

errLabel:
    return;
}
//通过JavaScript 右键消息体点击事件拿到每条消息的msgid
void MsgHtmlObj::clickReceive(QString msgid, QString msg) {
    if (!msgid.isEmpty()) {
#if 10
        QMenu tmpMenu;// = new QMenu;
        QAction act1;
        act1.setText(QString::fromUtf16((char16_t*)_T("复制")));
        tmpMenu.addAction(&act1);
        QAction* pAction = tmpMenu.exec(QCursor::pos());
        if (pAction) {
            if (pAction->text() == u8"复制") {
                //
                CDlgTalk_qt* cdlgTalkqt = mynull;
                cdlgTalkqt = (CDlgTalk_qt*)QWidget::find((WId)m_hTalk);
                QString copy_str = cdlgTalkqt->ui->widgetMsgShow->selectedText();

                QClipboard* clipboard = QApplication::clipboard();
                if (!copy_str.isEmpty()) {
                    clipboard->setText(copy_str);
                }
                else {
                    clipboard->setText(msg);
                }
                
                
            }
            else {
                int  kk = 0;
                printf("%d", kk);
            }
        }
#endif


        qDebug() << msgid << "--------------";
    }
}

//通过JavaScript 右键头像事件拿到用户id
void MsgHtmlObj::clickHeader(int userid,int chatType) {

    if (userid != 0) {
          QY_MESSENGER_ID infoId;
            infoId.ui64Id = userid;
            TCHAR idinfoto_name[125];
        if (chatType == 1) {
            QMenu tmpMenu;// = new QMenu;
            QAction act1;

            CDlgTalk_qt* cdlgTalkqt = mynull;
            cdlgTalkqt = (CDlgTalk_qt*)QWidget::find((WId)m_hTalk);
            getTalkerDesc(infoId, mynull, mynull, mynull, mynull, mynull, mynull, mynull, mynull, idinfoto_name, mycountof(idinfoto_name));
            QString idinfoName = QString::fromStdWString(std::wstring(idinfoto_name));
            if (idinfoName.isEmpty()) {
                idinfoName = "(" + QString::number(userid) + ")";
            }

            act1.setText("@" + idinfoName);
            tmpMenu.addAction(&act1);
            QAction* pAction = tmpMenu.exec(QCursor::pos());
            if (pAction) {
                if (pAction->text() == "@" + idinfoName) {
                   //
                    cdlgTalkqt->ui->sendMsg->insertPlainText("@" + idinfoName);
                
                }
                else {
                    int  kk = 0;
                    printf("%d", kk);
                }
            }
        }
        qDebug() << userid << "--------------" << chatType;
    }
}


//通过JavaScript 左键点击头像事件拿到用户id
void MsgHtmlObj::clickLeftHeader(int userid) {
    if ( userid != 0 ) {

        CDlgTalk_head_msgInfo::showDialog(QString::number(userid));
     //   CDlgTalk_head_msgInfo::isVisibleMsgBtn();
    }
}

void MsgHtmlObj::fileCancel(QString msgid)
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();
    DBManager* pDm = (DBManager*)pProcInfo->m_var.pDBManager;

    //点击取消按钮操作
    CDlgTalk_qt* cdlgTalkqt = mynull;
    cdlgTalkqt = (CDlgTalk_qt*)QWidget::find((WId)m_hTalk);
    DLG_TALK_var* pm_var = cdlgTalkqt->get_pm_var();
    //  if (!cdlgTalkqt) return  -1;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));


    QList<MessageData> messFind = pDm->getMessagesMidFind(QString::number(pm_var->addr.idInfo.ui64Id), msgid);
    QString iTaskId = messFind[0].iTaskId;
    PARAM_dlgTalk_procTask  param;
    memset(&param, 0, sizeof(param));


    if (messFind[0].fromUserId == QString::number(pMisCnt->idInfo.ui64Id)) {
        dlgTalk_procTask1(m_hTalk, iTaskId.toInt(), CONST_imOp_send_cancel, mynull, &param);
    }
    else {
        dlgTalk_procTask1(m_hTalk, iTaskId.toInt(), CONST_imOp_recv_cancel, mynull, &param);
    }


    //接收者取消 传输结束 改状态
    pDm->updateMessage(QString::number(pm_var->addr.idInfo.ui64Id), iTaskId.toInt(), 1, 0);

}

//打开默认本地文件夹
void MsgHtmlObj::openFile(QString fileName, QString msgid, QString userid) {
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    //if (!pProcInfo)  goto  errLabel;
    TCHAR* pDir = pProcInfo->cfg.policy.dirToSaveFile;

    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_qt* pProcInfo1 = (CCtxQmc_qt*)pQyMc->get_pProcInfo();
    DBManager* pDm = (DBManager*)pProcInfo1->m_var.pDBManager;
    QString pathStr;
    if (fileName.isEmpty()) {
        QList<MessageData> fileFind = pDm->getMessagesMidFind(userid, msgid);
        pathStr = QString::fromStdWString(std::wstring(pDir)) + fileFind[0].content.remove(QRegularExpression("^ +\\s*"));;
    }
    else {
        pathStr = QString::fromStdWString(std::wstring(pDir)) + fileName.remove(QRegularExpression("^ +\\s*"));;
    }


    // QString pathStr = u8"C:\\Users\\28610\\Documents\\中企资料.zip";
    QProcess proc(this);

    proc.start("explorer /select, " + pathStr.replace("/", "\\"));
    proc.waitForFinished();
}
//显示更多消息
void MsgHtmlObj::showMore(int page)
{
    //TODO:显示更多消息
    CDlgTalk_qt* cdlgTalkqt = mynull;
    cdlgTalkqt = (CDlgTalk_qt*)QWidget::find((WId)m_hTalk);
    DLG_TALK_var* pm_var = cdlgTalkqt->get_pm_var();

    cdlgTalkqt->more_loadFinished(page, COUNT_chat_more_count);
}

WinMsgShow::WinMsgShow(QWidget* parent) :QWebEngineView(parent)
, m_bshowbox(false)
{
    installEventFilter(parent);
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "7777");
    QNetworkProxyFactory::setUseSystemConfiguration(false);
    winpage = new WinQWebEnginePage(this);
    setPage(winpage);
    channel = new QWebChannel(this);
    m_msgHtmlObj = new MsgHtmlObj(this);
    channel->registerObject("external", m_msgHtmlObj);
    this->page()->setWebChannel(channel);
    this->load(QUrl("qrc:/Resources/MsgHtml/msgTmpl.html"));
    this->setAcceptDrops(true);


#if  0
    m_pContextMenu = new QMenu;
    this->pageAction(QWebEnginePage::Copy)->setText(QStringLiteral("复制"));
    //this->pageAction(QWebEnginePage::Paste)->setText(QStringLiteral("粘贴"));
    m_pContextMenu->addAction(this->pageAction(QWebEnginePage::Copy));
    //m_pContextMenu->addAction(this->pageAction(QWebEnginePage::Paste));
#endif

    //
    setContextMenuPolicy(Qt::DefaultContextMenu);
}

void WinMsgShow::contextMenuEvent(QContextMenuEvent* event)
{
    QString str = this->selectedText();
    if (str.size() == 0) {
        return;
    }

    //m_pContextMenu->exec(QCursor::pos());

#if 10
    QMenu tmpMenu;// = new QMenu;
    this->pageAction(QWebEnginePage::Copy)->setText(QStringLiteral("复制"));
    //this->pageAction(QWebEnginePage::Paste)->setText(QStringLiteral("粘贴"));

    tmpMenu.addAction(this->pageAction(QWebEnginePage::Copy));

    //QAction act1;
    //act1.setText(QString::fromUtf16((char16_t*)_T("hh")));
   // tmpMenu.addAction(&act1);

//
   // QAction* pAction = tmpMenu.exec(QCursor::pos());

    //if (pAction) {
     //   if (pAction->text() == "hh") {
     //       int  kk = 0;
     //       printf("%d", kk);
    //    }
    //    else {
   //         int  kk = 0;
   //         printf("%d", kk);
  //      }
        //pAction->
   // }
 //   int  ii = 0;
 //   printf("%d", ii);
#endif

}


//
int replaceEmoji(TCHAR* html, int w, int h, TCHAR* output, int  cntof_output)
{
    int  iErr = -1;

    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();

    //
    TCHAR* prefix = (TCHAR*)_T("&#x1f");
    int len_prefix = lstrlen(prefix);
    TCHAR* pT;
    TCHAR* pT1;
    TCHAR  tBuf1[256];
    TCHAR* pO = output;
    int len_oLeft = cntof_output;


    //
    if (cntof_output == 0)  return  -1;

    //
    for (pT = html; *pT; ) {
        if (!_tcsnicmp(prefix, pT, len_prefix))
        {
            pT1 = _tcschr(pT, _T(';'));
            if (pT1) {
                safeTcsnCpy(pT + len_prefix, tBuf1, pT1 - pT - len_prefix + 1);
                //
                QString tt = QString::fromUtf16((char16_t*)pProcInfo->m_var.installDir_qt) + "/resource/emoji/" + "1f" + QString::fromUtf16((char16_t*)tBuf1) + ".png";
                if (bFileExists((TCHAR*)tt.utf16())) {
                    int  ii = 0;
                    _sntprintf(tBuf1, mycountof(tBuf1), _T("<img src=\"%s\" width=%d height=%d>"), tt.utf16(), w, h);
                    int  len = lstrlen(tBuf1);
                    if (len_oLeft < len + 1)  goto  errLabel;
                    memcpy(pO, tBuf1, len * sizeof(TCHAR));
                    pO += len;  len_oLeft -= len;
                    pT = pT1 + 1;
                    continue;
                }
                //
                int  ii = 0;
            }
        }
        //
        if (len_oLeft < 2)  break;
        *pO = *pT;
        pO++;  len_oLeft--;
        pT++;

        continue;
    }

    iErr = 0;
errLabel:

    //
    if (len_oLeft)  *pO = 0;
    else  output[cntof_output - 1] = 0;

    //
    return  0;
}



//发送消息
void WinMsgShow::sendMsg(const QString& html1, const QString& username, const QString& msgid, const int& msgtype, const int& fileStatus, const int& chatType, const int& isMore, const int& filesize, const int& userid)
{
    QJsonObject msgObj;
    QString qsMsg;

    //
    //QString str = QString::fromUtf16((const char16_t *)_T("kkk"));
    QString html = html1;
    //
    TCHAR  tBuf[2048];
    //
#if  0
    html = QString::fromUtf16((const char16_t*)_T("kk<img src=./emoji/1f466.png>mm"));
    html = "kk<img src=\"" + qApp->applicationDirPath() + "/emoji/1f466.png\">mm";
    html = "kk<img src=emoji/1f466.png>mm";
    QString html2 = QString::fromUtf16((char16_t*)_T("命名&#x1f644;版本"));
    //
    //
    replaceEmoji((TCHAR*)html2.utf16(), tBuf, mycountof(tBuf));

#endif
    int  w = 25;
    int  h = 25;
    replaceEmoji((TCHAR*)html.utf16(), w, h, tBuf, mycountof(tBuf));
    //
    html = QString::fromUtf16((char16_t*)tBuf);


    //
    const QList<QStringList> msgLst = parseHtml(html);
    for (int index = 0; index < msgLst.size(); index++)
    {
        if (msgLst.at(index).at(0) == "img")
        {
            QString imagePath = msgLst.at(index).at(1);
            QPixmap pixmap;
            if (imagePath.left(3) == "qrc")
            {
                pixmap.load(imagePath.mid(3));
            }
            else
            {
                pixmap.load(imagePath);
            }
            int width = this->width() * 0.65;
            if (pixmap.width() > width)
            {
                pixmap = pixmap.scaled(QSize(width, pixmap.height()), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            }
            QString imgPath = QString("<img src=\"%1\" width=\"%2\" height=\"%3\"/>").arg(imagePath).arg(pixmap.width()).arg(pixmap.height());
            qsMsg += imgPath;
        }
        else if (msgLst.at(index).at(0) == "text")
        {
            qsMsg += msgLst.at(index).at(1);
        }
    }
    msgObj.insert("MSG", html);
    msgObj.insert("USERNAME", username);
    msgObj.insert("FILENAME", html);
    msgObj.insert("HTMLID", msgid);
    msgObj.insert("MSGTYPE", msgtype);
    msgObj.insert("CANCEL", u8"取 消");
    msgObj.insert("RECE", u8"接 收");
    msgObj.insert("FILESTATUS", fileStatus);
    msgObj.insert("TYPE", chatType);
    msgObj.insert("ISMORE", isMore);
    msgObj.insert("FILESIZE", filesize);
    msgObj.insert("USERID", userid);
    const QString&& Msg = QJsonDocument(msgObj).toJson(QJsonDocument::Compact);
    this->page()->runJavaScript(QString("appendHtml(%1)").arg(Msg));
}

//接收消息
void WinMsgShow::receiveMsg(const QString& html1, const QString& username, const QString& msgid, const int& msgtype, const int& fileStatus, const int& chatType, const int& isMore, const int& filesize , const int& userid)
{
    QJsonObject msgObj;
    QString qsMsg;
    QString html = html1;
    //
    TCHAR  tBuf[2048];
    int  w = 25;
    int  h = 25;
    replaceEmoji((TCHAR*)html.utf16(), w, h, tBuf, mycountof(tBuf));
    //
    html = QString::fromUtf16((char16_t*)tBuf);


    const QList<QStringList> msgLst = parseHtml(html);
    for (int index = 0; index < msgLst.size(); index++)
    {
        if (msgLst.at(index).at(0) == "img")
        {
            QString imagePath = msgLst.at(index).at(1);
            QPixmap pixmap;
            if (imagePath.left(3) == "qrc")
            {
                pixmap.load(imagePath.mid(3));
            }
            else
            {
                pixmap.load(imagePath);
            }
            int width = this->width() * 0.65;
            if (pixmap.width() > width)
            {
                pixmap = pixmap.scaled(QSize(width, pixmap.height()), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            }
            QString imgPath = QString("<img src=\"%1\" width=\"%2\" height=\"%3\"/>").arg(imagePath).arg(pixmap.width()).arg(pixmap.height());
            qsMsg += imgPath;
        }
        else if (msgLst.at(index).at(0) == "text")
        {
            qsMsg += msgLst.at(index).at(1);
        }
    }
    //msgObj.insert("MSG", qsMsg
    msgObj.insert("MSG", html);
    msgObj.insert("USERNAME", username);
    msgObj.insert("FILENAME", html);
    msgObj.insert("HTMLID", msgid);
    msgObj.insert("MSGTYPE", msgtype);
    msgObj.insert("CANCEL", u8"取 消");
    msgObj.insert("RECE", u8"接 收");
    msgObj.insert("FILESTATUS", fileStatus);
    msgObj.insert("TYPE", chatType);
    msgObj.insert("ISMORE", isMore);
    msgObj.insert("FILESIZE", filesize);
    msgObj.insert("USERID", userid);
    const QString&& Msg = QJsonDocument(msgObj).toJson(QJsonDocument::Compact);
    this->page()->runJavaScript(QString("recvHtml(%1)").arg(Msg));
}

void WinMsgShow::setFileProgress(const QString& msgid, QString progress, int iStatus, QString userid, int isObjType)
{
    m_msgHtmlObj->FileMessageProgress(msgid, progress, iStatus, userid, isObjType);
}

//
void WinMsgShow::MoreEnd() {
    this->page()->runJavaScript(QString("MoreEnd()"));
}

void WinMsgShow::dragEnterEvent(QDragEnterEvent* event) //拖动文件到窗口，触发
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction(); //事件数据中存在路径，方向事件
    }
    else
    {
        event->ignore();
    }
}

void WinMsgShow::dragMoveEvent(QDragMoveEvent* event) //拖动文件到窗口移动文件，触发
{

}

void WinMsgShow::dropEvent(QDropEvent* event) //拖动文件到窗口释放文件，触发
{
    const QMimeData* mimeData = event->mimeData();
    if (mimeData->hasUrls())
    {
        QList<QUrl> urls = mimeData->urls();
        QString fileName = urls.at(0).toLocalFile();
        //
        emit signal_file_drag(fileName);
    }
}


QList<QStringList> WinMsgShow::parseHtml(const QString& html)
{
    QDomDocument doc;
    doc.setContent(html);
    QDomElement root = doc.documentElement();

    const QDomNode&& node = root.firstChildElement("body");
    return parseDocNode(node);
}

QList<QStringList> WinMsgShow::parseDocNode(const QDomNode& node)
{
    QList<QStringList> attribute;
    const QDomNodeList&& list = node.childNodes();
    for (int i = 0; i < list.count(); i++)
    {
        const QDomNode&& node = list.at(i);
        if (node.isElement())
        {
            const QDomElement&& element = node.toElement();
            if (element.tagName() == "img")
            {
                QStringList attributeLst;
                attributeLst << "img" << element.attribute("src");
                attribute << attributeLst;
            }
            if (element.tagName() == "span")
            {
                QStringList attributeLst;
                attributeLst << "text" << element.text();
                attribute << attributeLst;
            }
            if (node.hasChildNodes())
            {
                attribute << parseDocNode(node);
            }
        }
    }
    return attribute;
}

WinMsgShow::~WinMsgShow()
{
    if (winpage) {
        delete winpage;
        winpage = nullptr;
    }
    if (m_msgHtmlObj) {
        delete m_msgHtmlObj;
        m_msgHtmlObj = nullptr;
    }
    if (channel) {
        delete channel;
        channel = nullptr;
    }
#if  0
    if (m_pContextMenu) {
        delete m_pContextMenu;
        m_pContextMenu = nullptr;
    }
#endif

}

