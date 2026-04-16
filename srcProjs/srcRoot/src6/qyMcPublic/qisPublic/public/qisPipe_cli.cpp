

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
#include <ctxQmThread.h>




//
#ifdef  __DEBUG__
int  iidoPipe_cli(  QIS_pipe  *  pPipe  )
{
	int  iErr	=	-1;

	QIS_pipe  *  pRtsp  =  pPipe;
	
	//
	CQyMalloc  mallocObj;
	int  size  =  sizeof(  RTSP_msg  );
	RTSP_msg  *  pRTSP_msg  =  (  RTSP_msg  *  )mallocObj.mallocf(  size  );
	if  (  !pRTSP_msg  )  return  -1;

	//
	BOOL  bOverlapped  =  FALSE;

	//
	if  (  cli_chkQyPipe(  pPipe->cfg.pipeName,  bOverlapped,  &pPipe->pipe  )  )  {
		goto  errLabel;
	}

	//
	for  (  ;  !pPipe->bQuit;  )  {
		Sleep(  1000  );
		//
		//WriteFile...
		
	if  (  !pRTSP_msg  )  goto  errLabel;
	RTSP_msg  &	msg  =  *(  RTSP_msg  *  )pRTSP_msg;
	memset(  &msg,  0,  offsetof(  RTSP_msg,  buf  )  );

	//
	unsigned  char   *  pBuffer  =  (  unsigned  char  *  )(  "hello, I am trump"  );
	int  BufferLen  =  strlen(  (  char  *  )pBuffer  );
	BOOL  fSuccess;



	//
#if  0
	msg.iMediumType  =  iMediumType;
	msg.iCodecType  =  iCodecType;
	msg.iSampleTimeInMs  =  iSampleTimeInMs;
	msg.uiPts  =  uiPts;				//  2015/02/09
	//
	msg.iDataType  =  iDataType;		//  2015/10/16
	//
	msg.bSpsPps  =  bSpsPps;
	msg.index_spsPps  =  index_spsPps;
	msg.bFinished_spsPps  =  bFinished_spsPps;
	//
	msg.bNeedResp  =  bNeedResp;		//  2015/01/30
	//  2015/02/24
	msg.dwTickCnt_doPretrans  =  pRes->dwTickCnt_doPretrans;	//  2015/02/24
#endif
	//
	if  (  BufferLen  >  sizeof(  msg.buf  )  )  goto  errLabel;
	if  (  !(  pBuffer  ==  (  unsigned  char  *  )msg.buf  &&  BufferLen  ==  msg.uiLen  )  )  {	
		memcpy(  msg.buf,  pBuffer,  BufferLen  );
		msg.uiLen  =  BufferLen;
	}
	//
	int  msgLen  =  offsetof(  RTSP_msg,  buf  )  +  msg.uiLen;
						
	DWORD  cbWritten  =  0;
	//
	fSuccess = WriteFile( 
						pPipe->pipe.hPipe,                  // pipe handle 
						&msg,             // message 
						msgLen, // message length 
						&cbWritten,             // bytes written 
						NULL);                  // not overlapped 
	
	if  (  !fSuccess  )  {		
		//traceLogA("WriteFile failed"); 	
		goto  errLabel;	
	}
	if  (  cbWritten  !=  msgLen  )  {
#ifdef  __DEBUG__
		traceLog(  _T(  "BufferCB_rtspCli: WriteFile err, cbWritten err"  )  );
#endif
		goto  errLabel;
	}	

	}



	iErr  =  0;
errLabel:

	//
	closeQyPipe(  &pPipe->pipe  );


	return  iErr;

}
#endif

