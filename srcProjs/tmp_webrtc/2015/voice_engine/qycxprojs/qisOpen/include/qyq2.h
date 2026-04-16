


#ifndef  __QYQ2_H__
#define  __QYQ2_H__	//  {


#define		CONST_uiInitCnt_sema_q2SyncFlg						20									//  2009/05/13


typedef  struct  __qyQ2_t										{									//  2009/05/13

				 struct											{
					 TCHAR										name[16];
					 unsigned  int								uiMaxQNodes;

					 RW_lock_param								rwLockParam_syncFlg;

					 unsigned  int								uiMaxCnt_semaTrigger;

					 unsigned  short							usCnt_hEvents;
					 TCHAR										evt0Name[24];						//  2009/12/22
				 }												cfg;

				 //
				 BOOL											bFlag_toPostMsg_q1;
#if  0
				 TCHAR											mutexName_syncFlg[32  +  1];						
				 HANDLE											hSema_syncFlg;						//  和mutxName一起用做同步
#else				
				 CMutexRW								*		pRw_syncFlg;
#endif

				 //
				 HANDLE											hSemaTrigger1;				//  2007/05/08
				 long											lPrevCnt_semaTrigger;		//  2007/05/08, 没有严格意义，用来debug用。

				 //
				 HANDLE											hEvents[1  +  1];

				 unsigned  char									ucbTriggerErr;				//  2008/11/21. 在使用触发机制的队列中，当触发器满了，设置此位。有利于及时调用相关函数将触发器恢复

				 GENERIC_Q										qs[2];	

}		 QY_Q2;

//
__declspec(  dllexport  )  int  initQyQ2(  GENERIC_Q_CFG  *  pCfg,  RW_lock_param  *  pRwLockParam_syncFlg,  unsigned  short  usCnt_hEvents,  LPCTSTR  evt0Name,  PF_qElemNewEx  pfQElemNewEx,  PF_qElemNew  pfQElemNew,  PF_qElemInit  pfQElemInit,  PF_qElemExit  pfQElemExit,  PF_qElemFreeEx  pfQElemFreeEx,  PF_qElemFree  pfQElemFree,  PF_qElemRemove  pfQElemRemove,  QY_Q2  *  pQ2  );
__declspec(  dllexport  )  int  initQyQ2(  GENERIC_Q_cfgEx  *  pCfg,  RW_lock_param  *  pRwLockParam_syncFlg,  unsigned  short  usCnt_hEvents,  LPCTSTR  evt0Name,  QY_Q2  *  pQ2  );	//  2012/11/10

__declspec(  dllexport  )  int  exitQyQ2(  QY_Q2  *  pQ2  );
__declspec(  dllexport  )  void  emptyQ2(  QY_Q2  *  pQ  );

#if  0
	BOOL  isQ2Warning(  QY_Q2  *  pQ2,  unsigned  int  uiQNodes_warningInterval  );
	BOOL  isQ2Empty(  QY_Q2  *  pQ2  );
	int  getQ2Nodes_toPostMsg(  QY_Q2  *  pQ2  );
	int  getQ2Nodes_toGetMsg(  QY_Q2  *  pQ2  );
#endif

#define  isQ2Warning(  pQ2,  uiQNodes_warningInterval  )  (  !(  pQ2  )  ?  FALSE  :  (  isQWarning(  (  pQ2  )->bFlag_toPostMsg_q1  ?  &(  pQ2  )->qs[1]  :  &(  pQ2  )->qs[0],  uiQNodes_warningInterval  )  )  )
#define  isQ2Empty(  pQ2  )	(  !(  pQ2  )  ?  FALSE  :  (  isQEmpty(  &(  pQ2  )->qs[0]  )  &&  isQEmpty(  &(  pQ2  )->qs[1]  )  )  )
#define  getQ2Nodes_toPostMsg(  pQ2  )  (  !(  pQ2  )  ?  -1  :  (  (  pQ2  )->bFlag_toPostMsg_q1  ?  (  pQ2  )->qs[1].uiQNodes  :  (  pQ2  )->qs[0].uiQNodes  )  )
#define  getQ2Nodes_toGetMsg(  pQ2  )  (  !(  pQ2  )  ?  -1  :  (  (  pQ2  )->bFlag_toPostMsg_q1  ?  (  pQ2  )->qs[0].uiQNodes  :  (  pQ2  )->qs[1].uiQNodes  )  )
//  2015/02/18
#define  getQ2Nodes(  pQ2  )			(  !(  pQ2  )  ?  -1  :  (  (  pQ2  )->qs[0].uiQNodes  +  (  pQ2  )->qs[1].uiQNodes  )  )


//
__declspec(  dllexport  )  int  q2AvoidTriggerTooHigh(  LPCTSTR  mutexName_toAvoidTriggerTooHigh,  QY_Q2  *  pQ  );
__declspec(  dllexport  )  int  q2PostMsg(  Q_ELEM_T  *  pQElem,  unsigned  int  size,  QY_Q2  *  pQ2  );
__declspec(  dllexport  )  int  q2PostMsgAndTrigger(  Q_ELEM_T  *  pQElem,  unsigned  int  size,  QY_Q2  *  pQ2  );
__declspec(  dllexport  )  int  q2TriggerToProcess(  QY_Q2  *  pQ2  );
__declspec(  dllexport  )  int  q2GetMsg(  QY_Q2  *  pQ2,  Q_ELEM_T  *  pQElem,  unsigned  int  *  puiSize  );
__declspec(  dllexport  )  int  q2GetMsgPkg(  QY_Q2  *  pQ2,  void  *  pPkg,  unsigned  int  uiSize_pkg,  unsigned  int  *uiLens,  unsigned  int  *  pnLens  );
__declspec(  dllexport  )  int  q2GetMsgs(  QY_Q2  *  pQ2,  Q_ELEM_T  *  pQElems[],  unsigned  int  *puiSizes,  unsigned  int  *  pnQElems  );

//
typedef  int  (  *PF_q2GetMsg  )(  QY_Q2  *  pQ2,  Q_ELEM_T  *  pQElem,  unsigned  int  *  puiSize  );


class  CQyQ2Help: public CQyRWLock  {

		struct					{
			QY_Q2			*	pQ2;
			//
			GENERIC_Q		*	pQ_toGetMsg;
			GENERIC_Q		*	pQ_toPostMsg;
		}						m_var;
public:
		CQyQ2Help(  );
		~CQyQ2Help(  );

		GENERIC_Q	*	getQ_toPostMsg(  QY_Q2  *  pQ2  );
		GENERIC_Q	*	getQ_toGetMsg(  QY_Q2  *  pQ2  );
		int				qPostMsgAndTrigger(  Q_ELEM_T  *  pQElem,  unsigned  int  size,  QY_Q2  *  pQ2  );

};



#endif  //  }

