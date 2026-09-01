#include "WinContactItem.h"
#include "ui_WinContactItem.h"
#include <qfiledialog.h>


WinContactItem::WinContactItem(QString id, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::WinContactItem)
{
    id_ = id;
    ui->setupUi(this);
    isTimeShow(false);
    initControl();
    updateMsgCount();

    isOnLine(false);
}

WinContactItem::~WinContactItem()
{
    delete ui;
}

void WinContactItem::AddNewMsgCount(int count)
{
    msgCount += count;
    updateMsgCount();
}

void WinContactItem::Clear()
{
    msgCount = 0;
    updateMsgCount();
}

//获取当前小红点数量
int WinContactItem::GetMsgCount() 
{
    return msgCount;
}
//在线状态
void WinContactItem::isOnLine(bool isShow) 
{
    ui->lab_online->setVisible(isShow);
}

void WinContactItem::isTimeShow(bool isShow) 
{
    ui->sendTime->setVisible(isShow);
}

void WinContactItem::initControl()
{
    setAttribute(Qt::WA_DeleteOnClose);
    //CommonUtils::loadStyleSheet(this,"WinContactItem");
}

void WinContactItem::updateMsgCount()
{
    ui->lab_count->setText(msgCount > 99 ? "99" : QString::number(msgCount));
    ui->lab_count->setVisible(msgCount != 0);
}


void WinContactItem::closeEvent(QCloseEvent* ev)
{
    return;
}



void WinContactItem::setUserName(const QString& userName)
{
#if  0
    int maxCnt = 10;
    QString qstr;
    if (userName.size() > maxCnt ) {
        qstr  =  userName.mid(0,maxCnt);
    }
#endif
    
    //
    ui->userName->setText(userName);
}


void WinContactItem::setSignName(const QString& signName)
{
    ui->signName->setText(signName);
}

void WinContactItem::setSendTime(const QString& sendTime)
{
    ui->sendTime->setText(sendTime);
}

void WinContactItem::setHeadPixmap(const QPixmap& headPath)
{
    ui->headName->setPixmap(headPath);
}




QSize WinContactItem::getHeadLabelSize() const
{
    return ui->headName->size();
}
