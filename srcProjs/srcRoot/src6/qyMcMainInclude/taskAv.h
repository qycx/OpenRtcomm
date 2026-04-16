
#ifndef  __taskAv_h__
#define  __taskAv_h__	//  {

//
//
#include	"mytypes.h"
#include	"qmcTransform.h"


//
#include	"ctxQmcTmpl.h"
#include	"taskCommon.h"
#include	"qmcTaskInfo.h"

//
//  2016/04/18
//
typedef  struct  __procTaskAv_t										{											//  

				 HWND												hWnd_task;									//  2009/09/09

				 VIDEO_CONFERENCE_CFG								videoConferenceCfg;

				 //
				 unsigned  int										uiTaskType;									//  2017/09/08

				 //
				 unsigned  char										ucbSendLocalAv;								//  2008/06/12
				 int												iIndex_sharedObj;
				 //  2014/12/11
				 int												iIndex_sharedObjUsr;						//  2014/12/11


				 //  2014/09/24
				 int												iIndex_taskInfo;							//  2014/09/24

				 //
				 unsigned  char										ucbLocalSource_rtspStream;					//  2014/03/16
				 
				 //
				 unsigned  char										ucbStarter;									//  2010/08/31
				 unsigned  char										ucbVideoConference;							//  2009/05/30
				 unsigned  char										ucbVideoConferenceStarter;					//  
				 TASK_AV_FROM										mem0_from;									//  the first member in mems_from array. 2009/02/15

				 //
				 unsigned  short									usCntLimit_mems_from;
				 TASK_AV_FROM								*		pMems_from;


				 //  2014/08/04
				 struct												{
					 unsigned  int									uiObjType;									//  2014/08/08
					 unsigned  short								usIndex_obj;
					 //
					 unsigned  char									ucbSaveVideo_req;
					 //unsigned  char								ucbSaveVideo_reply;							//  2014/09/07
					 //
					 DWORD											dwLastTickCnt_notification;
				 }													saveVideo;


				 //  2014/11/10
				 struct												{
					 //
					 BOOL											bExists_confMosaic;
					 //
					 int											iIndex_sharedObj_video;
					 int											iIndex_sharedObj_resource;
				 }													confMosaicMaker;

				 //
#if  0
				 struct												{
					 //
					 BOOL											bExists_confMosaic;							//  for conference mems
					 //
					 PROC_conf_mosaic								confMosaic_video,  confMosaic_resource;
				 }													confMosaicTrans;
#endif
				 
				 //
#define  bApplyForAvProxy(  pMisCnt,  pTRANSFER_AV_INFO  )			(  (  pTRANSFER_AV_INFO  )->idInfo_logicalPeer.ui64Id  &&  pMisCnt->idInfo.ui64Id  !=  (  pTRANSFER_AV_INFO  )->idInfo_logicalPeer.ui64Id  )
				 //  2014/11/21
				 struct												{											//  2014/11/21. 要求proxy服务的客户端. 申请proxy的特点是有一个content_idInfo_logicalPeer
					 //
					 BOOL											bRecvd_proxyReply;							//  得到了响应
					 //
					 struct											{
						 struct										{
							 unsigned  int							uiTranNo_openAvDev_a;							
							 unsigned  int							uiTranNo_openAvDev_v;
						 }											proxy;
					 }												proxyReply;

				 }													applyForProxy;

				 //
				 struct												{
					 BOOL											bExists;
					 //
					 struct											{
						 time_t										tStartTran;						
						 unsigned  int								uiTranNo;
					 }												proxy;					 
				 }													dlgTalkInProxy;
				 //  2014/11/19
				 struct												{
					 //
					 BOOL											bExists_avProxy;
					 //
				 }													doProxy;									//  2014/11/19. 用一个客户端为另一个客户端做转发。在mosaic需要这么做

				 //  2014/11/21
				 struct												{
					 //
					 BOOL											bRecvd_proxiedTranInfo;
					 //				
					 TASK_AV_FROM									proxied_from;								//  2014/11/21
				 }													receiver;

				 //
				 unsigned  short									usCntLimit_transforms;						//  2009/05/12
				 QY_TRANSFORM							*			pTransforms;								//  2009/05/12

				 unsigned  short									usCntLimit_dispatchs;						//  2011/12/08
				 QIS_DISPATCH							*			pDispatchs;									//  2009/06/17

				 //
				 struct												{
					 unsigned  short								usMaxFps_toShareBmp_conf;					//  2009/06/04

					 void								*			pMsgTask_toTransform;
				 }													video;
				 struct												{

					 AUDIO_PLAY_CFG									playCfg;									//  2009/06/14
					 
					 //
					 void								*			pMsgTask_toTransform;
				 }													audio;

				 //  
				 struct												{

					 QY_Q2								*			pOutputQ2;									//  2009/07/26

					 #ifdef  __DEBUG__					 
							 TRANSFER_videoData_stat				stat;										//  2011/01/26
					 #endif

				 }													photomosaic;								//  

				 //  
				 struct												{

					 QY_Q2								*			pOutputQ2;

					 time_t											tLastTime_showFrameInfo;
					 unsigned  short								usCnt_pkts;

				 }													mixer;
				 

				 //  
				 struct												{
					 int											maxxScreen;
					 int											maxyScreen;

					 RA_POINTER_EVENT								pointerEvent;	

				 }													remoteAssist;

	

				 //  2016/02/29
				 struct												{
					 DWORD											dwTickCnt_recentlyRefreshed;
					 //
					 BOOL											bWaitingTo_beRe_accepted;
				 }													canceledTask_status;


				 //
				 BOOL												bTaskInvalid;								//  2009/09/14
				 
				 //			
				 AV_TRAN_INFO reply_avTranInfo;
				 
				 //
				 TCHAR												debugHint[128];								//  2009/10/15

}		 PROC_TASK_AV;


