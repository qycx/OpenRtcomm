
#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"dlgtalkproc.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qmcDmoPublic.h"

#include	"wallTalkers.h"
#include	"qmcGpsProc.h"
#include	"msAecCommon.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"
#include	"amCapPublic.h"
#include	"isCliD3dPublic.h"
#include	"qyMcMainWndProc.h"
#include	"imgProcessPublic.h"
#include	"qmcCommFunc_isCli.h"
#include	"qyMessengerHelpPublic.h"

//
#include	"load_isD3dFunc.h"


#include "qmcStruct_defs.h"//

//
#if  0
int load_ancPktProcess(FUNCS_for_isCliHelp* pFuncs);
int  unload_ancPktProcess(FUNCS_for_isCliHelp* pFuncs);
#endif 



//  2015/12/05
 void  *  getZoneObjs(  HWND  hDlgWalls,  int  iWndContentType,  int  iZoneObjsType  )
 {
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  NULL;

	 switch  (  iWndContentType  )  {
			 case  CONST_qyWndContentType_vWall:
				   return  getZoneObjs_dynBmps(  hDlgWalls,  iWndContentType  );
				   break;
			 default:
					break;
	 }

	 //  2016/06/03
	 switch  (  iZoneObjsType    )  {
			 case  CONST_zoneObjsType_walls:
				   return  pProcInfo->pGZone_d3dWalls;
				   break;
			 default:
					 break;
	 }

	 //
	 return  pProcInfo->pGZone_activeTalkers;
 }



