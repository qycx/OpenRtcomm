#include "WinMsgQTextEdit.h" 
#include	"stdafx.h"
#include	"qyMcMainCommon_qt.h"
#include	"ctxQmc_qt.h"
#include "CDlgTalk_qt.h";
#include <QClipboard>	


//
WinMsgQTextEdit::WinMsgQTextEdit(QWidget*parent)
	: QTextEdit(parent)
{
	this->installEventFilter(this);
}



WinMsgQTextEdit::~WinMsgQTextEdit()
{
	deleteAllEmotionImage();
}



void WinMsgQTextEdit::deleteAllEmotionImage()
{
	//for (auto itor = m_emotionMap.constBegin(); itor != m_emotionMap.constEnd(); ++itor)
	//{
	//	delete itor.key();
	//}
	//m_emotionMap.clear();
}

void WinMsgQTextEdit::addEmotionUrl(QString code)
{
	//char32_t t[] = { 0x1F601,0x0 };	//加上0x00是为了防止表情后面跟随乱码
	//t[0] = emotionNum;
	//QString imageName = QString::fromUcs4(t);
	//QVector<uint> ind = imageName.toUcs4();
	//this->insertPlainText(imageName);
	//this->setText(imageName);

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();

	
	const QString&& imageName = QString::fromUtf16((char16_t*)pProcInfo->m_var.installDir_qt) + "/resource/emoji/" + code + ".png";
	const QString&& flagName = QString("%1").arg(imageName);
	QImage image(imageName);
	image=image.scaled(32,32,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
	this->textCursor().insertImage(image, QString("emoj:%1").arg(code));
	//insertHtml(QString("<img src='%1' width='32' height='32'></img>").arg(flagName));

	//if (m_listEmotionUrl.contains(imageName))
	//	return;
	//else
	//	m_listEmotionUrl.append(imageName);

	//QMovie* apngMovie = new QMovie(imageName, "apng", this);
	//apngMovie->setCacheMode(QMovie::CacheNone);
	//m_emotionMap.insert(apngMovie, flagName);

	//connect(apngMovie, SIGNAL(frameChanged(int)), this, SLOT(onEmotionImageFrameChange(int)));
	//apngMovie->start();

	updateGeometry();
	verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}

//void WinMsgQTextEdit::onEmotionImageFrameChange(int frame)
//{
//	QMovie* movie = qobject_cast<QMovie*>(sender());
//	document()->addResource(QTextDocument::ImageResource, QUrl(m_emotionMap.value(movie)), movie->currentPixmap());
//	setLineWrapColumnOrWidth(lineWrapColumnOrWidth());
//}
//
void WinMsgQTextEdit::insertFromMimeData(const QMimeData* source)
{
	//__super::insertFromMimeData(source);
	
#if  0
	if( source->hasHtml() )
	{
		QString str = source->html();
		QString tmp_str = QTextEdit::toPlainText();
		QTextEdit::setPlainText(tmp_str + str);
		QTextEdit::moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
	}
#endif

		
	if (source->hasText())
	{

		QString str = source->text().trimmed();
		int nPrefix = _tcslen(_T("file:///"));
		QString kk = str.mid(nPrefix);
		if (kk.size() != 0) {
			if (bFileExists((TCHAR*)kk.utf16())) {
				//
				emit signal_file_drag(kk);
			}
		}
		else 
		{
			QString tmp_str = QTextEdit::toPlainText();
			QTextEdit::setPlainText(tmp_str + str);
			QTextEdit::moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
		}
		
	}
	else
	{
		QTextEdit::insertFromMimeData(source);
	}
}

void WinMsgQTextEdit::keyPressEvent(QKeyEvent* event)
{
	//抓取快捷键 Ctrl V
	if (event->key() == Qt::Key_V && event->modifiers() == Qt::ControlModifier) {
		QClipboard* clipboard = QApplication::clipboard();
		QString text = clipboard->text();

		QTextEdit::insertPlainText(text);
		return ;
	}
	__super::keyPressEvent(event);
}

bool WinMsgQTextEdit::eventFilter(QObject* target, QEvent* event)
{
	if (target == this&& event->type() == QEvent::ContextMenu)
	{
		QMenu* menu = this->createStandardContextMenu();
		QList<QAction*> actions = menu->actions();
		QList<QAction*> list;
		for (size_t i = 0; i < actions.size(); i++)
		{
			if (actions[i]->text() != u8"复制" && actions[i]->text() != u8"粘贴")
			{
				list.append(actions[i]);
			}
		}
		for (size_t i = 0; i < list.size(); i++)
		{
			menu->removeAction(list[i]);
		}
		menu->exec(QCursor::pos());
		delete menu;
		return true;
	}
	return QTextEdit::eventFilter(target, event);
}