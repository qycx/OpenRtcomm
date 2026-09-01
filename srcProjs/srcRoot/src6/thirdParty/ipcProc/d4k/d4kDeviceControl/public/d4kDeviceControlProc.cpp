
#include	"StdAfx.h"
#include	"d4kDeviceControlProc.h"
#include <ctxQmThread.h>
#include <showInfo_open.h>
#include <sstream>
#include "TcpClient.h"

#include <vector>
#include <map>

extern int printLogChar(const char* log);
extern int printLog(TCHAR* log);

#define BUF_LEN  2048 * 10

#define D4K_PORT 61111

DhDeviceControlProc gBuf_dhDeviceControl;


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

int getChn(const std::string& info) {
	int len = info.length();

	std::vector<std::string>  vecLine = split_string_by_newline(replace_all(info, "\r\n", "\n"));

	IpcInfo ipcInfo;
	int chn_cnt = 0;

	for (const auto& item : vecLine) {
		std::vector<std::string> kv = split(item, ':');
		if (kv.size() >= 2) {
			std::string key = trim(kv[0]);

			if (key == "chn_cnt") {
				chn_cnt = atoi(trim(kv[1]).c_str());
				break;
			}
		}
	}

	return chn_cnt;
}

void cutScreen() {

	std::map<int, int> mapScreen = { {1,4}, {4, 9}, {9, 16}, {16, 1} };

	printLogChar("------------------cutScreen------------begin---------------");

	TcpClient client(gBuf_dhDeviceControl.m_var.appParams.nvrIp, D4K_PORT);
	if (client.Connect()) {

		char buffer[BUF_LEN];
		const char* message4 = "cmd : DataSync\r\ntype : 4\r\n";
		printLogChar(message4);
		client.Send(message4, strlen(message4));
		memset(buffer, 0x00, sizeof(buffer));
		int len = client.Receive(buffer, sizeof(buffer) - 1);
		//cmd : SyncFinsh
		printLogChar(buffer);

		int ret = strcmp(buffer, "cmd : SyncFinsh\r\n");

		if (ret == 0) {
			client.Send(message4, strlen(message4));
			printLogChar(message4);
			memset(buffer, 0x00, sizeof(buffer));
			len = client.Receive(buffer, sizeof(buffer) - 1);
			printLogChar(buffer);
		}

		int chn_cnt = getChn(buffer);

		const auto& item = mapScreen.find(chn_cnt);
		if (item != mapScreen.end()) {

			char cmd[256];
			_snprintf(cmd, sizeof(cmd), "cmd : CutScreen\r\nsplit_num : %d\r\ndevice_id : 0\r\n", item->second);
			printLogChar(cmd);
			client.Send(cmd, strlen(cmd));

			memset(buffer, 0x00, sizeof(buffer));
			int len = client.Receive(buffer, sizeof(buffer) - 1);
			if (len > 0)
				buffer[len + 1] = '\0';

			printLogChar(buffer);

			int ret = strcmp(buffer, "cmd : SyncFinsh\r\n");

			if (ret == 0) {
				printLogChar(cmd);
				client.Send(cmd, strlen(cmd));
				memset(buffer, 0x00, sizeof(buffer));
				len = client.Receive(buffer, sizeof(buffer) - 1);
				printLogChar(buffer);
			}

		}

	}

	printLogChar("------------------cutScreen------------end---------------");
}

void callVideo(TcpClient& client, int chn, int id) {
	printLogChar("------------------callVideo------------begin---------------");

	char cmd[256];
	_snprintf(cmd, sizeof(cmd), "cmd : CallVedio\r\nchn : %d\r\nid : %d\r\n", chn, id);
	printLogChar(cmd);

	client.Send(cmd, strlen(cmd));

	char buffer[512];
	memset(buffer, 0x00, sizeof(buffer));
	int len = client.Receive(buffer, sizeof(buffer) - 1);
	if (len > 0)
		buffer[len + 1] = '\0';

	//printf("%s\r\n", buffer);
	printLogChar(buffer);

	int ret = strcmp(buffer, "cmd : SyncFinsh\r\n");

	if (ret == 0) {
		client.Send(cmd, strlen(cmd));
		printLogChar(cmd);

		memset(buffer, 0x00, sizeof(buffer));
		len = client.Receive(buffer, sizeof(buffer) - 1);

		if (len > 0)
			buffer[len + 1] = '\0';

		//printf("%s\r\n", buffer);
		printLogChar(buffer);
	}	

	printLogChar("------------------callVideo------------end---------------");
}



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

		if (count >= 3) {
			count = 0;
			mapIpc[ipcInfo.id] = ipcInfo;
		}
	}
}

