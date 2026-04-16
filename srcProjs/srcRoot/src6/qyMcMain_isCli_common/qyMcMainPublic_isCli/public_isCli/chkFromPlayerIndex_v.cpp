
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
//  #include	"dlgtest_isCli.h"

#endif
#include	"qmcCmdProc.h"

#include	"qySqlFunc.h"
#include	"qyAvRecordPublic.h"

//  #include	"DlgProgress.h"

#include	"myDb.h"

#include	"isCliHelpPublic.h"
#include	"isCliD3dPublic.h"
#include	"qmcCommFunc_isCli.h"
#include	"ctxMcThread.h"


//
 __declspec(  dllexport  )  int  tmpGetMaxAudioPlayCfg(  AUDIO_PLAY_CFG  *  pSrc0,  AUDIO_PLAY_CFG  *  pSrc1,  AUDIO_PLAY_CFG  *  pDst  )
{
	pDst->usMinTimeInMsOfAudioDataPlaying  =  max(  pSrc0->usMinTimeInMsOfAudioDataPlaying,  pSrc1->usMinTimeInMsOfAudioDataPlaying  );					//  2009/06/14
	pDst->usAudioDataAddedToPlayEveryTime  =  max(  pSrc0->usAudioDataAddedToPlayEveryTime,  pSrc1->usAudioDataAddedToPlayEveryTime  );					//  2009/06/16
	pDst->usNotifyIntervalInMs_needMoreAudioData  =  max(  pSrc0->usNotifyIntervalInMs_needMoreAudioData,  pSrc1->usNotifyIntervalInMs_needMoreAudioData  );				//  2009/06/14. = CONST_notifyInterval
	
	//  2012/01/27
	pDst->usMinTimeInMsToPlay  =  max(  pSrc0->usMinTimeInMsToPlay,  pSrc1->usMinTimeInMsToPlay  );											//  2012/01/27
	//
	pDst->usMaxTimeInMsToPlay  =  max(  pSrc0->usMaxTimeInMsToPlay,  pSrc1->usMaxTimeInMsToPlay  );											//  2009/06/03
	pDst->usMaxTimeInMsToBeRemoved  =  max(  pSrc0->usMaxTimeInMsToBeRemoved,  pSrc1->usMaxTimeInMsToBeRemoved  );							//  2009/06/03

	return  0;
}




