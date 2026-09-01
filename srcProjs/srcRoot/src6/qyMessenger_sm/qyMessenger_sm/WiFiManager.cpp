#include "stdafx.h"
#include "WiFiManager.h"
#include <iostream>
#include <Wincrypt.h>
#include <sstream>

//#include "myLog_open.h"



using namespace std;

void printLogChar_open(const char* log) {

}

BOOL Utf8ToUnicode(std::wstring& str, const char* pUTF8Text)
{
	if (NULL == pUTF8Text)
	{
		return FALSE;
	}

	int  unicodeLen = ::MultiByteToWideChar(CP_UTF8, 0, pUTF8Text, -1, NULL, 0);

	wchar_t*  pUnicode = NULL;

	try
	{
		pUnicode = new  wchar_t[unicodeLen + 1];
	}
	catch (...)
	{
		return FALSE;
	}

	MultiByteToWideChar(CP_UTF8, 0, pUTF8Text, -1, static_cast<LPWSTR>(pUnicode), unicodeLen);

	str = pUnicode;

	delete[]pUnicode;
	return TRUE;
}

CDefer::CDefer(const std::function<void()>& constructor, const std::function<void()>& destructor)
	: _constructor(constructor)
	, _destructor(destructor)
{
	if (_constructor)
	{
		_constructor();
	}
}
CDefer::~CDefer()
{
	if (_destructor)
	{
		_destructor();
	}
}

bool WiFiManager::ScanWiFi()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (!InitialHandle())
	{
		//std::cout << "initial wlan handle failed" << std::endl;
		printLogChar_open("initial wlan handle failed");
		return false;
	}

	DWORD dwResult = 0;
	PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
	PWLAN_INTERFACE_INFO pIfInfo = NULL;
	WCHAR GuidString[39] = { 0 };

	PWLAN_AVAILABLE_NETWORK_LIST pBssList = NULL;
	PWLAN_AVAILABLE_NETWORK pBssEntry = NULL;


	CDefer pIfRaii([]() {}, [&pBssList, &pIfList]()
	{
		if (pBssList != NULL)
		{
			WlanFreeMemory(pBssList);
			pBssList = NULL;
		}

		if (pIfList != NULL)
		{
			WlanFreeMemory(pIfList);
			pIfList = NULL;
		}
	});

	unsigned int i = 0;


	dwResult = WlanEnumInterfaces(m_wlanHandle, NULL, &pIfList);
	if (dwResult != ERROR_SUCCESS)
	{
		return false;
	}

	for (i = 0; i < (int)pIfList->dwNumberOfItems; i++) 
	{
		pIfInfo = (WLAN_INTERFACE_INFO*)&pIfList->InterfaceInfo[i];

		dwResult = StringFromGUID2(pIfInfo->InterfaceGuid, (LPOLESTR)&GuidString,
			sizeof(GuidString) / sizeof(*GuidString));


		dwResult = WlanScan(m_wlanHandle, (const GUID*)(&pIfInfo->InterfaceGuid), NULL, NULL, NULL);
		if (dwResult != ERROR_SUCCESS)
		{
			return false;
		}
	}
	
	return false;
}
#include <algorithm>
bool compare_no_case(const std::wstring& lhs, const std::wstring& rhs) {

	std::wstring lhs_lower = lhs;
	std::wstring rhs_lower = rhs;
	std::transform(lhs_lower.begin(), lhs_lower.end(), lhs_lower.begin(), ::towlower);
	std::transform(rhs_lower.begin(), rhs_lower.end(), rhs_lower.begin(), ::towlower);
	return lhs_lower == rhs_lower;

}

