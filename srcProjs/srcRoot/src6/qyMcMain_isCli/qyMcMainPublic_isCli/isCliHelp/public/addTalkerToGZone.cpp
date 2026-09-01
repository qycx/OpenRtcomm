
#include "stdafx.h"

#include	<stdlib.h>
#include	<tchar.h>

//#include <d3dx9.h>

#include	"qyMcMainCommon.h"

#include	"isCliCorePublic.h"
//
#include	"ctxQmc.h"
#include	"funcsForIsCliHelp.h"
#include	"dlgTalkProc.h"


//
//  __declspec(  dllexport  )  int  addTalkerToGZone(  HWND  hDlgTalk,  int  iWndContentType,  QY_MESSENGER_ID  *  pIdInfo,  int  iParam_reserved,  int  *  piIndex_wall  )
 __declspec(  dllexport  )  int  addTalkerToGZone(  CTX_qm_thread  *  pCqt,  HWND  hDlgTalk,  int  iWndContentType,  QY_MESSENGER_ID  *  pIdInfo,  int  iParam_reserved,  int  *  piIndex_wall  )
{

	int				iErr		=	-1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	//
	int  iIndex_wall  =  0;
	
	//  2015/12/05
	BOOL  bModified  =  FALSE;

	//
	ZONE_objs  *  pVar  =  pProcInfo->pGZone_activeTalkers;
	if  (  !pVar  )  return  -1;

	if  (  !IsWindow(  hDlgTalk  )  )  return  -1;
	if  (  !pIdInfo  )  return  -1;
	if  (  !pIdInfo->ui64Id  ||  iParam_reserved  )  return  -1;

	//
	if  (  iWndContentType  !=  CONST_qyWndContentType_talker  )  {
		return  -1;
	}
	{
		CHelp_getDlgTalkVar  help_getDlgTalkVar;
		DLG_TALK_var  *  pm_var  =  NULL;
		//
		pm_var  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlgTalk  );
		if  (  !pm_var  )  return  -1;
		//
		if  (  !isTalkerShadowMgr(  pm_var->addr  )  )  {
			return  -1;
		}
	}

#if  0
	int				i;
	//  2015/12/04
	for  (  i  =  0;  i  <  mycountof(  pVar->mems  );  i  ++  )  {
		 ZONE_obj  *  pMem  =  &pVar->mems[i];
		 if  (  pMem->hWndWallMem  ==  hDlgTalk  )   break;
	}
	if  (  i  <  mycountof(  pVar->mems  )  )  {
		iErr =  0;  goto  errLabel;
	}



	//
	//  remove invalid mems
	chkZoneObjs(  pVar  );

	//
	for  (  i  =  0;  i  <  mycountof(  pVar->mems  );  i  ++  )  {
		if  (  !IsWindow(  pVar->mems[i].hWndWallMem  )  )  break;
	}
	if  (  i  ==  mycountof(  pVar->mems  )  )  goto  errLabel;

	ZONE_obj  *  pMem  =  &pVar->mems[i];
	pMem->hWndWallMem  =  hDlgTalk;
	pMem->idInfo.ui64Id  =  pIdInfo->ui64Id;
	pMem->iParam_reserved  =  iParam_reserved;
	pMem->index  =  i;
	//  2016/02/09
	pMem->waitForPreRender.bWait  =  TRUE;
	pMem->waitForPreRender.dwTickCnt_startToWait  =  GetTickCount(  );

	//
	bModified  =  TRUE;

	//
	if  (  bModified  )  {
		pVar->dwModifiedTickCnt_zoneObjs  =  GetTickCount(  );
	}
#endif

	//  2016/05/31
	if  (  addWndToZoneObjs(  pProcInfo,  pCqt,  hDlgTalk,  iWndContentType,  pIdInfo,  iParam_reserved,  pVar,  &iIndex_wall  )  )  {
		goto  errLabel;
	}


	//
	iErr  =  0;
errLabel:
	if  (  !iErr  )  {
		if  (  piIndex_wall  )  *piIndex_wall  =  iIndex_wall;
	}
	return  iErr;
}



//
__declspec(  dllexport  )  int  getVal_isTalkerInGZone(  HWND  hDlgTalk,  int  iWndContentType,  int  *  piIndex_wall,  BOOL  * pbInGZone  )
{

	int				iErr		=	-1;
	//
	BOOL  bInGZone  =  FALSE;
	//
	int				i;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	ZONE_objs  *  pVar  =  pProcInfo->pGZone_activeTalkers;
	if  (  !pVar  )  return  -1;

	if  (  !IsWindow(  hDlgTalk  )  )  return  -1;

	//
	if  (  iWndContentType  !=  CONST_qyWndContentType_talker  )  {
		return  -1;
	}


	//
	HWND  hMgr  =  hDlgTalk;
	{
		CHelp_getDlgTalkVar  help_getDlgTalkVar;
		DLG_TALK_var  *  pm_var  =  NULL;
		//
		pm_var  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlgTalk  );
		if  (  !pm_var  )  return  -1;
		//
		if  (  !isTalkerShadowMgr(  pm_var->addr  )  )  {
			TALKER_shadow  *  pShadowInfo   =  (  TALKER_shadow  *  )pm_var->pShadowInfo;
			if  (  !pShadowInfo  )  goto  errLabel;
			hMgr  =  pShadowInfo->hMgr;
		}
	}

	//
	for  (  i  =  0;  i  <  mycountof(  pVar->mems  );  i  ++  )  {
		ZONE_obj  *  pMem  =  &pVar->mems[i];
		if  (  !pMem->hWndWallMem  )  continue;
		if  (  pMem->hWndWallMem  ==  hMgr  )  break;
	}
	if  (  i  ==  mycountof(  pVar->mems  )  )  goto  errLabel;

	bInGZone  =  TRUE;

	iErr  =  0;

errLabel:
	if  (  !iErr  )  {
		if  (  piIndex_wall  )  *piIndex_wall  =  i;
		if  (  pbInGZone  )  *pbInGZone  =  bInGZone;
	}
	return  iErr;
}


//
 __declspec(  dllexport  )  BOOL  isTalkerInGZone(  HWND  hDlgTalk,  int  iWndContentType,  int  *  piIndex_wall  )
 {
	 BOOL  bInGZone  =  FALSE;
	 //
	 if  (  !getVal_isTalkerInGZone(  hDlgTalk,  iWndContentType,  piIndex_wall,  &bInGZone  )
		 &&  bInGZone  )
	 {
		 return  TRUE;
	 }
	 return  FALSE;

 }




