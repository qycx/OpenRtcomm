

#ifndef  __qyShowInfoCommon_h__
#define  __qyShowInfoCommon_h__	//  {

//typedef  int  (  *  PF_q2PostMsgAndTrigger  )(  void  *  pQElem,  unsigned  int  size,  void  *  pQ2  );

//
#include	"qy_qBuf2.h"


//
typedef  struct								{
				BOOL						bInited;
				//
				TCHAR						errHintWndCls[512];
				PF_qyShowInfo0				errHintPf;
				//
				DWORD						dwThreadId;
				HANDLE						hThread;
				BOOL						bQuit;
				//
				BOOL						bShowMore;
				//
				TCHAR						mutexName_syncQ[32];
				//
				BOOL						bUsePipe;			//  2012/02/03
				BOOL						bUseSock;
				char						servIp[CONST_qyMaxIpLen  +  1];
				unsigned  short				usPort;
				BOOL						bResetServ;
				//
				BOOL						bCli;
				//
				RW_lock_param				rwLockParam;		//  2009/05/14
	 
				//  
				//QY_Q2						q2;
				QY_qBuf2			*		pq2;
				BOOL						bQInited;
				//
				//QY_Q2						state_q2;			//  2015/08/23
				QY_qBuf2			*		pstate_q2;
				BOOL						bQInited_state;
				
				//
				//PF_q2PostMsgAndTrigger		pf_q2PostMsgAndTrigger;		//  2014/03/23

}		ShowInfo_struct;




#endif  //  }

