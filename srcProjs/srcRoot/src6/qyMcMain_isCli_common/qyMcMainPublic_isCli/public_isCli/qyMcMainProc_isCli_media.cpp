
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


#ifdef  __DEBUG__
 int  testDmoDecompressInit(  COMPRESS_VIDEO  *  pCompressVideo  );
#endif



 int  procMsgTask_mc_media(  void  *  pQyMcParam,  void  *  pSciParam,  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_TASK  *  pMsg,  unsigned  int  lenInBytes_msg,  BOOL  bMsgInput,  void  *  pCTX_MC_THREAD,  MIS_CHANNEL  *  pChannel  )
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
							 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "procMsgTask_mc_media: getIdInfo_logicalPeer failed."  )  );
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
						   if  (  !tmpiRet  )  {
							   #ifdef  __DEBUG__
									   traceLogA(  (char*)  "procMsgTask_mc_media: transferAvInfo, to qPostMsg"  ); 
							   #endif

									   //
#if  0
									   
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
#endif
							   

							   #ifdef  __DEBUG__
									   traceLogA(  (char*)  "procMsgTask_mc_media: transferAvInfo, qPostMsg ok;"  ); 
							   #endif
						   }							
						   //  							
							   
						   //  2008/03/21, 
						   startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "send transferAvInfo"  )  );
						   						   
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
	
								 startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "send transferAvReplyInfo"  )  );

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
										 //
										 traceLogA(  (char*)  "procMsgTask_mc_media: gpsReply ok;"  ); 
									 }
								 }									 
	
								 startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "send transferGpsReplyInfo"  )  );
						   }					   
						   
						   break;


						   //
					 default:
							#ifdef  __DEBUG__
									traceLogA(  (char*)  "procMsgTask_mc_media failed. unknown pContent->uiType is %d",  pContent->uiType  );
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

			 //  traceLogA(  (char*)  "ÐÅÏ¢´ÓtalkingÍ¨µÀÖÐ·¢³ö"  );
			 if  (  postMsg2Mgr_mc(  pMisCnt,  NULL,  pMsg->uiType,  pMsg->ucFlg,  pMsg->usCode,  pMsg->tStartTime,  pMsg->uiTranNo,  pMsg->usSeqNo,  pMsg->data.buf,  pMsg->lenInBytes  -  offsetof(  MIS_MSG_routeTalkData,  buf  ),  &pMsg->addr_logicalPeer.idInfo,  &pMsg->data.route.idInfo_to,  0,  NULL,  FALSE  )  )  goto  errLabel;
			 
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
						   pMsg->uiTaskType  =  pContent->transferAvInfo.uiTaskType;
						   pMsg->iStatus  =  CONST_imTaskStatus_resp;

						   //  2009/09/07
						   if  (  pContent->transferAvInfo.uiTaskType  ==  CONST_imTaskType_viewDynBmp  )  {

							   if  (  qPostMsg(  pMsg,  lenInBytes_msg,  &pQyMc->gui.processQ,  _T(  "procMsgTask_mc_media"  ))) {
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
							   if  (  pRcd->iStatus  !=  pMsg->iStatus  &&  !bTaskAlive(  pRcd->iStatus  )  )  {
								   if  (  g_dbFuncs.pf_updateTaskStatus(  pDb,  pMsg->iStatus,  pRcd->id  )  )  goto  errLabel;
							   }
							   
						   }

						   //  2007/07/01						   
						   pMsg->iTaskId  =  pRcd->id;
						   pMsg->uiTaskMode_unused  =  pRcd->uiMode;

						   //
						   if  (  qPostMsg(  pMsg,  lenInBytes_msg,  &pQyMc->gui.processQ,  _T(  "procmsgTask_mc_media 2"  ))) {
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
						 	
						   bRemoveIfErr  =  FALSE;			//  2008/05/14, avProcInfo

						   if  (  !pCtx->pProcessQ  )  goto  errLabel;

						   startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "recv transferVideoData"  )  );

						   //  2009/05/12						   
						   pMsg->uiChannelType  =  pChannel->uiType;
						   
						   if  (  tmpiRet  =  pCtx->pProcessQ->qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  )  <=  0  )  {
							   getTimelStr(  pMsg->tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
							   //  traceLogA(  (char*)  "procMsgTask_mc_media failed: video data error"  );
							   TCHAR  tBuf[128];
							   _sntprintf(tBuf, mycountof(tBuf), _T(  "%s err: %I64u,  tn %d, tn_openAvDev [%d], read from %s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  ), pMsg->data.route.idInfo_from.ui64Id,  pMsg->uiTranNo,  pContent->transferVideoData.uiTranNo_openAvDev,  qyGetDesByType1(  CONST_channelTypeTable,  pMsg->uiChannelType_input  )  );
							   showInfo_open0(0, 0, tBuf);
							   //
							   //  2010/12/27
							   //  if  (  pMsg->data.route.idInfo_to.ui64Id  !=  pMisCnt->idInfo.ui64Id  )  
							   {
								   #define	CONST_nIntervalInMs_tryToResumeVideoTask	200		//  5000		//  2014/10/13
								   //
								   if  (  GetTickCount(  )  -  pCtx->dwTickCnt_tryToResumeVideoConference  >  CONST_nIntervalInMs_tryToResumeVideoTask  )  {
									   pCtx->dwTickCnt_tryToResumeVideoConference  =  GetTickCount(  );

									   #ifdef  __DEBUG__
											   if  (  0  )  {
													traceLogA(  (char*)  "procMsgTask_mc_media: videoData err, try to find orgReq"  );
											   }
									   #endif
									   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "procMsgTask_mc_media: %I64u, videoData err, try to find orgReq."  ),  pMsg->data.route.idInfo_from.ui64Id   );
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

						   bRemoveIfErr  =  FALSE;			//  2008/05/14, avProcInfo
						 	
						   if  (  !pCtx->pProcessQ  )  goto  errLabel;

						   startChannel(  pProcInfo,  pMisCnt,  pChannel,  _T(  "recv transferAudioData"  )  );

						   //  2009/05/12						   
						   pMsg->uiChannelType  =  pChannel->uiType;

						   if  (  (  tmpiRet  =  pCtx->pProcessQ->qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  )  )  <=  0  )  {
							   getTimelStr(  pMsg->tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
							   //  traceLogA(  (char*)  "procMsgTask_mc_media failed: audio data error"  );
							   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "%s err: %I64u. tn %d, tn_openAvDev [%d], read from %s"  ),  qyGetDesByType1(  getResTable(  0, &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  ),  pMsg->data.route.idInfo_from.ui64Id,  pMsg->uiTranNo,  pContent->transferAudioData.uiTranNo_openAvDev, qyGetDesByType1(  CONST_channelTypeTable,  pMsg->uiChannelType_input  )  );
							   //
							   //  2009/10/17
							   //  if  (  pMsg->data.route.idInfo_to.ui64Id  !=  pMisCnt->idInfo.ui64Id  )  
							   {
								   if  (  GetTickCount(  )  -  pCtx->dwTickCnt_tryToResumeVideoConference  >  2000  )  {
									   pCtx->dwTickCnt_tryToResumeVideoConference  =  GetTickCount(  );
									   //
									   TCHAR  tBuf[128];
									   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "procMsgTask_mc_media: audioData err, shall send a request to retrieve original avInfo. conf%I64u, from %I64u"  ),  pMsg->addr_logicalPeer.idInfo.ui64Id,  pMsg->data.route.idInfo_from.ui64Id  );
									   showInfo_open0(  0,  0,  tBuf  );										   
									   //
									   int  iStatus  =  CONST_imTaskStatus_err_missingOrgReq;
									   //
									   if  (  tmpiRet  ==  CONST_qyRet_cantGet_index_activeMems_from  )  {
										   iStatus  =  CONST_imTaskStatus_err_cantGet_index_activeMems_from;
									   }
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
							   #ifdef  __DEBUG__
									   traceLogA(  (char*)  "procMsgTask_mc_media failed: remoteAssistReq"  );
							   #endif
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

							   if  (  qPostMsg(  pMsg,  lenInBytes_msg,  &pQyMc->gui.processQ,  _T(  "procMsgTask_mc_media 4"  ))) {
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
						     traceLogA(  (char*)  "procMsgTask_mc_media failed, bInput, pContent->uiType is %d",  pContent->uiType  );
							 goto  errLabel;
							 break;
			 }		
			 
		 }	//  ÒÔÉÏÎªÊäÈë

		 			 
		 traceLogA(  (char*)  "procMsgTask_mc_media:  Óöµ½ÁËÎÞ·¨½âÊÍµÄÇé¿ö£¬´íÎó"  );  goto  errLabel;
	 
	 
		}
	 else  {
		
		   printMisMsg(  0,  0,  (  MIS_MSGU  *  )pMsg  );

		   qyShowInfo1(  CONST_qyShowType_debug,  0, (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "µÃµ½%I64uµÄÏìÓ¦%s"  ),  pMsg->data.route.idInfo_from.ui64Id,  qyGetDesByType1(  CONST_qyRcTable,  pMsg->usCode  )  );

		   if  (  !isRcOk(  pMsg->usCode  )  )  goto  errLabel;

		   traceLogA(  (char*)  "procMsgTask_mc_media:  ¶ÔÓÚÏìÓ¦°ü£¬»¹Ã»ÓÐ´¦ÀíÄØ"  );
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


//  2015/09/13



/////////////////////
int  doMediaMsg(  QY_MC  *  pQyMc,  QY_SERVICEGUI_INFO			*		pSci,  MC_VAR_isCli  *  pProcInfo,     MIS_MSGU  *  pMsg,  int  msgLen,  unsigned  int  uiChannelType,  CTX_MC_THREAD  *  pCtx  )
{
	int  iErr  =  -1;
	int  len  =  msgLen;

	#if  10

			   //
			   switch  (  pMsg->uiType  )  {
					   case  CONST_misMsgType_input:  {
						     MIS_CNT					*		pMisCnt							=  (  MIS_CNT  *  )pMsg->input.pMisCnt;
							 MIS_CHANNEL				*		pChannel						=	NULL;

							 if  (  !pMisCnt  )  break;
							 //  if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  pMsg->input.uiChannelType  )  )  )  break;
							 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  break;

							 if  (  isUcFlgResp(  pMsg->input.ucFlg  )  )  {
								 if  (  procMsgInput_other_resp(  pQyMc,  pSci,  pProcInfo,  &pMsg->input,  len,  pCtx,  pChannel  )  )  break;							 
								}
							 else  {
								   if  (  procMsgInput_other_req(  pQyMc,  pSci,  pProcInfo,  &pMsg->input,  len,  pCtx,  pChannel  )  )  break;							 								
							 }							 

							 //
							 }
						     break;
					   case  CONST_misMsgType_talk:  
							 #ifdef  __DEBUG__
									 traceLogA(  (char*)  "mcThreadProc_mis_media: msg_talk ÔÝÊ±²»´¦Àí"  );
							 #endif
						     break;
					   case  CONST_misMsgType_task:  {
						     MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMsg->task.pMisCnt;
							 MIS_CHANNEL				*		pChannel						=	NULL;

							 if  (  !pMisCnt  )  break;
							 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  break;

							 if  (  procMsgTask_mc_media(  pQyMc,  pSci,  pProcInfo,  &pMsg->task,  len,  FALSE,  pCtx,  pChannel  )  )  break;

							 //  printMisMsg(  0,  0,  pMsg  );

							 }
						     break;
					   case  CONST_misMsgType_applyForChkChannels_qmc:  {
						     MIS_CNT	*	pMisCnt		=	(  MIS_CNT  *  )pMsg->applyForChkChannels_qmc.pMisCnt;
							 if  (  !pMisCnt  )  break;

							 #ifdef  __DEBUG__
									 traceLogA(  (char*)  "media: applyForChkChannels"  );
							 #endif
							 startChannel(  pProcInfo,  pMisCnt,  getChannelByType(  pMisCnt,  uiChannelType  ),  _T(  "media: applyForChannels"  )  );  		

							 }						     
						     break;
					   case  CONST_misMsgType_outputTask:  
					   default:
								#ifdef  __DEBUG__
										traceLogA(  (char*)  "mcThreadProc_mis_media failed, Î´´¦ÀíµÄÏûÏ¢ÀàÐÍ%d",  pMsg->uiType  );
								#endif
								break;
			   }
#endif

			   iErr  =  0;
errLabel:
			   return  iErr;
}





//  2015/09/14
#define		CONST_pMsgs_media		10

//  2015/09/13
 extern "C" DWORD WINAPI mcThreadProc_mis_media( LPVOID lpParameter )
{
	 int								iErr							=	-1;
	 QY_MC						*		pQyMc							=	QY_GET_GBUF(  );
	 QY_SERVICEGUI_INFO			*		pSci							=	(  QY_SERVICEGUI_INFO  *  )lpParameter;
	 MC_VAR_isCli					*		pProcInfo						=	(  MC_VAR_isCli  *  )pSci->pVar;
	 int								loopCtrl						=	0;
	 int								i;
	 DWORD								dwThreadId						=	GetCurrentThreadId(  );

	 //
#if  0
	 CQyMalloc							mallocObj;
	 MIS_MSGU					*		pMsg							=	NULL;
	 unsigned  int						len;
#endif

	 CQyMalloc							mallocObj_msgs;
	 MIS_MSGU						*	msgs							=	NULL;

	 MIS_MSGU						*	pMsgs[CONST_pMsgs_media];
	 int								msgLens[CONST_pMsgs_media];

	 int								maxMsgs							=	CONST_pMsgs_media;			//  一次最多处理的包数。
	 int								nMsgs;

	 //
	 DWORD								dwRet;
	 //  long								lPrev;
	 //
	 CTX_MC_THREAD						ctx;
	 CQyMalloc							mallocObj_pMsgInputBuf;
	 CQyMalloc							mallocObj_pMsgBuf;
	 //
	 //  CWnd						*		pMainWnd						=	AfxGetApp(  )->m_pMainWnd;
	 //
	 QY_Q2						*		pTriggerQ2						=	&pProcInfo->mediaQ2;
	 unsigned  int						uiChannelType					=	CONST_channelType_media;
	 
	 //
	 int  lastTickCnt_chkTasksStatus = 0;

	 //
	 traceLogA(  (char*)  "mcThreadProc_mis_media:  enters"  );

	 //
	 memset(  &ctx,  0,  sizeof(  ctx  )  );
	 ctx.pProcessQ  =  &pProcInfo->processQ_media;
	 ctx.pMsgBuf_forInput  =  (  MIS_MSGU  *  )mallocObj_pMsgInputBuf.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  );
	 if  (  !ctx.pMsgBuf_forInput  )  goto  errLabel;
	 ctx.pMsgBuf  =  (  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  );
	 if  (  !ctx.pMsgBuf  )  goto  errLabel;
	 	
#if  0
	 if  (  !(  pMsg  =  (  MIS_MSGU  *  )mallocObj.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  )  )  )  goto  errLabel;
#endif
	 if  (  !(  msgs  =  (  MIS_MSGU  *  )mallocObj_msgs.mallocf(  CONST_iAllocType_longTimeMsg,  maxMsgs  *  sizeof(  MIS_MSGU  )  )  )  )  {
		 iErr  =  -100;
		 goto  errLabel;
	 }
	 for  (  i  =  0;  i  <  maxMsgs;  i  ++  )  {
		  pMsgs[i]  =  &msgs[i];
	 }



	 //
	 for  (  ;  !pQyMc->bQuit;  loopCtrl  ++  )  {
		 if (!pQyMc->bLogon) {
			 break;
		 }

		  //  if  (  !pMainWnd  )  pMainWnd					=	AfxGetApp(  )->m_pMainWnd;
		  if  (  !pQyMc->gui.hMainWnd  )  {
			  Sleep(  1000  );  continue;
		  }

		  int  iWaitTimeInMs = 5000;
		  iWaitTimeInMs = CONST_iWaitTimeInMs_media;
		  dwRet  =  WaitForSingleObject(  pTriggerQ2->hEvents[0], iWaitTimeInMs);
		  if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
		  
		  for  (  ;  !pQyMc->bQuit;  )  {
			   //
			   if  (  isQ2Empty(  pTriggerQ2  )  )  break;  

			   //
			   for  (  i  =  0;  i  <  maxMsgs;  i  ++  )  {
				    msgLens[i]  =  sizeof(  msgs[0]  );
			   }
			   nMsgs  =  maxMsgs;
			   //  len  =  sizeof(  pMsg[0]  );
			   {
				   CQyQ2Help	q2Help;			  
				   if  (  qGetMsgs(  q2Help.getQ_toGetMsg(  pTriggerQ2,  _T(  "threadProc_media"  )), (void**)pMsgs, (unsigned  int*)msgLens, (unsigned  int*)&nMsgs))  break;
			   }			   

			   //
			   for  (  i  =  0;  i  <  nMsgs;  i  ++  )  {
				    memset(  (  (  char  *  )(  pMsgs[i]  )  )  +  msgLens[i],  0,  min(  256,  sizeof(  msgs[0]  )  -  msgLens[i]  )  );			   			   
			   }

			   #ifdef  __DEBUG__
					   //  traceLog((TCHAR*)  _T(  "preTransV: nMsgs %d"  ),  nMsgs  );
			   #endif
			   if  (  !nMsgs  )  continue;

			   for  (  i  =  0;  i  <  nMsgs;  i  ++  )
			   {
				   MIS_MSGU  *  pMsg  =  pMsgs[i];
				   int  msgLen  =  msgLens[i];

				   //
				   doMediaMsg(  pQyMc,  pSci,  pProcInfo,  pMsg,  msgLen,  uiChannelType,  &ctx  );

			   }

		  }

		  //				  
		  //
		//
		  bool  bNeedStartChannel;  bNeedStartChannel = false;
		  //
		  if (!(loopCtrl % 2))
		  {
			  int  tickCnt0 = myGetTickCount(mynull);
			  int  lDiffInMs = tickCnt0 - lastTickCnt_chkTasksStatus;
			  if (abs(lDiffInMs) > 1000) {
				  bNeedStartChannel = true;
				  //
				  lastTickCnt_chkTasksStatus = tickCnt0;
			  }
		  }
		  if (pProcInfo->av.bNeedStartChannel_v) {
			  bNeedStartChannel = true;
			  //  这里要将标志位清除
			  pProcInfo->av.bNeedStartChannel_v = false;
			  //
			  showInfo_open0(0, 0, _T("media: bNeedStartChannel_v is true"));
		  }

		  //
		  if (bNeedStartChannel) {
			  //
			  if (pProcInfo->status.tasksStatus.bTaskExists_av) {
				  MIS_CNT* pMisCnt = (MIS_CNT*)pProcInfo->getMisCntByName(_T(""));
				  if (!pMisCnt)  break;

				  //
				  //traceLog((TCHAR*)_T("media: taskExists_av true, try to startChannel "));
				  startChannel(pProcInfo, pMisCnt, getChannelByType(pMisCnt, uiChannelType), _T("media: taskExists_av true, try to startChannels"));
			  }
		  }



		  //
		  if  (  !(  loopCtrl  %  5  )  )  {

			  //  ÏÂÃæ×¢Òâ°Ñ²»ÓÃµÄÍ¨µÀ¸ø»ØÊÕ»ØÀ´
			  //for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
			  for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
			  {
				   MIS_CNT  *  pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  i  );//&pProcInfo->misCnts[i]; 
				   if  (  !pMisCnt  )  continue;
				   //
				   if  (  !pMisCnt->cfg.dynCfg.cnt.usCntPort  )  continue;

				   waitForChannel(  pProcInfo,  pMisCnt,  uiChannelType,  FALSE  );
			  }
		  }

	 }


	 iErr  =  0;

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


	 pProcInfo->status.threadsStatus.ulbMediaQuit  =  TRUE;

	 traceLogA(  (char*)  "mcThreadProc_mis_media:  leaves"  );

	 return  iErr;
}






























 //  2015/10/01
 //int  drawVideoData(  MC_VAR_isCli  *  pProcInfo,  myDRAW_VIDEO_DATA  *  pkts,  int  pktsLen,  BOOL  *  pbPktsRedirected,  int  iIndex_player  )
 int  drawVideoData(  MC_VAR_isCli  *  pProcInfo,  myDRAW_VIDEO_DATA  *  pkts,  int  pktsLen,  BOOL  *  pbPktsRedirected,  void  *  pQY_TRANSFORM  )
{
	int						iErr						=	-1;
	if  (  !pProcInfo  )  return  -1;
	QY_MC				*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;
	
	QY_TRANSFORM  *  pTransform  =  (  QY_TRANSFORM  *  )pQY_TRANSFORM;
	if  (  !pTransform  )  return  -1;
	int  iIndex_player  =  pTransform->iIndex_player;

	//
#ifdef  __DEBUG__
#endif 

	//
	int		i;
	int		nPkts	=  0;
	nPkts  =  pktsLen  /  sizeof(  myDRAW_VIDEO_DATA  );
	if  (  !nPkts
		||  pktsLen  %  sizeof(  myDRAW_VIDEO_DATA  )  )  
	{
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "drawVideoData pktsLen err"  )  );
		#endif
		goto  errLabel;
	}

	//
