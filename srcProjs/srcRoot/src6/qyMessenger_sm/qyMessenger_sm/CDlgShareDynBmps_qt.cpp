#include "CDlgShareDynBmps_qt.h"

#include <QPushButton>


#include "qyAvRecordPublic.h"
#include "qmcShareDynBmp.h"

#include "GuiShare.h"
#include "qmcVideoCapture.h"
#include "qmcCommFunc_isCli.h"

//////qmcVideoCapture_dx///////

#include	"qyMcMainCommon.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
#include	<fcntl.h>
#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#include <locale> 
#include <codecvt> 

#ifndef  __WINCE__
#pragma include_alias( "dxtrans.h", "myqedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__

//  #include	<Qedit.h>
#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>

#include	"qmcDmoPublic.h"
#ifndef  __WINCE__
#include	"qmcVideoCapture_dx.h"
#endif

/////////qmcVideoCapture_dx///////////

#include "isCliHelpPublic.h"

#include "isCmdConst.h"

CDlgShareDynBmps_qt::CDlgShareDynBmps_qt(const std::string& rtspUrl, QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::CDlgShareDynBmps_qtClass())
{
	ui->setupUi(this);

	m_hWnd = (HWND)this->winId();

	m_rtspUrl = rtspUrl;

	memset(&m_var, 0, sizeof(m_var));
	memset(&m_varAVDev, 0, sizeof(m_varAVDev));
	//
	/*cw
	m_var.m_hParent = hParent;
	m_var.m_nID = CDlgShareDynBmps::IDD;

	//  2013/07/01
	m_var.guiData.iIDC_BUTTON_gps = IDC_BUTTON_gps;
	m_var.guiData.iIDC_STATIC_gpsStatus = IDC_STATIC_gpsStatus;
	m_var.guiData.iIDC_STATIC_pic0 = IDC_STATIC_pic0;
	//
	m_var.guiData.iIDC_BUTTON_hide = IDC_BUTTON_hide;
	m_var.guiData.iIDCANCAL = IDCANCEL;
	m_var.guiData.iIDC_BUTTON_add = IDC_BUTTON_add;
	m_var.guiData.iIDC_BUTTON_procRtsp = IDC_BUTTON_procRtsp;
	m_var.guiData.iIDC_BUTTON_del = IDC_BUTTON_del;
	m_var.guiData.iIDC_BUTTON_selfTest = IDC_BUTTON_selfTest;
	m_var.guiData.iIDC_BUTTON_ptz = IDC_BUTTON_ptz;
	m_var.guiData.iIDC_BUTTON_remoteStorageSettings = IDC_BUTTON_remoteStorageSettings;
	m_var.guiData.iIDC_CHECK_autoPopupAndHideOnStartup = IDC_CHECK_autoPopupAndHideOnStartup;
	//
	m_var.guiData.iIDC_BUTTON_playLocalAudio = IDC_BUTTON_playLocalAudio;
	*/
	//  2014/04/06
	m_var.ucbAutoClip = TRUE;
	

	connect(ui->pushButton_shareScreen, &QPushButton::clicked, this, &CDlgShareDynBmps_qt::onShareScreenButtonClicked);
	connect(ui->pushButton_webcam1, &QPushButton::clicked, this, &CDlgShareDynBmps_qt::onWebcam1ButtonClicked);
	connect(ui->pushButton_ic, &QPushButton::clicked, this, &CDlgShareDynBmps_qt::onIcButtonClicked);

	this->setGeometry(0, 0, 600, 300);
	this->setStyleSheet("background-color: black;");

	ui->pushButton_shareScreen->setVisible(false);
	ui->pushButton_webcam1->setVisible(false);
	ui->pushButton_ic->setVisible(false);

	ui->widget_pic0->setStyleSheet("background-color: black;");
}

BOOL  isSame_ipDev(IP_dev* p1, IP_dev* p2)
{
	//
	if (p1->iType == p2->iType
		&& !_strcmpi(p1->ip, p2->ip)
		&& !_strcmpi(p1->urls[0].token, p2->urls[0].token)
		&& !_strcmpi(p1->urls[0].rtspUrl.url, p2->urls[0].rtspUrl.url)
		&& !_strcmpi(p1->urls[1].token, p2->urls[1].token)
		&& !_strcmpi(p1->urls[1].rtspUrl.url, p2->urls[1].rtspUrl.url)
		&& !_strcmpi(p1->urls[2].token, p2->urls[2].token)
		&& !_strcmpi(p1->urls[2].rtspUrl.url, p2->urls[2].rtspUrl.url)
		&& p1->ucCnt_urls == p2->ucCnt_urls
		&& !_strcmpi(p1->deviceServiceAddr, p2->deviceServiceAddr)
		)
	{
		return  TRUE;
	}

	

	//
	return  FALSE;
}

int  CDlgShareDynBmps_qt::refreshIpDevs()
{
	int  iErr = -1;

	//
	ShareDynBmps_ipDevsInfo* pIpDevs_src = &m_var.shareDynBmpsThreadInfo.onvif.ipDevsInfo;
	ShareDynBmps_ipDevsInfo* pIpDevs_dst = &m_var.onvif.ipDevsInfo;

	//
	QY_timestamp  ts_src = pIpDevs_src->ts_ipDevsInfo;

	//
	if (timestamp_isSame(&pIpDevs_dst->ts_ipDevsInfo, &pIpDevs_src->ts_ipDevsInfo))  return  0;


	//
	CQySyncCnt  syncCnt;
	if (syncMtCnt_rLock(&m_var.shareDynBmpsThreadInfo.onvif.syncMtCnt_ipDevsInfo, &syncCnt, _T(""))) {
		showInfo_open0(0, 0, _T("refreshIpDevs: rLock failed"));
		goto  errLabel;
	}

	//	
	//m_var.onvif.ipDevsInfo  =  m_var.shareDynBmpsThreadInfo.onvif.ipDevsInfo;


	int  i;
	//
	for (i = 0; i < mycountof(m_var.shareDynBmpsThreadInfo.onvif.ipDevsInfo.mems); i++) {
		IP_dev* pIpDev_src = &m_var.shareDynBmpsThreadInfo.onvif.ipDevsInfo.mems[i];
		IP_dev* pIpDev_dst = &m_var.onvif.ipDevsInfo.mems[i];

		//
		if (!pIpDev_src->iType) {
			if (!pIpDev_dst->iType)  continue;
			//
			pIpDev_dst->status.toBeStopped = TRUE;
			continue;
		}
		//
		if (!pIpDev_dst->iType) {
			//
			memcpy(pIpDev_dst, pIpDev_src, sizeof(pIpDev_dst[0]));
			continue;
		}
		//		 
		if (pIpDev_dst->rule.status.uiTranNo_changeContent != pIpDev_src->rule.status.uiTranNo_changeContent) {
			pIpDev_dst->status.toBeStopped = TRUE;
			continue;
		}
		//  2016/11/10
#ifdef  __DEBUG__
#if  1
#endif
#endif
		 //
#if  0	 //  2016/11/11
		if (pIpDev_dst->rule.iOnvifRuleType == CONST_onvifRuleType_probe
			&& pIpDev_dst->usHelp_subIndex)
		{
			//
			TCHAR  tBuf[128];
			_sntprintf(tBuf, mycountof(tBuf), _T("Err: usHelp_subIndex of probed ipDev is %d, ( must be 0 ). so remove the result"), (int)pIpDev_dst->usHelp_subIndex);
			showInfo_open0(0, 0, tBuf);
			//
			pIpDev_dst->status.toBeStopped = TRUE;
			continue;
		}
#endif


		//
		//
		if (isSame_ipDev(pIpDev_src, pIpDev_dst)) {
			continue;
		}
		//
		pIpDev_dst->status.toBeStopped = TRUE;
		//
		continue;
	}

	//
	BOOL  bExists_toDel; bExists_toDel = FALSE;
	//
	for (i = 0; i < mycountof(m_var.onvif.ipDevsInfo.mems); i++) {
		IP_dev* pIpDev_dst = &m_var.onvif.ipDevsInfo.mems[i];
		//
		if (!pIpDev_dst->status.toBeStopped)  continue;

		//  2016/08/09
		bExists_toDel = TRUE;

		//
		{
			CHelp_shareDynBmp	help_mem;
			SHARE_dyn_bmp* pMem = help_mem.getMemByIndex_obj(m_hWnd, &m_var, CONST_objType_rtspStream, pIpDev_dst->rule.usIndex_obj, pIpDev_dst->usHelp_subIndex);
			if (pMem) {
				// _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s,Used"  ),  displayBuf  );
			}
			else {
				//  2016/06/25. 删除的操作在这里。
				//if  (  pRule->status.bDel  )  
				{
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("shareDynBmp::ipDev index_obj %d will be removed."), (int)pIpDev_dst->rule.usIndex_obj);
					memset(pIpDev_dst, 0, sizeof(IP_dev));
					//	
					continue;
				}
			}
		}

		//
		continue;
	}

	//
	if (!bExists_toDel) {
		pIpDevs_dst->ts_ipDevsInfo = ts_src;
	}

	//	
	this->reloadOnvifList();

	iErr = 0;
errLabel:

	return  iErr;
}

int  CDlgShareDynBmps_qt::sizeAllControls()
{
	/*
	CWnd* pCtrl;

	pCtrl = GetDlgItem(m_var.idc);
	if (!pCtrl)  goto  errLabel;
	pCtrl->Invalidate(TRUE);
	//  pCtrl->UpdateWindow(  );

	RECT	rc;
	pCtrl->GetClientRect(&rc);

	*/


	if (!m_var.hWndIDC)  goto  errLabel;
	//::InvalidateRect();
	RECT	rc;
	::GetClientRect(m_var.hWndIDC, &rc);
	

	m_var.iW_pic = rc.right - rc.left;
	m_var.iH_pic = rc.bottom - rc.top;

	//
	getCapImages(m_var.ucbAutoClip, 0, 0, rc.right - rc.left, rc.bottom - rc.top, NULL, &m_var.images);

errLabel:
	return  0;
}

