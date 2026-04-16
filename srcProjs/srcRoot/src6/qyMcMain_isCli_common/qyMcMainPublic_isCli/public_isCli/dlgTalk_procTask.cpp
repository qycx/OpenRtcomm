
#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	<time.h>
#include	<stddef.h>
#include	<ShellAPI.h>

#include	"qymcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"

#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"


#include	"tmpCeLib.h"
#include	"qyWnd.h"

#include	"qyRtcCommProc.h"
#ifndef  __WINCE__
#include	"dlgVideosProc.h"
#endif
#include	<assert.h>
#include	"qmcDxSurfacePublic.h"
#ifndef  __WINCE__
#include	"qmcConferenceWall.h"
#include	"isCliHelpPublic.h"
#endif
#include	"qmcCmdProc.h"

#include	"policyAvParams.h"

#include	"dlgTalkProc.h"
#include	"qmcSharePublic.h"

#include	"DlgWalls.h"

#include	"gpsCommProc.h"
#include	"qmcGpsProc.h"

#include	"qyCusResTemp.h"

#include	"qmcVWall.h"
#include	"dlgDesktopsMonProc.h"

#include	"sp.h"
#include	"myDb.h"
#include	"isCliHelpPublic.h"

#include	"imgProcessPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"dlgMsgToolProc.h"
#include	"qmcVideoCapture_rtsp.h"
#include	"qmcDynBmp.h"

#include	"qyCusResTemp.h"
#include	"dlgShareDynBmpsProc.h"
#include	"isCliD3dPublic.h"


//
//int  dlgTalk_procTask_display_op(  HWND  hDlgTalk,  DLG_TALK_var  *  pm_var,  int  iTaskId,  unsigned  short  usOp,  MIS_MSG_TASK  *  pMsgTask,  IM_TASK_RCD  &  rcd,  int  iStatus_old,  int  iStatus,  LPCTSTR  paramStrBuf  );
int  dlgTalk_procTask_recv_accept(  HWND  hCurDlgTalk,  DLG_TALK_var  *  pCurVar,  HWND  hMgr,  DLG_TALK_var  *  pMgrVar,  int  iTaskId,  unsigned  short  usOp,  LPCTSTR  paramStrBuf,  
	 IM_TASK_RCD  &	rcd,  MIS_MSG_TASK  *	pMsgTask,  IM_CONTENTU  *	pContent,
	 int  &  iStatus,  int  &  iStatus_old,  
	 QM_dbFuncs		&	g_dbFuncs,  
	 void  *	pDb,
	 TALKER_shadow_mgr  *  pShadowMgr,
	 PARAM_dlgTalk_procTask  *  pParam  );


 int  dlgTalk_procTask_transferFileReq(  HWND  hCurDlgTalk,  DLG_TALK_var  *  pCurVar,  HWND  hMgr,  DLG_TALK_var  *  pMgrVar,  int  iTaskId,  unsigned  short  usOp,  LPCTSTR  paramStrBuf,  
	 IM_TASK_RCD  &	rcd,  MIS_MSG_TASK  *	pMsgTask,  IM_CONTENTU  *	pContent,
	 int  &  iStatus,  int  &  iStatus_old,  
	 QM_dbFuncs		&	g_dbFuncs,  
	 void  *	pDb,
	 TALKER_shadow_mgr  *  pShadowMgr  );
  int  dlgTalk_procTask_transferAvInfo(  HWND  hCurDlgTalk,  DLG_TALK_var  *  pCurVar,  HWND  hMgr,  DLG_TALK_var  *  pMgrVar,  int  iTaskId,  unsigned  short  usOp,  LPCTSTR  paramStrBuf,  
	 IM_TASK_RCD  &	rcd,  MIS_MSG_TASK  *	pMsgTask,  IM_CONTENTU  *	pContent,
	 int  &  iStatus,  int  &  iStatus_old,  
	 QM_dbFuncs		&	g_dbFuncs,  
	 void  *	pDb,
	 TALKER_shadow_mgr  *  pShadowMgr,
	 PARAM_dlgTalk_procTask  *  pParam
	 );