#ifdef  __DEBUG__
	if (0) {
		if (nPkts) {
			myDRAW_VIDEO_DATA* p = &pkts[0];
			//
			if (p->idInfo_peer.ui64Id) {
				int  ii = 0;
			}
			//if (p->sharedTex.pktSharedTexInfo.dbg_ui64Id == 924) 
			{
				TCHAR  tBuf[128];
				_sntprintf(tBuf, mycountof(tBuf), _T("drawVideoData: %I64u: index_player %d"), p->sharedTex.pktSharedTexInfo.dbg_ui64Id, iIndex_player);
				showInfo_open0(0, 0, tBuf);
			}
		}
	}
#endif 


	//  2015/09/06
	DWORD  dwTickCnt; dwTickCnt = GetTickCount();

	//
	for  (  i  =  0;  i  <  nPkts;  i  ++  )  {

		 myDRAW_VIDEO_DATA	*	p;
		 int						len;

		 //
		 p  =  &pkts[i];
		 int  iSampleTimeInMs  =  p->head.uiSampleTimeInMs;
		 BITMAPINFO  *  pBmpInfo_input  =  (  BITMAPINFO  *  )&p->bih;	
		 BYTE  *  pInput  =  (  BYTE  *  )p->memory.m_pBuf;
		 unsigned  int  inputLen  =  p->bih.biSizeImage;

		 if  (  inputLen  >  pProcInfo->cfg.uiBufSize_myDrawVideoData  )  {
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "drawVideoData failed: inputLen %d is too big"  ),  inputLen  );
			 goto  errLabel;
		 }
		 if  (  inputLen  !=  pBmpInfo_input->bmiHeader.biSizeImage  )  {
			 #ifdef  __DEBUG__
					 traceLog((TCHAR*)  _T(  "drawVideoData err: inputLen err"  )  );
			 #endif
			 goto  errLabel;
		 }

		 //  len  =  offsetof(  myDRAW_VIDEO_DATA,  buf  )  +  pBmpInfo_input->bmiHeader.biSizeImage;
		 len  =  sizeof(  myDRAW_VIDEO_DATA  );

		 //  
		 p->head.uiTranNo_openAvDev  =  pTransform->video.tv.uiTranNo_openAvDev;	//  2015/10/01	//  Player->video.uiTranNo;	//  2014/11/26
		 //
		 //  p->uiCapType  =  0;
		 //  p->iIndex_capBmp  =  0;
		 //		 	
		 p->iTaskId  =  pTransform->iTaskId;	//  2015/10/01.	//  pPlayer->iTaskId;