bool WiFiManager::GetWiFiList(WiFiInfoList& wifilist)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (!InitialHandle())
	{
		//std::cout << "initial wlan handle failed" << std::endl;
		printLogChar_open("initial wlan handle failed");
		return false;
	}

	DWORD dwResult = 0;
	PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
	PWLAN_INTERFACE_INFO pIfInfo = NULL;
	WCHAR GuidString[39] = { 0 };

	PWLAN_AVAILABLE_NETWORK_LIST pBssList = NULL;
	PWLAN_AVAILABLE_NETWORK pBssEntry = NULL;


	CDefer pIfRaii([]() {}, [&pBssList, &pIfList]()
	{
		if (pBssList != NULL)
		{
			WlanFreeMemory(pBssList);
			pBssList = NULL;
		}

		if (pIfList != NULL)
		{
			WlanFreeMemory(pIfList);
			pIfList = NULL;
		}
	});

	unsigned int i, j;

	dwResult = WlanEnumInterfaces(m_wlanHandle, NULL, &pIfList);
	if (dwResult != ERROR_SUCCESS)
	{
		return false;
	}

	for (i = 0; i < (int)pIfList->dwNumberOfItems; i++)
	{
		pIfInfo = (WLAN_INTERFACE_INFO*)&pIfList->InterfaceInfo[i];
		dwResult = WlanGetAvailableNetworkList(m_wlanHandle,
			&pIfInfo->InterfaceGuid,
			2,
			NULL,
			&pBssList);

		if (dwResult != ERROR_SUCCESS)
		{
			//std::cout << "WlanGetAvailableNetworkList failed with error:" << dwResult;

			std::stringstream ss;
			ss << "WlanGetAvailableNetworkList failed with error:" << dwResult;
			printLogChar_open(ss.str().c_str());
			return false;
		}

		for (j = 0; j < pBssList->dwNumberOfItems; j++)
		{
			pBssEntry = (WLAN_AVAILABLE_NETWORK*)&pBssList->Network[j];

			WiFiInfo info;


			char ssid[36];
			memcpy(ssid, pBssEntry->dot11Ssid.ucSSID, pBssEntry->dot11Ssid.uSSIDLength);
			ssid[pBssEntry->dot11Ssid.uSSIDLength] = 0;
			Utf8ToUnicode(info.cstrSSID, ssid);


			info.nSignalValue = pBssEntry->wlanSignalQuality;


			info.bLinked = pBssEntry->dwFlags & WLAN_AVAILABLE_NETWORK_CONNECTED;


			bool bRepeat = false;
			if (wifilist.size() > 0)
			{
				for (size_t i = 0; i < wifilist.size(); i++)
				{
					//if (wifilist[i].cstrSSID.CompareNoCase(info.cstrSSID) == 0)
					if(compare_no_case(wifilist[i].cstrSSID, info.cstrSSID))
					{
						wifilist[i].bLinked |= info.bLinked;
						bRepeat = true;
					}
				}
			}

			if (bRepeat)
			{
				continue;
			}

			DWORD dwFlags = WLAN_PROFILE_GET_PLAINTEXT_KEY | WLAN_PROFILE_USER;
			DWORD dwGrantedAccess = WLAN_READ_ACCESS;
			DWORD dwResult = WlanGetProfile(m_wlanHandle,
				&pIfInfo->InterfaceGuid,
				info.cstrSSID.c_str(),
				NULL,
				&info.pProfileXml,
				&dwFlags,
				&dwGrantedAccess);
			if (dwResult == ERROR_SUCCESS)
			{

				std::wstring cstrXml = info.pProfileXml;
				int nFirstIndex = cstrXml.find(_T("<keyMaterial>"));
				if (nFirstIndex != std::wstring::npos)
				{
					int nLastIndex = cstrXml.find(_T("</keyMaterial>"));
					std::wstring strKey = std::wstring(cstrXml.c_str() + nFirstIndex + 13, nLastIndex - (nFirstIndex + 13));

			
					BYTE byteKey[1024] = { 0 };
					DWORD dwLength = 1024;
					DATA_BLOB dataOut, dataVerify;

					BOOL bRes = CryptStringToBinary(strKey.c_str(), strKey.length(), CRYPT_STRING_HEX, byteKey, &dwLength, 0, 0);

					if (bRes)
					{
						dataOut.cbData = dwLength;
						dataOut.pbData = (BYTE*)byteKey;

						if (CryptUnprotectData(&dataOut, NULL, NULL, NULL, NULL, 0, &dataVerify))
						{
							TCHAR str[MAX_PATH] = { 0 };
							wsprintf(str, L"%hs", dataVerify.pbData);
							strKey = str;
						}
					}

					info.cstrPassword = strKey;
				}
			}
			else if (dwResult == ERROR_NOT_FOUND)
			{
				
			}
			

			wifilist.emplace_back(info);
		}
	}

	return true;
}

