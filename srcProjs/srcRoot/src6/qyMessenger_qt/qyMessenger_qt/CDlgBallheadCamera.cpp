#include	<tchar.h>
#include "CDlgBallheadCamera.h"

//#include <qdesktopwidget.h>
#include<qscreen.h>

#include	"qyMcMainCommon_qt.h"
//#include	"ctxQmc_sm.h"
//#include	"smProc_qt.h"
#include  "CDlgTalk_qt.h"
#include <qlist.h>
#include	"funcsforIsCliHelp.h"

#pragma execution_character_set("utf-8")

#define		CONST_ALL_Txt			"切换布局"
#define		CONST_NULL_Txt			"无可用球机设备"

CDlgBallheadCamera::CDlgBallheadCamera(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::CDlgBallheadCameraClass)
{
	ui->setupUi(this);


	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);


	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setWindowOpacity(0.9);
	QCursor::setPos(0, 0);

	m_pParent = parent;


	ui->lab_title->setText(u8"球机列表选择");
	ui->btnBall_Amp_off->setText(u8"取消画面放大");
	ui->btnBall_up->setText(u8"（第1页）上一页");
	ui->btnBall_2->setText("");
	ui->btnBall_3->setText("");
	ui->btnBall_4->setText("");
	ui->btnBall_5->setText("");
	ui->btnBall_6->setText("");
	ui->btnBall_7->setText("");
	ui->btnBall_8->setText("");
	ui->btnBall_9->setText("");
	ui->btnBall_down->setText(u8"（第1页）下一页");


	ui->lab_title_val->setVisible(false);
	ui->btnBall_Amp_off_val->setVisible(false);
	ui->btnBall_up_val->setVisible(false);
	ui->ball_2_val->setVisible(false);
	ui->ball_3_val->setVisible(false);
	ui->ball_4_val->setVisible(false);
	ui->ball_5_val->setVisible(false);
	ui->ball_6_val->setVisible(false);
	ui->ball_7_val->setVisible(false);
	ui->ball_8_val->setVisible(false);
	ui->ball_9_val->setVisible(false);
	ui->btnBall_down_val->setVisible(false);
	ui->btnBall_close_val->setVisible(false);
	sheetBackgroundImage();

	//初始化数据
	loadData();
}

CDlgBallheadCamera::~CDlgBallheadCamera()
{

}

//布局
void CDlgBallheadCamera::sheetBackgroundImage() {

	QRect rc = QApplication::primaryScreen()->geometry();

	ui->lab_title->setAlignment(Qt::AlignCenter);

	if (rc.width() > 3500) {

		ui->lab_title->setStyleSheet("font-size:54px;font-weight:bold;background:#1E2747;color:#fff;font-family: Microsoft YaHei;");
		//ui->widget->setStyleSheet("QWidget#widget{background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30);}QPushButton{color:#fff;background:#5C8CFC;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

		int w_i = 1600;
		int h_i = 120;
		ui->lab_title->setFixedSize(w_i, h_i);
		ui->btnBall_Amp_off->setFixedSize(w_i, h_i);
		ui->btnBall_up->setFixedSize(w_i, h_i);
		ui->btnBall_2->setFixedSize(w_i, h_i);
		ui->btnBall_3->setFixedSize(w_i, h_i);
		ui->btnBall_4->setFixedSize(w_i, h_i);
		ui->btnBall_5->setFixedSize(w_i, h_i);
		ui->btnBall_6->setFixedSize(w_i, h_i);
		ui->btnBall_7->setFixedSize(w_i, h_i);
		ui->btnBall_8->setFixedSize(w_i, h_i);
		ui->btnBall_9->setFixedSize(w_i, h_i);
		ui->btnBall_down->setFixedSize(w_i, h_i);
		ui->btnBall_close->setFixedSize(w_i, h_i);

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
		ui->btnBall_Amp_off->setFixedSize(w_i, h_i);
		ui->btnBall_up->setFixedSize(w_i, h_i);
		ui->btnBall_2->setFixedSize(w_i, h_i);
		ui->btnBall_3->setFixedSize(w_i, h_i);
		ui->btnBall_4->setFixedSize(w_i, h_i);
		ui->btnBall_5->setFixedSize(w_i, h_i);
		ui->btnBall_6->setFixedSize(w_i, h_i);
		ui->btnBall_7->setFixedSize(w_i, h_i);
		ui->btnBall_8->setFixedSize(w_i, h_i);
		ui->btnBall_9->setFixedSize(w_i, h_i);
		ui->btnBall_down->setFixedSize(w_i, h_i);
		ui->btnBall_close->setFixedSize(w_i, h_i);

	}

}



