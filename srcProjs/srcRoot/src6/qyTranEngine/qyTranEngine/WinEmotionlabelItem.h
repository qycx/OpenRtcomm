#ifndef WINEMOTIONLABELITEM_H
#define WINEMOTIONLABELITEM_H

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
	void enterEvent(QEvent *event) override;
	void leaveEvent(QEvent *event) override;

signals:
	void emotionClicked(QString code);

private:
	int m_emotionIndex;
	QString code_;
	//QMovie* m_apngMovie;
};

#endif // WINEMOTIONLABELITEM_H
