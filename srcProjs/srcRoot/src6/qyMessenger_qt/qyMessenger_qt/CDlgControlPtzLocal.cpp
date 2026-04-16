#include	"stdafx.h"
#include "CDlgControlPtzLocal.h"

//#include <qdesktopwidget.h>
#include	<qscreen>

#include	"qyMcMainCommon_qt.h"
#include	"ctxQmc_qt.h"
#include  "CDlgTalk_qt.h"


CDlgControlPtzLocal::CDlgControlPtzLocal(QWidget* parent)
	: QDialog(parent),
	ui(new Ui::CDlgControlPtzLocalClass)
{
	ui->setupUi(this);
}

CDlgControlPtzLocal::~CDlgControlPtzLocal()
{
	int i = 1;
}

//²¼¾Ö
void CDlgControlPtzLocal::sheetBackgroundImage() {

	//QRect rc = QApplication::desktop()->screenGeometry();
	QRect rc = QApplication::primaryScreen()->geometry();

	//
	ui->lab_title->setAlignment(Qt::AlignCenter);

	if (rc.width() > 3500) {

		ui->lab_title->setStyleSheet("font-size:54px;font-weight:bold;color:#fff;font-family: Microsoft YaHei;");
		////ui->widget->setStyleSheet("QWidget#widget{background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30);}QPushButton{color:#fff;background:#5C8CFC;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

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
		////ui->label_title->setStyleSheet("font-size:84px;color:#fff;font-weight:bold;background:none;font-family: Microsoft YaHei;");
		////ui->widget->setContentsMargins(20, 20, 20, 20);



	}
	else {
		//resize(500, 700);
		//ui->lab_title->setHeight(30);
		ui->lab_title->setStyleSheet("font-size:28px;font-weight:bold;color:#fff;background:#1E2747;font-family: Microsoft YaHei;");
		////ui->widget->setStyleSheet("QWidget#widget{background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30);}QPushButton{color:#fff;background:#5C8CFC;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");


		ui->widget->setStyleSheet("QWidget#widget{border-radius:10px;} QPushButton{border-bottom:2px solid #000;background:#1E2747;font-size:28px;color:#fff;font-family: Microsoft YaHei;}QPushButton:focus {font-family: Microsoft YaHei;background:#1A54F1;color:#fff}");
		////ui->label_title->setStyleSheet("font-size:42px;color:#fff;font-weight:bold;background:none;font-family: Microsoft YaHei;");



		//int h_i = 60;
		//int w_i = 700;
		//ui->widget->setFixedWidth(w_i);


	}

}




void CDlgControlPtzLocal::on_btnPtz_up_clicked()
{



	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown, true);

	Sleep(100);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp, true);


}


void CDlgControlPtzLocal::on_btnPtz_down_clicked()
{
	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown, true);

	Sleep(100);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp, true);

}

void CDlgControlPtzLocal::on_btnPtz_left_clicked()
{
	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown, true);

	Sleep(100);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp, true);
}

void CDlgControlPtzLocal::on_btnPtz_right_clicked()
{
	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown, true);

	Sleep(100);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp, true);
}

void CDlgControlPtzLocal::on_btnPtz_zoomUp_clicked()
{
	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown, true);

	Sleep(100);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp, true);
}

void CDlgControlPtzLocal::on_btnPtz_zoomDown_clicked()
{
	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown, true);

	Sleep(100);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp, true);
}

void CDlgControlPtzLocal::on_btnPtz_focusUp_clicked()
{
	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown, true);

	Sleep(100);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp, true);
}
void CDlgControlPtzLocal::on_btnPtz_focusDown_clicked()
{
	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown, true);

	Sleep(100);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp, true);
}
void CDlgControlPtzLocal::on_btnPtz_haloUp_clicked()
{
	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown, true);

	Sleep(100);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp, true);
}
void CDlgControlPtzLocal::on_btnPtz_haloDown_clicked()
{
	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown, true);

	Sleep(100);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp, true);
}

void CDlgControlPtzLocal::on_btnPtz_close_clicked()
{
	dlg_YTBtn_remote(CONST_mouseStatus_lBtnDown, true);

	Sleep(100);

	dlg_YTBtn_remote(CONST_mouseStatus_lBtnUp, true);
}


void CDlgControlPtzLocal::dlg_YTBtn_remote(unsigned  char  ucMouseStatus, bool is_local) {

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



void CDlgControlPtzLocal::dlg_YTBtn_remote_3ddw(PTZ_control_cmd* pPtzControlCmd) {

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