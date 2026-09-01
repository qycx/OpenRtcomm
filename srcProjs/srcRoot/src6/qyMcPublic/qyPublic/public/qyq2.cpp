

#include	"stdafx.h"

#include	"qyPrecomp.h"

#include	<windows.h>
#include	<assert.h>
#include	<tchar.h>
#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<MSAcm.h>
#endif
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyCommProc.h"
#include	"qmOpenCommon.h"

#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"				//  2009/05/13

#include	"qnmCommProc.h"
//#include	"qnmCommProc_mis.h"
//#include	"qyWmComm_is.h"


#if  0
 int  initQyQ2(  GENERIC_Q_CFG  *  pCfg,  RW_lock_param  *  pRwLockParam_syncFlg,  unsigned  short  usCnt_hEvents,  PF_qElemNew  pfQElemNew,  PF_qElemInit  pfQElemInit,  PF_qElemExit  pfQElemExit,  PF_qElemFree  pfQElemFree,  PF_qElemRemove  pfQElemRemove,  QY_Q2  *  pQ2  )
{
	return  initQyQ2(  pCfg,  pRwLockParam_syncFlg,  usCnt_hEvents,  NULL,  NULL,  pfQElemNew,  pfQElemInit,  pfQElemExit,  NULL,  pfQElemFree,  pfQElemRemove,  pQ2  );
}
#endif

 //  int  initQyQ2(  GENERIC_Q_CFG  *  pCfg,  RW_lock_param  *  pRwLockParam_syncFlg,  unsigned  short  usCnt_hEvents,  LPCTSTR  evt0Name,  PF_qElemNew  pfQElemNew,  PF_qElemInit  pfQElemInit,  PF_qElemExit  pfQElemExit,  PF_qElemFree  pfQElemFree,  PF_qElemRemove  pfQElemRemove,  QY_Q2  *  pQ2  )
 __declspec(  dllexport  )  int  initQyQ2(  GENERIC_Q_CFG  *  pCfg,  RW_lock_param  *  pRwLockParam_syncFlg,  unsigned  short  usCnt_hEvents,  LPCTSTR  evt0Name,  PF_qElemNewEx  pfQElemNewEx,  PF_qElemNew  pfQElemNew,  PF_qElemInit  pfQElemInit,  PF_qElemExit  pfQElemExit,  PF_qElemFreeEx  pfQElemFreeEx,  PF_qElemFree  pfQElemFree,  PF_qElemRemove  pfQElemRemove,  QY_Q2  *  pQ2  )
{
	if  (  !pCfg  ||  !pRwLockParam_syncFlg  )  return  -1;

	GENERIC_Q_cfgEx	cfgEx;
	memset(  &cfgEx,  0,  sizeof(  cfgEx  )  );
	memcpy(  &cfgEx.common,  pCfg,  sizeof(  cfgEx.common  )  );

	cfgEx.pfQElemNewEx  =  pfQElemNewEx;
	cfgEx.pfQElemNew  =  pfQElemNew;
	cfgEx.pfQElemInit  =  pfQElemInit;
	cfgEx.pfQElemExit  =  pfQElemExit;
	cfgEx.pfQElemFreeEx  =  pfQElemFreeEx;
	cfgEx.pfQElemFree  =  pfQElemFree;
	cfgEx.pfQElemRemove  =  pfQElemRemove;

	return  initQyQ2(  &cfgEx,  pRwLockParam_syncFlg,  usCnt_hEvents,  evt0Name,  pQ2  );
}

 //  2012/11/10
