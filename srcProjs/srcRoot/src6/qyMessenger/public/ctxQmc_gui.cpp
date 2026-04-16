
#include	"stdafx.h"
#include	<stdio.h>
#include	<stddef.h>
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
//  #include	"myresource.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"

#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	<windows.h>
#include	<windef.h>
#include	<lmcons.h>
#ifndef  __WINCE__
	#include	<lmshare.h>
#endif
#include	<tlhelp32.h>
#include	<iphlpapi.h>

//  #include	"qwmDynFunc.h"

#include	"qmcCmdProc.h"

#include	"tmpCeLib.h"
#include	"qySqlFunc.h"
#include	"qyThread.h"
#include	"isCmdConst.h"
#include	"qyCusResTemp.h"
//
#include	"policyAvParams.h"


#include	"myDb.h"

#include	"isCliCorePublic.h"
#include	"isCliHelpPublic.h"
#include	"qyMessengerHelpPublic.h"
#include	"imgProcessPublic.h"
#include	"isCliD3dPublic.h"
#include	"qisWallsProc.h"
#include	"qmcObjVarPublic.h"
#include	"qmcTaskPublic.h"
#include	"qmcSharePublic.h"
#include	"dlgShareDynBmpsProc.h"
#include	"funcsForIsCliHelp.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliExPublic.h"
#include	"ctxMcThread.h"

//
#include	"qmcVideoTool.h"
#include	"ctxQmc_gui.h"
#include	"policyAvParams.h"
#include	"qyAvRecordPublic.h"
//#include	"qmcVideoCapture_isCli.h"
//#include	"qmcCommFunc_isCli.h"
#include	"qmcCmdProc.h"
#include	"qyMcMainWndProc.h"
#include	<shellapi.h>
#include	"resource.h"

#include	"smCommProc.h"
#include	"dlgtalkproc.h"
#include	"hgCommProc.h"
#include	"ipcProc.h"
#include	"ctxQmThread.h"

//
int  tmpHandler_showMsg_task_qmcCli(void* hDlgTalkParam, DLG_TALK_var& m_var, void* p1, void* pMsgParam);

//
extern  "C"  __declspec(dllexport)  int  parseCmdLine_qyMc(LPCTSTR  pCmdLine, QMC_APP_PARAMS * pParams)
{
	parseCmdLine_qmc_func(pCmdLine, pParams);

	//
	if (10) {
		pParams->bUse_forTest_mediaDivceAsScreen = true;
	}

	//
#ifdef  __DEBUG__
	
	//
	if (0) {
		pParams->bUse_forTest_fakePic = true;
		showInfo_open0(0, 0, _T("for test: bUse_forTest_fakePic set to true"));
	}
		//
#if  0
		pParams->bUse_decD3d_nv = true;
		showInfo_open0(0, 0, _T("for test: bUse_decD3d_nv set to true"));
#endif
		//
#if  0
		pParams->bUse_encD3d_nv = true;
		showInfo_open0(0, 0, _T("for test: bUse_encD3d_nv set to true"));
#endif

		//
		//pParams->ucHardwareAccl_forDbg  =  CONST_hdAccl_msdk_hardware;

		//
#if  0
		pParams->bUse_playDev_dummy = true;
#endif 


		//
#endif

	 //
	 return  0;
 }

 //
 int  doPre_createConsoleWall(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 return  0;
 }

 //
 //  2015/01/20
 int  newVar_isCli_gui(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 QY_MC					*	pQyMc				=	(  QY_MC  *  )p0;
	 QY_SERVICEGUI_INFO		*	pSci				=	(  QY_SERVICEGUI_INFO  *  )p1;

	 CCtxQmc  *  p  =  NULL;

	 p  =  new  CCtxQmc_gui;

	 if  (  !p  )  return  -1;

	 pSci->pVar  =  p;

	 return  0;
 }

 int  freeVar_isCli_gui(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 QY_MC					*	pQyMc				=	(  QY_MC  *  )p0;
	 QY_SERVICEGUI_INFO		*	pSci				=	(  QY_SERVICEGUI_INFO  *  )p1;

	 if  (  pSci->pVar  )  {
		 CCtxQmc  *  p  =  (  CCtxQmc  *  )pSci->pVar;
		 delete  p;
		 pSci->pVar  =  NULL;
	 }

	 return  0;
 }




//
CCtxQmc_gui::CCtxQmc_gui(  )
{
	//  2014/02/08
	this->m_iCtxType  =  CONST_ctxType_qmc;
	this->m_iCtxSubtype = CONST_ctxSubtype_qmcMfc;

	//
#ifdef  __DEBUG__
		this->test1  =  567;
		this->test2  =  901;
#endif

	//
	int  size  =  &this->_bEnd  -  &this->_start;
	memset(  &this->_start,  0,  size  );

	//
	memset(  &m_var,  0,  sizeof(  m_var  )  );

	//
#ifdef  __DEBUG__
	CCtxQyMc* pQyMc = g_pQyMc;
	_sntprintf(pQyMc->cfg.smTmpLogFile, mycountof(pQyMc->cfg.smTmpLogFile), _T("c:\\tttbbb\\smTmpLog.log"));

#endif

	// 
	if (0) {
		m_bUseKeyToLogin_forQmcGui = true;
		showInfo_open0(0, 0, _T("for test, m_bUseKeyToLogin set to true"));
	}

	//
	if (m_bUseKeyToLogin_forQmcGui) {
		//
		this->cfg.ucb_closeTalkIfNoConf = true;
	}


	//
	//getCfgValByName(CONST_cfgFileName_smCfg, )


}

