
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
#include	"ctxQmc_qyMcu.h"
#include	"policyAvParams.h"
#include	"qyAvRecordPublic.h"
//#include	"qmcVideoCapture_isCli.h"
//#include	"qmcCommFunc_isCli.h"
#include	"qmcCmdProc.h"
#include	"qyMcMainWndProc.h"
#include	<shellapi.h>
#include	"resource.h"
#include <smCommProc.h>
#include	"tmpRegFunc_open.h"
#include <help_getDlgTalkVar.h>
#include	"dlgtalkproc.h"

//
//
int  tmpHandler_showMsg_task_qyMcu(void* hDlgTalkParam, DLG_TALK_var& m_var, void* p1, void* pMsgParam);
int  sendConfKey(HWND  hDlgTalk, QY_MESSENGER_ID    idInfo_to, LPCTSTR  hint);


//
//
 extern  "C"  __declspec(  dllexport  )  int  parseCmdLine_qyMc(  LPCTSTR  pCmdLine,  QMC_APP_PARAMS  *  pParams  )
 {
	 //
#ifdef  __DEBUG__
		#if  0
			pCmdLine  =  _T(  "-fileServer=1"  );
			//pCmdLine  =  _T(  ""  );
			showInfo_open0(  0,  0,  _T(  "for test. parseCmdLine_qmc: cmdLine set to \"\""  )  );
		#endif			 
#endif


	 //
	 parseCmdLine_qmc_func(  pCmdLine,  pParams  );
	 
	 //
	 pParams->bMcu  =  true;
	 if  (  pParams->idInfo_mcu.ui64Id  )  {
		 pParams->bService  =  true;
	 }

	 //
	 if  (  pParams->bService  )  {
		 pParams->bUseMachineKey  =  true;
		 pParams->bUseAuthTypeMcu  =  true;
		 //
		 pParams->ucbNotNeedLocked  =  true;
		 //
	 }
	 if  (  pParams->bMcu  )  {
		 pParams->canStartConf  =  true;		 
		 //
		 pParams->bNoPrompt_mfc  =  true;
		 pParams->bNoAcceptAv  =  true;
		 //
	 }
	 if (pParams->bConfServer) {
		 pParams->bInSilence = true;
		 pParams->bNoAec = true;

		 //
		 pParams->bNoDrawDibDraw_forConfServer = true;
		 		
		 //
		 //pParams->bUse_decD3d_nv = true;

		 //
		 pParams->bUse_encD3d_nv = true;

	 }

	 //
#ifdef __DEBUG__ //__DEBUG__
	 //
#ifndef  __DEBUG__
	 MessageBox(null,_T("for test"  ),  _T(  "for test, here"  ),  MB_OK  );
	 //
#endif
	 //
#if 10

	 //
#if 0
	 pParams->bUse_decD3d_nv = false;
	 pParams->bUse_encD3d_nv = false;
	 showInfo_open0(0,0,_T("for test: mcu: use dec_nv, enc_nv"));
#endif


	 //pParams->bInSilence = false;
	 //
		#if  0		//  测试pool里的mcu
			#if  10
				 pParams->bService  =  false;
				 //pParams->bMcu  =  false;
				 showInfo_open0(  0,  0,  _T(  "for test. parseCmdLine_qmc: bService set to false"  )  );
			#endif
				 //
			#if  10
				 pParams->bUseMachineKey  =  false;
				 showInfo_open0(  0,  0,  _T(  "for test. parseCmdLine_qmc: bUseMachineKey set to false"  )  );
			#endif
				 //
			#if  0
				 pParams->bUseAuthTypeMcu  =  false;
				 showInfo_open0(  0,  0,  _T(  "for test. parseCmdLine_qmc: bUseAuthTypeMcu set to false"  )  );			 
				 //
				 #if  10
					  pParams->canStartConf  =  true;
					  showInfo_open0(  0,  0,  _T(  "for test. parseCmdLine_qmc: bNoConfStarter set to false"  )  );			 
				 #endif
				 //
				 #if  10
					  pParams->bConfServer  =  true;
				 #else
				 	  pParams->bConfServer  =  false;
					  pParams->ucbFileServer  =  true;
				 #endif
				
				 //
				 pParams->bNoPrompt  =  false;

				 
				 
				 //
				 #if  0
					  //safeStrnCpy(  "202.8.121.51",  pParams->serverAddr,  mycountof(  pParams->serverAddr  )  );
					  //
					  safeTcsnCpy(  _T(  "ywm"  ),  pParams->usrName,  mycountof(  pParams->usrName  )  );
					  safeTcsnCpy(  _T(  "123"  ),  pParams->passwd,  mycountof(  pParams->passwd  )  );
				 #endif
			#endif

		#else  // 不在pool里的mcu
			//
			#if  10
				 pParams->bService  =  false;
				 //pParams->bMcu  =  false;
				 showInfo_open0(  0,  0,  _T(  "for test. parseCmdLine_qmc: bService set to false"  )  );
			#endif
				 //
			#if  10
				 pParams->bUseMachineKey  =  false;
				 showInfo_open0(  0,  0,  _T(  "for test. parseCmdLine_qmc: bUseMachineKey set to false"  )  );
			#endif
				 //
			#if  10
				 pParams->bNoDrawDibDraw_forConfServer = false;
				 showInfo_open0(  0,  0,  _T(  "for test. parseCmdLine_qmc: bNoDrawDibDraw_forConfServer set to false"  )  );
			#endif

				 //
			#if  10
				 pParams->bUseAuthTypeMcu  =  false;
				 showInfo_open0(  0,  0,  _T(  "for test. parseCmdLine_qmc: bUseAuthTypeMcu set to false"  )  );			 
				 //
				 if (0) {
#if  10
					 pParams->canStartConf = true;
					 showInfo_open0(0, 0, _T("for test. parseCmdLine_qmc: bNoConfStarter set to false"));
#endif
					 //
					 if (!pParams->bFileServer) {
#if  10
						 pParams->bConfServer = true;
#else
						 pParams->bConfServer = false;
						 pParams->ucbFileServer = true;
#endif					  
					 }

					 //

					 //
					 //pParams->bNoPrompt  =  false;

					 //
					 //pParams->bUse_forTest_defaultAvLevel_240p=true;

					 //
					 if (10) {
						 //pParams->bUse_forTest_useNv = true;
					 }

					 //
					 if (1) {
						 pParams->bUse_forTest_noLocalAv = true;
					 }

					 //
					 if (0) {
						 pParams->ucb2Streams_forDbg = true;
					 }
					 //
					 //pParams->conf_iFourcc_forDbg = CONST_fourcc_h264;// CONST_fourcc_HEVC;
					 pParams->conf_iFourcc_forDbg = CONST_fourcc_HEVC;
					 //
					 pParams->ucHardwareAccl_forDbg = CONST_hdAccl_msdk_hardware;
					 //pParams->ucHardwareAccl_forDbg = CONST_hdAccl_nv;
					 //
					 pParams->iMeetingLevel_forDbg = CONST_meetingLevel_jm;
					 pParams->bRecord_forDbg = true;

				 }
				 else {
					  //
					  pParams->bFileServer = true;

					  //
				 }

				 //
				 #if  10
					  safeStrnCpy(  "bbs.qycx.com",  pParams->serverAddr,  mycountof(  pParams->serverAddr  )  );
					  //
					  safeStrnCpy("127.0.0.1", pParams->serverAddr, mycountof(pParams->serverAddr));
					  //safeStrnCpy("10.0.1.109", pParams->serverAddr, mycountof(pParams->serverAddr));
					  safeStrnCpy("103.85.174.150", pParams->serverAddr, mycountof(pParams->serverAddr));
					  
					  safeStrnCpy("119.57.97.99", pParams->serverAddr, mycountof(pParams->serverAddr));

					  //
					  char* servInitVal = "";
					  TCHAR* usrInitVal = _T("");
					  TCHAR* pwdInitVal = _T("");



					  //
					  servInitVal = "192.168.1.14";
					  usrInitVal = _T("yuwm");
					  pwdInitVal = _T("123456");


					  //
					  servInitVal = "119.57.97.99";
					  usrInitVal = _T("yuwm");
					  pwdInitVal = _T("123456");

					  //
#if 10
					  servInitVal = "127.0.0.1";
					  usrInitVal = _T(  "fileServer"  );
					  pwdInitVal = _T("123456");
#endif
					  

					  //
					  safeStrnCpy(servInitVal, pParams->serverAddr, mycountof(pParams->serverAddr));

					  //
					  pParams->port=8768;

					  //					  
					  //safeTcsnCpy(  _T(  "yuweiming"  ),  pParams->usrName,  mycountof(  pParams->usrName  )  );
					  safeTcsnCpy(  usrInitVal,  pParams->usrName,  mycountof(  pParams->usrName  )  );
					  safeTcsnCpy(  pwdInitVal,  pParams->passwd,  mycountof(  pParams->passwd  )  );

				 #endif

			#endif
		#endif
#endif

#endif

		return  0;
 }
 

 //
 int  doPre_createConsoleWall(  void  *  p0,  void  *  p1,  void  *  p2  )	
 {
	 CCtxQyMc  *  pQyMc  =  QY_GET_GBUF(  );
	 CCtxQmc  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

#ifdef  __DEBUG__
		#if  10
			 //
			 showInfo_open0(  0,  0,  _T(  "for test: set doConf"  )  );
			 
			 //
			 pProcInfo->av.doConf.confReq.uiType  =  CONST_imCommType_confReq;
			 pProcInfo->av.doConf.confReq.usOp  =  0;
			 pProcInfo->av.doConf.confReq.idInfo_initiator.ui64Id  =  117;
			 pProcInfo->av.doConf.confReq.idInfo_imGrp_related.ui64Id = 923;// 107;// 208;
			 pProcInfo->av.doConf.confReq.policy.talkerPolicy.conf_iFourcc  =  CONST_fourcc_HEVC;
			 //
			 pProcInfo->av.doConf.confReq.ucHardwareAccl = CONST_hdAccl_nv;
			 //
			 pProcInfo->av.doConf.confReq.policy.talkerPolicy.gpu_usIndex = 0;
		#endif
#endif

	 return  0;		
 }



