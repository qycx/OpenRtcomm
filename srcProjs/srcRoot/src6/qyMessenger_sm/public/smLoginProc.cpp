


#include	"stdafx.h"

//#include    <qdir.h>

#include	"myCmdParams_open.h"
#include	"tmpRegFunc_open.h"
#include	"imCommType_defs.h"
#include	"qyMcMainCommon.h"
#include	"qnmCommProc.h"
#include <DlgMcClientLogon.h>
#include	"smLoginProc.h"
#include	"ctxQmc.h"
//#include <smProc.h>
//#include	"ctxQmc_sm.h"
#include	"qyCusResTemp.h"
#include <qmcCommFunc_isCli.h>

#include <string>

//
void login_do_onLoginOkclicked(HWND  hDlg, DLG_mcClientLogon_var& m_var, SmLoginVar& m_smLoginVar, bool b0, bool* pbOk_doLogin);
BOOL  bAnotherInstanceExists(QY_MC* pQyMc, LPCTSTR  appObjPrefix);
BOOL  bAutoRun(BOOL  ucbAutoLogon, int iServerNo, TCHAR* pUsr, TCHAR* pPasswd);
BOOL CALLBACK myEnumWindowsProc_singleInstance(HWND hwnd, LPARAM lParam);
int sm_doMcClientLogonOK(QY_MC  *  pQyMc,  HWND  hDlgQmcLogin, DLG_mcClientLogon_var& m_var, char* m_server, LPTSTR m_name, LPTSTR m_passwd, char* ca_sendData, int ca_sendDataLen);

//
int qmcLogStatus(LPCTSTR  tWhere, int  logType, LPCTSTR  logDesc);


//
bool bGetSmTerminalInitCfg(TCHAR* cfgFileName, Sm_terminal_initCfg* pCfg)
{
	int  iErr = -1;
	TCHAR  tBuf[256];
	char  buf[256];

	//
	if (!pCfg)  return  -1;

	//
	memset(pCfg, 0, sizeof(pCfg[0]));


	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_sm_terminalIp), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	myTChar2Utf8(tBuf, buf, mycountof(buf));
	safeStrnCpy(buf, pCfg->terminal_ip, mycountof(pCfg->terminal_ip));
	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_sm_terminalMask), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	myTChar2Utf8(tBuf, buf, mycountof(buf));
	safeStrnCpy(buf, pCfg->terminal_mask, mycountof(pCfg->terminal_mask));
	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_sm_terminalGateway), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	myTChar2Utf8(tBuf, buf, mycountof(buf));
	safeStrnCpy(buf, pCfg->terminal_gateway, mycountof(pCfg->terminal_gateway));
	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_sm_terminalDns), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	myTChar2Utf8(tBuf, buf, mycountof(buf));
	safeStrnCpy(buf, pCfg->terminal_dns, mycountof(pCfg->terminal_dns));
	
	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_sm_terminalMcu), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	myTChar2Utf8(tBuf, buf, mycountof(buf));
	safeStrnCpy(buf, pCfg->terminal_mcu, mycountof(pCfg->terminal_mcu));
	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_sm_terminalMcu2), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	myTChar2Utf8(tBuf, buf, mycountof(buf));
	safeStrnCpy(buf, pCfg->terminal_mcu2, mycountof(pCfg->terminal_mcu2));


	
	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_sm_terminalSqm), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	myTChar2Utf8(tBuf, buf, mycountof(buf));
	safeStrnCpy(buf, pCfg->terminal_sqm, mycountof(pCfg->terminal_sqm));

	/*
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_sm_terminalType), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	pCfg->terminal_type = _ttol(tBuf);
	*/


	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_sm_devPrefix), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	safeTcsnCpy(  tBuf,  pCfg->devPrefix, mycountof(pCfg->devPrefix));

	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_fake_usrName), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	safeTcsnCpy(tBuf, pCfg->fake_usrName, mycountof(pCfg->fake_usrName));

	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_fake_passwd), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	myTChar2Utf8(tBuf, buf, mycountof(buf));
	safeStrnCpy(buf, pCfg->fake_passwd, mycountof(pCfg->fake_passwd));

	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_authType), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	pCfg->authType = _ttol(tBuf);


	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_fake_devLoginName), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	safeTcsnCpy(tBuf, pCfg->fake_devLoginName, mycountof(pCfg->fake_devLoginName));



	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_fake_devLoginPasswd), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	myTChar2Utf8(tBuf, buf, mycountof(buf));
	safeStrnCpy(buf, pCfg->fake_devLoginPasswd, mycountof(pCfg->fake_devLoginPasswd));

	//
	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_fake_talkerDesc), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	safeTcsnCpy(tBuf, pCfg->fake_talkerDesc, mycountof(pCfg->fake_talkerDesc));


	



	//
	iErr = 0;
	return  iErr;
}


//
int saveSmTerminalInitCfg(Sm_terminal_initCfg* pCfg, TCHAR* cfgFileName)
{
	int  iErr = -1;
	TCHAR  tBuf[256];
	FILE* fp = _tfopen(cfgFileName, _T("w,ccs=UNICODE"));
	if (!fp) {
		qyDisplayLastError((char*)"");
		goto  errLabel;
	}

	//
	_ftprintf(fp, _T(  "%S   %S\n"  ), CONST_cfgName_sm_terminalIp, pCfg->terminal_ip);
	_ftprintf(fp, _T( "%S   %S\n" ), CONST_cfgName_sm_terminalMask, pCfg->terminal_mask);
	_ftprintf(fp, _T( "%S   %S\n" ), CONST_cfgName_sm_terminalGateway, pCfg->terminal_gateway);
	//
	_ftprintf(fp, _T( "%S   %S\n" ), CONST_cfgName_sm_terminalDns, pCfg->terminal_dns);
	//
	_ftprintf(fp, _T( "%S   %S\n" ), CONST_cfgName_sm_terminalMcu, pCfg->terminal_mcu);
	_ftprintf(fp, _T( "%S   %S\n" ), CONST_cfgName_sm_terminalMcu2, pCfg->terminal_mcu2);

	//
	_ftprintf(fp, _T( "%S   %S\n" ), CONST_cfgName_sm_terminalSqm, pCfg->terminal_sqm);

	//_ftprintf(fp, _T("%S   %d\n"), CONST_cfgName_sm_terminalType, (int)pCfg->terminal_type);

	//
	_ftprintf(fp, _T( "%S   %d\n" ), CONST_cfgName_authType, (int)pCfg->authType);
	_ftprintf(fp, _T( "%S   %s\n" ), CONST_cfgName_fake_devLoginName, pCfg->fake_devLoginName);
	_ftprintf(fp, _T( "%S   %S\n" ), CONST_cfgName_fake_devLoginPasswd, pCfg->fake_devLoginPasswd);
	_ftprintf(fp, _T( "%S   %s\n" ), CONST_cfgName_fake_talkerDesc, pCfg->fake_talkerDesc);




	//setCfgV

	iErr = 0;
errLabel:

	if (fp) {
		fclose(fp);
	}

	return  iErr;
}



//
int login_getCertId(char* certId, int  cntof_certId)
{
	if (!certId)  return  -1;

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	//
	myTChar2Utf8(pProcInfo->authInfo.ca_usrName, certId, cntof_certId);

	//
	return  0;
}


//
void login_do_onLoginOkclicked(HWND  hDlg, DLG_mcClientLogon_var& m_var, SmLoginVar& m_smLoginVar, bool b0, bool* pbOk_doLogin)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	//
	showInfo_open0(0, 0, _T("qmcLogin: onLoginOkclicked called"));

	//
	int curIndex = 0; // ui->editServer->currentIndex();
	//
	//TCHAR    serviceNameLogin[128];		serviceNameLogin[0] = 0; // ui->editServer->currentText();
	TCHAR    UserName[128];				UserName[0] = 0; // ui->editUserAccount->text();
	TCHAR    Password[128];				Password[0] = 0;  //ui->editPassword->text();



	int i = 1;
	//
	char servIp[128];
	int  port;
	//myTChar2Utf8(QStringToTCHAR(ServerIp), servIp, mycountof(servIp));

	if (curIndex < 0 || curIndex >= CONST_maxOfVideoConferencingServers)  return;
	int  tmpIndex = m_smLoginVar.m_tmpCntDisplays.mems[curIndex].index;
	m_var.iSeqNoSelected = tmpIndex;
	//
	if (pProcInfo->m_bUseKeyToLogin_forQmcGui) {
		m_var.iSeqNoSelected = pQyMc->appParams.iSeqNoSelected_appObjPrefix;
	}
	//
	safeStrnCpy(m_var.cntCfgs.mems[tmpIndex].cntAddr, servIp, mycountof(servIp));
	port = m_var.cntCfgs.mems[tmpIndex].port;
	//
