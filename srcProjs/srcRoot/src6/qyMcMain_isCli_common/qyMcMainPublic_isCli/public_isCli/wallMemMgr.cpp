

#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>

#include	"DXUT/Core/DXUT.h"
#include	"DXUT/Optional/DXUTgui.h"
#include	"DXUT/Optional/SDKmisc.h"

//  2014/10/23
#include	"effects11\\inc\\D3dx11effect.h"


#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qySyncCommProc.h"
#include	"qmcVideoCapture_isCli.h"


#include	"isCliD3dCommon.h"
#include	"dlgD3dWall.h"

//
#include	"isCliHelpPublic.h"

//
#include	"cuboidTool.h"

#include	"isCmdConst.h"
#include	"qyCusResTemp.h"
#include	"imgProcessPublic.h"
#include	"dlgTalkProc.h"
#include	"dynFuncs_d3dCall.h"
#include	"funcsForisCliHelp.h"
#include	"subtitlesCfg.h"

#include	"wallMem.h"
#include	"wallMemMgr.h"




//
int  initWmGrp(  int  index_d3dWnd,  int  iGrpType,  unsigned  int  usMaxCnt,  BOOL  bUseZOrder,  WM_grp_sync  *  pGrp  )
{
	int  iErr  =  -1;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	WM_grp_sync  *  pMgr  = pGrp;

	if  (  !usMaxCnt  ||  !pMgr  )  return  -1;
	if  (  pMgr->m_var.usMaxCnt_wmInfoSyncs  )  return  -1;


	CQySyncObj  syncObj;

	syncMtCnt_wLock_wait(  &pMgr->syncMtCnt,  0,  &syncObj,  NULL,  _T(  ""  )  );  
	
	//
	pMgr->m_var.iGrpType  =  iGrpType;

	//
	pMgr->m_var.usMaxCnt_wmInfoSyncs  =  usMaxCnt;
	int  size  =  sizeof(  WM_info_sync  )  *  usMaxCnt;
	pMgr->m_var.pWmInfoSyncs  =  (  WM_info_sync  *  )mymalloc(  size  );
	if  (  !pMgr->m_var.pWmInfoSyncs  )  goto  errLabel;
	memset(  pMgr->m_var.pWmInfoSyncs,   0,  size  );

	//
	int  i;
	for  (  i  =  0;  i  <  pMgr->m_var.usMaxCnt_wmInfoSyncs;  i  ++  )  {
		 WM_info_sync  *  pWis  =  &pMgr->m_var.pWmInfoSyncs[i];
		 //
		 pWis->index_d3dWnd  =  index_d3dWnd;	//  2016/05/28
		 //
		 pWis->iGrpType  =  iGrpType;
		 pWis->index_wm  =  i;
	}

	//
	if  (  bUseZOrder  )  {
		size  =  sizeof(  WM_zOrder  )  *  usMaxCnt;
		pMgr->m_var.pWmZOrders  =  (  WM_zOrder  *  )mymalloc(  size  );
		if  (  !pMgr->m_var.pWmZOrders  )  goto  errLabel;
		memset(  pMgr->m_var.pWmZOrders,  0,  size  );
		//
		pMgr->m_var.bUseZOrder  =  TRUE;
	}

	//
	pMgr->m_var.usCnt_validWmObjs  =  0;

	//  2016/05/24
	safeTcsnCpy(  qyGetDesByType1(  CONST_wmGrpTypeTable,  pGrp->m_var.iGrpType  ),  pGrp->m_var.name,  mycountof(  pGrp->m_var.name  )  );
	
	//
	if  (  syncMtCnt_start(  &pMgr->syncMtCnt,  pFuncs->isCliHelp.pf_getuiNextTranNo  )  )  {
		goto  errLabel;
	}

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		exitWmGrp(  pGrp  );
	}
	return  iErr;
}


//exitWallMemMgr应该在createTexturemgr和freeTextureMgr类似的地方调用. 因为在delete时也会有3d资源要释放。
int  exitWmGrp(  WM_grp_sync  *  pGrp  )
{
	int  iErr  =  -1;

	//
	D3D_context  *  pCtx  =  g_pD3dContext;


	WM_grp_sync  *  pMgr  = pGrp;
	
	//
	if  (  !pMgr  )  return  -1;

	CQySyncObj  syncObj;

	syncMtCnt_wLock_wait(  &pMgr->syncMtCnt,  0,  &syncObj,  NULL,  _T(  ""  )  );  

	if  (  !pMgr->m_var.usMaxCnt_wmInfoSyncs  )  {
		iErr  =  0;  goto  errLabel;
	}

	for  (  int  i  =  0;  i  <  pMgr->m_var.usMaxCnt_wmInfoSyncs;  i  ++  )  {
		WM_info_sync  *  pWallMemSync  =  &pMgr->m_var.pWmInfoSyncs[i];
		//
		d3dWallFrm_exit(  pCtx,  pWallMemSync  );
		//MACRO_safeDelete(  pWallMemSync->pWallMemObj  );
		if  (  wmInfoSync_freeWmObj(  pWallMemSync,  _T(  ""  )  )  )  {
			goto  errLabel;
		}
	}
	//
	MACRO_mysafeFree(  pMgr->m_var.pWmZOrders  );
	//
	MACRO_mysafeFree(  pMgr->m_var.pWmInfoSyncs  );
	pMgr->m_var.usMaxCnt_wmInfoSyncs  =  0;

	iErr  =  0;
errLabel:
	return  iErr;
	
}


//
int  emptyWmGrp(  WM_grp_sync  *  pGrp  )
{
	int  iErr  =  -1;

	//
	D3D_context  *  pCtx  =  g_pD3dContext;


	WM_grp_sync  *  pMgr  = pGrp;
	
	//
	if  (  !pMgr  )  return  -1;

	//
	for  (  int  i  =  0;  i  <  pMgr->m_var.usMaxCnt_wmInfoSyncs;  i  ++  )  {
		WM_info_sync  *  pWallMemSync  =  &pMgr->m_var.pWmInfoSyncs[i];
		//
		d3dWallFrm_exit(  pCtx,  pWallMemSync  );
		//MACRO_safeDelete(  pWallMemSync->pWallMemObj  );
		if  (  wmInfoSync_freeWmObj(  pWallMemSync,  _T(  ""  )  )  )  {
			goto  errLabel;
		}
	}

	iErr  =  0;
errLabel:
	return  iErr;
	
}


//
int  newIndex_wmInfoSync(  WM_grp_sync  *  pGrp  )
{
	int  iErr  =  -1;
	int  index_wm  =  0;
	//
	WM_info_sync  *  pWallMemInfoSync  =  NULL;
	
	//
	if  (  !pGrp  )  return  -1;

	//
	for  (  ;  index_wm  <  pGrp->m_var.usMaxCnt_wmInfoSyncs;  index_wm  ++  )  {					   
		 pWallMemInfoSync  =  &pGrp->m_var.pWmInfoSyncs[index_wm];						
		 if  (  wmInfoSync_getWmObj(  pWallMemInfoSync  )  )  {			  													
			 continue;						
		 }						
		 //			
		 break;				   
	}				   
	if  (  index_wm  ==  pGrp->m_var.usMaxCnt_wmInfoSyncs  )  {	
		showInfo_open0(  0,  0,  _T(  "newIndex_wmInfosync failed, cannot find a null pWallmemInfoSync.pWallMemObj"  )  );			  		   						  
		goto  errLabel;
	}

	iErr  =  0;
errLabel:
	return  iErr  ?  -1  :  index_wm;
}


