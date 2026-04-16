

#ifndef  __qmcVideoCapture_isCli_H__
#define  __qmcVideoCapture_isCli_H__	//  {

//
#include	"qmcVideoCapture.h"

//
#include	"ctxQmc.h"
//
#include	"shareAv.h"






//
int  tryToFreeSharedObjs(  MC_VAR_isCli  *  pProcInfo  );
int freeAllSharedObjs(CCtxQmc* pProcInfo);

BOOL  bNoSharedObjExists(  MC_VAR_isCli  *  pProcInfo  );
void  stopAll_sharedObjs( MC_VAR_isCli  *  pProcInfo );






//
BOOL  canShareScreen(  MC_VAR_isCli  *  pProcInfo  );
BOOL  canRemoteAssist(  MC_VAR_isCli  *  pProcInfo  );
BOOL  bRemoteAssistExists(  MC_VAR_isCli  *  pProcInfo  );

BOOL  canRemotePtzControl(  MC_VAR_isCli  *  pProcInfo  );


//
int  newCapProcInfoBmpIndex(  MC_VAR_isCli  *  pProcInfo,  int  iIndex_sharedObj  );
int  newCapProcInfoAudioIndex(  MC_VAR_isCli  *  pProcInfo,  int  iIndex_sharedObj  );


//  2013/08/07
#define  isPlayerIndexValid(  pProcInfo,  index  )	  	(  (  index  )  >=  0  &&  (  index  )  <  (  pProcInfo  )->av.usCnt_players  )  

__declspec(  dllexport  )  QY_PLAYER  *  getPlayerByIndex(  MC_VAR_isCli  *  pProcInfo,  int  index  );



#if  0	//  2014/06/21
//
#define		CONST_fourcc_YUY2	MAKEFOURCC(  'Y',  'U',  'Y',  '2'  )		//  2010/05/31
#define		CONST_fourcc_YV12	MAKEFOURCC(  'Y',  'V',  '1',  '2'  )		//  2010/07/11
#define		CONST_fourcc_I420	MAKEFOURCC(  'I',  '4',  '2',  '0'  )		//  2010/07/11
#define		CONST_fourcc_HDYC	MAKEFOURCC(  'H',  'D',  'Y',  'C'  )		//  2012/01/03
//
#define		CONST_fourcc_v210	MAKEFOURCC(  'v',  '2',  '1',  '0'  )		//  2012/02/23

//  
#define		CONST_fourcc_h264	MAKEFOURCC(  'h',  '2',  '6',  '4'  )		//  2014/02/24
//
//  #define		CONST_fourcc_MP2T	MAKEFOURCC(  'M',  'P',  '2',  'T'	)		//  2014/03/05
#endif






//
BITMAPINFO  *  newBitmapInfo(  UINT bits,  unsigned  int  bmWidth,  unsigned  int  bmHeight  );

//
#include	"colorSpaceFunc.h"





#include	"addTxt.h"

//

//
int  postToDraw(  MC_VAR_isCli  *  pProcInfo,  unsigned  int  uiTranNo,  myDRAW_VIDEO_DATA  *  pPkt,  int  pktLen,  BOOL  *  pbPktRedirected,  unsigned  int  uiCapType,  int  iIndex_capBmp,  QY_MESSENGER_ID  *  pIdInfo_sender,  int nPkts_left,  QY_MESSENGER_ID  *  pIdInfo_peer,  int  iTaskId,  HWND  hWnd_task,  PLAYER_ID  *  pPlayerId,  LPCTSTR  hint  );

int doCalcMql(MC_VAR_isCli* pProcInfo, unsigned  int  uiTranNo, myDRAW_VIDEO_DATA* pPkt, QY_MESSENGER_ID* pIdInfo_sender, int  nPkts_left, QY_MESSENGER_ID* pIdInfo_peer, int  iTaskId, PLAYER_ID* pPlayerId, LPCTSTR  hint);

//
__declspec(  dllexport  )  int  tmpGetMaxAudioPlayCfg(  AUDIO_PLAY_CFG  *  pSrc0,  AUDIO_PLAY_CFG  *  pSrc1,  AUDIO_PLAY_CFG  *  pDst  );


//
int  drawVideoData(  MC_VAR_isCli  *  pProcInfo,  myDRAW_VIDEO_DATA  *  pkts,  int  pktsLen,  BOOL  *  pbPktsRedirected,  void  *  pQY_TRANSFORM  );

//
int  getBih_capBmpToPlay(  CAP_procInfo_bmpU  *  pCapBmp,  BITMAPINFOHEADER  *  pBih  );
//
int  drawLocalVideoData(  MC_VAR_isCli  *  pProcInfo,  unsigned  int  uiTranNo,  myDRAW_VIDEO_DATA	*	pkts,  int  pktsLen,  BOOL  *  pbPktsRedirected,  unsigned  int  uiCapType,  int  iIndex_capBmp,  int  iTaskId,  MIS_CNT  *  pMisCnt  =  NULL,  QY_MESSENGER_ID  *  pIdInfo_peer  =  NULL  );


