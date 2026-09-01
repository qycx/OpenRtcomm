
#include	"stdafx.h"
#include	"ctxQmcEvt.h"
#include	<stddef.h>

#include	"policyAvParams.h"
#include	"qyMcMainCommon.h"
#include	"qisNameDefs.h"
#include	"qmcVideoCapture.h"
#include	"rtspUsrData.h"
#include	"qisPropIdDefs.h"
//
#include	"dynLib_isD3dFunc.h"

//
CCtxQmcEvt::CCtxQmcEvt(  )
{
	//  2015/02/08
	this->m_iCtxType  =  CONST_ctxType_evt;

	memset(  &m_var,  0,  sizeof(  m_var  )  );
	//
	safeTcsnCpy(  _T(  "evt"  ),  this->who_showInfo,  mycountof(  this->who_showInfo  )  );
}


CCtxQmcEvt::~CCtxQmcEvt(  )
{
}



BOOL  CCtxQmcEvt::bCtxQuit(  )
{
	if  (  CCtxQmcTmpl::bCtxQuit(  )  )  return  TRUE;
	//
	if  (  m_var.evt.bQuit  )  return  TRUE;
	//
	if  (  m_var.evt.status.bStopped_threadReadShm  )  return  TRUE;
	//
	return  FALSE;
}


	RW_lock_param  *  CCtxQmcEvt::get_qyMc_rwLockParam(  )  
	{
		return  &m_var.qyMc_cfg.rwLockParam;
	}
	//

	TCHAR  *  CCtxQmcEvt::get_appObjPrefix(  )
	{
		return  m_var.cmdLine.appObjPrefix;
	}


	void  *  CCtxQmcEvt::get_qmc_cfg(  )
	{
		return  &m_var.cfg;
	}

	QNM_CUSRES_INFO  *  CCtxQmcEvt::get_qyMc_cusRes(  )  
	{
		//  not finished
		return  NULL;
	}

	QMC_status  *  CCtxQmcEvt::get_qmc_status(  )  
	{
		//  
		return  &m_var.status;
	}

	QMC_cfg_debugStatusInfo  *  CCtxQmcEvt::get_qmc_cfg_debugStatusInfo(  )  
	{
		//
		return  NULL;
	}


	QY_sharedObj_sync  *  CCtxQmcEvt::getSharedObjSyncByIndex(  int  index  )  
	{
		return  &m_var.sharedObjSync;
	}
	

	CAP_procInfo_bmpU  *  CCtxQmcEvt::getCapBmpBySth(  int  index,  unsigned  int  uiCapType  )  
	{
		return  (  CAP_procInfo_bmpU  *  )&m_var.capBmp;
	}

	CAP_procInfo_audioU  *  CCtxQmcEvt::getCapAudioBySth(  int  index,  unsigned  int  uiCapType  )  
	{
		return  NULL;
	}

	//	
	int  CCtxQmcEvt::newShmCmdIndex(  int  iIndex_sharedObj  )
	{
		return  -1;
	}

	//	
	void  *  CCtxQmcEvt::getQmShmCmdByIndex(  int  iIndex  )
	{
		return  NULL;
	}


	//
	MIS_CNT  *  CCtxQmcEvt::getMisCntByName(  LPCTSTR  misServName  )  
	{
		if  (  !misServName  )  return  NULL;
		//
		return  &(this->m_var.misCnt);
	}

	//
	MIS_CNT  *  CCtxQmcEvt::getMisCntByIndex(  int  iIndex  )  
	{
		if  (  iIndex  )  return  NULL;
		//
		return  &this->m_var.misCnt;
	}

	//
	HWND  CCtxQmcEvt::get_hMainWnd(  )  
	{
		//
		return  NULL;
	}


	//
	void  *  CCtxQmcEvt::getPolicyAvParams(  )  
	{	
		//
		return  m_var.p_gAvParams;
	}

	void  *  CCtxQmcEvt::getCusModules(  )  
	{
		QY_MC  *  pQyMc  =  (  QY_MC  *  )this->pQyMc;	
		if  (  !pQyMc  )  return  NULL;
		
		return  &pQyMc->cusModules;
	}


	//
	int  CCtxQmcEvt::setQmDbFuncs(  int  iDbType,  QM_dbFuncs  *  pDbFuncs  )	
	{
			return  -1;
	}



	BOOL  CCtxQmcEvt::b_qyMc_quit(  )  
	{
		//
		return  FALSE;
	}



	BOOL  CCtxQmcEvt::bWebcamUsing(  unsigned  int  uiCamCapType,  void  *  pMoniker_v,  LPCTSTR  camName,  int  *  piIndex_capBmp,  int  *  piIndex_sharedObj  )
	{
		return  FALSE;
	}



	BOOL  CCtxQmcEvt::bMediaTaskExists(  int  iTaskId  )
	{
		return  FALSE;
	}

	
	BOOL  CCtxQmcEvt::bAudioChannelReady(  )
	{
		return  TRUE;
	}

	BOOL  CCtxQmcEvt::bVideoChannelReady(  )
	{
		return  TRUE;
	}


	//
