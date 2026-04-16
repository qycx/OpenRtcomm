


#include	"stdafx.h"

#include	<stddef.h>
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>

#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"
#include	"qmcSound_dx.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qmOpenCommon.h"
//#include	"rtspCliHelpPublic.h"
#include	"ctxMcThread.h"
#include	"qmcTaskInfo.h"





 


 //
#if  0
 int  old_doPreTransformTaskVideo(  QY_TRANSFORM  *  pTransform,  MIS_MSG_TASK  *  pMsgTask,  myDRAW_VIDEO_DATA  *  pkts,  CQyMalloc  *  mallocObj_pkts,  int  maxPkts,  int  *  pnPkts,  CTX_mc_pretrans  *  pCtx  )
{
	int						iErr				=	-1;

	MC_VAR_isCli		*	pProcInfo			=	(  MC_VAR_isCli  *  )pTransform->pProcInfo;  
	MSGR_ADDR			*	pAddr				=	pTransform->pAddr_logicalPeer;
	int						iTaskId				=	pTransform->iTaskId;
	AV_TRAN_INFO		*	pTranInfo_unused	=	(  AV_TRAN_INFO  *  )pTransform->pTranInfo_unused;
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pTransform->pTask;

	
	//  2012/03/18
	//QY_qThreadProcInfo_common		
	PRETRANS_procInfo	*	pPreTransformVideo				=	&pTransform->v_preTransThread;
	
	//
	QY_MC				*	pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;
	MIS_CNT				*	pMisCnt				=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
	if  (  !pMisCnt  )  return  -1;
	int						tmpiRet				=	0;
	//  
	char					timeBuf[32]			=	"";
	TCHAR					tHintBuf[256]		=	_T(  ""  );

	//
	IM_CONTENTU			*	pContent			=	(  IM_CONTENTU  *  )pMsgTask->data.buf;
	if  (  pContent->uiType  !=  CONST_imCommType_transferVideoData  )  return  -1;
	TRANSFER_VIDEO_DATA	*	pTransferVideoData	=	&pContent->transferVideoData;

	//  2014/11/11
	TASK_AV_FROM		*	pFrom				=	NULL;
	int  index_pMems_from  =  0;
	int  index_activeMems_from  =  0;

	index_pMems_from  =  pContent->transferVideoData.tmpInternal.param.index_pMems_from;
	index_activeMems_from  =  pContent->transferVideoData.tmpInternal.param.index_activeMems_from;

	//
#if  0
	if  (  pTransform->bMosaicVideo  )  {
		pFrom  =  &pTask->confMosaicTrans.confMosaic_video.taskAvFrom;
		}
	else  {
		  index_pMems_from  =  pContent->transferVideoData.tmpInternal.param.index_pMems_from;	
		  if  (  index_pMems_from  <  0  ||  index_pMems_from  >=  pTask->usCntLimit_mems_from  )  return  -1;
		  pFrom  =  &pTask->pMems_from[index_pMems_from];

		//
		if  (  index_activeMems_from  !=  pContent->transferVideoData.tmpInternal.param.index_activeMems_from  )  return  -1;
		if  (  pTask->ucbVideoConferenceStarter  )  {
			if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTask->usCntLimit_activeMems_from  )  return  -1;
		}
	
	}
#endif
	pFrom  =  getTaskAvFrom(  pTransform,  index_pMems_from,  index_activeMems_from,  _T(  "pretrans"  )  );
	if  (  !pFrom  )  return  -1;

	
	//
	int						i;
	DWORD					curTickCnt			=	GetTickCount(  );	

	TCHAR					where_showInfo[32]	=	_T(  ""  );		_sntprintf(  where_showInfo,  mycountof(  where_showInfo  ),  _T(  "pretransV %d"  ),  pTransform->index_activeMems_from  );

	//  BYTE				*	pData_allocated		=	NULL;

	if  (  !pAddr  )  return  -1;


	//
	if  (  pMsgTask->data.route.debugInfo.debug_myDRAW_VIDEO_DATA.dwTickCnt_start  )  {
		pMsgTask->data.route.debugInfo.debug_myDRAW_VIDEO_DATA.usPreTransInMs  =  curTickCnt  -  pMsgTask->data.route.debugInfo.debug_myDRAW_VIDEO_DATA.dwTickCnt_start;
	}
	if  (  pMsgTask->tStartTime  <  pFrom->tStartTime_task  )  {
		_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s tStartTime < tStartTime_task. skipped."  ),  tHintBuf  );  goto  errLabel;
	}
	if  (  pMsgTask->dwTickCnt_start  )  {	//  2009/03/22
		int  iElapse  =  curTickCnt  -  pMsgTask->dwTickCnt_start;
		if  (  iElapse  >  pProcInfo->cfg.policy.usTimeoutInMsToSwitch  )  {

			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%I64u, %dms, skipped."  ),  pFrom->idInfo.ui64Id,  iElapse  );

			DEBUG_myDRAW_VIDEO_DATA	*	pDebugPkt  =  &pMsgTask->data.route.debugInfo.debug_myDRAW_VIDEO_DATA;
			if  (  pDebugPkt->dwTickCnt_start  )  {
				pDebugPkt->usTransInMs  =  curTickCnt  -  pDebugPkt->dwTickCnt_start;
				_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s tE %d, e %d, p %d, d %d, o %d, tr %d"  ),  tHintBuf,  (  int  )pDebugPkt->usToEncInMs,  (  int  )pDebugPkt->usEncedInMs,  (  int  )pDebugPkt->usPostInMs,  (  int  )pDebugPkt->usToDispatchInMs,  (  int  )pDebugPkt->usOutputInMs,  (  int  )pDebugPkt->usTransInMs  );
			}

			goto  errLabel;
		}
	}

	//  MACRO_setMyStep(  pTransform->video.debugStep,  11  );
	MACRO_setMyStep(  pPreTransformVideo->debugStep,  11  );



		//  check
	if  (  pMsgTask->data.route.idInfo_from.ui64Id  !=  pFrom->idInfo.ui64Id
		||  pTransferVideoData->uiTranNo_openAvDev  !=  pFrom->video.tv_recvd.uiTranNo_openAvDev  )  
	{
		#ifdef  __DEBUG__
				traceLogA(  (char*)  "procTaskVideo: idInfo_from %I64u, videoData.uiTranNo %d !=  pFrom %I64u, %d",  pMsgTask->data.route.idInfo_from.ui64Id,  pTransferVideoData->uiTranNo_openAvDev,  pFrom->idInfo.ui64Id,  pFrom->video.tv_recvd.uiTranNo_openAvDev  );  
		#endif
		goto  errLabel;
	}

	//
	if  (  !pTransferVideoData->usCnt  )  {
		pTransferVideoData->usCnt  =  1;	//  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
		pTransferVideoData->mems[0].uiLen  =  pTransferVideoData->uiLen;
	}
	if  (  pTransferVideoData->usCnt  >  mycountof(  pTransferVideoData->mems  )  )  goto  errLabel;

	//  MACRO_setMyStep(  pTransform->video.debugStep,  31  );
	MACRO_setMyStep(  pPreTransformVideo->debugStep,  31  );


	//if  (  !pTask->ucbVideoConference  )  
	{
		//	
		for  (  i  =  0;  i  <  pTransferVideoData->usCnt;  i  ++  )  {
			 TRANSFER_VIDEO_dataMemHead  *  pMem  =  &pTransferVideoData->mems[i];
		
			 //
			 pFrom->video.usCnt_pkts  ++  ;
			 //  pFrom->video.usCnt_pkts  +=  pTransferVideoData->usCnt;		//  2011/01/26
			 if  (  !pMem->stat.tSelectTime  )  continue;
			 	 
			
			 //
			 if  (  //pFrom->video.tv_recvd.uiTranNo_openAvDev  !=  pTransferVideoData->uiTranNo_openAvDev  ||  
					!pFrom->video.tSelectTime  ||  pFrom->video.tSelectTime  !=  pMem->stat.tSelectTime  )  
			 {
				pTransferVideoData->tmpInternal.result.usRespCode  =  CONST_qyRc_ok;

				_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s tSelectTime changed."  ),  tHintBuf  );

				//
				//pFrom->video.tv_recvd.uiTranNo_openAvDev  =  pTransferVideoData->uiTranNo_openAvDev;
				pFrom->video.tSelectTime  =  (  time_t  )pMem->stat.tSelectTime;
				pFrom->video.dwTickCnt_selectTime  =  curTickCnt;
				//  pFrom->video.usCnt_pkts  =  1;
				pFrom->video.usCnt_pkts  =  pTransferVideoData->usCnt;
				//		
				}
			else  {
				  if  (  pFrom->video.dwTickCnt_selectTime  !=  curTickCnt  )  {
					  pTransferVideoData->tmpInternal.result.fFps  =  (  float  )(  pFrom->video.usCnt_pkts  *  1000.  /  (  curTickCnt  -  pFrom->video.dwTickCnt_selectTime  )  );
				  }

				  pTransferVideoData->tmpInternal.result.usRespCode  =  CONST_qyRc_ok;

			}
			pTransferVideoData->tmpInternal.result.tSelectTime  =  pFrom->video.tSelectTime;	//  ½«ÕâÐ©·¢»Ø¡£2008/12/05
			pTransferVideoData->tmpInternal.result.usCnt_pkts  =  pFrom->video.usCnt_pkts;

			//
			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s, %I64u, %d: recvd.pkts %d, expected. %d"  ),  tHintBuf,  pFrom->idInfo.ui64Id,  pFrom->video.tv_recvd.uiTranNo_openAvDev,  (  long  )pFrom->video.usCnt_pkts,  (  long  )pMem->stat.usCnt_pkts  );
			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s, recvd.fps %.2f, expected. %d"  ),  tHintBuf,  pTransferVideoData->tmpInternal.result.fFps,  (  long  )pMem->stat.usFps  );
			//
			if  (  pMem->stat.usCnt_pkts  ==  (  unsigned  short  )pFrom->video.usCnt_pkts  )  {
					  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s ok."  ),  tHintBuf,  pMem->stat.usFps  );
					}
			else  {
					  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s err"  ),  tHintBuf  );			  
			}			  

			//
			pTransferVideoData->tmpInternal.result.usDiff_pkts  =  pMem->stat.usCnt_pkts  -  pFrom->video.usCnt_pkts;

			//
			
		}
	}
		

	//  MACRO_setMyStep(  pTransform->video.debugStep,  41  );
	MACRO_setStep(  pPreTransformVideo->debugStep,  41  );

