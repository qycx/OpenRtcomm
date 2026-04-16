

#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<assert.h>

#include	<windows.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"commondefs.h"
#include	"qyCommon\\commonfunc.h"
#include	<tchar.h>
#include	"qyCommProc.h"
#include	"qySyncCommProc.h"
#include	"genericqueue.h"
#include	"qySharedQ.h"

#include	<assert.h>
#ifdef  __noMfc__
	#define  _ASSERT(  x  )
#else
	#include	<crtdbg.h>
#endif

#include	"mcSharedQ.h"
#include	"qyMcMainCommon.h"

//
CMcSharedQ::CMcSharedQ( )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CMcSharedQ::~CMcSharedQ()
{

}





#ifndef  __USE_qySharedQ__



//
BOOL  CMcSharedQ::bSetQInfo(  LPCTSTR  mutexName_sync,  unsigned  int  uiMaxCnt_sema,  unsigned  int  uiMilliSeconds_mutex_r,  unsigned  int  uiMilliSeconds_sema_r,  unsigned  int  uiMilliSeconds_mutex_w,  unsigned  int  uiMilliSeconds_sema_w  )
{
	return  TRUE;
}


int  CMcSharedQ::initQ(  GENERIC_Q_CFG  *  pCfg,  RW_lock_param pRwLockParam_sync, PF_qElemNewEx  pfQElemNewEx,  PF_qElemNew  pfQElemNew,  PF_qElemInit  pfQElemInit,  PF_qElemExit  pfQElemExit,  PF_qElemFreeEx  pfQElemFreeEx,  PF_qElemFree  pfQElemFree  )
{
	int  iErr  =  -1;

	memcpy(  &m_var.cfg,  pCfg,  sizeof(  m_var.cfg  )  );
	//
	m_var.pfQElemNewEx  =  pfQElemNewEx;
	m_var.pfQElemFreeEx  =  pfQElemFreeEx;
	//
	m_var.pfQElemNew = pfQElemNew;
	m_var.pfQElemFree = pfQElemFree;
	//
	m_var.pfQElemInit  =  pfQElemInit;
	m_var.pfQElemExit  =  pfQElemExit;
	
	//
		
	//	
	m_var.rwLockParam_sync = pRwLockParam_sync;
		
	//
	m_var.pRw_sync = new CMutexRW();
	
	//
	int  size  =  sizeof(  QMEM_mcTask  )  *  m_var.cfg.uiMaxQNodes;
	m_var.pMems  =  (  QMEM_mcTask  *  )mymalloc(  size  );
	if  (  !m_var.pMems  )  goto  errLabel;
	memset(  m_var.pMems,  0,  size  );

	iErr  =  0;

errLabel:

	return  iErr;
}

#if  0
void  qNodeFree(  GENERIC_Q  *  pQ,  Q_NODE *pQNode,  BOOL  bElemRemove  )
{
	 
	 if  (  !pQ  ||  !pQNode  )  return;

	 //  2007/04/17, qNodeFreeÒªÊÇÊÍ·ÅËùÓÐºóÐøµÄ½Úµã»áÔì³É¶Ô¶ÑÕ»²»Àû£¬ËùÒÔ¸ÄÎª½öÊÍ·ÅÒ»¸ö

	 if  (  pQNode->qElemMemory.m_pBuf  )  {
		 if  (  pQNode->ucbQElemInited  )  {
             if  (  pQ->pfQElemExit  )  (  pQ->pfQElemExit  )(  pQNode->qElemMemory.m_pBuf  );
			 pQNode->ucbQElemInited  =  FALSE;
		 }
		 if  (  bElemRemove  )  {	//  2009/12/08
			 if  (  pQ->pfqElemRemoveEx  )  (  pQ->pfqElemRemoveEx  )(  pQNode->qElemMemory.m_pBuf,  pQNode->size,  pQ->cfg.name  );	//  2012/11/10
			 else  {
				   if  (  pQ->pfQElemRemove  )  (  pQ->pfQElemRemove  )(  pQNode->qElemMemory.m_pBuf,  pQ->cfg.name  );
			 }
		 }
		 if  (  pQ->pfQElemFreeEx  )  (  *pQ->pfQElemFreeEx  )(  &pQNode->qElemMemory  );
		 else  {
			   if  (  pQ->pfQElemFree  )  (  *pQ->pfQElemFree )(  pQNode->qElemMemory.m_pBuf  );
		 }
	 }
	 free( pQNode );

	 return;

}

