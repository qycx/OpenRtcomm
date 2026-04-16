

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
//
#include	"ctxMcThread.h"


//
int  procMsgTask_mc_media_mgr(  void  *  pQyMcParam,  void  *  pSciParam,  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_TASK  *  pMsg,  unsigned  int  lenInBytes_msg,  BOOL  bMsgInput,  CTX_MC_THREAD  *  pCtx,  MIS_CHANNEL  *  pChannel  );
int  procMsgTask_mc_robot_mgr(  void  *  pQyMcParam,  void  *  pSciParam,  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_TASK  *  pMsg,  unsigned  int  lenInBytes_msg,  BOOL  bMsgInput,  CTX_MC_THREAD  *  pCtx,  MIS_CHANNEL  *  pChannel  );


//
 int  procMsgTask_mc_mgr(  void  *  pQyMcParam,  void  *  pSciParam,  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_TASK  *  pMsg,  unsigned  int  lenInBytes_msg,  BOOL  bMsgInput,  void  *  pCTX_MC_THREAD,  MIS_CHANNEL  *  pChannel  )
 {
	 int					iErr				=	-1;
	 QY_MC				*	pQyMc				=	(  QY_MC  *  )pQyMcParam;
	 QY_SERVICEGUI_INFO	*	pSci				=	(  QY_SERVICEGUI_INFO  *  )pSciParam;
	 //
	 CTX_MC_THREAD  *  pCtx  =  (  CTX_MC_THREAD  *  )pCTX_MC_THREAD;
	 //
	 int					dataLen				=	0;
	 unsigned  int			uiMsgLen			=	offsetof(  MIS_MSG_TASK,  data  )  +  offsetof(  MIS_MSG_routeTalkData,  buf  );
	 IM_CONTENTU		*	pContent			=	(  IM_CONTENTU  *  )pMsg->data.buf;
	 //  CWnd				*	pMainWnd			=	AfxGetApp(  )->m_pMainWnd;
	 MIS_CNT			*	pMisCnt				=	(  MIS_CNT  *  )pMsg->pMisCnt;
     
	 //  IM_TASK_RCD			rcd;
	 int					tmpiRet;
	 //
	 int					lenInBytes			=	0;
	 IM_SIMPLE_RESP			respSimple;
	 unsigned  short		usRespCode			=	CONST_qyRc_unknown;	
	 unsigned  int			uiChannelType		=	CONST_channelType_talking;
	 char					timeBuf[CONST_qyTimeLen  +  1]	=	"";
	 //
	 BOOL					bRemoveIfErr		=	TRUE;		//  ÔÚÔËÐÐ³ö´íÊ±ÊÇ·ñÉ¾³ýÏà¹Ø½Úµã¡£
	 //
	 //  TCHAR					sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;
		
	//  2015/09/06
#ifdef  __DEBUG__
#if  0
		traceLog((TCHAR*)  _T(  "Not finished: procMsgTask_mc_mgr."  )  );
	    return  procMsgTask2Output_mc(  pProcInfo,  (  MIS_CNT  *  )pMsg->pMisCnt,  pMsg,  lenInBytes_msg,  pChannel,  _T(  "thread_mgr"  )  );
#endif
#endif



	//
	 if  (  !pQyMc->gui.hMainWnd  )  return  -1;
	 if  (  !pMisCnt  )  return  -1;

	 //  memset(  &rcd,  0, sizeof(  rcd  )  );

	 //  2014/11/22
#ifdef  __DEBUG__
	    int  i;
		switch  (  pContent->uiType  )  {
				case  CONST_imCommType_transferAvInfo:  
					  i  =  0;
					  break;
				case  CONST_imCommType_transferAvReplyInfo:
					  i  =  0;
					  break;
				default:
						break;	 
		}
#endif


	 if  (  !pMsg->addr_logicalPeer.idInfo.ui64Id  )  {	//  Ç°ÃæÃ»ÓÐ¸³ÖµµÄ¶¼ÊÇÊÕµ½µÄÏûÏ¢
		 if  (  getIdInfo_logicalPeer(  pSci,  pMisCnt,  &pMsg->data.route,  &pMsg->addr_logicalPeer  )  )  {
			 switch  (  pMsg->uiTaskType  )  {
					 case  CONST_imTaskType_shareDynBmp:
					 case  CONST_imTaskType_shareGps:
						   break;
					 default:  {
							 #ifdef  __DEBUG__
								     traceLogA(  (char*)  "procMsgTask_mc_media: getIdInfo_logicalPeer failed."  );  
							 #endif
							 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "procMsgTask_mc_mgr: getIdInfo_logicalPeer failed."  )  );
							 goto  errLabel;							 
							 }
							 break;
			 }
	 	 }		 
	 }
	 

	 if  (  !isUcFlgResp(  pMsg->ucFlg  )  )  {

		 //
		 switch  (  pMsg->usCode  )  {
				 case  CONST_qyCmd_sendMedia:  {		//  
			 		   //
					   if  (  procMsgTask_mc_media_mgr(  pQyMcParam,  pSciParam,  pProcInfo,  pMsg,  lenInBytes_msg,  bMsgInput,  pCtx,  pChannel  )  )  {
						   goto  errLabel;			 
					   }
					   			 
					   //
					   iErr  =  0;  goto  errLabel;
					   }
					   break;				 
			
				 case  CONST_qyCmd_sendRobotTask:
				 case  CONST_qyCmd_sendRobotTaskReply:  
				 case  CONST_qyCmd_sendRobotTaskData:  {
			 		   //
					   if  (  procMsgTask_mc_robot_mgr(  pQyMcParam,  pSciParam,  pProcInfo,  pMsg,  lenInBytes_msg,  bMsgInput,  pCtx,  pChannel  )  )  {
						   goto  errLabel;			 
					   }					   			 
					   //
					   iErr  =  0;  goto  errLabel;

					   }
					   break;					  

				 default:
						 break;
		 }




		 //  2015/09/07
		 if  (  !bMsgInput  )  {
			 
			 if  (  procMsgTask2Output_mc(  pProcInfo,  (  MIS_CNT  *  )pMsg->pMisCnt,  pMsg,  lenInBytes_msg,  pChannel,  _T(  "thread_mgr"  )  )  )  {
				 goto  errLabel;
			 }

			 iErr  =  0;  goto  errLabel;

		 }

		 
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "procMsgTask_mc_mgr failed:  kkkkkkkkk"  );  
		 #endif
		 goto  errLabel;
	 
	 
		}
	 else  {

		   if  (  !bMsgInput  )  {

			   if  (  procMsgTask2Output_mc(  pProcInfo,  (  MIS_CNT  *  )pMsg->pMisCnt,  pMsg,  lenInBytes_msg,  pChannel,  _T(  "thread_mgr"  )  )  )  {
				   goto  errLabel;
			   }

			   iErr  =  0;  goto  errLabel;
		   }

		   //
		   printMisMsg(  0,  0,  (  MIS_MSGU  *  )pMsg  );

		   #ifdef  __DEBUG__
				   qyShowInfo1(  CONST_qyShowType_debug,  0, (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "%I64u¦%s"  ),  pMsg->data.route.idInfo_from.ui64Id,  qyGetDesByType1(  CONST_qyRcTable,  pMsg->usCode  )  );
		   #endif

		   if  (  !isRcOk(  pMsg->usCode  )  )  goto  errLabel;

		   #ifdef  __DEBUG__
				   traceLogA(  (char*)  "procMsgTask_mc_media:  "  );
		   #endif

		   //
	 }

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		#if  0	//  2011/10/28, 出错就清理队列，容易导致功能不稳定
		 if  (  pCtx->pProcessQ  )  {
			 if  (  bRemoveIfErr  )  pCtx->pProcessQ->qRemoveMsg(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  );
		 }
		#endif
	 }

	 return  iErr;
}


//
 int  procMsgTask_mc_media_mgr(  void  *  pQyMcParam,  void  *  pSciParam,  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_TASK  *  pMsg,  unsigned  int  lenInBytes_msg,  BOOL  bMsgInput,  CTX_MC_THREAD  *  pCtx,  MIS_CHANNEL  *  pChannel  )
 {
	 int					iErr				=	-1;
	 QY_MC				*	pQyMc				=	(  QY_MC  *  )pQyMcParam;
	 QY_SERVICEGUI_INFO	*	pSci				=	(  QY_SERVICEGUI_INFO  *  )pSciParam;
	 //
	 int					dataLen				=	0;
	 unsigned  int			uiMsgLen			=	offsetof(  MIS_MSG_TASK,  data  )  +  offsetof(  MIS_MSG_routeTalkData,  buf  );
	 IM_CONTENTU		*	pContent			=	(  IM_CONTENTU  *  )pMsg->data.buf;
	 //  CWnd				*	pMainWnd			=	AfxGetApp(  )->m_pMainWnd;
	 MIS_CNT			*	pMisCnt				=	(  MIS_CNT  *  )pMsg->pMisCnt;
     
	 //  IM_TASK_RCD			rcd;
	 int					tmpiRet;
	 //
	 int					lenInBytes			=	0;
	 IM_SIMPLE_RESP			respSimple;
	 unsigned  short		usRespCode			=	CONST_qyRc_unknown;	
	 unsigned  int			uiChannelType		=	CONST_channelType_talking;
	 char					timeBuf[CONST_qyTimeLen  +  1]	=	"";
	 //
	 BOOL					bRemoveIfErr		=	TRUE;		//  ÔÚÔËÐÐ³ö´íÊ±ÊÇ·ñÉ¾³ýÏà¹Ø½Úµã¡£
	 //
	 //  TCHAR					sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;
		
	//  2015/09/06
#ifdef  __DEBUG__
#if  0
		traceLog((TCHAR*)  _T(  "Not finished: procMsgTask_mc_mgr."  )  );
	    return  procMsgTask2Output_mc(  pProcInfo,  (  MIS_CNT  *  )pMsg->pMisCnt,  pMsg,  lenInBytes_msg,  pChannel,  _T(  "thread_mgr"  )  );
#endif
#endif



	//
	 if  (  !pQyMc->gui.hMainWnd  )  return  -1;
	 if  (  !pMisCnt  )  return  -1;

	 //  memset(  &rcd,  0, sizeof(  rcd  )  );

	 //  2014/11/22
#ifdef  __DEBUG__
	    if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
			int  i;
			i  =  0;
	 
		}
