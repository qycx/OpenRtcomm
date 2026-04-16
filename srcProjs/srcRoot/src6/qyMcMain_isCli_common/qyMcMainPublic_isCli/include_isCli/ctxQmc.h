
#ifndef  __ctxQmc_h__
#define  __ctxQmc_h__


#include	"qmcCommFunc_is_open.h"
#include	"qmcCommFunc_mis.h"
#include	"ctxQmcTmpl.h"

#include	"qyMcMainCommon.h"
#include	"qmcCfg.h"
#include	"mcSharedQ.h"
#include	"zone_objs.h"


//
#include	"qisPtzWnd.h"
#include	"qmcStruct_defs.h"
#include	"mixProc.h"

//
#include	"hgCommProc.h"
#include	"qmHgProc.h"

//
#include	"ipcProc.h"
#include	"qisSyncTex.h"
#include <qmcPlayDevTmpl.h>


//  2015/08/01
typedef  struct													{
					 HWND										hTool_offlineRes;
}																OfflineRes_var;


typedef  struct  __qmcAecInfo_t									{				
				 AEC_layout										aecLayout;		

				 //
				 QY_Q2											aecPlayQ2;
				 struct {
					 //
					 DWORD										dwTgt_start1;
					 //
					 int										mql;
					 //
				 }												aec_var;


}	QMC_aec_info;


//
						 //
typedef  struct  __hk_portStatus_t {
	//
	bool								bDisable_hdmi1Out_hdmi;		//  primary screen
	bool								bDisable_hdmi2Out_dvi;		//  second screen
	bool								bDisable_hdmiIn_vga;		//  采集卡
	bool								bDisable_usb_sxt_usb1;
	bool								bDisable_usb_mkf_usb2;
	bool								bDisable_lb_out;     //喇叭 音频输出
	bool								bDisable_usb_key_usb3;
	bool								bDisable_network;

}										HkPortStatus;

//
int getHkPortStatus(LPCTSTR  fileName, HkPortStatus* p);
int saveHkPortStatus(HkPortStatus* p, LPCTSTR  fileName);

//
int get_default_ucHardwareAccl();

//
bool  bSupported_aiResize();



//
class  CCtxQmc:public  CCtxQmcTmpl
{
public:
	CCtxQmc(  );
	virtual  ~CCtxQmc(  );

	///////////////
	//typedef  struct  __mcVar_isCli_t								{
				 //MACRO_mcVar_common

				//
	char  _start;
	
	#if  1
			int  test1;
	#endif

				 //
				 QMC_cfg										cfg;
	
				 //
				 unsigned  int									uiDevType;													//  2007/08/03
				 //
				 unsigned  int									uiTerminalType;												//  
				 bool                                           bApplyFy;


				 //
				 QY_COMM_AUTHINFO_MIS							authInfo;

				 //
				 TCHAR											cspContainer_qmc[128];

				 //
				 unsigned  int									uiLastTranNo;

				 //
				 HANDLE											hThread_mgr;
				 DWORD											dwThreadId_mgr;
				 //
				 HANDLE											hThread_display;											//  2007/06/09		
				 DWORD											dwThreadId_display;
				 //
				 HANDLE											hThread_work;			
				 DWORD											dwThreadId_work;
				 //
				 HANDLE											hThread_scheduler;
				 DWORD											dwThreadId_scheduler;
				 //
				 HANDLE											hThread_robot;												//  2007/07/04
				 DWORD											dwThreadId_robot;
				 //
				 HANDLE											hThread_media;
				 DWORD											dwThreadId_media;
				 //
				 HANDLE											hThread_realTimeMedia;
				 DWORD											dwThreadId_realTimeMedia;
				 //  2016/12/26
				 HANDLE											hThread_rtOp;
				 DWORD											dwThreadId_rtOp;
				 
				 //
				 GENERIC_Q										mgrQ;														//  
				 //																											//  mgr
				 //																											//  
				 //
				 GENERIC_Q										displayQ;													//  
				 GENERIC_Q										workQ;														//  
				 GENERIC_Q										schedulerQ;													//  
				 GENERIC_Q										robotQ;	
				 QY_Q2											mediaQ2;
				 QY_Q2											realTimeMediaQ2;
				 QY_Q2											rtOpQ2;					//  2016/12/26

				 QY_Q2                                          icQ2;
				 
				 //  2015/12/04
				 ZONE_objs								*		pGZone_activeTalkers;
				 
				 //  2016/06/03
				 ZONE_objs								*		pGZone_d3dWalls;											//  2016/06/03

				 //
				 CMcSharedQ										processQ_media;												//  

				 #ifdef  __NOTSUPPORT_DB__
						 //GENERIC_Q								memTaskQ;													//  2010/04/22. 内存任务队列。当不使用数据库时，把任务存在内存里。
				 #endif

				 //
				 GENERIC_Q										imMsgLogQ;													//  2010/07/17
				
				 //
				 PolicyAvParams							*		p_gAvParams;
				 void									*		pFuncs_for_isCliHelp;										//  2013/06/08