#if  0
		 p->uiEventId_lastRecvd  =  pPlayer->video.m_var.uiEventId_lastRecvd;
		 p->hWnd_task  =  pPlayer->video.m_var.hWnd_task;		//  2009/09/09
		 p->idInfo_peer.ui64Id  =  pPlayer->video.m_var.idInfo_peer.ui64Id;
		 //
		 //  p->head.usIndex  =  pPlayer->video.m_var.usIndex;
		 p->usIndex_activeMems_from  =  pPlayer->video.m_var.usIndex;		//  2013/07/18
#endif
	
		 //
		 p->head.uiSampleTimeInMs  =  iSampleTimeInMs;
		 //  p->head.uiSampleTimeInMs_org  =  iSampleTimeInMs_org;
		 	
		 //  2015/09/06
		 p->debugInfo.dwTickCnt_drawVideoData  =  dwTickCnt;
	}

#if  1  //  def  __DEBUG__
		for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
			if  (  !pkts[i].hWnd_task
				&&  !pkts[i].idInfo_peer.ui64Id  )
			{
				#ifdef  __DEBUG__
						traceLog((TCHAR*)  _T(  "drawVideoData: err, pkts[%d].hWnd_task null and idInfo_peer  is 0"  ),  i  );
				#endif

				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "drawVideoData: err, pkts[%d].hWnd_task null and idInfo_peer  is 0"  ),  i  );
			}
		}
		//  traceLog((TCHAR*)  _T(  "drawVideoData: nPkts %d, iIndex_player %d"  ),  nPkts,  iIndex_player  );
