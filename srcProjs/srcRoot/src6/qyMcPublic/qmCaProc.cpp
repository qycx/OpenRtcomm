

#include	"stdafx.h"

#include	<windowsx.h>
#include	<winsock2.h>
#include	<vfw.h>
#include	<tchar.h>


#include	"qmCommon.h"
#include	"qmCaProc.h"
#include <myCmdParams_open.h>
#include <tmpRegFunc_open.h>


//
//#define		CONST_str_devPrefix			_T("管理员4470")
//#define		CONST_str_devPrefix			_T("管理员")
//#define		CONST_str_devPrefix			_T("个人测试")
#define		CONST_str_devPrefix1			_T("dev")

//_T("个人测试3")
//_T("个人测试9")



//
//  bDev:	1 used as devKey
//			0 used as userKey
//
int  createTool_ca(LPCTSTR  installDir,  int caToolType,  LPCTSTR  who_showInfo,  int iCmd, bool bSys, TCHAR  *  devPrefix,  bool bDev,  bool  bFullCmp,  char  *  caServIp,  int caServPort,  char  *  pwd,  LPCTSTR  logFile,  Tool_ca * pToolCa)
{
	int			iErr = -1;

	//
	//Var_ca* pVc = &pProcInfo->m_var.ca;
	Tool_ca* pTc = pToolCa;
	TCHAR  tBuf[128];

	//
	if (!who_showInfo) who_showInfo = _T("");

	//
	if (!devPrefix || !devPrefix[0])  devPrefix = (TCHAR*)CONST_str_devPrefix1;


	//
	if (pTc->m_bDisableCa) {
		showInfo_open0(0, 0, _T("createTool_ca failed, bDisableCa is true"));
		return  -1;
	}


	// 
	//
	STARTUPINFO				si;
	PROCESS_INFORMATION		pi;
	BOOL						bProcessCreated = FALSE;
	TCHAR						tmpExeName[MAX_PATH + 1] = _T("");

	if (pTc->hProcess_ca)  return  0;

	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));

	//
	//traceLogA((char*)"Now start qwm ");

	//
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
#if  0
	si.dwFlags = STARTF_USESHOWWINDOW;	//
	si.wShowWindow = SW_HIDE;
#endif
	si.dwFlags = STARTF_FORCEOFFFEEDBACK;

#define  CONST_subDir_thirdPartyBjca	_T(  "thirdParty\\bjca\\"  )
#define  CONST_subDir_thirdPartyJdzy	_T(  "thirdParty\\jdzy\\"  )

	//
	switch (caToolType) {
			case  CONST_caToolType_bjca:
				  _sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s%s%s"), installDir, CONST_subDir_thirdPartyBjca, _T(  "bjca.exe"));
				  break;
			case  CONST_caToolType_bjca1:
				  _sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s%s%s"), installDir, CONST_subDir_thirdPartyBjca, _T("bjca1.exe"));
				  break;
			case  CONST_caToolType_jdzyServ:
				  _sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s%s%s"), installDir, CONST_subDir_thirdPartyJdzy, _T("jdzyServ.exe"));
				  break;
			case  CONST_caToolType_jdzyCli:
				  _sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s%s%s"), installDir, CONST_subDir_thirdPartyJdzy, _T("jdzy.exe"));
				  break;
			case  CONST_caToolType_jdzyCli_sx:
				_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s%s%s"), installDir, CONST_subDir_thirdPartyJdzy, _T("jdzy_sx.exe"));
				break;
			default:
				goto  errLabel;				
	}

	//
	if (tQyQuoteFileName(tmpExeName, mycountof(tmpExeName)))  goto  errLabel;


	//
	TCHAR* cmdLine_devPrefix;cmdLine_devPrefix = (TCHAR*)CONST_qmCmdLine_devPrefix;
	if (bFullCmp)cmdLine_devPrefix = (TCHAR*)CONST_qmCmdLine_devName;
	//
	_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s -%s%d -%s%d -%s%d -%s%s -%s%d -%s%s"), tmpExeName, (CONST_qmCmdLine_ca), iCmd, 
																							(CONST_qmCmdLine_tn), pTc->tn_process_ca,
																							CONST_qmCmdLine_sys, bSys  ?  1  :  0,
																							cmdLine_devPrefix, devPrefix,
																							CONST_qmCmdLine_dev,  bDev  ?  1  :  0,
																							CONST_qmCmdLine_who_showInfo,  who_showInfo
																						);
	if (bIpValid(caServIp)) {
		_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s -%s%S -%s%d"), tmpExeName, CONST_qmCmdLine_caServ, caServIp,  CONST_qmCmdLine_caPort,  caServPort  );
	}
	if (pwd  &&  pwd[0]) {
		_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s -%s%S"), tmpExeName, CONST_qmCmdLine_pwd, pwd);
	}
	_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s -%s%s"), tmpExeName, CONST_qmCmdLine_log, logFile);

	//
	int  ii;ii = 0;



	//
	DWORD  dwCreationFlags;dwCreationFlags = CREATE_NO_WINDOW;
#if 0
	QMC_debugStatusInfo* pCfg_debugStatusInfo = pProcInfo->get_qmc_debugStatusInfo();
	if (pCfg_debugStatusInfo
		&& pCfg_debugStatusInfo->ucbShowRtspCliControl)
	{
		dwCreationFlags = 0;
	}
