// QnmDb.cpp: implementation of the CQnmDb class.
//
//////////////////////////////////////////////////////////////////////

#include	"stdafx.h"

#include	<tchar.h>

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#ifdef  __useMfc__
		 #include	<afxmt.h>
		 #include	<afxdb.h>
#endif
#include	<WinSock2.h>

#include	"qyCommon.h"


#include	"qyString.h"
#include	"qyDbCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"

#include	"qyCommProc.h"
#include	"qnmCommProc.h"

#include	"QnmDb.h"
#include	"qySyncObj.h"
#include	"qySyncCommProc.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#if  0
//  静态成员区  {
 unsigned  char		CQnmDb::m_ucbInited	=	0;
 QNM_DB_MEM			CQnmDb::m_dbMems[CONST_qnmMaxDbs];

 
 //
 QNM_DB_MEM		*	CQnmDb::m_g_dbMems  =  NULL;
 int				CQnmDb::m_g_iCnt_dbMems  =  0;
#endif


 //
 QNM_db_pool	*	g_pQnmDbPool	=	NULL;
 

 //
 int  CQnmDb::initDbPool(  )
{
	int  iErr  =  -1;

	 //  if  (  m_ucbInited  )  return  0;
	if  (  g_pQnmDbPool  )  return  0;
	 
	int  size  =  sizeof(  QNM_db_pool  );
	g_pQnmDbPool  =  (  QNM_db_pool  *  )mymalloc(  size  );
	if  (  !g_pQnmDbPool  )  goto  errLabel;
	memset(  g_pQnmDbPool,  0,  size  );

	g_pQnmDbPool->m_g_iCnt_dbMems  =  mycountof(  g_pQnmDbPool->m_dbMems  );

	 //  memset(  m_dbMems,  0,  sizeof(  m_dbMems  )  );
	 //  m_ucbInited  =  TRUE;

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 exitDbPool(  );
	 }

	 return  0;
}

 void  CQnmDb::exitDbPool(  )
{
	 int			i;
	 //  CDatabase	*	pDb		=	NULL;
	 void	*	pDb		=	NULL;

	 //  if  (  !m_ucbInited  )  return;
	 if  (  !g_pQnmDbPool  )  return;

	 for  (  i  =  0;  i  <  mycountof(  g_pQnmDbPool->m_dbMems  );  i  ++  )  {
		  if  (  !(  pDb  =  (  void  *  )g_pQnmDbPool->m_dbMems[i].pDb  )  )  continue;
		  //  qyCloseDb(  pDb  );  delete  pDb;
		  qyFreeDb(  &pDb  );
	 }

	 //  m_ucbInited  =  FALSE;
	 MACRO_safeFree(  g_pQnmDbPool  );

	 return;
}


 int  CQnmDb::makeDbPool(  LPCWSTR  connectStr,  unsigned  int  cnt,  int  iDsnIndex  )
{
	 int			iErr		=		-1;
	 unsigned  int	i;
	 unsigned  int	index		=		0;
	 //  CDatabase	*	pDb			=		NULL;
	 void		*	pDb			=		NULL;

#if  0
	 CMutex			mutex(  FALSE,  CString(  CONST_mutexName_qnmDb  )  );
	 if  (  !mutex.Lock(  )  )  return  -1;
#endif
	 CQySyncObj		syncObj;
	 if  (  syncObj.sync(  _T(  CONST_mutexName_qnmDb  )  )  )  return  -1;

	 for  (  i  =  0;  i  <  cnt;  i  ++  )  {
		  
		  //  取空闲的dbMems
		  for  (  ;  index  <  mycountof(  g_pQnmDbPool->m_dbMems  );  index  ++  )  {
			  if  (  !g_pQnmDbPool->m_dbMems[index].pDb  )  break;
		  }
		  if  (  index  ==  mycountof(  g_pQnmDbPool->m_dbMems  )  )  {
			  traceLog(  (TCHAR*)_T(  "dbPool已满，makeDbPool失败"    )  );  goto  errLabel;
		  }

		  //  pDb  =  new  CDatabase;
		  pDb  =  qyNewDb(  );
		  if  (  !pDb  )  goto  errLabel;
		  if  (  !bQyOpenDb(  connectStr,  pDb  )  )  {
			  traceLogA(  (char*)"打开数据库连接失败，makeDbPool失败"  );  goto  errLabel;
		  }

		  g_pQnmDbPool->m_dbMems[index].pDb  =  pDb;  pDb  =  NULL;
		  g_pQnmDbPool->m_dbMems[index].uiThreadId  =  GetCurrentThreadId(  );
		  g_pQnmDbPool->m_dbMems[index].iDsnIndex  =  iDsnIndex;					//  2006/12/22
		  g_pQnmDbPool->m_dbMems[index].iDbType  =  0;							//  暂时不赋值

	 }

	 iErr  =  0;

errLabel:

#if  0
	 mutex.Unlock(  );  
#endif

	 if  (  pDb  )  {
		 //  qyCloseDb(  pDb  );  delete  pDb;
		 qyFreeDb(  &pDb  );
	 }

	 return  iErr;

}


  int  CQnmDb::makeDbPool_myDb(  void  *  pDb,  unsigned  int  cnt,  int  iDsnIndex  )
{
	 int			iErr		=		-1;
	 unsigned  int	i;
	 unsigned  int	index		=		0;


#if  0
	 CMutex			mutex(  FALSE,  CString(  CONST_mutexName_qnmDb  )  );	 
	 if  (  !mutex.Lock(  )  )  return  -1;
#endif
	 CQySyncObj	syncObj;
	 if  (  syncObj.sync(  _T(  CONST_mutexName_qnmDb  )  )  )  return  -1;

	 for  (  i  =  0;  i  <  cnt;  i  ++  )  {
		  
		  //  取空闲的dbMems
		  for  (  ;  index  <  mycountof(  g_pQnmDbPool->m_dbMems  );  index  ++  )  {
			  if  (  !g_pQnmDbPool->m_dbMems[index].pDb  )  break;
		  }
		  if  (  index  ==  mycountof(  g_pQnmDbPool->m_dbMems  )  )  {
			  traceLogA(  (char*)"dbPool已满，makeDbPool失败"  );  goto  errLabel;
		  }

		  g_pQnmDbPool->m_dbMems[index].pDb  =  pDb;  
		  g_pQnmDbPool->m_dbMems[index].uiThreadId  =  GetCurrentThreadId(  );
		  g_pQnmDbPool->m_dbMems[index].iDsnIndex  =  iDsnIndex;					//  2006/12/22
		  g_pQnmDbPool->m_dbMems[index].iDbType  =  CONST_dbType_myDb;

	 }

	 iErr  =  0;

errLabel:

#if  0
	 mutex.Unlock(  );  
#endif


	 return  iErr;

}


 void  CQnmDb::freeDbPool(  int  iDsnIndex  )	//  2006/12/22, 这个函数用来卸载某个数据源时用的
{
	 int			i;

	 //  if  (  !m_ucbInited  )  return;
	 if  (  !g_pQnmDbPool  )  return;

	 for  (  i  =  0;  i  <  mycountof(  g_pQnmDbPool->m_dbMems  );  i  ++  )  {
		  if  (  g_pQnmDbPool->m_dbMems[i].iDsnIndex  !=  iDsnIndex  )  continue;
		  if  (  !g_pQnmDbPool->m_dbMems[i].pDb  )  continue;
		  if  (  g_pQnmDbPool->m_dbMems[i].iDbType  ==  CONST_dbType_myDb  )  {
			  //  不需要操作. 2012/07/14
			  ;  
			  }
		  else  {
			     //  CDatabase	*	pDb		=	NULL;
			     void  *  pDb  =  NULL;
				 pDb  =  (  void  *  )g_pQnmDbPool->m_dbMems[i].pDb;
				 //  qyCloseDb(  pDb  );  delete  pDb;
				 qyFreeDb(  &pDb  );
		  }
		  memset(  &g_pQnmDbPool->m_dbMems[i],  0,  sizeof(  g_pQnmDbPool->m_dbMems[i]  )  );
	 }

	 return;

}


 QNM_db_pool  *  CQnmDb::getDbPool(  )
{
	//  if  (  !m_ucbInited  )  return  NULL;
	if  (  !g_pQnmDbPool  )  return  NULL;

	//  if  (  !piCnt  )  return  NULL;
	
	//  *piCnt  =  mycountof(  g_pQnmDbPool->m_dbMems  );

	return  g_pQnmDbPool;	//  m_dbMems;
}

