#ifndef WINBASIC_H
#define WINBASIC_H
#include "stdafx.h"
#include <QDialog>
#include <QMouseEvent>
#include <QPoint>
#include <QCursor>
#include <QRect>
#include <windowsx.h>
#include <QMouseEvent>
#include <QAbstractNativeEventFilter>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QLabel>

class WinBasic : public QWidget
{
    Q_OBJECT

public:
    WinBasic(bool showBorder, QWidget* parent = nullptr);
    ~WinBasic();

    bool isLeftDalk = true;
    bool isTopDalk = true;
    //
    bool  isChatTalk = false;
    //
    void setCanResize(bool b) { canResize_ = b; }
protected:
    // void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent* event);
    bool nativeEvent(const QByteArray& eventType, void* message, long* result);
    bool m_mousePressed;
    QPoint mousePoint;
    void drawShadow(QPainter* painter);
    virtual void paintEvent(QPaintEvent* event);
    virtual bool eventFilter(QObject* target, QEvent* event);
    virtual bool canResize() { return canResize_; }

private slots:
    void onShowClose(bool);
    void onShowMin(bool);
private:
    bool showBorder_ = false;
    bool canResize_ = true;

};

#endif // WINBASIC_H
