
#include	"stdafx.h"

#include	<stddef.h>
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>
#include	<time.h>

#include	"isCliSaveAvCommon.h"

#include	"saveAvProc_open.h"
#include <stdio.h>
#include <string>
#include	"qytcharcommproc.h"

#include "TcpClient.h"

#include <chrono>
#include <sstream>
//
QIS_guiOpen_saveAv* g_pGuiOpen = nullptr;

//
extern  "C"  __declspec(dllexport)  int  setGuiOpen_saveAv(QIS_guiOpen_saveAv * pGuiOpen)
{
	//
	g_pGuiOpen = pGuiOpen;

	//
	return  0;
}



//
int saveAv_v_fwrite(void const* _Buffer, size_t  _ElementSize, size_t  _ElementCount, mySAVE_av_procInfo  * pSave)
{
	int total = _ElementSize * _ElementCount;
	if (pSave->video.cache.uiLen + total > pSave->video.cache.bufSize) {
		fwrite(pSave->video.cache.buf, pSave->video.cache.uiLen, 1, pSave->video.fp);
		pSave->video.cache.uiLen = 0;
		//
		if (total > pSave->video.cache.bufSize) {
			fwrite(_Buffer, total, 1, pSave->video.fp);
			return  0;
		}
	}
	memcpy(pSave->video.cache.buf + pSave->video.cache.uiLen, _Buffer, total);
	pSave->video.cache.uiLen += total;
	
	//
	return  0;

}


int  saveAv_v_fclose(mySAVE_av_procInfo* pSave)
{
	if (pSave->video.fp) {
		if (pSave->video.cache.uiLen) {
			fwrite(pSave->video.cache.buf, pSave->video.cache.uiLen, 1, pSave->video.fp);
			pSave->video.cache.uiLen = 0;
		}
		fclose(pSave->video.fp);  pSave->video.fp = nullptr;
	}

	return  0;
}


//
//
int saveAv_a_fwrite(void const* _Buffer, size_t  _ElementSize, size_t  _ElementCount, AStreamMem* pMem)
{
	int total = _ElementSize * _ElementCount;
	if (pMem->cache.uiLen + total > pMem->cache.bufSize) {
		fwrite(pMem->cache.buf, pMem->cache.uiLen, 1, pMem->fp);
		pMem->cache.uiLen = 0;
		//
		if (total > pMem->cache.bufSize) {
			fwrite(_Buffer, total, 1, pMem->fp);
			return  0;
		}
	}
	memcpy(pMem->cache.buf + pMem->cache.uiLen, _Buffer, total);
	pMem->cache.uiLen += total;

	//
	return  0;

}


int  saveAv_a_fclose(AStreamMem* pMem)
{
	if (pMem->fp) {
		if (pMem->cache.uiLen) {
			fwrite(pMem->cache.buf, pMem->cache.uiLen, 1, pMem->fp);
			pMem->cache.uiLen = 0;
		}
		fclose(pMem->fp);  pMem->fp = nullptr;
	}

	return  0;
}

std::string UnicodeToANSI(const std::wstring& wstr)
{
	if (wstr.empty()) return std::string();

	int size_needed = WideCharToMultiByte(
		CP_ACP,
		0,                   
		wstr.c_str(),        
		(int)wstr.length(),  
		NULL,                
		0,                   
		NULL, NULL           
	);

	if (size_needed == 0) {
		return "";
	}

	std::string result(size_needed, 0);
	WideCharToMultiByte(
		CP_ACP, 0,
		wstr.c_str(), (int)wstr.length(),
		&result[0], size_needed,
		NULL, NULL
	);

	return result;
}

char* UnicodeToAnsi(const wchar_t* szStr, int& nLen)
{
	nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	if (pResult == nullptr)
		return nullptr;
	WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);
	return pResult;
}

#include <chrono>
#include <sstream>
#include <iomanip>
#include <string>



std::string getDT() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	std::tm* now_tm = std::localtime(&now_time);

	std::stringstream ss;

	ss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S.");

	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
	ss << std::setw(3) << std::setfill('0') << millis.count();

	return ss.str();
}

/*
void  main() {

	TCHAR msg[100];
	swprintf_s(msg, L"sjlkjdkld");
	char* str = UnicodeToAnsi(msg);

}*/
#include <mutex>
std::recursive_mutex save_av_log_mtx;

int printLogChar(const char* log) {
	//return 0;

	if (log == nullptr)
		return 1;

	//std::lock_guard<std::recursive_mutex> lock(save_av_log_mtx);
	//return 0;
	FILE* pf = fopen("D:/qycx/log_saveAv.txt", "a+");
	if (pf == NULL)
	{
		perror("打开文件失败！");
		return 1;
	}

	//TCHAR* pp;  


	fprintf(pf, "[%s]  - %s \n", getDT().c_str(), log);

	fclose(pf);

	return 0;

}

int printLogChar(const char* log, const std::string& guid) {
	//return 0;

	if (log == nullptr)
		return 1;

	//std::lock_guard<std::recursive_mutex> lock(save_av_log_mtx);
	//return 0;
	FILE* pf = fopen("D:/qycx/log_saveAv.txt", "a+");
	if (pf == NULL)
	{
		perror("打开文件失败！");
		return 1;
	}

	//TCHAR* pp;  


	fprintf(pf, "[%s]  - %s : %s\n", getDT().c_str(), log, guid.c_str());

	fclose(pf);

	return 0;

}

int printLogChar(const char* log, DWORD tid) {
	//return 0;

	if (log == nullptr)
		return 1;

	//std::lock_guard<std::recursive_mutex> lock(save_av_log_mtx);
	//return 0;
	FILE* pf = fopen("D:/qycx/log_saveAv.txt", "a+");
	if (pf == NULL)
	{
		perror("打开文件失败！");
		return 1;
	}

	//TCHAR* pp;  


	fprintf(pf, "[%s]  - %s : %lu\n", getDT().c_str(), log, tid);

	//fprintf(pf, " %s : %lu\n", log, tid);

	fclose(pf);

	return 0;

}


//int printLogChar(const char* log, DWORD tid) {
//	//return 0;
//
//	if (log == nullptr)
//		return 1;
//
//	std::lock_guard<std::mutex> lock(save_av_log_mtx);
//	//return 0;
//	FILE* pf = fopen("D:/qycx/log_saveAv.txt", "a+");
//	if (pf == NULL)
//	{
//		perror("打开文件失败！");
//		return 1;
//	}
//
//	//TCHAR* pp;  
//
//
//	fprintf(pf, "[%s]  - %s : %lu\n", getDT().c_str(), log, tid);
//
//	fclose(pf);
//
//	return 0;
//
//}

int printLogChar(int log) {
	//return 0;
	//std::lock_guard<std::recursive_mutex> lock(save_av_log_mtx);
	FILE* pf = fopen("D:/qycx/log_saveAv.txt", "a+");
	if (pf == NULL)
	{
		perror("打开文件失败！");
		return 1;
	}

	//TCHAR* pp;  


	fprintf(pf, "[%s]  - %d \n", getDT().c_str(), log);

	fclose(pf);

	return 0;

}

int printLogChar(int log, DWORD tid) {
	//return 0;
	//std::lock_guard<std::recursive_mutex> lock(save_av_log_mtx);
	FILE* pf = fopen("D:/qycx/log_saveAv.txt", "a+");
	if (pf == NULL)
	{
		perror("打开文件失败！");
		return 1;
	}

	//TCHAR* pp;  


	fprintf(pf, "[%s]  - %d: %lu \n", getDT().c_str(), log, tid);

	fclose(pf);

	return 0;

}


int printLog(TCHAR* log) {
	//return 0;

	if (log == nullptr)
		return 1;
	//return 0;
	//std::lock_guard<std::recursive_mutex> lock(save_av_log_mtx);
	FILE* pf = fopen("D:\\qycx\\log_saveAv.txt", "a+");
	if (pf == NULL)
	{
		perror("打开文件失败！");
		return 1;
	}

	//TCHAR* pp;

	char* pBuf = NULL;
	int nLen = 0;	

	fprintf(pf, "[%s]  - %s \n", getDT().c_str(), UnicodeToANSI(log).c_str());

	/*pBuf = UnicodeToAnsi(log, nLen);	

	if (pBuf) {
		fprintf(pf, "%s:%s  - %s \n", __DATE__, __TIME__, pBuf);
		delete[] pBuf;
	}*/

	fclose(pf);

}

#include <tmpRegFunc_open.h>
#define		CONST_qyRootKey_qnmScheduler_mis				"Software\\Qycx\\mis\\Scheduler" 
#define		CONST_regValName_caGwIp						    "caGwIp"