CCtxQmc_gui::~CCtxQmc_gui(  )
{
	int  i  =  0;

}


//
 int  CCtxQmc_gui::setQmDbFuncs(  int  iDbType,  QM_dbFuncs  *  pDbFuncs  )  
 {  
	 return  ::setQmDbFuncs_qm(  iDbType,  pDbFuncs  );  
 }

 //
 int  qyMc_setQmDbFuncs(  int  iDbType,  QM_dbFuncs  *  pDbFuncs  )
 {
	 return  ::setQmDbFuncs_qm(  iDbType,  pDbFuncs  );
 }


 BOOL CALLBACK myEnumWindowsProc_singleInstance(  HWND hwnd,  LPARAM lParam  );


 __declspec(  dllexport  )  int  qyShowMainWndFunc_cli(  HWND  hMainWnd,  void  *  pVar,  BOOL  bShow  )
{
	int					iErr	=	-1;
	if  (  !pVar  )  return  -1;
	QY_MC_mainWndVar  &  var	=	*(  QY_MC_mainWndVar  *  )pVar;

	QY_MC			*	pQyMc	=	var.pQyMc;
	if  (  !pQyMc  )  return  -1;
	MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pQyMc->get_pProcInfo(  );
	if  (  !pProcInfo  )  return  -1;
	if  (  pProcInfo->m_iCtxType  !=  CONST_ctxType_qmc  )  return  -1;
	
	//
	int					i;
	#ifndef  __WINCE__
			 QY_REG		reg;
	#endif
	CQyString			lckCStr;

	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	//
	var.ucbVisible  =  TRUE;

	//
	pQyMc->cfg.ucbDsnless  =  pQyMc->cfg.pSysCfg->ucbDnsless;	//  2007/06/13, ¸Ä³ÉÎÞDSN·½Ê½À´Á¬½Ó
	if  (  !pQyMc->cfg.ucbDsnless  )  lstrcpyn(  pQyMc->cfg.defaultDbName,  pQyMc->cfg.pSysCfg->defaultDbName, mycountof(  pQyMc->cfg.defaultDbName  )  );


	//  2011/02/27
#ifndef  __WINCE__
	if  (  pQyMc->iSystemId  ==  CONST_qySystemId_messenger  &&  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {		//  2007/03/03, ÏÂÃæÎªqyMsgµÄÖ÷²Ù×÷½çÃæµÄÏÔÊ¾
		int		iCxScreen	=  0;
		int		iCyScreen	=	0;
		int		iX			=	0;
		int		iY			=	0;
		int		iWidth		=	250;	//  180;
		int		iHeight		=	500;
		
#if  0	//  def  __APP_qyMc_touchscreen__
		//  iWidth  =  210;		
		iWidth  =  280;
#endif

		iCxScreen  =  GetSystemMetrics(  SM_CXSCREEN  );		//  2005/08/19
		iCyScreen  =  GetSystemMetrics(  SM_CYSCREEN  );		//  2005/08/19
		if  (  !iCxScreen  ||  !iCyScreen  )  goto  errLabel;

		//
#ifndef  __APP_qyMc_touchscreen__
		iX  =  iCxScreen  -  iWidth  -  60;
		iY	=  (  iCyScreen  -  iHeight  )  /2  -  40;  
#else
		iWidth  =  iCxScreen  /  2;
		iHeight  =  iCyScreen  /  2;
		//
		iX  =  (  iCxScreen  -  iWidth  )  /  2;
		iY  =  (  iCyScreen  -  iHeight  )  /  2;
#endif
		
		::MoveWindow(  pQyMc->gui.hMainWnd,  iX,  iY,  iWidth,  iHeight,  0  );
	}
#endif

	//


	{
		  PARAM_showDlgMcLogon  param  =  {0};
		  
		  //	
		  if  (  !bQyMcLogon(  pQyMc,  showDlgMcClientLogon,  &param  )  )  goto  errLabel;

	}

	//
	if (pQyMc->iAppType == CONST_qyAppType_client) {

		if (!pQyMc->appParams.ucbNotNeedLocked) {	//  Release 2007/05/29
			//  
			if (pQyMc->cfg.singleInstanceStr[0]) {

#ifndef  __WINCE__
				lckCStr = CQyString(pQyMc->appParams.appObjPrefix) + CQyString(pQyMc->cfg.singleInstanceStr);
#else
				lckCStr = CQyString(CONST_mutexPrefix_mcClientLogon) + pQyMc->cfg.singleInstanceStr;
#endif
				pQyMc->gui.hMutex_singleInstance = CreateMutex(NULL, FALSE, lckCStr);
				if (!pQyMc->gui.hMutex_singleInstance) {
					traceLog(_T("singleInstance failed, null."));
					goto  errLabel;
				}
				if (GetLastError() == ERROR_ALREADY_EXISTS) {
					traceLog(_T("singleInstance failed, already exists."));

					COMMON_PARAM	commonParam;
					HWND	hPrevWnd = NULL;

					MACRO_makeCommonParam3(0, (void*)lckCStr.GetBuffer(), &hPrevWnd, commonParam);
					EnumWindows(myEnumWindowsProc_singleInstance, (LPARAM)&commonParam);

					if (IsWindow(hPrevWnd)) {
						//  if  (  IsIconic(  hPrevWnd  )  )  ShowWindow(  hPrevWnd,  SW_RESTORE  );
						ShowWindow(hPrevWnd, SW_SHOWNORMAL);

#if !defined(  __WINCE__  )  ||  defined(  __TEST__  )
						SetForegroundWindow(hPrevWnd);
						SetForegroundWindow(GetLastActivePopup(hPrevWnd));
#else
						SetForegroundWindow((HWND)(((ULONG)hPrevWnd) | 0x01));
#endif

					}

					goto  errLabel;
				}

				//
				if (!IsWindow(pQyMc->gui.hMainWnd))  goto  errLabel;
				if (!SetProp(pQyMc->gui.hMainWnd, lckCStr, (HANDLE)1))  goto  errLabel;
			}
			//  ¼ì²é½áÊø	 	 
		}

	}
		//
	



#ifndef  __WINCE__
	//  2007/12/31, ¸ù¾Ý×°ÔØÄ£¿éµÄÇé¿öÀ´¸Ä±ä²Ëµ¥¡£	
	if (pQyMc->iAppType == CONST_qyAppType_client) {
		if (pQyMc->gui.hMenuChildFrm)  cusModuleMenu(pQyMc, pQyMc->gui.hMenuChildFrm, CONST_resId_menu_modulesGuanLi_isClient);
		//  CMenu	*	pMenu;
		HMENU	hMenu;
		if (IsWindow(pQyMc->gui.hMainWnd)) {
			//  if  (  (  pMenu  =  pMainWnd->GetMenu(  )  )  )  cusModuleMenu(  pQyMc,  pMenu->m_hMenu,  CONST_resId_menu_modulesGuanLi_isClient  );
			hMenu = ::GetMenu(pQyMc->gui.hMainWnd);
			if (hMenu)  cusModuleMenu(pQyMc, hMenu, CONST_resId_menu_modulesGuanLi_isClient);
		}
	}
#endif


	//  2013/06/18
	int  app_m_nCmdShow  =  SW_NORMAL;
	//  2015/06/03
	if  (  !bShow  )  app_m_nCmdShow  =  SW_HIDE;


#ifdef  __WINCE__

		centerWnd(  pQyMc->gui.hMainWnd  );

#else

	if  (  pQyMc->iSystemId  ==  CONST_qySystemId_messenger  &&  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {		//  2007/03/03, ÏÂÃæÎªqyMsgµÄÖ÷²Ù×÷½çÃæµÄÏÔÊ¾
		
#ifdef  __useMfc__
		AfxGetApp(  )->m_nCmdShow  =  SW_NORMAL;
#endif

		{
			QY_SERVICEGUI_INFO		*		pSci				=	getServiceGuiInfo(  pQyMc,  pQyMc->iServiceId  );
			if  (  !pSci  )  goto  errLabel;
			MC_VAR_isCli				*		pProcInfo;
			if  (  !(  pProcInfo			=	(  MC_VAR_isCli  *  )pSci->pVar  )  )  goto  errLabel;
			int								i;

#ifdef  __useMfc__
			CWaitCursor						cur;
#endif

			for  (  i  =  0;  !pQyMc->bQuit  &&  i  <  60;  i  ++  )  {		//  ÕâÀïÊÇÎªÁËµÈ´ýmcThreadproc_mis³õÊ¼»¯Íê³É£¬2007/09/02
				 if  (  pProcInfo->status.ulbThreadProcInited  )  break;
				 Sleep(  500  );
			}
			if  (  !pProcInfo->status.ulbThreadProcInited  )  {
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Failed: ulbThreadProcInited is false"  )  );
				goto  errLabel; 
			}

		}


		//  2012/07/18
			 

	    //  2012/04/03
		#ifdef  __APP_qyMc__
				MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pQyMc->get_pProcInfo(  );
				if  (  !pProcInfo  )  goto  errLabel;
				if  (  pProcInfo->m_iCtxType  !=  CONST_ctxType_qmc  )  goto  errLabel;
				//
				if  (  pProcInfo->cfg.policy.ucbUseGlobalVWall  )  {
					PostMessage(  pQyMc->gui.hMainWnd,  WM_COMMAND,  MAKEWPARAM(  ID_2dVWall_global,  0  ),  0  );
				}
		#endif

		}
	else  {

#ifdef  __useMfc__
		  AfxGetMainWnd(  )->CenterWindow(  );		
		  #ifdef  __DEBUG__
				  AfxGetApp(  )->m_nCmdShow  =  SW_NORMAL;
		  #else
				  AfxGetApp(  )->m_nCmdShow  =  SW_SHOWMAXIMIZED;
		  #endif
#endif

	}


	//
	if  (  pQyMc->cfg.ucbUseTrayIcon  )  {
		//  sendTrayMsg(  AfxGetApp(  )->m_hInstance,  AfxGetMainWnd(  )->m_hWnd,  pQyMc->cfg.iIDR_TRAY,  NIM_ADD,  IDR_TRAY_offline,  CONST_qyWm_trayNotify  );
		sendTrayMsg(  get_my_hInst( pQyMc ),  pQyMc->gui.hMainWnd,  pQyMc->cfg.iIDR_TRAY,  NIM_ADD,  IDR_TRAY_offline,  CONST_qyWm_trayNotify  );
	}

	//  AfxGetMainWnd(  )->ShowWindow(  AfxGetApp(  )->m_nCmdShow  );
	ShowWindow(  pQyMc->gui.hMainWnd,  app_m_nCmdShow  );
	
	//  AfxGetMainWnd()->UpdateWindow(  );
	UpdateWindow(  pQyMc->gui.hMainWnd  );

#endif


#ifdef  __DEBUG__
		#if  0
			traceLog(  _T(  "Test: for d3d"  )  );
			createWall_d3d(  pQyMc->pGBuf_d3d  );
		#endif
#endif



	iErr  =  0;
errLabel:

	//  if  (  pLckFile  )  delete  pLckFile;

	if  (  iErr  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "qyShowMainWnd failed"  )  );
		#endif
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qyShowMainWnd failed."  )  );
		//  Sleep(  200  );

		myPostQuitMessage(  1  );  
	}

	return  iErr;

}