#ifdef  __DEBUG__
		if  (  pProcInfo->cfg.debugStatusInfo.ucbPrint_v_in  )  
		{
			 traceLog((TCHAR*)  _T(  "transV: from %I64u, tn %d, usCnt %d, uiLen %d"  ),  pFrom->idInfo.ui64Id,  pMsgTask->uiTranNo,  pTransferVideoData->usCnt,  pTransferVideoData->uiLen  );
		}
#endif
		

	
	//  注意这里的nPkts. 如果是stream需要splitter的话，不能让*pnPkts增加，因为*pnPkts会用来表明有多少个包是分配好内存的。
	//  
	//  2011/12/09
	//  int  &  nPkts  =  *pnPkts;		
	int  nPkts  =  *pnPkts;

	//
	BOOL							bDecompressOk;  
	int								iPos;
	TRANSFER_VIDEO_dataMemHead	*	pMem;

	//  2011/12/08
	myDRAW_VIDEO_DATA			*	pPkt_dec  =  NULL;

	unsigned  int					uiSize_buf  =  0;
	unsigned  int					uiSize_dec  =  0;

	//
	//  2015/10/04. 对共享纹理，不需要为图像数据分配内存
	BOOL  bPkt_sharedTex  =  FALSE;
#if  0
	if  (  pTransform->video.tv.compressor.common.ucCompressors  !=  CONST_videoCompressors_vcm
		&&  pTransform->video.tv.compressor.common.ucCompressors  !=  CONST_videoCompressors_dmo
		&&  pTransform->video.u.qdcObjInfo.var.usPktResType_dec  ==  CONST_pktResType_sharedTex  )
	{
		bPkt_sharedTex  =  TRUE;
	}
