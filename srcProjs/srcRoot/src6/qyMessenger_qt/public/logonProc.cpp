


#include	"stdafx.h"

#include	<qstring.h>




#include "CQmcLogin.h"

#include	"qyCusResTemp.h"

#include "ctxQmc.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliHelpPublic.h"
#include	"ctxQmc_qt.h"


extern int  newstartQThreadToSaveIC(MC_VAR_common* pProcInfo);
extern int  newstartQThreadToCheckICFile(MC_VAR_common* pProcInfo);

//
extern  "C"  BOOL  bServConnected_mis(QY_ENV * pEnv, char* serverIp, unsigned  short  serverPort, void* pParam, int  serviceId, char* ver, QY_ENC_CTX * pCommEncCtx, __int64  i64StartTime_base,  SOCK_TIMEOUT * pTo);
int  doMisCntLogon(MIS_CNT* pMisCnt, MIS_CHANNEL* pChannel, HWND    hDlg, TCHAR* respHint, int  cntof_respHint);
BOOL  bAutoRun(BOOL  bNoAutoLogon, int iServerNo, TCHAR* pUsr, TCHAR* pPasswd);


//
BOOL  bAnotherInstanceExists(QY_MC* pQyMc, LPCTSTR  appObjPrefix);

//
int  dlgMcClientLogon_OnOK_qt(CQmcLogin* pDlg, char * m_server, LPTSTR  m_name, LPTSTR  m_passwd)
{
	int							iErr = -1;

	// TODO: Add your control notification handler code here
	//CDlgMcClientLogon* pDlg = (CDlgMcClientLogon*)CDlgMcClientLogon::FromHandle(hDlg);
	DLG_mcClientLogon_var& m_var = pDlg->m_var;
	TCHAR						tBuf[128];

	//
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return  -1;
	if (pProcInfo->m_iCtxType != CONST_ctxType_qmc)  return  -1;

	//
	char						buf[1024] = "";
	unsigned  int				len;

	//
	TCHAR						appObjPrefix[16 + 1] = _T("");			//  2010/03/10

#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("dlgMcClientLogon_OnOK called"));
	showInfo_open0(0, mynull, _T("dlgMcClientLogon_OnOK called"));
#endif

	//  2014/02/09
	if (m_var.iSeqNoSelected < 0 || m_var.iSeqNoSelected >= mycountof(m_var.cntCfg))  return  -1;

	//
	_sntprintf(appObjPrefix, mycountof(appObjPrefix), _T("%s%d"), CONST_qmCmdLine_sym_appObjPrefix, m_var.iSeqNoSelected);
#ifndef  __WINCE__
	if (bAnotherInstanceExists(pQyMc, appObjPrefix))  goto  errLabel;
#endif

	//
	TCHAR						tPrefix[32]; tPrefix[0] = 0;// = _T("");
	_sntprintf(tPrefix, mycountof(tPrefix), _T("%d: "), m_var.nTries_triggerIDOK);

	if (!bSupported_devAuth()) {

		if (!m_name || !m_name[0])  goto  errLabel;
		if (!m_passwd || !m_passwd[0])  goto  errLabel;

		tTrim(m_name);
		tTrim(m_passwd);
		//
		if (!m_name[0]) {
			//SetFocus(GetDlgItem(hDlg, m_var.guiData.iIDC_NAME));
			goto  errLabel;
		}
		if (!m_passwd[0]) {
			//SetFocus(GetDlgItem(hDlg, m_var.guiData.iIDC_PASSWD));
			goto  errLabel;
		}

		//
		lstrcpyn(pProcInfo->authInfo.messengerName, m_name, mycountof(pProcInfo->authInfo.messengerName));
		myTChar2Utf8(m_passwd, buf, mycountof(buf));
		len = mycountof(pProcInfo->authInfo.messengerPasswd);
		bQyGetStrMd5_x(buf, pProcInfo->authInfo.messengerPasswd, &len);
	}

	//  CWaitCursor		cur;

	//
	_sntprintf(m_var.cntCfg[m_var.iSeqNoSelected].usr, mycountof(m_var.cntCfg[m_var.iSeqNoSelected].usr), m_name);
	_sntprintf(m_var.cntCfg[m_var.iSeqNoSelected].passwd, mycountof(m_var.cntCfg[m_var.iSeqNoSelected].passwd), m_passwd);

 	memcpy(&pQyMc->cfg.dynCfg.cnt, &m_var.cntCfg[m_var.iSeqNoSelected], sizeof(QNM_CNT_CFG));

	//  2010/01/09
	{
		int  index = 0;
		MIS_CNT* pMisCnt = getMisCntByIndex(0, pProcInfo, index);
		if (!pMisCnt)  goto  errLabel;
		memcpy(&pMisCnt->cfg.dynCfg, &pQyMc->cfg.dynCfg, sizeof(pMisCnt->cfg.dynCfg));
		memset(&pMisCnt->server, 0, sizeof(pMisCnt->server));
	}
	//
	int								i;
	QY_LOGICAL_SERVER				tmpCnt;

	//for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
	for (i = 0; i < pProcInfo->ucCnt_misCnts; i++)
	{
		MIS_CNT* pMisCnt = getMisCntByIndex(0, pProcInfo, i);//&pProcInfo->misCnts[i];
		if (!pMisCnt)  continue;
		MIS_CHANNEL* pChannel = getChannelByType(pMisCnt, CONST_channelType_talking);
		if (!pChannel)  continue;

		if (pChannel->bSessionOpen) {
			qnmCloseSession_msg(mynull,&pChannel->session, &pChannel->sock, &pQyMc->cfg.to,_T("l128"));
			pChannel->bSessionOpen = FALSE;
		}

		if (!pChannel->bSessionOpen) {

			pMisCnt->pAuthInfo = &pProcInfo->authInfo;
			clearQySock(&pChannel->sock);

			//  
			{
				if (pMisCnt->cfg.dynCfg.cnt.usCntPort) {
					_sntprintf(tBuf, mycountof(tBuf), getResStr(0, &pQyMc->cusRes, CONST_resId_searchingServer));
					_sntprintf(tBuf, mycountof(tBuf), _T("%s: %s, %s, %s; Port: %d"), tBuf,
						CQyString(pMisCnt->cfg.dynCfg.cnt.cntIp),
						CQyString(pMisCnt->cfg.dynCfg.cnt.cntAddrs[0]),
						CQyString(pMisCnt->cfg.dynCfg.cnt.cntAddrs[1]),
						pMisCnt->cfg.dynCfg.cnt.usCntPort);
					//m_var.guiData.pf_SetDlgItemText(pDlg->m_hWnd, m_var.guiData.iIDC_STATIC_hint, CQyString(tPrefix) + tBuf);
					if (getCorrectCnt(&pQyMc->env, &pMisCnt->cfg.dynCfg, bServConnected_mis, pMisCnt, pQyMc->iServiceId, qnmVerStr(pQyMc->iServiceId), &pMisCnt->commEncCtx.common, pQyMc->i64StartTime_base,  &pQyMc->cfg.to, &tmpCnt)) {
						_sntprintf(tBuf, mycountof(tBuf), getResStr(0, &pQyMc->cusRes, CONST_resId_cannotFindServer));
						//m_var.guiData.pf_SetDlgItemText(pDlg->m_hWnd, m_var.guiData.iIDC_STATIC_hint, CQyString(tPrefix) + tBuf);
						qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("getCorrectCnt failed"));
						continue;
					}
					else  if (memcmp(&pMisCnt->server, &tmpCnt, sizeof(tmpCnt))) {
						memcpy(&pMisCnt->server, &tmpCnt, sizeof(pMisCnt->server));
					}
				}
			}
			if (!pMisCnt->commEncCtx.ucbPublicKeyDownloaded || !pMisCnt->commEncCtx.ucbPublicKeyVerified)  continue;

			_sntprintf(tBuf, mycountof(tBuf), _T("%s ok"), CQyString(pMisCnt->server.ip));
			//m_var.guiData.pf_SetDlgItemText(pDlg->m_hWnd, m_var.guiData.iIDC_STATIC_hint, tBuf);


#ifdef  __DEBUG__
			showInfo_open0(0, mynull, _T("before doMisCntLogon"));
#endif

			//
			HWND  hWnd = (HWND)pDlg->window()->winId();


			m_var.respHint[0] = 0;
			if (!doMisCntLogon(pMisCnt, pChannel, hWnd, m_var.respHint, mycountof(m_var.respHint)))  break;

		}

		_sntprintf(tBuf, mycountof(tBuf), _T("%s %s: %s"), getResStr(0, &pQyMc->cusRes, CONST_resId_failedToLogon), CQyString(pMisCnt->server.ip), m_var.respHint);
		//m_var.guiData.pf_SetDlgItemText(pDlg->m_hWnd, m_var.guiData.iIDC_STATIC_hint, CQyString(tPrefix) + tBuf);

		continue;
	}

	//if  (  i  ==  mycountof(  pProcInfo->misCnts  )  )  
	if (i == pProcInfo->ucCnt_misCnts)
	{
		goto  errLabel;
	}

	pQyMc->curUsrInfo.right.bAdmin = TRUE;
	myTChar2Str(m_name, pQyMc->curUsrInfo.name, sizeof(pQyMc->curUsrInfo.name));
	//  _sntprintf(  pQyMc->appObjPrefix,  mycountof(  pQyMc->appObjPrefix  ),  _T(  "qm%d"  ),  pDlg->m_var.iSeqNoSelected  );
	lstrcpyn(pQyMc->appParams.appObjPrefix, appObjPrefix, mycountof(pQyMc->appParams.appObjPrefix));
	pQyMc->appParams.iSeqNoSelected_appObjPrefix = m_var.iSeqNoSelected;		//  2017/01/01

	//  2019/04/08
	//ucbNoSavePasswd;
	//ucbNoAutoLogon;

	//pDlg->ui->
	//int				iBST_UNCHECKED = 0;
	//HWND			hCtrl;
	HKEY			hKeyRoot0; hKeyRoot0 = HKEY_CURRENT_USER;
	TCHAR			tQnmSchedulerBuf[256]; tQnmSchedulerBuf[0] = 0;// = _T("");