#endif
//
void  CMcSharedQ::qNodeFree(  MC_sharedQ_var  *  pQ,  QMEM_mcTask *pMem,  BOOL  bElemRemove  )
{
	if  (  pQ  !=  &m_var  )  return;
	QMEM_mcTask  *  pQNode  =  pMem;

	 if  (  pQNode->qElemMemory.m_pBuf  )  {
		 if  (  pQNode->ucbQElemInited  )  {
             if  (  pQ->pfQElemExit  )  (  pQ->pfQElemExit  )(  pQNode->qElemMemory.m_pBuf  );
			 pQNode->ucbQElemInited  =  FALSE;
		 }
		 if  (  bElemRemove  )  {	//  2009/12/08
			 if  (  pQ->pfqElemRemoveEx  )  (  pQ->pfqElemRemoveEx  )(  pQNode->qElemMemory.m_pBuf,  pQNode->size,  pQ->cfg.name  );	//  2012/11/10
			 else  {
				   if  (  pQ->pfQElemRemove  )  (  pQ->pfQElemRemove  )(  pQNode->qElemMemory.m_pBuf,  pQ->cfg.name  );
			 }
		 }
		 if  (  pQ->pfQElemFreeEx  )  (  *pQ->pfQElemFreeEx  )(  &pQNode->qElemMemory  );
		 else  {
			   if  (  pQ->pfQElemFree  )  (  *pQ->pfQElemFree )(  pQNode->qElemMemory.m_pBuf  );
		 }
		 pQNode->qElemMemory.m_pBuf  =  NULL;
	 }	 
	 //
	 pQNode->ucbQElemInited  =  FALSE;
	 pQNode->bNeedRemoved  =  FALSE;		
	 pQNode->bUsed  =  FALSE;
	 
	 //
	 TCHAR  tBuf[128];
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "mcSharedQ::qNodeFree %s"  ),  pQNode->tDesc  );
	 showInfo_open0(  0,  0,  tBuf  );

	 //
	 return;
}


