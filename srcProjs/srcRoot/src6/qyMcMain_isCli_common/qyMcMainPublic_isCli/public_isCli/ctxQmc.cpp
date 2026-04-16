

#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"

#include	"ctxQmc.h"
#include	"policyAvParams.h"
#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcCommFunc_isCli.h"
#include	"qmcCmdProc.h"
#include	"qmcVideoTool.h"
//
#include	"funcsForIsCliHelp.h"
#include	"isCliHelpPublic.h"
#include	"imgProcessPublic.h"
#include	"isCliCorePublic.h"
#include	"qmcTaskInfo.h"
//
#include	"load_isD3dFunc.h"
//
#include	"dynLib_isD3dFunc.h"	//  2017/10/09
#include	"isCliExPublic.h"
#include	"smCommProc.h"

//
CCtxQmc::CCtxQmc(  )
{
	//  2014/02/08
	this->m_iCtxType  =  CONST_ctxType_qmc;

	//
#ifdef  __DEBUG__
		this->test1  =  567;
		this->test2  =  901;
#endif

	//
	int  size  =  &this->_bEnd  -  &this->_start;
	memset(  &this->_start,  0,  size  );

	//
	CCtxQmc* pProcInfo = this;
			

	//
	return;
}

CCtxQmc::~CCtxQmc(  )
{

}



//
RW_lock_param  *  CCtxQmc::get_qyMc_rwLockParam(  )
{  
	QY_MC  *  pQyMc  =  this->pQyMc;

	return  &pQyMc->cfg.rwLockParam;		
}



TCHAR  *  CCtxQmc::get_appObjPrefix(  )
{
	QY_MC  *  pQyMc  =  this->pQyMc;

	return  pQyMc->appParams.appObjPrefix;

}




void  *  CCtxQmc::get_qmc_cfg(  )
{
	return  &this->cfg;
}


QNM_CUSRES_INFO  *  CCtxQmc::get_qyMc_cusRes(  )
{
	QY_MC  *  pQyMc  =  this->pQyMc;

	return  &pQyMc->cusRes;
}



 QMC_status  *  CCtxQmc::get_qmc_status(  )
 {
	 return  &this->status;
 }



 QMC_debugStatusInfo  *  CCtxQmc::get_qmc_debugStatusInfo(  )
 {
	 return  &this->cfg.debugStatusInfo;
 }


 QY_sharedObj_sync  *  CCtxQmc::getSharedObjSyncByIndex(  int  index  )
 {
	 MC_VAR_isCli  *  pProcInfo  =  this;

	if  (  !pProcInfo  )  return  NULL;
	if  (  !pProcInfo->pSharedObjSyncs  )  return  NULL;
	if  (  index  <  0  ||  index  >=  pProcInfo->cfg.usMaxCnt_pSharedObjs  )  return  NULL;

	QY_sharedObj_sync  *  pSharedObjInfos  =  (  QY_sharedObj_sync  *  )pProcInfo->pSharedObjSyncs;

	return  &pSharedObjInfos[index];

 }


#if  0
QY_SHARED_OBJ  *  CCtxQmc::getSharedObjByIndex(  int  index  )
{
	QY_sharedObj_sync  *  pSharedObjInfo  =  getSharedObjSyncByIndex(  index  );
	if  (  !pSharedObjInfo  )  return  NULL;
	//
	return  &pSharedObjInfo->sharedObj;

}
#endif


CAP_procInfo_bmpU  *  CCtxQmc::getCapBmpBySth(  int  index,  unsigned  int  uiCapType  )
{
	CCtxQmc  *  pProcInfo  =  this;

	if  (  index  <  0  ||  index  >=  pProcInfo->cfg.usMaxCnt_capProcInfoBmps  )  return  NULL;
	//  if  (  !index  )  return  NULL;
	if  (  !index  )  return  (  CAP_procInfo_bmpU  *  )&pProcInfo->av.localAv.videoCaptureProcInfo;	//  2009/06/02
	if  (  uiCapType  )  {
		if  (  pProcInfo->pCapProcInfoBmps[index].common.uiType  !=  uiCapType  )  return  NULL;
	}
	return  &pProcInfo->pCapProcInfoBmps[index];
}



CAP_procInfo_audioU  *  CCtxQmc::getCapAudioBySth(  int  index,  unsigned  int  uiCapType  )
{
	CCtxQmc  *  pProcInfo  =  this;

	if  (  index  <  0  ||  index  >=  pProcInfo->cfg.usMaxCnt_capProcInfoAudios  )  return  NULL;
	//  if  (  !index  )  return  NULL;
	if  (  !index  )  return  (  CAP_procInfo_audioU  *  )&pProcInfo->av.localAv.recordSoundProcInfo;
	if  (  uiCapType  )  {
		if  (  pProcInfo->pCapProcInfoAudios[index].common.uiType  !=  uiCapType  )  return  NULL;
	}
	return  &pProcInfo->pCapProcInfoAudios[index];


}

//
void  *  CCtxQmc::get_QM_SHM_CMDS(  )
{
	QM_SHM_CMDS	*	pShmCmds  =  QY_GET_shmCmds(  this  );				
	return  pShmCmds;
}



//
int  CCtxQmc::newShmCmdIndex(  int  iIndex_sharedObj  )
{	
	MC_VAR_isCli  *  pProcInfo  =  this;

	if  (  iIndex_sharedObj  <  0  ||  iIndex_sharedObj  >=  pProcInfo->cmdsShm.usMaxCnt_qmCmds  )  return  -1;
	
#if  1	
	QM_SHM_CMD	*	pShmCmd		=	getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  iIndex_sharedObj  );
	if  (  !pShmCmd  )  return  -1;
	memset(  pShmCmd,  0,  sizeof(  pShmCmd[0]  )  );
#endif

	return  iIndex_sharedObj;

}


//
void  *  CCtxQmc::getQmShmCmdByIndex(  int  iIndex  )
{
	MC_VAR_isCli  *  pProcInfo  =  this;
	QM_SHM_CMDS  *  pCmds  =  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf;

	return  getShmCmdByIndex(  pCmds,  iIndex  );
}


//  2016/013/15
void  *  CCtxQmc::getQmcTaskInfoByIndex(  int  index  )
{
	MC_VAR_isCli  *  pProcInfo  =  this;

	/*
	//
	QMC_TASK_INFO  *  pTaskInfos  =  (  QMC_TASK_INFO  *  )pProcInfo->pQmcTaskInfos;

	if  (  index  <  0  ||  index  >=  pProcInfo->cfg.usMaxCnt_taskInfos  )  return  NULL;

	QMC_TASK_INFO				*	pTaskInfo	=	&pTaskInfos[index];

	return  pTaskInfo;
	*/
	return ::getQmcTaskInfoByIndex(pProcInfo,index);
}


