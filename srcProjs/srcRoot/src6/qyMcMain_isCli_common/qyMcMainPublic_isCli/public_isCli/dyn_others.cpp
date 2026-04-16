

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
//#include	"msAecCommon.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"
#include	"amCapPublic.h"
#include	"isCliD3dPublic.h"
#include	"qyMcMainWndProc.h"
#include	"imgProcessPublic.h"



QY_OBJ_DB  *  dyn_getProcedObjDb(  void  *  p0,  int  iDsnIndex  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  NULL;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  NULL;

	return  pFuncs->pf_getProcedObjDb(  pProcInfo->pQyMc,  p0,  iDsnIndex  );
}


//
//
int  dyn_tmpHandler_showMsg(  void  *  hDlgTalkParam,  void  *  p1, void  *  pMsgParam  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	return  pFuncs->pf_tmpHandler_showMsg(  hDlgTalkParam,  p1,  pMsgParam  );
}


#if  0
extern  "C"  bool dyn_bPktSkipped(Param_bPktSkipped* pParam, int nWhere, int fps_expected, int fps_real, int nQNodes1, int totalPkts, int nPkts_left, bool b4k, int* piTotalPkts_lastOk, unsigned  __int64* pnFactor)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);

	if (!pFuncs->ancPktProcess.pf_bPktSkipped)  return  false;

	int  tmpiRet;
	tmpiRet = pFuncs->ancPktProcess.pf_bPktSkipped(pParam, nWhere, fps_expected, fps_real, nQNodes1, totalPkts, nPkts_left, b4k, piTotalPkts_lastOk, pnFactor);

	return  tmpiRet;
}

//
extern "C" int  dyn_player_get_fps(Param_getFps* pParam, __int64 pIdInfo, unsigned  short  usFps_expected, unsigned  int  uiSampleTimeInMs, TMP_fps_info* pFpsInfo, TCHAR* pHint)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);

	if (!pFuncs->ancPktProcess.pf_bPktSkipped)  return  -1;

	int  tmpiRet;
	tmpiRet = pFuncs->ancPktProcess.pf_player_get_fps(pParam, pIdInfo, usFps_expected, uiSampleTimeInMs, pFpsInfo, (TCHAR*)_T(""));
	return  tmpiRet;

}
#endif 


