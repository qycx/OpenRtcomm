
#include    "stdafx.h"

#define  __noDbg_new__

#include "SearchMsgRecord.h"
#include "MsgRecordItem.h"
#include <qlistwidget.h>
#include <QDebug>
#include <MsgRecordSon.h>
#include <QtCore/qmath.h>
#include <QPainter>
//
//#include <qdesktopwidget.h>
#include    <qscreen.h>
//
#include <MessageData.h>
#include <SearchListModel.h>
#include    "qyMcMainCommon_qt.h"

#include "ctxQmc_qt.h"
#include <DBManager.h>
#include <CMainFrame.h>

#define SHADOW_WIDTH 1 // 阴影边框宽度;
namespace {
    SearchMsgRecord* dlg = nullptr;
}
SearchMsgRecord::SearchMsgRecord( QWidget *parent )
	: WinBasic(parent)
    , ui(new Ui::SearchMsgRecord)

{
	ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::Dialog);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->listWidget->setFrameShape(QListWidget::NoFrame);
    connect(ui->listWidget, &QListWidget::clicked, this, &SearchMsgRecord::slot_list_item_clicked);
   // connect(ui->btnTalker, &QListWidget::clicked, this, &SearchMsgRecord::on_btnTalker_clicked);




#if 0
    for (int i = 0; i <= msgs.size() - 1; i++) {
        QListWidgetItem* pChild = new QListWidgetItem();
        pChild->setSizeHint(QSize(100, 102));
        MsgRecordItem* msgItem = new MsgRecordItem();
        msgItem->setName(msgs[i].fromUserName);
        msgItem->setMsg(msgs[i].content);
        msgItem->setTime(QString::number(msgs[i].messageTime));
     //   msgItem->setUserid(msgs[i].userId);
        msgItem->setObjectName(msgs[i].messageId + "_" + msgs[i].userId);
       
        ui->listWidget->insertItem(i, pChild);
        ui->listWidget->setItemWidget(pChild, msgItem);
    }
#endif


}
void SearchMsgRecord::slot_list_item_clicked(QModelIndex idx) {
    //qDebug() << idx;
    auto item = ui->listWidget->item(idx.row());
    MsgRecordItem* msgItem = (MsgRecordItem*)ui->listWidget->itemWidget(item);
    QString msg_id = msgItem->objectName();



    QStringList strList = msg_id.split("_", Qt::SkipEmptyParts);
   

    QPoint pt = this->pos();
    pt.setX(pt.x()+this->width());

    
    MsgRecordSon::getDialog();

    MsgRecordSon::setContent(strList[1],strList[0]);
    MsgRecordSon::showWnd(pt);


 }

//点击进入聊天
void SearchMsgRecord::on_btnTalker_clicked()
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    HWND  hMainWnd = pQyMc->gui.hMainWnd;
    CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);
    
    
    WinObjUser user;
    user.idinfo = _idInfo;
    pMainWnd->cut_talk_list(user);
  

}

void SearchMsgRecord::getDialog()
{
    if (!dlg)
    {
        dlg = new SearchMsgRecord();

    }
}
void SearchMsgRecord::showWnd(QPoint pt)
{
    if (!dlg)  return;
    dlg->show();
    dlg->activateWindow();
    if (!pt.isNull())
    {
        dlg->move(pt);
    }
}

void SearchMsgRecord::setContent(QString idInfo, QString keyword)
{
  
    dlg->removeProessAll();
    QY_MC* pQyMc = QY_GET_GBUF();
    CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();
    DBManager* pDm = (DBManager*)pProcInfo->m_var.pDBManager;
    QList<MessageData> msgs_list = pDm->searchMessage(idInfo , keyword);
    QY_MESSENGER_ID idInfo_s;
    unsigned  int  uiObjType = 0;
    TCHAR grpName_peer[125];
    TCHAR srcName_peer[125];
    idInfo_s.ui64Id = idInfo.toInt();

    getTalkerDesc(idInfo_s, &uiObjType, grpName_peer, mycountof(grpName_peer), mynull, mynull, 0, mynull, 0, srcName_peer, mycountof(srcName_peer));
    if (uiObjType == CONST_objType_imGrp) {
        dlg->ui->labCount->setText("   " + QString::fromStdWString( grpName_peer) + QString::number(msgs_list.size()) + u8"条相关记录");
    }
    else if (uiObjType == CONST_objType_messenger) {
        dlg->ui->labCount->setText("   " + QString::fromStdWString(srcName_peer) + QString::number(msgs_list.size()) + u8"条相关记录");
    }

    
 
    dlg->_idInfo = idInfo;
    for (int i = 0; i <= msgs_list.size() - 1; i++) {
        QListWidgetItem* pChild = new QListWidgetItem();
        pChild->setSizeHint(QSize(60, 80));
        MsgRecordItem* msgItem = new MsgRecordItem();
        msgItem->setName(msgs_list[i].fromUserName + " " + QDateTime::fromSecsSinceEpoch(msgs_list[i].messageTime).toString("yyyy/MM/dd hh:mm:ss"));
        msgItem->setMsg(msgs_list[i].content);
        msgItem->setCursor();
        //   msgItem->setUserid(msgs[i].userId);
        msgItem->setObjectName(msgs_list[i].messageId + "_" + msgs_list[i].userId);

        dlg->ui->listWidget->insertItem(i, pChild);
        dlg->ui->listWidget->setItemWidget(pChild, msgItem);
    }
}

void SearchMsgRecord::removeProessAll() {

    while (ui->listWidget->count() > 0)
    {
        QListWidgetItem* item = ui->listWidget->takeItem(0);
        delete item;
    }
}

SearchMsgRecord::~SearchMsgRecord()
{
    dlg = nullptr;
    MsgRecordSon::closeDialog();
}

void SearchMsgRecord::closeDialog() {
    if (dlg) {
        dlg->close();
    }
}

void SearchMsgRecord::paintEvent(QPaintEvent* event)
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
        //painter.drawRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2);
        // 圆角阴影边框;
        painter.drawRoundedRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2, 4, 4);
    }
}

void SearchMsgRecord::showEvent(QShowEvent* event)
{
    QRect rc = QApplication::primaryScreen()->geometry();
    //
    if (this->pos().x() + this->width() > rc.width())
    {
        this->move(rc.width() - this->width(), this->pos().y());
    }
}