__declspec(  dllexport  )   int  initQyQ2(  GENERIC_Q_cfgEx  *  pCfgEx,  RW_lock_param  *  pRwLockParam_syncFlg,  unsigned  short  usCnt_hEvents,  LPCTSTR  evt0Name,  QY_Q2  *  pQ2  )
{
	int			iErr				=	-1;
	int			j;		 

	if  (  !pCfgEx  ||  !pRwLockParam_syncFlg  )  return  -1;

	GENERIC_Q_CFG	*	pCfg  =  &pCfgEx->common;

	lstrcpyn(  pQ2->cfg.name,  pCfg->name,  mycountof(  pQ2->cfg.name  )  );
	pQ2->cfg.uiMaxQNodes  =  pCfg->uiMaxQNodes;

	//
	pQ2->cfg.m_qType=pCfg->m_qType;

	//
	memcpy(  &pQ2->cfg.rwLockParam_syncFlg,  pRwLockParam_syncFlg,  sizeof(  pQ2->cfg.rwLockParam_syncFlg  )  );
#if  0
	_sntprintf(  pQ2->mutexName_syncFlg,  mycountof(  pQ2->mutexName_syncFlg  ),  _T(  "q2s-%s"  ),  pCfg->mutexName_prefix  );
	pQ2->hSema_syncFlg  =  CreateSemaphore(  0,  pQ2->cfg.rwLockParam_syncFlg.uiInitCnt_sema,  pQ2->cfg.rwLockParam_syncFlg.uiMaxCnt_sema,  NULL  );		 
	if  (  !pQ2->hSema_syncFlg  )  goto  errLabel;		 
#else
	pQ2->pRw_syncFlg  =  new  CMutexRW(  );
	if  (  !pQ2->pRw_syncFlg  )  goto  errLabel;
#endif

	//
	_sntprintf(  pQ2->mutexName_syncR,  mycountof(  pQ2->mutexName_syncR  ),  _T(  "q2_syncR%d-%d"  ), GetCurrentProcessId(),  getuiNextTranNo(NULL,0,NULL)  );

	//
	if  (  pCfg->uiMaxCnt_semaTrigger  )  {
		pQ2->cfg.uiMaxCnt_semaTrigger  =  pCfg->uiMaxCnt_semaTrigger;
		if  (  !(  pQ2->hSemaTrigger1  =  CreateSemaphore(  NULL,  0,  pQ2->cfg.uiMaxCnt_semaTrigger,  NULL  )  )  )  goto  errLabel;
		traceLogA(  "%S creates sema",  pCfg->name  );
	}


	if  (  usCnt_hEvents  )  {
		if  (  usCnt_hEvents  >  mycountof(  pQ2->hEvents  )  )  goto  errLabel;
		pQ2->cfg.usCnt_hEvents  =  usCnt_hEvents;
		if  ( evt0Name  )  lstrcpyn(  pQ2->cfg.evt0Name,  evt0Name,  mycountof(  pQ2->cfg.evt0Name  )  );  
		//
		pQ2->hEvents[0]  =  CreateEvent(  NULL,  FALSE,  FALSE,  (  pQ2->cfg.evt0Name[0]  ?  pQ2->cfg.evt0Name  :  NULL  )  );
		for  (  j  =  1;  j  <  pQ2->cfg.usCnt_hEvents;  j  ++  )  {
			 pQ2->hEvents[j] = CreateEvent( NULL, FALSE, FALSE, NULL );
			 if ( NULL == pQ2->hEvents[j] ) goto  errLabel;
		}
	}


	TCHAR		mutexName[64]		=	_T(  ""  );
	for  (  j  =  0;  j  <  mycountof(  pQ2->qs  );  j  ++  )  {
		 _sntprintf(  mutexName,  mycountof(  mutexName  ),  _T(  "%s-%u"  ),  pCfg->mutexName_prefix,  j  );		
		 if  (  initGenericQ(  mutexName,  mutexName,  0,  pCfg->uiMaxQNodes,  pCfgEx->pfQElemNewEx,  pCfgEx->pfQElemNew,  pCfgEx->pfQElemInit,  pCfgEx->pfQElemExit,  pCfgEx->pfQElemFreeEx,  pCfgEx->pfQElemFree,  pCfgEx->pf_QElemRemoveEx,  pCfgEx->pfQElemRemove,  &pQ2->qs[j]  )  )  goto  errLabel;		  
	}
	
#ifdef  __DEBUG__
		traceLog(  _T(  "initQyQ2, %s, %s"  ),  pQ2->cfg.name, pQ2->qs[0].cfg.mutexName_prefix  );
#endif

	iErr  =  0;
errLabel:

	if  (  iErr  )  exitQyQ2(  pQ2  );

	return iErr;
}