//
int  CMcSharedQ::recalc_uiQNodes(  )
{
	int  iErr  =  -1;
	int  i;
	int  iQNodes  =  0;

	for  (  i  =  0;  i  <  m_var.cfg.uiMaxQNodes;  i  ++   )  {
		 QMEM_mcTask  *  pMem  =  &m_var.pMems[i];
		 //
		 if  (  !pMem->bUsed  )  continue;
		 //
		 iQNodes  ++  ;
	}

	if  (  m_var.uiQNodes  !=  iQNodes  )  {
		m_var.uiQNodes  =  iQNodes;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}


//
void  CMcSharedQ::exitQ(  )
{
	int  i;

	for  (  i  =  0;  i  <  m_var.cfg.uiMaxQNodes;  i  ++  )  {
		 QMEM_mcTask  *  pMem  =  &m_var.pMems[i];
		 if  (  !pMem->bUsed  )  continue;
		 {
			 CQySyncObj  syncObj;
			 TCHAR		mutexName[128]  =  _T(  ""  );

			 //
			 pMem->bNeedRemoved  =  TRUE;

			 //
			 if  (  getMutexName(  i,  mutexName,  mycountof(  mutexName  )  )  )  {
				 #ifdef  __DEBUG__
						 MACRO_qyAssert(  0,  _T(  "mcSharedQ: getMutexName"  )  );
				 #endif
				 continue;
			 }
			 /*
			 if  (  syncMtCnt_wLock_wait(  &pMem->syncMtCnt,  mutexName,  &syncObj,  NULL,  _T(  ""  )  )  )  {
				 #ifdef  __DEBUG__
						 MACRO_qyAssert(  0,  _T(  "mcSharedQ: getMutexName"  )  );
				 #endif
				 continue;
			 }
			 */
			 //
			 this->qNodeFree(  &m_var,  pMem,  TRUE  );
		 }
	}
	//
	this->recalc_uiQNodes();
	//
	if  (  isEmpty(  )  )  {
		MACRO_safeFree(  m_var.pMems  );
		//
		MACRO_safeDelete(m_var.pRw_sync);
	}

	return;
}
	

int  CMcSharedQ::qPostMsg(  Q_ELEM_T  *  pQElem,  unsigned  int  size  )
{
	int		iErr  =  -1;
	int  i;
	QMEM_mcTask  *  pQNode  =  NULL;
	MC_sharedQ_var  *  pQ  =  &m_var;
	int  iAllocType  =  0;

	//
	#ifdef  __DEBUG__
	int  iThreadId  =  GetCurrentThreadId();

	
	if  (  iThreadId  !=  m_var.dwThreadId_console  )  {
		#ifdef  __DEBUG__
				MACRO_qyAssert(  0,  _T(  "mcSharedQ: qPostMsg, threadId != mgr"  )  );
		#endif
		return  -1;
	}
#endif


	//
	{
		CQyRWLock rwLock;

		if(0!=rwLock.wLock(m_var.pRw_sync,m_var.rwLockParam_sync.uiMilliSeconds_sema_w)) return -1;

	//
	for  (  i  =  0;  i  <  m_var.cfg.uiMaxQNodes;  i  ++  )  {
		 pQNode  =  &m_var.pMems[i];
		 if  (  pQNode->bUsed  )  continue;
		 break;
	}
	if  (  i  ==  m_var.cfg.uiMaxQNodes  )  {
		showInfo_open0(  0,  0,  _T(  "mcSharedQ qPostMsg failed, full"  )  );
		return  CONST_qyRet_qFull;
	}

	//
	CQySyncObj  syncObj;
	TCHAR		mutexName[128];
	if  (  getMutexName(  i,  mutexName,  mycountof(  mutexName  )  )  )  return  -1;

	/*
	if  (  syncMtCnt_wLock_noWait(  &pQNode->syncMtCnt,  mutexName,  &syncObj,  NULL  )  )  {
		return  -1;
	}
	*/
	
	//
	pQNode->bUsed  =  TRUE;

	//
	_sntprintf(  pQNode->tDesc,  mycountof(  pQNode->tDesc  ),  _T(  "sharedQ.mems[%d]"  ),  i  );


	//
	if  (  pQ->pfQElemNewEx  )  {
		if  (  !(  pQ->pfQElemNewEx(  iAllocType,  size,  &pQNode->qElemMemory  )  )  )  goto  errLabel;
		}
	else  {
		  if  (  pQ->pfQElemNew  )  {			//  2007/08/15, Ôö¼Ó¶ÔpfQElemNewµÄ·Ç0µÄÐ£Ñé
			  if  (  !(  pQNode->qElemMemory.m_pBuf  =  (  char  *  )pQ->pfQElemNew(  size  )  )  )  goto  errLabel;
		  }
	}
	if  (  pQNode->qElemMemory.m_pBuf  &&  size  )  {
		memcpy(  pQNode->qElemMemory.m_pBuf,  pQElem,  size  );
		pQNode->size  =  size;
	}
	//
	if  (  pQ->pfQElemInit  &&  pQ->pfQElemInit(  pQNode->qElemMemory.m_pBuf  )  )  goto  errLabel;		
	pQNode->ucbQElemInited  =  TRUE;

	//
	//syncMtCnt_start(  &pQNode->syncMtCnt,  getuiNextTranNo  );


#ifdef  __DEBUG__		//  2009/12/12
		if  (  10  )  {
			if  (  size  ==  51742
				||  size  ==  51354  )  
			{
				traceLogA(  (char*)"qPostMsg: size %d",  size  );
			}
		}
#endif


	//pQ->uiQNodes  ++  ;
	this->recalc_uiQNodes(  );
	
	

	iErr  =  0;

errLabel:
	
	//
	if  (  iErr  )  {
		if  (  pQNode  )  qNodeFree(  pQ,  pQNode,  FALSE  );
	}

	}

	//  2015/09/10
	TCHAR  tBuf[128]  =  _T(  ""  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "mcSharedQ::qPostMsg %s, i %d"  ),  iErr  ?  _T(  "failed"  )  :  _T(  "ok"  ),  i  );
	showInfo_open0(  0,  0,  tBuf  );


	//
	return  iErr;
}
		
