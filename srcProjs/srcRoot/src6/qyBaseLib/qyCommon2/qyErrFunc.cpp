	
#include	"qyPrecomp.h"

#include    <WinSock2.h>
#include	<windows.h>
#include	<stdio.h>
#include	<stdlib.h>
#ifndef  __WINCE__
	#include	<process.h>
	#include	<lmerr.h>
#endif
#include	<tchar.h>
#include	"qyCommon.h"


 extern "C" void qyDisplayLastError( LPSTR szAPI )
{
    HMODULE		hModule				=	NULL; // default to system source
    DWORD		dwLastError			=	GetLastError(  );
    LPTSTR		MessageBuffer;
    DWORD		dwBufferLength;
	TCHAR		tBuf[512]			=	_T(  ""  );
	
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%S error! ( rc = %lu ): "  ),  szAPI, dwLastError  );

    DWORD  dwFormatFlags  =  FORMAT_MESSAGE_ALLOCATE_BUFFER 
							|  FORMAT_MESSAGE_IGNORE_INSERTS 
								|  FORMAT_MESSAGE_FROM_SYSTEM ;
    //
    // if dwLastError is in the network range, load the message source
    //
	
#ifndef  __WINCE__

    if  (  dwLastError  >=  NERR_BASE  &&  dwLastError  <=  MAX_NERR  )  {
		TCHAR		svLibName[MAX_PATH  +  1];
		
		if  (  qyFullLibName(  _T(  "netmsg.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
        hModule  =  LoadLibraryEx(  svLibName,
            						NULL,
            						LOAD_LIBRARY_AS_DATAFILE  );
        if  (  hModule  !=  NULL  )  dwFormatFlags  |=  FORMAT_MESSAGE_FROM_HMODULE;
    }
	
#endif

    //
    // call FormatMessage() to allow for message text to be acquired
    // from the system or the supplied module handle
    //
    if  (  dwBufferLength  =  FormatMessage(  dwFormatFlags,
											   hModule, // module to get message from (NULL == system)
        									   dwLastError,
        									   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
        									   (LPTSTR) &MessageBuffer,
        									   0,
        									   NULL  )  )
    {
	
        	
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s [%s]"  ),  tBuf,  MessageBuffer  );
		
        //
        // free the buffer allocated by the system
        //
        LocalFree(  MessageBuffer  );
    }

	traceLogA(  "%S",  tBuf  );

errLabel:
    //
    // if we loaded a message source, unload it
    //
    if  (  hModule  !=  NULL  )  FreeLibrary(  hModule  );
		
}

 