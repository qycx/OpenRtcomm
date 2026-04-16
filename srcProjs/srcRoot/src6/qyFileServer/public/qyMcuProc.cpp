

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
#include	"ctxQmc_qyMcu.h"
#include	"policyAvParams.h"
#include	"qyAvRecordPublic.h"
//#include	"qmcVideoCapture_isCli.h"
//#include	"qmcCommFunc_isCli.h"
#include	"qmcCmdProc.h"
#include	"qyMcMainWndProc.h"
#include	<shellapi.h>
#include	"resource.h"

//
#include	"dlgtalkproc.h"
#include <GuiShare.h>



//
extern  "C"  BOOL  bServConnected_mis(  QY_ENV  *  pEnv,  char  *  serverIp,  unsigned  short  serverPort,  void  *  pParam,  int  serviceId,  char  *  ver,  QY_ENC_CTX  *  pCommEncCtx,  __int64  i64StartTime_base,  SOCK_TIMEOUT  *  pTo  );
 int  set_doConf(CONF_req* pConfReq, LPCTSTR  hint);


 



//
 int  doConf_showDlgMcClientLogon(  HINSTANCE  g_hInst,  HWND  hMainWnd,  void  *  pQyMcParam,  PARAM_showDlgMcLogon  * pParam  )
 {

	int							iErr				=	-1;
	QY_MC  *  pQyMc  =  (  QY_MC  *  )pQyMcParam;

	// TODO: Add your control notification handler code here
	//CDlgMcClientLogon		*	pDlg				=	(  CDlgMcClientLogon  *  )CDlgMcClientLogon::FromHandle(  hDlg  );
	//DLG_mcClientLogon_var	&	m_var				=	pDlg->m_var;
	TCHAR						tBuf[128];

	//
	TCHAR  *  m_name  =  pParam->usrName;
	TCHAR  *  m_passwd  =  pParam->passwd;

	//
	MC_VAR_isCli			*	pProcInfo			=	(  MC_VAR_isCli  *  )pQyMc->get_pProcInfo(  );
	if  (  !pProcInfo  )  return  -1;
	if  (  pProcInfo->m_iCtxType  !=  CONST_ctxType_qmc  )  return  -1;

	//
	char						buf[1024]			=	"";
	unsigned  int				len;

	//
	TCHAR						appObjPrefix[16  +  1]	=	_T(  ""  );			//  2010/03/10
	TCHAR						respHint[128]  =  _T(  ""  );

#ifdef  __DEBUG__
		traceLog(  _T(  "doConf_dlgMcClientLogon_OnOK called"  )  );
#endif
				
	//  2014/02/09
	//if  (  m_var.iSeqNoSelected  <  0  ||  m_var.iSeqNoSelected  >=  mycountof(  m_var.cntCfg  )  )  return  -1;

	//
	//_sntprintf(  appObjPrefix,  mycountof(  appObjPrefix  ),  _T(  "%s%d"  ),  CONST_qmCmdLine_sym_appObjPrefix, m_var.iSeqNoSelected  );
	_sntprintf(appObjPrefix, mycountof(appObjPrefix), _T("%s%u"), CONST_qmCmdLine_sym_appObjPrefix, GetCurrentProcessId());

	#ifndef  __WINCE__
			 //if  (  bAnotherInstanceExists(  pQyMc,  appObjPrefix  )  )  goto  errLabel;
	#endif

	//
	TCHAR						tPrefix[32]			=	_T(  ""  );
	//_sntprintf(  tPrefix,  mycountof(  tPrefix  ),  _T(  "%d: "  ),  m_var.nTries_triggerIDOK  );

	if  (  !bSupported_devAuth(  )  )  
	{

		if  (  !m_name  ||  !m_name[0]  )  goto  errLabel;
		if  (  !m_passwd  ||  !m_passwd[0]  )  goto  errLabel;

		tTrim(  m_name  );
		tTrim(  m_passwd  );
		//
		if  (  !m_name[0]  )  {
			//SetFocus(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_NAME  )  );
			goto  errLabel;
		}
		if  (  !m_passwd[0]  )  {
			//SetFocus(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_PASSWD  )  );
			goto  errLabel;
		}
	
		//
		lstrcpyn(  pProcInfo->authInfo.messengerName,  m_name,  mycountof(  pProcInfo->authInfo.messengerName  )  );
		myTChar2Utf8(  m_passwd,  buf,  mycountof(  buf  )  );
		len  =  mycountof(  pProcInfo->authInfo.messengerPasswd  );
		bQyGetStrMd5_x(  buf,  pProcInfo->authInfo.messengerPasswd,  &len  );
	}

	//  CWaitCursor		cur;
	
	//
	//_sntprintf(  m_var.cntCfg[m_var.iSeqNoSelected].usr,  mycountof(  m_var.cntCfg[m_var.iSeqNoSelected].usr  ),  m_name  );
	//_sntprintf(  m_var.cntCfg[m_var.iSeqNoSelected].passwd,  mycountof(  m_var.cntCfg[m_var.iSeqNoSelected].passwd  ),  m_passwd  );

	//memcpy(  &pQyMc->cfg.dynCfg.cnt,  &m_var.cntCfg[m_var.iSeqNoSelected],  sizeof(  QNM_CNT_CFG  )  );

	//  2010/01/09
	{
	int  index  =  0;
	MIS_CNT  *  pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  index  );
	if  (  !pMisCnt  )  goto  errLabel;
	memcpy(  &pMisCnt->cfg.dynCfg,  &pQyMc->cfg.dynCfg,  sizeof(  pMisCnt->cfg.dynCfg  )  );
	memset(  &pMisCnt->server,  0,  sizeof(  pMisCnt->server  )  );
	}
	//
	int								i;
	QY_LOGICAL_SERVER				tmpCnt;

	//for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
	for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
	{
		 MIS_CNT  *  pMisCnt			=  getMisCntByIndex(  0,  pProcInfo,  i  );//&pProcInfo->misCnts[i];
		 if  (  !pMisCnt  )  continue;
		 MIS_CHANNEL	*	pChannel	=  getChannelByType(  pMisCnt,  CONST_channelType_talking  );
		 if  (  !pChannel  )  continue;

		 if  (  pChannel->bSessionOpen  )  {
			 qnmCloseSession_msg(  mynull, &pChannel->session,  &pChannel->sock,  &pQyMc->cfg.to,  _T("doConf_showDlgMcClientLogon.l187"));
			 pChannel->bSessionOpen  =  FALSE;
		 }

		 if  (  !pChannel->bSessionOpen  )  {
			 
			 pMisCnt->pAuthInfo  =  &pProcInfo->authInfo;
			 clearQySock(  &pChannel->sock  );

			 //  
			 {					   
				 if  (  pMisCnt->cfg.dynCfg.cnt.usCntPort  )  {
					 _sntprintf(  tBuf,  mycountof(  tBuf  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_searchingServer  )  );
					 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: %s, %s, %s; Port: %d"  ),  tBuf,
						 CQyString(  pMisCnt->cfg.dynCfg.cnt.cntIp  ), 	
						 CQyString(  pMisCnt->cfg.dynCfg.cnt.cntAddrs[0]  ),  
						 CQyString(  pMisCnt->cfg.dynCfg.cnt.cntAddrs[1]  ),  
						 pMisCnt->cfg.dynCfg.cnt.usCntPort  );
					 //m_var.guiData.pf_SetDlgItemText(  pDlg->m_hWnd,  m_var.guiData.iIDC_STATIC_hint,  CQyString(  tPrefix  )  +  tBuf  );
					 if  (  getCorrectCnt(  &pQyMc->env,  &pMisCnt->cfg.dynCfg,  bServConnected_mis,  pMisCnt,  pQyMc->iServiceId,  qnmVerStr(  pQyMc->iServiceId  ),  &pMisCnt->commEncCtx.common,  pQyMc->i64StartTime_base,  &pQyMc->cfg.to,  &tmpCnt  )  )  {
						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotFindServer  )  );
						 //m_var.guiData.pf_SetDlgItemText(  pDlg->m_hWnd,  m_var.guiData.iIDC_STATIC_hint,  CQyString(  tPrefix  )  +  tBuf  );
						 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "getCorrectCnt failed"  )  );
						 continue;
						 }
					 else  if  (  memcmp(  &pMisCnt->server,  &tmpCnt,  sizeof(  tmpCnt  )  )  )  {
							   memcpy(  &pMisCnt->server,  &tmpCnt,  sizeof(  pMisCnt->server  )  );
					 }					   
				 }		
			 }
			 if  (  !pMisCnt->commEncCtx.ucbPublicKeyDownloaded  ||  !pMisCnt->commEncCtx.ucbPublicKeyVerified  )  continue;

			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ok"  ),  CQyString(  pMisCnt->server.ip  )  );  
			 //m_var.guiData.pf_SetDlgItemText(  pDlg->m_hWnd,  m_var.guiData.iIDC_STATIC_hint,  tBuf  );			 

			 //m_var.respHint[0]  =  0;
			 if  (  !doMisCntLogon(  pMisCnt,  pChannel,  hMainWnd,  respHint,  mycountof(  respHint  )  )  )  break;
		 
		 }

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s: %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_failedToLogon  ),  CQyString(  pMisCnt->server.ip  ),  respHint  );
		 //m_var.guiData.pf_SetDlgItemText(  pDlg->m_hWnd,  m_var.guiData.iIDC_STATIC_hint,  CQyString(  tPrefix  )  +  tBuf  );

		 continue;
	}

	//if  (  i  ==  mycountof(  pProcInfo->misCnts  )  )  
	if  (  i  ==  pProcInfo->ucCnt_misCnts  )  
	{
		goto  errLabel;
	}

	pQyMc->curUsrInfo.right.bAdmin  =  TRUE;
	myTChar2Str(  m_name,  pQyMc->curUsrInfo.name,  sizeof(  pQyMc->curUsrInfo.name  )  );
	//  _sntprintf(  pQyMc->appObjPrefix,  mycountof(  pQyMc->appObjPrefix  ),  _T(  "qm%d"  ),  pDlg->m_var.iSeqNoSelected  );
	lstrcpyn(  pQyMc->appParams.appObjPrefix,  appObjPrefix,  mycountof(  pQyMc->appParams.appObjPrefix  )  );
	pQyMc->appParams.iSeqNoSelected_appObjPrefix  =  0;//m_var.iSeqNoSelected;		//  2017/01/01

	//  2019/04/08
	int				iBST_UNCHECKED  =  0;
	HWND			hCtrl;
	HKEY			hKeyRoot0				=	HKEY_CURRENT_USER;
	TCHAR			tQnmSchedulerBuf[256]	=	_T(  ""  );	