#ifdef  __DEBUG__
	//safeStrnCpy((char*)"bbs.qycx.com", servIp, mycountof(servIp));
#endif

	//
	//safeStrnCpy(servIp, m_var.cntCfg[m_var.iSeqNoSelected].cntIp, mycountof(m_var.cntCfg[m_var.iSeqNoSelected].cntIp));
	safeStrnCpy(servIp, m_var.cntCfg[m_var.iSeqNoSelected].cntAddrs[0], mycountof(m_var.cntCfg[m_var.iSeqNoSelected].cntAddrs[0]));
	m_var.cntCfg[m_var.iSeqNoSelected].usCntPort = port;

	//
	Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
	if (!pCtxSm)  return;
	Var_ca_dev_qmc* pVc = &pCtxSm->ca_dev;
	
	//
	if (pProcInfo->getAuthType() == CONST_authType_logon) {
		safeTcsnCpy(pCtxSm->smTerminalInitCfg.fake_devLoginName, UserName, mycountof(UserName));
		myUtf82TChar(pCtxSm->smTerminalInitCfg.fake_devLoginPasswd, Password, mycountof(Password));
	}	
	
	//
	//QString serverTip = u8"准备连接" + QString::fromUtf8(servIp) + " :" + QString::number(port);
	//safeTcsnCpy((TCHAR*)serverTip.utf16(), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
	_sntprintf(pVc->tStatusBuf, mycountof(pVc->tStatusBuf), _T("准备连接%S:%d"), servIp, port);
		
	//
	if (0 != sm_doMcClientLogonOK(pQyMc,  hDlg, m_var, servIp, (UserName), (Password), pVc->cli.ca_sendData, pVc->cli.ca_sendDataLen)) {
		//
		Ctx_sm* pCtxSm = pProcInfo->getCtxSm();

		_sntprintf(pVc->tStatusBuf, mycountof(pVc->tStatusBuf), _T("登录失败, 可能是用户名或密码错误 IP : %S:%d"), pCtxSm->smTerminalInitCfg.terminal_mcu, port);

		// 
		return;
	}

	//
	if (0 != pProcInfo->do_afterLogonOk()) {
		//
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("do_afterLogonOk failed"));
#endif
	}

	//
	if (pbOk_doLogin) *pbOk_doLogin = true;

	//
	//this->accept();

	//
	return;
}


//
//
extern  "C"  int  waitForProcess(HANDLE * ph, DWORD  dwMilliseconds, int *piExitCode )
{
	DWORD	dwRet = 0;

	if (!ph)  return  -1;

	if (*ph) {

		dwRet = WaitForSingleObject(*ph, dwMilliseconds);
		if (dwRet != WAIT_TIMEOUT && dwRet != WAIT_FAILED) {

			//
			int  exitCode = 0;
	
			if (GetExitCodeProcess(*ph, (LPDWORD)&exitCode)) {
				int  ii = 0;
				if (piExitCode) {
					*piExitCode = exitCode;
				}
			}

			//
			CloseHandle(*ph);  *ph = NULL;

		}
	}

	return  0;

}




//
DWORD  tmpThreadProc_dev_ca_toGet_cli_sendData(LPVOID pParam)
{
#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("tmpThreadProc_dev_ca_toGet_cliSendData enters"));
#endif

	//
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
	if (!pCtxSm)  return  -1;
	Var_ca_dev_qmc* pVc = &pCtxSm->ca_dev;
	TCHAR	tBuf[128];

	//
	pVc->toolCa.tn_process_ca = getuiNextTranNo(nullptr, 0, &pCtxSm->tn0_ca);

	//
	bool  bSys = false;
	bool  bDev = true;
	HKEY  hKeyRoot0 = HKEY_CURRENT_USER;

	//
	TCHAR  cfgName_caRandom[128];
	_sntprintf(cfgName_caRandom, mycountof(cfgName_caRandom), _T("%s%d"), _T(CONST_regValName_caRandom_prefix), pVc->toolCa.tn_process_ca);
	char* caRandom = (char*)(pMisCnt->commEncCtx.ucbCaRandomOk ? pMisCnt->commEncCtx.caRandom : "");
	tmpSetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_caRandom, REG_BINARY, caRandom, strlen(caRandom));

	//
	TCHAR  cfgName[128];
	_sntprintf(cfgName, mycountof(cfgName), _T("%s%d"), _T(CONST_regValName_ca_sendData_prefix), pVc->toolCa.tn_process_ca);
	qyDelRegCfgT(hKeyRoot0, _T(CONST_rootKey_ca), cfgName);




	int caToolType = CONST_caToolType_bjca;
	TCHAR* who = (TCHAR*)_T("bjca.cli.sendData");
	char* caServIp = pCtxSm->caGwIp;
	int caServPort = pCtxSm->caGwPort;
	//
	switch (pProcInfo->getAuthType()) {
	case  CONST_authType_jdzy:
		//
		caToolType = CONST_caToolType_jdzyCli;
		who = (TCHAR*)_T("jdzy.ca");
		//
		break;
	default:
		break;
	}
	//
	pVc->nTimes_toReadKey++;
	//
	TCHAR* devPrefix = pCtxSm->smTerminalInitCfg.devPrefix;
	bool  bFullCmp = pProcInfo->m_bUseKeyToLogin_forQmcGui;
	//
	if (createTool_ca(pQyMc->cfg.installDir, caToolType, who, CONST_caCmd_login_sendData, bSys, devPrefix,  bDev, bFullCmp,  caServIp, caServPort, nullptr, pQyMc->cfg.qmcLogFile, &pVc->toolCa)) {
		//
		_sntprintf(pVc->tStatusBuf, mycountof(pVc->tStatusBuf), _T("第%d次启动设备key失败"), pVc->nTimes_toReadKey);
		//
		goto  errLabel;
	}

	//
	_sntprintf(pVc->tStatusBuf, mycountof(pVc->tStatusBuf), _T("第%d次读取设备key..."), pVc->nTimes_toReadKey);

	//
#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("createTool_ca ok"));
#endif

	//
	int  i;
	int maxSteps; maxSteps = 10;// 1000;
	for (i = 0; i < maxSteps; i++)
	{
		if (pVc->toolCa.bNeedQuit)  goto  errLabel;

		//
		int exitCode = 0;

		//waitForObject(&pVc->toolCa.hProcess_ca, 1000);
		waitForProcess(&pVc->toolCa.hProcess_ca, 1000, &exitCode);
		if (!pVc->toolCa.hProcess_ca) {
#ifdef  __DEBUG__
			traceLog((TCHAR*)_T("tool_ca waited"));
#endif
			//
			unsigned  int  uiType = 0;
			char  buf[4096];
			unsigned  int bufLen = 0;
			bufLen = sizeof(buf);
			if (tmpGetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName, &uiType, buf, &bufLen)) {
				_sntprintf(pVc->tStatusBuf, mycountof(pVc->tStatusBuf), _T("读取设备key失败"));
				if (exitCode == CONST_caRet_getRandomErr) {
					_sntprintf(pVc->tStatusBuf, mycountof(pVc->tStatusBuf), _T("%s(getRandomErr)"), pVc->tStatusBuf);
				}
				//
				showInfo_open0(0, 0, pVc->tStatusBuf);
				//
				goto  errLabel;
			}
			buf[bufLen] = 0;

			//
			qyDelRegCfgT(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_caRandom);
			//
			qyDelRegCfgT(hKeyRoot0, _T(CONST_rootKey_ca), cfgName);

			//
			if (bufLen > mycountof(pVc->cli.ca_sendData))  goto  errLabel;
			memcpy(pVc->cli.ca_sendData, buf, bufLen);
			pVc->cli.ca_sendDataLen = bufLen;
			//
			pProcInfo->authInfo.ca_usrName[0] = 0;
			//
			_sntprintf(tBuf, mycountof(tBuf), _T("threadProc_ca: get ca_sendData %dB [%S]"), bufLen, buf);
			showInfo_open0(0, 0, tBuf);
			//
			pVc->flgs.loginToMcu.bGot_cli_ca_sendData = true;

			//
			_sntprintf(pVc->tStatusBuf, mycountof(pVc->tStatusBuf), _T("读取设备key成功"));


			//
			break;
		}
		//
		continue;
	}



	//
	iErr = 0;

	//
