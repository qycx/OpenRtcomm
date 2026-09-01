#ifndef WINSERCONFIG_H
#define WINSERCONFIG_H   

#include "ui_WinSerConfig.h" 
#include "WinMsgBox.h"
#include "WinTitle.h"
#include <QDialog> 


QT_BEGIN_NAMESPACE
namespace Ui { class WinSerConfig; }
QT_END_NAMESPACE

class WinSerConfig : public QDialog
{
    Q_OBJECT
public:
        struct {
        void* plogin;
        int index_cntCfg;
    } m_var;

public:
    WinSerConfig(QWidget*parent = nullptr);
    ~WinSerConfig();
    int initWinSerConfig();

    int init();
   
signals:
   void signal_select_load();

private:
    void initTableWidget();
   // void insertTableWidget(QString uuid,QString serviceName,QString ipAddr,QString addr1,QString addr2,QString port);
    void insertTableWidget(QString uuid,QString serviceName,QString addr1,QString port);
    //void updateTableWidget(QString uuid,QString serviceName,QString ipAddr,QString addr1,QString addr2,QString port);
    void updateTableWidget(QString uuid,QString serviceName,QString addr1,QString port);
    void loadStyleSheet(const QString &sheetName);
    QString getCurrent();

private slots:
    void editBtnClicked();
    void delBtnClicked();
    void cancelBtnClicked();
    void addBtnClicked();
    void saveBtnClicked();
    void editBtnClicked(QString uuid);
    void deleteBtnClicked(QString uuid);
    void onShowClose(bool);
    void onShowMin(bool);
    void onButtonMinClicked();
    void onButtonCloseClicked();

private:
    Ui::WinSerConfig *ui; 
    WinTitle* winTitle = nullptr; 

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent*);
    bool m_mousePressed;
    QPoint mousePoint;
};

#endif // WINSERCONFIG_H
