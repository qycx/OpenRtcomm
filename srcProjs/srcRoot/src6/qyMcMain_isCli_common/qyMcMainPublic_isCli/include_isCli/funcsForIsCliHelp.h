

#ifndef  __funcsForIsCliHelp_h__
#define  __funcsForIsCliHelp_h__	//  {


//  2014/04/18
#include	"qisWebRtcPublic.h"
//
#include	"qmShellPublic.h"
#include	"qisD3dDefs.h"
//
#include	"myDb.h"
//
#include	"subtitles.h"
#include	"dlgTalkPublic.h"

//
#include	"qmcStruct_defs.h"

#include	"makeDynaMenu.h"
#include "tmpGuiOpenFunc.h"

//
//
typedef  int  (  *PF_askToRefreshLayout_mgr  )(  HWND  hDlgTalk  );
typedef  BOOL  (  *PF_bMainWndAbove  )(  QY_MC  *  pQyMc,  HWND  hWnd  );
typedef  BOOL  (  *PF_bMessengerOnline  )(  QY_MC  *  pQyMc  );
//
//typedef  BOOL  (  *PF_bQisExportVWall  )(  void  *  pCQyVWall,  void  *  pQY_IMEXPORTINFO  );
//typedef  BOOL  (  *PF_bQisImportVWall  )(  void  *  pQY_IMEXPORTINFO,  void  *  pCQyVWall  );
//
typedef  BOOL  (  *PF_bQnmExportCurQuery  )(  QY_IMEXPORTINFO  *  pExportInfo  );
typedef  BOOL  (  *PF_bWebcamUsing  )(  void  *  pMC_VAR_isCli,  unsigned  int  uiCamCapType,  void  *  pMoniker_v,  LPCTSTR  camName,  int  *  piIndex_capBmp,  int  *  piIndex_sharedObj  );


