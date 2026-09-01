

#include	"stdafx.h"
#include	<tchar.h>
#include	"hk3ddw.h"
#include <stdio.h>
#include <ctxQmThread.h>
#include <showInfo_open.h>

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <windows.h>
//
Hk3ddwProc  gBuf_hk3ddw;


#include <stdio.h>
#include <tchar.h>

char* UnicodeToAnsi(const wchar_t* szStr, int& nLen)
{
	nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);
	return pResult;
}


#include <chrono>
#include <sstream>
#include <iomanip>
#include <string>

#define LOG_FILE "D:/qycx/hik3d.txt"
#define LOG_FILE_W L"D:/qycx/hik3d.txt"

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



int printLogChar(const char* log) {
	//return 0;
	if (gBuf_hk3ddw.m_var.appParams.log == 0)
		return 0;

	FILE* pf = fopen("D:/qycx/hik3d.txt", "a+");
	if (pf == NULL)
	{
		perror("打开文件失败！");
		return 1;
	}

	//TCHAR* pp;


	//fprintf(pf, "%s:%s  - %s \n", __DATE__, __TIME__, log);
	fprintf(pf, "[%s]  - %s \n", getDT().c_str(), log);

	fclose(pf);

	return 0;

}

int printLogChar(int log) {
	//return 0;
	if (gBuf_hk3ddw.m_var.appParams.log == 0)
		return 0;
 

	FILE* pf = fopen("D:/qycx/hik3d.txt", "a+");
	if (pf == NULL)
	{
		perror("打开文件失败！");
		return 1;
	}

	//TCHAR* pp;


	//fprintf(pf, "%s:%s  - %s \n", __DATE__, __TIME__, log);
	fprintf(pf, "[%s]  - %d \n", getDT().c_str(), log);

	fclose(pf);

	return 0;

}

int printLogChar(const char* des, int log) {
	//return 0;
	if (gBuf_hk3ddw.m_var.appParams.log == 0)
		return 0;


	FILE* pf = fopen("D:/qycx/hik3d.txt", "a+");
	if (pf == NULL)
	{
		perror("打开文件失败！");
		return 1;
	}

	//TCHAR* pp;


	//fprintf(pf, "%s:%s  - %s \n", __DATE__, __TIME__, log);
	fprintf(pf, "[%s]  - %s: %d \n", getDT().c_str(), des, log);

	fclose(pf);

	return 0;

}