#if  0
	hCtrl  =  GetDlgItem(  hDlg,  m_var.guiData.iIDC_CHECK_savePasswd  );
	iBST_UNCHECKED  =  SendMessage(  hCtrl,  BM_GETSTATE, 0,  0  );
	m_var.cntCfg[m_var.iSeqNoSelected].ucbNoSavePasswd  =  iBST_UNCHECKED  ==  BST_UNCHECKED;

	//
	if  (  !m_var.iSeqNoSelected  )  	 
		_sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  )  );
	else 
		_sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s\\%d"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  m_var.iSeqNoSelected  );

	if  (  !m_var.cntCfg[m_var.iSeqNoSelected].ucbNoSavePasswd  )  {
		qySetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_usr ),  m_name  );
		qySetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_passwd  ),  m_passwd  );
	}
#endif


	//
#if  0
	unsigned char  ucbNoAutoLogon;
	hCtrl  =  GetDlgItem(  hDlg,  m_var.guiData.iIDC_CHECK_autoLogon  );
	iBST_UNCHECKED  =  SendMessage(  hCtrl,  BM_GETSTATE,  0,  0  );
	ucbNoAutoLogon  =  iBST_UNCHECKED  ==  BST_UNCHECKED;

	if  (  ucbNoAutoLogon  !=  m_var.cntCfg[m_var.iSeqNoSelected].ucbNoAutoLogon  )  {
		m_var.cntCfg[m_var.iSeqNoSelected].ucbNoAutoLogon  =  ucbNoAutoLogon;

		qySetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_ucbNoAutoLogon  ),  m_var.cntCfg[m_var.iSeqNoSelected].ucbNoAutoLogon  ?  _T(  "1"  ) :  _T(  "0"  )  );

	}

	bAutoRun(  m_var.cntCfg[m_var.iSeqNoSelected].ucbNoAutoLogon,  m_var.iSeqNoSelected,  m_var.cntCfg[m_var.iSeqNoSelected].usr,  m_var.cntCfg[m_var.iSeqNoSelected].passwd  );

	if  (  ucbNoAutoLogon  )  {
		HKEY  hkResult;
		if  (  RegOpenKey(  hKeyRoot0,  _T(  CONST_exeName_qyMessenger  ),  &hkResult  )  ==  ERROR_SUCCESS  )  {
			RegDeleteValue(  hkResult,  _T(  CONST_exeName_qyMessenger  )  );
			RegCloseKey(  hkResult  );
		}
	}