#include <fstream>

bool ExecuteCommand(const std::wstring& command) {
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si);
	TCHAR szPath[MAX_PATH] = _T("C:\\Windows\\System32\\netsh.exe wlan add profile filename=\"d:\\qycx\\wifi.xml\"");
	// 创建一个隐藏的进程
	if (!CreateProcess(NULL, const_cast<LPWSTR>(command.c_str()) /*(LPWSTR)command.c_str()*/, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
		//std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
		std::stringstream ss;
		ss << "CreateProcess failed (" << GetLastError() << ").";
		printLogChar_open(ss.str().c_str());
		return false;
	}

	// 等待进程结束
	WaitForSingleObject(pi.hProcess, INFINITE);

	// 关闭进程和线程句柄
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return true;
}

bool WiFiManager::ConnectWiFi(std::wstring cstrSetSSID, std::wstring targetKey, bool flag)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (!InitialHandle())
	{
		//std::cout << "initial wlan handle failed" << std::endl;
		printLogChar_open("initial wlan handle failed");
		return false;
	}

	DWORD dwResult = 0;
	PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
	PWLAN_INTERFACE_INFO pIfInfo = NULL;
	WCHAR GuidString[39] = { 0 };

	PWLAN_AVAILABLE_NETWORK_LIST pBssList = NULL;
	PWLAN_AVAILABLE_NETWORK pBssEntry = NULL;


	CDefer pIfRaii([]() {}, [&pBssList, &pIfList]()
	{
		if (pBssList != NULL)
		{
			WlanFreeMemory(pBssList);
			pBssList = NULL;
		}

		if (pIfList != NULL)
		{
			WlanFreeMemory(pIfList);
			pIfList = NULL;
		}
	});

	unsigned int i, j;

	dwResult = WlanEnumInterfaces(m_wlanHandle, NULL, &pIfList);
	if (dwResult != ERROR_SUCCESS)
	{
		return false;
	}

	for (i = 0; i < (int)pIfList->dwNumberOfItems; i++)
	{
		pIfInfo = (WLAN_INTERFACE_INFO*)&pIfList->InterfaceInfo[i];
		dwResult = WlanGetAvailableNetworkList(m_wlanHandle,
			&pIfInfo->InterfaceGuid,
			0,
			NULL,
			&pBssList);

		if (dwResult != ERROR_SUCCESS)
		{
			//std::cout << "WlanGetAvailableNetworkList failed with error:" << dwResult;
			std::stringstream ss;
			ss << "WlanGetAvailableNetworkList failed with error:" << dwResult;
			printLogChar_open(ss.str().c_str());
			return false;
		}

		for (j = 0; j < pBssList->dwNumberOfItems; j++)
		{
			pBssEntry = (WLAN_AVAILABLE_NETWORK*)&pBssList->Network[j];

			WiFiInfo info;

			char ssid[36];
			memcpy(ssid, pBssEntry->dot11Ssid.ucSSID, pBssEntry->dot11Ssid.uSSIDLength);
			ssid[pBssEntry->dot11Ssid.uSSIDLength] = 0;
			Utf8ToUnicode(info.cstrSSID, ssid);
			
			//if (cstrSetSSID.CompareNoCase(info.cstrSSID) == 0)
			if(compare_no_case(cstrSetSSID, info.cstrSSID))
			{
				DWORD dwFlags = WLAN_PROFILE_GET_PLAINTEXT_KEY | WLAN_PROFILE_USER;
				DWORD dwGrantedAccess = WLAN_READ_ACCESS;
				DWORD dwResult = WlanGetProfile(m_wlanHandle,
					&pIfInfo->InterfaceGuid,
					info.cstrSSID.c_str(),
					NULL,
					&info.pProfileXml,
					&dwFlags,
					&dwGrantedAccess);
				ERROR_ACCESS_DENIED;
				if (dwResult == ERROR_SUCCESS)
				{
					std::wstring cstrXml = info.pProfileXml;
					int nFirstIndex = cstrXml.find(_T("<keyMaterial>"));
					if (nFirstIndex != std::wstring::npos)
					{
						int nLastIndex = cstrXml.find(_T("</keyMaterial>"));
						std::wstring strKey = std::wstring(cstrXml.c_str() + nFirstIndex + 13, nLastIndex - (nFirstIndex + 13));

						BYTE byteKey[1024] = { 0 };
						DWORD dwLength = 1024;
						DATA_BLOB dataOut, dataVerify;

						BOOL bRes = CryptStringToBinary(strKey.c_str(), strKey.length(), CRYPT_STRING_HEX, byteKey, &dwLength, 0, 0);

						if (bRes)
						{
							dataOut.cbData = dwLength;
							dataOut.pbData = (BYTE*)byteKey;

							if (CryptUnprotectData(&dataOut, NULL, NULL, NULL, NULL, 0, &dataVerify))
							{
								TCHAR str[MAX_PATH] = { 0 };
								wsprintf(str, L"%hs", dataVerify.pbData);
								strKey = str;
							}
						}

						info.cstrPassword = strKey;
					}

					//if (info.cstrPassword.Compare(targetKey) != 0)
					if (!compare_no_case(info.cstrPassword, targetKey))
					{
						SetProfile(cstrSetSSID, targetKey, pBssEntry, pIfInfo->InterfaceGuid);
					}
				}
				else if (ERROR_NOT_FOUND == dwResult) {
					pBssEntry->dot11BssType = dot11_BSS_type_infrastructure;
					pBssEntry->dot11DefaultAuthAlgorithm = DOT11_AUTH_ALGO_RSNA_PSK;
					pBssEntry->dot11DefaultCipherAlgorithm = DOT11_CIPHER_ALGO_CCMP;
					
					std::wstring szProfileXML(_T(""));
					if (BuildProfile(cstrSetSSID, targetKey, pBssEntry, szProfileXML)) {
						std::wofstream file("d:\\qycx\\wifi.xml", std::ios::out | std::ios::trunc);
						if (file.is_open())	{
							//std::string wstr  = szProfileXML.GetBuffer();
							std::wstring str(szProfileXML);
							file << str;

							file.close();

						

							//std::string command = "netsh wlan add profile filename=\"d:\\qycx\\wifi.xml\"";
							//std::string command = "C:\\Windows\\System32\\netsh.exe wlan add profile filename=\"d:\\qycx\\wifi.xml\"";
							//std::string command = "netsh.exe wlan add profile filename=\"d:\\qycx\\wifi.xml\"";
							TCHAR szPath[MAX_PATH] = _T("C:\\Windows\\System32\\netsh.exe wlan add profile filename=\"d:\\qycx\\wifi.xml\"");

							if (!ExecuteCommand(szPath)) {
								printLogChar_open("ExecuteCommand failed");
							}

							/*
							int result = system(command.c_str());

							//int result = (int)ShellExecute(NULL, L"", L"netsh", L"wlan add profile filename=\"d:\\qycx\\wifi.xml\"", NULL, SW_SHOWNA);

							if (result < 0) {
								//std::cerr << "Error executing command." << std::endl;
								printLogChar_open("Error executing command.");
							}
							else if (result == 0) {
								//std::cout << "Command executed successfully." << std::endl;
								printLogChar_open("Command executed successfully.");
							}
							else {
								//std::cout << "Command exited with non-zero status " << result << std::endl;
								std::stringstream ss;
								ss << "Command exited with non-zero status " << result;
								printLogChar_open(ss.str().c_str());
							}
							*/
						}						
						
					}
					
				}

				
				

				WLAN_AVAILABLE_NETWORK wlanAN = pBssList->Network[j];


				if (std::wcslen(wlanAN.strProfileName) <= 0) {
					wcscpy_s(wlanAN.strProfileName, WLAN_MAX_NAME_LENGTH, cstrSetSSID.c_str());
					//cstrSetSSID.ReleaseBuffer();
				}

				WLAN_CONNECTION_PARAMETERS wlanConnPara;
				wlanConnPara.wlanConnectionMode = wlan_connection_mode_profile; //YES,WE CONNECT AP VIA THE PROFILE
				wlanConnPara.strProfile = wlanAN.strProfileName;                // set the profile name
				wlanConnPara.pDot11Ssid = NULL;                                 // SET SSID NULL
				wlanConnPara.dot11BssType = dot11_BSS_type_infrastructure;      //dot11_BSS_type_any,I do not need it this time.       
				wlanConnPara.pDesiredBssidList = NULL;                          // the desired BSSID list is empty
				wlanConnPara.dwFlags = WLAN_CONNECTION_HIDDEN_NETWORK;          //it works on my WIN78

				if (flag)
					dwResult = WlanConnect(m_wlanHandle, &pIfInfo->InterfaceGuid, &wlanConnPara, NULL);
				else
					dwResult = WlanDisconnect(m_wlanHandle, &pIfInfo->InterfaceGuid, NULL);

				if (dwResult == ERROR_SUCCESS)
				{
				}
			}
		}
	}

	return true;
}

