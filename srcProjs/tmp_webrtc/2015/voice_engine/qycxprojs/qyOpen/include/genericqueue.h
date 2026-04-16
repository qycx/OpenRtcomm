#ifndef  __GENERICQUEUE_H__ 
#define  __GENERICQUEUE_H__

#ifdef  __cplusplus
  extern  "C"  {
#endif

//
#define __DUAL_LINK_LIST__

 #define  OBJ_T		void
 
 #define  Q_ELEM_T	void

typedef  struct  __q_node_t							{

				  //  Q_ELEM_T						*	pQElem;
				  QY_MEMORY							qElemMemory;
				  unsigned  int						size;
				  //
				  unsigned  char					ucbQElemInited;

				  #ifdef  __DUAL_LINK_LIST__
						  struct  __q_node_t	*	pPrev;	
				  #endif

				  struct  __q_node_t			*	pNext;

				  //  unsigned  int						uiSeqNo;				//  下次加入连表的节点的序号；

}		 Q_NODE;


//  sun介绍：队列中每个节点有一个不重复的序号，此序号和mutexName_prefix一起，用于在队列节点增删操作时的同步
//  可惜此项技术还有点用不上。2007/04/17


//  typedef  Q_ELEM_T  *  (  *  PF_qElemNew  )(  unsigned  int  );
typedef  Q_ELEM_T  *  (  *  PF_qElemNew  )(  size_t  );
typedef  void  (  *  PF_qElemFree  )(  Q_ELEM_T  *  p  );
//
typedef  char  *  (  *  PF_qElemNewEx  )(  int  iAllocType,  size_t  size,  QY_MEMORY  *  p  );	//  2010/04/24
typedef  void  (  *  PF_qElemFreeEx  )(  QY_MEMORY  *  p  );								//  2010/04/24
//
typedef  int  (  *  PF_qElemInit  )(  Q_ELEM_T  *  p  );
typedef  void  (  *  PF_qElemExit  )(  Q_ELEM_T  *  p  );
typedef  void  (  *  PF_qElemRemove  )(  Q_ELEM_T  *  p,  LPCTSTR  hint  );
//
typedef  void  (  *  PF_qElemRemoveEx  )(  Q_ELEM_T  *  p,  size_t  size,  LPCTSTR  hint  );	//  2012/11/10



typedef  struct  __genericQCfg_t					{
				 TCHAR								name[24];					//  队列名称, 用在调试等工作用
				 unsigned  int						uiMaxQNodes;				//  对队列中的节点数做限制，为0时不限制

				 TCHAR								mutexName_prefix[32];		//  队列中的增删处理节点同步用

				 //
				 unsigned  int						uiMaxCnt_semaTrigger;		//  对用在线程处理做触发用的semaphore, 为0时不用
				 				 
				 //
				 BOOL								bUseEvt;
				 TCHAR								evt0Name[24];				//  2009/12/22
				 
}		 GENERIC_Q_CFG;


//  2012/11/10
typedef  struct  __genericQCfgEx_t					{
				 GENERIC_Q_CFG						common;
				 //
				 PF_qElemNewEx						pfQElemNewEx;
				 PF_qElemNew						pfQElemNew;
				 PF_qElemInit						pfQElemInit;
				 PF_qElemExit						pfQElemExit;
				 PF_qElemFreeEx						pfQElemFreeEx;
				 PF_qElemFree						pfQElemFree;
				 PF_qElemRemoveEx					pf_QElemRemoveEx;
				 PF_qElemRemove						pfQElemRemove;

}		 GENERIC_Q_cfgEx;

//
typedef  struct  __generic_q_t						{

				 GENERIC_Q_CFG						cfg;

				 Q_NODE								front;
				 Q_NODE							*	pRear;
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
				 unsigned  int						uiQNodes;

				 //
				 HANDLE								hSemaTrigger;				//  2007/05/08				 
				 long								lPrevCnt_semaTrigger;		//  2007/05/08, 没有严格意义，用来debug用。

				 //
				 HANDLE								hEvent;

				 //				 	
				 unsigned  char						ucbTriggerErr;				//  2008/11/21. 在使用触发机制的队列中，当触发器满了，设置此位。有利于及时调用相关函数将触发器恢复
				 
				 //
				 BOOL								bNeedSync;

				 CRITICAL_SECTION					cs;
				 BOOL								bCsInited;

				 SYNC_OBJ_PARAM						syncObjParam;

				 //  2012/07/14
				 BOOL								bInited;

				 //  2009/09/20 
				 Q_NODE							*	pLastQNode;

 }		GENERIC_Q;


 extern __declspec(dllexport) OBJ_T *objNew( int size );
 extern __declspec(dllexport) void objFree( OBJ_T *p );
 #define qNodeNew( ) objNew( sizeof( Q_NODE ) )

//  void qNodeFree(  GENERIC_Q  *  pQ,  Q_NODE *pQNode  );


__declspec(  dllexport  )  GENERIC_Q  *  genericQNew(  LPCTSTR  qName,  LPCTSTR  mutexName_prefix,  unsigned  int  uiMaxCnt_sema,  unsigned  int  uiMaxQNodes,  PF_qElemNew  pfQElemNew,  PF_qElemFree  pfQElemFree  );
__declspec(  dllexport  )  void genericQFree( GENERIC_Q *pQ );
__declspec(  dllexport  )  void exitGenericQ( GENERIC_Q *pQ );
//
int  qPostMsgEx(  Q_ELEM_T  *  pQElem,  int  iAllocType,  unsigned  int  size,  GENERIC_Q  *  pQ  );
//
__declspec(  dllexport  )  int  qPostMsg(  Q_ELEM_T  *  pQElem,  unsigned  int  size,  GENERIC_Q  *  pQ  );
__declspec(  dllexport  )  int  qPostMsgAndTrigger(  Q_ELEM_T  *  pQElem,  unsigned  int  size,  GENERIC_Q  *  pQ  );
__declspec(  dllexport  )  int  qAvoidTriggerTooHigh(  LPCTSTR  mutexName_toAvoidTriggerTooHigh,  GENERIC_Q  *  pQ  );

int  qSendMsg(  Q_ELEM_T  *  pQElem,  int  size,  GENERIC_Q  *  pQ  );
__declspec(  dllexport  )  int  qGetMsg(  GENERIC_Q  *  pQ,  Q_ELEM_T  *  pQElem,  unsigned  int  *puiSize  );
__declspec(  dllexport  )  int  qGetMsgs(  GENERIC_Q  *  pQ,  Q_ELEM_T  *  pQElems[],  unsigned  int  *puiSizes,  unsigned  int  *  pnQElems  );	//  2011/07/15
__declspec(  dllexport  )  int  qGetMsgPkg(  GENERIC_Q  *  pQ,  void  *  pPkg,  unsigned  int  uiSize_pkg,  unsigned  int  *uiLens,  unsigned  int  *  pnLens  );
__declspec(  dllexport  )  int  qRemoveMsg(  GENERIC_Q  *  pQ,  PF_bCommonHandler pf_bRemoveCond,  void  *  p0,  void  *  p1  );
__declspec(  dllexport  )  void  emptyGenericQ( GENERIC_Q *pQ );
//
//  __declspec(  dllexport  )  int  qTraverse(  GENERIC_Q  *  pQ,  PF_commonHandler pf_visit,  void  *  p0,  void  *  p1  );
__declspec(  dllexport  )  int  qTraverse(  GENERIC_Q  *  pQ,  PF_commonHandler pf_visit,  void  *  p0,  void  *  p1  );
//
#if  0
	BOOL  isQFull(  GENERIC_Q  *  pQ  );
	BOOL  isQWarning(  GENERIC_Q  *  pQ,  unsigned  int  uiQNodes_warningInterval  );		//  判断是否队列的成员空闲空间〈uiQNodes_interval
	BOOL  isQEmpty(  GENERIC_Q  *  pQ  );
#endif

#define  isQFull(  pQ  )  (  !(  pQ  )  ?  FALSE  :  (  (  pQ  )->cfg.uiMaxQNodes  &&  (  pQ  )->uiQNodes  >=  (  pQ  )->cfg.uiMaxQNodes  )  )
#define  isQWarning(  pQ,  uiQNodes_warningInterval  )  (  !(  pQ  )  ?  FALSE  :  (  (  pQ  )->cfg.uiMaxQNodes  &&  (  pQ  )->uiQNodes  +  uiQNodes_warningInterval  >=  (  pQ  )->cfg.uiMaxQNodes  )  )
#define  isQEmpty(  pQ  )  (  (  (  pQ  )->front.pNext  )  ?  FALSE  :  TRUE  )



/*
 extern __declspec(dllexport) unsigned int qLength( GENERIC_Q *pQ );
 extern __declspec(dllexport) int peekMsg( GENERIC_Q *pQ, Q_ELEM_T *pQElem, int size );
 */

#define getpLastQNode( pQ ) pQ->pRear

__declspec(  dllexport  )  int removeAQNode( GENERIC_Q *pQ, Q_NODE *pQNode );
__declspec(  dllexport  )  int preserveLastQNode( GENERIC_Q *pQ );
__declspec(  dllexport  )  int restoreLastQNode( GENERIC_Q *pQ );
__declspec(  dllexport  )  void stopPreserveLastQNode( GENERIC_Q *pQ );
__declspec(  dllexport  )  void link2Q( GENERIC_Q *pSrcQ, GENERIC_Q *pDesQ );
 /*
 extern __declspec(dllexport) int insertMsg( GENERIC_Q *pQ, Q_NODE *pFollowed, Q_ELEM_T *pInserted, int size );
*/




#ifdef __cplusplus
 }
