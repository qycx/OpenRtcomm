
#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>


#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//  #include	"qmcVideoCapture_isCli.h"
//#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
//  #include	"myfourcc.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

//#include	"isCliHelpPublic.h"
//#include	"dlgShareDynBmpsProc.h"
//#include	"isClid3dpublic.h"
#include	"qmcTaskPublic.h"

//#include	"qmcCommFunc_isCli.h"
#include	"qmcCfg.h"
#include	"shareAv.h"

#include <chrono>
#include <iomanip>
#include <sstream>
#include <thread>
#include <atomic>

//#include	"qmcVideoCapture_isCli.h"

#define CONST_pkts_IC 2
#define IC_FILE_PATH "c:\\tttbbb\\ic\\"

std::wstring joinPath(const std::wstring& path, const std::wstring& filename) {
	if (path.empty()) {
		return filename;
	}
	
	char lastChar = path.back();

	bool needsSeparator = (lastChar != '/' && lastChar != '\\');


	std::wstring fullPath = path;
	if (needsSeparator) {

#ifdef _WIN32
		fullPath += '\\';
#else
		fullPath += '/';
#endif
	}

	fullPath += filename;
	return fullPath;
}

bool CheckDiskSpace(const std::string& drive, ULONGLONG minSpaceMB) {
	ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalNumberOfFreeBytes;

	if (!GetDiskFreeSpaceExA(
		drive.c_str(),
		&freeBytesAvailable,
		&totalNumberOfBytes,
		&totalNumberOfFreeBytes)) {
		TCHAR tBuf[128] = _T("");
		_sntprintf(tBuf, mycountof(tBuf), _T("cant't get disk space:%d"), GetLastError());
		showInfo_open0(0, _T("check_ic_file"), tBuf);
		return false;
	}


	ULONGLONG freeSpaceMB = freeBytesAvailable.QuadPart / (1024 * 1024);	

	return freeSpaceMB >= minSpaceMB;
}

std::string GetDriveLetterFromPath(const std::string& path) {
	if (path.size() >= 2 && path[1] == ':') {
		return path.substr(0, 2); 
	}
	return ""; 
}

DWORD WINAPI mcThreadProc_toSaveIC(LPVOID lpParameter)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	myDRAW_VIDEO_DATA			pkts[CONST_pkts_IC];
	unsigned  int			    uiLens[CONST_pkts_IC];		//  要增加一个qGetMsgs，将pPkts和pktLens作为参数输入。2011/07/15
	int							nLens = mycountof(uiLens);		//  一次最多处理的包数。
	int							nPkts;
	BOOL                        tmpbErr = FALSE;

	

	while (pQyMc->bLogon) {

		//  2011/07/15, 先将pkts清空,nPkts 赋 0
		nPkts = 0;
		{
			CQyMalloc		mallocObj_tmpPkts[CONST_pkts_IC];

			if (!isQ2Empty(&pProcInfo->icQ2)) {		//  这里要将 qGetMsg 改成 qGetMsgs...

				//  pktLen  =  uiBufSize;  
				int nLens = mycountof(uiLens);
				//  2014/04/10
				if (q2GetMsgPkg(&pProcInfo->icQ2, (void*)pkts, sizeof(pkts), (unsigned  int*)uiLens, (unsigned  int*)&nLens, _T("save_ic"))) {
					break;
				}

				for (int i = 0; i < nLens; i++) {
					nPkts += uiLens[i] / sizeof(pkts[0]);
					if (uiLens[i] % sizeof(pkts[0])) {
#ifdef  __DEBUG__
						traceLog((TCHAR*)_T("save_ic: uiLen err"));
						assert(0);
#endif
					}
				}

				for (int i = 0; i < nPkts; i++) {
					myDRAW_VIDEO_DATA* pPkt = &pkts[i];
					if (pPkt->memory.m_pBuf) {
						if (mallocObj_tmpPkts[i].attach(&pPkt->memory)) {
#ifdef  __DEBUG__
							traceLogA((char*)"save_ic: mallocObj.attach failed");
#endif
							clean_myDRAW_VIDEO_DATA(pPkt, _T("playVideo"));
							tmpbErr = TRUE;
							continue;
						}
					}
				}

				if (tmpbErr)  continue;			    

			    if (!nPkts) {
#ifdef  __DEBUG__
				//traceLog((TCHAR*)  _T(  "mcThreadProc_vpp1: no pkts read."  )  );
#endif
				   break;
			    }

				tmpbErr = FALSE;
				for (int i = 0; i < nPkts; i++) {
					//do save
					//pkts[i].decInfo.dynBmp.resObj.uiObjType;
					//pkts[i].memory.m_pBuf; //rgb

					auto now = std::chrono::system_clock::now();
					auto now_c = std::chrono::system_clock::to_time_t(now);
					std::tm* ptm = std::localtime(&now_c);
					auto duration = now.time_since_epoch();
					auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;
					std::wstringstream ss;
					ss << std::put_time(ptm, _T("%Y%m%d%H%M%S")) << '.' << std::setfill(_T('0')) << std::setw(3) << milliseconds;


					TCHAR* pDir = pProcInfo->cfg.policy.dirToSaveICFile;
					bool isSaveIC = pProcInfo->cfg.policy.isSaveICFile;

					if (isSaveIC && bDir(pDir)) {

						std::wstring filename;// = pDir;// _T(IC_FILE_PATH);
						filename.append(ss.str());
						filename.append(_T(".bmp"));

						std::wstring path = joinPath(pDir, filename);

						/*
						filename.append(ss.str());
						filename.append(".raw");

						FILE* fp = NULL;
						fp = fopen(filename.c_str(), "wb");
						if (fp) {
							fwrite(pkts[i].memory.m_pBuf, pkts[i].memory.uiBufSize, 1, fp);
							fclose(fp);
						}*/

						mySaveBitmap(&pkts[i].bih, pkts[i].memory.m_pBuf, false, path.c_str());
					}
				}

			}
		}
	}

	return 0;

}

