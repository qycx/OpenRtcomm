
#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
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

#include	"isCliHelpPublic.h"
#include	"testOnly.h"
#include	"rtspUsrData.h"
#include	"qdcOpenCommon.h"
//
#include	"isCliD3dPublic.h"
//
#include	"qisNameDefs.h"
#include	"vtShmFunc.h"


//  2015/01/29
#ifdef  __DEBUG__
		//#define		__DUMP_h264_dvt__

		//
		//  #define		__DEBUG_dvt__

#endif


 //extern  "C"  DWORD WINAPI mcThreadProc_readShm_dvtCli( LPVOID lpParameter );


int  rtspCli_readResp(  RTSP_cli_common  *  pRtspCli,  RTSP_usrData_resp  *  pResp  )	
{
	int  iErr =  - 1;

	
	int  iSize  =  sizeof(  RTSP_usrData_resp  );	

	DWORD  nRead  =  0;
	if  (  !ReadFile(  pRtspCli->pipe.hPipe,  pResp,  iSize,  &nRead,  NULL  )  )  {
		goto  errLabel;
	}

	iErr  =  0;
errLabel:
	return  iErr;	
}

//
//  int  askDvtToQuit(  MC_VAR_common  *  pProcInfo,  DVT_cli  *  pDvtCli  )
int  askVtToQuit(  void  *  pMC_VAR_common,  unsigned  int  tn_cliPipe,  VT_process  *  pVtProcess  )
{
	int  iErr  =  -1;
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pMC_VAR_common;
	if  (  !pProcInfo  )  return  -1;
	DWORD  dwRet;		 
	//
	TCHAR	evtName[256];		
	HANDLE	hEvent  =  NULL;		 
	int  i;
		
	//  
	//if  (  !pDvtCli->tn_cliPipe  )  return  0;
			
#if  10
	M_get_evtName_syncQuit(  CONST_evtNamePrefix_rtspCliSyncQuit,  pProcInfo->get_appObjPrefix(  ),  tn_cliPipe,  evtName  );
	//_sntprintf(  evtName,  mycountof(  evtName  ),  _T(  "%s%d"  ),  CONST_evtNamePrefix_rtspCliSyncQuit,  pRtsp->tn_rtspCliPipe  );	
	hEvent  =  CreateEvent(  NULL,  FALSE,  FALSE,  evtName  );
#endif

	//	
	if  (  hEvent  )  SetEvent(  hEvent  );

	 
	iErr  =  0;

errLabel:

	
	if  (  hEvent  )  CloseHandle(  hEvent  );

	return  iErr;
}



//
//int  createVt(  void  *  pMC_VAR_common,  int  iVtType,  unsigned  int  tn_cliPipe,  VT_process  *  pVtProcess,  LPCTSTR  hint  )
int  createVt(  void  *  pMC_VAR_common,  int  iVtType,  unsigned  int  tn_cliPipe,  unsigned  short  usPktResType1,  VT_process  *  pVtProcess,  LPCTSTR  hint  )
{
	int			iErr	=	-1;
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pMC_VAR_common;
	if  (  !pProcInfo  )  return  -1;
	//
	QY_MC	*	pQyMc	=	(  QY_MC  *  )pProcInfo->pQyMc;//QY_GET_GBUF(  );
	if  (  !pQyMc  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "createRtspCliHelp failed, pQyMc is null"  )  );
		#endif
		return  -1;
	}
	//if  (  !pTransform  )  return  -1;
	//  DVT_cli  *  pDvtCli  =  &pTransform->video.dvtCli;
	//
	STARTUPINFO				si;
	PROCESS_INFORMATION		pi;
	BOOL						bProcessCreated				=		FALSE;
	TCHAR						tmpExeName[MAX_PATH  +  1]	=	_T(  ""  );
	
	//
	if  (  pVtProcess->hProcess_vt  )  return  0;

	//
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
	
	//
	TCHAR  *  toolName  =  (TCHAR*)_T(  ""  );
	//unsigned  short  usPktResType  =  0;
	switch  (  iVtType  )  {
			case  CONST_vtType_decV:
				  toolName  =  (TCHAR*)_T(  "qyDecTool.exe"  );
				  //usPktResType  =  pProcInfo->get_pktResType_suggested(  CONST_pktUsage_dec  );
				  break;
			case  CONST_vtType_encV:
				  toolName  =  (TCHAR*)_T(  "qyEncTool.exe"  );
				  //usPktResType  =  pProcInfo->get_pktResType_suggested(  CONST_pktUsage_enc  );
				  break;
			default:
					goto  errLabel;
	}


	//
#define  CONST_subDir_dvt	_T(  "bin\\"  )
	_sntprintf(  tmpExeName,  mycountof(  tmpExeName  ),  _T(  "%s%s%s"  ),  pQyMc->cfg.installDir,  CONST_subDir_dvt,  toolName  );	
	if  (  tQyQuoteFileName(  tmpExeName,  mycountof(  tmpExeName  )  )  )  goto  errLabel;

	//
	_sntprintf(  tmpExeName,  mycountof(  tmpExeName  ),  _T(  "%s -a%s -tn=%d"  ),  tmpExeName,  pProcInfo->get_appObjPrefix(  ),  tn_cliPipe  );
	if  (  hint  )  _sntprintf(  tmpExeName,  mycountof(  tmpExeName  ),  _T(  "%s -%s%s"  ),  tmpExeName,  CONST_qmCmdLine_sym_tag,  hint  );	//  2015/02/17
	
	//  2015/10/04
	//if  (  !pTransform->pCapDev_rtsp  )  
	{
	}
	_sntprintf(  tmpExeName,  mycountof(  tmpExeName  ),  _T(  "%s -%s%d"  ),  tmpExeName,  CONST_qmCmdLine_pktResType_suggested,  (  int  )usPktResType1  );

	//
	DWORD  dwCreationFlags; dwCreationFlags = CREATE_NO_WINDOW;
	QMC_debugStatusInfo* pCfg_debugStatusInfo; pCfg_debugStatusInfo = pProcInfo->get_qmc_debugStatusInfo();
#if  0
	if  (  pCfg_debugStatusInfo
		&&  pCfg_debugStatusInfo->ucbShowRtspCliControl  )  		
	{
			dwCreationFlags  =  0;
	}
#endif
	//
	if  (  !CreateProcess(  NULL,  tmpExeName,  NULL,  NULL,  0,  dwCreationFlags,  NULL,  NULL,  &si,  &pi  )  )  goto  errLabel;	 	
	bProcessCreated  =  TRUE;

#ifdef  __DEBUG__
	traceLogA(  (char*)  "CreateProcess %s succeeded,  new processId is %d,  new threadId is %d.",  tmpExeName,  pi.dwProcessId,  pi.dwThreadId  );
	qyShowInfo(  pQyMc->pShowInfoStruct,  CONST_qyShowType_qwmComm,  0,  (char*)"",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "create %s ok"  ),  tmpExeName  );
#endif


	//
	iErr  =  0;

