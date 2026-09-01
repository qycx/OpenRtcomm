#include	"stdafx.h"
#include "CDlgControlPtz.h"
//
//#include <qdesktopwidget.h>
#include	<qscreen.h>

#include	"qyMcMainCommon_qt.h"
//#include	"ctxQmc_sm.h"
//#include	"smProc_qt.h"
#include  "CDlgTalk_qt.h"
#include <qlist.h>
#include	"funcsforIsCliHelp.h"
#include	"ptzFunc.h"

CDlgControlPtz::CDlgControlPtz(bool b3dLocation, QWidget *parent)
	: QDialog(parent),
	ui(new Ui::CDlgControlPtzClass)
{
	ui->setupUi(this);

	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);


	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setWindowOpacity(0.7);
	//QCursor::setPos(0, 0);
	m_pParent = parent;

	sheetBackgroundImage();

	//QRect rc = QApplication::desktop()->screenGeometry();
	QRect rc = QApplication::primaryScreen()->geometry();
	//
	move(rc.width() - this->width() ,0); //将窗口移动到屏幕右侧 
	

	ui->btnPtz_up->setFocus();

	

	if (b3dLocation)
		ui->btnPtz_3d->setVisible(true);
	else
		ui->btnPtz_3d->setVisible(false);

	set3D(b3dLocation);


	ui->btnPtz_up->installEventFilter(this);
	ui->btnPtz_down->installEventFilter(this);
	ui->btnPtz_left->installEventFilter(this);
	ui->btnPtz_right->installEventFilter(this);
	ui->btnPtz_zoomUp->installEventFilter(this);
	ui->btnPtz_zoomDown->installEventFilter(this);

}

bool CDlgControlPtz::eventFilter(QObject* watched, QEvent* event)
{

	


	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (watched == ui->btnPtz_up) {		

		int nID = IDC_BUTTON_UP;
		pProcInfo->m_ipcProc.op.nID = nID;

		if (event->type() == QEvent::MouseButtonPress) {
			

			dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
			dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown);
			is_btnUPDown_up = true;
			
		}
		else if (event->type() == QEvent::MouseButtonRelease) {
			
			dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
			is_btnUPDown_up = false;
		}
	} else if (watched == ui->btnPtz_down) {
		int nID = IDC_BUTTON_DOWN;
		pProcInfo->m_ipcProc.op.nID = nID;

		if (event->type() == QEvent::MouseButtonPress) {
			dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
			dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown);
			is_btnUPDown_down = true;

		}
		else if (event->type() == QEvent::MouseButtonRelease) {
			dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
			is_btnUPDown_down = false;
		}
	}else if (watched == ui->btnPtz_left) {
		int nID = IDC_BUTTON_LEFT;
		pProcInfo->m_ipcProc.op.nID = nID;

		if (event->type() == QEvent::MouseButtonPress) {
			dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
			dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown);
			is_btnUPDown_left = true;

		}
		else if (event->type() == QEvent::MouseButtonRelease) {
			dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
			is_btnUPDown_left = false;
		}

		
	}
	else if (watched == ui->btnPtz_right) {
		int nID = IDC_BUTTON_RIGHT;
		pProcInfo->m_ipcProc.op.nID = nID;

		if (event->type() == QEvent::MouseButtonPress) {
			dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
			dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown);
			is_btnUPDown_right = true;

		}
		else if (event->type() == QEvent::MouseButtonRelease) {
			dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
			is_btnUPDown_right = false;
		}


	}
	else if (watched == ui->btnPtz_zoomUp) {
		int nID = IDC_BUTTON_ZOOM_IN;
		pProcInfo->m_ipcProc.op.nID = nID;

		if (event->type() == QEvent::MouseButtonPress) {
			dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
			dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown);
			is_btnUPDown_zoomUp = true;

		}
		else if (event->type() == QEvent::MouseButtonRelease) {
			dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
			is_btnUPDown_zoomUp = false;
		}


	}
	else if (watched == ui->btnPtz_zoomDown) {
		int nID = IDC_BUTTON_ZOOM_OUT;
		pProcInfo->m_ipcProc.op.nID = nID;

		if (event->type() == QEvent::MouseButtonPress) {
			dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
			dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown);
			is_btnUPDown_zoomDown = true;

		}
		else if (event->type() == QEvent::MouseButtonRelease) {
			dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
			is_btnUPDown_zoomDown = false;
		}


	}


	


	return QWidget::eventFilter(watched, event);
}

