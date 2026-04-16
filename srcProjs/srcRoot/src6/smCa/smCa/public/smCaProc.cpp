
#include	"stdafx.h"
//
#include	<vfw.h>
#include	<Wincrypt.h>
#include	<WinSock2.h>
#include	<tchar.h>

//
#include	"qmOpenCommon.h"
#include	"qmCommon.h"
#include "qnmCommProc_mis.h"
#include	"qmCaProc.h"
#include <tmpRegFunc_open.h>
#include <myCmdParams_open.h>


//
//int  qmd_getCaServCfg(int caToolType, char* caGwIp, int sizeof_caGwIp, int* piCaGwPort)
__declspec(dllexport) int  qmd_getCaServCfg(int caToolType, char* caGwIp, int sizeof_caGwIp, int* piCaGwPort, char* hgIp, int  sizeof_hgIp, int* piHgPort)
{
	int  iErr = -1;

	do {
		//
		//safeStrnCpy(  (char*)"218.240.128.210",  caGwIp,  sizeof_caGwIp  );
		TCHAR  tBuf[256];
		HKEY hKeyRoot0 = HKEY_LOCAL_MACHINE;
		unsigned  int  uiType = 0;
		unsigned  int  size = sizeof(tBuf);
		//
		char  tmpHgIp[128] = "";
		int  tmpHgPort = 0;

		//
		if (tmpGetRegCfg_open(hKeyRoot0, _T(CONST_qyRootKey_qnmScheduler_mis), _T(CONST_regValName_caGwIp), &uiType, (char*)tBuf, &size)) {
			break;
		}
		//
		TCHAR* pT;
		pT = _tcschr(tBuf, _T(':'));
		if (!pT)  break;
		*pT = 0;  pT++;

		//
		myTChar2Utf8(tBuf, caGwIp, sizeof_caGwIp);

		TCHAR* pTF;
		pTF = _tcschr(pT, _T(';'));
		if (!pTF)  break;
		*pTF = 0;  pTF++;

		*piCaGwPort = _ttol(pT);

		TCHAR* pTHg;
		pTHg = _tcschr(pTF, _T('='));

		if (!pTHg) break;
		pTHg++;


		pT = _tcschr(pTHg, _T(':'));
		if (!pT)  break;
		*pT = 0;  pT++;

		myTChar2Utf8(pTHg, hgIp, sizeof_hgIp);

		*piHgPort = _ttol(pT);

		//
		iErr = 0;
	} while (false);

	//
	return  iErr;
}


