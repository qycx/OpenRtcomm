

#include	"stdafx.h"
#include	<tchar.h>
#include	"d4kListIpProc.h"
#include <stdio.h>
#include <ctxQmThread.h>
#include <showInfo_open.h>

#include <iostream>
#include <string>
#include <vector>

#include <iostream>
#include <sstream>
#include <map>

#include "TcpClient.h"

#define D4K_PORT 61111

DhListIpProc  gBuf_dhListIp;



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
	  //if (!gBuf_dhListIp.m_var.appParams.log)
		//  return 0;
	  FILE* pf = fopen("D:/qycx/d4kListIp.txt", "a+");
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


  int printLog(TCHAR* log) {
	  //return 0;
	  //if (!gBuf_dhListIp.m_var.appParams.log)
		//  return 0;
	  FILE* pf = fopen("D:\\qycx\\d4kListIp.txt", "a+");
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

  inline std::string trim_left(const std::string& source, const std::string& t = " ")
  {
	  std::string str = source;
	  return str.erase(0, source.find_first_not_of(t));
  }

  inline std::string trim_right(const std::string& source, const std::string& t = " ")
  {
	  std::string str = source;
	  return str.erase(str.find_last_not_of(t) + 1);
  }
  inline std::string trim(const std::string& source, const std::string& t = " ")
  {
	  std::string str = source;
	  return trim_left(trim_right(str, t), t);
  }


  std::vector<std::string> split(const std::string& text, char sep) {
	  std::vector<std::string> tokens;
	  std::istringstream tokenStream(text);
	  std::string token;
	  while (std::getline(tokenStream, token, sep)) {
		  tokens.push_back(token);
	  }
	  return tokens;
  }

  std::string replace_all(std::string str, const std::string& from, const std::string& to) {
	  std::string::size_type start_pos = 0;
	  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		  str.replace(start_pos, from.length(), to);
		  start_pos += to.length();
	  }
	  return str;
  }

  std::vector<std::string> split_string_by_newline(const std::string& str) {
	  std::vector<std::string> lines;
	  std::istringstream iss(str);
	  //std::stringstream ss;
	  //ss << str;
	  std::string line;
	  while (std::getline(iss, line)) {
		  lines.push_back(line);
	  }
	  return lines;
  }

  struct IpcInfoDef {
	  std::string name;
	  int         id;
	  std::string ip;
  };



  void parse_ipc_info_1(const std::string& info, std::map<int, IpcInfoDef>& mapIpc) {
	  int len = info.length();

	  std::vector<std::string>  vecLine = split_string_by_newline(replace_all(info, "\r\n", "\n"));

	  //std::vector<> 
	  IpcInfoDef ipcInfo;
	  int count = 0;

	  for (const auto& item : vecLine) {
		  std::vector<std::string> kv = split(item, ':');
		  if (kv.size() >= 2) {
			  std::string key = trim(kv[0]);

			  if (key == "id") {
				  ipcInfo.id = atoi(trim(kv[1]).c_str());
				  count++;
			  }
			  else if (key == "name") {
				  ipcInfo.name = trim(kv[1]);
				  count++;
			  }
			  else if (key == "ipaddr") {
				  ipcInfo.ip = trim(kv[1]);
				  count++;
			  }

		  }

		  if (count == 3) {
			  count = 0;
			  mapIpc[ipcInfo.id] = ipcInfo;
		  }
	  }
  }

  void parse_ipc_info_4(const std::string& info, const std::map<int, IpcInfoDef>& mapIpc, std::map<int, IpcInfoDef>& mapChannel) {
	  int len = info.length();

	  std::vector<std::string>  vecLine = split_string_by_newline(replace_all(info, "\r\n", "\n"));

	  //std::vector<> 
	  IpcInfo ipcInfo;
	  int count = 0;

	  int chn_cnt = 0;

	  for (const auto& item : vecLine) {
		  std::vector<std::string> kv = split(item, ':');
		  if (kv.size() >= 2) {
			  std::string key = trim(kv[0]);

			  if (key == "chn_cnt") {
				  chn_cnt = atoi(trim(kv[1]).c_str());
			  }
			  else if (key.find("chn_") != std::string::npos) {
				  std::string strCh = key.substr(4, -1);
				  int ch = atoi(key.substr(4).c_str());
				  int ipc = atoi(trim(kv[1]).c_str());

				  if (mapChannel.size() >= chn_cnt)
					  break;

				  if (ipc > 0) {
					  const auto& item = mapIpc.find(ipc);
					  if (item != mapIpc.end()) {
						  mapChannel[ch] = item->second;
					  }
				  }
			  }

		  }
	  }
  }

  void getIpc() {
	  TcpClient client(gBuf_dhListIp.m_var.appParams.nvrIp, D4K_PORT);
	  //Json::Value return_root;
	  //Json::FastWriter return_writer;
	  if (client.Connect()) {
		  const char* message = "cmd : DataSync\r\ntype : 1\r\n";
		  client.Send(message, strlen(message));

		  char buffer[20480];
		  int len = client.Receive(buffer, sizeof(buffer) - 1);
		  if (len > 0)
			  buffer[len + 1] = '\0';
		  buffer[sizeof(buffer) - 1] = '\0';
		  std::map<int, IpcInfoDef> mapIpc;
		  parse_ipc_info_1(buffer, mapIpc);

		  printLogChar("----------mapIpc------begin--------");
		  for (const auto& item : mapIpc) {
			  std::stringstream ss;
			  ss << item.first << ":" << item.second.id << "," << item.second.name << "," << item.second.ip;
			  printLogChar(ss.str().c_str());

		  }
		  printLogChar("----------mapIpc------end--------");
		  //std::cout << "Received: " << buffer << std::endl;

		  const char* message4 = "cmd : DataSync\r\ntype : 4\r\n";
		  client.Send(message4, strlen(message));
		  memset(buffer, 0x00, sizeof(buffer));
		  len = client.Receive(buffer, sizeof(buffer) - 1);
		  //cmd : SyncFinsh

		  int ret = strcmp(buffer, "cmd : SyncFinsh\r\n");

		  if (ret == 0) {
			  client.Send(message4, strlen(message));
			  memset(buffer, 0x00, sizeof(buffer));
			  len = client.Receive(buffer, sizeof(buffer) - 1);
		  }

		  std::map<int, IpcInfoDef> mapChannel;
		  parse_ipc_info_4(buffer, mapIpc, mapChannel);
		  printLogChar("----------mapChannel------begin--------");

		  NvrInfo* pNvrInfo = &gBuf_dhListIp.m_var.nvrInfo;
		  pNvrInfo->usCnt = 0;
		  for (const auto& item : mapChannel) {

			  std::stringstream ss;
			  ss << item.first << ":" << item.second.id << "," << item.second.name << "," << item.second.ip;
			  printLogChar(ss.str().c_str());


			  /*
			  Json::Value itemJson;
			  itemJson["Channel"] = item.first;
			  itemJson["Ip"] = item.second.ip;
			  itemJson["Name"] = item.second.name;
			  //
			  //
			  return_root.append(itemJson);
			  */

			  TCHAR  tName[256];
			  myUtf82TChar((char*)item.second.name.c_str(), tName, sizeof(tName) / sizeof(tName[0]));

			  
			  if (pNvrInfo->usCnt < mycountof(pNvrInfo->mems)) {
				  IpcInfo* pMem = &pNvrInfo->mems[pNvrInfo->usCnt];
				  //
				  pMem->iChannel = item.second.id;
				  strncpy(pMem->ip, item.second.ip.c_str(), mycountof(pMem->ip));
				  lstrcpyn(pMem->name, tName, mycountof(tName));

				  //
				  pNvrInfo->usCnt++;
			  }
		  }

		  printLogChar("----------mapChannel------end--------");

		  gBuf_dhListIp.m_var.m_bGot_nvrInfo = true;

	  }
  }


  void getIpc2() {
	  printLogChar("----------getIpc2------begin--------");
	  TcpClient client(gBuf_dhListIp.m_var.appParams.nvrIp, D4K_PORT);
	  //Json::Value return_root;
	  //Json::FastWriter return_writer;
	  if (client.Connect()) {
		  const char* message = "cmd : DataSync\r\ntype : 1\r\n";
		  client.Send(message, strlen(message));
		  printLogChar(message);

		  char buffer[20480] = {'\0'};
		  int len = client.Receive(buffer, sizeof(buffer) - 1);
		  if (len > 0)
			  buffer[len + 1] = '\0';

		  printLogChar(buffer);

		  std::map<int, IpcInfoDef> mapIpc;
		  parse_ipc_info_1(buffer, mapIpc);

		  printLogChar("----------mapIpc------begin--------");
		  for (const auto& item : mapIpc) {
			  std::stringstream ss;
			  ss << item.first << ":" << item.second.id << "," << item.second.name << "," << item.second.ip;
			  printLogChar(ss.str().c_str());

		  }
		  printLogChar("----------mapIpc------end--------");
		  //std::cout << "Received: " << buffer << std::endl;

		  const char* message4 = "cmd : DataSync\r\ntype : 4\r\n";
		  client.Send(message4, strlen(message4));
		  printLogChar(message4);

		  memset(buffer, 0x00, sizeof(buffer));
		  len = client.Receive(buffer, sizeof(buffer) - 1);
		  if (len > 0)
			  buffer[len + 1] = '\0';
		  printLogChar(buffer);

		  int ret = strcmp(buffer, "cmd : SyncFinsh\r\n");

		  if (ret == 0) {
			  client.Send(message4, strlen(message4));
			  printLogChar(message4);

			  memset(buffer, 0x00, sizeof(buffer));
			  len = client.Receive(buffer, sizeof(buffer) - 1);
			  if (len > 0)
				  buffer[len + 1] = '\0';
			  printLogChar(buffer);
		  }


		  NvrInfo* pNvrInfo = &gBuf_dhListIp.m_var.nvrInfo;
		  pNvrInfo->usCnt = 0;
		  for (const auto& item : mapIpc) {

			  std::stringstream ss;
			  ss << item.first << ":" << item.second.id << "," << item.second.name << "," << item.second.ip;
			  //std::cout << ss.str() << std::endl;
			  printLogChar(ss.str().c_str());
			  
			  TCHAR  tName[256];
			  myUtf82TChar((char*)item.second.name.c_str(), tName, sizeof(tName) / sizeof(tName[0]));


			  if (pNvrInfo->usCnt < mycountof(pNvrInfo->mems)) {
				  IpcInfo* pMem = &pNvrInfo->mems[pNvrInfo->usCnt];
				  //
				  pMem->iChannel = item.second.id;
				  strncpy(pMem->ip, item.second.ip.c_str(), mycountof(pMem->ip));
				  lstrcpyn(pMem->name, tName, mycountof(tName));

				  //
				  pNvrInfo->usCnt++;
			  }
			  
		  }

		  printLogChar("----------mapChannel------end--------");

		  gBuf_dhListIp.m_var.m_bGot_nvrInfo = true;

		  

	  }
	  else {
		  printLogChar("connect failed");
	  }

	  printLogChar("----------getIpc2------end--------");
  }

  //
  //
  int  dhListIp_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
  {
	  int  iErr = -1;
	  unsigned  int    dwByte = msgLen;
	  //	
	  TCHAR  tBuf[128];

	  printLogChar("------------dhListIp_qisPipe_onRead------------");

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
		  _snprintf(m.buf, mycountof(m.buf), "d4kListIp recvd: %s", pDbg->buf);
		  qisPipe_writeMsg(&m, sizeof(m), gBuf_dhListIp.m_var.pQisPipe);

	  }
	  break;
	  case  CONST_onvifMsg_subtype_ping:
	  {
		  if (0) {
			  showInfo_open0(0, 0, _T("d4kListIp: recv ping"));
		  }
	  }
	  break;

	  case  CONST_onvifMsg_subtype_nvrInfo:
	  {
		  getIpc2();
		  //
		  if (!gBuf_dhListIp.m_var.m_bGot_nvrInfo) {
			  break;
		  }

		  //
#ifdef  _DEBUG
		  _sntprintf(tBuf,mycountof(tBuf), _T("dhListIp: get nvrInfo req, cnt %d and send back resp"),  (int)gBuf_dhListIp.m_var.nvrInfo.usCnt);
		  showInfo_open0(0, 0, tBuf);
#endif

		  //

		  

		  OnvifMsg_nvrInfo m = { 0 };
		  m.uiType = CONST_qisMsgType_onvif;
		  m.iSubtype = CONST_onvifMsg_subtype_nvrInfo;
		  m.ucbResp = true;
		  m.nvrInfo = gBuf_dhListIp.m_var.nvrInfo;

		  printLogChar("----------CONST_onvifMsg_subtype_nvrInfo------begin--------");

		  printLogChar("----------CONST_onvifMsg_subtype_nvrInfo------end--------");
		  
		  //
		  qisPipe_writeMsg(&m, sizeof(m), gBuf_dhListIp.m_var.pQisPipe);
		  //
		  //gBuf_dhListIp.m_var.m_bDone_nvrInfo = true;
		  //
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