void CDlgShareDynBmps_qt::onTimer() {
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	if (!pProcInfo)  return;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return;


	//



	/*
	if (nIDEvent == m_var.uiTimerId_test) {

		m_var.nCtrls_test++;

#if  1	//  def  __DEBUG__
#if  10	
		//  测试数据
		traceLog(_T("for test"));
		if (!m_var.pComPort_gps) {
			m_var.pComPort_gps = new  CComPortEx;
		}
		CComPortEx* pPort = (CComPortEx*)m_var.pComPort_gps;
		if (!pPort)  goto  errLabel;

		//
		myGPS_POSITION	pos;
		memset(&pos, 0, sizeof(pos));
#if  0
		pos.dblLatitude = 40.2;
		pos.dblLongitude = 116.6;
#else
		myTestData_gps(&m_var.pMisCnt->idInfo, m_var.nCtrls_test, &pos);
#endif

		GetSystemTime(&pos.stUTCTime);

		//
		setGpsPos(m_var.pComPort_gps, &pos);
		if (!IsWindow(pPort->m_var.hWndOwner)) {
			::PostMessage(m_hWnd, CONST_qyWm_postComm, CONST_qyWmParam_gps, 0);
		}

		//
		QY_SHARED_OBJ* pSharedObj = NULL;
		int					iIndex_sharedObj = m_var.share_gps.var.iIndex_sharedObj;
		if (iIndex_sharedObj)  pSharedObj = getSharedObjByIndex(pProcInfo, iIndex_sharedObj);
		//
		if (pSharedObj) {
			//  ::toShareGps(  pProcInfo,  pPort,  0,  &pos,  pSharedObj,  NULL,  (  MIS_MSGU  *  )pPort->m_var.pMsgBuf  );
			pFuncs->gps.pf_toShareGps(pProcInfo, pPort, 0, &pos, pSharedObj, NULL, (MIS_MSGU*)pPort->m_var.pMsgBuf);
		}

		//
#endif
#endif

		return;
	}*/

	// TODO: Add your message handler code here and/or call default
	m_var.nCtrls++;


#ifdef  __DEBUG__
	//traceLog(  _T(  "dlgShareDynBmps::OnTimer called. %d"  ),  m_var.nCtrls  );
#endif


	 //
	if (!(m_var.nCtrls % (5000 / m_var.nElapseInMs))) {
		refreshShareStatus(0);
	}

	/*if (!(m_var.nCtrls % 2)) {
		this->chkShareGps();
	}*/


	//  2011/10/15
#if  0
	if (m_var.bNeed_shareWebcamInConference) {
		MACRO_SetForegroundWindow(this->m_hWnd);
		if (pFuncs->pf_bDlgTalkAbove(pProcInfo->hWnd_shareDynBmps)) {
			::SetWindowPos(pProcInfo->hWnd_shareDynBmps, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
			::SetWindowPos(pProcInfo->hWnd_shareDynBmps, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

			//  ::SetForegroundWindow(  pProcInfo->hWnd_shareDynBmps  );

#ifdef  __DEBUG__
			if (pFuncs->pf_bDlgTalkAbove(pProcInfo->hWnd_shareDynBmps)) {
				traceLog(_T("kk: dlgTalkAbove"));
			}
#endif

		}

		return;
	}
#endif

	//
	if (!(m_var.nCtrls % (5000 / m_var.nElapseInMs))) {
		if (m_var.tLastModifiedTime != m_var.tLastModifiedTime_ok) {
			pFuncs->shareDynBmps.pf_dlgShareDynBmps_sndDynBmpsInfo(m_hWnd, &m_var);
		}
	}


	//  2014/09/11
	if (m_var.internalProcess.bNeedProcess) {
		pFuncs->shareDynBmps.pf_dlgShareDynBmps_internalProcess(g_pQyMc, m_hWnd, &m_var);
	}


	//
	if (m_var.onvif.selfTest.bSelfTest) {
		//
		int  max_nElapseInS = 100;
		//
		int  nElapseInS = (GetTickCount() - m_var.onvif.selfTest.dwTickCnt_startSelfTest) / 1000;
		TCHAR  tBuf[128];
		_sntprintf(tBuf, mycountof(tBuf), _T("%s %d"), getResStr(0, &pQyMc->cusRes, CONST_resId_stop), max_nElapseInS - nElapseInS);
		//SetDlgItemText(m_var.guiData.iIDC_BUTTON_selfTest, tBuf);

		//
		if (nElapseInS > max_nElapseInS) {
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("shareDynBmp::rtsp: selfTest too long."));
			showNotification(0, 0, 0, 0, 0, 0, _T("selfTest too long"));
			m_var.onvif.selfTest.bSelfTest = FALSE;
			m_var.onvif.selfTest.bNeedChkRtsp = TRUE;
		}
	}
	BOOL  bNeedChk = FALSE;
	if (!m_var.onvif.selfTest.bSelfTest) {
		if (!(m_var.nCtrls % (120000 / m_var.nElapseInMs))
			|| m_var.onvif.selfTest.bNeedChkRtsp)
		{
			bNeedChk = TRUE;
		}
	}
	if (bNeedChk) {
		if (m_var.onvif.selfTest.bNeedChkRtsp) {
			m_var.onvif.selfTest.bNeedChkRtsp = FALSE;
		}

		//
		int				i;
		int				index;


		//  share_dynBmps
		for (index = 0; index < mycountof(m_var.shares); index++) {
			SHARE_dynBmps* pShare;

			//  
			pShare = &m_var.shares[index];
			if (!pShare)  goto  errLabel;

#if  0	//  2014/09/09
			for (i = 0; i < pShare->usCnt; i++) {

				//
				if (!pShare->mems[i].usIndex_obj)  continue;

				//  
				if (pShare->mems[i].var.bShared) {

					//
					pFuncs->shareDynBmps.pf_dlgShareDynBmps_chkSharedObj(m_hWnd, &m_var, pShare->mems[i].var.iIndex_sharedObj);

					//  2014/0/04
					if (pShare->uiObjType == CONST_objType_rtspStream) {
						QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, pShare->mems[i].var.iIndex_sharedObj);
						if (pSharedObj) {
							ROUTE_sendLocalAv* pRoute = &pSharedObj->route_sendLocalAv;
							if (isEmpty_ROUTE_sendLocalAv(pRoute)) {
								//
								qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsClient"), 0, _T(""), _T(""), _T("shareDynBmp::rtsp: route is empty, so close taskAv."));
								//
								pFuncs->shareDynBmps.pf_dlgShareDynBmps_closeTaskAv(m_hWnd, &m_var, pShare->uiObjType, i);
								//
								m_var.onvif.bNeedRefreshed = TRUE;
							}
						}
					}

				}

				//  2014/06/10
				if (!pShare->mems[i].var.bShared) {
					if (pShare->uiObjType == CONST_objType_rtspStream) {
						qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsClient"), 0, _T(""), _T(""), _T("shareDynBmp::rtsp index_obj %d need to be cleared."), (int)pShare->mems[i].usIndex_obj);
						memset(&pShare->mems[i], 0, sizeof(pShare->mems[i]));
						//
						m_var.onvif.bNeedRefreshed = TRUE;
					}
				}

			}
#endif


#if  10	//  2014/09/09
			for (i = 0; i < pShare->usCnt; i++) {
				CHelp_shareDynBmp  help_dynBmpMem;
				SHARE_dyn_bmp* pDynBmpMem = NULL;
				pDynBmpMem = &pShare->mems_internal[i];	//  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  pShare->uiObjType,  i  );
				if (!pDynBmpMem)  continue;

				//
				if (!pDynBmpMem->resObj.usIndex_obj)  continue;

				//  2021/03/13
				if (!pDynBmpMem->var.iTaskId) {
					continue;
				}

				//  
				//  if  (  pDynBmpMem->var.bShared  )  
				if (bShared(pDynBmpMem))
				{

					//
					pFuncs->shareDynBmps.pf_dlgShareDynBmps_chkTask(m_hWnd, &m_var, pDynBmpMem->var.iTaskId);

					//  2014/0/04
					if (pDynBmpMem->resObj.uiObjType == CONST_objType_rtspStream) {
						int  index_taskInfo = GuiShare.pf_getQmcTaskInfoIndexBySth(pProcInfo, pDynBmpMem->var.iTaskId);
						QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)GuiShare.pf_getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
						if (pTaskInfo) {
							ROUTE_sendLocalAv* pRoute = &pTaskInfo->var.curRoute_sendLocalAv;
							if (isEmpty_ROUTE_sendLocalAv(pRoute)) {
								//
								qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("shareDynBmp::rtsp: route is empty, so close taskAv."));
								//
								pFuncs->shareDynBmps.pf_dlgShareDynBmps_closeTaskAv(m_hWnd, &m_var, pDynBmpMem->resObj.uiObjType, i);
								//
								m_var.onvif.bNeedRefreshed = TRUE;
							}
						}
					}

				}

				//  2014/06/10
				if (!bShared(pDynBmpMem)) {
					if (GetTickCount() - pDynBmpMem->var.dwTickCnt_start > 10000) {
						if (pDynBmpMem->resObj.uiObjType == CONST_objType_rtspStream) {
							qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("shareDynBmp::rtsp index_obj %d need to be cleared."), (int)pDynBmpMem->resObj.usIndex_obj);
							if (help_dynBmpMem.clear(pDynBmpMem))
							{
								MACRO_qyAssert(0, _T("dynBmpMem.clear failed"));
							}
							//
							m_var.onvif.bNeedRefreshed = TRUE;
						}
					}
				}

			}
#endif

		}

		//  share_gps
		if (m_var.share_gps.bShare) {
			pFuncs->shareDynBmps.pf_dlgShareDynBmps_chkTask(m_hWnd, &m_var, m_var.share_gps.var.iTaskId);
		}

	}
	//
	//  2016/07/07
	if (!timestamp_isSame(&m_var.onvif.ipDevsInfo.ts_ipDevsInfo, &m_var.shareDynBmpsThreadInfo.onvif.ipDevsInfo.ts_ipDevsInfo)) {
		//
		showInfo_open0(0, 0, _T("shareDynBmps.timer: refresh ipDevsInfo"));
		//
	    this->refreshIpDevs();
	}
	//  2014/06/10
	if (m_var.onvif.bNeedRefreshed) {
		DWORD  dwTickCnt = GetTickCount();
		if (dwTickCnt - m_var.onvif.dwLastTickCnt_refreshed > 5000) {
			m_var.onvif.dwLastTickCnt_refreshed = dwTickCnt;
			m_var.onvif.bNeedRefreshed = FALSE;
			//
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("shareDynBmps::reload onvif list."));
			this->reloadOnvifList();
		}
	}

errLabel:
	int i = i + 1;
}

CDlgShareDynBmps_qt::~CDlgShareDynBmps_qt()
{
	delete ui;

	if (timer){
		if(timer->isActive())
			timer->stop();
	    delete timer;
	}

	dlgShareDynBmps_OnDestroy();
		
}


int  getWebcamInfo(unsigned  int  uiObjType, int  index_obj, WEBCAM_info* pWebcamInfo)
{
	int  iErr = -1;
	//
	int				uiCapType = CONST_capType_av;
	int				uiSubCapType = CONST_subCapType_webcam;


	QY_REG			reg;
	memset(&reg, 0, sizeof(reg));

	//
	TCHAR* pRegKeyName = NULL;

	switch (uiObjType) {
	case  CONST_objType_webcam:
		pRegKeyName = (TCHAR*)_T(CONST_regKeyName_webcam);
		break;
	case  CONST_objType_screen:
		pRegKeyName = (TCHAR*)_T(CONST_regKeyName_screen);
		break;
	case  CONST_objType_ic:
		pRegKeyName = (TCHAR*)_T(CONST_regKeyName_ic);
		break;
	default:
		return  -1;
	}


	//
	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	//  _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
	getRegRootKey_qmc(uiCapType, uiSubCapType, 0, reg.rootKey, mycountof(reg.rootKey));
	_sntprintf(reg.rootKey, mycountof(reg.rootKey), _T("%s\\%s"), reg.rootKey, pRegKeyName);
	_sntprintf(reg.rootKey, mycountof(reg.rootKey), _T("%s\\%d"), reg.rootKey, index_obj);

	//
	memset(pWebcamInfo, 0, sizeof(pWebcamInfo[0]));


	//
	pWebcamInfo->index_obj = index_obj;

	//
	TCHAR  tName[256];

	//
	if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_aName, (char*)tName, sizeof(tName), NULL))  tName[0] = 0;
	tTrim(tName);
	safeTcsnCpy(tName, pWebcamInfo->aName, mycountof(pWebcamInfo->aName));

	if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_vName, (char*)tName, sizeof(tName), NULL))  tName[0] = 0;
	tTrim(tName);
	safeTcsnCpy(tName, pWebcamInfo->vName, mycountof(pWebcamInfo->vName));

	//
	unsigned char  ucCmd;
	TCHAR* pRegVal = NULL;
	char				buf[256];

	//
	if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_name, (char*)tName, sizeof(tName), NULL))  tName[0] = 0;
	tTrim(tName);
	safeTcsnCpy(tName, pWebcamInfo->cusName, mycountof(pWebcamInfo->cusName));


	//	
	ucCmd = FALSE;
	pRegVal = (TCHAR*)(CONST_regValName_ucbUnresizable);
	if (!qyGetRegCfgT(reg.hKeyRoot0, CQyString(reg.rootKey), pRegVal, (char*)buf, sizeof(buf), 0) && atol(buf))  ucCmd = TRUE;
	pWebcamInfo->ucbUnresizable = ucCmd;


	//	
	ucCmd = FALSE;
	pRegVal = (TCHAR*)(CONST_regValName_ucbAutoOpenOnStartup);
	if (!qyGetRegCfgT(reg.hKeyRoot0, CQyString(reg.rootKey), pRegVal, (char*)buf, sizeof(buf), 0) && atol(buf))  ucCmd = TRUE;
	pWebcamInfo->ucbAutoOpenOnStartup = ucCmd;

	//  2018/10/30
	QY_MC* pQyMc = QY_GET_GBUF();
	if (pQyMc->iCustomId == CONST_qyCustomId_hzj) {
		if (index_obj == 1 && uiObjType == CONST_objType_webcam) {
			MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
			//
			if (!pWebcamInfo->vName[0]) {
				safeTcsnCpy(pProcInfo->status.vName_1st_webcam, pWebcamInfo->vName, mycountof(pWebcamInfo->vName));
			}
		}
		if (index_obj == 1) {
			pWebcamInfo->ucbAutoOpenOnStartup = TRUE;
		}
	}
	if (pQyMc->iCustomId == CONST_qyCustomId_hbwj) {
		if (index_obj == 1 && uiObjType == CONST_objType_screen) {
			pWebcamInfo->ucbAutoOpenOnStartup = TRUE;
		}
	}


	iErr = 0;