				 //  2016/09/05
				 //void									*		p_g_dbFuncs;
				 
				 //
				 unsigned  char									ucb_doInitRecordSound;										//  2010/08/03


				 //  av, 2008/03/18
				 struct											{

					 
					 //
					 struct										{
						 bool									bChannelReady;
						 DWORD									dwLastModifiedTickCnt;
						 //
						 int									iThreadsStatus;
					 }											talk, audio, video, robot, rtOp;
					 
					 //
					 struct										{

						 CAP_procInfo_video						videoCaptureProcInfo;										//  200903/18

						 //
						 QY_MESSENGER_ID						idInfo_curConference;										//  (idInfo)
						 unsigned  int							uiTaskType_curConference;									//  
						 //
						 CAP_procInfo_recordSound				recordSoundProcInfo;										//  2009/02/11

						 //  
						 QY_PLAYER								player;

						 //  2014/04/07
						 HWND									hWnd_selectAvCompressor;

						 //
						 DWORD dwLastTickCnt_aCap_unused;
						 DWORD dwLastTickCnt_vCap;

						 //
						 struct {
							 int								mTimes_lostVideo;
							 //
							 int								mTimes_noCamera;
							 //
							 bool								bNeedRestart_noCamera;
						 }										chkCamera;

					 }											localAv;


					 //  
					 unsigned  short							usCnt_players;
					 QY_PLAYER							*		pPlayers;

					 //
					 Mix_procInfo								mixProcInfo;

					 //
					 QMC_aec_info								aecInfo;


					 //
					 int										sizeof_mySaveAvProcInfo;		//  自定义的saveProcInfo的大小
					 unsigned  short							usCnt_saveAvProcInfos;
					 void								*		pSaveAvProcInfos;


					 //
					 struct										{
						 //
						 CONF_req								confReq;
						 //
						 bool									bStartToQuitApp;
						 //
					 }											doConf;

					 //
					 struct {
						 int									iHkStatus;

						 //
						 HkPortStatus							portStatus;
						 //
					 }											hk;


					 //
					 struct {

							 //
							 TCHAR								login_termialName[128];
							 TCHAR								login_userName[128];

							//
							 TCHAR								rcDesc[256];

							 //
							 myZONE								peerZone, otherZone;
							 //myZONE									meZone;				//  2017/09/26

							 //
							 struct {
								 //
								 TCHAR							title[128];
								 //
								 unsigned  char					ucMbFlg;

								 //
								 int							iHkStatus_local;			 

								 //
								 struct {
									 //
									 AV_TRAN_INFO				tranInfo;
									 QY_MESSENGER_ID			idInfo_imGrp_related;
									 QY_MESSENGER_ID			idInfo_starter;
									 //
								 }								localAv;

							 }									taskInfo;

					 }											confLayout;

					 //
					 struct										{
						 bool									bEnableToSpeak;
						 //
						 QY_MESSENGER_ID						idInfo_grp;
						 
						 //
						 struct {
							 bool								bEnableToSnd;
							 QY_MESSENGER_ID					idInfo_grp;
						 }										fl;					//  辅流

						 //
					 }											speakState;

					 //
					 struct {
						 QY_MESSENGER_ID						idInfo_peer;
						 DWORD									dwTickCnt_last;
					 }											talk_doAv_info;

					 //
					 struct {
						 int									adapterLuid_LowPart;
						 int									adapterLuid_HighPart;
					 }											gpu;

					 //
					 struct {
						 //
						 DWORD									dwLastTickCnt_avReply;
						 //
					 }											acceptTaskAv;

					 //
					 bool										bNeedStartChannel_a;
					 bool										bNeedStartChannel_v;
					 bool										bNeedStartChannel_f;

					 //
				 }												av;
				 
				 //
				 CQmcPlayDevTmpl						*		pPlayDev;
				 					 
				 //
				 struct											{
					 //
					 BOOL										bNeedChkPlayers;					//  2018/06/16
					 //
					 bool										bNeedChkTasks;
					 //
				 }												ctrl;


				 //  gps  2012/05/07
				 struct											{

					 //  2012/05/07
					 unsigned  short							usCnt_players;
					 QY_PLAYER_gps						*		pPlayers;

				 }												gps;

				 
				 //	
				 CAP_procInfo_bmpU						*		pCapProcInfoBmps;
				 CAP_procInfo_audioU					*		pCapProcInfoAudios;

				 //  
				 void									*		pSharedObjSyncs;											//  2014/09/30

				 //  2015/11/10
				 void									*		pQmcObjVarInfos;											//  2015/11/10
				 //  2014/09/24
				 void									*		pQmcTaskInfos;


				 //
				 //  2015/07/01
				 unsigned  char									ucCnt_misCnts;
				 MIS_CNT								*		pMisCnts;

				 //  2011/04/05
				 struct											{
					 CUSTOMER_service_obj 						objs[1];
					 //
					 struct										{
						 QY_MESSENGER_ID						idInfo;						
						 TCHAR									talkerDesc[32];
					 }											called;
				 }												customerService;

