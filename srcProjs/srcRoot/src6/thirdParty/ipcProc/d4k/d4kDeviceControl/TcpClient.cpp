#include "stdafx.h"
#include "TcpClient.h"


#pragma comment(lib, "ws2_32.lib")

TcpClient::TcpClient(const char* serverIp, int port) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    _socket = socket(AF_INET, SOCK_STREAM, 0);

    _serverAddress.sin_family = AF_INET;
    _serverAddress.sin_port = htons(port);
    _serverAddress.sin_addr.s_addr = inet_addr(serverIp);
}

TcpClient::~TcpClient() {
    closesocket(_socket);
    WSACleanup();
}

bool TcpClient::Connect() {
    if (connect(_socket, (sockaddr*)&_serverAddress, sizeof(_serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
        return false;
    }
    return true;
}

void TcpClient::Send(const char* data, int length) {
    send(_socket, data, length, 0);
}

int TcpClient::Receive(char* buffer, int length) {
    return recv(_socket, buffer, length, 0);
}