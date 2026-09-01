
#ifndef  __isCliHelpPublic_h__
#define  __isCliHelpPublic_h__		//  {


#include	"qisGuiPublic_public.h"
#include	"qisD3dDefs.h"
#include	"dlgTalkPublic.h"

//
#include	"ctxQmc.h"

//
 //
#define		MAX_nElapseInS							5		//  20	//  2015/07/18
#define		MAX_nTimeoutInS							65


//  2017/08/25
#define		CONST_usConfType_null					0
//
#define		CONST_usConfType_consult				10
//
#define		CONST_usConfType_emergencyCommand		20			//  Ó¦¼±Ö¸»Ó



//
  __declspec(dllexport)  int   set_g_pQyMc_isCliHelp(  void  *  pQyMc  );
  __declspec(dllexport)  int   set_g_dbPool_isCliHelp(  void  *  pPool  );
  __declspec(  dllexport  )  BOOL  dll_PreTranslateMessage_isCliHelp(  MSG  *  pMsg  );


  
  //
  __declspec(  dllexport  )  int  showDlgImObjRule(  HWND  hParent,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );
  __declspec(  dllexport  )  int  showDlgImObjRule(  HWND  hParent,  HWND  hCurTalk  );

  __declspec(  dllexport  )  int  showDlgSubtitleSelect(  HWND  hParent,  void  *  pSUBTITLE_cfg  );
 
  //
  __declspec(  dllexport  )  int  viewDlgMsgTool_talk(  HWND  hParent,  HWND  hCurTalk,  BOOL  bUseHtmlEdit  );
  __declspec(  dllexport  )  void  *  getDlgMsgToolVar(  HWND  hDlgMsgTool  );

  //  2016/03/23
  __declspec(  dllexport  )  int  viewDlgMsgInput_talk(  HWND  hParent,  HWND  hCurTalk,  HWND  *  phWnd_msgInput  );
  __declspec(  dllexport  )  BOOL  setMsgInputPos(  HWND  hWnd_msgInput,  int  iX_screen,  int  iY_screen,  int  iW,  int  iH  );




  //
  __declspec(  dllexport  )  int  showDlgPtzSettings(  HWND  hParent  );
  __declspec(  dllexport  )  int  getPtzSettings(  void  *  pCOM_PORT_cfg  );

  //
  __declspec(  dllexport  )  int  showDlgRemoteStorageSettings(  HWND  hParent  );


  //
  __declspec(  dllexport  )  SUBTITLES_cfg  *  getCurSubtitlesCfg(  int  iSharedObjType,  int  iCapType,  int  iCapSubType  );
  __declspec(  dllexport  )  int  deleteSubtitlesCfg(  int  iCapType,  int  iCapSubType,  int  iUsage  );
   __declspec(  dllexport  )  int  subtitlesCfg_modify(  SUBTITLES_cfg  *  pCfg,  DWORD  dwTickCnt,  BOOL  bForce,  SUBTITLES_cfg  *  pCur,  BOOL  *  pbModified  );
   __declspec(  dllexport  )  int  getSubtitlesCfg(  int  iCapType,  int  iCapSubType,  int  iUsage,  SUBTITLES_cfg  *  pSubtitlesCfg  );
   __declspec(  dllexport  ) int  getSubtitlesCfg_d3dWall(  int  iCapType,  int  iCapSubType,  int  iUsage,  SUBTITLES_cfg  *  pSubtitlesCfg  );
   

   __declspec(  dllexport  )  int  viewDlgSubtitles(  int  iSharedObjType,  int  iCapType,  int  iCapSubType,  HWND  hParent  );
  __declspec(  dllexport  )  int  viewDlgSubtitles_talk(  int  iSharedObjType,  int  iCapType,  int  iCapSubType,  int  iUsage,  HWND  hParent,  HWND  hCurTalk,  void  *  pCurVarParam,  void  *  pMgrVarParam  );


//
typedef  struct  __dft_sendTask_cfg_t				{
					 QY_MESSENGER_ID				idInfo_dst;
					 TCHAR							file_fullName[MAX_PATH];
					 TCHAR							file_shortName[64];
					 //
					 unsigned  __int64				ui64FileLen;

}		 DFT_sendTask_cfg;


  //
  //
typedef  struct  __dft_sendTask_t					{
				 //
				 DFT_sendTask_cfg					cfg;
				 //
				 int								iStatus;
				 //
				 myTRANSFER_FILE_STATUS				transferFileStatus;
				 DWORD								dwTickCnt_modified;
				 //
}		 DFT_sendTask;


//
typedef  struct  __dft_sendTasks_t					{
				 unsigned  short					usMaxCnt;
				 unsigned  short					usCnt;
				 DFT_sendTask					*	pMems;
}		 DFT_sendTasks;


  //
  typedef  struct  __param_viewOfflineRes_t			{
				   BOOL								bNoBorder;
  }		   PARAM_viewOfflineRes;

  //
  __declspec(  dllexport  )  int  getOfflineResTaskStatus(  HWND   hOfflineRes,  DFT_sendTask  *  pTask  );

  //
  __declspec(  dllexport  )  int  viewDlgOfflineRes_talk(  HWND  hParent,  HWND  hCurTalk,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phTool  );

  //
  __declspec(  dllexport  )  int  viewDlgOfflineRes_me(  HWND  hParent,  OfflineRes_var  *  pVar,  PARAM_viewOfflineRes  *  pParam  );

  //
  __declspec(  dllexport  )  void  dlgOfflineRes_upload(  HWND  hParent,  HWND  hDlg_offlineRes,  LPCTSTR  fileName  );



  
