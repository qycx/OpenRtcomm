

#ifndef  __qmcCommFunc_isCli_h__
#define  __qmcCommFunc_isCli_h__	//  {

//
#include	"ctxQmc.h"

//
MIS_CNT  *  getMisCntByName(  MC_VAR_common  *  pProcInfo,  LPCTSTR  misServName  );
MIS_CNT  *  getMisCntByIndex(  void  *  p0,  MC_VAR_isCli  *  pProcInfo,  int  iIndex  );
int  getMisCntIndexByName(  void  *  p0,  MC_VAR_isCli  *  pProcInfo,  LPCTSTR  misServName  );


int  tryToStartChannel(  MIS_CNT  *  pMisCnt,  MIS_CHANNEL  *  pChannel,  TCHAR  *  respHint,  unsigned  int  respHintCnt  );
int  waitForChannel(  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  unsigned  int  uiChannelType,  BOOL  bForceQuit  );


//
int  updateMeDisplayInfo(  void  *  pMC_VAR_isCli,  MIS_CNT  *  pMisCnt,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  talkerDesc,  LPCTSTR  displayName  );

//
int  procMsgInput_mgr_req(  void  *  pQyMcParam,  void  *  pSgiParam,  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_INPUT  *  pMsgInput,  unsigned  int  lenInBytes_msg,  void  *  pCTX_MC_THREAD,  MIS_CHANNEL  *  pChannel  );
int  procMsgInput_mgr_resp(  void  *  pQyMcParam,  void  *  pSgiParam,  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_INPUT  *  pMsgInput,  unsigned  int  lenInBytes_msg,  void  *  pCTX_MC_THREAD,  MIS_CHANNEL  *  pChannel  );


//
int  procMsgInput_other_req(  void  *  pQyMc,  void  *  pSgi,  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_INPUT  *  pMsgInput,  unsigned  int  lenInBytes_msg,  void  *  pCTX_MC_THREAD,  MIS_CHANNEL  *  pChannel  );
int  procMsgInput_other_resp(  void  *  pQyMc,  void  *  pSgi,  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_INPUT  *  pMsgInput,  unsigned  int  lenInBytes_msg,  void  *  pCTX_MC_THREAD,  MIS_CHANNEL  *  pChannel  );


//
int  procMsgTask_mc_mgr(  void  *  pQyMcParam,  void  *  pSciParam,  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_TASK  *  pMsg,  unsigned  int  lenInBytes_msg,  BOOL  bMsgInput,  void  *  pCTX_MC_THREAD,  MIS_CHANNEL  *  pChannel  );
int  procMsgTask_mc_media(  void  *  pQyMc,  void  *  pSci,  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_TASK  *  pMsg,  unsigned  int  lenInBytes_msg,  BOOL  bMsgInput,  void  *  pCTX_MC_THREAD,  MIS_CHANNEL  *  pChannel  );


int  initTaskAvFrom_audio(  MC_VAR_common  *  pProcInfo,  DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from,  int  index_activeMems_from,  QY_TRANSFORM  *  pTransform  );
void  exitTaskAvFrom_audio(  MC_VAR_common  *  pProcInfo,  QY_TRANSFORM  *  pTransform  );


//
int  startChannel(  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  MIS_CHANNEL  *  pChannel,  LPCTSTR  hint  );

//
bool  bUseMachineKey_qmc(  CCtxQyMc  *  pQyMc  );
//
int  initCrypt_qmc(  MC_VAR_isCli  *  pVar,   MIS_CNT  *  pMisCnt,  LPCTSTR  szContainer,  LPCTSTR  szProvider,  BOOL  bMachineKey,  BOOL  bNewKeySetIfNotExists,  ENC_CTX_session  *  pEncCtx  );
void  exitCrypt_qmc(  MC_VAR_isCli  *  pVar,  MIS_CNT  *  pMisCnt,  ENC_CTX_session  *  pEncCtx  );





//
__declspec(  dllexport  )  int  procTaskGpsDataResp(  MC_VAR_isCli  *  pProcInfo,  void  *  pTranInfo,  PROC_TASK_GPS  *  pTask,  MIS_MSG_INPUT  *  pMsgInput,  TRANSFER_GPS_dataResp  *  pResp  );

//
__declspec(  dllexport  )  int  procMsgTask2Output_mc(  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSG_TASK  *  pMsg,  unsigned  int  lenInBytes_msg,  MIS_CHANNEL  *  pChannel,  LPCTSTR  tHint  );

//
int chkTasksStatus(AtTasksStatus* pTasksStatus, LPCTSTR  hint);

//
int mainWnd_chk_tasks(HWND hMainWnd, void  *  pVar);

int mainWnd_do_closeTask(int iTaskId);


//
int  chkPlayers(  MC_VAR_isCli  *  pProcInfo  );
//
int  chkSharedObjs(  MC_VAR_isCli  *  pProcInfo  );

//
BOOL  bRecorderUsing(  void  *  pMC_VAR_isCli,  void  *  pMoniker_a,  int  *  piIndex_capAudio,  int  *  piIndex_sharedObj  );
BOOL  bWebcamUsing(  void  *  pMC_VAR_isCli,  unsigned  int  uiCamCapType,  void  *  pMoniker_v,  LPCTSTR  camName,  int  *  piIndex_capBmp,  int  *  piIndex_sharedObj  );

//
//
//

#ifdef  __isCli__			//
int  initPtz(  );
//  void  exitPtz(  );
//  BOOL  isActive_comPort_ptz(  );
//  int doRemotePtzCmd(  char  *  buf,  unsigned  int  iLen  );
//
#endif


//
int  startLocalAudioPlayer(  MC_VAR_isCli  *  pProcInfo  );
int  stopLocalAudioPlayer(  MC_VAR_isCli  *  pProcInfo,  int  nTries  );
int  startLocalAudioPlaying(  MC_VAR_common  *  pProcInfoCommon  );
int  stopLocalAudioPlaying(  MC_VAR_common  *  pProcInfoCommon  );

//
int  startLocalAudioRecorder(  QY_MC  *  pQyMc,  unsigned  int  uiRecordType,  void  *  pGuid,  LPCTSTR  capDevDesc,  int  iIndex_sharedObj,  unsigned short usCntLimit_activeMems_from,  AUDIO_COMPRESSOR_CFG  *  pCompressor  );
int  stopLocalAudioRecorder(  MC_VAR_isCli  *  pProcInfoCommon,  int  index_sharedObj,  int  nTries  );
int  resumeLocalAudioRecorder( QY_MC  *  pQyMc, int  iIndex_sharedObj  );

int  closeOtherPlayers(  MC_VAR_isCli  *  pProcInfo  );


//
int  exitDSoundToPlayIfNoPlayer(  MC_VAR_isCli  *  pProcInfo  );


//
int  startPlayAudio_dSound(  void  *  pPlayerParam  );
int  stopPlayAudio_dSound(  void  *  pPlayerParam  );



//
//
int  waitToQuit_isCli(  MC_VAR_isCli  *  pProcInfo,  int  dwTimeInMs,  LPCTSTR  hint  );
int  notifyPanicToApp(  QY_MC  *  pQyMc,  int  iErr,  LPCTSTR  hint  );



#endif  //  }


