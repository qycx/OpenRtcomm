
#ifndef  __ctxQmcTmpl_t__
#define  __ctxQmcTmpl_t__


#ifdef  __useMfc__
		 #include	<afxtempl.h>
#else
		#include	<CommCtrl.h>
#endif


#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<MSAcm.h>
#endif

#include	<Wincrypt.h>
#include	<WinSock2.h>

//  2013/11/26
#include	"mydbg.h"

#include	"qmCommon.h"

//
#include	"qmcDefs.h"


#include	"qmcrypt.h"

//
#include	"qmcSharedObj.h"

//  2016/04/19
#include	"qmcTransform.h"

//  2016/09/13
#include	"qmcStruct_defs.h"
#include	"qisGuiPublic_public.h"


//
typedef  struct  __renderStatus_t	{
				 float				fps;
				 DWORD				dwTickCnt_calcFps;
}		 RENDER_status;


//
typedef  struct  {
	
				 QY_MESSENGER_ID						idInfo_sender;
				 DWORD									dwTickCnt_lastRefreshed;

}	applyForOrgReq_status_mem;


//
typedef  struct  __atTasksStatus_t {

				 //
				 bool				bTaskExists_av;
				 bool				bTaskExists_file;

}		 AtTasksStatus;


//  2015/01/21
typedef  struct  __qmcStatus_									{
					 unsigned  long								ulbThreadProcInited:1;										//  mcThreadProc_mis 2007/09/02
					 
					 //																									//
					 struct {
						 unsigned  long							ulbMgrQuit : 1;												//  
						 unsigned  long							ulbDisplayQuit : 1;											//  display
						 unsigned  long							ulbWorkQuit : 1;												//  work
						 unsigned  long							ulbSchedulerQuit : 1;											//  scheduler
						 unsigned  long							ulbRobotQuit : 1;												//  svr
						 unsigned  long							ulbMediaQuit : 1;												//  media
						 unsigned  long							ulbRealTimeMediaQuit : 1;										//  realTimeMedia
						 unsigned  long							ulbRtOpQuit : 1;												//  2016/12/26
						 unsigned  long							ulbLogQuit : 1;												//  log
					 }											threadsStatus;

					 //
#if  0
					 struct										{
						 unsigned  long							ulbImGrpExists:1;											//  是否下载了分组信息。2011/04/10.
						 unsigned  long							ulbContactExists:1;											//  是否下载了contact信息
						//
						unsigned  long							ulbAllContactsRetrieved:1;									//  是否用户信息都下载了. 2013/08/01
						//
						unsigned  short							nTimes_refresh;												//  因为access写入较慢,所以,在所有用户信息得到后,需要自动的刷新几次. 比如3次
						DWORD									dwTickCnt_lastRefreshed;
					 }											retrieveImObjList;
#endif

					 //
					 struct										{
						 DWORD									dwTickCnt_start;
						 DWORD									dwTimeInMs;
					 }											waitToQuit;													//  2011/02/02

					 //
					 DWORD										dwTickCnt_toStat;											//  2009/10/11
					 //
					 struct										{											 				//  for cpu usage. 2009/10/10
						 LARGE_INTEGER							oldIdleTime;
						 LARGE_INTEGER							oldKernelTime;
						 LARGE_INTEGER							oldUsrTime;
						 //
						 DWORD									dwTickCnt_start_ce;
						 DWORD									dwIdleTime_start_ce;
						 //
						 int									iCpuUsage;
					 }											cpu;
					 QMC_net_stat								netStat;													//  2009/10/10
					 MEMORYSTATUS								memory;														//  201007/28
					 RENDER_status								render;


					 //
					 DWORD										dwTickCnt_diskToStat;										//

					 struct {
							__int64									sumDiskSize;
							__int64									availableDiskSize;
							
					 }											iDiskUsage;

					 //
					 struct										{
						 DWORD									dwTickCnt_lastDisplayed;
						 TCHAR									tBuf[256];					 
						 int									len;
					 }											notification;

					 //  2010/08/14
					 //QY_PROGRESS								progress;

					 //  2012/03/25
					 long										nThreads_dec;
					 long										nThreads_dispatch;						//  2013/08/26
					 long										nThreads_player;
					 long										nThreads_aTrans;						//  2014/03/15
					 long										nThreads_vTrans;						//  2014/03/15
					 long										nThreads_talkerProc;					//  2016/03/15
					 long										nThreads_shareDynBmps;					//  2016/06/15

					 //  2013/03/07
					 DWORD										dwTickCnt_chkDb;
					 
					 //  2017/10/03
					 DWORD										dwTickCnt_sendTo_applyForOrgReq;		//  2017/10/03

					 //  2013/07/19
					 struct										{
						 int									xPos_screen;  
						 int									yPos_screen;
						 //
						 HWND									hParent_ia;								//  2012/05/03					
						 //
					 }											param_viewInstantAssistant;						

					 //  2014/02/04
					 struct                          			{
						 struct									{
							 int								xPos;  
							 int								yPos;
							 //
							 DWORD								dwLastTickCnt;
						 }										mousemove,  lButtonDown,  command;
						 //  2016/01/15
						 struct									{
							 BOOL								bSetCaptured;
							 unsigned  int						uiTranNo_wm;
							 
							 //
							 RECT								bgScreenRect_wm;
							 
							 //
							 int								sx_mouse,  sy_mouse;


						 }										SetCapture;
						 //
					 }											param_d3dWall;

					 //  2014/02/11
					 struct										{
						 int									uiQNodes_displayedObjQ;
					 }											display;								//  thread_display的状态.
					 //  2014/05/27
					 struct										{
						 int									maxiTotal;
						 int									nTotal;
					 }											hashTbl_leftView_db;

					 //  2014/12/22
					 struct										{
						 BOOL									bFailed_newSharedObj;
					 }											sysErr;

					 //  2015/06/18
					 struct										{
						 TRANS_pts_info							transPtsInfo_sum;
						 TRANS_pts_info							transPtsInfo_sum_last;
						 //
						 BOOL									bTooManyPtsErr;
						 unsigned  char							ucCnt_bTooManyPtsErr;
						 DWORD									dwTickCnt_lastModified_bTooManyPtsErr;
						 //
						 BOOL									bWarning;

					 }											ptsStat;
				 
					 //
					 struct										{
						 unsigned  __int64						ui64_a_pkts_ok;
						 unsigned  __int64						ui64_a_pkts_err;
						 unsigned  __int64						ui64_v_pkts_ok;
						 unsigned  __int64						ui64_v_pkts_err;
						 //
					 }											pktsStat;

					 //  这个avStatus似乎应该和tasksStatus合并。
					 struct										{
						 //
						 bool									bExists_meeting;

					 } avStatus;

					 //
					 struct {
						 //
						 bool									bDone_createConsoleWall;

					 } confServerStatus;

					 //
					 struct {
						 //
						 bool									bGot_confReq;
						 DWORD									dwLastTickCnt_confReq;

						 //
						 bool									bDone_doCmd_startAvCall;
						 DWORD									dwLastTickCnt_doCmd_startAvCall;

						 //
						 DWORD									dwLastTickCnt_toShareVideo_post_qmc;
						 int									nTimes_noVideo;

						 //
						 DWORD									unused_dwLastTickCnt_reserved;

					 }											confStatus;


					 //
					 struct {
						 applyForOrgReq_status_mem				mems[10];
					 }  applyForOrgReq_status;

					 //
					 AtTasksStatus								tasksStatus;

					 //  2018/10/30
					 TCHAR										vName_1st_webcam[256];	

					 //
					 TCHAR										tSysStateDesc[256];

}		QMC_status;


