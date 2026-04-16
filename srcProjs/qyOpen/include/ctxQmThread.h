

#ifndef  __ctxQmThread_h__
#define	 __ctxQmThread_h__	//  {


//
#define		M_ctxQmThread_commonMems	int			iType;						\
										DWORD  		dwTickCnt_lastGot;			\
										DWORD		dwThreadId9;					\
										int			reserved;


//
typedef  struct  __ctxQmThread_t	{
				 M_ctxQmThread_commonMems	
}		 CTX_qm_thread;



//
#ifdef  __cplusplus
 extern  "C" {
#endif
	 
//	 
__declspec(  dllexport  )  int init_tickCnt();
__declspec(  dllexport  )  DWORD  myGetTickCount(  CTX_qm_thread  *  pCtx  );
__declspec(  dllexport  )  unsigned  __int64  myGetMicroseconds();


#ifdef  _DEBUG
__declspec(dllexport) unsigned  __int64  get_g_tickCnt0_us();
#endif


#ifdef  __cplusplus
 }
#endif



#endif  //  }


