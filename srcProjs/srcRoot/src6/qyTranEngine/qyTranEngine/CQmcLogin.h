#ifndef CQMCLOGIN_H
#define CQMCLOGIN_H 

#include <QWidget>
#include <QFile>
#include <QMouseEvent>
#include "WinBasic.h"
#include <QIcon>
#include <QStyle>
#include "WinSerConfig.h"
#include <QSettings>
#include <QtDebug>
#include <QListView>
#include <QDialog>
#include "WinTitle.h"
#include <QKeyEvent>

 
#include <mutex>

//
#include	"stdafx.h"
#include	"qyMcMainCommon_qt.h"
#include "DlgMcClientLogon.h" 



//
QT_BEGIN_NAMESPACE
namespace Ui { class CQmcLogin; }
QT_END_NAMESPACE


#if 0
typedef  struct  __tmp_cnt_display_t {
    int	index;
    TCHAR displayName[64];
}  TMP_cnt_display;

typedef  struct  __tmp_cnt_displays_t {
    TMP_cnt_display	mems[CONST_maxOfVideoConferencingServers];
}  TMP_cnt_displays;
#endif


//
class CQmcLogin : public QDialog
{
    Q_OBJECT

    //
public:
    DLG_mcClientLogon_var  m_var;
    TMP_cnt_displays  m_tmpCntDisplays;

    //
private:
    QTimer* m_pWinTimer;

 
public:
    CQmcLogin(QWidget *parent = nullptr);
    ~CQmcLogin();
    void getRegName();

private:
    void initControl();
    
private slots:
    void on_timer_winMethod();
    void onSelectBtnClicked(bool);
    void onLoginOkclicked(bool);
    void onButtonMinClicked();
    void onButtonCloseClicked();
    void load_select();
    void on_editServer_currentIndexChanged(int index);
private:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent*);
    virtual void keyPressEvent(QKeyEvent* event);
    bool m_mousePressed;
    QPoint mousePoint;

private:
    Ui::CQmcLogin* ui;
    WinTitle* winTitle = nullptr;
    //WinSerConfig* winSerConfig = nullptr;

};
#endif // CQMCLOGIN_H
