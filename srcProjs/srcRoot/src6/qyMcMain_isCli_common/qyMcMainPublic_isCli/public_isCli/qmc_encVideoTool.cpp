
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
#include	"qmcVideoTool.h"
#include	"qisNameDefs.h"
#include	"vtShmFunc.h"

//
int  get_bih_dec(  int  iW,  int  iH,  int  iFourcc_enc,  BITMAPINFOHEADER  *  pBih_dec  )
{
	if  (  !iW  ||  !iH  )  return  -1;

	switch  (  iFourcc_enc  )  {
			case  CONST_fourcc_h264:
			case  CONST_fourcc_HEVC:	//  2017/10/08
				  makeBmpInfoHeader_yv12(  12,  iW,  iH,  pBih_dec  );
				  break;
			case  CONST_fourcc_vp80:
				  makeBmpInfoHeader_i420(  12,  iW,  iH,  pBih_dec  );
				  break;
			default:
				    makeBmpInfoHeader_rgb(  24,  iW,  iH,  pBih_dec  );
					break;
	}
	return  0;
}


#ifdef  __DEBUG__

		//#define  __DEBUG_evt__

#endif

//
//  2015/10/11
//				 EVT_cli										evtCli;

//
 int  qdcInitCompressVideo_evtCli(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_decompress,  QY_VIDEO_HEADER  *  pVh_compress,  unsigned  int  uiModuleType,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{	
	int						iErr	=	-1;
	//
	EVT_cli		*	pObj	=	NULL;	

	//
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
	MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pQyMc->get_pProcInfo(  );
	if  (  !pProcInfo  )  return  -1;

	//  2012/09/01
	//
	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->var.pObj  )  return  -1;

	VIDEO_COMPRESSOR_cfgCommon	*	pCompressor	=	(  VIDEO_COMPRESSOR_cfgCommon  *  )pVideoCompressorCfg_reserved;

	//
	memcpy(  &pQdcObjInfo->cfg.v,  pCompressor,  sizeof(  pQdcObjInfo->cfg.v  )  );

	//
	//  sInputParams        Params  =  {};   // input parameters from command line


	//  memset(  &qdcObjInfo,  0,  sizeof(  qdcObjInfo  )  );
	pObj  =  (  EVT_cli  *  )malloc(  sizeof(  EVT_cli  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	pQdcObjInfo->var.pObj  =  pObj;

	//
	pQdcObjInfo->var.ucbTransformFuncsOk  =  TRUE;	

	
	//
	EVT_cli							*	pEvtCli						=	pObj;
	//
	TCHAR  tBuf[128]  =  _T(  ""  );


	//
	pEvtCli->bQuit  =  FALSE;
	memset(  &pEvtCli->status,  0,  sizeof(  pEvtCli->status  )  );
		
	//
	int  iIndex_capProcInfo  =  0;
	pEvtCli->tn_cliPipe  =  getuiNextTranNo(  0,  0,  0  );
	//
	if  (  pQyMc->appParams.ucbDbgEvt  )  {
		#if  1  //def  __DEBUG_evt__
				pEvtCli->tn_cliPipe  =  2;
				//
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "__DEBUG_evt__: tn_cliPipe is set to %d"  ),  pEvtCli->tn_cliPipe  );
				showInfo_open0(  0,  0,  tBuf  );
		#endif
	}

	// create pipe
	//
	unsigned  int  uiRtspType  =  CONST_rtspType_encV;  


	//
	if  (  !pVh_decompress->bih.biWidth  ||  !pVh_decompress->bih.biHeight  )  goto  errLabel;

	//
	int  iFourcc_enc  =  fourccStr2i(  pCompressor->fourccStr  );

	//
	BITMAPINFOHEADER  bih_dec;
	if  (  get_bih_dec(  pVh_decompress->bih.biWidth,  pVh_decompress->bih.biHeight,  iFourcc_enc,  &bih_dec  )  )  goto  errLabel;

	//
	int  iIndex_sharedObj  =  -1;

	//
	PARAM_initVideoCapDev_rtsp  param;
	memset(  &param,  0,  sizeof(  param  )  );
	param.pQdcObjInfo  =  pQdcObjInfo;
	//
	if  (  initVideoCapDev_rtsp(  pProcInfo,  uiRtspType,  _T(  "enc.264"  ),  pEvtCli->tn_cliPipe,  &bih_dec,  FALSE,  pProcInfo->get_hMainWnd(  ),  iIndex_sharedObj,  &param,  &pEvtCli->pVideoCapDev  )  )  goto  errLabel;	
	

	//
	QY_shm  *  pShm  =  &pEvtCli->dataShm;	
	//
	if  (  pShm->hMap   )  {
		goto  errLabel;						  
	}
							
							//
							unsigned  char  ucCnt_shmPktBufs  =  MAX_shmPktBufs_evt;

							//
							pShm->uiBufSize_pBuf  =  offsetof(  VT_shm_content,  buf  )  +  bih_dec.biSizeImage  *  ucCnt_shmPktBufs;
							if  (  !pShm->uiBufSize_pBuf  )  goto  errLabel;
							//
							_sntprintf(  pShm->shmName,  mycountof(  pShm->shmName  ),  _T(  "Local\\%s%s%d"  ),  CQyString(  pQyMc->appParams.appObjPrefix  ),  CONST_shmName_qm_evt,  pEvtCli->tn_cliPipe  );						// name of mapping object 
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
							pShmContent->uiType  =  CONST_shmType_evt;
							//
							pShmContent->bih_dec  =  bih_dec;
							//  2015/02/19
							pShmContent->ucCnt_shmPktBufs  =  ucCnt_shmPktBufs;
							//
							memcpy(  &pShmContent->u.evt.i.compressorCfgCommon,  pCompressor,  sizeof(  pShmContent->u.evt.i.compressorCfgCommon  )  );

							//
							if  (  pEvtCli->writeShm.hEvent_syncR  )  goto  errLabel;							
							_sntprintf(  pEvtCli->writeShm.evtName_syncR,  mycountof(  pEvtCli->writeShm.evtName_syncR  ),  _T(  "%s%s%d"  ),  pQyMc->appParams.appObjPrefix,  CONST_evtNamePrefix_rtspCliSyncR,  pEvtCli->tn_cliPipe  );
							pEvtCli->writeShm.hEvent_syncR  =  CreateEvent(  NULL,  FALSE,  FALSE,  pEvtCli->writeShm.evtName_syncR  );
							if  (  !pEvtCli->writeShm.hEvent_syncR  )  goto  errLabel;

							//  2015/02/19
							if  (  pEvtCli->writeShm.hEvent_syncW  )  goto  errLabel;							
							_sntprintf(  pEvtCli->writeShm.evtName_syncW,  mycountof(  pEvtCli->writeShm.evtName_syncW  ),  _T(  "%s%s%d"  ),  pQyMc->appParams.appObjPrefix,  CONST_evtNamePrefix_rtspCliSyncW,  pEvtCli->tn_cliPipe  );
							pEvtCli->writeShm.hEvent_syncW  =  CreateEvent(  NULL,  FALSE,  FALSE,  pEvtCli->writeShm.evtName_syncW  );
							if  (  !pEvtCli->writeShm.hEvent_syncW  )  goto  errLabel;
							

			
	//							
	//
	memcpy(  pVh_compress,  pVh_decompress,  sizeof(  pVh_compress[0]  )  );
	pVh_compress->bih.biCompression  =  fourccStr2i(  pCompressor->fourccStr  );	//  CONST_fourcc_h264;
					  
	//  2015/10/16
	if  (  !pQyMc->appParams.ucbDbgEvt  )  {
		#if  1  //  ndef  __DEBUG_evt__
		//	
		unsigned  short  usPktResType  =  0;	//  pProcInfo->get_pktResType_suggested(  CONST_pktUsage_enc,  uiModuleType  );	
		usPktResType  =  pCompressor->usPktResType_suggested;	//  2016/04/28
		//
		//_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d.from%d"  ),  pTransform->iTaskId,  index_pMems_from  );
		if  (  createVt(  pProcInfo,  CONST_vtType_encV,  pEvtCli->tn_cliPipe,  usPktResType,  &pEvtCli->vtProcess,  tBuf  )  )  {		
			goto  errLabel;	
		}
		#endif
	}


	iErr  =  0;
errLabel:

	return  iErr;
}

