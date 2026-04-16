
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<assert.h>
#include	<tchar.h>
#include	<iphlpapi.h>
//  #include	<IPTypes.h>
#include	<stdlib.h>

#include	"qyCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qySyncCommProc.h"


//  #include	<lmshare.h>

//  #include	"qwmDynFunc.h"

#ifdef  __WINCE__
#else
	#include	<crtdbg.h>
#endif

//int  freeTmpMemoryIndex(  int  index  );


int  RW_lock_param_init(  RW_lock_param  * p  )
{
	  if  (  !p  )  return  -1;

	  //
	  RW_lock_param  &  rwLockParam  =  *p;

	  //	  	 
	  rwLockParam.uiMaxCnt_sema			=	CONST_uiInitCnt_sema_q2SyncFlg;
	  rwLockParam.uiInitCnt_sema			=	rwLockParam.uiMaxCnt_sema  -  1;
	  rwLockParam.uiMilliSeconds_mutex_r	=	10000;
	  rwLockParam.uiMilliSeconds_sema_r	=	10000;
	  rwLockParam.uiMilliSeconds_mutex_w	=	10000;
	  rwLockParam.uiMilliSeconds_sema_w	=	10000;


	  return  0;
}


 //
 //
 //

 void  qyExitProcess(  LPCTSTR  hint  )
{
	if  (  !hint  )  hint  =  _T(  "qyExitProcess called"  );

#ifdef  __DEBUG__
	MessageBox(  NULL,  hint,  _T(  "Serious error."  ),  MB_OK  |  MB_TASKMODAL  );
#endif
	//
	ExitProcess(  0  );
}

 //

#define		CONST_uiMilliSeconds_sema_r		10000

 CMutexRW::CMutexRW(  ):
		m_semReaders(  NULL  ),
		m_semWriters(  NULL  ),
		m_nReaders(  0  )  
{
	this->m_pEnv  =  NULL;
	this->m_bSupported_srw  =  FALSE;
	
	this->m_pEnv  =  g_pEnv;
#if  0
	QWM_DYN_LIB	*	pDynLib	=	NULL;
	if  (  m_pEnv  )  pDynLib  =  (  QWM_DYN_LIB  *  )(  (  QY_ENV  *  )m_pEnv  )->pDynLibs;
#endif
	/*
	if  (  pDynLib  
		&&  pDynLib->pInitializeSRWLock
			&&  pDynLib->pAcquireSRWLockShared
				&&  pDynLib->pReleaseSRWLockShared
					&&  pDynLib->pAcquireSRWLockExclusive
						&&  pDynLib->pReleaseSRWLockExclusive  )
	{
		this->m_bSupported_srw  =  TRUE;
	}
	*/

	if  (  this->m_bSupported_srw  )  {
		#if  0
				pDynLib->pInitializeSRWLock(  &this->m_srw  );
		#endif
		return;
	}

	//  initialize the Readers & Writers variables
	m_semReaders  =  ::CreateSemaphore(  NULL,  1,  1,  NULL  );
	m_semWriters  =  ::CreateSemaphore(  NULL,  1,  1,  NULL  );
	m_nReaders  =  0;

	if  (  m_semReaders  ==  NULL  ||  m_semWriters  ==  NULL  )  {
			LPVOID  lpMsgBuf;
			FormatMessage(  FORMAT_MESSAGE_ALLOCATE_BUFFER  |  
					FORMAT_MESSAGE_FROM_SYSTEM  |
					FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL,
					GetLastError(  ),
					MAKELANGID(  LANG_NEUTRAL,  SUBLANG_DEFAULT  ),  //  Default language
					(  LPTSTR  )  & lpMsgBuf,
					0,
					NULL
					);
			traceLogA(  (char*)"ERROR:CreateSemaphore:%s\n",  (  LPCTSTR  )lpMsgBuf  );
			LocalFree(  lpMsgBuf  );		
	}
}

 CMutexRW::~CMutexRW(  )
{
	if  (  this->m_bSupported_srw  )  {
		return;
	}
	
	if  (  m_semWriters  )  (  ::CloseHandle(  m_semWriters  )  );
	m_semWriters  =  NULL;
	if  (  m_semReaders  )  (  ::CloseHandle(  m_semReaders  )  );
	m_semReaders  =  NULL;
}


