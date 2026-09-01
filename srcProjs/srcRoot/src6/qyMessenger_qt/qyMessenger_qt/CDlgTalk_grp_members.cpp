#include	"stdafx.h"

#define  __noDbg_new__


#include "CDlgTalk_grp_members.h"
#include <qtablewidget.h>
#include <QtCore/qmath.h>
#include <QPainter>

#include	"qyMcMainCommon_qt.h"
#include	"ctxQmc.h"
#include	"myDb.h"
#include "CMainFrame.h"
#include <ctxQmc_qt.h>
#include <dlgtalkproc.h>
#include <defineModels.h>
#include <WinRuleSet.h>

#define SHADOW_WIDTH 6 // 阴影边框宽度;

namespace {
	CDlgTalk_grp_members* dlg = nullptr;
}



int  tmpHandler_printImGrpMemList_grpMembers(void* p0, void* p1, void* p2)
{
	int  iRet = -1;
	COMMON_PARAM* pCommonParam = (COMMON_PARAM*)p0;
	COMMON_PARAM* pCommonParam1 = (COMMON_PARAM*)p1;

	//
	CMyDb* pDb = (CMyDb*)pCommonParam->p0;
	//  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
	//HWND				hListCtrl = (HWND)pCommonParam->p1;
	//if (!hListCtrl)  goto  errLabel;
	int				iItem = (int)pCommonParam->p2;
	//
	//BOOL				bUnprocedOnly = (BOOL)p1;
	CDlgTalk_grp_members* pDlg = (CDlgTalk_grp_members*)pCommonParam1->p0;
	QString* pPeer_id = (QString*)pCommonParam1->p1;
	QList<MemberInfo>* pMemList = (QList<MemberInfo>*)pCommonParam1->p2;
#if  10

	//
	IM_GRP_MEM* pQMem = (IM_GRP_MEM*)p2;
	int				index = 0;
	QY_MC* pQyMc = QY_GET_GBUF();


	QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  return -1;// goto  errLabel;
	QM_dbFuncs& g_dbFuncs = *pDbFuncs;


	QY_MESSENGER_REGINFO		regInfo;
	MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable);

	memset(&regInfo, 0, sizeof(regInfo));
	
	/*DLG_TALK_var* pm_var = (DLG_TALK_var*)pDLG_TALK_var;
	pm_var = cdlgTalkqt->get_pm_var();*/
	MC_VAR_isCli* pProcInfo; pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt; pMisCnt = pProcInfo->getMisCntByName(_T(""));


	//  if  (  pQMem->uiType  ==  CONST_objType_imGrp  )
	{
#if  0
		_sntprintf(tBuf, mycountof(tBuf), _T(""));
		index = 0;  myListCtrl_InsertItem(hListCtrl, iItem, tBuf);

		_sntprintf(tBuf, mycountof(tBuf), _T("%s"), qyGetDesByType1(getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable), CONST_objType_imGrp));
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

		_sntprintf(tBuf, mycountof(tBuf), _T("%I64u"), pQMem->idInfo_grp.ui64Id);
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

		//
		IM_GRP_INFO  grpInfo;
		if (!g_dbFuncs.pf_bGetImGrpInfoBySth(pDb, pQyMc->cfg.db.iDbType, _T(""), &pQMem->idInfo_grp, &grpInfo))  memset(&grpInfo, 0, sizeof(grpInfo));

		_sntprintf(tBuf, mycountof(tBuf), _T("%s"), grpInfo.name);
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

		_sntprintf(tBuf, mycountof(tBuf), _T("%I64u"), pQMem->idInfo_mem.ui64Id);
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

		if (!g_dbFuncs.pf_bGetMessengerRegInfoBySth(pDb, CONST_dbType_myDb, getResTable(0, &pQyMc->cusRes, CONST_resId_fieldIdTable), CONST_tabName_qyImObjRegInfoTab, pQMem->misServName, &pQMem->idInfo_mem, 0, &regInfo)) {
			memset(&regInfo, 0, sizeof(regInfo));
		}

		MY_REG_DESC  desc;
		regInfo2Desc(0, &regInfo, &desc, NULL, 0, NULL, 0);

		_sntprintf(tBuf, mycountof(tBuf), _T("%s"), desc.pDw);
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);
		_sntprintf(tBuf, mycountof(tBuf), _T("%s"), desc.pBm);
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);
		_sntprintf(tBuf, mycountof(tBuf), _T("%s"), desc.pSyr);
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

		//
		_sntprintf(tBuf, mycountof(tBuf), _T("%s"), qyGetDesByType1(getResTable(0, &pQyMc->cusRes, CONST_resId_imGrpMemRoleTable), pQMem->iRole));
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);


		//
		_sntprintf(tBuf, mycountof(tBuf), _T(""));
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);


		_sntprintf(tBuf, mycountof(tBuf), _T("%s"), (pQMem->iStatus ? _T("Del") : _T("Ok")));
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);
#endif
		
		
		//
		traceLog((TCHAR*)_T("grp %I64u, mem %I64u"), pQMem->idInfo_grp.ui64Id, pQMem->idInfo_mem.ui64Id);

		if (QString::number(pQMem->idInfo_grp.ui64Id)== *pPeer_id) {

			TCHAR grpName_mem[125];
			TCHAR srcName_mem[125];
			TCHAR dw[125];
			TCHAR bm[125];
			

			getTalkerDesc(pQMem->idInfo_mem, NULL, grpName_mem, mycountof(grpName_mem), mynull, dw, mycountof(dw), bm, mycountof(bm), srcName_mem, mycountof(srcName_mem));
			MemberInfo data;

			QString mem_name = QString::fromStdWString(srcName_mem);// +" " + QString::number(pQMem->idInfo_mem.ui64Id);
			QString mem_dw = QString::fromStdWString(dw);
			QString mem_bm = QString::fromStdWString(bm);
			int row = pDlg->ui.tableWidget->rowCount();
			pDlg->ui.tableWidget->insertRow(row);
			//QTableWidgetItem* item = new QTableWidgetItem;
			if (!mem_name.isNull()) {

				data.name = mem_dw + " " + mem_bm + " " + mem_name;

			}
			else {

				data.name = " (" + QString::number(pQMem->idInfo_mem.ui64Id) + ")";

			}
			data.userId = QString::number(pQMem->idInfo_mem.ui64Id);
			if (pMisCnt->idInfo.ui64Id == pQMem->idInfo_mem.ui64Id) {
				data.status = u8"我";
				
			}

			pMemList->append(data);
			
		}
		
	}

