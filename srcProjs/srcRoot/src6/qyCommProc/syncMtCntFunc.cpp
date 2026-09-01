
#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	<time.h>
#include	<stdlib.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyDefs_open.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCustom.h"
#include	"qyTCharCommProc.h"

#include	"tmpCeLib.h"
#include	"syncMtCnt.h"
#include	"qysynccommproc.h"


int  syncMtCnt_start(  SYNC_mt_cnt  *  pMtCnt,  PF_getuiNextTranNo  pf_getuiNextTranNo  )
{
	if  (  !pf_getuiNextTranNo  )  return  -1;

	pMtCnt->uiTranNo  =  pf_getuiNextTranNo(  0,  0,  0  );
	if  (  !pMtCnt->uiTranNo  )  pMtCnt->uiTranNo  =  pf_getuiNextTranNo(  0,  0,  0  );
	if  (  !pMtCnt->uiTranNo  )  return  -1;

	return  0;
}

int  syncMtCnt_rLock(  SYNC_mt_cnt  *  pMtCnt,  CQySyncCnt  *  psyncCnt,  LPCTSTR  hint  )
{ 
	int  iErr  =  -1;

	if  (  !pMtCnt  )  return  -1;
	if  (  !psyncCnt  )  return  -1;

	unsigned  int  tn_taskInfo  =  pMtCnt->uiTranNo;
	if  (  !tn_taskInfo  )  goto  errLabel;

	if  (  psyncCnt->sync(  &pMtCnt->lCnt_used,  hint  )  )  goto  errLabel;

	if  (  tn_taskInfo  !=  pMtCnt->uiTranNo  )  goto  errLabel;

	iErr  =  0;

errLabel:
	return  iErr;
}




 //  2015/08/31
 //
 int  tmpFunc_syncMtCnt_wLock(  SYNC_mt_cnt  *  pMtCnt  )
 {
	 CQySyncObj	syncObj;

	 //
	 if  (  !pMtCnt  )  return  -1;
	 //if  (  !ptn  )  return  -1;

	 //
	 pMtCnt->uiTranNo  =  0;
	 if  (  pMtCnt->lCnt_used  )  return  -1;
	 return  0;
}


 //  2015/08/31
 //
 int  syncMtCnt_wLock_noWait(  SYNC_mt_cnt  *  pMtCnt,  LPCTSTR  mutexName,  CQySyncObj  *  pSyncObj,  unsigned  int  *  ptn  )

 {
	 //CQySyncObj	syncObj;

	 //
	 if  (  !pMtCnt  )  return  -1;
	 if  (  !pSyncObj  )  return  -1;
	 //if  (  !ptn  )  return  -1;
	 
	 //
	 if  (  !mutexName  )  mutexName  =  CONST_mtxName_syncMtCnt_wLock;	//  _T(  "syncMtCnt_wLock"  );

	 if  (  pSyncObj->sync(  mutexName  )  )  return  -1;

	 //
	 if  (  ptn  )  {
		 *ptn  =  pMtCnt->uiTranNo;
	 }

#if  0
	 //
	 pMtCnt->uiTranNo  =  0;
	 if  (  pMtCnt->lCnt_used  )  return  -1;
	 return  0;
#endif

	 return  tmpFunc_syncMtCnt_wLock(  pMtCnt  );  
 }





 //
 int  syncMtCnt_wLock_wait(  SYNC_mt_cnt  *  pMtCnt,  LPCTSTR  mutexName,  CQySyncObj  *  pSyncObj,  unsigned  int  *  ptn_unused,  LPCTSTR  hint  )
 {
	 int  iErr  =  -1;

	 if  (  !pSyncObj  )  return  -1;

	 if  (  !hint  )  hint  =  _T(  ""  );


	 //
	 if  (  !mutexName  )  mutexName  =  CONST_mtxName_syncMtCnt_wLock;	//  _T(  "syncMtCnt_wLock"  );

	 if  (  pSyncObj->sync(  mutexName  )  )  return  -1;
	 

	//
	for  (  ;  ;  )  {
		 if  (  !tmpFunc_syncMtCnt_wLock(  pMtCnt  )  )  break;
		 Sleep(  50  );
		 //
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsCli"  ),  0,  _T(  "syncMt"  ),  _T(  ""  ),  _T(  "%s"  ),  hint  );
	}

	iErr  =  0;

	return  iErr;
 }