#endif


	 if  (  !pMsg->addr_logicalPeer.idInfo.ui64Id  )  {	//  Ç°ÃæÃ»ÓÐ¸³ÖµµÄ¶¼ÊÇÊÕµ½µÄÏûÏ¢
		 if  (  getIdInfo_logicalPeer(  pSci,  pMisCnt,  &pMsg->data.route,  &pMsg->addr_logicalPeer  )  )  {
			 switch  (  pMsg->uiTaskType  )  {
					 case  CONST_imTaskType_shareDynBmp:
					 case  CONST_imTaskType_shareGps:
						   break;
					 default:  {
							 #ifdef  __DEBUG__
								     traceLogA(  (char*)  "procMsgTask_mc_media: getIdInfo_logicalPeer failed."  );  
							 #endif
							 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "procMsgTask_mc_mgr: getIdInfo_logicalPeer failed."  )  );
							 goto  errLabel;							 
							 }
							 break;
			 }
	 	 }		 
	 }
	 

	 if  (  !isUcFlgResp(  pMsg->ucFlg  )  )  {

		 if  (  !bMsgInput  &&  pMsg->usCode  ==  CONST_qyCmd_sendMedia  )  {		//  Ö÷¶¯·¢³ö
			 			 
			 switch  (  pContent->uiType  )  {

					 case  CONST_imCommType_transferAvInfo:
						   if  (  pContent->transferAvInfo.tmp_usSubtype  !=  CONST_transferAvInfo_subtype_task  )  {
							   #ifdef  __DEBUG__
									   MACRO_qyAssert(  0,  _T(  "transferAvInfo.subtype err, not task"  )  );
							   #endif
							   goto  errLabel;
						   }
						   //TRANSFER_AV_task  *  pTransferAvTask;  pTransferAvTask  =  (  TRANSFER_AV_task  *  )pContent;

						   //
						   if  (  !pCtx->pProcessQ  )  goto  errLabel;

						   tmpiRet  =  pCtx->pProcessQ->qTraverse_mono(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  );
						   if  (  tmpiRet  <  0  )  {
							   #ifdef  __DEBUG__
									   traceLogA(  (char*)  "procMsgTask_mc_media: transferAvInfo qTraverse_mono failed;"  ); 
							   #endif
							   goto  errLabel;
						   }
						   /*
						   if  (  !tmpiRet  )  {
							   #ifdef  __DEBUG__
									   traceLogA(  (char*)  "procMsgTask_mc_media: transferAvInfo, to qPostMsg"  ); 
							   #endif
							   if  (  pCtx->pProcessQ->qPostMsg(  pMsg,  lenInBytes_msg  )  )  {
								   traceLogA(  (char*)  "procMsgTask_mc_robot: 1. qPostMsg failed"  );
								   goto  errLabel;
							   }
							   //
							   //printQ_mis(  &pCtx->pProcessQ->m_q,  0  );

							   //
							   if  (  pTransferAvTask->myTask.ucbVideoConferenceStarter  )  {
								   //  ÔÙ²éÑ¯Ò»´ÎprocessQ_media, ÒòÎªÊÓÆµ»áÒéµÄbmpInfo_compressµÈ£¬ÊÇÔÚÈë¶ÓÁÐÊ±²ÅÉú³ÉµÄ¡£Òª´ÓÀïÃæÈ¡³öÀ´
								   if  (  pCtx->pProcessQ->qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  )  <=  0  )  goto  errLabel;
							   }

							   #ifdef  __DEBUG__
									   traceLogA(  (char*)  "procMsgTask_mc_media: transferAvInfo, qPostMsg ok;"  ); 
							   #endif
						   }
						   */
						   //  							
							   
						   //  2008/03/21, 
						   //startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "send transferAvInfo"  )  );
						   						   
						   break;
					 case  CONST_imCommType_transferAvReplyInfo:

						   if  (  !pCtx->pProcessQ  )  goto  errLabel;

						   //  traceLogA(  (char*)  "Î´Íê³É£¬Òª×¢Òâ£¬»¹ÐèÒªÓÐ¹Ø±ÕÊÓÆµ»á»°µÄ¹¤×÷¡£Ö÷ÒªÖ¸£¬¶Ô hic µÄ ICClose(  ) µÈ"  );
						   if  (  pContent->transferAvReplyInfo.usOp  !=  CONST_imOp_recv_accept  )  {
							   #if  0	//  2012/03/24. 这里不直接删除,都统一转移到qisChkTasks_gui里去进行,以便异步处理
									pCtx->pProcessQ->qRemoveMsg(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  );	//  ²»ÔÊÐí´«ËÍ					
							   #endif
							   }				 
						   else  {					   
								 //  Ö»ÓÐ¶ÓÁÐÖÐµÄÏûÏ¢²ÅÊÇ¿ÉÒÔ´«µÝÊý¾ÝµÄ								   
							     tmpiRet  =  pCtx->pProcessQ->qTraverse_mono(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  );								
								 if  (  tmpiRet  <  0  )  {	
									 #ifdef  __DEBUG__
											 traceLogA(  (char*)  "procMsgTask_mc_media: transferAvReplyInfo qTraverse_mono failed."  );
									 #endif
									 goto  errLabel;									 
								 }
								 /*
								 if  (  !tmpiRet  )  {
									 if  (  pMsg->iTaskId  )  {		//  2009/09/10
										 #ifdef  __DEBUG__
												 traceLogA(  (char*)  "procMsgTask_mc_media: transferAvReplyInfo to qPostMsg;"  ); 
										 #endif
										 //
										 if  (  pCtx->pProcessQ->qPostMsg(  pMsg,  lenInBytes_msg  )  )  {
											 #ifdef  __DEBUG__
													 traceLogA(  (char*)  "procMsgTask_mc_robot: transferAvReplyInfo, qPostMsg failed"  );
											 #endif
											 goto  errLabel;
										 }
										 //
										 //printQ_mis(  &pCtx->pProcessQ->m_q,  0  );
										 #ifdef  __DEBUG__
												 traceLogA(  (char*)  "procMsgTask_mc_media: avReply ok;"  ); 
										 #endif

										 //
										 //  2014/11/20								 
										 //  post

									 }
								 }	
								 */
	
								 //startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "send transferAvReplyInfo"  )  );

						   }					   
						   
						   break;
					 case  CONST_imCommType_transferVideoData:  {

						   bRemoveIfErr  =  FALSE;			//  2008/05/14, ²»ÄÜÒòÎª³ö´í½«É¾³ý½Úµã¡£ÓÐÊ±Êý¾Ý±ÈavProcInfoÅÜµÄ¿ì£¬²»ÄÜÒò´Ë°Ñ½Úµã¸øÉ¾³ýÁË¡£

						   if  (  !pCtx->pProcessQ  )  goto  errLabel;

						   startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "send transferVideoData"  )  );

						   if  (  (  tmpiRet  =  pCtx->pProcessQ->qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  )  )  <=  0  )  {
							   traceLogA(  (char*)  "procMsgTask_mc_media: ´¦ÀíCONST_imCommType_transferVideoData %s¡£",  tmpiRet  ?  "failed"  :  "not found"  );
							   goto  errLabel;
						   }

						   }
						   iErr  =  0;  goto  errLabel;
						   break;
					 case  CONST_imCommType_transferAudioData:  {

						   bRemoveIfErr  =  FALSE;			//  2008/05/14, ²»ÄÜÒòÎª³ö´í½«É¾³ý½Úµã¡£ÓÐÊ±Êý¾Ý±ÈavProcInfoÅÜµÄ¿ì£¬²»ÄÜÒò´Ë°Ñ½Úµã¸øÉ¾³ýÁË¡£

						   if  (  !pCtx->pProcessQ  )  goto  errLabel;

						   startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "send transferAudioData"  )  );

						   if  (  (  tmpiRet  =  pCtx->pProcessQ->qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  )  )  <=  0  )  {
							   traceLogA(  (char*)  "procMsgTask_mc_media: ´¦ÀíCONST_imCommType_transferAudioData %s¡£",  tmpiRet  ?  "failed"  :  "not found"  );
							   goto  errLabel;
						   }

						   }
						   iErr  =  0;  goto  errLabel;
						   break;
					 case  CONST_imCommType_taskProcReq:
						   switch  (  pContent->taskProcReq.usOp  )  {
								   case  CONST_imOp_send_cancel:								
								   case  CONST_imOp_recv_cancel:

									     if  (  !pCtx->pProcessQ  )  goto  errLabel;

									     //  printQ_mis(  &pCtx->processQ  );
										 #if  0  //  2012/03/24. 这里不直接删除,都统一转移到qisChkTasks_gui里去进行,以便异步处理
											pCtx->pProcessQ->qRemoveMsg(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  );
										 #endif
										 //  printQ_mis(  &pCtx->processQ  );

									     break;
								   default:
										   break;
						   }

						   //  ÇåÀíÒ»ÏÂ.  2008/10/18
						   //  chkMsgrs_sendLocalAv(  pProcInfo  );
						   //  if  (  bNoMsgrs_sendLocalAv(  pProcInfo,  -1  )  )  {
							   //  if  (  pMainWnd  )  PostMessage(  pMainWnd->m_hWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_applyForClosingAv_qmc,  0  );    
						   //  }

						   break;
						   //

					 case  CONST_imCommType_transferGpsInfo:		//  2012/04/19					

						   if  (  !pCtx->pProcessQ  )  goto  errLabel;

						   tmpiRet  =  pCtx->pProcessQ->qTraverse_mono(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  );
						   if  (  tmpiRet  <  0  )  {	  
							   traceLogA(  (char*)  "procMsgTask_mc_media: transferGpsInfo qTraverse_mono failed;"  ); 
							   goto  errLabel;
						   }
						   if  (  !tmpiRet  )  {
							   traceLogA(  (char*)  "procMsgTask_mc_media: transferGpsInfo, to qPostMsg"  ); 
							   if  (  pCtx->pProcessQ->qPostMsg(  pMsg,  lenInBytes_msg  )  )  {
								   traceLogA(  (char*)  "procMsgTask_mc_robot: 1. qPostMsg failed"  );
								   goto  errLabel;
							   }
							   //
							   //printQ_mis(  &pCtx->pProcessQ->m_q,  0  );

							   //  if  (  pContent->transferAvInfo.myTask.ucbVideoConferenceStarter  )  
							   {
								   //  
								   if  (  pCtx->pProcessQ->qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  )  <=  0  )  goto  errLabel;
							   }

							   traceLogA(  (char*)  "procMsgTask_mc_media: transferGpsInfo, qPostMsg ok;"  ); 
						   }							
						   //  							
							   
						   //  2008/03/21, 
						   startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "send transferGpsInfo"  )  );
						   						   
						   break;
						   					 
					 case  CONST_imCommType_transferGpsReplyInfo:

						   if  (  !pCtx->pProcessQ  )  goto  errLabel;

						   //  traceLogA(  (char*)  "Î´Íê³É£¬Òª×¢Òâ£¬»¹ÐèÒªÓÐ¹Ø±ÕÊÓÆµ»á»°µÄ¹¤×÷¡£Ö÷ÒªÖ¸£¬¶Ô hic µÄ ICClose(  ) µÈ"  );
						   if  (  pContent->transferGpsReplyInfo.usOp  !=  CONST_imOp_recv_accept  )  {
							   #if  0	//  2012/03/24. 这里不直接删除,都统一转移到qisChkTasks_gui里去进行,以便异步处理
									pCtx->pProcessQ->qRemoveMsg(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  );	//  ²»ÔÊÐí´«ËÍ					
							   #endif
							   }				 
						   else  {					   
								 //  Ö»ÓÐ¶ÓÁÐÖÐµÄÏûÏ¢²ÅÊÇ¿ÉÒÔ´«µÝÊý¾ÝµÄ								   
							     tmpiRet  =  pCtx->pProcessQ->qTraverse_mono(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  );								
								 if  (  tmpiRet  <  0  )  {	
									 traceLogA(  (char*)  "procMsgTask_mc_media: transferGpsReplyInfo qTraverse_mono failed."  );
									 goto  errLabel;									 
								 }
								 if  (  !tmpiRet  )  {
									 if  (  pMsg->iTaskId  )  {		//  2009/09/10
										 traceLogA(  (char*)  "procMsgTask_mc_media: transferGpsReplyInfo to qPostMsg;"  ); 
										 if  (  pCtx->pProcessQ->qPostMsg(  pMsg,  lenInBytes_msg  )  )  {
											 traceLogA(  (char*)  "procMsgTask_mc_robot: transferGpsReplyInfo, qPostMsg failed"  );
											 goto  errLabel;
										 }
										 //
										 //printQ_mis(  &pCtx->pProcessQ->m_q,  0  );
										 traceLogA(  (char*)  "procMsgTask_mc_media: gpsReply ok;"  ); 
									 }
								 }									 
	
								 startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "send transferGpsReplyInfo"  )  );
						   }					   
						   
						   break;
						   
					 case  CONST_imCommType_imGrp:  {  //  2018/10/27
						   int  ii  =  0;
						   }
						   break;
						   
						   //
					 default:
							#ifdef  __DEBUG__
									traceLogA(  (char*)  "procMsgTask_mc_media_mgr failed. unknown pContent->uiType is %d",  pContent->uiType  );
							#endif
							goto  errLabel;
							break;			 
			 }

			 printMisMsg(  0,  0,  (  MIS_MSGU  *  )pMsg  );
			
			 if  (  !pMsg->data.route.idInfo_to.ui64Id  )  {
				 switch  (  pMsg->uiTaskType  )  {
						 case  CONST_imTaskType_shareDynBmp:		
						 case  CONST_imTaskType_shareGps:
							   //
							   iErr  =  0;  goto  errLabel;
							   break;
						 default:
								break;
				 }
				 traceLogA(  (char*)  "procMsgTask_mc_media failed, idInfo_to is 0"  );
				 goto  errLabel;
			 }

			 //  traceLogA(  (char*)  "talking"  );
			 //if  (  postMsg2Mgr_mc(  pMisCnt,  NULL,  pMsg->uiType,  pMsg->ucFlg,  pMsg->usCode,  pMsg->tStartTime,  pMsg->uiTranNo,  pMsg->usSeqNo,  pMsg->data.buf,  pMsg->lenInBytes  -  offsetof(  MIS_MSG_routeTalkData,  buf  ),  &pMsg->addr_logicalPeer.idInfo,  &pMsg->data.route.idInfo_to,  0,  NULL,  FALSE  )  )  goto  errLabel;
			 //  2015/09/06
			 if  (  procMsgTask2Output_mc(  pProcInfo,  (  MIS_CNT  *  )pMsg->pMisCnt,  pMsg,  lenInBytes_msg,  pChannel,  _T(  "thread_mgr"  )  )  )  goto  errLabel;

			 //
			 iErr  =  0;  goto  errLabel;

		 }

			 
		 //  ½ÓÊÕÎÄ¼þµÄÇëÇó°ü, Î´È·ÈÏ£»Ó¦×ª·¢µ½½çÃæÈ¥ÏÔÊ¾
		 //
		 if  (  bMsgInput  &&  pMsg->usCode  ==  CONST_qyCmd_sendMedia  )  {
		
			 //  2009/10/18
			 pMsg->uiChannelType  =  pChannel->uiType;

			 //
			 //  ½ÓÊÕÎÄ¼þÊ±£¬ÒªÏÈ¸ø¶Ô·½·¢Ò»¸öokµÄÏìÓ¦£¬ÕâÑù£¬·½±ã¶Ô·½ÖªµÀÍ¨ÐÅÃ»ÎÊÌâ¡£·ñÔò£¬¾ÍÓÖÒªÔÙ·¢Ò»´ÎÁË
			 //
			 switch  (  pContent->uiType  )  {
				     case  CONST_imCommType_transferAvInfo:  {
						   void						*	pDb			=	NULL;
						   #ifndef  __NOTSUPPORT_DB__
									CQnmDb				db;
						   #endif
						   unsigned  short				usRespCode	=	CONST_qyRc_unknown;	
						   CQyMalloc					mallocObj_rcd;
						   IM_TASK_RCD				*	pRcd		=	(  IM_TASK_RCD  *  )mallocObj_rcd.mallocf(  sizeof(  IM_TASK_RCD  )  );
						   if  (  !pRcd  )  goto  errLabel;

						   if  (  !pCtx->pProcessQ  )  goto  errLabel;

						   //
						   if (pContent->transferAvInfo.uiTaskType == CONST_imTaskType_shareDevice_grp) {
							   if (pProcInfo->uiTerminalType == CONST_terminalType_conf) {
								   //
								   traceLog((TCHAR*)_T("对会议终端，强制改成会议任务"));
								   //
								   pContent->transferAvInfo.uiTaskType = CONST_imTaskType_transferAvInfo;
								   pContent->transferAvInfo.shareDevice_grp_index = 0;
							   }
						   }

						   //
						   pMsg->uiTaskType  =  pContent->transferAvInfo.uiTaskType;
						   pMsg->iStatus  =  CONST_imTaskStatus_resp;

						   //  2009/09/07
						   if  (  pContent->transferAvInfo.uiTaskType  ==  CONST_imTaskType_viewDynBmp  )  {

							   if  (  qPostMsg(  pMsg,  lenInBytes_msg,  &pQyMc->gui.processQ,  _T(  "procMsgTask_mc_media_mgr"  ))) {
								   #ifdef  __DEBUG__
										   traceLogA(  (char*)  "mcThreadProc_mis_work(  ): qPostMsg(  ) failed"  );  
								   #endif
								   goto  errLabel;
							   }			
							   PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    

							   iErr  =  0;  goto  errLabel;
						   }
				   
						   //  2014/11/21. 这里要把代理的信息更新到起始任务里。
						   if  (  pContent->transferAvInfo.proxiedTranInfo.idInfo.ui64Id  &&  pContent->transferAvInfo.proxiedTranInfo.uiObjType  )  {
							   if  (  pContent->transferAvInfo.proxiedTranInfo.idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {

								   PARAM_findOrgMsg  param;
								   memset(  &param,  0,  sizeof(  param  )  );
								   param.bNeedUpdate  =  TRUE;

								   tmpiRet  =  pCtx->pProcessQ->qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  &param  );

								   iErr  =  0;  goto  errLabel;
							   }
						   }

						   //
						   #ifndef  __NOTSUPPORT_DB__
									if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
									pDb  =  db.m_pDbMem->pDb;
						   #endif

						   //
						   if  (  !msg2TaskRcd(  pMisCnt,  pMsg,  usRespCode,  pRcd  )  )  {
							   #ifdef  __DEBUG__
									   traceLogA(  (char*)  "msg2TaskRcd failed"  );  
							   #endif
							   goto  errLabel;
						   }
						   tmpiRet  =  storeTaskInDb(  pDb,  pQyMc->cfg.db.iDbType,  pMisCnt,  0,  pRcd,  FALSE  );
						   if  (  tmpiRet  <  0  )  {
							   #ifdef  __DEBUG__
									   traceLogA(  (char*)  "mcThreadProc_mis_media(  ): storeTaskInDb failed"  ); 
							   #endif
							   goto  errLabel;
						   }
						   //
#ifdef  __DEBUG__
						   if (0) {
							   int  index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, pRcd->id);
							   QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*  )getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
							   if (pTaskInfo) {
								   QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
								   MIS_MSG_TASK* tmp_pMsgTask = &pTaskInfo->var.pTaskData->msgU.task;
								   int  iStatus = tmp_pMsgTask->iStatus;
								   int  ii = 0;


							   }
						   }
#endif 
						   //  //  2008/06/04
						   if  (  tmpiRet  >  0  )  {	//  rcd.iStatus
							   tmpiRet  =  pCtx->pProcessQ->qTraverse_mono(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  );
							   if  (  tmpiRet  <  0  )  goto  errLabel;
							   if  (  tmpiRet  >  0  )  {
								   #ifdef  __DEBUG__
										   traceLogA(  (char*)  "procMsgTask_mc_media. hhh"  );
								   #endif
						   		   iErr  =  0;  goto  errLabel;						   
							   }
							   //  
#if  0
							   if  (  pRcd->iStatus  !=  pMsg->iStatus  &&  !bTaskAlive(  pRcd->iStatus  )  )  {
								   if  (  g_dbFuncs.pf_updateTaskStatus(  pDb,  pMsg->iStatus,  pRcd->id  )  )  goto  errLabel;
							   }
#endif 
							   
						   }

						   //  2007/07/01						   
						   pMsg->iTaskId  =  pRcd->id;
						   pMsg->uiTaskMode_unused  =  pRcd->uiMode;

						   //
						   if  (  qPostMsg(  pMsg,  lenInBytes_msg,  &pQyMc->gui.processQ,  _T(  "procMsgTask_mc_media_mgr"  ))) {
							   #ifdef  __DEBUG__
									   traceLogA(  (char*)  "mcThreadProc_mis_work(  ): qPostMsg(  ) failed"  );  
							   #endif
							   goto  errLabel;
						   }			
						   PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    
			   
						   iErr  =  0;  goto  errLabel;  

						   }
						   break;
					 case  CONST_imCommType_transferAvReplyInfo:  {  
						   void						*	pDb			=	NULL;
						   #ifndef  __NOTSUPPORT_DB__
									CQnmDb				db;
						   #endif
						   unsigned  short				usRespCode	=	CONST_qyRc_unknown;	

						   if  (  !pCtx->pProcessQ  )  goto  errLabel;

						   #ifndef  __NOTSUPPORT_DB__
									if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
									pDb  =  db.m_pDbMem->pDb;
						   #endif

						   //  ¶Ô·½²»ÔÊÐí
						   if  (  pContent->transferAvReplyInfo.usOp  !=  CONST_imOp_recv_accept  )  {
							   traceLogA(  (char*)  "procMsgTask_mc_media, usSp is not accept"  );
							   goto  errLabel;
						   }
						   //
						   if  (  pContent->transferAvReplyInfo.usOp  ==  CONST_imOp_recv_accept  )  {

							   #ifndef  __NOTSUPPORT_DB__
										if  (  !g_dbFuncs.pf_bGetImTaskRcdBySth(  pDb,  pQyMc->cfg.db.iDbType,  FALSE,  pMisCnt->cfg.misServName, &pMisCnt->idInfo, (  time_t  )pContent->transferAvReplyInfo.tStartTime_org,  pContent->transferAvReplyInfo.uiTranNo_org,  0,  NULL  )  )  {
											#ifdef  __DEBUG__
													traceLogA(  (char*)  "procMsgTask_mc_media failed: bGetImTaskRcdBySth returns false"  );
											#endif
											goto  errLabel;
									    }
							   #else
										CE_TASK_MEM	taskMem;
										if  (  getCeTaskMem(  pDb,  pQyMc->cfg.db.iDbType,  pMisCnt,  &pMisCnt->idInfo,  (  time_t  )pContent->transferAvReplyInfo.tStartTime_org,  pContent->transferAvReplyInfo.uiTranNo_org,  0,  &taskMem  )  )  {
											traceLogA(  (char*)  "procMsgTask_mc_media failed, getCeTaskMem failed"  );
											goto  errLabel;
										}
							   #endif

							   //
							   //  printQ_mis(  &pCtx->pProcessQ->m_q,  0  );
							   //
							   printMisMsg(  0,  0,  (  MIS_MSGU  *  )pMsg  );

							   //  
							   if  (  pCtx->pProcessQ->qTraverse_mono(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  )  <=  0  )  {	  
								   traceLogA(  (char*)  "procMsgTask_mc_media failed: "  );
								   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "%s err: "  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
								   //
								   //  postMsg2Mgr...
								   goto  errLabel;
							   }
							   }
						   else  {
							     traceLogA(  (char*)  "pContent->uiType is %d",  pContent->uiType  );
								 goto  errLabel;
						   }					   
			
						   //  2013/02/13
						   if  (  pContent->transferAvReplyInfo.uiTranNo_org  )  {
							   if  (  pContent->transferAvReplyInfo.uiTranNo_org  ==  pQyMc->gui.progress.var.uiTranNo  )  {
								   notifyProgressEnd(  &pQyMc->gui.progress,  pContent->transferAvReplyInfo.uiTranNo_org,  0  );
							   }
						   }


						   /*
						   traceLogA(  (char*)  "·¢ËÍÊÓÆµÊý¾ÝµÄÌõ¼þ¾ß±¸ÁË"  );
						   if  (  startChannel(  pProcInfo,  pMisCnt,  getChannelByType(  pMisCnt,  CONST_channelType_media  ),  _T(  "ÒÔ·¢ËÍÊÓÆµÊý¾Ý"  )  )  )  {
							   traceLogA(  (char*)  "Æô¶¯media ChannelÊ§°Ü"  );  goto  errLabel;
						   }
						   if  (  startChannel(  pProcInfo,  pMisCnt,  getChannelByType(  pMisCnt,  CONST_channelType_realTimeMedia  ),  _T(  "ÒÔ·¢ËÍÒôÆµÊý¾Ý"  )  )  )  {
							   traceLogA(  (char*)  "Æô¶¯rtMedia ChannelÊ§°Ü"  );  goto  errLabel;
						   }
						   */
						   startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "recv transferAvReplyInfo"  )  );
				 
						   //  ÏÂÃæ×¼±¸·¢ËÍ×¼±¸ºÃµÄÏìÓ¦°ü
						   usRespCode  =  CONST_qyRc_ok;
				 
						   MACRO_makeImSimpleResp(  pMsg->usCode,  pContent->uiType,  0,  respSimple  );

						   postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_outputTask,  CONST_commFlg_resp,  usRespCode,  pMsg->tStartTime,  pMsg->uiTranNo,  0,  pMsg->iTaskId,  pMsg->uiTaskType,  (  char  *  )&respSimple,  sizeof(  respSimple  ),  &pMsg->addr_logicalPeer.idInfo,  &pMsg->idInfo_taskSender,  &pMsg->idInfo_taskReceiver,  &pMsg->data.route.idInfo_from,  pChannel->uiType,  NULL,  FALSE  );     

						   iErr  =  0;  goto  errLabel;

						  }
						   break;
					 case  CONST_imCommType_transferVideoData:  {
						 	
						   bRemoveIfErr  =  FALSE;			//  2008/05/14, ²»ÄÜÒòÎª³ö´í½«É¾³ý½Úµã¡£ÓÐÊ±Êý¾Ý±ÈavProcInfoÅÜµÄ¿ì£¬²»ÄÜÒò´Ë°Ñ½Úµã¸øÉ¾³ýÁË¡£

						   if  (  !pCtx->pProcessQ  )  goto  errLabel;

						   startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "recv transferVideoData"  )  );

						   //  2009/05/12						   
						   pMsg->uiChannelType  =  pChannel->uiType;
						   
						   if  (  tmpiRet  =  pCtx->pProcessQ->qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  )  <=  0  )  {
							   getTimelStr(  pMsg->tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
							   //  traceLogA(  (char*)  "procMsgTask_mc_media failed: video data error"  );
							   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "%s err: %I64u,  tn %d, tn_openAvDev [%d]"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  ), pMsg->data.route.idInfo_from.ui64Id,  pMsg->uiTranNo,  pContent->transferVideoData.uiTranNo_openAvDev  );
							   //
							   //  2010/12/27
							   //  if  (  pMsg->data.route.idInfo_to.ui64Id  !=  pMisCnt->idInfo.ui64Id  )  
							   {
								   #define	CONST_nIntervalInMs_tryToResumeVideoTask	200		//  5000		//  2014/10/13
								   //
								   if  (  GetTickCount(  )  -  pCtx->dwTickCnt_tryToResumeVideoConference  >  CONST_nIntervalInMs_tryToResumeVideoTask  )  {
									   pCtx->dwTickCnt_tryToResumeVideoConference  =  GetTickCount(  );

									   #ifdef  __DEBUG__
											   traceLogA(  (char*)  "Not finished: procMsgTask_mc_media_mgr: videoData err, shall send a request to retrieve original avInfo"  );
									   #endif
									   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "procMsgTask_mc_media_mgr: %I64u, videoData err, will send a request to retrieve original avInfo."  ),  pMsg->data.route.idInfo_from.ui64Id   );
									   //
									   showTaskStatus(  pMisCnt,  &pMsg->addr_logicalPeer.idInfo,  &pMsg->data.route.idInfo_from,  NULL,  FALSE,  pMsg->usCode,  0,  pContent->transferVideoData.uiTranNo_openAvDev,  pContent->uiType,  0,  CONST_imTaskStatus_err_missingOrgReq  );
								   }
							   }
							   //
							   //
							   goto  errLabel;		
						   }


						   iErr  =  0;  goto  errLabel;

						   }
						   break;

					 case  CONST_imCommType_transferAudioData:  {

						   bRemoveIfErr  =  FALSE;			//  2008/05/14, ²»ÄÜÒòÎª³ö´í½«É¾³ý½Úµã¡£ÓÐÊ±Êý¾Ý±ÈavProcInfoÅÜµÄ¿ì£¬²»ÄÜÒò´Ë°Ñ½Úµã¸øÉ¾³ýÁË¡£
						 	
						   if  (  !pCtx->pProcessQ  )  goto  errLabel;

						   startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "recv transferAudioData"  )  );

						   //  2009/05/12						   
						   pMsg->uiChannelType  =  pChannel->uiType;

						   if  (  tmpiRet  =  pCtx->pProcessQ->qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  )  <=  0  )  {
							   getTimelStr(  pMsg->tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
							   //  traceLogA(  (char*)  "procMsgTask_mc_media failed: audio data error"  );
							   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "%s err: %I64u. tn %d, tn_openAvDev [%d]"  ),  qyGetDesByType1(  getResTable(  0, &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  ),  pMsg->data.route.idInfo_from.ui64Id,  pMsg->uiTranNo,  pContent->transferAudioData.uiTranNo_openAvDev  );
							   //
							   //  2009/10/17
							   //  if  (  pMsg->data.route.idInfo_to.ui64Id  !=  pMisCnt->idInfo.ui64Id  )  
							   {
								   if  (  GetTickCount(  )  -  pCtx->dwTickCnt_tryToResumeVideoConference  >  5000  )  {
									   pCtx->dwTickCnt_tryToResumeVideoConference  =  GetTickCount(  );
									   #ifdef  __DEBUG__
											   traceLogA(  (char*)  "Not finished: procMsgTask_mc_media: audioData err, try to find orgReq"  );
									   #endif
									   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "procMsgTask_mc_media: audioData err, try to find orgReq"  )  );
									   //
									   int  iStatus  =  CONST_imTaskStatus_err_missingOrgReq;
									   //
									   showTaskStatus(  pMisCnt,  &pMsg->addr_logicalPeer.idInfo,  &pMsg->data.route.idInfo_from,  NULL,  FALSE,  pMsg->usCode,  0,  pContent->transferAudioData.uiTranNo_openAvDev,  pContent->uiType,  0,  iStatus  );
								   }								   
							   }
							   //
							   //
							   goto  errLabel;		//  ÀíÓÉÍ¬ÉÏ
						   }


						   iErr  =  0;  goto  errLabel;

						   }
						   break;

					 case  CONST_imCommType_remoteAssistReq:
						   
						   bRemoveIfErr  =  FALSE;			//  2008/05/14, ²»ÄÜÒòÎª³ö´í½«É¾³ý½Úµã¡£ÓÐÊ±Êý¾Ý±ÈavProcInfoÅÜµÄ¿ì£¬²»ÄÜÒò´Ë°Ñ½Úµã¸øÉ¾³ýÁË¡£
						   
						   if  (  !pCtx->pProcessQ  )  goto  errLabel;

						   startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "recv remoteAssistReq"  )  );

						   if  (  tmpiRet  =  pCtx->pProcessQ->qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  )  <=  0  )  {
							   getTimelStr(  pMsg->tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
							   traceLogA(  (char*)  "procMsgTask_mc_media failed: "  );
							   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "%s err: st [%s], tn_openAvDev [%d]"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  ), CQyString(  timeBuf  ),  pContent->transferVideoData.uiTranNo_openAvDev  );
							   //
							   goto  errLabel;		//  ÀíÓÉÍ¬ÉÏ
						   }

						   iErr  =  0;  goto  errLabel;

						   break;

						   //  2012/04/20
					 case  CONST_imCommType_transferGpsInfo:  {
						   unsigned  short				usRespCode	=	CONST_qyRc_unknown;	

						   if  (  !pCtx->pProcessQ  )  goto  errLabel;

						   //
						   pMsg->uiTaskType  =  pContent->transferGpsInfo.uiTaskType;
						   pMsg->iStatus  =  CONST_imTaskStatus_resp;

						   //  2009/09/07
						   if  (  pContent->transferGpsInfo.uiTaskType  ==  CONST_imTaskType_viewGps  )  {

							   if  (  qPostMsg(  pMsg,  lenInBytes_msg,  &pQyMc->gui.processQ,  _T(  "procMsgTask_mc_media_mgr 2"  ))) {
								   traceLogA(  (char*)  "mcThreadProc_mis_work(  ): qPostMsg(  ) failed"  );  goto  errLabel;
							   }			
							   PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    

							   iErr  =  0;  goto  errLabel;
						   }

						   //
						   #ifdef  __DEBUG__
								   traceLog((TCHAR*)  _T(  "procMsgTask_mc_media failed, transferGpsInfo."  )  );
						   #endif

						   goto  errLabel;

						   //
						   }
						   break;
						   					 
					 case  CONST_imCommType_transferGpsReplyInfo:  {  
						   void						*	pDb			=	NULL;
						   #ifndef  __NOTSUPPORT_DB__
									CQnmDb				db;
						   #endif
						   unsigned  short				usRespCode	=	CONST_qyRc_unknown;	

						   if  (  !pCtx->pProcessQ  )  goto  errLabel;

						   #ifndef  __NOTSUPPORT_DB__
									if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
									pDb  =  db.m_pDbMem->pDb;
						   #endif

						   //  ¶Ô·½²»ÔÊÐí
						   if  (  pContent->transferGpsReplyInfo.usOp  !=  CONST_imOp_recv_accept  )  {
							   traceLogA(  (char*)  "procMsgTask_mc_media, usOp is not accept"  );
							   goto  errLabel;
						   }
						   //
						   if  (  pContent->transferGpsReplyInfo.usOp  ==  CONST_imOp_recv_accept  )  {

							   #ifndef  __NOTSUPPORT_DB__
										if  (  !g_dbFuncs.pf_bGetImTaskRcdBySth(  pDb,  pQyMc->cfg.db.iDbType,  FALSE,  pMisCnt->cfg.misServName, &pMisCnt->idInfo, (  time_t  )pContent->transferGpsReplyInfo.tStartTime_org,  pContent->transferGpsReplyInfo.uiTranNo_org,  0,  NULL  )  )  {
											traceLogA(  (char*)  "procMsgTask_mc_media failed: ÕâÀïÃ»ÕÒµ½Ïà¹ØµÄÈÎÎñ£¬Ó¦¸ÃÏò¶Ô·½·¢ËÍÒ»¸ö´íÎóµÄÈÎÎñµÄÏìÓ¦°ü"  );
											goto  errLabel;
									    }
							   #else
										CE_TASK_MEM	taskMem;
										if  (  getCeTaskMem(  pDb,  pQyMc->cfg.db.iDbType,  pMisCnt,  &pMisCnt->idInfo,  (  time_t  )pContent->transferGpsReplyInfo.tStartTime_org,  pContent->transferGpsReplyInfo.uiTranNo_org,  0,  &taskMem  )  )  {
											traceLogA(  (char*)  "procMsgTask_mc_media failed, getCeTaskMem failed"  );
											goto  errLabel;
										}
							   #endif

							   //
							   //printQ_mis(  &pCtx->pProcessQ->m_q,  0  );
							   //
							   printMisMsg(  0,  0,  (  MIS_MSGU  *  )pMsg  );

							   //  
							   if  (  pCtx->pProcessQ->qTraverse_mono(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  )  <=  0  )  {	  
								   traceLogA(  (char*)  "procMsgTask_mc_media failed: "  );
								   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "%s err: "  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
								   //
								   //  postMsg2Mgr...
								   goto  errLabel;
							   }
							   }
						   else  {
							     traceLogA(  (char*)  "pContent->uiType is %d",  pContent->uiType  );
								 goto  errLabel;
						   }					   
			
						   /*
						   traceLogA(  (char*)  "·¢ËÍÊÓÆµÊý¾ÝµÄÌõ¼þ¾ß±¸ÁË"  );
						   if  (  startChannel(  pProcInfo,  pMisCnt,  getChannelByType(  pMisCnt,  CONST_channelType_media  ),  _T(  "ÒÔ·¢ËÍÊÓÆµÊý¾Ý"  )  )  )  {
							   traceLogA(  (char*)  "Æô¶¯media ChannelÊ§°Ü"  );  goto  errLabel;
						   }
						   if  (  startChannel(  pProcInfo,  pMisCnt,  getChannelByType(  pMisCnt,  CONST_channelType_realTimeMedia  ),  _T(  "ÒÔ·¢ËÍÒôÆµÊý¾Ý"  )  )  )  {
							   traceLogA(  (char*)  "Æô¶¯rtMedia ChannelÊ§°Ü"  );  goto  errLabel;
						   }
						   */
						   startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "recv transferGpsReplyInfo"  )  );
				 
						#if  0
						   //  ÏÂÃæ×¼±¸·¢ËÍ×¼±¸ºÃµÄÏìÓ¦°ü
						   usRespCode  =  CONST_qyRc_ok;
				 
						   MACRO_makeImSimpleResp(  pMsg->usCode,  pContent->uiType,  0,  respSimple  );

						   postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_outputTask,  CONST_commFlg_resp,  usRespCode,  pMsg->tStartTime,  pMsg->uiTranNo,  0,  pMsg->iTaskId,  pMsg->uiTaskType,  (  char  *  )&respSimple,  sizeof(  respSimple  ),  &pMsg->addr_logicalPeer.idInfo,  &pMsg->idInfo_taskSender,  &pMsg->idInfo_taskReceiver,  &pMsg->data.route.idInfo_from,  pChannel->uiType,  NULL,  FALSE  );     
						#endif

						   iErr  =  0;  goto  errLabel;

						  }
						   break;
						   	
					 case  CONST_imCommType_transferGpsData:  {
						 	
						   bRemoveIfErr  =  FALSE;			//  2008/05/14, ²»ÄÜÒòÎª³ö´í½«É¾³ý½Úµã¡£ÓÐÊ±Êý¾Ý±ÈavProcInfoÅÜµÄ¿ì£¬²»ÄÜÒò´Ë°Ñ½Úµã¸øÉ¾³ýÁË¡£

						   if  (  !pCtx->pProcessQ  )  goto  errLabel;

						   startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "recv transferGpsData"  )  );

						   //  2009/05/12						   
						   pMsg->uiChannelType  =  pChannel->uiType;
						   
						   if  (  tmpiRet  =  pCtx->pProcessQ->qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  )  <=  0  )  {
							   getTimelStr(  pMsg->tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
							   //  traceLogA(  (char*)  "procMsgTask_mc_media failed: video data error"  );
							   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "%s err: %I64u,  tn %d, tn_openAvDev [%d]"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  ), pMsg->data.route.idInfo_from.ui64Id,  pMsg->uiTranNo,  pContent->transferGpsData.uiType  );
							   //
							   //
							   goto  errLabel;		
						   }

						   iErr  =  0;  goto  errLabel;

						   }
						   break;

					 default:
							 #ifdef  __DEBUG__
									 traceLogA(  (char*)  "procMsgTask_mc_media failed, bInput, pContent->uiType is %d",  pContent->uiType  );
							 #endif
							 goto  errLabel;
							 break;
			 }		
			 
		 }	//  

		 //  2015/




		 //  2015/09/07
		 if  (  !bMsgInput  )  {
			 
			 if  (  procMsgTask2Output_mc(  pProcInfo,  (  MIS_CNT  *  )pMsg->pMisCnt,  pMsg,  lenInBytes_msg,  pChannel,  _T(  "thread_mgr"  )  )  )  {
				 goto  errLabel;
			 }

			 iErr  =  0;  goto  errLabel;

		 }

		 
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "procMsgTask_mc_mgr failed:  kkkkkkkkk"  );  
		 #endif
		 goto  errLabel;
	 
	 
		}
	 else  {


		   //
		   printMisMsg(  0,  0,  (  MIS_MSGU  *  )pMsg  );

		   #ifdef  __DEBUG__
				   qyShowInfo1(  CONST_qyShowType_debug,  0, (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "%I64u¦%s"  ),  pMsg->data.route.idInfo_from.ui64Id,  qyGetDesByType1(  CONST_qyRcTable,  pMsg->usCode  )  );
		   #endif

		   if  (  !isRcOk(  pMsg->usCode  )  )  goto  errLabel;

		   #ifdef  __DEBUG__
				   traceLogA(  (char*)  "procMsgTask_mc_media:  "  );
		   #endif

		   //
	 }

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		#if  0	//  2011/10/28, 出错就清理队列，容易导致功能不稳定
		 if  (  pCtx->pProcessQ  )  {
			 if  (  bRemoveIfErr  )  pCtx->pProcessQ->qRemoveMsg(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  );
		 }
		#endif
	 }

	 return  iErr;
}


