#ifndef WINROOTCONTATITEM_H
#define WINROOTCONTATITEM_H

#include <QAbstractItemModel>
#include <QLabel>

class QPropertyAnimation;
class WinRootContatItem : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(int rotation READ rotation WRITE setRotation)

public:
    WinRootContatItem(QWidget *parent = nullptr);
    ~WinRootContatItem();

public:
    void setText(const QString& title);
    void setExpanded(bool expand);

private:
    int rotation();
    void setRotation(int rotation);

private:
    void paintEvent(QPaintEvent *event);

private:
    QPropertyAnimation * m_animation;
    QString m_titleText;
    int m_rotation;
};

#endif // WINROOTCONTATITEM_H