void get_current_time_with_ms(char* time_str, int size) {
	SYSTEMTIME st;
	GetLocalTime(&st);
	sprintf_s(time_str, size, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
		st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
}


void my_printlog(const char* format, ...) {
	FILE* log_file = NULL;
	char time_str[24];
	va_list args;

	get_current_time_with_ms(time_str, sizeof(time_str));

	fopen_s(&log_file, LOG_FILE, "a, ccs=UTF-8"); // 使用UTF-8编码
	if (log_file == NULL) {
		//printf("Error: Cannot open log file %s\n", LOG_FILE);
		return;
	}

	fprintf(log_file, "[%s] ", time_str);

	va_start(args, format);
	vfprintf(log_file, format, args);
	va_end(args);

	fprintf(log_file, "\n");
	fclose(log_file);
}


void my_printlog_w(const wchar_t* format, ...) {
	FILE* log_file = NULL;
	wchar_t time_str[24];
	SYSTEMTIME st;
	va_list args;


	GetLocalTime(&st);
	swprintf_s(time_str, 24, L"%04d-%02d-%02d %02d:%02d:%02d.%03d",
		st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);


	_wfopen_s(&log_file, LOG_FILE_W, L"a, ccs=UTF-8");
	if (log_file == NULL) {
		//wprintf(L"Error: Cannot open log file\n");
		return;
	}

	fwprintf(log_file, L"[%ls] ", time_str);

	va_start(args, format);
	vfwprintf(log_file, format, args);
	va_end(args);

	fwprintf(log_file, L"\n");
	fclose(log_file);
}


int printLog(const wchar_t* log) {
	//return 0;

	if (gBuf_hk3ddw.m_var.appParams.log == 0)
		return 0;
	
	FILE* pf = fopen("D:\\qycx\\hik3d.txt", "a+");
	if (pf == NULL)
	{
		perror("打开文件失败！");
		return 1;
	}

	//TCHAR* pp;

	char* pBuf = NULL;
	int nLen = 0;

	pBuf = UnicodeToAnsi(log, nLen);

	if (pBuf) {
		fprintf(pf, "[%s]  - %s \n", getDT().c_str(), pBuf);
		delete[] pBuf;
	}

	fclose(pf);

}

//
int  hk3ddw_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
{
	int  iErr = -1;
	unsigned  int    dwByte = msgLen;
	//	
	TCHAR  tBuf[128];

	//	
	if (dwByte < sizeof(OnvifMsg_common)) {
		//dyn_showInfo_open(0, 0, _T("pipeThread_cli err: read too small bytes < sizeof(  Onvif_msg_common  )"));
		return  -1;
	}
#if 0
	if (dwByte > gBuf_dhListIp.m_var.uiSize_pOnvifMsgBuf)
	{
		_sntprintf(tBuf, mycountof(tBuf), _T("onvifMsgBuf too small, dwByte %d > size_msgBuf %d"), dwByte, gBuf_dhListIp.m_var.uiSize_pOnvifMsgBuf);
		//dyn_showInfo_open(0, 0, tBuf);
		return  -1;
	}
#endif


	//
	//gBuf_dh.status.dwTickCnt_lastMsg = GetTickCount();

	//
	OnvifMsg_common* pMsgCommon = (OnvifMsg_common*)pMsg;
	if (pMsgCommon->uiType != CONST_qisMsgType_onvif)  return  -1;

	//
	Hk3ddwProc* pGBuf = &gBuf_hk3ddw;
	pGBuf->m_var.dwLastTickCnt_recvd = myGetTickCount(nullptr);

	//
	//
	switch (pMsgCommon->iSubtype) {
	case  CONST_onvifMsg_subtype_dbg:
	{
		OnvifMsg_dbg* pDbg = (OnvifMsg_dbg*)pMsgCommon;
		OnvifMsg_dbg  m = { 0 };
		m.uiType = CONST_qisMsgType_onvif;
		m.iSubtype = CONST_onvifMsg_subtype_dbg;
		_snprintf(m.buf, mycountof(m.buf), "dhListIp recvd: %s", pDbg->buf);
		qisPipe_writeMsg(&m, sizeof(m), pGBuf->m_var.pQisPipe);

	}
	break;
	case  CONST_onvifMsg_subtype_ping:
	{
		if (0) {
			showInfo_open0(0, 0, _T("listIp: recv ping"));
		}

		//
		//hk_do3ddw();

	}
	break;

	case  CONST_onvifMsg_subtype_nvrInfo:
	{

		//
		if (!pGBuf->m_var.m_bGot_nvrInfo) {
			break;
		}

		//
#ifdef  _DEBUG
		_sntprintf(tBuf, mycountof(tBuf), _T("dhListIp: get nvrInfo req, cnt %d and send back resp"), (int)pGBuf->m_var.nvrInfo.usCnt);
		showInfo_open0(0, 0, tBuf);
#endif

		//
		OnvifMsg_nvrInfo m = { 0 };
		m.uiType = CONST_qisMsgType_onvif;
		m.iSubtype = CONST_onvifMsg_subtype_nvrInfo;
		m.ucbResp = true;
		m.nvrInfo = pGBuf->m_var.nvrInfo;
		//
		qisPipe_writeMsg(&m, sizeof(m), pGBuf->m_var.pQisPipe);
		//
		//gBuf_dhListIp.m_var.m_bDone_nvrInfo = true;
		//
	}
	break;

	case  CONST_onvifMsg_subtype_ptz:
	{
		OnvifMsg_ptz* pPtz = (OnvifMsg_ptz*)pMsgCommon;

		printLogChar("----hk3ddw_qisPipe_onRead----CONST_onvifMsg_subtype_ptz-----");

		//
		_sntprintf(tBuf, mycountof(tBuf), _T("hk3ddw00: channel %d, ptz cmd %d, wh %dX%d, top %d,%d, bottom %d,%d"), (int)pPtz->iChannel, (int)pPtz->ucCmd,
			(int)pPtz->paramU.param3ddw.sW_video,  (int)pPtz->paramU.param3ddw.sH_video,  
			(int)pPtz->paramU.param3ddw.xTop,  (int)pPtz->paramU.param3ddw.yTop, (int)pPtz->paramU.param3ddw.xBottom,(int)pPtz->paramU.param3ddw.yBottom);

		

		//
		showInfo_open0(0, 0, tBuf);
		printLog(tBuf);	

		hk_do3ddw(pPtz->iChannel, pPtz->paramU.param3ddw.sW_video, pPtz->paramU.param3ddw.sH_video, pPtz->paramU.param3ddw.xTop, pPtz->paramU.param3ddw.yTop,
			pPtz->paramU.param3ddw.xBottom, pPtz->paramU.param3ddw.yBottom);		

	}
	break;


	default:
		//dyn_showInfo_open(0, 0, _T("onvifCli_qisPipe_onRead: unprocessed subtype"));
		break;
	}


	//
	iErr = 0;

errLabel:

	//
	return  iErr;
}






