
#include	"stdafx.h"
#include	<stdio.h>
#include	<stddef.h>
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
//  #include	"myresource.h"
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
#include	"qyThread.h"
#include	"isCmdConst.h"
#include	"qyCusResTemp.h"
//
#include	"policyAvParams.h"


#include	"myDb.h"

#include	"isCliCorePublic.h"
#include	"isCliHelpPublic.h"
#include	"qyMessengerHelpPublic.h"
#include	"imgProcessPublic.h"
#include	"isCliD3dPublic.h"
#include	"qisWallsProc.h"
#include	"qmcObjVarPublic.h"
#include	"qmcTaskPublic.h"
#include	"qmcSharePublic.h"
#include	"dlgShareDynBmpsProc.h"
#include	"funcsForIsCliHelp.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliExPublic.h"
#include	"ctxMcThread.h"

//
#include	"qmcVideoTool.h"


//
__declspec(  dllexport  )  int  postMsg2MgrFunc_mc(  void  *  pMIS_CNT,  MSG_ROUTE  *  pRoute,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  short  usSeqNo,  int  iTaskId,  unsigned  int  uiTaskType,  char  *  data,  unsigned  int  dataLen,  
						QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  
						QY_MESSENGER_ID	 *  pIdInfo_taskSender,					
						QY_MESSENGER_ID	 *  pIdInfo_taskReceiver,				
						QY_MESSENGER_ID  *  pIdInfo_dst,  
						unsigned  int  uiChannelType,
						MIS_MSGU  *  pMsgBuf,  BOOL  bLog  )
{
	 int						iErr		=  -1;

	 MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMIS_CNT;

	 if  (  !pMisCnt  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  "postMsg2MgrFunc_mc failed: pMisCnt is null."  );
		 #endif	
		 return  -1;
	 }

	 MC_VAR_isCli				*	pProcInfo	=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	 if  (  !pProcInfo  )  return  -1;
	 QY_MC					*	pQyMc		=	(  QY_MC  *  )pProcInfo->pQyMc;
	 //  QY_SERVICEGUI_INFO		*	pSci		=	(  QY_SERVICEGUI_INFO  *  )pProcInfo->pSgiParam;
	 CQyMalloc					mallocObj;
	 MIS_MSGU				*	pMsg		=	pMsgBuf;
	 if  (  !pMsg  )  {
		 #ifdef  __DEBUG__
				 if  (  pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
					 OutputDebugString(  _T(  "postMsg2MgrFunc_mc: pMsgBuf is null, need to malloc\n"  )  );
				 }
		 #endif
		 pMsg  =  (  MIS_MSGU  *  )mallocObj.mallocf(  CONST_iAllocType_msg,  sizeof(  MIS_MSGU  )  );
	 }
	 if  (  !pMsg  )  return  -1;
	 int					len			=	0;
	 int					tmpiRet;

	 //  2011/01/23
	 BOOL					bMix		=	FALSE;
#if  0
	 if  (  uiMisMsgType  ==  CONST_misMsgType_outputTask_toMix  )  {
		 bMix  =  TRUE;
		 uiMisMsgType  =  CONST_misMsgType_task;
	 }
#endif

	 //
	 if  (  makeMsg2MgrFunc_mc(  pMisCnt,  pRoute,  uiMisMsgType,  ucFlg,  usCode,  tStartTime,  uiTranNo,  usSeqNo,  iTaskId,  uiTaskType,  data,  dataLen,  pIdInfo_logicalPeer,  pIdInfo_taskSender,  pIdInfo_taskReceiver,  pIdInfo_dst,  uiChannelType,  pMsg,  &len  )  )  {
		 goto  errLabel;
	 }

	 if  (  pMsg->uiType  ==  CONST_misMsgType_outputTask  )  {		//  2008/05/13, ¶ÔoutputTask, Ö±½Ó·¢µ½Êä³ö¶ÔÁÐÀïÁË
		 MIS_CNT					*		pMisCnt							=  (  MIS_CNT  *  )pMsg->task.pMisCnt;
		 MIS_CHANNEL				*		pChannel						=	NULL;

		 if  (  !pMisCnt  )  goto  errLabel;
		 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  pMsg->task.uiChannelType  )  )  )  goto  errLabel;

		 if  (  procMsgTask2Output_mc(  pProcInfo,  pMisCnt,  &pMsg->task,  len,  pChannel,  _T(  "postMsg2MgrFunc_mc"  )  )  )  goto  errLabel;

		 iErr  =  0;  goto  errLabel;

	 }

	 //  2011/01/23
