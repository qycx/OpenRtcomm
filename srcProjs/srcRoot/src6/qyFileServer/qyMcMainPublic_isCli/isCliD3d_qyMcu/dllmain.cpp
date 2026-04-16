// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include	<tchar.h>
#include	"qyMcMainCommon.h"


HINSTANCE	g_hInst  =  NULL;


//  2013/06/10
 HINSTANCE  get_my_hInst(  )
{
	return  g_hInst;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	if  (  !g_hInst  )  g_hInst  =  hModule;
	MACRO_qyAssert(  g_hInst  ==  hModule,  _T(  "isCliD3d: g_hInst err"  )  );

	//
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


#if  0
ATOM MyRegisterClass_test(HINSTANCE hInstance);
int  MyUnregisterClass_test(  HINSTANCE  hInst  );
#endif

extern  D3D_context	g_d3dContext;

extern  "C" __declspec(  dllexport  )  int  dllInit_d3d_isCli(  )	
{
	int				iErr	=	-1;

#if  0
	ATOM	a;
	a  =  MyRegisterClass_test(  g_hInst  );
	if  (  !a  )  goto  errLabel;
#endif
	
	//  2013/09/07. ∫ÕisCliHelpπ≤”√
	set_cur_iResId_sys(  CONST_resId_sys_isCliHelp  );

	//
	g_pD3dContext = &g_d3dContext;


#ifdef  __DEBUG__
	{
		//  mymalloc(  1  );
		//  new  char [1];
	}
#endif

	iErr  =  0;
errLabel:



	return  iErr;
}

extern  "C" __declspec(  dllexport  )  int  dllExit_d3d_isCli(  )
{
#if  0
	MyUnregisterClass_test(  g_hInst  );
#endif

	return  0;
}