errLabel:
	
	if  (  bProcessCreated  )  {
		 if  (  pi.hThread  )  {  CloseHandle(  pi.hThread  );  pi.hThread  =  NULL;  }
		 if  (  pi.hProcess  )  pVtProcess->hProcess_vt  =  pi.hProcess;
	 }

	if  (  iErr  )  {
		qyShowInfo(  pQyMc->pShowInfoStruct,  CONST_qyShowType_qwmComm,  0,  (char*)"",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "createVt failed, %s"  ),  tmpExeName  );
	}

	return  iErr;

}


//int  closeDvt(  MC_VAR_common  *  pProcInfo,  DVT_cli  *  pDvtCli  )
int  closeVt(  void  *  pMC_VAR_common,  unsigned  int  tn_cliPipe,  VT_process  *  pVtProcess  )
{
	int  iErr  =  -1;
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pMC_VAR_common;//  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	DWORD  dwRet;		 
	//
	int  i;

	if  (  !pVtProcess->hProcess_vt  )  return  0;
			
	
	//	
	for  (  i  =  0;  i  <  30;  i  ++  )  {		
		 //
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)"",  pProcInfo->who_showInfo,  0,  _T(  "closeVt:"  ),  _T(  ""  ),  _T(  "askDvtToQuit,  %d"  ),  i  );
		//
		askVtToQuit(  pProcInfo,  tn_cliPipe,  pVtProcess  );
		 //
		dwRet  =  WaitForSingleObject(  pVtProcess->hProcess_vt,  1000  );
		 if  (  dwRet  !=  WAIT_FAILED  &&  dwRet  !=  WAIT_TIMEOUT  )  {
			 CloseHandle(  pVtProcess->hProcess_vt  );  pVtProcess->hProcess_vt  =  NULL;
			 //
			 showInfo_open0(  0,  0,  _T(  "vt waited"  )  );
			 //
			 break;
		 }		
		 if  (  i  >=  2  )  {
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)"",  pProcInfo->who_showInfo,  0,  _T(  "closeVt:"  ),  _T(  ""  ),  _T(  "too long to wait, terminate dvt"  )  );
			 TerminateProcess(  pVtProcess->hProcess_vt,  -1  );
		 }
	}

	//	
	if  (  pVtProcess->hProcess_vt  )  {	//  即使没回收，也要关闭了
#ifdef  __DEBUG__
			 myMessageBox(  NULL,  _T(  "即使没回收，也要关闭了. 这里没做好，应该rtspCli赶紧退出的"  ),  0,  0  );
#endif
			 //
			 CloseHandle(  pVtProcess->hProcess_vt  );  pVtProcess->hProcess_vt  =  NULL;		
	}
	 
	iErr  =  0;

errLabel:

	return  iErr;
}


//
//  int  doDecodeVideo_dvtCli(  QY_TRANSFORM  *  pTransform,  int  index_pMems_from,  MIS_MSGU  *  pMsgBuf  )
int  doDecodeVideo_dvtCli(  QY_TRANSFORM  *  pTransform,  int  index_pMems_from,  unsigned  int  uiModuleType_toDec,  MIS_MSGU  *  pMsgBuf  )
{
	int  iErr  =  -1;

	//MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMIS_CNT;

#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "doDecodeVideo_tool enters"  )  );
#endif

	//
	QY_MC				*	pQyMc				=	QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo			=  QY_GET_procInfo_isCli(  );
	//
	QMC_cfg				*	pQmcCfg				=	(  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;

	//  2016/04/28
	if  (  !uiModuleType_toDec  )  {
		showInfo_open0(  0,  0,  _T(  "doDecodeVideo_dvtCli failed, uiModuleType_toDec is 0"  )  );
		return  -1;
	}

	//
	MSGR_ADDR			*	pAddr				=	pTransform->pAddr_logicalPeer;
	if  (  !pAddr  )  return  -1;
	int						iTaskId				=	pTransform->iTaskId;
	//
	AV_TRAN_INFO		*	pTranInfo_unused			=	(  AV_TRAN_INFO  *  )pTransform->pTranInfo_unused;
	if  (  !pTranInfo_unused  )  return  -1;
	//
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pTransform->pTask;
	if  (  !pTask  )  return  -1;
	
#if  0
	TASK_AV_FROM		*	pFrom				=	NULL;

	//
	CQyMalloc  mallocObj_pResp;		
	int  iSize  =  sizeof(  RTSP_usrData_resp  );	
	RTSP_usrData_resp  *  pResp  =  (  RTSP_usrData_resp  *  )mallocObj_pResp.mallocf(  iSize  );
	if  (  !pResp  )  return  -1;

	//
	TRANSFORM_VIDEO_procInfo		*	pTransformVideo				=	&pTransform->video;
	DVT_cli							*	pDvtCli						=	&pTransformVideo->dvtCli;
	//
	TCHAR		tBuf[128];

	//
	pDvtCli->bQuit  =  FALSE;
	memset(  &pDvtCli->status,  0,  sizeof(  pDvtCli->status  )  );

	//
	int  size  =  sizeof(  RTSP_cli_common  );
	pDvtCli->pRtspCli  = mymalloc(  size  );
	if  (  !pDvtCli->pRtspCli  )  goto  errLabel;
	RTSP_cli_common  *  pRtspCli  =  (  RTSP_cli_common  *  )pDvtCli->pRtspCli;
	memset(  pRtspCli,  0,  sizeof(  pRtspCli[0]  )  );
	
	//
	int  iIndex_capProcInfo  =  0;
	pDvtCli->tn_cliPipe  =  getuiNextTranNo(  0,  0,  0  );

	//
	if  (  pQyMc->appParams.ucbDbgDvt  )  {
		#if  1  //  def  __DEBUG_dvt__
		//
		pDvtCli->tn_cliPipe  =  64;
		//traceLog((TCHAR*)  _T(  "TEST: tn_rtspCliPipe is set to 10"  )  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "__DEBUG_dvt__: tn_rtspCliPipe is set to %d"  ),  pDvtCli->tn_cliPipe  );
		showInfo_open0(  0,  0,  tBuf  );
		//
		#endif
	}
	//
	if  (  rtspCliCommon_init(  BufferCB_rtspCliCommon,  rtspCliCommon_exit,  iIndex_capProcInfo,  pProcInfo->get_appObjPrefix(  ),  pDvtCli->tn_cliPipe,  pRtspCli  )  )  {
		goto  errLabel;
	}
	
	//	
	RTSP_msg  *  pRtspMsg  =  (  RTSP_msg  *  )pRtspCli->pRTSP_msg;		
	if  (  !pRtspMsg  )  goto  errLabel;


	//
	pFrom  =  getTaskAvFrom(  pTransform,  index_pMems_from,  pTransform->index_activeMems_from,  _T(  "doDecodeVideo_msdk"  )  );
	if  (  !pFrom  )  return  -1;

	//
	exitTaskAvFrom_video(  pProcInfo,  pTransform  );
	

	MACRO_setMyStep(  pTransform->video.debugStep,  21  );

		 //  if  (  !pFrom->video.ucbInited  )  
		 if  (  !pTransform->video.ucbInited  )  
		 {
			 unsigned  int  uiModuleType_suggested  =  uiModuleType_toDec;	//  CONST_moduleType_mediaSdk_dec;
			 BOOL  bUseDecTool  =  TRUE;
			 //
			 if  (  initTaskAvFrom_video(  pProcInfo,  pFrom,  index_pMems_from,  pTransform->iTaskId,  uiModuleType_suggested,  bUseDecTool,  pTransform  )  )  goto  errLabel;
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskVideo: initTaskAvFrom_video %d"  ),  index_pMems_from  );
		 }
		 if  (  !pTransform->video.ucbInited  )  {
			 traceLogA(  (char*)  "procTaskVideo failed: video is not inited"  );
			 goto  errLabel;
		 }

		 //
#if  0  //  2016/04/28
		 if  (  pTransform->video.uiModuleType_toDec  !=  CONST_moduleType_mediaSdk_dec  )  {
			 #ifdef  __DEBUG__
					 traceLog((TCHAR*)  _T(  "doTransformVideo_mediaSdk failed, uiModuleType_toDec is not mediaSdk_dec"  )  );
			 #endif
			 goto  errLabel;
		 }
#endif

		 //
		 QDC_OBJ_INFO  *  pQdcObjInfo  =  &pTransform->video.u.qoi.myQoi.common;
		 long  old_lPktId  =  0;

		 //		 		
		 int		iMediumType  =  CONST_mediumType_video;
		 int		iCodecType  =  0;	//  CONST_codecType_h264;
		 unsigned  short  usPktResType  =  0;

		 //  2016/04/28
		 usPktResType  =  pTransformVideo->usPktResType;
		 	  
		 //
		 //  decTool
		 //
		 //  2017/10/08
		 int  iFourcc_enc  =  fourccStr2i(  pFrom->video.tv_recvd.compressor.common.fourccStr  );
		 switch  (  iFourcc_enc  )  {
				 case  CONST_fourcc_h264:
					   iCodecType  =  CONST_codecType_h264;
					   break;
				 case  CONST_fourcc_HEVC:
					   iCodecType  =  CONST_codecType_HEVC;
					   break;
				 default:
						 showInfo_open0(  0,  0,  _T(  "doDecodeVideo_dvtCli failed, unprocessed fourcc"  )  );
					     goto  errLabel;
						 break;
		 }

		 //  2016/04/26
		 if  (  !pQyMc->appParams.ucbDbgDvt  )  {
			 #if  1  //  ndef  __DEBUG_dvt__
			 //
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d.from%d"  ),  pTransform->iTaskId,  index_pMems_from  );
			 if  (  createVt(  pProcInfo,  CONST_vtType_decV,  pDvtCli->tn_cliPipe,  usPktResType,  &pDvtCli->vtProcess,  tBuf  )  )  {
				 showInfo_open0(  0,  0,  _T(  "createDvt failed"  )  );
				 goto  errLabel;		 
			 }
			#endif
			}
		 else  {  //  2016/04/27
			   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "__DEBUG_dvt__: pktResType %d"  ),  (  int  )usPktResType  );
			   showInfo_open0(  0,  0,  tBuf  );
		 }
		 
		 //
		 //  先建立发送管道		 
		 showInfo_open0(  0,  0,  _T(  "doDecV_tool, try to chkPipe"  )  );
		 int  i;
		 BOOL  bPipeOk  =  FALSE;
		 for  (  i  =  0;  i  <  50;  i  ++  )  {
			  if  (  !rtspCliCommon_chkPipe(  pRtspCli  )  )  {
				  bPipeOk  =  TRUE;
				  break;
			  }
			  //
			  Sleep(  100  );			  
		 }
		 if  (  !bPipeOk  )  {
			 showInfo_open0(  0,  0,  _T(  "doDecV_tool, chkPipe failed"  )  );
			 goto  errLabel;
		 }
		 showInfo_open0(  0,  0,  _T(  "doDecV_tool, chkPipe ok"  )  );


		//  2015/01/29