//
 //  2015/01/20
 int  newVar_isCli_gui(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 QY_MC					*	pQyMc				=	(  QY_MC  *  )p0;
	 QY_SERVICEGUI_INFO		*	pSci				=	(  QY_SERVICEGUI_INFO  *  )p1;

	 CCtxQmc  *  p  =  NULL;

	 p  =  new  CCtxQmc_qyMcu;

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
CCtxQmc_qyMcu::CCtxQmc_qyMcu(  )
{
	//  2014/02/08
	this->m_iCtxType  =  CONST_ctxType_qmc;

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
		
		//
		

#endif

}

CCtxQmc_qyMcu::~CCtxQmc_qyMcu(  )
{
	int  i  =  0;

}

//
int  CCtxQmc_qyMcu::getAuthType(  )
{
	CCtxQyMc  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  pQyMc->appParams.bUseAuthTypeMcu  )  {
		return  CONST_authType_qyMcu;
	}
	return  CCtxQmc::getAuthType(  );
}


//
 int  CCtxQmc_qyMcu::setQmDbFuncs(  int  iDbType,  QM_dbFuncs  *  pDbFuncs  )  
 {  
	 return  ::setQmDbFuncs_qm(  iDbType,  pDbFuncs  );  
 }

 //
 int  qyMc_setQmDbFuncs(  int  iDbType,  QM_dbFuncs  *  pDbFuncs  )
 {
	 return  ::setQmDbFuncs_qm(  iDbType,  pDbFuncs  );
 }


