
#ifndef  __QYSHAREDQ_H__
#define  __QYSHAREDQ_H__	//  {


//  一个共享队列，用读写锁。注意，在初始化q时，要把q的mutexName设为"", 以避免在qPostMsg等函数里又被同步。 
// qPostMsg, qGetMsg.. 都要写一个成员函数
//

class  CQySharedQ										{
				 
public:
		CQySharedQ();
		virtual ~CQySharedQ();

private:
		struct											{
	
			struct										{
          					 
				//		以下为读写锁的参数, 
				TCHAR									mutexName_sync[32  +  1];						
				//
				unsigned  int							uiMaxCnt_sema;		
				unsigned  int							uiInitCnt_sema;
				unsigned  int							uiMilliSeconds_mutex_r;
				unsigned  int							uiMilliSeconds_sema_r;
				unsigned  int							uiMilliSeconds_mutex_w;
				unsigned  int							uiMilliSeconds_sema_w;
			}											cfg;

#if  0
			HANDLE										hSema_sync;						//  和mutxName一起用做同步
#else
			CMutexRW								*	pRw_sync;
#endif

			#ifdef  __DEBUG__
					DWORD								dwThreadId_gui;					//  要赋这个值,是因为在gui里,不能用共享锁.因为很多处理线程要调用SetWindowRgn(  ). SendMessage(  )来绘图.如果gui里用锁,就会和SendMessage(  )造成死锁.
			#endif

			BOOL										bQInited;

		}												m_var;

public:
		GENERIC_Q										m_q;

public:
		BOOL  bSetQInfo(  LPCTSTR  mutexName_sync,  unsigned  int  uiMaxCnt_sema,  unsigned  int  uiMilliSeconds_mutex_r,  unsigned  int  uiMilliSeconds_sema_r,  unsigned  int  uiMilliSeconds_mutex_w,  unsigned  int  uiMilliSeconds_sema_w  );

		int  initQ(  GENERIC_Q_CFG  *  pCfg,  PF_qElemNewEx  pfQElemNewEx,  PF_qElemNew  pfQElemNew,  PF_qElemInit  pfQElemInit,  PF_qElemExit  pfQElemExit,  PF_qElemFreeEx  pfQElemFreeEx,  PF_qElemFree  pfQElemFree  );
		void  exitQ(  );
	
		int  qPostMsg(  Q_ELEM_T  *  pQElem,  unsigned  int  size  );
		int  qGetMsg(  Q_ELEM_T  *  pQElem,  unsigned  int  *puiSize  );
		int  qRemoveMsg(  PF_bCommonHandler pf_bRemoveCond,  void  *  p0,  void  *  p1  );
		void  emptyQ(  );

		int  qTraverse(  PF_commonHandler pf_visit,  void  *  p0,  void  *  p1  );
		int  qTraverse_mono(  PF_commonHandler pf_visit,  void  *  p0,  void  *  p1  );

		BOOL  isFull(  );
		BOOL  isWarning(  unsigned  int  uiQNodes_warningInterval  );		//  判断是否队列的成员空闲空间〈uiQNodes_interval
		BOOL  isEmpty(  );
	


};



#endif  //  }


