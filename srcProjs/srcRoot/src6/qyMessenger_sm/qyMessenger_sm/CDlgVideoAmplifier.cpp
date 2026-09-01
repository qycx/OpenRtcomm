#include	<tchar.h>
#include "CDlgVideoAmplifier.h"
//
//#include <qdesktopwidget.h>
#include	<qscreen.h>

#include	"qyMcMainCommon_qt.h"
#include	"ctxQmc_sm.h"
#include	"smProc_qt.h"
#include  "CDlgTalk_qt.h"
#include <qlist.h>
#include	"funcsforIsCliHelp.h"

CDlgVideoAmplifier::CDlgVideoAmplifier(QWidget* parent)
	: QDialog(parent),
	ui(new Ui::CDlgVideoAmplifierClass)
{
	ui->setupUi(this);

	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);


	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setWindowOpacity(0.9);
	QCursor::setPos(0, 0);

	m_pParent = parent;

	ui->btnAmp_up->setText(u8"（第1页）上一页");
	ui->btnAmp_2->setText("");
	ui->btnAmp_3->setText("");
	ui->btnAmp_4->setText("");
	ui->btnAmp_5->setText("");
	ui->btnAmp_6->setText("");
	ui->btnAmp_7->setText("");
	ui->btnAmp_8->setText("");
	ui->btnAmp_9->setText("");
	ui->btnAmp_down->setText(u8"（第1页）下一页");

	sheetBackgroundImage();

	loadData();
}

//初始化数据
void CDlgVideoAmplifier::loadData() {

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
			_sntprintf(tBuf, mycountof(tBuf), _T("%I64u|%d| %s"), pActiveMem->avStream.idInfo.ui64Id, pActiveMem->avStream.obj.tranInfo.video.uiTranNo_openAvDev, pActiveMem->desc);

			_dataList.append(QString::fromUtf16((char16_t*)tBuf));
			//
			//tmpiRet = SendMessage(hCtl, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)tBuf);

			//
			continue;
		}

		//
	} while (false);



	//for (int i = 0; i < _pageCount; i++) {
	//	ui->btnAmp_2->setText(_dataList[i]);
	//ui->btnAmp_3->setText(_dataList[i]);
	//ui->btnAmp_4->setText(_dataList[i]);
	//ui->btnAmp_5->setText(_dataList[i]);
	//ui->btnAmp_6->setText(_dataList[i]);
	//ui->btnAmp_7->setText(_dataList[i]);
	//ui->btnAmp_8->setText(_dataList[i]);
	//ui->btnAmp_9->setText(_dataList[i]);


	//	QString termName1 = QString::fromUtf16(_dataList[i]);
	//	QString termName2 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[1].termName);
	//	QString termName3 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[2].termName);
	//	QString termName4 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[3].termName);
	//	QString termName5 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[4].termName);
	//	QString termName6 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[5].termName);
	//	QString termName7 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[6].termName);
	//	QString termName8 = QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.p2pInfos.mems[7].termName);


	//}


	switch (_dataList.size())
	{
	case 1:
		ui->btnAmp_2->setText(_dataList[0]);

		break;
	case 2:
		ui->btnAmp_2->setText(_dataList[0]);
		ui->btnAmp_3->setText(_dataList[1]);

		break;
	case 3:
		ui->btnAmp_2->setText(_dataList[0]);
		ui->btnAmp_3->setText(_dataList[1]);
		ui->btnAmp_4->setText(_dataList[2]);

		break;
	case 4:
		ui->btnAmp_2->setText(_dataList[0]);
		ui->btnAmp_3->setText(_dataList[1]);
		ui->btnAmp_4->setText(_dataList[2]);
		ui->btnAmp_5->setText(_dataList[3]);

		break;
	case 5:
		ui->btnAmp_2->setText(_dataList[0]);
		ui->btnAmp_3->setText(_dataList[1]);
		ui->btnAmp_4->setText(_dataList[2]);
		ui->btnAmp_5->setText(_dataList[3]);
		ui->btnAmp_6->setText(_dataList[4]);

		break;
	case 6:
		ui->btnAmp_2->setText(_dataList[0]);
		ui->btnAmp_3->setText(_dataList[1]);
		ui->btnAmp_4->setText(_dataList[2]);
		ui->btnAmp_5->setText(_dataList[3]);
		ui->btnAmp_6->setText(_dataList[4]);
		ui->btnAmp_7->setText(_dataList[5]);

		break;
	case 7:
		ui->btnAmp_2->setText(_dataList[0]);
		ui->btnAmp_3->setText(_dataList[1]);
		ui->btnAmp_4->setText(_dataList[2]);
		ui->btnAmp_5->setText(_dataList[3]);
		ui->btnAmp_6->setText(_dataList[4]);
		ui->btnAmp_7->setText(_dataList[5]);
		ui->btnAmp_8->setText(_dataList[6]);

		break;
	case 8:
		ui->btnAmp_2->setText(_dataList[0]);
		ui->btnAmp_3->setText(_dataList[1]);
		ui->btnAmp_4->setText(_dataList[2]);
		ui->btnAmp_5->setText(_dataList[3]);
		ui->btnAmp_6->setText(_dataList[4]);
		ui->btnAmp_7->setText(_dataList[5]);
		ui->btnAmp_8->setText(_dataList[6]);
		ui->btnAmp_9->setText(_dataList[7]);

		break;
	default:
		break;
	}


	//if (pProcInfo->m_var.ctxSm.hg.p2pInfos.cnt > 1) {
	ui->btnAmp_2->setFocus();
	//}

}



