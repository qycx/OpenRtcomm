

#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//#include	"qmcVideoCapture_isCli.h"
//#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
//  #include	"myfourcc.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

#include	"qmcVideoCapture_rtsp.h"
#include	"qmcCopyData.h"
#include	"rtspUsrData.h"
#include	"qmcCfg.h"
#include	"qisNameDefs.h"
#include	"qyPipeFunc.h"
#include <string>


//  2015/01/29
#ifdef  __DEBUG__
		//
		#define  __DUMP_h264_rtsp__

#if  0
#define		__USE_rtsp_asDll__		//  2014/03/05.为了方便测试，将rtspCliHelp.dll直接链入messenger
#endif

//
#if 0
#define		__DBG_rtspCli__ 
#endif



int  BufferCB_av_rtsp_test_mp2t(void* pGBUF_rtspCliHelp, int  iIndex_capProcInfo, int  iMediumType, int  iCodecType, int  iSampleTimeInMs, unsigned  int  uiPts, int  iDataType, unsigned  char* pBuffer, long  BufferLen, bool  bSpsPps, int  index_spsPps, bool  bFinished_spsPps, bool  bNeedResp, CB_rtsp_res* pRes);



#endif

//
 DWORD WINAPI mcThreadProc_writeShm_dvt( LPVOID lpParameter );
int  qvcf_doRecvRtsp(  void  *  pCapDev_rtsp  );

//
//  2015/10/16
//#define		needRtspCliHelp(  pVIDEO_capDev_rtsp  )				(  (  pVIDEO_capDev_rtsp  )->uiType  !=  CONST_rtspType_decV  )
BOOL  needRtspCliHelp(  VIDEO_capDev_rtsp  *  pVIDEO_capDev_rtsp  )
{
	switch  (  pVIDEO_capDev_rtsp->uiType  )  {
			case  CONST_rtspType_decV:
			case  CONST_rtspType_encV:
				  return  FALSE;
				  break;
			default:
					break;
	}

	return  TRUE;
}


//
bool  b__DBG_rtspCli__()
{

#ifdef  __DBG_rtspCli__
	return  true;
#endif 

	//
	return  false;
}



//  2014/06/06
BOOL  bThreadQuit_videoCapDevRtsp(  VIDEO_capDev_rtsp  *  pRtsp  )
{
	return  pRtsp->bQuit  ||  pRtsp->pipe.bThreadQuit;
}


//
int  askRtspCliToQuit(  VIDEO_capDev_rtsp  *  pRtsp  )
{
	int  iErr  =  -1;
	DWORD  dwRet;		 
	//
	TCHAR	evtName[256];		
	HANDLE	hEvent  =  NULL;		 
	int  i;

	if  (  !pRtsp->hProcess_rtspCliHelp  )  return  0;
			
	_sntprintf(  evtName,  mycountof(  evtName  ),  _T(  "%s%d"  ),  CONST_evtNamePrefix_rtspCliSyncQuit,  pRtsp->tn_rtspCliPipe  );	
	hEvent  =  CreateEvent(  NULL,  FALSE,  FALSE,  evtName  );
	
	//	
	if  (  hEvent  )  SetEvent(  hEvent  );

	 
	iErr  =  0;

errLabel:

	
	if  (  hEvent  )  CloseHandle(  hEvent  );

	return  iErr;
}


#include <regex>

struct RtspUrlParts {
	std::wstring protocol;
	std::wstring username;
	std::wstring password;
	std::wstring hostname;
	std::wstring port;
	std::wstring path;
};

RtspUrlParts parseRtspUrl(const std::wstring& url) {
	RtspUrlParts parts;

	std::wregex pattern(L"(rtsp)://(?:([^:]+):([^@]+)@)?([^:/]+)(?::([0-9]+))?(/.*)");
	std::wsmatch matches;

	if (std::regex_search(url, matches, pattern)) {
		parts.protocol = matches[1].str();
		parts.username = matches[2].str();
		parts.password = matches[3].str();
		parts.hostname = matches[4].str();
		parts.port = matches[5].str();
		parts.path = matches[6].str();
	}

	return parts;
}



int  createRtspCliHelp(  VIDEO_capDev_rtsp  *  pRtsp  )
{
	int			iErr	=	-1;
	MC_VAR_common  *  pProcInfo	=	pRtsp->pProcInfoCommon;//QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	//
	QY_MC	*	pQyMc	=	(  QY_MC  *  )pProcInfo->pQyMc;//QY_GET_GBUF(  );
	if  (  !pQyMc  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "createRtspCliHelp failed, pQyMc is null"  )  );
		#endif
		return  -1;
	}
	//
	STARTUPINFO				si;
	PROCESS_INFORMATION		pi;
	BOOL						bProcessCreated				=		FALSE;
	TCHAR						tmpExeName[MAX_PATH  +  1]	=	_T(  ""  );
	TCHAR						url[MAX_PATH + 1] = _T("");


	RtspUrlParts parts = parseRtspUrl(pRtsp->url);
	_sntprintf(url, mycountof(url), _T("%s://%s:%s%s"), parts.protocol.c_str(), parts.hostname.c_str(), parts.port.c_str(), parts.path.c_str());
	
	if  (  pRtsp->hProcess_rtspCliHelp  )  return  0;

	memset(  &si,  0,  sizeof(  si  )  );	
	memset(  &pi,  0,  sizeof(  pi  )  );
	
	traceLogA(  (char*)  "Now start qwm "  );	
	memset(  &si,  0,  sizeof(  STARTUPINFO  )  );
	si.cb  =  sizeof(  STARTUPINFO  );