int  CCtxQmcEvt::toShareVideo_post(  unsigned  int  uiCapType,  int  iIndex_capProcInfo,  myDRAW_VIDEO_DATA  *  pkts,  unsigned  int  nPkts,  COMPRESS_VIDEO  *  pCompressVideo,  QY_SHARED_OBJ  *  pSharedObj,  MIS_MSGU  *  pMsgBuf  )
{
	int  iErr  =  -1;

	//		
	if  (  nPkts  !=  1  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "toShareVideo_post failed: nPkts must is 1"  )  );
		#endif
		goto  errLabel;
	}
	myDRAW_VIDEO_DATA  *  pPkt  =  &pkts[0];
	
	//  if  (  pPkt->memory.uiBufSize  !=  pPkt->uiSize_dec  +  sizeof(  TRANSFER_VIDEO_DATA  )  )  
	if  (  pPkt->memory.uiBufSize  <  pPkt->uiSize_dec  +  sizeof(  TRANSFER_VIDEO_DATA  )  )  //  2014/09/30
	{
		#ifdef  __DEBUG__
				traceLog(  _T(  "toShareVideo_post: uiBufSize err"  )  );
		#endif
		goto  errLabel;
	}


	TRANSFER_VIDEO_DATA	*	pReq						=	NULL;

	pReq  =  (  TRANSFER_VIDEO_DATA  *  )(  pPkt->memory.m_pBuf  +  pPkt->uiSize_dec  );



	//				  
	if  (  !pReq->usCnt  )  {	
		#if  0
			traceLog(  _T(  "toShareBmp failed: req.usCnt is 0"  )  );
		#endif
		goto  errLabel;
	}

	//
	int						lenInBytes					=	0;

	//
	lenInBytes  =  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  +  pReq->uiLen;

	//
			 int		iMediumType  =  CONST_mediumType_video;
		 int		iCodecType  =  CONST_codecType_h264;


	//
		unsigned  int  uiSampleTimeInMs  =  0;
	unsigned  int  uiPts  =  0;	//  2015/02/09
	unsigned  char  *  pBuffer  =  NULL;
	long  BufferLen  =  0;
	bool  bSpsPps  =  false;
	int  index_spsPps  =  0;
	bool  bFinished_spsPps  =  FALSE;
	CB_rtsp_res		res;
	bool  bNeedResp  =  FALSE;//true;	//  2015/01/30


#ifdef  __DEBUG__
		//showInfo_open0(  0,  0,  _T(  "to send usrData_commInfo"  )  );
#endif
	//  send usrData_commInfo
	iMediumType  =  CONST_mediumType_usrData;
	//
	int  iDataType  =  CONST_rtspUsrDataType_encData;
	//
	pBuffer  =  (  unsigned  char  *  )pReq;
	BufferLen  =  lenInBytes;
	//
	memset(  &res,  0,  sizeof(  res  )  );
	
	//
	RTSP_cli_common  *  pRtspCli  =  m_var.pRtspCli;
	
	//
	if  (  BufferCB_rtspCliCommon(  pRtspCli,  pRtspCli->iIndex_capProcInfo,  iMediumType,  iCodecType,  uiSampleTimeInMs,  uiPts,  iDataType,  pBuffer,  BufferLen,  bSpsPps,  index_spsPps,  bFinished_spsPps,  bNeedResp,  &res  )  )  {					
		goto  errLabel;			  		 
	}	
		


	iErr  =  0;

	errLabel:
		return  iErr;
	}




int  CCtxQmcEvt::drawVideoData(  myDRAW_VIDEO_DATA  *  pkts,  int  pktsLen,  BOOL  *  pbPktsRedirected,  void  *  pQY_TRANSFORM  )
{
	return  -1;
}


