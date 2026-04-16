

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
int get_mql(  QY_MESSENGER_ID  idInfo_sender,  DWORD  dwCurTgt,  int  nQNodes_left,  int  nIntervalInMs_toAdjust_mql,  int  tmp_mql_ok,  int  tmp_mql_big_ok,  PLAY_v_mql  *  pMql  )
{
	int  iErr =  -1;
	PLAY_v_mql  &  mql  =  *pMql;
	TCHAR  tBuf_adjust[128];

	//
	if  (  abs(  (  long  )(  dwCurTgt  -  mql.dwTgt_start  )  )  >  nIntervalInMs_toAdjust_mql  )  {
			//  2015/09/15
			//_sntprintf(  tBuf_other,  mycountof(  tBuf_other  ),  _T(  "INT_ADJ %d. "  ),  nIntervalInMs_toAdjust_mql  /  1000  );
			//
			if  (  mql.mql  >  tmp_mql_ok  )  {														
				mql.bNeedReset  =  TRUE;											   											 
				//				
				_sntprintf(  tBuf_adjust,  mycountof(  tBuf_adjust  ),  _T(  "Adj: mql > mql_ok %d."  ),  tmp_mql_ok  );																 										   												 								
			}
			//
			mql.last_xql  =  mql.xql;
			mql.last_mql  =  mql.mql;
			//			
			mql.mql  =  nQNodes_left;	
			mql.xql  =  nQNodes_left;
			mql.dwTgt_start  =  dwCurTgt;		
			
			//
#ifdef  __DEBUG__
			if (0) {
				//if (nIntervalInMs_toAdjust_mql == 1000) 
				{
					_sntprintf(tBuf_adjust,mycountof(tBuf_adjust),_T("get_mql %I64u: last_mql %d, start to adjust mql. interval %d"), idInfo_sender.ui64Id,  mql.last_mql,  nIntervalInMs_toAdjust_mql);
					showInfo_open0(0, 0, tBuf_adjust);
				}
			}
#endif
			

			}		
		else  {			
			  if  (  nQNodes_left  <  mql.mql  )  {										 				
				  mql.mql  =  nQNodes_left;									 
			  }
			  if  (  nQNodes_left  >  mql.xql  )  {
				  mql.xql  =  nQNodes_left;
			  }
			  //				
			  if  (  mql.bNeedReset  )  {				
				  if  (  nQNodes_left  <=  tmp_mql_big_ok  )  {
					  mql.bNeedReset  =  FALSE;
					  //
					  _sntprintf(  tBuf_adjust,  mycountof(  tBuf_adjust  ),  _T(  "Adj ok: ql <= mql_big_ok %d."  ),  tmp_mql_big_ok  );						
				  }
			  }					

		}
	

		iErr  =  0;
errLabel:
		return  iErr;


}


 //  2011/12/10
int  postToDraw(  MC_VAR_isCli  *  pProcInfo,  unsigned  int  uiTranNo,  myDRAW_VIDEO_DATA  *  pPkt,  int  pktLen,  BOOL  *  pbPktRedirected,  unsigned  int  uiCapType,  int  iIndex_capBmp,  QY_MESSENGER_ID  *  pIdInfo_sender,  int  nPkts_left,  QY_MESSENGER_ID  *  pIdInfo_peer,  int  iTaskId,  HWND  hWnd_task,  PLAYER_ID  *  pPlayerId,  LPCTSTR  hint  )
{
	int							iErr						=	-1;
	if  (  !pProcInfo  )  return  -1;
	QY_MC					*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;
	TCHAR						tBuf[128];
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt)  return  -1;
	
	//
	if  (  !hint  )  hint  =  _T(  ""  );

	//  2016/02/18
	if  (  !pPlayerId  )  return  -1;
	int  index_player  =  pPlayerId->index_player;
	//
	if  (  index_player  <  0  ||  index_player  >=  pProcInfo->av.usCnt_players  )  return  -1;
	QY_PLAYER  *  pPlayer  =  &pProcInfo->av.pPlayers[index_player];
	PLAY_VIDEO_procInfo		*	pPlay						=	&pProcInfo->av.pPlayers[index_player].video;

	//  2015/10/01
	unsigned  short  usIndex  =  pPkt->usIndex_activeMems_from;  

	
	//  CQyQ2Help					q2Help;
	HWND						hWnd_display				=	NULL;
	
	int							iSampleTimeInMs				=	pPkt->head.uiSampleTimeInMs;
	//unsigned  int				uiPts						=	pPkt->head.uiPts;		//  2015/02/19


	int tmp_player_usFps = pPlay->usFps;
	//tmp_player_usFps = pPlay->m_var.status.fpsInfo.fps_real;
	if (!tmp_player_usFps)  tmp_player_usFps = 1;
	TCHAR* tWhere = pPlay->m_var.tWhere;


	//
	if  (  pPkt->usPktResType  !=  CONST_pktResType_sharedTex  )  {
		if  (  !pPkt->memory.m_pBuf  )  {
			#ifdef  __DEBUG__
					traceLogA(  (char*)  "postToDraw failed: pkt.pBuf is null"  );
			#endif
			showInfo_open0(  0,  _T(  "postToDraw"  ),  _T(  " failed, pkt.pBuf is null"  )  );
			return  -1;
		}
	}

	//