errLabel:


	return  iErr;
}

int  CDlgShareDynBmps_qt::refreshShareCfg_screen(unsigned  int  uiObjType, int  index_obj)
{
	int  iErr = -1;

	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;


	CHelp_shareDynBmp  help_shareDynBmpMem;

	if (uiObjType != CONST_objType_screen)  return  -1;

	//
	SHARE_dynBmps* pShare = this->getShareDynBmpsBySth(uiObjType);
	if (!pShare)  return  -1;

	//
	WEBCAM_info  webcamInfo;
	getWebcamInfo(uiObjType, index_obj, &webcamInfo);

	int  index_pShare_mem = index_obj - 1;

	//
	SHARE_dyn_bmp* pDynBmpMem = help_shareDynBmpMem.getMemByIndex(m_hWnd, &m_var, uiObjType, index_pShare_mem);
	if (!pDynBmpMem)  goto  errLabel;

	TCHAR  tBuf[256];

	//  pDynBmpMem->name
	//
	safeTcsnCpy(webcamInfo.cusName, pDynBmpMem->cusName, mycountof(pDynBmpMem->cusName));

	//

//
	/*QY_DMITEM* pItem = qyGetDmItemByType(pShare->pTable_ctrls, index_obj, sizeof(QY_DMITEM));
	if (pItem) {
		SetDlgItemText((int)pItem->des, pDynBmpMem->name);
	}*/


	iErr = 0;
errLabel:

	return  iErr;

}

int  CDlgShareDynBmps_qt::refreshShareCfg_webcam(unsigned  int  uiObjType, int  index_obj)
{
	int  iErr = -1;

	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;


	CHelp_shareDynBmp  help_shareDynBmpMem;

	if (uiObjType != CONST_objType_webcam)  return  -1;

	//
	SHARE_dynBmps* pShare = this->getShareDynBmpsBySth(uiObjType);
	if (!pShare)  return  -1;

	//
	WEBCAM_info  webcamInfo;
	getWebcamInfo(uiObjType, index_obj, &webcamInfo);

	int  index_pShare_mem = index_obj - 1;

	//
	SHARE_dyn_bmp* pDynBmpMem = help_shareDynBmpMem.getMemByIndex(m_hWnd, &m_var, uiObjType, index_pShare_mem);
	if (!pDynBmpMem)  goto  errLabel;

	TCHAR  tBuf[256];
	safeTcsnCpy(webcamInfo.vName, pDynBmpMem->name, mycountof(pDynBmpMem->name));
	if (webcamInfo.aName[0])  _sntprintf(pDynBmpMem->name, mycountof(pDynBmpMem->name), _T("%s (%s)"), pDynBmpMem->name, webcamInfo.aName);
	//
	safeTcsnCpy(webcamInfo.cusName, pDynBmpMem->cusName, mycountof(pDynBmpMem->cusName));

	////
	//CAP_STUFF& gcap = *(CAP_STUFF*)m_var.pCapStuff1;
	////
	//TCHAR  tName[256];
	//int  i;
	//for (i = 0; i < mycountof(gcap.rgpmVideoMenu); i++) {
	//	if (!gcap.rgpmVideoMenu[i])  continue;
	//	//
	//	pFuncs->moniker.pf_getMonikerProp(gcap.rgpmVideoMenu[i], CONST_moniker_FriendlyName, tName, mycountof(tName));
	//	//
	//	if (_tcsicmp(tName, webcamInfo.vName))  continue;
	//	//
	//	break;
	//}
	//if (i <= mycountof(gcap.rgpmVideoMenu)) {
	//	//			  
	//	pDynBmpMem->iMenuId = ID_MENU_VDEVICE0 + i;
	//}

	////
	//QY_DMITEM* pItem = qyGetDmItemByType(pShare->pTable_ctrls, index_obj, sizeof(QY_DMITEM));
	//if (pItem) {
	//	SetDlgItemText((int)pItem->des, pDynBmpMem->name);
	//}


	iErr = 0;
errLabel:

	return  iErr;

}

int  getOnvifRuleIndex(ShareDynBmps_onvif_rulesInfo* pRulesInfo, unsigned  short  usIndex_obj)
{
	if (!pRulesInfo)  return  -1;
	ShareDynBmps_onvif_rulesInfo& rulesInfo = *pRulesInfo;

	//
	int  i;
	for (i = 0; i < mycountof(rulesInfo.mems); i++) {
		if (rulesInfo.mems[i].usIndex_obj == usIndex_obj)  break;
	}
	if (i == mycountof(rulesInfo.mems))  return  -1;

	return  i;
}


int  CDlgShareDynBmps_qt::displayOnvifList()
{
	int  iRet = -1;

	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;
	//
	CTX_qm_thread* pCtx_thread = &pQyMc->gui.ctx_gui_thread;


	//
	TCHAR			tName[64] = _T("");
	TCHAR			tBuf[255] = _T("");

	TCHAR* p;
	char* p1;
	TCHAR* pName;
	TCHAR* pUrl;

	int				uiCapType = CONST_capType_av;
	int				uiSubCapType = CONST_subCapType_webcam;

#if  10
	QY_REG			reg;
	memset(&reg, 0, sizeof(reg));

	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	//  _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
	getRegRootKey_qmc(uiCapType, uiSubCapType, 0, reg.rootKey, mycountof(reg.rootKey));
	_sntprintf(reg.rootKey, mycountof(reg.rootKey), _T("%s\\%s"), reg.rootKey, _T(CONST_regKeyName_rtspUrl));
#endif
	//
	::SendMessage(m_var.hCtrl_onvifList, LB_RESETCONTENT, 0, 0);



	//
	//  dlgShareDynBmps_chkOnvifRules(  m_hWnd,  m_var,  &m_var.onvif.rulesInfo,  &m_var.onvif.ipDevsInfo  );

	//
	TCHAR  displayBuf[1024];
	int  i;
	int  nPos;

	//
	for (i = 0; i < m_var.onvif.rulesInfo.usCnt; i++) {
		Onvif_rule* pRule = &m_var.onvif.rulesInfo.mems[i];

		//	
		_sntprintf(displayBuf, mycountof(displayBuf), _T("%s %d: %s,%s,%s,%s:*,%s"), CONST_str_rule, (int)pRule->usIndex_obj, _T("")/*qyGetDesByType1(CONST_onvifRuleTypeTable, pRule->iOnvifRuleType)*/, pRule->cusName, CQyString(pRule->url), CQyString(pRule->usrName), CQyString(pRule->defToken));
		if (pRule->status.bDel)  _sntprintf(displayBuf, mycountof(displayBuf), _T("%s,Del"), displayBuf);
		if (m_var.onvif.selfTest.bSelfTest) {
			if (pRule->usIndex_obj == m_var.onvif.selfTest.usIndex_obj_selfTest)  _sntprintf(displayBuf, mycountof(displayBuf), _T("%s,selTest"), displayBuf);
		}
		//		
		//  2014/09/09		
		//
		IP_dev* pIpDev = NULL;//getIpDevBy_index_obj(  &m_var.onvif.ipDevsInfo,  pRule->usIndex_obj  );
		//
		if (pRule->iOnvifRuleType == CONST_onvifRuleType_rtspUrl) {
			int  j;
			for (j = 0; j < mycountof(m_var.onvif.ipDevsInfo.mems); j++) {
				pIpDev = &m_var.onvif.ipDevsInfo.mems[j];
				if (!pIpDev->iType)  continue;
				if (pIpDev->rule.usIndex_obj != pRule->usIndex_obj)  continue;
				break;
			}
			//
			if (j < mycountof(m_var.onvif.ipDevsInfo.mems)) {
				//
				if (pIpDev->rule.status.uiTranNo_changeContent == pRule->status.uiTranNo_changeContent) {
					_sntprintf(displayBuf, mycountof(displayBuf), _T("%s rule ok."), displayBuf);
				}

				//
				CHelp_shareDynBmp	help_mem;
				SHARE_dyn_bmp* pMem = help_mem.getMemByIndex_obj(m_hWnd, &m_var, CONST_objType_rtspStream, pRule->usIndex_obj, pIpDev->usHelp_subIndex);
				if (pMem) {
					_sntprintf(displayBuf, mycountof(displayBuf), _T("%s,Used"), displayBuf);
				}
				else {
					//  2016/06/25. 删除的操作在这里。
					if (pIpDev->status.toBeStopped) {
						_sntprintf(displayBuf, mycountof(displayBuf), _T("%s,toBeStopped"), displayBuf);
					}
				}

			}
		}
		//
		nPos = ::SendMessage(m_var.hCtrl_onvifList, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)displayBuf);
		if (pRule->usIndex_obj == m_var.onvif.sel.usIndex_obj_sel) {
			//
			::SendMessage(m_var.hCtrl_onvifList, LB_SETCURSEL, (WPARAM)nPos, (LPARAM)0);
		}
		//		 	
		//
		if (pRule->iOnvifRuleType != CONST_onvifRuleType_rtspUrl) {
			int  j;
			for (j = 0; j < mycountof(m_var.onvif.ipDevsInfo.mems); j++) {
				pIpDev = &m_var.onvif.ipDevsInfo.mems[j];
				if (!pIpDev->iType)  continue;
				if (pIpDev->rule.usIndex_obj != pRule->usIndex_obj)  continue;
				//
				if (pRule->iOnvifRuleType == CONST_onvifRuleType_discovery) {  //  2016/08/15
					displayBuf[0] = 0;
					_sntprintf(displayBuf, mycountof(displayBuf), _T("%s %d"), CONST_str_ipCam, (int)pIpDev->rule.usIndex_obj);
					if (pIpDev->usHelp_subIndex)  _sntprintf(displayBuf, mycountof(displayBuf), _T("%s.%d"), displayBuf, (int)pIpDev->usHelp_subIndex);
					//
					_sntprintf(displayBuf, mycountof(displayBuf), _T("%s: URI: %s"), displayBuf, CQyString(pIpDev->deviceServiceAddr));
					//
					nPos = ::SendMessage(m_var.hCtrl_onvifList, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)displayBuf);
				}
				//
				unsigned  char  ucCnt_urls = min(pIpDev->ucCnt_urls, mycountof(pIpDev->urls));
				int  k;
				for (k = 0; k < ucCnt_urls; k++) {
					displayBuf[0] = 0;
					_sntprintf(displayBuf, mycountof(displayBuf), _T("%s %d"), CONST_str_ipCam, (int)pIpDev->rule.usIndex_obj);
					if (pIpDev->usHelp_subIndex)  _sntprintf(displayBuf, mycountof(displayBuf), _T("%s.%d"), displayBuf, (int)pIpDev->usHelp_subIndex);

					//if  (  pIpDev->subIndex  )  _sntprintf(  displayBuf,  mycountof(  displayBuf  ),  _T(  "%s %d"  ),  displayBuf,  (  int  )pIpDev->subIndex  );

					//						
					_sntprintf(displayBuf, mycountof(displayBuf), _T("%s: %s %s"), displayBuf, CQyString(pIpDev->urls[k].token), CQyString(pIpDev->urls[k].rtspUrl.url));

					//
					//
					CHelp_shareDynBmp	help_mem;
					SHARE_dyn_bmp* pMem = help_mem.getMemByIndex_obj(m_hWnd, &m_var, CONST_objType_rtspStream, pRule->usIndex_obj, pIpDev->usHelp_subIndex);
					if (pMem) {
						_sntprintf(displayBuf, mycountof(displayBuf), _T("%s,Used"), displayBuf);
					}
					else {
						//  2016/06/25. 删除的操作在这里。
						if (pIpDev->status.toBeStopped) {
							_sntprintf(displayBuf, mycountof(displayBuf), _T("%s, toBeStopped"), displayBuf);
						}
					}
					//		 
					nPos = ::SendMessage(m_var.hCtrl_onvifList, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)displayBuf);
				}
			}
		}
		//

	   //
		continue;
	}

	//
	for (i = 0; i < mycountof(m_var.onvif.ipDevsInfo.mems); i++) {
		IP_dev* pIpDev = &m_var.onvif.ipDevsInfo.mems[i];
		//
		if (!pIpDev->iType)  continue;
		//
		int  ruleIndex = getOnvifRuleIndex(&m_var.onvif.rulesInfo, pIpDev->rule.usIndex_obj);
		if (ruleIndex < 0) {
			displayBuf[0] = 0;
			_sntprintf(displayBuf, mycountof(displayBuf), _T("Invalid IpCam %d"), pIpDev->rule.usIndex_obj);
			if (pIpDev->usHelp_subIndex)  _sntprintf(displayBuf, mycountof(displayBuf), _T("%s %d"), displayBuf, (int)pIpDev->usHelp_subIndex);
			if (pIpDev->ucCnt_urls) {
				_sntprintf(displayBuf, mycountof(displayBuf), _T("%s: %s"), displayBuf, CQyString(pIpDev->urls[0].rtspUrl.url));
			}
			//
			CHelp_shareDynBmp	help_mem;
			SHARE_dyn_bmp* pMem = help_mem.getMemByIndex_obj(m_hWnd, &m_var, CONST_objType_rtspStream, pIpDev->rule.usIndex_obj, pIpDev->usHelp_subIndex);
			if (pMem) {
				_sntprintf(displayBuf, mycountof(displayBuf), _T("%s,Used"), displayBuf);
			}
			else {
				//  2016/06/25. 删除的操作在这里。
				if (pIpDev->status.toBeStopped) {
					_sntprintf(displayBuf, mycountof(displayBuf), _T("%s, toBeStopped"), displayBuf);
				}
			}
			//		 
			nPos = ::SendMessage(m_var.hCtrl_onvifList, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)displayBuf);


		}

	}


	iRet = 0;
