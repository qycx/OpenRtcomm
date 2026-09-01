
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
#include	"GuiShare.h"


 __declspec(  dllexport  )  int  dlgTalk_procCmd(  HWND  hCurTalk,  int  nID,  int  iTaskId,  unsigned  short  usOp,  LPCTSTR  paramStrBuf,  PARAM_dlgTalk_procTask  *  pParam  )
 {
	int  iErr  =  -1; 
	//
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	//
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	//
	if  (  !hCurTalk  )  return  -1;
	CHelp_getDlgTalkVar	help_getDlgTalkVar_cur;
	DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_cur.getVar(  hCurTalk  );
	if  (  !pCurVar  )  return  -1;

	HWND  hMgr  =  hCurTalk;
	if  (  !isTalkerShadowMgr(  pCurVar->addr  )  )  {
		TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pCurVar->pShadowInfo;
		if  (  !pShadow  )  return  -1;
		hMgr  =  pShadow->hMgr;
	}
	if  (  !hMgr  )  return  -1;

	//
	CHelp_getDlgTalkVar					help_getDlgTalkVar;
	DLG_TALK_var					*	pMgrVar							=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hMgr  );
	if  (  !pMgrVar  )  return  -1;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	//
	MC_VAR_isCli					*	pProcInfo							=	QY_GET_procInfo_isCli(  );  //(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	MIS_CNT  *  pMisCnt  =  pMgrVar->pMisCnt;

	//
	switch  (  nID  )  {
			case  ID_menuItemIdc_shareFullScreen:  {
				  int  ii;
				  ii  =  0;
				  //
				  if  (  !pMgrVar->av.taskInfo.bTaskExists  )  goto  errLabel;
				  QMC_TASK_INFO  *  pTaskInfo;
				  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pMgrVar->av.taskInfo.iIndex_taskInfo  );
				  if  (  !pTaskInfo  )  goto  errLabel;
				  QMC_taskData_conf  *  pTc;
				  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;				  

				  //
				  if  (  pTc->shareScreen.bTaskExists  )  {
					  //
					  if  (  pMgrVar->av.taskInfo.ucbStarter  )  {

						  //
						  AV_stream_simple  ass  =  {0};
						  ass.resObj.uiObjType  =  CONST_objType_screen;
						  //
						  pProcInfo->confStarter_requestToSpeak(  hMgr,  &pMisCnt->idInfo,  &ass,  NULL,  false  );
						  //
						  pProcInfo->sendConfKey(  hMgr,  pMgrVar->addr.idInfo,  _T(  "dlgTalk_procCmd"  )  );
					  
						  }
					  else  {
						    RES_obj_simple  ros  =  {0};
						    ros.uiObjType  =  CONST_objType_screen;
							//
						    confOthers_requestToSpeak(  hMgr,  -1,  &ros,  false  );
					  }

					  //
					  GuiShare.pf_freeSharedObjByIndex(  pProcInfo,  pTc->shareScreen.index_sharedObj  );
					  pTc->shareScreen.bTaskExists  =  false;

					  //
				  }
				  
				  //					
				  GuiShare.pf_chkResources(  hMgr,  true  );
				  
				  }
				  //
				  break;
			case  ID_startShareMediaDevice_unresizable: 
			{

				int  ii;
				ii = 0;
				//
				if (!pMgrVar->av.taskInfo.bTaskExists)  goto  errLabel;
				QMC_TASK_INFO* pTaskInfo;
				pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, pMgrVar->av.taskInfo.iIndex_taskInfo);
				if (!pTaskInfo)  goto  errLabel;
				QMC_taskData_conf* pTc;
				pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;

				//
				if (pTc->shareMediaDevice.bTaskExists) {
					//
					QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, pTc->shareMediaDevice.index_sharedObj);
					if (!pSharedObj)  goto  errLabel;
					unsigned  int uiObjType = 0;
					if (isAvFlg_unresizable(pSharedObj->taskAvProps.v.ucAvFlg)) {
						uiObjType = CONST_objType_screen;
					}
					else {
						goto  errLabel;
					}
					//
					if (pMgrVar->av.taskInfo.ucbStarter) {
						goto  errLabel;
					}
					else {
						RES_obj_simple  ros = { 0 };
						ros.uiObjType = uiObjType;
						//
						confOthers_requestToSpeak(hMgr, -1, &ros, false);
					}

					//
					GuiShare.pf_freeSharedObjByIndex(pProcInfo, pTc->shareMediaDevice.index_sharedObj);
					pTc->shareMediaDevice.bTaskExists = false;

					//
				}

				//					
				GuiShare.pf_chkResources(hMgr, true);

			}

				  //
				  break;

			default:
					break;
	}



	iErr  =  0;
	errLabel:
	 return  iErr;

 }




 //
 //__declspec(  dllexport  )  int  procSendFile(  LPCTSTR  fullFilePath,  HWND  m_hWnd,  void  *  pDLG_TALK_var  )
 __declspec(dllexport)  int  procSendFile(LPCTSTR  fullFilePath, LPCTSTR  fileName, void* pPROC_offlineRes_u, HWND  m_hWnd, void* pDLG_TALK_var, int* piTaskId)
 {
	 MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	 FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	 if (!pFuncs)  return  -1;

#if  0//ndef  __SUPPORT_HTMLEDIT__
	 return  -1;
#else

	 DLG_TALK_var* pm_var = (DLG_TALK_var*)pDLG_TALK_var;
	 if (!pm_var)  return  -1;
	 DLG_TALK_var& m_var = *pm_var;

	 QY_MC* pQyMc = QY_GET_GBUF();
	 //IHTMLDocument2* pDoc = NULL;
	 TCHAR				tBuf[256] = _T("");
	 DWORD64				ui64FileLen = 0;
	 CQyMalloc			mallocObj;
	 //  unsigned  char		ucFlg		=	0;


	 if (!fullFilePath)  return  -1;
	 if (GetFileAttributes(fullFilePath) == -1) {
		 traceLogA("procSendFile: file not exists, %S", fullFilePath);
		 return  -1;
	 }

	 //  ÕâÀï£¬ÔÝÊ±²ÉÓÃ32Î»µÄÎÄ¼þ´óÐ¡¡£ÒÔºó¸ÄÎª64Î»µÄ£¬ÒÔÖ§³Ö´óÎÄ¼þ
	 struct _stat64 statBuf;
	 if (_tstat64(fullFilePath, &statBuf))  return  -1;
	 ui64FileLen = statBuf.st_size;

	 //
	 if (ui64FileLen == 0) {
		 //qyShowHint(_T("send failed, fileLen is 0"));
		 return -1;
	 }


	 //
		 //
	 int  iTaskId = 0;
	 //
	 {
		 void* pDb = NULL;
#ifndef  __NOTSUPPORT_DB__
		 CQnmDb		db;
		 if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
		 pDb = db.m_pDbMem->pDb;
#endif

		 iTaskId = newTaskId(pDb, pQyMc->cfg.db.iDbType);
	 }
	 int  iTaskId_suggested = iTaskId;

	 int  iIndex_taskInfo = -1;

	 unsigned  int  uiTaskDataType = 0;
	 uiTaskDataType = CONST_taskDataType_transferFile;
	 iIndex_taskInfo = newTaskInfoIndex(pProcInfo, uiTaskDataType, m_hWnd, iTaskId_suggested, _T("procSendFile"));
	 if (iIndex_taskInfo < 0) {
		 traceLogA("procSendAvInfoFunc faile, newTaskInfoIndex failed");
		 goto  errLabel;
	 }
	 QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, iIndex_taskInfo);
	 if (pTaskInfo == NULL)goto errLabel;




	 //  ÏÈÉêÇëtStartTime, uiTranNo
	 MACRO_prepareForTran();

	 //  ÏÈ·ÅÈëÊý¾Ý¿âÖÐ£¬·¢±éÖØ·¢ºÍ¼ÇÂ¼×´Ì¬
	 //MIS_MSG_TASK				*	pMsg	=	(  MIS_MSG_TASK  *  )mallocObj.mallocf(  sizeof(  MIS_MSG_TASK  )  );
	 MIS_MSG_TASK* pMsg = &pTaskInfo->var.pTaskData->msgU.task;
	 if (!pMsg)  goto  errLabel;
	 TRANSFER_FILE_REQ* pContent;
	 unsigned  int					lenInBytes;
	 IM_TASK_RCD						rcd;
	 //
	 MACRO_memset_misMsgTask(pMsg);
	 pMsg->uiType = CONST_misMsgType_task;
	 //
	 pMsg->pMisCnt = m_var.pMisCnt;
	 //
	 pMsg->ucFlg = CONST_commFlg_routeTalkData;
	 //
	 pMsg->usCode = CONST_qyCmd_sendRobotTask;
	 pMsg->tStartTime = tStartTran;
	 pMsg->uiTranNo = uiTranNo;
	 //
	 pContent = (TRANSFER_FILE_REQ*)pMsg->data.buf;
	 memset(pContent, 0, sizeof(pContent[0]));
	 pContent->uiType = CONST_imCommType_transferFileReq;
	 lstrcpyn(pContent->fullFilePath, fullFilePath, mycountof(pContent->fullFilePath));
	 if (fileName && fileName[0]) {
		 safeTcsnCpy(fileName, pContent->fileName, mycountof(pContent->fileName));
	 }
	 else {
		 if (pProcInfo->getDirAndFinalName(pContent->fullFilePath, NULL, 0, pContent->fileName, mycountof(pContent->fileName)))  goto  errLabel;
	 }
	 pContent->ui64FileLen = ui64FileLen;
	 //  2014/07/13
	 unsigned  int  uiSizePerSnd_internal = 0;
	 if (pProcInfo->processQ_media.isEmpty())  uiSizePerSnd_internal = pProcInfo->cfg.uiSizePerSnd_file_noAv;
	 else  uiSizePerSnd_internal = pProcInfo->cfg.uiSizePerSnd_file_avExists;
	 pContent->uiSizePerSnd_suggest = uiSizePerSnd_internal;

	 //  2015/08/05
	 if (pPROC_offlineRes_u) {
		 PROC_offlineRes_u* pProcOfflineRes = (PROC_offlineRes_u*)pPROC_offlineRes_u;
		 if (pProcOfflineRes->common.usSubtype == CONST_procOfflineResSubtype_upload) {
			 pContent->usSubtype = pProcOfflineRes->common.usSubtype;
			 pContent->idInfo_logicalPeer.ui64Id = pProcOfflineRes->upload.idInfo_logicalPeer.ui64Id;
			 //
			 pContent->hTool_offlineRes = pProcOfflineRes->upload.hTool_offlineRes;
		 }
		 else  if (pProcOfflineRes->common.usSubtype == CONST_procOfflineResSubtype_download) {
			 pContent->usSubtype = pProcOfflineRes->common.usSubtype;
			 pContent->idInfo_logicalPeer.ui64Id = pProcOfflineRes->download.idInfo_logicalPeer.ui64Id;
		 }
	 }

	 //
	 //pContent->MAX_FILE_SEND_BLOCK_suggest = 1;


	 //
	 TASK_transferFile  task;
	 memset(&task, 0, sizeof(task));
	 task.m_index_taskInfo = iIndex_taskInfo;

	 PROC_TASK_FILE& pContent_myTask = task.myTask;



	 //  2009/10/20
	 pContent_myTask.hWnd_task = m_hWnd;

	 //  2007/07/18
	 pMsg->uiTaskType = CONST_imTaskType_sendFile;
	 //
	 pMsg->idInfo_taskSender.ui64Id = m_var.pMisCnt->idInfo.ui64Id;
	 pMsg->idInfo_taskReceiver.ui64Id = m_var.addr.idInfo.ui64Id;
	 //
	 pMsg->iStatus = CONST_imTaskStatus_waitToSend;

	 //
	 pMsg->addr_logicalPeer.idInfo = m_var.addr.idInfo;


	 //  ÕâÀïµÄ¸³ÖµËÆºõÓ¦ÔÚ·¢ËÍÊ±Ê¹ÓÃ, 2007/07/24
	 pMsg->data.route.idInfo_from.ui64Id = pMsg->idInfo_taskSender.ui64Id;
	 pMsg->data.route.idInfo_to.ui64Id = pMsg->idInfo_taskReceiver.ui64Id;
	 //

	 lenInBytes = sizeof(pContent[0]);
	 pMsg->lenInBytes = offsetof(MIS_MSG_routeTalkData, buf) + lenInBytes;

	 if (!pFuncs->pf_msg2TaskRcd(m_var.pMisCnt, pMsg, CONST_qyRc_unknown, &rcd))  goto  errLabel;

	 {
		 void* pDb = NULL;
#ifndef  __NOTSUPPORT_DB__
		 CQnmDb	db;
		 //
		 if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
		 pDb = db.m_pDbMem->pDb;
#endif
		 //
		 if (pFuncs->pf_storeTaskInDb(pDb, pQyMc->cfg.db.iDbType, m_var.pMisCnt, iTaskId_suggested, &rcd, FALSE) < 0)  goto  errLabel;
	 }

	 //
		 //  2013/02/13
	 if (iTaskId_suggested) {		//  2014/10/29
		 if (rcd.id != iTaskId_suggested) {
#ifdef  __DEBUG__
			 traceLog(_T("procSendFile failed, rcd.id != taskInfo.iTaskId"));
#endif
			 goto  errLabel;
		 }
	 }

	 //


 //
	 pMsg->iTaskId = rcd.id;
	 pMsg->uiTaskMode_unused = rcd.uiMode;
	 pMsg->uiChannelType = CONST_channelType_robot;	//  2009/10/17

	 PARAM_PROC_ROW  param;
	 memset(&param, 0, sizeof(param));
	 param.bScrollIntoView = TRUE;
	 param.bNewMsg = TRUE;
	 if (pFuncs->pf_tmpHandler_showMsg(m_hWnd, &param, pMsg))  goto  errLabel;//显示一条消息记录

	 if (pFuncs->pf_dlgTalk_qPostMsg(m_hWnd, pMsg, offsetof(MIS_MSG_TASK, data) + pMsg->lenInBytes))  goto  errLabel;//放到talk内部处理队列

	 //	
	 if (m_var.addr.uiObjType == CONST_objType_imGrp) {
		 pContent->bGrpTask = TRUE; //  2007/09/05, ¸³ÉÏ×é±êÊ¶
	 }


	 //
	 if (0 != pProcInfo->processQ_media.qPostMsg(&task, sizeof(task)))//建立实时任务。
	 {
		 traceLogA("procMsgTask_mc_robot: 1. qPostMsg failed");
		 goto errLabel;
	 }



	 //  mgr
	 unsigned  int  uiChannelType = CONST_channelType_robot;
	 //
	 uiChannelType = 0;
	 //发送文件任务请求发送到对方。
	 if (postMsgTask2Mgr_mc(m_var.pMisCnt, CONST_misMsgType_task, 0, CONST_qyCmd_sendRobotTask, tStartTran, uiTranNo, 0, pMsg->iTaskId, pMsg->uiTaskType, (char*)pContent, lenInBytes, &m_var.addr.idInfo, &pMsg->idInfo_taskSender, &pMsg->idInfo_taskReceiver, &m_var.addr.idInfo, uiChannelType, NULL, 0))  goto  errLabel;

	 //  2015/08/06
	 if (piTaskId)  *piTaskId = rcd.id;

 errLabel:
	 return  0;
#endif
 }


