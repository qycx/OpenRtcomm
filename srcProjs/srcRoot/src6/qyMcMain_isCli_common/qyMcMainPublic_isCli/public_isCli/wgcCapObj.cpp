
#include	"stdafx.h"

#include <iostream>
#include <thread>
#include <chrono>

#ifdef  _WIN32
#include	<process.h>
#endif


#include	"qyMcMainCommon.h"
#include	"wgcCapObj.h"
#include	<qisPipe_open.h>
//
#include	"CtxQmc.h"
#include	<qisNameDefs.h>
#include	<vtShmFunc.h>
//
#include	"funcsForIsCliHelp.h"
//
//  2026/09/15  重启成功后立刻要一次关键帧, 不然接收端要干等下一个 IDR, 画面恢复很慢
//
#include	"qmcVideoCapture.h"


//
//  2026/09/15
//  "长时间没有帧" 这个判据要不要用:
//  WGC(Windows.Graphics.Capture) 是内容变化驱动 —— 屏幕不动就没有新帧,
//  所以静态画面(比如一直停在一页 PPT)会把它误判成故障. 默认关.
//  如果现场出现过"工具进程没死、但画面确实卡死了"的情况, 再把这里改成 1.
//
#define		WGC_ucbChk_dataStale			0


//
unsigned __stdcall wgc_threadProc_keepalive(void* arg);


//
int doWgc(WgcCapObj  *  pWgo,  WgcCapDev* pDev)
{
	return  0;
}


//  ============================================================================
//  内层 WgcCapDev: 真正干活的. WgcCapObj 只负责 建它 / 放它 / 盯着它.
//  ============================================================================

//
//  建立内层设备
//
int  WgcCapObj::startCapDev()
{
	int  iErr = -1;

	do {
		//
		if (m_var.pCapDev)  break;

		//
		WgcCapDev* pDev = mynull;
		try {
			pDev = new WgcCapDev();
		}
		catch (...) {
			showInfo_open(0, 0, 0, _T("WgcCapObj.startCapDev failed, new WgcCapDev except"));
			break;
		}
		if (!pDev) {
			showInfo_open(0, 0, 0, _T("WgcCapObj.startCapDev failed, pDev is null"));
			break;
		}

		//
		//  内层 initDev 失败时自己会 exitDev, 这里只管删
		//
		if (pDev->initDev(param_p0, &param_bih_suggested, param_lInstanceData)) {
			showInfo_open(0, 0, 0, _T("WgcCapObj.startCapDev failed, dev->initDev"));
			MACRO_safeDelete(pDev);
			break;
		}

		//
		m_var.pCapDev = pDev;
		m_var.w = pDev->m_var.status.w;
		m_var.h = pDev->m_var.status.h;

		iErr = 0;
	} while (false);

	return  iErr;
}


//
//  释放内层设备
//
int  WgcCapObj::stopCapDev()
{
	if (!m_var.pCapDev)  return  0;

	//  1) 先让内层的读回调停下来, 免得它踩到马上要释放的共享内存
	m_var.pCapDev->notifyStopReading(WGC_stopReading_timeoutMs);

	//  2) 正常退出: 关管道 / 解映射共享内存 / 关掉 anWgcTool.exe
	m_var.pCapDev->exitDev(mynull);

	//  3) 删
	MACRO_safeDelete(m_var.pCapDev);

	return  0;
}


//
bool  WgcCapObj::isCapDevOk()
{
	if (!m_var.pCapDev)  return  false;

	//
	return  m_var.pCapDev->isToolAlive();
}