//  2014/11/20
//  2012/05/01
 //  
 int  dlgTalk_procTask1(  HWND  hCurDlgTalk,  int  iTaskId,  unsigned  short  usOp,  LPCTSTR  paramStrBuf,  PARAM_dlgTalk_procTask  *  pParam  )
{
	int								iErr								=	-1;
	//

	//
	if  (  !hCurDlgTalk  )  return  -1;
	CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
	DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  hCurDlgTalk  );
	if  (  !pCurVar  )  return  -1;

	QY_MC* pQyMc = pCurVar->pQyMc;// QY_GET_GBUF();
	//
	QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  return  -1;
	QM_dbFuncs& g_dbFuncs = *pDbFuncs;

	HWND  hDlgTalk  =  hCurDlgTalk;
	if  (  !isTalkerShadowMgr(  pCurVar->addr  )  )  {
		TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pCurVar->pShadowInfo;
		if  (  !pShadow  )  return  -1;
		hDlgTalk  =  pShadow->hMgr;
	}
	if  (  !hDlgTalk  )  return  -1;

	//
	CHelp_getDlgTalkVar					help_getDlgTalkVar;
	DLG_TALK_var					*	pm_var							=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pm_var  )  return  -1;
	DLG_TALK_var				&	m_var								=	*pm_var;
	MC_VAR_isCli					*	pProcInfo							=	QY_GET_procInfo_isCli(  );  //(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	//
	int								lenInBytes							=	0;
	//
	void						*	pDb									=	NULL;
	int								iDbType								=	pQyMc->cfg.db.iDbType;
	CQyMalloc						mallocObj_pRcd;
	IM_TASK_RCD					*	pRcd								=	(  IM_TASK_RCD  *  )mallocObj_pRcd.mallocf(  sizeof(  IM_TASK_RCD  )  );
	if  (  !pRcd  )  return  -1;
	IM_TASK_RCD					&	rcd									=	*pRcd;
	MIS_MSG_TASK				*	pMsgTask							=	NULL;
	IM_CONTENTU					*	pContent							=	NULL;	
	//
	TCHAR						*	pT;
	//
	TCHAR							tBuf[256];
#ifndef  __WINCE__
	int								nItem;
	TCHAR							sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	//  DWORD							dwProcessId;
#endif
	int								iStatus								=	0;
	int								iStatus_old							=	0;
	
	int								i;

	//
	if  (  !iTaskId  )  return  -1;

	//  2012/05/01
	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;
	

#ifndef  __NOTSUPPORT_DB__
		CQnmDb							db;

		if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
		pDb  =  db.m_pDbMem->pDb;
#endif

	//
#if  10
	if  (  !(  pMsgTask  =  findTaskInProcessQ(  &m_var,  iTaskId  )  )  )  {
		#ifdef  __DEBUG__
				traceLogA(  (char*)  "procQmInternalUrl failed: send again, findTaskInProcessQ failed"  );	
		#endif
		goto  errLabel;
	}
#endif 
#if  0
	int  index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, iTaskId);
	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
	if (pTaskInfo == NULL)  goto  errLabel;
	QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;
	if (!pTaskData == NULL)  goto  errLabel;
	pMsgTask = &pTaskData->msgU.task;
#endif 



	//
	msg2TaskRcd(  m_var.pMisCnt,  pMsgTask,  0,  &rcd  );
	pContent  =  (  IM_CONTENTU  *  )pMsgTask->data.buf;

#ifdef  __SUPPORT_HTMLEDIT__
	if  (  usOp  ==  CONST_imOp_openFile  )  {
		if  (  (  pT  =  _tcsrchr(  rcd.content,  _T(  '\\'  )  )  )  )  {
			*pT  =  0;
			if  (  bDir(  rcd.content  )  )  {		//  ÊÇÄ¿Â¼²Å´ò¿ª£¬·ñÔò£¬²»´ò¿ª¡£·ÀÖ¹ÊÇ¿ÉÖ´ÐÐÎÄ¼þ
				ShellExecute(  NULL,  _T(  "open"  ),  rcd.content,  _T(  ""  ),  NULL,  SW_SHOW  );
			}
		}
		iErr  =  0;  goto  errLabel;
	}
