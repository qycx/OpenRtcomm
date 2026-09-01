#include	"stdafx.h"
#include "CDlgControlPtzLocal.h"
//
//#include <qdesktopwidget.h>
#include	<qscreen.h>

#include	"qyMcMainCommon_qt.h"
#include	"ctxQmc_sm.h"
#include  "CDlgTalk_qt.h"


CDlgControlPtzLocal::CDlgControlPtzLocal(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::CDlgControlPtzLocalClass)
{
	ui->setupUi(this);

	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);


	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setWindowOpacity(0.7);

	m_pParent = parent;

	sheetBackgroundImage();

	QRect rc = QApplication::primaryScreen()->geometry();
	move(rc.width() - this->width(), 0); //将窗口移动到屏幕右侧 
}

CDlgControlPtzLocal::~CDlgControlPtzLocal()
{
	int i = 1;
}

//²¼¾Ö
void CDlgControlPtzLocal::sheetBackgroundImage() {

	QRect rc = QApplication::primaryScreen()->geometry();

	ui->lab_title->setAlignment(Qt::AlignCenter);

	if (rc.width() > 3500) {

		ui->lab_title->setStyleSheet("font-size:54px;font-weight:bold;background:#1E2747;color:#fff;font-family: Microsoft YaHei;");
		//
		resize(500, 700);

		ui->widget->setStyleSheet("QWidget#widget{border-radius:10px;} QPushButton{border-bottom:2px solid #000;background:#1E2747;font-size:68px;color:#fff;font-family: Microsoft YaHei;}QPushButton:focus {font-family: Microsoft YaHei;background:#1A54F1;color:#fff}");

	}
	else {

		ui->lab_title->setStyleSheet("font-size:28px;font-weight:bold;color:#fff;background:#1E2747;font-family: Microsoft YaHei;");

		ui->widget->setStyleSheet("QWidget#widget{border-radius:10px;} QPushButton{border-bottom:2px solid #000;background:#1E2747;font-size:28px;color:#fff;font-family: Microsoft YaHei;}QPushButton:focus {font-family: Microsoft YaHei;background:#1A54F1;color:#fff}");

	}


}




void CDlgControlPtzLocal::on_btnPtz_up_clicked()
{

	int nID = IDC_BUTTON_UP;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	pProcInfo->m_ipcProc.op.nID = nID;
	pProcInfo->m_ipcProc.op.iChannel = 1;
	//

	if (!is_btnUPDown_up) {
		check_btn_upDown_event();
		dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown, true);
		is_btnUPDown_up = true;
		ui->btnPtz_up->setText(u8"停止");
	}
	else {
		dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp, true);
		is_btnUPDown_up = false;
		ui->btnPtz_up->setText(u8"上");
	}

}


void CDlgControlPtzLocal::on_btnPtz_down_clicked()
{
	int nID = IDC_BUTTON_DOWN;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	pProcInfo->m_ipcProc.op.nID = nID;
	pProcInfo->m_ipcProc.op.iChannel = 1;



	if (!is_btnUPDown_down) {
		check_btn_upDown_event();
		dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown,true);
		is_btnUPDown_down = true;
		ui->btnPtz_down->setText(u8"停止");
	}
	else {
		dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp ,true);
		is_btnUPDown_down = false;
		ui->btnPtz_down->setText(u8"下");
	}

}

void CDlgControlPtzLocal::on_btnPtz_left_clicked()
{
	int nID = IDC_BUTTON_LEFT;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	pProcInfo->m_ipcProc.op.nID = nID;
	pProcInfo->m_ipcProc.op.iChannel = 1;


	if (!is_btnUPDown_left) {
		check_btn_upDown_event();
		dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown,true);
		is_btnUPDown_left = true;
		ui->btnPtz_left->setText(u8"停止");
	}
	else {
		dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp,true);
		is_btnUPDown_left = false;
		ui->btnPtz_left->setText(u8"左");
	}
}