//
 void  *  getZoneObjsInfo(  CCtxQmc  *  pProcInfo,  HWND  hDlgWalls,  int  iWndContentType,  int  iZoneObjsType  )
 {
	 switch  (  iWndContentType  )  {
			 case  CONST_qyWndContentType_vWall:
				   return  getZoneObjsInfo_dynBmps(  hDlgWalls,  iWndContentType  );
				   break;
			 case  CONST_qyWndContentType_ts_main:
				   #ifdef  __APP_qyMc_touchscreen__
						   return  getZoneObjsInfo_ts(  hDlgWalls,  iWndContentType  );
				   #endif
				   break;
			 case  CONST_qyWndContentType_consoleWall:
			 case  CONST_qyWndContentType_generalWall:
				   return  dyn_getZoneObjsInfo_d3dWall(  pProcInfo,  hDlgWalls,  iWndContentType,  iZoneObjsType  );
				   break;
			 default:
					break;
	 }

	 return  NULL;
 }


 //
 int  tmp_sendConfKey(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint)
 {
	 CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	 return  pProcInfo->sendConfKey(hDlgTalk, idInfo_to, hint);
 }



 //
 FUNCS_for_isCliHelp  *  FUNCS_for_isCliHelp_new(  QY_MC  *  pQyMc  )
{
	int						iErr	=	-1;
	FUNCS_for_isCliHelp	*  pFuncs  =  NULL;

	//
	if  (  !pQyMc  )  return  NULL;
	CCtxQmc  *  pProcInfo  =  (  CCtxQmc  *  )pQyMc->get_pProcInfo(  );

	//
	int						size  =  sizeof(  FUNCS_for_isCliHelp  );
	pFuncs  =  (  FUNCS_for_isCliHelp  *  )mymalloc(  size  );
	if  (  !pFuncs  )  goto  errLabel;
	memset(  pFuncs,  0,  size  );

	//
	//pFuncs->pf_addTxtToPic_screen  =  addTxtToPic_screen;
	//pFuncs->pf_setPktInputInfo  =  setPktInputInfo;
	//pFuncs->pf_CTX_addTxt_free  =  CTX_addTxt_free;


	//
	pFuncs->pf_askToRefreshLayout_mgr  =  askToRefreshLayout_mgr;
	//
	//
	pFuncs->pf_bFullScreen_wnd  =  bFullScreen_wnd_default;
	//
	pFuncs->pf_bMainWndAbove  =  bMainWndAbove;
	pFuncs->pf_bMessengerOnline  =  bMeOnline;
	//
	//pFuncs->pf_bQisExportVWall  =  bQisExportVWall;
	//pFuncs->pf_bQisImportVWall  =  bQisImportVWall;
	//
	pFuncs->pf_bWebcamUsing  =  bWebcamUsing;
	pFuncs->pf_bRecorderUsing  =  bRecorderUsing;

	pFuncs->pf_bQnmExportCurQuery  =  bQnmExportCurQuery;

	pFuncs->pf_bViewImTaskListFunc  =  bViewImTaskListFunc;
	pFuncs->pf_bViewImObjListFunc  =  bViewImObjListFunc;
	pFuncs->pf_bViewMessengerRegInfoList  =  bViewMessengerRegInfoList;
	pFuncs->pf_bViewImGrpList  =  bViewImGrpList;
	pFuncs->pf_bViewImGrpMemList_isClient  =  bViewImGrpMemList_isClient;	//  2014/04/18
	pFuncs->pf_bViewImObjRuleList_is  =  bViewImObjRuleList_is;				//  2014/04/18
	
	//
	//pFuncs->pf_canRemotePtzControl  =  canRemotePtzControl;
	//
	pFuncs->pf_CAP_STUFF_free  =  CAP_STUFF_free;
	pFuncs->pf_CAP_STUFF_new  =  CAP_STUFF_new;
	pFuncs->pf_getChosenDevice  =  getChosenDevice;
	pFuncs->pf_myChooseDevices  =  myChooseDevices;
	pFuncs->pf_chooseAvDevice_mgr  =  chooseAvDevice_mgr;
	pFuncs->pf_cfgCaptureFilter  =  cfgCaptureFilter;
	pFuncs->pf_cfgCapturePin  =  cfgCapturePin;
	pFuncs->pf_cfgCrossBar  =  cfgCrossBar;
	//
	//pFuncs->pf_chkTalkerRules  =  chkTalkerRules;
	//pFuncs->pf_chkToViewDynBmp  =  chkToViewDynBmp;

	//
	//
	pFuncs->pf_delImObj  =  delImObj;
	pFuncs->pf_displayNotification_talk_ts  =  displayNotification_talk_ts;
	//
	//pFuncs->pf_dlgDynBmps_getZoneParam  =  dlgDynBmps_getZoneParam;
	//
	pFuncs->pf_bDlgTalkAbove  =  bDlgTalkAbove;
	pFuncs->pf_dlgTalk_cancelTasks  =  dlgTalk_cancelTasks;
	pFuncs->pf_dlgTalk_OnDestroy  =  dlgTalk_OnDestroy;
	//
	pFuncs->pf_dlgTalk_OnInitDialog  =  dlgTalk_OnInitDialog;
	pFuncs->pf_dlgTalk_OnQyComm  =  dlgTalk_OnQyComm;
	pFuncs->pf_dlgTalk_OnQyPostComm  =  dlgTalk_OnQyPostComm;
	pFuncs->pf_dlgTalk_qPostMsg  =  dlgTalk_qPostMsg;
	pFuncs->pf_dlgTalk_requestToSpeak  =  dlgTalk_requestToSpeak;
	pFuncs->pf_dlgTalk_requestToOp = dlgTalk_requestToOp;
	pFuncs->pf_dlgTalk_procTask1  =  dlgTalk_procTask1;
	pFuncs->pf_dlgTalk_procCmd  =  dlgTalk_procCmd;
	//
	pFuncs->pf_dlgTalk_closeTask = dlgTalk_closeTask;
	//
	//pFuncs->pf_dlgTalk_drawItem_bgWall  =  dlgTalk_drawItem_bgWall;
	//pFuncs->pf_dlgTalk_getBgWallMemInfo  =  dlgTalk_getBgWallMemInfo;
	//  
	//pFuncs->pf_tmpHandler_chkVWallRule_dlgDynBmps  =  tmpHandler_chkVWallRule_dlgDynBmps;
	//pFuncs->pf_dlgVideos_procVideo  =  dlgVideos_procVideo;
	//
	//pFuncs->pf_doCmd_startAvCall  =  doCmd_startAvCall;
	//
	pFuncs->pf_stopAll_avRecord  =  stopAll_avRecord;
	pFuncs->pf_doCmd_startShareMediaDevice  =  doCmd_startShareMediaDevice;
	pFuncs->pf_doCmd_startShareMediaFile  =  doCmd_startShareMediaFile;


	pFuncs->pf_enumDmoIoTypes	=	enumDmoIoTypes;
	pFuncs->pf_enumDmos  =  enumDmos;

	pFuncs->pf_exitShareMediaFile  =  exitShareMediaFile;

	pFuncs->pf_fillQyMcQuery  =  fillQyMcQuery;
	//
	pFuncs->pf_findQMemByKey  =  findQMemByKey;

	pFuncs->pf_findTalker  =  findTalker;
	pFuncs->pf_findTaskInProcessQ  =  findTaskInProcessQ;
	//
	pFuncs->pf_getCusModule  =  getCusModule;
	//
	pFuncs->pf_getZoneObjs  =  getZoneObjs;  //  2015/12/05
	pFuncs->pf_getZoneObjsInfo  =  getZoneObjsInfo;
	//
	pFuncs->pf_getDmoInfoBySth  =  getDmoInfoBySth;
	//
	pFuncs->pf_get_g_guiData  =  get_g_guiData;
	pFuncs->pf_getMenuStatus  =  getMenuStatus;
	pFuncs->pf_getMisCntByName  =  getMisCntByName;

	//
	pFuncs->moniker.pf_addDevicesToMenu  =  addDevicesToMenu;

	pFuncs->moniker.pf_getMoniker_a  =  getMoniker_a;
	pFuncs->moniker.pf_getMoniker_v  =  getMoniker_v;
	//
	pFuncs->moniker.pf_getMonikerProp  =  getMonikerProp;
	pFuncs->moniker.pf_getMonikerDisplayName  =  getMonikerDisplayName;
	pFuncs->moniker.pf_getMonikerByDisplayName  =  getMonikerByDisplayName;		//  2015/09/18
	
	pFuncs->moniker.pf_getADevFriendlyName  =  getADevFriendlyName;
	pFuncs->moniker.pf_getADeviceGuid  =  getADeviceGuid;

	//
	pFuncs->pf_getProcedObjDb  =  getProcedObjDb;
#if  defined(  __APP_qyMc__  )  ||  defined(  __DLL_qyMessenger_help__  )
	pFuncs->pf_getRect_talkers  =  getRect_talkers_default;
#else
	pFuncs->pf_getRect_talkers  =  getRect_talkers_ts;
#endif

	pFuncs->pf_getShareMediaFileState  =  getShareMediaFileState;

	pFuncs->pf_getTalkerDesc  =  getTalkerDesc;

	//  2014/04/19
	pFuncs->pf_BufferCB_av  =  BufferCB_av;

	//
	pFuncs->gps.pf_toShareGps  =  toShareGps;

	pFuncs->imgProcess.pf_bUseChromaKey  =  bUseChromaKey;
	pFuncs->imgProcess.pf_addColorKey  =  addColorKey;
	pFuncs->imgProcess.pf_getColorDistance_keys  =  getColorDistance_keys;
	pFuncs->imgProcess.pf_delColorKey  =  delColorKey;
	pFuncs->imgProcess.pf_getCurImgProcessCfg  =  getCurImgProcessCfg;
	pFuncs->imgProcess.pf_refreshCurImgProcessCfg  =  refreshCurImgProcessCfg;
	pFuncs->imgProcess.pf_procChromaKey  =  procChromaKey;
	pFuncs->imgProcess.pf_test_procChromaKey  =  test_procChromaKey;

	//
	pFuncs->pf_imObjRulesReq2ImRules  =  imObjRulesReq2ImRules;
	pFuncs->pf_imObjRulesReq2Rules  =  imObjRulesReq2Rules;

	pFuncs->pf_initShareMediaFile  =  initShareMediaFile;

	//
	pFuncs->mainWnd.pf_initVar_onCreate_mainFrame  =  initVar_onCreate_mainFrame;
	pFuncs->mainWnd.pf_exitVar_onDestroy_mainFrame  =  exitVar_onDestroy_mainFrame;
	pFuncs->mainWnd.pf_mainWnd_OnClose  =  mainWnd_OnClose;
	pFuncs->mainWnd.pf_mainWnd_OnQyPostComm  =  mainWnd_OnQyPostComm;
	pFuncs->mainWnd.pf_mainWnd_OnQyQuitMainWnd  =  mainWnd_OnQyQuitMainWnd;
	//
	//pFuncs->mainWnd.pf_mainWnd_OnQyShowMainWnd  =  mainWnd_OnQyShowMainWnd;
	//
	pFuncs->mainWnd.pf_mainWnd_OnTimer  =  mainWnd_OnTimer;
	//
	pFuncs->mainWnd.pf_mainWnd_OnQyTrayNotify  =  mainWnd_OnQyTrayNotify;
	pFuncs->mainWnd.pf_mainWnd_OnQyGraphNotify_mediaDevice  =  mainWnd_OnQyGraphNotify_mediaDevice;
	pFuncs->mainWnd.pf_handleGraphEvent_mediaFile  =  handleGraphEvent_mediaFile;
	pFuncs->mainWnd.pf_showDlgQnmCfgOptionsIsClient  =  showDlgQnmCfgOptionsIsClient;
	pFuncs->mainWnd.pf_bViewActiveImObjList  =  bViewActiveImObjList;
	//
	pFuncs->pf_netMc_procTreeEvent  =  netMc_procTreeEvent;
	pFuncs->pf_netMc_procTreeSel  =  netMc_procTreeSel;

	pFuncs->pf_msg2TaskRcd  =  msg2TaskRcd;

	pFuncs->pf_pauseShareMediaFile  =  pauseShareMediaFile;
	//
	//
	//  pFuncs->pf_requestToSpeak_videoConferenceOthers  =  requestToSpeak_videoConferenceOthers;
	//pFuncs->pf_confStarter_requestToSpeak  =  confStarter_requestToSpeak;

	//  2017/07/08   
	pFuncs->pf_resumeLocalAudioRecorder  =  resumeLocalAudioRecorder;

	//  2017/09/13
	pFuncs->pf_resumeLocalVideo  =  resumeLocalVideo;

	//
	pFuncs->pf_runShareMediaFile  =  runShareMediaFile;

	pFuncs->pf_saveChosenDevice  =  saveChosenDevice;
	pFuncs->pf_sendVideoConferenceLayout  =  sendConfLayout;
	pFuncs->pf_sendVideoConferenceStatus  =  tmp_sendConfKey;
	pFuncs->pf_setCurSharedObjUsr_localAv  =  setCurSharedObjUsr_localAv;
	pFuncs->pf_resetCurSharedObjUsr_localAv  =  resetCurSharedObjUsr_localAv;
	pFuncs->pf_setEncodingDefaults_video  =  setEncodingDefaults_video;

	pFuncs->pf_stopShareMediaFile  =  stopShareMediaFile;
	pFuncs->pf_storeTaskInDb  =  storeTaskInDb;
	//  pFuncs->pf_toShareBmp  =  toShareBmp;
	//
	pFuncs->pf_startProgress  =  startProgress;
	pFuncs->pf_startToRefreshRecentFriends  =  startToRefreshRecentFriends;

	pFuncs->pf_talkerShadow_procGps  =  talkerShadow_procGps;
	pFuncs->pf_TALKER_shadow_free  =  TALKER_shadow_free;
	pFuncs->pf_talkToMessenger  =  talkToMessenger;
	pFuncs->pf_testLocalAv  =  testLocalAv;
	pFuncs->pf_tmpHandler_showMsg  =  tmpHandler_showMsg;
	//
	//pFuncs->pf_toSelectRegion  =  toSelectRegion;
	pFuncs->pf_toSelectRegion1  =  toSelectRegion1;

	//
	pFuncs->pf_tryToTalkToMessenger  =  tryToTalkToMessenger;
	pFuncs->pf_tryToTalkToMessenger_id  =  tryToTalkToMessenger_id;
	pFuncs->pf_tryToTalkToMessenger_any  =  tryToTalkToMessenger_any;


	//
	//pFuncs->pf_doSth_afterInitDlgTalk  =  doSth_afterInitDlgTalk;
	pFuncs->pf_doSth_afterInitDlgMsgTool  =  doSth_afterInitDlgMsgTool;


	//
	pFuncs->pf_updateMeDisplayInfo  =  updateMeDisplayInfo;
	//
	//
#ifdef  __APP_qyMc_touchscreen__
	pFuncs->pf_viewWallsBar_ts  =  viewWallsBar_ts;
#endif
	//  2015/06/03
	pFuncs->pf_viewWallsBar_3d  =  viewWallsBar;
	//  2015/06/03
	pFuncs->pf_setWallsBarPos  =  setWallsBarPos;
	//
	pFuncs->pf_vw_getCurSp  =  vw_getCurSp;

	//
	pFuncs->pf_testLocalAv_openLocalVideo  =  testLocalAv_openLocalVideo;
	pFuncs->pf_doCmd_test  =  doCmd_test;

	//
	pFuncs->pf_stopLocalAudioPlaying  =  stopLocalAudioPlaying;
	pFuncs->pf_freeSharedObjUsr_localAv  =  freeSharedObjUsr;

	//
	pFuncs->pf_tryToFreeSharedObjs  =  (  PF_tryToFreeSharedObjs  )tryToFreeSharedObjs;

	//  2013/07/01
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_refreshShareStatus  =  dlgShareDynBmps_refreshShareStatus;
	//pFuncs->shareDynBmps.pf_dlgShareDynBmps_getShareDynBmpsBySth  =  (  PF_dlgShareDynBmps_getShareDynBmpsBySth  )dlgShareDynBmps_getShareDynBmpsBySth;
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_refreshShareStatus_gps  =  dlgShareDynBmps_refreshShareStatus_gps;
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_OnQyComm  =  dlgShareDynBmps_OnQyComm;
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_OnQyPostComm  =  dlgShareDynBmps_OnQyPostComm;
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_chkTask  =  dlgShareDynBmps_chkTask;
	//
	pFuncs->shareDynBmps.pf_toShareDynBmp  =  toShareDynBmp;	//  2015/05/09
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_toShareDynBmp  =  dlgShareDynBmps_toShareDynBmp;
	//
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_toShareGps  =  dlgShareDynBmps_toShareGps;
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_closeTaskAv  =  dlgShareDynBmps_closeTaskAv;
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_chkShareGps  =  dlgShareDynBmps_chkShareGps;
	//
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_sndDynBmpsInfo  =  dlgShareDynBmps_sndDynBmpsInfo;
	//  2014/0
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_testRtspUrl  =  dlgShareDynBmps_testRtspUrl;
	//  2014/09/11
	pFuncs->shareDynBmps.pf_dlgShareDynBmps_internalProcess  =  dlgShareDynBmps_internalProcess;

	//  2017/06/8

	//  2013/12/23
	//  2015/11/15
	//
	pFuncs->isCliHelp.pf_addTalkerShadow  =  addTalkerShadow;
	pFuncs->isCliHelp.pf_removeTalkerShadow  =  removeTalkerShadow;
	//
	//
	pFuncs->isCliHelp.pf_dlgTalk_canSpeak  =  dlgTalk_canSpeak;
	//
	pFuncs->isCliHelp.pf_getuiNextTranNo  =  getuiNextTranNo;
	//
	pFuncs->isCliHelp.pf_myListCtrl_InsertItem  =  myListCtrl_InsertItem;
	pFuncs->isCliHelp.pf_myListCtrl_SetItemText  =  myListCtrl_SetItemText;
	//
	pFuncs->isCliHelp.pf_showDlgPolicyAv  =  showDlgPolicyAv;
	pFuncs->isCliHelp.pf_showDlgPolicyIsClient  =  showDlgPolicyIsClient;
	pFuncs->isCliHelp.pf_showDlgMsgList  =  showDlgMsgList;
	pFuncs->isCliHelp.pf_showDlgObjs  =  showDlgObjs;
	//
	//pFuncs->isCliHelp.pf_d3dWall_viewDlgTalk  =  d3dWall_viewDlgTalk;
	//
	//
	pFuncs->isCliHelp.pf_d3dWall_setBg  =  d3dWall_setBg;
	
	//  2015/11/30
	pFuncs->isCliHelp.pf_d3dWall_openQvw  =  d3dWall_openQvw;

	//
	pFuncs->isCliHelp.pf_dlgTalk_getTaskInfo  =  dlgTalk_getTaskInfo;
	pFuncs->isCliHelp.pf_dlgTalk_getTaskList  =  dlgTalk_getTaskList;

	//  2015/06/05
	pFuncs->isCliHelp.pf_showMenu_wallsBar  =  showMenu_wallsBar;

	//
	pFuncs->isCliHelp.pf_showMenu_d3dWall  =  showMenu_d3dWall;
	pFuncs->isCliHelp.pf_showMenu_generalWall  =  showMenu_generalWall;
	//
	pFuncs->isCliHelp.pf_bTaskExists_recvResource  =  bTaskExists_recvResource;
	pFuncs->isCliHelp.pf_bTaskExists_sendingResource  =  bTaskExists_sendingResource;

	//
	pFuncs->isCliHelp.pf_dlgTalk_getCurSubtitlesCfg  =  dlgTalk_getCurSubtitlesCfg;
	pFuncs->isCliHelp.pf_dlgTalk_getSubtitleMsgs  =  dlgTalk_getSubtitleMsgs;	//  2014/12/23


	//
	pFuncs->isCliHelp.pf_d3dWall_isUserActive  =  d3dWall_isUserActive;
	//
	pFuncs->isCliHelp.pf_getSubtitlesCfg  =  getSubtitlesCfg;	//  2014/12/21
	pFuncs->isCliHelp.pf_subtitlesCfg_modify  =  subtitlesCfg_modify;
	pFuncs->isCliHelp.pf_getSubtitlesCfg_d3dWall  =  getSubtitlesCfg_d3dWall;
	
	//  2015/11/21
	pFuncs->isCliHelp.pf_viewVWall  =  viewVWall;
	pFuncs->isCliHelp.pf_viewGlobalVWall  =  viewGlobalVWall;
	
	//
	pFuncs->isCliHelp.pf_addToWalls  =  addToWalls;
	//  2016/03/23
	pFuncs->isCliHelp.pf_viewDlgMsgInput_talk  =  viewDlgMsgInput_talk;
	pFuncs->isCliHelp.pf_setMsgInputPos  =  setMsgInputPos;
		
	//
	pFuncs->isCliHelp.pf_bDlgTalkWaitToAccept  =  bDlgTalkWaitToAccept;
	
	//
	pFuncs->isCliHelp.pf_dlgTalk_re_acceptTask  =  dlgTalk_re_acceptTask;
	//
	//
	pFuncs->isCliHelp.pf_bNoPrompt_selectAvCompressor  =  bNoPrompt_selectAvCompressor;
	//pFuncs->isCliHelp.pf_viewDlgSelectAvCompressor  =  viewDlgSelectAvCompressor;

	//
	pFuncs->isCliHelp.bOk  =  TRUE;

	//  2016/06/24
	//
	pFuncs->messenger_help.pf_myOnAppAbout  =  myOnAppAbout;
	//
	pFuncs->messenger_help.pf_toEditRtspUrlForConf  =  toEditRtspUrlForConf;
	pFuncs->messenger_help.bOk  =  TRUE;


	//
	if (pQyMc->appParams.bMcu) {
		load_isCliD3d(pProcInfo->cfg.isCliD3dFileName, pProcInfo->cfg.isCliD3dFileName_dx12, pFuncs);
	}

	//
	load_aiResize(pFuncs);

	//
	load_help_audioProc(pFuncs);
	load_help_webrtc1(pFuncs);

	//  2016/04/26
	initDynLib_isD3dFunc(  &pFuncs->pDynLib_isD3dFunc  );

	//  2015/02/17
	//if  (  bSupported_remoteStorage(  pQyMc  )  )  
	load_isCliSaveAv(pFuncs);

	//
#if  0
	load_ancPktProcess(pFuncs);
#endif

	//
	iErr  =  0;
errLabel:

	return  pFuncs;
}	


