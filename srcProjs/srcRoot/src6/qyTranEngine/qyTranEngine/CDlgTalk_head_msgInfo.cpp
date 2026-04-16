#include "CDlgTalk_head_msgInfo.h"
#include <QImage>

#include    "qyMcMainCommon_qt.h"
#include    "ctxQmc.h"
#include <WinObjUser.h>
#include <CMainFrame.h>
#include <ctxQmc_qt.h>

//
#define SHADOW_WIDTH 15 // ÒõÓ°±ß¿ò¿í¶È;
#define d_WIDTH 280
//
CDlgTalk_head_msgInfo::CDlgTalk_head_msgInfo(QString userId, QWidget* parent)
    : WinBasic(true, parent)
{
    ui.setupUi(this);
    QY_MESSENGER_ID infoId;
    infoId.ui64Id = userId.toInt();
    TCHAR idinfoto_name[125];
    TCHAR dw[125];
    TCHAR bm[125];
    //ui.btn_msg->setVisible(false);
    QImage Image;
    Image.load(":/Resources/Images/WinMain/headMax.png");
    QPixmap pixmap = QPixmap::fromImage(Image);
    getTalkerDesc(infoId, null, null, null, null, dw, mycountof(dw), bm, mycountof(bm), idinfoto_name, mycountof(idinfoto_name));
    p_userid = userId;
    ui.lab_head->setPixmap(pixmap);
    
    ui.lab_MessagerId->setText(userId);
    QString idinfoName = QString::fromStdWString(std::wstring(idinfoto_name));
    if (idinfoName.isEmpty()) {
        idinfoName = "(" + userId + ")";
    }
    ui.lab_name->setText(idinfoName);
    ui.dw->setText(QString::fromStdWString(std::wstring(dw)) + " " + QString::fromStdWString(std::wstring(bm)));

    //
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    //
    ui.label_staticMessengerId->setText("Messenger ID:");
    //ui.label_staticLogonTo->setText(u8"µÇÂ¼µ½:");
    //ui.label_server->setText(pMisCnt->server.ip);


    //
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(this->windowFlags() | Qt::SubWindow);
    installEventFilter(this);
}

CDlgTalk_head_msgInfo::~CDlgTalk_head_msgInfo()
{
    int  ii = 0;
}

void CDlgTalk_head_msgInfo::showDialog(QString userId,  QWidget* parent)
{
    CDlgTalk_head_msgInfo* dlg = new CDlgTalk_head_msgInfo(userId,  parent);
    QPoint pt = QCursor::pos();
    QRect rc = QApplication::desktop()->screenGeometry();
    int d_x = rc.width() - d_WIDTH;
    if (pt.x() > d_x) {
        dlg->move(pt.x() - d_WIDTH , pt.y());
    }
    else {
        dlg->move(pt);
    }
    dlg->show();
    dlg->activateWindow();
    
}

void CDlgTalk_head_msgInfo::isVisibleMsgBtn() {
    //thsui.msgDo->setVisible(false);
}


void CDlgTalk_head_msgInfo::on_msgDo_clicked() 
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    HWND  hMainWnd = pQyMc->gui.hMainWnd;
    CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);


    WinObjUser user;
    user.idinfo = p_userid;
    pMainWnd->cut_talk_list(user);
}


bool CDlgTalk_head_msgInfo::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == this && QEvent::WindowDeactivate == event->type())
    {
        this->close();
        return true;
    }
    return false;
}

void CDlgTalk_head_msgInfo::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH), QBrush(Qt::white));

    QColor color(0, 0, 0, 70);
    for (int i = 0; i < SHADOW_WIDTH; i++)
    {
        color.setAlpha(120 - qSqrt(i) * 30);
        painter.setPen(color);
        // ·½½ÇÒõÓ°±ß¿ò;
        painter.drawRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2);
        // Ô²½ÇÒõÓ°±ß¿ò;
        //painter.drawRoundedRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2, 4, 4);
    }
}