#endif
		
	//
	QY_PLAYER  *  pPlayer;
	pPlayer  =  getPlayerByIndex(  pProcInfo,  iIndex_player  );
	if  (  !pPlayer  )  goto  errLabel;

	if  (  !pPlayer->video.bRunning  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "drawVideoData failed: play.video.bRuning is false"  )  );
		#endif
		goto  errLabel;
	}

	//
	if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewAudioStatus  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "drawVideoData : me, %d,%d plays"  ),  pPlayer->video.uiTranNo,  0  );
	}


	//  这里转发的是图像数据的地址，在mcThreadProc_playVideo和其他处理里，要注意这是地址，并且，在接力棒的最后一棒，要注意释放掉。
	if  (  !pbPktsRedirected  ||  *pbPktsRedirected  )  {
		#ifdef  __DEBUG__
				traceLogA(  (char*)  "drawVideoData: pbPktRedirected error"  );
		#endif
		goto  errLabel;
	}
	//
	if  (  pPlayer->video.m_var.status.bNoMsgAndWait  )  {
		if  (  q2PostMsgAndTrigger(  pkts,  pktsLen,  &pPlayer->video.q2,  _T(  "drawVideoData 1"  )))  goto  errLabel;
		}
	else  {
		  if  (  q2PostMsg(  pkts,  pktsLen,  &pPlayer->video.q2,  _T(  "drawVideodata l1321")))  goto  errLabel;
	}
	//  pkt redirected
	*pbPktsRedirected  =  TRUE;

	iErr  =  0;

