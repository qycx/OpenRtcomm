#include "DBManager.h"
#include <QDir>
#include <QStandardPaths>
#include <QSqlQuery>
#include <QVariant>
#include <qmutex.h>
//#include    <Windows.h>
#include    <tchar.h>
#include    "qyMcMainCommon_qt.h"

//
#define MESSAGE_TAB_   "msg_tab_"
#define SESSION_TAB_   "session_tab"

namespace {
    QList<QString> message_tables;
    QMutex mutex_;
}

DBManager::DBManager(QObject* parent)
    : QObject(parent)
{
}

DBManager::~DBManager()
{
    exitDB();
}


QString GetLocalDBPath()
{
    QString strDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);;
    QDir dir(strDir);
    if (!dir.exists(strDir))
    {
        dir.mkpath(strDir);
    }
    strDir.append("/db/");
    QDir dirDB(strDir);
    if (!dirDB.exists())
    {
        dirDB.mkpath(strDir);
    }
    return strDir;
}

void DBManager::initDB(QString userId)
{
    QString connectionName = "im_data";
    //
    uint curThreadId = GetCurrentThreadId();
    connectionName = "im_data" + QString::number(curThreadId);
    //
    _db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    QString db_file = GetLocalDBPath() + QString("im_%1_data.db").arg(userId);
    _db.setDatabaseName(db_file);
    if (_db.open())
    {
        //消息表
        loadMessageTables();
        //会话表
        createSessionTable();
    }
    return;
}

void DBManager::exitDB()
{
    if (_db.isOpen()) {
        _db.close();
    }
    return;
}

void DBManager::loadMessageTables()
{
    QString sql = "SELECT name FROM sqlite_master WHERE type = 'table' ORDER BY name; ";
    QSqlQuery sql_query(_db);
    sql_query.prepare(sql);
    if (sql_query.exec())
    {
        while (sql_query.next())
        {
            QString tableName = sql_query.value("name").toString();
            if (tableName.startsWith(MESSAGE_TAB_))
            {
                message_tables.append(tableName);
            }
        }
    }
}



#pragma region 会话表


bool DBManager::createSessionTable()
{
    QString sql = QString("create table if not exists %1 (session_id VARCHAR(50) PRIMARY KEY \
        ,session_name VARCHAR(50) \
        ,header_url VARCHAR(500) \
        ,chat_type INTEGER \
        ,content TEXT \
         ,msg_type INT DEFAULT(0) \
        ,unread_count INTEGER DEFAULT(0) \
        ,time_stamp DEFAULT(0)\
        ,grp_creator VARCHAR(200) \
    )").arg(SESSION_TAB_);
    QSqlQuery sql_query(_db);
    sql_query.prepare(sql);
    sql_query.exec();
    return true;
}

bool DBManager::insertSession(const SessionInfo session)
{
    QMutexLocker locker(&mutex_);
    QString sql = QString("replace  into %1 values (:session_id,:session_name,:header_url,:chat_type,:content,:msg_type,:unread_count,:time_stamp,:grp_creator)").arg(SESSION_TAB_);
    QSqlQuery sql_query(_db);
    sql_query.prepare(sql);
    QString qstr;
    qstr = QString::number(session.session_id);
    sql_query.bindValue(":session_id", qstr);
    qstr = QString::fromUtf16((char16_t*)session.session_name);
    sql_query.bindValue(":session_name", qstr);
    qstr = QString::fromUtf16((char16_t*)session.header_url);
    sql_query.bindValue(":header_url", qstr);

    sql_query.bindValue(":chat_type", session.chat_type);

    qstr = QString::fromUtf16((char16_t*)session.content);
    sql_query.bindValue(":content", qstr);

    qstr = QString::number(session.grp_creator);
    sql_query.bindValue(":grp_creator", qstr);


    sql_query.bindValue(":msg_type", session.msg_type);
    sql_query.bindValue(":unread_count", session.unread_count);
    sql_query.bindValue(":time_stamp", session.time_stamp);

    bool res = sql_query.exec();
    if (!res)
    {
        qDebug() << sql_query.lastError();
    }
    return res;
}


void DBManager::insertSession(QList<SessionInfo> sessions)
{
    if (sessions.size() == 0)
    {
        return;
    }
    _db.transaction();
    for (int i = 0; i < sessions.size(); i++)
    {
        auto session = sessions.at(i);
        QString sid = QString::number(session.session_id);
        SessionInfo sinfo = getSession(sid);
        if (!sinfo.session_id)
        {
            session.unread_count += sinfo.unread_count;
        }
        bool b = insertSession(session);
    }
    _db.commit();
}

