#ifndef DEFINE_MODULES_H_
#define DEFINE_MODULES_H_
#include <QString>
//群成员
struct MemberInfo
{
    QString userId;
    QString name;
    QString dw;
    QString bm = "";
    QString status = "";
    QString do_spokes = "";
    bool  online = false;
};

//
// 发言人列表

struct SpeakInfo
{
    QString userInfo;
    qint64 userId;
    QString type;
    QString index;
};
//
struct FriendInfo
{
    QString userId;
    QString name;
    QString dw;
};

//
struct  myFriendInfo
{
    qint64  userId;
    //
    QString grpName;
    //
    QString dw;
    QString bm;
    QString syr;
};






#endif // !DEFINE_MODULES_H_