#endif
	if  (  isPkt_sharedTex(  pTransform  )  )  {
		bPkt_sharedTex  =  TRUE;
	}

	//
	if  (  !bPkt_sharedTex  )  {
		//
		uiSize_dec  =  M_rgb24SizeImage(  pFrom->video.tv_recvd.vh_decompress.bih.biWidth,  pFrom->video.tv_recvd.vh_decompress.bih.biHeight  );
		//
		if  (  !uiSize_dec  )  {  //  2014/02/26
			uiSize_dec  =  M_rgb24SizeImage(  pTransform->video.tv.vh_decompress.bih.biWidth,  pTransform->video.tv.vh_decompress.bih.biHeight  );
		}
		//  
		if  (  pFrom->video.tv_recvd.compressor.common.ucCompressors  !=  CONST_videoCompressors_stream  )  {
			if  (  !uiSize_dec  )  {
				#ifdef  __DEBUG__
						traceLog((TCHAR*)  _T(  "doPreTransformTaskVideo failed: uiSize_dec err, uiSize_dec is 0"  )  );
				#endif
				goto  errLabel;
			}
		}
		if  (  uiSize_dec  >  pProcInfo->cfg.uiBufSize_myDrawVideoData  )  uiSize_dec  =  pProcInfo->cfg.uiBufSize_myDrawVideoData;
	}

	//
	for  (  iPos  =  0,  i  =  0;  i  <  pTransferVideoData->usCnt;  iPos  =  iPos  +  pTransferVideoData->mems[i].uiLen,  i  ++  )  {
		 pMem  =  &pTransferVideoData->mems[i];

		 //  MACRO_setMyStep(  pTransform->video.debugStep,  51  );
		 MACRO_setStep(  pPreTransformVideo->debugStep,  51  );

		 #if  1  //def  __DEBUG__
		 		 //  2015/01/15
				 if  (  pMem->uiPts  )  {				
					 if  (  !pTransform->v_preTransThread.helpInfo.pts.uiPts_lastRecvd  )  {
						 pTransform->v_preTransThread.helpInfo.pts.uiPts_first  =  pMem->uiPts;						
						 pTransform->v_preTransThread.helpInfo.pts.dwTickCnt_start  =  GetTickCount(  );
						 }
					 else  {
						   TCHAR  tBuf[128];						
						   if  (  pMem->uiPts  !=  pTransform->v_preTransThread.helpInfo.pts.uiPts_lastRecvd  +  1  )  {							
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "pretrans err: pts err. pkt.pts %d, last %d"  ),  pMem->uiPts,  pTransform->v_preTransThread.helpInfo.pts.uiPts_lastRecvd  );								
							   showInfo_open0(  0,  0,  tBuf  );								  
							   //  2015/02/20							  
						   }						  							  
						   //
						   #ifdef  __DEBUG__
								   #if  0
										_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "pretrans: pts %d"  ),  pMem->uiPts  );
										showInfo_open0(  0,  0,  tBuf  );
								   #endif
						   #endif
					 }											
					 pTransform->v_preTransThread.helpInfo.pts.uiPts_lastRecvd  =  pMem->uiPts;											 
				 }					
		 #endif
					
		 //
		 if  (  iPos  +  pTransferVideoData->mems[i].uiLen  >  pTransferVideoData->uiLen  )  {
			 #ifdef  __DEBUG__
					 traceLogA(  (char*)  "procTaskVideo: Êý¾Ý³¤¶È²»¶Ô"  );
			 #endif
			 goto  errLabel;
		 }
		 if  (  !pMem->uiLen  )  {
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "transformTaskVideo warning: pMem->uiLen is 0, skipped"  )  );
			 continue;
		 }
		 if  (  pMem->uiTranNo_openAvDev
			 &&  pMem->uiTranNo_openAvDev  !=  pFrom->video.tv_recvd.uiTranNo_openAvDev  )  
		 {		//  2012/01/09
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "transformTaskVideo warning: pMem->tn %d != pFrom->tn %d, skipped"  ),  pMem->uiTranNo_openAvDev,  pFrom->video.tv_recvd.uiTranNo_openAvDev  );
			 continue;
		 }

		 //
		 bDecompressOk  =  FALSE;

		 if  (  pTransferVideoData->mems[i].uiSampleTimeInMs  )  {
			 int  index_dmo  =  0;	
#if  0
			 if  (  pFrom->ucbVideoConferenceStarter  )  index_dmo  =  pTransferVideoData->mems[i].usIndex;
#endif
			 if  (  index_dmo  <  0  ||  index_dmo  >=  mycountof(  pFrom->iDiffInMs_tStartAudios  )  )  goto  errLabel;

			 pTransferVideoData->mems[i].uiSampleTimeInMs  =  (  int  )pTransferVideoData->mems[i].uiSampleTimeInMs  -  pFrom->iDiffInMs_tStartAudios[index_dmo];	//  2009/05/26

			 #ifdef  __DEBUG__
					 #if  0
						  //  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "transformTaskVideo: decompress %d -> %d"  ),  pTransform->video.vh_compress.bih.biSizeImage,  pTransform->video.vh_decompress.bih.biSizeImage  );
						  traceLogA(  (char*)  "transformV: iSampleTimeInMs %d",  pTransferVideoData->mems[i].uiSampleTimeInMs  );
					 #endif
			 #endif
		 }

		 //  
		 if  (  bUseSplitter(  pFrom->video.tv_recvd.compressor.common.ucCompressors,  pFrom->video.tv_recvd.vh_stream.dwFourcc  )  )  {

			 _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "doPretrans failed, bUseSpl is true"  )  );
			 goto  errLabel;

			 //
			 continue;
		 }


		 //
		 if  (  nPkts  >=  maxPkts  )  goto  errLabel;
		 pPkt_dec  =  &pkts[nPkts];
		 memset(  pPkt_dec,  0,  sizeof(  myDRAW_VIDEO_DATA  )  );
		 //
		 memcpy(  &pPkt_dec->head,  pMem,  sizeof(  pPkt_dec->head  )  );
		 //
		 pPkt_dec->decInfo.index_pMems_from  =  index_pMems_from;
		 //  2016/12/27
		 //  2014/09/04
		 pPkt_dec->uiTaskType  =  pTransform->uiTaskType;	//  2014/10/01
		 //  2014/10/12
		 if  (  pTransform->uiTaskType  ==  CONST_imTaskType_viewDynBmp  )  {
			 //pPkt_dec->decInfo.dynBmp.usIndex_obj  =  pFrom->video.dynBmp.usIndex_obj;
			 MIS_MSG_TASK  *  pMsgTask_req  =  (  MIS_MSG_TASK  *  )pTransform->pMsgTask;
			 if  (  pMsgTask_req  )  {
				 IM_CONTENTU  *  pContent_req  =  M_getMsgContent(  pMsgTask_req->ucFlg,  &pMsgTask_req->data  );
				 switch  (  pContent_req->uiType  )  {
						 case  CONST_imCommType_transferAvInfo:
							 pPkt_dec->decInfo.dynBmp.resObj.uiObjType  =  pContent_req->transferAvInfo.viewDynBmp.resObj.uiObjType;
							 pPkt_dec->decInfo.dynBmp.resObj.usIndex_obj  =  pContent_req->transferAvInfo.viewDynBmp.resObj.usIndex_obj;
							   pPkt_dec->decInfo.dynBmp.idInfo.ui64Id  =  pMsgTask_req->data.route.idInfo_to.ui64Id;
							   //
							   //  2015/11/08
							   if  (  pPkt_dec->decInfo.dynBmp.resObj.uiObjType  ==  CONST_objType_screen  )  {
								   pPkt_dec->decInfo.ucbUnresizable  =  TRUE;
							   }
							   break;
						 default:
								break;
				 }				 
			 }
		 }
		 //  2015/10/23
		 if  (  isAvFlg_unresizable(  pFrom->taskAvProps.v.ucAvFlg  )  )  {
			 pPkt_dec->decInfo.ucbUnresizable  =  TRUE;
		 }
		 //
		 memcpy(  &pPkt_dec->debugInfo,  &pMsgTask->data.route.debugInfo.debug_myDRAW_VIDEO_DATA,  sizeof(  pPkt_dec->debugInfo  )  );
		 //  2015/02/24
		 pPkt_dec->debugInfo.dwTickCnt_proc_io_read  =  pMsgTask->dwTickCnt_start;
		 //
		 pPkt_dec->debugInfo.dwTickCnt_doPretrans  =  GetTickCount(  );
		 //  2015/09/05
		 pPkt_dec->debugInfo.uiTranNo_msgTask  =  pMsgTask->uiTranNo;
		 //  2014/03/26
		 M_set_pktId_alloc(  pPkt_dec  );
		 //
		 pPkt_dec->uiSize_dec  =  uiSize_dec;
		 pPkt_dec->uiLen_enc  =  pMem->uiLen;
		 uiSize_buf  =  pPkt_dec->uiSize_dec  +  pPkt_dec->uiOffset_enc  +  pPkt_dec->uiLen_enc;
		 //
		 pPkt_dec->head.uiLen  =  uiSize_buf;
		 //
		 if  (  mallocObj_pkts[nPkts].get(  &pPkt_dec->memory  )  )  {
			 if  (  !mallocObj_pkts[nPkts].mallocf(  uiSize_buf  )  )  {
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doPreTransV failed: malloc failed,uiSize_buf%d"  ),  uiSize_buf  );
				 //  2014/05/12
				 pCtx->status.errFlgs.bErrExists_mallocfFailed  =  TRUE;
				 //
				 goto  errLabel;
			 }
			 if  (  mallocObj_pkts[nPkts].get(  &pPkt_dec->memory  )  )  goto  errLabel;
		 }
		 if  (  pPkt_dec->memory.uiBufSize  !=  uiSize_buf  )  goto  errLabel;
		 memcpy(  pPkt_dec->memory.m_pBuf  +  pPkt_dec->uiSize_dec  +  pPkt_dec->uiOffset_enc,  pTransferVideoData->buf  +  iPos,  pPkt_dec->uiLen_enc  );
		 nPkts  ++  ;
	}


	//  2014/03/04	
	if  (  nPkts  )  {
		if  (  bUseSplitter(  pFrom->video.tv_recvd.compressor.common.ucCompressors, pFrom->video.tv_recvd.vh_stream.dwFourcc  )  )  {
			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "doPretrans failed, bUseSpl is true"  )  );
			goto  errLabel;
		}
	}

	//
	*pnPkts  =  nPkts;


	//
	iErr  =  0;