//
int CCtxQmc::getQmcTaskInfoIndexBySth(int iTaskId)
{

	return  ::getQmcTaskInfoIndexBySth(this, iTaskId);
}



//
void  *  CCtxQmc::get_g_guiData(  )
{
	MC_VAR_isCli  *  pProcInfo  =  this;
	if  (  !pProcInfo  )  return  NULL;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );	
	if  (  !pFuncs   ) return  NULL;

	return  pFuncs->pf_get_g_guiData(  );
}


//
int  CCtxQmc::getAuthType(  )
{
	return  bSupported_devAuth(  )  ?  CONST_authType_dev  :  CONST_authType_logon;
}


//
 unsigned  char  CCtxQmc::get_ucCnt_misCnts(  )
 {
	 return  this->ucCnt_misCnts;
 }

//
  MIS_CNT  *  CCtxQmc::getMisCntByName(  LPCTSTR  misServName  )
  {
	  int  i;
	  CCtxQmc  *  pProcInfo  =  this;


	  for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  {
		  MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )getMisCntByIndex(  i  );
		  if  (  !pMisCnt  )  continue;

		  if  (  !lstrcmpi(  pMisCnt->cfg.misServName,  misServName  )  )  {
			  return  pMisCnt;  //  &pProcInfo->misCnts[i];
		  }
	 }

errLabel:
	 return  NULL;
	  
  }


MIS_CNT  *  CCtxQmc::getMisCntByIndex(  int  iIndex  )
{
	CCtxQmc  *  pProcInfo  =  this;

	//
	if  (  iIndex  <  0  ||  iIndex  >  pProcInfo->ucCnt_misCnts  )  return  NULL;

	return  &pProcInfo->pMisCnts[iIndex];
}



HWND  CCtxQmc::get_hMainWnd(  )
{
	QY_MC  *  pQyMc  =  (  QY_MC  *  )this->pQyMc;
	if  (  !pQyMc  )  return  NULL;

	return  pQyMc->gui.hMainWnd;
}



void  *  CCtxQmc::getPolicyAvParams(  )
{
	PolicyAvParams  *  p  =  this->p_gAvParams;	//  QY_GET_PolicyAvParams(  );

	return  p;
}


//  2015/10/30
void  *  CCtxQmc::get_pFuncs_for_isCliHelp(  )
{
	FUNCS_for_isCliHelp  *  p  =  (  FUNCS_for_isCliHelp  *  )this->pFuncs_for_isCliHelp;
	return  p;
}


void  *  CCtxQmc::getCusModules(  )
{
	QY_MC  *  pQyMc  =  (  QY_MC  *  )this->pQyMc;
	if  (  !pQyMc  )  return  NULL;

	return  &pQyMc->cusModules;
}


BOOL  CCtxQmc::bSupported_dvt(  unsigned  int  uiModuleType_toDec  )
{
	BOOL  bRet  =  FALSE;

	 //
	QY_MC  *  pQyMc  =  (  QY_MC  *  )this->pQyMc;
	if  (  !pQyMc  )  return  FALSE;

	if  (  pQyMc->appParams.ucbNoDvt  )  {
		return  FALSE;
	}


	//
	/*
	switch  (  uiModuleType_toDec  )  {
			case  CONST_moduleType_mediaSdk_dec:
			case  CONST_moduleType_dec_nv:	//  2015/04/23
			case  CONST_moduleType_dec_amf:	//  2015/05/06
			//case  CONST_moduleType_dec_vp8:
				  bRet  =  TRUE;
				  break;
			default:
					break;
	}
	*/
	 

	//	
	return  bRet;
}

//  2015/10/11
BOOL  CCtxQmc::bSupported_evt(  unsigned  int  uiModuleType_toEnc  )
{
	BOOL  bRet  =  FALSE;

	//
#ifdef  __DEBUG__
		#if  0
			 traceLog((TCHAR*)  _T(  "TEST: evt.bSupported_encVideoTool false"  )  );
			 return  FALSE;
		#endif
#endif


	 //
	QY_MC  *  pQyMc  =  (  QY_MC  *  )this->pQyMc;
	if  (  !pQyMc  )  return  FALSE;

	if  (  pQyMc->appParams.ucbNoEvt  )  {
		return  FALSE;
	}


	//
	/*
	switch  (  uiModuleType_toEnc  )  {
			case  CONST_moduleType_mediaSdk_enc:
			case  CONST_moduleType_enc_nv:	//  2015/04/23
			case  CONST_moduleType_enc_amf:	//  2015/05/06
			//case  CONST_moduleType_dec_vp8:
				  bRet  =  TRUE;
				  break;
			default:
					break;
	}
	*/
	 

	//	
	return  bRet;
}


//  2017/10/11
BOOL  CCtxQmc::bUse_imObjView_as_guiWnd(  )
{
	return  ::bUse_imObjView_as_guiWnd(  );
}


BOOL  CCtxQmc::bSupport_sharedTex()
{
	return  false;
}