#if  0
	 if  (  bMix  )  {

		 if  (  (  tmpiRet  =  pProcInfo->processQ_media.qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsg,  0  )  )  <=  0  )  {
			 #ifdef  __DEBUG__
					 traceLog(  _T(  "postMsg2MgrFunc_mc: msg_task_toMix"  ),  tmpiRet  ?  "failed"  :  "not found"  );
			 #endif
			 goto  errLabel;
		 }

		 iErr  =  0;  goto  errLabel;
	 }
#endif

	 //  printMisMsg(  0,  0,  &msg  );

	 //  2015/09/09
#if  0
	 if  (  uiMisMsgType  ==  CONST_misMsgType_input  )  {
		 MIS_CHANNEL  *  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  );
		 if  (  !pChannel  )  goto  errLabel;
		 //
		 tmpiRet  =  q2PostMsgAndTrigger(  pMsg,  len,  &pChannel->inputQ2  );
		 if  (  tmpiRet  )  {
			 iErr  =  tmpiRet;  goto  errLabel;
		 }
		 //
		 iErr  =  0;  goto  errLabel;
	 }
#endif


	 //
	 switch  (  uiChannelType  )  {
			 case  CONST_channelType_robot:
				   if  (  (  tmpiRet  =  qPostMsgAndTrigger(  pMsg,  len,  &pProcInfo->robotQ,  _T(  "postMsg2MgrFunc_mc" )))) {
					   iErr  =  tmpiRet;  goto  errLabel;
				   }
				   break;
			 case  CONST_channelType_media:  {
				   //  CQyQ2Help	q2Help;

				   if  (  (  tmpiRet  =  q2PostMsgAndTrigger(  pMsg,  len,  &pProcInfo->mediaQ2,  _T(  "postMsg2MgrFunc 2"  )))) {
					   iErr  =  tmpiRet;  goto  errLabel;
				   }
				   }
				   break;				   
			 case  CONST_channelType_realTimeMedia:  {
				   if  (  (  tmpiRet  =  q2PostMsgAndTrigger(  pMsg,  len,  &pProcInfo->realTimeMediaQ2,  _T(  "postMsg2MgrFunc 3"  )))) {
					   iErr  =  tmpiRet;  goto  errLabel;
				   }
				   }
				   break;
			 case  CONST_channelType_rtOp:  {
				   if  (  (  tmpiRet  =  q2PostMsgAndTrigger(  pMsg,  len,  &pProcInfo->rtOpQ2,  _T(  "postMsg2MgrFunc 4"  )))) {
					   iErr  =  tmpiRet;  goto  errLabel;
				   }
				   }
				   break;
			 default:
				    if  (  (  tmpiRet  =  qPostMsgAndTrigger(  pMsg,  len,  &pProcInfo->mgrQ,  _T(  "postMsg2MgrFunc 5"  )))) {
						iErr  =  tmpiRet;  goto  errLabel;
					}
					break;
	 }


	 if  (  bLog  )  {	//  2010/07/22
		 postImMsg2Log_isClient(  pMsg,  len  );
	 }

	 iErr  =  0;

errLabel:
	 return  iErr;
}