void  FUNCS_for_isCliHelp_free(  void  **  ppFuncs  )
{
	if  (  !ppFuncs  )  return;
	if  (  !*ppFuncs  )  return;

	FUNCS_for_isCliHelp  *  pFuncs  =  (  FUNCS_for_isCliHelp  *  )*ppFuncs;

	//
#if  0
	unload_ancPktProcess(pFuncs);
#endif 

	//
	unload_aiResize(pFuncs);

	//
	unload_isCliSaveAv(pFuncs);

	//
	unload_isCliD3d(  pFuncs  );

	//
	unload_help_audioProc(pFuncs);
	unload_help_webrtc1(pFuncs);

	//  2016/04/26
	exitDynLib_isD3dFunc(  &pFuncs->pDynLib_isD3dFunc  );

	//
	free(  *ppFuncs  );  *ppFuncs  =  NULL;
	return;
}


//
int  load_isCliD3d(LPCTSTR  fileName, LPCTSTR  fileName_dx12, FUNCS_for_isCliHelp* pFuncs)
{
	int						iErr	=	-1;
	CCtxQyMc		*		pQyMc	=	g_pQyMc;
	
	TCHAR				tmpFileName[MAX_PATH  +  1];
	 TCHAR				pathBuf[MAX_PATH  +  1];
	 TCHAR			*	filePart;
	 HINSTANCE			hDll							=		NULL;
	 PF_pCommonHandler	pf								=		NULL;
	 
	 if  (  !fileName  ||  !fileName[0]  )  return  -1;


	 GetModuleFileName(  NULL,  tmpFileName,  sizeof(  tmpFileName  )  /  sizeof(  tmpFileName[0]  )  );
	 if  (  !GetFullPathName(  tmpFileName,  sizeof(  pathBuf  )  /  sizeof(  pathBuf[0]  ),  pathBuf,  &filePart  )  )  goto  errLabel;
	 filePart[0]  =  0;

	 //
	 _sntprintf(  tmpFileName,  mycountof(  tmpFileName  ),  _T(  "%s%s"  ),  pathBuf,  fileName  );
	 pFuncs->isCliD3d.hDll  =  LoadLibrary(  tmpFileName  );
	 if  (  !pFuncs->isCliD3d.hDll  )  goto  errLabel;

	 //
	 pFuncs->isCliD3d.pf_getZoneObjsInfo_d3dWall  =  (  PF_getZoneObjsInfo_d3dWall  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "getZoneObjsInfo_d3dWall"  );
	 pFuncs->isCliD3d.pf_set_g_pQyMc_isCliD3d  =  (  PF_set_g_pQyMc_isCliD3d  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "set_g_pQyMc_isCliD3d"  );
	 
	
	 //
	 pFuncs->isCliD3d.pf_dllInit_d3d_isCli  =  (  PF_dllInit_d3d_isCli  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "dllInit_d3d_isCli"  );
	 pFuncs->isCliD3d.pf_dllExit_d3d_isCli  =  (  PF_dllExit_d3d_isCli  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "dllExit_d3d_isCli"  );		
	 //
	 pFuncs->isCliD3d.pf_GBuf_d3d_isCli_new  =  (  PF_GBuf_d3d_isCli_new  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "GBuf_d3d_isCli_new"  );
	 pFuncs->isCliD3d.pf_GBuf_d3d_isCli_free  =  (  PF_GBuf_d3d_isCli_free  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "GBuf_d3d_isCli_free"  );				
	 //
	 pFuncs->isCliD3d.pf_getMaxCnt_wallMems  =  (  PF_getMaxCnt_wallMems  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "getMaxCnt_wallMems"  );
	 pFuncs->isCliD3d.pf_getWallMemByIndex  =  (  PF_getWallMemByIndex  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "getWallMemByIndex"  );
	 
	 //  2014/11/05	 
	 //
	 pFuncs->isCliD3d.pf_bD3dUsing  =  (  PF_bD3dUsing  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "bD3dUsing"  );
	 pFuncs->isCliD3d.pf_bFullScreen_d3dWnd  =  (  PF_bFullScreen_d3dWnd  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "bFullScreen_d3dWnd"  );
		
	 //
	 pFuncs->isCliD3d.pf_createConsoleWall  =  (  PF_createConsoleWall  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "createConsoleWall"  );
	 pFuncs->isCliD3d.pf_closeConsoleWall  =  (  PF_closeConsoleWall  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "closeConsoleWall"  );
	 //
	 pFuncs->isCliD3d.pf_createGeneralWall  =  (  PF_createGeneralWall  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "createGeneralWall"  );

	 //  2015/06/05
	 //
	 pFuncs->isCliD3d.pf_myPreRender = (PF_myPreRender)GetProcAddress(pFuncs->isCliD3d.hDll, "myPreRender");
	 pFuncs->isCliD3d.pf_myRender  =  (  PF_myRender  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "myRender"  );
		
	 //  2015/10/06
	 pFuncs->isCliD3d.pf_getTex2Props  =  (  PF_getTex2Props  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "getTex2Props"  );
	 //
	 pFuncs->isCliD3d.pf_fillData_d3d  =  (  PF_fillData_d3d  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "fillData_d3d"  );
	 pFuncs->isCliD3d.pf_fillData_d3d_setDataReady  =  (  PF_fillData_d3d_setDataReady  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "fillData_d3d_setDataReady"  );

	 //
	 pFuncs->isCliD3d.pf_doProc_readRtt  =  (  PF_doProc_readRtt  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "doProc_readRtt"  );
																														 

	 //
	 pFuncs->isCliD3d.pf_qisWallsCfgNew  =  (  PF_qisWallsCfgNew  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "qisWallsCfgNew"  );
	 pFuncs->isCliD3d.pf_qisWallsCfgFree  =  (  PF_qisWallsCfgFree  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "qisWallsCfgFree"  );

	 //  2015/11/30
	 pFuncs->isCliD3d.pf_addQisWallCfg  =  (  PF_addQisWallCfg  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "addQisWallCfg"  );
	 pFuncs->isCliD3d.pf_setCurQisWallCfg  =  (  PF_setCurQisWallCfg  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "setCurQisWallCfg"  );


	 //  2014/10/31
	 pFuncs->isCliD3d.pf_removeMosaicFromD3dWall  =  (  PF_removeMosaicFromD3dWall  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "removeMosaicFromD3dWall"  );
	 pFuncs->isCliD3d.pf_getVal_bExists_mosaic  =  (  PF_getVal_bExists_mosaic  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "getVal_bExists_mosaic"  );

	 //
	 pFuncs->isCliD3d.PF_bDisplayMcViewContent_d3dWall  =   (  PF_bDisplayMcViewContent_d3dWall  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "bDisplayMcViewContent_d3dWall"  );

	 //
	 pFuncs->isCliD3d.pf_d3dWall_doLayout  =  (  PF_d3dWall_doLayout  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "d3dWall_doLayout"  );

	 //  2015/12/07
	 //pFuncs->isCliD3d.pf_renew_dwModifiedTickCnt_layout  =  (  PF_renew_dwModifiedTickCnt_layout  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "renew_dwModifiedTickCnt_layout"  );

	 //  2015/12/12
	 pFuncs->isCliD3d.pf_tryToTalkToMessenger_d3dWall  =  (  PF_tryToTalkToMessenger_d3dWall  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "tryToTalkToMessenger_d3dWall"  );

	 //
	 //pFuncs->isCliD3d.pf_d3dWall_refreshWallMemInfo  =  (  PF_d3dWall_refreshWallMemInfo  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "d3dWall_refreshWallMemInfo"  );
	 //
	 pFuncs->isCliD3d.pf_d3dWall_askToRefreshBg = (PF_d3dWall_askToRefreshBg)GetProcAddress(pFuncs->isCliD3d.hDll, "d3dWall_askToRefreshBg");
	 //
	 pFuncs->isCliD3d.pf_d3dWall_askToRefreshMenu  =  (  PF_d3dWall_askToRefreshMenu  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "d3dWall_askToRefreshMenu"  );
	 pFuncs->isCliD3d.pf_d3dWall_askToRefreshIa  =  (  PF_d3dWall_askToRefreshIa  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "d3dWall_askToRefreshIa"  );

	 //
	 pFuncs->isCliD3d.pf_getVal_bWmTalkerShadowExists  =  (  PF_getVal_bWmTalkerShadowExists  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "getVal_bWmTalkerShadowExists"  );

	 //  2015/10/30
	 //pFuncs->isCliD3d.pf_DXUTSaveTextureToFile  =  (  PF_DXUTSaveTextureToFile  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "my_DXUTSaveTextureToFile"  );

	 //  2016/02/25
	 pFuncs->isCliD3d.pf_refreshDlgTalkSubtitleMsgs_d3dWall  =  (  PF_refreshDlgTalkSubtitleMsgs_d3dWall  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "refreshDlgTalkSubtitleMsgs_d3dWall"  );
	 pFuncs->isCliD3d.pf_refreshDlgTalkSubtitlesCfg_d3dWall  =  (  PF_refreshDlgTalkSubtitlesCfg_d3dWall  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "refreshDlgTalkSubtitlesCfg_d3dWall"  );

	 //
	 pFuncs->isCliD3d.pf_d3dWall_refreshAllWallMems  =  (  PF_d3dWall_refreshAllWallMems  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "d3dWall_refreshAllWallMems"  );
	//  2015/12/12
	pFuncs->isCliD3d.pf_d3dWall_refreshWallMemByTalker  =  (  PF_d3dWall_refreshWallMemByTalker  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "d3dWall_refreshWallMemByTalker"  );

	//
	//  2016/01/25
	pFuncs->isCliD3d.pf_d3dWall_refreshImgs  =  (  PF_d3dWall_refreshImgs  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "d3dWall_refreshImgs"  );
	//
	pFuncs->isCliD3d.pf_test_d3dWall_chkImgs = (PF_test_d3dWall_chkImgs)GetProcAddress(pFuncs->isCliD3d.hDll, "test_d3dWall_chkImgs");

	//
	pFuncs->isCliD3d.pf_tryToChkD3dWall = (PF_tryToChkD3dWall)GetProcAddress(pFuncs->isCliD3d.hDll, "tryToChkD3dWall");

	//
	pFuncs->isCliD3d.pf_qisWall_exit = (PF_qisWall_exit)GetProcAddress(pFuncs->isCliD3d.hDll, "qisWall_exit");

	//
	pFuncs->isCliD3d.pf_CUBOID_tool_exit = (PF_CUBOID_tool_exit)GetProcAddress(pFuncs->isCliD3d.hDll, "CUBOID_tool_exit");

	//
	pFuncs->isCliD3d.pf_resetForResize = (PF_resetForResize)GetProcAddress(pFuncs->isCliD3d.hDll, "resetForResize");

	//
	pFuncs->isCliD3d.pf_d3dWnd_OnMouseMove = (PF_d3dWnd_OnMouseMove)GetProcAddress(pFuncs->isCliD3d.hDll, "d3dWnd_OnMouseMove");
	pFuncs->isCliD3d.pf_d3dWnd_OnMove = (PF_d3dWnd_OnMove)GetProcAddress(pFuncs->isCliD3d.hDll, "d3dWnd_OnMove");
	pFuncs->isCliD3d.pf_d3dWnd_OnMoving = (PF_d3dWnd_OnMoving)GetProcAddress(pFuncs->isCliD3d.hDll, "d3dWnd_OnMoving");
	//
	pFuncs->isCliD3d.pf_D3D_devCtx_pool_exit = (PF_D3D_devCtx_pool_exit)GetProcAddress(pFuncs->isCliD3d.hDll, "D3D_devCtx_pool_exit");
	pFuncs->isCliD3d.pf_get_D3D_devCtx_pool = (PF_get_D3D_devCtx_pool)GetProcAddress(pFuncs->isCliD3d.hDll, "get_D3D_devCtx_pool");
	//
	pFuncs->isCliD3d.pf_generalWall_OnIsCmd = (PF_generalWall_OnIsCmd)GetProcAddress(pFuncs->isCliD3d.hDll, "generalWall_OnIsCmd");
	//
	pFuncs->isCliD3d.pf_InitD3D = (PF_InitD3D)GetProcAddress(pFuncs->isCliD3d.hDll, "InitD3D");
	pFuncs->isCliD3d.pf_InitGraphics=(PF_InitGraphics)GetProcAddress(pFuncs->isCliD3d.hDll,"InitGraphics");
	pFuncs->isCliD3d.pf_Cleanup = (PF_Cleanup)GetProcAddress(pFuncs->isCliD3d.hDll, "Cleanup");
	//
	pFuncs->isCliD3d.pf_InitGraphics11 = (PF_InitGraphics11)GetProcAddress(pFuncs->isCliD3d.hDll, "InitGraphics11");

	//
	pFuncs->isCliD3d.pf_renderNote_otherTalker = (PF_renderNote_otherTalker)GetProcAddress(pFuncs->isCliD3d.hDll, "renderNote_otherTalker");
	pFuncs->isCliD3d.pf_renderNote_otherTalker_func = (PF_renderNote_otherTalker_func)GetProcAddress(pFuncs->isCliD3d.hDll, "renderNote_otherTalker_func");
	//
	pFuncs->isCliD3d.pf_renderNoteFunc_importantNote = (PF_renderNoteFunc_importantNote)GetProcAddress(pFuncs->isCliD3d.hDll, "renderNoteFunc_importantNote");
	pFuncs->isCliD3d.pf_renderImportantNote = (PF_renderImportantNote)GetProcAddress(pFuncs->isCliD3d.hDll, "renderImportantNote");
	pFuncs->isCliD3d.pf_renderSubtitles = (PF_renderSubtitles)GetProcAddress(pFuncs->isCliD3d.hDll, "renderSubtitles");
	//
	pFuncs->isCliD3d.pf_addWmEnlarge = (PF_addWmEnlarge)GetProcAddress(pFuncs->isCliD3d.hDll, "addWmEnlarge");
	//
	pFuncs->isCliD3d.pf_d3dWall_av = (PF_d3dWall_av)GetProcAddress(pFuncs->isCliD3d.hDll, "d3dWall_av");
	pFuncs->isCliD3d.pf_talkerFrm_init = (PF_talkerFrm_init)GetProcAddress(pFuncs->isCliD3d.hDll, "talkerFrm_init");
	pFuncs->isCliD3d.pf_talkerFrm_exit = (PF_talkerFrm_init)GetProcAddress(pFuncs->isCliD3d.hDll, "talkerFrm_exit");

	pFuncs->isCliD3d.pf_talkerFrm_mosaic_init = (PF_talkerFrm_mosaic_init)GetProcAddress(pFuncs->isCliD3d.hDll, "talkerFrm_mosaic_init");
	pFuncs->isCliD3d.pf_talkerFrm_mosaic_exit = (PF_talkerFrm_mosaic_exit)GetProcAddress(pFuncs->isCliD3d.hDll, "talkerFrm_mosaic_exit");

	//
	pFuncs->isCliD3d.pf_d3dWall_closeDlgTalk = (PF_d3dWall_closeDlgTalk)GetProcAddress(pFuncs->isCliD3d.hDll, "d3dWall_closeDlgTalk");

	//
	pFuncs->isCliD3d.pf_d3dWall_enlargeWall = (PF_d3dWall_enlargeWall)GetProcAddress(pFuncs->isCliD3d.hDll, "d3dWall_enlargeWall");

	//
	pFuncs->isCliD3d.pf_hideAllCtrls_dxDialog = (PF_hideAllCtrls_dxDialog)GetProcAddress(pFuncs->isCliD3d.hDll, "hideAllCtrls_dxDialog");

	//
	pFuncs->isCliD3d.pf_d3dWall_cleanMessageBox = (PF_d3dWall_cleanMessageBox)GetProcAddress(pFuncs->isCliD3d.hDll, "d3dWall_cleanMessageBox");
	pFuncs->isCliD3d.pf_d3dWall_MessageBox = (PF_d3dWall_MessageBox)GetProcAddress(pFuncs->isCliD3d.hDll, "d3dWall_MessageBox");


	//
	pFuncs->isCliD3d.pf_g_DialogResourceManager_StoreD3D11State = (PF_g_DialogResourceManager_StoreD3D11State)GetProcAddress(pFuncs->isCliD3d.hDll, "g_DialogResourceManager_StoreD3D11State");
	pFuncs->isCliD3d.pf_g_DialogResourceManager_ApplyRenderUI11 = (PF_g_DialogResourceManager_ApplyRenderUI11)GetProcAddress(pFuncs->isCliD3d.hDll, "g_DialogResourceManager_ApplyRenderUI11");
	pFuncs->isCliD3d.pf_g_DialogResourceManager_RestoreD3D11State = (PF_g_DialogResourceManager_RestoreD3D11State)GetProcAddress(pFuncs->isCliD3d.hDll, "g_DialogResourceManager_RestoreD3D11State");

	//
	pFuncs->isCliD3d.pf_myRender_tool = (PF_myRender_tool)GetProcAddress(pFuncs->isCliD3d.hDll, "myRender_tool");

	//
	pFuncs->isCliD3d.pf_stopUsingD3d = (PF_stopUsingD3d)GetProcAddress(pFuncs->isCliD3d.hDll, "stopUsingD3d");

	//
	pFuncs->isCliD3d.pf_chkAndRecoverD3dImg = (PF_chkAndRecoverD3dImg)GetProcAddress(pFuncs->isCliD3d.hDll, "chkAndRecoverD3dImg");

	//
	pFuncs->isCliD3d.pf_d3dWall_OnSize = (PF_d3dWall_OnSize)GetProcAddress(pFuncs->isCliD3d.hDll, "d3dWall_OnSize");

	//
	pFuncs->isCliD3d.pf_saveTex12 = (PF_saveTex12)GetProcAddress(pFuncs->isCliD3d.hDll, "saveTex");


	 //
	 pFuncs->isCliD3d.bOk  =  TRUE;


	 

	 //
	 iErr  =  0;

errLabel:
	 return  iErr;
}