//
 int  qdcExitCompressVideo_evtCli(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int  iErr  =  -1;

	MC_VAR_isCli  *  pProcInfo   =  QY_GET_procInfo_isCli(  );
	//
	if  (  pQdcObjInfo->var.pObj  )  {
		EVT_cli							*	pEvtCli						=	(  EVT_cli  *  )pQdcObjInfo->var.pObj;
			
		//
		pEvtCli->bQuit  =  TRUE;
		//
		#if  10
			askVtToQuit(  pProcInfo,  pEvtCli->tn_cliPipe,  &pEvtCli->vtProcess  );
			//  2015/02/02
			closeVt(  pProcInfo,  pEvtCli->tn_cliPipe,  &pEvtCli->vtProcess  );
		#endif

		//
		showInfo_open0(  0,  0,  _T(  "doEmcodeVideo_tool_exit: after closing evt"  )  );

		//  2015/06/22
		SetEvent(  pEvtCli->writeShm.hEvent_syncR  );
	
		// ÏÈwaitFor thread
		#if  0
			waitForObject(  &pDvtCli->readShm.hThread,  20000  );
			if  (  pDvtCli->readShm.hThread  )  {
				TCHAR  tBuf[128];
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "waiting for readShm.hThread failed"  )  );
				qyExitProcess(  tBuf  );
			}
		#endif
		//
		if  (  pEvtCli->writeShm.hEvent_syncR  )  {
			CloseHandle(  pEvtCli->writeShm.hEvent_syncR  );  pEvtCli->writeShm.hEvent_syncR  =  NULL;
		}
		//  2015/02/19
		if  (  pEvtCli->writeShm.hEvent_syncW  )  {
			CloseHandle(  pEvtCli->writeShm.hEvent_syncW  );  pEvtCli->writeShm.hEvent_syncW  =  NULL;
		}

		//
		showInfo_open0(  0,  0,  _T(  "doEncodeVideo_tool_exit: readShm waited"  )  );

		//  close(shm)
		QY_shm  *  pShm  =  &pEvtCli->dataShm;
		if  (  pShm->pBuf  )  {
			UnmapViewOfFile(  pShm->pBuf  );  
			pShm->pBuf  =  NULL;	 
		}
		if  (  pShm->hMap  )  {
			 CloseHandle(  pShm->hMap  );  pShm->hMap  =  NULL;	 
		}
	  
		//
		showInfo_open0(  0,  0,  _T(  "doEncodeVideo_tool_exit: shm closed. before rtspCliCommon_exit"  )  );

		//
		exitVideoCapDev_rtsp(  pProcInfo,  &pEvtCli->pVideoCapDev  );

		//
		free(  pEvtCli  );
	}
	pQdcObjInfo->var.pObj  =  NULL;


	//
	showInfo_open0(  0,  0,  _T(  "enc_tool::qdcExitCompressVideo leaves"  )  );


	return  0;
}


