// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include	<tchar.h>

int  init_zero_spl(  );
int  load_spl(  LPCTSTR  path  );
int  unload_spl(  );


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		 init_zero_spl(  );
		 load_spl(  _T(  ""  )  );
		 break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		 break;
	case DLL_PROCESS_DETACH:
		 unload_spl(  );
		 break;
	}
	return TRUE;
}