//
__declspec(  dllexport  )  int  postImMsg2Log_isClient(  MIS_MSGU  *  pMsg,  int  lenInBytes_msg  ) 
{
	int		iErr	=	-1;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	int				tmpiRet		=	-1;
	
#ifdef  __WINCE__
	tmpiRet  =  qTraverse(  &pProcInfo->imMsgLogQ,  (  PF_commonHandler  )tmpHandler_searchImMsgLog,  0,  pMsg  );
	if  (  tmpiRet  <  0  )  return  -1;
	if  (  tmpiRet  )  {
		return  tmpiRet;
	}

	if  (  isQFull(  &pProcInfo->imMsgLogQ  )  )  {
		MIS_CNT	*	pMisCnt	=	NULL;
		switch  (  pMsg->uiType  )  {
				case  CONST_misMsgType_talk:
					  pMisCnt  =  (  MIS_CNT  *  )pMsg->talk.pMisCnt;
					  break;
				case  CONST_misMsgType_task:
					  pMisCnt  =  (  MIS_CNT  *  )pMsg->task.pMisCnt;
					  break;
				default:
						break;
		}

		int		iQNodes		=	pProcInfo->imMsgLogQ.uiQNodes;
		TCHAR	tBuf[64]	=	_T(  ""  );

		//
		traceLog(  _T(  "logImMsg_ce: q is full, start to remove some msg"  )  );
		qRemoveMsg(  &pProcInfo->imMsgLogQ,  (  PF_bCommonHandler  )tmpHandler_bRemoveImMsgLog,  &pProcInfo->imMsgLogQ,  0  );
		traceLog(  _T(  "logImMsg_ce: q has %d msgs"  ),  pProcInfo->imMsgLogQ.uiQNodes  );
		//

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "imMsgLogQ is full, to remove some msg, %d -> %d"  ),  iQNodes,  pProcInfo->imMsgLogQ.uiQNodes  );
		showNotification(  pMisCnt,  NULL,  NULL,  0,  0,  0,  tBuf  );

	}
#endif

	qPostMsg(  pMsg,  lenInBytes_msg,  &pProcInfo->imMsgLogQ,  _T(  "postImMsg2Log_isCli"  ));

#ifndef  __WINCE__
	if  (  qPostMsgAndTrigger(  NULL,  0,  &pProcInfo->schedulerQ,  _T(  "postImMsg2Log_isCli 1"  )))  goto  errLabel;
#endif
	
	iErr  =  0;

	iErr  =  0;
errLabel:
	return  iErr;
}


