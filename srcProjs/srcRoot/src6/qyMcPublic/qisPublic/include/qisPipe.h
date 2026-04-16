

#ifndef  __qisPipe_h__
#define  __qisPipe_h__	//  {

//
#include	"qisPipe_open.h"
#include	"qyPipeFunc.h"


//
struct  __qisPipe_t												{

				 struct											{
					 TCHAR										pipeName[32];
					 //
					 BOOL										bStarter;

				 }												cfg;

				 //
				 TCHAR											name[64];

				 //
				 PARAM_initQisPipe								param;

				 //
				 //QY_Q2										inputQ2;										//  2015/09/09
				 //
				 QY_Q2											outputQ2;

				 //
				 DWORD											dwThreadId;						
				 HANDLE											hThread_recvRtsp;				
				 BOOL											bQuit;							
				 DWORD											dwTickCnt_start;				
				 BOOL											bRunning;						

				 //
				 //  2015/06/22
				 HANDLE											hEvent_syncThreadQuit_recvRtsp;

				 //
				 QY_pipe										pipe;

				 //
				 void									*		p0;												//  可以传给thread_work_iocp参数. 2012/02/24

				 //
				 BOOL											bInited;

				 //
				 struct											{
					 unsigned  long								ulbSessionErr:1;								//  

				 }												status;

};



//
//
typedef  struct  __ctx_pipeThread_t						{
				 //
				 QIS_pipe								*		pQisPipe;

				 //
				 HANDLE											hEvent_write;
				 
				 //
				 DWORD											dwThreadId;						
				 HANDLE											hThread_write;				
				 
}		 CTX_pipeThread;


//
//
DWORD  WINAPI  pipeThread_write(LPVOID lpvParam);



#endif  //  }


