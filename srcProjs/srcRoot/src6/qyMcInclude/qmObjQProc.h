
#ifndef  __QMOBJQPROC_H__
#define	 __QMOBJQPROC_H__	//  {


//  #define		MACRO_qmObjQMem_common					int	iType;	void  *  pObjInfo;				//  节点包含指向详细信息的指针


//  此节点为队列中的指向的详细PC信息
typedef  struct  __qMemPc_t								{
		
				 char									mac[CONST_qyMacLen  +  1];
				 unsigned  long							ulIp;
				 long									lLastCommTime;
				 //
				 long									lRefreshedLastCommTime;	//  被刷新入数据库的时间
				 //
				 long									lRefreshedTime;			//  队列策略刷新的时间
				 QNM_CMDPARAM_getOpCmd					getOpCmd;
				 char									reserved[128];			//  其他策略				
}		 QMEM_PC;


//////////////
//






typedef  struct	 __qmObjQMem_t							{
				 int									iType;	
				 void								*	pQMemObj;				//  节点包含指向详细信息的指针
}		 QM_OBJQ_MEM;


#define		CONST_objQType_null							0
#define		CONST_objQType_netMc						1
#define		CONST_objQType_mis							2
#define		CONST_objQType_misClient					3						//  对在messenger的管理端和客户端由于使用的不同，存储方式也不同。故用不同的类型来区分


//
#define		CONST_qmObjQMaxCnt_misClient				10000					//  对isClient, 可以管理的成员最高在10000个, 2007/08/15, 暂时这样规定。


//
typedef  int  (  __cdecl  *  PF_compare_qmObjQ  )( const void * pKey, const void * pMemParam);	//  排序用的比较函数 
typedef  int  (  *  PF_fillQmObjMemInfo  )(  void  *  pServiceInfo,  void  *  pQParam,  void  *  pDb,  int  iDbType,  void  *  pClient,  QM_OBJQ_MEM  *  pMem  );


typedef  struct  __qmObjQ_t								{
				 int									iType;
				 TCHAR									name[32  +  1];			//  名称，有利于调试，2007/06/03
				 unsigned  int							maxCnt;					//  最多容纳个数；这同时意味着分配的空间大小=maxCnt  *  sizeof(  QM_OBJQ_MEMU  )
				 unsigned  int							cnt;					//  有效个数
				 QM_OBJQ_MEM						*	pMems;					//  是个数组

				 TCHAR									mutexName[64  +  1];
#if  0
				 HANDLE									hSema;					//  和mutxName一起用做同步
#else
				 CMutexRW							*	pRw;
#endif
				 unsigned  int							uiMaxCnt_sema;		
				 unsigned  int							uiInitCnt_sema;
				 unsigned  int							uiMilliSeconds_mutex_r;
				 unsigned  int							uiMilliSeconds_sema_r;
				 unsigned  int							uiMilliSeconds_mutex_w;
				 unsigned  int							uiMilliSeconds_sema_w;

				 PF_compare_qmObjQ						pfCompare; 
				 PF_commonHandler						pfExitQMemObj;
				 //
				 PF_fillQmObjMemInfo					pfFillQmObjMemInfo;
				 PF_commonHandler						tmp_pfAddToQmObjQ;				 
				 //
				 PF_commonHandler						pfPrintQ;
				 

}		 QM_OBJQ;



 __declspec(  dllexport  )  int  initQmObjQ(  void  *  p0,  void  *  pLicenseCtx,  int  iObjQType,  LPCTSTR  qName,  LPCTSTR  mutexName,  LPCTSTR  semaName,  unsigned  uiMaxCnt_sema,  
				PF_compare_qmObjQ  pfCompare,  PF_commonHandler  pfExitQMemObj,  PF_fillQmObjMemInfo  pfFillQmObjMemInfo,  PF_commonHandler  tmp_pfAddToQmObjQ,
				QM_OBJQ  *  pQParam  );
 //
 __declspec(  dllexport  )  void  exitQmObjQ(  void  *  p0,  QM_OBJQ  *  pQParam  );
 //
 __declspec(  dllexport  )  int  findQMemByKey(  void  *  p0,  void  *  pQParam,  void  *  pKeyInfo,  QM_OBJQ_MEM  *  pMemParam  );
 //
 __declspec(  dllexport  )  int  findQMemByObj(  void  *  p0,  void  *  pQParam,  void  *  pClient,  QM_OBJQ_MEM  *  pMem  );

 //
 __declspec(  dllexport  )  BOOL  bQmObjQFull(  void  *  p0,  void  *  pQParam  );
 //
 //
 int  addToQmObjQ(  void  *  p0,  QM_OBJQ_MEM  *  tmppMem,  void  *  pQParam,  PF_commonHandler  tmp_pfAddToQmObjQ  );
 __declspec(  dllexport  )  int  printQmObjQ(  QM_OBJQ  *  pQ  );
 int  procQmObjQ_netMc(  void  *  pSubThreadInfoParam,  void  *  pSessionParam  );
 //
 __declspec(  dllexport  )  int  procQmObjQ(  void  *  pServiceInfo,  QM_OBJQ  *  pObjQ,  void  *  pDb,  int  iDbType,  int  iObjType,  void  *  pClient,  QM_OBJQ_MEM  *  pMem  );

 //
 __declspec(  dllexport  )  int  qmObjQTraverse(  void  *  pServiceInfo,  void  *  pQParam,  PF_commonHandler pf_visit,  void  *  p0,  void  *  p1  );


__declspec(  dllexport  )  int  tmp_findMisQMemById(  void  *  p0,  void  *  pQParam,  void  *  pKeyInfo,  QM_OBJQ_MEM  *  pMemParam  );


__declspec(  dllexport  )  int  procMisMsg_moreData(  GENERIC_Q  *  pCacheQ,  MIS_MSG_INPUT  *  pMsgInput,  BOOL  *  pbMsgSkipped  );


#endif  //  }