#endif

		
	switch  (  usOp  )  {
				case  CONST_imOp_send_permit:  {					  //  

					  if  (  rcd.uiContentType  ==  CONST_imCommType_transferAvInfo  )  {
						  
						  #ifdef  __DEBUG__
								  traceLogA(  (char*)  "procQmInternalUrl: send transferAvInfo again."  );
						  #endif
						  
						  if  (  pProcInfo->processQ_media.qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsgTask,  0  )  <=  0  )  {	
							  goto  errLabel;
						  }									
					  }

					  iStatus  =  CONST_imTaskStatus_req;

					  //
					  /*
					  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
						   if  (  pShadowMgr->shadows[i].hShadow  &&  isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  {
							   CHelp_getDlgTalkVar	help_getDlgTalkVar;
							   dlgTalk_procTask_display_op(  pShadowMgr->shadows[i].hShadow,  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  pShadowMgr->shadows[i].hShadow  ),  iTaskId,  usOp,  pMsgTask,  rcd,  iStatus_old,  iStatus,  paramStrBuf  );
						   }
					  }
					  //					  
					  dlgTalk_procTask_display_op(  hDlgTalk,  &m_var,  iTaskId,  usOp,  pMsgTask,  rcd,  iStatus_old,  iStatus,  paramStrBuf  );
					  */
					  dlgTalk_procTask_display_op_mgr(  hDlgTalk,  iTaskId,  usOp,  pMsgTask,  rcd,  iStatus_old,  iStatus,  paramStrBuf  );
					  
					  
					  //					  
					  lenInBytes  =  pMsgTask->lenInBytes  -  offsetof(  MIS_MSG_routeTalkData,  buf  );
					  if  (  lenInBytes  <  0  )  goto  errLabel;
					  //
					  //  2015/09/07
					  unsigned  int  uiChannelType  =  pMsgTask->uiChannelType;
					  //  2015/09/07
					  uiChannelType  =  0;
					  //
					  if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  pMsgTask->usCode,  pMsgTask->tStartTime,  pMsgTask->uiTranNo,  0,  pMsgTask->iTaskId,  pMsgTask->uiTaskType,  (  char  *  )pMsgTask->data.buf,  lenInBytes,  &m_var.addr.idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &rcd.idInfo_recv,  uiChannelType,  NULL,  FALSE  )  )  goto  errLabel;
				  					  
					  }
					  break;
				case  CONST_imOp_recv_accept:
				case  CONST_imOp_recvFile_saveas:  
				case  CONST_imOp_dual_permit:  

					  if  (  dlgTalk_procTask_recv_accept(  hCurDlgTalk,  pCurVar,  hDlgTalk,  pm_var,  iTaskId,  usOp,  paramStrBuf,  rcd,  pMsgTask,  pContent,  iStatus,  iStatus_old,  g_dbFuncs,  pDb,  pShadowMgr,  pParam  )  )  goto  errLabel;
 
					  break;
				case  CONST_imOp_recv_deny:
				case  CONST_imOp_recv_cancel:	{
					  //
					  #ifdef  __DEBUG__
							  showInfo_open0(  0,  _T(  "dlgTalk_procTask1"  ),  _T(  "recv_cancel"  )  );
					  #endif
					  //
					  if  (  usOp  ==  CONST_imOp_recv_deny  )  iStatus  =  CONST_imTaskStatus_deniedByReceiver;
					  else  iStatus  =  CONST_imTaskStatus_canceledByReceiver;
					  iStatus_old  =  pMsgTask->iStatus;
					  //
					  if  (  g_dbFuncs.pf_updateTaskStatus(  pDb,  iStatus,  rcd.id  )  )  goto  errLabel;
					  pMsgTask->iStatus  =  iStatus;	//  2009/10/17
					  mytime(  &pMsgTask->tLastModifiedTime  );	//  2014/05/01
					  
					  //
					  /*
					  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
						   if  (  pShadowMgr->shadows[i].hShadow  &&  isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  {
							   CHelp_getDlgTalkVar	help_getDlgTalkVar;

							   dlgTalk_procTask_display_op(  pShadowMgr->shadows[i].hShadow,  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  pShadowMgr->shadows[i].hShadow  ),  iTaskId,  usOp,  pMsgTask,  rcd,  iStatus_old,  iStatus,  paramStrBuf  );
						   }
					  }
					  //
					  dlgTalk_procTask_display_op(  hDlgTalk,  &m_var,  iTaskId,  usOp,  pMsgTask,  rcd,  iStatus_old,  iStatus,  paramStrBuf  );
						*/
					  dlgTalk_procTask_display_op_mgr(  hDlgTalk,  iTaskId,  usOp,  pMsgTask,  rcd,  iStatus_old,  iStatus,  paramStrBuf  );
						

					  //
					  //  if  (  rcd.uiContentType  ==  CONST_imCommType_transferAvInfo  )  {
					  //	  freeCapImageByTaskId(  pDlg,  0,  rcd.id,  &pDlg->m_var.av.peerImages  );
					  //  }					  

					  //  
					  TASK_PROC_REQ		taskProcReq;
					  QY_MESSENGER_ID  idInfo_dst;

					  memset(  &taskProcReq,  0,  sizeof(  taskProcReq  )  );
					  taskProcReq.uiType  =  CONST_imCommType_taskProcReq;
					  taskProcReq.usOp  =  usOp;
					  taskProcReq.tStartTime_org  =  rcd.tSendTime;
					  taskProcReq.uiTranNo_org  =  rcd.uiTranNo;
					  taskProcReq.uiSerialNo_org  =  rcd.uiSerialNo;
					  taskProcReq.uiContentType_org  =  rcd.uiContentType;
					  
					  //  2014/11/22
					  idInfo_dst.ui64Id  =  rcd.idInfo_send.ui64Id;
					  //					  	
					  lenInBytes  =  sizeof(  taskProcReq  );			
					  //					
					  MACRO_prepareForTran(  );						
					  //
					  if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  pMsgTask->usCode,  tStartTran,  uiTranNo,  0,  iTaskId,  rcd.uiMode,  (  char  *  )&taskProcReq,  lenInBytes,  &m_var.addr.idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &idInfo_dst,  pMsgTask->uiChannelType,  NULL,  FALSE  )  )  goto  errLabel;
					  
					  //
					  if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
						  TRANSFER_AV_INFO  *  pTransferAvInfo  =  &pContent->transferAvInfo;
						  //