int  getCaServCfg(char* caGwIp, int sizeof_caGwIp, int* piCaGwPort, char* hgIp, int  sizeof_hgIp, int* piHgPort, char* recIp, int  sizeof_recIp, int* piRecPort)
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

		TCHAR* pTRec;
		pTRec = _tcschr(pT, _T('='));

		if (!pTRec) break;
		pTRec++;


		pT = _tcschr(pTRec, _T(':'));
		if (!pT)  break;
		*pT = 0;  pT++;

		myTChar2Utf8(pTRec, recIp, sizeof_recIp);

		*piRecPort = _ttol(pT);

		//
		iErr = 0;
	} while (false);

	//
	return  iErr;
}



int  getCaServCfg(char* caGwIp, int sizeof_caGwIp, int* piCaGwPort, char* hgIp, int  sizeof_hgIp, int* piHgPort)
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

unsigned long long GetCurrentTimeMsec()
{
#ifdef _WIN32
	struct timeval tv;
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tv.tv_sec = clock;
	tv.tv_usec = wtm.wMilliseconds * 1000;
	return ((unsigned long long)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000);
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((unsigned long long)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000);
#endif
}

uint64_t get_ms() {
	auto now = std::chrono::high_resolution_clock::now();
	auto duration_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
	uint64_t milliseconds = duration_in_ms.count();
	return milliseconds;
}

#include <locale> 
#include <codecvt> 

std::string
to_string(
	const std::wstring& wstr)
{
	return std::wstring_convert<
		std::codecvt_utf8_utf16<WCHAR>, WCHAR>{}.to_bytes(wstr);
}


#include <windows.h>
#include <initguid.h>
#include <objbase.h>
#include <string>

std::string GenerateGuidString() {
	GUID guid;
	CoCreateGuid(&guid);

	OLECHAR* guidString;
	StringFromCLSID(guid, &guidString);

	// 转换为 std::string (宽字符转换为多字节)
	std::wstring ws(guidString);
	std::string str(ws.begin(), ws.end());

	// 释放内存
	CoTaskMemFree(guidString);

	return str;
}

DWORD GetThreadId() {
	DWORD threadId = GetCurrentThreadId();
	return threadId;
}

#include <mutex>
std::mutex lockM;