#if  0
	si.dwFlags  =  STARTF_USESHOWWINDOW;	//
	si.wShowWindow  =  SW_HIDE;
#endif
	si.dwFlags  =  STARTF_FORCEOFFFEEDBACK;
	
#define  CONST_subDir_toolsRtspCli	_T(  "tools\\rtspCli\\"  )
	_sntprintf(  tmpExeName,  mycountof(  tmpExeName  ),  _T(  "%s%s%s"  ),  pQyMc->cfg.installDir,  CONST_subDir_toolsRtspCli,  _T(  "rtspCli.exe"  )  );	
	if  (  tQyQuoteFileName(  tmpExeName,  mycountof(  tmpExeName  )  )  )  goto  errLabel;

	
	
	//
	_sntprintf(  tmpExeName,  mycountof(  tmpExeName  ),  _T(  "%s -a%s -tn=%d"  ),  tmpExeName,  pProcInfo->get_appObjPrefix(  ),  pRtsp->tn_rtspCliPipe  );

	if(parts.username.length() > 0)
		_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s -B 10000000 -b 10000000 -u %s %s"), tmpExeName, parts.username.c_str(), parts.password.c_str());
	else
		_sntprintf(tmpExeName, mycountof(tmpExeName), _T("%s -B 10000000 -b 10000000 "), tmpExeName);

	_sntprintf(  tmpExeName,  mycountof(  tmpExeName  ),  _T(  "%s -t \"%s\""  ),  tmpExeName, url);
	//
	
	//
	DWORD  dwCreationFlags; dwCreationFlags = CREATE_NO_WINDOW;
	QMC_debugStatusInfo* pCfg_debugStatusInfo; pCfg_debugStatusInfo = pProcInfo->get_qmc_debugStatusInfo();
	if  (  pCfg_debugStatusInfo
		&&  pCfg_debugStatusInfo->ucbShowRtspCliControl  )  		
	{
			dwCreationFlags  =  0;
	}
	//
#ifdef  __DEBUG__
	if (0) {
		dwCreationFlags = 0;
		showInfo_open0(0, 0, _T("for test, show rtspCli"));
	}

	//
	if (b__DBG_rtspCli__()) {

		traceLog((TCHAR*)_T("for dbg: __DBG_rtspCli__ is set"));
		iErr = 0;  goto  errLabel;
	}


#endif 
	//
	if  (  !CreateProcess(  NULL,  tmpExeName,  NULL,  NULL,  0,  dwCreationFlags,  NULL,  NULL,  &si,  &pi  )  )  goto  errLabel;	 	
	bProcessCreated  =  TRUE;

#ifdef  __DEBUG__
	traceLogA(  (char*)  "CreateProcess %s succeeded,  new processId is %d,  new threadId is %d.",  tmpExeName,  pi.dwProcessId,  pi.dwThreadId  );
	qyShowInfo(  pQyMc->pShowInfoStruct,  CONST_qyShowType_qwmComm,  0,  (char*)"",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "create %s ok"  ),  tmpExeName  );
#endif


	//
	iErr  =  0;

errLabel:
	
	if  (  bProcessCreated  )  {
		 if  (  pi.hThread  )  {  CloseHandle(  pi.hThread  );  pi.hThread  =  NULL;  }
		 if  (  pi.hProcess  )  pRtsp->hProcess_rtspCliHelp  =  pi.hProcess;
	 }

	if  (  iErr  )  {
		qyShowInfo(  pQyMc->pShowInfoStruct,  CONST_qyShowType_qwmComm,  0,  (char*)"",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "createRtspCliHelp failed, %s"  ),  tmpExeName  );
	}

	return  iErr;

}


int  closeRtspCliHelp(  VIDEO_capDev_rtsp  *  pRtsp  )
{
	int  iErr  =  -1;
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pRtsp->pProcInfoCommon;//  QY_GET_procInfo_isCli(  );
	DWORD  dwRet;		 
	//
	int  i;

	if  (  !pRtsp->hProcess_rtspCliHelp  )  return  0;
			
	
	//	
	for  (  i  =  0;  i  <  30;  i  ++  )  {		
		 //
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  "closeRtspCliHelp:"  ),  _T(  ""  ),  _T(  "askRtspCliToQuit,  %d"  ),  i  );
		//
		askRtspCliToQuit(  pRtsp  );
		 //
		 dwRet  =  WaitForSingleObject(  pRtsp->hProcess_rtspCliHelp,  1000  );
		 if  (  dwRet  !=  WAIT_FAILED  &&  dwRet  !=  WAIT_TIMEOUT  )  {
			 CloseHandle(  pRtsp->hProcess_rtspCliHelp  );  pRtsp->hProcess_rtspCliHelp  =  NULL;
			 break;
		 }		
		 if  (  i  >=  3  )  {
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  "closeRtspCliHelp:"  ),  _T(  ""  ),  _T(  "too long to wait, terminate rtspCli"  )  );
			 TerminateProcess(  pRtsp->hProcess_rtspCliHelp,  -1  );
		 }
	}

	//	
	if  (  pRtsp->hProcess_rtspCliHelp  )  {	//  即使没回收，也要关闭了
#ifdef  __DEBUG__
			 myMessageBox(  NULL,  _T(  "即使没回收，也要关闭了. 这里没做好，应该rtspCli赶紧退出的"  ),  0,  0  );
#endif
			 //
			 CloseHandle(  pRtsp->hProcess_rtspCliHelp  );  pRtsp->hProcess_rtspCliHelp  =  NULL;		
	}
	 
	iErr  =  0;

