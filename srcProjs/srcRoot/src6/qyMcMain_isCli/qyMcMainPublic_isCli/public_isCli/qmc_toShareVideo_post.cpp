
#include	"stdafx.h"
#include	<stddef.h>
#include	<time.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"
#include	"tmpCeLib.h"
#ifndef  __WINCE__
//  #include	"DlgVideos.h"
#endif
#include	"qmcVideoCapture_isCli.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#ifndef  __WINCE__
#include	"qmcVWall.h"
//  #include	"DlgDynBmps.h"
#endif
#include	"qmcCmdProc.h"

#include	"qySqlFunc.h"
#include	"qyAvRecordPublic.h"

#include	"qmcCommFunc_isCli.h"

#include	"qmcVideoTool.h"




//
int  toShareVideo_post_qmc(  MC_VAR_isCli  *	pProcInfo,		unsigned  int  uiCapType,  int  iIndex_capProcInfo,  myDRAW_VIDEO_DATA  *  pkts,  unsigned  int  nPkts,  COMPRESS_VIDEO  *  pCompressVideo,  QY_SHARED_OBJ  *  pSharedObj,  MIS_MSGU  *  pMsgBuf  )
{
	int						iErr						=	-1;
	QY_MC			*		pQyMc						=	QY_GET_GBUF(  );
	int						tmpiRet						=	0;

	if  (  !pkts  ||  !nPkts  )  return  -1;

	DWORD					dwCkID						=	0;
	DWORD					dwFlags						=	0;
	DWORD					lIndex						=	0;
	DWORD					dwQuality					=	pCompressVideo->u.vcm.iQuality;
	//  int						i;
	unsigned  int			uiChannelType				=	CONST_channelType_media;
	
	time_t					tStartTran					=	pkts[0].input.tStartTran;			//  2011/08/30
	if  (  !tStartTran  )  {
		#ifdef  __DEBUG__
				//traceLog((TCHAR*)  _T(  "toShareVideo_post: tStartTran is 0"  )  );
		#endif
		mytime(  &tStartTran  );  
	}

	unsigned  char			ucbNeedShowFrameInfo		=	FALSE;

	//  2010/09/04
	SHARED_OBJ_USR	*	pSharedObjUsr	=	NULL;
	if  (  !pSharedObj  )  goto  errLabel;
	pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
	if  (  !pSharedObjUsr  )  goto  errLabel;

	//
#if  0
	//  pCompressVideo->usFramesThisSecond_input  ++  ;
	pCompressVideo->usFramesThisSecond_input  +=  nPkts  ;
#endif


	if  (  pCompressVideo->tLastTime_post  !=  tStartTran  )  {				//  Õâ±íÃ÷ÊÇÒ»ÃëµÄ¿ªÊ¼				

		//
		#ifdef  __DEBUG__
				if  (  !iIndex_capProcInfo  )  {
					int  ii  =  0;
				}
		#endif

		//
		pCompressVideo->tLastTime_post  =  tStartTran;

		//  
		if  (  (  int  )(  tStartTran  -  pCompressVideo->tLastTime_showFrameInfo  )  >  pProcInfo->cfg.usNeedShowFrameInfoIntervalInS  )  {			
			//
			ucbNeedShowFrameInfo  =  TRUE;
		}
		
#if  0
		if  (  !pCompressVideo->ucbFixedRate  )  {  		
			  if  (  !isVideoNormalState(  pCompressVideo  )  )  ucbNeedShowFrameInfo  =  TRUE;								//  ·ÇÎÈ¶¨Ì¬ÐèÒª²»Í£µÄÈ¥ÎÊ¿Í»§¶Ë¡£Ò»Ö±µ½½¨Á¢ÎÈ¶¨Ì¬ÎªÖ¹
		}
#endif
	
		//  2017/09/05
		#ifdef  __DEBUG__
				#if  0	//  for test
					 ucbNeedShowFrameInfo  =  TRUE;
				#endif
		#endif

		//
		DWORD  dwTickCnt  =  GetTickCount(  );
		int   nElapseInMs  =  dwTickCnt  -  pCompressVideo->dwTickCnt_selectTime;

		//  2014/04/26. 2008/12/05, uiCnt_pkts_fromSelect
		if  (  !pCompressVideo->tSelectTime  
			||  pCompressVideo->uiCnt_pkts_fromSelect  >  32  *  1024
			//||  pCompressVideo->tmp_bMediaChannelReady  !=  pProcInfo->av.bVideoChannelReady  
			//||  pCompressVideo->tmp_ucbNotSendData  !=  pSharedObjUsr->ucbNotSendData  
			||  abs(  nElapseInMs  )  >  1  *  60  *  1000	//  2017/09/05
			)  
		{
			CQySyncObj		syncObj;
			if  (  !syncObj.sync(  pProcInfo->cfg.mutexName_syncSendAv,  0  )  )  {
				pCompressVideo->tSelectTime  =  tStartTran;
				pCompressVideo->dwTickCnt_selectTime  =  dwTickCnt;
				pCompressVideo->uiCnt_pkts_fromSelect  =  0;
				pCompressVideo->fFps_sending  =  0;

				pCompressVideo->usTimes_ok  =  0;
				pCompressVideo->usTimes_failure  =  0;
		
				//pCompressVideo->tmp_bMediaChannelReady  =  pProcInfo->av.bVideoChannelReady;
				//pCompressVideo->tmp_ucbNotSendData  =  pSharedObjUsr->ucbNotSendData;
				
				//
				ucbNeedShowFrameInfo  =  TRUE;

				//
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "to select %d/s. index_capBmp %d"  ),  pCompressVideo->usFrames_perSecond_expected,  iIndex_capProcInfo  );
			}
		}

	}


	//