//
 BOOL  CCtxQmc::b_qyMc_quit(  )
 {
	QY_MC  *  pQyMc  =  (  QY_MC  *  )this->pQyMc;
	if  (  !pQyMc  )  return  FALSE;

	return  pQyMc->bQuit;
 }


 // 2015/10/14
 QY_Q2  *  CCtxQmc::get_realTimeMediaQ2(  )
 {
	 return  &this->realTimeMediaQ2;
 }


 QY_Q2  *  CCtxQmc::get_mediaQ2(  )
 {
	 return  &this->mediaQ2;
 }





 BOOL  CCtxQmc::bWebcamUsing(  unsigned  int  uiCamCapType,  void  *  pMoniker_v,  LPCTSTR  camName,  int  *  piIndex_capBmp,  int  *  piIndex_sharedObj  )
 {
	 return  ::bWebcamUsing(  this,  uiCamCapType,  pMoniker_v,  camName,  piIndex_capBmp,  piIndex_sharedObj  );

 }


 //
 int  tmpHandler_bMediaTaskExists(  QY_MC  *  pQyMc,  void  *  p0,  void  *  p1,  TASK_common*taskElem  )
{
	int	iTaskId =  (  int  )p0;

	//CCtxQyMc *pQyMc=g_pQyMc;
	CCtxQmc * pProcInfo=(CCtxQmc * )pQyMc->get_pProcInfo();
	QMC_TASK_INFO * pTaskInfo=(QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo,taskElem->m_index_taskInfo);
	if(!pTaskInfo) return -1;

	MIS_MSGU  *  pMsg=&pTaskInfo->var.pTaskData->msgU;

	//
	if  (  pMsg->uiType  ==  CONST_misMsgType_task  )  {
		if  (  pMsg->task.iTaskId  ==  iTaskId  )  return 1;
	}

	return  0;
}


  BOOL  CCtxQmc::bMediaTaskExists(  int  iTaskId  )
 {	 
	BOOL		bRet	=	FALSE;

	MC_VAR_isCli  *  pProcInfo  =  this;

	if  (  pProcInfo->processQ_media.qTraverse(  tmpHandler_bMediaTaskExists,  (  void  *  )iTaskId,  0  )  <=  0  )  goto  errLabel;

	bRet  =  TRUE;
errLabel:
	return  bRet;

 }


  //
  BOOL  CCtxQmc::bAudioChannelReady(  )
  {
	  return  this->av.audio.bChannelReady;
  }


  //  2015/10/14
  BOOL  CCtxQmc::bVideoChannelReady(  )
  {
	  return  this->av.video.bChannelReady;
  }

  //
  int  CCtxQmc::toShareVideo_post(  unsigned  int  uiCapType,  int  iIndex_capProcInfo,  myDRAW_VIDEO_DATA  *  pkts,  unsigned  int  nPkts,  COMPRESS_VIDEO  *  pCompressVideo,  QY_SHARED_OBJ  *  pSharedObj,  MIS_MSGU  *  pMsgBuf  )
  {
	  return  toShareVideo_post_qmc(  this,  uiCapType,  iIndex_capProcInfo,  pkts,  nPkts,  pCompressVideo,  pSharedObj,  pMsgBuf  );
  }


  //
  int  CCtxQmc::drawLocalVideoData(  unsigned  int  uiTranNo,  myDRAW_VIDEO_DATA	*	pkts,  int  pktsLen,  BOOL  *  pbPktsRedirected,  unsigned  int  uiCapType,  int  iIndex_capBmp,  int  iTaskId,  void  *  pMIS_CNT,  QY_MESSENGER_ID  *  pIdInfo_peer  )
  {
	  return  ::drawLocalVideoData(  this,  uiTranNo,  pkts,  pktsLen,  pbPktsRedirected,  uiCapType,  iIndex_capBmp,  iTaskId,  (  MIS_CNT  *  )pMIS_CNT,  pIdInfo_peer  );
  }


int  CCtxQmc::drawVideoData(  myDRAW_VIDEO_DATA  *  pkts,  int  pktsLen,  BOOL  *  pbPktsRedirected,  void  *  pQY_TRANSFORM  )
{
	MC_VAR_isCli  *  pProcInfo  =  this;
	return  ::drawVideoData(  pProcInfo,  pkts,  pktsLen,  pbPktsRedirected,  pQY_TRANSFORM  );
}


//  2015/10/13
int  CCtxQmc::playLocalAudioData(  int  iTaskId,  unsigned  int  uiTranNo,  WAVEFORMATEX  *  pWf,  myPLAY_AUDIO_DATA  *  pPkt,  int  pktLen,  BOOL  *  pbPktRedirected,  unsigned  int  uiCapType,  int  iIndex_capAudio  )
{
	//return  ::playLocalAudioData(  this,  iTaskId,  uiTranNo,  pWf,  pPkt,  pktLen,  pbPktRedirected,  uiCapType,  iIndex_capAudio  );
	return  ::playLocalAudioData(  this,  iTaskId,  uiTranNo,  pWf,  pPkt->head.uiSampleTimeInMs,  (  BYTE  *  )pPkt->memory.m_pBuf,  pPkt->uiSize_dec,  uiCapType,  iIndex_capAudio  );

}

//
int  CCtxQmc::playAudioData(  int  iSampleTimeInMs,  unsigned  int  uiPts,  BYTE  *  pInput,  unsigned  int  inputLen,  int  iIndex_player  )
{
	return  ::playAudioData(  this,  iSampleTimeInMs,  uiPts,  pInput,  inputLen,  iIndex_player  );
}




//  2015/10/14
void  *  CCtxQmc::get_cur_SUBTITLES_cfg(  int  iSharedObjType,  int  iCapType,  int  iCapSubType  )
{
	return  ::getCurSubtitlesCfg(  iSharedObjType,  iCapType,  iCapSubType  );  
}


int CCtxQmc::resizeRgb24(  unsigned  char  *  src,  int  srcWidth,  int  srcHeight,  unsigned  char  *  dst,  int  dstWidth,  int  dstHeight  )
{
	return  ::resizeRgb24(  src,  srcWidth,  srcHeight,  dst,  dstWidth,  dstHeight  );
}


int  CCtxQmc::showNotification(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  LPCTSTR  hint  )
{
	return  ::showNotification(  pMisCnt,  pIdInfo_logicalPeer,  pIdInfo_from,  tStartTime,  uiTranNo,  uiContentType,  hint  );
}





