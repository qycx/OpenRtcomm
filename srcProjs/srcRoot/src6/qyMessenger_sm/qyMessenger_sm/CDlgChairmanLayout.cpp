#include	<tchar.h>
#include "CDlgChairmanLayout.h"

//
//#include <qdesktopwidget.h>
#include	<qscreen.h>

#include	"qyMcMainCommon_qt.h"
#include	"ctxQmc_sm.h"
#include	"smProc_qt.h"
#include  "CDlgTalk_qt.h"
#include <qlist.h>
#include	"funcsforIsCliHelp.h"

CDlgChairmanLayout::CDlgChairmanLayout(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::CDlgChairmanLayoutClass)
{
	ui->setupUi(this);

	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setWindowOpacity(0.9);
	QCursor::setPos(0, 0);

	m_pParent = parent;

	ui->lab_title->setText(u8"选择主席人");
	ui->btnChair_tile->setText(u8"进入平铺布局");
	ui->btnChair_up->setText(u8"（第1页）上一页");
	ui->btnChair_2->setText("");
	ui->btnChair_3->setText("");
	ui->btnChair_4->setText("");
	ui->btnChair_5->setText("");
	ui->btnChair_6->setText("");
	ui->btnChair_7->setText("");
	ui->btnChair_8->setText("");
	ui->btnChair_9->setText("");
	ui->btnChair_down->setText(u8"（第1页）下一页");

	sheetBackgroundImage();


	ui->lab_title_val->setVisible(false);
	ui->btnChair_title_val->setVisible(false);
	ui->btnChair_up_val->setVisible(false);
	ui->btnChair_2_val->setVisible(false);
	ui->btnChair_3_val->setVisible(false);
	ui->btnChair_4_val->setVisible(false);
	ui->btnChair_5_val->setVisible(false);
	ui->btnChair_6_val->setVisible(false);
	ui->btnChair_7_val->setVisible(false);
	ui->btnChair_8_val->setVisible(false);
	ui->btnChair_9_val->setVisible(false);
	ui->btnChair_down_val->setVisible(false);

	//初始化数据
	loadData();


}

CDlgChairmanLayout::~CDlgChairmanLayout()
{

}


//布局
void CDlgChairmanLayout::sheetBackgroundImage() {

	QRect rc = QApplication::primaryScreen()->geometry();

	ui->lab_title->setAlignment(Qt::AlignCenter);

	if (rc.width() > 3500) {

		ui->lab_title->setStyleSheet("font-size:54px;font-weight:bold;background:#1E2747;color:#fff;font-family: Microsoft YaHei;");
		//ui->widget->setStyleSheet("QWidget#widget{background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30);}QPushButton{color:#fff;background:#5C8CFC;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

		int w_i = 1600;
		int h_i = 120;
		ui->lab_title->setFixedSize(w_i, h_i);
		ui->btnChair_tile->setFixedSize(w_i, h_i);
		ui->btnChair_up->setFixedSize(w_i, h_i);
		ui->btnChair_2->setFixedSize(w_i, h_i);
		ui->btnChair_3->setFixedSize(w_i, h_i);
		ui->btnChair_4->setFixedSize(w_i, h_i);
		ui->btnChair_5->setFixedSize(w_i, h_i);
		ui->btnChair_6->setFixedSize(w_i, h_i);
		ui->btnChair_7->setFixedSize(w_i, h_i);
		ui->btnChair_8->setFixedSize(w_i, h_i);
		ui->btnChair_9->setFixedSize(w_i, h_i);
		ui->btnChair_down->setFixedSize(w_i, h_i);
		ui->btnChair_close->setFixedSize(w_i, h_i);

		ui->widget->setStyleSheet("QWidget#widget{border-radius:10px;} QPushButton{border-bottom:2px solid #000;background:#1E2747;font-size:68px;color:#fff;font-family: Microsoft YaHei;}QPushButton:focus {font-family: Microsoft YaHei;background:#1A54F1;color:#fff}");
		//ui->label_title->setStyleSheet("font-size:84px;color:#fff;font-weight:bold;background:none;font-family: Microsoft YaHei;");
		//ui->widget->setContentsMargins(20, 20, 20, 20);



	}
	else {
		//resize(500, 700);
		//ui->lab_title->setHeight(30);
		ui->lab_title->setStyleSheet("font-size:28px;font-weight:bold;color:#fff;background:#1E2747;font-family: Microsoft YaHei;");
		//ui->widget->setStyleSheet("QWidget#widget{background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30);}QPushButton{color:#fff;background:#5C8CFC;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");


		ui->widget->setStyleSheet("QWidget#widget{border-radius:10px;} QPushButton{border-bottom:2px solid #000;background:#1E2747;font-size:28px;color:#fff;font-family: Microsoft YaHei;}QPushButton:focus {font-family: Microsoft YaHei;background:#1A54F1;color:#fff}");
		//ui->label_title->setStyleSheet("font-size:42px;color:#fff;font-weight:bold;background:none;font-family: Microsoft YaHei;");



		int h_i = 60;
		int w_i = 700;
		ui->widget->setFixedWidth(w_i);

		ui->lab_title->setFixedSize(w_i, h_i);
		ui->btnChair_tile->setFixedSize(w_i, h_i);
		ui->btnChair_up->setFixedSize(w_i, h_i);
		ui->btnChair_2->setFixedSize(w_i, h_i);
		ui->btnChair_3->setFixedSize(w_i, h_i);
		ui->btnChair_4->setFixedSize(w_i, h_i);
		ui->btnChair_5->setFixedSize(w_i, h_i);
		ui->btnChair_6->setFixedSize(w_i, h_i);
		ui->btnChair_7->setFixedSize(w_i, h_i);
		ui->btnChair_8->setFixedSize(w_i, h_i);
		ui->btnChair_9->setFixedSize(w_i, h_i);
		ui->btnChair_down->setFixedSize(w_i, h_i);
		ui->btnChair_close->setFixedSize(w_i, h_i);

	}

}



