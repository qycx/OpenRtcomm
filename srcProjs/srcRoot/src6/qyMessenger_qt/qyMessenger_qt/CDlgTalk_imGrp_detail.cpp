#include "CDlgTalk_imGrp_detail.h"
#include "WinRuleSet.h"

CDlgTalk_imGrp_detail* cDlgTalk_imGrp_detail = nullptr;
CDlgTalk_imGrp_detail::CDlgTalk_imGrp_detail(QWidget* parent)
	: QWidget(parent), ui(new Ui::CDlgTalk_imGrp_detail)
{
	ui->setupUi(this);
	cDlgTalk_imGrp_detail = this;
	this->setObjectName("ContactsGroupInfo");
	initControl();
}

CDlgTalk_imGrp_detail::~CDlgTalk_imGrp_detail()
{
	delete ui;
	if (grpWidget)
	{
		delete grpWidget;
		grpWidget = nullptr;
	}
}

//显示群组信息
void CDlgTalk_imGrp_detail::ShowContactsGroupInfo(WinObjUser user)
{
	if (user.dataType != 3)
	{
		if (user.name == "null")
		{
			ui->centerWidget->hide();
			ui->bottomWidget->hide();
			return;
		}
		ui->centerWidget->show();
		ui->bottomWidget->show();
		//
		//if (ui->gridLayout->count() > 0)
		{
			QLayoutItem* child;
			while ((child = ui->gridLayout->takeAt(0)) != 0)
			{
				if (child->widget())
				{
					child->widget()->setParent(NULL);
					//
					child->widget()->close();
				}
				//
				delete child;
			}
		}
		//
		m_curUser.idinfo = user.idinfo;
		m_curUser.name = user.name;
		m_curUser.bm = user.bm;
		m_curUser.dw = user.dw;
		m_curUser.dataType = user.dataType;
		//
		toGetGroupByIdInfo(user.idinfo.toInt(), user.name);
	}
}

void CDlgTalk_imGrp_detail::initControl()
{
	grpWidget = new QWidget(this);
	grpWidget->setObjectName("grpWidget");
	grpWidget->setLayout(ui->gridLayout);
	ui->scrollArea->setWidget(grpWidget);
	ui->scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{width:10px;}");
	ui->scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal{height:10px;}");


	QFile file(":/Resources/QSS/CDlgTalk_imGrp_detail.css");
	file.open(QFile::ReadOnly);
	if (file.isOpen())
	{
		this->setStyleSheet("");
		QString qsstyleSheet = QLatin1String(file.readAll());
		this->setStyleSheet(qsstyleSheet);
	}
	file.close();
	//ui->labelGroupInfo->setVisible(false);
}

void CDlgTalk_imGrp_detail::on_btnSendMsg_clicked()
{
	emit toSendMsg(m_curUser);
}

void CDlgTalk_imGrp_detail::on_benSendMeeting_clicked()
{
	//emit toSendMeeting(m_curUser);

	QY_MESSENGER_ID idInfo;
	idInfo.ui64Id = m_curUser.idinfo.toInt();
	talk_doAv((HWND)this->winId(), idInfo,false);
}

void CDlgTalk_imGrp_detail::on_setBtn_clicked() {
	QY_MESSENGER_ID  idInfo;
	idInfo.ui64Id = this->m_curUser.idinfo.toInt();
	
	WinRuleSet::showDialog(this,idInfo.ui64Id);
}


void CDlgTalk_imGrp_detail::showGroupContactList(CMyDb* pDb, IM_GRP_MEM* pQMem, int64_t* idinfo)
{
	QY_MC* pQyMc = QY_GET_GBUF();
	MY_REG_DESC					desc;
	QY_MESSENGER_REGINFO		regInfo;
	memset(&regInfo, 0, sizeof(regInfo));
	QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
	QM_dbFuncs& g_dbFuncs = *pDbFuncs;
	TCHAR	talkerDesc[128] = _T("");
	if (pQMem->iStatus == CONST_qyStatus_ok)
	{
		if (pQMem->idInfo_grp.ui64Id == (*idinfo))
		{
			LPCTSTR misServName = _T("");
			if (!g_dbFuncs.pf_bGetMessengerRegInfoBySth(pDb, CONST_dbType_myDb, getResTable(0, &pQyMc->cusRes, CONST_resId_fieldIdTable), CONST_tabName_qyImObjRegInfoTab, misServName, &pQMem->idInfo_mem, 0, &regInfo))
			{
				memset(&regInfo, 0, sizeof(regInfo));
			}
			regInfo2Desc(0, &regInfo, &desc, talkerDesc, mycountof(talkerDesc), NULL, 0);
			QString pDw = QString::fromWCharArray(desc.pDw).trimmed();
			QString pBm = QString::fromWCharArray(desc.pBm).trimmed();
			QString pSyr = QString::fromWCharArray(desc.pSyr).trimmed();
			//
			int rows = ui->gridLayout->count();
			//
			WinContactItem* pContactItem = new WinContactItem(QString::number(pQMem->idInfo_grp.ui64Id), ui->centerWidget);
			pContactItem->setHeadPixmap(QPixmap(":/Resources/Images/WinMain/person.png"));
			pContactItem->setUserName(pSyr + " (" + QString::number(pQMem->idInfo_mem.ui64Id) + ")");
			pContactItem->setSignName(pDw + " " + pBm);
			ui->gridLayout->addWidget(pContactItem, rows / 3, rows % 3, Qt::AlignLeft);
		}
	}
}

int  getGroupByIdInfo(void* p0, void* p1, void* p2)
{
	int  iRet = -1;
	COMMON_PARAM* pCommonParam = (COMMON_PARAM*)p0;
	CMyDb* pDb = (CMyDb*)pCommonParam->p0;
	int64_t* idinfo = (int64_t*)p1;
	IM_GRP_MEM* pQMem = (IM_GRP_MEM*)p2;
	int				index = 0;
	QY_MC* pQyMc = QY_GET_GBUF();
	QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable);
	QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  goto  errLabel;
	if (pQMem->iStatus == CONST_qyStatus_ok)
	{
		cDlgTalk_imGrp_detail->showGroupContactList(pDb, pQMem, idinfo);
	}
	iRet = 0;
errLabel:
	return  iRet;
}

int CDlgTalk_imGrp_detail::toGetGroupByIdInfo(int64_t idinfo, QString name)
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
	QY_OBJ_DB* pObjDb = getProcedObjDb(pQyMc, 0, pQyMc->iDsnIndex_mainSys);
	if (!bObjDbAvail(pObjDb)) return -1;
	//
	CMyDb* pDb = (CMyDb*)pObjDb->pDb;
	int cnt = 0;
	COMMON_PARAM	commonParam;
	MACRO_makeCommonParam3(pDb, 0, (void*)cnt, commonParam);
	qTraverse(pDb->m_var.pQ_qyImGrpMemTab, getGroupByIdInfo, &commonParam, &idinfo);
	ui->labelGroupInfo->setFont(QFont("SimHei", 16, 10));
	ui->labelGroupInfo->setText(QString("%1(%2)").arg(name).arg(idinfo));
	iRet = 0;
errLabel:
	return  iRet;
}
