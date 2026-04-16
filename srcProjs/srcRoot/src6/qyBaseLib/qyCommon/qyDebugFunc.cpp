


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#include	<WinSock2.h>
#include <windows.h>
#if  0
	#include <process.h>
#endif
#include "qyCommon.h"


 extern "C"  int  traceInfo(  void  *  pLogCtxParam,  char  *  fmt,  ...  )
{

#if  0
	
	#if  defined(__WITHOUT_DEBUG_LOG__)
		 return 0;
	#else

		va_list				args;
		char				buf[4096]			=	"";
		int					n					=	0;
		static	int			cnt					=	0;
		//  int					errnoBuf;
		DWORD				dwErr;
		QY_LOG_CTX		*	pLogCtx				=	(  QY_LOG_CTX  *  )pLogCtxParam;
		unsigned  char		ucbLogOn			=	TRUE;
		char			*	pFilePart			=	NULL;

		//  errnoBuf  =  errno;
		dwErr  =  GetLastError(  );

		if  (  pLogCtx  )  {
			ucbLogOn  =  pLogCtx->ucbLogOn;
			pFilePart  =  pLogCtx->filePart;
		}
		
		if  (  ucbLogOn  )	  {
 		
			va_start(  args,  fmt  );

			n	=	wvsprintf(  buf,  fmt, args  );
			if  (  n  >  sizeof(  buf  )  -  1  )  {
				traceLogEx(  pFilePart,  "traceLogA(  ):  buf too small to contain the output string."  );
				}
			else  {
				  traceLogEx(  pFilePart,  buf  );
			}
	
			va_end(  args  );
		
		}

		//  errno  =  errnoBuf; 
		SetLastError(  dwErr  );

  
		return 0;

	#endif
#endif
		return  0;
}


 //  2004/08/23¼Ó
 extern  "C"  int  traceInReg(  void  *  pLogCtxParam,  char  *  fmt,  ...  )
{
#if  0
		va_list				args;
		char				buf[4096]			=	"";
		int					n					=	0;
		DWORD				dwErr;
		QY_LOG_CTX		*	pLogCtx				=	(  QY_LOG_CTX  *  )pLogCtxParam;
		unsigned  char		ucbLogOn			=	TRUE;

		dwErr  =  GetLastError(  );

		if  (  !pLogCtx  )  return  -1;
		
		if  (  ucbLogOn  )	  {
 		
			va_start(  args,  fmt  );

			n	=	wvsprintf(  buf,  fmt, args  );
			if  (  n  >  sizeof(  buf  )  -  1  )  safeStrnCpy(  "traceInReg(  ):  buf too small to contain the output string.",  buf,  sizeof(  buf  )  );
			qySetRegCfgEx(  &pLogCtx->reg,  pLogCtx->regValName,  buf  );
			traceInfo(  pLogCtx,  "%s : %s",  pLogCtx->regValName,  buf  );
				
			va_end(  args  );
		
		}

		SetLastError(  dwErr  );

#endif
  
		return 0;

}