//关闭
void CDlgChairmanLayout::on_btnChair_close_clicked() {

	CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)m_pParent;

	pWin_cdlgtalk->on_closeChairman_slots();
	return;
}






void CDlgChairmanLayout::on_btnChair_2_clicked() {


	send_selLayoutType(ui->btnChair_2_val->text());


}

void CDlgChairmanLayout::on_btnChair_3_clicked() {



	send_selLayoutType(ui->btnChair_3_val->text());


}

void CDlgChairmanLayout::on_btnChair_4_clicked() {


	send_selLayoutType(ui->btnChair_4_val->text());


}

void CDlgChairmanLayout::on_btnChair_5_clicked() {

	send_selLayoutType(ui->btnChair_5_val->text());


}

void CDlgChairmanLayout::on_btnChair_6_clicked() {

	send_selLayoutType(ui->btnChair_6_val->text());



}

void CDlgChairmanLayout::on_btnChair_7_clicked() {

	send_selLayoutType(ui->btnChair_7_val->text());


}

void CDlgChairmanLayout::on_btnChair_8_clicked() {

	send_selLayoutType(ui->btnChair_8_val->text());


}

void CDlgChairmanLayout::on_btnChair_9_clicked() {

	send_selLayoutType(ui->btnChair_9_val->text());

}

//平铺模式
void CDlgChairmanLayout::on_btnChair_tile_clicked()
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));


	// do sth					
	ConfLayoutParam  confLayoutParam = { 0 };

	confLayoutParam.oneBigLayoutParam.ucbOneBigLayout = false;


	if (!pMisCnt)  return;
	CHelp_getDlgTalkVar help_getDlgTalkVar;
	CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)m_pParent;

	DLG_TALK_var* pm_var = pWin_cdlgtalk->get_pm_var();
	if (!pm_var)return;
	if (isTalkerShadowMgr(pm_var->addr)) return;
	TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
	HWND  hMgr = pShadowInfo->hMgr;

	do {
		CHelp_getDlgTalkVar help_getDlgTalkVar;
		DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hMgr);
		if (!pDlgTalkVar)break;
		if (!isTalkerShadowMgr(pDlgTalkVar->addr)) break;
		if (!pDlgTalkVar->av.taskInfo.bTaskExists) break;

		QY_MESSENGER_ID  idInfo_to = pDlgTalkVar->av.taskInfo.idInfo_starter;

		//
		QY_MESSENGER_ID  idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
		QY_MESSENGER_ID  idInfo_requester = pMisCnt->idInfo;

		//
		sendConfLayout(false , 0, CONST_imOp_setOneBig, &confLayoutParam, idInfo_imGrp_related, idInfo_requester, idInfo_to, _T(""));

		//
		iErr = 0;
	} while (false);

	on_btnChair_close_clicked();

	pWin_cdlgtalk->_isChairmanLayout = false;//记录菜单变化

	//关闭放大状态 强制
	pWin_cdlgtalk->on_closeVideoAmpOff_slots();

}


//上一页
void CDlgChairmanLayout::on_btnChair_up_clicked() {

	//pageLoadData(true);

}

//下一页
void CDlgChairmanLayout::on_btnChair_down_clicked() {

	//pageLoadData(false);

}