errLabel:

	return  iErr;
}






//
int  rtspSendResp(  VIDEO_capDev_rtsp  *  pRtsp,  RTSP_usrData_resp  *  pResp  )
{
	int  iErr  =  -1;
	int  iSize  =  sizeof(  RTSP_usrData_resp  );
	
	pResp->uiType  =  CONST_rtspUsrDataType_resp;
	static  int  iii  =  0;  iii  ++  ;
	
	DWORD  nWritten  =  0;
		
	//	
	if  (  !WriteFile(  pRtsp->pipe.hPipe,  pResp,  iSize,  &nWritten,  NULL  )  )  {		
		goto  errLabel;				   
	}


	iErr  =  0;
errLabel:
	return  iErr;

}

//
int  tmp_getResp(  MC_VAR_common  *  pProcInfo,  VIDEO_capDev_rtsp  *  pRtsp,  RTSP_usrData_resp  *  pResp  )
{
	int  iErr  =  -1;

	QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pRtsp->iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;

	CAP_procInfo_bmpU* pCapBmp; pCapBmp = getCapBmpBySth(pProcInfo, pSharedObj->iIndex_capBmp, 0);
	if  (  !pCapBmp  )  goto  errLabel;

	DVT_decV* pDvt_decV; pDvt_decV = pRtsp->pDvt_decV;
	if  (  !pDvt_decV  )  goto  errLabel;

	//
	memset( pResp,  0,  sizeof(  pResp[0]  )  );
	pResp->bih_dec  =  pCapBmp->common.vh_org.bih;

	if  (  pDvt_decV->dataShm.hMap  )  {
		pResp->bShmOpen  =  TRUE;
	}

	iErr  =  0;
errLabel:
	return  iErr;

}


//
DWORD  WINAPI  pipeInstanceThread_doRecvRtsp(LPVOID lpvParam) 
{ 
	VIDEO_capDev_rtsp  *  pRtsp  =  (  VIDEO_capDev_rtsp  *  )lpvParam;
	CQyMalloc	mallocObj;
	//  TCHAR		chRequest[CONST_bufSize_rtspCliPipe]; 
	int  iBUFSIZE  =  CONST_bufSize_rtspCliPipe;
	RTSP_msg	*	pMsg	=	(  RTSP_msg  *  )mallocObj.mallocf(  iBUFSIZE  );
	if  (  !pMsg  )  return  -1;
	
	MC_VAR_common  *  pProcInfo  =  pRtsp->pProcInfoCommon;//QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	RW_lock_param  *  pQyMc_cfg_rwLockParam  =  pProcInfo->get_qyMc_rwLockParam(  );
	if  (  !pQyMc_cfg_rwLockParam  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "pipeInstanceThread failed, get_qyMc_rwLockParam returns null"  )  );
		#endif
		return  -1;
	}
	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;

	//  2016/04/09
	CUS_MODULES  *  pCusModules  =  (  CUS_MODULES  *  )pProcInfo->getCusModules(  );
	if  (  !pCusModules  )  {
		showInfo_open0(  0,  0,  _T(  "pipeInstanceThread failed, pCusModules is null"  )  );
		return  -1;
	}

#if  10

	//
	int  iIndex_capBmp  =  -1;

	//
	QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pRtsp->iIndex_sharedObj  );
	if  (  pSharedObj  )  {
		iIndex_capBmp  =  pSharedObj->iIndex_capBmp;
	}

	//
	int  iSize;
	
	//
	iSize  =  sizeof(  RTSP_usrData_resp  );		
	CQyMalloc	mallocObj_pResp;
	RTSP_usrData_resp  *  pResp  =  (  RTSP_usrData_resp  *  )mallocObj_pResp.mallocf(  iSize  );
	if  (  !pResp  )  {
		showInfo_open0(  0,  0,  _T(  "pipeThread: resp.mallocf failed"  )  );
		return  -1;
	}
	
	//
	if  (  pRtsp->uiType  ==  CONST_rtspType_decV  )  {
		iSize  =  sizeof(  DVT_decV  );
		pRtsp->pDvt_decV  =  (  DVT_decV  *  )mymalloc(  iSize  );
		if  (  !pRtsp->pDvt_decV  )  return  -1;
		memset(  pRtsp->pDvt_decV,  0,  iSize  );
	}	

	//  2015/02/04
	QY_TRANSFORM  *  pTransform  =  NULL;
	if  (  pSharedObj  )  {
		if  (  !pSharedObj->pTransInfo_stream  )  goto  errLabel;
		TRANSINFO_stream  *  pTransInfo  =  (  TRANSINFO_stream  *  )pSharedObj->pTransInfo_stream;
		if  (  !pTransInfo->myTask.pMems_from  )  goto  errLabel;
		//	
		pTransform  =  &pTransInfo->myTask.pTransforms[0];
	}


	//
	int			index; index = 0;
	DWORD		dwRet;
	DWORD		cbBytesRead;
	//

