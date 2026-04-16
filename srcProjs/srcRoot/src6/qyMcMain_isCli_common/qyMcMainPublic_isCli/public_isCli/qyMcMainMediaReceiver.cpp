
#include	"stdafx.h"
#include	<stdio.h>
#include	<stddef.h>
#include	<time.h>

#include	"qyMcMainCommon.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcAcm.h"
#include	"qyVk.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qmcDmoPublic.h"
#include	"tmpCeLib.h"
#include	"qmcCommFunc_isCli.h"
#include	"qy_qBuf2_defs.h"

//  #define		MACRO_getDmo(  usCnt,  dmoInfos,  usIndex  )	(  (  usIndex  >=  0  &&  usIndex  <  usCnt  )  ?  &dmoInfos[usIndex]  :  NULL  )


 // procTaskAvReply must be called int media thread. If mems_from[index] need to be modified, transform threads must be stopped first.
 //
  








///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////





 int  mySendAvResp(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_TASK  *  pMsg,  MIS_MSGU  *  pMsgBuf  )
{
	int					iErr			=	-1;
	IM_CONTENTU		*	pContent		=	(  IM_CONTENTU  *  )pMsg->data.buf;
	int					lenInBytes;
	unsigned  short		usRespCode			=	CONST_qyRc_unknown;	
	MIS_CNT			*	pMisCnt			=	(  MIS_CNT  *  )pMsg->pMisCnt;
	if  (  !pMisCnt  )  return  -1;
	TCHAR				tBuf[128];
	int  i;

	//  2017/09/04
	if  (  pMsg->data.route.idInfo_from.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
		return  0;
	}

	//
	switch  (  pContent->uiType  )  {
			case  CONST_imCommType_transferVideoData:
				  for  (  i  =  0;  i  <  pContent->transferVideoData.usCnt;  i  ++  )  {
					   TRANSFER_VIDEO_dataMemHead  *  pMem  =  &pContent->transferVideoData.mems[i];
					   if  (  !pMem->stat.tSelectTime  )  continue;
					   //				  
					   {
				
					  MSG_ROUTE					route;
					  unsigned  char				ucFlg	=	CONST_commFlg_resp;
					  TRANSFER_VIDEO_dataResp		resp;

					  memset(  &route,  0,  sizeof(  route  )  );
					  memcpy(  &route.debugInfo,  &pMsg->data.route.debugInfo,  sizeof(  route.debugInfo  )  );

					  ucFlg  |=  CONST_commFlg_routeTalkData;

					  memset(  &resp,  0,  sizeof(  resp  )  );
					  resp.uiType  =  CONST_imCommType_transferVideoDataResp;
					  //
					  resp.idInfo.ui64Id  =  pMem->idInfo.ui64Id;
					  resp.uiTranNo_openAvDev  =  pMem->uiTranNo_openAvDev;
					  if  (  !resp.uiTranNo_openAvDev  )  {
						  resp.uiTranNo_openAvDev  =  pContent->transferVideoData.uiTranNo_openAvDev;
					  }
					  //
					  resp.usFps  =  (  unsigned  short  )pContent->transferVideoData.tmpInternal.result.fFps; 
					  resp.tSelectTime  =  pContent->transferVideoData.tmpInternal.result.tSelectTime;
					  resp.usCnt_pkts  =  pContent->transferVideoData.tmpInternal.result.usCnt_pkts;
					  resp.usDiff_pkts  =  pContent->transferVideoData.tmpInternal.result.usDiff_pkts;

					  //
					  lenInBytes  =  sizeof(  resp  );
				
					  usRespCode  =  pContent->transferVideoData.tmpInternal.result.usRespCode;

					  if  (  postMsg2Mgr_mc(  pMisCnt,  &route,  CONST_misMsgType_outputTask,  ucFlg,  usRespCode, pMsg->tStartTime,  pMsg->uiTranNo,  0,  (  char  *  )&resp,  lenInBytes,  &pMsg->addr_logicalPeer.idInfo,  &pMsg->data.route.idInfo_from,  pMsg->uiChannelType,  pMsgBuf,  FALSE  )  )  goto  errLabel;
					  
					  //  2017/09/05
					  #ifdef  __DEBUG__
							  #if  0
								   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "sendAvResp to %I64u"  ),  pMsg->data.route.idInfo_from.ui64Id  );
								   showInfo_open0(  0,  _T(  "sendAvResp"  ),  tBuf  );
							  #endif
					  #endif

					  }
				  }
				  break;
			case  CONST_imCommType_transferAudioData:
				  if  (  pContent->transferAudioData.tLastTime_showFrameInfo_020534  )  {

					  MSG_ROUTE					route;
					  unsigned  char				ucFlg	=	CONST_commFlg_resp;
					  TRANSFER_AUDIO_dataResp		resp;
					  unsigned  short				usRespCode;

					  memset(  &route,  0,  sizeof(  route  )  );
					  memcpy(  &route.debugInfo,  &pMsg->data.route.debugInfo,  sizeof(  route.debugInfo  )  );

					  ucFlg  |=  CONST_commFlg_routeTalkData;
										   
					  memset(  &resp,  0,  sizeof(  resp  )  );
					  resp.uiType  =  CONST_imCommType_transferAudioDataResp;
					  resp.uiTranNo_openAvDev  =  pContent->transferAudioData.uiTranNo_openAvDev;
					  resp.usCnt_pkts  =  pContent->transferAudioData.tmpInternal.result.usCnt_pkts;
							   
					  lenInBytes  =  sizeof(  resp  );
				
					  usRespCode  =  pContent->transferAudioData.tmpInternal.result.usRespCode;

					  if  (  postMsg2Mgr_mc(  pMisCnt,  &route,  CONST_misMsgType_outputTask,  ucFlg,  usRespCode, pMsg->tStartTime,  pMsg->uiTranNo,  0,  (  char  *  )&resp,  lenInBytes,  &pMsg->addr_logicalPeer.idInfo,  &pMsg->data.route.idInfo_from,  pMsg->uiChannelType,  pMsgBuf,  FALSE  )  )  goto  errLabel;
				
				  }
				  break;
			case  CONST_imCommType_transferGpsData:		//  2012/04/24
				  if  (  pContent->transferGpsData.tLastTime_showFrameInfo_020534  )  {

					  MSG_ROUTE						route;
					  unsigned  char				ucFlg	=	CONST_commFlg_resp;
					  TRANSFER_GPS_dataResp			resp;
					  unsigned  short				usRespCode;

					  memset(  &route,  0,  sizeof(  route  )  );
					  memcpy(  &route.debugInfo,  &pMsg->data.route.debugInfo,  sizeof(  route.debugInfo  )  );

					  ucFlg  |=  CONST_commFlg_routeTalkData;
										   
					  memset(  &resp,  0,  sizeof(  resp  )  );
					  resp.uiType  =  CONST_imCommType_transferGpsDataResp;
							   
					  lenInBytes  =  sizeof(  resp  );
				
					  usRespCode  =  CONST_qyRc_ok;

					  if  (  postMsg2Mgr_mc(  pMisCnt,  &route,  CONST_misMsgType_outputTask,  ucFlg,  usRespCode, pMsg->tStartTime,  pMsg->uiTranNo,  0,  (  char  *  )&resp,  lenInBytes,  &pMsg->addr_logicalPeer.idInfo,  &pMsg->data.route.idInfo_from,  pMsg->uiChannelType,  pMsgBuf,  FALSE  )  )  goto  errLabel;

				  }
				  break;
			default:
					break;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}





