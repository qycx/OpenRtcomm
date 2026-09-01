// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include "qyMcMainCommon.h"


//
int dll_initInstance()
{
	//
	set_cur_iResId_sys(CONST_resId_sys_isCliHelp);

	return 0;
}

int dll_exitInstance()
{
	return 0;
}

//
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
		dll_initInstance();
		}
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH: 
		{
		dll_exitInstance();
		}
		break;
	}
	return TRUE;
}

