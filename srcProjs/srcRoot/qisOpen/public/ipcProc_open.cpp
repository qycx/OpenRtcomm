
#include "stdafx.h"

#include	"ipcProc_open.h"
#include <tmpDefs_open.h>
#include <qytcharcommproc.h>
#include <myCmdParams_open.h>
#include <showInfo_open.h>





//
//
int  createTool_ipcProc(LPCTSTR  installDir, int iNvrType, char  *  ip,  TCHAR  *  tUsr,  char  *  passwd,  int tn, 
	LPCTSTR  who_showInfo, LPCTSTR  logFile, IpcProcTool* pToolCa, int log, int ipcType)
{
	int			iErr = -1;

	//
	//Var_ca* pVc = &pProcInfo->m_var.ca;
	IpcProcTool* pTc = pToolCa;
	TCHAR  tBuf[128];

	//
	if (!who_showInfo) who_showInfo = _T("");




	// 
	//
	STARTUPINFO				si;
	PROCESS_INFORMATION		pi;
	BOOL						bProcessCreated = FALSE;
	TCHAR						tmpExeName[MAX_PATH + 1] = _T("");

	if (pTc->hProcess_ipcProc)  return  0;

	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));

	//
	//traceLogA((char*)"Now start qwm ");

	//
	do {

		//
		memset(&si, 0, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
#if  0
		si.dwFlags = STARTF_USESHOWWINDOW;	//
		si.wShowWindow = SW_HIDE;
#endif
		si.dwFlags = STARTF_FORCEOFFFEEDBACK;

		//
#if 1 //def  _DEBUG
	#define  CONST_subDir_thirdPartyIpcProc_dh		_T(  "bin2019\\"  )
#else
	#define  CONST_subDir_thirdPartyIpcProc_dh		_T(  "thirdParty\\ipcProc\\dh\\"  )
#endif

#define  CONST_subDir_thirdPartyIpcProc_hik		_T(  "thirdParty\\hik\\"  )
#define  CONST_subDir_thirdPartyIpcProc_hik_sub		_T(  "hik\\"  )

		//
		switch (iNvrType) {
		case  CONST_iNvrType_dh:
			_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s%s%s"), installDir, CONST_subDir_thirdPartyIpcProc_dh, _T("dh2019.exe"));
			break;
		case  CONST_iNvrType_dhListIp:
			_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s%s%s"), installDir, CONST_subDir_thirdPartyIpcProc_dh, _T("dhListIp2019.exe"));
			break;
		case  CONST_iNvrType_dhDeviceControl:
			_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s%s%s"), installDir, CONST_subDir_thirdPartyIpcProc_dh, _T("DeviceControlAndTimeSynchronization.exe"));
			break;
		case  CONST_iNvrType_dhPtz:
			_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s%s%s"), installDir, CONST_subDir_thirdPartyIpcProc_dh, _T("RealPlayAndPTZControl.exe"));
			break;
		case  CONST_iNvrType_d4k:
			_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s%s%s"), installDir, CONST_subDir_thirdPartyIpcProc_dh, _T("d4k.exe"));
			break;
		case  CONST_iNvrType_d4kListIp:
			_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s%s%s"), installDir, CONST_subDir_thirdPartyIpcProc_dh, _T("d4kListIp.exe"));
			break;
		case  CONST_iNvrType_d4kDeviceControl:
			_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s%s%s"), installDir, CONST_subDir_thirdPartyIpcProc_dh, _T("d4kDeviceControl.exe"));
			break;
		case  CONST_iNvrType_hik:
			_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s%s%s"), installDir, CONST_subDir_thirdPartyIpcProc_hik, _T("hik.exe"));
			break;
		case  CONST_iNvrType_hikListIp:
			_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s%s%s"), installDir, CONST_subDir_thirdPartyIpcProc_hik_sub, _T("hikListIp.exe"));
			break;
		case  CONST_iNvrType_hikDeviceControl:
			_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s%s%s"), installDir, CONST_subDir_thirdPartyIpcProc_hik_sub, _T("hikDeviceControlAndTimeSynchronization.exe"));
			break;
		case  CONST_iNvrType_hikPtz:
			_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s%s%s"), installDir, CONST_subDir_thirdPartyIpcProc_hik_sub, _T("hikRealPlayAndPTZControl.exe"));
			break;
			//
		case  CONST_iNvrType_hk3ddw:
			_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s%s%s"), installDir, CONST_subDir_thirdPartyIpcProc_hik_sub, _T("hk3ddw.exe"));
			break;

		default:
			goto  errLabel;
		}

		//
		if (tQyQuoteFileName(tmpExeName, mycountof(tmpExeName)))  goto  errLabel;

		//		
		//-ip = 10.0.1.169 - usr = admin - pwd = test, 234

		//
		if (ip) {
			_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s -%s%S"), tmpExeName,
				CONST_qmCmdLine_ip, ip
			);
		}
		if (tUsr) {
			_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s -%s%s"), tmpExeName,
				CONST_qmCmdLine_usr, tUsr
			);
		}
		if (passwd) {
			_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s -%s%S"), tmpExeName,
				CONST_qmCmdLine_pwd, passwd
			);
		}
		//
		_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s -%s%d"), tmpExeName,
			CONST_qmCmdLine_tn, tn
		);

        
		_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s -%s%d"), tmpExeName,
			CONST_qmCmdLine_log, log
		);

		_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s -%s%d"), tmpExeName,
			CONST_qmCmdLine_devType, ipcType
		);
		


		//