#endif

	iRet = 0;
errLabel:
	return  iRet;
}










CDlgTalk_grp_members::CDlgTalk_grp_members(QWidget *parent)
	: WinBaseDialog(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(this->windowFlags() | Qt::Dialog);
	this->setAttribute(Qt::WA_DeleteOnClose);

	connect(ui.tableWidget, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(slot_onTableClicked(int, int)));

	ui.tableWidget->setVerticalScrollMode(QTableWidget::ScrollPerPixel);
	ui.tableWidget->setFocusPolicy(Qt::NoFocus);
	ui.tableWidget->horizontalHeader()->setFixedHeight(40);
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	//ui.tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
	ui.tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
	ui.tableWidget->setIconSize(QSize(50, 50));
	//ui.tableWidget->setFrameShape(QFrame::NoFrame); //设置无边框
	ui.tableWidget->setStyleSheet("selection-background-color: rgba(82,115,204,50%)");
	ui.tableWidget->setShowGrid(false); //设置不显示格子线
	ui.tableWidget->verticalHeader()->setVisible(false);
	ui.tableWidget->verticalHeader()->setDefaultSectionSize(50); //设置行高
	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeMode::Fixed);
	ui.tableWidget->setColumnWidth(0, 300);
	ui.tableWidget->setColumnWidth(1, 170);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeMode::Interactive);

	//ui.tableWidget->setColumnWidth(1, 380);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeMode::Fixed);
	ui.tableWidget->setColumnWidth(2, 50);

	//

	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeMode::Interactive);
	
	

	//
	HWND  m_hWnd = (HWND)this->winId();

	//
	int  ii = 0;
	
	

}



void CDlgTalk_grp_members::getDialog(QWidget* parent) {
	if (!dlg)
	{
		dlg = new CDlgTalk_grp_members(parent);
	}
}

void CDlgTalk_grp_members::showWnd() {
	if (!dlg) return;
	dlg->show();
	dlg->activateWindow();
	
}


