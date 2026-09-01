
#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#ifdef  __WINCE__
#ifndef  __TEST__
#include	"ceMenuBar.h"
#endif
#endif

#include	"myresource.h"

#include	"DlgMcClientLogon.h"
#include	"DlgQnmCfgOptionsIsClient.h"
#include	"qyCusResTemp.h"

#include	"ctxQmc.h"
#include	"qmcCommFunc_isCli.h"



//int  doMisCntLogon(  MIS_CNT  *  pMisCnt,  MIS_CHANNEL  *  pChannel,  HWND    hDlg,  DLG_mcClientLogon_var  &  m_var  )
int  doMisCntLogon(MIS_CNT* pMisCnt, MIS_CHANNEL* pChannel, HWND    hDlg, TCHAR* respHint, int  cntof_respHint)
{
	int				iErr = -1;
	if (!pMisCnt)  return  -1;
	MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)pMisCnt->pProcInfoParam;
	if (!pProcInfo)  return  -1;
	QY_MC* pQyMc = (QY_MC*)pProcInfo->pQyMc;
	QY_SERVICEGUI_INFO* pSci = (QY_SERVICEGUI_INFO*)pProcInfo->pSgiParam;
	BOOL					bCryptInited = FALSE;
	int						i;
	TCHAR					tBuf[256];

	memset(&pChannel->commEncCtx, 0, sizeof(pChannel->commEncCtx));
	memcpy(&pChannel->commEncCtx.common, &pMisCnt->commEncCtx.common, sizeof(pChannel->commEncCtx.common));
	bool  bMachineKey = bUseMachineKey_qmc(pQyMc);
	if (initCrypt_qmc(pProcInfo, pMisCnt, pProcInfo->cspContainer_qmc, get_DEFAULT_cspProvider(), bMachineKey, (pChannel->uiType == CONST_channelType_talking), &pChannel->commEncCtx))  goto  errLabel;
	bCryptInited = TRUE;
	//

	_sntprintf(pChannel->commEncCtx.mutexName_syncCrypt_e, mycountof(pChannel->commEncCtx.mutexName_syncCrypt_e), _T("qmcCrypt%u-%u-e"), GetCurrentProcessId(), getuiNextTranNo(0, 0, 0));
	//_sntprintf(  pChannel->commEncCtx.mutexName_syncCrypt_d, mycountof(pChannel->commEncCtx.mutexName_syncCrypt_d), _T("qmcCrypt%u-%u-d"), GetCurrentProcessId(), getuiNextTranNo(0, 0, 0));


	//
	pChannel->curServer = pMisCnt->server;

	//
	int  iMaxTriesToStartSession_mis; iMaxTriesToStartSession_mis = CONST_maxTriesToStartSession_mis;
	//
	//iMaxTriesToStartSession_mis = 1;
	//  
	for (i = 0; i < iMaxTriesToStartSession_mis; i++) {

		//  2011/02/02
		pProcInfo->authInfo.uiLogonId = 0;

		//
		_sntprintf(tBuf, mycountof(tBuf), _T("%s %s, %d..."), getResStr(0, &pQyMc->cusRes, CONST_resId_tryToConnect), CQyString(pMisCnt->server.ip), i);
		//m_var.guiData.pf_SetDlgItemText(  hDlg,  m_var.guiData.iIDC_STATIC_hint,  tBuf  );
		//
		if (!tryToStartChannel(pMisCnt, pChannel, respHint, cntof_respHint)) {
			break;
		}

		//
		continue;
	}
	if (i == iMaxTriesToStartSession_mis) {
		//
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T("Logon"), _T(""), _T("failed"));
		//
		goto  errLabel;
	}
	pChannel->status.ulbSessionErr = FALSE;
	//

	iErr = 0;

errLabel:

	pChannel->status.ulbSessionErr = TRUE;	//  此标志位通知recv和snd两线程退出

	if (pChannel->bSessionOpen) {
		//
		traceLogA((char*)"to close session");
		//
		qnmCloseSession_msg(mynull,&pChannel->session, &pChannel->sock, &pQyMc->cfg.to,_T("doMisCntLogon.l90"));
		pChannel->bSessionOpen = FALSE;
		//
		traceLogA((char*)"session closed");

		//
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T("Logon"), _T(""), _T("Session is closed"));

	}
	if (bCryptInited)  exitCrypt_qmc(pProcInfo, pMisCnt, &pChannel->commEncCtx);

	pChannel->status.ulbIoQuit = TRUE;

	return  iErr;
}


