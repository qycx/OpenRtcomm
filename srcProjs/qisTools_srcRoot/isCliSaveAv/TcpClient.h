#pragma once

#include <WinSock2.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")
#include <functional>
#include <string>
#include <map>
using namespace std;

class TcpClient;
typedef function<void(char*, int)> RecvCallBack;

enum Cmd_Def {
	RecordStart = 1,
	VideoStart = 2,
	AudioStart = 3,
	VideoStop = 4,
	AudioStop = 5,
	RecordStop = 6,
	VideoData = 7,
	AudioData = 8,

};

enum Video_Type {
	Video_Type_Unknow = 0,
	Video_Type_H264 = 1,
	Video_Type_H265 = 2,
};

class TcpClient
{
private:
	SOCKET sclient_ = INVALID_SOCKET;
	const char* ip_ = NULL;
	u_short port_ = 0;

	bool isConnected = false;

public:

	int Initialize();
	bool ConnectStatus();
	int  ReConntct();
	bool SendRecordStart(const char* name);
	bool SendRecordStartNew(const char* name, bool isRecord, bool isLive, __int64 meetingId, unsigned  __int64 gid, const char* liveUrl);
	bool SendRecordStop(const char* name);

	bool SendVideoStart(const char* name, const char* videoName);
	bool SendAudioStart(const char* name, const char* audioName);
	bool SendAudioStop(const char* name, const char* audioName);

	void SetVideoType(const char* videoName);

	bool SendVideoData(const char* name, const char* videoName, unsigned char* data, int dataLen, unsigned  int	uiSampleTimeInMs, 
		unsigned  int	uiPts, unsigned  int orgSampleTimeInMs, int qsize0, int qsize1, bool& isReconnect);
	bool SendAudioData(const char* name, const char* audioName, unsigned char* data, int dataLen, unsigned  int	uiSampleTimeInMs, unsigned  int	uiPts, unsigned  int orgSampleTimeInMs, int qsize0, int qsize1);

	void Start();
	bool Close();
	bool CloseSocket();
	int SendBuf(const char*, int);
	int SendBuf(const char*, int len, bool& isReconnect);
	void SetRecvFunc(RecvCallBack);

	unsigned  int m_lastVideoPts = 0;
	unsigned  int m_lastAudioPts = 0;

	DWORD lastConnectTime = 0;

	std::string m_name;
	bool m_isRecord = false;
	bool m_isLive = false;
	__int64 m_meetingId = 0;
	unsigned  __int64 m_gid = 0;
	std::string m_liveUrl;

	std::string m_videoName;

	Video_Type  m_videoType = Video_Type_Unknow;

	std::map<std::string, int> m_audioName;


	std::string m_vpsSps;
	unsigned  int	m_uiSampleTimeInMs;
	unsigned  int	m_uiPts;
	unsigned  int   m_orgSampleTimeInMs;

	bool m_init = false;

	TcpClient(const char*, u_short);
	TcpClient();
	~TcpClient();

};