int  CCtxQmcEvt::playAudioData(  int  iSampleTimeInMs,  unsigned  int  uiPts,  BYTE  *  pInput,  unsigned  int  inputLen,  int  iIndex_player  )
{
	return  -1;
}


int  CCtxQmcEvt::showNotification(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  LPCTSTR  hint  )
{
	return  -1;
}


	
int  CCtxQmcEvt::qisChkTasks_gui(  )			//  2009/09/10
{
	return  -1;
}


int  CCtxQmcEvt::applyForRemovingInvalidTasks(  unsigned  int  uiChannelType  )
{
	return  -1;
}



int  CCtxQmcEvt::removeInvalidTasks(  unsigned  int  uiChannelType  )			//  2009/09/10
{
	return  -1;
}



//  2015/10/04
#if  0
unsigned  short  CCtxQmcEvt::get_pktResType_suggested(  int  pktUsage,  unsigned  int  uiModuleType  )
{
	return  this->m_var.cmdLine.usPktResType_suggested;
}
#endif


//
int  CCtxQmcEvt::get_deced_pktResType(  unsigned  int  uiModuleType,  int  iFourcc,  unsigned  short  *  pusPktResType_o  )				//  2015/10/04
{
	return  -1;
}

//
int  CCtxQmcEvt::get_pktResType_toEnc(  unsigned  short  usPktResType_src,  unsigned  int  uiModuleType,  int  iFourcc,  unsigned  short  *  pusPktResType_i  )				//  2015/10/04
{
	if  (  pusPktResType_i  )  {
		*pusPktResType_i  =  m_var.cmdLine.usPktResType_suggested;
	}
	return  0;
}


//
//
void  *  CCtxQmcEvt::get_pf_DXUTSaveTextureToFile(  )
{
	DYN_LIB_isD3dFunc  *  pLib_isD3dFunc  =  (  DYN_LIB_isD3dFunc  *  )m_var.pDynLib_isD3dFunc;
	if  (  !pLib_isD3dFunc  )  return  NULL;
			
	//
	return  pLib_isD3dFunc->pf_DXUTSaveTextureToFile;
}



//
//
void  *  evt_qoi_getPtrProperty(  void  *  pQdcObjInfoParam,  int  propertyId  );


//
int  CCtxQmcEvt::set_qoi_funcs(  MY_qoi  *  pMyQoi  )
{
	//
	pMyQoi->common.pf_qoi_getPtrProperty  =  evt_qoi_getPtrProperty;
	//

	return  0;
}


//
BOOL  CCtxQmcEvt::bGetLongProperty(  int  propId,  long  *  pVal  )
{
	BOOL  bRet  =  FALSE;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  FALSE;

	//
	if  (  !pVal  )  return  FALSE;

	//
	switch  (  propId  )  {
			default:
					break;
	}
	
errLabel:

	return  bRet;

}



//
BOOL  CCtxQmcEvt::bGetStrProperty(  int  propId,  TCHAR  *  tBuf,  int  tBufCnt  )
{
	BOOL  bRet  =  FALSE;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  FALSE;

	//
	switch  (  propId  )  {
			case  CONST_qdcPropId_fn_ck:  {
				  //
				  CQyString  cfgStr,  fn_ck;	
				  //
				  cfgStr  =  CQyString(  pQyMc->cfg.installDir  )  +   _T(  CONST_qyCfgSubDir  );
				  fn_ck  =  cfgStr  +  CONST_fileName_fx_ck;
				  //
				  safeTcsnCpy(  fn_ck,  tBuf,  tBufCnt  );
				  //
				  bRet  =  TRUE;  goto  errLabel;
				  }
				  break;
			default:
					break;
	}
	
errLabel:

	return  bRet;
}


//  2016/04/26
int  CCtxQmcEvt::initCompressVideo(  BITMAPINFO  *  pBmpInfo_input,  unsigned  int  uiCapType,  VIDEO_COMPRESSOR_CFG  *  pCompressor,  BOOL  bCapDev,  unsigned  int  uiBufSize_pData,  COMPRESS_VIDEO  *  pCompressVideo  )
{
	return  ::initCompressVideo(  this,  pBmpInfo_input,  uiCapType,  pCompressor,  bCapDev,  uiBufSize_pData,  pCompressVideo  );
}


