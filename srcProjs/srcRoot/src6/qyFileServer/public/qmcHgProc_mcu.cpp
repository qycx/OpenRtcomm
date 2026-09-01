


#include	"stdafx.h"
#include	<stdio.h>
#include	<stddef.h>
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
//  #include	"myresource.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"

#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	<windows.h>
#include	<windef.h>
#include	<lmcons.h>
#ifndef  __WINCE__
#include	<lmshare.h>
#endif
#include	<tlhelp32.h>
#include	<iphlpapi.h>

//  #include	"qwmDynFunc.h"

#include	"qmcCmdProc.h"

#include	"tmpCeLib.h"
#include	"qySqlFunc.h"
#include	"qyThread.h"
#include	"isCmdConst.h"
#include	"qyCusResTemp.h"
//
#include	"policyAvParams.h"


#include	"myDb.h"

#include	"isCliCorePublic.h"
#include	"isCliHelpPublic.h"
#include	"qyMessengerHelpPublic.h"
#include	"imgProcessPublic.h"
#include	"isCliD3dPublic.h"
#include	"qisWallsProc.h"
#include	"qmcObjVarPublic.h"
#include	"qmcTaskPublic.h"
#include	"qmcSharePublic.h"
#include	"dlgShareDynBmpsProc.h"
#include	"funcsForIsCliHelp.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliExPublic.h"
#include	"ctxMcThread.h"

//
#include	"qmcVideoTool.h"
//#include	"ctxQmc_gui.h"
#include	"policyAvParams.h"
#include	"qyAvRecordPublic.h"
//#include	"qmcVideoCapture_isCli.h"
//#include	"qmcCommFunc_isCli.h"
#include	"qmcCmdProc.h"
#include	"qyMcMainWndProc.h"
#include	<shellapi.h>
#include	"resource.h"

#include	"smCommProc.h"
#include	"dlgtalkproc.h"
#include	"hgCommProc.h"
#include <ctxQmc_qyMcu.h>

//
//
int mcu_send_xt(int talk_loopCtrl, QY_MESSENGER_ID  idInfo_conf)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	bool  bSkip = false;

	Param_dbg param;
	param.m_bShowInfo = false;
	if (!bChannelOk(getChannelByType(pMisCnt, 0), &param))  return  -1;
	//
	if (!pProcInfo->av.doConf.confReq.idInfo_imGrp_related.ui64Id)  return  -1;


	//
	bool bNeedXtNow = false;

	//
	int intervalInS = CONST_intervalInS_mcuXt;
	if (!pProcInfo->xt.bGotOnce_xtResp) {		//  第一次时，需要尽快得到xt_resp
		intervalInS = 3;
	}
	//
	if (!bNeedXtNow) {
		if ((talk_loopCtrl % intervalInS)) {
			return  -1;
		}
	}


	//
	MACRO_prepareForTran();
	QIS_ca_req  req;

	//
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_qisCaReq;



	//  将电话告知的设备授权码+证书的唯一标识，送到会管服务器
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "[cmd=%d]", CONST_hgCmd_mcuXt);
	char idStr[CONST_qyMessengerIdStrLen + 1];
	idInfo2Str(&idInfo_conf, idStr, mycountof(idStr));
	_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "%s [obj=%d len=%d]%s", req.ca_cliData, CONST_hgType_grpIdInfo, strlen(idStr), idStr);
	//
#ifdef  __DEBUG__
#endif

	//
	req.ca_cliDataLen = strlen(req.ca_cliData);

	//
	int len = sizeof(req);
	pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);

	//
	pProcInfo->xt.nTimes_waitForXtResp++;

	//
	TCHAR  tBuf[128];


	_sntprintf(tBuf, mycountof(tBuf), (TCHAR*)_T("22mcu_send_xt, nTimes_waitForXtResp %d"), pProcInfo->xt.nTimes_waitForXtResp);
	showInfo_open0(0, 0, tBuf);

	//
	return  0;

}



//
int mcuProc_xt_resp(Param_sxrz_servReply* pParam)
{
	int  iErr = -1;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	TCHAR  tBuf[128];
	char  buf[128];

	//
	do {

		//
		_sntprintf(tBuf, mycountof(tBuf), _T("recv mcuXtResp: rc %d"), pParam->iRc);
		showInfo_open0(0, 0, tBuf);

		//
		if (pParam->iRc == CONST_hgRc_mcuNeedDown) {
			waitToQuit_isCli(pProcInfo, 1000, _T("mcuProc_xt_resp.163"));
		}


		//
		pProcInfo->xt.dwTickCnt_lastXtResp = myGetTickCount(nullptr);
		pProcInfo->xt.nTimes_waitForXtResp = 0;
		pProcInfo->xt.bGotOnce_xtResp = true;

		
		//
		//
		iErr = 0;
	} while (false);

	return  iErr;
}


