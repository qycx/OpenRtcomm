// msgrMgrModule.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "msgrMgrModule.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
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


// This is an example of an exported variable
MSGRMGRMODULE_API int nMsgrMgrModule=0;

// This is an example of an exported function.
MSGRMGRMODULE_API int fnMsgrMgrModule(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see msgrMgrModule.h for the class definition
CMsgrMgrModule::CMsgrMgrModule()
{ 
	return; 
}

