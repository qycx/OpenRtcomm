#include "WinBaseDialog.h"
#include <QPainter>
#include <qmath.h>
#include    <qpainterpath.h>

extern float dpi_ ;
extern int boundaryWidth;

WinBaseDialog::WinBaseDialog(QWidget *parent)
    : QDialog(parent)
{
    setMouseTracking(true);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->installEventFilter(this);
    if (showBorder_)
    {
        this->setAttribute(Qt::WA_TranslucentBackground, true);
        this->setContentsMargins(boundaryWidth, boundaryWidth, boundaryWidth, boundaryWidth);
    }
}

WinBaseDialog::~WinBaseDialog()
{
}




void WinBaseDialog::mousePressEvent(QMouseEvent* event)
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

#else
#endif
}

bool WinBaseDialog::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
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


void WinBaseDialog::drawShadow(QPainter* painter)
{
    painter->save();

    QColor color(0, 0, 0, 30);
    int x_nBorder = 4;
    int x_nRatio = 0;
    for (int i = 0; i < x_nBorder; ++i)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);

        path.addRoundedRect(x_nBorder - i, x_nBorder - i, this->width() - (x_nBorder - i) * 2, this->height() - (x_nBorder - i) * 2, x_nRatio, x_nRatio);

        color.setAlpha(100 - qSqrt(i) * 80);
        painter->setPen(color);
        //
        painter->drawPath(path);
    }

    painter->restore();
}


void WinBaseDialog::paintEvent(QPaintEvent* event)
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



void WinBaseDialog::onShowClose(bool)
{
    close();
}

void WinBaseDialog::onShowMin(bool)
{
    showMinimized();
}

