
#include	"stdafx.h"
#include	<mmsystem.h>
#include	"qmOpenCommon.h"
#include	"qyMcMainCommon.h"
#include	"ctxQmc.h"
#include	"ipcProc.h"
#include <myCmdParams_open.h>
#include	"ipcProc_open.h"


//
bool bGetIpcProcInitCfg(TCHAR* cfgFileName, IpcProcInitCfg* pCfg)
{
	bool  iErr = true;
	TCHAR  tBuf[256];
	char  buf[256];

	//
	if (!pCfg)  return  -1;

	//
	memset(pCfg, 0, sizeof(pCfg[0]));


#if 0
	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_sm_terminalIp), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	myTChar2Utf8(tBuf, buf, mycountof(buf));
	safeStrnCpy(buf, pCfg->terminal_ip, mycountof(pCfg->terminal_ip));
	//


#endif

	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_bEnableIpc), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	pCfg->m_bEnableIpc = _ttol(tBuf);

	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_iNvrType), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	pCfg->m_iNvrType = _ttol(tBuf);

    
	if (getCfgValByNameT(cfgFileName, (TCHAR*)(CONST_cfgName_NvrLog), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	pCfg->m_iNvrLog = _ttol(tBuf);
	
	

	//
		//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_nvrIp), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	myTChar2Utf8(tBuf, buf, sizeof(buf));
	safeStrnCpy(buf, pCfg->nvrIp, mycountof(pCfg->nvrIp));

	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_nvrUsr), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	safeTcsnCpy(tBuf, pCfg->nvrUsr, mycountof(pCfg->nvrUsr));

	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_nvrPwd), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	myTChar2Utf8(tBuf, buf, sizeof(buf));
	safeStrnCpy(buf, pCfg->nvrPwd, mycountof(pCfg->nvrPwd));


	//
	iErr = true;
	return  iErr;
}

bool bGetShareProcInitCfg(TCHAR* cfgFileName, ShareProcInitCfg* pCfg)
{
	bool  iErr = true;
	TCHAR  tBuf[256];
	char  buf[256];

	//
	if (!pCfg)  return  -1;

	//
	memset(pCfg, 0, sizeof(pCfg[0]));


#if 0
	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_sm_terminalIp), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	myTChar2Utf8(tBuf, buf, mycountof(buf));
	safeStrnCpy(buf, pCfg->terminal_ip, mycountof(pCfg->terminal_ip));
	//


#endif

	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_bEnableShare), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	pCfg->m_bEnableShare = _ttol(tBuf);

	//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_bAutoShare), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	pCfg->m_bAutoShare = _ttol(tBuf);

	//
		//
	if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_rtspUrl), tBuf, mycountof(tBuf))) {
		tBuf[0] = 0;
	}
	tTrim(tBuf);
	myTChar2Utf8(tBuf, buf, sizeof(buf));
	safeStrnCpy(buf, pCfg->rtspUrl, mycountof(pCfg->rtspUrl));


	//
	iErr = true;
	return  iErr;
}

//
int ipcProc_exit()
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	//
	if (pProcInfo->m_ipcProc.tool.hProcess_ipcProc) {
		showInfo_open0(0, 0, _T("ipcProc_exit, send close msg to dh"));

		//
		OnvifMsg_ping msg = { 0 };
		msg.uiType = CONST_qisMsgType_onvif;
		msg.iSubtype = CONST_onvifMsg_subtype_close;
		//
		qisPipe_writeMsg(&msg, sizeof(msg), pProcInfo->m_ipcProc.pQisPipe);

		//
		waitForObject(&pProcInfo->m_ipcProc.tool.hProcess_ipcProc, 50);
	}
	//
	closeTool_ipcProc(&pProcInfo->m_ipcProc.tool);
	//
	if (pProcInfo->m_ipcProc.pQisPipe) {
		qisPipeFree(&pProcInfo->m_ipcProc.pQisPipe);
	}

	return  0;
}