//
//  2014/11/26
//  2011/07/03
//  
//int  tmp_chkFromPlayerIndex_v(  unsigned  int  uiTranNo_openAvDev,  unsigned  short  usIndex,  BITMAPINFO  *  pBmpInfo_input,  int  iSampleTimeInMs,  int  iSampleTimeInMs_org_unused,  QY_MESSENGER_ID  *  pIdInfo_sender,  unsigned  int  uiEventId_lastRecvd,  void  *  pMIS_CNT,  QY_MESSENGER_ID  *  pIdInfo_peer,  int  iTaskId,  QY_TRANSFORM  *  pTransform,  int  *  piIndex_player_transform,  PROC_TASK_AV  *  pTask,  myDRAW_VIDEO_DATA  *  pPkt  )
int  tmp_chkFromPlayerIndex_v(  unsigned  int  uiTranNo_openAvDev,  unsigned  short  usIndex,  BITMAPINFO  *  pBmpInfo_input,  int  iSampleTimeInMs,  int  iSampleTimeInMs_org_unused,  QY_MESSENGER_ID  *  pIdInfo_sender,  void  *  pMIS_CNT,  QY_MESSENGER_ID  *  pIdInfo_peer,  int  iTaskId,  QY_TRANSFORM  *  pTransform,  int  *  piIndex_player_transform,  PROC_TASK_AV  *  pTask,  myDRAW_VIDEO_DATA  *  pPkt  )
{
	int						iErr						=	-1;
	//
	MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMIS_CNT;
	//
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	QY_MC				*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;
	
	if  (  !pBmpInfo_input  )  return  -1;
	if  (  !pIdInfo_sender  )  return  -1;

	if  (  !pTransform  )  return  -1;
	TRAN_audio  *  pTa  =  &pTransform->audio.ta;
	TRAN_video  *  pTv  =  &pTransform->video.tv;

	if  (  !pTa  )  return  -1;
	if  (  !pTv  )  return  -1;
	if  (  !piIndex_player_transform  )  return  -1;
	
#ifdef  __DEBUG__
	if  (  0  )  {
		//  SampleTime  =  0;
		traceLogA(  "test here"  );
	}
#endif


	QY_PLAYER  *  pPlayer;
	pPlayer  =  getPlayerByIndex(  pProcInfo,  *piIndex_player_transform  );  //  pTransform->iIndex_player  );
	if  (  pPlayer  )  {
		if  (  pPlayer->iTaskId  !=  iTaskId
			||  pPlayer->idInfo_recorder.ui64Id  !=  pIdInfo_sender->ui64Id
			||  pPlayer->video.uiTranNo  !=  uiTranNo_openAvDev  
			||  pPlayer->bNeedEnd1
			)
		{	
			traceLogA(  "drawVideoData: not correct player"  );
			*piIndex_player_transform  =  -1;
			pPlayer  =  NULL;
		}
	}
	if  (  !pPlayer  )  {
		int						k;

		for  (  k  =  0;  k  <  pProcInfo->av.usCnt_players;  k  ++  )  {

			 //
 			 if (pProcInfo->av.pPlayers[k].bNeedEnd1)  continue;		//  2025/05/29

			 //
			 if  (  pProcInfo->av.pPlayers[k].iTaskId  !=  iTaskId  )  continue;		//  2010/09/07

			 if  (  pProcInfo->av.pPlayers[k].idInfo_recorder.ui64Id  ==  pIdInfo_sender->ui64Id
			 	 &&  pProcInfo->av.pPlayers[k].video.uiTranNo  ==  uiTranNo_openAvDev  )  		 
			 {
				 if  (  !pTa->uiTranNo_openAvDev  )  break;
				
				 if  (  pProcInfo->av.pPlayers[k].idInfo_recorder.ui64Id  ==  pIdInfo_sender->ui64Id
					 &&  pProcInfo->av.pPlayers[k].audio.uiTranNo  ==  pTa->uiTranNo_openAvDev  )
				 {
					 break;				 		 
				 }
			 }
		}

		if  (  k  <  pProcInfo->av.usCnt_players  )  {
			*piIndex_player_transform  =  k;
			pPlayer  =  getPlayerByIndex(  pProcInfo,  k  );
			if  (  !pPlayer  )  goto  errLabel;
		}
	}

	if  (  !pPlayer  ||  !pPlayer->video.bRunning  )  {

		
		//  ÕâÀï×é°ü·¢¸øÖ÷Ïß³Ì¡£
		MIS_MSG_applyForPlayer_qmc	msg;
		memset(  &msg,  0,  sizeof(  msg  )  );
		msg.uiType  =  CONST_misMsgType_applyForPlayer_qmc;
		msg.iTaskId  =  iTaskId;								//  2009/09/17
		msg.idInfo_recorder.ui64Id  =  pIdInfo_sender->ui64Id;
		msg.video.uiTranNo  =  uiTranNo_openAvDev;
		memcpy(  &msg.video.vh.bih,  pBmpInfo_input,  sizeof(  msg.video.vh.bih  )  );
		//msg.video.ucbFlippedImg  =  pTv->compressor.common.ucbOutputFlippedImg;
		msg.video.usFps  =  pTv->compressor.common.usMaxFps_toShareBmp;	//  2015/02/20

		//
		if  (  pTa->uiTranNo_openAvDev  )  {
			msg.audio.uiTranNo  =  pTa->uiTranNo_openAvDev;
			memcpy(  &msg.audio.ah.wfx,  &pTa->ah_decompress.wfx,  sizeof(  msg.audio.ah.wfx  )  );

			//  2009/06/14
			if  (  pTask  )  {
				#if  0	//  2011/12/25
					memcpy(  &msg.audio.playCfg,  &pTask->audio.playCfg,  sizeof(  msg.audio.playCfg  )  );
				#else
					tmpGetMaxAudioPlayCfg(  &pTask->audio.playCfg,  &pTa->compressor.playCfg,  &msg.audio.playCfg  );
				#endif
			}
		}

		//
		TCHAR  tBuf[128];
		if  (  !msg.video.vh.bih.biWidth  ||  !msg.video.vh.bih.biHeight  )  
		{		
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "chkFromPlayerIndex_v failed, idInfo %I64u, %d, trans.v.tv.vh_dec.bih: %dX%d"  ),  pIdInfo_sender->ui64Id,  msg.video.uiTranNo,  msg.video.vh.bih.biWidth,  msg.video.vh.bih.biHeight  );
			showInfo_open0(  0,  0,  tBuf  );
			goto  errLabel;
		}


		//
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "chkFromPlayerIndex_v : %I64u,%d,%d apply for player"  ),  pIdInfo_sender->ui64Id,  msg.audio.uiTranNo,  msg.video.uiTranNo  );

		//					  
		qPostMsg(  &msg,  sizeof(  msg  ),  &pQyMc->gui.processQ,  _T(  "tmp_chkFromPlayerIndex_v"  ));
			
		PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    

		iErr  =  -2;  goto  errLabel;
	}


	//  2009/05/27
