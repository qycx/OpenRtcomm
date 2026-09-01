
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#include	<WinSock2.h>
#include	<windows.h>
#include	<tchar.h>

#if  0
	#include <unistd.h>
	#include "process.h"
	#include <sys/types.h>
	#include <sys/stat.h>
#endif


#include "qyCommon.h"

#include <stdio.h>



#if  0
 extern "C" int qyGetFileSize(  char * fileName )
{
   struct _stat buf;
   int result;

   result = _stat( fileName, &buf );

   if ( result != 0 )  return  -1;

   return  buf.st_size;
}
#endif

 extern "C" int qyGetFileSize(  LPCTSTR fileName )
{
	int		iErr		=	-1;
	HANDLE	hFile		=	NULL;
	DWORD	dwFileSize	=	0;

	hFile  =  CreateFile(  fileName,  GENERIC_READ,  0,  NULL,  OPEN_EXISTING,  0,  NULL  );
	if  (  hFile  ==   INVALID_HANDLE_VALUE  )  goto  errLabel;

	dwFileSize =   GetFileSize(  hFile,  NULL  );

	iErr  =  0;

errLabel:
	if  (  isHandleValid(  hFile  )  )  CloseHandle(  hFile  );
	return  iErr  ?  iErr  :  dwFileSize;
 }

 extern  "C"  char * qyStatusStr(  unsigned  char  ucStatus,  char  *  buf,  int  size  )
{
	if  (  size  <=  2  )	return  "";
	sprintf(  buf,  "%02x",  ucStatus  );
	return  buf;
}