errLabel:

	//  MACRO_setMyStep(  pTransform->video.debugStep,  181  );
	MACRO_setStep(  pPreTransformVideo->debugStep,  181  );


	//  
	if  (  iErr  ||  tHintBuf[0]  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  where_showInfo,  _T(  ""  ),  _T(  "tn %d, %s. %s"  ),  pMsgTask->uiTranNo,  (  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  )  ),  tHintBuf  );
		#ifdef  __DEBUG__
				//traceLog((TCHAR*)  _T(  "transformTaskVideo: %s"  ),  tHintBuf  );
		#endif
	}


	if  (  !iErr  )  {
		//if  (  !pTask->ucbVideoConference  )  
		{
			mySendAvResp(  pProcInfo,  pMsgTask,  pCtx->pMsgBuf  );
		}
	}

	
	//  MACRO_setMyStep(  pTransform->video.debugStep,  199  );
	MACRO_setStep(  pPreTransformVideo->debugStep,  198  );


	return  iErr;

	return  iErr;
 }
#endif

//
 int  doPreTransformTaskVideo(  QY_TRANSFORM  *  pTransform,  MIS_MSG_TASK  *  pMsgTask,  myDRAW_VIDEO_DATA  *  pkts,  CQyMalloc  *  mallocObj_pkts,  int  maxPkts,  int  *  pnPkts,  CTX_mc_pretrans  *  pCtx  )
{
	int						iErr				=	-1;

	MC_VAR_isCli		*	pProcInfo			=	(  MC_VAR_isCli  *  )pTransform->pProcInfo;  
	MSGR_ADDR			*	pAddr				=	pTransform->pAddr_logicalPeer;
	int						iTaskId				=	pTransform->iTaskId;
	AV_TRAN_INFO		*	pTranInfo_unused	=	(  AV_TRAN_INFO  *  )pTransform->pTranInfo_unused;
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pTransform->pTask;

	//
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

	
	//  2012/03/18
	//QY_qThreadProcInfo_common		
	PRETRANS_procInfo	*	pPreTransformVideo				=	&pTransform->v_preTransThread;
	
	//
	QY_MC				*	pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;
	MIS_CNT				*	pMisCnt				=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
	if  (  !pMisCnt  )  return  -1;
	int						tmpiRet				=	0;
	//  
	char					timeBuf[32]			=	"";
	TCHAR					tHintBuf[256]		=	_T(  ""  );

	//
	IM_CONTENTU			*	pContent			=	(  IM_CONTENTU  *  )pMsgTask->data.buf;
	if  (  pContent->uiType  !=  CONST_imCommType_transferVideoData  )  return  -1;
	TRANSFER_VIDEO_DATA	*	pTransferVideoData	=	&pContent->transferVideoData;

	//  2014/11/11
	//TASK_AV_FROM		*	pFrom				=	NULL;
	int  index_pMems_from  =  0;
	int  index_activeMems_from  =  0;

	index_pMems_from  =  pContent->transferVideoData.tmpInternal.param.index_pMems_from;
	index_activeMems_from  =  pContent->transferVideoData.tmpInternal.param.index_activeMems_from;

	//
#if  0
	pFrom  =  getTaskAvFrom(  pTransform,  index_pMems_from,  index_activeMems_from,  _T(  "pretrans"  )  );
	if  (  !pFrom  )  return  -1;
#endif
	if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTc->videoConference.usCntLimit_activeMems_from  ) return  -1;
	DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pTc->videoConference.activeMems_from[index_activeMems_from];
	
	//
	int						i;
	DWORD					curTickCnt			=	myGetTickCount(  NULL  );	

	TCHAR					where_showInfo[32]	=	_T(  ""  );		_sntprintf(  where_showInfo,  mycountof(  where_showInfo  ),  _T(  "pretransV %d"  ),  pTransform->index_activeMems_from  );

	//  BYTE				*	pData_allocated		=	NULL;

	if  (  !pAddr  )  return  -1;

	//
	pActiveMem_from->dwLastTickCnt_vData  =  curTickCnt;

	//
	if  (  pMsgTask->data.route.debugInfo.debug_myDRAW_VIDEO_DATA.dwTickCnt_start  )  {
		pMsgTask->data.route.debugInfo.debug_myDRAW_VIDEO_DATA.usPreTransInMs  =  curTickCnt  -  pMsgTask->data.route.debugInfo.debug_myDRAW_VIDEO_DATA.dwTickCnt_start;
	}
#if  0
	if  (  pMsgTask->tStartTime  <  pFrom->tStartTime_task  )  {
		_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s tStartTime < tStartTime_task. skipped."  ),  tHintBuf  );  goto  errLabel;
	}
#endif

	//
#if  0
	if  (  pMsgTask->dwTickCnt_start  )  {	//  2009/03/22
		int  iElapse  =  curTickCnt  -  pMsgTask->dwTickCnt_start;
		if  (  iElapse  >  pProcInfo->cfg.policy.usTimeoutInMsToSwitch  )  {

			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%I64u, %dms, skipped."  ),  pActiveMem_from->avStream.idInfo.ui64Id,  iElapse  );

			DEBUG_myDRAW_VIDEO_DATA	*	pDebugPkt  =  &pMsgTask->data.route.debugInfo.debug_myDRAW_VIDEO_DATA;
			if  (  pDebugPkt->dwTickCnt_start  )  {
				pDebugPkt->usTransInMs  =  curTickCnt  -  pDebugPkt->dwTickCnt_start;
				_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s tE %d, e %d, p %d, d %d, o %d, tr %d"  ),  tHintBuf,  (  int  )pDebugPkt->usToEncInMs,  (  int  )pDebugPkt->usEncedInMs,  (  int  )pDebugPkt->usPostInMs,  (  int  )pDebugPkt->usToDispatchInMs,  (  int  )pDebugPkt->usOutputInMs,  (  int  )pDebugPkt->usTransInMs  );
			}

			goto  errLabel;
		}
	}
#endif

	//  MACRO_setMyStep(  pTransform->video.debugStep,  11  );
	MACRO_setMyStep(  pPreTransformVideo->debugStep,  11  );



		//  check
	if  (  pMsgTask->data.route.idInfo_from.ui64Id  !=  pActiveMem_from->avStream.idInfo.ui64Id
		||  pTransferVideoData->uiTranNo_openAvDev  !=  pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev  )  
	{
		#ifdef  __DEBUG__
				traceLogA(  (char*)  "procTaskVideo: idInfo_from %I64u, videoData.uiTranNo %d !=  pFrom %I64u, %d",  pMsgTask->data.route.idInfo_from.ui64Id,  pTransferVideoData->uiTranNo_openAvDev,  pActiveMem_from->avStream.idInfo.ui64Id,  pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev  );  
		#endif
		goto  errLabel;
	}

	//
	if  (  !pTransferVideoData->usCnt  )  {
		pTransferVideoData->usCnt  =  1;	//  ¶ÔÀÏµÄÊý¾Ý°ü£¬Õâ¸öusCntÃ»Ìî£¬°üº¬Ò»¸öÊý¾Ý
		pTransferVideoData->mems[0].uiLen  =  pTransferVideoData->uiLen;
	}
	if  (  pTransferVideoData->usCnt  >  mycountof(  pTransferVideoData->mems  )  )  goto  errLabel;

	//  MACRO_setMyStep(  pTransform->video.debugStep,  31  );
	MACRO_setMyStep(  pPreTransformVideo->debugStep,  31  );