#if  0
	if  (  pPlayer->video.m_var.uiSampleTimeInMs_org_newRecvd  &&  iSampleTimeInMs_org  )  {
		if  (  iSampleTimeInMs_org  <  (  int  )(  pPlayer->video.m_var.uiSampleTimeInMs_org_newRecvd  -  500  )
			||  iSampleTimeInMs_org  >  (  int  )(  pPlayer->video.m_var.uiSampleTimeInMs_org_newRecvd  +  3000  )  )
		{
			//  move backward or forward
			traceLogA(  "drawVideoData: pkt.uiSampleTimeInMs_org %d, player.%d. trigger to empty old data",  iSampleTimeInMs_org,  pPlayer->video.m_var.uiSampleTimeInMs_org_newRecvd  );
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "drawVideoData: pkt.uiSampleTimeInMs_org %d, player.%d. trigger to empty old data"  ),  iSampleTimeInMs_org,  pPlayer->video.m_var.uiSampleTimeInMs_org_newRecvd  );

			//  
			pPlayer->uiSampleTimeInMs_start  =  iSampleTimeInMs;

			q2TriggerToProcess(  &pPlayer->video.q2  );
			q2TriggerToProcess(  &pPlayer->audio.q2  );
		}
	}
#endif

	//
	pPlayer->video.m_var.uiSampleTimeInMs_newRecvd  =  iSampleTimeInMs;
	//pPlayer->video.m_var.uiSampleTimeInMs_org_newRecvd  =  iSampleTimeInMs_org;
	pPlayer->video.m_var.dwTickCnt_uiSampleTimeInMs_newRecvd  =  GetTickCount(  );
	
	//  2015/09/30
	//if  (  pPlayer->video.m_var.uiPktResType  !=  p.u
	pTransform->video.u.qoi.myQoi.common.var.sharedTex.uiSeqNo_lastRender = pPlayer->video.m_var.status.fillD3d.uiSeqNo_lastRender;

	//
#if  0  //  2015/10/01
	if  (  pPlayer->video.m_var.hWnd_task  !=  pTask->hWnd_task  )  pPlayer->video.m_var.hWnd_task  =  pTask->hWnd_task;
	if  (  pPlayer->video.m_var.usIndex  !=  usIndex  )  pPlayer->video.m_var.usIndex  =  usIndex;
	//  pPlayer->video.m_var.pMisCnt;
	if  (  pIdInfo_peer  )  {
		if  (  pPlayer->video.m_var.idInfo_peer.ui64Id  !=  pIdInfo_peer->ui64Id  )  pPlayer->video.m_var.idInfo_peer.ui64Id  =  pIdInfo_peer->ui64Id;
	}
	if  (  pPlayer->video.m_var.uiEventId_lastRecvd  !=  uiEventId_lastRecvd  )  pPlayer->video.m_var.uiEventId_lastRecvd  =  uiEventId_lastRecvd;