//
typedef  int  (  *PF_dlg_YTCmd  )(  HWND  hDlg_ptz,  int  nResourceID,  void  *  p0,  void  *  p1  );

//
typedef  struct  __param_viewLocalPtzControl_t	{
				   //
				   PF_dlg_YTCmd					pf_dlg_YTCmd;
				   //
				   void						*	p0;
				   void						*	p1;
}		   PARAM_viewLocalPtzControl;

//
__declspec(  dllexport  ) int  viewLocalPtzControl(  HWND  hParent,  BOOL  bManual,  unsigned  int  uiObjType_camera,  unsigned  short  usIndex_obj,  unsigned  short  usHelp_subIndex,  PARAM_viewLocalPtzControl  *  pParam,  QIS_ptz_wnd  *  pPtzWnd  );

//
__declspec(  dllexport  )  int  ptz_resourceId2Cmd(  int  nResourceID,  int  *  pnCmd  );
//
__declspec(  dllexport  )  int  dlg_YTCmd_shareDynBmps(  HWND  hDlg_ptz,  int  nResourceID,  void  *  p0,  void  *  p1  );


//
__declspec(  dllexport  )  int doRemotePtzCmd(  void  *  p0,  PTZ_control_cmd  *  pReq,  PARAM_viewLocalPtzControl  *  pParam,  QIS_ptz_wnd  *  pPtzWnd  );

//
__declspec(  dllexport  ) int  viewRemotePtzControl(  HWND  hParent,  HWND  hCurTalk  );


  //
  __declspec(  dllexport  )  BOOL  bNoPrompt_selectAvCompressor(  unsigned  int  uiCapType,  unsigned  int  uiSubCapType  );
  __declspec(dllexport) int  viewDlgSelectAvCompressor_mfc(HWND  hParent, QY_MESSENGER_ID idInfo, unsigned  int  uiCapType, unsigned  int  uiSubCapType, int  iCapUsage, BOOL  b3D, unsigned  short  usConfType);

  //
  int  fixBgWallPolicy(  QY_MESSENGER_ID  *  pIdInfo,  unsigned  short  *  pusRows,  unsigned  short  *  pusCols,  TCHAR  *  tHint,  unsigned  int  uiCnt_tHint  );
  int  my_getnGrpMems_isCli(  QY_MESSENGER_ID  *  pIdInfo  );

  //
   __declspec(  dllexport  ) int  getBgWallCfg(  QY_MESSENGER_ID  * pIdInfo,  BgWall_cfg  *  pCfg  );
   __declspec(  dllexport  ) int  saveBgWallPolicy_neverJoinInBgWall(  QY_MESSENGER_ID  * pIdInfo,  unsigned char ucbShowBgWall_confMem  );

  //
  __declspec(  dllexport  ) int  getTalkerPolicy(  QY_MESSENGER_ID  * pIdInfo,  TALKER_policy  *  pTALKER_policy  );
  
  //
  __declspec(  dllexport  )  int  showDlgCfgVideoConference(  HWND  pParent  );

  __declspec(  dllexport  )  int  showDlgCfgWmv(  HWND  hParent  );
  
  __declspec(  dllexport  )  int  showDlgVideoCompressors(  HWND  hParent,  AV_COMPRESSOR_CFG  *  pAvCompressor,  unsigned  int  uiCapType,  unsigned int uiSubCapType,  int  iCapUsage,  int  level,  AV_COMPRESSOR_CFG  *  pCompressor_o  );

  __declspec(  dllexport  )  int  showDlgPolicyAv(  HWND  hParent,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage  );

  //
  __declspec(  dllexport  )  int  setSaveMsgFlg(  BOOL  bEnable  );

  //
  int  getNewIndex_rtspUrlList(  );
  //
  int  deleteCfg_rtspUrlList(  );

//
 __declspec(  dllexport  )  int  showDlgPolicyIsClient(  HWND  hParent  );
 __declspec(  dllexport  ) int  initPolicyAvParams(  );
 //
 __declspec(  dllexport  ) int  myGetAvCompressorCfg(  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage,  int  level,  AV_COMPRESSOR_CFG  *  pCompressor  );
 //
 __declspec(  dllexport  ) int  getCamCapType(  MC_VAR_common  *  pProcInfo  );
 __declspec(  dllexport  ) int  fixPlayCfg(  MC_VAR_isCli  *  pProcInfo,  AUDIO_PLAY_CFG  *  pPlayCfg  );
 
 //
  __declspec(  dllexport  )  int  showDlgSelect_isCli(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  int  iSelectType,  int  iObjType,  LPCTSTR  hint,  void  *  p0,  void  *  p1,  void  *  pDlgSelect_isCli_o_U  );
  __declspec(  dllexport  )  int  showDlgSelect_remoteVideo(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  int  iSelectType,  int  iObjType,  LPCTSTR  hint,  void  *  p0,  void  *  p1,  void  *  pU  );

  //
  //