bool ensurePathExists(const std::string& path) {
	DWORD attrib = GetFileAttributesA(path.c_str());
	if (attrib == INVALID_FILE_ATTRIBUTES) {
		if (CreateDirectoryA(path.c_str(), NULL) ||
			ERROR_ALREADY_EXISTS == GetLastError()) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (attrib & FILE_ATTRIBUTE_DIRECTORY) {
		return true;
	}
	else {
		return false;
	}
}

bool createSaveICPath() {

	if (ensurePathExists("c:\\tttbbb")) {
		return ensurePathExists("c:\\tttbbb\\ic");
	}

	return false;

}

int  newstartQThreadToSaveIC(MC_VAR_common* pProcInfo)
{
	DWORD				dwThreadDaemonId;
	int iIndex = 0;
	GENERIC_Q_CFG		tmpCfg;

	MC_VAR_isCli* pProcInfoCli = (MC_VAR_isCli*)pProcInfo;

	CCtxQyMc* pQyMc = g_pQyMc;
	//MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	TCHAR	tName[128];
	memcpy(&tmpCfg, &pProcInfoCli->cfg.toSaveIcQ, sizeof(tmpCfg));
	_sntprintf(tmpCfg.name, mycountof(tmpCfg.name), _T("%s"), tmpCfg.name);
	_sntprintf(tmpCfg.mutexName_prefix, mycountof(tmpCfg.mutexName_prefix), _T("%s"), tmpCfg.mutexName_prefix);
	_sntprintf(tName, mycountof(tName), _T("%s"), CONST_evtName_qm_data_a);
	if (initQyQ2(&tmpCfg, &pQyMc->cfg.rwLockParam, mycountof(pProcInfoCli->icQ2.hEvents),
		CQyString(pQyMc->appParams.appObjPrefix) + tName, mallocMemory, mymalloc, 0, 0, 
		freeMemory, myfree, (PF_qElemRemove)clean_myPLAY_AUDIO_DATA, &pProcInfoCli->icQ2))  goto  errLabel;

	HANDLE hThread; hThread = CreateThread(NULL, 0, mcThreadProc_toSaveIC, (LPVOID)iIndex, CREATE_SUSPENDED, &dwThreadDaemonId);
	if (!hThread)  goto  errLabel;
	DWORD dwThreadId; dwThreadId = dwThreadDaemonId;
	if (ResumeThread(hThread) == -1)  goto  errLabel;


errLabel:
	return 0;
}

bool deleteOldRawFiles(const std::wstring& directoryPath, int daysToKeep) {
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	int deletedCount = 0;
	int errorCount = 0;

	std::wstring searchPath = directoryPath + _T("\\*.raw");

	SYSTEMTIME sysNow;
	GetSystemTime(&sysNow);
	FILETIME ftNow;
	SystemTimeToFileTime(&sysNow, &ftNow);
	ULARGE_INTEGER ulNow;
	ulNow.LowPart = ftNow.dwLowDateTime;
	ulNow.HighPart = ftNow.dwHighDateTime;

	TCHAR tBuf[128] = _T("");

	hFind = FindFirstFile(searchPath.c_str(), &findFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		_sntprintf(tBuf, mycountof(tBuf), _T("find file failed:%d"), GetLastError());
		showInfo_open0(0, _T("check_ic_file"), tBuf);
		return false;
	}

	do {		
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			continue;
		}

		FILETIME ftModified = findFileData.ftLastWriteTime;
		ULARGE_INTEGER ulModified;
		ulModified.LowPart = ftModified.dwLowDateTime;
		ulModified.HighPart = ftModified.dwHighDateTime;

		ULONGLONG diff = ulNow.QuadPart - ulModified.QuadPart;
		ULONGLONG days = diff / (10000000ULL * 60 * 60 * 24);

		if (days > static_cast<ULONGLONG>(daysToKeep)) {
			std::wstring fullPath = directoryPath + _T("\\") + findFileData.cFileName;

			if (DeleteFile(fullPath.c_str())) {
				deletedCount++;
				_sntprintf(tBuf, mycountof(tBuf), _T("already delete ic file:%s"), findFileData.cFileName);
				showInfo_open0(0, _T("check_ic_file"), tBuf);
			}
			else {
				errorCount++;
				_sntprintf(tBuf, mycountof(tBuf), _T("delete ic file failed:%s,%d"), findFileData.cFileName, GetLastError());
				showInfo_open0(0, _T("check_ic_file"), tBuf);
			}
		}
	} while (FindNextFile(hFind, &findFileData) != 0);

	FindClose(hFind);

	_sntprintf(tBuf, mycountof(tBuf), _T("finish delete ic file:deletedCount=%d,errorCount=%d"), deletedCount, errorCount);
	showInfo_open0(0, _T("check_ic_file"), tBuf);

	return true;
}