#ifdef  __DEBUG__
		if (pPkt->usPktResType == CONST_pktResType_sharedTex) {
			int  ii = 0;
		}
#endif


	//
	BITMAPINFO				*	pBmpInfo_input				=  (  BITMAPINFO  *  )&pPkt->bih;
	if  (  !pBmpInfo_input  )  return  -1;

#if  0
	BYTE					*	pInput						=	(  BYTE  *  )pPkt->memory.m_pBuf;
	if  (  !pInput  )  return  -1;
#endif
	
#ifdef  __DEBUG__
	    if  ( pProcInfo->cfg.debugStatusInfo.ucbPrint_v_draw  )  {		
			traceLog((TCHAR*)  _T(  "postToDraw: SampleTime %d, dwTickCnt %d, SampleTime_newRecvd %d"  ),  iSampleTimeInMs,  GetTickCount(  ),  pPlay->m_var.uiSampleTimeInMs_newRecvd  );
		}
#endif

	//  2013/07/03
#if  1	//  
		//
		if  (  pPlay->m_var.status.fillD3d.bFilled_d3dData  )  {
			dyn_fillData_d3d_setDataReady(  pPkt,  index_player  );
		}
#endif


		//
		int  dwTickCnt = myGetTickCount(mynull);//timeGetTime(  );	 //  pPkt->debugInfo.dwTickCnt_postToDraw;	//  timeGetTime(  );
		//
		if (pPlay->m_var.status.dwLastTickCnt_postToDraw) {
			pPlay->m_var.status.nInterval_real_postToDraw = dwTickCnt - pPlay->m_var.status.dwLastTickCnt_postToDraw;
		}
		pPlay->m_var.status.dwLastTickCnt_postToDraw = dwTickCnt;



	//  2013/10/04	
	BOOL  bD3dOnly  =  FALSE;
	GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
	if  (  pGBuf  )  { 
		if  (  hWnd_task  ==  pGBuf->hWall_d3d  )  {
			bD3dOnly  =  TRUE;
		}
	}
	
	if (!bD3dOnly) {	//  2013/10/04

		//
		MIS_MSG_procVideo_qmc		msg;
		memset(&msg, 0, sizeof(msg));
		msg.uiType = CONST_misMsgType_procVideo_qmc;
		//  msg.ucbLocalAv  =  TRUE;
		msg.uiCapType = uiCapType;
		msg.iIndex_capProcInfo = iIndex_capBmp;

		//  2009/04/25
		if (pIdInfo_sender)  msg.idInfo_sender.ui64Id = pIdInfo_sender->ui64Id;
		//  2014/09/04
		//msg.dynBmp.usIndex_obj  =  pPkt->decInfo.dynBmp.usIndex_obj;
		//
		msg.uiTranNo_openAvDev = uiTranNo;
		msg.usIndex = usIndex;

		//
		msg.iTaskId = iTaskId;
		msg.hWnd_task = hWnd_task;		//  2009/09/14
		//  2016/12/27
		//msg.uiEventId_lastRecvd  =  uiEventId_lastRecvd;

		//
		if (pMisCnt)  msg.pMisCnt = pMisCnt;
		if (pIdInfo_peer)  msg.idInfo_peer.ui64Id = pIdInfo_peer->ui64Id;

		memcpy(&msg.bih, &pBmpInfo_input->bmiHeader, sizeof(msg.bih));

		//  2013/10/08
		//  msg.ucbAlphaed  =  pPkt->ucbAlphaed;

		//
		//  msg.data  =  pData_allocated  =  (  BYTE  *  )mymalloc(  msg.bih.biSizeImage  );
		/*
		msg.data  =  (  BYTE  *  )mallocObj.malloc(  msg.bih.biSizeImage  );
		if  (  !msg.data  )  goto  errLabel;
		memcpy(  msg.data,  pInput,  pBmpInfo_input->bmiHeader.biSizeImage  );
		*/
		if (pPkt->usPktResType != CONST_pktResType_sharedTex) {
			if (pPkt->uiSize_dec < msg.bih.biSizeImage) {
#ifdef  __DEBUG__
				traceLog((TCHAR*)_T("postToDraw: pkt.uiSize_dec error, pPkt->uiSize_dec %d < biSizeImage %d"), pPkt->uiSize_dec, msg.bih.biSizeImage);
#endif	
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("postToDraw: pkt.uiSize_dec error, pPkt->uiSize_dec %d < biSizeImage %d"), pPkt->uiSize_dec, msg.bih.biSizeImage);
				goto  errLabel;
			}
		}
		//  
		//  memcpy(  &msg.memory,  &pPkt->memory,  sizeof(  msg.memory  )  );
		memcpy(&msg.pkt, pPkt, sizeof(msg.pkt));

		//
		//msg.playerId.index_player  =  index_player;		//  2009/10/03
		msg.playerId = *pPlayerId;						//  2016/02/19

		//  2012/11/09
		M_msg_setNo(*pPkt, msg);


		//
		if (pPkt->usPktResType == CONST_pktResType_sharedTex) {
#if 10
			CAP_images* pImgs;
			//
			pImgs = &pProcInfo->av.confLayout.peerZone.images;
			bool  bNeedRefreshImgs_peer = false;
			refreshLayoutCapImages_forD3d(&msg, pImgs, &bNeedRefreshImgs_peer);
			//
			pImgs = &pProcInfo->av.confLayout.otherZone.images;
			bool  bNeedRefreshImgs_other = false;
			refreshLayoutCapImages_forD3d(&msg, pImgs, &bNeedRefreshImgs_other);
			//
			if (bNeedRefreshImgs_peer || bNeedRefreshImgs_other) {
				//
				PostMessage(pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_needRefreshImgs, pPkt->iTaskId);
			}
			//
			iErr = 0;  goto  errLabel;
#endif
		}

		//
