#ifndef WINQCLICKLABEL_H
#define WINQCLICKLABEL_H

#include <QLabel>

class WinQClickLabel : public QLabel
{
	Q_OBJECT

public:
	WinQClickLabel(QWidget *parent);
	~WinQClickLabel();

signals:
	void clicked();

private:
	void mousePressEvent(QMouseEvent *event);
};

#endif // WINQCLICKLABEL_H
