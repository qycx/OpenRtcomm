

#ifndef  __syncMtCnt_h__
#define  __syncMtCnt_h__	//  {

#include	"qysyncCommProc.h"


//  2014/09/29
typedef  struct  __syncMtCnt_									{
				 //
				 unsigned  int									uiTranNo;	
				 
				 //
				 long											lCnt_used;
}		 SYNC_mt_cnt;


//
int  syncMtCnt_start(  SYNC_mt_cnt  *  pMtCnt,  PF_getuiNextTranNo  pf_getuiNextTranNo  );
//
int  syncMtCnt_rLock(  SYNC_mt_cnt  *  pMtCnt,  CQySyncCnt  *  psyncCnt,  LPCTSTR  hint  );

#ifdef  __DEBUG__
	//int  syncMtCnt_wLock_noWait(  SYNC_mt_cnt  *  pMtCnt,  LPCTSTR  mutexName,  unsigned  int  *  ptn  );
	//
	//int  syncMtCnt_wLock_wait(  SYNC_mt_cnt  *  pMtCnt,  LPCTSTR  mutexName,  unsigned  int  *  ptn_unused,  LPCTSTR  hint  );

#endif

//  2015/11/12
#define		CONST_mtxName_syncMtCnt_wLock		_T(  "syncMtCnt_wLock"  );

//
int  syncMtCnt_wLock_noWait(  SYNC_mt_cnt  *  pMtCnt,  LPCTSTR  mutexName,  CQySyncObj  *  pSyncObj,  unsigned  int  *  ptn  );
//
int  syncMtCnt_wLock_wait(  SYNC_mt_cnt  *  pMtCnt,  LPCTSTR  mutexName,  CQySyncObj  *  pSyncObj,  unsigned  int  *  ptn_unused,  LPCTSTR  hint  );
 
 


#endif  //  }