//
int  CCtxQmc_gui::loadCusModules(void* pQyMcParam)
{
	return  ::loadCusModules(pQyMcParam);
}


int  CCtxQmc_gui::unloadCusModules(void* pQyMcParam)
{
	return  ::unloadCusModules(pQyMcParam);
}

//
int  CCtxQmc_gui::initCusModules(void* pQyMcParam)
{
	return  ::initCusModules(pQyMcParam);

}


int  CCtxQmc_gui::startCusModules(void* pQyMcParam)
{
	return  ::startCusModules(pQyMcParam);
}


int  CCtxQmc_gui::stopCusModules(void* pQyMcParam)
{
	return  ::stopCusModules(pQyMcParam);
}




int CCtxQmc_gui::getSmCfgInfo(TCHAR* cfgDirName, int cfgDirNameLen)
{
	::getSmCfgDir_cli(cfgDirName, cfgDirNameLen);
	//
	TCHAR* tDir = cfgDirName;
	CCtxQmc* pProcInfo = this;
	if (bDir(tDir)) {
		_sntprintf(pQyMc->cfg.tmInitFile, mycountof(pQyMc->cfg.tmInitFile), _T("%s%s"), tDir, CONST_cfgFileName_tmInit);

		//
		_sntprintf(pQyMc->cfg.smCfgFile, mycountof(pQyMc->cfg.smCfgFile), _T("%s%s"), tDir, CONST_cfgFileName_cli_smCfg);

		//
		if (m_bUseKeyToLogin_forQmcGui) {
			_sntprintf(pQyMc->cfg.tmInitFile, mycountof(pQyMc->cfg.tmInitFile), _T("%s.%d"), pQyMc->cfg.tmInitFile, pQyMc->appParams.iSeqNoSelected_appObjPrefix);

		}

		//
		_sntprintf(pQyMc->cfg.smTmpLogFile, mycountof(pQyMc->cfg.smTmpLogFile), _T("%s%s"), tDir, CONST_logFileName_smTmp);
		//
		_sntprintf(pQyMc->cfg.hkPortStatusFile, mycountof(pQyMc->cfg.hkPortStatusFile), _T("%s%s"), tDir, CONST_cfgFileName_hkPortStatus);
		//
		TCHAR  tLogDir[256];
		_sntprintf(tLogDir, mycountof(tLogDir), _T("%s\\log\\"), tDir);
		if (!bDir(tLogDir)) {
			CreateDirectory(tLogDir, NULL);
		}
		//
		_sntprintf(pQyMc->cfg.qmcLogFile, mycountof(pQyMc->cfg.qmcLogFile), _T("%s\\log\\%s"), tDir, CONST_logFileName_qmcStatus);

		//
		_sntprintf(pQyMc->cfg.ipcProcInitFile, mycountof(pQyMc->cfg.ipcProcInitFile), _T("%s%s"), tDir, CONST_cfgFileName_ipcProcInit);

		//
	}


	//
	return  0;
}


