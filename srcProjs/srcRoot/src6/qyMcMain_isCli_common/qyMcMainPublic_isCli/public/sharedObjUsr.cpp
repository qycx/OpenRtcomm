
#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>


#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"

//#include	"qmcVideoCapture_isCli.h"
//
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

#include	"qmcTaskPublic.h"

#include	"qmcCfg.h"
#include	"imgFunc_open.h"
#include	"qmcFunc.h"






 int  getNewSharedObjUsrFunc(  MC_VAR_common  *  pProcInfo,  HWND  hWnd,  int  iIndex_sharedObj,  BOOL  bLocalAv,  int  *  piIndex_sharedObjUsr,  BOOL  *  pbFirstUsr  )
{
	int								iErr				=	-1;
	//MC_VAR_isCli				*		pProcInfo			=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	QY_MC					*		pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;//QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
	//
	int								index				=	iIndex_sharedObj;	//  0;
	//
	QY_sharedObj_sync		*		pSharedObjInfo		=	NULL;
	QY_SHARED_OBJ			*		pSharedObj			=	NULL;
	BOOL							bFirstUsr			=	FALSE;

	if  (  !IsWindow(  hWnd  )  )  return  -1;

	pSharedObjInfo  =  getSharedObjSyncByIndex(  pProcInfo,  index  );
	if  (  !pSharedObjInfo  )  return  -1;
	pSharedObj  =  &pSharedObjInfo->sharedObj;
	//
	if  (  pSharedObj->bUsed  )  {
		if  (  pSharedObj->bQuit  )  {
			showInfo_open0(  0,  0,  _T(  "getNewSharedObjUsrFunc failed, sharedObj.bQuit is true"  )  );
			showNotification_open(  0,  0,  0,  _T(  "getNewSharedObjUsrFunc failed, sharedObj.bQuit is true"  )  );
			return  -1;
		}
	}

	if  (  !pSharedObj->bUsed  )  {
		memset(  pSharedObj,  0,  sizeof(  pSharedObj[0]  )  );
		pSharedObj->uiTranNo  =  getuiNextTranNo(  0,  0,  0  );
		pSharedObj->bUsed  =  TRUE;

		//
		pSharedObj->pProcInfo  =  pProcInfo;					//  2015/10/15

		//
		pSharedObj->dwTickCnt_start  =  GetTickCount(  );		//  2011/08/01

		//
		pSharedObj->iIndex_curUsr  =  -1;						//  2010/09/07

		//  2014/09/30
		syncMtCnt_start(  &pSharedObjInfo->syncMtCnt,  getuiNextTranNo  );  

		//
		bFirstUsr  =  TRUE;
	}

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pSharedObj->usrs  );  i  ++  )  {
		 if  (  pSharedObj->usrs[i].hWnd_starter  ==  hWnd  )  break;
	}
	if  (  i  ==  mycountof(  pSharedObj->usrs  )  )  {
		for  (  i  =  0;  i  <  mycountof(  pSharedObj->usrs  );  i  ++  )  {
			 if  (  !IsWindow(  pSharedObj->usrs[i].hWnd_starter  )  )  break;
		}
		if  (  i  ==  mycountof(  pSharedObj->usrs  )  )  return  -1;
		//
		if  (  pQyMc->iCustomId  !=  CONST_qyCustomId_hzj  )  {
			//
			if  (  !bFirstUsr  )  {  //  2017/02/12
				showInfo_open0(  0,  0,  _T(  "getNewSharedObjUsrFunc failed, not first usr"  )  );
				return  -1;
			}
		//
		}
	}
	//
	SHARED_OBJ_USR	*	pSharedObjUsr	=	getSharedObjUsr(  pSharedObj,  i  );
	memset(  pSharedObjUsr,  0,  sizeof(  pSharedObjUsr[0]  )  );
	pSharedObjUsr->hWnd_starter  =  hWnd;

	//
	if  (  piIndex_sharedObjUsr  )  *piIndex_sharedObjUsr  =  i;
	if  (  pbFirstUsr  )  *pbFirstUsr  =  bFirstUsr;

	//
	iErr  =  0;

	return  iErr;	//  index;
}


 //
 int  getNewSharedObjUsr_localAv(  MC_VAR_common  *  pProcInfo,  HWND  hWnd,  int  *  piIndex_sharedObj,  int  *  piIndex_sharedObjUsr,  BOOL  *  pbFirstUsr  )
 {
	 if  (  !piIndex_sharedObj  ||  !piIndex_sharedObjUsr  )  return  -1;

	 int  iIndex_sharedObj_localAv  =  0;
	 BOOL  bLocalAv  =  TRUE;
	 if  (  getNewSharedObjUsrFunc(  pProcInfo,  hWnd,  iIndex_sharedObj_localAv,  bLocalAv,  piIndex_sharedObjUsr,  pbFirstUsr  )  )  return  -1;
	 //
	 *piIndex_sharedObj  =  iIndex_sharedObj_localAv;

	 return  0;
 }

 //
  int  getNewSharedObjUsr(  MC_VAR_common  *  pProcInfo,  HWND  hWnd,  int  iIndex_sharedObj,  int  *  piIndex_sharedObjUsr,  BOOL  *  pbFirstUsr  )
  {
	  BOOL  bLocalAv  =  FALSE;

	  return  getNewSharedObjUsrFunc(  pProcInfo,  hWnd,  iIndex_sharedObj,  bLocalAv,  piIndex_sharedObjUsr,  pbFirstUsr  );
  }





  //  2010/09/01
  int  freeSharedObjUsrFunc(  void  *  pMC_VAR_isCli,  int  index,  HWND  hWnd  )
{
	int								iErr				=	-1;

	//
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pMC_VAR_isCli;

	//
	/*
	if  (  index  !=  0  )  {
		traceLog(  (TCHAR*)_T(  "freeSharedObjUsr_localAv failed, index error"  )  );
		return  -1;
	}
	*/

	//  int								index				=	0;
	//  MC_VAR_isCli				*		pProcInfo			=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	QY_MC					*		pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;//QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
	//
	//QY_sharedObj_sync		*		pSharedObjInfos		=	NULL;
	QY_SHARED_OBJ			*		pSharedObj			=	NULL;

	if  (  !IsWindow(  hWnd  )  )  return  -1;

	//pSharedObjInfos  =  (  QY_sharedObj_sync  *  )pProcInfo->pSharedObjSyncs;
	//pSharedObj  =  &pSharedObjInfos[index].sharedObj;
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  index  );
	if  (  !pSharedObj  )  return  -1;

	//
	if  (  pSharedObj->bQuit  )  return  -1;

	if  (  !pSharedObj->bUsed  )  return  -1;
	
	int  i;
	for  (  i  =  0;  i  <  mycountof(  pSharedObj->usrs  );  i  ++  )  {
		 if  (  pSharedObj->usrs[i].hWnd_starter  ==  hWnd  )  {
			 memset(  &pSharedObj->usrs[i],  0,  sizeof(  pSharedObj->usrs[i]  )  );

			 if  (  pSharedObj->iIndex_curUsr  ==  i  )  pSharedObj->iIndex_curUsr  =  -1;		//  2010/09/07  
		 }
	}

	//  check if sharedObjUsr exists.
	for  (  i  =  0;  i  <  mycountof(  pSharedObj->usrs  );  i  ++  )  {
		 if  (  IsWindow(  pSharedObj->usrs[i].hWnd_starter  )  )  break;
	}
	if  (  i  ==  mycountof(  pSharedObj->usrs  )  )  {
		askSharedObjToStop(  pProcInfo,  pSharedObj,  pQyMc->gui.hMainWnd,  _T(  "freeSharedObjUsr_localAv"  )  );
	}

	//
	return  0;
 }


  //
