



#include	"stdafx.h"
#include	<math.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"tmpCeLib.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyOpenShellCommon.h"
#include	"funcsForIsCliHelp.h"




 

 //
  //BOOL  isSlaveOfMaster(  int  iIndex_sharedObj_slave,  QY_SHARED_OBJ  *  pSharedObj_slave,  int  iIndex_sharedObj_master,  QY_SHARED_OBJ  *  pSharedObj_master  );

 //  2014/09/23
 int  chkSharedObjSlave(  MIS_MSG_procVideo_qmc  *  pMsg,  BOOL  *  pbRedirected  )
 {
	 int				iErr			=	-1;
	 MC_VAR_isCli  *	pProcInfo		=  QY_GET_procInfo_isCli(  );
	 BOOL				bRedirected		=  FALSE;

	 CQySyncCnt			syncCnt;
	 CQySyncCnt			syncCnt_slave;

	 if  (  !pMsg->uiCapType  )  return  -1;
	 
	 //
	 CAP_procInfo_bmpCommon  *  pCapBmp  =  (  CAP_procInfo_bmpCommon  *  )getCapBmpBySth(  pProcInfo,  pMsg->iIndex_capProcInfo,  pMsg->uiCapType  );
	 if  (  !pCapBmp  )  goto  errLabel;
	 
	 //
	 int	iIndex_sharedObj_master; iIndex_sharedObj_master = pCapBmp->iIndex_sharedObj;
	 QY_sharedObj_sync* pSharedObjInfo_master; pSharedObjInfo_master = getSharedObjSyncByIndex(pProcInfo, iIndex_sharedObj_master);
	 if  (  !pSharedObjInfo_master  )  goto  errLabel;

	 if  (  syncMtCnt_rLock(  &pSharedObjInfo_master->syncMtCnt,  &syncCnt,  _T(  "chkSharedObjSlave"  )  )  )  {
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "chkSharedObjSlave failed, master, syncMtCnt_rLock failed"  )  );
		 #endif
		 goto  errLabel;
	 }
	 	 
	 //
	 QY_SHARED_OBJ* pSharedObj_master; pSharedObj_master = &pSharedObjInfo_master->sharedObj;
	 if  (  !pSharedObj_master->bUsed  )  goto  errLabel;

	 //
	 SHARED_OBJ_USR* pSharedObjUsr; pSharedObjUsr = getSharedObjUsr(pSharedObj_master, pSharedObj_master->iIndex_curUsr);
	 if  (  !pSharedObjUsr  )  {
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "chkSharedObjSlave failed, master, sharedObjUsr is null"  )  );
		 #endif
		 goto  errLabel;
	 }
	 if  (  pSharedObjUsr->iTaskId  !=  pMsg->iTaskId  )  {
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "chkSharedObjSlave: iTask unmatched"  )  );
		 #endif
		 goto  errLabel;
	 }
	 	
	 //
	 if  (  pSharedObj_master->bSlave  ||  !pSharedObj_master->master.slaveKey.iIndex_sharedObj  )  goto  errLabel;
	 	
	 //
	 int		iIndex_sharedObj_slave; iIndex_sharedObj_slave = pSharedObj_master->master.slaveKey.iIndex_sharedObj;
	 //
	 QY_sharedObj_sync* pSharedObjInfo_slave; pSharedObjInfo_slave = getSharedObjSyncByIndex(pProcInfo, iIndex_sharedObj_slave);
	 if  (  !pSharedObjInfo_slave  )  goto  errLabel;

	 //
	 if  (  syncMtCnt_rLock(  &pSharedObjInfo_slave->syncMtCnt,  &syncCnt_slave,  _T(  "chkSharedObjSlave 2"  )  )  )  goto  errLabel;

	 QY_SHARED_OBJ* pSharedObj_slave; pSharedObj_slave = &pSharedObjInfo_slave->sharedObj;
	 if  (  !pSharedObj_slave->bUsed  )  goto  errLabel;


	 //	 	
	 if  (  !isSlaveOfMaster(  iIndex_sharedObj_slave,  pSharedObj_slave,  iIndex_sharedObj_master,  pSharedObj_master  )  )  {
		   goto  errLabel;
	 }
	 
	 //
	 CAP_procInfo_bmpCommon* pCapBmp_slave; pCapBmp_slave = (CAP_procInfo_bmpCommon*)getCapBmpBySth(pProcInfo, pSharedObj_slave->iIndex_capBmp, 0);
	 if  (  !pCapBmp_slave  )  goto  errLabel;
	 
	 //
	 if  (  !pCapBmp_slave->vppThread.bQInited  )  goto  errLabel;

	 //
	 int  len; len = sizeof(pMsg->pkt);
	 if  (  q2PostMsgAndTrigger(  &pMsg->pkt,  len,  &pCapBmp_slave->vppThread.q2,  _T(  "chkSharedObjSlave"  )))  goto  errLabel;

	 //
	 bRedirected  =  TRUE;

	 //
	 iErr  =  0;
