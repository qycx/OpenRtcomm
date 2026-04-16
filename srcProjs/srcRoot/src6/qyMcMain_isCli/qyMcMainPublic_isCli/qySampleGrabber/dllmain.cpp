// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include	"streams.h"

extern "C" BOOL WINAPI DllEntryPoint(HINSTANCE, ULONG, LPVOID);

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  dwReason,
                       LPVOID lpReserved
					 )
{
#if  0
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
#endif
	return DllEntryPoint((HINSTANCE)(hModule), dwReason, lpReserved);
}


 STDAPI DllRegisterServer(void)
{
	return AMovieDllRegisterServer2( TRUE );
}

STDAPI DllUnregisterServer(void)
{
	return AMovieDllRegisterServer2( FALSE );
}


__declspec(dllexport)  int  kk(  )
{
	return 0;
}