#ifndef WINCONTACTSLIST_H
#define WINCONTACTSLIST_H

#include "stdafx.h"
#include <QWidget>
#include "ui_WinContactsList.h"
#include "WinBasic.h"
#include "WinContactItem.h"
#include <QAction>
#include <WinObjUser.h>
#include "qyMcMainCommon_qt.h"
#include "qyMcMainWndProc.h"  
#include "ctxQmc.h"
#include "myDb.h"

#include	"defineModels.h"


QT_BEGIN_NAMESPACE
namespace Ui { class WinContactsList; }
QT_END_NAMESPACE

//联系人
class WinContactsList : public QWidget
{
	Q_OBJECT

public:
	explicit WinContactsList(QWidget* parent = nullptr);
	~WinContactsList();
	void initControl();

public:
	//显示联系人
	void showContactList(CMyDb* pDb, QMEM_qyImObj* pQMem);

	//
	void addToContactList(CMyDb* pDb, COMMON_PARAM * pCommonParam1, QMEM_qyImObj* pQMem);
	void fillGrp(QList<myFriendInfo>& pq);
	void fillTmpGrp(QList<myFriendInfo>& pq);
	void fillContact(QList<myFriendInfo>& pq);

	void updateContactItem(qint64 idInfo, unsigned  short status);

	//
	int toContactList();
	void addTmpContactItem(int id);
	void delTmpContactItem(QString idInfo);

	//
	int  onLineStatusUp();
	//bool eventFilter(QObject* obj, QEvent* event);
	void wheelEvent(QWheelEvent* event);
private slots:
	//联系人的树控件的信号槽
	void on_treeWidgetContacts_itemExpanded(QTreeWidgetItem* item);
	void on_treeWidgetContacts_itemCollapsed(QTreeWidgetItem* item);
	void on_treeWidgetContacts_itemClicked(QTreeWidgetItem* item, int column);
	void on_treeWidgetContacts_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);
	void onScrollBarValueChanged(int);

signals:
	void toShowContactsInfo(WinObjUser user);

private:
	Ui::WinContactsList* ui;
	QTreeWidgetItem* m_pRootFriendItemGroup;
	QTreeWidgetItem* m_pRootFriendItemTemp;
	QTreeWidgetItem* m_pRootFriendItemFriend;
	//QMap<int64_t, QString> grpInfoMap;
};

#endif // WINCONTACTSLIST_H