//  2015/10/16
int  qdcGetSpsPps_evtCli(  QDC_OBJ_INFO  *  pQdcObjInfo,  char  *  spsBuf,  unsigned  int  *  puiSpsSize,  char  *  ppsBuf,  unsigned  int  *  puiPpsSize,  char  *  vpsBuf,  unsigned  int  *  puiVpsSize  )
{
	int  iErr  =  -1;
	
	//  2016/05/07
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
	//
	EVT_cli  *  pEvtCli  =  (  EVT_cli  *  )pQdcObjInfo->var.pObj;
	
	QY_shm  *  pShm  =  &pEvtCli->dataShm;	
	
	VT_shm_content  *  pShmContent;	
	pShmContent  =  (  VT_shm_content  *  )pShm->pBuf;

	//
	showInfo_open0(  0,  0,  _T(  "qdcGetSpsPps_evtCli: try to get spsPps"  )  );

	//
	if  (  pShmContent->uiType  !=  CONST_shmType_evt  )  goto  errLabel;
	
	//
	int  i;
	int  maxTimes  =  10;
	DWORD  dwRet;
	//
#ifdef  __DEBUG__
		//maxTimes  =  1000;
		maxTimes  =  100;
#endif
	if  (  pQyMc->appParams.ucbDbgEvt  )  {
		showInfo_open0(  0,  0,  _T(  "qdcGetSpsPps_evtCli: set maxTimes to 10000 for dbgEvt"  )  );
		maxTimes  =  10000;
	}
	//
	for  (  i  =  0;  i  <  maxTimes;  i  ++  )  {
		 dwRet  =  WaitForSingleObject(  pEvtCli->writeShm.hEvent_syncW,  200  );
		 if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
		 //
		 if  (  dwRet  !=  WAIT_TIMEOUT  )  {
			 traceLog((TCHAR*)  _T(  "qdcGetSpsPps_evtCli, waited"  )  );
		 }		 
		 //
		 if  (  !pShmContent->u.evt.o.bDone_vh_stream  )  {
			 showInfo_open0(  0,  0,  _T(  "qdcGetSpsPps_evtCli: vh_stream not got, wait"  )  );
			 continue;
		 }
		 //
		 VH_stream  vh_stream;
		 {
			 CQySyncObj	syncObj;
			 if  (  syncObj.sync(  CONST_mtxName_qm_evt  )  )  goto  errLabel;
			 memcpy(  &vh_stream,  &pShmContent->u.evt.o.vh_stream,  sizeof(  vh_stream  )  );
		 }
		 if  (  vh_stream.usCnt  >  mycountof(  vh_stream.mems  )  )  goto  errLabel;
		 //
		 TCHAR  tBuf[128];
		 char  buf[128];
		 //
		 //  2017/10/08
		 switch  (  vh_stream.dwFourcc  )  {
				 case  CONST_fourcc_h264:  {
					   if  (  vh_stream.usCnt  !=  2  )  {			 
						   showInfo_open0(  0,  0,  _T(  "qdcGetSpsPps_evtCli failed: h264, vh_strea.usCnt != 2"  )  );			 
						   goto  errLabel;		 
					   }					 
					   //
		 			   int  index  =  0;
		 			   if  (  vh_stream.mems[index].usLen  >  *puiSpsSize  )  {
						   goto  errLabel;
					   }
					   memcpy(  spsBuf,  vh_stream.mems[index].spsPps,  vh_stream.mems[index].usLen  );
					   *puiSpsSize  =  vh_stream.mems[index].usLen;
					   //
					   index  =  1;
					   if  (  vh_stream.mems[index].usLen  >  *puiPpsSize  )  {
						   goto  errLabel;
					   }
					   memcpy(  ppsBuf,  vh_stream.mems[index].spsPps,  vh_stream.mems[index].usLen  );
					   *puiPpsSize  =  vh_stream.mems[index].usLen;
					   //					   
					   //
					   if  (  puiVpsSize  )  *puiVpsSize  =  0;
					   //
					   }
					   break;
				 case  CONST_fourcc_HEVC:  {
					   if  (  vh_stream.usCnt  !=  3  )  {			 
						   showInfo_open0(  0,  0,  _T(  "qdcGetSpsPps_evtCli failed: h265, vh_strea.usCnt != 3"  )  );			 
						   goto  errLabel;		 
					   }					 
					   //
		 			   int  index  =  0;
					   if  (  vh_stream.mems[index].usLen  >  *puiVpsSize  )  {
						   goto  errLabel;
					   }
					   memcpy(  vpsBuf,  vh_stream.mems[index].spsPps,  vh_stream.mems[index].usLen  );
					   *puiVpsSize  =  vh_stream.mems[index].usLen;
					   //
					   index  ++  ;
		 			   if  (  vh_stream.mems[index].usLen  >  *puiSpsSize  )  {
						   goto  errLabel;
					   }
					   memcpy(  spsBuf,  vh_stream.mems[index].spsPps,  vh_stream.mems[index].usLen  );
					   *puiSpsSize  =  vh_stream.mems[index].usLen;
					   //
					   index  ++  ;
					   if  (  vh_stream.mems[index].usLen  >  *puiPpsSize  )  {
						   goto  errLabel;
					   }
					   memcpy(  ppsBuf,  vh_stream.mems[index].spsPps,  vh_stream.mems[index].usLen  );
					   *puiPpsSize  =  vh_stream.mems[index].usLen;
					   //					   
					   }
					   break;
				 default:
					    //
					    iFourcc2Str(  vh_stream.dwFourcc,  buf,  mycountof(  buf  )  );		 
						_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qdcGetSpsPps_evtCli failed: unsupported fourcc %d %S"  ),  vh_stream.dwFourcc,  buf  );					     
						showInfo_open0(  0,  0,  tBuf  );
					    goto  errLabel;
					    break;
		 }
		 //
		 break;
	}
	if  (  i  ==  maxTimes  )  {
		showInfo_open0(  0,  0,  _T(  "qdcGetSpsPps_evtCli failed: spsPps has not been got"  )  );
		goto  errLabel;
	}


	//
	showInfo_open0(  0,  0,  _T(  "qdcGetSpsPps_evtCli: spsPps got"  )  );
	
	iErr  =  0;
errLabel:
	return  iErr;
}