int  unload_isCliD3d(  FUNCS_for_isCliHelp  *  pFuncs  )
{
	//  FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );

	//
	pFuncs->isCliD3d.bOk  =  FALSE;

	if  (  pFuncs->isCliD3d.hDll  )  {
		FreeLibrary(  pFuncs->isCliD3d.hDll  );
		pFuncs->isCliD3d.hDll  =  NULL;
	}



	//
	return  0;
}


/////////////////////////////////

int  load_aiResize( FUNCS_for_isCliHelp* pFuncs)
{
	int						iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;

	TCHAR				tmpFileName[MAX_PATH + 1];
	TCHAR				pathBuf[MAX_PATH + 1];
	TCHAR* filePart;
	HINSTANCE			hDll = NULL;
	PF_pCommonHandler	pf = NULL;



	GetModuleFileName(NULL, tmpFileName, sizeof(tmpFileName) / sizeof(tmpFileName[0]));
	if (!GetFullPathName(tmpFileName, sizeof(pathBuf) / sizeof(pathBuf[0]), pathBuf, &filePart))  goto  errLabel;
	filePart[0] = 0;

	//
#if  10
	//
	_sntprintf(tmpFileName, mycountof(tmpFileName), _T("%s%s"), pathBuf, _T("module_aiResize.dll"));
	pFuncs->aiResize.hDll = LoadLibrary(tmpFileName);
	if (!pFuncs->aiResize.hDll)  goto  errLabel;

	//
	pFuncs->aiResize.pf_doPre_toPlayVideo = (PF_doPre_toPlayVideo)GetProcAddress(pFuncs->isCliD3d.hDll, "doPre_toPlayVideo");
#endif 

	//
	pFuncs->aiResize.bOk = TRUE;

	//
	iErr = 0;

errLabel:
	return  iErr;
}