QList<SessionInfo> DBManager::getSessions()
{
    QString sql = QString("select * from %1 order by time_stamp desc").arg(SESSION_TAB_);
    return query_sessions(sql);
}

SessionInfo DBManager::getSession(QString sid)
{
    SessionInfo sessionInfo;
    QString sql = QString("select * from %1 where session_id='%2'").arg(SESSION_TAB_).arg(sid);
    QList<SessionInfo> sessions = query_sessions(sql);
    if (sessions.size() > 0)
    {
        sessionInfo = sessions[0];
    }
    return sessionInfo;
}


bool DBManager::updateSessionName(QString sid, QString name)
{
    QString sql = QString("update %1 set session_name='%2' where session_id='%3'").arg(SESSION_TAB_).arg(name).arg(sid);
    QSqlQuery sql_query(_db);
    sql_query.prepare(sql);
    return sql_query.exec();
}

bool DBManager::updateSessionUnReadCount(QString sid, int count)
{
    QString sql = QString("update %1 set unread_count=%2 where session_id='%3'").arg(SESSION_TAB_).arg(count).arg(sid);
    QSqlQuery sql_query(_db);
    sql_query.prepare(sql);
    return sql_query.exec();
}

bool DBManager::deleteSession(QString sid)
{
    QString sql = QString("delete from %1 where session_id='%2'").arg(SESSION_TAB_).arg(sid);
    QSqlQuery sql_query(_db);
    sql_query.prepare(sql);
    return sql_query.exec();
}

bool DBManager::clearnSessions()
{
    QString sql = QString("delete from %1").arg(SESSION_TAB_);
    QSqlQuery sql_query(_db);
    sql_query.prepare(sql);
    return sql_query.exec();
}

QList<SessionInfo> DBManager::query_sessions(QString sql)
{
    QList<SessionInfo> sessions;
    QSqlQuery sql_query(_db);
    sql_query.prepare(sql);
    if (sql_query.exec())
    {
        while (sql_query.next())
        {
            SessionInfo session;
            memset(&session, 0, sizeof(session));
            session.session_id = sql_query.value("session_id").toInt();


            lstrcpyn(session.session_name, (wchar_t*)(sql_query.value("session_name").toString()).utf16(), mycountof(session.session_name));
            lstrcpyn(session.header_url, (wchar_t*)(sql_query.value("header_url").toString()).utf16(), mycountof(session.header_url));
            lstrcpyn(session.content, (wchar_t*)(sql_query.value("content").toString()).utf16(), mycountof(session.content));

            session.time_stamp = sql_query.value("time_stamp").toULongLong();
            session.chat_type = (ChatType)sql_query.value("chat_type").toInt();
            session.unread_count = sql_query.value("unread_count").toInt();
            session.msg_type = (MessageTypes)sql_query.value("msg_type").toInt();

            session.grp_creator = sql_query.value("grp_creator").toInt();

            //
            sessions.append(session);
        }
    }
    return sessions;
}

#pragma endregion

#pragma region 消息表
MessageData queryMessage(QSqlQuery& sql_query)
{
    MessageData msg;
    msg.messageId = sql_query.value("messageId").toString();
    msg.type = (MessageTypes)sql_query.value("type").toInt();
    msg.content = sql_query.value("content").toString();
    msg.messageTime = sql_query.value("messageTime").toULongLong();
    msg.fromUserId = sql_query.value("fromUserId").toString();
    msg.fromUserName = sql_query.value("fromUserName").toString();
    msg.headerUrl = sql_query.value("headerUrl").toString();
    msg.toUserId = sql_query.value("toUserId").toString();
    msg.toUserName = sql_query.value("toUserName").toString();
    msg.chatType = (ChatType)sql_query.value("chatType").toInt();
    msg.isRead = sql_query.value("isRead").toInt();
    msg.isSend = sql_query.value("isSend").toInt();
    msg.fileName = sql_query.value("fileName").toString();
    msg.userId = sql_query.value("userId").toString();
    msg.iTaskId = sql_query.value("iTaskId").toString();
    msg.is_activeProcess = sql_query.value("is_activeProcess").toInt();
    msg.cancel = sql_query.value("cancel").toInt();
    msg.is_rece = sql_query.value("is_rece").toInt();
    msg.isUpload = sql_query.value("isUpload").toInt();
    msg.isDownload = sql_query.value("isDownload").toInt();
    msg.fileSize = sql_query.value("fileSize").toULongLong();
    msg.filePath = sql_query.value("filePath").toString();
    msg.isRealDel = sql_query.value("isRealDel").toInt();
    msg.deleteTime = sql_query.value("deleteTime").toULongLong();
    msg.other = sql_query.value("other").toString();
    msg.seqNo = sql_query.value("seqNo").toULongLong();
    msg.sizePerSnd_suggest = sql_query.value("sizePerSnd_suggest").toInt();
    return msg;
}

