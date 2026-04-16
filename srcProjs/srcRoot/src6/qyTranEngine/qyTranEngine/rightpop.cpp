#include "rightpop.h"

#include <QApplication>

#include <QDesktopWidget>

#include <QProgressBar>
#include <QVBoxLayout>
#include <QLabel>

RightPop::RightPop(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint| Qt::ToolTip)
    , transparentPercent(1.0)
    , progressBar(nullptr)
    , label(nullptr)
    , labelSize(nullptr)
{
    resize(300, 200);
    backGroundPix.load(":/Resources/Images/popup/background.png");
    backGroundPix = backGroundPix.scaled(width(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    closeButton = new EPushButton(this);
    closeButton->setPixName(":/Resources/Images/popup/close");
    closeButton->setToolTip(tr("close"));
    closeButton->move(width() - 27, 0);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(onExit()));



    QVBoxLayout layout(this);

    label = new QLabel("uploading....", this);
    layout.addWidget(label);
    label->setGeometry(20, 50, 300, 30);

    progressBar = new QProgressBar(this);
    layout.addWidget(progressBar);
    progressBar->setGeometry(20, 100, 280, 30);

    progressBar->setRange(0, 100); // 设置进度条的范围从0到100
    //progressBar->setValue(50); // 初始化进度条值为0


    labelSize = new QLabel("", this);
    layout.addWidget(labelSize);
    labelSize->setGeometry(180, 140, 300, 30);
    labelSize->show();


    showTimer = new QTimer(this);
    showTimer->setInterval(5);
    stayTimer = new QTimer(this);
    stayTimer->setInterval(5000);
    closeTimer = new QTimer(this);
    closeTimer->setInterval(5);

    connect(showTimer, SIGNAL(timeout()), this, SLOT(onMove()));
    connect(stayTimer, SIGNAL(timeout()), this, SLOT(onStay()));
    connect(closeTimer, SIGNAL(timeout()), this, SLOT(onClose()));
    //showMessage();

    //SetProgress(30);
    //SetTip("file");
}

void RightPop::SetTip(const QString& tip)
{
    if (label)
        label->setText(tip);
        
}

void RightPop::SetProgress(int value)
{
    if (progressBar)
        progressBar->setValue(value);

}

void RightPop::SetSize(const QString& size)
{
    if (labelSize)
        labelSize->setText(size);

}

RightPop::~RightPop()
{

}

void RightPop::showMessage()
{
    QRect rect = QApplication::desktop()->availableGeometry();
    point.setX(rect.width() - width());
    point.setY(rect.height() + 50);
    desktopHeight = rect.height() + 50;
    move(point.x(), point.y());
    showTimer->start();
}

void RightPop::onMove()
{
    desktopHeight--;
    move(point.x(), desktopHeight);
        qDebug() << point.x() << desktopHeight;
    if (desktopHeight <= point.y() - 200) {
        showTimer->stop();
        stayTimer->start();
    }
}

void RightPop::onStay()
{
    stayTimer->stop();
    //closeTimer->start();
}

void RightPop::startClose() {
    closeTimer->start();
}

void RightPop::onClose()
{
//    transparentPercent -= 0.1;
//    qDebug() << transparentPercent;
//    if (transparentPercent <= 0.0) {
//        closeTimer->stop();
//        onExit();
//    }
//    else {
//        setWindowOpacity(transparentPercent);
//    }
    desktopHeight++;
    move(point.x(), desktopHeight);
    if (desktopHeight >= point.y()) {
        closeTimer->stop();
        onExit();
    }
}

void RightPop::onExit()
{
    hide();
    //exit(0);
}

void RightPop::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), backGroundPix);
    painter.setFont(QFont("arial", 10, QFont::Bold));
    painter.setPen(QColor("#FFFFFF"));
    painter.setBrush(QColor("#FFFFFF"));
    painter.drawText(QRectF(5, 5, 100, 35), tr("Uploading...."));
    painter.drawRect(QRectF(0, 30, width(), height() - 30));

    QWidget::paintEvent(event);
}