DWORD WINAPI mcThreadProc_toCheckICFile(LPVOID lpParameter)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	//myDRAW_VIDEO_DATA			pkts[CONST_pkts_IC];
	//unsigned  int			    uiLens[CONST_pkts_IC];		//  要增加一个qGetMsgs，将pPkts和pktLens作为参数输入。2011/07/15
	//int							nLens = mycountof(uiLens);		//  一次最多处理的包数。
	//int							nPkts;
	//BOOL                        tmpbErr = FALSE;

	const auto interval = std::chrono::hours(12);

	while (pQyMc->bLogon) {
		TCHAR* pDir = pProcInfo->cfg.policy.dirToSaveICFile;

		if (bDir(pDir)) {
			deleteOldRawFiles(pDir, 7);
		}

		auto now = std::chrono::system_clock::now();
		time_t now_time = std::chrono::system_clock::to_time_t(now);

		auto start = std::chrono::steady_clock::now();
		while (pQyMc->bLogon &&
			std::chrono::steady_clock::now() - start < interval) {
			std::this_thread::sleep_for(std::chrono::minutes(1)); // 每分钟检查一次是否停止
		}
	}

	return 0;
}

int  newstartQThreadToCheckICFile(MC_VAR_common* pProcInfo)
{
	DWORD				dwThreadDaemonId;
	int iIndex = 0;
	GENERIC_Q_CFG		tmpCfg;

	MC_VAR_isCli* pProcInfoCli = (MC_VAR_isCli*)pProcInfo;

	CCtxQyMc* pQyMc = g_pQyMc;
	//MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	TCHAR	tName[128];
	memcpy(&tmpCfg, &pProcInfoCli->cfg.toSaveIcQ, sizeof(tmpCfg));
	_sntprintf(tmpCfg.name, mycountof(tmpCfg.name), _T("%s"), tmpCfg.name);
	_sntprintf(tmpCfg.mutexName_prefix, mycountof(tmpCfg.mutexName_prefix), _T("%s"), tmpCfg.mutexName_prefix);
	_sntprintf(tName, mycountof(tName), _T("%s"), CONST_evtName_qm_data_a);
	if (initQyQ2(&tmpCfg, &pQyMc->cfg.rwLockParam, mycountof(pProcInfoCli->icQ2.hEvents),
		CQyString(pQyMc->appParams.appObjPrefix) + tName, mallocMemory, mymalloc, 0, 0,
		freeMemory, myfree, (PF_qElemRemove)clean_myPLAY_AUDIO_DATA, &pProcInfoCli->icQ2))  goto  errLabel;

	HANDLE hThread; hThread = CreateThread(NULL, 0, mcThreadProc_toCheckICFile, (LPVOID)iIndex, CREATE_SUSPENDED, &dwThreadDaemonId);
	if (!hThread)  goto  errLabel;
	DWORD dwThreadId; dwThreadId = dwThreadDaemonId;
	if (ResumeThread(hThread) == -1)  goto  errLabel;


errLabel:
	return 0;
}