#if  0
	//if  (  !pTask->ucbVideoConference  )  
	{
		//	
		for  (  i  =  0;  i  <  pTransferVideoData->usCnt;  i  ++  )  {
			 TRANSFER_VIDEO_dataMemHead  *  pMem  =  &pTransferVideoData->mems[i];
		
			 //
			 pFrom->video.usCnt_pkts  ++  ;
			 //  pFrom->video.usCnt_pkts  +=  pTransferVideoData->usCnt;		//  2011/01/26
			 if  (  !pMem->stat.tSelectTime  )  continue;
			 	 
			
			 //
			 if  (  //pFrom->video.tv_recvd.uiTranNo_openAvDev  !=  pTransferVideoData->uiTranNo_openAvDev  ||  
					!pFrom->video.tSelectTime  ||  pFrom->video.tSelectTime  !=  pMem->stat.tSelectTime  )  
			 {
				pTransferVideoData->tmpInternal.result.usRespCode  =  CONST_qyRc_ok;

				_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s tSelectTime changed."  ),  tHintBuf  );

				//
				//pFrom->video.tv_recvd.uiTranNo_openAvDev  =  pTransferVideoData->uiTranNo_openAvDev;
				pFrom->video.tSelectTime  =  (  time_t  )pMem->stat.tSelectTime;
				pFrom->video.dwTickCnt_selectTime  =  curTickCnt;
				//  pFrom->video.usCnt_pkts  =  1;
				pFrom->video.usCnt_pkts  =  pTransferVideoData->usCnt;
				//		
				}
			else  {
				  if  (  pFrom->video.dwTickCnt_selectTime  !=  curTickCnt  )  {
					  pTransferVideoData->tmpInternal.result.fFps  =  (  float  )(  pFrom->video.usCnt_pkts  *  1000.  /  (  curTickCnt  -  pFrom->video.dwTickCnt_selectTime  )  );
				  }

				  pTransferVideoData->tmpInternal.result.usRespCode  =  CONST_qyRc_ok;

			}
			pTransferVideoData->tmpInternal.result.tSelectTime  =  pFrom->video.tSelectTime;	//  ½«ÕâÐ©·¢»Ø¡£2008/12/05
			pTransferVideoData->tmpInternal.result.usCnt_pkts  =  pFrom->video.usCnt_pkts;

			//
			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s, %I64u, %d: recvd.pkts %d, expected. %d"  ),  tHintBuf,  pFrom->idInfo.ui64Id,  pFrom->video.tv_recvd.uiTranNo_openAvDev,  (  long  )pFrom->video.usCnt_pkts,  (  long  )pMem->stat.usCnt_pkts  );
			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s, recvd.fps %.2f, expected. %d"  ),  tHintBuf,  pTransferVideoData->tmpInternal.result.fFps,  (  long  )pMem->stat.usFps  );
			//
			if  (  pMem->stat.usCnt_pkts  ==  (  unsigned  short  )pFrom->video.usCnt_pkts  )  {
					  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s ok."  ),  tHintBuf,  pMem->stat.usFps  );
					}
			else  {
					  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s err"  ),  tHintBuf  );			  
			}			  

			//
			pTransferVideoData->tmpInternal.result.usDiff_pkts  =  pMem->stat.usCnt_pkts  -  pFrom->video.usCnt_pkts;

			//
			
		}
	}
#endif
		

	//  MACRO_setMyStep(  pTransform->video.debugStep,  41  );
	MACRO_setStep(  pPreTransformVideo->debugStep,  41  );

#ifdef  __DEBUG__
		if  (  pProcInfo->cfg.debugStatusInfo.ucbPrint_v_in  )  
		{
			 //traceLog((TCHAR*)  _T(  "transV: from %I64u, tn %d, usCnt %d, uiLen %d"  ),  pActiveMem_from->avStream.idInfo.ui64Id,  pMsgTask->uiTranNo,  pTransferVideoData->usCnt,  pTransferVideoData->uiLen  );

			 //
			 TCHAR  tBuf[128];
			 for (i = 0; i < pTransferVideoData->usCnt; i++) {
				 _sntprintf(tBuf, mycountof(tBuf), _T("%I64u,%d: pts %d"), pActiveMem_from->avStream.idInfo.ui64Id, pTransferVideoData->uiTranNo_openAvDev, pTransferVideoData->mems[i].uiPts);
				 showInfo_open0(0, _T("preTransV"), tBuf);
			 }
		}
#endif
		

	
	//  注意这里的nPkts. 如果是stream需要splitter的话，不能让*pnPkts增加，因为*pnPkts会用来表明有多少个包是分配好内存的。
	//  
	//  2011/12/09
	//  int  &  nPkts  =  *pnPkts;		
	int  nPkts  =  *pnPkts;

	//
	BOOL							bDecompressOk;  
	int								iPos;
	TRANSFER_VIDEO_dataMemHead	*	pMem;

	//  2011/12/08
	myDRAW_VIDEO_DATA			*	pPkt_dec  =  NULL;

	unsigned  int					uiSize_buf  =  0;
	unsigned  int					uiSize_dec  =  0;

	//
	//  2015/10/04. 对共享纹理，不需要为图像数据分配内存
	BOOL  bPkt_sharedTex  =  FALSE;
#if  0
	if  (  pTransform->video.tv.compressor.common.ucCompressors  !=  CONST_videoCompressors_vcm
		&&  pTransform->video.tv.compressor.common.ucCompressors  !=  CONST_videoCompressors_dmo
		&&  pTransform->video.u.qdcObjInfo.var.usPktResType_dec  ==  CONST_pktResType_sharedTex  )
	{
		bPkt_sharedTex  =  TRUE;
	}
#endif
	if  (  isPkt_sharedTex(  pTransform  )  )  {
		bPkt_sharedTex  =  TRUE;
	}

	//
#ifdef  __DEBUG__
#if 0
	if (!bPkt_sharedTex) {
		showInfo_open0(0, 0, _T("not sharedTex"));
	}
	else {
		showInfo_open0(0, 0, _T("sharedTex"));
	}