//
//  自愈: 内层设备整只重建.
//  共享内存(以及管道连接)都是工具侧建的, 工具一死这些就作废;
//  与其在里面修修补补, 不如整只重建 —— 用的全是已经跑通的 initDev/exitDev.
//
int  WgcCapObj::restartCapDev(LPCTSTR hint)
{
	int  iErr = -1;
	TCHAR  tBuf[256];
	DWORD  dwTickCnt_begin = GetTickCount();

	//
	if (m_var.bRecovering)  return  -1;			//  重入保护
	m_var.bRecovering = true;

	//
	do {
		//
		_sntprintf(tBuf, mycountof(tBuf), _T("wgcCapObj: restart capDev begin. (%s)"),
			(hint ? hint : _T("")));
		showInfo_open0(0, 0, tBuf);

		//
		stopCapDev();

		//  正在退出程序, 就别重建了
		if (m_bQuit)  break;

		//
		if (startCapDev()) {
			m_var.nRestart_failed++;
			_sntprintf(tBuf, mycountof(tBuf), _T("wgcCapObj: restart capDev FAILED. ok %d, failed %d"),
				m_var.nRestart_ok, m_var.nRestart_failed);
			showInfo_open0(0, 0, tBuf);
			break;
		}

		//
		m_var.nRestart_ok++;

		//  2026/09/15  重启成功后立刻要一次关键帧:
		//  压缩器侧在 1.8s 内会把编码帧强制成 IDR, 接收端不用干等下一个自然 IDR,
		//  这是"恢复慢"观感的主要来源.
		//
		{
			MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
			if (pProcInfo && m_var.index_sharedObj >= 0) {
				setFlg_forceKeyFrame(pProcInfo, m_var.index_sharedObj);
			}
		}

		//  分辨率变了要提醒: 下游压缩器是按老尺寸配的
		if (m_var.w && m_var.h
			&& (m_var.w != m_var.pCapDev->m_var.status.w || m_var.h != m_var.pCapDev->m_var.status.h))
		{
			_sntprintf(tBuf, mycountof(tBuf), _T("wgcCapObj: NOTE screen size changed: %dx%d -> %dx%d"),
				m_var.w, m_var.h, m_var.pCapDev->m_var.status.w, m_var.pCapDev->m_var.status.h);
			showInfo_open0(0, 0, tBuf);
			showNotification_open(0, 0, 0, tBuf);
		}
		m_var.w = m_var.pCapDev->m_var.status.w;
		m_var.h = m_var.pCapDev->m_var.status.h;

		//
		_sntprintf(tBuf, mycountof(tBuf), _T("wgcCapObj: restart capDev OK. (%dx%d, ok %d, elapsed %dms)"),
			m_var.w, m_var.h, m_var.nRestart_ok, (int)(GetTickCount() - dwTickCnt_begin));
		showInfo_open0(0, 0, tBuf);
		traceLog((TCHAR*)_T("%s"), tBuf);

		iErr = 0;
	} while (false);

	//
	m_var.bRecovering = false;

	return  iErr;
}


//  ============================================================================
//  监控线程: 盯住 anWgcTool.exe(createVt 拉起来的那个)
//  ============================================================================

