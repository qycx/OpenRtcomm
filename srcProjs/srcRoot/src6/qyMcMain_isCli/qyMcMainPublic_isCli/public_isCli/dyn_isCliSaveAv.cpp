

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
#include	"saveAvProc_open.h"
#include	"isCliSaveAvPublic.h"
//
#include	"ctxMcThread.h"




extern  "C"  __declspec(  dllexport  )  int  dyn_doSaveAv(  SAVE_av_procInfo  *  pSave,  SAVE_av_pktU  *  pSp,  BOOL  *  pbExists_pSvp,  void  *  pCTX_mc_saveAv  )
{	
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if  (  !pProcInfo  )  return  -1;
	if  (  pProcInfo->m_iCtxType  !=  CONST_ctxType_qmc  )  {
		return  -1;
	}
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliSaveAv.bOk  )  return  -1;

	//
	CTX_mc_saveAv  *  pCtx  =  (  CTX_mc_saveAv  *  )pCTX_mc_saveAv;


	return  pFuncs->isCliSaveAv.pf_doSaveAv(  pSave,  pSp,  pbExists_pSvp,  pCtx  );
}