errLabel:

	//
	closeTool_ca(&pVc->toolCa);

#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("tmpThreadProc_ca leaves"));
#endif

	//
	return  0;
}


//
//
DWORD  tmpThreadProc_dev_sxrz_toGet_cliData(LPVOID pParam)
{
#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("tmpThreadProc_ca enters"));
#endif

	//
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
	if (!pCtxSm)  return  -1;
	Var_ca_dev_qmc* pVc = &pCtxSm->ca_dev;
	TCHAR	tBuf[128];

	//
	pVc->toolCa.tn_process_ca = getuiNextTranNo(nullptr, 0, &pCtxSm->tn0_ca);

	//
	bool  bSys = false;
	bool  bDev = true;
	HKEY  hKeyRoot0 = HKEY_CURRENT_USER;
	TCHAR* rootKey = (TCHAR*)_T(CONST_rootKey_ca);
	//
	//TCHAR  cfgName_req[128];
	//TCHAR  cfgName_resp[128];
	//
	TCHAR  cfgName_req_serv_random[128];
	TCHAR  cfgName_req_serv_cert[128];
	TCHAR  cfgName_req_serv_signData[128];
	//
	TCHAR  cfgName_resp_cli_cert[128];
	TCHAR  cfgName_resp_cli_signData[128];



	//TCHAR  cfgName_resp[128];


	//
	//_sntprintf(cfgName_req, mycountof(cfgName_req), _T("%s%d"), _T(CONST_regValName_ca_sendData_prefix), pVc->toolCa.tn_process_ca);
	//tmpSetRegCfg_open(hKeyRoot0, rootKey, cfgName_req, REG_BINARY, pVc->serv.ca_sendData, pVc->serv.ca_sendDataLen);

	//
	_sntprintf(cfgName_req_serv_random, mycountof(cfgName_req_serv_random), _T("%s%d"), _T(CONST_regValName_serv_random_prefix), pVc->toolCa.tn_process_ca);
	tmpSetRegCfg_open(hKeyRoot0, rootKey, cfgName_req_serv_random, REG_BINARY, pVc->sxrz.serv.param_sxrz_servReply.serv_random, strlen(pVc->sxrz.serv.param_sxrz_servReply.serv_random));
	_sntprintf(cfgName_req_serv_cert, mycountof(cfgName_req_serv_cert), _T("%s%d"), _T(CONST_regValName_serv_cert_prefix), pVc->toolCa.tn_process_ca);
	tmpSetRegCfg_open(hKeyRoot0, rootKey, cfgName_req_serv_cert, REG_BINARY, pVc->sxrz.serv.param_sxrz_servReply.serv_cert, strlen(pVc->sxrz.serv.param_sxrz_servReply.serv_cert));
	_sntprintf(cfgName_req_serv_signData, mycountof(cfgName_req_serv_signData), _T("%s%d"), _T(CONST_regValName_serv_signData_prefix), pVc->toolCa.tn_process_ca);
	tmpSetRegCfg_open(hKeyRoot0, rootKey, cfgName_req_serv_signData, REG_BINARY, pVc->sxrz.serv.param_sxrz_servReply.serv_signData, strlen(pVc->sxrz.serv.param_sxrz_servReply.serv_signData));




	//
	//_sntprintf(cfgName_resp, mycountof(cfgName_resp), _T("%s%d"), _T(CONST_regValName_ca_sendDataResp_prefix), pVc->toolCa.tn_process_ca);
	//qyDelRegCfgT(hKeyRoot0, rootKey, cfgName_resp);

	_sntprintf(cfgName_resp_cli_cert, mycountof(cfgName_resp_cli_cert), _T("%s%d"), _T(CONST_regValName_cli_cert_prefix), pVc->toolCa.tn_process_ca);
	qyDelRegCfgT(hKeyRoot0, rootKey, cfgName_resp_cli_cert);
	_sntprintf(cfgName_resp_cli_signData, mycountof(cfgName_resp_cli_signData), _T("%s%d"), _T(CONST_regValName_cli_signData_prefix), pVc->toolCa.tn_process_ca);
	qyDelRegCfgT(hKeyRoot0, rootKey, cfgName_resp_cli_signData);

	//
	safeTcsnCpy(_T("准备获取终端证书"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));


	//
	int caToolType = CONST_caToolType_bjca1;

	std::string pwd = "";
    std::string caIp = pCtxSm->caYqServIp;
	int caPort = pCtxSm->caYqServPort;
	if (pProcInfo->authInfo.usAuthType == CONST_authType_jdzy) {
		caToolType = CONST_caToolType_jdzyCli;		
	}

	TCHAR* who = (TCHAR*)_T("bjca1.cli.auth");
	//
	TCHAR* devPrefix = pCtxSm->smTerminalInitCfg.devPrefix;
	bool  bFullCmp = pProcInfo->m_bUseKeyToLogin_forQmcGui;

	
	//
	if (createTool_ca(pQyMc->cfg.installDir, caToolType, who, CONST_caCmd_login_auth, bSys, devPrefix,  bDev, bFullCmp,  (char*)caIp.c_str(), caPort, (char*)pwd.c_str(), pQyMc->cfg.qmcLogFile, &pVc->toolCa))  goto  errLabel;

	//
#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("createTool_ca ok"));
#endif

	//
	int  i;
	int maxSteps; maxSteps = 10;// 1000;
	for (i = 0; i < maxSteps; i++)
	{
		if (pVc->toolCa.bNeedQuit)  goto  errLabel;

		//
		waitForObject(&pVc->toolCa.hProcess_ca, 1000);
		if (!pVc->toolCa.hProcess_ca) {
#ifdef  __DEBUG__
			traceLog((TCHAR*)_T("tool_ca waited"));
#endif
			//
			char cli_cert[4096];
			char cli_signData[2048];


			//
			unsigned  int  uiType = 0;
			char  buf[4096];
			unsigned  int bufLen = 0;
			bufLen = sizeof(buf);

			//if (tmpGetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp, &uiType, buf, &bufLen))  goto  errLabel;
			//buf[bufLen] = 0;

			bufLen = sizeof(buf);
			if (tmpGetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp_cli_cert, &uiType, buf, &bufLen)) {
				//
				qmcLogForHg(CONST_hgLogType_sxrzsb, (TCHAR*)_T("双向认证失败"), false);
				//
				goto  errLabel;
			}
			if (bufLen > sizeof(cli_cert) - 1) goto  errLabel;
			memcpy(cli_cert, buf, bufLen);
			cli_cert[bufLen] = 0;

			bufLen = sizeof(buf);
			if (tmpGetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp_cli_signData, &uiType, buf, &bufLen)) {
				//
				qmcLogForHg(CONST_hgLogType_sxrzsb, (TCHAR*)_T("双向认证失败"), false);
				//
				goto  errLabel;
			}
			if (bufLen > sizeof(cli_signData) - 1) goto  errLabel;
			memcpy(cli_signData, buf, bufLen);
			cli_signData[bufLen] = 0;


			//
			//qyDelRegCfgT(hKeyRoot0, rootKey, cfgName_req);
			//qyDelRegCfgT(hKeyRoot0, rootKey, cfgName_resp);
			//
			qyDelRegCfgT(hKeyRoot0, rootKey, cfgName_req_serv_random);
			qyDelRegCfgT(hKeyRoot0, rootKey, cfgName_req_serv_cert);
			qyDelRegCfgT(hKeyRoot0, rootKey, cfgName_req_serv_signData);
			//
			qyDelRegCfgT(hKeyRoot0, rootKey, cfgName_resp_cli_cert);
			qyDelRegCfgT(hKeyRoot0, rootKey, cfgName_resp_cli_signData);



			//			
			if (strlen(cli_cert) >= sizeof(pVc->sxrz.cli.cert))  goto  errLabel;
			safeStrnCpy(cli_cert, pVc->sxrz.cli.cert, mycountof(pVc->sxrz.cli.cert));
			if (strlen(cli_signData) >= sizeof(pVc->sxrz.cli.signData))goto  errLabel;
			safeStrnCpy(cli_signData, pVc->sxrz.cli.signData, mycountof(pVc->sxrz.cli.signData));


			//
			pVc->flgs.sxrz.bGot_cliData = true;

			//
			break;
		}
		//
		continue;
	}



	//
	iErr = 0;

	//
errLabel:

	//
	closeTool_ca(&pVc->toolCa);