//
 //  lenInBytes
 int  procMsgTask_mc_robot_mgr(  void  *  pQyMcParam,  void  *  pSciParam,  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_TASK  *  pMsg,  unsigned  int  lenInBytes_msg,  BOOL  bMsgInput,  CTX_MC_THREAD  *  pCtx,  MIS_CHANNEL  *  pChannel  )
{
	 int					iErr				=	-1;
	 QY_MC				*	pQyMc				=	(  QY_MC  *  )pQyMcParam;
	 QY_SERVICEGUI_INFO	*	pSci				=	(  QY_SERVICEGUI_INFO  *  )pSciParam;
	 //
	 int					dataLen				=	0;
	 unsigned  int			uiMsgLen			=	offsetof(  MIS_MSG_TASK,  data  )  +  offsetof(  MIS_MSG_routeTalkData,  buf  );
	 unsigned  int			uiChannelType		=	CONST_channelType_talking;
	 IM_CONTENTU		*	pContent			=	(  IM_CONTENTU  *  )pMsg->data.buf;
	 HWND					hMainWnd			=	pQyMc->gui.hMainWnd;
	 MIS_CNT			*	pMisCnt				=	(  MIS_CNT  *  )pMsg->pMisCnt;
	 unsigned  short		usRespCode;
     
	 CQyMalloc				mallocObj_rcd;
	 IM_TASK_RCD		*	pRcd				=	(  IM_TASK_RCD  *  )mallocObj_rcd.mallocf(  sizeof(  IM_TASK_RCD  )  );
	 if  (  !pRcd  )  return  -1;
	 IM_TASK_RCD		&	rcd					=	*pRcd;
	 int					tmpiRet;
	 //
	 int					lenInBytes			=	0;
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;


	 if  (  !hMainWnd  )  return  -1;
	 if  (  !pMisCnt  )  return  -1;

	 memset(  &rcd,  0, sizeof(  rcd  )  );

#if  0
	 if  (  pCtx->pProcessQ->m_q.cfg.uiMaxQNodes  &&  pCtx->pProcessQ->m_q.uiQNodes  >=  pCtx->pProcessQ->m_q.cfg.uiMaxQNodes  )  {
		 traceLogA(  (char*)  "procMsgTask_mc_robot: processQ has max qNodes"  );
	 }
#endif

	 //
	 if  (  !pMsg->addr_logicalPeer.idInfo.ui64Id  )  {	//  Ç°ÃæÃ»ÓÐ¸³ÖµµÄ¶¼ÊÇÊÕµ½µÄÏûÏ¢
		 if  (  getIdInfo_logicalPeer(  pSci,  pMisCnt,  &pMsg->data.route,  &pMsg->addr_logicalPeer  )  )  {
		   	 traceLogA(  (char*)  "procMsgTask_mc_robot: getIdInfo_logicalPeer failed."  );  
			 goto  errLabel; 
	 	 }		 
	 }
	 

	 if  (  !isUcFlgResp(  pMsg->ucFlg  )  )  {
			 
			 //
			 //  ×¢Òâ£ºÒÔÏÂ£¬bMsgInputÎªFALSEÊ±£¬Îª´ÓÄÚ²¿·¢³ö¡£ÎªTRUEÊ±£¬´ÓÍâ²¿ÊÕÈë£¬ÓÉmgrÖÐ×ª¹ýÀ´
			 //
			  			
			 //  Ö÷¶¯·¢³ö
			 //
			 if  (  !bMsgInput  &&  pMsg->usCode  ==  CONST_qyCmd_sendRobotTask  )  {		

				 switch  (  pContent->uiType  )  {
					     case  CONST_imCommType_transferFileReq:
							   if  (  pCtx->pProcessQ->qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  )  <=  0  )  {	  
								   
								   /*
								   //
								   //  ÒªÊÇÔÚprocessQÀïÃ»ÓÐ£¬ÄÇÃ´¾Í¼ÓÈë¶ÓÁÐ; 
								   //
								   pMsg->idInfo_taskSender.ui64Id  =  pMsg->data.route.idInfo_from.ui64Id;
								   pMsg->idInfo_taskReceiver.ui64Id  =  pMsg->data.route.idInfo_to.ui64Id;
								   //
								   QM_OBJQ_MEM				mem;
								   QMEM_MESSENGER_CLI	*	pQMemObj;
								   if  (  findQMemByKey(  0,  pMisCnt->pObjQ,  &pMsg->idInfo_taskReceiver,  &mem  )  )  {
									   #ifdef  __DEBUG__
											   traceLog((TCHAR*)  _T(   "procMsgTask_mc_robot, not input transferFileReq， findQMemByKey failed"  )  );  
									   #endif
									   //										
									   showInfo_open0(  0,  0,  _T(   "procMsgTask_mc_robot, not input transferFileReq， findQMemByKey failed"  )  );
									   //
									   goto  errLabel;
								   }
								   pQMemObj  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
								   if  (  !pQMemObj  )  goto  errLabel;
								   if  (  pQMemObj->uiType  ==  CONST_objType_imGrp  )  pContent->transferFileReq.bGrpTask  =  TRUE; //  2007/09/05, ¸³ÉÏ×é±êÊ¶
								   //
								   //
								   if  (  pCtx->pProcessQ->qPostMsg(  pMsg,  lenInBytes_msg  )  )  {
									   #ifdef  __DEBUG__
											   traceLog((TCHAR*)  _T(  "procMsgTask_mc_robot, not input transferFileReq， qPostMsg failed"  )  );
									   #endif
									   //
									   showInfo_open0(  0,  0,  _T(   "procMsgTask_mc_robot, not input transferFileReq， qPostMsg failed"  )  );
									   //
									   goto  errLabel;
								   }
								   //  applyToSend¸ÄÎªwaitToSend, 2007/07/18
								   */
								   traceLogA(  (char*)  "procMsgTask_mc_robot_mgr failed: fileReq not found"  );
								   goto  errLabel;
							   }

							   /*
							   traceLogA(  (char*)  "·"  );
							   if  (  !pChannel->hThread_io  )  {
								   if  (  startMcIoThread(  pSci,  pMisCnt,  pChannel->uiType,  _T(  "ÒÔ·¢ËÍÎÄ¼þ"  )  )  )  {
									   traceLogA(  (char*)  "robot Channel"  );  
									   goto  errLabel;
								   }
							   }
							   */

							   break;
						 case  CONST_imCommType_taskProcReq:
							   switch  (  pContent->taskProcReq.usOp  )  {
								       case  CONST_imOp_send_cancel:
									   case  CONST_imOp_recv_cancel:
										     //  printQ_mis(  &pCtx->processQ  );
										     //pCtx->pProcessQ->qRemoveMsg(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  );
										     traceLogA(  (char*)  "cannot remove task here"  );
											 //  printQ_mis(  &pCtx->processQ  );
										     
										     break;
									   default:
											   break;
							   }

							   break;
						 default:
							    traceLogA(  (char*)  "´íÎóµÄÊý¾Ý¸ñÊ½£ºpContent->uiType is %d",  pContent->uiType  );
								goto  errLabel;
								break;
				 }

				 //  
				 //if  (  postMsg2Mgr_mc(  pMisCnt,  NULL,  pMsg->uiType,  pMsg->ucFlg,  pMsg->usCode,  pMsg->tStartTime,  pMsg->uiTranNo,  pMsg->usSeqNo,  (  char  *  )pMsg->data.buf,  pMsg->lenInBytes  -  offsetof(  MIS_MSG_routeTalkData,  buf  ),  &pMsg->addr_logicalPeer.idInfo,  &pMsg->data.route.idInfo_to,  0,  NULL,  FALSE  )  )  goto  errLabel;
				 //  2015/09/06
				 if  (  procMsgTask2Output_mc(  pProcInfo,  (  MIS_CNT  *  )pMsg->pMisCnt,  pMsg,  lenInBytes_msg,  pChannel,  _T(  "thread_mgr"  )  )  )  goto  errLabel;


				 iErr  =  0;  goto  errLabel;
			 }


			 //  ½ÓÊÕÎÄ¼þµÄÇëÇó°ü, Î´È·ÈÏ£»Ó¦×ª·¢µ½½çÃæÈ¥ÏÔÊ¾
			 //
			 if  (  bMsgInput  &&  pMsg->usCode  ==  CONST_qyCmd_sendRobotTask  )  {
				 
				   unsigned  short			usRespCode	=	CONST_qyRc_unknown;	
				   void					*	pDb			=	NULL;

				   #ifndef  __NOTSUPPORT_DB__
   							CQnmDb					db;			   	 
							if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
							pDb  =  db.m_pDbMem->pDb;
				   #endif
				
				   //  2009/10/18
				   pMsg->uiChannelType  =  pChannel->uiType;

				   //
				   switch  (  pContent->uiType  )  {
					       case  CONST_imCommType_transferFileReq:
							     pMsg->uiTaskType  =  CONST_imTaskType_recvFile;
					   		     pMsg->iStatus  =  CONST_imTaskStatus_applyToRecv;
								 break;
						   default:
					      	      traceLogA(  (char*)  "´íÎóµÄÊý¾Ý¸ñÊ½£ºpContent->uiType is %d",  pContent->uiType  );
						  		  goto  errLabel;
								  break;
				   }

				

				   //  ÕâÀïÒªÈë¿â£¬È»ºóÔÙÍ¨Öª½çÃæ

				   if  (  !msg2TaskRcd(  pMisCnt,  pMsg,  usRespCode,  &rcd  )  )  {
					   traceLogA(  (char*)  "msg2TaskRcd failed"  );  goto  errLabel;
				   }
				   tmpiRet  =  storeTaskInDb(  pDb,  pQyMc->cfg.db.iDbType,  pMisCnt,  0,  &rcd,  FALSE  );
				   if  (  tmpiRet  <  0  )  {
					   traceLogA(  (char*)  "mcThreadProc_mis_work(  ): storeTaskInDb failed"  ); 
					   goto  errLabel;
				   }
				   if  (  tmpiRet  >  0  )  {	//  ÕâÀï±íÃ÷Ô­À´ÒÑ¾­ÓÐ¼ÇÂ¼ÁË, Òª¶Ôrcd.iStatus×ö·ÖÎö£¬Èç¹ûÒÑ¾­È¡ÏûÁË£¬ÄÇÃ´¾ÍÒª·¢ËÍÒ»¸öÒÑÈ¡ÏûµÄÏìÓ¦¸ø¶Ô·½
					   switch  (  pContent->uiType  )  {
							   case  CONST_imCommType_transferFileReq:
								     if  (  rcd.iStatus  !=  CONST_imTaskStatus_applyToRecv  &&  rcd.iStatus  !=  CONST_imTaskStatus_waitToRecv  )  {
										 IM_SIMPLE_RESP		respSimple;
										 //
										 MACRO_makeImSimpleResp(  pMsg->usCode,  pContent->uiType,  rcd.iStatus,  respSimple  );
										 //
										 postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_outputTask,  CONST_commFlg_resp,  usRespCode,  pMsg->tStartTime,  pMsg->uiTranNo,  0,  pMsg->iTaskId,  pMsg->uiTaskType,  (  char  *  )&respSimple,  sizeof(  respSimple  ),  &pMsg->addr_logicalPeer.idInfo,  &pMsg->idInfo_taskSender,  &pMsg->idInfo_taskReceiver,  &pMsg->data.route.idInfo_from,  uiChannelType,  NULL,  FALSE  );     

										 traceLogA(  (char*)  "ÕâÀïÊÇËµÃ÷´ËÈÎÎñÒÑ½áÊøÁË£¬²»¹ÜÊ²Ã´½á¹û¡£²é³ö½á¹û·¢»ØÈ¥"  );

										 iErr  =  0;  goto  errLabel;

									 }
								     break;
							   default:
									  break;
					   }
				   }

				   //  ×¢Òâ£¬ÕâÀïÒª½«Êý¾Ý¿âÖÐÏàÓ¦µÄID¸ø¸³ÉÏ£¬2007/07/01
				   pMsg->iTaskId  =  rcd.id;
				   pMsg->uiTaskMode_unused  =  rcd.uiMode;
   			   

				   traceLogA(  (char*)  ""  );
				

				   if  (  qPostMsg(  pMsg,  lenInBytes_msg,  &pQyMc->gui.processQ,  _T(  "procmsgTask_mc_robot"  ))) {
					   traceLogA(  (char*)  "mcThreadProc_mis_work(  ): qPostMsg(  ) failed"  );  goto  errLabel;
				   }
			
				   PostMessage(  hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    
			   
				   iErr  =  0;  goto  errLabel;  

			 }


			 if  (  !bMsgInput  &&  pMsg->usCode  ==  CONST_qyCmd_sendRobotTaskReply  )  {

				 traceLogA(  (char*)  "ÎÄ¼þ½ÓÊÕÇëÇóÒÑ±»È·ÈÏ, ÐÅÏ¢´ÓtalkingÍ¨µÀÖÐ·¢³ö"  );

				 switch  (  pContent->uiType  )  {
						 case  CONST_imCommType_transferFileReplyReq:
							   if  (  pContent->transferFileReplyReq.usOp  !=  CONST_imOp_recv_accept  )  {
								   pCtx->pProcessQ->qRemoveMsg(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  );	//  ²»ÔÊÐí´«ËÍ					
		 						   }				 
							   else  {
					   
								     //  ¼ÓÈë¶ÓÁÐ¡£Ö»ÓÐ¶ÓÁÐÖÐµÄÏûÏ¢²ÅÊÇ¿ÉÒÔ´«µÝÊý¾ÝµÄ								   
								     if  (  pCtx->pProcessQ->qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  )  <=  0  )  {	
										 //
										 //  ÒªÊÇÔÚprocessQÀïÃ»ÓÐ£¬ÄÇÃ´¾Í¼ÓÈë¶ÓÁÐ; 
										 //
										 pMsg->idInfo_taskSender.ui64Id  =  pMsg->data.route.idInfo_to.ui64Id;
										 pMsg->idInfo_taskReceiver.ui64Id  =  pMsg->data.route.idInfo_from.ui64Id;
										 //
										 /*
										 if  (  pCtx->pProcessQ->qPostMsg(  pMsg,  lenInBytes_msg  )  )  {
											 traceLogA(  (char*)  "procMsgTask_mc_robot: 2. ÕâÀï¼Ó²»ÁËÈÎÎñÁË£¬Ó¦¸ÃÍ¨Öª¹ÜÀíÏß³Ì£¬ËµÈÎÎñ¶ÓÁÐÂúÁË¡£²»ÄÜÔÙ¼ÓÁË"  );
											 goto  errLabel;
										 }
										 */
										 traceLogA(  (char*) "findTask failed," );
										 goto errLabel;
									 }

									 //  2008/11/18
									 startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "send transferFileReply"  )  );
									 
							   }
							   break;
						 default:
							    traceLogA(  (char*)  "´íÎóµÄÊý¾Ý¸ñÊ½£ºpContent->uiType is %d",  pContent->uiType  );
								goto  errLabel;
							    break;
				 }
								 
				 //if  (  postMsg2Mgr_mc(  pMisCnt,  NULL,  pMsg->uiType,  pMsg->ucFlg,  pMsg->usCode,  pMsg->tStartTime,  pMsg->uiTranNo,  pMsg->usSeqNo,  pMsg->data.buf,  pMsg->lenInBytes  -  offsetof(  MIS_MSG_routeTalkData,  buf  ),  &pMsg->addr_logicalPeer.idInfo,  &pMsg->data.route.idInfo_to,  0,  NULL,  FALSE  )  )  goto  errLabel;
				 //  2015/09/06
				 if  (  procMsgTask2Output_mc(  pProcInfo,  (  MIS_CNT  *  )pMsg->pMisCnt,  pMsg,  lenInBytes_msg,  pChannel,  _T(  "thread_mgr"  )  )  )  goto  errLabel;


				 printMisMsg(  0,  0,  (  MIS_MSGU  *  )pMsg  );
				 
				 iErr  =  0;  goto  errLabel;
			 
			 }

	
		 			 
			 //  ·¢ËÍÎÄ¼þµÄ»Ø¸´°ü£¬´ÓmgrÖÐÀ´
			 if  (  bMsgInput  &&  pMsg->usCode  ==  CONST_qyCmd_sendRobotTaskReply  )  {
				 IM_SIMPLE_RESP			respSimple;

				 #ifndef  __NOTSUPPORT_DB__
		 				  CQnmDb					db;
						  if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
				 #endif

				 if  (  pContent->uiType  ==  CONST_imCommType_transferFileReplyReq  )  {
					 //  char					timeBuf[CONST_qyTimeLen  +  1]  =  "";

					 //  ¶Ô·½²»ÔÊÐí
					 if  (  pContent->transferFileReplyReq.usOp  !=  CONST_imOp_recv_accept  )  goto  errLabel;

					 #ifndef  __NOTSUPPORT_DB__
							  //  
							  if  (  !g_dbFuncs.pf_bGetImTaskRcdBySth(  db.m_pDbMem->pDb,  pQyMc->cfg.db.iDbType,  FALSE,  pMisCnt->cfg.misServName, &pMisCnt->idInfo, (  time_t  )pContent->transferFileReplyReq.tStartTime_org,  pContent->transferFileReplyReq.uiTranNo_org,  0,  &rcd  )  )  {
								  traceLogA(  (char*)  "procMsgTask_mc_robot failed: bGetImTaskRcdBySth failed"  );
								  goto  errLabel;
							  }
					 #endif

					 //
					 //printQ_mis(  &pCtx->pProcessQ->m_q,  0  );
					 //
					 printMisMsg(  0,  0,  (  MIS_MSGU  *  )pMsg  );

					 //  
					 if  (  pCtx->pProcessQ->qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  )  <=  0  )  {	  
						 traceLogA(  (char*)  "procMsgTask_mc_robot failed: "  );
						 //  postMsg2Mgr...
						 goto  errLabel;
					 }

					 //
					 showInfo_open0(0, 0, _T("procMsgTask_mc_robot_mgr: get fileReply"));

					}
				 else  {
					   traceLogA(  (char*)  "´íÎóµÄÊý¾Ý¸ñÊ½£ºpContent->uiType is %d",  pContent->uiType  );
					   goto  errLabel;
				 }					   
			
				 startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "recv transferFileReply"  )  );
				 

				 //
				 showInfo_open0(0, 0, _T("procMsgTask_mc_robot_mgr: send simpleResp for fileReply"));


				 //  ÏÂÃæ×¼±¸·¢ËÍ×¼±¸ºÃµÄÏìÓ¦°ü
				 usRespCode  =  CONST_qyRc_ok;
				 uiChannelType  =  0;//CONST_channelType_robot;
				 
				 MACRO_makeImSimpleResp(  pMsg->usCode,  pContent->uiType,  0,  respSimple  );

				 postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_outputTask,  CONST_commFlg_resp,  usRespCode,  pMsg->tStartTime,  pMsg->uiTranNo,  0,  pMsg->iTaskId,  pMsg->uiTaskType,  (  char  *  )&respSimple,  sizeof(  respSimple  ),  &pMsg->addr_logicalPeer.idInfo,  &pMsg->idInfo_taskSender,  &pMsg->idInfo_taskReceiver,  &pMsg->data.route.idInfo_from,  uiChannelType,  NULL,  FALSE  );     

				 iErr  =  0;  goto  errLabel;

			 }	//  

			 traceLogA(  (char*)  "procMsgTask_mc_robot:  Óöµ½ÁËÎÞ·¨½âÊÍµÄÇé¿ö£¬´íÎó"  );  goto  errLabel;
		 
	 
		}
	 else  {
		
		   printMisMsg(  0,  0,  (  MIS_MSGU  *  )pMsg  );

		   qyShowInfo1(  CONST_qyShowType_debug,  0, (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "µÃµ½%I64uµÄÏìÓ¦%s"  ),  pMsg->data.route.idInfo_from.ui64Id,  qyGetDesByType1(  CONST_qyRcTable,  pMsg->usCode  )  );

		   if  (  !isRcOk(  pMsg->usCode  )  )  goto  errLabel;

		   traceLogA(  (char*)  "procMsgTask_mc_robot:  ¶ÔÓÚÏìÓ¦°ü£¬»¹Ã»ÓÐ´¦ÀíÄØ"  );
	 }

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
#if  0	//  2014/07/13
		 pCtx->pProcessQ->qRemoveMsg(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  );
