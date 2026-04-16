
#ifndef  __mcSharedQ_h__
#define  __mcSharedQ_h__  //  {

//
#include	"syncmtcnt.h"

//
//#define		__USE_qySharedQ__


#ifdef  __USE_qySharedQ__
		#include	"qySharedQ.h"
#endif
#include	"taskCommon.h"

//
typedef  struct  __qMem_mcTask_t					{
				 //SYNC_mt_cnt						syncMtCnt;

				 //
				 BOOL								bUsed;							//  赋值true表明new
				 				 
				 //
				 QY_MEMORY							qElemMemory;
				 unsigned  int						size;
				 
				 //
				 unsigned  char						ucbQElemInited;					//  表明是否初始化

				 //
				 BOOL								bNeedRemoved;					//  是否准备放弃

				 //
				 TCHAR								tDesc[16];

}		 QMEM_mcTask;

//
class  CCtxQyMc;

//
typedef  struct  __mcShareQ_var_t					{

				 //
				 CCtxQyMc						*	pQyMc;
				 

				 //
				 GENERIC_Q_CFG						cfg;

				 //
				 PF_qElemNew						pfQElemNew;
				 PF_qElemFree						pfQElemFree;
				 //
				 PF_qElemNewEx						pfQElemNewEx;				//  2010/04/24
				 PF_qElemFreeEx						pfQElemFreeEx;				//  2010/04/24
				 //
				 PF_qElemInit						pfQElemInit;				//  2007/06/10
				 PF_qElemExit						pfQElemExit;				//  
				 //
				 PF_qElemRemove						pfQElemRemove;				//  2009/12/08
				 //
				 PF_qElemRemoveEx					pfqElemRemoveEx;			//  2012/11/10

				 //				
				 RW_lock_param rwLockParam_sync;
				 		
				 //		
				 CMutexRW * pRw_sync;

			
				 #ifdef  __DEBUG__
						 DWORD						dwThreadId_gui;					
						 //  
						 DWORD											dwThreadId_console;
				 #endif

				 //
				 QMEM_mcTask						*			pMems;
				 //
				 unsigned  int									uiQNodes;
				 			
				 //
				 
		
}		 MC_sharedQ_var;

//
class CCtxQyMc;

//
typedef  int  (  *  PF_enumTask  )(  CCtxQyMc  *  pQyMc,  LPVOID  p0,  LPVOID  p1,  TASK_common * taskElem  );
typedef  int  (  *  PF_bEnumTask  )(  CCtxQyMc  *  pQyMc,  LPVOID  p0,  LPVOID  p1,  TASK_common *  taskElem  );		//  TRUE or FALSE


//
class  CMcSharedQ 
		#ifdef  __USE_qySharedQ__
				//: public  CQySharedQ
		#endif
{
				 
public:
		CMcSharedQ();
		virtual ~CMcSharedQ();

		
		//
public:
		MC_sharedQ_var		m_var;

		

#ifndef  __USE_qySharedQ__

public:
		//
		int  getMutexName(  int  i,  TCHAR  *  mutexName,  int  cnt  )
		{
			_sntprintf(  mutexName,  cnt,  _T(  "mcSharedObj%d"  ),  i  );
			return  0;
		}

		//
		void  qNodeFree(  MC_sharedQ_var  *  pQ,  QMEM_mcTask *pMem,  BOOL  bElemRemove  );

		//
		int  recalc_uiQNodes(  );


		//
		BOOL  bSetQInfo(  LPCTSTR  mutexName_sync,  unsigned  int  uiMaxCnt_sema,  unsigned  int  uiMilliSeconds_mutex_r,  unsigned  int  uiMilliSeconds_sema_r,  unsigned  int  uiMilliSeconds_mutex_w,  unsigned  int  uiMilliSeconds_sema_w  );

		//
		int  initQ(  GENERIC_Q_CFG  *  pCfg,  RW_lock_param pRwLockParam_sync, PF_qElemNewEx  pfQElemNewEx,  PF_qElemNew  pfQElemNew,  PF_qElemInit  pfQElemInit,  PF_qElemExit  pfQElemExit,  PF_qElemFreeEx  pfQElemFreeEx,  PF_qElemFree  pfQElemFree  );
		void  exitQ(  );
	
		int  qPostMsg(  Q_ELEM_T  *  pQElem,  unsigned  int  size  );
		int  qGetMsg(  Q_ELEM_T  *  pQElem,  unsigned  int  *puiSize  );
		int  qRemoveMsg(  PF_bEnumTask pf_bRemoveCond,  void  *  p0,  void  *  p1  );
		int  emptyQ(  );

		int  qTraverse(  PF_enumTask pf_visit,  void  *  p0,  void  *  p1  );
		int  qTraverse_mono(  PF_enumTask pf_visit,  void  *  p0,  void  *  p1  );

		BOOL  isFull(  );
		BOOL  isWarning(  unsigned  int  uiQNodes_warningInterval  );		//  判断是否队列的成员空闲空间〈uiQNodes_interval
		BOOL  isEmpty(  );

		//
		int	 chkMsgs_toBeRemoved(  );

#endif

};





#endif  //  }


