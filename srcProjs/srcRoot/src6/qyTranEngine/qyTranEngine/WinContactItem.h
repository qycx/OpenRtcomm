#ifndef WINCONTACTITEM_H
#define WINCONTACTITEM_H

#include <QWidget>
#include "ui_WinContactItem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WinContactItem; }
QT_END_NAMESPACE

class WinContactItem : public QWidget
{
    Q_OBJECT

public:
    WinContactItem(QString id, QWidget* parent = 0);
    ~WinContactItem();
    /// <summary>
    /// 消息数累加
    /// </summary>
    /// <param name="count"></param>
    void AddNewMsgCount(int count);
    /// <summary>
    /// 清空消息提示
    /// </summary>
    void Clear();
    //获取当前小红点数量
    int GetMsgCount();

    QString ID() { return id_; }
public:
    void setUserName(const QString& userName);
    void setSendTime(const QString& sendTime);
    void setSignName(const QString& signName);
    void setHeadPixmap(const QPixmap& headPath);
    void isTimeShow(bool isShow);
    void isOnLine(bool isShow);
    QSize getHeadLabelSize() const;
    //
    void closeEvent(QCloseEvent* ev);

    //
private:
    void initControl();
    void updateMsgCount();
private:
    Ui::WinContactItem* ui;
    int msgCount = 0;
    QString id_;

public:
    unsigned  __int64     m_idInfo;
    int                m_uiTranNo;
    int                 m_iTaskId;
    time_t             m_send_time;
};

#endif // WINCONTACTITEM_H
