// DlgMcClientLogon.cpp : implementation file
//

#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#ifdef  __WINCE__
	#ifndef  __TEST__
		#include	"ceMenuBar.h"
	#endif
#endif

#include	"myresource.h"

#include	"DlgMcClientLogon.h"
#include	"DlgQnmCfgOptionsIsClient.h"
#include	"qyCusResTemp.h"

#include	"ctxQmc.h"
#include	"qmcCommFunc_isCli.h"


extern  "C"  BOOL  bServConnected_mis(  QY_ENV  *  pEnv,  char  *  serverIp,  unsigned  short  serverPort,  void  *  pParam,  int  serviceId,  char  *  ver,  QY_ENC_CTX  *  pCommEncCtx,  __int64  i64StartTime_base,  SOCK_TIMEOUT  *  pTo  );

//
void  *  newQyWnd_CDlgMcClientLogon(  )
{
	CQyWnd	*	pWnd	=	NULL;
	int  iWndContentType  =  CONST_qyWndContentType_mcClientLogon;

#include	"unDeclareDebugNew.h"
	pWnd  =  new  CDlgMcClientLogon;
#include	"declareDebugNew.h"
	
	if  (  pWnd  )  pWnd->m_var.iWndContentType  =  iWndContentType;

	return  pWnd;
}

 //  2019/04/09

 BOOL  bAutoRun(  BOOL  ucbAutoLogon,  int iServerNo,  TCHAR  * pUsr,  TCHAR  * pPasswd  )
{
	BOOL			bRet			=	FALSE;
	
	HKEY			hKey;
	QY_MC		*	pQyMc			=	(  QY_MC  *  )g_pQyMc;
	TCHAR			tmpFileName[MAX_PATH  +  1];
	
	//
	if (iServerNo)  return  false;

	//
	if (!ucbAutoLogon) {
		  //  2019/04/20
		if (RegOpenKey(HKEY_CURRENT_USER, pQyMc->env.svRunKey, &hKey) == ERROR_SUCCESS) {

			LONG  iERROR_SUCCESS;
			iERROR_SUCCESS = RegDeleteValue(hKey, _T(CONST_exeName_qyMessenger));
						
			RegCloseKey(hKey);		

		}
	}
	else {

		if (RegOpenKey(HKEY_CURRENT_USER, pQyMc->env.svRunKey, &hKey) != ERROR_SUCCESS)  goto  errLabel;

		TCHAR		tPathBuf[MAX_PATH + 1];
		TCHAR* pFilePort;
		int			iLen;


		GetModuleFileName(NULL, tmpFileName, mycountof(tmpFileName));

#if  0
		GetFullPathName(tmpFileName, mycountof(tPathBuf), tPathBuf, &pFilePort);
		pFilePort[0] = 0;

		_sntprintf(tmpFileName, mycountof(tmpFileName), _T("\"%s%s.exe\""), tPathBuf, _T(CONST_exeName_qyMessenger));
#endif
		_sntprintf(tPathBuf, mycountof(tPathBuf), _T("\"%s\""), tmpFileName);
		_sntprintf(tmpFileName, mycountof(tmpFileName), _T("%s"), tPathBuf);

		//
		_sntprintf(tmpFileName, mycountof(tmpFileName), _T("%s -aqm%d -u%s -p%s"), tmpFileName, iServerNo, pUsr, pPasswd);

		iLen = (lstrlen(tmpFileName) + 1) * sizeof(TCHAR);

		if (pUsr[0] && pPasswd[0]) {
			if (RegSetValueEx(hKey, _T(CONST_exeName_qyMessenger), 0, REG_SZ, (const BYTE*)tmpFileName, iLen) != ERROR_SUCCESS);
		}
		RegCloseKey(hKey);

	}

	bRet  =  TRUE;
errLabel:

	if  (  !bRet  )  {
	}

	return  bRet;
}



#if 0
 //int  doMisCntLogon(  MIS_CNT  *  pMisCnt,  MIS_CHANNEL  *  pChannel,  HWND    hDlg,  DLG_mcClientLogon_var  &  m_var  )
 int  iidoMisCntLogon(  MIS_CNT  *  pMisCnt,  MIS_CHANNEL  *  pChannel,  HWND    hDlg,  TCHAR  *  respHint,  int  cntof_respHint  )
{
	int				iErr			=	-1;
	if  (  !pMisCnt  )  return  -1;
	MC_VAR_isCli		*	pProcInfo		=	(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	QY_MC				*	pQyMc			=	(  QY_MC  *  )pProcInfo->pQyMc;
	QY_SERVICEGUI_INFO	*	pSci	=	(  QY_SERVICEGUI_INFO  *  )pProcInfo->pSgiParam;
	BOOL					bCryptInited	=	FALSE;
	int						i;
	TCHAR					tBuf[256];

	memset(  &pChannel->commEncCtx,  0,  sizeof(  pChannel->commEncCtx  )  );
	memcpy(  &pChannel->commEncCtx.common,  &pMisCnt->commEncCtx.common,  sizeof(  pChannel->commEncCtx.common  )  );
	bool  bMachineKey  =  bUseMachineKey_qmc(  );
	if  (  initCrypt_qmc(  pProcInfo,   pMisCnt,  pProcInfo->cspContainer_qmc,  get_DEFAULT_cspProvider(),  bMachineKey,  (  pChannel->uiType  ==  CONST_channelType_talking  ),  &pChannel->commEncCtx  )  )  goto  errLabel;
	bCryptInited  =  TRUE;
	//

	_sntprintf(  pChannel->commEncCtx.mutexName_syncCrypt_e,  mycountof(  pChannel->commEncCtx.mutexName_syncCrypt_e  ),  _T(  "qmcCrypt%u-%u-e"  ),  GetCurrentProcessId(),  getuiNextTranNo(  0,  0,  0  )  );
	//_sntprintf(  pChannel->commEncCtx.mutexName_syncCrypt_d, mycountof(pChannel->commEncCtx.mutexName_syncCrypt_d), _T("qmcCrypt%u-%u-d"), GetCurrentProcessId(), getuiNextTranNo(0, 0, 0));

	//  2011/02/02
	pProcInfo->authInfo.uiLogonId  =  0;

	//
	pChannel->curServer = pMisCnt->server;

	//
	int  iMaxTriesToStartSession_mis = CONST_maxTriesToStartSession_mis;
	//
	//iMaxTriesToStartSession_mis = 1;
	//  
	for  (  i  =  0;  i  <  iMaxTriesToStartSession_mis;  i  ++  )  {
		 //
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s, %d..."  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_tryToConnect  ),  CQyString(  pMisCnt->server.ip  ),  i  );
		 //m_var.guiData.pf_SetDlgItemText(  hDlg,  m_var.guiData.iIDC_STATIC_hint,  tBuf  );
		 //
		 if (!tryToStartChannel(pMisCnt, pChannel, respHint, cntof_respHint)) {
			 break;
		 }
	}
	if  (  i  ==  iMaxTriesToStartSession_mis  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  "Logon"  ),  _T(  ""  ),  _T(  "failed"  )  );
		goto  errLabel;
	}	
	pChannel->status.ulbSessionErr  =  FALSE;
	//

	iErr  =  0;