//
typedef  struct  {
				QDC_OBJ_INFO  *  pQdcObjInfo;
				EVT_cli  *  pEvtCli;
}		 PARAM_CMySmplYUVReader_myLoadNextFrame_evtCli;

//
int  CMySmplYUVReader_myLoadNextFrame_evtCli(  unsigned  short  usPktResType,  void  *  p0_pInput,  void  *  p1_uiInputSize,  void  *  p2_myLoadNextFrame  )		
{
	
	char  *  pInput  =  (  char  *  )p0_pInput;
	unsigned  int  uiInputSize  =  (  unsigned  int  )p1_uiInputSize;
	PARAM_CMySmplYUVReader_myLoadNextFrame_evtCli  *  pParam  =  (  PARAM_CMySmplYUVReader_myLoadNextFrame_evtCli  *  )p2_myLoadNextFrame;

	//
	int  iErr  =  -1;
	BOOL  bSkipped_err  =  FALSE;

	if  (  !pParam  )  return  -1;
	QDC_OBJ_INFO  *  pQdcObjInfo  =  pParam->pQdcObjInfo;
	if  (  !pQdcObjInfo  )  return  -1;
	EVT_cli  *  pEvtCli  =  pParam->pEvtCli;
	if  (  !pEvtCli  )  return  -1;
	//
	 QY_shm  *  pShm  =  &pEvtCli->dataShm;
	 if  (  !pShm->pBuf  )  return  -1;
	 VT_shm_content  *  pShmContent  =  (  VT_shm_content  *  )pShm->pBuf;
	 BITMAPINFOHEADER	bih_shm  =  pShmContent->bih_dec;
	 
	 //
	 TCHAR  tBuf[128];
	 
	 //
	 myDRAW_VIDEO_DATA  *  pCurPkt  =  (  myDRAW_VIDEO_DATA  *  )pQdcObjInfo->cfg.v.pCurPkt;
	 if  (  !pCurPkt  )  return  -1;

	 //
#ifdef  __DEBUG__
		#if  0
			 traceLog((TCHAR*)  _T(  "YUV: inputSize %d"  ),  uiInputSize  );
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "yuvReader: inputSize %d. %d. "  ),  uiInputSize,  pCurPkt->head.uiSampleTimeInMs  );
			 showInfo_open0(  0,  0,  tBuf  );
		#endif
		//

