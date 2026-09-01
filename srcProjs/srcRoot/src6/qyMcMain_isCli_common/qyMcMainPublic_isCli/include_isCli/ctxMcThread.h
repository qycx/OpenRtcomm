

#ifndef  __ctxMcThread_h__
#define  __ctxMcThread_h__	//  {


#include	"qmcCommFunc_mis.h"
#include	"mcSharedQ.h"

//  2015/12/08
#include	"ctxQmThread.h"
#include	"qisPipe_open.h"

//
typedef  struct  __ctxMcThread_t						{
				 CTX_qm_thread							common;

				 //
				 CMcSharedQ						*		pProcessQ;		 

				 DWORD									dwTickCnt_tryToResumeVideoConference;	//  2009/10/17

				 MIS_MSGU						*		pMsgBuf_forInput;						//  2009/12/11
				 MIS_MSGU						*		pMsgBuf;								//  2009/12/11

}		  CTX_MC_THREAD, CTX_MC_thread;


typedef  struct  __ctxMc_work_t							{				
				 CTX_MC_thread							common;

				 GENERIC_Q								guestQ;
				 BOOL									bGuestQInited;
				 void							**		ppGuests_sortedByDevIdStr;
				 //

}		  CTX_MC_work;


typedef  struct  __ctxMc_scheduler_t					{		//  2009/09/05				
				 CTX_MC_thread							common;

				 //
				 void* pDBManager;

}		  CTX_MC_scheduler;





//  2014/03/07
typedef  struct  __ctxMc_pretrans_t						{
				 CTX_MC_thread							common;
				 
				 //  2014/05/12
				 struct									{
					 struct								{
						 BOOL							bErrExists_mallocfFailed;
					 }									errFlgs;
					 unsigned  char						ucMsgSkipped_ifMallocFailed;		//  2014/05/12
				 }										status;

				 //
				 MIS_MSGU						*		pMsgBuf;
				 //
}		 CTX_mc_pretrans;



//  2016/03/15
typedef  struct  __ctxMc_talkerThread_t					{
				 CTX_MC_thread							common;

}		 CTX_mc_talkerThread;

//
//  2016/06/15
typedef  struct  __ctxMc_shareDynBmpsThread_t			{
				 CTX_MC_thread							common;

				 //
				 void							*		pShareDynBmps_threadProcInfo;
				 QIS_pipe						*		pQisPipe;

}		 CTX_mc_shareDynBmpsThread;





#endif  //  }