#ifdef  __DEBUG__
		traceLogA(  (char*)  "pipeInstanceThread enters"  );
#endif
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "pipeThread starts"  )  );


#if  0
	for  (  index  =  0;  index  <  mycountof(  pPipes->mems  );  index  ++  )  {
		 if  (  GetCurrentThreadId(  )  ==  pPipes->mems[index].dwThreadId  )  break;
	}
	if  (  index  ==  mycountof(  pPipes->mems  )  )  goto  errLabel;
#endif
 
	// The thread's parameter is a handle to a pipe instance. 
 
	while  (   !bThreadQuit_videoCapDevRtsp(  pRtsp  )  )  { 

		   OVERLAPPED  overlapStruct;
		   memset(  &overlapStruct,  0,  sizeof(  overlapStruct  )  );
		   overlapStruct.hEvent  =  pRtsp->pipe.hEvent;

		   // Read client requests from the pipe. 
		   ReadFile( 
			   pRtsp->pipe.hPipe,        // handle to pipe 
			   pMsg,    // buffer to receive data 
			   iBUFSIZE, // size of buffer 
			   &cbBytesRead, // number of bytes read 
			   &overlapStruct  );        // not overlapped I/O 
 
		   for  (  ;  ;  )  {
			    if  (  bThreadQuit_videoCapDevRtsp(  pRtsp  )  )  goto  errLabel;
				dwRet  =  WaitForSingleObject(  pRtsp->pipe.hEvent,  2000  );
				if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
				if  (  dwRet  ==  WAIT_TIMEOUT  )  continue;
				break;
		   }
		   //  2015/06/22
		   if  (  bThreadQuit_videoCapDevRtsp(  pRtsp  )  )  goto  errLabel;
		   
		   //
		   DWORD	dwByte;
		   if  (  !GetOverlappedResult(  pRtsp->pipe.hPipe,  &overlapStruct,  &dwByte,  TRUE  )  )  {
			   #ifdef  __DEBUG__
					   traceLog((TCHAR*)  _T(  "pipeThread failed, GetOverlappedResult failed"  )  );
			   #endif
			   goto  errLabel;
		   }
		   
#ifdef  __DEBUG__
		   //
#if  0
		   QMC_cfg_debugStatusInfo  *  pCfg_debugStatusInfo  =  pProcInfo->get_qmc_cfg_debugStatusInfo(  );
		   if  (  pCfg_debugStatusInfo
			   &&  pCfg_debugStatusInfo->ucbPrint_rtsp  )  
		   {
			   //  traceLogA(  (char*)  "read from pipe %d bytes",  dwByte  );
		   }
#endif 
		   //
		   //  traceLogA(  (char*)  "read from pipe %d bytes",  dwByte  );
#endif
		   //  if  (  cbBytes
		   if  (  dwByte  <  offsetof(  RTSP_msg,  buf  )  )  {
			   TCHAR  tBuf[128];
			   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "pipeThread: serious err: dwByte %d err. should be > offsetof(  RTSP_msg,  buf  ) %d"  ),  dwByte,  offsetof(  RTSP_msg,  buf  )  );
			   #ifdef  __DEBUG__
					   traceLog((TCHAR*)  _T(  "%s"  ),  tBuf  );
			   #endif
			   showInfo_open0(  0,  0,  tBuf  );
			   //
			   goto  errLabel;
		   }

		   //  2015/01/30
		   if  (  pMsg->iMediumType  ==  CONST_mediumType_usrData  )  {
			   //
			   RTSP_usrData_common  *  pUsrDataCommon  =  (  RTSP_usrData_common  *  )pMsg->buf;

			   //
			   if  (  pRtsp->uiType  ==  CONST_rtspType_encV  )  {
				   //
				   //  traceLog((TCHAR*)  _T(  "pipe: encV, dataType %d, len %d"  ),  pMsg->iDataType,  pMsg->uiLen  );
				   TRANSFER_VIDEO_DATA  *  pReq  =  (  TRANSFER_VIDEO_DATA  *  )pMsg->buf;
				   //traceLog((TCHAR*)  _T(  "pip3: encV: req.cnt %d. pts %d"  ),  pReq->usCnt,  pReq->mems[0].uiPts  );
				   if  (  pReq->usCnt  ==  1  )  {				   
					   myDRAW_VIDEO_DATA  buf_pkt;
					   doPostEnc_mediaSdk_new(  pRtsp->pQdcObjInfo,  pReq->buf,  pReq->uiLen,  pReq->mems[0].uiSampleTimeInMs,  pReq->mems[0].uiPts,  &buf_pkt  );				   
					   }
				   else  {
					     showInfo_open0(  0,  0,  _T(  "pipe: encV err, req.cnt != 1"  )  );
				   }
				   //
				   QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )pRtsp->pQdcObjInfo;
				   if  (  pQdcObjInfo  )  {
					   EVT_cli  *  pEvtCli  =  (  EVT_cli  *  )pQdcObjInfo->var.pObj;
					   if  (  pEvtCli  )  {
						   pEvtCli->status.dwLastTickCnt_encDataGot  =  GetTickCount(  );
					   }
				   }
				   //
				   continue;
			   }


			   //
			   if  (  pRtsp->uiType  !=  CONST_rtspType_decV  )  {
				   goto  errLabel;
			   }
			   DVT_decV  *  pDvt_decV  =  (  DVT_decV  *  )pRtsp->pDvt_decV;
			   if  (  !pDvt_decV  )  goto  errLabel;
			   
			   if  (  pUsrDataCommon->uiType  ==  CONST_rtspUsrDataType_commInfo  )  {
				   //
				   RTSP_usrData_commInfo  *  pCommInfo  =  (  RTSP_usrData_commInfo  *  )pMsg->buf;

				   //
				   showInfo_open0(  0,  0,  _T(  "dvt: commInfo has been got"  )  );

				   //
				   if  (  pCommInfo->bShmReady  )  {
					   if  (  !pDvt_decV->dataShm.hMap  )  {
						   QY_shm  *  pShm  =  &pDvt_decV->dataShm;
						   
						   _sntprintf(  pShm->shmName,  mycountof(  pShm->shmName  ),  _T(  "Local\\%s%s%d"  ),  CQyString(  pProcInfo->get_appObjPrefix(  )  ),  CONST_shmName_qm_dvt,  pRtsp->tn_rtspCliPipe  );						// name of mapping object 

						   pShm->hMap  =  OpenFileMapping(  FILE_MAP_READ  |  FILE_MAP_WRITE,  0,  pShm->shmName  );
						   if  (  !pShm->hMap  )  {
							   qyDisplayLastError( (char*) "OpenFileMapping"  );
							   goto  errLabel;
						   }
						   //
						   pShm->pBuf  =  (  char  *  ) MapViewOfFile(pShm->hMap,   // handle to map object
						                        FILE_MAP_ALL_ACCESS,			// read/write permission
						                        0,                   
						                        0,                   
												pShm->uiBufSize_pBuf  );           						
						   if  (  !pShm->pBuf  )  goto  errLabel;

						   //						   
						   if  (  pDvt_decV->writeShm.hEvent_syncR  )  goto  errLabel;							
						   _sntprintf(  pDvt_decV->writeShm.evtName_syncR,  mycountof(  pDvt_decV->writeShm.evtName_syncR  ),  _T(  "%s%s%d"  ),  pProcInfo->get_appObjPrefix(  ),  CONST_evtNamePrefix_rtspCliSyncR,  pRtsp->tn_rtspCliPipe  );
						   pDvt_decV->writeShm.hEvent_syncR  =  CreateEvent(  NULL,  FALSE,  FALSE,  pDvt_decV->writeShm.evtName_syncR  );
						   if  (  !pDvt_decV->writeShm.hEvent_syncR  )  goto  errLabel;

						   //  2015/02/19
						   if  (  pDvt_decV->writeShm.hEvent_syncW  )  goto  errLabel;							
						   _sntprintf(  pDvt_decV->writeShm.evtName_syncW,  mycountof(  pDvt_decV->writeShm.evtName_syncW  ),  _T(  "%s%s%d"  ),  pProcInfo->get_appObjPrefix(  ),  CONST_evtNamePrefix_rtspCliSyncW,  pRtsp->tn_rtspCliPipe  );
						   pDvt_decV->writeShm.hEvent_syncW  =  CreateEvent(  NULL,  FALSE,  FALSE,  pDvt_decV->writeShm.evtName_syncW  );
						   if  (  !pDvt_decV->writeShm.hEvent_syncW  )  goto  errLabel;


						   //
						   DWORD  dwThreadDaemonId;
						   //
						   void  *  lpParameter  =  pTransform;	//  2015/10/06	//  pRtsp;
						   //
						   pDvt_decV->writeShm.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_writeShm_dvt,  lpParameter,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
						   if  (  !pDvt_decV->writeShm.hThread  )  goto  errLabel;					
						   pDvt_decV->writeShm.dwThreadId  =  dwThreadDaemonId;					
						   if  (  ResumeThread(  pDvt_decV->writeShm.hThread  )  ==  -1  )  goto  errLabel;									 

						   //  2016/04/12
						   VT_shm_content  *  pShmContent  =  (  VT_shm_content  *  )pShm->pBuf;			
						   _sntprintf(  pProcInfo->who_showInfo,  mycountof(  pProcInfo->who_showInfo  ),  _T(  "dvt%s"  ),  pShmContent->cfg.name  );
						   set_who_showInfo(  pProcInfo->who_showInfo  );

					   }
				   }


				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "SendMsgTimeout ok"  )  );
				   #endif

			   }
			   
			   //
			   if  (  pMsg->bNeedResp  )  {
				   //
				   tmp_getResp(  pProcInfo,  pRtsp,  pResp  );
				   //
				   if  (  rtspSendResp(  pRtsp,  pResp  )  )  {
					   goto  errLabel;
				   }
			   }

			   //
			   continue;
		   }
		   	   
		   //  2015/05/20
		   int  iDataType  =  0;

		   //
		   CB_rtsp_res  res;
		   memset(  &res,  0,  sizeof(  res  )  );
		   res.dwTickCnt_doPretrans  =  pMsg->dwTickCnt_doPretrans;		//  2015/02/24

		   if (pMsg->iMediumType == CONST_mediumType_video) {
			   //
			   BufferCB_v_rtsp(pProcInfo, NULL, iIndex_capBmp, pMsg->iMediumType, iDataType, pMsg->iCodecType, pMsg->iSampleTimeInMs, pMsg->uiPts,
				   (unsigned  char*)pMsg->buf, pMsg->uiLen, pMsg->bSpsPps, pMsg->index_spsPps, pMsg->bFinished_spsPps, &res);
		   }
		   else {
			   unsigned  int  bufSize_pMsgTaskBuf = sizeof(MIS_MSG_TASK);
			   CQyMalloc  mallocObj_pMsgTaskBuf;

			   MIS_MSG_TASK* pMsgTaskBuf = (MIS_MSG_TASK*)mallocObj_pMsgTaskBuf.mallocf(bufSize_pMsgTaskBuf);
			   if (!pMsgTaskBuf)  goto  errLabel;;

			   iDataType = 20;

			   BufferCB_a_rtsp(pProcInfo, NULL, iIndex_capBmp, pMsg->iMediumType, pMsg->iDataType, pMsg->iCodecType, pMsg->iSampleTimeInMs, pMsg->uiPts,
				   (unsigned  char*)pMsg->buf, pMsg->uiLen, pMsgTaskBuf, &res);
		   }

		   //
		   if  (  pMsg->bNeedResp  )  {
			   //
			   tmp_getResp(  pProcInfo,  pRtsp,  pResp  );
			   //
			   if  (  rtspSendResp(  pRtsp,  pResp  )  )  {
				   goto  errLabel;
			   }
			   
			   #ifdef  __DEBUG__
					   traceLog((TCHAR*)  _T(  "writeFile ok"  )  );
			   #endif
		   }

		   //  2015/02/05
		   if  (  pRtsp->uiType  ==  CONST_rtspType_decV  )  {
			   int  nQNodes  =  getQ2Nodes_toGetMsg(  &pTransform->video.q2  )  +  getQ2Nodes_toPostMsg(  &pTransform->video.q2  );		   				   
			   TCHAR  tBuf[128];
			   //
			   int  maxQNodes_toWait  =  30;
			   //
			   #ifdef  __DEBUG__
					   //maxQNodes_toWait  =  0;
					   //
					   //
			   #endif
			   //
		#if  0
			   if  (  nQNodes  >  maxQNodes_toWait  )  {		
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "too many msg in transQ, %d. will quit now."  ),  nQNodes  );
				   showInfo_open0(  0,  0,  tBuf  );
				   goto  errLabel;
			   }
		#endif
			   //
			   DVT_decV  *  pDvt_decV  =  (  DVT_decV  *  )pRtsp->pDvt_decV;
			   if  (  !pDvt_decV  )  goto  errLabel;

			   QY_shm  *  pShm  =  &pDvt_decV->dataShm;
			   if  (  pShm->pBuf  )  {
				   VT_shm_content  *  pShmContent  =  (  VT_shm_content  *  )pShm->pBuf;			
				   if  (  pShmContent->u.dvt.i.ucbShowPreDecVStatus  )  {
						#if  0
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "msg in transQ has %d nodes."  ),  nQNodes  );
					   showInfo_open0(  0,  0,  tBuf  );
						#endif
				   }
				   //  2016/04/13
				   if  (  pShmContent->u.dvt.i.ucbShowDec_pipeStatus  )  {
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "pipe input: pts %d, dataLen %d."  ),   pMsg->uiPts,  pMsg->uiLen  );
					   if  (  pTransform  )  {
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s transQ %d+%d"  ),  tBuf,  pTransform->video.q2.qs[0].uiQNodes,  pTransform->video.q2.qs[1].uiQNodes  );
					   }
					   showInfo_open0(  0,  0,tBuf  );
				   }

				   //
				   //  2015/02/09
				   if  (  pQmcCfg->debugStatusInfo.ucbShowPreDecVStatus  !=  pShmContent->u.dvt.i.ucbShowPreDecVStatus  )  pQmcCfg->debugStatusInfo.ucbShowPreDecVStatus  =  pShmContent->u.dvt.i.ucbShowPreDecVStatus;
				   if  (  pQmcCfg->debugStatusInfo.ucbShowPostDecVStatus  !=  pShmContent->u.dvt.i.ucbShowPostDecVStatus  )  pQmcCfg->debugStatusInfo.ucbShowPostDecVStatus  =  pShmContent->u.dvt.i.ucbShowPostDecVStatus;
				   //  2015/10/07
				   //if  (  pQmcCfg->debugStatusInfo.ucbShowDec_sharedTexStatus  !=  pShmContent->u.dvt.i.ucbShowDec_sharedTexStatus  )  pQmcCfg->debugStatusInfo.ucbShowDec_sharedTexStatus  =  pShmContent->u.dvt.i.ucbShowDec_sharedTexStatus;
				   //
				   CUS_MODULE_U	*	pModule			=	NULL;
				   M_getCompressModule(  pCusModules,  pTransform->video.uiModuleType_toDec,  pModule  );	//  2012/09/09
				   if  (  pModule  )  {
					   if  (  pModule->compress.pf_qdcGetProp  &&  pModule->compress.pf_qdcSetProp  )  {
						   BOOL  bShowDec_sharedTexStatus  =  FALSE;
						   if  (  !pModule->compress.pf_qdcGetProp(  CONST_qdcPropId_bShowDec_sharedTexStatus,  NULL,  &bShowDec_sharedTexStatus  )  )  {
							   BOOL  tmpbVal  =  pShmContent->u.dvt.i.ucbShowDec_sharedTexStatus;
							   if  (  bShowDec_sharedTexStatus  !=  tmpbVal  )  {
								   pModule->compress.pf_qdcSetProp(  CONST_qdcPropId_bShowDec_sharedTexStatus,  &tmpbVal,  NULL  );
								   //
								   #ifdef  __DEBUG__
										   showInfo_open0(  0,  0,  _T(  "bShowDec_sharedTexStatus changed"  )  );
								   #endif
							   }
						   }
						   //  2016/04/14
						   unsigned  int  uiXql_player  =  0;
						   if  (  !pModule->compress.pf_qdcGetProp(  CONST_qdcPropId_uiXql_player,  NULL,  &uiXql_player  )  )  {
							   unsigned  int  tmpuiVal  =  pShmContent->status.uiXql_player;
							   if  (  uiXql_player  !=  tmpuiVal  )  {
								   pModule->compress.pf_qdcSetProp(  CONST_qdcPropId_uiXql_player,  &tmpuiVal,  NULL  );
								   //
								   #ifdef  __DEBUG__
										   showInfo_open0(  0,  0,  _T(  "xql_player changed"  )  );
								   #endif
							   }
						   }						   
					   }
				   }

			   }
		   }

		   //
		   continue;

	} 
 