void CDlgControlPtz::set3D(bool flag)
{
	if (flag) {
		ui->btnPtz_3d->setText(u8"关3D(on)");
		m_3dLocation = true;
	}
	else {
		ui->btnPtz_3d->setText(u8"开3D(off)");
		m_3dLocation = false;
	}

}

void CDlgControlPtz::on_btnPtz_3d_clicked()
{
	if (m_3dLocation) {
		m_3dLocation = false;
		ui->btnPtz_3d->setText(u8"开3D(off)");
	}
	else {
		m_3dLocation = true;
		ui->btnPtz_3d->setText(u8"关3D(on)");
	}

	CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)m_pParent;

	if(pWin_cdlgtalk)
		pWin_cdlgtalk->on_click3dPtz_slots(m_3dLocation);
	
}

//布局
void CDlgControlPtz::sheetBackgroundImage() {

	QRect rc = QApplication::primaryScreen()->geometry();

	ui->lab_title->setAlignment(Qt::AlignCenter);

	if (rc.width() > 3500) {

		//ui->lab_title->setStyleSheet("font-size:54px;font-weight:bold;background:#1E2747;color:#fff;font-family: Microsoft YaHei;");
		ui->lab_title->setStyleSheet("font-size:26px;font-weight:bold;background:#1E2747;color:#fff;font-family: Microsoft YaHei;");
		////ui->widget->setStyleSheet("QWidget#widget{background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30);}QPushButton{color:#fff;background:#5C8CFC;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");
		resize(500, 700);
		//ui->widget->setFixedSize();
		//int w_i = 1600;
		//int h_i = 200;
		//ui->lab_title->setFixedSize(w_i, h_i);
		//ui->btnBall_Amp_off->setFixedSize(w_i, h_i);
		//ui->btnBall_up->setFixedSize(w_i, h_i);
		//ui->btnBall_2->setFixedSize(w_i, h_i);
		//ui->btnBall_3->setFixedSize(w_i, h_i);
		//ui->btnBall_4->setFixedSize(w_i, h_i);
		//ui->btnBall_5->setFixedSize(w_i, h_i);
		//ui->btnBall_6->setFixedSize(w_i, h_i);
		//ui->btnBall_7->setFixedSize(w_i, h_i);
		//ui->btnBall_8->setFixedSize(w_i, h_i);
		//ui->btnBall_9->setFixedSize(w_i, h_i);
		//ui->btnBall_down->setFixedSize(w_i, h_i);
		//ui->btnBall_close->setFixedSize(w_i, h_i);

		//ui->widget->setStyleSheet("QWidget#widget{border-radius:10px;} QPushButton{border-bottom:2px solid #000;background:#1E2747;font-size:68px;color:#fff;font-family: Microsoft YaHei;}QPushButton:focus {font-family: Microsoft YaHei;background:#1A54F1;color:#fff}");
		ui->widget->setStyleSheet("QWidget#widget{border-radius:10px;} QPushButton{border-bottom:2px solid #000;background:#1E2747;font-size:34px;color:#fff;font-family: Microsoft YaHei;}QPushButton:focus {font-family: Microsoft YaHei;background:#1A54F1;color:#fff}");
		////ui->label_title->setStyleSheet("font-size:84px;color:#fff;font-weight:bold;background:none;font-family: Microsoft YaHei;");
		////ui->widget->setContentsMargins(20, 20, 20, 20);



	}
	else {
		//resize(500, 700);
		//ui->lab_title->setHeight(30);
		//ui->lab_title->setStyleSheet("font-size:28px;font-weight:bold;color:#fff;background:#1E2747;font-family: Microsoft YaHei;");
		ui->lab_title->setStyleSheet("font-size:18px;font-weight:bold;color:#fff;background:#000000;font-family: Microsoft YaHei;");
		////ui->widget->setStyleSheet("QWidget#widget{background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30);}QPushButton{color:#fff;background:#5C8CFC;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");


		//ui->widget->setStyleSheet("QWidget#widget{border-radius:10px;} QPushButton{border-bottom:2px solid #000;background:#1E2747;font-size:28px;color:#fff;font-family: Microsoft YaHei;}QPushButton:focus {font-family: Microsoft YaHei;background:#1A54F1;color:#fff}");
		ui->widget->setStyleSheet("QWidget#widget{border-radius:10px;} QPushButton{border-bottom:2px solid #000;background:#000000;font-size:18px;color:#fff;font-family: Microsoft YaHei;}QPushButton:focus {font-family: Microsoft YaHei;background:#1A54F1;color:#fff}");
		////ui->label_title->setStyleSheet("font-size:42px;color:#fff;font-weight:bold;background:none;font-family: Microsoft YaHei;");



		//int h_i = 60;
		//int w_i = 700;
		//ui->widget->setFixedWidth(w_i);


	}

}