//  2015/02/17
extern  "C"  __declspec(dllexport)  int  doSaveAv(SAVE_av_procInfo * pSaveParam, SAVE_av_pktU * pSp, BOOL * pbExists_pSvp, CTX_mc_saveAv * pCtx)
{
	int									iErr = -1;

	

	//std::string guid = GenerateGuidString();
	DWORD guid = GetThreadId();	
	

	printLogChar("--------------------------doSaveAv----------in---------------", guid);
	

	if (pSaveParam == nullptr || pSp == nullptr) {
		printLogChar("--------------------------doSaveAv----------pSaveParam == nullptr || pSp == nullptr---------------", guid);
		return iErr;
	}

	printLogChar("--------------------------doSaveAv----------type---------------", pSaveParam->iType);

	/*if (pSaveParam->iType != 1) {
		printLogChar("-------------exit-------------doSaveAv----------type---------------", pSaveParam->iType);
		return iErr;
	}*/

	std::stringstream ssParm;

	ssParm << "on start bRecord_conf:" << pSaveParam->bRecord_conf << ",bRecord_trans:" << pSaveParam->bRecord_trans << ",bLive:"
		<< pSaveParam->bLive << ",meetingId:" << pSaveParam->meetingId
		<< ",peerId:" << pSaveParam->peerId << ",iType=" << pSaveParam->iType << ",index=" << pSaveParam->index;

	printLogChar(ssParm.str().c_str(), guid);


	if (pSaveParam->bRecord_conf == 0 && pSaveParam->bRecord_trans == 0) {
		printLogChar("-------------exit-------------doSaveAv----------bRecord_conf---------------", pSaveParam->bRecord_conf);
		printLogChar("-------------exit-------------doSaveAv----------bRecord_trans---------------", pSaveParam->bRecord_trans);
		return iErr;
	}
	


	/*if (pSaveParam->iType != 1)
		return 0;*/

	//
	mySAVE_av_procInfo* pSave = (mySAVE_av_procInfo*)pSaveParam;

	

	//
	unsigned  int  len;
	TCHAR								tmpDirName[MAX_PATH] = _T("");
	TCHAR								fileName[MAX_PATH] = _T("");
	TCHAR								fileNamePure[MAX_PATH] = _T("");
	char								timeBuf[CONST_qyTimeLen + 1];
	char								buf[256] = "";
	TCHAR								outputFileName[255] = _T("");
	TCHAR								tBuf[256];

	//TCHAR  tBuf[256];
	HKEY hKeyRoot0 = HKEY_LOCAL_MACHINE;
	unsigned  int  uiType = 0;
	unsigned  int  size = sizeof(tBuf);
	//
	char  gwIp[64] = "";
	int   gwPort = 0;
	char  hgIp[64] = "";
	int   hgPort = 0;
	char  reIp[64] = "";
	int   rePort = 0;

	

	g_pGuiOpen->pf_showInfo(0, 0, _T("doSaveAv new"));

	if (getCaServCfg(gwIp, sizeof(gwIp), &gwPort, hgIp, sizeof(hgIp), &hgPort, reIp, sizeof(reIp), &rePort) != 0) {
	//if (getCaServCfg(gwIp, sizeof(gwIp), &gwPort, hgIp, sizeof(hgIp), &hgPort) != 0) {
		printLogChar("get hg ip failed");
		g_pGuiOpen->pf_showInfo(0, 0, _T("get hg ip failed"));
		return -1;
	}
	else {
		printLogChar("--------hg ip -----begin-----", guid);
		std::stringstream ss;
		ss << "hgip:" << hgIp << "hgPort:" << hgPort << "reIp:" << reIp << "rePort:" << rePort << std::endl;
		printLogChar(ss.str().c_str());
		printLogChar("--------hg ip -----end-----", guid);
	}

	//const char* recIp = "10.0.1.111";//hgIp;// "10.0.1.135";
	//const char* recIp = "10.0.1.135";
	//const char* recIp = "10.0.1.121";
	//const char* reIp = "10.0.10.180";
	//int rePort = 12033;

	printLogChar("--------rec ip -----begin-----", guid);
	printLogChar(reIp, guid);
	printLogChar(rePort);
	printLogChar("--------rec ip -----end-----", guid);


	printLogChar("--------data-----begin-----", guid);

	std::string bufRec;
	std::stringstream ssRec;

	std::stringstream bufstr;
	std::string liveUrl;

	if (pSave == nullptr) {
		printLogChar("---------pSave isnulll-----", guid);
		goto  errLabel;
	}

	//printLogChar("--------doSaveAv--aaaaaaaaaa--1111111111-", guid);

	liveUrl = to_string(pSaveParam->liveUrl);

	pSaveParam->bRecord_conf = true;
	pSaveParam->bLive = true;
	

	bufstr << "bRecord:" << pSaveParam->bRecord_conf << ",bLive:" << pSaveParam->bLive << ",meetingId:" << pSaveParam->meetingId
		<< ",peerId:" << pSaveParam->peerId << ",liveUrl:" << liveUrl << ",iType=" << pSaveParam->iType;
	
	printLogChar(bufstr.str().c_str(), guid);
	printLogChar("--------data-----end-----", guid);



	printLogChar("doSaveAv in", guid);
	bool ret = false;


	TcpClient* client = nullptr;

	if (pSaveParam->iType == 1) {
		client = new TcpClient(reIp, rePort);
		if (client == nullptr) {
			printLogChar("new TcpClient  failed", guid);
			goto  errLabel;
		}

		client->Initialize();
		//ret = client->Start(guid);

		client->Start();
	}

	/*if (ret != 0) {
		_sntprintf(tBuf, mycountof(tBuf), _T("rec client start failed %s:%d"), reIp, rePort);
		g_pGuiOpen->pf_showInfo(0, 0, tBuf);
		printLogChar("rec client start failed", guid);
		goto  errLabel;
	}
	else {
		printLogChar("rec client start success", guid);
	}*/

	//

	TCHAR* capScreenDir = _T("c:\\tttbbb\\124\\");
	capScreenDir = pSave->common.tDir;

	
	if (!bDir(capScreenDir)) {
		//
		goto  errLabel;
	}
	_sntprintf(tmpDirName, mycountof(tmpDirName), _T("%s\\%s_tmp\\"), (capScreenDir), pSave->common.pureFileName_prefix);
	if (!bDir(tmpDirName)) {
		if (!CreateDirectory(tmpDirName, NULL)) {
			int  tmperr = GetLastError();
			//ERROR_ALREADY_EXISTS
			goto  errLabel;
		}
	}
	
	//

	
	_sntprintf(outputFileName, mycountof(outputFileName), _T("%s\\%s.mp4"), capScreenDir, pSave->common.pureFileName_prefix);
	lstrcpyn(pSave->common.fullOutputFileName, outputFileName, mycountof(pSave->common.fullOutputFileName));
	

	/*char* pBufRec = NULL;
	int nLenRec = 0;
	pBufRec = UnicodeToAnsi(pSave->common.pureFileName_prefix, nLenRec);

	if (pBufRec == nullptr) {
		printLogChar("UnicodeToAnsi pBufRec failed");
		goto  errLabel;
	}*/

	bufRec = UnicodeToANSI(pSave->common.pureFileName_prefix);

	/*if (pSaveParam->iType == 1) {
		ssRec << bufRec << "_" << guid;
	}
	else {
		ssRec << bufRec << "_" << guid;
	}
	
	bufRec = ssRec.str();*/

	bool bIsStart = false;

	//client->SendRecordStart(pBufRec);

	if (pSaveParam->iType == 1) {
		client->SendRecordStartNew(bufRec.c_str(), pSaveParam->bRecord_conf, pSaveParam->bLive, pSaveParam->meetingId, pSaveParam->peerId, liveUrl.c_str());
		bIsStart = true;

		printLogChar("---------SendRecordStart----------begin---", guid);
		printLogChar(bufRec.c_str(), guid);
		printLogChar("---------SendRecordStart----------end---", guid);
	}
	else {	
		/*ssRec << bufRec << "_" << pSaveParam->peerId << "_" << pSaveParam->index;
		bufRec = ssRec.str();*/
		
	}

	
	

	//
	TCHAR								tName[128] = _T("");
	TCHAR								tNamePure[128] = _T("");

	

	//printLogChar("---------doSaveAv-----111111111111111111111--aaaa---", guid);

	//
	pSave->common.video.frame_cnt = 0;

	//
	int  i;	

	memset(&pSave->audio, 0, sizeof(pSave->audio));
	memset(&pSave->video, 0, sizeof(pSave->video));
	for (i = 0; i < mycountof(pSave->audio.aStreams.mems); i++) {
		AStreamMem* pMem = &pSave->audio.aStreams.mems[i];
		pMem->cache.bufSize = sizeof(pMem->cache.buf);
	}
	pSave->video.cache.bufSize = sizeof(pSave->video.cache.buf);	

	

	//
	DWORD  dwTickCnt_start = GetTickCount();
	DWORD  dwTickCnt_flush = 0;


	//printLogChar("---------doSaveAv-----111111111111111111111-----", guid);

	bool isReconnect = false;
	//
	for (; ; ) {

		

		if (pSave->common.bQuit
			&& isQ2Empty(&pSave->common.q2))
		{
			//printLogChar("---------doSaveAv-----111111111111111111111-break----", guid);
			break;
		}

		//printLogChar("---------doSaveAv-----2222222222-----", guid);

		//
		if (1) {
			//g_pGuiOpen->pf_showInfo(0, 0, _T("doSaveAv"));
		}

		if (g_pGuiOpen->pf_q2GetMsg == nullptr) {
			printLogChar("---------g_pGuiOpen->pf_q2GetMsg isnulll-----", guid);
			goto  errLabel;
		}

		

		if (pSp == nullptr) {
			printLogChar("---------pSp isnulll-----", guid);
			goto  errLabel;
		}

		//printLogChar("---------doSaveAv-----2222222222--aaa---", guid);

		//
		len = sizeof(SAVE_av_pktU);
		
		if (isReconnect) {
			int count = 0;
			while (g_pGuiOpen->pf_q2GetMsg(&pSave->common.q2, pSp, &len, _T("doSaveAv")) == 0) {
				count++;
			}

			printLogChar("---------isReconnect---clear--", count);

			isReconnect = false;
		}

		if (g_pGuiOpen->pf_q2GetMsg(&pSave->common.q2, pSp, &len, _T("doSaveAv"))) {
			Sleep(100);
			continue;
		}

		
		if (pSaveParam->iType != 1 || pSaveParam->bRecord_conf == 0) {
			//printLogChar("-------------exit-------------doSaveAv----------type---------------", pSaveParam->iType);
			//printLogChar("-------------exit-------------doSaveAv--------typeother---------------", pSaveParam->iType);
			continue;
		}


#ifdef  _DEBUG
		//traceLog(_T("saveThread: svp->uiLen %d, len %d "), pSvp->uiLen, len);
#endif

		//int qsize = getQ2Nodes(&pSave->common.q2.qs[0].uiQNodes);
		int qsize0 = pSave->common.q2.qs[0].uiQNodes;
		int qsize1 = pSave->common.q2.qs[1].uiQNodes;

		//printLogChar("---------doSaveAv-----3333333333333-----", guid);

		

		//		
		if (!pSp->common.bAudio) {

			//printLogChar("---------doSaveAv-----4444444444-----", guid);

			//
			SAVE_video_pkt* pSvp = &pSp->vPkt;
			int								iFourcc_file = 0;

			//if (pSaveParam->iType == 2 && !bIsStart) {
			//	pSaveParam->peerId = pSvp->idInfo.ui64Id;

			//	if (liveUrl.empty()) {
			//		std::stringstream ssUrl;
			//		ssUrl << "rtsp://192.168.1.180/live/" << pSaveParam->peerId;
			//		liveUrl = ssUrl.str();
			//	}

			//	//pSaveParam->index;

			//	printLogChar("---------SendRecordStartNew--2--------", pSvp->idInfo.ui64Id);
			//	client->SendRecordStartNew(bufRec.c_str(), pSaveParam->bRecord, pSaveParam->bLive, pSaveParam->meetingId, pSaveParam->peerId, liveUrl.c_str());
			//	bIsStart = true;
			//}		


			if (pSaveParam->iType != 1 && !bIsStart) {

				pSaveParam->peerId = pSvp->idInfo.ui64Id;

				ssRec << bufRec << "_" << pSaveParam->peerId << "_" << pSaveParam->index;
				bufRec = ssRec.str();

				if (liveUrl.empty()) {
					std::stringstream ssUrl;
					ssUrl << "rtsp://" << reIp  << "/live/" << pSaveParam->peerId;// << "_" << pSaveParam->index;
					liveUrl = ssUrl.str();
				}

				client->SendRecordStartNew(bufRec.c_str(), pSaveParam->bRecord_conf, pSaveParam->bLive, pSaveParam->meetingId,
					pSaveParam->peerId, liveUrl.c_str());

				bIsStart = true;
				std::stringstream ss;
				printLogChar("---------SendRecordStart---single-------begin---", guid);
				ss << bufRec << "," << pSaveParam->index;
				//printLogChar(bufRec.c_str(), guid);
				printLogChar(ss.str().c_str(), guid);
				printLogChar("---------SendRecordStart---single-------end---", guid);
			}
			

			iFourcc_file = pSvp->iFourcc;

			if (pSvp->bSpsPps)
				printLogChar("---------bSpsPps----------", guid);
			//
			if (!pSave->video.flag) {

				iFourcc_file = pSp->vPkt.iFourcc;// CONST_fourcc_h264;
				//
				lstrcpyn(tName, _T("v_"), mycountof(tName));
				//
				switch (iFourcc_file) {
				case  CONST_fourcc_h264:
					_sntprintf(fileName, mycountof(fileName), _T("%s%s.264"), tmpDirName, tName);
					_sntprintf(fileNamePure, mycountof(fileNamePure), _T("%s.264"), tName);
					break;
				case  CONST_fourcc_HEVC:
					_sntprintf(fileName, mycountof(fileName), _T("%s%s.265"), tmpDirName, tName);
					_sntprintf(fileNamePure, mycountof(fileNamePure), _T("%s.265"), tName);
					break;
				default:
					//
					char  fourccStr[4 + 1];
					TCHAR  tBuf[128];
					iFourcc2Str(iFourcc_file, fourccStr, mycountof(fourccStr));
					_sntprintf(tBuf, mycountof(tBuf), _T("doSaveAv failed: %S not supported"), (fourccStr));
					g_pGuiOpen->pf_showInfo(0, 0, tBuf);
					goto  errLabel;
					break;
				}
				//printLogChar("---------doSaveAv-----5555555555555-----", guid);
				//
				{
					time_t  t;
					time(&t);
					pSave->video.tStartToSave = t;
					lstrcpyn(pSave->video.fileName, fileName, mycountof(pSave->video.fileName));
					//lstrcpyn(pSave->video.fileNamePure, fileNamePure, mycountof(pSave->video.fileNamePure));
				}

				/*char* pBufVideoName = NULL;
				int nLenvideoName = 0;
				pBufVideoName = UnicodeToAnsi(fileNamePure, nLenvideoName);*/

				std::string bufVideoName = UnicodeToANSI(fileNamePure);

				strncpy(pSave->video.fileNamePure, bufVideoName.c_str(), mycountof(pSave->video.fileNamePure));

				

				pSave->video.startTime = get_ms();
				pSave->video.firstTime = 0;
				pSave->video.count = 0;

				client->SendVideoStart(bufRec.c_str(), bufVideoName.c_str());
				pSave->video.flag = true;
				
				printLogChar("---------SendVideoStart----------begin---");
				printLogChar(bufRec.c_str());
				printLogChar(bufVideoName.c_str());
				printLogChar("---------SendVideoStart----------end---");
				

			}

			//printLogChar("---------doSaveAv-----666666666666-----", guid);

			unsigned  int orgSampleTimeInMs = pSvp->uiSampleTimeInMs;
			//
			switch (iFourcc_file) {
			case  CONST_fourcc_h264:
			case  CONST_fourcc_HEVC:
				//
				TCHAR  tBuf[128];
				_sntprintf(tBuf, mycountof(tBuf), _T("doSaveAv: %d bytes\n"), pSvp->uiLen);
				OutputDebugString(tBuf);
				//printLogChar("---------SendVideoData----------begin---");
				//printLogCharU(pSvp->uiSampleTimeInMs);
				//printLogChar("---------SendVideoData----------end---");


				if (pSvp->uiSampleTimeInMs != 0) {
					if (pSave->video.firstTime == 0) {
						pSave->video.firstTime = pSvp->uiSampleTimeInMs;
						//pSvp->uiSampleTimeInMs = pSave->video.startTime;
						pSvp->uiSampleTimeInMs = 0;
					}
					else {
						//pSvp->uiSampleTimeInMs = pSave->video.startTime + pSvp->uiSampleTimeInMs - pSave->video.firstTime;
						pSvp->uiSampleTimeInMs = pSvp->uiSampleTimeInMs - pSave->video.firstTime;
					}
				}
				else if (pSvp->uiSampleTimeInMs == 0) {
					//pSvp->uiSampleTimeInMs = pSave->video.startTime;
				}

				//printLogChar("---------doSaveAv-----777777777777-----", guid);

				//pSvp->uiSampleTimeInMs = pSave->video.count * 33;
				//pSave->video.count++;
				
				//if (!client->SendVideoData(bufRec.c_str(), pSave->video.fileNamePure, (unsigned char*)pSvp->buf, pSvp->uiLen, 
				//	pSvp->uiSampleTimeInMs, pSvp->uiPts, orgSampleTimeInMs, qsize0, qsize1)) goto errLabel;

				client->SendVideoData(bufRec.c_str(), pSave->video.fileNamePure, (unsigned char*)pSvp->buf, pSvp->uiLen,
					pSvp->uiSampleTimeInMs, pSvp->uiPts, orgSampleTimeInMs, qsize0, qsize1, isReconnect);
					
					

				break;

			default:
				goto  errLabel;
				break;
			}

			//
			pSave->common.video.frame_cnt++;

		}
		else {
			SAVE_audio_pkt* pSap = &pSp->aPkt;
			WORD			wFormatTag_file = 0;

			wFormatTag_file = pSap->wFormatTag;

			//printLogChar("----------------- audio in -----------------------");

			//
			int  index_activeMems_from = pSap->index_activeMems_from;
			if (index_activeMems_from < 0 || index_activeMems_from >= mycountof(pSave->audio.aStreams.mems)) {
				g_pGuiOpen->pf_showInfo(0, 0, _T("doSaveAv: index_activeMems_from err"));
				continue;
			}

			//printLogChar("----------------- audio in 2-----------------------");

			//
			DWORD  dwTickCnt = GetTickCount();
			unsigned  int orgSampleTimeInMs = pSap->uiSampleTimeInMs;

			//printLogChar("---------doSaveAv-----888888888888-----", guid);

			//
			AStreamMem* pMem = &pSave->audio.aStreams.mems[index_activeMems_from];
			if (pMem->flag) {
				int iDiffInMs = dwTickCnt - pMem->dwTickCnt_lastWrite;

				//printLogChar("----------------- audio in 3-----------------------");

				/*
				printLogChar("---------iDiffInMs----------begin---");
				printLogChar(iDiffInMs);
				printLogChar(dwTickCnt);
				printLogChar(pMem->dwTickCnt_lastWrite);
				printLogChar("---------iDiffInMs----------end---");
				*/
				//
				//std::stringstream ss;
				//ss << "pMem->idInfo.ui64Id=" << pMem->idInfo.ui64Id << ",pSap->idInfo.ui64Id=" << pSap->idInfo.ui64Id 
				//	<< ",pMem->tn_openAvDev=" << pMem->tn_openAvDev << ",pSap->uiTranNo_openAvDev=" << pSap->uiTranNo_openAvDev;
				//printLogChar(ss.str().c_str());

				//printLogChar("----------------- audio in 3-------end----------------");
				/*if (pMem->idInfo.ui64Id != pSap->idInfo.ui64Id
					|| pMem->tn_openAvDev != pSap->uiTranNo_openAvDev
					|| abs(iDiffInMs) > 1000)*/
				if (pMem->idInfo.ui64Id != pSap->idInfo.ui64Id
					|| pMem->tn_openAvDev != pSap->uiTranNo_openAvDev)
				{
					//printLogChar("----------------- audio in 3--------1---------------");
					if (pMem->cache.uiLen) {

						if (pSap->uiSampleTimeInMs != 0) {
							if (pMem->firstTime == 0) {
								pMem->firstTime = pSap->uiSampleTimeInMs;
								//pSap->uiSampleTimeInMs = pMem->startTime;
								pSap->uiSampleTimeInMs = pMem->diff;
							}
							else {
								//pSap->uiSampleTimeInMs = pMem->startTime + pSap->uiSampleTimeInMs - pMem->firstTime;
								pSap->uiSampleTimeInMs = pMem->diff + pSap->uiSampleTimeInMs - pMem->firstTime;
							}
						}


						//pSap->uiSampleTimeInMs = pMem->startTime - pSave->video.startTime + pMem->count * 36;
						//pMem->count++;
						
						client->SendAudioData(bufRec.c_str(), pMem->fileNamePure, (unsigned char*)pMem->cache.buf, pMem->cache.uiLen,
							pSap->uiSampleTimeInMs, pSap->uiPts, orgSampleTimeInMs, qsize0, qsize1);
							
							
						pMem->cache.uiLen = 0;
					}
					//printLogChar("----------------- audio in 3----------2-------------");
					pMem->flag = false;
					//client->SendAudioClose()
					_sntprintf(tBuf, mycountof(tBuf), _T("doSaveAv: a, fclose [%d]"), index_activeMems_from);
					g_pGuiOpen->pf_showInfo(0, 0, tBuf);
				}
			}

			//printLogChar("---------doSaveAv-----99999999999999-----", guid);
			if (!pMem->flag) {

				//printLogChar("----------------- audio in 4-----------------------");
				//
				pMem->idInfo.ui64Id = pSap->idInfo.ui64Id;
				pMem->tn_openAvDev = pSap->uiTranNo_openAvDev;

				//printLogChar("---------doSaveAv-----00000000000000-----", guid);

				//
				char  timeBuf[32];
				time_t  t;
				time(&t);
				g_pGuiOpen->pf_getTimelStr(t, timeBuf, mycountof(timeBuf));


				//auto now = std::chrono::high_resolution_clock::now();
				auto now = std::chrono::system_clock::now();
				auto duration_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
				int64_t milliseconds = duration_in_ms.count();

				auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
				auto value = now_ms.time_since_epoch().count();

				uint64_t milliseconds2 = GetCurrentTimeMsec();

				//
				_sntprintf(tName, mycountof(tName), _T("%s\\a_%I64u_%d_%lld-%S.mp3"), tmpDirName, pSap->idInfo.ui64Id,
					pSap->uiTranNo_openAvDev, milliseconds, timeBuf);
				_sntprintf(tNamePure, mycountof(tNamePure), _T("a_%I64u_%d_%lld-%S.mp3"), pSap->idInfo.ui64Id, pSap->uiTranNo_openAvDev,
					milliseconds, timeBuf);

				/*char* pBufAudioName = NULL;
				int nLenAudioName = 0;
				pBufAudioName = UnicodeToAnsi(tNamePure, nLenAudioName);*/

				std::string bufAudioName = UnicodeToANSI(tNamePure);

				strncpy(pMem->fileNamePure, bufAudioName.c_str(), mycountof(pMem->fileNamePure));
				pMem->flag = true;
				pMem->startTime = get_ms();
				pMem->firstTime = 0;
				pMem->count = 0;
				pMem->diff = pMem->startTime - pSave->video.startTime;

				client->SendAudioStart(bufRec.c_str(), pMem->fileNamePure);
				/*
				printLogChar("---------SendAudioStart----------begin---");
				printLogChar(pBufRec);
				printLogChar(pMem->fileNamePure);
				printLogChar("---------SendAudioStart----------end---");
				*/

				//
				_sntprintf(tBuf, mycountof(tBuf), _T("doSaveAv: a, fopen [%d]"), index_activeMems_from);
				g_pGuiOpen->pf_showInfo(0, 0, tBuf);
			}

			//printLogChar("---------doSaveAv-----aaaaaaaaaaaaaaaa-----", guid);

			//printLogChar("----------------- audio in 5-----------------------");

			//std::stringstream ss;
			//ss << "wFormatTag_file=" << wFormatTag_file;
			//printLogChar(ss.str().c_str());

			//printLogChar("----------------- audio in 5-----------end------------");

			//
			switch (wFormatTag_file) {
			case 0:
			case  WAVE_FORMAT_MPEGLAYER3:
				/*
				printLogChar("---------SendAudioData----------begin---");
				printLogCharU(pSap->uiSampleTimeInMs);
				printLogChar("---------SendAudioData----------end---");
				*/


				if (pSap->uiSampleTimeInMs != 0) {
					if (pMem->firstTime == 0) {
						pMem->firstTime = pSap->uiSampleTimeInMs;
						//pSap->uiSampleTimeInMs = pMem->startTime;
						pSap->uiSampleTimeInMs = pMem->diff;
					}
					else {
						//pSap->uiSampleTimeInMs = pMem->startTime + pSap->uiSampleTimeInMs - pMem->firstTime;
						pSap->uiSampleTimeInMs = pMem->diff + pSap->uiSampleTimeInMs - pMem->firstTime;
					}
				}

				//pSap->uiSampleTimeInMs = pMem->startTime - pSave->video.startTime + pMem->count * 36;
				//pMem->count++;
				 
				//if (!client->SendAudioData(bufRec.c_str(), pMem->fileNamePure, (unsigned char*)pSap->buf, pSap->uiLen,
				//	pSap->uiSampleTimeInMs, pSap->uiPts, orgSampleTimeInMs, qsize0, qsize1)) goto errLabel;
				
				client->SendAudioData(bufRec.c_str(), pMem->fileNamePure, (unsigned char*)pSap->buf, pSap->uiLen,
					pSap->uiSampleTimeInMs, pSap->uiPts, orgSampleTimeInMs, qsize0, qsize1);
					

				break;
			default:
				//showInfo_open(  0,  0,  _T(  ""))
				break;
			}

			//
			pMem->dwTickCnt_lastWrite = dwTickCnt;

			//
#if 0
			if (fp_a_test) {
				fclose(fp_a_test);  fp_a_test = nullptr;
			}
#endif


		}

		//
		continue;

	}

	//printLogChar("---------doSaveAv-----bbbbbbbbbbbbbbb-----", guid);

	iErr = 0;
errLabel:

	printLogChar("---------errLabel----------begin---", guid);
	printLogChar(bufRec.c_str(), guid);
	printLogChar("---------errLabel----------end---", guid);
	//

	//printLogChar("---------doSaveAv-----cccccccccccc-----", guid);

	
	if (client) {

		if (bIsStart) {

			if (pSaveParam->iType == 1) {
				client->SendRecordStop(bufRec.c_str());

				printLogChar("---------SendRecordStop----------begin---", guid);
				printLogChar(bufRec.c_str(), guid);
				printLogChar("---------SendRecordStop----------end---", guid);

				Sleep(1000 * 5);
			}
		
		}

		delete client;
		client = nullptr;
	}

	/*if (client) {
		delete client;
		client = nullptr;
	}*/

	printLogChar("--------------------------doSaveAv----------end---------------", guid);
	//
	return  iErr;
}