#endif
	//
	if (!CreateProcess(NULL, tmpExeName, NULL, NULL, 0, dwCreationFlags, NULL, NULL, &si, &pi)) {
		_sntprintf(tBuf, mycountof(tBuf), _T("createProcess failed, [%s]"), tmpExeName);
		showInfo_open0(0, 0, tBuf);
		goto  errLabel;
	}
	bProcessCreated = TRUE;

#if  1//def  __DEBUG__
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "CreateTool_ca succeeded,  new processId is %d, tn %d"  ),  pi.dwProcessId,  pTc->tn_process_ca);
	showInfo_open0(  0,  0,  tBuf  );
	//qyShowInfo(pQyMc->pShowInfoStruct, CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("create %s ok"), tmpExeName);
#endif


	//
	iErr = 0;

errLabel:

	if (bProcessCreated) {
		if (pi.hThread) { CloseHandle(pi.hThread);  pi.hThread = NULL; }
		if (pi.hProcess) {
			pTc->hProcess_ca = pi.hProcess;
			pTc->dwProcessId_ca  =  pi.dwProcessId;
		}
	}

	if (iErr) {
		//qyShowInfo(pQyMc->pShowInfoStruct, CONST_qyShowType_qwmComm, 0, (char*)"", _T("IsClient"), 0, _T(""), _T(""), _T("createRtspCliHelp failed, %s"), tmpExeName);
	}

	return  iErr;

}


int  closeTool_ca(Tool_ca * pToolCa)
{
	int  iErr = -1;
	//
	//CCtxQyMc* pQyMc = g_pQyMc;
	//CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();//  QY_GET_procInfo_isCli(  );
	DWORD  dwRet;
	//
	int  i;

	Tool_ca* pTc = pToolCa;

	//
#if  1  //def  __DEBUG__
	if (pTc->hProcess_ca) {
		TCHAR  tBuf[128];

		DWORD  dwProcessId = 0;
		dwProcessId = pTc->dwProcessId_ca;

		_sntprintf(tBuf, mycountof(tBuf), _T("closeTool_ca: processId %d"), dwProcessId);
		showInfo_open0(0, 0, tBuf);
	}
#endif


	//
	if (!pTc->hProcess_ca)  return  0;

	//
	TerminateProcess(pTc->hProcess_ca, -1);

	//	
	for (i = 0; i < 30; i++) {
		//
		//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T("closeRtspCliHelp:"), _T(""), _T("askRtspCliToQuit,  %d"), i);
		//
		//askRtspCliToQuit(pRtsp);
		//
		dwRet = WaitForSingleObject(pTc->hProcess_ca, 1000);
		if (dwRet != WAIT_FAILED && dwRet != WAIT_TIMEOUT) {
			CloseHandle(pTc->hProcess_ca);  pTc->hProcess_ca = NULL;
			break;
		}
		if (i >= 3) {
			//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T("closeRtspCliHelp:"), _T(""), _T("too long to wait, terminate rtspCli"));
			TerminateProcess(pTc->hProcess_ca, -1);
		}
	}

	//	
	if (pTc->hProcess_ca) {	//  即使没回收，也要关闭了
#ifdef  __DEBUG__
		//myMessageBox(NULL, _T("即使没回收，也要关闭了. 这里没做好，应该rtspCli赶紧退出的"), 0, 0);
#endif
		//
		CloseHandle(pTc->hProcess_ca);  pTc->hProcess_ca = NULL;
	}

	iErr = 0;

errLabel:

	return  iErr;
}




//
//
//
int  parse_sendDataResp(  char  *  resp,  TMP_caTool_result  *  pResult  )
{
	int  iErr  =  -1;
	char  *  p;
	char  *  sym;

	//
	if (!pResult)  return  -1;
	memset(pResult, 0, sizeof(pResult[0]));

	//
	sym = (char*)CONST_sym_bExists_usrKey;
	p = strstr(resp, sym);
	if (p) {
		p += strlen(sym);

		pResult->bExists_usrKey = atol(p);
	}


	//
	sym  =  (char*)CONST_sym_usr;
	p  =  strstr(resp,sym);
	if (p) {
		p += strlen(sym);

		char  buf[1024];
		safeStrnCpy(p, buf, mycountof(buf));
		myUtf82TChar(buf, pResult->tUsrName, mycountof(pResult->tUsrName));
	}

	//
	iErr  =  0;
	//
	errLabel:
	//
	return  iErr;
}

//
//int  qmd_getCaServCfg(int caToolType, char* caGwIp, int sizeof_caGwIp, int* piCaGwPort)
/*
int  qmd_getCaServCfg(int caToolType, char* caGwIp, int sizeof_caGwIp, int* piCaGwPort, char* hgIp, int  sizeof_hgIp, int* piHgPort)
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
		char  tmpHgIp[128]  =  "";
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
		*piCaGwPort = _ttol(pT);

		//
		safeStrnCpy(tmpHgIp, hgIp, sizeof_hgIp);
		*piHgPort = tmpHgPort;

		//
		iErr = 0;
	} while (false);

	//
	return  iErr;
}
*/