#endif
	 }

	 return  iErr;
}


///


//////////////////
//  2015/09/06
//  resp一般不涉及任务的初始化和终止，所以呢，就转发到相关处理线程去
//
 //  2015/09/06
 //int  procMsgInput_mgr_resp(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_INPUT  *  pMsgInput,  unsigned  int  lenInBytes_msg,  CTX_MC_THREAD  *  pCtx  )
int  procMsgInput_mgr_resp(  void  *  pQyMcParam,  void  *  pSgiParam,  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_INPUT  *  pMsgInput,  unsigned  int  lenInBytes_msg,  void  *  pCTX_MC_THREAD,  MIS_CHANNEL  *  pChannel  )
{
	 int						iErr			=	-1;
	 QY_MC					*	pQyMc			=	(  QY_MC  *  )pQyMcParam;
	 QY_SERVICEGUI_INFO		*	pSci			=	(  QY_SERVICEGUI_INFO  *  )pSgiParam;
	 CTX_MC_THREAD  *  pCtx  =  (  CTX_MC_THREAD  *  )pCTX_MC_THREAD;

	 //  int						dataLen			=	0;
	 int						msgLen			=	0;
	 MIS_CNT				*	pMisCnt			=	0;
	 //MIS_MSG_routeTalkData	*	pAddrTalkData	=	NULL;		
	 IM_CONTENTU			*	pContent		=	NULL;
	 //
	 if  (  !pCtx  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "procMsgInput_mgr_resp failed: pCtx is null"  );
		 #endif
		 return  -1;
	 }

	 //  CQyMalloc					mallocObj;
	 MIS_MSG_INPUT			*	pMsg			=	(  MIS_MSG_INPUT  *  )pCtx->pMsgBuf_forInput;	//  (  MIS_MSG_INPUT  *  )mallocObj.malloc(  sizeof(  MIS_MSG_INPUT  )  );
	 if  (  !pMsg  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "procMsgInput_mgr_resp failed: pMsgBuf is null"  );
		 #endif
		 return  -1;
	 }
	 //
	 TCHAR						tHintBuf[255  +  1]		=	_T(  ""  );
	 
	 if  (  !pMsgInput->pMisCnt  )  return  -1;
	 
	 if  (  sizeof(  pMsgInput->data  )  <  sizeof(  MIS_MSG_routeTalkData  )  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "procMsgInput_mgr_resp:  pMsgInput->buf µÄ´óÐ¡ {%d} Ã»ÓÐ >=  sizeof(  MIS_MSG_routeTalkData  ) {%d}",  sizeof(  pMsgInput->data  ),  sizeof(  MIS_MSG_routeTalkData  )  );
		 #endif
		 goto  errLabel;
	 }

	 pMisCnt  =  (  MIS_CNT  *  )pMsgInput->pMisCnt;

	 if  (  !isUcFlgResp(  pMsgInput->ucFlg  )  )  goto  errLabel;
	 
	 //  traceLogA(  (char*)  ""  );
	 if  (  !pMsgInput->ucbConvrted  )  {
	 
		 MACRO_memset_misMsgInput(  pMsg  );
		 memcpy(  pMsg,  pMsgInput,  offsetof(  MIS_MSG_INPUT,  data  )  );  
		 msgLen  =  offsetof(  MIS_MSG_INPUT,  data  );

		 if  (  
			 //isUcFlgTalkData(  pMsgInput->ucFlg  )  ||  
			 isUcFlgRouteTalkData(  pMsgInput->ucFlg  )  )  
		 {
			 MIS_MSG_routeTalkData  *  pAddrTalkData	=	(  MIS_MSG_routeTalkData  *  )&pMsg->data;
			 //
			 if  (  qyntohRouteTalkData(  pMsgInput->ucFlg,  (  char  *  )&pMsgInput->data,  pMsgInput->lenInBytes,  &pAddrTalkData->route,  (  IM_CONTENTU  *  )pAddrTalkData->buf,  tHintBuf,  mycountof(  tHintBuf  )  )  )  goto  errLabel;    
			 if  (  tHintBuf[0]  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    %s"  ),  tHintBuf  );
			 //
			 msgLen  +=  offsetof(  MIS_MSG_routeTalkData,  buf  );
			 pContent  =  (  IM_CONTENTU  *  )pAddrTalkData->buf;				
			}
		 else  {
			   if  (  !pMsgInput->lenInBytes  )  {
				   #ifdef  __DEBUG__
						   traceLogA(  (char*)  "procMsgInput_mgr_resp failed: msgInput.lenInBytes is 0"  );
				   #endif
				   goto  errLabel;
			   }

			   if  (  qyntohRouteTalkData(  pMsgInput->ucFlg,  (  char  *  )&pMsgInput->data,  pMsgInput->lenInBytes,  NULL,  (  IM_CONTENTU  *  )&pMsg->data,  tHintBuf,  mycountof(  tHintBuf  )  )  )  goto  errLabel;    
			   if  (  tHintBuf[0]  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    %s"  ),  tHintBuf  );
			   //
			   pContent  =  (  IM_CONTENTU  *  )&pMsg->data;				
		 }
		 pMsg->ucbConvrted  =  TRUE;

		 //	
		 pMsgInput  =  pMsg;
	 }

	 //
#if  0
	 pAddrTalkData  =  MACRO_msgRouteTalkData(  pMsgInput->ucFlg,  &pMsgInput->data  );
	 if  (  !pAddrTalkData  )  {
		 #ifdef  __DEBUG__
				 MACRO_qyAssert(  0,  _T(  "procMsgInput_mgr_resp failed: pAddrTalkData is null"  )  );  
		 #endif
		 goto  errLabel;
	 }
#endif

	 //
	 pContent  =  M_getMsgContent(  pMsgInput->ucFlg,  &pMsgInput->data  );
	 if  (  !pContent  )  {
		 #ifdef  __DEBUG__
				 MACRO_qyAssert(  0,  _T(  "procMsgInput_mgr_resp failed: pContent is null"  )  );  
		 #endif
		 goto  errLabel;
	 }

	 //
#ifdef  __DEBUG__
	 if (pContent->uiType == CONST_imCommType_confReq) {
		 int  ii = 0;
	 }
#endif 


	 //
	 BOOL  bNeedProcess; bNeedProcess = FALSE;
	 
	 //  ÏÂÃæ´¦ÀíÏìÓ¦
	 //	
	 switch  (  pContent->uiType  )  {
 			 case  CONST_imCommType_simpleResp:  {  
				   //
				   qyShowInfo1(  CONST_qyShowType_debug,  0, (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "procMsgInput_mgr_resp: simpleResp¦%d, %s,  %d"  ),  pContent->simpleResp.uiContentType_org,  qyGetDesByType1(  CONST_qyRcTable,  pMsgInput->usCode  ),  pMsgInput->uiTranNo  );

				   //
				   if  (  !pCtx->pProcessQ  )  goto  errLabel;
				   
				   //
				   if (pMsg->uiTranNo == 543) {
					   int  ii = 0;
				   }

				   //
				   msgLen  +=  sizeof(  pContent->simpleResp  );
				   switch  (  pContent->simpleResp.usCmd_org  )  {
						   case  CONST_qyCmd_sendRobotTaskReply:
							     qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->robotQ,  _T(  "procMsgInput_mgr_resp"  ));
							     break;
						   case  CONST_qyCmd_sendMedia:  {
							     CQyQ2Help	q2Help;

							     q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->mediaQ2,  _T(  "procMsgInput_mgr_resp 1"  ));
								 }
							     break;

						   case  CONST_qyCmd_refreshImObjListReq:
							     qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->schedulerQ,  _T(  "procmsgInput_mgr_resp 3"  ));
							     break;
						   default:
								  //
								  bNeedProcess  =  TRUE;

								  #ifdef  __DEBUG__
										  traceLogA(  (char*)  "procMsgInput_mgr_resp: simpleResp, unprocessed cmd %S",  qyGetDesByType1(  CONST_qyCmdTable,  pContent->simpleResp.usCmd_org  )  );
								  #endif
								  break;
				   }

				   }
				   break;
				   
			 case  CONST_imCommType_taskProcResp:  {
				 
				   msgLen  +=  sizeof(  pContent->taskProcResp  );
				   switch  (  pContent->taskProcResp.usCmd_org  )  {
						   case  CONST_qyCmd_sendMedia:
							     q2PostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->mediaQ2,  _T(  "proMsgInput_mgr_resp 1"  ));
								 break;
						   default:
								  //
								  bNeedProcess  =  TRUE;

								  #ifdef  __DEBUG__
										  traceLogA(  (char*)  "procMsgInput_mgr_resp: taskProcResp, unprocessed cmd %S",  qyGetDesByType1(  CONST_qyCmdTable,  pContent->taskProcResp.usCmd_org  )  );
								  #endif
								  break;
				   }

				   }
				   break;

			 //  case  CONST_imCommType_intervalParams:
			 case  CONST_imCommType_getCfgsReq:
				   if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;
				   //
				   msgLen  +=  sizeof(  pContent->getCfgsReq  );
				   //
				   if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->schedulerQ,  _T(  "procMsgInput_mgr_resp 3"  ))) {
					   traceLogA(  (char*)  "qPostMsgAndTrigger failed"  );  goto  errLabel;
				   }
				   //
				   break;
			 case  CONST_imCommType_retrieveToPaths:
				   if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;
				   //
				   msgLen  +=  sizeof(  pContent->retrieveToPaths  );
				   //
				   if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->schedulerQ,  _T(  "procMsgInput_mgr_resp 2"  ))) {
					   traceLogA(  (char*)  "qPostMsgAndTrigger failed"  );  goto  errLabel;
				   }
				   //
				   break;

			 case  CONST_imCommType_retrieveImGrpListResp:
				   if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;
				   //
				   msgLen  +=  sizeof(  pContent->retrieveImGrpListResp  );				   
				   //
				   if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->schedulerQ,  _T(  "procMsgInput_mgr_resp 3"  ))) {
					   traceLogA(  (char*)  "qPostMsgAndTrigger failed"  );  goto  errLabel;
				   }
				   break;
			 case  CONST_imCommType_retrieveImGrpMemListResp:
				   if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;
				   //
				   msgLen  +=  sizeof(  pContent->retrieveImGrpMemListResp  );				   
				   //
				   if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->schedulerQ,  _T( "procMsgInput_mgr_resp 7"  ))) {
					   traceLogA(  (char*)  "qPostMsgAndTrigger failed"  );  goto  errLabel;
				   }				   
				   break;
			 case  CONST_imCommType_retrieveContactListResp:
				   if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;
				   //
				   msgLen  +=  sizeof(  pContent->retrieveContactListResp  );				   
				   //
				   if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->schedulerQ,  _T(  "procMsgInput_mgr_resp 8"  ))) {
					   traceLogA(  (char*)  "qPostMsgAndTrigger failed"  );  goto  errLabel;
				   }
				   break;
			 case  CONST_imCommType_retrieveImObjListEndResp:
				   if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;
				   //
				   msgLen  +=  sizeof(  pContent->retrieveImObjListEndResp  );				   
				   //
				   if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->schedulerQ,  _T(  "procMsgInput_mgr_resp 9"  ))) {
					   traceLogA(  (char*)  "qPostMsgAndTrigger failed"  );  goto  errLabel;
				   }		
				   break;
			 case  CONST_imCommType_refreshRecentFriendsResp:  				   
				   if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;
				   //
				   msgLen  +=  sizeof(  pContent->refreshRecentFriendsResp  );
				   //
				   if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->displayQ,  _T(  "procMsgInput_mgr_resp 1"  ))) {
					   traceLogA(  (char*)  "qPostMsgAndTrigger failed"  );  goto  errLabel;
				   }
				   break;
			 case  CONST_imCommType_refreshWebContactsInfo:
				   if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;
				   //
				   msgLen  +=  sizeof(  pContent->refreshWebContactsInfo  );
				   //
				   if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->workQ,  _T(  "procMsgInput_mgr_resp 3"  )))  goto  errLabel;

				   break;
			 case  CONST_imCommType_htmlContent:
				   if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;

				   //  qyShowInfo1(  CONST_qyShowType_debugWarning,  0,  (  ""  ),  pProcInfo->who_showInfo,  _T(  ""  ),  _T(  "procMsgInput_mgr_resp"  ),  _T(  "resp of html. %s"  ),  CQyString(  (  char  *  )&pMsgInput->data  )  );

				   //  2014/07/12
				   msgLen  +=  sizeof(  pContent->html  );
				   //
				   if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->workQ,  _T(  "procMsgInput_mgr_resp 8"  )))  goto  errLabel;
	   
				   break;			 
			 case  CONST_imCommType_vDevComs:
				   if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;
				   //
				   msgLen  +=  sizeof(  pContent->vDevComs  );
				   //
				   if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->workQ,  _T(  "procMsgInput_mgr_resp 11"  )))  goto  errLabel;
 
				   break;
			 case  CONST_imCommType_retrieveSmPolicy:
				   if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;
				   //
				   msgLen  +=  sizeof(  pContent->retrieveSmPolicy  );
				   //
				   if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->workQ,  _T(  "procMsgInput_mgr_resp 1"  )))  goto  errLabel;

				   break;
			 case  CONST_imCommType_retrievePhoneMsgrs:
				   if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;
				   //
				   msgLen  +=  sizeof(  pContent->retrievePhoneMsgrs  );
				   //
				   if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->schedulerQ,  _T(  "procMsgInput_mgr_resp 2"  )))  goto  errLabel;
                   
				   break;
				   //
				   //
			 case  CONST_imCommType_refreshDynBmps:		//  2009/08/31
				   if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;
				   //
				   msgLen  +=  sizeof(  pContent->refreshDynBmps  );
				   //
				#if  0	//  2011/10/31. 直接发到gui比较简洁
				   if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->workQ  )  )  goto  errLabel;				  
				#endif

				   qPostMsg(  pMsg,  msgLen,  &pQyMc->gui.processQ,  _T(  "procMsgInput_mgr_resp 2"  ));
				   PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    
				   break;
			 case  CONST_imCommType_verifyViewDynBmp:		//  2011/10/31
				   if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;
				   //
				   msgLen  +=  sizeof(  pContent->verifyViewDynBmp  );
				   
				   //
				   qPostMsg(  pMsg,  msgLen,  &pQyMc->gui.processQ,  _T(  "procMsgInput_mgr_resp 2"  ));
				   PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    
				   break;
			 case  CONST_imCommType_retrieveDynBmps:	//  2009/09/05
				   if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;
				   //
				   msgLen  +=  sizeof(  pContent->retrieveDynBmps  );
				   
				   //
				   if  (  
					   //isUcFlgTalkData(  pMsgInput->ucFlg  )  ||  
					   isUcFlgRouteTalkData(  pMsgInput->ucFlg  )  
					   )  
				   {
					   //
					   qPostMsg(  pMsg,  msgLen,  &pQyMc->gui.processQ,  _T(  "procMsgInput_mgr_resp 1"  ));
					   PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    
					   break;
				   }
				   //
				   if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->schedulerQ,  _T(  "procMsgInput_mgr_resp 1"  )))  goto  errLabel;
				   break;
			 case  CONST_imCommType_refreshImObjRulesReq:	//  2010/08/15
				   if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;
				   //
				   msgLen  +=  sizeof(  pContent->refreshImObjRulesReq  );
				   //
				   if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->schedulerQ,  _T(  "procmsgInput_mgr_resp 22"  )))  goto  errLabel;
				   break;
			 case  CONST_imCommType_retrieveCustomerServiceObjListReq:		//  2011/04/04
				   if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;
				   //
				   msgLen  +=  sizeof(  pContent->retrieveCustomerServiceObjListReq  );
				   //
				   qPostMsg(  pMsg,  msgLen,  &pQyMc->gui.processQ,  _T(  "procMsgInput_mgr_resp 23"  ));
				   PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    
				   break;
			 case  CONST_imCommType_procOfflineRes:  //  2015/08/02
				   //if  (  !isRcOk(  pMsgInput->usCode  )  )  goto  errLabel;
				   //
				   msgLen  +=  sizeof(  pContent->procOfflineResU  );
				   //
				   //
				   if  (  
					   //isUcFlgTalkData(  pMsgInput->ucFlg  )  ||  
					   isUcFlgRouteTalkData(  pMsgInput->ucFlg  )  )  {
					   //
					   qPostMsg(  pMsg,  msgLen,  &pQyMc->gui.processQ,  _T(  "procmsgInput_mgr_resp 12"  ));
					   PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    
					   break;
				   }
				   //
				   if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->schedulerQ,  _T(  "procMsgInput_mgr_resp 14"  )))  goto  errLabel;
				   break;
			 case  CONST_imCommType_imGrp:  //  2017/07/26
				   msgLen  +=  sizeof(  pContent->imGrpEx  );
				   //
				   qPostMsg(  pMsg,  msgLen,  &pQyMc->gui.processQ,  _T(  "procmsgInput_mgr_resp 222"  ));
				   PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    				   
				   break;
			 case  CONST_imCommType_qisCaReq: {
				   //
				   int  ii = 0;
				   //pProcInfo->update_serv_ca_sendData(&pContent->qisCaReq);
				   //
				   }
				   break;
			 case  CONST_imCommType_confReq:
				 msgLen += sizeof(pContent->confReq);
				 //
				 qPostMsg(pMsg, msgLen, &pQyMc->gui.processQ, _T("procmsgInput_mgr_resp 222"));
				 PostMessage(pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);

				 break;
			 case  CONST_imCommType_taskInteractionReq: {
				 
				 msgLen += sizeof(pContent->taskInteractionReq);
				 //
				 qPostMsg(pMsg, msgLen, &pQyMc->gui.processQ, _T("procmsgInput_mgr_resp 1845"));
				 PostMessage(pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);

				 }
				 break;
			 default:
				    //
				    bNeedProcess  =  TRUE;
					//
	   				break;
	 }
	 //
	 if  (  !bNeedProcess  )  {
		 iErr  =  0;  goto  errLabel;
	 }

	 //
	 switch  (  pContent->uiType  )  {
		 		
			 case  CONST_imCommType_simpleResp:  {  
				   //
				   qyShowInfo1(  CONST_qyShowType_debug,  0, (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "    simpleResp¦%s,  %d"  ),  qyGetDesByType1(  CONST_qyRcTable,  pMsgInput->usCode  ),  pMsgInput->uiTranNo  );

				   msgLen  +=  sizeof(  pContent->simpleResp  );
				   switch  (  pContent->simpleResp.usCmd_org  )  {
						   case  CONST_qyCmd_sendRobotTaskReply:
							     qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->robotQ,  _T(  "procMsgInput_mgr_resp 234"  ));
							     break;
						   case  CONST_qyCmd_sendMedia:  {
							     CQyQ2Help	q2Help;

							     q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->mediaQ2,  _T(  "procMsgInput_mgr_resp 34"  ));
								 }
							     break;
						   case  CONST_qyCmd_refreshImObjListReq:
							     qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->schedulerQ,  _T(  "procMsgInput_mgr_resp 35"  ));
							     break;
						   default:
								  #ifdef  __DEBUG__
										  traceLogA(  (char*)  "procMsgInput_mgr_resp: simpleResp, unprocessed cmd %S",  qyGetDesByType1(  CONST_qyCmdTable,  pContent->simpleResp.usCmd_org  )  );
								  #endif
								  break;
				   }

				   }
				   break;

			 case  CONST_imCommType_taskProcResp:  {	//  2009/10/19

				   msgLen  +=  sizeof(  pContent->taskProcResp  );
				   switch  (  pContent->taskProcResp.usCmd_org  )  {
						   case  CONST_qyCmd_sendMedia:
							     q2PostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->mediaQ2,  _T(  "procMsgInput_mgr_resp 45"  ));
								 break;
						   default:
							       traceLogA(  (char*)  "procMsgInput_mgr_resp: taskProcResp, unprocessed cmd %S",  qyGetDesByType1(  CONST_qyCmdTable,  pContent->taskProcResp.usCmd_org  )  );
								   break;
				   }

				   }
				   break;
			 case  CONST_imCommType_transferFileDataResp:
				   //
				   msgLen  +=  sizeof(  pContent->transferFileDataResp  );
				   //
				   if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->robotQ,  _T(  "procMsgInput_mgr_resp 890"  )))  goto  errLabel;

				   break;


			 default:
				    //
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "procMsgInput_mgr_resp(  ):  unprocessed imCommType[%d] - %s"  ),  pContent->uiType,  qyGetDesByType1(  CONST_qyCmdTable,  pMsgInput->usCode_org  )  );
					#endif
					qyShowInfo1(  CONST_qyShowType_debugWarning,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  _T(  ""  ),  _T(  ""  ),  _T(  ""  ),  _T(  "procMsgInput_mgr_resp: unprocessed imCommType %d - %s"  ),  pContent->uiType,  qyGetDesByType1(  CONST_qyCmdTable,  pMsgInput->usCode_org  )  );
					//
					break;
	 }



	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
	 }
	 return  iErr;
}


 //int  procMsgInput_mgr_req(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_INPUT  *  pMsgInput,  unsigned  int  lenInBytes_msg,  CTX_MC_THREAD  *  pCtx  )
 int  procMsgInput_mgr_req(  void  *  pQyMcParam,  void  *  pSgiParam,  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_INPUT  *  pMsgInput,  unsigned  int  lenInBytes_msg,  void  *  pCTX_MC_THREAD,  MIS_CHANNEL  *  pChannel  )
{
	int				iErr		=	-1;
	QY_MC					*	pQyMc			=	(  QY_MC  *  )pQyMcParam;	
	QY_SERVICEGUI_INFO		*	pSci			=	(  QY_SERVICEGUI_INFO  *  )pSgiParam;
	CTX_MC_THREAD  *  pCtx  =  (  CTX_MC_THREAD  *  )pCTX_MC_THREAD;

	QM_dbFuncs* pDbFuncs; pDbFuncs = pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  return  -1;// goto  errLabel;
	QM_dbFuncs& g_dbFuncs = *pDbFuncs;

	int				len;
	//
	TCHAR			tHintBuf[255  +  1]		=	_T(  ""  );
	TCHAR			tBuf[128]				=	_T(  ""  );

	if  (  !pCtx  )  {
		#ifdef  __DEBUG__
				traceLogA(  (char*)  "procMsgInput_mgr_req failed: pCtx is null"  );
		#endif
		return  -1;
	}

	if  (  isUcFlgResp(  pMsgInput->ucFlg  )  )  return  -1;
	
	//  
	#ifdef  __DEBUG__
			if  (  pProcInfo->cfg.debugStatusInfo.bDbgDetail){
				traceLogA(  (char*)  "procMsgInput_mgr_req: %S",  qyGetDesByType1(  CONST_qyCmdTable,  pMsgInput->usCode  )  );
			}
	#endif

	//  2017/10/11  
	if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewMgrStatus  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "procMsgInput_mgr_req: tn %d"  ),  pMsgInput->uiTranNo  );
		showInfo_open0(  0,  0,  tBuf  );
	}

	//	
	//  2015/09/07
	BOOL  bNeedProcess  =  FALSE;
				  
	//
	switch  (  pMsgInput->usCode  )  {
			case  CONST_qyCmd_talkTo:  {
				  //  CQyMalloc		mallocObj;
				  MIS_MSGU	*	pMsg		=	pCtx->pMsgBuf_forInput;	//  (  MIS_MSGU  *  )mallocObj.malloc(  sizeof(  MIS_MSGU  )  );
				  if  (  !pMsg  )  {
					  #ifdef  __DEBUG__
							  traceLogA(  (char*)  "procMsgInput_mgr_req failed: pMsgBuf is null"  );
					  #endif
					  goto  errLabel;
				  }

				  MACRO_memset_misMsg(  pMsg  );
	
				  pMsg->talk.uiType  =  CONST_misMsgType_talk;
				  pMsg->talk.ucFlg  =  pMsgInput->ucFlg;
				  //
				  pMsg->talk.usCode  =  pMsgInput->usCode;
				  pMsg->talk.tStartTime  =  pMsgInput->tStartTime;
				  pMsg->talk.uiTranNo  =  pMsgInput->uiTranNo;
				  pMsg->talk.usSeqNo  =  pMsgInput->usSeqNo;
				  //
				  pMsg->talk.pMisCnt  =  pMsgInput->pMisCnt;
				  //
				  pMsg->talk.tRecvTime  =  pMsgInput->tRecvTime;
				  //				  
				  if  (  qyntohRouteTalkData(  pMsgInput->ucFlg,  (  char  *  )&pMsgInput->data,  pMsgInput->lenInBytes,  &pMsg->talk.data.route,  (  IM_CONTENTU  *  )pMsg->talk.data.buf,  tHintBuf,  mycountof(  tHintBuf  )  )  )  {
					  showInfo_open0(  0,  0,  _T(  "procMsgInput_mgr_req failed, qyntohRouteTalkData failed"  )  );
					  goto  errLabel;
				  }
				  if  (  tHintBuf[0]  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    %s"  ),  tHintBuf  );

				  IM_HTML_CONTENT  *  pHtmlContent;

				  pHtmlContent  =  (  IM_HTML_CONTENT  *  )pMsg->talk.data.buf;
				  len  =  offsetof(  IM_HTML_CONTENT,  wBuf  )  +  min(  sizeof(  pHtmlContent->wBuf  ),  (  _tcslen(  pHtmlContent->wBuf  )  +  1  )  *  sizeof(  pHtmlContent->wBuf[0]  )  );
				  //
				  {				    
					  #ifdef  __DEBUG__
							  traceLogA(  (char*)  "talk str is [%S]",  pHtmlContent->wBuf  );
					  #endif
				  }
				  //
				  pMsg->talk.lenInBytes  =  len  +  offsetof(  MIS_MSG_routeTalkData,  buf  );
				  len  =  pMsg->talk.lenInBytes  +  offsetof(  MIS_MSG_TALK,  data  );
				  if  (  qPostMsgAndTrigger(  pMsg,  len,  &pProcInfo->workQ,  _T(  "procMsgInput_mgr_req"  )))  goto  errLabel;
				  
				  }
				  break;
			case  CONST_qyCmd_sendTask:  
			case  CONST_qyCmd_sendTaskReply:  
				  
				  if  (  qPostMsgAndTrigger(  pMsgInput,  lenInBytes_msg,  &pProcInfo->workQ,  _T(  "procMsgInput_mgr_req"  )))  goto  errLabel;
				  				  
			      break;

			default:
					bNeedProcess  =  TRUE;
					break;
	}
	if  (  !bNeedProcess  )  {
		iErr  =  0;  goto  errLabel;
	}

				  
	//
	MIS_CNT* pMisCnt; pMisCnt = 0;
	MIS_MSG_routeTalkData* pAddrTalkData; pAddrTalkData = NULL;
	int						msgLen; msgLen = 0;
	IM_CONTENTU* pContent; pContent = NULL;

	//  CQyMalloc					mallocObj;	
	MIS_MSG_INPUT* pMsg; pMsg = (MIS_MSG_INPUT*)pCtx->pMsgBuf_forInput;	//  (  MIS_MSG_INPUT  *  )mallocObj.malloc(  sizeof(  MIS_MSG_INPUT  )  );
	if  (  !pMsg  )  {
		#ifdef  __DEBUG__
			    traceLogA(  (char*)  "procMsgInput_mgr_req failed: pMsgBuf is null"  );
		#endif
		 goto  errLabel;		
	}				 
	
	//
	int							lenInBytes; lenInBytes = 0;
	//
	BOOL						bRemoveIfErr; bRemoveIfErr = TRUE;
	//  2008/11/19
	MSG_ROUTE					route;
	unsigned  char				ucFlg; ucFlg = 0;


					 
	if  (  !pMsgInput->pMisCnt  )  return  -1;
		
	if  (  sizeof(  pMsgInput->data  )  <  sizeof(  MIS_MSG_routeTalkData  )  )  {
		#ifdef  __DEBUG__	
				traceLogA(  (char*)  "procMsgInput_mgr_resp:  pMsgInput->buf µÄ´óÐ¡ {%d} Ã»ÓÐ >=  sizeof(  MIS_MSG_routeTalkData  ) {%d}",  sizeof(  pMsgInput->data  ),  sizeof(  MIS_MSG_routeTalkData  )  );
		#endif
		goto  errLabel;	
	}
					  
	pMisCnt  =  (  MIS_CNT  *  )pMsgInput->pMisCnt;
		
	if  (  isUcFlgResp(  pMsgInput->ucFlg  )  )  goto  errLabel;
					 
	//  traceLogA(  (char*)  ""  );
		
	if  (  !pMsgInput->ucbConvrted  )  {

				  MACRO_memset_misMsgInput(  pMsg  );
				  memcpy(  pMsg,  pMsgInput,  offsetof(  MIS_MSG_INPUT,  data  )  );  
				  msgLen  =  offsetof(  MIS_MSG_INPUT,  data  );

				  if  (  
					  //isUcFlgTalkData(  pMsgInput->ucFlg  )  ||  
					  isUcFlgRouteTalkData(  pMsgInput->ucFlg  )  )  {
					  pAddrTalkData	=	(  MIS_MSG_routeTalkData  *  )&pMsg->data;
					  //
					  if  (  qyntohRouteTalkData(  pMsgInput->ucFlg,  (  char  *  )&pMsgInput->data,  pMsgInput->lenInBytes,  &pAddrTalkData->route,  (  IM_CONTENTU  *  )pAddrTalkData->buf,  tHintBuf,  mycountof(  tHintBuf  )  )  )  {
						  showInfo_open0(  0,  0,  _T(  "procMsgInput_mgr_req failed, qyntohRouteTalkData failed"  )  );
						  goto  errLabel;    
					  }
					  if  (  tHintBuf[0]  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    %s"  ),  tHintBuf  );
					  //
					  msgLen  +=  offsetof(  MIS_MSG_routeTalkData,  buf  );
					  //
					  pContent  =  (  IM_CONTENTU  *  )pAddrTalkData->buf;				
					  }
				  else  {
					    if  (  !pMsgInput->lenInBytes  )  {
							#ifdef  __DEBUG__
									traceLogA(  (char*)  "procMsgInput_mgr_req failed, msgInput.lenInBytes is 0"  );
							#endif
							goto  errLabel;
						}

						if  (  qyntohRouteTalkData(  pMsgInput->ucFlg,  (  char  *  )&pMsgInput->data,  pMsgInput->lenInBytes,  NULL,  (  IM_CONTENTU  *  )&pMsg->data,  tHintBuf,  mycountof(  tHintBuf  )  )  )  {
							showInfo_open0(  0,  0,  _T(  "procMsgInput_mgr_req failed, qyntohRouteTalkData failed sssssss"  )  );						  
							goto  errLabel;    
						}
						if  (  tHintBuf[0]  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    %s"  ),  tHintBuf  );
						//
						pContent  =  (  IM_CONTENTU  *  )&pMsg->data;				
				  }
				  pMsg->ucbConvrted  =  TRUE;

				  //
				  pMsgInput  =  pMsg;

	}
	
	 //
	 pContent  =  M_getMsgContent(  pMsgInput->ucFlg,  &pMsgInput->data  );
	 if  (  !pContent  )  {
		 #ifdef  __DEBUG__
				 MACRO_qyAssert(  0,  _T(  "procMsgInput_mgr_req failed, pContent is null"  )  );
		 #endif
		 goto  errLabel;
	 }


	 //  2017/10/11  
	if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewMgrStatus  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "procMsgInput_mgr_req: tn %d. after ntoh"  ),  pMsgInput->uiTranNo  );
		showInfo_open0(  0,  0,  tBuf  );
	}


	//