void CDlgControlPtzLocal::on_btnPtz_right_clicked()
{
	int nID = IDC_BUTTON_RIGHT;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	pProcInfo->m_ipcProc.op.nID = nID;
	pProcInfo->m_ipcProc.op.iChannel = 1;

	if (!is_btnUPDown_right) {

		check_btn_upDown_event();

		dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown,true);
		is_btnUPDown_right = true;
		ui->btnPtz_right->setText(u8"停止");
	}
	else {
		dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp,true);
		is_btnUPDown_right = false;
		ui->btnPtz_right->setText(u8"右");
	}
}

void CDlgControlPtzLocal::on_btnPtz_zoomUp_clicked()
{
	int nID = IDC_BUTTON_ZOOM_IN;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	pProcInfo->m_ipcProc.op.nID = nID;
	pProcInfo->m_ipcProc.op.iChannel = 1;

	if (!is_btnUPDown_zoomUp) {

		check_btn_upDown_event();

		dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown , true);
		is_btnUPDown_zoomUp = true;
		ui->btnPtz_zoomUp->setText(u8"停止");
	}
	else {
		dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp , true);
		is_btnUPDown_zoomUp = false;
		ui->btnPtz_zoomUp->setText(u8"变倍+");
	}
}

void CDlgControlPtzLocal::on_btnPtz_zoomDown_clicked()
{
	int nID = IDC_BUTTON_ZOOM_OUT;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	pProcInfo->m_ipcProc.op.nID = nID;
	pProcInfo->m_ipcProc.op.iChannel = 1;

	if (!is_btnUPDown_zoomDown) {

		check_btn_upDown_event();

		dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown , true);
		is_btnUPDown_zoomDown = true;
		ui->btnPtz_zoomDown->setText(u8"停止");
	}
	else {
		dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp,true);
		is_btnUPDown_zoomDown = false;
		ui->btnPtz_zoomDown->setText(u8"变倍-");
	}
}

void CDlgControlPtzLocal::on_btnPtz_focusUp_clicked()
{
	int nID = IDC_BUTTON_FOCUS_IN;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	pProcInfo->m_ipcProc.op.nID = nID;
	pProcInfo->m_ipcProc.op.iChannel = 1;

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown , true);

	Sleep(200);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp , true);
}
void CDlgControlPtzLocal::on_btnPtz_focusDown_clicked()
{
	int nID = IDC_BUTTON_FOCUS_OUT;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	pProcInfo->m_ipcProc.op.nID = nID;
	pProcInfo->m_ipcProc.op.iChannel = 1;

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown,true);

	Sleep(200);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp ,true);
}
void CDlgControlPtzLocal::on_btnPtz_haloUp_clicked()
{
	int nID = IDC_BUTTON_IRIS_IN;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	pProcInfo->m_ipcProc.op.nID = nID;
	pProcInfo->m_ipcProc.op.iChannel = 1;

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown , true);

	Sleep(200);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp , true);
}
void CDlgControlPtzLocal::on_btnPtz_haloDown_clicked()
{
	int nID = IDC_BUTTON_IRIS_OUT;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	pProcInfo->m_ipcProc.op.nID = nID;
	pProcInfo->m_ipcProc.op.iChannel = 1;

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown,true);

	Sleep(200);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp,true);
}

void CDlgControlPtzLocal::on_btnPtz_close_clicked()
{
	CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)m_pParent;

	pWin_cdlgtalk->on_closeControlPtzLocal_slots();
	return;
}