errLabel:

	pChannel->status.ulbSessionErr  =  TRUE;	//  此标志位通知recv和snd两线程退出

	if  (  pChannel->bSessionOpen  )  {
			traceLogA(  (char*)  "to close session"  );			
			qnmCloseSession_msg(  &pChannel->session,  &pChannel->sock,  &pQyMc->cfg.to  );
			pChannel->bSessionOpen  =  FALSE;
			traceLogA(  (char*)  "session closed"  );	

			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  "Logon"  ),  _T(  ""  ),  _T(  "Session is closed"  )  );

	}
	if  (  bCryptInited  )  exitCrypt_qmc(  pProcInfo,  pMisCnt,  &pChannel->commEncCtx  );
	
	pChannel->status.ulbIoQuit  =  TRUE;

	return  iErr; 
}
#endif





 int dlgMcClientLogon_bNotSeleceted(  HWND  hDlg,  void  *  pVarParam  )
{
	if  (  !pVarParam  )  return  -1;
	DLG_mcClientLogon_var	&	m_var	=	*(  DLG_mcClientLogon_var  *  )pVarParam;

	QY_MC	*	pQyMc					=	m_var.guiData.pQyMc;
	HKEY		hKeyRoot0				=	HKEY_CURRENT_USER;
	TCHAR		tQnmSchedulerBuf[256]	=	_T(  ""  );	
	TCHAR		tBuf[16]				=	_T(  ""  );
	int			i						=	0;

	for  (  i = 0; i < CONST_maxOfVideoConferencingServers;  i  ++  )  {
		 if  (  !i  )  
			 _sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  )  );
		 else 
			 _sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s\\%d"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  i  );

		 qyDelRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_bSelected  )  );
	}
	return  0;
}

 __declspec(  dllexport  )  int	 dlgMcClientLogon_refresh(  HWND  hDlg  )
{
	int							iErr					=	-1;
	CDlgMcClientLogon		*	pDlg					=	(  CDlgMcClientLogon  *  )CDlgMcClientLogon::FromHandle(  hDlg  );
	DLG_mcClientLogon_var	&	m_var					=	pDlg->m_var;
	//
	QY_MC					*	pQyMc					=	m_var.guiData.pQyMc;
	if  (  !pQyMc  )  return  -1;
	TCHAR						tBuf[255  +  1]			=	_T(  ""  );
	HKEY						hKeyRoot0				=	HKEY_CURRENT_USER;
	TCHAR						tQnmSchedulerBuf[256]	=	_T(  ""  );	
	//  char						buf[256]				=	"";
	int							i,j;
	CQyString					str						=  _T(  ""  );
	
	if  (  getLogonServerCfg(  pQyMc,  m_var.cntCfg,  0,  m_var.seqNo,  m_var.cntName[0],  mycountof(  m_var.cntName[0]  )  )  >  0  )
		m_var.usItemCount  = 1;
#ifdef  __SUPPORT_MULTILOGON__
	    for (  int serverIndex = 1;  serverIndex <  CONST_maxOfVideoConferencingServers; serverIndex ++  )  {
			if  (  getLogonServerCfg(  pQyMc,  m_var.cntCfg,  serverIndex,  m_var.seqNo,  m_var.cntName[serverIndex],  mycountof(  m_var.cntName[0]  )  )  >  0  )
				m_var.usItemCount  ++;
		}

	//  CComboBox m_logonServer;
	HWND	m_logonServer	=	GetDlgItem(  pDlg->m_hWnd,  m_var.guiData.iIDC_COMBO_logonServer  );
	if  (  m_logonServer  )  {
		SendMessage(  m_logonServer,  CB_RESETCONTENT,  0,  0  );

		for  (  i = 0,j = 0;  i <  CONST_maxOfVideoConferencingServers;  i ++  )  {
			if  (  !m_var.usItemCount  )  break;
			if  (  ( !i || m_var.seqNo[i]  )  )  {
				//  str.Format(  _T("%s"),  m_var.cntName[i]  );
				str  =  m_var.cntName[i];
				//  m_logonServer.InsertString(  j,  str  );
				SendMessage(  m_logonServer,  CB_INSERTSTRING,  j,  (  LPARAM  )str.GetBuffer(  )  );
				j ++;
				if (  j > m_var.usItemCount  )  break;
			}
		}
	}

	for  (  i = 0; i < CONST_maxOfVideoConferencingServers;  i ++  )  {
		 if  (  !i  )  _sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  )  );
		 else _sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s\\%d"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  i  );

		 qyGetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_bSelected  ),  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  );
		 if  (  _ttoi(  tBuf  )  ==  1  )  break;
	}
	if  (  i == CONST_maxOfVideoConferencingServers  )  i  =  0;
	m_var.iSeqNoSelected  =  i;
	//
	qyGetRegCfg1W(  &pQyMc->env, hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_cntName  ),  tBuf,  mycountof(  tBuf  ),  0  );
	if  (  m_logonServer  )  {
		i  =  SendMessage(  m_logonServer,  CB_FINDSTRING,  0,  (  LPARAM  )tBuf  );
		SendMessage(  m_logonServer,  CB_SETCURSEL,  i,  0  );
	}