#ifdef  __DEBUG__
	if (pContent->uiType == CONST_imCommType_taskProcReq) {
		int  ii = 0;
		//
		if (pContent->taskProcReq.usOp == CONST_imOp_ping) {
			int  ii = 0;
			//
			traceLog((TCHAR*)_T("get ping from %I64u"), pMsgInput->data.route.idInfo_from.ui64Id);
		}
		if (pContent->taskProcReq.usOp == CONST_imOp_recv_applyForOrgReq) {
			int  ii = 0;
		}
	}
	if (pContent->uiType == CONST_imCommType_confReq) {
		int  ii = 0;
	}

#endif 


	//
	if  (  
		//!isUcFlgTalkData(  pMsgInput->ucFlg  )  &&  
		!isUcFlgRouteTalkData(  pMsgInput->ucFlg  )  )  {
		int  ii  =  0;
		//
		switch  (  pContent->uiType  )  {
				case  CONST_imCommType_confReq:
					  //
					  pMsgInput->lenInBytes = min(sizeof(pMsgInput->data), offsetof(MIS_MSG_routeTalkData, buf) + sizeof(CONF_req));
					  //
					  len = offsetof(MIS_MSG_INPUT, data) + pMsgInput->lenInBytes;

					  //						
					  if  (  qPostMsg(  pMsgInput,  len,  &pQyMc->gui.processQ,  _T(  "procMsgInput_mgr_req 22"  ))) {
							  traceLogA(  (char*)  "mcThreadProc_mis_work(  ): qPostMsg(  ) failed"  );
							  goto  errLabel;				  
						
					  }						
					  PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    

					  break;
				case  CONST_imCommType_mcuCmd:
					  //
					  if  (  !pQyMc->appParams.bMcu  )  {
						  showInfo_open0(  0,  0,  _T(  "procMsgInput_mgr_req failed: from serv, mcuCmd. I am not a mcu"  )  ); 
						  goto  errLabel;
					  }
					  if  (  memcmp(  &pProcInfo->cfg.debugStatusInfo,  &pContent->mcuCmd.debugStatusInfo,  sizeof(  pProcInfo->cfg.debugStatusInfo  )  )  )  {
						  pProcInfo->cfg.debugStatusInfo  =  pContent->mcuCmd.debugStatusInfo;
					  }
					  if  (  !pQyMc->env.bDebugInfo  )  pQyMc->env.bDebugInfo  =  true;
					  pProcInfo->cfg.dwRefreshedTickCnt_debugStatusInfo  =  myGetTickCount(  NULL  );
					  //
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "procMsgInput_mgr_req: mcuCmd recvd"  )  );
					  #ifdef  __DEBUG__
							  traceLog((TCHAR*)  tBuf  );
					  #endif
					  showInfo_open0(  0,  0,  tBuf  );  
					  //
					  break;
				case  CONST_imCommType_qisCaReq:
					  //
					  pProcInfo->sxrz_yq(&pContent->qisCaReq);
					  //
					  break;
				default:
					    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "procMsgInput_mgr_req: from serv, unprocessed contentType %d"  ),  pContent->uiType  );
						showInfo_open0(  0,  0,  tBuf  );
						goto  errLabel;
						break;
		}

		//
		iErr  =  0;  goto  errLabel;
	}



	//
	pAddrTalkData  =  MACRO_msgRouteTalkData(  pMsgInput->ucFlg,  &pMsgInput->data  );	
	if  (  !pAddrTalkData  )  {
		 #ifdef  __DEBUG__
				 MACRO_qyAssert(  0,  _T(  "procMsgInput_other_req failed: pAddrTalkData null"  )  );  
		 #endif
		 goto  errLabel;
	 
	}
	
	//
	bNeedProcess  =  FALSE;

	//
	switch  (  pContent->uiType  )  {
			case  CONST_imCommType_transferFileReq:  {
			      TRANSFER_FILE_REQ  *  pReq  =  NULL;
				  //
				  pMsgInput->lenInBytes  =  min(  sizeof(  pMsgInput->data  ),  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  sizeof(  TRANSFER_FILE_REQ  )  );
				  //
				  pReq  =  (  TRANSFER_FILE_REQ  *  )&pContent->transferFileReq;
				  //
				  //  ÏÂÃæÊÇÄÚ²¿´¦Àí±äÁ¿
				  lstrcpyn(  pReq->fullFilePath,  pReq->fileName,  mycountof(  pReq->fullFilePath  )  );
				  //
				  pMsgInput->uiType  =  CONST_misMsgType_task;
				  //
				  pMsgInput->idInfo_taskSender.ui64Id  =  pAddrTalkData->route.idInfo_from.ui64Id;
				  pMsgInput->idInfo_taskReceiver.ui64Id  =  pAddrTalkData->route.idInfo_to.ui64Id;
				  //
				  len  =  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgInput->lenInBytes;
				  //
				  if  (  procMsgTask_mc_mgr(  pQyMc,  pSci,  pProcInfo,  pMsgInput,  len,  TRUE,  pCtx,  pChannel  )  )  goto  errLabel;
				  }
				  break;
				  			
			case  CONST_imCommType_transferFileReplyReq:  {
				  TRANSFER_FILE_REPLYREQ  *  pReq  =  NULL;
				  //
				  pMsgInput->lenInBytes  =  min(  sizeof(  pMsgInput->data  ),  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  sizeof(  TRANSFER_FILE_REPLYREQ  )  );
				  //
				  pReq  =  (  TRANSFER_FILE_REPLYREQ  *  )&pContent->transferFileReplyReq;
				  //
				  pMsgInput->uiType  =  CONST_misMsgType_task;
				  //
				  pMsgInput->idInfo_taskSender.ui64Id  =  pAddrTalkData->route.idInfo_to.ui64Id;
				  pMsgInput->idInfo_taskReceiver.ui64Id  =  pAddrTalkData->route.idInfo_from.ui64Id;
				  //
				  len  =  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgInput->lenInBytes;

				  if  (  procMsgTask_mc_mgr(  pQyMc,  pSci,  pProcInfo,  pMsgInput,  len,  TRUE,  pCtx,  pChannel  )  )  goto  errLabel;
				  }
				  break;
			case  CONST_imCommType_transferFileDataReq:  {				
				  
				  msgLen  +=  sizeof(  pContent->transferAudioData  );					
				  if  (  qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->robotQ,  _T(  "procmsgInput_mgr_req 22"  )))  goto  errLabel;

#if  0
				  //  TRANSFER_FILEDATA_REQ		req;
				  //
				  //  memset(  &req,  0,  sizeof(  req  )  );
				  //  if  (  stream2Data(  &ptr,  &size,  tmpHandler_stream2TransferFileDataReq,  0,  &req  )  )  goto  errLabel;
				  //  memcpy(  pContent,  &req,  min(  sizeof(  pContent[0]  ),  sizeof(  req  )  )  );
				  // 
				  pMsgInput->lenInBytes  =  min(  sizeof(  pMsgInput->data  ),  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  sizeof(  TRANSFER_FILEDATA_REQ  )  );

				  TRANSFER_FILEDATA_RESP		resp;
				  //
				  memset(  &resp,  0, sizeof(  resp  )  );
				  resp.uiType  =  CONST_imCommType_transferFileDataResp;

				  if  (  !pCtx->pProcessQ  )  goto  errLabel;
				  printQ_mis(  &pCtx->pProcessQ->m_q,  0  );
				  traceLogA(  (char*)  "Now print pMsgInput"  );
				  printMisMsg(  0,  0,  (  MIS_MSGU  *  )pMsgInput  );

				  if  (  pCtx->pProcessQ->qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsgInput,  &resp  )  <=  0  )  {
					  traceLogA(  (char*)  "Ã»ÓÐÕÒµ½Ïà¹ØµÄÈÎÎñ½Úµã»ò´¦Àí³ö´í£¬²»ÄÜ¼ÌÐø"  );
					  goto  errLabel;				   
				  }
				  lenInBytes  =  sizeof(  resp  );
				  
				  //  2009/02/25
				  startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "proc transferFileDataReq"  )  );    

				  //
				  ucFlg  =  0;
				  memset(  &route,  0,  sizeof(  route  )  );
				  route.idInfo_from.ui64Id  =  pMisCnt->idInfo.ui64Id;
				  if  (  1  )  {
					   ucFlg  |=  CONST_commFlg_routeTalkData;
					   route.debugInfo.dwTickCnt_me_start  =  GetTickCount(  );	
					   time_t	tNow;	mytime(  &tNow  );  route.debugInfo.tTime_start  =  tNow;
				  }
				  ucFlg  |=  CONST_commFlg_resp;		//  ×¢Òâ£¬ÕâÀïÊÇÏìÓ¦
				  route.debugInfo.index  =  resp.uiDataBlockIndex;

				  if  (  postMsg2Mgr_mc(  pMisCnt,  &route,  CONST_misMsgType_outputTask,  ucFlg,  CONST_qyCmd_sendRobotTaskData, pMsgInput->tStartTime,  pMsgInput->uiTranNo,  0,  (  char  *  )&resp,  lenInBytes,  &pMsgInput->addr_logicalPeer.idInfo,  &pAddrTalkData->route.idInfo_from,  uiChannelType,  NULL,  FALSE  )  )  goto  errLabel;