__declspec(  dllexport  )   int  exitQyQ2(  QY_Q2  *  pQ2  )
{
	int			j;

#ifdef  __DEBUG__
		traceLog(  _T(  "exitQyQ2 %s, %s"  ),  pQ2->cfg.name,  pQ2->qs[0].cfg.mutexName_prefix  );
#endif

	for  (  j  =  0;  j  <  mycountof(  pQ2->qs  );  j  ++  )  {
		 exitGenericQ(  &pQ2->qs[j]  );		 
	}
	
	for  (  j  =  0;  j  <  mycountof(  pQ2->hEvents  );  j  ++  )  {
		  if  (  pQ2->hEvents[j]  )  {
			  CloseHandle(  pQ2->hEvents[j]  );  pQ2->hEvents[j]  =  NULL;
		  }
	 }

	if  (  pQ2->hSemaTrigger1  )  {  
		CloseHandle(  pQ2->hSemaTrigger1  );  pQ2->hSemaTrigger1  =  NULL;  
	}

#if  0
	if  (  pQ2->hSema_syncFlg  )  {
		CloseHandle(  pQ2->hSema_syncFlg  );  pQ2->hSema_syncFlg  =  NULL;
	}
#else
	MACRO_safeDelete(  pQ2->pRw_syncFlg  );
#endif
	
	 return  0;
}

 __declspec(  dllexport  ) void  emptyQ2(  QY_Q2  *  pQ  )
 {
	 if  (  !pQ  )  return;
	 emptyGenericQ(  &pQ->qs[0]  );
	 emptyGenericQ(  &pQ->qs[1]  );
 }



 //
static BOOL  tmp_bRemoveCond_reduceQ2Nodes(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 if  (  !p0  )  return  false;
	 int  &cnt  =  *(  int  *  )p0;

	 if  (  cnt  )  return  false;
	 cnt  ++  ;
	 return  true;
 }
 
 //
 __declspec(  dllexport  )  void  reduceQ2Nodes(  int nLeft,  QY_Q2  *  pQ2,  LPCTSTR  hint  )
 {
	 if  (  nLeft  <  0  )  return;
	 if  (  !pQ2  )  return;

	 for  (  ;  ;  )  {
		  int  nQNodes  =  getQ2Nodes(  pQ2  );
		  if  (  nQNodes  <=  nLeft  )  break;
		  {
			  	CQyQ2Help		q2Help;
				GENERIC_Q  *  pQ_toGetMsg  =  q2Help.getQ_toGetMsg(  pQ2,  hint  );
				if  (  !pQ_toGetMsg  )  break;
				int  cnt  =  0;
				qRemoveMsg(  pQ_toGetMsg,  tmp_bRemoveCond_reduceQ2Nodes,  &cnt,  0  );
				continue;
		  }
		  //
		  continue;
	 }

	 return;
 }


 //