//关闭
void CDlgBallheadCamera::on_btnBall_close_clicked() {

	CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)m_pParent;

	pWin_cdlgtalk->on_showBallheadCamera_slots();
	return;
}






void CDlgBallheadCamera::on_btnBall_2_clicked() {

	if (ui->ball_2_val->text() != CONST_NULL_Txt) {
		send_selLayoutType(ui->ball_2_val->text());
	}

}

void CDlgBallheadCamera::on_btnBall_3_clicked() {



	send_selLayoutType(ui->ball_3_val->text());


}

void CDlgBallheadCamera::on_btnBall_4_clicked() {


	send_selLayoutType(ui->ball_4_val->text());


}

void CDlgBallheadCamera::on_btnBall_5_clicked() {

	send_selLayoutType(ui->ball_5_val->text());


}

void CDlgBallheadCamera::on_btnBall_6_clicked() {

	send_selLayoutType(ui->ball_6_val->text());



}

void CDlgBallheadCamera::on_btnBall_7_clicked() {

	send_selLayoutType(ui->ball_7_val->text());


}

void CDlgBallheadCamera::on_btnBall_8_clicked() {

	send_selLayoutType(ui->ball_8_val->text());


}

void CDlgBallheadCamera::on_btnBall_9_clicked() {

	send_selLayoutType(ui->ball_9_val->text());

}

void CDlgBallheadCamera::send_selLayoutTypeCancle() {

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt)  return;

	ConfLayoutParam  confLayoutParam = { 0 };
	//confLayoutParam = pTc->videoConference.confLayoutParam;
	//if (!confLayoutParam.ui64Id)  break;
	//

	confLayoutParam.phoneEnlargeParam.x = 0;
	confLayoutParam.phoneEnlargeParam.y = 0;

	/*
   if (str.isEmpty()) return;
   QStringList list = str.split("|");

   confLayoutParam.enlargeParam.usEnlargeType = CONST_enlargeType_img;
   confLayoutParam.enlargeParam.ui64Id = pProcInfo->m_ipcProc.op.idInfo.ui64Id;
   confLayoutParam.ipcParam.iChannel = list[0].toInt();
   pProcInfo->m_ipcProc.op.iChannel = list[0].toInt();*/

	CHelp_getDlgTalkVar help_getDlgTalkVar;
	CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)m_pParent;

	DLG_TALK_var* pm_var = pWin_cdlgtalk->get_pm_var();
	if (!pm_var)return;
	if (isTalkerShadowMgr(pm_var->addr)) return;
	TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
	HWND  hMgr = pShadowInfo->hMgr;

	do {

		//DLG_TALK_var* pDlgTalkVar = pWin_cdlgtalk->get_pm_var();
		DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hMgr);
		if (!pDlgTalkVar)break;
		if (!isTalkerShadowMgr(pDlgTalkVar->addr)) break;
		if (!pDlgTalkVar->av.taskInfo.bTaskExists) break;

		QY_MESSENGER_ID  idInfo_to = pDlgTalkVar->av.taskInfo.idInfo_starter;

		//
		QY_MESSENGER_ID  idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
		QY_MESSENGER_ID  idInfo_requester = pMisCnt->idInfo;

		//
		sendConfLayout(false, 0, CONST_imOp_phone_cancelEnlargeImg, &confLayoutParam, idInfo_imGrp_related, idInfo_requester, idInfo_to, _T(""));

		//

	} while (false);

	pWin_cdlgtalk->_isVideoAmplifier = false; //记录菜单变化

	on_btnBall_close_clicked();

	pWin_cdlgtalk->on_closeControlPtz_slots(); //关闭云台窗口

}