#endif
				  }
				  break;
			case  CONST_imCommType_transferFileEndReq:  { 
					
				  //  TRANSFER_FILEEND_REQ    req;

				  traceLogA(  (char*)  "transferFileEndReq"  );

				  //  memset(  &req,  0,  sizeof(  req  )  );
				  //  if  (  stream2Data(  &ptr,  &size,  tmpHandler_stream2TransferFileEndReq,  0,  &req  )  )  goto  errLabel;                                 
				  //  memcpy(  pContent,  &req,  min(  sizeof(  pContent[0]  ),  sizeof(  req  )  )  );

				  pMsgInput->lenInBytes  =  min(  sizeof(  pMsgInput->data  ),  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  sizeof(  TRANSFER_FILEDATA_REQ  )  );

				  if  (  !pCtx->pProcessQ  )  goto  errLabel;
				  //
				  //printQ_mis(  &pCtx->pProcessQ->m_q,  0  );
					
				  //
				  printMisMsg(  0,  0,  (  MIS_MSGU  *  )pMsgInput  );

				  TRANSFER_FILEEND_RESP	resp;
				  //
				  memset(  &resp,  0,  sizeof(  resp  )  );
				  resp.uiType  =  CONST_imCommType_transferFileEndResp;
				  //  2015/09/08
				  resp.tmpInternal.bChkToRemove_i  =  TRUE;
				  //
				  if  (  pCtx->pProcessQ->qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsgInput,  &resp  )  <=  0  )  break;
				  if  (  resp.tmpInternal.bNeedRemoved_o  )  {
					  //pCtx->pProcessQ->qRemoveMsg(  tmpHandler_findOrgMsgAndProc_is,  pMsgInput,  0  );
					  qmcApplyForRemovingInvalidTasks(  pProcInfo,  0  );  //  2015/09/07
				  }

				  //
				  //printQ_mis(  &pCtx->pProcessQ->m_q,  0  );

				  traceLogA(  (char*)  "Î´Íê³É£ºÊµ¼ÊÉÏÕâÀï»¹Ó¦¸Ã·¢Ò»¸öendÏìÓ¦°ü"  );

				  }							     
				  break;								 

			case  CONST_imCommType_taskProcReq:  {

				  //  
				  #ifdef  __DEBUG__
						  if  (  pProcInfo->cfg.debugStatusInfo.bDbgDetail){
							  traceLogA(  (char*)  "procMsgInput_mgr_req: taskProcReq"  );
						  }
				  #endif

				  //
				  pMsgInput->lenInBytes  =  min(  sizeof(  pMsgInput->data  ),  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  sizeof(  TRANSFER_FILE_PROCREQ  )  );

				  if  (  !pCtx->pProcessQ  )  {
					  #ifdef  __DEBUG__
							  traceLogA(  (char*)  "procMsgInput_mgr_req error: taskProcReq: pProcessQ is null"  );  
					  #endif
					  goto  errLabel;
				  }
				  #ifdef  __DEBUG__
						  //  printQ_mis(  &pCtx->pProcessQ->m_q,  0  );
						  //  printMisMsg(  0,  0,  (  MIS_MSGU  *  )pMsgInput  );
						  if  (  pContent->taskProcReq.usOp  ==  CONST_imOp_recv_cancel  )  {
							  int  ii  =  0;
						  }
						  if (pContent->taskProcReq.usOp == CONST_imOp_ping) {
							  int  ii = 0;
						  }
						  if (pContent->taskProcReq.usOp == CONST_imOp_applyForConf) {
							  int  ii = 0;
						  }
				  #endif
				  //
				  _sntprintf(tBuf, mycountof(tBuf), _T("mgr_req: recv taskProcReq, op %d (%s) (st_org %I64u,tn_org %d) from %I64u l2409"), 
					  (int)pContent->taskProcReq.usOp, qyGetDesByType1(CONST_imOpTable_en, pContent->taskProcReq.usOp),  
					  pContent->taskProcReq.tStartTime_org, pContent->taskProcReq.uiTranNo_org, 
					  pMsgInput->data.route.idInfo_from.ui64Id);
				  showInfo_open0(0, 0, tBuf);
						  
				  //
				  TASK_PROC_RESP					resp;
				  //  
				  memset(  &resp,  0,  sizeof(  resp  )  );
				  resp.uiType  =  CONST_imCommType_taskProcResp;

				  //
				  void* p1 = &resp;
				  if (pContent->taskProcReq.usOp == CONST_imOp_recv_applyForOrgReq) {
					  //p1 = null;
				  }

				  //
				  int  tmpiRet;
				  tmpiRet  =pCtx->pProcessQ->qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsgInput,  p1  );
					
				  //
				  if  (  resp.tmpInternal.bNeedRemoved_o  )  {
					  qmcApplyForRemovingInvalidTasks(  pProcInfo,  0  );
					  #ifdef  __DEBUG__
							  traceLog((TCHAR*)  _T(  "Need removed"  )  );
					  #endif
				  }
				  //
				  if  (  tmpiRet  ==  0  )  {
					  if  (  pContent->taskProcReq.usOp  == CONST_imOp_recv_applyForOrgReq  )  {
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "taskProcReq: applyForOrgReq, not match. from %I64u, content_org %d, org_tn %d"  ),   pMsgInput->data.route.idInfo_from.ui64Id,  pContent->taskProcReq.uiContentType_org,  pContent->taskProcReq.uiTranNo_org  );
						  showInfo_open0(  0,  0,  tBuf  );
					  }
					  //  对参会方
					  if (pContent->taskProcReq.usOp == CONST_imOp_ping) {
						  _sntprintf(tBuf, mycountof(tBuf), _T("taskProcReq: ping, not match. from %I64u, content_org %d, org_tn %d"), pMsgInput->data.route.idInfo_from.ui64Id, pContent->taskProcReq.uiContentType_org, pContent->taskProcReq.uiTranNo_org);
						  showInfo_open0(0, 0, tBuf);
						  //
						  //
						  len = offsetof(MIS_MSG_TASK, data) + pMsgInput->lenInBytes;
						  //
						  if (qPostMsg(pMsgInput, len, &pQyMc->gui.processQ, _T("procMsgInput_mgr_req kk"))) {
							  traceLogA((char*)"mcThreadProc_mis_work(  ): qPostMsg(  ) failed");
							  goto  errLabel;
						  }
						  PostMessage(pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);
						  //
						  break;

					  }
				  }					  
				  //					
				  if  (  pContent->taskProcReq.usOp  ==  CONST_imOp_send_cancel  )  {
						  void							*		pDb		=	NULL;
						  CE_TASK_MEM							taskMem;
						  int									iStatus  =  CONST_imTaskStatus_canceledBySender;
						  CQyString								subject;
						  CQyString								content;

						  #ifndef  __NOTSUPPORT_DB__
								   CQnmDb								db;						  
								   if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;										 	
								   pDb  =  db.m_pDbMem->pDb;

								   IM_TASK_RCD							rcd;
								   if  (  !g_dbFuncs.pf_bGetImTaskRcdBySth(  pDb,  pSci->cfg.iDbType, FALSE,  pMisCnt->cfg.misServName,  &pAddrTalkData->route.idInfo_from,  (  time_t  )pContent->taskProcReq.tStartTime_org,  pContent->taskProcReq.uiTranNo_org,  0,  &rcd  )  )  goto  errLabel;

								   memset(  &taskMem,  0,  sizeof(  taskMem  )  );
								   taskMem.iStatus  =  rcd.iStatus;
								   taskMem.iTaskId  =  rcd.id;
								   taskMem.idInfo_send.ui64Id  =  rcd.idInfo_send.ui64Id;
								   taskMem.idInfo_recv.ui64Id  =  rcd.idInfo_recv.ui64Id;
								   subject  =  rcd.subject;
								   content  =  rcd.content;
						  #else
								   if  (  getCeTaskMem(  pDb,  pSci->cfg.iDbType,  pMisCnt,  &pAddrTalkData->route.idInfo_from,  pContent->taskProcReq.tStartTime_org,  pContent->taskProcReq.uiTranNo_org,  0,  &taskMem  )  )  goto  errLabel;  
						  #endif

						  //  2014/11/22
						  switch  (  taskMem.iStatus  )  {
								  case  CONST_imTaskStatus_applyToRecv:
								  case  CONST_imTaskStatus_resp:
								  case  CONST_imTaskStatus_waitToRecv:
									    break;
								  default:
									     iErr  =  0;  goto  errLabel;									  
										 break;	//  
						  }

						  //  
						  if  (  g_dbFuncs.pf_updateTaskStatus(  pDb,  iStatus,  taskMem.iTaskId  )  )  goto  errLabel;																   
						  //
						#if  0	//  2014/11/22. 在代理的工作模式下，不能用route得到logicalpeer
						  if  (  !pMsgInput->addr_logicalPeer.idInfo.ui64Id  )  {	//  
							  if  (  getIdInfo_logicalPeer(  pSci,  pMisCnt,  &pMsgInput->data.route,  &pMsgInput->addr_logicalPeer  )  )  {
								  #ifdef  __DEBUG__
										  traceLogA(  (char*)  "procMsgInput_other_req: getIdInfo_logicalPeer failed."  );  
								  #endif
								  goto  errLabel;
							  }		 
						  }
						#endif

						  //
						  showTaskStatus(  pMisCnt,  &pMsgInput->addr_logicalPeer.idInfo,  &taskMem.idInfo_send,  &taskMem.idInfo_recv,  FALSE,  pContent->taskProcReq.uiContentType_org,  taskMem.iTaskId,  iStatus,  0,  0,  subject,  content  );
						  
						  //  2015/10/08  
						  break;										 
					  
				  }
										
				  if  (  tmpiRet  >  0  )  {

				  if  (  pContent->taskProcReq.usOp  ==  CONST_imOp_recv_applyForChkTaskAlive  )  {
					  			  

					  //
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "Resp to %I64u, task is alive"  ),  pMsgInput->data.route.idInfo_from.ui64Id  );

					  resp.tStartTime_org  =  pContent->taskProcReq.tStartTime_org;
					  resp.uiTranNo_org  =  pContent->taskProcReq.uiTranNo_org;
					  resp.usCmd_org  =  pMsgInput->usCode;
					  resp.usOp_org  =  pContent->taskProcReq.usOp;
					  //
					  lenInBytes  =  sizeof(  resp  );
					  //
					  ucFlg  =  0;
					  ucFlg  |=  CONST_commFlg_resp;		//  ×¢Òâ£¬ÕâÀïÊÇÏìÓ¦

					  if  (  postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_outputTask,  ucFlg,  CONST_qyRc_ok,  pMsgInput->tStartTime,  pMsgInput->uiTranNo,  0,  (  char  *  )&resp,  lenInBytes,  &pMsgInput->addr_logicalPeer.idInfo,  &pAddrTalkData->route.idInfo_from,  pMsgInput->uiChannelType,  pCtx->pMsgBuf,  FALSE  )  )  goto  errLabel;

					  break;
				  }


				  #ifdef  __DEBUG__
						  //  printQ_mis(  &pCtx->pProcessQ->m_q,  0  );
				  #endif
					  }

				  }
				  break;
	
			case  CONST_imCommType_transferAvInfo:  {
			      TRANSFER_AV_INFO  *  pReq  =  NULL;
				  //
#if  0
				  if  (  pChannel->uiType  ==  CONST_channelType_realTimeMedia  )  {	//  realTimeMedia 
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "Error: %s ÊÕµ½ %I64u µÄ %s"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  ),  pMsgInput->data.route.idInfo_from.ui64Id,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
					  goto  errLabel;
				  }