int  unload_aiResize(FUNCS_for_isCliHelp* pFuncs)
{
	//  FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );

	//
	pFuncs->aiResize.bOk = FALSE;

	if (pFuncs->aiResize.hDll) {
		FreeLibrary(pFuncs->aiResize.hDll);
		pFuncs->aiResize.hDll = NULL;
	}

	//
	return  0;
}



///////////////////////////

 
//
int load_isCliSaveAv(FUNCS_for_isCliHelp* pFuncs)
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;

	TCHAR				tmpFileName[MAX_PATH + 1];
	TCHAR				pathBuf[MAX_PATH + 1];
	TCHAR* filePart;
	//  HINSTANCE			hDll							=		NULL;
	PF_pCommonHandler	pf = NULL;


	GetModuleFileName(NULL, tmpFileName, sizeof(tmpFileName) / sizeof(tmpFileName[0]));
	if (!GetFullPathName(tmpFileName, sizeof(pathBuf) / sizeof(pathBuf[0]), pathBuf, &filePart))  goto  errLabel;
	filePart[0] = 0;

	_sntprintf(tmpFileName, mycountof(tmpFileName), _T("%sisCliSaveAv.dll"), pathBuf);
	pFuncs->isCliSaveAv.hDll = LoadLibrary(tmpFileName);
	if (!pFuncs->isCliSaveAv.hDll)  goto  errLabel;

	//
	pFuncs->isCliSaveAv.pf_setGuiOpen_saveAv = (PF_setGuiOpen_saveAv)GetProcAddress(pFuncs->isCliSaveAv.hDll, "setGuiOpen_saveAv");
	if (!pFuncs->isCliSaveAv.pf_setGuiOpen_saveAv)  goto  errLabel;
	//
	pFuncs->isCliSaveAv.pf_getSize_SAVE_av_procInfo = (PF_getSize_SAVE_av_procInfo)GetProcAddress(pFuncs->isCliSaveAv.hDll, "getSize_SAVE_av_procInfo");
	if (!pFuncs->isCliSaveAv.pf_getSize_SAVE_av_procInfo)  goto  errLabel;
	//			 
	pFuncs->isCliSaveAv.pf_doSaveAv = (PF_doSaveAv)GetProcAddress(pFuncs->isCliSaveAv.hDll, "doSaveAv");
	if (!pFuncs->isCliSaveAv.pf_doSaveAv)  goto  errLabel;
	//
	pQyMc->guiOpen_saveAv.pf_q2GetMsg = q2GetMsg;
	pQyMc->guiOpen_saveAv.pf_myGetTickCount = myGetTickCount;
	pQyMc->guiOpen_saveAv.pf_showInfo = showInfo_open0;
	pQyMc->guiOpen_saveAv.pf_getTimelStr = getTimelStr;
	pQyMc->guiOpen_saveAv.pf_gettTimeBylStr = gettTimeBylStr;
	//
	pFuncs->isCliSaveAv.pf_setGuiOpen_saveAv(&pQyMc->guiOpen_saveAv);
	//
	pFuncs->isCliSaveAv.bOk = TRUE;

	iErr = 0;