bool DBManager::createMessageTable(QString tableName)
{
    QString sql = QString("create table if not exists %1 (messageId VARCHAR(50) PRIMARY KEY \
        ,type INTEGER \
,messageTime BIGINT DEFAULT(0) \
,userId VARCHAR(150) \
,fromUserId VARCHAR(150) \
,fromUserName VARCHAR(500) \
,headerUrl VARCHAR(500) \
,toUserId VARCHAR(150) \
,toUserName VARCHAR(500) \
,iTaskId VARCHAR(50)\
,is_activeProcess INTEGER DEFAULT(0) \
        ,chatType INTEGER DEFAULT(0) \
        ,isRead INTEGER DEFAULT(0) \
        ,isSend INTEGER DEFAULT(0) \
        ,content TEXT \
        ,fileName TEXT \
        ,cancel INTEGER DEFAULT(0)\
        ,is_rece INTEGER DEFAULT(0)\
        ,isUpload INTEGER DEFAULT(0) \
        ,isDownload INTEGER DEFAULT(0) \
        ,fileSize BIGINT DEFAULT(0) \
  ,filePath TEXT \
  ,isRealDel INTEGER DEFAULT(0) \
        ,deleteTime BIGINT DEFAULT(0),other TEXT,seqNo BIGINT DEFAULT(0),sizePerSnd_suggest INTEGER DEFAULT(0))").arg(tableName);
    QSqlQuery sql_query(_db);
    sql_query.prepare(sql);
    return sql_query.exec();
}

QMap<QString, QList<MessageData>> DBManager::searchMessage(QString str)
{
    QMap<QString, QList<MessageData>> map;
    for (size_t i = 0; i < message_tables.size(); i++)
    {
        QString tableName = message_tables[i];
        QString sql = QString("select * from %1 where content like '%%2%' order by messageTime desc").arg(tableName).arg(str);
        QString userId = tableName.replace(MESSAGE_TAB_, "");
        QList<MessageData> msgs;
        QSqlQuery sql_query(_db);
        sql_query.prepare(sql);
        if (sql_query.exec())
        {
            while (sql_query.next())
            {
                msgs.append(queryMessage(sql_query));
            }
        }
        if (msgs.size() > 0)
        {
            map[userId] = msgs;
        }
    }
    return map;
}

void DBManager::setAllUserActiveProcess(int value)
{
    _db.transaction();
    for (size_t i = 0; i < message_tables.size(); i++)
    {
        QString tableName = message_tables[i];
        QString sql = QString("update %1 set is_activeProcess=%2").arg(tableName).arg(value);
        QSqlQuery sql_query(_db);
        sql_query.prepare(sql);
        sql_query.exec();
    }
    _db.commit();
}

QList<MessageData> DBManager::searchMessage(QString userId, QString str)
{
    QList<MessageData> msgs;
    QString tableName = MESSAGE_TAB_ + userId;
    if (!message_tables.contains(tableName))
    {
        return msgs;
    }
    QString sql = QString("select * from %1 where content like '%%2%' order by messageTime desc").arg(tableName).arg(str);
    QSqlQuery sql_query(_db);
    sql_query.prepare(sql);
    if (sql_query.exec())
    {
        while (sql_query.next())
        {
            msgs.append(queryMessage(sql_query));
        }
    }
    return msgs;
}