//   
 __declspec(  dllexport  )  int  makeMsg2MgrFunc_mc(  MIS_CNT  *  pMisCnt,  MSG_ROUTE  *  pRoute,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  short  usSeqNo,  int  iTaskId,  unsigned  int  uiTaskType,  char  *  data,  unsigned  int  dataLen,  
							QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  
	 						QY_MESSENGER_ID	 *  pIdInfo_taskSender,					
							QY_MESSENGER_ID	 *  pIdInfo_taskReceiver,				
							QY_MESSENGER_ID  *  pIdInfo_dst,  
							unsigned  int  uiChannelType,  MIS_MSGU  *  pMsg,  int  *  pMsgLen  )
{
	 int					iErr		=  -1;
	 int					len			=	0;

	 if  (  !pMsg  )  {
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "makeMsg2MgrFunc_mc failed, pMsg is null"  )  );
		 #endif
		 return  -1;
	 }

	 MACRO_memset_misMsg(  pMsg  );
	 pMsg->uiType  =  uiMisMsgType;
	 switch  (  pMsg->uiType  )  {
			 case  CONST_misMsgType_input:
				   //
				   pMsg->input.pMisCnt  =  pMisCnt;
				   //
				   pMsg->input.ucFlg  =  ucFlg;
				   pMsg->input.usCode  =  usCode;
				   //
				   pMsg->input.tStartTime  =  tStartTime;
				   pMsg->input.uiTranNo  =  uiTranNo;
				   pMsg->input.usSeqNo  =  usSeqNo;
				   //
				   mytime(  &pMsg->input.tRecvTime  );						//  2008/04/05
				   pMsg->input.dwTickCnt_start  =  GetTickCount(  );		//  2008/05/23		
				   //
				   pMsg->input.uiChannelType  =  uiChannelType;				//  2008/04/17
				   //
				   pMsg->input.uiChannelType_input  =  uiChannelType;		//  2017/10/03
				   //
				   //  pMsg->input.usDataType;
				   pMsg->input.lenInBytes  =  min(  sizeof(  pMsg->input.data  ),  dataLen  );
				   memcpy(  &pMsg->input.data,  data,  pMsg->input.lenInBytes  );
				   //
				   len  =  offsetof(  MIS_MSG_INPUT,  data  )  +  pMsg->input.lenInBytes;

				   break;
			 case  CONST_misMsgType_req:
				   //
				   pMsg->req.pMisCnt  =  pMisCnt;
				   //
				   pMsg->req.ucFlg  =  ucFlg;
				   //
				   pMsg->req.usCode  =  usCode;
				   //
				   pMsg->req.tStartTime  =  tStartTime;
				   pMsg->req.uiTranNo  =  uiTranNo;
				   pMsg->req.usSeqNo  =  usSeqNo;
				   //
				   pMsg->req.lenInBytes  =  min(  sizeof(  pMsg->req.data  ),  dataLen  );
				   memcpy(  &pMsg->req.data,  data,  pMsg->req.lenInBytes  );
				   //
				   len  =  offsetof(  MIS_MSG_REQ,  data  )  +  pMsg->req.lenInBytes;
				   break;
			 case  CONST_misMsgType_talk:
				   //
				   pMsg->talk.pMisCnt  =  pMisCnt;
				   //
				   pMsg->talk.ucFlg  =  ucFlg  |  CONST_commFlg_routeTalkData;
				   pMsg->talk.usCode  =  usCode;
				   //
				   pMsg->talk.tStartTime  =  tStartTime;
				   pMsg->talk.uiTranNo  =  uiTranNo;
				   pMsg->talk.usSeqNo  =  usSeqNo;
				   //
				   if  (  pRoute  )  memcpy(  &pMsg->talk.data.route,  pRoute,  sizeof(  pMsg->talk.data.route  )  );
				   else  pMsg->talk.data.route.idInfo_from.ui64Id  =  pMisCnt->idInfo.ui64Id;
				   //				   
				   if  (  pIdInfo_dst  )  pMsg->talk.data.route.idInfo_to.ui64Id  =  pIdInfo_dst->ui64Id;
				   //
				   if  (  pIdInfo_logicalPeer  )  pMsg->talk.addr_logicalPeer.idInfo.ui64Id  =  pIdInfo_logicalPeer->ui64Id;  //  ÕâÀï¸³ÉÏÁËÄ¿±ê·½
				   else  {
						 #ifdef  __DEBUG__
								 traceLogA(  "msgTalk: no logicalPeer"  );						 
						 #endif
				   }
				   //
				   pMsg->talk.uiChannelType  =  uiChannelType;		//  2008/04/17
				   //
				   len  =  min(  sizeof(  pMsg->talk.data.buf  ),  dataLen  );
				   memcpy(  pMsg->talk.data.buf,  data,  len  );
				   //
				   pMsg->talk.lenInBytes  =  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  len;
				   //
				   len  =  offsetof(  MIS_MSG_TALK,  data  )  +  pMsg->talk.lenInBytes;
				   
				   break;
			 case  CONST_misMsgType_task:
			 case  CONST_misMsgType_outputTask:
				   //
				   pMsg->task.pMisCnt  =  pMisCnt;
				   //
				   pMsg->task.ucFlg  =  ucFlg  |  CONST_commFlg_routeTalkData;
				   pMsg->task.usCode  =  usCode;
				   //
				   pMsg->task.tStartTime  =  tStartTime;
				   pMsg->task.uiTranNo  =  uiTranNo;
				   pMsg->task.usSeqNo  =  usSeqNo;
				   //
				   pMsg->task.iTaskId  =  iTaskId;
				   pMsg->task.uiTaskType  =  uiTaskType;
				   //
				   if  (  pRoute  )  memcpy(  &pMsg->task.data.route,  pRoute,  sizeof(  pMsg->task.data.route  )  );
				   else  pMsg->task.data.route.idInfo_from.ui64Id  =  pMisCnt->idInfo.ui64Id;
				   //
				   if  (  pIdInfo_dst  )  pMsg->task.data.route.idInfo_to.ui64Id  =  pIdInfo_dst->ui64Id;
				   //
				   if  (  pIdInfo_logicalPeer  )  pMsg->task.addr_logicalPeer.idInfo.ui64Id  =  pIdInfo_logicalPeer->ui64Id;  //  ÕâÀï¸³ÉÏÁËÄ¿±ê·½
				   else  {
					     //  traceLogA(  "msgTask: no logicalPeer"  );						 
				   }

				   if  (  pIdInfo_taskSender  )  pMsg->task.idInfo_taskSender.ui64Id  =  pIdInfo_taskSender->ui64Id;
				   if  (  pIdInfo_taskReceiver  )  pMsg->task.idInfo_taskReceiver.ui64Id  =  pIdInfo_taskReceiver->ui64Id;
				   
				   if  (  !pMsg->task.dwTickCnt_start  )  pMsg->task.dwTickCnt_start  =  GetTickCount(  );	//  2009/03/22
				   //
				   pMsg->task.uiChannelType  =  uiChannelType;		//  2008/04/17

				   //
				   len  =  min(  sizeof(  pMsg->task.data.buf  ),  dataLen  );
				   memcpy(  pMsg->task.data.buf,  data,  len  );
				   //
				   pMsg->task.lenInBytes  =  offsetof(  MIS_MSG_routeTalkData,  buf  )  +  len;
				   //
				   len  =  offsetof(  MIS_MSG_TASK,  data  )  +  pMsg->task.lenInBytes;

				   break;
			 default:
					#ifdef  __DEBUG__
							traceLogA(  "makeMsg2MgrFunc_mc failed: unkown msg, %S",  qyGetDesByType1(  CONST_misMsgTypeTable,  pMsg->uiType  )  );
					#endif
					goto  errLabel;
					
	 }

	 //
	 if  (  !len  )  goto  errLabel;

	 iErr  =  0; 