errLabel:


	//  if  (  pData_allocated  )  free(  pData_allocated  );

	return  iErr;
}

//  2014/05/03
int  getBih_capBmpToPlay(  CAP_procInfo_bmpU  *  pCapBmp,  BITMAPINFOHEADER  *  pBih  )
{
	if  (  !pCapBmp  ||  !pBih  )  return  -1;

	//if  (  !pCapBmp->common.compressVideo.bVideoCompressInited  )  return  -1;
	//
	if  (  pCapBmp->common.compressVideo.ucbResizeByEncoder  )  {
		makeBmpInfoHeader_rgb(  24,  pCapBmp->common.vh_org.bih.biWidth,  pCapBmp->common.vh_org.bih.biHeight,  pBih  );
		}
	else  {
		  memcpy(  pBih,  &pCapBmp->common.compressVideo.vh_decompress.bih,  sizeof(  pBih[0]  )  );
	}
	return  0;
}
	
 //  int  drawLocalVideoData(  MC_VAR_isCli  *  pProcInfo,  unsigned  int  uiTranNo,  BITMAPINFO  *  pBmpInfo_input,  int  iSampleTimeInMs,  BYTE  *  pInput,  unsigned  int  uiCapType,  int  iIndex_capBmp,  int  iTaskId,  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_peer  )
 int  drawLocalVideoData(  MC_VAR_isCli  *  pProcInfo,  unsigned  int  uiTranNo,  myDRAW_VIDEO_DATA	*	pkts,  int  pktsLen,  BOOL  *  pbPktsRedirected,  unsigned  int  uiCapType,  int  iIndex_capBmp,  int  iTaskId,  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_peer  )
{
	int						iErr						=	-1;
	if  (  !pProcInfo  )  return  -1;
	QY_MC				*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;

	if  (  !pkts  ||  !pktsLen  )  return  -1;
	int						nPkts						=	pktsLen  /  sizeof(  myDRAW_VIDEO_DATA  );
	if  (  !nPkts  )  return  -1;
	
	BITMAPINFO	*	pBmpInfo_input  =  (  BITMAPINFO  *  )&pkts[0].bih;

	if  (  !pBmpInfo_input->bmiHeader.biWidth
		||  !pBmpInfo_input->bmiHeader.biHeight
		||  !pBmpInfo_input->bmiHeader.biSizeImage  )
	{
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "drawLocalVideoData failed, pBmpInfo_input err"  )  );
#endif
		return  -1;
	}

	CAP_procInfo_bmpU	*	pCapBmp						=	NULL;
	QY_SHARED_OBJ		*	pSharedObj					=	NULL;
	CAP_procInfo_audioU	*	pCapAudio					=	NULL;

	pCapBmp  =	getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );
	if  (  !pCapBmp  )  goto  errLabel;
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pCapBmp->common.iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	pCapAudio  =  getCapAudioBySth(  pProcInfo,  pSharedObj->iIndex_capAudio,  0  );


	SHARED_OBJ_USR* pSharedObjUsr; pSharedObjUsr = getSharedObjUsr(pSharedObj, pSharedObj->iIndex_curUsr);
	if  (  !pSharedObjUsr  )  goto  errLabel;

#ifdef  __DEBUG__
	if  (  10  )  {
		//  SampleTime  =  0;
		if  (  pktsLen  %  sizeof(  myDRAW_VIDEO_DATA  )  )  {
			traceLogA(  (char*)  "test here"  );
		}
		if  (  pCapBmp->common.uiType  ==  CONST_capType_screen  )  {
			int  ii  =  0;
		}
#if  0
		if  (  !pCapBmp->common.iIndex_sharedObj  )  {
			return  -1;
		}
#endif
	}