errLabel:
	return  iErr;

}


int  unload_isCliSaveAv(FUNCS_for_isCliHelp* pFuncs)
{
	//  FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );

	//
	pFuncs->isCliSaveAv.bOk = FALSE;

	if (pFuncs->isCliSaveAv.hDll) {
		FreeLibrary(pFuncs->isCliSaveAv.hDll);
		pFuncs->isCliSaveAv.hDll = NULL;
	}



	//
	return  0;
}









//
#if  0
int load_ancPktProcess(FUNCS_for_isCliHelp* pFuncs)
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;

	TCHAR				tmpFileName[MAX_PATH + 1];
	TCHAR				pathBuf[MAX_PATH + 1];
	TCHAR* filePart;
	//  HINSTANCE			hDll							=		NULL;
	PF_pCommonHandler	pf = NULL;


	GetModuleFileName(NULL, tmpFileName, sizeof(tmpFileName) / sizeof(tmpFileName[0]));
	if (!GetFullPathName(tmpFileName, sizeof(pathBuf) / sizeof(pathBuf[0]), pathBuf, &filePart))  goto  errLabel;
	filePart[0] = 0;

#if  10
	_sntprintf(tmpFileName, mycountof(tmpFileName), _T("%sancPktProcess.dll"), pathBuf);
	pFuncs->ancPktProcess.hDll = LoadLibrary(tmpFileName);
	if (!pFuncs->ancPktProcess.hDll)  goto  errLabel;

	//
	pFuncs->ancPktProcess.pf_bPktSkipped = (PF_bPktSkipped)GetProcAddress(pFuncs->ancPktProcess.hDll, "bPktSkipped");
	if (!pFuncs->ancPktProcess.pf_bPktSkipped)  goto  errLabel;
	//
	pFuncs->ancPktProcess.pf_player_get_fps = (PF_player_get_fps)GetProcAddress(pFuncs->ancPktProcess.hDll, "player_get_fps");
	if (!pFuncs->ancPktProcess.pf_player_get_fps)  goto  errLabel;