int  CCtxQmcEvt::exitCompressVideo(  BOOL  bCapDev,  COMPRESS_VIDEO  *  pCompressVideo  )
{
	return  ::exitCompressVideo(  this,  bCapDev,  pCompressVideo  );
}



//
int  CCtxQmcEvt::initRtspCli(  )
{
	int  iErr  =  -1;
	CCtxQmcEvt  *  pProcInfo  =  this;

	//
	int  size  =  sizeof(  RTSP_cli_common  );
	m_var.pRtspCli  = (  RTSP_cli_common  *  )mymalloc(  size  );
	if  (  !m_var.pRtspCli  )  goto  errLabel;
	RTSP_cli_common  *  pRtspCli  =  (  RTSP_cli_common  *  )m_var.pRtspCli;
	memset(  pRtspCli,  0,  sizeof(  pRtspCli[0]  )  );

	//
	int  iIndex_capProcInfo  =  0;


	//
	if  (  rtspCliCommon_init(  BufferCB_rtspCliCommon,  rtspCliCommon_exit,  iIndex_capProcInfo,  pProcInfo->get_appObjPrefix(  ),  m_var.cmdLine.tn_cliPipe,  pRtspCli  )  )  {
		goto  errLabel;
	}
	

	iErr  =  0;
errLabel:
	return  iErr;

}

