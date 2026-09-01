
#ifndef  __QYPRECOMP_H__
#define  __QYPRECOMP_H__	/* { */


//#define  __WITHOUT_SOCK__

#if  1
	#define		UNICODE
	#define		_UNICODE
#endif 


#ifdef		_DEBUG
	#define		__DEBUG__
#endif


#ifdef		__DEBUG__								//  Debug版本开关量


//
#ifndef  __noDbg_new__
//

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

//
#endif 

#endif



#ifndef		__DEBUG__								//  Release版本开关量
	//#define		__WITHOUT_DEBUG_LOG__	
#endif



//
#endif	/* } */


