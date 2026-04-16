#include "WinQClickLabel.h"
#include <QMouseEvent>

WinQClickLabel::WinQClickLabel(QWidget *parent)
	: QLabel(parent)
{
	
}

WinQClickLabel::~WinQClickLabel()
{

}

void WinQClickLabel::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit clicked();
	}
}
