#pragma once

#define AUTH_CODE_SOCKET_FAIL			20	//网络通讯初始化失败 
#define AUTH_CODE_CONNECT_FAIL			21	//连接服务器失败 
#define AUTH_CODE_SEND_INFO_FAIL		22	//发送请求信息失败
#define AUTH_CODE_RECV_INFO_FAIL		23	//接收响应信息失败
#define AUTH_CODE_BIND_SOCKET_FAIL		24	//绑定SOCKET失败
#define AUTH_CODE_LISTEN_SOCKET_FAIL	25	//监听SOCKET失败
#define AUTH_CODE_ACCEPT_SOCKET_FAIL	26	//接受客户端连接失败