int  CMcSharedQ::qGetMsg(  Q_ELEM_T  *  pQElem,  unsigned  int  *puiSize  )
{
#ifdef  __DEBUG__
		MACRO_qyAssert(  0,  _T(  "mcSharedQ, qGetMsg"  )  );
#endif

	return  -1;
}

int  CMcSharedQ::qRemoveMsg(  PF_bEnumTask pf_bRemoveCond,  void  *  p0,  void  *  p1  )
{
	int  iErr  =  -1;
	int  i;  
	int  tmpbRet;
	bool bExists_needRemoved=false;



	//
	{
		CQyRWLock rwLock;

		if(0!=rwLock.rLock(m_var.pRw_sync,m_var.rwLockParam_sync.uiMilliSeconds_sema_r)) return -1;

	for  (  i  =  0;  i  <  m_var.cfg.uiMaxQNodes;  i  ++  )  {
		 QMEM_mcTask  *  pMem  =  &m_var.pMems[i];
		 if  (  !pMem->bUsed  )  continue;

		 //
		 if(pMem->bNeedRemoved)
		 {
			 bExists_needRemoved=true;
			 continue;
		 }

		 //
		 {
			 CQySyncCnt	syncCnt;

			 //if  (  syncMtCnt_rLock(  &pMem->syncMtCnt,  &syncCnt,  _T(  ""  )  )  )  continue;
			 //
			 tmpbRet  =  (  *  pf_bRemoveCond  )(  m_var.pQyMc,  p0,  p1,  (TASK_common*)pMem->qElemMemory.m_pBuf  );
			 if  (  !tmpbRet  )  continue;
		 }
		 //
		 {
			 pMem->bNeedRemoved  =  TRUE;
			 //
			 /*
			 CQySyncObj  syncObj;
			 TCHAR  mutexName[128]  =  _T(  ""  );
			 //
			 if  (  getMutexName(  i,  mutexName,  mycountof(  mutexName  )  )  )  continue;
			 //if  (  syncMtCnt_wLock_noWait(  &pMem->syncMtCnt,  mutexName,  &syncObj,  NULL  )  )  continue;
			 //
			 //qNodeFree(  &m_var,  pMem,  TRUE  );			 
			 */
			 bExists_needRemoved=true;
			 continue;
		 }
	}
	}

	//
	//this->recalc_uiQNodes(  );
	if(bExists_needRemoved){
		this->chkMsgs_toBeRemoved();
	}

	iErr  =  0;
errLabel:

	return  iErr;
}



