
#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	<time.h>
#include	<stddef.h>
#include	<ShellAPI.h>
#include	<tchar.h>

#include	"qymcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"
#include	"qyCusResTemp.h"

#include	"dlgTalkProc.h"




//
   CQyString  getQmInternalUrl(  int  iTaskId,  LPCTSTR  rowIdStr,  int  iOp,  LPCTSTR  paramStr,  LPCTSTR  displayStr  )
{
	TCHAR	opStr[32]		=	_T(  ""  );
	TCHAR	taskIdStr[32]	=	_T(  ""  );

	_ltot(  iOp,  opStr,  10  );
	_ltot(  iTaskId,  taskIdStr,  10  );

	CQyString	str;
	str  =  CQyString( (char*) "<a href=\""  )  +  CQyString(  CONST_qmInternalUrl_root  )  +  CQyString(  taskIdStr  )  +  CQyString(  (char*)"/"  )  +  CQyString(  rowIdStr  ?  rowIdStr  :  CQyString(  (char*)""  )  )  +  CQyString(  (char*)"/"  )  +  CQyString(  opStr  )  +  CQyString(  (char*)"/"  )  +  CQyString(  paramStr  ?  paramStr  :  _T(  ""  )  )  +  CQyString(  (char*)"/default.htm\">"  )  +  CQyString(  displayStr  )  +  CQyString(  (char*)"</a>"  );
	//  return  CQyString(  "<a href=\""  )  +  CONST_qmInternalUrl_root  +  taskIdStr  +  _T(  "/"  )  +  (  rowIdStr  ?  rowIdStr  :  _T(  ""  )  )  +  _T(  "/"  )  +  opStr  +  _T(  "/"  )  +  (  paramStr  ?  paramStr  :  _T(  ""  )  )  +  _T(  "/default.htm\">"  )  +  displayStr  +  _T(  "</a>"  );
	return  str;
}


 int  tmpMakeHtmlStr(  QY_MC  *  pQyMc,  MIS_MSGU  *  pMsg,  int  iStatus,  BOOL  bIncludeUrl,  LPCTSTR  rowIdStr,  LPCTSTR  paramStrBuf,  QY_MESSENGER_ID  *  pIdInfo_talker,  TCHAR  *  tBuf,  unsigned  int  cnt  )
{
	int						iErr						=	-1;
	//QY_MC				*	pQyMc						=	QY_GET_GBUF(  );
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	QY_MESSENGER_ID			idInfo_tmpTalker			=	{	0,	};
	QY_MESSENGER_ID			idInfo_logicalReceiver		=	{	0,	};
	TCHAR					tDir[MAX_PATH  +  1]		=	_T(  ""  );
	TCHAR					tFile[MAX_PATH  +  1]		=	_T(  ""  );
	char					buf[255  +  1]				=	"";
    
	if  (  !pMsg  ||  !tBuf  ||  !cnt  )  return  -1;
	
	if  (  !rowIdStr  )  rowIdStr  =  _T(  ""  );
	if  (  !paramStrBuf  )  paramStrBuf  =  _T(  ""  );

	tBuf[0]  =  0;

	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_task:  {
				  IM_CONTENTU			*	pContent					=	(  IM_CONTENTU  *  )pMsg->task.data.buf;				  
				  MIS_CNT				*	pMisCnt						=	(  MIS_CNT  *  )pMsg->task.pMisCnt;
				  
				  if  (  !pMsg->task.pMisCnt  ||  !pMsg->task.idInfo_taskSender.ui64Id  &&  !pMsg->task.idInfo_taskReceiver.ui64Id  )  {
					  traceLogA(  (char*)  "tmpMakeHtmlStr: taskSenderºÍtaskReceiver Ã»ÓÐ¸³Öµ"  );  goto  errLabel;
				  }

				  //  ÕâÀïµÄ¼ÆËã£¬ÊÇÎªÁËÓÐÐ©ÏûÏ¢ÊÇ×÷Îª×é³ÉÔ±½ÓÊÕµÄ£¬ËùÒÔÒª»»³ÉÎÒÀ´ÏÔÊ¾
				  if  (  pMisCnt->idInfo.ui64Id  ==  pMsg->task.idInfo_taskSender.ui64Id  )  {	//  ÕâÀï²»ÓÃ¾«È··ÖÎöÁË
					  idInfo_logicalReceiver.ui64Id  =  pMsg->task.idInfo_taskReceiver.ui64Id;	
					  }
				  else  if  (  pMisCnt->idInfo.ui64Id  ==  pMsg->task.idInfo_taskReceiver.ui64Id  )  idInfo_logicalReceiver.ui64Id  =  pMsg->task.idInfo_taskReceiver.ui64Id;
				  else  {
					    QM_OBJQ_MEM				mem;
						QMEM_MESSENGER_CLI	*	pQMemObj;
						if  (  findQMemByKey(  0,  pMisCnt->pObjQ,  &pMsg->task.idInfo_taskReceiver,  &mem  )  )  goto  errLabel;
						pQMemObj  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
						if  (  !pQMemObj  )  goto  errLabel;
						if  (  pQMemObj->uiType  !=  CONST_objType_imGrp  )  idInfo_logicalReceiver.ui64Id  =  pMsg->task.idInfo_taskReceiver.ui64Id;
						else  idInfo_logicalReceiver.ui64Id  =  pMisCnt->idInfo.ui64Id;
					     
				  }

				  //
				  idInfo_tmpTalker.ui64Id  =  pMsg->task.idInfo_taskSender.ui64Id;
				  switch  (  iStatus  )  {
						  case  CONST_imTaskStatus_recvBreak:						
						  case  CONST_imTaskStatus_waitToRecv:
						  case  CONST_imTaskStatus_recvFinished:
						  case  CONST_imTaskStatus_canceledByReceiver:
						  case  CONST_imTaskStatus_deniedByReceiver:
							    idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;											  
								break;
						  default:
								break;				  
				  }


			#ifndef  __WINCE__
				  //
				  switch  (  pContent->uiType  )  {
						  case  CONST_imCommType_transferFileReq:
							    switch  (  iStatus  )  {
										case  CONST_imTaskStatus_applyToSend:	
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s, %s: %s, %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_reqToSend  ),
																				pContent->transferFileReq.fullFilePath,  
																				getResStr(  0,  &pQyMc->cusRes,  CONST_resId_pleaseSelect  ),
																				bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_send_permit,  0,  _T(  "Allow"  )  )  :  _T(  "Allow"  ),
																				bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_send_cancel,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  )  );
											  break;
										case  CONST_imTaskStatus_sendBreak:
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_sendFile  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_interupted  ),  
																				pContent->transferFileReq.fullFilePath  );												  												  
											  break;
										case  CONST_imTaskStatus_waitToSend:
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s, %s %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_willSendFile  ),  
																				pContent->transferFileReq.fullFilePath,
																				getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canSelect  ),
																				bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_send_cancel,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_toInterupt  )  );
											  break;
										case  CONST_imTaskStatus_sendFinished:
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s"  ),  pContent->transferFileReq.fullFilePath,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_sendFinished  )  );
											  break;
										case  CONST_imTaskStatus_applyToRecv:
											 _sntprintf(  tBuf,  cnt,  _T(  "%s %s, %s: %s, %s, %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_pleaseRecvFile  ),
																				pContent->transferFileReq.fullFilePath,  
																				getResStr(  0,  &pQyMc->cusRes,  CONST_resId_select  ),
																				bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_recv_accept,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_accept  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_accept  ),  
																				bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_recvFile_saveas,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_saveAs  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_saveAs  ),  
																				bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_recv_deny,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_deny  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_deny  )  );

											  break;
										case  CONST_imTaskStatus_recvBreak:
											  //  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;											  
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_recvFile  ),  
																				pContent->transferFileReq.fullFilePath,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_interupted  )  );
											  break;
										case  CONST_imTaskStatus_waitToRecv:
											  //  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;											  
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s, %s %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_accepted  ),  pContent->transferFileReq.fileName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canSelect  ),  bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_recv_cancel,  paramStrBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_toInterupt  )  );
											  break;		
										case  CONST_imTaskStatus_recvFinished:  {
											  //  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;
											  if  (  pProcInfo->getDirAndFinalName(  pContent->transferFileReq.fullFilePath,  tDir,  mycountof(  tDir  ),  tFile,  mycountof(  tFile  )  )  )  {
												  tDir[0]  =  0;  tFile[0]  =  0;
											  }
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s, &s %s %s %s"  ),  pContent->transferFileReq.fileName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_recvFinished  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_saved  ),  bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_openFile,  tDir,  tDir  )  :  tDir,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_zhongDe  ),  tFile  );											  
											  //
											  }
											  break;
										case  CONST_imTaskStatus_canceledBySender:
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_faSong  ),  pContent->transferFileReq.fullFilePath,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canceled  )  );
											  break;
										case  CONST_imTaskStatus_canceledByReceiver:
											  //  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_jieShou  ),pContent->transferFileReq.fullFilePath,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canceled  )  );
											  break;
										case  CONST_imTaskStatus_deniedByReceiver:
											  //  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_denied  ),  pContent->transferFileReq.fullFilePath  );
											  break;
										default:
											    break;
								}
								break;
						  case  CONST_imCommType_transferAvInfo:
							    switch  (  iStatus  )  {
										case  CONST_imTaskStatus_req:
										case  CONST_imTaskStatus_acceptedByReceiver:	//  2012/06/03
										case  CONST_imTaskStatus_dualByReceiver:		//  2012/06/03
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s, %s %s %s, %s %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qingqiu  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->task.uiTaskType  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canSelect  ),
																				bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_send_cancel,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  )  )  :  getResStr(  0, &pQyMc->cusRes,  CONST_resId_quXiao  ),  
                                                                                getResStr(  0,  &pQyMc->cusRes,  CONST_resId_toInterupt  ),
																				getResStr(  0,  &pQyMc->cusRes,  CONST_resId_select  ),
																				bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_send_permit,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_sendAgain  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_sendAgain  ),
																				getResStr(  0,  &pQyMc->cusRes,  CONST_resId_toRequestAgain  )
																				);												  											  
											  break;
										case  CONST_imTaskStatus_resp:
											  switch  (  pContent->transferAvInfo.uiTaskType  )  {
													  case  CONST_imTaskType_transferAvInfo:
														    _sntprintf(  tBuf,  cnt,  _T(  "%s %s. %s %s: %s, %s, %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qingqiu  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->task.uiTaskType  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ifAcceptVideo  ),  getResStr(  0, &pQyMc->cusRes,  CONST_resId_pleaseSelect  ),
																				bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_dual_permit,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_y  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_y  ),  
																				bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_recv_accept,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_n  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_n  ),
																				bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_recv_deny,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_deny  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_deny  )  );

														    break;
													  case  CONST_imTaskType_shareScreen:
													  default:
														     _sntprintf(  tBuf,  cnt,  _T(  "%s %s. %s: %s, %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qingqiu  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->task.uiTaskType  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_pleaseSelect  ),
																				bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_recv_accept,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_accept  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_accept  ),  
																				bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_recv_deny,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_deny  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_deny  )  );
															  break;
											  }
											  break;
										case  CONST_imTaskStatus_waitToRecv:
											  //  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;											  
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s, %s %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_accepted  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->task.uiTaskType  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canSelect  ),  bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_recv_cancel,  paramStrBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_toInterupt  )  );
											  break;		
										case  CONST_imTaskStatus_canceledBySender:
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s"  ),  qyGetDesByType1(  getResTable(  0, &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->task.uiTaskType  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canceled  )  );
											  break;
										case  CONST_imTaskStatus_canceledByReceiver:
  											  //  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;											
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->task.uiTaskType  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canceled  )  );
											  break;
										case  CONST_imTaskStatus_deniedByReceiver:
										case  CONST_imTaskStatus_recvBreak:
											  //  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;
											  _sntprintf(  tBuf,  cnt,  _T(  "%s: %s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskStatusTable  ),  iStatus  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->task.uiTaskType  )  );
											  break;
										default:
											    break;
								}							    
							    break;
						  case  CONST_imCommType_queryCustomerServiceOfficerReq:
							    switch  (  iStatus  )  {																
										case  CONST_imTaskStatus_resp:
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s. %s: %s, %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qingqiu  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->task.uiTaskType  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_pleaseSelect  ),
																				bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_recv_accept,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_accept  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_accept  ),  
																				bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_recv_deny,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_deny  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_deny  )  );
											  break;
										case  CONST_imTaskStatus_waitToRecv:
											  //  _sntprintf(  tBuf,  cnt,  _T(  "%s %s, %s %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_accepted  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->task.uiTaskType  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canSelect  ),  bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_recv_cancel,  paramStrBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_toInterupt  )  );											
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_accepted  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->task.uiTaskType  )  );
											  break;		
										case  CONST_imTaskStatus_canceledBySender:
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s"  ),  qyGetDesByType1(  getResTable(  0, &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->task.uiTaskType  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canceled  )  );
											  break;
										case  CONST_imTaskStatus_canceledByReceiver:
  											  //  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;											
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->task.uiTaskType  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canceled  )  );
											  break;
										case  CONST_imTaskStatus_deniedByReceiver:
										case  CONST_imTaskStatus_recvBreak:
											  //  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;
											  _sntprintf(  tBuf,  cnt,  _T(  "%s: %s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskStatusTable  ),  iStatus  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->task.uiTaskType  )  );
											  break;
										default:
												break;
								}
							    break;
						  case  CONST_imCommType_rtcCallReq:
						  default:
							     switch  (  iStatus  )  {
										 case  CONST_imTaskStatus_req:
											   _sntprintf(  tBuf,  cnt,  _T(  "%s: %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qingqiu  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->task.uiTaskType  )  );
											   break;
										 case  CONST_imTaskStatus_resp:
											   _sntprintf(  tBuf,  cnt,  _T(  "&s: %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qingqiu  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->task.uiTaskType  )  );										   											   
											   break;
										 default:
												break;
								 }
								 break;
				  }
			#endif
				  //
				  }
				  break;


			case  CONST_misMsgType_taskStatus:  {
				  MIS_CNT				*	pMisCnt						=	(  MIS_CNT  *  )pMsg->taskStatus.pMisCnt;
				  //				  
				  if  (  pMisCnt->idInfo.ui64Id  ==  pMsg->taskStatus.idInfo_taskSender.ui64Id  )  {	//  ÕâÀï²»ÓÃ¾«È··ÖÎöÁË
					  idInfo_logicalReceiver.ui64Id  =  pMsg->taskStatus.idInfo_mem.ui64Id;	
					  }
				  else  if  (  pMisCnt->idInfo.ui64Id  ==  pMsg->taskStatus.idInfo_mem.ui64Id  )  idInfo_logicalReceiver.ui64Id  =  pMsg->taskStatus.idInfo_mem.ui64Id;
				  else  {
					    QM_OBJQ_MEM				mem;
						QMEM_MESSENGER_CLI	*	pQMemObj;
						//
						if  (  findQMemByKey(  0,  pMisCnt->pObjQ,  &pMsg->taskStatus.idInfo_mem,  &mem  )  )  goto  errLabel;
						pQMemObj  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
						if  (  !pQMemObj  )  goto  errLabel;
						if  (  pQMemObj->uiType  !=  CONST_objType_imGrp  )  idInfo_logicalReceiver.ui64Id  =  pMsg->taskStatus.idInfo_mem.ui64Id;
						else  idInfo_logicalReceiver.ui64Id  =  pMisCnt->idInfo.ui64Id;
					     
				  }

				  //
				  idInfo_tmpTalker.ui64Id  =  pMsg->taskStatus.idInfo_taskSender.ui64Id;
				  switch  (  pMsg->taskStatus.uiContentType  )  {
						  case  CONST_imCommType_transferFileReq:
						  case  CONST_imCommType_transferFileReplyReq:
							    switch  (  iStatus  )  {
										case  CONST_imTaskStatus_waitToRecv:
										case  CONST_imTaskStatus_recvFinished:
										case  CONST_imTaskStatus_canceledByReceiver:
											  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;
											  break;
										default:
												break;
								}
							    break;
						  case  CONST_imCommType_transferAvInfo:
						  case  CONST_imCommType_transferAvReplyInfo:
							    switch  (  iStatus  )  {
										case  CONST_imTaskStatus_waitToRecv:
										case  CONST_imTaskStatus_canceledByReceiver:
										case  CONST_imTaskStatus_deniedByReceiver:
											  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;
											  break;
										default:
												break;
								}
							    break;
						  default:
								 break;
				  }

				  //
			#ifndef  __WINCE__
				  switch  (  pMsg->taskStatus.uiContentType  )  {
						  case  CONST_imCommType_transferFileReq:
						  case  CONST_imCommType_transferFileReplyReq:
							    switch  (  iStatus  )  {
										case  CONST_imTaskStatus_applyToRecv:	
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s, %s %s, %s, %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_pleaseRecvFile  ), 
														  pMsg->taskStatus.u.transferFileStatus.fullFilePath,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_select  ),
														  bIncludeUrl  ?  getQmInternalUrl(  pMsg->taskStatus.iTaskId,  rowIdStr,  CONST_imOp_recv_accept,  0,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_accept  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_accept  ),  
														  bIncludeUrl  ?  getQmInternalUrl(  pMsg->taskStatus.iTaskId,  rowIdStr,  CONST_imOp_recvFile_saveas,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_saveAs  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_saveAs  ),
														  bIncludeUrl  ?  getQmInternalUrl(  pMsg->taskStatus.iTaskId,  rowIdStr,  CONST_imOp_recv_deny,  0,  getResStr( 0,  &pQyMc->cusRes,  CONST_resId_deny  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_deny  )  );
											  break;
										case  CONST_imTaskStatus_waitToSend:
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s, %s %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_willSendFile  ),  pMsg->taskStatus.u.transferFileStatus.fullFilePath,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canSelect  ),
														  bIncludeUrl  ?  getQmInternalUrl(  pMsg->taskStatus.iTaskId,  rowIdStr,  CONST_imOp_send_cancel,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_toInterupt  )  );												  											  						  
											  break;
										case  CONST_imTaskStatus_waitToRecv:
											  //  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s, %s %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_accepted  ),  pMsg->taskStatus.u.transferFileStatus.fileName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canSelect  ),  bIncludeUrl  ?  getQmInternalUrl(  0,  NULL,  CONST_imOp_send_cancel,  NULL,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_toInterupt  )  );
											  break;
										case  CONST_imTaskStatus_recvFinished:
											  //  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;
											  if  (  pProcInfo->getDirAndFinalName(  pMsg->taskStatus.u.transferFileStatus.fullFilePath,  tDir,  mycountof(  tDir  ),  tFile,  mycountof(  tFile  )  )  )  {
												  tDir[0]  =  0;  tFile[0]  =  0;
											  }
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s, %s %s %s %s"  ),  pMsg->taskStatus.u.transferFileStatus.fileName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_recvFinished  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_saved  ),  bIncludeUrl  ?  getQmInternalUrl(  pMsg->taskStatus.iTaskId,  rowIdStr,  CONST_imOp_openFile,  tDir,  tDir  )  :  tDir,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_zhongDe  ),  tFile  );
											  break;
										case  CONST_imTaskStatus_sendFinished:
											  if  (  pMsg->taskStatus.bImGrpMem  )  _sntprintf(  tBuf,  cnt,  _T(  "%s %s"  ),  pMsg->taskStatus.u.transferFileStatus.fullFilePath,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_recvFinished  )  );		
											  else  _sntprintf(  tBuf,  cnt,  _T(  "%s %s"  ),  pMsg->taskStatus.u.transferFileStatus.fullFilePath,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_sendFinished  )  ); 
											  break;
										case  CONST_imTaskStatus_canceledBySender:
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_faSong  ),  pMsg->taskStatus.u.transferFileStatus.fileName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canceled  )  );
											  break;
										case  CONST_imTaskStatus_canceledByReceiver:
											  //  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;				
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_jieShou  ),  pMsg->taskStatus.u.transferFileStatus.fileName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canceled  )  );
											  break;
										default:
												break;
								}								
								break;
						  case  CONST_imCommType_transferAvInfo:
						  case  CONST_imCommType_transferAvReplyInfo:
							    switch  (  iStatus  )  {
										case  CONST_imTaskStatus_req:
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s, %s %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qingqiu  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->taskStatus.uiTaskType  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canSelect  ),
																				bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_send_cancel,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  )  ):  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_toInterupt  )  );
											  break;
										case  CONST_imTaskStatus_resp:
											  _sntprintf(  tBuf,  cnt,  _T(  "%s: %s."  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qingqiu  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->taskStatus.uiTaskType  )  );
											  break;
										case  CONST_imTaskStatus_waitToRecv:
											  //  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;											  
											  _sntprintf(  tBuf,  cnt,  _T(  "%s %s, %s %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_accepted  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->taskStatus.uiTaskType  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canSelect  ),  bIncludeUrl  ?  getQmInternalUrl(  pMsg->task.iTaskId,  rowIdStr,  CONST_imOp_recv_cancel,  paramStrBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  )  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_toInterupt  )  );
											  break;		
										case  CONST_imTaskStatus_canceledBySender:
											  _sntprintf(  tBuf,  cnt,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canceled  )  );
											  break;
										case  CONST_imTaskStatus_canceledByReceiver:
  											  //  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;											
											  _sntprintf(  tBuf,  cnt,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_canceled  )  );
											  break;
										case  CONST_imTaskStatus_deniedByReceiver:
											  //  idInfo_tmpTalker.ui64Id  =  idInfo_logicalReceiver.ui64Id;
											  _sntprintf(  tBuf,  cnt,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_denied  )  );
											  break;
										default:
											    break;
								}								
							    break;
						  default:
								  break;
				  }
			#endif
				  //
				  //
				  }
				  break;
			default:
					break;
	}

	iErr  =  0;
errLabel:
	if  (  pIdInfo_talker  )  {
		pIdInfo_talker->ui64Id  =  idInfo_tmpTalker.ui64Id;
	}
	return  iErr;
 }