/////////////// //  2012/03/24
 int  tmpHandler_findTaskInvalid_gui(  QY_MC  *  pQyMc,  void  *  p0,  void  *  p1,  TASK_common  *  pTaskElemParam  )
{
	int					iErr					=	-1;
	//
	CCtxQmc	*	pProcInfo						=	(  CCtxQmc  *  )p0;//
	//  
	BOOL			*	pbInvalidTaskExists		=	(  BOOL  *  )p1;
	TASK_common		*	taskElem				=	(  TASK_common  *  )pTaskElemParam;
	QMC_TASK_INFO	*	pTaskInfo				=	(  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(pProcInfo,  taskElem->m_index_taskInfo  );
	if(  pTaskInfo  ==  NULL  )  return  -1;
	MIS_MSGU		*	pMsg					=	(  MIS_MSGU  *  )&pTaskInfo->var.pTaskData->msgU;//pMsgParamElem;
	//
	BOOL				bInvalidTaskExists		=	FALSE;
	QY_WMBUF_COMM		wmBuf;


	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_task:  {
				  IM_CONTENTU	*	pContent	=	M_getMsgContent(  pMsg->task.ucFlg,  &pMsg->task.data  );
				  if  (  !pContent  )  goto  errLabel;
				  switch  (  pContent->uiType  )  {
						  case  CONST_imCommType_transferAvInfo:  
						  case  CONST_imCommType_transferAvReplyInfo:
							  {
							    PROC_TASK_AV	 *  pTask			=	NULL;
								TASK_transferAv  *  task= (TASK_transferAv  *  )taskElem;
								//
								if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
									//
									pTask  =  &task->myTask;//get_transferAvInfo_pTask(  &pContent->transferAvInfo,  _T(  ""  )  );  
									if  (  !pTask  )  goto  errLabel;
									}
								else  if  (  pContent->uiType  ==  CONST_imCommType_transferAvReplyInfo  )  {
										  pTask  =  &task->myTask;//get_transferAvReplyInfo_pTask(  &pContent->transferAvReplyInfo,  _T(  ""  )  );	//  &pContent->transferAvReplyInfo.myTask;
										  if  (  !pTask  )  goto  errLabel;
										  }
								else  {
									  MACRO_qyAssert(  0,  _T(  "tmpHandler_findTaskInvalid err, unknown uiType"  )  );
									  goto  errLabel;
								}
								//
								if  (  !IsWindow(  pTask->hWnd_task  )  )  {
									pTask->bTaskInvalid  =  TRUE;	
									bInvalidTaskExists  =  TRUE;
									break;
								}
								//
								QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pTask->iIndex_sharedObj  );
								if  (  pSharedObj  )  {  //  2014/09/29. slave可以等master要退出时才退出
									if  (  pSharedObj->bSlave  )  break;
								}
								//
								memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
								wmBuf.uiType  =  CONST_qyWmParam_chkTask;
								wmBuf.u.chkTask.iTaskId  =  pMsg->task.iTaskId;
								if  (  CONST_qyWmRc_ok  ==  SendMessage(  pTask->hWnd_task,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  )  )  {
									if  (  wmBuf.u.chkTask.bNotExists  )  {
										pTask->bTaskInvalid  =  TRUE;  
										bInvalidTaskExists  =  TRUE;
										break;
									}									
								}
								if  (  !wmBuf.u.chkTask.bChked  )  {
									traceLogA(  (char*)  "Warning: tmpHandler_bTaskInvalid error: hWnd_task can't process chkTask msg"  );
								}
								}
								break;
						  case  CONST_imCommType_transferFileReq:  {
							    traceLogA(  (char*)"not finished" );
								goto errLabel;
								//
							    PROC_TASK_FILE	*	pTask  =  NULL;//&pContent->transferFileReq.myTask;
								if  (  !IsWindow(  pTask->hWnd_task  )  )  {
									pTaskInfo->var.bTaskInvalid  =  TRUE;
									bInvalidTaskExists  =  TRUE;
									break;
								}
								}
							    break;
						  case  CONST_imCommType_transferFileReplyReq:{
							    traceLogA(  (char*)"not finished" );
								goto errLabel;
								//
							    PROC_TASK_FILE	*	pTask  =  NULL;//&pContent->transferFileReplyReq.myTask;
								if  (  !IsWindow(  pTask->hWnd_task  )  )  {
									pTaskInfo->var.bTaskInvalid  =  TRUE;
									bInvalidTaskExists  =  TRUE;
									break;
								}
								}
							    break;
						  case  CONST_imCommType_transferGpsInfo:  {	//  2012/04/19
							    PROC_TASK_GPS	*	pTask  =  &pContent->transferGpsInfo.myTask;
							    if  (  !IsWindow(  pTask->hWnd_task  )  )  {
									pTask->bTaskInvalid  =  TRUE;
									bInvalidTaskExists  =  TRUE;
									break;
								}
								memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
								wmBuf.uiType  =  CONST_qyWmParam_chkTask;
								wmBuf.u.chkTask.iTaskId  =  pMsg->task.iTaskId;
								if  (  CONST_qyWmRc_ok  ==  SendMessage(  pTask->hWnd_task,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  )  )  {
									if  (  wmBuf.u.chkTask.bNotExists  )  {
										pTask->bTaskInvalid  =  TRUE;  
										bInvalidTaskExists  =  TRUE;
										break;
									}									
								}
								}
							    break;
						  default:
								  #ifdef  __DEBUG__
										  traceLog((TCHAR*)  _T(  "tmpHandler_bTaskInvalid: unknown contentType"  )  );
								  #endif
								  break;
				  }
				  }
				  break;
			default:
				    traceLogA(  (char*)  "tmpHandler_bTaskInvalid: msgType [%d] error",  pMsg->uiType  );
					break;
	}

	if  (  bInvalidTaskExists  )  {
		if  (  pbInvalidTaskExists  )  *pbInvalidTaskExists  =  TRUE;
	}
	iErr  =  0;
errLabel:
	return  iErr;
}


//
int  CCtxQmc::qisChkTasks_gui(  )
{
	MC_VAR_isCli  *  pProcInfo  =  this;
	
	int								iErr				=	-1;
	//QY_SERVICEGUI_INFO		*		pSci				=	getServiceGuiInfo(  pQyMc,  pQyMc->iServiceId  );
	//if  (  !pSci  )  return  -1;
	//MC_VAR_isCli				*		pProcInfo			=	(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC					*		pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;	//
	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_mis  )  return  -1;

	//
	//
	BOOL							bInvalidTaskExists;

	traceLogA(  (char*)  "qisChkTasks_gui(  ) called."  );
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qisChkTasks_gui called"  )  );

	#ifdef  __DEBUG__
			_ASSERT(  pProcInfo->processQ_media.m_var.dwThreadId_gui  ==  GetCurrentThreadId(  )  );
	#endif
				
	bInvalidTaskExists  =  FALSE;
	pProcInfo->processQ_media.qTraverse(  tmpHandler_findTaskInvalid_gui,  pProcInfo,  &bInvalidTaskExists  );
	if  (  bInvalidTaskExists  )  {
		//this->applyForRemovingInvalidTasks(  CONST_channelType_media  );
	}

	//
#if  0
	#ifdef  __DEBUG__
			_ASSERT(  pProcInfo->processQ_robot.m_var.dwThreadId_gui  ==  GetCurrentThreadId(  )  );
	#endif

	bInvalidTaskExists  =  FALSE;
	pProcInfo->processQ_robot.qTraverse(  tmpHandler_findTaskInvalid_gui,  pProcInfo,  &bInvalidTaskExists  );
	if  (  bInvalidTaskExists  )  qisApplyForChkingTasks(  CONST_channelType_robot  );
#endif

	//  2009/12/28
	PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_task_end,  0  );	

	//
	iErr  =  0;

	return  iErr;
}






