#include "WinRootContatItem.h"
#include <QPainter>
#include <QPropertyAnimation>

WinRootContatItem::WinRootContatItem(QWidget *parent)
    : QLabel(parent)
    , m_rotation(0)
{
    setFixedHeight(32);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_animation = new QPropertyAnimation(this, "rotation");
    m_animation->setDuration(50);
    m_animation->setEasingCurve(QEasingCurve::InQuad);
}

WinRootContatItem::~WinRootContatItem()
{
    delete m_animation;
}

void WinRootContatItem::setExpanded(bool expand)
{
    if (expand)
    {
        m_animation->setEndValue(90);
    }
    else
    {
        m_animation->setEndValue(0);
    }
    m_animation->start();
}

int WinRootContatItem::rotation()
{
    return m_rotation;
}

void WinRootContatItem::setRotation(int rotation)
{
    m_rotation = rotation;
    update();
}

void WinRootContatItem::setText(const QString& title)
{
    m_titleText = title;
    update();
}

void WinRootContatItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    {
        painter.setRenderHint(QPainter::TextAntialiasing, true);
        QFont font;
        font.setPointSize(10);
        painter.setFont(font);
        painter.drawText(24, 0, width() - 24, height(), Qt::AlignLeft | Qt::AlignVCenter, m_titleText);
    }

    {
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter.save();
        //背景图
        QPixmap pixmap;
        pixmap.load(":/Resources/Images/WinMain/arrow.png");
        QPixmap tmpPixmap(pixmap.size());
        tmpPixmap.fill(Qt::transparent);

        QPainter p(&tmpPixmap);
        p.setRenderHint(QPainter::SmoothPixmapTransform, true);
        //旋转m_rotation角度
        p.translate(pixmap.width() / 2, pixmap.height() / 2);
        p.rotate(m_rotation);
        p.drawPixmap(0 - pixmap.width() / 2, 0 - pixmap.height() / 2, pixmap);
        painter.drawPixmap(6, (height() - pixmap.height()) / 2, tmpPixmap);
        painter.restore();
    }

    QLabel::paintEvent(event);
}
