






#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//#include	"qmcVideoCapture_isCli.h"
//#include	"qyAvRecordPublic.h"
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
#include	"qmcCopyData.h"
#include	"rtspUsrData.h"
#include	"CtxQmcDvt.h"

//
#include	"vtShmFunc.h"




//  2011/07/15, Ã¿´Î¶ÁÈ¡Èô¸É°üÈ»ºóÒ»´ÎÐÔÑ¹Ëõ
 DWORD WINAPI mcThreadProc_writeShm_dvt( LPVOID lpParameter )
{
	//VIDEO_capDev_rtsp  *  pRtsp  =  (  VIDEO_capDev_rtsp  *  )lpParameter;
	QY_TRANSFORM  *  pTransform  =  (  QY_TRANSFORM  *  )lpParameter;  //  2015/10/06
	if  (  !pTransform  )  return  -1;
	VIDEO_capDev_rtsp  *  pRtsp  =  (  VIDEO_capDev_rtsp  *  )pTransform->pCapDev_rtsp;
	if  (  !pRtsp  )  return  -1;

	 MC_VAR_common					*	pProcInfo					=	(  MC_VAR_common  *  )pRtsp->pProcInfoCommon;//QY_GET_procInfo_isCli(  );
	 if (  !pProcInfo  )  return  -1;	 

	 int							iIndex_sharedObj			=	(  int  )lpParameter;

	 QY_MC						*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;	//  


	 //
	 DWORD							dwThreadId					=	GetCurrentThreadId(  );

	 myDRAW_VIDEO_DATA				pkts[CONST_pkts_vpp];
	 unsigned  int					uiLens[CONST_pkts_vpp];		//  qGetMsgs pPkts pktLens 2011/07/15
	 int							nLens						=	mycountof(  uiLens  );		//  
	 int							i;
	 int							nPkts;						//								pPkts[] 2011/07/15
	 //  2015/02/18
	 int							total_nPkts					=	0;
	 TCHAR							tBuf[128];

	 //
#if  0
	 CQyMalloc						mallocObj_pMsgBuf;
	 MIS_MSGU					*	pMsgBuf						=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsgBuf  )  return  -1;
#endif

	 //
	 DWORD							dwTickCnt;

	 //  2010/09/18
	 //  int							tmpiRet;
	 BOOL							tmpbErr;
	 
	 QY_Q2  *  pCacheQ2  =  &pRtsp->cacheQ2_dvt_decV;

	 DVT_decV					*	pDvt_decV					=	(  DVT_decV  *  )pRtsp->pDvt_decV;
	 if  (  !pDvt_decV  )  return  -1;
	 QY_shm  *  pShm  =  &pDvt_decV->dataShm;
	 if  (  !pShm->pBuf  )  return  -1;
	 VT_shm_content  *  pShmContent  =  (  VT_shm_content  *  )pShm->pBuf;
	 BITMAPINFOHEADER	bih_shm  =  pShmContent->bih_dec;

	 //  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u starts"  ),  pPlay->q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id  );

	 for  (  ;  !pRtsp->bQuit;  )  {
		  if  (  pDvt_decV->bQuit  )  {
			  showInfo_open0(  0,  0,  _T(  "writeShm: dvt_decV.bQuit is true, quit soon"  )  );
			  goto  errLabel;
		  }

		  //
		  HANDLE  hs[5];
		  unsigned  short  usCnt_hs  =  0;
		  hs[usCnt_hs]  =  pCacheQ2->hEvents[0];  usCnt_hs  ++  ;
		  hs[usCnt_hs]  =  pCacheQ2->hEvents[1];  usCnt_hs  ++  ;
		  hs[usCnt_hs]  =  pDvt_decV->writeShm.hEvent_syncW;  usCnt_hs  ++  ;
		  

		  //
		  DWORD  dwEvt  =  MsgWaitForMultipleObjects(
							 usCnt_hs,		//  pCacheQ2->cfg.usCnt_hEvents,	//  mycountof(  pPlay->hEvents  ),				// Number of events.
							 hs,			//  pCacheQ2->hEvents,							// Location of handles.
                             FALSE,										// Wait for all?
                             5000,									// How long to wait?
                             0  );										// Any message is an 
																		// event.
		  if  (  dwEvt  ==  WAIT_FAILED  )  goto  errLabel;
	      //
		  dwTickCnt  =  GetTickCount(  );

		  if  (  dwEvt  !=  WAIT_TIMEOUT  )  {
			  dwEvt -= WAIT_OBJECT_0;
			  switch  (  dwEvt  )  {
					  case  0:
						     //  dwTickCnt_lastData  =  dwTickCnt;		//  audio data received
						       //  traceLogA(  "mcThreadProcInfo_vpp: event 0."  );
							 break;
					  case  1:
							 #ifdef  __DEBUG__
									 traceLogA(  "mcThreadProcInfo_vpp: event 1."  );
							 #endif
							 break;
					  case  2:
							 #ifdef  __DEBUG__
									 //showInfo_open0(  0,  0,  _T(  "writeShm:event2"  )  );
							 #endif
						     break;
					  default:
						     traceLogA(  "unknown event"  );	
		  					 goto  errLabel;
							 break;
			  }
		  }

#ifdef  __DEBUG__
		#if  0
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "writeShm here£¬ uiCnt_read %d, uiCnt_write %d"  ),  pShmContent->status_readShm.uiCnt_readShm,  pShmContent->status_writeShm.uiCnt_writeShm  );
		  showInfo_open0(  0,  0,  tBuf  );
		#endif
