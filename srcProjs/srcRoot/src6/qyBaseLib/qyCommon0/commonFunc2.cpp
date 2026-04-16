
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#ifndef WIN32
 //  #include <unistd.h>
#endif
#include <ctype.h>

#ifdef WIN32
 #include <windows.h>
#endif
#include	<tchar.h>

#include "commonDefs.h"
#include "qyCommon\\commonFunc.h"
#include "qyCommon\\commonFunc1.h"


#define MAX_ARGS	256
 
 int myArgc = 0;
 char *myArgv[MAX_ARGS];

 extern "C" int getArgcv( char *prog, char *lpCmdLine )
{
	if ( myArgc ) return -1;

	myArgv[myArgc] = prog;
	myArgc ++;
	
	while ( *lpCmdLine ) {
		if ( isascii( *lpCmdLine ) && isspace( *lpCmdLine ) ) lpCmdLine ++;

		myArgv[myArgc] = lpCmdLine;
		myArgc ++;
		lpCmdLine ++;
		while ( !isascii( *lpCmdLine ) || ( !isspace( *lpCmdLine ) && *lpCmdLine ) )
			lpCmdLine ++;
		if ( *lpCmdLine ) {
			*lpCmdLine = '\0'; lpCmdLine ++;
		}
		
		if ( myArgc == MAX_ARGS ) break;	// Only MAX_ARGS arguments can be allowed.
	}
	 
	return 0;

}