errLabel:
	return  iRet;
}

int  CDlgShareDynBmps_qt::refreshShareStatus(unsigned  int  uiObjType)
{
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;

	return  pFuncs->shareDynBmps.pf_dlgShareDynBmps_refreshShareStatus(g_pQyMc, m_hWnd, &m_var, uiObjType);
}

 int  parseRegVal_webcam_rtspUrl(LPCTSTR  regVal, Onvif_rule* pItemUrl)
{
	int  iErr = -1;

	TCHAR* p0, * p1;
	TCHAR	tBuf[512];
	BOOL  bDel = FALSE;

	safeTcsnCpy(regVal, tBuf, mycountof(tBuf));

	int  ch = ';';
	//
	p0 = tBuf;
	p1 = _tcschr(p0, ch);
	if (!p1)  goto  errLabel;

	//
	*p1 = 0;
	pItemUrl->iOnvifRuleType = _ttol(p0);

	//
	p0 = p1;
	p0++;
	p1 = _tcschr(p0, ch);
	if (!p1)  goto  errLabel;
	//
	*p1 = 0;
	safeTcsnCpy(p0, pItemUrl->cusName, mycountof(pItemUrl->cusName));

	//
	p0 = p1;
	p0++;
	TCHAR* pUrl; pUrl = p0;

	p1 = _tcschr(pUrl, ch);
	if (!p1)  goto  errLabel;
	*p1 = 0;
	myTChar2Utf8(pUrl, pItemUrl->url, mycountof(pItemUrl->url));

	//
	p0 = p1;
	p0++;
	p1 = _tcschr(p0, ch);
	if (!p1)  goto  errLabel;
	*p1 = 0;
	myTChar2Utf8(p0, pItemUrl->usrName, mycountof(pItemUrl->usrName));

	//
	p0 = p1;
	p0++;
	p1 = _tcschr(p0, ch);
	if (!p1)  goto  errLabel;
	*p1 = 0;
	myTChar2Utf8(p0, pItemUrl->passwd, mycountof(pItemUrl->passwd));

	//
	p0 = p1;
	p0++;
	p1 = _tcschr(p0, ch);
	if (!p1)  goto  errLabel;
	*p1 = 0;
	myTChar2Utf8(p0, pItemUrl->defToken, mycountof(pItemUrl->defToken));

	//
	p0 = p1;
	p0++;
	p1 = _tcschr(p0, ch);
	if (p1) {
		*p1 = 0;
	}
	//			
	bDel = _ttol(p0);

	//
	pItemUrl->status.bDel = bDel;

	iErr = 0;
errLabel:
	return  iErr;

};

 BOOL  isSame_onvifRule(Onvif_rule* p1, Onvif_rule* p2)
 {
	 //
	 if (p1->usIndex_obj == p2->usIndex_obj
		 && p1->iOnvifRuleType == p2->iOnvifRuleType
		 && !_strcmpi(p1->url, p2->url)
		 && !_tcsicmp(p1->cusName, p2->cusName)
		 && !_strcmpi(p1->usrName, p2->usrName)
		 && !_strcmpi(p1->passwd, p2->passwd)
		 && !_strcmpi(p1->defToken, p2->defToken)
		 )
	 {
		 return  TRUE;
	 }

	 //
	 return  FALSE;
 }


 int  CDlgShareDynBmps_qt::reloadOnvifList()
 {
	 int  iRet = -1;

	 QY_MC* pQyMc = QY_GET_GBUF();
	 MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	 if (!pProcInfo)  return  -1;
	 FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	 if (!pFuncs)  return  -1;
	 //
	 CTX_qm_thread* pCtx_thread = &pQyMc->gui.ctx_gui_thread;

	 


	 //
	 TCHAR			tName[64] = _T("");
	 TCHAR			tBuf[255] = _T("");
	 //TCHAR			tBuf[255] = _T("1,,rtsp://192.168.1.24:554/cam/realmonitor?channel=1&subtype=0,,,,0");

	 TCHAR* p;
	 char* p1;
	 TCHAR* pName;
	 TCHAR* pUrl;
	 std::wstring rtspUrl;

	 int				uiCapType = CONST_capType_av;
	 int				uiSubCapType = CONST_subCapType_webcam;

	 if (m_rtspUrl.empty())
		 goto errLabel;

	  rtspUrl =  std::wstring_convert<std::codecvt_utf8<WCHAR>, WCHAR>().from_bytes(m_rtspUrl);

	  //_sntprintf(tBuf, mycountof(tBuf), _T("1;;%s;;;;0"), rtspUrl.c_str());

	 {

		 //
		 int  tmp_ruleIndex;
		 int				index_obj = 0;
		 //
		 ShareDynBmps_onvif_rulesInfo  new_rulesInfo = { 0 };

		 //
		 do {
			 //tTrim(tBuf);
			 //if (!tBuf[0])  continue;

			 index_obj = 1;
			 //
			 Onvif_rule  tmpRule = { 0 };
			 tmpRule.usIndex_obj = index_obj;

			 tmpRule.iOnvifRuleType = 1;
			 myTChar2Utf8(rtspUrl.c_str(), tmpRule.url, mycountof(tmpRule.url));
			 tmpRule.status.bDel = 0;
			 //parseRegVal_webcam_rtspUrl(tBuf, &tmpRule);

			 //
			 tmp_ruleIndex = getOnvifRuleIndex(&new_rulesInfo, index_obj);
			 if (tmp_ruleIndex < 0) {
				 if (new_rulesInfo.usCnt >= mycountof(new_rulesInfo.mems)) {
					 break;
				 }
				 //					
				 new_rulesInfo.mems[new_rulesInfo.usCnt] = tmpRule;
				 new_rulesInfo.usCnt++;
			 }
			 else  if (!isSame_onvifRule(&tmpRule, &new_rulesInfo.mems[tmp_ruleIndex])) {
				 //						
				 new_rulesInfo.mems[tmp_ruleIndex] = tmpRule;
			 }

		 } while (0);

		 BOOL  bChanged = FALSE;


		 //
		 // 应该是在new_rulesinfo的mems遍历，对每个成员，都看原来的m_var.onvif.rulesInfo有没有同样的index_obj和内容，如果一样，就把该成员的tranNo设成和原来一样。如果不一样，就取一个新的值。
		 // 最后如果有不一样的，就把new_rulesinfo赋给m_var.onvif.rulesInfo. 同时更新ts_rulesInfo.
		 //
		 int  i;
		 for (i = 0; i < new_rulesInfo.usCnt; i++) {
			 Onvif_rule* pRule = &new_rulesInfo.mems[i];
			 index_obj = pRule->usIndex_obj;
			 //
			 tmp_ruleIndex = getOnvifRuleIndex(&m_var.onvif.rulesInfo, index_obj);
			 if (tmp_ruleIndex < 0) {
				 pRule->status.uiTranNo_changeContent = pFuncs->isCliHelp.pf_getuiNextTranNo(0, 0, 0);
				 bChanged = TRUE;
				 //
				 continue;
			 }
			 //
			 if (isSame_onvifRule(pRule, &m_var.onvif.rulesInfo.mems[tmp_ruleIndex])) {
				 pRule->status.uiTranNo_changeContent = m_var.onvif.rulesInfo.mems[tmp_ruleIndex].status.uiTranNo_changeContent;
			 }
			 else {
				 pRule->status.uiTranNo_changeContent = pFuncs->isCliHelp.pf_getuiNextTranNo(0, 0, 0);
				 bChanged = TRUE;
			 }
			 continue;
		 }
		 //
		 if (new_rulesInfo.usCnt != m_var.onvif.rulesInfo.usCnt) {
			 bChanged = TRUE;
		 }
		 //
		 if (bChanged) {
			 timestamp_renew(pCtx_thread, &new_rulesInfo.ts_rulesInfo,_T("dlgShareDynBmps.reloadOnvifList.l1267"));
			 //
			 CQySyncObj  syncObj;

			 //
			 if (syncMtCnt_wLock_wait(&m_var.onvif.syncMtCnt_cur_rulesInfo, _T(""), &syncObj, NULL, _T(""))) {
				 goto  errLabel;
			 }

			 //
			 m_var.onvif.rulesInfo = new_rulesInfo;

			 //		
			 syncMtCnt_start(&m_var.onvif.syncMtCnt_cur_rulesInfo, pFuncs->isCliHelp.pf_getuiNextTranNo);
		 }
	 }

	 //
	 //dlgShareDynBmps_chkOnvifRules(  m_hWnd,  m_var,  &m_var.onvif.rulesInfo,  &m_var.onvif.ipDevsInfo  );


	 //
#if  0
	//
	 ::SendMessage(m_var.hCtrl_onvifList, LB_RESETCONTENT, 0, 0);

	 //
	 int  i;
	 //
	 for (i = 0; i < m_var.onvif.rulesInfo.usCnt; i++) {
		 Onvif_rule* pRule = &m_var.onvif.rulesInfo.mems[i];

		 //
		 TCHAR  displayBuf[1024];
		 _sntprintf(displayBuf, mycountof(displayBuf), _T("%d,%s,%s,%s"), pRule->usIndex_obj, qyGetDesByType1(CONST_onvifRuleTypeTable, pRule->iOnvifRuleType), pRule->cusName, CQyString(pRule->url));
		 if (pRule->status.bDel)  _sntprintf(displayBuf, mycountof(displayBuf), _T("%s,Del"), displayBuf);
		 if (m_var.onvif.selfTest.bSelfTest) {
			 if (pRule->usIndex_obj == m_var.onvif.selfTest.usIndex_obj_selfTest)  _sntprintf(displayBuf, mycountof(displayBuf), _T("%s,selTest"), displayBuf);
		 }
		 //
		 //  2014/09/09
		 {
			 CHelp_shareDynBmp	help_mem;
			 SHARE_dyn_bmp* pMem = help_mem.getMemByIndex_obj(m_hWnd, &m_var, CONST_objType_rtspStream, pRule->usIndex_obj);
			 if (pMem) {
				 _sntprintf(displayBuf, mycountof(displayBuf), _T("%s,Used"), displayBuf);
			 }
			 else {
				 //  2016/06/25. 删除的操作在这里。
				 if (pRule->status.bDel) {
					 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsClient"), 0, _T(""), _T(""), _T("shareDynBmp::rtsp index_obj %d will be removed."), (int)pRule->usIndex_obj);
					 //					  					  					  
					 qyDelRegCfgT(reg.hKeyRoot0, reg.rootKey, tName);
					 continue;
				 }
			 }
		 }
		 //
		 IP_dev* pIpDev = getIpDevBy_index_obj(&m_var.onvif.ipDevsInfo, pRule->usIndex_obj);
		 if (pIpDev) {
			 if (pIpDev->ucCnt_urls) {
				 _sntprintf(displayBuf, mycountof(displayBuf), _T("%s. ( realUrl %s )"), displayBuf, CQyString(pIpDev->urls[0].url));
			 }
		 }
		 //
		 //
		 ::SendMessage(m_var.hCtrl_onvifList, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)displayBuf);
		 if (pRule->usIndex_obj == m_var.onvif.usIndex_obj_sel) {
			 //
			 ::SendMessage(m_var.hCtrl_onvifList, LB_SETCURSEL, (WPARAM)i, (LPARAM)0);
		 }
		 //
		 continue;
	 }
