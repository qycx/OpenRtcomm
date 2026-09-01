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
#include "noticewidget.h"

#include "CInfraredDialogMenu.h"
#include "CDlgDebug.h"
 
#include <mutex>

//
#include	"stdafx.h"
#include	"qyMcMainCommon_qt.h"
#include "DlgMcClientLogon.h" 



//
QT_BEGIN_NAMESPACE
namespace Ui { class CQmcLogin; }
QT_END_NAMESPACE


void login_do_onLoginOkclicked(HWND  hDlg, DLG_mcClientLogon_var& m_var, SmLoginVar& m_smLoginVar, bool b0, bool* pbOk_doLogin);




//
class CQmcLogin : public QDialog
{
    Q_OBJECT

    //
public:
    DLG_mcClientLogon_var  m_var;
    
    //
    //SmLoginVar       m_smLoginVar;
    //HANDLE          m_hThread_ca=nullptr;

    //
private:
    QTimer* m_pWinTimer=nullptr;

 
public:
    CQmcLogin(QWidget *parent = nullptr);
    ~CQmcLogin();
    void getRegName();


    //
    int  showStatus(TCHAR* str);


    //
    //void do_onLoginOkclicked(bool b0, bool* pbOk_doLogin);

    //
    CInfraredDialogMenu* m_pInfraredMenu = nullptr;
    
    //
    bool b_isMenuDebug = false;


    void Infrared_down();
    void Infrared_up();
    void Infrared_ok(QString objname = nullptr);
   

    void showHint(QString msg, QString fontColor = "#f60", qint64 out_time = 3000);
    //
    void sheetBackgroundImage();
private:
    void initControl();


    
    //
private slots:
    void on_timer_winMethod();
    void onSelectBtnClicked(bool);
    void onLoginOkclicked(bool);
    void onButtonMinClicked();
    void onButtonCloseClicked();
    void load_select();
    void on_editServer_currentIndexChanged(int index);

    void on_showDeviceBinding_slots();
    
    void on_infraredMenu();
    void infraredMenu_quit();

    void on_showDebug_slots();

    void refResolution();

 

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
    //NoticeWidget noticeWin;
    //WinSerConfig* winSerConfig = nullptr;

};
#endif // CQMCLOGIN_H
