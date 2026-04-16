#ifndef USER_INFO_WIDGET_H_
#define USER_INFO_WIDGET_H_

#include <QDialog>
#include "ui_UserInfoDialog.h"
#include "WinBasic.h"

class UserInfoDialog : public WinBasic
{
    Q_OBJECT
public:
    static void showDialog(QString userId, QString userName, QString dwInfo, QWidget* parent = Q_NULLPTR);
private:
    UserInfoDialog(QString userId,QString userName, QString dwInfo, QWidget* parent = Q_NULLPTR);
    ~UserInfoDialog();
private:
    virtual bool eventFilter(QObject* watched, QEvent* event);
    virtual bool canResize() { return false; }
private:
    Ui::UserInfoDialog ui;
};
#endif