//
//  2009/10/20
typedef  struct  __procTaskFile_t										{											//  video

				 HWND													hWnd_task;									//  2009/09/09


				 //
				 struct													{
					 __int64											tStartTime_reply;
					 unsigned int										uiTranNo_reply;
					 //
					 TRANSFER_FILE_REPLYREQ								replyReq;
					 
					 //
					 __int64											tStartTime_lastFileDataReq;
					 unsigned  int 										uiTranNo_lastFileDataReq;
					 
				 }														reply_info;

				 //
				 FILE										*			fp;

				 //

#if  10
				 //
				 DWORD64												ui64FileLen;
				 unsigned  int                                          reqBlock;
				 //
				 WCHAR													fileName_transferred[256  +  1];	//  
				 WCHAR													fullFilePath_save[MAX_PATH  +  1];	//  
				 unsigned  int											uiSizePerSnd_internal;				//  

				 //
				 unsigned  int											MAX_FILE_SEND_BLOCK_internal;

				 //
				 unsigned  int											uiLastDataBlockIndex;				//  
				 unsigned  short										usErrors;							//  

				 //
				 unsigned  char											ucPercent;							//  

				 //
				 int													nTimes_toRestart;

#endif


}		 PROC_TASK_FILE;





typedef struct __task_transferAv_t
{
	M_taskCommon

	//
	PROC_TASK_AV myTask;
}	TASK_transferAv;


typedef  struct  __task_transferFile_t 
{
	M_taskCommon

	//
	PROC_TASK_FILE  myTask;										
}		 TASK_transferFile;


//
#if  0  // def  __DEBUG__
//
//  2016/04/18.
typedef  struct  __transferAv_task_t								{

				 //
				 //
				 TRANSFER_AV_INFO									req;

				 //
				 PROC_TASK_AV										myTask;

}		 TRANSFER_AV_task,  TRANSFER_av_task;



//
//  
typedef  struct  __transferAvReplyTask_t							{									//  2007/07/06
				 //
				 TRANSFER_AV_replyInfo								req;

				 //
				 PROC_TASK_AV										myTask;
				 
}			    TRANSFER_AV_reply_task;	 	


//
//
PROC_TASK_AV  *  get_transferAvInfo_pTask(  TRANSFER_AV_INFO  *  pTransferAvInfo,  LPCTSTR  hint  );
PROC_TASK_AV  *  get_transferAvReplyInfo_pTask(  TRANSFER_AV_replyInfo  *  pTransferAvReplyInfo,  LPCTSTR  hint  );
#endif

//
int  startTransformThreads(  MC_VAR_common  *  pProcInfo,  unsigned  int  uiTaskType,  PROC_TASK_AV  *  pTask  );
int  stopTransformThreads(  MC_VAR_common  *  pProcInfo,  PROC_TASK_AV  *  pTask  );


