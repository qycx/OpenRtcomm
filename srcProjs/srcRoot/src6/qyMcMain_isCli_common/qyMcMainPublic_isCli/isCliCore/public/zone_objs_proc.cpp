

#include "stdafx.h"

#include	<stdlib.h>
#include	<tchar.h>

//#include <d3dx9.h>

#include	"qyMcMainCommon.h"

#include	"isCliCoreCommon.h"
#include	"ctxQmc.h"
#include	"funcsForIsCliHelp.h"
#include	"dlgTalkProc.h"


//
__declspec(  dllexport  )  int  set_enlarged_gZone(  CCtxQmc  *  pProcInfo,  HWND  hWnd  )
{
	int  i;

	if  (  !pProcInfo  )  return  -1;

	ZONE_objs  *  pZoneObjs  =  pProcInfo->pGZone_activeTalkers;
	if  (  !pZoneObjs  )  return  -1;

	if  (  !hWnd  )  return  -1;

	for  (  i  =  0;  i  <  mycountof(  pZoneObjs->mems  );  i  ++  )  {
		 ZONE_obj  *  pMem  =  &pZoneObjs->mems[i];
		 if  (  pMem->hWndWallMem  ==  hWnd  )  break;
	}
	if  (  i  ==  mycountof(  pZoneObjs->mems  )  )  return  -1;
	pZoneObjs->iIndex_enlarged1  =  i;

	return  0;
}


//
__declspec(  dllexport  )  int  set_recentAvRecvd_gZone(  CCtxQmc  *  pProcInfo,  HWND  hWnd  )
{	
	int  i;

	if  (  !pProcInfo  )  return  -1;

	ZONE_objs  *  pZoneObjs  =  pProcInfo->pGZone_activeTalkers;
	if  (  !pZoneObjs  )  return  -1;

	if  (  !hWnd  )  return  -1;

	for  (  i  =  0;  i  <  mycountof(  pZoneObjs->mems  );  i  ++  )  {
		 ZONE_obj  *  pMem  =  &pZoneObjs->mems[i];
		 if  (  pMem->hWndWallMem  ==  hWnd  )  break;
	}
	if  (  i  ==  mycountof(  pZoneObjs->mems  )  )  {
		//  not valid
		showInfo_open0(  0,  _T(  "set_recentAvRecvd_gZone"  ),  _T(  "invalid hWnd"  )  );
		return  -1;
	}
	int  index  =  i;
	ZONE_obj  *  pZoneObj  =  &pZoneObjs->mems[index];

	//
	DWORD  dwTickCnt  =  GetTickCount(  );

	//
	pZoneObj->dwTickCnt_recent_avRecvd  =  dwTickCnt;

	
	//
	int  j;
	RECENT_avRecvd_mem  *  pMem;
	//
	for  (  j  =  0;  j  <  mycountof(  pZoneObjs->recentAvRecvd.mems  );   j  ++  )  {
		pMem  =  &pZoneObjs->recentAvRecvd.mems[j];
		if  (  pMem->hTalker  ==  hWnd  )  break;
	}
	if  (  j  <  mycountof(  pZoneObjs->recentAvRecvd.mems  )  )  {
		// already in
		return  0;
	}	
	//
	j  =  pZoneObjs->recentAvRecvd.uiCnt_recentAvRecvd  %  mycountof(  pZoneObjs->recentAvRecvd.mems  );
	pMem  =  &pZoneObjs->recentAvRecvd.mems[j];

	pMem->dwTickCnt_recent_avRecvd  =  dwTickCnt;
	pMem->hTalker  =  hWnd;
	pMem->iIndex_zoneObj  =  index;

	pZoneObjs->recentAvRecvd.uiCnt_recentAvRecvd  ++  ;
		
	return  0;
	
}