//  2015/10/11
 int  newstartQThreadToShareAv(  MC_VAR_common  *  pProcInfo,  int  iIndex_sharedObj,  BOOL  bAudio  )
{
	int			iErr	=	-1;
	if(  !pProcInfo  )  return  -1;
	QY_MC	*	pQyMc	=	(  QY_MC  *  )pProcInfo->pQyMc;//QY_GET_GBUF(  );
	QMC_cfg  *  pCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pCfg  )  return  -1;

	//
	QY_SHARED_OBJ	*	pSharedObj	=	NULL;

	//  2011/07/27	
	TCHAR				tName[128];
	GENERIC_Q_CFG		tmpCfg;
	GENERIC_Q_cfgEx		qCfgEx;
	DWORD				dwThreadDaemonId;

	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;	

	if  (  bAudio  )  {
		CAP_procInfo_audioCommon  *  pCapAudio  =  NULL;

		pCapAudio  =  (  CAP_procInfo_audioCommon  *  )getCapAudioBySth(  pProcInfo,  pSharedObj->iIndex_capAudio,  0  );
		if  (  !pCapAudio  )  goto  errLabel;

		//  2015/10/11
		if  (  pCapAudio->thread.bQInited  )  {
			#ifdef  __DEBUG__
				    //  2015/10/11
					MACRO_qyAssert(  0,  _T(  "startQThreadToShareAv failed, capA.bQInited is already true"  )  );
			#endif
			showInfo_open0(  0,  0,  _T(  "startQThreadToShareAv failed, capA.bQInited is already true"  )  );
			goto  errLabel;
		}

		//
		memcpy(  &tmpCfg,  &pCfg->toShareAudioQ,  sizeof(  tmpCfg  )  );
		_sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-%d"  ),  tmpCfg.name,  pSharedObj->uiTranNo  );
		_sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-%d"  ),  tmpCfg.mutexName_prefix,  pSharedObj->uiTranNo  );
		_sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s%u"  ),  CONST_evtName_qm_data_a,  pSharedObj->uiTranNo  );
		if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapAudio->thread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myPLAY_AUDIO_DATA,  &pCapAudio->thread.q2  )  )  goto  errLabel;
		pCapAudio->thread.bQInited  =  TRUE;

		//
		if  (  !pCapAudio->thread.hThread  )  {
			//
			pCapAudio->thread.bQuit  =  FALSE;			
			pCapAudio->thread.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_toShareAudio,  (  LPVOID  )iIndex_sharedObj,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
			if  (  !pCapAudio->thread.hThread  )  goto  errLabel;					
			pCapAudio->thread.dwThreadId  =  dwThreadDaemonId;			
			if  (  ResumeThread(  pCapAudio->thread.hThread  )  ==  -1  )  goto  errLabel;									 
		}

		memset(&qCfgEx, 0, sizeof(qCfgEx));
		memcpy(&qCfgEx.common, &tmpCfg, sizeof(qCfgEx.common));
		qCfgEx.pfQElemNewEx = mallocMemory;
		qCfgEx.pfQElemNew = mymalloc;
		qCfgEx.pfQElemFreeEx = freeMemory;
		qCfgEx.pfQElemFree = myfree;
		qCfgEx.pf_QElemRemoveEx = (PF_qElemRemoveEx)cleanEx_myPLAY_AUDIO_DATA;
		if (initQyQ2(&qCfgEx, &pQyMc->cfg.rwLockParam, mycountof(pCapAudio->appThread.q2.hEvents),
			CQyString(pQyMc->appParams.appObjPrefix) + tName, &pCapAudio->appThread.q2))  goto  errLabel;
		pCapAudio->appThread.bQInited = TRUE;

		if (!pCapAudio->appThread.hThread) {
			pCapAudio->appThread.bQuit = FALSE;
			pCapAudio->appThread.hThread = CreateThread(NULL, 0, mcThreadProc_app, (LPVOID)iIndex_sharedObj, 
				CREATE_SUSPENDED, &dwThreadDaemonId);
			if (!pCapAudio->appThread.hThread)  goto  errLabel;
			pCapAudio->appThread.dwThreadId = dwThreadDaemonId;
			if (ResumeThread(pCapAudio->appThread.hThread) == -1)  goto  errLabel;
		}
	}

	//
	{
		  CAP_procInfo_bmpCommon  *  pCapBmp	=	NULL;

		  pCapBmp  =  (  CAP_procInfo_bmpCommon  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
		  if  (  !pCapBmp  )  goto  errLabel;


		  //////////////////////////////////

		  //  2011/12/06
		  memcpy(  &tmpCfg,  &pCfg->toShareVideo_postQ,  sizeof(  tmpCfg  )  );
		  _sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-%d"  ),  tmpCfg.name,  pSharedObj->uiTranNo  );
		  _sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-%d"  ),  tmpCfg.mutexName_prefix,  pSharedObj->uiTranNo  );
		  _sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s%u"  ),  CONST_evtName_qm_toShareVideo_post,  pSharedObj->uiTranNo  );
		  if  (  pCapBmp->postThread.bQInited  )  {
			  #ifdef  __DEBUG__  
					  //  2015/10/11
					  MACRO_qyAssert(  0,  _T(  "startQThreadToShareAv failed, capV.bQInited is  already true."  )  );
			  #endif
			  showInfo_open0(  0,  0,  _T(  "startQThreadToShareAv failed, capV.bQInited is  already true."  )  );
			  goto  errLabel;
		  }
		  //  if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapBmp->postThread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myDRAW_VIDEO_DATA,  &pCapBmp->postThread.q2  )  )  goto  errLabel;
		  memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );
		  memcpy(  &qCfgEx.common,  &tmpCfg,  sizeof(  qCfgEx.common  )  );
		  qCfgEx.pfQElemNewEx  =  mallocMemory;
		  qCfgEx.pfQElemNew  =  mymalloc;
		  qCfgEx.pfQElemFreeEx  =  freeMemory;
		  qCfgEx.pfQElemFree  =  myfree;
		  qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_myDRAW_VIDEO_DATA;
		  if  (  initQyQ2(  &qCfgEx,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapBmp->postThread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  &pCapBmp->postThread.q2  )  )  goto  errLabel;
		  pCapBmp->postThread.bQInited  =  TRUE;

		  //  2010/12/29
		  pCapBmp->compressVideo.debugInfo.nStep  =  35;

		  
		  //
		  memcpy(  &tmpCfg,  &pCfg->toShareVideoQ,  sizeof(  tmpCfg  )  );
		  _sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-%d"  ),  tmpCfg.name,  pSharedObj->uiTranNo  );
		  _sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-%d"  ),  tmpCfg.mutexName_prefix,  pSharedObj->uiTranNo  );
		  _sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s%u"  ),  CONST_evtName_qm_data_v,  pSharedObj->uiTranNo  );
		  if  (  pCapBmp->thread.bQInited  )  {
			  traceLog((TCHAR*)  _T(  "startQThreadToShareAv failed, bQInited is  already true."  )  );
			  goto  errLabel;
		  }
		  //  if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapBmp->thread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myDRAW_VIDEO_DATA,  &pCapBmp->thread.q2  )  )  goto  errLabel;
		  memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );
		  memcpy(  &qCfgEx.common,  &tmpCfg,  sizeof(  qCfgEx.common  )  );
		  qCfgEx.pfQElemNewEx  =  mallocMemory;
		  qCfgEx.pfQElemNew  =  mymalloc;
		  qCfgEx.pfQElemFreeEx  =  freeMemory;
		  qCfgEx.pfQElemFree  =  myfree;
		  qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_myDRAW_VIDEO_DATA;
		  if  (  initQyQ2(  &qCfgEx,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapBmp->thread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  &pCapBmp->thread.q2  )  )  goto  errLabel;
		  pCapBmp->thread.bQInited  =  TRUE;

		  //  2010/12/29
		  pCapBmp->compressVideo.debugInfo.nStep  =  37;


		  //  2011/12/04
		  memcpy(  &tmpCfg,  &pCfg->vppQ,  sizeof(  tmpCfg  )  );
		  _sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-%d"  ),  tmpCfg.name,  pSharedObj->uiTranNo  );
		  _sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-%d"  ),  tmpCfg.mutexName_prefix,  pSharedObj->uiTranNo  );
		  _sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s%u"  ),  CONST_evtName_qm_vpp,  pSharedObj->uiTranNo  );
		  if  (  pCapBmp->vppThread.bQInited  )  {
			  traceLog((TCHAR*)  _T(  "startQThreadToShareAv failed, vppThread.bQInited is  already true."  )  );
			  goto  errLabel;
		  }
		  //  if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapBmp->vppThread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myDRAW_VIDEO_DATA,  &pCapBmp->vppThread.q2  )  )  goto  errLabel;
		  memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );
		  memcpy(  &qCfgEx.common,  &tmpCfg,  sizeof(  qCfgEx.common  )  );
		  qCfgEx.pfQElemNewEx  =  mallocMemory;
		  qCfgEx.pfQElemNew  =  mymalloc;
		  qCfgEx.pfQElemFreeEx  =  freeMemory;
		  qCfgEx.pfQElemFree  =  myfree;
		  qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_myDRAW_VIDEO_DATA;
		  if  (  initQyQ2(  &qCfgEx,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapBmp->vppThread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  &pCapBmp->vppThread.q2  )  )  goto  errLabel;
		  pCapBmp->vppThread.bQInited  =  TRUE;
		  //


		  

		  //
		  if  (  !pCapBmp->postThread.hThread  )  {
			  //
			  pCapBmp->postThread.bQuit  =  FALSE;			
			  pCapBmp->postThread.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_toShareVideo_post,  (  LPVOID  )iIndex_sharedObj,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
			  if  (  !pCapBmp->postThread.hThread  )  goto  errLabel;					
			  pCapBmp->postThread.dwThreadId  =  dwThreadDaemonId;			
			  if  (  ResumeThread(  pCapBmp->postThread.hThread  )  ==  -1  )  goto  errLabel;									 
		  }

		  //
		  if  (  !pCapBmp->thread.hThread  )  {
			  //
			  pCapBmp->thread.bQuit  =  FALSE;			
			  pCapBmp->thread.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_encVideo,  (  LPVOID  )iIndex_sharedObj,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
			  if  (  !pCapBmp->thread.hThread  )  goto  errLabel;					
			  pCapBmp->thread.dwThreadId  =  dwThreadDaemonId;			
			  if  (  ResumeThread(  pCapBmp->thread.hThread  )  ==  -1  )  goto  errLabel;									 
		  }

		  //  2010/12/29
		  pCapBmp->compressVideo.debugInfo.nStep  =  38;

		  //
		  if  (  !pCapBmp->vppThread.hThread  )  {
			  //
			  pCapBmp->vppThread.bQuit  =  FALSE;			
			  pCapBmp->vppThread.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_vpp,  (  LPVOID  )iIndex_sharedObj,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
			  if  (  !pCapBmp->vppThread.hThread  )  goto  errLabel;					
			  pCapBmp->vppThread.dwThreadId  =  dwThreadDaemonId;			
			  if  (  ResumeThread(  pCapBmp->vppThread.hThread  )  ==  -1  )  goto  errLabel;									 
		  }




	}

	iErr  =  0;

errLabel:

	return  iErr;
}


