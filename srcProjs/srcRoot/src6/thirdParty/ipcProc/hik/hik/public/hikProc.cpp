

#include	"stdafx.h"
#include    "hikProc.h"
#include <qisOnvifCommProc_open.h>
#include <stdio.h>
#include <ctxQmThread.h>
#include <showInfo_open.h>

//#include "pipe_client.h"

//extern Pipe_Client* g_pipeClient;


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
	/*if (!gBuf_dh.m_var.appParams.log)
		return 0;*/

	FILE* pf = fopen("D:/qycx/hik.txt", "a+");
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


int printLog(const TCHAR* log) {
	//return 0;
	if (!gBuf_dh.m_var.appParams.log)
		return 0;
	FILE* pf = fopen("D:\\qycx\\hik.txt", "a+");
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

std::string make_msg(int type, const char* content) {
	std::stringstream ss;

	ss << type << ":" << content << "\r\n";

	return ss.str();
}

std::string make_msg(int type, int channel) {
	std::stringstream ss;

	ss << type << ":" << channel << "\r\n";

	return ss.str();
}

//void processCmd(OnvifMsg_nvrControl* pNc) {
//
//	printLogChar("------------------processCmd------------begin---------------");
//	std::stringstream ss;
//	ss << "cmd:" << pNc->usCmd << ",iChannel:" << pNc->iChannel;
//
//	printLogChar(ss.str().c_str());
//
//
//	do {
//		if (!pNc)  break;
//		//
//		switch (pNc->usCmd) {
//		case  CONST_nvrControlCmd_selectChannel:
//			if (g_pipeClient) {
//				
//				std::string msg = make_msg(CONST_onvifMsg_subtype_nvrControl, pNc->iChannel);
//				printLogChar(msg.c_str());
//				g_pipeClient->Write(msg.c_str());
//			}
//			else {
//				printLogChar("processCmd:pipeClient is null");
//			}
//			break;
//
//		default:
//			printLogChar("cmd not suported");
//			break;
//		}
//
//		//
//	} while (false);
//
//	printLogChar("------------------processCmd------------end---------------");
//}

std::string make_msg(int type, int channel, int ucCmd, int ucMouseStatus) {
	std::stringstream ss;

	ss << type << ":" << channel << "," << ucCmd << "," << ucMouseStatus << "\r\n";

	return ss.str();
}

//void processPtz(OnvifMsg_ptz* ptz) {
//
//	printLogChar("------------------processPtz------------begin---------------");
//	std::stringstream ss;
//	ss << "cmd:" << ptz->ucCmd << ",iChannel:" << ptz->iChannel << ",ucMouseStatus:" << ptz->ucMouseStatus;
//
//	printLogChar(ss.str().c_str());
//
//
//	if (g_pipeClient) {
//
//		std::string msg = make_msg(CONST_onvifMsg_subtype_ptz, ptz->iChannel, ptz->ucCmd, ptz->ucMouseStatus);
//		printLogChar(msg.c_str());
//		g_pipeClient->Write(msg.c_str());
//	}
//	else {
//		printLogChar("processPtz:pipeClient is null");
//	}
//
//	printLogChar("------------------processPtz------------end---------------");
//}
//
int  hik_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
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
				_snprintf(m.buf, mycountof(m.buf), "dh recvd: %s", pDbg->buf);
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
#ifdef  _DEBUG
				if (10) {
					showInfo_open0(0, 0, _T("recv ping, redirect to listIp"));
				}
#endif

				printLogChar("recv ping, redirect to listIp");
				//
				m.tn = gBuf_dh.m_var.dhListIp.tool.tn;
				if (m.tn) {
					qisPipe_writeMsg(&m, sizeof(m), gBuf_dh.m_var.dhListIp.pQisPipe);
					
					//
					/*if (g_pipeClient) {
						std::string msg = make_msg(CONST_onvifMsg_subtype_ping, "");
						printLogChar(msg.c_str());
						g_pipeClient->Write(msg.c_str());
					}
					else {
						printLogChar("pipeClient is null");
					}*/
				}

				//
				m.tn = gBuf_dh.m_var.hk3ddw.tool.tn;
				if (m.tn) {
					qisPipe_writeMsg(&m, sizeof(m), gBuf_dh.m_var.hk3ddw.pQisPipe);
				}

				
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
				showInfo_open0(0,0,_T(  "hik: nvrInfoReq from qm, redirect to hikListIp.pQisPipe\n"));
				printLogChar("hik: nvrInfoReq from qm, redirect to hikListIp.pQisPipe");

				//  这个管道Client最好去掉. 统一使用pQisPipe
				/*if (g_pipeClient) {
					std::string msg = make_msg(CONST_onvifMsg_subtype_nvrInfo, "");
					printLogChar(msg.c_str());
					g_pipeClient->Write(msg.c_str());
				}
				else {
					printLogChar("pipeClient is null");
				}*/

				//
				//int  ii = 0;
				qisPipe_writeMsg(pMsg, msgLen, gBuf_dh.m_var.dhListIp.pQisPipe);
			}
				break;
			case  CONST_onvifMsg_subtype_nvrControl:
			{
				showInfo_open0(0, 0, _T("hik: redirect to dhDeviceControl.pQisPipe\n"));
				printLogChar("hik: redirect to dhDeviceControl.pQisPipe");

				qisPipe_writeMsg(pMsg, msgLen, gBuf_dh.m_var.dhListIp.pQisPipe);

				/*
				OnvifMsg_nvrControl* pPtz = (OnvifMsg_nvrControl*)pMsgCommon;
				processCmd((OnvifMsg_nvrControl*)pPtz);
				*/
				
			}
				break;
			case  CONST_onvifMsg_subtype_ptz:
			{
				OnvifMsg_ptz* pPtz = (OnvifMsg_ptz*)pMsgCommon;

				//
				_sntprintf(tBuf, mycountof(tBuf), _T("hik: ptz cmd %d. redirect to dhPtz.pQisPipe"), (int)pPtz->ucCmd);

				//
				showInfo_open0(0, 0, tBuf  );
				printLogChar("hik: redirect to dhPtz.pQisPipe");

				//
				if (pPtz->ucCmd == CONST_ptzCmd_3ddw) {
					//
					qisPipe_writeMsg(pMsg, msgLen, gBuf_dh.m_var.hk3ddw.pQisPipe);
					//
					break;

				}


				//
				//processPtz((OnvifMsg_ptz*)pPtz);

				//
				qisPipe_writeMsg(pMsg, msgLen, gBuf_dh.m_var.dhListIp.pQisPipe);

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
#include <vector>

std::vector<std::string> split(const std::string& text, char sep) {
	std::vector<std::string> tokens;
	std::istringstream tokenStream(text);
	std::string token;
	while (std::getline(tokenStream, token, sep)) {
		tokens.push_back(token);
	}
	return tokens;
}

std::wstring MultiByteToWideString(const std::string& mbStr)
{
	int wLen = MultiByteToWideChar(CP_ACP, 0, mbStr.c_str(), -1, NULL, 0);
	if (wLen == 0)
	{
		return std::wstring();
	}

	std::wstring wStr(wLen, 0);
	MultiByteToWideChar(CP_ACP, 0, mbStr.c_str(), -1, &wStr[0], wLen);
	return wStr;
}

void processNvrInfo(int pos, std::string& content) {	

	printLogChar("-------processNvrInfo-------begin-----------");
	content.erase(0, pos + 1);

	printLogChar(content.c_str());

	OnvifMsg_nvrInfo	msg = { 0 };
	msg.uiType = CONST_qisMsgType_onvif;
	msg.iSubtype = CONST_onvifMsg_subtype_nvrInfo;

	msg.nvrInfo.usCnt = 0;

	std::vector<std::string> vecInfo = split(content, ';');

	if (vecInfo.size() > 0) {

		for (const auto& item : vecInfo) {
			std::vector<std::string> vecOne = split(item, ',');
			if (vecOne.size() == 3) {
				msg.nvrInfo.mems[msg.nvrInfo.usCnt].iChannel = atoi(vecOne[0].c_str());
				strncpy(msg.nvrInfo.mems[msg.nvrInfo.usCnt].ip, vecOne[1].c_str(), mycountof(msg.nvrInfo.mems[msg.nvrInfo.usCnt].ip));
				//TCHAR  tName[256];
				//myUtf82TChar((char*)vecOne[2].c_str(), tName, sizeof(tName) / sizeof(tName[0]));
				std::wstring strName = MultiByteToWideString(vecOne[2]);
				//lstrcpyn(msg.nvrInfo.mems[msg.nvrInfo.usCnt].name, tName, mycountof(tName));
				lstrcpyn(msg.nvrInfo.mems[msg.nvrInfo.usCnt].name, strName.c_str(), strName.length());

				msg.nvrInfo.usCnt++;
			}
		}

		qisPipe_writeMsg(&msg, sizeof(msg), gBuf_dh.m_var.qm.pQisPipe);

	}
	
	printLogChar("-------processNvrInfo-------end-----------");
}

std::string msgProcess(std::string msg) {
	printLogChar("-------msgProcess-------begin-----------");
	printLogChar(msg.c_str());

	int pos = msg.find(':');
	if (pos == std::string::npos) {
		printLogChar("-------msgProcess:message error");
		return "";
	}

	int cmd = atoi(msg.substr(0, pos).c_str());
	TCHAR  tBuf[128];
	

	switch (cmd) {
	case  CONST_onvifMsg_subtype_nvrInfo:
		processNvrInfo(pos, msg);
		break;
	
	}

	printLogChar("-------msgProcess-------end-----------");

	return "";
}


//
int  dh_listIp_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
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
		showInfo_open0(0, 0, _T("hik: recv from hikListIp, and send it to app 3"));
		printLogChar("hik: recv from hikListIp, and send it to app 3");

		printLogChar("-----------CONST_onvifMsg_subtype_nvrInfo-----------dh_ptz_qisPipe_onRead------------");
		for (int count = 0; count < pOn->nvrInfo.usCnt; ++count) {

			printLog(pOn->nvrInfo.mems[count].name);		
		}
		printLogChar("-----------CONST_onvifMsg_subtype_nvrInfo-----------dh_ptz_qisPipe_onRead----end--------");

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
int  hk_3ddw_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
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
	gBuf_dh.m_var.hk3ddw.dwLastTickCnt_recvd = myGetTickCount(nullptr);

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
		showInfo_open0(0, 0, _T("hik: recv from hikListIp, and send it to app 1"));
		printLogChar("hik: recv from hikListIp, and send it to app 1");

		
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
		showInfo_open0(0, 0, _T("hik: recv from hikListIp, and send it to app 2"));

		

		//std::wstring strName = MultiByteToWideString(vecOne[2]);
		//lstrcpyn(msg.nvrInfo.mems[msg.nvrInfo.usCnt].name, tName, mycountof(tName));
		//lstrcpyn(msg.nvrInfo.mems[msg.nvrInfo.usCnt].name, strName.c_str(), strName.length());

		//msg.nvrInfo.usCnt++;

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