//  2016/06/03
__declspec(  dllexport  )  int  addWndToZoneObjs(  CCtxQmc  *  pProcInfo,  CTX_qm_thread  *  pCqt,  HWND  hWnd,  int  iWndContentType,  QY_MESSENGER_ID  *  pIdInfo1,  int  iParam_reserved,  ZONE_objs  *  pZoneObjs,  int  *  piIndex_wall  ) 
{

	int				iErr		=	-1;
	int				i;

	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	(  FUNCS_for_isCliHelp  *  )QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	
	//  2015/12/05
	BOOL  bModified  =  FALSE;

	//
	ZONE_objs  *  pVar  =  pZoneObjs;
	if  (  !pVar  )  return  -1;

	if  (  !IsWindow(  hWnd  )  )  return  -1;

	//
	if  (  iWndContentType  ==  CONST_qyWndContentType_talker  )  {
		if  (  !pIdInfo1  )  return  -1;
		if  (  !pIdInfo1->ui64Id  ||  iParam_reserved  )  return  -1;

	}
	

	//  2015/12/04
	for  (  i  =  0;  i  <  mycountof(  pVar->mems  );  i  ++  )  {
		 ZONE_obj  *  pMem  =  &pVar->mems[i];
		 if  (  pMem->hWndWallMem  ==  hWnd  )   break;
	}
	if  (  i  <  mycountof(  pVar->mems  )  )  {
		iErr =  0;  goto  errLabel;
	}



	//
	//  remove invalid mems
	chkZoneObjs(  pCqt,  pVar  );

	//
	for  (  i  =  0;  i  <  mycountof(  pVar->mems  );  i  ++  )  {
		if  (  !IsWindow(  pVar->mems[i].hWndWallMem  )  )  break;
	}
	if  (  i  ==  mycountof(  pVar->mems  )  )  goto  errLabel;

	ZONE_obj  *  pMem  =  &pVar->mems[i];
	pMem->hWndWallMem  =  hWnd;
	if  (  pIdInfo1  )  pMem->idInfo.ui64Id  =  pIdInfo1->ui64Id;
	pMem->iParam_reserved  =  iParam_reserved;
	pMem->index  =  i;
	//  2016/02/09
	pMem->waitForPreRender.bWait  =  TRUE;
	pMem->waitForPreRender.dwTickCnt_startToWait  =  GetTickCount(  );

	//
	bModified  =  TRUE;
		
	//
	if  (  bModified  )  {
		pVar->ts_zoneObjs.dwModifiedTickCnt  =  myGetTickCount(  pCqt  );
	}


	//
	iErr  =  0;
errLabel:
	if  (  !iErr  )  {
		if  (  piIndex_wall  )  *piIndex_wall  =  i;
	}
	return  iErr;
}






 //
 __declspec(  dllexport  )  int  removeTalkerFromGZone(  CCtxQmc  *  pProcInfo,  HWND  hDlgTalk,  int  iWndContentType  )
 {
	 if  (  !pProcInfo  )  return  -1;
	 QY_MC  *  pQyMc  =  (  QY_MC  *  )pProcInfo->pQyMc;
	 if  (  !pQyMc  )  return  -1;
	 //
	 CTX_qm_thread  *  pCqt  =  &pQyMc->gui.ctx_gui_thread;

	 return  removeWndFromZoneObjs(  pProcInfo,  pCqt,  hDlgTalk,  iWndContentType,  pProcInfo->pGZone_activeTalkers  );
 }

 //
  __declspec(  dllexport  )  int  removeWndFromZoneObjs(  CCtxQmc  *  pProcInfo,  CTX_qm_thread  *  pCqt,  HWND  hDlgTalk,  int  iWndContentType,  ZONE_objs  *  pZoneObjs  )
 {
	 int  iErr  =  -1;

	 if  (  !pProcInfo  )  return  -1;
	 int  i;
	 BOOL  bModified  =  FALSE;
	 
	 //
	 if  (  !hDlgTalk  )  return  -1;

	 //	
	 ZONE_objs  *  pVar  =  (  ZONE_objs  *  )pZoneObjs;	//  pProcInfo->pGZone_activeTalkers;	
	 if  (  !pVar  )  return  -1;

	 for  (  i  =  0;  i  <  mycountof(  pVar->mems  );  i  ++  )  {
		 ZONE_obj  *  pMem  =  &pVar->mems[i];
		 if  (  !pMem->hWndWallMem  )  continue;
		 //
		 if  (  pMem->hWndWallMem  ==  hDlgTalk  )  {
			 #ifdef  __DEBUG__
					 traceLog(  _T(  "removeTalkerFromGZone: mems[%d] removed"  ),  i  );
			 #endif
			 memset(  pMem,  0,  sizeof(  pMem[0]  )  );

			 //
			 bModified  =  TRUE;

			 //
			 break;
		 }
	}
	 	 
	 //
	if  (  bModified  )  {
		pVar->ts_zoneObjs.dwModifiedTickCnt  =  myGetTickCount(  pCqt  );
	}


	 iErr  =  0;
errLabel:
	 return  iErr;

 }



 //
 int  myCompare_recent_zoneObjs(  const  void  *  arg1,  const  void  *  arg2  )
 {
	 ZONE_obj  **  pp1  =  (  ZONE_obj  **  )arg1;
	 ZONE_obj  **  pp2  =  (  ZONE_obj  **  )arg2;

	 DWORD  dwTickCnt1  =  (  (  *pp1  )->dwTickCnt_recent_avRecvd  );
	 DWORD  dwTickCnt2  =  (  (  *pp2  )->dwTickCnt_recent_avRecvd  );

	 int  iVal;
	 if  (  dwTickCnt1  <  dwTickCnt2  )  iVal  =  -1;
	 else  if  (  dwTickCnt1  ==  dwTickCnt2  )  iVal  =  0;
	 else  iVal  =  1;

	 return  0  -  iVal;
 }