//
 int  playAudioData(  MC_VAR_isCli  *  pProcInfo,  int  iSampleTimeInMs,  unsigned  int  uiPts,  BYTE  *  pInput,  unsigned  int  inputLen,  int  iIndex_player  )
{
	int						iErr						=	-1;
	QY_MC				*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;

	//CQyMalloc				mallocObj_pkt;
	CQyMalloc				mallocObj;

	QY_PLAYER  *  pPlayer;
	pPlayer  =  getPlayerByIndex(  pProcInfo,  iIndex_player  );
	if  (  !pPlayer  )  return  -1;

	//
	if (inputLen == 0) {
		return  -1;
	}
	if  (  inputLen  >  pProcInfo->cfg.uiBufSize_myPlayAudioData  )  {
		goto  errLabel;
	}


	if (pProcInfo->cfg.b_useQ2_toPlayA) {

		myPLAY_AUDIO_data		pkt;	//  2015/02/14
		myPLAY_AUDIO_DATA* p;
		int						len;

		len = sizeof(myPLAY_AUDIO_DATA);//,  buf  );
		p = &pkt;//  (  myPLAY_AUDIO_DATA  *  )mallocObj_pkt.mallocf(  len  );
		if (!p)  goto  errLabel;
		memset(p, 0, len);//offsetof(  myPLAY_AUDIO_DATA,  buf  )  );
		//  p->uiTranNo_openAvDev  =  pPlayer->audio.uiTranNo;
		//
		//  2016/12/10
		unsigned  int  uiSize_dec = inputLen;
		//  2011/12/06		
		unsigned  int  uiSize_enc = 0;	//  sizeof(  TRANSFER_AUDIO_DATA  );
		uiSize_enc = 1;					//  2017/10/14. 因为uiSize_dec可能为0， 所以这里要加一个字节，避免head.uiLen为0
		//
		//  p->head.uiLen  =  dwNumBytes;
		p->head.uiLen = uiSize_dec + uiSize_enc;	//  2016/12/10
		p->uiSize_dec = uiSize_dec;					//  2016/12/10
		//
		p->head.uiSampleTimeInMs = iSampleTimeInMs;
		//  p->head.uiSampleTimeInMs_org  =  iSampleTimeInMs_org;
		p->head.uiPts = uiPts;						//  2017/10/13

		//
		//
		if (!mallocObj.mallocf(p->head.uiLen))  goto  errLabel;
		if (mallocObj.get(&p->memory))  goto  errLabel;
		memcpy(p->memory.m_pBuf, pInput, p->uiSize_dec);  //  p->head.uiLen  );

		//  	
#if  0	//  2011/11/30, 不想采用触发机制了
		if (q2PostMsgAndTrigger(p, offsetof(myPLAY_AUDIO_DATA, buf), &pPlayer->audio.q2))
#else
		if (q2PostMsg(p, sizeof(myPLAY_AUDIO_DATA), &pPlayer->audio.q2, _T("playAudioData")))
#endif
		{
			//  if  (  !pQyMc->bUseDirectSound_toPlay  )  			
			if (pQyMc->uiAPlayType == CONST_aPlayType_wave)
			{
				PostThreadMessage(pPlayer->audio.dwThreadId, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);
			}
			goto  errLabel;
		}
		mallocObj.detach();

		//  2010/05/03
		//  if  (  !pQyMc->bUseDirectSound_toPlay  )  		
		if (pQyMc->uiAPlayType == CONST_aPlayType_wave)
		{
			PostThreadMessage(pPlayer->audio.dwThreadId, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);
		}
	}
	else {
		 //
		HeadData_playA headData;
		memset(&headData, 0, sizeof(HeadData_playA));
		headData.uiPts = uiPts;
		headData.uiSize_dec = inputLen;
		if (0 != pPlayer->audio.qBuf2->q2PostMsg(&headData, pInput, inputLen,  _T(  "playAudioData"  )))
		{
			goto errLabel;
		}

	}

    iErr  =  0;
errLabel:

	//p->memory.m_pBuf  =  NULL;		//  shall be reset

	return  iErr;

}



 //
 int  playLocalAudioData(  MC_VAR_isCli  *  pProcInfo,  int  iTaskId,  unsigned  int  uiTranNo,  WAVEFORMATEX  *  pWf,  int  iSampleTimeInMs,  BYTE  *  pInput,  unsigned  int  inputLen,  unsigned  int  uiCapType,  int  iIndex_capAudio  )
{
	int						iErr			=	-1;
	QY_MC				*	pQyMc			=	(  QY_MC  *  )pProcInfo->pQyMc;
	
	if  (  !pWf  )  return  -1;
	if  (  !uiTranNo  )  {
		traceLogA(  (char*)  "playLocalAudioData failed, uiTranNo is 0"  );
		return  -1;
	}

	QY_SHARED_OBJ		*	pSharedObj		=	NULL;
	CAP_procInfo_bmpU	*	pCapBmp			=	NULL;
	CAP_procInfo_audioU	*	pCapAudio		=	NULL;
	QY_PLAYER			*	pPlayer			=	NULL;

	pCapAudio  =  getCapAudioBySth(  pProcInfo,  iIndex_capAudio,  0  );
	if  (  !pCapAudio  )  goto  errLabel;
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pCapAudio->common.iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	pCapBmp  =	getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
		
	SHARED_OBJ_USR* pSharedObjUsr; pSharedObjUsr = getSharedObjUsr(pSharedObj, pSharedObj->iIndex_curUsr);
	if  (  !pSharedObjUsr  )  goto  errLabel;

	//
	pPlayer  =  getPlayerByIndex(  pProcInfo,  pSharedObj->iIndex_localPlayer  );
	if  (  pPlayer  )  {
		if  (  pPlayer->iTaskId  !=  iTaskId
			||  pPlayer->idInfo_recorder.ui64Id  !=  0
			||  pPlayer->audio.uiTranNo  !=  uiTranNo  )
		{	
			traceLogA(  (char*)  "playLocalAudioData: not correct player"  );
			//
			pSharedObj->iIndex_localPlayer  =  -1;
			pPlayer  =  NULL;
		}
	}

	if  (  !pPlayer  )  {
		int						k;

		for  (  k  =  0;  k  <  pProcInfo->av.usCnt_players;  k  ++  )  {
			 
			 //  2015/05/22
			 if  (  pProcInfo->av.pPlayers[k].iTaskId  !=  iTaskId  )  continue;		//  2010/09/07

			 //
			 if  (  pProcInfo->av.pPlayers[k].idInfo_recorder.ui64Id  ==  0
			 	 &&  pProcInfo->av.pPlayers[k].audio.uiTranNo  ==  uiTranNo  )  		 
			 {
				 if  (  !pCapBmp  )  break;
				
#if  0
				 if  (  pProcInfo->av.pPlayers[k].idInfo_recorder.ui64Id  ==  0
					 &&  pProcInfo->av.pPlayers[k].video.uiTranNo  ==  pCapBmp->common.compressVideo.uiTranNo_openAvDev  )
				 {
					 break;				 		 
				 }
#endif
				 //  2010/09/04
				 if  (  pProcInfo->av.pPlayers[k].idInfo_recorder.ui64Id  ==  0
					 &&  pProcInfo->av.pPlayers[k].video.uiTranNo  ==  pSharedObjUsr->uiTranNo_openAvDev_v  )
				 {
					 break;				 		 
				 }

			 }
		}

		if  (  k  <  pProcInfo->av.usCnt_players  )  {
			pSharedObj->iIndex_localPlayer  =  k;
			pPlayer  =  getPlayerByIndex(  pProcInfo,  k  );
			if  (  !pPlayer  )  goto  errLabel;
		}
	}

	//  
	if  (  !pPlayer  ||  !pPlayer->audio.bRunning  )  {


		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playLocalAudioData : me,%d,%d apply for player"  ),  uiTranNo,  0  );

		//  ÕâÀï×é°ü·¢¸øÖ÷Ïß³Ì¡£
		MIS_MSG_applyForPlayer_qmc	msg;
		memset(  &msg,  0,  sizeof(  msg  )  );
		msg.uiType  =  CONST_misMsgType_applyForPlayer_qmc;
		msg.iTaskId  =  iTaskId;
		//  msg.idInfo_recorder.ui64Id  =  0;
		msg.audio.uiTranNo  =  uiTranNo;
		//  msg.audio.usIndex  =  0;
		memcpy(  &msg.audio.ah,  pWf,  min(  sizeof(  msg.audio.ah  ),  sizeof(  WAVEFORMATEX  )  +  pWf->cbSize  )  );
		//
		memcpy(  &msg.audio.playCfg,  &pCapAudio->common.compressAudio.compressor.playCfg,  sizeof(  msg.audio.playCfg  )  );	//  2012/01/04

		//
		if  (  pCapBmp  )  {
			//  msg.video.uiTranNo  =  pCapBmp->common.compressVideo.uiTranNo_openAvDev;
			msg.video.uiTranNo  =  pSharedObjUsr->uiTranNo_openAvDev_v;						//  2010/09/04
			//  msg.video.usIndex  =  0;
			//
			//  memcpy(  &msg.video.vh.bih,  &pCapBmp->common.compressVideo.vh_decompress.bih,  sizeof(  msg.video.vh.bih  )  );
			if  (  getBih_capBmpToPlay(  pCapBmp,  &msg.video.vh.bih  )  )  goto  errLabel;
			//
			//msg.video.ucbFlippedImg  =  pCapBmp->common.compressVideo.compressor.common.ucbOutputFlippedImg;	//  2011/12/11
			//
			msg.video.usFps  =  pCapBmp->common.compressVideo.compressor.common.usMaxFps_toShareBmp;		//  2015/02/20
		}

		//					  
		qPostMsg(  &msg,  sizeof(  msg  ),  &pQyMc->gui.processQ,  _T(  "playLocalAudioData"  ));
			
		PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    
		iErr  =  0;  goto  errLabel;
	}			

	if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewAudioStatus  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playLocalAudioData : me, %d,%d plays"  ),  uiTranNo,  0  );
	}

	{
		  CQyMalloc				mallocObj;
		  myPLAY_AUDIO_DATA		pkt;
		  myPLAY_AUDIO_DATA  *  pPkt=  &pkt;			//  =	(  myPLAY_AUDIO_DATA  *  )mallocObj.malloc(  offsetof(  myPLAY_AUDIO_DATA,  buf  )  +  len  );
		  if  (  !pPkt  )  goto  errLabel;
		  myPLAY_AUDIO_DATA  *  p  =  pPkt;
		  
		  if  (  inputLen  >  pProcInfo->cfg.uiBufSize_myPlayAudioData  )  {		
			  goto  errLabel;	
		  }

		  //
		  memset(  pPkt,  0,  sizeof(  myPLAY_AUDIO_DATA  )  );
		  pPkt->head.idInfo.ui64Id  =  0;
		  pPkt->head.uiSampleTimeInMs  =  iSampleTimeInMs;

		  //
		  unsigned  int  uiSize_dec  = inputLen;
		  unsigned  int  uiSize_enc  =  0;
		  //
		  pPkt->head.uiLen  =  uiSize_dec  +  uiSize_enc;
		  pPkt->uiSize_dec  =  uiSize_dec;
		  //
		  	if  (  !mallocObj.mallocf(  p->head.uiLen  )  )  goto  errLabel;
			if  (  mallocObj.get(  &p->memory  )  )  goto  errLabel;	
			memcpy(  p->memory.m_pBuf,  pInput,  p->uiSize_dec  );  //  p->head.uiLen  );

		 

		//
		/*
		if  (  pPkt->head.uiSampleTimeInMs  <  pPlayer->audio.m_var.uiSampleTimeInMs  )  {		//  move backward the media file. need to clear up the old media data
			emptyQ2(  &pPlayer->audio.q2  );
			pPlayer->audio.m_var.uiSampleTimeInMs  =  0;
		}
		if  (  pPkt->head.uiSampleTimeInMs  >  pPlayer->audio.m_var.uiSampleTimeInMs_expectedToRecv  +  3000  )  {		//  move forward the media file. need to clear up the old media data
			traceLogA(  (char*)  "pPkt->uiSampleTimeInMs %d, expected %d.",  pPkt->head.uiSampleTimeInMs,  pPlayer->audio.m_var.uiSampleTimeInMs_expectedToRecv  );
			emptyQ2(  &pPlayer->video.q2  );
			pPlayer->video.m_var.uiSampleTimeInMs_newRecvd  =  0;
			emptyQ2(  &pPlayer->audio.q2  );
			pPlayer->audio.m_var.uiSampleTimeInMs  =  0;
		}
		//
		if  (  pPkt->head.uiSampleTimeInMs  )  {
			if  (  pPlayer->audio.waveFormatEx.nAvgBytesPerSec  )  {
				pPlayer->audio.m_var.uiSampleTimeInMs_expectedToRecv  =  (  unsigned  int  )(  pPkt->head.uiSampleTimeInMs  +  pPkt->head.uiLen  *  1000.  /  pPlayer->audio.waveFormatEx.nAvgBytesPerSec  );
			}
		}
		*/

		DWORD	dwTickCnt_now  =  GetTickCount(  );

		//  2009/04/06
		pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd  =  pPkt->head.uiSampleTimeInMs;
		pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_newRecvd  =  dwTickCnt_now;

		if  (  pPkt->head.uiSampleTimeInMs  &&  getQ2Nodes_toGetMsg(  &pPlayer->audio.q2  )  >  1  )  {
			int	iAbs  =  abs(  (  int  )(  pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_newRecvd  -  pPlayer->audio.m_var.dwTickCnt_uiSampleTimeInMs_syncRecv  )  );	//  The iAbs is needed because uiSampleTimeInMs may be a future value.
			if  (  pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd  +  iAbs  <  pPlayer->audio.m_var.uiSampleTimeInMs  )  {			//  move backward the media file. need to clear up the old media data
				traceLogA(  (char*)  "pkt.uiSampleTimeInMs %d + iAbs %d < player.%d. trigger to empty old data",  pPkt->head.uiSampleTimeInMs,  iAbs,  pPlayer->audio.m_var.uiSampleTimeInMs  );
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "playAudioData: pkt.uiSampleTimeInMs %d + abs %d < player.%d. trigger to empty old data"  ),  pPlayer->audio.m_var.uiSampleTimeInMs_newRecvd,  iAbs,  pPlayer->audio.m_var.uiSampleTimeInMs  );

				q2TriggerToProcess(  &pPlayer->audio.q2  );
			}
			if  (  pPlayer->audio.m_var.uiSampleTimeInMs  )  {
				if  (  pPkt->head.uiSampleTimeInMs  >  pPlayer->audio.m_var.uiSampleTimeInMs  +  10000  )  {	//  2009/05/25. too old audio data
					traceLogA(  (char*)  "pkt.uiSampleTimeInMs %d > player.%d  +  10000. trigger to empty old data",  pPkt->head.uiSampleTimeInMs,  pPlayer->audio.m_var.uiSampleTimeInMs  );
					q2TriggerToProcess(  &pPlayer->audio.q2  );
				}
			}
			//  2012/01/26
			if  (  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  )
			{	//  2009/06/03
				TCHAR  tBuf[256]  =  _T(  ""  );
				int  nWaitingInMs_audio  =  MACRO_getnWaitingInMs_audio_syncRecv(  pPlayer->audio,  dwTickCnt_now  );
				if  (  nWaitingInMs_audio  >  0  &&  nWaitingInMs_audio  >  pPlayer->audio.playCfg.usMaxTimeInMsToPlay  +  pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying  )  {

					#if  10
						_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "chkFromPlayerIndex_a: nWaitingInMs_audio %d > uiMaxTimeToPlay %d + playing %d. trigger to empty old data"  ),  nWaitingInMs_audio,  pPlayer->audio.playCfg.usMaxTimeInMsToPlay,  pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying  );
						#ifdef  __DEBUG__
								traceLogA(  (char*)  "%S",  tBuf  );
						#endif
						qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
					#endif

					#ifdef  __DEBUG__
							#if  0
								if  (  pPlayer->audio.playCfg.uiMaxTimeInMsToPlay  !=  pTask->audio.playCfg.uiMaxTimeInMsToPlay  )  {
									traceLogA(  (char*)  "playAudioData err: player.audio.m_var.uiMaxTimeInMsToPlay != task.audio.playCfg.*"  );
								}
								if  (  pPlayer->audio.playCfg.uiMaxTimeInMsToBeRemoved  !=  pTask->audio.playCfg.uiMaxTimeInMsToBeRemoved  )  {
									traceLogA(  (char*)  "playAudioData err: player.audio.m_var.uiMaxTimeInMsToBeRemoved != task.audio.playCfg.*"  );
								}
							#endif
					#endif

					q2TriggerToProcess(  &pPlayer->audio.q2  );
				}
			}
		}

		//
#if  0	//  2011/11/30, 不想采用触发机制了
		if  (  q2PostMsgAndTrigger(  pPkt,  pktLen,  &pPlayer->audio.q2  )  )  
#else
		if  (  q2PostMsg(  pPkt,  sizeof(  myPLAY_AUDIO_DATA  ),  &pPlayer->audio.q2,  _T(  "playLocalAudioData 1"  )))
#endif
		{
			//  if  (  !pQyMc->bUseDirectSound_toPlay  ) 				
			if  (  pQyMc->uiAPlayType  ==  CONST_aPlayType_wave  )  //  2017/02/16 				
			{			
				PostThreadMessage(  pPlayer->audio.dwThreadId,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
			}
			goto  errLabel;
		}
		mallocObj.detach(  );

	}
	
	//  2010/05/03
	//  if  (  !pQyMc->bUseDirectSound_toPlay  ) 		
	if  (  pQyMc->uiAPlayType  ==  CONST_aPlayType_wave  ) 		
	{
		PostThreadMessage(  pPlayer->audio.dwThreadId,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
	}
    iErr  =  0;
errLabel:
	return  iErr;
}









 //////////
#if  0
 int  old_transformTaskAudioPkt(  QY_TRANSFORM  *  pTransform,  MIS_MSG_TASK  *  pMsgTask,  TRANSFER_AUDIO_DATA  *  pReq,  PKT_info_toDec  *  pPktInfo_toDec,  int  index_pMems_from,  int  index_activeMems_from,  myPLAY_AUDIO_DATA	*	pPkt_dec,  MIS_MSGU  *  pMsgBuf  )
{
	int						iErr				=	-1;

	MC_VAR_isCli			*	pProcInfo			=	(  MC_VAR_isCli  *  )pTransform->pProcInfo;
	MSGR_ADDR			*	pAddr				=	pTransform->pAddr_logicalPeer;
	int						iTaskId				=	pTransform->iTaskId;  
	AV_TRAN_INFO		*	pTranInfo_unused	=	(  AV_TRAN_INFO  *  )pTransform->pTranInfo_unused;
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pTransform->pTask;
	//  myPLAY_AUDIO_DATA	*	pPkt_dec			=	(  myPLAY_AUDIO_DATA  *  )&pTransform->audio.pkt_dec;
	//  MIS_MSG_TASK		*	pMsgTask_toCompress	=	(  MIS_MSG_TASK  *  )pTransform->audio.pMsgTask_toCompress_videoConference;

	
	QY_MC				*	pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;
	MIS_CNT				*	pMisCnt				=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
	if  (  !pMisCnt  )  return  -1;
	int						tmpiRet				=	0;
	char					timeBuf[32]			=	"";
	TCHAR					tHintBuf[256]		=	_T(  ""  );
	if  (  !pReq  ||  !pReq->usCnt  ||  pReq->usCnt  >  mycountof(  pReq->mems  )  )  return  -1;
	if  (  !pPktInfo_toDec  )  return  -1;

	//
	CUS_MODULES *pCusModules=(CUS_MODULES * )pProcInfo->getCusModules();
	if( !pCusModules ) return -1;

	//
	TASK_AV_FROM		*	pFrom				=	NULL;

#if  0
	if  (  index_pMems_from  <  0  ||  index_pMems_from  >=  pTask->usCntLimit_mems_from  )  return  -1;
	if  (  pTask->ucbVideoConferenceStarter  )  {
		if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTask->usCntLimit_activeMems_from  )  return  -1;
	}
	pFrom  =  &pTask->pMems_from[index_pMems_from];
#endif
	pFrom  =  getTaskAvFrom(  pTransform,  index_pMems_from,  index_activeMems_from,  _T(  "transformTaskAudio"  )  );
	if  (  !pFrom  )  return  -1;

	//
	int						index				=	index_pMems_from;
	DWORD					curTickCnt			=	GetTickCount(  );	

	TCHAR					where_showInfo[32]	=	_T(  ""  );		_sntprintf(  where_showInfo,  mycountof(  where_showInfo  ),  _T(  "transA %d"  ),  pTransform->index_activeMems_from  );

	if  (  !pAddr  )  return  -1;
	
	if  (  pMsgTask->tStartTime  <  pFrom->tStartTime_task  )  {
		_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s tStartTime < tStartTime_task. skipped."  ),  tHintBuf  );  goto  errLabel;
	}
	//
#if  0  //  2017/10/14
	if  (  pMsgTask->dwTickCnt_start  )  {	//  2009/03/22
		int  iElapse  =  curTickCnt  -  pMsgTask->dwTickCnt_start;
		if  (  iElapse  >  pProcInfo->cfg.policy.usTimeoutInMsToSwitch_rt  )  {
			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%I64u,  %dms elapsed, start %u, msg skipped"  ),  pFrom->idInfo.ui64Id,  iElapse,  pMsgTask->dwTickCnt_start  );
			goto  errLabel;
		}
	}
