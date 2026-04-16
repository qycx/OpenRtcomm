



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

//int  dlgTalk_procTask_display_op(  HWND  hDlgTalk,  DLG_TALK_var  *  pm_var,  int  iTaskId,  unsigned  short  usOp,  MIS_MSG_TASK  *  pMsgTask,  IM_TASK_RCD  &  rcd,  int  iStatus_old,  int  iStatus,  LPCTSTR  paramStrBuf  );

//
int  getResServDir(  QY_MC  *  pQyMc,  TCHAR  *  resServDir,  int  cntofDir  )
{
	 TCHAR  *  pRegVal;
	 HKEY  hKeyRoot  =  HKEY_LOCAL_MACHINE;
	 TCHAR  *  rootKey_qnmScheduler  =  (TCHAR*)_T(  CONST_qyRootKey_qnmScheduler_mis  );
	 TCHAR  tBuf[MAX_PATH]  =  _T(  ""  );
	
	 //CCtxQyMc  *  pQyMc  =  QY_GET_GBUF(  );
	 CCtxQmc  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 //pProcInfo->cfg.policy.dirToSaveFile


	 if  (  pQyMc->appParams.bService  )  {
		 pRegVal  =  (TCHAR*)_T(  CONST_regValName_offlineResServDir  );											//  2015/08/07	 
		 if  (  qyGetRegCfgT(  hKeyRoot,  (  rootKey_qnmScheduler  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
		 }
	 else  {
		   safeTcsnCpy(  pProcInfo->cfg.policy.dirToSaveFile,  tBuf,  mycountof(  tBuf  )  );
	 }
	 //
	 tTrim(  tBuf  );
	 if  (  !tBuf[0]  )  {
		 return  -1;
	 }

	 //
	 safeTcsnCpy(  tBuf,  resServDir,  cntofDir  );

	 if  (  tTrailDir(  resServDir,  cntofDir  )  )  return  -1;

	 return  0;

}

//
int getPath_fileServer(  QY_MC  *  pQyMc,  QY_MESSENGER_ID  *  pIdInfo_send,  QY_MESSENGER_ID  *  pIdInfo_recv,  TCHAR  *	pFilePath,  int  len  )
{
	int					iErr			=  -1;
	//
	MC_VAR_isCli	*	pProcInfo		=  QY_GET_procInfo_isCli(  );
	//QY_MC			*	pQyMc			=  QY_GET_GBUF(  );
	TCHAR				tBuf[128]		=  _T(  ""  );

	TCHAR  resServDir[MAX_PATH]  =  _T(  ""  );
	if  (  getResServDir(  pQyMc,  resServDir,  mycountof(  resServDir  )  )  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "getResServDir failed. resServDir isnot set correctly"  )  );
		showInfo_open0(  0,  0,  tBuf  );
		showNotification_open(  0,  0,  0,  tBuf  );
		goto  errLabel;;
	}
	//  pProcInfo->cfg.policy.dirToSaveFile
#ifdef  __DEBUG__
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "resServDir: %s"  ),  resServDir  );
	showInfo_open0( 0, 0, tBuf  );
#endif
	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%S"  ),  resServDir,  CONST_subDir_fileServer  );
	if  (  !bDir(  tBuf  )  )
	{
		BOOL  bRet  =  CreateDirectory(  tBuf,  NULL  );
		if  (  !bRet  &&  GetLastError(  )  !=  ERROR_ALREADY_EXISTS  )  {
			//qyDisplayLastError(  "Creating msgDir"  );  
			goto  errLabel;		   
		}							  
	}
		
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%I64u"  ),  tBuf,  pIdInfo_recv->ui64Id  );
	if  (  !bDir(  tBuf  )  )
	{
		BOOL  bRet  =  CreateDirectory(  tBuf,  NULL  );
		if  (  !bRet  &&  GetLastError(  )  !=  ERROR_ALREADY_EXISTS  )  {
			//qyDisplayLastError(  "Creating msgDir"  );  
			goto  errLabel;		   
		}
	}

	_sntprintf(  pFilePath,  len,  _T(  "%s"  ),  tBuf  );

	iErr  =  0;
errLabel:
	//
	if  (  iErr  )  {
		showInfo_open0(  0,  0,  _T(  "getPath_fileServer failed"  )  );
		showNotification_open(  0,  0,  0,  _T(  "getPath_fileServer failed"  )  );
	}

	return  iErr;
}