//  2012/03/24
/*
  BOOL  tmpHandler_bTaskInvalid(  void  *  p0,  void  *  p1,  void  *  pMsgParamElem  )
{
	BOOL			bRet	=	FALSE;
	MIS_MSGU	*	pMsg	=	(  MIS_MSGU  *  )pMsgParamElem;
	int				i;

	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_task:  {
				  IM_CONTENTU	*	pContent	=	M_getMsgContent(  pMsg->task.ucFlg,  &pMsg->task.data  );
				  if  (  !pContent  )  goto  errLabel;
				  switch  (  pContent->uiType  )  {
						  case  CONST_imCommType_transferAvInfo:  
						  case  CONST_imCommType_transferAvReplyInfo:
							  {
							    PROC_TASK_AV	 *  pTask			=	NULL;
								if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
									pTask  =  get_transferAvInfo_pTask(  &pContent->transferAvInfo,  _T(  ""  )  );	//  &pContent->transferAvInfo.myTask;
									if  (  !pTask  )  goto  errLabel;
									}
								else  if  (  pContent->uiType  ==  CONST_imCommType_transferAvReplyInfo  )  {
										  pTask  =  get_transferAvReplyInfo_pTask(  &pContent->transferAvReplyInfo,  _T(  ""  )  );	//  &pContent->transferAvReplyInfo.myTask;
										  if  (  !pTask  )  goto  errLabel;
										  }
								else  {
									  MACRO_qyAssert(  0,  _T(  "tmpHandler_bTaskInvalid err, unknown uiType"  )  );
									  goto  errLabel;
								}

								if  (  pTask->bTaskInvalid  )  {

									#if  0
									//  先要检查transform是否都已经清理完毕,否则就不从队列删除
									BOOL	bActive  =  FALSE;
									for  (  i  =  0;  i  <  pTask->usCntLimit_transforms;  i  ++  )  {
										 QY_TRANSFORM	*	p	=	&pTask->pTransforms[i];
										 if  (  p->v_preTransThread.hThread  )  {
											 p->v_preTransThread.bQuit  =  TRUE;
										 }
										 if  (  p->audio.hThread  )  {
											 p->audio.bQuit  =  TRUE;
										 }
										 if  (  p->video.hThread  )  {
											 p->video.bQuit  =  TRUE;
										 }
										 //										 
										 if  (  p->video.dwTickCnt_start
											 &&  p->video.bRunning  )
										 {
											 bActive  =  TRUE;
										 }
									}
									if  (  bActive  )  {
										//  还在活跃着, 不能删除
										qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "task %d still active"  ),  pMsg->task.iTaskId  );
										break;
									}
									#endif

									qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "task %d will be removed"  ),  pMsg->task.iTaskId  );
									//
									bRet  =  TRUE;  goto  errLabel;
								}
								}
								break;
						  case  CONST_imCommType_transferFileReq:  {
							    traceLogA(  (char*)"not finished" );
								goto errLabel;
								//
							    PROC_TASK_FILE	*	pTask	=	NULL;//&pContent->transferFileReq.myTask;
								if  (  pTask->bTaskInvalid  )  {
									bRet  =  TRUE;  goto  errLabel;
								}
								if  (  pTask->bNeedRemoved  )  {  //  2015/09/08
									bRet  =  TRUE;  goto  errLabel;
								}
								}
							    break;
						  case  CONST_imCommType_transferFileReplyReq:  {
							    traceLogA(  (char*)"not finished" );
								goto errLabel;
								//
							    PROC_TASK_FILE	*	pTask	=	NULL;//&pContent->transferFileReplyReq.myTask;
								if  (  pTask->bTaskInvalid  )  {
									bRet  =  TRUE;  goto  errLabel;
								}
								if  (  pTask->bNeedRemoved  )  {
									bRet  =  TRUE;  goto  errLabel;
								}
								}
							    break;
						  case  CONST_imCommType_transferGpsInfo:   {		//  2012/04/19
							    PROC_TASK_GPS  *  pTask  =  &pContent->transferGpsInfo.myTask;
								if  (  pTask->bTaskInvalid  )  {
									bRet  =  TRUE;  goto  errLabel;
								}
								}
							    break;
						  default:
								  #ifdef  __DEBUG__
										  traceLog((TCHAR*)  _T(  "tmpHandler_bTaskInvalid: unknown contentType"  )  );
								  #endif
								  break;
				  }
				  }
				  break;
			default:
				    traceLogA(  (char*)  "tmpHandler_bTaskInvalid: msgType [%d] error",  pMsg->uiType  );
					break;
	}

errLabel:
	return  bRet;
}
*/