#endif

	 //			 
	 if  (  pCurPkt->usPktResType  !=  CONST_pktResType_sharedTex  )  {
		 if  (  bih_shm.biSizeImage  !=  uiInputSize  )  {
			 //
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "CMySmplYUVReader_myLoadNextFrame_evtCli failed, bih_shm: %dX%d, sizeImg %d != uiInputSize %d"  ),  bih_shm.biWidth,  bih_shm.biHeight,  bih_shm.biSizeImage,  uiInputSize  );
			 showInfo_open0(  0,  0,  tBuf  );
			 //
			 return  -1;
		 }	
	 }
	 			
	 //	
	 int  ucCnt_shmPkts  =  pShmContent->ucCnt_shmPktBufs;		
	 if  (  !ucCnt_shmPkts  ||  ucCnt_shmPkts  >  mycountof(  pShmContent->mems  )  )  goto  errLabel;				  
	 //
	 int  index_toWrite  =  pShmContent->status.writeShm.uiCnt_writeShm  %  ucCnt_shmPkts;		
	 VT_shm_pktInfo  *  pShmPkt  =  &pShmContent->mems[index_toWrite];
	 if  (  pShmPkt->bDataReady  )  {
		 BOOL  bDbg   =  FALSE;
		 //
		 #ifdef  __DEBUG__
				 bDbg  =  TRUE;
		 #endif
		 //
		 if  (  pShmContent->u.evt.i.ucbShowEncVStatus  ||  bDbg  )  {						
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "writeShm failed: shm.mems[%d].bDataReady is true. cnt_writeShm %d, cnt_readShm %d. try to wait"  ),  index_toWrite,  pShmContent->status.writeShm.uiCnt_writeShm,  pShmContent->status.readShm.uiCnt_readShm   );			
			 showInfo_open0(  0,  0,  tBuf  );			  
			 //
			 #ifdef  __DEBUG__
					 if  (  bDbg  )  {				 
						 traceLog((TCHAR*)  tBuf  );			 
					 }
			 #endif
		 }

		 SetEvent(  pEvtCli->writeShm.hEvent_syncR  );
		 bSkipped_err  =  TRUE;
		 goto  errLabel;
	 }



	 //
	 writeShmPkt(  pCurPkt,  pShmContent,  &bih_shm,  ucCnt_shmPkts,  index_toWrite  );

	 //
	 pShmContent->status.writeShm.uiCnt_writeShm  ++  ;					   		
	 SetEvent(  pEvtCli->writeShm.hEvent_syncR  );

	 iErr  =  0;


