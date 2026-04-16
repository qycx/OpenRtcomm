

#include	"stdafx.h"

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


#include	"qyCommCommon.h"
#include	"qmOpenCommon.h"
#include	"qyWmComm.h"
#include	"qnmCommProc.h"

#include	"qisPipe.h"
#include	"rtspUsrData.h"
#include	"qisMsg_open.h"

#include	"qisOnvifCommProc_open.h"





//
extern  "C"  __declspec(dllexport) BOOL  bQisPipeOk(  QIS_pipe  *  pQisPipe  )
{
	return  !pQisPipe->bQuit  &&  !pQisPipe->pipe.bThreadQuit  &&  !pQisPipe->status.ulbSessionErr;
}



//
DWORD  WINAPI  pipeThread_starter(LPVOID lpvParam) 
{ 
	QIS_pipe  *  pQisPipe  =  (  QIS_pipe  *  )lpvParam;
	QIS_pipe  *  pRtsp  =  (  QIS_pipe  *  )pQisPipe;
	//
	CQyMalloc	mallocObj;
	int  size_pMsg  =  CONST_bufSize_rtspCliPipe;
	RTSP_msg	*	pMsg	=	(  RTSP_msg  *  )mallocObj.mallocf(  size_pMsg  );
	if  (  !pMsg  )  return  -1;
	if  (  sizeof(  RTSP_msg  )  >  size_pMsg  )  {
		showInfo_open0(  0,  0,  _T(  "pipeThread_starter failed, size_pMsg too small"  )  );
		return  -1;
	}


	
	//
	int			index	=	0;
	DWORD		dwRet;
	DWORD		cbBytesRead;
	//

	CTX_pipeThread  ctx  =  {0};
	TCHAR  tBuf[128]  =  _T(  ""  );


	//
#ifdef  __DEBUG__
		traceLogA(  "pipeThread_starter enters"  );
#endif
		showInfo_open0(0,pQisPipe->name,_T(  "pipeThread_starter starts"  )  );

	//
	pQisPipe->status.ulbSessionErr  =  FALSE;


	//
	ctx.pQisPipe  =  pQisPipe;
	//
	ctx.hEvent_write  =  CreateEvent(  NULL,  FALSE,  FALSE,  FALSE  );		
	if  (  !ctx.hEvent_write  )  goto  errLabel;
	
	//
	DWORD  dwThreadId;

	// Create a thread for this client. 	
	ctx.hThread_write = CreateThread( 
            NULL,						// no security attribute 
            0,							// default stack size 
            pipeThread_write,				// thread proc
			(LPVOID)&ctx,				// thread parameter 
            CREATE_SUSPENDED,           // not suspended 
            &dwThreadId);				// returns thread ID 
	if  (  ctx.hThread_write == NULL) {
		  printf("CreateThread failed"); 
		  goto  errLabel;
	  }         
	  ctx.dwThreadId  =  dwThreadId;
	  ResumeThread(  ctx.hThread_write  );


 
	// The thread's parameter is a handle to a pipe instance.  
	while  (   bQisPipeOk(  pRtsp  )  )  { 

		   OVERLAPPED  overlapStruct;
		   memset(  &overlapStruct,  0,  sizeof(  overlapStruct  )  );
		   overlapStruct.hEvent  =  pRtsp->pipe.hEvent;

		   // Read client requests from the pipe. 
		   ReadFile( 
			   pRtsp->pipe.hPipe,        // handle to pipe 
			   pMsg,    // buffer to receive data 
			   size_pMsg, // size of buffer 
			   &cbBytesRead, // number of bytes read 
			   &overlapStruct  );        // not overlapped I/O 
 
		   for  (  ;  ;  )  {
			    if  (  !bQisPipeOk(  pRtsp  )  )  goto  errLabel;
				dwRet  =  WaitForSingleObject(  pRtsp->pipe.hEvent,  2000  );
				if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
				if  (  dwRet  ==  WAIT_TIMEOUT  )  continue;
				break;
		   }
		   //  2015/06/22
		   if  (  !bQisPipeOk(  pRtsp  )  )  goto  errLabel;
		   
		   //
		   DWORD	dwByte;
		   if  (  !GetOverlappedResult(  pRtsp->pipe.hPipe,  &overlapStruct,  &dwByte,  TRUE  )  )  {
			   #ifdef  __DEBUG__
					   traceLog(  _T(  "pipeThread failed, GetOverlappedResult failed"  )  );
			   #endif
			   goto  errLabel;
		   }
		   
		   //		   		  
		   //
		   int  iType  =  *(  int  *  )pMsg;
		   switch  (  iType  )  {
				   case  CONST_qisMsgType_rtsp:  {
					     
					     //  
					     if  (  dwByte  <  offsetof(  RTSP_msg,  buf  )  )  {
							 TCHAR  tBuf[128];			   
							 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "pipeThread: serious err: dwByte %d err. should be > offsetof(  RTSP_msg,  buf  ) %d"  ),  dwByte,  offsetof(  RTSP_msg,  buf  )  );
						     #ifdef  __DEBUG__					   
									 traceLog(  _T(  "%s"  ),  tBuf  );
							 #endif
							 showInfo_open0(  0,  0,  tBuf  );			   
							 //			   
							 goto  errLabel;		   
						 }

					     #ifdef  __DEBUG__		   
								 //		   
		   
								 char  b222[128];		   
								 int  len  =  min(  pMsg->uiLen,  sizeof(  b222  )  );		   
								 memcpy(  b222,  pMsg->buf,  len  );		   
								 b222[sizeof(  b222  )  -  1]  =  0;		   
								 //  traceLogA(  "read from pipe %d bytes",  dwByte  );		   
								 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "read from pipe %d bytes. [%S]"  ),  dwByte,  b222  );		   
								 showInfo_open0(  0,  0,  tBuf  );

						 #endif

						 //
						 }
						 break;
				   case  CONST_qisMsgType_onvif:
						 #if  0
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "pipeThread_cli: unprocessed, onvifMsg"  )  );
							  showInfo_open0(  0,  0,  tBuf  );					     
						 #endif
						 //
					     break;
				   default:
					       _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "pipeThread_cli: unprocessed msgType %d"  ),  iType  );
						   showInfo_open0(  0,  0,  tBuf  );
						   break;			
		   }

		   
		   //  2016/06/29		   
		   if  (  pQisPipe->param.pf_onRead  )  {
			   pQisPipe->param.pf_onRead(  pQisPipe,  pMsg,  dwByte,  pQisPipe->param.p0,  pQisPipe->param.p1  );
		   }
		   		   	   	   

		   //
		   continue;

	} 
 
