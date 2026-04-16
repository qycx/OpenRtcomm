#include "stdafx.h"
#include "pipe_client.h"
std::wstring ConvertStringToWString(const std::string& str) {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(str);
}