//
unsigned __stdcall wgc_threadProc_keepalive(void* arg)
{
	//
	WgcCapObj* pWgo = static_cast<WgcCapObj*>(arg);
	if (!pWgo)  return  0;

	//
	TCHAR  tBuf[256];
	int    iWarn = 0;
	bool   bStarted = false;
	DWORD  dwTickCnt_waitStarted = GetTickCount();

	//
	showInfo_open(0, 0, 0, _T("wgcCapObj: watchdog thread starts"));
	traceLog((TCHAR*)_T("wgcCapObj: watchdog thread starts"));

	//
	while (!pWgo->m_bQuit) {

		//  100ms 粒度, 退出时反应快点
		int  i;
		for (i = 0; i < (WGC_watch_intervalMs / 100); i++) {
			if (pWgo->m_bQuit)  return  0;
			Sleep(100);
		}

		//
		WgcCapDev* pDev = pWgo->m_var.pCapDev;
		if (!pDev)  continue;

		//
		LPCTSTR  szReason = mynull;
		bool     bAbnormal = false;

		//  1) 工具进程还在吗 —— 这是主判据, 不会误报
		if (!pDev->isToolAlive()) {
			bAbnormal = true;
			szReason = _T("wgcTool process exited");
		}
		//  2) 起来了但一直没进入取帧阶段
		else if (!bStarted) {
			if (GetTickCount() - dwTickCnt_waitStarted > WGC_waitStarted_timeoutMs) {
				bAbnormal = true;
				szReason = _T("wait capture data started timeout");
			}
		}
		//  3) 在取帧, 但帧断了(默认关, 见文件头 WGC_ucbChk_dataStale)
		else if (WGC_ucbChk_dataStale && pDev->isDataStale(WGC_dataStale_timeoutMs)) {
			bAbnormal = true;
			szReason = _T("no capture data too long");
		}

		//
		if (!bAbnormal) {
			if (pDev->isShmOk() && !bStarted) {
				bStarted = true;
				pWgo->m_var.iBackoffLevel = 0;
				iWarn = 0;
			}
			continue;
		}

		//  限频 + 退避(连续失败就不要死循环重启)
		DWORD  dwNow = GetTickCount();
		DWORD  dwInterval = WGC_restart_minIntervalMs;
		if (pWgo->m_var.iBackoffLevel > 0) {
			int  iShift = pWgo->m_var.iBackoffLevel;
			if (iShift > 3)  iShift = 3;
			dwInterval = WGC_restart_minIntervalMs << iShift;
			if (dwInterval > WGC_restart_backoffMaxMs)  dwInterval = WGC_restart_backoffMaxMs;
		}
		if (pWgo->m_var.dwLastTickCnt_restart
			&& (dwNow - pWgo->m_var.dwLastTickCnt_restart) < dwInterval)
		{
			continue;
		}
		pWgo->m_var.dwLastTickCnt_restart = dwNow;

		//
		iWarn++;
		_sntprintf(tBuf, mycountof(tBuf),
			_T("wgcCapObj: wgcTool abnormal(%s), restart it. warn#%d, ok %d, failed %d"),
			(szReason ? szReason : _T("")), iWarn, pWgo->m_var.nRestart_ok, pWgo->m_var.nRestart_failed);
		showInfo_open0(0, 0, tBuf);
		showNotification_open(0, 0, 0, tBuf);
		traceLog((TCHAR*)_T("%s"), tBuf);

		//
		if (pWgo->restartCapDev(szReason)) {
			if (pWgo->m_var.iBackoffLevel < 3)  pWgo->m_var.iBackoffLevel++;
		}
		else {
			pWgo->m_var.iBackoffLevel = 0;
		}

		//
		bStarted = false;
		dwTickCnt_waitStarted = GetTickCount();
	}

	//
	showInfo_open(0, 0, 0, _T("wgcCapObj: watchdog thread leaves"));
	traceLog((TCHAR*)_T("wgcCapObj: watchdog thread leaves"));

	return  0;
}


//
WgcCapObj::WgcCapObj()
{
	memset(&m_var, 0, sizeof(m_var));
	//
	m_hThread_capDev = mynull;
	m_bQuit = false;

	//
	return;
}


WgcCapObj::~WgcCapObj()
{
	//  兜底: 谁忘了调 exitDev, 这里也要收拾干净
	exitDev(mynull);

	//
	return;
}




