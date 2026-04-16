
#include	"stdafx.h"
 
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>
#include	<stddef.h>

#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"
#include	"qmcSound_dx.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyTick.h"

#include	"qisWebRtcPublic.h"
#include	"qy_qBuf2_defs.h"
#include	"ctxQmc.h"


//  2017/10/13
#define		M_chk_pts(  pPlayerAudio, pkt  )	\
				{  if  (  pPlayAudio->lowLatency.ptsInfo.uiPts_lastRecvd  &&  pkt.head.uiPts != pPlayAudio->lowLatency.ptsInfo.uiPts_lastRecvd + 1 )  {		\
						pPlayAudio->lowLatency.ptsInfo.nErr_ptsMissed  ++  ;			\
					    if  (  pProcInfo->cfg.debugStatusInfo.ucbShowPlayAudioStatus  )  {			\
							_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "my_inStream: pts missed: pts_lastRecvd %d, pkt.pts %d. nErr_ptsMissed %d"  ),  pPlayAudio->lowLatency.ptsInfo.uiPts_lastRecvd,  pkt.head.uiPts, pPlayAudio->lowLatency.ptsInfo.nErr_ptsMissed  );	\
						   showInfo_open0(  0,  0,  tBuf  );						\
						}														\
					}															\
					pPlayAudio->lowLatency.ptsInfo.uiPts_lastRecvd  =  pkt.head.uiPts;	\
				}



//
int fillSilence(int wBits, char* buf, int bufLen)
{
	//int  wBits = 16;
	FillMemory(buf, bufLen, (wBits == 8) ? 128 : 0);

	return  0;
}

//
int  my_inStream(  void  *  p0,  void  *  p1,  void  * p2  )
{
	int  nRead  =  0;
	//
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	//
	 QY_PLAYER				*	pPlayer  =  (  QY_PLAYER  *  )p0;
	 PLAY_AUDIO_procInfo	*	pPlayAudio  =  &pPlayer->audio;
	 char  *  buf  =  (  char  *  )p1;
	 int  bufLen  =  (  int  )p2;

	 //
	 TCHAR  tBuf[128];
	 int  wBits = 16;

	 //
	 bool  bDbg = false;
#ifdef  __DEBUG__
	 if (pPlayer->idInfo_recorder.ui64Id) {
		 bDbg = true;
	 }
#endif 

	 //
	 int n10ms = pPlayAudio->ah.wfx.nAvgBytesPerSec / 100;
	 if (!n10ms || bufLen != n10ms) 
	 {
		 _sntprintf(tBuf, mycountof(tBuf), _T("my_inStream failed: n10ms is 0 or bufLen %d != n10ms %d"), bufLen, n10ms);
		 showInfo_open0(0, 0, tBuf);
		 return  0;
	 }

	 //
	 pPlayAudio->m_var.nTimes_my_inStream++;

	 //
	 if (pPlayAudio->bQuit) {
		 pPlayAudio->bNeedStop_webRtc_my_inStream = TRUE;
		 pProcInfo->ctrl.bNeedChkPlayers = TRUE;

		 //
		 nRead = 0;  return  0;// goto  errLabel;
	 }

	 //
#if  10
	 //
	 if  (  pPlayAudio->cache.pLeft  !=  pPlayAudio->cache.pBuf  )  {						   
		 if  (  pPlayAudio->cache.nLeft  )  memcpy(  pPlayAudio->cache.pBuf,  pPlayAudio->cache.pLeft,  pPlayAudio->cache.nLeft  );				   
		 pPlayAudio->cache.pLeft  =  pPlayAudio->cache.pBuf; 			   
	 }

	 //
#ifdef  __DEBUG__
		#if  0
		if  (  pPlayer->idInfo_recorder.ui64Id  ==  110  )  {
			DWORD  dwTickCnt  =  GetTickCount(  );
			TCHAR  tBuf[128];
			//
			int  nNodes =  pPlayAudio->q2.qs[0].uiQNodes  +  pPlayAudio->q2.qs[1].uiQNodes;
			//
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "110. myInstream. %d. nLeft %d, bufLen %d, nNodes %d\n"  ),  dwTickCnt,  pPlayAudio->cache.nLeft,  bufLen,  nNodes  );
			OutputDebugString(  tBuf  );
		}
		#endif
#endif

	 //	
	 int  nQNodes_left = 0;
	 if (pProcInfo->cfg.b_useQ2_toPlayA) {
			nQNodes_left = getQ2Nodes(&pPlayAudio->q2);
		}
	 else {
			nQNodes_left = pPlayAudio->qBuf2->get_Q2Nodes();	
	 }
	 BOOL  bAdjust  =  FALSE;
	 
	 //  2017/06/21
	 DWORD		dwTickCnt  =  myGetTickCount( mynull );
	 int  iElapseInMs  =  dwTickCnt  -  pPlayAudio->lowLatency.dwTgt_start1;
	 int  nIntervalInMs_toAdjust  =  5000;
	 nIntervalInMs_toAdjust = 4000;	// 1000;
	 //
	 iElapseInMs  =  abs(  iElapseInMs  );
	 //
	 BOOL  bNeedReset  =  FALSE;
	 
	 //
	 int  unused_iElapseInMs_last_dangerousMql = 0;
	 

	 //			
	 if (pPlayAudio->lowLatency.mql > nQNodes_left) {
		 pPlayAudio->lowLatency.mql = nQNodes_left;
		 //
	 }
	 if (pPlayAudio->lowLatency.xql < nQNodes_left) {
		 pPlayAudio->lowLatency.xql = nQNodes_left;
	 }

	 //
	 int default_max_mql_ok = 4;	//  7
	 int default_min_mql_ok = 3;
	 int default_max_mql_ok_inMs = 150;
	 int default_min_mql_ok_inMs = 100;
	 //
	 int default_xql_ok_inMs = 2500; //  2000; 
	 //
	 int  max_mql_ok = default_max_mql_ok;// 7;
	 int  min_mql_ok = default_min_mql_ok;// 4;
	 //
	 int  xql_ok = 30;	//  30

	 //
