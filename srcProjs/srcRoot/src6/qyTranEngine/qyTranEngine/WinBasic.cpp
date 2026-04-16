#include "WinBasic.h" 
#include <QPainter>
#include <QtMath>
#include <QDebug>
#include    "stdafx.h"
#include    "qyMcMainCommon_qt.h"

//
float dpi_ = 1;
int boundaryWidth = 4;

WinBasic::WinBasic(bool showBorder, QWidget* parent)
    : QWidget(parent)
{
    showBorder_ = showBorder;
    setMouseTracking(true);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->installEventFilter(this);
    if (showBorder_)
    {
        this->setAttribute(Qt::WA_TranslucentBackground, true);
        this->setContentsMargins(boundaryWidth, boundaryWidth, boundaryWidth, boundaryWidth);
    }


}


void WinBasic::mousePressEvent(QMouseEvent* event)
{
#ifdef Q_OS_WIN
    // qDebug() << "x====" << event->pos().x() << "y===========" << event->pos().y();


    if (isTopDalk) {
        if (event->pos().y() <= 30 * dpi_)
        {
            if (ReleaseCapture())
            {
                HWND par = ::GetParent(HWND(winId()));
                SendMessage(HWND(winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
            }
            event->ignore();
        }
    }


    if (isLeftDalk) {
        if (event->pos().x() <= 100 * dpi_) {
            if (ReleaseCapture())
            {
                HWND par = ::GetParent(HWND(winId()));
                SendMessage(HWND(winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
            }
            event->ignore();
        }
    }

    //
    if (isChatTalk) {
        if (event->pos().y() <= 60 * dpi_)
        {
            if (ReleaseCapture())
            {
                CCtxQyMc* pQyMc = g_pQyMc;
                if (pQyMc) {
                    //
                    HWND par = pQyMc->gui.hMainWnd;
                    SendMessage(HWND(par), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
                }
            }
            event->ignore();
        }
    }


#else
#endif
}

bool WinBasic::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
    if (!canResize())
    {
        return false;
    }
    MSG* msg = (MSG*)message;
    switch (msg->message)
    {
    case WM_NCHITTEST:
    {
        int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x() * dpi_;
        int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y() * dpi_;
        if (xPos < boundaryWidth * dpi_ && yPos < boundaryWidth * dpi_)                    //左上角
            *result = HTTOPLEFT;
        else if (xPos >= width() * dpi_ - boundaryWidth * dpi_ && yPos < boundaryWidth * dpi_)          //右上角
            *result = HTTOPRIGHT;
        else if (xPos < boundaryWidth * dpi_ && yPos >= height() * dpi_ - boundaryWidth * dpi_)         //左下角
            *result = HTBOTTOMLEFT;
        else if (xPos >= width() * dpi_ - boundaryWidth * dpi_ && yPos >= height() * dpi_ - boundaryWidth * dpi_)//右下角
            *result = HTBOTTOMRIGHT;
        else if (xPos < boundaryWidth * dpi_)                                     //左边
            *result = HTLEFT;
        else if (xPos >= width() * dpi_ - boundaryWidth * dpi_)                              //右边
            *result = HTRIGHT;
        else if (yPos < boundaryWidth * dpi_)                                       //上边
            *result = HTTOP;
        else if (yPos >= height() * dpi_ - boundaryWidth * dpi_)                             //下边
            *result = HTBOTTOM;
        else              //其他部分不做处理，返回false，留给其他事件处理器处理
            return false;
        return true;
    }
    }
    return QWidget::nativeEvent(eventType, message, result);
}

bool WinBasic::eventFilter(QObject* target, QEvent* event)
{
    if (target == this)
    {
        if (event->type() == QEvent::WindowStateChange)
        {
            boundaryWidth = this->windowState() == Qt::WindowMaximized ? 0 : 4;
            this->setContentsMargins(boundaryWidth, boundaryWidth, boundaryWidth, boundaryWidth);
            if (this->windowState() != Qt::WindowMaximized)
            {
                this->resize(this->size().width() + boundaryWidth * 2, this->size().height() + boundaryWidth * 2);
            }
            return false;
        }
    }
    return QWidget::eventFilter(target, event);
}
void WinBasic::drawShadow(QPainter* painter)
{
    painter->save();

    QColor color(207, 207, 207, 30);
    int x_nBorder = 4;
    int x_nRatio = 0;
    for (int i = 0; i < x_nBorder; ++i)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);

        path.addRoundedRect(x_nBorder - i, x_nBorder - i, this->width() - (x_nBorder - i) * 2, this->height() - (x_nBorder - i) * 2, x_nRatio, x_nRatio);

        color.setAlpha(100 - qSqrt(i) * 80);
        painter->setPen(color);
        painter->drawPath(path);
    }

    painter->restore();
}


void WinBasic::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    if (showBorder_)
    {
        painter.setRenderHint(QPainter::Antialiasing);

        //drawBG(&painter);

        drawShadow(&painter);
    }
    else
    {
        QWidget::paintEvent(event);
    }
    //QDialog::paintEvent(event);
}



void WinBasic::onShowClose(bool)
{
    close();
}

void WinBasic::onShowMin(bool)
{
    showMinimized();
}


WinBasic::~WinBasic()
{
}