// Flush the pipe to allow the client to read the pipe's contents 
// before disconnecting. Then disconnect the pipe, and close the 
// handle to this pipe instance. 
 
errLabel:

	//
	showInfo_open0(  0,  0,  _T(  "pipeThread: start to quit"  )  );
	
	//
	if  (  pRtsp->pDvt_decV  )  {
		DVT_decV  *  pDvt_decV  =  (  DVT_decV  *  )pRtsp->pDvt_decV;

		//
		pDvt_decV->bQuit  =  TRUE;
		//  2015/06/22
		SetEvent(  pDvt_decV->writeShm.hEvent_syncW  );
		//
		waitForObject(  &pDvt_decV->writeShm.hThread,  20000  );
		if  (  pDvt_decV->writeShm.hThread  )  {
			qyExitProcess(  _T(  "Failed: dvt_decV.writeShm.thread not waited"  )  );	
		}
		
		//
		if  (  pDvt_decV->writeShm.hEvent_syncR  )  {		
			CloseHandle(  pDvt_decV->writeShm.hEvent_syncR  );  pDvt_decV->writeShm.hEvent_syncR  =  NULL;	
		}
		//  2015/02/19
		if  (  pDvt_decV->writeShm.hEvent_syncW  )  {		
			CloseHandle(  pDvt_decV->writeShm.hEvent_syncW  );  pDvt_decV->writeShm.hEvent_syncW  =  NULL;	
		}

		
		//
		QY_shm  *  pShm  =  &pDvt_decV->dataShm;
		if  (  pShm->pBuf  )  {
			UnmapViewOfFile(  pShm->pBuf  );  
			pShm->pBuf  =  NULL;	 
		}
		if  (  pShm->hMap  )  {
			 CloseHandle(  pShm->hMap  );  pShm->hMap  =  NULL;	 
		}

		//
		MACRO_safeFree(  pRtsp->pDvt_decV  );
	}

	//  
	askRtspCliToQuit(  pRtsp  );
	//
	BOOL  tmpbRet;
	tmpbRet  =  CancelIo(  pRtsp->pipe.hPipe  );
	//
	DisconnectNamedPipe(  pRtsp->pipe.hPipe  ); 
	
	//