#if  0
 BOOL  isQ2Warning(  QY_Q2  *  pQ2,  unsigned  int  uiQNodes_warningInterval  )		//  判断是否队列的成员空闲空间〈uiQNodes_interval
 {
	 if  (  !pQ2  )  return  FALSE;
	 return  isQWarning(  pQ2->bFlag_toPostMsg_q1  ?  &pQ2->qs[1]  :  &pQ2->qs[0],  uiQNodes_warningInterval  );
 }

 BOOL  isQ2Empty(  QY_Q2  *  pQ2  )	//  因为只要判断pQ->front.pNext一个数值，所以，不需要使用同步手段。2008/03/21
{
	if  (  !pQ2  )  return  FALSE;
	return  (  isQEmpty(  &pQ2->qs[0]  )  &&  isQEmpty(  &pQ2->qs[1]  )  );
}

 int  getQ2Nodes_toPostMsg(  QY_Q2  *  pQ2  )
{
	if  (  !pQ2  )  return  -1;

	return  pQ2->bFlag_toPostMsg_q1  ?  pQ2->qs[1].uiQNodes  :  pQ2->qs[0].uiQNodes;
}

 int  getQ2Nodes_toGetMsg(  QY_Q2  *  pQ2  )
{
	if  (  !pQ2  )  return  -1;

	return  pQ2->bFlag_toPostMsg_q1  ?  pQ2->qs[0].uiQNodes  :  pQ2->qs[1].uiQNodes;
}
#endif

  //  这个mutexName_toAvoidTriggerTooHigh是专门在多线程的情况下用来防止多个线程同时进行调节trigger用的
 __declspec(  dllexport  )  int  q2AvoidTriggerTooHigh(  LPCTSTR  mutexName_toAvoidTriggerTooHigh,  QY_Q2  *  pQ  )
{
	if  (  !pQ  ||  !pQ->hSemaTrigger1  )  return  0;

	long  lPrevCnt_semaTrigger;	lPrevCnt_semaTrigger  =  pQ->lPrevCnt_semaTrigger;
	lPrevCnt_semaTrigger  =  min(  (  int  )pQ->cfg.uiMaxCnt_semaTrigger,  lPrevCnt_semaTrigger  );
	long	minlPrevCnt		=	max(  10,  pQ->cfg.uiMaxCnt_semaTrigger  /  10  );
	long	maxlPrevCnt		=	max(  50,  pQ->cfg.uiMaxCnt_semaTrigger  /  2  );  
	
	if  (  lPrevCnt_semaTrigger  >  minlPrevCnt  )  {
		CQySyncObj		syncObj;

		if  (  mutexName_toAvoidTriggerTooHigh  &&  mutexName_toAvoidTriggerTooHigh[0]  )  {
			if  (  syncObj.sync(  mutexName_toAvoidTriggerTooHigh,  0  )  )  return  0;
		}
	
		if  (  lPrevCnt_semaTrigger  >  maxlPrevCnt  )  {				//  要在这里用waitForSingleObject把计数降下来。否则，其他地方会因为计数过大，而触发出错变慢。
			int	i;
			i  =  lPrevCnt_semaTrigger  -  minlPrevCnt;
			i  =  min(  i,  50  );										//  一次最多50个，否则，容易时间太长
			for  (  ;  i;  i  --  )  {
				 WaitForSingleObject(  pQ->hSemaTrigger1,  0  );			
				 pQ->lPrevCnt_semaTrigger  --  ;				 		
			}			  			   
			}
		else  {  
			  WaitForSingleObject(  pQ->hSemaTrigger1,  0  );  pQ->lPrevCnt_semaTrigger  --  ;			
		}

	}

	return  0;
}

 __declspec(  dllexport  ) int  q2PostMsg(  Q_ELEM_T  *  pQElem,  unsigned  int  size,  QY_Q2  *  pQ2,  LPCTSTR  hint  )
 {
	 CQyQ2Help	q2Help;
	 return  qPostMsg(  pQElem,  size,  q2Help.getQ_toPostMsg(  pQ2  ),  hint  );
 }

 __declspec(  dllexport  )   int  q2PostMsgAndTrigger(  Q_ELEM_T  *  pQElem,  unsigned  int  size,  QY_Q2  *  pQ2,  LPCTSTR  hint  )
 {
	 CQyQ2Help	q2Help;
	 return  q2Help.qPostMsgAndTrigger(  pQElem,  size,  pQ2,  hint  );
 }

 __declspec(  dllexport  ) int  q2TriggerToProcess(  QY_Q2  *  pQ2  )
 {
 	 if  (  pQ2->hEvents[1]  )  SetEvent(  pQ2->hEvents[1]  );
	 return  0;
 }

//  2010/05/03
 __declspec(  dllexport  )  int  q2GetMsg(  QY_Q2  *  pQ2,  Q_ELEM_T  *  pQElem,  unsigned  int  *  puiSize,  LPCTSTR  hint  )
{
	CQyQ2Help		q2Help;
	return  qGetMsg(  q2Help.getQ_toGetMsg(  pQ2,hint  ),  pQElem,  puiSize  );
}

 //  2014/03/25
 __declspec(  dllexport  )  int  q2GetMsgPkg(  QY_Q2  *  pQ2,  void  *  pPkg,  unsigned  int  uiSize_pkg,  unsigned  int  *uiLens,  unsigned  int  *  pnLens,  LPCTSTR  hint  )
 {
	CQyQ2Help		q2Help;
	return  qGetMsgPkg(  q2Help.getQ_toGetMsg(  pQ2,hint  ),  pPkg,  uiSize_pkg,  uiLens,  pnLens  );
 }


 //  2014/04/10
 __declspec(  dllexport  )  int  q2GetMsgs(  QY_Q2  *  pQ2,  Q_ELEM_T  *  pQElems[],  unsigned  int  *puiSizes,  unsigned  int  *  pnQElems,  LPCTSTR  hint  )	
{
	CQyQ2Help		q2Help;
	return  qGetMsgs(  q2Help.getQ_toGetMsg(  pQ2,hint  ),  pQElems,  puiSizes,  pnQElems  );
 }