#endif
#endif


	//
	if  (  !bPkt_sharedTex  )  {
		//
		uiSize_dec  =  M_rgb24SizeImage(  pActiveMem_from->avStream.obj.tranInfo.video.vh_decompress.bih.biWidth,  pActiveMem_from->avStream.obj.tranInfo.video.vh_decompress.bih.biHeight  );
		//
		if  (  !uiSize_dec  )  {  //  2014/02/26
			uiSize_dec  =  M_rgb24SizeImage(  pTransform->video.tv.vh_decompress.bih.biWidth,  pTransform->video.tv.vh_decompress.bih.biHeight  );
		}
		//  
		if  (  pActiveMem_from->avStream.obj.tranInfo.video.compressor.common.ucCompressors  !=  CONST_videoCompressors_stream  )  {
			if  (  !uiSize_dec  )  {
				#ifdef  __DEBUG__
						traceLog((TCHAR*)  _T(  "doPreTransformTaskVideo failed: uiSize_dec err, uiSize_dec is 0"  )  );
				#endif
				goto  errLabel;
			}
		}
		if  (  uiSize_dec  >  pProcInfo->cfg.uiBufSize_myDrawVideoData  )  uiSize_dec  =  pProcInfo->cfg.uiBufSize_myDrawVideoData;
	}

	//
	for  (  iPos  =  0,  i  =  0;  i  <  pTransferVideoData->usCnt;  iPos  =  iPos  +  pTransferVideoData->mems[i].uiLen,  i  ++  )  {
		 pMem  =  &pTransferVideoData->mems[i];

		 //  MACRO_setMyStep(  pTransform->video.debugStep,  51  );
		 MACRO_setStep(  pPreTransformVideo->debugStep,  51  );

		 #if  1  //def  __DEBUG__
		 		 //  2015/01/15
				 if  (  pMem->uiPts  )  {				
					 if  (  !pTransform->v_preTransThread.helpInfo.pts.uiPts_lastRecvd  )  {
						 pTransform->v_preTransThread.helpInfo.pts.uiPts_first  =  pMem->uiPts;						
						 pTransform->v_preTransThread.helpInfo.pts.dwTickCnt_start  =  GetTickCount(  );
						 }
					 else  {
						   TCHAR  tBuf[128];						
						   if  (  pMem->uiPts  !=  pTransform->v_preTransThread.helpInfo.pts.uiPts_lastRecvd  +  1  )  {							
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "pretrans err: pts err. pkt.pts %d, last %d"  ),  pMem->uiPts,  pTransform->v_preTransThread.helpInfo.pts.uiPts_lastRecvd  );								
							   showInfo_open0(  0,  0,  tBuf  );								  
							   //  2015/02/20							  
						   }						  							  
						   //
						   #ifdef  __DEBUG__
								   #if  0
										_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "pretrans: pts %d"  ),  pMem->uiPts  );
										showInfo_open0(  0,  0,  tBuf  );
								   #endif
						   #endif
					 }											
					 pTransform->v_preTransThread.helpInfo.pts.uiPts_lastRecvd  =  pMem->uiPts;											 
				 }					
		 #endif
					
		 //
		 if  (  iPos  +  pTransferVideoData->mems[i].uiLen  >  pTransferVideoData->uiLen  )  {
			 #ifdef  __DEBUG__
					 traceLogA(  (char*)  "procTaskVideo: Êý¾Ý³¤¶È²»¶Ô"  );
			 #endif
			 goto  errLabel;
		 }
		 if  (  !pMem->uiLen  )  {
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "transformTaskVideo warning: pMem->uiLen is 0, skipped"  )  );
			 continue;
		 }
		 if  (  pMem->uiTranNo_openAvDev
			 &&  pMem->uiTranNo_openAvDev  !=  pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev  )  
		 {		//  2012/01/09
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "transformTaskVideo warning: pMem->tn %d != pFrom->tn %d, skipped"  ),  pMem->uiTranNo_openAvDev,  pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev  );
			 continue;
		 }

		 //
		 bDecompressOk  =  FALSE;

		 if  (  pTransferVideoData->mems[i].uiSampleTimeInMs  )  {
			 int  index_dmo  =  0;	
#if  0
			 if  (  pFrom->ucbVideoConferenceStarter  )  index_dmo  =  pTransferVideoData->mems[i].usIndex;
#endif
			 //if  (  index_dmo  <  0  ||  index_dmo  >=  mycountof(  pFrom->iDiffInMs_tStartAudios  )  )  goto  errLabel;

			 pTransferVideoData->mems[i].uiSampleTimeInMs  =  (  int  )pTransferVideoData->mems[i].uiSampleTimeInMs  -  0;//pFrom->iDiffInMs_tStartAudios[index_dmo];	//  2009/05/26

			 #ifdef  __DEBUG__
					 #if  0
						  //  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "transformTaskVideo: decompress %d -> %d"  ),  pTransform->video.vh_compress.bih.biSizeImage,  pTransform->video.vh_decompress.bih.biSizeImage  );
						  traceLogA(  (char*)  "transformV: iSampleTimeInMs %d",  pTransferVideoData->mems[i].uiSampleTimeInMs  );
					 #endif
			 #endif
		 }

		 //  
		 if  (  bUseSplitter(  pActiveMem_from->avStream.obj.tranInfo.video.compressor.common.ucCompressors,  pActiveMem_from->avStream.obj.tranInfo.video.vh_stream.dwFourcc  )  )  {

			 _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "doPretrans failed, bUseSpl is true"  )  );
			 goto  errLabel;

			 //
			 continue;
		 }


		 //
		 if  (  nPkts  >=  maxPkts  )  goto  errLabel;
		 pPkt_dec  =  &pkts[nPkts];
		 memset(  pPkt_dec,  0,  sizeof(  myDRAW_VIDEO_DATA  )  );
		 //
		 memcpy(  &pPkt_dec->head,  pMem,  sizeof(  pPkt_dec->head  )  );
		 //
		 pPkt_dec->decInfo.index_pMems_from  =  index_pMems_from;
		 //  2016/12/27
		 //  2014/09/04
		 pPkt_dec->uiTaskType  =  pTransform->uiTaskType;	//  2014/10/01
		 //  2014/10/12
		 if  (  pTransform->uiTaskType  ==  CONST_imTaskType_viewDynBmp  )  {
			 //pPkt_dec->decInfo.dynBmp.usIndex_obj  =  pFrom->video.dynBmp.usIndex_obj;
			 MIS_MSG_TASK  *  pMsgTask_req  =  (  MIS_MSG_TASK  *  )pTransform->pMsgTask;
			 if  (  pMsgTask_req  )  {
				 IM_CONTENTU  *  pContent_req  =  M_getMsgContent(  pMsgTask_req->ucFlg,  &pMsgTask_req->data  );
				 switch  (  pContent_req->uiType  )  {
						 case  CONST_imCommType_transferAvInfo:
							 pPkt_dec->decInfo.dynBmp.resObj.uiObjType  =  pContent_req->transferAvInfo.ass.resObj.uiObjType;
							 pPkt_dec->decInfo.dynBmp.resObj.usIndex_obj  =  pContent_req->transferAvInfo.ass.resObj.usIndex_obj;
							   pPkt_dec->decInfo.dynBmp.idInfo.ui64Id  =  pMsgTask_req->data.route.idInfo_to.ui64Id;
							   //
							   //  2015/11/08
							   if  (  pPkt_dec->decInfo.dynBmp.resObj.uiObjType  ==  CONST_objType_screen  )  {
								   pPkt_dec->decInfo.ucbUnresizable  =  TRUE;
							   }
							   break;
						 default:
								break;
				 }				 
			 }
		 }
		 //  2015/10/23
		 if  (  isAvFlg_unresizable(  pActiveMem_from->avStream.obj.tranInfo.taskAvProps.v.ucAvFlg  )  )  {
			 pPkt_dec->decInfo.ucbUnresizable  =  TRUE;
		 }
		 //
		 memcpy(  &pPkt_dec->debugInfo,  &pMsgTask->data.route.debugInfo.debug_myDRAW_VIDEO_DATA,  sizeof(  pPkt_dec->debugInfo  )  );
		 //  2015/02/24
		 pPkt_dec->debugInfo.dwTickCnt_proc_io_read  =  pMsgTask->dwTickCnt_start;
		 //
		 pPkt_dec->debugInfo.dwTickCnt_doPretrans  =  GetTickCount(  );
		 //  2015/09/05
		 pPkt_dec->debugInfo.uiTranNo_msgTask  =  pMsgTask->uiTranNo;
		 //  2014/03/26
		 M_set_pktId_alloc(  pPkt_dec  );
		 //
		 pPkt_dec->uiSize_dec  =  uiSize_dec;
		 pPkt_dec->uiLen_enc  =  pMem->uiLen;
		 uiSize_buf  =  pPkt_dec->uiSize_dec  +  pPkt_dec->uiOffset_enc  +  pPkt_dec->uiLen_enc;
		 //
		 pPkt_dec->head.uiLen  =  uiSize_buf;
		 //
		 if  (  mallocObj_pkts[nPkts].get(  &pPkt_dec->memory  )  )  {
			 if  (  !mallocObj_pkts[nPkts].mallocf(  uiSize_buf  )  )  {
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doPreTransV failed: malloc failed,uiSize_buf%d"  ),  uiSize_buf  );
				 //  2014/05/12
				 pCtx->status.errFlgs.bErrExists_mallocfFailed  =  TRUE;
				 //
				 goto  errLabel;
			 }
			 if  (  mallocObj_pkts[nPkts].get(  &pPkt_dec->memory  )  )  goto  errLabel;
		 }
		 if  (  pPkt_dec->memory.uiBufSize  !=  uiSize_buf  )  goto  errLabel;
		 memcpy(  pPkt_dec->memory.m_pBuf  +  pPkt_dec->uiSize_dec  +  pPkt_dec->uiOffset_enc,  pTransferVideoData->buf  +  iPos,  pPkt_dec->uiLen_enc  );
		 nPkts  ++  ;
	}


	//  2014/03/04	
	if  (  nPkts  )  {
		if  (  bUseSplitter(  pActiveMem_from->avStream.obj.tranInfo.video.compressor.common.ucCompressors, pActiveMem_from->avStream.obj.tranInfo.video.vh_stream.dwFourcc  )  )  {
			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "doPretrans failed, bUseSpl is true"  )  );
			goto  errLabel;
		}
	}

	//
	*pnPkts  =  nPkts;


	//
	iErr  =  0;