errLabel:
	 if  (  bSkipped_err  )  {
		 return  0;
	 }
	return  iErr;
}


//
int  restartVt(  void  *  pMC_VAR_common,  int  vtType,  int  tn_cliPipe,  unsigned  short  usPktResType,  VT_process  *  pVtProcess  )
{
	int  iErr  =  -1;

	//
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pMC_VAR_common;
	

	//
	showInfo_open0(  0,  0,  _T(  "restartVt"  )  );

	askVtToQuit(  pProcInfo,  tn_cliPipe,  pVtProcess  );
	//  2015/02/02
	closeVt(  pProcInfo,  tn_cliPipe,  pVtProcess  );
		
	//
#if  0
	unsigned  short  usPktResType  =  0;
	switch  (  vtType  )  {
			case  CONST_vtType_decV:
				  usPktResType  =  pProcInfo->get_pktResType_suggested(  CONST_pktUsage_dec  );
				  break;
			case  CONST_vtType_encV:
				  usPktResType  =  pProcInfo->get_pktResType_suggested(  CONST_pktUsage_enc  );
				  break;
			default:
					goto  errLabel;
	}
#endif

	//	
	TCHAR  tBuf[123]  =  _T(  ""  );

	if  (  createVt(  pProcInfo,  vtType,  tn_cliPipe,  usPktResType,  pVtProcess,  tBuf  )  )  {	
		goto  errLabel;					 
	}

	iErr  =  0;
errLabel:
	return  iErr;

}