#endif


	//
	QY_PLAYER* pPlayer; pPlayer = NULL;
	TCHAR  tBuf[128];

	pPlayer  =  getPlayerByIndex(  pProcInfo,  pSharedObj->iIndex_localPlayer  );
	if  (  pPlayer  )  {
		if  (  pPlayer->idInfo_recorder.ui64Id  !=  0
			||  pPlayer->video.uiTranNo  !=  uiTranNo  )
		{	
#ifdef  __DEBUG__
			_sntprintf(tBuf,mycountof(tBuf),_T("drawLocalVideoData: not correct player. index_localPlayer %d"  ),  pSharedObj->iIndex_localPlayer);
			traceLog(tBuf);
			showInfo_open(0, 0, 0, tBuf);
#endif
			//
			pSharedObj->iIndex_localPlayer  =  -1;
			pPlayer  =  NULL;
		}
	}
	if  (  !pPlayer  )  {
		int						k;

		for  (  k  =  0;  k  <  pProcInfo->av.usCnt_players;  k  ++  )  {
			 if  (  pProcInfo->av.pPlayers[k].idInfo_recorder.ui64Id  ==  0
			 	 &&  pProcInfo->av.pPlayers[k].video.uiTranNo  ==  uiTranNo  )  		 
			 {
				 if  (  !pCapAudio  )  break;
				
#if  0
				 if  (  pProcInfo->av.pPlayers[k].idInfo_recorder.ui64Id  ==  0
					 &&  pProcInfo->av.pPlayers[k].audio.uiTranNo  ==  pCapAudio->common.compressAudio.uiTranNo_openAvDev  )
				 {
					 break;				 		 
				 }
#endif
				 //  2010/09/04
				 if  (  pProcInfo->av.pPlayers[k].idInfo_recorder.ui64Id  ==  0
					 &&  pProcInfo->av.pPlayers[k].audio.uiTranNo  ==  pSharedObjUsr->uiTranNo_openAvDev_a  )
				 {
					 break;				 		 
				 }

			 }
		}

		if  (  k  <  pProcInfo->av.usCnt_players  )  {
			pSharedObj->iIndex_localPlayer  =  k;
			pPlayer  =  getPlayerByIndex(  pProcInfo,  k  );
			if  (  !pPlayer  )  goto  errLabel;
		}
	}

	if  (  !pPlayer  ||  !pPlayer->video.bRunning  )  {

		//  2014/12/10
		DWORD  dwTickCnt  =  myGetTickCount(  mynull  );
		if  (  dwTickCnt  -  pSharedObjUsr->dwLastTickCnt_applyForPlayer  <  200  )  {
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "drawLocalVideoData failed, can't apply for player, too quickly"  )  );
			#endif
			goto  errLabel;
		}
		pSharedObjUsr->dwLastTickCnt_applyForPlayer  =  dwTickCnt;

		
		//  ÕâÀï×é°ü·¢¸øÖ÷Ïß³Ì¡£
		MIS_MSG_applyForPlayer_qmc	msg;
		memset(  &msg,  0,  sizeof(  msg  )  );
		msg.uiType  =  CONST_misMsgType_applyForPlayer_qmc;
		//  msg.idInfo_recorder.ui64Id  =  0;
		msg.video.uiTranNo  =  uiTranNo;
		//
		//  memcpy(  &msg.video.vh.bih,  pBmpInfo_input,  sizeof(  msg.video.vh.bih  )  );
		if  (  getBih_capBmpToPlay(  pCapBmp,  &msg.video.vh.bih  )  )  goto  errLabel;
		//
		//msg.video.ucbFlippedImg  =  pCapBmp->common.compressVideo.compressor.common.ucbOutputFlippedImg;	//  2011/12/11
		//
		msg.video.usFps  =  pCapBmp->common.compressVideo.compressor.common.usMaxFps_toShareBmp;	//  2015/02/20

		//
		bool  bHaveAudio;  bHaveAudio = true;

		//
		if (bHaveAudio) {
			if (pCapAudio) {
				//  msg.audio.uiTranNo  =  pCapAudio->common.compressAudio.uiTranNo_openAvDev;
				msg.audio.uiTranNo = pSharedObjUsr->uiTranNo_openAvDev_a;							//  2010/09/04
				memcpy(&msg.audio.ah, &pCapAudio->common.compressAudio.ah_decompress, sizeof(msg.audio.ah));
				//
				memcpy(&msg.audio.playCfg, &pCapAudio->common.compressAudio.compressor.playCfg, sizeof(msg.audio.playCfg));	//  2012/01/03
			}
		}

		//
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("drawLocalVideoData : me,%d,%d apply for player. index_capBmp %d"), msg.audio.uiTranNo,msg.video.uiTranNo, iIndex_capBmp);


		//					  
		qPostMsg(  &msg,  sizeof(  msg  ),  &pQyMc->gui.processQ,  _T(  "drawLocalVideoData "  ));
			
		PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    

		iErr  =  0;  goto  errLabel;
	}

	if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewAudioStatus  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "drawLocalVideoData : me, %d,%d plays"  ),  uiTranNo,  0  );
	}

	//
	int  i;
	for  (  i  =  0;  i  <  nPkts;  i  ++  )  {

		myDRAW_VIDEO_DATA	*	p							=	&pkts[i];

		p->head.uiTranNo_openAvDev  =  uiTranNo;
		p->uiCapType  =  uiCapType;
		p->iIndex_capBmp  =  iIndex_capBmp;
		p->iTaskId  =  iTaskId;
		p->hWnd_task  =  pSharedObjUsr->hWnd_starter;		//  2009/09/14
		//
		/*
		p->head.uiLen  =  pBmpInfo_input->bmiHeader.biSizeImage;
		p->head.uiSampleTimeInMs  =  iSampleTimeInMs;
		p->head.usIndex  =  0;
		memcpy(  p->buf,  pInput,  p->head.uiLen  );
		*/
		if  (  p->head.uiLen  <  pBmpInfo_input->bmiHeader.biSizeImage  )  {
			traceLogA(  (char*)  "drawLocalVideoData: uiLen error"  );
			goto  errLabel;
		}

		//
		pPlayer->video.m_var.uiSampleTimeInMs_newRecvd  =  p->head.uiSampleTimeInMs;
		pPlayer->video.m_var.dwTickCnt_uiSampleTimeInMs_newRecvd  =  GetTickCount(  );
	
		if  (  p->head.uiSampleTimeInMs  )  {
			if  (  p->head.uiSampleTimeInMs  <  pPlayer->video.m_var.uiSampleTimeInMs  )  {
				traceLogA(  (char*)  "drawLocalVideoData: pkt.uiSampleTimeInMs %d < player.%d. trigger to empty old data",  p->head.uiSampleTimeInMs,  pPlayer->video.m_var.uiSampleTimeInMs  );
				q2TriggerToProcess(  &pPlayer->video.q2  );
			}
			if  (  pPlayer->video.m_var.uiSampleTimeInMs  )  {
				if  (  p->head.uiSampleTimeInMs  >  pPlayer->video.m_var.uiSampleTimeInMs  +  10000  )  {	//  2009/05/25. too old audio data
					traceLogA(  (char*)  "drawLocalVideoData: pkt.uiSampleTimeInMs %d > player.%d  +  10000. trigger to empty old data",  p->head.uiSampleTimeInMs,  pPlayer->video.m_var.uiSampleTimeInMs  );
					q2TriggerToProcess(  &pPlayer->video.q2  );
				}
			}
		}
	}

#ifdef  __DEBUG__
		#if  0
			 traceLog((TCHAR*)  _T(  "drawLocalVideo: iIndex_localPlayer %d, nPkts %d"  ),  pSharedObj->iIndex_localPlayer,  nPkts  );
		#endif	
#endif

	//  这里转发的是图像数据的地址，在mcThreadProc_playVideo和其他处理里，要注意这是地址，并且，在接力棒的最后一棒，要注意释放掉。
	if  (  !pbPktsRedirected  ||  *pbPktsRedirected  )  {
		traceLogA(  (char*)  "drawLocalVideoData: pbPktRedirected error"  );
		goto  errLabel;
	}
	//
	if  (  pPlayer->video.m_var.status.bNoMsgAndWait  )  {
		if  (  q2PostMsgAndTrigger(  pkts,  pktsLen,  &pPlayer->video.q2,  _T(  "drawLocalVideodata 1"  )))  goto  errLabel;
		}
	else  {	
		  if  (  q2PostMsg(  pkts,  pktsLen,  &pPlayer->video.q2,  _T("drawLocalVideoData 2")))  goto  errLabel;
	}
	//
	*pbPktsRedirected  =  TRUE;
	
	iErr  =  0;

