

#include	"stdafx.h"

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