#if 0
	 if (pPlayAudio->lowLatency.avg_pkt.nAvg_pkt_inMs) {
		 min_mql_ok = default_min_mql_ok_inMs / pPlayAudio->lowLatency.avg_pkt.nAvg_pkt_inMs + 1;
		 max_mql_ok = default_max_mql_ok_inMs / pPlayAudio->lowLatency.avg_pkt.nAvg_pkt_inMs + 1;
		 //
		 //xql_ok = default_xql_ok_inMs / pPlayAudio->lowLatency.avg_pkt.nAvg_pkt_inMs + 1;
		 //
		 int ii = 0;
	 }
#endif 

	 //
	 pPlayAudio->lowLatency.max_mql_ok = max_mql_ok;
	 pPlayAudio->lowLatency.min_mql_ok = min_mql_ok;
	 pPlayAudio->lowLatency.xql_ok = xql_ok;
	 	 
	 //
	 if (bDbg) {
		 if (0) {
			 _sntprintf(tBuf, mycountof(tBuf), _T("my_inStream: %I64u: %d: nql %d, mql %d, xql %d. mql_ok %d, xql_ok %d. nAvg_pktInMs %d"),
				 pPlayer->idInfo_recorder.ui64Id, pPlayer->audio.m_var.nTimes_my_inStream,
				 nQNodes_left, pPlayAudio->lowLatency.mql, pPlayAudio->lowLatency.xql,
				 pPlayAudio->lowLatency.max_mql_ok, pPlayAudio->lowLatency.xql_ok,
				 pPlayAudio->lowLatency.avg_pkt.nAvg_pkt_inMs);
			 showInfo_open(0, 0, 0, tBuf);
		 }
	 }

	 //
#if  0
	 if  (  iElapseInMs  >  nIntervalInMs_toAdjust  +  1000  )  {
		 bNeedReset  =  TRUE;
		 }
	 else
#endif 
	 if  (  iElapseInMs  >  nIntervalInMs_toAdjust  )
	 {
		 bNeedReset = true;

		 //
		 if (bDbg) {
			 if (10) {
				 //
				 int totalBytes;
				 totalBytes = nQNodes_left * 1152  + pPlayAudio->cache.nLeft;

				 //
				 _sntprintf(tBuf, mycountof(tBuf), _T("my_inStream: %I64u: %d: total %d. nql %d, mql %d, xql %d. mql_ok %d, xql_ok %d. nAvg_pktInMs %d"),
					 pPlayer->idInfo_recorder.ui64Id, pPlayer->audio.m_var.nTimes_my_inStream,
					 totalBytes,
					 nQNodes_left, pPlayAudio->lowLatency.mql, pPlayAudio->lowLatency.xql,
					 pPlayAudio->lowLatency.max_mql_ok, pPlayAudio->lowLatency.xql_ok,
					 pPlayAudio->lowLatency.avg_pkt.nAvg_pkt_inMs);
				 showInfo_open(0, 0, 0, tBuf);
			 }
		 }


		 //		 
		 if (pPlayAudio->lowLatency.mql > max_mql_ok) {
			 pPlayAudio->lowLatency.bNeedAdjust = TRUE;
		 }
		 //
		 if (pPlayAudio->lowLatency.xql > xql_ok) {
			 if (pPlayAudio->lowLatency.mql > max_mql_ok) {
				 pPlayAudio->lowLatency.bNeedAdjust = TRUE;
			 }
		 }

		 //
		 if (pPlayAudio->lowLatency.bNeedAdjust) {
			 if (pPlayAudio->lowLatency.mql <= min_mql_ok) {
				 pPlayAudio->lowLatency.bNeedAdjust = FALSE;
			 }
		 }
		 //
		 if (pPlayAudio->lowLatency.bNeedAdjust) {
			 if (dwTickCnt - pPlayAudio->lowLatency.dwTickCnt_last_adjust > 200) {
				 bAdjust = TRUE;
			 }
		 }

		 //
		 if (!pPlayAudio->lowLatency.bNeedAdjust) {
			 bNeedReset = TRUE;
		 }

		 //
		 if (bDbg) {
			 _sntprintf(tBuf, mycountof(tBuf), _T("bAdjust %d"), bAdjust);
			 showInfo_open(0, 0, 0, tBuf);
		 }

		 //
		 if (bAdjust) {
			 //
			 int  nSkipped = pPlayAudio->lowLatency.mql - min_mql_ok;
			 if (nSkipped > 0) {
				 //nSkipped  =  nSkipped  /  2;
				 //
				 //if  (  nSkipped  >  1  )  nSkipped  =  1;
				 nSkipped = 1;
				 //		
				 int  i;
				 for (i = 0; i < nSkipped; i++) {
					 bool bSkipped = false;

					 if (pProcInfo->cfg.b_useQ2_toPlayA) {
						 myPLAY_AUDIO_DATA  pkt;
						 unsigned  int  pktLen = sizeof(pkt);
						 if (!q2GetMsg(&pPlayAudio->q2, &pkt, &pktLen, _T("my_instream0"))) {
							 //
							 M_chk_pts(pPlayAudio, pkt);
							 //
							 clean_myPLAY_AUDIO_DATA(&pkt, _T("PlayAudio, bAdjust, to remove old data"));
							 //
							 bSkipped = true;
							 //
						 }
					 }
					 else {
						 int len = (int)(pPlayAudio->cache.uiBufSize - pPlayAudio->cache.nLeft);

						 HeadData_playA headData;
						 if (0 == pPlayAudio->qBuf2->q2GetMsg(&headData, (pPlayAudio->cache.pBuf + pPlayAudio->cache.nLeft), (uint*)&len, _T("my_inStream")))
						 {
							 bSkipped = true;
						 }
					 }
					 //
					 if (bSkipped)
					 {
						 _sntprintf(tBuf, mycountof(tBuf), _T("my_inStream: %I64u, bAdjust, to remove too old data, mql %d. max_mql_ok %d. nSkipped %d"), pPlayer->idInfo_recorder.ui64Id, pPlayAudio->lowLatency.mql, pPlayAudio->lowLatency.max_mql_ok, nSkipped);
						 showInfo_open0(0, 0, tBuf);
					 }
					 //
				 }
			 }
			 //
			 pPlayAudio->lowLatency.dwTickCnt_last_adjust = dwTickCnt;
		 }


	 }
	 
	 //
	 if  (  bNeedReset  )  {
		 pPlayAudio->lowLatency.dwTgt_start1  =  dwTickCnt;
		 //		
		 //
		 pPlayAudio->lowLatency.last_mql  =  pPlayAudio->lowLatency.mql;
		 pPlayAudio->lowLatency.last_xql  =  pPlayAudio->lowLatency.xql;
		 //		   
		 pPlayAudio->lowLatency.mql  =  nQNodes_left;		  
		 pPlayAudio->lowLatency.xql  =  nQNodes_left;
		 //
		 //  2017/10/13
		 memset(  &pPlayAudio->lowLatency.ptsInfo,  0,  sizeof(  pPlayAudio->lowLatency.ptsInfo  )  );
		 memset(  &pPlayAudio->lowLatency.avg_pkt,  0,  sizeof(  pPlayAudio->lowLatency.avg_pkt  )  );		 
		 //
		 if  (  pProcInfo->cfg.debugStatusInfo.ucbShowPlayAudioStatus  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "my_inStream: %I64u, need Reset. nIntervalInMs_toAdjust %dms"  ),  pPlayer->idInfo_recorder.ui64Id,  nIntervalInMs_toAdjust  );
		 	 showInfo_open0(  0,  0,  tBuf  );
		 }
	 }




	 //  2017/06/21. to remove too old data