int  CMcSharedQ::emptyQ(  )
{
	int  iErr  =  -1;
	int  i;  
	int  tmpbRet;

	#ifdef  __DEBUG__
	int  iThreadId  =  GetCurrentThreadId();

	
	if  (  iThreadId  !=  m_var.dwThreadId_console  )  {
		#ifdef  __DEBUG__
				MACRO_qyAssert(  0,  _T(  "mcSharedQ: emptyQ, threadId != mgr"  )  );
		#endif
		return -1;
	}
#endif



	{
		CQyRWLock rwLock;
		if(0!=rwLock.wLock(m_var.pRw_sync,m_var.rwLockParam_sync.uiMilliSeconds_sema_w)) return -1;

	for  (  i  =  0;  i  <  m_var.cfg.uiMaxQNodes;  i  ++  )  {
		 QMEM_mcTask  *  pMem  =  &m_var.pMems[i];
		 if  (  !pMem->bUsed  )  continue;
		 //
		 {
			 pMem->bNeedRemoved  =  TRUE;
			 //
			 CQySyncObj  syncObj;
			 TCHAR  mutexName[128]  =  _T(  ""  );
			 //
			 if  (  getMutexName(  i,  mutexName,  mycountof(  mutexName  )  )  )  continue;
			 //if  (  syncMtCnt_wLock_wait(  &pMem->syncMtCnt,  mutexName,  &syncObj,  NULL,  _T(  ""  )  )  )  continue;
			 //
			 qNodeFree(  &m_var,  pMem,  TRUE  );			 
		 }
	}
	//
	this->recalc_uiQNodes(  );
	}

	iErr  =  0;
errLabel:

	return iErr;
}



int  CMcSharedQ::qTraverse(  PF_enumTask pf_visit,  void  *  p0,  void  *  p1  )
{
		int  iErr  =  -1;
	int  i;  
	int  tmpiRet;

	//
	int  nNodes  =  m_var.uiQNodes;

	{
		CQyRWLock rwLock;

		if(0!=rwLock.rLock(m_var.pRw_sync,m_var.rwLockParam_sync.uiMilliSeconds_sema_r) )return -1;
	//
	for  (  i  =  0;  i  <  m_var.cfg.uiMaxQNodes  &&  nNodes;  i  ++  )  {
		 QMEM_mcTask  *  pMem  =  &m_var.pMems[i];
		 if  (  !pMem->bUsed  )  continue;
		 //
		 {
			 CQySyncCnt	syncCnt;

			 //if  (  syncMtCnt_rLock(  &pMem->syncMtCnt,  &syncCnt,  _T(  ""  )  )  )  continue;
			 //
			 if  (  !pMem->ucbQElemInited  ||  pMem->bNeedRemoved  )  continue;
			 //
			 nNodes  --  ;
			 //
			 tmpiRet  =  (  *  pf_visit  )(  m_var.pQyMc,  p0,  p1,  (TASK_common*)pMem->qElemMemory.m_pBuf  );
			 if  (  tmpiRet  )  {
				 iErr  =  tmpiRet;  goto  errLabel;
			 }
		 }
	}

	}

#ifdef  __DEBUG__
		if  (  nNodes  )  {
			int  ii;
			ii  =  0;
		}
#endif
	if  (  nNodes  )  {
		TCHAR  tBuf[128];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "sharedQ.qTraverse err, nNodes_left is %d"  ),  nNodes  );
		showInfo_open0(  0,  0,  tBuf  );
	}

	//
	iErr  =  0;
errLabel:

	return  iErr;
}


int  CMcSharedQ::qTraverse_mono(  PF_enumTask pf_visit,  void  *  p0,  void  *  p1  )
{
		int  iErr  =  -1;
	int  i;  
	int  tmpiRet;

	//
	int  nNodes  =  m_var.uiQNodes;

	{
		CQyRWLock rwLock;

		if(0!=rwLock.wLock(m_var.pRw_sync,m_var.rwLockParam_sync.uiMilliSeconds_sema_w) )return -1;
	//
	for  (  i  =  0;  i  <  m_var.cfg.uiMaxQNodes  &&  nNodes;  i  ++  )  {
		 QMEM_mcTask  *  pMem  =  &m_var.pMems[i];
		 if  (  !pMem->bUsed  )  continue;
		 //
		 {
			 CQySyncCnt	syncCnt;

			 //if  (  syncMtCnt_rLock(  &pMem->syncMtCnt,  &syncCnt,  _T(  ""  )  )  )  continue;
			 //
			 if  (  !pMem->ucbQElemInited  ||  pMem->bNeedRemoved  )  continue;
			 //
			 nNodes  --  ;
			 //
			 tmpiRet  =  (  *  pf_visit  )(  m_var.pQyMc,  p0,  p1,  (TASK_common*)pMem->qElemMemory.m_pBuf  );
			 if  (  tmpiRet  )  {
				 iErr  =  tmpiRet;  goto  errLabel;
			 }
		 }
	}

	}

#ifdef  __DEBUG__
		if  (  nNodes  )  {
			int  ii;
			ii  =  0;
		}
#endif
	if  (  nNodes  )  {
		TCHAR  tBuf[128];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "sharedQ.qTraverse err, nNodes_left is %d"  ),  nNodes  );
		showInfo_open0(  0,  0,  tBuf  );
	}

	//
	iErr  =  0;