#if  0  //  2012/03/24
 int  CMutexRW::Lock_DataRead(  unsigned  int  uiMilliSeconds_sema  )  
{
		int		iErr		=	-1;

		if  (  this->m_bSupported_srw  )  {
			QWM_DYN_LIB	*	pDynLib	=	(  QWM_DYN_LIB  *  )m_pEnv->pDynLibs;
			#if  0
					pDynLib->pAcquireSRWLockShared(  &this->m_srw  );
			#endif
			return  0;
		}

		DWORD	dwRet		=	WAIT_TIMEOUT;
		BOOL	bWaited_r	=	FALSE;

		//  P(  semReaders  )
		dwRet  =  ::WaitForSingleObject(  m_semReaders,  CONST_uiMilliSeconds_sema_r  );
		if  (  dwRet  ==  WAIT_FAILED  ||  dwRet  ==  WAIT_TIMEOUT  )  goto  errLabel;
		assert(  dwRet ==  WAIT_OBJECT_0  );
		bWaited_r  =  TRUE;

		m_nReaders  ++;

		if  (  m_nReaders  ==  1  )
		{
			//  P(  semWriters  )
			dwRet  =  ::WaitForSingleObject(  m_semWriters, uiMilliSeconds_sema  );
			//  assert(  dwEvent  ==  WAIT_OBJECT_0  );
			if  (  dwRet  !=  WAIT_OBJECT_0  )  goto  errLabel;
		}

		iErr  =  0;

errLabel:
		
		//  V(  semReaders  )		
		if  (  bWaited_r  )  ::ReleaseSemaphore(  m_semReaders,  1,  NULL  );

		return  iErr;
}
#endif

 //  2012/03/24
 int  CMutexRW::Lock_DataRead(  unsigned  int  uiMilliSeconds_sema  )  
{
		int		iErr		=	-1;

		if  (  this->m_bSupported_srw  )  {
#if  0
			QWM_DYN_LIB	*	pDynLib	=	(  QWM_DYN_LIB  *  )(  (  QY_ENV  *  )m_pEnv  )->pDynLibs;
#endif
			#if  0
					pDynLib->pAcquireSRWLockShared(  &this->m_srw  );
			#endif
			return  0;
		}

		DWORD	dwRet		=	WAIT_TIMEOUT;
		BOOL	bWaited_r	=	FALSE;

		//  P(  semReaders  )
		dwRet  =  ::WaitForSingleObject(  m_semReaders,  CONST_uiMilliSeconds_sema_r  );
		if  (  dwRet  ==  WAIT_FAILED  ||  dwRet  ==  WAIT_TIMEOUT  )  goto  errLabel;
		assert(  dwRet ==  WAIT_OBJECT_0  );
		bWaited_r  =  TRUE;

		m_nReaders  ++;

		if  (  m_nReaders  ==  1  )
		{
			//  P(  semWriters  )
			dwRet  =  ::WaitForSingleObject(  m_semWriters, uiMilliSeconds_sema  );
			if  (  dwRet  ==  WAIT_FAILED  ||  dwRet  ==  WAIT_TIMEOUT  )  goto  errLabel;
			assert(  dwRet  ==  WAIT_OBJECT_0  );
			//  if  (  dwRet  !=  WAIT_OBJECT_0  )  goto  errLabel;
		}

		iErr  =  0;

errLabel:
		
		//  V(  semReaders  )		
		if  (  bWaited_r  )  {
			//
			if ( iErr !=0 ) {
				m_nReaders--;
			}
			//
			::ReleaseSemaphore(  m_semReaders,  1,  NULL  );
		}

		return  iErr;
}


 

 void  CMutexRW::Unlock_DataRead(  )  
{
		if  (  this->m_bSupported_srw  )  {
#if  0
			QWM_DYN_LIB	*	pDynLib	=	(  QWM_DYN_LIB  *  )(  (  QY_ENV  *  )m_pEnv  )->pDynLibs;
#endif
			#if  0
				pDynLib->pReleaseSRWLockShared(  &this->m_srw  );
			#endif
			return;
		}

		DWORD  dwEvent  =  WAIT_TIMEOUT;
		//  P(  semReaders  )
		dwEvent  =  ::WaitForSingleObject(  m_semReaders,  INFINITE  );
		assert(  dwEvent  ==  WAIT_OBJECT_0  );

		m_nReaders--;

		if  (  m_nReaders  ==  0  )
		{
			//  V(  semWriters  )
			(  ::ReleaseSemaphore(  m_semWriters,  1,  NULL  )  );
		}
		//  V(  semReaders  )
		(  ::ReleaseSemaphore(  m_semReaders,  1,  NULL  )  );
}