#if 0
	 int  xql_ok  =  30;	//  15;	//  6;
	 //
	 if  (  pPlayAudio->lowLatency.xql_ok  >  xql_ok  )  {
		 xql_ok  =  pPlayAudio->lowLatency.xql_ok;
	 }
	 //
	 while  (  getQ2Nodes(  &pPlayer->audio.q2  )  >  xql_ok  )  {
		    myPLAY_AUDIO_DATA  pkt;
			unsigned  int  pktLen  =  sizeof(  pkt  );		 		
			if  (  q2GetMsg(  &pPlayAudio->q2,  &pkt,  &pktLen,  _T(  "my_inStream 1"  )))  break;
			//
			M_chk_pts(  pPlayAudio,  pkt  );
			//
			clean_myPLAY_AUDIO_DATA(  &pkt,  _T(  "PlayAudio,to remove old data"  )  );
			//
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "my_inStream: %I64u, to remove too old data, xql_ok %d, qNodes %d"  ),  pPlayer->idInfo_recorder.ui64Id,  xql_ok,  getQ2Nodes(  &pPlayer->audio.q2  )  );  
			showInfo_open0(  0,  0,  tBuf  );
			//
			continue;		 
	 }
#endif

	 //
#ifdef  __DEBUG__
		#if  0
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "my_inStream: n_left %d"  ),  nQNodes_left  );
				showInfo_open0(  0,  0,  tBuf  );
		#endif
