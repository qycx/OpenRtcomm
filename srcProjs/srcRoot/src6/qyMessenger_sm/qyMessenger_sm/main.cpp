

#include <QApplication> 
#include    <tchar.h>  

#define  __noDbg_new__

#include	"reportingHook.h"
#include	"setDebugNew.h" 
#include    "qyMcMainCommon_qt.h"
#include	"ctxQmc_sm.h" 
#include	"GuiShare.h" 
#include "CMainFrame.h"
#include "CQmcLogin.h" 
#include "WinSerConfig.h"
#include "QyApplication.h"
extern float dpi_;
#include <iostream>
#include<Windows.h>
#include <shellscalingapi.h>
#include "CDeviceBinding.h"

#pragma comment(lib, "Shcore.lib")
#ifdef  __DEBUG__
//#include "vld.h"
#endif
#include	"smCommProc.h"

#include <pdh.h>
#include <pdhmsg.h>
#include <QyMcExt_gui.h>

//
BOOL				InitInstance(HINSTANCE, int);
int					ExitInstance(HINSTANCE  hInstance);

//
bool bDone_smTerminalInitCfg(CCtxQmc_sm  *  pProcInfo)
{
	Sm_terminal_initCfg* pCfg = &pProcInfo->m_var.ctxSm.smTerminalInitCfg;

	//
	if (pProcInfo->m_var.bNeedCfg_smTerminalInitCfg)  return false;


	if (qyGetCustomId() != CONST_qyCustomId_business) {
		//
		if (bIpValid(pCfg->terminal_ip)
			&& bMaskValid(pCfg->terminal_mask)
			&& bIpValid(pCfg->terminal_gateway)
			&& bIpValid(pCfg->terminal_mcu)
			)
		{
			return  true;
		}
	}

		//
		if (bIpValid(pCfg->terminal_ip)
			&& bMaskValid(pCfg->terminal_mask)
			&& bIpValid(pCfg->terminal_gateway)
			&& bIpValid(pCfg->terminal_mcu)
			&& pCfg->terminal_sqm[0])
		{
			return  true;
		}
	


	return false;
}


//
int setNeedCfgOn_smTerminalInitCfg(bool bEnable)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

	pProcInfo->m_var.bNeedCfg_smTerminalInitCfg = bEnable;

	return 0;
}


//
bool  bNeedReinit()
{
	bool  bRet = false;

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

	if (pProcInfo->m_var.bNeedCfg_smTerminalInitCfg) {
		bRet = true;
	}

errLabel:
	return  bRet;
}



////////////////////////////////

int  createTool_sm(  TCHAR  *  fileName, Tool_ca* pToolCa)
{
	int			iErr = -1;

	//
	//Var_ca* pVc = &pProcInfo->m_var.ca;
	Tool_ca* pTc = pToolCa;
	TCHAR  tBuf[128];

	



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

	//
	safeTcsnCpy(fileName, tmpExeName, mycountof(tmpExeName));
	
	//
	if (tQyQuoteFileName(tmpExeName, mycountof(tmpExeName)))  goto  errLabel;


	//
	//
	_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s -ahaha"), tmpExeName  );

	//
	int  ii; ii = 0;



	//
	DWORD  dwCreationFlags; dwCreationFlags = 0;  // dwCreationFlags = CREATE_NO_WINDOW;
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
	_sntprintf(tBuf, mycountof(tBuf), _T("CreateTool_ca succeeded,  new processId is %d, tn %d"), pi.dwProcessId, pTc->tn_process_ca);
	showInfo_open0(0, 0, tBuf);
	//qyShowInfo(pQyMc->pShowInfoStruct, CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("create %s ok"), tmpExeName);
#endif


	//
	iErr = 0;

errLabel:

	if (bProcessCreated) {
		if (pi.hThread) { CloseHandle(pi.hThread);  pi.hThread = NULL; }
		if (pi.hProcess) {
			pTc->hProcess_ca = pi.hProcess;
			pTc->dwProcessId_ca = pi.dwProcessId;
		}
	}

	if (iErr) {
		//qyShowInfo(pQyMc->pShowInfoStruct, CONST_qyShowType_qwmComm, 0, (char*)"", _T("IsClient"), 0, _T(""), _T(""), _T("createRtspCliHelp failed, %s"), tmpExeName);
	}

	return  iErr;

}


