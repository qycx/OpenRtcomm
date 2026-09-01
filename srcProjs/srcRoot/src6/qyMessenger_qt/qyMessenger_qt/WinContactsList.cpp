
#include "WinContactsList.h"
#include "ui_WinContactsList.h"
#include "WinRootContatItem.h"

#include "WinBasic.h"
#include <QDebug>
#include <QTableWidgetItem>
#include <qscrollarea.h>
#include	"defineModels.h"
#include <QScrollBar>
#include	<qfile.h>


//
WinContactsList* winCl = NULL;

WinContactsList::WinContactsList(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::WinContactsList)
{
	ui->setupUi(this);
	winCl = this;
	initControl();

	QScrollBar* verticalScrollBar = ui->treeWidgetContacts->verticalScrollBar();

	connect(verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(onScrollBarValueChanged(int)));

}

//捕捉滚动条事件
void WinContactsList::onScrollBarValueChanged(int value)
{
	onLineStatusUp();
}
WinContactsList::~WinContactsList()
{
	delete ui;
	if (m_pRootFriendItemGroup)
	{
		delete m_pRootFriendItemGroup;
		m_pRootFriendItemGroup = nullptr;
	}
	if (m_pRootFriendItemTemp)
	{
		delete m_pRootFriendItemTemp;
		m_pRootFriendItemTemp = nullptr;
	}
	if (m_pRootFriendItemFriend)
	{
		delete m_pRootFriendItemFriend;
		m_pRootFriendItemFriend = nullptr;
	}
}

void WinContactsList::initControl()
{
	QFile file(":/Resources/QSS/WinContactsList.css");
	file.open(QFile::ReadOnly);
	if (file.isOpen())
	{
		this->setStyleSheet("");
		QString qsstyleSheet = QLatin1String(file.readAll());
		this->setStyleSheet(qsstyleSheet);
	}
	file.close();



	//群组
	m_pRootFriendItemGroup = new QTreeWidgetItem();
	m_pRootFriendItemGroup->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
	//设置Data用于区分，Item是分组节点还是子节点，0代表分组节点，1代表子节点
	m_pRootFriendItemGroup->setData(0, Qt::UserRole, 0);
	WinRootContatItem* pItemName1 = new WinRootContatItem(ui->treeWidgetContacts);
	pItemName1->setText(u8"群组");
	//擦入分组节点
	ui->treeWidgetContacts->addTopLevelItem(m_pRootFriendItemGroup);
	ui->treeWidgetContacts->setItemWidget(m_pRootFriendItemGroup, 0, pItemName1);

	//临时组
	m_pRootFriendItemTemp = new QTreeWidgetItem();
	m_pRootFriendItemTemp->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
	//设置Data用于区分，Item是分组节点还是子节点，0代表分组节点，1代表子节点
	m_pRootFriendItemTemp->setData(0, Qt::UserRole, 0);
	WinRootContatItem* pItemName2 = new WinRootContatItem(ui->treeWidgetContacts);
	pItemName2->setText(u8"临时组");
	//擦入分组节点
	ui->treeWidgetContacts->addTopLevelItem(m_pRootFriendItemTemp);
	ui->treeWidgetContacts->setItemWidget(m_pRootFriendItemTemp, 0, pItemName2);
	
	//好友
	m_pRootFriendItemFriend = new QTreeWidgetItem();
	m_pRootFriendItemFriend->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
	m_pRootFriendItemFriend->setData(0, Qt::UserRole, 0);
	WinRootContatItem* pItemName3 = new WinRootContatItem(ui->treeWidgetContacts);
	pItemName3->setText(u8"好友");
	ui->treeWidgetContacts->addTopLevelItem(m_pRootFriendItemFriend);
	ui->treeWidgetContacts->setItemWidget(m_pRootFriendItemFriend, 0, pItemName3);
}

