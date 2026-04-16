

#include	"stdafx.h"
#include	<tchar.h>
#include	"hikListIpProc.h"
#include <stdio.h>
#include <ctxQmThread.h>
#include <showInfo_open.h>
//#include <pipe_client.h>

  DhListIpProc  gBuf_dhListIp;

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

	  if (!gBuf_dhListIp.m_var.appParams.log)
		  return 0;

	  FILE* pf = fopen("D:/qycx/hikListIp.txt", "a+");
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

	  if (!gBuf_dhListIp.m_var.appParams.log)
		  return 0;

	  FILE* pf = fopen("D:/qycx/hikListIp.txt", "a+");
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

  int printLogCharSpec(const char* log) {
	  if (!gBuf_dhListIp.m_var.appParams.log)
		  return 0;

	  FILE* pf = fopen("D:/qycx/hikListIp.txt", "a+");
	  if (pf == NULL)
	  {
		  perror("打开文件失败！");
		  return 1;
	  }

	  //TCHAR* pp;
	  DWORD pid = GetCurrentProcessId();
	  DWORD threadId = GetCurrentThreadId();

	  //fprintf(pf, "%s:%s  - %s \n", __DATE__, __TIME__, log);
	  fprintf(pf, "[%s][%u-%u]  - %s \n", getDT().c_str(), pid, threadId, log);

	  fclose(pf);

	  return 0;
  }

  
  int printLog(const wchar_t* log) {
	  //return 0;
	  if (!gBuf_dhListIp.m_var.appParams.log)
		  return 0;
	  FILE* pf = fopen("D:\\qycx\\hikListIp.txt", "a+");
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
  
//  std::string msgProcess(std::string msg) {
//	  printLogChar("-------msgProcess-------begin-----------");
//	  printLogChar(msg.c_str());
//
//	  gBuf_dhListIp.m_var.dwLastTickCnt_recvd = myGetTickCount(nullptr);
//
//	  int pos = msg.find(':');
//	  if (pos == std::string::npos) {
//		  return "";
//	  }
//
//	  int cmd = atoi(msg.substr(0, pos).c_str());
//	  TCHAR  tBuf[128];
//
//	  switch (cmd) {
//	  case  CONST_onvifMsg_subtype_nvrInfo:
//	  {
//
//		  //
//		  /*
//		  printLogChar("CONST_onvifMsg_subtype_nvrInfo");
//		  if (g_pipeClient) {
//
//			  std::stringstream ss;
//			  ss << cmd << ":" << "1,192.168.1.2,test;2,192.168.1.3,test2\r\n";
//
//			  g_pipeClient->Write(ss.str().c_str());
//
//		  }
//		  */
//
//		  if (!gBuf_dhListIp.m_var.m_bGot_nvrInfo) {
//			  break;
//		  }
//
//		  printLogChar("hikListIp: get nvrInfo req, cnt %d and send back resp");
//
//		  //
//#ifdef  _DEBUG
//		  _sntprintf(tBuf, mycountof(tBuf), _T("hikListIp: get nvrInfo req, cnt %d and send back resp"), (int)gBuf_dhListIp.m_var.nvrInfo.usCnt);
//		  showInfo_open0(0, 0, tBuf);
//#endif
//
//		  //
//		  /*
//		  OnvifMsg_nvrInfo m = { 0 };
//		  m.uiType = CONST_qisMsgType_onvif;
//		  m.iSubtype = CONST_onvifMsg_subtype_nvrInfo;
//		  m.ucbResp = true;
//		  m.nvrInfo = gBuf_dhListIp.m_var.nvrInfo;
//		  //
//		  qisPipe_writeMsg(&m, sizeof(m), gBuf_dhListIp.m_var.pQisPipe);
//		  */
//		  //
//		  //gBuf_dhListIp.m_var.m_bDone_nvrInfo = true;
//		  //
//
//		  if (g_pipeClient) {
//
//			  std::stringstream ss;
//			  ss << cmd << ":";
//			  for (int i = 0; i < gBuf_dhListIp.m_var.nvrInfo.usCnt; ++i) {
//				  if (i > 0)
//					  ss << ";";
//
//				  ss << gBuf_dhListIp.m_var.nvrInfo.mems[i].iChannel << ","
//					  << gBuf_dhListIp.m_var.nvrInfo.mems[i].ip << ","
//					  << gBuf_dhListIp.m_var.nvrInfo.mems[i].name;
//
//			  }
//			  ss << "\r\n";
//
//			  g_pipeClient->Write(ss.str().c_str());
//
//		  }
//
//
//	  }
//	  break;
//	  case CONST_onvifMsg_subtype_nvrControl: 
//
//		  if(gBuf_dhListIp.m_var.hControlWnd != nullptr) {
//			  printLogChar("hikListIp: CONST_onvifMsg_subtype_nvrControl");
//
//			  OnvifMsg_nvrControl nc;
//			  nc.iChannel =  atoi(msg.substr(pos + 1).c_str());	  
//			  nc.usCmd = CONST_nvrControlCmd_selectChannel;
//
//			  //showInfo_open0(0, _T("hikListIp"), _T("CONST_onvifMsg_subtype_nvrControl"));
//
//			  COPYDATASTRUCT		tmpCopyData;
//
//			  tmpCopyData.lpData = &nc;
//			  tmpCopyData.cbData = sizeof(nc);
//			  int  iRet = ::SendMessageTimeout(gBuf_dhListIp.m_var.hControlWnd, WM_COPYDATA, NULL, (LPARAM)&tmpCopyData, 0, 1000, NULL);
//		  }
//		  else {
//			  printLogChar("hikListIp: CONST_onvifMsg_subtype_nvrControl hControlWnd is null");
//		  }
//		  break;
//
//	  case CONST_onvifMsg_subtype_ptz:
//
//		  if (gBuf_dhListIp.m_var.hMainWnd != nullptr) {
//			  printLogChar("hikListIp: CONST_onvifMsg_subtype_ptz");
//
//			  std::string content = msg.substr(pos + 1);
//
//			  printLogChar(content.c_str());
//
//			  std::vector<std::string> vecValue = split(content, ',');
//
//			  if (vecValue.size() >= 3) {
//				  OnvifMsg_ptz ptz;
//
//				  ptz.iChannel = atoi(vecValue[0].c_str());
//				  ptz.ucCmd = atoi(vecValue[1].c_str());
//				  ptz.ucMouseStatus = atoi(vecValue[2].c_str());
//
//				  std::stringstream ss;
//				  ss << "CONST_onvifMsg_subtype_ptz:" << ptz.iChannel << "," << int(ptz.ucCmd) << "," << (int)ptz.ucMouseStatus;
//				  printLogChar(ss.str().c_str());
//
//				  COPYDATASTRUCT		tmpCopyData;
//
//				  tmpCopyData.lpData = &ptz;
//				  tmpCopyData.cbData = sizeof(ptz);
//				  int  iRet = ::SendMessageTimeout(gBuf_dhListIp.m_var.hMainWnd, WM_COPYDATA, NULL, (LPARAM)&tmpCopyData, 0, 1000, NULL);
//			  }
//			  else {
//				  printLogChar("hikListIp: CONST_onvifMsg_subtype_ptz content error");
//			  }			  
//		  }
//		  else {
//			  printLogChar("hikListIp: CONST_onvifMsg_subtype_ptz hMainWnd is null");
//		  }
//		  break;
//	  case CONST_onvifMsg_subtype_ping:
//		  printLogChar("hikListIp: receive CONST_onvifMsg_subtype_ping");
//		  break;
//
//	  case 1234: 
//		  if (g_pipeClient != nullptr) {
//			  delete g_pipeClient;
//			  g_pipeClient = nullptr;
//			  
//		  } 
//		  {
//			  int pid = atoi(msg.substr(pos + 1).c_str());
//			  std::stringstream ss;
//			  ss << "pipe_hik_" << pid;
//			  printLogChar(ss.str().c_str());
//			  g_pipeClient = new Pipe_Client(ss.str());
//			  g_pipeClient->Start();
//		  }
//	      
//		  break;
//
//	  }	
//
//	  printLogChar("-------msgProcess-------end-----------");
//
//	  return "";
//  } 

 

  //
  //
  int  hikListIp_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
  {
	  int  iErr = -1;
	  unsigned  int    dwByte = msgLen;
	  printLogChar("hikListIp: dhListIp_qisPipe_onRead in");
	  //	
	  TCHAR  tBuf[128];

	  //	
	  if (dwByte < sizeof(OnvifMsg_common)) {
		  //dyn_showInfo_open0(0, 0, _T("pipeThread_cli err: read too small bytes < sizeof(  Onvif_msg_common  )"));
		  return  -1;
	  }
#if 0
	  if (dwByte > gBuf_dhListIp.m_var.uiSize_pOnvifMsgBuf)
	  {
		  _sntprintf(tBuf, mycountof(tBuf), _T("onvifMsgBuf too small, dwByte %d > size_msgBuf %d"), dwByte, gBuf_dhListIp.m_var.uiSize_pOnvifMsgBuf);
		  //dyn_showInfo_open0(0, 0, tBuf);
		  return  -1;
	  }
#endif

	  //
	  showInfo_open0(0, 0, _T("hikListIp: kkkk"));


	  //
	  //gBuf_dh.status.dwTickCnt_lastMsg = GetTickCount();

	  //
	  OnvifMsg_common* pMsgCommon = (OnvifMsg_common*)pMsg;
	  if (pMsgCommon->uiType != CONST_qisMsgType_onvif)  return  -1;

	  //
	  gBuf_dhListIp.m_var.dwLastTickCnt_recvd = myGetTickCount(nullptr);

	  //
	  //
	  switch (pMsgCommon->iSubtype) {
	  case  CONST_onvifMsg_subtype_dbg:
	  {
		  OnvifMsg_dbg* pDbg = (OnvifMsg_dbg*)pMsgCommon;
		  OnvifMsg_dbg  m = { 0 };
		  m.uiType = CONST_qisMsgType_onvif;
		  m.iSubtype = CONST_onvifMsg_subtype_dbg;
		  _snprintf(m.buf, mycountof(m.buf), "hikListIp recvd: %s", pDbg->buf);
		  qisPipe_writeMsg(&m, sizeof(m), gBuf_dhListIp.m_var.pQisPipe);

	  }
	  break;
	  case  CONST_onvifMsg_subtype_ping:
	  {
		  if (0) {
			  showInfo_open0(0, 0, _T("listIp: recv ping"));
		  }
	  }
	  break;

	  case  CONST_onvifMsg_subtype_nvrInfo:
	  {

		  std::stringstream ss;
		  ss << "hikListIp: dhListIp_qisPipe_onRead CONST_onvifMsg_subtype_nvrInfo:Got_nvrInfo=" << gBuf_dhListIp.m_var.m_bGot_nvrInfo;

		  printLogChar(ss.str().c_str());

		  //
		  if (!gBuf_dhListIp.m_var.m_bGot_nvrInfo) {
			  break;
		  }

		  printLogChar("hikListIp: get nvrInfo req, cnt %d and send back resp");

		  //
#ifdef  _DEBUG
		  _sntprintf(tBuf,mycountof(tBuf), _T("hikListIp: get nvrInfo req, cnt %d and send back resp"),  (int)gBuf_dhListIp.m_var.nvrInfo.usCnt);
		  showInfo_open0(0, 0, tBuf);
#endif

		  //
		  OnvifMsg_nvrInfo m = { 0 };
		  m.uiType = CONST_qisMsgType_onvif;
		  m.iSubtype = CONST_onvifMsg_subtype_nvrInfo;
		  m.ucbResp = true;
		  m.nvrInfo = gBuf_dhListIp.m_var.nvrInfo;

		  ss.str("");
		  ss << "-----------CONST_onvifMsg_subtype_nvrInfo-----------hikListIp_qisPipe_onRead------------:deviceType:" 
			  << gBuf_dhListIp.m_var.m_DeviceType << ",devType:" << gBuf_dhListIp.m_var.appParams.devType;

		  printLogChar(ss.str().c_str());

		  if (gBuf_dhListIp.m_var.m_DeviceType == DeviceType_IPZM) {			 

			  IpcInfo* pMem = &m.nvrInfo.mems[m.nvrInfo.usCnt];
			  pMem->iChannel = 1;
			  m.nvrInfo.deviceType = DeviceType_IPZM;

			  std::wstring strName = L"布控";
			  if (gBuf_dhListIp.m_var.appParams.devType == 1) {
				  strName += L"(球机)";
			  }
			  else if (gBuf_dhListIp.m_var.appParams.devType == 2) {
				  strName += L"(3D)";
			  }			 

			  lstrcpynW(pMem->name, strName.c_str(), sizeof(pMem->name) / sizeof(WCHAR));

			  //
			  m.nvrInfo.usCnt++;
		  }
		  else {
			  for (int count = 0; count < m.nvrInfo.usCnt; ++count) {

				  printLog(m.nvrInfo.mems[count].name);

			  }
		  }
		  printLogChar("-----------CONST_onvifMsg_subtype_nvrInfo-----------hikListIp_qisPipe_onRead----end--------");	  




		  //
		  qisPipe_writeMsg(&m, sizeof(m), gBuf_dhListIp.m_var.pQisPipe);
		  //
		  //gBuf_dhListIp.m_var.m_bDone_nvrInfo = true;
		  //
	  }
	  break;

	  case  CONST_onvifMsg_subtype_nvrControl:
	  {
		  printLogChar("hikListIp: dhListIp_qisPipe_onRead CONST_onvifMsg_subtype_nvrControl");

		  OnvifMsg_ptz* pPtz = (OnvifMsg_ptz*)pMsgCommon;
		  //
		  int  ii = 0;

		  //
		  COPYDATASTRUCT		tmpCopyData;

		  tmpCopyData.lpData = pPtz;
		  tmpCopyData.cbData = sizeof(*pPtz);
		  int  iRet = ::SendMessageTimeout(gBuf_dhListIp.m_var.hControlWnd, WM_COPYDATA, NULL, (LPARAM)&tmpCopyData, 0, 1000, NULL);


	  }
	  break;
	  case  CONST_onvifMsg_subtype_ptz:
	  {
		  printLogChar("hikListIp: dhListIp_qisPipe_onRead CONST_onvifMsg_subtype_ptz");

		  OnvifMsg_ptz* pPtz = (OnvifMsg_ptz*)pMsgCommon;
		  //
		  int  ii = 0;		  

		  //
		  COPYDATASTRUCT		tmpCopyData;

		  tmpCopyData.lpData = pPtz;
		  tmpCopyData.cbData = sizeof(*pPtz);

		  
		 
		  int  iRet = ::SendMessageTimeout(gBuf_dhListIp.m_var.hMainWnd, WM_COPYDATA, NULL, (LPARAM)&tmpCopyData, 0, 1000, NULL);


	  }
	  break;

	  default:
		  //dyn_showInfo_open0(0, 0, _T("onvifCli_qisPipe_onRead: unprocessed subtype"));
		  break;
	  }


	  //
	  iErr = 0;

  errLabel:

	  //
	  return  iErr;
  }
