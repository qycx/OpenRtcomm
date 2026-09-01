#ifndef WINMSGBOX_H
#define WINMSGBOX_H

#include <QWidget>
#include "WinBasic.h"
#include "ui_WinMsgBox.h"
#include "WinTitle.h"


enum ChosseResult
{
    ID_OK = 0,                      // 确定;
    ID_CANCEL                       // 取消;
};

enum MessageType
{
    MESSAGE_INFORMATION = 0,        // 提示信息;
    MESSAGE_WARNNING,               // 提示警告;
    MESSAGE_QUESTION,               // 提示询问;
};

enum MessageButtonType
{
    BUTTON_OK = 0,                  // 只有确定按钮;
    BUTTON_OK_AND_CANCEL,           // 确定、取消按钮;
    BUTTON_CLOSE                    // 关闭按钮;
};


QT_BEGIN_NAMESPACE
namespace Ui { class WinMsgBox; }
QT_END_NAMESPACE

class WinMsgBox : public QWidget
{
    Q_OBJECT

public:
    explicit WinMsgBox(QWidget *parent = nullptr);
    ~WinMsgBox();
    void setWindowTitle(QString title, int titleFontSize = 10);
    void setContentText(QString contentText);
    void setMessageType(MessageType messageType);
    void setButtonType(MessageButtonType buttonType);
    void setMessageContent(QString messageContent);

public:
    int static showWinMsgBox(QWidget* parent, const QString &title,const QString &contentText , MessageType messageType, MessageButtonType messageButtonType , bool isModelWindow = false);

private:
    Ui::WinMsgBox *ui;
    QEventLoop* m_eventLoop;
    ChosseResult m_chooseResult;
    WinTitle *winTitle = nullptr;


private:
    void initWindow();
    int exec();
    void closeEvent(QCloseEvent *event);
    void loadStyleSheet(const QString &sheetName);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent*);
    bool m_mousePressed;
    QPoint mousePoint;

private slots:
    void onOkClicked();
    void onCancelClicked(); 
    void onButtonMinClicked();
    void onButtonCloseClicked();
};

#endif // WINMSGBOX_H
