
#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"
#include	"tmpCeLib.h"
#include	"qmcVideoCapture.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#include	"qmcCmdProc.h"

//  #include	"qySqlFunc.h"
//#include	"qyAvRecordPublic.h"
//#include	"imgProcessPublic.h"
//#include	"isCliHelpPublic.h"

//#include	"qmcCommFunc_isCli.h"
#include	"vppProc.h"


 DWORD WINAPI mcThreadProc_vpp1_proc( LPVOID lpParameter )
 {
	 CTX_vpp  *  pCtx  =  (  CTX_vpp  *  )lpParameter;
	 if  (  !pCtx  )  return  -1;
	 int   iIndex_sharedObj  =  pCtx->iIndex_sharedObj;

	 //
	 QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();
	 if  (  !pQyMc  )  {
		 return  -1;
	 }
	 MC_VAR_common					*	pProcInfo				=	(MC_VAR_common*)pQyMc->get_pProcInfo(  );
	 if (  !pProcInfo  )  return  -1;

	 QY_SHARED_OBJ				*	pSharedObj					=	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	 if  (  !pSharedObj  )  return  -1;

	 CAP_procInfo_bmpCommon		*	pCapProcInfo1				=  (  CAP_procInfo_bmpCommon  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
	 if  (  !pCapProcInfo1  )  return  -1;


	 //  2010/12/28

	 //  2009/12/24
#if  0
	 QM_SHM_CMD					*	pShmCmd						=	NULL;
	 QM_SHM_DATA				*	pShmData					=	NULL;
	 TCHAR							mutexName_syncShmData[64]	=	_T(  ""  );
	 pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pSharedObj->iIndex_shmCmd  );
	 pShmData  =  (  QM_SHM_DATA  *  )pSharedObj->dataShm.pBuf;
	 _sntprintf(  mutexName_syncShmData,  mycountof(  mutexName_syncShmData  ),  _T(  "%s%u"  ),  CONST_mutexName_qm_syncData_v,  pSharedObj->uiTranNo  );
#endif

	 //
	 DWORD							dwThreadId					=	GetCurrentThreadId(  );

	 myDRAW_VIDEO_DATA				pkts[CONST_pkts_vpp];
	 unsigned  int					uiLens[CONST_pkts_vpp];		//  要增加一个qGetMsgs，将pPkts和pktLens作为参数输入。2011/07/15
	 int							nLens						=	mycountof(  uiLens  );		//  一次最多处理的包数。
	 int							i;
	 int							nPkts;						//								pPkts[]中有几个包是有效的。 2011/07/15

	 MIS_CNT					*	pMisCnt						=	(  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );
	 if  (  !pMisCnt  )  return  -1;	 	 

	 CQyMalloc						mallocObj_pMsgBuf;
	 MIS_MSGU					*	pMsgBuf						=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsgBuf  )  return  -1;


	 DWORD							dwTickCnt;

	 //  2010/09/18
	 //  int							tmpiRet;
	 BOOL							tmpbErr;


	 //
	 traceLogA(  (char*)  "mcThreadProc_vpp1 %S enters",  pCtx->vppThread1_proc.q2.cfg.name  );

	 //
	 pCtx->vppThread1_proc.bRunning  =  TRUE;



	 //  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u starts"  ),  pPlay->q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id  );
	 

	 /////////////////

	 for  (  ;  !pCtx->vppThread1_proc.bQuit;  )  {
		  
		  //  2010/12/28
		  //pCapProcInfo->compressVideo.debugInfo.nStep  =  105;

		  //
		  DWORD  dwEvt  =  MsgWaitForMultipleObjects(
							pCtx->vppThread1_proc.q2.cfg.usCnt_hEvents,	//  mycountof(  pPlay->hEvents  ),				// Number of events.
							 pCtx->vppThread1_proc.q2.hEvents,							// Location of handles.
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
						       //  traceLogA(  (char*)  "mcThreadProcInfo_vpp: event 0."  );
							 break;
					  case  1:
						     traceLogA(  (char*)  "mcThreadProcInfo_vpp: event 1."  );
							 break;
					  default:
						     traceLogA(  (char*)  "unknown event"  );	
		  					 goto  errLabel;
							 break;
			  }
		  }

	
		  for  (  ;  !pCtx->vppThread1_proc.bQuit;  )  {

			   //  2011/07/15, 先将pkts清空,nPkts 赋 0
			   nPkts  =  0;
			  {
				  CQyMalloc		mallocObj_tmpPkts[CONST_pkts_vpp];

				  if  (  !isQ2Empty(  &pCtx->vppThread1_proc.q2  )  )  {		//  这里要将 qGetMsg 改成 qGetMsgs...

					  //  pktLen  =  uiBufSize;  
					  nLens  =  mycountof(  uiLens  );
					  //  2014/04/10
					  if  (  q2GetMsgPkg(  &pCtx->vppThread1_proc.q2,  (  void  *  )pkts,  sizeof(  pkts  ),  (  unsigned  int  *  )uiLens,  (  unsigned  int  *  )&nLens,  _T(  "vpp1"  ))) {
						  break;			   						  
					  }

					  for  (  i  =  0;  i  <  nLens;  i  ++  )  {
						   nPkts  +=  uiLens[i]  /  sizeof(  pkts[0]  );
						   if  (  uiLens[i]  %  sizeof(  pkts[0]  )  )  {
							   #ifdef  __DEBUG__
									   traceLog((TCHAR*)  _T(  "vpp: uiLen err"  )  );
									   assert(  0  );
							   #endif
						   }
					  }
					  
					  tmpbErr  =  FALSE;	//  注意：这里如果attach出错，要继续attach, 但是最后要continue. 以防止pPkts[i]没有机会释放内存
					  for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
						   if  (  pkts[i].memory.m_pBuf  )  {
							   if  (  mallocObj_tmpPkts[i].attach(  &pkts[i].memory  )  )  {
								   traceLogA(  (char*)  "mcThreadProc_vpp: mallocObj.attach failed"  );
								   freeMemory(  &pkts[i].memory  );  
								   tmpbErr  =  TRUE;			   
							   }					  
						   }
					  }
					  if  (  tmpbErr  )  continue;

					  }
			   
				  if  (  !nPkts  )  {
					  #ifdef  __DEBUG__
							  //traceLog((TCHAR*)  _T(  "mcThreadProc_vpp1: no pkts read."  )  );
					  #endif
					  break;
				  }

				  //  traceLogA(  (char*)  "playVideo: msg reaved, pktLen %d, dataLen %d",  pktLen,  pPkt->head.uiLen  );

				  tmpbErr  =  FALSE;
				  //
				  if (0) {
					  for (i = 0; i < nPkts; i++) {
						  if (pkts[i].uiSize_dec < pCapProcInfo1->compressVideo.vh_decompress.bih.biSizeImage) {
							  traceLogA((char*)("mcThreadProc_vpp err: pkt.uiSize_dec %d <  sizeImage %d. skipped"), pkts[i].uiSize_dec, pCapProcInfo1->compressVideo.vh_decompress.bih.biSizeImage);
							  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("mcThreadProc_vpp err: pkt.uiSize_dec %d !=  sizeImage %d. skipped"), pkts[i].uiSize_dec, pCapProcInfo1->compressVideo.vh_decompress.bih.biSizeImage);
							  tmpbErr = TRUE;
							  break;
						  }
					  }
				  }
				  //
				  if  (  tmpbErr  )  continue;

				   #ifdef  __DEBUG__
						   #if  10
								//  traceLogA(  (char*)  "mcThreadProc_vpp: pkt.SampleTime %d",  pPkt->head.uiSampleTimeInMs  );				  
								//  traceLog((TCHAR*)  _T(  "mcThreadProc_vpp: nLens %d,  nPkts %d"  ),  nLens,  nPkts  );
								M_pkts_showNo_vpp(  pkts,  nPkts  );
								//
								if  (  pSharedObj->bSlave  )  {
									int  i;
									i  =  0;
								}
								//
								#if  0
								TCHAR  tBuf[128];
								for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
									_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "thread_vpp1: pkt %d"  ),  pkts[i].head.uiSampleTimeInMs  );
									showInfo_open0(  0,  0,  tBuf  );
								}
								#endif

						   #endif
				   #endif


				   // 
				   tmpbErr  =  FALSE;
				   for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
					    if  (  pCtx->ucbSingleThread_vpp  )  {
							}
						else  {  //  把数据格式转成rgb.
						      if  (  doVpp1(  pProcInfo,  pCtx,  pSharedObj,  pCapProcInfo1,  &pkts[i],  sizeof(  pkts[i]  )  )  )  {
								  #ifdef  __DEBUG__
										traceLog((TCHAR*)  _T(  "doVpp failed"  )  );
								  #endif
								  tmpbErr  =  TRUE;
								  break;
							  }						
						}
				   }
				   if  (  tmpbErr  )  {
					   showInfo_open0(  0,  0,  _T(  "doVpp1 failed, skipped"  )  );
					   continue;
				   }

				   //
				   BOOL  bPktsRedirected  =  FALSE;
				   //
				   if  (  pCtx->ucbSingleThread_vpp  )  {
					   //
					   }
				   else  {  //  2015/05/07. 送给vpp1
					     if  (  !q2PostMsgAndTrigger(  pkts,  nPkts  *  sizeof(  pkts[0]  ),  &pCtx->vppThread2_beforeEnc.q2,  _T(  "vpp1"  ))) {
							 bPktsRedirected  =  TRUE;					   
						 }
				   }
				   //
				   if  (  bPktsRedirected  )  {
					   for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
							mallocObj_tmpPkts[i].detach(    );
						}
				   }

					#ifdef  __DEBUG__
							if  (  !bPktsRedirected  )  {
								M_pkts_showNo(  pkts,  nPkts,  _T(  "vpp free"  )  );
							}
					#endif

			   }

			   continue;
		  }

		  continue;
	 }

	 traceLogA(  (char*)  "mcThreadProc_vpp1 will quit"  );

errLabel:

	 //  2010/12/28
	 //pCapProcInfo->compressVideo.debugInfo.nStep  =  199;

	 //
	 pCtx->vppThread1_proc.bRunning  =  FALSE;


	 //
	 traceLogA(  (char*)  "mcThreadProc_vpp1 %S leaves",  pCtx->vppThread1_proc.q2.cfg.name  );
	
	 return  0;

}