//
int  getFilePrefix_fileServer(  time_t  t,  char  *  filePrefix,  unsigned  int  cnt  )
{
	if  (  cnt  <  CONST_qyTimeLen  )  return  -1;

	//time_t  t;
	//time(  &t  );
	//
#ifdef  __DEBUG__

#if  0
		char  timeBuf[CONST_qyTimeLen  +  1]  =  "";
		getTimeStr(  t,  timeBuf,  mycountof(  timeBuf  )  );
#endif

#endif
	//
	struct  tm  *  p  =  mygmtime(  &t  );
	int  iY  =  9999  -  (  p->tm_year  +  1900  );
	int  iM  =  99  -  (  p->tm_mon  +  1 );
	int  iD  =  99  -  p->tm_mday;
	int  iH  =  99  -  p->tm_hour;
	int  iMin  =  99  -  p->tm_min;
	int  iS  =  99  -  p->tm_sec;
	//
	_snprintf(  filePrefix,  cnt,  "%04d%02d%02d%02d%02d%02d",  iY,  iM,  iD,  iH,  iMin,  iS  );
	if  (  cnt  >  CONST_qyTimeLen  )  filePrefix[CONST_qyTimeLen]  =  0;


	//
#ifdef  __DEBUG__

#if  0
	int  filePrefix2tTime(  char  *  filePrefix,  time_t  *  pt  );
	//
	time_t  tt;
	filePrefix2tTime(  filePrefix,  &tt  );
	getTimeStr(  tt,  timeBuf,  mycountof(  timeBuf  )  );
#endif
	
#endif

	return  0;

}

//
int  filePrefix2tTime(  char  *  filePrefix,  time_t  *  pt  )
{
	if  (  strlen(  filePrefix  )  <  CONST_qyTimeLen  )  return  -1;
	//
	char  buf[32];
	char  *  p  =  filePrefix;
	int  len  =  4;
	memcpy(  buf,  p,  len  );  p  +=  len;  buf[len]  =  0;
	int  iVal  =  atol(  buf  );
	int  iY  =  9999  -  iVal;
	//
	len  =  2;
	memcpy(  buf,  p,  len  );  p  +=  len;  buf[len]  =  0;
	iVal  =  atol(  buf  );
	int  iM  =  99  -  iVal;
	//
	len  =  2;
	memcpy(  buf,  p,  len  );  p  +=  len;  buf[len]  =  0;
	iVal  =  atol(  buf  );
	int  iD  =  99  -  iVal;
	//
	len  =  2;
	memcpy(  buf,  p,  len  );  p  +=  len;  buf[len]  =  0;
	iVal  =  atol(  buf  );
	int  iH  =  99  -  iVal;
	//
	len  =  2;
	memcpy(  buf,  p,  len  );  p  +=  len;  buf[len]  =  0;
	iVal  =  atol(  buf  );
	int  iMin  =  99  -  iVal;
	//
	len  =  2;
	memcpy(  buf,  p,  len  );  p  +=  len;  buf[len]  =  0;
	iVal  =  atol(  buf  );
	int  iS  =  99  -  iVal;

	//
	_snprintf(  buf,  mycountof(  buf  ),  "%04d%02d%02d%02d%02d%02d",  iY,  iM,  iD,  iH,  iMin,  iS  );
	//
	*pt  =  gettTimeByStr(  buf  );

	return  0;
}