int  closeTool_sm(Tool_ca* pToolCa)
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

#pragma comment(lib, "pdh.lib")

bool GetMemoryUsageWithPDH(double& memoryUsage) {
	PDH_HQUERY query;
	PDH_HCOUNTER counter;
	PDH_FMT_COUNTERVALUE counterVal;

	if (PdhOpenQuery(NULL, 0, &query) != ERROR_SUCCESS) {
		traceLog((TCHAR*)_T("Failed to open PDH query. "));
		return false;
	}

	if (PdhAddCounter(query, L"\\Memory\\% Committed Bytes In Use", 0, &counter) != ERROR_SUCCESS) {
		traceLog((TCHAR*)_T("Failed to add memory counter. "));
		PdhCloseQuery(query);
		return false;
	}

	if (PdhCollectQueryData(query) != ERROR_SUCCESS) {
		traceLog((TCHAR*)_T("Failed to collect query data. "));
		PdhCloseQuery(query);
		return false;
	}

	if (PdhGetFormattedCounterValue(counter, PDH_FMT_DOUBLE, NULL, &counterVal) != ERROR_SUCCESS) {
		traceLog((TCHAR*)_T("Failed to get formatted counter value. "));
		PdhCloseQuery(query);
		return false;
	}

	//double memoryUsage = counterVal.doubleValue;

	memoryUsage = counterVal.doubleValue;

	//std::cout << "Memory Usage (PDH): " << std::fixed << std::setprecision(2)
	//	<< memoryUsage << "%" << std::endl;

	PdhCloseQuery(query);
	return true;
}
//
int chkIfSmAlive()
{
	int  nTotal_noChange = 0;
	int  lastLoopCtrl = 0;
	int  nTotal_memOver = 0;
	int  ret = 0;

	//
	for (; ; ) {		

		double useValue = 0;
		GetMemoryUsageWithPDH(useValue);

		if (useValue > 90.0) {
			nTotal_memOver++;
		}
		else {
			nTotal_memOver = 0;
		}

		{
			QY_REG  reg;
			TCHAR  tBuf[128];

			memset(&reg, 0, sizeof(reg));
			reg.hKeyRoot0 = HKEY_CURRENT_USER;
			lstrcpyn(reg.rootKey, _T(CONST_qyRootKey_qnmScheduler_misClient), mycountof(reg.rootKey));


			TCHAR* pRegVal = (TCHAR*)_T(CONST_regValName_sm_memOverTimes);
			qySetRegCfgT(reg.hKeyRoot0, CQyString(reg.rootKey), pRegVal, _ltot(nTotal_memOver, tBuf, 10));
		}


		if (nTotal_memOver > 20) {
			traceLog((TCHAR*)_T("nTotal_memOver too large, it means mem no enough. "));
			ret = 2;
			break;
		}


		QY_REG  reg;
		TCHAR  tBuf[128];

		memset(&reg, 0, sizeof(reg));
		reg.hKeyRoot0 = HKEY_CURRENT_USER;
		lstrcpyn(reg.rootKey, _T(  CONST_qyRootKey_qnmScheduler_misClient  ), mycountof(reg.rootKey));


		TCHAR* pRegVal = (TCHAR*)_T(CONST_regValName_sm_loopCtrl);
		unsigned  int  uiType = 0;
		//
		bool  bChange = false;
		if (!qyGetRegCfgT(reg.hKeyRoot0, CQyString(reg.rootKey), pRegVal, (char*)tBuf, sizeof(tBuf), &uiType)) {
			int  tmp_loopCtrl = _ttol(tBuf);
			if (lastLoopCtrl != tmp_loopCtrl) {
				bChange = true;
				lastLoopCtrl = tmp_loopCtrl;
			}
		}
		if (!bChange)  nTotal_noChange++;
		else  nTotal_noChange = 0;
		//
		_sntprintf(tBuf, mycountof(tBuf), _T("nTotal_noChange %d, lastLoopCtrl %d"), nTotal_noChange, lastLoopCtrl);
		traceLog(tBuf);
		//
		int max_noChange = 30;
		//
		max_noChange = 15;
		//
		if (nTotal_noChange > max_noChange) {
			traceLog((TCHAR*)_T("nTotal_noChange too large, it means sm is not alive. "));
			ret = 1;
			break;
		}

		

		//
		Sleep(3000);
	}

	return  ret;
}