#endif 

	//
	pFuncs->ancPktProcess.bOk = true;

	//

	iErr = 0;
errLabel:
	return  iErr;

}


int  unload_ancPktProcess(FUNCS_for_isCliHelp* pFuncs)
{
	//  FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );

	//
	pFuncs->ancPktProcess.bOk = FALSE;

	if (pFuncs->ancPktProcess.hDll) {
		FreeLibrary(pFuncs->ancPktProcess.hDll);
		pFuncs->ancPktProcess.hDll = NULL;
	}




	//
	return  0;
}
#endif 



//
////////////
int  load_help_audioProc(  FUNCS_for_isCliHelp  *  pFuncs  )
{
	int						iErr	=	-1;
	
	TCHAR				tmpFileName[MAX_PATH  +  1];
	 TCHAR				pathBuf[MAX_PATH  +  1];
	 TCHAR			*	filePart;
	 HINSTANCE			hDll							=		NULL;
	 PF_pCommonHandler	pf								=		NULL;
	 

	 GetModuleFileName(  NULL,  tmpFileName,  sizeof(  tmpFileName  )  /  sizeof(  tmpFileName[0]  )  );
	 if  (  !GetFullPathName(  tmpFileName,  sizeof(  pathBuf  )  /  sizeof(  pathBuf[0]  ),  pathBuf,  &filePart  )  )  goto  errLabel;
	 filePart[0]  =  0;

#if  10
	 _sntprintf(  tmpFileName,  mycountof(  tmpFileName  ),  _T(  "%shelp_audioProc.dll"  ),  pathBuf  );
	 pFuncs->help_audioProc.hDll  =  LoadLibrary(  tmpFileName  );
	 if  (  !pFuncs->help_audioProc.hDll  )  goto  errLabel;
#endif

	 //
	 pFuncs->help_audioProc.pf_initAecObj  =  (  PF_initAecObj  )GetProcAddress(  pFuncs->help_audioProc.hDll,  "initAecObj"  );
	 pFuncs->help_audioProc.pf_exitAecObj  =  (  PF_exitAecObj  )GetProcAddress(  pFuncs->help_audioProc.hDll,  "exitAecObj"  );
	 pFuncs->help_audioProc.pf_aecObj_doAec  =  (  PF_aecObj_doAec  )GetProcAddress(  pFuncs->help_audioProc.hDll,  "aecObj_doAec"  );
	 
	 //
	 pFuncs->help_audioProc.pf_initAudioMixerObj = (PF_initAudioMixerObj)GetProcAddress(pFuncs->help_audioProc.hDll, "initAudioMixerObj");
	 pFuncs->help_audioProc.pf_exitAudioMixerObj = (PF_exitAudioMixerObj)GetProcAddress(pFuncs->help_audioProc.hDll, "exitAudioMixerObj");
	 pFuncs->help_audioProc.pf_audioMixerObj_doMix = (PF_audioMixerObj_doMix)GetProcAddress(pFuncs->help_audioProc.hDll, "audioMixerObj_doMix");


	 //
	 pFuncs->help_audioProc.bOk  =  TRUE;

	 iErr  =  0;

errLabel:
	 return  iErr;
}