// Flush the pipe to allow the client to read the pipe's contents 
// before disconnecting. Then disconnect the pipe, and close the 
// handle to this pipe instance. 
 
errLabel:

	//
	showInfo_open0(  0,  pRtsp->name,  _T(  "pipeThread_starter: start to quit"  )  );

	//
	pRtsp->status.ulbSessionErr  =  TRUE;
	
	//
	MACRO_qyNullThread(  ctx.hThread_write  );		
	//
	showInfo_open0(  0,  pRtsp->name,  _T(  "Function starter is closed"  )  );							   
	
	//
	if  (  isHandleValid(  ctx.hEvent_write  )  )  {
		CloseHandle(  ctx.hEvent_write  );  ctx.hEvent_write  =  NULL;
	}

	//
	BOOL  tmpbRet;
	tmpbRet  =  CancelIo(  pRtsp->pipe.hPipe  );
	//
	if  (  pRtsp->cfg.bStarter  )  {
		DisconnectNamedPipe(  pRtsp->pipe.hPipe  ); 
	}
	
	//
#ifdef  __DEBUG__
		showInfo_open0(  0,  0,  tmpbRet  ?  _T(  "pipeThread: CancelIo true"  )  :  _T(  "pipeThread: CancelIo false"  )  );
#endif


	traceLogA(  "pipeThread_starter leaves"  );
	showInfo_open0(0,pQisPipe->name,_T(  "pipeThread_starter leaves"  )  );


	return  1;
}

