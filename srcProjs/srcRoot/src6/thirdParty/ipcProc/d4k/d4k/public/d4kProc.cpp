

#include	"stdafx.h"
#include    "d4kProc.h"
#include <qisOnvifCommProc_open.h>
#include <stdio.h>
#include <ctxQmThread.h>
#include <showInfo_open.h>


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
	FILE* pf = fopen("D:/qycx/d4k.txt", "a+");
	if (pf == NULL)
	{
		perror("fopen failed");
		//
		return 1;
	}

	//TCHAR* pp;


	//fprintf(pf, "%s:%s  - %s \n", __DATE__, __TIME__, log);
	fprintf(pf, "[%s]  - %s \n", getDT().c_str(), log);

	fclose(pf);

	return 0;

}


int printLog(TCHAR* log) {
	//return 0;
	FILE* pf = fopen("D:\\qycx\\d4k.txt", "a+");
	if (pf == NULL)
	{
		perror("fopen failed");
		//
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
int  dh_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
{
	int  iErr = -1;
	unsigned  int    dwByte = msgLen;
	//	
	TCHAR  tBuf[128];

	printLogChar("dh_qisPipe_onRead");

	//	
	if (dwByte < sizeof(OnvifMsg_common)) {
		//dyn_showInfo_open(0, 0, _T("pipeThread_cli err: read too small bytes < sizeof(  Onvif_msg_common  )"));
		return  -1;
	}
#if 0
	if (dwByte > gBuf_dh.m_var.qm.uiSize_pOnvifMsgBuf)
	{
		_sntprintf(tBuf, mycountof(tBuf), _T("onvifMsgBuf too small, dwByte %d > size_msgBuf %d"), dwByte, gBuf_dh.m_var.qm.uiSize_pOnvifMsgBuf);
		//dyn_showInfo_open(0, 0, tBuf);
		return  -1;
	}
#endif



	//
	OnvifMsg_common* pMsgCommon = (OnvifMsg_common*)pMsg;
	if (pMsgCommon->uiType != CONST_qisMsgType_onvif)  return  -1;

	//
	gBuf_dh.m_var.qm.dwLastTickCnt_recvd = myGetTickCount(nullptr);

	//
	//
	switch  (  pMsgCommon->iSubtype) {
			case  CONST_onvifMsg_subtype_dbg:
				{
				OnvifMsg_dbg* pDbg = (OnvifMsg_dbg*)pMsgCommon;
				OnvifMsg_dbg  m = { 0 };
				m.uiType = CONST_qisMsgType_onvif;
				m.iSubtype = CONST_onvifMsg_subtype_dbg;
				m.ucbResp = true;
				_snprintf(m.buf, mycountof(m.buf), "d4k recvd: %s", pDbg->buf);
				qisPipe_writeMsg(&m, sizeof(m), gBuf_dh.m_var.qm.pQisPipe);
				
				}
				  break;
			case  CONST_onvifMsg_subtype_ping:
				{
				OnvifMsg_ping* pPing = (OnvifMsg_ping*)pMsgCommon;
				//
				OnvifMsg_ping m = { 0 };
				m.uiType = CONST_qisMsgType_onvif;
				m.iSubtype = CONST_onvifMsg_subtype_ping;
				//
				if (0) {
					showInfo_open0(0, 0, _T("recv ping, redirect to listIp"));
				}
				//
				m.tn = gBuf_dh.m_var.dhListIp.tool.tn;
				if (m.tn) {
					qisPipe_writeMsg(&m, sizeof(m), gBuf_dh.m_var.dhListIp.pQisPipe);
				}
				m.tn = gBuf_dh.m_var.dhDeviceControl.tool.tn;
				if (m.tn) {
					qisPipe_writeMsg(&m, sizeof(m), gBuf_dh.m_var.dhDeviceControl.pQisPipe);
				}
				/*
				m.tn = gBuf_dh.m_var.dhPtz.tool.tn;
				if (m.tn) {
					qisPipe_writeMsg(&m, sizeof(m), gBuf_dh.m_var.dhPtz.pQisPipe);
				}*/

				}
				
				break;
			case  CONST_onvifMsg_subtype_close:
				  //
				  //gBuf_dh.m_var.m_bClose = true;
				  //
				  showInfo_open0(0, 0, _T("recv close msg"));
				  //
				  PostMessage(gBuf_dh.m_var.hMainWnd, WM_CLOSE, 0, 0);
				  //
				  break;

			case  CONST_onvifMsg_subtype_nvrInfo:
			{
				//  先启动dhListIp
				showInfo_open0(0,0,_T(  "d4k: redirect to dhListIp.pQisPipe\n"));

				printLogChar("d4k: redirect to dhListIp.pQisPipe");

				//
				int  ii = 0;
				qisPipe_writeMsg(pMsg, msgLen, gBuf_dh.m_var.dhListIp.pQisPipe);
			}
				break;
			case  CONST_onvifMsg_subtype_nvrControl:
			{
				//
				printLogChar("d4k: redirect to dhDeviceControl.pQisPipe");
				qisPipe_writeMsg(pMsg, msgLen, gBuf_dh.m_var.dhDeviceControl.pQisPipe);
			}
				break;
				/*
			case  CONST_onvifMsg_subtype_ptz:
			{
				OnvifMsg_ptz* pPtz = (OnvifMsg_ptz*)pMsgCommon;


				//
				qisPipe_writeMsg(pMsg, msgLen, gBuf_dh.m_var.dhPtz.pQisPipe);

			}
			break;
			*/
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


//
int  dh_listIp_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
{
	int  iErr = -1;
	unsigned  int    dwByte = msgLen;
	//	
	TCHAR  tBuf[128];

	printLogChar("dh_listIp_qisPipe_onRead");

	//	
	if (dwByte < sizeof(OnvifMsg_common)) {
		//dyn_showInfo_open(0, 0, _T("pipeThread_cli err: read too small bytes < sizeof(  Onvif_msg_common  )"));
		return  -1;
	}
#if 0
	if (dwByte > gBuf_dh.m_var.tool.uiSize_pOnvifMsgBuf)
	{
		_sntprintf(tBuf, mycountof(tBuf), _T("onvifMsgBuf too small, dwByte %d > size_msgBuf %d"), dwByte, gBuf_dh.m_var.tool.uiSize_pOnvifMsgBuf);
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
	gBuf_dh.m_var.dhListIp.dwLastTickCnt_recvd = myGetTickCount(nullptr);

	//
	//
	switch (pMsgCommon->iSubtype) {
	case  CONST_onvifMsg_subtype_dbg:
	{
		OnvifMsg_dbg* pDbg = (OnvifMsg_dbg*)pMsgCommon;


	}
	break;
	//
	case  CONST_onvifMsg_subtype_nvrInfo:
	{
		OnvifMsg_nvrInfo* pOn = (OnvifMsg_nvrInfo*)pMsgCommon;
		if (!pOn->ucbResp)  break;
		int  ii = 0;

		//
		showInfo_open0(0, 0, _T("dh: recv from dhListIp, and send it to app"));
		printLogChar("dh: recv from dhListIp, and send it to app");

		//
		qisPipe_writeMsg(pMsg, msgLen, gBuf_dh.m_var.qm.pQisPipe);

	}
	break;
	//
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


//
//
int  dh_deviceControl_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
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
	if (dwByte > gBuf_dh.m_var.tool.uiSize_pOnvifMsgBuf)
	{
		_sntprintf(tBuf, mycountof(tBuf), _T("onvifMsgBuf too small, dwByte %d > size_msgBuf %d"), dwByte, gBuf_dh.m_var.tool.uiSize_pOnvifMsgBuf);
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
	gBuf_dh.m_var.dhDeviceControl.dwLastTickCnt_recvd = myGetTickCount(nullptr);

	//
	//
	switch (pMsgCommon->iSubtype) {
	case  CONST_onvifMsg_subtype_dbg:
	{
		OnvifMsg_dbg* pDbg = (OnvifMsg_dbg*)pMsgCommon;


	}
	break;
	case  CONST_onvifMsg_subtype_nvrControl:
	{
		OnvifMsg_nvrInfo* pOn = (OnvifMsg_nvrInfo*)pMsgCommon;
		if (!pOn->ucbResp)  break;
		int  ii = 0;

		//
		showInfo_open0(0, 0, _T("dh: recv from d4kDeviceControl, and send it to app"));
		printLogChar("dh: recv from d4kDeviceControl, and send it to app");

		//
		qisPipe_writeMsg(pMsg, msgLen, gBuf_dh.m_var.qm.pQisPipe);

	}
	break;
	//
	//
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




//
int  dh_ptz_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
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
	if (dwByte > gBuf_dh.m_var.tool.uiSize_pOnvifMsgBuf)
	{
		_sntprintf(tBuf, mycountof(tBuf), _T("onvifMsgBuf too small, dwByte %d > size_msgBuf %d"), dwByte, gBuf_dh.m_var.tool.uiSize_pOnvifMsgBuf);
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
	gBuf_dh.m_var.dhListIp.dwLastTickCnt_recvd = myGetTickCount(nullptr);

	//
	//
	switch (pMsgCommon->iSubtype) {
	case  CONST_onvifMsg_subtype_dbg:
	{
		OnvifMsg_dbg* pDbg = (OnvifMsg_dbg*)pMsgCommon;


	}
	break;
	//
	case  CONST_onvifMsg_subtype_nvrInfo:
	{
		OnvifMsg_nvrInfo* pOn = (OnvifMsg_nvrInfo*)pMsgCommon;
		if (!pOn->ucbResp)  break;
		int  ii = 0;

		//
		showInfo_open0(0, 0, _T("dh: recv from dhListIp, and send it to app"));

		//
		qisPipe_writeMsg(pMsg, msgLen, gBuf_dh.m_var.qm.pQisPipe);

	}
	break;
	//
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