//
__declspec(dllexport) int ca_getRandom_jdzy(LPCTSTR  installDir,  LPCTSTR  statusLogFile,  Param_ca_getRandom* pParam, Var_ca_qmd* pVcq)
{
	int  iErr = -1;
	//CQyMcDaemon* pDaemon = g_pDaemon;
	TCHAR			tBuf[256];

	//
	bool	bSys = true;
	bool	bDev = true;

	//
	//pVcq->toolCa.tn_process_ca  =  getuiNextTranNo(0,0,&pDaemon->var.tn0_ca);
	pVcq->toolCa.tn_process_ca = getuiNextTranNo(0, 0, 0);


	//
#ifdef  __DEBUG__
		//_sntprintf(tBuf, mycountof(tBuf), _T("getUsrInfo_ca: sendData [%S]"), pAuthInfo->ca_sendData);
		//showInfo_open0(0, 0, tBuf);
#endif



		//
	HKEY  hKeyRoot0 = HKEY_LOCAL_MACHINE;
	TCHAR* rootKey = (TCHAR*)_T(CONST_rootKey_ca_sys_win32);
	//
	TCHAR  cfgName_req[128] = _T("");
	TCHAR  cfgName_resp[128] = _T("");

	//_sntprintf(cfgName_req, mycountof(cfgName_req), _T("%s%d"), _T(CONST_regValName_ca_sendData_prefix), pVcq->toolCa.tn_process_ca);
	//tmpSetRegCfg_open(hKeyRoot0, rootKey, cfgName_req, REG_BINARY, pAuthInfo->ca_sendData, pAuthInfo->ca_sendDataLen);

	_sntprintf(cfgName_resp, mycountof(cfgName_resp), _T("%s%d"), _T(CONST_regValName_ca_getRandomResp_prefix), pVcq->toolCa.tn_process_ca);
	qyDelRegCfgT(hKeyRoot0, rootKey, cfgName_resp);

	//
	memset(&pVcq->resp, 0, sizeof(pVcq->resp));


	//
	TCHAR* who = (TCHAR*)_T("ca.serv:c.getRandom");
	char  caGwIp[15 + 1] = "";
	int caGwPort = 0;
	char  hgIp[128 + 1] = "";
	int  hgPort = 0;
	if (qmd_getCaServCfg(CONST_caToolType_jdzyServ, caGwIp, mycountof(caGwIp), &caGwPort,  hgIp,  mycountof(hgIp),&hgPort)) {
		showInfo_open0(0, 0, _T("ca_getRandom_jdzy. qmd_getCaServCfg failed"));
		goto  errLabel;
	}
	//
	bool  bFullCmp;bFullCmp = false;
	//
	if (createTool_ca(installDir, CONST_caToolType_jdzyServ, who, CONST_caCmd_getRandom, bSys, nullptr, bDev, bFullCmp, caGwIp, caGwPort, nullptr, statusLogFile, &pVcq->toolCa)) {
		goto  errLabel;
	}

	//
	int  i;
	int  maxCnt; maxCnt = 30;
	for (i = 0; i < maxCnt; i++) {
		waitForObject(&pVcq->toolCa.hProcess_ca, 1000);
		if (!pVcq->toolCa.hProcess_ca) {

			//
			//
			unsigned  int  uiType = 0;
			char  buf[1024];
			unsigned  int  bufLen;
			bufLen = mycountof(buf);
			if (tmpGetRegCfg_open(hKeyRoot0, rootKey, cfgName_resp, &uiType, buf, &bufLen)) {
				showInfo_open0(0, 0, _T("getUsrInfo_ca failed, tmpGetRegCfg_open failed"));
				goto  errLabel;
			}
			if (bufLen >= mycountof(buf) - 1) {
				goto  errLabel;
			}
			buf[bufLen] = 0;

			//
			qyDelRegCfgT(hKeyRoot0, rootKey, cfgName_req);
			qyDelRegCfgT(hKeyRoot0, rootKey, cfgName_resp);

			//
#if  0
			if (parse_sendDataResp(buf, pVcq->resp.tUsrName, mycountof(pVcq->resp.tUsrName))) {
				showInfo_open0(0, 0, _T("getUsrInfo_ca failed, parse_sendDataResp failed"));
				goto  errLabel;
			}
#endif
			//
			if (bufLen > mycountof(pParam->ca_random) - 1) {
				goto  errLabel;
			}
			safeStrnCpy(buf, pParam->ca_random, bufLen + 1);



			//
#ifdef  __DEBUG__
			{

			}
#endif

			//
			break;
		}
		//
		continue;
	}
	if (i == maxCnt) {
		goto  errLabel;
	}


	//
	iErr = 0;
errLabel:

	closeTool_ca(&pVcq->toolCa);

	//
	return  iErr;
}