int  unload_help_audioProc(  FUNCS_for_isCliHelp  *  pFuncs  )
{
	//  FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );

	//
	pFuncs->help_audioProc.bOk  =  FALSE;

	if  (  pFuncs->help_audioProc.hDll  )  {
		FreeLibrary(  pFuncs->help_audioProc.hDll  );
		pFuncs->help_audioProc.hDll  =  NULL;
	}

	return  0;
}

//
int  load_help_webrtc1(FUNCS_for_isCliHelp* pFuncs)
{
	int						iErr = -1;

	TCHAR				tmpFileName[MAX_PATH + 1];
	TCHAR				pathBuf[MAX_PATH + 1];
	TCHAR* filePart;
	HINSTANCE			hDll = NULL;
	PF_pCommonHandler	pf = NULL;


	GetModuleFileName(NULL, tmpFileName, sizeof(tmpFileName) / sizeof(tmpFileName[0]));
	if (!GetFullPathName(tmpFileName, sizeof(pathBuf) / sizeof(pathBuf[0]), pathBuf, &filePart))  goto  errLabel;
	filePart[0] = 0;

	//
#ifdef  __DEBUG__
#if 0
	showInfo_open0(0, 0, _T("for debug: set path for webrtc1"));
	_sntprintf(pathBuf, mycountof(pathBuf), _T("D:\\root\\webrtc\\src\\out\\Default1\\"));
#endif
#endif

#if  10
	_sntprintf(tmpFileName, mycountof(tmpFileName), _T("%shelp_webrtc1.dll"), pathBuf);
	pFuncs->help_webrtc1.hDll = LoadLibrary(tmpFileName);
	if (!pFuncs->help_webrtc1.hDll)  goto  errLabel;
#endif

	//

	//
	pFuncs->help_webrtc1.pf_help_webrtc_init = (PF_help_webrtc_init)GetProcAddress(pFuncs->help_webrtc1.hDll, "help_webrtc_init");
	pFuncs->help_webrtc1.pf_help_webrtc_exit = (PF_help_webrtc_exit)GetProcAddress(pFuncs->help_webrtc1.hDll, "help_webrtc_exit");

	//
	pFuncs->help_webrtc1.bOk = TRUE;

	iErr = 0;

errLabel:
	return  iErr;
}

int  unload_help_webrtc1(FUNCS_for_isCliHelp* pFuncs)
{
	//  FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );

	//
	pFuncs->help_webrtc1.bOk = FALSE;

	if (pFuncs->help_webrtc1.hDll) {
		FreeLibrary(pFuncs->help_webrtc1.hDll);
		pFuncs->help_webrtc1.hDll = NULL;
	}

	return  0;
}


