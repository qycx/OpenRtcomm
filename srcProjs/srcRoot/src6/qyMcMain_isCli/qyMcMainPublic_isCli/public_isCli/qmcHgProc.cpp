

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
//
#include	"policyAvParams.h"


#include	"myDb.h"

#include	"isCliCorePublic.h"
#include	"isCliHelpPublic.h"
#include	"qyMessengerHelpPublic.h"
#include	"imgProcessPublic.h"
#include	"isCliD3dPublic.h"
#include	"qisWallsProc.h"
#include	"qmcObjVarPublic.h"
#include	"qmcTaskPublic.h"
#include	"qmcSharePublic.h"
#include	"dlgShareDynBmpsProc.h"
#include	"funcsForIsCliHelp.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliExPublic.h"
#include	"ctxMcThread.h"

//
#include	"qmcVideoTool.h"
//#include	"ctxQmc_gui.h"
#include	"policyAvParams.h"
#include	"qyAvRecordPublic.h"
//#include	"qmcVideoCapture_isCli.h"
//#include	"qmcCommFunc_isCli.h"
#include	"qmcCmdProc.h"
#include	"qyMcMainWndProc.h"
#include	<shellapi.h>
//#include	"resource.h"

#include	"smCommProc.h"
#include	"dlgtalkproc.h"
#include	"hgCommProc.h"
#include	"policyIsClientFunc.h"



int qmcProc_xt_resp( Param_sxrz_servReply  *  pParam)
{
	int  iErr = -1;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	TCHAR  tBuf[128];
	char  buf[128];

	//
	do {

		//
		showInfo_open0(0, 0, _T("recv xtResp"));

		//
		pProcInfo->xt.dwTickCnt_lastXtResp = myGetTickCount(nullptr);
		pProcInfo->xt.nTimes_waitForXtResp = 0;
		pProcInfo->xt.bGotOnce_xtResp = true;

		//
		DWORD dwIp_2ndMcu = 0;
		DWORD  dwIp_confMcu  =  0;
		dwIp_2ndMcu = inet_addr(pParam->str2ndMcuIp);
		dwIp_confMcu = inet_addr(pParam->confMcuIp);
		//
		if(  //bulIpValid(dwIp_2ndMcu)&& 
			bulIpValid(dwIp_confMcu) )
		{
#if 0
			if (pMisCnt->dualSystem.dw2ndMcuIp != dwIp_2ndMcu) {
				pMisCnt->dualSystem.dw2ndMcuIp = dwIp_2ndMcu;
				//
				ulIp2Str(dwIp_2ndMcu, buf, mycountof(buf));
				_sntprintf(tBuf, mycountof(tBuf), _T("xt_resp: dw2ndMcuIp changed to %S"), buf);
				showInfo_open0(0, 0, tBuf);
			}
#endif
			//
			if (pMisCnt->dualSystem.dwConfMcuIp != dwIp_confMcu) {
				//
				char ip_old[CONST_qyMaxIpLen + 1];
				ulIp2Str(pMisCnt->dualSystem.dwConfMcuIp, ip_old, mycountof(ip_old));
				ulIp2Str(dwIp_confMcu, buf, mycountof(buf));
				_sntprintf(tBuf, mycountof(tBuf), _T("xt_resp: change dwConfMcuIp %S to %S"), ip_old,  buf);
				showInfo_open0(0, 0, tBuf);

				//
				pMisCnt->dualSystem.dwConfMcuIp = dwIp_confMcu;
			}
			//
#if 0
			char  str2ndMcuIp[CONST_qyMaxIpLen + 1] = "";
			get_2ndMcu(str2ndMcuIp, mycountof(str2ndMcuIp));
			if (stricmp(str2ndMcuIp, pParam->str2ndMcuIp)) {
				set_2ndMcu(pParam->str2ndMcuIp);
			}
#endif

		}

		//
		iErr = 0;
	} while (false);

	return  iErr;
}