#endif


//  2012/11/10
__declspec(  dllexport  )  int  initGenericQ(  LPCTSTR  qName,  LPCTSTR  mutexName_prefix,  unsigned  int  uiMaxCnt_semaTrigger,  unsigned  int  uiMaxQNodes,  PF_qElemNewEx  pfQElemNewEx,  PF_qElemNew  pfQElemNew,  PF_qElemInit  pfQElemInit,  PF_qElemExit  pfQElemExit,  PF_qElemFreeEx  pfQElemFreeEx,  PF_qElemFree  pfQElemFree,  PF_qElemRemoveEx  pfQElemRemoveEx,  PF_qElemRemove  pfQElemRemove,  GENERIC_Q  *  pQ  );

__declspec(  dllexport  )  int  initGenericQ(  LPCTSTR  qName,  LPCTSTR  mutexName_prefix,  unsigned  int  uiMaxCnt_semaTrigger,  unsigned  int  uiMaxQNodes,  PF_qElemNewEx  pfQElemNewEx,  PF_qElemNew  pfQElemNew,  PF_qElemInit  pfQElemInit,  PF_qElemExit  pfQElemExit,  PF_qElemFreeEx  pfQElemFreeEx,  PF_qElemFree  pfQElemFree,  PF_qElemRemove  pfQElemRemove,  GENERIC_Q  *  pQ  );

