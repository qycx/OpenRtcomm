
#include<windows.h>
#include<winsock.h>

#include "asrPrecomp.h"
#include "asrCommon.h"


 extern "C" int _cdecl TCPIO_Insert(void)
{
	traceLog2( "TCPIO_Insert: ", "enters." );
	
	// Initialize Winsock 1.1
	WSADATA wsaData;
	if( WSAStartup(MAKEWORD(1,1), &wsaData)!=0) {
		traceLog2( "TCPIO_Insert: ", "WSAStartup( ) failed." );
		return -1;
	}
	traceLog2( "TCPIO_Insert: ", "after WSAStartup( )." );
	if(LOBYTE(wsaData.wVersion)!=1 || HIBYTE(wsaData.wVersion)!=1) {
		pWSACleanup();
		return -1;
	}

	traceLog2( "TCPIO_Insert: ", "before returning 0." );
	
	return 0;
}

 extern "C" int _cdecl TCPIO_Remove(void)
{
	// Clean up Winsock 1.1
	WSACleanup();
	return 0;
}
