
#include    "stdafx.h"

#define  __noDbg_new__

#include "MsgRecordSon.h"
#include <qlistwidget.h>
#include <MsgRecordItem.h>
#include <QtCore/qmath.h>
#include <QPainter>
//
//#include <qdesktopwidget.h>
#include    <qscreen.h>
//
#include    "qyMcMainCommon_qt.h"

#include "ctxQmc_qt.h"
#include <DBManager.h>
#include <QtCore>
#include <QtGui>

#define SHADOW_WIDTH 1 // 阴影边框宽度;
namespace {
    MsgRecordSon* dlg = nullptr;
}

MsgRecordSon::MsgRecordSon(QWidget *parent)
	: WinBasic(parent)
{
	ui.setupUi(this);

    this->setWindowFlags(this->windowFlags() | Qt::Dialog);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui.listWidget->setFrameShape(QListWidget::NoFrame);
}

MsgRecordSon::~MsgRecordSon()
{
    dlg = nullptr;
}


void MsgRecordSon::getDialog() {
    if (!dlg) 
    {
        dlg = new MsgRecordSon();
    }
}

void MsgRecordSon::showWnd(QPoint pt) {
    if (!dlg) return;
    dlg->show();
    dlg->activateWindow();
    if (!pt.isNull())
    {
        dlg->move(pt);
    }
}   

void MsgRecordSon::setContent(QString userId , QString msgId) 
{
 
    dlg->removeProessAll();

    QY_MC* pQyMc = QY_GET_GBUF();
    CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();
    DBManager* pDm = (DBManager*)pProcInfo->m_var.pDBManager;
    QY_MESSENGER_ID idInfo_s;
    unsigned  int  uiObjType = 0;
    TCHAR grpName_peer[125];
    TCHAR srcName_peer[125];
    idInfo_s.ui64Id = userId.toInt();

    getTalkerDesc(idInfo_s, &uiObjType, grpName_peer, mycountof(grpName_peer), mynull, mynull, 0, mynull, 0, srcName_peer, mycountof(srcName_peer));
    if (uiObjType == CONST_objType_imGrp) {
        dlg->ui.labValue->setText("   " + QString::fromStdWString(grpName_peer) + u8"上下文详情");
    }
    else if (uiObjType == CONST_objType_messenger) {
        dlg->ui.labValue->setText("   " + QString::fromStdWString(srcName_peer) + u8"上下文详情");
    }


    QList<MessageData> m_downList;

    QList<MessageData> m_upList;

    pDm->getMessage(userId, msgId, m_upList, m_downList);
   // char		bufTime[256] = "";

    QList<MessageData> m_msg = pDm->getMessagesMidFind(userId, msgId);
    m_upList.append(m_msg);
    ///int list_size = m_upList.size();
    
    for (int i = 0; i <= m_downList.size() - 1; i++) {
        m_upList.append(m_downList[i]);
    }
    for (int i = 0; i <= m_upList.size() - 1; i++) {
       // displayShortTime(m_upList[i].messageTime, bufTime, mycountof(bufTime));
        //QString str(bufTime);

        QListWidgetItem* pChild = new QListWidgetItem();
        pChild->setSizeHint(QSize(50, 70));
        MsgRecordItem* msgItem = new MsgRecordItem();
        if (msgId == m_upList[i].messageId)
        {
            msgItem->set_on();
        }
        msgItem->setName(m_upList[i].fromUserName + " " + QDateTime::fromSecsSinceEpoch(m_upList[i].messageTime).toString("yyyy/MM/dd hh:mm:ss"));
        msgItem->setMsg(m_upList[i].content);
        msgItem->setObjectName(m_upList[i].messageId);
        
        dlg->ui.listWidget->insertItem(i, pChild);
        dlg->ui.listWidget->setItemWidget(pChild, msgItem);
        if (msgId == m_upList[i].messageId) 
        {
            dlg->ui.listWidget->scrollToItem(pChild);
        }
    }
   
}

void MsgRecordSon::removeProessAll() {

    while (ui.listWidget->count() > 0)
    {
        QListWidgetItem* item = ui.listWidget->takeItem(0);
        delete item;
    }
}


void MsgRecordSon::closeDialog() {
    if (dlg) {
        dlg->close();
    }
}
void MsgRecordSon::paintEvent(QPaintEvent* event)
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

void MsgRecordSon::showEvent(QShowEvent* event)
{
    QRect rc = QApplication::primaryScreen()->geometry();
    //
    if (this->pos().x() + this->width() > rc.width())
    {
        this->move(rc.width() - this->width(), this->pos().y());
    }
}