//显示联系人
void WinContactsList::showContactList(CMyDb* pDb, QMEM_qyImObj* pQMem)
{
	QY_MC* pQyMc = QY_GET_GBUF();
	MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	QY_MESSENGER_REGINFO		regInfo;
	QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
	QM_dbFuncs& g_dbFuncs = *pDbFuncs;
	TCHAR						grpIdBuf[256];
	memset(&regInfo, 0, sizeof(regInfo));
	IM_GRP_INFO					grp_info;
	memset(&grp_info, 0, sizeof(grp_info));

	_sntprintf(tBuf, mycountof(tBuf), _T("%I64u"), pQMem->messengerInfo.idInfo.ui64Id);
	if (pQMem->messengerInfo.iStatus == CONST_qyStatus_ok)
	{
		if (pQMem->messengerInfo.uiType != CONST_objType_imGrp)
		{
			if (!g_dbFuncs.pf_bGetMessengerRegInfoBySth(pDb, CONST_dbType_myDb, getResTable(0, &pQyMc->cusRes, CONST_resId_fieldIdTable), CONST_tabName_qyImObjRegInfoTab, pQMem->messengerInfo.misServName, &pQMem->messengerInfo.idInfo, 0, &regInfo))
			{
				memset(&regInfo, 0, sizeof(regInfo));
			}
			int		tmpiRet;
			TCHAR	talkerDesc[128] = _T("");
			regInfo2Desc(0, &regInfo, &desc, talkerDesc, mycountof(talkerDesc), NULL, 0);
			QString pdw = QString::fromWCharArray(desc.pDw).trimmed();
			QString pBm = QString::fromWCharArray(desc.pBm).trimmed();
			QString pSyr = QString::fromWCharArray(desc.pSyr).trimmed();
			QString idinfo = QString::fromWCharArray(tBuf);
			if (!pSyr.isEmpty())
			{
				//if (grpInfoMap.isEmpty() || grpInfoMap.value(pQMem->messengerInfo.idInfo.ui64Id).isEmpty())
				{
					

					//grpInfoMap.insert(pQMem->messengerInfo.idInfo.ui64Id, pSyr);
					QTreeWidgetItem* pChild = new QTreeWidgetItem();
					//添加子节点 
					pChild->setData(0, Qt::UserRole, 1);
					WinObjUser user;
					user.idinfo = idinfo;
					user.name = pSyr;
					user.dw = pdw;
					user.bm = pBm;
					user.dataType = 3;//好友
					pChild->setData(0, Qt::UserRole + 1, QVariant::fromValue(user));
					WinContactItem* pContactItem = new WinContactItem(user.idinfo,ui->treeWidgetContacts);
					QPixmap pix1(":/Resources/Images/WinMain/person.png");
					pContactItem->setHeadPixmap(pix1);
					pContactItem->setUserName(pSyr);

					pContactItem->setSignName(pdw + " " + pBm);
					m_pRootFriendItemFriend->addChild(pChild);
					ui->treeWidgetContacts->setItemWidget(pChild, 0, pContactItem);
				}
			}
		}
		else if (pQMem->messengerInfo.uiType == CONST_objType_imGrp)
		{
			if (!g_dbFuncs.pf_bGetImGrpInfoBySth(pDb, CONST_dbType_myDb, pQMem->messengerInfo.misServName, &pQMem->messengerInfo.idInfo, &grp_info))
			{
				memset(&grp_info, 0, sizeof(grp_info));
			};
			_sntprintf(grpIdBuf, mycountof(grpIdBuf), _T("%I64u"), grp_info.idInfo.ui64Id);
			QString pdw = QString::fromWCharArray(grp_info.name).trimmed();
			QString idinfo = QString::fromWCharArray(tBuf);
			QString idInfo_creator = QString::number(grp_info.idInfo_creator.ui64Id);// :fromWCharArray(grpIdBuf);
			if (!pdw.isEmpty())
			{
				//if (grpInfoMap.isEmpty() || grpInfoMap.value(grp_info.idInfo.ui64Id).isEmpty())
				{
					//grpInfoMap.insert(grp_info.idInfo.ui64Id, pdw);
					if (!idInfo_creator.contains("0"))
					{
						QTreeWidgetItem* pChild = new QTreeWidgetItem();
						//添加子节点
						pChild->setData(0, Qt::UserRole, 1);
						WinObjUser user;
						user.idinfo = idinfo;
						if (pdw.isEmpty()) {
							user.name = idinfo;
						}
						else {
							user.name = pdw;
						}
						
						user.dataType = 2;//临时组
						pChild->setData(0, Qt::UserRole + 1, QVariant::fromValue(user));
						WinContactItem* pContactItem = new WinContactItem(user.idinfo ,ui->treeWidgetContacts);
						pContactItem->setHeadPixmap(QPixmap(":/Resources/Images/WinMain/tmp_group.png"));
						pContactItem->setUserName(pdw);
						m_pRootFriendItemTemp->addChild(pChild);
						ui->treeWidgetContacts->setItemWidget(pChild, 0, pContactItem);
					}
					else
					{
						QTreeWidgetItem* pChild = new QTreeWidgetItem();
						//添加子节点
						pChild->setData(0, Qt::UserRole, 1);
						WinObjUser user;
						user.idinfo = idinfo;
						user.name = pdw;
						user.dataType = 1;//群组
						pChild->setData(0, Qt::UserRole + 1, QVariant::fromValue(user));
						WinContactItem* pContactItem = new WinContactItem(user.idinfo,ui->treeWidgetContacts);
						pContactItem->setHeadPixmap(QPixmap(":/Resources/Images/WinMain/group.png"));
						pContactItem->setUserName(pdw);
						m_pRootFriendItemGroup->addChild(pChild);
						ui->treeWidgetContacts->setItemWidget(pChild, 0, pContactItem);
					}
				}
			}
		}
	}
}