#if  0
  int  freeSharedObjUsr_localAv(  void  *  pMC_VAR_isCli,  int  index,  HWND  hWnd  )
  {
	  BOOL  bLocalAv  =  TRUE;
	  return  freeSharedObjUsrFunc(  pMC_VAR_isCli,  index,  bLocalAv,  hWnd  );
  }
#endif

  //
  int  freeSharedObjUsr(  void  *  pMC_VAR_isCli,  int  index,  HWND  hWnd  )
  {
	  BOOL  bLocalAv  =  FALSE;
	  return  freeSharedObjUsrFunc(  pMC_VAR_isCli,  index,  hWnd  );
  }

 

 //  2011/03/16
 int  resetCurSharedObjUsrFunc(  void  *  pMC_VAR_isCli,  int  index_sharedObj,  BOOL  bLocalAv  )
{
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pMC_VAR_isCli;

	//MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	//
	QY_SHARED_OBJ	*	pSharedObj	=	getSharedObjByIndex(  pProcInfo,  index_sharedObj  );
	if  (  !pSharedObj  )  return  -1;

	HWND				hWnd_starter_old	=	NULL;
	SHARED_OBJ_USR	*	pSharedObjUsr	=	getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
	if  (  pSharedObjUsr  &&  IsWindow(  pSharedObjUsr->hWnd_starter  )  )  {
			QY_WMBUF_COMM	wmBuf;
			memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );

			wmBuf.uiType  =  CONST_qyWmParam_requestToSpeak;
			wmBuf.u.requestToSpeak.uiCmd  =  ID_stopSpeaking;
			SendMessage(  pSharedObjUsr->hWnd_starter,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
			//
			hWnd_starter_old  =  pSharedObjUsr->hWnd_starter;
	}

	pSharedObj->iIndex_curUsr  =  -1;

	if  (  IsWindow(  hWnd_starter_old  )  )  {
		//  InvalidateRect(  hWnd_starter_old,  NULL,  TRUE  );
		PostMessage(  hWnd_starter_old,  CONST_qyWm_postComm,  CONST_qyWmParam_curSharedObjUsrChanged_mgr,  0  );
	}

	return  0;
}


 //
 int  resetCurSharedObjUsr_localAv(  void  *  pMC_VAR_isCli,  int  index_sharedObj  )
 {
	 BOOL  bLocalAv  =  TRUE;
	 return  resetCurSharedObjUsrFunc(  pMC_VAR_isCli,  index_sharedObj,  bLocalAv  );
 }

 //
 int  resetCurSharedObjUsr(  void  *  pMC_VAR_isCli,  int  index_sharedObj  )
 {
	 BOOL  bLocalAv  =  FALSE;
	 return  resetCurSharedObjUsrFunc(  pMC_VAR_isCli,  index_sharedObj,  bLocalAv  );
 }

