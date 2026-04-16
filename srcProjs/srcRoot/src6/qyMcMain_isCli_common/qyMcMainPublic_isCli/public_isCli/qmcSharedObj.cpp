
#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyWnd.h"
#include	"qmcCmdProc.h"
//#include	"qmcVWall.h"
//#include	"dlgTalkPublic.h"




  //  2014/09/30
 QY_sharedObj_sync  *  getSharedObjSyncByIndex(  MC_VAR_common  *  pProcInfo,  int  index  )
{
	if  (  !pProcInfo  )  return  NULL;
	return  pProcInfo->getSharedObjSyncByIndex(  index  );
}


//
//
 QY_SHARED_OBJ  *  getSharedObjByIndex(  MC_VAR_common  *  pProcInfo,  int  index  )
{
#if  0

	if  (  !pProcInfo  )  return  NULL;
	if  (  !pProcInfo->pSharedObjInfos  )  return  NULL;
	if  (  index  <  0  ||  index  >  pProcInfo->cfg.usMaxCnt_pSharedObjs  )  return  NULL;

	QY_sharedObj_sync  *  pSharedObjInfos  =  (  QY_sharedObj_sync  *  )pProcInfo->pSharedObjInfos;

	return  &pSharedObjInfos[index].sharedObj;
#endif
	QY_sharedObj_sync  *  pSharedObjInfo  =  getSharedObjSyncByIndex(  pProcInfo,  index  );
	if  (  !pSharedObjInfo  )  return  NULL;
	//
	return  &pSharedObjInfo->sharedObj;
}


 //
 int  getSharedObjUsrIndex(  CCtxQmcTmpl  *  pProcInfo,  int  iTaskId,  int  index_sharedObj  )
 {
	 int  i;
	 
	 if  (  !iTaskId  )  return  -1;

	 QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  index_sharedObj  );
	 if  (  !pSharedObj  )  return  -1;
	 
	 for  (  i  =  0;  i  <  mycountof(  pSharedObj->usrs  );  i  ++  )  {
		 if  (  pSharedObj->usrs[i].iTaskId  ==  iTaskId  )  break;
	 }
	 if  (  i  ==  mycountof(  pSharedObj->usrs  )  )  return -1;
	 return  i;
 }


 
 CAP_procInfo_audioU  *  getCapAudioBySth(  MC_VAR_common  *  pProcInfo,  int  index,  unsigned  int  uiCapType  )
{
	BOOL							bRet				=	FALSE;

	if  (  !pProcInfo  )  return  NULL;

	//
	return  pProcInfo->getCapAudioBySth(  index,  uiCapType  );
}

 //  if  uiCapType is 0, don't need to check capType. and if uiCapType is not 0, ...
 CAP_procInfo_bmpU  *  getCapBmpBySth(  MC_VAR_common  *  pProcInfo,  int  index,  unsigned  int  uiCapType  )
{

	BOOL							bRet				=	FALSE;

	if  (  !pProcInfo  )  return  NULL;

	//
	return  pProcInfo->getCapBmpBySth(  index,  uiCapType  );
}

 //
  QM_SHM_CMD  *  getShmCmdByIndex(  QM_SHM_CMDS  *  pCmds,  int  iIndex  )
{
	 if  (  !pCmds  )  return  NULL;
	 if  (  iIndex  <  0  ||  iIndex  >=  mycountof(  pCmds->mems  )  )  return  NULL;
	 return  &pCmds->mems[iIndex];
}