#if 0
		_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s -%s%s"), tmpExeName,
			CONST_qmCmdLine_who_showInfo, who_showInfo
		);
		_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s -%s%s"), tmpExeName, CONST_qmCmdLine_log, logFile);
#endif

		//
		int  ii = 0;



		//
		DWORD  dwCreationFlags = CREATE_NO_WINDOW;
		       //dwCreationFlags = 0;
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
		_sntprintf(tBuf, mycountof(tBuf), _T("CreateTool_ipc succeeded,  new processId is %d"), pi.dwProcessId);
		showInfo_open0(0, 0, tBuf);
		//qyShowInfo(pQyMc->pShowInfoStruct, CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("create %s ok"), tmpExeName);
#endif

		//
		iErr = 0;

	} while (false);


errLabel:

	if (bProcessCreated) {
		if (pi.hThread) { CloseHandle(pi.hThread);  pi.hThread = NULL; }
		if (pi.hProcess) {
			pTc->hProcess_ipcProc = pi.hProcess;
			pTc->dwProcessId_ipcProc = pi.dwProcessId;
		}
	}

	if (iErr) {
		//qyShowInfo(pQyMc->pShowInfoStruct, CONST_qyShowType_qwmComm, 0, (char*)"", _T("IsClient"), 0, _T(""), _T(""), _T("createRtspCliHelp failed, %s"), tmpExeName);
	}

	return  iErr;

}


int  closeTool_ipcProc(IpcProcTool* pToolCa)
{
	int  iErr = -1;
	//
	//CCtxQyMc* pQyMc = g_pQyMc;
	//CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();//  QY_GET_procInfo_isCli(  );
	DWORD  dwRet;
	//
	int  i;

	IpcProcTool* pTc = pToolCa;

	//
#if  1  //def  __DEBUG__
	if (pTc->hProcess_ipcProc) {
		TCHAR  tBuf[128];

		DWORD  dwProcessId = 0;
		dwProcessId = pTc->dwProcessId_ipcProc;

		_sntprintf(tBuf, mycountof(tBuf), _T("closeTool_ca: processId %d"), dwProcessId);
		showInfo_open0(0, 0, tBuf);
	}
#endif


	//
	if (!pTc->hProcess_ipcProc)  return  0;

	//
	TerminateProcess(pTc->hProcess_ipcProc, -1);

	//	
	for (i = 0; i < 30; i++) {
		//
		//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T("closeRtspCliHelp:"), _T(""), _T("askRtspCliToQuit,  %d"), i);
		//
		//askRtspCliToQuit(pRtsp);
		//
		dwRet = WaitForSingleObject(pTc->hProcess_ipcProc, 1000);
		if (dwRet != WAIT_FAILED && dwRet != WAIT_TIMEOUT) {
			CloseHandle(pTc->hProcess_ipcProc);  pTc->hProcess_ipcProc = NULL;
			break;
		}
		if (i >= 3) {
			//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T("closeRtspCliHelp:"), _T(""), _T("too long to wait, terminate rtspCli"));
			TerminateProcess(pTc->hProcess_ipcProc, -1);
		}
	}

	//	
	if (pTc->hProcess_ipcProc) {	//  即使没回收，也要关闭了
#ifdef  __DEBUG__
		//myMessageBox(NULL, _T("即使没回收，也要关闭了. 这里没做好，应该rtspCli赶紧退出的"), 0, 0);
#endif
		//
		CloseHandle(pTc->hProcess_ipcProc);  pTc->hProcess_ipcProc = NULL;
	}

	iErr = 0;

errLabel:

	return  iErr;
}