#if  0
	if  (  !pProcInfo->av.bVideoChannelReady  )  {
		//
		//  qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning: toShareV_post: mediaChannel is not ready."  )  );
		//		
		static  DWORD	sdwTickCnt_applyForChkChannels	=	0;
		//
		if  (  !pSharedObjUsr->ucbNotSendData
			//&&  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  
			//||  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  
			)
		{
					   MIS_CNT							*	pMisCnt		=	NULL;
					   MIS_MSG_applyForChkChannels_qmc		msg_applyForChkChannels;
					   int	dwTickCnt;						dwTickCnt  =  GetTickCount(  );
					   int									i;
					   //  CQyQ2Help								q2Help;

					   if  (  dwTickCnt  -  sdwTickCnt_applyForChkChannels  >  4000  )  {
						   //  for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
						   for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
						   {
							   pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  i  );  //  &pProcInfo->misCnts[i];
							   if  (  !pMisCnt->cfg.dynCfg.cnt.usCntPort  )  continue;

							   //  traceLogA(  "toShareBmp: applyForChkChannels"  );
							   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "toShareV_post: media Channel not Ready, applyForChkChannels"  )  );

							   //
							   memset(  &msg_applyForChkChannels,  0,  sizeof(  msg_applyForChkChannels  )  );
							   msg_applyForChkChannels.uiType  =  CONST_misMsgType_applyForChkChannels_qmc;
							   msg_applyForChkChannels.pMisCnt  =  pMisCnt;
							   //
							   if  (  q2PostMsgAndTrigger(  &msg_applyForChkChannels,  sizeof(  msg_applyForChkChannels  ),  &pProcInfo->mediaQ2  )  )  {
								   showNotification(  0,  0,  0,  0,  0,  0,  _T(  "toShareBmp: applyForChkChannels failed"  )  );
							   }
						   }
						   sdwTickCnt_applyForChkChannels  =  dwTickCnt;
					   }
				   
		}		  
	
		//  2015/05/12
#ifdef  __DEBUG__
		//traceLog((TCHAR*)  _T(  "toShareVideo_post: bVideoChannelReady false. skipped"  )  );
#endif

		//  
		iErr  =  0;  goto  errLabel;
	}