#endif
	 //
	 //displayOnvifList();


	 iRet = 0;
 errLabel:
	 return  iRet;
 }

int  CDlgShareDynBmps_qt::reloadOnvifList_bak()
{
	int  iRet = -1;

	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;
	//
	CTX_qm_thread* pCtx_thread = &pQyMc->gui.ctx_gui_thread;


	//
	TCHAR			tName[64] = _T("");
	TCHAR			tBuf[255] = _T("");

	TCHAR* p;
	char* p1;
	TCHAR* pName;
	TCHAR* pUrl;

	int				uiCapType = CONST_capType_av;
	int				uiSubCapType = CONST_subCapType_webcam;


	QY_REG			reg;
	memset(&reg, 0, sizeof(reg));

	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	//  _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
	getRegRootKey_qmc(uiCapType, uiSubCapType, 0, reg.rootKey, mycountof(reg.rootKey));
	_sntprintf(reg.rootKey, mycountof(reg.rootKey), _T("%s\\%s"), reg.rootKey, _T(CONST_regKeyName_rtspUrl));


	{

		//
		int  tmp_ruleIndex;
		int				index_obj = 0;
		//
		ShareDynBmps_onvif_rulesInfo  new_rulesInfo = { 0 };

		//
		for (index_obj = MIN_usIndex_obj_rtspUrl; index_obj <= MAX_usIndex_obj_rtspUrl; index_obj++) {
			//
			if (new_rulesInfo.usCnt >= mycountof(new_rulesInfo.mems))  break;
			//
			_sntprintf(tName, mycountof(tName), _T("%d"), index_obj);
			if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, tName, (char*)tBuf, sizeof(tBuf), 0))  continue;

			//
			tTrim(tBuf);
			if (!tBuf[0])  continue;

			//
			Onvif_rule  tmpRule = { 0 };
			//
			tmpRule.usIndex_obj = index_obj;
			parseRegVal_webcam_rtspUrl(tBuf, &tmpRule);

			//
			tmp_ruleIndex = getOnvifRuleIndex(&new_rulesInfo, index_obj);
			if (tmp_ruleIndex < 0) {
				if (new_rulesInfo.usCnt >= mycountof(new_rulesInfo.mems)) {
					break;
				}
				//					
				new_rulesInfo.mems[new_rulesInfo.usCnt] = tmpRule;
				new_rulesInfo.usCnt++;
			}
			else  if (!isSame_onvifRule(&tmpRule, &new_rulesInfo.mems[tmp_ruleIndex])) {
				//						
				new_rulesInfo.mems[tmp_ruleIndex] = tmpRule;
			}

			//
			continue;

		}

		BOOL  bChanged = FALSE;


		//
		// 应该是在new_rulesinfo的mems遍历，对每个成员，都看原来的m_var.onvif.rulesInfo有没有同样的index_obj和内容，如果一样，就把该成员的tranNo设成和原来一样。如果不一样，就取一个新的值。
		// 最后如果有不一样的，就把new_rulesinfo赋给m_var.onvif.rulesInfo. 同时更新ts_rulesInfo.
		//
		int  i;
		for (i = 0; i < new_rulesInfo.usCnt; i++) {
			Onvif_rule* pRule = &new_rulesInfo.mems[i];
			index_obj = pRule->usIndex_obj;
			//
			tmp_ruleIndex = getOnvifRuleIndex(&m_var.onvif.rulesInfo, index_obj);
			if (tmp_ruleIndex < 0) {
				pRule->status.uiTranNo_changeContent = pFuncs->isCliHelp.pf_getuiNextTranNo(0, 0, 0);
				bChanged = TRUE;
				//
				continue;
			}
			//
			if (isSame_onvifRule(pRule, &m_var.onvif.rulesInfo.mems[tmp_ruleIndex])) {
				pRule->status.uiTranNo_changeContent = m_var.onvif.rulesInfo.mems[tmp_ruleIndex].status.uiTranNo_changeContent;
			}
			else {
				pRule->status.uiTranNo_changeContent = pFuncs->isCliHelp.pf_getuiNextTranNo(0, 0, 0);
				bChanged = TRUE;
			}
			continue;
		}
		//
		if (new_rulesInfo.usCnt != m_var.onvif.rulesInfo.usCnt) {
			bChanged = TRUE;
		}
		//
		if (bChanged) {
			timestamp_renew(pCtx_thread, &new_rulesInfo.ts_rulesInfo,_T("dlgShareDynBmps.reloadOnvifList_base.l1467"));
			//
			CQySyncObj  syncObj;

			//
			if (syncMtCnt_wLock_wait(&m_var.onvif.syncMtCnt_cur_rulesInfo, _T(""), &syncObj, NULL, _T(""))) {
				goto  errLabel;
			}

			//
			m_var.onvif.rulesInfo = new_rulesInfo;

			//		
			syncMtCnt_start(&m_var.onvif.syncMtCnt_cur_rulesInfo, pFuncs->isCliHelp.pf_getuiNextTranNo);
		}
	}

	//
	//dlgShareDynBmps_chkOnvifRules(  m_hWnd,  m_var,  &m_var.onvif.rulesInfo,  &m_var.onvif.ipDevsInfo  );


	//
#if  0
	//
	::SendMessage(m_var.hCtrl_onvifList, LB_RESETCONTENT, 0, 0);

	//
	int  i;
	//
	for (i = 0; i < m_var.onvif.rulesInfo.usCnt; i++) {
		Onvif_rule* pRule = &m_var.onvif.rulesInfo.mems[i];

		//
		TCHAR  displayBuf[1024];
		_sntprintf(displayBuf, mycountof(displayBuf), _T("%d,%s,%s,%s"), pRule->usIndex_obj, qyGetDesByType1(CONST_onvifRuleTypeTable, pRule->iOnvifRuleType), pRule->cusName, CQyString(pRule->url));
		if (pRule->status.bDel)  _sntprintf(displayBuf, mycountof(displayBuf), _T("%s,Del"), displayBuf);
		if (m_var.onvif.selfTest.bSelfTest) {
			if (pRule->usIndex_obj == m_var.onvif.selfTest.usIndex_obj_selfTest)  _sntprintf(displayBuf, mycountof(displayBuf), _T("%s,selTest"), displayBuf);
		}
		//
		//  2014/09/09
		{
			CHelp_shareDynBmp	help_mem;
			SHARE_dyn_bmp* pMem = help_mem.getMemByIndex_obj(m_hWnd, &m_var, CONST_objType_rtspStream, pRule->usIndex_obj);
			if (pMem) {
				_sntprintf(displayBuf, mycountof(displayBuf), _T("%s,Used"), displayBuf);
			}
			else {
				//  2016/06/25. 删除的操作在这里。
				if (pRule->status.bDel) {
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsClient"), 0, _T(""), _T(""), _T("shareDynBmp::rtsp index_obj %d will be removed."), (int)pRule->usIndex_obj);
					//					  					  					  
					qyDelRegCfgT(reg.hKeyRoot0, reg.rootKey, tName);
					continue;
				}
			}
		}
		//
		IP_dev* pIpDev = getIpDevBy_index_obj(&m_var.onvif.ipDevsInfo, pRule->usIndex_obj);
		if (pIpDev) {
			if (pIpDev->ucCnt_urls) {
				_sntprintf(displayBuf, mycountof(displayBuf), _T("%s. ( realUrl %s )"), displayBuf, CQyString(pIpDev->urls[0].url));
			}
		}
		//
		//
		::SendMessage(m_var.hCtrl_onvifList, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)displayBuf);
		if (pRule->usIndex_obj == m_var.onvif.usIndex_obj_sel) {
			//
			::SendMessage(m_var.hCtrl_onvifList, LB_SETCURSEL, (WPARAM)i, (LPARAM)0);
		}
		//
		continue;
	}
#endif
	//
	//displayOnvifList();


	iRet = 0;
errLabel:
	return  iRet;
}


int  CDlgShareDynBmps_qt::closeTaskAv(unsigned  int  uiObjType, int  index_pShare_mem)
{
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;

	return  pFuncs->shareDynBmps.pf_dlgShareDynBmps_closeTaskAv(m_hWnd, &m_var, uiObjType, index_pShare_mem);
}


int  getRemoteStorageCfg(REMOTE_storage_cfg* pCfg)
{
	QY_MC* pQyMc = QY_GET_GBUF();

	QY_REG			reg;
	TCHAR* pRegVal = NULL;
	TCHAR			tBuf[256] = _T("");

	if (!pCfg)  return  -1;
	memset(pCfg, 0, sizeof(pCfg[0]));

	memset(&reg, 0, sizeof(reg));
	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	lstrcpyn(reg.rootKey, CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), mycountof(reg.rootKey));

	pRegVal = (TCHAR*)CONST_regValName_remoteStorageUsers;
	if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, sizeof(tBuf), 0)) {
		tBuf[0] = 0;
	}
	if (tBuf[0])
	{
		getUi64IdFromReg(tBuf, pCfg->idInfos_allowed, mycountof(pCfg->idInfos_allowed));
	}

	return  0;
}

int  CDlgShareDynBmps_qt::dlgShareDynBmps_OnQyComm(HWND  hDlg, void* pDLG_Share_var, WPARAM  wParam, LPARAM  lParam)
{
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;

	return  pFuncs->shareDynBmps.pf_dlgShareDynBmps_OnQyComm(g_pQyMc, hDlg, pDLG_Share_var, wParam, lParam);
}

int  CDlgShareDynBmps_qt::dlgShareDynBmps_OnQyPostComm(HWND  pDlg, void* pDLG_Share_var, WPARAM  wParam, LPARAM  lParam)
{
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;

	return  pFuncs->shareDynBmps.pf_dlgShareDynBmps_OnQyPostComm(g_pQyMc, pDlg, pDLG_Share_var, wParam, lParam);
}

bool CDlgShareDynBmps_qt::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
{
	Q_UNUSED(eventType);
	MSG* msg = reinterpret_cast<MSG*>(message);

	//
	switch (msg->message)
	{
	case  CONST_qyWm_comm:
	{
		//
		HWND  hDlgTalk = (HWND)this->winId();
		//DLG_shareDynBmps_var* pm_var = get_pm_var();

		////
		//QY_WMBUF_COMM* pWmBuf = (QY_WMBUF_COMM*)msg->lParam;
		//if (msg->wParam == CONST_qyWmParam_getObjAddr) {
		//	pWmBuf->u.getObjAddr.pObjAddr = this;
		//	*result = CONST_qyWmRc_ok;
		//	return  true;
		//}
		////
		//if (pWmBuf->uiType == CONST_misMsgType_input) {

		//	MIS_MSG_INPUT* pMsg = (MIS_MSG_INPUT*)pWmBuf;
		//	IM_CONTENTU* pContent = NULL;
		//	int					i;
		//	//
		//	if (isUcFlgRouteTalkData(pMsg->ucFlg) || isUcFlgTalkData(pMsg->ucFlg))  pContent = (IM_CONTENTU*)pMsg->data.buf;
		//	else  pContent = (IM_CONTENTU*)&pMsg->data;

		//	if (pContent->uiType == CONST_imCommType_confReq) {
		//		if (isUcFlgResp(pMsg->ucFlg)) {
		//			//
		//			HWND  hTalk = (HWND)this->winId();
		//			//
		//			if (!isRcOk(pMsg->usCode)) {
		//				talk_doAv(hTalk, pm_var->addr.idInfo, true);
		//			}
		//			//
		//			*result = CONST_qyWmRc_ok;
		//			return  true;
		//		}
		//	}

		//}
		//
		*result = dlgShareDynBmps_OnQyComm(hDlgTalk, &this->m_var, msg->wParam, msg->lParam);

	}
	//						 
	return  true;
	break;
	
	case  CONST_qyWm_postComm:
	{
		//
		HWND  hDlgTalk = (HWND)this->winId();
		
		*result = dlgShareDynBmps_OnQyPostComm(hDlgTalk, &this->m_var, msg->wParam, msg->lParam);
	}
	//
	return  true;
	break;
	case  WM_CLOSE:
		//this->closeCDlgTalk_qt();
		return  true;
		break;
	default:
		//
		if (msg->message == WM_MOUSEMOVE)
		{
			int  i = 0;
		}
		//
		break;
	}

	return  QWidget::nativeEvent(eventType, message, result);
}

