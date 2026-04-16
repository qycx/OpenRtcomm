#include	"stdafx.h"
#include "CDlgControlPtzLocal.h"




CDlgControlPtzLocal::CDlgControlPtzLocal(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::CDlgControlPtzLocalClass)
{
	ui->setupUi(this);
}

CDlgControlPtzLocal::~CDlgControlPtzLocal()
{
	int i = 1;
}




void CDlgControlPtzLocal::dlg_YTBtn_remote( unsigned  char  ucMouseStatus , bool is_local ) {

	/*CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
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
	



	qisPipe_writeMsg(&m, sizeof(m), pProcInfo->m_ipcProc.pQisPipe);*/
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