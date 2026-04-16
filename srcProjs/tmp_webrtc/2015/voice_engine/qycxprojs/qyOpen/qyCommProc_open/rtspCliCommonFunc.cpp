

#include	"stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>
#include	<stddef.h>
#include	<mmsystem.h>

#include	"qdcOpenCommon.h"
#include	"qyPipeFunc_open.h"

//
 int  rtspCliCommon_init(  PF_BufferCB_rtsp  pf_BufferCB_rtsp,  PF_rtspCliHelp_exit  pf_exit,  int  iIndex_capProcInfo,  LPCTSTR  appObjPrefix,  int  tn,  void  *  pRTSP_cli_common  )
{
	int  iErr  =  -1;

	RTSP_cli_common  *  pGBuf  =  (  RTSP_cli_common  *  )pRTSP_cli_common;
	if  (  !pGBuf  )  return  -1;

	memset(  pGBuf,  0,  sizeof(  pGBuf[0]  )  );
	pGBuf->pf_BufferCB_rtsp  =  pf_BufferCB_rtsp;
	pGBuf->pf_rtspCliHelp_exit  =  pf_exit;
	pGBuf->iIndex_capProcInfo  =  iIndex_capProcInfo;
	//
	lstrcpyn(  pGBuf->appObjPrefix,  appObjPrefix,  mycountof(  pGBuf->appObjPrefix  )  );
	pGBuf->tn_rtspCliPipe  =  tn;
	
	//
	if  (  !pGBuf->pRTSP_msg  )  {
		int  size  =  sizeof(  RTSP_msg  );
		pGBuf->pRTSP_msg  =  malloc(  size  );
		if  (  !pGBuf->pRTSP_msg  )  goto  errLabel;
	}

	//
	//  2014/06/06
	//_sntprintf(  pGBuf->evtName_syncQuit,  mycountof(  pGBuf->evtName_syncQuit  ),  _T(  "%s%d"  ),  CONST_evtNamePrefix_rtspCliSyncQuit,  tn  );
	M_get_evtName_syncQuit(  CONST_evtNamePrefix_rtspCliSyncQuit,  pGBuf->appObjPrefix,  tn,  pGBuf->evtName_syncQuit  );
	pGBuf->hEvent_syncQuit  =  CreateEvent(  NULL,  FALSE,  FALSE,  pGBuf->evtName_syncQuit  );
	if  (  !pGBuf->hEvent_syncQuit  )  goto  errLabel;
	

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		rtspCliCommon_exit(  pGBuf  );
	}
	return  iErr;
}

 //
 int  rtspCliCommon_chkPipe(  void  *  pRTSP_cli_common  )
 {
	 int  iErr  =  -1;
	 RTSP_cli_common  *  pGBuf  =  (  RTSP_cli_common  *  )pRTSP_cli_common;	
	 if  (  !pGBuf  )  return  -1;
	 
	 //
	 TCHAR	pipeName[256]  =  _T(  ""  );		
	 //
	 M_get_pipeName(  CONST_rtspCliPipePrefix,  pGBuf->appObjPrefix,  pGBuf->tn_rtspCliPipe,  pipeName  );

	 //  2016/06/20
	 return  cli_chkQyPipe(  pipeName,  FALSE,  &pGBuf->pipe  );

	 //
#if  0
	 BOOL  fSuccess;

	 //
	 if  (  !isHandleValid_open(  pGBuf->pipe.hPipe  )  )  {	
		//

		//
		pGBuf->pipe.hPipe = CreateFile( 
							pipeName,   // pipe name 
							GENERIC_READ |  // read and write access 
							GENERIC_WRITE, 
							0,              // no sharing 
							NULL,           // default security attributes
							OPEN_EXISTING,  // opens existing pipe 
							0,              // default attributes 
							NULL);          // no template file   						
		if (  pGBuf->pipe.hPipe == INVALID_HANDLE_VALUE  )  {
#ifdef  _DEBUG
			OutputDebugString(  _T(  "BufferCB_rtspCli failed: CreateFile failed\n"  )  );
#endif
			goto  errLabel;
		}

		
		//traceLogA(  "showInfoThreadProc: pipe created"  );
		DWORD  dwMode = PIPE_READMODE_MESSAGE; 
		fSuccess  = SetNamedPipeHandleState( 
							pGBuf->pipe.hPipe,    // pipe handle 
							&dwMode,  // new pipe mode 
							NULL,     // don't set maximum bytes 
							NULL);    // don't set maximum time 					
		if (!fSuccess)  {
							//  qyDisplayLastError(  "SetNamedPipeHandleState failed"  ); 							
			goto  errLabel;						
		} 

	}

	 iErr  =  0;
errLabel:

	 //
	 if  (  iErr  )  {
	 	if  (  pGBuf->pipe.hPipe  !=  INVALID_HANDLE_VALUE  )  {
			CloseHandle(  pGBuf->pipe.hPipe  );  pGBuf->pipe.hPipe  =  NULL;
		}
	 }

	 return  iErr;
#endif
 }



 //  2015/10/16