#endif


	iErr  =  0;

errLabel:

	if  (  !iErr  )  {
		//  EndDialog(  pDlg->m_hWnd,  IDOK  );
	}
	if  (  iErr  )  {
		//m_var.bLogonFailed  =  TRUE;
	}

	return  iErr;
}


//
bool  bExists_conf(int* piTaskId)
{
	bool  bRet = false;
	int  i;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	//
	if (!piTaskId)  return  false;

	//
	for (i = 0; i < pProcInfo->cfg.usMaxCnt_taskInfos; i++) {
		if (!qmcTaskInfo_bAlive(pProcInfo, i))  continue;
		QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, i);
		if (pTaskInfo->var.pTaskData->uiType == CONST_taskDataType_conf) {
			//
			*piTaskId = pTaskInfo->var.iTaskId;
			//
			break;
		}
	}
	if (i == pProcInfo->cfg.usMaxCnt_taskInfos)  goto  errLabel;

	bRet = true;
errLabel:
	return  bRet;
}


//
int mainWnd_procMsgInput_confReq(HWND  hMainWnd, void* pVar, MIS_MSG_INPUT* pMsgInput)
{
	int  iErr = -1;

	if (!pVar)  return  -1;
	QY_MC_mainWndVar& var = *(QY_MC_mainWndVar*)pVar;
	QY_MC* pQyMc = var.pQyMc;
	if (!pQyMc)  return  -1;
	MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return  -1;
	if (pProcInfo->m_iCtxType != CONST_ctxType_qmc)  return  -1;

	TCHAR  tBuf[128];

	//
	showInfo_open0(0, 0, _T("mainWnd_proc_confReq called"));

	//
	if (!pQyMc->appParams.bConfServer) {
		showInfo_open0(0, 0, _T("confReq denied, I am not a confServ"));
		goto  errLabel;
	}
	//
	if (pProcInfo->av.doConf.bStartToQuitApp) {
		showInfo_open0(0, 0, _T("confReq denied, bStartToQuitApp is true"));
		goto  errLabel;
	}

	//		
	if (
		//isUcFlgTalkData(pMsgInput->ucFlg) && 
		isUcFlgRouteTalkData(pMsgInput->ucFlg)) {
		showInfo_open0(0, 0, _T("confReq failed. confReq cant be received from messenger"));
		goto  errLabel;

	}

	//
	IM_CONTENTU* pContent = M_getMsgContent(pMsgInput->ucFlg, &pMsgInput->data);

	//
	if (pContent->uiType != CONST_imCommType_confReq) {
		goto  errLabel;
	}

	//
	if (1) {
		TCHAR  tBuf[128];
		//
		_sntprintf(tBuf, mycountof(tBuf), _T("mainWnd_proc_confReq: bitrate_dl %d, bitrate_ul %d"), pContent->confReq.policy.talkerPolicy.conf_bitrateInKbps_dl,  pContent->confReq.policy.talkerPolicy.conf_bitrateInKbps_ul);
		showInfo_open0(0, 0, tBuf);
		_sntprintf(tBuf, mycountof(tBuf), _T("mainWnd_proc_confReq: taskType %d, shareDevice_index %d, gpu_usIndex %d"), pContent->confReq.policy.talkerPolicy.uiTaskType, pContent->confReq.policy.talkerPolicy.shareDevice_grp_index, (int)pContent->confReq.policy.talkerPolicy.gpu_usIndex);
		showInfo_open0(0, 0, tBuf);
		//
		_sntprintf(tBuf, mycountof(tBuf), _T("mainWnd_proc_confReq: meetingId_hg %I64u, meetingType %d"), pContent->confReq.hgInfo.ui64MeetingId_hg,  pContent->confReq.hgInfo.iMeetingType_hg);
		showInfo_open0(0, 0, tBuf);
		_sntprintf(tBuf, mycountof(tBuf), _T("mainWnd_proc_confReq: meetingLevel %d, meetingDuration %dmin"), pContent->confReq.hgInfo.iMeetingLevel_hg, pContent->confReq.hgInfo.iMeetingDurationInMin);
		showInfo_open0(0, 0, tBuf);
		_sntprintf(tBuf, mycountof(tBuf), _T("mainWnd_proc_confReq: meetingStartTime %I64u, meetingCompere %s"), pContent->confReq.hgInfo.ui64_meetingStartTime, pContent->confReq.hgInfo.meetingCompere);
		showInfo_open0(0, 0, tBuf);
		_sntprintf(tBuf, mycountof(tBuf), _T("mainWnd_proc_confReq: bRecord %d, bShare %d, bFlow512k %d"), pContent->confReq.hgInfo.bRecord_conf, pContent->confReq.hgInfo.bShare_2ndStream,  pContent->confReq.hgInfo.bFlow512k);
		showInfo_open0(0, 0, tBuf);
		//



		//
		int  i;
		tBuf[0] = 0;
		_sntprintf(tBuf, mycountof(tBuf), _T("mainWnd_proc_confReq:"));
		for (i = 0; i < mycountof(pContent->confReq.hgInfo.shareMems); i++) {
			if (!pContent->confReq.hgInfo.shareMems[i].idInfo.ui64Id)  break;
			_sntprintf(tBuf, mycountof(tBuf), _T("%s [%d] %I64u,"), tBuf, i, pContent->confReq.hgInfo.shareMems[i].idInfo.ui64Id);
		}
		showInfo_open0(0, 0, tBuf);
		//
	}

	//		
	int  iTaskId = 0;
	if (bExists_conf(&iTaskId)) {
		
		//
		showInfo_open0(0, 0, _T("confReq: conf already exists"));

		//
		_sntprintf(tBuf, mycountof(tBuf), _T("confReq: grp %I64u, op %d"), pContent->confReq.idInfo_imGrp_related.ui64Id, (int)pContent->confReq.usOp);
		showInfo_open0(0, 0, tBuf);

		//
		int  index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, iTaskId);
		QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
		if (!pTaskInfo) {
			goto  errLabel;
		}

		if (pProcInfo->av.doConf.confReq.idInfo_imGrp_related.ui64Id != pContent->confReq.idInfo_imGrp_related.ui64Id) {
			_sntprintf(tBuf, mycountof(tBuf), _T("confReq: oldConf is %I64u, will be closed"), pProcInfo->av.doConf.confReq.idInfo_imGrp_related.ui64Id);
			showInfo_open0(0, 0, tBuf);

			//
			//PostMessage(pTaskInfo->var.hWnd_task, WM_CLOSE, 0, 0);
			mcu_startToQuitApp(_T("confReq: oldConf exists"));

			//
			goto  errLabel;
		}

		//
		if (pContent->confReq.usOp == CONST_imOp_send_cancel) {
			HWND  hTalk;
			if (findTalker(pQyMc, &pContent->confReq.idInfo_imGrp_related, &hTalk))  goto  errLabel;
				
			//
			dlgTalk_procTask1(hTalk, iTaskId, pContent->confReq.usOp, _T(""), NULL);
		}

		//
		iErr = 0;  goto  errLabel;
	}

	//		
	set_doConf(&pContent->confReq, _T("mainWnd_postComm"));

	//
	if (pQyMc->appParams.bConfServer) {
		//
		if (!pProcInfo->status.confServerStatus.bDone_createConsoleWall) {
			//
			if (GuiShare.pf_doPre_createConsoleWall)  GuiShare.pf_doPre_createConsoleWall(NULL, NULL, NULL);
			//
			dyn_createConsoleWall(pQyMc->pGBuf_d3d);

			//
			pProcInfo->status.confServerStatus.bDone_createConsoleWall = true;
		}

	}



	//		
	dyn_setCurQisWallCfg(0, pQyMc->pQisWallsCfg);

	//
	iErr = 0;