int  CCtxQmc_gui::initVar_post(void* p0, void* p1, void* p2)
{
	return  0;
}


int  CCtxQmc_gui::exitVar_pre(void* p0, void* p1, void* p2)
{
	return  0;
}


int  CCtxQmc_gui::exitVar_post(void* p0, void* p1, void* p2)
{
	return  0;
}


 //
 int  CCtxQmc_gui::qyShowMainWndFunc(  HWND  hMainWnd,  void  *  pVar,  BOOL  bShow  )
 {
	 return  ::qyShowMainWndFunc_cli(  hMainWnd,  pVar,  bShow  );
 }

 //
 int  CCtxQmc_gui::getAuthType()
 {
	 if (m_bUseKeyToLogin_forQmcGui) {
		 //
#ifdef  __DEBUG__
		 return  CONST_authType_jdzy;
#endif
		 //
		 return  CONST_authType_bjca;
	 }
	 //
	 return  CCtxQmc::getAuthType();
 }



//
int  CCtxQmc_gui::postMsg2Mgr_mc(  void  *  pMIS_CNT,  MSG_ROUTE  *  pRoute,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  char  *  data,  unsigned  int  dataLen,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  uiChannelType,  MIS_MSGU  *  pMsgBuf,  BOOL  bLog  )
{
	return  ::postMsg2Mgr_mc(  pMIS_CNT,  pRoute,  uiMisMsgType,  ucFlg,  usCode,  tStartTime,  uiTranNo,  uiSeqNo,  data,  dataLen,  pIdInfo_logicalPeer,  pIdInfo_dst,  uiChannelType,  pMsgBuf,  bLog  );
}