#ifdef  __DEBUG__
		if (msg.idInfo_sender.ui64Id) {
			int  ii = 0;
		}
#endif

		do  {
			//
			pPlay->m_var.totalPkts_postToDraw++;
			int nPkts_left = 1;	//  对postToDraw, 不需要过多缓存，所以这里可以赋成1

			//
			Param_bPktSkipped param = { 0 };
			//
			int nQNodes = getQ2Nodes(&pPlay->displayQ2);
			bool  b4k = is4k(msg.bih.biWidth, msg.bih.biHeight);
			unsigned  __int64 nFactor = 0;
			//
			//if (b4k) 
			{
				if (bPktSkipped(& param, CONST_nWhere_postToDraw, pPlay->usFps, 0, nQNodes, pPlay->m_var.totalPkts_postToDraw, nPkts_left, b4k, &pPlay->m_var.totalPkts_lastOk_postToDraw, &nFactor)) {
					_sntprintf(tBuf, mycountof(tBuf), _T("postToDraw: fps %d, nQNodes %d, totalPkts %d, nFactor %I64u, skipped"), (int)tmp_player_usFps, nQNodes, pPlay->m_var.totalPkts_postToDraw, nFactor);
					showInfo_open0(0, 0, tBuf);
					//
					break;
				}
			}

			//
#ifdef  __DEBUG__
			if (1) {
				if (nQNodes > 10) {
					_sntprintf(tBuf, mycountof(tBuf), _T("postToDraw: fps %d, nQNodes %d, totalPkts %d, nFactor %I64u, ok"), (int)tmp_player_usFps, nQNodes, pPlay->m_var.totalPkts_postToDraw, nFactor);
					showInfo_open0(0, 0, tBuf);
				}
			}
#endif

			//  to get hWnd_display		
			if (hWnd_task && IsWindow(hWnd_task)) {		//  2009/09/09
				hWnd_display = hWnd_task;
			}
			else  if (!msg.idInfo_peer.ui64Id && msg.uiCapType) {
				switch (msg.uiCapType) {
				case  CONST_capType_av: {
					CAP_procInfo_video* pVc;
					pVc = (CAP_procInfo_video*)getCapBmpBySth(pProcInfo, msg.iIndex_capProcInfo, 0);
					if (!pVc || pVc->uiType != msg.uiCapType)  break;
					if (pVc->curhWnd) {
						if (!IsWindow(pVc->curhWnd))  pVc->curhWnd = NULL;
						else  hWnd_display = pVc->curhWnd;
					}
				}
									  break;
				case  CONST_capType_mediaFile: {
					CAP_procInfo_mediaFileBmp* pBc;
					pBc = (CAP_procInfo_mediaFileBmp*)getCapBmpBySth(pProcInfo, msg.iIndex_capProcInfo, 0);
					if (!pBc || pBc->uiType != msg.uiCapType)  break;
					if (pBc->curhWnd) {
						if (!IsWindow(pBc->curhWnd))  pBc->curhWnd = NULL;
						else  hWnd_display = pBc->curhWnd;
					}
				}
											 break;
				default:
#ifdef  __DEBUG__
					traceLogA((char*)"doMainWnd_procVideo: unprocessed capType %d", msg.uiCapType);
#endif
					break;
				}
			}
			else {
				if (!IsWindow(pPlay->m_var.hWnd_display)) {
					HWND  hWnd;
					if (findTalker(pQyMc, &msg.idInfo_peer, &hWnd)) {
#ifdef  __DEBUG__
						traceLog((TCHAR*)_T("postToDraw: findTalker failed, iIndex_player %d, idInfo_peer %I64u."), index_player, msg.idInfo_peer.ui64Id);
#endif
						qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("postToDraw failed: findTalker failed, iIndex_player %d, idInfo_peer %I64u."), index_player, msg.idInfo_peer.ui64Id);
						goto  errLabel;
					}
					pPlay->m_var.hWnd_display = hWnd;
				}
				hWnd_display = pPlay->m_var.hWnd_display;
			}
			if (!hWnd_display) {
				traceLogA((char*)"postToDraw failed. can't get hWnd_display");
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("postToDraw failed. can't get hWnd_display"));
				goto  errLabel;
			}

			//
			if (!pbPktRedirected || *pbPktRedirected) {
				traceLogA((char*)"postToDraw: pbPktRedirected error");
				goto  errLabel;
			}
			//
			if (!q2PostMsg(&msg, sizeof(msg), &pPlay->displayQ2, _T("postToDraw"))) {
				*pbPktRedirected = TRUE;
			}
			int nNodes_displayQ2 = getQ2Nodes(&pPlay->displayQ2);
			if (nNodes_displayQ2 < 5
				|| isQ2Warning(&pPlay->displayQ2, 10)
				)
			{
				PostMessage(hWnd_display, CONST_qyWm_postComm, CONST_qyWmParam_guiMsgArrive, index_player);
			}

			//
		} while (false);
		
		//
	}

	//
