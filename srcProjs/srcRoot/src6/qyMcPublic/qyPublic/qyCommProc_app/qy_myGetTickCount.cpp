

#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	<time.h>
#include	<stdlib.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyDefs_open.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCustom.h"
#include	"qyTCharCommProc.h"

#include	"tmpCeLib.h"

#include	"ctxQmThread.h"

LARGE_INTEGER g_tFreq={0};
LARGE_INTEGER g_t0={0};
unsigned  __int64		  g_tickCnt0_us  =  0;

//
extern  "C"  __declspec(  dllexport  )  int init_tickCnt()
{
	QueryPerformanceFrequency(  &g_tFreq  );
	QueryPerformanceCounter(  &g_t0  );
	g_tickCnt0_us  =  ((unsigned  __int64)GetTickCount(  ))  * 1000;
	return  0;
}


//
#ifdef  __DEBUG__

//
extern "C"  __declspec(dllexport) unsigned  __int64  get_g_tickCnt0_us()
{
	return  g_tickCnt0_us;
}
#endif 




//
extern  "C"  __declspec(  dllexport  )  unsigned  __int64  myGetMicroseconds()
{
	if(!g_tFreq.QuadPart  )  return  0;
	LARGE_INTEGER t1;
	QueryPerformanceCounter(&t1  );

	unsigned __int64 elapseInMs = ( t1.QuadPart  -  g_t0.QuadPart  )  *  1000000  /  g_tFreq.QuadPart;

	return elapseInMs  +  g_tickCnt0_us;
}


 extern  "C"  __declspec(  dllexport  )  DWORD  myGetTickCount(  CTX_qm_thread  *  pCtx  )
 {
	 unsigned  __int64  us  =  myGetMicroseconds(  );
	 DWORD  dwTickCnt  =  us  /  1000;
	 //
	 if  (  pCtx  )  {
		 if  (  dwTickCnt  <=  pCtx->dwTickCnt_lastGot  )  {
			 dwTickCnt  =  pCtx->dwTickCnt_lastGot  +  1;
		 }
		 pCtx->dwTickCnt_lastGot  =  dwTickCnt;
	 
		 //
		 #ifdef  __DEBUG__
				 if  (  GetCurrentThreadId()  !=  pCtx->dwThreadId9  )  {		
					 MACRO_qyAssert(  0,  _T(  "myGetTickCount: threadId not matched"  )  );	 
				 }
		 #endif
	 }


	 return  dwTickCnt;
 }

 
 