#define		CONST_fw_bar		0.2	//0.15
  //
#define		CONST_avRes_space_toClose		5	
#define		CONST_dynBmps_space_skip		10	




  //
   __declspec(  dllexport  )  int  viewWallsBar(  HWND  hWndEvent,  int  iWndContentType,  int  xPos_screen,  int  yPos_screen,  HWND  hDlgWalls,  void  *  pDLG_wall_var,  BOOL  bNoDelayToView  );
   __declspec(  dllexport  )  int  setWallsBarPos(  HWND  hDlgWalls,  void  *  pDLG_wall_var,  HWND  hBar,  int  iWndContentType  );
   __declspec(  dllexport  )  BOOL  qyBar_SetDlgItemText(  HWND  hBar,  int  iBarType,  TCHAR  *  tBuf  );

   __declspec(  dllexport  )  int  showDlgMsgList(  HWND  hParent,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );

   __declspec(  dllexport  )  int  showDlgObjs(  HINSTANCE  g_hInst,  HWND  hParent,  void  *  pDLG_guiDataParam_objs  );

   __declspec(  dllexport  )  int  showMenu_wallsBar(  HINSTANCE  hInst,  HWND  hParent,  int  iWndContentType_hParent,  void  *  p2  );

   __declspec(  dllexport  )  int  viewMediaControl(  HWND  hDlgParent,  int  iIndex_capAudio,  int  iIndex_capBmp,  HWND  *  phWnd_mediaControl  );
   //__declspec(  dllexport  )  int  viewMediaControl_qmCmd(  HWND  hDlgParent,  int  iIndex_capAudio,  int  iIndex_capBmp,  HWND  *  phWnd_mediaControl  );


 __declspec(  dllexport  )  void  *  getDlgDesktopsMonVar(  HWND  hDlgDesktopsMon  );

 
 //
 __declspec(  dllexport  )  void  *  getDlgDynBmpsVar(  HWND  hDlgDynBmps  );

 //
  __declspec(  dllexport  )  void  *  getDlgVideosVar(  HWND  hDlgVideos  );

 //
 __declspec(  dllexport  )  int  showDlgVideos(  HWND  hParent,  HWND  hDlg_org,  BOOL  bDlgTalk,  void  *  pPARAM_dlgVideos,  CAP_subWnds  *  pSubWnds,  HWND  *  phWnd  );


 //
 __declspec(  dllexport  )  int  showEnlargedWnd(  HWND  hParent,  HWND  hDlg_org,  BOOL  bDlgTalk,  void  *  pPARAM_dlgVideos,  CAP_subWnds  *  pSubWnds  );

 //
 __declspec(  dllexport  )  int  showRemoteAssistWnd(  HWND  hParent,  HWND  hDlg_org,  BOOL  bDlgTalk,  void  *  pPARAM_dlgVideos,  CAP_subWnds  *  pSubWnds  );

 //
 typedef  struct  __param_viewDynBmp_t  {
				  BOOL					bAvConsole;
				  //
				  BOOL					bValid_pos;
				  int					x,  y,  w,  h;
				  BOOL					bFullScreen;
				  //
				  BOOL					bNoBorder;
 }		  PARAM_viewDynBmp;
 //
 __declspec(  dllexport  ) int  viewDynBmp(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex_obj,  LPCTSTR  cusName,  PARAM_viewDynBmp  *  pParam  );
 __declspec(  dllexport  ) int  closeDynBmp(  HWND  hParent,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex_obj  );
 __declspec(  dllexport  ) int  closeAllDynBmps(  HWND  hParent,  LPCTSTR  misServName  );
 //
 __declspec(  dllexport  ) int  findDynBmp(   LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex_obj,  HWND  *  phWnd  );


 //
 __declspec(  dllexport  ) int  viewQvcf(  HWND  hParent,  LPCTSTR  fileName  );

 //
 __declspec(  dllexport  )  int  addToWallGpsMgr(  HWND  hDlgTalk,  int  iIndex_shadow,  void  *  pmyGPS_POSITION,  HWND  hDlgWall  );
  __declspec(  dllexport  )  LRESULT  myGuiSendMessage(  HWND hWnd,  int  iWndContentType,  UINT uMsg,  WPARAM wParam,  LPARAM lParam);
  
  __declspec(  dllexport  ) int  myGetProps_vw(  char  *  buf,  void  *  pQY_props  );

   __declspec(  dllexport  )  void  *  getZoneObjs_dynBmps(  HWND  hDlgWalls,  int  iWndContentType  );
  __declspec(  dllexport  )  void  *  getZoneObjsInfo_dynBmps(  HWND  hDlgWalls,  int  iWndContentType  );
  __declspec(  dllexport  )  int  getRect_talkers_default(  HWND  hDlgWalls,  RECT  *  pRc  );

  //  2014/09/22
  //__declspec(  dllexport  )  void  *  getDlgWallsVar_shareDynBmps(  HWND  hDlgWalls,  int  iWndContentType  );

  //
  __declspec(  dllexport  )  BOOL  bFullScreen_wnd_default(  HWND  hWnd,  int  iWndContentType  );

  //  2013/09/26
   __declspec(  dllexport  ) int  viewDlgImg(  HWND  hParent,  int  iSubType,  LPCTSTR  cusName  );

  __declspec(  dllexport  )  int  popupNotificationWnd(  );
  __declspec(  dllexport  )  int  addNotification(  MIS_MSG_taskStatus  *  pStatus  );
  __declspec(  dllexport  )  int  removeNotification(  QY_MESSENGER_ID  *  pIdInfo_logicalPeer  );
  __declspec(  dllexport  )  int  clearNotification(  );
  __declspec(  dllexport  )  int  viewVWall(  HWND  hParent,  LPCTSTR  misServName,  int  iSubType,  BOOL  bNewVirtualWall,  LPCTSTR  init_qvwFile,  BOOL  bNeedNotShowWnd,  HWND  *  phWnd  );
  //
  __declspec(  dllexport  )  int  viewVWall_hbwj(  HWND  hParent,  LPCTSTR  misServName,  int  iSubType,  BOOL  bNewVirtualWall,  QY_MESSENGER_ID  *  pIdInfo_grp_avStream,  LPCTSTR  init_qvwFile,  BOOL  bNeedNotShowWnd,  HWND  *  phWnd  );