bool WiFiManager::RigisterConnectNotification(CONNECT_NOTIFICATION_CALLBACK funcCallback)
{
	if (funcCallback) {
		m_funcConnectNotification = funcCallback;
	}
	return false;
}

void OnNotificationCallback(PWLAN_NOTIFICATION_DATA data, PVOID context)
{
	if (data != NULL && data->NotificationSource == WLAN_NOTIFICATION_SOURCE_ACM)
	{
		switch (data->NotificationCode)
		{
		case wlan_notification_acm_scan_complete:
		case wlan_notification_acm_scan_fail:
			WiFiManager::GetInstance().SetConnectResult(NULL, data->NotificationCode);
			break;
		case wlan_notification_acm_connection_start:
		case wlan_notification_acm_connection_complete:
		case wlan_notification_acm_connection_attempt_fail:
		case wlan_notification_acm_disconnecting:
		case wlan_notification_acm_disconnected:
		{
			PWLAN_CONNECTION_NOTIFICATION_DATA connection = (PWLAN_CONNECTION_NOTIFICATION_DATA)data->pData;
			WiFiManager::GetInstance().SetConnectResult(connection, data->NotificationCode);
		}
			break;
		default:
			break;
		}
	}
}


bool WiFiManager::InitialHandle()
{
	DWORD dwResult = 0;
	DWORD dwCurVersion = 0;
	DWORD dwMaxClient = 2;
	if (m_wlanHandle == NULL)
	{
		if ((dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &m_wlanHandle)) != ERROR_SUCCESS)
		{
			//std::cout << "wlanOpenHandle failed with error: " << dwResult << std::endl;
			std::stringstream ss;
			ss << "wlanOpenHandle failed with error: " << dwResult;
			printLogChar_open(ss.str().c_str());
			m_wlanHandle = NULL;
			return false;
		}

		if ((dwResult = WlanRegisterNotification(m_wlanHandle, WLAN_NOTIFICATION_SOURCE_ALL, TRUE, WLAN_NOTIFICATION_CALLBACK(OnNotificationCallback), NULL, nullptr, nullptr)) != ERROR_SUCCESS)
		{
			//std::cout << "wlanRegisterNotification failed with error: " << dwResult << std::endl;
			std::stringstream ss;
			ss << "wlanRegisterNotification failed with error: " << dwResult;
			printLogChar_open(ss.str().c_str());
			m_wlanHandle = NULL;
			return false;
		}
	}
	return true;
}