//布局
void CDlgVideoAmplifier::sheetBackgroundImage() {

	QRect rc = QApplication::primaryScreen()->geometry();

	ui->lab_title->setAlignment(Qt::AlignCenter);

	if (rc.width() > 3500) {

		ui->lab_title->setStyleSheet("font-size:54px;font-weight:bold;background:#1E2747;color:#fff;font-family: Microsoft YaHei;");
		//ui->widget->setStyleSheet("QWidget#widget{background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30);}QPushButton{color:#fff;background:#5C8CFC;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

		int w_i = 1600;
		int h_i = 120;
		ui->lab_title->setFixedSize(w_i, h_i);
		ui->btnAmp_up->setFixedSize(w_i, h_i);
		ui->btnAmp_2->setFixedSize(w_i, h_i);
		ui->btnAmp_3->setFixedSize(w_i, h_i);
		ui->btnAmp_4->setFixedSize(w_i, h_i);
		ui->btnAmp_5->setFixedSize(w_i, h_i);
		ui->btnAmp_6->setFixedSize(w_i, h_i);
		ui->btnAmp_7->setFixedSize(w_i, h_i);
		ui->btnAmp_8->setFixedSize(w_i, h_i);
		ui->btnAmp_9->setFixedSize(w_i, h_i);
		ui->btnAmp_down->setFixedSize(w_i, h_i);
		ui->btnAmp_close->setFixedSize(w_i, h_i);

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
		ui->btnAmp_up->setFixedSize(w_i, h_i);
		ui->btnAmp_2->setFixedSize(w_i, h_i);
		ui->btnAmp_3->setFixedSize(w_i, h_i);
		ui->btnAmp_4->setFixedSize(w_i, h_i);
		ui->btnAmp_5->setFixedSize(w_i, h_i);
		ui->btnAmp_6->setFixedSize(w_i, h_i);
		ui->btnAmp_7->setFixedSize(w_i, h_i);
		ui->btnAmp_8->setFixedSize(w_i, h_i);
		ui->btnAmp_9->setFixedSize(w_i, h_i);
		ui->btnAmp_down->setFixedSize(w_i, h_i);
		ui->btnAmp_close->setFixedSize(w_i, h_i);



	}

}

CDlgVideoAmplifier::~CDlgVideoAmplifier()
{}


//关闭
void CDlgVideoAmplifier::on_btnAmp_close_clicked() {

	CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)m_pParent;

	pWin_cdlgtalk->on_showVideoAmplifier_slots();
	return;
}






void CDlgVideoAmplifier::on_btnAmp_2_clicked() {


	send_selLayoutType(ui->btnAmp_2->text());


}

void CDlgVideoAmplifier::on_btnAmp_3_clicked() {



	send_selLayoutType(ui->btnAmp_3->text());


}

void CDlgVideoAmplifier::on_btnAmp_4_clicked() {


	send_selLayoutType(ui->btnAmp_4->text());


}

void CDlgVideoAmplifier::on_btnAmp_5_clicked() {

	send_selLayoutType(ui->btnAmp_5->text());


}

void CDlgVideoAmplifier::on_btnAmp_6_clicked() {

	send_selLayoutType(ui->btnAmp_6->text());



}