				 //  2009/12/21
				 struct											{
					 unsigned  short							usMaxCnt_qmCmds;
					 unsigned  int								uiBufSize_qmShm;
					 //
					 HANDLE										hMap;
					 char	*  									pBuf;
				 }												cmdsShm;



				 //
				 QIS_ptz_wnd									ptzWnd;
				 
				 //  2013/09/26
				 struct											{
					 HWND										hWnd_dlgImg;
				 }												chromaKey;

				 //  2013/03/09
				 struct											{					
					 HWND										hWnd_videoTagCfg;
					 //
					 SUBTITLES_cfg								webcam;
					 SUBTITLES_cfg								d3dWall;													//  d3dWall需要设置字体。先这么使用 . 2013/12/10
				 }												subtitles;

				 //
				 QisSharedTexInfos						*		m_pQisSharedTexInfos;

				 //
				 OfflineRes_var									offlineRes;

				 //
				 struct {
					 HWND										hWnd_2ndScreen;
					 //
				 }												dlg2ndScreen;
				 
				 //  2017/07/18
				 struct											{
					 TCHAR										unique_wndTitle_parent[64];			//  必须是独一无二的窗口题头。
					 //
					 BOOL										bGotMsg_avConsole;
				 }												avConsole;

				 //  2017/07/26
				 struct											{
					 HWND										hWnd_cfgGrp;
				 }												cfgGrp;

				 //
				 //
				 struct {

					 DWORD										dwTickCnt_lastXtResp;

					 //
					 int										nTimes_waitForXtResp;

					 //
					 bool										bGotOnce_xtResp;			//  已经收到过一次

					 //
					 bool										bUsrLogined;				//  是否用户登录了
					 
					 
					 bool										bUsrUkeyed;				//  Ukey插拔状态
					 bool										bVideoDevOk;				//  摄像头插拔状态
					 bool										bAudioDevOk;				//  音频插拔状态
					 bool										bSpeak;				



					 //
					 bool										bNeedRestart_noXtResp;

					 //
					 bool										bNeedRestart_mjChanged;

					 //
					 bool										bErr_leaveConf;

				 }												xt;
				 //


				 //
				 HWND											hWnd_shareDynBmps;											//  2009/08/13								
				 //
				 unsigned  char									ucbAutoHideOnStartup;
				 unsigned  char									ucbAutoOpenChked;											//  2017/06/10


				 //
				 //  HWND											hFrame_sharedDynBmpList;									//  2009/09/03
				 DWORD											dwTickCnt_toRetrieveSharedDynBmps;
				 //BOOL											bInited_mcProcResp_retrieveDynBmps;							//  2011/10/31
				 time_t											tLastRefreshedTime_misServ_sharedDynBmps;
				 //
				 HWND											hWnd_notification;											//  2010/08/24

				 //
				 HWND											hWnd_imObjView;												//  2017/01/04

				 //
				 HWND											g_hVWall;													//  2012/04/02
				 int											iWndContentType_g_hVWall;									//  2013/07/11

				 //  2018/10/28
				 HWND											hWall_hzj;													//  2018/10/28
				 struct											{
					 QY_MESSENGER_ID							idInfo_tmpGrp;
					 BOOL										bConfStarted;
				 }												hzj;

				 //
				 IpcProc										m_ipcProc;

				 //
				 HWND											hWnd_status_realTimeImTaskList;								//  2013/02/06
				 HWND											hWnd_status_taskInfoList;									//  2014/09/25
				 HWND											hWnd_status_sharingObjectList;								
				 HWND											hWnd_status_playerList;
				 HWND											hWnd_status_wallList;
				 HWND											hWnd_status_ipCamList;										//  2016/07/30
				 HWND											hWnd_status_imNetStatList;
				 HWND											hWnd_status_talkerList;
				 HWND											hWnd_status_messengerStatusList;
				 HWND											hWnd_status_qList;											//  2011/01/20
				 HWND											hWnd_status_myDb;											//  2013/02/22
				 HWND											hWnd_status_unprocedImTaskList;								//  2013/02/17
				 HWND											hWnd_status_currentImTaskList;								//  2013/02/17
				 HWND											hWnd_status_imObjList;										//  2014/04/17
				 HWND											hWnd_status_regInfoList;									//  2014/04/17
				 HWND											hWnd_status_imGrpList;										//  2014/04/17
				 HWND											hWnd_status_imGrpMemList;									//  2014/04/17
				 HWND											hWnd_status_imObjRuleList;									//  2014/04/17
				 HWND											hWnd_status_dynBmpList;										//  2014/04/18


				 //  2015/01/21
				 QMC_status										status;


				 //  2010/12/29
				 struct											{
					 int										nStep_progress;
					 //
					 long										lLastTn_pktNo;	//  2012/11/10

				 }												debugInfo;

				 //
				 struct {
					 bool										bLegal;
					 bool										isOk;
					 int										nTimes_last;
					 bool										bLog;
					
				 }												legal_info;    //入会校验