bool WiFiManager::BuildProfile(std::wstring& curSSID, std::wstring targetKey, PWLAN_AVAILABLE_NETWORK pNet, std::wstring& szProfileXML)
{
	//CStringW szProfileXML("");  
	//wchar_t* wscProfileXML = NULL;
	std::wstring szTemp(_T(""));

	szProfileXML += _T("<?xml version=\"1.0\"?><WLANProfile xmlns=\"http://www.microsoft.com/networking/WLAN/profile/v1\"><name>");
	szTemp = curSSID;
	szProfileXML += szTemp;
	/*SSIDConfig*/
	szProfileXML += _T("</name><SSIDConfig><SSID><name>");
	//TCHAR ssid[36];
	//memcpy(ssid, pNet->dot11Ssid.ucSSID, pNet->dot11Ssid.uSSIDLength);
	//ssid[pNet->dot11Ssid.uSSIDLength] = 0;
	//szProfileXML += ssid;
	szProfileXML += curSSID;
	szProfileXML += _T("</name></SSID></SSIDConfig>");
	/*connectionType*/
	szProfileXML += _T("<connectionType>");
	switch (pNet->dot11BssType)
	{
	case dot11_BSS_type_infrastructure:
		szProfileXML += _T("ESS");
		break;
	case dot11_BSS_type_independent:
		szProfileXML += _T("IBSS");
		break;
	case dot11_BSS_type_any:
		szProfileXML += _T("Any");
		break;
	default:
		//wprintf(L"Unknown BSS type");
		printLogChar_open("Unknown BSS type");
		return false;
	}

	szProfileXML += _T("</connectionType><connectionMode>auto</connectionMode><MSM><security><authEncryption><authentication>");
	//manual
	switch (pNet->dot11DefaultAuthAlgorithm)
	{
	case DOT11_AUTH_ALGO_80211_OPEN:
		szProfileXML += _T("open");
		//wprintf(L"Open 802.11 authentication\n");
		printLogChar_open("Open 802.11 authentication");
		break;
	case DOT11_AUTH_ALGO_80211_SHARED_KEY:
		szProfileXML += _T("shared");
		//wprintf(L"Shared 802.11 authentication");
		printLogChar_open("Shared 802.11 authentication");
		break;
	case DOT11_AUTH_ALGO_WPA:
		szProfileXML += _T("WPA");
		//wprintf(L"WPA-Enterprise 802.11 authentication\n");
		printLogChar_open("WPA-Enterprise 802.11 authentication");
		break;
	case DOT11_AUTH_ALGO_WPA_PSK:
		szProfileXML += _T("WPAPSK");
		//wprintf(L"WPA-Personal 802.11 authentication\n");
		printLogChar_open("WPA-Personal 802.11 authentication");
		break;
	case DOT11_AUTH_ALGO_WPA_NONE:
		szProfileXML += _T("none");
		//wprintf(L"WPA-NONE,not exist in MSDN\n");
		printLogChar_open("WPA-NONE,not exist in MSDN");
		break;
	case DOT11_AUTH_ALGO_RSNA:
		szProfileXML += _T("WPA2");
		//wprintf(L"WPA2-Enterprise 802.11 authentication\n");
		printLogChar_open("WPA2-Enterprise 802.11 authentication");
		break;
	case DOT11_AUTH_ALGO_RSNA_PSK:
		szProfileXML += _T("WPA2PSK");
		//wprintf(L"WPA2-Personal 802.11 authentication\n");
		printLogChar_open("WPA2-Personal 802.11 authentication");
		break;
	default:
		//wprintf(L"Unknown authentication");
		printLogChar_open("Unknown authentication");
		return false;
	}
	szProfileXML += _T("</authentication><encryption>");
	switch (pNet->dot11DefaultCipherAlgorithm)
	{
	case DOT11_CIPHER_ALGO_NONE:
		szProfileXML += _T("none");
		break;
	case DOT11_CIPHER_ALGO_WEP40:
		szProfileXML += _T("WEP");
		break;
	case DOT11_CIPHER_ALGO_TKIP:
		szProfileXML += _T("TKIP");
		break;
	case DOT11_CIPHER_ALGO_CCMP:
		szProfileXML += _T("AES");
		break;
	case DOT11_CIPHER_ALGO_WEP104:
		szProfileXML += _T("WEP");
		break;
	case DOT11_CIPHER_ALGO_WEP:
		szProfileXML += _T("WEP");
		break;
	case DOT11_CIPHER_ALGO_WPA_USE_GROUP:
		//wprintf(L"USE-GROUP not exist in MSDN");
		printLogChar_open("USE-GROUP not exist in MSDN");
	default:
		//wprintf(L"Unknown encryption");
		printLogChar_open("Unknown encryption");
		return false;
	}
	szProfileXML += _T("</encryption></authEncryption><sharedKey><keyType>passPhrase</keyType><protected>false</protected><keyMaterial>");

	szProfileXML += targetKey;
	szProfileXML += _T("</keyMaterial></sharedKey></security></MSM></WLANProfile>");

	return true;
}


