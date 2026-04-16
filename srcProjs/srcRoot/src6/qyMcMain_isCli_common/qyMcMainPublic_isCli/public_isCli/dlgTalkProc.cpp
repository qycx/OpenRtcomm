

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
#include	"policyIsClientFunc.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliExPublic.h"
#include	"isCliCorePublic.h"
#include	"dyn_isCliD3d_public.h"
#include	"myTChar.h"

#ifdef  __TEST_ONLY__
		#include	"testOnly.h"
#endif

 //  int  getDefaultPolicyAvLevel(  );
 BOOL  bReady_toShowMsg(  HWND  hCurTalk  );
 int  tmpHandler_shadow_displayProcessedMsg(  void  *  hDlgTalkParam,  void  *  p1, void  *  pMsgParam  );
 int  mySendTalkResp(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_TALK  *  pMsg,  MIS_MSGU  *  pMsgBuf  );
//
  BOOL  bPermitted_taskAv(  QY_MC  *  pQyMc,  QY_MESSENGER_ID  *  pIdInfo_grp,  TCHAR  *  hint,  unsigned  int  cnt  );
  int dlgTalk_closeTaskAv_afterTaskClosed(HWND  hDlgTalk, DLG_TALK_var* pm_var);




#ifndef  __WINCE__

  //  2014/07/12
 CQyString		getRowIdStr_talk(  HWND  hDlgTalk,  MIS_MSG_TALK  *  pMsg  )  
{	
	TCHAR			tBuf[CONST_maxRowIdStrLen  +  1]	=  _T(  ""  );
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var  *  pm_var		=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk,  _T(  "getRowIdStr_talk"  )  );
	if  (  !pm_var  )  return  CQyString(  (char*)""  );

	//
	__int64  t64  =  pMsg->tStartTime;
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "tRowId%I64u_%I64u_%d"  ),  pMsg->data.route.idInfo_from.ui64Id,  t64,  pMsg->uiTranNo  );  

	return  CQyString(  tBuf  );  
}



#endif






 //
 int  chkResources(  HWND  hDlgTalk,  BOOL  bFreeCapImages  )
{
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	HWND  hCurTalk  =  hDlgTalk;
	DLG_TALK_var	*	pCurVar	=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hCurTalk,  _T(  "chkRecvdResources"  )  );
	if  (  !pCurVar  )  return  -1;
	//
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	HWND  hMgr  =  hCurTalk;
	DLG_TALK_var  *  pMgrVar  =  pCurVar;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
		TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pCurVar->pShadowInfo;
		hMgr  =  pShadow->hMgr;
		pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
		if  (  !pMgrVar  )  return  -1;
	}
	//
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;
	//
	DLG_TALK_var  &  m_var  =  *pCurVar;  

	//
#if  0
	int		nScreens,  nMediaFiles;
	int		iW_screen,  iH_screen;
#endif
	//
	INFO_recvResource  info_recvdResource  =  {0};
	INFO_sendResource  info_sendResource  =  {0};
	//
	BOOL	bTaskExists	=	FALSE;

	//  bTaskExists  =  bTaskExists_recvdResource(  &m_var,  &nScreens,  &nMediaFiles,  NULL,  &iW_screen,  &iH_screen,  NULL  );
	bTaskExists  =  bTaskExists_recvResource1(  pMgrVar,  &info_recvdResource  );
	if  (  bTaskExists  !=  pShadowMgr->resourcesInfo.bTaskExists_recvd_screenAndMediaFile  )  pShadowMgr->resourcesInfo.bTaskExists_recvd_screenAndMediaFile  =  bTaskExists;
	//  2017/08/23
	if  (  memcmp(  &pShadowMgr->resourcesInfo.info_recv,  &info_recvdResource,  sizeof(  info_recvdResource  )  )  )  pShadowMgr->resourcesInfo.info_recv  =  info_recvdResource;
	//
	bTaskExists_sendingResource1(  pMgrVar,  &info_sendResource  );
	if  (  memcmp(  &pShadowMgr->resourcesInfo.info_send,  &info_sendResource,  sizeof(  info_sendResource  )  )  )  pShadowMgr->resourcesInfo.info_send  =  info_sendResource;
		
	//
	//  2014/11/13		
	if  (  isTalkerShadowMgr(  m_var.addr  )  )  {					
		TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
		if  (  pShadowMgr  )  {
			pShadowMgr->shareScreen.ucbExists_localScreenSharing  =  info_sendResource.nScreens  > 0;//  findTaskInProcessQ(  &m_var,  0,  0,  TRUE  )  !=  NULL;					  
		}				  
	}

	//  2014/12/09
	if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
		//dlgTalk_chkAutoAnswer(  hDlgTalk  );
	}

	//  2012/05/22
	askToRefreshLayout_mgr(  hDlgTalk  );

	return  0;
}


 //
 int  dlgTalk_closeTask(  HWND  hDlgTalk,  int  iTaskId  )
 {
	 int  iErr =  -1;
	 CCtxQyMc *pQyMc=g_pQyMc;
	 CCtxQmc * pProcInfo=(CCtxQmc *)pQyMc->get_pProcInfo();

	 CHelp_getDlgTalkVar  help_getVar;
	 DLG_TALK_var * pm_var = (DLG_TALK_var*)help_getVar.getVar(hDlgTalk);
	 if(!pm_var )  return  -1;
	 DLG_TALK_var  & m_var = *pm_var;
	 if(!isTalkerShadowMgr(m_var.addr))  return -1;

	 int index_taskInfo=getQmcTaskInfoIndexBySth(pProcInfo,iTaskId );
	 if(index_taskInfo<0) return -1;

	 if(  m_var.av.taskInfo.bTaskExists
		 &&  m_var.av.taskInfo.iTaskId==iTaskId  )  
	 {
		 dlgTalk_closeTaskAv(  hDlgTalk, m_var  );
		 iErr = 0; goto errLabel;
	 }

	 //
	 QMC_TASK_INFO  *  pTaskInfo=(QMC_TASK_INFO *  )getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
	 if(pTaskInfo==NULL ) goto errLabel;
	 

	 if(  !qmcTaskInfo_bAlive(  pProcInfo,  index_taskInfo  )  )  {
		 iErr = 0;  goto errLabel;
	 }

	 removeTask(pTaskInfo->var.iTaskId);
	 qmcTaskInfo_setClosed(pProcInfo,index_taskInfo,  _T(  "dlgTalk_closeTask"  )  );
	 
	 iErr = 0;
errLabel:
	 return iErr;
 }


 //
 int  confStarter_sendToCancelTaskAv(  HWND  hDlgTalk,  DLG_TALK_var  &  m_var  )
 {
	 int  iErr  =  -1;
	 
	 CCtxQmc  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	 if  (  !m_var.av.taskInfo.bTaskExists  )  return  -1;
	 if  (  !m_var.av.taskInfo.ucbStarter  )  return  -1;

	 QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  m_var.av.taskInfo.iIndex_taskInfo  );
	 if  (  !pTaskInfo  )  return  -1;

	 MIS_MSG_TASK  *  pMsgTask  =  &pTaskInfo->var.pTaskData->msgU.task;
	 if  (  pMsgTask->uiType  !=  CONST_misMsgType_task  )  return  -1;

	 unsigned  short  usOp  =  CONST_imOp_send_cancel;

	 IM_CONTENTU  *  pContent  =  M_getMsgContent(  pMsgTask->ucFlg,  &pMsgTask->data  );
	 if  (  !pContent  )  goto  errLabel;

	 int  lenInBytes;

	 					  //  
					  TASK_PROC_REQ		taskProcReq;
					  memset(  &taskProcReq,  0,  sizeof(  taskProcReq  )  );
					  taskProcReq.uiType  =  CONST_imCommType_taskProcReq;
					  taskProcReq.usOp  =  usOp;
					  taskProcReq.tStartTime_org  =  pMsgTask->tStartTime;//rcd.tSendTime;
					  taskProcReq.uiTranNo_org  =  pMsgTask->uiTranNo;//rcd.uiTranNo;
					  taskProcReq.uiSerialNo_org  =  0;//rcd.uiSerialNo;
					  taskProcReq.uiContentType_org  =  pContent->uiType;//rcd.uiContentType;
					  //
					  lenInBytes  =  sizeof(  taskProcReq  ); 
					  //					  
					  MACRO_prepareForTran(  );						

					  //  2015/09/07
					  unsigned  int  uiChannelType  =  pMsgTask->uiChannelType;
					  //  2015/09/07
					  uiChannelType  =  0;
					  //
					  QY_MESSENGER_ID  idInfo_dst  =  m_var.addr.idInfo;
					  //
					  if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  pMsgTask->usCode,  tStartTran,  uiTranNo,  0,  pMsgTask->iTaskId,  pMsgTask->uiTaskType,  (  char  *  )&taskProcReq,  lenInBytes,  &m_var.addr.idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &idInfo_dst,  uiChannelType,  NULL,  FALSE  )  )  {
						  goto  errLabel;
					  }

					  //
					  showInfo_open0(  0,  0,  _T(  "confStarter_sendToCancelTaskAv"  )  );

					  //
					  iErr  =  0;
errLabel:
					  return  iErr;
 }





 //
 int  dlgTalk_closeTaskAv(HWND  hDlgTalk, DLG_TALK_var& m_var)
 {
	 MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	 QY_MC* pQyMc = (QY_MC*)pProcInfo->pQyMc;

	 //
	 unsigned  __int64  tmp_ui64MeetingId_hg = 0;
	 tmp_ui64MeetingId_hg = pProcInfo->av.doConf.confReq.hgInfo.ui64MeetingId_hg;
	 bool  tmp_bRecord = pProcInfo->av.doConf.confReq.hgInfo.bRecord_conf;

	 //
	 if (pProcInfo->av.localAv.idInfo_curConference.ui64Id) {
		 if (m_var.addr.idInfo.ui64Id == pProcInfo->av.localAv.idInfo_curConference.ui64Id) {
			 pProcInfo->av.localAv.idInfo_curConference.ui64Id = 0;
		 }
	 }

	 //
	 //
	 if (m_var.av.taskInfo.bTaskExists) {
		 QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, m_var.av.taskInfo.iIndex_taskInfo);
		 if (pTaskInfo) {
			 if (pTaskInfo->var.pTaskData->uiType == CONST_taskDataType_conf) {
				 QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
				 //
				 if (pTc->shareScreen.bTaskExists) {
					 freeSharedObjByIndex(pProcInfo, pTc->shareScreen.index_sharedObj);
					 pTc->shareScreen.bTaskExists = false;
				 }
				 //
				 if (pTc->shareMediaDevice.bTaskExists) {
					 freeSharedObjByIndex(pProcInfo, pTc->shareMediaDevice.index_sharedObj);
					 pTc->shareMediaDevice.bTaskExists = false;
				 }
			 }
		 }

		 //
		 pProcInfo->reportToHg_meetingOn(m_var.av.taskInfo.hgInfo.ui64MeetingId_hg, m_var.av.taskInfo.hgInfo.iMeetingType_hg,  m_var.addr.idInfo.ui64Id,  false);
	 }


	 //  2016/03/15
	 exitTalkerThread(pProcInfo, &m_var.talkerThreadInfo);

	 //  2009/08/16
	 if (m_var.av.ucbGot_iIndex_sharedObj_localAv) {

		 //  2017/09/11
		 if (isTalkerShadowMgr(m_var.addr)) {
			 get_conf_stat(hDlgTalk);
		 }

		 //
		 //  2016/03/28
		 int  iIndex_sharedObj = m_var.av.iIndex_sharedObj_localAv;
		 if (bExists_slave(pProcInfo, iIndex_sharedObj)) {
			 QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, iIndex_sharedObj);
			 if (pSharedObj) {
				 int  iIndex_sharedObj_slave;
				 iIndex_sharedObj_slave = pSharedObj->master.slaveKey.iIndex_sharedObj;
				 //
				 freeSharedObjUsr(pProcInfo, iIndex_sharedObj_slave, hDlgTalk);
			 }
		 }
		 //
		 //  askSharedObjToStop(  pProcInfo,  getSharedObjByIndex(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv  ),  pQyMc->gui.hMainWnd  );
		 freeSharedObjUsr(pProcInfo, m_var.av.iIndex_sharedObj_localAv, hDlgTalk);
		 m_var.av.ucbGot_iIndex_sharedObj_localAv = FALSE;
	 }
	 //
	 //freeSharedObjUsr(  pProcInfo,  


	 //  2011/03/14
	 HWND				hMgr = NULL;
	 CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	 //DLG_TALK_var  *		pMgrVar		=  NULL;		
	 if (isTalkerShadowMgr(m_var.addr)) {
		 hMgr = hDlgTalk;
		 //pMgrVar  =  &m_var;
	 }
	 else {
		 TALKER_shadow* pShadow = (TALKER_shadow*)m_var.pShadowInfo;
		 if (pShadow) {
			 hMgr = pShadow->hMgr;
			 //pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pShadow->hMgr  );
			 //if  (  !pMgrVar  )  goto  errLabel;
		 }
	 }


	 //
	 closeInstantAssistant(hDlgTalk);

	 //  2014/11/01
	 if (isTalkerShadowMgr(m_var.addr)) {
		 if (m_var.av.taskInfo.bTaskExists) {
			 //
			 pProcInfo->stopMosaicThreads(&m_var.av.taskInfo.mosaicMaker);
			 //
			 shareDynBmp_closeTaskAv(&m_var.av.taskInfo.mosaicMaker.video);
			 shareDynBmp_closeTaskAv(&m_var.av.taskInfo.mosaicMaker.resource);

			 //
			 qmcTaskInfo_setClosed(pProcInfo, m_var.av.taskInfo.iIndex_taskInfo, _T("dlgTalk_closeTaskAv"));

			 //
#if 0
			 if (pQyMc->appParams.bMcu) {
				 if (m_var.av.taskInfo.ucbStarter) {
					 //
					 clear_doConf(m_var.addr.idInfo, _T("dlgTalk_closeTaskAv"));
					 //
					 sendConfReq(0, hDlgTalk, m_var.addr.idInfo, CONST_imOp_send_cancel, 0, 0, 0);
					 //
					 confStarter_sendToCancelTaskAv(hDlgTalk, m_var);

					 //  2019/03/17
					 showInfo_open0(0, NULL, _T("dlgTalk_closeTaskAv: startToQuitApp"));
					 //
					 pProcInfo->av.doConf.bStartToQuitApp = true;
					 PostMessage(hDlgTalk, WM_CLOSE, 0, 0);
				 }
			 }
#endif
			 //
			 dlgTalk_closeTaskAv_afterTaskClosed(hDlgTalk, &m_var);

		 }
	 }

	 //
	 exitSavers();

	 //
	 memset(&pProcInfo->legal_info, 0, sizeof(pProcInfo->legal_info));

	 //
	 if  (  pQyMc->appParams.bConfServer  )
	 {
		 bool  bRecord = tmp_bRecord;

		 //
		 TCHAR  tt[128];
		 _sntprintf(tt, mycountof(tt), _T("dlgTalk_closeTaskAv: bRecord %d"), bRecord);
		 showInfo_open0(0, 0, tt);

		 //
		 if (bRecord) {

			 //
			 TCHAR  tBuf[256] = _T("");
			 unsigned  int uiType;
			 char  url_prefix[256] = "";
#if 0
			 qyGetRegCfgT(HKEY_LOCAL_MACHINE, _T(CONST_qyRootKey_qnmScheduler_misClient), _T("saveAvUrl_prefix"), (char*)tBuf, sizeof(tBuf), &uiType);
			 tBuf[mycountof(tBuf) - 1] = 0;
			 myTChar2Utf8(tBuf, url_prefix, mycountof(url_prefix));
#endif
			 //
			 Mcu_initCfg  mi;
			 memset(&mi, 0, sizeof(mi));
			 bGetMcuInitCfg(pQyMc->cfg.smCfgFile, &mi);
			 safeStrnCpy(mi.saveAvUrl_prefix, url_prefix, mycountof(url_prefix));

			 //
			 char  buf[256];
			 char  video_url[256] = "";
			 char  resource_url[256] = "";
			 int  index_saver = 0;
			 TCHAR* pFileName;
			 TCHAR* pT;
			 SAVE_av_procInfo* pSave;
			 //
			 index_saver = 0;
			 pSave = getSaver(index_saver);
			 if (pSave) {
				 pFileName = pSave->fullOutputFileName;
				 pT = _tcsrchr(pFileName, _T('\\'));
				 if (pT) {
					 pT++;
					 myTChar2Utf8(pT, buf, mycountof(buf));
					 //
					 _snprintf(video_url, mycountof(video_url), "%s%s", url_prefix, buf);
				 }
			 }
			 index_saver = 1;
			 pSave = getSaver(index_saver);
			 if (pSave) {
				 pFileName = pSave->fullOutputFileName;
				 pT = _tcsrchr(pFileName, _T('\\'));
				 if (pT) {
					 pT++;
					 myTChar2Utf8(pT, buf, mycountof(buf));
					 //
					 _snprintf(resource_url, mycountof(resource_url), "%s%s", url_prefix, buf);
				 }
			 }

			 //
			 pProcInfo->reportToHg_saveAv(tmp_ui64MeetingId_hg, video_url, resource_url);

		 }
	 }

	 //
	 memset(&m_var.av.taskInfo, 0, sizeof(m_var.av.taskInfo));
	 //  2017/10/03
	 m_var.av.dwTickCnt_closeTaskAv = GetTickCount();


	 //  2017/09/06
	 resetTalkerList_mgr(hDlgTalk);

	 //  2017/10/02
	 if (isTalkerShadowMgr(m_var.addr)) {
		 TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)m_var.pShadowInfo;
		 if (pShadowMgr) {
			 if (IsWindow(pProcInfo->dlg2ndScreen.hWnd_2ndScreen)) {
				 QY_WMBUF_COMM	wmBuf;
				 memset(&wmBuf, 0, sizeof(wmBuf));
				 wmBuf.uiType = CONST_qyWmParam_freeCapImages;
				 SendMessageTimeout(pProcInfo->dlg2ndScreen.hWnd_2ndScreen, CONST_qyWm_comm, 0, (LPARAM)&wmBuf, 0, 1000, NULL);
			 }
		 }
	 }


	 //  2010/09/03
	 //  InvalidateRect(  hDlgTalk,  NULL,  TRUE  );
	 PostMessage(hMgr, CONST_qyWm_postComm, CONST_qyWmParam_curSharedObjUsrChanged_mgr, 0);

	 //  2011/04/10
	 if (m_var.addr.idInfo.ui64Id == pProcInfo->customerService.called.idInfo.ui64Id) {
		 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("dlgTalk, customer service, no av exists, closed automatically"));
		 PostMessage(hDlgTalk, WM_CLOSE, 0, 0);
	 }

	 //
	 chkAvStatus();

	 //
	 return  0;
 }


 



 //
 int  tmpHandler_fillConfMgrInfo(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 int  iErr  =  -1;	 	
	 //p0
	 CONF_mgr_info  *  pMgrInfo  =  (  CONF_mgr_info  *  )p1;
	 IM_GRP_MEM  *  pQMem  =  (  IM_GRP_MEM  *  )p2;
	 
	 if  (  pQMem->iRole  ==  CONST_imGrpMemRole_mgr  )  {
		 //

		 //
		 if  (  pMgrInfo->usCnt  >=  mycountof(  pMgrInfo->mems  )  )  {
			 //
			 TCHAR  tBuf[128];
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "too many conf mgrs in a group. max is %d"  ),  mycountof(  pMgrInfo->mems  )  );
			 showInfo_open0(  0,  0,  tBuf  );
			 //
			 iErr  =  1;  goto  errLabel;
		 }
		 //
		 pMgrInfo->mems[pMgrInfo->usCnt].idInfo.ui64Id  =  pQMem->idInfo_mem.ui64Id;
		 pMgrInfo->usCnt  ++  ;
		 //
		 iErr  =  0;  goto  errLabel;	
	 }
	 
	 iErr  =  0;

errLabel:
	
	 return  iErr;
 }


 //  2015/07/28
 int  fillConfMgrInfo(  QY_MC  *  pQyMc,  QY_MESSENGER_ID  *  pIdInfo_grp,  CONF_mgr_info  *  pMgrInfo  )
 {
	 int  iErr  =  -1;
	 //QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	 	void  *  pDb  =  NULL;
		#ifndef  __NOTSUPPORT_DB__
				 CQnmDb				db;
				 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
				 pDb  =  db.m_pDbMem->pDb;
		#endif
	
		int  tmpiRet  =  -1;
		tmpiRet  =  enumGrpMems_isCli(  pDb,  pQyMc->cfg.db.iDbType,  pIdInfo_grp,  tmpHandler_fillConfMgrInfo,  NULL,  pMgrInfo  );
		if  (  tmpiRet  <  0  )  goto  errLabel;
	

		iErr  =  0;

errLabel:
		if  (  !iErr  )  {
		}
	 return  iErr;
 }

 //
 int  getVal_bMsgrConfMgr(  QY_MESSENGER_ID  *  pIdInfo,  CONF_mgr_info  *  pConfMgrInfo,  BOOL  *  pbRet  )
 {
	 int  iErr  =  -1;
	 BOOL  bRet  =  FALSE;

		 if  (  !pIdInfo  ||  !pIdInfo->ui64Id  )  return  -1;
		 if  (  !pConfMgrInfo  )  return  -1;

		 int  i;
		 //
		 for  (  i  =  0;  i  <  pConfMgrInfo->usCnt;  i  ++  )  {
			  if  (  pConfMgrInfo->mems[i].idInfo.ui64Id  ==  pIdInfo->ui64Id  )  {
				  bRet  =  TRUE;
				  break;
			  }
		 }



		iErr  =  0;

errLabel:

		if  (  !iErr  )  {
			if  (  pbRet  )  *pbRet  =  bRet;
		}

	return  iErr;
 }


 ///////////////////////////
 //  2014/10/02. 
//#define		__BGWALL_skip_me__

//


 


  //
  int  exitGrpConfCtrl(  GRP_confCtrl  *  p  )
  {
	  if  (  !p  )  return  0;
	  MACRO_safeFree(  p->pMems  );
	  memset(  p,  0,  sizeof(  p[0]  )  );
	  return  0;
  }


  //
  __declspec(  dllexport  )  BOOL  bFillImGrpMem_confCtrl_myDb(  HWND  hDlgTalkParam,  void  *  pDbParam,  void  *  pParam,  GRP_confCtrl  *  pConfCtrl  );



  //
  int  initGrpConfCtrl(  QY_MC  *  pQyMc,  HWND  hDlgTalk_mgr,  GRP_confCtrl  *  p  )
 {
	 int  iErr  =  -1;
	 //QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	 //
	 if  (  p->pMems  )  return -1;

	 //
	 memset(  p,  0,  sizeof(  p[0]  )  );
	
	 //
	 PARAM_PROC_ROW		param;
	
	 memset(  &param,  0,  sizeof(  param  )  );
	
	 //
	 {	 
		 CQnmDb				db;
				
		 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
				
		 bFillImGrpMem_confCtrl_myDb(  hDlgTalk_mgr,  db.m_pDbMem->pDb,  &param,  NULL  );						

		 //
		 p->usMaxCnt  =  param.nItem;
		 int  size  =  sizeof(  GrpMem_confCtrl  )  *  p->usMaxCnt;
		 p->pMems  =  (  GrpMem_confCtrl  *  )malloc(  size  );
		 if  (  !p->pMems  )  goto  errLabel;
		 memset(  p->pMems,  0,  size  );
		 
		 //
		 memset(  &param,  0,  sizeof(  param  )  );
		 bFillImGrpMem_confCtrl_myDb(  hDlgTalk_mgr,  db.m_pDbMem->pDb,  &param,  p  );						

	 }

	 iErr  =  0;
errLabel:

	 return  iErr;
 }





  //
  //
   int  qCmp_taspRespInfoMem(  const  void  *  p1,  const  void  *  p2  )
{
	TASK_respInfo_mem	*	pElem1  =  (  TASK_respInfo_mem  *  )p1;
	TASK_respInfo_mem	*	pElem2  =  (  TASK_respInfo_mem  *  )p2;
	_int64								iDiff	=	0;				

	iDiff  =  pElem1->idInfo.ui64Id  -  pElem2->idInfo.ui64Id;
	
	if  (  iDiff  <  0  )  return  -1;
	if  (  !iDiff  )  return  0;
	return  1;

}


#ifdef  __DEBUG__
   //
   int  print_TASK_respInfo(  TASK_respInfo  *  pRespInfo,  LPCTSTR  hint  )
   {
	   if  (  !hint  )  hint  =  _T(  ""  );

	   traceLog((TCHAR*)  _T(  "print task_respInfo starts... %s"  ),  hint  );
	   int  i;
	   for  (  i  =  0;  i  <  pRespInfo->usCnt;  i  ++  )  {
		    TASK_respInfo_mem  *  pMem  =  &pRespInfo->mems[i];
			//
			traceLog((TCHAR*)  _T(  "mem[%d] %I64u"  ),  i,  pMem->idInfo.ui64Id  );
	   }

	   traceLog((TCHAR*)  _T(  "print task_respInfo ends."  )  );

	   return  0;
   }
#endif


   //
   int  dlgTalk_init_respInfo(  HWND  hDlgTalk_mgr,  DLG_TALK_var  *  pMgrVar,  unsigned  char  ucbVideoConference  )
   {
	   MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	   if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return  -1;
	   if  (  !pMgrVar->av.ucbGot_iIndex_sharedObj_localAv  )  return  -1;
	   QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pMgrVar->av.iIndex_sharedObj_localAv  );
	   if  (  !pSharedObj  )  return  -1;
	   SHARED_OBJ_USR  *  pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  pMgrVar->av.iIndex_usr_localAv  );
	   if  (  !pSharedObjUsr  )  return  -1;
	   //
	   TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	  
	   if  (  !pMgrVar->av.taskInfo.bTaskExists  )  return -1;
	   QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pMgrVar->iIndex_talkerInfo  );
	   if  (  !pTaskInfo  )  return  -1;

	   //  2017/09/06	
	   TASK_respInfo  *  pRespInfo  =  &pTaskInfo->var.taskRespInfo;
	//
	memset(  pRespInfo,  0,  sizeof(  pRespInfo[0]  )  );
	//
	if  (  ucbVideoConference  )  
	{
		//
		unsigned  int  tmp_usCnt  =  0;
		//
		int  i;
		for  (  i  =  0;  i  <  pShadowMgr->confCtrl.grpConfCtrl.usCnt;  i  ++  )  {
			 GrpMem_confCtrl  *  pMem  =  &pShadowMgr->confCtrl.grpConfCtrl.pMems[i];
			 //  traceLog((TCHAR*)  _T(  "mem[%d] %I64u"  ),  i,  pMem->idInfo.ui64Id  );
			 //
			 if  (  !pMem->idInfo.ui64Id  )  continue;
			 //
			 if  (  tmp_usCnt  >=  mycountof(  pRespInfo->mems  )  )  break;
			 pRespInfo->mems[tmp_usCnt].idInfo.ui64Id  =  pMem->idInfo.ui64Id;
			 tmp_usCnt  ++  ;

			 continue;
		}
		//
		pRespInfo->usCnt  =  tmp_usCnt;

		//
		#ifdef  __DEBUG__
				print_TASK_respInfo( pRespInfo,  _T(  "before qsort"  )  );
		#endif

		//
		qsort(  pRespInfo->mems,  tmp_usCnt,  sizeof(  TASK_respInfo_mem  ),  qCmp_taspRespInfoMem  );  
	
		//
		#ifdef  __DEBUG__
				print_TASK_respInfo( pRespInfo,  _T(  "after qsort"  )  );
		#endif
	
	
	}

	return  0;
   
   }


 



//
#if  0
int  old_doCmd_startShareScreen(  HWND  hDlg,  DLG_TALK_var  *  pm_var  )
{
	int					iErr			=	-1;
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );

	if  (  !pm_var  )  return  -1;
	DLG_TALK_var	&	m_var			=	*pm_var;

	//
	//  2009/10/11	
	if  (  pm_var->addr.uiObjType  ==  CONST_objType_imGrp  )  {

			TCHAR  tHint[128]  =  _T(  ""  );
			if  (  !bPermitted_taskAv(  &pm_var->addr.idInfo,  tHint,  mycountof(  tHint  )  )  )    {
				//qyShowHint(  tHint  );
				showNotification(  0,  0,  0,  0,  0,  0,  tHint  );
				goto  errLabel;
			}
	
	}

	//		
	int						iIndex_sharedObj;		
	int						iIndex_sharedObjUsr		=	0;
	QY_SHARED_OBJ			*	pSharedObj				=	NULL;
	int						iIndex_screenCapProcInfo;
	CAP_procInfo_screen	*	pScreenCapProcInfo	=	NULL;
	COMPRESS_VIDEO		*	pCompressVideo			=	NULL;
	unsigned  int				uiTaskType;

				  OutputDebugString(  _T(  "avRecord_start\n"  )  );

				  iIndex_sharedObj  =  newSharedObjIndex(  pProcInfo,  hDlg,  &iIndex_sharedObjUsr,  NULL  );
				  if  (  iIndex_sharedObj  <  0  )  {
					  showInfo_open0(  0,  0,  _T(  "doCmd_startShareScreen failed, newSharedObj failed"  )  );
					  goto  errLabel;
				  }
				  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
				  if  (  !pSharedObj  )  goto  errLabel;
				  iIndex_screenCapProcInfo  =  newCapProcInfoBmpIndex(  pProcInfo,  iIndex_sharedObj  );	
				  pScreenCapProcInfo  =  (  CAP_procInfo_screen  *  )getCapBmpBySth(  pProcInfo,  iIndex_screenCapProcInfo,  0  );
				  if  (  !pScreenCapProcInfo  )  goto  errLabel;
				  pScreenCapProcInfo->uiType  =  CONST_capType_screen;
				  pScreenCapProcInfo->iIndex_sharedObj  =  iIndex_sharedObj;
				  pScreenCapProcInfo->uiTranNo_sharedObj  =  pSharedObj->uiTranNo;
				  pCompressVideo  =  &pScreenCapProcInfo->compressVideo;
				  
				  //
				  pSharedObj->bDirectX  =  bDirectX_avRecord(  );
				  pSharedObj->bRemoteAssist  =  bRemoteAssist_avRecord(  );		//  2008/11/09, ÊÇ·ñÔ¶³ÌÐ­Öú				
				  pSharedObj->iIndex_capBmp  =  iIndex_screenCapProcInfo;
				  
				  
				  //  2014/04/19
				  if  (  newstartQThreadToShareAv(  pProcInfo,  iIndex_sharedObj,  FALSE  )  )  {
						  goto  errLabel;									  
				  }			
				  
				  //
				  uiTaskType  =  pSharedObj->bRemoteAssist  ?  CONST_imTaskType_remoteAssist  :  CONST_imTaskType_shareScreen;

				  //
				  //m_var.av.ucbSendLocalScreen  =  TRUE;	

				  //
				  sizeAllControls_dlgTalk(  hDlg,  &m_var,  NULL  );					//  µ÷ÕûÒ»ÏÂ²¼¾Ö

				  //  2011/08/08
				  int  level  =  getLevel_avRecord(  );
				  AV_COMPRESSOR_CFG		screenCompressor;
				  if  (  myGetAvCompressorCfg(  CONST_capType_screen,  0,  0,  level,  &screenCompressor  )  )  goto  errLabel;

				  //
				  RECT	selectedRc;		//  ÕâÀïÒª×¢Òâ£ºbmp¿í¶ÈÊÇselectedRcµÄ¿í¶È+1¡£³¤¶ÈÒ²ÊÇÈç´Ë¡£

				  selectedRc  =  getSelectedRect(  );				  
				  //  makeBmpInfoHeader_rgb(  24,  selectedRc.right  -  selectedRc.left  +  1,  selectedRc.bottom  -  selectedRc.top  +  1,  &pCompressVideo->vh_decompress.bih  );
				  makeBmpInfoHeader_rgb(  24,  selectedRc.right  -  selectedRc.left  +  1,  selectedRc.bottom  -  selectedRc.top  +  1,  &pScreenCapProcInfo->vh_org.bih  );
				  //  2014/04/19
				  //  memcpy(  &pScreenCapProcInfo->vh_org.bih,  &pCompressVideo->vh_decompress.bih,  sizeof(  pScreenCapProcInfo->vh_org  )  );
				  //  2014/04/05
				  screenCompressor.video.common.pVideoQ2  =  &pScreenCapProcInfo->thread.q2;
				  screenCompressor.video.common.pParent_transform  =  pScreenCapProcInfo;
				  //
				  if  (  initCompressVideo(  pProcInfo,  (  BITMAPINFO  *  )&pScreenCapProcInfo->vh_org.bih,  CONST_capType_screen,  &screenCompressor.video,  FALSE,  getSize_qyAvRecord(  ),  pCompressVideo  )  )  {
					  //  qyShowHint(  _T(  "Initialize video compress failed!"  )  );  
					  showNotification(  NULL,  0,  0,  0,  0,  0,  _T(  "Initialize video compress failed!"  )  );  
					  goto  errLabel;
				  }
			
				  int  iTaskId  =  0;
				  	{
		void	*	pDb	=	NULL;
		#ifndef  __NOTSUPPORT_DB__
				 CQnmDb		db;
				 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
				 pDb  =  db.m_pDbMem->pDb;
		#endif

		iTaskId  =  newTaskId(  pDb,  pQyMc->cfg.db.iDbType  );
	}

		
				  //  m_var.pProcInfo->av.localAv.curhWnd  =  this->m_hWnd;

				  switch  (  m_var.addr.uiObjType  )  {
						  case  CONST_objType_imGrp:				  
                  
					            //  2014/11/30
							    unsigned  int  uiTranNo_avTask_starter;  uiTranNo_avTask_starter  =  0;
							    BOOL				bAvProxy;		bAvProxy  =  FALSE;
								QY_MESSENGER_ID	idInfo_proxy;	memset(  &idInfo_proxy,  0,  sizeof(  idInfo_proxy  )  );
								//
								if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
									if  (  m_var.av.taskInfo.bTaskExists
										&&  !m_var.av.taskInfo.ucbStarter  )					  
									{
										//  2014/11/22
										uiTranNo_avTask_starter  =  m_var.av.taskInfo.uiTranNo_org;
																  
										//
										if  (  m_var.av.taskInfo.mosaicTrans.bExists_confMosaic  )  {
											bAvProxy  =  TRUE;
											//
											idInfo_proxy.ui64Id  =  m_var.av.taskInfo.idInfo_starter.ui64Id;  						  
										}					  
									}
									
									//
									if  (  bAvProxy  )  {
										QY_MESSENGER_ID  content_idInfo_logicalPeer;
										content_idInfo_logicalPeer.ui64Id  =  m_var.addr.idInfo.ui64Id;
						  
										MSGR_ADDR		addr;						  						  
										memset(  &addr,  0,  sizeof(  addr  )  );
										lstrcpyn(  addr.misServName,  m_var.pMisCnt->cfg.misServName,  mycountof(  addr.misServName  )  );
										addr.idInfo.ui64Id  =  idInfo_proxy.ui64Id;
  
										if  (  procSendAvInfo(  m_var.pMisCnt,  hDlg,  TRUE,  uiTaskType,  pCompressVideo,  NULL,  iIndex_sharedObj,  iIndex_sharedObjUsr,  NULL,  &content_idInfo_logicalPeer,  uiTranNo_avTask_starter,  NULL,  &addr  )  )  {	
											qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: procSendAvInfo failed"  )  );
											goto  errLabel;				  						  
										}						  
										//						  
										break;					  
									}				  
								}
							    //
							    if  (  procSendAvInfo(  m_var.pMisCnt,  hDlg,  TRUE,  uiTaskType,  pCompressVideo,  NULL,  iIndex_sharedObj,  iIndex_sharedObjUsr,  NULL,  NULL,  &iTaskId,  &m_var.addr,  NULL  )  )  goto  errLabel;

								break;
						  case  CONST_objType_tmpGrp:
							    traceLogA(  (char*)  "tmpGrp not supported to share screen"  );
								goto  errLabel;
								break;
						  default: 
							      //				   
								  //  if  (  old_procSendAvInfo(  this->m_hWnd,  uiTaskType,  NULL,  NULL,  NULL,  pCompressVideo,  NULL,  iIndex_sharedObj,  this  )  )  goto  errLabel;
							      if  (  procSendAvInfo(  m_var.pMisCnt,  hDlg,  TRUE,  uiTaskType,  pCompressVideo,  NULL,  iIndex_sharedObj,  iIndex_sharedObjUsr,  NULL,  NULL,  &iTaskId,  &m_var.addr,  NULL  )  )  goto  errLabel;
								  break;

				  }
				  				  
				  //  
				  setFps_capScreen(  screenCompressor.video.common.usMaxFps_toShareBmp  );
				  startAvRecord(  pProcInfo,  iIndex_screenCapProcInfo,  g_pQyMc->gui.hMainWnd  );

				  //  2010/09/09
				  setCurSharedObjUsr(  pProcInfo,  iIndex_sharedObj,  hDlg  );
				  //  2014/11/17				  	
				  setFlg_inConfMosaic(  hDlg,  CONST_qyWndContentType_talker,  iIndex_sharedObj,  iIndex_sharedObjUsr  );

				  //  2014/11/14
				  chkResources(  hDlg,  FALSE  );

				  //  2011/03/12
				  dlgTalk_displayAvStatus(  hDlg,  m_var,  0,  0,  0  );


				  //
				  iErr  =  0;

errLabel:
				  return  iErr;
				  
	
}
#endif


//
int  doCmd_startShareScreen(  QY_MC  * pQyMc,  HWND  hDlgTalk,  DLG_TALK_var  *  pm_var  )
{
	int					iErr			=	-1;
	//QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );

	if  (  !pm_var  )  return  -1;
	DLG_TALK_var	&	m_var			=	*pm_var;

	//
	if  (  !m_var.av.taskInfo.bTaskExists  )  {
		showInfo_open0(  0,  0,  _T(  "shareScreen failed, av.taskinfo.bTaskExists is false"  )  );
		return  -1;
	}

	//	
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  m_var.av.taskInfo.iIndex_taskInfo  );
	if  (  !pTaskInfo  )  goto  errLabel;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

	//
	if  (  pTc->shareScreen.bTaskExists  )  {
		showInfo_open0(  0,  0,  _T(  "shareScreen failed, shareScreen.bTaskExists already true"  )  );
		goto  errLabel;
	}

	
	

	//		
	int						iIndex_sharedObj;		
	int						iIndex_sharedObjUsr		=	0;
	QY_SHARED_OBJ			*	pSharedObj				=	NULL;
	int						iIndex_screenCapProcInfo;
	CAP_procInfo_screen	*	pScreenCapProcInfo	=	NULL;
	COMPRESS_VIDEO		*	pCompressVideo			=	NULL;
	unsigned  int				uiTaskType;

				  OutputDebugString(  _T(  "avRecord_start\n"  )  );

				  iIndex_sharedObj  =  newSharedObjIndex(  pProcInfo,  hDlgTalk,  CONST_sharedObjType_screen,  &iIndex_sharedObjUsr,  NULL  );
				  if  (  iIndex_sharedObj  <  0  )  {
					  showInfo_open0(  0,  0,  _T(  "doCmd_startShareScreen failed, newSharedObj failed"  )  );
					  goto  errLabel;
				  }
				  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
				  if  (  !pSharedObj  )  goto  errLabel;
				  iIndex_screenCapProcInfo  =  newCapProcInfoBmpIndex(  pProcInfo,  iIndex_sharedObj  );	
				  pScreenCapProcInfo  =  (  CAP_procInfo_screen  *  )getCapBmpBySth(  pProcInfo,  iIndex_screenCapProcInfo,  0  );
				  if  (  !pScreenCapProcInfo  )  goto  errLabel;
				  pScreenCapProcInfo->uiType  =  CONST_capType_screen;
				  pScreenCapProcInfo->iIndex_sharedObj  =  iIndex_sharedObj;
				  pScreenCapProcInfo->uiTranNo_sharedObj  =  pSharedObj->uiTranNo;
				  pCompressVideo  =  &pScreenCapProcInfo->compressVideo;
				  
				  //
				  pSharedObj->bDirectX  =  bDirectX_avRecord(  );
				  pSharedObj->bRemoteAssist  =  bRemoteAssist_avRecord(  );		//  2008/11/09, ÊÇ·ñÔ¶³ÌÐ­Öú				
				  pSharedObj->iIndex_capBmp  =  iIndex_screenCapProcInfo;
				  
				  
				  //  2014/04/19
				  if  (  newstartQThreadToShareAv(  pProcInfo,  iIndex_sharedObj,  FALSE  )  )  {
						  goto  errLabel;									  
				  }			
				  
				  //
				  uiTaskType  =  pSharedObj->bRemoteAssist  ?  CONST_imTaskType_remoteAssist  :  CONST_imTaskType_shareScreen;

				  //
				  //m_var.av.ucbSendLocalScreen  =  TRUE;	

				  //
				  sizeAllControls_dlgTalk(  hDlgTalk,  &m_var,  NULL  );					//  µ÷ÕûÒ»ÏÂ²¼¾Ö

				  //  2011/08/08
				  int  level  =  getLevel_avRecord(  );
				  AV_COMPRESSOR_CFG		screenCompressor;
				  if  (  myGetAvCompressorCfg(  CONST_capType_screen,  0,  0,  level,  &screenCompressor  )  )  goto  errLabel;

				  //
				  int  conf_iFourcc  =  get_conf_iFourcc(  );		  
				  //
				  conf_iFourcc = fourccStr2i(pTc->videoConference.activeMems_from[0].avStream.obj.tranInfo.video.compressor.common.fourccStr);
				  //
				  int conf_bitrateInKbps = 0;
				  //		  
				  set_conf_iFourcc(  conf_iFourcc,  conf_bitrateInKbps,  &screenCompressor  );


				  //
				  RECT	selectedRc;		//  ÕâÀïÒª×¢Òâ£ºbmp¿í¶ÈÊÇselectedRcµÄ¿í¶È+1¡£³¤¶ÈÒ²ÊÇÈç´Ë¡£

				  selectedRc  =  getSelectedRect(  );				  
				  //  makeBmpInfoHeader_rgb(  24,  selectedRc.right  -  selectedRc.left  +  1,  selectedRc.bottom  -  selectedRc.top  +  1,  &pCompressVideo->vh_decompress.bih  );
				  makeBmpInfoHeader_rgb(  24,  selectedRc.right  -  selectedRc.left  +  1,  selectedRc.bottom  -  selectedRc.top  +  1,  &pScreenCapProcInfo->vh_org.bih  );
				  //  2014/04/19
				  //  memcpy(  &pScreenCapProcInfo->vh_org.bih,  &pCompressVideo->vh_decompress.bih,  sizeof(  pScreenCapProcInfo->vh_org  )  );
				  //  2014/04/05
				  screenCompressor.video.common.pVideoQ2  =  &pScreenCapProcInfo->thread.q2;
				  screenCompressor.video.common.pParent_transform  =  pScreenCapProcInfo;
				  //
				  if  (  initCompressVideo(  pProcInfo,  (  BITMAPINFO  *  )&pScreenCapProcInfo->vh_org.bih,  CONST_capType_screen,  &screenCompressor.video,  FALSE,  getSize_qyAvRecord(  ),  pCompressVideo  )  )  {
					  //  qyShowHint(  _T(  "Initialize video compress failed!"  )  );  
					  showNotification(  NULL,  0,  0,  0,  0,  0,  _T(  "Initialize video compress failed!"  )  );  
					  goto  errLabel;
				  }
			
				  int  iTaskId  =  0;
				  iTaskId  =  m_var.av.taskInfo.iTaskId;

				  //
				  SHARED_OBJ_USR  *  pSharedObjUsr;
				  pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  iIndex_sharedObjUsr  );
				  if  (  !pSharedObjUsr  )  goto  errLabel;		  
				  //
				  COMPRESS_AUDIO  *  pCompressAudio  =  NULL;
				  /*
		  if  (  pCompressAudio  &&  pCompressAudio->uiTranNo_openAvDev_org  )  {
			  pSharedObjUsr->uiTranNo_openAvDev_a  =  pCompressAudio->uiTranNo_openAvDev_org  +  iIndex_sharedObjUsr;	//  pSharedObj->iIndex_curUsr;
		  }
		  */
		  if  (  pCompressVideo  &&  pCompressVideo->uiTranNo_openAvDev_org  )  {	//  
			  pSharedObjUsr->uiTranNo_openAvDev_v  =  pCompressVideo->uiTranNo_openAvDev_org  +  iIndex_sharedObjUsr;	//  pSharedObj->iIndex_curUsr;
		  }
		  pSharedObjUsr->iTaskId  =  iTaskId;


		
				  //  m_var.pProcInfo->av.localAv.curhWnd  =  this->m_hWnd;
#if  0

				  switch  (  m_var.addr.uiObjType  )  {
						  case  CONST_objType_imGrp:				  
                  
					            //  2014/11/30
							    unsigned  int  uiTranNo_avTask_starter;  uiTranNo_avTask_starter  =  0;
							    BOOL				bAvProxy;		bAvProxy  =  FALSE;
								QY_MESSENGER_ID	idInfo_proxy;	memset(  &idInfo_proxy,  0,  sizeof(  idInfo_proxy  )  );
								//
								if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
									if  (  m_var.av.taskInfo.bTaskExists
										&&  !m_var.av.taskInfo.ucbStarter  )					  
									{
										//  2014/11/22
										uiTranNo_avTask_starter  =  m_var.av.taskInfo.uiTranNo_org;
																  
										//
										if  (  m_var.av.taskInfo.mosaicTrans.bExists_confMosaic  )  {
											bAvProxy  =  TRUE;
											//
											idInfo_proxy.ui64Id  =  m_var.av.taskInfo.idInfo_starter.ui64Id;  						  
										}					  
									}
									
									//
									if  (  bAvProxy  )  {
										QY_MESSENGER_ID  content_idInfo_logicalPeer;
										content_idInfo_logicalPeer.ui64Id  =  m_var.addr.idInfo.ui64Id;
						  
										MSGR_ADDR		addr;						  						  
										memset(  &addr,  0,  sizeof(  addr  )  );
										lstrcpyn(  addr.misServName,  m_var.pMisCnt->cfg.misServName,  mycountof(  addr.misServName  )  );
										addr.idInfo.ui64Id  =  idInfo_proxy.ui64Id;
  
										if  (  procSendAvInfo(  m_var.pMisCnt,  hDlg,  TRUE,  uiTaskType,  pCompressVideo,  NULL,  iIndex_sharedObj,  iIndex_sharedObjUsr,  NULL,  &content_idInfo_logicalPeer,  uiTranNo_avTask_starter,  NULL,  &addr  )  )  {	
											qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: procSendAvInfo failed"  )  );
											goto  errLabel;				  						  
										}						  
										//						  
										break;					  
									}				  
								}
							    //
							    if  (  procSendAvInfo(  m_var.pMisCnt,  hDlg,  TRUE,  uiTaskType,  pCompressVideo,  NULL,  iIndex_sharedObj,  iIndex_sharedObjUsr,  NULL,  NULL,  &iTaskId,  &m_var.addr,  NULL  )  )  goto  errLabel;

								break;
						  case  CONST_objType_tmpGrp:
							    traceLogA(  (char*)  "tmpGrp not supported to share screen"  );
								goto  errLabel;								break;
						  default: 
							      //				   
								  //  if  (  old_procSendAvInfo(  this->m_hWnd,  uiTaskType,  NULL,  NULL,  NULL,  pCompressVideo,  NULL,  iIndex_sharedObj,  this  )  )  goto  errLabel;
							      if  (  procSendAvInfo(  m_var.pMisCnt,  hDlg,  TRUE,  uiTaskType,  pCompressVideo,  NULL,  iIndex_sharedObj,  iIndex_sharedObjUsr,  NULL,  NULL,  &iTaskId,  &m_var.addr,  NULL  )  )  goto  errLabel;
								  break;

				  }
#endif

				  //
				  if  (  pTc->shareScreen.bTaskExists  )  goto  errLabel;
				  pTc->shareScreen.index_sharedObj  =  iIndex_sharedObj;
				  pTc->shareScreen.bTaskExists  =  true;

				  				  
				  //  
				  setFps_capScreen(  screenCompressor.video.common.usMaxFps_toShareBmp  );
				  startAvRecord(  pProcInfo,  iIndex_screenCapProcInfo,  g_pQyMc->gui.hMainWnd  );

				  //  2010/09/09
				  setCurSharedObjUsr(  pProcInfo,  iIndex_sharedObj, iIndex_sharedObjUsr);
				  //  2014/11/17				  	
				  pProcInfo->setFlg_inConfMosaic(  hDlgTalk,  CONST_qyWndContentType_talker,  iIndex_sharedObj,  iIndex_sharedObjUsr  );

				  //
				  if  (  m_var.av.taskInfo.ucbStarter  )  {
					  AV_stream  tmpAs = {0};
					  tmpAs.idInfo.ui64Id  =  m_var.pMisCnt->idInfo.ui64Id;
					  tmpAs.obj.resObj.uiObjType  =  CONST_objType_screen;
					  tmpAs.obj.tranInfo.video.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_v;
					  tmpAs.obj.tranInfo.video.compressor  =  pCompressVideo->compressor;
					  tmpAs.obj.tranInfo.video.vh_compress  =  pCompressVideo->vh_compress;
					  tmpAs.obj.tranInfo.video.vh_stream  =  pCompressVideo->vh_stream;
					  tmpAs.obj.tranInfo.video.vh_decompress  =  pCompressVideo->vh_decompress;
					  //
					  if  (  addTo_activeMems_from(  m_var.pMisCnt,  &tmpAs.idInfo,  &tmpAs.obj,  &pTc->videoConference  )  )  {
						  goto  errLabel;
					  }
				  }


				  //  2014/11/14
				  chkResources(  hDlgTalk,  FALSE  );

				  //
				  QY_MESSENGER_ID  idInfo_dst;
				  if  (  m_var.av.taskInfo.ucbStarter  )  {
					  if  (  !m_var.av.taskInfo.ucbVideoConference  )  {						    
						  idInfo_dst  =  m_var.addr.idInfo;
						  pProcInfo->sendConfKey(  hDlgTalk,  idInfo_dst,  _T(  "doCmd_startShareScreen"  )  );						    
					  }
				  }
				  else  {  //
					    //
					    confOthers_requestToSpeak(  hDlgTalk,  iIndex_sharedObj,  mynull,  true  );
				  }




				  //  2011/03/12
				  dlgTalk_displayAvStatus(  hDlgTalk,  m_var,  0,  0,  0  );


				  //
				  iErr  =  0;

errLabel:
				  return  iErr;
				  
	
}




/*
#define FILE_FILTER_TEXT \
    TEXT("Video Files (*.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v)\0*.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v\0")\
    TEXT("Audio files (*.wav; *.mpa; *.mp2; *.mp3; *.au; *.aif; *.aiff; *.snd)\0*.wav; *.mpa; *.mp2; *.mp3; *.au; *.aif; *.aiff; *.snd\0")\
    TEXT("MIDI Files (*.mid, *.midi, *.rmi)\0*.mid; *.midi; *.rmi\0") \
    TEXT("Image Files (*.jpg, *.bmp, *.gif, *.tga)\0*.jpg; *.bmp; *.gif; *.tga\0") \
    TEXT("All Files (*.*)\0*.*;\0\0")
*/
#define FILE_FILTER_TEXT \
    TEXT("Video Files (*.avi; *.wmv; *.qt; *.mov; *.mpg; *.mpeg; *.m1v)\0*.avi; *.wmv; *.qt; *.mov; *.mpg; *.mpeg; *.m1v\0")\
    TEXT("All Files (*.*)\0*.*;\0\0")



 //  2013/10/04
  int  doCmd_startShareMediaFile(  QY_MC  *  pQyMc,  HWND  hDlg,  int  iWndContentType,  int  level,  LPCTSTR  pathCStr,  int  *piIndex_sharedObj,  int  *  piIndex_sharedObjUsr  )
{
	int								iErr		=	-1;
	//  DLG_TALK_var					&  m_var	=  *(  DLG_TALK_var  *  )pDLG_TALK_var;

#if  0
	LPCTSTR							lpszDefExt  =	TEXT("*\0");
	LPCTSTR							lpszFilter	=	FILE_FILTER_TEXT;
	LPCTSTR							title		=	TEXT("Open Media File...\0");
	CString							pathCStr;
	DWORD							dwFlags     =	OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;
#endif

	//
	//QY_MC						*	pQyMc					=	QY_GET_GBUF(  );
	MC_VAR_isCli				*	pProcInfo				=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	int								iIndex_sharedObj;
	int								iIndex_sharedObjUsr		=	0;
	QY_SHARED_OBJ				*	pSharedObj				=	NULL;
	int								iIndex_capBmp;
	CAP_procInfo_mediaFileBmp	*	pCapBmp					=	NULL;
	COMPRESS_VIDEO				*	pCompressVideo			=	NULL;
	int								iIndex_capAudio;
	CAP_procInfo_mediaFileAudio	*	pCapAudio				=	NULL;
	COMPRESS_AUDIO				*	pCompressAudio			=	NULL;
	//
#if  0
	int								iIndex_shmCmd;
	QM_SHM_CMD					*	pShmCmd					=	NULL;
#endif
	//
	unsigned  int					uiTaskType;
	
	//
	//  pathCStr  =  qyBrowseForFile(  TRUE,  lpszDefExt,  dwFlags,  FILE_FILTER_TEXT,  title,  NULL  );
	//  if  (  pathCStr  ==  ""  )  goto  errLabel;
	if  (  !pathCStr  ||  !pathCStr[0]  )  return  -1;
	
	//
	iIndex_sharedObj  =  newSharedObjIndex(  pProcInfo,  hDlg,  CONST_sharedObjType_mediaFile,  &iIndex_sharedObjUsr,  NULL  );
	if  (  iIndex_sharedObj  <  0  )  {
		qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: newSharedObjIndex failed"  )  );
		goto  errLabel;
	}

	//
	qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile enters, index_sharedobj %d"  ),  iIndex_sharedObj  );
	OutputDebugString(  _T(  "share media file\n"  )  );
	
	//
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  {
		qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: getSharedObjByIndex failed"  )  );
		goto  errLabel;
	}
	//pSharedObj->uiType  =  CONST_sharedObjType_mediaFile;
	iIndex_capBmp  =  newCapProcInfoBmpIndex(  pProcInfo,  iIndex_sharedObj  );
	pCapBmp  =  (  CAP_procInfo_mediaFileBmp  *  )getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );
	if  (  !pCapBmp  )  {
		qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: getCapBmpBySth failed"  )  );
		goto  errLabel;
	}
	pCapBmp->uiType  =  CONST_capType_mediaFile;
	pCapBmp->iIndex_sharedObj  =  iIndex_sharedObj;
	pCapBmp->uiTranNo_sharedObj  =  pSharedObj->uiTranNo;
	pCompressVideo  =  &pCapBmp->compressVideo;
	iIndex_capAudio  =  newCapProcInfoAudioIndex(  pProcInfo,  iIndex_sharedObj  );
	pCapAudio  =  (  CAP_procInfo_mediaFileAudio  *  )getCapAudioBySth(  pProcInfo,  iIndex_capAudio,  0  );
	if  (  !pCapAudio  )  {
		qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: getCapAudiobySth failed"  )  );
		goto  errLabel;
	}
	pCapAudio->uiType  =  CONST_capType_mediaFile;
	pCapAudio->iIndex_sharedObj  =  iIndex_sharedObj;
	pCapAudio->uiTranNo_sharedObj  =  pSharedObj->uiTranNo;
	pCompressAudio  =  &pCapAudio->compressAudio;
#if  0
	iIndex_shmCmd  =  newShmCmdIndex(  pProcInfo,  iIndex_sharedObj  );
	pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  iIndex_shmCmd  );
	if  (  !pShmCmd  )  {
		qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: getShmCmdByIndex failed"  )  );
		goto  errLabel;		    
	}
#endif
	//
	pSharedObj->iIndex_capBmp  =  iIndex_capBmp;
	pSharedObj->iIndex_capAudio  =  iIndex_capAudio;

	//
	//pSharedObj->iIndex_shmCmd  =  iIndex_shmCmd;


	//
#if  10  //  2015/10/11
	BOOL  bAudio  =  TRUE;	//  bNoAudio(  pSharedObj->pShareMediaObj  );
	//
	if  (  newstartQThreadToShareAv(  pProcInfo,  iIndex_sharedObj,  bAudio  )  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "doCmd_startShareMediaFile, startQThreadToShareAv failed"  )  );
		#endif

		qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: startQThreadToShareAv failed"  )  );

		goto  errLabel;
	}
#endif


	//
	uiTaskType  =  CONST_imTaskType_shareMediaFile;

	//
	//  m_var.av.ucbSendLocalMediaFile  =  TRUE;	

	//  sizeAllControls_dlgTalk(  hDlg,  m_var,  NULL  );					//  µ÷ÕûÒ»ÏÂ²¼¾Ö

	if  (  initShareMediaFile(  pathCStr,  pQyMc->gui.hMainWnd,  iIndex_sharedObj,  &pSharedObj->pShareMediaObj  )  )  {
		qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: initShareMediaFile failed"  )  );
		goto  errLabel;
	}

	//  
	if  (  !bGetCapturePara_shareMediaFile(  (  MC_VAR_common  *  )pProcInfo,  iIndex_capAudio,  iIndex_capBmp,  pSharedObj->pShareMediaObj,  &pCapAudio->wf_org,  &pCapBmp->vh_org,  NULL  )  )  {
		qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: bGetCapturePara_shareMediaFile failed"  )  );
		goto  errLabel;
	}
		
	if  (  !bAudioOnly(  pSharedObj->pShareMediaObj  )  )  {
		//  2014/10/16
		if  (  pCapBmp->vh_org.bih.biCompression  ==  CONST_fourcc_YUY2  &&  pCapBmp->vh_org.bih.biBitCount  ==  16  )  ;
		else  if  (  pCapBmp->vh_org.bih.biCompression  ==  BI_RGB  &&  pCapBmp->vh_org.bih.biBitCount  ==  24  )  ;
		else  {
			  qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: vh_org err"  )  );
			  goto  errLabel;
		}
	}

	//  2011/08/08
	AV_COMPRESSOR_CFG	mediaFileCompressor;
	if  (  myGetAvCompressorCfg(  CONST_capType_mediaFile,  0,  0,  level,  &mediaFileCompressor  )  )  {
		qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: myGetAvCompressorCfg failed"  )  );
		goto  errLabel;
	}

	//
	if  (  !bAudioOnly(  pSharedObj->pShareMediaObj  )  )  {

		CAP_procInfo_mediaFileBmp	*	pVc  =  pCapBmp;

		//
		if  (  pVc->vh_org.bih.biCompression  !=  BI_RGB  ||  pVc->vh_org.bih.biBitCount  !=  24  )  {
			if  (  initOrg2RgbBuf(  (  MC_VAR_common  *  )pProcInfo,  (  CAP_procInfo_bmpCommon  *  )pVc  )  )  {
				traceLogA(  (char*)  "initOrg2RgbBuf failed."  );
				goto  errLabel;		
			}
		}

		QY_VIDEO_HEADER	*	pVh_rgb;
		pVh_rgb  =  pVc->bOrg2RgbBufInited  ?  &pVc->vh_rgb  :  &pVc->vh_org;

		//
		BITMAPINFO  *  pBmpInfo_input  =  (  BITMAPINFO  *  )pVh_rgb;	//  (  BITMAPINFO  *  )&pCapBmp->vh_org.bih;
		//
		//  2014/04/03
		mediaFileCompressor.video.common.pVideoQ2  =  &pCapBmp->thread.q2;
		mediaFileCompressor.video.common.pParent_transform  =  pCapBmp;
		//
		if  (  initCompressVideo(  pProcInfo,  pBmpInfo_input,  CONST_capType_mediaFile,  &mediaFileCompressor.video,  FALSE,  0,  pCompressVideo  )  )  {
			qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: initCompressVideo failed"  )  );
			//  qyShowHint(  _T(  "Initialize video compress failed!"  )  );  
			showNotification(  NULL,  0,  0,  0,  0,  0,  _T(  "Initialize video compress failed!"  )  );  
			goto  errLabel;
		}

		//  2014/10/17
		char  fourccStr_org[5  +  1];  fourccStr_org[0]  =  0;
		iFourcc2Str(  pVc->vh_org.bih.biCompression,  fourccStr_org,  mycountof(  fourccStr_org  )  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "w [%d], h [%d], org [%s],  sizeImg [%d]"  ),  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight, CQyString(  fourccStr_org  ),  pVc->vh_org.bih.biSizeImage  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "rgb [%d]"  ),  pVc->vh_rgb.bih.biSizeImage  );

	}

	if  (  !bNoAudio(  pSharedObj->pShareMediaObj  )  )  {
		AUDIO_COMPRESSOR_CFG	audioCompressor;
		if  (  mediaFileCompressor.audio.common.ucCompressors  ==  CONST_audioCompressors_acm  )  {
			memcpy(  &audioCompressor,  &mediaFileCompressor.audio,  sizeof(  audioCompressor  )  );
			}
		else  {
			  memset(  &audioCompressor,  0,  sizeof(  audioCompressor  )  );		
			  //  audioCompressor.ucCompressors  =  policyAv.mediaFileCompressor.audio.ucCompressors;
			  memcpy(  &audioCompressor,  &mediaFileCompressor.audio,  sizeof(  audioCompressor  )  );
			  memcpy(  &audioCompressor.wf_decompress_default,  &pCapAudio->wf_org,  sizeof(  audioCompressor.wf_decompress_default  )  );
			  //
			  memset(  &audioCompressor.wf_compress,  0,  sizeof(  audioCompressor.wf_compress  )  );	//  2011/02/02
			  audioCompressor.wf_compress.wFormatTag  =  mediaFileCompressor.audio.wf_compress.wFormatTag;
			  audioCompressor.wf_compress.nChannels  =  pCapAudio->wf_org.nChannels;
			  audioCompressor.wf_compress.nSamplesPerSec  =  pCapAudio->wf_org.nSamplesPerSec;
			  audioCompressor.wf_compress.wBitsPerSample  =  pCapAudio->wf_org.wBitsPerSample;
		}
		//
		//  2016/12/10
		AUDIO_COMPRESSOR_CFG  *  pCompressor  =  &audioCompressor;
		pCompressor->common.pAudioQ2  =  &pCapAudio->thread.q2;	
		pCompressor->common.pParent_transform  =  pCapAudio;
		//
		if  (  initCompressAudio(  pProcInfo,  &pCapAudio->wf_org,  &audioCompressor,  pCompressAudio  )  )  {
			qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: initCompressAudio failed"  )  );
			qyShowHint(  _T(  "Initialize audio compress failed!"  )  );  
			goto  errLabel;
		}
	}

	//
	pCapBmp->curhWnd  =  hDlg;
	
	if  (  bAudioOnly(  pSharedObj->pShareMediaObj  )  )  pCompressVideo  =  NULL;
	if  (  bNoAudio(  pSharedObj->pShareMediaObj  )  )  pCompressAudio  =  NULL;

	if  (  iWndContentType  ==  CONST_qyWndContentType_talker  )  {
		CHelp_getDlgTalkVar	help_getDlgTalkVar;
		DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlg  );
		if  (  !pDlgTalkVar  )  goto  errLabel;
		DLG_TALK_var  &  m_var  =  *pDlgTalkVar;

		//
		switch  (  m_var.addr.uiObjType  )  {
			case  CONST_objType_imGrp:				                 
				  //  if  (  old_procSendAvInfo(  pDlg->m_hWnd,  uiTaskType,  NULL,  NULL,  NULL,  pCompressVideo,  pCompressAudio,  iIndex_sharedObj,  pDlg  )  )  goto  errLabel;
				  //
				  //  2014/11/22		
				  unsigned  int  uiTranNo_avTask_starter;  uiTranNo_avTask_starter  =  0;
				  BOOL				bAvProxy;		bAvProxy  =  FALSE;
				  QY_MESSENGER_ID	idInfo_proxy;	memset(  &idInfo_proxy,  0,  sizeof(  idInfo_proxy  )  );
				  //
				  if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
					  if  (  m_var.av.taskInfo.bTaskExists
						  &&  !m_var.av.taskInfo.ucbStarter  )
					  {
						  //  2014/11/22
						  uiTranNo_avTask_starter  =  m_var.av.taskInfo.uiTranNo_org;

						  //
						  if  (  m_var.av.taskInfo.mosaicTrans.bExists_confMosaic  )  {
							  bAvProxy  =  TRUE;
							  //
							  idInfo_proxy.ui64Id  =  m_var.av.taskInfo.idInfo_starter.ui64Id;  
						  }
					  }

					  #ifdef  __DEBUG__
							  if  (  b__TEST_avProxy__(  )  )  {
									bAvProxy  =  TRUE;
									idInfo_proxy.ui64Id  =  103;
									showInfo_open0(  0,  0,  _T(  "For test: use 103 as idInfo_proxy"  )  );
									traceLog((TCHAR*)  _T(  "For test: bAvProxy is true"  )  );
									if  (  m_var.pMisCnt->idInfo.ui64Id  ==  103  )  {
										showInfo_open0(  0,  0,  _T(  "start media file failed. don't use 103 to start media file"  )  );
										goto  errLabel;
									}
							  }
					  #endif

					  //
					  if  (  bAvProxy  )  {
						  QY_MESSENGER_ID  content_idInfo_logicalPeer;
						  content_idInfo_logicalPeer.ui64Id  =  m_var.addr.idInfo.ui64Id;
						  
						  MSGR_ADDR		addr;						  
						  memset(  &addr,  0,  sizeof(  addr  )  );
						  lstrcpyn(  addr.misServName,  m_var.pMisCnt->cfg.misServName,  mycountof(  addr.misServName  )  );
						  addr.idInfo.ui64Id  =  idInfo_proxy.ui64Id;
  
						  if  (  procSendAvInfo(  m_var.pMisCnt,  hDlg,  TRUE,  uiTaskType,  pCompressVideo,  pCompressAudio,  iIndex_sharedObj,  iIndex_sharedObjUsr,  NULL,  &content_idInfo_logicalPeer,  uiTranNo_avTask_starter,  NULL,  &addr  )  )  {
							  qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: procSendAvInfo failed"  )  );
							  goto  errLabel;				  
						  }
						  //
						  break;
					  }
				  }
				  //
				  PARAM_startAvCall param; memset(&param, 0, sizeof(param));;
				  if  (  procSendAvInfo(  m_var.pMisCnt,  hDlg,  TRUE,  uiTaskType,  &param, pCompressVideo,  pCompressAudio,  iIndex_sharedObj,  iIndex_sharedObjUsr,  NULL,  NULL,  NULL,  &m_var.addr,  NULL  )  )  {
					  qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: procSendAvInfo failed"  )  );
					  goto  errLabel;
				  }
				  break;
			case  CONST_objType_tmpGrp:
				  traceLogA(  (char*)  ""  );
				  goto  errLabel;
				  break;
			default: 
				    //				   
				PARAM_startAvCall  tmpParam;  memset(&tmpParam, 0, sizeof(tmpParam));
				    //  if  (  old_procSendAvInfo(  pDlg->m_hWnd,  uiTaskType,  NULL,  NULL,  NULL,  pCompressVideo,  pCompressAudio,  iIndex_sharedObj,  pDlg  )  )  goto  errLabel;					
				    if  (  procSendAvInfo(  m_var.pMisCnt,  hDlg,  TRUE,  uiTaskType,  &tmpParam,pCompressVideo,  pCompressAudio,  iIndex_sharedObj,  iIndex_sharedObjUsr,  NULL,  NULL,  NULL,  &m_var.addr,  NULL  )  )  {
						qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: procSendAvInfo failed"  )  );
						goto  errLabel;					
					}
					break;	
		}
		}
	else  {  //  2013/10/04
		  SHARED_OBJ_USR	*	pSharedObjUsr			=	NULL;
		  			
		  pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  iIndex_sharedObjUsr  );
		  if  (  !pSharedObjUsr  )  goto  errLabel;
		  //
		  if  (  pCompressAudio  &&  pCompressAudio->uiTranNo_openAvDev_org  )  {
			  pSharedObjUsr->uiTranNo_openAvDev_a  =  pCompressAudio->uiTranNo_openAvDev_org  +  iIndex_sharedObjUsr;	//  pSharedObj->iIndex_curUsr;
		  }
		  if  (  pCompressVideo  &&  pCompressVideo->uiTranNo_openAvDev_org  )  {	//  
			  pSharedObjUsr->uiTranNo_openAvDev_v  =  pCompressVideo->uiTranNo_openAvDev_org  +  iIndex_sharedObjUsr;	//  pSharedObj->iIndex_curUsr;
		  }
	}

	//  2010/09/09
	setCurSharedObjUsr(  pProcInfo,  iIndex_sharedObj, iIndex_sharedObjUsr);
	//  2014/11/16
	pProcInfo->setFlg_inConfMosaic(  hDlg,  iWndContentType,  iIndex_sharedObj,  iIndex_sharedObjUsr  );

	//  2009/12/07	
#if  0
	GENERIC_Q_CFG		tmpCfg;
	DWORD	dwThreadDaemonId;
	TCHAR	tName[128];

	if  (  !bNoAudio(  pSharedObj->pShareMediaObj  )  )  {
		//
		memcpy(  &tmpCfg,  &pProcInfo->cfg.toShareAudioQ,  sizeof(  tmpCfg  )  );
		_sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-%d"  ),  tmpCfg.name,  pSharedObj->uiTranNo  );
		_sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-%d"  ),  tmpCfg.mutexName_prefix,  pSharedObj->uiTranNo  );
		_sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s%u"  ),  CONST_evtName_qm_data_a,  pSharedObj->uiTranNo  );
		if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapAudio->thread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myPLAY_AUDIO_DATA,  &pCapAudio->thread.q2  )  )  {
			qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: initQyQ2 audio failed"  )  );
			goto  errLabel;
		}
		pCapAudio->thread.bQInited  =  TRUE;

		//
		if  (  !pCapAudio->thread.hThread  )  {
			//
			pCapAudio->thread.bQuit  =  FALSE;			
			pCapAudio->thread.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_toShareAudio,  (  LPVOID  )iIndex_sharedObj,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
			if  (  !pCapAudio->thread.hThread  )  {
				qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: createThread audio failed"  )  );
				goto  errLabel;					
			}
			pCapAudio->thread.dwThreadId  =  dwThreadDaemonId;			
			if  (  ResumeThread(  pCapAudio->thread.hThread  )  ==  -1  )  {
				qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: resumeThread audio failed"  )  );
				goto  errLabel;									 
			}
		}
	}
#endif
#if  0  //  2015/10/11
	BOOL  bAudio  =  bNoAudio(  pSharedObj->pShareMediaObj  );
	//
	if  (  startQThreadToShareAv(  pProcInfo,  iIndex_sharedObj,  bAudio  )  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "doCmd_startShareMediaFile, startQThreadToShareAv failed"  )  );
		#endif

		qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: startQThreadToShareAv failed"  )  );

		goto  errLabel;
	}
#endif

	//
	if  (  runShareMediaFile(  pSharedObj->pShareMediaObj  )  )  {
		qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: runShareMediaFile failed"  )  );
		goto  errLabel;
	}
#if  0
	pShmCmd->psCurrent  =  getShareMediaFileState(  pSharedObj->pShareMediaObj  );
#endif
	
#if  0
	TCHAR	tBuf[255  +  1]	=	_T(  ""  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\n %s"  ),  m_var.peerDesc,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_howToEnlarge  )  );
	SetDlgItemText(  hDlg,  m_var.guiData.iIDC_STATIC_peerDesc,  tBuf  );
#endif

#ifdef  __APP_qyMc_touchscreen__
		#if  0
			//pShmCmd->bLooping  =  TRUE;
			traceLog((TCHAR*)  _T(  "doCmd_startShareMediaFile: bLooping is TRUE for touchscreen"  )  );
		#endif
#endif

#ifdef  __DEBUG__
		#if  0
			pShmCmd->bLooping  =  TRUE;
			traceLog((TCHAR*)  _T(  "doCmd_startShareMediaFile: bLooping is TRUE for debug"  )  );
		#endif
#endif

	//  2012/11/06
	//pShmCmd->bLooping  =  pProcInfo->cfg.policy.ucbLooping_mediaFile;

	//  2013/10/04
#if 0
	if  (  iWndContentType  ==  CONST_qyWndContentType_consoleWall  )  {
		pShmCmd->bLooping  =  TRUE;
		pShmCmd->bGlobalMute  =  TRUE;
	}
#endif

	//
	iErr  =  0;

errLabel:
	
	//  2013/03/01
	if  (  iWndContentType  ==  CONST_qyWndContentType_talker  )  {	
		//  sizeAllControls_dlgTalk(  hDlg,  m_var,  NULL  );					//  µ÷ÕûÒ»ÏÂ²¼¾Ö
		askToRefreshLayout_mgr(  hDlg  );
	}

	if  (  !iErr  )  {
		if  (  piIndex_sharedObj  )  *piIndex_sharedObj  =  iIndex_sharedObj;
		if  (  piIndex_sharedObjUsr  )  *piIndex_sharedObjUsr  =  iIndex_sharedObjUsr;
	}

	qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "shareMediaFile: leaves with %s"  ),  iErr  ?  _T(  "Failed"  )  :  _T(  "OK"  )  );

	return  iErr;
				  
}




 int  doCmd_startShareMediaDevice(  QY_MC  *  pQyMc,  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  unsigned  int  uiSubCapType,  int  level,  void  **  ppCapStuff  )
{
	int		iErr	=	-1;
	//QY_MC* pQyMc = QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

	//  2014/11/24
	int  iWndContentType  =  CONST_qyWndContentType_talker;

	//
	DLG_TALK_var  &  m_var  =  *(  DLG_TALK_var  *  )pDLG_TALK_var;

	//
	//
	if (!m_var.av.taskInfo.bTaskExists) {
		showInfo_open0(0, 0, _T("shareMediaDevice failed, av.taskinfo.bTaskExists is false"));
		return  -1;
	}

	//	
	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, m_var.av.taskInfo.iIndex_taskInfo);
	if (!pTaskInfo)  goto  errLabel;
	if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  goto  errLabel;
	QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;

	//
	if (pTc->shareMediaDevice.bTaskExists) {
		showInfo_open0(0, 0, _T("shareMediaDevice failed, shareMediaDevice.bTaskExists already true"));
		goto  errLabel;
	}


	//
	int								iIndex_sharedObj;
	int								iIndex_sharedObjUsr		=	0;
	QY_SHARED_OBJ				*	pSharedObj				=	NULL;
	int								iIndex_capBmp;
	CAP_procInfo_mediaDeviceBmp	*	pCapBmp					=	NULL;
	COMPRESS_VIDEO				*	pCompressVideo			=	NULL;
	int								iIndex_capAudio;
	CAP_procInfo_mediaDeviceAudio	*	pCapAudio				=	NULL;
	COMPRESS_AUDIO				*	pCompressAudio			=	NULL;
	//
#if  0
	int								iIndex_shmCmd;
	QM_SHM_CMD					*	pShmCmd					=	NULL;
#endif
	unsigned  int					uiTaskType;
	unsigned  int					uiCapType				=	CONST_capType_mediaDevice;


	#ifdef  __DEBUG__
			traceLog((TCHAR*)  _T(  "doCmd_startShareMediaDevice: "  )  );
	#endif


	iIndex_sharedObj  =  newSharedObjIndex(  pProcInfo,  hDlgTalk,  CONST_sharedObjType_mediaDevice,  &iIndex_sharedObjUsr,  NULL  );
	if  (  iIndex_sharedObj  <  0  )  goto  errLabel;
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	//pSharedObj->uiType  =  CONST_sharedObjType_mediaDevice;
	iIndex_capBmp  =  newCapProcInfoBmpIndex(  pProcInfo,  iIndex_sharedObj  );
	pCapBmp  =  (  CAP_procInfo_mediaDeviceBmp  *  )getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );
	if  (  !pCapBmp  )  goto  errLabel;
	pCapBmp->uiType  =  uiCapType;
	pCapBmp->iIndex_sharedObj  =  iIndex_sharedObj;
	pCapBmp->uiTranNo_sharedObj  =  pSharedObj->uiTranNo;
	pCompressVideo  =  &pCapBmp->compressVideo;
	iIndex_capAudio  =  newCapProcInfoAudioIndex(  pProcInfo,  iIndex_sharedObj  );
	pCapAudio  =  (  CAP_procInfo_mediaDeviceAudio  *  )getCapAudioBySth(  pProcInfo,  iIndex_capAudio,  0  );
	if  (  !pCapAudio  )  goto  errLabel;
	pCapAudio->uiType  =  uiCapType;
	pCapAudio->iIndex_sharedObj  =  iIndex_sharedObj;
	pCapAudio->uiTranNo_sharedObj  =  pSharedObj->uiTranNo;
	pCompressAudio  =  &pCapAudio->compressAudio;
	//
#if  0
	iIndex_shmCmd  =  newShmCmdIndex(  pProcInfo,  iIndex_sharedObj  );
	pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  iIndex_shmCmd  );
	if  (  !pShmCmd  )  goto  errLabel;		    
#endif
	//
	pSharedObj->iIndex_capBmp  =  iIndex_capBmp;
	pSharedObj->iIndex_capAudio  =  iIndex_capAudio;
	//
	//pSharedObj->iIndex_shmCmd  =  iIndex_shmCmd;



	//  2009/12/07	
	if  (  newstartQThreadToShareAv(  pProcInfo,  iIndex_sharedObj,  TRUE  )  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "doCmd_startShareMediaDevice, startQThreadToShareAv failed"  )  );
		#endif
		goto  errLabel;
	}


	//
	uiTaskType  =  CONST_imTaskType_shareMediaFile;
	//  2015/03/11
	TASK_av_props  taskAvProps; 
	memset(  &taskAvProps,  0,  sizeof(  taskAvProps  )  );
	//
	if  (  uiSubCapType  ==  CONST_subCapType_unresizable  )  {
		taskAvProps.v.ucAvFlg  |=  CONST_avFlg_unresizable;
	}
	//
	pSharedObj->taskAvProps = taskAvProps;

	//
	//  m_var.av.ucbSendLocalMediaFile  =  TRUE;	

	//  sizeAllControls_dlgTalk(  hDlg,  m_var,  NULL  );					//  µ÷ÕûÒ»ÏÂ²¼¾Ö

	//  2011/08/08
	AV_COMPRESSOR_CFG		mediaDeviceCompressor;
	if  (  myGetAvCompressorCfg(  CONST_capType_mediaDevice,  uiSubCapType,  0,  level,  &mediaDeviceCompressor  )  )  goto  errLabel;

	AV_COMPRESSOR_CFG	*	pCompressor  =  &mediaDeviceCompressor;
	//
	refreshWebCamSettings(  &pCompressor->video,  pCapBmp  );

	//
	int  conf_iFourcc = get_conf_iFourcc();
	//
	conf_iFourcc = fourccStr2i(pTc->videoConference.activeMems_from[0].avStream.obj.tranInfo.video.compressor.common.fourccStr);
	//
	int conf_bitrateInKbps = 0;
	//
	set_conf_iFourcc(conf_iFourcc, conf_bitrateInKbps, pCompressor);
	//
	pCompressor->video.common.usMaxFps_toShareBmp = min(pCompressor->video.common.usMaxFps_toShareBmp, CONST_fps_shareMediaDevice);


	//
	BOOL	bAudio  =  CAP_STUFF_bAudio(  *ppCapStuff  );
	BOOL	bVideo  =  CAP_STUFF_bVideo(  *ppCapStuff  );

	//
	if  (  initShareMediaDevice(  ppCapStuff,  &pCompressor->audio,  &pCapBmp->policy.bih,  pQyMc->gui.hMainWnd,  iIndex_sharedObj,  &pSharedObj->pShareMediaObj  )  )  goto  errLabel;
	//  pCapBmp->bCapDevConnected  =  TRUE;	//  2012/02/24

	//  
	if  (  !bGetCapturePara_shareMediaDevice(  (  MC_VAR_common  *  )pProcInfo,  iIndex_capAudio,  iIndex_capBmp,  pSharedObj->pShareMediaObj,  &pCapAudio->wf_org,  &pCapBmp->vh_org,  NULL  )  )  goto  errLabel;

	//
	if  (  bVideo  )  {
		CAP_procInfo_mediaDeviceBmp	*	pVc  =  pCapBmp;

		//
		if  (  pVc->vh_org.bih.biCompression  !=  BI_RGB  ||  pVc->vh_org.bih.biBitCount  !=  24  )  {
			if  (  initOrg2RgbBuf(  (  MC_VAR_common  *  )pProcInfo,  (  CAP_procInfo_bmpCommon  *  )pVc  )  )  {
				traceLogA(  (char*)  "initOrg2RgbBuf failed."  );
				goto  errLabel;		
			}
		}

		QY_VIDEO_HEADER	*	pVh_rgb;
		pVh_rgb  =  pVc->bOrg2RgbBufInited  ?  &pVc->vh_rgb  :  &pVc->vh_org;
		//
		//  2014/04/03
		pCompressor->video.common.pVideoQ2  =  &pVc->thread.q2;
		pCompressor->video.common.pParent_transform  =  pVc;
		//
		if  (  initCompressVideo(  pProcInfo,  (  BITMAPINFO  *  )&pVh_rgb->bih,  uiCapType,  &pCompressor->video,  FALSE,  0,  pCompressVideo  )  )  {
			showNotification(  NULL,  0,  0,  0,  0,  0,  _T(  "Initialize video compress failed!"  )  );  
			goto  errLabel;
		}
	}

	if  (  bAudio  )  {
		AUDIO_COMPRESSOR_CFG	audioCompressor;
		if  (  pCompressor->audio.common.ucCompressors  ==  CONST_audioCompressors_acm  )  {
			memcpy(  &audioCompressor,  &pCompressor->audio,  sizeof(  audioCompressor  )  );
			}
		else  {
			  memset(  &audioCompressor,  0,  sizeof(  audioCompressor  )  );		
			  //  audioCompressor.ucCompressors  =  pCompressor->audio.ucCompressors;
			  memcpy(  &audioCompressor,  &pCompressor->audio,  sizeof(  audioCompressor  )  );
			  memcpy(  &audioCompressor.wf_decompress_default,  &pCapAudio->wf_org,  sizeof(  audioCompressor.wf_decompress_default  )  );
			  //
			  memset(  &audioCompressor.wf_compress,  0,  sizeof(  audioCompressor.wf_compress  )  );	//  2011/02/02
			  audioCompressor.wf_compress.wFormatTag  =  pCompressor->audio.wf_compress.wFormatTag;
			  audioCompressor.wf_compress.nChannels  =  pCapAudio->wf_org.nChannels;
			  audioCompressor.wf_compress.nSamplesPerSec  =  pCapAudio->wf_org.nSamplesPerSec;
			  audioCompressor.wf_compress.wBitsPerSample  =  pCapAudio->wf_org.wBitsPerSample;
		}
		//
		//  2016/12/10
		AUDIO_COMPRESSOR_CFG  *  pCompressor  =  &audioCompressor;	
		pCompressor->common.pAudioQ2  =  &pCapAudio->thread.q2;	
		pCompressor->common.pParent_transform  =  pCapAudio;
		//
		if  (  initCompressAudio(  pProcInfo,  &pCapAudio->wf_org,  &audioCompressor,  pCompressAudio  )  )  {
			showNotification(  NULL,  0,  0,  0,  0,  0,  _T(  "Initialize audio compress failed!"  )  );  
			goto  errLabel;
		}
	}

	//
	pCapBmp->curhWnd  =  hDlgTalk;
	
	if  (  !bVideo  )  pCompressVideo  =  NULL;
	if  (  !bAudio  )  pCompressAudio  =  NULL;

	//
	int  iTaskId = 0;
	iTaskId = m_var.av.taskInfo.iTaskId;

	//
	SHARED_OBJ_USR* pSharedObjUsr;
	pSharedObjUsr = getSharedObjUsr(pSharedObj, iIndex_sharedObjUsr);
	if (!pSharedObjUsr)  goto  errLabel;
	//	
	
	if  (  pCompressAudio  &&  pCompressAudio->uiTranNo_openAvDev_org  )  {
		pSharedObjUsr->uiTranNo_openAvDev_a  =  pCompressAudio->uiTranNo_openAvDev_org  +  iIndex_sharedObjUsr;	//  pSharedObj->iIndex_curUsr;
	}
		
	if (pCompressVideo && pCompressVideo->uiTranNo_openAvDev_org) {	//  
		pSharedObjUsr->uiTranNo_openAvDev_v = pCompressVideo->uiTranNo_openAvDev_org + iIndex_sharedObjUsr;	//  pSharedObj->iIndex_curUsr;
	}
	pSharedObjUsr->iTaskId = iTaskId;



	//
	if (pTc->shareMediaDevice.bTaskExists)  goto  errLabel;
	memset(&pTc->shareMediaDevice, 0, sizeof(pTc->shareMediaDevice));
	pTc->shareMediaDevice.index_sharedObj = iIndex_sharedObj;
	pTc->shareMediaDevice.bTaskExists = true;


	//  2010/09/09
	setCurSharedObjUsr(  pProcInfo,  iIndex_sharedObj, iIndex_sharedObjUsr);

	//  2014/11/16
	pProcInfo->setFlg_inConfMosaic(  hDlgTalk,  iWndContentType,  iIndex_sharedObj,  iIndex_sharedObjUsr  );

	//
	if (m_var.av.taskInfo.ucbStarter) {
		goto  errLabel;
	}


	//  2014/11/14
	chkResources(hDlgTalk, FALSE);

	//
	QY_MESSENGER_ID  idInfo_dst;
	if (m_var.av.taskInfo.ucbStarter) {
		if (!m_var.av.taskInfo.ucbVideoConference) {
			idInfo_dst = m_var.addr.idInfo;
			pProcInfo->sendConfKey(hDlgTalk, idInfo_dst, _T("doCmd_startShareScreen"));
		}
	}
	else {  //
		  //
		confOthers_requestToSpeak(hDlgTalk, iIndex_sharedObj, mynull, true);
	}




	//  2011/03/12
	dlgTalk_displayAvStatus(hDlgTalk, m_var, 0, 0, 0);




	//
	if  (  runShareMediaDevice(  pSharedObj->pShareMediaObj  )  )  goto  errLabel;
	
	//
	iErr  =  0;

errLabel:

	//  2013/03/01
	//  sizeAllControls_dlgTalk(  hDlg,  m_var,  NULL  );					//  µ÷ÕûÒ»ÏÂ²¼¾Ö
	askToRefreshLayout_mgr(  hDlgTalk  );

	return  iErr;
				  
}


 //  2007/09/08, ¼¤»î´°¿Ú¸ÄÎª²»ÇÀÊó±êµÄÄ£Ê½  
 int  activateWnd(  HWND  hDlgTalk,  DLG_TALK_var  &  m_var  )
{
	 CCtxQyMc* pQyMc = g_pQyMc;
	 CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

#if  0
	if  (  m_var.bNeedNotShowWnd  )  {
		ShowWindow(  hDlgTalk,  SW_SHOW  );
		m_var.bNeedNotShowWnd  =  FALSE;
	}
#else
	if  (  m_var.guiData.param.bNeedNotShowWnd  )  return  0;
#endif

#ifdef  __WINCE__
		return  0;
#else
	/*
	HWND		hForeWnd	=	NULL;
	DWORD		dwForeId	=	0;
	DWORD		dwCurId		=	0;
	*/
	#ifdef  __DEBUG__
			//  traceLogA(  (char*)  "activateWnd called"  );
	#endif
	
	if  (  !hDlgTalk  )  return  -1;

	//
	if (!pProcInfo->bAppQt()) {

		FLASHWINFO	f;

		memset(&f, 0, sizeof(f));
		f.cbSize = sizeof(f);
		f.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
		f.hwnd = hDlgTalk;

		FlashWindowEx(&f);
	}

	//  2007/09/09, ÎªÁË±£Ö¤ÖÐ¹úÈËÃñ°ì¹«µÄ°²¾², ÔÝÊ±ÏÈ°ÑµÛ¹úÖ÷Òå¿ª·¢µÄapi -- MessageBeep ¸ø¹ØÉÏ. ºóÃæÓÃÏÈ½øµÄ¿ª¹Ø½øÐÐ¹ÜÀí,·ÀÖ¹µÛ¹úÖ÷ÒåµÄµ·ÂÒ.
	//
	//  MessageBeep(  MB_OK  );

	return  0;
#endif
}

 


#ifdef  __NOTSUPPORT_DB__

 int  tmpHandler_loadTasks_ce(  void  *  p0,  void  *  p1,  MIS_MSGU  *  pMsg  )
{
	int					iErr		=	-1;
	HWND				hDlgTalk	=	(  HWND  )p0;
	DLG_TALK_var	*	pVar		=	(  DLG_TALK_var  *  )p1;

	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MIS_CNT			*	pMisCnt		=	NULL;
	IM_CONTENTU		*	pContent	=	NULL;

	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_talk:
				   pMisCnt  =  (  MIS_CNT  *  )pMsg->talk.pMisCnt;
				   pContent  =  (  IM_CONTENTU  *  )pMsg->talk.data.buf;

				   if  (  (  pMsg->talk.data.route.idInfo_from.ui64Id  ==  pVar->addr.idInfo.ui64Id
					   &&  pMsg->talk.data.route.idInfo_to.ui64Id  ==  pMisCnt->idInfo.ui64Id  )
					   ||  (  pMsg->talk.data.route.idInfo_to.ui64Id  ==  pVar->addr.idInfo.ui64Id  
					   &&  pMsg->talk.data.route.idInfo_from.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  
					   )
				   {
					   qPostMsg(  pMsg,  offsetof(  MIS_MSG_TALK,  data  )  +  pMsg->talk.lenInBytes,  &pVar->m_processQ  );
				   }
				   break;

			case  CONST_misMsgType_task:	
				   pMisCnt  =  (  MIS_CNT  *  )pMsg->task.pMisCnt;
				   pContent  =  (  IM_CONTENTU  *  )pMsg->task.data.buf;

				   if  (  (  pMsg->task.data.route.idInfo_from.ui64Id  ==  pVar->addr.idInfo.ui64Id
					   &&  pMsg->task.data.route.idInfo_to.ui64Id  ==  pMisCnt->idInfo.ui64Id  )
					   ||  (  pMsg->task.data.route.idInfo_to.ui64Id  ==  pVar->addr.idInfo.ui64Id  
					   &&  pMsg->task.data.route.idInfo_from.ui64Id  ==  pMisCnt->idInfo.ui64Id  )
					   )
				   {

					   CE_TASK_MEM	taskMem;
					   if  (  getCeTaskMem(  NULL,  pQyMc->cfg.db.iDbType,  pMisCnt,  NULL,  0,  0,  pMsg->task.iTaskId,  &taskMem  )  )  break;
					   if  (  !bTaskAlive(  taskMem.iStatus  )  )  break;

					   qPostMsg(  pMsg,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsg->task.lenInBytes,  &pVar->m_processQ  );
				   }
				  break;

			default:
						break;
	}

	//  qPostMsg(  

	return  0;
 }

#endif


 int  dlgTalk_loadTasks(  QY_MC  *  pQyMc,  HWND  hDlgTalk,  DLG_TALK_var  &  m_var  )
{

#ifdef  __NOTSUPPORT_DB__

		MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );

		qTraverse(  &pProcInfo->imMsgLogQ,  (  PF_commonHandler  )tmpHandler_loadTasks_ce,  hDlgTalk,  &m_var  );

		//
		PARAM_PROC_ROW	param;
		memset(  &param,  0,  sizeof(  param  )  );
		param.bScrollIntoView  =  TRUE;													//  ÕâÀïÒª×¢Òâ£ºÒòÎª
		param.bNewMsg  =  TRUE;		
		qTraverse(  &m_var.m_processQ, tmpHandler_showMsg,  hDlgTalk,  &param  );				//  2007/08/13£¬ÕâÀïÒª×¢Òâ£ºÒªÏÈÏÔÊ¾¶ÓÁÐ£¬ÔÙÏÔÊ¾¿âÀïµÄÈÎÎñ¡£ÒòÎªµ±¿âÀïµÄÈÎÎñºÍ¶ÓÁÐµÄÈÎÎñÖØÊ±£¬ÎªÁË±£Ö¤ÏÔÊ¾µÄ×¼È·ÐÔ£¬Ö»ÄÜÏÔÊ¾Ò»¸ö¡£µ«ÊÇ¶ÓÁÐÀïµÄÏûÏ¢ÊÇÒª¼ÇÂ¼µÄ£¬¿âÀï¶ÁÈ¡µÄÊÇ²»¼ÇÂ¼µÄ

#ifdef  __DEBUG__
		printQ_mis(  &m_var.m_processQ,  0  );
#endif

	    return  0;
#else
	int					iErr										=	-1;
	//QY_MC			*	pQyMc										=	QY_GET_GBUF(  );
	CQnmDb				db;
	char				idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";
#if  0
	TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]			=	_T(  ""  );
	char				idStr_me[CONST_qyMessengerIdStrLen  +  1]	=	"";
	CDBVariant			varVals[15];
#endif
	int					tmpiRet										=	-1;
	//  CWnd			*	pDlgTalk									=	CWnd::FromHandle(  hDlgTalk  );
	//  if  (  !pDlgTalk  )  return  -1;
	//  CListCtrl		*	pListCtrl									=	(  CListCtrl  *  )pDlgTalk->GetDlgItem(  m_var.idcList_task  );
#if  0
	HWND				hListCtrl									=	GetDlgItem(  hDlgTalk,  m_var.msgToolCommon.idcList_task  );
	if  (  !hListCtrl  )  return  -1;
#endif
	PARAM_PROC_ROW		param;
	CQySyncObj			syncObj;

	if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  return  -1;
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	idInfo2Str(  &m_var.addr.idInfo,  idStr,  mycountof(  idStr  )  );
#if  0
	idInfo2Str(  &m_var.pMisCnt->idInfo,  idStr_me,  mycountof(  idStr_me  )  );	//  2009/09/08
#endif
	traceLogA(  (char*)  "displayTasks: usMaxDisplayedTasks %d",  m_var.usMaxDisplayedTasks  );

	if  (  syncObj.sync(  CQyString(  m_var.pMisCnt->cfg.mutexNamePrefix_syncTask  )  +  idStr  )  )  goto  errLabel;

	memset(  &param,  0,  sizeof(  param  )  );
	param.bAddOnRowIndex  =  TRUE;	//  2007/07/12
		
	tmpiRet  =  g_dbFuncs.pf_selectImTask_dlgTalk_loadTasks(  hDlgTalk,  &param,  db.m_pDbMem->pDb  );

	//  if  (  pListCtrl->GetItemCount(  )  >  0  )  
#if  0
	if  (  myListCtrl_GetItemCount(  hListCtrl  )  >  0  )
	{
		int		nItem  =  0;
		//
		//  pListCtrl->SetItemState(  nItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
		myListCtrl_SetItemState(  hListCtrl,  nItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
		//  pListCtrl->Update(  nItem  );
		myListCtrl_Update(  hListCtrl,  nItem  );
		//
		//  pListCtrl->GetItemText(  nItem,  CONST_nSubItem_rowId_cur,  param.rowIdStr,  mycountof(  param.rowIdStr  )  );
		myListCtrl_GetItemText(  hListCtrl,  nItem,  CONST_nSubItem_rowId_cur,  param.rowIdStr,  mycountof(  param.rowIdStr  )  );
		activateRowByRowId(  hDlgTalk,  param.rowIdStr  );

	}
#endif

	//  

	iErr  =  0;
errLabel:
	return  iErr;
#endif
}

 

 int  dlgTalk_chkInvalidTaskInMosaic(  QY_MC  *  pQyMc,  HWND  hDlgTalk , DLG_TALK_var  &  m_var,  MIS_MSG_TASK  *  pMsgTask  )
 {
	 int  iErr  =  -1;
	 //QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 BOOL  bNeedChk  =  FALSE;
	 IM_CONTENTU	*	pContent	=	(  IM_CONTENTU  *  )pMsgTask->data.buf;	
	 TCHAR  tBuf[128]  =  _T(  ""  );
	 
	 if  (  !pMsgTask->iTaskId  )  return  -1;
	 if  (  !bTaskAlive(  pMsgTask->iStatus  )  )  return  -1;

#if  0
	 if  (  m_var.av.taskInfo.bTaskExists  &&  m_var.av.taskInfo.ucbVideoConference  &&  m_var.av.taskInfo.ucbStarter	
		 &&  m_var.av.taskInfo.mosaicMaker.video.resObj.uiObjType  )
	 {
		switch  (  pContent->uiType  )  {
				 case  CONST_imCommType_transferAvInfo:  
					   bNeedChk  =  TRUE;
					   break;
				 default:
						break;
		}
	 }
	 if  (  !bNeedChk  )  {
		 iErr  =  0;  goto  errLabel;
	 }
	 
	 TRANSFER_AV_INFO  *  pTransferAvInfo  =  &pContent->transferAvInfo;

	 //
	 if  (  pMsgTask->data.route.idInfo_from.ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  )  {
		 if  (  pMsgTask->iTaskId  ==  m_var.av.taskInfo.iTaskId  )  {
			 iErr  =  0;  goto  errLabel;
		 }
		 PROC_TASK_AV  *  pTask  =  get_transferAvInfo_pTask(  pTransferAvInfo,  _T(  ""  )  );
		 if  (  !pTask  )  goto  errLabel;
		 int  iIndex_sharedObj  =  pTask->iIndex_sharedObj;
		 QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex( pProcInfo, iIndex_sharedObj  );
		 if  (  !pSharedObj  )  goto  errLabel;
		 SHARED_OBJ_USR  *  pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  pTask->iIndex_sharedObjUsr  );
		 if  (  !pSharedObjUsr  )  goto  errLabel;
		 if  (  pSharedObjUsr->hWnd_starter  !=  hDlgTalk  )  goto  errLabel;
		 //
		 if  (  !pSharedObjUsr->ucbInConfMosaic  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsgTask->uiTaskType  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hintToStopScreensharing  )  );			//  _T(  "from me cannot join in conference, cancel it please"  )  );
			 showNotification(  m_var.pMisCnt,  &m_var.addr.idInfo,  0,  0,  0,  0,  tBuf  );
		 }

		 }
	 else  {
		   if  (  !pTransferAvInfo->uiTranNo_avTask_starter  )  {
			   //  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s from %I64u cannot join in conference, cancel it please"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsgTask->uiTaskType  ),  pMsgTask->data.route.idInfo_from.ui64Id  );
			   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u %s %s"  ),  pMsgTask->data.route.idInfo_from.ui64Id,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsgTask->uiTaskType  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hintToStopScreensharing  )  );			//  _T(  "from me cannot join in conference, cancel it please"  )  );
			   showNotification(  m_var.pMisCnt,  &m_var.addr.idInfo,  0,  0,  0,  0,  tBuf  );		 
			   }
		   else  {
			     int  i;
				 i  =  0;
		   }
	 }
#endif

	 iErr  =  0;
errLabel:

	 return  iErr;

 }


 //
 int  dlgTalk_chkRecvdTasks(  HWND  hDlgTalk,  DLG_TALK_var  &  m_var  )
{
	int					iErr					=	-1;
	CCtxQyMc* pQyMc = g_pQyMc;
	MC_VAR_isCli	*	pProcInfo				=	QY_GET_procInfo_isCli(  );
	Q_NODE			*	pQNode					=	NULL;
	
	//					   	
	int					nElapseInS				=	MAX_nElapseInS;	//  20;					   
	int					nTimeoutInS				=	MAX_nTimeoutInS;	//  65;

	//
	BOOL				bNeedChkRecvdTasks		=  FALSE;

	//
	if  (  !m_var.m_pProcessQ  )  return  -1;
	GENERIC_Q	&	m_processQ	=	*m_var.m_pProcessQ;

	TCHAR  tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "dlgTalk_chkRecvdTasks %I64u called"  ),  m_var.addr.idInfo.ui64Id  );
#ifdef  __DEBUG__
		if  (  pProcInfo->cfg.debugStatusInfo.bDbgDetail){
			traceLog((TCHAR*)  tBuf  );
		}
#endif
		//showInfo_open0(  0,  0,  tBuf  );

		//  2016/02/29
		BOOL  bWaitingTo_beRe_accepted  =  FALSE;
		BOOL  bChanged_taskList  =  FALSE;

	//
	for  (  pQNode  =  m_processQ.front.pNext;  pQNode;  pQNode  =  pQNode->pNext  )  {
		 MIS_MSGU  *  pMsg1  =  (  MIS_MSGU  *  )pQNode->qElemMemory.m_pBuf;
		 if  (  pMsg1->uiType  !=  CONST_misMsgType_task  )  continue;
		 if  (  !pMsg1->task.iTaskId  )  continue;

		 //
		 int  index_taskInfo  =  getQmcTaskInfoIndexBySth(  pProcInfo,  pMsg1->task.iTaskId  );
		 QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  index_taskInfo  );
		 if  (  !pTaskInfo  )  continue;
		 			 
		 //
		 MIS_MSGU		*	pMsg					=	&pTaskInfo->var.pTaskData->msgU;
		 if  (  pMsg->uiType  !=  CONST_misMsgType_task  )  continue;

		 //
		 IM_CONTENTU	*	pContent	=	(  IM_CONTENTU  *  )pMsg->task.data.buf;

		 //
		 if  (  !bTaskAlive(  pMsg->task.iStatus  )  )  {
			 
			 //  2016/02/29
			 if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
#if  0
				 PROC_TASK_AV  *  pTask  =  get_transferAvInfo_pTask(  &pContent->transferAvInfo,  _T(  ""  )  );
				 if  (  !pTask  )  goto  errLabel;
				 if  (  pTask->canceledTask_status.bWaitingTo_beRe_accepted  )  {
					 int  iDiffInMs  =  GetTickCount(  )  -  pTask->canceledTask_status.dwTickCnt_recentlyRefreshed;
					 if  (  abs(  iDiffInMs  )  >  CONST_intervalInMs_task_screenAndMediaFile_re_accept  )  {
						 pTask->canceledTask_status.bWaitingTo_beRe_accepted  =  FALSE;
						 //
						 bChanged_taskList  =  TRUE;
						}
					 else  {
						   bWaitingTo_beRe_accepted  =  TRUE;						   
					 }
				 }
#endif
			 }
			 //
			 continue;
		 }
	 
		 switch  (  pContent->uiType  )  {
				 case  CONST_imCommType_transferAvInfo:  {
					   CAP_IMAGES	*	pImgs		=  &m_var.av.peerZone.images;
					   int				i;

					   //  2014/12/11. 这里检查下，如果是在3d会议中，那么不能有发送到组里的任务
					   if  (  m_var.av.taskInfo.bTaskExists  &&  m_var.av.taskInfo.ucbVideoConference  &&  m_var.av.taskInfo.ucbStarter
						   &&  m_var.av.taskInfo.mosaicMaker.video.resObj.uiObjType  )
					   {
						   dlgTalk_chkInvalidTaskInMosaic(  pQyMc,  hDlgTalk,  m_var,  &pMsg->task  );
					   }

					   //
					   if  (  pMsg->task.idInfo_taskSender.ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  )  continue;



					   //
					   time_t			t;  
					   mytime(  &t  );
					   					   
#if  0
					   //
					   for  (  i  =  0;  i  <  mycountof(  pImgs->mems  );  i  ++  )  {
						   if  (  pImgs->mems[i].iTaskId  ==  pMsg->task.iTaskId  )  {
							   minElapseInMs  =  min(  minElapseInMs,  dwTickCnt  -  pImgs->mems[i].dwTickCnt_lastDrawing  );
							   if  (  minElapseInMs  <  nElapseInS  *  1000  )  {
								   break;							   
							   }
						   }
					   }
					   if  (  i  <  mycountof(  pImgs->mems  )  )  {
						   //  bTaskImgAlive  =  TRUE;
						   continue;
					   }
#endif
					   //
					   #ifdef  __DEBUG__


					   #endif


					   //
					   if  (  t  -  pMsg->task.tTime_alive  <  nElapseInS  
						   ||  bTaskImgActive(  hDlgTalk,  &m_var,  &pMsg->task  )  )  
					   {
						   //
						   pMsg->task.nTimes_applyForChkTaskAlive  =  0;
						   continue;
					   }
					   

					   //  2011/02/02
					   //int  iWndContentType;

					   //
					   #ifdef  __DEBUG__
							   traceLogA(  (char*)  "task %d: tElapse %d",  pMsg->task.iTaskId,  t  -  pMsg->task.tStartTime_processed  );
					   #endif


					   //
					   int  maxValidVal_nTimes_applyForChkTaskAlive  =  10;//2;
					   if  (  m_var.av.taskInfo.bTaskExists  &&  m_var.av.taskInfo.iTaskId  ==  pMsg->task.iTaskId  )  {
						   maxValidVal_nTimes_applyForChkTaskAlive  =  20;	//  10;
					   }
					   if (m_var.av.taskInfo.ucbVideoConference && !m_var.av.taskInfo.ucbStarter) {
						   maxValidVal_nTimes_applyForChkTaskAlive = 1;		//  如果nTimes_applyForChkTaskAlive大于0就是表明已经有5秒以上画面没更新了. 2023/05/15
					   }
					   //
#ifdef  __DEBUG__
					   if (0) {
						   //
						   traceLog((TCHAR*)_T("for test, max_nTimes_applyForChkTaskAlive set to 10000"));
						   maxValidVal_nTimes_applyForChkTaskAlive = 10000;
					   }
#endif 
					   //
					   if  (  pMsg->task.nTimes_applyForChkTaskAlive  >  maxValidVal_nTimes_applyForChkTaskAlive  )  
					   {
						   //
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "talker%I64u: task %d shall be canceled. nTimes_applyForChkTaskAlive %d"  ),  m_var.addr.idInfo.ui64Id,  pMsg->task.iTaskId,  (int)pMsg->task.nTimes_applyForChkTaskAlive  );
						   #ifdef  __DEBUG__
								   traceLog((TCHAR*)  tBuf  ),
						   #endif
						   showInfo_open0(  0,  0,  tBuf  );
						   //showNotification_open(  0,  0,  0,  tBuf  );

						   //
						   //
					#if  10
						   if  (  m_var.av.taskInfo.bTaskExists
							   &&  m_var.av.taskInfo.iTaskId  ==  pMsg->task.iTaskId  )  
						   {
							   if  (  m_var.av.taskInfo.idInfo_initiator.ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  )  {
								   //
								   //  发起方都是手工关闭
								   //if  (  IDYES  !=  qyMessageBox(  hDlgTalk,  _T(  "很久没收到视频数据了，是不是要取消会议?"  ),  _T(  "qycx.com"  ),  MB_YESNO | MB_DEFBUTTON2,  10000,  NULL  )  )  
								   {
									   //
									   pMsg->task.nTimes_applyForChkTaskAlive  =  0;
									   //
									   continue;
								   }
							   }
						   }
					#endif

						   //
						   if  (  !pMsg->task.iTaskId  )  goto  errLabel;
						   dlgTalk_cancelTasks(  hDlgTalk,  &m_var,  pMsg->task.iTaskId,  TRUE  );

						   //
						   if (!pQyMc->appParams.bConfServer) {
							   if (bObjTypeGrp(m_var.addr.uiObjType )) {
								   if (!m_var.av.taskInfo.bTaskExists) {
									   //
									   bool  bNeedChk = false;
									   //
									   HWND  hTalk = mynull;
									   if (!findTalker_shadow(pQyMc, m_var.addr.idInfo.ui64Id, CONST_talkerSubtype_video, &hTalk)) {
										   bNeedChk = true;
									   }
									   //
									   if (pProcInfo->m_iCtxSubtype == CONST_ctxSubtype_qmcMfc) {
										   bNeedChk = true;
									   }
									   //
									   if (bNeedChk) {
										   dlgTalk_chkAutoAnswer(hDlgTalk);
									   }
								   }
							   }
						   }

						   //
						   break;
					   }

					   //  2014/12/09
					   bNeedChkRecvdTasks  =  TRUE;

					   //  2014/12/09
					   if  (  t  -  pMsg->task.tTime_applyForChkTaskAlive  <  1  )  {
						   //  发起请求不要过于频繁
						   continue;
					   }					  

					   //
					   #ifdef  __DEBUG__
							   traceLogA(  (char*)  "task %d may be off, send req to retrieve status",  pMsg->task.iTaskId  );
					   #endif
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "talker%I64u: chkRecvdTasks, task %d hasn't received data for %ds, send req to check whether task is alive."  ),  m_var.addr.idInfo.ui64Id,  pMsg->task.iTaskId,  nElapseInS  );
					   showInfo_open0(  0,  0,  tBuf  );

					   //  2010/10/30
					   pMsg->task.tTime_applyForChkTaskAlive  =  t;
					   pMsg->task.nTimes_applyForChkTaskAlive  ++  ;

					   //
					   TASK_PROC_REQ		taskProcReq;
					   int					lenInBytes;
					   memset(  &taskProcReq,  0,  sizeof(  taskProcReq  )  );
					   taskProcReq.uiType  =  CONST_imCommType_taskProcReq;
					   taskProcReq.usOp  =  CONST_imOp_recv_applyForChkTaskAlive;
					   taskProcReq.tStartTime_org  =  pMsg->task.tStartTime;
					   taskProcReq.uiTranNo_org  =  pMsg->task.uiTranNo;
					   //  taskProcReq.uiSerialNo_org  =  0;
					   taskProcReq.uiContentType_org  =  pContent->uiType;
					   //	
					   lenInBytes  =  sizeof(  taskProcReq  );			
					   //					
					   MACRO_prepareForTran(  );						
					   //
					   if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  pMsg->task.usCode,  tStartTran,  uiTranNo,  0,  0,  0,  (  char  *  )&taskProcReq,  lenInBytes,  &m_var.addr.idInfo,  NULL,  NULL,  &pMsg->task.data.route.idInfo_from,  0,  NULL,  FALSE  )  )  goto  errLabel;

					   }
					   break;
				 case  CONST_imCommType_transferFileReq:  {
					   QMC_taskData_transferFile  *  pTt  =  (  QMC_taskData_transferFile  * )pTaskInfo->var.pTaskData;
					   //  2015/08/08					 
					   if  (  pContent->transferFileReq.bNeedCancel  )  {
						   #ifdef  __DEBUG__
								   traceLogA(  (char*)  "dlgTalk::task %d shall be canceled",  pMsg->task.iTaskId  );
						   #endif
						   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk::task %d shall be canceled"  ),  pMsg->task.iTaskId  );
						   //
						   if  (  !pMsg->task.iTaskId  )  goto  errLabel;
						   dlgTalk_cancelTasks(  hDlgTalk,  &m_var,  pMsg->task.iTaskId,  TRUE  );
						   break;				 
					   }

					   //
					   if  (  pMsg->task.idInfo_taskSender.ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  )  continue;

					   time_t			t;  
					   int			minElapseInMs	=	nTimeoutInS  *  1000  +  1;
					   DWORD			dwTickCnt		=	GetTickCount(  );
					   mytime(  &t  );

					   if  (  t  -  pMsg->task.tStartTime_processed  <  nElapseInS  )  continue;

					   //
					   if  (  dwTickCnt  -  pTt->dwLastReportTickCnt  <  7000  )  continue;

					   //
					   if  (  pMsg->task.iStatus  !=  CONST_imTaskStatus_waitToRecv  )  {
						   #ifdef  __DEBUG__
								   traceLog((TCHAR*)  _T(  "dlgTalk_chkRecvdTasks: fileReq, %s"  ),  qyGetDesByType1(  CONST_qyStatusTable_en,  pMsg->task.iStatus  )  );
						   #endif
						   continue;
					   }
						
					   #ifdef  __DEBUG__
							   traceLog((TCHAR*)  _T(  "dlgTalk_chkRecvdTasks: fileReq: waitToRecv"  )  );
					   #endif

					   MIS_MSG_applyForChkChannels_qmc	msg_applyForChkChannels_qmc;

					   //  robot
					   memset(  &msg_applyForChkChannels_qmc,  0,  sizeof(  msg_applyForChkChannels_qmc  )  );
					   msg_applyForChkChannels_qmc.uiType  =  CONST_misMsgType_applyForChkChannels_qmc;
					   msg_applyForChkChannels_qmc.pMisCnt  =  m_var.pMisCnt;

					   MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );

					   qPostMsgAndTrigger(  &msg_applyForChkChannels_qmc,  sizeof(  msg_applyForChkChannels_qmc  ),  &pProcInfo->robotQ,  _T(  "dlgTalk_chkRecvdTasks"  ));

					   }					   
					   break;

				 default:
						#ifdef  __DEBUG__
								traceLog((TCHAR*)  _T(  "dlgTalk_chkRecvdTasks: contentType %d"  ),  pContent->uiType  );
						#endif
						break;
		 }
	}
	
	//  2014/12/09
	m_var.needChkTasks.bNeedChkRecvdTasks  =  bNeedChkRecvdTasks;

	//  2016/02/29
	if  (  bChanged_taskList  )  {
		dyn_d3dWall_refreshWallMemByTalker(  hDlgTalk  );
	}
	if  (  bWaitingTo_beRe_accepted  !=  m_var.guiData.av.canceledTask_screenOrMediaFile.bTaskExists_waitingTo_beRe_accepted  )  {
		m_var.guiData.av.canceledTask_screenOrMediaFile.bTaskExists_waitingTo_beRe_accepted  =  bWaitingTo_beRe_accepted;
		dyn_d3dWall_askToRefreshIa();
	}

	//
	iErr  =  0;
errLabel:

	#ifdef  __DEBUG__
			//traceLogA(  (char*)  "chkRecvdTasks leaves"  );
	#endif

	return  iErr;
}


//
 int  confStarter_chkActiveMems(  HWND  hDlgTalk,  DLG_TALK_var  &m_var  )
{
	int  iErr  =  -1;
	CCtxQmc  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;
	if  (  !m_var.av.taskInfo.bTaskExists  )  return  -1;
	if  (  !m_var.av.taskInfo.ucbVideoConference
		||  !m_var.av.taskInfo.ucbStarter  )
	{
		return  -1;
	}

	int  index_taskInfo  =  getQmcTaskInfoIndexBySth(  pProcInfo,  m_var.av.taskInfo.iTaskId  );
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  index_taskInfo  );
	if  (  !pTaskInfo  )  goto  errLabel;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;
	if  (  pTc->common.uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;

	//
	DWORD  dwTickCnt  =  myGetTickCount(  NULL  );
	MIS_CNT  *  pMisCnt  =  m_var.pMisCnt;

	//
	bool  bChanged  = false;

	//
	int  i;
	for  (  i  =  0;  i  <  pTc->videoConference.usCntLimit_activeMems_from;  i  ++  )  {
		DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem  =  &pTc->videoConference.activeMems_from[i];
		if  (  !pActiveMem->avStream.idInfo.ui64Id  )  continue;
		if  (  pActiveMem->avStream.idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  continue;
		//
		int  iDiffInMs_a  =  dwTickCnt  -  pActiveMem->dwLastTickCnt_aData;
		int  iDiffInMs_v  =  dwTickCnt  -  pActiveMem->dwLastTickCnt_vData;
		//
		//traceLog((TCHAR*)  _T(  "confStart_chkActiveMems: activeMems[%d] iDiffInMs_a %d, iDiffInMs_v %d"  ),  i,  iDiffInMs_a,  iDiffInMs_v  );

		if  (  abs(iDiffInMs_a)  >  5000    &&  abs(iDiffInMs_v)  >  5000  )  {
			pActiveMem->nTimes_tooLong  ++  ;
			}
		else  {
			  pActiveMem->nTimes_tooLong  =  0;
		}

		//
		if  (  pActiveMem->nTimes_tooLong  >  2  )  {
			TCHAR  tBuf[128];
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "talker%I64u, too long time after last data recved, activeMems[%d] canceled"  ),  m_var.addr.idInfo.ui64Id,  i  );
			showInfo_open0(  0,  0,  tBuf  );
			//
			pProcInfo->confStarter_requestToSpeak(  hDlgTalk,  &pActiveMem->avStream.idInfo,  &pActiveMem->avStream.obj,  _T(  ""  ),  false  );
			//
			bChanged  =  true;
		}

		//
		continue;
	}

	if  (  bChanged  )  {
		BOOL  bModified  =  false;
		dlgTalk_refresh_usLayoutType_cur(  hDlgTalk,  &bModified  );
		//
		refreshConfLayout(m_var.av.taskInfo.iIndex_taskInfo);
		//
		pProcInfo->sendConfKey(  hDlgTalk,  m_var.addr.idInfo,  _T(  "confStarter_chkActiveMems: some speakers canceled"  )  );
	}


	iErr  =  0;
errLabel:
	return  iErr;

}


 //
  int  confServ_chkConf(  QY_MC  *  pQyMc,  HWND  hDlgTalk,  DLG_TALK_var  &m_var  )
{
	int  iErr  =  -1;
	//CCtxQyMc  *  pQyMc  =  QY_GET_GBUF(  );
	CCtxQmc  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	TCHAR  tBuf[128];

	//
	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;

	if  (  !pQyMc->appParams.bConfServer  )  return  -1;

	//
	if  (  pProcInfo->cfg.debugStatusInfo.ucbShowDlgTalkStatus  )  {
		showInfo_open0(  0,  0,  _T(  "confServ_chkConf called"  )  );
	}
	
	//
	DWORD  dwTickCnt  =  myGetTickCount(  NULL  );

	//
	if  (  !m_var.av.taskInfo.bTaskExists  )  {
		//
		bool  bNeedClose  =  false;
		
		//
		int  iDiffInMs  =  dwTickCnt  -  m_var.dwTickCnt_created;
		if  (  abs(  iDiffInMs  )  >  10000  )  {
			bNeedClose  =  true;
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "talker%I64u, no av task exists. need be closed"  ),  m_var.addr.idInfo.ui64Id  );
		}
		
		//
		if  (  bNeedClose  )  {
			//
			sendConfReq(  0,  hDlgTalk,  m_var.addr.idInfo,  CONST_imOp_send_cancel,  0,  0,  0,  0  );  

			//
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. bNeedClose true, Post WM_CLOSE"  ),  tBuf  );	
			showInfo_open0(  0,  0,  tBuf  );			
			//				
			PostMessage(  hDlgTalk,  WM_CLOSE,  0,  0  );				
			goto  errLabel;
		}

		//
		return  -1;
	}
		
	//
	if  (  !m_var.av.taskInfo.ucbVideoConference
		||  !m_var.av.taskInfo.ucbStarter  )
	{
		return  -1;
	}

	//
	{
		//
		bool  bNeedClose  =  false;
		//
		tBuf[0]  =  0;
		if  (  !pProcInfo->av.video.bChannelReady  )  {

			int  iDiffInMs  =  dwTickCnt  -  pProcInfo->av.video.dwLastModifiedTickCnt;
			if  (  abs(  iDiffInMs  )  >  5000  )  {
				m_var.av.taskInfo.confStarterInfo.nTimes_vChannel_notReady  ++  ;
			}
			//
			if  (  m_var.av.taskInfo.confStarterInfo.nTimes_vChannel_notReady  >  3  )  {
				bNeedClose  =  true;
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "talker%I64u: nTimes_vChannel_notReady>3, need close"  ),  m_var.addr.idInfo.ui64Id  );
			}
			//
			}
		else  {
			  m_var.av.taskInfo.confStarterInfo.nTimes_vChannel_notReady  =  0;
		}
		//
		#ifdef  __DEBUG__
				#if  0
					 if  (  m_var.loopCtrl_timer  >  100  )  {
						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "For test, set bNeedClose to true"  )  );
						bNeedClose  =  true;
					 }
				#endif
					 //
				#if  1
					 if (bNeedClose) {
						 traceLog((TCHAR*)_T("for test: bNeedClose set to false"));
						 bNeedClose = false;
					 }
				#endif		
				//
		#endif
		//
		if  (  bNeedClose  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. bNeedClose true, Post WM_CLOSE"  ),  tBuf  );	
			showInfo_open0(  0,  0,  tBuf  );			
			//				
			PostMessage(  hDlgTalk,  WM_CLOSE,  0,  0  );				
			goto  errLabel;
		}
		//
		if  (  pProcInfo->cfg.debugStatusInfo.ucbShowDlgTalkStatus  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "talker%I64u: v.bChannelReady %d. nTimes_vChannel_notReady %d"  ),  m_var.addr.idInfo.ui64Id,  pProcInfo->av.video.bChannelReady,  m_var.av.taskInfo.confStarterInfo.nTimes_vChannel_notReady  );
			showInfo_open0(  0,  0,  tBuf  );
		}
		//
	}


	iErr =  0;
	errLabel:
	return  iErr;
  }


//  2012/04/20
 int  dlgTalk_chkToViewGps(  QY_MC  *  pQyMc,  HWND  hDlgTalk,  DLG_TALK_var  &  m_var  )
{
	int					iErr			=	-1;
	//QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	TCHAR				tHint[128]		=	_T(  ""  );
	

	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;

	TALKER_shadow_mgr	*	pShadowMgr	=	(  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;
	
	if  (  !pShadowMgr->vwRuleCmd.ucbViewGps  )  return  -1;

	//
	DWORD	dwTickCnt  =  GetTickCount(  );

	if  (  dwTickCnt  -  pShadowMgr->viewGps.dwTickCnt_lastRecvd  <  20000  )  {
		//  表示还活跃着
		iErr  =  0;  goto  errLabel;
	}


	//
	_sntprintf(  tHint,  mycountof(  tHint  ),  _T(  "%s: %I64u"  ),  _T(  "restart"  ),  m_var.addr.idInfo.ui64Id  );
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "viewGps: %s"  ),  tHint  );


	if  (  procSendGpsInfo(  m_var.pMisCnt,  hDlgTalk,  TRUE,  CONST_imTaskType_viewGps,  -1,  -1,  NULL,  &pShadowMgr->viewGps.iTaskId,  &m_var.addr  )  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "viewGps: procSendGpsInfo failed"  )  );
		goto  errLabel;
	}

	//
	qmcApplyForChkingTasks_gui(  pQyMc  );

	iErr  =  0;
errLabel:
	return  iErr;
 }


 



 
 //
 





 //
int  dlgTalk_chkAsAdvertisingPlayer(  HWND  hDlgTalk,  DLG_TALK_var  *  pDlgTalkVar,  BOOL  *  pbNeedClose,  TCHAR  *  tHint,  unsigned  int  uiCnt_tHint  )
{
	int		iErr	=	-1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	BOOL  bNeedClose  =  FALSE;

	if  (  !pDlgTalkVar  )  return  -1;

	if  (  !pProcInfo->cfg.policy.ucbRunAsAdvertisingPlayer  )  goto  errLabel;
	if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  goto  errLabel;
	
	//  2014/06/11
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pDlgTalkVar->pShadowInfo;	
	if  (  !pShadowMgr  )  goto  errLabel;


	//  2014/06/11
	BOOL  bExists_dynBmpRule  =  FALSE;
	int  i;
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->vwRuleCmd.dynBmpRules  );  i  ++  )  {			
		if  (  !pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.uiObjType  )  continue;
		if  (  tmpF_bViewRemoteVideo(  &pShadowMgr->vwRuleCmd,  pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.uiObjType,  pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.usIndex_obj,  pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.usHelp_subIndex  )  )  {
			 bExists_dynBmpRule  =  TRUE;
			 #ifdef  __DEBUG__
					 traceLog((TCHAR*)  _T(  "dlgTalk_chkAsAdvertisingPlayer: dynBmpRule exists"  )  );
			 #endif
			 break;
		 }
	}

	//
	BOOL  bExists_remoteAssist  =  FALSE;
	if  (  bRemoteAssistExists(  pProcInfo  )  )  {
		bExists_remoteAssist  =  TRUE;
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "dlgTalk_chkAsAdvertisingPlayer: remoteAssist exists"  )  );
		 #endif
	}

	//
	if  (  !pDlgTalkVar->av.taskInfo.bTaskExists
		&&  !bTaskExists_sendingResource(  pDlgTalkVar,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL  )
		&&  !bTaskExists_recvResource(  pDlgTalkVar,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL  )  
		&&  !bExists_dynBmpRule  
		&&  !bExists_remoteAssist  
		)  
	{
		if  (  tHint  &&  uiCnt_tHint  )  {
			_sntprintf(  tHint,  uiCnt_tHint,  _T(  "dlgTalk_chkAsAdvertisingPlayer (%I64u), no av task exists, prompt to close window"  ),  pDlgTalkVar->addr.idInfo.ui64Id  );
		}

#if  0
		qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_chkAsAdvertisingPlayer (%I64u), no av task exists, prompt to close window"  ),  pDlgTalkVar->addr.idInfo.ui64Id  );
		_sntprintf(  pShadowMgr->promptToClose.tHint,  mycountof(  pShadowMgr->promptToClose.tHint  ),  _T(  "No av exists, window will be closed"  )  );
		PostMessage(  hDlgTalk,  WM_COMMAND,  MAKEWPARAM(  ID_promptToClose,  0  ),  0  );
#endif
		bNeedClose  =  TRUE;
	}
		
	iErr  =  0;
errLabel:

	if  (  !iErr  )  {
		if  (  pbNeedClose  )  *pbNeedClose  =  bNeedClose;
	}

	return  iErr;
}

//  2015/08/04
int  dlgTalk_chkFileServer(  HWND  hDlgTalk,  DLG_TALK_var  *  pDlgTalkVar,  BOOL  *  pbNeedClose,  TCHAR  *  tHint,  unsigned  int  uiCnt_tHint  )
{
	int		iErr	=	-1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	QY_MC  *  pQyMc  =  (  QY_MC  *  )pProcInfo->pQyMc;

	//
	BOOL  bNeedClose  =  FALSE;

	if  (  !pDlgTalkVar  )  return  -1;

	if  (  !bSupported_fileServer(  pQyMc  )  )  goto  errLabel;
	if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  goto  errLabel;
	
	//  2014/06/11
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pDlgTalkVar->pShadowInfo;	
	if  (  !pShadowMgr  )  goto  errLabel;

	//  2015/08/10
	if  (  myGetTickCount(  NULL  )  -  pDlgTalkVar->dwTickCnt_created  <  1  *  60  *  1000  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "dlgTalk_chkFileServer failed: dlgTalk can't be closed too quickly"  )  );
		#endif
		goto  errLabel;
	}


	//  2014/06/11
	BOOL  bExists_dynBmpRule  =  FALSE;
	int  i;
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->vwRuleCmd.dynBmpRules  );  i  ++  )  {			
		if  (  !pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.uiObjType  )  continue;
		if  (  tmpF_bViewRemoteVideo(  &pShadowMgr->vwRuleCmd,  pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.uiObjType,  pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.usIndex_obj,  pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.usHelp_subIndex  )  )  {
			 bExists_dynBmpRule  =  TRUE;
			 #ifdef  __DEBUG__
					 traceLog((TCHAR*)  _T(  "dlgTalk_chkFileServer: dynBmpRule exists"  )  );
			 #endif
			 break;
		 }
	}

	//
	BOOL  bExists_remoteAssist  =  FALSE;
	if  (  bRemoteAssistExists(  pProcInfo  )  )  {
		bExists_remoteAssist  =  TRUE;
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "dlgTalk_chkFileServer: remoteAssist exists"  )  );
		 #endif
	}

	//
	DWORD  dwTickCnt  =  GetTickCount(  );
	int  iElapseInMs  =  0;

	//
	BOOL  bExists_fileTask  =  FALSE;
	iElapseInMs  =  dwTickCnt  -  pShadowMgr->fileTaskInfo.dwLastModifiedTickCnt_taskStatus;
	int  nIntervalInMs  =  9000;
	nIntervalInMs  =  20000;
	if  (  iElapseInMs  >  nIntervalInMs  *  (  pShadowMgr->fileTaskInfo.usTimes_noFileTask  +  1  )  )  {
		pShadowMgr->fileTaskInfo.usTimes_noFileTask  ++  ;
	}
	if  (  pShadowMgr->fileTaskInfo.usTimes_noFileTask  <  6  )  bExists_fileTask  =  TRUE;

	//
#ifdef  __DEBUG__

#endif

	//
	if  (  pShadowMgr->fileTaskInfo.usTimes_noFileTask  )  {
		if  (  tHint  &&  uiCnt_tHint  )  {
			_sntprintf(  tHint,  uiCnt_tHint,  _T(  "dlgTalk_chkFileServer (%I64u), elapse %dms, nTimes %d"  ),  pDlgTalkVar->addr.idInfo.ui64Id,  iElapseInMs,  (  int  )pShadowMgr->fileTaskInfo.usTimes_noFileTask  );
			showInfo_open0(  0,  0,  tHint  );
		}
	}



	//
	if  (  !pDlgTalkVar->av.taskInfo.bTaskExists
		&&  !bTaskExists_sendingResource(  pDlgTalkVar,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL  )
		&&  !bTaskExists_recvResource(  pDlgTalkVar,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL  )  
		&&  !bExists_dynBmpRule  
		&&  !bExists_remoteAssist  
		&&  !bExists_fileTask
		)  
	{
		if  (  tHint  &&  uiCnt_tHint  )  {
				_sntprintf(  tHint,  uiCnt_tHint,  _T(  "dlgTalk_chkFileServer (%I64u), no file task exists, elapse %dms, prompt to close window"  ),  pDlgTalkVar->addr.idInfo.ui64Id,  iElapseInMs  );
		}

#if  0
		qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_chkFileServer (%I64u), no file task exists, prompt to close window"  ),  pDlgTalkVar->addr.idInfo.ui64Id  );
		_sntprintf(  pShadowMgr->promptToClose.tHint,  mycountof(  pShadowMgr->promptToClose.tHint  ),  _T(  "No file exists, window will be closed"  )  );
		PostMessage(  hDlgTalk,  WM_COMMAND,  MAKEWPARAM(  ID_promptToClose,  0  ),  0  );
#endif
		//
		bNeedClose  =  TRUE;
	}
		
	iErr  =  0;
errLabel:

	if  (  !iErr  )  {
		if  (  pbNeedClose  )  *pbNeedClose  =  bNeedClose;
	}

	return  iErr;
}




//  2014/12/09
typedef  struct  __param_chkAutoAnswer_t	{
				 BOOL						bTaskFound;
}		 PARAM_chkAutoAnswer;






//  2014/12/08
int  tmpHandler_chkAutoAnswer(  void  *  hDlgTalkParam,  void  *  p1,  void  *  pMsgParam  )
{
	int  iErr  =  -1;
	
	HWND				hDlgTalk					=	(  HWND  )hDlgTalkParam;	
	PARAM_chkAutoAnswer  *  pParam				=	(  PARAM_chkAutoAnswer  *  )p1;
	MIS_MSGU		*	pMsgElem					=	(  MIS_MSGU  *  )pMsgParam;
	
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pm_var					=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pm_var  )  return  -1;	
	DLG_TALK_var	&	m_var					=	*pm_var;
	
	QY_MC* pQyMc = m_var.pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli	*	pProcInfo				=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	TCHAR				txtContent[1024]		=	_T(  ""  );
	TCHAR				senderDesc[255  +  1]	=	_T(  ""  );
	TCHAR				receiverDesc[255  +  1]	=	_T(  ""  );
	time_t				t;
	int					tmpiRet					=	0;
	//
	TCHAR				tBuf[1024]				=	_T(  ""  );
	int					i;
	//
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	//
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "tmpHandler_chkAutoAnswer called"  )  );
#endif

	//
	if  (  !hDlgTalk  ||  !pParam  || !pMsgElem  )  return  -1;

	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

    if  (  !bReady_toShowMsg(  hDlgTalk  )  )  goto  errLabel;

	mytime(  &t  );

	//
	if (pMsgElem->uiType != CONST_misMsgType_task) {
		iErr = 0;  goto  errLabel;
	}

	//
	if (!pMsgElem->task.tStartTime_processed) {
		//  not processed by tmpHandler_showMsg. skipped

		//  2016/05/09
		static  DWORD  dwTickCnt_triggerMsgArrive = 0;
		DWORD  dwTickCnt = GetTickCount();
		int  iDiffInMs = dwTickCnt - dwTickCnt_triggerMsgArrive;
		if (abs(iDiffInMs) > 500) {
			dwTickCnt_triggerMsgArrive = dwTickCnt;
			//
			::PostMessage(hDlgTalk, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);
			//
			showInfo_open0(0, 0, _T("tmpHandler_chkAutoAnswer: tStartTime_processed 0, trigger to post msgArrive. "));
		}

		//
		iErr = 0;  goto  errLabel;
	}

	//
	MIS_MSG_TASK* pMsgTaskElem = &pMsgElem->task;
	IM_CONTENTU* pContentElem = M_getMsgContent(pMsgTaskElem->ucFlg, &pMsgTaskElem->data);
	if (pContentElem == mynull)goto  errLabel;
	MIS_MSGU* pMsg = mynull;
	//
	if  (  pProcInfo->bAppQt()  )  {
		switch  (  pContentElem->uiType) {
				case  CONST_imCommType_transferAvInfo: {
					  int  index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, pMsgTaskElem->iTaskId);
					  if (index_taskInfo < 0) {
						  // skipped
						  iErr = 0;  goto  errLabel;
					  }			
					  QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);			
					  QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;			
					  pMsg = &pTaskData->msgU;			
					  }			
					  break;		
				default:			
						pMsg = (MIS_MSGU*)pMsgTaskElem;			
						break;		
		}
		}
	else {
		 //
		 pMsg = (MIS_MSGU*)pMsgTaskElem;
	}
	//
	if (pMsg == mynull)  goto  errLabel;



	//
	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_task:  {


				  //
				  if (!pProcInfo->bAppQt()) {
					  int index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, pMsg->task.iTaskId);
					  if (index_taskInfo >= 0) {
						  //  processed
						  break;
					  }
				  }
				  else {
					  switch (pContentElem->uiType) {
					  case  CONST_imCommType_transferAvInfo:
						  break;
					  default:
						  //
					  {
						  int index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, pMsg->task.iTaskId);
						  if (index_taskInfo >= 0) {
							  //  processed
							  iErr = 0;  goto  errLabel;
						  }
					  }

					  //
					  break;
					  }
				  }


				  //				  					  
				  MIS_MSG_routeTalkData		*	pTalkData							=	&pMsg->task.data;					
				  IM_CONTENTU				*	pContent							=	(  IM_CONTENTU  *  )pTalkData->buf;	
				  QY_MESSENGER_ID				idInfo_talker;
				  MIS_CNT  *  pMisCnt  =  m_var.pMisCnt;
				  if  (  !pMisCnt  )  goto  errLabel;
				  			
				  //
				  switch  (  pMsg->task.iStatus  )  {
						  case  CONST_imTaskStatus_resp:
							    break;
						  case  CONST_imTaskStatus_applyToRecv:  //  2015/08/05
							    break;
						  default:
								 //  processed
							     iErr  =  0;  goto  errLabel;
					    		 break;
				  }

				  //  2010/09/06					
				  if  (  pMsg->task.data.route.idInfo_from.ui64Id  !=  pMisCnt->idInfo.ui64Id  )  {
						  if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
							  QM_OBJQ_MEM				mem;
							  QMEM_MESSENGER_CLI	*	pQMemObj	=	NULL;
							  unsigned  int				uiRuleCmd	=	0;
							  TASK_autoAnswer			autoAnswer;  

							  if  (  findQMemByKey(  pProcInfo->pSgiParam,  (  QM_OBJQ  *  )m_var.pMisCnt->pObjQ,  &m_var.addr.idInfo,  &mem  )  )  {
								  traceLog((TCHAR*)  _T(  "dlgTalk_OnInitDialog failed, findQMemByKey failed."  )  );
								  goto  errLabel;
							  }
							  if  (  !mem.pQMemObj  )  goto  errLabel;
		
							  pQMemObj  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;

							  //
							  if (pProcInfo->bAppQt()) {
								  HWND  hShadow = mynull;
								  if (findTalker_shadow(pQyMc, m_var.addr.idInfo.ui64Id, CONST_talkerSubtype_video, &hShadow)) {
									  showInfo_open0(0, mynull, _T("chkAutoAnswer failed, findTalker_shadow failed"));
									  goto  errLabel;
								  }
							  }


							  //
							  if  (  pContent->transferAvInfo.uiTaskType  ==  CONST_imTaskType_transferAvInfo
								  ||  pContent->transferAvInfo.uiTaskType ==  CONST_imTaskType_shareDevice_grp )  
							  {
								  //  2016/02/15
								  BOOL  bPermitted  =  FALSE;
								  //
								  if  (  bAutoAccepted_avCall(  hDlgTalk,  &pQMemObj->rules,  pContent->transferAvInfo.uiTaskType  )  )  {
									  bPermitted  =  TRUE;
								  }
								  //
								  if  (  bPermitted  )
								  {
									  CQySyncFlg  syncFlg;

									  if  (  m_var.av.taskInfo.bTaskExists  )  {	
										  //  2014/12/09. 触发对任务的检查
										  if  (  !m_var.av.taskInfo.ucbStarter  )  {											
											  m_var.needChkTasks.bNeedChkRecvdTasks  =  TRUE;
										  }
										  //  skipped
										  iErr  =  0;  goto  errLabel;
									  }

									  //  2014/12/09
									  pParam->bTaskFound  =  TRUE;
									  if  (  syncFlg.sync(  &m_var.autoAnswer.bInProgress_autoAnswer  )  )  goto  errLabel;
									  
									  memset(  &autoAnswer,  0,  sizeof(  autoAnswer  )  );

									  //										
									  //  if  (  m_var.av.autoAnswer_av.task.bTaskNeedAutoAnswered  )  goto  errLabel;										
									  //  
									  if  (  isRuleCmdPermit(  pQMemObj->rules.uiCmd_autoAnswer_av  )  )  uiRuleCmd  =  pQMemObj->rules.uiCmd_autoAnswer_av;
									  else  uiRuleCmd  =  pQMemObj->customerService.rules.uiCmd_autoAnswer_av;
									  //
									  autoAnswer.uiCmd_autoAnswer  =  uiRuleCmd;
									  //
									  autoAnswer.task.iTaskId  =  pMsg->task.iTaskId;
									  autoAnswer.task.iTaskStatus  =  pMsg->task.iStatus;
									  autoAnswer.task.bTaskNeedAutoAnswered  =  TRUE;

									  TASK_autoAnswer  *  pAutoAnswer  =  &autoAnswer;					
									  										
									  //
									  int					iIndex_sharedObj	=	getSharedObjIndex_localAv(  );										
									  QY_SHARED_OBJ	*	pSharedObj			=	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
																				
									  if  (  pSharedObj->bQuit  )  {
										  showInfo_open0(  0,  0,  _T(  "tmpHandler_chkAutoAnswer failed, pSharedObj->bQuit is true"  )  );
										  goto  errLabel;
									  }
																				
									  //										
									  MIS_MSG_TASK  *  pMsgTask  =  findTaskInProcessQ(  &m_var,  pAutoAnswer->task.iTaskId  );
									  //
									  if  (  !pMsgTask  )  {
										  showInfo_open0(  0,  0,  _T(  "tmpHandler_chkAutoAnswer failed, findTaskInProcessQ returns null"  )  );
										  goto  errLabel;
									  }
									  
									  {
										  HWND	hFore	=	GetForegroundWindow(  );
										  //  EnableWindow(  hDlgTalk,  FALSE  );
										  PARAM_dlgTalk_procTask  param;
										  memset(  &param,  0,  sizeof(  param  )  );
										  param.av_autoAnswer_av_task_bTaskNeedAutoAnswered  =  TRUE;
										  dlgTalk_procTask1(  hDlgTalk,  pMsgTask->iTaskId,  CONST_imOp_dual_permit,  NULL,  &param  );  
										  //  EnableWindow(  hDlgTalk,  TRUE  );
										  if  (  pAutoAnswer->uiCmd_autoAnswer  !=  CONST_ruleCmd_permitAndFullscreen  )  {
											  if  (  hFore  )  SetForegroundWindow(  hFore  );						
											  }
										  else  {	//  2010/11/28						  
											    if  (  !dlgTalk_get_usLayoutType_local(  hDlgTalk  )  )  {						  
													//  2011/10/04	
													if  (  pProcInfo->cfg.policy.ucbRunAsAdvertisingPlayer  )  {
														HWND  hWnd_forPrompt  =  NULL;
														int  iWndContentType  =  0;
														dlgTalk_findWndForPrompt(  hDlgTalk,  &m_var,  &hWnd_forPrompt,  &iWndContentType  );
														if  (  hWnd_forPrompt
															&&  !pFuncs->pf_bFullScreen_wnd(  hWnd_forPrompt,  iWndContentType  )  )  								  
														{
															PostMessage(  hWnd_forPrompt,  WM_COMMAND,  MAKEWPARAM(  ID_fullScreen,  0  ),  0  );
															SetForegroundWindow(  hWnd_forPrompt  );									  								  
														}							  
													}						  
												}					
										  }
										  //  2011/10/15. 如果设置了会议需要共享摄像机，那么这里要触发共享窗口
										  if  (  m_var.pMisCnt->imRules.conferenceId_shareWebcam.ui64Id
											  &&  m_var.pMisCnt->imRules.conferenceId_shareWebcam.ui64Id  ==  m_var.addr.idInfo.ui64Id  )					
										  {					
											  viewDlgShareDynBmps_isCli(  TRUE  );					
										  }				
									  }		
									  
									  memset(  &pAutoAnswer->task,  0,  sizeof(  pAutoAnswer->task  )  );
									  
									  //  2013/03/03
									  askToRefreshLayout_mgr(  hDlgTalk  );
									  
									  //  2010/12/30.
									  //  注意：这里实际上是错的，应该让notification对iTaskId敏感。这里应该根据iTaskId来删除通知，
									  //  因为有的通知如文字消息只能在窗口看见后删除, 所以不应该因为这里的删除而影响了文字消息。
									  removeNotification(  &m_var.addr.idInfo  );

				
									  //			
								  }
		
							  }
	

							  else  if  (  pContent->transferAvInfo.uiTaskType  ==  CONST_imTaskType_shareScreen  )  {		//  2010/12/20
	  								    //  2016/02/15								  
										BOOL  bPermitted  =  FALSE;
										
										if  (  bAutoAccepted_avCall(  hDlgTalk,  &pQMemObj->rules,  pContent->transferAvInfo.uiTaskType  )  )  {
											bPermitted  =  TRUE;								  
										}
										//
										if  (  bPermitted  )  
										{
											CQySyncFlg  syncFlg;

											//
											if  (  !bAppX64(  )  )  {
												if  (  m_var.av.taskInfo.bTaskExists
													&&  m_var.av.taskInfo.ucbVideoConference
													&&  m_var.av.taskInfo.ucbStarter
													&&  m_var.av.taskInfo.mosaicMaker.video.resObj.uiObjType  )
												{
													if  (  bTaskExists_sendingResource(  &m_var,  NULL,NULL,  NULL,  NULL,  NULL,  NULL  )  )  {
														_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "for win32 app, only one resource task can be active, so task can't be auto answered"  )  );
														showInfo_open0(  0,  0,  tBuf  );
														showNotification_open(  0,  0,  0,  tBuf  );
														goto  errLabel;
													}
													int  nScreens  =  0;
													int  nMediaFiles  =  0;
													int  iTaskId_recvdResource  =  0;
													if  (  bTaskExists_recvResource(  &m_var,  &nScreens,  &nMediaFiles,  NULL,  NULL,  NULL,  &iTaskId_recvdResource  )  )  {
														if  (  nScreens  +  nMediaFiles  >  1
															||  iTaskId_recvdResource  !=  pMsg->task.iTaskId  )
														{
															_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "for win32 app, only one resource task can be active, so task can't be auto answered"  )  );
															showInfo_open0(  0,  0,  tBuf  );
															showNotification_open(  0,  0,  0,  tBuf  );
															goto  errLabel;
														}
													}
						
												}												
											}

											//  2014/12/09
											pParam->bTaskFound  =  TRUE;
											if  (  syncFlg.sync(  &m_var.autoAnswer.bInProgress_autoAnswer  )  )  goto  errLabel;
											
											memset(  &autoAnswer,  0,  sizeof(  autoAnswer  )  );
											//
											if  (  isRuleCmdPermit(  pQMemObj->rules.uiCmd_autoAnswer_screen  )  )  uiRuleCmd  =  pQMemObj->rules.uiCmd_autoAnswer_screen;
											else  uiRuleCmd  =  pQMemObj->customerService.rules.uiCmd_autoAnswer_screen;
											//
											autoAnswer.uiCmd_autoAnswer  =  uiRuleCmd;
											//
											autoAnswer.task.iTaskId  =  pMsg->task.iTaskId;
											autoAnswer.task.iTaskStatus  =  pMsg->task.iStatus;
											autoAnswer.task.bTaskNeedAutoAnswered  =  TRUE;
											
											//				
											TASK_autoAnswer  *  pAutoAnswer  =  &autoAnswer;					
											//if  (  pAutoAnswer->task.bTaskNeedAutoAnswered  )  
											
											MIS_MSG_TASK  *  pMsgTask  =  findTaskInProcessQ(  &m_var,  pAutoAnswer->task.iTaskId  );
											if  (  !pMsgTask  )  goto  errLabel;
														
											//			
											{
												HWND	hFore	=	GetForegroundWindow(  );
												//  EnableWindow(  hDlgTalk,  FALSE  );
												PARAM_dlgTalk_procTask  param;
												memset(  &param,  0,  sizeof(  param  )  );
												dlgTalk_procTask1(  hDlgTalk,  pMsgTask->iTaskId,  CONST_imOp_recv_accept,  NULL,  &param  );  
												//  EnableWindow(  hDlgTalk,  TRUE  );
												if  (  pAutoAnswer->uiCmd_autoAnswer  !=  CONST_ruleCmd_permitAndFullscreen  )  {
													if  (  hFore  )  SetForegroundWindow(  hFore  );					
													}
												else  {	//  2010/11/28
													  if  (  !m_var.av.taskInfo.bTaskExists  )  {
														  if  (  !dlgTalk_get_usLayoutType_local(  hDlgTalk  )  )  {
															  //  2011/10/04	
															  if  (  pProcInfo->cfg.policy.ucbRunAsAdvertisingPlayer  )  {
																  HWND  hWnd_forPrompt  =  NULL;
																  int  iWndContentType  =  0;
																  dlgTalk_findWndForPrompt(  hDlgTalk,  &m_var,  &hWnd_forPrompt,  &iWndContentType  );
																  if  (  hWnd_forPrompt
																	  &&  !pFuncs->pf_bFullScreen_wnd(  hWnd_forPrompt,  iWndContentType  )  )  								  
																  {
																	  PostMessage(  hWnd_forPrompt,  WM_COMMAND,  MAKEWPARAM(  ID_fullScreen,  0  ),  0  );
																	  SetForegroundWindow(  hWnd_forPrompt  );									  
								  
																  }							  
															  }
						  
														  }					  
													  }									
												}											
											}				

											memset(  &pAutoAnswer->task,  0,  sizeof(  pAutoAnswer->task  )  );
											
											if  (  !m_var.av.taskInfo.bTaskExists  )  {
												//  2013/03/03
												askToRefreshLayout_mgr(  hDlgTalk  );
			
											}
											
											//  2010/12/30. 注意：这里实际上是错的，应该让notification对iTaskId敏感。这里应该根据iTaskId来删除通知，因为有的通知如文字消息只能在窗口看见后删除。						
											removeNotification(  &m_var.addr.idInfo  );
											
											//
			

		
										}
										}
										//										
							  else  if  (  pContent->transferAvInfo.uiTaskType  ==  CONST_imTaskType_remoteAssist  )  {		//  2010/12/20
	  								    //  2016/02/15								  
										BOOL  bPermitted  =  FALSE;
										
										if  (  bAutoAccepted_avCall(  hDlgTalk,  &pQMemObj->rules,  pContent->transferAvInfo.uiTaskType  )  )  {
											bPermitted  =  TRUE;								  
										}
										//
										if  (  bPermitted  )  
										{
											CQySyncFlg  syncFlg;

											//
											if  (  !bAppX64(  )  )  {
												if  (  m_var.av.taskInfo.bTaskExists
													&&  m_var.av.taskInfo.ucbVideoConference
													&&  m_var.av.taskInfo.ucbStarter
													&&  m_var.av.taskInfo.mosaicMaker.video.resObj.uiObjType  )
												{
													if  (  bTaskExists_sendingResource(  &m_var,  NULL,NULL,  NULL,  NULL,  NULL,  NULL  )  )  {
														_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "for win32 app, only one resource task can be active, so task can't be auto answered"  )  );
														showInfo_open0(  0,  0,  tBuf  );
														showNotification_open(  0,  0,  0,  tBuf  );
														goto  errLabel;
													}
													int  nScreens  =  0;
													int  nMediaFiles  =  0;
													int  iTaskId_recvdResource  =  0;
													if  (  bTaskExists_recvResource(  &m_var,  &nScreens,  &nMediaFiles,  NULL,  NULL,  NULL,  &iTaskId_recvdResource  )  )  {
														if  (  nScreens  +  nMediaFiles  >  1
															||  iTaskId_recvdResource  !=  pMsg->task.iTaskId  )
														{
															_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "for win32 app, only one resource task can be active, so task can't be auto answered"  )  );
															showInfo_open0(  0,  0,  tBuf  );
															showNotification_open(  0,  0,  0,  tBuf  );
															goto  errLabel;
														}
													}
						
												}												
											}

											//  2014/12/09
											pParam->bTaskFound  =  TRUE;
											if  (  syncFlg.sync(  &m_var.autoAnswer.bInProgress_autoAnswer  )  )  goto  errLabel;
											
											memset(  &autoAnswer,  0,  sizeof(  autoAnswer  )  );
											//
											if  (  isRuleCmdPermit(  pQMemObj->rules.uiCmd_autoAnswer_screen  )  )  uiRuleCmd  =  pQMemObj->rules.uiCmd_autoAnswer_screen;
											else  uiRuleCmd  =  pQMemObj->customerService.rules.uiCmd_autoAnswer_screen;
											//
											autoAnswer.uiCmd_autoAnswer  =  uiRuleCmd;
											//
											autoAnswer.task.iTaskId  =  pMsg->task.iTaskId;
											autoAnswer.task.iTaskStatus  =  pMsg->task.iStatus;
											autoAnswer.task.bTaskNeedAutoAnswered  =  TRUE;
											
											//				
											TASK_autoAnswer  *  pAutoAnswer  =  &autoAnswer;					
											//if  (  pAutoAnswer->task.bTaskNeedAutoAnswered  )  
											
											MIS_MSG_TASK  *  pMsgTask  =  findTaskInProcessQ(  &m_var,  pAutoAnswer->task.iTaskId  );
											if  (  !pMsgTask  )  goto  errLabel;
														
											//			
											{
												HWND	hFore	=	GetForegroundWindow(  );
												//  EnableWindow(  hDlgTalk,  FALSE  );
												PARAM_dlgTalk_procTask  param;
												memset(  &param,  0,  sizeof(  param  )  );
												dlgTalk_procTask1(  hDlgTalk,  pMsgTask->iTaskId,  CONST_imOp_recv_accept,  NULL,  &param  );  
												//  EnableWindow(  hDlgTalk,  TRUE  );
												if  (  pAutoAnswer->uiCmd_autoAnswer  !=  CONST_ruleCmd_permitAndFullscreen  )  {
													if  (  hFore  )  SetForegroundWindow(  hFore  );					
													}
												else  {	//  2010/11/28
													  if  (  !m_var.av.taskInfo.bTaskExists  )  {
														  if  (  !dlgTalk_get_usLayoutType_local(  hDlgTalk  )  )  {
															  //  2011/10/04	
															  if  (  pProcInfo->cfg.policy.ucbRunAsAdvertisingPlayer  )  {
																  HWND  hWnd_forPrompt  =  NULL;
																  int  iWndContentType  =  0;
																  dlgTalk_findWndForPrompt(  hDlgTalk,  &m_var,  &hWnd_forPrompt,  &iWndContentType  );
																  if  (  hWnd_forPrompt
																	  &&  !pFuncs->pf_bFullScreen_wnd(  hWnd_forPrompt,  iWndContentType  )  )  								  
																  {
																	  PostMessage(  hWnd_forPrompt,  WM_COMMAND,  MAKEWPARAM(  ID_fullScreen,  0  ),  0  );
																	  SetForegroundWindow(  hWnd_forPrompt  );									  
								  
																  }							  
															  }
						  
														  }					  
													  }									
												}											
											}				

											memset(  &pAutoAnswer->task,  0,  sizeof(  pAutoAnswer->task  )  );
											
											if  (  !m_var.av.taskInfo.bTaskExists  )  {
												//  2013/03/03
												askToRefreshLayout_mgr(  hDlgTalk  );
			
											}
											
											//  2010/12/30. 注意：这里实际上是错的，应该让notification对iTaskId敏感。这里应该根据iTaskId来删除通知，因为有的通知如文字消息只能在窗口看见后删除。						
											removeNotification(  &m_var.addr.idInfo  );
											
											//
			

		
										}
										//
										}								
										//
							  else  if  (  pContent->transferAvInfo.uiTaskType  ==  CONST_imTaskType_shareMediaFile  )  {	//  2010/12/20
	  								    //  2016/02/15								  
										BOOL  bPermitted  =  FALSE;
										
										if  (  bAutoAccepted_avCall(  hDlgTalk,  &pQMemObj->rules,  pContent->transferAvInfo.uiTaskType  )  )  {
											bPermitted  =  TRUE;								  
										}
										//
										if  (  bPermitted  )
										{
											CQySyncFlg  syncFlg;
											
											//
											if  (  !bAppX64(  )  )  {
												if  (  m_var.av.taskInfo.bTaskExists
													&&  m_var.av.taskInfo.ucbVideoConference
													&&  m_var.av.taskInfo.ucbStarter
													&&  m_var.av.taskInfo.mosaicMaker.video.resObj.uiObjType  )
												{
													if  (  bTaskExists_sendingResource(  &m_var,  NULL,NULL,  NULL,  NULL,  NULL,  NULL  )  )  {
														_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "for win32 app, only one resource task can be active, so task can't be auto answered"  )  );
														showInfo_open0(  0,  0,  tBuf  );
														showNotification_open(  0,  0,  0,  tBuf  );
														goto  errLabel;
													}
													int  nScreens  =  0;
													int  nMediaFiles  =  0;
													int  iTaskId_recvdResource  =  0;
													if  (  bTaskExists_recvResource(  &m_var,  &nScreens,  &nMediaFiles,  NULL,  NULL,  NULL,  &iTaskId_recvdResource  )  )  {
														if  (  nScreens  +  nMediaFiles  >  1
															||  iTaskId_recvdResource  !=  pMsg->task.iTaskId  )
														{
															_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "for win32 app, only one resource task can be active, so task can't be auto answered"  )  );
															showInfo_open0(  0,  0,  tBuf  );
															showNotification_open(  0,  0,  0,  tBuf  );
															goto  errLabel;
														}
													}
						
												}												
											}

											//  2014/12/09
											pParam->bTaskFound  =  TRUE;
											if  (  syncFlg.sync(  &m_var.autoAnswer.bInProgress_autoAnswer  )  )  goto  errLabel;
											
											memset(  &autoAnswer,  0,  sizeof(  autoAnswer  )  );

											autoAnswer.uiCmd_autoAnswer  =  pQMemObj->rules.uiCmd_autoAnswer_mediaFile;
											autoAnswer.task.iTaskId  =  pMsg->task.iTaskId;
											autoAnswer.task.iTaskStatus  =  pMsg->task.iStatus;
											autoAnswer.task.bTaskNeedAutoAnswered  =  TRUE;
											

											//
											TASK_autoAnswer  *  pAutoAnswer  =  &autoAnswer;					
											//	
											//if  (  pAutoAnswer->task.bTaskNeedAutoAnswered  )  	
		
											MIS_MSG_TASK  *  pMsgTask  =  findTaskInProcessQ(  &m_var,  pAutoAnswer->task.iTaskId  );
											if  (  !pMsgTask  )  goto  errLabel;
			
											//			
											{
												HWND	hFore	=	GetForegroundWindow(  );
												//  EnableWindow(  hDlgTalk,  FALSE  );
												PARAM_dlgTalk_procTask  param;
												memset(  &param,  0,  sizeof(  param  )  );
												dlgTalk_procTask1(  hDlgTalk,  pMsgTask->iTaskId,  CONST_imOp_recv_accept,  NULL,  &param  );  
												//  EnableWindow(  hDlgTalk,  TRUE  );
												if  (  pAutoAnswer->uiCmd_autoAnswer  !=  CONST_ruleCmd_permitAndFullscreen  )  {					
													if  (  hFore  )  SetForegroundWindow(  hFore  );					
													}
												else  {	//  2010/11/28					  
													  if  (  !m_var.av.taskInfo.bTaskExists  )  {						  
														  if  (  !dlgTalk_get_usLayoutType_local(  hDlgTalk  )  )  {
															  //  2011/10/04								  
															  if  (  pProcInfo->cfg.policy.ucbRunAsAdvertisingPlayer  )  {								  
																  HWND  hWnd_forPrompt  =  NULL;
																  int  iWndContentType  =  0;								  
																  dlgTalk_findWndForPrompt(  hDlgTalk,  &m_var,  &hWnd_forPrompt,  &iWndContentType  );								  
																  if  (  hWnd_forPrompt									  
																	  &&  !pFuncs->pf_bFullScreen_wnd(  hWnd_forPrompt,  iWndContentType  )  )  								  
																  {											  
																	  PostMessage(  hWnd_forPrompt,  WM_COMMAND,  MAKEWPARAM(  ID_fullScreen,  0  ),  0  );										  									  
																	  SetForegroundWindow(  hWnd_forPrompt  );									  								  
																  }							  
															  }						  
														  }					  
													  }				
												}							
											}
														
											memset(  &pAutoAnswer->task,  0,  sizeof(  pAutoAnswer->task  )  );
														
											if  (  !m_var.av.taskInfo.bTaskExists  )  {
												//  2013/03/03				
												askToRefreshLayout_mgr(  hDlgTalk  );			
											}
														
											//  2010/12/30. 注意：这里实际上是错的，应该让notification对iTaskId敏感。这里应该根据iTaskId来删除通知，因为有的通知如文字消息只能在窗口看见后删除。			
											removeNotification(  &m_var.addr.idInfo  );

			
											//
										}
							  }
							  //
							  }
						  else  if  (  pContent->uiType  ==  CONST_imCommType_queryCustomerServiceOfficerReq  )  {		//  2011/04/08
									#if  0
										 if  (  m_var.addr.uiObjType  ==  CONST_objType_messenger  )  {						//  暂时只有messenger才可以
											 m_var.av.autoAnswer_customerService.uiCmd_autoAnswer  =  CONST_ruleCmd_permit;	//  这里暂时采用不需要设置就可以自动响应的办法，因为在服务器上实际上设置的客服可以认为是已经授权了。
											 m_var.av.autoAnswer_customerService.task.iTaskId  =  pMsg->task.iTaskId;
											 m_var.av.autoAnswer_customerService.task.iTaskStatus  =  pMsg->task.iStatus;
											 m_var.av.autoAnswer_customerService.task.bTaskNeedAutoAnswered  =  TRUE;
										 }
									#endif
										 //  2014/12/09											
										 //m_var.av.autoAnswer.bTaskExists  =  TRUE;
									}
						  else  if  (  pContent->uiType  ==  CONST_imCommType_transferFileReq  )  {  //  2015/08/04
									if  (  bSupported_fileServer(  pQyMc  )  )  {

										CQySyncFlg  syncFlg;											//  2014/12/09
										
										pParam->bTaskFound  =  TRUE;
										if  (  syncFlg.sync(  &m_var.autoAnswer.bInProgress_autoAnswer  )  )  goto  errLabel;

										//
										MIS_MSG_TASK  *  pMsgTask  =  &pMsg->task;
										//
										PARAM_dlgTalk_procTask  param;											
										memset(  &param,  0,  sizeof(  param  )  );
										dlgTalk_procTask1(  hDlgTalk,  pMsgTask->iTaskId,  CONST_imOp_recv_accept,  NULL,  &param  );  
										

										}
									else  {  //  2015/8/06
										  if  (  pContent->transferFileReq.usSubtype  ==  CONST_procOfflineResSubtype_download  )  {
											  CQySyncFlg  syncFlg;											//  2014/12/09
										
											  pParam->bTaskFound  =  TRUE;										
											  if  (  syncFlg.sync(  &m_var.autoAnswer.bInProgress_autoAnswer  )  )  goto  errLabel;
											  									
											  //
											  MIS_MSG_TASK  *  pMsgTask  =  &pMsg->task;									
											  //
											  PARAM_dlgTalk_procTask  param;											
											  memset(  &param,  0,  sizeof(  param  )  );
											  dlgTalk_procTask1(  hDlgTalk,  pMsgTask->iTaskId,  CONST_imOp_recv_accept,  NULL,  &param  );  
											  //
											  QY_MESSENGER_ID  idInfo_peer;
											  idInfo_peer.ui64Id  =  pContent->transferFileReq.idInfo_logicalPeer.ui64Id;
											  //
											  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->procOfflineRes_mgr.mems  );  i  ++  )  {
												   PROC_offlineRes_mem  *  pMem  =  &pShadowMgr->procOfflineRes_mgr.mems[i];
												   if  (  !IsWindow(  pMem->hTool_offlineRes  )  )  continue;
												   if  (  idInfo_peer.ui64Id  !=  pMem->idInfo_req.ui64Id  )  continue;
												   //
												   tmpiRet  =  SendMessage(  pMem->hTool_offlineRes,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsgTask  );
												   //
												   if  (  tmpiRet  ==  CONST_qyWmRc_ok  )  {												   							   
													   pContent->transferFileReq.hTool_offlineRes  =  pMem->hTool_offlineRes;
													   break;
												   }
											  }
											  //pMsgTask->uiTranNo
										
										  }
									}
									//
									}
						  else  {
								#ifdef  __DEBUG__
										//  其他的contentType不需要自动处理. 2011/04/08
								#endif
						  }

					  }


				  }

				  break;
			default:
					break;
	}



	iErr  =  0;
errLabel:

	return  0;	//  returns 0 in order to process every msg
}


//  2014/12/09
int  dlgTalk_chkAutoAnswer(  HWND hDlgTalk  )
{
	int  iErr  =   -1;
	
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pm_var		=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk,  _T(  "dlgTalk_mytimeProc"  )  );
	if  (  !pm_var  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "dlgTalk_myTimerProc: getDlgTalkVar returns NULL"  )  );
		#endif
		return  -1;
	}
	DLG_TALK_var	&	m_var		=	*pm_var;


	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;

	//
	showInfo_open0(  0,  0,  _T(  "dlgTalk_chkAutoAnswer"  )  );
	
	//
	PARAM_chkAutoAnswer  param;
	memset(  &param,  0,  sizeof(  param  )  );

	qTraverse(  m_var.m_pProcessQ,  tmpHandler_chkAutoAnswer,  hDlgTalk,  &param  );

	if  (  !param.bTaskFound  )  {
		m_var.autoAnswer.bTaskExists  =  FALSE;
		}
	else  {
		  m_var.autoAnswer.bTaskExists  =  TRUE;
	}

	iErr  =  0;
errLabel:

	return  iErr;
}

//

//
QY_DMITEM  CONST_taskRespInfoMemStateTable[]  =
{
	{	CONST_taskRespInfoMemState_join,		(TCHAR*)_T(  "join"  ),		},
	{	CONST_taskRespInfoMemState_leave,		(TCHAR*)_T(  "leave"  ),	},
	//
	{	CONST_taskRespInfoMemState_ok,			(TCHAR*)_T(  "state_ok"  ),  },
	{	CONST_taskRespInfoMemState_warning,		(TCHAR*)_T(  "state_warning"  ),	},
	{	CONST_taskRespInfoMemState_notInConf,	(TCHAR*)_T(  "not in conf"  ),		},
	//
	{	CONST_taskRespInfoMemState_offline,		(TCHAR*)_T(  "offline"  ),			},
	{	-1,		},
};



//
int  logConfLog(  TASK_respInfo_mem  *  pRespInfoMem,  int  iState,  time_t  tTime_state  )
{
	int  iErr  =  -1;

	if  (  !iState  ||  !tTime_state  )  {
		return  -1;
	}

	//
	CONF_logs  *  pLogs  =  &pRespInfoMem->var.logs;

	//
	if  (  pRespInfoMem->var.logs.usCnt  >=  mycountof(  pRespInfoMem->var.logs.mems  )  )  {
		showInfo_open0(  0,  _T(  "logConfLog"  ),  _T(  "failed, logs full"  )  );
		goto  errLabel;
	}

	//
	if  (  pLogs->usCnt  >=  1  )  {
		CONF_log  *  pLastLog  =  NULL;	
		pLastLog  =  &pLogs->mems[pLogs->usCnt  -  1];	
		switch  (  pLastLog->iState  )  {
				case  CONST_taskRespInfoMemState_ok:
				case  CONST_taskRespInfoMemState_warning:
					  switch  (  iState  )  {
							  case  CONST_taskRespInfoMemState_ok:
							  case  CONST_taskRespInfoMemState_warning:
								    iErr  =  0;  goto  errLabel;
								    break;
							  default:
									  break;
					  }
					  break;
				default:
						break;
		}
	}


	//	
	CONF_log  *  pLog  =  &pRespInfoMem->var.logs.mems[pRespInfoMem->var.logs.usCnt];
	pLog->iState  =  iState;
	pLog->tTime  =  tTime_state;
	pRespInfoMem->var.logs.usCnt  ++  ;

	
errLabel:

	return  iErr;
}



//
int  sendConfState(  HWND  hDlgTalk_mgr,  DLG_TALK_var  *  pMgrVar  )
{
	int  iErr  =  -1;
	int  i;
	QY_MC* pQyMc = pMgrVar->pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMgrVar->pMisCnt;
	if  (  !pMisCnt  )  return  -1;
	CTX_qm_thread  *  pCtx  =  &pQyMc->gui.ctx_gui_thread;

	//
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return  -1;
	if  (  !pMgrVar->av.taskInfo.bTaskExists  )  return  -1;
	if  (  !pMgrVar->av.taskInfo.ucbVideoConference  )  return  -1;
	if  (  !pMgrVar->av.taskInfo.ucbStarter  )  return  -1;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;

	//
	ROUTE_sendLocalAv		route  =  {0};

	//
	if  (  !pShadowMgr->av.confMgrInfo.usCnt  )  return  0;

	
	//
	QY_MESSENGER_ID  idInfo_dst;
	for  (  i  =  0;  i  <  pShadowMgr->av.confMgrInfo.usCnt;  i  ++  )  {			
		 idInfo_dst.ui64Id  =  pShadowMgr->av.confMgrInfo.mems[i].idInfo.ui64Id;				   
		 if  (  idInfo_dst.ui64Id  ==  pMgrVar->av.taskInfo.idInfo_starter.ui64Id  )  continue;
		 addToMsgrs_sendLocalAv(  pProcInfo,  pMisCnt,  &idInfo_dst,  FALSE,  &route, false,  _T(  "sendConfState.3906"  ));
	}

	//
	if  (  !pMgrVar->av.ucbGot_iIndex_sharedObj_localAv  )  goto  errLabel;
	TASK_respInfo  *  pRespInfo  =  get_respInfo(  pProcInfo,  pMgrVar->av.taskInfo.iIndex_taskInfo  );
	if  (  !pRespInfo  )  goto  errLabel;

	//
	//
	CONF_state  cs  =  {0};
	cs.uiType  =  CONST_imCommType_confState;
	cs.idInfo_imGrp_related.ui64Id  =  pMgrVar->addr.idInfo.ui64Id;

	//
	BOOL  bSendAll  =  FALSE;

	//
	if  (  !pMgrVar->av.taskInfo.confState.uiTranNo_retrieveAll  ||  pMgrVar->av.taskInfo.confState.ucbNeed_sendAll  )  {
		//
		bSendAll  =  TRUE;
		//
		pMgrVar->av.taskInfo.confState.ucbNeed_sendAll  =  FALSE;
		//
		pMgrVar->av.taskInfo.confState.uiTranNo_retrieveAll  =  getuiNextTranNo(  0,  0,  0  );
		pMgrVar->av.taskInfo.confState.usSeqNo_retrievePart  =  0;
		}
	else  {
		  pMgrVar->av.taskInfo.confState.usSeqNo_retrievePart  ++  ;
	}
	//
	cs.uiTranNo_retrieveAll  =  pMgrVar->av.taskInfo.confState.uiTranNo_retrieveAll;
	cs.usSeqNo_retrievePart  =  pMgrVar->av.taskInfo.confState.usSeqNo_retrievePart;

	//
	unsigned  char			ucFlg						=	CONST_commFlg_routeTalkData;	//  0;
	int  channelType  =  CONST_channelType_media;
	TCHAR  tBuf[128];
	
	//
	unsigned  short  usMaxCnt_perSnd  =  MAX_confMemStates;
#ifdef  __DEBUG__
		#if  1	//  for TEST
			 //usMaxCnt_perSnd  =  2;
		#endif
#endif
	if  (  usMaxCnt_perSnd  >  MAX_confMemStates  )  usMaxCnt_perSnd  =  MAX_confMemStates;

	//
	for  (  i  =  0;  i  <  pRespInfo->usCnt;  i  ++  )  {
		 TASK_respInfo_mem  *  pMem  =  &pRespInfo->mems[i];
		 //
		 if  (  !bSendAll  )  {
			 if  (  pMem->var.dwLastModifiedTickCnt_usState  <  pMgrVar->av.taskInfo.confState.dwTickCnt_sent  )  continue;
		 }
		 //
		 if  (  cs.usCnt  ==  usMaxCnt_perSnd  )  {
			 
			 //
			 //
			 #ifdef  __DEBUG__
					 #if  1
					 #endif
			 #endif
			 //
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "snd confState: tn_all %d, sn_part %d, %d mems, sn %d"  ),  cs.uiTranNo_retrieveAll,  (  int  )cs.usSeqNo_retrievePart,  (  int  )cs.usCnt,  (  int  )cs.usSeqNo  );
			 if  (  bSendAll  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. all"  ),  tBuf  ); 
			 showInfo_open0(  0,  0,  tBuf  );
			 			 
			 //
			 MACRO_prepareForTran(  );
			 //
			 postMsg2Mgr_mc(  pMisCnt,  &route.route,  CONST_misMsgType_outputTask,  ucFlg,  CONST_qyCmd_sendTask,  tStartTran,  uiTranNo,  0,  (  char  *  )&cs,  sizeof(  cs  ),  0,  0,  channelType  );    
			 		 
			 //
			 cs.usCnt  =  0;
			 cs.usSeqNo  ++  ;
		 }
		 CONF_mem_state  *  pCms  =  &cs.mems[cs.usCnt];
		 pCms->idInfo.ui64Id  =  pMem->idInfo.ui64Id;
		 pCms->usState  =  pMem->var.usState_byDlgTalk;
		 cs.usCnt  ++  ;
	}

	//
	#ifdef  __DEBUG__
			#if  1
			#endif
	#endif
	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "snd confState: tn_all %d, sn_part %d, %d mems, sn %d, end"  ),  cs.uiTranNo_retrieveAll,  (  int  )cs.usSeqNo_retrievePart,  (  int  )cs.usCnt,  (  int  )cs.usSeqNo  );
	if  (  bSendAll  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. all"  ),  tBuf  ); 
	showInfo_open0(  0,  0,  tBuf  );
			 

	//
	MACRO_prepareForTran(  );
	//
	cs.ucbEnd  =  TRUE;
	//
	postMsg2Mgr_mc(  pMisCnt,  &route.route,  CONST_misMsgType_outputTask,  ucFlg,  CONST_qyCmd_sendTask,  tStartTran,  uiTranNo,  0,  (  char  *  )&cs,  sizeof(  cs  ),  0,  0,  channelType  );    


	//  2017/09/17
	pMgrVar->av.taskInfo.confState.dwTickCnt_sent  =  myGetTickCount(  pCtx  );



	iErr  =  0;
errLabel:
	return  iErr;
}




//
int  dlgTalk_chkTaskRespInfo(  HWND  hDlgTalk_mgr,  DLG_TALK_var  *  pMgrVar,  TASK_respInfo  *  pRespInfo,  BOOL  bNeedFullChk  )
{
	int  iErr  =  -1;
	QY_MC* pQyMc = pMgrVar->pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli  *  pProcInfo   =  QY_GET_procInfo_isCli(  );
	int  i;
	MIS_CNT  *  pMisCnt  =  pMgrVar->pMisCnt;
	if  (  !pMisCnt  )  {
		return  -1;
	}


	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return  -1;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;

	//
#if  0
	traceLog((TCHAR*)  _T(  "dlgTalk_chkTaskRespInfo called, bNeedFullChk %d"  ),  bNeedFullChk  );
	showInfo_open0(  0,  _T(  "chkTaskRespInfo"  ),  _T(  ""  )  );
#endif
	
	//
	CTX_qm_thread  *  pCtx  =  &pQyMc->gui.ctx_gui_thread;
	//
	time_t  tNow;  time(  &tNow  );
	DWORD  dwTickCnt  =  myGetTickCount(  pCtx  );

	int  iElapseInS  =  0;
	unsigned  short  usState  =  0;
	time_t  tTime_state  =  0;

	//
	int  tmp_usCnt  =  min(  pRespInfo->usCnt,  MAX_taskRespInfoMems  );

	//
	BOOL  bNeedRefreshed  =  FALSE;


	//
	if  (  bNeedFullChk  )  {

		//
		for  (  i  =  0;  i  <  tmp_usCnt;  i  ++  )  {
			 TASK_respInfo_mem  *  pMem  =  &pRespInfo->mems[i];
			 //
			 usState  =  get_respInfoMem_state(  pMisCnt,  tNow,  pMem,  &tTime_state  );
			 //
			 if  (  pMem->var.usState_byDlgTalk  !=  usState  )  {
				 pMem->var.usState_byDlgTalk  =  usState;
				 pMem->var.dwLastModifiedTickCnt_usState  =  dwTickCnt;
				 //
				 logConfLog(  pMem,  usState,  tTime_state  );
				 //
				 bNeedRefreshed  =  TRUE;
			 }
		}

		//  这里怎么办，是遍历所有的GRPMEM来刷新状态呢，还是如果
		for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
			 TALKER_shadow_mgrMem  *  pShadow  =  &pShadowMgr->shadows[i];
			 if  (  !IsWindow(  pShadow->hShadow  )  )  continue;
			 //
			 refreshGrpMemListStatus(  pShadow->hShadow  );
		}

		}
	else  {

		  //  遍历所有的respInfo, 查找bNeedCalc.计算好，然后遍历所有的GRPMEM来刷新状态
		  for  (  i  =  0;  i  <  tmp_usCnt;  i  ++  )  {
			   TASK_respInfo_mem  *  pMem  =  &pRespInfo->mems[i];
			   if  (  !pMem->var.bNeedCalc_byProcTaskDataResp  )  continue;
			   //
			   usState  =  get_respInfoMem_state(  pMisCnt,  tNow,  pMem,  &tTime_state  );
			   //
			   if  (  pMem->var.usState_byDlgTalk  !=  usState  )  {
				 pMem->var.usState_byDlgTalk  =  usState;
				 pMem->var.dwLastModifiedTickCnt_usState  =  dwTickCnt;
				 //
				 logConfLog(  pMem,  usState,  tTime_state  );
				 //
				 bNeedRefreshed  =  TRUE;
			   }			 
		  }
		  //
		  if  (  bNeedRefreshed  )  {
			  //	
			  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {			 
				   TALKER_shadow_mgrMem  *  pShadow  =  &pShadowMgr->shadows[i];
			 	   if  (  !IsWindow(  pShadow->hShadow  )  )  continue;
				   //
				   //  这里的处理，为了高效，需要利用dwLastModifiedTickCnt来遍历所有的从pGrpMemListStatus->dwLastTickCnt以来未刷新的respInfoMem成员
				   //  然后bsearch grpMemIndex，更新grpMemStatus.
				   //  这里为了省事，先调用refreshGrpMemListStatus. 效率不够好。 2017/09/10
			 	   //
				   refreshGrpMemListStatus(  pShadow->hShadow  );
			  }
		  }
	}
	
	//
	BOOL  bNeedSend  =  FALSE;
	int  iElapseInMs  =  dwTickCnt  -  pMgrVar->av.taskInfo.confState.dwTickCnt_sent;
	if  (  abs(  iElapseInMs  )  >  2  *  60  *  1000  )  bNeedSend  =  TRUE;
	//
	if  (  bNeedRefreshed  ||  bNeedSend  )  {
		sendConfState(  hDlgTalk_mgr,  pMgrVar  );
	}
#ifdef  __DEBUG__
		//  for TEST
		//sendConfState(  hDlgTalk_mgr,  pMgrVar,  pRespInfo  );
#endif


	//
	iErr  =  0;
errLabel:
	return  iErr;
}


//
int postToCloseWnd(HWND  hWnd,  TCHAR* hint)
{
	TCHAR  tBuf[128];
	if (!hint)  hint = (TCHAR*)_T("");

	//
	_sntprintf(  tBuf,mycountof(tBuf),_T("postToCloseWnd now. %s"), hint);
	showInfo_open0(0, 0, tBuf);
	PostMessage(hWnd, WM_CLOSE, 0, 0);

	//
	return  0;
}

 
//
  VOID CALLBACK dlgTalk_myTimerProc(  HWND hDlgTalk,  UINT uMsg,  UINT_PTR idEvent,  DWORD dwTime  )
{
	int							len				=	0;
	CHelp_getDlgTalkVar			help_getDlgTalkVar;
	DLG_TALK_var			*	pm_var		=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk,  _T(  "dlgTalk_mytimeProc"  )  );
	if  (  !pm_var  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "dlgTalk_myTimerProc: getDlgTalkVar returns NULL"  )  );
		#endif
		return;
	}
	DLG_TALK_var	&	m_var		=	*pm_var;
	QY_MC* pQyMc = m_var.pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	//  2016/04/01
	DWORD  dwTickCnt_start_myTimerProc  =  GetTickCount(  );
	TCHAR  tBuf[128];


	m_var.loopCtrl_timer  ++  ;
		
	//		
	CQySyncFlg   syncFlg;
	if  (  syncFlg.sync(  &m_var.syncFlgs.bInSequence  )  )  {				
		showInfo_open0(  0,  0,  _T(  "dlgTalk_myTimeProc failed, bLocked already"  )  );
		goto  errLabel;									
	}

	//  traceLogA(  (char*)  "myTimerProc here."  );
#ifdef  __DEBUG__
		//  2013/07/31
		//  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_myTimerProc: %I64u, %d, %d "  ),  m_var.addr.idInfo.ui64Id,  m_var.addr.uiTranNo_shadow,  m_var.addr.iNo_debug  ); 
		//
	getCurrentCameraName(hDlgTalk, tBuf, mycountof(tBuf));
	//
#endif

	//  2012/05/17
	if  (  !m_var.guiData.bFinished_createCtrls  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "dlgTalk_myTimerProc(  ) failed: bFinished_createCtrls is false, %I64u"  ),  m_var.addr.idInfo.ui64Id  );
		#endif
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_myTimerProc failed, bFinished_createCtrls false.%I64u"  ),  m_var.addr.idInfo.ui64Id  );
		goto  errLabel;
	}

	//
	pProcInfo->do_talk_OnTimer(hDlgTalk,  &m_var);

	//
	if  (  !(  m_var.loopCtrl_timer  %  10  )  )  {	//  -1ÊÇÎªÁËµÚ0´Î¾ÍÆð×÷ÓÃ¡£
		if  (  m_var.addr.uiObjType  ==  CONST_objType_webGuest  )  {
			CQyMalloc						mallocObj_req;
			REFRESH_WEBCONTACTS_INFO	*	pReq			=	(  REFRESH_WEBCONTACTS_INFO  *  )mallocObj_req.mallocf(  sizeof(  REFRESH_WEBCONTACTS_INFO  )  );
			if  (  pReq  )  {
		
				#ifdef  __DEBUG__
						qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%I64u start to refresh"  ),  m_var.addr.idInfo.ui64Id  );
				#endif

				memset(  pReq,  0,  sizeof(  pReq[0]  )  );
				pReq->uiType  =  CONST_imCommType_refreshWebContactsInfo;
				pReq->ucbNeedDetail  =  TRUE;
				//
				pReq->mems[pReq->usCnt].idInfo.ui64Id  =  m_var.addr.idInfo.ui64Id;
				pReq->mems[pReq->usCnt].uiLogonId  =  m_var.addr.uiLogonId;
				pReq->usCnt  ++  ;
				//
				len  =  offsetof(  REFRESH_WEBCONTACTS_INFO,  mems  )  +  pReq->usCnt  *  sizeof(  pReq->mems[0]  );
				//
				postMsg2Mgr_mc(  m_var.pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_refreshRecentFriendsReq,  0,  0,  0,  (  char  *  )pReq,  len,  NULL,  0,  0,  NULL,  FALSE  ); 
			}
		}
	}

	//  2008/10/22
	//  if  (  m_var.ucbNewMsgArrives  )  
	if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
		TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
		if  (  pShadowMgr->ucbNewMsgArrives  )  {
			#ifdef  __DEBUG__
					if  (  pProcInfo->cfg.debugStatusInfo.ucbDebug_newMsgArrives  )  {
						traceLog((TCHAR*)  _T(  "dlgTalk_myTimeProc: bNewMsgArrives true"  )  );
					}
			#endif

			int  i;
			for  (  i  =   0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {										
				 if  (  pShadowMgr->shadows[i].hShadow  &&  isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  {
					 CHelp_getDlgTalkVar	help_getDlgTalkVar;
					 DLG_TALK_var  *  pVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  pShadowMgr->shadows[i].hShadow  );
					 if  (  pVar  )  {											
						 //			
						 activateWnd(  pShadowMgr->shadows[i].hShadow,  *pVar  );
					 }										
				 }
			}
			//
#if  0		//  ts的闪烁有问题，可能需要activate主窗口才行 2014/07/14
			if  (  !m_var.guiData.param.bNeedNotShowWnd  )  {
				activateWnd(  hDlgTalk,  m_var  );
			}
#endif
		}

		//  2014/12
		if  (  isQFull(  m_var.m_pProcessQ  )  )  {
			TCHAR  tBuf[128];
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "talker %I64u' processQ is full, please close the talker and reopen it"  ),  m_var.addr.idInfo.ui64Id  );
			showNotification(  0,  0,  0,  0,  0,  0,  tBuf  );
			showInfo_open0(  0,  0,  tBuf  );
			//  2017/09/24
			safeTcsnCpy(  tBuf,  m_var.promptToClose.tHint,  mycountof(  m_var.promptToClose.tHint  )  );
			PostMessage(  hDlgTalk,  WM_COMMAND,  MAKEWPARAM(  ID_promptToClose,  0  ),  0  );
			goto  errLabel;

		}
	}

	//  2009/06/01
	if  (  !(  m_var.loopCtrl_timer  %  4  )  )  {
		if  (  m_var.av.taskInfo.bTaskExists  
			&&  m_var.pMisCnt  
				&&  m_var.pMisCnt->refreshVideoConferenceActiveMems.bNeedRefreshed
					&&  m_var.pMisCnt->refreshVideoConferenceActiveMems.iTaskId  ==  m_var.av.taskInfo.iTaskId  
						&&  !m_var.av.taskInfo.ucbStarter  )  
		{				
			m_var.pMisCnt->refreshVideoConferenceActiveMems.bNeedRefreshed  =  FALSE;
			m_var.pMisCnt->refreshVideoConferenceActiveMems.dwLastTickCnt_refreshed  =  GetTickCount(  );

			//
			#ifdef  __DEBUG__
					traceLogA(  (char*)  "send to starter to ask for activeMems info."  );
			#endif
			requestToRefreshActiveMems_videoConferenceOthers(  hDlgTalk  );
		}
	}

	//  2009/10/18
	int  loopCtrl_timer_dlgTalk_chkRecvdTasks  =  pProcInfo->cfg.loopCtrl_timer_dlgTalk_chkRecvdTasks;
	if  (  m_var.needChkTasks.bNeedChkRecvdTasks  )  loopCtrl_timer_dlgTalk_chkRecvdTasks  =  2;//5;
	//  
	if  (  !(  m_var.loopCtrl_timer  %  loopCtrl_timer_dlgTalk_chkRecvdTasks  )  )  {
		dlgTalk_chkRecvdTasks(  hDlgTalk,  m_var  );
	}
	//
	if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
		if  (  !(  m_var.loopCtrl_timer  %  5  )  )  {
			confStarter_chkActiveMems(  hDlgTalk,  m_var  );
			//
			confServ_chkConf(  pQyMc,  hDlgTalk,  m_var  );
		}
	}
	//
	int  loopCtrl_chkAsAdvertisingPlayer  =  pProcInfo->cfg.loopCtrl_timer_dlgTalk_chkRecvdTasks;
	if  (  !(  m_var.loopCtrl_timer  %  loopCtrl_chkAsAdvertisingPlayer  )  )  {
		BOOL  bNeedClose  =  FALSE;
		TCHAR  tHint[128];

		//
		if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
			TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
			
			//  2013/11/14
			if  (  pProcInfo->cfg.policy.ucbRunAsAdvertisingPlayer  )  {
				//
				bNeedClose  =  FALSE;
				if  (  !dlgTalk_chkAsAdvertisingPlayer(  hDlgTalk,  &m_var,  &bNeedClose,  tHint,  mycountof(  tHint  )  )  )  {
					if  (  bNeedClose  )  {
						qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  tHint  );
						//
						if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hzj  )  PostMessage(  hDlgTalk,  WM_CLOSE,  0,  0  );
						else  {
							  _sntprintf(  m_var.promptToClose.tHint,  mycountof(  m_var.promptToClose.tHint  ),  _T(  "No av exists, window will be closed"  )  );
							  PostMessage(  hDlgTalk,  WM_COMMAND,  MAKEWPARAM(  ID_promptToClose,  0  ),  0  );
						}
					}
				}
			}
			
			//  2015/08/04
			if  (  bSupported_fileServer(  pQyMc  )  )  {			
				//
				bNeedClose  =  FALSE;
				if  (  !dlgTalk_chkFileServer(  hDlgTalk,  &m_var,  &bNeedClose,  tHint,  mycountof(  tHint  )  )  )  {
					if  (  bNeedClose  )  {
						qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  tHint  );
						_sntprintf(  m_var.promptToClose.tHint,  mycountof(  m_var.promptToClose.tHint  ),  _T(  "No file task exists, window will be closed"  )  );
						PostMessage(  hDlgTalk,  WM_COMMAND,  MAKEWPARAM(  ID_promptToClose,  0  ),  0  );
					}
					
				}
			}

			//  2018/10/25
#if  0
			if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hzj  )  {
				if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
					if  (  !m_var.av.taskInfo.bTaskExists  )  {
						//
						#ifdef  __DEBUG__
								traceLog((TCHAR*)  _T(  "for hzj: close talk if taskinfo.bTaskExists is false"  )  );
						#endif
						//
						PostMessage(  hDlgTalk,  WM_CLOSE,  0,  0  );
					}
				}
			}
#endif

		}

		//
		if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {
			//  2017/08/28
#if  0
			if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_bjyz  )  {
				//
				bNeedClose  =  FALSE;
				if  (  !dlgTalk_chk_yz(  hDlgTalk,  &m_var,  &bNeedClose,  tHint,  mycountof(  tHint  )  )  )  {
					if  (  bNeedClose  )  {
						qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  tHint  );
						_sntprintf(  m_var.promptToClose.tHint,  mycountof(  m_var.promptToClose.tHint  ),  _T(  "No av task exists, window will be closed"  )  );
						PostMessage(  hDlgTalk,  WM_COMMAND,  MAKEWPARAM(  ID_promptToClose,  0  ),  0  );
					}
					
				}
			}
#endif
		}

	}

	//  2017/01/10
	int  nTimes_chkTalkerRules  =  5;
	int  nTimes_chkDynBmps  =  30;

	//
	if  (  isTalkerShadowMgr(  m_var.addr  ) )  {
		TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
		if  (  pShadowMgr->quickToRetrieveImg.ucbOn  )  {
			pShadowMgr->quickToRetrieveImg.ucbOn  =  FALSE;
			//
			nTimes_chkTalkerRules  =  1;
			nTimes_chkDynBmps  =  1;
		}
	}

	//  2012/04/24
	if  (  !(  m_var.loopCtrl_timer  %  nTimes_chkTalkerRules  )  )  {
		if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
		
			//  2013/02/15
			chkTalkerRules(  hDlgTalk,  &m_var  );
		}
	}

	//  2012/04/20
	if  (  !(  m_var.loopCtrl_timer  %  nTimes_chkDynBmps  )  )  {
		DWORD			dwTickCnt			=					GetTickCount(  );
		int  k;

		//
		{
			CAP_IMAGES  &  images  =  m_var.av.peerZone.images;
			int  idc  =  m_var.av.idc_peer;				 
			int  idc_dst  =  0;
			for  (  k  =  0;  k  <  mycountof(  images.mems  );  k  ++  )  {						   
				 CAP_IMAGE	*	pImg	=  &images.mems[k];
				 if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;
  						   
				 //  is active
				 if  (  dwTickCnt  -  pImg->dwTickCnt_lastDrawing  <  15  *  1000  )  continue;
				
				 //  2015/10/24
				 if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
					 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
					 int  ii;				 
					 for  (  ii  =  0;  ii  <  mycountof(  pShadowMgr->vwRuleCmd.dynBmpRules  );  ii  ++  )  {
						 TALKER_dynBmp  *  pTalkerDynBmp  =  &pShadowMgr->talkerDynBmps[ii];
						 if  (  pTalkerDynBmp->taskInfo.iTaskId  ==  pImg->iTaskId  )  {
							 memset(  &pTalkerDynBmp->taskInfo.srcInfo,  0,  sizeof(  pTalkerDynBmp->taskInfo.srcInfo  )  );
						 }
					 }
				 }
				 //
				 old_freeCapImageByTaskId(  hDlgTalk,  idc,  pImg->iTaskId,  &images,  old_M_GetDlgItem(  hDlgTalk,  idc_dst  )  );
				 //  2015/10/24
				 askToRefreshLayout_mgr(  hDlgTalk  );

				 //  2015/10/18
				 if  (  isTalkerShadowMgr(  m_var.addr  )  )  {					
					 dyn_d3dWall_refreshImgs(  hDlgTalk,  (TCHAR*)_T("dlgTalk_myTimerProc.4382"  ));
				 }

			}
		}
		{	// 2015/09/09
			CAP_IMAGES  &  images  =  m_var.av.meZone.images;
			int  idc  =  m_var.av.idc_me;
			int  idc_dst  =  idc;
			for  (  k  =  0;  k  <  mycountof(  images.mems  );  k  ++  )  {						   
				 CAP_IMAGE	*	pImg	=  &images.mems[k];
				 if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;
  						   
				 //  is active
				 if  (  dwTickCnt  -  pImg->dwTickCnt_lastDrawing  <  15  *  1000  )  continue;
					
				 old_freeCapImageByTaskId(  hDlgTalk,  idc,  pImg->iTaskId,  &images,  old_M_GetDlgItem(  hDlgTalk,  idc_dst  )  );
				 
				 //  2015/10/18
				 if  (  isTalkerShadowMgr(  m_var.addr  )  )  {					
					 dyn_d3dWall_refreshImgs(  hDlgTalk,  (TCHAR*)_T(  "dlgTalk_myTimerProc.4402"  ));
				 }

			}
		}

		{  // 2015/09/09
			CAP_IMAGES  &  images  =  m_var.av.otherZone.images;
			int  idc  =  m_var.av.idc_other;
			int  idc_dst  =  idc;
			for  (  k  =  0;  k  <  mycountof(  images.mems  );  k  ++  )  {						   
				 CAP_IMAGE	*	pImg	=  &images.mems[k];
				 if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;
  						   
				 //  is active
				 if  (  dwTickCnt  -  pImg->dwTickCnt_lastDrawing  <  15  *  1000  )  continue;
					
				 old_freeCapImageByTaskId(  hDlgTalk,  idc,  pImg->iTaskId,  &images,  old_M_GetDlgItem(  hDlgTalk,  idc_dst  )  );
				 
				 //  2015/10/18
				 if  (  isTalkerShadowMgr(  m_var.addr  )  )  {					
					 dyn_d3dWall_refreshImgs(  hDlgTalk,  (TCHAR*)_T(  "dlgTalk_myTimerProc.4423"  ));
				 }

			}
		}
		int  j;
		for  (  j  =  0;  j  <  mycountof(  m_var.av.bgWall.mems  );  j  ++  )
		{	// 2015/09/09
			CAP_IMAGES  &  images  =  m_var.av.bgWall.mems[j].images;
			int  idc  =  m_var.av.idc_bgWall_conf;
			int  idc_dst  =  idc;
			for  (  k  =  0;  k  <  mycountof(  images.mems  );  k  ++  )  {						   
				 CAP_IMAGE	*	pImg	=  &images.mems[k];
				 if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;
  						   
				 //  is active
				 if  (  dwTickCnt  -  pImg->dwTickCnt_lastDrawing  <  15  *  1000  )  continue;
					
				 old_freeCapImageByTaskId(  hDlgTalk,  idc,  pImg->iTaskId,  &images,  old_M_GetDlgItem(  hDlgTalk,  idc_dst  )  );
				 
				 //  2015/10/18
				 if  (  isTalkerShadowMgr(  m_var.addr  )  )  {					
					 dyn_d3dWall_refreshImgs(  hDlgTalk,  (TCHAR*)_T(  "dlgTalk_myTimerProc.4445"  ));
				 }

			}
		}



		//
		if  (  isTalkerShadowMgr(  m_var.addr  )  )  {

			TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
			if  (  !pShadowMgr  )  goto  errLabel;

			//  先要清理shadow中没用的.主要是指dynBmp规则的,又没有墙或者视频数据来刷新的
			dlgTalk_chkShadows(  hDlgTalk,  &m_var  );

			//
			if  (  !bMeOnline(  pQyMc  )  )  {
				#ifdef  __DEBUG__
						traceLog((TCHAR*)  _T(  "dlgTalk_myTimeProc: Can't connect to server, don't need to check rule."  )  );
				#endif
				}
			else  {

				  //
				  BOOL			bImgRestarted		=					FALSE;

				  int  i;
				  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->vwRuleCmd.dynBmpRules  );  i  ++  )  {
					  if  (  !pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.uiObjType  )  continue;

					  chkToViewDynBmp(  hDlgTalk,  &m_var,  i,  FALSE,  &bImgRestarted  );				  					   					   
				  }

				  //
				  if  (  pShadowMgr->vwRuleCmd.ucbViewGps  )  {
					  dlgTalk_chkToViewGps(  pQyMc,  hDlgTalk,  m_var  );
				  }

				  //
				  if  (  bImgRestarted  )  qmcApplyForChkingTasks_gui(  pQyMc  );		

			}

		}
	}

	//  2016/03/15
#if  0
	if  (  !(  m_var.loopCtrl_timer  %  10  )  )  {
		if  (  isTalkerShadowMgr(  m_var.addr  )  )  {

			//  2014/09/25
			if  (  m_var.av.taskInfo.bTaskExists  &&  m_var.av.taskInfo.ucbStarter  &&  m_var.av.taskInfo.ucbVideoConference  )  {
				confStarter_chkBgWall(  hDlgTalk,  &m_var  );
			}

		}
	}
#endif


	//  2012/05/14
	if  (  isTalkerShadowMgr(  m_var.addr  )  )  {

		TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
		if  (  !pShadowMgr  )  goto  errLabel;
		
		//  2012/05/18		
		if  (  m_var.guiData.param.bNeedNotShowWnd  )  {

			if  (  m_var.dwTickCnt_start_noShadow  ||  !(  m_var.loopCtrl_timer  %  10  )  )  {
				DWORD	dwTickCnt	=	GetTickCount(  );

				//  2014/01/11
				BOOL  bNeedClose  =  FALSE;
				int	 nWaitInMs  =  70;

				//
				BOOL  tmpbCanClose  =  FALSE;
				if  (  !bTalkerShadowExists(  hDlgTalk,  &tmpbCanClose  )  
					||  tmpbCanClose  )
				{
					if  (  !bProcOfflineResToolExists_mgr(  &m_var  )  
						&&  !IsWindow(  pShadowMgr->ptz.hWnd_ptzControl  )
						)  
					{				
						bNeedClose  =  TRUE;
					}
				}

				//  2018/11/11
				if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hzj  )  {
					bNeedClose  =  FALSE;
				}
				
				//
				if  (  !bNeedClose  )  {
					m_var.dwTickCnt_start_noShadow  =  0;
					}
				else  {
					  //
					  if  (  !m_var.dwTickCnt_start_noShadow  )  m_var.dwTickCnt_start_noShadow  =  dwTickCnt;
					  else  {
						    if  (  dwTickCnt  -  m_var.dwTickCnt_start_noShadow  >  nWaitInMs  )  {
								qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_myTimeProc (%I64u), no shadow exists, close window now"  ),  m_var.addr.idInfo.ui64Id  );
								PostMessage(  hDlgTalk,  WM_CLOSE,  0,  0  );
								goto  errLabel;
							}
					  }
				}
		
			}
		
		}
		
		//  2010/09/07
		if  (  m_var.autoAnswer.bTaskExists  )  
		{
			dlgTalk_chkAutoAnswer(  hDlgTalk  );	
		}

		//  2017/09/08
		if  (  m_var.av.taskInfo.bTaskExists  
			&&  m_var.av.taskInfo.ucbStarter
			)
		{
			BOOL  bNeedFullChk  =  !(  m_var.loopCtrl_timer  %  20  );
			QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  m_var.av.taskInfo.iIndex_taskInfo  );
			if  (  pTaskInfo  )  {
					TASK_respInfo  *  pRespInfo  =  &pTaskInfo->var.taskRespInfo;
					if  (  pRespInfo->bNeedCalc_byProcTaskDataResp  ||  bNeedFullChk  )  {
						pRespInfo->bNeedCalc_byProcTaskDataResp  =  FALSE;
						//
						dlgTalk_chkTaskRespInfo(  hDlgTalk,  &m_var,  pRespInfo,  bNeedFullChk  );
				}
			}

			//  2017/09/17
			if  (  m_var.av.taskInfo.confState.ucbNeed_sendAll  )  {
				sendConfState(  hDlgTalk,  &m_var  );  
			}

			//
			if  (  !(  m_var.loopCtrl_timer  %  5  )  )  {
				if  (  m_var.av.taskInfo.ucbVideoConference
					&&  m_var.av.taskInfo.usConfType  !=  CONST_usConfType_consult  )
				{
					if  (  !dyn_bD3dUsing(  pProcInfo,  NULL  )  )  {
						if  (  pQyMc->iCustomId  !=  CONST_qyCustomId_hzj
							&&  pQyMc->iCustomId  !=  CONST_qyCustomId_hbwj  )  
						{
							showNotification(  0,  0,  0,  0,  0,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_3dWallMustBeOpen  )  );  // _T(  "3d wall must be open during a meeting."  )  );
						}
					}
				}
			}
		}
		//  2017/09/17
		if  (  !(  m_var.loopCtrl_timer  %  5  )  )  {
			if  (  m_var.av.taskInfo.bTaskExists 
				&&  !m_var.av.taskInfo.ucbStarter
				&&  pShadowMgr->av.ucbMeConfMgr  )
			{
				if  (  !m_var.av.taskInfo.confState.uiTranNo_retrieveAll  )  {
					send_confState_retrieveAll_req(  hDlgTalk,  &m_var,  _T(  "because tn_retrieveAll is 0"  )  );
				}
			}
		}
	


	}


	//
	if (isTalkerShadowMgr(m_var.addr)) {
		//
		if (m_var.av.taskInfo.bTaskExists) {
			m_var.chkConfStatus.nTimes_noConf = 0;
		}
		else {
			m_var.chkConfStatus.nTimes_noConf++;
		}
		if (pProcInfo->cfg.ucb_closeTalkIfNoConf) {
			if (m_var.chkConfStatus.nTimes_noConf > 10) {
				_sntprintf(tBuf, mycountof(tBuf), _T("talk%I64u: need be closed, nTimes_noConf %d"), m_var.addr.idInfo.ui64Id,  m_var.chkConfStatus.nTimes_noConf);
				showInfo_open0(0, 0, tBuf);
				postToCloseWnd(hDlgTalk, tBuf);
			}
		}
	}



	//
#ifdef  __DEBUG__
		//	qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_myTimeProc (%I64u,%d), bShouldQuit, close window now"  ),  m_var.addr.idInfo.ui64Id,  m_var.addr.uiTranNo_shadow  );								

#endif
	//  2017/09/23
	if  (  m_var.bShouldQuit1  )  {					
		qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_myTimeProc (%I64u,%d), bShouldQuit, close window now"  ),  m_var.addr.idInfo.ui64Id,  m_var.addr.uiTranNo_shadow  );								
		PostMessage(  hDlgTalk,  WM_CLOSE,  0,  0  );
		goto  errLabel;
	}

	//  2017/08/23		
	if  (  m_var.remoteAssist.bNeedSend_lastMouseEvent  )  {
		dlgTalk_processPointerEvent(  hDlgTalk,  m_var.remoteAssist.lastMouseEvent.x,  m_var.remoteAssist.lastMouseEvent.y,  m_var.remoteAssist.lastMouseEvent.nFlags,  m_var.remoteAssist.lastMouseEvent.bMouseMove,  TRUE  );
	}

	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: %d, %s: %d kbps "  ),  _T(  "下行"  ),  pProcInfo->status.netStat.ins.uiInSpeedInKbps,  _T(  "上行"  ),  pProcInfo->status.netStat.ins.uiOutSpeedInKbps  );
	SetDlgItemText(  hDlgTalk,  m_var.guiData.iIDC_STATIC_status,  tBuf  );



#ifdef  __DEBUG__
#endif

	//  2011/08/01
	#ifndef  __WINCE__
			 QM_SHM_CMDS	*	pShmCmds  =  QY_GET_shmCmds(  pProcInfo  );
			 if  (  pShmCmds  )  {
				 if  (  pShmCmds->ucbDaemonDemo  )  {
					 if  (  m_var.av.taskInfo.bTaskExists  
						 &&  m_var.av.ucbGot_iIndex_sharedObj_localAv  )  
					 {
						 QY_SHARED_OBJ	*	pSharedObj	=	getSharedObjByIndex(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv  );
						 if  (  pSharedObj
							 &&  pSharedObj->dwTickCnt_start  )  
						 {
							 int	n	=	GetTickCount(  )  -  pSharedObj->dwTickCnt_start;
							 n  =  n  /  1000;
							 //
							 if  (  n  >  pQyMc->uiMaxTimeInS_videoConference  -  1  *  60  )  {
								 if  (  !(  m_var.loopCtrl_timer  %  15  )  )  {
									 PostMessage(  hDlgTalk,  WM_COMMAND,  MAKEWPARAM(  ID_popupASpecialPrompt,  0  ),  0  );    
									 MessageBeep(  -1  );
								 }
							 }
							 //
							 if  (  n  >  pQyMc->uiMaxTimeInS_videoConference  )  {
								 unsigned  short  usOp  =  m_var.av.taskInfo.ucbStarter  ?  CONST_imOp_send_cancel  :  CONST_imOp_recv_cancel;
								 PARAM_dlgTalk_procTask  param;
								 memset(  &param,  0,  sizeof(  param  )  );
								 //
								 dlgTalk_procTask1(  hDlgTalk,  m_var.av.taskInfo.iTaskId,  usOp,  NULL,  &param  );  
								 //  这里要做一个明显的提示
								 PostMessage(  hDlgTalk,  WM_COMMAND,  MAKEWPARAM(  ID_popupASpecialPrompt,  0  ),  0  );    
							 }
						 }
					 }
				 }
			 }
	#endif


#ifdef  __DEBUG__
		//  traceLog((TCHAR*)  _T(  "toShareScreen %s"  ),  findTaskInProcessQ(  m_var,  0,  0,  TRUE  )  ?  _T(  "exists"  )  :  _T(  "none"  )  );
			 pProcInfo->do_test(hDlgTalk,CONST_qyWndContentType_talker);
#endif

errLabel:
	//
	if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
		if  (  pProcInfo->cfg.debugStatusInfo.ucbShowDlgTalkStatus  )  {
			TCHAR  tBuf[128]  =  _T(  ""  );
			DWORD  dwTickCnt_end_myTimerProc  =  GetTickCount(  );
			int  iDiffInMs  =  dwTickCnt_end_myTimerProc  -  dwTickCnt_start_myTimerProc;
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "dlgTalk %I64u, myTimeProc: nElapseInMs %dms"  ),  m_var.addr.idInfo.ui64Id,  iDiffInMs  );
			showInfo_open0(  0,  0,  tBuf  );			
		}
	}

	//
	return;
}






//
  VOID CALLBACK dlgTalk_myTimerProc_guiMsgArrive(HWND hDlgTalk, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
  {
	  int							len = 0;
	  CHelp_getDlgTalkVar			help_getDlgTalkVar;
	  DLG_TALK_var* pm_var = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hDlgTalk, _T("dlgTalk_mytimeProc"));
	  if (!pm_var) {
#ifdef  __DEBUG__
		  traceLog((TCHAR*)_T("dlgTalk_myTimerProc: getDlgTalkVar returns NULL"));
#endif
		  return;
	  }
	  DLG_TALK_var& m_var = *pm_var;
	  QY_MC* pQyMc = m_var.pQyMc;// QY_GET_GBUF();
	  MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	  if (!pProcInfo)  return;

	  //  2016/04/01
	  DWORD  dwTickCnt = myGetTickCount(mynull);
	  TCHAR  tBuf[128];

	  int  iDiffInMs = 0;

	  iDiffInMs = dwTickCnt - m_var.lastTickCnt_guiMsgArrive;

	  //_sntprintf(tBuf, mycountof(tBuf), _T("timer_guiMsgArrive: elaplse %dms. last_lParam %d"), iDiffInMs,  m_var.last_lParam_guiMsgArrive);
	  //traceLog(tBuf);
	  if (iDiffInMs < 1000 && iDiffInMs  >  33) {
		  LPARAM  lParam = m_var.last_lParam_guiMsgArrive;

		  //doWnd_guiMsgArrive(pProcInfo, lParam, hDlgTalk, FALSE, m_var.pMsgBuf_doWnd_guiMsgArrive);

		  //
#ifdef  __DEBUG__
		  if (0) {
			  _sntprintf(tBuf, mycountof(tBuf), _T("补充: timer_guiMsgArrive: elaplse %dms. last_lParam %d"), iDiffInMs,  m_var.last_lParam_guiMsgArrive);
			  showInfo_open0(0, 0, tBuf);
		  }
#endif
	  }

	  //
	  return;

  }


 int  tmp_getMenuDesc(  QY_MC  *  pQyMc,  int  idc,  AV_COMPRESSOR_CFG  &  avCompressor,  TCHAR  *  tBuf,  unsigned  int  cnt  )  
{
	//QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	PolicyAvParams  *  pAvParams  =  pProcInfo->p_gAvParams;	//  QY_GET_PolicyAvParams(  );
	if  (  !pAvParams  )  return  -1;
	PolicyAvParams  &  gAvParams  =  *pAvParams;
	
	_sntprintf(  tBuf,  cnt,  _T(  "%s:"  ),  getResStr(  0,  &pQyMc->cusRes,  idc  )  );  

	if  (  avCompressor.audio.common.ucCompressors  )  {
		int  iDelayInMs  =  MACRO_getDelayInMs(  avCompressor.audio.playCfg  );
		_sntprintf(  tBuf,  cnt,  _T(  "%s  %s %.1fs"  ),  tBuf,  qyGetDesByType1(  gAvParams.pAudioCompressorsTable,  avCompressor.audio.common.ucCompressors  ),  iDelayInMs  /  1000.  );

		//		
		_sntprintf(  tBuf,  cnt,  _T(  "%s,"  ),  tBuf  );

	}


	if  (  avCompressor.video.common.iWidth_pic  ||  avCompressor.video.common.iHeight_pic  )  {
		_sntprintf(  tBuf,  cnt,  _T(  "%s %d * %d"  ),  tBuf,  avCompressor.video.common.iWidth_pic,  avCompressor.video.common.iHeight_pic  );
	}
	_sntprintf(  tBuf,  cnt,  _T(  "%s %dfps"  ),  tBuf,  (  int  )avCompressor.video.common.usMaxFps_toShareBmp  );
	_sntprintf(  tBuf,  cnt,  _T(  "%s  %s"  ),  tBuf,  qyGetDesByType1(  gAvParams.pVideoCompressorsTable,  avCompressor.video.common.ucCompressors  )  );

	if  (  avCompressor.video.common.iAvgBitrate  )  {
		_sntprintf(  tBuf,  cnt,  _T(  "%s %dk"  ),  tBuf,  avCompressor.video.common.iAvgBitrate  /  1000  );
	}
	if  (  avCompressor.video.common.iTargetUsage  )  {
		_sntprintf(  tBuf,  cnt,  _T(  "%s  %s"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iTargetUsageTable  ),  avCompressor.video.common.iTargetUsage  )  );
	}

	return  0;
}

#define		tmp_getMenuDesc_screen		tmp_getMenuDesc
#define		tmp_getMenuDesc_mediaFile	tmp_getMenuDesc
#define		tmp_getMenuDesc_mediaDevice	tmp_getMenuDesc
#define		tmp_getMenuDesc_mediaDevice_unresizable	tmp_getMenuDesc



  //  2012/05/03. 这个函数还有一个问题,就是dlgTalk_make_capStuff可能在发起会议后又被调用.这之前时,如果发生设备接入移出,那么主talker新作的capstuff和影子就不同了.应该刷新下影子窗口
  //  暂时不解决.
 int  dlgTalk_make_capStuff(  HWND  hDlgTalk,  DLG_TALK_var  *  pm_var  )
 {
	 int		iErr	=	-1;
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	 if  (  !pm_var  )  return  -1;

	 if  (  pm_var->pCapStuff  )  return  -1;

	 //
	 if  (  isTalkerShadowMgr(  pm_var->addr  )  )  {
		 DLG_TALK_var  &  m_var  =  *pm_var;
		 //
		 m_var.pCapStuff  =  CAP_STUFF_new(  );
		 if  (  !m_var.pCapStuff  )  goto  errLabel;

		 addDevicesToMenu(  m_var.pCapStuff,  m_var.bIncludeACap,  hDlgTalk  );
		 TCHAR	recorder_sel[MAX_monikerDisplayNameLen  +  1]  =  _T(  ""  );
		 TCHAR	webcam_sel[MAX_monikerDisplayNameLen  +  1]	=  _T(  ""  );
		 getChosenDevice(  recorder_sel,  mycountof(  recorder_sel  ),  webcam_sel,  mycountof(  webcam_sel  ),  m_var.pCapStuff,  m_var.bIncludeACap,  &m_var.iMenuId_selectedAudio,  &m_var.iMenuId_selectedVideo  );  
#if  0	//  如果没有，不取第一个，用缺省那个. 2014/07/31
		 if  (  !m_var.iMenuId_selectedAudio  )  {
			 m_var.iMenuId_selectedAudio  =  ID_MENU_ADEVICE0;
		 }
#endif
		 if  (  !m_var.iMenuId_selectedVideo  )  {
			 m_var.iMenuId_selectedVideo  =  ID_MENU_VDEVICE0;
		 }
		 //  2014/03/01
		 if  (  pProcInfo->cfg.policy.video.uiCamCapType  !=  CONST_camCapType_directX  )  {
			 m_var.iMenuId_selectedVideo  =  0;
		 }
		 //
		 chooseAvDevice(  m_var.pCapStuff,  m_var.bIncludeACap,  hDlgTalk,  NULL,  m_var.iMenuId_selectedAudio  );
		 chooseAvDevice(  m_var.pCapStuff,  m_var.bIncludeACap,  hDlgTalk,  NULL,  m_var.iMenuId_selectedVideo  );

		 }
	 else  {
		   TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pm_var->pShadowInfo;
		   if  (  !pShadow  )  goto  errLabel;
		   CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
		   DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pShadow->hMgr  );
		   if  (  !pMgrVar  )  goto  errLabel;

		   addDevicesToMenu_shadow(  pMgrVar->pCapStuff,  pMgrVar->bIncludeACap,  hDlgTalk  );
		   //
		   chooseAvDevice_shadow(  pMgrVar->pCapStuff,  pMgrVar->bIncludeACap,  hDlgTalk,  NULL,  pMgrVar->iMenuId_selectedAudio  );
		   chooseAvDevice_shadow(  pMgrVar->pCapStuff,  pMgrVar->bIncludeACap,  hDlgTalk,  NULL,  pMgrVar->iMenuId_selectedVideo  );

	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}


 //
  int  old_doSth_afterInitDlgTalk(  HWND  hDlgTalk,  int  iWndContentType  )
  {
	  //
	 DLG_TALK_var  *  pDlgTalkVar  =  NULL;
	 CHelp_getDlgTalkVar	help_getDlgTalkVar;
	 
	
	 pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlgTalk  );
	 if  (  !pDlgTalkVar  )  return  -1;

	 if  (  isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  {
		 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pDlgTalkVar->pShadowInfo;
		 if  (  !pShadowMgr  )  goto  errLabel;

		 //
		 SUBTITLES_cfg  tmpCfg;
		 //
		 int  iCapType  =  CONST_capType_mosaic;
		 getSubtitlesCfg(  iCapType,  0,  0,  &tmpCfg  );  
		 //
		 subtitlesCfg_modify(  &tmpCfg,  GetTickCount(  ),  FALSE,  &pShadowMgr->subtitles.d3dConf,  NULL  );

		 //
#ifdef  __DEBUG__
		 int  i;
		 i  =  9;
#endif
	 }
	 

errLabel:

	  //
	  return  0;
  }




  //
 int  doSth_afterInitDlgMsgTool(  QY_MC  *  pQyMc,  HWND  hDlgMsgTool,  int  iWndContentType  )
 {
	 int		iErr	=	-1;
	 //QY_MC		*	pQyMc	=	QY_GET_GBUF();


	 CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	 //  void  *  pDLG_TALK_var  =  NULL;
	 DLG_TALK_var  *  pDlgTalkVar  =  NULL;
	 CHelp_getDlgTalkVar	help_getDlgTalkVar;
	 
	 HWND  hDlgTalk  =  NULL;
	 
	 if  (  iWndContentType  !=  CONST_qyWndContentType_dlgMsgTool  )  return  -1;	
	 DLG_msgTool_var  *  pDlgMsgToolVar  =  (  DLG_msgTool_var  *  )getDlgMsgToolVar(  hDlgMsgTool  );
	 if  (  !pDlgMsgToolVar  )  return  -1;
	 
	 //	
	 hDlgTalk  =  pDlgMsgToolVar->hDlgTalk;

	
	 pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlgTalk  );
	 if  (  !pDlgTalkVar  )  return  -1;
	 //  DLG_TALK_var  &  m_var  =  *(  DLG_TALK_var  *  )pDLG_TALK_var;

	 if  (  !pDlgTalkVar->guiData.bFinished_createCtrls  )  return  -1;
	 
	
	 //  2012/05/14
	 if  (  !bReady_toShowMsg(  hDlgTalk  )  )  goto  errLabel;

	 HWND  hMgr  =  hDlgTalk;
	 if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  {
		 TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pDlgTalkVar->pShadowInfo;
		 if  (  !pShadow  )  goto  errLabel;
		 hMgr  =  pShadow->hMgr;
	 }
	 DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  hMgr  );
	 if  (  !pMgrVar  )  goto  errLabel;

	 PARAM_PROC_ROW		param;
	
	 memset(  &param,  0,  sizeof(  param  )  );
	 
	 qTraverse(  pMgrVar->m_pProcessQ,  tmpHandler_shadow_displayProcessedMsg,  hDlgTalk,  &param  );

#if  0
	 if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  {		
		 if  (  isTalkerSubtype_canInput(  pDlgTalkVar->iTalkerSubType  )  )  {										 
			 qTraverse(  pMgrVar->m_pProcessQ,  tmpHandler_shadow_displayMsg,  hDlgTalk,  &param  );
		 }
	 }										 								   
	
	 memset(  &param,  0,  sizeof(  param  )  );
	 //
	 param.bScrollIntoView  =  TRUE;													//  ÕâÀïÒª×¢Òâ£ºÒòÎª
	 param.bNewMsg  =  TRUE;		

	 qTraverse(  pMgrVar->m_pProcessQ, tmpHandler_showMsg,  hMgr,  &param  );				//  2007/08/13
#endif

	 if  (  pDlgTalkVar->ucbTaskIdSet  )  activateImTask(  hDlgTalk,  pDlgTalkVar,  pDlgTalkVar->iTaskId_activated  );	//  2006/08/11

	 //
	 if  (  pProcInfo->cfg.policy.ucbSaveMsg  )  {
		 TCHAR	sendDesc[128]  =  _T(  "Note:"  );
		 TCHAR  tNote[128]  =  _T(  ""  );
		 TCHAR	txtContent[128];
		 QY_MESSENGER_ID  idInfo_from;
		 idInfo_from.ui64Id  =  0;

		 //_sntprintf(  sendDesc,  mycountof(  sendDesc  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_note  )  );		  //  _T(  "Note:"  );
		 _sntprintf(  tNote,  mycountof(  tNote  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_logMsg  )  );		  //  _T(  "Message will be saved."  );
		 addToRecentMsg(  hDlgTalk,  pDlgTalkVar,  -1,  0,  mynull,  mynull,  idInfo_from,  sendDesc,  CONST_imOp_says,  0,  (char*)"",  NULL,  tNote,  param.bFollowingRows,  param.bScrollIntoView,  txtContent,  mycountof(  txtContent  )  );
	 }


	 //  2012/05/22
	 if  (  isTalkerSubtype_canInput(  pDlgTalkVar->iTalkerSubType  )  )  {
		 ::PostMessage(   hDlgTalk,  CONST_qyWm_postComm,  CONST_qyWmParam_refreshLayout,  0  );
	 }

	 //
	 iErr  =  0;
errLabel:
	 return  iErr;
	 
}


 int  getMenuStatus_dlgTalk(  QY_MC  *  pQyMc,  void  *  p0,  void  *  p1,  void  *  piStatusParam  )
{
	 int						iErr		=	-1;
	 //  p0;
	 int						iMenuId		=	(  int  )p1;
	 int				*		piStatus	=	(  int  *  )piStatusParam;
	 
	 if  (  !pQyMc  )  return  -1;
	 if  (  !piStatus  )  return  -1;

	 if  (  isIsCli(  pQyMc  )  )  {		 
		 switch  (  iMenuId  )  {
#if  0
				 case  ID_udbNotViewRtsp5:
				 case  ID_udbViewRtsp5:
					   if  (  !bSupported_rtsp(  )  )  {
						   //  skipped
						   goto  errLabel;
					   }
					   break;
#endif
				 case  ID_ucbNotViewGps:
				 case  ID_ucbViewGps:
				 case  ID_notShowGpsData:
				 case  ID_showGpsData:
					   if  (  !bSupported_gps(  pQyMc  )  )  {
						   //  skipped
						   goto  errLabel;
					   }
					   break;
				 default:
						break;
		 }
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
 }



 //
 


  
//
 int  dlgTalk_OnInitDialog(  HWND  hDlgTalk,  void  *  pDLG_TALK_var  )
{
	// TODO: Add extra initialization here
	int							iErr		=	-1;
	DLG_TALK_var			&	m_var		=	*(  DLG_TALK_var  *  )pDLG_TALK_var;

	MC_VAR_isCli				*	pProcInfo	=	QY_GET_procInfo_isCli(  );  //(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	QY_MC					*	pQyMc		=	(  QY_MC  *  )pProcInfo->pQyMc;
	//  QY_SERVICEGUI_INFO		*	pSgi		=	(  QY_SERVICEGUI_INFO  *  )pProcInfo->pSgiParam;
	int							idc;
	BOOL						tmpbRet;
	//
	TCHAR						tBuf[128]	=	_T(  ""  );
#ifndef  __WINCE__
		 RECT						rect;
		 //  CListCtrl				*	pListCtrl	=	NULL;	
		 HWND						hListCtrl	=	NULL;
#endif

	//  2012/05/25
	if  (  pProcInfo->cfg.debugStatusInfo.ucbShowDlgTalkStatus  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_OnInitDialog %I64u, %d enters"  ),  m_var.addr.idInfo.ui64Id,  m_var.addr.uiTranNo_shadow  ); 
	}

	//
	if  (  !m_var.guiData.bInfoSet  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "dlgTalk_OnInitDialog failed, bInfoSet is false"  )  );
		#endif
		MACRO_qyAssert(  0,  _T(  "dlgTalk_OnInitDialog failed"  )  );
		goto  errLabel;
	}

	//  2015/11/15
	QMC_objVar_info  *  pTalkerInfo  =  getQmcObjVarInfoByIndex(  pProcInfo,  m_var.iIndex_talkerInfo  );
	if  (  !pTalkerInfo  ||  !pTalkerInfo->bUsed  )  goto  errLabel;
	pTalkerInfo->var.hWnd  =  hDlgTalk;
	pTalkerInfo->var.idInfo.ui64Id  =  m_var.addr.idInfo.ui64Id;
	pTalkerInfo->var.uiTranNo_shadow  =  m_var.addr.uiTranNo_shadow;

	
	//  2013/07/22. 移到函数起始处
	{
		CQyMalloc									mallocObj;
		MIS_MSG_TALKINGFRIEND_QMC				*	pMsg;
		if  (  !(  pMsg  =	(  MIS_MSG_TALKINGFRIEND_QMC  *  )mallocObj.mallocf(  sizeof(  MIS_MSG_TALKINGFRIEND_QMC  )  )  )  )  goto  errLabel;	
	
		//  ´ÓÕâÀïÆð£¬m_hWnd²ÅÓÐÐ§
		memset(  pMsg,  0,  sizeof(  pMsg[0]  )  );
		pMsg->uiType  =  CONST_misMsgType_talkingFriend_qmc;
		memcpy(  &pMsg->addr,  &m_var.addr,  sizeof(  pMsg->addr  )  );
		//
		pMsg->hWnd  =  hDlgTalk;
		if  (  ::qPostMsg(  pMsg,  sizeof(  pMsg[0]  ),  &m_var.pMisCnt->talkingFriendQ,  _T(  "dlgTalk_OnInitDia"  )))  goto  errLabel;

	}

	//
	 QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  &pQyMc->cusRes  );
	 if  (  !pResMem  )  goto  errLabel;
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	//
	m_var.bUseDirectX  =  pQyMc->cfg.bUseDxSurface;	//  2009/08/06
	//
#if  1  //  def  __APP_qyMc__
		m_var.ucbUseHtmlEdit  =  isTalkerSubtype_canInput(  m_var.iTalkerSubType  );	//  2012/05/17
#elif  defined(  __APP_qyMc_touchscreen__  )
	   m_var.ucbUseHtmlEdit  =  TRUE;
#endif
	   //
	   if (isTalkerShadowMgr(m_var.addr))  m_var.ucbUseHtmlEdit = false;

	   //
	//  2014/04/06
	m_var.ucbAutoClip = false;// TRUE;
	m_var.ucbAutoClip_me  =  FALSE;		//  2016/02/17

	//  2017/09/30
#ifdef  __DEBUG__
		//m_var.ucbAutoClip  =  FALSE;
#endif


	//  2010/09/03
	DWORD	dwStyle	=	GetWindowLong(  hDlgTalk,  GWL_STYLE  );
	dwStyle  |=  WS_CLIPCHILDREN;
#if  0
#ifdef  __APP_qyMc_touchscreen__
		dwStyle  |=  WS_CHILD;				//  2011/07/11
#endif
#endif
	SetWindowLong(  hDlgTalk,  GWL_STYLE,  dwStyle  );

	//  2014/02/04
	m_var.dwTickCnt_created  =  myGetTickCount(  NULL  );

	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "talker%I64u"  ),  m_var.addr.idInfo.ui64Id  );
	if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
		m_var.m_pProcessQ  =  genericQNew(  tBuf,  tBuf,  0,  pProcInfo->cfg.envVar.usMaxQNodes_dlgTalk_processQ,  mymalloc,  myfree  );
		if  (  !m_var.m_pProcessQ  )  goto  errLabel;
	}


	//  
	{
		void					*	pDb				=		NULL;
#ifndef  __NOTSUPPORT_DB__
		QY_MESSENGER_INFO			messengerInfo;
		QY_MESSENGER_REGINFO		regInfo;
		IM_GRP_INFO					grpInfo;

		CQnmDb						db;
		if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
		pDb  =  db.m_pDbMem->pDb;
		//
		if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDbFuncs,  pDb,  pQyMc->cfg.db.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  m_var.addr.misServName,  &m_var.addr.idInfo,  0,  &messengerInfo,  &regInfo,  NULL,  NULL  )  )  {
			memset(  &messengerInfo,  0,  sizeof(  messengerInfo  )  );
			memset(  &regInfo,  0,  sizeof(  regInfo  )  );
			//
			if  (  m_var.iTalkUsage  ==  CONST_talkUsage_doConf  )  {
				//
				qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Messenger (%I64u) not found in contact list. will be used as a doConf grp."  ),  m_var.addr.idInfo.ui64Id  );
				//
				m_var.addr.uiObjType  =  CONST_objType_imGrp;
				//
				messengerInfo.uiType  =  m_var.addr.uiObjType;
				messengerInfo.idInfo.ui64Id  =  m_var.addr.idInfo.ui64Id;
				//
				regInfo.addr.idInfo.ui64Id  =  m_var.addr.idInfo.ui64Id;

				}
			else  {
				  //
				  if  (  !m_var.ucbGuest  )  {	//  2011/04/09. 对视频客服，允许不在数据库中的访问请求。
					  //  2012/05/23
					  qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Messenger (%I64u) not found in contact list. will be used as a tmp msgr."  ),  m_var.addr.idInfo.ui64Id  );
					  m_var.ucbTmpMsgr  =  TRUE;
					  //
					  //m_var.addr.uiObjType  =  CONST_objType_messenger;
					  m_var.addr.uiObjType  =  CONST_objType_tmpMsgr;		//  2018/11/11. 可能是组，也可能是messenger.
					  //  2015/08/11
					  messengerInfo.uiType  =  m_var.addr.uiObjType;
					  messengerInfo.idInfo.ui64Id  =  m_var.addr.idInfo.ui64Id;

					  //
					  regInfo.addr.idInfo.ui64Id  =  m_var.addr.idInfo.ui64Id;			
				  }
			}

			//
			//  if  (  !m_var.ucbGuest  )  qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Messenger (%I64u) not found in contact list"  ),  m_var.addr.idInfo.ui64Id  );
			}
		else  {	//  2008/11/11
			  m_var.addr.uiObjType  =  messengerInfo.uiType;
			  //
			  if  (  !regInfo.addr.idInfo.ui64Id  )  {		//  2012/05/07. 如果没有用户注册信息,这里需要补上idInfo
				  regInfo.addr.uiObjType  =  messengerInfo.uiType;
				  regInfo.addr.idInfo.ui64Id  =  messengerInfo.idInfo.ui64Id;
			  }
		}
#else

		QM_OBJQ_MEM				mem;
		QMEM_MESSENGER_CLI	*	pQMemObj;

		if  (  findQMemByKey(  pProcInfo->pSgiParam,  (  QM_OBJQ  *  )m_var.pMisCnt->pObjQ,  &m_var.addr.idInfo,  &mem  )  )  {
			traceLog((TCHAR*)  _T(  "dlgTalk_OnInitDialog failed, findQMemByKey failed."  )  );
			goto  errLabel;
		}
		if  (  !mem.pQMemObj  )  goto  errLabel;
		
		pQMemObj  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
		m_var.addr.uiObjType  =  pQMemObj->uiType;

#endif

#ifndef  __NOTSUPPORT_DB__
		//  if  (  regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  )  )  goto  errLabel;
		
		if  (  m_var.addr.uiObjType  ==  CONST_objType_tmpGrp  )  {
			//  
			m_var.guiData.ucbShowImGrpMems  =  TRUE;
			//
			m_var.iLvType_memList  =  CONST_qyQueryType_tmpGrpMemList;		//  
			m_var.uiDefaultCmd_memList  =  ID_qyProperties;
			//
			_sntprintf(  m_var.talkerDesc,  mycountof(  m_var.talkerDesc  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_tempGroup  )  );
			_sntprintf(  m_var.displayName,  mycountof(  m_var.displayName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_tempGroup  )  );
			//
			//  _sntprintf(  m_var.peerDesc,  mycountof(  m_var.peerDesc  ),  _T(  "%s"  ),  m_var.talkerDesc  );

			//
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_tempGroup  )  );
			SetWindowText(  hDlgTalk,  tBuf  );
			//
			SetDlgItemText(  hDlgTalk,  m_var.guiData.iIDC_STATIC_dlgDesc,  tBuf  );

			//  SetDlgItemText(  hDlgTalk,  IDC_STATIC_peerDesc,  m_var.peerDesc  );

			}
		else  if  (  messengerInfo.uiType  ==  CONST_objType_imGrp  )  {
				  //
			      m_var.guiData.ucbShowImGrpMems  =  TRUE;
				  //
				  m_var.iLvType_memList  =  CONST_qyQueryType_talk_imGrpMemList;		//  Ò»°ã·Ö×é  
				  m_var.uiDefaultCmd_memList  =  ID_qyTalk;
				  //
				  //  ½«³ÉÔ±ÁÐ±íÖÐµÄ×´Ì¬ÁÐ¿í¶ÈÉè³É0£¬ÒòÎª²»ÐèÒª, 2008/01/22
				#if  0
				  QY_COLUMNINFO	*	pColumn  =  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_imGrpMemListColumns_isCli  );
				  if  (  pColumn  )  {
					  for  (  ;  pColumn->type  !=  -1;  pColumn  ++  )  {
						   if  (  pColumn->type  ==  CONST_resId_status  )  pColumn->width  =  0;
					  }
				  }
				#endif

				  //
				  if  (  !g_dbFuncs.pf_bGetImGrpInfoBySth(  pDb,  pQyMc->cfg.db.iDbType,  m_var.addr.misServName,  &m_var.addr.idInfo,  &grpInfo  )  )  memset(  &grpInfo,  0,  sizeof(  grpInfo  )  );
				  //
				  if  (  grpInfo.name[0]  )  {
					  _sntprintf(  m_var.talkerDesc,  mycountof(  m_var.talkerDesc  ),  _T(  "%s"  ),  grpInfo.name  );
					  _sntprintf(  m_var.displayName,  mycountof(  m_var.displayName  ),  _T(  "%s"  ),  grpInfo.name  );
					  }
				  else  {
					     _sntprintf(  m_var.talkerDesc,  mycountof(  m_var.talkerDesc  ),  _T(  "(%I64u)"  ),  m_var.addr.idInfo.ui64Id  );
						 _sntprintf(  m_var.displayName,  mycountof(  m_var.displayName  ),  _T(  "(%I64u)"  ),  m_var.addr.idInfo.ui64Id  );
				  }
				  //  _sntprintf(  m_var.peerDesc,  mycountof(  m_var.peerDesc  ),  _T(  "%s"  ),  m_var.talkerDesc  );

				  //
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  m_var.talkerDesc  );
				  if  (  pQyMc->ucbDaemonDemo  &&  pQyMc->ucDays_left  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s (  %s %d %s  )"  ),  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_trialPeriod  ),  (  int  )pQyMc->ucDays_left,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_days  )  );
				  }
				  //
				  #ifdef  __DEBUG__
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u"  ),  tBuf,  m_var.addr.idInfo.ui64Id  );
				  #endif
				  //
				  SetWindowText(  hDlgTalk,  tBuf  );	
				  //				  	
				  SetDlgItemText(  hDlgTalk,  m_var.guiData.iIDC_STATIC_dlgDesc,  tBuf  );

				  //  SetDlgItemText(  hDlgTalk,  IDC_STATIC_peerDesc,  m_var.peerDesc  );

				  m_var.guiData.usGrpSubtype  =  grpInfo.usSubtype;
				  
				  }
		else  {
			  if  (  messengerInfo.uiType  )  {
			  	  MY_REG_DESC					desc;
			  
				  if  (  regInfo2Desc(  0,  &regInfo,  &desc,  m_var.talkerDesc,  mycountof(  m_var.talkerDesc  ),  m_var.displayName,  mycountof(  m_var.displayName  )  )  )  goto  errLabel;
				  if  (  !desc.pSyr[0]  )  {
					  if  (  m_var.addr.uiObjType  ==  CONST_objType_phoneGuest  )  {
						  _sntprintf(  m_var.talkerDesc,  mycountof(  m_var.talkerDesc  ),  _T(  "(%s)"  ),  m_var.addr.wDevIdStr  );
						  _sntprintf(  m_var.displayName,  mycountof(  m_var.displayName  ),  _T(  "(%s)"  ),	 m_var.addr.wDevIdStr  );
					  }
				  }
				  //  _sntprintf(  m_var.peerDesc,  mycountof(  m_var.peerDesc  ),  _T(  " %s \t\t%s\n\n %s \t\t%s\n\n %s \t%s\n"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_STATIC_danWei  ),  desc.pDw,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_STATIC_buMen  ),  desc.pBm,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_STATIC_shiYongRen  ),  desc.pSyr  );
			  }

			  //
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  m_var.talkerDesc  );
			  if  (  pQyMc->ucbDaemonDemo  &&  pQyMc->ucDays_left  )  {
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s (  %s %d %s  )"  ),  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_trialPeriod  ),  (  int  )pQyMc->ucDays_left,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_days  )  );
			  }
			  SetWindowText(  hDlgTalk,  tBuf  );
			  //
			  if  (  m_var.iTalkerSubType  ==  CONST_talkerSubtype_onVWall  )  SetDlgItemText(  hDlgTalk,  m_var.guiData.iIDC_STATIC_dlgDesc,  m_var.displayName  );
			  else  SetDlgItemText(  hDlgTalk,  m_var.guiData.iIDC_STATIC_dlgDesc,  tBuf  );

			  //  SetDlgItemText(  hDlgTalk,  IDC_STATIC_peerDesc,  m_var.peerDesc  );
		}


		if  (  m_var.addr.uiObjType  !=  CONST_objType_tmpGrp  )  {

			if  (  !m_var.ucbGuest
				//&&  !m_var.ucbTmpMsgr  
				)  
			{
				QM_OBJQ_MEM				mem;
				QMEM_MESSENGER_CLI	*	pQMemObj;

				if  (  procQmObjQ(  pProcInfo->pSgiParam,  (  QM_OBJQ  *  )m_var.pMisCnt->pObjQ,  pDb,  pQyMc->cfg.db.iDbType,  m_var.addr.uiObjType,  &messengerInfo,  &mem  )  )  goto  errLabel;
				if  (  !mem.pQMemObj  )  goto  errLabel;
		
				pQMemObj  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
				if  (  pQMemObj  )  {
					if  (  messengerInfo.uiType  )  {
						lstrcpyn(  pQMemObj->displayName,  m_var.displayName,  mycountof(  pQMemObj->displayName  )  );
						lstrcpyn(  pQMemObj->talkerDesc,  m_var.talkerDesc,  mycountof(  pQMemObj->talkerDesc  )  );				  
					}
					//  2014/04/29
					REFRESH_imObjRules_req	req;
					memset(  &req,  0,  sizeof(  req  )  );
					if  (  g_dbFuncs.pf_bGetImObjRulesReq(  pDb,  pQyMc->cfg.db.iDbType,  m_var.pMisCnt->cfg.misServName,  0,  &m_var.addr.idInfo,  NULL,  0,  &req  )  )  {
						imObjRulesReq2Rules(  &req,  &m_var.addr.idInfo,  &pQMemObj->rules  );			
						}
					else  {
						  #ifdef  __DEBUG__
								  traceLog((TCHAR*)  _T(  "dlgTalk_OnInitDialog, bGetImObjRulesReq failed"  )  );
						  #endif		
					}
				}
			}
		}


#else

		getTalkerDesc(  m_var.pMisCnt,  &m_var.addr.idInfo,  tBuf,  mycountof(  tBuf  ),  0,  0  );
		SetWindowText(  hDlgTalk,  tBuf  );
		//
		SetDlgItemText(  hDlgTalk,  m_var.guiData.iIDC_STATIC_dlgDesc,  tBuf  );

#endif
	}
	m_var.guiData.bImGrp  =  (  m_var.addr.uiObjType  ==  CONST_objType_imGrp  );


	//
	//if  (  !m_var.pm_LargeImageList  ||  !m_var.pm_SmallImageList  )  goto  errLabel;



	//
	m_var.nSubItem_status  =  CONST_nSubItem_status;	//  2007/07/17





#ifndef  __WINCE__

	//
	if  (  m_var.guiData.ucbShowImGrpMems  )  {

		//			
		//  
		m_var.idc_talkerList  =  m_var.guiData.iIDC_talkerList;
		m_var.pColumns_talkers  =  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_instantAssistant_talkerListColumns  );
	
		//
		hListCtrl  =  ::GetDlgItem(  hDlgTalk,  m_var.idc_talkerList  );

		//  pListCtrl->ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
		myListCtrl_ModifyStyle(  hListCtrl,  LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL,  0 );
		//  pListCtrl->SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );
		myListCtrl_SetExtendedStyle(  hListCtrl,  LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );
		//
		if (m_var.pm_LargeImageList) {
			//  pListCtrl->SetImageList(  (  CImageList  *  )m_var.pm_LargeImageList,  LVSIL_NORMAL  );
			myListCtrl_SetImageList(hListCtrl, m_var.pm_LargeImageList, LVSIL_NORMAL);
		}
		if (m_var.pm_SmallImageList) {
			//  pListCtrl->SetImageList(  (  CImageList  *  )m_var.pm_SmallImageList,  LVSIL_SMALL  );
			myListCtrl_SetImageList(hListCtrl, m_var.pm_SmallImageList, LVSIL_SMALL);
		}

		//  
		int					i;
		QY_COLUMNINFO	*	pColumns;
		
		LV_COLUMN lvc;
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		
		pColumns  =  m_var.pColumns_talkers;
		for  (  i  =  0;  pColumns[i].type  !=  -1;  i  ++  )  {
					   lvc.iSubItem		=	i;
					   lvc.pszText		=	pColumns[i].label;
					   lvc.cx			=	pColumns[i].width;
					   lvc.fmt			=	pColumns[i].fmt;
					   myListCtrl_InsertColumn(  hListCtrl,  i,  &lvc  );
		}

		
		//
		m_var.idcList_members  =  m_var.guiData.iIDC_LIST_members;
		m_var.pColumns_members  =  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_imGrpMemListColumns_isCli  );
	
		//  ³ÉÔ±ÁÐ±íµÄ³õÊ¼»¯
		//  pListCtrl  =  (  CListCtrl  *  )CWnd::FromHandle(  GetDlgItem(  hDlgTalk,  m_var.idcList_members  )  );
		hListCtrl  =  GetDlgItem(  hDlgTalk,  m_var.idcList_members  );
		//
		//  pListCtrl->ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
		myListCtrl_ModifyStyle(  hListCtrl,  LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL,  0 );
		//  pListCtrl->SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );
		myListCtrl_SetExtendedStyle(  hListCtrl,  LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );
		//
		//  pListCtrl->SetImageList(  (  CImageList  *  )m_var.pm_LargeImageList,  LVSIL_NORMAL  );
		myListCtrl_SetImageList(  hListCtrl,  m_var.pm_LargeImageList,  LVSIL_NORMAL  );
		//  pListCtrl->SetImageList(  (  CImageList  *  )m_var.pm_SmallImageList,  LVSIL_SMALL  );
		myListCtrl_SetImageList(  hListCtrl,  m_var.pm_SmallImageList,  LVSIL_SMALL  );
		
		//
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		
		pColumns  =  m_var.pColumns_members;
		for  (  i  =  0;  pColumns[i].type  !=  -1;  i  ++  )  {
			 lvc.iSubItem		=	i;
			 lvc.pszText		=	pColumns[i].label;
			 lvc.cx			=	pColumns[i].width;
			 lvc.fmt			=	pColumns[i].fmt;
			 //  pListCtrl->InsertColumn(  i,  &lvc  );
			 myListCtrl_InsertColumn(  hListCtrl,  i,  &lvc  );
		}


		//
		if  (  initMcCtxDisplayedWnd(  pQyMc,  hDlgTalk,  m_var.talkerDesc,  &m_var.displayCtx  )  )  goto  errLabel;
		m_var.bDisplayCtxInited  =  TRUE;

	}


	//

#endif


	m_var.iCol_content		=	2;
	m_var.lColor_active		=	0x00FFFFE0;		//  ¼¤»îÌ¬ÑÕÉ«Îªlight yellow, 2007/07/02
	m_var.lColor_org		=	0x00ffffff;		//  Ô­À´µÄÑÕÉ«Îª°×É«


	//  2012/04/24
	m_var.pShadowInfo  =  TALKER_shadow_new(  isTalkerShadowMgr(  m_var.addr  )  );
	if  (  !m_var.pShadowInfo  )  goto  errLabel;
	//
	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {
		  //
		  TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
		  HWND	hWnd;
		  if  (  findTalker(  pQyMc,  &m_var.addr.idInfo,  &hWnd  )  ) goto  errLabel;
		  pTalkerShadow->hMgr  =  hWnd;
		  }
	else  {
		   //  2015/07/29
		   TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
		   
		   //
		   if  (  m_var.addr.uiObjType  ==  CONST_objType_imGrp  )  {
		   		//
				if  (  !fillConfMgrInfo(  pQyMc,  &m_var.addr.idInfo,  &pShadowMgr->av.confMgrInfo  )
					&&  pShadowMgr->av.confMgrInfo.usCnt  )		
				{
					//
					BOOL  bVal  =  FALSE;		
					if  (  !getVal_bMsgrConfMgr(  &m_var.pMisCnt->idInfo,  &pShadowMgr->av.confMgrInfo,  &bVal  )
						&&  bVal  )  			
					{
						pShadowMgr->av.ucbMeConfMgr  =  TRUE;
					}		
				}
		   }
	}
	//  2015/12/04
	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {
		if  (  !isTalkerInGZone(  hDlgTalk,  CONST_qyWndContentType_talker,  NULL  )  )  {
			showInfo_open0(  0,  0,  _T(  "dlgTalk_OnInitDialog failed, not a gZone mem"  )  );
			#ifdef  __DEBUG__
					MACRO_qyAssert(  0,  _T(  "dlgTalk_OnInitDialog failed, not a gZone mem"  )  );
			#endif
			goto  errLabel;
		}
	}
	//  2015/08/10
	TALKER_shadow_mgr  *  pShadowMgr  =  NULL;
	HWND				hMgr  =  NULL;
	{
		CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
		hMgr  =  hDlgTalk;
		DLG_TALK_var  *  pMgrVar  =  &m_var;
		if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {
			TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
			if  (  !pTalkerShadow  )  goto  errLabel;
			hMgr  =  pTalkerShadow->hMgr;
			pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
			if  (   !pMgrVar  )  goto  errLabel; 
		}
		pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
		if  (  !pShadowMgr  )  goto  errLabel;
		//
		//  2015/08/10		
		if  (  pShadowMgr->av.ucbMeConfMgr  )  {		
			GetWindowText(  hDlgTalk,  tBuf,  mycountof(  tBuf  )  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s (%s)"  ),  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_mgr  )  );
			SetWindowText(  hDlgTalk,  tBuf  );				
		}

		//
#ifdef  __DEBUG__  //  2017/01/05
		#if  1
			GetWindowText(  hDlgTalk,  tBuf,  mycountof(  tBuf  )  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s (sn %d, subtype %d)"  ),  tBuf,  m_var.addr.uiTranNo_shadow,  m_var.iTalkerSubType  );
			SetWindowText(  hDlgTalk,  tBuf  );				
		#endif
#endif
	}

	//  2012/05/08
	if  (  initCapSubWnds(  DEFAULT_usMaxCnt_capSubWnds,  &m_var.subWnds  )  )  goto  errLabel;


#if !defined(  __WINCE__  )  ||  defined(  __TEST__  )  //  2007/10/04, 
	{
		HMENU				hMenu	=	GetMenu(  hDlgTalk  );
		if  (  !hMenu  )  {
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "dlgTalk_OnInitDialog:, hMenu is null"  )  );
			#endif
			//goto  errLabel;
		}


#if  1  //def  __SUPPORT_wndMenu__
		QY_DMITEM		*	pItem;
		unsigned  int		nPos	=	0;

		//
		if  (  m_var.guiData.ucbShowImGrpMems  )  {
			if  (  m_var.guiData.usGrpSubtype  ==  CONST_imGrpSubtype_msg  )  {
				nPos  =  CONST_resId_menu_dlgTalk_imGrp_msg;
			}
			else  {
				nPos  =  CONST_resId_menu_dlgTalk_imGrp;
			}
			}
		else  {
			  nPos  =  CONST_resId_menu_dlgTalk_messenger;
		}

		//
		if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  CONST_resId_popupMenu  )  )  )  {
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "dlgTalk_OnInitDialog failed, pItem CONST_resId_popupMenu is null"  )  );
			#endif
			goto  errLabel;
		}
		if  (  !(  pItem  =  qyGetDmItemByType(  pItem,  nPos,  sizeof(  QY_DMITEM  )  )  )  )  {
			goto  errLabel;
		}
		if (hMenu) {
			if (makeDynaMenu(&pQyMc->cusRes, hMenu, (QY_DMITEM*)pItem->pData, getMenuStatus_dlgTalk, pQyMc, 0))  goto  errLabel;
		}
#endif

		//
		if  (  m_var.guiData.usGrpSubtype  !=  CONST_imGrpSubtype_msg  )  {
			if  (  dlgTalk_make_capStuff(  hDlgTalk,  &m_var  )  )  goto  errLabel;

			//
			#if  1  //  def  __SUPPORT_wndMenu__
			//
			if  (  hMenu  )  {
				AV_COMPRESSOR_CFG	avCompressor;
				int					level;
				//  POLICY_av	policyAv;
				//
				//
				//  2012/01/28
				//  if  (  getPolicyAv(  0,  pProcInfo->cfg.policy.iPolicyAvLevel_req,  &policyAv  )  )  goto  errLabel;
				level  =  0;
				if  (  myGetAvCompressorCfg(  CONST_capType_screen,  0,  0,  level,  &avCompressor  )  )  goto  errLabel;
				idc  =  ID_startShareFullScreen;
				tmp_getMenuDesc_screen(  pQyMc,  idc,  avCompressor,  tBuf,  mycountof(  tBuf  )  );
				//  ModifyMenu(  hMenu,  idc,  MF_BYCOMMAND | MF_STRING,  idc,  tBuf  );


				//  2012/01/28
				level  =  0;
				if  (  myGetAvCompressorCfg(  CONST_capType_mediaFile,  0,  0,  level,  &avCompressor  )  )  goto  errLabel;
				idc  =  ID_startShareMediaFile;
				tmp_getMenuDesc_mediaFile(  pQyMc,  idc,  avCompressor,  tBuf,  mycountof(  tBuf  )  );
				//  ModifyMenu(  hMenu,  idc,  MF_BYCOMMAND | MF_STRING,  idc,  tBuf  );
				//
#if  0
				level  =  0;
				if  (  myGetAvCompressorCfg(  CONST_capType_mediaDevice,  0,  0,  level,  &avCompressor  )  )  goto  errLabel;
				idc  =  ID_startShareMediaDevice;
				tmp_getMenuDesc_mediaDevice(  idc, avCompressor,  tBuf,  mycountof(  tBuf  )  );
				//  ModifyMenu(  hMenu,  idc,  MF_BYCOMMAND | MF_STRING,  idc,  tBuf  );

				level  =  0;
				if  (  myGetAvCompressorCfg(  CONST_capType_mediaDevice,  CONST_subCapType_unresizable,  0,  level,  &avCompressor  )  )  goto  errLabel;
				idc  =  ID_startShareMediaDevice_unresizable;
				tmp_getMenuDesc_mediaDevice(  idc, avCompressor,  tBuf,  mycountof(  tBuf  )  );
#endif		
				//
				idc  =  ID_MENU_selectRtsp;

				QY_REG  reg;				
				reg.hKeyRoot0  =  HKEY_CURRENT_USER;
				lstrcpyn(  reg.rootKey,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  sizeof(  reg.rootKey  )  );
				if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_rtspUrl_selected  ),  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
					CQyString  str  =  CQyString(  _T(  "Rtsp stream: "  )  )  +  tBuf;
					ModifyMenu(  hMenu,  idc,  MF_BYCOMMAND | MF_STRING,  idc,  str  );					
				}
				//  2014/12/12. for test
				if  (  pQyMc->appParams.rtspUrl[0]  )  {
					CQyString  str  =  CQyString(  _T(  "Rtsp stream: "  )  )  +  pQyMc->appParams.rtspUrl;
					ModifyMenu(  hMenu,  idc,  MF_BYCOMMAND | MF_STRING,  idc,  str  );					
				}

				//
				if  (  pProcInfo->cfg.policy.video.uiCamCapType  ==  CONST_camCapType_rtsp  )  {

					//
					unsigned  char  uCheck  =  MF_CHECKED;					
					//
					CheckMenuItem(  hMenu, idc,  uCheck  );
				}

				//  2014/04/10
				if  (  !bSupported_rtsp(  )  )  {
					idc  =  ID_MENU_selectRtsp;
					DeleteMenu(  hMenu,  idc,  MF_BYCOMMAND  );
				}

				//  2014/07/31
				if  (  !pProcInfo->cfg.policy.audio.ucbNot_selectDefaultRecorder  )  {
					idc  =  ID_MENU_selectDefaultRecorder;
					unsigned  char  uCheck  =  MF_CHECKED;					
					CheckMenuItem(  hMenu, idc,  uCheck  );
				}
		}
		//



#endif
	}
	}
#endif

	//  2017/06/30
	if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
		TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
		//
		//  2017/11/03
		getBgWallCfg(  &m_var.addr.idInfo,  &pShadowMgr->bgWall.bgWallCfg  );
		//  2018/01/01. 缺省都不让用
		pShadowMgr->bgWall.bgWallCfg.useBgWall  =  FALSE;
		pShadowMgr->bgWall.bgWallCfg.ucbAddBgWallToConf  =  FALSE;

		//
		//
		if  (  m_var.addr.uiObjType  ==  CONST_objType_imGrp  )  {
			if  (  initGrpConfCtrl(  pQyMc, hDlgTalk,  &pShadowMgr->confCtrl.grpConfCtrl  )  )  {					  
				goto  errLabel;
			}
		}
	}




	//
	if  (  !bUse_imObjView_as_guiWnd(  )  )  {
		if  (  bApp_ts(  pQyMc  )  )  {
			if  (  !m_var.addr.uiTranNo_shadow  )  {
				//  2011/03/01
				if  (  IsWindow(  pProcInfo->g_hVWall  )  )  {
					m_var.ucbOnGlobalVWall  =  TRUE;		//  表明归GlobalVWall管理. 2012/04/03
					BOOL	bThin  =  TRUE;
					//  bThin  =  FALSE;
					makeWndNoBorder(  hDlgTalk,  bThin,  &m_var.hMenu,  NULL  );
					//
					m_var.guiData.ucbShowDlgDesc  =  TRUE;
				}
				}
			else  {  //  2012/04/23. 触摸屏没有影子窗口
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "dlgTalk_OnInitDialog failed, talkerShadow is invalid for ts"  )  );
				  #endif
				  goto  errLabel;
			}
			//  2015/06/06
			if  (  bApp_ts_3d(  pQyMc  )  )  {
				m_var.guiData.ucbShowDlgDesc  =  FALSE;
			}

		}
		}
	else  {
		  //  pc
		  if  (  !m_var.addr.uiTranNo_shadow  )  {			
			  }		
		  else  {
			  //  2011/03/01
			  if  (  m_var.iTalkerSubType  ==  CONST_talkerSubtype_onVWall_global  )  {
				  m_var.ucbOnGlobalVWall  =  TRUE;		//  表明归GlobalVWall管理. 2012/04/03
				  makeWndNoBorder(  hDlgTalk,  TRUE,  &m_var.hMenu,  NULL  );
				  //
				  m_var.guiData.ucbShowDlgDesc  =  TRUE;
			  }
		
			  //  2012/04/23. 影子窗口也没有边框菜单
			  if  (  m_var.iTalkerSubType  ==  CONST_talkerSubtype_onVWall  )  {
				  makeWndNoBorder(  hDlgTalk,  TRUE,  &m_var.hMenu,  NULL  );
				  //
				  m_var.guiData.ucbShowDlgDesc  =  TRUE;
			  }		
		  }
	}




#ifdef  __DEBUG__
		 // m_var.guiData.ucbShowDlgDesc  =  TRUE;
#endif


	//
	//  2010/09/03
	if  (  !pProcInfo->cfg.policy.dlgTalk.ucbShowImGrpMems  )  {
		m_var.guiData.ucbShowImGrpMems  =  FALSE;
	}
	//  2017/08/21
		
	//	
	if  (  m_var.addr.uiObjType  ==  CONST_objType_imGrp  )  {
			int  iRole  =  0;
			getRole_byIdInfo(  &m_var.pMisCnt->idInfo,  &iRole  );
			if  (  iRole  ==  CONST_imObjRole_superAdmin  )  {
				m_var.guiData.ucbShowImGrpMems  =  TRUE;

				//
			}
			//  2017/09/01
			if  (  pShadowMgr->av.ucbMeConfMgr  )  {
				m_var.guiData.ucbShowImGrpMems  =  TRUE;
			}
	}

	//
	if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_bjyz  )  {
		//
		m_var.guiData.snmpbShowMsgBox  =  CONST_snmpFalse;
	}


	//
	if  (  m_var.guiData.ucbShowImGrpMems  )  {
		
		
		//  2014/02/10		
		dlgTalk_loadGrpMems(  hDlgTalk,  &m_var,  _T(  ""  )  );
								
		//  2017/09/02	
		fillTalkerList_func(  hMgr,  hDlgTalk,  &m_var.av.videoConferenceStatus,  m_var.guiData.iIDC_talkerList  );
	}





	//
	m_var.pMsgBuf_doWnd_guiMsgArrive  =  (  MIS_MSGU  *  )mymalloc(  sizeof(  MIS_MSGU  )  );
	if  (  !m_var.pMsgBuf_doWnd_guiMsgArrive  )  goto  errLabel;

	//  2012/05/05
	int  iSize;	
	m_var.av.usCnt_zoneParams  =  pProcInfo->av.usCnt_players;
	iSize  =  m_var.av.usCnt_zoneParams  *  sizeof(  ZONE_PARAM  );
	m_var.av.pZoneParams  =  (  ZONE_PARAM  *  )mymalloc(  iSize  );
	if  (  !m_var.av.pZoneParams  )  goto  errLabel;
	memset(  m_var.av.pZoneParams,  0,  iSize  );


	//
	//

	if  (  m_var.ucbUseHtmlEdit  )  {

#ifdef  __SUPPORT_HTMLEDIT__

		//  if  (  dlgTalk_OnInitDialog_createHtmlEdits(  hDlgTalk,  &m_var  )  )  goto  errLabel;

		if  (  dlgTalk_bShowMsgBox1(  hDlgTalk  )  )  {

			//  2015/06/06
			HWND  hParent  =  hDlgTalk;
		
			//  2015/06/06		
			if  (  !bUse_imObjView_as_guiWnd(  )  )  {
				if  (  bApp_ts_3d(  pQyMc  )  )  {						
					GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
					if  (  !IsWindow(  pGBuf->hWall_d3d  )  )  {
						goto  errLabel;
					}
					hParent  =  pGBuf->hWall_d3d;					  
				}
			}

			//  2014/01/24
			if  (  viewDlgMsgTool_talk(  hParent,  hDlgTalk,  m_var.ucbUseHtmlEdit  )  )  goto  errLabel;

		}
#endif

		//
		m_var.guiData.bFinished_createCtrls  =  TRUE;

		}
	else  {		//  2012/05/17
		  m_var.guiData.bFinished_createCtrls  =  TRUE;
	}

	//



	//  2009/10/19
	dlgTalk_loadTasks(  pQyMc,  hDlgTalk,  m_var  );

	//  2013/02/26
	SCROLLINFO	si;
	si.cbSize  =  sizeof(  SCROLLINFO  );
	si.fMask  =  SIF_ALL;
	si.nMin  =  0;
	si.nMax  =  0;
	si.nPage  =  si.nMax  /  10;
	si.nPos  =  0;
	SetScrollInfo(  hDlgTalk,  SB_HORZ,  &si,  TRUE  );
	SetScrollInfo(  hDlgTalk,  SB_VERT,  &si,  TRUE  );
	
	//  2013/02/27
	m_var.m_layout.usCnt_row  =  1;	
	m_var.m_layout.usCnt_col  =  1;

	//
	if  (  !m_var.m_layout.uiW_pic  ||  !m_var.m_layout.uiH_pic  )  {
		m_var.m_layout.uiW_pic  =  DEFAULT_uiInitW_pic_dlgDesktopsMon;
		m_var.m_layout.uiH_pic  =  DEFAULT_uiInitH_pic_dlgDesktopsMon;
	}
	if (dlgTalk_SetPicRect(hDlgTalk, m_var.m_layout.uiW_pic, m_var.m_layout.uiH_pic, TRUE)) {
		//goto  errLabel;
	}



		 //
#ifndef  __WINCE__
		 if  (  m_var.ucbOnGlobalVWall  )  {
			 }
		 else  {
			  RECT	rc;
			  GetWindowRect(  hDlgTalk,  &rc  );

			  //
#if  0
			  int  iW_dlg  =  rc.right  -  rc.left;
			  int  iH_dlg  =  rc.bottom  -  rc.top;
			  //
			  float  f  =  iW_dlg  *  1.0  /  iH_dlg;
			  f  =  1.7;	//  1.25;
			  if  (  abs(  f  )  <  0.001  )  f  =  1;
			  iH_dlg  =  iW_dlg  /  f;
			  //
			  MoveWindow(  hDlgTalk,  rc.left,  rc.top,  iW_dlg,  iH_dlg,  TRUE  );
#endif
			  int  iW_cli  =  848;
			  int  iH_cli  =  480;
			  //  2014/12/22
			  if  (  m_var.iTalkerSubType  ==  CONST_talkerSubtype_3dTool  )  {
				  iW_cli  =  360;
				  iH_cli  =  440;
				  //
				  SetClientSizeAndPos(  hDlgTalk,  iW_cli,  iH_cli,  rc.left  +  (  rc.right  -  rc.left   -  iW_cli  )  /  2,  rc.top  -  20  );
			  
				  }
			  else  {
					//			  
				    SetClientSize(  hDlgTalk,  iW_cli,  iH_cli  );
			  }
			  //
			  #ifdef  __DEBUG__
					  traceLog((TCHAR*)  _T(  "iW_cli_talk %d, iH_cli_talk %d"  ),  iW_cli,  iH_cli  );
			  #endif


		 }		 
#else
		 centerWnd(  hDlgTalk  );
#endif




	//  sizeAllControls_dlgTalk(  hDlgTalk,  m_var,  NULL  );
		 if (dlgTalk_doLayout(hDlgTalk)) {
			 //goto  errLabel;
		 }


	//  if  (  m_var.ucbGuest  )  
	{
		m_var.uiTimerId  =  ::SetTimer(  hDlgTalk,  (  UINT_PTR  )1,  1000,  dlgTalk_myTimerProc  );	//  ×¢Òâ£ºÕâÀïÓÃ´°¿Ú¾ä±úÀ´µ±timerId, Ä¿µÄ£¬¾ÍÊÇÏ£Íû²»Í¬µÄ´°¿Ú£¬²»Í¬µÄ¶¨Ê±Æ÷¡£
	}

	//
	m_var.uiTimerId_guiMsgArrive = ::SetTimer(hDlgTalk, (UINT_PTR)2, 33, dlgTalk_myTimerProc_guiMsgArrive);


	//  2012/05/17
	//  if  (  !m_var.ucbUseHtmlEdit  )  
	if  (  m_var.guiData.bFinished_createCtrls  )
	{
		pProcInfo->do_talk_afterInit(  hDlgTalk  );
	}

	//
	SetDlgItemText(  hDlgTalk,  m_var.guiData.iIDC_BUTTON_micOff,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_micOff  )  );
	SetDlgItemText(  hDlgTalk,  m_var.guiData.iIDC_STATIC_filter,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_filterKeywords  )  );
	SetDlgItemText(  hDlgTalk,  m_var.guiData.iIDC_BUTTON_permitToSpeak,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_speak  )  );
	SetDlgItemText(  hDlgTalk,  m_var.guiData.iIDC_BUTTON_noSpeaking,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_stopSpeaking  )  );

	//
	EnableWindow(  ::GetDlgItem(  hDlgTalk,  m_var.guiData.iIDC_BUTTON_micOff  ),  FALSE  );

	//  2017/08/21
	SetDlgItemText(  hDlgTalk,  m_var.guiData.iIDC_STATIC_peerInfo,  _T(  " 附加信息"  )  );
	SetDlgItemText(  hDlgTalk,  m_var.guiData.iIDC_BUTTON_shareScreen,  _T(  "共享屏幕"  )  );
	SetDlgItemText(  hDlgTalk,  m_var.guiData.iIDC_BUTTON_controlDesktop,  _T(  "控制屏幕"  )  );



	//
#ifdef  __DEBUG__

#endif

	iErr  =  0;

errLabel:
	
	if  (  iErr  )  {
		m_var.bInitFailed  =  TRUE;
		
		//  2012/05/17
		if  (  !m_var.ucbUseHtmlEdit  )  {
			PostMessage(  hDlgTalk,  WM_CLOSE,  0,  0  );
			//
			showInfo_open0(  0,  _T(  ""  ),  _T(  "dlgTalk_OnInitDialog failed, to Close"  )  );
		}
	}

#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "dlgTalk_OnInitDialog: %I64u tn %d leaves with %s"  ),  m_var.addr.idInfo.ui64Id,  m_var.addr.uiTranNo_shadow,  iErr  ?  _T(  "Err"  )  :  _T(  "OK"  )  );
#endif

	//  2012/05/25
	if  (  pProcInfo->cfg.debugStatusInfo.ucbShowDlgTalkStatus  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_OnInitDialog %I64u, %d leaves with %s"  ),  m_var.addr.idInfo.ui64Id,  m_var.addr.uiTranNo_shadow,  iErr  ?  _T(  "Err"  )  :  _T(  "OK"  )  ); 
	}


	return  iErr;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

 int  dlgTalk_OnDestroy(  HWND  hDlg,  void  *  pDLG_TALK_var  )
{ 
	
	if  (  !pDLG_TALK_var  )  return  -1;
	 DLG_TALK_var		&	m_var	=	*(  DLG_TALK_var  *  )pDLG_TALK_var;
	 MC_VAR_isCli  *  pProcInfo	=	QY_GET_procInfo_isCli(  );

#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "dlgTalk_OnDestroy called, %I64u"  ),  m_var.addr.idInfo.ui64Id  );
		//
		//  2013/07/31	
		//qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_OnDestroy: %I64u, %d "  ),  m_var.addr.idInfo.ui64Id,  m_var.addr.uiTranNo_shadow  ); 
	
#endif
			
	
	 
	
	 //
	 if  (  m_var.uiTimerId  )  KillTimer(  hDlg,  m_var.uiTimerId  );		//  2007/12/22
	 
	 //
	 if (m_var.uiTimerId_guiMsgArrive) {									//  2024/10/23
		 KillTimer(hDlg, m_var.uiTimerId_guiMsgArrive);
	 }

	 //
	 MACRO_safeFree(  m_var.av.pZoneParams  );								//  2012/05/05
	 MACRO_safeFree(  m_var.pMsgBuf_doWnd_guiMsgArrive  );					//  2009/12/08

	 if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
		 dlgTalk_closeTaskAv(  hDlg,  m_var  );
		 //
		 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
		 if  (  pShadowMgr  )  {
			 //	 
			 exitGrpConfCtrl(  &pShadowMgr->confCtrl.grpConfCtrl  );
		 }
		 //
		 cleanTalkerRuleTasks(  hDlg,  false,  _T(  "dlgTalk_OnDestroy"  )  );
	 }

	 //
	 int  idc_dst;
	 idc_dst  =  0;	//  m_var.av.idc_peer;
	 old_freeCapImages(  hDlg,  m_var.av.idc_peer,  &m_var.av.peerZone.images,  old_M_GetDlgItem(  hDlg,  idc_dst  ),  &m_var.av.hDc_peer,  _T( "dlgTalk_OnDestroy.5905"));
	 idc_dst  =  m_var.av.idc_me;
	 old_freeCapImages(  hDlg,  m_var.av.idc_me,  &m_var.av.meZone.images,  old_M_GetDlgItem(  hDlg,  idc_dst  ),  &m_var.av.hDc_me,_T("dlgTalk_OnDestroy.5907"));
	 idc_dst  =  m_var.av.idc_other;
	 old_freeCapImages(  hDlg,  m_var.av.idc_other,  &m_var.av.otherZone.images,  old_M_GetDlgItem(  hDlg,  idc_dst  ),  &m_var.av.hDc_other,_T("dlgTalk_OnDestroy.5909"));
	 idc_dst  =  m_var.av.idc_bgWall_conf;	//  2014/10/01
	 int  j;
	 for  (  j  =  0;  j  <  mycountof(  m_var.av.bgWall.mems  );  j  ++  )  {
		 CAP_IMAGES  *  pImgs  =  &m_var.av.bgWall.mems[j].images;
		  old_freeCapImages(  hDlg,  m_var.av.idc_bgWall_conf,  pImgs,  old_M_GetDlgItem(  hDlg,  idc_dst  ),  &m_var.av.hDc_bgWall_conf,  _T(  "dlgTalk_OnDestroy.5914"  ));
	 }

	 //  2009/08/19
	 CAP_STUFF_free(  m_var.pCapStuff  );

	 //  2012/04/09
	 BOOL	bRet  =  0;
	 if  (  m_var.hMenu  )  {
		 bRet  =  DestroyMenu(  m_var.hMenu  );
	 }

	 //  2012/05/09


	 //
	 if  (  m_var.bTmpGrpMemQInited  )  exitGenericQ(  &m_var.tmpGrpMemQ  );	//  2008/01/22

	 closeSubWnds(  &m_var.subWnds  );	//  2009/09/09

	 //
	 removeTalker(m_var.pQyMc, &m_var.addr, 0);
	 //
	 if  (  m_var.bDisplayCtxInited  )  exitMcCtxDisplayedWnd(  g_pQyMc,  hDlg,  &m_var.displayCtx  );


	 //
	 return  0;
}
 
 //  2016/02/17
 typedef  struct  __param_findTaskAvOrgReq_t	{
				  int							iStatus_o;
				  int							iTaskId;
				  unsigned  int					uiTaskType;
 }		  PARAM_findTaskAvOrgReq;


 //
 int  tmpHandler_findTaskAvOrgReq(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int								iErr		=	-1;
	MIS_MSG_TASKSTATUS			*	pMsgStatus	=	(  MIS_MSG_TASKSTATUS  *  )p0;
	PARAM_findTaskAvOrgReq		*	pParam_o	=	(  PARAM_findTaskAvOrgReq  *  )p1;			//  2014/07/30
	MIS_MSGU					*	pMsgElem	=	(  MIS_MSGU  *  )p2;

	switch  (  pMsgElem->uiType  )  {
			case  CONST_misMsgType_task:  {
				  MIS_MSG_routeTalkData		*	pTalkData							=	&pMsgElem->task.data;
				  IM_CONTENTU				*	pContent							=	(  IM_CONTENTU  *  )pTalkData->buf;	
				  BOOL							bFound								=	FALSE;

				  if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
					  if  (  pMsgStatus->uiContentType  ==  CONST_imCommType_transferVideoData  &&						//  2010/12/27
						  pContent->transferAvInfo.ass.tranInfo.video.uiTranNo_openAvDev  ==  pMsgStatus->uiTranNo  )  
					  {
						  bFound  =  TRUE;
						  //
  						  #ifdef  __DEBUG__
								  traceLog((TCHAR*)  _T(  "taskAvOrgReq found, taskStatus %s"  ),  qyGetDesByType1(  CONST_qyStatusTable_en,  pMsgElem->task.iStatus  )  );
						  #endif						  
					  }
					  if  (  pMsgStatus->uiContentType  ==  CONST_imCommType_transferAudioData  &&					  
						  pContent->transferAvInfo.ass.tranInfo.audio.uiTranNo_openAvDev  ==  pMsgStatus->uiTranNo  )  
					  {
						  bFound  =  TRUE;
						  //
						  #ifdef  __DEBUG__
								  traceLog((TCHAR*)  _T(  "taskAvOrgReq found, taskStatus %s"  ),  qyGetDesByType1(  CONST_qyStatusTable_en,  pMsgElem->task.iStatus  )  );
						  #endif
					  }
				  }

				  //
				  if  (  bFound  )  {

					  //  2014/07/30						
					  pParam_o->iStatus_o  =  pMsgElem->task.iStatus;		
					  pParam_o->iTaskId  =  pMsgElem->task.iTaskId;
					  pParam_o->uiTaskType  =  pMsgElem->task.uiTaskType;
					  //
					  iErr  =  1;  goto  errLabel;
				  }

				  }
				  break;
			default:
					break;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}


 //
  int  tmpHandler_bRefreshContactsStatus_dlgTalk(  void  *  pElemParam,  void  *  pMemParam,  void  *  hDlgTalkParam  )
{
	 int								iErr						=	-1;
	 DISPLAYEDELEM_U				*	pElem						=	(  DISPLAYEDELEM_U  *  )pElemParam;
	 REFRESH_RECENTFRIEND_RESP_h		*	pMem						=	(  REFRESH_RECENTFRIEND_RESP_h  *  )pMemParam;
	 HWND								hDlg						=	(  HWND  )hDlgTalkParam;
	 CHelp_getDlgTalkVar				help_getDlgTalkVar;
	 DLG_TALK_var					*	pm_var						=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlg  );
	 if  (  !pm_var  )  return  -1;
	 DLG_TALK_var					&	m_var						=	*pm_var;
	 //
	 QY_MC* pQyMc = m_var.pQyMc;// QY_GET_GBUF();
	 //
	 TCHAR								tBuf[256]					=	_T(  ""  );
	 TCHAR								displayName[255  +  1]		=	_T(  ""  );
	 int								nImage,  nSelectedImage;
	 //
	 int								iRcdId;
	 //
	 if  (  !hDlg  )  return  -1;
	 if  (  !m_var.idcList_members  )  return  -1;
 #ifndef  __WINCE__
	 //  CWnd							*	pDlg						=	CWnd::FromHandle(  hDlg  );
	 //  CListCtrl						*	pListCtrl			=	(  CListCtrl  *  )pDlg->GetDlgItem(  m_var.idcList_members  );
	 HWND								hListCtrl				=	GetDlgItem(  hDlg,  m_var.idcList_members  );
	 //  if  (  !pListCtrl  )  return  -1;
	 if  (  !hListCtrl  )  return  -1;

	 switch  (  pElem->uiType  )  {
			 case  CONST_displayedElemType_messengerTree:
				   iRcdId  =  (  int  )pElem->messengerTree.hItem;
				   break;
			 default:	
					goto  errLabel;
	 }

	 LVFINDINFO info;
	 int		nItem  =  0;

	 info.flags = LVFI_PARAM;
	 info.lParam = (  LPARAM  )iRcdId;

	 //  if  (  (  nItem  =  pListCtrl->FindItem(  &info,  -1  )  )  ==  -1  )  
	 if  (  (  nItem  =  myListCtrl_FindItem(  hListCtrl,  &info,  -1  )  )  ==  -1  )
	 {	//  Ã»ÕÒµ½
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "tmpHandler_bRefreshContactsStatus_dlgTalk: FindItem failed, "  );
		 #endif
		 iErr  =  0;  goto  errLabel;
	 }

	 
	 LVITEM				lvItem;

	 memset(  &lvItem,  0,  sizeof(  lvItem  )  );
	 lvItem.mask  =  LVIF_TEXT  |  LVIF_IMAGE  |  LVIF_STATE;
	 lvItem.iItem  =  nItem;
	 lvItem.pszText  =  tBuf;
	 lvItem.cchTextMax  =  mycountof(  tBuf  );
	 //  if  (  !pListCtrl->GetItem(  &lvItem  )  )  
	 if  (  !myListCtrl_GetItem(  hListCtrl,  &lvItem  )  )  
	 {
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)  "tmpHandler_bRefreshContactsStatus_dlgTalk: GetItem failed, ³ö´íÁË"  );  
		 #endif
		 goto  errLabel;				  
	 }
					  
	 lstrcpyn(  displayName,  tBuf,  mycountof(  displayName  )  );	//  ÕâÀï¹ÊÒâÈÃdisplayNameÖ¸ÏòtBuf, ÊÇÒòÎªÕâÀïÔÝÊ±Ö»ÐèÒª±ä»¯Í¼±ê
	
	 getMessengerImages(  pQyMc,  pMem->usRunningStatus,  &nImage,  &nSelectedImage  );
				
	 if  (  _tcsicmp(  tBuf,  displayName  )  ||  lvItem.iImage  !=  nImage  )  {
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  displayName  );
		 lvItem.iImage  =  nImage;
		 //  pListCtrl->SetItem(  &lvItem  );
		 myListCtrl_SetItem(  hListCtrl,  &lvItem  );
	 }
#endif

	 iErr  =  0;

errLabel:
	 return  iErr;
}


 

  //
   int  tmpHandler_cancelTask(  HWND  hDlg,  void  *  p1,  void  *  p2  )
{

	int					iErr		=	-1;
	PARAM_PROC_ROW	*	pParam		=	(  PARAM_PROC_ROW  *  )p1;
	MIS_MSGU		*	pMsgElem	=	(  MIS_MSGU  *  )p2;

	//  2012/05/09
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pm_var		=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlg  );
	if  (  !pm_var  )  return  -1;

	HWND				hMgr	=	hDlg;
	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	DLG_TALK_var  *  pMgrVar	=  pm_var;
	if  (  !isTalkerShadowMgr(  pm_var->addr  )  )  {
		TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pm_var->pShadowInfo;
		if  (  !pShadow  )  return  -1;
		hMgr  =  pShadow->hMgr;
		pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  hMgr  );
		if  (  !pMgrVar  )  return  -1;
	}

	//
	//  DLG_TALK_var	&	m_var		=	*getDlgTalkVar(  hDlg  );
	//
	QY_MC* pQyMc = pm_var->pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	MIS_CNT			*	pMisCnt		=	pMgrVar->pMisCnt;
	TCHAR				tBuf[256]	=	_T(  ""  );
	char				buf[256]	=	"";
	CQyMalloc			mallocObj;

	if  (  !hDlg  ||  !pParam  ||  !pMsgElem  )  return  -1;
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	if  (  pMsgElem->uiType  ==  CONST_misMsgType_task  )  {
		MIS_MSG_TASK	*	pMsg		=	&pMsgElem->task;
		IM_CONTENTU		*	pContent	=  (  IM_CONTENTU  *  )pMsg->data.buf;
		int					iStatus;
		int					lenInBytes;

		if  (  pParam->iTaskId  )  {
			if  (  pMsg->iTaskId  !=  pParam->iTaskId  )  {
				iErr  =  0;  goto  errLabel;
			}
		}

		void  *  pDb  =  NULL;
		#ifndef  __NOTSUPPORT_DB__
				 CQnmDb				db;
				 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
				 pDb  =  db.m_pDbMem->pDb;
		#endif

		switch  (  pContent->uiType  )  {
				case  CONST_imCommType_transferAvInfo:
				case  CONST_imCommType_transferFileReq:
					  switch  (  pMsg->iStatus  )  {
							  case  CONST_imTaskStatus_req:
							  case  CONST_imTaskStatus_applyToSend:
							  case  CONST_imTaskStatus_waitToSend:  
							  case  CONST_imTaskStatus_acceptedByReceiver:
							  case  CONST_imTaskStatus_dualByReceiver:  {

									#if  1	//  ndef  __APP_qyMc_touchscreen__
											 if  (  pParam->ucbNeedAsk  &&  !pParam->ucbAsked  )  {					
												 G_guiData_qyMc	*	pGuiData	=	get_g_guiData(  );
												 PF_MessageBox	pf  =  (  PF_MessageBox  )pGuiData->pf_MessageBox;
												 MACRO_qyAssert(  pf,  _T(  "pf_MessageBox is null"  )  );
												 int  tmpiRet  =  pf(  hDlg,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ifExitSession  ),  _T(  "qycx.com"  ),  MB_YESNOCANCEL  );
												 //
												 pParam->iRetVal_id_messageBox  =  tmpiRet;
												 //
												 if  (  tmpiRet  ==  IDCANCEL  )  goto  errLabel;
												 //
												 if  (  tmpiRet  ==  IDNO  )  {
													 iErr  =  1;  goto  errLabel;
												 }
												 //
												 pParam->ucbAsked  =  TRUE;
											 }
									#endif

							        iStatus  =  CONST_imTaskStatus_canceledBySender;						  
									g_dbFuncs.pf_updateTaskStatus(  pDb,  iStatus,  pMsg->iTaskId  );
									pMsg->iStatus  =  iStatus;		//  2012/05/15

									//  °ÑÏÔÊ¾×´Ì¬ÐÞ¸ÄÏÂ.2008/11/14
									showTaskStatus(  pMisCnt,  &pMgrVar->addr.idInfo,  &pMsg->idInfo_taskSender,  &pMsg->idInfo_taskReceiver,  FALSE,  pContent->uiType,  pMsg->iTaskId,  iStatus,  0,  0,  _T(  ""  ),  _T(  ""  )  );
						  						  
									//  Í¨Öª¶Ô·½
									TASK_PROC_REQ		taskProcReq;
									memset(  &taskProcReq,  0,  sizeof(  taskProcReq  )  );
									taskProcReq.uiType  =  CONST_imCommType_taskProcReq;
									taskProcReq.usOp  =  CONST_imOp_send_cancel;
									taskProcReq.tStartTime_org  =  pMsg->tStartTime;
									taskProcReq.uiTranNo_org  =  pMsg->uiTranNo;
									taskProcReq.uiContentType_org  =  pContent->uiType;
									//
									lenInBytes  =  sizeof(  taskProcReq  ); 
									//					  
									MACRO_prepareForTran(  );						
									//  2015/09/08
									unsigned  int  uiChannelType  =  pMsg->uiChannelType;
									//
									uiChannelType  =  0;
									//
									if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  pMsg->usCode,  tStartTran,  uiTranNo,  0,  pMsg->iTaskId,  pMsg->uiTaskType,  (  char  *  )&taskProcReq,  lenInBytes,  &pMgrVar->addr.idInfo,  &pMsg->idInfo_taskSender,  &pMsg->idInfo_taskReceiver,  &pMsg->idInfo_taskReceiver,  uiChannelType,  NULL,  FALSE  )  )  goto  errLabel;
									}
									break;
							  case  CONST_imTaskStatus_resp:
							  case  CONST_imTaskStatus_applyToRecv:
							  case  CONST_imTaskStatus_waitToRecv:  {

									#if  1  //  ndef  __APP_qyMc_touchscreen__
											 if  (  pParam->ucbNeedAsk  &&  !pParam->ucbAsked  )  {
												 //  if  (  myMessageBox(  hDlg,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ifExitSession  ),  _T(  "qycx.com"  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
												 //  2016/02/12
												 int  tmpiRet  =  myMessageBox(  hDlg,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ifExitSession  ),  _T(  "qycx.com"  ),  MB_YESNOCANCEL  );
												 //
												 if  (  tmpiRet  ==  IDCANCEL  )  goto  errLabel;
												 //
												 if  (  tmpiRet  ==  IDNO  )  {
													 iErr  =  1;   goto  errLabel;
												 }
												 //
												 pParam->ucbAsked  =  TRUE;
											 }
								    #endif

								    iStatus  =  pParam->bAutoCancel  ?  CONST_imTaskStatus_autoCanceledByReceiver  :  CONST_imTaskStatus_canceledByReceiver;						  			
									g_dbFuncs.pf_updateTaskStatus(  pDb,  iStatus,  pMsg->iTaskId  );
									pMsg->iStatus  =  iStatus;		//  2012/05/15

									//  °ÑÏÔÊ¾×´Ì¬ÐÞ¸ÄÏÂ.2008/11/14
									showTaskStatus(  pMisCnt,  &pMgrVar->addr.idInfo,  &pMsg->idInfo_taskSender,  &pMsg->idInfo_taskReceiver,  FALSE,  pContent->uiType,  pMsg->iTaskId,  iStatus,  0,  0,  _T(  ""  ),  _T(  ""  )  );
						  			
									//  Í¨Öª¶Ô·½
									TASK_PROC_REQ		taskProcReq;
									memset(  &taskProcReq,  0,  sizeof(  taskProcReq  )  );
									taskProcReq.uiType  =  CONST_imCommType_taskProcReq;
									taskProcReq.usOp  =  CONST_imOp_recv_cancel;
									taskProcReq.tStartTime_org  =  pMsg->tStartTime;
									taskProcReq.uiTranNo_org  =  pMsg->uiTranNo;
									taskProcReq.uiContentType_org  =  pContent->uiType;
									//
									lenInBytes  =  sizeof(  taskProcReq  ); 
									//					  
									MACRO_prepareForTran(  );						
									//  2015/09/08
									unsigned  int  uiChannelType  =  pMsg->uiChannelType;
									//
									uiChannelType  =  0;
									//	
									if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  pMsg->usCode,  tStartTran,  uiTranNo,  0,  pMsg->iTaskId,  0,  (  char  *  )&taskProcReq,  lenInBytes,  &pMgrVar->addr.idInfo,  &pMsg->idInfo_taskSender,  &pMsg->idInfo_taskReceiver,  &pMsg->idInfo_taskSender,  uiChannelType,  NULL,  FALSE  )  )  goto  errLabel;
									}
									break;
							  default:
									  break;
					  }					  
					  break;
				default:
						break;
		}


		//
		//
		if (!pParam->bAutoCancel) {
			if (pMgrVar->av.taskInfo.bTaskExists
				&& pMgrVar->av.taskInfo.iTaskId == pMsg->iTaskId)
			{
				clearSpeakState(_T("tmpHandler_cancelTask.6395"));
			}
		}

		//
		//
		dlgTalk_closeTask(  hDlg,  pMsg->iTaskId  );

	}

	

	//
	iErr  =  0;

errLabel:
	
	return  iErr;
}




//
  int  dlgTalk_cancelTasks(  HWND  hCurTalk,  void  *  pCurDLG_TALK_var,  int  iTaskId,  BOOL  bAutoCancel  )
{
	int					iErr										=	-1;
	DLG_TALK_var	*	pCurVar										=	(  DLG_TALK_var  *  )pCurDLG_TALK_var;
	QY_MC* pQyMc = pCurVar->pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli	*	pProcInfo									=	QY_GET_procInfo_isCli(  );
	//
	char				idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char				idStr_me[CONST_qyMessengerIdStrLen  +  1]	=	"";
	int					tmpiRet										=	-1;
	//  CListCtrl		*	pListCtrl									=	(  CListCtrl  *  )CWnd::FromHandle(  GetDlgItem(  hDlg,  m_var.idcList_task  )  );
	PARAM_PROC_ROW		param;
	CQySyncObj			syncObj;

	if  (  !pCurVar  )  return  -1;

	//
	HWND				hMgr	=	hCurTalk;
	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	DLG_TALK_var  *  pMgrVar	=  pCurVar;
	if  (  !isTalkerShadowMgr(  pCurVar->addr  )  )  {
		TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pCurVar->pShadowInfo;
		if  (  !pShadow  )  return  -1;
		hMgr  =  pShadow->hMgr;
		pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  hMgr  );
		if  (  !pMgrVar  )  return  -1;
	}

	//
	//  DLG_TALK_var  &  m_var  =  *pm_var;

	if  (  !pMgrVar->m_pProcessQ  )  return  -1;
	GENERIC_Q		&	m_processQ  =  *pMgrVar->m_pProcessQ;

	//  2011/02/03
	if  (  pMgrVar->bCancelTasks  )  return  -1;
	pMgrVar->bCancelTasks  =  TRUE;

	//
	idInfo2Str(  &pMgrVar->addr.idInfo,  idStr,  mycountof(  idStr  )  );
	idInfo2Str(  &pMgrVar->pMisCnt->idInfo,  idStr_me,  mycountof(  idStr_me  )  );

	#ifdef  __DEBUG__
			traceLogA(  (char*)  "cancelTasks: usMaxDisplayedTasks %d",  pMgrVar->usMaxDisplayedTasks  );
	#endif

	if  (  syncObj.sync(  CQyString(  pMgrVar->pMisCnt->cfg.mutexNamePrefix_syncTask  )  +  idStr  )  )  goto  errLabel;

	memset(  &param,  0,  sizeof(  param  )  );
	if  (  !pQyMc->bQuit  )  param.ucbNeedAsk  =  TRUE;

	//  2013/09/08
	if  (  !IsWindowVisible(  hCurTalk  )  )  {
		param.ucbNeedAsk  =  FALSE;
	}
	//  2015/08/04
	BOOL  bNeedClose  =  FALSE;
	if  (  pProcInfo->cfg.policy.ucbRunAsAdvertisingPlayer  )  {				
		//
		bNeedClose  =  FALSE;			
		if  (  !dlgTalk_chkAsAdvertisingPlayer(  hMgr,  pMgrVar,  &bNeedClose,  NULL,  0  )  )  {
			if  (  bNeedClose  )  {
				param.ucbNeedAsk  =  FALSE;
			}			
		}
	}
	if  (  bSupported_fileServer(  pQyMc  )  )  {
		//
		bNeedClose  =  FALSE;
		if  (  !dlgTalk_chkFileServer(  hMgr,  pMgrVar,  &bNeedClose,  NULL,  0  )  )  {
			if  (  bNeedClose  )  {
				param.ucbNeedAsk  =  FALSE;
			}
		}
	}
	if  (  pQyMc->appParams.bNoPrompt_mfc  )  {
		param.ucbNeedAsk  =  FALSE;
	}

	//
	if (pProcInfo->m_bUseKeyToLogin_forQmcGui) {
		param.ucbNeedAsk = false;
	}
	
	//
	if  (  iTaskId  )  {
		param.iTaskId  =  iTaskId;
		param.ucbNeedAsk  =  FALSE;			//  
		param.bAutoCancel  =  bAutoCancel;	//  2014/07/30
	}
	tmpiRet  =  qTraverse(  &m_processQ,  (  PF_commonHandler  )tmpHandler_cancelTask,  hCurTalk,  &param  );  
	if  (  tmpiRet  <  0  )  goto  errLabel;

	iErr  =  0;
errLabel:

	pMgrVar->bCancelTasks  =  FALSE;	//  2011/02/03

	return  iErr;
}



  //





  //  2014/12/24
  int  getVal_bTaskSlave(  HWND  hDlg,  DLG_TALK_var  &  m_var,  int  iTaskId,  BOOL  *  pbExists  )
  {
	  int	iErr  =  -1;
	  MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	  BOOL  bFound  =  FALSE;

	  if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;

	  if  (  !m_var.av.taskInfo.bTaskExists  
		  ||  !m_var.av.ucbGot_iIndex_sharedObj_localAv  )
	  {
		  iErr  =  0;  goto  errLabel;
	  }

	  int  iIndex_sharedObj_master  =  m_var.av.iIndex_sharedObj_localAv;

	  QY_SHARED_OBJ				*	pSharedObj_master		=	NULL;
	  pSharedObj_master  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj_master  );
	  if  (  !pSharedObj_master  )  goto  errLabel;
		
	  //  2014/09/23. 在主对象和辅助对象间建立主从关系	
	  if  (  pSharedObj_master->bSlave  )  goto  errLabel;

	  SHARE_dyn_bmp  *  pShareDynBmp_slave  =  (  SHARE_dyn_bmp  *  )pSharedObj_master->master.pShareDynBmp_slave;
	  if  (  !pShareDynBmp_slave  )  {
		  iErr  =  0;  goto  errLabel;
	  }

	  if  (  pShareDynBmp_slave->var.iTaskId  ==  iTaskId  )  {
		  bFound  =  TRUE;
	  }

	  iErr  =  0;
errLabel:
	  if  (  !iErr  )  {
		  if  (  pbExists  )  *pbExists  =  bFound;
	  }

	  return  iErr;

  }


 //
 int  dlgTalk_toChkTask(  HWND  hDlg,  DLG_TALK_var  &m_var,  QY_WMBUF_COMM  *  pComm  )
{
	int		iErr	=	-1;
	BOOL	bFound  =  FALSE;

	if  (  !pComm  )  return  -1;
	if  (  pComm->uiType  !=  CONST_qyWmParam_chkTask  )  return  -1;

	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;

	if  (  m_var.av.taskInfo.bTaskExists  )  {
		if  (  m_var.av.taskInfo.iTaskId  ==  pComm->u.chkTask.iTaskId  )  {
			bFound  =  TRUE;
		}
		//  2014/12/24
		BOOL  tmpbVal  =  FALSE;
		if  (  getVal_bTaskSlave(  hDlg,  m_var,  pComm->u.chkTask.iTaskId,  &tmpbVal  )  )  goto  errLabel;
		if  (  tmpbVal  )  bFound  =  TRUE;
		
		//
		if  (  !bFound  )  {
			if  (  m_var.av.taskInfo.ucbStarter  
				&&  m_var.av.taskInfo.ucbVideoConference  )	
			{
				if  (  confStarter_bTaskInBgWall(  hDlg,  &m_var,  pComm->u.chkTask.iTaskId,  NULL,  NULL  )  )  {			
					bFound  =  TRUE;			
				}		
			}
		}
	}
	if  (  !bFound  )  {
		MIS_MSG_TASK	*	pMsgTask;
		if  (  (  pMsgTask  =  findTaskInProcessQ(  &m_var,  pComm->u.chkTask.iTaskId  )  )  )  {
			if  (  bTaskAlive(  pMsgTask->iStatus  )  )  {
				bFound  =  TRUE;
			}
		}
	}
	//  2012/04/25
	if  (  !bFound  )  {	//  
		int  i;
		for  (  i  =  0;  i  <  mycountof(  pShadowMgr->talkerDynBmps  );  i  ++  )  {
			 if  (  pShadowMgr->talkerDynBmps[i].taskInfo.iTaskId  ==  pComm->u.chkTask.iTaskId  )  {
				 bFound  =  TRUE;
				 break;
			 }
		}
	}
	//  2012/04/20
	if  (  !bFound  )  {
		if  (  pShadowMgr->vwRuleCmd.ucbViewGps
			&&  pShadowMgr->viewGps.iTaskId  ==  pComm->u.chkTask.iTaskId  )
		{	//  就算活跃着
			bFound  =  TRUE;
		}
	}

	if  (  !bFound  )  {
		pComm->u.chkTask.bNotExists  =  TRUE;
	}

	pComm->u.chkTask.bChked  =  TRUE;

	iErr  =  0;

errLabel:

	return  iErr;
}


 //  2014/12/22
 int  dlgTalk_toChkSharedObj(  HWND  hDlg,  DLG_TALK_var  &m_var,  QY_WMBUF_COMM  *  pComm  )
{
	int		iErr	=	-1;
	BOOL	bFound  =  FALSE;

	if  (  !pComm  )  return  -1;
	if  (  pComm->uiType  !=  CONST_qyWmParam_chkSharedObject  )  return  -1;

	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;

	//
	if  (  pComm->u.chkSharedObject.iTaskId  )  {
		//
		QY_WMBUF_COMM  wmBuf;
		memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
		wmBuf.uiType  =  CONST_qyWmParam_chkTask;									
		wmBuf.u.chkTask.iTaskId  =  pComm->u.chkSharedObject.iTaskId;
		if  (  CONST_qyWmRc_ok  !=  SendMessage(  hDlg,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  )  )  goto  errLabel;
		bFound  =  !wmBuf.u.chkTask.bNotExists;
	}
	
	//
	if  (  !bFound  )  {
		pComm->u.chkSharedObject.bNotExists  =  TRUE;
	}

	//  pComm->u.chkSharedObject.bChked  =  TRUE;

	iErr  =  0;
	
errLabel:

	return  iErr;
}

 

 //
  int  dlgTalk_displayAvStatus(  HWND  hDlg,  DLG_TALK_var  &  m_var,  int  iTaskId,  int  iStatus,  LPCTSTR  statusDesc  )
{
	int					iErr		=	-1;
	QY_MC* pQyMc = m_var.pQyMc;// QY_GET_GBUF();
	MIS_MSG_TASK	*	pMsgTask	=	NULL;

	if  (  m_var.av.taskInfo.bTaskExists  )  {
		pMsgTask  =  findTaskInProcessQ(  &m_var,  m_var.av.taskInfo.iTaskId,  0  );
		if  (  !pMsgTask  )  goto  errLabel;
		}
	else  {
		  pMsgTask  =  findTaskInProcessQ(  &m_var,  m_var.guiData.av.iTaskId  );
		  if  (  !pMsgTask  ||  !bTaskAlive(  pMsgTask->iStatus  )  )  {
			  pMsgTask  =  findTaskInProcessQ(  &m_var,  0,  TRUE  );
		  }
	}
	if  (  !pMsgTask  )  {
		m_var.guiData.av.iTaskId  =  0;
		m_var.guiData.av.iStatus  =  0;
		m_var.guiData.av.statusDesc[0]  =  0;
		}
	else  {
		  if  (  m_var.guiData.av.iTaskId  !=  pMsgTask->iTaskId  )  m_var.guiData.av.iTaskId  =  pMsgTask->iTaskId;
		  if  (  m_var.guiData.av.iStatus  !=  pMsgTask->iStatus  )  m_var.guiData.av.iStatus  =  pMsgTask->iStatus;
	}

	if  (  m_var.guiData.av.iTaskId  )  {	
		if  (  m_var.guiData.av.iTaskId  ==  iTaskId  )  m_var.guiData.av.iStatus  =  iStatus;
		
		if  (  m_var.guiData.av.iTaskId  ==  iTaskId  &&  statusDesc  )  lstrcpyn(  m_var.guiData.av.statusDesc,  statusDesc,  mycountof(  m_var.guiData.av.statusDesc  )  );
		else  _sntprintf(  m_var.guiData.av.statusDesc,  mycountof(  m_var.guiData.av.statusDesc  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0, &pQyMc->cusRes,  CONST_resId_imTaskStatusTable  ),  m_var.guiData.av.iStatus  )  );
	}


	//
	m_var.guiData.bChanged_status  =  TRUE;

	//
#if  10
	if  (  m_var.guiData.bChanged_status  )  {
		m_var.guiData.bChanged_status  =  FALSE;

		PF_commonHandler	pf		=	NULL;
		pf  =  (  PF_commonHandler  )m_var.guiData.pf_refreshDlg_talk_ce;
		if  (  pf  )  pf(  hDlg,  &m_var.guiData,  0  );

		if  (  !m_var.av.taskInfo.bTaskExists  )  {
			if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
				TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
				if  (  !pShadowMgr  )  goto  errLabel;
				int  i;
				for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
					 if  (  !pShadowMgr->shadows[i].hShadow  )  continue;
					 InvalidateRect(  GetDlgItem(  pShadowMgr->shadows[i].hShadow,  m_var.guiData.iIDC_STATIC_dlgDesc  ),  NULL,  TRUE  );  
				}
			}
			//
			InvalidateRect(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_STATIC_dlgDesc  ),  NULL,  TRUE  );  
		}

		#ifdef  __DEBUG__
				//  if  (  !hint  )  hint  =  _T(  ""  );
				//  traceLog((TCHAR*)  _T(  "dlgTalk_bRefresh: status, %s"  ),  hint  );
		#endif

	}
#endif


	iErr  =  0;
errLabel:
	return  iErr;
 }



#ifndef  __WINCE__
  //  int  addToTaskList(  PARAM_PROC_ROW  *  pParam,  TASK_DISPLAY  *  pTaskDisplay,  CListCtrl  *  pListCtrl  )
  int  addToTaskList(  QY_MC  *  pQyMc,  PARAM_PROC_ROW  *  pParam,  TASK_DISPLAY  *  pTaskDisplay,  HWND  hListCtrl  )
{
		int			iErr		=	-1;	
		TCHAR		tBuf[256]	=	_T(  ""  );
		//QY_MC	*	pQyMc		=	QY_GET_GBUF(  );
		char	*	p			=	NULL;
		char		buf[256]	=	"";
		int			nItem		=	pParam->nItem;
		int			i;
		int			j;


		//  2012/05/01
		nItem  =  0;

		//
		i  =  0;  
		//  if  (  (  j  =  pListCtrl->InsertItem(  nItem,  _ltot(  pTaskDisplay->id,  tBuf,  10  )  )  )  <  0  )  
		if  (  (  j  =  myListCtrl_InsertItem(  hListCtrl,  nItem,  _ltot(  pTaskDisplay->id,  tBuf,  10  )  )  )  <  0  )  
		{
			#ifdef  __DEBUG__
			CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
			if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
				traceLog((TCHAR*)_T("addToTaskList: InsertItem failed"));
			}
			#endif
			goto  errLabel;
		}
		//  i  ++  ;	pListCtrl->SetItemText(  nItem,  i,  pTaskDisplay->rowIdStr  );
		i  ++  ;	myListCtrl_SetItemText(  hListCtrl,  nItem,  i,  pTaskDisplay->rowIdStr  );
		//  i  ++  ;	pListCtrl->SetItemText(  nItem,  i,  pTaskDisplay->rowIdStr  );							//  rowIdStr_cur
		i  ++  ;	myListCtrl_SetItemText(  hListCtrl,  nItem,  i,  pTaskDisplay->rowIdStr  );							//  rowIdStr_cur
		//  i  ++  ;	pListCtrl->SetItemText(  nItem,  i,  _ltot(  pTaskDisplay->iStatus,  tBuf,  10  )  );	//  iStatus_cur
		i  ++  ;	myListCtrl_SetItemText(  hListCtrl,  nItem,  i,  _ltot(  pTaskDisplay->iStatus,  tBuf,  10  )  );	//  iStatus_cur
		i  ++  ;	
					//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pTaskDisplay->idInfo_send.ui64Id  );  
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pTaskDisplay->displayName_sender  );
					//  pListCtrl->SetItemText(  nItem,  i,  tBuf  );
					myListCtrl_SetItemText(  hListCtrl,  nItem,  i,  tBuf  );
		//  i  ++  ;	pListCtrl->SetItemText(  nItem,  i,  pTaskDisplay->typeStr  );
		i  ++  ;	myListCtrl_SetItemText(  hListCtrl,  nItem,  i,  pTaskDisplay->typeStr  );
		//  i  ++  ;	pListCtrl->SetItemText(  nItem,  i,  qyGetDesByType1(  getResTable(  0, &pQyMc->cusRes,  CONST_resId_imTaskStatusTable  ),  pTaskDisplay->iStatus  )  );		//  iStatus
		i  ++  ;	myListCtrl_SetItemText(  hListCtrl,  nItem,  i,  qyGetDesByType1(  getResTable(  0, &pQyMc->cusRes,  CONST_resId_imTaskStatusTable  ),  pTaskDisplay->iStatus  )  );		//  iStatus
		//  i  ++  ;	pListCtrl->SetItemText(  nItem,  i,  pTaskDisplay->subject  );
		i  ++  ;	myListCtrl_SetItemText(  hListCtrl,  nItem,  i,  pTaskDisplay->subject  );
		//  i  ++  ;	if  (  pTaskDisplay->tSendTime  )  p  =  displayShortTime(  pTaskDisplay->tSendTime,  buf,  mycountof(  buf  )  );  if  (  !p  )  p  =  "";  pListCtrl->SetItemText(  nItem,  i,  CQyString(  p  )  );
		i  ++  ;	if  (  pTaskDisplay->tSendTime  )  p  =  displayShortTime(  pTaskDisplay->tSendTime,  buf,  mycountof(  buf  )  );  if  (  !p  )  p  =  (char*)"";  myListCtrl_SetItemText(  hListCtrl,  nItem,  i,  CQyString(  p  )  );
		//  i  ++  ;	if  (  pTaskDisplay->tRecvTime  )  p  =  displayShortTime(  pTaskDisplay->tRecvTime,  buf,  mycountof(  buf  )  );  if  (  !p  )  p  =  "";  pListCtrl->SetItemText(  nItem,  i,  CQyString(  p  )  );
		i  ++  ;	if  (  pTaskDisplay->tRecvTime  )  p  =  displayShortTime(  pTaskDisplay->tRecvTime,  buf,  mycountof(  buf  )  );  if  (  !p  )  p  =  (char*)"";  myListCtrl_SetItemText(  hListCtrl,  nItem,  i,  CQyString(  p  )  );
		//
		//  pListCtrl->SetItemData(  nItem,  pTaskDisplay->id  );	//  ÕâÀï¼ÓÈëÊý¾ÝidÊÇÒòÎªÓÐ×´Ì¬ÐÅÏ¢µÈ£¬ÓÃÕûÊýÀ´Æ¥ÅäÓ¦¸Ã»á¿ìÒ»Ð©£¬2007/07/17
		myListCtrl_SetItemData(  hListCtrl,  nItem,  pTaskDisplay->id  );	//  ÕâÀï¼ÓÈëÊý¾ÝidÊÇÒòÎªÓÐ×´Ì¬ÐÅÏ¢µÈ£¬ÓÃÕûÊýÀ´Æ¥ÅäÓ¦¸Ã»á¿ìÒ»Ð©£¬2007/07/17

		if  (  pParam->bScrollIntoView  )  {
			//  pListCtrl->SetItemState(  nItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
			myListCtrl_SetItemState(  hListCtrl,  nItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
			//  pListCtrl->Update(  nItem  );
			myListCtrl_Update(  hListCtrl,  nItem  );
		}

		//  (  pParam->nItem  )  ++  ; 
		//  pParam->nItem  =  pListCtrl->GetItemCount(  );
		pParam->nItem  =  myListCtrl_GetItemCount(  hListCtrl  );


		iErr  =  0;

errLabel:

	return  iErr;
}

#endif





//
int  tmpHandler_showMsg_displayTask(  HWND  hDlgTalk,  DLG_TALK_var  *  pDlgTalkVar,  PARAM_PROC_ROW	*	pParam,  MIS_MSGU  *  pMsg  )
{
	int					iErr	=	-1;
	MC_VAR_isCli	*	pProcInfo				=	QY_GET_procInfo_isCli(  );
	TCHAR				txtContent[1024]		=	_T(  ""  );
	TCHAR				tBuf[1024]				=	_T(  ""  );

	if  (  !pDlgTalkVar  )  return  -1;
	//  DLG_TALK_var  &  m_var  =  *pm_var;

	QY_MC* pQyMc = pDlgTalkVar->pQyMc;// QY_GET_GBUF();

	//  2014/01/26
#if 10
	MSG_tool_common* pmsgToolCommon = mynull;
	DLG_msgTool_var  *  pDlgMsgToolVar  =  (  DLG_msgTool_var  *  )getDlgMsgToolVar(  pDlgTalkVar->msgTool.hWnd_msgTool  );
	if (pDlgMsgToolVar) {
		pmsgToolCommon = &pDlgMsgToolVar->msgToolCommon;
	}
	HWND				hWnd_msgTool		=	pDlgTalkVar->msgTool.hWnd_msgTool;
	
	//  2014/01/27
	if (pDlgMsgToolVar) {
		if (!pDlgMsgToolVar->guiData.bFinished_createCtrls) {
#ifdef  __DEBUG__
			traceLog((TCHAR*)_T("tmpHandler_showMsg_displayTask failed, bFinished_createCtrls is false"));
#endif
			goto  errLabel;
		}
	}
#endif
		
	//
	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_task:  {

				  MIS_MSG_routeTalkData		*	pTalkData							=	&pMsg->task.data;				
				  IM_CONTENTU				*	pContent							=	(  IM_CONTENTU  *  )pTalkData->buf;	
				  QY_MESSENGER_ID				idInfo_talker;
				  #ifndef  __WINCE__
						   CQyString				rowIdStr							=	getNextRowIdStr(  hDlgTalk  );
				  #else
						   TCHAR				rowIdStr[1]							=	_T(  ""  );
				  #endif
				  char							timeBuf[CONST_qyTimeLen  +  1]		=	"";
				  TASK_DISPLAY					taskDisplay;
				  char							buf[255  +  1]						=	"";
				  int							nItem;
				  int							iStatus;

				  #ifndef  __WINCE__
						   //  CListCtrl		*	pListCtrl;
						   //  pListCtrl  =	(  CListCtrl  *  )CWnd::FromHandle(  GetDlgItem(  hDlg,  m_var.idcList_task  )  );
						   //  if  (  !pListCtrl  )  goto  errLabel;
						   HWND  hListCtrl  =  mynull;
						   if (pmsgToolCommon) {
							   hListCtrl = GetDlgItem(hWnd_msgTool, pmsgToolCommon->idcList_task);
							   if (!hListCtrl) {
#ifdef  __DEBUG__
								   traceLog((TCHAR*)_T("tmpHandler_showMsg_displayTask failed: list_task is null"));
#endif
								   goto  errLabel;
							   }
						   }
				  #endif

				#ifdef  __SUPPORT_HTMLEDIT__
	
					    //  if  (  (  nItem  =  getTaskItem(  pListCtrl->m_hWnd,  pMsg->task.iTaskId  )  )  >=  0  )  
					    if  (  (  nItem  =  getTaskItem(  hListCtrl,  pMsg->task.iTaskId  )  )  >=  0  )  
						{
						  PARAM_PROC_ROW					param;												//  ´æÔÚÖØ·¢µÄ¿ÉÄÜÐÔ£¬ËùÒÔÐèÒªÔÚÕâÀïÐÞ¸Ä×´Ì¬¡£

						  iStatus  =  pMsg->task.iStatus;

						  memset(  &param,  0,  sizeof(  param  )  );
						  //  pListCtrl->GetItemText(  nItem,  1,  param.rowIdStr,  mycountof(  param.rowIdStr  )  );				  
						  myListCtrl_GetItemText(  hListCtrl,  nItem,  1,  param.rowIdStr,  mycountof(  param.rowIdStr  )  );
						  param.pf  =  (  PF_commonHandler  )modifyRow;
						  param.iCol  =  pDlgTalkVar->iCol_content;
						  if  (  tmpMakeHtmlStr( pQyMc, pMsg,  pMsg->task.iStatus, TRUE,  param.rowIdStr,  NULL,  &param.idInfo_talker,  param.content,  mycountof(  param.content  )  )  )  goto  errLabel;
						  
						  //
						  if  (  doDoc_doTable_byRowId_param(  pDlgTalkVar,  &param  )  )  goto  errLabel;

						  //
						  activateRowByRowId(  hDlgTalk,  param.rowIdStr  );

						  //  2007/07/22, °ÑtaskListµÄ¶ÔÓ¦ÐÐµÄrowIdStr_cur¸ÄÎª´ËÏî
						  //  pListCtrl->SetItemText(  nItem,  CONST_nSubItem_rowId_cur,  param.rowIdStr  );
						  myListCtrl_SetItemText(  hListCtrl,  nItem,  CONST_nSubItem_rowId_cur,  param.rowIdStr  );
						  //  pListCtrl->SetItemText(  nItem,  CONST_nSubItem_iStatus_cur,  _ltot(  iStatus,  tBuf,  10  )  );		  
						  myListCtrl_SetItemText(  hListCtrl,  nItem,  CONST_nSubItem_iStatus_cur,  _ltot(  iStatus,  tBuf,  10  )  );
						  //  pListCtrl->SetItemText(  nItem,  CONST_nSubItem_status,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskStatusTable  ),  iStatus  )  );		//  iStatus
						  myListCtrl_SetItemText(  hListCtrl,  nItem,  CONST_nSubItem_status,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskStatusTable  ),  iStatus  )  );		//  iStatus
						  //
						  //  pListCtrl->SetItemState(  nItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
						  myListCtrl_SetItemState(  hListCtrl,  nItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
						  //  pListCtrl->Update(  nItem  );
						  myListCtrl_Update(  hListCtrl,  nItem  );


						  break;
					  }
				#endif
					  //  ×¢Òâ£ºÆäËûÈÎÎñÒ²ÐèÒªÅÐ¶Ï£¬ÊÇ·ñÈÎÎñÒÑ¾­±»ÏÔÊ¾ÁË¡£Ö÷ÒªÔÚÏûÏ¢µ½Ê±£¬´°¿ÚÈç¹ûÕý¹Ø±Õ£¬Ôò½«±»¼¤·¢. Í¨¹ýÏûÏ¢ºÍ³õÊ¼»¯2ÖØ×÷ÓÃ£¬ÈÎÎñ½«±»ÖØ¸´ÏÔÊ¾¡£

					  //  2010/04/23
					  //  dlgTalk_displayAvStatus(  hDlgTalk,  *pDlgTalkVar,  0,  0,  0  );

					  //
					  memset(  &taskDisplay,  0,  sizeof(  taskDisplay  )  );
					  taskDisplay.id  =  pMsg->task.iTaskId;
				#ifndef  __WINCE__
					  lstrcpyn(  taskDisplay.rowIdStr,  rowIdStr,  mycountof(  taskDisplay.rowIdStr  )  );
				#endif
					  //
					  lstrcpyn(  taskDisplay.typeStr,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsg->task.uiTaskType  ),  mycountof(  taskDisplay.typeStr  )  );
					  switch  (  pContent->uiType  )  {
							  case  CONST_imCommType_transferFileReq:
								    unsigned  __int64  tmp_ui64;
								    lstrcpyn(  taskDisplay.subject,  pContent->transferFileReq.fileName,  mycountof(  taskDisplay.subject  )  );
									tmp_ui64  =  pContent->transferFileReq.ui64FileLen;
									if  (  tmp_ui64  <  1024  *  1024  )  _sntprintf(  taskDisplay.subject,  mycountof(  taskDisplay.subject  ),  _T(  "%s %I64uK"  ),  taskDisplay.subject,  tmp_ui64  /  (  1024  )  );
									else  _sntprintf(  taskDisplay.subject,  mycountof(  taskDisplay.subject  ),  _T(  "%s %I64uM"  ),  taskDisplay.subject,  tmp_ui64  /  (  1024  *  1024  )  );
									break;
							  case  CONST_imCommType_rtcCallReq:	//  
								    traceLogA(  (char*)  "Not supported."  );  goto  errLabel;
								    break;
							  case  CONST_imCommType_transferAvInfo:
								    //
								    if  (  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biWidth  &&  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biHeight  )  {
										_sntprintf(  taskDisplay.subject,  mycountof(  taskDisplay.subject  ),  _T(  "%d * %d"  ),  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biWidth,  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biHeight  );
									}
								    //
								    break;
							  case  CONST_imCommType_queryCustomerServiceOfficerReq:	//  2011/04/06
								    break;
							  default:
								      traceLog((TCHAR*)  _T(  "tmpHandler_showMsg: unprocessed contentType %d"  ),  pContent->uiType  );
								      goto  errLabel;
					  }
					  //
					  taskDisplay.iStatus  =  pMsg->task.iStatus;
					  //
					  //  taskDisplay.idInfo_send.ui64Id  =  pMsg->task.idInfo_taskSender.ui64Id;
					  getTalkerDesc(  pMsg->task.idInfo_taskSender,  NULL,  0,  taskDisplay.displayName_sender,  mycountof(  taskDisplay.displayName_sender  )  );  
					  if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
						  if  (  pContent->transferAvInfo.confCfg.ucbVideoConference  )  {
							  _sntprintf(  taskDisplay.displayName_sender,  mycountof(  taskDisplay.displayName_sender  ),  _T(  "%I64u"  ),  pMsg->task.data.route.idInfo_from.ui64Id  );							  
						  }
					  }
					  //
					  taskDisplay.tSendTime  =  pMsg->task.tStartTime;
					  taskDisplay.tRecvTime  =  pMsg->task.tRecvTime;
					  //										
					  //  2007/07/18
					  //
				#ifndef  __WINCE__
					  //  addToTaskList(  pParam,  &taskDisplay,  pListCtrl  );
					  addToTaskList(  pQyMc,  pParam,  &taskDisplay,  hListCtrl  );
				#endif

					  if  (  tmpMakeHtmlStr( pQyMc, pMsg,  pMsg->task.iStatus, TRUE,  rowIdStr,  NULL,  &idInfo_talker,  tBuf,  mycountof(  tBuf  )  )  )  goto  errLabel;
				#ifndef  __SUPPORT_HTMLEDIT__
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  taskDisplay.typeStr,  taskDisplay.subject  );
				#endif

					  {
						  BOOL  bScrollIntoView  =  pParam->bScrollIntoView;
						  //									
						  pParam->bScrollIntoView  =  FALSE;
						  //
						  if  (  pMsg->task.tStartTime  )  getTimeStr(  pMsg->task.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
						  addToRecentMsg(  hDlgTalk,  pDlgTalkVar,  pParam->bAddOnRowIndex  ?  pParam->lRowIndex  :  -1,  pMsg->task.iTaskId,  pMsg,  mynull,  idInfo_talker,  taskDisplay.displayName_sender,  CONST_imOp_tryToSendFile,  pMsg->task.iStatus,  timeBuf,  rowIdStr,  tBuf,  pParam->bFollowingRows,  pParam->bScrollIntoView,  txtContent,  mycountof(  txtContent  )  );	
						  //
						  pParam->bScrollIntoView  =  bScrollIntoView;
					  }
					  MIS_CNT	*	pMisCnt;  
					  pMisCnt	=	(  MIS_CNT  *  )pMsg->task.pMisCnt;
					  if  (  !pMisCnt  )  {
						  traceLog((TCHAR*)  _T(  "tmpHandler_showMsg failed: task.pMisCnt is null"  )  );
						  goto  errLabel;
					  }

					  if  (  isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  {
						  #ifndef  __WINCE__
								   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  taskDisplay.subject  );
								   if  (  pMsg->task.data.route.idInfo_from.ui64Id  !=  pMisCnt->idInfo.ui64Id  )  
					      #endif					  
								   {
									   showNotification(  pMsg->task.pMisCnt,  &pMsg->task.addr_logicalPeer.idInfo,  &pMsg->task.data.route.idInfo_from,  pMsg->task.tStartTime,  pMsg->task.uiTranNo,  pContent->uiType,  tBuf  );
								   }
					  }


					  //
				#ifdef  __SUPPORT_HTMLEDIT__
					  if  (  pParam->bScrollIntoView  )  activateRowByRowId(  hDlgTalk,  rowIdStr  );
								
					  #ifdef  __DEBUG__
					  if (pmsgToolCommon) {
						  printHtmlEdit(pmsgToolCommon->m_pHtmlEdit_recentMsgList);
					  }
					  #endif
				#endif
					  }
					  //
					  break;
			default:
				    goto  errLabel;
					break;
						  
	}

	iErr  =  0;

errLabel:
	
	return  iErr;

}



//  2012/05/02
int  tmpHandler_showMsg_displayTaskStatus(  HWND  hDlg,  DLG_TALK_var  *  pm_var,  MIS_MSG_TASKSTATUS  *  pMsgTaskStatus,  MIS_MSG_TASK  *  pMsgTask,  IM_CONTENTU  *  pContent,  int  iStatus  )
{
	int					iErr	=	-1;
	TCHAR				txtContent[1024]		=	_T(  ""  );
	TCHAR				tBuf[1024]				=	_T(  ""  );

	if  (  !pm_var  )  return  -1;
	DLG_TALK_var  &  m_var  =  *pm_var;
	QY_MC* pQyMc = m_var.pQyMc;// QY_GET_GBUF();

		//  2016/03/13
#if  0
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ": %I64u, tn_shadow %d, iStatus %d"  ),  m_var.addr.idInfo.ui64Id,  m_var.addr.uiTranNo_shadow,  pMsgTaskStatus->iStatus  );
	showInfo_open0(  0,  _T(  "tmpHandler_showMsg_displayTaskStatus"  ),  tBuf  );
#endif


	//
	MSG_tool_common* pmsgToolCommon = mynull;
	//
	HWND	hDlgMsgTool  =  m_var.msgTool.hWnd_msgTool;
	DLG_msgTool_var  *  pDlgMsgToolVar  =  (  DLG_msgTool_var  *  )getDlgMsgToolVar(  hDlgMsgTool  );
	if (pDlgMsgToolVar) {
		pmsgToolCommon = &pDlgMsgToolVar->msgToolCommon;
	}

	//
	#ifndef  __WINCE__
		     //  CListCtrl		*	pListCtrl				=	(  CListCtrl  *  )CWnd::FromHandle(  GetDlgItem(  hDlg,  m_var.idcList_task  )  );
			 //  if  (  !pListCtrl  )  goto  errLabel;
			 HWND		hListCtrl = mynull;
			 if (pmsgToolCommon) {
				 hListCtrl = GetDlgItem(hDlgMsgTool, pmsgToolCommon->idcList_task);
				 if (!hListCtrl)  goto  errLabel;
			 }
    #endif

	int								nItem				=	0;
	MIS_MSG_imMsgRcd					msgImMsgRcd;

    #ifdef  __SUPPORT_HTMLEDIT__
	        //  nItem  =  getTaskItem(  pListCtrl->m_hWnd,  pMsgTaskStatus->iTaskId  );						
			nItem  =  getTaskItem(  hListCtrl,  pMsgTaskStatus->iTaskId  );
			if  (  nItem  <  0  )  {
				traceLogA(  (char*)  "CDlgTalk::OnQyComm(  ): getTaskItem failed"  );  
				goto  errLabel;
			}	
	#endif


	PARAM_PROC_ROW					param;

	memset(  &param,  0,  sizeof(  param  )  );
	param.pf  =  (  PF_commonHandler  )modifyRow;
	param.iCol  =  m_var.iCol_content;



	//
	switch  (  pMsgTaskStatus->iStatus  )  {	
			case  CONST_imTaskStatus_sending:
			case  CONST_imTaskStatus_receiving:
				  #ifdef  __SUPPORT_HTMLEDIT__	
						  //  
						  //  pListCtrl->GetItemText(  nItem,  CONST_nSubItem_iStatus_cur, tBuf,  mycountof(  tBuf  )  );
						  //  iStatus  =  _ttol(  tBuf  );								
							  
						  //_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d%%( %I64uk )"  ),  pMsgTaskStatus->u.transferFileStatus.ucPercent,  pMsgTaskStatus->u.transferFileStatus.ui64Len_recvd  /  1024  );
						  M_getTransferFileStatus_str(  pMsgTaskStatus->u.transferFileStatus,  tBuf,  mycountof(  tBuf  )  );  //  2015/08/06
						  //  pListCtrl->SetItemText(  nItem,  m_var.nSubItem_status,  tBuf  );
						  myListCtrl_SetItemText(  hListCtrl,  nItem,  m_var.nSubItem_status,  tBuf  );

				  #else
					    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d%%(%I64uk)"  ),  pMsgTaskStatus->u.transferFileStatus.ucPercent,  pMsgTaskStatus->u.transferFileStatus.ui64Len_recvd  /  1024  );						
						addToRecentMsg(  hDlg,  &m_var,  -1,  pMsgTaskStatus->iTaskId,  null,  null,  pMsgTaskStatus->idInfo_mem,  NULL,  CONST_imOp_tryToSendFile,  pMsgTaskStatus->iStatus,  NULL,  NULL,  tBuf,  0,  0,  0,  0  );								
				  #endif
				  //
				  //
				  break;				
			case  CONST_imTaskStatus_sendFinished:						
			case  CONST_imTaskStatus_recvFinished:
			case  CONST_imTaskStatus_canceledBySender:
			case  CONST_imTaskStatus_canceledByReceiver:
			case  CONST_imTaskStatus_autoCanceledByReceiver:	//  2014/07/30
				  
				  //
				  #ifdef  __DEBUG__
						  showInfo_open0(  0,   _T(  ""  ),  _T(  "tmpHandler_showMsg_displayTaskStatus: finished...."  )  );
				  #endif

				  //
				  if  (  pMsgTaskStatus->iStatus  ==  CONST_imTaskStatus_sendFinished  &&  pMsgTaskStatus->bImGrpMem  )  {	//  ¶ÔÓÚ·Ö×é£¬³ÉÔ±²»ÄÜ¸Ä±äÈÎÎñ×´Ì¬¡£¹ÊÖ±½ÓÏÔÊ¾Ò»¸öÏûÏ¢£¬¼ÓÇ¿Ö±¹ÛÐÔ

					  if  (  tmpMakeHtmlStr(  pQyMc,(  MIS_MSGU  *  )pMsgTaskStatus,  pMsgTaskStatus->iStatus,  FALSE,  0,  NULL,  NULL,  param.content,  mycountof(  param.content  )  )  )  goto  errLabel;

					  addToRecentMsg(  hDlg,  &m_var,  -1,  pMsgTaskStatus->iTaskId,  mynull,  mynull,  pMsgTaskStatus->idInfo_mem,  NULL,  CONST_imOp_tryToSendFile,  pMsgTaskStatus->iStatus,  NULL,  NULL,  param.content,  FALSE,  TRUE,  0,  0  );
					  //  printHtmlEdit(  &pDlg->m_htmlEdit_recentMsgList  );

					  //  
					  activateWnd(  hDlg,  m_var  );

					  break;
				  }

				  #ifdef  __SUPPORT_HTMLEDIT__  //  {

						  if  (  !pMsgTaskStatus->uiTaskType  )  {							
								//  pListCtrl->GetItemText(  nItem,  CONST_nSubItem_uiTaskType,  tBuf,  mycountof(  tBuf  )  );							
							  myListCtrl_GetItemText(  hListCtrl,  nItem,  CONST_nSubItem_uiTaskType,  tBuf,  mycountof(  tBuf  )  );
							  pMsgTaskStatus->uiTaskType  =  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  tBuf  );						
						  }							
						  //						
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskStatusTable  ),  pMsgTaskStatus->iStatus  )  );							
						  //  pListCtrl->SetItemText(  nItem,  m_var.nSubItem_status,  tBuf  );
						  myListCtrl_SetItemText(  hListCtrl,  nItem,  m_var.nSubItem_status,  tBuf  );

						  //								
						  //  pListCtrl->GetItemText(  nItem,  CONST_nSubItem_rowId_cur,  param.rowIdStr,  mycountof(  param.rowIdStr  )  );  						
						  myListCtrl_GetItemText(  hListCtrl,  nItem,  CONST_nSubItem_rowId_cur,  param.rowIdStr,  mycountof(  param.rowIdStr  )  );  						
						  if  (  tmpMakeHtmlStr( pQyMc, (  MIS_MSGU  *  )pMsgTaskStatus,  iStatus,  FALSE,  NULL,  NULL,  NULL,  param.content,  mycountof(  param.content  )  )  )  goto  errLabel;
										 
						  //
						  if  (  doDoc_doTable_byRowId_param(  &m_var,  &param  )  )  goto  errLabel;
						  //  
						  lstrcpyn(  param.rowIdStr,  getNextRowIdStr(  hDlg  ),  mycountof(  param.rowIdStr  )  );
						  //  
						  if  (  tmpMakeHtmlStr(  pQyMc,(  MIS_MSGU  *  )pMsgTaskStatus,  iStatus,  TRUE,  param.rowIdStr,  NULL,  &param.idInfo_talker,  param.content,  mycountof(  param.content  )  )  )  goto  errLabel;
						  //
						  if  (  param.lRowIndex_who_gotByRowId  ==  -1  )  param.lRowIndex  =  -1;
						  else  param.lRowIndex  =  param.lRowIndex_who_gotByRowId  +  2;	//  ¼Ó£²ÊÇÒòÎªÓÐ·¢ÑÔÈËºÍÁÄÌìÄÚÈÝ£²ÐÐ
						  param.bFollowingRows  =  TRUE;
						  //
						  addToRecentMsg(  hDlg,  &m_var,  param.lRowIndex,  0,  mynull,  mynull,  param.idInfo_talker,  NULL,  CONST_imOp_tryToSendFile,  0,  NULL,  param.rowIdStr,  param.content,  param.bFollowingRows,  param.bScrollIntoView,  msgImMsgRcd.rcd.txtContent,  mycountof(  msgImMsgRcd.rcd.txtContent  )  );									
						  //					
						  activateRowByRowId(  hDlg,  param.rowIdStr  );

						  //  2007/07/22, °ÑtaskListµÄ¶ÔÓ¦ÐÐµÄrowIdStr_cur¸ÄÎª´ËÏî
						  //  pListCtrl->SetItemText(  nItem,  CONST_nSubItem_rowId_cur,  param.rowIdStr  );
						  myListCtrl_SetItemText(  hListCtrl,  nItem,  CONST_nSubItem_rowId_cur,  param.rowIdStr  );
						  //  pListCtrl->SetItemText(  nItem,  CONST_nSubItem_iStatus_cur,  _ltot(  iStatus,  tBuf,  10  )  );	
						  myListCtrl_SetItemText(  hListCtrl,  nItem,  CONST_nSubItem_iStatus_cur,  _ltot(  iStatus,  tBuf,  10  )  );
				  #else
						  tBuf[0]  =  0;
						  QY_MESSENGER_ID idInfo_talker; idInfo_talker.ui64Id = 0;
						  addToRecentMsg(  hDlg,  &m_var,  -1,  pMsgTaskStatus->iTaskId,  null,  null,  idInfo_talker,  NULL,  CONST_imOp_tryToSendFile,  pMsgTaskStatus->iStatus,  NULL,  NULL,  tBuf,  0,  0,  0,  0  );																		
						  showNotification(  pMsgTask->pMisCnt,  NULL,  NULL,  0,  0,  pContent->uiType,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskStatusTable  ),  pMsgTaskStatus->iStatus  )  );
				  #endif

				
				  //  				
				  activateWnd(  hDlg,  m_var  );
				  break;
				
			default:
					#ifdef  __SUPPORT_HTMLEDIT__
						    if  (  !pMsgTaskStatus->uiTaskType  )  {							
								//  pListCtrl->GetItemText(  nItem,  CONST_nSubItem_uiTaskType,  tBuf,  mycountof(  tBuf  )  );							
								myListCtrl_GetItemText(  hListCtrl,  nItem,  CONST_nSubItem_uiTaskType,  tBuf,  mycountof(  tBuf  )  );
								pMsgTaskStatus->uiTaskType  =  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  tBuf  );
							}
							//
							_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskStatusTable  ),  pMsgTaskStatus->iStatus  )  );
							//  pListCtrl->SetItemText(  nItem,  m_var.nSubItem_status,  tBuf  );
							myListCtrl_SetItemText(  hListCtrl,  nItem,  m_var.nSubItem_status,  tBuf  );
					#else

					#endif

					//					
				    break;				  
				  
	}									 



	iErr  =  0;
errLabel:
	return  iErr;
}



 //  2012/05/17
 BOOL  bReady_toShowMsg(  HWND  hCurTalk  )
{
	BOOL	bRet	=	FALSE;
	// 因为将htmlEdit从dlgTalk中移走，所以不需要考虑初始化未完成的问题了. 2014/01/27

    bRet  =  TRUE;

errLabel:

	return  bRet;

}

#ifdef  __DEBUG__

 int  dlgTalk_printHtmlEdit(  DLG_TALK_var  *  pDlgTalkVar  )
 {
	 if  (  !pDlgTalkVar  )  return  -1;
 							  
	 DLG_msgTool_var  *  pDlgMsgToolVar  =  (  DLG_msgTool_var  *  )getDlgMsgToolVar(  pDlgTalkVar->msgTool.hWnd_msgTool  );	
	 if  (  !pDlgMsgToolVar  )  return  -1;
	MSG_tool_common  &msgToolCommon			=  pDlgMsgToolVar->msgToolCommon;
	HWND				hWnd_msgTool		=	pDlgTalkVar->msgTool.hWnd_msgTool;


	printHtmlEdit(  msgToolCommon.m_pHtmlEdit_recentMsgList  );

	return  0;
 }


#endif


 //  2014/07/12
 int  tmpMakeHtmlStr_talk(  HWND  hDlg,  DLG_TALK_var  *  pDlgTalkVar,  MIS_MSG_TALK  *  pMsg,  TCHAR  *  strBuf,  unsigned  int  cnt   )
{
	int		iErr		=	-1;
	TCHAR	tBuf[512]	=	_T(  ""  );
	QY_MC* pQyMc = pDlgTalkVar->pQyMc;// QY_GET_GBUF();

	int				iStatus  =  pMsg->iStatus;
	IM_CONTENTU  *  pContent  =  M_getMsgContent(  pMsg->ucFlg,  &pMsg->data  );
	BOOL			bSendByMe  =  pMsg->data.route.idInfo_from.ui64Id  ==  pDlgTalkVar->pMisCnt->idInfo.ui64Id;
	
	switch  (  pContent->uiType  )  {
			case  CONST_imCommType_htmlContent:
				  if  (  bSendByMe  &&  pDlgTalkVar->addr.uiObjType  ==  CONST_objType_messenger  )  {
					  if  (  iStatus  ==  CONST_imTaskStatus_sendFinished  )  safeTcsnCpy(  pContent->html.wBuf,  tBuf,  mycountof(  tBuf  )  );					  
					  else  {
						    //_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s (%s)"  ),  pContent->html.wBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_notArrived  )  );
						  _sntprintf(tBuf, mycountof(tBuf), _T("%s"), pContent->html.wBuf);
					  }
					  }
				  else  {
					    safeTcsnCpy(  pContent->html.wBuf,  tBuf,  mycountof(  tBuf  )  );
				  }				  
				  break;
			default:
					break;
	}


	iErr  =  0;
errLabel:

	safeTcsnCpy(  tBuf,  strBuf,  cnt  );

	return  0;
}



 //
#if  0
 int  clearShownMsg_d3d(  HWND  hDlg  )
 {
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pm_var					=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlg  );
	if  (  !pm_var  )  return  -1;	
	DLG_TALK_var	&	m_var					=	*pm_var;

	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;	
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
	SUBTITLE_msgs  *  pSubtitleMsgs  =  &pShadowMgr->msg.msgs;
	
	//  2014/12/23	
	//SUBTITLE_msgs  *  pSubtitleMsgs;  pSubtitleMsgs  =  &pShadowMgr->msg.msgs;
					
	//		
	pSubtitleMsgs->dwModifiedTickCnt_any_start  =  GetTickCount(  );		

	//
	memset(  &pSubtitleMsgs->mems,  0,  sizeof(  pSubtitleMsgs->mems  )  );

	//									
	pSubtitleMsgs->dwModifiedTickCnt_any_end  =  pSubtitleMsgs->dwModifiedTickCnt_any_start;

	return  0;
 }
#endif






 //  2014/07/12
  int  tmpHandler_showMsg_talk(  void  *  hDlgTalkParam,  DLG_TALK_var	&	m_var,  void  *  p1, void  *  pMsgParam  )
{
	int  iErr  =  -1;

		HWND				hDlg					=	(  HWND  )hDlgTalkParam;
		
		PARAM_PROC_ROW	*	pParam					=	(  PARAM_PROC_ROW  *  )p1;
		MIS_MSGU		*	pMsg					=	(  MIS_MSGU  *  )pMsgParam;
	
		QY_MC* pQyMc = m_var.pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli	*	pProcInfo				=	QY_GET_procInfo_isCli(  );	//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	TCHAR				txtContent[1024]		=	_T(  ""  );
	TCHAR				senderDesc[255  +  1]	=	_T(  ""  );
	TCHAR				receiverDesc[255  +  1]	=	_T(  ""  );
	time_t				t;

		int					tmpiRet					=	0;
	//
	TCHAR				tBuf[1024]				=	_T(  ""  );
	int					i;
	//
	
	if  (  !hDlg  ||  !pParam  ||  !pMsg  )  return  -1;

	#ifndef  __WINCE__
		     CQyString				rowIdStr							=	getRowIdStr_talk(  hDlg,  &pMsg->talk  );
	#else
			TCHAR				rowIdStr[1]							=	_T(  ""  );
	#endif





					  MIS_MSG_routeTalkData		*	pTalkData							=	&pMsg->talk.data;
					  IM_CONTENTU				*	pContent							=	(  IM_CONTENTU  *  )pTalkData->buf;	
					  char							timeBuf[CONST_qyTimeLen  +  1]		=	"";
					  TCHAR							displayContent[1024]				=	_T(  ""  );

					  activateWnd(  hDlg,  m_var  );		//  ÕâÀïÒªÉÁÁÁ¶Ô»°¿ò¡£ÌáÐÑÓÃ»§µÄ×¢Òâ
					  //  m_var.ucbNewMsgArrives  =  TRUE;
					  dlgTalk_set_newMsgArrives(  hDlg,  &m_var,  TRUE  );
					  //  2016/03/25
					  m_var.msgTool.dwModifiedTickCnt_showMsgTalk  =  myGetTickCount(  &pQyMc->gui.ctx_gui_thread  );

					  //
					  if  (  pTalkData->route.uiObjType_src  ==  CONST_objType_webGuest  )  {
						  char				ip[15  +  1]	=  "";
						  QY_DMITEM		*	pItem			=	NULL;
						  //
						  ulIp2Str(  pTalkData->route.ulDetectedIp_from,  ip,  mycountof(  ip  )  );
						  pItem  =  qyGetDmItemByType(  (  QY_DMITEM  *  )CONST_langStrTable, pTalkData->route.usLangId_from,  sizeof(  CONST_langStrTable[0]  )  ); 
						  _sntprintf(  senderDesc,  mycountof(  senderDesc  ),  _T(  "Guest%d(%s,%s)"  ),  pTalkData->route.uiLogonId,  CQyString(  ip  ).GetBuffer(  0  ),  (  pItem  &&  pItem->des  )  ?  pItem->des  :  _T(  ""  )  );
						  //
						  //  uiWebSessId.
						  if  (  m_var.addr.uiLogonId  !=  pTalkData->route.uiLogonId  )  m_var.addr.uiLogonId  =  pTalkData->route.uiLogonId;

					  }

					  //  2014/12/23
					  if  (  !senderDesc[0]  )  {					  	
						  pFuncs->pf_getTalkerDesc(  pTalkData->route.idInfo_from,  NULL,  0,  senderDesc,  mycountof(  senderDesc  )  );
					  }
					  
					  //
					  switch  (  pContent->uiType  )  {
							  case  CONST_imCommType_htmlContent:

								    //  2014/07/12
								    if  (  m_var.addr.uiObjType  ==  CONST_objType_messenger  )  {
										if  (  pMsg->talk.data.route.idInfo_from.ui64Id  !=  m_var.pMisCnt->idInfo.ui64Id  )  {
											mySendTalkResp(  pProcInfo,  &pMsg->talk,  NULL  );
										}
									}


								    //
								    if  (  pMsg->talk.tStartTime  )  getTimeStr(  pMsg->talk.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
									tmpMakeHtmlStr_talk(  hDlg,  &m_var,  &pMsg->talk,  displayContent,  mycountof(  displayContent  )  );

									//  2012/04/30
									if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;
									TALKER_shadow_mgr  *  pShadowMgr;
									pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
									if  (  !pShadowMgr  )  goto  errLabel;
									for  (  i  =   0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
										if  (  pShadowMgr->shadows[i].hShadow  &&  isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  {
											CHelp_getDlgTalkVar	help_getDlgTalkVar;
											DLG_TALK_var  *  pVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  pShadowMgr->shadows[i].hShadow  );
											if  (  pVar  )  {
												//
												addToRecentMsg(  pShadowMgr->shadows[i].hShadow,  pVar,  -1,  0,  pMsg,  mynull,  pTalkData->route.idInfo_from,  senderDesc,  CONST_imOp_says,  0,  timeBuf,  rowIdStr,  displayContent,  pParam->bFollowingRows,  pParam->bScrollIntoView,  txtContent,  mycountof(  txtContent  )  );

												//
												#ifdef  __DEBUG__  
														//  2014/01/26
														dlgTalk_printHtmlEdit(  pVar  );
												#endif
											}
										}
									}
									//if  (  !m_var.guiData.param.bNeedNotShowWnd  )  
									{
										addToRecentMsg(  hDlg,  &m_var,  -1,  0,  pMsg,  mynull,  pTalkData->route.idInfo_from,  senderDesc,  CONST_imOp_says,  0,  timeBuf,  rowIdStr,  displayContent,  pParam->bFollowingRows,  pParam->bScrollIntoView,  txtContent,  mycountof(  txtContent  )  );

										//
										#ifdef  __DEBUG__  
												//  2014/01/26
												dlgTalk_printHtmlEdit(  &m_var  );
										#endif
									}

									if  (  pMsg->talk.data.route.idInfo_from.ui64Id  !=  m_var.pMisCnt->idInfo.ui64Id  )  {
										//
										showNotification(  pMsg->talk.pMisCnt,  &pMsg->talk.addr_logicalPeer.idInfo,  &pMsg->talk.data.route.idInfo_from,  pMsg->talk.tStartTime,  pMsg->talk.uiTranNo,  pContent->uiType,  pContent->html.wBuf  );
									}

									//  2014/12/23
								#if  0
									SUBTITLE_msgs  *  pSubtitleMsgs;  pSubtitleMsgs  =  &pShadowMgr->msg.msgs;
									//
									pSubtitleMsgs->dwModifiedTickCnt_any_start  =  GetTickCount(  );
									//
									int  i;
									for  (  i  =  0;  i  <  mycountof(  pSubtitleMsgs->mems  )  -  1;  i  ++  )  {
										 SUBTITLE_msg  *  pMem_cur  =  &pSubtitleMsgs->mems[i];
										 SUBTITLE_msg  *  pMem_next  =  &pSubtitleMsgs->mems[i  +  1];
										 *pMem_cur  =  *pMem_next;
									}
									SUBTITLE_msg  *  pMem_last;  pMem_last  =  &pSubtitleMsgs->mems[i];
									memset(  pMem_last,  0,  sizeof(  *pMem_last  )  );
									pMem_last->dwTickCnt_recvd  =  GetTickCount(  );
									pMem_last->idInfo_sender.ui64Id  =  pTalkData->route.idInfo_from.ui64Id;
									safeTcsnCpy(  senderDesc,  pMem_last->talkerDesc,  mycountof(  pMem_last->talkerDesc  )  );
									safeTcsnCpy(  displayContent,  pMem_last->tBuf,  mycountof(  pMem_last->tBuf  )  );
									//
									pSubtitleMsgs->dwModifiedTickCnt_any_end  =  pSubtitleMsgs->dwModifiedTickCnt_any_start;
								#endif
									//
									showMsg_d3d(  hDlg,  &pTalkData->route.idInfo_from,  senderDesc,  displayContent  );
									

								#if  0
									if  (  pParam->bNewMsg  )  {
										getTalkerDesc(  m_var.pMisCnt,  &pTalkData->route.idInfo_to,  receiverDesc,  mycountof(  receiverDesc  ),  NULL,  0  );
										postImMsg2Log(  m_var.pMisCnt->cfg.misServName,  &pTalkData->route.idInfo_from,  senderDesc,  pMsg->talk.tStartTime,  pMsg->talk.uiTranNo,  &pTalkData->route.idInfo_to,  receiverDesc,  pContent->uiType,  pContent->html.wBuf,  txtContent,  t,  &pProcInfo->schedulerQ  );
									}
								#endif
									//
									break;
							  default:
								      //  traceLogA(  (char*)  "tmpHandler_showMsg: Î´´¦Àí%SµÄÊý¾ÝÄÚÈÝ",  qyGetDesByType1(  CONST_pcCommTypeTable,  pContent->uiType  )  );
									  break;
					  }


				  

				  iErr  =  0;
errLabel:
				  return  iErr;
}



//
BOOL  bAutoAccepted_avCall(  HWND  hDlgTalk,  QY_imObj_rules  *  pRules,  unsigned  int  uiTaskType  )
{
	BOOL  bRet  =  FALSE;
	
	CHelp_getDlgTalkVar  help;
	DLG_TALK_var  *  pm_var  =  (  DLG_TALK_var  *  )help.getVar(  hDlgTalk  );
	if  (  !pm_var  )  goto  errLabel;
	if  (  !isTalkerShadowMgr(  pm_var->addr  )  )  goto  errLabel;
	DLG_TALK_var  *  pMgrVar  =  pm_var;

	QY_MC* pQyMc = pMgrVar->pQyMc;// QY_GET_GBUF();

	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  goto  errLabel;

	//
	switch  (  uiTaskType  )  {
			case  CONST_imTaskType_transferAvInfo:
			case  CONST_imTaskType_shareDevice_grp:
				  if  (  pMgrVar->av.taskInfo.bTaskExists  )  goto  errLabel;
				  //
				  if  (  pRules->uiCmd_autoAnswer_av  )  {								
					  if  (  isRuleCmdPermit(  pRules->uiCmd_autoAnswer_av  )  )  {
						  bRet  =  TRUE;  goto  errLabel;								
					  }									  
					  }						
				  else  if  (  isRuleCmdPermit(  pProcInfo->cfg.policy.avRules.uiCmd_autoAnswer_av  )  )  {										 
							bRet  =  TRUE;  goto  errLabel;								  
				  }
				  break;

			case  CONST_imTaskType_shareScreen:
				  if  (  dyn_bD3dUsing(  pProcInfo,  NULL  )  )  {
					  if  (  !pMgrVar->av.taskInfo.bTaskExists  )  goto  errLabel;
					  //
					  if  (  pRules->uiCmd_autoAnswer_screen  )  {
						  if  (  pRules->uiCmd_autoAnswer_screen  ==  CONST_ruleCmd_manual  )  goto  errLabel;
					  }
					  //
					  bRet  =  TRUE;  goto  errLabel;
					  break;
				  }
				  //
				  if  (  pRules->uiCmd_autoAnswer_screen  )  {								
					  if  (  isRuleCmdPermit(  pRules->uiCmd_autoAnswer_screen  )  )  {
						  bRet  =  TRUE;  goto  errLabel;								
					  }									  
					  }						
				  else  if  (  isRuleCmdPermit(  pProcInfo->cfg.policy.avRules.uiCmd_autoAnswer_av  )  )  {										 
							bRet  =  TRUE;  goto  errLabel;								  
				  }
				  break;
			case  CONST_imTaskType_remoteAssist:  {
				  //
				  if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_bjyz  )  {
					  bRet  =  TRUE;  goto  errLabel;
				  }
				  }
				  break;
			case  CONST_imTaskType_shareMediaFile:
				  if  (  dyn_bD3dUsing(  pProcInfo,  NULL  )  )  {
					  if  (  !pMgrVar->av.taskInfo.bTaskExists  )  goto  errLabel;
					  //
					  if  (  pRules->uiCmd_autoAnswer_mediaFile  )  {
						  if  (  pRules->uiCmd_autoAnswer_mediaFile  ==  CONST_ruleCmd_manual  )  goto  errLabel;
					  }
					  //
					  bRet  =  TRUE;  goto  errLabel;
					  break;
				  }
				  //
				  if  (  pRules->uiCmd_autoAnswer_mediaFile  )  {								
					  if  (  isRuleCmdPermit(  pRules->uiCmd_autoAnswer_mediaFile  )  )  {
						  bRet  =  TRUE;  goto  errLabel;								
					  }									  
					  }						
				  else  if  (  isRuleCmdPermit(  pProcInfo->cfg.policy.avRules.uiCmd_autoAnswer_av  )  )  {										 
							bRet  =  TRUE;  goto  errLabel;								  
				  }
				  break;
			default:
					break;
	}

errLabel:

	return  bRet;
}



//
int  store_ConfMem_confCtrl(  QY_MC  *  pQyMc,  ConfMem_confCtrl  *  pConfCtrl,  QY_MESSENGER_ID  *  pIdInfo  )
{
	int  iErr  =  -1;
	//QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;

			 QM_OBJQ_MEM				mem;
			 QMEM_MESSENGER_CLI		*	pQMem	=	NULL;
			 QY_MESSENGER_INFO			messengerInfo;
			 void					*	pDb		=	NULL;
			 int						i;

			 CQnmDb						tmpObjDb;						
			 pDb				=		tmpObjDb.getAvailableDb(  pQyMc->iDsnIndex_mainSys  );

			 //
			 if  (  !pConfCtrl  )  return  -1;



			 //  ÏÈÓÃregInfoÌî³äÒ»ÏÂmessengerInfo, ÒòÎªÏÂÃæµÄpClientÖ»ÄÜÖ¸ÏòmessengerInfo
			 memset(  &messengerInfo,  0,  sizeof(  messengerInfo  )  );
			 //
			 //lstrcpyn(  messengerInfo.misServName,  regInfo.addr.misServName,  mycountof(  messengerInfo.misServName  )  );
			 messengerInfo.idInfo.ui64Id  =  pIdInfo->ui64Id;//  regInfo.addr.idInfo.ui64Id;

			 //               
			 if  (  procQmObjQ(  pProcInfo->pSgiParam,  (  QM_OBJQ  *  )pMisCnt->pObjQ,  pDb,  pQyMc->cfg.db.iDbType,  CONST_objType_messenger,  &messengerInfo,  &mem  )  )  goto  errLabel;
			 if  (  !mem.pQMemObj  )  goto  errLabel;

			 pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;

			 //
			 if  (  memcmp(  pConfCtrl,  &pQMem->confMem_confCtrl,  sizeof(  ConfMem_confCtrl  )  )  )  {
				 memcpy(  &pQMem->confMem_confCtrl,  pConfCtrl,  sizeof(  ConfMem_confCtrl  )  );
			 }

			 iErr  =  0;
errLabel:


			 return  iErr;
}

//
//
int  get_ConfMem_confCtrl(  QY_MC  *  pQyMc,  QY_MESSENGER_ID  *  pIdInfo,  ConfMem_confCtrl  *  pConfCtrl  )
{
	int  iErr  =  -1;
	//QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;

			 QM_OBJQ_MEM				mem;
			 QMEM_MESSENGER_CLI		*	pQMem	=	NULL;
			 QY_MESSENGER_INFO			messengerInfo;
			 void					*	pDb		=	NULL;
			 int						i;

			 CQnmDb						tmpObjDb;						
			 pDb				=		tmpObjDb.getAvailableDb(  pQyMc->iDsnIndex_mainSys  );

			 //
			 if  (  !pConfCtrl  )  return  -1;



			 //  ÏÈÓÃregInfoÌî³äÒ»ÏÂmessengerInfo, ÒòÎªÏÂÃæµÄpClientÖ»ÄÜÖ¸ÏòmessengerInfo
			 memset(  &messengerInfo,  0,  sizeof(  messengerInfo  )  );
			 //
			 //lstrcpyn(  messengerInfo.misServName,  regInfo.addr.misServName,  mycountof(  messengerInfo.misServName  )  );
			 messengerInfo.idInfo.ui64Id  =  pIdInfo->ui64Id;//  regInfo.addr.idInfo.ui64Id;

			 //               
			 if  (  procQmObjQ(  pProcInfo->pSgiParam,  (  QM_OBJQ  *  )pMisCnt->pObjQ,  pDb,  pQyMc->cfg.db.iDbType,  CONST_objType_messenger,  &messengerInfo,  &mem  )  )  goto  errLabel;
			 if  (  !mem.pQMemObj  )  goto  errLabel;

			 pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;

			 //
			 if  (  memcmp(  pConfCtrl,  &pQMem->confMem_confCtrl,  sizeof(  ConfMem_confCtrl  )  )  )  {
				 memcpy(  pConfCtrl,  &pQMem->confMem_confCtrl,  sizeof(  ConfMem_confCtrl  )  );
			 }

			 iErr  =  0;
errLabel:


			 return  iErr;
}



//
#ifdef  __DEBUG__
int  print_confState(  CONF_state  *  pConfState,  LPCTSTR  hint  )
{
	if  (  !hint  )  hint  =  _T(  ""  );
	int  i;
	TCHAR  tBuf[128];

	traceLog((TCHAR*)  _T(  "print_confState starts...  "  )  );
	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "tn_all %d, sn_part %d. %d mems, seqNo %d, ucbEnd %d"  ),  pConfState->uiTranNo_retrieveAll,  (  int  )pConfState->usSeqNo_retrievePart,  (  int  )pConfState->usCnt,  (  int  )pConfState->usSeqNo,  (  int  )pConfState->ucbEnd  );
	traceLog((TCHAR*)  tBuf  );
	//
	for  (  i  =  0;  i  <  pConfState->usCnt;  i  ++  )  {
		 CONF_mem_state  *  pMem  =  &pConfState->mems[i];
		 //
		 traceLog((TCHAR*)  _T(  "mem[%d]: %I64u %s"  ),  i,  pMem->idInfo.ui64Id,  qyGetDesByType1(  CONST_taskRespInfoMemStateTable,  pMem->usState  )  );

	}
	//
	traceLog((TCHAR*)  _T(  "print_confState ends"  )  );
	
	return  0;
}
#endif


//
int  send_confState_retrieveAll_req(  HWND  hDlgTalk_mgr,  DLG_TALK_var  *  pMgrVar,  LPCTSTR  hint  )
{
	if  (  !hint  )  hint  =  _T(  ""  );

	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return  -1;
	MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMgrVar->pMisCnt;
	if  (  !pMisCnt  )  return  -1;

	//
	CONF_state  cs  =  {0};

	cs.uiType  =  CONST_imCommType_confState;
	cs.idInfo_imGrp_related.ui64Id  =  pMgrVar->addr.idInfo.ui64Id;
	cs.sendByReceiver.ucbRetrieveAll  =  TRUE;

	//
	//
	MACRO_prepareForTran(  );
	unsigned  char  ucFlg  =  0;
	unsigned  int  channelType  =  CONST_channelType_media;
	//
	QY_MESSENGER_ID  idInfo_dst;
	idInfo_dst.ui64Id  =  pMgrVar->av.taskInfo.idInfo_starter.ui64Id;
	//
	postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_outputTask,  ucFlg,  CONST_qyCmd_sendTask,  tStartTran,  uiTranNo,  0,  (  char  *  )&cs,  sizeof(  cs  ),  0,  &idInfo_dst,  channelType  );    

	//
	TCHAR  tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "send_confState_retrieveAll_req to %I64u: %s"  ),  idInfo_dst.ui64Id,  hint  );
	showInfo_open0(  0,  0,  tBuf  );


	return  0;
}


//
int  dlgTalk_proc_recvd_confState(  HWND  hDlgTalk_mgr,  DLG_TALK_var  *  pMgrVar,  MIS_MSG_TASK  *  pMsgTask,  CONF_state  *  pConfState  )
{
	int  iErr  =  -1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return  -1;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	TCHAR  tBuf[128];
	//
	if  (  !pMgrVar->av.taskInfo.bTaskExists  )  return  -1;
	if  (  !pMgrVar->av.ucbGot_iIndex_sharedObj_localAv  )  return  -1;
	
	//							  
	#ifdef  __DEBUG__
			//			
			print_confState(  pConfState,  _T(  "recvd: confState"  )  );	
	#endif
	//
	if  (  pMgrVar->av.taskInfo.ucbStarter  )  {
		//
		if  (  !pConfState->sendByReceiver.ucbRetrieveAll  )  goto  errLabel;
		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "recv confState: from %I64u, retrieveAll"  ),  pMsgTask->data.route.idInfo_from.ui64Id  );
		showInfo_open0(  0,  0,  tBuf  );
		//
		pMgrVar->av.taskInfo.confState.ucbNeed_sendAll  =  TRUE;
		//
		iErr  =  0;  goto  errLabel;
	}
	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "recv confState: tn_all %d, sn_part %d. %d mems, sn %d, end %d"  ),  pConfState->uiTranNo_retrieveAll,  (  int  )pConfState->usSeqNo_retrievePart,  (  int  )pConfState->usCnt,  (  int  )pConfState->usSeqNo,  (  int  )pConfState->ucbEnd  );
	showInfo_open0(  0,  0,  tBuf  );
	//
	if  (  pConfState->usSeqNo_retrievePart  )  {
		if  (  pMgrVar->av.taskInfo.confState.uiTranNo_retrieveAll  !=  pConfState->uiTranNo_retrieveAll  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Err: talk.tn_all %d != tn_all %d. send retrieveAll req"  ),  pMgrVar->av.taskInfo.confState.uiTranNo_retrieveAll,  pConfState->uiTranNo_retrieveAll  );
			send_confState_retrieveAll_req(  hDlgTalk_mgr,  pMgrVar,  tBuf  );
			goto  errLabel;
		}
		if  (  pMgrVar->av.taskInfo.confState.usSeqNo_retrievePart  +  1  !=  pConfState->usSeqNo_retrievePart  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Err: talk.sn_part  + 1 != sn_part. send retrieveAll req"  )  );
			send_confState_retrieveAll_req(  hDlgTalk_mgr,  pMgrVar,  tBuf  );
			goto  errLabel;
		}
	}
	if  (  pConfState->ucbEnd  )  {
		if  (  !pConfState->usSeqNo_retrievePart  )  pMgrVar->av.taskInfo.confState.uiTranNo_retrieveAll  =  pConfState->uiTranNo_retrieveAll;
		pMgrVar->av.taskInfo.confState.usSeqNo_retrievePart  =  pConfState->usSeqNo_retrievePart;
	}
	
	//
	TASK_respInfo  *  pRespInfo  =  get_respInfo(  pProcInfo,  pMgrVar->av.taskInfo.iIndex_taskInfo  );  
	if  (  !pRespInfo  )  return  -1;
	//
	int  tmp_usCnt  =  min(  pRespInfo->usCnt,  MAX_taskRespInfoMems  );
	//
	BOOL  bNeedRefresh  =  FALSE;
	//
	int  i;
	for  (  i  =  0;  i  <  pConfState->usCnt;  i  ++  )  {
		 CONF_mem_state  *  pMem  =  &pConfState->mems[i];
		 //
		 if  (  !pMem->idInfo.ui64Id  )  continue;
		 //
		 TASK_respInfo_mem  *  pRespInfoMem  =  (  TASK_respInfo_mem  *  )bsearch(  &pMem->idInfo,  pRespInfo->mems,  tmp_usCnt,  sizeof(  pRespInfo->mems[0]  ),  bCmp_respInfoMem  ); 
		 if  (  !pRespInfoMem  )  {
			 showInfo_open0(  0,  0,  _T(  "dlgTalk_proc_recvd_constate err: bsearch returns null"  )  );
			 continue;
		 }
		 if  (  pRespInfoMem->var.usState_byDlgTalk  ==  pMem->usState  )  continue;
		 //
		 pRespInfoMem->var.usState_byDlgTalk  =  pMem->usState;
		 //
		 bNeedRefresh  =  TRUE;
	}

	//
	if  (  bNeedRefresh  )  {
		for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
			TALKER_shadow_mgrMem  *  pShadow  =  &pShadowMgr->shadows[i];
			if  (  !IsWindow(  pShadow->hShadow  )  )  continue;
			//
			refreshGrpMemListStatus(  pShadow->hShadow  );
		}
	}


	//
	iErr  =  0;
errLabel:
	return  iErr;

}


//
int  dlgTalk_proc_recvd_confCtrlState(HWND  hDlgTalk_mgr, DLG_TALK_var* pMgrVar, MIS_MSG_TASK* pMsgTask, CONF_ctrl_state* pConfCtrlState)
{
	int  iErr = -1;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();

	if (!isTalkerShadowMgr(pMgrVar->addr))  return  -1;
	TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
	TCHAR  tBuf[128];
	//
	if (!pMgrVar->av.taskInfo.bTaskExists)  return  -1;

	//							  
#ifdef  __DEBUG__
		//			
	//print_confState(pConfCtrlState, _T("recvd: confState"));
#endif
	//
	if (pMgrVar->av.taskInfo.ucbStarter) {
		//
		goto  errLabel;

	}
	//
	_sntprintf(tBuf, mycountof(tBuf), _T("recv confCtrlState: compere %I64u"), pConfCtrlState->idInfo_compere.ui64Id);
	showInfo_open0(0, 0, tBuf);

	//
	pMgrVar->av.taskInfo.unused_idInfo_compere = pConfCtrlState->idInfo_compere;

	//
	pProcInfo->do_dlgTalk_proc_recvd_confCtrlState(hDlgTalk_mgr);

	//
	iErr = 0;
errLabel:
	return  iErr;

}






 //  2013/09/11
#if  0
   int  old_tmpHandler_showMsg_task(  void  *  hDlgTalkParam,  	DLG_TALK_var	&	m_var,  void  *  p1, void  *  pMsgParam  )
{
	int		iErr	=	-1;

	HWND				hDlg					=	(  HWND  )hDlgTalkParam;
	
	PARAM_PROC_ROW	*	pParam					=	(  PARAM_PROC_ROW  *  )p1;
	MIS_MSGU		*	pMsg					=	(  MIS_MSGU  *  )pMsgParam;
	
	QY_MC			*	pQyMc					=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo				=	QY_GET_procInfo_isCli(  );	//
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;
	
	int					i;
	TCHAR				tBuf[128]				=	_T(  ""  );

	//
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	HWND  hMgr  =  hDlg;
	DLG_TALK_var  *  pMgrVar  =  &m_var;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
		TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pMgrVar->pShadowInfo;
		if  (  !pTalkerShadow  )  return  -1;
		hMgr  =  pTalkerShadow->hMgr;
		pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
		if  (  !pMgrVar  )  return  -1;
	}
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;

	//
	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_task:

				{
					  MIS_MSG_routeTalkData		*	pTalkData							=	&pMsg->task.data;
					  IM_CONTENTU				*	pContent							=	(  IM_CONTENTU  *  )pTalkData->buf;	
					  QY_MESSENGER_ID				idInfo_talker;
					  //
					  char							timeBuf[CONST_qyTimeLen  +  1]		=	"";
					  TASK_DISPLAY					taskDisplay;
					  char							buf[255  +  1]						=	"";
					  int							nItem;
					  int							iStatus;
					  
					  //
					  if  (  pContent->uiType  ==  CONST_imCommType_taskInteractionReq  )  {
						  if  (  !m_var.av.taskInfo.bTaskExists  )  goto  errLabel;
						  QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  m_var.av.taskInfo.iIndex_taskInfo  );
						  if  (  !pTaskInfo  )  goto  errLabel;
						  if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;
						  QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

						  DLG_TALK_videoConference	*	pVc				=	&pTc->videoConference;
						  BOOL							bBroadcasted	=	FALSE;

						  #ifdef  __DEBUG__
								  traceLogA(  (char*)  "taskInteractionReq"  );
						  #endif

						  if  (  pContent->taskInteractionReq.usOp  ==  CONST_imOp_stopSpeaking  )  {
							  QY_MESSENGER_ID  idInfo_speaker;				idInfo_speaker.ui64Id  =  0;
							  QY_MESSENGER_ID  idInfo_mgr;					idInfo_mgr.ui64Id  =  0;
							  //
							  if  (  !pContent->taskInteractionReq.idInfo_speaker.ui64Id  )  idInfo_speaker.ui64Id  =  pMsg->task.data.route.idInfo_from.ui64Id;
							  else  {
								    idInfo_speaker.ui64Id  =  pContent->taskInteractionReq.idInfo_speaker.ui64Id;
									idInfo_mgr.ui64Id  =  pMsg->task.data.route.idInfo_from.ui64Id;
							  }

							  //
							  BOOL	bActive  =  isMemFromActive(  pVc,  &idInfo_speaker,  NULL  );
							  
							  confStarter_requestToSpeak(  hDlg,  &idInfo_speaker,  FALSE,  NULL  );
							  //
							  if  (  !idInfo_mgr.ui64Id  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u request to stop speaking"  ),  idInfo_speaker.ui64Id  );
							  else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u let %I64u stop speaking"  ),  idInfo_mgr.ui64Id,  idInfo_speaker.ui64Id  );
							  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
							  //
							  if  (  !pVc->bNeedRefresh_activeMems_from  &&  bActive  &&  !isMemFromActive(  pVc,  &idInfo_speaker,  NULL  )  )  {
								  traceLogA(  (char*)  "broadcast all mems info in group when %I64u stop speaking.",  idInfo_speaker.ui64Id  );
								
								  sendConfKey(  hDlg,  &m_var.addr.idInfo  );

								  bBroadcasted  =  TRUE;
							  }
							  }
						  else  if  (  pContent->taskInteractionReq.usOp  ==  CONST_imOp_requestToSpeak  )  {

							        qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%I64u request to speak"  ),  pMsg->task.data.route.idInfo_from.ui64Id  );
						     
									//  2015/02/17
									if  (  !m_var.av.taskInfo.bTaskExists
										||  !m_var.av.taskInfo.ucbStarter  )  
									{
										showInfo_open0(  0,  0,  _T(  "failed, not the conf starter"  )  );
										goto  errLabel;
									}
#if  10
									if  (  m_var.av.taskInfo.ucbVideoConference  )  {

										//  2015/02/17. 新的版本才在taskInteractionReq里包含tranInfo.
										if  (  pContent->taskInteractionReq.avStream.tranInfo.audio.uiTranNo_openAvDev  ||  pContent->taskInteractionReq.avStream.tranInfo.video.uiTranNo_openAvDev  )  {
											
											//  2015/07/30
											if  (  pContent->taskInteractionReq.idInfo_speaker.ui64Id  )  {
												showInfo_open0(  0,  0,  _T(  "err: mgr can't send tranInfo"  )  );
												goto  errLabel;
											}

											//
											BOOL  bErr_inFromList  =  FALSE;							
											TASK_AV_FROM  *  pFrom  =  NULL;
											QY_MESSENGER_ID  idInfo_from;
											idInfo_from.ui64Id  =  pMsg->task.data.route.idInfo_from.ui64Id;
											for  (  i  =  0;  i  <  pVc->usCntLimit_mems_from;  i  ++  )  {
												 pFrom  =  &pVc->pMems_from[i];
												 //
												 if  (  pFrom->idInfo.ui64Id  ==  idInfo_from.ui64Id  )  break;								
											}
											if  (  i  ==  pVc->usCntLimit_mems_from  )  {
												bErr_inFromList  =  TRUE;										
												//
												showInfo_open0(  0,  0,  _T(  "proc requestToSpeak: not in from list"  )  );										
												}
											else  if  (  memcmp(  &pFrom->audio.ta_recvd,  &pContent->taskInteractionReq.avStream.tranInfo.audio,  sizeof(  pFrom->audio.ta_recvd  )  )
												||  memcmp(  &pFrom->video.tv_recvd,  &pContent->taskInteractionReq.avStream.tranInfo.video,  sizeof(  pFrom->video.tv_recvd  )  )  )
											{											  
													  bErr_inFromList  =  TRUE;
													  //											  
													  showInfo_open0(  0,  0,  _T(  "proc requestToSpeak: tranInfo not matched"  )  );									
											}
											//
											if  (  bErr_inFromList  )  {										
												//										
												pVc->bNeedRefresh_fromList  =  TRUE;																				
												//
												if  (  refreshTaskAv_videoConferenceStarter(  hDlg,  &pMsg->task  )  <  0  )  {											
													showInfo_open0(  0,  0,  _T(  "proc request: refreshTaskAv_videoConferenceStarter failed"  )  );											
													goto  errLabel;										
												}									
											}
										}
									}
#endif

									//  2015/07/30													
									QY_MESSENGER_ID  idInfo_speaker;				idInfo_speaker.ui64Id  =  0;
									QY_MESSENGER_ID  idInfo_mgr;					idInfo_mgr.ui64Id  =  0;							  
									//
									if  (  !pContent->taskInteractionReq.idInfo_speaker.ui64Id  )  idInfo_speaker.ui64Id  =  pMsg->task.data.route.idInfo_from.ui64Id;							  
									else  {
										  idInfo_speaker.ui64Id  =  pContent->taskInteractionReq.idInfo_speaker.ui64Id;									
										  idInfo_mgr.ui64Id  =  pMsg->task.data.route.idInfo_from.ui64Id;							  
									}

									//  first, add to the requestingMems
									if  (  !isMemFromActive(  pVc,  &idInfo_speaker,  NULL  )  )  {
										//
										unsigned  char  ucbManual  =  pProcInfo->cfg.policy.ucbManullyPermitToSpeakOnVideoConference;
										//
										if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;
										TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
										if  (  !pShadowMgr  )  goto  errLabel;
										//
										BOOL  bVal  =  FALSE;
										if  (  !getVal_bMsgrConfMgr(  &pMsg->task.data.route.idInfo_from,  &pShadowMgr->av.confMgrInfo,  &bVal  )
											&&  bVal  )
										{
											ucbManual  =  FALSE;
										}
										//
										if  (  ucbManual  )  {
											if  (  !isMemFromRequesting(  pVc,  &pMsg->task.data.route.idInfo_from  )  )  {
												if  (  !addTo_requestingMems_from(  m_var.pMisCnt,  pVc,  &pMsg->task.data.route.idInfo_from  )  )  {
													//  trigger the instantAssistant to refresh
													#if  0
													SendMessage(  m_var.hWnd_instantAssistant,  CONST_qyWm_comm,  0,  0  );
													//  2017/06/25
													SendMessage(  m_var.confMgr.hWnd_confMgr,  CONST_qyWm_comm,  0,  0  );													
													#endif
													//
													refreshTalkerList(  hDlg  );
												}
											}
											//  2015/02/16
											tBuf[0]  =  0;
											//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s : "  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_systemMessage  )  );
											_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u %s. %s"  ),  tBuf,  pMsg->task.data.route.idInfo_from.ui64Id,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_requestToSpeak  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_waitingForPermitted  )  );
											showNotification_open(  0,  0,  0,  tBuf  );
											sendNotification(  tBuf,  &m_var.addr.idInfo,  &pMsg->task.data.route.idInfo_from  );
											showNotification_d3d(  hDlg,  tBuf  );
											//
											}
										else  {
											  confStarter_requestToSpeak(  hDlg,  &idInfo_speaker,  TRUE,  &pContent->taskInteractionReq.avStream  );
										}
										if  (  isMemFromActive(  pVc,  &idInfo_speaker,  NULL  )
											||  isMemFromRequesting(  pVc,  &idInfo_speaker  )		//  2015/07/30. 因为需要发给管理员来启停发言，所以，即使是手动允许，也要发送一遍
											)  
										{
											#ifdef  __DEBUG__
													traceLogA(  (char*)  "broadcast all mems info in group when %I64u is speaking.",  idInfo_speaker.ui64Id  );
											#endif
										
											//
											sendConfKey(  hDlg,  &m_var.addr.idInfo  );
										
											bBroadcasted  =  TRUE;
										}
									}								
								}
								//								
						  else  if  (  pContent->taskInteractionReq.usOp  ==  CONST_imOp_prohibitSpeaking  )  {
									int  i  =  0;
									//
									pMgrVar->av.taskInfo.confMem_confCtrl.ucbPermitToSpeak  =  0;
									//
									pMgrVar->av.taskInfo.confMem_confCtrl.idInfo_starter.ui64Id  =  pMgrVar->av.taskInfo.idInfo_starter.ui64Id;
									pMgrVar->av.taskInfo.confMem_confCtrl.tStartTime  =  pMgrVar->av.taskInfo.tStartTime_org;
									pMgrVar->av.taskInfo.confMem_confCtrl.uiTranNo  =  pMgrVar->av.taskInfo.uiTranNo_org;
									//
									store_ConfMem_confCtrl(  &pMgrVar->av.taskInfo.confMem_confCtrl,  &pMgrVar->addr.idInfo  );
									//
									dlgTalk_requestToSpeak(  hMgr,  FALSE  );
									//
									refreshTalkerList(  hMgr  );
									//
									showNotification(  0,  &pMsg->task.data.route.idInfo_from,  0,  0,  0,  0,  _T(  "主持人停止了你的发言"  )  );
									//
									break;
									}
						  else  if  (  pContent->taskInteractionReq.usOp  ==  CONST_imOp_permitToSpeak  )  {
									//
							        pMgrVar->av.taskInfo.confMem_confCtrl.ucbPermitToSpeak  =  TRUE;
									//
									//
									pMgrVar->av.taskInfo.confMem_confCtrl.idInfo_starter.ui64Id  =  pMgrVar->av.taskInfo.idInfo_starter.ui64Id;
									pMgrVar->av.taskInfo.confMem_confCtrl.tStartTime  =  pMgrVar->av.taskInfo.tStartTime_org;
									pMgrVar->av.taskInfo.confMem_confCtrl.uiTranNo  =  pMgrVar->av.taskInfo.uiTranNo_org;
									//
									store_ConfMem_confCtrl(  &pMgrVar->av.taskInfo.confMem_confCtrl,  &pMgrVar->addr.idInfo  );									
							        //
									if  (  pProcInfo->cfg.policy.avRules.ucbLetConfMgrSetMicOn  )  {

										//  2017/07/13
										setCurSharedObjUsr_localAv(  pProcInfo,  pMgrVar->av.iIndex_sharedObj_localAv,  hMgr  );

										dlgTalk_requestToSpeak(  hMgr,  TRUE  );
									}
									//
									refreshTalkerList(  hMgr  );
									//
									showNotification(  0,  &pMsg->task.data.route.idInfo_from,  0,  0,  0,  0,  _T(  "主持人请你发言"  )  );
									//
									break;
									}
									//
						  else  if  (  pContent->taskInteractionReq.usOp  ==  CONST_imOp_requestToControlDesktop_yz  )  {
							        if  (  pQyMc->iCustomId  !=  CONST_qyCustomId_bjyz  )  goto  errLabel;
									//
									BOOL  bRemoteAssist  =  TRUE;	
									//	
									dlgTalk_OnCmd_shareScreen(  hMgr,  bRemoteAssist  );
									//
									showNotification(  0,  &pMsg->task.data.route.idInfo_from,  0,  0,  0,  0,  _T(  "请你共享屏幕"  )  );
									//
									break;
								    }
						  else  if  (  pContent->taskInteractionReq.usOp  ==  CONST_imOp_stopControlDesktop_yz  )  {
							        if  (  pQyMc->iCustomId  !=  CONST_qyCustomId_bjyz  )  goto  errLabel;
									//
									BOOL  bRemoteAssist  =  TRUE;	
									//	
									dlgTalk_OnCmd_shareScreen(  hMgr,  bRemoteAssist  );
									//
									showNotification(  0,  &pMsg->task.data.route.idInfo_from,  0,  0,  0,  0,  _T(  "请你取消共享"  )  );
									//
									break;
								    }
						  else  {
								#ifdef  __DEBUG__
										traceLogA(  (char*)  "%I64u request to refresh activeMems info",  pMsg->task.data.route.idInfo_from.ui64Id  );
								#endif
						  }

						  //
						  if  (  !pVc->bNeedRefresh_activeMems_from  &&  !bBroadcasted  )  {
							  sendConfKey(  hDlg,  &pMsg->task.data.route.idInfo_from  );
							  //
							  #ifdef  __DEBUG__
									  traceLogA(  (char*)  "send back all mems info to the requester"  );
							  #endif
							  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Send back all mems info to %I64u"  ),  pMsg->task.data.route.idInfo_from.ui64Id  );
						  }

						  //  2013/07/18
						  dyn_d3dWall_refreshImgs(  hDlg  );

						  //
						  break;
					  }
					  if  (  pContent->uiType  ==  CONST_imCommType_confKey  )  {
						  int							i,  j;
						  BOOL							bNeedRefresh_activeMems_from	=	FALSE;	//  2010/09/12

						  #ifdef  __DEBUG__
								  traceLogA(  (char*)  "videoConferenceStatus"  );
						  #endif
						
						  //
						  if  (  !m_var.av.taskInfo.bTaskExists  )  goto  errLabel;						  
						  if  (  m_var.av.taskInfo.ucbStarter  )  {
							  #ifdef  __DEBUG__
									  traceLogA(  (char*)  "Can't send status to starter."  );  
							  #endif
							  goto  errLabel;
						  }
						  QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  m_var.av.taskInfo.iIndex_taskInfo  );
						  if  (  !pTaskInfo  )  goto  errLabel;
						  if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;
						  QMC_taskData_conf  *  pTc =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;
						  DLG_TALK_videoConference  *  pVc  =  &pTc->videoConference;

#if  0
						  for  (  i  =  0;  i  <  pContent->videoConferenceStatus.usCnt;  i  ++  )  {
							   if  (  !pContent->videoConferenceStatus.mems[i].mem.idInfo.ui64Id  )  break;
							   if  (  !pContent->videoConferenceStatus.mems[i].ucbActive  )  break;
							   if  (  i  >=  mycountof(  pVc->activeMems_from  )  )  break;
							   if  (  pVc->activeMems_from[i].mem.idInfo.ui64Id  !=  pContent->videoConferenceStatus.mems[i].mem.idInfo.ui64Id  
								   ||  pVc->activeMems_from[i].tranInfo.audio.uiTranNo_openAvDev  !=  pContent->videoConferenceStatus.mems[i].tranInfo.audio.uiTranNo_openAvDev
								   ||  pVc->activeMems_from[i].tranInfo.video.uiTranNo_openAvDev  !=  pContent->videoConferenceStatus.mems[i].tranInfo.video.uiTranNo_openAvDev
								   )  
							   {
								   //  pVc->activeMems_from[i].mem.idInfo.ui64Id  =  pContent->videoConferenceStatus.mems[i].mem.idInfo.ui64Id;
								   memcpy(  &pVc->activeMems_from[i].mem,  &pContent->videoConferenceStatus.mems[i].mem,  sizeof(  pVc->activeMems_from[i].mem  )  );
								   memcpy(  &pVc->activeMems_from[i].tranInfo,  &pContent->videoConferenceStatus.mems[i].tranInfo,  sizeof(  pVc->activeMems_from[i].tranInfo  )  );	//  2009/05/31
								   //  getTalkerDesc(  m_var.pMisCnt,  &pVc->activeMems_from[i].mem.idInfo,  pVc->activeMems_from[i].desc,  mycountof(  pVc->activeMems_from[i].desc  ),  0,  0  );
								   M_getActiveMemDesc(  m_var.pMisCnt,  &pVc->activeMems_from[i].mem.idInfo,  pVc->activeMems_from[i].desc,  mycountof(  pVc->activeMems_from[i].desc  )  );
								   //
								   bNeedRefresh_activeMems_from  =  TRUE;			//  2010/09/12

								   //
								   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Conference status changed, %I64u modified."  ),  pVc->activeMems_from[i].mem.idInfo.ui64Id  );																						
							   }
						  }
						  j  =  i;
						  for  (  ;  i  <  mycountof(  pVc->activeMems_from  );  i  ++  )  {
							   if  (  pVc->activeMems_from[i].mem.idInfo.ui64Id  )  {
								   pVc->activeMems_from[i].mem.idInfo.ui64Id  =  0;
								   //
								   bNeedRefresh_activeMems_from  =  TRUE;			//  2010/09/12
							   }
						  }
						  i  =  j;
#endif
						  
						  
#if  10	//  2013/07/18
						  int  a  =  0;
						  for  (  i  =  0;  i  <  pContent->videoConferenceStatus.usCnt;  i  ++  )  {
							   if  (  !pContent->videoConferenceStatus.mems[i].idInfo.ui64Id  )  break;
							   if  (  !pContent->videoConferenceStatus.mems[i].ucbActive  )  break;
							   if  (  i  >=  mycountof(  pVc->activeMems_from  )  )  break;
							   //
							   if  (  pContent->videoConferenceStatus.mems[i].usIndex_speaker  >=  mycountof(  pVc->activeMems_from  )  )  {
								   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Conference status err, usIndex_activeMems_from too big."  )  );																						
								   goto  errLabel;
							   }

							   //
							   for  (  ;  a  <  pContent->videoConferenceStatus.mems[i].usIndex_speaker;  a  ++  )  {
								    if  (  pVc->activeMems_from[a].idInfo.ui64Id  )  {
										pVc->activeMems_from[a].idInfo.ui64Id  =  0;
									}
									//
									bNeedRefresh_activeMems_from  =  TRUE;
							   }
							   //
							   DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pVc->activeMems_from[a];
							   if  (  pActiveMem_from->idInfo.ui64Id  !=  pContent->videoConferenceStatus.mems[i].idInfo.ui64Id  
								   ||  pActiveMem_from->tranInfo.audio.uiTranNo_openAvDev  !=  pContent->videoConferenceStatus.mems[i].tranInfo.audio.uiTranNo_openAvDev
								   ||  pActiveMem_from->tranInfo.video.uiTranNo_openAvDev  !=  pContent->videoConferenceStatus.mems[i].tranInfo.video.uiTranNo_openAvDev
								   )  
							   {
								   //  pVc->activeMems_from[i].mem.idInfo.ui64Id  =  pContent->videoConferenceStatus.mems[i].mem.idInfo.ui64Id;
								   memcpy(  &pActiveMem_from->idInfo,  &pContent->videoConferenceStatus.mems[i].idInfo,  sizeof(  pActiveMem_from->idInfo  )  );
								   memcpy(  &pActiveMem_from->tranInfo,  &pContent->videoConferenceStatus.mems[i].tranInfo,  sizeof(  pActiveMem_from->tranInfo  )  );	//  2009/05/31
								   //  getTalkerDesc(  m_var.pMisCnt,  &pVc->activeMems_from[i].mem.idInfo,  pVc->activeMems_from[i].desc,  mycountof(  pVc->activeMems_from[i].desc  ),  0,  0  );
								   M_getActiveMemDesc(  m_var.pMisCnt,  &pActiveMem_from->idInfo,  pActiveMem_from->desc,  mycountof(  pActiveMem_from->desc  )  );
								   //
								   bNeedRefresh_activeMems_from  =  TRUE;			//  2010/09/12

								   //
								   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Conference status changed, %I64u modified."  ),  pActiveMem_from->idInfo.ui64Id  );																						
							   }
							   a  ++  ;
						  }
						  //  j  =  i;
						  for  (  ;  a  <  mycountof(  pVc->activeMems_from  );  a  ++  )  {
							   DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pVc->activeMems_from[a];
							   if  (  pActiveMem_from->idInfo.ui64Id  )  {
								   pActiveMem_from->idInfo.ui64Id  =  0;
								   //
								   bNeedRefresh_activeMems_from  =  TRUE;			//  2010/09/12
							   }
						  }
						  //  i  =  j;
#endif

						  //
						  for  (  ;  i  <  pContent->videoConferenceStatus.usCnt;  i  ++  )  {		//  skipped if active mem too many.
							  if  (  !pContent->videoConferenceStatus.mems[i].ucbActive  )  break;					  
						  }
						  for  (  j  =  0;  i  +  j  <  pContent->videoConferenceStatus.usCnt;  j  ++  )  {
							   if  (  !pContent->videoConferenceStatus.mems[i  +  j].idInfo.ui64Id  )  break;
							   if  (  j  >=  mycountof(  pVc->requestingMems_from  )  )  break;
							   if  (  pVc->requestingMems_from[j].idInfo.ui64Id  !=  pContent->videoConferenceStatus.mems[i  +  j].idInfo.ui64Id  )  {							   
								   pVc->requestingMems_from[j].idInfo.ui64Id  =  pContent->videoConferenceStatus.mems[i  +  j].idInfo.ui64Id;	
								   //  getTalkerDesc(  m_var.pMisCnt,  &pVc->requestingMems_from[j].idInfo,  pVc->requestingMems_from[j].desc,  mycountof(  pVc->requestingMems_from[j].desc  ),  0,  0  );
								   M_getActiveMemDesc(  m_var.pMisCnt,  &pVc->requestingMems_from[j].idInfo,  pVc->requestingMems_from[j].desc,  mycountof(  pVc->requestingMems_from[j].desc  )  );
							   }
						  }
						  for  (  ;  j  <  mycountof(  pVc->requestingMems_from  );  j  ++  )  {
							   if  (  pVc->requestingMems_from[j].idInfo.ui64Id  )  pVc->requestingMems_from[j].idInfo.ui64Id  =  0;
						  }

						  #ifdef  __DEBUG__
								  printDlgTalkVideoConference(  pVc  );
						  #endif

						  //  2009/05/31
						  refreshTaskAv_videoConferenceOthers(  hDlg  );

						  //
						  QY_SHARED_OBJ	*	pSharedObj;
						  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv  );
						  if  (  pSharedObj  )  {
							  SHARED_OBJ_USR	*	pSharedObjUsr	=	getSharedObjUsr(  pSharedObj,  m_var.av.iIndex_usr_localAv  );
							  if  (  pSharedObjUsr  &&  pSharedObjUsr->iTaskId  ==  m_var.av.taskInfo.iTaskId  )  {
								  if  (  isMemFromActive(  pVc,  &m_var.pMisCnt->idInfo,  NULL  )  )  {
									  if  (  pSharedObjUsr->ucbNotSendData  )  {
										  //  2010/12/29, 为了加强客户端的安全性，要求视频只能在用户点击时，才能进入发言态。从主持人的列表里下来的信息不能打开发言开关。
										  if  (  m_var.av.taskInfo.bEnableToSpeak  )  {
												pSharedObjUsr->ucbNotSendData  =  FALSE;
												qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Conference status refreshed. Start to speak."  )  );
												}
										  else  {
										  		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Conference status refreshed. This messenger is already in active list but in fact do not speak."  )  );																						
										  }
									  }
									 }
								  else  {
									    if  (  !pSharedObjUsr->ucbNotSendData  )  {
											pSharedObjUsr->ucbNotSendData  =  TRUE;
											qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Conference status refreshed. Speaking stopped."  )  );
										}
								  }
							  }
						  }

						  if  (  bNeedRefresh_activeMems_from  )  {
							#if  0
							  freeCapImageBySth(  hDlg,  0,  m_var.av.taskInfo.iTaskId,  NULL,  &m_var.av.peerImages  );	//  2010/09/12
							  if  (  m_var.av.taskInfo.bTaskExists  &&  m_var.av.taskInfo.hWnd_remoteAv  )  {
								  QY_WMBUF_COMM		wmBuf;
								  memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
								  wmBuf.uiType  =  CONST_qyWmParam_freeCapImage;
								  wmBuf.u.freeCapImage.iTaskId  =  m_var.av.taskInfo.iTaskId;
								  SendMessage(  m_var.av.taskInfo.hWnd_remoteAv,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
							  }
							#endif
							  dlgTalk_freeCapImageBySth_mgr(  hDlg,  m_var.av.taskInfo.iTaskId,  NULL  );		//  2010/09/12
						  }

						  //
						  #if 0
							  SendMessage(  m_var.hWnd_instantAssistant,  CONST_qyWm_comm,  0,  0  );
						  #endif
						  //  2017/07/05
						  refreshTalkerList(  hDlg  );


						  //  2010/12/29
						  m_var.av.taskInfo.usLayoutType_starter  =  pContent->videoConferenceStatus.usLayoutType_starter;
						  
						  if  (  !dlgTalk_get_usLayoutType_local(  hDlg  )  )  {
							  #if  0
							  BOOL	bModified  =  FALSE;
						  	  dlgTalk_refresh_usLayoutType_cur(  hDlg,  &bModified  );						  
							  //  if  (  bModified  )  
							  {
								  dlgTalk_setLayout(  hDlg,  m_var.av.usLayoutType_cur  );
								  sizeAllControls_dlgTalk(  hDlg,  m_var  );			//  2011/10/05
							  }
							  #endif
							  askToRefreshLayout_mgr(  hDlg  );
						  }

						  break;
					  }
					  if  (  pContent->uiType  ==  CONST_imCommType_confLayout  )  {				//  2010/12/27

						  #ifdef  __DEBUG__
								  traceLogA(  (char*)  "videoConferenceLayout"  );
						  #endif
						  //
						  if  (  !m_var.av.taskInfo.bTaskExists  )  goto  errLabel;
						  if  (  m_var.av.taskInfo.ucbStarter  )  {
							  #ifdef  __DEBUG__
									  traceLogA(  (char*)  "Can't send layout to starter."  );  
							  #endif
							  goto  errLabel;
						  }
						  m_var.av.taskInfo.usLayoutType_starter  =  pContent->videoConferenceLayout.usLayoutType;

						  if  (  !dlgTalk_get_usLayoutType_local(  hDlg  )  )  {
							  //  2012/05/20
							  askToRefreshLayout_mgr(  hDlg  );
						  }

						  break;
					  }
					  if  (  pContent->uiType  ==  CONST_imCommType_confState  )  {  //  2017/09/17
						  //
						  dlgTalk_proc_recvd_confState(  hDlg,  &m_var,  &pMsg->task,  &pContent->confState  );
						  //
						  break;
					  }

					  					
					  //
					  activateWnd(  hDlg,  m_var  );	//  ÕâÀïÒªÉÁÁÁ¶Ô»°¿ò¡£ÌáÐÑÓÃ»§µÄ×¢Òâ
					  //  m_var.ucbNewMsgArrives  =  TRUE;
					  dlgTalk_set_newMsgArrives(  hDlg,  &m_var,  TRUE  );

					  if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;

					  //
					  dlgTalk_displayAvStatus(  hDlg,  m_var,  0,  0,  0  );
					  //
					  TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
					  if  (  !pShadowMgr  )  goto  errLabel;
					  for  (  i  =   0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
						   if  (  pShadowMgr->shadows[i].hShadow  &&  isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  {
							   CHelp_getDlgTalkVar	help_getDlgTalkVar;
							   tmpHandler_showMsg_displayTask(  pShadowMgr->shadows[i].hShadow,  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  pShadowMgr->shadows[i].hShadow  ),  pParam,  pMsg  );
						   }
					  }
					  //
					  tmpHandler_showMsg_displayTask(  hDlg,  &m_var,  pParam,  pMsg  );

					  //
					  if  (  pParam->bNewMsg  )  {
						  postImMsg2Log_isClient(  pMsg,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsg->task.lenInBytes  );
					  }

					  MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMsg->task.pMisCnt;
					  if  (  !pMisCnt  )  goto  errLabel;

					  //  2010/09/06
					  if  (  pMsg->task.data.route.idInfo_from.ui64Id  !=  pMisCnt->idInfo.ui64Id  )  {
						  if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
							  QM_OBJQ_MEM				mem;
							  QMEM_MESSENGER_CLI	*	pQMemObj	=	NULL;
							  unsigned  int				uiRuleCmd	=	0;

							  if  (  findQMemByKey(  pProcInfo->pSgiParam,  (  QM_OBJQ  *  )m_var.pMisCnt->pObjQ,  &m_var.addr.idInfo,  &mem  )  )  {
								  #ifdef  __DEBUG__
										  traceLog((TCHAR*)  _T(  "dlgTalk_OnInitDialog failed, findQMemByKey failed."  )  );
								  #endif
								  goto  errLabel;
							  }
							  if  (  !mem.pQMemObj  )  goto  errLabel;
		
							  pQMemObj  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;

							  if  (  pContent->transferAvInfo.uiTaskType  ==  CONST_imTaskType_transferAvInfo  )  {
								  //
								  //  2016/02/12
								  set_recentAvRecvd_gZone(  pProcInfo,  hDlg  );
								  //
								  BOOL  bPermitted  =  FALSE;

								  if  (  bAutoAccepted_avCall(  hDlg,  &pQMemObj->rules,  pContent->transferAvInfo.uiTaskType  )  )  {
									  bPermitted  =  TRUE;
								  }
								  //
								  if  (  bPermitted  )
								  {								
									#if  0
									  if  (  !m_var.av.taskInfo.bTaskExists  )  {						
										  //
										  if  (  m_var.av.autoAnswer_av.task.bTaskNeedAutoAnswered  )  goto  errLabel;
										  //  
										  if  (  isRuleCmdPermit(  pQMemObj->rules.uiCmd_autoAnswer_av  )  )  uiRuleCmd  =  pQMemObj->rules.uiCmd_autoAnswer_av;
										  else  uiRuleCmd  =  pQMemObj->customerService.rules.uiCmd_autoAnswer_av;
										  m_var.av.autoAnswer_av.uiCmd_autoAnswer  =  uiRuleCmd;
										  //
										  m_var.av.autoAnswer_av.task.iTaskId  =  pMsg->task.iTaskId;
										  m_var.av.autoAnswer_av.task.iTaskStatus  =  pMsg->task.iStatus;
										  m_var.av.autoAnswer_av.task.bTaskNeedAutoAnswered  =  TRUE;
									  }
									#endif
									  //  2014/12/09
									  m_var.autoAnswer.bTaskExists  =  TRUE;
								  }
								  //
								  //  2016/05/09
								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "tmpHandler_showMsg: task transferAvInfo, from %I64u. bPermitted %d"  ),  pMsg->task.data.route.idInfo_from.ui64Id,  bPermitted  );
								  showInfo_open0(  0,  0,  tBuf  );
								  //
								  }
							  else  if  (  pContent->transferAvInfo.uiTaskType  ==  CONST_imTaskType_shareScreen  )  {		//  2010/12/20
										BOOL  bPermitted  =  FALSE;
										
										if  (  bAutoAccepted_avCall(  hDlg,  &pQMemObj->rules,  pContent->transferAvInfo.uiTaskType  )  )  {
											bPermitted  =  TRUE;								  
										}
										//
										if  (  bPermitted  )
										{
											#if  0
											//
											if  (  isRuleCmdPermit(  pQMemObj->rules.uiCmd_autoAnswer_screen  )  )  uiRuleCmd  =  pQMemObj->rules.uiCmd_autoAnswer_screen;
											else  uiRuleCmd  =  pQMemObj->customerService.rules.uiCmd_autoAnswer_screen;
											m_var.av.autoAnswer_screen.uiCmd_autoAnswer  =  uiRuleCmd;
											//
											m_var.av.autoAnswer_screen.task.iTaskId  =  pMsg->task.iTaskId;
											m_var.av.autoAnswer_screen.task.iTaskStatus  =  pMsg->task.iStatus;
											m_var.av.autoAnswer_screen.task.bTaskNeedAutoAnswered  =  TRUE;
											#endif
											//  2014/12/09
											m_var.autoAnswer.bTaskExists  =  TRUE;
										}
										}
							  else  if  (  pContent->transferAvInfo.uiTaskType  ==  CONST_imTaskType_remoteAssist  )  {		//  2017/08/23
								  		BOOL  bPermitted  =  FALSE;
										
										if  (  bAutoAccepted_avCall(  hDlg,  &pQMemObj->rules,  pContent->transferAvInfo.uiTaskType  )  )  {
											bPermitted  =  TRUE;								  
										}
										//
										if  (  bPermitted  )
										{
											#if  0
											//
											if  (  isRuleCmdPermit(  pQMemObj->rules.uiCmd_autoAnswer_screen  )  )  uiRuleCmd  =  pQMemObj->rules.uiCmd_autoAnswer_screen;
											else  uiRuleCmd  =  pQMemObj->customerService.rules.uiCmd_autoAnswer_screen;
											m_var.av.autoAnswer_screen.uiCmd_autoAnswer  =  uiRuleCmd;
											//
											m_var.av.autoAnswer_screen.task.iTaskId  =  pMsg->task.iTaskId;
											m_var.av.autoAnswer_screen.task.iTaskStatus  =  pMsg->task.iStatus;
											m_var.av.autoAnswer_screen.task.bTaskNeedAutoAnswered  =  TRUE;
											#endif
											//  2014/12/09
											m_var.autoAnswer.bTaskExists  =  TRUE;
										}									
									    }
							  else  if  (  pContent->transferAvInfo.uiTaskType  ==  CONST_imTaskType_shareMediaFile  )  {	//  2010/12/20
										BOOL  bPermitted  =  FALSE;
																				
										if  (  bAutoAccepted_avCall(  hDlg,  &pQMemObj->rules,  pContent->transferAvInfo.uiTaskType  )  )  {
											bPermitted  =  TRUE;								  
										}
										//
										if  (  bPermitted  )
										{
											#if  0
											m_var.av.autoAnswer_mediaFile.uiCmd_autoAnswer  =  pQMemObj->rules.uiCmd_autoAnswer_mediaFile;
											m_var.av.autoAnswer_mediaFile.task.iTaskId  =  pMsg->task.iTaskId;
											m_var.av.autoAnswer_mediaFile.task.iTaskStatus  =  pMsg->task.iStatus;
											m_var.av.autoAnswer_mediaFile.task.bTaskNeedAutoAnswered  =  TRUE;
											#endif
											//  2014/12/09
											m_var.autoAnswer.bTaskExists  =  TRUE;
										}
							  }
							  //
							  }
						  else  if  (  pContent->uiType  ==  CONST_imCommType_queryCustomerServiceOfficerReq  )  {		//  2011/04/08
									#if  0
										 if  (  m_var.addr.uiObjType  ==  CONST_objType_messenger  )  {						//  暂时只有messenger才可以
											 m_var.av.autoAnswer_customerService.uiCmd_autoAnswer  =  CONST_ruleCmd_permit;	//  这里暂时采用不需要设置就可以自动响应的办法，因为在服务器上实际上设置的客服可以认为是已经授权了。
											 m_var.av.autoAnswer_customerService.task.iTaskId  =  pMsg->task.iTaskId;
											 m_var.av.autoAnswer_customerService.task.iTaskStatus  =  pMsg->task.iStatus;
											 m_var.av.autoAnswer_customerService.task.bTaskNeedAutoAnswered  =  TRUE;
										 }
									#endif
										 //  2014/12/09											
										 m_var.autoAnswer.bTaskExists  =  TRUE;
									}
						  else  if  (  pContent->uiType  ==  CONST_imCommType_transferFileReq  )  {  //  2015/08/05
									if  (  bSupported_fileServer(  pQyMc  )  )  {
										m_var.autoAnswer.bTaskExists  =  TRUE;
										}
									else  {
										  if  (  pContent->transferFileReq.usSubtype  ==  CONST_procOfflineResSubtype_download  )  {
											  m_var.autoAnswer.bTaskExists  =  TRUE;
										  }
									}
									//
								    }
						  else  {
								#ifdef  __DEBUG__
										//  其他的contentType不需要自动处理. 2011/04/08
								#endif
						  }

					  }

				  }
				  break;
				  
			default:
					break;
		}
		
		iErr  =  0;

errLabel:


	//  2013/09/09	
	dyn_d3dWall_refreshWallMemByTalker(  hDlg  );

	return  iErr;

}
#endif


//
#if  0
int  iiold_tmpHandler_showMsg_task_taskInteractionReq(  void  *  hDlgTalkParam,  	DLG_TALK_var	&	m_var,  void  *  p1, void  *  pMsgParam,
												   IM_CONTENTU  *  pContent  )

{
	int  iErr  =  -1;
	
	CCtxQyMc  *  pQyMc  =  g_pQyMc;
	CCtxQmc  *  pProcInfo  =  (  CCtxQmc  *  )pQyMc->get_pProcInfo();
		
	HWND				hDlg					=	(  HWND  )hDlgTalkParam;

	MIS_MSGU		*	pMsg					=	(  MIS_MSGU  *  )pMsgParam;

		//
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	HWND  hMgr  =  hDlg;
	DLG_TALK_var  *  pMgrVar  =  &m_var;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
		TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pMgrVar->pShadowInfo;
		if  (  !pTalkerShadow  )  return  -1;
		hMgr  =  pTalkerShadow->hMgr;
		pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hMgr  );
		if  (  !pMgrVar  )  return  -1;
	}
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;

	TCHAR  tBuf[128];
	int  i;


	switch  (  pContent->uiType  )  {
			case  CONST_imCommType_taskInteractionReq:  {
	
						  if  (  !m_var.av.taskInfo.bTaskExists  )  goto  errLabel;
						  QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  m_var.av.taskInfo.iIndex_taskInfo  );
						  if  (  !pTaskInfo  )  goto  errLabel;
						  if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;
						  QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

						  DLG_TALK_videoConference	*	pVc				=	&pTc->videoConference;
						  BOOL							bBroadcasted	=	FALSE;

						  #ifdef  __DEBUG__
								  traceLogA(  (char*)  "taskInteractionReq"  );
						  #endif

						  if  (  pContent->taskInteractionReq.usOp  ==  CONST_imOp_stopSpeaking  )  {
							  QY_MESSENGER_ID  idInfo_speaker;				idInfo_speaker.ui64Id  =  0;
							  QY_MESSENGER_ID  idInfo_mgr;					idInfo_mgr.ui64Id  =  0;
							  //
							  if  (  !pContent->taskInteractionReq.avStream.idInfo.ui64Id  )  idInfo_speaker.ui64Id  =  pMsg->task.data.route.idInfo_from.ui64Id;
							  else  {
								    idInfo_speaker.ui64Id  =  pContent->taskInteractionReq.avStream.idInfo.ui64Id;
									idInfo_mgr.ui64Id  =  pMsg->task.data.route.idInfo_from.ui64Id;
							  }

							  //
							  BOOL	bActive  =  isMemFromActive(  pVc,  &idInfo_speaker,  null,  NULL  );
							  
							  confStarter_requestToSpeak(  hDlg,  &idInfo_speaker,  FALSE,  NULL  );
							  //
							  if  (  !idInfo_mgr.ui64Id  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u request to stop speaking"  ),  idInfo_speaker.ui64Id  );
							  else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u let %I64u stop speaking"  ),  idInfo_mgr.ui64Id,  idInfo_speaker.ui64Id  );
							  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
							  //
							  if  (  !pVc->bNeedRefresh_activeMems_from  &&  bActive  &&  !isMemFromActive(  pVc,  &idInfo_speaker,  null,  NULL  )  )  {

								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "broadcast all mems info in group when %I64u stop speaking."  ),  idInfo_speaker.ui64Id  );
								  #ifdef  __DEBUG__
										  traceLog((TCHAR*)  tBuf  );
								  #endif
								
								  sendConfKey(  hDlg,  &m_var.addr.idInfo,  tBuf  );

								  bBroadcasted  =  TRUE;
							  }
							  }
						  else  if  (  pContent->taskInteractionReq.usOp  ==  CONST_imOp_requestToSpeak  )  {

							        qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%I64u request to speak"  ),  pMsg->task.data.route.idInfo_from.ui64Id  );
						     
									//  2015/02/17
									if  (  !m_var.av.taskInfo.bTaskExists
										||  !m_var.av.taskInfo.ucbStarter  )  
									{
										showInfo_open0(  0,  0,  _T(  "failed, not the conf starter"  )  );
										goto  errLabel;
									}
#if  10
									if  (  m_var.av.taskInfo.ucbVideoConference  )  {

										//  2015/02/17. 新的版本才在taskInteractionReq里包含tranInfo.
										if  (  pContent->taskInteractionReq.avStream.obj.tranInfo.audio.uiTranNo_openAvDev  ||  pContent->taskInteractionReq.avStream.obj.tranInfo.video.uiTranNo_openAvDev  )  {
											
											//  2015/07/30
											if  (  pContent->taskInteractionReq.avStream.idInfo.ui64Id  )  {
												showInfo_open0(  0,  0,  _T(  "err: mgr can't send tranInfo"  )  );
												goto  errLabel;
											}

											//
											BOOL  bErr_inFromList  =  FALSE;							
											TASK_AV_FROM  *  pFrom  =  NULL;
											QY_MESSENGER_ID  idInfo_from;
											idInfo_from.ui64Id  =  pMsg->task.data.route.idInfo_from.ui64Id;
											for  (  i  =  0;  i  <  pVc->usCntLimit_mems_from;  i  ++  )  {
												 pFrom  =  &pVc->pMems_from[i];
												 //
												 if  (  pFrom->idInfo.ui64Id  ==  idInfo_from.ui64Id  )  break;								
											}
											if  (  i  ==  pVc->usCntLimit_mems_from  )  {
												bErr_inFromList  =  TRUE;										
												//
												showInfo_open0(  0,  0,  _T(  "proc requestToSpeak: not in from list"  )  );										
												}
											else  if  (  memcmp(  &pFrom->audio.ta_recvd,  &pContent->taskInteractionReq.avStream.obj.tranInfo.audio,  sizeof(  pFrom->audio.ta_recvd  )  )
												||  memcmp(  &pFrom->video.tv_recvd,  &pContent->taskInteractionReq.avStream.obj.tranInfo.video,  sizeof(  pFrom->video.tv_recvd  )  )  )
											{											  
													  bErr_inFromList  =  TRUE;
													  //											  
													  showInfo_open0(  0,  0,  _T(  "proc requestToSpeak: tranInfo not matched"  )  );									
											}
											//
											if  (  bErr_inFromList  )  {										
												//										
												pVc->bNeedRefresh_fromList  =  TRUE;																				
												//
												if  (  refreshTaskAv_videoConferenceStarter(  hDlg,  &pMsg->task  )  <  0  )  {											
													showInfo_open0(  0,  0,  _T(  "proc request: refreshTaskAv_videoConferenceStarter failed"  )  );											
													goto  errLabel;										
												}									
											}
										}
									}
#endif

									//  2015/07/30													
									QY_MESSENGER_ID  idInfo_speaker;				idInfo_speaker.ui64Id  =  0;
									QY_MESSENGER_ID  idInfo_mgr;					idInfo_mgr.ui64Id  =  0;							  
									//
									if  (  !pContent->taskInteractionReq.avStream.idInfo.ui64Id  )  idInfo_speaker.ui64Id  =  pMsg->task.data.route.idInfo_from.ui64Id;							  
									else  {
										  idInfo_speaker.ui64Id  =  pContent->taskInteractionReq.avStream.idInfo.ui64Id;									
										  idInfo_mgr.ui64Id  =  pMsg->task.data.route.idInfo_from.ui64Id;							  
									}

									//  first, add to the requestingMems
									if  (  !isMemFromActive(  pVc,  &idInfo_speaker,  &pContent->taskInteractionReq.avStream.obj.resObj,  NULL  )  )  {
										//
										unsigned  char  ucbManual  =  pProcInfo->cfg.policy.ucbManullyPermitToSpeakOnVideoConference;
										//
										if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;
										TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
										if  (  !pShadowMgr  )  goto  errLabel;
										//
										BOOL  bVal  =  FALSE;
										if  (  !getVal_bMsgrConfMgr(  &pMsg->task.data.route.idInfo_from,  &pShadowMgr->av.confMgrInfo,  &bVal  )
											&&  bVal  )
										{
											ucbManual  =  FALSE;
										}
										//
										if  (  ucbManual  )  {
											if  (  !isMemFromRequesting(  pVc,  &pMsg->task.data.route.idInfo_from  )  )  {
												if  (  !addTo_requestingMems_from(  m_var.pMisCnt,  &pMsg->task.data.route.idInfo_from,  pVc    )  )  {
													//  trigger the instantAssistant to refresh
													#if  0
													SendMessage(  m_var.hWnd_instantAssistant,  CONST_qyWm_comm,  0,  0  );
													//  2017/06/25
													SendMessage(  m_var.confMgr.hWnd_confMgr,  CONST_qyWm_comm,  0,  0  );													
													#endif
													//
													refreshTalkerList(  hDlg  );
												}
											}
											//  2015/02/16
											tBuf[0]  =  0;
											//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s : "  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_systemMessage  )  );
											_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u %s. %s"  ),  tBuf,  pMsg->task.data.route.idInfo_from.ui64Id,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_requestToSpeak  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_waitingForPermitted  )  );
											showNotification_open(  0,  0,  0,  tBuf  );
											sendNotification(  tBuf,  &m_var.addr.idInfo,  &pMsg->task.data.route.idInfo_from  );
											showNotification_d3d(  hDlg,  tBuf  );
											//
											}
										else  {
											confStarter_requestToSpeak(  hDlg,  &idInfo_speaker,  &pContent->taskInteractionReq.avStream.obj,  TRUE  );
										}
										if  (  isMemFromActive(  pVc,  &idInfo_speaker,  null,  NULL  )
											||  isMemFromRequesting(  pVc,  &idInfo_speaker  )		//  2015/07/30. 因为需要发给管理员来启停发言，所以，即使是手动允许，也要发送一遍
											)  
										{
											//
											_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "broadcast all mems info in group when %I64u is speaking."  ),  idInfo_speaker.ui64Id  );
											//
											#ifdef  __DEBUG__
													traceLog((TCHAR*)  tBuf  );
											#endif
										
											//
											sendConfKey(  hDlg,  &m_var.addr.idInfo,  tBuf  );
										
											bBroadcasted  =  TRUE;
										}
									}								
								}
								//								
						  else  if  (  pContent->taskInteractionReq.usOp  ==  CONST_imOp_prohibitSpeaking  )  {
									int  i  =  0;
									//
									pMgrVar->av.taskInfo.confMem_confCtrl.ucbPermitToSpeak  =  0;
									//
									pMgrVar->av.taskInfo.confMem_confCtrl.idInfo_starter.ui64Id  =  pMgrVar->av.taskInfo.idInfo_starter.ui64Id;
									pMgrVar->av.taskInfo.confMem_confCtrl.tStartTime  =  pMgrVar->av.taskInfo.tStartTime_org;
									pMgrVar->av.taskInfo.confMem_confCtrl.uiTranNo  =  pMgrVar->av.taskInfo.uiTranNo_org;
									//
									store_ConfMem_confCtrl(  &pMgrVar->av.taskInfo.confMem_confCtrl,  &pMgrVar->addr.idInfo  );
									//
									dlgTalk_requestToSpeak(  hMgr,  FALSE  );
									//
									refreshTalkerList(  hMgr  );
									//
									showNotification(  0,  &pMsg->task.data.route.idInfo_from,  0,  0,  0,  0,  _T(  "主持人停止了你的发言"  )  );
									//
									break;
									}
						  else  if  (  pContent->taskInteractionReq.usOp  ==  CONST_imOp_permitToSpeak  )  {
									//
							        pMgrVar->av.taskInfo.confMem_confCtrl.ucbPermitToSpeak  =  TRUE;
									//
									//
									pMgrVar->av.taskInfo.confMem_confCtrl.idInfo_starter.ui64Id  =  pMgrVar->av.taskInfo.idInfo_starter.ui64Id;
									pMgrVar->av.taskInfo.confMem_confCtrl.tStartTime  =  pMgrVar->av.taskInfo.tStartTime_org;
									pMgrVar->av.taskInfo.confMem_confCtrl.uiTranNo  =  pMgrVar->av.taskInfo.uiTranNo_org;
									//
									store_ConfMem_confCtrl(  &pMgrVar->av.taskInfo.confMem_confCtrl,  &pMgrVar->addr.idInfo  );									
							        //
									if  (  pProcInfo->cfg.policy.avRules.ucbLetConfMgrSetMicOn  )  {

										//  2017/07/13
										setCurSharedObjUsr_localAv(  pProcInfo,  pMgrVar->av.iIndex_sharedObj_localAv,  hMgr  );

										dlgTalk_requestToSpeak(  hMgr,  TRUE  );
									}
									//
									refreshTalkerList(  hMgr  );
									//
									showNotification(  0,  &pMsg->task.data.route.idInfo_from,  0,  0,  0,  0,  _T(  "主持人请你发言"  )  );
									//
									break;
									}
									//
						  else  if  (  pContent->taskInteractionReq.usOp  ==  CONST_imOp_requestToControlDesktop_yz  )  {
							        if  (  pQyMc->iCustomId  !=  CONST_qyCustomId_bjyz  )  goto  errLabel;
									//
									BOOL  bRemoteAssist  =  TRUE;	
									//	
									dlgTalk_OnCmd_shareScreen(  hMgr,  bRemoteAssist  );
									//
									showNotification(  0,  &pMsg->task.data.route.idInfo_from,  0,  0,  0,  0,  _T(  "请你共享屏幕"  )  );
									//
									break;
								    }
						  else  if  (  pContent->taskInteractionReq.usOp  ==  CONST_imOp_stopControlDesktop_yz  )  {
							        if  (  pQyMc->iCustomId  !=  CONST_qyCustomId_bjyz  )  goto  errLabel;
									//
									BOOL  bRemoteAssist  =  TRUE;	
									//	
									dlgTalk_OnCmd_shareScreen(  hMgr,  bRemoteAssist  );
									//
									showNotification(  0,  &pMsg->task.data.route.idInfo_from,  0,  0,  0,  0,  _T(  "请你取消共享"  )  );
									//
									break;
								    }
						  else  {
								#ifdef  __DEBUG__
										traceLogA(  (char*)  "%I64u request to refresh activeMems info",  pMsg->task.data.route.idInfo_from.ui64Id  );
								#endif
						  }

						  //
						  if  (  !pVc->bNeedRefresh_activeMems_from  &&  !bBroadcasted  )  {
							  sendConfKey(  hDlg,  &pMsg->task.data.route.idInfo_from,  _T(  "send back all mems info to the requester"  )  );
							  //
							  #if  0
							  #ifdef  __DEBUG__
									  traceLogA(  (char*)  "send back all mems info to the requester"  );
							  #endif
							  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Send back all mems info to %I64u"  ),  pMsg->task.data.route.idInfo_from.ui64Id  );
							  #endif
						  }

						  //  2013/07/18
						  dyn_d3dWall_refreshImgs(  hDlg  );

						  //
						  break;
						  }
						  break;
						  
				default:
				
					break;
					
		  }
					  

		  iErr  =  0;

errLabel:

			
		  return  iErr;
}
#endif


//
int  tmpHandler_showMsg_task_taskInteractionReq(void* hDlgTalkParam, DLG_TALK_var& m_var, void* p1, void* pMsgParam,
	IM_CONTENTU* pContent)

{
	int  iErr = -1;

	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	//
	HWND				hDlg = (HWND)hDlgTalkParam;

	MIS_MSGU* pMsg = (MIS_MSGU*)pMsgParam;

	//
	CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	HWND  hMgr = hDlg;
	DLG_TALK_var* pMgrVar = &m_var;
	if (!isTalkerShadowMgr(pMgrVar->addr)) {
		TALKER_shadow* pTalkerShadow = (TALKER_shadow*)pMgrVar->pShadowInfo;
		if (!pTalkerShadow)  return  -1;
		hMgr = pTalkerShadow->hMgr;
		pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
		if (!pMgrVar)  return  -1;
	}
	TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
	if (!pShadowMgr)  return  -1;

	TCHAR  tBuf[128];
	int  i;


	switch (pContent->uiType) {
	case  CONST_imCommType_taskInteractionReq: {

		if (!m_var.av.taskInfo.bTaskExists)  goto  errLabel;
		QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, m_var.av.taskInfo.iIndex_taskInfo);
		if (!pTaskInfo)  goto  errLabel;
		if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  goto  errLabel;
		QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;

		DLG_TALK_videoConference* pVc = &pTc->videoConference;
		BOOL							bBroadcasted = FALSE;

#ifdef  __DEBUG__
		traceLogA((char*)"taskInteractionReq");
#endif

		if (pContent->taskInteractionReq.usOp == CONST_imOp_stopSpeaking) {
			QY_MESSENGER_ID  idInfo_speaker;				idInfo_speaker.ui64Id = 0;
			QY_MESSENGER_ID  idInfo_mgr;					idInfo_mgr.ui64Id = 0;
			//
			if (!pContent->taskInteractionReq.avStream.idInfo.ui64Id)  idInfo_speaker.ui64Id = pMsg->task.data.route.idInfo_from.ui64Id;
			else {
				idInfo_speaker.ui64Id = pContent->taskInteractionReq.avStream.idInfo.ui64Id;
				idInfo_mgr.ui64Id = pMsg->task.data.route.idInfo_from.ui64Id;
			}

			//
			if (m_var.av.taskInfo.ucbVideoConference
				&& m_var.av.taskInfo.ucbStarter)
			{
				if (m_var.av.taskInfo.idInfo_starter.ui64Id == idInfo_speaker.ui64Id) {
					showInfo_open0(0, 0, _T("taskInteractionReq err, can't stop starter speaking"));
					goto  errLabel;
				}
				if (idInfo_mgr.ui64Id != 0) {
					if (0) {
						QY_MESSENGER_ID idInfo_compere = unused_dlgTalk_get_idInfo_compere(hMgr);
						if (idInfo_mgr.ui64Id != idInfo_compere.ui64Id) {
							showInfo_open0(0, 0, _T("taskInteractionReq err, compere is not valid"));
							goto  errLabel;
						}
					}
					if (!dlgTalk_bConfCompere(hMgr, idInfo_mgr)) {
						showInfo_open0(0, 0, _T("taskInteractionReq err, compere is not valid"));
						goto  errLabel;
					}
				}
				//
				//
			}

			//
			BOOL	bActive = isMemFromActive(pVc, &idInfo_speaker, &pContent->taskInteractionReq.avStream.obj.resObj, NULL);
			if (bActive) {
				//
				pProcInfo->confStarter_requestToSpeak(hDlg, &idInfo_speaker, &pContent->taskInteractionReq.avStream.obj, pContent->taskInteractionReq.talkerDesc, FALSE);
				
				//
				BOOL  bModified = false;
				dlgTalk_refresh_usLayoutType_cur(hDlg, &bModified);
				if (bModified) {
					askToRefreshLayout_mgr(hDlg);
				}

			}
			//
			if (!idInfo_mgr.ui64Id)  _sntprintf(tBuf, mycountof(tBuf), _T("%I64u request to stop speaking"), idInfo_speaker.ui64Id);
			else  _sntprintf(tBuf, mycountof(tBuf), _T("%I64u let %I64u stop speaking"), idInfo_mgr.ui64Id, idInfo_speaker.ui64Id);
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%s"), tBuf);
			//
			if (bActive && !isMemFromActive(pVc, &idInfo_speaker, &pContent->taskInteractionReq.avStream.obj.resObj, NULL)) {

				_sntprintf(tBuf, mycountof(tBuf), _T("broadcast all mems info in group when %I64u stop speaking."), idInfo_speaker.ui64Id);
#ifdef  __DEBUG__
				traceLog((TCHAR*)tBuf);
#endif

				pProcInfo->sendConfKey(hDlg, m_var.addr.idInfo, tBuf);

				bBroadcasted = TRUE;
			}
		}
		else  if (pContent->taskInteractionReq.usOp == CONST_imOp_requestToSpeak) {

			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%I64u request to speak"), pMsg->task.data.route.idInfo_from.ui64Id);

			//  2015/02/17
			if (!m_var.av.taskInfo.bTaskExists
				|| !m_var.av.taskInfo.ucbStarter)
			{
				showInfo_open0(0, 0, _T("failed, not the conf starter"));
				goto  errLabel;
			}
#if  0
			if (m_var.av.taskInfo.ucbVideoConference) {

				//  2015/02/17. 新的版本才在taskInteractionReq里包含tranInfo.
				if (pContent->taskInteractionReq.avStream.obj.tranInfo.audio.uiTranNo_openAvDev || pContent->taskInteractionReq.avStream.obj.tranInfo.video.uiTranNo_openAvDev) {

					//  2015/07/30
					if (pContent->taskInteractionReq.avStream.idInfo.ui64Id) {
						showInfo_open0(0, 0, _T("err: mgr can't send tranInfo"));
						goto  errLabel;
					}

					//
					BOOL  bErr_inFromList = FALSE;
					TASK_AV_FROM* pFrom = NULL;
					QY_MESSENGER_ID  idInfo_from;
					idInfo_from.ui64Id = pMsg->task.data.route.idInfo_from.ui64Id;
					for (i = 0; i < pVc->usCntLimit_mems_from; i++) {
						pFrom = &pVc->pMems_from[i];
						//
						if (pFrom->idInfo.ui64Id == idInfo_from.ui64Id)  break;
					}
					if (i == pVc->usCntLimit_mems_from) {
						bErr_inFromList = TRUE;
						//
						showInfo_open0(0, 0, _T("proc requestToSpeak: not in from list"));
					}
					else  if (memcmp(&pFrom->audio.ta_recvd, &pContent->taskInteractionReq.avStream.obj.tranInfo.audio, sizeof(pFrom->audio.ta_recvd))
						|| memcmp(&pFrom->video.tv_recvd, &pContent->taskInteractionReq.avStream.obj.tranInfo.video, sizeof(pFrom->video.tv_recvd)))
					{
						bErr_inFromList = TRUE;
						//											  
						showInfo_open0(0, 0, _T("proc requestToSpeak: tranInfo not matched"));
					}
					//
					if (bErr_inFromList) {
						//										
						pVc->bNeedRefresh_fromList = TRUE;
						//
						if (refreshTaskAv_videoConferenceStarter(hDlg, &pMsg->task) < 0) {
							showInfo_open0(0, 0, _T("proc request: refreshTaskAv_videoConferenceStarter failed"));
							goto  errLabel;
						}
					}
				}
			}
#endif

			//  2015/07/30													
			QY_MESSENGER_ID  idInfo_speaker;				idInfo_speaker.ui64Id = 0;
			QY_MESSENGER_ID  idInfo_mgr;					idInfo_mgr.ui64Id = 0;
			//
			if (!pContent->taskInteractionReq.avStream.idInfo.ui64Id)  idInfo_speaker.ui64Id = pMsg->task.data.route.idInfo_from.ui64Id;
			else {
				idInfo_speaker.ui64Id = pContent->taskInteractionReq.avStream.idInfo.ui64Id;
				idInfo_mgr.ui64Id = pMsg->task.data.route.idInfo_from.ui64Id;
			}

			//  first, add to the requestingMems
			int  index_active = 0;
			if (!isMemFromActive(pVc, &idInfo_speaker, &pContent->taskInteractionReq.avStream.obj.resObj, &index_active)) {
				//
				unsigned  char  ucbManual = pProcInfo->cfg.policy.ucbManullyPermitToSpeakOnVideoConference;
				//
				if (!isTalkerShadowMgr(m_var.addr))  goto  errLabel;
				TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)m_var.pShadowInfo;
				if (!pShadowMgr)  goto  errLabel;
				//
				BOOL  bVal = FALSE;
				if (!getVal_bMsgrConfMgr(&pMsg->task.data.route.idInfo_from, &pShadowMgr->av.confMgrInfo, &bVal)
					&& bVal)
				{
					ucbManual = FALSE;
				}
				//
				if (ucbManual) {
					if (!isMemFromRequesting(pVc, &pMsg->task.data.route.idInfo_from)) {
						if (!addTo_requestingMems_from(m_var.pMisCnt, &pMsg->task.data.route.idInfo_from, pContent->taskInteractionReq.talkerDesc, pVc)) {
							//  trigger the instantAssistant to refresh
#if  0
							SendMessage(m_var.hWnd_instantAssistant, CONST_qyWm_comm, 0, 0);
							//  2017/06/25
							SendMessage(m_var.confMgr.hWnd_confMgr, CONST_qyWm_comm, 0, 0);
#endif
							//
							refreshTalkerList(hDlg);
						}
					}
					//  2015/02/16
					tBuf[0] = 0;
					//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s : "  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_systemMessage  )  );
					_sntprintf(tBuf, mycountof(tBuf), _T("%s %I64u %s. %s"), tBuf, pMsg->task.data.route.idInfo_from.ui64Id, getResStr(0, &pQyMc->cusRes, CONST_resId_requestToSpeak), getResStr(0, &pQyMc->cusRes, CONST_resId_waitingForPermitted));
					showNotification_open(0, 0, 0, tBuf);
					sendNotification(tBuf, &m_var.addr.idInfo, &pMsg->task.data.route.idInfo_from);
					showNotification_d3d(hDlg, tBuf);
					//
				}
				else {
					pProcInfo->confStarter_requestToSpeak(hDlg, &idInfo_speaker, &pContent->taskInteractionReq.avStream.obj, pContent->taskInteractionReq.talkerDesc, TRUE);
				}
				//
				if (isMemFromActive(pVc, &idInfo_speaker, mynull, &index_active)) {
					DLG_TALK_videoConferenceActiveMemFrom* pActive = &pTc->videoConference.activeMems_from[index_active];
					//
					pActive->iHkStatus = pContent->taskInteractionReq.iHkStatus;
					//
					pActive->ucbNvr = pContent->taskInteractionReq.ucbNvr;
					//
#if  1  //def  __DEBUG__
					_sntprintf(tBuf, mycountof(tBuf), _T("active[%d].iHkStatus %d. bNvr %d"), index_active, pActive->iHkStatus, (int)pActive->ucbNvr);
					showInfo_open0(0, 0, tBuf);
#endif
				}
				//
				if (pContent->taskInteractionReq.avStream.obj.resObj.uiObjType) {
					BOOL  bModified = false;
					dlgTalk_refresh_usLayoutType_cur(hDlg, &bModified);
					if (bModified) {
						askToRefreshLayout_mgr(hDlg);
					}
				}
				//
				if (isMemFromActive(pVc, &idInfo_speaker, &pContent->taskInteractionReq.avStream.obj.resObj, NULL)
					|| isMemFromRequesting(pVc, &idInfo_speaker)		//  2015/07/30. 因为需要发给管理员来启停发言，所以，即使是手动允许，也要发送一遍
					)
				{
					//
					_sntprintf(tBuf, mycountof(tBuf), _T("broadcast all mems info in group when %I64u is speaking."), idInfo_speaker.ui64Id);
					//
#ifdef  __DEBUG__
					traceLog((TCHAR*)tBuf);
#endif

					//
					pProcInfo->sendConfKey(hDlg, m_var.addr.idInfo, tBuf);

					bBroadcasted = TRUE;
				}
				//
			}
			else {
				DLG_TALK_videoConferenceActiveMemFrom* pActive = &pTc->videoConference.activeMems_from[index_active];
				if (pContent->taskInteractionReq.avStream.obj.tranInfo.audio.uiTranNo_openAvDev == 0
					&& pContent->taskInteractionReq.avStream.obj.tranInfo.video.uiTranNo_openAvDev == 0)
				{
					showInfo_open0(0, 0, _T("requestToSpeak failed, a_tn and v_tn are 0"));
					goto  errLabel;
				}
				if (pActive->avStream.obj.tranInfo.audio.uiTranNo_openAvDev != pContent->taskInteractionReq.avStream.obj.tranInfo.audio.uiTranNo_openAvDev
					|| pActive->avStream.obj.tranInfo.video.uiTranNo_openAvDev != pContent->taskInteractionReq.avStream.obj.tranInfo.video.uiTranNo_openAvDev)
				{
					//  update avStream
					pActive->avStream.obj.tranInfo = pContent->taskInteractionReq.avStream.obj.tranInfo;
					//
					pProcInfo->sendConfKey(hMgr, m_var.addr.idInfo, _T("talk_msgTask_taskInteraction, update activeMem"));

					//
					bBroadcasted = true;

					//iErr  =  0;  goto  errLabel;
				}
			}
		}
		//
		else if (pContent->taskInteractionReq.usOp == CONST_imOp_sendStreamInfo) {
			//
			QY_MESSENGER_ID  idInfo_speaker;				idInfo_speaker.ui64Id = 0;
			QY_MESSENGER_ID  idInfo_mgr;					idInfo_mgr.ui64Id = 0;
			//
			if (!pContent->taskInteractionReq.avStream.idInfo.ui64Id)  idInfo_speaker.ui64Id = pMsg->task.data.route.idInfo_from.ui64Id;
			else {
				idInfo_speaker.ui64Id = pContent->taskInteractionReq.avStream.idInfo.ui64Id;
				idInfo_mgr.ui64Id = pMsg->task.data.route.idInfo_from.ui64Id;
			}

			//  first, add to the requestingMems
			int  index_active = 0;
			if (isMemFromActive(pVc, &idInfo_speaker, &pContent->taskInteractionReq.avStream.obj.resObj, &index_active)) {
				DLG_TALK_videoConferenceActiveMemFrom* pActive = &pTc->videoConference.activeMems_from[index_active];
				if (pActive->iHkStatus != pContent->taskInteractionReq.iHkStatus) {
					pActive->iHkStatus = pContent->taskInteractionReq.iHkStatus;
					//
					refreshConfStreamInfos(m_var.av.taskInfo.iTaskId);
				}

			}
			//
			iErr = 0;  goto  errLabel;
		}
		//								
		else  if (pContent->taskInteractionReq.usOp == CONST_imOp_prohibitSpeaking) {
			int  i = 0;
			//
			if (m_var.av.taskInfo.ucbVideoConference) {
				if (0) {
					QY_MESSENGER_ID  idInfo_compere = unused_dlgTalk_get_idInfo_compere(hMgr);
					if (idInfo_compere.ui64Id != pMsg->task.data.route.idInfo_from.ui64Id) {
						showNotification(0, &pMsg->task.data.route.idInfo_from, 0, 0, 0, 0, _T("错误：收到一个非主持人的请求"));
						goto  errLabel;
					}
				}
				if (!dlgTalk_bConfCompere(hMgr, pMsg->task.data.route.idInfo_from)) {
					showNotification(0, &pMsg->task.data.route.idInfo_from, 0, 0, 0, 0, _T("错误：收到一个非主持人的请求"));
					goto  errLabel;

				}
			}
			//
			pMgrVar->av.taskInfo.confMem_confCtrl.ucbPermitToSpeak = 0;
			//
			pMgrVar->av.taskInfo.confMem_confCtrl.idInfo_starter.ui64Id = pMgrVar->av.taskInfo.idInfo_starter.ui64Id;
			pMgrVar->av.taskInfo.confMem_confCtrl.tStartTime = pMgrVar->av.taskInfo.tStartTime_org;
			pMgrVar->av.taskInfo.confMem_confCtrl.uiTranNo = pMgrVar->av.taskInfo.uiTranNo_org;
			//
			store_ConfMem_confCtrl(pQyMc,  &pMgrVar->av.taskInfo.confMem_confCtrl, &pMgrVar->addr.idInfo);
			//
			dlgTalk_requestToSpeak(hMgr, FALSE);
			//
			refreshTalkerList(hMgr);
			//
			showNotification(0, &pMsg->task.data.route.idInfo_from, 0, 0, 0, 0, _T("主持人停止了你的发言"));
			//
			break;
		}
		else  if (pContent->taskInteractionReq.usOp == CONST_imOp_permitToSpeak) {
			//
			if (0) {
				QY_MESSENGER_ID  idInfo_compere = unused_dlgTalk_get_idInfo_compere(hMgr);
				if (idInfo_compere.ui64Id != pMsg->task.data.route.idInfo_from.ui64Id) {
					showNotification(0, &pMsg->task.data.route.idInfo_from, 0, 0, 0, 0, _T("错误：收到一个非主持人的请求"));
					goto  errLabel;
				}
			}
			if (!dlgTalk_bConfCompere(hMgr, pMsg->task.data.route.idInfo_from)) {
				showNotification(0, &pMsg->task.data.route.idInfo_from, 0, 0, 0, 0, _T("错误：收到一个非主持人的请求"));
				goto  errLabel;

			}

			//
			pProcInfo->do_permitToSpeak(hMgr,pMsg->task.data.route.idInfo_from);

			//
#if 0
			pMgrVar->av.taskInfo.confMem_confCtrl.ucbPermitToSpeak = TRUE;
			//
			//
			pMgrVar->av.taskInfo.confMem_confCtrl.idInfo_starter.ui64Id = pMgrVar->av.taskInfo.idInfo_starter.ui64Id;
			pMgrVar->av.taskInfo.confMem_confCtrl.tStartTime = pMgrVar->av.taskInfo.tStartTime_org;
			pMgrVar->av.taskInfo.confMem_confCtrl.uiTranNo = pMgrVar->av.taskInfo.uiTranNo_org;
			//
			store_ConfMem_confCtrl(&pMgrVar->av.taskInfo.confMem_confCtrl, &pMgrVar->addr.idInfo);
			//
			if (pProcInfo->cfg.policy.avRules.ucbLetConfMgrSetMicOn) {

				//  2017/07/13
				setCurSharedObjUsr_localAv(pProcInfo, pMgrVar->av.iIndex_sharedObj_localAv, hMgr);

				dlgTalk_requestToSpeak(hMgr, TRUE);
			}
			//
			refreshTalkerList(hMgr);
			//
			showNotification(0, &pMsg->task.data.route.idInfo_from, 0, 0, 0, 0, _T("主持人请你发言"));
#endif
			//
			break;
		}
		//
		else  if (pContent->taskInteractionReq.usOp == CONST_imOp_requestToControlDesktop_yz) {
			if (pQyMc->iCustomId != CONST_qyCustomId_bjyz)  goto  errLabel;
			//
			BOOL  bRemoteAssist = TRUE;
			//	
			dlgTalk_OnCmd_shareScreen(hMgr, bRemoteAssist);
			//
			showNotification(0, &pMsg->task.data.route.idInfo_from, 0, 0, 0, 0, _T("请你共享屏幕"));
			//
			break;
		}
		else  if (pContent->taskInteractionReq.usOp == CONST_imOp_stopControlDesktop_yz) {
			if (pQyMc->iCustomId != CONST_qyCustomId_bjyz)  goto  errLabel;
			//
			BOOL  bRemoteAssist = TRUE;
			//	
			dlgTalk_OnCmd_shareScreen(hMgr, bRemoteAssist);
			//
			showNotification(0, &pMsg->task.data.route.idInfo_from, 0, 0, 0, 0, _T("请你取消共享"));
			//
			break;
		}
		else  if (pContent->taskInteractionReq.usOp == CONST_imOp_setCompere) {
			//
			if (pMisCnt->idInfo.ui64Id != pMgrVar->av.taskInfo.idInfo_starter.ui64Id)  goto  errLabel;
			if (!dlgTalk_bConfInitiator(hMgr, pMsg->task.data.route.idInfo_from)) {
				showInfo_open0(0, 0, _T("taskInteractionReq: failed, not idInfo_initiator"));
				goto  errLabel;
			}
			if (!pContent->taskInteractionReq.idInfo_compere.ui64Id)  goto  errLabel;
			//
			pMgrVar->av.taskInfo.unused_idInfo_compere = pContent->taskInteractionReq.idInfo_compere;
			//
			_sntprintf(tBuf, mycountof(tBuf), _T("taskInteractionReq: set compere to %I64u"), pMgrVar->av.taskInfo.unused_idInfo_compere.ui64Id);
			showInfo_open0(0, 0, tBuf);
			//
			sendConfCtrlState(hMgr, m_var.addr.idInfo, _T(""));

			//
			break;
		}
		else {
#ifdef  __DEBUG__
			traceLogA((char*)"%I64u request to refresh activeMems info", pMsg->task.data.route.idInfo_from.ui64Id);
#endif
		}

		//
		sendTaskInteractionResp(0, 0, pContent->taskInteractionReq.tStartTime_org, pContent->taskInteractionReq.uiTranNo_org, pContent->taskInteractionReq.ucStep, pContent->taskInteractionReq.idInfo_imGrp_related.ui64Id, pMsg->task.data.route.idInfo_from.ui64Id);


		//
		//if  (  !pVc->bNeedRefresh_activeMems_from  &&  !bBroadcasted  )  
		if (!bBroadcasted)
		{
			pProcInfo->sendConfKey(hDlg, pMsg->task.data.route.idInfo_from, _T("send back all mems info to the requester"));
			//
#if  0
#ifdef  __DEBUG__
			traceLogA((char*)"send back all mems info to the requester");
#endif
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("Send back all mems info to %I64u"), pMsg->task.data.route.idInfo_from.ui64Id);
#endif
		}


		//
		refreshConfLayout(pMgrVar->av.taskInfo.iIndex_taskInfo);


		//  2013/07/18
		dyn_d3dWall_refreshImgs(hDlg, (TCHAR*)_T("showMsg_task_taskInteractionReq.9325"));

		//
		talk_refreshLayout_mgr(hDlg);


		//
		break;
	}
											 break;

	default:

		break;

	}




	//
	iErr = 0;

errLabel:


	return  iErr;
}


extern int applyFy(QY_MESSENGER_ID idInfo_grp, BOOL  bEnable);

//

//
int refreshMosaicTransStatus(HWND  hDlg,  DLG_TALK_var  *  pDlgMgrVar)
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	DLG_talk_mosaicTransStatus	status;
	memset(&status, 0, sizeof(status));

	if (!isTalkerShadowMgr(pDlgMgrVar->addr))  return  -1;

	if (!pDlgMgrVar->av.taskInfo.bTaskExists) return  -1;
	if (pDlgMgrVar->av.taskInfo.ucbStarter)  return  -1;

	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, pDlgMgrVar->av.taskInfo.iIndex_taskInfo);
	if (!pTaskInfo)  goto  errLabel;
	QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
	if (pTc->common.uiType != CONST_taskDataType_conf)  goto  errLabel;
	//
	int i;
	for (i = 0; i < pTc->videoConference.usCntLimit_activeMems_from; i++) {
		DLG_TALK_videoConferenceActiveMemFrom* pActiveMem_from = &pTc->videoConference.activeMems_from[i];
		if (pActiveMem_from->avStream.idInfo.ui64Id == pDlgMgrVar->av.taskInfo.idInfo_starter.ui64Id) {
			switch (pActiveMem_from->avStream.obj.resObj.uiObjType) {
			case  CONST_objType_mosaicStream_video:
				status.uiTranNo_openAvDev_confMosaic_video = pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev;
				break;
			case  CONST_objType_mosaicStream_resource:
				status.uiTranNo_openAvDev_confMosaic_resource = pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev;
				//
				status.bDisplayResource = TRUE;
				status.iW_resource = pActiveMem_from->avStream.obj.tranInfo.video.vh_decompress.bih.biWidth;
				status.iH_resource = pActiveMem_from->avStream.obj.tranInfo.video.vh_decompress.bih.biHeight;
				break;
			default:
				break;
			}
		}
		//
		//if (bFound_mosaic)  break;
		//
		continue;
	}

	//
	if (status.uiTranNo_openAvDev_confMosaic_video && status.uiTranNo_openAvDev_confMosaic_resource) {
		//
		status.ucb2Streams = true;
		//
		status.bDisplayResource = false;
		status.iW_resource = 0;
		status.iH_resource = 0;
	}



	if (memcmp(&status, &pDlgMgrVar->av.taskInfo.mosaicTrans.status, sizeof(status))) {  //  2014/11/16
		pDlgMgrVar->av.taskInfo.mosaicTrans.status = status;
		askToRefreshLayout_mgr(hDlg);
		//
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("dlgTalk_procVideo: mosaic.status changed, after askToRefreshLayout_mgr "));
#endif
	}

	//
	iErr = 0;

errLabel:

return  iErr;

}


//
int  tmpHandler_showMsg_task_confKey(void* hDlgTalkParam, DLG_TALK_var& m_var, void* p1, void* pMsgParam,
	IM_CONTENTU* pContent)
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	HWND				hDlg = (HWND)hDlgTalkParam;
	MIS_MSGU* pMsg = (MIS_MSGU*)pMsgParam;
	if (!pMsg)  return  -1;
	if (pMsg->uiType != CONST_misMsgType_task)  return  -1;


	//			
	int							i, j;
	BOOL							bNeedRefresh_activeMems_from = FALSE;	//  2010/09/12

	//
	TCHAR  tBuf[128];
#ifdef  __DEBUG__
	traceLogA((char*)"confKey");
#endif
	_sntprintf(tBuf, mycountof(tBuf), _T("talker%I64u: recv confKey from %I64u"), m_var.addr.idInfo.ui64Id, pMsg->task.data.route.idInfo_from.ui64Id);
	showInfo_open0(0, 0, tBuf);



	//
	if (!m_var.av.taskInfo.bTaskExists)  goto  errLabel;
	if (m_var.av.taskInfo.ucbStarter) {
#ifdef  __DEBUG__
		traceLogA((char*)"Can't send status to starter.");
#endif
		goto  errLabel;
	}
	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, m_var.av.taskInfo.iIndex_taskInfo);
	if (!pTaskInfo)  goto  errLabel;
	if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  goto  errLabel;
	QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
	DLG_TALK_videoConference* pVc = &pTc->videoConference;

#if  0
	for (i = 0; i < pContent->videoConferenceStatus.usCnt; i++) {
		if (!pContent->videoConferenceStatus.mems[i].mem.idInfo.ui64Id)  break;
		if (!pContent->videoConferenceStatus.mems[i].ucbActive)  break;
		if (i >= mycountof(pVc->activeMems_from))  break;
		if (pVc->activeMems_from[i].mem.idInfo.ui64Id != pContent->videoConferenceStatus.mems[i].mem.idInfo.ui64Id
			|| pVc->activeMems_from[i].tranInfo.audio.uiTranNo_openAvDev != pContent->videoConferenceStatus.mems[i].tranInfo.audio.uiTranNo_openAvDev
			|| pVc->activeMems_from[i].tranInfo.video.uiTranNo_openAvDev != pContent->videoConferenceStatus.mems[i].tranInfo.video.uiTranNo_openAvDev
			)
		{
			//  pVc->activeMems_from[i].mem.idInfo.ui64Id  =  pContent->videoConferenceStatus.mems[i].mem.idInfo.ui64Id;
			memcpy(&pVc->activeMems_from[i].mem, &pContent->videoConferenceStatus.mems[i].mem, sizeof(pVc->activeMems_from[i].mem));
			memcpy(&pVc->activeMems_from[i].tranInfo, &pContent->videoConferenceStatus.mems[i].tranInfo, sizeof(pVc->activeMems_from[i].tranInfo));	//  2009/05/31
			//  getTalkerDesc(  m_var.pMisCnt,  &pVc->activeMems_from[i].mem.idInfo,  pVc->activeMems_from[i].desc,  mycountof(  pVc->activeMems_from[i].desc  ),  0,  0  );
			M_getActiveMemDesc(m_var.pMisCnt, &pVc->activeMems_from[i].mem.idInfo, pVc->activeMems_from[i].desc, mycountof(pVc->activeMems_from[i].desc));
			//
			bNeedRefresh_activeMems_from = TRUE;			//  2010/09/12

			//
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("Conference status changed, %I64u modified."), pVc->activeMems_from[i].mem.idInfo.ui64Id);
		}
	}
	j = i;
	for (; i < mycountof(pVc->activeMems_from); i++) {
		if (pVc->activeMems_from[i].mem.idInfo.ui64Id) {
			pVc->activeMems_from[i].mem.idInfo.ui64Id = 0;
			//
			bNeedRefresh_activeMems_from = TRUE;			//  2010/09/12
		}
	}
	i = j;
#endif


#if  10	//  2013/07/18
	int  a = 0;
	for (i = 0; i < pContent->confKey.usCnt; i++) {
		if (!pContent->confKey.mems[i].avStream.idInfo.ui64Id)  break;
		//if  (  !pContent->videoConferenceStatus.mems[i].ucbActive  )  break;
		if (i >= mycountof(pVc->activeMems_from))  break;

		//
#if  0
		if (pContent->videoConferenceStatus.mems[i].usIndex_speaker >= mycountof(pVc->activeMems_from)) {
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("Conference status err, usIndex_activeMems_from too big."));
			goto  errLabel;
		}

		//
		for (; a < pContent->videoConferenceStatus.mems[i].usIndex_speaker; a++) {
			if (pVc->activeMems_from[a].idInfo.ui64Id) {
				pVc->activeMems_from[a].idInfo.ui64Id = 0;
			}
			//
			bNeedRefresh_activeMems_from = TRUE;
		}
#endif
		//
		DLG_TALK_videoConferenceActiveMemFrom* pActiveMem_from = &pVc->activeMems_from[a];
		if (pActiveMem_from->avStream.idInfo.ui64Id != pContent->confKey.mems[i].avStream.idInfo.ui64Id
			|| pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev != pContent->confKey.mems[i].avStream.obj.tranInfo.audio.uiTranNo_openAvDev
			|| pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev != pContent->confKey.mems[i].avStream.obj.tranInfo.video.uiTranNo_openAvDev
			)
		{
			//  
			//memcpy(  &pActiveMem_from->avStream.idInfo,  &pContent->videoConferenceStatus.mems[i].avStream.idInfo,  sizeof(  pActiveMem_from->avStream.idInfo  )  );
			//memcpy(  &pActiveMem_from->avStream.obj.tranInfo,  &pContent->videoConferenceStatus.mems[i].avStream.obj.tranInfo,  sizeof(  pActiveMem_from->avStream.obj.tranInfo  )  );	//  2009/05/31
			pActiveMem_from->avStream = pContent->confKey.mems[i].avStream;	//  2009/05/31
			//
			//  getTalkerDesc(  m_var.pMisCnt,  &pVc->activeMems_from[i].mem.idInfo,  pVc->activeMems_from[i].desc,  mycountof(  pVc->activeMems_from[i].desc  ),  0,  0  );
			M_getActiveMemDesc(m_var.pMisCnt, &pActiveMem_from->avStream.idInfo, pActiveMem_from->desc, mycountof(pActiveMem_from->desc));
			//
			bNeedRefresh_activeMems_from = TRUE;			//  2010/09/12

			//
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("confKey changed, %I64u modified."), pActiveMem_from->avStream.idInfo.ui64Id);
		}
		a++;
	}

	
	//  j  =  i;
	for (; a < mycountof(pVc->activeMems_from); a++) {
		DLG_TALK_videoConferenceActiveMemFrom* pActiveMem_from = &pVc->activeMems_from[a];
		if (pActiveMem_from->avStream.idInfo.ui64Id) {
			//pActiveMem_from->avStream.idInfo.ui64Id  =  0;
			memset(pActiveMem_from, 0, sizeof(pActiveMem_from[0]));
			//
			bNeedRefresh_activeMems_from = TRUE;			//  2010/09/12
		}
	}
	//  i  =  j;
#endif

						  //
#if  0
	for (; i < pContent->videoConferenceStatus.usCnt; i++) {		//  skipped if active mem too many.
		if (!pContent->videoConferenceStatus.mems[i].ucbActive)  break;
	}
#endif
	for (j = 0; j < pContent->confKey.requestingMems.usCnt; j++) {
		if (!pContent->confKey.requestingMems.mems[j].idInfo.ui64Id)  break;
		if (j >= mycountof(pVc->requestingMems_from))  break;
		if (pVc->requestingMems_from[j].avStream.idInfo.ui64Id != pContent->confKey.requestingMems.mems[j].idInfo.ui64Id) {
			pVc->requestingMems_from[j].avStream.idInfo.ui64Id = pContent->confKey.requestingMems.mems[j].idInfo.ui64Id;
			//  getTalkerDesc(  m_var.pMisCnt,  &pVc->requestingMems_from[j].idInfo,  pVc->requestingMems_from[j].desc,  mycountof(  pVc->requestingMems_from[j].desc  ),  0,  0  );
			M_getActiveMemDesc(m_var.pMisCnt, &pVc->requestingMems_from[j].avStream.idInfo, pVc->requestingMems_from[j].desc, mycountof(pVc->requestingMems_from[j].desc));
		}
	}
	for (; j < mycountof(pVc->requestingMems_from); j++) {
		if (pVc->requestingMems_from[j].avStream.idInfo.ui64Id)  pVc->requestingMems_from[j].avStream.idInfo.ui64Id = 0;
	}

	//
	int bAmplification = pContent->confKey.confLayoutParam.respVideoStatus.bAmplification;


	//
#ifdef  __DEBUG__
	printDlgTalkVideoConference(pVc);
#endif

	//  2009/05/31
	refreshTaskAv_videoConferenceOthers(hDlg);

	//
	QY_SHARED_OBJ* pSharedObj;
	pSharedObj = getSharedObjByIndex(pProcInfo, m_var.av.iIndex_sharedObj_localAv);
	if (pSharedObj) {
		SHARED_OBJ_USR* pSharedObjUsr = getSharedObjUsr(pSharedObj, m_var.av.iIndex_usr_localAv);
		if (pSharedObjUsr && pSharedObjUsr->iTaskId == m_var.av.taskInfo.iTaskId) {
			if (isMemFromActive(pVc, &m_var.pMisCnt->idInfo, mynull, NULL)) {
				if (pTc->ucbNotSendData) {
					//  2010/12/29, 为了加强客户端的安全性，要求视频只能在用户点击时，才能进入发言态。从主持人的列表里下来的信息不能打开发言开关。
#if  0
					if (m_var.av.taskInfo.bEnableToSpeak) {
						pSharedObjUsr->ucbNotSendData = FALSE;
						qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("Conference status refreshed. Start to speak."));
					}
					else {
						qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("Conference status refreshed. This messenger is already in active list but in fact do not speak."));
					}
#else
  //
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("Conference status refreshed. This messenger is already in active list but in fact do not speak."));
					//
#endif
				}
			}
			else {
#if  0
				if (!pSharedObjUsr->ucbNotSendData) {
					pSharedObjUsr->ucbNotSendData = TRUE;
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("Conference status refreshed. Speaking stopped."));
				}
#endif
			}
		}
	}

	if (bNeedRefresh_activeMems_from) {
#if  0
		freeCapImageBySth(hDlg, 0, m_var.av.taskInfo.iTaskId, NULL, &m_var.av.peerImages);	//  2010/09/12
		if (m_var.av.taskInfo.bTaskExists && m_var.av.taskInfo.hWnd_remoteAv) {
			QY_WMBUF_COMM		wmBuf;
			memset(&wmBuf, 0, sizeof(wmBuf));
			wmBuf.uiType = CONST_qyWmParam_freeCapImage;
			wmBuf.u.freeCapImage.iTaskId = m_var.av.taskInfo.iTaskId;
			SendMessage(m_var.av.taskInfo.hWnd_remoteAv, CONST_qyWm_comm, 0, (LPARAM)&wmBuf);
		}
#endif
		dlgTalk_freeCapImageBySth_mgr(hDlg, m_var.av.taskInfo.iTaskId, NULL);		//  2010/09/12
	}

	//
#if 0
	SendMessage(m_var.hWnd_instantAssistant, CONST_qyWm_comm, 0, 0);
#endif
	//  2017/07/05
	refreshTalkerList(hDlg);

	//
	if (m_var.av.taskInfo.unused_idInfo_compere.ui64Id != pContent->confKey.idInfo_compere.ui64Id) {
		m_var.av.taskInfo.unused_idInfo_compere.ui64Id = pContent->confKey.idInfo_compere.ui64Id;
	}

	//  2010/12/29
	m_var.av.taskInfo.usLayoutType_starter = pContent->confKey.usLayoutType_starter;



	//
	if (!dlgTalk_get_usLayoutType_local(hDlg)) {
#if  0
		BOOL	bModified = FALSE;
		dlgTalk_refresh_usLayoutType_cur(hDlg, &bModified);
		//  if  (  bModified  )  
		{
			dlgTalk_setLayout(hDlg, m_var.av.usLayoutType_cur);
			sizeAllControls_dlgTalk(hDlg, m_var);			//  2011/10/05
		}
#endif
		askToRefreshLayout_mgr(hDlg);
	}


	if ( pProcInfo->bApplyFy) {
		pProcInfo->bApplyFy = false;

		if (!isMemFromActive(pVc, &m_var.pMisCnt->idInfo, mynull, NULL)) {
			QY_MESSENGER_ID idInfo_grp;
			idInfo_grp.ui64Id = pProcInfo->av.localAv.idInfo_curConference.ui64Id;
			if (applyFy(idInfo_grp, TRUE) == 0) {
				showInfo_open0(0, _T("applyFy"), _T("tmpHandler_showMsg_task_confKey auto apply fy success"));
			}
			else {
				showInfo_open0(0, _T("applyFy"), _T("tmpHandler_showMsg_task_confKey auto apply fy failed"));

			}
	}
		else {
			showInfo_open0(0, _T("applyFy"), _T("tmpHandler_showMsg_task_confKey auto apply isMemFromActive=true"));
		}
	}

	//break;

	iErr = 0;

errLabel:

	//
	refreshMosaicTransStatus(hDlg, &m_var);

	//
	talk_refreshLayout_mgr(hDlg);

	//
	AEC_layout_chk(&pProcInfo->av.aecInfo.aecLayout);

	//
	pProcInfo->confKeyChanged(hDlg);


	//
	return  iErr;
}



///////////////////////////////////


int  tmpHandler_showMsg_task_statusConfLayoutParam(void* hDlgTalkParam, DLG_TALK_var& m_var, void* p1, void* pMsgParam,
	IM_CONTENTU* pContent)
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	HWND				hDlg = (HWND)hDlgTalkParam;
	MIS_MSGU* pMsg = (MIS_MSGU*)pMsgParam;
	if (!pMsg)  return  -1;
	if (pMsg->uiType != CONST_misMsgType_task)  return  -1;


	//			
	int							i, j;
	BOOL							bNeedRefresh_activeMems_from = FALSE;	//  2010/09/12

	//
	TCHAR  tBuf[128];
#ifdef  __DEBUG__
	traceLogA((char*)"confKey");
#endif
	_sntprintf(tBuf, mycountof(tBuf), _T("talker%I64u: recv confKey from %I64u"), m_var.addr.idInfo.ui64Id, pMsg->task.data.route.idInfo_from.ui64Id);
	showInfo_open0(0, 0, tBuf);



	//
	if (!m_var.av.taskInfo.bTaskExists)  goto  errLabel;
	if (m_var.av.taskInfo.ucbStarter) {
#ifdef  __DEBUG__
		traceLogA((char*)"Can't send status to starter.");
#endif
		goto  errLabel;
	}
	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, m_var.av.taskInfo.iIndex_taskInfo);
	if (!pTaskInfo)  goto  errLabel;
	if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  goto  errLabel;
	QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
	DLG_TALK_videoConference* pVc = &pTc->videoConference;



	//
	int bAmplification = pContent->statusConfLayoutParam.confLayoutParam.respVideoStatus.bAmplification;

	if (pQyMc->m_iCtxSubtype == CONST_ctxSubtype_qmcQt) {
		if (bAmplification) {
			pProcInfo->m_ipcProc.op.idInfo.ui64Id = pContent->statusConfLayoutParam.confLayoutParam.enlargeParam.ui64Id;
		}
		else {
			pProcInfo->m_ipcProc.op.idInfo.ui64Id = 0;
		}
	}


	//break;

	iErr = 0;

errLabel:




	//
	return  iErr;
}



//  测试时有用
int  doSelIpc_local(IpcParam* pIpcParam, HWND  hTalk_mgr)
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt)  return  -1;

	do {
		//
			  //  本地操作
		OnvifMsg_nvrControl  m = { 0 };
		m.uiType = CONST_qisMsgType_onvif;
		m.iSubtype = CONST_onvifMsg_subtype_nvrControl;
		//
		m.usCmd = CONST_nvrControlCmd_selectChannel;
		m.iChannel = pIpcParam->iChannel;
		//
		qisPipe_writeMsg(&m, sizeof(m), pProcInfo->m_ipcProc.pQisPipe);



		//
		iErr = 0;
	} while (false);

	return  iErr;
}






//  2014/09/05
  int  tmpHandler_showMsg_input(  void  *  hDlgTalkParam,  	DLG_TALK_var	&	m_var,  void  *  p1, void  *  pMsgParam  )
{
	int		iErr	=	-1;

	HWND				hDlg					=	(  HWND  )hDlgTalkParam;
	
	PARAM_PROC_ROW	*	pParam					=	(  PARAM_PROC_ROW  *  )p1;
	MIS_MSGU		*	pMsg					=	(  MIS_MSGU  *  )pMsgParam;
	
	QY_MC* pQyMc = m_var.pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli	*	pProcInfo				=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	int					i;
	TCHAR				tBuf[128];


	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;
			
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;


	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_input:  {

				  IM_CONTENTU			*	pContent	=	M_getMsgContent(  pMsg->input.ucFlg,  &pMsg->input.data  );									 

				  switch  (  pContent->uiType  )  {
						  case  CONST_imCommType_retrieveDynBmps:
							    //
							    if  (  pContent->retrieveDynBmps.conf.idInfo_imGrp_related.ui64Id  )  {		//  2014/09/26
								    if  (  !isUcFlgResp(  pMsg->input.ucFlg  )  )  {
										#ifdef  __DEBUG__
												traceLog((TCHAR*)  _T(  "tmpHandler_showMsg_input: recvd a req: retrieve dynBmp"  )  );
										#endif
										//
										//CQySyncFlg	syncFlg;	
										//
										CQyMalloc  mallocObj_tmppMsg;
										MIS_MSGU  *  tmp_pMsg  =  (  MIS_MSGU  *  )mallocObj_tmppMsg.mallocf(  sizeof(  MIS_MSGU  )  );
										if  (  !tmp_pMsg  )  goto  errLabel;
										memcpy(  tmp_pMsg,  pMsg,  sizeof(  pContent->retrieveDynBmps  )  +  offsetof(  MIS_MSG_INPUT,  data  )  );
										pMsg  =  tmp_pMsg;  //  2014/12/25
										//
										if  (  !m_var.av.taskInfo.bTaskExists  )  goto  errLabel;
										if  (  pShadowMgr->bgWall.bgWallCfg.ucbNeverJoinInBgWall  ) {											
											qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHandler_showMsg_input, this client never join in background wall"  )  );
											goto  errLabel;											
										}
										//
										#if  0	//  2014/12/25
										if  (  syncFlg.sync(  &m_var.syncFlgs.bInSequence  )  )  {		
												qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHandler_showMsg_input failed, bLocked already"  )  );
												goto  errLabel;
										
										}
										#endif
										//
										#ifdef  __TEST_ONLY__
#if  0
												if  (  b__TEST_joinInBgWall__(  )  )  {
													static  BOOL  bDone  =  FALSE;
													if  (  !bDone  )  {
														bDone  =  TRUE;
														myMessageBox(  hDlg,  _T(  "Test join in bgWall"  ),  _T(  "Warning"  ),  MB_OK  );
													}
													m_var.av.taskInfo.joinInBgWall.idcRet_joinInBgWall  =  ID_qyOk;
													pFuncs->pf_setCurSharedObjUsr_localAv(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv,  hDlg  );  
												}
#endif
										#endif
										//
										if  (  !pShadowMgr->av.joinInBgWall.idcRet_joinInBgWall  )  {
											//
											HWND  hCurTalk  =  NULL;
											for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
												if  (  IsWindow(  pShadowMgr->shadows[i].hShadow  )  &&  isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  break;
											}
											if  (  i  ==  mycountof(  pShadowMgr->shadows  )  )  {	//  2014/10/08. 这里还少考虑一个3d的情况
												hCurTalk  =  hDlg;
												}
											else  {
												  hCurTalk  =  pShadowMgr->shadows[i].hShadow;
											}
											//
											TCHAR  *  pHint_showBgWall  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_showBgWall  );
											TCHAR  *  pStr_never  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_never  );
											int  idcRet  =  IDCANCEL;
											//
											#if  0  //  2016/03/09
											if  (  !dyn_bFullScreen_d3dWall(  )  )  {
												//
												idcRet  =  qyMessageBox_custom(  hCurTalk,  pHint_showBgWall,  _T(  "Qycx.com"  ),  pStr_never,  MB_YESNOCANCEL,  20,  NULL  );
											}
											#endif
											//
											//  2016/03/09
											#if  0		//  2017/11/01
											if  (  !pShadowMgr->av.joinInBgWall.ucbNeedToAsk_willingTo_joinInBgWall  )  {
												pShadowMgr->av.joinInBgWall.ucbNeedToAsk_willingTo_joinInBgWall  =  TRUE;
												dyn_d3dWall_askToRefreshMenu(  );
											}
											#endif
											//
											if  (  idcRet  ==  IDCANCEL  )  {
												goto  errLabel;
											}
											//
											pShadowMgr->av.joinInBgWall.idcRet_joinInBgWall  =  idcRet;											
											if  (  idcRet  !=  ID_qyOk  )  {
												if  (  idcRet  ==  ID_qyCancel  )  {
													pShadowMgr->bgWall.bgWallCfg.ucbNeverJoinInBgWall  =  TRUE;
													saveBgWallPolicy_neverJoinInBgWall(  &m_var.addr.idInfo,  pShadowMgr->bgWall.bgWallCfg.ucbNeverJoinInBgWall  );
												}
												goto  errLabel;
											}
											if  (  idcRet  ==  ID_qyOk  )  {	//  
												#ifdef  __DEBUG__
														traceLog((TCHAR*)  _T(  "调用声音独占的功能 "  )  );																
												#endif
												pFuncs->pf_setCurSharedObjUsr_localAv(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv,  m_var.av.iIndex_usr_localAv  );  
											}
										}
										if  (  pShadowMgr->av.joinInBgWall.idcRet_joinInBgWall  !=  ID_qyOk  )  {
											#ifdef  __DEBUG__
													traceLog((TCHAR*)  _T(  "access denied: idcRet_joinInBgWall is not idyes"  )  );
											#endif
											goto  errLabel;
										}
										//
										if  (  confMem_sndRetrieveDynBmpsRespToMsgr(  hDlg,  &m_var,  pMsg  )  )  goto  errLabel;
										//
										iErr  =  0;  goto  errLabel;
									}
									//
									if  (  confStarter_procRetrieveDynBmpsResp(  hDlg,  &m_var,  pMsg  )  )  goto  errLabel;
									//
									iErr  =  0;  goto  errLabel;
								}
								//
								if  (  !isUcFlgResp(  pMsg->input.ucFlg  )  )  {
									#ifdef  __DEBUG__
											traceLog((TCHAR*)  _T(  "tmpHandler_showMsg_input failed: req of retrieveDynBmps is not wanted here"  )  );
									#endif
									goto  errLabel;								
								}								
								//
								if  (  pMsg->input.uiTranNo  ==  pShadowMgr->selectRemoteVideo.uiTranNo  )  break;
								//
							    for  (  i  =  0;  i  <  mycountof(  pShadowMgr->talkerDynBmps  );  i  ++  )  {
									if  (  pMsg->input.uiTranNo  ==  pShadowMgr->talkerDynBmps[i].taskInfo.retrieveOne.uiTranNo  )  {
										break;
									}
								}
								if  (  i  ==  mycountof(  pShadowMgr->talkerDynBmps  )  )  goto  errLabel;
								//
								if  (  pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.usIndex_obj  )  {
									#ifdef  __DEBUG__
											traceLog((TCHAR*)  _T(  "Err: rule.usIndex_obj is not 0. so retrieveOne is not permitted"  )  );
									#endif
									goto  errLabel;
								}
								//
								TALKER_dynBmp  *  pTalkerDynBmp;  
								pTalkerDynBmp  =  &pShadowMgr->talkerDynBmps[i];
								if  (  pContent->retrieveDynBmps.usCnt  !=  1  )  goto  errLabel;
								if  (  !pContent->retrieveDynBmps.mems[0].qisResObj.resObj.usIndex_obj  )  {
									#ifdef  __DEBUG__
											traceLog((TCHAR*)  _T(  "tmpHandler_showMsg_input: retrieveOne failed, usIndex_obj is 0"  )  );
									#endif
									goto  errLabel;
								}
								pTalkerDynBmp->dynBmpRule.dynBmp.resObj.usIndex_obj  =  pContent->retrieveDynBmps.mems[0].qisResObj.resObj.usIndex_obj;
								_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Retrieve one: usIndex_obj %d"  ),  pTalkerDynBmp->dynBmpRule.dynBmp.resObj.usIndex_obj  );
								showInfo_open0(  0,  0,  tBuf  );
								
								//
								BOOL  bNeedProgress;  bNeedProgress  =  FALSE;
								tryToFindSameRule_sndViewDynBmpReq(  hDlg,  &m_var,  bNeedProgress,  NULL,  i  );

							    break;
						  default:
								  break;
				  }
				  }
				  break;
				  
			default:
					break;
		}
		
		iErr  =  0;

errLabel:


	
	return  iErr;

}


//  2014/07/12
 int  mySendTalkResp(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_TALK  *  pMsg,  MIS_MSGU  *  pMsgBuf  )
{
	int				iErr			=	-1;
	IM_CONTENTU	*	pContent		=	(  IM_CONTENTU  *  )pMsg->data.buf;
	int				lenInBytes;
	unsigned  short		usRespCode			=	CONST_qyRc_unknown;	
	MIS_CNT		*	pMisCnt			=	(  MIS_CNT  *  )pMsg->pMisCnt;

	switch  (  pContent->uiType  )  {
			case  CONST_imCommType_htmlContent:
				  {
				
					  MSG_ROUTE					route;
					  unsigned  char				ucFlg	=	CONST_commFlg_resp;
					  IM_HTML_CONTENT				resp;

					  memset(  &route,  0,  sizeof(  route  )  );
					  memcpy(  &route.debugInfo,  &pMsg->data.route.debugInfo,  sizeof(  route.debugInfo  )  );

					  ucFlg  |=  CONST_commFlg_routeTalkData;

					  memset(  &resp,  0,  sizeof(  resp  )  );
					  resp.uiType  =  pContent->uiType;
					  resp.ucbResp  =  TRUE;

					  lenInBytes  =  sizeof(  resp  );
				
					  usRespCode  =  0;

					  if  (  postMsg2Mgr_mc(  pMisCnt,  &route,  CONST_misMsgType_outputTask,  ucFlg,  usRespCode, pMsg->tStartTime,  pMsg->uiTranNo,  0,  (  char  *  )&resp,  lenInBytes,  &pMsg->addr_logicalPeer.idInfo,  &pMsg->data.route.idInfo_from,  pMsg->uiChannelType,  pMsgBuf,  FALSE  )  )  goto  errLabel;
					  }
				  break;
			default:
					break;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}






 //  2012/04/30
  int  tmpHandler_showMsg(  void  *  hDlgTalkParam,  void  *  p1, void  *  pMsgParam  )
{

	int					iErr					=	-1;
	HWND				hDlg					=	(  HWND  )hDlgTalkParam;

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pm_var					=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlg  );
	if  (  !pm_var  )  return  -1;	
	DLG_TALK_var	&	m_var					=	*pm_var;

	PARAM_PROC_ROW	*	pParam					=	(  PARAM_PROC_ROW  *  )p1;
	MIS_MSGU		*	pMsg					=	(  MIS_MSGU  *  )pMsgParam;

	QY_MC* pQyMc = m_var.pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli	*	pProcInfo				=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	TCHAR				txtContent[1024]		=	_T(  ""  );
	TCHAR				senderDesc[255  +  1]	=	_T(  ""  );
	TCHAR				receiverDesc[255  +  1]	=	_T(  ""  );
	time_t				t;
	int					tmpiRet					=	0;
	//
	TCHAR				tBuf[1024]				=	_T(  ""  );
	int					i;
	//

	if  (  !hDlg  ||  !pParam  ||  !pMsg  )  return  -1;

	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

    if  (  !bReady_toShowMsg(  hDlg  )  )  goto  errLabel;

	mytime(  &t  );

	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_talk:
				  if  (  pMsg->talk.tStartTime_processed  )  break;
				  mytime(  &pMsg->talk.tStartTime_processed  );	//  2007/10/13
				  m_var.nMsgTalks_processed_inProcessQ  ++  ;				//  2012/05/20

				  pParam->bMsgNeedRemoved  =  TRUE;		//  2009/10/18

				  //  2011/03/15
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "show msg_talk"  )  );

				  //
				  if  (  tmpHandler_showMsg_talk(  hDlgTalkParam,  m_var,  p1,  pMsgParam  )  )  {
					  #ifdef  __DEBUG__
							  traceLog((TCHAR*)  _T(  "tmpHandler_showMsg_talk failed"  )  );
					  #endif
					  goto  errLabel;
				  }

				  
				  break;
		    case  CONST_misMsgType_task:
				  if  (  pMsg->task.tStartTime_processed  )  break;
				  mytime(  &pMsg->task.tStartTime_processed  );  //  2007/10/13, ´Ë¸³ÖµÊÇÎªÁË±ÜÃâÏûÏ¢±»ÖØ¸´´¦Àí¡£Ô­À´ÊÇÔÚ´ËcaseµÄ×îÏÂÃæ£¬ÏÖÔÚÒÆµ½ÕâÀï¡£ÊÇÒòÎª£¬Èç¹ûÖÐ¼ä´¦Àí³ö´í£¬break»ògoto µÄ»°£¬¾ÍÎÞ·¨¸³ÖµÁË£¬ÓÚÊÇ¾ÍÒªÒ»ÔÙÖØ¸´´¦Àí´ËÏûÏ¢£¬ÓÖÖØ¸´Ìø³ö£¬Ôì³ÉºóÐøÏûÏ¢ÎÞ·¨´¦ÀíµÄÏÖÏó¡£

				  //
				  if  (  !pMsg->task.iTaskId  )  pParam->bMsgNeedRemoved  =  TRUE;		//  2009/10/18

				  //
				  if (pProcInfo->tmpHandler_showMsg_task(hDlgTalkParam, &m_var, p1, pMsgParam))  goto  errLabel;

				  break;

			case  CONST_misMsgType_input:	//  2014/09/05
				  if  (  pMsg->input.tStartTime_processed  )  break;
				  mytime(  &pMsg->input.tStartTime_processed  );

				  //
				  pParam->bMsgNeedRemoved  =  TRUE;

				  //
				  if  (  tmpHandler_showMsg_input(  hDlgTalkParam,  m_var,  p1,  pMsgParam  )  )  goto  errLabel;

				  break;

			case  CONST_misMsgType_taskStatus: 
				  if  (  pMsg->taskStatus.tStartTime_processed  )  break;
				  mytime(  &pMsg->taskStatus.tStartTime_processed  );	//  2007/10/13, ´Ë¸³ÖµÊÇÎªÁË±ÜÃâÏûÏ¢±»ÖØ¸´´¦Àí¡£Ô­À´ÊÇÔÚ´ËcaseµÄ×îÏÂÃæ£¬ÏÖÔÚÒÆµ½ÕâÀï¡£ÊÇÒòÎª£¬Èç¹ûÖÐ¼ä´¦Àí³ö´í£¬break»ògoto µÄ»°£¬¾ÍÎÞ·¨¸³ÖµÁË£¬ÓÚÊÇ¾ÍÒªÒ»ÔÙÖØ¸´´¦Àí´ËÏûÏ¢£¬ÓÖÖØ¸´Ìø³ö£¬Ôì³ÉºóÐøÏûÏ¢ÎÞ·¨´¦ÀíµÄÏÖÏó¡£

				  pParam->bMsgNeedRemoved  =  TRUE;		//  2009/10/18
				  
				{
				  MIS_MSG_TASKSTATUS		*		pMsgTaskStatus								=	(  MIS_MSG_TASKSTATUS  *  )&pMsg->taskStatus;			//  ÓÐÊ±¾ÍÓÃÕâ¸ö½á¹¹£¬ 2007/07/17
				  MIS_MSG_TASK				*		pMsgTask									=	NULL;
				  IM_CONTENTU				*		pContent									=	NULL;  
				  int								iStatus										=	0;
				  int								tmpiRet;
				  //

				  if  (  !(  pMsgTask  =  findTaskInProcessQ(  &m_var,  pMsgTaskStatus->iTaskId  )  )  )  goto  errLabel;
				  pContent  =  (  IM_CONTENTU  *  )pMsgTask->data.buf;

				  //  2015/08/07
				  if  (  pContent  )  {
					  if  (  !bSupported_fileServer(  pQyMc  )  )  {
						  if  (  pContent->uiType  ==  CONST_imCommType_transferFileReq  )  {
							  if  (  pContent->transferFileReq.usSubtype  ==  CONST_procOfflineResSubtype_upload
								  ||  pContent->transferFileReq.usSubtype  ==  CONST_procOfflineResSubtype_download  )  
							  {
								  tmpiRet  =  SendMessage(  pContent->transferFileReq.hTool_offlineRes,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsgTaskStatus  );
								  if  (  tmpiRet  !=  CONST_qyWmRc_ok  )  {
									  showInfo_open0(  0,  0,  _T(  "taskStatus: to tool_offlineRes, not ok"  )  );
									  //
									  pContent->transferFileReq.bNeedCancel  =  TRUE;
									  m_var.needChkTasks.bNeedChkRecvdTasks  =  TRUE;
									  }
								  else  {
										#ifdef  __DEBUG__
												traceLog((TCHAR*)  _T(  "taskStatus: to tool_offlineRes: ok"  )  );
										#endif
								  }
							  }
						  }
					  }
				  }


				  //
				  if  (  pMsgTaskStatus->iStatus  ==  CONST_imTaskStatus_sendFinished  &&  pMsgTaskStatus->bImGrpMem  )  {	//  
					  //	
					  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
						  if  (  pShadowMgr->shadows[i].hShadow  &&  isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  {
							  CHelp_getDlgTalkVar	help_getDlgTalkVar;
							  tmpHandler_showMsg_displayTaskStatus(  pShadowMgr->shadows[i].hShadow,  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  pShadowMgr->shadows[i].hShadow  ),  pMsgTaskStatus,  pMsgTask,  pContent,  iStatus  );
						  }
					  }
					  tmpHandler_showMsg_displayTaskStatus(  hDlg,  &m_var,  pMsgTaskStatus,  pMsgTask,  pContent,  iStatus  );

					  break;
				  }

				  //
				  switch  (  pMsgTaskStatus->iStatus  )  {
						  case  CONST_imTaskStatus_sending:
						  case  CONST_imTaskStatus_receiving:

							    //  2015/08/04
							    pShadowMgr->fileTaskInfo.dwLastModifiedTickCnt_taskStatus  =  GetTickCount(  );
								pShadowMgr->fileTaskInfo.usTimes_noFileTask  =  0;

							    //
							    for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
									if  (  pShadowMgr->shadows[i].hShadow  &&  isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  {
										CHelp_getDlgTalkVar	help_getDlgTalkVar;
										tmpHandler_showMsg_displayTaskStatus(  pShadowMgr->shadows[i].hShadow,  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  pShadowMgr->shadows[i].hShadow  ),  pMsgTaskStatus,  pMsgTask,  pContent,  iStatus  );
									}
								}
							    tmpHandler_showMsg_displayTaskStatus(  hDlg,  &m_var,  pMsgTaskStatus,  pMsgTask,  pContent,  iStatus  );

								//
							    if  (  pContent  &&  pContent->uiType  ==  CONST_imCommType_transferFileReq  )  {		//  2010/12/04
									if  (  pMsgTask->idInfo_taskSender.ui64Id  !=  m_var.pMisCnt->idInfo.ui64Id  )  {
										mytime(  &pMsgTask->tStartTime_processed  );										//
									}
								}
								//
							    break;					
						  case  CONST_imTaskStatus_acceptedByReceiver:
						  case  CONST_imTaskStatus_dualByReceiver:
							    if  (  pMsgTask->iStatus  ==  CONST_imTaskStatus_req  )  {
									if  (  !pMsgTaskStatus->bImGrpMem  )  {
										pMsgTask->iStatus  =  pMsgTaskStatus->iStatus;		
									}
									//
									dlgTalk_displayAvStatus(  hDlg,  m_var,  pMsgTask->iTaskId,  pMsgTask->iStatus,  NULL  );
								}
							    break;
						  case  CONST_imTaskStatus_sendFinished:
						  case  CONST_imTaskStatus_recvFinished:
						  case  CONST_imTaskStatus_canceledBySender:
						  case  CONST_imTaskStatus_canceledByReceiver:
						  case  CONST_imTaskStatus_autoCanceledByReceiver:		//  2014/07/30

   								//
								iStatus  =  pMsgTaskStatus->iStatus;								
								//
								pMsgTask->iStatus  =  pMsgTaskStatus->iStatus;	//  2009/10/17
							    
								//
								for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
									if  (  pShadowMgr->shadows[i].hShadow  &&  isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  {
										CHelp_getDlgTalkVar	help_getDlgTalkVar;
										tmpHandler_showMsg_displayTaskStatus(  pShadowMgr->shadows[i].hShadow,  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  pShadowMgr->shadows[i].hShadow  ),  pMsgTaskStatus,  pMsgTask,  pContent,  iStatus  );
									}
								}
								tmpHandler_showMsg_displayTaskStatus(  hDlg,  &m_var,  pMsgTaskStatus,  pMsgTask,  pContent,  iStatus  );

								//  2014/11/22
								if  (  pMsgTaskStatus->iStatus  ==  CONST_imTaskStatus_canceledBySender  )  {
									if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
#if  0
										TRANSFER_AV_INFO  *  pTransferAvInfo  =  &pContent->transferAvInfo;
										PROC_TASK_AV  *  pTask  =  get_transferAvInfo_pTask(  pTransferAvInfo,  _T(  ""  )  );
										if  (  !pTask  )  goto  errLabel;
										//
										if  (  pTask->dlgTalkInProxy.bExists  )  {
											TASK_PROC_REQ		taskProcReq;
											QY_MESSENGER_ID		idInfo_dst;
											int					lenInBytes;
																													  
											memset(  &taskProcReq,  0,  sizeof(  taskProcReq  )  );
											taskProcReq.uiType  =  CONST_imCommType_taskProcReq;
											taskProcReq.usOp  =  CONST_imOp_send_cancel;
											
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
											if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  pMsgTask->usCode,  tStartTran,  uiTranNo,  0,  pMsgTask->iTaskId,  pMsgTask->uiTaskType,  (  char  *  )&taskProcReq,  lenInBytes,  &m_var.addr.idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &idInfo_dst,  pMsgTask->uiChannelType,  NULL,  FALSE  )  )  {
												//goto  errLabel;
											}

										}
#endif
									}
								}


								//
								dlgTalk_displayAvStatus(  hDlg,  m_var,  pMsgTask->iTaskId,  pMsgTask->iStatus,  NULL  );
								//  freeCapImageByTaskId(  hDlg,  0,  pMsgTaskStatus->iTaskId,  &m_var.av.peerImages  );
								dlgTalk_freeCapImageBySth_mgr(  hDlg,  pMsgTaskStatus->iTaskId,  NULL  );


								//  2009/02/20
								if  (  m_var.av.taskInfo.bTaskExists  )  {
									if  (  m_var.av.taskInfo.iTaskId  ==  pMsgTaskStatus->iTaskId  )  {
										dlgTalk_closeTaskAv(  hDlg,  m_var  );
									}
								}
								//  2013/11/18
								if  (  pShadowMgr->remoteAssist.iTaskId  ==  pMsgTaskStatus->iTaskId  )  {
									SendMessage(  pShadowMgr->remoteAssist.hWnd_remoteAssist,  WM_CLOSE,  0,  0  );
									pShadowMgr->remoteAssist.hWnd_remoteAssist  =  NULL;
									pShadowMgr->remoteAssist.iTaskId  =  0;
								}

								//  2010/12/23
								chkResources(  hDlg,  TRUE  );

								//  2012/03/24
								qmcApplyForChkingTasks_gui(  pQyMc  );

								//  2013/09/09
								dyn_d3dWall_refreshWallMemByTalker(  hDlg  );


							    break;
						  default:

							    //
							    for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {								
									 if  (  pShadowMgr->shadows[i].hShadow  &&  isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  {
										 CHelp_getDlgTalkVar	help_getDlgTalkVar;
										 tmpHandler_showMsg_displayTaskStatus(  pShadowMgr->shadows[i].hShadow,  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  pShadowMgr->shadows[i].hShadow  ),  pMsgTaskStatus,  pMsgTask,  pContent,  iStatus  );						  
									 }					  
								}
							    tmpHandler_showMsg_displayTaskStatus(  hDlg,  &m_var,  pMsgTaskStatus,  pMsgTask,  pContent,  iStatus  );

								break;
				  }

				  //
				  }

				  break;
			
			case  CONST_misMsgType_notifyTaskEnd_qmc:  				
				  if  (  pMsg->notifyTaskEnd.tStartTime_processed  )  break;
				  mytime(  &pMsg->notifyTaskEnd.tStartTime_processed  );	//  2007/10/13, 

				  pParam->bMsgNeedRemoved  =  TRUE;		//  2009/10/18

				{			  
#if  10
				  MIS_MSG_notifyTaskEnd_qmc	*	pMsgNotifyTaskEnd  =  (  MIS_MSG_notifyTaskEnd_qmc  *  )&pMsg->notifyTaskEnd;
				  if  (  pMsgNotifyTaskEnd->bToCancel  )  {
					  if  (  !pMsgNotifyTaskEnd->iTaskId  )  {
						  traceLogA(  (char*)  "iTaskId error"  );
						  goto  errLabel;
					  }
					  dlgTalk_cancelTasks(  hDlg,  &m_var,  pMsgNotifyTaskEnd->iTaskId,  FALSE  );
					  break;
				  }
				  //  
				  //  freeCapImageByTaskId(  hDlg,  0,  pMsgNotifyTaskEnd->iTaskId,  &m_var.av.meImages  );  
				  int  idc_dst  =  m_var.av.idc_me;
				  old_freeCapImageByTaskId(  hDlg,  m_var.av.idc_me,  pMsgNotifyTaskEnd->iTaskId,  &m_var.av.meZone.images,  old_M_GetDlgItem(  hDlg,  idc_dst  )  );  
#endif

				  }
				  break;

			case  CONST_misMsgType_applyForWork:
				  if  (  pMsg->applyForWork.tStartTime_processed  )  break;
				  mytime(  &pMsg->applyForWork.tStartTime_processed  );	//  2007/10/13, 

				  pParam->bMsgNeedRemoved  =  TRUE;		//  2009/10/18

				  if  (  pMsg->applyForWork.uiContentType  ==  CONST_imCommType_queryCustomerServiceOfficerReplyReq  )  {
					  if  (  m_var.av.taskInfo.bTaskExists  )  break;
					  PostMessage(  hDlg,  WM_COMMAND,  MAKEWPARAM(  ID_startAvCall,  0  ),  0  );
				  }

				  break;

			case  CONST_misMsgType_applyForTalkerShadow_qmc:  {  //  2012/04/23
				  if  (  pMsg->applyForTalkerShadow_qmc.tStartTime_processed  )  break;
				  mytime(  &pMsg->applyForTalkerShadow_qmc.tStartTime_processed  );	//  2007/10/13, 

				  pParam->bMsgNeedRemoved  =  TRUE;		//  2009/10/18

				  //  2014/12/03
				  dlgTalk_doApplyForTalkerShadow_qmc(  hDlg,  &pMsg->applyForTalkerShadow_qmc  );


				  }

				  break;


			default:
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "tmpHandler_showMsg failed, unprocessed msgType %d"  ),  pMsg->uiType  );
					#endif
					//
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHandler_showMsg failed, unprocessed msgType %d"  ),  pMsg->uiType  );
					goto  errLabel;
					break;
	}



	iErr  =  0;

errLabel:
	return  iErr;
}

 //  2012/04/30
  int  tmpHandler_shadow_displayProcessedMsg(  void  *  hDlgTalkParam,  void  *  p1, void  *  pMsgParam  )
{

	int					iErr					=	-1;
	HWND				hDlg					=	(  HWND  )hDlgTalkParam;
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pm_var					=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlg  );
	if  (  !pm_var  )  return  -1;
	DLG_TALK_var	&	m_var					=	*pm_var;
	PARAM_PROC_ROW	*	pParam					=	(  PARAM_PROC_ROW  *  )p1;
	MIS_MSGU		*	pMsg					=	(  MIS_MSGU  *  )pMsgParam;
	QY_MC* pQyMc = m_var.pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli	*	pProcInfo				=	QY_GET_procInfo_isCli(  ); //(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	TCHAR				txtContent[1024]		=	_T(  ""  );
	TCHAR				senderDesc[255  +  1]	=	_T(  ""  );
	TCHAR				receiverDesc[255  +  1]	=	_T(  ""  );
	time_t				t;
	int					tmpiRet					=	0;
	//
	TCHAR				tBuf[1024]				=	_T(  ""  );
	//

	if  (  !hDlg  ||  !pParam  ||  !pMsg  )  return  -1;

#if  0
	if  (  isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;
	if  (  !isTalkerSubtype_canInput(  m_var.iTalkerSubType  )  )  goto  errLabel;
#endif

	mytime(  &t  );

	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_talk:  {
				  MIS_MSG_routeTalkData		*	pTalkData							=	&pMsg->talk.data;
				  IM_CONTENTU				*	pContent							=	(  IM_CONTENTU  *  )pTalkData->buf;	
				  char							timeBuf[CONST_qyTimeLen  +  1]		=	"";
				  
				  if  (  !pMsg->talk.tStartTime_processed  )  {		//  只显示已经处理过的消息
					  break;
				  }

				  addToRecentMsg(  hDlg,  &m_var,  -1,  0,  mynull,  mynull,  pTalkData->route.idInfo_from,  senderDesc,  CONST_imOp_says,  0,  timeBuf,  NULL,  pContent->html.wBuf,  pParam->bFollowingRows,  pParam->bScrollIntoView,  txtContent,  mycountof(  txtContent  )  );
				  }				  
				  break;
			case  CONST_misMsgType_task:

				  if  (  !pMsg->task.tStartTime_processed  )  break;

				  if  (  !bTaskAlive(  pMsg->task.iStatus  )  )  break;
				  tmpHandler_showMsg_displayTask(  hDlg,  &m_var,  pParam,  pMsg  );
				  break;
			default:
					break;
	}

	iErr   =  0;

errLabel:
	return  iErr;
}







//
int  tmpHandler_procHtmlResp(  HWND  hDlg,  MIS_MSG_INPUT  *  pMsgInput,  MIS_MSGU  *  pMsgElem  )
{
	int  iErr  =  -1;

	if  (  pMsgElem->uiType  ==  CONST_misMsgType_talk  )  {
		if  (  pMsgInput->tStartTime  ==  pMsgElem->talk.tStartTime
			&&  pMsgInput->uiTranNo  ==  pMsgElem->talk.uiTranNo  )
		{
			//						
			CHelp_getDlgTalkVar	help_getDlgTalkVar;
			DLG_TALK_var	*	pm_var					=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlg  );
			if  (  !pm_var  )  goto  errLabel;
			
			if  (  pm_var->addr.uiObjType  ==  CONST_objType_messenger  )  {	//  2014/07/13. 因为分组比单人要复杂的多，所以这里暂时只考虑单人的情况

				pMsgElem->talk.iStatus  =  CONST_imTaskStatus_sendFinished;
						
				PARAM_PROC_ROW					param;
			
				memset(  &param,  0,  sizeof(  param  )  );
				param.pf  =  (  PF_commonHandler  )modifyRow;
				param.iCol  =  pm_var->iCol_content;
			
				safeTcsnCpy(  getRowIdStr_talk(  hDlg,  &pMsgElem->talk  ),  param.rowIdStr,  mycountof(  param.rowIdStr  )  );

				IM_CONTENTU  *  pContent  =  M_getMsgContent(  pMsgElem->talk.ucFlg,  &pMsgElem->talk.data  );
				if  (  pContent->uiType  ==  CONST_imCommType_htmlContent  )  {
				
					//
					tmpMakeHtmlStr_talk(  hDlg,  pm_var,  &pMsgElem->talk,  param.content,  mycountof(  param.content  )  );
					#ifdef  __DEBUG__
							//  _sntprintf(  param.content,  mycountof(  param.content  ),  _T(  "%s 收到"  ),  pContent->html.wBuf  );
					#endif

					//
					if  (  !isTalkerShadowMgr(  pm_var->addr  )  )  goto  errLabel;

					TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pm_var->pShadowInfo;

					int  i;
					for  (   i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
						 if  (  pShadowMgr->shadows[i].hShadow  &&  isTalkerSubtype_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  {					
							 CHelp_getDlgTalkVar	help_getDlgTalkVar_shadow;
							 if  (  doDoc_doTable_byRowId_param(  help_getDlgTalkVar_shadow.getVar(  pShadowMgr->shadows[i].hShadow  ),  &param  )  )  goto  errLabel;
						 }		
					}

					//								
					if  (  doDoc_doTable_byRowId_param(  pm_var,  &param  )  )  goto  errLabel;

				}
			}

			//
			iErr  =  1;  goto  errLabel;
		}
	}

	iErr  =  0;
errLabel:
	return  iErr;

}


//
int  getVal_bImGrpMem(  QY_MC  *  pQyMc, QY_MESSENGER_ID  *  pIdInfo_grp,  QY_MESSENGER_ID  *  pIdInfo_mem,  BOOL  *  pb  )
{
	int  iErr  =  -1;
	BOOL  bRet  =  FALSE;
	//QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	CQnmDb  db;
	IM_GRP_MEM						grpMem;
	
	if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  return  -1;

	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	if  (  !g_dbFuncs.pf_bGetImGrpMemBySth(  db.m_pDbMem->pDb,  pQyMc->cfg.db.iDbType,  _T(  ""  ),  pIdInfo_grp,  pIdInfo_mem,  0,  &grpMem  )  )  goto  errLabel;

	bRet  =  TRUE;
	
	iErr   =  0;
errLabel:
	if  (  !iErr  )  {
		if  (  pb  )  *pb  =  bRet;
	}
	return  iErr;
}


//  2015/08/02
 int  dlgTalk_OnQyComm_msgInput_procOfflineRes(  HWND  hDlg,  void  *  pDLG_TALK_var,  WPARAM  wParam,  LPARAM  lParam  )
 {
	int					iErr			=	-1;
	DLG_TALK_var	&	m_var			=	*(  DLG_TALK_var  *  )pDLG_TALK_var;
	QY_MC* pQyMc = m_var.pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	QY_WMBUF_COMM	*	pComm			=	(  QY_WMBUF_COMM  *  )lParam;

	 				
	MIS_MSG_INPUT		*	pMsg		=   (  MIS_MSG_INPUT  *  )pComm;	
	IM_CONTENTU	*	pContent	=	NULL;
	int					i;				  
	
	
	//
	if (isUcFlgRouteTalkData(pMsg->ucFlg) 
		//|| isUcFlgTalkData(pMsg->ucFlg)
		) 
	{
		pContent = (IM_CONTENTU*)pMsg->data.buf;
	}
	else  pContent  =  (  IM_CONTENTU  *  )&pMsg->data;

	if  (  pContent->uiType  !=  CONST_imCommType_procOfflineRes  )  goto  errLabel;

	//  2015/06/05
	#ifdef  __DEBUG__
			traceLog((TCHAR*)  _T(  "dlgTalk_OnQyComm: get \"procOfflineRes\" from %I64u, bResp %d"  ),  pMsg->data.route.idInfo_from.ui64Id,  pContent->procOfflineResU.common.ucbResp  );
	#endif

	if  (  !(  isUcFlgRouteTalkData(  pMsg->ucFlg  )  
		//||  isUcFlgTalkData(  pMsg->ucFlg  )  
		)  
		)  
	{	
		goto  errLabel;								
	}
						
	//	
	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;		
	TALKER_shadow_mgr  *  pShadowMgr;
	pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;								
	if  (  !pShadowMgr  )  goto  errLabel;								
	//
	if  (  pContent->procOfflineResU.common.usSubtype  ==  CONST_procOfflineResSubtype_retrieve  )  {
		//
		if  (  !isUcFlgResp(  pMsg->ucFlg  )  )  {
			goto  errLabel;  
		}
		
		//
		PROC_offlineRes_mem  *  pMem;
		for  (  i  =  0;  i  <  mycountof(  pShadowMgr->procOfflineRes_mgr.mems  );  i  ++  )  {
			pMem  =  &pShadowMgr->procOfflineRes_mgr.mems[i];
			if  (  !IsWindow(  pMem->hTool_offlineRes  )  )  continue;
			if  (  pMem->uiTranNo_real  ==  pMsg->uiTranNo  )  break;
		}
		if  (  i  ==  mycountof(  pShadowMgr->procOfflineRes_mgr.mems  )  )  goto  errLabel;
		//
		SendMessage(  pMem->hTool_offlineRes,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );	

		//
		notifyProgressEnd(  &pQyMc->gui.progress,  pMem->uiTranNo_progress_tool,  0  );

		}
	else  if  (  pContent->procOfflineResU.common.usSubtype  ==  CONST_procOfflineResSubtype_download  )  {
			  //
			  #ifdef  __DEBUG__
					  traceLog((TCHAR*)  _T(  "dlgTalk_OnQyComm_msgInput_procOfflineRes: download %s"  ),  pContent->procOfflineResU.download.fileName  );
			  #endif
			  //
			  CHelp_getDlgTalkVar	help_getDlgTalkVar;				
			  //
			  TCHAR  tNameBuf[256]  =  _T(  ""  );

			  TCHAR  *  pName  =  (TCHAR*)_T(  "C:\\tttbbb\\upmostFromVlc.zip"  );//_T(  "C:\\Users\\t1650\\Documents\\qmFileServer\\113\\103_1.txt"  );
			  HWND  hMgr  =  hDlg;					  
			  //					  
			  //  procSendFile(  pName,  &pContent->procOfflineResU,  hMgr,  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hMgr  )  );
	  		  QY_MESSENGER_ID  idInfo_peer;
			  idInfo_peer.ui64Id  =  pContent->procOfflineResU.download.idInfo_logicalPeer.ui64Id;
			  if  (  !idInfo_peer.ui64Id  ) idInfo_peer.ui64Id  =  pMsg->data.route.idInfo_from.ui64Id;

			  getPath_fileServer(  pQyMc,  0,  &idInfo_peer,  tNameBuf, mycountof(  tNameBuf  )  );

			  //
			  char  filePrefix[128]  =  "";
			  if  (  getFilePrefix_fileServer(  pContent->procOfflineResU.download.tCreationTime,  filePrefix,  mycountof(  filePrefix  )  )  )  goto  errLabel;

			  //
			  _sntprintf(  tNameBuf, mycountof(  tNameBuf  ),  _T(  "%s\\%S_qm%I64u_%s"  ),  tNameBuf,  filePrefix,  pContent->procOfflineResU.download.idInfo_sender.ui64Id,  pContent->procOfflineResU.download.fileName  );  

			 //   getPath(  pMsg,  pContent,  tNameBuf,  mycountof(  tNameBuf  )  );  
			  procSendFile(  tNameBuf,  pContent->procOfflineResU.download.fileName,  &pContent->procOfflineResU,  hMgr,  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hMgr  ),  NULL  );

			  //
			  }
	else  if  (  pContent->procOfflineResU.common.usSubtype  ==  CONST_procOfflineResSubtype_del  )  {
			  if  (  !isUcFlgResp(  pMsg->ucFlg  )  )  {
				  goto  errLabel;  		
			  }
		
			  //
			  PROC_offlineRes_mem  *  pMem;
			  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->procOfflineRes_mgr.mems  );  i  ++  )  {
				   pMem  =  &pShadowMgr->procOfflineRes_mgr.mems[i];				   
				   if  (  !IsWindow(  pMem->hTool_offlineRes  )  )  continue;
				   if  (  pMem->uiTranNo_real  ==  pMsg->uiTranNo  )  break;		
			  }
			  if  (  i  ==  mycountof(  pShadowMgr->procOfflineRes_mgr.mems  )  )  goto  errLabel;		
			  //
			  SendMessage(  pMem->hTool_offlineRes,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );	
			  		
			  //		
			  notifyProgressEnd(  &pQyMc->gui.progress,  pMem->uiTranNo_progress_tool,  0  );

			  }
	else  {
			#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "dlgTalk_OnQyComm: procOfflineRes: subtype err"  )  );
		#endif
		goto  errLabel;		
	}


	iErr  =  0;
errLabel:
	return  iErr;
 }


 //
  int  dlgTalk_OnQyComm_wmParam_procOfflineRes(  HWND  hDlg,  void  *  pDLG_TALK_var,  WPARAM  wParam,  LPARAM  lParam  )
{
    int				iErr			=	-1;
	DLG_TALK_var	&	m_var			=	*(  DLG_TALK_var  *  )pDLG_TALK_var;
	QY_MC* pQyMc = m_var.pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	QY_WMBUF_COMM	*	pComm			=	(  QY_WMBUF_COMM  *  )lParam;
	TCHAR				tBuf[512]		=	_T(  ""  );
#ifndef  __WINCE__
#endif
	
	if  (  !pComm  )  return  -1;

	switch  (  pComm->uiType  )  {
			case  CONST_qyWmParam_procOfflineRes:  {

				  //
				  PROC_offlineRes_u  *  pReq  =  (  PROC_offlineRes_u  *  )pComm->u.procOfflineRes.pPROC_offlineRes_u;
				  QY_MESSENGER_ID  idInfo_req;  idInfo_req.ui64Id  =  pComm->u.procOfflineRes.ui64Id_req;
				  HWND  hTool  =  pReq->common.hTool_offlineRes;
				  unsigned  int  uiTranNo_wait  =  pComm->u.procOfflineRes.uiTranNo_wait;
				  //
				  TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
				  if  (  !pShadowMgr  )  goto  errLabel;
				  //
				  int  i;
				  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->procOfflineRes_mgr.mems  );  i  ++  )  {
					   PROC_offlineRes_mem  *  pMem  =  &pShadowMgr->procOfflineRes_mgr.mems[i];
					   if  (  pMem->hTool_offlineRes  ==  hTool  )  break;		
				  }
				  if  (  i  ==  mycountof(  pShadowMgr->procOfflineRes_mgr.mems  )  )  {
					  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->procOfflineRes_mgr.mems  );  i  ++  )  {
						   PROC_offlineRes_mem  *  pMem  =  &pShadowMgr->procOfflineRes_mgr.mems[i];
						   if  (  !IsWindow(  pMem->hTool_offlineRes  )  )  break;			
					  }
					  if  (  i  ==  mycountof(  pShadowMgr->procOfflineRes_mgr.mems  )  )  {
						  showInfo_open0(  0,  0,  _T(  "failed, too many offlineRes tools"  )  );
						  goto  errLabel;			
					  }			
					  PROC_offlineRes_mem  *  pMem  =  &pShadowMgr->procOfflineRes_mgr.mems[i];
					  memset(  pMem,  0,  sizeof(  pMem[0]  )  );
					  pMem->hTool_offlineRes  =  hTool;
					  pMem->idInfo_req.ui64Id  =  idInfo_req.ui64Id;
				  }
				  int  index_procOfflineRes_mem  =  i;				
				  PROC_offlineRes_mem  *  pMem  =  &pShadowMgr->procOfflineRes_mgr.mems[i];
				  //
				  if  (  pReq->common.usSubtype  ==  CONST_procOfflineResSubtype_retrieve  )  {
				  
					  //
					  pMem->uiTranNo_progress_tool  =  uiTranNo_wait;
					  //
					  unsigned  int  uiTranNo_real  =  0;
					  if  (  sndProcOfflineResToMsgr_qmc(  m_var.pMisCnt,  FALSE,  pReq,  &m_var.addr.idInfo,  &uiTranNo_real  )  )  {
						  goto  errLabel;
					  }
					  //
					  pMem->uiTranNo_real  =  uiTranNo_real;
					  break;
				  }
				  if  (  pReq->common.usSubtype  ==  CONST_procOfflineResSubtype_upload  )  {
					  CHelp_getDlgTalkVar	help_getDlgTalkVar;
					  //
					  TCHAR  *  pName  =  pReq->upload.fullFileName;
					  HWND  hMgr  =  hDlg;
					  //
					  TCHAR* finalName = mynull;
					  if (pProcInfo->bAppQt()) {
						  finalName = _tcsrchr(pName, _T('/'));
						  if (finalName != mynull) {
							  finalName++;
						  }

					  }
					  //
					  int  iTaskId  =  0;
					  procSendFile(  pName,  finalName,  pReq,  hMgr,  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hMgr  ),  &iTaskId  );
					  //
					  pComm->u.procOfflineRes.iTaskId  =  iTaskId;

					  break;												   
				  }
				  if  (  pReq->common.usSubtype  ==  CONST_procOfflineResSubtype_download  )  {
					  //
					  pMem->uiTranNo_progress_tool  =  uiTranNo_wait;
					  //
					  unsigned  int  uiTranNo_real  =  0;
					  if  (  sndProcOfflineResToMsgr_qmc(  m_var.pMisCnt,  FALSE,  pReq,  &m_var.addr.idInfo,  &uiTranNo_real  )  )  {
						  goto  errLabel;
					  }
					  //
					  pMem->uiTranNo_real  =  uiTranNo_real;
					  break;
				  }
				  if  (  pReq->common.usSubtype  ==  CONST_procOfflineResSubtype_del  )  {
					  //
					  pMem->uiTranNo_progress_tool  =  uiTranNo_wait;
					  //
					  unsigned  int  uiTranNo_real  =  0;
					  if  (  sndProcOfflineResToMsgr_qmc(  m_var.pMisCnt,  FALSE,  pReq,  &m_var.addr.idInfo,  &uiTranNo_real  )  )  {
						  goto  errLabel;
					  }
					  //
					  pMem->uiTranNo_real  =  uiTranNo_real;
					  //
					  pComm->u.procOfflineRes.uiTranNo_real  =  uiTranNo_real;
					  break;
				  }

				  //
				  }
				  break;
			default:
					break;
	}


	iErr  =  0;
errLabel:
	return  iErr;

  }



 //  2015/06/13
 int  dlgTalk_OnQyComm(  HWND  hDlg,  void  *  pDLG_TALK_var,  WPARAM  wParam,  LPARAM  lParam  )
{
	LONG				lRet			=	-1;
	if  (  !pDLG_TALK_var  )  return  -1;
	DLG_TALK_var	&	m_var			=	*(  DLG_TALK_var  *  )pDLG_TALK_var;
	QY_MC* pQyMc = m_var.pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	QY_WMBUF_COMM	*	pComm			=	(  QY_WMBUF_COMM  *  )lParam;
	TCHAR				tBuf[512]		=	_T(  ""  );
	
	//
	if  (  !pComm  )  return  -1;

	CQySyncFlg  syncFlg;

	//
	if  (  !m_var.guiData.bFinished_createCtrls  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "CDlgTalk::OnQyComm(  ) failed: bFinished_createCtrls is false, %I64u"  ),  m_var.addr.idInfo.ui64Id  );
		#endif
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::OnQyComm failed, bFinished_createCtrls false.%I64u"  ),  m_var.addr.idInfo.ui64Id  );
		goto  errLabel;
	}
	

	//  2015/06/13
	switch  (  pComm->uiType  )  {
			case  CONST_misMsgType_procVideo_qmc:  {
				   MIS_MSG_procVideo_qmc		*	pMsg			=  (  MIS_MSG_procVideo_qmc  *  )pComm;
				   //  2014/11/15
				   BOOL  bDone  =  FALSE;
				   PARAM_dlgTalk_procVideo  param;
				   //
				   if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
					   if  (  !pMsg->idInfo_peer.ui64Id  )  {
						   //
						   //  2014/12/25. 这里为什么用index_capImage_localVideoInMeImages这个变量呢，因为peer或者other都需要一个 zoneParam来存储index_capImg等信息。
						   //  因为localVideo需要重用，所以，专门增加了zoneParams_localOnPeer来存储。为了防止不同的本地视频之间干扰，就利用本地区的index_capImg来区分
						   //
						   switch  (  pMsg->uiCapType  )  {
								   case  CONST_capType_av:  {
									     BOOL  bNoPeer  =  TRUE;
										 //										 						
										 BOOL  tmp_bLocalVideoDisplayedOnPeer  =  pMsg->localOnPeer.bLocalVideoDisplayedOnPeer;
										 int  tmp_index_capImage_localVideoInMeImages  =  pMsg->localOnPeer.index_capImage_localVideoInMeImages;
										 unsigned  short  tmp_usIndex  =  pMsg->usIndex;
										 //
										 int  iIndex_av  =  0;
										 //
										 if  (  m_var.av.taskInfo.bTaskExists
											 &&  m_var.av.taskInfo.ucbVideoConference
											 &&  m_var.av.taskInfo.ucbStarter
											 &&  pMsg->iTaskId  ==  m_var.av.taskInfo.iTaskId  )
										 {
											 QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  m_var.av.taskInfo.iIndex_taskInfo  );
											 if  (  !pTaskInfo  )  goto  errLabel;
											 if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;
											 QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;
											 //
											 QY_MESSENGER_ID  idInfo_sender;
											 idInfo_sender.ui64Id  =  m_var.pMisCnt->idInfo.ui64Id;
											 if  (  isMemFromActive(  &pTc->videoConference,  &idInfo_sender,  mynull,  &iIndex_av  )  )  {
												 bNoPeer  =  FALSE;
											 }
										 }
										 //
										 memset(  &param,  0,  sizeof(  param  )  );
										 param.bNeed_index_capImage  =  TRUE;
										 //
										 pMsg->localOnPeer.bLocalVideoDisplayedOnPeer  =  FALSE;
										 pMsg->localOnPeer.index_capImage_localVideoInMeImages  =  0;
										 //  
										 //  2014/12/25
										 //  dlgTalk_procVideo(  hDlg,  m_var,  pMsg,  NULL  );
										 dlgTalk_procVideo(  hDlg,  &m_var,  pMsg,  &param  );
										 //
										 if  (  !bNoPeer  )  {											
											 pMsg->localOnPeer.bLocalVideoDisplayedOnPeer  =  TRUE;
											 pMsg->localOnPeer.index_capImage_localVideoInMeImages  =  param.index_capBmp;
											 pMsg->idInfo_sender.ui64Id  =  m_var.pMisCnt->idInfo.ui64Id;
											 pMsg->idInfo_peer.ui64Id  =  m_var.addr.idInfo.ui64Id;
											 pMsg->usIndex  =  iIndex_av;
											 dlgTalk_procVideo(  hDlg,  &m_var,  pMsg,  NULL  );
										 }
										 //
										 pMsg->localOnPeer.bLocalVideoDisplayedOnPeer  =  tmp_bLocalVideoDisplayedOnPeer;
										 pMsg->localOnPeer.index_capImage_localVideoInMeImages  =  tmp_index_capImage_localVideoInMeImages;
										 pMsg->idInfo_sender.ui64Id  =  0;
										 pMsg->idInfo_peer.ui64Id  =  0;
										 pMsg->usIndex  =  tmp_usIndex;
										 //
										 //  2014/11/29
										 unsigned  short  usIndex_av  =  0;
										 if  (  confStarter_bMeOnBgWall(  hDlg,  &m_var,  NULL,  &usIndex_av  )  )  {
											 pMsg->meOnBgWall.bMeDisplayedOnBgWall  =  TRUE;
											 pMsg->usIndex  =  usIndex_av;
											 dlgTalk_procVideo(  hDlg,  &m_var,  pMsg,  NULL  );
											 pMsg->meOnBgWall.bMeDisplayedOnBgWall  =  FALSE;
											 pMsg->usIndex  =  tmp_usIndex;
										 }
										 //
										 bDone  =  TRUE;
										 }									     
									     break;
								   case  CONST_capType_screen:
								   case  CONST_capType_mediaFile:
								   case  CONST_capType_mediaDevice:  {
									     BOOL  bNoPeer;  bNoPeer  =  FALSE;
										 //										
										 if  (  m_var.av.taskInfo.bTaskExists
											 &&  m_var.av.taskInfo.ucbVideoConference
											 &&  !m_var.av.taskInfo.ucbStarter  
											 &&  m_var.av.taskInfo.mosaicTrans.bExists_confMosaic  )
										 {
											 bNoPeer  =  TRUE;
										 }
										 //
										 if  (  m_var.av.taskInfo.bTaskExists
											 &&  !m_var.av.taskInfo.ucbVideoConference
											 &&  !m_var.av.taskInfo.ucbStarter  )
										 {
											 if  (  pMsg->uiCapType  ==  CONST_capType_screen  )  {
												 bNoPeer  =  TRUE;
											 }
										 }
										 //
										 BOOL  tmp_bLocalVideoDisplayedOnPeer  =  pMsg->localOnPeer.bLocalVideoDisplayedOnPeer;
										 int  tmp_index_capImage_localVideoInMeImages  =  pMsg->localOnPeer.index_capImage_localVideoInMeImages;
										 //
										 memset(  &param,  0,  sizeof(  param  )  );
										 param.bNeed_index_capImage  =  TRUE;
										 //
										 pMsg->localOnPeer.bLocalVideoDisplayedOnPeer  =  FALSE;
										 pMsg->localOnPeer.index_capImage_localVideoInMeImages  =  0;
										 dlgTalk_procVideo(  hDlg,  &m_var,  pMsg,  &param  );
										 //
										 if  (  !bNoPeer  )  {											
											 pMsg->localOnPeer.bLocalVideoDisplayedOnPeer  =  TRUE;
											 pMsg->localOnPeer.index_capImage_localVideoInMeImages  =  param.index_capBmp;
											 dlgTalk_procVideo(  hDlg,  &m_var,  pMsg,  NULL  );
										 }
										 //										 	
										 pMsg->localOnPeer.bLocalVideoDisplayedOnPeer  =  tmp_bLocalVideoDisplayedOnPeer;
										 pMsg->localOnPeer.index_capImage_localVideoInMeImages  =  tmp_index_capImage_localVideoInMeImages;
										 //
										 bDone  =  TRUE;
										 }
									     break;
								   default:
										   break;
						   }
					   }
				   }
				   //
				   if  (  !bDone  )  {
					   //
					   if  (  dlgTalk_procVideo(  hDlg,  &m_var,  pMsg,  NULL  )  )  goto  errLabel;
				   }
				   //
				   }

				   //
				   lRet  =  CONST_qyWmRc_ok;  goto  errLabel;

				   break;
		   				     			
			case  CONST_misMsgType_task:  {
				  MIS_MSG_TASK  *  pMsg  =  (  MIS_MSG_TASK  *  )pComm;
				  IM_CONTENTU  *  pContent  =  M_getMsgContent(  pMsg->ucFlg,  &pMsg->data  );
				  int  i;
				  //
				  switch  (  pContent->uiType  )  {

								//  2015/06/06
						  case  CONST_imCommType_ptzControlReq: {				//  2012/08/07			
							    if  (  !pContent->ptzControlReq.ucbReply  )  goto  errLabel;
								traceLog((TCHAR*)  _T(  "ptzControlReply"  )  );
								
								if  (  !pContent->ptzControlReq.usCnt  )  goto  errLabel;
								memcpy(  &m_var.ptzControl.cfg,  &pContent->ptzControlReq.mems[0],  sizeof(  m_var.ptzControl.cfg  )  );
								safeWcsnCpy(  pContent->ptzControlReq.u.reply.tHint,  m_var.ptzControl.tHint,  mycountof(  m_var.ptzControl.tHint  )  );
														  
								//
								notifyProgressEnd(  &pQyMc->gui.progress,  pContent->ptzControlReq.u.reply.uiTranNo_org,  0  );
													
								//			
								lRet  =  CONST_qyWmRc_ok;  goto  errLabel;

								}
								break;				  

						  default:
								 #ifdef  __DEBUG__
										  traceLogA(  (char*)  "dlgTalk::OnQyComm: unprocessed contentType %d",  pContent->uiType  );
								 #endif
								 break;
				  }
				  //
				  }
				  break;

			case  CONST_misMsgType_input:  {				
				  MIS_MSG_INPUT		*	pMsg		=   (  MIS_MSG_INPUT  *  )pComm;
				  IM_CONTENTU	*	pContent	=	NULL;
				  int					i;
				  //
				  if (isUcFlgRouteTalkData(pMsg->ucFlg) 
					  //|| isUcFlgTalkData(pMsg->ucFlg)
					  ) 
				  {
					  pContent = (IM_CONTENTU*)pMsg->data.buf;
				  }
				  else  pContent  =  (  IM_CONTENTU  *  )&pMsg->data;
				  //
				  switch  (  pContent->uiType  )  {

						  case  CONST_imCommType_retrieveDynBmps:	//  2014/05/06
								if  (  !(  isUcFlgRouteTalkData(  pMsg->ucFlg  )  
									//||  isUcFlgTalkData(  pMsg->ucFlg  )  
									)  )  
								{
									goto  errLabel;
								}
								//
								if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;
								TALKER_shadow_mgr  *  pShadowMgr;
								pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
								if  (  !pShadowMgr  )  goto  errLabel;
								//
								//  2015/06/05
								#ifdef  __DEBUG__
										traceLog((TCHAR*)  _T(  "dlgTalk_OnQyComm: get \"retrieveDynBmps\" from %I64u, bResp %d"  ),  pMsg->data.route.idInfo_from.ui64Id,  pContent->retrieveDynBmps.ucbResp  );
								#endif
								//
								//if  (  !isUcFlgResp(  pMsg->ucFlg  )  )  goto  errLabel;
								if  (  qPostMsg(  pMsg,  sizeof(  pMsg[0]  ),  m_var.m_pProcessQ,  _T(  "dlgTalk_Onqycomm"  )))  goto  errLabel;
								//  2014/09/05
								//
								if  (  pMsg->uiTranNo  ==  pShadowMgr->selectRemoteVideo.uiTranNo  )  {
									notifyProgressEnd(  &pQyMc->gui.progress,  pMsg->uiTranNo,  0  );
									break;
								}
								//									
								::PostMessage(  hDlg,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );

								//
								//
								lRet  =  CONST_qyWmRc_ok;  goto  errLabel;

							    break;

						  case  CONST_imCommType_procOfflineRes:  {  //  2015/08/03
							    //
								if  (  dlgTalk_OnQyComm_msgInput_procOfflineRes(  hDlg,  &m_var,  wParam,  lParam  )  )  goto  errLabel;
								
								//
								lRet  =  CONST_qyWmRc_ok;  goto  errLabel;

								}
							    break;
						  case  CONST_imCommType_confReq:
							    //
							    if (isUcFlgResp(pMsg->ucFlg)) {
									int ii = 0;
									//
									if (!isTalkerShadowMgr(m_var.addr)
										&&  m_var.iTalkerSubType  ==  0  )  
									{
										

									}

							    }
							    //
							    break;
						  case  CONST_imCommType_taskInteractionReq:
							    //
							    if (isUcFlgResp(pMsg->ucFlg)) {
									traceLog((TCHAR*)_T("dlgTalk_OnQyCommm: taskInteractionResp, from %I64u: ucStep %d"), pMsg->data.route.idInfo_from.ui64Id,  (int)pContent->taskInteractionReq.ucStep);
							  
								}
							    //
								break;

						  default:
								  #ifdef  __DEBUG__
										  //traceLogA(  (char*)  "dlgTalk::OnQyComm: unprocessed contentType %d",  pContent->uiType  );
								  #endif
								  break;
				  }
				 
				  }

				  break;


				   
			default:
					   break;					   
	}

	//
	if  (  10  )
	{
		if  (  syncFlg.sync(  &m_var.syncFlgs.bInSequence  )  )  {				
			
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_OnQyComm failed, bLocked already, uiType is %d"  ),  pComm->uiType  );
			//
			goto  errLabel;										
		}
	}


	//
	switch  (  pComm->uiType  )  {
					 
			  
			case  CONST_qyWmParam_activateImTask:
				  #ifndef  __WINCE__
						   activateImTask(  hDlg,  &m_var,  pComm->u.activateImTask.iTaskId_activated  );
				  #endif
				  break;
			case  CONST_misMsgType_taskStatus:  {
				  MIS_MSG_TASKSTATUS		*		pMsgTaskStatus								=	(  MIS_MSG_TASKSTATUS  *  )pComm;			//  ÓÐÊ±¾ÍÓÃÕâ¸ö½á¹¹£¬ 2007/07/17
				  MIS_MSG_TASK				*		pMsgTask									=	NULL;
				  IM_CONTENTU				*		pContent									=	NULL;  
				  int								nItem;
				  PARAM_PROC_ROW					param;
				  MIS_MSG_imMsgRcd					msgImMsgRcd;
				  int								tmpiRet;
				  //
				  if  (  pMsgTaskStatus->iStatus  ==  CONST_imTaskStatus_err_missingOrgReq  )  {
					  //
					  if (pProcInfo->bAppQt()) {
						  pMsgTaskStatus->ucbNeeded_applyForOrgReq = TRUE;
						  //
						  _sntprintf(tBuf, mycountof(tBuf), _T("qt: dlgTalk_OnQyComm %I64u: need apply for org req"), m_var.addr.idInfo.ui64Id);
						  showInfo_open0(0, 0, tBuf);
						  //
						  break;
					  }
					  //
					  #if  0
							if  (  m_var.av.taskInfo.bTaskExists  )  break;
							if  (  m_var.addr.uiObjType  !=  CONST_objType_imGrp  )  break;					  
					  #endif
					  if  (  pMsgTaskStatus->uiContentType  ==  CONST_imCommType_transferAudioData  
						  ||  pMsgTaskStatus->uiContentType  ==  CONST_imCommType_transferVideoData  )  
					  {
						  //  2016/02/17
						  PARAM_findTaskAvOrgReq  param_findTaskAvOrgReq;
						  memset(  &param_findTaskAvOrgReq,  0,  sizeof(  param_findTaskAvOrgReq  )  );
						  //
						  tmpiRet  =  qTraverse(  m_var.m_pProcessQ,  tmpHandler_findTaskAvOrgReq,  pMsgTaskStatus,  &param_findTaskAvOrgReq  );
						  if  (  tmpiRet  <  0  )  goto  errLabel;
						  if  (  tmpiRet  )  {

							  #ifdef  __DEBUG__
									  //traceLog((TCHAR*)  _T(  "dlgTalk::OnQyComm: taskAvOrgReq found. iStatus %d"  ),  param_findTaskAvOrgReq.iStatus_o  );
							  #endif
							  //  2014/11/21
							  pMsgTaskStatus->ucbFound  =  TRUE;
							  pMsgTaskStatus->idInfo_logicalPeer.ui64Id  =  m_var.addr.idInfo.ui64Id;
							  
							  //  2014/07/30
							  if  (  param_findTaskAvOrgReq.iStatus_o  ==  CONST_imTaskStatus_autoCanceledByReceiver  )  {
								  pMsgTaskStatus->ucbNeeded_applyForOrgReq  =  TRUE;
								  //
								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "dlgTalk_OnQyComm %I64u: taskAvOrgReq found. autoCanceledByReceiver, need apply for org req"  ),  m_var.addr.idInfo.ui64Id  );
								  showInfo_open0(  0,  0,  tBuf  );
								  }
							  else  if (1) {
								  pMsgTaskStatus->ucbNeeded_applyForOrgReq = TRUE;
								  //
								  _sntprintf(tBuf, mycountof(tBuf), _T("dlgTalk_OnQyComm %I64u: taskAvOrgReq found. need apply for org req"), m_var.addr.idInfo.ui64Id);
								  showInfo_open0(0, 0, tBuf);
							  }
							  else  {  //  2015/10/08
								    //  2016/05/09
								    if  (  bTaskAlive(  param_findTaskAvOrgReq.iStatus_o  )  )  {
										if  (  param_findTaskAvOrgReq.uiTaskType  ==  CONST_imTaskType_transferAvInfo  )  {
											if  (  !m_var.av.taskInfo.bTaskExists  )  {
												m_var.autoAnswer.bTaskExists  =  TRUE;
												//
												_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "dlgTalk_OnQyComm %I64u: taskAvOrgReq found. %s. transferAvInfo. no active avTask. auto answer"  ),  m_var.addr.idInfo.ui64Id,  qyGetDesByType1(  CONST_qyStatusTable_en,  param_findTaskAvOrgReq.iStatus_o  )  );
												showInfo_open0(  0,  0,  tBuf  );
												//
												break;
											}
										}
									}

								    //
								    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "dlgTalk_OnQyComm %I64u: taskAvOrgReq found. %s. do nothing"  ),  m_var.addr.idInfo.ui64Id,  qyGetDesByType1(  CONST_qyStatusTable_en,  param_findTaskAvOrgReq.iStatus_o  )  );
								    showInfo_open0(  0,  0,  tBuf  );
									
									//
									if  (  !bTaskAlive(  param_findTaskAvOrgReq.iStatus_o  )  )  {
										if  (  !m_var.av.taskInfo.bTaskExists  )  {
											if  (  param_findTaskAvOrgReq.uiTaskType  !=  CONST_imTaskType_transferAvInfo  )  {
												showInfo_open0(  0,  0,  _T(  "taskType err: not av. "  )  );
												}
											else  {
												  m_var.guiData.av.canceledTask_av.iTaskId  =  param_findTaskAvOrgReq.iTaskId;
												  m_var.guiData.av.canceledTask_av.iStatus  =  param_findTaskAvOrgReq.iStatus_o;
												  m_var.guiData.av.canceledTask_av.dwTickCnt_recentlyRefreshed  =  GetTickCount(  );
												  //
												  //  2017/09/14. 这里不让SHADOW最小化的原因是，当会议呼叫时，由于最小化和取消会议，导致用户无法察觉被呼叫的状态。
												  DWORD  dwTickCnt  =  GetTickCount(  );
												  int  iDiffInMs  =  dwTickCnt  -  m_var.guiData.av.canceledTask_av.dwTickCnt_chkShadowIconic;
												  if  (  abs(  iDiffInMs  )  >  3000  )  {
													  m_var.guiData.av.canceledTask_av.dwTickCnt_chkShadowIconic  =  dwTickCnt;
													  //
													  if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
														  TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
														  if  (  !pShadowMgr  )  goto  errLabel;
														  int  i;
														  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
															   TALKER_shadow_mgrMem  *  pShadow  =  &pShadowMgr->shadows[i];
															   if  (  !IsWindow(  pShadow->hShadow  )  )  continue;
															   if  (  isTalkerSubtype_canInput(  pShadow->iTalkerSubType  )  )  {
																   if  (  IsIconic(  pShadow->hShadow  )  )  {
																	   PostMessage(  pShadow->hShadow,  WM_SYSCOMMAND,  SC_RESTORE,  0  );
																	   break;
																   }
															   }
														  }
													  }
												  }
											}
											//
											}
										else  { 
											  showInfo_open0(  0,  0,  _T(  "Note: task waits to be re-accepted"  )  );
											  //
#if  0
											  m_var.guiData.av.canceledTask_screenOrMediaFile.iTaskId  =  param_findTaskAvOrgReq.iTaskId;
											  m_var.guiData.av.canceledTask_screenOrMediaFile.uiTaskType  =  param_findTaskAvOrgReq.uiTaskType;
											  m_var.guiData.av.canceledTask_screenOrMediaFile.iStatus  =  param_findTaskAvOrgReq.iStatus_o;
											  m_var.guiData.av.canceledTask_screenOrMediaFile.dwTickCnt_recentlyRefreshed  =  GetTickCount(  );
#endif
											  //
											  MIS_MSG_TASK  *  pMsgTask  =  findTaskInProcessQ(  &m_var,  param_findTaskAvOrgReq.iTaskId  );
											  if  (  pMsgTask  )  {
												  IM_CONTENTU  *  pContent  =  M_getMsgContent(  pMsgTask->ucFlg,  &pMsgTask->data  );
												  if  (  pContent
													  &&  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  
												  {
#if  0
													  PROC_TASK_AV  *  pTask  =  get_transferAvInfo_pTask(  &pContent->transferAvInfo,  _T(  ""  )  );
													  if  (  !pTask  )  goto  errLabel;
													  //
													  pTask->canceledTask_status.dwTickCnt_recentlyRefreshed  =  GetTickCount(  );
													  //
													  if  (  !pTask->canceledTask_status.bWaitingTo_beRe_accepted  )  {
														  pTask->canceledTask_status.bWaitingTo_beRe_accepted  =  TRUE;
													  }
													  //
													  D3D_talkerData_cfg  *  pDtc  =  &m_var.d3d_talkerData_cfg;
													  int  i;
													  for  (  i  =  0;  i  <  pDtc->taskList.usCnt;  i  ++  )  {
														   TASK_list_mem  *  pTlm  =  &pDtc->taskList.mems[i];
														   if  (  pTlm->iTaskId  ==  param_findTaskAvOrgReq.iTaskId  )  break;
													  }
													  if  (  i  ==  pDtc->taskList.usCnt  )  {
														  dyn_d3dWall_refreshWallMemByTalker(  hDlg  );
													  }
													  //
													  if  (  !m_var.guiData.av.canceledTask_screenOrMediaFile.bTaskExists_waitingTo_beRe_accepted  )  {
														  m_var.guiData.av.canceledTask_screenOrMediaFile.bTaskExists_waitingTo_beRe_accepted  =  TRUE;
														  dyn_d3dWall_askToRefreshIa(  );
													  }
#endif
												  }
											  }
										}
									}

							  }

							  //
							  break;
						  }

						  //
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "dlgTalk_OnQyComm %I64u: taskAvOrgReq not found. need apply for org req"  ),  m_var.addr.idInfo.ui64Id  );
						  #ifdef  __DEBUG__
								  traceLog((TCHAR*)  tBuf  );
						  #endif
						  showInfo_open0(  0,  0,  tBuf  );
						  //
						  pMsgTaskStatus->ucbNeeded_applyForOrgReq  =  TRUE;
						  
					  }
					  //
					  break;
				  }
				  else if  (  pMsgTaskStatus->iStatus  ==  CONST_imTaskStatus_canceledByReceiver  )  {
						   int  ii  =0;
				  }

				  //
				  dlgTalk_qPostMsg(  hDlg,  pMsgTaskStatus,  sizeof(  pMsgTaskStatus[0]  )  );	//  2011/03/10.将可能改变任务状态的消息都要用postMsg的方式，发送到processQ.在那边统一顺序处理，有利于同步
				  ::PostMessage(  hDlg,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
									 
				  //
				  }				  				  
				  break;
			case  CONST_misMsgType_task:  {
				  MIS_MSG_TASK  *  pMsg  =  (  MIS_MSG_TASK  *  )pComm;
				  IM_CONTENTU  *  pContent  =  M_getMsgContent(  pMsg->ucFlg,  &pMsg->data  );
				  int  i;
				  //
				  switch  (  pContent->uiType  )  {
						  case  CONST_imCommType_transferAvInfo:
							    if  (  pMsg->uiTaskType  !=  CONST_imTaskType_viewDynBmp  )  goto  errLabel;
								if  (  !pContent->transferAvInfo.idInfo_logicalPeer.ui64Id  )  goto  errLabel;
								//
								//confMem_procReq_transferAvInfo(  hDlg,  &m_var,  (  MIS_MSGU  *  )pMsg  );
								if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;
								if  (  !m_var.av.taskInfo.bTaskExists  )  goto  errLabel;
								if  (  m_var.av.taskInfo.ucbStarter  )  goto  errLabel;
								if  (  !m_var.av.ucbGot_iIndex_sharedObj_localAv  )  goto  errLabel;
								confMem_procReq_transferAvInfo(  hDlg,  m_var.av.iIndex_sharedObj_localAv,  (  MIS_MSGU  *  )pMsg  );
								
								//
							    break;

						  default:
								 #ifdef  __DEBUG__
										  traceLogA(  (char*)  "dlgTalk::OnQyComm: unprocessed contentType %d",  pContent->uiType  );
								 #endif
								 break;
				  }
				  //
				  }
				  break;
			case  CONST_misMsgType_input:  {
				  MIS_MSG_INPUT		*	pMsg		=   (  MIS_MSG_INPUT  *  )pComm;
				  IM_CONTENTU	*	pContent	=	NULL;
				  int					i;
				  //
				  if (isUcFlgRouteTalkData(pMsg->ucFlg) 
					  //|| isUcFlgTalkData(pMsg->ucFlg)
					  ) 
				  {
					  pContent = (IM_CONTENTU*)pMsg->data.buf;
				  }
				  else  pContent  =  (  IM_CONTENTU  *  )&pMsg->data;
				  //
				  switch  (  pContent->uiType  )  {
						  case  CONST_imCommType_refreshWebContactsInfo:
							    WEB_CONTACT_STATUS  *	pMem;
								unsigned  short			usRunningStatus;
								TCHAR					tBuf1[256];
								//
								if  (  !m_var.ucbGuest  )  goto  errLabel;	//  ½ö¶Ô·Ã¿ÍÓÐÓÃ¡£
								//
							    for  (  i  =  0;  i  <  pContent->refreshWebContactsInfo.usCnt;  i  ++  )  {
									 pMem  =  &pContent->refreshWebContactsInfo.mems[i];
									 if  (  pMem->idInfo.ui64Id  !=  m_var.addr.idInfo.ui64Id  )  continue;
									 //
									 usRunningStatus  =  (  pMem->usRunningStatus  ==  CONST_usRunningStatus_online  )  ?  CONST_usRunningStatus_online  :  CONST_usRunningStatus_offline;
									 //
									 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s - %s - %s"  ),  m_var.talkerDesc,  pMem->wLocation,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_usRunningStatusTable  ),  usRunningStatus  )  );
									 GetWindowText(  hDlg,  tBuf1,  mycountof(  tBuf1  )  );
									 if  (  lstrcmpi(  tBuf1,  tBuf  )  )  {	
										 SetWindowText(  hDlg,  tBuf  );									 
										 //
										 activateWnd(  hDlg,  m_var  );		//  ÌâÍ·±ä»¯ÁËÒ²Ó¦¸ÃÉÁÁÁ										 
									 }
								}
							    break;
						  case  CONST_imCommType_taskProcReq:
							    if  (  pContent->taskProcReq.usOp  ==  CONST_imOp_recv_applyForOrgReq  )  {
									CQyMalloc  malloc_pMsgTask_o;
									int  size  =  sizeof(  MIS_MSG_TASK  );
									MIS_MSG_TASK  *  pMsgTask_o  =  (  MIS_MSG_TASK  *  )malloc_pMsgTask_o.mallocf(  size  );
									if  (  !pMsgTask_o  )  goto  errLabel;
									MACRO_memset_misMsgTask(  pMsgTask_o  );

									MIS_MSG_TASK	*	pMsgTask_i  =  findTaskInProcessQ(  &m_var,  pMsg->iTaskId  );
									if  (  !pMsgTask_i  )  goto  errLabel;
									IM_CONTENTU		*	pContentTask_i	=	(  IM_CONTENTU  *  )pMsgTask_i->data.buf;
									if  (  pContentTask_i->uiType  !=  CONST_imCommType_transferAvInfo  )  goto  errLabel;
									//
									if  (  1  )  {	//  2012/05/25
										BOOL  bPermitted  =  FALSE;
										#ifdef  __DEBUG__
												if  (  pProcInfo->cfg.debugStatusInfo.bDbgDetail){
													traceLog((TCHAR*)  _T(  "recvd applyForOrgReq. to check whether the from is a valid user. %I64u"  ),  pMsg->data.route.idInfo_from.ui64Id  );
												}
										#endif

										if  (  m_var.addr.uiObjType  ==  CONST_objType_imGrp  )  {
											if  (  pQyMc->appParams.bConfServer  )  {
												bPermitted  =  TRUE;
												}
											else  {
												  //  要检查是否是组成员											
												  BOOL  bVal  =  FALSE;
												  if  (  !getVal_bImGrpMem(  pQyMc, &m_var.addr.idInfo,  &pMsg->data.route.idInfo_from,  &bVal  )  											
													  &&  bVal  )  																							
												  {												
													  bPermitted  =  TRUE;																						
												  }
											}
											//
											}
										else  {
											  if  (  pMsg->data.route.idInfo_from.ui64Id  ==  m_var.addr.idInfo.ui64Id  )  {
												  bPermitted  =  TRUE;
											  }
										}
										//
										if  (  !bPermitted  )  {
  										    #ifdef  __DEBUG__
												  traceLog((TCHAR*)  _T(  "applyForOrgReq denied. Not a valid user."  )  );
										    #endif											
											goto  errLabel;
										}
									}
								    //
									PARAM_findOrgMsg  param;
									memset(  &param,  0,  sizeof(  param  )  );
									param.pMsgTask_o  =  pMsgTask_o;
									if  (  pProcInfo->processQ_media.qTraverse(  tmpHandler_findOrgMsgAndProc_is,  pMsgTask_i,  &param  )  <=  0  )  {	
										#ifdef  __DEBUG__
												traceLogA(  (char*)  "dlgTalk_OnQyComm: taskProcReq: applyForOrgReq failed."  );				  
										#endif
										goto  errLabel;
									}

									if  (  pMsgTask_o->uiType  !=  CONST_misMsgType_task  )  {
										#ifdef  __DEBUG__
												traceLogA(  (char*)  "dlgTalk_OnQyComm: taskProcReq: applyForOrgReq failed. msg.type %d err",  pMsgTask_o->uiType  );				  
										#endif
										goto  errLabel;
									}
									IM_CONTENTU		*	pContentTask_o	=	(  IM_CONTENTU  *  )pMsgTask_o->data.buf;
									if  (  pContentTask_o->uiType  !=  CONST_imCommType_transferAvInfo  )  goto  errLabel;

									//
#if  0
									if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
										if  (  m_var.av.taskInfo.bTaskExists
											&&  m_var.av.taskInfo.iTaskId  ==  pMsg->iTaskId  )  
										{
											//getVideoConferenceStatus(  hDlg,  pMsg->iTaskId,  &pContentTask_o->transferAvInfo.videoConferenceStatus,  _T(  "dlgtalk_onQyComm"  )  );
										}
									}
#endif


									//
									#ifdef  __DEBUG__
											if  (  pProcInfo->cfg.debugStatusInfo.bDbgDetail){
												traceLogA(  (char*)  "dlgTalk_OnQyComm: send transferAvInfo again."  );				  
											}
									#endif
									//
									int  lenInBytes  =  pMsgTask_o->lenInBytes  -  offsetof(  MIS_MSG_routeTalkData,  buf  );
									if  (  lenInBytes  <  0  )  goto  errLabel;
									//
									QY_MESSENGER_ID	idInfo_dst;
									idInfo_dst.ui64Id  =  pMsg->data.route.idInfo_from.ui64Id;
									//  set idInfo_logicalPeer temporiary.
									if  (  m_var.addr.idInfo.ui64Id  !=  idInfo_dst.ui64Id  )  
									{
										pContentTask_o->transferAvInfo.idInfo_logicalPeer.ui64Id  =  m_var.addr.idInfo.ui64Id;
									}
									postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_outputTask,  0,  pMsgTask_o->usCode,  pMsgTask_o->tStartTime,  pMsgTask_o->uiTranNo,  0,  pMsgTask_o->iTaskId,  pMsgTask_o->uiTaskType,  (  char  *  )pMsgTask_o->data.buf,  lenInBytes,  &m_var.addr.idInfo,  &pMsgTask_o->idInfo_taskSender,  &pMsgTask_o->idInfo_taskReceiver,  &idInfo_dst,  0,  NULL,  FALSE  );
									//pContentTask_o->transferAvInfo.idInfo_logicalPeer.ui64Id  =  0;

									//
									if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
										if  (  m_var.av.taskInfo.bTaskExists
											&&  m_var.av.taskInfo.iTaskId  ==  pMsg->iTaskId  )  
										{
											pProcInfo->sendConfKey(  hDlg,  idInfo_dst,  _T(  "send orgReq"  )  );
										}
									}

									//
									_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "talker%I64u.onQyComm: send transferAvInfo again to %I64u. a_tn %d, v_tn %d"  ),  m_var.addr.idInfo.ui64Id,  idInfo_dst.ui64Id,  pContentTask_o->transferAvInfo.ass.tranInfo.audio.uiTranNo_openAvDev,  pContentTask_o->transferAvInfo.ass.tranInfo.video.uiTranNo_openAvDev  );
									showInfo_open0(  0,  0,  tBuf  );
									//
									break;
							    }
								//  2014/10/09
								if  (  pContent->taskProcReq.usOp  ==  CONST_imOp_stopSending  
									||  pContent->taskProcReq.usOp  ==  CONST_imOp_requestToSend  )
								{
									if  (  !m_var.av.taskInfo.bTaskExists  )  goto  errLabel;
									if  (  !m_var.av.ucbGot_iIndex_sharedObj_localAv  )  goto  errLabel;
									QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv  );
									if  (  !pSharedObj  )  goto  errLabel;
									if  (  pSharedObj->bSlave  )  goto  errLabel;
									SHARE_dyn_bmp  *  pDynBmpMem  =  (  SHARE_dyn_bmp  *  )pSharedObj->master.pShareDynBmp_slave;
									if  (  !pDynBmpMem  )  goto  errLabel;

									if  (  pDynBmpMem->resObj.uiObjType  !=  pContent->taskProcReq.viewDynBmp.ros.uiObjType
										||  pDynBmpMem->resObj.usIndex_obj  !=  pContent->taskProcReq.viewDynBmp.ros.usIndex_obj  )
									{
										goto  errLabel;
									}

									//
									int  index_taskInfo_slave  =  getQmcTaskInfoIndexBySth(  pProcInfo,  pDynBmpMem->var.iTaskId  );
									QMC_TASK_INFO  *  pTaskInfo_slave  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  index_taskInfo_slave  );
									if  (  !pTaskInfo_slave  )  goto  errLabel;

									//
									QY_SHARED_OBJ  *  pSharedObj_slave  =  getSharedObjByIndex(  pProcInfo,  pSharedObj->master.slaveKey.iIndex_sharedObj  );
									if  (  !pSharedObj_slave  )  goto  errLabel;
									if  (  !pSharedObj_slave->bUsed  )  goto  errLabel;
									if  (  !pSharedObj_slave->bSlave  )  goto  errLabel;
									if  (  pSharedObj_slave->uiTranNo  !=  pSharedObj->master.slaveKey.uiTranNo  )  goto  errLabel;

									if  (  pContent->taskProcReq.usOp  ==  CONST_imOp_stopSending  )  {
										removeFromMsgrs_sendLocalAv(  pProcInfo,  m_var.pMisCnt,  &pMsg->data.route.idInfo_from,  &pTaskInfo_slave->var.curRoute_sendLocalAv,false,  _T(  "dlgTalk_OnQyComm:taskProcReq.stopSending"  ));
										qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_OnQyComm: slave: removeFromMsgrs_sendLocalAv, %I64u"  ),  pMsg->data.route.idInfo_from  );
									}

									break;
								}
							    break;
						  case  CONST_imCommType_taskProcResp:
							    if  (  pContent->taskProcResp.usOp_org  ==  CONST_imOp_recv_applyForChkTaskAlive  )  {
									Q_NODE		*	pQNode;
									MIS_MSGU	*	pMsg;
									
									if  (  !m_var.m_pProcessQ  )  goto  errLabel;

									for  (  pQNode  =  m_var.m_pProcessQ->front.pNext;  pQNode;  pQNode  =  pQNode->pNext  )  {
										 pMsg  =  (  MIS_MSGU  *  )pQNode->qElemMemory.m_pBuf;
										 if  (  pMsg->uiType  !=  CONST_misMsgType_task  )  continue;
										 if  (  pMsg->task.tStartTime  ==  pContent->taskProcResp.tStartTime_org
											 &&  pMsg->task.uiTranNo  ==  pContent->taskProcResp.uiTranNo_org  )
										 {
											 if  (  bTaskAlive(  pContent->taskProcResp.iStatus  )  )  {
												 //
												 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "talker%I64u: resp recvd, task %d is alive"  ),  m_var.addr.idInfo.ui64Id,  pMsg->task.iTaskId  );
												 showInfo_open0(  0,  0,  tBuf  );
												 #ifdef  __DEBUG__
														 traceLog((TCHAR*)  tBuf  );
												 #endif
												 //
												 //  mytime(  &pMsg->task.tStartTime_processed  );
												 mytime(  &pMsg->task.tTime_alive  );	//  2014/12/09
											 }
											 break;
										 }
									}
								}
							    break;
#if  0  //  2015/06/14
						  case  CONST_imCommType_retrieveDynBmps:	//  2014/05/06
								if  (  !(  isUcFlgRouteTalkData(  pMsg->ucFlg  )  ||  isUcFlgTalkData(  pMsg->ucFlg  )  )  )  {
									goto  errLabel;
								}
								//
								if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;
								TALKER_shadow_mgr  *  pShadowMgr;
								pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
								if  (  !pShadowMgr  )  goto  errLabel;
								//
								//  2015/06/05
								#ifdef  __DEBUG__
										traceLog((TCHAR*)  _T(  "dlgTalk_OnQyComm: get \"retrieveDynBmps\" from %I64u, bResp %d"  ),  pMsg->data.route.idInfo_from.ui64Id,  pContent->retrieveDynBmps.ucbResp  );
								#endif
								//
								//if  (  !isUcFlgResp(  pMsg->ucFlg  )  )  goto  errLabel;
								if  (  qPostMsg(  pMsg,  sizeof(  pMsg[0]  ),  m_var.m_pProcessQ  )  )  goto  errLabel;
								//  2014/09/05
								//
								if  (  pMsg->uiTranNo  ==  pShadowMgr->selectRemoteVideo.uiTranNo  )  {
									notifyProgressEnd(  pMsg->uiTranNo,  0  );
									break;
								}
								//									
								::PostMessage(  hDlg,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
							    break;
#endif
						  case  CONST_imCommType_htmlContent:	//  2014/07/12
								if  (  !(  isUcFlgRouteTalkData(  pMsg->ucFlg  )  
									//||  isUcFlgTalkData(  pMsg->ucFlg  )  
									)  )  
								{
									goto  errLabel;
								}
								if  (  !isUcFlgResp(  pMsg->ucFlg  )  )  goto  errLabel;
								//
								#ifdef  __DEBUG__
										traceLog((TCHAR*)  _T(  "resp of html from %I64u"  ),  pMsg->data.route.idInfo_from.ui64Id  );
								#endif

								//
								if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;
								qTraverse(  m_var.m_pProcessQ,  (  PF_commonHandler  )tmpHandler_procHtmlResp,  hDlg,  pMsg  );

							    break;
						  default:
								  #ifdef  __DEBUG__
										  traceLogA(  (char*)  "dlgTalk::OnQyComm: unprocessed contentType %d",  pContent->uiType  );
								  #endif
								  break;
				  }

				  }
				  break;
			case  CONST_misMsgType_refreshContactsStatus_qmc:  {
				   MIS_MSG_REFRESHCONTACTSSTATUS_QMC  *  pMsg  =  (  MIS_MSG_REFRESHCONTACTSSTATUS_QMC  *  )pComm;
				   //
				   bRefreshContactsStatus_wnd(  pMsg,  &m_var.displayCtx,  tmpHandler_bRefreshContactsStatus_dlgTalk,  hDlg  ); 				   
				   }
				   break;
			 case  CONST_misMsgType_refreshMeStatus_qmc:  {
				   MIS_MSG_REFRESHMESTATUS_QMC  *  pMsg  =  (  MIS_MSG_REFRESHMESTATUS_QMC  *  )pComm;
				   //
				   bRefreshMeStatus_wnd(  pMsg,  &m_var.displayCtx,  tmpHandler_bRefreshContactsStatus_dlgTalk,  hDlg  );				
				   }
				   break;

			 case  CONST_qyWmParam_getnCol:  {
				#ifndef  __WINCE__
				   LVCOLUMN		column;
				   int			i;


				   HWND				hListCtrl		=	NULL;	//  GetDlgItem(  hDlg,  m_var.msgToolCommon.idcList_task  );


				   //  if  (  pComm->u.getnCol.hList  )  pListCtrl  =  (  CListCtrl  *  )CListCtrl::FromHandle(  pComm->u.getnCol.hList  );
				   //  if  (  !pListCtrl  )  goto  errLabel;
				   if  (  pComm->u.getnCol.hList  )  
					   hListCtrl  =  pComm->u.getnCol.hList;
				   if  (  !hListCtrl  )  goto  errLabel;

				   memset(  &column,  0,  sizeof(  column  )  );
				   column.mask  =  LVCF_TEXT;
				   column.pszText  =  tBuf;
				   column.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				   for  (  i  =  0;  ;  i  ++  )  {
					    //  if  (  !pListCtrl->GetColumn( i,  &column  )  )  
					    if  (  !myListCtrl_GetColumn( hListCtrl,  i,  &column  )  )
						{
							traceLogA(  (char*)  "dlgTalk_OnQyComm: getnCol failed",  pComm->u.getnCol.colName  );  
							goto  errLabel;					   
						}					   
						if  (  !lstrcmpi(  tBuf,  pComm->u.getnCol.colName  )  )  break;
				   }
				   pComm->u.getnCol.nCol  =  i;
				#endif
				   }
				   break;
	   	

			case  CONST_misMsgType_notifyTaskEnd_qmc:  {
				  MIS_MSG_notifyTaskEnd_qmc	*	pMsg  =  (  MIS_MSG_notifyTaskEnd_qmc  *  )pComm;

				  dlgTalk_qPostMsg(  hDlg,  pMsg,  sizeof(  pMsg[0]  )  );	//  2011/03/10.将可能改变任务状态的消息都要用postMsg的方式，发送到processQ.在那边统一顺序处理，有利于同步
				  ::PostMessage(  hDlg,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );

#if  0
				  MIS_MSG_notifyTaskEnd_qmc	*	pMsg  =  (  MIS_MSG_notifyTaskEnd_qmc  *  )pComm;
				  if  (  pMsg->bToCancel  )  {
					  if  (  !pMsg->iTaskId  )  {
						  traceLogA(  (char*)  "iTaskId error"  );
						  goto  errLabel;
					  }
					  dlgTalk_cancelTasks(  hDlg,  m_var,  pMsg->iTaskId  );
					  break;
				  }
				  //  freeCapImageByTaskId(  hDlg,  m_var.av.idc_meDesc,  pMsg->iTaskId,  &m_var.av.meImages  );  
				  freeCapImageByTaskId(  hDlg,  0,  pMsg->iTaskId,  &m_var.av.meImages  );  
#endif

				  }
				  break;

			case  CONST_qyWmParam_chkTask:
				  if  (  dlgTalk_toChkTask(  hDlg,  m_var,  pComm  )  )  goto  errLabel;
				  break;
			case  CONST_qyWmParam_chkSharedObject:		//  2014/11/30
				  if  (  dlgTalk_toChkSharedObj(  hDlg,  m_var,  pComm  )  )  goto  errLabel;
				  break;

			case  CONST_qyWmParam_requestToSpeak:  {		//  2010/09/02
				  if  (  !m_var.av.taskInfo.bTaskExists  )  break;
				  //
				  if  (  !pComm->u.requestToSpeak.bManager  &&  pComm->u.requestToSpeak.uiCmd  ==  ID_stopSpeaking  )  {
					  dlgTalk_requestToSpeak(  hDlg,  FALSE  );
				  }
				  }
				  break;

			  	
			case  CONST_misMsgType_applyForTalkerShadow_qmc:  {	//  2012/04/23
				  MIS_MSG_applyForTalkerShadow_qmc	*	pMsg  =  (  MIS_MSG_applyForTalkerShadow_qmc  *  )lParam;
				  //
				  if  (  isTalkerShadowMgr(  m_var.addr  )  )  {		//  这里的处理是影子窗口的放大窗口或者变幻窗口
					  goto  errLabel;
				  }
				  TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
				  if  (  !pTalkerShadow  )  goto  errLabel;

				  if  (  !IsWindow(  pTalkerShadow->hEnlargedWnd  )  )  {
					  pTalkerShadow->hEnlargedWnd  =  pMsg->hShadow;
					  MACRO_SetForegroundWindow(  pTalkerShadow->hEnlargedWnd  );
				  }

				  }	
				  break;

			case  CONST_qyWmParam_procOfflineRes:  {  //  2015/08/03

				  if  (  dlgTalk_OnQyComm_wmParam_procOfflineRes(  hDlg,  &m_var,  wParam,  lParam  )  )  goto  errLabel;

				  //					
				  lRet  =  CONST_qyWmRc_ok;  goto  errLabel;

				  }
				  break;

			case  CONST_qyWmParam_command:  {		//  2016/05/24
				  QY_wmBuf_command  *  pWmBuf  =  (  QY_wmBuf_command  *  )pComm;
				  //
				  dlgTalk_OnIsCmd_noSync(  hDlg,  &m_var,  pWmBuf->iCmdId,  pWmBuf  );  
				  }
				  break;

			default:
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "dlgTalk_OnQyComm failed, unknown commType %d"  ),  pComm->uiType  );
					#endif
				    goto  errLabel;
	}
	lRet  =  CONST_qyWmRc_ok;
errLabel:
	return	lRet;

}




//
 int  dlgTalk_OnQyPostComm(  HWND  hDlg,  void  *  pDLG_TALK_var,  WPARAM  wParam,  LPARAM  lParam  )
{
	LONG				lRet			=	-1;
	if  (  !pDLG_TALK_var  )  return  -1;
	DLG_TALK_var	&	m_var			=	*(  DLG_TALK_var  *  )pDLG_TALK_var;
	QY_MC* pQyMc = m_var.pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	char				buf[1024]		=	"";
	//

	CQySyncFlg  syncFlg;
	if  (  syncFlg.sync(  &m_var.syncFlgs.bInSequence  )  )  {	
		showInfo_open0(  0,  0,  _T(  "dlgTalk_onQyPostComm failed, bLocked already"  )  );
		goto  errLabel;									
	}
	
	//
	PARAM_PROC_ROW		param;
	
	memset(  &param,  0,  sizeof(  param  )  );
	
	switch  (  wParam  )  {
			case  CONST_qyWmParam_setActiveWindow:
				  #ifndef  __WINCE__
						   //  SetActiveWindow(  hDlg  );
						   MACRO_SetForegroundWindow(  hDlg  );
				  #else
						   SetForegroundWindow(  hDlg  );
				  #endif

			      //  2012/05/17
				  lRet  =  CONST_qyWmRc_ok;  
				  goto  errLabel;

				  break;
			default:
					break;					
		
	}

	//  2012/05/17
	if  (  !m_var.guiData.bFinished_createCtrls  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "CDlgTalk::OnQyPostComm(  ) failed: bFinished_createCtrls is false, %I64u"  ),  m_var.addr.idInfo.ui64Id  );
		#endif
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::OnQyPostComm failed, bFinished_createCtrls false.%I64u"  ),  m_var.addr.idInfo.ui64Id  );
		goto  errLabel;
	}

	switch  (  wParam  )  {
			case  CONST_qyWmParam_msgArrive:
				  //
				  #ifdef  __SUPPORT_HTMLEDIT__
						  //  if  (  !m_var.m_pHtmlEdit_recentMsgList->m_bDisplayInited  )  break;
				  #endif

				  param.bScrollIntoView  =  TRUE;
				  param.bNewMsg  =  TRUE;
				  qTraverse(  m_var.m_pProcessQ, tmpHandler_showMsg,  hDlg,  &param  );  
				  //  printQ_mis(  &m_var.processQ,  0  );
				  if  (  param.bMsgNeedRemoved  )  {
					  					  
					#if  0  //  2014/12/25
					  CQySyncFlg	syncFlg;							
					  if  (  syncFlg.sync(  &m_var.syncFlgs.bInSequence  )  )  {		
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_OnQyPostComm failed, bLocked already, before removeMsg"  )  );
						  goto  errLabel;											
					  }
					#endif

					  //  traceLogA(  (char*)  "dlgTalk: before removeMsg, nQNodes is %d",  m_var.m_processQ.uiQNodes  );
					  memset(  &param,  0,  sizeof(  param  )  );
					  qRemoveMsg(  m_var.m_pProcessQ,  tmpHandler_bRemoveMsgInProcessQ,  hDlg,  &param  );
					  //  traceLogA(  (char*)  "dlgTalk: after removeMsg, nQNodes is %d",  m_var.m_processQ.uiQNodes  );
					  if  (  param.nMsgTalks_processed_inProcessQ  !=  m_var.nMsgTalks_processed_inProcessQ  )  {
						  #ifdef  __DEBUG__
								  traceLog((TCHAR*)  _T(  "dlgTalk_OnQyPostComm: nMsgTalks_processed_inProcessQ err, skipped"  )  );
						  #endif
						  m_var.nMsgTalks_processed_inProcessQ  =  param.nMsgTalks_processed_inProcessQ;
					  }
				  }
				  break;
			case  CONST_qyWmParam_guiMsgArrive:
				  
				  doWnd_guiMsgArrive(  pProcInfo,  lParam,  hDlg,  FALSE,  m_var.pMsgBuf_doWnd_guiMsgArrive  );	
				  				  
				  //
				  break;

			case  CONST_qyWmParam_doPost_drawCapImages:		//  2014/04/12
				  HWND  hWnd_dst;
				  hWnd_dst = m_var.av.hWnd_dst_peer;
				  doPost_drawCapImages(  hWnd_dst,  m_var.av.hDc_peer,  lParam,  &m_var.av.peerZone.images  );
				  hWnd_dst  =  M_GetDlgItem(  hDlg,  m_var.av.hCtrl_other  );
				  doPost_drawCapImages(  hWnd_dst,  m_var.av.hDc_other,  lParam,  &m_var.av.otherZone.images  );
				  hWnd_dst  =  M_GetDlgItem(  hDlg,  m_var.av.hCtrl_me  );
				  doPost_drawCapImages(  hWnd_dst,  m_var.av.hDc_me,  lParam,  &m_var.av.meZone.images  );
				  hWnd_dst  =  M_GetDlgItem(  hDlg,  m_var.av.hCtrl_bgWall_conf  );								//  201410/01
				  int  j;
				  for  (  j  =  0;  j  <  mycountof(  m_var.av.bgWall.mems  );  j  ++  )  {
					   CAP_IMAGES  *  pImgs  =  &m_var.av.bgWall.mems[j].images;
					   doPost_drawCapImages(  hWnd_dst,  m_var.av.hDc_bgWall_conf,  lParam,  pImgs  );
				  }

				  break;

			case  CONST_qyWmParam_gpsMsgArrive:	//  2012/04/20. 主窗口收到的信息
				  if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;
				  dlgTalk_gpsMsgArrive(  pProcInfo,  lParam,  hDlg,  m_var,  FALSE,  m_var.pMsgBuf_doWnd_guiMsgArrive  );
				  break;
#if  0
			case  CONST_qyWmParam_gps:	//  2012/04/24. 影子窗口收到的信息
				  if  (  isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;
				  int  index_shadow;
				  index_shadow  =  (  int  )lParam;
				  talkerShadow_procGps(  pProcInfo,  hDlg,  FALSE,  index_shadow  );
				  break;
#endif
			case  CONST_qyWmParam_avRecord_start:  {
				  CHelp_getDlgTalkVar	help_getDlgTalkVar;
				  HWND	hMgr  =  hDlg;
				  if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {
					  TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
					  if  (  !pShadow  )  goto  errLabel;
					  hMgr  =  pShadow->hMgr;
				  }
				  if  (  !IsWindow(  hMgr  )  )  goto  errLabel;
				  doCmd_startShareScreen(  pQyMc,  hMgr,  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hMgr  )  );

				  }
				  break;

			case  CONST_qyWmParam_broadcastRecorderStatus:
				  
				  traceLogA(  (char*)  "broadcastRecorderQuit"  );
				  if  (  IsWindow(  m_var.hWnd_instantAssistant  )  )  {					  
					  ::SendMessage(  m_var.hWnd_instantAssistant,  CONST_qyWm_comm,  0,  0  );					  
				  }

				  break;
			case  CONST_qyWmParam_notifyQmShmCmdStatus:  {
				  int	iIndex_sharedObj	=	(  int  )lParam;

				  traceLogA(  (char*)  "Not supported"  );
				  goto  errLabel;
				  }
				  break;
			case  CONST_qyWmParam_refreshLayout:  {
				  //  unsigned  short	usLayoutType  =  (  unsigned  short  )lParam;		  

				  //
				  BOOL	bModified  =  FALSE;
				  dlgTalk_refresh_usLayoutType_cur(  hDlg,  &bModified  );
				  if  (  bModified  )  {	//  2013/02/24
					  int  idc_dst  =  0;	//  m_var.av.idc_peer;
					  old_freeCapImages(  hDlg,  m_var.av.idc_peer,  &m_var.av.peerZone.images,  old_M_GetDlgItem(  hDlg,  idc_dst  ),  &m_var.av.hDc_peer,_T("dlgTalk_OnQyPostComm.11881"));
					  //  2013/02/28
					  InvalidateRect(  hDlg,  NULL,  TRUE  );
					  //
					  if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
						  ushort  usLayout_cur  =  m_var.m_layout.usLayoutType_cur;
						  //sendConfLayout(  usLayout_cur,  hDlg,  m_var.addr.idInfo,  _T(  "refreshLayout"  )  );
					  }
				  }
				  
				  //  2013/08/18
				  if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
					  dyn_d3dWall_refreshImgs(  hDlg,  (TCHAR*)_T(  "dlgTalk_OnQyPostComm.12089"  ));
				  }

				  //  2012/05/14
				  if  (  isInvisibleMgr(  m_var  )  )  {
					  //  不可见,就不用显示了
					  break;
				  }

				  //
				  if  (  dlgTalk_get_usLayoutType_local(  hDlg  )  ==  CONST_usLayoutType_dialog  )  {
					  #ifndef  __WINCE__
							   if  (  IsIconic(  hDlg  )  )  ::SendMessage(  hDlg,  WM_SYSCOMMAND,  SC_RESTORE,  0  );
					  #endif
					  //  SetForegroundWindow(  hDlg  );
				  }
				  }
				  break;
			case  CONST_qyWmParam_bNeedRefresh_activeMems_from:  {
				  if  (  !m_var.av.taskInfo.bTaskExists  )  break;
				  if  (  lParam  !=  m_var.av.taskInfo.iTaskId  )  break;
				  if  (  !m_var.av.taskInfo.ucbVideoConference
					  ||  !m_var.av.taskInfo.ucbStarter  )  break;
				  QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  m_var.av.taskInfo.iIndex_taskInfo  );
				  if  (  !pTaskInfo  )  goto  errLabel;
				  if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;
				  QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

				  //
				  pTc->videoConference.bNeedRefresh_activeMems_from  =  TRUE;
				  refreshTaskAv_videoConferenceStarter(  hDlg,  NULL  );
				  }
				  //
				  break;
			case  CONST_qyWmParam_curSharedObjUsrChanged_mgr:  {
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "dlgTalk_postComm, CONST_qyWmParam_curSharedObjUsrChanged"  )  );
				  #endif
				  if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {
					  #ifdef  __DEBUG__
							  traceLog((TCHAR*)  _T(  "dlgTalk_postComm failed, CONST_qyWmParam_curSharedObjUsrChanged_mgr sent to shadow"  )  );
					  #endif
					  goto  errLabel;
				  }
				   
				  //  if  (  m_var.av.taskInfo.bTaskExists  )  
				  {
					  //  if  (  m_var.av.ucbGot_iIndex_sharedObj_localAv  )  
					  {
						  TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
						  if  (  !pShadowMgr  )  goto  errLabel;

						  int  i;
						  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
							   //  viewLocalAv_dlgTalk(  pShadowMgr->shadows[i].hShadow,  FALSE  );
							   if  (  !pShadowMgr->shadows[i].hShadow  )  continue;
							   PostMessage(  pShadowMgr->shadows[i].hShadow,  CONST_qyWm_postComm,  CONST_qyWmParam_curSharedObjUsrChanged_shadow,  0  );
						  }
						  //  viewLocalAv_dlgTalk(  hDlg,  FALSE  );
						  int  idc_dst  =  m_var.av.idc_me;
						  old_freeCapImages(  hDlg,  m_var.av.idc_me,  &m_var.av.meZone.images,  old_M_GetDlgItem(  hDlg,  idc_dst  ),  &m_var.av.hDc_me,  _T(  "dlgTalk_OnQyPostComm.11953"  ));

						  //  2013/04/08
						  dlgTalk_doLayout(  hDlg  );
					  }
				  }

				  //
				  //  InvalidateRect_mgr(  hDlg,  NULL,  TRUE  );
				  InvalidateRect(  hDlg,  NULL,  TRUE  );
				  }				  
				  break;
			case  CONST_qyWmParam_curSharedObjUsrChanged_shadow:		//  2013/02/28
				  if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
  					  #ifdef  __DEBUG__
							  traceLog((TCHAR*)  _T(  "dlgTalk_postComm failed, CONST_qyWmParam_curSharedObjUsrChanged_shadow sent to mgr"  )  );
					  #endif
					  goto  errLabel;
				  }
				  //
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "dlgTalk_postComm: CONST_qyWmParam_curSharedObjUsrChanged_shadow to shadow"  )  );
				  #endif
				  //
				  int  idc_dst;  idc_dst  =  m_var.av.idc_me;
				  old_freeCapImages(  hDlg,  m_var.av.idc_me,  &m_var.av.meZone.images,  old_M_GetDlgItem(  hDlg,  idc_dst  ),  &m_var.av.hDc_me,  _T(  "dlgTalk_OnQyPostComm.11978"  ));
				  InvalidateRect(  hDlg,  NULL,  TRUE  );
	
				  HWND  hCtrl;
				  hCtrl  =  GetDlgItem(  hDlg,  m_var.guiData.iIDC_STATIC_dlgDesc  );
				  InvalidateRect(  hCtrl,  NULL,  TRUE  );
				  
				  //  2013/03/03
				  //  sizeAllControls_dlgInstantAssistant(  m_var.hWnd_instantAssistant  );
				  dlgTalk_doLayout(  hDlg  );


				  break;
			case  CONST_qyWmParam_invalidate_bgWall:	//  2016/03/15
				  {
					 HWND  hDlgTalk  =  hDlg;
					 if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;

					 //
					 InvalidateRect_mgr(  hDlgTalk,  m_var.av.idc_bgWall_conf,  NULL,  TRUE  );
					 //
					 int  idc  =  m_var.av.idc_bgWall_conf;
					 int  idc_dst  =  0;
					 //freeCapImageByTaskId(  hDlgTalk,  idc,  pImg->iTaskId,  &images,  old_M_GetDlgItem(  hDlgTalk,  idc_dst  )  );
					 dlgTalk_freeCapImages_bgWall_mgr(  hDlgTalk,  idc  );
					 //  2014/11/29
					 dyn_d3dWall_refreshWallMemByTalker(  hDlgTalk  );

				  }
				  break;
			case  CONST_qyWmParam_freeCapImageBySth_bgWall:  //  2016/03/15
				  {
					  HWND  hDlgTalk  =  hDlg;
					  int  iTaskId  =  lParam;
					 if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;
					  //
					  dlgTalk_freeCapImageBySth_bgWall_mgr(  hDlgTalk,  iTaskId,  NULL  );

				  }
				  break;
				  //
			case  CONST_qyWmParam_misMsgInited:  {  //  2018/10/30
				  int  ii  =  0;
				  if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hzj  )  {
			
					  if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;

					  FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
							 
					  //		
					  pFuncs->pf_setCurSharedObjUsr_localAv(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv,  m_var.av.iIndex_usr_localAv  );
						 
					  //		
					  dlgTalk_requestToSpeak(  hDlg,  TRUE  );

		 
				  }
				  }
				  break;
			default:
				    goto  errLabel;
	}

	lRet  =  QY_RC_WMOK;

errLabel:

	return	lRet;
}

/////////////////
 









#define		CONST_nGetMsgs_procGps		20

 //  2011/12/10
 int  dlgTalk_gpsMsgArrive(  void  *  pProcInfoParam,  int  iIndex_player_gps,  HWND  hWnd,  DLG_TALK_var  &  m_var,  BOOL  bForce_displayAllFrames,  MIS_MSGU  *  pMsg  )
{
	int					iErr			=	-1;
	MC_VAR_isCli		*	pProcInfo		=	(  MC_VAR_isCli  *  )pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	QY_MC			*	pQyMc			=	(  QY_MC  *  )pProcInfo->pQyMc;

	//  
	int					cnt				=	0;
	QY_PLAYER_gps	*	pPlayer_gps		=	NULL;

	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;
	TALKER_shadow_mgr  *	pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;


	if  (  !pMsg  )  {
		traceLogA(  (char*)  "doWnd_guiMsgArrive failed: pMsg is NULL"  );
		return  -1;
	}
	//  unsigned  int		len;
	BOOL				bSkipped;

	MIS_MSG_procGps_qmc			msgs[CONST_nGetMsgs_procGps];
	MIS_MSGU				*	pMsgs[CONST_nGetMsgs_procGps];
	int							len_pMsgs[CONST_nGetMsgs_procGps];
	int							max_nMsgs  =  CONST_nGetMsgs_procGps;
	int							nMsgs;
	int							i;

	//  traceLogA(  (char*)  "doWnd_guiMsgArrive"  );
#ifdef  __DEBUG__
#endif

	//
	for  (  i  =  0;  i  <  max_nMsgs;  i  ++  )  {
		 pMsgs[i]  =  (  MIS_MSGU  *  )&msgs[i];
	}

	//  2012/05/07
	if  (  iIndex_player_gps  <  0  ||  iIndex_player_gps  >=  pProcInfo->gps.usCnt_players  )  goto  errLabel;
	pPlayer_gps  =  &pProcInfo->gps.pPlayers[iIndex_player_gps];


	//
	BOOL	ucbDisplayAllFrames  =  FALSE;

	//
	for  (  ;  !pQyMc->bQuit;  )  {
		 
		 if  (  isQ2Empty(  &pPlayer_gps->q2  )  )  break;

		 for  (  i  =  0;  i  <  max_nMsgs;  i  ++  )  {
			  len_pMsgs[i]  =  sizeof(  MIS_MSG_procGps_qmc  );
		 }
		 nMsgs  =  max_nMsgs;
		 {
			 CQyQ2Help			q2Help;
			 if  (  qGetMsgs(  q2Help.getQ_toGetMsg(  &pPlayer_gps->q2,  _T(  "dlgTalk_gpsMsgArrive"  )), (void**)pMsgs, (unsigned  int*)len_pMsgs, (unsigned  int*)&nMsgs))  break;
		 }
		 
		 cnt  ++  ;
		 pShadowMgr->viewGps.dwTickCnt_lastRecvd  =  GetTickCount(  );

		 //
		 #ifdef  __DEBUG__
				 #if  0
					  traceLog((TCHAR*)  _T(  "dlgTalk_gpsMsgArrive %I64u: nMsgs %d"  ),  m_var.addr.idInfo.ui64Id,  nMsgs  );
				 #endif
		 #endif

		 //
		 for  (  i  =  0;  i  <  nMsgs;  i  ++  )  {
			  pMsg  =  pMsgs[i];
			  switch  (  pMsg->uiType  )  {
				      case  CONST_misMsgType_procGps_qmc:

							bSkipped  =  FALSE;
							if  (  pMsg->procGps.idInfo_peer.ui64Id  !=  m_var.addr.idInfo.ui64Id  )  {
   							   #if  10
								    traceLogA(  (char*)  "doWnd_guiMsgArrive: msg.index_peer not matched, skipped."  );			
									qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doWnd_guiMsgArrive: msg.idInfo_peer not matched, skipped."  )  );			
								#endif	
								bSkipped  =  TRUE;						   
							}				
							if  (  !ucbDisplayAllFrames  &&  i  !=  nMsgs  -  1  )  {
								#ifdef  __DEBUG__
										#if  0
											traceLogA(  (char*)  "doWnd_guiMsgArrive: msg is not the last one, skipped."  );			
											qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doWnd_guiMsgArrive: msg is not the last one, skipped. nMsgs %d, cnt %d"  ),  nMsgs,  cnt  );
										#endif	
								#endif
								bSkipped  =  TRUE;						   			 
							}		 					  

							if  (  !bSkipped  )  {
								#if  0
							   ::SendMessage(  hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  ); 
								#endif

							   myGPS_POSITION	gpsPos;
							   memset(  &gpsPos,  0,  sizeof(  gpsPos  )  );
							   gpsPos.dblLatitude  =  pMsg->procGps.transferGpsData.mems[0].iLaInM10000f  /  10000.  /  60.;
							   gpsPos.dblLongitude  =  pMsg->procGps.transferGpsData.mems[0].iLoInM10000f  /  10000.  /  60.;
							   TCHAR	tBuf[256];

							   #ifdef  __APP_qyMc__
									   #ifdef  __DEBUG__
											   #if  0
													gps_DisplayStr(  &gpsPos,  tBuf,  mycountof(  tBuf  )  );
													traceLog((TCHAR*)  _T(  "gpsStr %s"  ),  tBuf  );
													//  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk, recvd gps %s"  ),  tBuf  );
											   #endif
									   #endif
							   #endif

							   //
							   memcpy(  &pShadowMgr->viewGps.gpsPos,  &gpsPos,  sizeof(  pShadowMgr->viewGps.gpsPos  )  );

							   //
							   int  j;
							   for  (  j  =  0;  j  <  mycountof(  pShadowMgr->shadows  );  j  ++  )  {
								    if  (  pShadowMgr->shadows[j].hShadow
										&&  pShadowMgr->shadows[j].vwRuleCmd.ucbViewGps  )
									{
										#if  0
										if  (  !PostMessage(  pShadowMgr->shadows[j].hShadow,  CONST_qyWm_postComm,  CONST_qyWmParam_gps,  j  )  )  {
											if  (  !IsWindow(  pShadowMgr->shadows[j].hShadow  )  )  {
												pShadowMgr->shadows[j].hShadow  =  NULL;
											}
										}
										#endif
										if  (  pShadowMgr->shadows[i].iWndContentType_wall  ==  CONST_qyWndContentType_vWall  )  {
											addToWallGpsMgr(  pShadowMgr->shadows[j].hShadow,  j,  &gpsPos,  pShadowMgr->shadows[j].hWall  );											
											PostMessage(  pShadowMgr->shadows[j].hWall,  CONST_qyWm_postComm,  CONST_qyWmParam_gps,  j  );
										}

									}
							   }

							}
					 
						   break;
					 default:
						     traceLogA(  (char*)  "dlgTalk_gpsMsgArrive:  unprocessed: msgType: %d",  pMsg->uiType  );										
							 break;								
			 }
		 }
		 //  if  (  pPlayer->video.m_var.ucbDisplayAllFrames  )  
		 {
			 if  (  cnt  >=  2  )		//  2011/07/16
			 {
				 #if  0		//  2012/05/08. 按理,不需要这里重新发起,因为每个数据都带了一个包
					  if  (  !isQ2Empty(  &pPlayer_gps->q2  )  )  {
						  ::PostMessage(  hWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_gpsMsgArrive,  0  );   							   
					  }
				 #endif

			     //
				 break;
			 }
		 }
	}
				  

	iErr  =  0;
errLabel:
	return  iErr;
 

}




///////////////////









 //
BOOL  bTaskExists_remoteVideo_manual(  void  *  pDLG_TALK_var,  int  *  pnTasks,  int  *  pnTasks_unresizable,  int  *  piW_unresizable,  int  *  piH_unresizable  )
{
	BOOL  bRet  =  FALSE;

	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )pDLG_TALK_var;
	if  (  !pMgrVar  )  return  FALSE;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  {
		return  FALSE;
	}
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  {
		return  FALSE;
	}

	//
	int  nTasks  =  0;
	int  nTasks_unresizable  =  0;
	int  iW_unresizable  =  0;
	int  iH_unresizable  =  0;

	//
	int  i;
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->vwRuleCmd.dynBmpRules  );  i  ++  )  {
		if  (  !pShadowMgr->vwRuleCmd.dynBmpRules[i].dynBmp.resObj.uiObjType  )  continue;
		
		//  2016/02/18
		if  (  !pShadowMgr->vwRuleCmd.dynBmpRules[i].helpInfo.ucbAddedManually  )  continue;

		//
		TALKER_dynBmp  *  pTalkerDynBmp  =  &pShadowMgr->talkerDynBmps[i];
		//
		if  (  !pTalkerDynBmp->taskInfo.iTaskId  )  continue;
		if  (  !pTalkerDynBmp->taskInfo.srcInfo.iW  ||  !pTalkerDynBmp->taskInfo.srcInfo.iH  )  continue;
		//
		nTasks  ++  ;
		
		//		
		if  (  pTalkerDynBmp->taskInfo.srcInfo.iW  &&  pTalkerDynBmp->taskInfo.srcInfo.iW  &&  pTalkerDynBmp->taskInfo.srcInfo.ucbUnresizable  )  {
				nTasks_unresizable  ++  ;
				if  (  nTasks_unresizable  ==  1  )  {
					iW_unresizable  =  pTalkerDynBmp->taskInfo.srcInfo.iW;
					iH_unresizable  =  pTalkerDynBmp->taskInfo.srcInfo.iH;
				}
		}
	}

	if  (  !nTasks  )  goto  errLabel;

	if  (  pnTasks  )  *pnTasks  =  nTasks;
	if  (  pnTasks_unresizable  )  *pnTasks_unresizable  =  nTasks_unresizable;
	if  (  piW_unresizable  )  *piW_unresizable  =  iW_unresizable;
	if  (  piH_unresizable  )  *piH_unresizable  =  iH_unresizable;
	
	bRet  =  TRUE;

errLabel:


	return  bRet;


}






 //  2013/03/03
 int  dlgTalk_refresh_usLayoutType_cur(  HWND  hDlgTalk,  BOOL  *  pbModified  )
{
	int							iErr								=	-1;

	//
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var			*	pDlgTalkVar							=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk,  _T(  "dlgTalk_refresh_usLayoutType_cur"  )  );
	if  (  !pDlgTalkVar  )  return  -1;

	QY_MC* pQyMc = pDlgTalkVar->pQyMc;// QY_GET_GBUF();
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();


	unsigned  short				usLayoutType_cur					=	0;
	//
	BOOL						bScroll								=	FALSE;
	//  2013/06/25. 如果有远程视频的指令,就算一个活动任务
	BOOL						bExists_remoteVideo  =  FALSE;
	//
	BOOL						bModified							=	FALSE;

	CHelp_getDlgTalkVar			help_getDlgTalkVar_mgr;

	HWND  hMgr  =  hDlgTalk;
	DLG_TALK_var	*	pMgrVar	=	pDlgTalkVar;
	if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  {
		TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pDlgTalkVar->pShadowInfo;
		if  (  !pShadow  )  goto  errLabel;
		hMgr  =  pShadow->hMgr;
		pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pShadow->hMgr,  _T(  "dlgTalk_refresh_usLayoutType_cur,hMgr"  )  );
		if  (  !pMgrVar  )  goto  errLabel;
	}

	//
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

	//  2013/02/28
	unsigned  short  usLayoutType_local  =  dlgTalk_get_usLayoutType_local(  hDlgTalk  );

	//
	int  nScreens  =  0,  nMediaFiles  =  0;
	int  nMediaFiles_unresizable  =  0;											//  2015/03/12
	int  iW_unresizable  =  0,  iH_unresizable  =  0;
	BOOL	bExists_recvdResource  =  FALSE;
	//
	int  nScreens_sendingResource  =  0,  nMediaFiles_sendingResource  =  0;	//  2015/03/12
	int  nMediaFiles_unresizable_sendingResource  =  0;
	int  iW_unresizable_sendingResource  =  0,  iH_unresizable_sendingResource  =  0;	//  2015/03/12
	BOOL	bExists_sharingResource  =  FALSE;	//  2014/11/14


	//
	//
	int  nTasks_remoteVideo  =  0;
	int  nTasks_unresizable_remoteVideo  =  0;
	int  iW_unresizable_remoteVideo  =  0;
	int  iH_unresizable_remoteVideo  =  0;
	bExists_remoteVideo  =  bTaskExists_remoteVideo_manual(  pMgrVar,  &nTasks_remoteVideo,  &nTasks_unresizable_remoteVideo,  &iW_unresizable_remoteVideo,  &iH_unresizable_remoteVideo  );  


	//  2014/11/18
	BOOL  bDone  =  FALSE;

	//  2014/11/16
	if  (  pMgrVar->av.taskInfo.bTaskExists  )  {
		if  (  pMgrVar->av.taskInfo.ucbVideoConference
			&&  !pMgrVar->av.taskInfo.ucbStarter  )  
		{
			if  (  pMgrVar->av.taskInfo.mosaicTrans.bExists_confMosaic  )  {
				usLayoutType_cur  =  CONST_usLayoutType_dialog;
				if  (  pMgrVar->av.taskInfo.mosaicTrans.status.bDisplayResource  
					&&  !bExists_remoteVideo
					&&  !pShadowMgr->shareScreen.ucbExists_localScreenSharing	//  2016/04/24
					)  
				{
					usLayoutType_cur  =  CONST_usLayoutType_resourceOnly;

					//
					//pMgrVar->av.taskInfo.mosaicTrans.status.

					//
					bScroll  =  TRUE;
					//
					iW_unresizable  =  pMgrVar->av.taskInfo.mosaicTrans.status.iW_resource;
					iH_unresizable  =  pMgrVar->av.taskInfo.mosaicTrans.status.iH_resource;

					//			
					if (!pProcInfo->bAppQt()) {
						if (iW_unresizable != pDlgTalkVar->m_layout.uiW_pic || iH_unresizable != pDlgTalkVar->m_layout.uiH_pic) {
							//
#ifdef  __DEBUG__
							traceLog((TCHAR*)_T("dlgTalk_refresh_usLayoutType_cur: bModified, tn %d, iW_unresizable %dx%d, talk.%dx%d"), pDlgTalkVar->addr.uiTranNo_shadow, iW_unresizable, iH_unresizable, pDlgTalkVar->m_layout.uiW_pic, pDlgTalkVar->m_layout.uiH_pic);
#endif

							//
							dlgTalk_SetPicRect(hDlgTalk, iW_unresizable, iH_unresizable, FALSE);
							bModified = TRUE;
							//
							//
						}
					}

				}
				//
				bDone  =  TRUE;
			}
		}
	}
		//
	if  (  !bDone  )  {
		//
		bExists_recvdResource  =  bTaskExists_recvResource(  pMgrVar,  &nScreens,  &nMediaFiles,  &nMediaFiles_unresizable,  &iW_unresizable,  &iH_unresizable,  NULL  );

		//  2014/11/15
		bExists_sharingResource  =  bTaskExists_sendingResource(  pMgrVar,  &nScreens_sendingResource,  &nMediaFiles_sendingResource,  &nMediaFiles_unresizable_sendingResource,  &iW_unresizable_sendingResource,  &iH_unresizable_sendingResource,  NULL  );

		//  2014/11/14
		if  (  pShadowMgr->shareScreen.ucbExists_localScreenSharing  )  {
			bExists_sharingResource  =  TRUE;
		}	

		//
		int  i;

		for  (  i  =  0;  i  <  1;  i  ++  )  {

			//
			if  (  pMgrVar->av.taskInfo.bTaskExists  )  {
			
				//
				if  (  usLayoutType_local  )  {
					usLayoutType_cur  =  usLayoutType_local;
					break;
				}

				//
				if  (  pMgrVar->av.taskInfo.usLayoutType_starter  )  {
					usLayoutType_cur  =  pMgrVar->av.taskInfo.usLayoutType_starter;
					break;
				}

				//  2015/10/25
				if  (  bExists_remoteVideo  )  {
					usLayoutType_cur  =  CONST_usLayoutType_training;
					break;
				}

				//
				if  (  bExists_recvdResource  ||  bExists_sharingResource  )  {
					usLayoutType_cur  =  CONST_usLayoutType_training;
					break;
				}


				//
				usLayoutType_cur  =  CONST_usLayoutType_dialog;
				break;
			}
		
			//  2012/05/24		
			if  (  usLayoutType_local  )  {
				usLayoutType_cur  =  usLayoutType_local;
				break;			
			}

			//  2015/10/23
			if  (  bExists_remoteVideo  )  {
				usLayoutType_cur  =  CONST_usLayoutType_resourceOnly;
				break;
			}
		
			//
			if  (  bExists_recvdResource  ||  bExists_sharingResource  )  {
				usLayoutType_cur  =  CONST_usLayoutType_resourceOnly;
				break;
			}
		
			//
			usLayoutType_cur  =  CONST_usLayoutType_dialog;
			break;
		}

		//
		if  (  usLayoutType_cur  ==  CONST_usLayoutType_resourceOnly
			||  usLayoutType_cur  ==  CONST_usLayoutType_training  )
		{
			BOOL  bNeedScroll  =  FALSE;
			int  iW_scroll  =  0;
			int  iH_scroll  =  0;
			//
			if  (  !bExists_remoteVideo
				&&  !bExists_sharingResource
				&&  bExists_recvdResource
				&&  (  (  nScreens  ==  1  &&  !nMediaFiles  )  ||  (  !nScreens  &&  nMediaFiles  ==  1  &&  nMediaFiles_unresizable  ==  1  )  )
				&&  iW_unresizable
				&&  iH_unresizable  )  
			{
				bNeedScroll  =  TRUE;
				iW_scroll  =  iW_unresizable;
				iH_scroll  =  iH_unresizable;
			}
			//
			if  (  !bNeedScroll  )  {
				if  (  !bExists_remoteVideo
					&&  bExists_sharingResource
					&&  !bExists_recvdResource
					&&  !nScreens_sendingResource
					&&  nMediaFiles_sendingResource  ==  1
					&&  nMediaFiles_unresizable_sendingResource  ==  1
					&&  iW_unresizable_sendingResource
					&&  iH_unresizable_sendingResource  )  
				{
					bNeedScroll  =  TRUE;
					iW_scroll  =  iW_unresizable_sendingResource;
					iH_scroll  =  iH_unresizable_sendingResource;
				}
			}
			//  2015/10/23
			if  (  !bNeedScroll  )  {
				if  (  bExists_remoteVideo
					&&  !bExists_recvdResource
					&&  !bExists_sharingResource  )
				{
					if  (  nTasks_remoteVideo  ==  1  
						&&  nTasks_unresizable_remoteVideo  ==  1  )  
					{
						bNeedScroll  =  TRUE;
						iW_scroll  =  iW_unresizable_remoteVideo;
						iH_scroll  =  iH_unresizable_remoteVideo;
					}

				}
			}
			//
			if  (  bNeedScroll  )  {
				bScroll  =  TRUE;

				if  (  iW_scroll  !=  pDlgTalkVar->m_layout.uiW_pic  ||  iH_scroll  !=  pDlgTalkVar->m_layout.uiH_pic  )  {
					dlgTalk_SetPicRect(  hDlgTalk,  iW_scroll,  iH_scroll,  FALSE  );
					bModified  =  TRUE;
				}
			}
		}
		
	}

	//  result:
	if (!pProcInfo->bAppQt()) {
		if (bScroll != pDlgTalkVar->m_scrollInfo.bScrollBarEnabled) {
			dlgTalk_bEnableScrollBar(hDlgTalk, bScroll);
			bModified = TRUE;
			//
#ifdef  __DEBUG__		
			traceLog((TCHAR*)_T("dlgTalk_refresh_usLayoutType_cur: tn %d,  bModified, scroll ->%d changed"), pDlgTalkVar->addr.uiTranNo_shadow, bScroll);
#endif
		}
	}
	//
#ifdef  __DEBUG__
		#if  0
			TCHAR  tBuf[128];
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "tn_shadow %d, scroolBarEnable %d. nTasks_remoteVideo %d, nTasks_unresizable %d"  ),  pDlgTalkVar->addr.uiTranNo_shadow,  pDlgTalkVar->m_scrollInfo.bScrollBarEnabled,
				nTasks_remoteVideo,  nTasks_unresizable_remoteVideo  );
			showInfo_open0(  0,  0,  tBuf  );
		#endif
#endif
	
	//
	if  (  pDlgTalkVar->m_layout.usLayoutType_cur  !=  usLayoutType_cur  )  {	
		//
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("dlgTalk_refresh_usLayoutType_cur: tn %d, layoutType changed"), pDlgTalkVar->addr.uiTranNo_shadow);
#endif
		//
		pDlgTalkVar->m_layout.usLayoutType_cur  =  usLayoutType_cur;
		bModified  =  TRUE;		
		//

	}

	//  2015/11/14
	if  (  pDlgTalkVar->m_layout.ucbExists_localScreenSharing  !=  pShadowMgr->shareScreen.ucbExists_localScreenSharing  )  {
		pDlgTalkVar->m_layout.ucbExists_localScreenSharing  =  pShadowMgr->shareScreen.ucbExists_localScreenSharing;
		bModified  =  TRUE;
	}

	//  2014/11/15
	if  (  !bExists_sharingResource  &&  !pMgrVar->av.taskInfo.bTaskExists  )  {
		HWND  hCtrl_meDesc  =  GetDlgItem(  hDlgTalk,  pDlgTalkVar->guiData.iIDC_STATIC_meDesc  );
		if  (  IsWindowVisible(  hCtrl_meDesc  )  )  {
			bModified  =  TRUE;
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "refresh_usLayoutType_cur: meDesc need be invisible"  )  );
			#endif
		}
	}

	//  2015/10/25
	//  if  (  !bExists_sharingResource  )  
	if  (  pDlgTalkVar->guiData.iIDC_STATIC_peerDesc  )
	{
		  HWND  hCtrl_peerDesc  =  GetDlgItem(  hDlgTalk,  pDlgTalkVar->guiData.iIDC_STATIC_peerDesc  );	
		  if  (  IsWindowVisible(  hCtrl_peerDesc  )  )  {		
			  bModified  =  TRUE;
			  #ifdef  __DEBUG__
					  traceLog((TCHAR*)  _T(  "refresh_usLayoutType_cur: peerDesc need be invisible"  )  );
			  #endif		  
		  }	
	}

	//  2014/11/18
	if  (  pShadowMgr->shareScreen.ucbExists_localScreenSharing  )  {		
		TCHAR  tBuf[128]  =  _T(  ""  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\n\n    %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_sharingLetWinBeSmaller  )  );
		SetDlgItemText(  hDlgTalk,  pDlgTalkVar->guiData.iIDC_STATIC_peerDesc,  tBuf  );
		}
	else  {
		  SetDlgItemText(  hDlgTalk,  pDlgTalkVar->guiData.iIDC_STATIC_peerDesc,  _T(  ""  )  );	
	}
	
	//
	if  (  bModified  )  {
		dlgTalk_doLayout(  hDlgTalk  );
	}

	iErr  =  0;

errLabel:

	if  (  !iErr  )  {
		if  (  pbModified  )  *pbModified  =  bModified;
		//
		if  (  bModified  )  {
			dyn_d3dWall_refreshImgs(  hMgr,  (TCHAR*)_T(  "dlgTalk_refresh_usLayoutType_cur"  ));
		}
	}

	return  iErr;
}








/////////////////////////////

 //  2011/08/13
 int  tmpHandler_isDlgTalk(  void  *  p0,  void  *  p1,  void  *  p2  )
{
		int				iErr	=	-1;
	//  HWND			hWnd_last	=	(  HWND  )p0;
	HWND		*	phWnd_next	=	(  HWND  *  )p1;
	MIS_MSGU	*	pMsg	=	(  MIS_MSGU  *  )p2;

	if  (  pMsg->uiType  ==  CONST_misMsgType_talkingFriend_qmc  )  {
		if  (  IsWindow(  pMsg->talkingFriend_qmc.hWnd  )  )  {
			if  (  *phWnd_next  ==  pMsg->talkingFriend_qmc.hWnd  )  {
			iErr  =  1;  goto  errLabel;
			}
		}
	}

	iErr  =  0;
errLabel:
	return  iErr;
 }


 			
 //  2011/08/12. 是否有dlgTalk在hWnd之前
 BOOL bDlgTalkAbove(  HWND hWnd  )
{
	BOOL		bRet	=	FALSE;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	MIS_CNT	*	pMisCnt	=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	if  (  !pMisCnt  )  return  FALSE;

	for  (  HWND  hWndPrev  =  ::GetWindow(  hWnd,  GW_HWNDPREV  );  hWndPrev  !=  0;  hWndPrev  =  ::GetWindow(  hWndPrev,  GW_HWNDPREV  )  )  {

		 if  (  qTraverse(  &pMisCnt->talkingFriendQ,  tmpHandler_isDlgTalk,  NULL,  &hWndPrev  )  >  0  )  {
			 traceLog((TCHAR*)  _T(  "dlgTalk above"  )  );
			 bRet  =  TRUE;
			 break;
		 }
	}
	return  bRet;
}


 
//  2012/04/06
 int  tmpHandler_isDlgTalk_wall(  void  *  p0,  void  *  p1,  void  *  p2  )
{
		int				iErr	=	-1;
	//  HWND			hWnd_last	=	(  HWND  )p0;
	HWND		*	phWnd_next	=	(  HWND  *  )p1;
	HWND		*	phWnd	=	(  HWND  *  )p2;

	if  (  *phWnd_next  ==  *phWnd  )  {
		iErr  =  1;  goto  errLabel;			
	}

	iErr  =  0;
errLabel:
	return  iErr;
 }


 			

 //  2012/04/10.是否mainWnd在hWnd之前
 BOOL  bMainWndAbove(  QY_MC  *  pQyMc,  HWND  hWnd  )
{
	BOOL	bRet	=	FALSE;
	//QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;

	for  (  HWND  hWndPrev  =  ::GetWindow(  hWnd,  GW_HWNDPREV  );  hWndPrev  !=  0;  hWndPrev  =  ::GetWindow(  hWndPrev,  GW_HWNDPREV  )  )  {

		 if  (  pQyMc->gui.hMainWnd  ==  hWndPrev  )  {
			 bRet  =  TRUE;  goto  errLabel;
			 break;
		 }
	}

errLabel:

	return  bRet;
}




 int  openLocalVideo_slave(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiCamCapType,  int  iIndex_sharedObj_master,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressorParam,  int  iIndex_sharedObj  )
{
	int		iErr	=	-1;

	//
	QY_MC* pQyMc = pProcInfoCommon->pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli				*	pProcInfo				=	QY_GET_procInfo_isCli(  );
	int								iIndex_sharedObjUsr		=	0;
	QY_SHARED_OBJ				*	pSharedObj				=	NULL;
	int								iIndex_capBmp;
	CAP_procInfo_bmpCommon		*	pCapBmp					=	NULL;
	COMPRESS_VIDEO				*	pCompressVideo			=	NULL;
	unsigned  int					uiCapType				=	CONST_capType_mediaDevice;


	#ifdef  __DEBUG__
			traceLog((TCHAR*)  _T(  "openLocalVideo_slave"  )  );
	#endif

	//
	QY_SHARED_OBJ				*	pSharedObj_master		=	NULL;
	CAP_procInfo_bmpCommon		*	pCapBmp_master			=	NULL;
	pSharedObj_master  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj_master  );
	if  (  !pSharedObj_master  )  goto  errLabel;
	pCapBmp_master  =  (  CAP_procInfo_bmpCommon  *  )getCapBmpBySth(  pProcInfo,  pSharedObj_master->iIndex_capBmp,  0  );
	if  (  !pCapBmp_master  )  goto  errLabel;
	

	//
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	iIndex_capBmp  =  pSharedObj->iIndex_capBmp;
	pCapBmp  =  (  CAP_procInfo_bmpCommon  *  )getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );
	if  (  !pCapBmp  )  goto  errLabel;
	pCompressVideo  =  &pCapBmp->compressVideo;
	

	//  2014/09/23. 在主对象和辅助对象间建立主从关系
	if  (  pSharedObj_master->bSlave  )  goto  errLabel;

	
	//  2014/09/10
	memcpy(  &pCompressVideo->compressor,  pVideoCompressorParam,  sizeof(  pCompressVideo->compressor  )  );
	VIDEO_COMPRESSOR_CFG  *  pVideoCompressor  =  &pCompressVideo->compressor;
	

	
#if  1	//  def  __DEBUG__
	pVideoCompressor->common.iWidth_pic  =  min(  MAX_w_slave,  pVideoCompressor->common.iWidth_pic  );
	pVideoCompressor->common.iHeight_pic  =  min(  MAX_h_slave,  pVideoCompressor->common.iHeight_pic  );
	//
	#ifdef  __DEBUG__
			traceLog((TCHAR*)  _T(  "Note: this needs to be modified, openLocalVideo_slave, compressor.w,h is restricted"  )  );
	#endif
#endif

	
	BOOL	bAudio  =  FALSE;	//  CAP_STUFF_bAudio(  *ppCapStuff  );
	BOOL	bVideo  =  TRUE;	//  CAP_STUFF_bVideo(  *ppCapStuff  );

	//  2014/09/23
	//memcpy(  &pCapBmp->vh_org.bih,  &pCapBmp_master->compressVideo.vh_decompress.bih,  sizeof(  pCapBmp->vh_org.bih  )  );
	makeBmpInfoHeader_rgb(  24,  pCapBmp_master->compressVideo.vh_decompress.bih.biWidth,  pCapBmp_master->compressVideo.vh_decompress.bih.biHeight,  &pCapBmp->vh_org.bih  );


	//
	if  (  bVideo  )  {
		CAP_procInfo_bmpCommon	*	pVc  =  pCapBmp;

		//
		if  (  pVc->vh_org.bih.biCompression  !=  BI_RGB  ||  pVc->vh_org.bih.biBitCount  !=  24  )  {
			if  (  initOrg2RgbBuf(  (  MC_VAR_common  *  )pProcInfo,  pVc  )  )  {
				traceLogA(  (char*)  "initOrg2RgbBuf failed."  );
				goto  errLabel;		
			}
		}

		QY_VIDEO_HEADER	*	pVh_rgb;
		pVh_rgb  =  pVc->bOrg2RgbBufInited  ?  &pVc->vh_rgb  :  &pVc->vh_org;
		//
		//  2014/04/03
		pVideoCompressor->common.pVideoQ2  =  &pVc->thread.q2;
		pVideoCompressor->common.pParent_transform  =  pVc;
		//
		//  2016/04/02
		_sntprintf(  pCompressVideo->tag_dbg,  mycountof(  pCompressVideo->tag_dbg  ),  _T(  "capBmp%d, slave of %d"  ),  iIndex_capBmp,  iIndex_sharedObj_master  );  
		//
		if  (  initCompressVideo(  pProcInfo,  (  BITMAPINFO  *  )&pVh_rgb->bih,  uiCapType,  pVideoCompressor,  FALSE,  0,  pCompressVideo  )  )  {
			showNotification(  NULL,  0,  0,  0,  0,  0,  _T(  "open slave: init video compress failed!"  )  );  
			goto  errLabel;
		}
	}
		
	
	//
	iErr  =  0;

errLabel:

	//  2013/03/01
	//  sizeAllControls_dlgTalk(  hDlg,  m_var,  NULL  );					//  µ÷ÕûÒ»ÏÂ²¼¾Ö
	//askToRefreshLayout_mgr(  hDlg  );

	return  iErr;
				  
}

 //  2014/09/23
 int  makeSlaveStream(  QY_MC  *  pQyMc,  HWND  hDlg,  int  iIndex_sharedObj_master,  int  level,  int  iFourcc_suggested  )
{
	int		iErr	=	-1;


	//
	//QY_MC						*	pQyMc					=	QY_GET_GBUF(  );
	MC_VAR_isCli				*	pProcInfo				=	QY_GET_procInfo_isCli(  );


	#ifdef  __DEBUG__
			if  (  pProcInfo->cfg.debugStatusInfo.ucb_noSlave  ) {
				traceLog((TCHAR*)_T("makeSlaveStream skipped" ) );
				return  0;
			}
			//
			traceLog((TCHAR*)  _T(  "makeSlaveStream"  )  );
	#endif

	//
	QY_SHARED_OBJ				*	pSharedObj_master		=	NULL;
	pSharedObj_master  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj_master  );
	if  (  !pSharedObj_master  )  goto  errLabel;
	
	//  2014/09/23. 在主对象和辅助对象间建立主从关系
	if  (  pSharedObj_master->bSlave  )  goto  errLabel;

	//
	//  pSharedObj_master->master.uiObjType_slave  =  CONST_objType_smallStream;
	//
	int  len  =  sizeof(  SHARE_dyn_bmp  );
	if  (  pSharedObj_master->master.pShareDynBmp_slave  )  {
		showInfo_open0(  0,  0,  _T(  "makeSlaveStream failed: pSharedDynBmp_slave is not null"  )  );
		goto  errLabel;
	}
	pSharedObj_master->master.pShareDynBmp_slave  =  mymalloc(  len  );
	if  (  !pSharedObj_master->master.pShareDynBmp_slave  )  goto  errLabel;
	memset(  pSharedObj_master->master.pShareDynBmp_slave,  0,  len  );

	//
	SHARE_dyn_bmp  *  pShareDynBmp_slave  =  (  SHARE_dyn_bmp  *  )pSharedObj_master->master.pShareDynBmp_slave;
	//
	pShareDynBmp_slave->iIndex_sharedObj_master  =  iIndex_sharedObj_master;
	//
	pShareDynBmp_slave->resObj.uiObjType  =  CONST_objType_smallStream;
	pShareDynBmp_slave->resObj.usIndex_obj  =  CONST_usIndex_avStream_slave;

	//	
	int iTaskId_suggested=0;
	{
		void * pDb=NULL;
		CQnmDb db;
		if(!db.getAvailableDb(pQyMc->iDsnIndex_mainSys)) goto errLabel;
		pDb=db.m_pDbMem->pDb;
		iTaskId_suggested=newTaskId(pDb,pQyMc->cfg.db.iDbType);
	}
	//
	if  (  toShareDynBmp(  pProcInfo,  hDlg,  NULL,  iTaskId_suggested,  NULL,  iFourcc_suggested,  NULL,  pShareDynBmp_slave  )  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "makeSlaveStream failed: toShareDynBmp failed"  )  );
		#endif
		goto  errLabel;
	}

	//
	if  (  !pShareDynBmp_slave->var.ucbUsed_iIndex_sharedObj  )  goto  errLabel;
	int  iIndex_sharedObj_slave =  pShareDynBmp_slave->var.iIndex_sharedObj;

	//
	QY_SHARED_OBJ  *  pSharedObj_slave  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj_slave  );
	if  (  !pSharedObj_slave  )  goto  errLabel;

	//
	if  (  addSlaveToMaster(  pProcInfo,  iIndex_sharedObj_slave,  iIndex_sharedObj_master  )  )  goto  errLabel;
		
	//
	iErr  =  0;

errLabel:


	return  iErr;
				  
}