//  2014/11/20
 int  dlgTalk_procTask_transferFileReq(  HWND  hCurDlgTalk,  DLG_TALK_var  *  pCurVar,  HWND  hMgr,  DLG_TALK_var  *  pMgrVar,  int  iTaskId,  unsigned  short  usOp,  LPCTSTR  paramStrBuf,  
	 IM_TASK_RCD  &	rcd,  MIS_MSG_TASK  *	pMsgTask,  IM_CONTENTU  *	pContent,
	 int  &  iStatus,  int  &  iStatus_old,  
	 QM_dbFuncs		&	g_dbFuncs,  
	 void  *	pDb,
	 TALKER_shadow_mgr  *  pShadowMgr  )
 {
	 int  iErr  =  -1;

	 HWND  hDlgTalk  =  hMgr;
	 DLG_TALK_var  &  m_var  =  *pMgrVar;

	 //
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 QY_MC* pQyMc = m_var.pQyMc;// QY_GET_GBUF();
	 int  i;
	 int  lenInBytes;

	 //
	 if  (  !pMsgTask)  {
		 return -1;
	 }

	 //
	 if  (  rcd.uiContentType  !=   CONST_imCommType_transferFileReq  )  return  -1;

	 	 //	
	 int iIndex_taskInfo = -1;
		
	 iIndex_taskInfo=getQmcTaskInfoIndexBySth(pProcInfo,iTaskId);	
	 if  (  iIndex_taskInfo  <  0  ) {
				iIndex_taskInfo = newTaskInfoIndex(pProcInfo, CONST_taskDataType_transferFile,hMgr, iTaskId,  _T(  "dlgTalk_procTask_transferFileReq"  )  );
				if (iIndex_taskInfo < 0)
				{
					traceLogA(  (char*)"dlgTalk_procTask_transferAvInfo failed, index_taskInfo <0");
					goto errLabel;
				}
				QMC_TASK_INFO *pTaskInfo=(QMC_TASK_INFO *)getQmcTaskInfoByIndex(pProcInfo,iIndex_taskInfo);
				int tmpLen=pMsgTask->lenInBytes + offsetof(  MIS_MSG_TASK, data );
				memcpy( &pTaskInfo->var.pTaskData->msgU.task, pMsgTask, tmpLen );
			
	 }
	 //	
	 QMC_TASK_INFO* pTaskInfo; pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, iIndex_taskInfo);
	 pMsgTask=&pTaskInfo->var.pTaskData->msgU.task;
	 if(pMsgTask->uiType!=CONST_misMsgType_task) {	
		 goto errLabel;			
	 }
	 if  (  pMsgTask->iTaskId!=iTaskId ) {
		 return -1;
	 }




	 //
	 switch  (  usOp  )  {
				case  CONST_imOp_recv_accept:
				case  CONST_imOp_recvFile_saveas:  
				case  CONST_imOp_dual_permit:  { 
	 
					  //  
					  unsigned  char			ucbSendLocalAv					=	FALSE;
					  int						iIndex_sharedObj				=	-1;
					  int						iIndex_sharedObjUsr				=	-1;
					  QY_SHARED_OBJ			*	pSharedObj						=	NULL;
					  int						iIndex_capBmp					=	-1;	
					  CAP_procInfo_video	*	pCapBmp							=	NULL;
					  int						iIndex_capAudio					=	-1;
					  CAP_procInfo_audioCommon	*	pCapAudio						=	NULL;
					  int						iIndex_shmCmd					=	-1;
					  QM_SHM_CMD			*	pShmCmd							=	NULL;
					  BOOL						bFirstUsr						=	FALSE;
					  SHARED_OBJ_USR		*	pSharedObjUsr					=	NULL;
					  TALKER_policy				talkerPolicy;

					  //  2011/08/08
					  AV_COMPRESSOR_CFG		avCompressor_reply;		//  响应要取得compressor, 目前只有av才有需要. 2012/02/16
					  //  if  (  myGetAvCompressorCfg(  CONST_capType_av,  0,  CONST_capUsage_conf,  0,  &avCompressor_reply  )  )  goto  errLabel;
					  if  (  myGetAvCompressorCfg(  CONST_capType_av,  0,  0,  0,  &avCompressor_reply  )  )  goto  errLabel;	//  2014/08/15

					  getTalkerPolicy(  &m_var.addr.idInfo,  &talkerPolicy  );
					  //m_var.m_layout.ucbNeverJoinInBgWall  =  talkerPolicy.ucbNeverJoinInBgWall;
					  //m_var.m_layout.usPollingIntervalInS1  =  pShadowMgr->bgWall.bgWallCfg.usPollingIntervalInS;
					  m_var.m_layout.bgWallLayoutCfg.usRows_bg  =  pShadowMgr->bgWall.bgWallCfg.bgWallLayoutCfg.usRows_bg;
					  m_var.m_layout.bgWallLayoutCfg.usCols_bg  =  pShadowMgr->bgWall.bgWallCfg.bgWallLayoutCfg.usCols_bg;
					  //
					  if  (  rcd.uiContentType  ==  CONST_imCommType_transferFileReq  )  {  		
						  CQyString			pathCStr;				
						  TCHAR				tFileBuf[256]  = _T(  ""  );
						  //
						  if  (  bSupported_fileServer(  pQyMc  )  )  {
							  QY_MESSENGER_ID  idInfo_peer;
							  if  (  pContent->transferFileReq.idInfo_logicalPeer.ui64Id  )  idInfo_peer.ui64Id  =  pContent->transferFileReq.idInfo_logicalPeer.ui64Id;
							  else  idInfo_peer.ui64Id  =  rcd.idInfo_recv.ui64Id;
							  //
							  QY_MESSENGER_ID  idInfo_sender;
							  idInfo_sender.ui64Id  =  rcd.idInfo_send.ui64Id;
							  //
							  //  if  (  getFilePath_fileServer(  &rcd.idInfo_send,  &idInfo_peer,  rcd.subject,  tFileBuf, mycountof(  tFileBuf  )  )  )  goto  errLabel;
							  TCHAR  tPath[MAX_PATH]  =  _T(  ""  );
							  if  (  getPath_fileServer(  pQyMc,  &rcd.idInfo_send,  &idInfo_peer,  tPath,  mycountof(  tPath  )  )  )  goto  errLabel;
							  if  (  tTrailDir(  tPath,  mycountof(  tPath  )  )  )  goto  errLabel;
							  //
							  TCHAR  tFile_part[256]  =  _T(  ""  );
							  TCHAR  tFile_postfix[24]  =  _T(  ""  );
							  safeTcsnCpy(  rcd.subject,  tFile_part,  mycountof(  tFile_part  )  );
							  TCHAR  *  pT  =  _tcsrchr(  tFile_part,  _T(  '.'  )  );
							  if  (  pT  )  {
								  *pT  =  0;  pT  ++  ;
								  safeTcsnCpy(  pT,  tFile_postfix,  mycountof(  tFile_postfix  )  );
								  tTrim(  tFile_postfix  );
							  }
							  //
							  time_t  t;  time(  &t  );
							  char  filePrefix[CONST_qyTimeLen  +  1]  =  "";
							  if  (  getFilePrefix_fileServer(  t,  filePrefix,  mycountof(  filePrefix  )  )  )  goto  errLabel;
							  //
							  int  iii;
							  int  max_iii  =  255;
							  for  (  iii  =  0;  iii  <  max_iii;  iii  ++  )  {
								   _sntprintf(  tFileBuf,  mycountof(  tFileBuf  ),  _T(  "%s%S_qm%I64u_%s"  ),  tPath,  filePrefix,  idInfo_sender.ui64Id,  tFile_part  );

								   if  (  iii  )  {
									     _sntprintf(  tFileBuf,  mycountof(  tFileBuf  ),  _T(  "%s_%d"  ),  tFileBuf,  iii  );									   
								   }
								   if  (  tFile_postfix[0]  )  _sntprintf(  tFileBuf,  mycountof(  tFileBuf  ),  _T(  "%s.%s"  ),  tFileBuf,  tFile_postfix  );
								   //
								   DWORD           dwAttrs;
								   dwAttrs  =  GetFileAttributes(  tFileBuf  );
								   if  (  dwAttrs  !=  INVALID_FILE_ATTRIBUTES  )  continue;
								   //
								   TCHAR  tmpBuf[MAX_PATH]  =  _T(  ""  );
								   _sntprintf(  tmpBuf,  mycountof(  tmpBuf  ),  _T(  "%s.tmp"  ),  tFileBuf  );
								   dwAttrs  =  GetFileAttributes(  tFileBuf  );
								   if  (  dwAttrs  !=  INVALID_FILE_ATTRIBUTES  )  continue;
								   //
								   break;								   
							  }
							  if  (  iii  ==  max_iii  )  {
								  showInfo_open0(  0,  0,  _T(  "dlgTalk_procTask_transferFileReq failed, no valid iii can be used"  )  );
								  goto  errLabel;
							  }
							  //
							  pathCStr  =  CQyString(  tFileBuf  );
						  }
						  else  
						  {
							  pathCStr  =  CQyString(  pProcInfo->cfg.policy.dirToSaveFile  )  +  CQyString(  rcd.subject  );					  
						  }
						  if  (  usOp  ==  CONST_imOp_recvFile_saveas  )  {
							  //
							  if  (  qyBrowseForFile(  hDlgTalk,  FALSE,  _T(  "*"  ),  0,  _T(  "File format(*.*)\0*.*\0\0"  ),  NULL,  rcd.subject,  pQyMc,  pathCStr  )  )  {
								  goto  errLabel;
								  //break;
							  }

							  usOp  =  CONST_imOp_recv_accept;		//  saveAs, CONST_imOp_recvFile_accept
						  }
						  safeTcsnCpy(  pathCStr.GetBuffer(  0  ),  pContent->transferFileReq.fullFilePath,  mycountof(  pContent->transferFileReq.fullFilePath  )  );  
						  lstrcpyn(  rcd.content,  pathCStr.GetBuffer(  0  ),  mycountof(  rcd.content  )  );
						  }
					  else  if  (  rcd.uiContentType  ==  CONST_imCommType_transferAvInfo  )  {
								//
							    }
					  else  if  (  rcd.uiContentType  ==  CONST_imCommType_queryCustomerServiceOfficerReq  )  {
							    ;
								}
					  else  {
							#ifdef  __DEBUG__
									traceLog((TCHAR*)  _T(  "dlgTalk_procTask failed: unprocessed contentType, %d"  ),  rcd.uiContentType  );
							#endif
						    goto  errLabel;							
					  }

					  //
					  //if  (  !(  pMsgTask  =  findTaskInProcessQ(  &m_var,  iTaskId,  0  )  )  )  goto  errLabel;
					  if  (  !pMsgTask  )  goto errLabel;
 										  
					  // 
					  iStatus  =  CONST_imTaskStatus_waitToRecv;
					  iStatus_old  =  pMsgTask->iStatus;
					  //					
					  if  (  g_dbFuncs.pf_updateTaskStatus(  pDb,  iStatus,  rcd.id  )  )  goto  errLabel;
					  pMsgTask->iStatus  =  iStatus;
		  
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
					  if  (  rcd.uiContentType  ==  CONST_imCommType_transferFileReq  )  {
						  /*
						  CQyMalloc						mallocObj_transferFileReplyReq;
						  TRANSFER_FILE_REPLYREQ	*	pTransferFileReplyReq	=	(  TRANSFER_FILE_REPLYREQ  *  )mallocObj_transferFileReplyReq.mallocf(  sizeof(  TRANSFER_FILE_REPLYREQ  )  );
						  if  (  !pTransferFileReplyReq  )  goto  errLabel;
						  TRANSFER_FILE_REPLYREQ	&	transferFileReplyReq	=	*pTransferFileReplyReq;
						  */
						  TASK_transferFile task;
						  memset(&task,0,sizeof(task));
						  //
						  task.m_index_taskInfo=iIndex_taskInfo;
						  pTaskInfo->var.m_bReplyTask=true;
						  //
						  TRANSFER_FILE_REPLYREQ transferFileReplyReq;
						  PROC_TASK_FILE &transferFileReplyReq_myTask=task.myTask;

						  //
						  memset(  &transferFileReplyReq,  0,  sizeof(  transferFileReplyReq  )  );
						  transferFileReplyReq.uiType  =  CONST_imCommType_transferFileReplyReq;
						  transferFileReplyReq.usOp  =  usOp;
						  transferFileReplyReq.tStartTime_org  =  rcd.tSendTime;
						  transferFileReplyReq.uiTranNo_org  =  rcd.uiTranNo;
						  transferFileReplyReq.uiSerialNo_org  =  rcd.uiSerialNo;
						  //
						  task.myTask.ui64FileLen  =  pContent->transferFileReq.ui64FileLen;	//  _tcstol(  rcd.propStrs[0],  &pT,  10  );
						  _sntprintf(  task.myTask.fileName_transferred,  mycountof(  task.myTask.fileName_transferred  ),  _T(  "%s"  ),  rcd.subject  );
						  _sntprintf(  task.myTask.fullFilePath_save,  mycountof(  task.myTask.fullFilePath_save  ),  _T(  "%s"  ),  rcd.content  );
						  //  2014/07/13
						  unsigned  int  uiSizePerSnd_internal  =  0;
						  if  (  pProcInfo->processQ_media.isEmpty(  )  )  uiSizePerSnd_internal  =  pProcInfo->cfg.uiSizePerSnd_file_noAv;
						  else  uiSizePerSnd_internal  =  pProcInfo->cfg.uiSizePerSnd_file_avExists;
						  task.myTask.uiSizePerSnd_internal  =  min(  uiSizePerSnd_internal,  pContent->transferFileReq.uiSizePerSnd_suggest  );	//  PDEFAULT_usSizePerSnd_file;
						  //
						  transferFileReplyReq_myTask.hWnd_task  =  hDlgTalk;		//  2009/10/20
						  //
						  lenInBytes  =  sizeof(  transferFileReplyReq  );
						  //					
						  MACRO_prepareForTran(  );

						  //
						  task.myTask.reply_info.tStartTime_reply=tStartTran;
						  task.myTask.reply_info.uiTranNo_reply=uiTranNo;
						  task.myTask.reply_info.replyReq  =  transferFileReplyReq;
						  		
						  //						
						  if(0!=pProcInfo->processQ_media.qPostMsg(&task,sizeof(task)))							
						  {							  
							  goto errLabel;								
						  }

						  //
						  chkToApplyForChannel(pProcInfo, CONST_channelType_robot, true);

						  //
						  showInfo_open0(0, 0, (TCHAR*)_T("dlgTalk_procTask_transferFileReq: send reply"));

						  //
						  unsigned  int  uiChannelType  =  CONST_channelType_robot;
						  //
						  uiChannelType  =  0;
						  //
						  if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendRobotTaskReply,  tStartTran,  uiTranNo,  0,  iTaskId,  rcd.uiMode,  (  char  *  )&transferFileReplyReq,  lenInBytes,  &m_var.addr.idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &rcd.idInfo_send,  uiChannelType,  NULL,  FALSE  )  )  goto  errLabel;
					  
                          }
					  else  if  (  rcd.uiContentType  ==  CONST_imCommType_transferAvInfo  )  {
						  
								//
								}
					  else  if  (  rcd.uiContentType  ==  CONST_imCommType_queryCustomerServiceOfficerReq  )  {		//  2011/04/08
								//
								QM_OBJQ_MEM				mem;
								QMEM_MESSENGER_CLI	*	pQMemObj;

								if  (  findQMemByKey(  pProcInfo->pSgiParam,  (  QM_OBJQ  *  )m_var.pMisCnt->pObjQ,  &m_var.addr.idInfo,  &mem  )  )  {
									traceLog((TCHAR*)  _T(  "dlgTalk_procTask failed, findQMemByKey failed."  )  );
									goto  errLabel;
								}
								if  (  !mem.pQMemObj  )  goto  errLabel;
		
								pQMemObj  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
								pQMemObj->customerService.rules.uiCmd_autoAnswer_av  =  CONST_ruleCmd_permit;				//  这里要把视频客服的策略设置成允许，否则就不能自动接收了
								pQMemObj->customerService.rules.uiCmd_autoAnswer_screen  =  CONST_ruleCmd_permit;

								//
								QUERY_customerServiceOfficer_replyReq	replyReq;

								memset(  &replyReq,  0,  sizeof(  replyReq  )  );
								replyReq.uiType  =  CONST_imCommType_queryCustomerServiceOfficerReplyReq;
								//
								replyReq.tStartTime_org  =  pMsgTask->tStartTime;
								replyReq.uiTranNo_org  =  pMsgTask->uiTranNo;
								//
								safeWcsnCpy(  m_var.pMisCnt->talkerDesc,  replyReq.talkerDesc,  mycountof(  replyReq.talkerDesc  )  );
								//
								lenInBytes  =  sizeof(  replyReq  );
								//					
								MACRO_prepareForTran(  );						  
								//
								if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendTaskReply,  tStartTran,  uiTranNo,  0,  iTaskId,  rcd.uiMode,  (  char  *  )&replyReq,  lenInBytes,  &m_var.addr.idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &rcd.idInfo_send,  0,  NULL,  FALSE  )  )  goto  errLabel;
						        
							    }
					  else  {
							#ifdef  __DEBUG__
									traceLog((TCHAR*)  _T(  "dlgTalk_procTask failed, unprocessed contentType %d"  ),  rcd.uiContentType  );
							#endif
						    goto  errLabel;							
					  }
					  //

					  //  2010/12/24
					  chkResources(  hDlgTalk,  FALSE  );

					  }
					  
					  break;
				default:
						break;
	 }
					  

	 iErr  =  0;
errLabel:
	 return  iErr;

 }



