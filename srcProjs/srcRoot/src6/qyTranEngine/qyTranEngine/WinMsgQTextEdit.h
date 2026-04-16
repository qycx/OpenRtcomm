#pragma once

#include <QObject>
#include <QTextEdit>
#include <QMovie>
#include <QFont>
#include <QScrollBar>
#include <QMimeData>

class WinMsgQTextEdit : public QTextEdit
{
	Q_OBJECT

public:
	WinMsgQTextEdit(QWidget*parent);
	~WinMsgQTextEdit();

private:
	void insertFromMimeData(const QMimeData* source) override;
	bool eventFilter(QObject* target, QEvent* event);
	void keyPressEvent(QKeyEvent* event);
signals:
	void signal_file_drag(QString fileName);

private slots:
	//void onEmotionImageFrameChange(int frame);

public:
	void addEmotionUrl(QString code);
	void deleteAllEmotionImage();

private:
	//QList<QString> m_listEmotionUrl;
	//QMap<QMovie*, QString> m_emotionMap;
	
};