				 //
				 bool											m_bUseKeyToLogin_forQmcGui;

				 //
				 int											iDefault_ucHardwareAccl;

				 bool                                           m_bHikRecvOk;


				 //
		#if  1
				 int  test2;
		#endif
			
		char  _bEnd;

//}		 MC_VAR_isCli;

		//virtual  BOOL  isQmCmd(  );

		virtual  RW_lock_param  *  get_qyMc_rwLockParam(  );
		virtual  TCHAR  *  get_appObjPrefix(  );

		virtual  void  *  get_qmc_cfg(  );

		virtual  QNM_CUSRES_INFO  *  get_qyMc_cusRes(  );

		//
		virtual  QMC_status  *  get_qmc_status(  );
		virtual  QMC_debugStatusInfo  *  get_qmc_debugStatusInfo(  );

		//
		virtual QY_sharedObj_sync  *  getSharedObjSyncByIndex(  int  index  );
		//virtual QY_SHARED_OBJ  *  getSharedObjByIndex(  int  index  );
		virtual  CAP_procInfo_bmpU  *  getCapBmpBySth(  int  index,  unsigned  int  uiCapType  );
		virtual  CAP_procInfo_audioU  *  getCapAudioBySth(  int  index,  unsigned  int  uiCapType  );

		//
		virtual  void  *  get_QM_SHM_CMDS(  );
		virtual   int  newShmCmdIndex(  int  iIndex_sharedObj  );
		virtual  void  *  getQmShmCmdByIndex(  int  iIndex  );
		
		//  2016/03/15
		virtual void  *  getQmcTaskInfoByIndex(  int  index  );
		virtual int getQmcTaskInfoIndexBySth(int iTaskId);

		
		//
		virtual  void  *  get_g_guiData(  );
		
		//
		virtual  int  getAuthType(  );

		//  2015/10/14
		virtual  unsigned  char  get_ucCnt_misCnts(  );
		//
		virtual MIS_CNT  *  getMisCntByName(  LPCTSTR  misServName  );
		virtual MIS_CNT  *  getMisCntByIndex(  int  iIndex  );

		virtual  HWND  get_hMainWnd(  );

		virtual  void  *  getPolicyAvParams(  );

		//  2015/10/30
		virtual  void  *  get_pFuncs_for_isCliHelp(  );

		//
		virtual  void  *  getCusModules(  );

		//
		virtual int  loadCusModules(void* pQyMcParam) = mynull;
		virtual int  unloadCusModules(void* pQyMcParam) = mynull;
		//
		virtual int  initCusModules(void* pQyMcParam) = mynull;
		virtual int  startCusModules(void* pQyMcParam) = mynull;
		virtual int  stopCusModules(void* pQyMcParam) = mynull;



		//
		virtual  BOOL  bSupported_dvt(  unsigned  int  uiModuleType_toDec  );
		//  2015/10/11
		virtual  BOOL  bSupported_evt(  unsigned  int  uiModuleType_toEnc  );

		//  2017/10/11
		virtual  BOOL  bUse_imObjView_as_guiWnd(  );
		virtual  BOOL  bSupport_sharedTex();



		//
		virtual  BOOL  b_qyMc_quit(  );

		//
		virtual Ctx_sm* getCtxSm() {
			return  nullptr;
		}

		//
		virtual int getSmCfgInfo(TCHAR* cfgDirName, int cfgDirNameLen) = NULL;

		//
		virtual  int  initVar_post(void* p0, void* p1, void* p2) = mynull;
		virtual  int  exitVar_pre(void* p0, void* p1, void* p2) = mynull;
		virtual  int  exitVar_post(void* p0, void* p1, void* p2)=mynull;



		//  2016/09/27
		virtual  int  qyShowMainWndFunc(  HWND  hMainWnd,  void  *  pVar,  BOOL  bShow  )  =  NULL;
 
 

		//  2015/10/14
		virtual  QY_Q2  *  get_realTimeMediaQ2(  );
		virtual  QY_Q2  *  get_mediaQ2(  );


		

		//
		virtual  BOOL  bWebcamUsing(  unsigned  int  uiCamCapType,  void  *  pMoniker_v,  LPCTSTR  camName,  int  *  piIndex_capBmp,  int  *  piIndex_sharedObj  );
		virtual  BOOL  bMediaTaskExists(  int  iTaskId  );

		//
		virtual  BOOL  bAudioChannelReady(  );
		virtual  BOOL  bVideoChannelReady(  );

		//
		virtual  int  toShareVideo_post(  unsigned  int  uiCapType,  int  iIndex_capProcInfo,  myDRAW_VIDEO_DATA  *  pkts,  unsigned  int  nPkts,  COMPRESS_VIDEO  *  pCompressVideo,  QY_SHARED_OBJ  *  pSharedObj,  MIS_MSGU  *  pMsgBuf  );