#if  0
						  PROC_TASK_AV  *  pTask  =  get_transferAvInfo_pTask(  pTransferAvInfo,  _T(  ""  )  );
						  if  (  !pTask  )  goto  errLabel;
						  //
						  if  (  pTask->dlgTalkInProxy.bExists  )  {
							  memset(  &taskProcReq,  0,  sizeof(  taskProcReq  )  );
							  taskProcReq.uiType  =  CONST_imCommType_taskProcReq;
							  taskProcReq.usOp  =  usOp;

							  taskProcReq.tStartTime_org  =  pTask->dlgTalkInProxy.proxy.tStartTran;
							  taskProcReq.uiTranNo_org  =  pTask->dlgTalkInProxy.proxy.uiTranNo;
							  taskProcReq.uiSerialNo_org  =  0;
							  taskProcReq.uiContentType_org  =  pContent->uiType;
							  //
							  idInfo_dst.ui64Id  =  m_var.addr.idInfo.ui64Id;
							  //
							  lenInBytes  =  sizeof(  taskProcReq  );			
							  //					
							  MACRO_prepareForTran(  );											  
							  //
							  if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  pMsgTask->usCode,  tStartTran,  uiTranNo,  0,  iTaskId,  rcd.uiMode,  (  char  *  )&taskProcReq,  lenInBytes,  &m_var.addr.idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &idInfo_dst,  pMsgTask->uiChannelType,  NULL,  FALSE  )  )  goto  errLabel;

						  }