//
#include	"dbgFunc_open.h"


//
bool  bUse_icCap(TCHAR* smCfgFile);



//
int main(int argc, char* argv[])
{
	//
	bool  bNeedChkAlive = true;
	//bNeedChkAlive = false;

#ifdef  __DEBUG__
		bNeedChkAlive = false;
#endif 
	//
	if (bNeedChkAlive) {  // 保活
		if (argc == 1) {

			TCHAR  fileName[MAX_PATH] = _T("");
			GetModuleFileName(NULL, fileName, mycountof(fileName));

			TCHAR* tDir = (TCHAR*)_T("d:\\qycx\\");
			TCHAR  qmcLogFile[MAX_PATH];
			_sntprintf(qmcLogFile, mycountof(qmcLogFile), _T("%s\\log\\%s"), tDir, CONST_logFileName_qmcStatus);
			//
			TCHAR  smCfgFile[MAX_PATH];
			_sntprintf(smCfgFile, mycountof(smCfgFile), _T("%s\\cli_smCfg.ini"),  tDir);


			//
			int  terminalType = qyGetTerminalType(smCfgFile); //(_T("d:\\qycx\\cli_smCfg.ini"));
			//if (terminalType == CONST_terminalType_mon) 
			if  (  1  )
			{

				int  nTimes = 0;
				for (nTimes = 0; ; nTimes++) {

					Tool_ca tool = { 0 };
					TCHAR  tBuf[128];
					
					if (!createTool_sm(fileName, &tool)) {

						//
						int ret = chkIfSmAlive();
						//
						closeTool_sm(&tool);								

						//
						if (bUse_icCap(smCfgFile)) {
							//
							traceLog((TCHAR*)_T("发现sm不正常了, 是工业相机采集端，所以立即恢复"));
							Sleep(1000);
							//
							//
							_sntprintf(tBuf, mycountof(tBuf), _T("sm is not alive, icCap, to resume now,ret=%d"), ret);
							logStatus(qmcLogFile, _T("sm"), _T("main"), 0, tBuf);

							//
							continue;
						}

						//
						traceLog((TCHAR*)_T("发现sm不正常了，先Sleep 10秒,不能太快重启"));
						Sleep(10000);

						//
						_sntprintf(tBuf, mycountof(tBuf), _T("sm is not alive, to restart now,ret=%d"), ret);
						logStatus(qmcLogFile, _T("sm"), _T("main"), 0, tBuf);
						
						//
						traceLog((TCHAR*)_T("可以重启了"));
						//
						system("shutdown -r -t 00 -f");
						//w
					}

					//
					break;
				}
			}
			else {  //  会议终端
				int  nTimes = 0;
				for (  nTimes  =  0; ;  nTimes  ++ ) {
					//
					Tool_ca tool = { 0 };
					if (!createTool_sm(fileName, &tool)) {

						//
						int ret = chkIfSmAlive();
						//
						closeTool_sm(&tool);

						//
						//waitForObject(&tool.hProcess_ca, INFINITE);
						//
						closeTool_sm(&tool);
					}
					//
					TCHAR  tBuf[128];
					_sntprintf(tBuf, mycountof(tBuf), _T("sm_conf is not alive,  nTimes %d, to recreate now"), nTimes);
					logStatus(qmcLogFile, _T("sm_conf"), _T("main"), 0, tBuf);
					
					//
					Sleep(1000);
					continue;
				}
			}

			//
			return  0;
		}
	}
	

	// 彻底关闭 Qt6 高DPI缩放（100%生效）
	qputenv("QT_ENABLE_HIGHDPI_SCALING", "0");
	qputenv("QT_SCALE_FACTOR", "1");

	QApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
	QApplication::setAttribute(Qt::AA_Use96Dpi);


	//
	HDC hdc = GetDC(NULL);
	int hor = GetDeviceCaps(hdc, LOGPIXELSY);
	dpi_ = (float)GetDeviceCaps(hdc, LOGPIXELSY) / 96.0;


	//
	/*if (dpi_ <= 1)
	{
		dpi_ = 1;
		
	}
	else if (dpi_ == 1.75) {
		dpi_ = 1.75;
		qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "2");
	}
	else if (dpi_ == 2) {
		dpi_ = 2;
		qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
	}
	else if (dpi_ > 2 && dpi_ < 2.5) {
		dpi_ = 2;
		qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "2.0");
	}
	else if (dpi_ >= 2.5 && dpi_ <= 3.5) {
		dpi_ = 3;
		qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "3.0");
	}
	else {
		dpi_ = 1;
		qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1.0");
	}*/
	//qputenv("QT_SCALE_FACTOR", "1.0");
	//这句非常重要，不加这句后面谜案消息框会出现重影
	//QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
	//QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QyApplication a(argc, argv);
	int  ret = -1;
	a.setQuitOnLastWindowClosed(false);
#if 0
	QTranslator tran;
	bool ok = tran.load("qymessenger_qt_zh.qm", QCoreApplication::applicationDirPath());
	if (ok)
	{
		a.installTranslator(&tran);
	}
#endif 

#ifdef  __DEBUG__
	traceLog((TCHAR*)_T("main, enters"));
#endif

	GuiShare_init();
	CMainFrame* cmainFrame = nullptr;
	


	if (InitInstance(nullptr, 0) == false)goto  errLabel;  
	{  

		int i;
		int maxCnt = 1;
		maxCnt = 1000000;
#ifdef  __DEBUG__
		//maxCnt = 10000;
		maxCnt = 1;
#endif
		//
		for (i = 0; i < maxCnt; i++) {

			//
			CCtxQyMc* pQyMc = g_pQyMc;
			if (pQyMc) {
				//
				pQyMc->bGuiQuit = false;
				pQyMc->bQuit = false;
				//
				pQyMc->bScheduler_dontWork = true;
				//
			}
			CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
			MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
			memset(&pMisCnt->refreshImObjRules, 0, sizeof(pMisCnt->refreshImObjRules));
			memset(&pMisCnt->refreshContactList, 0, sizeof(pMisCnt->refreshContactList));
			memset(&pMisCnt->retrieveImObjList, 0, sizeof(pMisCnt->retrieveImObjList));
			memset(&pMisCnt->dualSystem, 0, sizeof(pMisCnt->dualSystem));

			//
			memset(&pProcInfo->m_var.ctxSm, 0, sizeof(pProcInfo->m_var.ctxSm));

			//
			bool  bDisableCa = pProcInfo->m_var.ctxSm.ca_dev.toolCa.m_bDisableCa;
			memset(&pProcInfo->m_var.ctxSm.ca_dev, 0, sizeof(pProcInfo->m_var.ctxSm.ca_dev));
			memset(&pProcInfo->m_var.ctxSm.ca_usr, 0, sizeof(pProcInfo->m_var.ctxSm.ca_usr));
			pProcInfo->m_var.ctxSm.ca_dev.toolCa.m_bDisableCa = bDisableCa;
			pProcInfo->m_var.ctxSm.ca_usr.toolCa.m_bDisableCa = bDisableCa;
			//
			//memset(&pProcInfo->m_var.ctxSm.usrLogin_sm, 0, sizeof(pProcInfo->m_var.ctxSm.usrLogin_sm));
			//
			memset(&pProcInfo->xt,0,sizeof(pProcInfo->xt));
			memset(&pProcInfo->m_var.usrInput, 0, sizeof(pProcInfo->m_var.usrInput));


			//
			int iTickCnt0 = myGetTickCount(mynull);

			//
			cmainFrame = new CMainFrame();
			if (cmainFrame == nullptr) goto errLabel;

			//判断是否需要先加载设备绑定页
			bool  bShow_cdeviceBind  =  false;
			
			//
			//QY_MC* pQyMc = QY_GET_GBUF();
			QY_REG				reg;
			reg.hKeyRoot0 = HKEY_CURRENT_USER;
			lstrcpyn(reg.rootKey, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, mycountof(reg.rootKey));
			qyDelRegCfgT(reg.hKeyRoot0 , reg.rootKey , _T(CONST_regValName_cntAddr));
			qyDelRegCfgT(reg.hKeyRoot0 , reg.rootKey , _T(CONST_qyCfgName_cntIp));

			//
			bGetSmTerminalInitCfg(pQyMc->cfg.tmInitFile, &pProcInfo->m_var.ctxSm.smTerminalInitCfg);
			getHkPortStatus(pQyMc->cfg.hkPortStatusFile, &pProcInfo->av.hk.portStatus);
			disableCa(pProcInfo->av.hk.portStatus.bDisable_usb_key_usb3);
			//
			if (!bDone_smTerminalInitCfg(pProcInfo)) {
				//
				bShow_cdeviceBind = true;
			}
			//
			if (bShow_cdeviceBind) 
			//if (true) 
			{
				CDeviceBinding cdeviceBind;
			
				//
				cmainFrame->hWnd_curWorking = (HWND)cdeviceBind.winId();
				if (IsWindow(cmainFrame->hWnd_curWorking)) {
					int  ii = 0;
				}

				//
				cdeviceBind.show();
				cdeviceBind.exec();

				//
				setNeedCfgOn_smTerminalInitCfg(false);

				//
				bGetSmTerminalInitCfg(pQyMc->cfg.tmInitFile, &pProcInfo->m_var.ctxSm.smTerminalInitCfg);
				//
				if (!bDone_smTerminalInitCfg(pProcInfo)) {
					continue;
				}

			}

			//
			pProcInfo->authInfo.usAuthType = pProcInfo->getAuthType();

			//
			if (IsWindow(cmainFrame->hWnd_curWorking)) {
				int  ii = 0;
			}

			
			//
			int  iTickCnt1 = myGetTickCount(mynull);
			int iDiffInMs0 = iTickCnt1 - iTickCnt0;

			qDebug() << "CMainFrame::iDiffInMs0=" + QString::number(iDiffInMs0);

			// 
			CQmcLogin* login = new CQmcLogin(nullptr);

			//
			cmainFrame->hWnd_curWorking = (HWND)login->winId();

			//
			int iTickCnt2 = myGetTickCount(mynull);
			int  iDiffInMs2 = iTickCnt2 - iTickCnt1;

			//
			if (login == nullptr) goto errLabel;
			ret = login->exec();
			while (ret == 100) {
				login->show();
				ret = login->exec();
			}
			delete login;
			if (ret != QDialog::Accepted) {
				goto errLabel;
			}
			//
			pQyMc->bScheduler_dontWork = false;

			//
			for (; ; ) {
				if (bNeedReinit())  break;

				// 
				cmainFrame->Init();
				//	cmainFrame->show(); 
					//a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
				ret = a.exec();

				//
				break;
			}

			//
			qmcLogoff();

			//
			if (cmainFrame) {
				delete cmainFrame;
				cmainFrame = nullptr;
			}

			//
			if (pProcInfo->av.localAv.chkCamera.bNeedRestart_noCamera) {
				int  ii = 0;
				qmcLogStatus(_T("main"), 0, _T("bNeedRestart_noCamera is true, quit now"));
				//
				break;
			}

			//
			continue;

		}
	}

errLabel: 
	if (cmainFrame) {
		delete cmainFrame;
		cmainFrame = nullptr;
	}

	ExitInstance(nullptr); 

	//
#ifdef  __DEBUG__
	setFilterDebugHook();
#endif


	//
	return ret;
}




