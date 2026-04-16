


#include	"stdafx.h"
#include	<Windows.h>
#include	"qyMcMainCommon.h"
//#include <ctxQmc_sm.h>
#include	"myCmdParams_open.h"
#include	"myTChar.h"
#include	"hgCommProc.h"
#include	"ctxQmc.h"
#include	<time.h>
#include	"qyMsgFunc.h"
#include	"smLoginProc.h"

//



//
int qmcChkDualSystemHotBackup()
{
	int  iErr = -1;

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
	if (!pCtxSm)  return  -1;

	
	//
	int maxWaits = 3;
	bool bDbg = true;
	TCHAR  tBuf[128];

	//
#ifdef  __DEBUG__
		//

#endif


	//
	do {
		//
		DWORD  dwIp  =  0;
		DWORD  dwCurMcuIp = 0;

		dwCurMcuIp = inet_addr(pMisCnt->server.ip);

		//
		//  对没有会管的程序
		if (!pCtxSm->smTerminalInitCfg.terminal_mcu[0]
			&&  !pCtxSm->smTerminalInitCfg.terminal_mcu2[0]  ) 
		{
			//
			break;
		}

		//
		QWM_DYN_CFG dynCfg = { 0 };

		//
		//  如果有dwConfMcuIp，则优先判断dwConfMcuIp
		if (pMisCnt->dualSystem.dwConfMcuIp) {
			if (pMisCnt->dualSystem.dwConfMcuIp == dwCurMcuIp) {
				if (bMisCntOnline(pQyMc, pMisCnt)) {
					// all are ok
					// 
					if (pMisCnt->dualSystem.bStartToFindCorrectMcu)
					{
						pMisCnt->dualSystem.bStartToFindCorrectMcu = false;
					}

					//
					if (bDbg) {
						_sntprintf(tBuf, mycountof(tBuf), _T("dual: all is ok. %S"), pMisCnt->server.ip);
						showInfo_open0(0, 0, tBuf);
					}
					//
					iErr = 0;  break;
				}
				//
			}
		}
		
		//		
		if (!pMisCnt->dualSystem.bStartToFindCorrectMcu) {
			pMisCnt->dualSystem.bStartToFindCorrectMcu = true;
			pMisCnt->dualSystem.nTimes_toWait = 0;

			//
			memset(&pMisCnt->dualSystem.status, 0, sizeof(pMisCnt->dualSystem.status));
		}
		//
#ifdef  __DEBUG__
		if (!isValid_qwmDynCfg(&pMisCnt->dynCfg_suggested.dynCfg)) {
			int  ii = 0;
		}
		else {
			int  ii = 0;
		}
#endif
		//
		pMisCnt->dualSystem.nTimes_toWait++;
		if (pMisCnt->dualSystem.nTimes_toWait > 30) {
			pMisCnt->dualSystem.bStartToFindCorrectMcu = false;
			//
			showInfo_open0(0, 0, _T("too long to wait, retry"));
			iErr = 0;  break;
		}
		if (pMisCnt->dualSystem.dwConfMcuIp) {		//  confMcu不需要bDone, 用dwConfMcuIp是否为0来控制

			if (!pMisCnt->dualSystem.status.confMcu.bInited) {

				memset(&dynCfg, 0, sizeof(dynCfg));
				ulIp2Str(pMisCnt->dualSystem.dwConfMcuIp, dynCfg.cnt.cntIp, mycountof(dynCfg.cnt.cntIp));
				dynCfg.cnt.usCntPort = pMisCnt->cfg.dynCfg.cnt.usCntPort;
				//						
				pMisCnt->dynCfg_suggested.dynCfg = dynCfg;
				memset(&pMisCnt->dynCfg_suggested.helpInfo, 0, sizeof(pMisCnt->dynCfg_suggested.helpInfo));
				//
				pMisCnt->dynCfg_suggested.tn_changed = getuiNextTranNo(0, 0, 0);

				pMisCnt->dualSystem.status.confMcu.bInited = true;
				//
				//
				_sntprintf(tBuf, mycountof(tBuf), _T("dual: set serv_suggest.ip to confMcuIp %S"), dynCfg.cnt.cntIp);
				showInfo_open0(0, 0, tBuf);
			}
			if (!pMisCnt->dynCfg_suggested.helpInfo.bDone) {
				iErr = 0;  break;
			}

			if (pMisCnt->dynCfg_suggested.helpInfo.bFail) {
				//  在dynCfg_suggested.bDone为true,如果还没连通，则confMcu可能是错的。要清零，重新取值
				pMisCnt->dualSystem.dwConfMcuIp = 0;
				//
				showInfo_open0(0, 0, _T("dynCfg_suggested.bDone is true, but not ok, so clear confMcuIp"));
			}
			//
			iErr = 0;  break;
		}
#ifdef  __DEBUG__
		if (!isValid_qwmDynCfg(&pMisCnt->dynCfg_suggested.dynCfg)) {
			int  ii = 0;
		}
#endif

		if  (  pCtxSm->smTerminalInitCfg.terminal_mcu2[0]  )  {
			if (!pMisCnt->dualSystem.status.str2ndMcu.bDone) {
				if (!pMisCnt->dualSystem.status.str2ndMcu.bInited) {

					//
					memset(&dynCfg, 0, sizeof(dynCfg));

					safeStrnCpy(pCtxSm->smTerminalInitCfg.terminal_mcu2, dynCfg.cnt.cntIp, mycountof(dynCfg.cnt.cntIp));
					dynCfg.cnt.usCntPort = pMisCnt->cfg.dynCfg.cnt.usCntPort;
					pMisCnt->dynCfg_suggested.dynCfg = dynCfg;
					//
					memset(&pMisCnt->dynCfg_suggested.helpInfo, 0, sizeof(pMisCnt->dynCfg_suggested.helpInfo));
					//
					pMisCnt->dynCfg_suggested.tn_changed = getuiNextTranNo(0, 0, 0);
					//
					_sntprintf(tBuf, mycountof(tBuf), _T("dual: set serv_suggest.ip to 2ndMcuIp %S"), dynCfg.cnt.cntIp);
					showInfo_open0(0, 0, tBuf);

					//
					pMisCnt->dualSystem.status.str2ndMcu.bInited = true;
				}
				if (!pMisCnt->dynCfg_suggested.helpInfo.bDone) {
					iErr = 0;  break;
				}

				pMisCnt->dualSystem.status.str2ndMcu.bDone = true;

				//
				iErr = 0;  break;
			}
		}
		if (!pMisCnt->dualSystem.status.str1stMcu.bDone) {
			if (!pMisCnt->dualSystem.status.str1stMcu.bInited) {

				//
				memset(&dynCfg, 0, sizeof(dynCfg));
				//dynCfg = pMisCnt->cfg.dynCfg;
				safeStrnCpy(pCtxSm->smTerminalInitCfg.terminal_mcu, dynCfg.cnt.cntIp, mycountof(dynCfg.cnt.cntIp));
				dynCfg.cnt.usCntPort = pMisCnt->cfg.dynCfg.cnt.usCntPort;
				pMisCnt->dynCfg_suggested.dynCfg = dynCfg;
				//
				memset(&pMisCnt->dynCfg_suggested.helpInfo, 0, sizeof(pMisCnt->dynCfg_suggested.helpInfo));
				//
				pMisCnt->dynCfg_suggested.tn_changed = getuiNextTranNo(0, 0, 0);
				//
				_sntprintf(tBuf, mycountof(tBuf), _T("dual: set serv_suggest.ip to 1stMcuIp %S"), dynCfg.cnt.cntIp);
				showInfo_open0(0, 0, tBuf);
				//
				pMisCnt->dualSystem.status.str1stMcu.bInited = true;
			}
			//
			if (!pMisCnt->dynCfg_suggested.helpInfo.bDone) {
				iErr = 0;  break;
			}
			pMisCnt->dualSystem.status.str1stMcu.bDone = true;
			iErr = 0;  break;
		}

		//
#if 0
		showInfo_open0(0, 0, _T("dual: retry"));
		pMisCnt->dualSystem.bStartToFindCorrectMcu = false;
#endif

		//
		iErr = 0;
	} while (false);

	//
#ifdef  __DEBUG__
	if (!isValid_qwmDynCfg(&pMisCnt->dynCfg_suggested.dynCfg)) {
		int  ii = 0;
	}
#endif


	return  iErr;
}

