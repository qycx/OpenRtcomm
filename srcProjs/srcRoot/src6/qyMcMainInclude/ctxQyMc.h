
#ifndef  __ctxQyMc_h__
#define  __ctxQyMc_h__	//  {

//

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

//
#include	"qyCommon.h"
//
#include	"ctxQyTmpl.h"

//  2013/11/26
#include	"mydbg.h"

//
#include	"qmCommon.h"
//  2014/11/27
#include	"qmShellPublic.h"


#ifndef  __WINCE__
	#include	"qyDbCommon.h"
#endif


#include	"qyCommCommon.h"


#include	"qyGuiCommonEx.h"


#include	"qyGuiCommProc.h"

#include	"qnmDb.h"
#include	"qnmGuiCommProc.h"
#include	"qySnmpCommProc.h"
#include	"qnmCustomGui.h"
#include	"qnmCustomSearch.h"

#include	"avCapHelpCommProc.h"

#include	"qmUiFunc.h"

#include	"qmCrypt.h"

#include	"qmcCommFunc_netMc.h"
//#include	"qmcCommFunc_mis.h"



#include	"qyOpenGuiCommon.h"

#include	"qyMcMainDefs.h"
#include	"qyMcDlgBarCfg.h"

#include	"qyMcMainObj.h"

#include	"qyMcMainCusModule.h"
#include	"qyMcMainExtModule.h"

#include	"qyMcInputMgr.h"

#include	"qmcCmdParams.h"

//
//
#include	"qmStruct_defs.h"

//
#include	"ctxQyMcTmpl.h"
#include	"saveAvProcDefs_open.h"


//
#ifndef  __WINCE__
		 #define  CONST_procedObjDbs						8		//  64
#else
		 #define  CONST_procedObjDbs						1
#endif

//
//
class  CCtxQyMc: public  CCtxQyMcTmpl
{
public:
	CCtxQyMc(  );
	virtual  ~CCtxQyMc(  );

	//
	// 
//typedef  struct  __qyMc_t									{

					 //
				 struct		{
					 
					 RnDataRedirect_qyMcInfo		*		m_pParent_rnDataRedirect_qyMcInfo;

				 }			m_var;

				//
	char  _start;
	
	#if  1
			int  test1;
	#endif


				 MACRO_qyAppCommonMems

				 QY_ENV										env;							//  2005/11/03
				 unsigned  int								uiTotalPhys_memStatus;			//  2008/10/08

				 //
				 bool										bUse_msdk;						//  use vpl when false. else use msdk
				 //
				 bool										bUse_videoCodecSdk11_1_5;		//  

				 //  2017/02/16
#define		CONST_aPlayType_null			0
#define		CONST_aPlayType_wave			1
#define		CONST_aPlayType_dSound			2
#define		CONST_aPlayType_webRtc			3
//
#define		CONST_vPlayType_v				100

				 //
				 bool										b__USE_webrtc1__;

				 //  2017/02/16
				 unsigned  int								uiAPlayType;
				 unsigned  int								uiAPlayType_16kMono16;

				 //
				 HINSTANCE									g_hInst;						//  2010/07/14

				 //
				 QMC_APP_PARAMS								appParams;
				 unsigned  char								ucbApp_ts;						//  2013/06/13

				 //
#ifdef  __DEBUG__
				 unsigned  char								ucbUseNamedShm;					// 
				 unsigned  char								ucbDebugSeparately;				//  2009/12/22
#endif

				 QY_MC_CFG									cfg;
				 
				 unsigned  char								ucbDynLibInited;				//  2007/01/21
				 //  unsigned  char								ucbOsUsrAdmin;					//  2008/11/15

				 QY_ENC_CTX									encCtx,  commEncCtx;  
				 unsigned  char								ucbEncInited;
				 //
				 QY_LICENSE_CTX								licenseCtx;
				 //
				 QNM_CUSRES_INFO							cusRes;							//  2005/11/03
				 unsigned  char								ucbResInited;


				 //
				 QY_DMITEM						*			pQnmEventTypeTable0;
				 QY_DMITEM						*			pQnmEventTypeTable_pc;
				 QY_DMITEM						*			pQnmEventTypeTable_op;
				 QY_DMITEM						*			pQnmEventTypeTable_netDev;
					 
				 //
				 QY_MC_GUI									gui;

				 //  
				 QY_OBJ_DB									procedObjDbs[CONST_procedObjDbs];				//  2006/12/17
				 //
				 int										iDsnIndex_mainSys;								//  procedObjs Index

				 //  

				 BOOL										bLogon;
				 DWORD										dwTickCnt_logon;				//  2013/04/06
				 QYMC_USR									curUsrInfo;
				 //  TCHAR									appObjPrefix[16  +  1];			//  2010/03/10
				 BOOL										bQnmLicenseTimeout;				//  2010/03/22
					 
				 //
				 BOOL										bQuit;
				 BOOL										bGuiQuit;						//  2008/10/03
				 unsigned  short							usTimes_tryToQuit;
				 //
				 BOOL										bAskingToQuit;					//  2011/03/18
				 BOOL										bQuitVerified;					//  2011/03/16
				 //
				 BOOL										bPrepareToGuiQuit;				//  2016/03/28

				 //
				 BOOL										bScheduler_dontWork;			//

				 //
#if  0
				 HANDLE										hSema_syncCusModules;			//  
#else			
				 CMutexRW								*	pRw_syncCusModules;
#endif
				 //
				 QIS_guiOpen								guiOpen;
				 QY_GUI_OPEN_vDev							guiOpen_vDev;					//  2008/01/01
				 QIS_guiOpen_saveAv							guiOpen_saveAv;