int  CCtxQmcEvt::exitRtspCli(  )
{
	int  iErr  =  -1;
	
	//
	BOOL  tmpbRet_cancelIo  =  FALSE;
	//
	if  (  m_var.pRtspCli  )  {
		RTSP_cli_common  *  pRtspCli  =  (  RTSP_cli_common  *  )m_var.pRtspCli;

		rtspCliCommon_exit(  pRtspCli  ); 
		
		//  2015/02/08
		if  (  pRtspCli->status.bException_pRTSP_msg  )  {
			showInfo_open0(  0,  0,  _T(  "exception: free pRTSP_msg"  )  );
			showNotification_open(  0,  0,  0,  _T(  "exception: free pRTSP_msg"  )  );
		}
		tmpbRet_cancelIo  =  pRtspCli->status.bRet_CancelIo;

		//
		MACRO_safeFree(  m_var.pRtspCli  );
	}



	iErr  =  0;
errLabel:
	return  iErr;
}

	
/////////////////
int  CCtxQmcEvt::initEvt(  )
{
	int  iErr  =  -1;
	EVT_encV  *  pEvt  =  &m_var.evt;
	CCtxQmcEvt  *  pProcInfo  =  this;
	
	//
	QY_SHARED_OBJ			*	pSharedObj	=	&m_var.sharedObjSync.sharedObj;
	//
	pSharedObj->pEvt  =  &m_var.evt;

	//
	if  (  !pEvt->dataShm.hMap  )  {					
		QY_shm  *  pShm  =  &pEvt->dataShm;
					   

		_sntprintf(  pShm->shmName,  mycountof(  pShm->shmName  ),  _T(  "Local\\%s%s%d"  ),  CQyString(  pProcInfo->get_appObjPrefix(  )  ),  CONST_shmName_qm_evt,  this->m_var.cmdLine.tn_cliPipe  );						// name of mapping object 
						
		pShm->hMap  =  OpenFileMapping(  FILE_MAP_READ  |  FILE_MAP_WRITE,  0,  pShm->shmName  );		
		if  (  !pShm->hMap  )  {
			qyDisplayLastError(  "OpenFileMapping"  );	
			showInfo_open0(  0,  0,  _T(  "evt.OpenFileMapping failed"  )  );
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
		if  (  pEvt->readShm.hEvent_syncR  )  goto  errLabel;													 
		_sntprintf(  pEvt->readShm.evtName_syncR,  mycountof(  pEvt->readShm.evtName_syncR  ),  _T(  "%s%s%d"  ),  pProcInfo->get_appObjPrefix(  ),  CONST_evtNamePrefix_rtspCliSyncR,  pProcInfo->m_var.cmdLine.tn_cliPipe  );
		pEvt->readShm.hEvent_syncR  =  CreateEvent(  NULL,  FALSE,  FALSE,  pEvt->readShm.evtName_syncR  );
		if  (  !pEvt->readShm.hEvent_syncR  )  goto  errLabel;
								  
		//  2015/02/19		
		if  (  pEvt->readShm.hEvent_syncW  )  goto  errLabel;													 
		_sntprintf(  pEvt->readShm.evtName_syncW,  mycountof(  pEvt->readShm.evtName_syncW  ),  _T(  "%s%s%d"  ),  pProcInfo->get_appObjPrefix(  ),  CONST_evtNamePrefix_rtspCliSyncW,  pProcInfo->m_var.cmdLine.tn_cliPipe  );
		pEvt->readShm.hEvent_syncW  =  CreateEvent(  NULL,  FALSE,  FALSE,  pEvt->readShm.evtName_syncW  );
		if  (  !pEvt->readShm.hEvent_syncW  )  goto  errLabel;
		
		//
		 VT_shm_content  *  pShmContent  =  (  VT_shm_content  *  )pShm->pBuf;
		 BITMAPINFOHEADER	bih_shm  =  pShmContent->bih_dec;
		 //
		 if  (  pShmContent->uiType  !=  CONST_shmType_evt  )  goto  errLabel;

		//
		VIDEO_COMPRESSOR_CFG	compressor;
		memset(  &compressor,  0,  sizeof(  compressor  )  );
		{
			CQySyncObj	syncObj;
			if  (  syncObj.sync(  CONST_mtxName_qm_evt  )  )  goto  errLabel;
			memcpy(  &compressor.common,  &pShmContent->u.evt.i.compressorCfgCommon,  sizeof(  compressor.common  )  );
		}

		compressor.common.pVideoQ2  =  &this->m_var.capBmp.thread.q2;
		compressor.common.pParent_transform  =  &this->m_var.capBmp;
		if  (  initCompressVideo(  (  BITMAPINFO  *  )&bih_shm,  CONST_capType_mediaDevice,  &compressor,  FALSE,  0,  &m_var.capBmp.compressVideo  )  )  {
			goto  errLabel;
		}

		//
		{
			CQySyncObj	syncObj;
			if  (  syncObj.sync(  CONST_mtxName_qm_evt  )  )  goto  errLabel;
			
			VH_stream  *  pVh_stream  =  &m_var.capBmp.compressVideo.vh_stream;
			//
			memcpy(  &pShmContent->u.evt.o.vh_stream,  pVh_stream,  sizeof(  pShmContent->u.evt.o.vh_stream  )  );
			pShmContent->u.evt.o.bDone_vh_stream  =  TRUE;
		}


		//		
		DWORD  dwThreadDaemonId;			
		//
		void  *  lpParameter  =  pSharedObj;//pTransform;	//  2015/10/06	//  pRtsp;						   
		//
		pEvt->readShm.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_readShm_evt,  lpParameter,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
		if  (  !pEvt->readShm.hThread  )  goto  errLabel;											  
		pEvt->readShm.dwThreadId  =  dwThreadDaemonId;										
		if  (  ResumeThread(  pEvt->readShm.hThread  )  ==  -1  )  goto  errLabel;									 

					   
	}


	iErr  =  0;
errLabel:

	return  iErr;
}
	
int  CCtxQmcEvt::exitEvt(  )
{
	int  iErr  =  -1;
	
	EVT_encV  *  pEvt  =  &m_var.evt;
	CCtxQmcEvt  *  pProcInfo  =  this;

	{

		//
		pEvt->bQuit  =  TRUE;
		//  2015/06/22
		SetEvent(  pEvt->readShm.hEvent_syncR  );
		//
		waitForObject(  &pEvt->readShm.hThread,  20000  );
		if  (  pEvt->readShm.hThread  )  {
			qyExitProcess(  _T(  "Failed: evt.writeShm.thread not waited"  )  );	
		}

		//
		if  (  pEvt->readShm.hEvent_syncR  )  {		
			CloseHandle(  pEvt->readShm.hEvent_syncR  );  pEvt->readShm.hEvent_syncR  =  NULL;	
		}
		//  2015/02/19
		if  (  pEvt->readShm.hEvent_syncW  )  {		
			CloseHandle(  pEvt->readShm.hEvent_syncW  );  pEvt->readShm.hEvent_syncW  =  NULL;	
		}

		
		//
		QY_shm  *  pShm  =  &pEvt->dataShm;
		if  (  pShm->pBuf  )  {
			UnmapViewOfFile(  pShm->pBuf  );  
			pShm->pBuf  =  NULL;	 
		}
		if  (  pShm->hMap  )  {
			 CloseHandle(  pShm->hMap  );  pShm->hMap  =  NULL;	 
		}

		//
	}

	iErr  =  0;
errLabel:
	return  iErr;
}