#ifdef  __DEBUG__
		#ifdef  __DUMP_h264_dvt__ 
		  static  BOOL  bReset  =  FALSE;
		  TCHAR  *  pDir  =  _T(  "c:\\tttbbb\\dd\\"  );		  						  
		  TCHAR  *  fn  =  _T(  "kk.264"  );		
		  int  i;
		  for  (  i  =  0;  i  <  pFrom->video.tv_recvd.vh_stream.usCnt;  i  ++  )  {
			  dumpVideo_init(  &bReset,  pDir,  fn,  pFrom->video.tv_recvd.vh_stream.mems[i].spsPps,  pFrom->video.tv_recvd.vh_stream.mems[i].usLen  );				
		  }

		#endif
#endif



	unsigned  int  uiSampleTimeInMs  =  0;
	unsigned  int  uiPts  =  0;	//  2015/02/09
	unsigned  char  *  pBuffer  =  NULL;
	long  BufferLen  =  0;
	bool  bSpsPps  =  false;
	int  index_spsPps  =  0;
	bool  bFinished_spsPps  =  FALSE;
	CB_rtsp_res		res;
	bool  bNeedResp  =  true;	//  2015/01/30


#ifdef  __DEBUG__
	showInfo_open0(  0,  0,  _T(  "to send usrData_commInfo"  )  );