//

//
int  ipcProc_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
{
	int  iErr = false;
	unsigned  int    dwByte = msgLen;
	//
	//ShareDynBmps_threadProcInfo* pSt = (ShareDynBmps_threadProcInfo*)p0;
	//  p1
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;

	//	
	if (dwByte < sizeof(OnvifMsg_common)) {
		showInfo_open0(0, 0, _T("shareDynBmps_qisPipe_onRead err: read too small bytes < sizeof(  Onvif_msg_common  )"));
		return  -1;
	}
	//
	OnvifMsg_common* pMsgCommon = (OnvifMsg_common*)pMsg;


	if (pMsgCommon->uiType != CONST_qisMsgType_onvif)  return  -1;

	//
	TCHAR  tBuf[128];

	//
	switch  (  pMsgCommon->iSubtype) {
			case  CONST_onvifMsg_subtype_dbg:  {
				  OnvifMsg_dbg* pDbg = (OnvifMsg_dbg*)pMsgCommon;
				  //
				  traceLog((TCHAR*)_T("recvd: %S"), pDbg->buf);
				  //
				  }
				  break;
			case  CONST_onvifMsg_subtype_nvrInfo:
				{
					OnvifMsg_nvrInfo* pOn = (OnvifMsg_nvrInfo*)pMsgCommon;
					
					//
					if (memcmp(&pProcInfo->m_ipcProc.dev.nvrInfo, &pOn->nvrInfo, sizeof(NvrInfo))) {
						pProcInfo->m_ipcProc.dev.nvrInfo = pOn->nvrInfo;
					}
					pProcInfo->m_ipcProc.dev.dwLastTickCnt_nvrInfoGot = myGetTickCount(nullptr);
					//
					pProcInfo->m_ipcProc.dev.cnt_wait = 0;

					//
#ifdef  __DEBUG__
					//pProcInfo->m_ipcProc.op.nvrInfo = pProcInfo->m_ipcProc.dev.nvrInfo;
#endif

					//
#ifdef  __DEBUG__
					if (0) {
						int  i;
						if (!pOn->nvrInfo.usCnt) {
							showInfo_open0(0, 0, _T("app: get nvrInfo, no ipc"));
						}
						for (i = 0; i < pOn->nvrInfo.usCnt; i++) {
							IpcInfo* pMem = &pOn->nvrInfo.mems[i];
							_sntprintf(tBuf, mycountof(tBuf), _T("ipc[%d]: %d, %S, %s"), i, pMem->iChannel, pMem->ip, pMem->name);
							showInfo_open0(0, 0, tBuf);
						}
					}
#endif
		
				}
				  break;
			default:
					break;
				}


	//
#ifdef  __DEBUG__
#if  0
	_sntprintf(tBuf, mycountof(tBuf), _T("shareDynBmps_qisPipe_onRead: unprocessed onvifMsg.subtype %d, onvifMsg"), pMsgCommon->iSubtype);
	showInfo_open0(0, 0, tBuf);
#endif
#endif

#if 0
	//
	if (q2PostMsgAndTrigger(pMsg, msgLen, &pSt->q2, _T("shareDynBmps_qisPipe_onR"))) {
		showInfo_open0(0, 0, _T("shareDynBmps_qisPipe_onRead failed, q2PostMsg failed"));
		goto  errLabel;
	}
#endif

	//
	iErr = true;
errLabel:

	//
	return  iErr;

}

int getNvrType(int type) {
	switch (type) {
	case Nvr_type::Nvr_type_d4k:
		return CONST_iNvrType_d4k;
	case Nvr_type::Nvr_type_hik:
		return CONST_iNvrType_hik;
	default:
		return CONST_iNvrType_dh;
	}

}