#endif


	 //
	 while  (  pPlayAudio->cache.nLeft  <  bufLen  )  {		 
			  //
			  unsigned  int  uiPts  =  0;		//  2017/10/13
			  unsigned  int  uiDataLen  =  0;	//  2017/10/13
			  
												//
			  if (pProcInfo->cfg.b_useQ2_toPlayA) {
				  myPLAY_AUDIO_DATA  pkt;

				  unsigned  int  pktLen = sizeof(pkt);
				  if (q2GetMsg(&pPlayAudio->q2, &pkt, &pktLen, _T("my_inStream 3")))  break;
				  if (!pkt.memory.m_pBuf)  break;
				  //
				  uiPts = pkt.head.uiPts;			//  2017/10/13
				  uiDataLen = pkt.uiSize_dec;		//  2017/10/13
				  M_chk_pts(pPlayAudio, pkt);	//  2017/10/13
				  //
				  int  len = pPlayAudio->cache.uiBufSize - pPlayAudio->cache.nLeft;
				  len = min(len, pkt.uiSize_dec);
				  memcpy(pPlayAudio->cache.pBuf + pPlayAudio->cache.nLeft, pkt.memory.m_pBuf, len);
				  uiDataLen = len;
				  clean_myPLAY_AUDIO_DATA(&pkt, _T("PlayAudio"));

				  //
#ifdef  __DEBUG__
				  if (bDbg) {
					  if (0) {
						  _sntprintf(tBuf, mycountof(tBuf), _T("my_inStream: %I64u: pkt.uiSize_dec %d, dataLen %d"), pPlayer->idInfo_recorder.ui64Id, pkt.uiSize_dec, uiDataLen);
						  showInfo_open(0, 0, 0, tBuf);
					  }
					  if (uiDataLen == 0) {
						  _sntprintf(tBuf, mycountof(tBuf), _T("my_inStream: %I64u err: pkt.uiSize_dec %d, dataLen %d"), pPlayer->idInfo_recorder.ui64Id, pkt.uiSize_dec, uiDataLen);
						  showInfo_open(0, 0, 0, tBuf );
					  }
					  if (pkt.uiSize_dec != uiDataLen) {
						  showInfo_open(0, 0, 0, _T("my_inStream: err: size_dec != dataLen"));
					  }
				  }
#endif 
			  }
			  else {
				  HeadData_playA headData;
				  int len = (int)(pPlayAudio->cache.uiBufSize - pPlayAudio->cache.nLeft);
				  if (0 != pPlayAudio->qBuf2->q2GetMsg(& headData, (pPlayAudio->cache.pBuf + pPlayAudio->cache.nLeft), (uint*)&len,_T("my_inStream"))) break;
				  //
				  if (len != headData.uiSize_dec)
				  {
					  int ii = 0;
				  }
				  //
				  uiPts = headData.uiPts;
				  uiDataLen = headData.uiSize_dec;

			  }
			  pPlayAudio->cache.nLeft  +=  uiDataLen;
			  //
			  pPlayAudio->lowLatency.avg_pkt.nBytes_ptks  +=  uiDataLen;
			  pPlayAudio->lowLatency.avg_pkt.n_pkts  ++  ;
			  if  (  pPlayAudio->ah.wfx.nAvgBytesPerSec  )  {
				  pPlayAudio->lowLatency.avg_pkt.nAvg_pkt_inMs  =  pPlayAudio->lowLatency.avg_pkt.nBytes_ptks  *  1000.  /  pPlayAudio->lowLatency.avg_pkt.n_pkts  /  pPlayAudio->ah.wfx.nAvgBytesPerSec;
			  }
			  //
			  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowPlayAudioStatus  )  {
					  //  2017/10/13
					  //
					  int  dataInMs  =  0;
					  if  (  pPlayAudio->ah.wfx.nAvgBytesPerSec  )  {
						  dataInMs  =  uiDataLen  *  1000  /  pPlayAudio->ah.wfx.nAvgBytesPerSec;
					  }
					  //
					  //_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "my_inStream: %I64u: uiPts %d, uiDataLen %d. dataInMs %dms. nAvg_pkt_inMs %dms. nQNodes_left %d. mql %d"  ),  pPlayer->idInfo_recorder.ui64Id,  uiPts, uiDataLen,  dataInMs,  pPlayAudio->lowLatency.avg_pkt.nAvg_pkt_inMs,  nQNodes_left,  pPlayAudio->lowLatency.mql  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "my_inStream: %I64u: nErr_pts %d, elapseI_last_dangerMql %dms, uiPts %d, dataInMs %dms. mql %d, xql %d, nQNodes_left %d. "  ),  pPlayer->idInfo_recorder.ui64Id,  pPlayer->audio.lowLatency.ptsInfo.nErr_ptsMissed,  unused_iElapseInMs_last_dangerousMql,  uiPts, dataInMs,  pPlayAudio->lowLatency.mql,  pPlayAudio->lowLatency.xql,  getQ2Nodes(  &pPlayer->audio.q2  )  );
					  showInfo_open0(  0,  0,  tBuf  );
			  }
			  //
			  pPlayAudio->cache.dwTickCnt_lastAudioData3  =  myGetTickCount( mynull );
		  
	 }

	 //
	 if (bDbg) {
		 if (pPlayAudio->cache.nLeft == 0) {
			 int ii = 0;
			 _sntprintf(tBuf, mycountof(tBuf), _T("my_instream: %I64u, err. nleft is 0"),  pPlayer->idInfo_recorder.ui64Id);
			 showInfo_open(0, 0, 0, tBuf);
		 }
	 }

	 //
	 if  (  pPlayAudio->cache.nLeft  )  {
		 //
		 if (pPlayAudio->cache.nLeft < bufLen) {
			 //
			 int  n = 0;
			 if (pProcInfo->cfg.b_useQ2_toPlayA) {
				 n = getQ2Nodes(&pPlayer->audio.q2);
			 }
			 else {
				 n = pPlayer->audio.qBuf2->get_Q2Nodes();
			 }
			 //
			 if (!pQyMc->appParams.bMcu)
			 {			
				 _sntprintf(tBuf, mycountof(tBuf), _T("my_inStream: %I64u: nLeft %d < bufLen %d, fillSilence. nodes %d"), pPlayer->idInfo_recorder.ui64Id, pPlayAudio->cache.nLeft, bufLen, n);
				 showInfo_open0(0, 0, tBuf);
			 }
			 //
			 fillSilence(wBits, buf, bufLen);
			 nRead = bufLen;  goto  errLabel;
		 }
		 //
#ifdef  __DEBUG__
#if  0
		 int  n = 0;
		 if (pProcInfo->cfg.b_useQ2_toPlayA) {
			 n = getQ2Nodes(&pPlayer->audio.q2);
		 }
		 else {
			 n = pPlayer->audio.qBuf2->get_Q2Nodes();
		 }
		 _sntprintf(tBuf, mycountof(tBuf), _T("my_inStream: %I64u %d: nodes %d. mql %d"), pPlayer->idInfo_recorder.ui64Id, pPlayer->uiTranNo_player, n, pPlayer->audio.lowLatency.mql);
		 showInfo_open0(0, 0, tBuf);
#endif
#endif
		 //
		 int  len  =  min(  bufLen,  pPlayAudio->cache.nLeft  );
		 memcpy(  buf,  pPlayAudio->cache.pLeft,  len  );
		 //
		 QY_MC* pQyMc = pProcInfo->pQyMc;// QY_GET_GBUF();
		 if  (  pQyMc->appParams.bInSilence  )  {
			 //int  wBits  =  16;
			 FillMemory(  buf,  len,  ( wBits == 8 ) ? 128 : 0 );
		 }
		 //
		 pPlayAudio->cache.pLeft  +=  len;
		 pPlayAudio->cache.nLeft  -=  len;
		 nRead  =  len;  goto  errLabel;
	 }
#endif

	 //