#endif
	//  2015/10/01
	if  (  pPkt->hWnd_task  !=  pTask->hWnd_task  )  pPkt->hWnd_task  =  pTask->hWnd_task;
	if  (  pPkt->usIndex_activeMems_from  !=  usIndex  )  pPkt->usIndex_activeMems_from  =  usIndex;
	if  (  pIdInfo_peer  )  {
		if  (  pPkt->idInfo_peer.ui64Id  !=  pIdInfo_peer->ui64Id  )  pPkt->idInfo_peer.ui64Id  =  pIdInfo_peer->ui64Id;
	}
	//  2016/12/27
	//if  (  pPkt->uiEventId_lastRecvd  !=  uiEventId_lastRecvd  )  pPkt->uiEventId_lastRecvd  =  uiEventId_lastRecvd;


	//  2009/05/03
	if  (  iSampleTimeInMs  )  {
		
		//  traceLogA(  "drawVideoData: uiSampleTimeInMs %d, uiSampleTimeInMs_org %d",  p->head.uiSampleTimeInMs,  p->head.uiSampleTimeInMs_org  );

		if  (  iSampleTimeInMs  <  (  int  )(  pPlayer->video.m_var.uiSampleTimeInMs  -  500  )  )  {

			#ifdef  __DEBUG__	//  2014/06/14. 在rtsp解码video.264时，这里还有点错。暂时屏蔽showInfo
					#if  0
					traceLogA(  "drawVideoData: pkt.uiSampleTimeInMs %d < player.%d. trigger to empty old data",  iSampleTimeInMs,  pPlayer->video.m_var.uiSampleTimeInMs  );
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "drawVideoData: pkt.uiSampleTimeInMs %d < player.%d. trigger to empty old data"  ),  iSampleTimeInMs,  pPlayer->video.m_var.uiSampleTimeInMs  );
					#endif
			#endif

			q2TriggerToProcess(  &pPlayer->video.q2  );
		}
		if  (  pPlayer->video.m_var.uiSampleTimeInMs  )  {
			if  (  iSampleTimeInMs  >  (  int  )(  pPlayer->video.m_var.uiSampleTimeInMs  +  10000  )  )  {	//  2009/05/25. too old video data
				#ifdef  __DEBUG__  //  2014/06/15
						qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "drawVideoData: pkt.uiSampleTimeInMs %d > player.%d  +  10000. trigger to empty old data"  ),  iSampleTimeInMs,  pPlayer->video.m_var.uiSampleTimeInMs  );
				#endif
				q2TriggerToProcess(  &pPlayer->video.q2  );
			}
		}
	}


	iErr  =  0;
errLabel:
	return  iErr;
}



//
//  
//int  chkFromPlayerIndex_v(  QDC_OBJ_INFO  *  pQdcObjInfo,  myDRAW_VIDEO_DATA  *  pPkt,  void  *  p2  )
__declspec(  dllexport  )  int  chkFromPlayerIndex_v(  unsigned  int  uiTransformType,  void  *  pQY_TRANSFORM,  myDRAW_VIDEO_DATA  *  pPkt,  void  *  p2  )
{
	int			iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	if  (  uiTransformType  !=  CONST_uiTransformType_dec  )  return  -1;

	//if  (  !pQdcObjInfo  )  return  -1;
	QY_TRANSFORM  *  pTransform  =  (  QY_TRANSFORM  *  )pQY_TRANSFORM;	//  pQdcObjInfo->cfg.pParent_transform;
	if  (  !pTransform  )  return  -1;
	MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pTransform->pProcInfo;
	if  (  !pProcInfo  )  return  -1;  
	MSGR_ADDR			*	pAddr				=	pTransform->pAddr_logicalPeer;
	if  (  !pAddr  )  return  -1;
	int						iTaskId				=	pTransform->iTaskId;
	//
	AV_TRAN_INFO		*	pTranInfo_unused	=	(  AV_TRAN_INFO  *  )pTransform->pTranInfo_unused;
	if  (  !pTranInfo_unused  )  return  -1;
	//
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pTransform->pTask;
	if  (  !pTask  )  return  -1;

	//
	MIS_CNT  *  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );  

	//
	unsigned  short  usIndex  =  pTransform->index_activeMems_from;  

	//
	QY_MESSENGER_ID  *  pIdInfo_sender  =  &pTransform->video.idInfo;
	unsigned  int  uiTranNo_openAvDev  =  pTransform->video.tv.uiTranNo_openAvDev;  

	//
	QY_MESSENGER_ID  *  pIdInfo_peer  =  &pAddr->idInfo;


	BITMAPINFO  *  pBmpInfo_input  =  (  BITMAPINFO  *  )&pTransform->video.tv.vh_decompress.bih;

	int  iSampleTimeInMs  =  pPkt->head.uiSampleTimeInMs;
	unsigned  int  uiPts  =  pPkt->head.uiPts;	//  2015/02/19
	//
	unsigned  int  dwTickCnt_doPretrans  =  pPkt->debugInfo.dwTickCnt_doPretrans;	//  2015/02/24
	//  2016/12/27
	//unsigned  int  uiEventId_lastRecvd  =  pPkt->decInfo.uiEventId_lastRecvd;
	//
	TCHAR			tHint[256]	=	_T(  ""  );

	//  2017/08/17
	if  (  pIdInfo_sender->ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
		//
		#ifdef  __DEBUG__  //  2017/08/16
				traceLog(  _T(  "chkFromPlayerIndex_v: idInfo_sender is myslef. warning"  )  );
		#endif	
	}


	//  2014/04/22
