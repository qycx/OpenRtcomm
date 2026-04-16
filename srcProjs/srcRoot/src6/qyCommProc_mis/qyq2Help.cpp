

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


 //
 //
 //
CQyQ2Help::CQyQ2Help(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CQyQ2Help::~CQyQ2Help(  )
{
}


GENERIC_Q	*  CQyQ2Help::getQ_toPostMsg(  QY_Q2  *  pQ2  )
{
	if  (  !pQ2  )  return  NULL;
	if  (  m_var.pQ2  )  {
		if  (  m_var.pQ2  !=  pQ2  )  return  NULL;
		}
	else  
		m_var.pQ2  =  pQ2;

	if  (  m_var.pQ_toPostMsg  )  return  m_var.pQ_toPostMsg;
	
#if  0
	if  (  this->rLock(  pQ2->mutexName_syncFlg,  pQ2->cfg.rwLockParam_syncFlg.uiMilliSeconds_mutex_r,  pQ2->hSema_syncFlg,  pQ2->cfg.rwLockParam_syncFlg.uiMilliSeconds_sema_r  )  )  return  NULL;
#else
	if  (  this->rLock(  pQ2->pRw_syncFlg,  pQ2->cfg.rwLockParam_syncFlg.uiMilliSeconds_sema_r  )  )  return  NULL;
#endif

	m_var.pQ_toPostMsg  =  pQ2->bFlag_toPostMsg_q1  ?  &pQ2->qs[1]  :  &pQ2->qs[0];
	m_var.pQ_toGetMsg  =  pQ2->bFlag_toPostMsg_q1  ?  &pQ2->qs[0]  :  &pQ2->qs[1];

	return  m_var.pQ_toPostMsg;
}
		
GENERIC_Q	*  CQyQ2Help::getQ_toGetMsg(  QY_Q2  *  pQ2,  LPCTSTR  hint  )
{
	if  (  !pQ2  )  return  NULL;

	//
	if  (  hint ==  NULL  )  hint  =  _T(  ""  );

	//
	if  (  m_var.pQ2  )  {
		if  (  m_var.pQ2  !=  pQ2  )  return  NULL;
		}
	else  
		m_var.pQ2  =  pQ2;

	if  (  m_var.pQ_toGetMsg  )  return  m_var.pQ_toGetMsg;

	//
#if 10
	//
	TCHAR  tBuf[128];
	//
#ifdef  __DEBUG__
	//
#if 0
	_sntprintf(tBuf, mycountof(tBuf), _T("qyq2Help.getQ_toGetMsg failed, %s, %s"), pQ2->mutexName_syncR, hint);
#endif
	//
#endif

	//
	if (this->syncObj_syncR.sync(pQ2->mutexName_syncR,  0)) {
		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qyq2Help.getQ_toGetMsg failed, %s, %s"  ),  pQ2->mutexName_syncR,  hint  );
		if  (  pQ2->cfg.m_qType==CONST_qType_showInfo  )  {
			traceLog(  tBuf  );
		}
		else  {
			  tmp_showInfo_open_internal(  0,  _T(  ""  ),  tBuf  );
		}
		//
		return  NULL;
	}
#endif

	//
	GENERIC_Q	*	pQ_toGetMsg;
	GENERIC_Q	*	pQ_toPostMsg;
	if  (  pQ2->bFlag_toPostMsg_q1  )  {
		pQ_toGetMsg  =  &pQ2->qs[0];
		pQ_toPostMsg  =  &pQ2->qs[1];
		}
	else  {
		  pQ_toGetMsg  =  &pQ2->qs[1];		
		  pQ_toPostMsg  =  &pQ2->qs[0];
	}

	if  (  isQEmpty(  pQ_toGetMsg  )  )  {
		if  (  !isQEmpty(  pQ_toPostMsg  )  )  {
			//  try to switch outputQ
#if  0
			if  (  this->wLock(  pQ2->mutexName_syncFlg,  pQ2->cfg.rwLockParam_syncFlg.uiMilliSeconds_mutex_w,  pQ2->hSema_syncFlg,  pQ2->cfg.rwLockParam_syncFlg.uiMilliSeconds_sema_w,  pQ2->cfg.rwLockParam_syncFlg.uiInitCnt_sema  )  )  return  NULL;
#else
			if  (  this->wLock(  pQ2->pRw_syncFlg,  pQ2->cfg.rwLockParam_syncFlg.uiMilliSeconds_sema_w  )  )  return  NULL;
#endif
			pQ2->bFlag_toPostMsg_q1  =  !pQ2->bFlag_toPostMsg_q1;
			this->unlock(  );
		}
	}

	/*
#if  0
	if  (  this->rLock(  pQ2->mutexName_syncFlg,  pQ2->cfg.rwLockParam_syncFlg.uiMilliSeconds_mutex_r,  pQ2->hSema_syncFlg,  pQ2->cfg.rwLockParam_syncFlg.uiMilliSeconds_sema_r  )  )  return  NULL;
#else
	if  (  this->rLock(  pQ2->pRw_syncFlg,  pQ2->cfg.rwLockParam_syncFlg.uiMilliSeconds_sema_r  )  )  return  NULL;
#endif
	*/

	/*
	m_var.pQ_toPostMsg  =  pQ2->bFlag_toPostMsg_q1  ?  &pQ2->qs[1]  :  &pQ2->qs[0];
	m_var.pQ_toGetMsg  =  pQ2->bFlag_toPostMsg_q1  ?  &pQ2->qs[0]  :  &pQ2->qs[1];
	*/
	if  (  pQ2->bFlag_toPostMsg_q1  )  {
		m_var.pQ_toGetMsg  =  &pQ2->qs[0];
		m_var.pQ_toPostMsg  =  &pQ2->qs[1];
		}
	else  {
		  m_var.pQ_toGetMsg  =  &pQ2->qs[1];		
		  m_var.pQ_toPostMsg  =  &pQ2->qs[0];
	}

	return  m_var.pQ_toGetMsg;

}





 int  CQyQ2Help::qPostMsgAndTrigger(  Q_ELEM_T  *  pQElem,  unsigned  int  size,  QY_Q2  *  pQ2,  LPCTSTR  hint  )
{
	 int				tmpiRet			=	0;
	 unsigned  char		ucbTriggerErr	=	FALSE;

	 if  (  !pQ2  )  return  -1;

	 if  (  pQElem  &&  size  )  {
		 if  (  (  tmpiRet  =  qPostMsg(  pQElem,  size,  this->getQ_toPostMsg(  pQ2  ),  hint  )  )  )  {
			 traceLogA(  (char*)"qyQ2Help::qPostMsgAndTrigger: qPostMsg returns %d",  tmpiRet  );
		 }
	 }
	 if  (  pQ2->hSemaTrigger1  &&  !ReleaseSemaphore(  pQ2->hSemaTrigger1,  1,  &pQ2->lPrevCnt_semaTrigger  )  )  {
		 qyDisplayLastError(  (char*)"ReleaseSemaphore failed"  );
		 
		 ucbTriggerErr  =  TRUE;

		 //  traceLogA(  "%S qPostMsgAndTrigger err: uiQNodes %d, lPrevCnt_semaTrigger %d",  pQ2->cfg.name,  pQ->uiQNodes,  pQ2->lPrevCnt_semaTrigger  );
		 #ifdef  _UNICODE
				 //qyShowInfo_internal(  CONST_qyShowType_warning,  0,  "",  pQ2->cfg.name,  NULL,  NULL,  _T(  ""  ),  _T(  "qyQ2Help.qPostMsgAndTrigger failed: trigger err, lPrevCnt %d"  ),  pQ2->lPrevCnt_semaTrigger  );
		 #endif
		 }
	 else  {
		   #ifdef  __DEBUG__
				   /*
				   TCHAR	tBuf[255  +  1]	=	_T(  ""  );
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s qPostMsgAndTrigger : uiQNodes %d, lPrevCnt_semaTrigger %d\n"  ),  pQ->cfg.name,  pQ->uiQNodes,  pQ->lPrevCnt_semaTrigger  );
				   OutputDebugString(  tBuf  );
				   */
		   #endif
	 }
	 if  (  pQ2->hEvents[0]  )  {
		 SetEvent(  pQ2->hEvents[0]  );
	 }
	 
	 //  2008/11/21
	 if  (  ucbTriggerErr  !=  pQ2->ucbTriggerErr  )  {
		 pQ2->ucbTriggerErr  =  ucbTriggerErr;
	 }

	 return  tmpiRet;
}