#endif
#if  0
	if  (  pSharedObjUsr->ucbNotSendData  )  {
		iErr  =  0;  goto  errLabel;
	}
#endif
	//  2014/11/16
	if  (  pSharedObjUsr->ucbInConfMosaic  )  {
		#ifdef  __DEBUG__
				//traceLog((TCHAR*)  _T(  "toShareVideo_post: ucbInConfMosaic true. "  )  );
		#endif
		iErr  =  0;  goto  errLabel;
	}

	//
	unsigned  char			ucFlg; ucFlg = CONST_commFlg_routeTalkData;	//  0;
	unsigned  short			usIndex_activeMems_from; usIndex_activeMems_from = 0;
	unsigned  int			myuiSampleTimeInMs; myuiSampleTimeInMs = 0;//  2009/05/30
	int						ii;

	TRANSFER_VIDEO_DATA* pReq; pReq = NULL;

#if  0
	pReg  =  pCompressVideo->pReqBuf_myVideoCapture;	
	if  (  pReq  )  {
		memset(  pReq,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );
		pReq->uiType  =  CONST_imCommType_transferVideoData;
		//  pReq->uiTranNo_openAvDev  =  pCompressVideo->uiTranNo_openAvDev;
		pReq->uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_v;			//  2010/09/04
		//
	}
#else
	if  (  nPkts  !=  1  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "toShareVideo_post failed: nPkts must is 1"  )  );
		#endif
		goto  errLabel;
	}
	myDRAW_VIDEO_DATA* pPkt; pPkt = &pkts[0];
	
	//  if  (  pPkt->memory.uiBufSize  !=  pPkt->uiSize_dec  +  sizeof(  TRANSFER_VIDEO_DATA  )  )  
	if  (  pPkt->memory.uiBufSize  <  pPkt->uiSize_dec  +  sizeof(  TRANSFER_VIDEO_DATA  )  )  //  2014/09/30
	{
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "toShareVideo_post: uiBufSize err"  )  );
		#endif
		goto  errLabel;
	}

	pReq  =  (  TRANSFER_VIDEO_DATA  *  )(  pPkt->memory.m_pBuf  +  pPkt->uiSize_dec  );

#endif


	//				  
	if  (  !pReq->usCnt  )  {	
		#if  0
			traceLog((TCHAR*)  _T(  "toShareBmp failed: req.usCnt is 0"  )  );
		#endif
		//showInfo_open0(  0,  _T(  "toShareVideo_post_qmc"  ),  _T(  " failed, req.usCnt is 0"  )  );
		//
		goto  errLabel;
	}

#ifdef  __DEBUG__
		#if  0
			  traceLog((TCHAR*)  _T(  "post: pReq->usCnt %d, pReq->uiLen %d, nPkts %d"  ),  (  int  )pReq->usCnt,  pReq->uiLen,  nPkts  );
		#endif
#endif


	//  2008/11/22
#if  0  //  2016/12/27
	if  (  pCompressVideo->uiEventId_lastRecvd  )  {
		//  pReq->uiEventId_lastRecvd_ii  =  pCompressVideo->uiEventId_lastRecvd;
		pReq->mems[0].uiEventId_lastRecvd  =  pCompressVideo->uiEventId_lastRecvd;	//  2013/11/15
		pCompressVideo->uiEventId_lastRecvd  =  0;		//  ½«uiEventId_lastRecvdÇë0ÊÇÎªÁË±ÜÃâÖØ¸´·¢ËÍ
	}
#endif

	//  2017/09/04
#ifdef  __DEBUG__
		//
		int  i;
		for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
			TRANSFER_VIDEO_dataMemHead  *  pMem  =  &pReq->mems[i];
			//
			pCompressVideo->iVal_dbg  ++  ;
			//
		    pMem->stat.iVal_dbg  =  pCompressVideo->iVal_dbg;
			//
			#if  0
			if  (  !ucbNeedShowFrameInfo  )  {	
				if  (  !iIndex_capProcInfo  )  {
					TCHAR tBuf[128];		
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "req.iVal %d, index_capBmp %d"  ),  pMem->stat.iVal_dbg,  iIndex_capProcInfo  );
					showInfo_open0(  0,  _T(  "toShareVideo_post"  ),  tBuf  );
				}
			}
			#endif
		}
		//
