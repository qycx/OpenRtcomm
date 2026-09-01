#include	"stdafx.h"

#include "CDlgControlPtzLocal.h"

#include	"qyMcMainCommon.h"


#include	"dlgTalkProc.h"

#include	"ptzFunc.h"

#include	"CMainFrame.h"
#include <help_getDlgTalkVar.h>

int getResourceIdByPtzCmd(int ucCmd)
{
	int nResourceID = 0;

	switch (ucCmd) {
	case  CONST_ptzCmd_up:
		nResourceID = IDC_BUTTON_UP;
		break;
	case  CONST_ptzCmd_down:
		nResourceID = IDC_BUTTON_DOWN;
		break;
	case  CONST_ptzCmd_left:
		nResourceID = IDC_BUTTON_LEFT;
		break;
	case  CONST_ptzCmd_right:
		nResourceID = IDC_BUTTON_RIGHT;
		break;
	case  CONST_ptzCmd_topLeft:
		nResourceID = IDC_BUTTON_TOP_LEFT;
		break;
	case  CONST_ptzCmd_topRight:
		nResourceID = IDC_BUTTON_TOP_RIGHT;
		break;
	case  CONST_ptzCmd_bottomLeft:
		nResourceID = IDC_BUTTON_BOTTOM_LEFT;
		break;
	case  CONST_ptzCmd_bottomRight:
		nResourceID = IDC_BUTTON_BOTTOM_RIGHT;
		break;

		//  2013/04/07
	case  CONST_ptzCmd_noop:
		nResourceID = IDC_BUTTON_noop;
		break;

		//
	case  CONST_ptzCmd_focusIn:
		nResourceID = IDC_BUTTON_FOCUS_IN;
		break;
	case  CONST_ptzCmd_focusOut:
		nResourceID = IDC_BUTTON_FOCUS_OUT;
		break;

	case  CONST_ptzCmd_irisIn:
		nResourceID = IDC_BUTTON_IRIS_IN;
		break;
	case  CONST_ptzCmd_irisOut:
		nResourceID = IDC_BUTTON_IRIS_OUT;
		break;

	case  CONST_ptzCmd_zoomIn:
		nResourceID = IDC_BUTTON_ZOOM_IN;
		break;
	case  CONST_ptzCmd_zoomOut:
		nResourceID = IDC_BUTTON_ZOOM_OUT;
		break;

	default:
		break;
	}

	return nResourceID;
}

//void dlg_YTCmd(  HWND  hDlg_ptz,  int  nResourceID,  int  lStep_percent  )
void dlg_YTCmd(HWND  hDlg_ptz, int  nResourceID, int  lStep_percent, unsigned  char ucMouseStatus, int iChannel)
{
	//MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	//
	CDlgControlPtzLocal* pDlg = (CDlgControlPtzLocal*)QWidget::find((WId)hDlg_ptz);
	if (!pDlg)  return;

	//  2014/09/13
	/*if (pDlg->m_var.bRemote) {
		return;
	}*/

	//  2014/10/14
	//pDlg->m_var.dwTickCnt_lastPtzCmdRecvd = GetTickCount();

	//
	//if (pDlg->m_var.local.resObj_camera.uiObjType == CONST_objType_rtspStream) {
	//	PARAM_viewLocalPtzControl* pParam = &pDlg->m_var.local.param;
	//	if (pParam->pf_dlg_YTCmd) {
	//		pParam->pf_dlg_YTCmd(hDlg_ptz, nResourceID, pParam->p0, pParam->p1);
	//	}
	//	return;
	//}

	//int ptzCmd = pDlg->getPtzCmdByResourceId(nResourceID);
	//dlg_YTCmd_ipc(hDlg_ptz, iChannel, IDC_BUTTON_UP, ucMouseStatus);
	pDlg->dlg_YTBtn_remote(ucMouseStatus);
	//
	//switch (pDlg->m_var.iPtzType) {
	//case  CONST_ptzType_usb:
	//	dlg_YTCmd_usb(hDlg_ptz, nResourceID);
	//	break;
	//case  CONST_ptzType_serialPort:
	//	dlg_YTCmd_pelco(hDlg_ptz, nResourceID);
	//	break;
	//case  CONST_ptzType_ipc: {
//int iChannel = pProcInfo->m_ipcProc.op.iChannel;
	//	
	//}
	//					   break;
	//default:
	//	break;
	//}

	return;
}