#endif
				  //  2014/04/28
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  "procMsgInput_mgr_req"  ),  _T(  ": recv transferAvInfo from %I64u..... tn %d"  ),  pMsgInput->data.route.idInfo_from.ui64Id,  pMsgInput->uiTranNo  );

				  //
				  pMsgInput->lenInBytes  =  min(  sizeof(  pMsgInput->data  ),  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  sizeof(  TRANSFER_AV_INFO  )  );
				  //
				  pReq  =  (  TRANSFER_AV_INFO  *  )&pContent->transferAvInfo;
				  //  2014/09/28
				  if  (  pReq->idInfo_logicalPeer.ui64Id  )  {
					  if  (  pContent->transferAvInfo.uiTaskType  ==  CONST_imTaskType_viewDynBmp  )  {
						  		
						  pMsgInput->uiType  =  CONST_misMsgType_task;
						  pMsgInput->uiTaskType  =  pContent->transferAvInfo.uiTaskType;

						  //	
						  pMsgInput->idInfo_taskSender.ui64Id  =  pAddrTalkData->route.idInfo_from.ui64Id;
						  pMsgInput->idInfo_taskReceiver.ui64Id  =  pAddrTalkData->route.idInfo_to.ui64Id;				  
						  //
						  len  =  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgInput->lenInBytes;
		
						  if  (  pReq->idInfo_logicalPeer.ui64Id  )  {
							  if  (  !pMisCnt  )  goto  errLabel;
							  if  (  pReq->idInfo_logicalPeer.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
								  showInfo_open0(  0,  0,  _T(  "procMsgInput_other_req failed, viewDynBmp, req.idInfo_logicalPeer is me"  )  );
								  goto  errLabel;
							  }
							  pMsgInput->addr_logicalPeer.idInfo.ui64Id  =  pReq->idInfo_logicalPeer.ui64Id;
							  }
						  else  {
							    pMsgInput->addr_logicalPeer.idInfo.ui64Id  =  pAddrTalkData->route.idInfo_from.ui64Id; 
						  }
				  
						  if  (  qPostMsg(  pMsgInput,  len,  &pQyMc->gui.processQ,  _T(  "procMsgInput_mgr_req kk"  ))) {
							  traceLogA(  (char*)  "mcThreadProc_mis_work(  ): qPostMsg(  ) failed"  );
							  goto  errLabel;				  
						  }				  
						  PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    

						  iErr  =  0;  goto  errLabel;						   
					  }
				  }

				  //
				  #if  0	//  2014/11/19. 不能修改req.idInfo_logicalPeer以及to,from。因为在avproxy时，需要用这几个参数来判断是否需要proxy. 处理时要利用addr_logicalPeer或者req.idInfo_logicalPeer
				  if  (  pReq->idInfo_logicalPeer.ui64Id  )  {
					  traceLogA(  (char*)  "procMsgInput_other_req: transferAvInfo, use idInfo_logicalPeer to set idInfo_to"  );
					  pAddrTalkData->route.idInfo_to.ui64Id  =  pReq->idInfo_logicalPeer.ui64Id;
					  pReq->idInfo_logicalPeer.ui64Id  =  0;
				  }
				  #endif
				  //
				  #if  10
				  if  (  pReq->idInfo_logicalPeer.ui64Id  )  {
					  if  (  !pMisCnt  )  goto  errLabel;
					  if  (  pReq->idInfo_logicalPeer.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
						  showInfo_open0(  0,  0,  _T(  "procMsgInput_other_req failed, req.idInfo_logicalPeer is me"  )  );
						  goto  errLabel;
					  }
					  pMsgInput->addr_logicalPeer.idInfo.ui64Id  =  pReq->idInfo_logicalPeer.ui64Id;
				  }
				  #endif
				  //
				  pMsgInput->uiType  =  CONST_misMsgType_task;
				  //
				  pMsgInput->idInfo_taskSender.ui64Id  =  pAddrTalkData->route.idInfo_from.ui64Id;
				  pMsgInput->idInfo_taskReceiver.ui64Id  =  pAddrTalkData->route.idInfo_to.ui64Id;
				  //
				  len  =  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgInput->lenInBytes;
				  //
				  //  if  (  procMsgTask_mc_media(  pQyMc,  pSci,  pProcInfo,  pMsgInput,  len,  TRUE,  pCtx,  pChannel  )  )  goto  errLabel;
				  if  (  procMsgTask_mc_mgr(  pQyMc,  pSci,  pProcInfo,  pMsgInput,  len,  TRUE,  pCtx,  pChannel  )  )  goto  errLabel;
				  }
				  break;

			case  CONST_imCommType_transferAvReplyInfo:  {
				  TRANSFER_AV_replyInfo  *  pReq  =  NULL;
				  //
				  if  (  pChannel->uiType  ==  CONST_channelType_realTimeMedia  )  {	//  realTimeMedia 
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "Error: %s ÊÕµ½ %I64u µÄ %s"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  ),  pMsgInput->data.route.idInfo_from.ui64Id,  qyGetDesByType1(  getResTable(  0, &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
					  goto  errLabel;
				  }
				  //
				  pMsgInput->lenInBytes  =  min(  sizeof(  pMsgInput->data  ),  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  sizeof(  TRANSFER_AV_replyInfo  )  );
				  //
				  pReq  =  (  TRANSFER_AV_replyInfo  *  )&pContent->transferAvReplyInfo;
				  //
				  pMsgInput->uiType  =  CONST_misMsgType_task;
				  //
				  pMsgInput->idInfo_taskSender.ui64Id  =  pAddrTalkData->route.idInfo_to.ui64Id;
				  pMsgInput->idInfo_taskReceiver.ui64Id  =  pAddrTalkData->route.idInfo_from.ui64Id;
				  //
				  len  =  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgInput->lenInBytes;

				  if  (  procMsgTask_mc_mgr(  pQyMc,  pSci,  pProcInfo,  pMsgInput,  len,  TRUE,  pCtx,  pChannel  )  )  goto  errLabel;
				  }
				  break;

			case  CONST_imCommType_transferVideoData:  {						
				  CQyQ2Help	q2Help;

				  #ifdef  __DEBUG__
								//traceLogA(  (char*)  "mm"  );
				  #endif
					
				  //
				  if (!bDone_retrieveAllImObjRules(pMisCnt)) {
					  #ifdef  __DEBUG__
							  showInfo_open0(0, mynull, _T("procMsgInput_mgr_req:	videoData skipped, imObjRules not ok"));
					  #endif
					  goto  errLabel;
				  }

				  //
				  msgLen  +=  sizeof(  pContent->transferVideoData  );						
				  if  (  q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->mediaQ2,  _T(  "procmsgInput_mgr_req kk"  )))  goto  errLabel;
				  }
				  break;

			case  CONST_imCommType_transferAudioData:  {
				  CQyQ2Help	q2Help;

				  //
				  if (!bDone_retrieveAllImObjRules(pMisCnt)) {
#ifdef  __DEBUG__
					  showInfo_open0(0, mynull, _T("procMsgInput_mgr_req:	audioData skipped, imObjRules not ok"));
#endif
					  goto  errLabel;
				  }

				  //
				  msgLen  +=  sizeof(  pContent->transferAudioData  );					
				  if  (  q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->realTimeMediaQ2,  _T(  "procmsgInput_mgr_req bnsm"  )))  goto  errLabel;
				  }
				  break;

			default:
					bNeedProcess  =  TRUE;
					break;
	}
	if  (  !bNeedProcess  )  {
		iErr  =  0;  goto  errLabel;
	}
	



	//		
	switch  (  pContent->uiType  )  {
						  case  CONST_imCommType_transferAvInfo:  {
							    CQyQ2Help	q2Help;
							    //
							    msgLen  +=  sizeof(  pContent->transferAvInfo  );
								//
								if  (  q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->mediaQ2,  _T(  "procmsgInput_mgr_req 8"  )))  goto  errLabel;
								}
				   				break;
						  case  CONST_imCommType_transferAvReplyInfo:  {
							    CQyQ2Help	q2Help;

							    msgLen  +=  sizeof(  pContent->transferAvReplyInfo  );
								if  (  q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->mediaQ2,  _T(  "procMsgInput_mgr_req 88"  )))  goto  errLabel;
								}
				   				break;
						  case  CONST_imCommType_transferVideoData:  {
							    CQyQ2Help	q2Help;

							#ifdef  __DEBUG__
								traceLogA(  (char*)  "mm"  );
							#endif

							    msgLen  +=  sizeof(  pContent->transferVideoData  );
								if  (  q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->mediaQ2,  _T(  "procMsgInput_mgr_req 87"  )))  goto  errLabel;
								}
							    break;
						  case  CONST_imCommType_transferVideoDataResp:  {
							    CQyQ2Help	q2Help;

							    msgLen  +=  sizeof(  pContent->transferVideoDataResp  );
								if  (  q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->mediaQ2,  _T(  "procMsgInput_mgr_req 2"  )))  goto  errLabel;
								}
							    break;
						  case  CONST_imCommType_transferAudioData:  {
							    CQyQ2Help	q2Help;

							    msgLen  +=  sizeof(  pContent->transferAudioData  );
								if  (  q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->realTimeMediaQ2,  _T(  "procmsgInput_mgr_req 222"  )))  goto  errLabel;
								}
							    break;
						  case  CONST_imCommType_transferAudioDataResp:  {
							    CQyQ2Help	q2Help;

							    msgLen  +=  sizeof(  pContent->transferAudioDataResp  );
								if  (  q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->realTimeMediaQ2,  _T(  "procMsgInput_mgr_req 65"  )))  goto  errLabel;
								}
							    break;
						  case  CONST_imCommType_remoteAssistReq:  {
							    CQyQ2Help	q2Help;

							    msgLen  +=  sizeof(  pContent->remoteAssistReq  );
								//  if  (  q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->mediaQ2  )  )  goto  errLabel;				   				
								if  (  q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->rtOpQ2,  _T(  "procMsgInput_mgr_req 766"  )))  goto  errLabel;
								}
							    break;
						  case  CONST_imCommType_taskProcReq:  {
							    CQyQ2Help	q2Help;

							    msgLen  +=  sizeof(  pContent->taskProcReq  );
								if  (  q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->mediaQ2,  _T(  "procMsgInput_mgr_req 22"  )))  goto  errLabel;
								}
							    break;
						  case  CONST_imCommType_taskProcResp:  {
							    CQyQ2Help	q2Help;

							    msgLen  +=  sizeof(  pContent->taskProcResp  );
								if  (  q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->mediaQ2,  _T(  "procMsgInput_mgr_req 223"  )))  goto  errLabel;
								}
							    break;								
						  case  CONST_imCommType_transferGpsInfo:  {	//  2012/04/20
							    CQyQ2Help	q2Help;

								msgLen  +=  sizeof(  pContent->transferGpsInfo  );
								if  (  q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->mediaQ2,  _T(  "procMsgInput_mgr_req 8n"  )))  goto  errLabel;
								}
							    break;
						  case  CONST_imCommType_transferGpsReplyInfo:  {
							    CQyQ2Help	q2Help;

								msgLen  +=  sizeof(  pContent->transferGpsReplyInfo  );
								if  (  q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->mediaQ2,  _T(  "procMsgInput_mgr_req 33"  )))  goto  errLabel;
								}
							    break;
						  case  CONST_imCommType_transferGpsData:  {
							    CQyQ2Help	q2Help;

								msgLen  +=  sizeof(  pContent->transferGpsData  );
								if  (  q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->mediaQ2,  _T(  "procMsgInput_mgr_req 87"  )))  goto  errLabel;
								}
							    break;
						  case  CONST_imCommType_ptzControlReq:  {	//  2012/08/06
							    CQyQ2Help	q2Help;

								msgLen  +=  sizeof(  pContent->ptzControlReq  );
								if  (  q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->mediaQ2,  _T(  "procMsgInput_mgr_req nb"  )))  goto  errLabel;
								}
							    break;
						  case  CONST_imCommType_ptzControlCmd:  {	//  2012/08/06
							    CQyQ2Help	q2Help;

								msgLen  +=  sizeof(  pContent->ptzControlCmd  );
								if  (  q2Help.qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->mediaQ2,  _T(  "procMsgInput_mgr_req nm"  )))  goto  errLabel;
								}
							    break;

								//  2014/05/03
						  case  CONST_imCommType_retrieveDynBmps:
								#ifdef  __DEBUG__
										traceLog((TCHAR*)  _T(  "procMsgInput_mgr_req: retrieveDynBmps"  )  );
								#endif
								msgLen  +=  sizeof(  pContent->retrieveDynBmps  );
								if  (  qPostMsg(  pMsg,  msgLen,  &pQyMc->gui.processQ,  _T(  "procMsgInput_mgr_req 67"  )))  goto  errLabel;
								PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
								//
							    break;

								//  2015/08/02
						  case  CONST_imCommType_procOfflineRes:
								#ifdef  __DEBUG__
										traceLog((TCHAR*)  _T(  "procMsgInput_mgr_req: procOfflineRes"  )  );
								#endif
								msgLen  +=  sizeof(  pContent->procOfflineResU  );
								//
								if  (  pContent->procOfflineResU.common.usSubtype  ==  CONST_procOfflineResSubtype_download  )  {
									if  (  qPostMsg(  pMsg,  msgLen,  &pQyMc->gui.processQ,  _T(  "procMsgInput_mgr_req 7ns"  )))  goto  errLabel;
									PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
									break;
								}
								//
								qPostMsgAndTrigger(  pMsg,  msgLen,  &pProcInfo->schedulerQ,  _T(  "procMsgInput_mgr_req mnsu"  ));
							    //
							    break;

								//  2018/10/27
						  case  CONST_imCommType_imGrp:
								#ifdef  __DEBUG__
										traceLog((TCHAR*)  _T(  "procMsgInput_mgr_req: imGrp"  )  );
								#endif
								msgLen  +=  sizeof(  pContent->imGrpEx  );
								//
									if  (  qPostMsg(  pMsg,  msgLen,  &pQyMc->gui.processQ,  _T(  "procMsgInput_mgr_reqmn"  )))  goto  errLabel;
									PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
								
							    
							    break;

						  default:
								  #ifdef  __DEBUG__
										  traceLog((TCHAR*)  _T(  "procMsgInput_mgr_req: unprocessed contentType %d"  ),  pContent->uiType  );
								  #endif
							      qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procMsgInput_mgr_req: unprocessed contentType %d"  ),  pContent->uiType  );
								  break;


				 
	 }				  
		 

	iErr  =  0;

errLabel:

	return  iErr;
}