//  2014/08/05
//  #define		M_getMutexName_syncActiveMem(  pQmcCfg,  iTaskId,  mutexName,  mutexNameCnt  )		_sntprintf(  mutexName,  mutexNameCnt,  _T(  "%s%d"  ),  (  pQmcCfg  )->mutexName_syncActiveMem_prefix1,  iTaskId  )
#define		M_getMutexName_syncActiveMem(  pQmcCfg,  iTaskId,  mutexName,  mutexNameCnt  )		_sntprintf(  mutexName,  mutexNameCnt,  _T(  "%s%d.%d"  ),  (  pQmcCfg  )->mutexName_syncActiveMem_prefix1,  GetCurrentProcessId(  ),  iTaskId  )


//
//
typedef  struct  __transInfo_stream_t			{
				 MSGR_ADDR						addr_logicalPeer;

				 AV_TRAN_INFO					tranInfo;
				 PROC_TASK_AV					myTask;

				 //
				 int							iTaskId;				//  为了对rtsp流解码，虚拟一个任务
				 int							index_taskInfo;

				 //
}		 TRANSINFO_stream;


//
 int  initTransforms(  void  *  pMC_VAR_common,  MSGR_ADDR  *  pAddr_logicalPeer,  int  iTaskId,  unsigned  int  uiTaskType,  AV_TRAN_INFO  *  pTranInfo_unused,  PROC_TASK_AV  *  pTask,  MIS_MSG_TASK  *  pMsgTask  );
 void  exitTransforms(  void  *  pMC_VAR_common,  PROC_TASK_AV  *  pTask  );

 //
 __declspec(dllexport)  int  getNextAPktInfo_toDec(  PKT_info_toDec  *  pCurPktInfo,  QY_Q2  *	pAudioQ2  );
 __declspec(dllexport) void  clean_PKT_info_toDec(  PKT_info_toDec  *  p,  LPCTSTR  hint  );



 //
int  getNextAPkt(  myPLAY_AUDIO_DATA  *  pCurPkt,  GENERIC_Q  *	pInDataCacheQ,  QY_Q2  *	pAudioQ2  );
int  detachAPkt(  void  *  pPkt_myPLAY_AUDIO_DATA,  void  *  p1  );

//
int  getNextVPkt(  myDRAW_VIDEO_DATA  *  pCurPkt,  GENERIC_Q  *	pInDataCacheQ,  QY_Q2  *	pVideoQ2  );
int  detachVPkt(  void  *  pPkt_myDRAW_VIDEO_DATA,  void  *  p1  );


BOOL  bTransformAudioQuit(  void  *  pQY_TRANSFORM,  void  *  p1,  void  *  p2  );
BOOL  bTransformVideoQuit(  void  *  pQY_TRANSFORM,  void  *  p1,  void  *  p2  );


///
//  2014/11/12
TASK_AV_FROM  *  getTaskAvFrom(    QY_TRANSFORM  *  pTransform,  int  index_pMems_from,  int  index_activeMems_from,  LPCTSTR  hint  );
TASK_AV_FROM  *  getTaskAvFrom(    PROC_TASK_AV  *  pTask,  int  index_pMems_from,  LPCTSTR  hint  );

//
//
int  get_ucHardwareAccl( QY_MC  *  pQyMc );

//
 int adjustModuleType_decV( QY_MC  *  pQyMc,  uint *uiModuleType);
 int adjustModuleType_encV(  uint *uiModuleType);
int adjustModuleType_decA( uint *uiModuleType);
//
int adjustAudioBitrate(AUDIO_COMPRESSOR_cfgCommon* pCompressor);

//
int  getModuleType_encV(VIDEO_COMPRESSOR_cfgCommon* pCompressor, unsigned  int* puiModuleType);
int  getInputFourcc_encV(unsigned  int  uiModuleType, int* piFourcc);


//
int  initTaskAvFrom_video(  void  *  pMC_VAR_common,  DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from,  int  index_activeMems_from,  int  iTaskId,  unsigned  int  uiModuleType_suggested,  BOOL  bUseDecTool_suggested,  QY_TRANSFORM  *  pTransform  );
void  exitTaskAvFrom_video(  void  *  pMC_VAR_common,  QY_TRANSFORM  *  pTransform  );


//
//
__declspec(  dllexport  )  int  dispatch_outputConfVideo(  PROC_TASK_AV  *  pTask,  MIS_MSG_TASK  *  pMsgTask,  TRANSFER_VIDEO_DATA  *  pTransferVideoData,  QY_MESSENGER_ID  *  pIdInfo_from,  int  uiTranNo_openAvDev_conf  );



#endif  //  }