//
//void CDlgControlPtz::on_btnPtz_up_clicked()
//{
//	int nID = IDC_BUTTON_UP;
//	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
//
//	pProcInfo->m_ipcProc.op.nID = nID;
//
//	//
//
//	if (!is_btnUPDown_up) {
//		check_btn_upDown_event();
//		dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown);
//		is_btnUPDown_up = true;
//		ui->btnPtz_up->setText(u8"停止");
//	}
//	else {
//		dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
//		is_btnUPDown_up = false;
//		ui->btnPtz_up->setText(u8"上");
//	}
//
//	
//
//	//Sleep(200);
//
//	
//
//
//}


//void CDlgControlPtz::on_btnPtz_down_clicked() 
//{
//
//	int nID = IDC_BUTTON_DOWN;
//	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
//
//	pProcInfo->m_ipcProc.op.nID = nID;
//
//
//	
//
//	if (!is_btnUPDown_down) {
//		check_btn_upDown_event();
//		dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown);
//		is_btnUPDown_down = true;
//		ui->btnPtz_down->setText(u8"停止");
//	}
//	else {
//		dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
//		is_btnUPDown_down = false;
//		ui->btnPtz_down->setText(u8"下");
//	}
//
//}

//void CDlgControlPtz::on_btnPtz_left_clicked()
//{
//	int nID = IDC_BUTTON_LEFT;
//	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
//
//	pProcInfo->m_ipcProc.op.nID = nID;
//
//	
//
//	if (!is_btnUPDown_left) {
//		check_btn_upDown_event();
//		dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown);
//		is_btnUPDown_left = true;
//		ui->btnPtz_left->setText(u8"停止");
//	}
//	else {
//		dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
//		is_btnUPDown_left = false;
//		ui->btnPtz_left->setText(u8"左");
//	}
//}
//
//void CDlgControlPtz::on_btnPtz_right_clicked()
//{
//	int nID = IDC_BUTTON_RIGHT;
//	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
//
//	pProcInfo->m_ipcProc.op.nID = nID;
//
//
//	if (!is_btnUPDown_right) {
//
//		check_btn_upDown_event();
//
//		dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown);
//		is_btnUPDown_right = true;
//		ui->btnPtz_right->setText(u8"停止");
//	}
//	else {
//		dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
//		is_btnUPDown_right = false;
//		ui->btnPtz_right->setText(u8"右");
//	}
//}
//
//void CDlgControlPtz::on_btnPtz_zoomUp_clicked()
//{
//	int nID = IDC_BUTTON_ZOOM_IN;
//	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
//
//	pProcInfo->m_ipcProc.op.nID = nID;
//
//	if (!is_btnUPDown_zoomUp) {
//
//		check_btn_upDown_event();
//
//		dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown);
//		is_btnUPDown_zoomUp = true;
//		ui->btnPtz_zoomUp->setText(u8"停止");
//	}
//	else {
//		dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
//		is_btnUPDown_zoomUp = false;
//		ui->btnPtz_zoomUp->setText(u8"变倍+");
//	}
//}
//
//void CDlgControlPtz::on_btnPtz_zoomDown_clicked()
//{
//	int nID = IDC_BUTTON_ZOOM_OUT;
//	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
//
//	pProcInfo->m_ipcProc.op.nID = nID;
//
//
//	if (!is_btnUPDown_zoomDown) {
//
//		check_btn_upDown_event();
//
//		dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown);
//		is_btnUPDown_zoomDown = true;
//		ui->btnPtz_zoomDown->setText(u8"停止");
//	}
//	else {
//		dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
//		is_btnUPDown_zoomDown = false;
//		ui->btnPtz_zoomDown->setText(u8"变倍-");
//	}
//}