//
void WinContactsList::addToContactList(CMyDb* pDb, COMMON_PARAM  *pCommonParam1,  QMEM_qyImObj* pQMem)

{
	QList<myFriendInfo>* pq_grp = (QList<myFriendInfo>*)pCommonParam1->p0;
	QList<myFriendInfo>* pq_tmpGrp = (QList<myFriendInfo>*)pCommonParam1->p1;
	QList<myFriendInfo>* pq_contact = (QList<myFriendInfo>*)pCommonParam1->p2;

	QY_MC* pQyMc = QY_GET_GBUF();
	MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	QY_MESSENGER_REGINFO		regInfo;
	QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
	QM_dbFuncs& g_dbFuncs = *pDbFuncs;
	TCHAR						grpIdBuf[256];
	memset(&regInfo, 0, sizeof(regInfo));
	IM_GRP_INFO					grp_info;
	memset(&grp_info, 0, sizeof(grp_info));

	_sntprintf(tBuf, mycountof(tBuf), _T("%I64u"), pQMem->messengerInfo.idInfo.ui64Id);
	if (pQMem->messengerInfo.iStatus == CONST_qyStatus_ok)
	{
		if (pQMem->messengerInfo.uiType != CONST_objType_imGrp)
		{
			if (!g_dbFuncs.pf_bGetMessengerRegInfoBySth(pDb, CONST_dbType_myDb, getResTable(0, &pQyMc->cusRes, CONST_resId_fieldIdTable), CONST_tabName_qyImObjRegInfoTab, pQMem->messengerInfo.misServName, &pQMem->messengerInfo.idInfo, 0, &regInfo))
			{
				memset(&regInfo, 0, sizeof(regInfo));
			}
			int		tmpiRet;
			TCHAR	talkerDesc[128] = _T("");
			regInfo2Desc(0, &regInfo, &desc, talkerDesc, mycountof(talkerDesc), NULL, 0);
			QString pdw = QString::fromWCharArray(desc.pDw).trimmed();
			QString pBm = QString::fromWCharArray(desc.pBm).trimmed();
			QString pSyr = QString::fromWCharArray(desc.pSyr).trimmed();
			QString idinfo = QString::fromWCharArray(tBuf);
			//
			myFriendInfo fi;
			fi.userId = pQMem->messengerInfo.idInfo.ui64Id;
			fi.dw = pdw;
			fi.bm = pBm;
			if (pSyr.isEmpty()) {
				fi.syr = QString::number(pQMem->messengerInfo.idInfo.ui64Id);
			}
			else {
				fi.syr = pSyr;
			}
			
			CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
			if (!pProcInfo)  return;
			MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
			QY_MESSENGER_ID  idInfo;
			//
			idInfo.ui64Id = idinfo.toInt();
			//isCli_addTo_qmObjQ(idInfo);


			pq_contact->append(fi);
#if  0
			if (!pSyr.isEmpty())
			{
				//if (grpInfoMap.isEmpty() || grpInfoMap.value(pQMem->messengerInfo.idInfo.ui64Id).isEmpty())
				{
					//grpInfoMap.insert(pQMem->messengerInfo.idInfo.ui64Id, pSyr);
					QTreeWidgetItem* pChild = new QTreeWidgetItem();
					//添加子节点 
					pChild->setData(0, Qt::UserRole, 1);
					WinObjUser user;
					user.idinfo = idinfo;
					user.name = pSyr;
					user.dw = pdw;
					user.bm = pBm;
					user.dataType = 3;//好友
					pChild->setData(0, Qt::UserRole + 1, QVariant::fromValue(user));
					WinContactItem* pContactItem = new WinContactItem(user.idinfo, ui->treeWidgetContacts);
					QPixmap pix1(":/Resources/Images/WinMain/person.png");
					pContactItem->setHeadPixmap(pix1);
					pContactItem->setUserName(pSyr);
					pContactItem->setSignName(pdw + " " + pBm);
					m_pRootFriendItemFriend->addChild(pChild);
					ui->treeWidgetContacts->setItemWidget(pChild, 0, pContactItem);
				}
			}
#endif
		}
		else if (pQMem->messengerInfo.uiType == CONST_objType_imGrp)
		{
			if (!g_dbFuncs.pf_bGetImGrpInfoBySth(pDb, CONST_dbType_myDb, pQMem->messengerInfo.misServName, &pQMem->messengerInfo.idInfo, &grp_info))
			{
				memset(&grp_info, 0, sizeof(grp_info));
			};
			_sntprintf(grpIdBuf, mycountof(grpIdBuf), _T("%I64u"), grp_info.idInfo.ui64Id);
			QString pdw = QString::fromWCharArray(grp_info.name).trimmed();
			QString idinfo = QString::fromWCharArray(tBuf);
			QString idInfo_creator = QString::number(grp_info.idInfo_creator.ui64Id);// :fromWCharArray(grpIdBuf);
			//if (!pdw.isEmpty())
			{
				if (pdw.isEmpty()) {
					pdw = QString::number(pQMem->messengerInfo.idInfo.ui64Id);
				}

				//
				if (grp_info.idInfo_creator.ui64Id) {
					myFriendInfo  fi;
					fi.userId = pQMem->messengerInfo.idInfo.ui64Id;
					fi.grpName = pdw;
					pq_tmpGrp->append(fi);
				}
				else {
					myFriendInfo fi;
					fi.userId = pQMem->messengerInfo.idInfo.ui64Id;
					fi.grpName = pdw;
					pq_grp->append(fi);
				}

				//if (grpInfoMap.isEmpty() || grpInfoMap.value(grp_info.idInfo.ui64Id).isEmpty())
				{
					//grpInfoMap.insert(grp_info.idInfo.ui64Id, pdw);
#if  0
					if (!idInfo_creator.contains("0"))
					{
						QTreeWidgetItem* pChild = new QTreeWidgetItem();
						//添加子节点
						pChild->setData(0, Qt::UserRole, 1);
						WinObjUser user;
						user.idinfo = idinfo;
						user.name = pdw;
						user.dataType = 2;//临时组
						pChild->setData(0, Qt::UserRole + 1, QVariant::fromValue(user));
						WinContactItem* pContactItem = new WinContactItem(user.idinfo, ui->treeWidgetContacts);
						pContactItem->setHeadPixmap(QPixmap(":/Resources/Images/WinMain/tmp_group.png"));
						pContactItem->setUserName(pdw);
						m_pRootFriendItemTemp->addChild(pChild);
						ui->treeWidgetContacts->setItemWidget(pChild, 0, pContactItem);
					}
					else
					{
						QTreeWidgetItem* pChild = new QTreeWidgetItem();
						//添加子节点
						pChild->setData(0, Qt::UserRole, 1);
						WinObjUser user;
						user.idinfo = idinfo;
						user.name = pdw;
						user.dataType = 1;//群组
						pChild->setData(0, Qt::UserRole + 1, QVariant::fromValue(user));
						WinContactItem* pContactItem = new WinContactItem(user.idinfo, ui->treeWidgetContacts);
						pContactItem->setHeadPixmap(QPixmap(":/Resources/Images/WinMain/group.png"));
						pContactItem->setUserName(pdw);
						m_pRootFriendItemGroup->addChild(pChild);
						ui->treeWidgetContacts->setItemWidget(pChild, 0, pContactItem);
					}
#endif

				}
			}
		}
	}
}

