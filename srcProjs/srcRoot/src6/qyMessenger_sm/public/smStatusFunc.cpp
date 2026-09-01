



#include	"stdafx.h"

#include	<qstring.h>




#include "CQmcLogin.h"

#include	"qyCusResTemp.h"

#include "ctxQmc.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliHelpPublic.h"
#include	"ctxQmc_sm.h"
#include <qmcVideoCapture_isCli.h>


#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "IPHLPAPI.lib")

#include <iphlpapi.h>

#include <stdio.h>
#include <stdlib.h>


bool  bCommEnc()
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));


	if (pMisCnt->commEncCtx.common.type)  return  true;

	return  false;
}


//
int  getIpInfo(char* str1stMcu, int  sizeof_str1stMcu, char* str2ndMcu, int  sizeof_str2ndMcu, char* confMcu, int  sizeof_confMcu,  char  *  localIp,  int  sizeof_localIp)
{

	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
	if (!pCtxSm)  return  -1;
	Sm_terminal_initCfg* pCfg = &pCtxSm->smTerminalInitCfg;


	//pProcInfo->authInfo.ip
	safeStrnCpy(pCfg->terminal_mcu, str1stMcu, sizeof_str1stMcu);
	safeStrnCpy(pCfg->terminal_mcu2, str2ndMcu, sizeof_str2ndMcu);
	//
	ulIp2Str(pMisCnt->dualSystem.dwConfMcuIp, confMcu, sizeof_confMcu);
	safeStrnCpy(pProcInfo->authInfo.ip, localIp, sizeof_localIp);

	//
	return  0;
}