BOOL  CCtxQmc_qyMcu::bSupport_sharedTex()
{
	//return true;
	return false;
}


 //
BOOL CALLBACK myEnumWindowsProc_singleInstance(  HWND hwnd,  LPARAM lParam  );


//
   int  qyShowMainWndFunc_qyMcu(  HWND  hMainWnd,  void  *  pVar,  BOOL  bShow  )
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
		
		//::MoveWindow(  pQyMc->gui.hMainWnd,  iX,  iY,  iWidth,  iHeight,  0  );
	}
#endif

	//
	{
		PARAM_showDlgMcLogon  param  =  {0};
							    
		if  (  pQyMc->appParams.usrName[0]  &&  pQyMc->appParams.passwd[0]  )  {
		
			//
			safeTcsnCpy(  pQyMc->appParams.usrName,  param.usrName,  mycountof(  param.usrName  )  );
			safeTcsnCpy(  pQyMc->appParams.passwd,  param.passwd,  mycountof(  param.passwd  )  );
			//				
			if  (  !bQyMcLogon(  pQyMc,  doConf_showDlgMcClientLogon,  &param  )  )  goto  errLabel;				

			//
			}
					
		else  {		
			  if  (  !bQyMcLogon(  pQyMc,  showDlgMcClientLogon,  &param  )  )  goto  errLabel;				
		}
	}

	//
	if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {

		if  (  !pQyMc->appParams.ucbNotNeedLocked  )  {	//  Release 2007/05/29
			//  
			if  (  pQyMc->cfg.singleInstanceStr[0]  )  {

				#ifndef  __WINCE__
						 lckCStr = CQyString(  pQyMc->appParams.appObjPrefix  )  +  CQyString(  pQyMc->cfg.singleInstanceStr  );
				#else
						 lckCStr = CQyString(  CONST_mutexPrefix_mcClientLogon  )  +  pQyMc->cfg.singleInstanceStr;
				#endif
				pQyMc->gui.hMutex_singleInstance  =  CreateMutex(  NULL,  FALSE,  lckCStr  );
				if  (  !pQyMc->gui.hMutex_singleInstance  )  {
					traceLog(  _T(  "singleInstance failed, null."  )  );
					goto  errLabel;
				}
				if  (  GetLastError(  )  ==  ERROR_ALREADY_EXISTS  )  {
					traceLog(  _T(  "singleInstance failed, already exists."  )  );

					COMMON_PARAM	commonParam;
					HWND	hPrevWnd	=	NULL;

					MACRO_makeCommonParam3(  0,  (  void  *  )lckCStr.GetBuffer(  ),  &hPrevWnd,  commonParam  );
					EnumWindows(  myEnumWindowsProc_singleInstance,  (  LPARAM  )&commonParam  );

					if  (  IsWindow(  hPrevWnd  )  )  {
						//  if  (  IsIconic(  hPrevWnd  )  )  ShowWindow(  hPrevWnd,  SW_RESTORE  );
						ShowWindow(  hPrevWnd,  SW_SHOWNORMAL  );

						#if !defined(  __WINCE__  )  ||  defined(  __TEST__  )
								SetForegroundWindow(  hPrevWnd  );
								SetForegroundWindow(  GetLastActivePopup(  hPrevWnd  )  );
						#else
								SetForegroundWindow((HWND)(((ULONG) hPrevWnd) | 0x01) );
						#endif
			
					}

					goto  errLabel;
				}

				//
				if  (  !IsWindow(  pQyMc->gui.hMainWnd  )  )  goto  errLabel;
				if  (  !SetProp(  pQyMc->gui.hMainWnd,  lckCStr,  (  HANDLE  )1  )  )  goto  errLabel;
			}
			//  ¼ì²é½áÊø	 	 
		}


	#ifndef  __NOTSUPPORT_DB__
		//
		if  (  pQyMc->cfg.ucbDsnless  )  {
			
	   		     #if  0	//  defined(  __DEBUG__  )  //  ||  defined(  __TEST_MULTILOGON__  )
						 TCHAR		module[MAX_PATH];
				   		 TCHAR		tmpBuf[MAX_PATH];
				   		 TCHAR	*	filePart;
				   		 GetModuleFileName(  NULL,  module,  mycountof(  module  )  );
				   		 GetFullPathName(  module,  mycountof(  tmpBuf  ),  tmpBuf,  &filePart  );

						 _sntprintf(  pQyMc->cfg.defaultDbName,  mycountof(  pQyMc->cfg.defaultDbName  ),  _T(  "%s%s%s.%s.%s.mdb"  ),  pQyMc->cfg.appDataDir,  _T(  CONST_qyDbSubDir  ),  pQyMc->appObjPrefix,  pQyMc->cfg.pSysCfg->defaultDbName,  filePart  );
	
				 #else
						_sntprintf(  pQyMc->cfg.defaultDbName,  mycountof(  pQyMc->cfg.defaultDbName  ),  _T(  "%s%s%s.%s.mdb"  ),  pQyMc->cfg.appDataDir,  _T(  CONST_qyDbSubDir  ),  pQyMc->appParams.appObjPrefix,  pQyMc->cfg.pSysCfg->defaultDbName  );
				 #endif
			  
		}

		//
		memset(  &reg,  0,  sizeof(  reg  )  );
		//	if  (  safeStrCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  sizeof(  reg.rootKey  )  )  )  goto  errLabel;
		lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
		reg.pEncCtx  =  &pQyMc->encCtx;
		//
		unsigned  long		ulOpenOptions						=	0;				
		ulOpenOptions  =  get_CONST_qyDbOpenOptions(  );
		//
		if  (  getQnmDbParams(  &reg,  pQyMc->cfg.smCfgFile,  pQyMc->iSystemId,  pQyMc->cfg.ucbDsnless,  pQyMc->cfg.defaultDbName,  ulOpenOptions,  &pQyMc->cfg.db  )  )  goto  errLabel;
		pQyMc->cfg.db.iSystemId  =  pQyMc->iSystemId;			//  2007/01/06
		pQyMc->cfg.db.iAppType  =  pQyMc->iAppType;			//  2007/09/16

		//
		if  (  getProcedObjsCfg(  pQyMc  )  )  goto  errLabel;


		for  (  i  =  0;  i  <  mycountof(  pQyMc->serviceGuiInfos  );  i  ++  )  {
		  QY_SERVICEGUI_INFO	*	pInfo	=	&pQyMc->serviceGuiInfos[i];
		  if  (  !pInfo->cfg.iServiceId  )  continue;
		  pInfo->cfg.iDbType  =  pQyMc->cfg.db.iDbType;
		}

		if  (  !bChkQyMcEnv_db(  pQyMc  )  )  {
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bChkQyMcEnv_db failed."  )  );
			goto errLabel;
		}

		//
		if  (  initQyMcDb(  0,  0,  &getProcedObjDbs(  pQyMc  )[pQyMc->iDsnIndex_mainSys]  )  )  {
			traceLogA(  "initQyMc: initQyMcDb failed."  );  
			goto  errLabel;
		}
		pQyMc->gui.pDb  =  getProcedObjDbs(  pQyMc  )[pQyMc->iDsnIndex_mainSys].pDb;
		//  2013/01/30
		pQyMc->setQmDbFuncs(  pQyMc->cfg.db.iDbType,  &g_dbFuncs  );
	#endif

	}

	if  (  initQyMcSys(  pQyMc  )  )  goto  errLabel;	//  2005/03/21, ÓÃÓÚ×÷Ò»Ð©Ó¦ÓÃÏµÍ³µÄÌØÊâ³õÊ¼»¯£¬ÓÃÒÔ²¹³ä°²×°³ÌÐò²»¹»·½±ãµÄµØ·½
	if  (  !bClearQnmTmpTab(  pQyMc  )  )  goto  errLabel;

	for  (  i  =  0;  i  <  mycountof(  pQyMc->serviceGuiInfos  );  i  ++  )  {
		  QY_SERVICEGUI_INFO	*	pInfo	=	&pQyMc->serviceGuiInfos[i];
		  if  (  !pInfo->cfg.iServiceId  )  continue;

		  //
		  if  (  pInfo->cfg.uiVarSize  )  {
			  if  (  pInfo->cfg.pfInit_afterLogon  &&  pInfo->cfg.pfInit_afterLogon(  pQyMc,  pInfo,  0  )  )  goto  errLabel;
		  }
	 }

	//  2007/12/30, 
	if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {
		MC_VAR_common  *  pProcInfo  =  (MC_VAR_common*)pQyMc->get_pProcInfo(  );
		if  (  !pProcInfo  )  goto  errLabel;
		//
		if  (  !loadCusModules(  pQyMc  )  )  {
			pQyMc->bCusModulesLoaded  =  TRUE;
			//  2007/12/31
			if  (  initCusModules(  pQyMc  )  )  {
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initCusModules failed."  )  );
				goto  errLabel;
			}
			if  (  startCusModules(  pQyMc  )  )  {
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "startCusModules failed."  )  );
				goto  errLabel;
			}
			//
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "loadCusModules ok."  )  );
		}
	}

	if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {
		//  要在登陆后立即运行此函数. 2011/10/22
		if  (  initPolicyAvParams(  )  )  goto  errLabel;
	}