//
DWORD  WINAPI  pipeThread_write(LPVOID lpvParam) 
{ 
	CTX_pipeThread  *  pCtx  =  (  CTX_pipeThread  *  )lpvParam;
	QIS_pipe  *  pQisPipe  =  (  QIS_pipe  *  )pCtx->pQisPipe;

	//
	CQyMalloc	mallocObj;
	//  TCHAR		chRequest[CONST_bufSize_rtspCliPipe]; 
	int  iBUFSIZE  =  CONST_bufSize_rtspCliPipe;
	RTSP_msg	*	pMsg	=	(  RTSP_msg  *  )mallocObj.mallocf(  iBUFSIZE  );
	if  (  !pMsg  )  return  -1;
	int  len;
	
	//
	HANDLE  hEvent_write  =  pCtx->hEvent_write;
	
	
	//
	int  iSize  =  0;
	
	
	//
	int			index	=	0;
	DWORD		dwRet;
	DWORD		cbWritten;
	TCHAR		tBuf[128];

	//
	bool  bDbg = false;

	//
#ifdef  __DEBUG__
		traceLogA(  "pipeThread_write enters"  );
#endif
		if (bDbg) {
			showInfo_open0(0, pQisPipe->name, _T("pipeThread_write starts"));
		}

 
	// The thread's parameter is a handle to a pipe instance. 
 
	while  (   bQisPipeOk(  pQisPipe  )  )  { 

		   //
		   if  (  isQ2Empty(  &pQisPipe->outputQ2  )  )  {			  

              dwRet  =  WaitForSingleObject(  pQisPipe->outputQ2.hEvents[0],  3500  );	//  µÈ·¢ËÍÖ¸Áî
			  if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;							//  ÎªÁË·ÀÖ¹¶ª°ü£¬ÕâÀï²»ÅÐ¶Ï³¬Ê±£¬ÒÔoutputQÀïµÄÊý¾Ý°üÎª×¼
			  if  (  dwRet  ==  WAIT_TIMEOUT  )  continue;								//  Ã»ÓÐÈË´¥·¢£¬ËùÒÔ³¬Ê±
			  #ifdef  __DEBUG__
					  //  traceLog(  _T(  "snd: sth waited"  )  );
			  #endif		  
		   }		  
		  
		   //
		   while  (  bQisPipeOk(  pQisPipe  )  )  {

			      //  
			      len  =  sizeof(  pMsg[0]  );
				  if  (  q2GetMsg(  &pQisPipe->outputQ2,  pMsg,  (  unsigned  int  *  )&len,  _T(  "pipeThread_write"  )))  break;
				  		
				  if  (  len  <  sizeof(  int  )  )  {
					  showInfo_open0(  0,  0,  _T(  "pipeThread_write: get a err msg: msgLen too small < sizeof(  int  )"  )  );
					  break;
				  }
				  int  msgLen  =  len;
		   		  
				  //
				  OVERLAPPED  overlapStruct;
				  memset(  &overlapStruct,  0,  sizeof(  overlapStruct  )  );
				  overlapStruct.hEvent  =  hEvent_write;
				  		   
				  // Read client requests from the pipe. 
				  WriteFile( 
					  pQisPipe->pipe.hPipe,        // handle to pipe 
					  pMsg,    // buffer to receive data 
					  msgLen, // size of buffer 
					  &cbWritten, // number of bytes read 
					  &overlapStruct  );        // not overlapped I/O 
 
				  //
				  for  (  ;  ;  )  {
					
					  if  (  !bQisPipeOk(  pQisPipe  )  )  goto  errLabel;
					  dwRet  =  WaitForSingleObject(  hEvent_write,  2000  );
					  if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
					  if  (  dwRet  ==  WAIT_TIMEOUT  )  continue;
					  break;		   
				  }
				  //  2015/06/22
				  if  (  !bQisPipeOk(  pQisPipe  )  )  goto  errLabel;
		   
				  //		   
				  DWORD	dwBytes;
				  if  (  !GetOverlappedResult(  pQisPipe->pipe.hPipe,  &overlapStruct,  &dwBytes,  TRUE  )  )  {
					  #ifdef  __DEBUG__
							  traceLog(  _T(  "pipeThread failed, GetOverlappedResult failed"  )  );
					  #endif
					  //			   
					  goto  errLabel;		   
				  }
		   
				  //  if  (  cbBytes		   
				  if  (  dwBytes  !=  msgLen  )  {			   
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "pipeThread: serious err: dwByte %d err. should be == msgLen %d"  ),  dwBytes,  msgLen  );
					  #ifdef  __DEBUG__
							  traceLog(  _T(  "%s"  ),  tBuf  );
					  #endif
					  showInfo_open0(  0,  0,  tBuf  );			   
					  //			   
					  goto  errLabel;		   
				  }

				  //
				  #ifdef  __DEBUG__
						  //
						  if  (  pQisPipe->param.bPrint_write  )  {
						  char  b222[128]  =  "";
						  //safeStrnCpy(  pMsg->buf,  b222,  mycountof(  b222  )  );
						  int tn = 0;
						  OnvifMsg_common* p = (OnvifMsg_common*)pMsg;
						  tn = p->uiTranNo;
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "pipeThread_write: %s, %d bytes sent, [%S], tn %d"  ),  pQisPipe->name,  dwBytes,  b222,  tn  );				   
						  showInfo_open0(  0,  0,  tBuf  );
						  }
				  #endif
						  

				  //
				  continue;
		   }
		   
		   //
		   continue;
	} 
 
// Flush the pipe to allow the client to read the pipe's contents 
// before disconnecting. Then disconnect the pipe, and close the 
// handle to this pipe instance. 
 