errLabel:

	 if  (  !iErr  )  {	 
		 if  (  pMsgLen  )  {
			 *pMsgLen  =  len;
		 }
	 }

	 return  iErr;
}


//
//  lenInBytes
 __declspec(  dllexport  )  int  procMsgTask2Output_mc(  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSG_TASK  *  pMsgTask,  unsigned  int  lenInBytes_msg,  MIS_CHANNEL  *  pChannel,  LPCTSTR  tHint  )
{
	 int							iErr				=	-1;
	 QY_MC					*		pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;	 
	 IM_CONTENTU			*		pContent			=	M_getMsgContent(  pMsgTask->ucFlg,  &pMsgTask->data  );
	 if  (  !tHint  )  tHint  =  _T(  ""  );
	 
	 //
	 if  (  !pMsgTask->data.route.idInfo_to.ui64Id  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  "procMsgTask2Output_mc failed: route.idInfo_to is 0"  );  
		 #endif
		 goto  errLabel;
	 }
	 pMsgTask->data.route.idInfo_from.ui64Id  =  pMisCnt->idInfo.ui64Id;


	 //  2015/08/22
#ifdef  __DEBUG__

#endif


	 //
	 Param_dbg param;
	 param.m_pHint=_T("procMsgTask2Output_mc.452");
	 //
	 unsigned  char  tmp_bChannelOk  =  bChannelOk(  pChannel,  &param  );
	 if  (  !tmp_bChannelOk  )  {
#if  0
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "procMsgTask2Output_mc failed: %s is not ready"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
		 #endif
		 qyShowInfo1(  CONST_qyShowType_debugWarning,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procMsgTask2Output_mc failed: %s is not ready"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
#endif
		 //  2015/08/22
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "procMsgTask2Output_mc failed: %s is not ready. %s"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  ),  tHint  );
		 #endif
		 qyShowInfo1(  CONST_qyShowType_debugWarning,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procMsgTask2Output_mc failed: %s is not ready. %s"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  ),  tHint  );

	 }
	 if  (  pContent  )  {
		 switch  (  pContent->uiType  )  {
			     case  CONST_imCommType_transferVideoData:	
				 case  CONST_imCommType_transferAudioData:
				 case  CONST_imCommType_remoteAssistReq:
				 case  CONST_imCommType_ptzControlReq:					//  2012/8/07
				 case  CONST_imCommType_ptzControlCmd:
					   if  (  !tmp_bChannelOk  )  {
						   goto  errLabel;
					   }
					   break;
				 default:
					     break;
		 }
	 }


	 {
		 CQyQ2Help						q2Help;
		 if  (  qPostMsg(  pMsgTask,  lenInBytes_msg,  q2Help.getQ_toPostMsg(  &pChannel->toSendQ2  ),  _T("procMsgTask2Output"  ))) {
			 if  (  !isQFull(  q2Help.getQ_toPostMsg(  &pChannel->toSendQ2  )  )  )  {	//  2008/11/21
				 goto  errLabel;
				 }
			 else  {
				    switch  (  pChannel->uiType  )  {						
							case  CONST_channelType_media:		 
							case  CONST_channelType_realTimeMedia:							   
								  emptyGenericQ(  q2Help.getQ_toPostMsg(  &pChannel->toSendQ2  )  );
								  qyShowInfo1(  CONST_qyShowType_debugWarning,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procMsgTask2Output_mc: emptyQ now"  )  );
								  break;
							default:
									break;				 
					}				 
					//  2015/08/22. 队列满时，不能退出，应接着触发发送
			 }
		 }
	 }

	 if  (  !q2PostMsgAndTrigger(  0,  0,  &pChannel->outputQ2,  _T(  "procMsgTask2Output_mc"  ))) {
		 //  2008/11/22
		 if  (  pChannel->outputQ2.ucbTriggerErr  )  q2AvoidTriggerTooHigh(  0,  &pChannel->outputQ2  );
	 }


	 iErr  =  0;

errLabel:

	 return  iErr;
}


 //
 #if  1	//def  __DEBUG__

 __declspec(  dllexport  )  int  postMsg2Mgr_mc(  void  *  pMIS_CNT,  MSG_ROUTE  *  pRoute,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  char  *  data,  unsigned  int  dataLen,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  uiChannelType,  MIS_MSGU  *  pMsgBuf,  BOOL  bLog  )
{
	return  postMsg2MgrFunc_mc(  pMIS_CNT,  pRoute,  uiMisMsgType,  ucFlg,  usCode,  tStartTime,  uiTranNo,  uiSeqNo,  0,  0,  data,  dataLen,  pIdInfo_logicalPeer,  NULL,  NULL,  pIdInfo_dst,  uiChannelType,  pMsgBuf,  bLog  );
}


 __declspec(  dllexport  )  int  postMsgTask2Mgr_mc(  void  *  pMIS_CNT,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  int  iTaskId,  unsigned  int  uiTaskType,  char  *  data,  unsigned  int  dataLen,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_taskSender,  QY_MESSENGER_ID  *  pIdInfo_taskReceiver,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  uiChannelType,  MIS_MSGU  *  pMsgBuf,  BOOL  bLog  )
{
	return  postMsg2MgrFunc_mc(  pMIS_CNT,  NULL,  uiMisMsgType,  ucFlg,  usCode,  tStartTime,  uiTranNo,  uiSeqNo,  iTaskId,  uiTaskType,  data,  dataLen,  pIdInfo_logicalPeer,  pIdInfo_taskSender,  pIdInfo_taskReceiver,  pIdInfo_dst,  uiChannelType,  pMsgBuf,  bLog  );
}

#endif