//
int  doEncodeVideo_evtCli_run(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_bmpCommon  *  pCapProcInfo,  void  *  pMIS_CNT,  MIS_MSGU  *  pMsgBuf  )
{
	int  iErr  =  -1;

#if 0

	//
	QDC_OBJ_INFO  *  pQdcObjInfo  =  &pCapProcInfo->compressVideo.u.qoi.myQoi.common;
	EVT_cli							*	pEvtCli						=	(  EVT_cli  *  )pQdcObjInfo->var.pObj;
	if  (  !pEvtCli  )  return  -1;

	QY_shm  *  pShm  =  &pEvtCli->dataShm;
	if  (  !pShm->pBuf  )  return  -1;
	VT_shm_content  *  pShmContent  =  (  VT_shm_content  *  )pShm->pBuf;

	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg();
	if  (  !pQmcCfg  )  return  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;


	//
	long  old_lPktId  =  0;
		
	for  (  ;  !bCapBmpQuit(  pCapProcInfo,  0,  0  );  )  {
		 if  (  pEvtCli->bQuit  )  goto  errLabel;
		  
		  //  2010/12/28
		  MACRO_setStep(  pCapProcInfo->thread.debugStep,  CONST_threadStep_toWait  );

		  HANDLE  hs[5];
		  unsigned  short  usCnt  =  0;
		  hs[usCnt]  =  pCapProcInfo->thread.q2.hEvents[0];  usCnt  ++  ;
		  hs[usCnt]  =  pCapProcInfo->thread.q2.hEvents[1];	 usCnt  ++  ;
		  hs[usCnt]  =  pEvtCli->writeShm.hEvent_syncW;		 usCnt  ++  ;

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
						       //  traceLogA(  (char*)(  "mcThreadProcInfo_toShareBmp: event 0."  );
							 break;
					  case  1:
							 #ifdef  __DEBUG__
									 traceLogA(  (char*)  "doEncodeVideo_tool_qmc_run: event 1."  );
							 #endif
							 break;
					  case  2:
							 #ifdef  __DEBUG__
									 //traceLogA(  (char*)(  "doEncodeVideo_tool_qmc_run: event 2."  );
							 #endif
						     break;
					  default:
							 #ifdef  __DEBUG__
									 traceLogA(  (char*)  "unknown event"  );	
							 #endif
		  					 goto  errLabel;
							 break;
			  }
			  //

		  }


		  for  (  ;  !bCapBmpQuit(pCapProcInfo,  0,  0  );  )  {
			   if  (  pEvtCli->bQuit  )  goto  errLabel;
			  
			   //
			   myDRAW_VIDEO_DATA  *  pCurPkt  =  (  myDRAW_VIDEO_DATA  *  )pQdcObjInfo->cfg.v.pCurPkt;
			   if  (  !pCurPkt->memory.m_pBuf  &&  isQEmpty(  (  GENERIC_Q  *  )pQdcObjInfo->cfg.v.pInDataCacheQ  )  &&  isQ2Empty(  (  QY_Q2  *  )pQdcObjInfo->cfg.v.pVideoQ2  )  )  break;

			   //  2015/10/16
			   DWORD  dwTickCnt  =  GetTickCount(  );
			   int  iElapseInMs  =  0;
			   TCHAR  tBuf[128];

			   //
			   if  (  !pEvtCli->status.noEncData.dwStartTickCnt_noEncData  )  pEvtCli->status.noEncData.dwStartTickCnt_noEncData  =  dwTickCnt;
			   //
			   if  (  dwTickCnt  <  pEvtCli->status.dwLastTickCnt_encDataGot  +  2000  )  {
				   pEvtCli->status.noEncData.nTimes_noEncData  =  0;				 					   
				   pEvtCli->status.noEncData.dwStartTickCnt_noEncData  =  dwTickCnt;
				   }			 				   
			   else  {				   
				     pEvtCli->status.noEncData.nTimes_noEncData  ++  ;			
					 //
					 iElapseInMs  =  dwTickCnt  -  pEvtCli->status.noEncData.dwStartTickCnt_noEncData;
					 //
					 if  (  pEvtCli->status.noEncData.nTimes_noEncData  >  20
						 &&  iElapseInMs  >  4000  )  
					 {						 
						 //
						 if  (  !pQyMc->appParams.ucbDbgEvt  )  {
							 #if  1  //  ndef  __DEBUG_evt__
								  //
								  //
								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "restartVt. (encV failed, noEncData too long, nTimes_noEncData %d,  elapse_noEncData %dms)"  ),  pEvtCli->status.noEncData.nTimes_noEncData,  iElapseInMs  );
								  showInfo_open0(  0,  0,  tBuf  );
								  showNotification_open(  0,  0,  0,  tBuf  );

								  //  2016/04/28
								  unsigned  short  usPktResType_i  =  0;	//  pProcInfo->get_pktResType_suggested(  CONST_pktUsage_enc,  uiModuleType  );
								  usPktResType_i  =  pQdcObjInfo->cfg.v.usPktResType_suggested;
								  //
								  restartVt(  pProcInfo,  CONST_vtType_encV,  pEvtCli->tn_cliPipe,  usPktResType_i,  &pEvtCli->vtProcess  );
						 
								  //
								  pEvtCli->status.noEncData.nTimes_noEncData  =  0;
								  pEvtCli->status.noEncData.dwStartTickCnt_noEncData  =  dwTickCnt;
								  

							 #endif
						 }
					 }				   
			   }

			   //
			   #ifdef  __DEBUG__
					   #if  0
								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "restartVt. (encV failed, noEncData too long, nTimes_noEncData %d,  elapse_noEncData %dms)"  ),  pEvtCli->status.noEncData.nTimes_noEncData,  iElapseInMs  );
								  showInfo_open0(  0,  0,  tBuf  );
								  showNotification_open(  0,  0,  0,  tBuf  );
					   #endif
			   #endif

			   //
			   PARAM_CMySmplYUVReader_myLoadNextFrame_evtCli  param;
			   memset(  &param,  0,  sizeof(  param  )  );
			   param.pQdcObjInfo  =  pQdcObjInfo;
			   param.pEvtCli  =  pEvtCli;

			   //param.p  =  this;
			   //param.pSurface  =  pSurface;
			   if  (  pQdcObjInfo->cfg.v.enc.pf_smplYUVReader_LoadNextFrame(  pQdcObjInfo,  &old_lPktId,  CMySmplYUVReader_myLoadNextFrame_evtCli,  &param,  &pQdcObjInfo->var.encInfo.bNeed_forceKeyFrame  )  )  {
				   goto  errLabel;	 
			   }
			   //  2015/10/17
			   if  (  pQdcObjInfo->var.encInfo.bNeed_forceKeyFrame  !=  pShmContent->u.evt.i.bNeed_forceKeyFrame  )  {
				   pShmContent->u.evt.i.bNeed_forceKeyFrame  =  pQdcObjInfo->var.encInfo.bNeed_forceKeyFrame;
			   }
			   //  2015/10/19
			   if  (  pQmcCfg->debugStatusInfo.ucbShowEncVStatus  !=  pShmContent->u.evt.i.ucbShowEncVStatus  )  {
				   pShmContent->u.evt.i.ucbShowEncVStatus  =  pQmcCfg->debugStatusInfo.ucbShowEncVStatus;
			   }

			   //  2015/11/02
			   if  (  pQdcObjInfo->var.sharedTex.uiSeqNo_lastRender  !=  pShmContent->status.uiSeqNo_lastRender  )  {
				   pQdcObjInfo->var.sharedTex.uiSeqNo_lastRender  =  pShmContent->status.uiSeqNo_lastRender;
			   }
		  }
		
		}

#endif

	iErr  =  0;

errLabel:

	return  iErr;
}