void cutScreen2() {

	std::map<int, int> mapScreen = { {4, 9}, {9, 16}, {16, 4} };

	//std::map<int, int> mapScreen = { {1,9}, {4, 9}, {6, 9}, {9, 9} };
	printLogChar("------------------cutScreen2------------begin---------------");

	TcpClient client(gBuf_dhDeviceControl.m_var.appParams.nvrIp, D4K_PORT);
	if (client.Connect()) {

		char buffer[BUF_LEN];
		const char* message4 = "cmd : DataSync\r\ntype : 4\r\n";
		client.Send(message4, strlen(message4));
		printLogChar(message4);
		memset(buffer, 0x00, sizeof(buffer));
		int len = client.Receive(buffer, sizeof(buffer) - 1);
		if (len > 0)
			buffer[len + 1] = '\0';

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
		int chn_cnt = getChn(buffer);

		const char* message1 = "cmd : DataSync\r\ntype : 1\r\n";
		client.Send(message1, strlen(message1));
		printLogChar(message1);
		memset(buffer, 0x00, sizeof(buffer));
		len = client.Receive(buffer, sizeof(buffer) - 1);
		if (len > 0)
			buffer[len + 1] = '\0';

		ret = strcmp(buffer, "cmd : SyncFinsh\r\n");

		if (ret == 0) {
			client.Send(message1, strlen(message1));
			printLogChar(message1);
			memset(buffer, 0x00, sizeof(buffer));
			len = client.Receive(buffer, sizeof(buffer) - 1);
			if (len > 0)
				buffer[len + 1] = '\0';
			printLogChar(buffer);
		}

		std::map<int, IpcInfoDef> mapIpc;
		parse_ipc_info_1(buffer, mapIpc);

		const auto& item = mapScreen.find(chn_cnt);
		if (item == mapScreen.end()) {
			chn_cnt = 4;
		}
		else {
			chn_cnt = item->second;
		}

		char cmd[256];
		_snprintf(cmd, sizeof(cmd), "cmd : CutScreen\r\nsplit_num : %d\r\ndevice_id : 0\r\n", chn_cnt);
		client.Send(cmd, strlen(cmd));
		printLogChar(cmd);

		memset(buffer, 0x00, sizeof(buffer));
		len = client.Receive(buffer, sizeof(buffer) - 1);
		if (len > 0)
			buffer[len + 1] = '\0';

		ret = strcmp(buffer, "cmd : SyncFinsh\r\n");

		if (ret == 0) {
			client.Send(cmd, strlen(cmd));
			printLogChar(cmd);
			memset(buffer, 0x00, sizeof(buffer));
			len = client.Receive(buffer, sizeof(buffer) - 1);
			if (len > 0)
				buffer[len + 1] = '\0';

			printLogChar(buffer);
		}

		//printf("%s\r\n", buffer);
	

		int count = 0;
		for (const auto& it : mapIpc) {
			if (chn_cnt <= count)
				break;

			count++;

			callVideo(client, count, it.first);
		}	
	}
	else {
		printLogChar("connect failed");
	}

	printLogChar("------------------cutScreen2------------end---------------");
}


void selectChannel(int channel) {

	TcpClient client(gBuf_dhDeviceControl.m_var.appParams.nvrIp, D4K_PORT);
	printLogChar("------------------selectChannel------------begin---------------");

	if (client.Connect()) {
		char buffer[BUF_LEN] = { '\0' };
		//const char* message = "cmd : AmplifierDevChn\r\ndev : 0\r\nchn : 3\r\n";

		_snprintf(buffer, sizeof(buffer), "cmd : AmplifierDevChn\r\ndev : 0\r\nchn : %d\r\n", channel);
		client.Send(buffer, strlen(buffer));
		printLogChar(buffer);

		memset(buffer, 0x00, sizeof(buffer));
		int len = client.Receive(buffer, sizeof(buffer) - 1);
		if (len > 0)
			buffer[len + 1] = '\0';

		printLogChar(buffer);

	}

	printLogChar("------------------selectChannel------------end---------------");
}