//修改状态
void WinContactsList::updateContactItem(qint64 idInfo , unsigned  short status) {
	QTreeWidgetItemIterator it(ui->treeWidgetContacts);
	while (*it)
	{
		//QTreeWidgetItem是否满足条件---这里的条件可以自己修改
		QVariant variant = (*it)->data(0, Qt::UserRole + 1);
		WinObjUser user = variant.value<WinObjUser>();
		if (user.idinfo.toInt() == idInfo)
		{
			(*it)->setHidden(false);
			QTreeWidgetItem* item = *it;
			WinContactItem* winItem = (WinContactItem*)ui->treeWidgetContacts->itemWidget(item, 0);
			//QPixmap pix1(":/Resources/Images/WinMain/person.png");

			if (status != CONST_usRunningStatus_online) {
				winItem->isOnLine(false);
			}
			else {
				winItem->isOnLine(true);
			}
		}
		++it;
	}
}

void WinContactsList::wheelEvent(QWheelEvent* event) 
{
	
}

void WinContactsList::delTmpContactItem(QString idInfo) {
	QTreeWidgetItemIterator it(ui->treeWidgetContacts);
	while (*it)
	{
		//QTreeWidgetItem是否满足条件---这里的条件可以自己修改
		QVariant variant = (*it)->data(0, Qt::UserRole + 1);
		WinObjUser user = variant.value<WinObjUser>();
		if (user.idinfo == idInfo)
		{
			(*it)->setHidden(false);
			QTreeWidgetItem* item = *it;
			delete item;//删除子节点
			//显示父节点
			//while (item->parent())
			//{

			//	item->parent()->setHidden(false);
			//	
			//	
			//	//item = item->parent();
			//}
		}
		//else
		//{
		//	//不满足满足条件先隐藏，它的子项目满足条件时会再次让它显示
		//	(*it)->setHidden(true);
		//}
		++it;
	}
}