#endif

	//
	if  (  pTransform->audio.ucbInited  )  {
		if  (  pTransform->audio.index_pMems_from  !=  index_pMems_from
			||  pTransform->audio.idInfo.ui64Id  !=  pFrom->idInfo.ui64Id				
			||  pTransform->audio.ta.uiTranNo_openAvDev  !=  pFrom->audio.ta_recvd.uiTranNo_openAvDev  
			||  pTransform->audio.status.ucbDecFailed			//  2012/03/19
				)  
		{
			traceLogA(  (char*)  "procTaskAudio: transform.index_pMems_from %d, uiTranNo_openAvDev %d != %d, %d",  pTransform->audio.index_pMems_from,  pTransform->audio.ta.uiTranNo_openAvDev,  index_pMems_from,  pFrom->audio.ta_recvd.uiTranNo_openAvDev  );
			exitTaskAvFrom_audio(  pProcInfo,  pTransform  );			
		}
		}
	else  {
		  exitTaskAvFrom_audio(  pProcInfo,  pTransform  );			
	}

	//  2009/04/13
	if  (  !pTransform->audio.ucbInited  )  {		
		if  (  initTaskAvFrom_audio(  pProcInfo,  pFrom,  index_pMems_from,  pTransform  )  )  goto  errLabel;
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskAudio: initTaskAvFrom_audio %d"  ),  index_pMems_from  );
	}
	if  (  !pTransform->audio.ucbInited  )  {
		traceLogA(  (char*)  "procTaskAudio failed: ³õÊ¼»¯Î´Íê³É¡£"  );
		goto  errLabel;
	}

	//  check
	if  (  pMsgTask->data.route.idInfo_from.ui64Id  !=  pFrom->idInfo.ui64Id
		||  pReq->uiTranNo_openAvDev  !=  pFrom->audio.ta_recvd.uiTranNo_openAvDev  )  
	{
		traceLogA(  (char*)  "procTaskAudio: idInfo_from %I64u, audioData.uiTranNo %d !=  pFrom %I64u, %d",  pMsgTask->data.route.idInfo_from.ui64Id,  pReq->uiTranNo_openAvDev,  pFrom->idInfo.ui64Id,  pFrom->audio.ta_recvd.uiTranNo_openAvDev  );  
		goto  errLabel;
	}


	if  (  !pTask->ucbVideoConference  )  {
		//
		pFrom->audio.usCnt_pkts  ++  ;
		if  (  pReq->tLastTime_showFrameInfo_020534  )  {
			if  (  !pFrom->audio.tLastTime_showFrameInfo_020534  )  {	//  ÕâÊÇÔÚµÚÒ»´ÎµÄÊ±ºò£¬Ã»¿ªÊ¼¼ÆÊý£¬ÏìÓ¦OK¡£
				pReq->tmpInternal.result.usRespCode  =  CONST_qyRc_ok;

				_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "×¼±¸Ö¡¼ÆÊý."  )  );

				//  pFrom->audio.uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;	//  2013/08/04. 不能修改pFrom->audio.uiTranNo_openAvDev
				}
			else  if  (  pFrom->audio.ta_recvd.uiTranNo_openAvDev  ==  pReq->uiTranNo_openAvDev
						&&  pFrom->audio.tLastTime_showFrameInfo_020534  ==  pReq->tLastTime_showFrameInfo_020534  
							&&  pFrom->audio.usCnt_pkts  >=  pReq->usCnt_pkts  )  
					{
						pReq->tmpInternal.result.usRespCode  =  CONST_qyRc_ok;

						_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "pkts %d, Ò»ÖÂ."  ),  pReq->usCnt_pkts  );
					}
			else  {
				  CQyString	str;
				  CQyString	str_expected;

				  pReq->tmpInternal.result.usRespCode  =  CONST_qyRc_err;

				  getTimelStr(  pFrom->audio.tLastTime_showFrameInfo_020534,  timeBuf,  mycountof(  timeBuf  )  );  str  =  CQyString(  timeBuf  );
				  getTimelStr(  (  time_t  )pReq->tLastTime_showFrameInfo_020534,  timeBuf,  mycountof(  timeBuf  )  );  str_expected  =  CQyString(  timeBuf  );
				  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "Error: ( %d, %s, %d pkts ) != ÆÚÍû  ( %d, %s, %d pkts )."  ),  pFrom->audio.ta_recvd.uiTranNo_openAvDev,  str,  pFrom->audio.usCnt_pkts,  pReq->uiTranNo_openAvDev,  str_expected,  pReq->usCnt_pkts  );

				  //  pFrom->audio.uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;			
			}
			pReq->tmpInternal.result.usCnt_pkts  =  pFrom->audio.usCnt_pkts;	//  Òª½«·¢ËÍµÄÖ¡Êý·¢»Ø·¢ËÍ·½¡£

			pFrom->audio.usCnt_pkts  =  0;
			pFrom->audio.tLastTime_showFrameInfo_020534  =  pMsgTask->tStartTime;
		}
	
	}

	//  ÏÂÃæ¿ªÊ¼½âÑ¹Ëõ
	DWORD							dwBytes_pcm;
	TRANSFER_AUDIO_dataMemHead	*	pMem;
	int								iPos;
	WAVEFORMATEX				*	pWfx_toPlay  =  &pTransform->audio.ta.ah_decompress.wfx;


	//  TRANSFER_AUDIO_DATA			*	pReq_toCompress;	pReq_toCompress  =  NULL;
	
	/*
	if  (  pTask->ucbVideoConferenceStarter  )  {
		if  (  !pMsgTask_toCompress  )  goto  errLabel;
		pReq_toCompress  =  (  TRANSFER_AUDIO_DATA  *  )pMsgTask_toCompress->data.buf;

		pMsgTask_toCompress->uiType  =  CONST_misMsgType_task;
		//
		memset(  pReq_toCompress,  0,  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  );
		pReq_toCompress->uiType =  pReq->uiType;
		pReq_toCompress->uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;
	}
	*/

	//  memset(  pFrom->audio.pDecompressBuf_transferAudioData,  0,  offsetof(  TRANSFER_AUDIO_DATA,  mems  )  );
	//  pFrom->audio.pDecompressBuf_transferAudioData->uiType  =  pReq->uiType;
	//  pFrom->audio.pDecompressBuf_transferAudioData->uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;

	if  (  !pReq->usCnt  ||  pReq->usCnt  >  mycountof(  pReq->mems  )  )  {
		#ifdef  __DEBUG__
				traceLogA(  (char*)  "procTaskAudio failed: pReq->usCnt %d error",  pReq->usCnt  );
		#endif
		goto  errLabel;
	}


	//for  (  iPos  =  0,  i  =  0;  i  <  pReq->usCnt;  iPos  +=  pReq->mems[i].uiLen,  i  ++  )  
	for  (  int  kk  =  0;  kk  <  1;  kk  ++  )
	{
		if  (  !pPktInfo_toDec->bGot_msg  )  goto  errLabel;
		if  (  !pPktInfo_toDec->info.bGot_pkt  )  goto  errLabel;
		//
		//  2017/10/14
		iPos  =  pPktInfo_toDec->info.iPos;
		if  (  pPktInfo_toDec->info.index_mems  <0  ||  pPktInfo_toDec->info.index_mems  >=  pReq->usCnt  )  goto  errLabel;
		int								i;
		i  =  pPktInfo_toDec->info.index_mems;

		 //
		 pMem  =  &pReq->mems[i];

		 if  (  iPos  +  pMem->uiLen  >  pReq->uiLen  )  {
			 #ifdef  __DEBUG__
					 traceLogA(  (char*)  "procTasAudio: "  );
			 #endif
			 goto  errLabel;
		 }
		 if  (  !pMem->uiLen  )  {
			 #ifdef  __DEBUG__
					 traceLogA(  (char*)  "procTaskAudio warning: mem.uiLen is 0"  );
			 #endif
			 continue;
		 }
		 if  (  pMem->uiTranNo_openAvDev  )  {	//  2013/08/04. 会议时,参会人如果第2次进入会议,那么需要区分前后2次的音频流是不同的,靠的就是tn
			 if  (  pMem->uiTranNo_openAvDev  !=  pFrom->audio.ta_recvd.uiTranNo_openAvDev  )  {
				 #ifdef  __DEBUG__
						 traceLog((TCHAR*)  _T(  "transformTaskAudio: err, mem.uiTranNo_openAvDev %d != from.audio. %d. skipped"  ),  pMem->uiTranNo_openAvDev,  pFrom->audio.ta_recvd.uiTranNo_openAvDev  );
				 #endif
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "transformTaskAudio: err, %I64u, mem.uiTranNo_openAvDev %d != from.audio. %d. skipped"  ),  pMem->idInfo.ui64Id,  pMem->uiTranNo_openAvDev,  pFrom->audio.ta_recvd.uiTranNo_openAvDev  );
				 continue;
			 }
		 }

		 //
#ifdef  __DEBUG__
		#if  0
		 TCHAR  tBuf[128];
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u, pts %d"  ),  pFrom->idInfo.ui64Id,  pMem->uiPts  );
		 showInfo_open0(  0,  0,  tBuf  );
		#endif