#endif
					  }

					  //  
					  dlgTalk_freeCapImageBySth_mgr(  hDlgTalk,  rcd.id,  NULL  );
					  
					  //  2009/02/20
					  if  (  m_var.av.taskInfo.bTaskExists  
						  &&  m_var.av.taskInfo.iTaskId  ==  rcd.id  )  
					  {
							  dlgTalk_closeTaskAv(  hDlgTalk,  m_var  );
							  //
							  clearSpeakState(_T("dlgTalk_procTask1.339"));
							  //
							  if  (  1  )
							  {
								  int  ii = 0;
								  int  tmp_taskIndex = getQmcTaskInfoIndexBySth(pProcInfo, rcd.id);
								  QMC_TASK_INFO* tmp_pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, tmp_taskIndex);
								  if (tmp_pTaskInfo  ) {
									  QMC_taskData_common* pTaskData = (QMC_taskData_common*)tmp_pTaskInfo->var.pTaskData;
									  if (pTaskData) {
										  MIS_MSG_TASK* tmp_pMsgTask = &pTaskData->msgU.task;
										  if (tmp_pMsgTask->uiType == CONST_misMsgType_task) {
											  tmp_pMsgTask->iStatus = iStatus;
										  }
									  }
								  }

							  }
					  }
					  else  {
						  dlgTalk_closeTask(hDlgTalk, rcd.id);
					  }


					  //  2013/11/18
					  if  (  pShadowMgr->remoteAssist.iTaskId  ==  rcd.id  )  {
						  SendMessage(  pShadowMgr->remoteAssist.hWnd_remoteAssist,  WM_CLOSE,  0,  0  );
						  pShadowMgr->remoteAssist.hWnd_remoteAssist  =  NULL;
						  pShadowMgr->remoteAssist.iTaskId  =  0;
					  }

					  //  2010/12/23
					  chkResources(  hDlgTalk,  TRUE  );

					  //  2012/03/24
					  qmcApplyForChkingTasks_gui(  pQyMc  );
					  //
					  }
					  //
					  break;
				case  CONST_imOp_send_cancel:  {
					  //
					  #ifdef  __DEBUG__
							  showInfo_open0(  0,  _T(  "dlgTalk_procTask1"  ),  _T(  "send_cancel"  )  );
					  #endif
					  //
					  iStatus  =  CONST_imTaskStatus_canceledBySender;
					  iStatus_old  =  pMsgTask->iStatus;
					  //
					  if  (  g_dbFuncs.pf_updateTaskStatus(  pDb,  iStatus,  rcd.id  )  )  goto  errLabel;	
					  pMsgTask->iStatus  =  iStatus;	//  2009/10/17
					  mytime(  &pMsgTask->tLastModifiedTime  );	//  2014/05/01
					  
					  //
					  /*
					  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
						   if  (  pShadowMgr->shadows[i].hShadow  &&  isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  {
							   CHelp_getDlgTalkVar	help_getDlgTalkVar;

							   dlgTalk_procTask_display_op(  pShadowMgr->shadows[i].hShadow,  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  pShadowMgr->shadows[i].hShadow  ),  iTaskId,  usOp,  pMsgTask,  rcd,  iStatus_old,  iStatus,  paramStrBuf  );
						   }
					  }
					  dlgTalk_procTask_display_op(  hDlgTalk,  &m_var,  iTaskId,  usOp,  pMsgTask,  rcd,  iStatus_old,  iStatus,  paramStrBuf  );
					  */
					  dlgTalk_procTask_display_op_mgr(  hDlgTalk,  iTaskId,  usOp,  pMsgTask,  rcd,  iStatus_old,  iStatus,  paramStrBuf  );
					  

					  //  
					  TASK_PROC_REQ		taskProcReq;
					  memset(  &taskProcReq,  0,  sizeof(  taskProcReq  )  );
					  taskProcReq.uiType  =  CONST_imCommType_taskProcReq;
					  taskProcReq.usOp  =  usOp;
					  taskProcReq.tStartTime_org  =  rcd.tSendTime;
					  taskProcReq.uiTranNo_org  =  rcd.uiTranNo;
					  taskProcReq.uiSerialNo_org  =  rcd.uiSerialNo;
					  taskProcReq.uiContentType_org  =  rcd.uiContentType;
					  //
					  lenInBytes  =  sizeof(  taskProcReq  ); 
					  //					  
					  MACRO_prepareForTran(  );						

					  //  2015/09/07
					  unsigned  int  uiChannelType  =  pMsgTask->uiChannelType;
					  //  2015/09/07
					  uiChannelType  =  0;
					  //
					  if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  pMsgTask->usCode,  tStartTran,  uiTranNo,  0,  iTaskId,  rcd.uiMode,  (  char  *  )&taskProcReq,  lenInBytes,  &m_var.addr.idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &rcd.idInfo_recv,  uiChannelType,  NULL,  FALSE  )  )  {
						  goto  errLabel;
					  }
					  
					  //  
					  //  freeCapImageByTaskId(  hDlgTalk,  0,  rcd.id,  &m_var.av.peerImages  );
					  dlgTalk_freeCapImageBySth_mgr(  hDlgTalk,  rcd.id,  NULL  );
					  int  idc  =  m_var.av.idc_me;	//  0
					  dlgTalk_freeCapImageByTaskId_me_mgr(  hDlgTalk,  idc,  rcd.id  );

					  
					  //  2009/02/20
					  if  (  m_var.av.taskInfo.bTaskExists  
						  &&  m_var.av.taskInfo.iTaskId  ==  iTaskId  )  
					  {
							  dlgTalk_closeTaskAv(  hDlgTalk,  m_var  );						  
							  //  2014/10/09
							  dlgTalk_freeCapImages_bgWall_mgr(  hDlgTalk,  m_var.av.idc_bgWall_conf  );
						  }
					  else  {
						    dlgTalk_closeTask(  hDlgTalk,  iTaskId  );
					  }

					  //  2011/10/10
					  chkResources(  hDlgTalk,  TRUE  );

					  //  2012/03/24
					  qmcApplyForChkingTasks_gui(  pQyMc  );

					  //
					  }
					  //
					  break;
				default:
					   #ifdef  __DEBUG__
							   traceLogA(  (char*)  "procQmInternalUrl: unprocessed op {%d}", usOp  );
					   #endif
					   goto  errLabel;
	
	
	}
	
	

	iErr  =  0;