#endif
	//  send usrData_commInfo
	iMediumType  =  CONST_mediumType_usrData;
	//
	RTSP_usrData_commInfo	rtspUsrData;
	memset(  &rtspUsrData,  0,  sizeof(  rtspUsrData  )  );
	rtspUsrData.uiType  =  CONST_rtspUsrDataType_commInfo;
	//
	pBuffer  =  (  unsigned  char  *  )&rtspUsrData;
	BufferLen  =  sizeof(  rtspUsrData  );
	//
	memset(  &res,  0,  sizeof(  res  )  );
	//
	if  (  BufferCB_rtspCliCommon(  pRtspCli,  pRtspCli->iIndex_capProcInfo,  iMediumType,  iCodecType,  uiSampleTimeInMs,  uiPts,  0,  pBuffer,  BufferLen,  bSpsPps,  index_spsPps,  bFinished_spsPps,  bNeedResp,  &res  )  )  {					
		goto  errLabel;			  		 
	}	
	//
	if  (  bNeedResp  )  {
		if  (  rtspCli_readResp(  pRtspCli,  pResp  )  )  goto  errLabel;
	}

	//
	iMediumType  =  CONST_mediumType_video;
	bNeedResp  =  false;
	//  发送头信息给decTool
	for  (  i  =  0;  i  <  pFrom->video.tv_recvd.vh_stream.usCnt;  i  ++  )  {

		 uiSampleTimeInMs  =  0;
		 pBuffer  =  (  unsigned  char  *  )pFrom->video.tv_recvd.vh_stream.mems[i].spsPps;		
		 BufferLen  =  pFrom->video.tv_recvd.vh_stream.mems[i].usLen;;
		 bSpsPps  =  true;
		 index_spsPps  =  i;
		 bFinished_spsPps  =  FALSE;
		 memset(  &res,  0,  sizeof(  res  )  );
		 
		 //		
		 if  (  BufferCB_rtspCliCommon(  pRtspCli,  pRtspCli->iIndex_capProcInfo,  iMediumType,  iCodecType,  uiSampleTimeInMs,  uiPts,  0,  pBuffer,  BufferLen,  bSpsPps,  index_spsPps,  bFinished_spsPps,  bNeedResp,  &res  )  )  {			
			 goto  errLabel;			  
		 }		   
	}
	pBuffer  =  NULL;
	BufferLen  =  0;
	bSpsPps  =  true;
	index_spsPps  =  pFrom->video.tv_recvd.vh_stream.usCnt;
	bFinished_spsPps  =  TRUE;
	memset(  &res,  0,  sizeof(  res  )  );
	if  (  BufferCB_rtspCliCommon(  pRtspCli,  pRtspCli->iIndex_capProcInfo,  iMediumType,  iCodecType,  uiSampleTimeInMs,  uiPts,  0,  pBuffer,  BufferLen,  bSpsPps,  index_spsPps,  bFinished_spsPps,  bNeedResp,  &res  )  )  {						 
		goto  errLabel;			  		 
	}		   

	//	
	//  2016/04/19
	pDvtCli->status.noDecData.nTimes_noDecData  =  0;		
	pDvtCli->status.noDecData.dwStartTickCnt_noDecData  =  GetTickCount(  );	//  dwTickCnt;

	
	//
	for  (  ;  !pTransformVideo->bQuit;  )  {
		  
		  //  2010/12/28
		  MACRO_setStep(  pTransformVideo->debugStep,  CONST_threadStep_toWait  );

		  HANDLE  hs[5];
		  unsigned  short  usCnt  =  0;
		  hs[usCnt]  =  pTransformVideo->q2.hEvents[0];  usCnt  ++  ;
		  hs[usCnt]  =  pTransformVideo->q2.hEvents[1];	 usCnt  ++  ;
		  //hs[usCnt]  =  hProcess_tool;					 usCnt  ++  ;

		  //
		  DWORD  dwEvt  =  MsgWaitForMultipleObjects(							
							 usCnt,	//  mycountof(  pPlay->hEvents  ),				// Number of events.
							 hs,							// Location of handles.
                             FALSE,										// Wait for all?
                             5000,									// How long to wait?
                             0  );										// Any message is an 
																		// event.
		  if  (  dwEvt  ==  WAIT_FAILED  )  goto  errLabel;
	      //
		  //dwTickCnt  =  GetTickCount(  );

		  if  (  dwEvt  !=  WAIT_TIMEOUT  )  {
			  dwEvt -= WAIT_OBJECT_0;
			  switch  (  dwEvt  )  {
					  case  0:
						     //  dwTickCnt_lastData  =  dwTickCnt;		//  audio data received
						       //  traceLogA(  (char*)  "mcThreadProcInfo_toShareBmp: event 0."  );
							 break;
					  case  1:
						     traceLogA(  (char*)  "mcThreadProcInfo_toShareBmp: event 1."  );
							 break;
					  default:
						     traceLogA(  (char*)  "unknown event"  );	
		  					 goto  errLabel;
							 break;
			  }
			  //

		  }


		  for  (  ;  !pTransformVideo->bQuit;  )  {

			  myDRAW_VIDEO_DATA  *  pCurPkt  =  (  myDRAW_VIDEO_DATA  *  )pQdcObjInfo->cfg.v.pCurPkt;
			  if  (  !pCurPkt->memory.m_pBuf  &&  isQEmpty(  (  GENERIC_Q  *  )pQdcObjInfo->cfg.v.pInDataCacheQ  )  &&  isQ2Empty(  (  QY_Q2  *  )pQdcObjInfo->cfg.v.pVideoQ2  )  )  break;
			  
			  //  2016/03/29
			   DWORD  dwTickCnt  =  GetTickCount(  );
			   int  iElapseInMs  =  0;
			   //
			   BOOL  bChk_noDecData  =  TRUE;

			   //  2016/04/13
			   #ifdef  __DEBUG__
					   #if  0
							bChk_noDecData  =  FALSE;
							traceLog((TCHAR*)  _T(  "Note: bChk_noDecData is off"  )  );
						#endif
			   #endif

			   //
			   if  (  bChk_noDecData  )  {
				   //
				   if  (  dwTickCnt  <  pDvtCli->status.dwLastTickCnt_decDataGot  +  4000  )  {
					   pDvtCli->status.noDecData.nTimes_noDecData  =  0;		
					   pDvtCli->status.noDecData.dwStartTickCnt_noDecData  =  dwTickCnt;
					   }			 				   
				   else  {				   
					     pDvtCli->status.noDecData.nTimes_noDecData  ++  ;		
						 //
						 int  iMax_nTimes_noDecData  =  150;
						 //
						 switch  (  pTransform->uiTaskType  )  {
								 case  CONST_imTaskType_transferAvInfo:
									   iMax_nTimes_noDecData  =  100;
									   break;
								 default:
										break;
						 }
						 //
						 #ifdef  __DEBUG__  //  2017/10/09
								 if  (  pQyMc->appParams.ucbDbgDvt  )  {
									 iMax_nTimes_noDecData  =  1000;
									 traceLog((TCHAR*)  _T(  "let iMax_nTimes_noDecData = 1000, because dbgDvt is 1"  )  );
								 }
						 #endif
						 //
						 int  maxElapse  =  4000;  //  2016/08/30
						 //
						 if  (  !pDvtCli->dataShm.hMap  )  {	//  2016/08/30. 
							 maxElapse  =  6000;
						 }
						 //
						 iElapseInMs  =  dwTickCnt  -  pDvtCli->status.noDecData.dwStartTickCnt_noDecData;
						 //
						 if  (  pDvtCli->status.noDecData.nTimes_noDecData  >  iMax_nTimes_noDecData
							 &&  iElapseInMs  >  maxElapse  )  
						 {						 

							 //  2016/03/29
							 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "decV failed, noDecData too long, nTimes_noDecData %d,  elapse_noDecData %dms"  ),  pDvtCli->status.noDecData.nTimes_noDecData,  iElapseInMs  );
							 showInfo_open0(  0,  0,  tBuf  );
							 showNotification_open(  0,  0,  0,  tBuf  );
							 //
							 goto  errLabel;

						 }
				   }

				   //
				   #ifdef  __DEBUG__
								 #if  0
						 							 //  2016/03/29
									_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "decV failed, noDecData too long, nTimes_noDecData %d,  elapse_noDecData %dms"  ),  pDvtCli->status.nTimes_noDecData,  iElapseInMs  );
									showInfo_open0(  0,  0,  tBuf  );
									showNotification_open(  0,  0,  0,  tBuf  );

								 #endif
				   #endif

			   }

			   //
			   #ifdef  __DEBUG__
					   #if  0
					   static  DWORD  dwTickCnt_test_minutes  =  0;
					   int  iDiffInMs  =  dwTickCnt  -   dwTickCnt_test_minutes;
					   if  (  abs(  iDiffInMs  )  >  1000  *  30  )  {
						   showInfo_open0(  0,  0,  _T(  "start to sleep SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS"  )  );
						   Sleep(  1200  );
						   showInfo_open0(  0,  0,  _T(  "end sleeping EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE"  )  );
						   dwTickCnt_test_minutes  =  dwTickCnt;
					   }
					   #endif
			   #endif


			  
			  //			  				  
			  unsigned  int  nBytesRead  =  sizeof(  pRtspMsg->buf  );
			  uiSampleTimeInMs  =  0;
			  SMPL_bsRead_param  param;		//  2015/02/24
			  memset(  &param,  0,  sizeof(  param  )  );
			  //
			  //  if  (  pQdcObjInfo->cfg.dec.pf_smplBitstreamReader_ReadNextFrame_func(  pQdcObjInfo,  &old_lPktId,  0,  (  char  *  )(  pRtspMsg->buf  ),  &nBytesRead,  &uiSampleTimeInMs  )  )  
			  if  (  smplBitstreamReader_ReadNextFrame_func_v_new(  pQdcObjInfo,  &old_lPktId,  0,  (  char  *  )(  pRtspMsg->buf  ),  &nBytesRead,  &uiSampleTimeInMs,  &uiPts,  &param  )  )  
			  {		
				  showInfo_open0(  0,  0,  _T(  "doDecodeVideo_tool failed, smplBitstreamReader_ReadNextFrame_func_new failed"  )  );
				  goto  errLabel;	 		
			  }
			  pRtspMsg->uiLen  =  nBytesRead;;

			  //
			  iMediumType  =  CONST_mediumType_video;
			  bNeedResp  =  false;
			  //
			  unsigned  char  *  pBuffer  =  (  unsigned  char  *  )pRtspMsg->buf;
			  long  BufferLen  =  nBytesRead;
			  bool  bSpsPps  =  false;
			  int  index_spsPps  =  0;
			  bool  bFinished_spsPps  =  FALSE;
			  CB_rtsp_res  res;
			  			  
			  //  2015/01/29
			  #ifdef  __DEBUG__
					  #ifdef  __DUMP_h264_dvt__
	  					   dumpVideo(  pDir,  fn,  (  char  *  )pBuffer,  BufferLen  );
					  #endif
			  #endif
			  //
			  if  (  !pDvtCli->status.bShmOpen_dvt  )  {
				  bNeedResp  =  true;
			  }
			  		  

			  //
			  memset(  &res,  0,  sizeof(  res  )  );
			  res.dwTickCnt_doPretrans  =  param.dwTickCnt_doPretrans;	//  2015/02/24
			  //
			  if  (  BufferCB_rtspCliCommon(  pRtspCli,  pRtspCli->iIndex_capProcInfo,  iMediumType,  iCodecType,  uiSampleTimeInMs,  uiPts,  0,  pBuffer,  BufferLen,  bSpsPps,  index_spsPps,  bFinished_spsPps,  bNeedResp,  &res  )  )  {
				  goto  errLabel;
			  }		   
			  //
			  if  (  bNeedResp  )			  	{
				  if  (  rtspCli_readResp(  pRtspCli,  pResp  )  )  goto  errLabel;	
				  //
				  #ifdef  __DEBUG__
						  TCHAR  tBuf[128];
						  char  fourccStr[4  +  1];
						  iFourcc2Str(  pResp->bih_dec.biCompression,  fourccStr,  mycountof(  fourccStr  )  );
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "getResp, %S, %dX%d. imgSize %d"  ),  fourccStr,  pResp->bih_dec.biWidth,  pResp->bih_dec.biHeight,  pResp->bih_dec.biSizeImage  );
						  showInfo_open0(  0,  0,  tBuf  );
				  #endif

				  //
				  if  (  pResp->bih_dec.biWidth  &&  pResp->bih_dec.biHeight  )  {
					  QY_shm  *  pShm  =  &pDvtCli->dataShm;
					  //
					  if  (  pDvtCli->dataShm.hMap   )  {
						  if  (  pResp->bih_dec.biWidth  !=  pTransformVideo->tv.vh_decompress.bih.biWidth  
							  ||  pResp->bih_dec.biHeight  !=  pTransformVideo->tv.vh_decompress.bih.biHeight  )
						  {
							  goto  errLabel;
						  }
						  //
						  //
						  }
					  else  {
						    updateDecVideoParam( &pResp->bih_dec,  pResp->dFrameRate,  pTransform,  CONST_uiTransformType_dec  );  
							
							//
							unsigned  char  ucCnt_shmPktBufs  =  MAX_shmPktBufs_dvt;
							unsigned  int  uiBufSize_pBuf  =  offsetof(  VT_shm_content,  buf  )  +  pResp->bih_dec.biSizeImage  *  ucCnt_shmPktBufs;    
							//
							if  (  usPktResType  ==  CONST_pktResType_sharedTex  )  {
								ucCnt_shmPktBufs  =  MAX_shmPktBufs;
								uiBufSize_pBuf  =  offsetof(  VT_shm_content,  buf  );
							}
							//
							pShm->uiBufSize_pBuf  =  uiBufSize_pBuf;	//  offsetof(  VT_shm_content,  buf  )  +  pResp->bih_dec.biSizeImage  *  ucCnt_shmPktBufs;
							if  (  !pShm->uiBufSize_pBuf  )  goto  errLabel;
							//
							_sntprintf(  pShm->shmName,  mycountof(  pShm->shmName  ),  _T(  "Local\\%s%s%d"  ),  CQyString(  pQyMc->appParams.appObjPrefix  ),  CONST_shmName_qm_dvt,  pRtspCli->tn_rtspCliPipe  );						// name of mapping object 
							//
							pShm->hMap  =  CreateFileMapping(
											INVALID_HANDLE_VALUE,						// use paging file
											NULL,										// default security 
											PAGE_READWRITE,							// read/write access                 
											0,											// max. object size 
											pShm->uiBufSize_pBuf,				// buffer size  
											pShm->shmName  );						// name of mapping object 	 
							if  (  pShm->hMap  ==  NULL  ) { 
								traceLogA(  (char*)"Could not create file mapping object (%d).\n",  GetLastError());
								goto  errLabel;	 
							}
							pShm->pBuf  =  (  char  *  ) MapViewOfFile(pShm->hMap,   // handle to map object
						                        FILE_MAP_ALL_ACCESS,			// read/write permission
						                        0,                   
						                        0,                   
												pShm->uiBufSize_pBuf  );           
							if  (  !pShm->pBuf  )  goto  errLabel;

							//
							VT_shm_content  *  pShmContent;
							pShmContent  =  (  VT_shm_content  *  )pShm->pBuf;
							//
							memset(  pShmContent,  0,  offsetof(  VT_shm_content,  buf  )  );
							//
							pShmContent->bih_dec  =  pResp->bih_dec;
							//  2015/02/19
							pShmContent->ucCnt_shmPktBufs  =  ucCnt_shmPktBufs;
							
							//  2016/04/12
							_sntprintf(  pShmContent->cfg.name,  mycountof(  pShmContent->cfg.name  ),  _T(  "%I64u"  ),  pFrom->idInfo.ui64Id  );

							//
							if  (  pDvtCli->readShm.hEvent_syncR  )  goto  errLabel;							
							_sntprintf(  pDvtCli->readShm.evtName_syncR,  mycountof(  pDvtCli->readShm.evtName_syncR  ),  _T(  "%s%s%d"  ),  pQyMc->appParams.appObjPrefix,  CONST_evtNamePrefix_rtspCliSyncR,  pDvtCli->tn_cliPipe  );
							pDvtCli->readShm.hEvent_syncR  =  CreateEvent(  NULL,  FALSE,  FALSE,  pDvtCli->readShm.evtName_syncR  );
							if  (  !pDvtCli->readShm.hEvent_syncR  )  goto  errLabel;

							//  2015/02/19
							if  (  pDvtCli->readShm.hEvent_syncW  )  goto  errLabel;							
							_sntprintf(  pDvtCli->readShm.evtName_syncW,  mycountof(  pDvtCli->readShm.evtName_syncW  ),  _T(  "%s%s%d"  ),  pQyMc->appParams.appObjPrefix,  CONST_evtNamePrefix_rtspCliSyncW,  pDvtCli->tn_cliPipe  );
							pDvtCli->readShm.hEvent_syncW  =  CreateEvent(  NULL,  FALSE,  FALSE,  pDvtCli->readShm.evtName_syncW  );
							if  (  !pDvtCli->readShm.hEvent_syncW  )  goto  errLabel;
							
							//
							//create thread_readShm.
							if  (  !pDvtCli->readShm.hThread  )  {			
								DWORD  dwThreadDaemonId;
								pDvtCli->readShm.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_readShm_dvtCli,  pTransform,  CREATE_SUSPENDED,  &dwThreadDaemonId  );				   
								if  (  !pDvtCli->readShm.hThread  )  goto  errLabel;					
								pDvtCli->readShm.dwThreadId  =  dwThreadDaemonId;			
								if  (  ResumeThread(  pDvtCli->readShm.hThread  )  ==  -1  )  goto  errLabel;	
							}			   

							//

							//  send usrData_commInfo
							iMediumType  =  CONST_mediumType_usrData;
							bNeedResp  =  TRUE;
							//
							RTSP_usrData_commInfo	rtspUsrData;
							memset(  &rtspUsrData,  0,  sizeof(  rtspUsrData  )  );
							rtspUsrData.uiType  =  CONST_rtspUsrDataType_commInfo;
							rtspUsrData.bShmReady  =  TRUE;
							//	
							pBuffer  =  (  unsigned  char  *  )&rtspUsrData;
							BufferLen  =  sizeof(  rtspUsrData  );	
							//
							memset(  &res,  0,  sizeof(  res  )  );
							//
							if  (  BufferCB_rtspCliCommon(  pRtspCli,  pRtspCli->iIndex_capProcInfo,  iMediumType,  iCodecType,  uiSampleTimeInMs,  uiPts,  0,  pBuffer,  BufferLen,  bSpsPps,  index_spsPps,  bFinished_spsPps,  bNeedResp,  &res  )  )  {							
								showInfo_open0(  0,  0,  _T(  "doDecodeVideo_tool failed, BufferCB_rtspCliCommon failed"  )  );
								goto  errLabel;			  		 
							}		
							//
							if  (  bNeedResp  )  {
								if  (  rtspCli_readResp(  pRtspCli,  pResp  )  )  {
									showInfo_open0(  0,  0,  _T(  "doDecodeVideo_tool failed, rtspCli_readResp failed"  )  );
									goto  errLabel;
								}
								//
								if  (  !pResp->bShmOpen  )  {
									showInfo_open0(  0,  0,  _T(  "Failed: resp from dvt: shm not open"  )  );
									goto  errLabel;
								}
								//
								pDvtCli->status.bShmOpen_dvt  =  true;
								showInfo_open0(  0,  0,  _T(  "resp from dvt: shm open"  )  );
							}


					  }
				  }
			  }

			  //  2015/02/04
			  if  (  pDvtCli->dataShm.pBuf   )  {
				  QY_shm  *  pShm  =  &pDvtCli->dataShm;

				  VT_shm_content  *  pShmContent;
				  pShmContent  =  (  VT_shm_content  *  )pShm->pBuf;
				  //
				  //  2016/04/13
				  if  (  pShmContent->u.dvt.i.ucbShowDec_pipeStatus  !=  pQmcCfg->debugStatusInfo.ucbShowDec_pipeStatus  )  {
					  pShmContent->u.dvt.i.ucbShowDec_pipeStatus  =  pQmcCfg->debugStatusInfo.ucbShowDec_pipeStatus;
				  }
				  //
				  if  (  pShmContent->u.dvt.i.ucbShowPreDecVStatus  !=  pQmcCfg->debugStatusInfo.ucbShowPreDecVStatus  )  {
					  pShmContent->u.dvt.i.ucbShowPreDecVStatus  =  pQmcCfg->debugStatusInfo.ucbShowPreDecVStatus;
				  }
				  if  (  pShmContent->u.dvt.i.ucbShowPostDecVStatus  !=  pQmcCfg->debugStatusInfo.ucbShowPostDecVStatus  )  {
					  pShmContent->u.dvt.i.ucbShowPostDecVStatus  =  pQmcCfg->debugStatusInfo.ucbShowPostDecVStatus;
				  }
				  //  2015/10/07
				  if  (  pShmContent->u.dvt.i.ucbShowDec_sharedTexStatus  !=  pQmcCfg->debugStatusInfo.ucbShowDec_sharedTexStatus  )  {
					  pShmContent->u.dvt.i.ucbShowDec_sharedTexStatus  =  pQmcCfg->debugStatusInfo.ucbShowDec_sharedTexStatus;
				  }

			  }

			  //
			   continue;
		  }

		  continue;
	 }


	iErr  =  0;