BOOL CDlgShareDynBmps_qt::dlgShareDynBmps_Create(const RECT& rect)
{

	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet = FALSE;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProc = QY_GET_procInfo_isCli();

	/*
	if  (  !m_var.bInfoSet  )  {
		traceLogA(  "CDlgTalk::Create(  ): ÔÚ´´½¨¶Ô»°¿òÖ®Ç°Ó¦ÏÈÉèÖÃ³õÊ¼Êý¾Ý"  );
		return  FALSE;
	}
	*/

	if (pQyMc->iServiceId != CONST_qyServiceId_is)  return  FALSE;

	m_var.pMisCnt = getMisCntByName(pProc, _T(""));
	if (!m_var.pMisCnt)  goto  errLabel;

	//
	//cw if (!CDialog::Create(this->m_var.m_nID, CWnd::FromHandle(m_var.m_hParent)))  goto  errLabel;

	//
	m_var.bCreated = TRUE;

	bRet = TRUE;
errLabel:
	return  bRet;
}

int  CDlgShareDynBmps_qt::dlgShareDynBmps_OnDestroy()
{
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return -1;

	int				i, j;

	MACRO_qyAssert(!m_var.uiTimerId, _T("dlgShareDynBmps, OnDestroy uiTimeId"));

	MACRO_qyAssert(!m_var.uiTimerId_test, _T("dlgShareDynBmps, OnDestroy uiTimeId_test"));

	//  2012/04/17
	MACRO_qyAssert(!m_var.pComPort_gps, _T("dlgShareDynBmps, OnDestroy, pComPort_gps"));

	//  2016/06/16
	exitShareDynBmsThread(pProcInfo, &m_var.shareDynBmpsThreadInfo);


	//  2011/10/31
	for (i = 0; i < mycountof(m_var.recvdReqs); i++) {
		MACRO_safeFree(m_var.recvdReqs[i].pMsg);
	}

	//
	MACRO_safeFree(m_var.pMsgBuf_doWnd_guiMsgArrive);		//  2009/12/10

	SHARE_dynBmps* pShare;
	for (j = 0; j < mycountof(m_var.shares); j++) {
		pShare = &m_var.shares[j];
		//
		for (i = 0; i < pShare->usCnt; i++) {
			//CHelp_shareDynBmp  help_dynBmpMem;
			SHARE_dyn_bmp* pDynBmpMem = &pShare->mems_internal[i];	//  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  pShare->uiObjType,  i  );
			if (!pDynBmpMem)  continue;
			//
			if (pDynBmpMem->var.ucbLocalVideoOpen) {
				//  closeTaskAv(  pShare->uiObjType,  i  ); 
				closeTaskAv(pDynBmpMem->resObj.uiObjType, i);
			}
		}
	}

	//int  idc_dst  =  m_var.idc;
	//old_freeCapImages(this->m_hWnd, m_var.hWndIDC, &m_var.images, m_var.hWndIDC ? m_var.hWndIDC : m_hWnd/*old_M_GetDlgItem(  m_hWnd,  idc_dst  )*/, &m_var.hDc, _T("dlgShareDynBmps.OnDestroy.2105"));
	freeCapImages(this->m_hWnd, m_var.hWndIDC, &m_var.images, m_var.hWndIDC ? m_var.hWndIDC : m_hWnd/*old_M_GetDlgItem(  m_hWnd,  idc_dst  )*/, &m_var.hDc );

	//
	mytime(&m_var.tLastModifiedTime);
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_sndDynBmpsInfo(m_hWnd, &m_var);

	pFuncs->pf_CAP_STUFF_free(m_var.pCapStuff1);

	return 0;

}

int CDlgShareDynBmps_qt::dlgShareDynBmps_OnInitDialog()
{

#ifdef  __WINCE__
	return  FALSE;
#else

	int						iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  FALSE;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return FALSE;

	/*cw
	cusDlgRes(0, &pQyMc->cusRes, this->m_hWnd, this->IDD);
	TCHAR	tBuf[128];
	MIS_CNT* pMisCnt = getMisCntByIndex(0, pProcInfo, 0);
	if (!pMisCnt)  goto  errLabel;
	_sntprintf(tBuf, mycountof(tBuf), _T("%s: %s"), pMisCnt->displayName, getResStr(0, &pQyMc->cusRes, this->IDD));
	SetWindowText(tBuf);*/

	//
	m_var.bUseDirectX = pQyMc->cfg.bUseDxSurface;
	//m_var.idc = IDC_STATIC_pic0;
	m_var.hWndIDC = (HWND)ui->widget_pic0->winId();

	//
	this->sizeAllControls();

	////
	//if (pProcInfo->cfg.policy.ucbDlgShareDynBmps_autopopupandhideOnStartup) {
	//	int  idc = IDC_CHECK_autoPopupAndHideOnStartup;
	//	((CButton*)GetDlgItem(idc))->SetCheck(1);

	//}

	//
	SHARE_dynBmps* pShare;

	pShare = getShareDynBmpsBySth(CONST_objType_screen);
	if (pShare) {
		//pShare->uiObjType  =  CONST_objType_screen;
		pShare->pTable_ctrls = mynull;//CONST_controls_table_screen;
		pShare->usCnt = mycountof(pShare->mems_internal);
	}
	pShare = getShareDynBmpsBySth(CONST_objType_webcam);
	if (pShare) {
		//pShare->uiObjType  =  CONST_objType_webcam;
		pShare->pTable_ctrls = mynull;// CONST_controls_table_webcam;
		pShare->usCnt = mycountof(pShare->mems_internal);
	}
	pShare = getShareDynBmpsBySth(CONST_objType_rtspStream);
	if (pShare) {
		//pShare->uiObjType  =  CONST_objType_rtspStream;
		pShare->pTable_ctrls = mynull;
		pShare->usCnt = mycountof(pShare->mems_internal);
	}
	pShare = getShareDynBmpsBySth(CONST_objType_smallStream);
	if (pShare) {
		pShare->pTable_ctrls = mynull;
		pShare->usCnt = mycountof(pShare->mems_internal);
	}
	pShare = getShareDynBmpsBySth(CONST_objType_ic);
	if (pShare) {
		pShare->pTable_ctrls = mynull;
		pShare->usCnt = mycountof(pShare->mems_internal);
	}

	
	//
	unsigned  int  uiObjType = CONST_objType_screen;
	pShare = getShareDynBmpsBySth(CONST_objType_screen);
	if (!pShare)  goto  errLabel;
	if (pShare->usCnt) {
#if  0
		pShare->mems_internal[0].usIndex_obj = CONST_usIndex_screen0;	//  2014/05/31
		//
		lstrcpyn(pShare->mems_internal[0].name, getResStr(0, &pQyMc->cusRes, CONST_resId_fullScreenSharing), mycountof(pShare->mems_internal[0].name));
#endif
		CHelp_shareDynBmp  help_dynBmpMem;
		SHARE_dyn_bmp* pDynBmpMem = help_dynBmpMem.getMemByIndex(m_hWnd, &m_var, uiObjType, 0);
		if (pDynBmpMem) {
			pDynBmpMem->resObj.uiObjType = uiObjType;
			pDynBmpMem->resObj.usIndex_obj = CONST_usIndex_screen0;
			//
			lstrcpyn(pDynBmpMem->name, getResStr(0, &pQyMc->cusRes, CONST_resId_fullScreenSharing), mycountof(pDynBmpMem->name));

			//
			refreshShareCfg_screen(uiObjType, pDynBmpMem->resObj.usIndex_obj);
		}
	}

	//

	uiObjType = CONST_objType_smallStream;
	pShare = getShareDynBmpsBySth(uiObjType);
	if (!pShare)  goto  errLabel;
	if (pShare->usCnt) {
#if  0
		pShare->mems_internal[0].usIndex_obj = CONST_usIndex_screen0;	//  2014/05/31
		//
		lstrcpyn(pShare->mems_internal[0].name, getResStr(0, &pQyMc->cusRes, CONST_resId_fullScreenSharing), mycountof(pShare->mems_internal[0].name));
#endif
		CHelp_shareDynBmp  help_dynBmpMem;
		SHARE_dyn_bmp* pDynBmpMem = help_dynBmpMem.getMemByIndex(m_hWnd, &m_var, uiObjType, 0);
		if (pDynBmpMem) {
			pDynBmpMem->resObj.uiObjType = uiObjType;
			pDynBmpMem->resObj.usIndex_obj = CONST_usIndex_avStream_slave;
			//
			lstrcpyn(pDynBmpMem->name, _T("smallStream"), mycountof(pDynBmpMem->name));

			//
			//refreshShareCfg_avStream( uiObjType,  pDynBmpMem->resObj.usIndex_obj  );
			pDynBmpMem->var.ucbLocalVideoOpen = TRUE;
		}
	}


	//
	/*m_var.pCapStuff1 = pFuncs->pf_CAP_STUFF_new();
	if (!m_var.pCapStuff1)  goto  errLabel;
	pFuncs->moniker.pf_addDevicesToMenu(m_var.pCapStuff1, TRUE, NULL);*/

	//  traceLogA(  "sizeof gcap %d",  sizeof(  gcap  )  );
	uiObjType = CONST_objType_webcam;
	pShare = getShareDynBmpsBySth(uiObjType);
	if (!pShare)  goto  errLabel;

	//CAP_STUFF& gcap = *(CAP_STUFF*)m_var.pCapStuff1;

	//
	/*if (!gcap.rgpmVideoMenu[0])  pProcInfo->status.vName_1st_webcam[0] = 0;
	else  pFuncs->moniker.pf_getMonikerProp(gcap.rgpmVideoMenu[0], CONST_moniker_FriendlyName, pProcInfo->status.vName_1st_webcam, mycountof(pProcInfo->status.vName_1st_webcam));*/


	//
	int  i, j;
#if  0  //  2017/06/08
	for (i = 0, j = 0; i < mycountof(gcap.rgpmVideoMenu); i++) {
		CHelp_shareDynBmp  help_dynBmpMem;
		SHARE_dyn_bmp* pDynBmpMem = NULL;

		if (!gcap.rgpmVideoMenu[i])  continue;

		//
		pDynBmpMem = help_dynBmpMem.getMemByIndex(m_hWnd, &m_var, uiObjType, j);
		if (!pDynBmpMem)  continue;
		//
		pDynBmpMem->resObj.uiObjType = uiObjType;
		pDynBmpMem->resObj.usIndex_obj = j + 1;	//  2014/05/31
		//
		pDynBmpMem->iMenuId = ID_MENU_VDEVICE0 + i;	//  gcap.iMenuIds_video[i];
		//  lstrcpyn(  pShare->mems[j].name,  gcap.names_video[i],  mycountof(  pShare->mems[j].name  )  );
		//  getMonikerFriendlyName(  gcap.rgpmVideoMenu[i],  pShare->mems[j].name,  mycountof(  pShare->mems[j].name  )  );
		pFuncs->moniker.pf_getMonikerProp(gcap.rgpmVideoMenu[i], CONST_moniker_FriendlyName, pDynBmpMem->name, mycountof(pDynBmpMem->name));
		j++;
		if (j >= pShare->usCnt)  break;
	}
#endif
	//  2017/06/08
	for (j = 0; j < pShare->usCnt; j++) {
		CHelp_shareDynBmp  help_dynBmpMem;
		SHARE_dyn_bmp* pDynBmpMem = NULL;

		//
		pDynBmpMem = help_dynBmpMem.getMemByIndex(m_hWnd, &m_var, uiObjType, j);
		if (!pDynBmpMem)  continue;
		//
		pDynBmpMem->resObj.uiObjType = uiObjType;
		pDynBmpMem->resObj.usIndex_obj = j + 1;	//  2014/05/31
		//
#if 0
		WEBCAM_info  webcamInfo;
		getWebcamInfo(pDynBmpMem->resObj.usIndex_obj, &webcamInfo);
		//
		safeTcsnCpy(webcamInfo.vName, pDynBmpMem->name, mycountof(pDynBmpMem->name));
		if (webcamInfo.aName[0])  _sntprintf(pDynBmpMem->name, mycountof(pDynBmpMem->name), _T("%s (%s)"), pDynBmpMem->name, webcamInfo.aName);


		//
		TCHAR  tName[256];
		for (i = 0; i < mycountof(gcap.rgpmVideoMenu); i++) {
			if (!gcap.rgpmVideoMenu[i])  continue;
			//
			pFuncs->moniker.pf_getMonikerProp(gcap.rgpmVideoMenu[i], CONST_moniker_FriendlyName, tName, mycountof(tName));
			//
			if (_tcsicmp(tName, webcamInfo.vName))  continue;
			//
			break;
		}
		if (i == mycountof(gcap.rgpmVideoMenu))  continue;
		//
		pDynBmpMem->iMenuId = ID_MENU_VDEVICE0 + i;
#endif
		//
		this->refreshShareCfg_webcam(uiObjType, pDynBmpMem->resObj.usIndex_obj);
		//
		continue;
	}

	//
	uiObjType = CONST_objType_ic;
	pShare = getShareDynBmpsBySth(uiObjType);
	if (!pShare)  goto  errLabel;

	for (j = 0; j < pShare->usCnt; j++) {
		CHelp_shareDynBmp  help_dynBmpMem;
		SHARE_dyn_bmp* pDynBmpMem = NULL;

		//
		pDynBmpMem = help_dynBmpMem.getMemByIndex(m_hWnd, &m_var, uiObjType, j);
		if (!pDynBmpMem)  continue;
		//
		pDynBmpMem->resObj.uiObjType = uiObjType;
		pDynBmpMem->resObj.usIndex_obj = j + 1;	//  2014/05/31
		//

	}

	//
	mytime(&m_var.tLastModifiedTime);

	this->refreshShareStatus(0);

	

#if  0

	//  2014/05/02
	if (!bSupported_rtsp()) {
		::ShowWindow(::GetDlgItem(m_hWnd, IDC_STATIC_rtsp), SW_HIDE);
		::ShowWindow(::GetDlgItem(m_hWnd, IDC_LIST1), SW_HIDE);
		::ShowWindow(::GetDlgItem(m_hWnd, IDC_BUTTON_add), SW_HIDE);
		::ShowWindow(::GetDlgItem(m_hWnd, IDC_BUTTON_procRtsp), SW_HIDE);
		::ShowWindow(::GetDlgItem(m_hWnd, IDC_BUTTON_del), SW_HIDE);
		::ShowWindow(::GetDlgItem(m_hWnd, IDC_BUTTON_selfTest), SW_HIDE);
	}
	else {
#if  0
		int idc = IDC_BUTTON_selfTest;
		GetDlgItem(idc)->EnableWindow(FALSE);
#endif
	}

	//  2012/05/23
	if (!bSupported_gps(pQyMc)) {
		GetDlgItem(IDC_STATIC_gps)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_gpsStatus)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_gps)->ShowWindow(SW_HIDE);
	}

	//  2014/08/03