errLabel:

	//
	if (bDbg) {
		showInfo_open0(0, pQisPipe->name, _T("pipeThread_write: start to quit"));
	}

	//
#ifdef  __DEBUG__
		traceLogA(  "pipeThread_write leaves"  );
#endif
		if (bDbg) {
			showInfo_open0(0, pQisPipe->name, _T("pipeThread_write leaves"));
		}

		//
	return  1;
}


//
int  doPipe_starter(  QIS_pipe  *  pPipe  )
{
	int  iErr	=	-1;

	QIS_pipe  *  pRtsp  =  pPipe;
	
#if  10
	
		 
#ifdef  __DEBUG__
		  traceLog(  _T(  "start rtsp session"  )  );
#endif

		  //
		  int  iBUFSIZE  =  CONST_bufSize_rtspCliPipe;

		  //
		  TCHAR  pipeName[128];
		  if  (  !isHandleValid(  pRtsp->pipe.hPipe  )  )  {
			  //pRtsp->tn_rtspCliPipe  =  getuiNextTranNo(  0,  0,  0  );
			  //  _sntprintf(  pipeName,  mycountof(  pipeName  ),  _T(  "%s%d"  ),  CONST_rtspCliPipePrefix,  pRtsp->tn_rtspCliPipe  );
			  //M_get_pipeName(  CONST_rtspCliPipePrefix,  pProcInfo->get_appObjPrefix(  ),  pRtsp->tn_rtspCliPipe,  pipeName  );
			  safeTcsnCpy(  pRtsp->cfg.pipeName,  pipeName,  mycountof(  pipeName  )  );

			  pRtsp->pipe.hPipe  =  CreateNamedPipe( 
							          pipeName,             // pipe name 
									  PIPE_ACCESS_DUPLEX  |  FILE_FLAG_OVERLAPPED,       // read/write access 
									  PIPE_TYPE_MESSAGE  |  PIPE_READMODE_MESSAGE  |  PIPE_WAIT,                // // message type pipe , message-read mode , blocking mode 
									  PIPE_UNLIMITED_INSTANCES, // max. instances  
									  iBUFSIZE,                  // output buffer size 
									  iBUFSIZE,                  // input buffer size 
									  1000,                        // client time-out 
									  NULL);                    // default security attribute 

			  if  (  pRtsp->pipe.hPipe  ==  INVALID_HANDLE_VALUE  )  goto  errLabel;

		  }

		  if  (  !isHandleValid(  pRtsp->pipe.hEvent  )  )  {
		  		pRtsp->pipe.hEvent  =  CreateEvent(  NULL,  FALSE,  FALSE,  FALSE  );
				if  (  !pRtsp->pipe.hEvent  )  goto  errLabel;
		  }
		  
		  


		  //  		  		
		  OVERLAPPED  overlapStruct;
		  memset(  &overlapStruct,  0,  sizeof(  overlapStruct  )  );
		  overlapStruct.hEvent  =  pRtsp->pipe.hEvent;
 
		  //  ConnectNamedPipe( pRtsp->pipe.hPipe, &overlapStruct);
		  BOOL  fPendingIO  =  FALSE;
		  if  (  myConnectToNewClient(  pRtsp->pipe.hPipe,  &overlapStruct,  &fPendingIO  )  )  goto  errLabel;
		  
		  //
		  DWORD  dwRet;
		  for  (  ;  ;  )  {
			 if  (  pRtsp->bQuit  )  goto  errLabel;
			 //
			 //  2016/04/07
			 int  cnt_events  =  0;
			 HANDLE  hEvents[2]  =  {0};
			 hEvents[0]  =  pRtsp->pipe.hEvent;
			 hEvents[1]  =  pRtsp->hEvent_syncThreadQuit_recvRtsp;
			 cnt_events  =  2;			 //
			 //dwRet  =  WaitForSingleObject(  pRtsp->pipe.hEvent,  2000  );
			 dwRet  =  WaitForMultipleObjects(  cnt_events,  hEvents,  FALSE,  2000  );  
			 //
			 if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
			 if  (  dwRet  ==  WAIT_TIMEOUT  )  {
#ifdef  __DEBUG__
				 traceLog(  _T(  "wait for being connected"  )  );
#endif

				 continue;
			 }
			 //
			 dwRet -= WAIT_OBJECT_0;
			 switch  (  dwRet  )  {
					 case  0:
						    break;
					 case  1:
						   showInfo_open0(  0,  0,  _T(  "doRecvRtsp: event_quit waited"  )  );
						   goto  errLabel;
						   break;
					 default:
						    showInfo_open0(  0,  0,  _T(  "doRecvRtsp: unknown event waited"  )  );
							goto  errLabel;
			 }
			 //
			 break;		
		  }
		  
		  //
		  DWORD	dwByte;
		  if  (  !GetOverlappedResult(  pRtsp->pipe.hPipe,  &overlapStruct,  &dwByte,  TRUE  )  )  goto  errLabel;

		  DWORD  dwThreadId;
		  //
		  pRtsp->pipe.bThreadQuit  =  FALSE;
		  // Create a thread for this client. 
		  pRtsp->pipe.hThread = CreateThread( 
            NULL,						// no security attribute 
            0,							// default stack size 
            pipeThread_starter,				// thread proc
			(LPVOID)pRtsp,				// thread parameter 
            CREATE_SUSPENDED,           // not suspended 
            &dwThreadId);				// returns thread ID 
	  if  (  pRtsp->pipe.hThread == NULL) {
		  printf("CreateThread failed"); 
		  goto  errLabel;
	  }         
	  pRtsp->pipe.dwThreadId  =  dwThreadId;
	  ResumeThread(  pRtsp->pipe.hThread  );

	  //
	  for  (  ;  ;  )  {
		   if  (  pRtsp->bQuit  )  goto  errLabel;
		   //
		   waitForObject(  &pRtsp->pipe.hThread,  0  );
		   if  (  !pRtsp->pipe.hThread  )  break;
		   //
		   //
		   //  这里可能用来写指令到rtspCli.比如云台等
		   ///
		   //Sleep(  2000  );
		   dwRet  =  WaitForSingleObject(  pRtsp->hEvent_syncThreadQuit_recvRtsp,  2000  );
		   if  (  dwRet  ==  WAIT_TIMEOUT  )  {
			   #ifdef  __DEBUG__
					   //showInfo_open0(  0,  0,  _T(  "doRecvRtsp: waitFor hEvent_syncThreadQuit_recvRtsp timeout"  )  );
			   #endif
		   }
	  }

	  //
	  closeQyPipeThread(  &pRtsp->pipe  );



	  //  2015/05/09
	  iErr  =  0;
	 



errLabel:

	 //
	 closeQyPipeThread(  &pRtsp->pipe  );
	 //
	 closeQyPipe(  &pRtsp->pipe  );

#endif

	 //
	return  iErr;

}