//
  __declspec(  dllexport  )  int  viewBgWall(  HWND  hParent,  LPCTSTR  misServName,  int  iSubType,  HWND  hDlgTalk_mgr,  LPCTSTR  init_qvwFile,  BOOL  bNeedNotShowWnd,  HWND  *  phWnd  );

  //
 
__declspec(  dllexport  )  int  dynBmps_autoLayout(  HWND  hDlgDynBmps  );
__declspec(  dllexport  )  int  dynBmps_openFile(  LPCTSTR  fileName,  HWND  hDlgDynBmps  );


  //
  __declspec(  dllexport  )  int  showDlgSelectAvDev(  HWND  hParent,  void  *  pCapStuff,  int  iMenuId_selected,  BOOL  *  pbUnresizable  );
  __declspec(  dllexport  )  int  showDlgOpAvDev(  HWND  hParent,  HWND  hDlg_shareDynBmps,   int objType,  int  index_obj_selected,  BOOL  *  pbUnresizable  );
  __declspec(  dllexport  )  int  showDlgOpScreen(  HWND  hParent,  HWND  hDlg_shareDynBmps,  int  index_obj_selected  );


   //  __declspec(  dllexport  )  int  dlgTalk_OnQyPostComm_idcInited(  HWND  hDlg,  void  *  pDLG_TALK_var,  UINT  wParam,  LONG  lParam  );
   //__declspec(  dllexport  )  int  dlgTalk_OnInitDialog_createHtmlEdits(  HWND  hDlgTalk,  void  *  pDLG_TALK_var  );
   //  __declspec(  dllexport  ) int  dlgTalk_OnQyComm_getDropTarget(  HWND  hDlg,  void  *  pDLG_TALK_var,  UINT  wParam,  LONG  lParam  );
    __declspec(  dllexport  )  int  doDoc_doTable_byRowId_param(  void  *  pDLG_TALK_var,  void  *  pPARAM_PROC_ROW  );

	//
	__declspec(  dllexport  ) int  dlgMsgTool_OnQyComm_getDropTarget(  HWND  hDlg,  void  *  pvar,  WPARAM  wParam,  LPARAM  lParam  );

#ifdef  __DEBUG__
 __declspec(  dllexport  )	int  printHtmlEdit(  void  *  pCMyHtmlEditCtrl  );
#endif
 __declspec(  dllexport  )  int  parseQmInternalUrl(  LPCTSTR  url,  int  *  piTaskId,  TCHAR  *  rowIdStr,  unsigned  int  rowIdStrCnt,  unsigned  short  *  pusOp,  TCHAR  *  paramStr,  unsigned  int  paramStrCnt  );

 __declspec(dllexport) int  tmpHandler_findTalker(void* p0, void* pCommonParam1Param, void* pQElem);
   __declspec(  dllexport  )  int  findTalker(  void  *  pQyMcParam,  MSGR_ADDR  *  pAddr,  unsigned  int  unused,  HWND  *  phWnd  );


   //
   typedef  struct  __info_recv_screenTask_t		{
					QY_MESSENGER_ID				idInfo_sender;
					//

   }		INFO_recv_screenTask;

   //
   //
typedef  struct  __info_recvResource_t		{
	
				 //
				 int						nScreens;
				 int						nMediaFiles;
				 int						nMediaFiles_unresizable;
				 int						iW_unresizable;
				 int						iH_unresizable;
				 int						iTaskId_recvdResource;
				 //
				 BOOL						bExists_remoteAssist;

				 //
				 INFO_recv_screenTask		screenTasks[3];

}		 INFO_recvResource;


//
typedef  struct  __info_sendResource_t		{

				 //
				 int						nScreens;
				 int						nMediaFiles;
				 int						nMediaFiles_unresizable;
				 int						iW_unresizable;
				 int						iH_unresizable;
				 int						iTaskId_sendingResource;
				 //
				 BOOL						bExists_remoteAssist;

}		 INFO_sendResource;

