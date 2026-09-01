
#include	"stdafx.h"
#include	<tchar.h>
#include	<mmeapi.h>

#include	<winsock2.h>

#include	"qmOpenCommon.h"
#include	"tmpDefs_open.h"
#include	"smCommProc.h"


#include	"qmCommon.h"
#include	"saveAvCommProc.h"




//
void getSaveAvDir(TCHAR* dirName, int dirNameLen)
{
	//CCtxQyMc* pQyMc = g_pQyMc;

	TCHAR  tBuf[256] = _T("");
	unsigned  int  uiType = 0;
	qyGetRegCfgT(HKEY_LOCAL_MACHINE, _T(CONST_qyRootKey_qnmScheduler_misClient), _T("saveAvDir"), (char*)tBuf, sizeof(tBuf), &uiType);
	tBuf[mycountof(tBuf) - 1] = 0;
	tTrim(tBuf);

	//
	if (!tBuf[0]) {
		safeTcsnCpy(DEFAULT_saveAvDir, dirName, dirNameLen);
	}
	else {
		safeTcsnCpy(tBuf, dirName, dirNameLen);
	}

	//
	return;
}