errLabel:

	//  MACRO_setMyStep(  pTransform->video.debugStep,  181  );
	MACRO_setStep(  pPreTransformVideo->debugStep,  181  );


	//  
	if  (  iErr  ||  tHintBuf[0]  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  where_showInfo,  _T(  ""  ),  _T(  "tn %d, %s. %s"  ),  pMsgTask->uiTranNo,  (  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  )  ),  tHintBuf  );
		#ifdef  __DEBUG__
				//traceLog((TCHAR*)  _T(  "transformTaskVideo: %s"  ),  tHintBuf  );
		#endif
	}


	if  (  !iErr  )  {
		//if  (  !pTask->ucbVideoConference  )  
		{
			mySendAvResp(  pProcInfo,  pMsgTask,  pCtx->pMsgBuf  );
		}
	}

	
	//  MACRO_setMyStep(  pTransform->video.debugStep,  199  );
	MACRO_setStep(  pPreTransformVideo->debugStep,  198  );


	return  iErr;

	return  iErr;
 }




 //
 extern "C" DWORD WINAPI mcThreadProc_preTransformVideo( LPVOID lpParameter )
{
	 int								iErr						=	-1;

	 QY_TRANSFORM					*	pTransform					=	(  QY_TRANSFORM  *  )lpParameter;
	 if  (  !pTransform  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo					=	(  MC_VAR_isCli  *  )pTransform->pProcInfo;
	 if (  !pProcInfo  )  return  -1;	 
	 PROC_TASK_AV					*	pTask						=	(  PROC_TASK_AV  *  )pTransform->pTask;
	 if  (  !pTask  )  return  -1;

	 //QY_qThreadProcInfo_common
	 PRETRANS_procInfo  *	pPreTransformVideo				=	&pTransform->v_preTransThread;

	 //
	 QY_MC							*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;
	 DYN_LIB_DX						*	pDynLib						=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	 //  int								i;

	 CQyMalloc							mallocObj_msgs;
	 MIS_MSGU						*	msgs							=	NULL;

	 MIS_MSGU						*	pMsgs[CONST_pMsgs_preTransformVideo];
	 int								msgLens[CONST_pMsgs_preTransformVideo];

	 int								maxMsgs							=	CONST_pMsgs_preTransformVideo;			//  一次最多处理的包数。
	 int								nMsgs;
	 int								i;

	 IM_CONTENTU					*	pContent						=	NULL;

	 #define		DEFAULT_dwToInMs		5000
	 DWORD								dwToInMs						=	DEFAULT_dwToInMs;

	 DWORD								dwTickCnt_lastVideoData			=	GetTickCount(  );;						// 

	 //CQyMalloc							mallocObj_pPkt_dec;

	 CQyMalloc							mallocObj_pMsgBuf;
	 MIS_MSGU						*	pMsgBuf							=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsgBuf  )  return  -1;

	 //
#if  0
	 BUF_pretrans						buf_pretrans;
	 memset(  &buf_pretrans,  0,  sizeof(  buf_pretrans  )  );
#endif

	 //
	 myDRAW_VIDEO_DATA					pkts[CONST_pkts_preTransformVideo];
	 int								nPkts							=	0;

	 BOOL								bPktsRedirected;

	 CQyCoInit							coInit;		//  2010/06/07

	 CTX_mc_pretrans					ctx;		//  2014/03/07

	 //
	 memset(  &ctx,  0,  sizeof(  ctx  )  );

	 traceLogA(  (char*)  "mcThreadProc_transformVideo enters"  );
	 	 
	 MACRO_setStep(  pPreTransformVideo->debugStep,  CONST_threadStep_start  );
	 

	 //  2014/05/08
	 _sntprintf(  pPreTransformVideo->debugStep.showInfo.tWhere,  mycountof(  pPreTransformVideo->debugStep.showInfo.tWhere  ),  _T(  "pretransV %d:%d"  ),  pTransform->iTaskId,  pTransform->index_activeMems_from  );
	 pPreTransformVideo->debugStep.showInfo.uiStep  =  0;

	 //
#if  0
	 if  (  initGenericQ(  &pProcInfo->cfg.dynBmpQ,  mymalloc,  0,  0,  myfree,  0,  &ctx.streamDataQ  )  )  goto  errLabel;
	 ctx.bInited_streamDataQ  =  TRUE;
	 //
	 ctx.pBUF_pretrans  =  &buf_pretrans;
#endif
	 //
	 ctx.pMsgBuf  =  pMsgBuf;

	 //
	 pPreTransformVideo->bRunning  =  TRUE;
	 //  memset(  &pPreTransformVideo->m_var,  0,  sizeof(  pPreTransformVideo->m_var  )  );

#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "Note: 这里最好能根据情况，将maxMsgs自动调整，对每个transform,分配10个misMsgU, 是很浪费的 "  )  );
#endif

	 if  (  !(  msgs  =  (  MIS_MSGU  *  )mallocObj_msgs.mallocf(  CONST_iAllocType_longTimeMsg,  maxMsgs  *  sizeof(  MIS_MSGU  )  )  )  )  {
		 iErr  =  -100;
		 goto  errLabel;
	 }
	 for  (  i  =  0;  i  <  maxMsgs;  i  ++  )  {
		  pMsgs[i]  =  &msgs[i];
	 }
	 //
	 if  (  pTask->ucbVideoConferenceStarter  )  {
		 //  if  (  !(  pPreTransformVideo->pMsgTask_toCompress_videoConference  =  (  MIS_MSG_TALK  *  )mallocObj_pMsgTask_toCompress.malloc(  sizeof(  MIS_MSG_TALK  )  )  )  )  goto  errLabel;
	 }

	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  pPreTransformVideo->debugStep.showInfo.tWhere,  _T(  ""  ),  _T(  "%s %d starts"  ),  pPreTransformVideo->q2.cfg.name,  pTransform->index_activeMems_from  );
	
	 for  (  ;  !pPreTransformVideo->bQuit;  )  {
		  
		  if  (  !dwToInMs  )  {			  
			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning: mcThreadProc_transformVideo: dwToInMs %d"  ),  dwToInMs  );
			  dwToInMs  =  DEFAULT_dwToInMs;
		  }

		  //  2009/07/14
		  MACRO_setStep(  pPreTransformVideo->debugStep,  CONST_threadStep_toWait  );

		  //
		  DWORD  dwTickCnt0  =  GetTickCount(  );
		  DWORD  dwTickCnt;
		  DWORD  dwEvt  =  MsgWaitForMultipleObjects(
			  				 pPreTransformVideo->q2.cfg.usCnt_hEvents,		// mycountof(  pPreTransformVideo->hEvents  ),		// Number of events.
							 pPreTransformVideo->q2.hEvents,				// Location of handles.
                             FALSE,										// Wait for all?
                             dwToInMs,									// How long to wait?
                             0  );										// Any message is an 
																		// event.
		  if  (  dwEvt  ==  WAIT_FAILED  )  {
			  iErr  =  -110;
			  goto  errLabel;
		  }
	      //
		  dwTickCnt =   GetTickCount(  );

		  if  (  dwEvt  !=  WAIT_TIMEOUT  )  {
			  dwEvt -= WAIT_OBJECT_0;
			  switch  (  dwEvt  )  {
					  case  0:
						     dwTickCnt_lastVideoData  =  dwTickCnt;		//  audio data received
							 break;
					  case  1:
						     traceLogA(  (char*)  "transformVideo: event 1."  );
							 break;
					  default:
						     traceLogA(  (char*)  "unknown event"  );	
							 iErr  =  -120;
		  					 goto  errLabel;
							 break;
			  }
		  }


		  for  (  ;  !pPreTransformVideo->bQuit;  )  {

			   //  2011/12/06
			   if  (  isQ2Empty(  &pPreTransformVideo->q2  )  )  break;

			   //
			   MACRO_setStep(  pPreTransformVideo->debugStep,  CONST_threadStep_toGetMsg  );


			   for  (  i  =  0;  i  <  maxMsgs;  i  ++  )  {
				    msgLens[i]  =  sizeof(  msgs[0]  );
			   }
			   nMsgs  =  maxMsgs;
			   //  len  =  sizeof(  pMsg[0]  );
			   {
				   CQyQ2Help	q2Help;			  
				   if  (  qGetMsgs(  q2Help.getQ_toGetMsg(  &pPreTransformVideo->q2,  _T(  "preTransV 0"  )), (void**)pMsgs, (unsigned  int*)msgLens, (unsigned  int*)&nMsgs))  break;
			   }			   

			   //
			   for  (  i  =  0;  i  <  nMsgs;  i  ++  )  {
				    memset(  (  (  char  *  )(  pMsgs[i]  )  )  +  msgLens[i],  0,  min(  256,  sizeof(  msgs[0]  )  -  msgLens[i]  )  );			   			   
			   }

			   #ifdef  __DEBUG__
					   //  traceLog((TCHAR*)  _T(  "preTransV: nMsgs %d"  ),  nMsgs  );
			   #endif
			   if  (  !nMsgs  )  continue;

			   for  (  i  =  0;  i  <  nMsgs;  i  ++  )
			   {
				   MIS_MSGU  *  pMsg  =  pMsgs[i];

				   //
				   switch  (  pMsg->uiType  )  {
						   case  CONST_misMsgType_task:  
							   {
							     CQyMalloc	mallocObj_pkts[CONST_pkts_preTransformVideo];

							     MACRO_setStep(  pPreTransformVideo->debugStep,  CONST_threadStep_msgGot  );

								 //  2014/05/12
								 if  (  ctx.status.ucMsgSkipped_ifMallocFailed  )  {
									 #ifdef  __DEBUG__
											 traceLog((TCHAR*)  _T(  "pretransV: msg skipped if mallocFailed"  )  );
									 #endif
									 ctx.status.ucMsgSkipped_ifMallocFailed  --  ;
									 if  (  !ctx.status.ucMsgSkipped_ifMallocFailed  )  {
										 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  pPreTransformVideo->debugStep.showInfo.tWhere,  _T(  ""  ),  _T(  "pretransV: errExists_mallofFailed, nMsgSkipped %d. proc again"  ),  (  int  )ctx.status.ucMsgSkipped_ifMallocFailed  );		
									 }
									 continue;
								 }

								 //
								 nPkts  =  0;

								 //
								 memset(  &ctx.status.errFlgs,  0,  sizeof(  ctx.status.errFlgs  )  );
								 //doPreTransformTaskVideo(  pTransform,  &pMsg->task,  pTransform->index_activeMems_from,  pkts,  mallocObj_pkts,  mycountof(  mallocObj_pkts  )  -  nPkts,  &nPkts,  &ctx  );
								 doPreTransformTaskVideo(  pTransform,  &pMsg->task,  pkts,  mallocObj_pkts,  mycountof(  mallocObj_pkts  )  -  nPkts,  &nPkts,  &ctx  );
								 if  (  ctx.status.errFlgs.bErrExists_mallocfFailed  )  {
									 ctx.status.ucMsgSkipped_ifMallocFailed  =  15;	//  10;
									 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  pPreTransformVideo->debugStep.showInfo.tWhere,  _T(  ""  ),  _T(  "pretransV: errExists_mallofFailed, nMsgSkipped %d"  ),  (  int  )ctx.status.ucMsgSkipped_ifMallocFailed  );		
									 continue;
								 }

								 //
								 MACRO_setStep(  pPreTransformVideo->debugStep,  CONST_threadStep_msgProced  );

								 if  (  !nPkts  )  break;

			 			 		 #if  0
							          //  if  (  nPkts  !=  1  )  
									  {			
										  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "transV: nPkts %d"  ),  nPkts  );		
									  }
								 #endif
									  								 
								 //  2016/08/29
#if  10
								 if  (  isQ2Warning(  &pTransform->video.q2,  1  )  )  
								 {
									 int  kk;
									 unsigned  int  len;
									 int  tmpiRet;
									 TCHAR  tBuf[128]  =  _T(  ""  );
									 int nQ2Nodes = getQ2Nodes(&pTransform->video.q2);
									 
									 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "too many pkts in transQ. %d nodes. try to empty q"  ),  nQ2Nodes  );
									 showInfo_open0(  0,  0,  tBuf  );
									 //
									 emptyQ2(&pTransform->video.q2);

								 }
