

#include	"stdafx.h"
#include	<tchar.h>
#include	"hikListIpProc.h"
#include <stdio.h>
#include <ctxQmThread.h>
#include <showInfo_open.h>

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

  
  int printLog(wchar_t* log) {
	  //return 0;
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
  

  //
  //
  int  dhListIp_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
  {
	  int  iErr = -1;
	  unsigned  int    dwByte = msgLen;
	  printLogChar("hikListIp: dhListIp_qisPipe_onRead in");
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