void CDlgControlPtz::on_btnPtz_focusUp_clicked()
{
	int nID = IDC_BUTTON_FOCUS_IN;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	pProcInfo->m_ipcProc.op.nID = nID;

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown);

	//Sleep(200);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
}
void CDlgControlPtz::on_btnPtz_focusDown_clicked() 
{
	int nID = IDC_BUTTON_FOCUS_OUT;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	pProcInfo->m_ipcProc.op.nID = nID;

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown);

	Sleep(200);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
}
void CDlgControlPtz::on_btnPtz_haloUp_clicked()
{
	int nID = IDC_BUTTON_IRIS_IN;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	pProcInfo->m_ipcProc.op.nID = nID;

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown);

	Sleep(200);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
}
void CDlgControlPtz::on_btnPtz_haloDown_clicked()
{
	int nID = IDC_BUTTON_IRIS_OUT;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	pProcInfo->m_ipcProc.op.nID = nID;

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown);

	Sleep(200);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
}


//检测按键是否有未完成的 
void CDlgControlPtz::check_btn_upDown_event() {

	if (is_btnUPDown_up) {

		is_btnUPDown_up = false;
		ui->btnPtz_up->setText(u8"上");
	}

	if (is_btnUPDown_down) {
		is_btnUPDown_down = false;
		ui->btnPtz_down->setText(u8"下");
	}
	if (is_btnUPDown_left) {
		is_btnUPDown_left = false;
		ui->btnPtz_left->setText(u8"左");
	}
	if (is_btnUPDown_right) {
		is_btnUPDown_right = false;
		ui->btnPtz_right->setText(u8"右");
	}
	
	if (is_btnUPDown_zoomUp) {
		is_btnUPDown_zoomUp = false;
		ui->btnPtz_zoomUp->setText(u8"变倍+");
	}

	if (is_btnUPDown_zoomDown) {
		is_btnUPDown_zoomDown = false;
		ui->btnPtz_zoomDown->setText(u8"变倍-");
	}

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp);
}

//关闭云台窗口
void CDlgControlPtz::on_btnPtz_close_clicked()
{

	CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)m_pParent;

	pWin_cdlgtalk->on_closeControlPtz_slots();
	return;


}

