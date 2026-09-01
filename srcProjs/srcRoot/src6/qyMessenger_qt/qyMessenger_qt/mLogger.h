#pragma once
#include <string>

#ifdef _DEBUG
	#define LOG(...) WriteLog(__VA_ARGS__)
#else
	#define LOG(...) ((void)0) 
#endif

void WriteLog(const std::string& message, const std::string& fileName = "app.log");