#pragma once

/*
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
*/

class INetworkListManager;


class NetworkMonitor {
public:
    NetworkMonitor();    
    ~NetworkMonitor();
    
    void CheckAllNetworks() {
        
        
        CheckAdapterStatus();
        //std::cout << std::endl;
        CheckInternetConnectivity();
    }

    int GetAdapterStatus();
private:
    int CheckAdapterStatus();
    
    void CheckInternetConnectivity();
    
    INetworkListManager* pNLM;
};