//
__declspec(dllexport)  BOOL  bTaskExists_recvResource1(int iIndex_taskInfo, INFO_recvResource* pParam);  //  int  *  pnScreens,  int  *  pnMediaFiles,  int  *  pnMediaFiles_unresizable,  int  *  piW_unresizable,  int  *  piH_unresizable,  int  *  piTaskId_recvdResource  );


//
__declspec(  dllexport  )  BOOL  bTaskExists_recvResource1(  void  *  pMgrVar,  INFO_recvResource  *  pInfo  );
__declspec(  dllexport  )  BOOL  bTaskExists_sendingResource1(  void  *  pMgrVar,  INFO_sendResource  *  pInfo  );

   //
   __declspec(  dllexport  )  BOOL  bTaskExists_recvResource(  void  *  pMgrVar,  int  *  pnScreens,  int  *  pnMediaFiles,  int  *  pnMediaFiles_unresizable,  int  *  piW_unresizable,  int  *  piH_unresizable,  int  *  piTaskId_recvdResource  );
   __declspec(  dllexport  )  BOOL  bTaskExists_sendingResource(  void  *  pMgrVar,  int  *  pnScreens,  int  *  pnMediaFiles,  int  *  pnMediaFiles_unresizable,  int  *  piW_unresizable,  int  *  piH_unresizable,  int  *  piTaskId_sendingResource  );

   //
    __declspec(  dllexport  )  int  dlgTalk_getCurSubtitlesCfg(  HWND  hDlgTalk,  SUBTITLES_cfg  *  pCfg  );
  __declspec(  dllexport  )  int  dlgTalk_getSubtitleMsgs(  HWND  hDlgTalk,  SUBTITLE_msgs  *  pMsgs  );


   //
   __declspec(  dllexport  )  int  closeInstantAssistant(  HWND  hDlgTalk  );
   __declspec(  dllexport  )  int  closeMoreIa(  HWND  hDlgTalk  );

   //
   __declspec(  dllexport  )  int  sizeAllControls_dlgTalk(  HWND  hDlg,  void  *  pDLG_TALK_var,  RECT  *  pRect  );
   __declspec(  dllexport  )  int  activateRowByRowId(  HWND  hDlgTalk,  LPCTSTR  rowIdStr  );
   __declspec(  dllexport  )  unsigned  short  dlgTalk_get_usLayoutType_local(  HWND  hDlgTalk  );

   //
   //
   __declspec(  dllexport  )  int  dlgTalk_OnCmd_shareScreen(  HWND  hCurTalk,  BOOL  bRemoteAssist  );



   //
   __declspec(  dllexport  )  MIS_MSG_TASK  *  findTaskInProcessQ(  void  *  pDLG_TALK_var,  int  iTaskId,  BOOL  bNextAv  =  FALSE,  BOOL  bToShareScreen  =  FALSE  );
   
   //
   __declspec(  dllexport  )  int  activateImTask(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  int  iTaskId_activated  );
   //
   __declspec(  dllexport  )  int  dlgTalk_getLayout(  HWND  hDlgTalk,  DLG_talk_layout  *  pLayout  );
   //
   __declspec(  dllexport  )  int  dlgTalk_doLayout(  HWND  hDlgTalk  );
   __declspec(  dllexport  )  int  dlgTalk_SetPicRect(  HWND  hDlgTalk,  int  w,  int  h,  BOOL  bMoveWindow  );

   //
   __declspec(  dllexport  )  int  dlgTalk_processPointerEvent(  HWND  hCurTalk,  int  x,  int  y,  UINT  nFlags,  BOOL  bMouseMove  =  FALSE,  BOOL  bSendForce  =  FALSE  );



   //
   __declspec(  dllexport  )  int  findTalker(  void  *  pQyMcParam,  QY_MESSENGER_ID  *  pIdInfo,  HWND  *  phWnd  );
   __declspec(  dllexport  )  int  removeTalker(  void  *  pQyMcParam,  MSGR_ADDR  *  pAddr,  unsigned  int  unused  );

   //
   __declspec(  dllexport  )  int  findTalker_shadow(void* pQyMcParam, unsigned  __int64  id, int  iTalkSubtype, HWND* phWnd);


   //
   //__declspec(  dllexport  )  int  addToRecentMsg(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  long  lRowIndex,  int  iTaskId,  MIS_MSG_TASK  * pMsgTask,  QY_MESSENGER_ID  *  pIdInfo_talker,  LPCTSTR  talkerDesc,  unsigned  short  usOp,  int  iStatus,  char  *  timeBuf,  LPCTSTR  rowIdStr,  LPCTSTR  content,  BOOL  bFollowingRows,  BOOL  bScrollIntoView,  TCHAR  *  txtBuf,  unsigned  int  uiTxtBufCnt  );
   //__declspec(dllexport)  int  addToRecentMsg(HWND  hDlgTalk, void* pDLG_TALK_var, long  lRowIndex, int  iTaskId, MIS_MSG_TASK* pMsgTask, MIS_MSG_taskStatus  *  pMsgTaskStatus,  QY_MESSENGER_ID idInfo_talker, LPCTSTR  talkerDesc, unsigned  short  usOp, int  iStatus, char* timeBuf, LPCTSTR  rowIdStr, LPCTSTR  content, BOOL  bFollowingRows, BOOL  bScrollIntoView, TCHAR* txtBuf, unsigned  int  uiTxtBufCnt);
   __declspec(dllexport)  int  addToRecentMsg(HWND  hDlgTalk, void* pDLG_TALK_var, long  lRowIndex, int  iTaskId, MIS_MSGU* pMsgU, MIS_MSG_taskStatus* pMsgTaskStatus, QY_MESSENGER_ID idInfo_talker, LPCTSTR  talkerDesc, unsigned  short  usOp, int  iStatus, char* timeBuf, LPCTSTR  rowIdStr, LPCTSTR  content, BOOL  bFollowingRows, BOOL  bScrollIntoView, TCHAR* txtBuf, unsigned  int  uiTxtBufCnt);
   __declspec(  dllexport  )  int  modifyRow(  void  *  p0,  void  *  pPARAM_PROC_ROW,  void  *  pIHTMLTableRow  );
   //  __declspec(  dllexport  )  int  getTaskItem(  CListCtrl  *  pListCtrl,  int  iTaskId  );
   __declspec(  dllexport  )  int  getTaskItem(  HWND  hListCtrl,  int  iTaskId  );
   //
   __declspec(  dllexport  )  int  addTalkerShadow(  HWND  hWall,  int  iWndContentType_wall,  WM_ID  *  pWdId,  HWND  hShadow,  HWND  hDlgTalk_mgr  );
   __declspec(  dllexport  )  int  removeTalkerShadow(  HWND  hWall,  int  iWndContentType_wall,  HWND  hShadow,  HWND  hDlgTalk_mgr  );

	//
   __declspec(  dllexport  )  BOOL  bTalkerShadowExists(  HWND  hDlgTalk_mgr,  BOOL  *  pbCanClose  );
 
   


   //
    __declspec(  dllexport  )  BOOL  bProcOfflineResToolExists_mgr(  void  *  pDLG_TALK_var_procOfflineRes_mgr  );


   //
   __declspec(  dllexport  )  int  getlRowIndex(  void  *  p0,  void  *  pPARAM_PROC_ROW,  void  *  pIHTMLTableRow  );
   __declspec(  dllexport  )  BOOL  dlgTalk_bEnableScrollBar(  HWND  hDlgTalk,  BOOL  bEnable  );
   //
   __declspec(  dllexport  )  int  viewInstantAssistant(  HWND  hWndEvent,  int  iWndContentType,  int  xPos_screen,  int  yPos_screen,  HWND  hCurTalk,  BOOL  bNoDelayToView  );
   //
   __declspec(  dllexport  )  int  fillTalkerList_func(  HWND  hCurTalk,  HWND  hTool,  void  *  pVIDEO_CONFERENCE_STATUS,  int  idcList  );

   //
    int  dlgTalk_fillPeerInfo(  HWND  hCurTalk  );

	//
	__declspec(dllexport)  BOOL  bDone_retrieveAllImObjRules(MIS_CNT* pMisCnt);

   //
   __declspec(  dllexport  )  int  getTalker_inputShadow(  HWND  hCurTalk,  HWND  *  phTalk  );



   //
 __declspec(  dllexport  )  int  talkToMessenger(  unsigned  __int64  ui64Id,  int  iTalkUsage,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phWnd  );


 //
   __declspec(  dllexport  )  BOOL  bDlgTalkWaitToAccept(  HWND  hDlgTalk  );

   __declspec(  dllexport  )  int viewStatusCli(  int  iWndContentType,  int  iSubType,  LPCTSTR  title,  int  iResId_listColumns,  PF_commonHandler  pfInitDisplayListContent,  PF_commonHandler  pfDisplayListContent  );

    __declspec(  dllexport  )  int  testLocalAv(  HWND  hParent  );
	__declspec(  dllexport  )  int  viewTestSpeed(  HWND  hParent  );

	//
	__declspec(  dllexport  )  int  tmpHandler_bRemoveMsgInProcessQ(  void  *  p0,  void  *  p1, void  *  pMsgParam  );
	
	__declspec(  dllexport  )  int mainWnd_OnQyTrayNotify(  HWND  hMainWnd,  void  *  pVar,  WPARAM  wParam,  LPARAM  lParam  );
	__declspec(  dllexport  )  void mainFrm_OnqyClearUp(  HWND  hMainWnd  );

	__declspec(  dllexport  )  int  showDlgPropImGrp(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );
	__declspec(  dllexport  )  int  showDlgPropImMsg(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  int  id  );
	__declspec(  dllexport  )  int  showDlgPropMessenger(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  int  iObjType,  QY_MESSENGER_ID  *  pIdInfo  );
	__declspec(  dllexport  )  int  showDlgPropMessenger(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  MSGR_ADDR  *  pAddr  );

	//