#endif

		 //
		 //memset(  pPkt_dec,  0,  offsetof(  myPLAY_AUDIO_data,  buf  )  );
		 memset(  &pPkt_dec->head,  0,  sizeof(  pPkt_dec->head  )  );	//  2015/02/14
		 if  (  pMem->idInfo.ui64Id  )  {
			 pPkt_dec->head.idInfo.ui64Id  =  pMem->idInfo.ui64Id;
			 if  (  pPkt_dec->head.idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id  )  pPkt_dec->head.tmpInternal.uiTranNo_org  =  pReq->uiTranNo_openAvDev;
			 else  pPkt_dec->head.tmpInternal.uiTranNo_org  =  0;
			 }
		 else  {
			   pPkt_dec->head.idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;
			   pPkt_dec->head.tmpInternal.uiTranNo_org  =  pReq->uiTranNo_openAvDev;
		 }				 
		 //  2017/10/13
		 pPkt_dec->head.uiPts  =  pMem->uiPts;

		 //  2015/05/19
		 if  (  pTask->saveVideo.ucbSaveVideo_req  )  {						
			 //
			 //(  BYTE  *  )pReq->buf  +  iPos,  pMem->uiLen,  pMem->uiSampleTimeInMs,  pMem->ui_rtTimeLen
			 //
			 char  *  data  =  pReq->buf  +  iPos;
			 int  len  =  pMem->uiLen;
			 postAPktToSave(  CONST_uiTransformType_dec,  pTransform,  index_pMems_from,  pMem->uiSampleTimeInMs,  0,  data,  len  );  										   
		 }



		 //
		 if  (  pTransform->audio.ta.compressor.common.ucCompressors  ==  CONST_audioCompressors_acm  )  {

#ifdef  __SUPPORT_acmToDec__
			 dwBytes_pcm  =  pMem->uiLen  *  pTransform->audio.pWf_pcm->nAvgBytesPerSec  /  pTransform->audio.pWf_compress->nAvgBytesPerSec;
			 if  (  !pTransform->audio.pBuf_pcm  ||  pTransform->audio.dwBufSize_pcm  <=  dwBytes_pcm  )  {
				 if  (  pTransform->audio.pBuf_pcm  )  {
					 free(  pTransform->audio.pBuf_pcm  );  pTransform->audio.pBuf_pcm  =  NULL;
				 }
				 dwBytes_pcm  =  dwBytes_pcm  *  3  /  2  +  256;
				 if  (  !(  pTransform->audio.pBuf_pcm  =  (  char  *  )mymalloc(  dwBytes_pcm  )  )  )  {
					 traceLogA(  (char*)  "procTaskAudio: malloc for pBuf_pcm failed."  );
					 goto  errLabel;
				 }
				 pTransform->audio.dwBufSize_pcm  =  dwBytes_pcm;
			 }

			 //
			 //  pPkt_dec->head.uiSampleTimeInMs  =  pMem->uiSampleTimeInMs;
			 pPkt_dec->head.uiLen  =  pProcInfo->cfg.uiBufSize_myPlayAudioData;	//  mycountof(  pPkt_dec->buf  );

			 if  (  convertAudio(  pTransform->audio.u.acm.hstr1,  pTransform->audio.u.acm.hstr2,  pTransform->audio.pWf_compress,  (  BYTE  *  )pReq->buf  +  iPos,  pMem->uiLen,  pTransform->audio.pWf_pcm,  (  BYTE  *  )pTransform->audio.pBuf_pcm,  pTransform->audio.dwBufSize_pcm,  pTransform->audio.pWf_decompress,  (  BYTE  *  )pPkt_dec->memory.m_pBuf,  (  DWORD  *  )&pPkt_dec->head.uiLen  )  )  goto  errLabel;

			 //  pFrom->audio.pDecompressBuf_transferAudioData->usCnt  ++  ;
			 
			 //  pWfx_toPlay  =  pTransform->audio.pWf_decompress;
			 pPkt_dec->head.uiSampleTimeInMs  =  pMem->uiSampleTimeInMs;
			 #ifdef  __DEBUG__
					 //  traceLogA(  (char*)  "transformA: uiSampleTimeInMs %d",  pPkt_dec->head.uiSampleTimeInMs  );
			 #endif

#if  0
			   playAudioData(  pProcInfo,  pMisCnt,  pTransform->iTaskId,  pTask,  pWfx_toPlay,  pPkt_dec,  pFrom  );
#else
			 if  (  !chkFromPlayerIndex_a(  CONST_uiTransformType_dec,  pTransform,  pPkt_dec,  0  )  )  {
				 playAudioData(  pProcInfo,  pPkt_dec->head.uiSampleTimeInMs,  pPkt_dec->head.uiPts,  (  BYTE  *  )pPkt_dec->memory.m_pBuf,  pPkt_dec->head.uiLen,  pTransform->iIndex_player  );
			 }
#endif

			 if  (  !pTask->ucbVideoConferenceStarter  )  continue;

			 continue;

#else
				   MY_DMO_INFO	*	pDmoInfo	=	NULL;
			       int				index_dmo  =  0;					   
				   if  (  pFrom->ucbVideoConferenceStarter  )  index_dmo  =  pMem->usIndex;

				   pDmoInfo  =  &pTransform->audio.u.dmo;
				   pDmoInfo->pDebugStep  =  &pTransform->audio.debugStep;

				   //  pWfx_toPlay  =  &pFrom->audio.ah_decompress_recvd.wfx;
				   pPkt_dec->head.uiSampleTimeInMs  =  pMem->uiSampleTimeInMs;

				   if  (  chkFromPlayerIndex_a(  pProcInfo,  pMisCnt,  pTransform->iTaskId,  pTask,  pWfx_toPlay,  pPkt_dec,  pFrom  )  )  continue;
				   if  (  pDmoInfo->iIndex_player  !=  pFrom->iIndex_player  )  pDmoInfo->iIndex_player  =  pFrom->iIndex_player;

	   			   #ifdef  __DEBUG__
						   if  (  pProcInfo->cfg.debugStatusInfo.ucbPrint_a_in  )  {
							   traceLogA(  (char*)  "transformA: uiSampleTimeInMs %d. req.usCnt %d, req.len %d",  pMem->uiSampleTimeInMs,  pReq->usCnt,  pReq->uiLen  );
						   }
				   #endif

				   if  (  decompressAudio_filterGraph(  pDmoInfo,  &pFrom->audio.ah_compress_recvd,  (  BYTE  *  )pReq->buf  +  iPos,  pMem->uiLen,  pMem->uiSampleTimeInMs,  pMem->ui_rtTimeLen  )  )  goto  errLabel;

				   //  if  (  pFrom->iDiffInMs_tStartAudios[index_dmo]  !=  pDmoInfo->iDiffInMs_tStartStream  )  pFrom->iDiffInMs_tStartAudios[index_dmo]  =  pDmoInfo->iDiffInMs_tStartStream;

#endif
			 }
		 else  if  (  pTransform->audio.ta.compressor.common.ucCompressors  ==  CONST_audioCompressors_dmo  )  {
				   MY_DMO_INFO	*	pDmoInfo	=	NULL;
			       int				index_dmo  =  0;
#if  0
				   if  (  pFrom->ucbVideoConferenceStarter  )  index_dmo  =  pMem->usIndex;
#endif

				   pDmoInfo  =  &pTransform->audio.u.dmo;

				   //  2011/07/03
				   //  if  (  decompressAudio_dmo(  pDmoInfo,  &pFrom->audio.ah_compress_recvd,  (  BYTE  *  )pReq->buf  +  iPos,  pMem->uiLen,  pMem->uiSampleTimeInMs,  pMem->ui_rtTimeLen  )  )  goto  errLabel;
				   if  (  decompressAudio_dmo(  pDmoInfo,  &pTransform->audio.ta.ah_compress,  (  BYTE  *  )pReq->buf  +  iPos,  pMem->uiLen,  pMem->uiSampleTimeInMs,  pMem->ui_rtTimeLen  )  )  {
					   //
					   //  此标志位表明需要重新初始化transform. 2012/03/19
					   pTransform->audio.status.ucbDecFailed  =  TRUE;
					   _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s %s"  ),  tHintBuf,  _T(  "decompressAudio_dmo failed."  )  );
					   //
					   goto  errLabel;
				   }

				   if  (  pFrom->iDiffInMs_tStartAudios[index_dmo]  !=  pDmoInfo->iDiffInMs_tStartStream  )  pFrom->iDiffInMs_tStartAudios[index_dmo]  =  pDmoInfo->iDiffInMs_tStartStream;

				   int							j;
				   for  (  j  =  0  ;  ;  j  ++  )  {
					    				   		
						pPkt_dec->head.uiSampleTimeInMs  =  pMem->uiSampleTimeInMs;
						pPkt_dec->head.uiLen  =  pProcInfo->cfg.uiBufSize_myPlayAudioData;	//  mycountof(  pPkt_dec->buf  );

						if  (  getDmoOutputByIndex(  pDmoInfo,  j,  (  BYTE  *  )pPkt_dec->memory.m_pBuf,  &pPkt_dec->head.uiLen,  &pPkt_dec->head.uiSampleTimeInMs,  &pPkt_dec->head.ui_rtTimeLen  )  )  break;

						//
						pFrom->iSampleTimeInMs_audios[index_dmo]  =  pPkt_dec->head.uiSampleTimeInMs;		//  2010/06/20

						//
						//  pWfx_toPlay  =  &pFrom->audio.ah_decompress_recvd.wfx;
						//  playAudioData(  pProcInfo,  pMisCnt,  pTransform->iTaskId,  pTask,  pWfx_toPlay,  pPkt_dec,  pFrom  );
						if  (  !chkFromPlayerIndex_a(  CONST_uiTransformType_dec,  pTransform,  pPkt_dec,  0  )  )  {
							playAudioData(  pProcInfo,  pPkt_dec->head.uiSampleTimeInMs,  pPkt_dec->head.uiPts,  (  BYTE  *  )pPkt_dec->memory.m_pBuf,  pPkt_dec->head.uiLen,  pTransform->iIndex_player  );
						}

						if  (  !pTask->ucbVideoConferenceStarter  )  continue;
						
						continue;
				   }

				   }
		 else  {  
			   CUS_MODULE_U	*	pModule	=	NULL;
			   /*
			   switch  (  pTransform->audio.ta.compressor.common.ucCompressors  )  {
					   case  CONST_audioCompressors_ipp:
						     pModule  =  pQyMc->cusModules.pIpp;
							 break;
					   case  CONST_audioCompressors_custom:
						     pModule	=	getCusModule(  &pQyMc->cusModules,  CONST_moduleType_compress  );
							 break;
					   default:
						   traceLogA(  (char*)  "procTaskAudio: ucComprssors error, %d",  pFrom->audio.ta_recvd.compressor.common.ucCompressors  );
						   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskAudio: ucCompressors error, %d"  ),  (  int  )pFrom->audio.ta_recvd.compressor.common.ucCompressors  );
							  goto  errLabel;
							  break;
			   }
			   */
			   M_getCompressModule(pCusModules,pTransform->audio.uiModuleType_toDec,pModule );

			   if  (  !pModule
					   ||  !pModule->compress.pf_qdcDecompressAudio  
						||  !pModule->compress.pf_qdcGetOutputByIndex  )  goto  errLabel;


			   QDC_OBJ_INFO	*	pDmoInfo	=	NULL;
			   int				index_dmo  =  0;
#if  0
			   if  (  pFrom->ucbVideoConferenceStarter  )  index_dmo  =  pMem->usIndex;
#endif
#if  0
			   if  (  index_dmo  <  0  ||  index_dmo  >=  mycountof(  pTransform->audio.u.custom.qdcObjInfos  )  )  {
				   traceLogA(  (char*)  "procTaskAudio: index_dmo %d error",  index_dmo  );
				   goto  errLabel;
			   }
			   pDmoInfo  =  MACRO_getDmo(  pTransform->audio.u.custom.usCnt,  pTransform->audio.u.custom.qdcObjInfos,  index_dmo  );
			   if  (  !pDmoInfo  )  goto  errLabel;
#endif
			   pDmoInfo  =  &pTransform->audio.u.qoi.myQoi.common;	//  .qdcObjInfo;

			   //
			   if(pProcInfo->cfg.debugStatusInfo.ucb__Dump_mp3_dec__){
				   FILE * fp=fopen("c:\\tttbbb\\test\\dump_mp3_dec.mp3","ab" );
				   if(fp){
					   	byte* audio = (byte*)(pReq->buf+iPos);
						int len = (int)pMem->uiLen;
					
					   fwrite(audio,len,1,fp);
					   fclose(fp);
				   }

			   }

			   //  2011/07/03
			   //  if  (  pModule->compress.pf_qdcDecompressAudio(  pDmoInfo,  &pFrom->audio.ah_compress_recvd,  (  BYTE  *  )pReq->buf  +  iPos,  pMem->uiLen,  pMem->uiSampleTimeInMs,  pMem->ui_rtTimeLen  )  )  goto  errLabel;
			   if  (  pModule->compress.pf_qdcDecompressAudio(  pDmoInfo,  &pTransform->audio.ta.ah_compress,  (  BYTE  *  )pReq->buf  +  iPos,  pMem->uiLen,  pMem->uiSampleTimeInMs,  pMem->ui_rtTimeLen  )  <  0  )  goto  errLabel;
			   if  (  pFrom->iDiffInMs_tStartAudios[index_dmo]  !=  pDmoInfo->var.iDiffInMs_tStartAudio  )  pFrom->iDiffInMs_tStartAudios[index_dmo]  =  pDmoInfo->var.iDiffInMs_tStartAudio;

			   //  2017/10/14
			   BOOL  bDecDataGot  =  FALSE;

			   //
			   int							j;
			   for  (  j  =  0  ;  ;  j  ++  )  {
				   pPkt_dec->head.uiSampleTimeInMs  =  pMem->uiSampleTimeInMs;
				   pPkt_dec->head.uiLen  =  pProcInfo->cfg.uiBufSize_myPlayAudioData;	//  mycountof(  pPkt_dec->buf  );

				   if  (  pModule->compress.pf_qdcGetOutputByIndex(  pDmoInfo,  j,  (  BYTE  *  )pPkt_dec->memory.m_pBuf,  &pPkt_dec->head.uiLen,  &pPkt_dec->head.uiSampleTimeInMs,  &pPkt_dec->head.ui_rtTimeLen  )  )  break;

				   //
#ifdef  __DEBUG__
				   if(pProcInfo->cfg.debugStatusInfo.ucb__Dump_deced_pcm__)                   
				   {
							char fileName[MAX_PATH  +  1];
							_snprintf(  fileName,  mycountof(  fileName  ),  "%s%I64u_%s",  CONST_dump_dir,  pTransform->audio.idInfo.ui64Id,  CONST_fn_dump_deced_pcm  );
							//
							if(  pTransform->audio.tn_dumpAv!=pProcInfo->cfg.debugStatusInfo.tn_dumpAv  ) {
								pTransform->audio.tn_dumpAv=pProcInfo->cfg.debugStatusInfo.tn_dumpAv;
								//							  
								FILE  *  fp=fopen(fileName, "w"  );
								if( fp )  {
								  fclose(fp);							  
								}					
							}
							//
							FILE * fp=fopen( fileName,"ab");
							if(fp) {
								fwrite(pPkt_dec->memory.m_pBuf, (int)pPkt_dec->head.uiLen, 1, fp);
								fclose(fp);
							}
                        }
#endif



				   //
				   bDecDataGot  =  TRUE;

				   //  pWfx_toPlay  =  &pFrom->audio.ah_decompress_recvd.wfx;
				   //  playAudioData(  pProcInfo,  pMisCnt,  pTransform->iTaskId,  pTask,  pWfx_toPlay,  pPkt_dec,  pFrom  );
				   if  (  !chkFromPlayerIndex_a(  CONST_uiTransformType_dec,  pTransform,  pPkt_dec,  0  )  )  {
					   playAudioData(  pProcInfo,  pPkt_dec->head.uiSampleTimeInMs,  pPkt_dec->head.uiPts,  (  BYTE  *  )pPkt_dec->memory.m_pBuf,  pPkt_dec->head.uiLen,  pTransform->iIndex_player  );
				   }

				   if  (  !pTask->ucbVideoConferenceStarter  )  continue;

				   //  addToReq_toCompress_audio(  pProcInfo,  pTranInfo,  pTask,  index_activeMems_from,  pPkt_dec,  pMsgTask_toCompress  );

				   continue;
			   }

			   //  2017/10/14
			   if  (  !bDecDataGot  )  {  //  2017/10/14. 为了让player能校验uiPts, 故要发个空包过去。
				   pPkt_dec->head.uiLen  =  0;
				   //
				   playAudioData(  pProcInfo,  pPkt_dec->head.uiSampleTimeInMs,  pPkt_dec->head.uiPts,  (  BYTE  *  )pPkt_dec->memory.m_pBuf,  pPkt_dec->head.uiLen,  pTransform->iIndex_player  );
				   //
				   continue;
			   }
		 }
	}	
	
	iErr  =  0;  

errLabel:

	
	//  if  (  pWf_compress  )  free(  pWf_compress  );
	//  if  (  pWf_pcm  )  free(  pWf_pcm  );
	//  if  (  pWf_decompress  )  free(  pWf_decompress  );
	
	//  if  (  pTransferAudioData  )  free(  pTransferAudioData  );
	

	if  (  !iErr  )  {
		if  (  !pTask->ucbVideoConference  )  {
			mySendAvResp(  pProcInfo,  pMsgTask,  pMsgBuf  );
		}
	}

	if  (  iErr  ||  tHintBuf[0]  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  where_showInfo,  _T(  ""  ),  _T(  "%I64u %s: %s"  ),  pMsgTask->data.route.idInfo_from.ui64Id,  (  iErr  ?  _T(  "failed"  )  :  _T(  ""  )  ),  tHintBuf  );
	
	return  iErr;

}
#endif


//
int transformTaskAudioPkt(QY_TRANSFORM* pTransform, TRANSFER_AUDIO_dataMemHead* pMemHead, byte* pInput1, myPLAY_AUDIO_DATA* pPkt_dec, MIS_MSGU* pMsgBuf_unused)
{
	int						iErr = -1;

	MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)pTransform->pProcInfo;
	MSGR_ADDR* pAddr = pTransform->pAddr_logicalPeer;
	int						iTaskId = pTransform->iTaskId;
	AV_TRAN_INFO* pTranInfo_unused = (AV_TRAN_INFO*)pTransform->pTranInfo_unused;
	PROC_TASK_AV* pTask = (PROC_TASK_AV*)pTransform->pTask;

	//
	int index_activeMems_from = pTransform->index_activeMems_from;

	//
	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex((CCtxQmc*)pProcInfo, pTask->iIndex_taskInfo);
	if (!pTaskInfo)  return  -1;
	if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  return  -1;
	QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;


	//
	QY_MC* pQyMc = (QY_MC*)pProcInfo->pQyMc;
	MIS_CNT* pMisCnt = (MIS_CNT*)pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt)  return  -1;
	int						tmpiRet = 0;
	char					timeBuf[32] = "";
	TCHAR					tHintBuf[256] = _T("");

#if 0
	if (!pReq || !pReq->usCnt || pReq->usCnt > mycountof(pReq->mems))  return  -1;
	if (!pPktInfo_toDec)  return  -1;
#endif
	//int bufSize = ;

	//
	CUS_MODULES* pCusModules = (CUS_MODULES*)pProcInfo->getCusModules();
	if (!pCusModules) return -1;

	//