#ifndef  __WINCE__
	//  2007/12/31, ¸ù¾Ý×°ÔØÄ£¿éµÄÇé¿öÀ´¸Ä±ä²Ëµ¥¡£	
	if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {
		if  (  pQyMc->gui.hMenuChildFrm  )  cusModuleMenu(  pQyMc,  pQyMc->gui.hMenuChildFrm,  CONST_resId_menu_modulesGuanLi_isClient  );
		//  CMenu	*	pMenu;
		HMENU	hMenu;
		if  (  IsWindow(  pQyMc->gui.hMainWnd  )  )  {
			//  if  (  (  pMenu  =  pMainWnd->GetMenu(  )  )  )  cusModuleMenu(  pQyMc,  pMenu->m_hMenu,  CONST_resId_menu_modulesGuanLi_isClient  );
			hMenu  =  ::GetMenu(  pQyMc->gui.hMainWnd  );
			if  (  hMenu  )  cusModuleMenu(  pQyMc,  hMenu,  CONST_resId_menu_modulesGuanLi_isClient  );
		}
	}
#endif

	//  It is important to reread policy because module may change some policy. 2010/05/01
	if  (  pQyMc->iSystemId  ==  CONST_qySystemId_messenger
		&&  pQyMc->iAppType  ==  CONST_qyAppType_client  )
	{
		MC_VAR_isCli	*	pProcInfo	=	(  MC_VAR_isCli  *  )pQyMc->get_pProcInfo(  );
		if  (  !pProcInfo  )  goto  errLabel;
		if  (  pProcInfo->m_iCtxType  !=  CONST_ctxType_qmc  )  goto  errLabel;
	
		POLICY_isClient	policy;
		if  (  !getPolicyIsClient(  pProcInfo,  &policy  )  )  {
			if  (  memcmp(  &policy,  &pProcInfo->cfg.policy,  sizeof(  policy  )  )  )  {
				memcpy(  &pProcInfo->cfg.policy,  &policy,  sizeof(  pProcInfo->cfg.policy  )  );
			}
		}
	}

	DWORD  dwThreadDaemonId;
	for  (  i  =  0;  i  <  mycountof(  pQyMc->hDaemonThreads  );  i  ++  )  {
		  if  (  pQyMc->threadProcs[i]  )  {
		 	  pQyMc->hDaemonThreads[i] = CreateThread( NULL, 0, pQyMc->threadProcs[i], pQyMc, 0, &dwThreadDaemonId );
		 	  if ( pQyMc->hDaemonThreads[i] == NULL ) goto errLabel;
		  }
	 }


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
		sendTrayMsg(  get_my_hInst(pQyMc  ),  pQyMc->gui.hMainWnd,  pQyMc->cfg.iIDR_TRAY,  NIM_ADD,  IDR_TRAY_offline,  CONST_qyWm_trayNotify  );
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
int  CCtxQmc_qyMcu::loadCusModules(void* pQyMcParam)
{
	return  ::loadCusModules(pQyMcParam);
}


