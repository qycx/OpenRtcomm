

#include	"stdafx.h"
#include	<stdio.h>
#include	<stddef.h>
#include	<time.h>

#include	"qyMcMainCommon.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"

#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	<windows.h>
#include	<windef.h>
#include	<lmcons.h>
#ifndef  __WINCE__
	#include	<lmshare.h>
#endif
#include	<tlhelp32.h>
#include	<iphlpapi.h>
//  #include	"qwmDynFunc.h"

#include	"qmcCmdProc.h"

#include	"tmpCeLib.h"
#include	"qySqlFunc.h"
#include	"qmcCommFunc_isCli.h"
#include	"ctxMcThread.h"



 int  procMsgReq_mgr(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_REQ  *  pMsgReq,  unsigned  int  lenInBytes_msg,  CTX_MC_THREAD  *  pCtx  )
{
	 int						iErr		=	-1;
	 QY_MC					*	pQyMc		=	(  QY_MC  *  )pProcInfo->pQyMc;
	 QY_SERVICEGUI_INFO		*	pSci		=	(  QY_SERVICEGUI_INFO  *  )pProcInfo->pSgiParam;  
	 int						dataLen		=	0;
	 unsigned  int				uiMsgLen	=	offsetof(  MIS_MSG_REQ,  data  );
	 TCHAR						tBuf[1024]	=	_T(  ""  );
	 IM_CONTENTU		*	pContent	=	(  IM_CONTENTU  *  )&pMsgReq->data;
	 int						lenInBytes	=	0;
	 
	 if  (  !pCtx  )  {
		 traceLogA(  (char*)  "procMsgReq_mgr failed: pCtx is null"  );
		 return  -1;
	 }

	 //  CQyMalloc					mallocObj;
	 MIS_MSG_REQ			*	pMsg		=	(  MIS_MSG_REQ  *  )pCtx->pMsgBuf_forInput;	//  mallocObj.malloc(  sizeof(  MIS_MSG_REQ  )  );
	 if  (  !pMsg  )  return  -1;
	 MIS_CHANNEL		*	pChannel	=	NULL;
	 

	 //  traceLogA(  (char*)  "procMsgReq_mgr£º·¢ËÍÖ®Ç°Ó¦¸Ã´¦ÀíÊý¾Ý£¬±ÈÈç£º×ª»»Êý¾Ý×Ö½ÚË³ÐòµÈ: ´¦ÀíÇëÇó %S ",  qyGetDesByType1(  CONST_qyCmdTable,  pMsg->usCode  )  );

	 memcpy(  pMsg,  pMsgReq,  offsetof(  MIS_MSG_REQ,  data  )  );
	 lenInBytes  =  sizeof(  pMsg->data  );	

	 switch  (  pMsgReq->usCode  )  {
			 case  CONST_qyCmd_refreshImObjListReq:
				   //				   
				   if  (  (  dataLen  =  qyhtonImContentU(  0,  (  IM_CONTENTU  *  )&pMsgReq->data  )  )  <  0  )  goto  errLabel;
				   break;
			 case  CONST_qyCmd_refreshRecentFriendsReq:	
				   switch  (  pContent->uiType  )  {
						   case  CONST_imCommType_refreshWebContactsInfo:
							   	 if  (  qyhtonRouteTalkData(  NULL,  (  char  *  )&pMsgReq->data,  0,  TRUE,  pMsgReq->ucFlg,  (  char  *  )&pMsg->data,  (  unsigned  int  *  )&lenInBytes,  NULL,  0  )  )  goto  errLabel;
								 pMsg->lenInBytes  =  lenInBytes;
								 lenInBytes  +=  offsetof(  MIS_MSG_REQ,  data  );		
								 //
								 dataLen  =  pMsg->lenInBytes;	//  ÕâÊÇÎªÁË¼æÈÝÐÔ¡£µÈ¹ýÒ»Õó£¬½«ÉÏÃæºÍÏÂÃæµÄ¼¯³ÉÆðÀ´¡£2007/12/22
								 pMsgReq  =  pMsg;
							     break;
						   case  CONST_imCommType_refreshRecentFriendsReq:  
							   
							     #ifdef  __DEBUG__
							     {	
										 REFRESH_RECENTFRIENDS_REQ_h	*	p  =  (  REFRESH_RECENTFRIENDS_REQ_h  *  )&pMsgReq->data;
										 int								i;
										 //
										 _sntprintf(  tBuf,  mycountof(  tBuf  ),_T(  "uiType is %d, tLast is %I64u, usCnt is %d"  ),  p->uiType,  p->tLastRefreshedTime_misServ,  p->usCnt  );
										 for  (  i  =  0;  i  <  p->usCnt;  i  ++  )  {
											  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s,µÚ[%d]¸ö,id %I64u, t %I64u"  ),  tBuf,  i,  p->mems[i].idInfo.ui64Id,  p->mems[i].tLastRefreshedTime_misServ  );
						   				 }
						   				 //
						   				 qyShowInfo1(  CONST_qyShowType_debug,  0, (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  ""  )  );
						   				 qyShowInfo1(  CONST_qyShowType_debug,  0, (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tn %d,  %s"  ),  pMsgReq->uiTranNo,  tBuf  );
										 //
										 if  (  p->usCnt  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "usCnt %d, tn %d"  ),  p->usCnt,  pMsgReq->uiTranNo  );
								 }
								 #endif
				   
								 //
								 {
									 AT_REFRESH_RECENTFRIENDS_REQ_n  tmp_n;
									 memset(&tmp_n, 0, sizeof(tmp_n));
									 if ((dataLen = qyhtonRefreshRecentFriendsReq(0, (REFRESH_RECENTFRIENDS_REQ_h*)&pMsgReq->data,&tmp_n)) < 0)  goto  errLabel;
									 memcpy(&pMsgReq->data, &tmp_n, dataLen);
								 }
								 break;
						   default:
								   break;
				   }
				   break;
			 case  CONST_qyCmd_sendVDevReq:
				   if  (  qyhtonRouteTalkData(  NULL,  (  char  *  )&pMsgReq->data,  0,  TRUE,  pMsgReq->ucFlg,  (  char  *  )&pMsg->data,  (  unsigned  int  *  )&lenInBytes,  NULL,  0  )  )  goto  errLabel;
				   pMsg->lenInBytes  =  lenInBytes;
				   lenInBytes  +=  offsetof(  MIS_MSG_REQ,  data  );		
				   //
				   dataLen  =  pMsg->lenInBytes;	//  2007/12/22
				   pMsgReq  =  pMsg;
				   break;
			 case  CONST_qyCmd_getCfgs:
			 default:
				   //
				   #ifdef  __DEBUG__
						   if  (  pMsgReq->usCode  ==  CONST_qyCmd_sendReq  )  {
							   int  ii  =  0;
						   }
				   #endif
				   //
				   switch  (  pContent->uiType  )  {
					       case  0:  
							      //  
							      break;
						   case  CONST_imCommType_getCfgsReq:
						   case  CONST_imCommType_retrieveToPaths:							     
						   default:
							      if  (  qyhtonRouteTalkData(  NULL,  (  char  *  )&pMsgReq->data,  0,  TRUE,  pMsgReq->ucFlg,  (  char  *  )&pMsg->data,  (  unsigned  int  *  )&lenInBytes,  NULL,  0  )  )  goto  errLabel;
								  pMsg->lenInBytes  =  lenInBytes;
								  lenInBytes  +=  offsetof(  MIS_MSG_REQ,  data  );		
								  //
								  dataLen  =  pMsg->lenInBytes;	//  2007/12/22
								  pMsgReq  =  pMsg;
								  //
								  //  traceLogA(  (char*)  "procMsgReq_mgr:  CONST_qyCmd_getCfgs:  contentType is %d",  pContent->uiType  );
								  break;
				   }
				   break;
					
	 }

	 pMsgReq->lenInBytes  =  dataLen;
	 //
	 uiMsgLen  +=  dataLen;
				   

	 if  (  !pMsgReq->pMisCnt  )  {
		 traceLogA(  (char*)  "procMsgReq_mgr error: pMisCnt is null"  );  goto  errLabel;
	 }
	 if  (  !(  pChannel  =  getChannelByType(  (  MIS_CNT  *  )pMsgReq->pMisCnt,  CONST_channelType_talking  )  )  )  goto  errLabel;

	 if  (  postMsg2OutputQ_mc(  (  MIS_CNT  *  )pMsgReq->pMisCnt,  (  MIS_MSGU  *  )pMsgReq,  uiMsgLen,  pChannel  )  )  {
		 //  qyShowInfo1(  CONST_qyShowType_debugWarning,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  ""  )  );
		 traceLogA(  (char*)  "postMsg2OutputQ_mc failed"  );
		 goto  errLabel;
	 }

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
	 }

	 return  iErr;
}


 //  lenInBytes
 int  procMsgTalk_mc_mgr(  QY_MC  *  pQyMc,  QY_SERVICEGUI_INFO  *  pSci,  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSG_TALK  *  pMsgTalk,  unsigned  int  lenInBytes_msg,  CTX_MC_THREAD  *  pCtx  )
{
	 int					iErr				=	-1;
	 int					dataLen				=	0;
	 //  unsigned  int		uiMsgLen			=	offsetof(  MIS_MSG_TALK,  data  )  +  offsetof(  MIS_MSG_TALKDATA,  buf  );
	 int					lenInBytes;
	 //  unsigned  int			uiChannelType		=	CONST_channelType_talking;
	 if  (  !pMisCnt  )  return  -1;
	 MIS_CHANNEL		*	pChannel			=	getChannelByType(  pMisCnt,  CONST_channelType_talking  );
	 if  (  !pChannel  )  return  -1;
	 CQyMalloc				mallocObj;
	 MIS_MSG_TALK		*	pMsg				=	(  MIS_MSG_TALK  *  )mallocObj.mallocf(  sizeof(  MIS_MSG_TALK  )  );
	 if  (  !pMsg  )  return  -1;
	 IM_CONTENTU	*	pContent			=	NULL;

	 traceLogA(  (char*)  "procMsgTalk_mc_mgr:  "  );
	 
	 //  idInfo_to.ui64IdÎª0±íÊ¾Ö±½Ó´Ó±¾»úµÄ¶ÌÐÅÄ£¿é·¢ËÍ
	 if  (  !pMsgTalk->data.route.idInfo_to.ui64Id  )  {
		 switch  (  pMsgTalk->data.route.uiDevType_to  )  {
				 case  0:
					   qPostMsgAndTrigger(  pMsgTalk,  lenInBytes_msg,  &pProcInfo->workQ,  _T(  "procmsgTalk_mc_mgr"  ));
					   break;
				 case  CONST_objType_dev:
					   pContent  =  (  IM_CONTENTU  *  )pMsgTalk->data.buf;
					   if  (  pContent->uiType  ==  CONST_imCommType_htmlContent  )  {
						#if  0	//  2014/09/29
						   myVDev_postStr2Dev(  NULL,  0,  0,  0,  pContent->html.wBuf,  pMsgTalk->data.route.uiDevType_to,  pMsgTalk->data.route.wDevIdStr_to,  pMsgTalk->data.route.wForwardPath,  NULL,  0  );
						#endif
					   }
					   break;
				 default:
						break;
		 }
		 //
		 iErr  =  0;  goto  errLabel;
	 }

	 //  ÔÚ·¢Íù·þÎñÆ÷Ê±£¬Ó¦½«idInfo_fromÒ²Éè³É×Ô¼ºµÄÖµ, 2008/02/16
	 if  (  !pMsgTalk->data.route.idInfo_from.ui64Id  )  {
		 pMsgTalk->data.route.idInfo_from.ui64Id  =  pMisCnt->idInfo.ui64Id;
	 }

	 
	 switch  (  pMsgTalk->usCode  )  {
			 case  CONST_qyCmd_talkTo:
			 case  CONST_qyCmd_sendTask:
				   break;
			 case  CONST_qyCmd_sendTaskReply:
				   if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  CONST_channelType_robot  )  )  )  goto  errLabel;
				   break;
			 default:
					traceLogA(  (char*)  "procMsgTalk_mgr: Î´´¦ÀíµÄmsg, %S",  qyGetDesByType1(  CONST_qyCmdTable,  pMsgTalk->usCode  )  );
					goto  errLabel;
	 }


	 memcpy(  pMsg,  pMsgTalk,  offsetof(  MIS_MSG_TALK,  data  )  );
	 lenInBytes  =  sizeof(  pMsg->data  );	
	 if  (  qyhtonRouteTalkData(  &pMsgTalk->data.route,  pMsgTalk->data.buf,  0,  TRUE,  pMsgTalk->ucFlg,  (  char  *  )&pMsg->data,  (  unsigned  int  *  )&lenInBytes,  NULL,  0  )  )  goto  errLabel;
	 pMsg->lenInBytes  =  lenInBytes;
	 lenInBytes  +=  offsetof(  MIS_MSG_TALK,  data  );

	 if  (  postMsg2OutputQ_mc(  pMisCnt,  (  MIS_MSGU  *  )pMsg,  lenInBytes,  pChannel  )  )  {
		 //  qyShowInfo1(  CONST_qyShowType_debugWarning,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "·ÅÈë·¢ËÍ¶ÓÁÐÊ§°Ü"  )  );
		 traceLogA(  (char*)  "postMsg2OutputQ_mc failed"  );
		 goto  errLabel;
	 }

	 iErr  =  0;

