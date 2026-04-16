// QnmDb.h: interface for the CQnmDb class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QNMDB_H__BD4DA457_3231_43FB_B368_298FC6649CA0__INCLUDED_)
#define AFX_QNMDB_H__BD4DA457_3231_43FB_B368_298FC6649CA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000





#define		CONST_qnmMaxDbs				32	//  128
#define		CONST_mutexName_qnmDb		"qnmDbMutex"




typedef  struct  __qnmDbMem_t		{
				 void  *			pDb;
				 unsigned  char		ucbUsed;
				 //  int			iStatus;
				 unsigned  int		uiThreadId;
				 int				iDsnIndex;		//  2006/12/22
				 int				iDbType;		//  2012/07/14
}		 QNM_DB_MEM;


//  2013/07/28
typedef  struct  __qnmDbPool_t		{
				  QNM_DB_MEM		m_dbMems[CONST_qnmMaxDbs];
				  int				m_g_iCnt_dbMems;
 }		  QNM_db_pool;


//
class CQnmDb  
{


private:
#if  0
	static  unsigned  char		m_ucbInited;
	static  QNM_DB_MEM			m_dbMems[CONST_qnmMaxDbs];
#endif

public:
	static  int					initDbPool(  );
	static  int					makeDbPool(  LPCWSTR  connectStr,  unsigned  int  cnt,  int  iDsnIndex  );
	static  int					makeDbPool_myDb(  void  *  pDb,  unsigned  int  cnt,  int  iDsnIndex  );
	static  void				freeDbPool(  int  iDsnIndex  );
	static  void				exitDbPool(  );

private:
#if  0
	static	QNM_DB_MEM		*	m_g_dbMems;
	static  int					m_g_iCnt_dbMems;
#endif

public:

	static  QNM_db_pool  *  getDbPool(  );
	static  int  useDbPool(  QNM_db_pool  *  pDbPool  );

public:
	CQnmDb();
	virtual ~CQnmDb();

	QNM_DB_MEM	*	m_pDbMem;
	
	void  *		getAvailableDb(  int  iDsnIndex  );
	void		showQnmDbInfo(  );

};

#endif // !defined(AFX_QNMDB_H__BD4DA457_3231_43FB_B368_298FC6649CA0__INCLUDED_)