void CDlgVideoAmplifier::on_btnAmp_7_clicked() {

	send_selLayoutType(ui->btnAmp_7->text());


}

void CDlgVideoAmplifier::on_btnAmp_8_clicked() {

	send_selLayoutType(ui->btnAmp_8->text());


}

void CDlgVideoAmplifier::on_btnAmp_9_clicked() {

	send_selLayoutType(ui->btnAmp_9->text());

}

//上一页
void CDlgVideoAmplifier::on_btnAmp_up_clicked() {

	pageLoadData(true);

}

//下一页
void CDlgVideoAmplifier::on_btnAmp_down_clicked() {

	pageLoadData(false);

}

//分页装载数据
void CDlgVideoAmplifier::pageLoadData(bool is_up) {


	int dataList_size = _dataList.size();
	if (is_up) {

		if (_pageCur == 1) {
			return;
		}
		_pageCur--;
		int offset = (_pageCur - 1) * _pageCount;


		switch (dataList_size)
		{
		case 1:
			ui->btnAmp_2->setText(_dataList[offset]);

			break;
		case 2:
			ui->btnAmp_2->setText(_dataList[offset]);
			ui->btnAmp_3->setText(_dataList[++offset]);

			break;
		case 3:
			ui->btnAmp_2->setText(_dataList[offset]);
			ui->btnAmp_3->setText(_dataList[++offset]);
			ui->btnAmp_4->setText(_dataList[++offset]);

			break;
		case 4:
			ui->btnAmp_2->setText(_dataList[offset]);
			ui->btnAmp_3->setText(_dataList[++offset]);
			ui->btnAmp_4->setText(_dataList[++offset]);
			ui->btnAmp_5->setText(_dataList[++offset]);

			break;
		case 5:
			ui->btnAmp_2->setText(_dataList[offset]);
			ui->btnAmp_3->setText(_dataList[++offset]);
			ui->btnAmp_4->setText(_dataList[++offset]);
			ui->btnAmp_5->setText(_dataList[++offset]);
			ui->btnAmp_6->setText(_dataList[++offset]);

			break;
		case 6:
			ui->btnAmp_2->setText(_dataList[offset]);
			ui->btnAmp_3->setText(_dataList[++offset]);
			ui->btnAmp_4->setText(_dataList[++offset]);
			ui->btnAmp_5->setText(_dataList[++offset]);
			ui->btnAmp_6->setText(_dataList[++offset]);
			ui->btnAmp_7->setText(_dataList[++offset]);

			break;
		case 7:
			ui->btnAmp_2->setText(_dataList[offset]);
			ui->btnAmp_3->setText(_dataList[++offset]);
			ui->btnAmp_4->setText(_dataList[++offset]);
			ui->btnAmp_5->setText(_dataList[++offset]);
			ui->btnAmp_6->setText(_dataList[++offset]);
			ui->btnAmp_7->setText(_dataList[++offset]);
			ui->btnAmp_8->setText(_dataList[++offset]);

			break;
		case 8:
			ui->btnAmp_2->setText(_dataList[offset]);
			ui->btnAmp_3->setText(_dataList[++offset]);
			ui->btnAmp_4->setText(_dataList[++offset]);
			ui->btnAmp_5->setText(_dataList[++offset]);
			ui->btnAmp_6->setText(_dataList[++offset]);
			ui->btnAmp_7->setText(_dataList[++offset]);
			ui->btnAmp_8->setText(_dataList[++offset]);
			ui->btnAmp_9->setText(_dataList[++offset]);

			break;
		default:
			break;
		}


	}
	else {
		_pageCur++;
		int offset = (_pageCur - 1) * _pageCount;

		if (offset >= dataList_size) {
			_pageCur--;
			return;
		}


		switch (dataList_size)
		{
		case 1:
			ui->btnAmp_2->setText(_dataList[offset]);

			break;
		case 2:
			ui->btnAmp_2->setText(_dataList[offset]);
			ui->btnAmp_3->setText(_dataList[++offset]);

			break;
		case 3:
			ui->btnAmp_2->setText(_dataList[offset]);
			ui->btnAmp_3->setText(_dataList[++offset]);
			ui->btnAmp_4->setText(_dataList[++offset]);

			break;
		case 4:
			ui->btnAmp_2->setText(_dataList[offset]);
			ui->btnAmp_3->setText(_dataList[++offset]);
			ui->btnAmp_4->setText(_dataList[++offset]);
			ui->btnAmp_5->setText(_dataList[++offset]);

			break;
		case 5:
			ui->btnAmp_2->setText(_dataList[offset]);
			ui->btnAmp_3->setText(_dataList[++offset]);
			ui->btnAmp_4->setText(_dataList[++offset]);
			ui->btnAmp_5->setText(_dataList[++offset]);
			ui->btnAmp_6->setText(_dataList[++offset]);

			break;
		case 6:
			ui->btnAmp_2->setText(_dataList[offset]);
			ui->btnAmp_3->setText(_dataList[++offset]);
			ui->btnAmp_4->setText(_dataList[++offset]);
			ui->btnAmp_5->setText(_dataList[++offset]);
			ui->btnAmp_6->setText(_dataList[++offset]);
			ui->btnAmp_7->setText(_dataList[++offset]);

			break;
		case 7:
			ui->btnAmp_2->setText(_dataList[offset]);
			ui->btnAmp_3->setText(_dataList[++offset]);
			ui->btnAmp_4->setText(_dataList[++offset]);
			ui->btnAmp_5->setText(_dataList[++offset]);
			ui->btnAmp_6->setText(_dataList[++offset]);
			ui->btnAmp_7->setText(_dataList[++offset]);
			ui->btnAmp_8->setText(_dataList[++offset]);

			break;
		case 8:
			ui->btnAmp_2->setText(_dataList[offset]);
			ui->btnAmp_3->setText(_dataList[++offset]);
			ui->btnAmp_4->setText(_dataList[++offset]);
			ui->btnAmp_5->setText(_dataList[++offset]);
			ui->btnAmp_6->setText(_dataList[++offset]);
			ui->btnAmp_7->setText(_dataList[++offset]);
			ui->btnAmp_8->setText(_dataList[++offset]);
			ui->btnAmp_9->setText(_dataList[++offset]);

			break;
		default:
			break;
		}

	}

	ui->btnAmp_up->setText(u8"（第" + QString::number(_pageCur) + u8"页）上一页");
	ui->btnAmp_down->setText(u8"（第" + QString::number(_pageCur) + u8"页）下一页");

}