//
__declspec(dllexport)  int doRemotePtzCmd(void* p0, PTZ_control_cmd* pReq, PARAM_viewLocalPtzControl* pParam, QIS_ptz_wnd* pPtzWnd)
{

	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	TCHAR				tBuf[128] = _T("");
	if (!pProcInfo)  return  -1;

	//
	unsigned  int  uiObjType_camera = pReq->cmdInfo.obj.uiObjType;
	//
	//QIS_ptz_wnd  *  pPtzWnd  =  &pProcInfo->ptzWnd;

#ifdef  __DEBUG__
		//
	//traceLog(_T("doRemotePtzCmd: cmd %d %s"), (int)pReq->cmdInfo.ucCmd, qyGetDesByType1(CONST_ptzCmdTable_en, pReq->cmdInfo.ucCmd));
#endif
	//



	//
	if (!IsWindow(pPtzWnd->hWnd_localPtzControl)) {
		HWND hParent = pQyMc->gui.hMainWnd;
		BOOL  bManual = FALSE;					//  2014/10/14
		//
		viewLocalPtzControl(hParent, bManual, uiObjType_camera, pReq->cmdInfo.obj.usIndex_obj, pReq->cmdInfo.obj.usHelp_subIndex, pParam, pPtzWnd);
		if (!IsWindow(pPtzWnd->hWnd_localPtzControl))  return -1;
	}
	//
	HWND  hWnd_ptz = pPtzWnd->hWnd_localPtzControl;
	/*CDlgPtzControl* pDlg = NULL;
	pDlg = (CDlgPtzControl*)CWnd::FromHandlePermanent(hWnd_ptz);
	if (!pDlg)  goto  errLabel;*/
	//
	int  nID = 0;
	//nID = (int)qyGetDesByType(CONST_ptzCmd2ButtonTable, pReq->cmdInfo.ucCmd);

	 nID = getResourceIdByPtzCmd(pReq->cmdInfo.ucCmd);

	pProcInfo->m_ipcProc.op.nID = nID;

	pProcInfo->m_ipcProc.op.iChannel = pReq->cmdInfo.iChannel;


	pProcInfo->m_ipcProc.op.ucMouseStatus = pReq->cmdInfo.ucMouseStatus;

	//
	//
	int  lStep_percent = 0;
	//
	//lStep_percent = pDlg->m_slider_speed.GetPos();
	//i
#ifdef  __DEBUG__
	//traceLog(_T("Not finished: "));
#endif
	//
	dlg_YTCmd(hWnd_ptz, nID, lStep_percent, pReq->cmdInfo.ucMouseStatus, pReq->cmdInfo.iChannel);




	return  0;
}



//
__declspec(dllexport) int  viewLocalPtzControl(HWND  hParent, BOOL  bManual, unsigned  int  uiObjType_camera, unsigned  short  usIndex_obj, unsigned  short  usHelp_subIndex, PARAM_viewLocalPtzControl* pParam, QIS_ptz_wnd* pPtzWnd)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr = -1;

	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;

	CDlgControlPtzLocal* pDlg = NULL;
	RECT							rect;

	HWND* phWnd_lv = NULL;

	


	//
	phWnd_lv = &pPtzWnd->hWnd_localPtzControl;

	if (phWnd_lv) {
		if (IsWindow(*phWnd_lv)) {
			if (bManual) {
	//			//
				CDlgControlPtzLocal* tmp_p = (CDlgControlPtzLocal*)QWidget::find((WId)phWnd_lv );
				if (!tmp_p) {
					goto  errLabel;
				}
	//			if (!tmp_p->m_var.local.bManual) {
	//				tmp_p->m_var.local.bManual = bManual;
	//			}*/
	//			//
	//			//MACRO_SetForegroundWindow(*phWnd_lv);
			}
			iErr = 0;  goto  errLabel;
		}

		*phWnd_lv = NULL;
	}

	//
	pDlg = new  CDlgControlPtzLocal(QWidget::find((WId)hParent));
	if (!pDlg)   goto  errLabel;

	////  2014/10/14
	//if (bManual) {
	//	pDlg->m_var.local.bManual = bManual;
	//}
	////  2016/07.20
	//pDlg->m_var.local.resObj_camera.uiObjType = uiObjType_camera;
	//pDlg->m_var.local.resObj_camera.usIndex_obj = usIndex_obj;
	//pDlg->m_var.local.resObj_camera.usHelp_subIndex = usHelp_subIndex;
	////
	//if (pParam)  pDlg->m_var.local.param = *pParam;
	////  2016/07/20
	//pDlg->pPtzWnd = pPtzWnd;
	////
	////  2015/09/18
	//pDlg->m_var.m_nID = IDD_ptzControl_local;

	////
	//if (!pDlg->Create(rect))  goto  errLabel;
	//if (bManual) {
		//pDlg->show();
	//}

	////
	if (phWnd_lv)  *phWnd_lv = (HWND)pDlg->winId();
	//if (phWnd_lv)  *phWnd_lv = hParent;


	iErr = 0;

errLabel:
//
	if (iErr) {
			if (pDlg)  delete  pDlg;
	}



	return  iErr;
}