errLabel:

	 return  iErr;
}


 extern "C" DWORD WINAPI mcThreadProc_mis_mgr( LPVOID lpParameter )
{
	 int							iErr				=	-1;
	 QY_MC						*	pQyMc				=	QY_GET_GBUF(  );
	 QY_SERVICEGUI_INFO			*	pSci				=	(  QY_SERVICEGUI_INFO  *  )lpParameter;
	 MC_VAR_isCli					*	pProcInfo			=	(  MC_VAR_isCli  *  )pSci->pVar;
	 int							loopCtrl			=	0;
	 DWORD							dwThreadId			=	GetCurrentThreadId(  );
	 CQyMalloc						mallocObj;
	 MIS_MSGU					*	pMsg				=	NULL;
	 unsigned  int					len;
	 DWORD							dwRet;
	 //  long							lPrev;
	 CTX_MC_THREAD					ctx;
	 CQyMalloc						mallocObj_pMsgBuf_forInput;
	 //
	 unsigned  int					uiChannelType		=	CONST_channelType_talking;
	 
#ifdef  __DEBUG__
	 traceLogA(  (char*)  "mcThreadProc_mis_mgr:  enters"  );
#endif

	 //
	 memset(  &ctx,  0,  sizeof(  ctx  )  );
	 ctx.pProcessQ  =  &pProcInfo->processQ_media;  //  2015/09/06
	 ctx.pMsgBuf_forInput  =  (  MIS_MSGU  *  )mallocObj_pMsgBuf_forInput.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  );
	 if  (  !ctx.pMsgBuf_forInput  )  goto  errLabel;

	 if  (  !(  pMsg  =  (  MIS_MSGU  *  )mallocObj.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  )  )  )  goto  errLabel;


	 //
	 for  (  ;  !pQyMc->bQuit;  loopCtrl  ++  )  {
		 if (!pQyMc->bLogon) {
			 break;
		 }

		  dwRet  =  WaitForSingleObject(  pProcInfo->mgrQ.hEvent,  3500  );
		  if  (  dwRet  ==  WAIT_FAILED  )  {
			  goto  errLabel;
		  }
		  
		  for  (  ;  !pQyMc->bQuit;  )  {
			   len  =  sizeof(  pMsg[0]  );
			   if  (  qGetMsg(  &pProcInfo->mgrQ,  pMsg,  &len  )  )  break;
			   memset(  (  (  char  *  )pMsg  )  +  len,  0,  min(  256,  sizeof(  pMsg[0]  )  -  len  )  );
			   switch  (  pMsg->uiType  )  {
					   case  CONST_misMsgType_input:  {						   		
						   	 MIS_CNT					*	pMisCnt				=	NULL;
							 MIS_CHANNEL				*	pChannel			=	NULL;

						     pMisCnt  =  (  MIS_CNT  *  )pMsg->input.pMisCnt;
						     if  (  !pMisCnt  )  {
								 #ifdef  __DEBUG__
										 traceLogA(  (char*)  "mcThreadProc_mis_mgr: ÊÕµ½ÁËÒ»¸ö´íÎóµÄinput°ü£ºpMisCnt is null" );
								 #endif
							     break;						   
							 }
							 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  break;

							 if  (  isUcFlgResp(  pMsg->input.ucFlg  )  )  {
								 if  (  procMsgInput_mgr_resp(  pQyMc,  pSci,  pProcInfo,  &pMsg->input,  len,  &ctx,  pChannel  )  )  break;							 
								}
							 else  {
								   if  (  procMsgInput_mgr_req(  pQyMc,  pSci,  pProcInfo,  &pMsg->input,  len,  &ctx,  pChannel  )  )  break;							 								
							 }

							 //
							 /*
							 if  (  !ReleaseSemaphore(  pChannel->hSemaTrigger_input,  1,  &lPrev  )  )  {
								 traceLogA(  (char*)  "mcThreadProc_mis_mgr . ÕâÀï´íà¶,´¥·¢½ÓÊÕ³ö´íà¶£¬ReleaseSemaphore failed"  );  
							 }
							 */
							 }
							 break;
					   case  CONST_misMsgType_req:

						     if  (  !pMsg->req.pMisCnt  )  {
								 traceLogA(  (char*)  "mcThreadProc_mis_mgr: req pMisCnt is null" );
							     break;						   
							 }

							 if  (  procMsgReq_mgr(  pProcInfo,  &pMsg->req,  len,  &ctx  )  )  break;

						     break;
					   case  CONST_misMsgType_talk:

						     if  (  !pMsg->talk.pMisCnt  )  {
								 traceLogA(  (char*)  "mcThreadProc_mis_mgr: talk pMisCnt is null" );
							     break;						   
							 }

						     if  (  procMsgTalk_mc_mgr(  pQyMc,  pSci,  pProcInfo,  (  MIS_CNT  *  )pMsg->talk.pMisCnt,  &pMsg->talk,  len,  &ctx  )  )  break;

						     break;
					   case  CONST_misMsgType_task:  {
						     MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMsg->task.pMisCnt;
							 MIS_CHANNEL	*	pChannel;

						     if  (  !pMisCnt  )  {
								 #ifdef  __DEBUG__
										 traceLogA(  (char*)  "mcThreadProc_mis_mgr: MisCnt is null" );
								 #endif
								 break;
							 }
							 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  break;


							 //  if  (  procMsgTask2Output_mc(  pProcInfo,  (  MIS_CNT  *  )pMsg->task.pMisCnt,  &pMsg->task,  len,  pChannel,  _T(  "thread_mgr"  )  )  )  break;
							 if  (  procMsgTask_mc_mgr(  pQyMc,  pSci,  pProcInfo,  &pMsg->task,  len,  FALSE,  &ctx,  pChannel  )  )  break;

													 
							 }
						     break;

							 /*
					   case  CONST_misMsgType_applyForRemovingInvalidTasks_qmc:		//  2009/09/10
						     //
						     qmcRemoveInvalidTasks(  pProcInfo  );
						     break;
							 */

					   default:
								#ifdef  __DEBUG__
										traceLogA(  (char*)  "µÃµ½Î´´¦ÀíµÄÏûÏ¢: %S",  qyGetDesByType1(  CONST_misMsgTypeTable,  pMsg->uiType  )  );
								#endif
								break;
			   }
		
			   //  dwRet  =  WaitForSingleObject(  pProcInfo->mgrQ.hSemaTrigger,  50  );
			   //  if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;			   
		  }

	
		  //  if  (  !(  loopCtrl  %  20  )  )  traceLogA(  (char*)  "ÕâÀï»¹Ó¦¸ÃÓÐÒ»¸ö¶¨ÆÚ£¨±ÈÈç30·ÖÖÓÒ»´ÎµÄ£¬ÇåÀíprocessQµÄ¹¤×÷£¬ÒÔ·ÀÖ¹processQÀïÓÐµÄ½ÚµãÊ§È¥±»´¦ÀíµÄ¿ÉÄÜµÄ¡£¾ÍÒª°ÑÕâÐ©À¬»ø½ÚµãÇåµô"  );


	 }

	 iErr  =  0;
	 
errLabel:

	 //
	 showInfo_open0(  0,  0,  _T(  "thread_mgr: start to empty taskQ"  )  );

	 //
	 /*
	 if  (  ctx.pProcessQ  )  {
		 ctx.pProcessQ->emptyQ(  );
	 }
	 */

	 //
	 showInfo_open0(  0,  0,  _T(  "thread_mgr: taskQ is empty"  )  );

	 //
	 pProcInfo->status.threadsStatus.ulbMgrQuit  =  TRUE;

	 traceLogA(  (char*)  "msgThreadProc_mis_mgr:  leaves"  );

	 return  iErr;
}