//  2015/02/17
//extern  "C"  __declspec(dllexport)  int  doSaveAv_new(SAVE_av_procInfo * pSaveParam, SAVE_av_pktU * pSp, BOOL * pbExists_pSvp, CTX_mc_saveAv * pCtx)
//{
//	int									iErr = -1;
//
//	//
//	mySAVE_av_procInfo* pSave = (mySAVE_av_procInfo*)pSaveParam;
//
//	//
//	unsigned  int  len;
//	TCHAR								tmpDirName[MAX_PATH] = _T("");
//	TCHAR								fileName[MAX_PATH] = _T("");
//	TCHAR								fileNamePure[MAX_PATH] = _T("");
//	char								timeBuf[CONST_qyTimeLen + 1];
//	char								buf[256] = "";
//	TCHAR								outputFileName[255] = _T("");
//	TCHAR								tBuf[256];
//
//	//TCHAR  tBuf[256];
//	HKEY hKeyRoot0 = HKEY_LOCAL_MACHINE;
//	unsigned  int  uiType = 0;
//	unsigned  int  size = sizeof(tBuf);
//	//
//	char  gwIp[64] = "";
//	int   gwPort = 0;
//	char  hgIp[64] = "";
//	int   hgPort = 0;
//
//	if (getCaServCfg(gwIp, sizeof(gwIp), &gwPort, hgIp, sizeof(hgIp), &hgPort) != 0) {
//		printLogChar("get hg ip failed");
//		g_pGuiOpen->pf_showInfo(0, 0, _T("get hg ip failed"));
//		return -1;
//	}
//	else {
//		printLogChar("--------hg ip -----begin-----");
//		printLogChar(hgIp);
//		printLogChar("--------hg ip -----end-----");
//	}
//
//	//const char* recIp = hgIp;// "10.0.1.135";
//	const char* recIp = "10.0.1.180";
//	int port = 12033;
//
//
//	printLogChar("doSaveAv in");
//
//	TcpClient* client = new TcpClient(recIp, port);
//	client->Initialize();
//	bool ret = client->Start(); 
//
//	if (!ret) {
//		_sntprintf(tBuf, mycountof(tBuf), _T("rec client start failed %s:%d"), recIp, port);
//		g_pGuiOpen->pf_showInfo(0, 0, tBuf);
//		printLogChar("rec client start failed");
//		goto  errLabel;
//	}
//	else {
//		printLogChar("rec client start success");
//	}
//	
//	//
//	
//	TCHAR* capScreenDir = _T("c:\\tttbbb\\124\\");
//	capScreenDir = pSave->common.tDir;
//
//	/*
//	if (!bDir(capScreenDir)) {
//		//
//		goto  errLabel;
//	}
//	_sntprintf(tmpDirName, mycountof(tmpDirName), _T("%s\\%s_tmp\\"), (capScreenDir), pSave->common.pureFileName_prefix);
//	if (!bDir(tmpDirName)) {
//		if (!CreateDirectory(tmpDirName, NULL)) {
//			int  tmperr = GetLastError();
//			//ERROR_ALREADY_EXISTS
//			goto  errLabel;
//		}
//	}
//	*/
//	//
//	_sntprintf(outputFileName, mycountof(outputFileName), _T("%s\\%s.mp4"), capScreenDir,  pSave->common.pureFileName_prefix);
//	lstrcpyn(pSave->common.fullOutputFileName, outputFileName, mycountof(pSave->common.fullOutputFileName));
//
//	char* pBufRec = NULL;
//	int nLenRec = 0;
//	pBufRec = UnicodeToAnsi(pSave->common.pureFileName_prefix, nLenRec);
//
//	client->SendRecordStart(pBufRec);
//
//	printLogChar("---------SendRecordStart----------begin---");
//	printLogChar(pBufRec);
//	printLogChar("---------SendRecordStart----------end---");
//
//	//
//	TCHAR								tName[128] = _T("");
//	TCHAR								tNamePure[128] = _T("");
//	
//
//	//
//	pSave->common.video.frame_cnt = 0;
//
//	//
//	int  i;
//	memset(&pSave->audio, 0, sizeof(pSave->audio));
//	memset(&pSave->video, 0, sizeof(pSave->video));
//	for (i = 0; i < mycountof(pSave->audio.aStreams.mems); i++) {
//		AStreamMem* pMem = &pSave->audio.aStreams.mems[i];
//		pMem->cache.bufSize = sizeof(pMem->cache.buf);
//	}
//	pSave->video.cache.bufSize = sizeof(pSave->video.cache.buf);
//
//	//
//	DWORD  dwTickCnt_start = GetTickCount();
//	DWORD  dwTickCnt_flush = 0;
//
//	//
//	for (; ; ) {
//
//		if (pSave->common.bQuit
//			&& isQ2Empty(&pSave->common.q2))
//		{
//			break;
//		}
//
//
//		//
//		if (1) {
//			//g_pGuiOpen->pf_showInfo(0, 0, _T("doSaveAv"));
//		}
//
//		//
//		len = sizeof(SAVE_av_pktU);
//		if (g_pGuiOpen->pf_q2GetMsg(&pSave->common.q2, pSp, &len, _T("doSaveAv"))) {
//			Sleep(100);
//			continue;
//		}
//
//
//#ifdef  _DEBUG
//		//traceLog(_T("saveThread: svp->uiLen %d, len %d "), pSvp->uiLen, len);
//#endif
//
//		//		
//		if (!pSp->common.bAudio) {
//
//			//
//			SAVE_video_pkt* pSvp = &pSp->vPkt;
//			int								iFourcc_file = 0;
//
//			iFourcc_file = pSvp->iFourcc;
//			//
//			if (!pSave->video.flag) {
//
//				iFourcc_file = pSp->vPkt.iFourcc;// CONST_fourcc_h264;
//				//
//				lstrcpyn(tName, _T("v_"), mycountof(tName));
//				//
//				switch (iFourcc_file) {
//				case  CONST_fourcc_h264:
//					_sntprintf(fileName, mycountof(fileName), _T("%s%s.264"), tmpDirName, tName);
//					_sntprintf(fileNamePure, mycountof(fileNamePure), _T("%s.264"), tName);
//					break;
//				case  CONST_fourcc_HEVC:
//					_sntprintf(fileName, mycountof(fileName), _T("%s%s.265"), tmpDirName, tName);
//					_sntprintf(fileNamePure, mycountof(fileNamePure), _T("%s.265"), tName);
//					break;
//				default:
//					//
//					char  fourccStr[4 + 1];
//					TCHAR  tBuf[128];
//					iFourcc2Str(iFourcc_file, fourccStr, mycountof(fourccStr));
//					_sntprintf(tBuf, mycountof(tBuf), _T("doSaveAv failed: %S not supported"), (fourccStr));
//					g_pGuiOpen->pf_showInfo(0, 0, tBuf);
//					goto  errLabel;
//					break;
//				}
//
//				//
//				{
//					time_t  t;
//					time(&t);
//					pSave->video.tStartToSave = t;
//					lstrcpyn(pSave->video.fileName, fileName, mycountof(pSave->video.fileName));
//					//lstrcpyn(pSave->video.fileNamePure, fileNamePure, mycountof(pSave->video.fileNamePure));
//				}
//
//				char* pBufVideoName = NULL;
//				int nLenvideoName = 0;
//				pBufVideoName = UnicodeToAnsi(fileNamePure, nLenvideoName);
//				strncpy(pSave->video.fileNamePure, pBufVideoName, mycountof(pSave->video.fileNamePure));
//
//				client->SendVideoStart(pBufRec, pBufVideoName);
//				pSave->video.flag = true;
//
//				printLogChar("---------SendVideoStart----------begin---");
//				printLogChar(pBufRec);
//				printLogChar(pBufVideoName);
//				printLogChar("---------SendVideoStart----------end---");
//
//			}
//
//
//			//
//			switch (iFourcc_file) {
//			case  CONST_fourcc_h264:
//			case  CONST_fourcc_HEVC:
//				//
//				TCHAR  tBuf[128];
//				_sntprintf(tBuf, mycountof(tBuf), _T("doSaveAv: %d bytes\n"), pSvp->uiLen);
//				OutputDebugString(tBuf);
//
//				if (!client->SendVideoData(pBufRec, pSave->video.fileNamePure, (unsigned char*)pSvp->buf, pSvp->uiLen, 0, 0, 0)) goto errLabel;
//				break;
//
//			default:
//				goto  errLabel;
//				break;
//			}
//
//			//
//			pSave->common.video.frame_cnt++;
//
//		}
//		else {
//			SAVE_audio_pkt* pSap = &pSp->aPkt;
//			WORD			wFormatTag_file = 0;
//
//			wFormatTag_file = pSap->wFormatTag;
//
//			//
//			int  index_activeMems_from = pSap->index_activeMems_from;
//			if (index_activeMems_from < 0 || index_activeMems_from >= mycountof(pSave->audio.aStreams.mems)) {
//				g_pGuiOpen->pf_showInfo(0, 0, _T("doSaveAv: index_activeMems_from err"));
//				continue;
//			}
//
//			//
//			DWORD  dwTickCnt = GetTickCount();
//
//			//
//			AStreamMem* pMem = &pSave->audio.aStreams.mems[index_activeMems_from];
//			if (pMem->flag) {
//				int iDiffInMs = dwTickCnt - pMem->dwTickCnt_lastWrite;
//				//
//				if (pMem->idInfo.ui64Id != pSap->idInfo.ui64Id
//					|| pMem->tn_openAvDev != pSap->uiTranNo_openAvDev
//					||  abs(iDiffInMs)>1000  )
//				{
//					if (pMem->cache.uiLen) {
//						client->SendAudioData(pBufRec, pMem->fileNamePure, (unsigned char*)pMem->cache.buf, pMem->cache.uiLen, 0, 0, 0);
//						pMem->cache.uiLen = 0;						
//					}
//					pMem->flag = false;
//					_sntprintf(tBuf, mycountof(tBuf), _T("doSaveAv: a, fclose [%d]"), index_activeMems_from);
//					g_pGuiOpen->pf_showInfo(0, 0, tBuf);
//				}
//			}
//			if (!pMem->flag) {
//				//
//				pMem->idInfo.ui64Id = pSap->idInfo.ui64Id;
//				pMem->tn_openAvDev = pSap->uiTranNo_openAvDev;
//
//				//
//				char  timeBuf[32];
//				time_t  t;
//				time(&t);
//				g_pGuiOpen->pf_getTimelStr(t, timeBuf, mycountof(timeBuf));
//				
//				//
//				_sntprintf(tName, mycountof(tName), _T("%s\\a_%I64u_%d-%S.mp3"), tmpDirName, pSap->idInfo.ui64Id, pSap->uiTranNo_openAvDev,  timeBuf);
//				_sntprintf(tNamePure, mycountof(tNamePure), _T("a_%I64u_%d-%S.mp3"), pSap->idInfo.ui64Id, pSap->uiTranNo_openAvDev, timeBuf);
//
//				char* pBufAudioName = NULL;
//				int nLenAudioName = 0;
//				pBufAudioName = UnicodeToAnsi(tNamePure, nLenAudioName);
//				strncpy(pMem->fileNamePure, pBufAudioName, mycountof(pMem->fileNamePure));
//				pMem->flag = true;
//
//				client->SendAudioStart(pBufRec, pMem->fileNamePure);
//
//				printLogChar("---------SendAudioStart----------begin---");
//				printLogChar(pBufRec);
//				printLogChar(pMem->fileNamePure);
//				printLogChar("---------SendAudioStart----------end---");		
//
//				//
//				_sntprintf(tBuf, mycountof(tBuf), _T("doSaveAv: a, fopen [%d]"), index_activeMems_from);
//				g_pGuiOpen->pf_showInfo(0, 0, tBuf);
//			}
//
//			//
//			switch (wFormatTag_file) {
//			case  WAVE_FORMAT_MPEGLAYER3:
//				if (!client->SendAudioData(pBufRec, pMem->fileNamePure, (unsigned char*)pSap->buf, pSap->uiLen, 0, 0, 0)) goto errLabel;
//
//				break;
//			default:
//				//showInfo_open(  0,  0,  _T(  ""))
//				break;
//			}
//
//			//
//			pMem->dwTickCnt_lastWrite = dwTickCnt;
//
//			//
//#if 0
//			if (fp_a_test) {
//				fclose(fp_a_test);  fp_a_test = nullptr;
//			}
//#endif
//
//
//		}
//
//		//
//		continue;
//
//	}
//
//	iErr = 0;
//errLabel:
//	
//	printLogChar("---------errLabel----------begin---");
//	printLogChar(pBufRec);
//	printLogChar("---------errLabel----------end---");
//	//
//	
//
//	 if (client) {
//		 client->SendRecordStop(pBufRec);
//
//		 printLogChar("---------SendRecordStop----------begin---");
//		 printLogChar(pBufRec);
//		 printLogChar("---------SendRecordStop----------end---");
//
//		 Sleep(1000 * 5);
//
//		 delete client;
//		 client = nullptr;
//	 }
//
//	 //
//	 return  iErr;
//}



