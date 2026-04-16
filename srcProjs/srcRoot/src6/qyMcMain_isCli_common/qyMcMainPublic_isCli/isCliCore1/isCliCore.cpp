// isCliCore.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include	<stdlib.h>
#include	<tchar.h>

//#include <d3dx9.h>

#include	"qyMcMainCommon.h"

#include	"isCliCoreCommon.h"


//
//

 extern  "C" __declspec(dllexport)  int   set_g_pQyMc_isCliCore(  void  *  pQyMcParam  )
{
	if  (  !pQyMcParam  )  return  -1;
	QY_MC  *  pQyMc  =  (  QY_MC  *  )pQyMcParam;

#ifdef  __DEBUG__
		traceLog(  _T(  "set_g_pQyMc called"  )  );
#endif

	//  2013/07/31
	//set_g_pShowInfoStruct(  pQyMc->pShowInfoStruct  );


	return  0;
}


