#pragma once 

#include <QObject>  
#include <QtWebEngineWidgets/QWebEngineView>
#include <QWebChannel>
#include <QNetworkProxyFactory>  
#include <QDomDocument>
#include <QDomNode>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDesktopServices>
#include <QDebug>
#include <QMenu>
class WinQWebEnginePage : public QWebEnginePage
{
	Q_OBJECT
public:
	explicit WinQWebEnginePage(QObject* parent = nullptr) : QWebEnginePage(parent) {}
protected:
	bool acceptNavigationRequest(const QUrl& url, NavigationType type, bool isMainFrame);
};

class MsgHtmlObj : public QObject
{
	Q_OBJECT
		Q_PROPERTY(QString msgLHtmlTmpl MEMBER m_msgLHtmlTmpl NOTIFY signalMsgHtml)
		Q_PROPERTY(QString msgRHtmlTmpl MEMBER m_msgRHtmlTmpl NOTIFY signalMsgHtml)
		Q_PROPERTY(QString msgRHtmlFile MEMBER m_msgRHtmlFile NOTIFY signalMsgHtml)
		Q_PROPERTY(QString msgLHtmlFile MEMBER m_msgLHtmlFile NOTIFY signalMsgHtml)


public:
	HWND m_hTalk;
public:
	MsgHtmlObj(QObject* parent);

signals:
	void signalMsgHtml(const QString& html);
	void FileMessageProgress(const QString& mesid, QString progress, int iStatus, QString userid, int isObjType);
public slots:
	/// <summary>
	/// 接收文件
	/// </summary>
	void fileRecv(QString msgid);
	/// <summary>
	/// 取消接收文件
	/// </summary>
	/// <param name="msgid"></param>
	void fileCancel(QString msgid);

	//打开文件夹
	void openFile(QString fileName, QString msgid, QString userid);
	//显示更多 
	void showMore(int page);

	void clickReceive(QString msgid, QString msg);
	void clickHeader(int userid, int chatType);
	void clickLeftHeader(int userid);



private:
	QString m_msgLHtmlTmpl;
	QString m_msgRHtmlTmpl;
	QString m_msgRHtmlFile;
	QString m_msgLHtmlFile;
};


class WinMsgShow : public QWebEngineView
{
	Q_OBJECT

public:
	WinMsgShow(QWidget* parent);
	~WinMsgShow();
	//发送消息
	void sendMsg(const QString& html, const QString& username, const QString& msgid, const int& msgtype, const int& fileStatus, const int& chatType, const int& isMore, const int& filesize, const int& userid);
	//接收消息
	void receiveMsg(const QString& html, const QString& username, const QString& msgid, const int& msgtype, const int& fileStatus, const int& chatType, const int& isMore, const int& filesize, const int& userid);

	//设置文件进度
	void setFileProgress(const QString& msgid, QString progress, int iStatus, QString userid, int isObjType);

	//
	void MoreEnd();

	void dragEnterEvent(QDragEnterEvent* event) Q_DECL_OVERRIDE;
	void dragMoveEvent(QDragMoveEvent* event) Q_DECL_OVERRIDE;
	void dropEvent(QDropEvent* event) Q_DECL_OVERRIDE;

signals:
	void signal_file_drag(QString fileName);

private:
	QList<QStringList> parseHtml(const QString& html);
	QList<QStringList> parseDocNode(const QDomNode& node);

private:
public:
	MsgHtmlObj* m_msgHtmlObj = nullptr;
private:
	bool m_bshowbox;
	WinQWebEnginePage* winpage = nullptr;
	QWebChannel* channel = nullptr;
public:
	void contextMenuEvent(QContextMenuEvent* event);
	//void selectedTextData();
private:
	//QMenu* m_pContextMenu;
	//QAction* m_pCopyAct;
	//QAction* m_pPastAct;

	void RightShowMenu();
	void CopyAction();
	void PasteAction();
};

