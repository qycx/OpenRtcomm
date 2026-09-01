#pragma once
#include <tchar.h>
#include <QWidget>
#include <QFrame>
#include "qyMcMainCommon_qt.h"
#include "dlgVideosProc.h"
#include <QTimer>

class ShareStreamWidget  : public QWidget
{
    Q_OBJECT

public:
    ShareStreamWidget(QWidget *parent=nullptr);
    ~ShareStreamWidget();
private:
    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result);
    void resizeEvent(QResizeEvent* event);
private slots:
    void on_timer_winMethod();
private:
    DLG_videos_var		    m_var;
    QFrame              *   m_peer=nullptr;
    QTimer              *   m_pWinTimer=nullptr;
    int                     m_loopCtrl = 0;
};