HINSTANCE  get_my_hInst(QY_MC  *  pQyMc)
{
	//QY_MC* pQyMc = QY_GET_GBUF();
	return  pQyMc->g_hInst;
}

//  2013/06/15
BOOL  bQnmDemo()
{
	return  FALSE;
}


//
// 
HINSTANCE	g_hInst = NULL;							// current instance
//
struct {
	BOOL	bCoInited;
}			g_status_qmc;


//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	BOOL	bRet = FALSE;

	g_hInst = hInstance; // Store instance handle in our global variable

	//
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	//
#ifdef  __USE_oleInit__
	if (S_OK != OleInitialize(NULL)) {
		return  FALSE;
	}
#else
	DWORD dwCoInit = COINIT_APARTMENTTHREADED;	// COINIT_MULTITHREADED. 2013/06/17		
	if (!SUCCEEDED(CoInitializeEx(NULL, dwCoInit))) {
		return  FALSE;
	}
#endif
	g_status_qmc.bCoInited = TRUE;

	//
	set_cur_iResId_sys(CONST_resId_sys_isCli_ts);


	//  2015/07/08
	try {
		g_pQyMc = new  CCtxQyMc;
		if (!g_pQyMc)  goto  errLabel;
		//
		g_pQyMc->m_pQyMcExtTmpl = new QyMcExt_gui();
		if (!g_pQyMc->m_pQyMcExtTmpl)  goto  errLabel;
		g_pQyMc->m_pQyMcExtTmpl->m_var.m_pQyMc = g_pQyMc;
	}
	catch (...) {
		goto  errLabel;
	}
	//
	//  2016/08/12
	PARAM_initQyMc  param;
	memset(&param, 0, sizeof(param));
	param.pfNewVar = newVar_isCli_gui;
	param.pfFreeVar = freeVar_isCli_gui;
	//
	if (initQyMc(g_hInst, &param, g_pQyMc))   goto  errLabel;