//  2015/02/17
extern  "C"  __declspec(dllexport)  int  doSaveAv_bak(SAVE_av_procInfo * pSaveParam, SAVE_av_pktU * pSp, BOOL * pbExists_pSvp, CTX_mc_saveAv * pCtx)
{
	int									iErr = -1;

	//
	mySAVE_av_procInfo* pSave = (mySAVE_av_procInfo*)pSaveParam;

	//
	unsigned  int  len;
	TCHAR								tmpDirName[MAX_PATH] = _T("");
	TCHAR								fileName[MAX_PATH] = _T("");
	char								timeBuf[CONST_qyTimeLen + 1];
	char								buf[256] = "";
	TCHAR								outputFileName[255] = _T("");
	
	//
	TCHAR* capScreenDir = _T("c:\\tttbbb\\124\\");
	capScreenDir = pSave->common.tDir;
	if (!bDir(capScreenDir)) {
		//
		goto  errLabel;
	}
	_sntprintf(tmpDirName, mycountof(tmpDirName), _T("%s\\%s_tmp\\"), (capScreenDir), pSave->common.pureFileName_prefix);
	if (!bDir(tmpDirName)) {
		if (!CreateDirectory(tmpDirName, NULL)) {
			int  tmperr = GetLastError();
			//ERROR_ALREADY_EXISTS
			goto  errLabel;
		}
	}
	//
	_sntprintf(outputFileName, mycountof(outputFileName), _T("%s\\%s.mp4"), capScreenDir,  pSave->common.pureFileName_prefix);
	lstrcpyn(pSave->common.fullOutputFileName, outputFileName, mycountof(pSave->common.fullOutputFileName));

	//
	TCHAR								tName[128] = _T("");
	TCHAR								tBuf[256];

	//
	pSave->common.video.frame_cnt = 0;

	//
	int  i;
	memset(&pSave->audio, 0, sizeof(pSave->audio));
	memset(&pSave->video, 0, sizeof(pSave->video));
	for (i = 0; i < mycountof(pSave->audio.aStreams.mems); i++) {
		AStreamMem* pMem = &pSave->audio.aStreams.mems[i];
		pMem->cache.bufSize = sizeof(pMem->cache.buf);
	}
	pSave->video.cache.bufSize = sizeof(pSave->video.cache.buf);

	//
	DWORD  dwTickCnt_start = GetTickCount();
	DWORD  dwTickCnt_flush = 0;

	//
	for (; ; ) {

		if (pSave->common.bQuit
			&& isQ2Empty(&pSave->common.q2))
		{
			break;
		}


		//
		if (1) {
			//g_pGuiOpen->pf_showInfo(0, 0, _T("doSaveAv"));
		}

		//
		len = sizeof(SAVE_av_pktU);
		if (g_pGuiOpen->pf_q2GetMsg(&pSave->common.q2, pSp, &len, _T("doSaveAv"))) {
			Sleep(100);
			continue;
		}


#ifdef  _DEBUG
		//traceLog(_T("saveThread: svp->uiLen %d, len %d "), pSvp->uiLen, len);
#endif



		//		
		if (!pSp->common.bAudio) {

			//
			SAVE_video_pkt* pSvp = &pSp->vPkt;
			int								iFourcc_file = 0;

			iFourcc_file = pSvp->iFourcc;
			//
			if (!pSave->video.fp) {

				//
				//iFourcc_file  =  pSave->video.tv.vh_compress.bih.biCompression;	 
				//if  (  iFourcc_file  ==  CONST_fourcc_vp8_bad  )  iFourcc_file  =  CONST_fourcc_vp80;
				iFourcc_file = pSp->vPkt.iFourcc;// CONST_fourcc_h264;
				//
				lstrcpyn(tName, _T("v_"), mycountof(tName));
				//
				switch (iFourcc_file) {
				case  CONST_fourcc_h264:
					_sntprintf(fileName, mycountof(fileName), _T("%s%s.264"), tmpDirName, tName);
					break;
				case  CONST_fourcc_HEVC:
					_sntprintf(fileName, mycountof(fileName), _T("%s%s.265"), tmpDirName, tName);
					break;
				default:
					//
					char  fourccStr[4 + 1];
					TCHAR  tBuf[128];
					iFourcc2Str(iFourcc_file, fourccStr, mycountof(fourccStr));
					_sntprintf(tBuf, mycountof(tBuf), _T("doSaveAv failed: %S not supported"), (fourccStr));
					g_pGuiOpen->pf_showInfo(0, 0, tBuf);
					goto  errLabel;
					break;
				}

				//
				{
					time_t  t;
					time(&t);
					pSave->video.tStartToSave = t;
					lstrcpyn(pSave->video.fileName, fileName, mycountof(pSave->video.fileName));
				}

				//
				pSave->video.fp = _tfopen(fileName, _T("wb"));
				if (!pSave->video.fp) {
					goto  errLabel;
				}
			}


			//
			switch (iFourcc_file) {
			case  CONST_fourcc_h264:
			case  CONST_fourcc_HEVC:
				//
				TCHAR  tBuf[128];
				_sntprintf(tBuf, mycountof(tBuf), _T("doSaveAv: %d bytes\n"), pSvp->uiLen);
				OutputDebugString(tBuf);
				//
				//  dumpVideo(  dirName,  fileName,  pSvp->buf,  pSvp->uiLen  );
				//if (fwrite(pSvp->buf, pSvp->uiLen, 1, pSave->video.fp) != 1)  goto  errLabel;
				if (saveAv_v_fwrite(pSvp->buf, pSvp->uiLen, 1, pSave))  goto  errLabel;
				break;

			default:
				goto  errLabel;
				break;
			}

			//
			pSave->common.video.frame_cnt++;

		}
		else {
			SAVE_audio_pkt* pSap = &pSp->aPkt;
			WORD								wFormatTag_file = 0;

			wFormatTag_file = pSap->wFormatTag;

			//
			int  index_activeMems_from = pSap->index_activeMems_from;
			if (index_activeMems_from < 0 || index_activeMems_from >= mycountof(pSave->audio.aStreams.mems)) {
				g_pGuiOpen->pf_showInfo(0, 0, _T("doSaveAv: index_activeMems_from err"));
				continue;
			}

			//
			DWORD  dwTickCnt = GetTickCount();

			//
			AStreamMem* pMem = &pSave->audio.aStreams.mems[index_activeMems_from];
			if (pMem->fp) {
				int iDiffInMs = dwTickCnt - pMem->dwTickCnt_lastWrite;
				//
				if (pMem->idInfo.ui64Id != pSap->idInfo.ui64Id
					|| pMem->tn_openAvDev != pSap->uiTranNo_openAvDev
					||  abs(iDiffInMs)>1000  )
				{
					saveAv_a_fclose(pMem);  pMem->fp = nullptr;
					//
					_sntprintf(tBuf, mycountof(tBuf), _T("doSaveAv: a, fclose [%d]"), index_activeMems_from);
					g_pGuiOpen->pf_showInfo(0, 0, tBuf);
				}
			}
			if (!pMem->fp) {
				//
				pMem->idInfo.ui64Id = pSap->idInfo.ui64Id;
				pMem->tn_openAvDev = pSap->uiTranNo_openAvDev;

				//
				char  timeBuf[32];
				time_t  t;
				time(&t);
				g_pGuiOpen->pf_getTimelStr(t, timeBuf, mycountof(timeBuf));
				
				//
				_sntprintf(tName, mycountof(tName), _T("%s\\a_%I64u_%d-%S.mp3"), tmpDirName, pSap->idInfo.ui64Id, pSap->uiTranNo_openAvDev,  timeBuf);
				pMem->fp = _tfopen(tName, _T("ab"));
				if (!pMem->fp) {
					goto  errLabel;
				}

				//
				_sntprintf(tBuf, mycountof(tBuf), _T("doSaveAv: a, fopen [%d]"), index_activeMems_from);
				g_pGuiOpen->pf_showInfo(0, 0, tBuf);
			}

			//
			switch (wFormatTag_file) {
			case  WAVE_FORMAT_MPEGLAYER3:
				//
				//if (fwrite(pSap->buf, pSap->uiLen, 1, pMem->fp) != 1)  goto  errLabel;
				if (saveAv_a_fwrite(pSap->buf, pSap->uiLen, 1, pMem) )  goto  errLabel;

				break;
			default:
				//showInfo_open(  0,  0,  _T(  ""))
				break;
			}

			//
			pMem->dwTickCnt_lastWrite = dwTickCnt;

			//
#if 0
			if (fp_a_test) {
				fclose(fp_a_test);  fp_a_test = nullptr;
			}
#endif


		}



		//
		continue;

	}

	iErr = 0;
errLabel:

	//
	for (i = 0; i < mycountof(pSave->audio.aStreams.mems); i++) {
		AStreamMem* pMem = &pSave->audio.aStreams.mems[i];
		if (pMem->fp) {
			saveAv_a_fclose(pMem); pMem->fp = nullptr;
		}
	}

	 //
	 if  (  pSave->video.fp  )  {
		 //fclose(  pSave->video.fp  );  pSave->video.fp  =  NULL;
		 saveAv_v_fclose(pSave);
	 }

	 //	 
	 mixFiles(pSave,  tmpDirName, outputFileName);

	 //
	 if (bDir(tmpDirName)) {
		 RemoveDirectory(tmpDirName);
		 _sntprintf(tBuf, mycountof(tBuf), _T("remove dir %s"), tmpDirName);
		 g_pGuiOpen->pf_showInfo(0, 0, tBuf);
	 }

	 //
	 return  iErr;
}