int  CCtxQmc_qyMcu::unloadCusModules(void* pQyMcParam)
{
	return  ::unloadCusModules(pQyMcParam);
}

//
int  CCtxQmc_qyMcu::initCusModules(void* pQyMcParam)
{
	return  ::initCusModules(pQyMcParam);

}


int  CCtxQmc_qyMcu::startCusModules(void* pQyMcParam)
{
	return  ::startCusModules(pQyMcParam);
}


int  CCtxQmc_qyMcu::stopCusModules(void* pQyMcParam)
{
	return  ::stopCusModules(pQyMcParam);
}


//
int CCtxQmc_qyMcu::getSmCfgInfo(TCHAR* cfgDirName, int cfgDirNameLen)
{
	//CCtxQyMc* pQyMc = g_pQyMc;

	TCHAR  tBuf[256] = _T("");
	unsigned  int  uiType = 0;
	qyGetRegCfgT(HKEY_LOCAL_MACHINE, _T(CONST_qyRootKey_qnmScheduler_misClient), _T("mcu_smCfgDir"), (char*)tBuf, sizeof(tBuf), &uiType);
	tBuf[mycountof(tBuf) - 1] = 0;
	tTrim(tBuf);

	if (!tBuf[0]) {
		safeTcsnCpy(DEFAULT_smCfgDir, cfgDirName, cfgDirNameLen);
	}
	else {
		safeTcsnCpy(tBuf, cfgDirName, cfgDirNameLen);
	}



	CCtxQmc* pProcInfo = this;
	TCHAR* tDir = cfgDirName;
	if (bDir(tDir)) {
		_sntprintf(pQyMc->cfg.tmInitFile, mycountof(pQyMc->cfg.tmInitFile), _T("%s%s"), tDir, CONST_cfgFileName_tmInit);
		_sntprintf(pQyMc->cfg.smCfgFile, mycountof(pQyMc->cfg.smCfgFile), _T("%s%s"), tDir, CONST_cfgFileName_mcu_smCfg);
		_sntprintf(pQyMc->cfg.smTmpLogFile, mycountof(pQyMc->cfg.smTmpLogFile), _T("%s%s"), tDir, CONST_logFileName_smTmp);
	}

	//

	//
	return  0;
}

//
int  CCtxQmc_qyMcu::initVar_post(void* p0, void* p1, void* p2)
{
	return  0;
}


int  CCtxQmc_qyMcu::exitVar_pre(void* p0, void* p1, void* p2)
{
	return  0;
}


int  CCtxQmc_qyMcu::exitVar_post(void* p0, void* p1, void* p2)
{
	return  0;
}


 //
 int  CCtxQmc_qyMcu::qyShowMainWndFunc(  HWND  hMainWnd,  void  *  pVar,  BOOL  bShow  )
 {
	 return  ::qyShowMainWndFunc_qyMcu(  hMainWnd,  pVar,  bShow  );
 }


//
int  CCtxQmc_qyMcu::postMsg2Mgr_mc(  void  *  pMIS_CNT,  MSG_ROUTE  *  pRoute,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  char  *  data,  unsigned  int  dataLen,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  uiChannelType,  MIS_MSGU  *  pMsgBuf,  BOOL  bLog  )
{
	return  ::postMsg2Mgr_mc(  pMIS_CNT,  pRoute,  uiMisMsgType,  ucFlg,  usCode,  tStartTime,  uiTranNo,  uiSeqNo,  data,  dataLen,  pIdInfo_logicalPeer,  pIdInfo_dst,  uiChannelType,  pMsgBuf,  bLog  );
}


