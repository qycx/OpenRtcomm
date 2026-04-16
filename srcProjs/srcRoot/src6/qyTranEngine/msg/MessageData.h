#pragma once

#include <QObject>
#include <QString>
#include <quuid.h>
#include <QDateTime>

enum MessageTypes
{
    TextMessage,
    FileMessage,
    MeetingMessage
};

enum ChatType
{
    OneChat,
    GroupChat
};

struct MessageData
{
    MessageData()
    {
        messageId = QUuid::createUuid().toString(QUuid::StringFormat::WithoutBraces);
    }
    /// <summary>
    /// 消息编号
    /// </summary>
    QString messageId;
    /// <summary>
    /// 消息类型
    /// </summary>
    MessageTypes type;
    /// <summary>
    /// 消息时间
    /// </summary>
    qint64 messageTime;
    /// <summary>
    /// userId 不通场景意义不同， 私聊 收消息 为 发送人 id，发消息 为 接收人id，群聊 为群id
    /// </summary>
    QString userId;
    /// <summary>
    /// 发送人id
    /// </summary>
    QString fromUserId;
    /// <summary>
    /// 发送人姓名
    /// </summary>
    QString fromUserName;
    /// <summary>
/// 发送人头像
/// </summary>
    QString headerUrl;
    /// <summary>
/// 接收人id
/// </summary>
    QString toUserId;
    /// <summary>
/// 接收人姓名
/// </summary>
    QString toUserName;
    /// <summary>
/// 聊天类型
/// </summary>
    ChatType chatType;
    /// <summary>
    /// 已读
    /// </summary>
    int isRead;
    /// <summary>
  /// 已发送
  /// </summary>
    int isSend;
    /// <summary>
    /// 内容
    /// </summary>
    QString content;
    /// <summary>
    /// 是否真删除
    /// </summary>
    int isRealDel;
    /// <summary>
    /// 删除时间
    /// </summary>
    qint64 deleteTime;
    /// <summary>
    /// 其他
    /// </summary>
    QString other;
    /// <summary>
    ///消息号 暂时用不上
    /// </summary>
    qint64 seqNo;
    /// <summary>
/// 已上传
/// </summary>
    int isUpload;
    int is_rece;
    int cancel;
    /// <summary>
 /// 已下载
 /// </summary>
    int isDownload;
    /// <summary>
    /// 文件名
    /// </summary>
    QString fileName;
    /// <summary>
 /// 传文件的id号
 /// </summary>
    QString iTaskId;
    /// <summary>
    /// iTaskid 控制变量  true 生效  false失效
    bool is_activeProcess;
    /// 文件大小
    /// </summary>
    qint64 fileSize;
    /// <summary>
    /// 下载后的路径
    /// </summary>
    QString filePath;

    //每次包传输的大小
   int sizePerSnd_suggest;
};

#if 0
struct SessionInfo
{
    //消息类型 群组或个人
    ChatType    chat_type = ChatType::OneChat;
    //ID号
    QString		session_id = QString();
    //对方名称
    QString	    session_name = QString();
    QString     header_url = QString();
    MessageTypes msg_type = MessageTypes::TextMessage;
    //最后一调消息内容
    QString		content = QString();
    int			unread_count = 0;//未读消息数量
    //最后一条时间戳 
    quint64		time_stamp = 0;
};
#endif

struct SessionInfo
{
    //消息类型 群组或个人
    ChatType    chat_type = ChatType::OneChat;
    //ID号
    unsigned  __int64     session_id;
    //对方名称
    wchar_t     session_name[100];
    wchar_t     header_url[256];
    MessageTypes msg_type = MessageTypes::TextMessage;
    //最后一调消息内容
    wchar_t		content[100];
    int			unread_count = 0;//未读消息数量
    //最后一条时间戳 
    quint64		time_stamp = 0;  
    //组创建人
    int grp_creator = 0;
};