//
/*
  int  CCtxQmc::removeInvalidTasks(  unsigned  int  uiChannelType  )			//  2009/09/10
{
	MC_VAR_isCli  *  pProcInfo  =  this;

	int								iErr				=	-1;
	//QY_SERVICEGUI_INFO		*		pSci				=	getServiceGuiInfo(  pQyMc,  pQyMc->iServiceId  );
	//if  (  !pSci  )  return  -1;
	//MC_VAR_isCli				*		pProcInfo			=	(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC					*		pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;	//  
	if  (  !pQyMc  )  return  -1;
	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_mis  )  return  -1;


	//
	CMcSharedQ				*		pSharedQ			=	NULL;

#ifdef  __DEBUG__
	traceLogA(  (char*)  "qisChkTasks called"  );
#endif
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "ctxQmc.removeInvalidTasks called"  )  );

	//
#if  0
	switch  (  uiChannelType  )  {
			case  CONST_channelType_robot:
				  pSharedQ  =  &pProcInfo->processQ_robot;
				  break;
			case  CONST_channelType_media:
				  pSharedQ  =  &pProcInfo->processQ_media;
				  break;
			default:
					goto  errLabel;
	}
#endif
	pSharedQ  =  &pProcInfo->processQ_media;

	#ifdef  __DEBUG__
			//_ASSERT(  pSharedQ->m_var.dwThreadId_gui  !=  GetCurrentThreadId(  )  );
			if  (  GetCurrentThreadId(  )  !=  pProcInfo->dwThreadId_mgr  )  {
				MACRO_qyAssert(  0,  _T(  "qisRemoveInvalidTasks failed, not thread mgr"  )  );
				goto  errLabel;
			}
	#endif

	pSharedQ->qRemoveMsg(  tmpHandler_bTaskInvalid,  0,  0  );

	iErr  =  0;
errLabel:
	return  iErr;
}
*/




  //  2016/04/28  
  int  CCtxQmc::get_deced_pktResType(  unsigned  int  uiModuleType,  int  iFourcc,  unsigned  short  *  pusPktResType_o  )				//  2015/10/04
  {
	 int  iErr  =  -1;
	 unsigned  short  usPktResType  =  0;

	 //
	 QY_MC  *  pQyMc  =  this->pQyMc;

	 //
	 switch  (  pQyMc->env.iPlatformId  )  {
			 case  CONST_qyPlatform_winxp:
			 case  CONST_qyPlatform_win2003:
			 case  CONST_qyPlatform_winVista:
			 case  CONST_qyPlatform_win2008:
			 case  CONST_qyPlatform_win7:
			 case  CONST_qyPlatform_win2008R2:
				   iErr  =  0;  goto  errLabel;
				   break;
			 default:
					break;
	 }

	 //
	 if (uiModuleType == CONST_moduleType_decD3d_nv) {
		 usPktResType = CONST_pktResType_sharedTex;
		 iErr = 0;  goto  errLabel;
	 }

	 //
	 int  pktUsage; pktUsage = CONST_pktUsage_dec;

	 //  2017/01/10
	 //if  (  !bUse_imObjView_as_guiWnd(  )  )  
	 if  ( bSupport_sharedTex()  )
	 {
		 if  (  bApp_ts_3d(  pQyMc  )  )  {
			 //
			 switch  (  pktUsage  )  {
					 case  CONST_pktUsage_dec:  {
						   //				 
						   int  propId  =  CONST_qdcPropId_bSupport_sharedTex_dec;		
						   //  2017/10/11
						   PARAM_bSupport_sharedTex_dec  param_bsd  =  {0};
						   param_bsd.iFourcc  =  iFourcc;

						   //
						   BOOL  bVal  =  FALSE;
						   if  (  !getVal_bSupported_pktResType_sharedTex(  this,  uiModuleType,  propId,  &param_bsd,  &bVal  )  
							   &&  bVal  )							  
						   {
							   //  2015/11/01
							   usPktResType  =  CONST_pktResType_sharedTex;							  
						   }		 			  
						   }
						   break;
					 case  CONST_pktUsage_enc:  {
						   //
						   int  propId  =  CONST_qdcPropId_bSupport_sharedTex_enc;			
						   //  2017/10/11
						   PARAM_bSupport_sharedTex_enc  param_bse  =  {0};
						   param_bse.iFourcc  =  iFourcc;

						   //
						   BOOL  bVal  =  FALSE;
						   if  (  !getVal_bSupported_pktResType_sharedTex(  this,  uiModuleType,  propId,  &param_bse,  &bVal  )  
							   &&  bVal  )			
						   {
							   usPktResType  =  CONST_pktResType_sharedTex;
						   }			
						   }
						   break;
					 default:
							 break;
			 }
		 }
	 }

	 iErr  =  0;
errLabel:

	 //
	 if  (  !iErr  )  {
		 if  (  pusPktResType_o  )  {
			 *pusPktResType_o  =  usPktResType;
		 }
	 }

	 return  iErr;
  }

  //	
  int  CCtxQmc::get_pktResType_toEnc(  unsigned  short  usPktResType_src,  unsigned  int  uiModuleType,  int  iFourcc,  unsigned  short  *  pusPktResType_i  )				//  2015/10/04
  {
	 int  iErr  =  -1;
	 unsigned  short  usPktResType  =  0;

	 //
	 QY_MC  *  pQyMc  =  this->pQyMc;

	 //
	 switch  (  pQyMc->env.iPlatformId  )  {
			 case  CONST_qyPlatform_winxp:
			 case  CONST_qyPlatform_win2003:
			 case  CONST_qyPlatform_winVista:
			 case  CONST_qyPlatform_win2008:
			 case  CONST_qyPlatform_win7:
			 case  CONST_qyPlatform_win2008R2:
				   iErr  =  0;  goto  errLabel;
				   break;
			 default:
					break;
	 }

	 //
	 if (uiModuleType == CONST_moduleType_encD3d_nv) {
		 usPktResType = CONST_pktResType_sharedTex;
		 iErr = 0;  goto  errLabel;
	 }


	 //
	 if  (  usPktResType_src  !=  CONST_pktResType_sharedTex  )  {
		 iErr  =  0;  goto  errLabel;
	 }

	 //
	 int  pktUsage; pktUsage = CONST_pktUsage_enc;

	 //  2017/01/10
	 if  (  !bUse_imObjView_as_guiWnd(  )  )  {
		 if  (  bApp_ts_3d(  pQyMc  )  )  {
			 //
			 switch  (  pktUsage  )  {
					 case  CONST_pktUsage_dec:  {
						   //				 
						   int  propId  =  CONST_qdcPropId_bSupport_sharedTex_dec;				
						   //
						   PARAM_bSupport_sharedTex_dec  param_bsd  =  {0};
						   param_bsd.iFourcc  =  iFourcc;
						   //
						   BOOL  bVal  =  FALSE;
						   if  (  !getVal_bSupported_pktResType_sharedTex(  this,  uiModuleType,  propId,  &param_bsd,  &bVal  )  
							   &&  bVal  )							  
						   {
							   //  2015/11/01
							   usPktResType  =  CONST_pktResType_sharedTex;							  
						   }		 			  
						   }
						   break;
					 case  CONST_pktUsage_enc:  {
						   //
						   int  propId  =  CONST_qdcPropId_bSupport_sharedTex_enc;			
						   //
						   PARAM_bSupport_sharedTex_enc  param_bse  =  {0};
						   param_bse.iFourcc  =  iFourcc;
						   //
						   BOOL  bVal  =  FALSE;
						   if  (  !getVal_bSupported_pktResType_sharedTex(  this,  uiModuleType,  propId,  &param_bse,  &bVal  )  
							   &&  bVal  )			
						   {
							   usPktResType  =  CONST_pktResType_sharedTex;
						   }			
						   }
						   break;
					 default:
							 break;
			 }
		 }
	 }

	 iErr  =  0;
errLabel:

	 //
	 if  (  !iErr  )  {
		 if  (  pusPktResType_i  )  {
			 *pusPktResType_i  =  usPktResType;
		 }
	 }

	 return  iErr;
  }

  
  		
	
  //
#if  0
  int  CCtxQmc::qdcInitCompressVideo_evtCli(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_decompress,  QY_VIDEO_HEADER  *  pVh_compress,  unsigned  int  uiModuleType,  QDC_OBJ_INFO  *  pQdcObjInfo  )
  {
	  return  ::qdcInitCompressVideo_evtCli(  pVideoCompressorCfg_reserved,  pVh_decompress,  pVh_compress,  uiModuleType,  pQdcObjInfo  );
  }


  //
  int  CCtxQmc::qdcExitCompressVideo_evtCli(  QDC_OBJ_INFO  *  pQdcObjInfo  )
  {
	  return  ::qdcExitCompressVideo_evtCli(  pQdcObjInfo  );
  }

  //
  int  CCtxQmc::qdcGetSpsPps_evtCli(  QDC_OBJ_INFO  *  pQdcObjInfo,  char  *  spsBuf,  unsigned  int  *  puiSpsSize,  char  *  ppsBuf,  unsigned  int  *  puiPpsSize,  char  *  kk,  unsigned  int  *  puiKkSize  )
  {
	  return  ::qdcGetSpsPps_evtCli(  pQdcObjInfo,  spsBuf,  puiSpsSize,  ppsBuf,  puiPpsSize,  kk,  puiKkSize  );

  }


  //
  int  CCtxQmc::doEncodeVideo_evtCli_run(  CAP_procInfo_bmpCommon  *  pCapProcInfo,  void  *  pMIS_CNT,  MIS_MSGU  *  pMsgBuf  )		
  {
	  return  ::doEncodeVideo_evtCli_run(  this,  pCapProcInfo,  pMIS_CNT,  pMsgBuf  );
  }
