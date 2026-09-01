// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include	<tchar.h>
//#include	"qyMcMainCommon.h"

#include <windows.h>
#include <stdio.h>

#define VERSION_NUMBER "1.26.7.30"

// 实际的写入函数
void WriteVersionFile()
{
    OutputDebugStringA("exec WriteVersionFile\n");

    char filePath[256];
    sprintf(filePath, "d:/qycx/log/isCliSaveAv.ver.%s", VERSION_NUMBER);

    // 使用共享模式打开文件
    HANDLE hFile = CreateFileA(
        filePath,
        GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,  // 允许共享读写
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile != INVALID_HANDLE_VALUE) {
        DWORD dwBytesWritten;
        char versionInfo[512];
        DWORD processId = GetCurrentProcessId();

        sprintf(versionInfo,
            "DLL Version: %s\n"
            "Build Date: %s\n"
            "Build Time: %s\n"
            "Created by Process ID: %d\n",
            VERSION_NUMBER, __DATE__, __TIME__, processId);

        WriteFile(hFile, versionInfo, strlen(versionInfo), &dwBytesWritten, NULL);
        CloseHandle(hFile);

        OutputDebugStringA("Version file created successfully\n");
    }
}


void WriteVersionFileWithMutex()
{
   
    HANDLE hMutex = CreateMutexA(NULL, FALSE, "Global\\isCliSaveAvDLLVersionMutex");

    if (hMutex == NULL) {        
        WriteVersionFile();
        return;
    }

  
    DWORD dwWaitResult = WaitForSingleObject(hMutex, 5000);

    if (dwWaitResult == WAIT_OBJECT_0) {
      
        WriteVersionFile();

      
        ReleaseMutex(hMutex);
    }
    else {
       
        OutputDebugStringA("Failed to acquire mutex for version file writing\n");
       
    }

   
    CloseHandle(hMutex);
}




BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
        WriteVersionFileWithMutex();

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