//取消画面放大
void CDlgBallheadCamera::on_btnBall_Amp_off_clicked() 
{
	    send_selLayoutTypeCancle();
		return;

		CHelp_getDlgTalkVar help_getDlgTalkVar;
		CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)m_pParent;

		DLG_TALK_var* pm_var = pWin_cdlgtalk->get_pm_var();
		if (!pm_var)return;
		if (isTalkerShadowMgr(pm_var->addr)) return;
		TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
		HWND  hMgr = pShadowInfo->hMgr;
		//DLG_TALK_var* pDlgTalkVar = pWin_cdlgtalk->get_pm_var();
		//DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hMgr);



		unsigned  short  usLayoutType = 0;
		ConfLayoutParam confLayoutParam = { 0 };

		QY_MC* pQyMc = QY_GET_GBUF();
		MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
		if (!pProcInfo)  return; 
		MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
		if (!pMisCnt)  return;

		FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);

		CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
		DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
		if (!pDlgTalkVar)  return;
		if (pDlgTalkVar->av.taskInfo.bTaskExists) {
			//
			if (pDlgTalkVar->av.taskInfo.ucbStarter)
			{
				//pFuncs->pf_sendVideoConferenceLayout(usLayoutType, &confLayoutParam, hMgr, pDlgTalkVar->addr.idInfo, _T("doSelLayoutType"));

			}
			else {

				QY_MESSENGER_ID idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
				QY_MESSENGER_ID idInfo_requester; idInfo_requester.ui64Id = pMisCnt->idInfo.ui64Id;
				//
				//
				pFuncs->pf_sendVideoConferenceLayout(false ,usLayoutType, CONST_imOp_enlargeImg,  &confLayoutParam, idInfo_imGrp_related, idInfo_requester, pDlgTalkVar->av.taskInfo.idInfo_starter, _T("doSelLayoutType"));
			}
		}


		   
		
		pWin_cdlgtalk->_isVideoAmplifier = false; //记录菜单变化
		
		on_btnBall_close_clicked();

		pWin_cdlgtalk->on_closeControlPtz_slots(); //关闭云台窗口
}


//上一页
void CDlgBallheadCamera::on_btnBall_up_clicked() {

	pageLoadData(true);

}

//下一页
void CDlgBallheadCamera::on_btnBall_down_clicked() {

	pageLoadData(false);

}