//装载数据
void  CDlgChairmanLayout::loadData()
{

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

	CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)m_pParent;

	DLG_TALK_var* pm_var = pWin_cdlgtalk->get_pm_var();
	if (!pm_var)return;
	if (isTalkerShadowMgr(pm_var->addr)) return;
	TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
	HWND  hMgr = pShadowInfo->hMgr;

	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	DLG_TALK_var* pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
	if (!pMgrVar)return;

	//
	do {
		if (!pMgrVar->av.taskInfo.bTaskExists)  break;
		//
		int index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, pMgrVar->av.taskInfo.iTaskId);

		QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
		if (!pTaskInfo)break;
		QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;
		if (!pTaskData)break;
		if (pTaskData->uiType != CONST_taskDataType_conf)break;
		QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskData;
		DLG_TALK_videoConference* pVc = &pTc->videoConference;
		TCHAR  tBuf[256];
		int i;

		//
		for (i = 0; i < pVc->usCntLimit_activeMems_from; i++) {
			DLG_TALK_videoConferenceActiveMemFrom* pActiveMem = &pVc->activeMems_from[i];
			if (!pActiveMem->avStream.idInfo.ui64Id)  continue;

			if (pActiveMem->avStream.obj.resObj.uiObjType == CONST_objType_mosaicStream_video)  continue;
			if (pActiveMem->avStream.obj.resObj.uiObjType == CONST_objType_mosaicStream_resource)  continue;

			//
			_sntprintf(tBuf, mycountof(tBuf), _T("%I64u|%d|%s"), pActiveMem->avStream.idInfo.ui64Id, pActiveMem->avStream.obj.tranInfo.video.uiTranNo_openAvDev, pActiveMem->desc);
			_dataList.append(QString::fromUtf16((char16_t*)tBuf));
			//
			_sntprintf(tBuf, mycountof(tBuf), _T("%s"), pActiveMem->desc);
			_dataList_ui.append(QString::fromUtf16((char16_t*)tBuf));
			//tmpiRet = SendMessage(hCtl, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)tBuf);

			//
			continue;
		}

		//
	} while (false);




	switch (_dataList.size())
	{
	case 1:
		ui->btnChair_2->setText(_dataList_ui[0]);
		//
		ui->btnChair_2_val->setText(_dataList[0]);
		break;
	case 2:
		ui->btnChair_2->setText(_dataList_ui[0]);
		ui->btnChair_3->setText(_dataList_ui[1]);
		//
		ui->btnChair_2_val->setText(_dataList[0]);
		ui->btnChair_3_val->setText(_dataList[1]);
		break;
	case 3:
		ui->btnChair_2->setText(_dataList_ui[0]);
		ui->btnChair_3->setText(_dataList_ui[1]);
		ui->btnChair_4->setText(_dataList_ui[2]);
		//
		ui->btnChair_2_val->setText(_dataList[0]);
		ui->btnChair_3_val->setText(_dataList[1]);
		ui->btnChair_4_val->setText(_dataList[2]);
		break;
	case 4:
		ui->btnChair_2->setText(_dataList_ui[0]);
		ui->btnChair_3->setText(_dataList_ui[1]);
		ui->btnChair_4->setText(_dataList_ui[2]);
		ui->btnChair_5->setText(_dataList_ui[3]);
		//
		ui->btnChair_2_val->setText(_dataList[0]);
		ui->btnChair_3_val->setText(_dataList[1]);
		ui->btnChair_4_val->setText(_dataList[2]);
		ui->btnChair_5_val->setText(_dataList[3]);
		break;
	case 5:
		ui->btnChair_2->setText(_dataList_ui[0]);
		ui->btnChair_3->setText(_dataList_ui[1]);
		ui->btnChair_4->setText(_dataList_ui[2]);
		ui->btnChair_5->setText(_dataList_ui[3]);
		ui->btnChair_6->setText(_dataList_ui[4]);
		//
		ui->btnChair_2_val->setText(_dataList[0]);
		ui->btnChair_3_val->setText(_dataList[1]);
		ui->btnChair_4_val->setText(_dataList[2]);
		ui->btnChair_5_val->setText(_dataList[3]);
		ui->btnChair_6_val->setText(_dataList[4]);
		break;
	case 6:
		ui->btnChair_2->setText(_dataList_ui[0]);
		ui->btnChair_3->setText(_dataList_ui[1]);
		ui->btnChair_4->setText(_dataList_ui[2]);
		ui->btnChair_5->setText(_dataList_ui[3]);
		ui->btnChair_6->setText(_dataList_ui[4]);
		ui->btnChair_7->setText(_dataList_ui[5]);
		//
		ui->btnChair_2_val->setText(_dataList[0]);
		ui->btnChair_3_val->setText(_dataList[1]);
		ui->btnChair_4_val->setText(_dataList[2]);
		ui->btnChair_5_val->setText(_dataList[3]);
		ui->btnChair_6_val->setText(_dataList[4]);
		ui->btnChair_7_val->setText(_dataList[5]);
		break;
	case 7:
		ui->btnChair_2->setText(_dataList_ui[0]);
		ui->btnChair_3->setText(_dataList_ui[1]);
		ui->btnChair_4->setText(_dataList_ui[2]);
		ui->btnChair_5->setText(_dataList_ui[3]);
		ui->btnChair_6->setText(_dataList_ui[4]);
		ui->btnChair_7->setText(_dataList_ui[5]);
		ui->btnChair_8->setText(_dataList_ui[6]);
		//
		ui->btnChair_2_val->setText(_dataList[0]);
		ui->btnChair_3_val->setText(_dataList[1]);
		ui->btnChair_4_val->setText(_dataList[2]);
		ui->btnChair_5_val->setText(_dataList[3]);
		ui->btnChair_6_val->setText(_dataList[4]);
		ui->btnChair_7_val->setText(_dataList[5]);
		ui->btnChair_8_val->setText(_dataList[6]);
		break;
	case 8:
		ui->btnChair_2->setText(_dataList_ui[0]);
		ui->btnChair_3->setText(_dataList_ui[1]);
		ui->btnChair_4->setText(_dataList_ui[2]);
		ui->btnChair_5->setText(_dataList_ui[3]);
		ui->btnChair_6->setText(_dataList_ui[4]);
		ui->btnChair_7->setText(_dataList_ui[5]);
		ui->btnChair_8->setText(_dataList_ui[6]);
		ui->btnChair_9->setText(_dataList_ui[7]);

		//
		ui->btnChair_2_val->setText(_dataList[0]);
		ui->btnChair_3_val->setText(_dataList[1]);
		ui->btnChair_4_val->setText(_dataList[2]);
		ui->btnChair_5_val->setText(_dataList[3]);
		ui->btnChair_6_val->setText(_dataList[4]);
		ui->btnChair_7_val->setText(_dataList[5]);
		ui->btnChair_8_val->setText(_dataList[6]);
		ui->btnChair_9_val->setText(_dataList[7]);
		break;
	default:
		break;
	}


	//if (pProcInfo->m_var.ctxSm.hg.p2pInfos.cnt > 1) {
	ui->btnChair_tile->setFocus();


}