//
int  CCtxQmc_qyMcu::postMsgTask2Mgr_mc(  void  *  pMIS_CNT,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  int  iTaskId,  unsigned  int  uiTaskType,  char  *  data,  unsigned  int  dataLen,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_taskSender,  QY_MESSENGER_ID  *  pIdInfo_taskReceiver,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  uiChannelType,  MIS_MSGU  *  pMsgBuf,  BOOL  bLog  )
{
	return  ::postMsgTask2Mgr_mc(  pMIS_CNT,  uiMisMsgType,  ucFlg,  usCode,  tStartTime,  uiTranNo,  uiSeqNo,  iTaskId,  uiTaskType,  data,  dataLen,  pIdInfo_logicalPeer,  pIdInfo_taskSender,  pIdInfo_taskReceiver,  pIdInfo_dst,  uiChannelType,  pMsgBuf,  bLog  );
}


//
 int  CCtxQmc_qyMcu::postImMsg2Log_isClient(  MIS_MSGU  *  pMsg,  int  lenInBytes_msg  )
 {
	 return  ::postImMsg2Log_isClient(  pMsg,  lenInBytes_msg  );
 }




//
int  CCtxQmc_qyMcu::recoverMessenger(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QY_MESSENGER_INFO  *  pObj,  QY_MESSENGER_REGINFO  *  pRegInfo,  time_t  tLastModifiedTime,  BOOL  bLog,  GENERIC_Q  *  pLogQ  )
{
	return  ::recoverMessenger(  pDbFuncs,  pDb,  iDbType,  pFieldIdTable,  pObj,  pRegInfo,  tLastModifiedTime,  bLog,  pLogQ  );
}