//
__declspec(dllexport) int getUsrInfo_ca( LPCTSTR  installDir,  LPCTSTR  statusLogFile,  QY_COMM_AUTHINFO_MIS* pAuthInfo, Var_ca_qmd* pVcq)
{
	int  iErr = -1;
	TCHAR			tBuf[256];

	//CQyMcDaemon* pDaemon = g_pDaemon;

	//
	showInfo_open0(0, 0, _T("getUsrInfo_ca enters"));

	//		
	int  iTickCnt_start = myGetTickCount(nullptr);
#if 10

	//
	TCHAR  mutexName[64] = _T("sync_getUsrInfo_ca");
	CQySyncObj  syncObj;
	if (syncObj.sync(mutexName)) {
		showInfo_open0(0, 0, _T("getUsrInfo_ca failed, syncObj.sync failed"));
		return  -1;
	}

	//
	bool	bSys = true;
	bool	bDev = true;

	//
	//pVcq->toolCa.tn_process_ca  =  getuiNextTranNo(0,0,&pDaemon->var.tn0_ca);
	pVcq->toolCa.tn_process_ca = getuiNextTranNo(0, 0, 0);


	//
#ifdef  __DEBUG__
	_sntprintf(tBuf, mycountof(tBuf), _T("getUsrInfo_ca: sendData [%S]"), pAuthInfo->ca_sendData);
	showInfo_open0(0, 0, tBuf);
#endif



	//
	HKEY  hKeyRoot0 = HKEY_LOCAL_MACHINE;
	TCHAR* rootKey = (TCHAR*)_T(CONST_rootKey_ca_sys_win32);
	//
	TCHAR  cfgName_req[128];
	TCHAR  cfgName_resp[128];

	_sntprintf(cfgName_req, mycountof(cfgName_req), _T("%s%d"), _T(CONST_regValName_ca_sendData_prefix), pVcq->toolCa.tn_process_ca);
	tmpSetRegCfg_open(hKeyRoot0, rootKey, cfgName_req, REG_BINARY, pAuthInfo->ca_sendData, pAuthInfo->ca_sendDataLen);

	_sntprintf(cfgName_resp, mycountof(cfgName_resp), _T("%s%d"), _T(CONST_regValName_ca_sendDataResp_prefix), pVcq->toolCa.tn_process_ca);
	qyDelRegCfgT(hKeyRoot0, rootKey, cfgName_resp);

	//
	memset(&pVcq->resp, 0, sizeof(pVcq->resp));


	//
	int caToolType = CONST_caToolType_bjca;
	char  caGwIp[15 + 1] = "218.240.128.210";
	int caGwPort = 0;
	char hgIp[128] = "";
	int hgPort = 0;

	//
	switch (pAuthInfo->usAuthType) {
	case  CONST_authType_jdzy:
		caToolType = CONST_caToolType_jdzyServ;
		break;
	default:
		break;
	}
	TCHAR* who = (TCHAR*)_T("ca.serv:c.auth");
	//
	if (qmd_getCaServCfg(caToolType, caGwIp, mycountof(caGwIp), &caGwPort,hgIp,mycountof(hgIp),&hgPort)) {
		showInfo_open0(0, 0, _T("qmd_getCaServCfg failed"));
		goto  errLabel;
	}
	//
	bool  bFullCmp; bFullCmp = false;
	//
	if (createTool_ca(installDir, caToolType, who, CONST_caCmd_login_auth, bSys, nullptr, bDev, bFullCmp, caGwIp, caGwPort, nullptr, statusLogFile, &pVcq->toolCa)) {
		goto  errLabel;
	}

	//
	int  i;
	int  maxCnt; maxCnt = 30;
	for (i = 0; i < maxCnt; i++) {
		waitForObject(&pVcq->toolCa.hProcess_ca, 1000);
		if (!pVcq->toolCa.hProcess_ca) {

			//
			//
			unsigned  int  uiType = 0;
			char  buf[4096];
			unsigned  int  bufLen;
			bufLen = mycountof(buf);
			if (tmpGetRegCfg_open(hKeyRoot0, rootKey, cfgName_resp, &uiType, buf, &bufLen)) {
				_sntprintf(tBuf, mycountof(tBuf), _T("getUsrInfo_ca failed, tmpGetRegCfg_open %s failed"), cfgName_resp);
				showInfo_open0(0, 0, tBuf);
				goto  errLabel;
			}
			if (bufLen >= mycountof(buf) - 1) {
				showInfo_open0(0, 0, _T("getUsrInfo_ca failed, bufLen too big"));
				goto  errLabel;
			}
			buf[bufLen] = 0;

			//
			qyDelRegCfgT(hKeyRoot0, rootKey, cfgName_req);
			qyDelRegCfgT(hKeyRoot0, rootKey, cfgName_resp);

			//
			TMP_caTool_result  result;
			memset(&result, 0, sizeof(result));
			if (parse_sendDataResp(buf, &result)) {
				showInfo_open0(0, 0, _T("getUsrInfo_ca failed, parse_sendDataResp failed"));
				goto  errLabel;
			}
			safeTcsnCpy(result.tUsrName, pVcq->resp.tUsrName, mycountof(pVcq->resp.tUsrName));



			//
#ifdef  __DEBUG__
			TCHAR  tBuf[128];
			TCHAR  tUsr[128];
			safeTcsnCpy(pVcq->resp.tUsrName, tUsr, mycountof(tUsr));
			//
			int n = lstrlen(tUsr);
			if (n > 100) {
				int  ii = 0;
			}
			_sntprintf(tBuf, mycountof(tBuf), _T("getUsrInfo: n%d, Äãmm[%s]ºÃjj"), n, tUsr);
			showInfo_open0(0, 0, tBuf);
#endif

			//


			//
			break;
		}
		//
		continue;
	}
	if (i == maxCnt) {
		goto  errLabel;
	}

#endif

	//
	iErr = 0;
errLabel:

	closeTool_ca(&pVcq->toolCa);

	//
	int  iTickCnt_end = myGetTickCount(nullptr);
	int  iDiffInMs = iTickCnt_end - iTickCnt_start;
	_sntprintf(tBuf, mycountof(tBuf), _T("getUsrInfo_ca leaves with %s, %dms"), iErr ? _T("failed") : _T("ok"), iDiffInMs);
	showInfo_open0(0, 0, tBuf);


	//
	return  iErr;
}