#endif
	

	//  2010/09/12
	//  pCompressVideo->uiCnt_pkts_fromSelect  ++  ;
	pCompressVideo->uiCnt_pkts_fromSelect  +=  pReq->usCnt  ;
	//  pCompressVideo->usCnt_pkts  ++  ;
	if  (  ucbNeedShowFrameInfo  )  {
		ucFlg  |=  CONST_commFlg_routeTalkData;
		if  (  pCompressVideo->tRecvTime_resp_fromCli  >=  pCompressVideo->tFirstTime_showFrameInfo_withoutResp  )  {	//  ÕâÊÇÎªÁË³¬Ê±
			pCompressVideo->tFirstTime_showFrameInfo_withoutResp  =  tStartTran;
		}
		//  pReq->tLastTime_showFrameInfo_020534  =  pCompressVideo->tLastTime_showFrameInfo;
		//  pReq->usCnt_pkts  =  pCompressVideo->usCnt_pkts;
		//
		TRANSFER_VIDEO_dataMemHead  *  pMem  =  &pReq->mems[pReq->usCnt  -  1];
		
#if  10
		//
		pMem->stat.usCnt_pkts  =  (  unsigned  short  )pCompressVideo->uiCnt_pkts_fromSelect;
		pMem->stat.tSelectTime  =  pCompressVideo->tSelectTime;
		//				  				  
		pMem->stat.usFps  =  (  unsigned  short  )pCompressVideo->fFps_sending;
#endif
		//
		pCompressVideo->tLastTime_showFrameInfo  =  tStartTran;				//  ÉèÖÃÊ±¼ä´Á
		//  pCompressVideo->usCnt_pkts  =  0;
		//
		if  (  !iIndex_capProcInfo  )  {
			TCHAR  tBuf[128];
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "send fps %.2f/s, input fps %d/s,  imageSize_input %d, imageSize %d, index_capBmp %d"  ),  pCompressVideo->fFps_sending,  (  int  )pCompressVideo->input_BufferCB.videoInputInfo.usFps,  pCompressVideo->vh_decompress.bih.biSizeImage,  pCompressVideo->vh_compress.bih.biSizeImage,  iIndex_capProcInfo  );
			#ifdef  __DEBUG__
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "req.tSelectTime %I64u, uiLen %d, req.usCnt %d, iVal_dbg %d. stat.cnt_pts %d, iIndex_capBmp %d"  ),  pMem->stat.tSelectTime,  pReq->uiLen,  (  int  )pReq->usCnt,  pMem->stat.iVal_dbg,  (  int  )pMem->stat.usCnt_pkts,  iIndex_capProcInfo  );
			#endif
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  tBuf  );
		}
	}

		

	//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "compress ok, compressedDataLen is %d bytes\n"  ),  pProcInfo->av.iCompressBufSize  );  					  
	//  OutputDebugString(  tBuf  );
					  
	unsigned  int	uiTranNo;  if  (  (  uiTranNo  =  getuiNextTranNo(  0,  0,  0  )  )  ==  -1  )  goto  errLabel;
	int						lenInBytes; lenInBytes = 0;

	#ifdef  __DEBUG__
		    if  (  pProcInfo->cfg.debugStatusInfo.ucbPrint_v_out  )  {			
				//traceLog((TCHAR*)  _T(  "toShareBmp: tn %d, req.usCnt %d, len %d, mems[0].uiSampleTimeInMs %d, iDiffInMs_toStartAudio %d. iSampleTimeInMs %d"  ),  uiTranNo,  pReq->usCnt,  pReq->uiLen,  pReq->mems[0].uiSampleTimeInMs,  pSharedObj->iDiffInMs_tStartAudio,  pReq->mems[0].uiSampleTimeInMs_org  );
			}
			if  (  pSharedObj->bSlave  )  {
				int  ii;
				ii  =  0;
			}
			if  (  uiCapType  ==  CONST_capType_screen  )  {
				int  ii;
				ii  =  0;
			}
    #endif

	
	//
	lenInBytes  =  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  +  pReq->uiLen;
	//
	//unsigned  char		ucbHaveMsgrs_sendLocalAv;	ucbHaveMsgrs_sendLocalAv  =  FALSE;
	unsigned  char		ucbFixedRate;				ucbFixedRate  =  FALSE;		
	MIS_CNT			*	pMisCnt;					pMisCnt  =	NULL;		
			  
	// 