#else
	m_var.iSeqNoSelected  =  0;
#endif
		
	memcpy(  &pQyMc->cfg.dynCfg.cnt,  &m_var.cntCfg[m_var.iSeqNoSelected],  sizeof(  QNM_CNT_CFG  )  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Server: %s, %s, %s; Port: %d"  ),  
		CQyString(  m_var.cntCfg[m_var.iSeqNoSelected].cntIp  ), 	
		CQyString(  m_var.cntCfg[m_var.iSeqNoSelected].cntAddrs[0]  ),  
		CQyString(  m_var.cntCfg[m_var.iSeqNoSelected].cntAddrs[1]  ),  
		m_var.cntCfg[m_var.iSeqNoSelected].usCntPort  );
	m_var.guiData.pf_SetDlgItemText(  pDlg->m_hWnd,  m_var.guiData.iIDC_STATIC_hint,  tBuf  );
	//

	//  2019/04/08
	tBuf[0] = 0;
	qyGetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_usr  ),  (  char  *  )tBuf,  mycountof(  tBuf  ),  0  );
	SetDlgItemText(  pDlg->m_hWnd,  m_var.guiData.iIDC_NAME,  tBuf  );
	_sntprintf(  m_var.cntCfg[m_var.iSeqNoSelected].usr,  mycountof(  m_var.cntCfg[m_var.iSeqNoSelected].usr  ),  _T(  "%s"  ),  tBuf  );
	tBuf[0] = 0;
	qyGetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_passwd  ),  (  char  *  )tBuf,  mycountof(  tBuf  ),  0  );
	SetDlgItemText(  pDlg->m_hWnd,  m_var.guiData.iIDC_PASSWD,  tBuf  );
	_sntprintf(  m_var.cntCfg[m_var.iSeqNoSelected].passwd,  mycountof(  m_var.cntCfg[m_var.iSeqNoSelected].passwd  ),  _T(  "%s"  ),  tBuf  );
		
	tBuf[0] = 0;
	qyGetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_ucbAutoLogon  ),  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  );
	if  (  _ttoi(  tBuf  )  ==  1  )  {
		m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon  =  1;
		HWND  hCtrl  =  GetDlgItem(  pDlg->m_hWnd,  m_var.guiData.iIDC_CHECK_autoLogon  );
		SendMessage(  hCtrl,  BM_SETCHECK,  BST_UNCHECKED,  0  );
	}
	else  {
		m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon  =  0;
		HWND  hCtrl  =  GetDlgItem(  pDlg->m_hWnd,  m_var.guiData.iIDC_CHECK_autoLogon  );
		SendMessage(  hCtrl,  BM_SETCHECK,  BST_CHECKED,  0  );
	}

	bAutoRun(  m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon,  m_var.iSeqNoSelected,  m_var.cntCfg[m_var.iSeqNoSelected].usr,  m_var.cntCfg[m_var.iSeqNoSelected].passwd  );

	iErr  =  0;

errLabel:

	return  iErr;

}



