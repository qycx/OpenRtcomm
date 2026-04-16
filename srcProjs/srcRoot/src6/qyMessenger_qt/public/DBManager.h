#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include "../msg/MessageData.h"

class DBManager : public QObject
{
    Q_OBJECT

public:
    //
#if  0
    static DBManager& Instance()
    {
        static DBManager db;
        return db;
    }
#endif
    //
    void initDB(QString userId);
    void exitDB();

    //
    bool insertMessage(const MessageData& msg);
    
    QList<MessageData> getMessages(QString userId, int pageIndex, int pageSize = 20);
    QList<MessageData> getMessagesFind(QString userId, int iTaskId);
    QList<MessageData> getMessagesMidFind(QString userId, QString MessageId);
   QMap<QString, QList<MessageData>> searchMessage(QString str);
   QList<MessageData> searchMessage(QString userId, QString str);
   void setAllUserActiveProcess(int value);


   void getMessage(QString userId, QString messageId, QList<MessageData>& upList, QList<MessageData>& downList);

    bool updateMessage(QString userId, int iTaskId, int cancel, int is_rece);
    bool updateiTalkStatus();
    //插入会话
    bool insertSession(const SessionInfo session);
    //插入会话集合
    void  insertSession(QList<SessionInfo> sessions);
    //获取会话列表
    QList<SessionInfo> getSessions();
    //获取单个会话
    SessionInfo getSession(QString sid);
    //更新会话名
    bool updateSessionName(QString sid, QString name);
    //修改未读消息数
    bool updateSessionUnReadCount(QString sid, int count);
    //删除会话
    bool deleteSession(QString sid);
    //清空会话
    bool clearnSessions();
private:
    //加载消息表
    void loadMessageTables();
    //创建消息表
    bool createMessageTable(QString name);
    //创建会话表
    bool createSessionTable();
    QList<SessionInfo> query_sessions(QString sql);
private:
public:
    DBManager(QObject *parent=nullptr);
    ~DBManager();
private:
    QSqlDatabase _db;
};
