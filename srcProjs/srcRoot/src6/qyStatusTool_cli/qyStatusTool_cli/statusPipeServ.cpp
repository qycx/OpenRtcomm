

#include	"stdAfx.h"
#include	"qyStatusToolCommon.h"
#include	"qyStatusTool.h"
#include	"qyPs.h"

#define BUFSIZE 4096

typedef  struct  __pipeMem_t			{
				 HANDLE					hPipe;
				 HANDLE					hEvent;
				 HANDLE					hThread;
				 DWORD					dwThreadId;
}		 PIPE_MEM;

typedef  struct  __pipes_t				{
				 QY_STATUS_STRUCT	*	pParent;
				 BOOL					bStop;
				 PIPE_MEM				mems[100];	//10
}		 PIPES;

 DWORD  WINAPI  pipeInstanceThread(LPVOID lpvParam) 
{ 
	PIPES	*	pPipes	=	(  PIPES  *  )lpvParam;
	TCHAR		chRequest[BUFSIZE]; 
	int			index	=	0;
	DWORD		dwRet;
	DWORD		cbBytesRead;
	CWinApp	*	pApp		=	AfxGetApp(  );
	DWORD		dwTickCnt_lastData  =  GetTickCount();

	//
	traceLogA(  "pipeInstanceThread enters"  );

	for  (  index  =  0;  index  <  mycountof(  pPipes->mems  );  index  ++  )  {
		 if  (  GetCurrentThreadId(  )  ==  pPipes->mems[index].dwThreadId  )  break;
	}
	if  (  index  ==  mycountof(  pPipes->mems  )  )  goto  errLabel;

 
	// The thread's parameter is a handle to a pipe instance. 
 
	while  (   !pPipes->bStop  )  { 

		   OVERLAPPED  overlapStruct;
		   memset(  &overlapStruct,  0,  sizeof(  overlapStruct  )  );
		   overlapStruct.hEvent  =  pPipes->mems[index].hEvent;

		   // Read client requests from the pipe. 
		   ReadFile( 
			   pPipes->mems[index].hPipe,        // handle to pipe 
			   chRequest,    // buffer to receive data 
			   BUFSIZE*sizeof(TCHAR), // size of buffer 
			   &cbBytesRead, // number of bytes read 
			   &overlapStruct  );        // not overlapped I/O 
 
		   //
		   for  (  ;  ;  )  {
			    if  (  pPipes->bStop  )  goto  errLabel;
				//
				DWORD  dwTickCnt  =  GetTickCount(  );
				if  (  dwTickCnt  -  dwTickCnt_lastData  >  MAX_pipeServ_idleInMs  )  {
					goto  errLabel;
				}
				//
			    dwRet  =  WaitForSingleObject(  pPipes->mems[index].hEvent,  2000  );
				if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
				if  (  dwRet  ==  WAIT_TIMEOUT  )  continue;
				break;
		   }
		   //
		   dwTickCnt_lastData  =  GetTickCount(  );

		   //
		   DWORD	dwByte;
		   if  (  !GetOverlappedResult(  pPipes->mems[index].hPipe,  &overlapStruct,  &dwByte,  TRUE  )  )  goto  errLabel;
		   
		   //  traceLogA(  "here, %d",  sizeof(  QY_SHOW_STRUCT  )  );

#if 0
		   COPYDATASTRUCT	tmpCopyData;
			
		   tmpCopyData.lpData  =  chRequest;
		   tmpCopyData.cbData  =  dwByte;
		  
		   if  (  pApp  )  {
			   CWnd  *  pMainWnd	=	pApp->m_pMainWnd;
			   HWND			hWnd		=	NULL;

			   if  (  pMainWnd  )  {
				   hWnd  =  pMainWnd->m_hWnd;
				   if  (  hWnd  )  SendMessage(  hWnd,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
			   }				  
		   }
#endif
		   //
		   qPostMsg(chRequest, dwByte, &g_pStatusStruct->inputQ,  _T(  "pipeInstanceThread 2"  ));

	} 
 
// Flush the pipe to allow the client to read the pipe's contents 
// before disconnecting. Then disconnect the pipe, and close the 
// handle to this pipe instance. 
 
errLabel:
	if  (  index  <  mycountof(  pPipes->mems  )  )  {
		DisconnectNamedPipe(  pPipes->mems[index].hPipe  ); 
	}

	traceLogA(  "pipeInstanceThread leaves"  );

	return  1;
}


  DWORD  WINAPI  statusPipeServThreadProc(  LPVOID  lpParameter  )
 {
	int						iErr			=	-1;
	QY_STATUS_STRUCT	*	pStatusStruct	=	(  QY_STATUS_STRUCT  *  )lpParameter;
	HINSTANCE				hinstance		=	GetModuleHandle(  0  );
	//  MSG						msg; 
	//  BOOL					bRet;

	DWORD					dwThreadId; 
	int						iAppType		=	qyGetAppType(  0,  NULL  );
	//LPTSTR					lpszPipename	=	bAppClient(  iAppType  )  ?  CONST_statusPipeName_cli  :  CONST_statusPipeName_serv;
	LPTSTR					lpszPipename	=	bAppClient(  iAppType  )  ?  CONST_statusPipeName_cli_pipeServ  :  CONST_statusPipeName_serv_pipeServ;
 
	//
	PIPES					pipes;
	DWORD					dwRet;
	int						i;

	memset(  &pipes,  0,  sizeof(  pipes  )  );

// The main loop creates an instance of the named pipe and 
// then waits for a client to connect to it. When the client 
// connects, a thread is created to handle communications 
// with that client, and the loop is repeated. 
 
	//
	pStatusStruct->pipe.nPipes  =  mycountof(  pipes.mems  );
	pStatusStruct->pipe.nConnections  =  0;

	//
	for (  ;  !pStatusStruct->bQuit;)  { 

		for  (  i  =  0;  i  <  mycountof(  pipes.mems  );  i  ++  )  {
			 if  (  pipes.mems[i].hThread  )  {
				 waitForObject(  &pipes.mems[i].hThread,  0  );
				 //
				 if  (  !pipes.mems[i].hThread  )  {
					 pStatusStruct->pipe.nConnections  --  ;
				 }
			 }
			 if  (  !pipes.mems[i].hThread  )  {
				 if  (  pipes.mems[i].hPipe  )  {
					 CloseHandle(  pipes.mems[i].hPipe  );  pipes.mems[i].hPipe  =  NULL;
				 }
				 if  (  pipes.mems[i].hEvent  )  {
					 CloseHandle(  pipes.mems[i].hEvent  );  pipes.mems[i].hEvent  =  NULL;
				 }
			 }
		}
		for  (  i  =  0;  i  <  mycountof(  pipes.mems  );  i  ++  )  {
			 if  (  !pipes.mems[i].hThread  )  break;
		}
		if  (  i  ==  mycountof(  pipes.mems  )  )  {
			Sleep(  1000  );  continue;
		}

		//
		SECURITY_ATTRIBUTES  sa;
		SECURITY_DESCRIPTOR  sd;

		if  (  !InitializeSecurityDescriptor(  &sd,  SECURITY_DESCRIPTOR_REVISION  )  )  goto  errLabel;
		if  (  !SetSecurityDescriptorDacl(  &sd,  TRUE,  (  PACL) NULL,  FALSE  )  )  goto  errLabel;
		sa.nLength  =  sizeof(  sa  );
		sa.lpSecurityDescriptor  =  &sd;
		sa.bInheritHandle  =  TRUE;

		//
		pipes.mems[i].hPipe = CreateNamedPipe( 
          lpszPipename,             // pipe name 
          PIPE_ACCESS_DUPLEX  |  FILE_FLAG_OVERLAPPED,       // read/write access 
          PIPE_TYPE_MESSAGE  |  PIPE_READMODE_MESSAGE  |  PIPE_WAIT,                // // message type pipe , message-read mode , blocking mode 
          PIPE_UNLIMITED_INSTANCES, // max. instances  
          BUFSIZE,                  // output buffer size 
          BUFSIZE,                  // input buffer size 
          1000,                        // client time-out 
          &sa);                    // default security attribute 

		if  (  pipes.mems[i].hPipe == INVALID_HANDLE_VALUE) {
			printf("CreatePipe failed"); 
			goto  errLabel;
		}
 
		pipes.mems[i].hEvent  =  CreateEvent(  NULL,  FALSE,  FALSE,  FALSE  );
		if  (  !pipes.mems[i].hEvent  )  goto  errLabel;

	
		// Wait for the client to connect; if it succeeds, 
		// the function returns a nonzero value. If the function
		// returns zero, GetLastError returns ERROR_PIPE_CONNECTED. 
		OVERLAPPED  overlapStruct;
		memset(  &overlapStruct,  0,  sizeof(  overlapStruct  )  );
		overlapStruct.hEvent  =  pipes.mems[i].hEvent;
 
		ConnectNamedPipe( pipes.mems[i].hPipe, &overlapStruct);

		for  (  ;  ;  )  {
			 if  (  pStatusStruct->bQuit  )  goto  errLabel;
			 dwRet  =  WaitForSingleObject(  pipes.mems[i].hEvent,  2000  );
			 if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
			 if  (  dwRet  ==  WAIT_TIMEOUT  )  continue;
			 break;
		}

	  DWORD	dwByte;
	  if  (  !GetOverlappedResult(  pipes.mems[i].hPipe,  &overlapStruct,  &dwByte,  TRUE  )  )  continue;
		  
	  // Create a thread for this client. 
	  pipes.mems[i].hThread = CreateThread( 
            NULL,						// no security attribute 
            0,							// default stack size 
            pipeInstanceThread,				// thread proc
			(LPVOID)&pipes,				// thread parameter 
            CREATE_SUSPENDED,           // not suspended 
            &dwThreadId);				// returns thread ID 
	  if  (  pipes.mems[i].hThread == NULL) {
		  printf("CreateThread failed"); 
		  goto  errLabel;
	  }         
	  pipes.mems[i].dwThreadId  =  dwThreadId;
	  ResumeThread(  pipes.mems[i].hThread  );

	  //
	  pStatusStruct->pipe.nConnections  ++  ;

	  //
	  continue;
   } 

	iErr  =  0;

errLabel:

	traceLogA(  "statusPipeServThread is ready to stop"  );

	pipes.bStop  =  TRUE;
	for  (  i  =  0;  i  <  mycountof(  pipes.mems  );  i  ++  )  {
		 if  (  pipes.mems[i].hThread  )  {
			 waitForObject(  &pipes.mems[i].hThread,  INFINITE  );
		 }
		 if  (  isHandleValid(  pipes.mems[i].hPipe  )  )  {
			 CloseHandle(  pipes.mems[i].hPipe  );  pipes.mems[i].hPipe  =  NULL;
		 }
		 if  (  isHandleValid(  pipes.mems[i].hEvent  )  )  {
			 CloseHandle(  pipes.mems[i].hEvent  );  pipes.mems[i].hEvent  =  NULL;
		 }
	}

	traceLogA(  "statusPipeServThread leaves"  );

	return  iErr;
 }