		//
		virtual  int  drawLocalVideoData(  unsigned  int  uiTranNo,  myDRAW_VIDEO_DATA	*	pkts,  int  pktsLen,  BOOL  *  pbPktsRedirected,  unsigned  int  uiCapType,  int  iIndex_capBmp,  int  iTaskId,  void  *  pMIS_CNT,  QY_MESSENGER_ID  *  pIdInfo_peer  );
		virtual  int  drawVideoData(  myDRAW_VIDEO_DATA  *  pkts,  int  pktsLen,  BOOL  *  pbPktsRedirected,  void  *  pQY_TRANSFORM  );
		//
		virtual  int  playLocalAudioData(  int  iTaskId,  unsigned  int  uiTranNo,  WAVEFORMATEX  *  pWf,  myPLAY_AUDIO_DATA  *  pPkt,  int  pktLen,  BOOL  *  pbPktRedirected,  unsigned  int  uiCapType,  int  iIndex_capAudio  );
		virtual  int  playAudioData(  int  iSampleTimeInMs,  unsigned  int  uiPts,  BYTE  *  pInput,  unsigned  int  inputLen,  int  iIndex_player  );


		//  2015/10/14
		virtual  void  *  get_cur_SUBTITLES_cfg(  int  iSharedObjType,  int  iCapType,  int  iCapSubType  );
		//
		virtual  int resizeRgb24(  unsigned  char  *  src,  int  srcWidth,  int  srcHeight,  unsigned  char  *  dst,  int  dstWidth,  int  dstHeight  );


		//
		virtual  int  showNotification(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  LPCTSTR  hint  );

		//
		virtual  int  qisChkTasks_gui(  );			//  2009/09/10
		//virtual  int  removeInvalidTasks(  unsigned  int  uiChannelType  );			//  2009/09/10

		//
		virtual  int  get_deced_pktResType(  unsigned  int  uiModuleType,  int  iFourcc,  unsigned  short  *  pusPktResType_o  );				//  2015/10/04
		virtual  int  get_pktResType_toEnc(  unsigned  short  usPktResType_src,  unsigned  int  uiModuleType,  int  iFourcc,  unsigned  short  *  pusPktResType_i  );				//  2015/10/04


		//
		virtual void  *  get_pf_DXUTSaveTextureToFile(  );

		//  2016/02/12
		virtual  int  set_enlarged_gZone(  HWND  hWnd  );

		//
		virtual int  initCompressVideo(  BITMAPINFO  *  pBmpInfo_input,  unsigned  int  uiCapType,  VIDEO_COMPRESSOR_CFG  *  pCompressor,  BOOL  bCapDev,  unsigned  int  uiBufSize_pData,  COMPRESS_VIDEO  *  pCompressVideo  );
		virtual int  exitCompressVideo(  BOOL  bCapDev,  COMPRESS_VIDEO  *  pCompressVideo  );
				
		//
		virtual int  set_qoi_funcs(  MY_qoi  *  pMyQoi  );
		
		//  2016/08/14
		virtual  int  postMsg2Mgr_mc(  void  *  pMIS_CNT,  MSG_ROUTE  *  pRoute,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  char  *  data,  unsigned  int  dataLen,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  uiChannelType,  MIS_MSGU  *  pMsgBuf,  BOOL  bLog  )  =  NULL;
		virtual  int  postMsgTask2Mgr_mc(  void  *  pMIS_CNT,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  int  iTaskId,  unsigned  int  uiTaskType,  char  *  data,  unsigned  int  dataLen,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_taskSender,  QY_MESSENGER_ID  *  pIdInfo_taskReceiver,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  uiChannelType,  MIS_MSGU  *  pMsgBuf,  BOOL  bLog  )  =  NULL;
		virtual  int  postImMsg2Log_isClient(  MIS_MSGU  *  pMsg,  int  lenInBytes_msg  )  =  NULL; 
		//
		virtual  int  recoverMessenger(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QY_MESSENGER_INFO  *  pObj,  QY_MESSENGER_REGINFO  *  pRegInfo,  time_t  tLastModifiedTime,  BOOL  bLog,  GENERIC_Q  *  pLogQ  )  =  NULL;
		virtual  int  recoverImObjRules(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRules_req	*	pReq,  time_t  tLastModifiedTime  )  =  NULL;
		virtual  int  recoverImGrp(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime,  BOOL  bNoGrpName  )  =  NULL;
		virtual  int  recoverImGrpMem(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime  )  =  NULL;
		
		//
		virtual  FUNCS_for_isCliHelp  *  FUNCS_for_isCliHelp_new(  )  =  NULL;
		virtual  void  FUNCS_for_isCliHelp_free(  void  **  ppFuncs  )  =  NULL;

		//  2015/07/13
		virtual  BOOL  bUse_FUNCS_for_isCliHelp(  );
		virtual  BOOL  bUse_sharedObj(  );
		virtual  int  initCapSubWnds1(  unsigned  short  usMaxCnt,  CAP_subWnds  *  p  );


		//  2015/08/04
		BOOL			bSupported_shadow_for_tmpMsgr(  );
			