bool DBManager::insertMessage(const MessageData& msg)
{
    QMutexLocker locker(&mutex_);
    QString userId = msg.userId;
    QString tableName = MESSAGE_TAB_ + userId;
    if (!message_tables.contains(tableName))
    {
        if (createMessageTable(tableName))
        {
            message_tables.append(tableName);
        }
    }
    QString sql = QString("replace  into %1 values (:messageId,:type,:messageTime,:userId,:fromUserId,:fromUserName,:headerUrl,:toUserId,:toUserName,:iTaskId,:is_activeProcess \
,:chatType,:isRead,:isSend,:content,:fileName,:cancel,:is_rece,:isUpload,:isDownload,:fileSize,:filePath \
,:isRealDel,:deleteTime,:other,:seqNo,:sizePerSnd_suggest)").arg(tableName);
    QSqlQuery sql_query(_db);
    sql_query.prepare(sql);
    sql_query.bindValue(":messageId", msg.messageId);
    sql_query.bindValue(":type", msg.type);
    sql_query.bindValue(":messageTime", msg.messageTime);
    sql_query.bindValue(":userId", msg.userId);
    sql_query.bindValue(":fromUserId", msg.fromUserId);
    sql_query.bindValue(":fromUserName", msg.fromUserName);
    sql_query.bindValue(":headerUrl", msg.headerUrl);
    sql_query.bindValue(":toUserId", msg.toUserId);
    sql_query.bindValue(":toUserName", msg.toUserName);
    sql_query.bindValue(":chatType", msg.chatType);
    sql_query.bindValue(":isRead", msg.isRead);
    sql_query.bindValue(":isSend", msg.isSend);
    sql_query.bindValue(":content", msg.content);
    sql_query.bindValue(":fileName", msg.fileName);
    sql_query.bindValue(":iTaskId", msg.iTaskId);
    sql_query.bindValue(":is_activeProcess", msg.is_activeProcess);
    sql_query.bindValue(":isUpload", msg.isUpload);
    sql_query.bindValue(":cancel", msg.cancel);
    sql_query.bindValue(":is_rece", msg.is_rece);
    sql_query.bindValue(":isDownload", msg.isDownload);
    sql_query.bindValue(":fileSize", msg.fileSize);
    sql_query.bindValue(":filePath", msg.filePath);
    sql_query.bindValue(":isRealDel", msg.isRealDel);
    sql_query.bindValue(":deleteTime", msg.deleteTime);
    sql_query.bindValue(":other", msg.other);
    sql_query.bindValue(":seqNo", msg.seqNo);
    sql_query.bindValue(":sizePerSnd_suggest", msg.sizePerSnd_suggest);
    bool res = sql_query.exec();
    if (!res)
    {
        qDebug() << sql_query.lastError();
    }
    return res;
    return true;
}

void DBManager::getMessage(QString userId, QString messageId, QList<MessageData>& upList, QList<MessageData>& downList)
{
    auto ls = getMessagesMidFind(userId, messageId);
    if (ls.size() > 0)
    {
        qint64 msgTime = ls[0].messageTime;
        QString tableName = MESSAGE_TAB_ + userId;
        QList<MessageData> msgs;
        if (!message_tables.contains(tableName))
        {
            return;
        }
        {
            QString sql = QString("select * from ( select * from %1 where messageTime<%2 order by messageTime desc LIMIT 20) order by messageTime asc").arg(tableName).arg(msgTime);
            QSqlQuery sql_query(_db);
            sql_query.prepare(sql);
            if (sql_query.exec())
            {
                while (sql_query.next())
                {
                    upList.append(queryMessage(sql_query));
                }
            }
        }
        {
            QString sql = QString("select * from %1 where messageTime>%2 order by messageTime asc LIMIT 20").arg(tableName).arg(msgTime);
            QSqlQuery sql_query(_db);
            sql_query.prepare(sql);
            if (sql_query.exec())
            {
                while (sql_query.next())
                {
                    downList.append(queryMessage(sql_query));
                }
            }
        }
    }
}


QList<MessageData> DBManager::getMessages(QString userId, int pageIndex, int pageSize)
{
    QString tableName = MESSAGE_TAB_ + userId;
    QList<MessageData> msgs;
    if (!message_tables.contains(tableName))
    {
        return msgs;
    }
    QString sql = QString("select * from %1 where deleteTime<=0 order by messageTime desc limit %2, %3").arg(tableName).arg(pageIndex * pageSize).arg(pageSize);

    QSqlQuery sql_query(_db);
    sql_query.prepare(sql);
    if (sql_query.exec())
    {
        while (sql_query.next())
        {
            msgs.append(queryMessage(sql_query));
        }
    }
    return msgs;
}

