#include "NetworkMonitor.h"

#define _WIN32_WINNT 0x0501

#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>

#include <windows.h>
#include <iphlpapi.h>
#include <netlistmgr.h>
#include <comdef.h>

#include <iostream>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ole32.lib")

#include <locale>
#include <codecvt>
#include <string>



#include <locale>
#include <codecvt>
#include <string>

#include <vector>

//#include <winsock2.h>
//#include <iphlpapi.h>
//#include <ws2tcpip.h>
//#include <stdio.h>
//
//#pragma comment(lib, "iphlpapi.lib")
//#pragma comment(lib, "ws2_32.lib")

std::string PWCHARToANSI(PWCHAR wideStr) {
    if (wideStr == nullptr) return "";

    int bufferSize = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, nullptr, 0, nullptr, nullptr);
    if (bufferSize == 0) return "";

    std::string ansiStr(bufferSize, 0);
    WideCharToMultiByte(CP_ACP, 0, wideStr, -1, &ansiStr[0], bufferSize, nullptr, nullptr);

    // ÒÆ³ýÄ©Î²µÄnull×Ö·û
    if (!ansiStr.empty() && ansiStr.back() == '\0') {
        ansiStr.pop_back();
    }

    return ansiStr;
}

NetworkMonitor::NetworkMonitor() {
    CoInitialize(NULL);
    CoCreateInstance(CLSID_NetworkListManager, NULL, CLSCTX_ALL,
        IID_INetworkListManager, (LPVOID*)&pNLM);
}

NetworkMonitor::~NetworkMonitor() {
    if (pNLM) pNLM->Release();
    CoUninitialize();
}

int NetworkMonitor::CheckAdapterStatus() {

    ULONG bufferSize = 0;
    GetAdaptersAddresses(AF_UNSPEC, 0, NULL, NULL, &bufferSize);

    int count = 0;

    std::vector<BYTE> buffer(bufferSize);
    PIP_ADAPTER_ADDRESSES pAdapterAddresses = reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.data());

    if (GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAdapterAddresses, &bufferSize) == ERROR_SUCCESS) {
        for (PIP_ADAPTER_ADDRESSES pAdapter = pAdapterAddresses; pAdapter != NULL; pAdapter = pAdapter->Next) {
            if (pAdapter->OperStatus == IfOperStatusUp) {

                if (pAdapter->IfType == IF_TYPE_ETHERNET_CSMACD) {
                    count++;
                }
                else if (pAdapter->IfType == IF_TYPE_IEEE80211) {
                    count++;
                }
                else {
                    ULONG type = pAdapter->IfType;
                    type = type;
                }
            }

        }
    }

    return count;
}

int NetworkMonitor::GetAdapterStatus() {
    return CheckAdapterStatus();

}

void NetworkMonitor::CheckInternetConnectivity() {
    if (pNLM) {
        VARIANT_BOOL isConnected;
        pNLM->get_IsConnectedToInternet(&isConnected);

        if (isConnected == VARIANT_TRUE) {

        }
        else {

        }
    }
}