//
int  WgcCapObj::initDev(void* p0, BITMAPINFOHEADER* pBih_suggested1, LONG_PTR lInstanceData)
{
	int  iErr = -1;
	WgcCapObj* p = this;

	do {
		//
		param_p0 = p0;
		memset(&param_bih_suggested, 0, sizeof(param_bih_suggested));
		if (pBih_suggested1) {
			param_bih_suggested = *pBih_suggested1;
		}
		param_lInstanceData = lInstanceData;

		//
		m_bQuit = false;
		m_var.bRecovering = false;
		m_var.bWatching = false;
		m_var.iBackoffLevel = 0;
		m_var.nRestart_ok = 0;
		m_var.nRestart_failed = 0;
		m_var.dwLastTickCnt_restart = 0;
		//
		m_var.index_sharedObj = -1;		//  bGetCapturePara 成功后才有有效值

		//  1) 建内层设备
		if (startCapDev()) {
			showInfo_open(0, 0, 0, _T("WgcCapObj.initDev failed, startCapDev"));
			break;
		}

		//  2) 起监控线程
		if (!isHandleValid_open(p->m_hThread_capDev)) {
			//
			p->m_hThread_capDev = (HANDLE)_beginthreadex(
				nullptr,
				0,
				wgc_threadProc_keepalive,
				p,
				0,
				nullptr
			);

			if (!isHandleValid_open(p->m_hThread_capDev)) {
				//  监控没起来不影响采集, 但要让现场知道
				showInfo_open(0, 0, 0, _T("WgcCapObj.initDev failed, watchdog thread not started"));
			}
			else {
				m_var.bWatching = true;
				showInfo_open(0, 0, 0, _T("WgcCapObj.initDev: watchdog started"));
			}
		}

		iErr = 0;
	} while (false);


	return  iErr;
}


//
int  WgcCapObj::exitDev(void** ppShareMediaDeviceParam)
{
	//  1) 先停监控线程(它在重建时可能正在动内层设备)
	m_bQuit = true;
	if (isHandleValid_open(m_hThread_capDev)) {
		//
		waitForObject(&m_hThread_capDev, WGC_exitWaitThread_timeoutMs);
		if (isHandleValid_open(m_hThread_capDev)) {
			showInfo_open(0, 0, 0, _T("WgcCapObj.exitDev: watchdog thread still alive, force close"));
			CloseHandle(m_hThread_capDev);  m_hThread_capDev = mynull;
		}
		m_var.bWatching = false;
	}

	//  2) 放掉内层设备
	stopCapDev();

	//
	if (ppShareMediaDeviceParam) {
		*ppShareMediaDeviceParam = mynull;
	}

	//
	return  0;
}


BOOL  WgcCapObj::bGetCapturePara(CCtxQmc* pProcInfo, int  iIndex_capAudio, int  iIndex_capBmp, void* pShareMediaDevice, WAVEFORMATEX* pWf_org, QY_VIDEO_HEADER* pVh_org, SAMPLE_grabberCb_cache* pCache)
{
	if (!m_var.pCapDev)  return  FALSE;

	//
	BOOL  bRet = m_var.pCapDev->bGetCapturePara(pProcInfo, iIndex_capAudio, iIndex_capBmp, pShareMediaDevice, pWf_org, pVh_org, pCache);

	//
	if (bRet) {
		m_var.index_sharedObj = m_var.pCapDev->m_var.index_sharedObj;
		m_var.index_capBmp = m_var.pCapDev->m_var.index_capBmp;
		m_var.bih_dec = m_var.pCapDev->m_var.bih_dec;
		//
		if (pVh_org) {
			m_var.w = pVh_org->bih.biWidth;
			m_var.h = pVh_org->bih.biHeight;
		}
	}

	//
	return  bRet;
}


int  WgcCapObj::runDev(void* pShareMediaDeviceParam)
{
	if (!m_var.pCapDev)  return  -1;

	//
	return  m_var.pCapDev->runDev(pShareMediaDeviceParam);
}


int  WgcCapObj::stopDev(void* pShareMediaDeviceParam)
{
	if (!m_var.pCapDev)  return  -1;

	//
	return  m_var.pCapDev->stopDev(pShareMediaDeviceParam);
}


//
int  WgcCapObj::readShmPkt( VT_shm_content* pShmContent, int  index_toRead)
{
	if (!m_var.pCapDev)  return  -1;

	//
	return  m_var.pCapDev->readShmPkt(pShmContent, index_toRead);
}

