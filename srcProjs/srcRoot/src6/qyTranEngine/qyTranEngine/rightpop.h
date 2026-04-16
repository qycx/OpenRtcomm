#ifndef RIGHTPOP_H
#define RIGHTPOP_H

#include "epushbutton.h"
#include <QtGui>

#include <QProgressBar>
#include <QVBoxLayout>
#include <QLabel>

class RightPop : public QWidget
{
    Q_OBJECT

public:
    RightPop(QWidget *parent = 0);
    ~RightPop();
    void showMessage();

    void SetTip(const QString& tip);
    void SetProgress(int value);
    void SetSize(const QString& size);

    void startClose();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void onMove();
    void onStay();
    void onClose();
    void onExit();

private:
    QPixmap backGroundPix;
    EPushButton *closeButton;

    QTimer *showTimer;
    QTimer *stayTimer;
    QTimer *closeTimer;
    QPoint point;
    double transparentPercent;
    int desktopHeight;

    QProgressBar* progressBar;
    QLabel* label;
    QLabel* labelSize;
};

#endif // RIGHTPOP_H