#if  1
		//  2014/04/22		
		int  nIntervalInMs  =  40;		
		int		iFrameRate  =  pTransform->video.decInfo.dFrameRate_dec;
		if  (  iFrameRate  )  {
			nIntervalInMs  =  1000  /  iFrameRate;
		}		

		//									
		//		
		DWORD  dwCurTickCnt  =  myGetTickCount(  mynull  );
		//
		int	iNextIndex_preDec  =  0;
		long  lDiff_pre_post  =  0;
		{
			CQySyncObj	syncObj;
			TCHAR		tName[128];
			
			_sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s%d"  ),  CONST_mutexName_syncIndex_dec,  pTransform->iTaskId  );
			if  (  syncObj.sync(  tName  )  )  goto  errLabel;

			iNextIndex_preDec  =  pTransform->video.decInfo.iNextIndex_preDec;
			lDiff_pre_post  =  pTransform->video.decInfo.lDiff_pre_post;
			
			if  (  pTransform->video.decInfo.lDiff_pre_post  <=  0  )  {
				#if  0
				_sntprintf(  tHint,  mycountof(  tHint  ),  _T(  "chkFromPlayerIndex_v err: decInfo.lDiff_pre_post %d"  ),  pTransform->video.decInfo.lDiff_pre_post  );
				//goto  errLabel;
				showInfo_open0(  0,  0,  tHint  );
				tHint[0]  =  0;
				#endif
				}
			else  {
				  pTransform->video.decInfo.lDiff_pre_post  --  ;
			}
		}
		//				
		int  iNextIndex_postDec  =  0;
		//
		if  (  lDiff_pre_post  <  0  ||  lDiff_pre_post  >  mycountof(  pTransform->video.decInfo.iSampleTimeInMs_preDec_array  )  )  {
			_sntprintf(  tHint,  mycountof(  tHint  ),  _T(  "chkFromPlayerIndex_v err: lDiff_pre_post %d"  ),  lDiff_pre_post  );				
			//goto  errLabel;
			showInfo_open0(  0,  0,  tHint  );
			tHint[0]  =  0;
			}
		else  {
			  iNextIndex_postDec  =  mycountof(  pTransform->video.decInfo.iSampleTimeInMs_preDec_array  )  +  iNextIndex_preDec  -  lDiff_pre_post;
		}
		//
		iNextIndex_postDec  =  iNextIndex_postDec  %  mycountof(  pTransform->video.decInfo.iSampleTimeInMs_preDec_array  );

		//		
		iSampleTimeInMs  =  pTransform->video.decInfo.iSampleTimeInMs_preDec_array[iNextIndex_postDec];
		pPkt->head.uiSampleTimeInMs  =  iSampleTimeInMs;
		//  2015/02/19
		uiPts  =  pTransform->video.decInfo.uiPts_preDec_array[iNextIndex_postDec];
		pPkt->head.uiPts  =  uiPts;
		//  2015/02/24
		dwTickCnt_doPretrans  =  pTransform->video.decInfo.dwTickCnt_doPretrans[iNextIndex_postDec];
		pPkt->debugInfo.dwTickCnt_doPretrans  =  dwTickCnt_doPretrans;
		
		//	
		TCHAR	tBuf[256]  =  _T(  ""  );			
		int  e_doPretrans  =  0;
		//
		if  (  pProcInfo->cfg.debugStatusInfo.ucbShowPostDecVStatus  )  {	
			int  iLastIndex_preDec  =  0;							  
			if  (  !iNextIndex_preDec  )  iLastIndex_preDec  =  mycountof(  pTransform->video.decInfo.iSampleTimeInMs_preDec_array  )  -  1;
			else  iLastIndex_preDec  =  iNextIndex_preDec  -  1;							   

			int  st_preDec  =  pTransform->video.decInfo.iSampleTimeInMs_preDec_array[iLastIndex_preDec];
			//  2015/02/24
			e_doPretrans  =  GetTickCount(  )  -  pPkt->debugInfo.dwTickCnt_doPretrans;
			//
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "st_po %dms. d_po %dms. st_pre %dms, d_pre_po %dms. i_pre %d, i_po %d, lDiff_pre_post %d. "  ),  iSampleTimeInMs,  iSampleTimeInMs -  pTransform->video.decInfo.iSampleTimeInMs_postDec,  
				st_preDec,  st_preDec  -  iSampleTimeInMs,  iLastIndex_preDec,  iNextIndex_postDec,  lDiff_pre_post  );
		}
		//
