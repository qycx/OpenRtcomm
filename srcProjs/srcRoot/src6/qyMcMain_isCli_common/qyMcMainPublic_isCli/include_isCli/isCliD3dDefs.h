

#ifndef  __isCliD3dDefs_h__
#define  __isCliD3dDefs_h__		//  {



#ifndef  __DEBUG__
	//  下面这2个值应该一样
	#define		MAX_talkerMosaic_streams									2
	#define		MAX_talkerMosaic_threads									2	//1
#else
	//  下面这2个值应该一样
	#define		MAX_talkerMosaic_streams									2	//1
	#define		MAX_talkerMosaic_threads									2	//1
#endif


//
#ifndef  __DEBUG__
#if  MAX_talkerMosaic_streams  !=  MAX_talkerMosaic_threads
错了
#endif
#endif



#endif  //  }


