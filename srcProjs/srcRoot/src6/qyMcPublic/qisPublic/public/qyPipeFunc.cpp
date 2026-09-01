

#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<tchar.h>

#include	<stddef.h>
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>

#include	<WinSock2.h>
#include	<tchar.h>

#include	"qyCommonEx.h"

#include	"qysynccommproc.h"
#include	"genericQueue.h"
#include	"qyq2.h"

#include	"qycommproc.h"


#include	"qmOpenCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmcomm.h"
#include	"qnmCommProc.h"


//
#include	"qyPipeFunc.h"


//
//
__declspec(  dllexport  )  int  myConnectToNewClient(HANDLE hPipe, LPOVERLAPPED lpo,  BOOL  *  pfPendingIO  ) 
{ 
	int  iErr  =  -1;
   BOOL fConnected, fPendingIO = FALSE; 
 
// Start an overlapped connection for this pipe instance. 
   fConnected = ConnectNamedPipe(hPipe, lpo); 
 
// Overlapped ConnectNamedPipe should return zero. 
   if (fConnected) 
   {
      printf("ConnectNamedPipe failed with %d.\n", GetLastError()); 
      //  return 0;
	  goto  errLabel;
   }
 
   switch (GetLastError()) 
   { 
   // The overlapped connection in progress. 
      case ERROR_IO_PENDING: 
         fPendingIO = TRUE; 
         break; 
 
   // Client is already connected, so signal an event. 
 
      case ERROR_PIPE_CONNECTED: 
         if (SetEvent(lpo->hEvent)) 
            break; 
 
   // If an error occurs during the connect operation... 
      default: 
      {
         printf("ConnectNamedPipe failed with %d.\n", GetLastError());
         //  return 0;
		 goto  errLabel;
      }
   } 
 
   if  (  *pfPendingIO  )  *pfPendingIO  =  fPendingIO;

   iErr  =  0;
   
errLabel:
   return iErr; 
}



#if  0
int  closeRtspCliPipeThread(  VIDEO_capDev_rtsp  *  pRtsp  )
{
	int  iErr  =  -1;
	MC_VAR_common  *  pProcInfo  =  pRtsp->pProcInfoCommon;//QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	//
	int  i;
	
	pRtsp->pipe.bThreadQuit  =  TRUE;
	for  (  i  =  0;  ;  i  ++  )  {
		if  (  !pRtsp->pipe.hThread  )  break;		
		//
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "closeRtspCliPipeThread: wait for pipeThread,  %d"  ),  i  );	
		//
		SetEvent(  pRtsp->pipe.hEvent  );
		//
		waitForObject(  &pRtsp->pipe.hThread,  1000  );
	}
		
	return  0;
}
#endif

//
__declspec(  dllexport  )  int  closeQyPipeThread(  QY_pipe  *  pPipe  )
{
	int  iErr  =  -1;

	//
	int  i;
	
	pPipe->bThreadQuit  =  TRUE;
	for  (  i  =  0;  ;  i  ++  )  {
		if  (  !pPipe->hThread  )  break;		
		//
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "closeQyPipeThread: wait for pipeThread,  %d"  ),  i  );	
		//
		SetEvent(  pPipe->hEvent  );
		//
		waitForObject(  &pPipe->hThread,  1000  );
	}
		
	return  0;
}



//
#if  0
int  closeRtspCliPipe(  VIDEO_capDev_rtsp  *  pRtsp  )  
{
	 //
	 if  (  isHandleValid(  pRtsp->pipe.hPipe  )  )  {
		 //
		 BOOL  tmpbRet;
		 tmpbRet  =  CancelIo(  pRtsp->pipe.hPipe  );
		 //
#ifdef  __DEBUG__
		 showInfo_open0(  0,  0,  tmpbRet  ?  _T(  "closeRtspCliPipe: CancelIo true"  )  :  _T(  "closeRtspCliPipe: CancelIo false"  )  );
#endif
		 //
		 CloseHandle(  pRtsp->pipe.hPipe  );  pRtsp->pipe.hPipe  =  INVALID_HANDLE_VALUE;
	 }
	 if  (  isHandleValid(  pRtsp->pipe.hEvent  )  )  {
		 CloseHandle(  pRtsp->pipe.hEvent  );  pRtsp->pipe.hEvent  =  INVALID_HANDLE_VALUE;
	 }
	 return  0;
}
#endif