#if  0  //  单独的音频数据没收到，并不会退出.
	 if  (  dwTickCnt  -  pPlayAudio->cache.dwTickCnt_lastAudioData3  >  (  DWORD  )pProcInfo->cfg.usTimeoutInMs_player_a  )  {
		 //
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u, %d,%d: no data arrives too long, need stop running"  ),  pPlayer->idInfo_recorder.ui64Id,  pPlayAudio->uiTranNo,  pPlayer->video.uiTranNo  );

		 showInfo_open0(  0,  _T(  "my_inStream"  ),  tBuf  );
		 
		 //  2018/06/16
		 pPlayAudio->bNeedStop_webRtc_my_inStream  =  TRUE;
		 pProcInfo->ctrl.bNeedChkPlayers  =  TRUE;

		 //
		 nRead  =  0;  goto  errLabel;
	 }
#endif 
			
	 //
	 //int  wBits  =  16;
	 FillMemory(  buf,  bufLen,  ( wBits == 8 ) ? 128 : 0 );
	 nRead  =  bufLen;

	 //  2017/10/14
	 if  (  1 //pProcInfo->cfg.debugStatusInfo.ucbShowPlayAudioStatus  
		 )  
	 {
		 if (!pQyMc->appParams.bMcu)
		 {
			 bool  bPrint;  bPrint = false;

			 if (pProcInfo->cfg.debugStatusInfo.bDbgDetail_playA || bDbg) bPrint = true;
			 
			 //
			 if  (  bPrint)  {
				 _sntprintf(tBuf, mycountof(tBuf), _T("my_inStream: %I64u, fill silence data because no audio data"), pPlayer->idInfo_recorder.ui64Id);
				 showInfo_open(0, 0, 0,  tBuf);
#ifdef  __DEBUG__				 
				 traceLog((TCHAR*)_T("my_inStream: %s"), tBuf);				 
#endif

			 }
		 }
	 }

	 //
errLabel:

	 if  (  !nRead  )  {
		 int  ii  =  1;
	 }

	 return  nRead;
}