#if  0  //  为了允许正式版客户端视频被远程存储，所以需要开放这个设置
	if (!bSupported_remoteStorage()) {
		::EnableWindow(::GetDlgItem(m_hWnd, IDC_BUTTON_remoteStorageSettings), FALSE);
	}
#endif

#endif

	/*if (bQnmDemo()) {
		SetDlgItemText(IDC_STATIC_pic0, getResStr(0, &pQyMc->cusRes, CONST_resId_warning_restrictSharedDymBmps));
	}*/

	//  2009/12/10
	m_var.pMsgBuf_doWnd_guiMsgArrive = (MIS_MSGU*)mymalloc(sizeof(MIS_MSGU));
	if (!m_var.pMsgBuf_doWnd_guiMsgArrive)  goto  errLabel;

	//  2011/10/31
	for (i = 0; i < mycountof(m_var.recvdReqs); i++) {
		m_var.recvdReqs[i].pMsg = (MIS_MSGU*)mymalloc(sizeof(MIS_MSGU));
		if (!m_var.recvdReqs[i].pMsg)  goto  errLabel;
	}

	//  2012/05/6
	if (bTEST_shareScreen(0, 0)) {
		showNotification(0, 0, 0, 0, 0, 0, _T("TEST share screen"));
	}

	

	//
	/*cw
	m_var.hCtrl_onvifList = ::GetDlgItem(m_hWnd, IDC_LIST1);
	reloadOnvifList();
	*/
	reloadOnvifList();

	//  2014/08/06
	getRemoteStorageCfg(&m_var.saveVideo.cfg);

	//return 0;

	//  2016/06/16
	if (initShareDynBmpsThread(pProcInfo, m_hWnd, &m_var, &m_var.shareDynBmpsThreadInfo)) {
		goto  errLabel;
	}

	//
	//if (pProcInfo->cfg.policy.ucbDlgShareDynBmps_autopopupandhideOnStartup) {
	//	if (!pProcInfo->ucbAutoOpenChked) {
	//		pProcInfo->ucbAutoOpenChked = TRUE;
	//		//
	//		chkAutoOpen();
	//	}

	//}

	//
	//m_var.nElapseInMs = 1000;	//  5000;
	//m_var.uiTimerId = SetTimer(1, m_var.nElapseInMs, NULL);
	m_var.nElapseInMs = 1000;
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &CDlgShareDynBmps_qt::onTimer);
	timer->start(m_var.nElapseInMs);

	//  2012/04/29
	/*if (pProcInfo->cfg.ucbTestGps) {
		m_var.nElapseInMs_test = 1000;
		m_var.uiTimerId_test = SetTimer(2, m_var.nElapseInMs_test, NULL);
	}*/


	//
	iErr = 0;

	pProcInfo->hWnd_shareDynBmps = this->m_hWnd;

	toShareWebcam(CONST_objType_ic, 1);

errLabel:

	/*if (iErr) {
		PostMessage(WM_CLOSE, 0, 0);
	}*/
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE

#endif
}

SHARE_dynBmps* CDlgShareDynBmps_qt::getShareDynBmpsBySth(int  uiObjType)
{

	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  NULL;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  NULL;

	//  return   (  SHARE_dynBmps  *  )pFuncs->shareDynBmps.pf_dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  uiObjType  );


	return   (SHARE_dynBmps*)dlgShareDynBmps_getShareDynBmpsBySth(m_hWnd, &m_var, uiObjType);
}


int  CDlgShareDynBmps_qt::toShareScreen_func(int  index_pShare_mem)
{
	int					iErr = -1;
	SHARE_dynBmps* pShare;
	unsigned  int  uiObjType = CONST_objType_screen;
	pShare = getShareDynBmpsBySth(CONST_objType_screen);
	if (!pShare)  return  -1;
	CHelp_shareDynBmp  help_dynBmpMem;
	SHARE_dyn_bmp* pDynBmpMem = NULL;

	//if  (  index_pShare_mem  <  0  ||  index_pShare_mem  >=  pShare->usCnt  )  return  -1;
	pDynBmpMem = help_dynBmpMem.getMemByIndex(m_hWnd, &m_var, uiObjType, index_pShare_mem);
	if (!pDynBmpMem)  return  -1;

	//  2012/05/11 在点击启动共享后，就可以不必保持置前状态了
#if  0
	if (m_var.bNeed_shareWebcamInConference) {
		m_var.bNeed_shareWebcamInConference = FALSE;
	}
#endif


	//
	//if  (  pShare->mems[index_pShare_mem].var.ucbLocalVideoOpen  )  
	if (pDynBmpMem->var.ucbLocalVideoOpen)
	{
		closeTaskAv(uiObjType, index_pShare_mem);

		mytime(&m_var.tLastModifiedTime);

		this->refreshShareStatus(CONST_objType_screen);

		iErr = 0;  goto  errLabel;
	}

	int  iParam; iParam = index_pShare_mem;
	toSelectRegion1(m_hWnd, TRUE, FALSE, FALSE, 0, iParam);

	/*int  n;
	n = getnItems(pShare->pTable_ctrls);
	if (n > index_pShare_mem) {
		CWnd* p = GetDlgItem((int)pShare->pTable_ctrls[index_pShare_mem].pData);
		if (p)  p->EnableWindow(FALSE);
	}*/

	iErr = 0;
errLabel:


	return  iErr;
}


//int  CDlgOpScreen::refreshCtrlStatus()

BOOL  dlgShareDynBmps_bShared(CDlgShareDynBmps_qt* pDlg, unsigned int  uiObjType, int  index_obj)
{
	BOOL  bRet = FALSE;
	CHelp_shareDynBmp  help_shareDynBmpMem;

	/*CDlgShareDynBmps* pDlg = (CDlgShareDynBmps*)CDlgShareDynBmps::FromHandlePermanent(hDlg_shareDynBmps);
	if (!pDlg)  goto  errLabel;*/

	//
	int  index_pShare_mem = 0;

	//
	switch (uiObjType) {
	case  CONST_objType_screen:
	case  CONST_objType_webcam:
		index_pShare_mem = index_obj - 1;
		break;
	default:
		goto  errLabel;
	}

	//
	SHARE_dyn_bmp* pDynBmpMem; pDynBmpMem = help_shareDynBmpMem.getMemByIndex(pDlg->m_hWnd, &pDlg->m_var, uiObjType, index_pShare_mem);
	if (!pDynBmpMem)  goto  errLabel;

	if (!bShared(pDynBmpMem))  goto  errLabel;


	bRet = TRUE;

errLabel:
	return  bRet;

}

int  CDlgShareDynBmps_qt::refreshCtrlStatus(int index_obj_selected)
{
	int  idc;
	BOOL  bEnable = TRUE;
	QY_MC* pQyMc = QY_GET_GBUF();
	TCHAR  tBuf[256];

	//
	if (dlgShareDynBmps_bShared(this, CONST_objType_screen, index_obj_selected/*m_var.index_obj_selected*/)) {
		bEnable = FALSE;
	}


	//
	//idc = IDC_BUTTON_toShare;
	//if (bEnable) {
	//	//
	//	_sntprintf(tBuf, mycountof(tBuf), _T("%s"), getResStr(0, &pQyMc->cusRes, CONST_resId_startSharing));
	//}
	//else {
	//	_sntprintf(tBuf, mycountof(tBuf), _T("%s"), getResStr(0, &pQyMc->cusRes, CONST_resId_stopSharing));
	//}
	////
	//::SetDlgItemText(m_hWnd, idc, tBuf);


	//
	return  0;
}

int  CDlgShareDynBmps_qt::toShareScreen(int  index_pShare_mem)
{
	//showDlgOpScreen(m_hWnd, m_hWnd, index_pShare_mem + 1);
	int m_var_index_obj_selected = index_pShare_mem + 1;

	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return -1;

	int  idc;
	TCHAR  tBuf[256];

	//
	int				uiCapType = CONST_capType_av;
	int				uiSubCapType = CONST_subCapType_webcam;


	QY_REG			reg;
	memset(&reg, 0, sizeof(reg));

	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	//  _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
	getRegRootKey_qmc(uiCapType, uiSubCapType, 0, reg.rootKey, mycountof(reg.rootKey));
	_sntprintf(reg.rootKey, mycountof(reg.rootKey), _T("%s\\%s"), reg.rootKey, _T(CONST_regKeyName_screen));
	_sntprintf(reg.rootKey, mycountof(reg.rootKey), _T("%s\\%d"), reg.rootKey, index_pShare_mem/*m_var.index_obj_selected*/);

	//
	TCHAR  tName[128] = _T("tt");

	//
		//
	/*idc = IDC_EDIT_name;
	GetDlgItemText(idc, tName, mycountof(tName));
	tTrim(tName);*/

	qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_name, tName);




	//
	/*idc = IDC_CHECK_autoOpenOnStartup;
	BOOL  bVal = (((CButton*)GetDlgItem(idc))->GetCheck() == BST_CHECKED) ? 1 : 0;
	if (bVal) {
		qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_ucbAutoOpenOnStartup, _T("1"));

	}
	else {
		qyDelRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_ucbAutoOpenOnStartup);
	}*/


	toShareScreen_func(m_var_index_obj_selected/*m_var.index_obj_selected*/ - 1);
	//dlgShareDynBmps_toShareScreen_func(m_var.hDlg_shareDynBmps, m_var.index_obj_selected - 1);

	//
	refreshCtrlStatus(m_var_index_obj_selected);

	//
	this->refreshShareCfg_screen(CONST_objType_screen, m_var_index_obj_selected);

	return  0;
}

