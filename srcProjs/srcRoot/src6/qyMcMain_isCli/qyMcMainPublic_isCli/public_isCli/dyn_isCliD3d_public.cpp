
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



BOOL  dyn_bD3dUsing(  MC_VAR_isCli		*	pProcInfo,  BOOL  *  pm_bActive  )
{
	//  
	if  (  !pProcInfo  )  return  FALSE;
	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;

	if  (  !pFuncs->isCliD3d.bOk  )  return  FALSE;

	return  pFuncs->isCliD3d.pf_bD3dUsing( pm_bActive );
}


//  2014/01/12
BOOL  dyn_bFullScreen_d3dWnd(  CCtxQmc  *  pProcInfo,  HWND  hD3dWnd  )
{
	//
	if  (  !pProcInfo  )  return  FALSE;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  FALSE;

	if  (  !pFuncs->isCliD3d.bOk  )  return  FALSE;

	return  pFuncs->isCliD3d.pf_bFullScreen_d3dWnd(  hD3dWnd  );
}


//

//  2014/10/31
int  dyn_removeMosaicFromD3dWall(  CCtxQmcTmpl  *  pProcInfoCommon,  int  iIndex_sharedObj  )
{
	//
	if  (  !pProcInfoCommon  )  return  -1;
	if  (  pProcInfoCommon->m_iCtxType  !=  CONST_ctxType_qmc  )  return  -1;
	MC_VAR_isCli	*	pProcInfo	=	(  MC_VAR_isCli  *  )pProcInfoCommon;
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_removeMosaicFromD3dWall(  iIndex_sharedObj  );
}


 int  dyn_getVal_bExists_mosaic(  CCtxQmcTmpl  *  pProcInfoCommon,  int  iIndex_sharedObj,  BOOL  *  pbExists  )
 {
	if  (  !pProcInfoCommon  )  return  -1;
	if  (  pProcInfoCommon->m_iCtxType  !=  CONST_ctxType_qmc  )  return  -1;
	MC_VAR_isCli	*	pProcInfo	=	(  MC_VAR_isCli  *  )pProcInfoCommon;
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_getVal_bExists_mosaic(  iIndex_sharedObj,  pbExists  );
 }


 //
  //  2015/12/12
int  dyn_tryToTalkToMessenger_d3dWall(  CCtxQmc  *  pProcInfo,  QY_MESSENGER_ID  *  pIdInfo,  int  iTalkUsage,  BOOL  bNeedExist_hWnd,  HWND  *  phWnd_mgr  )
{
	//
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_tryToTalkToMessenger_d3dWall(  pIdInfo,  iTalkUsage,  bNeedExist_hWnd,  phWnd_mgr  );
}


//
int  dyn_closeConsoleWall(  CCtxQmcTmpl  *  pProcInfoCommon,  void  *  pGBuf_d3d  )
{
	if  (  !pProcInfoCommon  )  return  -1;
	if  (  pProcInfoCommon->m_iCtxType  !=  CONST_ctxType_qmc  )  return  -1;
	MC_VAR_isCli	*	pProcInfo	=	(  MC_VAR_isCli  *  )pProcInfoCommon;
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  {
		//  未装载，所以没有窗口需要关闭 
		return  0;
	}

	return  pFuncs->isCliD3d.pf_closeConsoleWall(  pGBuf_d3d  );
}