#if  1



	
	//
#if 0
	unsigned  int  uiPts_last  =  pPlay->m_var.status.uiPts_last;
	pPlay->m_var.status.uiPts_last  =  pPkt->head.uiPts;	//  2015/02/19
#endif

	
	//  215/09/10
	//
	int  nIntervalInMs_fillD3dData; nIntervalInMs_fillD3dData = pPlay->m_var.status.fillD3d.param0.nIntervalInMs_fillData + pPlay->m_var.status.fillD3d.param1.nIntervalInMs_fillData;
	//
	//  2015/09/14
	int  nQNodes_left; nQNodes_left = getQ2Nodes(&pPlay->q2) + nPkts_left;
	//


#endif

	//  2013/09/09
	if  (  pPlay->m_var.status.fillD3d.bFilled_d3dData  )  {
		if (pPlay->m_var.lowLatency.dwToInMs_toPostDraw) {
			pPlay->m_var.status.ucSkipped_for_d3dData = 0;
		}
		else  {
			  pPlay->m_var.status.ucSkipped_for_d3dData  =  (  nIntervalInMs_fillD3dData  /  16  );
			  if  (  pPlay->m_var.status.ucSkipped_for_d3dData  )  pPlay->m_var.status.ucSkipped_for_d3dData  --;
		}		
	}



		

	//
	iErr  =  0;  
	