#if  0
	hCtrl = GetDlgItem(hDlg, m_var.guiData.iIDC_CHECK_savePasswd);
	iBST_UNCHECKED = SendMessage(hCtrl, BM_GETSTATE, 0, 0);
#endif
	m_var.cntCfg[m_var.iSeqNoSelected].ucbSavePasswd = m_var.ucbSavePasswd;// iBST_UNCHECKED == BST_UNCHECKED;

	//
	if (!m_var.iSeqNoSelected)
		_sntprintf(tQnmSchedulerBuf, mycountof(tQnmSchedulerBuf), _T("%s"), CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler));
	else
		_sntprintf(tQnmSchedulerBuf, mycountof(tQnmSchedulerBuf), _T("%s\\%d"), CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), m_var.iSeqNoSelected);

	//
	qySetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_ucbSavePasswd), m_var.cntCfg[m_var.iSeqNoSelected].ucbSavePasswd ? _T("1") : _T("0"));

	//
	if (m_var.cntCfg[m_var.iSeqNoSelected].ucbSavePasswd) {
		qySetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_usr), m_name);
		qySetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_passwd), m_passwd);
	}
	else {
		qyDelRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_usr));
		qyDelRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_passwd));
	}



	//
	unsigned char  ucbAutoLogon;
#if  0
	hCtrl = GetDlgItem(hDlg, m_var.guiData.iIDC_CHECK_autoLogon);
	iBST_UNCHECKED = SendMessage(hCtrl, BM_GETSTATE, 0, 0);