#endif
	
		  for  (  ;  !pRtsp->bQuit;  )  {
			  if  (  pDvt_decV->bQuit  )  {
				  showInfo_open0(  0,  0,  _T(  "writeShm: dvt_decV.bQuit is true, quit soon"  )  );
				  goto  errLabel;
			  }
			  
			  //
			  if  (  isQ2Empty(  pCacheQ2  )  )  {
				  #ifdef  __DEBUG__
						  //showInfo_open0(  0,  0,  _T(  "writeShm cacheQ2 empty"  )  );
				  #endif
				  break;
			  }

			   //  2011/07/15, ÏÈ½«pktsÇå¿Õ,nPkts ¸³ 0
			   nPkts  =  0;
			  {
				  #define		CONST_pkts_writeShm		CONST_pkts_vpp	//  2015/02/10
				  CQyMalloc		mallocObj_tmpPkts[CONST_pkts_writeShm];

				  
				  //
				  int  ucCnt_shmPkts  =  pShmContent->ucCnt_shmPktBufs;
				  if  (  !ucCnt_shmPkts  ||  ucCnt_shmPkts  >  mycountof(  pShmContent->mems  )  )  goto  errLabel;
				  //				  
				  int  index_toWrite  =  pShmContent->status.writeShm.uiCnt_writeShm  %  ucCnt_shmPkts;
				  if  (  pShmContent->mems[index_toWrite].bDataReady  )  {
					  if  (  pShmContent->u.dvt.i.ucbShowPostDecVStatus  )  
					  {
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "writeShm failed: shm.mems[%d].bDataReady is true. cnt_writeShm %d, cnt_readShm %d. try to wait"  ),  index_toWrite,  pShmContent->status.writeShm.uiCnt_writeShm,  pShmContent->status.readShm.uiCnt_readShm   );
						  showInfo_open0(  0,  0,  tBuf  );
					  }
					  break;
				  }				  

				  
				  //
				  {		//  qGetMsg ¸ qGetMsgs...

					  //  pktLen  =  uiBufSize;  
					  nLens  =  mycountof(  uiLens  );
					  //  2014/04/10
					  if  (  q2GetMsgPkg(  pCacheQ2,  (  void  *  )pkts,  sizeof(  pkts  ),  (  unsigned  int  *  )uiLens,  (  unsigned  int  *  )&nLens  )  )  {												
						  break;			   						  
					  }

					  for  (  i  =  0;  i  <  nLens;  i  ++  )  {
						   nPkts  +=  uiLens[i]  /  sizeof(  pkts[0]  );
						   if  (  uiLens[i]  %  sizeof(  pkts[0]  )  )  {
							   #ifdef  __DEBUG__
									   traceLog(  _T(  "vpp: uiLen err"  )  );
									   assert(  0  );
							   #endif
						   }
					  }
					  //
					  #ifdef  __DEBUG__
							  //
							  if  (  nPkts  >  mycountof(  mallocObj_tmpPkts  )  )  {						  
								  assert(  0  );					  
							  }
							  //
							  if  (  mycountof(  mallocObj_tmpPkts  )  !=  mycountof(  pkts  )  )  {
								  assert(  0  );
							  }
					  #endif
					  
					  //
					  tmpbErr  =  FALSE;	//  attach attach, continue. pPkts[i]
					  for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
						   if  (  pkts[i].memory.m_pBuf  )  {
							   if  (  mallocObj_tmpPkts[i].attach(  &pkts[i].memory  )  )  {
								   #ifdef  __DEBUG__
										  traceLogA(  "mcThreadProc_writeShm: mallocObj.attach failed"  );
								   #endif
								   //
								   freeMemory(  &pkts[i].memory  );  
								   tmpbErr  =  TRUE;			   
							   }					  
						   }
					  }
					  if  (  tmpbErr  )  continue;


				  }
			   
				  if  (  !nPkts  )  {
					  #ifdef  __DEBUG__
							  assert(  0  );			//  Ó¦¸Ã²»ÄÜÔËÐÐµ½ÕâÀï
							  traceLog(  _T(  "mcThreadProc_vpp: no pkts read."  )  );
					  #endif
					  break;
				  }
				  #if  0
				  if  (  nPkts  !=  1  )  {
					  showInfo_open0(  0,  0,  _T(  "err: writeShm: nPkt is not 1"  )  );
				  }
				  #endif

				  //  traceLogA(  "playVideo: msg reaved, pktLen %d, dataLen %d",  pktLen,  pPkt->head.uiLen  );

				  tmpbErr  =  FALSE;
				  //
				  //
				  for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
					   myDRAW_VIDEO_DATA  *  tmppPkt  =  &pkts[i];
					   //
					   #ifdef  __DEBUG__
							   #if  0
							   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "mcThreadProc_writeShm err: pkt.%dX%d, uiSize_dec %d !=  bih.%dX%d, sizeImage %d. skipped"  ),  
																																			tmppPkt->bih.biWidth,  tmppPkt->bih.biHeight,  tmppPkt->bih.biSizeImage,  
																																			bih_shm.biWidth,  bih_shm.biHeight,  bih_shm.biSizeImage  );
							   #endif
					   #endif

					   //  2015/10/17
					   if  (  tmppPkt->usPktResType  ==  CONST_pktResType_sharedTex  )  {
						   if  (  tmppPkt->bih.biWidth  !=  bih_shm.biWidth
							   ||  tmppPkt->bih.biHeight  !=  bih_shm.biHeight  )
						   {
							   showInfo_open0(  0,  0,  _T(  "thread_writeShm: pkt.bih != bih_shm, skipped"  )  );
							   tmpbErr  =  TRUE;
							   break;
						   }
						   }
					   else  {
						     if  (  tmppPkt->bih.biSizeImage  !=  bih_shm.biSizeImage  )  {
								 #ifdef  __DEBUG__
								   traceLogA(  (  "mcThreadProc_writeShm err: pkt.uiSize_dec %d !=  sizeImage %d. skipped"  ),  tmppPkt->bih.biSizeImage,  bih_shm.biSizeImage  );
								 #endif
								 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "mcThreadProc_writeShm err: pkt.%dX%d, uiSize_dec %d !=  bih.%dX%d, sizeImage %d. skipped"  ),  
																																			tmppPkt->bih.biWidth,  tmppPkt->bih.biHeight,  tmppPkt->bih.biSizeImage,  
																																			bih_shm.biWidth,  bih_shm.biHeight,  bih_shm.biSizeImage  );
								 //
								 tmpbErr  =  TRUE;
								 break;					   
							 }
					   }
				  }
				  //
				  if  (  tmpbErr  )  continue;

				  //
				   #ifdef  __DEBUG__
						   #if  10
								//  traceLogA(  "mcThreadProc_vpp: pkt.SampleTime %d",  pPkt->head.uiSampleTimeInMs  );				  
								//  traceLog(  _T(  "mcThreadProc_vpp: nLens %d,  nPkts %d"  ),  nLens,  nPkts  );
								M_pkts_showNo_vpp(  pkts,  nPkts  );
								//
						   #endif
				   #endif
		

				   //
				   int  nWritten  =  0;
				   for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
					   //  2015/02/18
					   total_nPkts  ++  ;
					   //
					   
					   index_toWrite  =  pShmContent->status.writeShm.uiCnt_writeShm  %  ucCnt_shmPkts;
					   if  (  pShmContent->mems[index_toWrite].bDataReady  )  {
						   if  (  pShmContent->u.dvt.i.ucbShowPostDecVStatus  )  					  
						   {
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "writeShm failed: shm.mems[%d].bDataReady is true. cnt_writeShm %d, cnt_readShm %d. try to wait"  ),  index_toWrite,  pShmContent->status.writeShm.uiCnt_writeShm,  pShmContent->status.readShm.uiCnt_readShm   );
							   showInfo_open0(  0,  0,  tBuf  );					  
						   }					  
						   break;
					   }
					   //
					   if  (  writeShmPkt(  &pkts[i],  pShmContent,  &bih_shm,  ucCnt_shmPkts,  index_toWrite  )  )  {
						   showInfo_open0(  0,  0,  _T(  "writeShm err, writeShmPkt failed"  )  );
						   }
					   else  {
						     pShmContent->status.writeShm.uiCnt_writeShm  ++  ;					   
							 //
							 nWritten  ++  ;
					   }
				   }
				   //
				   if  (  nWritten  )  {  //  Note: nPkts
					   SetEvent(  pDvt_decV->writeShm.hEvent_syncR  );
				   }

				   //  2015/10/06
				   if  (  pShmContent->status.uiSeqNo_lastRender  )  {
					   unsigned  int  uiSeqNo_lastRender  =  pShmContent->status.uiSeqNo_lastRender;
					   //  
					   switch  (  pTransform->video.tv.compressor.common.ucCompressors  )  {
							   case  CONST_videoCompressors_vcm:
							   case  CONST_videoCompressors_dmo:
								     break;
							   default:
								       QDC_OBJ_INFO  *  pQdcObjInfo  =  &pTransform->video.u.qoi.myQoi.common;	//  .qdcObjInfo;
									   pQdcObjInfo->var.sharedTex.uiSeqNo_lastRender  =  uiSeqNo_lastRender;
									   //
									   #ifdef  __DEBUG__
											   #if  0
													_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "writeShm: uiSeqNo_lastRender %d"  ),  (  int  )pQdcObjInfo->var.decInfo.uiSeqNo_lastRender  );					   
													showInfo_open0(  0,  0,  tBuf  );
											   #endif
									   #endif
									   //
									   break;
					   }

					   //

				   }

				   //
				  #ifdef  __DEBUG__
				  #endif

				   //
				   if  (  nPkts  )  {  //  2015/02/04
					   CCtxQmcDvt  *  pCtx  =  (  CCtxQmcDvt  *  )pProcInfo;
					   pCtx->m_var.dvtStatus.dwLastTickCnt_writeShm  =  GetTickCount(  );
				   }

					#ifdef  __DEBUG__
					#endif

			   }

			   continue;
		  }

		  continue;
	 }

	 //
#ifdef  __DEBUG__
		traceLogA(  "mcThreadProc_writeShm will quit"  );
#endif

errLabel:
			
	 return  0;

}
