

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
#ifdef  __TEST_ONLY__
		#include	"testOnly.h"
#endif
#include	"qmcCommFunc_isCli.h"


//
//int  dlgTalk_procTask_display_op(  HWND  hDlgTalk,  DLG_TALK_var  *  pm_var,  int  iTaskId,  unsigned  short  usOp,  MIS_MSG_TASK  *  pMsgTask,  IM_TASK_RCD  &  rcd,  int  iStatus_old,  int  iStatus,  LPCTSTR  paramStrBuf  );


//
int  getAvLevelByWh(  int  w,  int  h  )
{
	int  level  =  0;

	//
	if  (  !h  )  return  0;

	//
	if  (  h  <=  240  )  level  =  CONST_policyAvLevel_240p;
	else  if  (  h  <=  480  )  {
			  if  (  w  >=  848  )  level  =  CONST_policyAvLevel_848x480;
			  else  level  =  CONST_policyAvLevel_480p;  
			  }
	else  if  (  h  <=  576  )  {
			  level  =  CONST_policyAvLevel_576p;
	}
	else  if  (  h  <=  720  )  {
			  level  =  CONST_policyAvLevel_720p;
	}
	else  if  (  h  <=  1080  )  {
			  level  =  CONST_policyAvLevel_1080p;
	}
	else  if (h <= 2160) {
			  level  =  CONST_policyAvLevel_2160p;
	}
	else  {
		  level  =  CONST_policyAvLevel_1080p;
	}

	return  level;
}


//
int  getAvLevel_reply(  TRANSFER_AV_INFO  *  pReq  )
{
	int  avLevel  =  CONST_policyAvLevel_480p;

	if  (  !pReq  )  return  0;
	int  iVal  =  0;
	if  (  !pReq->confCfg.ucbVideoConference  )  {
		iVal  =  pReq->ass.tranInfo.video.vh_decompress.bih.biWidth  *  pReq->ass.tranInfo.video.vh_decompress.bih.biHeight;
		}
	else  {
		  iVal =  pReq->confMosaicTranInfo_video.video.vh_decompress.bih.biWidth  *  pReq->confMosaicTranInfo_video.video.vh_decompress.bih.biHeight;
	}

	//
	if (iVal > (1920 + 200) * (1080 + 200))  avLevel = CONST_policyAvLevel_2160p;
	else  if (iVal >= 1920 * 1080)  avLevel = CONST_policyAvLevel_1080p;
	else  if (iVal >= 1280 * 720)  avLevel = CONST_policyAvLevel_720p;
	else  if (iVal >= 640 * 480)  avLevel = CONST_policyAvLevel_480p;
	else  if (iVal >= 320 * 240)  avLevel = CONST_policyAvLevel_240p;
	else  avLevel  =  CONST_policyAvLevel_256x144;

	//
	return  avLevel;

}



