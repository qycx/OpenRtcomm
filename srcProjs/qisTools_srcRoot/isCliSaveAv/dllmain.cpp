// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include	<tchar.h>
//#include	"qyMcMainCommon.h"


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		 	//  2013/09/07. ∫ÕisCliHelpπ≤”√
			//set_cur_iResId_sys(  CONST_resId_sys_isCliHelp  );
			break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	//
	return TRUE;
}