//
int WinContactsList::onLineStatusUp()
{
	//
	int  count = ui->treeWidgetContacts->topLevelItemCount();
	QY_MC* pQyMc = QY_GET_GBUF();
	QTreeWidgetItem* child;
	QY_MESSENGER_ID  idInfo;

	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return  -1;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt)  return  -1;

	int childCount = this->m_pRootFriendItemFriend->childCount();
	int  i;
	int height_s = this->height();
	for (i = 0; i < childCount; i++) {
		QTreeWidgetItem* item = this->m_pRootFriendItemFriend->child(i);
		QRect  rc = ui->treeWidgetContacts->visualItemRect(item);
	

		if (rc.bottom() < height_s && rc.top() >= 0) {
			//
		   /* WinContactItem* winItem = (WinContactItem * )ui->treeWidgetContacts->itemWidget(item , 0 );
			QString str = winItem->getName();*/
			QVariant variant = item->data(0, Qt::UserRole + 1);
			WinObjUser user = variant.value<WinObjUser>();
			//qDebug() << "item[" << i << "]," << rc.x() << "," << rc.y() << "," << rc.top() << "," << rc.bottom() << "," << user.idinfo;
			idInfo.ui64Id = user.idinfo.toInt();
			postRecentFriend(pMisCnt, idInfo, 0);
			
			

			/*TCHAR  tBuf[128];
			_sntprintf(tBuf, mycountof(tBuf), _T("item[%d],%d,%d,%d,%d,%d"), i, rc.x(), rc.y(), rc.top(), rc.bottom() , user.idinfo);
			traceLog(tBuf);*/
		}
		


		//
		continue;

	}
	pMisCnt->refreshRecentFriends.bRefreshAtOnce = true;
	//
	return  0;
}