__declspec(  dllexport  )  int  showDlgQnmEditPcUsrInfo(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  MSGR_ADDR  *  pAddr,  int  id,  unsigned  char  ucbInTab1,  unsigned  char  *  pucbChanged  );
__declspec(  dllexport  )  int  showDlgQnmEditPcUsrInfo(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  int  iObjType,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  char  ucbInTab1,  unsigned  char  *  pucbChanged  );
__declspec(  dllexport  )  int  showDlgQnmEditPcUsrInfo(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  int  iObjType,  char  *  mac,  unsigned  char  ucbInTab1,  unsigned  char  *  pucbChanged  );

__declspec(  dllexport  )  int  showDlgPropImTask(  HWND  hParent,  QY_OBJ_DB  *  pObjDb,  BOOL  bHisTab,  int  id  );

__declspec(  dllexport  )  int  showDlgQnmSearch(  HWND  hParent,  int  *  iType  );
__declspec(  dllexport  )  int  showDlgImMsgSearch(  HWND  hParent,  MY_DB_BUF  *  pDbBufs,  int  iQueryType  );


 //

 //
  __declspec(  dllexport  )  BOOL  d3dWall_isUserActive(  int  *  piElapseInMs_userActive  );


 
  
 
 //__declspec(  dllexport  )  int  d3dWall_viewDlgTalk(  HWND  hWall_d3d  );

 //__declspec(  dllexport  )  int  d3dWall_shareScreen(  HWND  hWall_d3d  );


 
  

  

  //
  __declspec(  dllexport  )  int  d3dWall_setBg(  HWND  hWall_d3d  );
  
  //
   __declspec(  dllexport  )  int  d3dWall_openQvw(  HWND  hWall_d3d  );

   //
  __declspec(  dllexport  )  int  dlgTalk_getTaskInfo(  void  *  pProcInfoParam,  HWND  hTalkerMgr,  void  *  pTALKER_task_info  );

  //
  __declspec(  dllexport  )  int  dlgTalk_getTaskList(  void  *  pProcInfoParam,  HWND  hTalkerMgr,  void  *  pTALKER_task_list,  BOOL  *  pbModified  );


  //
   __declspec(  dllexport  )  int  viewChromaKeyCfg(  HWND  hParent,  HWND  hWnd_img,  int  iWndContentType_img,  int idc_img  );

   __declspec(  dllexport  )  int  getImgProcessCfg( QY_MC  *  pQyMc, void  *  pIMG_process_cfg  );

   //
   __declspec(  dllexport  )  int  showMenu_d3dWall(  HINSTANCE  hInst,  HWND  hParent,  int  iWndContentType_hParent,  void  *  p2  );
   __declspec(  dllexport  )  int  showMenu_generalWall(  HINSTANCE  hInst,  HWND  hParent,  int  iWndContentType_hParent,  void  *  p2  );
   //
   //
    __declspec(  dllexport  )  unsigned  int  get_uiMaxQNodes_vwRuleQ(  );

   

	//
	__declspec(  dllexport  ) int  myDrawTxt(  LPCTSTR  str,  int nPointSize,  LPCTSTR lpszFaceName,  COLORREF crColor,  int  iX,  int iY,  int  iW,  int  iH,  HWND  hWnd_dst,  HDC  hDc  );

  
	//////////////////////
	unsigned  int	dyn_getuiNextTranNo(  void  *  p0,  long  val,  long  *  puiTranNo  );
    