//
int  my_inStream1(void* p0, void* p1, void* p2)
{
	int  nRead = 0;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	QY_PLAYER* pPlayer = (QY_PLAYER*)p0;
	PLAY_AUDIO_procInfo* pPlayAudio = &pPlayer->audio;
	char* buf = (char*)p1;
	int  bufLen = (int)p2;

	//
	TCHAR  tBuf[128];
	int  wBits = 16;

	//
	char pcmBuf[48000 * 2];
	int pcmLen = 0;



	//
#if  10
	 //

	//
#ifdef  __DEBUG__
#if  0
	if (pPlayer->idInfo_recorder.ui64Id == 110) {
		DWORD  dwTickCnt = GetTickCount();
		TCHAR  tBuf[128];
		//
		int  nNodes = pPlayAudio->q2.qs[0].uiQNodes + pPlayAudio->q2.qs[1].uiQNodes;
		//
		_sntprintf(tBuf, mycountof(tBuf), _T("110. myInstream. %d. nLeft %d, bufLen %d, nNodes %d\n"), dwTickCnt, pPlayAudio->cache.nLeft, bufLen, nNodes);
		OutputDebugString(tBuf);
	}
#endif
#endif

	//
	int  nQNodes_left = 0;
	if (pProcInfo->cfg.b_useQ2_toPlayA) {
		nQNodes_left = getQ2Nodes(&pPlayAudio->q2);
	}
	else {
		nQNodes_left = pPlayAudio->qBuf2->get_Q2Nodes();
	}
	BOOL  bAdjust = FALSE;

	//  2017/06/21
	DWORD		dwTickCnt = GetTickCount();
	int  iElapseInMs = dwTickCnt - pPlayAudio->lowLatency.dwTgt_start1;
	int  nIntervalInMs_toAdjust = 5000;
	//nIntervalInMs_toAdjust  =  10000;
	//
	iElapseInMs = abs(iElapseInMs);
	//
	BOOL  bNeedReset = FALSE;

	//
	int  dangerous_mql_ok = 3;
	//
	if (pPlayAudio->lowLatency.avg_pkt.nAvg_pkt_inMs) {
		int  dangerous_mql_ok_inMs = 100;
		//
		dangerous_mql_ok = dangerous_mql_ok_inMs / pPlayAudio->lowLatency.avg_pkt.nAvg_pkt_inMs + 1;
	}
	int  iElapseInMs_last_dangerousMql = 0;
	if (pPlayAudio->lowLatency.dwTickCnt_last_dangerousMql) {
		iElapseInMs_last_dangerousMql = dwTickCnt - pPlayAudio->lowLatency.dwTickCnt_last_dangerousMql;
		if (iElapseInMs_last_dangerousMql < 20000)
		{
			//
			nIntervalInMs_toAdjust = 20000;
		}
	}

	//
	if (iElapseInMs > nIntervalInMs_toAdjust + 1000) {
		bNeedReset = TRUE;
	}
	else {
		//
		int default_max_mql_ok = 4;
		int default_min_mql_ok = 3;
		int default_max_mql_ok_inMs = 150;
		int default_min_mql_ok_inMs = 100;
		int default_xql_ok_inMs = 2500; //  2000;

		//
#if 0
		default_max_mql_ok = 7;
		default_min_mql_ok = 4;
		default_max_mql_ok_inMs = 700;
		default_min_mql_ok_inMs = 400;
#endif

		//			
		if (pPlayAudio->lowLatency.mql > nQNodes_left) {
			pPlayAudio->lowLatency.mql = nQNodes_left;
			//
#ifdef  __DEBUG__
#if  0
			if (pProcInfo->cfg.debugStatusInfo.ucbShowPlayAudioStatus) {
				_sntprintf(tBuf, mycountof(tBuf), _T("mql set to %d"), pPlayAudio->lowLatency.mql);
				showInfo_open0(0, 0, tBuf);
			}
#endif
#endif
		}
		if (pPlayAudio->lowLatency.xql < nQNodes_left)  pPlayAudio->lowLatency.xql = nQNodes_left;
		//
		if (nQNodes_left <= dangerous_mql_ok) {
			pPlayAudio->lowLatency.last_dangerousMql = nQNodes_left;
			pPlayAudio->lowLatency.dwTickCnt_last_dangerousMql = dwTickCnt;
		}

		//			
		if (iElapseInMs > nIntervalInMs_toAdjust) {
			int  max_mql_ok = default_max_mql_ok;// 7;
			int  min_mql_ok = default_min_mql_ok;// 4;
			//
			if (pPlayAudio->lowLatency.avg_pkt.nAvg_pkt_inMs) {
				int  max_mql_ok_inMs = default_max_mql_ok_inMs;// 700;
				int  min_mql_ok_inMs = default_min_mql_ok_inMs;// 400;
				int  dangerous_mql_ok_inMs = 100;
				int  xql_ok_inMs = 2500;	//  2000;
				//
				int  diff_xql_mql = pPlayAudio->lowLatency.xql - pPlayAudio->lowLatency.mql;
				//
				if (pPlayAudio->lowLatency.mql > dangerous_mql_ok
					&& !pPlayAudio->lowLatency.ptsInfo.nErr_ptsMissed)
				{
					max_mql_ok_inMs = 300;
					min_mql_ok_inMs = 200;
				}
				//
				int  tmp_max_mql_ok = max_mql_ok_inMs / pPlayAudio->lowLatency.avg_pkt.nAvg_pkt_inMs;
				int  tmp_min_mql_ok = min_mql_ok_inMs / pPlayAudio->lowLatency.avg_pkt.nAvg_pkt_inMs;
				pPlayAudio->lowLatency.xql_ok = xql_ok_inMs / pPlayAudio->lowLatency.avg_pkt.nAvg_pkt_inMs;
				//
				if (tmp_max_mql_ok > max_mql_ok)  max_mql_ok = tmp_max_mql_ok;
				if (tmp_min_mql_ok > min_mql_ok)  min_mql_ok = tmp_min_mql_ok;
				//
				pPlayAudio->lowLatency.max_mql_ok = max_mql_ok;
				pPlayAudio->lowLatency.min_mql_ok = min_mql_ok;
				//
				if (pProcInfo->cfg.debugStatusInfo.ucbShowPlayAudioStatus) {	//  2017/10/13
					_sntprintf(tBuf, mycountof(tBuf), _T("my_inStream: %I64u, nErr_pts %d, max_mql_ok %d, min_mql_ok %d. mql %d. diff_xql_mql %d"), pPlayer->idInfo_recorder.ui64Id,
						pPlayAudio->lowLatency.ptsInfo.nErr_ptsMissed, max_mql_ok, min_mql_ok, pPlayAudio->lowLatency.mql, diff_xql_mql);
					//tmp_max_mql_ok %d, tmp_min_mql_ok %d, tmp_xql_ok %d. tmp_max_mql_ok,  tmp_min_mql_ok,  pPlayAudio->lowLatency.xql_ok,  
					showInfo_open0(0, 0, tBuf);
				}
			}
			//
			if (pPlayAudio->lowLatency.mql > max_mql_ok) {
				pPlayAudio->lowLatency.bNeedAdjust = TRUE;
			}
			//
			if (pPlayAudio->lowLatency.bNeedAdjust) {
				if (pPlayAudio->lowLatency.mql <= min_mql_ok) {
					pPlayAudio->lowLatency.bNeedAdjust = FALSE;
				}
			}
			//
			if (pPlayAudio->lowLatency.bNeedAdjust) {
				if (dwTickCnt - pPlayAudio->lowLatency.dwTickCnt_last_adjust > 200) {
					bAdjust = TRUE;
				}
			}

			//
			if (!pPlayAudio->lowLatency.bNeedAdjust) {
				bNeedReset = TRUE;
			}


			//
			if (bAdjust) {
				//
				int  nSkipped = pPlayAudio->lowLatency.mql - min_mql_ok;
				if (nSkipped > 0) {
					//nSkipped  =  nSkipped  /  2;
					//
					//if  (  nSkipped  >  1  )  nSkipped  =  1;
					nSkipped = 1;
					//		
					int  i;
					for (i = 0; i < nSkipped; i++) {
						bool bSkipped = false;

						if (pProcInfo->cfg.b_useQ2_toPlayA) {
							myPLAY_AUDIO_DATA  pkt;
							unsigned  int  pktLen = sizeof(pkt);
							if (!q2GetMsg(&pPlayAudio->q2, &pkt, &pktLen, _T("my_instream0"))) {
								//
								M_chk_pts(pPlayAudio, pkt);
								//
								clean_myPLAY_AUDIO_DATA(&pkt, _T("PlayAudio, bAdjust, to remove old data"));
								//
								bSkipped = true;
								//
							}
						}
						else {
							int len = (int)(pPlayAudio->cache.uiBufSize - pPlayAudio->cache.nLeft);

							HeadData_playA headData;
							if (0 == pPlayAudio->qBuf2->q2GetMsg(&headData, (pPlayAudio->cache.pBuf + pPlayAudio->cache.nLeft), (uint*)&len, _T("my_inStream")))
							{
								bSkipped = true;
							}
						}
						//
						if (bSkipped)
						{
							_sntprintf(tBuf, mycountof(tBuf), _T("my_inStream: %I64u, bAdjust, to remove too old data, mql %d. max_mql_ok %d. nSkipped %d"), pPlayer->idInfo_recorder.ui64Id, pPlayAudio->lowLatency.mql, pPlayAudio->lowLatency.max_mql_ok, nSkipped);
							showInfo_open0(0, 0, tBuf);
						}
						//
					}
				}
				//
				pPlayAudio->lowLatency.dwTickCnt_last_adjust = dwTickCnt;
			}

		}
	}

	//
	if (bNeedReset) {
		pPlayAudio->lowLatency.dwTgt_start1 = dwTickCnt;
		//		
		//
		pPlayAudio->lowLatency.last_mql = pPlayAudio->lowLatency.mql;
		pPlayAudio->lowLatency.last_xql = pPlayAudio->lowLatency.xql;
		//		   
		pPlayAudio->lowLatency.mql = nQNodes_left;
		pPlayAudio->lowLatency.xql = nQNodes_left;
		//
		//  2017/10/13
		memset(&pPlayAudio->lowLatency.ptsInfo, 0, sizeof(pPlayAudio->lowLatency.ptsInfo));
		memset(&pPlayAudio->lowLatency.avg_pkt, 0, sizeof(pPlayAudio->lowLatency.avg_pkt));
		//
		if (pProcInfo->cfg.debugStatusInfo.ucbShowPlayAudioStatus) {
			_sntprintf(tBuf, mycountof(tBuf), _T("my_inStream: %I64u, need Reset. nIntervalInMs_toAdjust %dms"), pPlayer->idInfo_recorder.ui64Id, nIntervalInMs_toAdjust);
			showInfo_open0(0, 0, tBuf);
		}
	}




	//  2017/06/21. to remove too old data
#if 10
	int  xql_ok = 30;	//  15;	//  6;
	//
	if (pPlayAudio->lowLatency.xql_ok > xql_ok) {
		xql_ok = pPlayAudio->lowLatency.xql_ok;
	}
	//
	while (getQ2Nodes(&pPlayer->audio.q2) > xql_ok) {
		myPLAY_AUDIO_DATA  pkt;
		unsigned  int  pktLen = sizeof(pkt);
		if (q2GetMsg(&pPlayAudio->q2, &pkt, &pktLen, _T("my_inStream 1")))  break;
		//
		M_chk_pts(pPlayAudio, pkt);
		//
		clean_myPLAY_AUDIO_DATA(&pkt, _T("PlayAudio,to remove old data"));
		//
		_sntprintf(tBuf, mycountof(tBuf), _T("my_inStream: %I64u, to remove too old data, xql_ok %d, qNodes %d"), pPlayer->idInfo_recorder.ui64Id, xql_ok, getQ2Nodes(&pPlayer->audio.q2));
		showInfo_open0(0, 0, tBuf);
		//
		continue;
	}
#endif

	//


	//
	//while (pPlayAudio->cache.nLeft < bufLen) 
	for (;;)
	{
		//
		unsigned  int  uiPts = 0;		//  2017/10/13
		unsigned  int  uiDataLen = 0;	//  2017/10/13

										  //
		if (pProcInfo->cfg.b_useQ2_toPlayA) {
			myPLAY_AUDIO_DATA  pkt;

			unsigned  int  pktLen = sizeof(pkt);
			if (q2GetMsg(&pPlayAudio->q2, &pkt, &pktLen, _T("my_inStream 3")))  break;
			if (!pkt.memory.m_pBuf)  break;
			//
			uiPts = pkt.head.uiPts;			//  2017/10/13
			uiDataLen = pkt.uiSize_dec;		//  2017/10/13
			M_chk_pts(pPlayAudio, pkt);	//  2017/10/13
			//
			int  len = sizeof(pcmBuf);// pPlayAudio->cache.uiBufSize - pPlayAudio->cache.nLeft;
			//len = min(len, pkt.uiSize_dec);
			if (len < pkt.uiSize_dec) goto  errLabel;
			len = pkt.uiSize_dec;
			//memcpy(pPlayAudio->cache.pBuf + pPlayAudio->cache.nLeft, pkt.memory.m_pBuf, len);
			memcpy(pcmBuf, pkt.memory.m_pBuf, len);
			uiDataLen = len;
			clean_myPLAY_AUDIO_DATA(&pkt, _T("PlayAudio"));
		}
		else {
			HeadData_playA headData;
			int len = (int)(pPlayAudio->cache.uiBufSize - pPlayAudio->cache.nLeft);
			if (0 != pPlayAudio->qBuf2->q2GetMsg(&headData, (pPlayAudio->cache.pBuf + pPlayAudio->cache.nLeft), (uint*)&len, _T("my_inStream"))) break;
			//
			if (len != headData.uiSize_dec)
			{
				int ii = 0;
			}
			//
			uiPts = headData.uiPts;
			uiDataLen = headData.uiSize_dec;

		}
		pPlayAudio->cache.nLeft += uiDataLen;
		//
		pPlayAudio->lowLatency.avg_pkt.nBytes_ptks += uiDataLen;
		pPlayAudio->lowLatency.avg_pkt.n_pkts++;
		if (pPlayAudio->ah.wfx.nAvgBytesPerSec) {
			pPlayAudio->lowLatency.avg_pkt.nAvg_pkt_inMs = pPlayAudio->lowLatency.avg_pkt.nBytes_ptks * 1000. / pPlayAudio->lowLatency.avg_pkt.n_pkts / pPlayAudio->ah.wfx.nAvgBytesPerSec;
		}
		//
		if (pProcInfo->cfg.debugStatusInfo.ucbShowPlayAudioStatus) {
			//  2017/10/13
			//
			int  dataInMs = 0;
			if (pPlayAudio->ah.wfx.nAvgBytesPerSec) {
				dataInMs = uiDataLen * 1000 / pPlayAudio->ah.wfx.nAvgBytesPerSec;
			}
			//
			//_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "my_inStream: %I64u: uiPts %d, uiDataLen %d. dataInMs %dms. nAvg_pkt_inMs %dms. nQNodes_left %d. mql %d"  ),  pPlayer->idInfo_recorder.ui64Id,  uiPts, uiDataLen,  dataInMs,  pPlayAudio->lowLatency.avg_pkt.nAvg_pkt_inMs,  nQNodes_left,  pPlayAudio->lowLatency.mql  );
			_sntprintf(tBuf, mycountof(tBuf), _T("my_inStream: %I64u: nErr_pts %d, elapseI_last_dangerMql %dms, uiPts %d, dataInMs %dms. mql %d, xql %d, nQNodes_left %d. "), pPlayer->idInfo_recorder.ui64Id, pPlayer->audio.lowLatency.ptsInfo.nErr_ptsMissed, iElapseInMs_last_dangerousMql, uiPts, dataInMs, pPlayAudio->lowLatency.mql, pPlayAudio->lowLatency.xql, getQ2Nodes(&pPlayer->audio.q2));
			showInfo_open0(0, 0, tBuf);
		}
		//.
		pPlayAudio->cache.dwTickCnt_lastAudioData3 = myGetTickCount(mynull);

		//
		if (uiDataLen > bufLen)  goto  errLabel;
		memcpy(buf, pcmBuf, uiDataLen);
		nRead = uiDataLen;
		//
		break;
	}

	//

#endif

	//


	//
errLabel:

	if (!nRead) {
		int  ii = 1;
	}

	return  nRead;
}