void CDlgTalk_grp_members::slot_onTableClicked(int row, int col) {
	
	//QString infoId = getCurrentId();
	 if (ui.tableWidget->rowCount() == 0)
    {
        return ;
    }
    //int row = ui.tableWidget->currentRow();
	QString infoId = ui.tableWidget->item(row, 1)->text();
    
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	HWND  hMainWnd = pQyMc->gui.hMainWnd;
	CMainFrame* pMainWnd = (CMainFrame*)getObjAddr(hMainWnd);


	WinObjUser user;
	user.idinfo = infoId;
	pMainWnd->cut_talk_list(user);
	

}

int subDevListSort(const MemberInfo& info1, const MemberInfo& info2)
{
	int iRet = _tcsicmp((wchar_t*)(info1.name).utf16(), (wchar_t*)(info2.name).utf16());  //升序排列  
	if (iRet < 0) return true;
	return false;

	//return info1->posid < info2->posid;     //降序排列  
}



void CDlgTalk_grp_members::setContent( QString peer_id ) {

	QY_MC* pQyMc = QY_GET_GBUF();
	//
	QY_OBJ_DB* pObjDb = getProcedObjDb(pQyMc, 0, pQyMc->iDsnIndex_mainSys);
	if (!bObjDbAvail(pObjDb))  return;
	QString* pPeer_id = &peer_id;
	QList<MemberInfo> memList;
	QList<MemberInfo>* pMemList = &memList;
	//	//
	CMyDb* pDb = (CMyDb*)pObjDb->pDb;
	int cnt = 0;
	COMMON_PARAM	commonParam;
	COMMON_PARAM    commonParam1;
	//  MACRO_makeCommonParam3(  pDb,  pListCtrl,  (  void  *  )cnt,  commonParam  );
	MACRO_makeCommonParam3(pDb, 0, (void*)cnt, commonParam);
	MACRO_makeCommonParam3(dlg, pPeer_id, pMemList, commonParam1);
	//




	dlg->clearTableWidget(dlg->ui.tableWidget);
	qTraverse(pDb->m_var.pQ_qyImGrpMemTab, tmpHandler_printImGrpMemList_grpMembers, &commonParam, &commonParam1);


	std::sort(memList.begin(), memList.end(), subDevListSort);



	for (int i = 0; i <= memList.size() - 1; i++) {
		QTableWidgetItem* item = new QTableWidgetItem;
		item->setSizeHint(QSize(50, 50));
		item->setIcon(QIcon(":/Resources/Images/WinMain/person.png"));
		item->setText(memList[i].name);
		item->setText(memList[i].name);
		dlg->ui.tableWidget->setItem(i, 0, item);

		dlg->ui.tableWidget->setItem(i, 1, new QTableWidgetItem( memList[i].userId ));
		dlg->ui.tableWidget->setItem(i, 2, new QTableWidgetItem( memList[i].status ));
	}

	int cols = dlg->ui.tableWidget->columnCount();
	int rows = dlg->ui.tableWidget->rowCount();

	

#if  10
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			QTableWidgetItem* pItem = dlg->ui.tableWidget->item(i, j);
			if (pItem) {
			//	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			}
		}
	}
#endif


	int  ii = 0;
}


CDlgTalk_grp_members::~CDlgTalk_grp_members()
{
	//
	HWND  m_hWnd = (HWND)this->winId();


	//
	dlg = nullptr;
}

void CDlgTalk_grp_members::closeDialog() {
	if (dlg) {
		dlg->close();
	}
}

void CDlgTalk_grp_members::closeEvent(QCloseEvent* ev)
{
	this->hide();
	ev->accept();
}

void CDlgTalk_grp_members::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH), QBrush(Qt::white));

	QColor color(0, 0, 0, 10);
	for (int i = 0; i < SHADOW_WIDTH; i++)
	{
		color.setAlpha(120 - qSqrt(i) * 40);
		painter.setPen(color);
		// 方角阴影边框;
	 // painter.drawRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2);
		// 圆角阴影边框;
		painter.drawRoundedRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2, 4, 4);
	}
}
void CDlgTalk_grp_members::clearTableWidget(QTableWidget* table)
{
	while (table->rowCount() > 0)
	{
		table->removeRow(0);
	}
}