#endif

  //  2015/10/30
  void  *  CCtxQmc::get_pf_DXUTSaveTextureToFile(  )
  {

	FUNCS_for_isCliHelp  *  pFuncs  =  (  FUNCS_for_isCliHelp  *  )this->get_pFuncs_for_isCliHelp(  );
	if  (  !pFuncs  )  return  NULL;

	//
	DYN_LIB_isD3dFunc  *  pLib_isD3dFunc  =  (  DYN_LIB_isD3dFunc  *  )pFuncs->pDynLib_isD3dFunc;
	if  (  !pLib_isD3dFunc  )  return  NULL;

	//
	return  pLib_isD3dFunc->pf_DXUTSaveTextureToFile;
 }


  //  2016/02/12
  int  CCtxQmc::set_enlarged_gZone(  HWND  hWnd  )
  {
	  return  ::set_enlarged_gZone(  this,  hWnd  );
  }

  //  2016/04/26
  int  CCtxQmc::initCompressVideo(  BITMAPINFO  *  pBmpInfo_input,  unsigned  int  uiCapType,  VIDEO_COMPRESSOR_CFG  *  pCompressor,  BOOL  bCapDev,  unsigned  int  uiBufSize_pData,  COMPRESS_VIDEO  *  pCompressVideo  )
  {  
	  return  ::initCompressVideo(  this,  pBmpInfo_input,  uiCapType,  pCompressor,  bCapDev,  uiBufSize_pData,  pCompressVideo  );
  }



  //  2016/04/26
  int  CCtxQmc::exitCompressVideo(  BOOL  bCapDev,  COMPRESS_VIDEO  *  pCompressVideo  )
  {
	  return  ::exitCompressVideo(  this,  bCapDev,  pCompressVideo  );
  }


  //
  int  qmc_qdcGetVorbisHeaders(  QDC_OBJ_INFO  *  pQdcObjInfo,  char  *  pBuf_header0,  unsigned  int  *  puiBufSize_header0,  char  *  pBuf_header1,  unsigned  int  *  puiBufSize_header1,  char  *  pBuf_header2,  unsigned  int  *  puiBufSize_header2  )
  {
	  int  iErr  =  -1;
	  if  (  pQdcObjInfo->uiType  !=  CONST_qoiType_decA  )  return  -1;
	  if  (  pQdcObjInfo->cfg.a.uiTransformType_pParent  !=  CONST_uiTransformType_dec  )  return  -1;
	  QY_TRANSFORM  *  pTransform  =  (  QY_TRANSFORM  *  )pQdcObjInfo->cfg.a.pParent_transform;

	  AH_stream  *  pAs  =  &pTransform->audio.ta.ah_stream;
	  if  (  pAs->mems[0].usLen  +  pAs->mems[1].usLen  +  pAs->mems[2].usLen  >  sizeof(  pAs->buf  )  )  goto  errLabel;
	  char* pHeader0; pHeader0 = pTransform->audio.ta.ah_stream.buf;
	  char* pHeader1; pHeader1 = pHeader0 + pAs->mems[0].usLen;
	  char* pHeader2; pHeader2 = pHeader1 + pAs->mems[1].usLen;

	  if  (  *puiBufSize_header0  <  pAs->mems[0].usLen  )  goto  errLabel;
	  memcpy(  pBuf_header0,  pHeader0,  pAs->mems[0].usLen  );
	  *puiBufSize_header0  =  pAs->mems[0].usLen;
	  if  (  *puiBufSize_header1  <  pAs->mems[1].usLen  )  goto  errLabel;
	  memcpy(  pBuf_header1,  pHeader1,  pAs->mems[1].usLen  );
	  *puiBufSize_header1  =  pAs->mems[1].usLen;
	  if  (  *puiBufSize_header2  <  pAs->mems[2].usLen  )  goto  errLabel;
	  memcpy(  pBuf_header2,  pHeader2,  pAs->mems[2].usLen  );
	  *puiBufSize_header2  =  pAs->mems[2].usLen;
	  

	  //
	  #ifdef  __DEBUG__
		#if  10
			  int  iii;
			  for  (  iii  =  0;  iii  <  58;  iii  ++  )  {
				   TCHAR  tt[128];
				   _sntprintf(  tt,  mycountof(  tt  ),  _T(  "header[%d] %02x\n"  ),  iii,  (  unsigned  char  )pAs->buf[iii]  );
				   OutputDebugString(  tt  );
			  }
			  iii  =  iii;
		#endif
	#endif



	  iErr  =  0;

errLabel:
	  return  iErr;

  }



  //
  //