//
//
int my_inStream4_toMix(void* p0, void* p1, void* p2, void* p3)
{
	int  nRead = 0;
	int  iErr = -1;
	CCtxQmc* pProcInfo = (CCtxQmc*)p0;
	int index_source = (int)p1;
	char* buf = (char*)p2;
	int size = (int)(long long)p3;

	//
	AEC_layout* pAecLayout = &pProcInfo->av.aecInfo.aecLayout;
	int wBits = 16;

	//
	if (index_source < 0 || index_source >= pAecLayout->usCntLimit_activeMems_from) {
		showInfo_open0(0, 0, _T("my_inStream4_toMix failed, index_source err"));
		goto  errLabel;
	}
	AEC_player_cfg* pMem; pMem = &pAecLayout->mems[index_source];
	if (!pMem->idInfo.ui64Id) goto  errLabel;
	if (!pMem->tn_a) {
		goto  errLabel;
	}
	if (!pMem->playerId.uiTranNo_player)goto  errLabel;
	QY_PLAYER* pPlayer;
	pPlayer = getPlayerByIndex(pProcInfo, pMem->playerId.index_player);
	if (!pPlayer)goto  errLabel;
	if (pPlayer->playerId.uiTranNo_player != pMem->playerId.uiTranNo_player)goto  errLabel;

	//
	
	//
	int n;
	n = my_inStream1(pPlayer, buf, (void*)size);
	nRead = n;// size;
	//
#ifdef  __DEBUG__
	if (pMem->fp_debug) {
		//fwrite(buf, size, 1, pMem->fp_debug);
	}
#endif


	//
	iErr = 0;

errLabel:

	if (iErr) {
#if  0
		fillSilence(wBits, buf, size);
		nRead = size;
#endif
		//
		nRead = 0;
	}

	//
	return  nRead;
}



