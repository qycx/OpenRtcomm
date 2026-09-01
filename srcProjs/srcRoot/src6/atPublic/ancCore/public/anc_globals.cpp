
#include	"stdafx.h"
#include	<tchar.h>

//
#include	"myTypes_basic.h"

#include	"ancCorePublic.h"



//
#if  0
	#define		DEFAULT_commVer		CONST_atCommVer_null
#else
	//#define		DEFAULT_commVer		CONST_atCommVer_1
#endif 
//
#ifdef  __USE_atCommVer_2__
		#define		DEFAULT_commVer		CONST_atCommVer_2
#else

		#define		DEFAULT_commVer		CONST_atCommVer_3

#endif 


//
extern  "C" {

	__declspec(dllexport)  
		int g_iCommVer = DEFAULT_commVer;


}