int  qmc_preForTest_encDev_YUVReader_myLoadNextFrame(	void  *  pQDC_OBJ_INFO,
						     							void									*	pENC_d3d11_devVar  								
														)
{
	
	//QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	//if  (  !pQyMc  )  return  -1;
	

	return  0;
}




  //
  void  *  qmc_qoi_getPtrProperty(  void  *  pQdcObjInfoParam,  int  propertyId  )
  {
	//
	if  (  !pQdcObjInfoParam  )  {
		showInfo_open0(  0,  0,  _T(  "qmc_qoi_getPtrProperty failed, pQdcObjInfoParam is null"  )  );
		return  NULL;
	}
	MY_qoi  *  pMyQoi  =  (  MY_qoi  *  )pQdcObjInfoParam;

	//
	MC_VAR_isCli			*		pProcInfo							=	(  MC_VAR_isCli  *  )pMyQoi->pProcInfoCommon;	//  2016/09/07
	if  (  !pProcInfo  )  {
		showInfo_open0(  0,  0,  _T(  "qmc_qoi_getPtrProperty failed, myQoi.pProcInfo is null"  )  );
		return  NULL;
	}
	if  (  pProcInfo->m_iCtxType  !=  CONST_ctxType_qmc  )  {
		showInfo_open0(  0,  0,  _T(  "qmc_qoi_getPtrProperty failed, ctxType is not qmc"  )  );
		return  NULL;
	}

	//
	switch  (  propertyId  )  {
			case  CONST_qdcPropId_PF_qdcGetVorbisHeaders:
				  return  qmc_qdcGetVorbisHeaders;
				  break;
			case  CONST_qdcPropId_PF_preForTest_encDev_YUVReader_myLoadNextFrame:	//  2017/10/07
				  return  qmc_preForTest_encDev_YUVReader_myLoadNextFrame;
				  break;
			default:
					break;
	}

	//
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  NULL;

	return  get_ptr_isD3dFunc(  pFuncs->pDynLib_isD3dFunc,  propertyId  );

  }


  //  2016/12/17
 BOOL  qmc_qoi_bSetPtrProperty(  void  *  pQdcObjInfoParam,  int  propertyId,  void  *  ptr  )
 {
	BOOL  bRet  =  FALSE;

	//
	if  (  !pQdcObjInfoParam  )  {
		showInfo_open0(  0,  0,  _T(  "qmc_qoi_getPtrProperty failed, pQdcObjInfoParam is null"  )  );
		return  NULL;
	}
	MY_qoi  *  pMyQoi  =  (  MY_qoi  *  )pQdcObjInfoParam;

	//
	MC_VAR_isCli			*		pProcInfo							=	(  MC_VAR_isCli  *  )pMyQoi->pProcInfoCommon;	//  2016/09/07
	if  (  !pProcInfo  )  {
		showInfo_open0(  0,  0,  _T(  "qmc_qoi_getPtrProperty failed, myQoi.pProcInfo is null"  )  );
		return  NULL;
	}
	if  (  pProcInfo->m_iCtxType  !=  CONST_ctxType_qmc  )  {
		showInfo_open0(  0,  0,  _T(  "qmc_qoi_getPtrProperty failed, ctxType is not qmc"  )  );
		return  NULL;
	}

	//
	switch  (  propertyId  )  {
			case  CONST_qdcPropId_PF_qdcGetVorbisHeaders:
				  if  (  pMyQoi->common.uiType  !=  CONST_qoiType_encA  )  goto  errLabel; 
				  //
				  QOI_encA  *  pQe;
				  pQe  =  (  QOI_encA  *  )pMyQoi;

				  if  (  !ptr  )  goto  errLabel;
				  //
				  pQe->pf_qdcGetVorbisHeaders  =  (  PF_qdcGetVorbisHeaders  )ptr;

				  //
				  break;
			default:
					goto  errLabel;
	}


	bRet  =  TRUE;
errLabel:
	return  bRet;
 }




  //
  int  CCtxQmc::set_qoi_funcs(  MY_qoi  *  pMyQoi  )
  {
	  //
	  pMyQoi->common.pf_qoi_getPtrProperty  =  qmc_qoi_getPtrProperty;
	  //  2016/12/17
	  pMyQoi->common.pf_qoi_bSetPtrProperty  =  qmc_qoi_bSetPtrProperty;
	  //
	  pMyQoi->pProcInfoCommon  =  this;


	  return  0;
  }




//  2015/07/13
BOOL  CCtxQmc::bUse_FUNCS_for_isCliHelp(  )
{
	return  TRUE;
}

//
 BOOL  CCtxQmc::bUse_sharedObj(  )
 {
	 return  TRUE;
 }



//
int  CCtxQmc::initCapSubWnds1(  unsigned  short  usMaxCnt,  CAP_subWnds  *  p  )
{
	return  ::initCapSubWnds(  usMaxCnt,  p  );
}

//  2015/08/04
BOOL			CCtxQmc::bSupported_shadow_for_tmpMsgr(  )
{
	BOOL  bRet  =  FALSE;

	//
	QY_MC  *  pQyMc  =  (  QY_MC  *  )this->pQyMc;
	if  (  !pQyMc  )  return  FALSE;
	
	//  2015/08/04. 将文件服务器暂时和远程存储同等处理。 这里要开放tmpMsgr的shadow功能
	if  (  bSupported_fileServer(  pQyMc  )  )  {
		bRet  =  TRUE;
	}

	//  2017/08/02, 因为临时组，要开放tmpMsgr
	bRet  =  TRUE;

	//
	return  bRet;
}


int  CCtxQmc::confStarter_requestToSpeak(  HWND  hDlgTalk,  QY_MESSENGER_ID  *  pIdInfo,  AV_stream_simple  *  pAss,  LPCTSTR  talkerDesc,  BOOL  bRequestToSpeak  )
{
	return ::confStarter_requestToSpeak(hDlgTalk,pIdInfo,pAss,talkerDesc,bRequestToSpeak);
}


//
int  CCtxQmc::waitToQuit_isCli(  int  dwTimeInMs,  LPCTSTR  hint  )
{
	return ::waitToQuit_isCli(this,dwTimeInMs,hint);
}

//
int  CCtxQmc::getChosenCamera(TCHAR* webcam_selected, unsigned  int  uiCnt_webcam_selected)
{
	//
#ifdef  __DEBUG__
		//
#if 0
	//if (sm_getChosenCamera(webcam_selected, uiCnt_webcam_selected))  return  -1;
	//return  0;
#endif

#endif

	//
	return  getChosenDevice(mynull, 0, webcam_selected, uiCnt_webcam_selected, mynull, 0, mynull, mynull);
 }
 
//
bool  CCtxQmc::bUse_dx11()
{
	bool  bRet = false;

#ifdef  __DEBUG__
		//return true;// false;
#endif
	//
	//bRet = true;

	//
	return  bRet;
 }


//
int  CCtxQmc::sendConfKey(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint)
{
	//
	return  ::sendConfKey(hDlgTalk, idInfo_to, hint);

}

//
int CCtxQmc::dlgTalk_confStart_pre(HWND  hDlgTalk, bool bConf, bool conf_ucb100k, LPCTSTR  hint)
{
	return  0;
}


//
int CCtxQmc::dlgTalk_confStart_post(HWND  hDlgTalk, LPCTSTR  hint)
{
	//
	chkTasksStatus(&this->status.tasksStatus,_T(""));
	//
	if (this->status.tasksStatus.bTaskExists_av) {
		this->av.bNeedStartChannel_a = true;
		//
		q2PostMsgAndTrigger(mynull, 0, &this->realTimeMediaQ2, _T(""));
		//
		this->av.bNeedStartChannel_v = true;
		//
		q2PostMsgAndTrigger(mynull, 0, &this->mediaQ2, _T(""));
		//
	}

	//
	showInfo_open0(0, 0, _T("dlgTalk_confStart_post called"));

	//
	return  0;
}