//
extern "C" DWORD WINAPI mcThreadProc_qisPipe_starter( LPVOID lpParameter )
{
	 //  VIDEO_capDev_rtsp  *  pRtsp  =  (  VIDEO_capDev_rtsp  *  )lpParameter;
	QIS_pipe  *  pRtsp  =  (  QIS_pipe  *  )lpParameter;

	 //MC_VAR_common					*	pProcInfo					=	(  MC_VAR_common  *  )pRtsp->pProcInfoCommon;//QY_GET_procInfo_isCli(  );
	 //if (  !pProcInfo  )  return  -1;	 

	 //QY_MC							*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;
	 //DYN_LIB_DX						*	pDynLib						=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	 //  int								i;


	 #define		DEFAULT_dwToInMs		5000
	 DWORD								dwToInMs					=	DEFAULT_dwToInMs;

	 DWORD								dwTickCnt_lastAudioData		=	GetTickCount(  );;						// 

	 //  2014/03/15

#ifdef  __DEBUG__
	 traceLogA(  "mcThreadProc_qisPipe_recv enters"  );
#endif

	 /*
	 for  (  i  =  0;  i  <  mycountof(  pDispatchAudio->hEvents  );  i  ++  )  {
		  pDispatchAudio->hEvents[i] = CreateEvent( NULL, FALSE, FALSE, NULL );
		  if ( NULL == pDispatchAudio->hEvents[i] ) goto  errLabel;
	 }
	 */

	 pRtsp->bRunning  =  TRUE;
	 //  memset(  &pDispatchAudio->m_var,  0,  sizeof(  pDispatchAudio->m_var  )  );


	 //
	int  dwToInMs_rtsp  =  3000;

	 //
	 for  (  ;  !pRtsp->bQuit;  )  {

		 //
		 doPipe_starter(  pRtsp  );
		 
		 //
		 //  放慢一点点
		 Sleep(  200  );
	 }



	 //
errLabel:


	 //
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s ends."  ),  _T(  "mcThreadProc_qisPipe_starter"  )  );
	 

	 pRtsp->bRunning  =  FALSE;


	 traceLogA(  "mcThreadProc_qisPipe_recv %S leaves",  _T(  "rtsp"  )  );

	return  0;
}