		//////////////////////
		virtual  int  tryToTalkToMessenger_any(HWND hparent, unsigned  __int64  ui64Id, int  iTalkSubtype, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd) = NULL;// {  return  -1;  }
		virtual  int  talkToMessenger(  unsigned  __int64  ui64Id,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phWnd  )  {  return  -1;  }
		virtual  int  doApplyForPlayer(  HWND  hMainWnd,  MIS_MSGU  *  pMsg  )  {  return  -1;  }

		//
		virtual int  stopMosaicThreads(  QMC_mosaic_maker  *  pMosaic  ) {  return -1;}
		virtual int  setFlg_inConfMosaic(  HWND  hDlg,  int  iWndContentType,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr  ){return -1;}
		virtual int  makeMosaicStream(  HWND  hDlg,  int  iTaskId,  int  level,  AV_COMPRESSOR_CFG  *  pCompressor_conf,  AV_COMPRESSOR_CFG  *  pCompressor_resource,  int  iFourcc_resource,  QMC_mosaic_maker  *  pMosaic  ){return -1;}
		virtual int  openLocalVideo_mosaic(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiCamCapType,  BITMAPINFOHEADER  *  pBih_photomosaic,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressorParam,  int  iIndex_sharedObj  ) {  return -1;}

		//
		virtual int  confStarter_requestToSpeak(  HWND  hDlgTalk,  QY_MESSENGER_ID  *  pIdInfo,  AV_stream_simple  *  pAss,  LPCTSTR  talkerDesc,  BOOL  bRequestToSpeak  );
		//
		virtual int  waitToQuit_isCli(  int  dwTimeInMs,  LPCTSTR  hint  );


		//
		virtual int  talkToMessenger(void* pQyMcParam, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkUsage, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)=NULL;
		virtual void* tmp_getDlgTalkVar(HWND  hDlgTalk)=NULL;
		virtual int  getTalkerShadow(HWND  hParent, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkerSubType, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)=NULL;

		//
		virtual  int  do_talk_afterInit(HWND  hDlgTalk) = NULL;
		virtual  int  do_talk_refreshLayout(HWND  hDlgTalk) = NULL;
		virtual  int  do_addToRecentMsg(HWND  hDlgTalk, void* pDLG_TALK_var, long  lRowIndex, int  iTaskId, MIS_MSGU* pMsgU, MIS_MSG_taskStatus  *  pMsgTaskStatus,  QY_MESSENGER_ID idInfo_talker, LPCTSTR  talkerDesc, unsigned  short  usOp, int  iStatus, char* timeBuf, LPCTSTR  rowIdStr, LPCTSTR  content, BOOL  bFollowingRows, BOOL  bScrollIntoView, TCHAR* txtBuf, unsigned  int  uiTxtBufCnt) = NULL;
		virtual  int  do_talk_OnTimer(HWND  hDlgTalk,void *pDLG_TALK_var) = mynull;

		//
		virtual int do_talk_shareDevice(HWND  hDlgTalk, void  *  pDLG_TALK_var,  bool  bEnable, bool  bSaveSpeakState) = NULL;

		//
		virtual bool myDestroyWindow(HWND  hWnd)  =  NULL;

		//
		virtual int  getDirAndFinalName(LPCTSTR  svFileName, TCHAR* dirName, unsigned  int  size, TCHAR* finalName, unsigned  int  finalNameSize) = mynull;
		

		//
		virtual int do_test(HWND  hWnd,int iWndContentType) =NULL;

		//
		virtual bool bAppQt() = NULL;

		
		//
		virtual  int  do_logImMsg_isCli(void* pDb, int  iDbType, void  *pDBManager, IM_MSG_RCD* pRcd)  =  NULL;

		//
		virtual  int  viewDlgSelectAvCompressor(HWND  hParent, QY_MESSENGER_ID idInfo, unsigned  int  uiCapType, unsigned  int  uiSubCapType, int  iCapUsage, BOOL  b3D, unsigned  short  usConfType)  =  NULL;
		virtual void gui_notify_clearTask(int  iTaskId) = mynull;
		virtual void gui_notify_clear() = mynull;

		//
		virtual void* DBManager_new()=mynull;
		virtual void DBManager_free(void ** ppDBManager)=mynull;
		//
		virtual int initDBManager(void * pDBManager) = mynull;

		//
		virtual int  do_dlgTalk_procTask_transferAvInfo(HWND  hTalk)=mynull;

		//
		virtual int AEC_layout_chk(AEC_layout* pLayout)=mynull;

		//
		virtual int  do_mainWnd_OnTimer(HWND  hMainWnd, void* pVar, UINT  nIDEvent) = mynull;

		//
		virtual  int  displayRecentFriends(MIS_MSG_displayRecentFriends_qmc* pMsg) = mynull;

		//
		virtual  int  confKeyChanged(HWND  hDlgTalk) = mynull;

		//
		virtual int do_requestToSpeak(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_from) = mynull;		//  自己申请发言
		virtual int do_stopSpeaking(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_from) = mynull;			//  自己停止发言