//
#include	"qmcDebugStatusInfo.h"


//  2015/07/07
#include	"ctxQyTmpl.h"

//
class  CCtxQmcTmpl;

//
typedef  int  (  *PF_doDecodeVideo_dvtCli  )(  QY_TRANSFORM  *  pTransform,  int  index_pMems_from,  unsigned  int  uiModuleType_toDec,  MIS_MSGU  *  pMsgBuf  );
//
typedef  int  (  *PF_qdcInitCompressVideo_evtCli  )(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_decompress,  QY_VIDEO_HEADER  *  pVh_compress,  unsigned  int  uiModuleType,  QDC_OBJ_INFO  *  pQdcObjInfo  );
typedef  int  (  *PF_qdcExitCompressVideo_evtCli  )(  QDC_OBJ_INFO  *  pQdcObjInfo  );
//
typedef  int  (  *PF_qdcGetSpsPps_evtCli  )(  QDC_OBJ_INFO  *  pQdcObjInfo,  char  *  spsBuf,  unsigned  int  *  puiSpsSize,  char  *  ppsBuf,  unsigned  int  *  puiPpsSize,  char  *  vpsBuf,  unsigned  int  *  puiVpsSize  );
//
typedef  int  (  *PF_doEncodeVideo_evtCli_run  )(  CCtxQmcTmpl  *  pProcInfo,  CAP_procInfo_bmpCommon  *  pCapProcInfo,  void  *  pMIS_CNT,  MIS_MSGU  *  pMsgBuf  );



//
class  CCtxQmcTmpl: public CCtxQyTmpl  
{

public:

CCtxQmcTmpl(  );
virtual  ~CCtxQmcTmpl(  );

