#pragma once

#include <iostream>
#include <string>
#include <Winsock2.h>

#pragma warning(disable:4996)

class TcpClient {
private:
    SOCKET _socket;
    sockaddr_in _serverAddress;

public:
    TcpClient(const char* serverIp, int port);

    ~TcpClient();

    bool Connect();

    void Send(const char* data, int length);

    int Receive(char* buffer, int length);
};