#if  0
	TASK_AV_FROM* pFrom = NULL;

	pFrom = getTaskAvFrom(pTransform, index_pMems_from, index_activeMems_from, _T("transformTaskAudio"));
	if (!pFrom)  return  -1;
#endif
	//
	if (index_activeMems_from < 0 || index_activeMems_from >= pTc->videoConference.usCntLimit_activeMems_from)  return  -1;
	DLG_TALK_videoConferenceActiveMemFrom* pActiveMem_from = &pTc->videoConference.activeMems_from[index_activeMems_from];

	//
	//int						index				=	index_pMems_from;
	DWORD					curTickCnt = GetTickCount();

	TCHAR					where_showInfo[32] = _T("");		_sntprintf(where_showInfo, mycountof(where_showInfo), _T("transA %d"), pTransform->index_activeMems_from);

	if (!pAddr)  return  -1;

#if  0
	if (pMsgTask->tStartTime < pFrom->tStartTime_task) {
		_sntprintf(tHintBuf, mycountof(tHintBuf), _T("%s tStartTime < tStartTime_task. skipped."), tHintBuf);  goto  errLabel;
	}
#endif
	//
#if  0  //  2017/10/14
	if (pMsgTask->dwTickCnt_start) {	//  2009/03/22
		int  iElapse = curTickCnt - pMsgTask->dwTickCnt_start;
		if (iElapse > pProcInfo->cfg.policy.usTimeoutInMsToSwitch_rt) {
			_sntprintf(tHintBuf, mycountof(tHintBuf), _T("%I64u,  %dms elapsed, start %u, msg skipped"), pFrom->idInfo.ui64Id, iElapse, pMsgTask->dwTickCnt_start);
			goto  errLabel;
		}
	}
#endif

	//
#if 0
	if (pTransform->audio.ucbInited) {
		if (pTransform->audio.index_activeMems_from != index_activeMems_from
			|| pTransform->audio.idInfo.ui64Id != pActiveMem_from->avStream.idInfo.ui64Id
			|| pTransform->audio.ta.uiTranNo_openAvDev != pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev
			|| pTransform->audio.status.ucbDecFailed			//  2012/03/19
			)
		{
			traceLogA((char*)"procTaskAudio: transform.index_activeMems_from %d, uiTranNo_openAvDev %d != %d, %d", pTransform->audio.index_activeMems_from, pTransform->audio.ta.uiTranNo_openAvDev, index_activeMems_from, pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev);
			exitTaskAvFrom_audio(pProcInfo, pTransform);
		}
	}
	else {
		exitTaskAvFrom_audio(pProcInfo, pTransform);
	}

	//  2009/04/13
	if (!pTransform->audio.ucbInited) {
		if (initTaskAvFrom_audio(pProcInfo, pActiveMem_from, index_activeMems_from, pTransform))  goto  errLabel;
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("procTaskAudio: initTaskAvFrom_audio %d"), index_activeMems_from);
	}
#endif

	if (!pTransform->audio.ucbInited) {
		traceLogA((char*)"procTaskAudio failed: ³õÊ¼»¯Î´Íê³É¡£");
		goto  errLabel;
	}

	//  check
#if 0
	if (pMsgTask->data.route.idInfo_from.ui64Id != pActiveMem_from->avStream.idInfo.ui64Id
		|| pReq->uiTranNo_openAvDev != pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev)
	{
		traceLogA((char*)"procTaskAudio: idInfo_from %I64u, audioData.uiTranNo %d !=  pFrom %I64u, %d", pMsgTask->data.route.idInfo_from.ui64Id, pReq->uiTranNo_openAvDev, pActiveMem_from->avStream.idInfo.ui64Id, pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev);
		goto  errLabel;
	}
#endif

	//
#if  0
	if (!pTask->ucbVideoConference) {
		//
		pFrom->audio.usCnt_pkts++;
		if (pReq->tLastTime_showFrameInfo_020534) {
			if (!pFrom->audio.tLastTime_showFrameInfo_020534) {	//  ÕâÊÇÔÚµÚÒ»´ÎµÄÊ±ºò£¬Ã»¿ªÊ¼¼ÆÊý£¬ÏìÓ¦OK¡£
				pReq->tmpInternal.result.usRespCode = CONST_qyRc_ok;

				_sntprintf(tHintBuf, mycountof(tHintBuf), _T("×¼±¸Ö¡¼ÆÊý."));

				//  pFrom->audio.uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;	//  2013/08/04. 不能修改pFrom->audio.uiTranNo_openAvDev
			}
			else  if (pFrom->audio.ta_recvd.uiTranNo_openAvDev == pReq->uiTranNo_openAvDev
				&& pFrom->audio.tLastTime_showFrameInfo_020534 == pReq->tLastTime_showFrameInfo_020534
				&& pFrom->audio.usCnt_pkts >= pReq->usCnt_pkts)
			{
				pReq->tmpInternal.result.usRespCode = CONST_qyRc_ok;

				_sntprintf(tHintBuf, mycountof(tHintBuf), _T("pkts %d, Ò»ÖÂ."), pReq->usCnt_pkts);
			}
			else {
				CQyString	str;
				CQyString	str_expected;

				pReq->tmpInternal.result.usRespCode = CONST_qyRc_err;

				getTimelStr(pFrom->audio.tLastTime_showFrameInfo_020534, timeBuf, mycountof(timeBuf));  str = CQyString(timeBuf);
				getTimelStr((time_t)pReq->tLastTime_showFrameInfo_020534, timeBuf, mycountof(timeBuf));  str_expected = CQyString(timeBuf);
				_sntprintf(tHintBuf, mycountof(tHintBuf), _T("Error: ( %d, %s, %d pkts ) != ÆÚÍû  ( %d, %s, %d pkts )."), pFrom->audio.ta_recvd.uiTranNo_openAvDev, str, pFrom->audio.usCnt_pkts, pReq->uiTranNo_openAvDev, str_expected, pReq->usCnt_pkts);

				//  pFrom->audio.uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;			
			}
			pReq->tmpInternal.result.usCnt_pkts = pFrom->audio.usCnt_pkts;	//  Òª½«·¢ËÍµÄÖ¡Êý·¢»Ø·¢ËÍ·½¡£

			pFrom->audio.usCnt_pkts = 0;
			pFrom->audio.tLastTime_showFrameInfo_020534 = pMsgTask->tStartTime;
		}

	}
#endif

	//  ÏÂÃæ¿ªÊ¼½âÑ¹Ëõ
	DWORD							dwBytes_pcm;
	TRANSFER_AUDIO_dataMemHead* pMem;
	int								iPos;
	WAVEFORMATEX* pWfx_toPlay; pWfx_toPlay = &pTransform->audio.ta.ah_decompress.wfx;


	//  TRANSFER_AUDIO_DATA			*	pReq_toCompress;	pReq_toCompress  =  NULL;

	/*
	if  (  pTask->ucbVideoConferenceStarter  )  {
		if  (  !pMsgTask_toCompress  )  goto  errLabel;
		pReq_toCompress  =  (  TRANSFER_AUDIO_DATA  *  )pMsgTask_toCompress->data.buf;

		pMsgTask_toCompress->uiType  =  CONST_misMsgType_task;
		//
		memset(  pReq_toCompress,  0,  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  );
		pReq_toCompress->uiType =  pReq->uiType;
		pReq_toCompress->uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;
	}
	*/

	//  memset(  pFrom->audio.pDecompressBuf_transferAudioData,  0,  offsetof(  TRANSFER_AUDIO_DATA,  mems  )  );
	//  pFrom->audio.pDecompressBuf_transferAudioData->uiType  =  pReq->uiType;
	//  pFrom->audio.pDecompressBuf_transferAudioData->uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;

#if 0
	if (!pReq->usCnt || pReq->usCnt > mycountof(pReq->mems)) {
#ifdef  __DEBUG__
		traceLogA((char*)"procTaskAudio failed: pReq->usCnt %d error", pReq->usCnt);
#endif
		goto  errLabel;
	}
#endif


	//for  (  iPos  =  0,  i  =  0;  i  <  pReq->usCnt;  iPos  +=  pReq->mems[i].uiLen,  i  ++  )  
	for (int kk = 0; kk < 1; kk++)
	{
#if 0
		if (!pPktInfo_toDec->bGot_msg)  goto  errLabel;
		if (!pPktInfo_toDec->info.bGot_pkt)  goto  errLabel;
		//
		//  2017/10/14
		iPos = pPktInfo_toDec->info.iPos;
		if (pPktInfo_toDec->info.index_mems < 0 || pPktInfo_toDec->info.index_mems >= pReq->usCnt)  goto  errLabel;
		int								i;
		i = pPktInfo_toDec->info.index_mems;
#endif
		//
		pMem = pMemHead;// &pReq->mems[i];

#if 0
		if (iPos + pMem->uiLen > pReq->uiLen) {
#ifdef  __DEBUG__
			traceLogA((char*)"procTasAudio: ");
#endif
			goto  errLabel;
		}
#endif
		if (!pMem->uiLen) {
#ifdef  __DEBUG__
			traceLogA((char*)"procTaskAudio warning: mem.uiLen is 0");
#endif
			continue;
		}
		if (pMem->uiTranNo_openAvDev) {	//  2013/08/04. 会议时,参会人如果第2次进入会议,那么需要区分前后2次的音频流是不同的,靠的就是tn
			if (pMem->uiTranNo_openAvDev != pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev) {
#ifdef  __DEBUG__
				traceLog((TCHAR*)_T("transformTaskAudio: err, mem.uiTranNo_openAvDev %d != from.audio. %d. skipped"), pMem->uiTranNo_openAvDev, pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev);
#endif
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("transformTaskAudio: err, %I64u, mem.uiTranNo_openAvDev %d != from.audio. %d. skipped"), pMem->idInfo.ui64Id, pMem->uiTranNo_openAvDev, pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev);
				continue;
			}
		}

		//
#ifdef  __DEBUG__
#if  0
		TCHAR  tBuf[128];
		_sntprintf(tBuf, mycountof(tBuf), _T("%I64u, pts %d"), pFrom->idInfo.ui64Id, pMem->uiPts);
		showInfo_open0(0, 0, tBuf);