void CDlgShareDynBmps_qt::onShareScreenButtonClicked()
{
	//CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	toShareScreen(0);

}

int  CDlgShareDynBmps_qt::toShareWebcam_func(int  objType, int  index_pShare_mem, void** ppCapStuff, int  iMenuId_v, BOOL  bUnresizable)
{
	int  iErr = -1;

	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;


	//
	unsigned  int  uiObjType = objType;// CONST_objType_webcam;

	CHelp_shareDynBmp  help_shareDynBmpMem;
	SHARE_dyn_bmp* pDynBmpMem = help_shareDynBmpMem.getMemByIndex(m_hWnd, &m_var, uiObjType, index_pShare_mem);
	if (!pDynBmpMem)  return  -1;

	if (pDynBmpMem->var.ucbLocalVideoOpen) {

		pFuncs->shareDynBmps.pf_dlgShareDynBmps_closeTaskAv(m_hWnd, &m_var, uiObjType, index_pShare_mem);
		return  0;
	}

	//
	if (iMenuId_v)  pDynBmpMem->iMenuId = iMenuId_v;

	//
	if (!pDynBmpMem->iMenuId)  goto  errLabel;



	//
	//  这里要选择音频和视频设备					

	//  2015/10/22	



	//
	AV_COMPRESSOR_CFG* pAvCompressor; pAvCompressor = NULL;
	TASK_av_props  avProps;
	memset(&avProps, 0, sizeof(avProps));

	//
	AV_COMPRESSOR_CFG		mediaDeviceCompressor;
	if (bUnresizable || objType == CONST_objType_ic) {
		unsigned  int  uiSubCapType = CONST_subCapType_unresizable;
		int  level = 0;
		if (myGetAvCompressorCfg(CONST_capType_mediaDevice, uiSubCapType, 0, level, &mediaDeviceCompressor))  goto  errLabel;

		if (objType == CONST_objType_ic) {
			mediaDeviceCompressor.video.common.ucCompressors = CONST_videoCompressors_hwAccl;
			iFourcc2Str(CONST_fourcc_HEVC, mediaDeviceCompressor.video.common.fourccStr, mycountof(mediaDeviceCompressor.video.common.fourccStr));
		}

		//
		pAvCompressor = &mediaDeviceCompressor;
		//
		avProps.v.ucAvFlg |= CONST_avFlg_unresizable;
	}
	//

	//
	if (pFuncs->shareDynBmps.pf_dlgShareDynBmps_toShareDynBmp(g_pQyMc, m_hWnd, &m_var, objType, index_pShare_mem, ppCapStuff, pAvCompressor, &avProps))  goto  errLabel;

	iErr = 0;

errLabel:


	return  iErr;
}

int CDlgShareDynBmps_qt::shareWebcam(int objType, int  index_pShare_mem)
{
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return -1;

	if (m_varAVDev.pCapStuff == nullptr) {
		CAP_STUFF* pCapStuff = NULL;


		//
		pCapStuff = (CAP_STUFF*)pFuncs->pf_CAP_STUFF_new();
		if (!pCapStuff)  goto  errLabel;
		pFuncs->moniker.pf_addDevicesToMenu(pCapStuff, TRUE, NULL);

		//
		m_varAVDev.pCapStuff = pCapStuff;
	}

	m_varAVDev.objType = objType;
	m_varAVDev.index_obj_selected = index_pShare_mem;

	int  idc;
	TCHAR  tBuf[256];
	int  index_a;
	CAP_STUFF* pCapStuff; pCapStuff = (CAP_STUFF*)m_varAVDev.pCapStuff;

	//
	int				uiCapType; uiCapType = CONST_capType_av;
	int				uiSubCapType; uiSubCapType = CONST_subCapType_webcam;


	QY_REG			reg;
	memset(&reg, 0, sizeof(reg));

	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	//  _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
	getRegRootKey_qmc(uiCapType, uiSubCapType, 0, reg.rootKey, mycountof(reg.rootKey));
	_sntprintf(reg.rootKey, mycountof(reg.rootKey), _T("%s\\%s"), reg.rootKey, _T(CONST_regKeyName_webcam));
	_sntprintf(reg.rootKey, mycountof(reg.rootKey), _T("%s\\%d"), reg.rootKey, m_varAVDev.index_obj_selected);

	//
	TCHAR  tName[128];



	/*cw
	idc = IDC_COMBO_aDev;
	GetDlgItemText(idc, tBuf, mycountof(tBuf));
	if (tBuf[0]) {
		index_a = _ttol(tBuf) - 1;
		//  ChooseDevices(  *pCapStuff,  pCapStuff->pmVideo,  pCapStuff->rgpmAudioMenu[index]  );
		pFuncs->pf_myChooseDevices(pCapStuff, pCapStuff->pmVideo, pCapStuff->rgpmAudioMenu[index_a]);

		//
		tName[0] = 0;
		//  getMonikerFriendlyName(  pCapStuff->rgpmAudioMenu[i],  tName,  mycountof(  tName  )  );
		pFuncs->moniker.pf_getMonikerProp(pCapStuff->rgpmAudioMenu[index_a], CONST_moniker_FriendlyName, tName, mycountof(tName));

		//
		qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_aName, tName);

	}
	else {
		//  ChooseDevices(  *pCapStuff,  pCapStuff->pmVideo,  NULL  );
		pFuncs->pf_myChooseDevices(pCapStuff, pCapStuff->pmVideo, NULL);

		//
		qyDelRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_aName);
	}*/

	if (objType == CONST_objType_ic) {
		pFuncs->pf_myChooseDevices(pCapStuff, pCapStuff->pmVideo, NULL);
		qyDelRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_aName);
	}
	else {

		index_a = 1;
		//  ChooseDevices(  *pCapStuff,  pCapStuff->pmVideo,  pCapStuff->rgpmAudioMenu[index]  );
		pFuncs->pf_myChooseDevices(pCapStuff, pCapStuff->pmVideo, pCapStuff->rgpmAudioMenu[index_a]);

		//
		tName[0] = 0;
		//  getMonikerFriendlyName(  pCapStuff->rgpmAudioMenu[i],  tName,  mycountof(  tName  )  );
		pFuncs->moniker.pf_getMonikerProp(pCapStuff->rgpmAudioMenu[index_a], CONST_moniker_FriendlyName, tName, mycountof(tName));

		//
		qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_aName, tName);
	}

	//
	int  index_v; index_v = 0;
	int  iMenuId_v; iMenuId_v = 0;

	/*cw
	idc = IDC_COMBO_vDev;
	GetDlgItemText(idc, tBuf, mycountof(tBuf));
	if (tBuf[0]) {
		index_v = _ttol(tBuf) - 1;
		//  ChooseDevices(  *pCapStuff,  pCapStuff->rgpmVideoMenu[index],  pCapStuff->pmAudio  );
		pFuncs->pf_myChooseDevices(pCapStuff, pCapStuff->rgpmVideoMenu[index_v], pCapStuff->pmAudio);

		//
		tName[0] = 0;
		//  getMonikerFriendlyName(  pCapStuff->rgpmAudioMenu[i],  tName,  mycountof(  tName  )  );
		pFuncs->moniker.pf_getMonikerProp(pCapStuff->rgpmVideoMenu[index_v], CONST_moniker_FriendlyName, tName, mycountof(tName));

		//
		qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_vName, tName);

		//
		iMenuId_v = index_v + ID_MENU_VDEVICE0;


	}
	else {
		//  ChooseDevices(  *pCapStuff,  NULL,  pCapStuff->pmAudio  );
		pFuncs->pf_myChooseDevices(pCapStuff, NULL, pCapStuff->pmAudio);

		//
		qyDelRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_vName);
	}*/

	pFuncs->pf_myChooseDevices(pCapStuff, pCapStuff->rgpmVideoMenu[index_v], pCapStuff->pmAudio);

	//
	tName[0] = 0;
	//  getMonikerFriendlyName(  pCapStuff->rgpmAudioMenu[i],  tName,  mycountof(  tName  )  );
	pFuncs->moniker.pf_getMonikerProp(pCapStuff->rgpmVideoMenu[index_v], CONST_moniker_FriendlyName, tName, mycountof(tName));

	//
	qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_vName, tName);

	iMenuId_v = index_v + ID_MENU_VDEVICE0;

	/*cw
	idc = IDC_EDIT_name;
	GetDlgItemText(idc, tName, mycountof(tName));
	tTrim(tName);
	qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_name, tName);
	*/
	if (objType == CONST_objType_ic) {
		qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_name, _T("ic"));
	}
	else {
		qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_name, _T("webcam1"));
	}


	//
	/*cw
	idc = IDC_CHECK_ucbUnresizable;
	m_var.bUnresizable = (((CButton*)GetDlgItem(idc))->GetCheck() == BST_CHECKED) ? 1 : 0;
	if (m_var.bUnresizable) {
		qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_ucbUnresizable, _T("1"));
	}
	else {
		qyDelRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_ucbUnresizable);
	}
	*/




	/*cw
	idc = IDC_CHECK_autoOpenOnStartup;
	BOOL  bVal = (((CButton*)GetDlgItem(idc))->GetCheck() == BST_CHECKED) ? 1 : 0;
	if (bVal) {
		qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_ucbAutoOpenOnStartup, _T("1"));

	}
	else {
		qyDelRegCfgT(reg.hKeyRoot0, reg.rootKey, CONST_regValName_ucbAutoOpenOnStartup);
	}


	//
	if (!iMenuId_v) {
		if (!dlgShareDynBmps_bShared(m_var.hDlg_shareDynBmps, CONST_objType_webcam, m_var.index_obj_selected)) {
			//qyShowHint(  _T(  "%s"  ),  _T(  "Camera must be selected"  )  );
			return;
		}
	}
	*/

	//
	//
	//dlgShareDynBmps_toShareWebcam_func(m_var.hDlg_shareDynBmps, m_var.objType, m_var.index_obj_selected - 1, &m_var.pCapStuff, iMenuId_v, m_var.bUnresizable);
	toShareWebcam_func(m_varAVDev.objType, m_varAVDev.index_obj_selected - 1, &m_varAVDev.pCapStuff, iMenuId_v, m_varAVDev.bUnresizable);
	//
	if (!m_varAVDev.pCapStuff) {
		CAP_STUFF* pCapStuff = NULL;

		//	 
		pCapStuff = (CAP_STUFF*)pFuncs->pf_CAP_STUFF_new();
		if (!pCapStuff)  goto  errLabel;
		pFuncs->moniker.pf_addDevicesToMenu(pCapStuff, TRUE, NULL);

		//
		m_varAVDev.pCapStuff = pCapStuff;

	}

	//
	//refreshCtrlStatus();


errLabel:
	return 0;
}

int  CDlgShareDynBmps_qt::toShareWebcam(int objType, int  index_pShare_mem)
{
	int  iErr = -1;

	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;


	//
	//  这里要选择音频和视频设备					

	//  2015/10/22	
	BOOL  bUnresizable = TRUE;

	//
	int  tmpiRet;
	//tmpiRet  =  showDlgSelectAvDev(  m_hWnd,  pCapStuff,  pDynBmpMem->iMenuId,  &bUnresizable  );
	int  index_obj_sel = index_pShare_mem + 1;


	//tmpiRet = showDlgOpAvDev(m_hWnd, m_hWnd, objType, index_obj_sel, &bUnresizable);
	shareWebcam(objType, index_obj_sel);
	//
	//this->refreshShareCfg_webcam(  CONST_objType_webcam,  index_obj_sel  );
	this->refreshShareCfg_webcam(objType, index_obj_sel);

	//	 
	iErr = 0;

errLabel:

	return  iErr;
}

void CDlgShareDynBmps_qt::onWebcam1ButtonClicked()
{
	//CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	toShareWebcam(CONST_objType_webcam, 1);

}

void CDlgShareDynBmps_qt::onIcButtonClicked()
{
	//CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	toShareWebcam(CONST_objType_ic, 1);

}