CDlgMcClientLogon::CDlgMcClientLogon(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgMcClientLogon::~CDlgMcClientLogon()
{
}

BOOL CALLBACK myEnumWindowsProc_singleInstance(  HWND hwnd,  LPARAM lParam  )
{
	BOOL	bRet	=	TRUE;
	COMMON_PARAM	*	pParam	=	(  COMMON_PARAM  *  )lParam;
	//
	TCHAR	*	lckCStr  =  (  TCHAR  *  )pParam->p1;
	HWND	*	phWnd	=	(  HWND  *  )pParam->p2;


	if  (  GetProp(  hwnd,  lckCStr  )  )  {
		//  myMessageBox(  NULL,  _T(  "Found"  ),  _T(  ""  ),  MB_OK  );
		*phWnd  =  hwnd;
		bRet  =  FALSE;  goto  errLabel;
	}

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


__declspec(  dllexport  )  int dlgMcClientLogon_OnInitDialog(  HWND  hDlg,  void  *  pVarParam  )
{

	// TODO:  Add extra initialization here
	int					iErr					=	-1;
	if  (  !pVarParam  )  return  -1;
	DLG_mcClientLogon_var	&	m_var  =  *(  DLG_mcClientLogon_var  *  )pVarParam;

	QY_MC			*	pQyMc					=	m_var.guiData.pQyMc;
	if  (  !pQyMc  )  return  -1;
	CQyString			titleCStr;
	char				buf[128]				=	"Logon"  ;
	cusDlgRes(  0,  &pQyMc->cusRes,  hDlg,  IDD_mcClient_logon  );

	if  (  !m_var.guiData.pf_GetDlgItemText  ||  !m_var.guiData.pf_SetDlgItemText  )  {
		OutputDebugString(  _T(  "logon failed: pf_GetDlgItemText or pf_SetDlgItemText is null\n"  )  );
		goto  errLabel;
	}

	//  2014/02/09
	BOOL  bNeedLock  =  TRUE;
	if  (  pQyMc->appParams.appObjPrefix[0]  &&  pQyMc->appParams.usrName[0]  &&  pQyMc->appParams.passwd[0]  )  {
		bNeedLock  =  FALSE;
	}

	//  2010/07/11
	if  (  bNeedLock  )  {
	if  (  pQyMc->cfg.singleInstanceStr[0]  )  {
		CQyString	lckCStr;

		lckCStr = CQyString(  (char*)CONST_mutexPrefix_mcClientLogon  )  +  CQyString(  pQyMc->cfg.singleInstanceStr  );
		m_var.hMutex_singleInstance  =  CreateMutex(  NULL,  FALSE,  lckCStr  );
		if  (  !m_var.hMutex_singleInstance  )  {
			traceLog((TCHAR*)  _T(  "singleInstance failed, null."  )  );			
			goto  errLabel;				
		}
		if  (  GetLastError(  )  ==  ERROR_ALREADY_EXISTS  )  {
			traceLog((TCHAR*)  _T(  "singleInstance failed, already exists."  )  );

			COMMON_PARAM	commonParam;
			HWND	hPrevWnd	=	NULL;

			MACRO_makeCommonParam3(  0,  (  void  *  )lckCStr.GetBuffer(  ),  &hPrevWnd,  commonParam  );
			EnumWindows(  myEnumWindowsProc_singleInstance,  (  LPARAM  )&commonParam  );

			if  (  IsWindow(  hPrevWnd  )  )  {
#if  10
				//  if  (  IsIconic(  hPrevWnd  )  )  ShowWindow(  hPrevWnd,  SW_RESTORE  );
				ShowWindow(  hPrevWnd,  SW_SHOWNORMAL  );
			    #if !defined(  __WINCE__  )  ||  defined(  __TEST__  )
								SetForegroundWindow(  hPrevWnd  );
								SetForegroundWindow(  GetLastActivePopup(  hPrevWnd  )  );
				#else
								SetForegroundWindow((HWND)(((ULONG) hPrevWnd) | 0x01) );
				#endif
#else
				//  2017/01/05
				SendMessage(  hPrevWnd,  WM_COMMAND,  MAKEWPARAM(  ID_qyShowWnd,  0  ),  0  );
#endif
			}

			goto  errLabel;
		}

		//
		if  (  !IsWindow(  hDlg  )  )  goto  errLabel;
		if  (  !SetProp(  hDlg,  lckCStr,  (  HANDLE  )1  )  )  goto  errLabel;
	}
	}

	//
#ifndef  __APP_qyMc_touchscreen__
		 centerWnd(  hDlg  );
#endif
	::SetWindowPos(  hDlg,  HWND_TOPMOST,  0,  0,  0,  0,  SWP_NOMOVE  |  SWP_NOSIZE  );

	titleCStr  =  CQyString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_logon_wndTitle  )  );
	//  titleCStr  +=  CQyString(  getResStr(  0,  &pQyMc->cusRes,  IDD_mcClient_logon  )  );
	titleCStr  =  pQyMc->cfg.qyMcTitle;
	SetWindowText(  hDlg,  titleCStr  );  
	//	
	SendMessage(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_NAME  ),  EM_SETLIMITTEXT,  16,  0  );
	SendMessage(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_PASSWD  ),  EM_SETLIMITTEXT,  16,  0  );

	//
	SetFocus(  hDlg  );

	dlgMcClientLogon_refresh(  hDlg  );

#ifdef  __SUPPORT_getUsrPasswdFromIni__

		if  (  pQyMc->cfg.bGetPolicyFromIni  )  {
			    traceLogA(  (char*)  "Warning: simulate to login"  );
				if  (  !getCfgValByName(  pQyMc->cfg.iniFullFileName,  (char*)CONST_regValName_usr,  buf,  sizeof(  buf  )  )  )  {
					trim(  buf  );
					if  (  buf[0]  )  {
						SetDlgItemText(  hDlg,  m_var.guiData.iIDC_NAME,  CQyString(  buf  )  );
					}
				}
				if  (  !getCfgValByName(  pQyMc->cfg.iniFullFileName,  (char*)CONST_regValName_passwd,  buf,  sizeof(  buf  )  )  )  {
					trim(  buf  );
					if  (  buf[0]  )  {
						SetDlgItemText(  hDlg,  m_var.guiData.iIDC_PASSWD,  CQyString(  buf  )  );
					}
				}
	 }