//
#define		CONST_tmp0			_T(  "tmp0.mp3"  )
//#define		CONST_tmp1			_T(  "tmp1.mp3"  )
#define		CONST_tmp_o			_T(  "tmp_o.mp3"  )

//
typedef  struct {
	TCHAR  fileName[256];

}  Param_enumFile;

//
int  tmp_enumFile_a(void* p0, void* p1, TmpFileResult* pResult)
{
	//
	Param_enumFile* pParam = (Param_enumFile*)p1;

	//
	TCHAR  tBuf[256];

	//
	if (bDir(pResult->fileName)) {
		return  0;
	}

	//
	if (!_tcsicmp(pResult->fileName, CONST_tmp0)
		|| !_tcsicmp(pResult->fileName, CONST_tmp_o))
	{
		return  0;
	}

	//
	if (pResult->fileName[0] != _T('a')) {
		return  0;
	}

	//
#ifdef  _DEBUG
	if (0) {
		_sntprintf(tBuf, mycountof(tBuf), _T("find [%s]\n"), pResult->fileName);
		OutputDebugString(tBuf);
	}
#endif
	
	//
	lstrcpyn(pParam->fileName, pResult->fileName, mycountof(pParam->fileName));

	//
	return  1;
}


int  get_a_t(TCHAR* fileName, time_t  *  pt_o)
{
	time_t  t;
	char  buf[128];

	TCHAR* pT = _tcschr(fileName, _T('-'));
	if (pT) {
		pT++;
		myTChar2Utf8(pT, buf, mycountof(buf));
		buf[CONST_qyTimeLen] = 0;
		*pt_o=g_pGuiOpen->pf_gettTimeBylStr(buf);
	}

	return  0;
}


