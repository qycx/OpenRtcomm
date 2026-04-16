#include "stdafx.h"
#include "TcpClient.h"
#include "TCPClient.h"
#include <string>
#include <iostream>
#include <sstream>
#include <thread>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")
using namespace std;

extern int printLogChar(const char* log);
extern int printLogChar(int log);


int TcpClient::Initialize() {

	WORD version = MAKEWORD(2, 2);
	WSADATA data;


	if (WSAStartup(version, &data) != 0) {
		//std::cout << "WSAStartup Failed!" << std::endl;
		printLogChar("WSAStartup Failed!");
		return 0;
	}

	m_init = true;

	//std::cout << "WSAStartup Success!" << std::endl;
	printLogChar("WSAStartup Success!");
	return 1;
}


void TcpClient::Start() {

	//while (1)
	bool ret = false;
	{
		//if (this->ConnectStatus()) {
		//	Sleep(500);
		//	//continue;
		//}

		sclient_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		sockaddr_in servAddr;
		servAddr.sin_family = AF_INET;
		servAddr.sin_port = htons(port_);
		servAddr.sin_addr.S_un.S_addr = inet_addr(ip_);

		lastConnectTime = GetTickCount64();

		int sendBufSize = 1024 * 16 * 1024;
		int result = setsockopt(sclient_, SOL_SOCKET, SO_SNDBUF, (char*)&sendBufSize, sizeof(sendBufSize));
		if (result == SOCKET_ERROR) {
			//std::cerr << "setsockopt failed" << std::endl;
			printLogChar("setsockopt Failed!");
			CloseSocket();
			//WSACleanup();
			//return false;
			isConnected = false;
		}


		if (connect(sclient_, (LPSOCKADDR)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		{
			//std::cout << "Connect Failed!" << std::endl;
			printLogChar("Connect Failed!");
			//continue;

			isConnected = false;
		}
		else {
			//std::cout << "Connect Success!" << std::endl;
			printLogChar("Connect Success!");
			ret = true;

			isConnected = true;
		}
	}
	//return ret;
}


void TcpClient::SetRecvFunc(RecvCallBack Func) {
	char buffer[1024];
	while (1) {
		int ret = recv(sclient_, buffer, 1024, 0);

		if (ret > 0) {
			(Func)(buffer, ret);
			memset(buffer, '\0', 1024);
		}
		else {
			Sleep(100);
		}
	}
}

bool TcpClient::CloseSocket() {

	if (sclient_ != INVALID_SOCKET) {
		closesocket(sclient_);
		//WSACleanup();
		sclient_ = INVALID_SOCKET;

		return true;
	}
	return false;
}

int TcpClient::ReConntct()
{
	//std::cout << "准备重连" << endl;
	//shutdown(ClientSocket,2);

	//printLogChar("ReConntct in");

	DWORD curTime = GetTickCount64();

	if (curTime - lastConnectTime < 10000) {
		return -2;
	}

	printLogChar("ReConntct...");

	lastConnectTime = curTime;

	//closesocket(sclient_);
	CloseSocket();


	sclient_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port_);
	servAddr.sin_addr.S_un.S_addr = inet_addr(ip_);

	int sendBufSize = 1024 * 16 * 1024;
	int result = setsockopt(sclient_, SOL_SOCKET, SO_SNDBUF, (char*)&sendBufSize, sizeof(sendBufSize));
	if (result == SOCKET_ERROR) {
		printLogChar("reconnect setsockopt failed");
		return -1;

	}

	if (connect(sclient_, (LPSOCKADDR)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		//std::cout << "Connect Failed!" << std::endl;
		printLogChar("reconnect Failed!");
		//continue;

		isConnected = false;

		return -3;
	}
	else {
		//std::cout << "Connect Success!" << std::endl;

		printLogChar("reconnect success");
		isConnected = true;

		SendRecordStartNew(m_name.c_str(), m_isRecord, m_isLive, m_meetingId, m_gid, m_liveUrl.c_str());
		SendVideoStart(m_name.c_str(), m_videoName.c_str());
		printLogChar("reconnect success 22222222");
		printLogChar(m_audioName.size());
		printLogChar("reconnect success 22222222 end");

		if (m_vpsSps.size() > 0) {
			printLogChar("reconnect success :send vps sps");
			bool isReconnect = false;
			SendVideoData(m_name.c_str(), m_videoName.c_str(), (unsigned char*)m_vpsSps.data(), m_vpsSps.size(), m_uiSampleTimeInMs,
				m_uiPts, m_orgSampleTimeInMs, 0, 0, isReconnect);
		}

		for (auto const& item : m_audioName) {
			printLogChar("reconnect success 3333333333");
			printLogChar(item.first.c_str());
			SendAudioStart(m_name.c_str(), item.first.c_str());
		}

		printLogChar("reconnect success 444444444444");

		return 0;
	}


}



int TcpClient::SendBuf(const char* buffer, int len) {
	//printLogCharN("Send in ................");

	if (!isConnected) {
		if (ReConntct() != 0) {
			//printLogChar("SendBuf ReConntct 0!");
			return 0;
		}
	}

	int nTotal = 0;
	int nLeft = len;

	bool isDeConnected = false;
	while (nTotal < len) {
		int nBytes = send(sclient_, buffer + nTotal, nLeft, 0);
		if (nBytes <= 0) {
			isDeConnected = true;
			printLogChar("SendBuf isDeConnected!");
			break;
		}
		nTotal += nBytes;
		nLeft -= nBytes;
	}

	if (nTotal == len) {
		//std::cout << "Send Success!" << std::endl;
		//printLogChar("SendBuf Success!");
		return 1;
	}

	if (isDeConnected) {
		isConnected = false;
		ReConntct();
	}

	//std::cout << "Send Failed!" << std::endl;
	printLogChar("SendBuf Failed!");
	return 0;
}

int TcpClient::SendBuf(const char* buffer, int len, bool& isReconnect) {
	//printLogCharN("Send in ................");

	if (!isConnected) {
		if (ReConntct() != 0) {
			//printLogChar("SendBuf ReConntct 0!");
			
			return 0;
		}
		printLogChar("SendBuf isReconnect true");
		isReconnect = true;
	}

	int nTotal = 0;
	int nLeft = len;

	bool isDeConnected = false;
	while (nTotal < len) {
		int nBytes = send(sclient_, buffer + nTotal, nLeft, 0);
		if (nBytes <= 0) {
			isDeConnected = true;
			printLogChar("SendBuf isDeConnected!");
			break;
		}
		nTotal += nBytes;
		nLeft -= nBytes;
	}

	if (nTotal == len) {
		//std::cout << "Send Success!" << std::endl;
		//printLogChar("SendBuf Success!");
		return 1;
	}

	if (isDeConnected) {
		isConnected = false;
		ReConntct();
	}

	//std::cout << "Send Failed!" << std::endl;
	printLogChar("SendBuf Failed!");
	return 0;
}

bool TcpClient::ConnectStatus() {

	//std::string str = "12131215";

	int flag = 0x12131215;

	int uflag = htonl(flag);

	int len = 0;

	static int cmd = 0;
	cmd++;

	//if (cmd > 20)
	//	return true;

	int ucmd = htonl(cmd);

	char buf[256] = { '\0' };
	_snprintf(buf, sizeof(buf), "%8d%4d", flag, 16);

	const char* name = "conf20240301112233_1";

	memcpy(buf, (void*)&uflag, sizeof(uflag));
	//len += 4;
	//memcpy(buf + 4, (void*)&uLen, sizeof(uLen));
	//len += 4;	
	memcpy(buf + 8, (void*)&ucmd, sizeof(ucmd));
	len += 4;
	int namLen = strlen(name);
	int nameLen = htonl(namLen);
	memcpy(buf + 12, (void*)&nameLen, sizeof(nameLen));
	len += 4;
	memcpy(buf + 16, (void*)name, strlen(name));
	len += strlen(name);



	int uLen = htonl(len);
	memcpy(buf + 4, (void*)&uLen, sizeof(uLen));



	//const char* send_Heart = str.c_str();
	//int result = send(sclient_, send_Heart, sizeof(send_Heart), 0);
	int result = SendBuf(buf, len + 8);
	//int result = send(sclient_, (char*)&uflag, sizeof(uflag), 0);

	if (result > 0) {
		return true;
	}
	return false;

}


bool TcpClient::SendRecordStart(const char* name) {

	//std::string str = "12131215";

	int flag = 0x12131215;

	int uflag = htonl(flag);

	int len = 0;

	static int cmd = Cmd_Def::RecordStart;

	//if (cmd > 20)
	//	return true;

	int ucmd = htonl(cmd);

	char buf[256] = { '\0' };
	//_snprintf(buf, sizeof(buf), "%8d%4d", flag, 16);

	//const char* name = "conf20240301112233_1";

	memcpy(buf, (void*)&uflag, sizeof(uflag));
	//len += 4;
	//memcpy(buf + 4, (void*)&uLen, sizeof(uLen));
	//len += 4;	
	memcpy(buf + 8, (void*)&ucmd, sizeof(ucmd));
	len += 4;
	int namLen = strlen(name);
	int nameLen = htonl(namLen);
	memcpy(buf + 12, (void*)&nameLen, sizeof(nameLen));
	len += 4;
	memcpy(buf + 16, (void*)name, strlen(name));
	len += strlen(name);



	int uLen = htonl(len);
	memcpy(buf + 4, (void*)&uLen, sizeof(uLen));



	//const char* send_Heart = str.c_str();
	//int result = send(sclient_, send_Heart, sizeof(send_Heart), 0);
	//int result = send(sclient_, buf, len + 8, 0);
	int result = SendBuf(buf, len + 8);
	//int result = send(sclient_, (char*)&uflag, sizeof(uflag), 0);

	if (result > 0) {
		return true;
	}
	return false;

}


bool TcpClient::SendRecordStartNew(const char* name, bool isRecord, bool isLive, __int64 meetingId, unsigned  __int64 gid, const char* liveUrl) {

	//std::string str = "12131215";

	m_name = name;
	m_isRecord = isRecord;
	m_isLive = isLive;
	m_meetingId = meetingId;
	m_gid = gid;
	m_liveUrl = liveUrl;


	int flag = 0x12131215;

	int uflag = htonl(flag);

	int len = 0;

	static int cmd = Cmd_Def::RecordStart;

	//if (cmd > 20)
	//	return true;

	int ucmd = htonl(cmd);

	char* buf = new char[512];
	//_snprintf(buf, sizeof(buf), "%8d%4d", flag, 16);

	//const char* name = "conf20240301112233_1";

	memcpy(buf, (void*)&uflag, sizeof(uflag));
	//len += 4;
	//memcpy(buf + 4, (void*)&uLen, sizeof(uLen));
	//len += 4;	
	memcpy(buf + 8, (void*)&ucmd, sizeof(ucmd));
	len += 4;
	int namLen = strlen(name);
	int nameLen = htonl(namLen);
	memcpy(buf + 12, (void*)&nameLen, sizeof(nameLen));
	len += 4;
	memcpy(buf + 16, (void*)name, namLen);
	len += namLen;

	int record = htonl(isRecord);
	memcpy(buf + 16 + namLen, (void*)&record, sizeof(record));
	len += 4;

	int live = htonl(isLive);
	memcpy(buf + 20 + namLen, (void*)&live, sizeof(live));
	len += 4;

	uint32_t meetingId1 = htonl((uint32_t)(meetingId >> 32));
	uint32_t meetingId2 = htonl((uint32_t)(meetingId & 0xFFFFFFFF));
	//long long meetingIdN = ((long long)meetingId1 << 32) | meetingId2;

	memcpy(buf + 24 + namLen, (void*)&meetingId1, sizeof(meetingId1));
	memcpy(buf + 28 + namLen, (void*)&meetingId2, sizeof(meetingId2));
	len += 8;

	uint32_t gid1 = htonl((uint32_t)(gid >> 32));
	uint32_t gid2 = htonl((uint32_t)(gid & 0xFFFFFFFF));
	//long long gidN = ((long long)gid1 << 32) | gid2;
	memcpy(buf + 32 + namLen, (void*)&gid1, sizeof(gid1));
	memcpy(buf + 36 + namLen, (void*)&gid2, sizeof(gid2));
	len += 8;

	int liveUrlLen = strlen(liveUrl);
	int liveUrlLenN = htonl(liveUrlLen);

	memcpy(buf + 40 + namLen, (void*)&liveUrlLenN, sizeof(liveUrlLenN));
	len += 4;

	memcpy(buf + 44 + namLen, (void*)liveUrl, liveUrlLen);
	len += liveUrlLen;


	int uLen = htonl(len);
	memcpy(buf + 4, (void*)&uLen, sizeof(uLen));


	std::stringstream ss;
	ss << "SendRecordStartNew:" << name << "," << isRecord << "," << isLive << "," << meetingId << "," << gid << std::endl;
	printLogChar(ss.str().c_str());

	//const char* send_Heart = str.c_str();
	//int result = send(sclient_, send_Heart, sizeof(send_Heart), 0);
	int result = SendBuf(buf, len + 8);
	//int result = send(sclient_, (char*)&uflag, sizeof(uflag), 0);

	delete[] buf;

	if (result > 0) {
		return true;
	}
	return false;

}


bool TcpClient::SendRecordStop(const char* name) {

	//std::string str = "12131215";

	int flag = 0x12131215;

	int uflag = htonl(flag);

	int len = 0;

	static int cmd = Cmd_Def::RecordStop;

	//if (cmd > 20)
	//	return true;

	int ucmd = htonl(cmd);

	char buf[256] = { '\0' };
	//_snprintf(buf, sizeof(buf), "%8d%4d", flag, 16);

	//const char* name = "conf20240301112233_1";

	memcpy(buf, (void*)&uflag, sizeof(uflag));
	//len += 4;
	//memcpy(buf + 4, (void*)&uLen, sizeof(uLen));
	//len += 4;	
	memcpy(buf + 8, (void*)&ucmd, sizeof(ucmd));
	len += 4;
	int namLen = strlen(name);
	int nameLen = htonl(namLen);
	memcpy(buf + 12, (void*)&nameLen, sizeof(nameLen));
	len += 4;
	memcpy(buf + 16, (void*)name, strlen(name));
	len += strlen(name);



	int uLen = htonl(len);
	memcpy(buf + 4, (void*)&uLen, sizeof(uLen));



	//const char* send_Heart = str.c_str();
	//int result = send(sclient_, send_Heart, sizeof(send_Heart), 0);
	int result = SendBuf(buf, len + 8);
	//int result = send(sclient_, (char*)&uflag, sizeof(uflag), 0);

	std::stringstream ss;
	ss << "SendRecordStop: name=" << name << ", result = " << result << ", len = " << len + 8;
	printLogChar(ss.str().c_str());

	if (result > 0) {
		return true;
	}
	return false;

}

void TcpClient::SetVideoType(const char* videoName) {
	int len = strlen(videoName); 

	if (len >= 4) {
		if (*(videoName + len - 1) == '4' && *(videoName + len - 2) == '6' && *(videoName + len - 3) == '2' && *(videoName + len - 4) == '.') {
			m_videoType = Video_Type_H264;
		} else if (*(videoName + len - 1) == '5' && *(videoName + len - 2) == '6' && *(videoName + len - 3) == '2' && *(videoName + len - 4) == '.') {
			m_videoType = Video_Type_H265;
		}
		else {
			m_videoType = Video_Type_Unknow;
		}		

	}
	else {
		m_videoType = Video_Type_Unknow;
	}

	
}


bool TcpClient::SendVideoStart(const char* name, const char* videoName) {

	//std::string str = "12131215";

	m_videoName = videoName;

	SetVideoType(videoName);


	int flag = 0x12131215;

	int uflag = htonl(flag);

	int len = 0;

	static int cmd = Cmd_Def::VideoStart;

	//if (cmd > 20)
	//	return true;

	int ucmd = htonl(cmd);

	char buf[256] = { '\0' };
	//_snprintf(buf, sizeof(buf), "%8d%4d", flag, 16);

	//const char* name = "conf20240301112233_1";

	memcpy(buf, (void*)&uflag, sizeof(uflag));
	//len += 4;
	//memcpy(buf + 4, (void*)&uLen, sizeof(uLen));
	//len += 4;	
	memcpy(buf + 8, (void*)&ucmd, sizeof(ucmd));
	len += 4;
	int namLen = strlen(name);
	int nameLen = htonl(namLen);
	memcpy(buf + 12, (void*)&nameLen, sizeof(nameLen));
	len += 4;
	memcpy(buf + 16, (void*)name, strlen(name));
	len += strlen(name);


	int videoNamLen = strlen(videoName);
	int videoNameLen = htonl(videoNamLen);
	memcpy(buf + 16 + strlen(name), (void*)&videoNameLen, sizeof(videoNameLen));
	len += 4;
	memcpy(buf + 20 + strlen(name), (void*)videoName, strlen(videoName));
	len += strlen(videoName);


	int uLen = htonl(len);
	memcpy(buf + 4, (void*)&uLen, sizeof(uLen));

	std::stringstream ss;
	ss << "SendVideoStart:" << name << "," << videoName << std::endl;
	printLogChar(ss.str().c_str());

	//const char* send_Heart = str.c_str();
	//int result = send(sclient_, send_Heart, sizeof(send_Heart), 0);
	int result = SendBuf(buf, len + 8);
	//int result = send(sclient_, (char*)&uflag, sizeof(uflag), 0);

	if (result > 0) {
		return true;
	}
	return false;

}

#define	M_nalType_h264(  p  )	(p)[2]  ==  1  ?  (  (p)[3]  &  0x1f  )  :  (  (p)[4]  &  0x1f  )
#define	M_nalType_h265(  p  )	((p)[2]  ==  1  ?  (  (p)[3]  &  0x7e  )  :  (  (p)[4]  &  0x7e  ))>>1

#define		CONST_h264nalType_idr			5
#define     CONST_h264nalType_sei           6
#define		CONST_h264nalType_sps			7
#define		CONST_h264nalType_pps			8

//
#define		CONST_h265naleType_CODED_SLICE_IDR			19		//  NAL_UNIT_CODED_SLICE_IDR, // 19 // Current name in the spec: IDR_W_DLP
#define		CONST_h265nalType_CODED_SLICE_IDR_N_LP		20		//  NAL_UNIT_CODED_SLICE_IDR_N_LP, // 20

#define		CONST_h265nalType_vps			32
#define		CONST_h265nalType_sps			33
#define		CONST_h265nalType_pps			34

extern int  nalType_h265(unsigned  char* pBuf, int  bufLen);

/*
int  nalType_h265(unsigned  char* pBuf, int  bufLen)
{
	unsigned  int  code = -1;
	//
	if (bufLen <= 3)  return  0;
	int  iType = 0;
	int  i;

	for (i = 0; i < bufLen - 1; i++) {
		code = (code << 8) + pBuf[i];
		if ((code & 0xffffff00) == 0x100) {
			char  na12 = pBuf[i + 1];
			//
			int  type = (code & 0x7E) >> 1;
			//
			if (code & 0x81)  return  0;  //  forbidden and reserved zero bits
			//
			if (na12 & 0xf8)  return  0;  //  reserved zero

			//
			return  type;
		}
	}


	return  iType;
}*/

bool TcpClient::SendVideoData(const char* name, const char* videoName, unsigned char* data, int dataLen,
	unsigned  int	uiSampleTimeInMs, unsigned  int	uiPts, unsigned  int orgSampleTimeInMs, int qsize0, int qsize1, bool& isReconnect) {

	//std::string str = "12131215";

	//printLogChar("----------SendVideoData----------begin------");

	int frame_type = -1;
	if (m_videoType == Video_Type_H264)
		frame_type = M_nalType_h264(data);
	else if (m_videoType == Video_Type_H265)
		frame_type = nalType_h265(data, dataLen);

	if (frame_type == CONST_h265nalType_vps || frame_type == CONST_h264nalType_sps) {
		m_vpsSps.resize(dataLen);
		m_vpsSps.assign((char*)data, dataLen);
		m_uiSampleTimeInMs = uiSampleTimeInMs;
		m_uiPts = uiPts;
		/*printLogChar("----------SendVideoData----------vpssps-------begin------");
		printLogChar(m_videoType);
		printLogChar(frame_type);
		printLogChar("----------SendVideoData----------vpssps-------end--------");*/
	}

	int flag = 0x12131215;

	int uflag = htonl(flag);

	int len = 0;

	static int cmd = Cmd_Def::VideoData;

	//if (cmd > 20)
	//	return true;

	int ucmd = htonl(cmd);

	//char buf[256] = { '\0' };
	int buflen = dataLen + 256;
	char* buf = new char[buflen];
	//_snprintf(buf, sizeof(buf), "%8d%4d", flag, 16);

	//const char* name = "conf20240301112233_1";

	memcpy(buf, (void*)&uflag, sizeof(uflag));
	//len += 4;
	//memcpy(buf + 4, (void*)&uLen, sizeof(uLen));
	//len += 4;	
	memcpy(buf + 8, (void*)&ucmd, sizeof(ucmd));
	len += 4;
	int namLen = strlen(name);
	int nameLen = htonl(namLen);
	memcpy(buf + 12, (void*)&nameLen, sizeof(nameLen));
	len += 4;
	memcpy(buf + 16, (void*)name, strlen(name));
	len += strlen(name);


	int videoNamLen = strlen(videoName);
	int videoNameLen = htonl(videoNamLen);
	memcpy(buf + 16 + strlen(name), (void*)&videoNameLen, sizeof(videoNameLen));
	len += 4;
	memcpy(buf + 20 + strlen(name), (void*)videoName, strlen(videoName));
	len += strlen(videoName);

	int sampleTimeInMs = htonl(uiSampleTimeInMs);
	memcpy(buf + 20 + strlen(name) + strlen(videoName), (void*)&sampleTimeInMs, sizeof(sampleTimeInMs));
	len += 4;

	memcpy(buf + 24 + strlen(name) + strlen(videoName), (void*)data, dataLen);
	len += dataLen;


	int uLen = htonl(len);
	memcpy(buf + 4, (void*)&uLen, sizeof(uLen));


	static int count = 0;
	//const char* send_Heart = str.c_str();
	//int result = send(sclient_, send_Heart, sizeof(send_Heart), 0);
	int result = SendBuf(buf, len + 8, isReconnect);
	//int result = send(sclient_, (char*)&uflag, sizeof(uflag), 0);


	count++;

	unsigned  int interval = orgSampleTimeInMs - m_lastVideoPts;

	if (interval > 300) {

		std::stringstream ss;
		ss << "SendVideoData: name=" << name << ",result=" << result << ",len=" << len + 8 << ",count=" << count
			<< ",uiSampleTimeInMs=" << uiSampleTimeInMs << ",uiPts=" << uiPts << ",orgSampleTimeInMs=" << orgSampleTimeInMs
			<< ",lastVideoPts=" << m_lastVideoPts << ",interval=" << interval << ",qsize0=" << qsize0 << ",qsize1=" << qsize1;
		printLogChar(ss.str().c_str());
	}


	m_lastVideoPts = orgSampleTimeInMs;

	delete[] buf;

	if (result > 0) {
		return true;
	}
	return false;

}



bool TcpClient::SendAudioStart(const char* name, const char* audioName) {

	//std::string str = "12131215";

	std::stringstream ss;
	ss << "SendAudioStart:" << name << "," << audioName << std::endl;
	printLogChar(ss.str().c_str());


	if (m_audioName.find(audioName) == m_audioName.end()) {
		m_audioName[audioName] = 1;
	}


	int flag = 0x12131215;

	int uflag = htonl(flag);

	int len = 0;

	static int cmd = Cmd_Def::AudioStart;

	//if (cmd > 20)
	//	return true;

	int ucmd = htonl(cmd);

	char buf[256] = { '\0' };

	//_snprintf(buf, sizeof(buf), "%8d%4d", flag, 16);

	//const char* name = "conf20240301112233_1";

	memcpy(buf, (void*)&uflag, sizeof(uflag));
	//len += 4;
	//memcpy(buf + 4, (void*)&uLen, sizeof(uLen));
	//len += 4;	
	memcpy(buf + 8, (void*)&ucmd, sizeof(ucmd));
	len += 4;
	int namLen = strlen(name);
	int nameLen = htonl(namLen);
	memcpy(buf + 12, (void*)&nameLen, sizeof(nameLen));
	len += 4;
	memcpy(buf + 16, (void*)name, strlen(name));
	len += strlen(name);


	int audioNamLen = strlen(audioName);
	int audioNameLen = htonl(audioNamLen);
	memcpy(buf + 16 + strlen(name), (void*)&audioNameLen, sizeof(audioNameLen));
	len += 4;
	memcpy(buf + 20 + strlen(name), (void*)audioName, audioNamLen);
	len += audioNamLen;


	int uLen = htonl(len);
	memcpy(buf + 4, (void*)&uLen, sizeof(uLen));



	//const char* send_Heart = str.c_str();
	//int result = send(sclient_, send_Heart, sizeof(send_Heart), 0);
	int result = SendBuf(buf, len + 8);
	//int result = send(sclient_, (char*)&uflag, sizeof(uflag), 0);

	if (result > 0) {
		return true;
	}
	return false;

}

bool TcpClient::SendAudioStop(const char* name, const char* audioName) {

	std::stringstream ss;
	ss << "SendAudioStop:" << name << "," << audioName << std::endl;
	printLogChar(ss.str().c_str());

	m_audioName.erase(audioName);
	return true;
}


bool TcpClient::SendAudioData(const char* name, const char* audioName, unsigned char* data, int dataLen, unsigned  int	uiSampleTimeInMs, unsigned  int	uiPts, unsigned  int orgSampleTimeInMs, int qsize0, int qsize1) {

	//std::string str = "12131215";

	//return true;

	int flag = 0x12131215;

	int uflag = htonl(flag);

	int len = 0;

	static int cmd = Cmd_Def::AudioData;

	//if (cmd > 20)
	//	return true;

	int ucmd = htonl(cmd);

	//char buf[256] = { '\0' };
	int buflen = dataLen + 256;
	char* buf = new char[buflen];
	//_snprintf(buf, sizeof(buf), "%8d%4d", flag, 16);

	//const char* name = "conf20240301112233_1";

	memcpy(buf, (void*)&uflag, sizeof(uflag));
	//len += 4;
	//memcpy(buf + 4, (void*)&uLen, sizeof(uLen));
	//len += 4;	
	memcpy(buf + 8, (void*)&ucmd, sizeof(ucmd));
	len += 4;
	int namLen = strlen(name);
	int nameLen = htonl(namLen);
	memcpy(buf + 12, (void*)&nameLen, sizeof(nameLen));
	len += 4;
	memcpy(buf + 16, (void*)name, strlen(name));
	len += strlen(name);


	int audioNamLen = strlen(audioName);
	int audioNameLen = htonl(audioNamLen);
	memcpy(buf + 16 + strlen(name), (void*)&audioNameLen, sizeof(audioNameLen));
	len += 4;
	memcpy(buf + 20 + strlen(name), (void*)audioName, audioNamLen);
	len += audioNamLen;


	int sampleTimeInMs = htonl(uiSampleTimeInMs);
	memcpy(buf + 20 + strlen(name) + audioNamLen, (void*)&sampleTimeInMs, sizeof(sampleTimeInMs));
	len += 4;


	memcpy(buf + 24 + strlen(name) + audioNamLen, (void*)data, dataLen);
	len += dataLen;


	int uLen = htonl(len);
	memcpy(buf + 4, (void*)&uLen, sizeof(uLen));

	static int count = 0;

	//const char* send_Heart = str.c_str();
	//int result = send(sclient_, send_Heart, sizeof(send_Heart), 0);
	int result = SendBuf(buf, len + 8);
	//int result = send(sclient_, (char*)&uflag, sizeof(uflag), 0);

	delete[] buf;

	count++;

	unsigned  int interval = orgSampleTimeInMs - m_lastAudioPts;

	if (0/*interval > 100*/) 
	{
		std::stringstream ss;
		ss << "SendAudioData: name=" << name << ",result=" << result << ",len=" << len + 8 << ",count=" << count
			<< ",uiSampleTimeInMs=" << uiSampleTimeInMs << ",uiPts=" << uiPts << ",orgSampleTimeInMs=" << orgSampleTimeInMs
			<< ",interval=" << interval << ",qsize0=" << qsize0 << ",qsize1=" << qsize1;
		printLogChar(ss.str().c_str());
	}

	m_lastAudioPts = orgSampleTimeInMs;

	if (result > 0) {
		return true;
	}
	return false;

}


bool TcpClient::Close() {
	if (sclient_ != INVALID_SOCKET) {
		closesocket(sclient_);		
		sclient_ = INVALID_SOCKET;	

		
	}

	if (m_init)
		WSACleanup();	

	return true;
}

TcpClient::TcpClient(const char* ip, u_short port) {
	this->ip_ = ip;
	this->port_ = port;
	sclient_ = INVALID_SOCKET;
}
TcpClient::TcpClient() {
	sclient_ = INVALID_SOCKET;
}

TcpClient::~TcpClient() {
	printLogChar("TcpClient exit begin");
	Close();
	printLogChar("TcpClient exit end");
}

