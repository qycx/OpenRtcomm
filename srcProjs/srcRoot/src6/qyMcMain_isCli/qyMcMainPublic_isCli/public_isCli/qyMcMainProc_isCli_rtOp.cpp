
#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qyPlaySound_wave.h"
//  #include	"QyRecordSound_wave.h"
#include	"module_qisCamCap.h"

#include	"mmDeviceProc.h"
#include	"qmcCommFunc_isCli.h"
#include	"ctxMcThread.h"





 extern "C" DWORD WINAPI mcThreadProc_mis_rtOp( LPVOID lpParameter )
{
	 QY_SERVICEGUI_INFO			*		pSci							=	(  QY_SERVICEGUI_INFO  *  )lpParameter;
	 if  (  !pSci  )  return  -1;
	 MC_VAR_isCli				*		pProcInfo						=	(  MC_VAR_isCli  *  )pSci->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 QY_MC						*		pQyMc							=	pProcInfo->pQyMc;
	 
	 int								loopCtrl						=	0;
	 int								i;
	 DWORD								dwThreadId						=	GetCurrentThreadId(  );
	 CQyMalloc							mallocObj;
	 MIS_MSGU					*		pMsg							=	NULL;
	 unsigned  int						len;
	 DWORD								dwRet;
	 //  long								lPrev;
	 //
	 CTX_MC_THREAD						ctx;
	 CQyMalloc							mallocObj_pMsgInputBuf;
	 CQyMalloc							mallocObj_pMsgBuf;
	 //
	 //  CWnd						*		pMainWnd						=	AfxGetApp(  )->m_pMainWnd;
	 //
	 QY_Q2						*		pTriggerQ						=	&pProcInfo->rtOpQ2;
	 unsigned  int						uiChannelType					=	CONST_channelType_rtOp;
	 //
	 
#ifdef  __DEBUG__
	 traceLogA(  (char*)  "mcThreadProc_mis_rtOp:  enters"  );
#endif

	 //
	 memset(  &ctx,  0,  sizeof(  ctx  )  );
	 ctx.pProcessQ  =  &pProcInfo->processQ_media;
	 ctx.pMsgBuf_forInput  =  (  MIS_MSGU  *  )mallocObj_pMsgInputBuf.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  );
	 if  (  !ctx.pMsgBuf_forInput  )  goto  errLabel;
	 ctx.pMsgBuf  =  (  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  );
	 if  (  !ctx.pMsgBuf  )  goto  errLabel;
	 	 
	 if  (  !(  pMsg  =  (  MIS_MSGU  *  )mallocObj.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  )  )  )  goto  errLabel;

	 for  (  ;  !pQyMc->bQuit;  loopCtrl  ++  )  {

		 if (!pQyMc->bLogon) {
			 break;
		 }

		  //  if  (  !pMainWnd  )  pMainWnd					=	AfxGetApp(  )->m_pMainWnd;
		  if  (  !pQyMc->gui.hMainWnd  )  {
			  Sleep(  1000  );  continue;
		  }

		  dwRet  =  WaitForSingleObject(  pTriggerQ->hEvents[0],  5000  );
		  if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
		  
		  for  (  ;  !pQyMc->bQuit;  )  {
			   len  =  sizeof(  pMsg[0]  );
#if  0
			   {
				   CQyQ2Help	q2Help;
				   if  (  qGetMsg(  q2Help.getQ_toGetMsg(  pTriggerQ  ),  pMsg,  &len  )  )  break;
			   }
#endif			//  2014/04/10
			   if  (  q2GetMsg(  pTriggerQ,  pMsg,  &len,  _T(  "mcThreadProc_mis_rtOp"  )))  break;

			   memset(  (  (  char  *  )pMsg  )  +  len,  0,  min(  256,  sizeof(  pMsg[0]  )  -  len  )  );			   

			   switch  (  pMsg->uiType  )  {
					   case  CONST_misMsgType_input:  {
						     MIS_CNT					*		pMisCnt							=  (  MIS_CNT  *  )pMsg->input.pMisCnt;
							 MIS_CHANNEL				*		pChannel						=	NULL;

							 if  (  !pMisCnt  )  break;
							 //  if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  pMsg->input.uiChannelType  )  )  )  break;
							 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  break;

							 if  (  isUcFlgResp(  pMsg->input.ucFlg  )  )  {
								 if  (  procMsgInput_other_resp(  pQyMc,  pSci,  pProcInfo,  &pMsg->input,  len,  &ctx,  pChannel  )  )  {
									 //  traceLogA(  (char*)  "mcThreadProc_mis_realTimeMedia: procMsgInput_other_resp failed."  );
								 }
								}
							 else  {
								 if  (  procMsgInput_other_req(  pQyMc,  pSci,  pProcInfo,  &pMsg->input,  len,  &ctx,  pChannel  )  )  {
									 //  traceLogA(  (char*)  "mcThreadProc_mis_realTimeMedia: procMsgInput_other_req failed."  );
								 }
							 }							 

							 //
							 }							 
						     break;
					   case  CONST_misMsgType_talk:  
							 #ifdef  __DEBUG__
									 traceLogA(  (char*)  "mcThreadProc_mis_realTimeMedia: msg_talk not finished"  );
							 #endif
						     break;
					   case  CONST_misMsgType_task:  {
						     MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMsg->task.pMisCnt;
							 MIS_CHANNEL				*		pChannel						=	NULL;

							 if  (  !pMisCnt  )  break;
							 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  break;

							 if  (  procMsgTask_mc_media(  pQyMc,  pSci,  pProcInfo,  &pMsg->task,  len,  FALSE,  &ctx,  pChannel  )  )  break;

							 //  printMisMsg(  0,  0,  pMsg  );

							 }
						     break;
					   case  CONST_misMsgType_applyForChkChannels_qmc:  {
						     MIS_CNT	*	pMisCnt		=	(  MIS_CNT  *  )pMsg->applyForChkChannels_qmc.pMisCnt;
							 if  (  !pMisCnt  )  break;
							 
							 #ifdef  __DEBUG__
									 traceLog((TCHAR*)  _T(  "rtMedia: applyForChkChannels"  )  );
							 #endif
							 startChannel(  pProcInfo,  pMisCnt,  getChannelByType(  pMisCnt,  uiChannelType  ),  _T(  "rtMedia: applyForChannels"  )  );  		

							 }						     
						     break;

					   case  CONST_misMsgType_outputTask:  
						     /*
							 {
						     MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMsg->task.pMisCnt;
							 MIS_CHANNEL				*		pChannel						=	NULL;

						     if  (  !pMisCnt  )  break;
							 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  pMsg->task.uiChannelType  )  )  )  break;

							 if  (  procMsgTask2Output_mc(  pQyMc,  pSci,  pProcInfo,  pMisCnt,  &pMsg->task,  len,  pChannel  )  )  break;
							 }
						     break;
							 */
					   default:
								traceLogA(  (char*)  "mcThreadProc_mis_realTimeMedia failed, 未处理的消息类型%d",  pMsg->uiType  );
								break;
			   }
		
			   //  dwRet  =  WaitForSingleObject(  pTriggerQ->hSemaTrigger,  50  );
			   //  if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;			   
		  }


		  if  (  !(  loopCtrl  %  5  )  )  {

			  //  for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
			  for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
			  {
				   MIS_CNT  *  pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  i  );  //&pProcInfo->misCnts[i]; 
				   if  (  !pMisCnt  )  continue;
				   //
				   if  (  !pMisCnt->cfg.dynCfg.cnt.usCntPort  )  continue;

				   waitForChannel(  pProcInfo,  pMisCnt,  uiChannelType,  FALSE  );
			  }
		  }
	 }


errLabel:

	 //for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
	 for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
	 {
		  MIS_CNT  *  pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  i  );  //&pProcInfo->misCnts[i]; 
		  if  (  !pMisCnt  )  continue;
		  //
		  if  (  !pMisCnt->cfg.dynCfg.cnt.usCntPort  )  continue;

		  waitForChannel(  pProcInfo,  pMisCnt,  uiChannelType,  TRUE  );
	 }


	 // 
	 //  pProcInfo->processQ_media.emptyQ(  );
	 
	 pProcInfo->status.threadsStatus.ulbRtOpQuit  =  TRUE;

#ifdef  __DEBUG__
		traceLogA(  (char*)  "mcThreadProc_mis_realTimeMedia:  leaves"  );
#endif

	 return  0;
}