//装载数据
void  CDlgBallheadCamera::loadData()
{

	int  iRet = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	//
	CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)m_pParent;

	DLG_TALK_var* pm_var = pWin_cdlgtalk->get_pm_var();
	if (!pm_var)return;
	if (isTalkerShadowMgr(pm_var->addr)) return;
	TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
	HWND  hMgr = pShadowInfo->hMgr;

	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	DLG_TALK_var* pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
	if (!pMgrVar)return;

	//int		tmpiRet;

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
		NvrInfo* pNvrInfo = &pProcInfo->m_ipcProc.op.nvrInfo;

		//
		if (pNvrInfo->usCnt) {
			_sntprintf(tBuf, mycountof(tBuf), _T("%d|%S|%s"), -1, "", _T("(所有)"));
			//tmpiRet = SendMessage(hCtl, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)tBuf);
			_dataList.append(QString::fromUtf16((char16_t*)tBuf));
			
			
			_dataList_ui.append(CONST_ALL_Txt);

		}
		else {

			_dataList_ui.append(CONST_NULL_Txt);
			_dataList.append(CONST_NULL_Txt);
		
		}


		//
		for (i = 0; i < pNvrInfo->usCnt; i++) {
			IpcInfo* pMem = &pNvrInfo->mems[i];

			//
			_sntprintf(tBuf, mycountof(tBuf), _T("%d|%S|%s"), pMem->iChannel, pMem->ip, pMem->name);

			_dataList.append(QString::fromUtf16((char16_t*)tBuf));
			//
			//tmpiRet = SendMessage(hCtl, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)tBuf);

			_sntprintf(tBuf, mycountof(tBuf), _T("%s"), pMem->name);
			_dataList_ui.append(QString::fromUtf16((char16_t*)tBuf));
			//
			continue;
		}

		//
	} while (false);


	switch (_dataList_ui.size())
	{
	case 1:
		ui->btnBall_2->setText(_dataList_ui[0]);
		//
		ui->ball_2_val->setText(_dataList[0]);

		break;
	case 2:
		ui->btnBall_2->setText(_dataList_ui[0]);
		ui->btnBall_3->setText(_dataList_ui[1]);
		//
		ui->ball_2_val->setText(_dataList[0]);
		ui->ball_3_val->setText(_dataList[1]);
		break;
	case 3:
		ui->btnBall_2->setText(_dataList_ui[0]);
		ui->btnBall_3->setText(_dataList_ui[1]);
		ui->btnBall_4->setText(_dataList_ui[2]);
		//
		ui->ball_2_val->setText(_dataList[0]);
		ui->ball_3_val->setText(_dataList[1]);
		ui->ball_4_val->setText(_dataList[2]);
		break;
	case 4:
		ui->btnBall_2->setText(_dataList_ui[0]);
		ui->btnBall_3->setText(_dataList_ui[1]);
		ui->btnBall_4->setText(_dataList_ui[2]);
		ui->btnBall_5->setText(_dataList_ui[3]);
		//
		ui->ball_2_val->setText(_dataList[0]);
		ui->ball_3_val->setText(_dataList[1]);
		ui->ball_4_val->setText(_dataList[2]);
		ui->ball_5_val->setText(_dataList[3]);
		break;
	case 5:
		ui->btnBall_2->setText(_dataList_ui[0]);
		ui->btnBall_3->setText(_dataList_ui[1]);
		ui->btnBall_4->setText(_dataList_ui[2]);
		ui->btnBall_5->setText(_dataList_ui[3]);
		ui->btnBall_6->setText(_dataList_ui[4]);
		//
		ui->ball_2_val->setText(_dataList[0]);
		ui->ball_3_val->setText(_dataList[1]);
		ui->ball_4_val->setText(_dataList[2]);
		ui->ball_5_val->setText(_dataList[3]);
		ui->ball_6_val->setText(_dataList[4]);

		break;
	case 6:
		ui->btnBall_2->setText(_dataList_ui[0]);
		ui->btnBall_3->setText(_dataList_ui[1]);
		ui->btnBall_4->setText(_dataList_ui[2]);
		ui->btnBall_5->setText(_dataList_ui[3]);
		ui->btnBall_6->setText(_dataList_ui[4]);
		ui->btnBall_7->setText(_dataList_ui[5]);
		//
		ui->ball_2_val->setText(_dataList[0]);
		ui->ball_3_val->setText(_dataList[1]);
		ui->ball_4_val->setText(_dataList[2]);
		ui->ball_5_val->setText(_dataList[3]);
		ui->ball_6_val->setText(_dataList[4]);
		ui->ball_7_val->setText(_dataList[5]);
		break;
	case 7:
		ui->btnBall_2->setText(_dataList_ui[0]);
		ui->btnBall_3->setText(_dataList_ui[1]);
		ui->btnBall_4->setText(_dataList_ui[2]);
		ui->btnBall_5->setText(_dataList_ui[3]);
		ui->btnBall_6->setText(_dataList_ui[4]);
		ui->btnBall_7->setText(_dataList_ui[5]);
		ui->btnBall_8->setText(_dataList_ui[6]);
		//
		ui->ball_2_val->setText(_dataList[0]);
		ui->ball_3_val->setText(_dataList[1]);
		ui->ball_4_val->setText(_dataList[2]);
		ui->ball_5_val->setText(_dataList[3]);
		ui->ball_6_val->setText(_dataList[4]);
		ui->ball_7_val->setText(_dataList[5]);
		ui->ball_8_val->setText(_dataList[6]);
		break;
	case 8:
		ui->btnBall_2->setText(_dataList_ui[0]);
		ui->btnBall_3->setText(_dataList_ui[1]);
		ui->btnBall_4->setText(_dataList_ui[2]);
		ui->btnBall_5->setText(_dataList_ui[3]);
		ui->btnBall_6->setText(_dataList_ui[4]);
		ui->btnBall_7->setText(_dataList_ui[5]);
		ui->btnBall_8->setText(_dataList_ui[6]);
		ui->btnBall_9->setText(_dataList_ui[7]);
		//
		ui->ball_2_val->setText(_dataList[0]);
		ui->ball_3_val->setText(_dataList[1]);
		ui->ball_4_val->setText(_dataList[2]);
		ui->ball_5_val->setText(_dataList[3]);
		ui->ball_6_val->setText(_dataList[4]);
		ui->ball_7_val->setText(_dataList[5]);
		ui->ball_8_val->setText(_dataList[6]);
		ui->ball_9_val->setText(_dataList[7]);

		break;
	default:
		ui->btnBall_2->setText(_dataList_ui[0]);
		ui->btnBall_3->setText(_dataList_ui[1]);
		ui->btnBall_4->setText(_dataList_ui[2]);
		ui->btnBall_5->setText(_dataList_ui[3]);
		ui->btnBall_6->setText(_dataList_ui[4]);
		ui->btnBall_7->setText(_dataList_ui[5]);
		ui->btnBall_8->setText(_dataList_ui[6]);
		ui->btnBall_9->setText(_dataList_ui[7]);
		//
		ui->ball_2_val->setText(_dataList[0]);
		ui->ball_3_val->setText(_dataList[1]);
		ui->ball_4_val->setText(_dataList[2]);
		ui->ball_5_val->setText(_dataList[3]);
		ui->ball_6_val->setText(_dataList[4]);
		ui->ball_7_val->setText(_dataList[5]);
		ui->ball_8_val->setText(_dataList[6]);
		ui->ball_9_val->setText(_dataList[7]);

		break;
	}


	//if (pProcInfo->m_var.ctxSm.hg.p2pInfos.cnt > 1) {
	ui->btnBall_Amp_off->setFocus();


}