#endif
#endif

		//
		//memset(  pPkt_dec,  0,  offsetof(  myPLAY_AUDIO_data,  buf  )  );
		memset(&pPkt_dec->head, 0, sizeof(pPkt_dec->head));	//  2015/02/14
		if (pMem->idInfo.ui64Id) {
			pPkt_dec->head.idInfo.ui64Id = pMem->idInfo.ui64Id;
#if 0
			if (pPkt_dec->head.idInfo.ui64Id == pMsgTask->data.route.idInfo_from.ui64Id)  pPkt_dec->head.tmpInternal.uiTranNo_org = pReq->uiTranNo_openAvDev;
			else  pPkt_dec->head.tmpInternal.uiTranNo_org = 0;
#endif
			pPkt_dec->head.tmpInternal.uiTranNo_org = pMem->uiTranNo_openAvDev;
		}
		else {
			goto  errLabel;
#if 0
			pPkt_dec->head.idInfo.ui64Id = pMsgTask->data.route.idInfo_from.ui64Id;
			pPkt_dec->head.tmpInternal.uiTranNo_org = pReq->uiTranNo_openAvDev;
#endif
		}
		//  2017/10/13
		pPkt_dec->head.uiPts = pMem->uiPts;

		//  2015/05/19
		if (pTask->saveVideo.ucbSaveVideo_req) {
			//
			//(  BYTE  *  )pReq->buf  +  iPos,  pMem->uiLen,  pMem->uiSampleTimeInMs,  pMem->ui_rtTimeLen
			//
			//char* data = pReq->buf + iPos;
			char* data = (char*)pInput1;
			int  len = pMem->uiLen;
			//postAPktToSave(CONST_uiTransformType_dec, pTransform, pMem->uiSampleTimeInMs, 0, data, len);
		}



		//
		if (pTransform->audio.ta.compressor.common.ucCompressors == CONST_audioCompressors_acm) {

#ifdef  __SUPPORT_acmToDec__
			dwBytes_pcm = pMem->uiLen * pTransform->audio.pWf_pcm->nAvgBytesPerSec / pTransform->audio.pWf_compress->nAvgBytesPerSec;
			if (!pTransform->audio.pBuf_pcm || pTransform->audio.dwBufSize_pcm <= dwBytes_pcm) {
				if (pTransform->audio.pBuf_pcm) {
					free(pTransform->audio.pBuf_pcm);  pTransform->audio.pBuf_pcm = NULL;
				}
				dwBytes_pcm = dwBytes_pcm * 3 / 2 + 256;
				if (!(pTransform->audio.pBuf_pcm = (char*)mymalloc(dwBytes_pcm))) {
					traceLogA((char*)"procTaskAudio: malloc for pBuf_pcm failed.");
					goto  errLabel;
				}
				pTransform->audio.dwBufSize_pcm = dwBytes_pcm;
			}

			//
			//  pPkt_dec->head.uiSampleTimeInMs  =  pMem->uiSampleTimeInMs;
			pPkt_dec->head.uiLen = pProcInfo->cfg.uiBufSize_myPlayAudioData;	//  mycountof(  pPkt_dec->buf  );

			if (convertAudio(pTransform->audio.u.acm.hstr1, pTransform->audio.u.acm.hstr2, pTransform->audio.pWf_compress, (BYTE*)pInput1, pMem->uiLen, pTransform->audio.pWf_pcm, (BYTE*)pTransform->audio.pBuf_pcm, pTransform->audio.dwBufSize_pcm, pTransform->audio.pWf_decompress, (BYTE*)pPkt_dec->memory.m_pBuf, (DWORD*)&pPkt_dec->head.uiLen))  goto  errLabel;

			//  pFrom->audio.pDecompressBuf_transferAudioData->usCnt  ++  ;

			//  pWfx_toPlay  =  pTransform->audio.pWf_decompress;
			pPkt_dec->head.uiSampleTimeInMs = pMem->uiSampleTimeInMs;
#ifdef  __DEBUG__
			//  traceLogA(  (char*)  "transformA: uiSampleTimeInMs %d",  pPkt_dec->head.uiSampleTimeInMs  );
#endif

#if  0
			playAudioData(pProcInfo, pMisCnt, pTransform->iTaskId, pTask, pWfx_toPlay, pPkt_dec, pFrom);
#else
			if (!chkFromPlayerIndex_a(CONST_uiTransformType_dec, pTransform, pPkt_dec, 0)) {
				playAudioData(pProcInfo, pPkt_dec->head.uiSampleTimeInMs, pPkt_dec->head.uiPts, (BYTE*)pPkt_dec->memory.m_pBuf, pPkt_dec->head.uiLen, pTransform->iIndex_player);
			}
#endif

			if (!pTask->ucbVideoConferenceStarter)  continue;

			continue;

#else
			MY_DMO_INFO* pDmoInfo = NULL;
			int				index_dmo = 0;
			if (pFrom->ucbVideoConferenceStarter)  index_dmo = pMem->usIndex;

			pDmoInfo = &pTransform->audio.u.dmo;
			pDmoInfo->pDebugStep = &pTransform->audio.debugStep;

			//  pWfx_toPlay  =  &pFrom->audio.ah_decompress_recvd.wfx;
			pPkt_dec->head.uiSampleTimeInMs = pMem->uiSampleTimeInMs;

			if (chkFromPlayerIndex_a(pProcInfo, pMisCnt, pTransform->iTaskId, pTask, pWfx_toPlay, pPkt_dec, pFrom))  continue;
			if (pDmoInfo->iIndex_player != pFrom->iIndex_player)  pDmoInfo->iIndex_player = pFrom->iIndex_player;

#ifdef  __DEBUG__
			if (pProcInfo->cfg.debugStatusInfo.ucbPrint_a_in) {
				traceLogA((char*)"transformA: uiSampleTimeInMs %d. req.usCnt %d, req.len %d", pMem->uiSampleTimeInMs, pReq->usCnt, pReq->uiLen);
			}
#endif

			if (decompressAudio_filterGraph(pDmoInfo, &pFrom->audio.ah_compress_recvd, (BYTE*)pReq->buf + iPos, pMem->uiLen, pMem->uiSampleTimeInMs, pMem->ui_rtTimeLen))  goto  errLabel;

			//  if  (  pFrom->iDiffInMs_tStartAudios[index_dmo]  !=  pDmoInfo->iDiffInMs_tStartStream  )  pFrom->iDiffInMs_tStartAudios[index_dmo]  =  pDmoInfo->iDiffInMs_tStartStream;

#endif
		}
		else  if (pTransform->audio.ta.compressor.common.ucCompressors == CONST_audioCompressors_dmo) {
			MY_DMO_INFO* pDmoInfo = NULL;
			int				index_dmo = 0;
#if  0
			if (pFrom->ucbVideoConferenceStarter)  index_dmo = pMem->usIndex;
#endif

			pDmoInfo = &pTransform->audio.u.dmo;

			//  2011/07/03
			//  if  (  decompressAudio_dmo(  pDmoInfo,  &pFrom->audio.ah_compress_recvd,  (  BYTE  *  )pReq->buf  +  iPos,  pMem->uiLen,  pMem->uiSampleTimeInMs,  pMem->ui_rtTimeLen  )  )  goto  errLabel;
			if (decompressAudio_dmo(pDmoInfo, &pTransform->audio.ta.ah_compress, (BYTE*)pInput1, pMem->uiLen, pMem->uiSampleTimeInMs, pMem->ui_rtTimeLen)) {
				//
				//  此标志位表明需要重新初始化transform. 2012/03/19
				pTransform->audio.status.ucbDecFailed = TRUE;
				_sntprintf(tHintBuf, mycountof(tHintBuf), _T("%s %s"), tHintBuf, _T("decompressAudio_dmo failed."));
				//
				goto  errLabel;
			}

			//if  (  pFrom->iDiffInMs_tStartAudios[index_dmo]  !=  pDmoInfo->iDiffInMs_tStartStream  )  pFrom->iDiffInMs_tStartAudios[index_dmo]  =  pDmoInfo->iDiffInMs_tStartStream;

			int							j;
			for (j = 0; ; j++) {

				pPkt_dec->head.uiSampleTimeInMs = pMem->uiSampleTimeInMs;
				pPkt_dec->head.uiLen = pProcInfo->cfg.uiBufSize_myPlayAudioData;	//  mycountof(  pPkt_dec->buf  );

				if (getDmoOutputByIndex(pDmoInfo, j, (BYTE*)pPkt_dec->memory.m_pBuf, &pPkt_dec->head.uiLen, &pPkt_dec->head.uiSampleTimeInMs, &pPkt_dec->head.ui_rtTimeLen))  break;

				//
				//pFrom->iSampleTimeInMs_audios[index_dmo]  =  pPkt_dec->head.uiSampleTimeInMs;		//  2010/06/20

				//
				//  pWfx_toPlay  =  &pFrom->audio.ah_decompress_recvd.wfx;
				//  playAudioData(  pProcInfo,  pMisCnt,  pTransform->iTaskId,  pTask,  pWfx_toPlay,  pPkt_dec,  pFrom  );
				if (!chkFromPlayerIndex_a(CONST_uiTransformType_dec, pTransform, pPkt_dec, 0)) {
					playAudioData(pProcInfo, pPkt_dec->head.uiSampleTimeInMs, pPkt_dec->head.uiPts, (BYTE*)pPkt_dec->memory.m_pBuf, pPkt_dec->head.uiLen, pTransform->iIndex_player);
				}

				if (!pTask->ucbVideoConferenceStarter)  continue;

				continue;
			}

		}
		else {
			CUS_MODULE_U* pModule = NULL;
			/*
			switch  (  pTransform->audio.ta.compressor.common.ucCompressors  )  {
					case  CONST_audioCompressors_ipp:
						  pModule  =  pQyMc->cusModules.pIpp;
						  break;
					case  CONST_audioCompressors_custom:
						  pModule	=	getCusModule(  &pQyMc->cusModules,  CONST_moduleType_compress  );
						  break;
					default:
						traceLogA(  (char*)  "procTaskAudio: ucComprssors error, %d",  pFrom->audio.ta_recvd.compressor.common.ucCompressors  );
						qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskAudio: ucCompressors error, %d"  ),  (  int  )pFrom->audio.ta_recvd.compressor.common.ucCompressors  );
						   goto  errLabel;
						   break;
			}
			*/
			M_getCompressModule(pCusModules, pTransform->audio.uiModuleType_toDec, pModule);

			if (!pModule
				|| !pModule->compress.pf_qdcDecompressAudio
				|| !pModule->compress.pf_qdcGetOutputByIndex)  goto  errLabel;


			QDC_OBJ_INFO* pDmoInfo = NULL;
			int				index_dmo = 0;
#if  0
			if (pFrom->ucbVideoConferenceStarter)  index_dmo = pMem->usIndex;
#endif
#if  0
			if (index_dmo < 0 || index_dmo >= mycountof(pTransform->audio.u.custom.qdcObjInfos)) {
				traceLogA((char*)"procTaskAudio: index_dmo %d error", index_dmo);
				goto  errLabel;
			}
			pDmoInfo = MACRO_getDmo(pTransform->audio.u.custom.usCnt, pTransform->audio.u.custom.qdcObjInfos, index_dmo);
			if (!pDmoInfo)  goto  errLabel;
#endif
			pDmoInfo = &pTransform->audio.u.qoi.myQoi.common;	//  .qdcObjInfo;

			//
			if (pProcInfo->cfg.debugStatusInfo.ucb__Dump_mp3_dec__) {
				FILE* fp = fopen("c:\\tttbbb\\test\\dump_mp3_dec.mp3", "ab");
				if (fp) {
					byte* audio = (byte*)pInput1;// (pReq->buf + iPos);
					int len = (int)pMem->uiLen;

					fwrite(audio, len, 1, fp);
					fclose(fp);
				}

			}

			//  2011/07/03

			//if (pModule->compress.pf_qdcDecompressAudio(pDmoInfo, &pTransform->audio.ta.ah_compress, (BYTE*)pInput1, pMem->uiLen, pMem->uiSampleTimeInMs, pMem->ui_rtTimeLen) < 0)  goto  errLabel;
			if (pModule->compress.pf_qdcDecompressAudio(pDmoInfo, &pTransform->audio.ta.ah_compress, (BYTE*)pInput1, pMem->uiLen, pMem->uiSampleTimeInMs, pMem->uiPts) < 0)  goto  errLabel;
			//
			//if  (  pFrom->iDiffInMs_tStartAudios[index_dmo]  !=  pDmoInfo->var.iDiffInMs_tStartAudio  )  pFrom->iDiffInMs_tStartAudios[index_dmo]  =  pDmoInfo->var.iDiffInMs_tStartAudio;

			//  2017/10/14
			BOOL  bDecDataGot = FALSE;

			//
			int							j;
			for (j = 0; ; j++) {
				pPkt_dec->head.uiSampleTimeInMs = pMem->uiSampleTimeInMs;

				//pPkt_dec->head.uiLen = pProcInfo->cfg.uiBufSize_myPlayAudioData;	//  mycountof(  pPkt_dec->buf  );
				//pPkt_dec->head.uiLen = pPkt_dec->memory.uiBufSize;
				//if (pModule->compress.pf_qdcGetOutputByIndex(pDmoInfo, j, (BYTE*)pPkt_dec->memory.m_pBuf, &pPkt_dec->head.uiLen, &pPkt_dec->head.uiSampleTimeInMs, &pPkt_dec->head.ui_rtTimeLen))  break;

				pPkt_dec->head.uiLen = 0;
				unsigned int bufSize = pPkt_dec->memory.uiBufSize - pPkt_dec->head.uiLen;
				if (pModule->compress.pf_qdcGetOutputByIndex(pDmoInfo, j, (BYTE*)pPkt_dec->memory.m_pBuf + pPkt_dec->head.uiLen, &bufSize, &pPkt_dec->head.uiSampleTimeInMs, &pPkt_dec->head.ui_rtTimeLen))  break;
				else {
					pPkt_dec->head.uiLen += bufSize;
				}


				//
#ifdef  __DEBUG__
				//
				TCHAR  tBuf[128];
				if (0) {
					_sntprintf(tBuf, mycountof(tBuf), _T("transAPkt: %I64u: pkt[%d], decLen %d, head.len %d"), pTransform->audio.idInfo.ui64Id, j, bufSize, pPkt_dec->head.uiLen);
					showInfo_open(0, 0, 0, tBuf);
				}
				//
				if (pProcInfo->cfg.debugStatusInfo.ucb__Dump_deced_pcm__)
				{
					char fileName[MAX_PATH + 1];
					_snprintf(fileName, mycountof(fileName), "%s%I64u_%s", CONST_dump_dir, pTransform->audio.idInfo.ui64Id, CONST_fn_dump_deced_pcm);
					//
					if (pTransform->audio.tn_dumpAv != pProcInfo->cfg.debugStatusInfo.tn_dumpAv) {
						pTransform->audio.tn_dumpAv = pProcInfo->cfg.debugStatusInfo.tn_dumpAv;
						//							  
						FILE* fp = fopen(fileName, "w");
						if (fp) {
							fclose(fp);
						}
					}
					//
					FILE* fp = fopen(fileName, "ab");
					if (fp) {
						fwrite(pPkt_dec->memory.m_pBuf, (int)pPkt_dec->head.uiLen, 1, fp);
						fclose(fp);
					}
				}
#endif



				//
				bDecDataGot = TRUE;

				//  pWfx_toPlay  =  &pFrom->audio.ah_decompress_recvd.wfx;
				//  playAudioData(  pProcInfo,  pMisCnt,  pTransform->iTaskId,  pTask,  pWfx_toPlay,  pPkt_dec,  pFrom  );
				//
				if (!chkFromPlayerIndex_a(CONST_uiTransformType_dec, pTransform, pPkt_dec, 0)) {
					playAudioData(pProcInfo, pPkt_dec->head.uiSampleTimeInMs, pPkt_dec->head.uiPts, (BYTE*)pPkt_dec->memory.m_pBuf, pPkt_dec->head.uiLen, pTransform->iIndex_player);
				}

				if (!pTask->ucbVideoConferenceStarter)  continue;

				//  addToReq_toCompress_audio(  pProcInfo,  pTranInfo,  pTask,  index_activeMems_from,  pPkt_dec,  pMsgTask_toCompress  );

				continue;
			}

			//  2017/10/14
			if (!bDecDataGot) {  //  2017/10/14. 为了让player能校验uiPts, 故要发个空包过去。
				pPkt_dec->head.uiLen = 0;
				//
				playAudioData(pProcInfo, pPkt_dec->head.uiSampleTimeInMs, pPkt_dec->head.uiPts, (BYTE*)pPkt_dec->memory.m_pBuf, pPkt_dec->head.uiLen, pTransform->iIndex_player);
				//
				continue;
			}
		}
	}

	iErr = 0;

errLabel:


	//  if  (  pWf_compress  )  free(  pWf_compress  );
	//  if  (  pWf_pcm  )  free(  pWf_pcm  );
	//  if  (  pWf_decompress  )  free(  pWf_decompress  );

	//  if  (  pTransferAudioData  )  free(  pTransferAudioData  );


	if (!iErr) {
		if (!pTask->ucbVideoConference) {
			//mySendAvResp(pProcInfo, pMsgTask, pMsgBuf);
		}
	}

	if (iErr || tHintBuf[0]) {
		//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, where_showInfo, _T(""), _T("%I64u %s: %s"), pMsgTask->data.route.idInfo_from.ui64Id, (iErr ? _T("failed") : _T("")), tHintBuf);
	}

	return  iErr;

}



//
#if  0
 int  iitransformTaskAudioPkt_useAudioQ2(  QY_TRANSFORM  *  pTransform,  MIS_MSG_TASK  *  pMsgTask,  TRANSFER_AUDIO_DATA  *  pReq,  PKT_info_toDec  *  pPktInfo_toDec,  int  index_pMems_from1,  int  index_activeMems_from,  myPLAY_AUDIO_DATA	*	pPkt_dec,  MIS_MSGU  *  pMsgBuf  )
{
	int						iErr				=	-1;

	MC_VAR_isCli			*	pProcInfo			=	(  MC_VAR_isCli  *  )pTransform->pProcInfo;
	MSGR_ADDR			*	pAddr				=	pTransform->pAddr_logicalPeer;
	int						iTaskId				=	pTransform->iTaskId;  
	AV_TRAN_INFO		*	pTranInfo_unused	=	(  AV_TRAN_INFO  *  )pTransform->pTranInfo_unused;
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pTransform->pTask;
	
	//
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  (  CCtxQmc  *  )pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;	
	

	//
	QY_MC				*	pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;
	MIS_CNT				*	pMisCnt				=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
	if  (  !pMisCnt  )  return  -1;
	int						tmpiRet				=	0;
	char					timeBuf[32]			=	"";
	TCHAR					tHintBuf[256]		=	_T(  ""  );
	if  (  !pReq  ||  !pReq->usCnt  ||  pReq->usCnt  >  mycountof(  pReq->mems  )  )  return  -1;
	if  (  !pPktInfo_toDec  )  return  -1;

	//
	CUS_MODULES *pCusModules=(CUS_MODULES * )pProcInfo->getCusModules();
	if( !pCusModules ) return -1;

	//
#if  0
	TASK_AV_FROM		*	pFrom				=	NULL;

	pFrom  =  getTaskAvFrom(  pTransform,  index_pMems_from,  index_activeMems_from,  _T(  "transformTaskAudio"  )  );
	if  (  !pFrom  )  return  -1;
#endif
	if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTc->videoConference.usCntLimit_activeMems_from  )  return  -1;
	DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pTc->videoConference.activeMems_from[index_activeMems_from];

	//
	//int						index				=	index_pMems_from;
	DWORD					curTickCnt			=	GetTickCount(  );	

	TCHAR					where_showInfo[32]	=	_T(  ""  );		_sntprintf(  where_showInfo,  mycountof(  where_showInfo  ),  _T(  "transA %d"  ),  pTransform->index_activeMems_from  );

	if  (  !pAddr  )  return  -1;
	