//
int  CCtxQmc_gui::postMsgTask2Mgr_mc(  void  *  pMIS_CNT,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  int  iTaskId,  unsigned  int  uiTaskType,  char  *  data,  unsigned  int  dataLen,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_taskSender,  QY_MESSENGER_ID  *  pIdInfo_taskReceiver,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  uiChannelType,  MIS_MSGU  *  pMsgBuf,  BOOL  bLog  )
{
	return  ::postMsgTask2Mgr_mc(  pMIS_CNT,  uiMisMsgType,  ucFlg,  usCode,  tStartTime,  uiTranNo,  uiSeqNo,  iTaskId,  uiTaskType,  data,  dataLen,  pIdInfo_logicalPeer,  pIdInfo_taskSender,  pIdInfo_taskReceiver,  pIdInfo_dst,  uiChannelType,  pMsgBuf,  bLog  );
}


//
 int  CCtxQmc_gui::postImMsg2Log_isClient(  MIS_MSGU  *  pMsg,  int  lenInBytes_msg  )
 {
	 return  ::postImMsg2Log_isClient(  pMsg,  lenInBytes_msg  );
 }




//
int  CCtxQmc_gui::recoverMessenger(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QY_MESSENGER_INFO  *  pObj,  QY_MESSENGER_REGINFO  *  pRegInfo,  time_t  tLastModifiedTime,  BOOL  bLog,  GENERIC_Q  *  pLogQ  )
{
	return  ::recoverMessenger(  pDbFuncs,  pDb,  iDbType,  pFieldIdTable,  pObj,  pRegInfo,  tLastModifiedTime,  bLog,  pLogQ  );
}


//
 int  CCtxQmc_gui::recoverImObjRules(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRules_req	*	pReq,  time_t  tLastModifiedTime  )
 {
	 return  ::recoverImObjRules(  pDbFuncs,  pDb,  iDbType,  misServName,  pIdInfo,  pReq,  tLastModifiedTime  );
 }

 //
 int  CCtxQmc_gui::recoverImGrp(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime,  BOOL  bNoGrpName  )
 {
	 return  ::recoverImGrp(  pDbFuncs,  pDb,  iDbType,  pFieldIdTable,  uiObjType,  pGrpInfo,  tLastModifiedTime,  bNoGrpName  );
 }


 //
 int  CCtxQmc_gui::recoverImGrpMem(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime  )
 {
	 return  ::recoverImGrpMem(  pDbFuncs,  pDb,  iDbType,  pGrpMem,  tLastModifiedTime  );
 }


 //
 //	
FUNCS_for_isCliHelp* CCtxQmc_gui::FUNCS_for_isCliHelp_new()
{
	safeTcsnCpy(_T("isCliD3d.dll"), this->cfg.isCliD3dFileName, mycountof(this->cfg.isCliD3dFileName));

	//
	safeTcsnCpy(_T("isCliD3d_dx12.dll"), this->cfg.isCliD3dFileName_dx12, mycountof(this->cfg.isCliD3dFileName_dx12));

	//
	return  ::FUNCS_for_isCliHelp_new(this->pQyMc);
}


//
void  CCtxQmc_gui::FUNCS_for_isCliHelp_free(void** ppFuncs)
{
	::FUNCS_for_isCliHelp_free(ppFuncs);
	return;
}