//  
//  int  toShareBmp(  void  *	pProcInfoParam,		unsigned  int  uiCapType,  int  iIndex_capProcInfo,  myDRAW_VIDEO_DATA  *  pPkts,  unsigned  int  nPkts,  COMPRESS_VIDEO  *  pCompressVideo,  QY_SHARED_OBJ  *  pSharedObj,  MIS_MSGU  *  pMsgBuf  );













__declspec(  dllexport  )  int  qmcApplyForChkingTasks_gui(  QY_MC  *  pQyMc  );	//  2009/09/10
int  qmcChkTasks_gui(  MC_VAR_common  *  pProcInfo  );			//  2009/09/10

//
int  chkToApplyForChannel(  CCtxQmc  *  pProcInfo,  int  channelType,  bool  bForce  );



//
int  qmcApplyForRemovingInvalidTasks(  MC_VAR_common  *  pProcInfo,  unsigned  int  uiChannelType  );
//int  qmcRemoveInvalidTasks(  MC_VAR_common  *  pProcInfo  );			//  2009/09/10


//
__declspec(  dllexport  )  int  get_respInfoMem_state(  MIS_CNT  *  pMisCnt,  time_t  tNow,  TASK_respInfo_mem  *  pMem,  time_t  *  pTime_state  );



__declspec(  dllexport  )  int  procTaskAvReply(  MC_VAR_isCli  *  pProcInfo,  MSGR_ADDR  *  pAddr_logicalPeer,  int  iTaskId,  AV_TRAN_INFO  *  pAvTran,  PROC_TASK_AV  *  pTask,  MIS_MSG_TASK  *  pMsgTask  );
//
__declspec(  dllexport  )  int  tmp_procTask_recv_cancel(  MC_VAR_isCli  *  pProcInfo,  PROC_TASK_AV  *  pTask,  MIS_MSG_INPUT  *  pMsgInput,  TASK_PROC_REQ  *  pTaskProcReq  );
//
__declspec(  dllexport  )  int  procTaskVideoDataResp(  MC_VAR_isCli  *  pProcInfo,  AV_TRAN_INFO  *  pTranInfo,  PROC_TASK_AV  *  pTask,  MIS_MSG_INPUT  *  pMsgInput,  TRANSFER_VIDEO_dataResp  *  pResp  );

//
int  mySendAvResp(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_TASK  *  pMsg,  MIS_MSGU  *  pMsgBuf  );


//
__declspec(dllexport) int  chkFromPlayerIndex_a(  unsigned  int  uiTransformType,  void  *  pQY_TRANSFORM,  myPLAY_AUDIO_DATA  *  p,  void  *  p2  );

int  playAudioData(  MC_VAR_isCli  *  pProcInfo,  int  iSampleTimeInMs,  unsigned  int  uiPts,  BYTE  *  pInput,  unsigned  int  inputLen,  int  iIndex_player  );
//
 int  playLocalAudioData(  MC_VAR_isCli  *  pProcInfo,  int  iTaskId,  unsigned  int  uiTranNo,  WAVEFORMATEX  *  pWf,  int  iSampleTimeInMs,  BYTE  *  pInput,  unsigned  int  inputLen,  unsigned  int  uiCapType,  int  iIndex_capAudio  );




//
__declspec(  dllexport  )  int  procTaskAudioDataResp(  MC_VAR_isCli  *  pProcInfo,  AV_TRAN_INFO  *  pTranInfo,  PROC_TASK_AV  *  pTask,  MIS_MSG_INPUT  *  pMsgInput,  TRANSFER_AUDIO_dataResp  *  pTransferAudioDataResp  );

__declspec(  dllexport  )  int  procTaskRemoteAssist(  MC_VAR_isCli  *  pProcInfo,  MSGR_ADDR  *  pAddr,  int  iTaskId,  MIS_MSG_TASK  *  pMsgTask,  REMOTE_ASSIST_REQ  *  pRemoteAssistReq,  AV_TRAN_INFO  *  pTranInfo,  PROC_TASK_AV  *  pTask,  int  index_mems_from  );


//  int  getIDD_instantAssistant(  HWND  hDlgTalk,  int  *  piStatus_instantAssistant,  BOOL  *  pbMin  );
int  getIDD_instantAssistant(  HWND  hParent,  int  iWndContentType_hParent,  HWND  hDlgTalk,  int  *  piStatus_instantAssistant,  BOOL  *  pbMin  );

int  sizeAllControls_dlgInstantAssistant(  HWND  hDlgIa  );

#define		CONST_iaStatus_null					0
#define		CONST_iaStatus_start				1
#define		CONST_iaStatus_start_wait			2
#if  0		//  2013/04/06
	#define		CONST_iaStatus_resource				3
	#define		CONST_iaStatus_resource_wait		4
#endif
#define		CONST_iaStatus_av					5
#define		CONST_iaStatus_msg					6			//  2014/02/01


#endif  //  }