errLabel:

	dlgTalk_displayAvStatus(  hDlgTalk,  m_var,  0,  0,  0  );									

	if  (  iErr  )  {
#if  0
		if  (  ucbGot_iIndex_sharedObj_localAv  )  {
			//  
			//freeSharedObjUsr_localAv(  m_var.av.iIndex_sharedObj_localAv,  hDlgTalk  );
			//m_var.av.ucbGot_iIndex_sharedObj_localAv  =  FALSE;
			dlgTalk_closeTaskAv(  hDlgTalk,  m_var  );
		}
#endif
	}

	//
	dyn_d3dWall_refreshWallMemByTalker(  hDlgTalk  );

	//  201
	refreshTalkToInfo_mgr(  hDlgTalk  );

	return  iErr;

}




 int  dlgTalk_procTask_recv_accept(  HWND  hCurDlgTalk,  DLG_TALK_var  *  pCurVar,  HWND  hMgr,  DLG_TALK_var  *  pMgrVar,  int  iTaskId,  unsigned  short  usOp,  LPCTSTR  paramStrBuf,  
	 IM_TASK_RCD  &	rcd,  MIS_MSG_TASK  *	pMsgTask,  IM_CONTENTU  *	pContent,
	 int  &  iStatus,  int  &  iStatus_old,  
	 QM_dbFuncs		&	g_dbFuncs,  
	 void  *	pDb,
	 TALKER_shadow_mgr  *  pShadowMgr,
	 PARAM_dlgTalk_procTask  *  pParam  
	 )
 {
	 int  iErr  =  -1;

	 HWND  hDlgTalk  =  hMgr;
	 DLG_TALK_var  &  m_var  =  *pMgrVar;

	 //
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 QY_MC* pQyMc = m_var.pQyMc;// QY_GET_GBUF();
	 int  i;
	 int  lenInBytes;

	 switch  (  rcd.uiContentType  )  {
			 case  CONST_imCommType_transferFileReq:
				   return  dlgTalk_procTask_transferFileReq(  hCurDlgTalk,  pCurVar,  hMgr,  pMgrVar,  iTaskId,  usOp,  paramStrBuf,  rcd,  pMsgTask,  pContent,  iStatus,  iStatus_old,  g_dbFuncs,  pDb,  pShadowMgr  );
			 case  CONST_imCommType_transferAvInfo:
				   return  dlgTalk_procTask_transferAvInfo(  hCurDlgTalk,  pCurVar,  hMgr,  pMgrVar,  iTaskId,  usOp,  paramStrBuf,  rcd,  pMsgTask,  pContent,  iStatus,  iStatus_old,  g_dbFuncs,  pDb,  pShadowMgr,  pParam  );
				   break;
			 default:
					break;
	 }
	 

					  

	 iErr  =  0;
errLabel:
	 return  iErr;

 }