//通过iTaskId 查询单条
QList<MessageData> DBManager::getMessagesFind(QString userId, int iTaskId)
{
    QString tableName = MESSAGE_TAB_ + userId;
    QList<MessageData> msgs;
    if (!message_tables.contains(tableName))
    {
        return msgs;
    }
    QString sql = QString("select * from %1 where deleteTime<=0 and is_activeProcess=1 and iTaskId=%2 limit 1").arg(tableName).arg(iTaskId);

    QSqlQuery sql_query(_db);
    sql_query.prepare(sql);
    if (sql_query.exec())
    {
        while (sql_query.next())
        {
            MessageData msg;
            msg.messageId = sql_query.value("messageId").toString();
            msg.type = (MessageTypes)sql_query.value("type").toInt();
            msg.content = sql_query.value("content").toString();
            msg.messageTime = sql_query.value("messageTime").toULongLong();
            msg.fromUserId = sql_query.value("fromUserId").toString();
            msg.fromUserName = sql_query.value("fromUserName").toString();
            msg.headerUrl = sql_query.value("headerUrl").toString();
            msg.toUserId = sql_query.value("toUserId").toString();
            msg.toUserName = sql_query.value("toUserName").toString();
            msg.chatType = (ChatType)sql_query.value("chatType").toInt();
            msg.isRead = sql_query.value("isRead").toInt();
            msg.isSend = sql_query.value("isSend").toInt();
            msg.fileName = sql_query.value("fileName").toString();
            msg.iTaskId = sql_query.value("iTaskId").toString();
            msg.is_activeProcess = sql_query.value("is_activeProcess").toInt();
            msg.cancel = sql_query.value("cancel").toInt();
            msg.is_rece = sql_query.value("is_rece").toInt();
            msg.isUpload = sql_query.value("isUpload").toInt();
            msg.isDownload = sql_query.value("isDownload").toInt();
            msg.fileSize = sql_query.value("fileSize").toULongLong();
            msg.filePath = sql_query.value("filePath").toString();
            msg.isRealDel = sql_query.value("isRealDel").toInt();
            msg.deleteTime = sql_query.value("deleteTime").toULongLong();
            msg.other = sql_query.value("other").toString();
            msg.seqNo = sql_query.value("seqNo").toULongLong();
            msg.sizePerSnd_suggest = sql_query.value("sizePerSnd_suggest").toInt();
            msgs.append(msg);
        }
    }
    return msgs;
}

//通过MessageId 查询单条
QList<MessageData> DBManager::getMessagesMidFind(QString userId, QString MessageId)
{
    QString tableName = MESSAGE_TAB_ + userId;
    QList<MessageData> msgs;
    if (!message_tables.contains(tableName))
    {
        return msgs;
    }
    QString sql = QString("select * from %1 where deleteTime<=0  and messageId='%2' limit 1").arg(tableName).arg(MessageId);

    QSqlQuery sql_query(_db);
    sql_query.prepare(sql);
    if (sql_query.exec())
    {
        while (sql_query.next())
        {
            MessageData msg;
            msg.messageId = sql_query.value("messageId").toString();
            msg.type = (MessageTypes)sql_query.value("type").toInt();
            msg.content = sql_query.value("content").toString();
            msg.messageTime = sql_query.value("messageTime").toULongLong();
            msg.fromUserId = sql_query.value("fromUserId").toString();
            msg.fromUserName = sql_query.value("fromUserName").toString();
            msg.headerUrl = sql_query.value("headerUrl").toString();
            msg.toUserId = sql_query.value("toUserId").toString();
            msg.toUserName = sql_query.value("toUserName").toString();
            msg.chatType = (ChatType)sql_query.value("chatType").toInt();
            msg.isRead = sql_query.value("isRead").toInt();
            msg.isSend = sql_query.value("isSend").toInt();
            msg.fileName = sql_query.value("fileName").toString();
            msg.iTaskId = sql_query.value("iTaskId").toString();
            msg.is_activeProcess = sql_query.value("is_activeProcess").toInt();
            msg.cancel = sql_query.value("cancel").toInt();
            msg.is_rece = sql_query.value("is_rece").toInt();
            msg.isUpload = sql_query.value("isUpload").toInt();
            msg.isDownload = sql_query.value("isDownload").toInt();
            msg.fileSize = sql_query.value("fileSize").toULongLong();
            msg.filePath = sql_query.value("filePath").toString();
            msg.isRealDel = sql_query.value("isRealDel").toInt();
            msg.deleteTime = sql_query.value("deleteTime").toULongLong();
            msg.other = sql_query.value("other").toString();
            msg.seqNo = sql_query.value("seqNo").toULongLong();
            msg.sizePerSnd_suggest = sql_query.value("sizePerSnd_suggest").toInt();
            msgs.append(msg);
        }
    }
    return msgs;
}

bool DBManager::updateMessage(QString userId, int iTaskId, int cancel, int is_rece) {
    QString tableName = MESSAGE_TAB_ + userId;

    QString sql = QString("update %1 set cancel=%2,is_rece=%3 where iTaskId=%4 and is_activeProcess=1").arg(tableName).arg(cancel).arg(is_rece).arg(iTaskId);
    QSqlQuery sql_query(_db);
    sql_query.prepare(sql);
    bool res = sql_query.exec();
    if (!res)
    {
        qDebug() << sql_query.lastError();
    }
    return res;
}
#pragma endregion
//退出程序 将iTalkid的数据库状态清空
bool DBManager::updateiTalkStatus() {
    return true;
}