#include <QDialog>
#include "ui_CDlgTalk_head_msgInfo.h"
#include "WinBasic.h"

class CDlgTalk_head_msgInfo : public WinBasic
{
    Q_OBJECT
public:
    static void showDialog(QString userId,  QWidget* parent = Q_NULLPTR);
    static void isVisibleMsgBtn();
private:
    CDlgTalk_head_msgInfo(QString userId,  QWidget* parent = Q_NULLPTR);
    ~CDlgTalk_head_msgInfo();
    

public slots:
    void on_msgDo_clicked();

private:
    virtual bool eventFilter(QObject* watched, QEvent* event);
    virtual bool canResize() { return false; }
    void paintEvent(QPaintEvent* event);
private:
    Ui::CDlgTalk_head_msgInfoClass ui;
    QString p_userid;
};