int  dyn_dlgTalk_getTaskInfo(  void  *  pProcInfo,  HWND  hTalkerMgr,  void  *  pTALKER_task_info  );
int  dyn_dlgTalk_getTaskList(  void  *  pProcInfoParam,  HWND  hTalkerMgr,  void  *  pTALKER_task_list,  BOOL  *  pbModified  );


	int  dyn_getSubtitlesCfg(  int  iCapType,  int  iCapSubType,  int  iUsage,  SUBTITLES_cfg  *  pSubtitlesCfg  );
	int  dyn_subtitlesCfg_modify(  SUBTITLES_cfg  *  pCfg,  DWORD  dwTickCnt,  BOOL  bForce,  SUBTITLES_cfg  *  pCur,  BOOL  *  pbModified  );
	int  dyn_getSubtitlesCfg_d3dWall(  int  iCapType,  int  iCapSubType,  int  iUsage,  SUBTITLES_cfg  *  pSubtitlesCfg  );
   
	//  2015/08/04
	 __declspec(  dllexport  )  int  procSendFile(  LPCTSTR  fullFilePath,  LPCTSTR  fileName,  void  *  pPROC_offlineRes_u,  HWND  m_hWnd,  void  *  pDLG_TALK_var,  int  *  piTaskId  );



   //
#ifdef  __DEBUG__
		__declspec(  dllexport  )  int  get_real_ij_btnDown(  int  *  p_real_i,  int  *  p_real_j,  int  *  p_img_i,  int  *  p_img_j  );

#endif

		//
#define  M_getTransferFileStatus_str(  transferFileStatus,  tBuf,  cnt  )  _sntprintf(  tBuf,  cnt,  _T(  "%d%%( %I64uk )"  ),  transferFileStatus.ucPercent,  transferFileStatus.ui64Len_recvd  /  1024  );



//
__declspec(  dllexport  )  int  cleanTalkerRuleTask(  HWND  hDlgTalk_mgr,  TALKER_dynBmp  *  pRuleDynBmp,  BOOL  b_askToRefreshLayout_mgr,  LPCTSTR  hint  );
__declspec(  dllexport  )  BOOL  bSame_dynBmpRule(  DYN_BMP_rule  *pRule1,  DYN_BMP_rule  *  pRule2  );


