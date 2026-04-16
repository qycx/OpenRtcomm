
#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"dlgtalkproc.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qmcDmoPublic.h"

#include	"wallTalkers.h"
#include	"qmcGpsProc.h"
#include	"msAecCommon.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"
#include	"amCapPublic.h"
#include	"isCliD3dPublic.h"
#include	"qyMcMainWndProc.h"
#include	"imgProcessPublic.h"



int dyn_help_webrtc_init(int iCntLimit_activeMems_from,
	PF_inStream4 pf_is,
	void* is_p0,
	PF_outStream pf_os,
	void* os_p0,
	void** ppObj)
{
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;

	if (!pFuncs->help_webrtc1.bOk) {
		showInfo_open0(0, 0, _T("dyn_help_webrtc_init: not loaed"));
		return  -1;
	}

	return  pFuncs->help_webrtc1.pf_help_webrtc_init( iCntLimit_activeMems_from,pf_is,is_p0,pf_os,os_p0, ppObj);

}


void dyn_help_webrtc_exit(void** ppObj)
{
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return;

	if (!pFuncs->help_webrtc1.bOk) {
		showInfo_open0(0, 0, _T("dyn_help_webrtc_exit: not loaed"));
		return;
	}

	pFuncs->help_webrtc1.pf_help_webrtc_exit(ppObj);
	return;

}





