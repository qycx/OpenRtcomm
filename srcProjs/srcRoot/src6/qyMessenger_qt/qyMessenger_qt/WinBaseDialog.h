#ifndef WIN_BASE_DIALOG_H_
#define WIN_BASE_DIALOG_H_



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

class WinBaseDialog : public QDialog
{
    Q_OBJECT

public:
    WinBaseDialog(QWidget *parent);
    ~WinBaseDialog();
    bool isLeftDalk = true;
    bool isTopDalk = true;

protected:
    // void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent* event);
    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result);
    bool m_mousePressed;
    QPoint mousePoint;
    void drawShadow(QPainter* painter);
    virtual void paintEvent(QPaintEvent* event);
    virtual bool canResize() { return true; }
private slots:
    void onShowClose(bool);
    void onShowMin(bool);
private:
    bool showBorder_ = true;
};
#endif // !WIN_BASE_DIALOG_H_