errLabel:

	//  if  (  pData_allocated  )  free(  pData_allocated  );

	return  iErr;
}



 int  notifyCapEnd(  void  *  pQY_MC,  unsigned  int  uiCapType,  int  iIndex_capBmp,  int  iTaskId,  HWND  hWnd  )
{
	int		iErr	=	-1;

	QY_MC  *  pQyMc  =  (  QY_MC  *  )pQY_MC;
	if  (  !pQyMc  )  return  -1;

	//
	MIS_MSG_notifyTaskEnd_qmc	msg;
	memset(  &msg,  0,  sizeof(  msg  )  );
	msg.uiType  =  CONST_misMsgType_notifyTaskEnd_qmc;
	msg.iTaskId  =  iTaskId;
	msg.hWnd  =  hWnd;

#if  0
	CQyQ2Help	q2Help;

	if  (  qPostMsg(  &msg,  sizeof(  msg  ),  q2Help.getQ_toPostMsg(  &pQyMc->gui.guiQ2  )  )  )  goto  errLabel;

	PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_guiMsgArrive,  0  );   
#else

	if  (  qPostMsg(  &msg,  sizeof(  msg  ),  &pQyMc->gui.processQ,  _T(  "notifyCapEnd"  )))  goto  errLabel;

	PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );   

#endif


	iErr  =  0;
errLabel:
	return  iErr;
}









 









 //  int  testLocalAv_openLocalVideo(  HWND  hWnd_testWebcam,  void  *  pADeviceGuid,  void  *  pMoniker,  BOOL  *  pbGot_sharedObjIndex_localAv,  int  *  piIndex_sharedObj  )
 int  testLocalAv_openLocalVideo(  HWND  hWnd_testWebcam,  void  *  pADeviceGuid,  LPCTSTR  capDevDesc,  void  *  pMoniker,  BOOL  *  pbGot_sharedObjIndex_localAv,  int  *  piIndex_sharedObj  )
{
	int						iErr						=	-1;
	QY_MC				*	pQyMc						=	QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProcInfo					=	QY_GET_procInfo_isCli(  );
	QY_SHARED_OBJ		*	pSharedObj					=	NULL;
	BOOL					bGot_sharedObjIndex_localAv	=	FALSE;
	BOOL					bFirstUsr					=	FALSE;
	int						iIndex_sharedObjUsr			=	0;
	int						iIndex_sharedObj			=	0;

	int						iIndex_capBmp					=	-1;	
	CAP_procInfo_video	*	pCapBmp							=	NULL;
	int						iIndex_capAudio					=	-1;
	CAP_procInfo_audioCommon	*	pCapAudio						=	NULL;
	//
#if  0
	int						iIndex_shmCmd					=	-1;
	QM_SHM_CMD			*	pShmCmd							=	NULL;
#endif
	//  MIS_CNT				*	pMisCnt						=	getMisCntByName(  pProcInfo,  _T(  ""  )  );	

	CQySyncObj	syncObj;
	if  (  syncObj.sync(  pProcInfo->cfg.mutexName_syncStartAv  )  )  goto  errLabel;

	
	//
	if  (  getNewSharedObjUsr_localAv(  pProcInfo,  hWnd_testWebcam,  &iIndex_sharedObj,  &iIndex_sharedObjUsr,  &bFirstUsr  )  )  {
		//
		TCHAR  tHint[128];
		HWND  hParent  =  hWnd_testWebcam;
		//			
		_sntprintf(  tHint,  mycountof(  tHint  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_notTestAv  )  );			
		showNotification(  0,  0,  0,  0,  0,  0,  tHint  );					
		//
		if (  !bUseD3DFullScreen()  )  {			
			myMessageBox(  hParent,  tHint,  _T(  "www.qycx.com"  ),  MB_OK  );  					
		}
		goto  errLabel;
	}
	//
	pSharedObj  =	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	bGot_sharedObjIndex_localAv  =  TRUE;


	//
	if  (  bFirstUsr  )  {

		iIndex_capBmp  =  newCapProcInfoBmpIndex(  pProcInfo,  iIndex_sharedObj  );
		pCapBmp  =  (  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );
		if  (  !pCapBmp  )  goto  errLabel;
		pCapBmp->uiType  =  CONST_capType_av;
		pCapBmp->iIndex_sharedObj  =  iIndex_sharedObj;
		pCapBmp->uiTranNo_sharedObj  =  pSharedObj->uiTranNo;
		//
#if  0
		iIndex_capAudio  =  newCapProcInfoAudioIndex(  pProcInfo,  iIndex_sharedObj  );
		pCapAudio  =  (  CAP_procInfo_audioCommon  *  )getCapAudioBySth(  pProcInfo,  iIndex_capAudio,  0  );
		if  (  !pCapAudio  )  goto  errLabel;
		pCapAudio->uiType  =  CONST_capType_av;
		pCapAudio->iIndex_sharedObj  =  iIndex_sharedObj;
		pCapAudio->uiTranNo_sharedObj  =  pSharedObj->uiTranNo;
#endif

		//
#if  0
		iIndex_shmCmd  =  newShmCmdIndex(  pProcInfo,  iIndex_sharedObj  );
		pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  iIndex_shmCmd  );
		if  (  !pShmCmd  )  goto  errLabel;
#endif

		//
		//pSharedObj->iIndex_shmCmd  =  iIndex_shmCmd;

		//
		if  (  pCapBmp->bCapDevConnected  )  {
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "testLocalAv_openLocalVideo failed: bCapDevConnected is true"  )  );
			#endif
			goto  errLabel;
		}
	
		//  2011/08/07
		AV_COMPRESSOR_CFG	avCompressor;
		if  (  myGetAvCompressorCfg(  CONST_capType_av,  0,  0,  0,  &avCompressor  )  )  goto  errLabel;

		//  2013/08/03
#if  0
		if  (  pProcInfo->cfg.policy.audio.uiRecordType  ==  CONST_recordType_msAec  )  {
			adjust_audioCompressor_aec(  &avCompressor.audio  );
		}