#endif
	ucbAutoLogon = m_var.ucbAutoLogon;// iBST_UNCHECKED == BST_UNCHECKED;

	if (ucbAutoLogon != m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon) {
		m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon = ucbAutoLogon;
	}

	//		
	qySetRegCfgT(hKeyRoot0, tQnmSchedulerBuf, _T(CONST_regValName_ucbAutoLogon), m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon ? _T("1") : _T("0"));

	
	//
	bAutoRun(m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon, m_var.iSeqNoSelected, m_var.cntCfg[m_var.iSeqNoSelected].usr, m_var.cntCfg[m_var.iSeqNoSelected].passwd);

#if  0
	if (ucbNoAutoLogon) {
		HKEY  hkResult;
		if (RegOpenKey(hKeyRoot0, _T(CONST_exeName_qyMessenger), &hkResult) == ERROR_SUCCESS) {
			RegDeleteValue(hkResult, _T(CONST_exeName_qyMessenger));
			RegCloseKey(hkResult);
		}
	}
#endif


	iErr = 0;

errLabel:

	if (!iErr) {
		//  EndDialog(  pDlg->m_hWnd,  IDOK  );
	}
	if (iErr) {
		m_var.bLogonFailed = TRUE;
	}

	return  iErr;
}


//
BOOL CALLBACK myEnumWindowsProc_singleInstance(HWND hwnd, LPARAM lParam);



