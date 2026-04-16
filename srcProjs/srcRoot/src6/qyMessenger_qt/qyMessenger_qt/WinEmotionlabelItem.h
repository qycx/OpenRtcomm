#ifndef WINEMOTIONLABELITEM_H
#define WINEMOTIONLABELITEM_H

#define  __noDbg_new__

#include	"qyPrecomp.h"
#include <QLabel>
#include <QMouseEvent>

//class QMovie;
class WinEmotionlabelItem : public QLabel
{
	Q_OBJECT

public:
	WinEmotionlabelItem(QWidget *parent);
	~WinEmotionlabelItem();

	void setEmotionName(QString path,QString name);
protected:
	//void initControl();
	void mousePressEvent(QMouseEvent* event);
#ifndef  __DEBUG__
	void enterEvent(QEnterEvent *event) override;
#endif
	void leaveEvent(QEvent *event) override;

signals:
	void emotionClicked(QString code);

private:
	int m_emotionIndex;
	QString code_;
	//QMovie* m_apngMovie;
};

#endif // WINEMOTIONLABELITEM_H