//
void WinContactsList::fillGrp(QList<myFriendInfo>& pq)
{
	for (size_t i = 0; i < pq.size(); i++)
	{
		{
			QTreeWidgetItem* pChild = new QTreeWidgetItem();
			//添加子节点
			pChild->setData(0, Qt::UserRole, 1);
			WinObjUser user;
			user.idinfo = QString::number(pq[i].userId);
			user.name = pq[i].grpName;
			user.dataType = 1;//群组
			pChild->setData(0, Qt::UserRole + 1, QVariant::fromValue(user));
			WinContactItem* pContactItem = new WinContactItem(user.idinfo, ui->treeWidgetContacts);
			pContactItem->setHeadPixmap(QPixmap(":/Resources/Images/WinMain/group.png"));
			pContactItem->setUserName(pq[i].grpName);
			m_pRootFriendItemGroup->addChild(pChild);
			ui->treeWidgetContacts->setItemWidget(pChild, 0, pContactItem);
		}

	}

	return;
}



void WinContactsList::fillTmpGrp(QList<myFriendInfo>& pq)
{
	for (size_t i = 0; i < pq.size(); i++)
	{
		{
			QTreeWidgetItem* pChild = new QTreeWidgetItem();
			//添加子节点
			pChild->setData(0, Qt::UserRole, 1);
			WinObjUser user;
			user.idinfo = QString::number(pq[i].userId);
			user.name = pq[i].grpName;
			user.dataType = 2;//临时组
			pChild->setData(0, Qt::UserRole + 1, QVariant::fromValue(user));
			WinContactItem* pContactItem = new WinContactItem(user.idinfo, ui->treeWidgetContacts);
			pContactItem->setHeadPixmap(QPixmap(":/Resources/Images/WinMain/tmp_group.png"));
			pContactItem->setUserName(pq[i].grpName);
			m_pRootFriendItemTemp->addChild(pChild);
			ui->treeWidgetContacts->setItemWidget(pChild, 0, pContactItem);
		}
	}
}


void WinContactsList::fillContact(QList<myFriendInfo>& pq)
{
	for (size_t i = 0; i < pq.size(); i++)
	{
		{
			//grpInfoMap.insert(pQMem->messengerInfo.idInfo.ui64Id, pSyr);
			QTreeWidgetItem* pChild = new QTreeWidgetItem();
			//添加子节点 
			pChild->setData(0, Qt::UserRole, 1);
			WinObjUser user;
			user.idinfo = QString::number(pq[i].userId);
			user.name = pq[i].syr;
			user.dw = pq[i].dw;
			user.bm = pq[i].bm;
			user.dataType = 3;//好友
			pChild->setData(0, Qt::UserRole + 1, QVariant::fromValue(user));
			WinContactItem* pContactItem = new WinContactItem(user.idinfo, ui->treeWidgetContacts);
			QPixmap pix1(":/Resources/Images/WinMain/person.png");
			pContactItem->setHeadPixmap(pix1);
			pContactItem->setUserName(pq[i].syr);
			pContactItem->setSignName(pq[i].dw + " " + pq[i].bm);
			m_pRootFriendItemFriend->addChild(pChild);
			ui->treeWidgetContacts->setItemWidget(pChild, 0, pContactItem);
		}
	}
}



/// <summary>
/// 
/// </summary>
/// <param name="id"></param>
void WinContactsList::addTmpContactItem(int id)
{
	QY_MESSENGER_ID idinfo;
	unsigned  int  uiObjType = 0;

	TCHAR grpName_from[128] = _T("");
	TCHAR srcName_from[128] = _T("");
	QString username;
	idinfo.ui64Id = id;
	getTalkerDesc(idinfo, &uiObjType, grpName_from, mycountof(grpName_from), mynull, mynull, 0, mynull, 0, srcName_from,mycountof(srcName_from));
	
	
	if (uiObjType == CONST_objType_imGrp) {
		username = QString::fromStdWString(grpName_from);
	}
	else {
		username = QString::fromStdWString(srcName_from);
	}

	QTreeWidgetItem* pChild = new QTreeWidgetItem();



	//添加子节点
	pChild->setData(0, Qt::UserRole, 1);
	WinObjUser user;
	user.idinfo = QString::number(id);
	user.name = username;
	user.dataType = 2;//临时组
	pChild->setData(0, Qt::UserRole + 1, QVariant::fromValue(user));
	WinContactItem* pContactItem = new WinContactItem(user.idinfo, ui->treeWidgetContacts);
	pContactItem->setHeadPixmap(QPixmap(":/Resources/Images/WinMain/tmp_group.png"));
	pContactItem->setUserName(username);
	m_pRootFriendItemTemp->addChild(pChild);
	ui->treeWidgetContacts->setItemWidget(pChild, 0, pContactItem);
}

