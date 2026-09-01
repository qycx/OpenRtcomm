

#include	"stdafx.h"

#include	<WinSock2.h>
#include	<windows.h>
#include	<tchar.h>
//
#include	<mmsystem.h>

#include	"qmOpenCommon.h"
#include	"qytcharcommproc.h"







extern  "C"  int  waitForObject(HANDLE * ph, DWORD  dwMilliseconds)
{
	DWORD	dwRet = 0;

	if (!ph)  return  -1;

	if (*ph) {

		dwRet = WaitForSingleObject(*ph, dwMilliseconds);
		if (dwRet != WAIT_TIMEOUT && dwRet != WAIT_FAILED) {

			CloseHandle(*ph);  *ph = NULL;

		}
	}

	return  0;

}


//
extern  "C"  int  waitForObject1(HANDLE* ph, DWORD  dwMilliseconds, Param_waitForObject* pParam)
{
	DWORD	dwRet = 0;

	if (!ph)  return  -1;

	if (*ph) {

		dwRet = WaitForSingleObject(*ph, dwMilliseconds);
		if (dwRet != WAIT_TIMEOUT && dwRet != WAIT_FAILED) {
			//
			DWORD  ec = 0;
			GetExitCodeProcess(*ph, &ec);
			//
			if (pParam) {
				pParam->ec = ec;
			}
			//
			CloseHandle(*ph);  *ph = NULL;

		}
	}

	return  0;

}


//

#include <tchar.h>
#include <stdlib.h>

void myLog(const TCHAR* fmt, ...)
{
	TCHAR buf[1024];
	va_list a; va_start(a, fmt);
	_vstprintf_s(buf, _countof(buf), fmt, a);   // TCHAR 格式化
	va_end(a);
	_tcsncat_s(buf, _countof(buf), _T("\n"), _TRUNCATE);

	// 转 UTF-8，保证日志文件中文可读
	int need = WideCharToMultiByte(CP_UTF8, 0, buf, -1, NULL, 0, NULL, NULL);
	char* mb = new char[need];
	WideCharToMultiByte(CP_UTF8, 0, buf, -1, mb, need, NULL, NULL);
	FILE* f = fopen("C:\\tttbbb\\CrashDumps_probe.log", "a");
	if (f) { fputs(mb, f); fclose(f); }
	delete[] mb;
}