//
 int  CCtxQmc_qyMcu::recoverImObjRules(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRules_req	*	pReq,  time_t  tLastModifiedTime  )
 {
	 return  ::recoverImObjRules(  pDbFuncs,  pDb,  iDbType,  misServName,  pIdInfo,  pReq,  tLastModifiedTime  );
 }

 //
 int  CCtxQmc_qyMcu::recoverImGrp(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime,  BOOL  bNoGrpName  )
 {
	 return  ::recoverImGrp(  pDbFuncs,  pDb,  iDbType,  pFieldIdTable,  uiObjType,  pGrpInfo,  tLastModifiedTime,  bNoGrpName  );
 }


 //
 int  CCtxQmc_qyMcu::recoverImGrpMem(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime  )
 {
	 return  ::recoverImGrpMem(  pDbFuncs,  pDb,  iDbType,  pGrpMem,  tLastModifiedTime  );
 }


 //
 //	
 FUNCS_for_isCliHelp  *  CCtxQmc_qyMcu::FUNCS_for_isCliHelp_new(  )
 {
	 //showInfo_open0(  0, 0,  _T(  "qmdCliHelp.FUNCS_for_is"  )  );
	 //
	 safeTcsnCpy(  _T(  "isCliD3d_qyMcu.dll"  ),  this->cfg.isCliD3dFileName,  mycountof(  this->cfg.isCliD3dFileName  )  );
	 return  ::FUNCS_for_isCliHelp_new(  this->pQyMc  );
 }


 //
 void  CCtxQmc_qyMcu::FUNCS_for_isCliHelp_free(  void  **  ppFuncs  )
 {
	 ::FUNCS_for_isCliHelp_free(  ppFuncs  );
	 return;
 }



 //  2016/09/08
  int  CCtxQmc_qyMcu::tryToTalkToMessenger_any(HWND  hParent, unsigned  __int64  ui64Id, int  iTalkSubtype, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
  {
	  return  ::tryToTalkToMessenger_any(hParent, ui64Id, iTalkSubtype, bNeedNotShowWnd, bActivateWnd, phWnd);
  }


  //
  int  CCtxQmc_qyMcu::talkToMessenger(  unsigned  __int64  ui64Id,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phWnd  )
  {
	  return  ::talkToMessenger(  ui64Id,  0,  bNeedNotShowWnd,  bActivateWnd,  phWnd  );

  }

		
  //  
  int  CCtxQmc_qyMcu::doApplyForPlayer(  HWND  hMainWnd,  MIS_MSGU  *  pMsg  )
  {
	  return  ::doApplyForPlayer(  g_pQyMc,  hMainWnd,  pMsg  );
  }


  int  CCtxQmc_qyMcu::talkToMessenger(void* pQyMcParam, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkUsage, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
  {
	  return  ::talkToMessenger_mfc(pQyMcParam, pAddr, pTmpGrpMemQ, iTalkUsage, bNeedNotShowWnd, bActivateWnd, phWnd);
  }


  void* CCtxQmc_qyMcu::tmp_getDlgTalkVar(HWND  hDlgTalk)
  {
	  return  ::tmp_getDlgTalkVar_mfc(hDlgTalk);
  }

  int  CCtxQmc_qyMcu::getTalkerShadow(HWND  hParent, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkerSubType, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd)
  {
	  return  ::getTalkerShadow_mfc(hParent, pAddr, pTmpGrpMemQ, iTalkerSubType, bNeedNotShowWnd, bActivateWnd, phWnd);
  }

  //
  int  CCtxQmc_qyMcu::getDirAndFinalName(LPCTSTR  svFileName, TCHAR* dirName, unsigned  int  size, TCHAR* finalName, unsigned  int  finalNameSize)
  {
	  return  getDirAndFinalName_win(svFileName, dirName, size, finalName, finalNameSize);
  }

  //
  int  CCtxQmc_qyMcu::do_mainWnd_OnTimer(HWND  hMainWnd, void* pVar, UINT  nIDEvent)
  {
	  int  iErr = -1;
	  if (!pVar)  return  -1;
	  QY_MC_mainWndVar& var = *(QY_MC_mainWndVar*)pVar;
	  CCtxQyMc* pQyMc = g_pQyMc;
	  CCtxQmc* pProcInfo = this;
	  TCHAR  tBuf[128];

	  //
	  MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	  if (pMisCnt == NULL)  return  -1;

	  //
#ifdef  __DEBUG__

#if 0
	  _sntprintf(tBuf, mycountof(tBuf), _T("Serious error: confServer: d3dUsing is false"));
	  _sntprintf(tBuf, mycountof(tBuf), _T("%s, wndType_gui %d"), tBuf, pQyMc->gui.iWndContentType_hGuiWnd);
	  showInfo_open0(0, 0, tBuf);
#endif

#endif

	  //
	  if (pQyMc->appParams.bConfServer) {
		  if (!(var.loopCtrl % 5)) {
			  BOOL  bActive = false;
			  if (!dyn_bD3dUsing(pProcInfo, &bActive)) {
				  //
				  _sntprintf(  tBuf,  mycountof(  tBuf),  _T("Serious error: confServer: d3dUsing is false"));
				  _sntprintf(tBuf, mycountof(tBuf), _T("%s, wndType_gui1 %d"), tBuf, pQyMc->gui.iWndContentType_hGuiWnd);																
				  showInfo_open0(0, 0, tBuf);
				  //
				  if (pProcInfo->status.confServerStatus.bDone_createConsoleWall) {
					  showInfo_open0(0, NULL, _T("confServer: quitApp now"));
					  notifyPanicToApp(pQyMc, 0, _T("d3dUsing is false"));
					  goto  errLabel;
				  }
			  }
		  }
		  //
		  if (!(var.loopCtrl % 5)) {
			  //
			  int  ii = 0;
			  TCHAR  tBuf[128]  =  _T(  ""  );
			  HKEY  hKeyRoot0 = HKEY_LOCAL_MACHINE;
			  TCHAR* rootKey = _T(CONST_qyRootKey_qnmScheduler_misClient);
			  TCHAR* cfgName = CONST_regValName_bMon;// _T("vMon");
			  unsigned  int  uiType = 0;
			  unsigned  int  size = sizeof(tBuf);
			  bool  bMon = false;
			  if (!tmpGetRegCfg_open(hKeyRoot0, rootKey, cfgName, &uiType, (char*)tBuf, &size)) {
				  if (_ttol(tBuf)) {
					  bMon = true;
				  }
			  }
			  pProcInfo->cfg.debugStatusInfo.bMon_decV  =  bMon;
			  pProcInfo->cfg.debugStatusInfo.bMon_encV = bMon;

			  //
		  }
	  }

	  //
	  if (pQyMc->appParams.bMcu) {
		  if (pProcInfo->cfg.dwRefreshedTickCnt_debugStatusInfo) {
			  DWORD  dwTickCnt = myGetTickCount(NULL);
			  if (dwTickCnt - pProcInfo->cfg.dwRefreshedTickCnt_debugStatusInfo > 10000) {
				  memset(&pProcInfo->cfg.debugStatusInfo, 0, sizeof(pProcInfo->cfg.debugStatusInfo));
				  pQyMc->env.bDebugInfo = false;
				  pProcInfo->cfg.dwRefreshedTickCnt_debugStatusInfo = 0;
				  //
				  showInfo_open0(0, 0, _T("too long from last refreshed, clear debugStatusInfo"));
			  }
		  }
	  }

	  //
	  if (!(var.loopCtrl % 3)) {
		  bool  bOnline = bMisCntOnline(pQyMc, pMisCnt);
		  //
#ifdef  __DEBUG__
		  //
#endif
		  //
		  if  (  bOnline  ) {
			  m_var.connection.status.nTimes_toWaitForConnection = 0;
		  }
		  else {
			  m_var.connection.status.nTimes_toWaitForConnection++;
			  //
			  _sntprintf(tBuf, mycountof(tBuf), _T("not online, nTimes_toWait %d"), m_var.connection.status.nTimes_toWaitForConnection);
			  showInfo_open0(0, 0, tBuf);
		  }
		  if (m_var.connection.status.nTimes_toWaitForConnection > 5) {
			  _sntprintf(tBuf, mycountof(tBuf), _T("not online, nTimes_toWait %d. quitApp now"), m_var.connection.status.nTimes_toWaitForConnection);
			  showInfo_open0(0, 0, tBuf);
			  notifyPanicToApp(pQyMc, 0, _T("not online too long"));
			  goto  errLabel;
		  }

	  }


	  //
	  if (pProcInfo->av.doConf.bStartToQuitApp) {
		  MIS_CHANNEL* pChannel = getChannelByType(pMisCnt, 0);
		  if (pChannel == NULL)  goto  errLabel;
		  //
		  if (isQEmpty(&pProcInfo->mgrQ)
			  && isQ2Empty(&pChannel->toSendQ2)
			  && isQ2Empty(&pChannel->outputQ2)
			  )
		  {
			  showInfo_open0(0, NULL, _T("everything is sent, quitApp now"));
			  notifyPanicToApp(pQyMc, 0, _T("doConf.bStartToQuitApp is true"));
			  goto  errLabel;
		  }
		  //
		  showInfo_open0(0, NULL, _T("bStartToQuitApp is true, but something is not sent, wait ..."));
	  }



	  //
	  iErr = 0;
	
  errLabel:
	  return  iErr;
  }



  //
  int  CCtxQmc_qyMcu::removeMosaicFromD3dWall(  int  iIndex_sharedObj  )
  {
	  return  ::dyn_removeMosaicFromD3dWall(  this,  iIndex_sharedObj  );
  }
	
  int  CCtxQmc_qyMcu::getVal_bExists_mosaic(  int  iIndex_sharedObj,  BOOL  *  pbExists  )
  {
	  return  ::dyn_getVal_bExists_mosaic(  this,  iIndex_sharedObj,  pbExists  );
  }

  //
  int  CCtxQmc_qyMcu::stopLocalAudioRecorder(  int  index_sharedObj,  int  nTries  )   
  {  
	  return  ::stopLocalAudioRecorder(  this,  index_sharedObj,  nTries  );  
  }


  //  		
  int  CCtxQmc_qyMcu::stopMosaicThreads(  QMC_mosaic_maker  *  pMosaic  ) 
  {  
	  return ::stopMosaicThreads(pMosaic);
  }

  //
  int  CCtxQmc_qyMcu::setFlg_inConfMosaic(  HWND  hDlg,  int  iWndContentType,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr  )
  {
	  return ::setFlg_inConfMosaic(  hDlg,  iWndContentType,  iIndex_sharedObj,  iIndex_sharedObjUsr  );
  }

  //
  int  CCtxQmc_qyMcu::makeMosaicStream(  HWND  hDlg,  int  iTaskId,  int  level,  AV_COMPRESSOR_CFG  *  pCompressor_conf,  AV_COMPRESSOR_CFG  *  pCompressor_resource,  int  iFourcc_resource,  QMC_mosaic_maker  *  pMosaic  )
  {
	  return ::makeMosaicStream(  hDlg,  iTaskId,  level,  pCompressor_conf,  pCompressor_resource,  iFourcc_resource,  pMosaic  );
	  //return 0;
  
  }


  //
  int  CCtxQmc_qyMcu::openLocalVideo_mosaic(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiCamCapType,  BITMAPINFOHEADER  *  pBih_photomosaic,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressorParam,  int  iIndex_sharedObj  ) 
  {
	  return ::openLocalVideo_mosaic(pProcInfoCommon,uiCamCapType,pBih_photomosaic,pVideoCompressorParam,iIndex_sharedObj);
  }


  //
  bool CCtxQmc_qyMcu::myDestroyWindow(HWND  hWnd)
  {
	  return  ::DestroyWindow(hWnd);
  }






  int CCtxQmc_qyMcu::sxrz_yq(QIS_ca_req* p) 	//  双向认证，客户端验签
  {
	  int  iErr = -1;


	  //
	  if (p->sHgCmd == CONST_hgCmd_hk) {
		  int  ii = 0;
	  }

	  //
	  Param_sxrz_servReply param;
	  memset(&param, 0, sizeof(param));
	  //
	  if (parseHgCmd_sxrz_servReply(p->ca_servData, p->ca_servDataLen, 0, &param))  goto  errLabel;

	  //
	  if (param.cmd_org == CONST_hgCmd_mcuXt) {
		  //
		  mcuProc_xt_resp(&param);
		  //
		  iErr = 0;  goto  errLabel;
	  }



	  //
	  iErr = 0;
  errLabel:
	  //
	  return  iErr;
  }


  //
  int  CCtxQmc_qyMcu::do_talk_OnTimer(HWND  hTalk,void  *  pDLG_TALK_var)
  {
	  int  iErr = -1;

	  DLG_TALK_var* pm_var = (DLG_TALK_var*)pDLG_TALK_var;
	  if (!pm_var)  return  -1;
	  DLG_TALK_var& m_var = *pm_var;
	  
	  //
	  if (isTalkerShadowMgr(m_var.addr)) {
		  if (m_var.av.taskInfo.bTaskExists) {
			  //
#if 0
			  TCHAR  tBuf[128];
			  _sntprintf(tBuf, mycountof(tBuf), _T("1178.initiator %I64u"), m_var.av.taskInfo.idInfo_initiator.ui64Id);
			  showInfo_open0(0, 0, tBuf);
#endif

			  //
			  if (!m_var.av.taskInfo.idInfo_initiator.ui64Id) {		//  为0表示是从会管发起的
				  
				  //
				  mcu_send_xt(m_var.loopCtrl_timer, m_var.addr.idInfo);
				  //
			  }
		  }

	  }



	  iErr = 0;
	  return  iErr;
  }


  //
  int  CCtxQmc_qyMcu::tmpHandler_showMsg_task(void* hDlgTalkParam, void* pDLG_TALK_var, void* p1, void* pMsgParam)
  {
	  if (!pDLG_TALK_var) return  -1;
	  DLG_TALK_var& m_var = *(DLG_TALK_var*)pDLG_TALK_var;

	  return  ::tmpHandler_showMsg_task_qyMcu(hDlgTalkParam, m_var, p1, pMsgParam);

  }



  int  CCtxQmc_qyMcu::sendConfKey(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint) 
  { 
	  return  ::sendConfKey(hDlgTalk,idInfo_to,hint);
  }


  int  CCtxQmc_qyMcu::sendStatusConfLayoutParam(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint)
  {
	  return  ::sendStatusConfLayoutParam(hDlgTalk, idInfo_to, hint);
  }
