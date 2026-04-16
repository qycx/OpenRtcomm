

#include	"stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>
#include	<stddef.h>
#include	<mmsystem.h>

#include	"qdcOpenCommon.h"
#include	"qyPipeFunc_open.h"




//
int  closeQyPipe(  QY_pipe  *  pPipe  )  
{
	 //
	 if  (  isHandleValid_open(  pPipe->hPipe  )  )  {
		 //
		 BOOL  tmpbRet;
		 tmpbRet  =  CancelIo(  pPipe->hPipe  );
		 //
#ifdef  __DEBUG__
		 showInfo_open0(  0,  0,  tmpbRet  ?  _T(  "closeRtspCliPipe: CancelIo true"  )  :  _T(  "closeRtspCliPipe: CancelIo false"  )  );
#endif
		 //
		 CloseHandle(  pPipe->hPipe  );  pPipe->hPipe  =  INVALID_HANDLE_VALUE;
	 }
	 if  (  isHandleValid_open(  pPipe->hEvent  )  )  {
		 CloseHandle(  pPipe->hEvent  );  pPipe->hEvent  =  INVALID_HANDLE_VALUE;
	 }
	 return  0;
}



//  2016/06/20
int  cli_chkQyPipe(  LPCTSTR  pipeName,  BOOL  bOverlapped,  QY_pipe  *  pPipe  )
 {
	 int  iErr  =  -1;

	 BOOL  fSuccess;

	 //
	 if  (  !pipeName  ||  !pipeName[0]  )  return  -1;
	 if  (  !pPipe  )  return  -1;

	 //
	 if  (  !isHandleValid_open(  pPipe->hPipe  )  )  {	
		//
		//TCHAR	pipeName[256];
		//int  tn_rtspCliPipe  =  0;
		//  _sntprintf(  pipeName,  mycountof(  pipeName  ),  _T(  "%s%d"  ),  CONST_rtspCliPipePrefix,  pGBuf->tn_rtspCliPipe  );
		//M_get_pipeName(  CONST_rtspCliPipePrefix,  pGBuf->appObjPrefix,  pGBuf->tn_rtspCliPipe,  pipeName  );

		//
		DWORD  dwFlagsAndAttributes  =  0;
		if  (  bOverlapped  )  {
			dwFlagsAndAttributes  =  FILE_FLAG_OVERLAPPED ;
		}

		//
		pPipe->hPipe = CreateFile( 
							pipeName,						// pipe name 
							GENERIC_READ |					// read and write access 
							GENERIC_WRITE, 
							0,								// no sharing 
							NULL,							// default security attributes
							OPEN_EXISTING,					// opens existing pipe 
							dwFlagsAndAttributes,           // default attributes 
							NULL);							// no template file   						
		if (  pPipe->hPipe == INVALID_HANDLE_VALUE  )  {
#ifdef  _DEBUG
			OutputDebugString(  _T(  "BufferCB_rtspCli failed: CreateFile failed\n"  )  );
#endif
			goto  errLabel;
		}

		
		//traceLogA(  "showInfoThreadProc: pipe created"  );
		DWORD  dwMode = PIPE_READMODE_MESSAGE; 
		fSuccess  = SetNamedPipeHandleState( 
							pPipe->hPipe,    // pipe handle 
							&dwMode,  // new pipe mode 
							NULL,     // don't set maximum bytes 
							NULL);    // don't set maximum time 					
		if (!fSuccess)  {
							//  qyDisplayLastError(  "SetNamedPipeHandleState failed"  ); 							
			goto  errLabel;						
		} 

	}

	 //
	 if  (  !isHandleValid_open(  pPipe->hEvent  )  )  {		  	
		 pPipe->hEvent  =  CreateEvent(  NULL,  FALSE,  FALSE,  FALSE  );				
		 if  (  !pPipe->hEvent  )  goto  errLabel;		
	 }


	 iErr  =  0;
errLabel:

	 //
	 if  (  iErr  )  {
#if  0
	 	if  (  pPipe->hPipe  !=  INVALID_HANDLE_VALUE  )  {
			CloseHandle(  pPipe->hPipe  );  pPipe->hPipe  =  NULL;
		}
#endif
		//
		closeQyPipe(  pPipe  );
	 }

	 return  iErr;
 }