		//
		virtual int do_permitToSpeak(HWND  hDlgTalk,QY_MESSENGER_ID  idInfo_from)=mynull;
		virtual int do_prohibitSpeaking(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_from) = mynull;
		//
		virtual int do_pleaseSpeak(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_from) = mynull;			//  主持人邀请发言
		virtual int do_pleaseStopSpeaking(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_from) = mynull;	//  主持人请停止发言


		//
		virtual int do_dlgTalk_proc_recvd_confCtrlState(HWND  hDlgTalk) = mynull;

		//
#ifdef  __DEBUG__
#endif
		//
		virtual int sxrz_yq(QIS_ca_req* p) = mynull; 	//  双向认证，客户端验签

		//
		virtual  bool  bNeedUsrLogin_sm() = mynull;

		//
		virtual int  closeDlg2ndScreen() {

			if (dlg2ndScreen.hWnd_2ndScreen)  ::SendMessageTimeout(dlg2ndScreen.hWnd_2ndScreen, WM_CLOSE, 0, 0, 0, 200, NULL);
			if (IsWindow(dlg2ndScreen.hWnd_2ndScreen)) {
				showInfo_open0(0, 0, _T("closeDlg2Screen failed, hWnd_2ndScreen exists"));
			}

			return 0;
		}

		//
		virtual int  showDlgSelectAvDev(HWND  hParent, void* pCapStuff, int  iMenuId_selected, BOOL* pbUnresizable)
		{
			return -1;
		}

		//
		virtual int  getChosenCamera(TCHAR* webcam_selected, unsigned  int  uiCnt_webcam_selected);

		//
		virtual bool  bUse_dx11();


		//
		virtual int reportToHg_meetingOn(unsigned  __int64  uiMeetingId_hg, int iMeetingType, unsigned  __int64  ui64Id_grp,  bool  bOn) = NULL;
		virtual int reportToHg_saveAv(unsigned  __int64  uiMeetingId_hg,  char* video_url,char*resource_url)=NULL;

		//
		virtual int chkDualSystemHotBackup() = NULL;

		//
		virtual unsigned  char  getMbFlg(int  iMeetingLevel) = NULL;

		
		//
		//virtual int do_afterLogonOk(HWND  hDlgQmcLogin, void* pDLG_mcClientLogon_var) = NULL;
		virtual int do_afterLogonOk() = NULL;

		//
		virtual int do_videoCurrInfo(HWND  hDlgTalk, void* pDlgTalkVar, void* pContent) { return  -1; }

		//
		virtual int  tmpHandler_showMsg_task(void* hDlgTalkParam, void* pDLG_TALK_var, void* p1, void* pMsgParam) = NULL;

		//
		virtual int  sendConfKey(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint);

		//
		virtual int  sendStatusConfLayoutParam(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint) { return -1; }

		//
		virtual BOOL  bSupported_emergencyCommand() = mynull;

		//
		virtual int dlgTalk_confStart_pre(HWND  hDlgTalk, bool bConf, bool conf_ucb100k, LPCTSTR  hint);
		virtual int dlgTalk_confStart_post(HWND  hDlgTalk, LPCTSTR  hint);


		//
		virtual   int  doCmd_startAvCall(HWND  hParent, HWND  hCurTalk, int  level, BOOL  b3D, unsigned  char  ucbAvConsole, PARAM_startAvCall* pParam) = NULL;



		//
};

//
typedef  class  CCtxQmc  MC_VAR_isCli;


//  2016/09/02
__declspec(  dllexport  )  FUNCS_for_isCliHelp  *  QY_GET_FUNCS_for_isCliHelp(  CCtxQmc  *  pProcInfo  );

//
//  2010/09/14
__declspec(  dllexport  )  QM_SHM_CMDS  *  QY_GET_shmCmds(  CCtxQmc  *  pProcInfo  );


//
//  2013/06/08
//#define  QY_GET_PolicyAvParams(  pProcInfo  )			(  PolicyAvParams  *  )(  (  pProcInfo  )->p_gAvParams  )


//
int  setSlaveStreamOn(  HWND  hMgr,  BOOL  bOn  );

//
int  displayNotification(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_taskStatus  *  pStatus  );

//
int  showDlgMcClientLogon(  HINSTANCE  g_hInst,  HWND  hMainWnd,  void  *  pQyMcParam,  PARAM_showDlgMcLogon  *  pParam  );
//
int  showDlgMcClientDevAuth(  HINSTANCE  g_hInst,  HWND  hMainWnd,  void  *  pQyMcParam,  PARAM_showDlgMcLogon  *  pParam  );

 //
int  confStarter_requestToSpeak(  HWND  hDlgTalk,  QY_MESSENGER_ID  *  pIdInfo,  AV_stream_simple  *  pAss,  LPCTSTR  talkerDesc,  BOOL  bRequestToSpeak  );

//
int  print_imObjs_isClient_myDb();

//
bool  bExists_activeTaskAv(QY_MC  *  pQyMc,  int* piTaskId_activeTaskAv, QY_MESSENGER_ID* pIdInfo_peer);
int chkAvStatus();