#endif
								 //
#ifdef  __DEBUG__
								 if  (  0  )
								 { 
									 TCHAR   tBuf[128];
									 int nQ2Nodes = getQ2Nodes(&pTransform->video.q2);
									 _sntprintf(tBuf, mycountof(tBuf), _T("%d pkts in transQ[%d]. "), nQ2Nodes, pTransform->index_activeMems_from);
									 //showInfo_open0(0, 0, tBuf);
									 traceLog(tBuf);
								 }
#endif


								 //
								 //  这里要送去解码
								 int  j,  k;
								 int  nPlay;
								 for  (  j  =  0;  j  <  nPkts;  )  {
									  nPlay  =  min(  nPkts  -  j,  CONST_pkts_out_preTransformVideo  );
									  bPktsRedirected  =  FALSE;
									  if  (  !q2PostMsgAndTrigger(  &pkts[j],  nPlay  *  sizeof(  pkts[0]  ),  &pTransform->video.q2,  _T(  "preTransV"  ))) {
										  bPktsRedirected  =  TRUE;
									  }
									  //
									  if (!bPktsRedirected) {
										  int  ii = 0;
									  }
									  //
									  if  (  bPktsRedirected  )  {
										  for  (  k  =  j;  k  <  j  +  nPlay;  k  ++  )  {
											  mallocObj_pkts[k].detach(  );
										  }
									  }
									  j  +=  nPlay;
								 }
							     }
							     break;
						   default:
									break;
				   }
			   
			   }
		  }
	 }

	 iErr  =  0;

errLabel:

	 //
	 MACRO_setStep(  pPreTransformVideo->debugStep,  CONST_threadStep_toExit  );
	 pPreTransformVideo->debugStep.iErr_thread  =  iErr;

#if  0
	 //  2014/03/04
	qdcExitSplInfo(  &g_splInfo  );
	bInited_splInfo  =  FALSE;
#endif

	 //
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s %d ends."  ),  pPreTransformVideo->q2.cfg.name,  pTransform->index_activeMems_from  );
	 

	 pPreTransformVideo->bRunning  =  FALSE;

	 //
#if  0
	 exitBufPretrans(  &buf_pretrans  );

	 //  2014/03/07
	 if  (  ctx.bInited_streamDataQ  )  {
		 exitGenericQ(  &ctx.streamDataQ  );
		 ctx.bInited_streamDataQ  =  FALSE;
	 }
#endif


	 //
	 MACRO_setStep(  pPreTransformVideo->debugStep,  CONST_threadStep_end  );

#ifdef  __DEBUG__
	 traceLogA(  (char*)  "mcThreadProc_transformVideo %S leaves",  pPreTransformVideo->q2.cfg.name  );
#endif

	 return  0;
}