//
__declspec(  dllexport  )  int  cleanTalkerRuleTasks(  HWND  hDlgTalk_mgr,  BOOL  b_askToRefreshLayout_mgr,  LPCTSTR  hint  );


typedef  struct  __param_getDesc_t		{
				 int					iTaskId;
}		 PARAM_getDesc;

//
__declspec(  dllexport  )  int  getDescByIdInfo(  PARAM_getDesc  *  pParam,  QY_MESSENGER_ID  *  pIdInfo,  TCHAR  *  talkerDesc,  unsigned  int  uiCnt_talkerDesc,  TCHAR  *  displayName,  unsigned  int  uiCnt_displayName  );


//
//

//
typedef  struct  __tmpUsr_t						{
				 QY_MESSENGER_ID				idInfo;		
				 //
				 //int							id_imGrpMem;
				 //
				 TCHAR							displayName[65];
				 TCHAR							talkerDesc[128  +  1];
}		 TMP_usr;


	 


//
typedef  struct  __tmp_usrs_t					{
				 unsigned  short				usMaxCnt;
				 unsigned  short				usCnt;				
				 TMP_usr					*	pMems;
}		 TMP_usrs;

//
__declspec(  dllexport  )  void  free_TMP_usrs(  TMP_usrs  *  pTmpUsrs  );



//
__declspec(  dllexport  )  int  createTmpGrp(HWND  hParent,  IM_GRP_EX  * p );
__declspec(  dllexport  )  int  modifyTmpGrp(  HWND  hParent,  IM_GRP_EX  *  p  );

//
__declspec(  dllexport  )  int  selectMsgrsToSend(  TMP_usrs  *  pTmpUsrs   );

//
__declspec(  dllexport  )  int  viewDlgEditConsultMem(  HWND  hParent,  QY_MESSENGER_ID  *  pIdInfo_grp,  QY_MESSENGER_ID  *  pId_mem  );

//
//__declspec(  dllexport  )  int  getConsultMem(  QY_MESSENGER_ID  *pIdInfo_grp,  QY_MESSENGER_ID  *  pIdInfo_mem,  CONSULT_mem  *  pMem  );

//
//
//
__declspec(  dllexport  )  int  refresh_consult_mem(  HWND  hDlgTalk_mgr,  QY_MESSENGER_ID  *  pIdInfo_toRefresh  );

//
__declspec(  dllexport  )  int  get_conf_stat(  HWND  hDlgTalk_mgr  );


//
//
  //  2014/11/30
  typedef  struct  __param_dlgTalk_procVideo_t				{
				   BOOL										bNeed_index_capImage;
				   int										index_capBmp;
  }		   PARAM_dlgTalk_procVideo;

//
  __declspec(  dllexport  )  int  dlgTalk_procVideo(  HWND  hDlg,  void  *  pDLG_TALK_var,  MIS_MSG_procVideo_qmc  *  pMsg,  PARAM_dlgTalk_procVideo  *  pParam  );

  //
 __declspec(  dllexport  )  int viewDlgCfgBgWall(  HWND  hParent,  HWND  hDlgTalk_mgr,  HWND  *  phWnd  );

 //
 __declspec(dllexport  )  bool  isActiveMemsFull(  int  iTaskId,  bool  bSpeaker  );


 //
 __declspec(dllexport)  int  selectAvDev(void* pCapStuffParam, LPCTSTR  aDev_expected,  LPCTSTR  vDev_expected);
 __declspec(dllexport)  int  printAvDevs(void* pCapStuffParam);

 //
 __declspec(dllexport)  int  dumpAvDevs(void* pCapStuffParam);



 __declspec(dllexport)int getCurrentCameraName(HWND  hDlgTalk, TCHAR* name, int cntofName);
 __declspec(dllexport)  int  sm_getChosenCamera(TCHAR* webcam_sel, int cntof_webcam_sel);


 //
#ifdef  _INC_COMMCTRL
 //
 __declspec(  dllexport  )  HTREEITEM treeCtrl_FindItemData( void  *  m_TreeCtrl,  DWORD lParam, BOOL bDownDir, HTREEITEM hItem );

 //
  __declspec(  dllexport  )  HTREEITEM treeCtrl_FindChildItemData( void  *  pTreeCtrl,  DWORD lParam, BOOL bDownDir, HTREEITEM hItem );


 //
 __declspec(  dllexport  )  HTREEITEM treeCtrl_GetLastItem( void  *  m_TreeCtrl,  HTREEITEM hItem );

 __declspec(  dllexport  )  HTREEITEM treeCtrl_GetNextItem( void  *  m_TreeCtrl,  HTREEITEM hItem,  BOOL  bNoParentItem );
 __declspec(  dllexport  )  HTREEITEM treeCtrl_GetPrevItem( void  *  m_TreeCtrl,  HTREEITEM hItem,  BOOL  bNoParentItem );

 __declspec(  dllexport  )  int  treeCtrl_DelAllChildOfItem(void  *  pTreeCtrl,  HTREEITEM hItem);


#endif

//
#endif  //  }