errLabel:

	return  iErr;
}

int  confStarter_sendToCancelTaskAv(HWND  hDlgTalk, DLG_TALK_var& m_var);

int dlgTalk_closeTaskAv_afterTaskClosed(HWND  hDlgTalk, DLG_TALK_var * pm_var)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	CCtxQmc* pProcInfo = (CCtxQmc *)pQyMc->get_pProcInfo();

	DLG_TALK_var& m_var = *pm_var;

	if (pQyMc->appParams.bMcu) {
		if (m_var.av.taskInfo.ucbStarter) {
			//
			clear_doConf(m_var.addr.idInfo, _T("dlgTalk_closeTaskAv"));
			//
			sendConfReq(0, hDlgTalk, m_var.addr.idInfo, CONST_imOp_send_cancel, 0, 0, 0,0);
			//
			confStarter_sendToCancelTaskAv(hDlgTalk, m_var);

			//  2019/03/17
#if  0
			showInfo_open0(0, NULL, _T("dlgTalk_closeTaskAv: startToQuitApp"));
			pProcInfo->av.doConf.bStartToQuitApp = true;
#endif
			//
			mcu_startToQuitApp(_T("dlgTalk_closeTaskAv"));

			//
			PostMessage(hDlgTalk, WM_CLOSE, 0, 0);
		}
	}

	return  0;

}

//
int mcu_startToQuitApp(  LPCTSTR  hint  )
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	TCHAR  tBuf[128];
	if (!hint)  hint = _T("");

	_sntprintf(tBuf, mycountof(tBuf), _T("mcu_startQuitApp: %s"), hint);
	showInfo_open0(0, 0, tBuf);

	//
	pProcInfo->av.doConf.bStartToQuitApp = true;

	//
	return  0;
}



