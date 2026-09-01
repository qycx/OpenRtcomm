#pragma once

#include <QObject>
#include <qstring.h>
#include <windows.h>
#include <QVariant>;
#include <qnmCommProc_is_open.h>
//#include "../qnmCommProc_mis.h"
/// <summary>
/// 消息信号中心
/// </summary>
/// 

typedef struct 
{
    QY_MESSENGER_ID     from_id;
    QY_MESSENGER_ID     peer_id;
    TCHAR             msg[100];
    
    int                uiTranNo;
    int                 iTaskId;
    time_t             send_time;
    
}SendData;

class MessageSignalCenter : public QObject
{
    Q_OBJECT

public:
    static MessageSignalCenter& Instance()
    {
        static MessageSignalCenter msc;
        return msc;
    }
signals:
   // void signal_recv_new_message(MIS_MSG_TALK* talk);
    void signal_recv_new_message(SendData sd);
private:

    MessageSignalCenter(QObject* parent = nullptr);
    ~MessageSignalCenter();
};