//
typedef  struct  __param_tool_t {
				 HANDLE			hProcess_vt;
}		 Param_tool;



//
//
int  tmp_createTool(Param_tool* pVtProcess, TCHAR  *  cmdLine,  LPCTSTR  hint)
{
	int			iErr = -1;

	//
	STARTUPINFO				si;
	PROCESS_INFORMATION		pi;
	BOOL						bProcessCreated = FALSE;
	TCHAR						tmpExeName[MAX_PATH + 1] = _T("");

	//
	if (pVtProcess->hProcess_vt)  return  0;

	//
	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));

	//traceLogA((char*)"Now start qwm ");
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
#if  0
	si.dwFlags = STARTF_USESHOWWINDOW;	//
	si.wShowWindow = SW_HIDE;
#endif
	si.dwFlags = STARTF_FORCEOFFFEEDBACK;

	//
	TCHAR* toolName = (TCHAR*)_T("");


	//
	DWORD  dwCreationFlags = CREATE_NO_WINDOW;
#ifdef  _DEBUG
	if (0) {
		dwCreationFlags = 0;
	}
#endif

	//
	if (!CreateProcess(NULL, cmdLine, NULL, NULL, 0, dwCreationFlags, NULL, NULL, &si, &pi))  goto  errLabel;
	bProcessCreated = TRUE;




	//
	iErr = 0;