#if  0
int tmpHanlder_getContactList(void* p0, void* p1, void* p2)
{
	int  iRet = -1;
	COMMON_PARAM* pCommonParam = (COMMON_PARAM*)p0;
	//
	CMyDb* pDb = (CMyDb*)pCommonParam->p0;
	//  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
	//HWND				hListCtrl = (HWND)pCommonParam->p1;
	//if (!hListCtrl)  goto  errLabel;
	int				iItem = (int)pCommonParam->p2;
	//
	BOOL				bUnprocedOnly = (BOOL)p1;
	//
	QMEM_qyImObj* pQMem = (QMEM_qyImObj*)p2;

	int				index = 0;
	QY_MC* pQyMc = QY_GET_GBUF();

	QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable);

	QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  goto  errLabel;
	QM_dbFuncs& g_dbFuncs = *pDbFuncs;

	if (pQMem->messengerInfo.iStatus == CONST_qyStatus_ok)
	{
		winCl->showContactList(pDb, pQMem);
	}
	iRet = 0;
errLabel:
	return  iRet;
}
#endif

//
int tmpHandler_getContactList_new(void* p0, void* p1, void* p2)
{
	int  iRet = -1;
	COMMON_PARAM* pCommonParam0 = (COMMON_PARAM*)p0;
	//
	CMyDb* pDb = (CMyDb*)pCommonParam0->p0;
	//  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
	//HWND				hListCtrl = (HWND)pCommonParam->p1;
	//if (!hListCtrl)  goto  errLabel;
	int				iItem = (int)pCommonParam0->p2;
	//
	//BOOL				bUnprocedOnly = (BOOL)p1;
	COMMON_PARAM* pCommonParam1 = (COMMON_PARAM*)p1;
	QList<myFriendInfo>* pq_grp = (QList<myFriendInfo>*)pCommonParam1->p0;
	QList<myFriendInfo>* pq_tmpGrp = (QList<myFriendInfo>*)pCommonParam1->p1;
	QList<myFriendInfo>* pq_contact = (QList<myFriendInfo>*)pCommonParam1->p2;


	//
	QMEM_qyImObj* pQMem = (QMEM_qyImObj*)p2;

	int				index = 0;
	QY_MC* pQyMc = QY_GET_GBUF();

	QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable);

	QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  return -1;// goto  errLabel;
	QM_dbFuncs& g_dbFuncs = *pDbFuncs;

	if (pQMem->messengerInfo.iStatus == CONST_qyStatus_ok)
	{
		winCl->addToContactList(pDb, pCommonParam1,  pQMem);
	}
	iRet = 0;
errLabel:
	return  iRet;
}


//
int q_grpListSort(const myFriendInfo& info1, const myFriendInfo& info2)
{
	int iRet = _tcsicmp((wchar_t*)(info1.grpName).utf16(), (wchar_t*)(info2.grpName).utf16());  //升序排列  
	if (iRet < 0) return true;
	return false;

	//return info1->posid < info2->posid;     //降序排列  
}

int q_contactListSort(const myFriendInfo& info1, const myFriendInfo& info2)
{
	QString info_start = info1.dw + info1.bm + info1.syr + QString::number(info1.userId);
	QString info_end = info2.dw + info2.bm + info2.syr + QString::number(info2.userId);
	 //= (wchar_t*)(info1.dw).utf16() + (wchar_t*)(info1.bm).utf16();

	int iRet = _tcsicmp((wchar_t*)(info_start).utf16(), (wchar_t*)(info_end).utf16());  //升序排列  
	if (iRet < 0) return true;
	return false;

	//return info1->posid < info2->posid;     //降序排列  
}

//
#include	<algorithm>