//执行  发送MCU
void CDlgControlPtz::dlg_YTBtn_remote( unsigned  char  ucMouseStatus)
{


	//CDlgPtzControl* pDlg = (CDlgPtzControl*)CWnd::FromHandlePermanent(hDlg);
	//if (!pDlg)  return;

	 CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)m_pParent;

	DLG_TALK_var* pm_var = pWin_cdlgtalk->get_pm_var();
	if (!pm_var)return;
	/*if (isTalkerShadowMgr(pm_var->addr)) {
	
	}

	TALKER_shadow* pShadowInfo = (TALKER_shadow*)pm_var->pShadowInfo;
	HWND  hMgr = pShadowInfo->hMgr;*/




	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	//
	unsigned  int  uiObjType = 0;
	unsigned  short  usIndex_obj = 0;
	unsigned  short  usHelp_subIndex = 0;
	//
	unsigned  char	ucCmd = 0;
	unsigned  char  ucParam = 0;
	TCHAR	tBuf[128];
	//unsigned  char  ucMouseStatus = CONST_mouseStatus_lBtnDown;

	//  2016/07/19


	//
	QY_MESSENGER_ID  idInfo; idInfo = pProcInfo->m_ipcProc.op.idInfo;
	int  iChannel = pProcInfo->m_ipcProc.op.iChannel;

	int nResourceID = pProcInfo->m_ipcProc.op.nID;


	//
	QY_MESSENGER_ID  idInfo_imGrp_related = { 0 };

	//
	QY_MESSENGER_ID  idInfo_to = pm_var->addr.idInfo;
	idInfo_to = pProcInfo->m_ipcProc.op.idInfo;

	do {

		//
		if (idInfo_to.ui64Id == pMisCnt->idInfo.ui64Id) {
			//  发送到mcu上去
			//HWND  hCurTalk = (HWND)m_pParent;
			HWND  hCurTalk = (HWND)m_pParent->winId();
			CHelp_getDlgTalkVar help_getDlgTalkVar;
			DLG_TALK_var* pCurVar = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hCurTalk);
			if (!pCurVar)  break;
			HWND  hMgr = nullptr;
			if (isTalkerShadowMgr(pCurVar->addr)) {
				hMgr = hCurTalk;
			}
			else {
				TALKER_shadow* pShadow = (TALKER_shadow*)pCurVar->pShadowInfo;
				if (!pShadow) break;
				hMgr = pShadow->hMgr;
			}
			CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
			DLG_TALK_var* pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
			if (!pMgrVar)  break;
			//
			if (!pMgrVar->av.taskInfo.bTaskExists)  break;
			if (!pMgrVar->av.taskInfo.ucbVideoConference)  break;
			//
			idInfo_imGrp_related.ui64Id = pMgrVar->addr.idInfo.ui64Id;
			//
			idInfo_to = pMgrVar->av.taskInfo.idInfo_starter;

			//
		}


		//
		switch (nResourceID) {
		case  IDC_BUTTON_UP:
			ucCmd = CONST_ptzCmd_up;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_DOWN:
			ucCmd = CONST_ptzCmd_down;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_LEFT:
			ucCmd = CONST_ptzCmd_left;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_RIGHT:
			ucCmd = CONST_ptzCmd_right;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_TOP_LEFT:
			ucCmd = CONST_ptzCmd_topLeft;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_TOP_RIGHT:
			ucCmd = CONST_ptzCmd_topRight;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_BOTTOM_LEFT:
			ucCmd = CONST_ptzCmd_bottomLeft;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_BOTTOM_RIGHT:
			ucCmd = CONST_ptzCmd_bottomRight;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;

			//  2013/04/07
		case  IDC_BUTTON_noop:
			ucCmd = CONST_ptzCmd_noop;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;

			//
		case  IDC_BUTTON_FOCUS_IN:
			ucCmd = CONST_ptzCmd_focusIn;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_FOCUS_OUT:
			ucCmd = CONST_ptzCmd_focusOut;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;

		case  IDC_BUTTON_IRIS_IN:
			ucCmd = CONST_ptzCmd_irisIn;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_IRIS_OUT:
			ucCmd = CONST_ptzCmd_irisOut;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;

		case  IDC_BUTTON_ZOOM_IN:
			ucCmd = CONST_ptzCmd_zoomIn;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;
		case  IDC_BUTTON_ZOOM_OUT:
			ucCmd = CONST_ptzCmd_zoomOut;
			sendPtzReq(uiObjType, usIndex_obj, usHelp_subIndex, idInfo, iChannel, ucCmd, ucParam, ucMouseStatus, mynull,idInfo_imGrp_related, idInfo_to);
			break;

		default:
			break;
		}

	} while (false);

	//
	return;
}




CDlgControlPtz::~CDlgControlPtz()
{}


//下箭头
void CDlgControlPtz::Infrared_down()
{
	/*cw--
	if (chkFocus(this))return;
	this->focusNextPrevChild(true);
	*/
}

//上箭头
void CDlgControlPtz::Infrared_up()
{
	/*cw--
	if (chkFocus(this))return;
	this->focusNextPrevChild(false);
	*/
}
//左右光标移动
void CDlgControlPtz::Infrared_input_left_right(QString name, bool isLeft)
{

	if (isLeft) {

		if (name == "btnPtz_right") {
			this->focusNextPrevChild(false);
		}

	}
	else {

		if (name == "btnPtz_left") {
			this->focusNextPrevChild(true);
		}
	}

}