//执行
void CDlgVideoAmplifier::send_selLayoutType(QString str) {

	if (str.isEmpty())return;

	CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)m_pParent;

	DLG_TALK_var* pm_var = pWin_cdlgtalk->get_pm_var();
	if (!pm_var)return;
	if (isTalkerShadowMgr(pm_var->addr)) return;
	TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
	HWND  hMgr = pShadowInfo->hMgr;


	QStringList list = str.split("|");

	unsigned  short  usLayoutType = 0;
	ConfLayoutParam confLayoutParam = { 0 };
	confLayoutParam.enlargeParam.usEnlargeType = CONST_enlargeType_img;
	confLayoutParam.enlargeParam.ui64Id = list[0].toInt();
	confLayoutParam.enlargeParam.tn_v = list[1].toInt();

	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);

	//
	pProcInfo->m_ipcProc.op.idInfo.ui64Id = list[0].toInt();

	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
	if (!pDlgTalkVar)return;
	if (pDlgTalkVar->av.taskInfo.bTaskExists) {
		//
		if (pDlgTalkVar->av.taskInfo.ucbStarter)
		{
			//pFuncs->pf_sendVideoConferenceLayout(usLayoutType, &confLayoutParam, hMgr, pDlgTalkVar->addr.idInfo, _T("doSelLayoutType"));

		}
		else {
			//
			QY_MESSENGER_ID  idInfo_imGrp_related;  idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
			QY_MESSENGER_ID idInfo_requester; idInfo_requester.ui64Id = pMisCnt->idInfo.ui64Id;

			//
			pFuncs->pf_sendVideoConferenceLayout(false, usLayoutType, CONST_imOp_enlargeImg, &confLayoutParam, idInfo_imGrp_related, idInfo_requester, pDlgTalkVar->av.taskInfo.idInfo_starter, _T("doSelLayoutType"));
		}
	}

	//
	on_btnAmp_close_clicked();
	pWin_cdlgtalk->_isVideoAmplifier = true; //记录菜单变化
}




//下箭头
void CDlgVideoAmplifier::Infrared_down()
{

	if (chkFocus(this))return;
	this->focusNextPrevChild(true);
}

//上箭头
void CDlgVideoAmplifier::Infrared_up()
{
	if (chkFocus(this))return;
	this->focusNextPrevChild(false);
}

