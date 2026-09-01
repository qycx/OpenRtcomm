

#include	"stdafx.h"
#include	<tchar.h>

#include	<mmeapi.h>
#include	<WinSock2.h>


#include	"stdafx.h"
#include	<stdio.h>
#include	<stddef.h>
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
//  #include	"myresource.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"

#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	<windows.h>
#include	<windef.h>
#include	<lmcons.h>
#ifndef  __WINCE__
#include	<lmshare.h>
#endif
#include	<tlhelp32.h>
#include	<iphlpapi.h>

//  #include	"qwmDynFunc.h"

#include	"qmcCmdProc.h"

#include	"tmpCeLib.h"
#include	"qySqlFunc.h"
#include	"qyThread.h"
#include	"isCmdConst.h"
#include	"qyCusResTemp.h"
#include	"qmCfg_isCli.h"
#include <smCommProc.h>



//
int getSmCfgDir_cli(TCHAR* cfgDirName, int cfgDirNameLen)
{
	//CCtxQyMc* pQyMc = g_pQyMc;

	TCHAR  tBuf[256] = _T("");
	unsigned  int  uiType = 0;
	qyGetRegCfgT(HKEY_CURRENT_USER, _T(CONST_qyRootKey_qnmScheduler_misClient), _T("smCfgDir"), (char*)tBuf, sizeof(tBuf), &uiType);
	tBuf[mycountof(tBuf) - 1] = 0;
	tTrim(tBuf);

	if (!tBuf[0]) {
		safeTcsnCpy(DEFAULT_smCfgDir, cfgDirName, cfgDirNameLen);
	}
	else {
		safeTcsnCpy(tBuf, cfgDirName, cfgDirNameLen);
	}

	//
	return  0;
}