#endif


		//
		TCHAR	displayName[MAX_monikerDisplayNameLen  +  1]	=	_T(  ""  );	
		TCHAR	tBuf[256]					=	_T(  ""  );
	
		//
		unsigned  short  usCntLimit_activeMems_from = 10;

		//
		if  (  !startLocalAudioRecorder(  pQyMc,  pProcInfo->cfg.policy.audio.uiRecordType,  pADeviceGuid,  capDevDesc,  iIndex_sharedObj,  usCntLimit_activeMems_from,  &avCompressor.audio  )  )  {
				//  m_var.av.ucbLocalAudioRecorderStarted  =  TRUE;			
		}

		//
		if  (  1  )  {
			
			//  2011/07/29			
			if  (  newstartQThreadToShareAv(  pProcInfo,  iIndex_sharedObj,  FALSE  )  )  goto  errLabel;
			
			//
			if  (  getMonikerDisplayName(  pMoniker,  displayName,  mycountof(  displayName  )  )  )  goto  errLabel;
		
			//
			if  (  openLocalVideo(  (  MC_VAR_common  *  )pProcInfo,  pProcInfo->cfg.policy.video.uiCamCapType,  displayName,  NULL,  &avCompressor.video,  iIndex_sharedObj  )  )  {	//  
				qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotFindVideoDevice  )  );  
				goto  errLabel;
			}

			
			//  
			if  (  startCapture(  pProcInfo,  pCapBmp  )  )  {
				qyShowHint(  _T(  "DlgDynBmp: startCapture failed"  )  );  goto  errLabel;
			}			
		}
	
		//
		pCapBmp->curhWnd  =  hWnd_testWebcam;




	}

	//  2013/05/24	
	startLocalAudioPlayer(  pProcInfo  );
	startLocalAudioPlaying(  pProcInfo  );

	//
	if  (  !pCapBmp  )  pCapBmp  =  (  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
	
	SHARED_OBJ_USR* pSharedObjUsr; pSharedObjUsr = getSharedObjUsr(pSharedObj, iIndex_sharedObjUsr);
	if  (  !pSharedObjUsr  )  goto  errLabel;

	if  (  pCapBmp  
		&&  pCapBmp->compressVideo.uiTranNo_openAvDev_org  )  
	{
		pSharedObjUsr->uiTranNo_openAvDev_v  =  pCapBmp->compressVideo.uiTranNo_openAvDev_org  +  iIndex_sharedObjUsr;
	}

	//
	//////////////////////////////////
	//  2014/10/29
	int  iTaskId; iTaskId = 0;
	{
		void	*	pDb	=	NULL;
		#ifndef  __NOTSUPPORT_DB__
				 CQnmDb		db;
				 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
				 pDb  =  db.m_pDbMem->pDb;
		#endif

		iTaskId  =  newTaskId(  pDb,  pQyMc->cfg.db.iDbType  );
		//
		pSharedObjUsr->iTaskId  =  iTaskId;
	}
////////////////////////////////////////////


	//  2010/09/07
	setCurSharedObjUsr_localAv(  pProcInfo,  iIndex_sharedObj,  iIndex_sharedObjUsr  );

	iErr  =  0;

errLabel:

	if  (  pbGot_sharedObjIndex_localAv  )  {
		*pbGot_sharedObjIndex_localAv  =  bGot_sharedObjIndex_localAv;
	}
	if  (  piIndex_sharedObj  )  {
		*piIndex_sharedObj  =  iIndex_sharedObj;
	}

	return  iErr;
}



 int  closeOtherWnds_isCli(  BOOL  *  pbOtherWndExists  )
{
	int						iErr			=		-1;
	QY_MC				*	pQyMc			=		QY_GET_GBUF(  );
	MC_VAR_isCli		*	pVar			=		QY_GET_procInfo_isCli(  );
	if  (  !pVar  )  return  -1;
	BOOL					bOtherWndExists	=		TRUE;
#ifndef  __noMfc__
	//CWaitCursor				cur;
#endif

#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "closeOtherWnds enters"  )  );
#endif

	//  2013/03/09
	if  (  IsWindow(  pVar->subtitles.hWnd_videoTagCfg  )  )  {
		SendMessage(  pVar->subtitles.hWnd_videoTagCfg,  WM_CLOSE,  0,  0  );
		if  (  !IsWindow(  pVar->subtitles.hWnd_videoTagCfg  )  )  pVar->subtitles.hWnd_videoTagCfg  =  NULL;
	}

	//
	if  (  IsWindow(  pVar->hWnd_shareDynBmps  )  )  {
		SendMessage(  pVar->hWnd_shareDynBmps,  WM_CLOSE,  0,  0  );  
		if  (  !IsWindow(  pVar->hWnd_shareDynBmps  )  )  pVar->hWnd_shareDynBmps  =  NULL;
	}

	//
	if  (  IsWindow(  pVar->hWnd_testWebcam  )  )  {
		SendMessage(  pVar->hWnd_testWebcam,  WM_CLOSE,  0,  0  );  
		if  (  !IsWindow(  pVar->hWnd_testWebcam  )  )  pVar->hWnd_testWebcam  =  NULL;
	}

	//  2012/08/02
	QIS_ptz_wnd  *  pPtzWnd  =  &pVar->ptzWnd;
	if  (  IsWindow(  pPtzWnd->hWnd_localPtzControl  )  )  {
		SendMessage(  pPtzWnd->hWnd_localPtzControl,  WM_CLOSE,  0,  0  );
		if  (  !IsWindow(  pPtzWnd->hWnd_localPtzControl  )  )  pPtzWnd->hWnd_localPtzControl  =  NULL;
	}

	//
	if  (  IsWindow(  pVar->hWnd_notification  )  )  {
		SendMessage(  pVar->hWnd_notification,  WM_CLOSE,  0,  0  );  
		if  (  !IsWindow(  pVar->hWnd_notification  )  )  pVar->hWnd_notification  =  NULL;
	}

	//
	if  (  IsWindow(  pVar->hWnd_status_qList  )  )  {
		SendMessage(  pVar->hWnd_status_qList,  WM_CLOSE,  0,  0  );
		if  (  !IsWindow(  pVar->hWnd_status_qList  )  )  pVar->hWnd_status_qList  =  NULL;
	}

	int  i;
	//for  (  i  =  0;  i  <  mycountof(  pVar->misCnts  );  i  ++  )  
	for  (  i  =  0;  i  <  pVar->ucCnt_misCnts;  i  ++  )  
	{
		MIS_CNT  *  pMisCnt  =  getMisCntByIndex(  0,  pVar,  i  );
		if  (  !pMisCnt  )  continue;

		 closeSubWnds(  &pMisCnt->subWnds  );
	}


	//
	if  (  
		!IsWindow(  pVar->subtitles.hWnd_videoTagCfg  )
		&&  !IsWindow(  pVar->hWnd_shareDynBmps  )
		&&  !IsWindow(  pVar->hWnd_testWebcam  )
		&&  !IsWindow(  pVar->ptzWnd.hWnd_localPtzControl  )
		&&  !IsWindow(  pVar->hWnd_notification  )
		&&  !IsWindow(  pVar->hWnd_status_qList  )
		)
	{
		bOtherWndExists  =  FALSE;
	}

	iErr  =  0;

errLabel:

	if  (  pbOtherWndExists  )  *pbOtherWndExists  =  bOtherWndExists;

#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "closeOtherWnds leaves"  )  );
#endif

	return  0;
}


