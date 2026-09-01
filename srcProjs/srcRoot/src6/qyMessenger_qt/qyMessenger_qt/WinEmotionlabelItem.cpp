

#define  __noDbg_new__

#include "WinEmotionlabelItem.h" 
//#include <QMovie>

WinEmotionlabelItem::WinEmotionlabelItem(QWidget* parent)
    : QLabel(parent)
{
    setAlignment(Qt::AlignCenter);
    setObjectName("WinEmotionlabelItem");
    setFixedSize(40, 40);
    //initControl();
    //connect(this, &WinQClickLabel::clicked, [this](){
    //	emit emotionClicked(m_emotionName);
    //});
}

WinEmotionlabelItem::~WinEmotionlabelItem()
{

}

void WinEmotionlabelItem::setEmotionName(QString path, QString name)
{
    QString imageName = path + name;
    //this->setText(name);
    int idx = name.indexOf('.');
    if (idx > 0)
    {
        code_ = name.left(idx);
    }
    this->setPixmap(QPixmap(imageName).scaled(this->size().width() - 8, this->size().height() - 8, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    this->setStyleSheet("QLabel:hover{background:#dddddd}");
    //m_apngMovie = new QMovie(imageName, "apng", this);
    //m_apngMovie->start();
    //m_apngMovie->stop();
    //setMovie(m_apngMovie);
}

//void WinEmotionlabelItem::initControl()
//{
//	setAlignment(Qt::AlignCenter);
//	setObjectName("WinEmotionlabelItem");
//	setFixedSize(32, 32);
//}

void WinEmotionlabelItem::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit emotionClicked(code_);
    }
}

#ifndef  __DEBUG__
void WinEmotionlabelItem::enterEvent(QEnterEvent* event)
{
    //m_apngMovie->start();
    __super::enterEvent(event);
}
#endif


void WinEmotionlabelItem::leaveEvent(QEvent* event)
{
    //m_apngMovie->jumpToFrame(0);
    //m_apngMovie->stop();
    __super::leaveEvent(event);
}