//
__declspec(  dllexport  )  int  chkZoneObjs(  CTX_qm_thread  *  pCqt,  ZONE_objs  *  pZoneObjs  )
{
	int  iErr  =  -1;
	int  i;
	BOOL  bModified  =  FALSE;
	ZONE_objs  *  pVar  =  pZoneObjs;

	if  (  !pVar  )  return  -1;

	for  (  i  =  0;  i  <  mycountof(  pVar->mems  );  i  ++  )  {
		 ZONE_obj  *  pMem  =  &pVar->mems[i];
		 if  (  !pMem->hWndWallMem  )  continue;
		 if  (  !IsWindow(  pMem->hWndWallMem  )  )  {
			 #ifdef  __DEBUG__
					 traceLog(  _T(  "addToGZone: mems[%d] is invalid, removed"  ),  i  );
			 #endif
			 memset(  pMem,  0,  sizeof(  pMem[0]  )  );

			 //
			 bModified  =  TRUE;
		 }
	}

	//
	//  2015/12/04	
	int  index;
	if  (  pZoneObjs->recentAvRecvd.uiCnt_recentAvRecvd  )  {
		int  cnt_recents  =  0;
		for  (  i  =  0;  i  <  mycountof(  pZoneObjs->recentAvRecvd.mems  );  i  ++  )  {
			 //
			 index  =  pZoneObjs->recentAvRecvd.uiCnt_recentAvRecvd  -  1  -  i;
			 index  =  index  %  mycountof(  pZoneObjs->recentAvRecvd.mems  );
			 //
			 RECENT_avRecvd_mem  *  pRecvdMem  =  &pZoneObjs->recentAvRecvd.mems[index];
			 //
			 if  (  pRecvdMem->hTalker  )  {
				 if  (  !isZoneObjIndexValid(  pRecvdMem->iIndex_zoneObj  )  )  {				 
					 memset(  pRecvdMem,  0,  sizeof(  pRecvdMem[0]  )  );
					}
				 else  {
				       ZONE_obj  *  pZoneObj  =  &pZoneObjs->mems[pRecvdMem->iIndex_zoneObj];
					   if  (  pZoneObj->hWndWallMem  !=  pRecvdMem->hTalker  )  {
						   memset(  pRecvdMem,  0,  sizeof(  pRecvdMem[0]  )  );
					   }
				   }
			 }
			 //
			 if  (  pRecvdMem->hTalker  )  cnt_recents  ++  ;
		}
		//
		if  (  cnt_recents  !=  mycountof(  pZoneObjs->recentAvRecvd.mems  )  )  {
			ZONE_obj  *  ppObjs[MAX_zoneObjs];
			for  (  i  =  0;  i  <  MAX_zoneObjs;  i  ++  )  {
				 ppObjs[i]  =  &pZoneObjs->mems[i];
			}
			qsort(  ppObjs,  MAX_zoneObjs,  sizeof(  ZONE_obj  **  ),  myCompare_recent_zoneObjs  );
			//
#if  0
			for  (  i  =  0;  i  <  MAX_zoneObjs;  i  ++  )  {
				traceLog(  _T(  "%d. dwTickCnt %dms"  ),  i,  ppObjs[i]->dwTickCnt_recent_avRecvd  );
			}
#endif
			//
			for  (  i  =  0;  i  <  MAX_zoneObjs;  i  ++  )  {
				 if  (  i  >  mycountof(  pZoneObjs->recentAvRecvd.mems  )  -  1  )  break;
				 RECENT_avRecvd_mem  *  pRecentMem  =  &pZoneObjs->recentAvRecvd.mems[i];
				 pRecentMem->iIndex_zoneObj  =  ppObjs[i]->index;
				 pRecentMem->hTalker  =  ppObjs[i]->hWndWallMem;
				 pRecentMem->dwTickCnt_recent_avRecvd  =  ppObjs[i]->dwTickCnt_recent_avRecvd;
			}
		}
		
	}



	//
	if  (  bModified  )  {
		pVar->ts_zoneObjs.dwModifiedTickCnt  =  myGetTickCount(  pCqt  );
	}

	iErr  =  0;
errLabel:
	return  iErr;
}


 