#if  0  //  2014/10/29
	if  (  pSharedObj->curRoute_sendLocalAv.route.uiMsgRouteId  !=  pSharedObj->route_sendLocalAv.route.uiMsgRouteId  )  {
		CQySyncObj	syncObj;
		if  (  !syncObj.sync(  pProcInfo->cfg.mutexName_syncSendAv,  0  )  )  {
			memcpy(  &pSharedObj->curRoute_sendLocalAv,  &pSharedObj->route_sendLocalAv,  sizeof(  pSharedObj->curRoute_sendLocalAv  )  );
		    #ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "toShareBmp: curRoute_sendLocalAv refreshed"  )  );
			#endif
		}			
	}
#endif

	int  iIndex_misCnt; iIndex_misCnt = 0;	//pSharedObj->curRoute_sendLocalAv.iIndex_misCnt
	if  (  !(  pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  iIndex_misCnt  )  )  )  {
		#ifdef  __DEBUG__
				traceLogA(  (char*)"getMisCntByIndex failed. index %d",  iIndex_misCnt  );
		#endif
		goto  errLabel;
	}

	//if  (  !pSharedObjUsr->ucbNotSendData  )  
	{

#if  0
		pSharedObj->curRoute_sendLocalAv.route.debugInfo.dwTickCnt_me_start  =  GetTickCount(  );		
		if  (  ucbNeedShowFrameInfo  )  {	//  2008/05/16									 
			//  time_t	tNow;	mytime(  &tNow  );  pSharedObj->curRoute_sendLocalAv.route.debugInfo.tTime_start  =  tNow;
			pSharedObj->curRoute_sendLocalAv.route.debugInfo.tTime_start  =  tStartTran;
		}
#endif

		#if	0
	  		if  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  )  {	//  
				if  (  postMsg2MgrFunc_mc(  pMisCnt,  &pSharedObj->curRoute_sendLocalAv.route,  CONST_misMsgType_outputTask_toMix,  ucFlg,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  pSharedObjUsr->iTaskId,  0,  (  char  *  )pReq,  lenInBytes,  &pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to,  NULL,  NULL,  0,  uiChannelType,  pMsgBuf,  FALSE  )  )  traceLog((TCHAR*)  _T(  "postMsg2MgrFunc_mc failed"  )  );
				}							   
			else  {
				  if  (  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  {
					  if  (  postMsg2MgrFunc_mc(  pMisCnt,  &pSharedObj->curRoute_sendLocalAv.route,  CONST_misMsgType_outputTask_toMix,  ucFlg,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  pSharedObjUsr->iTaskId,  0,  (  char  *  )pReq,  lenInBytes,  0,  NULL,  NULL,  0,  uiChannelType,  pMsgBuf,  FALSE  )  )  traceLog((TCHAR*)  _T(  "postMsg2MgrFunc_mc failed"  )  );
				  }				  
			}
		#else

#if  0
			int  msgLen  =  0;
	  		if  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  )  {	//  
				if  (  makeMsg2MgrFunc_mc(  pMisCnt,  &pSharedObj->curRoute_sendLocalAv.route,  CONST_misMsgType_task,  ucFlg,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  pSharedObjUsr->iTaskId,  0,  (  char  *  )pReq,  lenInBytes,  &pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to,  NULL,  NULL,  0,  uiChannelType,  pMsgBuf,  &msgLen  )  )  traceLog((TCHAR*)  _T(  "postMsg2MgrFunc_mc failed"  )  );
				}							   
			else  {
				  if  (  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  {
					  if  (  makeMsg2MgrFunc_mc(  pMisCnt,  &pSharedObj->curRoute_sendLocalAv.route,  CONST_misMsgType_task,  ucFlg,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  pSharedObjUsr->iTaskId,  0,  (  char  *  )pReq,  lenInBytes,  0,  NULL,  NULL,  0,  uiChannelType,  pMsgBuf,  &msgLen  )  )  traceLog((TCHAR*)  _T(  "postMsg2MgrFunc_mc failed"  )  );
				  }				  
			}
			if  (  msgLen  >  0  )  {
				CAP_procInfo_bmpCommon		*	pCapBmp				=  (  CAP_procInfo_bmpCommon  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
				if  (  !pCapBmp  )  goto  errLabel;

				#if  1
					 memcpy(  &pMsgBuf->task.data.route.debugInfo.debug_myDRAW_VIDEO_DATA,  &pPkt->debugInfo,  sizeof(  DEBUG_myDRAW_VIDEO_DATA  )  );
				#endif

				if  (  (  tmpiRet  =  pProcInfo->processQ_media.qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsgBuf,  0  )  )  <=  0  )  {
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "postMsg2MgrFunc_mc: msg_task_toMix"  ),  tmpiRet  ?  "failed"  :  "not found"  );
					#endif
				}
			}