#if  0
	if  (  pMsgTask->tStartTime  <  pFrom->tStartTime_task  )  {
		_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s tStartTime < tStartTime_task. skipped."  ),  tHintBuf  );  goto  errLabel;
	}
#endif
	//
#if  0  //  2017/10/14
	if  (  pMsgTask->dwTickCnt_start  )  {	//  2009/03/22
		int  iElapse  =  curTickCnt  -  pMsgTask->dwTickCnt_start;
		if  (  iElapse  >  pProcInfo->cfg.policy.usTimeoutInMsToSwitch_rt  )  {
			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%I64u,  %dms elapsed, start %u, msg skipped"  ),  pFrom->idInfo.ui64Id,  iElapse,  pMsgTask->dwTickCnt_start  );
			goto  errLabel;
		}
	}
#endif

	//
	if  (  pTransform->audio.ucbInited  )  {
		if  (  pTransform->audio.index_activeMems_from  !=  index_activeMems_from
			||  pTransform->audio.idInfo.ui64Id  !=  pActiveMem_from->avStream.idInfo.ui64Id				
			||  pTransform->audio.ta.uiTranNo_openAvDev  !=  pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev  
			||  pTransform->audio.status.ucbDecFailed			//  2012/03/19
				)  
		{
			traceLogA(  (char*)  "procTaskAudio: transform.index_activeMems_from %d, uiTranNo_openAvDev %d != %d, %d",  pTransform->audio.index_activeMems_from,  pTransform->audio.ta.uiTranNo_openAvDev,  index_activeMems_from,  pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev  );
			exitTaskAvFrom_audio(  pProcInfo,  pTransform  );			
		}
		}
	else  {
		  exitTaskAvFrom_audio(  pProcInfo,  pTransform  );			
	}

	//  2009/04/13
	if  (  !pTransform->audio.ucbInited  )  {		
		if  (  initTaskAvFrom_audio(  pProcInfo,  pActiveMem_from,  index_activeMems_from,  pTransform  )  )  goto  errLabel;
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskAudio: initTaskAvFrom_audio %d"  ),  index_activeMems_from  );
	}
	if  (  !pTransform->audio.ucbInited  )  {
		traceLogA(  (char*)  "procTaskAudio failed: ³õÊ¼»¯Î´Íê³É¡£"  );
		goto  errLabel;
	}

	//  check
	if  (  pMsgTask->data.route.idInfo_from.ui64Id  !=  pActiveMem_from->avStream.idInfo.ui64Id
		||  pReq->uiTranNo_openAvDev  !=  pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev  )  
	{
		traceLogA(  (char*)  "procTaskAudio: idInfo_from %I64u, audioData.uiTranNo %d !=  pFrom %I64u, %d",  pMsgTask->data.route.idInfo_from.ui64Id,  pReq->uiTranNo_openAvDev,  pActiveMem_from->avStream.idInfo.ui64Id,  pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev  );  
		goto  errLabel;
	}

	//
#if  0
	if  (  !pTask->ucbVideoConference  )  {
		//
		pFrom->audio.usCnt_pkts  ++  ;
		if  (  pReq->tLastTime_showFrameInfo_020534  )  {
			if  (  !pFrom->audio.tLastTime_showFrameInfo_020534  )  {	//  ÕâÊÇÔÚµÚÒ»´ÎµÄÊ±ºò£¬Ã»¿ªÊ¼¼ÆÊý£¬ÏìÓ¦OK¡£
				pReq->tmpInternal.result.usRespCode  =  CONST_qyRc_ok;

				_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "×¼±¸Ö¡¼ÆÊý."  )  );

				//  pFrom->audio.uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;	//  2013/08/04. 不能修改pFrom->audio.uiTranNo_openAvDev
				}
			else  if  (  pFrom->audio.ta_recvd.uiTranNo_openAvDev  ==  pReq->uiTranNo_openAvDev
						&&  pFrom->audio.tLastTime_showFrameInfo_020534  ==  pReq->tLastTime_showFrameInfo_020534  
							&&  pFrom->audio.usCnt_pkts  >=  pReq->usCnt_pkts  )  
					{
						pReq->tmpInternal.result.usRespCode  =  CONST_qyRc_ok;

						_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "pkts %d, Ò»ÖÂ."  ),  pReq->usCnt_pkts  );
					}
			else  {
				  CQyString	str;
				  CQyString	str_expected;

				  pReq->tmpInternal.result.usRespCode  =  CONST_qyRc_err;

				  getTimelStr(  pFrom->audio.tLastTime_showFrameInfo_020534,  timeBuf,  mycountof(  timeBuf  )  );  str  =  CQyString(  timeBuf  );
				  getTimelStr(  (  time_t  )pReq->tLastTime_showFrameInfo_020534,  timeBuf,  mycountof(  timeBuf  )  );  str_expected  =  CQyString(  timeBuf  );
				  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "Error: ( %d, %s, %d pkts ) != ÆÚÍû  ( %d, %s, %d pkts )."  ),  pFrom->audio.ta_recvd.uiTranNo_openAvDev,  str,  pFrom->audio.usCnt_pkts,  pReq->uiTranNo_openAvDev,  str_expected,  pReq->usCnt_pkts  );

				  //  pFrom->audio.uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;			
			}
			pReq->tmpInternal.result.usCnt_pkts  =  pFrom->audio.usCnt_pkts;	//  Òª½«·¢ËÍµÄÖ¡Êý·¢»Ø·¢ËÍ·½¡£

			pFrom->audio.usCnt_pkts  =  0;
			pFrom->audio.tLastTime_showFrameInfo_020534  =  pMsgTask->tStartTime;
		}
	
	}
#endif

	//  ÏÂÃæ¿ªÊ¼½âÑ¹Ëõ
	DWORD							dwBytes_pcm;
	TRANSFER_AUDIO_dataMemHead	*	pMem;
	int								iPos;
	WAVEFORMATEX				*	pWfx_toPlay  =  &pTransform->audio.ta.ah_decompress.wfx;


	//  TRANSFER_AUDIO_DATA			*	pReq_toCompress;	pReq_toCompress  =  NULL;
	
	/*
	if  (  pTask->ucbVideoConferenceStarter  )  {
		if  (  !pMsgTask_toCompress  )  goto  errLabel;
		pReq_toCompress  =  (  TRANSFER_AUDIO_DATA  *  )pMsgTask_toCompress->data.buf;

		pMsgTask_toCompress->uiType  =  CONST_misMsgType_task;
		//
		memset(  pReq_toCompress,  0,  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  );
		pReq_toCompress->uiType =  pReq->uiType;
		pReq_toCompress->uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;
	}
	*/

	//  memset(  pFrom->audio.pDecompressBuf_transferAudioData,  0,  offsetof(  TRANSFER_AUDIO_DATA,  mems  )  );
	//  pFrom->audio.pDecompressBuf_transferAudioData->uiType  =  pReq->uiType;
	//  pFrom->audio.pDecompressBuf_transferAudioData->uiTranNo_openAvDev  =  pReq->uiTranNo_openAvDev;

	if  (  !pReq->usCnt  ||  pReq->usCnt  >  mycountof(  pReq->mems  )  )  {
		#ifdef  __DEBUG__
				traceLogA(  (char*)  "procTaskAudio failed: pReq->usCnt %d error",  pReq->usCnt  );
		#endif
		goto  errLabel;
	}


	//for  (  iPos  =  0,  i  =  0;  i  <  pReq->usCnt;  iPos  +=  pReq->mems[i].uiLen,  i  ++  )  
	for  (  int  kk  =  0;  kk  <  1;  kk  ++  )
	{
		if  (  !pPktInfo_toDec->bGot_msg  )  goto  errLabel;
		if  (  !pPktInfo_toDec->info.bGot_pkt  )  goto  errLabel;
		//
		//  2017/10/14
		iPos  =  pPktInfo_toDec->info.iPos;
		if  (  pPktInfo_toDec->info.index_mems  <0  ||  pPktInfo_toDec->info.index_mems  >=  pReq->usCnt  )  goto  errLabel;
		int								i;
		i  =  pPktInfo_toDec->info.index_mems;

		 //
		 pMem  =  &pReq->mems[i];

		 if  (  iPos  +  pMem->uiLen  >  pReq->uiLen  )  {
			 #ifdef  __DEBUG__
					 traceLogA(  (char*)  "procTasAudio: "  );
			 #endif
			 goto  errLabel;
		 }
		 if  (  !pMem->uiLen  )  {
			 #ifdef  __DEBUG__
					 traceLogA(  (char*)  "procTaskAudio warning: mem.uiLen is 0"  );
			 #endif
			 continue;
		 }
		 if  (  pMem->uiTranNo_openAvDev  )  {	//  2013/08/04. 会议时,参会人如果第2次进入会议,那么需要区分前后2次的音频流是不同的,靠的就是tn
			 if  (  pMem->uiTranNo_openAvDev  !=  pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev  )  {
				 #ifdef  __DEBUG__
						 traceLog((TCHAR*)  _T(  "transformTaskAudio: err, mem.uiTranNo_openAvDev %d != from.audio. %d. skipped"  ),  pMem->uiTranNo_openAvDev,  pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev  );
				 #endif
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "transformTaskAudio: err, %I64u, mem.uiTranNo_openAvDev %d != from.audio. %d. skipped"  ),  pMem->idInfo.ui64Id,  pMem->uiTranNo_openAvDev,  pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev  );
				 continue;
			 }
		 }

		 //
#ifdef  __DEBUG__
		#if  0
		 TCHAR  tBuf[128];
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u, pts %d"  ),  pFrom->idInfo.ui64Id,  pMem->uiPts  );
		 showInfo_open0(  0,  0,  tBuf  );
		#endif