//
int mainWnd_chkIpcProc(int loopCtrl)
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc  *  )pQyMc->get_pProcInfo();

	//
	if (!pProcInfo->cfg.ipcProcInitCfg.m_bEnableIpc)  return  -1;

	//
	bool  bNeedFreePipe = false;

	//
	do {

		//
		if (!(loopCtrl % 5)) {


			if (!isHandleValid(pProcInfo->m_ipcProc.tool.hProcess_ipcProc)) {
				pProcInfo->m_ipcProc.tool.hProcess_ipcProc = 0;
			}

			waitForObject(&pProcInfo->m_ipcProc.tool.hProcess_ipcProc, 0);

			//		
			IpcProc* pCtx = &pProcInfo->m_ipcProc;

			//
			if (!pCtx->pQisPipe) {
				//
				bNeedFreePipe = true;

				//
				pCtx->pQisPipe = qisPipeNew();
				//
				if (!pCtx->pQisPipe)  goto  errLabel;
				//
				GENERIC_Q_CFG  qCfg = { 0 };
				TCHAR   pipeName[128] = _T("");
				//
				//
				_sntprintf(qCfg.name, mycountof(qCfg.name), _T("qisPipe"));
				_sntprintf(qCfg.mutexName_prefix, mycountof(qCfg.mutexName_prefix), _T("qiqPipe"));
				qCfg.uiMaxQNodes = CONST_uiMaxQNodes_outputQ_256;

				//		  		  
				M_get_pipeName(CONST_ipcProcPipePrefix, _T(""), CONST_ipcProcPipe_tn, pipeName);

				//
				PARAM_initQisPipe  param = { 0 };
				param.pf_onRead = ipcProc_qisPipe_onRead;
				//param.p0 = pSt;
				//
				if (initQisPipe(&qCfg, pipeName, TRUE, _T("qisPipeStarter"), &param, pCtx->pQisPipe)) {
					goto  errLabel;
				}

				//
				bNeedFreePipe = false;
			}


			//
#if 10
			if (!pProcInfo->m_ipcProc.tool.hProcess_ipcProc) {
				char* nvrIp = pProcInfo->cfg.ipcProcInitCfg.nvrIp;
				TCHAR* nvrUsr = pProcInfo->cfg.ipcProcInitCfg.nvrUsr;
				char* nvrPwd = pProcInfo->cfg.ipcProcInitCfg.nvrPwd;
				int nvrType = pProcInfo->cfg.ipcProcInitCfg.m_iNvrType;
				int nvrLog = pProcInfo->cfg.ipcProcInitCfg.m_iNvrLog;
				int devType = pProcInfo->cfg.ipcProcInitCfg.m_iDevType;

				

				//pProcInfo->m_var.ctxSm.smTerminalInitCfg
				//
				if (createTool_ipcProc(pQyMc->cfg.installDir, getNvrType(nvrType), nvrIp,  nvrUsr, nvrPwd, 0,  _T(""), _T(""),
					& pProcInfo->m_ipcProc.tool, nvrLog, devType)) {
					break;
				}
				//
				pProcInfo->m_ipcProc.dev.cnt_wait = 0;
			}
			//
			int waitTimes = 3;
			if (pProcInfo->cfg.ipcProcInitCfg.m_iNvrType == Nvr_type::Nvr_type_hik)
				waitTimes = 10;
			if (pProcInfo->m_ipcProc.dev.cnt_wait >= waitTimes) {
				closeTool_ipcProc(&pProcInfo->m_ipcProc.tool);
				
			}
#endif


		}

		//
		if (!pProcInfo->m_ipcProc.pQisPipe) {
			break;
		}

		//
		DWORD  dwTickCnt = myGetTickCount(mynull);
		int iDiffInMs = dwTickCnt - pProcInfo->m_ipcProc.dev.dwLastTickCnt_nvrInfoGot;
		if (abs(iDiffInMs)> CONST_intervalInMs_nvrInfo) {
			OnvifMsg_nvrInfo	msg = { 0 };
			msg.uiType = CONST_qisMsgType_onvif;
			msg.iSubtype = CONST_onvifMsg_subtype_nvrInfo;
			//
			qisPipe_writeMsg(&msg, sizeof(msg), pProcInfo->m_ipcProc.pQisPipe);

			//
			pProcInfo->m_ipcProc.dev.cnt_wait++;


		}

		//
		iDiffInMs = dwTickCnt - pProcInfo->m_ipcProc.dwLastTickCnt_ping;
		if (abs(iDiffInMs) > CONST_intervalInMs_ping) {
			pProcInfo->m_ipcProc.dwLastTickCnt_ping = dwTickCnt;
			//
			if (0) {
				showInfo_open0(0, 0, _T("send ping"));
			}
			//
			OnvifMsg_ping msg = { 0 };
			msg.uiType = CONST_qisMsgType_onvif;
			msg.iSubtype = CONST_onvifMsg_subtype_ping;
			//
			qisPipe_writeMsg(&msg, sizeof(msg), pProcInfo->m_ipcProc.pQisPipe);
		}

		//
#ifdef  __DEBUG__
		//
#if 0
		OnvifMsg_dbg msg = { 0 };
		msg.uiType = CONST_qisMsgType_onvif;
		msg.iSubtype = CONST_onvifMsg_subtype_dbg;

		//
		static int iii = 0;
		_snprintf(msg.buf, mycountof(msg.buf), "%d", iii);
		iii++;
		//
		qisPipe_writeMsg(&msg, sizeof(msg), pProcInfo->m_ipcProc.pQisPipe);
#endif
		//
#endif



		//
		iErr = 0;


		//
	} while (false);


	errLabel:

	//
	if (bNeedFreePipe) {
		if (pProcInfo->m_ipcProc.pQisPipe) {
			qisPipeFree(&pProcInfo->m_ipcProc.pQisPipe);
		}
	}

	return  iErr;
}


