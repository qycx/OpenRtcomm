
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





//  void  *  dyn_getZoneObjsInfo_d3dWall(  HWND  hDlgWalls,  int  iWndContentType,  int  iZoneObjsType  )
void  *  dyn_getZoneObjsInfo_d3dWall(  MC_VAR_isCli  *  pProcInfo,  HWND  hDlgWalls,  int  iWndContentType,  int  iZoneObjsType  )
{
	//MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  NULL;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  NULL;

	if  (  !pFuncs->isCliD3d.bOk  )  return  NULL;

	return  pFuncs->isCliD3d.pf_getZoneObjsInfo_d3dWall(  hDlgWalls,  iWndContentType,  iZoneObjsType  );
}

//
int  dyn_set_g_pQyMc_isCliD3d(  void  *  pQyMc  )
{
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_set_g_pQyMc_isCliD3d(  pQyMc  );
}

int  dyn_dllInit_d3d_isCli(  )
{
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_dllInit_d3d_isCli(  );
}
			
int  dyn_dllExit_d3d_isCli(  )
{
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_dllExit_d3d_isCli(  );
}

void  *  dyn_GBuf_d3d_isCli_new(  )
{
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  NULL;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  NULL;

	if  (  !pFuncs->isCliD3d.bOk  )  return  NULL;

	return  pFuncs->isCliD3d.pf_GBuf_d3d_isCli_new(  );
}

void  dyn_GBuf_d3d_isCli_free(  void  **  ppGBuf_d3d_isCli  )
{
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	if  (  !pFuncs->isCliD3d.bOk  )  return;

	return  pFuncs->isCliD3d.pf_GBuf_d3d_isCli_free(  ppGBuf_d3d_isCli  );
}


//  2014/11/04


unsigned  int  dyn_getMaxCnt_wallMems(  int  iGrpType  )
{
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  0;
	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  0;

	if  (  !pFuncs->isCliD3d.bOk  )  return  0;

	return  pFuncs->isCliD3d.pf_getMaxCnt_wallMems(  iGrpType  );
}


void  *  dyn_getWallMemByIndex(  void  *  pD3D_context,  int  iGrpType,  int  index  )
{
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  NULL;	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  NULL;

	if  (  !pFuncs->isCliD3d.bOk  )  return  NULL;

	return  pFuncs->isCliD3d.pf_getWallMemByIndex(  pD3D_context,  iGrpType,  index  );

}


#if  0
void  *  dyn_getD3dTalkerData(  void  *  pWallMemParam  )
{
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return  NULL;

	if  (  !pFuncs->isCliD3d.bOk  )  return  NULL;

	return  pFuncs->isCliD3d.pf_getD3dTalkerData(  pWallMemParam  );
}
#endif


//









//
int  dyn_createConsoleWall(  void  *  pGBuf_d3d  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_createConsoleWall(  pGBuf_d3d  );
}


//
int dyn_createGeneralWall(HINSTANCE hInstance, LPCTSTR  szTitle, HICON  hIcon,  HMENU  hMenu,  int  x,  int  y)
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_createGeneralWall(  hInstance,  szTitle,  hIcon,  hMenu,  x,  y  );

}



//
void  dyn_myRender()
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	if  (  !pFuncs->isCliD3d.bOk  )  return;

	return  pFuncs->isCliD3d.pf_myRender(  );
}


//  2015/10/06
  int  dyn_getTex2Props(  void  *  p0,  int  iIndex_player,  TEX2_props  *  pProps  )
 {
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_getTex2Props(  p0,  iIndex_player,  pProps  );

 }


int  dyn_fillData_d3d(Ctx_fillData_d3d * pCtx, myDRAW_VIDEO_DATA  *  pPkt,  int  iIndex_player,  PARAM_fillD3d  *  pParam,  BOOL  *  pbFilled  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if (!pCtx) return  -1;
	if  (  !pParam  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_fillData_d3d(  pCtx,  pPkt,  iIndex_player,  pParam,  pbFilled  );
}

int  dyn_fillData_d3d_setDataReady(  myDRAW_VIDEO_DATA  *  pPkt,  int  iIndex_player  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_fillData_d3d_setDataReady(  pPkt,  iIndex_player  );
}


void  *  dyn_qisWallsCfgNew(  unsigned  short  usMaxCnt  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  NULL;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  NULL;

	if  (  !pFuncs->isCliD3d.bOk  )  return  NULL;

	return  pFuncs->isCliD3d.pf_qisWallsCfgNew(  usMaxCnt  );
}

void  dyn_qisWallsCfgFree(  void  **  ppQIS_walls_cfg  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	if  (  !pFuncs->isCliD3d.bOk  )  return;

	return  pFuncs->isCliD3d.pf_qisWallsCfgFree(  ppQIS_walls_cfg  );
}


//
int  dyn_addQisWallCfg(  void  *  pQIS_walls_cfg,  unsigned  int  uiType,  LPCTSTR  fileName,  int  *  piIndex  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_addQisWallCfg(  pQIS_walls_cfg,  uiType,  fileName,  piIndex  );
}




int  dyn_setCurQisWallCfg(  int  curIndex,  void  *  pQIS_walls_cfg  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_setCurQisWallCfg(  curIndex,  pQIS_walls_cfg  );

}








//
int  dyn_d3dWall_askToRefreshMenu(  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_d3dWall_askToRefreshMenu(  );

}


//
int  dyn_d3dWall_askToRefreshIa(  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_d3dWall_askToRefreshIa(  );
}



//
int  dyn_getVal_bWmTalkerShadowExists(  WM_ID  *  pWmId,  BOOL  *  pbExists  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_getVal_bWmTalkerShadowExists(  pWmId,  pbExists  );

}

//




  int  dyn_refreshDlgTalkSubtitlesCfg_d3dWall(  HWND  hMgr  )
 {
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_refreshDlgTalkSubtitlesCfg_d3dWall(  hMgr  );

 }

  //
  //
 int  dyn_refreshDlgTalkSubtitleMsgs_d3dWall(  HWND  hMgr  )
{
	//
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_refreshDlgTalkSubtitleMsgs_d3dWall(  hMgr  );
 }


  //
  int  dyn_d3dWall_refreshAllWallMems(  )
  {
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_d3dWall_refreshAllWallMems(  );

  }

	
  //  2015/12/13	
  int  dyn_d3dWall_refreshWallMemByTalker(  HWND  hDlgTalk  )
  {
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_d3dWall_refreshWallMemByTalker(  hDlgTalk  );

  }


  //
int  dyn_d3dWall_refreshImgs(  HWND  hDlgTalk_mgr,  TCHAR  *  hint  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_d3dWall_refreshImgs(  hDlgTalk_mgr,  hint  );

}

//
#if  0
 int  dyn_renew_dwModifiedTickCnt_layout(  CTX_qm_thread  *  pCtxQmThread,  void  *  pWALLMem_u  )
 {
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->isCliD3d.bOk  )  return  -1;

	return  pFuncs->isCliD3d.pf_renew_dwModifiedTickCnt_layout(  pCtxQmThread,  pWALLMem_u  );

 }
#endif