int  CQnmDb::useDbPool(  QNM_db_pool  *  pDbPool  )
{
	if  (  !pDbPool  )  return  -1;

	//  if  (  !g_dbMems  ||  iCnt  <=  0  )  return  -1;
	if  (  g_pQnmDbPool  )  return  -1;

	//  m_g_dbMems  =  g_dbMems;
	//  m_g_iCnt_dbMems  =  iCnt;
	g_pQnmDbPool  =  pDbPool;

	return  0;
}


//  }



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQnmDb::CQnmDb()
{
	m_pDbMem  =  NULL;

}

CQnmDb::~CQnmDb()
{
	if  (  !m_pDbMem  )  return;
#if  0
	CMutex			mutex(  FALSE,  CString(  CONST_mutexName_qnmDb  )  );
	if  (  !mutex.Lock(  )  )  {
		traceLogA(  "最严重警告：CQnmDb::~CQnmDb(  ) 中mutex.Lock failed"  );
		return;
	}
#endif
	CQySyncObj	syncObj;
	if  (  syncObj.sync(  _T(  CONST_mutexName_qnmDb  )  )  )  {
		traceLogA(  (char*)"最严重警告：CQnmDb::~CQnmDb(  ) 中mutex.Lock failed"  );
		return;
	}

	m_pDbMem->ucbUsed  =  FALSE;

#if  0
	mutex.Unlock(  );
#endif
}

	
 void  *  CQnmDb::getAvailableDb(  int  iDsnIndex  )
{
	 int			index	=	-1;

	 if  (  m_pDbMem  )  return  m_pDbMem->pDb;

	 //
	 //  if  (  !m_g_dbMems  ||  m_g_iCnt_dbMems  <=  0  )  return  NULL;
	 if  (  !g_pQnmDbPool  )  return  NULL;


	 //
#if  0
	 CMutex			mutex(  FALSE,  CString(  CONST_mutexName_qnmDb  )  );
	 if  (  !mutex.Lock(  )  )  return  NULL;
#endif
	 CQySyncObj	syncObj;
	 if  (  syncObj.sync(  _T(  CONST_mutexName_qnmDb  )  )  )  return  NULL;

	 for  (  index  =  0;  index  <  g_pQnmDbPool->m_g_iCnt_dbMems;  index  ++  )  {
		  if  (  !g_pQnmDbPool->m_dbMems[index].pDb  )  continue;
		  if  (  g_pQnmDbPool->m_dbMems[index].iDsnIndex  !=  iDsnIndex  )  continue;
		  //  if  (  m_dbMems[index].uiThreadId  !=  GetCurrentThreadId(  )  )  continue;
		  //  traceLogA(  "2007/05/09, CDatabase应该可以支持多线程的调用，只要有同步就可以了, 这里把对threadId的考虑暂时去掉了"  );
		  if  (  !g_pQnmDbPool->m_dbMems[index].ucbUsed  )  break;
	 }

	 if  (  index  <  g_pQnmDbPool->m_g_iCnt_dbMems  )  {
		 m_pDbMem  =  &g_pQnmDbPool->m_dbMems[index];  
		 m_pDbMem->ucbUsed  =  TRUE;
		 
		 #ifdef  __DEBUG__
		 		 //  qyShowInfo1(  CONST_qyShowType_qnmChking,  "",  "qyMc",  "",  "",  "CQnmDb::getAvailableDb %d",  index  );
		 #endif

	 }
	
//  errLabel:

#if  0
	 mutex.Unlock(  );
#endif
	 
	 if  (  !m_pDbMem  )  {
		 //
#ifdef  __DEBUG__
		 //
		 //traceLogA(  (char*)"CQnmDb::getAvailableDb failed, return  NULL."  );
#endif
	 }

	 return  m_pDbMem  ?  m_pDbMem->pDb  :  NULL;
}



 void  CQnmDb::showQnmDbInfo(  )
{
	 int	i	=	0;
	 //  for  (  i  =  0;  i  <  m_
}