#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("tmpThreadProc_ca leaves"));
#endif

	//
	return  0;
}



//
 void smLogin_onTimer(HWND  hDlgLogin, DLG_mcClientLogon_var * pm_var, Ctx_sm  *  pCtxSm,  bool* pbNeedAccept)
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	Var_ca_dev_qmc* pVc = &pCtxSm->ca_dev;

	if (!pm_var)  return;
	DLG_mcClientLogon_var& m_var = *pm_var;
	SmLoginVar& m_smLoginVar = pm_var->m_smLoginVar;
	if (!pCtxSm)  return;
	Sm_terminal_initCfg* pCfg = &pCtxSm->smTerminalInitCfg;

	//
	if (!pbNeedAccept)  return;

	//
#ifdef  __DEBUG__
#if  0
	HWND  hWnd = (HWND)this->winId();
	::MoveWindow(hWnd, 0, 0, 100, 100, true);
#endif

	if (pQyMc->bQuit) {
		int  ii = 0;
	}
#endif



	//
	uint curTickCnt = myGetTickCount(nullptr);

	//
	waitForObject(&m_smLoginVar.m_hThread_ca, 0);

	//
	int iDiffInMs = curTickCnt - pVc->dwLastTickCnt_chkLogin;
	int maxWaitInMs = 60 * 1000;// 60 * 1000;
	if (!pVc->mcuIp_toChk[0]  ||  abs(iDiffInMs > maxWaitInMs))
	{  //  如果60秒还没完成设备登录，就要重新发起设备登录
									//		
		if (!m_smLoginVar.m_hThread_ca) {

			//
			showInfo_open0(0, 0, _T("60秒都没完成设备登录，就要重新发起设备登录"));
			//
			_sntprintf(pVc->tStatusBuf, mycountof(pVc->tStatusBuf), _T("发起设备登录%S"), pCfg->terminal_mcu);

			//
			pVc->dwLastTickCnt_chkLogin = curTickCnt;

			//
			pMisCnt->dualSystem.dwConfMcuIp = 0;

			//
			pVc->nTimes_chkLogin++;
			//
			bool  bUse2ndMcu = false;
			if (pVc->nTimes_chkLogin > 2
				&& (pVc->nTimes_chkLogin % 2))
			{
				char  str2ndMcu[128] = "";
				//
				//get_2ndMcu(str2ndMcu, mycountof(str2ndMcu));
				safeStrnCpy(pCfg->terminal_mcu2, str2ndMcu, mycountof(str2ndMcu));
				//
				if (bIpValid(str2ndMcu)) {
					bUse2ndMcu = true;
					//
					safeStrnCpy(str2ndMcu, pVc->mcuIp_toChk, mycountof(pVc->mcuIp_toChk));
				}
			}
			if (!bUse2ndMcu) {
				safeStrnCpy(pCfg->terminal_mcu, pVc->mcuIp_toChk, mycountof(pVc->mcuIp_toChk));
			}

			//			
			if (pQyMc->bLogon) {
				showInfo_open0(0, 0, _T("before logoff"));
				qmcLogoff();
			}
			//			
			memset(&pVc->flgs, 0, sizeof(pVc->flgs));
			iErr = 0; goto  errLabel;
		}
	}

	if (abs((int)(curTickCnt - pVc->dwLastTickCnt_chk_thread_ca)) > 1000) {
		//
		pVc->dwLastTickCnt_chk_thread_ca = curTickCnt;

		//  202310/12
		if (pProcInfo->getAuthType() == CONST_authType_logon) {
			pVc->flgs.loginToMcu.bGot_caServCfg = true;
			pVc->flgs.loginToMcu.bGot_random = true;
			pVc->flgs.loginToMcu.bGot_cli_ca_sendData = true;
		}


		//
		if (!pVc->flgs.loginToMcu.bGot_caServCfg) {

			//
			//safeStrnCpy((char*)"218.240.128.210", pProcInfo->m_var.caGwIp, mycountof(pProcInfo->m_var.caGwIp));

						//
			int curIndex = 0; // ui->editServer->currentIndex();




			int i = 1;
			//
			char servIp[128];
			int  port;

			//
			if (curIndex < 0 || curIndex >= CONST_maxOfVideoConferencingServers)  goto  errLabel;

			int  tmpIndex = m_smLoginVar.m_tmpCntDisplays.mems[curIndex].index;
			m_var.iSeqNoSelected = tmpIndex;
			//
			//safeStrnCpy(pProcInfo->m_var.smTerminalInitCfg.terminal_mcu, m_var.cntCfgs.mems[tmpIndex].cntAddr, mycountof(m_var.cntCfgs.mems[tmpIndex].cntAddr));
			safeStrnCpy(pVc->mcuIp_toChk, m_var.cntCfgs.mems[tmpIndex].cntAddr, mycountof(m_var.cntCfgs.mems[tmpIndex].cntAddr));
			m_var.cntCfgs.mems[tmpIndex].port = 8768;
			//
			safeStrnCpy(m_var.cntCfgs.mems[tmpIndex].cntAddr, servIp, mycountof(servIp));
			port = m_var.cntCfgs.mems[tmpIndex].port;

			//
			MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));



			QY_COMM_AUTHINFO_MIS authInfo;
			memset(&authInfo, 0, sizeof(authInfo));
			authInfo.usAuthType = pProcInfo->getAuthType();

			//
			showInfo_open0(0, 0, _T("before bGetCaAservCfg"));
			//
			if (!bGetCaServCfg(&pQyMc->env, servIp, port, pMisCnt, &authInfo, pQyMc->iServiceId, qnmVerStr(pQyMc->iServiceId), &pMisCnt->commEncCtx.common, pQyMc->i64StartTime_base,  &pQyMc->cfg.to)) {
				//
#ifdef  __DEBUG__
				traceLog((TCHAR*)_T("bGetCaServCfg failed"));
#endif
				//
				_sntprintf(  pVc->tStatusBuf,  mycountof(  pVc->tStatusBuf),  _T("bGetCaServCfg失败: 可能是连接 %s:%d %s"), CQyString(servIp), (int)port, _T("失败"));
				showInfo_open0(0, 0, pVc->tStatusBuf);

				//
				goto  errLabel;
			}
			//
			safeStrnCpy(pMisCnt->commEncCtx.caServCfg.caGwIp, pCtxSm->caGwIp, mycountof(pCtxSm->caGwIp));
			pCtxSm->caGwPort = pMisCnt->commEncCtx.caServCfg.caGwPort;

			safeStrnCpy(pMisCnt->commEncCtx.caServCfg.hgGwIp, pCtxSm->hgGwIp, mycountof(pCtxSm->hgGwIp));
			pCtxSm->hgGwPort = pMisCnt->commEncCtx.caServCfg.hgGwPort;
			safeStrnCpy(pMisCnt->commEncCtx.caServCfg.caYqServIp, pCtxSm->caYqServIp, mycountof(pCtxSm->caYqServIp));

			//
			_sntprintf(pVc->tStatusBuf, mycountof(pVc->tStatusBuf), _T("bGetCaServCfg ok, caGwIp %S:%d"), pCtxSm->caGwIp,  pCtxSm->caGwPort);
			showInfo_open0(0, 0, pVc->tStatusBuf);

			//
			pVc->flgs.loginToMcu.bGot_caServCfg = true;
		}

		//
		if (!pVc->flgs.loginToMcu.bGot_caServCfg) {
			showInfo_open0(0, 0, _T("qmcLogin.failed, bGot_caServCfg false, "));
			goto  errLabel;
		}


		//
		if (!pVc->flgs.loginToMcu.bGot_random) {
			//			
			//
			int curIndex = 0; // ui->editServer->currentIndex();
			//
			TCHAR  *  serviceNameLogin = (TCHAR*)_T(  ""  ); // ui->editServer->currentText();
			TCHAR  *  UserName = (TCHAR*)_T(  ""  ); // ui->editUserAccount->text();
			TCHAR  *  Password = (TCHAR*)_T(  ""  );  //ui->editPassword->text();



			int i = 1;
			//
			char servIp[128];
			int  port;

			//
			if (curIndex < 0 || curIndex >= CONST_maxOfVideoConferencingServers)  goto  errLabel;

			int  tmpIndex = m_smLoginVar.m_tmpCntDisplays.mems[curIndex].index;
			m_var.iSeqNoSelected = tmpIndex;
			//
			//safeStrnCpy(pProcInfo->m_var.smTerminalInitCfg.terminal_mcu, m_var.cntCfgs.mems[tmpIndex].cntAddr, mycountof(m_var.cntCfgs.mems[tmpIndex].cntAddr));
			safeStrnCpy(pVc->mcuIp_toChk, m_var.cntCfgs.mems[tmpIndex].cntAddr, mycountof(m_var.cntCfgs.mems[tmpIndex].cntAddr));
			m_var.cntCfgs.mems[tmpIndex].port = 8768;
			//
			safeStrnCpy(m_var.cntCfgs.mems[tmpIndex].cntAddr, servIp, mycountof(servIp));
			port = m_var.cntCfgs.mems[tmpIndex].port;

			//
			MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

			//
			switch (pProcInfo->getAuthType()) {
			case  CONST_authType_jdzy:

				//
				//if (getCorrectCnt(&pQyMc->env, &pMisCnt->cfg.dynCfg, bServConnected_mis, pMisCnt, pQyMc->iServiceId, qnmVerStr(pQyMc->iServiceId), &pMisCnt->commEncCtx.common, &pQyMc->cfg.to, &tmpCnt)) {

				QY_COMM_AUTHINFO_MIS authInfo;
				memset(&authInfo, 0, sizeof(authInfo));
				authInfo.usAuthType = pProcInfo->getAuthType();

				//
				if (!bGetCaRandom(&pQyMc->env, servIp, port, pMisCnt, &authInfo, pQyMc->iServiceId, qnmVerStr(pQyMc->iServiceId), &pMisCnt->commEncCtx.common, pQyMc->i64StartTime_base,&pQyMc->cfg.to)) {
					goto  errLabel;
				}

				//
				pVc->flgs.loginToMcu.bGot_random = true;

				//
				break;
			default:
				pVc->flgs.loginToMcu.bGot_random = true;
				break;
			}
		}


		if (pVc->flgs.loginToMcu.bGot_random) {
			//
			if (!pVc->flgs.loginToMcu.bGot_cli_ca_sendData) {
				DWORD  dwThreadDaemonId;

				if (!m_smLoginVar.m_hThread_ca) {

					//
					m_smLoginVar.m_hThread_ca = CreateThread(NULL, 0, tmpThreadProc_dev_ca_toGet_cli_sendData, 0, CREATE_SUSPENDED, &dwThreadDaemonId);
					if (!m_smLoginVar.m_hThread_ca)  goto  errLabel;
					//gBuf_rtspCliHelp.dwThreadId_spl = dwThreadDaemonId;
					if (ResumeThread(m_smLoginVar.m_hThread_ca) == -1)  goto  errLabel;

				}
			}
		}

	}


	//
	if (pVc->flgs.loginToMcu.bGot_cli_ca_sendData)
	{
		//
		if (!pQyMc->bLogon) {
			//
			showInfo_open0(0, 0, _T("before login"));
			//
			bool bOk_doLogin = false;
			login_do_onLoginOkclicked(hDlgLogin, m_var, m_smLoginVar, true, &bOk_doLogin);
			if (!bOk_doLogin) {
				//
				memset(&pVc->flgs, 0, sizeof(pVc->flgs));
				//
				showInfo_open0(0, 0, _T("qmcLogin: doLogin not ok, try to get ca_sendData again"));
			}
			//
			showInfo_open0(0, 0, _T("after login"));

		}
		//
		if (pQyMc->bLogon) {
			DWORD  dwTickCnt = myGetTickCount(mynull);
			int iDiffInMs = dwTickCnt - pVc->flgs.dwLastTickCnt_startToSxrz;
			int maxWaitInMs_sxrz = 30 * 1000;// 20 * 1000;
			if (abs(iDiffInMs) > maxWaitInMs_sxrz) {


				//
				showInfo_open0(0, 0, _T("start to sxrz"));
				//(_T("发起双向认证请求"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
				_sntprintf(pVc->tStatusBuf, mycountof(pVc->tStatusBuf), _T("发起双向认证请求%S"), pMisCnt->server.ip);

				//
				memset(&pVc->flgs.sxrz, 0, sizeof(pVc->flgs.sxrz));

				//
				if (pProcInfo->getAuthType() == CONST_authType_logon) {
					pVc->flgs.sxrz.bGot_servReply = true;
					pVc->flgs.sxrz.bGot_cliData = true;
					pVc->flgs.sxrz.bDone_sxrz = true;
					pVc->flgs.sxrz.bDone_sqm = true;
				}


				//
				MACRO_prepareForTran();
				QIS_ca_req  req;

				//
				memset(&req, 0, sizeof(req));
				req.uiType = CONST_imCommType_qisCaReq;
				//
				if (1) {
					_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "[cmd=%d]", CONST_hgCmd_sxrz_cliStart);
					req.ca_cliDataLen = strlen(req.ca_cliData);
				}
				//
				int len = sizeof(req);
				pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);
				//
				pVc->flgs.dwLastTickCnt_startToSxrz = dwTickCnt;

			}
			else {
				if (pVc->flgs.sxrz.bGot_servReply) {

					if (!pVc->flgs.sxrz.bGot_cliData) {
						//
						DWORD  dwThreadDaemonId;


						if (!m_smLoginVar.m_hThread_ca) {

							//
							m_smLoginVar.m_hThread_ca = CreateThread(NULL, 0, tmpThreadProc_dev_sxrz_toGet_cliData, 0, CREATE_SUSPENDED, &dwThreadDaemonId);
							if (!m_smLoginVar.m_hThread_ca)  goto  errLabel;
							//gBuf_rtspCliHelp.dwThreadId_spl = dwThreadDaemonId;
							if (ResumeThread(m_smLoginVar.m_hThread_ca) == -1)  goto  errLabel;


						}
					}
					else {
						//
						if (!pVc->flgs.sxrz.bSent_cliData) {
							//
							pVc->flgs.sxrz.bSent_cliData = true;

							//
							//safeTcsnCpy(_T("发送终端证书到服务器"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
							safeTcsnCpy(_T("snd term cert to server"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));

							//
							MACRO_prepareForTran();
							QIS_ca_req  req;

							//
							memset(&req, 0, sizeof(req));
							req.uiType = CONST_imCommType_qisCaReq;

							//
							_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "[obj=%d len=%d]%s [obj=%d len=%d]%s", CONST_hgType_sxrz_cli_cert, strlen(pVc->sxrz.cli.cert), pVc->sxrz.cli.cert,
								CONST_hgType_sxrz_cli_signData, strlen(pVc->sxrz.cli.signData), pVc->sxrz.cli.signData);
							//
#ifdef  __DEBUG__
							//_snprintf(req.sxrz_cliData, mycountof(req.sxrz_cliData), "%s [obj=%d len=%d]%s", req.sxrz_cliData, CONST_sxrz_serv_random,  strlen(pVc->sxrz.serv.param_sxrz_servReply.serv_random), pVc->sxrz.serv.param_sxrz_servReply.serv_random);
#endif
							//
							req.ca_cliDataLen = strlen(req.ca_cliData);

							//
							int len = sizeof(req);
							pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);

						}
						else {

							//
							if (pVc->flgs.sxrz.bDone_sxrz) {

#if 10
								//
								if (!pVc->flgs.sxrz.bSent_sqm) {
									pVc->flgs.sxrz.bSent_sqm = true;


									//
									safeTcsnCpy(_T("发送授权码到服务器"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));

									//
									MACRO_prepareForTran();
									QIS_ca_req  req;

									//
									memset(&req, 0, sizeof(req));
									req.uiType = CONST_imCommType_qisCaReq;

									//
									char  certId[256] = "";
									login_getCertId(certId, mycountof(certId));

									//
									char  clientIp[CONST_qyMaxIpLen + 1] = "";
									MIS_CHANNEL* pChannel = getChannelByType(pMisCnt, 0);
									if (!pChannel)  goto  errLabel;
									safeStrnCpy(pChannel->session.clientIp, clientIp, mycountof(clientIp));

									//  将电话告知的设备授权码+证书的唯一标识，送到会管服务器
									_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "[cmd=%d] [obj=%d len=%d]%s [obj=%d len=%d]%s [obj=%d len=%d]%s", CONST_hgCmd_sxrz_cliSqm, CONST_hgType_sxrz_cli_sqm, strlen(pCfg->terminal_sqm), pCfg->terminal_sqm,
										CONST_hgType_sxrz_cli_certId, strlen(certId), certId,
										CONST_hgType_sxrz_cli_ip, strlen(clientIp), clientIp
									);
									//
#ifdef  __DEBUG__
#endif
							//
									req.ca_cliDataLen = strlen(req.ca_cliData);

									//
									int len = sizeof(req);
									pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);




								}
#endif
								//
								if (pVc->flgs.sxrz.bDone_sqm) {
									//this->accept();
									*pbNeedAccept = true;
									iErr = 0;  goto  errLabel;
								}

							}

						}


					}





				}
			}


		}
		//
		iErr = 0;  goto  errLabel;
	}

	//