errLabel:

	return  iErr;

	return  -1;
}

		
BOOL  CMcSharedQ::isFull(  )
{
	if  (  m_var.uiQNodes  >=  m_var.cfg.uiMaxQNodes  )  return  TRUE;
	return  FALSE;
}
	
BOOL  CMcSharedQ::isWarning(  unsigned  int  uiQNodes_warningInterval  )		//  判断是否队列的成员空闲空间〈uiQNodes_interval
{
	if  (  m_var.uiQNodes  +  uiQNodes_warningInterval  >=  m_var.cfg.uiMaxQNodes  )  return  TRUE; 

	return FALSE;
}


BOOL  CMcSharedQ::isEmpty(  )
{
	if  (  !m_var.uiQNodes  )  return  TRUE;

	return  FALSE;
}


int	 CMcSharedQ::chkMsgs_toBeRemoved(  )
{
	int  iErr  =  -1;
	int  i;


#ifdef  __DEBUG__
	int  iThreadId  =  GetCurrentThreadId();

	
	if  (  iThreadId  !=  m_var.dwThreadId_console  )  {
		#ifdef  __DEBUG__
				MACRO_qyAssert(  0,  _T(  "mcSharedQ: chkMsgs_toBeRemoved, threadId != mgr"  )  );
		#endif
		return  -1;
	}
#endif
	

	//
				
	for ( i=0;i<m_var.cfg.uiMaxQNodes;i++)    
	{
				QMEM_mcTask & pMem = m_var.pMems[i];
				if (!pMem.bUsed) continue;
				if (pMem.bNeedRemoved) break;
            
	}	
	if (i == m_var.cfg.uiMaxQNodes) return 0;



	//
	{
		CQyRWLock rwLock;
		if(0!=rwLock.wLock(m_var.pRw_sync,m_var.rwLockParam_sync.uiMilliSeconds_sema_w ) ) return -1;

	for  (  i  =  0;  i  <  m_var.cfg.uiMaxQNodes;  i  ++  )  {
		 QMEM_mcTask  *  pMem  =  &m_var.pMems[i];
		 if  (  !pMem->bUsed  )  continue;
		 //
		 if  (  pMem->ucbQElemInited
			 &&  !pMem->bNeedRemoved  
			 //&&  pMem->syncMtCnt.uiTranNo  
			 )
		 {
			 continue;
		 }
		 //
		 {
			 pMem->bNeedRemoved  =  TRUE;
			 //
			 CQySyncObj  syncObj;
			 TCHAR  mutexName[128]  =  _T(  ""  );
			 //
			 if  (  getMutexName(  i,  mutexName,  mycountof(  mutexName  )  )  )  continue;
			 //if  (  syncMtCnt_wLock_noWait(  &pMem->syncMtCnt,  mutexName,  &syncObj,  NULL  )  )  continue;
			 //
			 qNodeFree(  &m_var,  pMem,  TRUE  );			 
		 }
	}
	//
	this->recalc_uiQNodes(  );
	}

	iErr  =  0;
errLabel:
	return  iErr;

}



#endif



