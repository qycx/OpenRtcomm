#include "UserInfoDialog.h"
#include <QImage>

#include    "qyMcMainCommon_qt.h"
#include    "ctxQmc.h"

//
UserInfoDialog::UserInfoDialog(QString userId, QString userName, QString dwInfo, QWidget* parent)
    : WinBasic(true, parent)
{
    ui.setupUi(this);
    //ui.btn_msg->setVisible(false);
    QImage Image;
    Image.load(":/Resources/Images/WinMain/headMax.png");
    QPixmap pixmap = QPixmap::fromImage(Image);
     ui.lab_head->setPixmap(pixmap);
     ui.lab_MessagerId->setText(userId);
     ui.lab_name->setText(userName);
     ui.dw->setText(dwInfo);

     //
     CCtxQyMc* pQyMc = g_pQyMc;
     CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
     MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
     //
     ui.label_staticMessengerId->setText("Messenger ID:");
     ui.label_staticLogonTo->setText(u8"µÇÂ¼µ½:");

     //
     QString qstr;
     qstr = pMisCnt->server.ip;
     qstr += "  "  +  QString::number(pQyMc->appParams.iSeqNoSelected_appObjPrefix);
     //
     ui.label_server->setText(qstr);


     //
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(this->windowFlags() | Qt::SubWindow);
    installEventFilter(this);
}

UserInfoDialog::~UserInfoDialog()
{
    int  ii = 0;
}

void UserInfoDialog::showDialog(QString userId, QString userName, QString dwInfo, QWidget* parent)
{
    UserInfoDialog* dlg = new UserInfoDialog(userId, userName, dwInfo, parent);
    QPoint pt = QCursor::pos();
   
    dlg->show();
    dlg->activateWindow();
    dlg->move(pt);
}


bool UserInfoDialog::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == this && QEvent::WindowDeactivate == event->type())
    {
        this->close();
        return true;
    }
    return false;
}
