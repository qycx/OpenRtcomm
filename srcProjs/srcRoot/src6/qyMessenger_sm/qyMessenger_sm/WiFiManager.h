#ifndef _WIFIMANAGER_H_
#define _WIFIMANAGER_H_
#include "stdafx.h"
#include <locale>
#include <wlanapi.h>
#include <vector>
#include <mutex>
#include <condition_variable>

#include  <functional>

using namespace std;
#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "Crypt32.lib")
struct WiFiInfo
{
	std::wstring cstrSSID;
	std::wstring cstrPassword;
	bool bLinked;
	int nSignalValue;
	LPWSTR pProfileXml;
	WiFiInfo(){
		cstrSSID = _T("");
		cstrPassword = _T("");
		bLinked = false;
		nSignalValue = false;
		pProfileXml = NULL;
	}
};

typedef vector<WiFiInfo> WiFiInfoList;

class CDefer
{
public:
	CDefer(const std::function<void()>& constructor, const std::function<void()>& destructor);

	~CDefer();

private:
	std::function<void()> _constructor;
	std::function<void()> _destructor;
};

typedef VOID(WINAPI *CONNECT_NOTIFICATION_CALLBACK) (PWLAN_CONNECTION_NOTIFICATION_DATA, DWORD);

class WiFiManager
{
	friend void OnNotificationCallback(PWLAN_NOTIFICATION_DATA data, PVOID context);
public:
	static WiFiManager& GetInstance()
	{
		static WiFiManager instance;
		return instance;
	}

	bool ScanWiFi(); 
	bool GetWiFiList(WiFiInfoList& wifilist); 
	bool ConnectWiFi(std::wstring curSSID, std::wstring targetKey, bool flag = true);
	bool RigisterConnectNotification(CONNECT_NOTIFICATION_CALLBACK funcCallback);
private:
	WiFiManager()
		: m_wlanHandle(NULL),
		m_funcConnectNotification(NULL)
	{
	}

	bool InitialHandle();
	bool SetProfile(std::wstring& curSSID, std::wstring targetKey, PWLAN_AVAILABLE_NETWORK pNet, GUID interfaceGuid);
	bool SetConnectResult(PWLAN_CONNECTION_NOTIFICATION_DATA pData, DWORD dwConnectCode);

	bool BuildProfile(std::wstring& curSSID, std::wstring targetKey, PWLAN_AVAILABLE_NETWORK pNet, std::wstring& szProfileXML);
private:
	HANDLE m_wlanHandle;
	std::mutex m_mutex;
	CONNECT_NOTIFICATION_CALLBACK m_funcConnectNotification;

};

#endif // !WIFIMANAGER_H