#endif
    
	//  2011/03/23
	m_var.uiTimerId  =  SetTimer(  hDlg,  1,  1000,  NULL  );

	//
	if  (  bSupported_devAuth(  )  )  {
		traceLog((TCHAR*)  _T(  "trigger IDOK."  )  );
			//  2019/04/20
			if  (  m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon  )  {
				PostMessage(  hDlg,  WM_COMMAND,  MAKEWPARAM(  IDOK,  0  ), 0  );
			}
		}
	else  {
		  if  (  pQyMc->appParams.appObjPrefix[0]  &&  pQyMc->appParams.usrName[0]  &&  pQyMc->appParams.passwd[0]  )  {	//  2014/02/09. 用命令行参数登录
			  HWND	m_logonServer	=	GetDlgItem(  hDlg,  m_var.guiData.iIDC_COMBO_logonServer  );
			  if  (  m_logonServer  )  {
				  SendMessage(  m_logonServer,  CB_SETCURSEL,  pQyMc->appParams.iSeqNoSelected_appObjPrefix,  0  );
				  //
				  dlgMcClientLogon_OnCbnSelchangeCombologonserver(  hDlg,  &m_var  );

			  }
			  SetDlgItemText(  hDlg,  m_var.guiData.iIDC_NAME,  pQyMc->appParams.usrName  );
			  SetDlgItemText(  hDlg,  m_var.guiData.iIDC_PASSWD,  pQyMc->appParams.passwd  );
			  //
			  traceLog((TCHAR*)  _T(  "trigger IDOK."  )  );
			//  2019/04/20
			if  (  m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon  )  {
				PostMessage(  hDlg,  WM_COMMAND,  MAKEWPARAM(  IDOK,  0  ), 0  );
			}
		  }
	}

	//  2019/04/08
	HWND  hCtrl  =  GetDlgItem(  hDlg,  m_var.guiData.iIDC_CHECK_savePasswd  );
	SendMessage(  hCtrl,  BM_SETCHECK,  BST_CHECKED,  0  );
	
	BOOL  bDisable_unchecked  =  FALSE;
	if  (  bDisable_unchecked  )  {
		EnableWindow(  hCtrl,  FALSE  );
	}

	//
	if  (  m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon  )  {
		PostMessage(  hDlg,  WM_COMMAND,  MAKEWPARAM(  IDOK,  0  ), 0  );
	}

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		//  EndDialog(  this->m_hWnd,  -1  );
	}

	return iErr;
}

 BOOL  bAnotherInstanceExists(  QY_MC  *  pQyMc,  LPCTSTR  appObjPrefix  )
{
	BOOL		bRet					=	FALSE;
	//
	if  (  !pQyMc  )  return  FALSE;
	//
	CQyString	lckCStr;
	HANDLE		hMutex_singleInstance	=	NULL;

	if  (  pQyMc->cfg.singleInstanceStr[0]  )  {

		#ifndef  __WINCE__
				 lckCStr = CQyString(  appObjPrefix  )  +  CQyString(  pQyMc->cfg.singleInstanceStr  );
		#else
				 lckCStr = CQyString(  CONST_mutexPrefix_mcClientLogon  )  +  pQyMc->cfg.singleInstanceStr;
		#endif
				
		hMutex_singleInstance  =  CreateMutex(  NULL,  FALSE,  lckCStr  );
		if  (  !hMutex_singleInstance  )  {				
			traceLog((TCHAR*)  _T(  "singleInstance failed, null."  )  );
			goto  errLabel;
		}
		if  (  GetLastError(  )  ==  ERROR_ALREADY_EXISTS  )  {
			traceLog((TCHAR*)  _T(  "singleInstance failed, already exists."  )  );

			COMMON_PARAM	commonParam;
			HWND	hPrevWnd	=	NULL;

			MACRO_makeCommonParam3(  0,  (  void  *  )lckCStr.GetBuffer(  ),  &hPrevWnd,  commonParam  );
			EnumWindows(  myEnumWindowsProc_singleInstance,  (  LPARAM  )&commonParam  );

			if  (  IsWindow(  hPrevWnd  )  )  {
#if  0
				//  if  (  IsIconic(  hPrevWnd  )  )  ShowWindow(  hPrevWnd,  SW_RESTORE  );
				ShowWindow(  hPrevWnd,  SW_SHOWNORMAL  );

				#if !defined(  __WINCE__  )  ||  defined(  __TEST__  )
					SetForegroundWindow(  hPrevWnd  );
					SetForegroundWindow(  GetLastActivePopup(  hPrevWnd  )  );
				#else
						SetForegroundWindow((HWND)(((ULONG) hPrevWnd) | 0x01) );
				#endif
#else
				//  2017/01/05
				SendMessage(  hPrevWnd,  WM_COMMAND,  MAKEWPARAM(  ID_qyShowWnd,  0  ),  0  );
#endif
			
			}

			bRet  =  TRUE;
			goto  errLabel;
		}

	}

errLabel:

	if (hMutex_singleInstance) {
		CloseHandle(hMutex_singleInstance);
	}

	return  bRet;
}



  void dlgMcClientLogon_OnTimer(  HWND  hDlg,  UINT_PTR nIDEvent)
{
	CDlgMcClientLogon		*	pDlg				=	(  CDlgMcClientLogon  *  )CDlgMcClientLogon::FromHandle(  hDlg  );
	DLG_mcClientLogon_var	&	m_var				=	pDlg->m_var;
	QY_MC					*	pQyMc				=	m_var.guiData.pQyMc;

	BOOL  bTrigger_logon  =  FALSE;

	//
	if  (  bSupported_devAuth(  )  )  bTrigger_logon  =  TRUE;

	//  2014/02/09. 对命令行参数登录，如果第一次登录失败，停在那里等手工登录就可以了。所以不需要在这里触发

	//
	if  (  bTrigger_logon  )  {
		if  (  m_var.bLogonFailed  )  {

			#ifdef  __DEBUG__	//  2014/02/09
					traceLog((TCHAR*)  _T(  "dlgMcClientLogon_OnTimer: bTrigger_logon"  )  );
			#endif

			//
			if  (  m_var.nTries_triggerIDOK  >  10  )  {
				SetDlgItemText(  hDlg,  m_var.guiData.iIDC_STATIC_hint,  _T(  "Logon failed, quit now"  )  );
				PostMessage(  hDlg,  WM_CLOSE,  0,  0  );
				return;
			}
			SetDlgItemText(  hDlg,  m_var.guiData.iIDC_STATIC_hint,  _T(  "Logon failed, try again"  )  );
			m_var.nTries_triggerIDOK  ++  ;
			m_var.bLogonFailed  =  FALSE;
			//  2019/04/20
			if  (  m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon  )  {
				PostMessage(  hDlg,  WM_COMMAND,  MAKEWPARAM(  IDOK,  0  ), 0  );
			}
			return;
		}
	}

	return;
}