errLabel:


	//
	doCalcMql(pProcInfo, uiTranNo, pPkt, pIdInfo_sender, nPkts_left, pIdInfo_peer, iTaskId, pPlayerId, hint);



	return  iErr;
}

 int doCalcMql(MC_VAR_isCli* pProcInfo, unsigned  int  uiTranNo, myDRAW_VIDEO_DATA* pPkt, QY_MESSENGER_ID* pIdInfo_sender, int  nPkts_left, QY_MESSENGER_ID* pIdInfo_peer, int  iTaskId, PLAYER_ID* pPlayerId, LPCTSTR  hint)
{
	int  iErr = -1;

	//  2016/02/18
	if (!pPlayerId)  return  -1;
	int  index_player = pPlayerId->index_player;
	//
	if (index_player < 0 || index_player >= pProcInfo->av.usCnt_players)  return  -1;
	QY_PLAYER* pPlayer = &pProcInfo->av.pPlayers[index_player];
	PLAY_VIDEO_procInfo* pPlay = &pProcInfo->av.pPlayers[index_player].video;

	int  tmp_player_usFps = pPlay->usFps;
	if (!tmp_player_usFps)  return  -1;

	//
	int							iSampleTimeInMs = pPkt->head.uiSampleTimeInMs;

	//  2015/09/14
	int  nQNodes_left = getQ2Nodes(&pPlay->q2) + nPkts_left;
	//
	TCHAR  tBuf_node[128] = _T("");
	int	 nInterval_iSampleTimeInMs = iSampleTimeInMs - pPlay->m_var.status.iSampleTimeInMs_last;
	TCHAR  tBuf_adjust[128] = _T("");
	//
	pPlay->m_var.status.iSampleTimeInMs_last = iSampleTimeInMs;



	////////////////////////////	
#if 10
	unsigned  int  uiPts_last = pPlay->m_var.status.uiPts_last;
	pPlay->m_var.status.uiPts_last = pPkt->head.uiPts;	//  2015/02/19
#endif

	int  dwTickCnt = myGetTickCount(mynull);//timeGetTime(  );	 //  pPkt->debugInfo.dwTickCnt_postToDraw;	//  timeGetTime(  );


#if 10
	//TCHAR  tBuf_node[128] = _T("");
	//int	 nInterval_iSampleTimeInMs  =  iSampleTimeInMs  -  pPlay->m_var.status.iSampleTimeInMs_last;	
	//TCHAR  tBuf_adjust[128] = _T("");
	//
	//pPlay->m_var.status.iSampleTimeInMs_last  =  iSampleTimeInMs;
	//
	if (pProcInfo->cfg.debugStatusInfo.ucbShowToDrawStatus) {
		//
		//  2015/09/05
		int  iE_from_read = -1;
		if (pPkt->debugInfo.dwTickCnt_proc_io_read)  iE_from_read = dwTickCnt - pPkt->debugInfo.dwTickCnt_proc_io_read;
		int  iE_from_pretrans = -1;
		if (pPkt->debugInfo.dwTickCnt_doPretrans)  iE_from_pretrans = dwTickCnt - pPkt->debugInfo.dwTickCnt_doPretrans;
		int  iE_from_drawVideoData = -1;
		if (pPkt->debugInfo.dwTickCnt_drawVideoData)  iE_from_drawVideoData = dwTickCnt - pPkt->debugInfo.dwTickCnt_drawVideoData;
		//
		int  iE_from_playPkt_start = dwTickCnt - pPkt->debugInfo.dwTickCnt_playPkt_start;
		//
		//
#if  0
		_sntprintf(tBuf_node, mycountof(tBuf_node), _T("bAdj %d. bReset %d"),
			pPlay->m_var.lowLatency.bNeedAdjust2,
			pPlay->m_var.lowLatency.mql.bNeedReset);
#endif
		//
		_sntprintf(tBuf_node, mycountof(tBuf_node), _T("%s mql %d, last %d, mql_ok %d. nodes %d."),
			tBuf_node,
			pPlay->m_var.lowLatency.mql.mql_1s.mql,
			pPlay->m_var.lowLatency.mql.mql_1s.last_mql,
			//
			pPlay->m_var.lowLatency.mql.mql_ok,
			//
			nQNodes_left
		);
		//
#ifdef  __DEBUG__
#endif
		//
	}
#endif



		//  2015/03/02											
		int 		M_mql_big_ok = 8;
		int 		M_mql_ok = 4;	// 3;	// 1;	//0	//3
		//
#define		M_mql_big_ok_sharedTex										4
#define		M_mql_ok_sharedTex											2
//
#define		MIN_mql_ok_sharedTex										3

//
#define		M_mql_big_ok_15fps											4	//  6
#define		M_mql_ok_15fps												2	//  1				


//											
		int  tmp_mql_big_ok = M_mql_big_ok_15fps;
		int  tmp_mql_ok = M_mql_ok_15fps;
		if (tmp_player_usFps > 15) {
			//
			if (pPkt->usPktResType == CONST_pktResType_sharedTex) {
				tmp_mql_big_ok = M_mql_big_ok_sharedTex * tmp_player_usFps / 30;
				tmp_mql_ok = M_mql_ok_sharedTex * tmp_player_usFps / 30;
				//
				if (pPkt->sharedTex.pktSharedTexInfo.usMax_intervalInMs_renderFrame) {
					//
					int  frameTimeInMs = 1000 / tmp_player_usFps;
					if (!frameTimeInMs)  frameTimeInMs = 33;
					//
					int  nNeeded = M_get_ucMaxCnt(pPkt->sharedTex.pktSharedTexInfo.usMax_intervalInMs_renderFrame, frameTimeInMs);
					if (pPkt->sharedTex.pktSharedTexInfo.ucMaxCnt_sharedTexes <= nNeeded) {
						int  nDiff = 12;	//  10;
						if (pPkt->sharedTex.pktSharedTexInfo.ucMaxCnt_sharedTexes > nDiff) {
							nNeeded = pPkt->sharedTex.pktSharedTexInfo.ucMaxCnt_sharedTexes - nDiff;
						}
					}
					//
					if (tmp_mql_ok < nNeeded)  tmp_mql_ok = nNeeded;
					//
					if (tmp_mql_ok > 10)  tmp_mql_big_ok = tmp_mql_ok + 1;
					else  tmp_mql_big_ok = tmp_mql_ok + 1;
					//
				}
			}
			else {
				tmp_mql_big_ok = M_mql_big_ok * tmp_player_usFps / 30. + 0.5;
				tmp_mql_ok = M_mql_ok * tmp_player_usFps / 30. + 0.5;
			}
		}
		//

		//
		//  
		if (!pPlayer->idInfo_recorder.ui64Id) {
			if (!pPkt->input.bRtsp) {				//  2015/03/12. 只有纯本地采集卡才能降到0. 
				tmp_mql_big_ok = 0;
				tmp_mql_ok = 0;
			}
		}

		//  2015/09/16
		if (pPlay->m_var.lowLatency.mql.mql_ok != tmp_mql_ok) {
			pPlay->m_var.lowLatency.mql.mql_ok = tmp_mql_ok;
		}
		if (pPlay->m_var.lowLatency.mql.mql_big_ok != tmp_mql_big_ok) {
			pPlay->m_var.lowLatency.mql.mql_big_ok = tmp_mql_big_ok;
		}

		//  2015/09/15
		//int  nIntervalInMs_toAdjust_mql  =  CONST_nIntervalInMs_toAdjust_mql_good_1s;


		//
		//int nQNodes_left = getQ2Nodes(&pPlay->q2)  +  nPkts_left;



		//  2015/02/25		
		DWORD  dwCurTgt = dwTickCnt;
		get_mql(*pIdInfo_sender, dwCurTgt, nQNodes_left, 1000, tmp_mql_ok, tmp_mql_big_ok, &pPlay->m_var.lowLatency.mql.mql_1s);
		//get_mql(*pIdInfo_sender, dwCurTgt, nQNodes_left, 2000, tmp_mql_ok, tmp_mql_big_ok, &pPlay->m_var.lowLatency.mql.mql_2s);
		get_mql(*pIdInfo_sender, dwCurTgt, nQNodes_left, 3000, tmp_mql_ok, tmp_mql_big_ok, &pPlay->m_var.lowLatency.mql.mql_3s);
		//get_mql(*pIdInfo_sender, dwCurTgt, nQNodes_left, 5000, tmp_mql_ok, tmp_mql_big_ok, &pPlay->m_var.lowLatency.mql.mql_5s);
		get_mql(*pIdInfo_sender, dwCurTgt, nQNodes_left, 8000, tmp_mql_ok, tmp_mql_big_ok, &pPlay->m_var.lowLatency.mql.mql_8s);




		//
	

	//
	bool  bSkip_showInfo = false;


	//
	if (pProcInfo->cfg.debugStatusInfo.ucbShowToDrawStatus) {
		//TCHAR  ttt[32]  =  _T(  ""  );
		//
		TCHAR  tBuf[256];
		_sntprintf(tBuf, mycountof(tBuf), _T("%I64u,%d: pts %d. nInt %d, real %d. "), pIdInfo_sender->ui64Id, uiTranNo, pPkt->head.uiPts, nInterval_iSampleTimeInMs, pPlay->m_var.status.nInterval_real_postToDraw);
		//
#if  0
		_sntprintf(tBuf, mycountof(tBuf), _T("%s pkt.e_from_start %d"), tBuf, pPkt->head.uiSampleTimeInMs - pPlay->m_var.lowLatency.calc.uiSampleTimeInMs_start);
#endif
#if  0
		_sntprintf(tBuf, mycountof(tBuf), _T("%s st %.1f"), tBuf, pPkt->head.uiSampleTimeInMs / 1000.);
#endif
		//
		//
		if (pPkt->usPktResType == CONST_pktResType_sharedTex) {
			int  real_index = 0;
			if (pPkt->sharedTex.pktSharedTexInfo.ucMaxCnt_sharedTexes)  real_index = pPkt->sharedTex.pktSharedTexInfo.uiSeqNo % pPkt->sharedTex.pktSharedTexInfo.ucMaxCnt_sharedTexes;
			_sntprintf(tBuf, mycountof(tBuf), _T("%s maxTexes %d, shrTex.sn %d, ind %d, maxInt_dec %d."), tBuf, (int)pPkt->sharedTex.pktSharedTexInfo.ucMaxCnt_sharedTexes, pPkt->sharedTex.pktSharedTexInfo.uiSeqNo,
				real_index,
				(int)pPkt->sharedTex.pktSharedTexInfo.usMax_intervalInMs_renderFrame);
		}
#if 0
		_sntprintf(tBuf, mycountof(tBuf), _T("%s to %d, nAh %d, nDelay %d. "), tBuf,
			pPlay->m_var.lowLatency.dwToInMs_toPostDraw,
			pPlay->m_var.lowLatency.ah.nAh, pPlay->m_var.lowLatency.ah.nDelay);
#endif
		//
		_sntprintf(tBuf, mycountof(tBuf), _T("%s to %d. "), tBuf,
			pPlay->m_var.lowLatency.dwToInMs_toPostDraw
		);

		//
		_sntprintf(tBuf, mycountof(tBuf), _T("%s %s."), tBuf, pPlay->m_var.lowLatency.bNoAudio ? _T("NA") : _T("A"));
		//
		if (pPlay->m_var.lowLatency.tBuf[0])  _sntprintf(tBuf, mycountof(tBuf), _T("%s %s"), tBuf, pPlay->m_var.lowLatency.tBuf);
		//
		_sntprintf(tBuf, mycountof(tBuf), _T("%s %s %s"), tBuf, tBuf_adjust, tBuf_node);
		_sntprintf(tBuf, mycountof(tBuf), _T("%s %s"), tBuf, hint);

		//
		bool  bNoLocal = false;

#ifdef  __DEBUG__
		bNoLocal = true;
		//
		if (bNoLocal) {
			if (!pPlayer->idInfo_recorder.ui64Id) {
				bSkip_showInfo = true;
			}
		}
#endif

		//
		if (!bSkip_showInfo) {
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T("doCalcMql: "), tBuf);
		}

	}

	//
	TCHAR  tBuf[128];



	//
	//  2016/04/10	
	if (!pPlay->m_var.lowLatency.calc.dwTickCnt_start2
		|| pPkt->head.uiPts != uiPts_last + 1
		|| pPlay->m_var.lowLatency.bNeedAdjust3
#if 0
		||  (  pPlay->m_var.lowLatency.calc.last_mql  >  pPlay->m_var.lowLatency.mql.mql_1s.last_mql
			&&  pPlay->m_var.lowLatency.mql.mql_1s.last_mql  >  pPlay->m_var.lowLatency.mql.mql_ok  )
#endif

		)
	{
		bool  bSkip_ptsChk = false;
#ifdef  __DEBUG__
		//bSkip_ptsChk = true;
#endif
		//
#if 10
		if (!bSkip_ptsChk) {
			if (pPkt->head.uiPts != uiPts_last + 1) {
				_sntprintf(tBuf, mycountof(tBuf), _T("doCalcMql: %I64u, err: pts %d != 1 + pts_last %d. reset play.sampleTimeInMs_start"), pPlayer->idInfo_recorder.ui64Id, pPkt->head.uiPts, uiPts_last);
				showInfo_open0(0, 0, tBuf);
			}
		}
#endif

		//
		//if (pProcInfo->cfg.debugStatusInfo.ucbShowToDrawStatus) 
		{
			//if (!bSkip_showInfo) 
			{
				_sntprintf(tBuf, mycountof(tBuf), _T("playVideo: %I64u, uiSampleTimeInMs_start1 adjust"), pPlayer->idInfo_recorder.ui64Id);
				if (pPlay->m_var.lowLatency.mql.mql_1s.last_mql > pPlay->m_var.lowLatency.mql.mql_ok) {
					_sntprintf(tBuf, mycountof(tBuf), _T("%s. last.mql %d > mql_ok %d"), tBuf, pPlay->m_var.lowLatency.mql.mql_1s.last_mql, pPlay->m_var.lowLatency.mql.mql_ok);
				}
				showInfo_open0(0, 0, tBuf);
			}
		}

		//
		pPlay->m_var.lowLatency.calc.uiPts_start = pPkt->head.uiPts;
		pPlay->m_var.lowLatency.calc.dwTickCnt_start2 = dwTickCnt;
		pPlay->m_var.lowLatency.calc.uiSampleTimeInMs_start1 = pPkt->head.uiSampleTimeInMs;

		//
		pPlay->m_var.lowLatency.bNeedAdjust3 = false;
		memset(&pPlay->m_var.lowLatency.ah, 0, sizeof(pPlay->m_var.lowLatency.ah));
	}

	//
	int  nAh = 0;
	int  nDelay = 0;
	//
	if (pPlay->m_var.lowLatency.mql.mql_1s.last_mql) {
		//
		if (nQNodes_left < 1) {
			nDelay = 1;
		}
		else {
			if (pPlay->m_var.lowLatency.mql.mql_1s.last_mql > pPlay->m_var.lowLatency.mql.mql_ok
				)
			{
				int  n = pPlay->m_var.lowLatency.mql.mql_1s.last_mql - pPlay->m_var.lowLatency.mql.mql_ok;
				int  iFps_real = pPlay->usFps;// pPlay->m_var.status.fpsInfo.fps_real;
				if (iFps_real) {
					float  fn = n / (float)iFps_real;
					if (fn > 0.5)  nAh = pPlay->m_var.status.fpsInfo.avgTimePerFrameInMs * 0.5;
					else {
						nAh = fn * pPlay->m_var.status.fpsInfo.avgTimePerFrameInMs;
					}
					//							
					if (nAh) {
						if (nQNodes_left < 5) {
							int  iVal;
							iVal = nAh * (nQNodes_left * 1.0 / 5);
							if (iVal)  nAh = iVal;
						}
					}
					//
				}
			}
		}
	}
	pPlay->m_var.lowLatency.ah.nAh = nAh;
	pPlay->m_var.lowLatency.ah.nDelay = nDelay;

	//
	memset(&pPlay->m_var.lowLatency.ah, 0, sizeof(pPlay->m_var.lowLatency.ah));


	//
	time_t  t;
	time(&t);
	if (pPlay->m_var.lowLatency.chk_st_start1.tStart_toChk_st_start1 != t) {
		pPlay->m_var.lowLatency.chk_st_start1.tStart_toChk_st_start1 = t;
		//
		if (pPlay->m_var.lowLatency.mql.mql_1s.last_mql <= pPlay->m_var.lowLatency.mql.mql_ok) {
			pPlay->m_var.lowLatency.chk_st_start1.nNeedAhead = 0;
		}
		else {
			pPlay->m_var.lowLatency.chk_st_start1.nNeedAhead = pPlay->m_var.lowLatency.mql.mql_1s.last_mql - pPlay->m_var.lowLatency.mql.mql_ok;
			pPlay->m_var.lowLatency.chk_st_start1.nTimes_ahead = pPlay->usFps;	// 
		}
	}

	//  通过将时间戳参考点前移，使播放加快
	if  (  pPlay->m_var.lowLatency.mql.mql_1s.last_mql  >  pPlay->m_var.lowLatency.mql.mql_ok  &&  
		//pPlay->m_var.lowLatency.mql.mql_2s.last_mql  >  pPlay->m_var.lowLatency.mql.mql_ok  &&
		pPlay->m_var.lowLatency.mql.mql_3s.last_mql  >  pPlay->m_var.lowLatency.mql.mql_ok  &&
		//pPlay->m_var.lowLatency.mql.mql_5s.last_mql > pPlay->m_var.lowLatency.mql.mql_ok &&
		pPlay->m_var.lowLatency.mql.mql_8s.last_mql > pPlay->m_var.lowLatency.mql.mql_ok &&
		nQNodes_left > pPlay->m_var.lowLatency.mql.mql_ok
		) 
	{
		if (pPlay->m_var.lowLatency.chk_st_start1.nTimes_ahead) {
			unsigned  int nAhead = min(pPlay->m_var.lowLatency.chk_st_start1.nNeedAhead, pPlay->m_var.status.fpsInfo.avgTimePerFrameInMs);

			//
			if (nAhead)
			{
				pPlay->m_var.lowLatency.calc.uiSampleTimeInMs_start1 += nAhead;

				//
				if (pProcInfo->cfg.debugStatusInfo.ucbShowToDrawStatus) {
					if (pPlayer->idInfo_recorder.ui64Id) {
						_sntprintf(tBuf, mycountof(tBuf), _T("doCalcMql %I64u: st_start1.nAhead %dms"), pPlayer->idInfo_recorder.ui64Id, nAhead);
						_sntprintf(tBuf, mycountof(tBuf), _T("%s mql_8 %d. n_left %d"), tBuf, pPlay->m_var.lowLatency.mql.mql_8s.last_mql,  nQNodes_left);
						showInfo_open0(0, 0, tBuf);
					}
				}
			}
			//
			pPlay->m_var.lowLatency.chk_st_start1.nTimes_ahead--;
		}
	}
	else {
		//
		if (pPlay->m_var.lowLatency.stat_noMsgAndWait.nTimes) {
			pPlay->m_var.lowLatency.chk_st_start1.nNeedDelay = min(10, 2 * pPlay->m_var.lowLatency.stat_noMsgAndWait.nTimes);
			pPlay->m_var.lowLatency.chk_st_start1.nTimes_delay = pPlay->usFps;
			//
			pPlay->m_var.lowLatency.stat_noMsgAndWait.nTimes = 0;

		}

		//
		if  (  pPlay->m_var.lowLatency.chk_st_start1.nTimes_delay)  {
			unsigned  int  nDelay = 2;
			//
			if (nDelay) {
				if (pPlay->m_var.lowLatency.calc.uiSampleTimeInMs_start1 > nDelay) {
					pPlay->m_var.lowLatency.calc.uiSampleTimeInMs_start1 -= nDelay;

					//
					if (pProcInfo->cfg.debugStatusInfo.ucbShowToDrawStatus) {
						if (pPlayer->idInfo_recorder.ui64Id) {
							_sntprintf(tBuf, mycountof(tBuf), _T("doCalcMql %I64u: st_start1.nDelay %dms"), pPlayer->idInfo_recorder.ui64Id, nDelay);
							_sntprintf(tBuf, mycountof(tBuf), _T("%s mql_8 %d"), tBuf, pPlay->m_var.lowLatency.mql.mql_8s.last_mql);
							showInfo_open0(0, 0, tBuf);
						}
					}
				}
			}
			//
			pPlay->m_var.lowLatency.chk_st_start1.nTimes_delay--;
		}
	}
	//


	//			
#ifdef  __DEBUG__
		//
#endif

	iErr = 0;

	return  iErr;

}