errLabel:

	if (bProcessCreated) {
		if (pi.hThread) { CloseHandle(pi.hThread);  pi.hThread = NULL; }
		if (pi.hProcess)  pVtProcess->hProcess_vt = pi.hProcess;
	}

	if (iErr) {
		//qyShowInfo(pQyMc->pShowInfoStruct, CONST_qyShowType_qwmComm, 0, (char*)"", _T("IsClient"), 0, _T(""), _T(""), _T("createVt failed, %s"), tmpExeName);
	}

	return  iErr;

}


//int  closeDvt(  MC_VAR_common  *  pProcInfo,  DVT_cli  *  pDvtCli  )
int  tmp_closeTool(Param_tool* pVtProcess, int nWaitsInS)
{
	int  iErr = -1;
	
	DWORD  dwRet;
	//
	int  i;

	if (!pVtProcess->hProcess_vt)  return  0;


	//	
	for (i = 0; i < nWaitsInS; i++) {
		//
	
		//
		dwRet = WaitForSingleObject(pVtProcess->hProcess_vt, 1000);
		if (dwRet != WAIT_FAILED && dwRet != WAIT_TIMEOUT) {
			CloseHandle(pVtProcess->hProcess_vt);  pVtProcess->hProcess_vt = NULL;
			//
			g_pGuiOpen->pf_showInfo(0, 0, _T("vt waited"));
			//
			break;
		}
	}
	if (i >= nWaitsInS) {
		g_pGuiOpen->pf_showInfo(0, 0, _T("closeVt:too long to wait, terminate vt"));
		TerminateProcess(pVtProcess->hProcess_vt, -1);
	}

	//	
	if (pVtProcess->hProcess_vt) {	//  即使没回收，也要关闭了
#ifdef  __DEBUG__
		myMessageBox(NULL, _T("即使没回收，也要关闭了. 这里没做好，应该rtspCli赶紧退出的"), 0, 0);
#endif
		//
		CloseHandle(pVtProcess->hProcess_vt);  pVtProcess->hProcess_vt = NULL;
	}

	iErr = 0;

errLabel:

	return  iErr;
}




//
 int mixFiles(mySAVE_av_procInfo  *  pSave,  TCHAR* tmpDir, TCHAR* mixFileName)
{
	int  iErr = -1;
	bool  bExists_a = false;
	int  tmpiRet;
	int  i;
	int maxWaits = 45;// 30;

	//
	g_pGuiOpen->pf_showInfo(0, 0, _T("mixFiles enters"));

	//
	TCHAR* ffmpeg = _T("c:\\tttbbb\\124\\ffmpeg.exe");
	ffmpeg = pSave->common.ffmpegPath;


	//
	TCHAR  fullTmp0[256]  =  _T(  ""  );
	TCHAR  fullTmp_o[256] = _T("");
	//
	TCHAR  tmp_a[256];
	time_t t_tmp_a = 0;
	TCHAR  cmdBuf[1024];

	//
	_sntprintf(fullTmp0, mycountof(fullTmp0), _T("%s\\%s"), tmpDir, CONST_tmp0);
	_sntprintf(fullTmp_o, mycountof(fullTmp_o), _T("%s\\%s"), tmpDir, CONST_tmp_o);

	//
	//return  0;

	//
	Param_enumFile param = { 0 };
	enumUsrDir_open(tmpDir, tmp_enumFile_a, 0, &param);
	if (param.fileName[0]) {
		bExists_a = true;
		//
		get_a_t(param.fileName, &t_tmp_a);
		_sntprintf(tmp_a, mycountof(tmp_a), _T("%s\\%s"), tmpDir, param.fileName);

		//
		int nDelayInS = t_tmp_a - pSave->video.tStartToSave;
		//
		_sntprintf(cmdBuf, mycountof(cmdBuf), _T("%s -i %s -filter_complex \"[0]adelay = delays = %ds:all = 1[aud0]; [aud0] amix = inputs = 1:normalize = 0\" -vsync 1 -y  %s"),
			ffmpeg,
			tmp_a, nDelayInS, fullTmp_o);
		Param_tool  pt;
		memset(&pt, 0, sizeof(pt));
		tmp_createTool(&pt,cmdBuf,_T(""));
		tmp_closeTool(&pt, maxWaits);

		//
		MoveFile(fullTmp_o, fullTmp0);
		DeleteFile(tmp_a);
	}

	if (bExists_a) {
		for (  i=0; i<  5000;  i  ++ ) {
			memset(&param, 0, sizeof(param));
			enumUsrDir_open(tmpDir, tmp_enumFile_a, 0, &param);
			if (!param.fileName[0]) {
				break;
			}
			//
			get_a_t(param.fileName, &t_tmp_a);
			_sntprintf(tmp_a, mycountof(tmp_a), _T("%s\\%s"), tmpDir, param.fileName);

			//
			int nDelayInS = t_tmp_a - pSave->video.tStartToSave;
			
			//
			_sntprintf(cmdBuf, mycountof(cmdBuf), _T("%s -i %s -i %s -filter_complex \"[0]adelay=delays=0s:all=1[aud0];[1]adelay=delays=%ds:all=1[aud1];[aud0][aud1]amix=inputs=2:normalize=0\" -vsync 2 -y  %s"),
				ffmpeg,
				fullTmp0, tmp_a, nDelayInS, fullTmp_o);

			Param_tool  pt;
			memset(&pt, 0, sizeof(pt));
			tmp_createTool(&pt, cmdBuf, _T(""));
			tmp_closeTool(&pt, maxWaits);

			//
			DeleteFile(fullTmp0);
			MoveFile(fullTmp_o, fullTmp0);
			DeleteFile(tmp_a);

			//
			continue;
		}
	}

	//
	if (bExists_a) {
		_sntprintf(cmdBuf, mycountof(cmdBuf), _T("%s -i %s -i %s -vcodec copy -acodec copy %s"),
			ffmpeg,
			pSave->video.fileName, fullTmp0, pSave->common.fullOutputFileName);

		Param_tool  pt;
		memset(&pt, 0, sizeof(pt));
		tmp_createTool(&pt, cmdBuf, _T(""));
		tmp_closeTool(&pt, maxWaits);

		//
		DeleteFile(fullTmp0);

	}
	else {
		//.\ffmpeg.exe - f h264 - i ..\vvv\dump.264 - vcodec copy ..\vvv\out.mp4
		//_sntprintf(cmdBuf, mycountof(cmdBuf), _T("%s -f h264 -i %s -vcodec copy %s"),
		_sntprintf(cmdBuf, mycountof(cmdBuf), _T("%s -i %s -vcodec copy %s"),
			ffmpeg,
			pSave->video.fileName, pSave->common.fullOutputFileName);

		Param_tool  pt;
		memset(&pt, 0, sizeof(pt));
		tmp_createTool(&pt, cmdBuf, _T(""));
		tmp_closeTool(&pt, maxWaits);

	}

	//
	DeleteFile(pSave->video.fileName);

	//
	iErr = 0;
errLabel:

	//
	g_pGuiOpen->pf_showInfo(0, 0, _T("mixFiles leaves"));

	return  iErr;
}