void selectIpc(int id) {
	printLogChar("------------------selectIpc------------begin---------------");

	TcpClient client(gBuf_dhDeviceControl.m_var.appParams.nvrIp, D4K_PORT);
	if (client.Connect()) {
		char cmd[256];
		_snprintf(cmd, sizeof(cmd), "cmd : CutScreen\r\nsplit_num : %d\r\ndevice_id : 0\r\n", 1);
		client.Send(cmd, strlen(cmd));

		printLogChar(cmd);

		char buffer[BUF_LEN];
		memset(buffer, 0x00, sizeof(buffer));
		int len = client.Receive(buffer, sizeof(buffer) - 1);
		if (len > 0)
			buffer[len + 1] = '\0';

		//printf("%s\r\n", buffer);
		printLogChar(buffer);
		

		callVideo(client, 1, id);		

	}
	else {
		printLogChar("connect failed");
	}

	printLogChar("------------------selectIpc------------end---------------");
}

void process(int channel) {
	if (channel == -1) {
		cutScreen2();
	}
	else {
		selectIpc(channel);
	}
}

void execCmd(OnvifMsg_nvrControl* pNc) {

	printLogChar("------------------execCmd------------begin---------------");
	std::stringstream ss;
	ss << "cmd:" << pNc->usCmd << ",iChannel:" << pNc->iChannel;
	
	printLogChar(ss.str().c_str());
	

	do {
		if (!pNc)  break;
		//
		switch (pNc->usCmd) {
		case  CONST_nvrControlCmd_selectChannel:
			process(pNc->iChannel);
			break;

		default:
			break;
		}

		//
	} while (false);

	printLogChar("------------------execCmd------------end---------------");
}


//
int  dhDeviceControl_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
{
	printLogChar("------------------dhDeviceControl_qisPipe_onRead------------begin---------------");
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
	gBuf_dhDeviceControl.m_var.dwLastTickCnt_recvd = myGetTickCount(nullptr);

	//
	//
	switch (pMsgCommon->iSubtype) {
#if 0
	case  CONST_onvifMsg_subtype_dbg:
	{
		OnvifMsg_dbg* pDbg = (OnvifMsg_dbg*)pMsgCommon;
		OnvifMsg_dbg  m = { 0 };
		m.uiType = CONST_qisMsgType_onvif;
		m.iSubtype = CONST_onvifMsg_subtype_dbg;
		_snprintf(m.buf, mycountof(m.buf), "dhPtz recvd: %s", pDbg->buf);
		qisPipe_writeMsg(&m, sizeof(m), gBuf_dhPtz.m_var.pQisPipe);

	}
	break;
#endif
	case  CONST_onvifMsg_subtype_ping:
	{
		OnvifMsg_ping* pPing = (OnvifMsg_ping*)pMsgCommon;

		if (0) {
			showInfo_open0(0, 0, _T("deviceControl: recv ping"));
		}
		//
		if (pPing->tn != gBuf_dhDeviceControl.m_var.appParams.tn) {
			TCHAR  tBuf[128];
			_sntprintf(tBuf, mycountof(tBuf), _T("deviceControl err: ping.tn %d != appParams.tn %d"), pPing->tn, gBuf_dhDeviceControl.m_var.appParams.tn);
			showInfo_open0(0, 0, tBuf);
			//
			gBuf_dhDeviceControl.m_var.bErr = true;
		}
	}
	break;
	case  CONST_onvifMsg_subtype_nvrControl:
	{
		OnvifMsg_ptz* pPtz = (OnvifMsg_ptz*)pMsgCommon;
		//
		int  ii = 0;

		//printLogChar("------------------dhDeviceControl_qisPipe_onRead------------copydata---------------");

		execCmd((OnvifMsg_nvrControl*)pPtz);

		OnvifMsg_nvrInfo m = { 0 };
		m.uiType = CONST_qisMsgType_onvif;
		m.iSubtype = CONST_onvifMsg_subtype_nvrControl;
		m.ucbResp = true;

		//
		qisPipe_writeMsg(&m, sizeof(m), gBuf_dhDeviceControl.m_var.pQisPipe);

		//gBuf_dhDeviceControl.m_var.m_bDone_nvrInfo = true;

		//
		/*
		COPYDATASTRUCT		tmpCopyData;

		tmpCopyData.lpData = pPtz;
		tmpCopyData.cbData = sizeof(*pPtz);
		int  iRet = ::SendMessageTimeout(gBuf_dhDeviceControl.m_var.hMainWnd, WM_COPYDATA, NULL, (LPARAM)&tmpCopyData,0,1000,NULL);
		*/

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
