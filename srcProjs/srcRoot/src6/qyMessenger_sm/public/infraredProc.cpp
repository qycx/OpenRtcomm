

#include	"stdafx.h"

#include	<qstring.h>

#define  __noDbg_new__

#include	"qyMcMainCommon_qt.h"
#include	"ctxQmc_sm.h"
#include <qyComPortEx.h>

//
#define		CONST_regRootKey_infrared			"HARDWARE\\DEVICEMAP\\SERIALCOMM"
#define		CONST_regValName_infrared_prefix	 "\\Device\\USBSER00"  //"\\Device\\Serial"

//
int  initCom_infrared(COM_PORT_cfg* pCfg, CComPortEx** ppPort);
void  exitCom_infrared(CComPortEx** ppPort);


//
int startInfraredThread()
{
	int  iErr = -1;

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
	TCHAR  tBuf[128];
	TCHAR	tReg[128];
	TCHAR  tVal[128];
	int  i;

	//
	int dwThreadId = GetCurrentThreadId();
#ifdef  __DEBUG__
	assert(dwThreadId == pQyMc->gui.ctx_gui_thread.dwThreadId9);
#endif


	//pProcInfo->m_var.
	int maxNum = 10;
	for (i = 0; i < maxNum; i++) {
		_sntprintf(tReg, mycountof(tReg), _T("%s%d"), _T(  CONST_regValName_infrared_prefix  ), i);
		if (qyGetRegCfgT(HKEY_LOCAL_MACHINE, _T(CONST_regRootKey_infrared), tReg, (char*)tVal, sizeof(tVal), mynull) == 0) {
			safeTcsnCpy(tVal, pProcInfo->m_var.comName, mycountof(pProcInfo->m_var.comName));
			break;
		}
	}
	if (i == maxNum) {
		goto  errLabel;
	}

	//
	COM_PORT_cfg  cfg;
	memset(&cfg, 0, sizeof(cfg));
	//cfg.
	//BOOL					bInitPort(HWND  hPortOwner, UINT  portNo = 1, UINT  baud = 19200, char  parity = NOPARITY, UINT  databits = 8, UINT  stopsbits = ONESTOPBIT, DWORD  dwCommEvents = EV_RXCHAR | EV_CTS, UINT  nBufferSize = 512, int  iComPortType = 0, int  iUsrData = 0);
	TCHAR* pT;
	TCHAR* comNamePrefix; comNamePrefix = (TCHAR*)_T("com");
	pT = pProcInfo->m_var.comName + lstrlen(comNamePrefix);
	cfg.portNo = _ttol(pT);
	cfg.m_rate = 9600;
	cfg.m_parity = NOPARITY;
	cfg.m_dataBit = 8;
	cfg.m_stopBit = ONESTOPBIT;
	
	
	//
	if (initCom_infrared(&cfg, (CComPortEx**)&pProcInfo->m_var.pComPort_infrared))  goto  errLabel;

	//
	pProcInfo->m_var.bInited_infrared = true;

	//
	iErr = 0;
	errLabel:
	return  iErr;
}


int  stopInfraredThread()
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

	//
	exitCom_infrared((CComPortEx**)&pProcInfo->m_var.pComPort_infrared);

	//
	pProcInfo->m_var.bInited_infrared = false;


	//
	return  0;
}


//
int chkInfraredThread()
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

	//
	int dwThreadId = GetCurrentThreadId();
#ifdef  __DEBUG__
	assert(dwThreadId == pQyMc->gui.ctx_gui_thread.dwThreadId9);
#endif

	if (pQyMc->bQuit)  return  -1;
	if (pQyMc->bGuiQuit)  return  -1;

	//
	bool  bPortOk = false;
	
	//
	if (pProcInfo->m_var.bInited_infrared)  {
		 CComPortEx* pPort = (CComPortEx*)pProcInfo->m_var.pComPort_infrared;
		 if (pPort) {
			 if (pPort->m_var.ucbStarted
				 && !pPort->m_var.ucbSeriousErr)
			 {
				 bPortOk = true;
			 }
		 }

		 if (bPortOk) {
			 if (pPort->m_var.hWndOwner != pQyMc->gui.hMainWnd) {
				 pPort->m_var.hWndOwner = pQyMc->gui.hMainWnd;
				 //
				 showInfo_open(0, 0, 0, _T("chkInfraredThread: port.hWndOwner changed"));
			 }
		 }

	}

	
	//
	if (!bPortOk) {
		showInfo_open0(0, 0, _T("chkInfrared: port not ok, restart"));
		//
		stopInfraredThread();
		startInfraredThread();
	}

	//
	return  0;
}



//
int  initCom_infrared(COM_PORT_cfg* pCfg, CComPortEx** ppPort)
{
	int					iErr = -1;

	QY_MC* pQyMc = QY_GET_GBUF();
#if  0
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
#endif

	CComPortEx* pPort = NULL;


#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("initPtz enters"));
#endif

	//if (!pm_var)  return  -1;
	if (!ppPort)  return  -1;
	if (*ppPort) {
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("comPort exists. initPtz leaves"));
#endif
		showInfo_open0(0, 0, _T("initPtz failed, comPort exists"));
		return  -1;
	}


	//
	pPort = new  CComPortEx;
	if (!pPort)  goto  errLabel;

	//
	//memset(pm_var, 0, sizeof(pm_var[0]));
	//if (memcmp(pCfg, &pm_var->cfg, sizeof(pCfg[0])))  memcpy(&pm_var->cfg, pCfg, sizeof(pm_var->cfg));

	//  pProcInfo->ptz.m_var.m_nSpeed  =  23;

	//
	if (!pPort->bInitPort(pQyMc->gui.hMainWnd, pCfg->portNo, pCfg->m_rate, pCfg->m_parity, pCfg->m_dataBit, pCfg->m_stopBit, EV_RXCHAR | EV_CTS, 512, CONST_iComPortType_infrared, 0))  goto  errLabel;

	if (!pPort->bStartMonitoring()) {
		//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsClient"), 0, _T(""), _T(""), _T("port.bStartMonitoring failed"));
		goto  errLabel;
	}
	//  m_var.share_gps.var.dwTickCnt_start  =  GetTickCount(  );



	iErr = 0;
errLabel:

	if (iErr) {
		exitCom_infrared(&pPort);
	}
	if (!iErr) {
		if (ppPort)  *ppPort = pPort;
	}
#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("initPtz leaves"));
#endif
	//  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initPtz %s"  ),  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  )  );

	return  iErr;
}

void  exitCom_infrared(CComPortEx** ppPort)
{
	QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return;

#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("exitPtz enters"));
#endif

	if (!ppPort || !*ppPort)  return;
	//
	//if  (  pProcInfo->ptz.pComPort  )  
	{
		CComPortEx* pPort = (CComPortEx*)*ppPort;	//  pProcInfo->ptz.pComPort;

		delete  pPort;
		//pProcInfo->ptz.pComPort  =  NULL;
		*ppPort = NULL;
	}

#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("exitPtz leaves"));
#endif

	return;
}