#ifdef  __DEBUG__
		if (0) {
			_sntprintf(tBuf, mycountof(tBuf), _T("chk_v: pts %d, st %d"), uiPts, iSampleTimeInMs);
			showInfo_open0(0, 0, tBuf);
		}

#endif
		
		//
		//  2015/02/25
		//
		if  (  lDiff_pre_post  <  pTransform->video.decInfo.lowLatency.min_lDiff_pre_post  			
			||  abs(  (  long  )(  dwCurTickCnt  -  pTransform->video.decInfo.lowLatency.dwTickCnt_start  )  )  >  15000  )  
		{
			pTransform->video.decInfo.lowLatency.min_lDiff_pre_post  =  lDiff_pre_post;
			pTransform->video.decInfo.lowLatency.dwTickCnt_start  =  dwCurTickCnt;
		}
		//
		//
		BOOL  bNeedReset_lDiff_pre_post  =  FALSE;
		//
		int  min_lDiff_pre_post_ok  =  5;
		//
		if  (  pTransform->video.decInfo.lowLatency.min_lDiff_pre_post  >  min_lDiff_pre_post_ok
			&&  pTransform->video.decInfo.lowLatency.min_lDiff_pre_post  ==  lDiff_pre_post
			&&  dwCurTickCnt  -  pTransform->video.decInfo.lowLatency.dwTickCnt_start  >  5000  )  
		{
				bNeedReset_lDiff_pre_post  =  TRUE;
				//
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u.chkFromPlayerIndex_v: min_lDiff_pre_post %d > ok.%d, trigger to reset"  ),  pTransform->video.idInfo.ui64Id,  pTransform->video.decInfo.lowLatency.min_lDiff_pre_post,  min_lDiff_pre_post_ok  );				
				showInfo_open0(  0,  0,  tBuf  );			
		}
		//
		if  (  bNeedReset_lDiff_pre_post  )  {
			CQySyncObj	syncObj;
			TCHAR		tName[128];
			
			//
			int  lDiff_pre_post_resetVal  =  0;	//  1

			//
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u.chkFromPlayerIndex_v: lDiff_pre_post %d too big, set to 0"  ),  pTransform->video.idInfo.ui64Id,  pTransform->video.decInfo.lDiff_pre_post  );				
			showInfo_open0(  0,  0,  tBuf  );

			//
			_sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s%d"  ),  CONST_mutexName_syncIndex_dec,  pTransform->iTaskId  );
			if  (  syncObj.sync(  tName  )  )  goto  errLabel;

			pTransform->video.decInfo.lDiff_pre_post  =  lDiff_pre_post_resetVal;
		}

		//
		pTransform->video.decInfo.iSampleTimeInMs_postDec  =  iSampleTimeInMs;				
		pTransform->video.decInfo.cnt_postDec  ++  ;
		//  2014/12/06
		pTransform->video.decInfo.dwLastTickCnt_postDec  =  dwCurTickCnt;
		//		
		//  2015/02/24
		if  (  pProcInfo->cfg.debugStatusInfo.ucbShowPostDecVStatus  )  {	
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, cnt_po %d, e_doPretrans %d. pts %d"  ),  tBuf,  pTransform->video.decInfo.cnt_postDec,  e_doPretrans,  uiPts  );
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  "postDec:"  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );							   
		}


#endif

		//  2016/12/27
		//unsigned  int  uiEventId_lastRecvd_unused  =  0;

	//
	//  		
	return  tmp_chkFromPlayerIndex_v(  uiTranNo_openAvDev,  usIndex,  pBmpInfo_input,  iSampleTimeInMs,  0,  pIdInfo_sender,  pMisCnt,  pIdInfo_peer,  iTaskId,  pTransform,  &pTransform->iIndex_player,  pTask,  pPkt  );

errLabel:

	if  (  iErr  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  "postDec failed:"  ),  _T(  ""  ),  _T(  "%s"  ),  tHint  );							   
	}

	return  iErr;

}


