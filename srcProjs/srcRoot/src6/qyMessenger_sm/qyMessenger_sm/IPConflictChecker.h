#pragma once
#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <iostream>
#include <vector>
#include <string>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

class IPConflictChecker {
private:
	std::vector<std::string> localIPs;

public:
	IPConflictChecker() {
		InitializeWinsock();
		GetLocalIPs();
	}

	~IPConflictChecker() {
		WSACleanup();
	}

private:
	void InitializeWinsock() {
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			throw std::runtime_error("WSAStartup failed");
		}
	}

	void GetLocalIPs() {
		char hostname[256];
		if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
			return;
		}

		struct hostent* host = gethostbyname(hostname);
		if (host == NULL) return;

		for (int i = 0; host->h_addr_list[i] != 0; ++i) {
			struct in_addr addr;
			memcpy(&addr, host->h_addr_list[i], sizeof(struct in_addr));
			localIPs.push_back(inet_ntoa(addr));
		}
	}

public:
	bool CheckSpecificIP(const std::string& ip) {
		for (const auto& localIP : localIPs) {
			if (localIP == ip) {
				return false;
			}
		}

		return CheckIPWithARP2(ip);
	}

	void CheckLocalNetwork() {
		std::cout << "开始检查本地网络IP冲突..." << std::endl;


		for (const auto& localIP : localIPs) {
			std::string subnet = GetSubnet(localIP);
			std::cout << "检查子网: " << subnet << "..." << std::endl;

			for (int i = 1; i <= 10; i++) {
				std::string testIP = subnet + "." + std::to_string(i);
				if (testIP != localIP) {
					CheckIPWithARP(testIP);
					Sleep(100); 
				}
			}
		}
	}

private:
	bool CheckIPWithARP(const std::string& ip) {
		DWORD dwRetVal;
		IPAddr DestIp = inet_addr(ip.c_str());
		ULONG MacAddr[2];
		ULONG PhysAddrLen = 6;

		dwRetVal = SendARP(DestIp, 0, MacAddr, &PhysAddrLen);

		if (dwRetVal == NO_ERROR) {
			BYTE* mac = (BYTE*)MacAddr;
			std::cout << "冲突! IP " << ip << " 被 MAC: ";
			printf("%02X-%02X-%02X-%02X-%02X-%02X 使用\n",
				mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
			return true;
		}

		return false;
	}

	bool CheckIPWithARP2(const std::string& ip) {
		DWORD dwRetVal;
		IPAddr DestIp = inet_addr(ip.c_str());
		ULONG MacAddr[2];
		ULONG PhysAddrLen = 6;

		dwRetVal = SendARP(DestIp, 0, MacAddr, &PhysAddrLen);

		if (dwRetVal == NO_ERROR) {
			BYTE* mac = (BYTE*)MacAddr;
			/*std::cout << "冲突! IP " << ip << " 被 MAC: ";
			printf("%02X-%02X-%02X-%02X-%02X-%02X 使用\n",
				mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);*/

			

			return true;
		}

		return false;
	}

	std::string GetSubnet(const std::string& ip) {
		size_t lastDot = ip.find_last_of('.');
		if (lastDot != std::string::npos) {
			return ip.substr(0, lastDot);
		}
		return ip;
	}
};