__declspec(  dllexport  )  int  dlgMcClientLogon_OnOK(  HWND  hDlg,  LPTSTR  m_name,  LPTSTR  m_passwd  )
{
	int							iErr				=	-1;

	// TODO: Add your control notification handler code here
	CDlgMcClientLogon		*	pDlg				=	(  CDlgMcClientLogon  *  )CDlgMcClientLogon::FromHandle(  hDlg  );
	DLG_mcClientLogon_var	&	m_var				=	pDlg->m_var;
	TCHAR						tBuf[128];

	//
	QY_MC					*	pQyMc				=	m_var.guiData.pQyMc;
	MC_VAR_isCli			*	pProcInfo			=	(  MC_VAR_isCli  *  )pQyMc->get_pProcInfo(  );
	if  (  !pProcInfo  )  return  -1;
	if  (  pProcInfo->m_iCtxType  !=  CONST_ctxType_qmc  )  return  -1;

	//
	char						buf[1024]			=	"";
	unsigned  int				len;

	//
	TCHAR						appObjPrefix[16  +  1]	=	_T(  ""  );			//  2010/03/10

#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "dlgMcClientLogon_OnOK called"  )  );
#endif
				
	//  2014/02/09
	if  (  m_var.iSeqNoSelected  <  0  ||  m_var.iSeqNoSelected  >=  mycountof(  m_var.cntCfg  )  )  return  -1;

	//
	_sntprintf(  appObjPrefix,  mycountof(  appObjPrefix  ),  _T(  "%s%d"  ),  CONST_qmCmdLine_sym_appObjPrefix, m_var.iSeqNoSelected  );
	#ifndef  __WINCE__
			 if  (  bAnotherInstanceExists(  pQyMc,  appObjPrefix  )  )  goto  errLabel;
	#endif

	//
	TCHAR						tPrefix[32]			=	_T(  ""  );
	_sntprintf(  tPrefix,  mycountof(  tPrefix  ),  _T(  "%d: "  ),  m_var.nTries_triggerIDOK  );

	if  (  !bSupported_devAuth(  )  )  {

		if  (  !m_name  ||  !m_name[0]  )  goto  errLabel;
		if  (  !m_passwd  ||  !m_passwd[0]  )  goto  errLabel;

		tTrim(  m_name  );
		tTrim(  m_passwd  );
		//
		if  (  !m_name[0]  )  {
			SetFocus(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_NAME  )  );
			goto  errLabel;
		}
		if  (  !m_passwd[0]  )  {
			SetFocus(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_PASSWD  )  );
			goto  errLabel;
		}
	
		//
		lstrcpyn(  pProcInfo->authInfo.messengerName,  m_name,  mycountof(  pProcInfo->authInfo.messengerName  )  );
		myTChar2Utf8(  m_passwd,  buf,  mycountof(  buf  )  );
		len  =  mycountof(  pProcInfo->authInfo.messengerPasswd  );
		bQyGetStrMd5_x(  buf,  pProcInfo->authInfo.messengerPasswd,  &len  );
	}

	//  CWaitCursor		cur;
	
	//
	_sntprintf(  m_var.cntCfg[m_var.iSeqNoSelected].usr,  mycountof(  m_var.cntCfg[m_var.iSeqNoSelected].usr  ),  m_name  );
	_sntprintf(  m_var.cntCfg[m_var.iSeqNoSelected].passwd,  mycountof(  m_var.cntCfg[m_var.iSeqNoSelected].passwd  ),  m_passwd  );

	memcpy(  &pQyMc->cfg.dynCfg.cnt,  &m_var.cntCfg[m_var.iSeqNoSelected],  sizeof(  QNM_CNT_CFG  )  );

	//  2010/01/09
	{
	int  index  =  0;
	MIS_CNT  *  pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  index  );
	if  (  !pMisCnt  )  goto  errLabel;
	memcpy(  &pMisCnt->cfg.dynCfg,  &pQyMc->cfg.dynCfg,  sizeof(  pMisCnt->cfg.dynCfg  )  );
	memset(  &pMisCnt->server,  0,  sizeof(  pMisCnt->server  )  );
	}
	//
	int								i;
	QY_LOGICAL_SERVER				tmpCnt;

	//for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
	for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
	{
		 MIS_CNT  *  pMisCnt			=  getMisCntByIndex(  0,  pProcInfo,  i  );//&pProcInfo->misCnts[i];
		 if  (  !pMisCnt  )  continue;
		 MIS_CHANNEL	*	pChannel	=  getChannelByType(  pMisCnt,  CONST_channelType_talking  );
		 if  (  !pChannel  )  continue;

		 if  (  pChannel->bSessionOpen  )  {
			 qnmCloseSession_msg(  mynull, &pChannel->session,  &pChannel->sock,  &pQyMc->cfg.to,  _T("dlgmcClientLogon_OnOK.l710"));
			 pChannel->bSessionOpen  =  FALSE;
		 }

		 if  (  !pChannel->bSessionOpen  )  {
			 
			 pMisCnt->pAuthInfo  =  &pProcInfo->authInfo;
			 clearQySock(  &pChannel->sock  );

			 //  
			 {					   
				 if  (  pMisCnt->cfg.dynCfg.cnt.usCntPort  )  {
					 _sntprintf(  tBuf,  mycountof(  tBuf  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_searchingServer  )  );
					 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: %s, %s, %s; Port: %d"  ),  tBuf,
						 CQyString(  pMisCnt->cfg.dynCfg.cnt.cntIp  ), 	
						 CQyString(  pMisCnt->cfg.dynCfg.cnt.cntAddrs[0]  ),  
						 CQyString(  pMisCnt->cfg.dynCfg.cnt.cntAddrs[1]  ),  
						 pMisCnt->cfg.dynCfg.cnt.usCntPort  );
					 m_var.guiData.pf_SetDlgItemText(  pDlg->m_hWnd,  m_var.guiData.iIDC_STATIC_hint,  CQyString(  tPrefix  )  +  tBuf  );
					 if  (  getCorrectCnt(  &pQyMc->env,  &pMisCnt->cfg.dynCfg,  bServConnected_mis,  pMisCnt,  pQyMc->iServiceId,  qnmVerStr(  pQyMc->iServiceId  ),  &pMisCnt->commEncCtx.common,  pQyMc->i64StartTime_base,  &pQyMc->cfg.to,  &tmpCnt  )  )  {
						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotFindServer  )  );
						 m_var.guiData.pf_SetDlgItemText(  pDlg->m_hWnd,  m_var.guiData.iIDC_STATIC_hint,  CQyString(  tPrefix  )  +  tBuf  );
						 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "getCorrectCnt failed"  )  );
						 continue;
						 }
					 else  if  (  memcmp(  &pMisCnt->server,  &tmpCnt,  sizeof(  tmpCnt  )  )  )  {
							   memcpy(  &pMisCnt->server,  &tmpCnt,  sizeof(  pMisCnt->server  )  );
							   //
							   //pMisCnt->dualSystemHotBackup.dw1stMcuIp = inet_addr(tmpCnt.ip);
					 }					   
				 }		
			 }
			 if  (  !pMisCnt->commEncCtx.ucbPublicKeyDownloaded  ||  !pMisCnt->commEncCtx.ucbPublicKeyVerified  )  continue;

			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ok"  ),  CQyString(  pMisCnt->server.ip  )  );  
			 m_var.guiData.pf_SetDlgItemText(  pDlg->m_hWnd,  m_var.guiData.iIDC_STATIC_hint,  tBuf  );			 

			 m_var.respHint[0]  =  0;
			 if  (  !doMisCntLogon(  pMisCnt,  pChannel,  pDlg->m_hWnd,  m_var.respHint,  mycountof(  m_var.respHint  )  )  )  break;
		 
		 }

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s: %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_failedToLogon  ),  CQyString(  pMisCnt->server.ip  ),  m_var.respHint  );
		 m_var.guiData.pf_SetDlgItemText(  pDlg->m_hWnd,  m_var.guiData.iIDC_STATIC_hint,  CQyString(  tPrefix  )  +  tBuf  );

		 continue;
	}

	//if  (  i  ==  mycountof(  pProcInfo->misCnts  )  )  
	if  (  i  ==  pProcInfo->ucCnt_misCnts  )  
	{
		goto  errLabel;
	}

	pQyMc->curUsrInfo.right.bAdmin  =  TRUE;
	myTChar2Str(  m_name,  pQyMc->curUsrInfo.name,  sizeof(  pQyMc->curUsrInfo.name  )  );
	//  _sntprintf(  pQyMc->appObjPrefix,  mycountof(  pQyMc->appObjPrefix  ),  _T(  "qm%d"  ),  pDlg->m_var.iSeqNoSelected  );
	lstrcpyn(  pQyMc->appParams.appObjPrefix,  appObjPrefix,  mycountof(  pQyMc->appParams.appObjPrefix  )  );
	pQyMc->appParams.iSeqNoSelected_appObjPrefix  =  m_var.iSeqNoSelected;		//  2017/01/01

	//  2019/04/08
	int				iBST_UNCHECKED  =  0;
	HWND			hCtrl;
	HKEY			hKeyRoot0				=	HKEY_CURRENT_USER;
	TCHAR			tQnmSchedulerBuf[256]	=	_T(  ""  );	

	hCtrl  =  GetDlgItem(  hDlg,  m_var.guiData.iIDC_CHECK_savePasswd  );
	iBST_UNCHECKED  =  SendMessage(  hCtrl,  BM_GETSTATE, 0,  0  );
	m_var.cntCfg[m_var.iSeqNoSelected].ucbSavePasswd  =  iBST_UNCHECKED  ==  BST_CHECKED;

	//
	if  (  !m_var.iSeqNoSelected  )  	 
		_sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  )  );
	else 
		_sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s\\%d"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  m_var.iSeqNoSelected  );

	if  (  m_var.cntCfg[m_var.iSeqNoSelected].ucbSavePasswd  )  {
		qySetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_usr ),  m_name  );
		qySetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_passwd  ),  m_passwd  );
	}



	//
	unsigned char  ucbAutoLogon;
	hCtrl  =  GetDlgItem(  hDlg,  m_var.guiData.iIDC_CHECK_autoLogon  );
	iBST_UNCHECKED  =  SendMessage(  hCtrl,  BM_GETSTATE,  0,  0  );
	ucbAutoLogon  =  iBST_UNCHECKED  ==  BST_CHECKED;

	if  (  ucbAutoLogon  !=  m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon  )  {
		m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon  =  ucbAutoLogon;

		qySetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_ucbAutoLogon  ),  m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon  ?  _T(  "1"  ) :  _T(  "0"  )  );

	}

	bAutoRun(  m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon,  m_var.iSeqNoSelected,  m_var.cntCfg[m_var.iSeqNoSelected].usr,  m_var.cntCfg[m_var.iSeqNoSelected].passwd  );

