
#ifndef  __ctxQmcDvt_h__
#define  __ctxQmcDvt_h__

#include	"ctxQmcTmpl.h"
#include	"qmcCfg.h"
#include	"qmcCmdParams.h"
#include	"qmcStruct_defs.h"
#include	"wgcCapturePublic.h"
#include	"qisPipe_open.h"


//
class  CCtxQmcWt:public  CCtxQmcTmpl
{
public:
	CCtxQmcWt(  );
	virtual  ~CCtxQmcWt(  );

	//
	struct												{
		//

		//QMC_APP_PARAMS								cmdLine;
		
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
		CAP_procInfo_bmpU								capBmp;

		//
		struct											{
			TCHAR										evtName_syncQuit[32];				
			HANDLE										hEvent_syncQuit;
		}												cmdProc;
		
		//
		int												tn_rtspCliPipe;

		//
		QIS_pipe* pQisPipe;


		//
		QY_shm											dataShm;
		//
		BITMAPINFOHEADER								bih_org;

		//
		int  w_o;
		int  h_o;
		BITMAPINFOHEADER								bih_o;
		//
		char								*			pBuf_o;			

		//
		QMC_status										status;

		//
		struct											{
			
			//
			bool										cli_bShmOk;
		
			//
			DWORD										dwLastTickCnt_writeShm;

			//
			DWORD										dwLastTickCnt_recvResp;

		}												wtStatus;

		//  2016/04/26
		//void								*			pDynLib_isD3dFunc;

	}													m_var;

	//
	int  m_total_nPkts{};


	//
	WgcCapture											m_wgc;


	//
	virtual  RW_lock_param  *  get_qyMc_rwLockParam(  )  ;

	virtual  TCHAR  *  get_appObjPrefix(  );

	//
	virtual  void  *  get_qmc_cfg(  );

	virtual  QNM_CUSRES_INFO  *  get_qyMc_cusRes(  )  ;

	virtual  QMC_status  *  get_qmc_status(  )  ;

	//
	virtual  QMC_debugStatusInfo* get_qmc_debugStatusInfo();


	//
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

	virtual  int  initInfrared() {
		return  -1;
	}
	virtual  int  exitInfrared() {
		return  -1;
	}

	
	//
	virtual  BOOL  qyMc_bQuit(  )  ;

	//
	virtual  BOOL  bWebcamUsing(  unsigned  int  uiCamCapType,  void  *  pMoniker_v,  LPCTSTR  camName,  int  *  piIndex_capBmp,  int  *  piIndex_sharedObj  );
	virtual  BOOL  bMediaTaskExists(  int  iTaskId  );
	
	//
	//
	virtual  BOOL  bAudioChannelReady(  );
	virtual  BOOL  bVideoChannelReady(  );

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
	//
	virtual  int  get_deced_pktResType(  unsigned  int  uiModuleType,  int  iFourcc,  unsigned  short  *  pusPktResType_o  );				//  2015/10/04
	virtual  int  get_pktResType_toEnc(  unsigned  short  usPktResType_src,  unsigned  int  uiModuleType,  int  iFourcc,  unsigned  short  *  pusPktResType_i  );				//  2015/10/04


	//
	//
	virtual int  set_qoi_funcs(  MY_qoi  *  pMyQoi  );

	//
	virtual  int  initForWriteFrame(int iFmt, int w_org, int h_org, Param_initForWriteFrame* pParam);
	virtual  int  exitForWriteFrame();
	virtual  int  procWgsCaptureFrame(int  iFmt, unsigned  char* data, int  w, int  h,Param_procWgsCaptureFrame  *  pParam) override;



};


#endif


