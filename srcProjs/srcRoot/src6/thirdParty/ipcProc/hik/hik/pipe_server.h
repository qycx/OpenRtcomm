#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <functional>
#include <thread>
#include <string>
#include <tchar.h>

#pragma warning(disable:4996)

extern std::wstring ConvertStringToWString(const std::string& str);

using namespace std;
#define BUFSIZE 1024

extern int printLogChar(const char* log);

class Pipe_Server {
public:
	Pipe_Server(std::string pipe_name, std::function<std::string(std::string)> callBackFun) :
		hPipe_(nullptr),
		isRuning_(false)
	{
		pipe_name_ = "\\\\.\\Pipe\\";
		pipe_name_ += pipe_name;
		if (pipe_name == "") {
			printLogChar("pipe name is empty");
			return;
		}
		printLogChar("Create pipe server:");
		printLogChar(pipe_name.c_str());

		callBackFun_ = callBackFun;

		callBackFun_ = callBackFun;

	}
	~Pipe_Server() {
		Close();
	}

	bool Start() {

		std::wstring wstr = ConvertStringToWString(pipe_name_);
		hPipe_ = CreateNamedPipe(wstr.c_str(), PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT
			, PIPE_UNLIMITED_INSTANCES, BUFSIZE, BUFSIZE, NMPWAIT_WAIT_FOREVER, 0);

		//waiting to be connected
		if (hPipe_) {
			isRuning_ = true;

			std::thread run_thread(std::bind(&Pipe_Server::run, this));
			run_thread.detach();

			return true;

			
		}
		else {

		}

		return false;
	}

	void Close() {

		if (hPipe_) {
			FlushFileBuffers(hPipe_);
			DisconnectNamedPipe(hPipe_);
			CloseHandle(hPipe_);
			hPipe_ = nullptr;
		}
	}

private:
	std::function<std::string(std::string)> callBackFun_;
	std::string pipe_name_;
	HANDLE hPipe_;
	bool  isRuning_;

	WCHAR* toWChar(const char* c) {
		WCHAR wszClassName[256];
		memset(wszClassName, 0, sizeof(wszClassName));
		MultiByteToWideChar(CP_ACP, 0, c, strlen(c) + 1, wszClassName,
			sizeof(wszClassName) / sizeof(wszClassName[0]));
		return wszClassName;
	}

	void run() {
		if (ConnectNamedPipe(hPipe_, NULL) != NULL) {
			printLogChar("ConnectNamedPipe success");			
		}
		else {
			printLogChar("ConnectNamedPipe failed");
			CloseHandle(hPipe_);//关闭管道
			return;
		}

		printLogChar(pipe_name_.c_str());
		printLogChar("run begin");


		string recvData = "";
		DWORD len = 0;
		char buffer[BUFSIZE] = { '\0' };
		while (isRuning_) {


			bool fSuccess = ReadFile(hPipe_, buffer, BUFSIZE * sizeof(char), &len, NULL);
			if (fSuccess) {
				//char buffer2[BUFSIZE + 1] = { 0 };
				//memcpy(buffer2, buffer, len);				
				recvData.append(buffer, len);
				//std::cout << recvData << std::endl;
				
				int pos = recvData.find("\r\n");
				if (pos != std::string::npos) {
					std::string msg = recvData.substr(0, pos);
					recvData.erase(0, pos + 2);


					std::string res_msg = callBackFun_(msg);
				}
			}
			else {
				Sleep(10);
			}
		}
	}

	/*
	void run_bak() {

		while (1) {
			HANDLE hPipe = CreateNamedPipe(pipe_name_.c_str(), PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT
				, PIPE_UNLIMITED_INSTANCES, 0, 0, NMPWAIT_WAIT_FOREVER, 0);

			//waiting to be connected
			if (ConnectNamedPipe(hPipe, NULL) != NULL) {
				std::cout << "连接成功，开始发送数据" << std::endl;

				//接收服务端发回的数据
				BOOL fSuccess = false;
				DWORD len = 0;
				char buffer[BUFSIZE];
				string recvData = "";
				while (true) {
					fSuccess = ReadFile(hPipe, buffer, BUFSIZE * sizeof(char), &len, NULL);
					char buffer2[BUFSIZE + 1] = { 0 };
					memcpy(buffer2, buffer, len);
					recvData.append(buffer2);
					if (!fSuccess || len < BUFSIZE)
						break;
				}
				std::cout << "recv data: \n" << recvData.c_str() << std::endl;

				std::string res_msg = callBackFun_(recvData);

				DWORD dwWrite;
				char* pStr = nullptr;
				pStr = new char(res_msg.size() + 1);    //存在内存泄露
				strcpy(pStr, res_msg.c_str());    //将string转变成char*
				if (!WriteFile(hPipe, pStr, strlen(pStr), &dwWrite, NULL)) {
					std::cout << "write failed..." << std::endl;
					DisconnectNamedPipe(hPipe);
					CloseHandle(hPipe);//关闭管道
					std::cout << "结束一次管道通信" << std::endl;

					//delete pStr;    //造成程序错误

					break;
				}
				else {
					std::cout << "send data: \n" << pStr << std::endl;
					DisconnectNamedPipe(hPipe);
					CloseHandle(hPipe);//关闭管道

					//delete pStr;    //造成程序错误

					std::cout << "结束一次管道通信" << std::endl;
				}
			}
			else {
				std::cout << "pipe connect failed" << std::endl;
				Sleep(1000);
			}
		}
	}
	*/
};