#pragma once
#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>

#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <functional>
#include <thread>
#include <string>
#include <codecvt>
#include <locale>
#include <tchar.h>

extern int printLogChar(const char* log);

extern std::wstring ConvertStringToWString(const std::string& str);

#define BUFSIZE 128

#pragma warning(disable:4996)

enum PipeClientState {
	PipeClientState_init = 0,
	PipeClientState_wait = 1,
	PipeClientState_open = 2,
	PipeClientState_exit = 3,
};



class Pipe_Client {
public:
	Pipe_Client(std::string pipe_name) : 
		hPipe_(nullptr) {
		pipe_name_ = "\\\\.\\Pipe\\";
		pipe_name_ += pipe_name;
		if (pipe_name == "") {
			printLogChar("pipe name is empty");
			return;
		}
		printLogChar("pipe name is: ");
		printLogChar(pipe_name.c_str());

	}

	bool isRuning_;
	PipeClientState  state_;
	HANDLE hPipe_;

	void Start() {
		state_ = PipeClientState_init;

		isRuning_ = true;

		std::thread run_thread(std::bind(&Pipe_Client::run, this));
		run_thread.detach();

	}

	~Pipe_Client() {
		Close();
	}

	bool Connect() {
		//std::wstring wstr = ConvertStringToWString(pipe_name_);
		if (WaitNamedPipe(pipe_name_.c_str(), NMPWAIT_WAIT_FOREVER) == FALSE) {
			//std::cout << "wait pipe failed" << std::endl;
			printLogChar("wait pipe failed");
			return false;
		}

		state_ = PipeClientState_wait;

		//LOG(INFO) << "打开命名管道: " << pipe_name_;
		//std::cout << "打开命名管道: " << pipe_name_ << std::endl;
		hPipe_ = CreateFile(pipe_name_.c_str(), GENERIC_READ | GENERIC_WRITE, 0,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if ((long)hPipe_ == -1) {
			printLogChar("open pipe failed");
			return false;
		}
		state_ = PipeClientState_open;

		return true;
	}

	void run() {
		
		while (true) {
			//std::wstring wstr = ConvertStringToWString(pipe_name_);
			printLogChar("----------run-----------begin---------");
			printLogChar(pipe_name_.c_str());
			if (WaitNamedPipe(pipe_name_.c_str(), NMPWAIT_WAIT_FOREVER) == FALSE) {
				printLogChar("wait pipe failed");
				Sleep(10);
				continue;
			}

			printLogChar("----------run--------------------");

			state_ = PipeClientState_wait;

			hPipe_ = CreateFile(pipe_name_.c_str(), GENERIC_READ | GENERIC_WRITE, 0,
				NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

			if ((long)hPipe_ == -1) {
				printLogChar("open pipe failed");
				break;
			}
			state_ = PipeClientState_open;
			printLogChar("----------run-----------end---------");
			
			break;
		}

		/*
		std::string recvData = "";
		
		BOOL fSuccess = false;
		DWORD len = 0;
		char buffer[BUFSIZE] = {'\0'};

		while (isRuning_) {
			
			//fSuccess = ReadFile(hPipe_, buffer, BUFSIZE * sizeof(char), &len, NULL);
			//char buffer2[BUFSIZE + 1] = { 0 };
			//memcpy(buffer2, buffer, len);
			//recvData.append(buffer2);
			//std::cout << recvData << std::endl;
			//if (!fSuccess || len < BUFSIZE)
			//	break;
				

			Sleep(10);
		}
		*/
	}

	void Write(const char* content) {

		printLogChar("-------Write-----begin---------");

		if (state_ != PipeClientState_open) {
			return;
		}
		printLogChar("-------Write--------------");

		DWORD    dwWrite;
		if (!WriteFile(hPipe_, content, strlen(content), &dwWrite, NULL)) {
			//std::cout << "write failed..." << std::endl << std::endl;
			printLogChar("-------Write-----failed---------");
			printLogChar(content);
			
		}
		else {
			//std::cout << "write:" << dwWrite << std::endl;
			printLogChar("-------Write-----success---------");
			FlushFileBuffers(hPipe_);
		}
		printLogChar("-------Write-----end---------");
	}

	void Close(){

		if (hPipe_) {
			FlushFileBuffers(hPipe_);
			DisconnectNamedPipe(hPipe_);
			CloseHandle(hPipe_);
			hPipe_ = nullptr;
		}
	}
	/*
	std::string sendAndGetMsg(std::string send_msg) {

		if (WaitNamedPipe(pipe_name_.c_str(), NMPWAIT_WAIT_FOREVER) == FALSE) {
			//LOG(INFO) << "EEEEEEEEE";
			std::cout << "wait pipe failed" << std::endl;
			return "";
		}


		//LOG(INFO) << "打开命名管道: " << pipe_name_;
		std::cout << "打开命名管道: " << pipe_name_ << std::endl;
		HANDLE hPipe = CreateFile(pipe_name_.c_str(), GENERIC_READ | GENERIC_WRITE, 0,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if ((long)hPipe == -1) {
			std::cout << "打开管道失败" << std::endl;
			return "";
		}

		//发送数据
		DWORD    dwWrite;
		static char* pStr = nullptr;
		if (pStr != nullptr) {
			delete pStr;
		}

		pStr = new char(send_msg.size() + 1);
		strcpy(pStr, send_msg.c_str());    //将string转变成char*
		if (!WriteFile(hPipe, pStr, strlen(pStr), &dwWrite, NULL)) {
			std::cout << "write failed..." << std::endl << std::endl;
			return "";
		}
		std::cout << "sent data: " << std::endl << pStr << std::endl << std::endl;
		Sleep(400);


		//接收服务端发回的数据
		std::string recvData = "";
		
		BOOL fSuccess = false;
		DWORD len = 0;
		char buffer[BUFSIZE];

		while (true) {
			fSuccess = ReadFile(hPipe, buffer, BUFSIZE * sizeof(char), &len, NULL);
			char buffer2[BUFSIZE + 1] = { 0 };
			memcpy(buffer2, buffer, len);
			recvData.append(buffer2);
			if (!fSuccess || len < BUFSIZE)
				break;
		}
		std::cout << "recv data:" << std::endl << recvData.c_str() << std::endl << std::endl;
		

		FlushFileBuffers(hPipe);
		DisconnectNamedPipe(hPipe);
		CloseHandle(hPipe);

		return recvData;
	}
	*/

private:
	std::string pipe_name_;
};