//
 //int doMcClientLogonOK(CQmcLogin * hDlg, LPTSTR m_name, LPTSTR m_passwd)
 int doMcClientLogonOK(void* pQmcLogin, char * m_server, LPTSTR m_name, LPTSTR m_passwd)
{
	int iErr = -1;
	CCtxQyMc  * pQyMc = QY_GET_GBUF();
	CCtxQmc_qt * pProcInfo = (CCtxQmc_qt  *  )pQyMc->get_pProcInfo();

	//
	CQmcLogin* pDlg = (CQmcLogin*)pQmcLogin;

	//
	QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  return -1;// goto  errLabel;
	QM_dbFuncs& g_dbFuncs = *pDbFuncs;


	//
	if (pQyMc->bLogon) return -1; 
	//
	if (dlgMcClientLogon_OnOK_qt(pDlg, m_server,  m_name, m_passwd) != 0) return -1;

	//


	//
	pQyMc->bLogon = true;
	pQyMc->dwTickCnt_logon = myGetTickCount(NULL);


	//
	if (!pQyMc->appParams.ucbNotNeedLocked) {	//  Release 2007/05/29
	//  
		if (pQyMc->cfg.singleInstanceStr[0]) {
			CQyString lckCStr;

#ifndef  __WINCE__
			lckCStr = CQyString(pQyMc->appParams.appObjPrefix) + CQyString(pQyMc->cfg.singleInstanceStr);
#else
			lckCStr = CQyString(CONST_mutexPrefix_mcClientLogon) + pQyMc->cfg.singleInstanceStr;
#endif
			pQyMc->gui.hMutex_singleInstance = CreateMutex(NULL, FALSE, lckCStr);
			if (!pQyMc->gui.hMutex_singleInstance) {
				traceLog((TCHAR*)_T("singleInstance failed, null."));
				goto  errLabel;
			}
			if (GetLastError() == ERROR_ALREADY_EXISTS) {
				traceLog((TCHAR*)_T("singleInstance failed, already exists."));

				COMMON_PARAM	commonParam;
				HWND	hPrevWnd = NULL;

				MACRO_makeCommonParam3(0, (void*)lckCStr.GetBuffer(), &hPrevWnd, commonParam);
				EnumWindows(myEnumWindowsProc_singleInstance, (LPARAM)&commonParam);

				if (IsWindow(hPrevWnd)) {
					//  if  (  IsIconic(  hPrevWnd  )  )  ShowWindow(  hPrevWnd,  SW_RESTORE  );
					ShowWindow(hPrevWnd, SW_SHOWNORMAL);

#if !defined(  __WINCE__  )  ||  defined(  __TEST__  )
					SetForegroundWindow(hPrevWnd);
					SetForegroundWindow(GetLastActivePopup(hPrevWnd));
#else
					SetForegroundWindow((HWND)(((ULONG)hPrevWnd) | 0x01));
#endif

				}

				goto  errLabel;
			}

			//
			if (!IsWindow(pQyMc->gui.hMainWnd))  goto  errLabel;
			if (!SetProp(pQyMc->gui.hMainWnd, lckCStr, (HANDLE)1))  goto  errLabel;
		}
		//  ¼ì²é½áÊø	 	 
	}





	//
	pQyMc->cfg.db.iDbType = CONST_dbType_myDb;



	//
	//
	if (0 != getProcedObjsCfg(pQyMc)) goto errLabel;

	if (initQyMcDb(0, 0, &getProcedObjDbs(pQyMc)[pQyMc->iDsnIndex_mainSys])) {
#ifdef  __DEBUG__
		traceLogA((char*)"initQyMc: initQyMcDb failed.");
#endif
		goto  errLabel;
	}
	pQyMc->gui.pDb = getProcedObjDbs(pQyMc)[pQyMc->iDsnIndex_mainSys].pDb;
	//  2013/01/30
	pQyMc->setQmDbFuncs(pQyMc->cfg.db.iDbType, &g_dbFuncs);

	//
	pProcInfo->m_var.pDBManager = pProcInfo->DBManager_new();
	if (pProcInfo->m_var.pDBManager == mynull)goto  errLabel;
	if (pProcInfo->initDBManager(pProcInfo->m_var.pDBManager))  goto  errLabel;


	//
	if (!loadCusModules(pQyMc)) {
		pQyMc->bCusModulesLoaded = TRUE;
		//  2007/12/31
		if (initCusModules(pQyMc)) {
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("initCusModules failed."));
			goto  errLabel;
		}
		if (startCusModules(pQyMc)) {
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("startCusModules failed."));
			goto  errLabel;
		}
		//
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("loadCusModules ok."));
	}


	//
	if (pQyMc->iAppType == CONST_qyAppType_client)
	{
		//  要在登陆后立即运行此函数. 2011/10/22
		if (initPolicyAvParams() != 0) goto errLabel;
	}

	if (pProcInfo->m_iCtxType != CONST_ctxType_qmc) goto errLabel;

	POLICY_isClient policy;
	if (0 == getPolicyIsClient(pProcInfo, &policy))
	{
		pProcInfo->cfg.policy = policy;
	}


	//
	showInfo_open0(0, mynull, _T("doMcClientLogon: before start threadProcs"));

	int  i;
	DWORD  dwThreadDaemonId;
	for (i = 0; i < mycountof(pQyMc->hDaemonThreads); i++) {
		if (pQyMc->threadProcs[i]) {
			pQyMc->hDaemonThreads[i] = CreateThread(NULL, 0, pQyMc->threadProcs[i], pQyMc, 0, &dwThreadDaemonId);
			if (pQyMc->hDaemonThreads[i] == NULL) goto errLabel;
		}
	}


	//
	showInfo_open0(0, mynull, _T("doMcClientLogon: after start threadProcs"));

	//bGetIpcProcInitCfg(pQyMc->cfg.ipcProcInitFile, &pProcInfo->cfg.ipcProcInitCfg);

	newstartQThreadToSaveIC(pProcInfo);
	newstartQThreadToCheckICFile(pProcInfo);

	//
	iErr = 0;

errLabel:

	if (0 != iErr)
	{
		qmcLogoff();
	}



	return iErr;
}



#if 0
void iiqyMcLogoff()
{
	CCtxQyMc * pQyMc = QY_GET_GBUF();
	CCtxQmc *pProcInfo = (CCtxQmc  *  )pQyMc->get_pProcInfo();

	//
	showInfo_open0(0, null, _T(  "qyMcLogoff enters")  );

	//
	pQyMc->bLogon = false;

	//
	exitAllDaemonThreads(pQyMc);

	//
	pProcInfo->processQ_media.emptyQ();

	//
	//
	chkPlayers(pProcInfo);


	//
	exitQyMcDb(null, null, &getProcedObjDbs(pQyMc)[pQyMc->iDsnIndex_mainSys]);

	//
	unloadCusModules(pQyMc);


	//
	CCtxQyMc* pQM = pQyMc;
	if (pQM->gui.hMutex_singleInstance) {
		CloseHandle(pQM->gui.hMutex_singleInstance);
		pQM->gui.hMutex_singleInstance = NULL;
	}


	//
	showInfo_open0(0, null, _T(  "qyMcLogoff leaves")  );


	return;
}
#endif


