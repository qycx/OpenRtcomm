

#ifndef  __QYMCMAINCOMMON_H__
#define  __QYMCMAINCOMMON_H__	/* { */


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

#include	<tchar.h>
#include	<Wincrypt.h>
#include	<WinSock2.h>

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
#include	"qyWndContentType.h"

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


 

//  2015/07/07
#include	"ctxQyMc.h"



// 后台线程的数据结构
typedef  struct  __qyMcThreadDaemon_t						{
				 int										iEnvType;
				 void						*				pParentParam;		//  指向pQyMc

				 HANDLE										hMutex;
				 void						*				pDb;

				 
}		 QY_MC_THREADDAEMON;


//
typedef struct {
	BOOL	bCoInited;
}		StatusQmc;


//
#include	"qyCoInit.h"


#include	"qyMcMainMenu.h"
#include	"qyMcMainProc.h"
#include	"qyMcMainDb.h"
#include	"qyMcMainTemp.h"
#include	"qyMcAuth.h"



#include	"qnmTrayProc.h"
#include	"qnmMainProc.h"
#include	"qnmMainProc_mis.h"
//
#include	"qnmHotKeys.h"

#ifdef  __SUPPORT_HTMLEDIT__
	#ifdef  __DLL_isCliHelp__
			//#include	"qyCustSite.h"
			#include	"qyIdisImp.h"
			#include	"qyDropTarget.h"
	#endif
#endif


#include	"qyCusResPublic.h"
#include	"qnmResDefs.h"

//
#include	"tmpLib.h"


#ifdef  __isMgr__
		extern  CCtxQyMc  *  g_pQyMc;
#else	
	#ifdef  __DLL_isCliCore__
			extern  __declspec(  dllexport  )  CCtxQyMc  *  g_pQyMc;
			extern  __declspec(  dllexport  )  D3D_context* g_pD3dContext;
	#else
			extern  __declspec(  dllimport  )  CCtxQyMc  *  g_pQyMc;
			extern  __declspec(  dllimport  )  D3D_context* g_pD3dContext;
#endif
#endif

//
#if  1//  ndef  __qmdConn__
#define  QY_GET_GBUF( )			(  g_pQyMc  )
#endif



//  2010/01/06
#define  isIsCli(  pQyMc1  )	(  pQyMc1														\
									&&  pQyMc1->iServiceId  ==  CONST_qyServiceId_is			\
									&&  (  pQyMc1->iAppType  ==  CONST_qyAppType_client		\
										||  pQyMc1->iAppType  ==  CONST_qyAppType_client_ts	\
										)														\
									)

#define  isIsMgr(  pQyMc1  )	(  pQyMc1  &&  pQyMc1->iServiceId  ==  CONST_qyServiceId_is  &&  !isIsCli(  pQyMc1  )  )
#define  isIs(  pQyMc1  )		(  pQyMc1  &&  pQyMc1->iServiceId  ==  CONST_qyServiceId_is  )

//
//  #define	 isQmCmd(  )			(  g_pQyMc->appParams.ucbAv  ||  g_pQyMc->appParams.ucbMediaFile  )

//
#define  QY_GET_procInfo_isCli(  )	(  isIsCli(  g_pQyMc  )  ?  (  (  MC_VAR_isCli  *  )g_pQyMc->serviceGuiInfos[0].pVar  )  :  NULL  )
#define  QY_GET_procInfo_isMgr(  )	(  isIsMgr(  g_pQyMc  )  ?  (  (  MC_VAR_isMgr  *  )g_pQyMc->serviceGuiInfos[0].pVar  )  :  NULL  )

//
//  2016/09/07
//#define	 QY_GET_qmDbFuncs(  )						(  g_pQyMc  ?  g_pQyMc->p_g_dbFuncs  :  NULL  )



//  2013/03/10
#define		isIdcChked(  hDlg,  idc  )				( ::SendMessage(  ::GetDlgItem(  hDlg,  idc  ),  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )
#define		setIdcChked(  hDlg,  idc,  bChked  )	::SendMessage(  ::GetDlgItem(  hDlg,  idc  ),  BM_SETCHECK,  bChked  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );


//
int  letInScope(  QY_MC  *  pQyMc,  TCHAR  *  wherePart,  unsigned  int  cnt  );

BOOL  isMem512(  QY_MC  *  pQyMc  );
BOOL  bLikeXp(  );
//
BOOL  bLeWin7(  );
//
BOOL  bAppX64(  );
BOOL  isWinCe(  );
BOOL  b4Core(  );
BOOL  b2Core(  );

//  2012/11/09
#define	isLowCfg(  pQyMc  )	(  isMem512(  pQyMc  )  ||  bLikeXp(  )  )

//
//unsigned  short  qyGetAppAvLevel_qyMc(  QY_MC  *  pQyMc  );
//
int  qyGetSubSystemId_isCli( QY_MC  *  pQyMc  );
//
BOOL  bQmFreeVer(  QY_MC  *  pQyMc  );
//
BOOL  bSupported_vwRuleType_messenger(  QY_MC  *  pQyMc  );
BOOL  bSupported_avLevel(  QY_MC  *  pQyMc,  unsigned  int  uiCapType,  BITMAPINFO  *  pBmpInfo_input,  VIDEO_COMPRESSOR_CFG  *  pCompressor  );
BOOL  bSupported_remoteStorage(  QY_MC  *  pQyMc  );
BOOL  bSupported_fileServer(  QY_MC  *  pQyMc  );
BOOL  bSupported_gps(  QY_MC  *  pQyMc  );



//
int  getMenuStatus_frame(  QY_MC  *  pQyMc,  void  *  p0,  void  *  p1,  void  *  piStatusParam  );

#if  (  defined  __APP_qyMc_touchscreen__  ||  defined  __APP_qyMc_ts_noMfc__  ) 
		void  *  getZoneObjsInfo_ts(  HWND  hDlgWalls,  int  iWndContentType  );
#endif

//
int  getRect_talkers_ts(  HWND  hDlgWalls,  RECT  *  pRc  );


//
BOOL  bProcessOsUsrAdmin(  );


#ifndef  ASSERT
	#define	ASSERT(  x  )	MACRO_qyAssert(  x,  _T(  ""  )  )
#endif
#ifndef  _ASSERT
	#define	_ASSERT(  x  )	MACRO_qyAssert(  x,  _T(  ""  )  )
#endif


//
BOOL  b_tttbbbMac(  QY_MC  *  pQyMc  );


//
__declspec(  dllexport  )  int  getRole_byIdInfo(  QY_MESSENGER_ID  *  pIdInfo,  int  *  piRole  );



#endif /* } */