#if  0	//  2012/03/24
 int  CMutexRW::Lock_DataWrite(  unsigned  int  uiMilliSeconds_sema  )  
{
		int		iErr		=	-1;

		if  (  this->m_bSupported_srw  )  {
			QWM_DYN_LIB	*	pDynLib	=	(  QWM_DYN_LIB  *  )m_pEnv->pDynLibs;
			#if  0
				pDynLib->pAcquireSRWLockExclusive(  &this->m_srw  );
			#endif
			return  0;
		}

		DWORD	dwEvent		=  WAIT_TIMEOUT;
	
		//  P(  semWriters  )
		dwEvent  =  ::WaitForSingleObject(  m_semWriters,  uiMilliSeconds_sema  );
		//  assert(  dwEvent  ==  WAIT_OBJECT_0  );
		if  (  dwEvent  !=  WAIT_OBJECT_0  )  goto  errLabel;

		iErr  =  0;
errLabel:
		return  iErr;
}
#endif

 //  2012/03/24
 int  CMutexRW::Lock_DataWrite(  unsigned  int  uiMilliSeconds_sema  )  
{
		int		iErr		=	-1;

		if  (  this->m_bSupported_srw  )  {
#if  0
			QWM_DYN_LIB	*	pDynLib	=	(  QWM_DYN_LIB  *  )(  (  QY_ENV  *  )m_pEnv  )->pDynLibs;
#endif
			#if  0
				pDynLib->pAcquireSRWLockExclusive(  &this->m_srw  );
			#endif
			return  0;
		}

		DWORD	dwRet		=  WAIT_TIMEOUT;
	
		//  P(  semWriters  )
		dwRet  =  ::WaitForSingleObject(  m_semWriters,  uiMilliSeconds_sema  );
		if  (  dwRet  ==  WAIT_FAILED  ||  dwRet  ==  WAIT_TIMEOUT  )  goto  errLabel;
		assert(  dwRet  ==  WAIT_OBJECT_0  );
		//  if  (  dwEvent  !=  WAIT_OBJECT_0  )  goto  errLabel;

		iErr  =  0;
errLabel:
		return  iErr;
}

 void  CMutexRW::Unlock_DataWrite(  )
{
		if  (  this->m_bSupported_srw  )  {
#if  0
			QWM_DYN_LIB	*	pDynLib	=	(  QWM_DYN_LIB  *  )(  (  QY_ENV  *  )m_pEnv  )->pDynLibs;
#endif
			#if  0
				pDynLib->pReleaseSRWLockExclusive(  &this->m_srw  );
			#endif
			return;
		}

		// V(  semWriters  )
		(  ::ReleaseSemaphore(  m_semWriters,  1,  NULL  )  );
}


 ////////////////////////

 CQyRWLock::CQyRWLock(  )  
{  
	memset(  &m_var,  0,  sizeof(  m_var  )  );	  
}


 /*
 CQyRWLock::~CQyRWLock(  )  
{  
			long  lPrev	=	999;

			if  (  m_var.nWaited  )  {
				if  (  !m_var.hSema  )  {
					qyExitProcess(  _T(  "CQyRWLock failed, hSema is null."  )  );
					}
				else  {
		
					  //  ÓÃÐ´ËøµÄ,Ó¦¸ÃÈÃuiInitCnt_semaºÍuiMaxCnt_semaÒ»ÖÂ.
					  //  ÐèÒª½«semaµÄ¿ÉÓÃÊý»Ö¸´µ½Ô­À´µÄÖµ
					  if  (  !ReleaseSemaphore(  m_var.hSema,  m_var.nWaited,  &lPrev  )  )  {
						  traceLogA(  "CQyRWLock::~CQyRWLock: ReleaseSemaphore failed. ²»¿ÉÈÝÈÌ£¬³ÌÐòÁ¢¼´±ÀÀ£"  );	
						  #ifdef  UNICODE
								  qyShowInfo1(  CONST_qyShowType_warning,  0,  "",  _T(  "wLock"  ),  NULL,  NULL,  _T(  ""  ),  _T(  "failed, ReleaseSemaphore failed. 1"  )  );
						  #endif
						  qyExitProcess(  _T(  "CQyRWLock failed."  )  );
					  }
				}	
			}

			if  (  m_var.hMutex  )  cancelSyncQmObjQ(  m_var.hMutex  );  
}
*/
 CQyRWLock::~CQyRWLock(  )  
 {
	 unlock(  );
 }

 /*
 int  CQyRWLock::rLock(  LPCTSTR  mutexName,  unsigned  int  uiMilliSeconds_mutex,  HANDLE  hSema,  unsigned  int  uiMilliSeconds_sema  )  
{  
			int		iErr	=	-1;
			DWORD		dwRet	=	0;

			if  (  m_var.bLocked  )  goto  errLabel;
																								//  
			m_var.hSema  =  hSema;

			dwRet  =  WaitForSingleObject(  hSema,  uiMilliSeconds_sema  );
			if  (  dwRet  ==  WAIT_FAILED  ||  dwRet  ==  WAIT_TIMEOUT  )  goto  errLabel;
			m_var.nWaited  ++  ;


			m_var.bLocked  =  TRUE;

			iErr  =  0;
		errLabel:

			if  (  iErr  )  {
				traceLogA(  "rLock failed. mutexName %S",  mutexName  );
				#ifdef  UNICODE
						qyShowInfo1(  CONST_qyShowType_warning,  0,  "",  _T(  "rLock"  ),  NULL,  NULL,  _T(  ""  ),  _T(  "failed"  )  );
				#endif
			}

			return  iErr;
}

 int  CQyRWLock::wLock(  LPCTSTR  mutexName,  unsigned  int  uiMilliSeconds_mutex,  HANDLE  hSema,  unsigned  int  uiMilliSeconds_sema,  unsigned  int  uiInitCnt_sema  )  
{
			int				iErr	=	-1;
			unsigned  int	i		=	0;
			DWORD			dwRet	=	0;

			CQySyncObj		syncObj;

			#ifdef  __DEBUG__
					_ASSERT(  uiMilliSeconds_sema  >=  10000  );			//  Õâ¸öÐ´ËøÊ±¼äÓ¦¸Ã³¬¹ý10Ãë¡£2008/10/22
			#endif

			if  (  m_var.bLocked  )  goto  errLabel;

			//  m_var.hMutex  =  syncQmObjQ(  mutexName,  uiMilliSeconds_mutex  );  
			//  if  (  !m_var.hMutex  )  goto  errLabel;
			if  (  syncObj.sync(  mutexName,  uiMilliSeconds_mutex  )  )  goto  errLabel;
		
			m_var.hSema  =  hSema;								//  ÒòÎªÏ£ÍûÔÚCQyRWLockÎö¹¹Ê±£¬ÓÃReleaseSemaphoreÀ´½²¼ÆÊý»Ö¸´µ½×î´ó¿ÉÓÃÊý£¬ËùÒÔ£¬ÕâÀïÏÈ¸³Öµ¡£2008/10/22
			m_var.uiInitCnt_sema  =  uiInitCnt_sema;

			//  ÏÂÃæÒª°ÑsemaphoreµÄ¼ÇÊý¸ã³É0£¬ÕâÊÇµÈ´ýËùÓÐµÄ¶ÁËøÍË³ö
			for  (  i  =  0;  i  <  uiInitCnt_sema;  i  ++  )  {
				 //  WaitForSingleObject(  hSema,  INFINITE  );	//  ÕâÊÇÎªÁËÄÜÈÃËùÓÐµÄ²Ù×÷¶¼ÍË³ö£¬±ÜÃâÔÚÊÍ·Å¶ÓÁÐÊ±£¬³åÍ»		  		 
				 dwRet  =  WaitForSingleObject(  hSema,  uiMilliSeconds_sema  );	
				 if  (  dwRet  ==  WAIT_FAILED  ||  dwRet  ==  WAIT_TIMEOUT  )  goto  errLabel;	
				 m_var.nWaited  ++  ;
			}

			m_var.bLocked  =  TRUE;
			
			iErr  =  0;

		errLabel:

			if  (  iErr  )  {
				traceLogA(  "wLock failed. mutexName %S",  mutexName  );
				#ifdef  UNICODE
						qyShowInfo1(  CONST_qyShowType_warning,  0,  "",  _T(  "wLock"  ),  NULL,  NULL,  _T(  ""  ),  _T(  "failed"  )  );
				#endif
			}

			return  iErr;
}

 //  2009/05/10
 void  CQyRWLock::unlock(  )  
{  
	long  lPrev	=	999;

	if  (  m_var.nWaited  )  {
		if  (  !m_var.hSema  )  {
			qyExitProcess(  _T(  "CQyRWLock failed, hSema is null."  )  );
		}
		else  {
			
			  //  ÓÃÐ´ËøµÄ,Ó¦¸ÃÈÃuiInitCnt_semaºÍuiMaxCnt_semaÒ»ÖÂ.
			  //  ÐèÒª½«semaµÄ¿ÉÓÃÊý»Ö¸´µ½Ô­À´µÄÖµ
			  if  (  !ReleaseSemaphore(  m_var.hSema,  m_var.nWaited,  &lPrev  )  )  {
				  traceLogA(  "CQyRWLock::~CQyRWLock: ReleaseSemaphore failed. ²»¿ÉÈÝÈÌ£¬³ÌÐòÁ¢¼´±ÀÀ£"  );	
				  #ifdef  UNICODE
						  qyShowInfo1(  CONST_qyShowType_warning,  0,  "",  _T(  "wLock"  ),  NULL,  NULL,  _T(  ""  ),  _T(  "failed, ReleaseSemaphore failed. 1"  )  );
				  #endif
				  qyExitProcess(  _T(  "CQyRWLock failed."  )  );
			  }
		}	
	}

	//  if  (  m_var.hMutex  )  cancelSyncQmObjQ(  m_var.hMutex  );  

	memset(  &m_var,  0,  sizeof(  m_var  )  );

	return;
}


*/





 int  CQyRWLock::rLock(  CMutexRW  *  p,  unsigned  int  uiMilliSeconds_sema  )
{
	int			iErr	=	-1;

	if  (  !p  )  return  -1;
	if  (  m_var.m_bIsLocked  )  return  -1;
	
	if  (  p->Lock_DataRead(  uiMilliSeconds_sema  )  )  goto  errLabel;

	m_var.m_pMutexRW  =  p;
	m_var.m_bIsLocked  =  true;
	m_var.m_bIsRlocked  =  true;

	iErr  =  0;
errLabel:
	return  iErr;
}


 int  CQyRWLock::wLock(  CMutexRW  *  p,  unsigned  int  uiMilliSeconds_sema  )
{
	int			iErr	=	-1;

	if  (  !p  )  return  -1;
	if  (  m_var.m_bIsLocked  )  return  -1;
	
	if  (  p->Lock_DataWrite(  uiMilliSeconds_sema  )  )  goto  errLabel;

	m_var.m_pMutexRW  =  p;
	m_var.m_bIsLocked  =  true;

	iErr  =  0;
errLabel:
	return  iErr;
}


 void  CQyRWLock::unlock(  )  
 {
	 if  (  m_var.m_bIsLocked  )  {
		 if  (  m_var.m_bIsRlocked  )  m_var.m_pMutexRW->Unlock_DataRead(  );
		 else  m_var.m_pMutexRW->Unlock_DataWrite(  );
		 
		 memset(  &m_var,  0,  sizeof(  m_var  )  );
	 }
	 return;
 }


 ////////////////////////
 