#if  0
	if  (  ucbNoAutoLogon  )  {
		HKEY  hkResult;
		if  (  RegOpenKey(  hKeyRoot0,  _T(  CONST_exeName_qyMessenger  ),  &hkResult  )  ==  ERROR_SUCCESS  )  {
			RegDeleteValue(  hkResult,  _T(  CONST_exeName_qyMessenger  )  );
			RegCloseKey(  hkResult  );
		}
	}
#endif



	iErr  =  0;

errLabel:

	if  (  !iErr  )  {
		//  EndDialog(  pDlg->m_hWnd,  IDOK  );
	}
	if  (  iErr  )  {
		m_var.bLogonFailed  =  TRUE;
	}

	return  iErr;
}

 __declspec(  dllexport  )  int dlgMcClientLogon_OnDestroy(  HWND  hDlg,  void  *  pVarParam  )
{
	int				iErr	=	-1;
	if  (  !pVarParam  )  return  -1;
	DLG_mcClientLogon_var	&	m_var	=	*(  DLG_mcClientLogon_var  *  )pVarParam;

	QY_MC		*	pQyMc	=	m_var.guiData.pQyMc;
	CQyString		lckCStr;
	HANDLE			hRet	=	NULL;

	if  (  m_var.uiTimerId  )  KillTimer(  hDlg,  m_var.uiTimerId  );		//  2007/12/22

	lckCStr = CQyString(  (char*)CONST_mutexPrefix_mcClientLogon  )  +  CQyString(  pQyMc->cfg.singleInstanceStr  );
	hRet  =  RemoveProp(  hDlg,  lckCStr  );

	if  (  m_var.hMutex_singleInstance  )  {
		 CloseHandle(  m_var.hMutex_singleInstance  );
		 m_var.hMutex_singleInstance  =  NULL;
	 }

	iErr  =  0;
	return  iErr;
}