errLabel:

	//
	showInfo_open0(  0,  0,  _T(  "doDecodeVideo_tool: start to quit"  )  );
	
	//
	pDvtCli->bQuit  =  TRUE;
	//
	askVtToQuit(  pProcInfo,  pDvtCli->tn_cliPipe,  &pDvtCli->vtProcess  );
	//  2015/02/02
	closeVt(  pProcInfo,  pDvtCli->tn_cliPipe,  &pDvtCli->vtProcess  );

	//
	showInfo_open0(  0,  0,  _T(  "doDecodeVideo_tool: after closing dvt"  )  );

	//  2015/06/22
	SetEvent(  pDvtCli->readShm.hEvent_syncR  );
	
	// 先waitFor thread
	waitForObject(  &pDvtCli->readShm.hThread,  20000  );
	if  (  pDvtCli->readShm.hThread  )  {
		TCHAR  tBuf[128];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "waiting for readShm.hThread failed"  )  );
		qyExitProcess(  tBuf  );
	}
	//
	if  (  pDvtCli->readShm.hEvent_syncR  )  {
		CloseHandle(  pDvtCli->readShm.hEvent_syncR  );  pDvtCli->readShm.hEvent_syncR  =  NULL;
	}
	//  2015/02/19
	if  (  pDvtCli->readShm.hEvent_syncW  )  {
		CloseHandle(  pDvtCli->readShm.hEvent_syncW  );  pDvtCli->readShm.hEvent_syncW  =  NULL;
	}

	//
	showInfo_open0(  0,  0,  _T(  "doDecodeVideo_tool: readShm waited"  )  );

	//  close(shm)
	QY_shm  *  pShm  =  &pDvtCli->dataShm;
	if  (  pShm->pBuf  )  {
		UnmapViewOfFile(  pShm->pBuf  );  
		pShm->pBuf  =  NULL;	 
	}
	if  (  pShm->hMap  )  {
		 CloseHandle(  pShm->hMap  );  pShm->hMap  =  NULL;	 
	}
	  
	//
	showInfo_open0(  0,  0,  _T(  "doDecodeVideo_tool: shm closed. before rtspCliCommon_exit"  )  );
	
	//
	BOOL  tmpbRet_cancelIo  =  FALSE;
	//
	if  (  pDvtCli->pRtspCli  )  {
		pRtspCli  =  (  RTSP_cli_common  *  )pDvtCli->pRtspCli;

		rtspCliCommon_exit(  pRtspCli  ); 
		
		//  2015/02/08
		if  (  pRtspCli->status.bException_pRTSP_msg  )  {
			showInfo_open0(  0,  0,  _T(  "exception: free pRTSP_msg"  )  );
			showNotification_open(  0,  0,  0,  _T(  "exception: free pRTSP_msg"  )  );
		}
		tmpbRet_cancelIo  =  pRtspCli->status.bRet_CancelIo;

		//
		MACRO_safeFree(  pDvtCli->pRtspCli  );
	}

	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doDecodeVideo_tool: after rtspCliCommon_exit, bRet_cancelIo %d"  ),  tmpbRet_cancelIo   );
	showInfo_open0(  0,  0,  tBuf  );

	#endif

	
	//  2015/01/17	
	if  (  pTransform->video.debugStep.dec.sts_SyncOperation324  ==  -17  )  {	
		showNotification_open(  0,  0,  0,  _T(  "Note: SyncOperation returns DEVICE_FAILED"  )  );		 
	}
			
	//	
	exitTaskAvFrom_video(  pProcInfo,  pTransform  );  


	//