//  int  BufferCB_rtspCliCommon(  void  *  pRTSP_cli_common,  int  iIndex_capProcInfo,  int  iMediumType,  int  iCodecType,  int  iSampleTimeInMs,  unsigned  int  uiPts,  unsigned  char  *  pBuffer,  long  BufferLen,  bool  bSpsPps,  int  index_spsPps,  bool  bFinished_spsPps,  bool  bNeedResp,  CB_rtsp_res  *  pRes  )
 int  BufferCB_rtspCliCommon(  void  *  pRTSP_cli_common,  int  iIndex_capProcInfo,  int  iMediumType,  int  iCodecType,  int  iSampleTimeInMs,  unsigned  int  uiPts,  int  iDataType,  unsigned  char  *  pBuffer,  long  BufferLen,  bool  bSpsPps,  int  index_spsPps,  bool  bFinished_spsPps,  bool  bNeedResp,  CB_rtsp_res  *  pRes  )
{
	int						hr					=	-1;

	if  (  !pRes  )  return  -1;
	RTSP_cli_common  *  pGBuf  =  (  RTSP_cli_common  *  )pRTSP_cli_common;
	if  (  !pGBuf  )  return  -1;
	
	BOOL		fSuccess;

	//  2014/06/06
	pGBuf->status.dwLastTickCnt_BufferCB_rtspCli  =  GetTickCount(  );

	//
	if  (  !isHandleValid_open(  pGBuf->pipe.hPipe  )  )  {	
		//
		if  (  rtspCliCommon_chkPipe(  pGBuf  )  )  {
			goto  errLabel;
		}

	}
						
	

	if  (  !pGBuf->pRTSP_msg  )  goto  errLabel;
	RTSP_msg  &	msg  =  *(  RTSP_msg  *  )pGBuf->pRTSP_msg;
	memset(  &msg,  0,  offsetof(  RTSP_msg,  buf  )  );

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
						pGBuf->pipe.hPipe,                  // pipe handle 
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

	hr  =  S_OK;

errLabel:
	
	if  (  FAILED(  hr  )  )  {
		//
		//
		if  (  pGBuf->pipe.hPipe  !=  INVALID_HANDLE_VALUE  )  {
			CloseHandle(  pGBuf->pipe.hPipe  );  pGBuf->pipe.hPipe  =  NULL;
		}
	}

	return  hr;
}


int  rtspCliCommon_exit(  void  *  pRTSP_cli_common  )
{
	RTSP_cli_common  *  pGBuf  =  (  RTSP_cli_common  *  )pRTSP_cli_common;
	if  (  !pGBuf  )  return  -1;

	//
	if  (  pGBuf->hEvent_syncQuit  )  {
		CloseHandle(  pGBuf->hEvent_syncQuit  );  pGBuf->hEvent_syncQuit  =  NULL;
	}

	//
#if  0  //  2016/06/20
	if  (  pGBuf->pipe.hPipe  !=  INVALID_HANDLE_VALUE  )  {
		//
		pGBuf->status.bRet_CancelIo  =  CancelIo(  pGBuf->pipe.hPipe  );
		//
		#ifdef  _DEBUG
				if  (  pGBuf->status.bRet_CancelIo  )  OutputDebugString(  _T(  "rtspCliCommon_exit: CancelIo true\n"  )  );
				else  OutputDebugString(  _T(  "rtspCliCommon_exit: cancelIo false\n"  )  );
		#endif
		//			
		CloseHandle(  pGBuf->pipe.hPipe  );  pGBuf->pipe.hPipe  =  NULL;
	}
#endif
	//  2016/06/20
	closeQyPipe(  &pGBuf->pipe  );
	
	//
	try  {
		 //
		 MACRO_safeFree(  pGBuf->pRTSP_msg  );
		}
	catch  (  ...  )  {
		   pGBuf->status.bException_pRTSP_msg  =  TRUE;
		   OutputDebugString(  _T(  "rtspCliCommon_exit: exception. free pRTSP_msg\n"  )  );
	}

	return  0;
}