errLabel:

	//
	return;
}


//
//
int  dlgMcClientLogon_OnOK_sm(QY_MC  *  pQyMc,  HWND hDlg, DLG_mcClientLogon_var& m_var, char* m_server, LPTSTR  m_name, LPTSTR  m_passwd, char* ca_sendData, unsigned  int  ca_sendDataLen)
{
	int							iErr = -1;

	// TODO: Add your control notification handler code here
	//CDlgMcClientLogon* pDlg = (CDlgMcClientLogon*)CDlgMcClientLogon::FromHandle(hDlg);
	//DLG_mcClientLogon_var& m_var = pDlg->m_var;
	TCHAR						tBuf[128];

	//
	//QY_MC* pQyMc = QY_GET_GBUF();
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
	if (bAnotherInstanceExists(pQyMc, appObjPrefix)) {
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("failed: bAnotherInstanceExists returns true"));
#endif
		goto  errLabel;
	}
#endif

	//
	TCHAR						tPrefix[32]; tPrefix[0] = 0;// = _T("");
	_sntprintf(tPrefix, mycountof(tPrefix), _T("%d: "), m_var.nTries_triggerIDOK);

	if (!bSupported_devAuth()) {

#if  0
		if (!m_name || !m_name[0])  goto  errLabel;
		if (!m_passwd || !m_passwd[0])  goto  errLabel;

		//
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
#endif

		//
		lstrcpyn(pProcInfo->authInfo.messengerName, m_name, mycountof(pProcInfo->authInfo.messengerName));
		myTChar2Utf8(m_passwd, buf, mycountof(buf));
		len = mycountof(pProcInfo->authInfo.messengerPasswd);
		bQyGetStrMd5_x(buf, pProcInfo->authInfo.messengerPasswd, &len);

		//
		if (pProcInfo->authInfo.usAuthType == CONST_authType_bjca
			|| pProcInfo->authInfo.usAuthType == CONST_authType_jdzy)
		{
			if (!ca_sendData || !ca_sendDataLen) {
				showInfo_open0(0, 0, _T("dlgMcClientLogon_OnOK_qt failed, ca_sendData is null or ca_sendDataLen is 0"));
				goto  errLabel;
			}
			if (ca_sendDataLen > mycountof(pProcInfo->authInfo.ca_sendData)) {
				showInfo_open0(0, 0, _T("dlgMcClientLogon_OnOK_qt failed, ca_sendDataLen too big"));
				goto  errLabel;
			}
			memcpy(pProcInfo->authInfo.ca_sendData, ca_sendData, ca_sendDataLen);
			pProcInfo->authInfo.ca_sendDataLen = ca_sendDataLen;
		}

	}

	//  CWaitCursor		cur;

	//
	_sntprintf(m_var.cntCfg[m_var.iSeqNoSelected].usr, mycountof(m_var.cntCfg[m_var.iSeqNoSelected].usr), m_name);
	_sntprintf(m_var.cntCfg[m_var.iSeqNoSelected].passwd, mycountof(m_var.cntCfg[m_var.iSeqNoSelected].passwd), m_passwd);
	//
	if (pProcInfo->getAuthType() == CONST_authType_logon) {
		Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
		if (pCtxSm) {
			safeStrnCpy(pCtxSm->smTerminalInitCfg.terminal_mcu, m_var.cntCfg[m_var.iSeqNoSelected].cntIp, mycountof(m_var.cntCfg[m_var.iSeqNoSelected].cntIp));
			safeStrnCpy(pCtxSm->smTerminalInitCfg.terminal_mcu2, m_var.cntCfg[m_var.iSeqNoSelected].cntAddrs[0], mycountof(m_var.cntCfg[m_var.iSeqNoSelected].cntAddrs[0]));
		}
	}
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
	unsigned  __int64               userId; userId = 0;

	//for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
	for (i = 0; i < pProcInfo->ucCnt_misCnts; i++)
	{
		MIS_CNT* pMisCnt = getMisCntByIndex(0, pProcInfo, i);//&pProcInfo->misCnts[i];
		if (!pMisCnt)  continue;
		MIS_CHANNEL* pChannel = getChannelByType(pMisCnt, CONST_channelType_talking);
		if (!pChannel)  continue;

		if (pChannel->bSessionOpen) {
			qnmCloseSession_msg(mynull,&pChannel->session, &pChannel->sock, &pQyMc->cfg.to,  _T("dlgMcClientLogon_OnOK_sm.l1306"));
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
			HWND  hWnd = hDlg;// (HWND)pDlg->window()->winId();


			m_var.respHint[0] = 0;
			if (!doMisCntLogon(pMisCnt, pChannel, hWnd, m_var.respHint, mycountof(m_var.respHint))) {
				userId = pMisCnt->idInfo.ui64Id;
				break;
			}

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
	pQyMc->curUsrInfo.common.id = userId;
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
int sm_doMcClientLogonOK(QY_MC  *  pQyMc,  HWND  hDlgQmcLogin, DLG_mcClientLogon_var& m_var, char* m_server, LPTSTR m_name, LPTSTR m_passwd, char* ca_sendData, int ca_sendDataLen)
{
	int iErr = -1;
	//CCtxQyMc* pQyMc = QY_GET_GBUF();
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	//
	//CQmcLogin* pDlg = (CQmcLogin*)pQmcLogin;


	//
	if (pQyMc->bLogon) return -1;


	//
	if (dlgMcClientLogon_OnOK_sm(pQyMc,  hDlgQmcLogin, m_var, m_server, m_name, m_passwd, ca_sendData, ca_sendDataLen) != 0) return -1;

	//


	//
	pQyMc->bLogon = true;
	pQyMc->dwTickCnt_logon = myGetTickCount(NULL);


	//
#if 0
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
#endif




#if 0

	//
	pQyMc->cfg.db.iDbType = CONST_dbType_myDb;

	//
	QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  goto  errLabel;
	QM_dbFuncs& g_dbFuncs = *pDbFuncs;


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
	if (pProcInfo->m_var.pDBManager == null)goto  errLabel;
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
	showInfo_open0(0, null, _T("doMcClientLogon: before start threadProcs"));

	int  i;
	DWORD  dwThreadDaemonId;
	for (i = 0; i < mycountof(pQyMc->hDaemonThreads); i++) {
		if (pQyMc->threadProcs[i]) {
			pQyMc->hDaemonThreads[i] = CreateThread(NULL, 0, pQyMc->threadProcs[i], pQyMc, 0, &dwThreadDaemonId);
			if (pQyMc->hDaemonThreads[i] == NULL) goto errLabel;
		}
	}


	//
	showInfo_open0(0, null, _T("doMcClientLogon: after start threadProcs"));
#endif



	//
	iErr = 0;

errLabel:

	if (0 != iErr)
	{
		qmcLogoff();
	}



	return iErr;
}



//
void  smLogin_clean(SmLoginVar &m_smLoginVar,  Ctx_sm  *  pCtxSm)
{
	if (m_smLoginVar.m_hThread_ca) {
		pCtxSm->ca_dev.toolCa.bNeedQuit = true;
		//
		waitForObject(&m_smLoginVar.m_hThread_ca, INFINITE);
		//
		pCtxSm->ca_dev.toolCa.bNeedQuit = false;
	}

	return;
}

//
void smUsrLogin_clean(SmUsrLoginVar& m_usrVar, Ctx_sm* pCtxSm)
{
	if (!pCtxSm) return;

	if (m_usrVar.m_hThread_ca) {
		pCtxSm->ca_usr.toolCa.bNeedQuit = true;
		//
		waitForObject(&m_usrVar.m_hThread_ca, INFINITE);
		//
		pCtxSm->ca_usr.toolCa.bNeedQuit = false;
	}

	return;
}


///////////////////////
//
DWORD  tmpThreadProc_ca_usr(LPVOID pParam)
{
	bool  bDbg = false;

	//
#ifdef  __DEBUG__
	if (bDbg) {
		traceLog((TCHAR*)_T("tmpThreadProc_ca_usr enters"));
	}
#endif

	//
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
	if (!pCtxSm)  return  -1;
	Var_ca_usr_qmc* pVc = &pCtxSm->ca_usr;
	TCHAR	tBuf[128];

	//
	DWORD  dwTickCnt_start = myGetTickCount(mynull);

	//
	pVc->toolCa.tn_process_ca = getuiNextTranNo(nullptr, 0, &pCtxSm->tn0_ca);

	//
	bool  bSys = false;
	bool  bDev = false;
	HKEY  hKeyRoot0 = HKEY_CURRENT_USER;
	//
	TCHAR  cfgName_req[128];
	_sntprintf(cfgName_req, mycountof(cfgName_req), _T("%s%d"), _T(CONST_regValName_ca_sendData_prefix), pVc->toolCa.tn_process_ca);

	TCHAR  cfgName_resp[128];
	_sntprintf(cfgName_resp, mycountof(cfgName_resp), _T("%s%d"), _T(CONST_regValName_ca_sendDataResp_prefix), pVc->toolCa.tn_process_ca);
	qyDelRegCfgT(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp);

	TCHAR  cfgName_resp_chkUsrKey[128];
	_sntprintf(cfgName_resp_chkUsrKey, mycountof(cfgName_resp_chkUsrKey), _T("%s%d"), _T(CONST_regValName_ca_chkUsrKeyResp_prefix), pVc->toolCa.tn_process_ca);
	qyDelRegCfgT(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp_chkUsrKey);

	//
	TCHAR  cfgName_resp_pinRetryCount[128];
	_sntprintf(cfgName_resp_pinRetryCount, mycountof(cfgName_resp_pinRetryCount), _T("%s%d"), _T(CONST_regValName_ca_pinRetryCountResp_prefix), pVc->toolCa.tn_process_ca);
	qyDelRegCfgT(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp_pinRetryCount);


	TCHAR* who = (TCHAR*)_T("bjca.usr");

	int caToolType = CONST_caToolType_bjca;

	

	int  iCmd = 0;
	char* pwd = (char*)"";
	std::string caIp = pCtxSm->caGwIp;
	int caPort = pCtxSm->caGwPort;
	if (pVc->bTryToChkUsrKey) {
		iCmd = CONST_caCmd_chkUsrKey;
		//
		//safeTcsnCpy(_T("正在检测UKEY插入"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));

		if (pProcInfo->getAuthType() == CONST_authType_jdzy) {
			caToolType = CONST_caToolType_jdzyCli;
		}

	}
	else {
		iCmd = CONST_caCmd_usrData;
		//
		pwd = pVc->usrLogin.keyPasswd;
		//
		safeTcsnCpy(_T("启动Key身份认证"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));

		if (pProcInfo->getAuthType() == CONST_authType_jdzy) {
			caToolType = CONST_caToolType_jdzyCli_sx;
			//caIp = "10.0.1.135";
			//caPort = 443;
			caIp = pCtxSm->hgGwIp;
			caPort = pCtxSm->hgGwPort;
		}

	}


	//
	bool  bFullCmp = false;
	if (createTool_ca(pQyMc->cfg.installDir, caToolType, who, iCmd, bSys, nullptr, bDev, bFullCmp, (char*)caIp.c_str(), caPort, pwd, pQyMc->cfg.qmcLogFile, &pVc->toolCa))  goto  errLabel;

	//
#ifdef  __DEBUG__
	if (bDbg) {
		traceLog((TCHAR*)_T("createTool_ca ok"));
	}
#endif

	//
	int  i;
	int maxSteps; maxSteps = 100;// 1000;
	for (i = 0; i < maxSteps; i++)
	{
		if (pVc->toolCa.bNeedQuit)  goto  errLabel;

		//
		waitForObject(&pVc->toolCa.hProcess_ca, 100);
		if (!pVc->toolCa.hProcess_ca) {
#if  1  //  def  __DEBUG__
			//traceLog((TCHAR*)_T("tool_ca waited"));
			showInfo_open0(0, 0, _T("tool_ca waited"));
#endif
			//
			unsigned  int  uiType = 0;
			char  buf_resp[4096] = "";
			char  buf_resp_chkUsrKey[4096];
			unsigned  int bufLen = 0;

			//
			bufLen = sizeof(buf_resp_chkUsrKey);
			if (tmpGetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp_chkUsrKey, &uiType, buf_resp_chkUsrKey, &bufLen)) {
				bufLen = 0;
			}
			buf_resp_chkUsrKey[bufLen] = 0;


			//
			bufLen = sizeof(buf_resp);
			if (tmpGetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp, &uiType, buf_resp, &bufLen)) {
				bufLen = 0;
			}
			buf_resp[bufLen] = 0;

			//
			char  buf_resp_pinRetryCount[128];
			bufLen = sizeof(buf_resp_pinRetryCount);
			if (tmpGetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp_pinRetryCount, &uiType, buf_resp_pinRetryCount, &bufLen)) {
				bufLen = 0;
			}
			buf_resp_pinRetryCount[bufLen] = 0;
			if (!pVc->bTryToChkUsrKey) {
				int  i = 0;
			}





			//
			TMP_caTool_result  result;



			//
			if (pVc->bTryToChkUsrKey) {

				//
				memset(&result, 0, sizeof(result));
				parse_sendDataResp(buf_resp_chkUsrKey, &result);

				//
				pVc->bExists_usrKey = result.bExists_usrKey;

				//
			//	_sntprintf(tBuf, mycountof(tBuf), _T("threadProc_ca_usr: bExists_usrKey %d"), pVc->bExists_usrKey);
#ifdef  __DEBUG__
				traceLog(tBuf);
#endif
				safeTcsnCpy(tBuf, pVc->tStatusBuf, mycountof(pVc->tStatusBuf));

				//
				break;
			}

			//
			memset(&result, 0, sizeof(result));
			parse_sendDataResp(buf_resp, &result);

			//
			if (!result.tUsrName[0]) {
				//
				_sntprintf(tBuf, mycountof(tBuf), _T("thread_ca_usr: getUsrName failed"));
				showInfo_open0(0, 0, tBuf);
				qmcLogStatus(_T("thread_ca_usr"), 0, _T("getUsrUsr failed"));
				//
				pVc->usrLogin.bFailed_getUsrName = true;
				pVc->usrLogin.iPinRetryCount = atol(buf_resp_pinRetryCount);
				//
				goto  errLabel;
			}


			//
			_sntprintf(tBuf, mycountof(tBuf), _T("threadProc_ca_usr: get tUsrName [%s]"), result.tUsrName);
			showInfo_open0(0, 0, tBuf);
#ifdef  __DEBUG__
			traceLog(tBuf);
#endif
			//
			safeTcsnCpy(tBuf, pVc->tStatusBuf, mycountof(pVc->tStatusBuf));

			//
			safeTcsnCpy(result.tUsrName, pVc->usrLogin.tUsrName, mycountof(pVc->usrLogin.tUsrName));

			//
			pVc->usrLogin.bGot_ca_cliUsrDataResp = true;

			//
			break;
		}
		//
		continue;
	}



	//
	iErr = 0;

	//