//
DWORD  WINAPI  pipeThread_cli(LPVOID lpvParam) 
{ 
	QIS_pipe  *  pQisPipe  =  (  QIS_pipe  *  )lpvParam;
	QIS_pipe  *  pRtsp  =  (  QIS_pipe  *  )pQisPipe;
	//
	CQyMalloc	mallocObj;
	//  TCHAR		chRequest[CONST_bufSize_rtspCliPipe]; 
	int  size_pMsg  =  CONST_bufSize_rtspCliPipe;
	RTSP_msg	*	pMsg	=	(  RTSP_msg  *  )mallocObj.mallocf(  size_pMsg  );
	if  (  !pMsg  )  return  -1;
	if  (  sizeof(  RTSP_msg  )  >  size_pMsg  )  {
		showInfo_open0(  0,  0,  _T(  "pipeThread_cli failed, size_pMsg too small"  )  );
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
		traceLogA(  "pipeThread_cli enters"  );
#endif
		showInfo_open0(0,pQisPipe->name,_T(  "pipeThread_cli starts"  )  );

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

	  //
	  DWORD  dwlastTickCnt_read;
	  dwlastTickCnt_read = myGetTickCount(nullptr);

 
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
			    if  (  !bQisPipeOk(  pRtsp  )  )  {
					showInfo_open0(0, 0, _T("pipeThread_cli: bQisPipeOk false, goto  errlabel"));
					goto  errLabel;					
				}
				//
				if (pQisPipe->param.uiMaxToInMs_read) {
					DWORD dwTickCnt = myGetTickCount(nullptr);
					int iDiffInMs = dwTickCnt - dwlastTickCnt_read;
					if (abs(iDiffInMs) > pQisPipe->param.uiMaxToInMs_read) {
						//
						TCHAR  tBuf[128];
						_sntprintf(  tBuf,  mycountof( tBuf),  _T("pipeThread_isCli break. %s haven't read too long. %dms"),  pQisPipe->name,  iDiffInMs);
						traceLog(tBuf);
						showInfo_open0(0, 0, tBuf);
						//
						goto  errLabel;
					}
				}
				//
				dwRet  =  WaitForSingleObject(  pRtsp->pipe.hEvent,  2000  );
				if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
				if  (  dwRet  ==  WAIT_TIMEOUT  )  continue;
				break;
		   }
		   //  2015/06/22
		   if (!bQisPipeOk(pRtsp)) {
			   showInfo_open0(0, 0, _T("pipeThread_cli.244: bQisPipeOk false, goto  errlabel"));
			   goto  errLabel;
		   }
		   
		   //
		   DWORD	dwByte;
		   if  (  !GetOverlappedResult(  pRtsp->pipe.hPipe,  &overlapStruct,  &dwByte,  TRUE  )  )  {
			   DWORD  dwErr  =  GetLastError();
			   #ifdef  __DEBUG__
			   _sntprintf(tBuf, mycountof(tBuf), _T("pipeThread failed, GetOverlappedResult failed, GetLastError returns %d"), dwErr);
					   traceLog(  tBuf  );
					   showInfo_open0(0, 0, tBuf);
			   #endif
			   goto  errLabel;
		   }
		   
		   //
		   if  (  dwByte  <  sizeof(  int  )  )  {
			   showInfo_open0(  0,  0,  _T(  "pipeThread_cli err: read too small bytes < sizeof(  int  )"  )  );
			   continue;
		   }

		   //
		   dwlastTickCnt_read = myGetTickCount(nullptr);

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
	showInfo_open0(  0,  pRtsp->name,  _T(  "pipeThread_cli: start to quit"  )  );

	//
	pRtsp->status.ulbSessionErr  =  TRUE;
	
	//
	MACRO_qyNullThread(  ctx.hThread_write  );		
	//
	showInfo_open0(0,pRtsp->name,_T(  "Function cli is closed"  )  );							   
	
	//
	if  (  isHandleValid(  ctx.hEvent_write  )  )  {
		CloseHandle(  ctx.hEvent_write  );  ctx.hEvent_write  =  NULL;
	}

	//
	BOOL  tmpbRet;
	tmpbRet  =  CancelIo(  pRtsp->pipe.hPipe  );
	
	//
#ifdef  __DEBUG__
		showInfo_open0(  0,  pRtsp->name,  tmpbRet  ?  _T(  "pipeThread: CancelIo true"  )  :  _T(  "pipeThread: CancelIo false"  )  );
#endif


	traceLogA(  "pipeThread_cli leaves"  );
	showInfo_open0(0,pRtsp->name,_T(  "pipeThread_cli leaves"  )  );


	return  1;
}


//
int  doPipe_cli(  QIS_pipe  *  pPipe  )
{
	int  iErr	=	-1;

	QIS_pipe  *  pRtsp  =  pPipe;
	
	//
	CQyMalloc  mallocObj;
	int  size  =  sizeof(  RTSP_msg  );
	RTSP_msg  *  pRTSP_msg  =  (  RTSP_msg  *  )mallocObj.mallocf(  size  );
	if  (  !pRTSP_msg  )  return  -1;

	//
	BOOL  bOverlapped  =  FALSE;
	bOverlapped  =  TRUE;

	//
	if  (  cli_chkQyPipe(  pPipe->cfg.pipeName,  bOverlapped,  &pPipe->pipe  )  )  {
		goto  errLabel;
	}

	//
	DWORD  dwRet;

	//
	//for  (  ;  !pPipe->bQuit;  )  
	{


		//
				  DWORD  dwThreadId;
		  //
		  pRtsp->pipe.bThreadQuit  =  FALSE;
		  // Create a thread for this client. 
		  pRtsp->pipe.hThread = CreateThread( 
            NULL,						// no security attribute 
            0,							// default stack size 
            pipeThread_cli,				// thread proc
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



	}



	iErr  =  0;
errLabel:

	//  2016/08/03
	if  (  isHandleValid(  pRtsp->outputQ2.hEvents[0]  )  )  {
		SetEvent(  pRtsp->outputQ2.hEvents[0]  );
	}
	
	//	 
	closeQyPipeThread(  &pRtsp->pipe  );

	//
	closeQyPipe(  &pPipe->pipe  );


	return  iErr;

}







//
extern "C" DWORD WINAPI mcThreadProc_qisPipe_cli( LPVOID lpParameter )
{
	//
	QIS_pipe  *  pRtsp  =  (  QIS_pipe  *  )lpParameter;



	 #define		DEFAULT_dwToInMs		5000
	 DWORD								dwToInMs					=	DEFAULT_dwToInMs;

	 DWORD								dwTickCnt_lastAudioData		=	GetTickCount(  );;						// 

	 //  2014/03/15

#ifdef  __DEBUG__
	 traceLogA(  "mcThreadProc_qisPipe_recv enters"  );
#endif


	 pRtsp->bRunning  =  TRUE;
	 //  memset(  &pDispatchAudio->m_var,  0,  sizeof(  pDispatchAudio->m_var  )  );


	 //
	int  dwToInMs_rtsp  =  3000;

	 //
	 for  (  ;  !pRtsp->bQuit;  )  {

		 //
		 doPipe_cli(  pRtsp  );
		 
		 //
		 //  放慢一点点
		 Sleep(  200  );
	 }



	 //
errLabel:


	 //
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s ends."  ),  _T(  "mcThreadProc_qisPipe_cli"  )  );
	 

	 pRtsp->bRunning  =  FALSE;


	 traceLogA(  "mcThreadProc_qisPipe_recv %S leaves",  _T(  "rtsp"  )  );

	return  0;
}