//分页装载数据
void CDlgBallheadCamera::pageLoadData(bool is_up) {

	

	int pNvrInfoUsCnt = _dataList_ui.size();

	if (is_up) {
		//
		if (_pageCur == 1) {
			return;
		}
		_pageCur--;
		int offset = (_pageCur - 1) * _pageCount;
		int offset_ui = (_pageCur - 1) * _pageCount;
		ui->btnBall_2->setText(_dataList_ui[offset_ui]);
		ui->btnBall_3->setText(_dataList_ui[++offset_ui]);
		ui->btnBall_4->setText(_dataList_ui[++offset_ui]);
		ui->btnBall_5->setText(_dataList_ui[++offset_ui]);
		ui->btnBall_6->setText(_dataList_ui[++offset_ui]);
		ui->btnBall_7->setText(_dataList_ui[++offset_ui]);
		ui->btnBall_8->setText(_dataList_ui[++offset_ui]);
		ui->btnBall_9->setText(_dataList_ui[++offset_ui]);
		//
		ui->ball_2_val->setText(_dataList[offset]);
		ui->ball_3_val->setText(_dataList[++offset]);
		ui->ball_4_val->setText(_dataList[++offset]);
		ui->ball_5_val->setText(_dataList[++offset]);
		ui->ball_6_val->setText(_dataList[++offset]);
		ui->ball_7_val->setText(_dataList[++offset]);
		ui->ball_8_val->setText(_dataList[++offset]);
		ui->ball_9_val->setText(_dataList[++offset]);
	}
	else {
		_pageCur++;
		int offset = (_pageCur - 1) * _pageCount;
		int offset_ui = (_pageCur - 1) * _pageCount;
		if (offset > pNvrInfoUsCnt) {
			_pageCur--;
			return;
		}
		ui->btnBall_2->setText(_dataList_ui[offset_ui]);

		int offset_ui_1 = offset_ui+1;
		if (_dataList_ui.size() > offset_ui_1) {
			ui->btnBall_3->setText(_dataList_ui[offset_ui_1]);
		}
		else {
			ui->btnBall_3->setText("");
		}

		int offset_ui_2 = offset_ui_1 + 1;
		if (_dataList_ui.size() > offset_ui_2) {
			ui->btnBall_4->setText(_dataList_ui[offset_ui_2]);
		}
		else {
			ui->btnBall_4->setText("");
		}
		int offset_ui_3 = offset_ui_2 + 1;
		if (_dataList_ui.size() > offset_ui_3) {
			ui->btnBall_5->setText(_dataList_ui[offset_ui_3]);
		}
		else {
			ui->btnBall_5->setText("");
		}
		int offset_ui_4 = offset_ui_3 + 1;
		if (_dataList_ui.size() > offset_ui_4) {
			ui->btnBall_6->setText(_dataList_ui[offset_ui_4]);
		}
		else {
			ui->btnBall_6->setText("");
		}
		int offset_ui_5 = offset_ui_4 + 1;
		if (_dataList_ui.size() > offset_ui_5) {
			ui->btnBall_7->setText(_dataList_ui[offset_ui_5]);
		}
		else {
			ui->btnBall_7->setText("");
		}
		int offset_ui_6 = offset_ui_5 + 1;
		if (_dataList_ui.size() > offset_ui_6) {
			ui->btnBall_8->setText(_dataList_ui[offset_ui_6]);
		}
		else {
			ui->btnBall_8->setText("");
		}
		int offset_ui_7 = offset_ui_6 + 1;
		if (_dataList_ui.size() > offset_ui_7) {
			ui->btnBall_9->setText(_dataList_ui[offset_ui_7]);
		}
		else {
			ui->btnBall_9->setText("");
		}
	
		//
		ui->ball_2_val->setText(_dataList[offset]);
		int offset_1 = offset +1;
		if (_dataList.size() > offset_1) {
			ui->ball_3_val->setText(_dataList[offset_1]);
		}
		else {
			ui->ball_3_val->setText("");
		}

		int offset_2 = offset_1 + 1;
		if (_dataList.size() > offset_2) {
			ui->ball_4_val->setText(_dataList[offset_2]);
		}
		else {
			ui->ball_4_val->setText("");
		}
		int offset_3 = offset_2 + 1;
		if (_dataList.size() > offset_3) {
			ui->ball_5_val->setText(_dataList[offset_3]);
		}
		else {
			ui->ball_5_val->setText("");
		}
		int offset_4 = offset_3 + 1;
		if (_dataList.size() > offset_4) {
			ui->ball_6_val->setText(_dataList[offset_4]);
		}
		else {
			ui->ball_6_val->setText("");
		}
		int offset_5 = offset_4 + 1;
		if (_dataList.size() > offset_5) {
			ui->ball_7_val->setText(_dataList[offset_5]);
		}
		else {
			ui->ball_7_val->setText("");
		}
		int offset_6 = offset_5 + 1;
		if (_dataList.size() > offset_6) {
			ui->ball_8_val->setText(_dataList[offset_6]);
		}
		else {
			ui->ball_8_val->setText("");
		}
		int offset_7 = offset_6 + 1;
		if (_dataList.size() > offset_7) {
			ui->ball_9_val->setText(_dataList[offset_7]);
		}
		else {
			ui->ball_9_val->setText("");
		}


		
		/*ui->ball_3_val->setText(_dataList[++offset]);
		ui->ball_4_val->setText(_dataList[++offset]);
		ui->ball_5_val->setText(_dataList[++offset]);
		ui->ball_6_val->setText(_dataList[++offset]);
		ui->ball_7_val->setText(_dataList[++offset]);
		ui->ball_8_val->setText(_dataList[++offset]);
		ui->ball_9_val->setText(_dataList[++offset]);*/
	}

	//



	ui->btnBall_up->setText(u8"（第" + QString::number(_pageCur) + u8"页）上一页");
	ui->btnBall_down->setText(u8"（第" + QString::number(_pageCur) + u8"页）下一页");




}