errLabel:
	 if  (  pbRedirected  )  *pbRedirected  =  bRedirected;
	 return  iErr;
 }







#define		CONST_nGetMsgs_procVideo	30	//  2015/06/20. //  20

 //  2011/12/10
 int  doWnd_guiMsgArrive(  void  *  pProcInfoParam,  int  index_player,  HWND  hWnd,  BOOL  bForce_displayAllFrames,  MIS_MSGU  *  pMsg  )
{
	int					iErr			=	-1;
	MC_VAR_isCli		*	pProcInfo		=	(  MC_VAR_isCli  *  )pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	QY_MC			*	pQyMc			=	(  QY_MC  *  )pProcInfo->pQyMc;

	//  
	int					cnt				=	0;
	QY_PLAYER		*	pPlayer			=	NULL;

	if  (  !pMsg  )  {
		traceLogA(  (char*)  "doWnd_guiMsgArrive failed: pMsg is NULL"  );
		return  -1;
	}
	//  unsigned  int		len;
	BOOL				bSkipped;

	MIS_MSG_procVideo_qmc		msgProcVideos[CONST_nGetMsgs_procVideo];
	MIS_MSGU				*	pMsgs[CONST_nGetMsgs_procVideo];
	int							len_pMsgs[CONST_nGetMsgs_procVideo];
	int							max_nMsgs  =  CONST_nGetMsgs_procVideo;
	int							nMsgs;
	int							i;

	//  traceLogA(  (char*)  "doWnd_guiMsgArrive"  );
#ifdef  __DEBUG__
#endif

	//
	for  (  i  =  0;  i  <  max_nMsgs;  i  ++  )  {
		 pMsgs[i]  =  (  MIS_MSGU  *  )&msgProcVideos[i];
	}

	//
	if  (  index_player  <  0  ||  index_player  >=  pProcInfo->av.usCnt_players  )  goto  errLabel;
	pPlayer  =  &pProcInfo->av.pPlayers[index_player];

	//
	BOOL	ucbDisplayAllFrames; ucbDisplayAllFrames = FALSE;
#if  0	//  2011/12/10, 因为在1080p时，cpu消耗很大，所以不采用显示所有帧的策略了
	ucbDisplayAllFrames  =  pPlayer->video.m_var.ucbDisplayAllFrames;
#endif

	//
	for  (  ;  !pQyMc->bQuit;  )  {
		 
		 if  (  isQ2Empty(  &pPlayer->video.displayQ2  )  )  break;

		 for  (  i  =  0;  i  <  max_nMsgs;  i  ++  )  {
			  len_pMsgs[i]  =  sizeof(  MIS_MSG_procVideo_qmc  );
		 }
		 nMsgs  =  max_nMsgs;

		 //
		 nMsgs = 2;

#if  0
		 {
			 CQyQ2Help			q2Help;
			 if  (  qGetMsgs(  q2Help.getQ_toGetMsg(  &pPlayer->video.displayQ2  ),  (  void  **  )pMsgs,  (  unsigned  int  *  )len_pMsgs,  (  unsigned  int  *  )&nMsgs  )  )  break;
		 }
#endif  //  2014/04/10
		 if  (  q2GetMsgs(  &pPlayer->video.displayQ2,  (  void  **  )pMsgs,  (  unsigned  int  *  )len_pMsgs,  (  unsigned  int  *  )&nMsgs,  _T(  "doWnd_guiMsgArrive"  )))  break;
		 
		 cnt  ++  ;

		 for  (  i  =  0;  i  <  nMsgs;  i  ++  )  {
			  pMsg  =  pMsgs[i];
			  bool bPktsRedirected = false;
			  switch  (  pMsg->uiType  )  {
				      case  CONST_misMsgType_procVideo_qmc:

						    //
						    //traceLog(_T("doWnd_guiMsgArrive: index_player %d, idInfo %I64u, pts %d"), pMsg->procVideo.playerId.index_player, pMsg->procVideo.idInfo_sender.ui64Id, pMsg->procVideo.pkt.head.uiPts);


						    //
							bSkipped  =  FALSE;
							if  (  pMsg->procVideo.playerId.index_player  !=  index_player  )  {
   							   #if  10
								    traceLogA(  (char*)  "doWnd_guiMsgArrive: msg.index_player %d != %d, skipped.",  pMsg->procVideo.playerId.index_player,  index_player  );			
									qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doWnd_guiMsgArrive: msg.index_player %d != %d, skipped."  ),  pMsg->procVideo.playerId.index_player,  index_player  );			
								#endif	
								bSkipped  =  TRUE;						   
							}				
							if  (  !ucbDisplayAllFrames  &&  i  !=  nMsgs  -  1  )  {
								#ifdef  __DEBUG__
										#if  0
											traceLogA(  (char*)  "doWnd_guiMsgArrive: msg is not the last one, skipped."  );			
											qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doWnd_guiMsgArrive: msg is not the last one, skipped. nMsgs %d, cnt %d"  ),  nMsgs,  cnt  );
										#endif	
								#endif
								bSkipped  =  TRUE;						   			 
							}		 					  

							if  (  !bSkipped  )  {
							   ::SendMessage(  hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  ); 

							   //
							   if  (  0  )
							   {
								   static  DWORD  dwTickCnt_lastPkt = 0;
								   DWORD  dwTickCnt = myGetTickCount(mynull);
								   int  iDiffInMs = dwTickCnt - dwTickCnt_lastPkt;
								   dwTickCnt_lastPkt = dwTickCnt;
								   TCHAR  tBuf[128];
								   _sntprintf(tBuf, mycountof(tBuf), _T("downd_guiMsgArrive: %I64u: pts %d,  iDiff %dms."), pMsg->procVideo.idInfo_sender.ui64Id,  pMsg->procVideo.pkt.head.uiPts,  iDiffInMs);
								   showInfo_open0(0, 0, tBuf);

							   }


							   //
							   if  (  bForce_displayAllFrames  )  pPlayer->video.m_var.ucbDisplayAllFrames  =  TRUE;
							   else  {
								     if  (  pMsg->procVideo.ucbDisplayAllFrames  !=  pPlayer->video.m_var.ucbDisplayAllFrames  )  pPlayer->video.m_var.ucbDisplayAllFrames  =  pMsg->procVideo.ucbDisplayAllFrames;	//  2009/07/25							 
							   }
							}
					 
							//  2014/09/23
							if  (  !pMsg->procVideo.idInfo_peer.ui64Id  &&  pMsg->procVideo.uiCapType  )  {
								BOOL  bRedirected  =  FALSE;
								chkSharedObjSlave(  &pMsg->procVideo,  &bRedirected  );  
								if  (  bRedirected  )  break;
							}

							//  2012/11/09
							M_msg_showNo(  pMsg->procVideo,  _T(  "doWnd_guiMsgArrive, free"  )  );

							
							if (pMsg->procVideo.pkt.decInfo.dynBmp.resObj.uiObjType == CONST_objType_ic) {
								if (!q2PostMsgAndTrigger(&pMsg->procVideo.pkt, 1 * sizeof(pMsg->procVideo.pkt), &pProcInfo->icQ2, _T("save_ic"))) {
									bPktsRedirected = TRUE;
									
								}
							}

						   //  if  (  pMsg->procVideo.data  )  free(  pMsg->procVideo.data  );	//  very important
							if(!bPktsRedirected)
								freeMemory(  &pMsg->procVideo.pkt.memory  );	//  2010/04/23

							//
						   break;
					 default:
						     traceLogA(  (char*)  "CMainFrame::OnQyPostComm: guiMsgArrive:  unprocessed: msgType: %d",  pMsg->uiType  );										
							 break;								
			 }
		 }
		 //  if  (  pPlayer->video.m_var.ucbDisplayAllFrames  )  
		 {
			 if  (  cnt  >=  2  )		//  2011/07/16
			 {
				 if  (  !isQ2Empty(  &pPlayer->video.displayQ2  )  )  {
					 ::PostMessage(  hWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_guiMsgArrive,  index_player  );   							   
				 }
				 break;
			 }
		 }
	}
				  

	iErr  =  0;
errLabel:
	return  iErr;
 

}


 //  int  doMainWnd_procVideo(  QY_MC  *  pQyMc,  CMainFrame  *  pMainFrame,  MIS_MSG_procVideo_qmc  *  pMsg  )
 int  doMainWnd_procVideo(  void  *  pQyMcParam,  MIS_MSG_procVideo_qmc  *  pMsg  )
{
	int				iErr		=	-1;
	QY_MC		*	pQyMc		=	(  QY_MC  *  )pQyMcParam;
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	
	FUNCS_for_isCliHelp		*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	if  (  !pMsg->pMisCnt  )  {
		traceLogA(  (char*)  "doMainWnd::procVideo failed, pMisCnt is null"  );
		return  -1;
	}
	LRESULT			lRet;

	if  (  !pMsg->idInfo_peer.ui64Id  &&  pMsg->uiCapType  )  {
		switch  (  pMsg->uiCapType  )  {
				case  CONST_capType_av:
					  /*
					  if  (  pProcInfo->av.localAv.videoCaptureProcInfo.hDlg  )  {
						  lRet  =  SendMessage(  pProcInfo->av.localAv.videoCaptureProcInfo.hDlg,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  ); 
						  if  (  lRet  !=  CONST_qyWmRc_ok  )  {
							  if  (  !IsWindow(  pProcInfo->av.localAv.videoCaptureProcInfo.hDlg  )  )  pProcInfo->av.localAv.videoCaptureProcInfo.hDlg  =  NULL;
						  }
						  break;
					  }
					  */
					  lRet  =  SendMessage(  pProcInfo->av.localAv.videoCaptureProcInfo.curhWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  ); 
					  if  (  lRet  !=  CONST_qyWmRc_ok  )  {
						  if  (  !IsWindow(  pProcInfo->av.localAv.videoCaptureProcInfo.curhWnd  )  )  pProcInfo->av.localAv.videoCaptureProcInfo.curhWnd  =  NULL;
					  }					  
					  break;
				case  CONST_capType_mediaFile:  {
					  CAP_procInfo_mediaFileBmp  *  pBc;
					  pBc  =  (  CAP_procInfo_mediaFileBmp  *  )getCapBmpBySth(  pProcInfo,  pMsg->iIndex_capProcInfo,  0  );
					  if  (  !pBc  ||  pBc->uiType  !=  pMsg->uiCapType  )  break;
					  if  (  pBc->curhWnd  )  {
						  lRet  =  SendMessage(  pBc->curhWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  ); 
						  if  (  lRet  !=  CONST_qyWmRc_ok  )  {
							  if  (  !IsWindow(  pBc->curhWnd  )  )  pBc->curhWnd  =  NULL;
						  }
					  }
					  }
					  break;
				default:
						traceLogA(  (char*)  "doMainWnd_procVideo: unprocessed capType %d",  pMsg->uiCapType  );
						break;
		}
		iErr  =  0;  goto  errLabel;
	}
	
	HWND  hWnd;

	if  (  pFuncs->pf_findTalker(  pQyMc,  &pMsg->idInfo_peer,  &hWnd  )  )  {
		traceLogA(  (char*)  "doMainWnd_procVideo: findTalker failed"  );
		goto  errLabel;
	}

	SendMessage(  hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  ); 

	iErr  =  0;
errLabel:
	return  iErr;
}


