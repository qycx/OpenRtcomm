
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<assert.h>
#include	<stddef.h>
#include	<tchar.h>
#include	<stdlib.h>
#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmPcComm.h"
#include	"qnmAssetsCommProc.h"
#include	"qnmSpCommProc.h"
#include	"qwmNetworkStatusCommProc.h"
#include	"qyTCharCommProc.h"
#include	"qnmCustom.h"
#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"
#include	"tmpCeLib.h"
#include	"qyShowInfoCommon.h"



//  used in qyPublic for internal use. don't use it as a public function.
extern  "C"	 int  qyShowInfo_internal(CTX_q_showInfo * pCtx, int  iShowType, unsigned  int* puiStep, char* clientIp, LPCWSTR  who_from, LPCWSTR  who_to, LPCWSTR  where, LPCWSTR  doStr, LPCWSTR  fmt, ...)
{
#ifdef  __WINCE__
	return  0;
#endif

	va_list			args;
#ifndef  __WINCE__
	int				errnoBuf;
#endif
	HWND			firstWnd = NULL;
	QY_SHOW_STRUCT	showStruct;
	//  char			fileNameBuf[257];
	//  char			timeBuf[CONST_qyTimeLen  +  1];
	FILE* fperr = NULL;
	int				fileLen = 0;


#ifndef  __DEBUG__
	if (iShowType == CONST_qyShowType_debug)  return  0;
#endif

#ifndef  __WINCE__
	errnoBuf = errno;
#endif

	va_start(args, fmt);

	memset(&showStruct, 0, sizeof(showStruct));
	showStruct.iType = iShowType;
	if (clientIp && clientIp[0])  showStruct.ulClientIp = inet_addr(clientIp);
	if (who_from) {
		_snwprintf(showStruct.who_from, mycountof(showStruct.who_from), L"%s", who_from);
	}
	if (who_to) {
		_snwprintf(showStruct.who_to, mycountof(showStruct.who_to), L"%s", who_to);
	}
	if (where) {
		_snwprintf(showStruct.whereBuf, mycountof(showStruct.whereBuf), L"%s", where);
	}
	//  when
	GetLocalTime(&showStruct.when);	//  2007/06/01
	if (puiStep) {				//  2008/04/28
		(*puiStep)++;
		showStruct.usStep = *puiStep;
	}
	//
	showStruct.dwProcessId = GetCurrentProcessId();  //  2015/08/30
	showStruct.dwThreadId = GetCurrentThreadId();
	//
	if (doStr) {
		_snwprintf(showStruct.doStr, mycountof(showStruct.doStr), L"%s", doStr);
	}
	_vsnwprintf(showStruct.what, mycountof(showStruct.what) - 1, fmt, args);

	//
	//  MACRO_qyAssert(  g_pShowInfoStruct,  _T(  "qyShowInfo1: g_pShowInfoStruct is null"  )  );
	//  if  (  !g_pShowInfoStruct  )  return  -1;
	if (pCtx && pCtx->pf_showInfo_open) {
		TCHAR  tBuf[256];
		_sntprintf(tBuf, mycountof(tBuf), _T("%s %s %s %s"), showStruct.who_from, showStruct.who_to, showStruct.doStr, showStruct.what);
		pCtx->pf_showInfo_open(0, showStruct.whereBuf, tBuf);
	}
	else
	{
		//
		TCHAR* errHintWndCls = (TCHAR*)CONST_qnmStatusToolWndClass_client;

		if (errHintWndCls[0]) {

			firstWnd = FindWindow(errHintWndCls, NULL);
			if (firstWnd) {
				COPYDATASTRUCT	tmpCopyData;

				tmpCopyData.lpData = &showStruct;
				tmpCopyData.cbData = sizeof(showStruct);
				SendMessage(firstWnd, WM_COPYDATA, NULL, (LPARAM)&tmpCopyData);
			}

			//  traceLogA(  "%s %s %s %s %s",  showStruct.when,  showStruct.who,  showStruct.where,  showStruct.doStr,  showStruct.what  );

		}

		//  2014/05/09
		errHintWndCls = (TCHAR*)CONST_qnmStatusToolWndClass;
		if (errHintWndCls[0]) {

			firstWnd = FindWindow(errHintWndCls, NULL);
			if (firstWnd) {
				COPYDATASTRUCT	tmpCopyData;

				tmpCopyData.lpData = &showStruct;
				tmpCopyData.cbData = sizeof(showStruct);
				SendMessage(firstWnd, WM_COPYDATA, NULL, (LPARAM)&tmpCopyData);
			}
		}

	}

	/*
	*/

	va_end(args);

#ifndef  __WINCE__
	errno = errnoBuf;
#endif

	return  0;
}