#endif

		 //
		 //memset(  pPkt_dec,  0,  offsetof(  myPLAY_AUDIO_data,  buf  )  );
		 memset(  &pPkt_dec->head,  0,  sizeof(  pPkt_dec->head  )  );	//  2015/02/14
		 if  (  pMem->idInfo.ui64Id  )  {
			 pPkt_dec->head.idInfo.ui64Id  =  pMem->idInfo.ui64Id;
			 if  (  pPkt_dec->head.idInfo.ui64Id  ==  pMsgTask->data.route.idInfo_from.ui64Id  )  pPkt_dec->head.tmpInternal.uiTranNo_org  =  pReq->uiTranNo_openAvDev;
			 else  pPkt_dec->head.tmpInternal.uiTranNo_org  =  0;
			 }
		 else  {
			   pPkt_dec->head.idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;
			   pPkt_dec->head.tmpInternal.uiTranNo_org  =  pReq->uiTranNo_openAvDev;
		 }				 
		 //  2017/10/13
		 pPkt_dec->head.uiPts  =  pMem->uiPts;

		 //  2015/05/19
		 if  (  pTask->saveVideo.ucbSaveVideo_req  )  {						
			 //
			 //(  BYTE  *  )pReq->buf  +  iPos,  pMem->uiLen,  pMem->uiSampleTimeInMs,  pMem->ui_rtTimeLen
			 //
			 char  *  data  =  pReq->buf  +  iPos;
			 int  len  =  pMem->uiLen;
			 //postAPktToSave(  CONST_uiTransformType_dec,  pTransform,  pMem->uiSampleTimeInMs,  0,  data,  len  );  										   
		 }



		 //
		 if  (  pTransform->audio.ta.compressor.common.ucCompressors  ==  CONST_audioCompressors_acm  )  {

#ifdef  __SUPPORT_acmToDec__
			 dwBytes_pcm  =  pMem->uiLen  *  pTransform->audio.pWf_pcm->nAvgBytesPerSec  /  pTransform->audio.pWf_compress->nAvgBytesPerSec;
			 if  (  !pTransform->audio.pBuf_pcm  ||  pTransform->audio.dwBufSize_pcm  <=  dwBytes_pcm  )  {
				 if  (  pTransform->audio.pBuf_pcm  )  {
					 free(  pTransform->audio.pBuf_pcm  );  pTransform->audio.pBuf_pcm  =  NULL;
				 }
				 dwBytes_pcm  =  dwBytes_pcm  *  3  /  2  +  256;
				 if  (  !(  pTransform->audio.pBuf_pcm  =  (  char  *  )mymalloc(  dwBytes_pcm  )  )  )  {
					 traceLogA(  (char*)  "procTaskAudio: malloc for pBuf_pcm failed."  );
					 goto  errLabel;
				 }
				 pTransform->audio.dwBufSize_pcm  =  dwBytes_pcm;
			 }

			 //
			 //  pPkt_dec->head.uiSampleTimeInMs  =  pMem->uiSampleTimeInMs;
			 pPkt_dec->head.uiLen  =  pProcInfo->cfg.uiBufSize_myPlayAudioData;	//  mycountof(  pPkt_dec->buf  );

			 if  (  convertAudio(  pTransform->audio.u.acm.hstr1,  pTransform->audio.u.acm.hstr2,  pTransform->audio.pWf_compress,  (  BYTE  *  )pReq->buf  +  iPos,  pMem->uiLen,  pTransform->audio.pWf_pcm,  (  BYTE  *  )pTransform->audio.pBuf_pcm,  pTransform->audio.dwBufSize_pcm,  pTransform->audio.pWf_decompress,  (  BYTE  *  )pPkt_dec->memory.m_pBuf,  (  DWORD  *  )&pPkt_dec->head.uiLen  )  )  goto  errLabel;

			 //  pFrom->audio.pDecompressBuf_transferAudioData->usCnt  ++  ;
			 
			 //  pWfx_toPlay  =  pTransform->audio.pWf_decompress;
			 pPkt_dec->head.uiSampleTimeInMs  =  pMem->uiSampleTimeInMs;
			 #ifdef  __DEBUG__
					 //  traceLogA(  (char*)  "transformA: uiSampleTimeInMs %d",  pPkt_dec->head.uiSampleTimeInMs  );
			 #endif

#if  0
			   playAudioData(  pProcInfo,  pMisCnt,  pTransform->iTaskId,  pTask,  pWfx_toPlay,  pPkt_dec,  pFrom  );
#else
			 if  (  !chkFromPlayerIndex_a(  CONST_uiTransformType_dec,  pTransform,  pPkt_dec,  0  )  )  {
				 playAudioData(  pProcInfo,  pPkt_dec->head.uiSampleTimeInMs,  pPkt_dec->head.uiPts,  (  BYTE  *  )pPkt_dec->memory.m_pBuf,  pPkt_dec->head.uiLen,  pTransform->iIndex_player  );
			 }
#endif

			 if  (  !pTask->ucbVideoConferenceStarter  )  continue;

			 continue;

#else
				   MY_DMO_INFO	*	pDmoInfo	=	NULL;
			       int				index_dmo  =  0;					   
				   if  (  pFrom->ucbVideoConferenceStarter  )  index_dmo  =  pMem->usIndex;

				   pDmoInfo  =  &pTransform->audio.u.dmo;
				   pDmoInfo->pDebugStep  =  &pTransform->audio.debugStep;

				   //  pWfx_toPlay  =  &pFrom->audio.ah_decompress_recvd.wfx;
				   pPkt_dec->head.uiSampleTimeInMs  =  pMem->uiSampleTimeInMs;

				   if  (  chkFromPlayerIndex_a(  pProcInfo,  pMisCnt,  pTransform->iTaskId,  pTask,  pWfx_toPlay,  pPkt_dec,  pFrom  )  )  continue;
				   if  (  pDmoInfo->iIndex_player  !=  pFrom->iIndex_player  )  pDmoInfo->iIndex_player  =  pFrom->iIndex_player;

	   			   #ifdef  __DEBUG__
						   if  (  pProcInfo->cfg.debugStatusInfo.ucbPrint_a_in  )  {
							   traceLogA(  (char*)  "transformA: uiSampleTimeInMs %d. req.usCnt %d, req.len %d",  pMem->uiSampleTimeInMs,  pReq->usCnt,  pReq->uiLen  );
						   }
				   #endif

				   if  (  decompressAudio_filterGraph(  pDmoInfo,  &pFrom->audio.ah_compress_recvd,  (  BYTE  *  )pReq->buf  +  iPos,  pMem->uiLen,  pMem->uiSampleTimeInMs,  pMem->ui_rtTimeLen  )  )  goto  errLabel;

				   //  if  (  pFrom->iDiffInMs_tStartAudios[index_dmo]  !=  pDmoInfo->iDiffInMs_tStartStream  )  pFrom->iDiffInMs_tStartAudios[index_dmo]  =  pDmoInfo->iDiffInMs_tStartStream;

#endif
			 }
		 else  if  (  pTransform->audio.ta.compressor.common.ucCompressors  ==  CONST_audioCompressors_dmo  )  {
				   MY_DMO_INFO	*	pDmoInfo	=	NULL;
			       int				index_dmo  =  0;
#if  0
				   if  (  pFrom->ucbVideoConferenceStarter  )  index_dmo  =  pMem->usIndex;
#endif

				   pDmoInfo  =  &pTransform->audio.u.dmo;

				   //  2011/07/03
				   //  if  (  decompressAudio_dmo(  pDmoInfo,  &pFrom->audio.ah_compress_recvd,  (  BYTE  *  )pReq->buf  +  iPos,  pMem->uiLen,  pMem->uiSampleTimeInMs,  pMem->ui_rtTimeLen  )  )  goto  errLabel;
				   if  (  decompressAudio_dmo(  pDmoInfo,  &pTransform->audio.ta.ah_compress,  (  BYTE  *  )pReq->buf  +  iPos,  pMem->uiLen,  pMem->uiSampleTimeInMs,  pMem->ui_rtTimeLen  )  )  {
					   //
					   //  此标志位表明需要重新初始化transform. 2012/03/19
					   pTransform->audio.status.ucbDecFailed  =  TRUE;
					   _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s %s"  ),  tHintBuf,  _T(  "decompressAudio_dmo failed."  )  );
					   //
					   goto  errLabel;
				   }

				   //if  (  pFrom->iDiffInMs_tStartAudios[index_dmo]  !=  pDmoInfo->iDiffInMs_tStartStream  )  pFrom->iDiffInMs_tStartAudios[index_dmo]  =  pDmoInfo->iDiffInMs_tStartStream;

				   int							j;
				   for  (  j  =  0  ;  ;  j  ++  )  {
					    				   		
						pPkt_dec->head.uiSampleTimeInMs  =  pMem->uiSampleTimeInMs;
						pPkt_dec->head.uiLen  =  pProcInfo->cfg.uiBufSize_myPlayAudioData;	//  mycountof(  pPkt_dec->buf  );

						if  (  getDmoOutputByIndex(  pDmoInfo,  j,  (  BYTE  *  )pPkt_dec->memory.m_pBuf,  &pPkt_dec->head.uiLen,  &pPkt_dec->head.uiSampleTimeInMs,  &pPkt_dec->head.ui_rtTimeLen  )  )  break;

						//
						//pFrom->iSampleTimeInMs_audios[index_dmo]  =  pPkt_dec->head.uiSampleTimeInMs;		//  2010/06/20

						//
						//  pWfx_toPlay  =  &pFrom->audio.ah_decompress_recvd.wfx;
						//  playAudioData(  pProcInfo,  pMisCnt,  pTransform->iTaskId,  pTask,  pWfx_toPlay,  pPkt_dec,  pFrom  );
						if  (  !chkFromPlayerIndex_a(  CONST_uiTransformType_dec,  pTransform,  pPkt_dec,  0  )  )  {
							playAudioData(  pProcInfo,  pPkt_dec->head.uiSampleTimeInMs,  pPkt_dec->head.uiPts,  (  BYTE  *  )pPkt_dec->memory.m_pBuf,  pPkt_dec->head.uiLen,  pTransform->iIndex_player  );
						}

						if  (  !pTask->ucbVideoConferenceStarter  )  continue;
						
						continue;
				   }

				   }
		 else  {  
			   CUS_MODULE_U	*	pModule	=	NULL;
			   /*
			   switch  (  pTransform->audio.ta.compressor.common.ucCompressors  )  {
					   case  CONST_audioCompressors_ipp:
						     pModule  =  pQyMc->cusModules.pIpp;
							 break;
					   case  CONST_audioCompressors_custom:
						     pModule	=	getCusModule(  &pQyMc->cusModules,  CONST_moduleType_compress  );
							 break;
					   default:
						   traceLogA(  (char*)  "procTaskAudio: ucComprssors error, %d",  pFrom->audio.ta_recvd.compressor.common.ucCompressors  );
						   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskAudio: ucCompressors error, %d"  ),  (  int  )pFrom->audio.ta_recvd.compressor.common.ucCompressors  );
							  goto  errLabel;
							  break;
			   }
			   */
			   M_getCompressModule(pCusModules,pTransform->audio.uiModuleType_toDec,pModule );

			   if  (  !pModule
					   ||  !pModule->compress.pf_qdcDecompressAudio  
						||  !pModule->compress.pf_qdcGetOutputByIndex  )  goto  errLabel;


			   QDC_OBJ_INFO	*	pDmoInfo	=	NULL;
			   int				index_dmo  =  0;
#if  0
			   if  (  pFrom->ucbVideoConferenceStarter  )  index_dmo  =  pMem->usIndex;
#endif
#if  0
			   if  (  index_dmo  <  0  ||  index_dmo  >=  mycountof(  pTransform->audio.u.custom.qdcObjInfos  )  )  {
				   traceLogA(  (char*)  "procTaskAudio: index_dmo %d error",  index_dmo  );
				   goto  errLabel;
			   }
			   pDmoInfo  =  MACRO_getDmo(  pTransform->audio.u.custom.usCnt,  pTransform->audio.u.custom.qdcObjInfos,  index_dmo  );
			   if  (  !pDmoInfo  )  goto  errLabel;
#endif
			   pDmoInfo  =  &pTransform->audio.u.qoi.myQoi.common;	//  .qdcObjInfo;

			   //
			   if(pProcInfo->cfg.debugStatusInfo.ucb__Dump_mp3_dec__){
				   FILE * fp=fopen("c:\\tttbbb\\test\\dump_mp3_dec.mp3","ab" );
				   if(fp){
					   	byte* audio = (byte*)(pReq->buf+iPos);
						int len = (int)pMem->uiLen;
					
					   fwrite(audio,len,1,fp);
					   fclose(fp);
				   }

			   }

			   //  2011/07/03
			   //  if  (  pModule->compress.pf_qdcDecompressAudio(  pDmoInfo,  &pFrom->audio.ah_compress_recvd,  (  BYTE  *  )pReq->buf  +  iPos,  pMem->uiLen,  pMem->uiSampleTimeInMs,  pMem->ui_rtTimeLen  )  )  goto  errLabel;
			   if  (  pModule->compress.pf_qdcDecompressAudio(  pDmoInfo,  &pTransform->audio.ta.ah_compress,  (  BYTE  *  )pReq->buf  +  iPos,  pMem->uiLen,  pMem->uiSampleTimeInMs,  pMem->ui_rtTimeLen  )  <  0  )  goto  errLabel;
			   //if  (  pFrom->iDiffInMs_tStartAudios[index_dmo]  !=  pDmoInfo->var.iDiffInMs_tStartAudio  )  pFrom->iDiffInMs_tStartAudios[index_dmo]  =  pDmoInfo->var.iDiffInMs_tStartAudio;

			   //  2017/10/14
			   BOOL  bDecDataGot  =  FALSE;

			   //
			   int							j;
			   for  (  j  =  0  ;  ;  j  ++  )  {
				   pPkt_dec->head.uiSampleTimeInMs  =  pMem->uiSampleTimeInMs;
				   pPkt_dec->head.uiLen  =  pProcInfo->cfg.uiBufSize_myPlayAudioData;	//  mycountof(  pPkt_dec->buf  );

				   if  (  pModule->compress.pf_qdcGetOutputByIndex(  pDmoInfo,  j,  (  BYTE  *  )pPkt_dec->memory.m_pBuf,  &pPkt_dec->head.uiLen,  &pPkt_dec->head.uiSampleTimeInMs,  &pPkt_dec->head.ui_rtTimeLen  )  )  break;

				   //
#ifdef  __DEBUG__
				   if(pProcInfo->cfg.debugStatusInfo.ucb__Dump_deced_pcm__)                   
				   {
							char fileName[MAX_PATH  +  1];
							_snprintf(  fileName,  mycountof(  fileName  ),  "%s%I64u_%s",  CONST_dump_dir,  pTransform->audio.idInfo.ui64Id,  CONST_fn_dump_deced_pcm  );
							//
							if(  pTransform->audio.tn_dumpAv!=pProcInfo->cfg.debugStatusInfo.tn_dumpAv  ) {
								pTransform->audio.tn_dumpAv=pProcInfo->cfg.debugStatusInfo.tn_dumpAv;
								//							  
								FILE  *  fp=fopen(fileName, "w"  );
								if( fp )  {
								  fclose(fp);							  
								}					
							}
							//
							FILE * fp=fopen( fileName,"ab");
							if(fp) {
								fwrite(pPkt_dec->memory.m_pBuf, (int)pPkt_dec->head.uiLen, 1, fp);
								fclose(fp);
							}
                        }
#endif



				   //
				   bDecDataGot  =  TRUE;

				   //  pWfx_toPlay  =  &pFrom->audio.ah_decompress_recvd.wfx;
				   //  playAudioData(  pProcInfo,  pMisCnt,  pTransform->iTaskId,  pTask,  pWfx_toPlay,  pPkt_dec,  pFrom  );
				   if  (  !chkFromPlayerIndex_a(  CONST_uiTransformType_dec,  pTransform,  pPkt_dec,  0  )  )  {
					   playAudioData(  pProcInfo,  pPkt_dec->head.uiSampleTimeInMs,  pPkt_dec->head.uiPts,  (  BYTE  *  )pPkt_dec->memory.m_pBuf,  pPkt_dec->head.uiLen,  pTransform->iIndex_player  );
				   }

				   if  (  !pTask->ucbVideoConferenceStarter  )  continue;

				   //  addToReq_toCompress_audio(  pProcInfo,  pTranInfo,  pTask,  index_activeMems_from,  pPkt_dec,  pMsgTask_toCompress  );

				   continue;
			   }

			   //  2017/10/14
			   if  (  !bDecDataGot  )  {  //  2017/10/14. 为了让player能校验uiPts, 故要发个空包过去。
				   pPkt_dec->head.uiLen  =  0;
				   //
				   playAudioData(  pProcInfo,  pPkt_dec->head.uiSampleTimeInMs,  pPkt_dec->head.uiPts,  (  BYTE  *  )pPkt_dec->memory.m_pBuf,  pPkt_dec->head.uiLen,  pTransform->iIndex_player  );
				   //
				   continue;
			   }
		 }
	}	
	
	iErr  =  0;  

errLabel:

	
	//  if  (  pWf_compress  )  free(  pWf_compress  );
	//  if  (  pWf_pcm  )  free(  pWf_pcm  );
	//  if  (  pWf_decompress  )  free(  pWf_decompress  );
	
	//  if  (  pTransferAudioData  )  free(  pTransferAudioData  );
	

	if  (  !iErr  )  {
		if  (  !pTask->ucbVideoConference  )  {
			mySendAvResp(  pProcInfo,  pMsgTask,  pMsgBuf  );
		}
	}

	if  (  iErr  ||  tHintBuf[0]  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  where_showInfo,  _T(  ""  ),  _T(  "%I64u %s: %s"  ),  pMsgTask->data.route.idInfo_from.ui64Id,  (  iErr  ?  _T(  "failed"  )  :  _T(  ""  )  ),  tHintBuf  );
	
	return  iErr;

}
#endif 


