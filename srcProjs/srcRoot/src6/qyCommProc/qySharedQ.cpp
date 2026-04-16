
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



CQySharedQ::CQySharedQ(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

}

CQySharedQ::~CQySharedQ(  )
{
	if  (  m_var.bQInited  )  {
		exitGenericQ(  &m_q  );  m_var.bQInited  =  FALSE;
	}

	//  if  (  m_var.hSema_sync  )  CloseHandle(  m_var.hSema_sync  );
	MACRO_safeDelete(  m_var.pRw_sync  );
}


 BOOL  CQySharedQ::bSetQInfo(  LPCTSTR  mutexName_sync,  unsigned  int  uiMaxCnt_sema,  unsigned  int  uiMilliSeconds_mutex_r,  unsigned  int  uiMilliSeconds_sema_r,  unsigned  int  uiMilliSeconds_mutex_w,  unsigned  int  uiMilliSeconds_sema_w  )
{
	BOOL		bRet	=	FALSE;

	if  (  !mutexName_sync  ||  !uiMaxCnt_sema  )  return  FALSE;

	memset(  &m_var,  0,  sizeof(  m_var  )  );

	lstrcpyn(  m_var.cfg.mutexName_sync,  mutexName_sync,  mycountof(  m_var.cfg.mutexName_sync  )  );
	//
	m_var.cfg.uiMaxCnt_sema  =  uiMaxCnt_sema;
	//  m_var.cfg.uiInitCnt_sema  =  m_var.cfg.uiMaxCnt_sema  -  1;
	m_var.cfg.uiInitCnt_sema  =  m_var.cfg.uiMaxCnt_sema;				//  2008/10/21, 初始值和最大值应该是一样的。才能确保写锁把计数清为0
	m_var.cfg.uiMilliSeconds_mutex_r  =  uiMilliSeconds_mutex_r;
	m_var.cfg.uiMilliSeconds_sema_r  =  uiMilliSeconds_sema_r;
	m_var.cfg.uiMilliSeconds_mutex_w  =  uiMilliSeconds_mutex_w;
	m_var.cfg.uiMilliSeconds_sema_w  =  uiMilliSeconds_sema_w;

	bRet  =  TRUE;
//  errLabel:
	return  bRet;
}


 int  CQySharedQ::initQ(  GENERIC_Q_CFG  *  pCfg,  PF_qElemNewEx  pfQElemNewEx,  PF_qElemNew  pfQElemNew,  PF_qElemInit  pfQElemInit,  PF_qElemExit  pfQElemExit,  PF_qElemFreeEx  pfQElemFreeEx,  PF_qElemFree  pfQElemFree  )
{
	int				iErr	=	-1;

	if  (  m_var.bQInited  )  return  -1;

	if  (  m_var.cfg.uiInitCnt_sema  )  {
#if  0
        m_var.hSema_sync  =  CreateSemaphore(  0,  m_var.cfg.uiInitCnt_sema,  m_var.cfg.uiMaxCnt_sema,  NULL  );		 
		if  (  !m_var.hSema_sync  )  goto  errLabel;		 
#else
		m_var.pRw_sync  =  new  CMutexRW(  );
		if  (  !m_var.pRw_sync  )  goto  errLabel;
#endif
	}

	if  (  initGenericQ(  pCfg->name,  NULL,  pCfg->uiMaxCnt_semaTrigger,  pCfg->uiMaxQNodes,  pfQElemNewEx,  pfQElemNew,  pfQElemInit,  pfQElemExit,  pfQElemFreeEx,  pfQElemFree,  NULL,  &this->m_q  )  )  return  -1;
	m_var.bQInited  =  TRUE;

	iErr  =  0;
errLabel:
	return  iErr;
}

 void  CQySharedQ::exitQ(  )
{
	traceLogA(  (char*)"CQySharedQ::exitQ: %S enters",  m_q.cfg.name  );

	if  (  m_var.bQInited  )  {
		exitGenericQ(  &m_q  );  m_var.bQInited  =  FALSE;
	}
#if  0
	if  (  m_var.hSema_sync  )  {
		CloseHandle(  m_var.hSema_sync  );  m_var.hSema_sync  =  NULL;
	}
#else
	MACRO_safeDelete(  m_var.pRw_sync  );
#endif

	traceLogA(  (char*)"CQySharedQ::exitQ: %S leaves",  m_q.cfg.name  );
}


 int  CQySharedQ::qPostMsg(  Q_ELEM_T  *  pQElem,  unsigned  int  size  )
{
	CQyRWLock	lockObj;

	if  (  !m_var.bQInited  )  return  -1;

	#ifdef  __DEBUG__
			_ASSERT(  m_var.dwThreadId_gui  !=  GetCurrentThreadId(  )  );
	#endif

#if  0
	if  (  m_var.hSema_sync  )  {
        if  (  lockObj.wLock(  m_var.cfg.mutexName_sync,  m_var.cfg.uiMilliSeconds_mutex_w,  m_var.hSema_sync,  m_var.cfg.uiMilliSeconds_sema_w,  m_var.cfg.uiInitCnt_sema  )  )  return  -1;
	}
#else
	if  (  m_var.pRw_sync  )  {
        if  (  lockObj.wLock(  m_var.pRw_sync,  m_var.cfg.uiMilliSeconds_sema_w  )  )  return  -1;
	}
#endif

	return  ::qPostMsg(  pQElem,  size,  &m_q,  _T(  "CQySharedQ.qPostMsg"  )  );
}
		
 int  CQySharedQ::qGetMsg(  Q_ELEM_T  *  pQElem,  unsigned  int  *puiSize  )
{
	CQyRWLock	lockObj;

	if  (  !m_var.bQInited  )  return  -1;

	#ifdef  __DEBUG__
			_ASSERT(  m_var.dwThreadId_gui  !=  GetCurrentThreadId(  )  );
	#endif

#if  0
	if  (  m_var.hSema_sync  )  {	
		if  (  lockObj.wLock(  m_var.cfg.mutexName_sync,  m_var.cfg.uiMilliSeconds_mutex_w,  m_var.hSema_sync,  m_var.cfg.uiMilliSeconds_sema_w,  m_var.cfg.uiInitCnt_sema  )  )  return  -1;
	}
#else
	if  (  m_var.pRw_sync  )  {	
		if  (  lockObj.wLock(  m_var.pRw_sync,  m_var.cfg.uiMilliSeconds_sema_w  )  )  return  -1;
	}
#endif

	return  ::qGetMsg(  &m_q,  pQElem,  puiSize  );

}

 int  CQySharedQ::qRemoveMsg(  PF_bCommonHandler pf_bRemoveCond,  void  *  p0,  void  *  p1  )
{
	CQyRWLock	lockObj;

	if  (  !m_var.bQInited  )  return  -1;

	#ifdef  __DEBUG__
			_ASSERT(  m_var.dwThreadId_gui  !=  GetCurrentThreadId(  )  );
	#endif

#if  0
	if  (  m_var.hSema_sync  )  {
        if  (  lockObj.wLock(  m_var.cfg.mutexName_sync,  m_var.cfg.uiMilliSeconds_mutex_w,  m_var.hSema_sync,  m_var.cfg.uiMilliSeconds_sema_w,  m_var.cfg.uiInitCnt_sema  )  )  return  -1;
	}
#else
	if  (  m_var.pRw_sync  )  {
        if  (  lockObj.wLock(  m_var.pRw_sync,  m_var.cfg.uiMilliSeconds_sema_w  )  )  return  -1;
	}
#endif

	return  ::qRemoveMsg(  &m_q,  pf_bRemoveCond,  p0,  p1  );
}




 void  CQySharedQ::emptyQ(  )
{
	CQyRWLock	lockObj;

	if  (  !m_var.bQInited  )  return;


#if  0
	if  (  m_var.hSema_sync  )  {
        if  (  lockObj.wLock(  m_var.cfg.mutexName_sync,  m_var.cfg.uiMilliSeconds_mutex_w,  m_var.hSema_sync,  m_var.cfg.uiMilliSeconds_sema_w,  m_var.cfg.uiInitCnt_sema  )  )  return;
	}
#else
	if  (  m_var.pRw_sync  )  {
        if  (  lockObj.wLock(  m_var.pRw_sync,  m_var.cfg.uiMilliSeconds_sema_w  )  )  return;
	}
#endif

	emptyGenericQ(  &m_q  );

	return;
}

 int  CQySharedQ::qTraverse(  PF_commonHandler pf_visit,  void  *  p0,  void  *  p1  )
{
	CQyRWLock	lockObj;

	if  (  !m_var.bQInited  )  return  -1;

	#ifdef  __DEBUG__
	#endif

#if  0
	if  (  m_var.hSema_sync  )  {
        if  (  lockObj.rLock(  m_var.cfg.mutexName_sync,  m_var.cfg.uiMilliSeconds_mutex_r,  m_var.hSema_sync,  m_var.cfg.uiMilliSeconds_sema_r  )  )  return  -1;
	}
#else
	if  (  m_var.pRw_sync  )  {
        if  (  lockObj.rLock(  m_var.pRw_sync,  m_var.cfg.uiMilliSeconds_sema_r  )  )  return  -1;
	}
#endif

	return  ::qTraverse(  &m_q,  pf_visit,  p0,  p1  );
}


 //  在某些涉及资源初始化或清理等工作时，需要防止并发，所以，用写锁来独占
 int  CQySharedQ::qTraverse_mono(  PF_commonHandler pf_visit,  void  *  p0,  void  *  p1  )
{
	CQyRWLock	lockObj;

	if  (  !m_var.bQInited  )  return  -1;

#if  0
	if  (  m_var.hSema_sync  )  {
		if  (  lockObj.wLock(  m_var.cfg.mutexName_sync,  m_var.cfg.uiMilliSeconds_mutex_w,  m_var.hSema_sync,  m_var.cfg.uiMilliSeconds_sema_w,  m_var.cfg.uiInitCnt_sema  )  )  return  -1;
	}
#else
	if  (  m_var.pRw_sync  )  {
		if  (  lockObj.wLock(  m_var.pRw_sync,  m_var.cfg.uiMilliSeconds_sema_w  )  )  return  -1;
	}
#endif

	return  ::qTraverse(  &m_q,  pf_visit,  p0,  p1  );
}


BOOL  CQySharedQ::isFull(  )
{
	return  isQFull(  &m_q  );
}

BOOL  CQySharedQ::isWarning(  unsigned  int  uiQNodes_warningInterval  )		//  判断是否队列的成员空闲空间〈uiQNodes_interval
{
	return  isQWarning(  &m_q,  uiQNodes_warningInterval  );
}

BOOL  CQySharedQ::isEmpty(  )
{
	return  isQEmpty(  &m_q  );
}