//
int  startPlayAudio_webRtc(  void  *  pPlayerParam  )
{
	int  iErr  =  -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	//
	 QY_PLAYER				*	pPlayer  =  (  QY_PLAYER  *  )pPlayerParam;
	 PLAY_AUDIO_procInfo	*	pPlayAudio  =  &pPlayer->audio;

	 //
	 pPlayAudio->cache.uiBufSize  =  max(  (  CONST_bufSize_transferAudioData  +  256  )  *  2,  pPlayAudio->ah.wfx.nAvgBytesPerSec  *  2  );
	 pPlayAudio->cache.pBuf  =  (  char  *  )malloc(  pPlayAudio->cache.uiBufSize  );
	 if  (  !pPlayAudio->cache.uiBufSize  ||  !pPlayAudio->cache.pBuf  )  goto  errLabel;

	 //
	 pPlayAudio->cache.pLeft  =  pPlayAudio->cache.pBuf;
	 pPlayAudio->cache.nLeft  =  0;
	 pPlayAudio->cache.dwTickCnt_lastAudioData3  =  myGetTickCount( mynull  );

	 //
 	 pPlayAudio->dwTickCnt_start  =  M_GetTickCount_audio(  tickObj  );		//  2010/05/04
	 pPlayer->uiSampleTimeInMs_start  =  0;
	 //
	 memset(  &pPlayAudio->m_var,  0,  sizeof(  pPlayAudio->m_var  )  );

	 //  2018/06/16
	 pPlayAudio->bNeedStop_webRtc_my_inStream  =  FALSE;

	 //
	 int maxDataBufLen; maxDataBufLen = 48000 * 2 * 3 / 2;
	 if (pPlayer->audio.qBuf2->alloc(maxDataBufLen) != 0) goto errLabel;

	 //
	 pPlayAudio->bRunning  =  TRUE;

	 //
	 if (!pQyMc->b__USE_webrtc1__) {
		 //
		 if (voe_play_init(pPlayer, my_inStream, &pPlayAudio->webRtc.pVoePlay)) {
			 goto  errLabel;
		 }
	 }


	iErr  =  0;
errLabel:
	return  iErr;
}


//
int  stopPlayAudio_webRtc(  void  *  pPlayerParam  )
{
	int  iErr  =  -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	//
	 QY_PLAYER				*	pPlayer  =  (  QY_PLAYER  *  )pPlayerParam;
	 PLAY_AUDIO_procInfo	*	pPlayAudio  =  &pPlayer->audio;


	 //
	 if (!pQyMc->b__USE_webrtc1__) {
		 //
		 voe_play_exit(&pPlayAudio->webRtc.pVoePlay);
	 }

	 //
	 pPlayAudio->bRunning  =  FALSE;
	 
	 //
	 pPlayer->audio.qBuf2->dofree();

	 //
	 MACRO_safeFree(  pPlayAudio->cache.pBuf  );


	iErr  =  0;
errLabel:
	return  iErr;


}