//  2014/11/20
 int  dlgTalk_procTask_transferAvInfo(  HWND  hCurTalk,  DLG_TALK_var  *  pCurVar,  HWND  hMgr,  DLG_TALK_var  *  pMgrVar,  int  iTaskId,  unsigned  short  usOp,  LPCTSTR  paramStrBuf,  
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
	 
	 //
	 unsigned  char					ucbGot_iIndex_sharedObj_localAv		=	FALSE;


	 if  (  !pParam  )  return  -1;
	 if  (  !pMsgTask)  {
		 return -1;
	 }
	 //
	 if  (  rcd.uiContentType  !=   CONST_imCommType_transferAvInfo  )  return  -1;

	 //
	 if  (  pQyMc->appParams.bNoAcceptAv  )  {
		 showInfo_open0(  0,  0,  _T(  "dlgTalk_procTask_transferAvInfo denied, bNoAcceptAv is true"  )  );
		 return  -1;
	 }	 
	 		
	 //
	 
	



	 //	
	 int iIndex_taskInfo = -1;
		
	 iIndex_taskInfo=getQmcTaskInfoIndexBySth(pProcInfo,iTaskId);	
	 if  (  iIndex_taskInfo  <  0  ) {
				iIndex_taskInfo = newTaskInfoIndex(pProcInfo, CONST_taskDataType_conf,hMgr, iTaskId,  _T(  "dlgTalk_procTask_transferAvInfo"  )  );
				if (iIndex_taskInfo < 0)
				{
					traceLogA(  (char*)"dlgTalk_procTask_transferAvInfo failed, index_taskInfo <0");
					goto errLabel;
				}
				QMC_TASK_INFO *pTaskInfo=(QMC_TASK_INFO *)getQmcTaskInfoByIndex(pProcInfo,iIndex_taskInfo);
				int tmpLen=offsetof(MIS_MSG_TASK,data ) + pMsgTask->lenInBytes;
				memcpy(  &pTaskInfo->var.pTaskData->msgU.task,pMsgTask,  tmpLen  );				
			
	 }
	 //
	 if (!qmcTaskInfo_bAlive(pProcInfo, iIndex_taskInfo)) {
		 showInfo_open0(0, mynull, _T("dlgTalk_procTask_transferAvInfo failed, qmcTaskInfo_bAlive false"));		 
		 goto  errLabel;
	 }
	 //	
	 QMC_TASK_INFO* pTaskInfo; pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, iIndex_taskInfo);
	 //
	 if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  {
		 goto  errLabel;
	 }
	 QMC_taskData_conf* pTc; pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
	 //
	 pMsgTask=&pTaskInfo->var.pTaskData->msgU.task;
	 if(pMsgTask->uiType!=CONST_misMsgType_task) {	
		 goto errLabel;			
	 }
	 if  (  pMsgTask->iTaskId!=iTaskId ) {
		 return -1;
	 }
	 pContent  =  (  IM_CONTENTU  *  )pMsgTask->data.buf;

	 //
	 if (pContent->uiType == CONST_imCommType_transferAvInfo) {
	 
		 //判断只有专用才加处理
		 if (pQyMc->appParams.bSmZy) {
			 if(pContent->transferAvInfo.confCfg.hgInfo.iMeetingType_hg != 2){
		
			 if (!pProcInfo->legal_info.isOk) {
				 int time_curr = myGetTickCount(mynull);
				 if (abs(time_curr - pProcInfo->legal_info.nTimes_last) < MAX_pipeCli_idleInMs) {
					 return -1;
				 }
				 //
				 legal_initiation(m_var.addr.idInfo.ui64Id);
				 pProcInfo->legal_info.nTimes_last = time_curr;
				 return -1;
			 }

			 if (!pProcInfo->legal_info.bLegal) {

				 if (!pProcInfo->legal_info.bLog) {
					 //
					 TCHAR  tBuf[256];  tBuf[0] = 0;
#if  0
					 _sntprintf(tBuf, mycountof(tBuf), _T("终端名:%s，终端用户:%s 违规进入会议号为%d的会议，已拦截"), pProcInfo->av.confLayout.login_termialName, pProcInfo->av.confLayout.login_userName, m_var.addr.idInfo.ui64Id);
#endif 
					 //
					 qmcLogForHg(0, tBuf, true);
					 //
					 pProcInfo->legal_info.bLog = true;
				 }

				 //return -1;
			 }
			 }

		 }
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
					  //
					  BOOL						bFirstUsr						=	FALSE;
					  SHARED_OBJ_USR		*	pSharedObjUsr					=	NULL;
					  TALKER_policy				talkerPolicy;
					  
					  //
					  CAP_procInfo_video* pCapBmp = NULL;
					  CAP_procInfo_audioCommon* pCapAudio = NULL;


					  //
					  if  (  pContent->uiType  !=  CONST_imCommType_transferAvInfo  )  goto  errLabel;
					  int level_reply  =  getAvLevel_reply(  &pContent->transferAvInfo  );
					  

					  //  2011/08/08
					  AV_COMPRESSOR_CFG		avCompressor_reply;		//  响应要取得compressor, 目前只有av才有需要. 2012/02/16
					  //  if  (  myGetAvCompressorCfg(  CONST_capType_av,  0,  CONST_capUsage_conf,  0,  &avCompressor_reply  )  )  goto  errLabel;
					  if  (  myGetAvCompressorCfg(  CONST_capType_av,  0,  0,  level_reply,  &avCompressor_reply  )  )  goto  errLabel;	//  2014/08/15


					  //  2017/08/08
					  #if  1  //  for compatibility
						   if  (  rcd.uiType  ==  CONST_imTaskType_transferAvInfo  )  {
						  	   if  (  !pContent->transferAvInfo.confCfg.ucbVideoConference  )  {
								   if  (  pMgrVar->addr.uiObjType  ==  CONST_objType_imGrp  )  {
									   pContent->transferAvInfo.confCfg.ucbVideoConference  =  TRUE;							
								   }						  
							   }					  
						   }
					  #endif

					  //  2016/04/17
					  //  2014/08/15
					  if  (  //  pMgrVar->addr.uiObjType  ==  CONST_objType_imGrp						  
						  (  rcd.uiType  ==  CONST_imTaskType_transferAvInfo
							  ||  rcd.uiType  ==  CONST_imTaskType_shareDevice_grp  
							  )
						  &&  pContent->transferAvInfo.confCfg.ucbVideoConference   
						  )
					  {
						  int  iWidth_pic_real  =  min(  avCompressor_reply.video.common.iWidth_pic,  pContent->transferAvInfo.confCfg.conf.iWidth_pic_conf  );
						  int  iHeight_pic_real  =  min(  avCompressor_reply.video.common.iHeight_pic,  pContent->transferAvInfo.confCfg.conf.iHeight_pic_conf  );
						  //
						  int  level_real  =  getAvLevelByWh(  iWidth_pic_real,  iHeight_pic_real  );
						  if  (  myGetAvCompressorCfg(  CONST_capType_av,  0,  0,  level_real,  &avCompressor_reply  )  )  {
							  showInfo_open0(  0,  0,  _T(  "dlgTalk_procTask_transferAvInfo failed, myGetAvCompressorCfg failed. real"  )  );
							  goto  errLabel;	//  2014/08/15
						  }

						  //
						  pTc->bResizeToPlay = false;
						  if (level_real <= CONST_policyAvLevel_848x480
							  && bSupported_aiResize())
						  {
#if  10
							  pTc->bResizeToPlay = true;
#endif
							  //
						  }		
						  
						  //
						  if  (  pContent->transferAvInfo.confCfg.ucbVideoConference  )  {
							  //
							  //
							  set_conf_iFourcc(pContent->transferAvInfo.confCfg.conf.conf_iFourcc, pContent->transferAvInfo.confCfg.conf.conf_bitrateInKbps_ul,&avCompressor_reply);
						  }

						  //
						  //
						  //
						  TCHAR  tBuf[128];
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "compressor of reply: %dX%d %dfps bitrate %d"  ),  avCompressor_reply.video.common.iWidth_pic,  avCompressor_reply.video.common.iHeight_pic,  (  int  )avCompressor_reply.video.common.usMaxFps_toShareBmp,  avCompressor_reply.video.common.iAvgBitrate  );
						  showInfo_open0(  0,  0,  tBuf  );
					  }
					  else {

						  //
						  //
						  set_conf_iFourcc(pContent->transferAvInfo.ass.tranInfo.video.vh_stream.dwFourcc, 0,  &avCompressor_reply);
					  }

					  //
					  pProcInfo->dlgTalk_confStart_pre(hMgr, pContent->transferAvInfo.confCfg.ucbVideoConference, pContent->transferAvInfo.confCfg.conf.conf_ucb100k, _T("l388"));
					  adjustAudioBitrate(&avCompressor_reply.audio.common);

					  //
					  if (pContent->transferAvInfo.confCfg.conf.conf_ucAudioCompressors) {

						  switch (pContent->transferAvInfo.confCfg.conf.conf_ucAudioCompressors) {
						  case  CONST_audioCompressors_lyra:
							  avCompressor_reply.audio.common.ucCompressors = CONST_audioCompressors_lyra;
							  break;
						  defualt:
							  break;
						  }

					  }

					  //
					  if (level_reply == CONST_policyAvLevel_256x144) {
						  avCompressor_reply.audio.common.ucCompressors = CONST_audioCompressors_lyra;
					  }

					  // 为了测试100k的临时设置
					  if (pContent->transferAvInfo.confCfg.conf.conf_ucb100k  )
					  {
						  avCompressor_reply.audio.common.ucCompressors = CONST_audioCompressors_lyra;

						  avCompressor_reply.video.common.iAvgBitrate = 40  *  1000;
					  }

					  
					  //
					  getTalkerPolicy(  &m_var.addr.idInfo,  &talkerPolicy  );
					  //
					  //m_var.m_layout.ucbNeverJoinInBgWall  =  talkerPolicy.ucbNeverJoinInBgWall;
					  //
					  //m_var.m_layout.usPollingIntervalInS1  =  pShadowMgr->bgWall.bgWallCfg.usPollingIntervalInS;
					  m_var.m_layout.bgWallLayoutCfg.usRows_bg  =  pShadowMgr->bgWall.bgWallCfg.bgWallLayoutCfg.usRows_bg;
					  m_var.m_layout.bgWallLayoutCfg.usCols_bg  =  pShadowMgr->bgWall.bgWallCfg.bgWallLayoutCfg.usCols_bg;
					  //					
					  if  (  rcd.uiContentType  ==  CONST_imCommType_transferAvInfo  )  {
								
								if  (  rcd.uiType  ==  CONST_imTaskType_transferAvInfo
									||  rcd.uiType  ==  CONST_imTaskType_shareDevice_grp  )  
								{
									if  (  m_var.av.taskInfo.bTaskExists  )  {
										qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "av is already active"  )  );
										goto  errLabel;
									}
								}

								//
								TCHAR  tBuf[128];
								_sntprintf(tBuf, mycountof(tBuf), _T("dlgTalk_procTask_av: taskType %d"), rcd.uiType);
								showInfo_open0(0, 0, tBuf);

								//  
								//  chkMsgrs_sendLocalAv(  pDlg->m_var.pProcInfo  );

								//
								if  (  usOp  ==  CONST_imOp_dual_permit  )  {									
									ucbSendLocalAv  =  TRUE;					
								
									CQySyncObj	syncObj;
									if  (  syncObj.sync(  pProcInfo->cfg.mutexName_syncStartAv  )  )  goto  errLabel;

									//
									if (rcd.uiType == CONST_imTaskType_transferAvInfo) {
										if (getNewSharedObjUsr_localAv(pProcInfo, hDlgTalk, &iIndex_sharedObj, &iIndex_sharedObjUsr, &bFirstUsr)) {
											//
											TCHAR  tHint[128];
											HWND  hParent = hCurTalk;
											//
											_sntprintf(tHint, mycountof(tHint), getResStr(0, &pQyMc->cusRes, CONST_resId_notAcceptAv));
											showInfo_open0(0, 0, tHint);
											showNotification_open(0, 0, 0, tHint);
											//
											if (pParam->bManualCmd) {
												if (pParam->hParent)  hParent = pParam->hParent;
												myMessageBox(hParent, tHint, _T("www.qycx.com"), MB_OK);
											}
											//
											goto  errLabel;
										}
									}
									else  if (rcd.uiType == CONST_imTaskType_shareDevice_grp) {
											 iIndex_sharedObj = newSharedObjIndex(pProcInfo, hDlgTalk, CONST_sharedObjType_mediaDevice, &iIndex_sharedObjUsr, &bFirstUsr);
											 if (iIndex_sharedObj < 0) {
												 showInfo_open0(0, 0, _T("dlgTalk_procTask_av failed: shareDevice_grp: newSharedObjIndex returns <0"));
												 goto  errLabel;
											 }
									}
									else {
										 #ifdef  __DEBUG__
												 traceLog((TCHAR*)_T("dlgTalk_procTask_av: unprocessed taskType %d"),  rcd.uiType);
										 #endif		
									}
									//
									if (!(pSharedObj = getSharedObjByIndex(pProcInfo, iIndex_sharedObj))) {
										traceLog((TCHAR*)_T("dlgTalk_procTask_av failed, getSharedObjByIndex failed"));
										goto  errLabel;
									}
									m_var.av.ucbGot_iIndex_sharedObj_localAv  =  ucbGot_iIndex_sharedObj_localAv  =  TRUE;
									m_var.av.iIndex_sharedObj_localAv  =  iIndex_sharedObj;
									m_var.av.iIndex_usr_localAv  =  iIndex_sharedObjUsr;
									//
									pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  m_var.av.iIndex_usr_localAv  );
									if  (  !pSharedObjUsr  )  goto  errLabel;

									//
									setCurSharedObjUsr_localAv(pProcInfo, iIndex_sharedObj, iIndex_sharedObjUsr);

									//
									if  (  bFirstUsr  )  {
										#ifndef  __noMfc__
												 //CWaitCursor		cur;
										#endif

										//
										int						iIndex_capBmp					=	-1;	
										int						iIndex_capAudio					=	-1;
#if  0
										int						iIndex_shmCmd					=	-1;
										QM_SHM_CMD			*	pShmCmd							=	NULL;
#endif

										//
										iIndex_capBmp  =  newCapProcInfoBmpIndex(  pProcInfo,  iIndex_sharedObj  );
										pCapBmp  =  (  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );
										if  (  !pCapBmp  )  goto  errLabel;
										pCapBmp->uiType  =  CONST_capType_av;
										pCapBmp->iIndex_sharedObj  =  iIndex_sharedObj;
										pCapBmp->uiTranNo_sharedObj  =  pSharedObj->uiTranNo;
										//  pCompressVideo  =  &pCapBmp->compressVideo;
										//  2010/12/29
										memset(  &pCapBmp->compressVideo.debugInfo,  0,  sizeof(  pCapBmp->compressVideo.debugInfo  )  );
										mytime(  &pCapBmp->compressVideo.debugInfo.tStart  );
										pCapBmp->compressVideo.debugInfo.nStep  =  1;
										//
										iIndex_capAudio  =  newCapProcInfoAudioIndex(  pProcInfo,  iIndex_sharedObj  );
										pCapAudio  =  (  CAP_procInfo_audioCommon  *  )getCapAudioBySth(  pProcInfo,  iIndex_capAudio,  0  );
										if  (  !pCapAudio  )  goto  errLabel;
										pCapAudio->uiType  =  CONST_capType_av;
										pCapAudio->iIndex_sharedObj  =  iIndex_sharedObj;
										pCapAudio->uiTranNo_sharedObj  =  pSharedObj->uiTranNo;
										//  pCompressAudio  =  &pCapAudio->compressAudio;
										//
										//
#if  0
										iIndex_shmCmd  =  newShmCmdIndex(  pProcInfo,  iIndex_sharedObj  );
										pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  iIndex_shmCmd  );
										if  (  !pShmCmd  )  goto  errLabel;