//分页装载数据
void CDlgChairmanLayout::pageLoadData(bool is_up) {

}

//执行
void CDlgChairmanLayout::send_selLayoutType(QString str) 
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	if (str.isEmpty()) return;
	QStringList list = str.split("|");

	// do sth					
	ConfLayoutParam  confLayoutParam = { 0 };
	
	confLayoutParam.oneBigLayoutParam.ucbOneBigLayout = true;
	confLayoutParam.oneBigLayoutParam.ui64Id = list[0].toInt();


	if (!pMisCnt)  return ;
	CHelp_getDlgTalkVar help_getDlgTalkVar;
	CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)m_pParent;

	DLG_TALK_var* pm_var = pWin_cdlgtalk->get_pm_var();
	if (!pm_var)return;
	if (isTalkerShadowMgr(pm_var->addr)) return;
	TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
	HWND  hMgr = pShadowInfo->hMgr;

	do {
		CHelp_getDlgTalkVar help_getDlgTalkVar;
		DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hMgr);
		if (!pDlgTalkVar)break;
		if (!isTalkerShadowMgr(pDlgTalkVar->addr)) break;
		if (!pDlgTalkVar->av.taskInfo.bTaskExists) break;

		QY_MESSENGER_ID  idInfo_to = pDlgTalkVar->av.taskInfo.idInfo_starter;

		//
		QY_MESSENGER_ID  idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
		QY_MESSENGER_ID  idInfo_requester = pMisCnt->idInfo;

		//
		sendConfLayout(false,0, CONST_imOp_setOneBig, &confLayoutParam, idInfo_imGrp_related, idInfo_requester, idInfo_to, _T(""));

		//
		iErr = 0;
	} while (false);
	
	on_btnChair_close_clicked();

	pWin_cdlgtalk->_isChairmanLayout = true;//记录菜单变化
}




//下箭头
void CDlgChairmanLayout::Infrared_down()
{

	if (chkFocus(this))return;
	this->focusNextPrevChild(true);
}

//上箭头
void CDlgChairmanLayout::Infrared_up()
{
	if (chkFocus(this))return;
	this->focusNextPrevChild(false);
}