#ifdef  __DEBUG__

 int  printShmMemory(  int  iAllocType,  LPCTSTR  hint,  BOOL  bDetail  )
{
#if  0
	MC_SHM_MEMORY	*	pShmMemory	=	(  MC_SHM_MEMORY  *  )g_pEnv->pShmMemory;
	if  (  !pShmMemory  )  return  -1;
	if  (  !hint  )  hint  =  _T(  ""  );

	traceLog(  _T(  "printShmMemory starts ... %s"  ),  hint  );


	int  index;
	int  i;
	for  (  index  =  0;  index  <  mycountof(  pShmMemory->mems  );  index  ++  )  {
		 if  (  iAllocType  )  {
			 if  (  index  !=  iAllocType  )  continue;
		 }

		 MC_SHM_memoryMem	*	pMem  =  &pShmMemory->mems[index];
		 int					nUsed	=	0;

		 for  (  i  =  0;  i  <  pMem->usMaxCnt;  i  ++  )  {
			  if  (  pMem->ucbUseds[i]  )  {
				  nUsed  ++  ;
				  if  (  bDetail  )  {
					  traceLogA(  "\tshmMemory[%d,%d] used",  index,  i  );
				  }
			  }
		 }

		 traceLog(  _T(  "iAllocType %d, nUsed %d, max %d"  ),  iAllocType,  nUsed,  pMem->usMaxCnt  );
	}

	traceLogA(  "printShmMemory ends."  );
#endif

	return  0;
}

#endif