#endif
									
										//
										pSharedObj->iIndex_capBmp  =  iIndex_capBmp;
										pSharedObj->iIndex_capAudio  =  iIndex_capAudio;
										//pSharedObj->iIndex_shmCmd  =  iIndex_shmCmd;


										if  (  rcd.uiType  ==  CONST_imTaskType_transferAvInfo  )
										{	  //  老的工作模式. 2013/03/19
											
											//
											if  (  1  )  {
												AUDIO_COMPRESSOR_CFG	*	pAudioCompressor	=	NULL;

												//  2011/08/08
												pAudioCompressor  =  &avCompressor_reply.audio;

												//  2013/08/03
												//
												TCHAR	displayName[MAX_monikerDisplayNameLen  +  1]  =  _T(  ""  );
												if  (  m_var.bIncludeACap  )  {				
													getMonikerDisplayName(  getMoniker_a(  m_var.pCapStuff,  m_var.iMenuId_selectedAudio  ),  displayName,  mycountof(  displayName  )  );				
												}
												TCHAR  capDevDesc[64]  =  _T(  ""  );
												void  *  pADev  =  m_var.bIncludeACap  ?    displayName  :  getADeviceGuid(  m_var.pCapStuff,  m_var.iMenuId_selectedAudio,  capDevDesc,  mycountof(  capDevDesc  )  );
												
												//
												unsigned  short  usMaxSpeakers = pContent->transferAvInfo.confCfg.usMaxSpeakers;
												unsigned  short  usCntLimit_activeMems_from = 0;
												//
												calc_conf_param(pContent->transferAvInfo.confCfg.ucbVideoConference, rcd.uiType, &usMaxSpeakers, &usCntLimit_activeMems_from);

												//
												int  n_aDevices  =  get_iNumADevices(m_var.pCapStuff);
												if (!n_aDevices) {
													TCHAR  tBuf[256];
													_sntprintf(tBuf, mycountof(tBuf), _T("%s：全向麦设备异常"), pProcInfo->av.confLayout.login_termialName);

													qmcLogForHg(0, tBuf, true);
												}

												//
												if (pContent->transferAvInfo.confCfg.conf.conf_ucb100k) {
													pAudioCompressor->common.iAvgBitrateInKbps = 24;// 16;
												}


												//  2008/4/17, 
												if  (  !startLocalAudioRecorder(  pQyMc,  pProcInfo->cfg.policy.audio.uiRecordType,  pADev,  capDevDesc,  iIndex_sharedObj,  usCntLimit_activeMems_from,  pAudioCompressor  )  )  {
													//  m_var.av.ucbLocalAudioRecorderStarted  =  TRUE;
												}
												else {
													//
													if (1) {
														TCHAR  tBuf[256];
														_sntprintf(tBuf, mycountof(tBuf), _T("%s：全向麦设备异常"), pProcInfo->av.confLayout.login_termialName);

														qmcLogForHg(0, tBuf, true);
													}
												}
											}

											//
											//showInfo_open0(0, 0, _T("dlgTalk_procTask_av: before openLocalVideo"));

											//
											if  (  !(  m_var.pMisCnt->imRules.conferenceId_shareWebcam.ui64Id
													&&  m_var.pMisCnt->imRules.conferenceId_shareWebcam.ui64Id  ==  m_var.addr.idInfo.ui64Id  
													&&  m_var.pMisCnt->imRules.ucbNoLocalVideoInThisConference  
													)													
													&&  pQyMc->iCustomId  !=  CONST_qyCustomId_hzj
												)  
											{
												//
												VIDEO_COMPRESSOR_CFG	videoCompressor;
												memcpy(  &videoCompressor,  &avCompressor_reply.video,  sizeof(  videoCompressor  )  );
												if  (  pContent->transferAvInfo.confCfg.conf.usMaxFps_toShareBmp_conf  )  videoCompressor.common.usMaxFps_toShareBmp  =  min(  videoCompressor.common.usMaxFps_toShareBmp,  pContent->transferAvInfo.confCfg.conf.usMaxFps_toShareBmp_conf  );
												//  2014/08/15
												if  (  pContent->transferAvInfo.confCfg.conf.iWidth_pic_conf  )  videoCompressor.common.iWidth_pic  =  min(  videoCompressor.common.iWidth_pic,  pContent->transferAvInfo.confCfg.conf.iWidth_pic_conf  );
												if  (  pContent->transferAvInfo.confCfg.conf.iHeight_pic_conf  )  videoCompressor.common.iHeight_pic  =  min(  videoCompressor.common.iHeight_pic,  pContent->transferAvInfo.confCfg.conf.iHeight_pic_conf  );
												//
												videoCompressor.common.usMaxFps_toShareBmp = min(CONST_fps_video, videoCompressor.common.usMaxFps_toShareBmp);

												//
												if (pContent->transferAvInfo.confCfg.hgInfo.bFlow512k) {
													videoCompressor.common.iAvgBitrate = 512000;
												}


#ifdef  __DEBUG__
												//videoCompressor.common.iAvgBitrate = 2000000;
#endif


												//  2015/10/11												
												if  (  newstartQThreadToShareAv(  pProcInfo,  iIndex_sharedObj,  FALSE  )  )  goto  errLabel;

												
												//  								
												if  (  !pProcInfo->av.localAv.videoCaptureProcInfo.bCapDevConnected  )  {	
										
													//
													_sntprintf(  tBuf,  mycountof(  tBuf),  _T("dlgTalk_procTask_av: before openLocalVideo 2: camCapType %d"),  pProcInfo->cfg.policy.video.uiCamCapType);
													showInfo_open0(0, 0, tBuf);


													//
													#ifndef  __noMfc__
															 //CWaitCursor		cur;
													#endif
						
													if  (  pProcInfo->cfg.policy.video.uiCamCapType  ==  CONST_camCapType_rtsp  )  {		//  2014/02/23					  					  
												#if  10
						
														//  2014/03/15
														int  size  =  sizeof(  TRANSINFO_stream  );		
														if  (  !pSharedObj->pTransInfo_stream  )  {
															pSharedObj->pTransInfo_stream  =  mymalloc(  size  );
															if  (  !pSharedObj->pTransInfo_stream  )  goto  errLabel;
															memset(  pSharedObj->pTransInfo_stream,  0,  size  );					  		
															//
															TRANSINFO_stream  *  pTransInfo  =  (  TRANSINFO_stream  *  )pSharedObj->pTransInfo_stream;

															{
																void* pDb = NULL;
#ifndef  __NOTSUPPORT_DB__
																CQnmDb		db;
																if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
																pDb = db.m_pDbMem->pDb;
#endif
																int  tmp_iTaskId;

																tmp_iTaskId = newTaskId(pDb, pQyMc->cfg.db.iDbType);
																pTransInfo->iTaskId = tmp_iTaskId;

															}

															pTransInfo->index_taskInfo = newTaskInfoIndex(pProcInfo, CONST_taskDataType_conf, hCurTalk, pTransInfo->iTaskId, _T(""));
															if (pTransInfo->index_taskInfo < 0) {
																showInfo_open0(0, 0, _T("CONST_imTaskType_transferAvInfo: for rtsp: newTaskInfoIndex failed"));
																goto  errLabel;
															}
																														//
															pTransInfo->myTask.iIndex_taskInfo = pTransInfo->index_taskInfo;
															//
															pTransInfo->myTask.ucbLocalSource_rtspStream  =  TRUE;
															//
															pTransInfo->myTask.usCntLimit_transforms  =  1;
															if  (  initTransforms(  pProcInfo,  &pTransInfo->addr_logicalPeer,  0,  0,  &pTransInfo->tranInfo,  &pTransInfo->myTask,  NULL  )  )  goto  errLabel;



#ifdef  __DEBUG__
															safeTcsnCpy(_T("hhh"), pTransInfo->myTask.debugHint, mycountof(pTransInfo->myTask.debugHint));
															pTransInfo->myTask.pTransforms[0].dwLastTickCnt_doApplyForPlayer_a = 987;
#endif 
															//
															QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, pTransInfo->index_taskInfo);
															if (!pTaskInfo)  goto  errLabel;
															QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
															pTc->videoConference.usCntLimit_activeMems_from = 1;


															//
#if 10
															pTransInfo->myTask.usCntLimit_mems_from = 1;
															size = sizeof(TASK_AV_FROM) * pTransInfo->myTask.usCntLimit_mems_from;
															pTransInfo->myTask.pMems_from = (TASK_AV_FROM*)mymalloc(size);
															if (!pTransInfo->myTask.pMems_from)  goto  errLabel;
															memset(pTransInfo->myTask.pMems_from, 0, size);
#endif 
															//
#if  0
															pTransInfo->myTask.usCntLimit_mems_from  =  1;
															size  =  sizeof(  TASK_AV_FROM  )  *  pTransInfo->myTask.usCntLimit_mems_from;
															pTransInfo->myTask.pMems_from  =  (  TASK_AV_FROM  *  )mymalloc(  size  );
															if  (  !pTransInfo->myTask.pMems_from  )  goto  errLabel;
															memset(  pTransInfo->myTask.pMems_from,  0,  size  );						 
#endif 
														}
						  
														//						  
														TCHAR  url[256]  =  _T(  ""  );	//  _T(  "rtsp://127.0.0.1:8554/video.264"  );
														QY_REG  reg;
														reg.hKeyRoot0  =  HKEY_CURRENT_USER;
														lstrcpyn(  reg.rootKey,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  sizeof(  reg.rootKey  )  );
														
														if  (  qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_rtspUrl_selected  ),  (  char  *  )url,  sizeof(  url  ),  0  )  )  {
															qyShowInfo1(  CONST_qyShowType_warning,  0, (char*) (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doCmd_startAvCall: rtsp url is wrong!"  )  );
															url[0]  =  0;
														}																				  
														//  2014/12/12. for test
														if  (  pQyMc->appParams.rtspUrl[0]  )  {
															safeTcsnCpy(  pQyMc->appParams.rtspUrl,  url,  mycountof(  url  )  );							  
															showInfo_open0(  0,  0,  CQyString(  _T(  "TEST: dlgTalk_procTask_transferAvInfo: use rtsp url: "  )  )  +  url  );						  
														}
														//
														if  (  !openLocalVideo_rtsp(  (  MC_VAR_common  *  )pProcInfo,  url,  &videoCompressor,  iIndex_sharedObj  )  )  {													  
															//  m_var.av.u.av.uc.ucbLocalVideoOpen  =  TRUE;										  
														}
													#endif
														}
													else  {

															 TCHAR	displayName[MAX_monikerDisplayNameLen  +  1]	=	_T(  ""  );	
															 
															 
															 //
															 //getChosenDevice(null, 0, displayName, mycountof(displayName), 0, 0, 0, 0);
															 if (!pProcInfo->getChosenCamera(displayName, mycountof(displayName))) {
																 if (!displayName[0]) {
																	 if (getMonikerDisplayName(getMoniker_v(m_var.pCapStuff, m_var.iMenuId_selectedVideo), displayName, mycountof(displayName)))  displayName[0] = 0;
																 }
															 }
															 
															 //
															 dumpAvDevs(pMgrVar->pCapStuff);															 

															 //
															 _sntprintf(tBuf, mycountof(tBuf), _T("dlgTalk_procTask_av: chosenCamera [%s]"), displayName);
															 showInfo_open0(0, 0, tBuf);

															 //
															 //int  tmpiRet  =  openLocalVideo(  (  MC_VAR_common  *  )pProcInfo,  pProcInfo->cfg.policy.video.uiCamCapType,  displayName,  NULL,  &videoCompressor,  iIndex_sharedObj  );
															 int  tmpiRet  =  openLocalVideo(  (  MC_VAR_common  *  )pProcInfo,  pProcInfo->cfg.policy.video.uiCamCapType,  displayName,  &pMgrVar->pCapStuff,  &videoCompressor,  iIndex_sharedObj  );
															 //
															 if  (  !tmpiRet  )  {
																  //  m_var.av.ucbLocalVideoOpen  =  TRUE;  																		
															 }
															 else {
																 int  ii = 0;

																 //
																 TCHAR  tBuf[256];
																 _sntprintf(tBuf, mycountof(tBuf), _T("%s：摄像头设备异常"), pProcInfo->av.confLayout.login_termialName);


																 qmcLogForHg(0, tBuf, true);
															 }
															 //
															 if (!pMgrVar->pCapStuff)  dlgTalk_make_capStuff(hMgr, pMgrVar);

													}

													//
															 
															 #ifdef  __DEBUG__
																	 //  if  (  !m_var.av.ucbLocalVideoOpen  )  traceLogA(  (char*)  "procQmInternalUrl: openLocalVideo failed."  );																		 
															 #endif
												}									
												if  (  pProcInfo->av.localAv.videoCaptureProcInfo.bCapDevConnected  )  {							
													pProcInfo->av.localAv.videoCaptureProcInfo.curhWnd  =  hDlgTalk;

													//
													//  2014/09/23. 建立多流
													int  level  =  0;
													if  (  makeSlaveStream(  pQyMc,  hDlgTalk,  iIndex_sharedObj,  level,  pContent->transferAvInfo.confCfg.conf.conf_iFourcc  )  )  goto  errLabel;
													
													//													
													//startCapture(  pProcInfo,  &pProcInfo->av.localAv.videoCaptureProcInfo  );													

												}
											
											}

											}
										else  if (rcd.uiType == CONST_imTaskType_shareDevice_grp) {
												 //int
												 int  ii = 0;
												 //  2009/12/07	
												 if (newstartQThreadToShareAv(pProcInfo, iIndex_sharedObj, TRUE)) {
#ifdef  __DEBUG__
													 traceLog((TCHAR*)_T("doCmd_startShareMediaDevice, startQThreadToShareAv failed"));
#endif
													 goto  errLabel;
												 }


												 //
												 //uiTaskType = CONST_imTaskType_shareMediaFile;
												 //  2015/03/11
												 TASK_av_props  taskAvProps;
												 memset(&taskAvProps, 0, sizeof(taskAvProps));
												 //
#if  0
												 if (uiSubCapType == CONST_subCapType_unresizable) {
													 taskAvProps.v.ucAvFlg |= CONST_avFlg_unresizable;
												 }
#endif
												 //
												 pSharedObj->taskAvProps = taskAvProps;

												 //
												 //  m_var.av.ucbSendLocalMediaFile  =  TRUE;	

												 //  sizeAllControls_dlgTalk(  hDlg,  m_var,  NULL  );					//  µ÷ÕûÒ»ÏÂ²¼¾Ö

												 //  2011/08/08
												 //AV_COMPRESSOR_CFG		mediaDeviceCompressor;
												 //if (myGetAvCompressorCfg(CONST_capType_mediaDevice, uiSubCapType, 0, level, &mediaDeviceCompressor))  goto  errLabel;

												 AV_COMPRESSOR_CFG* pCompressor = &avCompressor_reply;// &mediaDeviceCompressor;
												 //
												 refreshWebCamSettings(&pCompressor->video, pCapBmp);

												 //
												 int  conf_iFourcc = get_conf_iFourcc();
												 //
												 conf_iFourcc = fourccStr2i(pCompressor->video.common.fourccStr);
												 //
												 int conf_bitrateInKbps = 0;
												 //
												 set_conf_iFourcc(conf_iFourcc, conf_bitrateInKbps, pCompressor);
												 //
												 pCompressor->video.common.usMaxFps_toShareBmp = min(pCompressor->video.common.usMaxFps_toShareBmp, CONST_fps_shareMediaDevice);

												 //
												 //void* pCapStuff = pMgrVar->pCapStuff;
												 void** ppCapStuff = &pMgrVar->pCapStuff;
												 unsigned  int  uiCapType = 0;

												 //
														//
#ifdef  __DEBUG__
												 printAvDevs(*ppCapStuff);
#endif
												 //
												 TCHAR  dev_sel[128] = _T("USB Video Device");

#define		CONST_cfgName_shareDev				_T(  "shareDev")

												 TCHAR  tCfgName[128];
												 _sntprintf(tCfgName, mycountof(tCfgName), _T("%s%d"), CONST_cfgName_shareDev, pContent->transferAvInfo.shareDevice_grp_index);
												 //
												 //USB Video Device
												 getCfgValByNameT(pQyMc->cfg.smCfgFile, (TCHAR*)tCfgName, dev_sel, mycountof(dev_sel));
												 tTrim(dev_sel);

												 //
												 showInfo_open0(0, 0, _T("shareDevice_grp: before selectAvDev"));

												 //
												 if (selectAvDev(*ppCapStuff, dev_sel, dev_sel)) {
													 goto  errLabel;
												 }




												 //
												 BOOL	bAudio = CAP_STUFF_bAudio(*ppCapStuff);
												 BOOL	bVideo = CAP_STUFF_bVideo(*ppCapStuff);

												 //
												 int  tmpiRet = initShareMediaDevice(ppCapStuff, &pCompressor->audio, &pCapBmp->policy.bih, pQyMc->gui.hMainWnd, iIndex_sharedObj, &pSharedObj->pShareMediaObj);
												 //
												 if (!pMgrVar->pCapStuff)  dlgTalk_make_capStuff(hMgr, pMgrVar);
												 //
												 if  (  tmpiRet  )  goto  errLabel;
												 //  pCapBmp->bCapDevConnected  =  TRUE;	//  2012/02/24

												 //  
												 if (!bGetCapturePara_shareMediaDevice((MC_VAR_common*)pProcInfo, iIndex_capAudio, iIndex_capBmp, pSharedObj->pShareMediaObj, &pCapAudio->wf_org, &pCapBmp->vh_org, NULL))  goto  errLabel;


												 //
												 COMPRESS_AUDIO* pCompressAudio = &pCapAudio->compressAudio;
												 COMPRESS_VIDEO  *  pCompressVideo = &pCapBmp->compressVideo;


												 //
												 if (bVideo) {
													 CAP_procInfo_mediaDeviceBmp* pVc = pCapBmp;

													 //
													 if (pVc->vh_org.bih.biCompression != BI_RGB || pVc->vh_org.bih.biBitCount != 24) {
														 if (initOrg2RgbBuf((MC_VAR_common*)pProcInfo, (CAP_procInfo_bmpCommon*)pVc)) {
															 traceLogA((char*)"initOrg2RgbBuf failed.");
															 goto  errLabel;
														 }
													 }

													 QY_VIDEO_HEADER* pVh_rgb;
													 pVh_rgb = pVc->bOrg2RgbBufInited ? &pVc->vh_rgb : &pVc->vh_org;
													 //
													 //  2014/04/03
													 pCompressor->video.common.pVideoQ2 = &pVc->thread.q2;
													 pCompressor->video.common.pParent_transform = pVc;
													 //
													 if (initCompressVideo(pProcInfo, (BITMAPINFO*)&pVh_rgb->bih, uiCapType, &pCompressor->video, FALSE, 0, pCompressVideo)) {
														 showNotification(NULL, 0, 0, 0, 0, 0, _T("Initialize video compress failed!"));
														 goto  errLabel;
													 }
												 }

												 if (bAudio) {
													 AUDIO_COMPRESSOR_CFG	audioCompressor;
													 if (pCompressor->audio.common.ucCompressors == CONST_audioCompressors_acm) {
														 memcpy(&audioCompressor, &pCompressor->audio, sizeof(audioCompressor));
													 }
													 else {
														 memset(&audioCompressor, 0, sizeof(audioCompressor));
														 //  audioCompressor.ucCompressors  =  pCompressor->audio.ucCompressors;
														 memcpy(&audioCompressor, &pCompressor->audio, sizeof(audioCompressor));
														 memcpy(&audioCompressor.wf_decompress_default, &pCapAudio->wf_org, sizeof(audioCompressor.wf_decompress_default));
														 //
														 memset(&audioCompressor.wf_compress, 0, sizeof(audioCompressor.wf_compress));	//  2011/02/02
														 audioCompressor.wf_compress.wFormatTag = pCompressor->audio.wf_compress.wFormatTag;
														 audioCompressor.wf_compress.nChannels = pCapAudio->wf_org.nChannels;
														 audioCompressor.wf_compress.nSamplesPerSec = pCapAudio->wf_org.nSamplesPerSec;
														 audioCompressor.wf_compress.wBitsPerSample = pCapAudio->wf_org.wBitsPerSample;
													 }
													 //
													 //  2016/12/10
													 AUDIO_COMPRESSOR_CFG* pCompressor = &audioCompressor;
													 pCompressor->common.pAudioQ2 = &pCapAudio->thread.q2;
													 pCompressor->common.pParent_transform = pCapAudio;
													 //
													 if (initCompressAudio(pProcInfo, &pCapAudio->wf_org, &audioCompressor, pCompressAudio)) {
														 showNotification(NULL, 0, 0, 0, 0, 0, _T("Initialize audio compress failed!"));
														 goto  errLabel;
													 }
												 }

												 //
												 pCapBmp->curhWnd = hDlgTalk;

												 if (!bVideo)  pCompressVideo = NULL;
												 if (!bAudio)  pCompressAudio = NULL;

												 //

												 //
												 SHARED_OBJ_USR* pSharedObjUsr;
												 pSharedObjUsr = getSharedObjUsr(pSharedObj, iIndex_sharedObjUsr);
												 if (!pSharedObjUsr)  goto  errLabel;
												 //	

												 if (pCompressAudio && pCompressAudio->uiTranNo_openAvDev_org) {
													 pSharedObjUsr->uiTranNo_openAvDev_a = pCompressAudio->uiTranNo_openAvDev_org + iIndex_sharedObjUsr;	//  pSharedObj->iIndex_curUsr;
												 }

												 if (pCompressVideo && pCompressVideo->uiTranNo_openAvDev_org) {	//  
													 pSharedObjUsr->uiTranNo_openAvDev_v = pCompressVideo->uiTranNo_openAvDev_org + iIndex_sharedObjUsr;	//  pSharedObj->iIndex_curUsr;
												 }
												 pSharedObjUsr->iTaskId = iTaskId;

												 												 
												 //  2010/09/09
												 setCurSharedObjUsr(pProcInfo, iIndex_sharedObj, iIndex_sharedObjUsr);

												 //  2014/11/16
												 //pProcInfo->setFlg_inConfMosaic(hDlgTalk, iWndContentType, iIndex_sharedObj, iIndex_sharedObjUsr);

												 //
												 if (m_var.av.taskInfo.ucbStarter) {
													 goto  errLabel;
												 }


												 
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

												 
												 //
												 if (runShareMediaDevice(pSharedObj->pShareMediaObj))  goto  errLabel;


										}
										else {
											traceLog((TCHAR*)_T(  "dlgTalk_procTask_av: unprocessed rcd.uiType")  );
										}

									}

									//
									pProcInfo->av.localAv.idInfo_curConference.ui64Id = pMgrVar->addr.idInfo.ui64Id;


									//  2017/09/17
									dlgTalk_init_respInfo(  hMgr,  pMgrVar,  pContent->transferAvInfo.confCfg.ucbVideoConference  );  

									//  2010/09/04
									COMPRESS_AUDIO* pCompressAudio = &pCapAudio->compressAudio;// pProcInfo->av.localAv.recordSoundProcInfo.compressAudio;
									COMPRESS_VIDEO* pCompressVideo = &pCapBmp->compressVideo;// pProcInfo->av.localAv.videoCaptureProcInfo.compressVideo;

									if  (  pCompressAudio->uiTranNo_openAvDev_org  )  {
										pSharedObjUsr->uiTranNo_openAvDev_a  =  pCompressAudio->uiTranNo_openAvDev_org  +  iIndex_sharedObjUsr;	//  pSharedObj->iIndex_curUsr;
									}
									if  (  pCompressVideo->uiTranNo_openAvDev_org  )  {
										pSharedObjUsr->uiTranNo_openAvDev_v  =  pCompressVideo->uiTranNo_openAvDev_org  +  iIndex_sharedObjUsr;	//  pSharedObj->iIndex_curUsr;
									}

									//
									//  2016/03/28
									if  (  bExists_slave(  pProcInfo,  iIndex_sharedObj  )  )  {
																			
										int  iIndex_sharedObj_slave;										
										iIndex_sharedObj_slave  =  pSharedObj->master.slaveKey.iIndex_sharedObj;
										//
										SHARE_dyn_bmp  *  pShareDynBmp_slave  =  (  SHARE_dyn_bmp  *  )pSharedObj->master.pShareDynBmp_slave;
										if  (  !pShareDynBmp_slave  )  goto  errLabel;
										//
										int  index_sharedObjUsr_slave  =  0;											
										if  (  getNewSharedObjUsr(  pProcInfo,  hDlgTalk,  iIndex_sharedObj_slave,  &index_sharedObjUsr_slave,  NULL  )  )  {	
											showInfo_open0(  0,  0,  _T(  "dlgTalk_procTask_transferAvInfo failed: newSharedObjUsr failed"  )  );
											goto  errLabel;											  
										}
										//
										QY_SHARED_OBJ  *  pSharedObj_slave  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj_slave  );
										if  (  !pSharedObj_slave  )  goto  errLabel;
										//
										SHARED_OBJ_USR  *  pUsr_slave  =  getSharedObjUsr(  pSharedObj_slave,  index_sharedObjUsr_slave  );
										if  (  !pUsr_slave  )  goto  errLabel;
										//
										int  iIndex_capBmp  =  pSharedObj_slave->iIndex_capBmp;
										CAP_procInfo_bmpU  *  pCapBmp  =  getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );
										if  (  !pCapBmp  )  goto  errLabel;
										COMPRESS_VIDEO  *  pCompressVideo_slave  =  &pCapBmp->common.compressVideo;
										//
										if  (  pCompressVideo_slave->uiTranNo_openAvDev_org  )  {
											pUsr_slave->uiTranNo_openAvDev_v  =  pCompressVideo_slave->uiTranNo_openAvDev_org  +  index_sharedObjUsr_slave;									
										}
										//
										pUsr_slave->iTaskId  =  pShareDynBmp_slave->var.iTaskId;

										//  2016/03/28
										_sntprintf(  pUsr_slave->tDbgHint,  mycountof(  pUsr_slave->tDbgHint  ),  _T(  "%I64u"  ),  pMgrVar->addr.idInfo.ui64Id  );


									}

								}
								