#if  0  //  2015/02/09. 流最好不好随便中断，所以下面清空的思路不好
	//  2015/02/08. 如果，队列中堆满了数据，启动dvt时，需要时间。那么后续的包因为队列满，就会被扔掉。又造成pts不连续以致放弃解码。所以需要清空，以便用新的连续包来填充
	if  (  isQ2Warning(  &pTransform->video.q2,  10  )  )  {
		showInfo_open0(  0,  0,  _T(  "doDecodeVideo_tool: too many pkts in transQ, empty it"  )  );
		emptyQ2(  &pTransform->video.q2  );
	}
#endif


#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "doDecodeVideo_tool leaves"  )  );
#endif

	return  iErr;
}


#if 0
 extern  "C"  DWORD WINAPI mcThreadProc_readShm_dvtCli( LPVOID lpParameter )
{
	int									iErr							=	-1;
	QY_TRANSFORM					*	pTransform						=	(  QY_TRANSFORM  *  )lpParameter;
	if  (  !pTransform  )  return  -1;
	 MC_VAR_common						*	pProcInfo					=	(  MC_VAR_common  *  )pTransform->pProcInfo;//QY_GET_procInfo_isCli(  );
	 if (  !pProcInfo  )  return  -1;	 

	 //  
	 TRANSFORM_VIDEO_procInfo		*	pTransformVideo				=	&pTransform->video;

	 QY_MC							*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;

	 //
	 DWORD								dwThreadId					=	GetCurrentThreadId(  );

	 int								i;
	 	 	 	
	 DVT_cli						*	pDvtCli						=	&pTransformVideo->dvtCli;
	 RTSP_cli_common				*	pRtspCli					=	(  RTSP_cli_common  *  )pDvtCli->pRtspCli;	
	 
	 QY_shm  *  pShm  =  &pDvtCli->dataShm;
	 VT_shm_content  *  pShmContent  =  (  VT_shm_content  *  )pShm->pBuf;
	 BITMAPINFOHEADER	bih_shm  =  pShmContent->bih_dec;

	 //
	 QDC_OBJ_INFO					*	pQdcObjInfo					=	&pTransformVideo->u.qoi.myQoi.common;
	 QDC_OBJ_transCommon				obj_trans;
	 memset(  &obj_trans,  0,  sizeof(  obj_trans  )  );
	 YUVWriter_var						yuvWriter;
	 memset(  &yuvWriter,  0, sizeof(  yuvWriter  )  );
	 yuvWriter.size_pPkt  =  sizeof(  myDRAW_VIDEO_DATA  );
	 CQyMalloc	mallocObj_pPkt;
	 yuvWriter.pPkt  =  (  myDRAW_VIDEO_DATA  *  )mallocObj_pPkt.mallocf(  yuvWriter.size_pPkt  );
	 if  (  !yuvWriter.pPkt  )  return  -1;
	 memset(  yuvWriter.pPkt,  0,  yuvWriter.size_pPkt  );
	 yuvWriter.pQdcObjInfoParam  =  pQdcObjInfo;

	 //  2015/02/19
	 int  total_nPkts  =  0;
	 TCHAR  tBuf[128]  =  _T(  ""  );

	 //  2015/02/19
	 if  (  !pTransformVideo->pTmpDataQ  )  goto  errLabel;

	 //
	 for  (  ;  !pDvtCli->bQuit;  )  {
	  
		  HANDLE  hs[5];
		  unsigned  short  usCnt  =  0;
		  hs[usCnt]  =  pDvtCli->readShm.hEvent_syncR;  usCnt  ++  ;

		  //
		  DWORD  dwEvt  =  MsgWaitForMultipleObjects(							
							 usCnt,	//  mycountof(  pPlay->hEvents  ),				// Number of events.
							 hs,							// Location of handles.
                             FALSE,										// Wait for all?
                             5000,									// How long to wait?
                             0  );										// Any message is an 
																		// event.
		  if  (  dwEvt  ==  WAIT_FAILED  )  goto  errLabel;
	      //
		  //dwTickCnt  =  GetTickCount(  );

		  if  (  dwEvt  !=  WAIT_TIMEOUT  )  {
			  dwEvt -= WAIT_OBJECT_0;
			  switch  (  dwEvt  )  {
					  case  0:
						     //  dwTickCnt_lastData  =  dwTickCnt;		//  audio data received
						       //  traceLogA(  (char*)  "mcThreadProcInfo_toShareBmp: event 0."  );
							 #ifdef  __DEBUG__
									 //showInfo_open0(  0,  0,  _T(  "readShm: event0"  )  );
							 #endif
							 break;
					  case  1:
						     traceLogA(  (char*)  "mcThreadProcInfo_toShareBmp: event 1."  );
							 break;
					  default:
						     traceLogA(  (char*)  "unknown event"  );	
		  					 goto  errLabel;
							 break;
			  }
			  //
			  #ifdef  __DEBUG__
					  if  (  pShmContent->u.dvt.i.ucbShowPostDecVStatus  )  {
						  //showInfo_open0(  0,  0,  _T(  "readShm here"  )  );
					  }
			  #endif
		  }


		  //
		  for  (  ;  !pDvtCli->bQuit;  )  {


			      //
				  int  ucCnt_shmPktBufs  =  pShmContent->ucCnt_shmPktBufs;
				  if  (  !ucCnt_shmPktBufs  ||  ucCnt_shmPktBufs  >  mycountof(  pShmContent->mems  )  )  goto  errLabel;
				  //
				  if  (  pShmContent->status.readShm.uiCnt_readShm  >=  pShmContent->status.writeShm.uiCnt_writeShm  )  {
					  //
					  if  (  pShmContent->u.dvt.i.ucbShowPostDecVStatus  )  {
						  for  (  i  =  0;  i  <  ucCnt_shmPktBufs;  i  ++  )  {
							   if  (  pShmContent->mems[i].bDataReady  )  {
								   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Err: uiCnt_read %d >= uiCnt_write %d. and mems[%d].bDataReady is ture"  ),  pShmContent->status.readShm.uiCnt_readShm,  pShmContent->status.writeShm.uiCnt_writeShm,  i  );
								   showInfo_open0(  0,  0,  tBuf  );
								   break;
							   }
						  }
					  }
					  //
					  break;
				  }
				  //
				  int  index_toRead  =  pShmContent->status.readShm.uiCnt_readShm  %  ucCnt_shmPktBufs;
				  if  (  !pShmContent->mems[index_toRead].bDataReady  )  {
					     _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "readShm failed: shm.mems[%d].bDataReady is false. uiCnt_read %d, uiCnt_write %d"  ),  index_toRead,  pShmContent->status.readShm.uiCnt_readShm,  pShmContent->status.writeShm.uiCnt_writeShm   );
						  showInfo_open0(  0,  0,  tBuf  );					  
						  }
				  else  {
					    //
					    BYTE  *  pImg  =  NULL;
						PF_img_to_yuv  pf_img_to_yuv  =  shm_img_to_yuv;

						//  2015/10/04
						if  (  pQdcObjInfo->var.usPktResType_dec  !=  pShmContent->mems[index_toRead].usPktResType  )  {
							if  (  !pQdcObjInfo->var.usPktResType_dec  )  {
								pQdcObjInfo->var.usPktResType_dec  =  pShmContent->mems[index_toRead].usPktResType;
								//
								showInfo_open0(  0,  0,  _T(  "readShm: qdcObjInfo.usPktResType_dec set to shmMem."  )  );
								}
							else  {
								  showInfo_open0(  0,  0,  _T(  "readShm: failed, qdcObjInfo.usPktResType_dec != shmMem."  )  );
							}
						}

						//
						if  (  pShmContent->mems[index_toRead].usPktResType  ==  CONST_pktResType_sharedTex  )  {
							yuvWriter.outputInfo.usPktResType  =  pShmContent->mems[index_toRead].usPktResType;
							//yuvWriter.outputInfo.pktSharedTexInfo  =  pShmContent->mems[index_toRead].pktSharedTexInfo;
							yuvWriter.outputInfo.pkts_sharedTexInfo.mems[0]  =  pShmContent->mems[index_toRead].pktSharedTexInfo;
							yuvWriter.outputInfo.pkts_sharedTexInfo.ucCnt  =  1;
							//
							}
						else  {  
							  //
							  pImg  =  (  BYTE  *  )pShmContent->buf  +  index_toRead  *  bih_shm.biSizeImage;
						}

						//
						#if  0
							TCHAR  fn[128];
							static  int  ii  =  0;  ii  ++  ;
							_sntprintf(  fn,  mycountof(  fn  ),  _T(  "c:\\tttbbb\\dd\\kkk%d.bmp"  ),  ii  );
							//
							mySaveYv12(  fn,  pShmContent->bih_dec.biWidth,  pShmContent->bih_dec.biHeight,  pImg,  FALSE  );
						#endif
							
						//
						total_nPkts  ++  ;
						//
							
						//	
						#ifdef  __DEBUG__
								#if  0
							//if  (  pShmContent->cfg.ucbShowPostDecVStatus  )  
							{								
								//_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "readShm: shmPkts[%d], uiCnt_toWrite %d, uiCnt_toRead %d. | nQNodes %d, total_nPkts %d, maxQNodes %d"  ),  index_toRead,  pShmContent->status_writeShm.uiCnt_writeShm,  pShmContent->status_readShm.uiCnt_readShm,  nQNodes,  total_nPkts,  maxQNodes  );
								if  (  pShmContent->mems[index_toRead].usPktResType  ==  CONST_pktResType_sharedTex  )  {
									_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "dvtCli: readShm: shmPkts[%d], sn %d"  ),  index_toRead,  pShmContent->mems[index_toRead].pktSharedTexInfo.uiSeqNo  );
									showInfo_open0(  0,  0,  tBuf  );				  								
								}
							}
								#endif
						#endif
													
						//						
						smplYUVWriter_WriteNextFrame_all(  pQdcObjInfo,  &obj_trans,  bih_shm.biCompression,  &yuvWriter,  pImg,  bih_shm.biWidth,  bih_shm.biHeight,  0,  pf_img_to_yuv,  0,  _T(  "readShm"  )  );  		  
						//  2016/03/29
						pDvtCli->status.dwLastTickCnt_decDataGot  =  GetTickCount(  );

												
						//  2014/02/10
						pShmContent->mems[index_toRead].bDataReady  =  FALSE;
				  }

				  //  2015/10/06
				  {
					TEX2_props  props;
					if  (  !dyn_getTex2Props(  0,  pTransform->iIndex_player,  &props  )
						&&  props.bAvail  )  
					{
						if  (  pShmContent->status.uiSeqNo_lastRender  !=  props.uiSeqNo_lastRender  )  {
							pShmContent->status.uiSeqNo_lastRender  =  props.uiSeqNo_lastRender;
						}
						//  2016/04/14
						if  (  pShmContent->status.uiXql_player  !=  props.uiXql_player  )  {
							pShmContent->status.uiXql_player  =  props.uiXql_player;
						}
					}
				  }

				  //
				  pShmContent->status.readShm.uiCnt_readShm  ++  ;
				  SetEvent(  pDvtCli->readShm.hEvent_syncW  );	//  2015/02/19
	
				  continue;
		  }


		  continue;
	 }
	 
	 iErr =  0;
errLabel:


	 clean_myDRAW_VIDEO_DATA(  (  myDRAW_VIDEO_DATA  *  )yuvWriter.pPkt,  _T(  "readShm. cleanPkt"  )  );

	 return  iErr;

 }
#endif


