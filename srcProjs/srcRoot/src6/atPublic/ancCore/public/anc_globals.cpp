
#include	"stdafx.h"
#include	<tchar.h>

#include	"ancCorePublic.h"

//#include	"qyMcMainCommon.h"

//
#if  0
	#define		DEFAULT_commVer		CONST_atCommVer_null
#else
	//#define		DEFAULT_commVer		CONST_atCommVer_1
	#define		DEFAULT_commVer		CONST_atCommVer_2
#endif 


//
extern  "C" {

	__declspec(dllexport)  
		int g_iCommVer = DEFAULT_commVer;


}