#endif

			//

			int  msgLen  =  0;
	  		
			//
			if  (  makeMsg2MgrFunc_mc(  pMisCnt,  NULL,  CONST_misMsgType_task,  ucFlg,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  pSharedObjUsr->iTaskId,  0,  (  char  *  )pReq,  lenInBytes,  NULL,  NULL,  NULL,  0,  uiChannelType,  pMsgBuf,  &msgLen  )  )  traceLog((TCHAR*)  _T(  "postMsg2MgrFunc_mc failed"  )  );
			//
			if  (  msgLen  >  0  )  {
				CAP_procInfo_bmpCommon		*	pCapBmp				=  (  CAP_procInfo_bmpCommon  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
				if  (  !pCapBmp  )  goto  errLabel;

				#if  1
					 memcpy(  &pMsgBuf->task.data.route.debugInfo.debug_myDRAW_VIDEO_DATA,  &pPkt->debugInfo,  sizeof(  DEBUG_myDRAW_VIDEO_DATA  )  );
				#endif

				//
				pMsgBuf->task.bFrom_sharedObj  =  true;
				pMsgBuf->task.index_sharedObj  =  pSharedObj->index_sharedObj;
				
				//
				if  (  (  tmpiRet  =  pProcInfo->processQ_media.qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsgBuf,  0  )  )  <=  0  )  {
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "postMsg2MgrFunc_mc: msg_task_toMix"  ),  tmpiRet  ?  "failed"  :  "not found"  );
					#endif
				}
			}


	    #endif

	}

    #ifdef  __DEBUG__
		    //if  (  pSharedObjUsr->ucbNotSendData  )  traceLogA(  "toShareBmp: not send data"  );
	#endif

	//if  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  ||  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  ucbHaveMsgrs_sendLocalAv  =  TRUE;
	//if  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  )  ucbFixedRate  =  TRUE;

	//
	if  (  ucbFixedRate  !=  pCompressVideo->ucbFixedRate  )  pCompressVideo->ucbFixedRate  =  ucbFixedRate;

	//
#if  0  //  2014/12/09
	if  (  !ucbHaveMsgrs_sendLocalAv  &&  !IsWindow(  pProcInfo->hWnd_testWebcam  )  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Warning: no messenger need to be sent, video shall be stopped."  )  );
	}
#endif
		  

	iErr  =  0;

errLabel:

	//  if  (  pData_allocated  )  free(  pData_allocated  );
#ifdef  __DEBUG__
		//  traceLog((TCHAR*)  _T(  "toShareBmp leaves"  )  );
#endif

	return  iErr;

}