	//
	MACRO_mcVar_common
		
//
char  _start;
	  //  2012/03/25		
	  //				
	  HWND											hWnd_testWebcam;											//  2009/08/16
	  //
	  HWND											hWnd_testSpeed;
	  //
	  PF_doDecodeVideo_dvtCli						m_pf_doDecodeVideo_dvtCli;									//  2016/04/28
	  //	  
	  PF_qdcInitCompressVideo_evtCli				m_pf_qdcInitCompressVideo_evtCli;
	  PF_qdcExitCompressVideo_evtCli				m_pf_qdcExitCompressVideo_evtCli;
	  //
	  PF_qdcGetSpsPps_evtCli						m_pf_qdcGetSpsPps_evtCli;
	  //
	  PF_doEncodeVideo_evtCli_run					m_pf_doEncodeVideo_evtCli_run;

	  //
char  _end;

//
private:
	char  _start_private;
		  BOOL										bQuit_internal;
	char  _end_private;

public:
	//
	virtual  BOOL									bCtxQuit(  );
	int												setCtxQuit(  );

//
virtual  RW_lock_param  *  get_qyMc_rwLockParam(  )  =  0;
//
virtual  TCHAR  *  get_appObjPrefix(  )  =  0;

//
virtual  void  *  get_qmc_cfg(  )  =  0;

//
virtual  QNM_CUSRES_INFO  *  get_qyMc_cusRes(  )  =  0;

//
virtual  QMC_status  *  get_qmc_status(  )  =  0;
virtual  QMC_debugStatusInfo  *  get_qmc_debugStatusInfo(  )  =  0;

//
virtual QY_sharedObj_sync  *  getSharedObjSyncByIndex(  int  index  )  =  0;
//virtual QY_SHARED_OBJ  *  getSharedObjByIndex(  int  index  )  =  0;

virtual  CAP_procInfo_bmpU  *  getCapBmpBySth(  int  index,  unsigned  int  uiCapType  )  =  0;
virtual  CAP_procInfo_audioU  *  getCapAudioBySth(  int  index,  unsigned  int  uiCapType  )  =  0;

//
virtual  void  *  get_QM_SHM_CMDS(  )  {  return  NULL;  }
virtual   int  newShmCmdIndex(  int  iIndex_sharedObj  )  =  0;
virtual  void  *  getQmShmCmdByIndex(  int  iIndex  )  =  0;

//  2016/03/15
virtual void  *  getQmcTaskInfoByIndex(  int  index  ) {  return  NULL;  }

//  2015/10/13
virtual  void  *  get_g_guiData(  )  {  return  NULL;  }


//  2015/10/13
virtual  unsigned  char  get_ucCnt_misCnts(  )  {  return  0;  }
//
virtual MIS_CNT  *  getMisCntByName(  LPCTSTR  misServName  )  =  0;
virtual MIS_CNT  *  getMisCntByIndex(  int  iIndex  )  =  0;

//
virtual  HWND  get_hMainWnd(  )  =  0;

//
virtual  void  *  getPolicyAvParams(  )  =  0;

//  2015/10/30
virtual  void  *  get_pFuncs_for_isCliHelp(  )  {  return  NULL;  }

//
virtual  void  *  getCusModules(  )  =  0;


//  2016/09/27
virtual  int  setQmDbFuncs(  int  iDbType,  QM_dbFuncs  *  pDbFuncs  )  =  NULL;

//
virtual  int  initInfrared() = NULL;
virtual  int  exitInfrared() = NULL;


//
virtual  BOOL  bSupported_dvt(  unsigned  int  uiModuleType_toDec  )  {  return  FALSE;  }
//  2015/10/13
virtual  BOOL  bSupported_evt(  unsigned  int  uiModuleType_toEnc  )  {  return  FALSE;	}

//  2017/10/11	  
virtual  BOOL  bUse_imObjView_as_guiWnd(  )  {  return  FALSE;  }

//
virtual  BOOL  b_qyMc_quit(  )  =  0;

//  2015/10/14
virtual  QY_Q2  *  get_realTimeMediaQ2(  )  {  return  NULL;  };
virtual  QY_Q2  *  get_mediaQ2(  )  {  return  NULL;  };

//
virtual  BOOL  bWebcamUsing(  unsigned  int  uiCamCapType,  void  *  pMoniker_v,  LPCTSTR  camName,  int  *  piIndex_capBmp,  int  *  piIndex_sharedObj  )  =  0;
virtual  BOOL  bMediaTaskExists(  int  iTaskId  )  =  0;

//
virtual  BOOL  bAudioChannelReady(  )  =  0;
virtual  BOOL  bVideoChannelReady(  )  =  0;


//  2015/10/14
virtual  int  toShareVideo_post(  unsigned  int  uiCapType,  int  iIndex_capProcInfo,  myDRAW_VIDEO_DATA  *  pkts,  unsigned  int  nPkts,  COMPRESS_VIDEO  *  pCompressVideo,  QY_SHARED_OBJ  *  pSharedObj,  MIS_MSGU  *  pMsgBuf  )  {  return  -1;  }



//
virtual  int  drawLocalVideoData(  unsigned  int  uiTranNo,  myDRAW_VIDEO_DATA	*	pkts,  int  pktsLen,  BOOL  *  pbPktsRedirected,  unsigned  int  uiCapType,  int  iIndex_capBmp,  int  iTaskId,  void  *  pMIS_CNT,  QY_MESSENGER_ID  *  pIdInfo_peer  )  {  return  -1;  }
virtual  int  drawVideoData(  myDRAW_VIDEO_DATA  *  pkts,  int  pktsLen,  BOOL  *  pbPktsRedirected,  void  *  pQY_TRANSFORM  )  =  0;
//
virtual  int  playLocalAudioData(  int  iTaskId,  unsigned  int  uiTranNo,  WAVEFORMATEX  *  pWf,  myPLAY_AUDIO_DATA  *  pPkt,  int  pktLen,  BOOL  *  pbPktRedirected,  unsigned  int  uiCapType,  int  iIndex_capAudio  )  {  return  -1;  }
virtual  int  playAudioData(  int  iSampleTimeInMs,  unsigned  int  uiPts,  BYTE  *  pInput,  unsigned  int  inputLen,  int  iIndex_player  )  =  0;


//  2015/10/14
virtual  void  *  get_cur_SUBTITLES_cfg(  int  iSharedObjType,  int  iCapType,  int  iCapSubType  )  {  return  NULL;  }
 //
virtual  int resizeRgb24(  unsigned  char  *  src,  int  srcWidth,  int  srcHeight,  unsigned  char  *  dst,  int  dstWidth,  int  dstHeight  )  {  return  -1;  }



//
virtual  int  showNotification(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  LPCTSTR  hint  )  =  0;

//
virtual int  qisChkTasks_gui(  )  =  0;			//  2009/09/10
//virtual int  applyForRemovingInvalidTasks(  unsigned  int  uiChannelType  )  =  0;
//virtual int  removeInvalidTasks(  unsigned  int  uiChannelType  )  =  0;					//  2009/09/10

//
#define		CONST_pktUsage_null		0
#define		CONST_pktUsage_dec		1
#define		CONST_pktUsage_enc		2

//
#ifdef  __DEBUG__
//virtual  unsigned  short  get_pktResType_suggested(  int  pktUsage,  unsigned  int  uiModuleType  )  =  0;				//  2015/10/04
#endif
//
virtual  int  get_deced_pktResType(  unsigned  int  uiModuleType,  int  iFourcc,  unsigned  short  *  pusPktResType_o  )  =  0;				//  2015/10/04
virtual  int  get_pktResType_toEnc(  unsigned  short  usPktResType_src,  unsigned  int  uiModuleType,  int  iFourcc,  unsigned  short  *  pusPktResType_i  )  =  0;				//  2015/10/04


//
//
//
//  2015/10/30
virtual void  *  get_pf_DXUTSaveTextureToFile(  )  {  return  NULL;  }

//  2016/02/12
virtual  int  set_enlarged_gZone(  HWND  hWnd  )  {  return  -1;  }


//  2016/04/26
virtual int  initCompressVideo(  BITMAPINFO  *  pBmpInfo_input,  unsigned  int  uiCapType,  VIDEO_COMPRESSOR_CFG  *  pCompressor,  BOOL  bCapDev,  unsigned  int  uiBufSize_pData,  COMPRESS_VIDEO  *  pCompressVideo  )  {  return  -1;}
virtual int  exitCompressVideo(  BOOL  bCapDev,  COMPRESS_VIDEO  *  pCompressVideo  )  {  return  -1;  }

//
virtual int  set_qoi_funcs(  MY_qoi  *  pMyQoi  )  =  NULL;	//    {  return  -1;  }

//  2016/09/09
virtual  int  removeMosaicFromD3dWall(  int  iIndex_sharedObj  )  {  return  -1;  }
virtual  int  getVal_bExists_mosaic(  int  iIndex_sharedObj,  BOOL  *  pbExists  )  {  return  -1;  }

//
//  2016/09/12
virtual  int  stopLocalAudioRecorder(  int  index_sharedObj,  int  nTries  )  {  return  -1;  }







};

//  2015/01/20
typedef  class  CCtxQmcTmpl		MC_VAR_common;





#endif