#if  0
	HWND hWnd;

	//
	hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_ts_main), NULL, (DLGPROC)DialogProc_ts_main);
	if (!hWnd) {
		goto  errLabel;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
#endif

	//
#if  0
	CqyMc_tsDlg* pDlg = NULL;
	RECT							rect;

	pDlg = new  CqyMc_tsDlg;
	if (!pDlg->Create(rect))  return  FALSE;
#endif

#if  0
	//
	int  flg = SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW;
	SetWindowPos(pDlg->m_hWnd, NULL, 0, 0, 0, 0, flg);
#endif

	bRet = TRUE;
errLabel:

	return  bRet;
}

int ExitInstance(HINSTANCE  hInstance)
{
	int		iErr = -1;


	//
	exitQyMc(g_pQyMc);
	//  2015/07/08
	if (g_pQyMc) {
		QY_MC* pQyMc = (QY_MC*)g_pQyMc;
		//
		if (pQyMc->m_pQyMcExtTmpl) {
			MACRO_safeDelete(pQyMc->m_pQyMcExtTmpl);
		}
		MACRO_safeDelete(pQyMc);
		g_pQyMc = NULL;
	}


	//
	if (g_status_qmc.bCoInited) {
#ifdef  __USE_oleInit__
		OleUninitialize();
#else
		CoUninitialize();
#endif

		g_status_qmc.bCoInited = FALSE;
	}

	//
	iErr = 0;
errLabel:
	return  iErr;
}