#ifdef  __DEBUG__
		showInfo_open0(  0,  0,  tmpbRet  ?  _T(  "pipeThread: CancelIo true"  )  :  _T(  "pipeThread: CancelIo false"  )  );
#endif

#endif


	traceLogA(  (char*)  "pipeInstanceThread leaves"  );
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "pipeThread leaves"  )  );


	return  1;
}





//
int  doRecvRtsp(  VIDEO_capDev_rtsp  *  pRtsp  )
{
	int  iErr	=	-1;
	
	MC_VAR_common						*	pProcInfo					=	(  MC_VAR_common  *  )pRtsp->pProcInfoCommon;	//  QY_GET_procInfo_isCli(  );
	 if (  !pProcInfo  )  return  -1;	 

	// QY_MC							*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;


	
		 
#ifdef  __DEBUG__
		  traceLog((TCHAR*)  _T(  "start rtsp session"  )  );
#endif

		  //
		  int  iBUFSIZE  =  CONST_bufSize_rtspCliPipe;

		  //
		  TCHAR  pipeName[128];
		  if  (  !isHandleValid(  pRtsp->pipe.hPipe  )  )  {
			  //pRtsp->tn_rtspCliPipe  =  getuiNextTranNo(  0,  0,  0  );
			  //  _sntprintf(  pipeName,  mycountof(  pipeName  ),  _T(  "%s%d"  ),  CONST_rtspCliPipePrefix,  pRtsp->tn_rtspCliPipe  );
			  M_get_pipeName(  CONST_rtspCliPipePrefix,  pProcInfo->get_appObjPrefix(  ),  pRtsp->tn_rtspCliPipe,  pipeName  );

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
		  BOOL  fPendingIO; fPendingIO = FALSE;
		  if  (  myConnectToNewClient(  pRtsp->pipe.hPipe,  &overlapStruct,  &fPendingIO  )  )  goto  errLabel;

		  		  
		  //
		  if  (  needRtspCliHelp(  pRtsp  )  )  {
			  if  (  !isHandleValid(  pRtsp->hProcess_rtspCliHelp  )  )  {
				  createRtspCliHelp(  pRtsp  );
			  }
		  }

		  
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
				 traceLog((TCHAR*)  _T(  "wait for being connected"  )  );
#endif
				 if  (  needRtspCliHelp(  pRtsp  )  )  {
					 //  2014/06/06
					 waitForObject(  &pRtsp->hProcess_rtspCliHelp,  0  );
					 if  (  !pRtsp->hProcess_rtspCliHelp  )  break;
				 }

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
		  if  (  needRtspCliHelp(  pRtsp  )  )  {
			  if  (  !pRtsp->hProcess_rtspCliHelp  )  {
				  if (!b__DBG_rtspCli__()) {
					  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("no rtspCli. retry."), _T(""));
					  goto  errLabel;
				  }
			  }
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
            pipeInstanceThread_doRecvRtsp,				// thread proc
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
		   if  (  needRtspCliHelp(  pRtsp  )  )  {
			   waitForObject(  &pRtsp->hProcess_rtspCliHelp,  0  );
			   if (!b__DBG_rtspCli__()) {
				   if (!pRtsp->hProcess_rtspCliHelp) {
					   break;
				   }
			   }
		   }
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
	  //
	  closeRtspCliHelp(  pRtsp  );



	  //  2015/05/09
	  iErr  =  0;
	 



errLabel:

	 //
	 if  (  pRtsp->hProcess_rtspCliHelp  )  {
		 closeRtspCliHelp(  pRtsp  );
	 }

	 //
	 closeQyPipeThread(  &pRtsp->pipe  );
	 //
	 closeQyPipe(  &pRtsp->pipe  );

	return  iErr;

}



//  2014/10/04
extern "C" DWORD WINAPI mcThreadProc_recvRtsp( LPVOID lpParameter )
{
	 //  VIDEO_capDev_rtsp  *  pRtsp  =  (  VIDEO_capDev_rtsp  *  )lpParameter;
	CAP_dev_rtspCommon  *  pRtsp  =  (  CAP_dev_rtspCommon  *  )lpParameter;

	CCtxQyMc* pQyMc = g_pQyMc;
	 MC_VAR_common					*	pProcInfo					=	(  MC_VAR_common  *  )pRtsp->pProcInfoCommon;//QY_GET_procInfo_isCli(  );
	 if (  !pProcInfo  )  return  -1;	 

	 //QY_MC							*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;
	 //DYN_LIB_DX						*	pDynLib						=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	 //  int								i;


	 #define		DEFAULT_dwToInMs		5000
	 DWORD								dwToInMs					=	DEFAULT_dwToInMs;

	 DWORD								dwTickCnt_lastAudioData		=	GetTickCount(  );;						// 

	 //  2014/03/15

#ifdef  __DEBUG__
	 traceLogA(  (char*)  "mcThreadProc_recvRtsp enters"  );
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
#ifdef  __DEBUG__

	 //

#ifdef  __USE_rtsp_asDll__
	{

	char	argv0[128]		=  (  "rtspCli"  );
	char	argv1[128]		=  (  "-t"  );
#if  0
	char	argv_D[128]		=  (  "-D"  );
	char	argv_DVal[128]  =  (  "2000"  );
#endif
	char	argv_url[256]	=  "";	//  (  "rtsp://127.0.0.1:8554/video.264"  );

	//
	myTChar2Utf8(  pRtsp->url,  argv_url,  mycountof(  argv_url  )  );

	//
	//	
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "rtsp starts, %s"  ),  CQyString(  argv_url  )  );


	//
	char  *  pArgv[10];

	int		tmp_argc  =  0;
	//
	pArgv[tmp_argc]  =  argv0;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv1;  tmp_argc  ++  ;
#if  0
	pArgv[tmp_argc]  =  argv2;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv3;  tmp_argc  ++  ;
#endif
	pArgv[tmp_argc]  =  argv_url;  tmp_argc  ++  ;

	//
	int  iIndex_capBmp  =  0;
	set_PF_BufferCB_rtsp(  BufferCB_av_rtsp_test_mp2t,  NULL,  iIndex_capBmp,  pQyMc->appParams.appObjPrefix,  0  );
	
	//
	rtspCliHelp_main(  tmp_argc,  pArgv  );

	//
	goto  errLabel;

}
#endif
#endif


	int  dwToInMs_rtsp  =  3000;

	 //
	 for  (  ;  !pRtsp->bQuit;  )  {
		 if  (  pRtsp->uiType  ==  CONST_rtspType_qvcf  )  {
			 qvcf_doRecvRtsp(  pRtsp  );
			 }
		 else  {
			   doRecvRtsp(  (  VIDEO_capDev_rtsp  *  )pRtsp  );
		 }
		 //
		 //  放慢一点点
		 Sleep(  200  );
	 }

errLabel:

#if  0
	 //
	 if  (  pRtsp->hProcess_rtspCliHelp  )  {
		 closeRtspCliHelp(  pRtsp  );
	 }

	 //
	 closeRtspCliPipeThread(  pRtsp  );
	 //
	 closeRtspCliPipe(  pRtsp  );
#endif

	 //
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s ends."  ),  _T(  "threadProc_recvRtsp"  )  );
	 

	 pRtsp->bRunning  =  FALSE;


	 traceLogA(  (char*)  "mcThreadProc_rtsp %S leaves",  _T(  "rtsp"  )  );

	return  0;
}