__declspec(  dllexport  )  void dlgMcClientLogon_OnCbnSelchangeCombologonserver(  HWND  hDlg,  void  *  pVarParam  )
{
	if  (  !pVarParam  )  return;
	DLG_mcClientLogon_var	&	m_var	=	*(  DLG_mcClientLogon_var  *  )pVarParam;

	// TODO: Add your control notification handler code here
	QY_MC	*	pQyMc					=	m_var.guiData.pQyMc;
	HKEY		hKeyRoot0				=	HKEY_CURRENT_USER;
	TCHAR		tQnmSchedulerBuf[256]	=	_T(  ""  );	
	TCHAR		tBuf1[256]				=	_T(  ""  );	
	TCHAR		tBuf2[256]				=	_T(  ""  );
	char		buf[256]				=	"";
	int			i						=	0;


	HWND	m_logonServer	=	GetDlgItem(  hDlg,  m_var.guiData.iIDC_COMBO_logonServer  );
	if  (  !m_logonServer  )  return;

	if  (  (  i = SendMessage(  m_logonServer,  CB_GETCURSEL,  0,  0  )  )  ==  -1  )  return;

	//  m_logonServer.GetLBText(  i,  tBuf1  );
	SendMessage(  m_logonServer,  CB_GETLBTEXT,  i,  (  LPARAM  )tBuf1  );

	for  (  i = 0; i < CONST_maxOfVideoConferencingServers;  i ++  )  {
		if  (  !i  )  _sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf ),  _T(  "%s"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  )  );
		else  _sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s\\%d"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  i  );  

		qyGetRegCfg1W(  &pQyMc->env,  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_cntName  ),  tBuf2,  mycountof(  tBuf2  ),  0  );
		if  (  !_tcsncmp(  tBuf1,  tBuf2,  mycountof(  tBuf1  )  )  )  break;
	}
	if  (  i == CONST_maxOfVideoConferencingServers  )  i  =  0;
	m_var.iSeqNoSelected  =  i;
		
	//  memcpy(  &pQyMc->cfg.dynCfg.cnt,  &m_var.cntCfg[m_var.iSeqNoSelected],  sizeof(  QNM_CNT_CFG  )  );
	_snprintf(  buf,  sizeof(  buf  ),  "Server: %s, %s, %s; Port: %d",  
		m_var.cntCfg[m_var.iSeqNoSelected].cntIp, 	m_var.cntCfg[m_var.iSeqNoSelected].cntAddrs[0],  m_var.cntCfg[m_var.iSeqNoSelected].cntAddrs[1],  m_var.cntCfg[m_var.iSeqNoSelected].usCntPort  );
	SetDlgItemText(  hDlg,  m_var.guiData.iIDC_STATIC_hint,  CQyString(  buf  )  );
	//
	dlgMcClientLogon_bNotSeleceted(  hDlg,  pVarParam  );
	if  (  !m_var.iSeqNoSelected  )  
		_sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  )  );
	else 
		_sntprintf(  tQnmSchedulerBuf,  mycountof(  tQnmSchedulerBuf  ),  _T(  "%s\\%d"  ),  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  m_var.iSeqNoSelected  );
	_sntprintf(  tBuf1,  mycountof( tBuf1  ),  _T(  "%d"  ),  1  );
	qySetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_bSelected  ),  tBuf1  );
	//
	//  2019/04/08
	tBuf1[0] = 0;
	qyGetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_usr  ),  (  char  *  )tBuf1, mycountof(  tBuf1  ),  0  );
	memcpy(  m_var.cntCfg[m_var.iSeqNoSelected].usr,  tBuf1,  mycountof(  tBuf1  )  );
	SetDlgItemText(  hDlg,  m_var.guiData.iIDC_NAME,  m_var.cntCfg[m_var.iSeqNoSelected].usr  );
	tBuf1[0] = 0;
	qyGetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_passwd  ),  (  char  *  )tBuf1, mycountof(  tBuf1  ),  0  );
	memcpy(  m_var.cntCfg[m_var.iSeqNoSelected].passwd,  tBuf1,  mycountof(  tBuf1  )  );
	SetDlgItemText(  hDlg,  m_var.guiData.iIDC_PASSWD,  m_var.cntCfg[m_var.iSeqNoSelected].passwd  );
	//
	tBuf1[0]  =  0;
	qyGetRegCfgT(  hKeyRoot0,  tQnmSchedulerBuf,  _T(  CONST_regValName_ucbAutoLogon  ),  (  char  *  )tBuf1,  mycountof(  tBuf1  ),  0  );
	if  (  _ttoi(  tBuf1  )  ==  1  )  {
		m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon  =  1;
		HWND  hCtrl  =  GetDlgItem(  hDlg,  m_var.guiData.iIDC_CHECK_autoLogon  );
		SendMessage(  hCtrl,  BM_SETCHECK,  BST_CHECKED,  0  );
	}
	else  {
		m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon  =  0;
		HWND  hCtrl  =  GetDlgItem(  hDlg,  m_var.guiData.iIDC_CHECK_autoLogon  );
		SendMessage(  hCtrl,  BM_SETCHECK,  BST_UNCHECKED,  0  );
	}

	bAutoRun(  m_var.cntCfg[m_var.iSeqNoSelected].ucbAutoLogon,  m_var.iSeqNoSelected,  m_var.cntCfg[m_var.iSeqNoSelected].usr,  m_var.cntCfg[m_var.iSeqNoSelected].passwd  );

}







