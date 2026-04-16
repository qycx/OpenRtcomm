#ifndef EMOTIONWINDOW_H
#define EMOTIONWINDOW_H

#include <QDialog>
#include "ui_WinEmotion.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WinEmotion; }
QT_END_NAMESPACE

class WinEmotion : public QWidget
{
	Q_OBJECT

public:
	WinEmotion(QWidget *parent = 0);
	~WinEmotion();

private:
	void initControl();

private slots:
	void addEmotion(QString code);

signals:
	void signalWinEmotionHide();
	void signalEmotionItemClicked(QString code);

private:
	void paintEvent(QPaintEvent *event) override;
	void focusOutEvent(QFocusEvent *event) override;
	void showEvent(QShowEvent *event) override;

private:
	Ui::WinEmotion *ui;
};

#endif // EMOTIONWINDOW_H