//
int saveSmIpicInitCfg(IpcProcInitCfg* pCfg, TCHAR* cfgFileName)
{
	int  iErr = -1;
	TCHAR  tBuf[256];
	FILE* fp = _tfopen(cfgFileName, _T("w,ccs=UNICODE"));
	if (!fp) {
		qyDisplayLastError((char*)"");
		goto  errLabel;
	}

	//
	_ftprintf(fp, _T("%S   %S\n"), CONST_cfgName_nvrIp, pCfg->nvrIp);
	_ftprintf(fp, _T("%S   %S\n"), CONST_cfgName_nvrPwd, pCfg->nvrPwd);
	//
	_ftprintf(fp, _T("%S   %s\n"), CONST_cfgName_nvrUsr, pCfg->nvrUsr);

	//
	_ftprintf(fp, _T("%S   %d\n"), CONST_cfgName_iNvrType, (int)pCfg->m_iNvrType);
	_ftprintf(fp, _T("%S   %d\n"), CONST_cfgName_bEnableIpc, (int)pCfg->m_bEnableIpc);




	//setCfgV

	iErr = 0;
errLabel:

	if (fp) {
		fclose(fp);
	}

	return  iErr;
}


int saveSmShareInitCfg(ShareProcInitCfg* pCfg, TCHAR* cfgFileName)
{
	int  iErr = -1;
	TCHAR  tBuf[256];
	FILE* fp = _tfopen(cfgFileName, _T("w,ccs=UNICODE"));
	if (!fp) {
		qyDisplayLastError((char*)"");
		goto  errLabel;
	}

	//
	_ftprintf(fp, _T("%S   %d\n"), CONST_cfgName_bEnableShare, (int)pCfg->m_bEnableShare);
	_ftprintf(fp, _T("%S   %S\n"), CONST_cfgName_rtspUrl, pCfg->rtspUrl);
	_ftprintf(fp, _T("%S   %d\n"), CONST_cfgName_bAutoShare, (int)pCfg->m_bAutoShare);




	//setCfgV

	iErr = 0;
errLabel:

	if (fp) {
		fclose(fp);
	}

	return  iErr;
}