int WinContactsList::toContactList()
{
	int  iRet = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	int	 iServiceId = CONST_qyServiceId_mis;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return  -1;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt)  return  -1;
	//
	if (pQyMc->cfg.db.iDbType != CONST_dbType_myDb)
	{
		return  -1;
	}
	HTREEITEM				tmphtItem = NULL;
	TCHAR					displayName[512] = _T("");
	int						iObjId = 0;
	int						nImage, nSelectedImage;
	int						iTopFieldId = 0;
	char					topLevelColName[128] = "'";
	char* p = NULL;
	int						i;
	int						iObjType = 0;
	TCHAR					tBuf[1024];
	char					buf[256];

	QY_OBJ_DB* pObjDb = getProcedObjDb(pQyMc, 0, pQyMc->iDsnIndex_mainSys);
	if (!bObjDbAvail(pObjDb)) return -1;
	//
	CMyDb* pDb = (CMyDb*)pObjDb->pDb;
	int cnt = 0;
	COMMON_PARAM	commonParam0;
	MACRO_makeCommonParam3(pDb, 0, (void*)cnt, commonParam0);
	QList<myFriendInfo> q_grp;
	QList <myFriendInfo>q_tmpGrp;
	QList<myFriendInfo>q_contact;
	COMMON_PARAM commonParam1;
	MACRO_makeCommonParam3(&q_grp, &q_tmpGrp, &q_contact, commonParam1);

	//qTraverse(pDb->m_var.pQ_qyImObjTab, getContactList, &commonParam0, NULL);
	qTraverse(pDb->m_var.pQ_qyImObjTab, tmpHandler_getContactList_new, &commonParam0, &commonParam1);

	//
	//群组排序
	std::sort(q_grp.begin(), q_grp.end(), q_grpListSort);
	std::sort(q_tmpGrp.begin(), q_tmpGrp.end(), q_grpListSort);
	//联系人排序

	std::sort(q_contact.begin(), q_contact.end(), q_contactListSort);
	//
	fillGrp(q_grp);
	fillTmpGrp(q_tmpGrp);
	fillContact(q_contact);

	//
	this->m_pRootFriendItemFriend->setExpanded(true);


	//
	iRet = 0;
errLabel:
	return  iRet;
}

//联系人的树控件的信号槽
void WinContactsList::on_treeWidgetContacts_itemExpanded(QTreeWidgetItem* item)
{
	bool bIsChild = item->data(0, Qt::UserRole).toBool();
	if (!bIsChild)
	{
		WinRootContatItem* prootItem = dynamic_cast<WinRootContatItem*>(ui->treeWidgetContacts->itemWidget(item, 0));
		if (prootItem)
		{
			prootItem->setExpanded(true);
		}
	}
}

void WinContactsList::on_treeWidgetContacts_itemCollapsed(QTreeWidgetItem* item)
{
	bool bIsChild = item->data(0, Qt::UserRole).toBool();
	if (!bIsChild)
	{
		WinRootContatItem* prootItem = dynamic_cast<WinRootContatItem*>(ui->treeWidgetContacts->itemWidget(item, 0));
		if (prootItem)
		{
			prootItem->setExpanded(false);
		}
	}
}

void WinContactsList::on_treeWidgetContacts_itemClicked(QTreeWidgetItem* item, int column)
{
	
#if 10
	bool bIsChild = item->data(0, Qt::UserRole).toBool();
	if (!bIsChild)
	{
		item->setExpanded(!item->isExpanded());
	}
	else
	{
		QVariant variant = item->data(0, Qt::UserRole + 1);
		WinObjUser user = variant.value<WinObjUser>();
		emit toShowContactsInfo(user);
	}
	onLineStatusUp();
#endif
}



//
void WinContactsList::on_treeWidgetContacts_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
	//
	if (!current)  return;

	QTreeWidgetItem* item = current;

	bool bIsChild = item->data(0, Qt::UserRole).toBool();
	if (!bIsChild)
	{
		//item->setExpanded(!item->isExpanded());
	}
	else
	{
		QVariant variant = item->data(0, Qt::UserRole + 1);
		WinObjUser user = variant.value<WinObjUser>();
		emit toShowContactsInfo(user);
	}

}
