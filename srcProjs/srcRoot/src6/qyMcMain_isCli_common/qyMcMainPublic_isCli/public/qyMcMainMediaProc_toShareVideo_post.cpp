

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
#include	"qmcVideoCapture.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#include	"qmcCmdProc.h"

#include	"qySqlFunc.h"
//#include	"qyAvRecordPublic.h"

//#include	"qmcCommFunc_isCli.h"






//


 //  2011/07/15, 每次读取若干包然后一次性压缩
 DWORD WINAPI mcThreadProc_toShareVideo_post( LPVOID lpParameter )
{
	 int							iIndex_sharedObj			=	(  int  )lpParameter;

	 QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();
	 if  (  !pQyMc  )  {
		 return  -1;
	 }
	 MC_VAR_common					*	pProcInfo					=	(MC_VAR_common*)pQyMc->get_pProcInfo(  );//(  MC_VAR_isCli  *  )pSci->pVar;
	 if (  !pProcInfo  )  return  -1;

	 QY_SHARED_OBJ				*	pSharedObj					=	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	 if  (  !pSharedObj  )  return  -1;

	 CAP_procInfo_bmpCommon		*	pCapProcInfo				=  (  CAP_procInfo_bmpCommon  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
	 if  (  !pCapProcInfo  )  return  -1;

	 //  2010/12/28
	 pCapProcInfo->compressVideo.debugInfo.nStep  =  101;

	 //  2009/12/24

	 //
	 DWORD							dwThreadId					=	GetCurrentThreadId(  );

	 int							i;

	 //  unsigned  int					uiBufSize					=	sizeof(  myDRAW_VIDEO_DATA  );
	 myDRAW_VIDEO_DATA				pkts[CONST_pkts_toShareVideo_post];
	 unsigned  int					uiLens[CONST_pkts_toShareVideo_post];		//  要增加一个qGetMsgs，将pPkts和pktLens作为参数输入。2011/07/15
	 int							nLens						=	mycountof(  uiLens  );		//  一次最多处理的包数。
	 int							nPkts;						//								pPkts[]中有几个包是有效的。 2011/07/15

	 MIS_CNT					*	pMisCnt						=	(  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );
	 if  (  !pMisCnt  )  return  -1;	 	 

	 CQyMalloc						mallocObj_pMsgBuf;
	 MIS_MSGU					*	pMsgBuf						=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsgBuf  )  return  -1;


	 DWORD							dwTickCnt;

	 //  2010/09/18
	 //  TMP_MEMORY_GRP					tmpMemoryGrp;
	 //  BOOL							bInited_tmpMemoryGrp		=	FALSE;
	 int							tmpiRet;
	 BOOL							tmpbErr;


	 //
	 traceLogA(  (char*)  "mcThreadProc_toShareBmp_post %S enters",  pCapProcInfo->postThread.q2.cfg.name  );

	 pCapProcInfo->postThread.bQuit  =  FALSE;
	 pCapProcInfo->postThread.bRunning  =  TRUE;


	 //  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u starts"  ),  pPlay->q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id  );
	 

	 /////////////////

	 for  (  ;  !pCapProcInfo->postThread.bQuit;  )  {
		  
		  //  2010/12/28
		  pCapProcInfo->compressVideo.debugInfo.nStep  =  105;

		  //
		  DWORD  dwEvt  =  MsgWaitForMultipleObjects(
							pCapProcInfo->postThread.q2.cfg.usCnt_hEvents,	//  mycountof(  pPlay->hEvents  ),				// Number of events.
							 pCapProcInfo->postThread.q2.hEvents,							// Location of handles.
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
						       //  traceLogA(  (char*)  "mcThreadProcInfo_toShareBmp: event 0."  );
							 break;
					  case  1:
						     traceLogA(  (char*)  "mcThreadProcInfo_toShareBmp: event 1."  );
							 break;
					  default:
						     traceLogA(  (char*)  "unknown event"  );	
		  					 goto  errLabel;
							 break;
			  }
		  }

	
		  for  (  ;  !pCapProcInfo->postThread.bQuit;  )  {

			   //
			   if  (  isQ2Empty(  &pCapProcInfo->postThread.q2  )  )  {		
				   #ifdef  __DEBUG__
						   //  traceLog((TCHAR*)  _T(  "mcThreadProc_toShareBmp: break if q is empty"  )  );
				   #endif
				   break;
			   }

			   nPkts  =  0;
			  {
				  CQyMalloc		mallocObj_tmpPkts[CONST_pkts_toShareVideo_post];
				  
				  //  pktLen  =  uiBufSize;  
				  nLens  =  mycountof(  uiLens  );
				  {
					  CQyQ2Help	q2Help;
					  if  (  qGetMsgPkg(  q2Help.getQ_toGetMsg(  &pCapProcInfo->postThread.q2,  _T(  "toShareVideo_post"  )), (void*)pkts, sizeof(pkts), (unsigned  int*)uiLens, (unsigned  int*)&nLens)) {
						  break;			   
					  }
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
				  //
				  for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
					   myDRAW_VIDEO_DATA	*	pPkt  =  &pkts[i];
					   if  (  pPkt->memory.m_pBuf  )  {					
						   if  (  mallocObj_tmpPkts[i].attach(  &pPkt->memory  )  )  {
							   traceLogA(  (char*)  "mcThreadProc_toShareBmp: mallocObj.attach failed"  );
							   freeMemory(  &pPkt->memory  );  
							   tmpbErr  =  TRUE;	
							   continue;
						   }					  
					   }
				  }
				  if  (  tmpbErr  )  continue;
			   
				  if  (  !nPkts  )  {
					  #ifdef  __DEBUG__
							  assert(  0  );			//  应该不能运行到这里
							  traceLog((TCHAR*)  _T(  "mcThreadProc_toShareBmp: no pkts read."  )  );
					  #endif
					  break;
				  }

				  //  traceLogA(  (char*)  "playVideo: msg reaved, pktLen %d, dataLen %d",  pktLen,  pPkt->head.uiLen  );
				  tmpbErr  =  FALSE;
				  for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
					   //  2014/02/24
					   if  (  pkts[i].usPktResType  ==  CONST_pktResType_sharedTex  )  {
						   continue;
					   }
					   //
					   if  (  pkts[i].uiSize_dec  <  pCapProcInfo->compressVideo.vh_decompress.bih.biSizeImage  )  {
						   #ifdef  _DEBUG__
								   traceLogA(  (char*)  (  "toShareVideo_post err: pkt.uiSize_dec %d <  sizeImage %d. skipped"  ),  pkts[i].uiSize_dec,  pCapProcInfo->compressVideo.vh_decompress.bih.biSizeImage  );
						   #endif
						   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)"",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "toShareVideo_post err: pkt.uiSize_dec %d !=  sizeImage %d. skipped"  ),  pkts[i].uiSize_dec,  pCapProcInfo->compressVideo.vh_decompress.bih.biSizeImage  );
						   tmpbErr  =  TRUE;
						   break;
					   }
				  }
				  if  (  tmpbErr  )  continue;

				   #ifdef  __DEBUG__
						   #if  10
								//  traceLogA(  (char*)  "mcThreadProc_toShareBmp: pkt.SampleTime %d",  pPkt->head.uiSampleTimeInMs  );				  
								//  traceLog((TCHAR*)  _T(  "mcThreadProc_post: nPkts %d"  ),  nPkts  );
								M_pkts_showNo_encVideo_post(  pkts,  nPkts  );
								//
								if  (  pSharedObj->bSlave  )  {
									int  i;
									i  =  0;
								}
						   #endif
				   #endif

				   SHARED_OBJ_USR	*	pSharedObjUsr	=	getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
				   if  (  !pSharedObjUsr  )  {
					   #ifdef  __DEBUG__
							   traceLog((TCHAR*)  _T(  "mcThread_toShareBmp: pSharedObjUsr is null,  iIndex_sharedObj %d"  ),  iIndex_sharedObj  );
					   #endif
					   continue;
				   }

				   //
				   //  myDRAW_VIDEO_DATA  *  pPkt  =  pPkts[0];
				   //  

				   #if  1						
				   		//  if  (  nPkts  !=  1  )  
						{			
							DWORD	dwTickCnt	=	GetTickCount(  );
							for  (  i  =  0;  i  <  nPkts;  i  ++  )  {							
								 pkts[i].debugInfo.usPostInMs  =  dwTickCnt  -  pkts[i].debugInfo.dwTickCnt_start;							
							}

						#ifdef  __DEBUG__
							#if  0
								TCHAR	tBuf[128]	=	_T(  ""  );
								int  j  =  0;
								for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
									 //
									 char  buf[128];
									 iFourcc2Str(  pkts[i].bih.biCompression,  buf,  mycountof(  buf  )  );

									 //
									 TRANSFER_VIDEO_DATA	*	pReq  =  (  TRANSFER_VIDEO_DATA  *  )(  pkts[i].memory.m_pBuf  +  pkts[i].uiSize_dec  );
									 if  (  pReq->usCnt  )  {
										 j  +=  pReq->usCnt;
										 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s [%d].usCnt=%d"  ),  tBuf,  i,  (  int  )pReq->usCnt  );
									 }
								}
								if  (  j  )  {
									qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "postV: nPkts %d, total enc %d, %s "  ),  nPkts, j,  tBuf  );		
								}
							#endif
						#endif

						}
				   #endif

				   for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
					    pProcInfo->toShareVideo_post(  pCapProcInfo->uiType,  pSharedObj->iIndex_capBmp,  &pkts[i], 1,  &pCapProcInfo->compressVideo,  pSharedObj,  pMsgBuf  );				  				   
				   }

				   //  2014/09/23
				   BOOL  bNoDrawForSlave  =  TRUE;
				   #ifdef  __DEBUG__	//  for test							
						   #if  0
								bNoDrawForSlave  =  FALSE;
								traceLog((TCHAR*)  _T(  "For test: bNoDrawForSlave is false"  )  );
						   #endif
				   #endif
				   if  (  bNoDrawForSlave  )  {					
					   if  (  pSharedObj->bSlave  )  {			
						   continue;				   								   							
					   }
					   if  (  pSharedObj->usSubtype  ==  CONST_sharedObjSubtype_mosaic  )  {
						   continue;
					   }
				   }
				   
				   //  
				   BOOL		bPktRedirected  =  FALSE;
				   pProcInfo->drawLocalVideoData(  pSharedObjUsr->uiTranNo_openAvDev_v,  pkts,  nPkts  *  sizeof(  pkts[0]  ),  &bPktRedirected,  pCapProcInfo->uiType,  pSharedObj->iIndex_capBmp,  pSharedObjUsr->iTaskId,  NULL,  NULL  );							
				   if  (  bPktRedirected  )  {
						for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
							mallocObj_tmpPkts[i].detach(    );
						}
				   }

				   //
   				   #ifdef  __DEBUG__
						   if  (  !bPktRedirected  )  {
								M_pkts_showNo(  pkts,  nPkts,  _T(  "encVideo_post free"  )  );
						   }
				   #endif

			   }

			   continue;
		  }

		  continue;
	 }

	 traceLogA(  (char*)  "mcThreadProc_toShareBmp will quit"  );

errLabel:

	 //  2010/12/28
	 pCapProcInfo->compressVideo.debugInfo.nStep  =  199;

	 //
	 pCapProcInfo->postThread.bRunning  =  FALSE;

#if  0
	 if  (  bInited_tmpMemoryGrp  )  {
		 tmpiRet  =  freeTmpMemoryGrp(  &tmpMemoryGrp  );
		 MACRO_qyAssert(  !tmpiRet,  _T(  "mcThread_toShareBmp: freeTmpMemoryGrp failed"  )  );
	 }
#endif

	 traceLogA(  (char*)  "mcThreadProc_toShareBmp_post %S leaves",  pCapProcInfo->postThread.q2.cfg.name  );
	
	 return  0;

}