typedef  BOOL  (  *PF_bRecorderUsing  )(  void  *  pMC_VAR_isCli,  void  *  pMoniker_a,  int  *  piIndex_capAudio,  int  *  piIndex_sharedObj  );
typedef  BOOL  (  *PF_bViewImTaskListFunc  )(   QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart,  BOOL  bHisTab  );
typedef  BOOL  (  *PF_bViewImObjListFunc  )(   QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
//typedef	 BOOL  (  *PF_bViewImGrpList  )(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
typedef  BOOL  (  *PF_bViewMessengerRegInfoList  )(  QY_MC  * pQyMc,  QY_OBJ_DB  *  pObjDb  );

//
//typedef  BOOL  (  *PF_canRemotePtzControl  )(  );
//
typedef  void  (  *PF_CAP_STUFF_free  )(  void  *  p  );
typedef  void  *  (  *PF_CAP_STUFF_new  )(  );

typedef  int   (  *  PF_getChosenDevice  )(  TCHAR  *  recorder_selected,  unsigned  int  uiCnt_recorder_selected,  TCHAR  *  webcam_selected,  unsigned  int  uiCnt_webcam_selected,
						void  *  pCapParam,  BOOL  bIncludeAudio,  int  *  piMenuId_selectedAudio,  int  *  piMenuId_selectedVideo  );

typedef  void  (  *PF_myChooseDevices  )(  void  *  p_gcap,void  *  pIMoniker_v, void  *  pIMoniker_a  );
typedef  void  (  *PF_chooseAvDevice_mgr  )(  void  *  pCapParam,  HWND  hDlgTalk,  HWND  hWndStatus,  int  iMenuId  );
typedef  int   (  *PF_cfgCaptureFilter  )(  void  *  pAvCapStuff,  HWND  hwndParent  );
typedef  int   (  *PF_cfgCapturePin  )(  void  *  pAvCapStuff,  HWND  hwndParent  );
typedef  int  (  *PF_cfgCrossBar  )(  void  *  pAvCapStuff,  HWND  hwndParent  );


//
typedef  int  (  *PF_delImObj  )(  void  *  pDb,  int  iDbType,  BOOL  bClient,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );

typedef  int  (  *PF_displayNotification_talk_ts  )(  HWND  hDlg,  void  *  pGuiDataParam,  LPCTSTR  hint  );
//typedef  int  (  *PF_dlgDynBmps_getZoneParam  )(  HWND  hDlgDynBmps,  MIS_MSG_procVideo_qmc  *  pMsg,  ZONE_PARAM  *  pParam  );
//
typedef   BOOL (  *PF_bDlgTalkAbove  )(  HWND hWnd  );
typedef  int  (  *PF_dlgTalk_cancelTasks  )(  HWND  hDlg,  void  *  pDLG_TALK_var,  int  iTaskId,  BOOL  bAutoCancel  );
typedef  int  (  *PF_dlgTalk_OnDestroy  )(  HWND  hDlg,  void  *  pDLG_TALK_var  );
typedef  int  (  *PF_dlgTalk_OnInitDialog  )(  HWND  hDlgTalk,  void  *  pDLG_TALK_var  );
typedef  int  (  *PF_dlgTalk_OnQyComm  )(  HWND  hDlg,  void  *  pDLG_TALK_var,  WPARAM  wParam,  LPARAM  lParam  );
typedef  int  (  *PF_dlgTalk_OnQyPostComm  )(  HWND  hDlg,  void  *  pDLG_TALK_var,  WPARAM  wParam,  LPARAM  lParam  );
typedef  int  (  *PF_dlgTalk_qPostMsg  )(  HWND  hDlgTalk,  Q_ELEM_T  *  pQElem,  unsigned  int  size  );
typedef  int  (  *PF_dlgTalk_requestToSpeak  )(  HWND  hDlgTalk,  BOOL  bEnable,  bool  bSaveState  );
typedef  int  (*PF_dlgTalk_requestToOp)(HWND  hDlgTalk, BOOL  bEnable, int op);
typedef  int  (  *PF_dlgTalk_procTask1  )(  HWND  hCurDlgTalk,  int  iTaskId,  unsigned  short  usOp,  LPCTSTR  paramStrBuf,  PARAM_dlgTalk_procTask  *  pParam  );
typedef  int  (  *PF_dlgTalk_procCmd  )(  HWND  hCurTalk,  int  nID,  int  iTaskId,  unsigned  short  usOp,  LPCTSTR  paramStrBuf,  PARAM_dlgTalk_procTask  *  pParam  );
//
typedef  int  (*PF_dlgTalk_closeTask)(HWND  hDlgTalk, int  iTaskId);



//
typedef  int  (  *PF_dlgTalk_re_acceptTask  )(  HWND  hDlgTalk_mgr,  int  iTaskId  );

//
typedef  BOOL  (  *PF_bNoPrompt_selectAvCompressor  )(  unsigned  int  uiCapType,  unsigned  int  uiSubCapType  );

//
//typedef  int  (  *PF_viewDlgSelectAvCompressor  )(  HWND  hParent,  HWND  hCurTalk,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage,  BOOL  b3D,  unsigned  short  usConfType  );



//  
//typedef  int  (  *PF_doCmd_startAvCall  )(  HWND  hParent,  HWND  hCurTalk,  int  level,  BOOL  b3D,  unsigned  char  ucbAvConsole,  PARAM_startAvCall  *  pParam  );


typedef  int  (  *PF_doCmd_startShareMediaDevice  )(  QY_MC  *  pQyMc,  HWND  hDlg,  void  *  pDLG_TALK_var,  unsigned  int  uiSubCapType,  int  level,  void  **  ppCapStuff  );
//
typedef  int  (  *PF_doCmd_startShareMediaFile  )(  QY_MC  *  pQyMc,  HWND  hDlg,  int  iWndContentType,  int  level,  LPCTSTR  pathCStr,  int  *  piIndex_sharedObj,  int  *  piIndex_sharedObjUsr  );


typedef  int  (  *PF_enumDmoIoTypes  )(  QY_MC  *  pQyMc,  const  GUID  *  clsid,  const  GUID  *  clsid_input,  QY_AUDIO_HEADER  *  pAh_input,  BOOL  *  pbInputSupported,  const  GUID  *  clsid_output,  QY_AUDIO_HEADER  *  pAh_output,  BOOL  *  pbOutputSupported,  HWND  hComboBox  );
typedef  int  (  *PF_enumDmos  )(  void  *  pDynLib_dx,  const  GUID  *  clsid_category,  HWND  hComboBox  );

typedef  int  (  *PF_exitShareMediaFile  )(  void  **  ppShareMediaFileParam  );

typedef  int  (  *PF_fillQyMcQuery  )(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  int  type,  void  *  pParam,  LPCTSTR  wherePart,  QY_MC_QUERY  *  pQuery  );
typedef  int  (  *PF_findQMemByKey  )(  void  *  p0,  void  *  pQParam,  void  *  pKeyInfo,  QM_OBJQ_MEM  *  pMemParam  );
typedef  int  (  *PF_findTalker  )(  void  *  pQyMcParam,  QY_MESSENGER_ID  *  pIdInfo,  HWND  *  phWnd  );
typedef  MIS_MSG_TASK  *  (  *PF_findTaskInProcessQ  )(  void  *  pDLG_TALK_var,  int  iTaskId,  BOOL  bNextAv,  BOOL  bToShareScreen  );

typedef  CUS_MODULE_U  *  (  *PF_getCusModule  )(  CUS_MODULES  *  pModules,  unsigned  int  uiModuleType,  unsigned  int  uiVDevId,  unsigned  int  uiDevType,  WCHAR  *  wDevIdStr  );

//  2015/12/05
typedef  void  *  (  *PF_getZoneObjs  )(  HWND  hDlgWalls,  int  iWndContentType,  int  iZoneObjsType  );
typedef  void  *  (  *PF_getZoneObjsInfo  )(  CCtxQmc  *  pProcInfo,  HWND  hDlgWalls,  int  iWndContentType,  int  iZoneObjsType  );

//
typedef	 int  (  *PF_getDmoInfoBySth  )(  QY_MC  *  pQyMc,  void  *  pDynLib_dx,  const  GUID  *  clsid_category,  LPCTSTR  dmoName,  const  GUID  *  clsid_input,  QY_AUDIO_HEADER  *  pAh_input,  const  GUID  *  clsid_output,  QY_AUDIO_HEADER  *  pAh_output,  GUID  *  pDmoClsid,  void  *  pCompressor  );

typedef  QY_OBJ_DB  *  (  *PF_getProcedObjDb  )(  QY_MC  *  pQyMc,  void  *  p0,  int  iDsnIndex  );
typedef  G_guiData_qyMc  *  (  *PF_get_g_guiData  )(  );

//
typedef MIS_CNT  *  (  *PF_getMisCntByName  )(  MC_VAR_common  *  pProcInfo,  LPCTSTR  misServName  );


//
typedef  void  (  *PF_addDevicesToMenu  )(  void  *  pCapParam,  BOOL  bIncludeAudio,  HWND  hWnd  );

typedef  void  *  (  *PF_getMoniker_a  )(  void  *  pCapParam,  int  iMenuId  );
typedef  void  *  (  *PF_getMoniker_v  )(  void  *  pCapParam,  int  iMenuId  );
typedef  int  (  *PF_getMonikerProp  )(  void  *  pMonikerParam,  LPCTSTR  propName,  TCHAR  *  propVal,  int  propValCnt  );
typedef  int  (  *PF_getMonikerDisplayName  )(  void  *  pMonikerParam,  TCHAR  *  displayName,  int  displayNameCnt  );
typedef  int  (  *PF_getMonikerByDisplayName  )(  LPCTSTR  displayName,  void  **  ppMoniker  );


typedef  int  (  *PF_getADevFriendlyName  )(  void  *  pCapParam,  BOOL  bIncludeAudio,  int  iMenuId,  TCHAR  *  name,  int  cnt  );
typedef  void  *  (  *PF_getADeviceGuid  )(  void  *  pCapParam,  int  iMenuId,  TCHAR  *  devDesc,  int  devDescCnt  );


typedef  int  (  *PF_getRect_talkers  )(  HWND  hDlgWalls,  RECT  *  pRc  );

typedef  int  (  *PF_getShareMediaFileState  )(  void  *  pShareMediaFileParam  );

typedef	 int  (  *PF_getTalkerDesc  )(  QY_MESSENGER_ID    idInfo,  TCHAR  *  talkerDesc,  unsigned  int  talkerDescCnt,  TCHAR  *  shortName,  unsigned  int  shortNameCnt  );


typedef  BOOL  (  *PF_bUseChromaKey  )(  );
typedef  int  (  *PF_addColorKey  )(  BYTE  r,  BYTE  g,  BYTE  b,  unsigned  int  tola100x,  unsigned  int  tolb100x,  BOOL  bForce,  void  *  pIMG_process_cfg  );

typedef  int  (  *PF_getColorDistance_keys  )(  int  h_p,  int  s_p,  void  *  pIMG_process_cfg,  unsigned  char  *  pucIndex_key,  float  *  pDistance  );

typedef  int  (  *PF_delColorKey  )(  int  index,  void  *  pIMG_process_cfg  );

typedef  int  (  *PF_getCurImgProcessCfg  )(  void  *  pIMG_process_cfg,  DWORD  *  pdwTickCnt_modifiedTime  );
 
typedef  int  (  *PF_refreshCurImgProcessCfg  )(  void  *  pIMG_process_cfg  );
typedef  int  (  *PF_procChromaKey  )(  void  *  pProcInfo,  void  *  pKEYING_ctx,  void  *  pIMG_process_cfg,  BITMAPINFOHEADER  *  pBih,  BYTE  *  pData_src,  BOOL  bFlipImg  );
typedef  int  (  *PF_test_procChromaKey  )(  void  *  pProcInfo,  void  *  pKEYING_ctx,  void  *  pIMG_process_cfg,  BITMAPINFOHEADER  *  pBih,  void  *  pKEYING_img_datas,  BOOL  bFlipImg  );



typedef  int  (  *PF_imObjRulesReq2ImRules  )(  REFRESH_imObjRules_req  *  pReq,  QY_im_rules  *  pRules  );
typedef  int  (  *PF_imObjRulesReq2Rules  )(  REFRESH_imObjRules_req  *  pReq,  QY_MESSENGER_ID  *  pIdInfo_related,  QY_imObj_rules  *  pRules  );

typedef  int  (  *PF_initShareMediaFile  )(  LPCTSTR  tFile,  HWND  hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppShareMediaFileParam  );

//  {  mainWnd
typedef  int  (  *PF_mainWnd_OnClose  )(  HWND  hMainWnd,  void  *  pVar  );
typedef  int (  *PF_mainWnd_OnQyPostComm  )(  HWND  hMainWnd,  void  *  pVar,  UINT  wParam,  LONG  lParam  );
typedef  int  (  *PF_mainWnd_OnQyQuitMainWnd  )(  HWND  hMainWnd,  void  *  pVar  );
//typedef  int  (  *PF_mainWnd_OnQyShowMainWnd  )(  HWND  hMainWnd  );
//
typedef  int  (  *PF_mainWnd_OnTimer  )(  HWND  hMainWnd,  void  *  pVar,  UINT  nIDEvent  );
typedef  int  (  *PF_initVar_onCreate_mainFrame  )(  void  *  p0,  HWND  hMainWnd,  void  *  pVarParam  );
typedef  int  (  *PF_exitVar_onDestroy_mainFrame  )(  void  *  p0,  HWND  hMainWnd,  void  *  pVarParam  );
typedef  int (  *PF_mainWnd_OnQyTrayNotify  )(  HWND  hMainWnd,  void  *  pVar,  WPARAM  wParam,  LPARAM  lParam  );
typedef  LRESULT (  *PF_mainWnd_OnQyGraphNotify_mediaDevice  )(  QY_MC  *  pQyMc,  HWND  hMainWnd,  void  *  pVar,  WPARAM  wParam,  LPARAM  lParam  );
typedef  int  (  *PF_handleGraphEvent_mediaFile  )(  void  *  pShareMediaFile,  BOOL  bMediaFile,  BOOL  bLooping,  BOOL  bPlayThrough  );
typedef  int  (  *PF_showDlgQnmCfgOptionsIsClient  )(  HINSTANCE  g_hInst,  HWND  hParent,  DLG_guiData_qnmCfgOptionsIsClient  *  pParam,  QY_MC  *  pQyMc  );
typedef  BOOL  (  *PF_bViewActiveImObjList  )(  );
//  }

typedef  int  (  *PF_netMc_procTreeEvent  )(  void  *  pQyMcParam,  void  *  pSel,  void  *  pEventInfoParam  );
typedef  int  (  *PF_netMc_procTreeSel  )(  void  *  pQyMcParam,  void  *  p0,  void  *  p1  );

typedef  IM_TASK_RCD  *  (  *PF_msg2TaskRcd  )(  void  *  pMisCntParam,  MIS_MSG_TASK  *  pMsg,  unsigned  short  usRespCode,  IM_TASK_RCD  *  pRcd  );

typedef  int  (  *PF_pauseShareMediaFile  )(  void  *  pShareMediaFileParam  );

//
typedef  int  (  *PF_d3dWall_refreshImgs  )(  HWND  hDlgTalk_mgr,  TCHAR  *  hint  );

//
typedef  int  (*PF_test_d3dWall_chkImgs)(HWND  hDlgTalk_mgr,  bool  bBreakIfNotSame);



//
typedef  int  (*PF_tryToChkD3dWall)(D3D_context* pCtx);

//
class  CWallTmpl;

//
typedef  int  (*PF_qisWall_exit)(CWallTmpl* pWall);

typedef  void  (*PF_CUBOID_tool_exit)(void* pCUBOID_tool_pFrm);


typedef  int  (*PF_resetForResize)(D3D_context* pCtx, int  index_d3dWnd);

typedef  void  (*PF_d3dWnd_OnMouseMove)(HWND  m_hWnd, int  iWndContentType, WPARAM  wParam, LPARAM  lParam);

typedef  void  (*PF_d3dWnd_OnMove)(HWND  m_hWnd, int  iWndContentType, WPARAM  wParam, LPARAM  lParam);
typedef  void  (*PF_d3dWnd_OnMoving)(HWND  m_hWnd, int  iWndContentType, WPARAM  wParam, LPARAM  lParam);

typedef  int  (*PF_D3D_devCtx_pool_exit)(D3D_devCtx_pool* pPool);
typedef  void* (*PF_get_D3D_devCtx_pool)();

//
typedef  void  (*PF_generalWall_OnIsCmd)(HWND  m_hWnd, UINT nID);

typedef  HRESULT  (*PF_InitD3D)(D3D_context * pCtx, HWND  hWnd, BOOL  bWindowed, long  lStyle_wnd);
typedef  int  (*PF_InitGraphics)(D3D_context * pCtx);
typedef  void  (*PF_Cleanup)(D3D_context* pCtx);

typedef  int  (*PF_InitGraphics11)(D3D_context* pCtx);

typedef  int   (*PF_renderNote_otherTalker)(Param_renderTxt  *  pParam,  float  x_start, float  y_start, BOOL  bFocus, D3D_addTxt_mem  *  pAddTxtMem);
typedef  int   (*PF_renderNote_otherTalker_func)(float  x_start, float  y_start, BOOL  bFocus, COLORREF  rgba_note, QIS_textureInfo* pTextureInfo);
//
typedef  int   (*PF_renderNoteFunc_importantNote)(QIS_textureInfo* pTextureInfo, RECT* pRc_src, RECT* pRc_dst);

//
typedef  int  (*PF_addWmEnlarge)(WM_ID* pWmId_owner, int  index_d3dWnd_dst, int  init_posX, int  init_posY, unsigned  int  init_w, unsigned  int  init_h, WM_ID* pWmId_o);

class CWallMem;
//
typedef  int  (*PF_d3dWall_av)(HWND  hWall_d3d, PARAM_wmCmd* pParam, CWallMem* pWmObj);
//
typedef  int  (*PF_talkerFrm_init)(void* pD3D_context, CWallMem* pWallMemObj, WALLMemFrm_talker* pTalkerFrm);
typedef  int  (*PF_talkerFrm_exit)(void* pD3D_context, CWallMem* pWallMemObj, WALLMemFrm_talker* pTalkerFrm);

typedef  int  (*PF_talkerFrm_mosaic_init)(void* pD3D_context, int index_mosaic, WALLMemData_talker* pTalkerData, WALLMemFrm_talker* pTalkerFrm);
typedef  int  (*PF_talkerFrm_mosaic_exit)(void* pD3D_context, int  index_mosaic, WALLMemFrm_talker* pTalkerFrm);

typedef  int   (*PF_renderImportantNote)(D3D_addTxt_mem* pD3dAddTxtMem, int  x_start, int  y_start, unsigned  int  uiW, unsigned  int  uiH);

typedef  int  (*PF_renderSubtitles)(CTX_d3dAddTxt* pCtx_d3dAddTxt, int  iX, int  iY, int  wnd_w, int  wnd_h);

typedef  int  (*PF_d3dWall_closeDlgTalk)(HWND  hWall_d3d, PARAM_wmCmd* pParam_wmCmd, HWND  hDlgTalk_mgr);

typedef  int  (*PF_d3dWall_enlargeWall)(int  wallMemIndex);

typedef  int  (*PF_hideAllCtrls_dxDialog)(void* pDxDlg);

typedef  int  (*PF_d3dWall_cleanMessageBox)();
typedef  int  (*PF_d3dWall_MessageBox)(int  idc, PARAM_wmCmd* pParam, LPCTSTR  tHint);

//
typedef  void  (*PF_g_DialogResourceManager_StoreD3D11State)(void* pcontext);
typedef  void (*PF_g_DialogResourceManager_ApplyRenderUI11)(void* pcontext);
typedef  void (*PF_g_DialogResourceManager_RestoreD3D11State)(void* pcontext);

typedef  int  (*PF_myRender_tool)(D3D_context * pCtx, float  fx, float  fy, float  fz);


//
typedef  void  (*PF_stopUsingD3d)();


//
typedef  int  (*PF_chkAndRecoverD3dImg_a)(D3D_context* pCtx, CAP_image* pCapImg, D3D_image* pD3dImg, LPCTSTR  hint);


//
typedef  int  (*PF_chkAndRecoverD3dImg)(D3D_context* pCtx, CAP_image* pCapImg, D3D_image* pD3dImg, LPCTSTR  hint);


//
typedef  void  (*PF_d3dWall_OnSize)(HWND  m_hWnd, WPARAM  wParam, LPARAM  lParam);


///////////////////



////////////////////////////////////////////

//  
//typedef  int  (  *PF_confStarter_requestToSpeak  )(  HWND  hDlgTalk,  QY_MESSENGER_ID  *  pIdInfo,  AV_stream_simple  *  pAss,  LPCTSTR  talkerDesc,  BOOL  bRequestToSpeak  );

// 2017/07/08
typedef  int  (  *PF_resumeLocalAudioRecorder  )(  QY_MC  *  pQyMc,  int  iIndex_sharedObj  );
//  2017/09/13
typedef  int  (  *PF_resumeLocalVideo  )(  MC_VAR_common  *  pProcInfoCommon,  int  iIndex_sharedObj  );


//
typedef  int  (  *PF_runShareMediaFile  )(  void  *  pShareMediaFileParam  );

//
typedef  int  (  *PF_saveChosenDevice  )(  void  *  pCapParam,  BOOL  bIncludeAudio,  int  iMenuId  );
typedef  int  (*PF_sendVideoConferenceLayout)(unsigned char ucbResp ,unsigned  short  usLayoutType, unsigned  short  usOp, ConfLayoutParam* pParam, QY_MESSENGER_ID  idInfo_imGrp_related, QY_MESSENGER_ID  idInfo_requester, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint);

//
typedef  int  (  *PF_sendVideoConferenceStatus  )(  HWND  hDlgTalk,  QY_MESSENGER_ID    idInfo_to,  LPCTSTR  hint  );
typedef  int  (  *PF_setCurSharedObjUsr_localAv  )(  void  *  pMC_VAR_isCli,  int  index_sharedObj,  int index_sharedObjUsr  );
typedef  int  (  *PF_resetCurSharedObjUsr_localAv  )(  void  *  pMC_VAR_isCli,  int  index_sharedObj  );
typedef   void  (  *PF_setEncodingDefaults_video  )(  unsigned  int  uiCapType,  float  fFps,  DWORD  fourcc,  VIDEO_ENC_PARAMS  *  pParams  );

//  typedef  int  (  *PF_setModalWnd  )(  HWND  hDlg  );
typedef  int  (  *PF_startProgress  )(  QY_PROGRESS  *  pProgress,  unsigned  int  uiTranNo  );
typedef  int  (  *PF_startToRefreshRecentFriends  )(  MIS_CNT  *  pMisCnt,  MIS_MSGU  *  pMsgBuf  );

typedef  void  (  *PF_stopAll_avRecord  )(  );
typedef  int  (  *PF_stopShareMediaFile  )(  void  *  pShareMediaFileParam  );
typedef  int  (  *PF_storeTaskInDb  )(  void  *  pDb,  int  iDbType,  MIS_CNT  *  pMisCnt,  int  iTaskId_suggested,  IM_TASK_RCD  *  pRcd,  BOOL  bInHis  );
//  typedef  int  (  *PF_toShareBmp  )(  void  *	pProcInfo,		unsigned  int  uiCapType,  int  iIndex_capProcInfo,  myDRAW_VIDEO_DATA  *  pPkts,  unsigned  int  nPkts,  COMPRESS_VIDEO  *  pCompressVideo,  QY_SHARED_OBJ  *  pSharedObj,  MIS_MSGU  *  pMsgBuf  );
typedef  int  (  *PF_toShareGps  )(  void  *  pMC_VAR_isCli,  void  *  pComPortEx,  int  iSampleTimeInMs,  void  *  pmyGPS_POSITION,  QY_SHARED_OBJ  *  pSharedObj,  BOOL  *  pbHaveMsgrs_sendLocalAv,  MIS_MSGU  *  pMsgBuf  );

typedef  int  (  *PF_talkerShadow_procGps  )(  void  *  pProcInfoParam,  HWND  hDlgTalk,  BOOL  bForceRefreshPos,  int  index_shadow,  HWND  hDlgDynBmps_param,  void  *  pDlgDynBmpsVar_param,  int  index_wallGpsMgrMem  );
typedef  void  (  *PF_TALKER_shadow_free  )(  BOOL  bMgr,  void  *  pShadowInfo  );
typedef  int  (  *PF_talkToMessenger  )(  unsigned  __int64  ui64Id,  int  iTalkUsage,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phWnd  );
typedef  int  (  *PF_testLocalAv  )(  HWND  hParent  );
typedef  int  (  *PF_tmpHandler_showMsg  )(  void  *  hDlgTalkParam,  void  *  p1, void  *  pMsgParam  );
//typedef  int  (  *PF_toSelectRegion  )(  HWND  hWndStarter,  BOOL  bCapFullScreen,  BOOL  bRemoteAssist,  BOOL  bDirectX,  int  iParam  );
typedef  int  (  *PF_toSelectRegion1  )(  HWND  hWndStarter,  BOOL  bCapFullScreen,  BOOL  bRemoteAssist,  BOOL  bDirectX,  int  level,  int  iParam  );

//
typedef  int  (  *PF_tryToTalkToMessenger  )(HWND hParent,  void  *  pMSGR_ADDR,  int  iTalkUsage,  int iTalkSubtype, BOOL  bActivateWnd,  HWND  hVWall,  int  iWndContentType_hVWall,  HWND	*	phWnd  );
typedef  int  (  *PF_tryToTalkToMessenger_id  )(HWND hParent,  unsigned  __int64  ui64Id,  int  iTalkSubtype,  BOOL  bActivateWnd,  HWND  hVWall,  int  iWndContentType_hVWall,  HWND	*	phWnd  );

//
typedef  int  (  *PF_tryToTalkToMessenger_any  )(HWND hParent, unsigned  __int64  ui64Id,  int  iTalkSubtype,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phWnd  );
typedef  int  (  *PF_tryToTalkToMessenger_d3dWall  )(  QY_MESSENGER_ID  *  pIdInfo,  int  iTalkUsage,  BOOL  bNeedExist_hWnd,  HWND  *  phWnd_mgr  );



//
//typedef  int  (  *PF_doSth_afterInitDlgTalk  )(  HWND  hDlgTalk,  int  iWndContentType  );
typedef  int  (  *PF_doSth_afterInitDlgMsgTool  )(  QY_MC  *  pQyMc,  HWND  hDlg,  int  iWndContentType  );


//
typedef  int  (  *PF_updateMeDisplayInfo  )(  void  *  pMC_VAR_isCli,  MIS_CNT  *  pMisCnt,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  talkerDesc,  LPCTSTR  displayName  );

//typedef  int  (  *PF_viewInstantAssistant  )(  HWND  hWndEvent,  int  iWndContentType,  int  xPos_screen,  int  yPos_screen,  HWND  hDlgTalk,  BOOL  bNoDelayToView  );
typedef  int  (  *PF_viewWallsBar_ts  )(  HWND  hWndEvent,  int  iWndContentType,  int  xPos_screen,  int  yPos_screen,  HWND  hDlgWalls,  int  iWndContentType_hDlgWalls,  BOOL  bNoDelayToView  );
//  2015/06/03
typedef  int  (  *PF_viewWallsBar_3d  )(  HWND  hWndEvent,  int  iWndContentType,  int  xPos_screen,  int  yPos_screen,  HWND  hDlgWalls,  void  *  pDLG_wall_var,  BOOL  bNoDelayToView  );
//
typedef  int  (  *PF_setWallsBarPos  )(  HWND  hDlgWalls,  void  *  pDLG_wall_var,  HWND  hBar,  int  iBarType  );



//
typedef  BOOL  (  *PF_bFullScreen_wnd  )(  HWND  hWnd,  int  iWndContentType  );

//
typedef void * (  *PF_vw_getCurSp  )(  void  *  pCQyVWall  );

typedef  int  (  *PF_testLocalAv_openLocalVideo  )(  HWND  hWnd_testWebcam,  void  *  pADeviceGuid,  LPCTSTR  capDevDesc,  void  *  pMoniker,  BOOL  *  pbGot_sharedObjIndex_localAv,  int  *  piIndex_sharedObj  );
typedef  int  (  *PF_doCmd_test  )(  int  iMenuId  );

typedef  int  (  *PF_stopLocalAudioPlaying  )(  MC_VAR_common  *  pProcInfoCommon  );
typedef  int  (  *PF_freeSharedObjUsr_localAv  )(  void  *  pMC_VAR_isCli,  int  index,  HWND  hWnd  );
typedef  int  (*PF_tryToFreeSharedObjs)(  void  *  pProcInfo  );

//
typedef  int  (  *PF_dlgShareDynBmps_refreshShareStatus  )(  QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType  );
//
typedef  int  (  *PF_dlgShareDynBmps_refreshShareStatus_gps  )(  QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  );
typedef  LRESULT  (  *PF_dlgShareDynBmps_OnQyComm  )( QY_MC  *  pQyMc, HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  WPARAM wParam, LPARAM lParam );
typedef  LRESULT  (  *PF_dlgShareDynBmps_OnQyPostComm  )( QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  WPARAM wParam, LPARAM lParam );
typedef  int  (  *PF_dlgShareDynBmps_chkTask  )(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  iTaskId  );
//
typedef  int  (  *PF_toShareDynBmp  )(  CCtxQmc  *  pProcInfo,  HWND  m_hWnd,  void  **  ppCapStuff,  int  iTaskId_suggested,  AV_COMPRESSOR_CFG  *  pCompressor_suggested,  int  iFourcc_suggested,  TASK_av_props  *  pTaskAvProps,  SHARE_dyn_bmp  *  pDynBmpMem  );
typedef  int  (  *PF_dlgShareDynBmps_toShareDynBmp  )(  QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  int  index_pShare_mem,  void  **  ppCapStuff,  AV_COMPRESSOR_CFG  *  pCompressor_suggested,  TASK_av_props  *  pTaskAvProps  );


//
typedef  int  (  *PF_dlgShareDynBmps_toShareGps  )( QY_MC  *  pQyMc, HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var);
typedef  int  (  *PF_dlgShareDynBmps_closeTaskAv  )(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  int  index_pShare_mem  );
typedef  int  (  *PF_dlgShareDynBmps_chkShareGps  )(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  );
//
typedef  int  (  *PF_dlgShareDynBmps_sndDynBmpsInfo  )(   HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  );
//
typedef  int  (  *PF_dlgShareDynBmps_testRtspUrl  )(  QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  short  usIndex_obj,  unsigned  short  usHelp_subIndex  );

//
typedef  int  (  *PF_dlgShareDynBmps_internalProcess  )( QY_MC  *  pQyMc, HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  );


//
typedef  DWORD(*PF_doPre_toPlayVideo)(LPVOID pPlayerParam, bool bEnable_resize);




//
			typedef void  *  (  *PF_getZoneObjsInfo_d3dWall  )(  HWND  hDlgWalls,  int  iWndContentType,  int  iZoneObjsType  );
			
			typedef  int   (  *PF_set_g_pQyMc_isCliD3d  )(  void  *  pQyMc  );

			typedef  int  (  *PF_dllInit_d3d_isCli  )(  );
			typedef  int  (  *PF_dllExit_d3d_isCli  )(  );
			typedef  void  *  (  *PF_GBuf_d3d_isCli_new  )(  );
			typedef  void  (  *PF_GBuf_d3d_isCli_free  )(  void  **  ppGBuf_d3d_isCli  );

			//  2014/11/03
			typedef  unsigned  int  (  *PF_getMaxCnt_wallMems  )(  int  iGrpType  );
			typedef  void  *  (  *PF_getWallMemByIndex  )(  void  *  pD3D_context,  int  iGrpType,  int  index  );
			//typedef  void  *  (  *PF_getD3dTalkerData  )(  void  *  pWallMemParam  );
			

			//  2014/11/05			
			//
			typedef  BOOL  (  *PF_bD3dUsing  )(  BOOL  *  pm_bActive  );
			typedef  BOOL  (  *PF_bFullScreen_d3dWnd  )(  HWND  hD3dWnd  );

			//
			typedef  int  (  *PF_createConsoleWall  )(  void  *  pGBuf_d3d  );
			typedef  int  (  *PF_closeConsoleWall  )(  void  *  pGBuf_d3d  );

			//  2016/06/05
			typedef  int (  *PF_createGeneralWall  )(HINSTANCE hInstance, LPCTSTR  szTitle, HICON  hIcon,  HMENU  hMenu,  int  x,  int  y);

			//
			typedef  int  (*PF_myPreRender)(D3D_context* pCtx);
			typedef  void  (  *PF_myRender  )();

			//  2015/10/06
			typedef  int  (  *PF_getTex2Props  )(  void  *  p0,  int  iIndex_player,  void  *  pTEX2_props  );


			//
			typedef  int  (  *PF_fillData_d3d  )(  Ctx_fillData_d3d  *  pCtx,  myDRAW_VIDEO_DATA  *  pPkt,  int  iIndex_player,  PARAM_fillD3d  *  pParam,  BOOL  *  pbFilled  );
			typedef  int  (  *PF_fillData_d3d_setDataReady  )(  myDRAW_VIDEO_DATA  *  pPkt,  int  iIndex_player  );

			//
			typedef  DWORD (  *PF_doProc_readRtt  )( LPVOID lpParameter );


			//
			typedef  void  *  (  *PF_qisWallsCfgNew  )(  unsigned  short  usMaxCnt  );
			typedef  void  (  *PF_qisWallsCfgFree  )(  void  **  ppQIS_walls_cfg  );

			//
			typedef  int  (  *PF_addQisWallCfg  )(  void  *  pQIS_walls_cfg,  unsigned  int  uiType,  LPCTSTR  fileName,  int  *  piIndex  );
			typedef  int  (  *PF_setCurQisWallCfg  )(  int  curIndex,  void  *  pQIS_walls_cfg  );


			//  2014/10/31
			typedef  int  (  *PF_removeMosaicFromD3dWall  )(  int  iIndex_sharedObj  );
			typedef  int  (  *PF_getVal_bExists_mosaic  )(  int  iIndex_sharedObj,  BOOL  *  pbExists  );


			typedef  BOOL  (  *PF_bDisplayMcViewContent_d3dWall  )(  HWND  hListCtrl,  int  *piCnt  );


			//  2015/06/06
			typedef  int  (  *PF_d3dWall_doLayout  )(  HWND  hD3dWall  );


			//  2013/12/23
			
			//  2015/11/15
			typedef  int  (  *PF_d3dWall_refreshAllWallMems  )(  );
			//  2015/12/13
			typedef  int  (  *PF_d3dWall_refreshWallMemByTalker  )(  HWND  hDlgTalk  );


			//
			typedef  int  (  *PF_addTalkerShadow  )(  HWND  hWall,  int  iWndContentType_wall,  WM_ID  *  pWdId,  HWND  hShadow,  HWND  hDlgTalk_mgr  );
			typedef  int  (  *PF_removeTalkerShadow  )(  HWND  hWall,  int  iWndContentType_wall,  HWND  hShadow,  HWND  hDlgTalk_mgr  );
			//
			typedef  int  (  *PF_d3dWall_askToRefreshBg  )(  );
			typedef  int  (  *PF_d3dWall_askToRefreshMenu  )(  );
			typedef  int  (  *PF_d3dWall_askToRefreshIa  )(  );

			//
			typedef  int  (  *PF_getVal_bWmTalkerShadowExists  )(  WM_ID  *  pWmId_talker,  BOOL  *  pbExists  );
 
			//
			typedef int (*PF_initAecObj)(int sampleRate, void** ppObj);
			typedef int (*PF_exitAecObj)(void** ppObj);
			typedef int (*PF_aecObj_doAec)(void* pObjParam, char* render_data, unsigned int render_dataLen, char* mic_data, unsigned int mic_dataLen);

			//
			typedef int (*PF_initAudioMixerObj  )(int sampleRate, int nSources,	PF_inStream4 pf, void* p0,	void** ppObj);
			typedef int (*PF_exitAudioMixerObj)(void** ppObj);
			typedef int (*PF_audioMixerObj_doMix)(void* pObjParam,	char* dataBuf,	unsigned int* puiSize);

			//
			typedef  int (*PF_help_webrtc_init)(int iCntLimit_activeMems_from,
				PF_inStream4 pf_is,
				void* is_p0,
				PF_outStream pf_os,
				void* os_p0,
				void** ppObj);

			typedef  void (*PF_help_webrtc_exit)(void** ppObj);



			//
			typedef  int  (  *PF_myOnAppAbout  )(  HWND  hParent  );
			typedef  BOOL  (  *PF_dlgTalk_canSpeak  )(  HWND  hDlgTalk_mgr  );

			//
			typedef  int  (  *PF_myListCtrl_InsertItem  )(  HWND  hListCtrl,  int nItem, LPCTSTR lpszItem  );
			typedef  BOOL (  *PF_myListCtrl_SetItemText  )(  HWND  hListCtrl,  int nItem, int nSubItem, LPCTSTR lpszText);

			typedef  int  (  *PF_showDlgPolicyAv  )(  HWND  hParent,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  iCapUsage  );
			typedef  int  (  *PF_showDlgPolicyIsClient  )(  HWND  hParent  );
			typedef  int  (  *PF_showDlgMsgList  )(  HWND  hParent,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );
			typedef  int  (  *PF_showDlgObjs  )(  HINSTANCE  g_hInst,  HWND  hParent,  void  *  pDLG_guiDataParam_objs  );
			//
			//
			typedef  int  (  *PF_d3dWall_setBg  )(  HWND  hWall_d3d  );

			//
			typedef  int  (  *PF_d3dWall_openQvw  )(  HWND  hWall_d3d  );


			//
			typedef  int  (  *PF_dlgTalk_getTaskInfo  )(  void  *  pProcInfo,  HWND  hTalkerMgr,  void  *  pTALKER_task_info  );

			//
			typedef  int  (  *PF_dlgTalk_getTaskList  )(  void  *  pProcInfoParam,  HWND  hTalkerMgr,  void  *  pTALKER_task_list,  BOOL  *  pbModified  );


			//  2015/06/05
			typedef  int  (  *PF_showMenu_wallsBar  )(  HINSTANCE  hInst,  HWND  hParent,  int  iWndContentType_hParent,  void  *  p2  );

			//
			typedef  int  (  *PF_showMenu_d3dWall  )(  HINSTANCE  hInst,  HWND  hParent,  int  iWndContentType_hParent,  void  *  p2  );
			typedef  int  (  *PF_showMenu_generalWall  )(  HINSTANCE  hInst,  HWND  hParent,  int  iWndContentType_hParent,  void  *  p2  );

			typedef  BOOL  (  *PF_bTaskExists_recvResource  )(  void  *  pDLG_TALK_var,  int  *  pnScreens,  int  *  pnMediaFiles,  int  *  pnMediaFiles_unresizable,  int  *  piW_unresizable,  int  *  piH_unresizable,  int  *  piTaskId_recvdResource  );
			typedef  BOOL  (  *PF_bTaskExists_sendingResource  )(  void  *  pDLG_TALK_var,  int  *  pnScreens,  int  *  pnMediaFiles,  int  *  pnMediaFiles_unresizable,  int  *  piW_unresizable,  int  *  piH_unresizable,  int  *  piTaskId_sendingResource  );


			//  2014/12/16
			typedef  int  (  *PF_dlgTalk_getCurSubtitlesCfg  )(  HWND  hDlgTalk,  SUBTITLES_cfg  *  pCfg  );
			typedef  int  (  *PF_dlgTalk_getSubtitleMsgs  )(  HWND  hDlgTalk,  SUBTITLE_msgs  *  pMsgs  );

			//
			typedef  BOOL  (  *PF_d3dWall_isUserActive  )(  int  *  piElapseInMs_userActive  );

			//
			typedef  int  (  *PF_getSubtitlesCfg  )(  int  iCapType,  int  iCapSubType,  int  iUsage,  SUBTITLES_cfg  *  pSubtitlesCfg  );

			typedef  int  (  *PF_subtitlesCfg_modify  )(  SUBTITLES_cfg  *  pCfg,  DWORD  dwTickCnt,  BOOL  bForce,  SUBTITLES_cfg  *  pCur,  BOOL  *  pbModified  );
			typedef  int  (  *PF_getSubtitlesCfg_d3dWall  )(  int  iCapType,  int  iCapSubType,  int  iUsage,  SUBTITLES_cfg  *  pSubtitlesCfg  );
   
			//
			typedef  int  (  *PF_viewVWall  )(  HWND  hParent,  LPCTSTR  misServName,  int  iSubType,  BOOL  bNewVirtualWall,  LPCTSTR  init_qvwFile,  BOOL  bNeedNotShowWnd,  HWND  *  phWnd  );

			//  2015/11/21
			typedef  int  (  *PF_viewGlobalVWall  )(  HWND  hParent,  LPCTSTR  misServName,  LPCTSTR  init_qvwFile,  BOOL  bNeedNotShowWnd  );

			//  2015/12/12
			typedef  int  (  *PF_addToWalls  )(  HWND  hDlgTalk,  HWND  hDlgWalls,  int  iWndContentType,  int  *  piIndex_wall  );

			//  2016/03/23
			typedef  int  (  *PF_viewDlgMsgInput_talk  )(  HWND  hParent,  HWND  hCurTalk,  HWND  *  phWnd_msgInput  );
			//
			typedef  BOOL  (  *PF_setMsgInputPos  )(  HWND  hWnd_msgInput,  int  iX_screen,  int  iY_screen,  int  iW,  int  iH  );


			//
			typedef  BOOL  (  *PF_bDlgTalkWaitToAccept  )(  HWND  hDlgTalk  );


			//
			typedef  int  (  *PF_doSaveAv  )(  SAVE_av_procInfo  *  pSave,  void  *  pSAVE_av_pktU,  BOOL  *  pbExists_pSvp,  void  *  pCTX_mc_saveAv  );

			//
			typedef  int  (  *PF_refreshDlgTalkSubtitleMsgs_d3dWall  )(  HWND  hMgr  );
			typedef  int  (  *PF_refreshDlgTalkSubtitlesCfg_d3dWall  )(  HWND  hMgr  );


//
typedef  int  (  *PF_toEditRtspUrlForConf  )(  TCHAR  *  url,  unsigned  int  cnt  );




//
struct  __funcs_for_isCliHelp_t	{

			//
			PF_askToRefreshLayout_mgr			pf_askToRefreshLayout_mgr;
			PF_bFullScreen_wnd					pf_bFullScreen_wnd;
			PF_bMainWndAbove					pf_bMainWndAbove;
			PF_bMessengerOnline					pf_bMessengerOnline;

			//
			//PF_bQisExportVWall					pf_bQisExportVWall;
			//PF_bQisImportVWall					pf_bQisImportVWall;

			//
			PF_bQnmExportCurQuery				pf_bQnmExportCurQuery;
			PF_bWebcamUsing						pf_bWebcamUsing;
			PF_bRecorderUsing					pf_bRecorderUsing;

			PF_bViewImTaskListFunc				pf_bViewImTaskListFunc;
			PF_bViewImObjListFunc				pf_bViewImObjListFunc;
			PF_bViewMessengerRegInfoList		pf_bViewMessengerRegInfoList;
			PF_bViewImGrpList					pf_bViewImGrpList;
			PF_bViewImGrpMemList_isClient		pf_bViewImGrpMemList_isClient;			//  2014/04/18
			PF_bViewImObjRuleList_is			pf_bViewImObjRuleList_is;				//  2014/04/18

			//
			PF_CAP_STUFF_free					pf_CAP_STUFF_free;
			PF_CAP_STUFF_new					pf_CAP_STUFF_new;
			PF_getChosenDevice					pf_getChosenDevice;
			PF_myChooseDevices					pf_myChooseDevices;
			PF_chooseAvDevice_mgr				pf_chooseAvDevice_mgr;
			PF_cfgCaptureFilter					pf_cfgCaptureFilter;
			PF_cfgCapturePin					pf_cfgCapturePin;
			PF_cfgCrossBar						pf_cfgCrossBar;


			//
			PF_delImObj														pf_delImObj;
			PF_displayNotification_talk_ts									pf_displayNotification_talk_ts;
			//PF_dlgDynBmps_getZoneParam										pf_dlgDynBmps_getZoneParam;
			//
			PF_bDlgTalkAbove												pf_bDlgTalkAbove;
			PF_dlgTalk_cancelTasks											pf_dlgTalk_cancelTasks;
			PF_dlgTalk_OnDestroy											pf_dlgTalk_OnDestroy;
			//
			PF_dlgTalk_OnInitDialog											pf_dlgTalk_OnInitDialog;
			PF_dlgTalk_OnQyComm												pf_dlgTalk_OnQyComm;
			PF_dlgTalk_OnQyPostComm											pf_dlgTalk_OnQyPostComm;
			PF_dlgTalk_qPostMsg												pf_dlgTalk_qPostMsg;
			PF_dlgTalk_requestToSpeak										pf_dlgTalk_requestToSpeak;
			PF_dlgTalk_requestToOp  							    		pf_dlgTalk_requestToOp;
			//
			//
			PF_dlgTalk_procTask1											pf_dlgTalk_procTask1;
			PF_dlgTalk_procCmd												pf_dlgTalk_procCmd;
			PF_dlgTalk_closeTask											pf_dlgTalk_closeTask;

			//
			//PF_doCmd_startAvCall											pf_doCmd_startAvCall;
			PF_stopAll_avRecord												pf_stopAll_avRecord;
			PF_doCmd_startShareMediaDevice									pf_doCmd_startShareMediaDevice;
			PF_doCmd_startShareMediaFile									pf_doCmd_startShareMediaFile;

			PF_enumDmoIoTypes					pf_enumDmoIoTypes;
			PF_enumDmos							pf_enumDmos;

			PF_exitShareMediaFile				pf_exitShareMediaFile;

			PF_fillQyMcQuery					pf_fillQyMcQuery;
			PF_findQMemByKey					pf_findQMemByKey;
			PF_findTalker						pf_findTalker;
			PF_findTaskInProcessQ				pf_findTaskInProcessQ;

			PF_getCusModule						pf_getCusModule;

			//
			PF_getZoneObjs						pf_getZoneObjs;				//  2015/12/05
			PF_getZoneObjsInfo					pf_getZoneObjsInfo;

			//
			PF_getDmoInfoBySth					pf_getDmoInfoBySth;

			PF_get_g_guiData					pf_get_g_guiData;
			PF_getMenuStatus					pf_getMenuStatus;
			PF_getMisCntByName					pf_getMisCntByName;
			struct								{
				PF_addDevicesToMenu				pf_addDevicesToMenu;

				PF_getMoniker_a					pf_getMoniker_a;
				PF_getMoniker_v					pf_getMoniker_v;
				//
				PF_getMonikerProp				pf_getMonikerProp;
				PF_getMonikerDisplayName		pf_getMonikerDisplayName;
				PF_getMonikerByDisplayName		pf_getMonikerByDisplayName;

				PF_getADevFriendlyName			pf_getADevFriendlyName;
				PF_getADeviceGuid				pf_getADeviceGuid;
			}									moniker;

			PF_getProcedObjDb					pf_getProcedObjDb;

			PF_getRect_talkers					pf_getRect_talkers;

			PF_getShareMediaFileState			pf_getShareMediaFileState;

			PF_getTalkerDesc					pf_getTalkerDesc;

			//  2014/04/19
			PF_BufferCB_av						pf_BufferCB_av;

			//
			struct								{
				PF_toShareGps					pf_toShareGps;
			}									gps;

			struct								{
				PF_bUseChromaKey				pf_bUseChromaKey;
				PF_addColorKey					pf_addColorKey;
				PF_getColorDistance_keys		pf_getColorDistance_keys;
				PF_delColorKey					pf_delColorKey;
				PF_getCurImgProcessCfg			pf_getCurImgProcessCfg;
				PF_refreshCurImgProcessCfg		pf_refreshCurImgProcessCfg;
				PF_procChromaKey				pf_procChromaKey;
				PF_test_procChromaKey			pf_test_procChromaKey;
			}									imgProcess;

			PF_imObjRulesReq2ImRules			pf_imObjRulesReq2ImRules;
			PF_imObjRulesReq2Rules				pf_imObjRulesReq2Rules;

			PF_initShareMediaFile				pf_initShareMediaFile;

			struct								{								//  2013/07/29
				PF_initVar_onCreate_mainFrame	pf_initVar_onCreate_mainFrame;
				PF_exitVar_onDestroy_mainFrame	pf_exitVar_onDestroy_mainFrame;
				PF_mainWnd_OnClose				pf_mainWnd_OnClose;
				PF_mainWnd_OnQyPostComm			pf_mainWnd_OnQyPostComm;
				PF_mainWnd_OnQyQuitMainWnd		pf_mainWnd_OnQyQuitMainWnd;
				//
				//PF_mainWnd_OnQyShowMainWnd		pf_mainWnd_OnQyShowMainWnd;
				//
				PF_mainWnd_OnTimer				pf_mainWnd_OnTimer;
				//
				PF_mainWnd_OnQyTrayNotify		pf_mainWnd_OnQyTrayNotify;
				PF_mainWnd_OnQyGraphNotify_mediaDevice	pf_mainWnd_OnQyGraphNotify_mediaDevice;
				PF_handleGraphEvent_mediaFile	pf_handleGraphEvent_mediaFile;
				PF_showDlgQnmCfgOptionsIsClient pf_showDlgQnmCfgOptionsIsClient;
				PF_bViewActiveImObjList			pf_bViewActiveImObjList;
			}									mainWnd;

			PF_netMc_procTreeEvent				pf_netMc_procTreeEvent;
			PF_netMc_procTreeSel				pf_netMc_procTreeSel;

			PF_msg2TaskRcd						pf_msg2TaskRcd;

			PF_pauseShareMediaFile				pf_pauseShareMediaFile;
			//

			//  
			//PF_confStarter_requestToSpeak		pf_confStarter_requestToSpeak;

			//  2017/07/08
			PF_resumeLocalAudioRecorder			pf_resumeLocalAudioRecorder;

			//  2017/09/13
			PF_resumeLocalVideo					pf_resumeLocalVideo;

			//
			PF_runShareMediaFile				pf_runShareMediaFile;

			PF_saveChosenDevice					pf_saveChosenDevice;
			PF_sendVideoConferenceLayout		pf_sendVideoConferenceLayout;
			PF_sendVideoConferenceStatus		pf_sendVideoConferenceStatus;
			PF_setCurSharedObjUsr_localAv		pf_setCurSharedObjUsr_localAv;
			PF_resetCurSharedObjUsr_localAv		pf_resetCurSharedObjUsr_localAv;
			PF_setEncodingDefaults_video		pf_setEncodingDefaults_video;

			//  PF_setModalWnd						pf_setModalWnd;

			PF_startProgress					pf_startProgress;
			PF_startToRefreshRecentFriends		pf_startToRefreshRecentFriends;

			PF_stopShareMediaFile				pf_stopShareMediaFile;
			PF_storeTaskInDb					pf_storeTaskInDb;
			//PF_toShareBmp						pf_toShareBmp;

			PF_talkerShadow_procGps				pf_talkerShadow_procGps;
			PF_TALKER_shadow_free				pf_TALKER_shadow_free;
			PF_talkToMessenger					pf_talkToMessenger;
			PF_testLocalAv						pf_testLocalAv;
			PF_tmpHandler_showMsg				pf_tmpHandler_showMsg;
			//
			//PF_toSelectRegion					pf_toSelectRegion;
			PF_toSelectRegion1					pf_toSelectRegion1;

			//
			PF_tryToTalkToMessenger				pf_tryToTalkToMessenger;
			PF_tryToTalkToMessenger_id			pf_tryToTalkToMessenger_id;
			PF_tryToTalkToMessenger_any			pf_tryToTalkToMessenger_any;
			//PF_tryToTalkToMessenger_d3dWall		pf_tryToTalkToMessenger_d3dWall;

			//
			//PF_doSth_afterInitDlgTalk			pf_doSth_afterInitDlgTalk;
			PF_doSth_afterInitDlgMsgTool		pf_doSth_afterInitDlgMsgTool;

			//
			PF_updateMeDisplayInfo				pf_updateMeDisplayInfo;
			//
			//PF_viewInstantAssistant				pf_viewInstantAssistant;
			//
			PF_viewWallsBar_ts					pf_viewWallsBar_ts;
			//  2015/06/03
			PF_viewWallsBar_3d					pf_viewWallsBar_3d;
			//  2015/06/03
			PF_setWallsBarPos					pf_setWallsBarPos;
			//
			PF_vw_getCurSp						pf_vw_getCurSp;

			//
			PF_testLocalAv_openLocalVideo		pf_testLocalAv_openLocalVideo;
			PF_doCmd_test						pf_doCmd_test;

			//
			PF_stopLocalAudioPlaying			pf_stopLocalAudioPlaying;
			PF_freeSharedObjUsr_localAv			pf_freeSharedObjUsr_localAv;

			PF_tryToFreeSharedObjs				pf_tryToFreeSharedObjs;

			//
			struct											{
				PF_dlgShareDynBmps_refreshShareStatus		pf_dlgShareDynBmps_refreshShareStatus;
				//PF_dlgShareDynBmps_getShareDynBmpsBySth		pf_dlgShareDynBmps_getShareDynBmpsBySth;
				PF_dlgShareDynBmps_refreshShareStatus_gps	pf_dlgShareDynBmps_refreshShareStatus_gps;
				PF_dlgShareDynBmps_OnQyComm					pf_dlgShareDynBmps_OnQyComm;
				PF_dlgShareDynBmps_OnQyPostComm				pf_dlgShareDynBmps_OnQyPostComm;
				PF_dlgShareDynBmps_chkTask					pf_dlgShareDynBmps_chkTask;
				//
				PF_toShareDynBmp							pf_toShareDynBmp;
				PF_dlgShareDynBmps_toShareDynBmp			pf_dlgShareDynBmps_toShareDynBmp;
				//
				PF_dlgShareDynBmps_toShareGps				pf_dlgShareDynBmps_toShareGps;
				PF_dlgShareDynBmps_closeTaskAv				pf_dlgShareDynBmps_closeTaskAv;
				PF_dlgShareDynBmps_chkShareGps				pf_dlgShareDynBmps_chkShareGps;
				//
				PF_dlgShareDynBmps_sndDynBmpsInfo			pf_dlgShareDynBmps_sndDynBmpsInfo;
				//
				PF_dlgShareDynBmps_testRtspUrl				pf_dlgShareDynBmps_testRtspUrl;
				//
				PF_dlgShareDynBmps_internalProcess			pf_dlgShareDynBmps_internalProcess;		//  2014/09/11
				//

			}												shareDynBmps;


			//
			struct													{
				HINSTANCE											hDll;
				BOOL												bOk;
				//
				PF_getZoneObjsInfo_d3dWall							pf_getZoneObjsInfo_d3dWall;
				PF_set_g_pQyMc_isCliD3d								pf_set_g_pQyMc_isCliD3d;
				//
				PF_dllInit_d3d_isCli								pf_dllInit_d3d_isCli;
				PF_dllExit_d3d_isCli								pf_dllExit_d3d_isCli;
				//
				PF_GBuf_d3d_isCli_new								pf_GBuf_d3d_isCli_new;
				PF_GBuf_d3d_isCli_free								pf_GBuf_d3d_isCli_free;
				//
				PF_getMaxCnt_wallMems								pf_getMaxCnt_wallMems;
				PF_getWallMemByIndex								pf_getWallMemByIndex;
				//PF_getD3dTalkerData								pf_getD3dTalkerData;

				//  2015/11/26
				//
				PF_bD3dUsing										pf_bD3dUsing;
				PF_bFullScreen_d3dWnd								pf_bFullScreen_d3dWnd;
				//
				PF_createConsoleWall								pf_createConsoleWall;
				PF_closeConsoleWall									pf_closeConsoleWall;
				//
				PF_createGeneralWall								pf_createGeneralWall;
				//  2015/06/05
				//
				PF_myPreRender										pf_myPreRender;
				PF_myRender											pf_myRender;
				//  2015/10/06
				PF_getTex2Props										pf_getTex2Props;
				//
				PF_fillData_d3d										pf_fillData_d3d;
				PF_fillData_d3d_setDataReady						pf_fillData_d3d_setDataReady;

				//  2014/11/06
				PF_doProc_readRtt									pf_doProc_readRtt;

				//
				PF_qisWallsCfgNew									pf_qisWallsCfgNew;
				PF_qisWallsCfgFree									pf_qisWallsCfgFree;
				//
				PF_addQisWallCfg									pf_addQisWallCfg;
				PF_setCurQisWallCfg									pf_setCurQisWallCfg;


				//  2014/10/31
				PF_removeMosaicFromD3dWall							pf_removeMosaicFromD3dWall;				
				PF_getVal_bExists_mosaic							pf_getVal_bExists_mosaic;

				//  2014/11/05
				PF_bDisplayMcViewContent_d3dWall					PF_bDisplayMcViewContent_d3dWall;

				//  2015/06/06
				PF_d3dWall_doLayout									pf_d3dWall_doLayout;

				//
				PF_tryToTalkToMessenger_d3dWall						pf_tryToTalkToMessenger_d3dWall;

				//
				PF_d3dWall_askToRefreshBg							pf_d3dWall_askToRefreshBg;
				PF_d3dWall_askToRefreshMenu							pf_d3dWall_askToRefreshMenu;
				PF_d3dWall_askToRefreshIa							pf_d3dWall_askToRefreshIa;
				
				//
				PF_getVal_bWmTalkerShadowExists						pf_getVal_bWmTalkerShadowExists;

				//  2015/10/30
				//PF_DXUTSaveTextureToFile							pf_DXUTSaveTextureToFile;

				//
				PF_refreshDlgTalkSubtitleMsgs_d3dWall				pf_refreshDlgTalkSubtitleMsgs_d3dWall;
				PF_refreshDlgTalkSubtitlesCfg_d3dWall				pf_refreshDlgTalkSubtitlesCfg_d3dWall;
				
				//
				PF_d3dWall_refreshAllWallMems						pf_d3dWall_refreshAllWallMems;
				PF_d3dWall_refreshWallMemByTalker					pf_d3dWall_refreshWallMemByTalker;
				
				//
				PF_d3dWall_refreshImgs								pf_d3dWall_refreshImgs;
				//
				PF_test_d3dWall_chkImgs								pf_test_d3dWall_chkImgs;
				
				//
				PF_tryToChkD3dWall									pf_tryToChkD3dWall;

				//
				PF_qisWall_exit										pf_qisWall_exit;
				//
				PF_CUBOID_tool_exit									pf_CUBOID_tool_exit;
				//
				PF_resetForResize									pf_resetForResize;
				//
				PF_d3dWnd_OnMouseMove								pf_d3dWnd_OnMouseMove;
				PF_d3dWnd_OnMove									pf_d3dWnd_OnMove;
				PF_d3dWnd_OnMoving									pf_d3dWnd_OnMoving;
				//
				PF_D3D_devCtx_pool_exit								pf_D3D_devCtx_pool_exit;
				PF_get_D3D_devCtx_pool								pf_get_D3D_devCtx_pool;
				//
				PF_generalWall_OnIsCmd								pf_generalWall_OnIsCmd;
				//
				PF_InitD3D											pf_InitD3D;
				PF_InitGraphics										pf_InitGraphics;
				PF_Cleanup											pf_Cleanup;

				PF_InitGraphics11									pf_InitGraphics11;


				//
				PF_renderNote_otherTalker							pf_renderNote_otherTalker;
				PF_renderNote_otherTalker_func						pf_renderNote_otherTalker_func;
				//
				PF_renderNoteFunc_importantNote						pf_renderNoteFunc_importantNote;
				PF_renderImportantNote								pf_renderImportantNote;
				PF_renderSubtitles									pf_renderSubtitles;

				//
				PF_addWmEnlarge										pf_addWmEnlarge;
				//
				PF_d3dWall_av										pf_d3dWall_av;
				PF_talkerFrm_init									pf_talkerFrm_init;
				PF_talkerFrm_exit									pf_talkerFrm_exit;

				PF_talkerFrm_mosaic_init							pf_talkerFrm_mosaic_init;
				PF_talkerFrm_mosaic_exit							pf_talkerFrm_mosaic_exit;

				//
				PF_d3dWall_closeDlgTalk								pf_d3dWall_closeDlgTalk;

				//
				PF_d3dWall_enlargeWall								pf_d3dWall_enlargeWall;
				//
				PF_hideAllCtrls_dxDialog							pf_hideAllCtrls_dxDialog;
				//
				PF_d3dWall_cleanMessageBox							pf_d3dWall_cleanMessageBox;
				PF_d3dWall_MessageBox								pf_d3dWall_MessageBox;

				//
				PF_g_DialogResourceManager_StoreD3D11State			pf_g_DialogResourceManager_StoreD3D11State;
				PF_g_DialogResourceManager_ApplyRenderUI11			pf_g_DialogResourceManager_ApplyRenderUI11;
				PF_g_DialogResourceManager_RestoreD3D11State		pf_g_DialogResourceManager_RestoreD3D11State;

				//
				PF_myRender_tool									pf_myRender_tool;

				//
				PF_stopUsingD3d										pf_stopUsingD3d;

				//
				PF_chkAndRecoverD3dImg_a							pf_chkAndRecoverD3dImg_a;

				//
				PF_chkAndRecoverD3dImg								pf_chkAndRecoverD3dImg;

				//
				PF_d3dWall_OnSize									pf_d3dWall_OnSize;

				//
				PF_saveTex12										pf_saveTex12;

				//
			}														isCliD3d;


			//
			struct {
				HINSTANCE											hDll;
				BOOL												bOk;
				//
				PF_doPre_toPlayVideo								pf_doPre_toPlayVideo;

				//
			}														aiResize;


			//
#if  0
			struct {
				HINSTANCE											hDll;
				BOOL												bOk;

				//
				PF_bPktSkipped										pf_bPktSkipped;
				PF_player_get_fps									pf_player_get_fps;

			}														ancPktProcess;
#endif 


			//						
			struct													{
				HINSTANCE											hDll;
				BOOL												bOk;
				//
				PF_initAecObj										pf_initAecObj;
				PF_exitAecObj										pf_exitAecObj;
				PF_aecObj_doAec										pf_aecObj_doAec;
				//
				PF_initAudioMixerObj								pf_initAudioMixerObj;
				PF_exitAudioMixerObj								pf_exitAudioMixerObj;
				PF_audioMixerObj_doMix								pf_audioMixerObj_doMix;


			}														help_audioProc;







			//						
			struct {
				HINSTANCE									hDll;
				BOOL										bOk;
				//
				PF_help_webrtc_init							pf_help_webrtc_init;
				PF_help_webrtc_exit							pf_help_webrtc_exit;

			}												help_webrtc1;



			//  2013/12/23
			struct   										{
				BOOL										bOk;
				//
				//
				PF_addTalkerShadow							pf_addTalkerShadow;
				PF_removeTalkerShadow						pf_removeTalkerShadow;
				//
				PF_dlgTalk_canSpeak							pf_dlgTalk_canSpeak;

				PF_getuiNextTranNo							pf_getuiNextTranNo;

				PF_myListCtrl_InsertItem					pf_myListCtrl_InsertItem;
				PF_myListCtrl_SetItemText					pf_myListCtrl_SetItemText;
				
				PF_showDlgPolicyAv							pf_showDlgPolicyAv;
				PF_showDlgPolicyIsClient					pf_showDlgPolicyIsClient;
				PF_showDlgMsgList							pf_showDlgMsgList;
				PF_showDlgObjs								pf_showDlgObjs;
				//
				//  PF_d3dWall_viewDlgTalk						pf_d3dWall_viewDlgTalk;
				//
				PF_d3dWall_setBg							pf_d3dWall_setBg;
				//PF_d3dWall_enlargeWall						pf_d3dWall_enlargeWall;

				//  2015/11/30
				PF_d3dWall_openQvw							pf_d3dWall_openQvw;

				//
				PF_dlgTalk_getTaskInfo						pf_dlgTalk_getTaskInfo;
				//
				PF_dlgTalk_getTaskList						pf_dlgTalk_getTaskList;

				//  2015/06/05
				PF_showMenu_wallsBar						pf_showMenu_wallsBar;

				//
				PF_showMenu_d3dWall							pf_showMenu_d3dWall;
				PF_showMenu_generalWall						pf_showMenu_generalWall;
				//
				PF_bTaskExists_recvResource					pf_bTaskExists_recvResource;
				PF_bTaskExists_sendingResource				pf_bTaskExists_sendingResource;

				//
				PF_dlgTalk_getCurSubtitlesCfg				pf_dlgTalk_getCurSubtitlesCfg;
				PF_dlgTalk_getSubtitleMsgs					pf_dlgTalk_getSubtitleMsgs;

				//
				PF_d3dWall_isUserActive						pf_d3dWall_isUserActive;
				//
				PF_getSubtitlesCfg							pf_getSubtitlesCfg;
				PF_subtitlesCfg_modify						pf_subtitlesCfg_modify;
				PF_getSubtitlesCfg_d3dWall					pf_getSubtitlesCfg_d3dWall;

				//  2015/11/21
				PF_viewVWall								pf_viewVWall;
				PF_viewGlobalVWall							pf_viewGlobalVWall;

				//  2015/12/12
				PF_addToWalls								pf_addToWalls;
				//
				PF_viewDlgMsgInput_talk						pf_viewDlgMsgInput_talk;
				PF_setMsgInputPos							pf_setMsgInputPos;


				//
				PF_bDlgTalkWaitToAccept						pf_bDlgTalkWaitToAccept;
				
				//
				PF_dlgTalk_re_acceptTask					pf_dlgTalk_re_acceptTask;		
				//
				//
				PF_bNoPrompt_selectAvCompressor				pf_bNoPrompt_selectAvCompressor;
				//PF_viewDlgSelectAvCompressor				pf_viewDlgSelectAvCompressor;

			}												isCliHelp;

			//
			struct											{
				BOOL										bOk;
				//
				PF_myOnAppAbout								pf_myOnAppAbout;
				//
				PF_toEditRtspUrlForConf						pf_toEditRtspUrlForConf;
			}												messenger_help;


			//  2015/02/17
			struct											{
				HINSTANCE									hDll;
				BOOL										bOk;

				PF_setGuiOpen_saveAv						pf_setGuiOpen_saveAv;
				PF_getSize_SAVE_av_procInfo					pf_getSize_SAVE_av_procInfo;
				PF_doSaveAv									pf_doSaveAv;	//  

			}												isCliSaveAv;

			//  2016/04/26
			void  *											pDynLib_isD3dFunc;

};




//  2013/06/08
FUNCS_for_isCliHelp  *  FUNCS_for_isCliHelp_new(  QY_MC  *  pQyMc  );
void  FUNCS_for_isCliHelp_free(  void  **  ppFuncs  );

//
int  load_isCliD3d(  LPCTSTR  fileName,  LPCTSTR  fileName_dx12,  FUNCS_for_isCliHelp  *  pFuncs  );
int  unload_isCliD3d(  FUNCS_for_isCliHelp  *  pFuncs  );

int  load_aiResize( FUNCS_for_isCliHelp* pFuncs);
int  unload_aiResize(FUNCS_for_isCliHelp* pFuncs);


int load_isCliSaveAv(FUNCS_for_isCliHelp* pFuncs);
int  unload_isCliSaveAv(FUNCS_for_isCliHelp* pFuncs);



int  load_help_audioProc(  FUNCS_for_isCliHelp  *  pFuncs  );
int  unload_help_audioProc(  FUNCS_for_isCliHelp  *  pFuncs  );

int  load_help_webrtc1(FUNCS_for_isCliHelp* pFuncs);
int  unload_help_webrtc1(FUNCS_for_isCliHelp* pFuncs);





#endif  //  }

