#ifndef ADD_GROUP_MEMBER_DIALOG_H_
#define ADD_GROUP_MEMBER_DIALOG_H_
#define		CONST_dcgType_null					0
#define		CONST_dcgType_createTmpGrp			1
#define		CONST_dcgType_sendFile				2
#define		CONST_dcgType_modifyTmpGrp			3

#include <QDialog>
#include "ui_AddGroupMemberDialog.h"
#include "WinBaseDialog.h"
#include <QPushButton>
#include <QLabel>
#include    "qyMcMainCommon_qt.h"
#include "defineModels.h"
#include <isCliHelpPublic.h>


class MemberItemWidget;
class SelectMemberItemWidget;

class AddGroupMemberDialog : public WinBaseDialog
{
    Q_OBJECT

public:
    AddGroupMemberDialog(QList<QString>& members, QWidget *parent = Q_NULLPTR);
    ~AddGroupMemberDialog();
    void updateSelectItems();
    QList<FriendInfo> getSelects();
    void setAllFriends(QList<FriendInfo> friends);
    QY_MESSENGER_ID friendIds;
    bool nativeEvent(const QByteArray& eventType, void* message, long* result);
    bool postMessageQt(MSG* message, long* result);
    QString groupName;

    LRESULT  OnQyComm(WPARAM  wParam, LPARAM  lParam);
    struct {
        //
        int					iType;

    //    //
       IM_GRP_EX* pImGrpEx_input;			//  

    //    //
       TMP_usrs  			tmpUsrs;

    //    //
        TMP_usrs			tmpGrp;

    //    //
       TCHAR				tSelUsrs[256];

    //    //
     QY_MESSENGER_ID		idInfo_tmpGrp;

    }						m_var;
    //typedef  struct  __qyMessengerId_t {								//  
    //    unsigned  __int64									ui64Id;
    //}		 QY_MESSENGER_ID;
private:
    virtual bool isMinimized() const { return false; }
    virtual bool isMaximized() const { return false; }
    void loadFriends(QString str=QString());
    bool isInSelected(QString userId);
    //邀请好友入群
    void clearListWidget(QListWidget* list);
    //bool subDevListSort(const FriendInfo &info1, const FriendInfo &info2);

    int fill_usrs();
    int add_mem(QY_MESSENGER_ID* pIdInfo);
    int free_usrs();

    bool isGrpMem(QY_MESSENGER_ID* pIdInfo);
private slots:
    void slot_text_changed(QString str);
    void slot_membertem_clicked();
    void slot_button();
private:
    Ui::AddGroupMemberDialog ui;
    QList<QString> list_select_ids;
    QList<QString> members_;
    QList<FriendInfo> friends_;
};

class MemberItemWidget :public QPushButton
{
    Q_OBJECT
        friend AddGroupMemberDialog;
public:
    MemberItemWidget(FriendInfo friendInfo, bool selected,  QWidget* parent = nullptr);
    ~MemberItemWidget();
    void setSelected(bool b);
    bool isSelected() { return isSelected_; }
private slots:
    void slot_download_finished(QString md5, QString path, QString custom);
signals:
    void signal_closed();
private:
    QLabel* lab_img_ = nullptr;
    QString md5_avator_;
    QLabel* lab_sel_ = nullptr;
    bool isSelected_ = false;
    FriendInfo friendInfo_;

};

class SelectMemberItemWidget :public QWidget
{
    Q_OBJECT
        friend AddGroupMemberDialog;
public:
    SelectMemberItemWidget(FriendInfo friendInfo,  QWidget* parent = nullptr);
    ~SelectMemberItemWidget();
private slots:
    void slot_download_finished(QString md5, QString path, QString custom);
    void slot_button();
private:
    QLabel* lab_img_ = nullptr;
    QString md5_avator_;
    FriendInfo friendInfo_;
};
#endif