//检测按键是否有未完成的 
void CDlgControlPtzLocal::check_btn_upDown_event() {

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



void CDlgControlPtzLocal::dlg_YTBtn_remote( unsigned  char  ucMouseStatus , bool is_local ) {

	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	int  iChannel = pProcInfo->m_ipcProc.op.iChannel;

	int nResourceID = pProcInfo->m_ipcProc.op.nID;

	int ucCmd = getPtzCmdByResourceId(nResourceID);

	OnvifMsg_ptz  m = { 0 };
	m.uiType = CONST_qisMsgType_onvif;
	m.iSubtype = CONST_onvifMsg_subtype_ptz;
	m.iChannel = iChannel;
	m.ucCmd = ucCmd;
	
	if (is_local) {
		m.ucMouseStatus = ucMouseStatus;
	}
	else {
		m.ucMouseStatus = pProcInfo->m_ipcProc.op.ucMouseStatus;
	}
	



	qisPipe_writeMsg(&m, sizeof(m), pProcInfo->m_ipcProc.pQisPipe);
}


void CDlgControlPtzLocal::dlg_YTBtn_remote_3ddw( PTZ_control_cmd  *  pPtzControlCmd  ) {

	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	if (!pPtzControlCmd)  return;

#if 0
	int  iChannel = pProcInfo->m_ipcProc.op.iChannel;

	int nResourceID = pProcInfo->m_ipcProc.op.nID;

	int ucCmd = getPtzCmdByResourceId(nResourceID);
#endif 

	//
	int  iChannel = pPtzControlCmd->cmdInfo.iChannel;
	int  ucCmd = pPtzControlCmd->cmdInfo.ucCmd;

	//
	OnvifMsg_ptz  m = { 0 };
	m.uiType = CONST_qisMsgType_onvif;
	m.iSubtype = CONST_onvifMsg_subtype_ptz;
	m.iChannel = iChannel;
	m.ucCmd = ucCmd;
	//
	m.paramU = pPtzControlCmd->paramU;

	//
	qisPipe_writeMsg(&m, sizeof(m), pProcInfo->m_ipcProc.pQisPipe);

	return;
}






int CDlgControlPtzLocal::getPtzCmdByResourceId(int nResourceID) 
{
	int ucCmd = 0;

	switch (nResourceID) {
	case  IDC_BUTTON_UP:
		ucCmd = CONST_ptzCmd_up;
		break;
	case  IDC_BUTTON_DOWN:
		ucCmd = CONST_ptzCmd_down;
		break;
	case  IDC_BUTTON_LEFT:
		ucCmd = CONST_ptzCmd_left;
		break;
	case  IDC_BUTTON_RIGHT:
		ucCmd = CONST_ptzCmd_right;
		break;
	case  IDC_BUTTON_TOP_LEFT:
		ucCmd = CONST_ptzCmd_topLeft;
		break;
	case  IDC_BUTTON_TOP_RIGHT:
		ucCmd = CONST_ptzCmd_topRight;
		break;
	case  IDC_BUTTON_BOTTOM_LEFT:
		ucCmd = CONST_ptzCmd_bottomLeft;
		break;
	case  IDC_BUTTON_BOTTOM_RIGHT:
		ucCmd = CONST_ptzCmd_bottomRight;
		break;

		//  2013/04/07
	case  IDC_BUTTON_noop:
		ucCmd = CONST_ptzCmd_noop;
		break;

		//
	case  IDC_BUTTON_FOCUS_IN:
		ucCmd = CONST_ptzCmd_focusIn;
		break;
	case  IDC_BUTTON_FOCUS_OUT:
		ucCmd = CONST_ptzCmd_focusOut;
		break;

	case  IDC_BUTTON_IRIS_IN:
		ucCmd = CONST_ptzCmd_irisIn;
		break;
	case  IDC_BUTTON_IRIS_OUT:
		ucCmd = CONST_ptzCmd_irisOut;
		break;

	case  IDC_BUTTON_ZOOM_IN:
		ucCmd = CONST_ptzCmd_zoomIn;
		break;
	case  IDC_BUTTON_ZOOM_OUT:
		ucCmd = CONST_ptzCmd_zoomOut;
		break;

	default:
		break;
	}

	return ucCmd;
}