bool WiFiManager::SetProfile(std::wstring& curSSID, std::wstring targetKey, PWLAN_AVAILABLE_NETWORK pNet, GUID interfaceGuid)
{
	std::wstring szProfileXML(_T("")); 
	//wchar_t* wscProfileXML = NULL;
	std::wstring szTemp(_T(""));

	szProfileXML += _T("<?xml version=\"1.0\"?><WLANProfile xmlns=\"http://www.microsoft.com/networking/WLAN/profile/v1\"><name>");
	szTemp = curSSID;
	szProfileXML += szTemp;
	/*SSIDConfig*/
	szProfileXML += _T("</name><SSIDConfig><SSID><name>");
	/*
	TCHAR ssid[36];
	memcpy(ssid, pNet->dot11Ssid.ucSSID, pNet->dot11Ssid.uSSIDLength);
	ssid[pNet->dot11Ssid.uSSIDLength] = 0;
	szProfileXML += ssid;*/
	szProfileXML += curSSID;
	szProfileXML += _T("</name></SSID></SSIDConfig>");
	/*connectionType*/
	szProfileXML += _T("<connectionType>");
	switch (pNet->dot11BssType)
	{
	case dot11_BSS_type_infrastructure:
		szProfileXML += _T("ESS");
		break;
	case dot11_BSS_type_independent:
		szProfileXML += _T("IBSS");
		break;
	case dot11_BSS_type_any:
		szProfileXML += _T("Any");
		break;
	default:
		//wprintf(L"Unknown BSS type");
		printLogChar_open("Unknown BSS type");
		return false;
	}

	szProfileXML += _T("</connectionType><connectionMode>auto</connectionMode><MSM><security><authEncryption><authentication>");
	switch (pNet->dot11DefaultAuthAlgorithm)
	{
	case DOT11_AUTH_ALGO_80211_OPEN:
		szProfileXML += _T("open");
		//wprintf(L"Open 802.11 authentication\n");
		printLogChar_open("Open 802.11 authentication");
		break;
	case DOT11_AUTH_ALGO_80211_SHARED_KEY:
		szProfileXML += _T("shared");
		//wprintf(L"Shared 802.11 authentication");
		printLogChar_open("Shared 802.11 authentication");
		break;
	case DOT11_AUTH_ALGO_WPA:
		szProfileXML += _T("WPA");
		//wprintf(L"WPA-Enterprise 802.11 authentication\n");
		printLogChar_open("WPA-Enterprise 802.11 authentication");
		break;
	case DOT11_AUTH_ALGO_WPA_PSK:
		szProfileXML += _T("WPAPSK");
		//wprintf(L"WPA-Personal 802.11 authentication\n");
		printLogChar_open("WPA-Personal 802.11 authentication");
		break;
	case DOT11_AUTH_ALGO_WPA_NONE:
		szProfileXML += _T("none");
		//wprintf(L"WPA-NONE,not exist in MSDN\n");
		printLogChar_open("WPA-NONE,not exist in MSDN");
		break;
	case DOT11_AUTH_ALGO_RSNA:
		szProfileXML += _T("WPA2");
		//wprintf(L"WPA2-Enterprise 802.11 authentication\n");
		printLogChar_open("WPA2-Enterprise 802.11 authentication");
		break;
	case DOT11_AUTH_ALGO_RSNA_PSK:
		szProfileXML += _T("WPA2PSK");
		//wprintf(L"WPA2-Personal 802.11 authentication\n");
		printLogChar_open("WPA2-Personal 802.11 authentication");
		break;
	default:
		//wprintf(L"Unknown authentication");
		printLogChar_open("Unknown authentication");
		return false;
	}
	szProfileXML += _T("</authentication><encryption>");
	switch (pNet->dot11DefaultCipherAlgorithm)
	{
	case DOT11_CIPHER_ALGO_NONE:
		szProfileXML += _T("none");
		break;
	case DOT11_CIPHER_ALGO_WEP40:
		szProfileXML += _T("WEP");
		break;
	case DOT11_CIPHER_ALGO_TKIP:
		szProfileXML += _T("TKIP");
		break;
	case DOT11_CIPHER_ALGO_CCMP:
		szProfileXML += _T("AES");
		break;
	case DOT11_CIPHER_ALGO_WEP104:
		szProfileXML += _T("WEP");
		break;
	case DOT11_CIPHER_ALGO_WEP:
		szProfileXML += _T("WEP");
		break;
	case DOT11_CIPHER_ALGO_WPA_USE_GROUP:
		//wprintf(L"USE-GROUP not exist in MSDN");
		printLogChar_open("USE-GROUP not exist in MSDN");
	default:
		//wprintf(L"Unknown encryption");
		printLogChar_open("Unknown encryption");
		return false;
	}
	szProfileXML += _T("</encryption></authEncryption><sharedKey><keyType>passPhrase</keyType><protected>false</protected><keyMaterial>");

	szProfileXML += targetKey;

	szProfileXML += _T("</keyMaterial></sharedKey></security></MSM></WLANProfile>");

	/*
	wscProfileXML = szProfileXML.c_str();
	if (NULL == wscProfileXML)
	{
		wprintf(L"Change wscProfileXML fail\n");
		return false;
	}
	*/

	DWORD dwReasonCode = 0;
	DWORD dwResult = WlanSetProfile(m_wlanHandle, &interfaceGuid,
		0x00, szProfileXML.c_str(), NULL, TRUE, NULL, &dwReasonCode);
	if (ERROR_SUCCESS != dwResult)
	{
		switch (dwResult)
		{
		case ERROR_INVALID_PARAMETER:
			//OutputDebugString(L"Para is NULL\n");
			printLogChar_open("Para is NULL");
			break;
		case ERROR_INVALID_HANDLE:
			//OutputDebugString(L"Failed to INVALID HANDLE  \n");
			printLogChar_open("Failed to INVALID HANDLE");
			break;
		case ERROR_NOT_ENOUGH_MEMORY:
			//OutputDebugString(L"Failed to allocate memory \n");
			printLogChar_open("Failed to allocate memory");
			break;
		case ERROR_BAD_PROFILE:
			//OutputDebugString(L"The profile specified by strProfileXml is not valid \n");
			printLogChar_open("The profile specified by strProfileXml is not valid");
			break;
		case ERROR_ALREADY_EXISTS:
			//OutputDebugString(L"strProfileXml specifies a network that already exists \n");
			printLogChar_open("strProfileXml specifies a network that already exists");
			break;
		case ERROR_ACCESS_DENIED:
			//OutputDebugString(L"The caller does not set the profile. \n");
			printLogChar_open("The caller does not set the profile.");
			break;
		default:
			dwResult = GetLastError();
			//TRACE("WlanSetProfile Fail： %d\n", dwResult);
			std::stringstream ss;
			ss << "WlanSetProfile Fail： " << dwResult;
			printLogChar_open(ss.str().c_str());
			break;
		}
		if (dwResult != 183)
		{
			return false;
		}
	}

	return true;
}

bool WiFiManager::SetConnectResult(PWLAN_CONNECTION_NOTIFICATION_DATA pData, DWORD dwConnectCode)
{
	if (m_funcConnectNotification)
	{
		m_funcConnectNotification(pData, dwConnectCode);
	}
	return false;
}