#if  0
								m_var.av.ucbRecvRemoteAudio  =  TRUE;		//  ±íÊ¾ÔÊÐí½ÓÊÕÔ¶³ÌÊÓÆµ¡£										
								m_var.av.ucbRecvRemoteVideo  =  TRUE;
#endif

								//
							    
					  }

					  //
					  //if  (  !(  pMsgTask  =  findTaskInProcessQ(  &m_var,  iTaskId,  0  )  )  )  goto  errLabel;
					  if(NULL==pMsgTask) goto errLabel;
 										  
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
					  //
					  dlgTalk_procTask_display_op_mgr(  hDlgTalk,  iTaskId,  usOp,  pMsgTask,  rcd,  iStatus_old,  iStatus,  paramStrBuf  );
					  
					  
					  //						
					  if  (  rcd.uiContentType  ==  CONST_imCommType_transferAvInfo  )  {
						  
								/*
								CQyMalloc					mallocObj_transferAvReplyInfo;
								TRANSFER_AV_reply_task	*	pTransferAvReplyInfo		=	(  TRANSFER_AV_reply_task  *  )mallocObj_transferAvReplyInfo.mallocf(  sizeof(  TRANSFER_AV_reply_task  )  );
								if  (  !pTransferAvReplyInfo  )  goto  errLabel;
							    TRANSFER_AV_reply_task	&	transferAvReplyInfo			=	*pTransferAvReplyInfo;
						  		*/
								TASK_transferAv task;
								memset(&task,0,sizeof(task));
								//
								task.m_index_taskInfo=iIndex_taskInfo;
								pTaskInfo->var.m_bReplyTask=true;
								//
								TRANSFER_AV_replyInfo transferAvReplyInfo;
								PROC_TASK_AV &transferAvReplyInfo_myTask=task.myTask;
								//  
								memset(  &transferAvReplyInfo,  0,  sizeof(  transferAvReplyInfo  )  );
								transferAvReplyInfo.uiType  =  CONST_imCommType_transferAvReplyInfo;
								//  2016/04/18
								transferAvReplyInfo.tmp_usSubtype  =  CONST_transferAvReplyInfo_subtype_task;
								//
								transferAvReplyInfo.usOp  =  CONST_imOp_recv_accept;
								transferAvReplyInfo.tStartTime_org  =  pMsgTask->tStartTime;
								transferAvReplyInfo.uiTranNo_org  =  pMsgTask->uiTranNo;
								//
								if  (  ucbSendLocalAv  )  {	//  
									COMPRESS_VIDEO* pCompressVideo = &pCapBmp->compressVideo;//  pProcInfo->av.localAv.videoCaptureProcInfo.compressVideo;
									COMPRESS_AUDIO* pCompressAudio = &pCapAudio->compressAudio;// pProcInfo->av.localAv.recordSoundProcInfo.compressAudio;

									//  2009/04/19
									if  (  pContent->transferAvInfo.confCfg.conf.usMaxFps_toShareBmp_conf  )  {
										//  pCompressVideo->usMaxFps_toShareBmp  =  min(  pContent->transferAvInfo.tranInfo.video.usMaxFps_toShareBmp_videoConference,  pCompressVideo->usMaxFps_toShareBmp  );    
										//  2009/06/04
										transferAvReplyInfo_myTask.video.usMaxFps_toShareBmp_conf  =  pCompressVideo->compressor.common.usMaxFps_toShareBmp;
									}

									//
									if  (  !pSharedObjUsr  )  goto  errLabel;
									transferAvReplyInfo.tranInfo.video.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_v;	//  pCompressVideo->uiTranNo_openAvDev  +  iIndex_sharedObjUsr;
									//  
									memcpy(  &transferAvReplyInfo.tranInfo.video.compressor,  &pCompressVideo->compressor,  sizeof(  transferAvReplyInfo.tranInfo.video.compressor  )  );
									memcpy(  &transferAvReplyInfo.tranInfo.video.vh_compress,  &pCompressVideo->vh_compress,  sizeof(  transferAvReplyInfo.tranInfo.video.vh_compress  )  );
									//  2014/03/31
									memcpy(  &transferAvReplyInfo.tranInfo.video.vh_stream,  &pCompressVideo->vh_stream,  sizeof(  transferAvReplyInfo.tranInfo.video.vh_stream  )  );
									//
									memcpy(  &transferAvReplyInfo.tranInfo.video.vh_decompress.bih,  &pCompressVideo->vh_decompress.bih,  sizeof(  transferAvReplyInfo.tranInfo.video.vh_decompress.bih  )  );
									//
									transferAvReplyInfo.tranInfo.audio.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_a;	//  pCompressAudio->uiTranNo_openAvDev  +  iIndex_sharedObjUsr;
									memcpy(  &transferAvReplyInfo.tranInfo.audio.compressor,  &pCompressAudio->compressor,  sizeof(  transferAvReplyInfo.tranInfo.audio.compressor  )  );
									memcpy(  &transferAvReplyInfo.tranInfo.audio.ah_compress,  &pCompressAudio->ah_compress,  sizeof(  transferAvReplyInfo.tranInfo.audio.ah_compress  )  );
									//  2016/12/23
									memcpy(  &transferAvReplyInfo.tranInfo.audio.ah_stream,  &pCompressAudio->ah_stream,  sizeof(  transferAvReplyInfo.tranInfo.audio.ah_stream  )  );
									//
									memcpy(  &transferAvReplyInfo.tranInfo.audio.ah_decompress,  &pCompressAudio->ah_decompress,  sizeof(  transferAvReplyInfo.tranInfo.audio.ah_decompress  )  );
									//
									qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "AvReply: maxFps %d, video %d, audio %d"  ),  (  int  )pCompressVideo->compressor.common.usMaxFps_toShareBmp,  transferAvReplyInfo.tranInfo.video.uiTranNo_openAvDev,  transferAvReplyInfo.tranInfo.audio.uiTranNo_openAvDev  );
								}

								//  2017/09/08
								transferAvReplyInfo_myTask.uiTaskType  =  rcd.uiType;  

								//  2008/06/12
								transferAvReplyInfo_myTask.ucbSendLocalAv  =  ucbSendLocalAv;
								transferAvReplyInfo_myTask.iIndex_sharedObj  =  iIndex_sharedObj;		//  sharedObj
								
								//  
								//  int  index;  index  =  0;
								//
								transferAvReplyInfo_myTask.mem0_from.idInfo.ui64Id  =  pMsgTask->data.route.idInfo_from.ui64Id;
								transferAvReplyInfo_myTask.mem0_from.tStartTime_task  =  pMsgTask->tStartTime;
								//
								//if  (  rcd.uiType  ==  CONST_imTaskType_transferAvInfo  )  
								{							//  2009/06/01
									if  (  //m_var.addr.uiObjType  ==  CONST_objType_imGrp  
										pContent->transferAvInfo.confCfg.ucbVideoConference
										)  
									{									
										transferAvReplyInfo_myTask.ucbVideoConference  =  TRUE;							//  2009/05/30									
										transferAvReplyInfo_myTask.mem0_from.ucbVideoConferenceStarter  =  TRUE;		//  2009/04/02
									}
								}
								//  2014/09/23
								transferAvReplyInfo_myTask.mem0_from.shClientVer  =  pContent->transferAvInfo.ass.tranInfo.head.shClientVer;
								//
								//  2014/11/11
								memcpy(  &transferAvReplyInfo_myTask.mem0_from.video.tv_recvd,  &pContent->transferAvInfo.ass.tranInfo.video,  sizeof(  transferAvReplyInfo_myTask.mem0_from.video.tv_recvd  )  );
								//
								//  2014/11/11
								memcpy(  &transferAvReplyInfo_myTask.mem0_from.audio.ta_recvd,  &pContent->transferAvInfo.ass.tranInfo.audio,  sizeof(  transferAvReplyInfo_myTask.mem0_from.audio.ta_recvd  )  );
																
								//  2014/11/11
								unsigned  int									uiTranNo_openAvDev_confMosaic_video  =  0;								//  Video
								unsigned  int									uiTranNo_openAvDev_confMosaic_resource  =  0;							//  Video

								//
								if  (  transferAvReplyInfo_myTask.ucbVideoConference  )  {
									//PROC_conf_mosaic					*			pProcConfMosaic  =  NULL;

									if  (  pContent->transferAvInfo.confMosaicTranInfo_video.resObj.uiObjType  )  {
										//
										uiTranNo_openAvDev_confMosaic_video  =  pContent->transferAvInfo.confMosaicTranInfo_video.video.uiTranNo_openAvDev;

										//
										DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pTc->videoConference.activeMems_from[0];
										memset(  pActiveMem_from,  0,  sizeof(  pActiveMem_from[0]  )  );
										pActiveMem_from->avStream.idInfo=pMsgTask->data.route.idInfo_from;
										pActiveMem_from->avStream.obj.resObj  =  pContent->transferAvInfo.confMosaicTranInfo_video.resObj;
										pActiveMem_from->avStream.obj.tranInfo.video  =  pContent->transferAvInfo.confMosaicTranInfo_video.video;
										M_getActiveMemDesc(  m_var.pMisCnt,  &pActiveMem_from->avStream.idInfo,  pActiveMem_from->desc,  mycountof(  pActiveMem_from->desc  )  );
									}
									//
									if  (  pContent->transferAvInfo.confMosaicTranInfo_resource.resObj.uiObjType  )  {
										//
										uiTranNo_openAvDev_confMosaic_resource  =  pContent->transferAvInfo.confMosaicTranInfo_resource.video.uiTranNo_openAvDev;

									}
								}

								//  2014/11/21
								if  (  !transferAvReplyInfo_myTask.ucbVideoConference  )  {
									if  (  pContent->transferAvInfo.proxiedTranInfo.idInfo.ui64Id
										&&  pContent->transferAvInfo.proxiedTranInfo.uiObjType  )  
									{
										transferAvReplyInfo_myTask.receiver.bRecvd_proxiedTranInfo  =  TRUE;
										//
										transferAvReplyInfo_myTask.receiver.proxied_from.idInfo.ui64Id  =  pContent->transferAvInfo.proxiedTranInfo.idInfo.ui64Id;
										transferAvReplyInfo_myTask.receiver.proxied_from.shClientVer  =  pContent->transferAvInfo.proxiedTranInfo.ti.head.shClientVer;
										transferAvReplyInfo_myTask.receiver.proxied_from.video.tv_recvd  =  pContent->transferAvInfo.proxiedTranInfo.ti.video;
										transferAvReplyInfo_myTask.receiver.proxied_from.audio.ta_recvd  =  pContent->transferAvInfo.proxiedTranInfo.ti.audio;
									}
								}

								//
								if  (  transferAvReplyInfo_myTask.ucbVideoConference  )  pTc->videoConference.usCntLimit_mems_from  =  min(  30,  MAX_mems_taskAv  );
								if  (  pTc->videoConference.usCntLimit_mems_from  <  2  )  pTc->videoConference.usCntLimit_mems_from  =  2;	//  index  +  1;

								if  (  !transferAvReplyInfo_myTask.ucbVideoConference  )  {
									//
									pTc->videoConference.usMaxSpeakers  =  2;
									pTc->videoConference.usCntLimit_activeMems_from  =  pTc->videoConference.usMaxSpeakers  + MAX_resourceMems_taskAv_p2p;
								    #if  0		//  2012/02/16
										memcpy(  &transferAvReplyInfo_myTask.audio.playCfg,  (  rcd.uiType  ==  CONST_imTaskType_transferAvInfo  )  ?  &policyAv.avCompressor.audio.playCfg  :  &policyAv.mediaFileCompressor.audio.playCfg,  sizeof(  transferAvReplyInfo_myTask.audio.playCfg  )  );
								    #endif
									tmpGetMaxAudioPlayCfg(  &pContent->transferAvInfo.ass.tranInfo.audio.compressor.playCfg,  &avCompressor_reply.audio.playCfg,  &transferAvReplyInfo_myTask.audio.playCfg  );
									}
								else  {	//  2009/05/31
									pTc->videoConference.usMaxSpeakers  =  pContent->transferAvInfo.confCfg.usMaxSpeakers;
									if  (  !pTc->videoConference.usMaxSpeakers  )  {
										showInfo_open0(  0,  0,  _T(  "dlgTalk_procTask_transferAvInfo failed: usMaxSpeakers is 0"  )  );
										goto  errLabel;
									}
									pTc->videoConference.usCntLimit_activeMems_from  =  pContent->transferAvInfo.confCfg.usMaxSpeakers  +  MAX_mosaicMems_taskAv  +  MAX_resourceMems_taskAv_conf;
									//if  (  !pTc->videoConference.usCntLimit_activeMems_from  )  pTc->videoConference.usCntLimit_activeMems_from  =  min(  pTc->videoConference.usCntLimit_mems_from,  mycountof(  pTc->videoConference.activeMems_from  )  );
									//pTc->videoConference.usCntLimit_activeMems_from  =  min(  pTc->videoConference.usCntLimit_activeMems_from,  mycountof(  pTc->videoConference.activeMems_from  )  );
										
									  //  2009/06/03. //  2011/11/28, 因为高性能的策略在一些老式电脑上无法运行，所以，声音策略不能取从视频发起方下发的策略，而是用本地的策略和下发的策略的最大值	
									  AUDIO_PLAY_CFG  *  pAudioPlayCfg_conf  =  &pContent->transferAvInfo.ass.tranInfo.audio.compressor.playCfg;
									  tmpGetMaxAudioPlayCfg(  pAudioPlayCfg_conf,  &avCompressor_reply.audio.playCfg,  &transferAvReplyInfo_myTask.audio.playCfg  );
								}
								//
								if  (  pTc->videoConference.usCntLimit_activeMems_from  >  MAX_conf_activeMems  )  {

										showInfo_open0(  0,  0,  _T(  "dlgTalk_procTask_transferAvInfo failed: usCntLimit_activeMems_from too big"  )  );										
										goto  errLabel;
									
								}

								//
								transferAvReplyInfo_myTask.hWnd_task  =  hDlgTalk;		//  2009/09/09

								//
								lenInBytes  =  sizeof(  transferAvReplyInfo  );

								//
								pProcInfo->av.acceptTaskAv.dwLastTickCnt_avReply = myGetTickCount(mynull);

								//
								MACRO_prepareForTran(  );
								//
								//  if  (  postMsg2TaskQ_mc(  pQyMc,  pDlg->m_var.pSci,  pDlg->m_var.pMisCnt,  NULL,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsgTask->iTaskId,  0,  (  char  *  )&transferAvReplyInfo,  lenInBytes,  &pDlg->m_var.addr.idInfo,  &pMsgTask->idInfo_taskSender,  CONST_channelType_media  )  )  goto  errLabel;  
								//
								if  (  ucbSendLocalAv  )  {	
									if  (  !pSharedObj  ||  !pSharedObjUsr  )  goto  errLabel;

									pTc->ucbNotSendData  =  (  m_var.addr.uiObjType  ==  CONST_objType_imGrp  );
									if  (  pParam->av_autoAnswer_av_task_bTaskNeedAutoAnswered  )  pTc->ucbNotSendData  =  TRUE;	//  2010/09/07

									//  if  (  addToMsgrs_sendLocalAv(  pProcInfo,  m_var.pMisCnt,  &pMsgTask->idInfo_taskSender,  FALSE,  pSharedObj  )  )  goto  errLabel;
									//  if  (  setROUTE_sendLocalAv(  pProcInfo,  m_var.pMisCnt,  &pMsgTask->idInfo_taskSender,  FALSE,  pSharedObj  )  )  goto  errLabel;

									//  2010/09/03
									pSharedObjUsr->iTaskId  =  pMsgTask->iTaskId;
									//pSharedObjUsr->idInfo_to.ui64Id  =  pMsgTask->idInfo_taskSender.ui64Id;
									pSharedObjUsr->ucbVideoConference  =  pContent->transferAvInfo.confCfg.ucbVideoConference;	//  2018/11/10 

								}
								//
								transferAvReplyInfo_myTask.reply_avTranInfo=transferAvReplyInfo.tranInfo;
								//
								if(0!=pProcInfo->processQ_media.qPostMsg(&task,sizeof(task)))
								{
									goto errLabel;
								}

								//  2015/09/07
								unsigned  int  uiChannelType  =  CONST_channelType_media;
								//  2015/09/07
								uiChannelType  =  0;
								//  2012/04/01
								//  if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsgTask->iTaskId,  0,  (  char  *  )&transferAvReplyInfo,  lenInBytes,  &m_var.addr.idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &pMsgTask->idInfo_taskSender,  CONST_channelType_media,  NULL,  FALSE  )  )  goto  errLabel;
								if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsgTask->iTaskId,  pMsgTask->uiTaskType,  (  char  *  )&transferAvReplyInfo,  lenInBytes,  &m_var.addr.idInfo,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &pMsgTask->idInfo_taskSender,  uiChannelType,  NULL,  FALSE  )  )  goto  errLabel;

								//  209/02/20
								if  (  rcd.uiType  ==  CONST_imTaskType_transferAvInfo 
									||  rcd.uiType  ==  CONST_imTaskType_shareDevice_grp  )  
								{
									assert(  !m_var.av.taskInfo.bTaskExists  );
									//
									//memset(  &m_var.av.taskInfo,  0,  sizeof(  m_var.av.taskInfo  )  );
									dlgTalk_taskInfo_memset0(hMgr);
									//
									m_var.av.taskInfo.bTaskExists  =  TRUE;
									m_var.av.taskInfo.iTaskId  =  iTaskId;
									//
									m_var.av.taskInfo.dwTickCnt_start  =  myGetTickCount(  NULL  );
									//
									//  m_var.av.taskInfo.iIndex_sharedObj  =  ucbSendLocalAv  ?  iIndex_sharedObj  :  -1;
									m_var.av.taskInfo.idInfo_starter.ui64Id  =  rcd.idInfo_send.ui64Id;

									//
									m_var.av.taskInfo.uiInitW  =  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biWidth;
									m_var.av.taskInfo.uiInitH  =  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biHeight;

									//
																		//
									m_var.av.taskInfo.iIndex_taskInfo = iIndex_taskInfo;
									if(m_var.av.taskInfo.iIndex_taskInfo<0)
                                    {
										traceLogA(  (char*)"dlgTalk_procTask_transferAvInfo failed, index_taskInfo <0");
										goto errLabel;
                                    }


									//
									m_var.av.taskInfo.tStartTime_org  =  rcd.tSendTime;
									m_var.av.taskInfo.uiTranNo_org  =  rcd.uiTranNo;
									m_var.av.taskInfo.uiContentType_org  =  rcd.uiContentType;

									//  2015/02/17
									m_var.av.taskInfo.local_avStream.tranInfo  =  transferAvReplyInfo.tranInfo;

									//  2010/08/31
									m_var.av.taskInfo.ucbVideoConference  =  transferAvReplyInfo_myTask.ucbVideoConference;

									//  2017/08/25
									m_var.av.taskInfo.usConfType  =  pContent->transferAvInfo.confCfg.usConfType;

									//  2017/08/27
									m_var.av.taskInfo.idInfo_initiator  =  pContent->transferAvInfo.confCfg.idInfo_initiator;

									//
#if 0
									m_var.av.taskInfo.ui64MeetingId_hg = pContent->transferAvInfo.confCfg.hgInfo.ui64MeetingId_hg;
									m_var.av.taskInfo.iMeetingType_hg = pContent->transferAvInfo.confCfg.hgInfo.iMeetingType_hg;
#endif
									//
									m_var.av.taskInfo.hgInfo = pContent->transferAvInfo.confCfg.hgInfo;
									
									//
									m_var.av.taskInfo.confState.iW_conf = avCompressor_reply.video.common.iWidth_pic;
									m_var.av.taskInfo.confState.iH_conf = avCompressor_reply.video.common.iHeight_pic;
									m_var.av.taskInfo.confState.usMaxFps = avCompressor_reply.video.common.usMaxFps_toShareBmp;


									//  2014/11/12
									if  (  m_var.av.taskInfo.ucbVideoConference  )  {
										if  (  uiTranNo_openAvDev_confMosaic_video  ||  uiTranNo_openAvDev_confMosaic_resource  )  {
											m_var.av.taskInfo.mosaicTrans.bExists_confMosaic  =  TRUE;
											//
											//m_var.av.taskInfo.mosaicTrans.uiTranNo_openAvDev_confMosaic_video  =  uiTranNo_openAvDev_confMosaic_video;
											//m_var.av.taskInfo.mosaicTrans.uiTranNo_openAvDev_confMosaic_resource  =  uiTranNo_openAvDev_confMosaic_resource;
										}
									}

									//  2016/03/26
									if  (  m_var.av.taskInfo.ucbVideoConference  )  {
										//
										#if  0  //  2017/11/01
										if  (  pContent->transferAvInfo.confCfg.conf.bgWall.ucbShowBgWall_starter  )  {
											//  2017/11/01
											//pShadowMgr->av.joinInBgWall.ucbNeedToAsk_willingTo_joinInBgWall  =  TRUE;
										}
										#endif
										//  2017/07/06
										if  (  pContent->transferAvInfo.confCfg.conf.confCtrl.ucbConfCtrl_starter  )  {
											m_var.av.taskInfo.ucbConfCtrl  =  TRUE;
										}

										//  2018/11/01
										if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hzj  )  {
											pProcInfo->hzj.bConfStarted  =  TRUE;
											pProcInfo->hzj.idInfo_tmpGrp.ui64Id  =  m_var.addr.idInfo.ui64Id;
											//
											PostMessage(  pProcInfo->hWall_hzj,  CONST_qyWm_postComm,  CONST_qyWmParam_confAccepted,  0  );

										}
									}

									//  2010/08/31
									#if  0
									if  (  !m_var.av.taskInfo.ucbVideoConference  )  {
										if  (  !m_var.av.autoAnswer_av.task.bTaskNeedAutoAnswered  )  {
											//  m_var.av.taskInfo.bNeedAutoRequestToSpeak  =  TRUE;
										}
									}
									#endif

									//
									//  2017/09/03
									resetTalkerList_mgr(  hMgr  );

									//
									if (rcd.uiType == CONST_imTaskType_transferAvInfo) {
										if (AEC_layout_init(m_var.av.taskInfo.iTaskId, pTc->videoConference.usCntLimit_activeMems_from, &pProcInfo->av.aecInfo.aecLayout)) {
											showInfo_open0(0, 0, _T("dlgTalk_procTask_transferAvInfo. AEC_layout_init failed"));
											goto  errLabel;
										}
									}


									//