//执行
void CDlgBallheadCamera::send_selLayoutType(QString str) {

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt)  return;

	ConfLayoutParam  confLayoutParam = { 0 };
	//confLayoutParam = pTc->videoConference.confLayoutParam;
	//if (!confLayoutParam.ui64Id)  break;
	//
	if (str.isEmpty()) return;
	QStringList list = str.split("|");

	confLayoutParam.enlargeParam.usEnlargeType = CONST_enlargeType_img;
	confLayoutParam.enlargeParam.ui64Id = pProcInfo->m_ipcProc.op.idInfo.ui64Id;
	confLayoutParam.ipcParam.iChannel = list[0].toInt();
	pProcInfo->m_ipcProc.op.iChannel = list[0].toInt();

	CHelp_getDlgTalkVar help_getDlgTalkVar;
	CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)m_pParent;

	DLG_TALK_var* pm_var = pWin_cdlgtalk->get_pm_var();
	if (!pm_var)return;
	if (isTalkerShadowMgr(pm_var->addr)) return;
	TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
	HWND  hMgr = pShadowInfo->hMgr;

	do {
		
		//DLG_TALK_var* pDlgTalkVar = pWin_cdlgtalk->get_pm_var();
		DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hMgr);
		if (!pDlgTalkVar)break;
		if (!isTalkerShadowMgr(pDlgTalkVar->addr)) break;
		if (!pDlgTalkVar->av.taskInfo.bTaskExists) break;

		QY_MESSENGER_ID  idInfo_to = pDlgTalkVar->av.taskInfo.idInfo_starter;

		//
		QY_MESSENGER_ID  idInfo_imGrp_related = pDlgTalkVar->addr.idInfo;
		QY_MESSENGER_ID  idInfo_requester = pMisCnt->idInfo;

		//CONST_imOp_phone_enlargeChannel
		//sendConfLayout(false ,0, CONST_imOp_enlargeChannel, &confLayoutParam, idInfo_imGrp_related, idInfo_requester, idInfo_to, _T(""));
		sendConfLayout(false, 0, CONST_imOp_enlargeChannel, &confLayoutParam, idInfo_imGrp_related, idInfo_requester, idInfo_to, _T(""));

		//

	} while (false);


	on_btnBall_close_clicked();

	QString tmp_str = list[2];
	//调出云台窗口
	if (tmp_str.contains(u8"球机") || tmp_str.contains(u8"3D") || tmp_str.contains(u8"布控球")) {
		pWin_cdlgtalk->on_showControlPtz_slots(tmp_str);
	}
}





//下箭头
void CDlgBallheadCamera::Infrared_down()
{
	/*cw--
	if (chkFocus(this))return;
	this->focusNextPrevChild(true);
	*/
}

//上箭头
void CDlgBallheadCamera::Infrared_up()
{
	/*cw--
	if (chkFocus(this))return;
	this->focusNextPrevChild(false);
	*/
}