//
int  del_imGrp_isCli(QY_MC  *  pQyMc,  QY_MESSENGER_ID* pIdInfo_grp);

//
int isCli_addTo_qmObjQ(QY_MESSENGER_ID  idInfo);


//
//
int sendRespToHg(int respCode, short org_cmd, unsigned  __int64  meetingId,  Param_hg_cliReply  *  pCliReply  );
//

int reportToHg_speakOn(unsigned  __int64  ui64MeetingId_hg, unsigned  __int64  ui64Id_grp, bool  bOn);
int reportToHg_meetingOn(unsigned  __int64  ui64MeetingId_hg, int  iMeetingType,  unsigned  __int64  ui64Id_grp, bool  bOn);
//
int reportToHg_saveAv(unsigned  __int64  uiMeetingId_hg,  char* video_url, char* resource_url);

//
#define		CONST_intervalInS_xt			30
#define     ORG_FILE_SEND_LOGIC

//
int send_fy(int mainWnd_loopCtrl);
int send_xt(int mainWnd_loopCtrl);
//
int  startToRetrievePlans();
int  startToRetrieveP2pList();
int askforP2p(TCHAR* fromTermName, unsigned  __int64 grpId, TCHAR* termName, unsigned  __int64  peerId, int p2pLevel);
int askforP2p_do();
int legal_initiation(unsigned  __int64 grpId);


//
int qmcSendLogToHg(int logType, TCHAR* tLogDesc,char *timeBuf, bool bWarn);
int qmcLogForHg(int  logType, TCHAR* tLogDesc,bool bWarn);
int qmcChkSmTmpLogFile();
int qmcSendEndAvToHg(unsigned __int64 ui64Id_grp);



//
int initSavers(bool  bRecord_conf,bool  bRecord_trans,bool bLive,TCHAR  *  liveUrl, __int64 meetingId,  unsigned  __int64  peerId,int iTaskId);
int exitSavers();
SAVE_av_procInfo* getSaver(int index_saver);

//
int  initSaver(bool  bResource, time_t  t, unsigned  __int64 peerId,  int  iTaskId, int iSaverType,  int  index_trans, TCHAR  *  hint,  SAVE_av_procInfo* pSave);
int exitSaver(SAVE_av_procInfo* pSave);
int startSaver(SAVE_av_procInfo* pSave);
int stopSaver(SAVE_av_procInfo* pSave);








//
typedef  struct  __param_saveAv_t {

	//
	SAVE_av_pktU* pSaveAvPktU;

	//
	//int			index_saver;
	SAVE_av_procInfo* pSave;

	//
}  Param_saveAv;

//
int  postAvPktToSave(Param_saveAv* pParam, bool  bResource, int  index_activeMems_from, unsigned  __int64  ui64Id_from, unsigned  int  tn_openAvDev, unsigned  char  ucMediaType, int  iFourcc, unsigned  int  uiSampleTimeInMs, unsigned  int  uiPts, char* data, int  len);

__declspec(dllexport)  int  postAPktToSave(Param_saveAv* pParam, bool  bResource, int  index_activeMems_from, unsigned  __int64  ui64Id_from, unsigned  int  tn_openAvDev, unsigned  short  wFormatTag,  unsigned  int  uiSampleTimeInMs, unsigned  int  uiPts, char* audio, int  len);
__declspec(dllexport)  int  postVPktToSave(Param_saveAv* pParam, bool  bResource, int  index_activeMems_from, unsigned  __int64  ui64Id_from, unsigned  int  tn_openAvDev, int  iFourcc,  unsigned  int  uiSampleTimeInMs, unsigned  int  uiPts, char* video, int  len);


//
bool  bNeedMute();
bool  bNeedFakePic();
int get_iHkStatus();
bool  bNvr();


//
int  getFakePic(LPCTSTR  img_src, int bits, int iW, int iH, char* rgb_dst, int  rgbSize_dst);

//
int qmcChkDualSystemHotBackup();

//
unsigned  char  myGetMbFlg(int  iMeetingLevel);

//
int netflow_main();

int  doMisCntLogon(MIS_CNT* pMisCnt, MIS_CHANNEL* pChannel, HWND    hDlg, TCHAR* respHint, int  cntof_respHint);

//
extern  "C"  BOOL  bServConnected_mis(QY_ENV * pEnv, char* serverIp, unsigned  short  serverPort, void* pParam, int  serviceId, char* ver, QY_ENC_CTX * pCommEncCtx, __int64  i64StartTime_base,  SOCK_TIMEOUT * pTo);

//
void qmcLogoff();

//
__declspec(dllexport)  int  sendConfKey(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint);

//
__declspec(dllexport)  int  sendTaskInteractionResp(__int64  tStartTime_req, int  uiTranNo_req, __int64 tStartTime_org, int uiTranNo_org, unsigned  char  ucStep, __int64  grpId, __int64  toId);

__declspec(dllexport)  int  chkToForceKeyFrame(QY_TRANSFORM* pTransform);



//
#endif