				 //  
				 CUS_MODULES								cusModules;						//  2007/12/30
				 BOOL										bCusModulesLoaded;

				 //  
				 QY_SERVICEGUI_INFO							serviceGuiInfos[CONST_maxServiceGuis];

				 HANDLE										hDaemonThreads[QY_MC_TOTAL_DAEMON_THREADS];
				 QY_THREADPROC								threadProcs[QY_MC_TOTAL_DAEMON_THREADS];

				 //  2008/11/25
				 QM_INPUT_MGR								inputMgr;
				 BOOL										bInputMgrInited;

				 //  
				 void								*		pQisWallsCfg;												//  2013/07/11
				 void								*		pGBuf_d3d;													//  2013/07/03

				 //  2013/07/31
				 void								*		pShowInfoStruct;
				 
				 //
				 QM_dbFuncs							*		p_g_dbFuncs;												//  2016/09/04

				 //  2009/10/11
				 unsigned  char								ucbDaemonDemo;
				 unsigned  short							usMaxVideoConferenceMems;
				 unsigned  char								ucDays_left;												//  2010/03/22
				 //
				 //unsigned  short							usAppAvLevel_default;										//  2013/06/28
				 //unsigned  short							usAppAvLevel_daemon;										//  2011/10/22
				 //
				 unsigned  short							usSubSystemId_daemon;										//  2017/06/21

				 //
				 unsigned  char								ucbSupported_remoteStorage_default;							//  2014/08/03
				 unsigned  char								ucbSupported_fileServer_default;							//  2015/08/04

				 //
				 unsigned  char								ucbSupported_gps_default;									//  2013/06/28

				 //
				 unsigned  char								ucb_tttbbbMac;												//  2016/05/21
				 //
				 unsigned  int								uiMaxTimeInS_videoConference;								//  2011/08/01
				 unsigned  int								uiMaxWarningInS_videoConference;							//  2013/08/20
				 
				 //
				 unsigned  int								uiMaxTimeInS_videoConference_general;						//  2011/08/01
				 unsigned  int								uiMaxTimeInS_videoConference_freeVer;						//  2011/08/01
				 

				 //  2015/07/09. pInfo->cfg.pfNewVar(  pQM,  pInfo,  0  )  
				 PF_commonHandler							pfNewVar;													//  2015/01/20
				 PF_commonHandler							pfFreeVar;
				 BOOL										bCalledByQmd;												//  2015/07/17

				 //
				 __int64									i64StartTime_base;

				 //
				 struct										{
					 long									lTranNo_wallMem;											//  2016/01/05
					 //
					 long									lTranNo_player;												//  2016/02/18
					 //
				 }											globals;

				 //
				 struct										{
					 int									nTimes_notifyPanicToApp;
				 }											status_notifyPanicToApp;

				 //
				 struct {
					 DWORD									dwTickCnt_start;
					 DWORD									dwTickCnt_mainFrame_inited;
					 DWORD									dwTickCnt_dlgTalk_0_inited;
					 DWORD									dwTickCnt_dlgTalk_1_inited;
					 //
					 DWORD									dwTickCnt_bDone_retrieveAllImObjRules;
					 DWORD									dwTickCnt_after_initCMainFrameInfo;
					 DWORD									dwTickCnt_after_toContactList;
					 //
				 }											dbg;


				 //
		#if  1
				 int  test2;
		#endif
			
		char  _bEnd;

//}		QY_MC;

		//  2015/07/08

		//
		virtual  int  initQnmRes(  void  *  p0,  unsigned  short  usLangId,  int  iResId_sys  );
		virtual  void  exitQnmRes(  void  *  p0  );
		//
		virtual  int  addModuleMem_qnmRes(  int  iResId_sys  );
		//
		virtual  int   set_g_dbPool_isCliHelp(  void  *  pPool  );
		//
		virtual   BOOL  bChkQyMcEnv_mis(  );
		
		//  2015/10/14
		virtual  QY_SERVICEGUI_INFO	*	get_pSci(  );
		virtual  void  *  get_pProcInfo(  );
		
		//  2016/09/26
		virtual  int  setQmDbFuncs(  int  iDbType,  QM_dbFuncs  *  pDbFuncs  );

		//
		virtual  int  setModalWnd_func(  HWND  hDlg,  BOOL  bFileDialog  );

		//
		int  yv12ToRgb24( unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );
		int  rgb24ToYv12(  unsigned  char  *  rgb,  unsigned  char  *  yuv,  int  width,  int  height,  BOOL  bFlipImg  );
		//
		int  rgb24ToI420(  unsigned  char  *  rgb,  unsigned  char  *  yuv,  int  width,  int  height,  BOOL  bFlipImg  );



};





//
typedef  struct  __param_initQyMc_t		{
				 //  2015/07/09. pInfo->cfg.pfNewVar(  pQM,  pInfo,  0  )  
				 PF_commonHandler							pfNewVar;													//  2015/01/20
				 PF_commonHandler							pfFreeVar;
				 BOOL										bCalledByQmd;												//  2015/07/17
}		 PARAM_initQyMc;





//
#define		CONST_fileName_fx_ck	"qisChromaKey.fx"


//
//
__declspec(  dllexport  )  int	initQyMc(  HINSTANCE  g_hInst,  void  *  pPARAM_initQyMc,  QY_MC  *  pQyMc  );
__declspec(  dllexport  )  void	 exitQyMc(  QY_MC  *  pQyMc  );

//
 BOOL  bApp_ts(  QY_MC  *  pQyMc  );
 BOOL  bApp_ts_3d(  QY_MC  *  pQyMc  );
 //
 
 
 //
  int  testInMain(  QY_MC  *  pQyMc  );




#endif  //  }