#if  0
									QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  m_var.av.taskInfo.iIndex_taskInfo  );
									if  (  !pTaskInfo  )  goto  errLabel;
									if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;
									QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;
#endif
									//
									//
									unsigned  int  uiTaskType  =  rcd.uiType;
									MIS_CNT  *  pMisCnt  =  m_var.pMisCnt;
									if  (  uiTaskType  ==  CONST_imTaskType_transferAvInfo  )  {				
										if  (  !m_var.av.taskInfo.ucbVideoConference  )  {
											if  (  addToMsgrs_sendLocalAv(  pProcInfo,  pMisCnt,  &m_var.addr.idInfo,  FALSE,  &pTaskInfo->var.curRoute_sendLocalAv, false,  _T(  "dlgTalk_procTask_transferAvInfo.1538"  )))  goto  errLabel;
										}			
									}

									//
									if  (  !m_var.av.taskInfo.ucbVideoConference  )  {		//  2012/05/03. 在一对一接收时,自动将对方加入话筒列表,以便显示.
										DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  NULL;
										pActiveMem_from  =  &pTc->videoConference.activeMems_from[0];
										pActiveMem_from->avStream.idInfo.ui64Id  =  m_var.addr.idInfo.ui64Id;
										pActiveMem_from->avStream.obj.tranInfo  =  pContent->transferAvInfo.ass.tranInfo;
										_sntprintf(  pActiveMem_from->desc,  mycountof(  pActiveMem_from->desc  ),  _T(  "%s(%I64u)"  ),  m_var.displayName,  m_var.addr.idInfo.ui64Id  );
										#ifdef  __DEBUG__
												traceLog((TCHAR*)  _T(  "Note: 	在一对一接收时,自动将对方加入话筒列表,以便显示."  )  );
										#endif
										//  2013/04/10
										if  (  !pParam->av_autoAnswer_av_task_bTaskNeedAutoAnswered  )  {
											pActiveMem_from  =  &pTc->videoConference.activeMems_from[1];
											pActiveMem_from->avStream.idInfo.ui64Id  =  m_var.pMisCnt->idInfo.ui64Id;
											_sntprintf(  pActiveMem_from->desc,  mycountof(  pActiveMem_from->desc  ),  _T(  "%s(%I64u)"  ),  _T(  ""  ),  m_var.pMisCnt->idInfo.ui64Id  );
										}

									}

									//  2010/09/07
									if  (  ucbSendLocalAv  )  {				//
										if  (  !pParam->av_autoAnswer_av_task_bTaskNeedAutoAnswered  )  {
											//setCurSharedObjUsr_localAv(  pProcInfo,  iIndex_sharedObj,  iIndex_sharedObjUsr  );
											}	
										else  {
											  //
											  BOOL  bNeed_setCurSharedObjUsr  =  FALSE;
											  //
											  ZONE_objs  *  pGZone  =  pProcInfo->pGZone_activeTalkers;
											  if  (  isZoneObjIndexValid(  pGZone->iIndex_enlarged1  )  )  {
												  ZONE_obj  *  pZoneObj  =  &pGZone->mems[pGZone->iIndex_enlarged1];
												  if  (  pZoneObj->hWndWallMem  ==  hDlgTalk  )  bNeed_setCurSharedObjUsr  =  TRUE;
											  }
											  //  2018/12/26
											  if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hbwj  )  {
												  bNeed_setCurSharedObjUsr  =  TRUE;
											  }
											  if (pProcInfo->bAppQt()) {
												  bNeed_setCurSharedObjUsr = true;
											  }
											  //
											  bNeed_setCurSharedObjUsr = true;
											  //
											  if  (  bNeed_setCurSharedObjUsr  )  {
												  //setCurSharedObjUsr_localAv(  pProcInfo,  iIndex_sharedObj,  iIndex_sharedObjUsr  );
												  }
											  else  {
													//
													InvalidateRect_mgr(  hDlgTalk,  0,  NULL,  TRUE  );	
											  }
										}
									}

									//
									pProcInfo->dlgTalk_confStart_post(hDlgTalk, _T("dlgTalk_procTask_av: l1650"));

									//  2010/12/25
									//if  (  IsWindow(  m_var.av.hWnd_remoteAv_resourcesInfo  )  )  SendMessage(  m_var.av.hWnd_remoteAv_resourcesInfo,  WM_CLOSE,  0,  0  );
									closeInstantAssistant_mgr(  hDlgTalk  );
									
									//  2013/04/08
									//  sizeAllControls_dlgTalk(  hDlgTalk,  m_var,  NULL  );				//  
									dlgTalk_doLayout(  hDlgTalk  );

								}
							
								//
								if  (  rcd.uiType  ==  CONST_imTaskType_transferAvInfo  
									||  rcd.uiType  ==  CONST_imTaskType_shareDevice_grp)  
								{
									if  (  ucbSendLocalAv  &&  
										//m_var.addr.uiObjType  ==  CONST_objType_imGrp  
										pContent->transferAvInfo.confCfg.ucbVideoConference
										)  
									{
										//  2017/07/14
										if  (  pProcInfo->cfg.policy.avRules.ucbLetConfMgrSetMicOn  )  {
											if  (  !canJoinInBgWall(  hMgr,  pMgrVar  )  )  {
												HWND  hParent  =  NULL;
												dlgTalk_doCmd_joinInBgWall(  hMgr  );
											}
										}
										//
										int  get_ConfMem_confCtrl(  QY_MC  *  pQyMc,  QY_MESSENGER_ID  *  pIdInfo,  ConfMem_confCtrl  *  pConfCtrl  );
										//
										ConfMem_confCtrl  confCtrl  =  {0};
										get_ConfMem_confCtrl(  pQyMc,  &pMgrVar->addr.idInfo,  &confCtrl  );
										//
										if  (  pMgrVar->av.taskInfo.bTaskExists
											&&  pMgrVar->av.taskInfo.idInfo_starter.ui64Id  ==  confCtrl.idInfo_starter.ui64Id
											&&  pMgrVar->av.taskInfo.tStartTime_org  ==  confCtrl.tStartTime
											&&  pMgrVar->av.taskInfo.uiTranNo_org  ==  confCtrl.uiTranNo  )
										{
											pMgrVar->av.taskInfo.confMem_confCtrl  =  confCtrl;
										}
										//
										if  (  pMgrVar->av.taskInfo.confMem_confCtrl.ucbPermitToSpeak  )  {
											//
										}
								
									}
									if (ucbSendLocalAv) {
										if (!pContent->transferAvInfo.confCfg.ucbVideoConference
											&& pMgrVar->addr.uiObjType != CONST_objType_imGrp)
										{
											int  ii = 0;
											dlgTalk_requestToSpeak(hMgr, TRUE,false);
											pProcInfo->xt.bSpeak = true;	
											pProcInfo->av.hk.iHkStatus = setFyOff(pProcInfo->av.hk.iHkStatus);

										}
										else {
											pProcInfo->xt.bSpeak = false;
											pProcInfo->av.hk.iHkStatus = clearFyOff(pProcInfo->av.hk.iHkStatus);

										}
										//
										if (pContent->transferAvInfo.confCfg.ucbVideoConference
											&& bObjTypeGrp(pMgrVar->addr.uiObjType))
										{
											if (pProcInfo->av.speakState.bEnableToSpeak
												&& pProcInfo->av.speakState.idInfo_grp.ui64Id == pMgrVar->addr.idInfo.ui64Id)
											{
												dlgTalk_requestToSpeak(hMgr, TRUE, FALSE);
												pProcInfo->xt.bSpeak = true;
												pProcInfo->av.hk.iHkStatus = setFyOff(pProcInfo->av.hk.iHkStatus);
											}
											else {
												pProcInfo->xt.bSpeak = false;
												pProcInfo->av.hk.iHkStatus = clearFyOff(pProcInfo->av.hk.iHkStatus);
											}

											if (pProcInfo->av.speakState.fl.bEnableToSnd
												&&  pProcInfo->av.speakState.fl.idInfo_grp.ui64Id  ==  pMgrVar->addr.idInfo.ui64Id) 
											{
												pProcInfo->do_talk_shareDevice(hMgr, pMgrVar, true, false);
											}
										}
									}

									//
									pProcInfo->cfg.debugStatusInfo.tn_dumpAv=getuiNextTranNo(NULL,0,NULL);
									//
									}
								else  if  (  rcd.uiType  ==  CONST_imTaskType_remoteAssist  )  {
										  PARAM_dlgVideos	params  =  {0};
										  //
										  params.iTaskId  =  rcd.id;
										  //  params.m_var.uiTaskType  =  rcd.uiType;	//  2009/08/05
										  params.idInfo_sender.ui64Id  =  pMsgTask->idInfo_taskSender.ui64Id;
										  params.uiTranNo_openAvDev  =  pContent->transferAvInfo.ass.tranInfo.video.uiTranNo_openAvDev;
										  //
										  params.pImgs  =  &m_var.av.peerZone.images;
										  params.iIndex_capImage  =  -1;
										  params.usCnt_monPics_row  =  1;
										  params.usCnt_monPics_col  =  1;
										  params.uiInitW  =  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biWidth;
										  params.uiInitH  =  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biHeight;
										  params.bScrollBarEnabled  =  TRUE; 
										  params.bRemoteAssist  =  TRUE;		

										  //  2012/05/10
										  //params.hParent  =  hCurTalk;

										  //  2017/08/23
										  if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_bjyz  )  {
											  break;
										  }

										  //
										  if  (  showRemoteAssistWnd(  hCurTalk,  hDlgTalk,  TRUE,  &params,  &m_var.subWnds  )  )  goto  errLabel;

								}

					
								//
								{
									//					
									pProcInfo->reportToHg_meetingOn(pContent->transferAvInfo.confCfg.hgInfo.ui64MeetingId_hg, m_var.av.taskInfo.hgInfo.iMeetingType_hg,  m_var.addr.idInfo.ui64Id,  true);

								}

					  }
					  
					  //
					  }					  
					  break;
				default:
						break;
	 }
					 
	 //
	 refreshTalkToInfo_mgr(  hDlgTalk  );

	 //
	 talk_refreshLayout_mgr(hDlgTalk);


	 //
	 iErr  =  0;
errLabel:
	 
	 if  (  iErr  )  {
		if  (  ucbGot_iIndex_sharedObj_localAv  )  {
			//  
			//freeSharedObjUsr_localAv(  m_var.av.iIndex_sharedObj_localAv,  hDlgTalk  );
			//m_var.av.ucbGot_iIndex_sharedObj_localAv  =  FALSE;
			dlgTalk_closeTaskAv(  hDlgTalk,  m_var  );
		}
	}

	 //
	 refreshMosaicTransStatus(hDlgTalk, &m_var);


	 //  2010/12/24	
	 chkResources(  hDlgTalk,  FALSE  );

	 //
	 chkAvStatus();

	 //
	 pProcInfo->do_dlgTalk_procTask_transferAvInfo(hDlgTalk);

	 //
	 pProcInfo->AEC_layout_chk(&pProcInfo->av.aecInfo.aecLayout);

	 //
	 return  iErr;

 }