errLabel:

	//
	closeTool_ca(&pVc->toolCa);

	//
	qyDelRegCfgT(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_req);
	qyDelRegCfgT(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp);
	qyDelRegCfgT(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp_chkUsrKey);
	qyDelRegCfgT(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp_pinRetryCount);

	//
#ifdef  __DEBUG__
	//
	DWORD  dwTickCnt_end = myGetTickCount(mynull);
	int  nElapseInMs = dwTickCnt_end - dwTickCnt_start;
	_sntprintf(tBuf, mycountof(tBuf), _T("tmpThreadProc_ca_usr leaves, nElapseInMs %dms"), nElapseInMs);
	if (bDbg) {
		traceLog(tBuf);
	}
	//
#endif
	//
	//_sntprintf(pVc->tStatusBuf, mycountof(pVc->tStatusBuf), _T("%s. 结束"), pVc->tStatusBuf);

	//
	return  0;
}



//
int smUsrLogin_onTimer(HWND  hDlgLogin, DLG_mcClientLogon_var* pm_var, Ctx_sm* pCtxSm, bool& bNeedShowLogon, bool& bNeedClose, int terminal_type)
{
	int  iErr = -1;
	CCtxQmc* pProcInfo = (CCtxQmc*)QY_GET_procInfo_isCli();

	if (!pm_var || !pCtxSm)  return  -1;
	//
	DLG_mcClientLogon_var& m_var = *pm_var;
	//
	SmUsrLoginVar& m_usrVar = pm_var->m_smUsrLoginVar;
	Var_ca_usr_qmc* pVc = &pCtxSm->ca_usr;
	int  iDiffInMs;
	DWORD  dwThreadDaemonId;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt)  return  -1;

	//
	unsigned  int  uiTickCnt = myGetTickCount(nullptr);
	//
	waitForObject(&m_usrVar.m_hThread_ca, 0);

	//
	if (!m_usrVar.m_hThread_ca) {
		pVc->bTryToChkUsrKey = false;
	}

	//
	if (!m_var.m_bStartToUsrLogin) {
		if (!m_usrVar.m_hThread_ca) {

			//int i
			iDiffInMs = uiTickCnt - pVc->dwTickCnt_lastChkUsrKey;
			if (abs(iDiffInMs) > 2000) {
				//
				pVc->bTryToChkUsrKey = true;
				//  启动检测key
				m_usrVar.m_hThread_ca = CreateThread(NULL, 0, tmpThreadProc_ca_usr, 0, CREATE_SUSPENDED, &dwThreadDaemonId);
				if (!m_usrVar.m_hThread_ca)  goto  errLabel;
				//gBuf_rtspCliHelp.dwThreadId_spl = dwThreadDaemonId;
				if (ResumeThread(m_usrVar.m_hThread_ca) == -1)  goto  errLabel;

			}

		}
	}


	if (m_var.m_bStartToUsrLogin) {
		if (!m_usrVar.m_hThread_ca) {

			iDiffInMs = uiTickCnt - m_var.dwTickCnt_startToUsrLogin;
			if (abs(iDiffInMs) > 60000
				|| pVc->usrLogin.bFailed_getUsrName)
			{
				//
				showInfo_open0(0, 0, _T("user login failed"));
				if (pVc->usrLogin.bFailed_getUsrName) {
					
					if (pVc->usrLogin.iPinRetryCount == 0) {
						safeTcsnCpy(_T("登录失败，密码错误次数过多，UKEY已锁定，请联系管理员"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
						//
						TCHAR	tStatusLog[128];

						_sntprintf(tStatusLog, mycountof(tStatusLog), _T("终端名: %s, 登录失败，密码错误次数过多，UKEY已锁定，请联系管理员"), pProcInfo->av.confLayout.login_termialName);

						qmcLogForHg(0, (wchar_t*)tStatusLog, false);


					}
					else {
						//_sntprintf(pVc->tStatusBuf, mycountof(pVc->tStatusBuf), _T("登录失败，可能密码错误, 还可尝试%d次"), pVc->usrLogin.iPinRetryCount);

						TCHAR	tStatusLog[128]; tStatusLog[0] = 0;

						//_sntprintf(tStatusLog, mycountof(tStatusLog), _T("终端名: %s, 登录失败，可能密码错误, 还可尝试%d次"), pProcInfo->av.confLayout.login_termialName, pVc->usrLogin.iPinRetryCount);

						qmcLogForHg(0, (wchar_t*)tStatusLog, false);
					}
					
				}
				else {
					safeTcsnCpy(_T("用户登录失败"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
				}
				qmcLogStatus(_T("usrLogin"), 0, pVc->tStatusBuf);
#ifdef  __DEBUG__
				traceLog((TCHAR*)_T("user login failed, to clear usrLogin"));
#endif

				//
				m_var.m_bStartToUsrLogin = false;
				memset(&pVc->usrLogin, 0, sizeof(pVc->usrLogin));
				//
#if  0
				ui->loginUserBtn->setEnabled(true);
				ui->loginUserBtn->setText(u8"登录");
#endif
				bNeedShowLogon = true;
				//
				iErr = 0;  goto  errLabel;
			}

			//
			if (!pVc->bExists_usrKey
				|| pVc->usrLogin.bGot_ca_cliUsrDataResp)
			{
				// send usrInfo to manangerment.

				if (!pVc->usrLogin.bSent_cliUsrData) {
					pVc->usrLogin.bSent_cliUsrData = true;

					//
					//safeTcsnCpy(_T("发送用户信息到服务器"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
					safeTcsnCpy(_T("snd usrInfo to server"), pVc->tStatusBuf, mycountof(pVc->tStatusBuf));
#ifdef  __DEBUG__
					traceLog(pVc->tStatusBuf);
#endif

					//
					MACRO_prepareForTran();
					QIS_ca_req  req;

					//
					memset(&req, 0, sizeof(req));
					req.uiType = CONST_imCommType_qisCaReq;


					//
					int usrType = 0;
					char  buf_usr[128] = "";
					char  buf_passwd[128] = "";

					if (pVc->bExists_usrKey) {
						usrType = CONST_hgUsrType_key;
						myTChar2Utf8(pVc->usrLogin.tUsrName, buf_usr, mycountof(buf_usr));
					}
					else {
						usrType = CONST_hgUsrType_name;
						myTChar2Utf8(pVc->usrLogin.loginUsingName.tUsrName, buf_usr, mycountof(buf_usr));
						safeStrnCpy(pVc->usrLogin.loginUsingName.passwd, buf_passwd, mycountof(buf_passwd));
					}

					//
					req.sHgCmd = CONST_hgCmd_usrLogin;

					//
					char buf_usrType[10];
					safeStrnCpy(_ltoa(usrType, buf_usrType, 10), buf_usrType, mycountof(buf_usrType));


					char buf_terminalType[10];
					safeStrnCpy(_ltoa(terminal_type, buf_terminalType, 10), buf_terminalType, mycountof(buf_terminalType));

					//  用户名+密码送到会管服务器
					_snprintf(req.ca_cliData, mycountof(req.ca_cliData), "[cmd=%d] [obj=%d len=%d]%s [obj=%d len=%d]%s [obj=%d len=%d]%s [obj=%d len=%d]%s",
						req.sHgCmd,
						CONST_hgType_usrType, strlen(buf_usrType), buf_usrType,
						CONST_hgType_usrName, strlen(buf_usr), buf_usr,
						CONST_hgType_passwd, strlen(buf_passwd), buf_passwd,
						CONST_hgType_terminal_type, strlen(buf_terminalType), buf_terminalType);
					//
#ifdef  __DEBUG__
#endif

						//
					req.ca_cliDataLen = strlen(req.ca_cliData);

					//
					int len = sizeof(req);
					pProcInfo->postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_ca, tStartTran, uiTranNo, 0, (char*)&req, len, NULL, 0, 0, NULL, FALSE);

					//
					iErr = 0;  goto  errLabel;
				}


				//
				if (pVc->usrLogin.bDone) {  //  收到会管系统的确认，用户信息已经发送给会管系统了，就可以关闭此窗口

					//
					//ui->loginUserBtn->setEnabled(true);
					//ui->loginUserBtn->setText(u8"登录");
#ifdef  __DEBUG__
					traceLog((TCHAR*)_T("用户登录完成了,关闭窗口"));
#endif


					//	
					pCtxSm->usrLogin_sm.bUsrLogined = true;

					//
					pCtxSm->usrLogin_sm.loginState.bExists_usrKey = pVc->bExists_usrKey;

					//
					//this->close();
					//closeWnd_qt(this, _T("CUserLogin.login ok"));

					bNeedClose = true;

					//


					//
					iErr = 0;  goto errLabel;

				}

				//
				if (pVc->usrLogin.iRc) {
					//
					m_var.m_bStartToUsrLogin = false;
					//
					iErr = 0;  goto  errLabel;

				}

				//
				if (pVc->usrLogin.iRc) {
					//
					m_var.m_bStartToUsrLogin = false;
					//
#if 0
					ui->loginUserBtn->setEnabled(true);
					ui->loginUserBtn->setText(u8"登录");
#endif
					bNeedShowLogon = true;

					//
					iErr = 0;  goto  errLabel;

				}

			}
			//
		}


		//
		if (pVc->bExists_usrKey) {

			if (!pVc->usrLogin.bGot_ca_cliUsrDataResp) {

				if (!m_usrVar.m_hThread_ca) {
					m_usrVar.m_hThread_ca = CreateThread(NULL, 0, tmpThreadProc_ca_usr, 0, CREATE_SUSPENDED, &dwThreadDaemonId);
					if (!m_usrVar.m_hThread_ca)  goto  errLabel;
					//gBuf_rtspCliHelp.dwThreadId_spl = dwThreadDaemonId;
					if (ResumeThread(m_usrVar.m_hThread_ca) == -1)  goto  errLabel;

				}
			}
		}
	}

	iErr = 0;

errLabel:
	return  iErr;
}