//  2016/09/08
int  CCtxQmc_gui::tryToTalkToMessenger_any(HWND  hParent, unsigned  __int64  ui64Id, int  iTalkSubtype, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
{
	return  ::tryToTalkToMessenger_any(hParent, ui64Id, iTalkSubtype, bNeedNotShowWnd, bActivateWnd, phWnd);
}


//
int  CCtxQmc_gui::talkToMessenger(unsigned  __int64  ui64Id, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
{
	return  ::talkToMessenger(ui64Id, 0, bNeedNotShowWnd, bActivateWnd, phWnd);

}


//  
int  CCtxQmc_gui::doApplyForPlayer(HWND  hMainWnd, MIS_MSGU* pMsg)
{
	return  ::doApplyForPlayer(this->pQyMc,hMainWnd, pMsg);
}

//
int  CCtxQmc_gui::removeMosaicFromD3dWall(int  iIndex_sharedObj)
{
	return  ::dyn_removeMosaicFromD3dWall(this, iIndex_sharedObj);
}

int  CCtxQmc_gui::getVal_bExists_mosaic(int  iIndex_sharedObj, BOOL* pbExists)
{
	return  ::dyn_getVal_bExists_mosaic(this, iIndex_sharedObj, pbExists);
}

//
int  CCtxQmc_gui::stopLocalAudioRecorder(int  index_sharedObj, int  nTries)
{
	return  ::stopLocalAudioRecorder(this, index_sharedObj, nTries);
}


int  CCtxQmc_gui::talkToMessenger(void* pQyMcParam, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkUsage, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
{
	return  ::talkToMessenger_mfc(pQyMcParam, pAddr, pTmpGrpMemQ, iTalkUsage, bNeedNotShowWnd, bActivateWnd, phWnd);
}


void* CCtxQmc_gui::tmp_getDlgTalkVar(HWND  hDlgTalk)
{
	return  ::tmp_getDlgTalkVar_mfc(hDlgTalk);
}

int  CCtxQmc_gui::getTalkerShadow(HWND  hParent, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkerSubType, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
{
	return  ::getTalkerShadow_mfc(hParent, pAddr, pTmpGrpMemQ, iTalkerSubType, bNeedNotShowWnd, bActivateWnd, phWnd);
}


bool CCtxQmc_gui::myDestroyWindow(HWND  hWnd)
{
	return  ::DestroyWindow(hWnd);
}


int  CCtxQmc_gui::getDirAndFinalName(LPCTSTR  svFileName, TCHAR* dirName, unsigned  int  size, TCHAR* finalName, unsigned  int  finalNameSize)
{
	return  		::getDirAndFinalName_win(svFileName, dirName, size, finalName, finalNameSize);
}


int CCtxQmc_gui::do_mainWnd_OnTimer(HWND  hMainWnd, void* pVar, UINT  nIDEvent)
{
	if (!pVar)  return  -1;
	QY_MC_mainWndVar& var = *(QY_MC_mainWndVar*)pVar;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc_gui* pProcInfo = this;


	//
	qmcChkSmTmpLogFile();


		
	
	//
	if (!(var.loopCtrl % CONST_intervalInS_xt)) {
			//if (pProcInfo->m_var.ctxSm.ca_dev.flgs.sxrz.bDone_sqm) 
			{
				send_xt(var.loopCtrl);
			}

	}
					  
	
	//
	if (!(var.loopCtrl % 30)) {
			//		  
			startToRetrievePlans();
	}


	//
	mainWnd_chkIpcProc(var.loopCtrl);
	


		//
#ifdef  __DEBUG__

		//
	//traceLog(_T("qmc_gui.do_mainWnd_OnTimer called"));

		//
		if (1) {
			if (pQyMc->bLogon) {
				




			}

			//
		}

		//





#endif


	  return  -1;
  }


  //
  int  CCtxQmc_gui::displayRecentFriends(MIS_MSG_displayRecentFriends_qmc* pMsg)
  {
	  //
#ifdef  __DEBUG__
	  printRefreshRecentFriendsResp(&pMsg->resp,_T(""));
#endif

	  //
	  return  0;
  }

  //
  int CCtxQmc_gui::do_pleaseSpeak(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_from)
  {
	  //
	  int  iErr = -1;
	  //
	  CCtxQmc* pProcInfo = this;
		//
	  CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	  HWND  hMgr = hDlgTalk;
	  DLG_TALK_var* pMgrVar = (DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(hMgr );// &m_var;
	  if (!pMgrVar)return  -1;
	  if (!isTalkerShadowMgr(pMgrVar->addr)) {
		  TALKER_shadow* pTalkerShadow = (TALKER_shadow*)pMgrVar->pShadowInfo;
		  if (!pTalkerShadow)  return  -1;
		  hMgr = pTalkerShadow->hMgr;
		  pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
		  if (!pMgrVar)  return  -1;
	  }
	  TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
	  if (!pShadowMgr)  return  -1;

	  //
	  if (!dlgTalk_bConfCompere(hMgr, idInfo_from)) {
		  showNotification(0, &idInfo_from, 0, 0, 0, 0, _T("错误：收到一个非主持人的请求"));
		  goto  errLabel;

	  }

	  if (pMgrVar->av.taskInfo.usConfType != CONST_usConfType_emergencyCommand) {
		  showNotification(0, &idInfo_from, 0, 0, 0, 0, _T("错误：非应急指挥，不能调取视频"));
		  goto  errLabel;
	  }

	  //
	  //if (pProcInfo->cfg.policy.avRules.ucbLetConfMgrSetMicOn) 
	  {

		  //  2017/07/13
		  setCurSharedObjUsr_localAv(pProcInfo, pMgrVar->av.iIndex_sharedObj_localAv, pMgrVar->av.iIndex_usr_localAv);

		  dlgTalk_requestToSpeak(hMgr, TRUE);
	  }
	  //
	  refreshTalkerList(hMgr);
	  //
	  showNotification(0, &idInfo_from, 0, 0, 0, 0, _T("主持人请你发言"));

	  iErr = 0;

  errLabel:

	  //
	  return  iErr;
   }

  int CCtxQmc_gui::do_pleaseStopSpeaking(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_from)
  {
	  //
	  int  iErr = -1;
	  //
	  CCtxQmc* pProcInfo = this;
	  //
	  CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	  HWND  hMgr = hDlgTalk;
	  DLG_TALK_var* pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);// &m_var;
	  if (!pMgrVar)return  -1;
	  if (!isTalkerShadowMgr(pMgrVar->addr)) {
		  TALKER_shadow* pTalkerShadow = (TALKER_shadow*)pMgrVar->pShadowInfo;
		  if (!pTalkerShadow)  return  -1;
		  hMgr = pTalkerShadow->hMgr;
		  pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hMgr);
		  if (!pMgrVar)  return  -1;
	  }
	  TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
	  if (!pShadowMgr)  return  -1;

	  //
	  if (!dlgTalk_bConfCompere(hMgr, idInfo_from)) {
		  showNotification(0, &idInfo_from, 0, 0, 0, 0, _T("错误：收到一个非主持人的请求"));
		  goto  errLabel;

	  }

	  if (pMgrVar->av.taskInfo.usConfType != CONST_usConfType_emergencyCommand) {
		  showNotification(0, &idInfo_from, 0, 0, 0, 0, _T("错误：非应急指挥，不能调取视频"));
		  goto  errLabel;
	  }

	  //
	  //if (pProcInfo->cfg.policy.avRules.ucbLetConfMgrSetMicOn) 
	  {

		  //  2017/07/13
		  setCurSharedObjUsr_localAv(pProcInfo, pMgrVar->av.iIndex_sharedObj_localAv, pMgrVar->av.iIndex_usr_localAv);

		  dlgTalk_requestToSpeak(hMgr, false);
	  }
	  //
	  refreshTalkerList(hMgr);
	  //
	  showNotification(0, &idInfo_from, 0, 0, 0, 0, _T("主持人请你停止发言"));

	  iErr = 0;

  errLabel:

	  //
	  return  iErr;
  }




  //
  int CCtxQmc_gui::sxrz_yq(QIS_ca_req* p)
    {
		  int  iErr = -1;


		  //
		  ::sm_sxrz_yq(p);
		  return  0;



		  //
#if 0
	

			  //
			  Param_sxrz_servReply param;
			  memset(&param, 0, sizeof(param));
			  //
			  if (parseHgCmd_sxrz_servReply(p->ca_servData, p->ca_servDataLen, 0,  &param))  goto  errLabel;

			  //
			  if (param.cmd_org == CONST_hgCmd_xt) {
				  //
				  qmcProc_xt_resp(&param);
				  //
				  iErr = 0;  goto  errLabel;
			  }

			  //
			  if (param.cmd_org == CONST_hgCmd_retrievePlans) {
				  //


				  //
				  iErr = 0;  goto  errLabel;
			  }

			  //
			  if (p->sHgCmd == CONST_hgCmd_hk) {

				  //
				  Param_hg_cliReply  cliReply = { 0 };
				  cliReply.iHkStatus_old = param.iHkStatus;// this->av.hk.iHkStatus;

				  //
				  int  ii = 0;
				  if (this->av.hk.iHkStatus != param.iHkStatus) {
					  this->av.hk.iHkStatus = param.iHkStatus;
				  }

				  //

				  int respCode = 0;
				  //
				  sendRespToHg(respCode, p->sHgCmd, param.ui64MeetingId, &cliReply);


				  //
				  iErr = 0;  goto  errLabel;
			  }


			 

#endif

		  

		  //
		  iErr = 0;
	  errLabel:
		  //
		  return  iErr;
	  }

  int CCtxQmc_gui::chkDualSystemHotBackup()
  {
	  ::qmcChkDualSystemHotBackup();
	  return  0;
  }


  //
  int CCtxQmc_gui::do_afterLogonOk()
  {
	  int  iErr = -1;
	  QY_REG  reg;

	  QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
	  if (!pDbFuncs)  return  -1;
	  QM_dbFuncs& g_dbFuncs = *pDbFuncs;



#ifndef  __NOTSUPPORT_DB__
	  //
	  if (pQyMc->cfg.ucbDsnless) {

		  //			
		  _sntprintf(pQyMc->cfg.defaultDbName, mycountof(pQyMc->cfg.defaultDbName), _T("%s%s%s.%s.mdb"), pQyMc->cfg.appDataDir, _T(CONST_qyDbSubDir), pQyMc->appParams.appObjPrefix, pQyMc->cfg.pSysCfg->defaultDbName);

	  }

	  //
	  memset(&reg, 0, sizeof(reg));
	  //	if  (  safeStrCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  sizeof(  reg.rootKey  )  )  )  goto  errLabel;
	  lstrcpyn(reg.rootKey, CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), mycountof(reg.rootKey));
	  reg.pEncCtx = &pQyMc->encCtx;
	  //
	  unsigned  long		ulOpenOptions = 0;
	  ulOpenOptions = get_CONST_qyDbOpenOptions();
	  //
	  if (getQnmDbParams(&reg, NULL, pQyMc->iSystemId, pQyMc->cfg.ucbDsnless, pQyMc->cfg.defaultDbName, ulOpenOptions, &pQyMc->cfg.db))  goto  errLabel;
	  pQyMc->cfg.db.iSystemId = pQyMc->iSystemId;			//  2007/01/06
	  pQyMc->cfg.db.iAppType = pQyMc->iAppType;			//  2007/09/16

	  //
	  if (getProcedObjsCfg(pQyMc))  goto  errLabel;

	  int i;

	  for (i = 0; i < mycountof(pQyMc->serviceGuiInfos); i++) {
		  QY_SERVICEGUI_INFO* pInfo = &pQyMc->serviceGuiInfos[i];
		  if (!pInfo->cfg.iServiceId)  continue;
		  pInfo->cfg.iDbType = pQyMc->cfg.db.iDbType;
	  }

	  if (!bChkQyMcEnv_db(pQyMc)) {
		  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsClient"), 0, _T(""), _T(""), _T("bChkQyMcEnv_db failed."));
		  goto errLabel;
	  }

	  //
	  if (initQyMcDb(0, 0, &getProcedObjDbs(pQyMc)[pQyMc->iDsnIndex_mainSys])) {
		  traceLogA("initQyMc: initQyMcDb failed.");
		  goto  errLabel;
	  }
	  pQyMc->gui.pDb = getProcedObjDbs(pQyMc)[pQyMc->iDsnIndex_mainSys].pDb;
	  //  2013/01/30
	  pQyMc->setQmDbFuncs(pQyMc->cfg.db.iDbType, &g_dbFuncs);
#endif

  

  if (initQyMcSys(pQyMc))  goto  errLabel;	//  2005/03/21, ÓÃÓÚ×÷Ò»Ð©Ó¦ÓÃÏµÍ³µÄÌØÊâ³õÊ¼»¯£¬ÓÃÒÔ²¹³ä°²×°³ÌÐò²»¹»·½±ãµÄµØ·½
  if (!bClearQnmTmpTab(pQyMc))  goto  errLabel;

  for (i = 0; i < mycountof(pQyMc->serviceGuiInfos); i++) {
	  QY_SERVICEGUI_INFO* pInfo = &pQyMc->serviceGuiInfos[i];
	  if (!pInfo->cfg.iServiceId)  continue;

	  //
	  if (pInfo->cfg.uiVarSize) {
		  if (pInfo->cfg.pfInit_afterLogon && pInfo->cfg.pfInit_afterLogon(pQyMc, pInfo, 0))  goto  errLabel;
	  }
  }

  //  2007/12/30, 
  if (pQyMc->iAppType == CONST_qyAppType_client) {
	  MC_VAR_common* pProcInfo = (MC_VAR_common*)pQyMc->get_pProcInfo();
	  if (!pProcInfo)  goto  errLabel;
	  //
	  if (!loadCusModules(pQyMc)) {
		  pQyMc->bCusModulesLoaded = TRUE;
		  //  2007/12/31
		  if (initCusModules(pQyMc)) {
			  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsClient"), 0, _T(""), _T(""), _T("initCusModules failed."));
			  goto  errLabel;
		  }
		  if (startCusModules(pQyMc)) {
			  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsClient"), 0, _T(""), _T(""), _T("startCusModules failed."));
			  goto  errLabel;
		  }
		  //
		  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), _T("IsClient"), 0, _T(""), _T(""), _T("loadCusModules ok."));
	  }
  }

  if (pQyMc->iAppType == CONST_qyAppType_client) {
	  //  要在登陆后立即运行此函数. 2011/10/22
	  if (initPolicyAvParams())  goto  errLabel;
  }



  //  It is important to reread policy because module may change some policy. 2010/05/01
  if (pQyMc->iSystemId == CONST_qySystemId_messenger
	  && pQyMc->iAppType == CONST_qyAppType_client)
  {
	  MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)pQyMc->get_pProcInfo();
	  if (!pProcInfo)  goto  errLabel;
	  if (pProcInfo->m_iCtxType != CONST_ctxType_qmc)  goto  errLabel;

	  POLICY_isClient	policy;
	  if (!getPolicyIsClient(pProcInfo, &policy)) {
		  if (memcmp(&policy, &pProcInfo->cfg.policy, sizeof(policy))) {
			  memcpy(&pProcInfo->cfg.policy, &policy, sizeof(pProcInfo->cfg.policy));
		  }
	  }

	  //
	  bGetIpcProcInitCfg(pQyMc->cfg.ipcProcInitFile, &pProcInfo->cfg.ipcProcInitCfg);

  }

  DWORD  dwThreadDaemonId;
  for (i = 0; i < mycountof(pQyMc->hDaemonThreads); i++) {
	  if (pQyMc->threadProcs[i]) {
		  pQyMc->hDaemonThreads[i] = CreateThread(NULL, 0, pQyMc->threadProcs[i], pQyMc, 0, &dwThreadDaemonId);
		  if (pQyMc->hDaemonThreads[i] == NULL) goto errLabel;
	  }
  }

 

  //
  iErr = 0;

  errLabel:

	  return  iErr;
  }



  //
  int  CCtxQmc_gui::viewDlgSelectAvCompressor(HWND  hParent, QY_MESSENGER_ID idInfo, unsigned  int  uiCapType, unsigned  int  uiSubCapType, int  iCapUsage, BOOL  b3D, unsigned  short  usConfType)
  {
	  return  ::viewDlgSelectAvCompressor_mfc(hParent, idInfo, uiCapType, uiSubCapType, iCapUsage, b3D, usConfType);

  }

  int  CCtxQmc_gui::showDlgSelectAvDev(HWND  hParent, void* pCapStuff, int  iMenuId_selected, BOOL* pbUnresizable)
  {
	  return ::showDlgSelectAvDev(hParent, pCapStuff, iMenuId_selected, pbUnresizable);
  }


 

  //
  int  CCtxQmc_gui::do_talk_OnTimer(HWND  hDlgTalk, void* pDLG_TALK_var)
  {
	  //
	  conf_chkAvDev(hDlgTalk, pDLG_TALK_var);

	  //
	  return  0;
  }

  //
  int  CCtxQmc_gui::tmpHandler_showMsg_task(void* hDlgTalkParam, void* pDLG_TALK_var, void* p1, void* pMsgParam)
  {
	  if (!pDLG_TALK_var) return  -1;
	  DLG_TALK_var& m_var = *(DLG_TALK_var*)pDLG_TALK_var;

	  //
	  return  ::tmpHandler_showMsg_task_qmcCli(hDlgTalkParam, m_var, p1, pMsgParam);

  }
  

  int mainWnd_procMsgInput_confReq(HWND  hMainWnd, void* pVar, MIS_MSG_INPUT* pMsgInput)
  {
	  return  -1;
  }


  int dlgTalk_closeTaskAv_afterTaskClosed(HWND  hDlgTalk, DLG_TALK_var* pm_var)
  {
	  return -1;
  }


  //
  int  CCtxQmc_gui::doCmd_startAvCall(HWND  hParent, HWND  hCurTalk, int  level, BOOL  b3D, unsigned  char  ucbAvConsole, PARAM_startAvCall* pParam)
  {
	  return  	confCli_doCmd_startAvCall(hParent, hCurTalk, level, b3D, ucbAvConsole, pParam);

 }