__declspec(  dllexport  )  int  initGenericQ(  LPCTSTR  qName,  LPCTSTR  mutexName_prefix,  unsigned  int  uiMaxCnt_semaTrigger,  unsigned  int  uiMaxQNodes,  PF_qElemNew  pfQElemNew,  PF_qElemFree  pfQElemFree,  GENERIC_Q  *  pQ  );
//
__declspec(  dllexport  )  int  initGenericQ(  GENERIC_Q_CFG  *  pCfg,  PF_qElemNew  pfQElemNew,  PF_qElemInit  pfQElemInit,  PF_qElemExit  pfQElemExit,  PF_qElemFree  pfQElemFree,  PF_qElemRemove  pfQElemRemove,  GENERIC_Q  *  pQ  );

//  2010/04/25
__declspec(  dllexport  )  int  initGenericQ(  GENERIC_Q_CFG  *  pCfg,  PF_qElemNewEx  pfQElemNewEx,  PF_qElemNew  pfQElemNew,  PF_qElemInit  pfQElemInit,  PF_qElemExit  pfQElemExit,  PF_qElemFreeEx  pfQElemFreeEx,  PF_qElemFree  pfQElemFree,  PF_qElemRemove  pfQElemRemove,  GENERIC_Q  *  pQ  );

//  2012/11/10
__declspec(  dllexport  )  int  initGenericQ(  GENERIC_Q_cfgEx  *  pCfg,  GENERIC_Q  *  pQ  );


//  2014/06/20
typedef  int  (  *  PF_qPostMsg  )(  Q_ELEM_T  *  pQElem,  unsigned  int  size,  GENERIC_Q  *  pQ  );
typedef  int  (  *  PF_qGetMsg  )(  GENERIC_Q  *  pQ,  Q_ELEM_T  *  pQElem,  unsigned  int  *  puiSize  );



#endif /*} end of __GENERICQUEUE_H__ */



