
#ifndef  __ctxQmcEvt_h__
#define  __ctxQmcEvt_h__

#include	"ctxQmcTmpl.h"
#include	"qmcCfg.h"
//
#include	"qyGuiCommProc.h"
#include	"qmcCommFunc_mis.h"
#include	"qmcCmdParams.h"
#include	"qmcStruct_defs.h"

//
//  2015/01/31
typedef  struct  __evt_encV_t									{
				 //
				 QY_shm											dataShm;

				 //
				 struct											{
					 	 TCHAR									evtName_syncR[32];				
						 HANDLE									hEvent_syncR;

						 //
					 	 TCHAR									evtName_syncW[32];				
						 HANDLE									hEvent_syncW;


						 //
						 HANDLE									hThread;
						 DWORD									dwThreadId;

				 }												readShm;
				 
				 //
				 struct											{
					 BOOL										bStopped_threadReadShm;

				 }												status;

				 //
				 BOOL											bQuit;

}		 EVT_encV;



extern  "C"  DWORD WINAPI mcThreadProc_readShm_evt( LPVOID lpParameter );



//
class  CCtxQmcEvt:public  CCtxQmcTmpl
{
public:
	CCtxQmcEvt(  );
	virtual  ~CCtxQmcEvt(  );

	struct												{
		//

		QMC_APP_PARAMS									cmdLine;
		//
		struct											{
			RW_lock_param								rwLockParam;		

		}												qyMc_cfg;
		//
		QMC_cfg											cfg;

		//
		PolicyAvParams						*			p_gAvParams;
		//
		QY_sharedObj_sync								sharedObjSync;
		//
		CAP_procInfo_bmpCommon							capBmp;

		//
		RTSP_cli_common  *								pRtspCli;

		//  2015/10/17
		int												iIndex_sharedObj;


		//
		EVT_encV										evt;

		//  2015/10/15
		MIS_CNT											misCnt;

		//
		struct											{
			TCHAR										evtName_syncQuit[32];				
			HANDLE										hEvent_syncQuit;
		}												cmdProc;
		
		//
		QMC_status										status;
		
		//
		struct											{
			DWORD										dwLastTickCnt_readShm;
		}												evtStatus;

		//  2016/05/02
		void  *											pDynLib_isD3dFunc;

	}													m_var;

	//
	virtual  BOOL									bCtxQuit(  );
	
	//
	virtual  RW_lock_param  *  get_qyMc_rwLockParam(  )  ;

	virtual  TCHAR  *  get_appObjPrefix(  );

	//
	virtual  void  *  get_qmc_cfg(  );

	virtual  QNM_CUSRES_INFO  *  get_qyMc_cusRes(  )  ;

	virtual  QMC_status  *  get_qmc_status(  )  ;

	virtual  QMC_cfg_debugStatusInfo  *  get_qmc_cfg_debugStatusInfo(  )  ;


	virtual QY_sharedObj_sync  *  getSharedObjSyncByIndex(  int  index  )  ;

	virtual  CAP_procInfo_bmpU  *  getCapBmpBySth(  int  index,  unsigned  int  uiCapType  )  ;

	virtual  CAP_procInfo_audioU  *  getCapAudioBySth(  int  index,  unsigned  int  uiCapType  )  ;

	//
	virtual   int  newShmCmdIndex(  int  iIndex_sharedObj  );
	virtual  void  *  getQmShmCmdByIndex(  int  iIndex  );



	//
	virtual MIS_CNT  *  getMisCntByName(  LPCTSTR  misServName  )  ;
	//
	virtual MIS_CNT  *  getMisCntByIndex(  int  iIndex  )  ;

	//
	virtual  HWND  get_hMainWnd(  )  ;


	//
	virtual  void  *  getPolicyAvParams(  )  ;

	virtual  void  *  getCusModules(  )  ;

	//
	virtual  int  setQmDbFuncs(  int  iDbType,  QM_dbFuncs  *  pDbFuncs  );

	
	//
	virtual  BOOL  b_qyMc_quit(  )  ;

	//
	virtual  BOOL  bWebcamUsing(  unsigned  int  uiCamCapType,  void  *  pMoniker_v,  LPCTSTR  camName,  int  *  piIndex_capBmp,  int  *  piIndex_sharedObj  );
	virtual  BOOL  bMediaTaskExists(  int  iTaskId  );
	
	//
	virtual  BOOL  bAudioChannelReady(  );
	virtual  BOOL  bVideoChannelReady(  );

	//
	virtual  int  toShareVideo_post(  unsigned  int  uiCapType,  int  iIndex_capProcInfo,  myDRAW_VIDEO_DATA  *  pkts,  unsigned  int  nPkts,  COMPRESS_VIDEO  *  pCompressVideo,  QY_SHARED_OBJ  *  pSharedObj,  MIS_MSGU  *  pMsgBuf  );

	//
	virtual  int  drawVideoData(  myDRAW_VIDEO_DATA  *  pkts,  int  pktsLen,  BOOL  *  pbPktsRedirected,  void  *  pQY_TRANSFORM  );
	//
	virtual  int  playAudioData(  int  iSampleTimeInMs,  unsigned  int  uiPts,  BYTE  *  pInput,  unsigned  int  inputLen,  int  iIndex_player  );

	//
	virtual  int  showNotification(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  LPCTSTR  hint  );

	virtual int  qisChkTasks_gui(  );			//  2009/09/10
	virtual int  applyForRemovingInvalidTasks(  unsigned  int  uiChannelType  );
	virtual int  removeInvalidTasks(  unsigned  int  uiChannelType  );			//  2009/09/10

	//
	//virtual  unsigned  short  get_pktResType_suggested(  int  pktUsage,  unsigned  int  uiModuleType  );
	virtual  int  get_deced_pktResType(  unsigned  int  uiModuleType,  int  iFourcc,  unsigned  short  *  pusPktResType_o  );				//  2015/10/04
	virtual  int  get_pktResType_toEnc(  unsigned  short  usPktResType_src,  unsigned  int  uiModuleType,  int  iFourcc,  unsigned  short  *  pusPktResType_i  );				//  2015/10/04
	
	//
	//  2017/10//09
	virtual void  *  get_pf_DXUTSaveTextureToFile(  );


	//
	virtual int  set_qoi_funcs(  MY_qoi  *  pMyQoi  );

	//
	virtual  BOOL  bGetLongProperty(  int  propId,  long  *  pVal  );
	//
	virtual  BOOL  bGetStrProperty(  int  propId,  TCHAR  *  tBuf,  int  tBufCnt  );

	
	//
	virtual int  initCompressVideo(  BITMAPINFO  *  pBmpInfo_input,  unsigned  int  uiCapType,  VIDEO_COMPRESSOR_CFG  *  pCompressor,  BOOL  bCapDev,  unsigned  int  uiBufSize_pData,  COMPRESS_VIDEO  *  pCompressVideo  );
	virtual  int  exitCompressVideo(  BOOL  bCapDev,  COMPRESS_VIDEO  *  pCompressVideo  );


	//
	int  initRtspCli(  );
	int  exitRtspCli(  );

	//
	int  initEvt(  );
	int  exitEvt(  );



};


#endif


