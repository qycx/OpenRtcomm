

#include	"stdafx.h"

#include	<ShellAPI.h>
#include	<stddef.h>
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"qyCusResTemp.h"

#ifndef  __NOTSUPPORT_MULTIDOC__
#ifndef  __useQt__
	#include	"mainClient.h"
	#include	"mainFrm.h"
#endif
#endif
#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	"qmcVideoCapture_isCli.h"
#include	"funcsForIsCliHelp.h"

#include	"myresource.h"

#if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
#ifdef  __WINCE__
		#ifndef  __TEST__
				 #include	"ceMenuBar.h"
		#endif
		#include	"dlgTalk_ce.h"
#else
//		#include	"myHtmlEditCtrl.h"		 
//		#include	"DlgTalk.h"
		#include	"DlgTalkproc.h"
#endif
#endif
#include	"QyPlaySound_wave.h"
#include	"qmcDxSurfacePublic.h"
#include	"qyWnd.h"

#include	"dlgMcClientLogon.h"
#ifdef  __WINCE__
		#include	"dlg_qyMc_winCe.h"
		#include	"dlgObjs.h"
#endif
#if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
#include	"DlgQnmCfgOptionsIsClient.h"
//  #include	"DlgInstantAssistant.h"
#endif
#include	"module_qisCamCap.h"

#if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
#ifndef  __NOTSUPPORT_MULTIDOC__
#ifndef  __useQt__
		 #include	"dlgNotification.h"
#endif
#endif
#endif

//  
#include	"myDb.h"
#include	"isCliHelpPublic.h"
#include	"isCliD3dPublic.h"
#include	"qyMessengerHelpPublic.h"
#include	"qmcCommFunc_isCli.h"
#include	"dyn_isCliD3d_public.h"

#include	"avConsole_open.h"
#include <GuiShare.h>
#include <string>
#include	"smLoginProc.h"



//
extern QYMC_HOTKEY	gHotKeys_main[];


//
class  CObj_gGuiData	{
public:
		G_guiData_qyMc	m_var;
		//
		CObj_gGuiData(  )  {  memset(  &m_var,  0,  sizeof(  m_var  )  );  }
}	gObj_gGuiData;
 
 G_guiData_qyMc  *  get_g_guiData(  )
{
	return  &gObj_gGuiData.m_var;
}



 __declspec(  dllexport  )  int  initVar_onCreate_mainFrame(  void  *  p0,  HWND  hMainWnd,  void  *  pVarParam  )
{
	 int							iErr				=	-1;
	 QY_MC_mainWndVar		*		pVar				=	(  QY_MC_mainWndVar  *  )pVarParam;

#ifdef  __DEBUG__
	 traceLogA(  (char*)  "initVar_onCreate_mainFrame enters."  );
#endif

	 //
	 if  (  !hMainWnd  ||  !pVar  )  return  -1;

	 QY_MC					*		pQyMc				=	pVar->pQyMc;
	 if  (  !pQyMc  )  return  -1;
	 MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pQyMc->get_pProcInfo(  );
	 if  (  !pProcInfo  )  return  -1;
	 if  (  pProcInfo->m_iCtxType  !=  CONST_ctxType_qmc  )  return  -1;


	 //	 
	 QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  &pQyMc->cusRes  );
	 if  (  !pResMem  )  goto  errLabel;
	 
	 //
	 pQyMc->gui.hMainWnd  =  hMainWnd;
	 

#if  0  //  2013/08/23
	 HMENU		hMainMenu  =  ::GetMenu(  hMainWnd  );
	 if  (  hMainMenu  )  {
		 QY_DMITEM	*	pItem;
		 int  iResId  =  CONST_resId_mainMenu;
		 if  (  qyGetAppAvLevel_qyMc(  )  ==  CONST_qyAppAvLevel_mini  )  iResId  =  CONST_resId_mainMenu_mini;
		 //  if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  CONST_resId_mainMenu  )  )  )  goto  errLabel;
		 if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  iResId  )  )  )  goto  errLabel;
		 if  (  makeDynaMenu(  &pQyMc->cusRes,  hMainMenu,  pItem,  getMenuStatus_frame,  0  )  )  goto  errLabel;
	 }
#endif

	 //
	 if  (  !bQnmAddHotKeys(  gHotKeys_main,  hMainWnd  )  )  goto  errLabel;

	 //
	if  (  pQyMc->iServiceId  ==  CONST_qyServiceId_is  )  {

		//
		pVar->pMsgBuf_msgArrive	=	(  MIS_MSGU  *  )mymalloc(  sizeof(  MIS_MSGU  )  );	//  .pVar  =  pSci->pVar;
		if  (  !pVar->pMsgBuf_msgArrive  )  goto  errLabel;

		if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {
			MC_VAR_common				*		pProcInfo			=	(MC_VAR_common*)pQyMc->get_pProcInfo(  );
			if  (  !pProcInfo  )  goto  errLabel;


			//  2008/10/03
			if  (  initAvRecordMgr(  pQyMc->g_hInst  )  )  goto  errLabel;

			//
			pProcInfo->initInfrared();

		}
	}

	 pVar->uiTimerId  =  SetTimer(  hMainWnd,  1,  1000,  NULL  );

	 iErr  =  0;
errLabel:
	 
	 if  (  iErr  )  exitVar_onDestroy_mainFrame(  p0,  hMainWnd,  pVar  );

	 return  iErr;
}

 __declspec(  dllexport  )  int  exitVar_onDestroy_mainFrame(  void  *  p0,  HWND  hMainWnd,  void  *  pVarParam  )
{
	 int							iErr				=	-1;
	 QY_MC_mainWndVar		*		pVar				=	(  QY_MC_mainWndVar  *  )pVarParam;

	 if  (  !hMainWnd  ||  !pVar  )  {
		 traceLogA(  (char*)  "exitVar_onDestroy_mainFrame failed: pMainWnd or pVar is null"  );
		 return  -1;
	 }

	 QY_MC					*		pQyMc				=	pVar->pQyMc;
	 if  (  !pQyMc  )  return  -1;
	 CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	 if (!pProcInfo)  return - 1;

	 //
	 traceLogA(  (char*)  "exitVar_onDestroy_mainFrame enters."  );
	 showInfo_open0(  0,  0,  _T(  "exitVar_onDestroy_mainFrame enters."  )  );

	 //
	 if  (  pVar->uiTimerId  )  KillTimer(  hMainWnd,  pVar->uiTimerId  );

	 #ifndef  __WINCE__
			  if  (  pQyMc->cfg.ucbUseTrayIcon  )  {
				  //  sendTrayMsg(  AfxGetApp(  )->m_hInstance,  hMainWnd,  pQyMc->cfg.iIDR_TRAY,  NIM_DELETE,  IDR_TRAY_offline,  CONST_qyWm_trayNotify  );
				  sendTrayMsg(  get_my_hInst( pQyMc ),  hMainWnd,  pQyMc->cfg.iIDR_TRAY,  NIM_DELETE,  IDR_TRAY_offline,  CONST_qyWm_trayNotify  );
			  }
	 #endif

	 //  2010/07/10
	 CQyString	lckCStr;
	 HANDLE		hRet	=	NULL;
	 #ifndef  __WINCE__
			  lckCStr = CQyString(  pQyMc->appParams.appObjPrefix  )  +  CQyString(  pQyMc->cfg.singleInstanceStr  );
	 #else
			  lckCStr = CQyString(  CONST_mutexPrefix_mcClientLogon  )  +  pQyMc->cfg.singleInstanceStr;
	 #endif
	 hRet  =  RemoveProp(  hMainWnd,  lckCStr  );

	 //
	 qnmRemoveHotKeys(  gHotKeys_main,  hMainWnd  );

	 HMENU	hMainMenu	=	::GetMenu(  hMainWnd  );
	 RemoveMenu(  hMainMenu,  1,  MF_BYPOSITION  );

	 //
		 //
#if  0
	 int  i;
	 for (i = 0; i < pProcInfo->cfg.usMaxCnt_pSharedObjs; i++) {
		 QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, i);
		 if (!pSharedObj->bUsed)  continue;
		 pSharedObj->bQuit = true;
		 continue;
	 }
	 tryToFreeSharedObjs(pProcInfo);
	 tryToFreeSharedObjs(pProcInfo);
#endif
	 //
	 freeAllSharedObjs(pProcInfo);

	 //
	 showInfo_open0(0, 0, _T("before closeDlg2ndScreen"));

	 //
	 pProcInfo->closeDlg2ndScreen();

	 //
	 showInfo_open0(0, 0, _T("after closeDlg2ndScreen"));

	 //
	 if  (  pQyMc->iServiceId  ==  CONST_qyServiceId_is  )  {
		 if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {			 
			 QY_SERVICEGUI_INFO		*		pSci				=	getServiceGuiInfo(  pQyMc,  pQyMc->iServiceId  );
			 MC_VAR_isCli				*		pProcInfo			=	(  MC_VAR_isCli  *  )pSci->pVar;


		#if  __isCli__
			 //  2012/08/02
			 //exitPtz(  );
			 //showInfo_open0(0, 0, _T("249.befoe exitAvRecordMgr"));
		#endif
			 //
			 exitAvRecordMgr(  );

			 //
			// showInfo_open0(0, 0, _T("255.after exitAvRecordMgr"));


			 //
			 pProcInfo->exitInfrared();


			 //  
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Close audio and video."  )  );
			 //Sleep(50);
	 
			 //
			 closeOtherPlayers(  pProcInfo  );

			 //
			showInfo_open0(0, 0, _T("after closeOtherPlayers"));
			 //Sleep(1000);


			 //
			 if  (  pProcInfo->ucb_doInitRecordSound  )  {
				 MODULE_camCap	*	pCamCap	=	(  MODULE_camCap  *  )getCusModule(  &pQyMc->cusModules,  CONST_moduleType_camCap  );
				 if  (  pCamCap  
					 &&  pCamCap->pf_doInitRecordSound
					 &&  pCamCap->pf_doExitRecordSound  )
				 {
					 pCamCap->pf_doExitRecordSound(  );
				 }
				 pProcInfo->ucb_doInitRecordSound  =  FALSE;
			 }

			 //
			 //
			 showInfo_open0(0, 0, _T("after exitRecordSound"));
			 //Sleep(1000);


		 }

		 MACRO_safeFree(  pVar->pMsgBuf_msgArrive  );	//  2009/12/10
	 }

	 //
	 showInfo_open0(0, 0, _T("888"));


	 //  2015/07/30. 在没有喇叭时，audio.Play会死掉，所以这里要做一点特别的处理。
	 //MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pQyMc->get_pProcInfo(  );
	 if  (  pProcInfo  )  {		
		 if  (  pProcInfo->m_iCtxType  ==  CONST_ctxType_qmc  )  {
			 //
			 if  (  pProcInfo->av.localAv.player.audio.bRunning  
				 &&  pProcInfo->av.localAv.player.audio.m_var.dwTickCnt_beforePlay  )  
			 {
				 int  iElapseInMs  =  GetTickCount(  )  -  pProcInfo->av.localAv.player.audio.m_var.dwTickCnt_beforePlay;
				 if  (  iElapseInMs  >  3000  )  {
					 showInfo_open0(  0,  0,  _T(  "Serious err: playAudio.Play is dead. force to exit"  )  );
					 Sleep(  500  );
					 exit(  0  );
				 }
			 }	
		 }
	 }

	 //
	 pProcInfo->pPlayDev->exitDSoundToPlay(  (  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx,  0,  0  );

	 


	 //
	 traceLogA(  (char*)  "exitVar_onDestroy_mainFrame leaves."  );
	 showInfo_open0(  0,  0,  _T(  "exitVar_onDestroy_mainFrame leaves."  )  );

	 //
	 return  0;
}

 //  2014/11/21
  int  tmpHandler_findMissingOrgReq(  void  *  p0,  void  *  pMsgTaskStatusParam,  void  *  pQElem  )
{
	 int					iRet				=	-1;
	 //  p0;
	 MIS_MSG_TASKSTATUS  *  pMsgTaskStatus  =  (  MIS_MSG_TASKSTATUS  *  )pMsgTaskStatusParam;
	 //
	 //  
	 MIS_MSGU			*	pMsg				=	(  MIS_MSGU  *  )pQElem;
	 //
	 BOOL					bMatched			=	FALSE;

	 if  (  pMsg->uiType  ==  CONST_misMsgType_talkingFriend_qmc  )  {
		 
		 MIS_MSG_TALKINGFRIEND_QMC  *  pMem  =  &pMsg->talkingFriend_qmc;

		 if  (  isTalkerShadowMgr(  pMem->addr  )  )  {
			 //
			 if  (  pMsgTaskStatus->idInfo_logicalPeer.ui64Id  )  {
				 //
				 if  (  pMem->addr.idInfo.ui64Id  ==  pMsgTaskStatus->idInfo_logicalPeer.ui64Id  )  {
					 SendMessage(  pMem->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsgTaskStatus  );
					 if  (  pMsgTaskStatus->ucbFound  )  {
						 iRet  =  1;  goto  errLabel;				   
					 }
				 }
				 //
				 }
			 else  {
				   SendMessage(  pMem->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsgTaskStatus  );
				   if  (  pMsgTaskStatus->ucbFound  )  {
					   iRet  =  1;  goto  errLabel;
				   }
			 }
		 }
		 
	 }

	 iRet  =  0;
errLabel:
	 return  iRet;
}


  //
#if 0
  bool  bExists_conf(  int  *piTaskId  )
  {
	  bool  bRet  =  false;
	  int  i;
	  CCtxQmc  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	  //
	  if  (  !piTaskId  )  return  false;

	  //
	  for  (  i  =  0;  i  <  pProcInfo->cfg.usMaxCnt_taskInfos;  i  ++  )  {
		   if  (  !qmcTaskInfo_bAlive(  pProcInfo,  i  )  )  continue;
		   QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  i  );
		   if  (  pTaskInfo->var.pTaskData->uiType  ==  CONST_taskDataType_conf  )  {
			   //
			   *piTaskId  =  pTaskInfo->var.iTaskId;
			   //
			   break;
		   }
	  }
	  if  (  i  ==  pProcInfo->cfg.usMaxCnt_taskInfos  )  goto  errLabel;

	  bRet  =  true;
	  errLabel:
	  return  bRet;
  }
#endif


  //
#if 0
  int iimainWnd_procMsgInput_confReq(  HWND  hMainWnd,  void  *  pVar,  MIS_MSG_INPUT  *  pMsgInput  )
   {
	   int  iErr  =  -1;
	   	
	   if  (  !pVar  )  return  -1;	
	   QY_MC_mainWndVar  &  var			=	*(  QY_MC_mainWndVar  *  )pVar;	
	   QY_MC			*	pQyMc			=	var.pQyMc;	
	   if  (  !pQyMc  )  return  -1;	
	   MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pQyMc->get_pProcInfo(  );	
	   if  (  !pProcInfo  )  return  -1;	
	   if  (  pProcInfo->m_iCtxType  !=  CONST_ctxType_qmc  )  return  -1;
	   
	   TCHAR  tBuf[128];

	   //
	   if  (  !pQyMc->appParams.bConfServer  )  {
		   showInfo_open0(  0,  0,  _T(  "confReq denied, I am not a confServ"  )  );
		   goto  errLabel;
	   }

	   //		
	   if  (  isUcFlgTalkData(  pMsgInput->ucFlg  )  &&  isUcFlgRouteTalkData(  pMsgInput->ucFlg  )  )  {		
		   showInfo_open0(  0,  0,  _T(  "confReq failed. confReq cant be received from messenger"  )  );													   
		   goto  errLabel;
		
	   }
	
	   //
	   IM_CONTENTU  *  pContent  =  M_getMsgContent(  pMsgInput->ucFlg,  &pMsgInput->data  );

	   //
	   if  (  pContent->uiType  !=  CONST_imCommType_confReq  )  {
		   goto  errLabel;
	   }

	   //		
	   int  iTaskId  =  0;
	   if  (  bExists_conf(  &iTaskId  )  )  {		
		   //
		   showInfo_open0(  0,  0,  _T(  "confReq: conf already exists"  )  );									

		   //
		   int  index_taskInfo  =  getQmcTaskInfoIndexBySth(  pProcInfo,  iTaskId  );
		   QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  index_taskInfo  );
		   if  (  !pTaskInfo  )  {
			   goto  errLabel;
		   }

		   if  (  pProcInfo->av.doConf.confReq.idInfo_imGrp_related.ui64Id  !=  pContent->confReq.idInfo_imGrp_related.ui64Id  )  {
			   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "confReq: oldConf is %I64u, will be cloed"  ),  pProcInfo->av.doConf.confReq.idInfo_imGrp_related.ui64Id  );
			   showInfo_open0(  0,  0,  tBuf  );

			   //
			   PostMessage(  pTaskInfo->var.hWnd_task,  WM_CLOSE,  0,  0  );

			   goto  errLabel;
		   }

		   //
		   iErr  =  0;  goto  errLabel;		
	   }
		
	   //		
	   set_doConf(  &pContent->confReq,  _T(  "mainWnd_postComm"  )  );
	   		
	   //		
	   dyn_setCurQisWallCfg(  0,  pQyMc->pQisWallsCfg  );
	   
	   //
	   iErr   =  0;
errLabel:

	   return  iErr;
   }
#endif


  //
  bool  bNeed_applyForOrgReq_av(MIS_MSG_taskStatus* pTaskStatus)
  {
	  bool  bRet = false;

	  CCtxQyMc* pQyMc = g_pQyMc;
	  CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	  int  i;
	  
	  //
	  DWORD  dwTickCnt = myGetTickCount(NULL);
	  QY_MESSENGER_ID  idInfo_sender = pTaskStatus->idInfo_taskSender;
	  if (!idInfo_sender.ui64Id)  goto  errLabel;

	  //
	  applyForOrgReq_status_mem* pMem; pMem = mynull;

	  //
	  for (i = 0; i < mycountof(pProcInfo->status.applyForOrgReq_status.mems); i++) {
		  pMem = &pProcInfo->status.applyForOrgReq_status.mems[i];
		  if (!pMem->idInfo_sender.ui64Id)continue;
		  int  iDiffInMs = dwTickCnt - pMem->dwTickCnt_lastRefreshed;
		  if (abs(iDiffInMs) > 10000) {
			  memset(pMem, 0, sizeof(pMem[0]));
		  }
		  continue;
	  }

	  
	  
	  //
	  for (i = 0; i < mycountof(pProcInfo->status.applyForOrgReq_status.mems); i++)
	  {
		  pMem = &pProcInfo->status.applyForOrgReq_status.mems[i];

		  if (!pMem->idInfo_sender.ui64Id)  continue;
		  if (pMem->idInfo_sender.ui64Id == idInfo_sender.ui64Id)  break;
		  continue;
	  }

	  //
	  if (i == mycountof(pProcInfo->status.applyForOrgReq_status.mems)) {
		  bRet = true;
		  //
		  for (i = 0; i < mycountof(pProcInfo->status.applyForOrgReq_status.mems); i++) {
			  pMem = &pProcInfo->status.applyForOrgReq_status.mems[i];
			  if (!pMem->idInfo_sender.ui64Id) {
				  pMem->idInfo_sender = idInfo_sender;
				  pMem->dwTickCnt_lastRefreshed = dwTickCnt;
				  break;
			  }
		  }
		  //
		  }
	  else {

		   //
		   int  iDiffInMs = dwTickCnt - pMem->dwTickCnt_lastRefreshed;
		   if (abs(iDiffInMs) > 4000) {
			   bRet = true;

			   //
			   pMem->dwTickCnt_lastRefreshed = dwTickCnt;

		   }
	  }

	  //
  errLabel:
	  return  bRet;
  }

  //
  int  pingTaskAv(MIS_MSG_INPUT* pMsgInput, bool* pbExists_taskAv)
  {
	  int  iErr = -1;
	  CCtxQyMc* pQyMc = g_pQyMc;
	  CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	  bool  bExists = false;

	  //
	  IM_CONTENTU* pContent = M_getMsgContent(pMsgInput->ucFlg, &pMsgInput->data);
	  if (pContent->uiType != CONST_imCommType_taskProcReq)  return  -1;
	  TASK_PROC_REQ* pTaskProcReq = &pContent->taskProcReq;
	  if (pTaskProcReq->usOp != CONST_imOp_ping)  return  -1;

	  do {
		  int  i;
		  for (i = 0; i < pProcInfo->cfg.usMaxCnt_taskInfos; i++) {
			  QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, i);
			  if (!pTaskInfo->bUsed)  continue;
			  QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;
			  if (!pTaskData)  continue;
			  MIS_MSG_TASK* pMsgTask = &pTaskData->msgU.task;
			  if (pMsgTask->uiType != CONST_misMsgType_task) continue;
			  pContent = M_getMsgContent(pMsgTask->ucFlg, &pMsgTask->data);
			  //
			  if (pMsgTask->tStartTime == pTaskProcReq->tStartTime_org
				  && pMsgTask->uiTranNo == pTaskProcReq->uiTranNo_org)
			  {
				  int  ii = 0;
				  bExists = true;
				  //
				  pTaskInfo->var.dwTickCnt_recv_lastRefreshed = myGetTickCount(mynull);
				  //
				  break;
			  }
			  //
			  continue;
		  }
		  iErr = 0;
	  } while (false);

	  //
	  if (pbExists_taskAv)  *pbExists_taskAv = bExists;

	  //
	  return  iErr;
  }

  
  //
  int mainWnd_procMsgInput_confReq(HWND  hMainWnd, void* pVar, MIS_MSG_INPUT* pMsgInput);

 //
int  dlgTalk_qPostMsg(  HWND  hDlgTalk,  Q_ELEM_T  *  pQElem,  unsigned  int  size  );
  int mainWnd_OnQyPostComm(  HWND  hMainWnd,  void  *  pVar,  UINT  wParam,  LONG  lParam  )
 {
	LONG				lRet			=	-1;
	if  (  !pVar  )  return  -1;
	QY_MC_mainWndVar  &  var			=	*(  QY_MC_mainWndVar  *  )pVar;
	QY_MC			*	pQyMc			=	var.pQyMc;
	if  (  !pQyMc  )  return  -1;
	MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pQyMc->get_pProcInfo(  );
	if  (  !pProcInfo  )  return  -1;
	if  (  pProcInfo->m_iCtxType  !=  CONST_ctxType_qmc  )  return  -1;
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;
	
	//  char				buf[1024]		=	"";
	unsigned  int		len;
	int					i;

	//
	if  (  pQyMc->bGuiQuit  )  {
		showInfo_open0(  0,  0,  _T(  "mainWnd_OnQyPostComm failed, bGuiQuit is true"  )  );
		return  -1;
	}
	if  (  pQyMc->bPrepareToGuiQuit  )  {
		showInfo_open0(  0,  0,  _T(  "mainWnd_OnQyPostComm failed, bPrepareToGuiQuit is true"  )  );
		return  -1;
	}	
	
	//
	switch  (  wParam  )  {
			case  CONST_qyWmParam_setActiveWindow:
				  if  (  lParam  )  ::PostMessage(  (  HWND  )lParam,  CONST_qyWm_postComm,  wParam,  0  );
				  break;
			case  CONST_qyWmParam_msgArrive:  {
				  //  CQyMalloc			mallocObj;
				  MIS_MSGU		*	pMsg			=	var.pMsgBuf_msgArrive;	//  (  MIS_MSGU  *  )mallocObj.malloc(  sizeof(  MIS_MSGU  )  );
				  if  (  !pMsg  )  goto  errLabel;

				  for  (  ;  !pQyMc->bQuit;  )  {
					   MACRO_memset_misMsg(  pMsg  );
					   len  =  sizeof(  pMsg[0]  );
					   if  (  qGetMsg(  &pQyMc->gui.processQ,  pMsg,  &len  )  )  break;

					   //
					   #ifdef  __DEBUG__
					   //
					   if (0) {
						   TCHAR  tBuf[128];
						   _sntprintf(tBuf, mycountof(tBuf), _T("mainWnd_onQyPostComm: get a msg. nQNodes %d"), pQyMc->gui.processQ.uiQNodes);
						   showInfo_open0(0, 0, tBuf);
					   }
					   //
					   if (pMsg->uiType == CONST_misMsgType_taskStatus) {
						   if (pMsg->taskStatus.iStatus == CONST_imTaskStatus_canceledByReceiver) {
							   int  ii = 0;
						   }
					   }
					   if (pMsg->uiType == CONST_misMsgType_input) {
						   int  ii = 0;
					   }
					   //
					   #endif

					   //
					   switch  (  pMsg->uiType  )  {
							   case  CONST_misMsgType_talk:  
							   case  CONST_misMsgType_task:     {
								     HWND						hWnd				=	NULL;
									 MIS_CNT				*	pMisCnt				=	NULL;
									 MSGR_ADDR					addr_logicalPeer;
									 BOOL						bNeedNotShowWnd		=	FALSE;

									 memset(  &addr_logicalPeer,  0,  sizeof(  addr_logicalPeer  )  );
									 if  (  pMsg->uiType  ==  CONST_misMsgType_talk  )  {  
										 //
										 if  (  !(  pMisCnt  =  (  MIS_CNT  *  )pMsg->talk.pMisCnt  )  )  goto  errLabel;
										 //
										 if  (  myGetPeer(  pMisCnt->cfg.misServName,  &pMsg->talk.data.route,  &pMsg->talk.addr_logicalPeer,  &addr_logicalPeer  )  )  goto  errLabel;

										 //										
										 IM_CONTENTU  *  pContent  =  (  IM_CONTENTU  *  )pMsg->talk.data.buf;

										 //  2017/07/17
										 if  (  pContent->uiType  ==  CONST_imCommType_htmlContent  )  {
											 /*
											 if  (  pProcInfo->avConsole.bGotMsg_avConsole  )  {
												 //
												#if  0
												 __declspec(  dllexport  )  int  doAvConsole_cmd_recvMsg(  __int64  ui64Id_from,  __int64  ui64Id_to,  TCHAR  *  tTxt  );

												 doAvConsole_cmd_recvMsg(  pMsg->talk.data.route.idInfo_from.ui64Id,  pMsg->talk.data.route.idInfo_to.ui64Id,  pContent->html.wBuf  );
												#endif
												 //
												 showInfo_open0(  0,  0,  _T(  "avConsole: bGotMsg_avConsole is true, doAvConsole_cmd_recvMsg called"  )  );
												 //
												 break;
											 }
											 */
											 GuiShare.pf_gui_procMsg(pMsg);

										 }
										

										}
									 else  if  (  pMsg->uiType  ==  CONST_misMsgType_task  )  {
											   //
											   if  (  !(  pMisCnt  =  (  MIS_CNT  *  )pMsg->task.pMisCnt  )  )  goto  errLabel;
											   //
											   if  (  myGetPeer(  pMisCnt->cfg.misServName,  &pMsg->task.data.route,  &pMsg->task.addr_logicalPeer,  &addr_logicalPeer  )  )  goto  errLabel;
											   
											   //
											   IM_CONTENTU  *  pContent  =  (  IM_CONTENTU  *  )pMsg->task.data.buf;
											   
											   //
											   #ifdef  __DEBUG__
													   if  (  pContent->uiType  ==  CONST_imCommType_ptzControlCmd  )  {
														   int  ii  =  0;
													   }
													   if (pContent->uiType == CONST_imCommType_confLayout) {
														   int  ii = 0;
													   }
													   if (pContent->uiType == CONST_imCommType_statusConfLayoutParam) {
														   int  ii = 0;
													   }
													   if (pContent->uiType == CONST_imCommType_transferAvInfo) {
														   int  ii = 0;
													   }
											   #endif

											   //  2009/09/07 
											   if  (  pMsg->task.uiTaskType  ==  CONST_imTaskType_viewDynBmp  
												   ||  pMsg->task.uiTaskType  ==  CONST_imTaskType_viewGps  )  
											   {
												   //  2014/09/28			
												   if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
													   if  (  pContent->transferAvInfo.idInfo_logicalPeer.ui64Id  )  {													
														   if  (  findTalker(  pQyMc,  &pContent->transferAvInfo.idInfo_logicalPeer,  &hWnd  )  )  {
															   #ifdef  __DEBUG__
																   traceLog((TCHAR*)  _T(  "mainWnd_OnPostComm: retrieveDynBmps conf findTalker failed"  )  );
															   #endif
															   goto  errLabel;													   
														   }
														   ::SendMessage(  hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );
														   break;												   
													   }
												   }										   													
												   
												   //
												   if  (  !IsWindow(  pProcInfo->hWnd_shareDynBmps  )  )  {									
													   traceLogA(  (char*)  "Not finished. hWnd_sharedWebcams is not valid"  );
													   break;
												   }
												   ::SendMessage(  pProcInfo->hWnd_shareDynBmps,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );

												   break;												   
											   }
											   
											   //  2015/06/06
											   if  (  pContent->uiType  ==  CONST_imCommType_ptzControlReq  
												   &&  pContent->ptzControlReq.ucbReply  )  
											   {												
												   if  (  findTalker(  pQyMc,  &addr_logicalPeer.idInfo,  &hWnd  )  )  {
													   #ifdef  __DEBUG__
															   traceLog((TCHAR*)  _T(  "mainWnd_OnPostComm: reply for ptzControlReq, findTalker failed"  )  );
													   #endif
													   goto  errLabel;
												   }														   
												   ::SendMessage(  hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );													
												   break;												   												
											   }

											   //  2012/08/08
											   if  (  pContent->uiType  ==  CONST_imCommType_ptzControlCmd  )  {
												   #ifdef  __DEBUG__
														   traceLog((TCHAR*)  _T(  "mainWnd_OnPostComm: ptzControlCmd"  )  );
												   #endif


												   //  2016/07/20
												   if  (  pContent->ptzControlCmd.cmdInfo.obj.uiObjType  ==  CONST_objType_rtspStream  )  {
													   SendMessage(  pProcInfo->hWnd_shareDynBmps,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );
													   break;
												   }
													
												   //
												   PARAM_viewLocalPtzControl  param  =  {0};
												   //
												   doRemotePtzCmd(  NULL,  &pContent->ptzControlCmd,  &param,  &pProcInfo->ptzWnd  );

												   break;
											   }
											   //  2015/08/05
											   if  (  pContent->uiType  ==  CONST_imCommType_transferFileReq  
												   &&  pContent->transferFileReq.usSubtype  ==  CONST_procOfflineResSubtype_download  )
											   {
												   if  (  findTalker(  pQyMc,  &addr_logicalPeer.idInfo,  &hWnd  )  )  {
													   #ifdef  __DEBUG__
															   traceLog((TCHAR*)  _T(  "mainWnd_OnPostComm: transferFileReq download, findTalker failed"  )  );
													   #endif
													   goto  errLabel;
												   }	
												   
												   //									 
												   if  (  dlgTalk_qPostMsg(  hWnd,  pMsg,  len  )  )  goto  errLabel;	  
									 
												   ::PostMessage(  hWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
												   //
												   break;
											   }
											   //
											   if  (  !pMsg->task.iTaskId  )  {

												   #ifdef  __DEBUG__
														   traceLog((TCHAR*)  _T(  "mainWnd_OnQyPostComm: task.iTaskId is 0"  )  );
												   #endif

												   //
												   bNeedNotShowWnd  =  TRUE;
											   }


											   //
											   GuiShare.pf_gui_procMsg(pMsg);

											   //
											   }
									 else  
										 goto  errLabel;

									 //
									 hWnd  =  NULL;
									 
									 //
									 if  (  !hWnd  )  {

										 if  (  pProcInfo->cfg.ucb_talkToMsgr_manually  ) {
											 if (findTalker(pQyMc, &addr_logicalPeer.idInfo, &hWnd))  goto  errLabel;
											}
										 else {
											 if (pProcInfo->tryToTalkToMessenger_any(mynull, addr_logicalPeer.idInfo.ui64Id, 0, bNeedNotShowWnd, FALSE, &hWnd))  goto  errLabel;
										 }

									 }
										
									 //									 
									 if  (  dlgTalk_qPostMsg(  hWnd,  pMsg,  len  )  )  goto  errLabel;
	  
									 ::PostMessage(  hWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
									 
									}
								     break;

							   case  CONST_misMsgType_input:	//  2014/09/05
								   {
								     HWND						hWnd		=	NULL;
									 MIS_CNT				*	pMisCnt		=	NULL;
									 MSGR_ADDR					addr_logicalPeer;
									 if  (  !(  pMisCnt  =  (  MIS_CNT  *  )pMsg->input.pMisCnt  )  )  goto  errLabel;
									 
									 IM_CONTENTU			*	pContent	=	M_getMsgContent(  pMsg->input.ucFlg,  &pMsg->input.data  );									 
							
									 //
#ifdef  __DEBUG__
									 if (pContent->uiType == CONST_imCommType_taskInteractionReq) {
										 int  ii = 0;
									 }
									 if (pContent->uiType == CONST_imCommType_taskProcReq) {
										 if (pContent->taskProcReq.usOp == CONST_imOp_ping) {
											 int  ii = 0;
										 }
									 }
#endif 

									 //  2014/05/05
									 BOOL  bMsgProcessed  =  FALSE;
									 switch  (  pContent->uiType  )  {
											 case  CONST_imCommType_retrieveDynBmps:
												   bMsgProcessed  =  TRUE;

												   //  2015/06/05
												   #ifdef  __DEBUG__
														   traceLog((TCHAR*)  _T(  "mainWnd_OnPostComm: get retrieveDynBmps from %I64u, bResp %d"  ),  pMsg->input.data.route.idInfo_from.ui64Id,  pContent->retrieveDynBmps.ucbResp  );
												   #endif

												   //
												   if  (  !(  
													   //isUcFlgTalkData(  pMsg->input.ucFlg  )  ||  
													   isUcFlgRouteTalkData(  pMsg->input.ucFlg  )  )  )  {
   														 #ifdef  __DEBUG__
																 traceLog((TCHAR*)  _T(  "mainWnd_OnPostComm: error: req retrieveDynBmps not from others"  )  );
														 #endif
														 goto  errLabel;
												   }
												   //  2017/06/11
												   if  (  pContent->retrieveDynBmps.ucbResp
													   &&  pContent->retrieveDynBmps.ucbAvConsole  )  
												   {
													   AvConsole_req_retrieveDynBmps  reply  =  {0};
													   reply.iType  =  CONST_qisMsgType_avConsole;				
													   //		
													   reply.usCmd  =  CONST_avConsole_cmd_retrieveDynBmps;		
													   reply.ucbReply  =  TRUE;
													   //
													   RETRIEVE_DYN_BMPS  *  pReq  =  &pContent->retrieveDynBmps;
													   //
													   if  (  pReq->usCnt  >  mycountof(  pReq->mems  )  )  goto  errLabel;
													   for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
														   if  (  reply.usCnt  >=  mycountof(  reply.mems  )  )  break;
														   //
														   reply.mems[reply.usCnt].uiObjType  =  pReq->mems[i].qisResObj.resObj.uiObjType;
														   reply.mems[reply.usCnt].usIndex_obj  =  pReq->mems[i].qisResObj.resObj.usIndex_obj;
														   reply.mems[reply.usCnt].usHelp_subIndex  =  pReq->mems[i].qisResObj.resObj.usHelp_subIndex;
														   safeTcsnCpy(  pReq->mems[i].cusName,  reply.mems[reply.usCnt].cusName,  mycountof(  reply.mems[reply.usCnt].cusName  )  );
														   //
														   reply.mems[reply.usCnt].w  =  pReq->mems[i].usW;
														   reply.mems[reply.usCnt].h  =  pReq->mems[i].usH;
														   //
														   reply.usCnt  ++  ;
														   continue;
													   }
													   //
													#if  0
													   __declspec(  dllexport  )  int  doAvConsole_cmd_retrieveDynBmps(  AvConsole_req_retrieveDynBmps  *  pReq  );
													   //
													   doAvConsole_cmd_retrieveDynBmps(  &reply  );
													#endif
													   //
													   break;
												   }
												   //  2014/09/26
												   if  (  pContent->retrieveDynBmps.conf.idInfo_imGrp_related.ui64Id  )  {
													   if  (  findTalker(  pQyMc,  &pContent->retrieveDynBmps.conf.idInfo_imGrp_related,  &hWnd  )  )  {
														   #ifdef  __DEBUG__
																   traceLog((TCHAR*)  _T(  "mainWnd_OnPostComm: retrieveDynBmps conf findTalker failed"  )  );
														   #endif
														   goto  errLabel;
													   }
													   ::SendMessage(  hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );
													   break;												   
												   }
												   //
												   if  (  isUcFlgResp(  pMsg->input.ucFlg  )  )  {													
													   if  (  findTalker(  pQyMc,  &pMsg->input.data.route.idInfo_from,  &hWnd  )  )  {
														   #ifdef  __DEBUG__
																   traceLog((TCHAR*)  _T(  "mainWnd_OnPostComm: retrieveDynBmps resp findTalker failed"  )  );
														   #endif
														   goto  errLabel;
													   }
													   ::SendMessage(  hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );
													   break;												   
												   }
												   //  2014/09/04
												   if  (  !IsWindow(  pProcInfo->hWnd_shareDynBmps  )  )  {									
													   #ifdef  __DEBUG__
															   traceLogA(  (char*)  "retrieveDynBmps failed: hWnd_sharedWebcams is not valid"  );
													   #endif
													   showInfo_open0(  0,  0,  _T(  "retrieveDynBmps failed: hWnd_sharedWebcams is not valid"  )  );
													   break;
												   }
												   ::SendMessage(  pProcInfo->hWnd_shareDynBmps,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );													
												   break;
											 case  CONST_imCommType_htmlContent:  //  2014/07/12
												   bMsgProcessed  =  TRUE;
												   												   		
												   if  (  !(  
													   //isUcFlgTalkData(  pMsg->input.ucFlg  )  ||  
													   isUcFlgRouteTalkData(  pMsg->input.ucFlg  )  )  )  {
   														 #ifdef  __DEBUG__
																 traceLog((TCHAR*)  _T(  "mainWnd_OnPostComm: error: resp html not from others"  )  );
														 #endif
														 goto  errLabel;
												   }
												   if  (  isUcFlgResp(  pMsg->input.ucFlg  )  )  {													
													   if  (  findTalker(  pQyMc,  &pMsg->input.data.route.idInfo_from,  &hWnd  )  )  goto  errLabel;
													   ::SendMessage(  hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );
													   break;												   
												   }
												   #ifdef  __DEBUG__
														   traceLog((TCHAR*)  _T(  "Err: request html is not processed here"  )  ); 
												   #endif
												   break;											
												   
											 case  CONST_imCommType_taskProcReq:	//  2014/10/09
												   bMsgProcessed = true;
												   //
												   if (pContent->taskProcReq.usOp == CONST_imOp_ping) {
													   int  ii = 0;
													   bool  bExists_taskAv = false;
													   pingTaskAv(&pMsg->input, &bExists_taskAv);

													   //
													   if (!bExists_taskAv) {
														   //
														   QY_MESSENGER_ID  idInfo_imGrp_related;
														   idInfo_imGrp_related.ui64Id = 0;
														   //  在判断taskProcReq是属于哪个任务时，用startTime_org,tn_org就可以决定。不一定需要idInfo_grp
														   //
														   MSGR_ADDR  addr = { 0 };
														   addr.idInfo.ui64Id = pMsg->input.data.route.idInfo_from.ui64Id;
														   procSendTaskProcReq(pMisCnt, CONST_qyCmd_sendMedia, CONST_imOp_recv_applyForOrgReq, pContent->taskProcReq.tStartTime_org, pContent->taskProcReq.uiTranNo_org, pContent->taskProcReq.uiContentType_org, idInfo_imGrp_related, 0, 0, mynull, 0, true, mynull, &addr);
														   //
														   showInfo_open0(0, 0, _T("mainWnd_OnQyPostComm: procSendTaskProcReq"));
													   }
													   else {
														   int  ii = 0;
													   }

													   //
													   break;

												   }

												   //
												   if  (  pContent->taskProcReq.hWnd_task  )  {
													   bMsgProcessed  =  TRUE;
													   //
													   ::SendMessage(  pContent->taskProcReq.hWnd_task,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );												 
												   }
												   break;

											 case  CONST_imCommType_procOfflineRes:  //  2015/08/03
												   bMsgProcessed  =  TRUE;

												   //  2015/06/05
												   #ifdef  __DEBUG__
														   traceLog((TCHAR*)  _T(  "mainWnd_OnPostComm: get procOfflineRes from %I64u, bResp %d"  ),  pMsg->input.data.route.idInfo_from.ui64Id,  pContent->procOfflineResU.common.ucbResp  );
												   #endif

												   //
												   if  (  !(  
													   //isUcFlgTalkData(  pMsg->input.ucFlg  )  ||  
													   isUcFlgRouteTalkData(  pMsg->input.ucFlg  )  )  )  {
   														 #ifdef  __DEBUG__
																 traceLog((TCHAR*)  _T(  "mainWnd_OnPostComm: error: req retrieveDynBmps not from others"  )  );
														 #endif
														 goto  errLabel;
												   }
												   //
												   if  (  pContent->procOfflineResU.common.usSubtype  ==  CONST_procOfflineResSubtype_download  )  {
													   if  (  pProcInfo->talkToMessenger(  pMsg->input.data.route.idInfo_from.ui64Id,  FALSE,  FALSE,  &hWnd  )  )  {
														     #ifdef  __DEBUG__
																     traceLog((TCHAR*)  _T(  "mainWnd_OnPostComm: procOfflineRes req talkToMessenger failed"  )  );
														     #endif
														     goto  errLabel;																		
													   }
													   }
												   else  {
														 if  (  findTalker(  pQyMc,  &pMsg->input.data.route.idInfo_from,  &hWnd  )  )  {
														     #ifdef  __DEBUG__
																     traceLog((TCHAR*)  _T(  "mainWnd_OnPostComm: procOfflineRes req findTalker failed"  )  );
														     #endif
														     goto  errLabel;																									   
														 }
												   }
												   //
												   ::SendMessage(  hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );
												   
												   //												   
												   break;
											 case  CONST_imCommType_imGrp:  //  2017/07/26
												   bMsgProcessed  =  TRUE;
												   //
												   if  (  (  
													   //isUcFlgTalkData(  pMsg->input.ucFlg  )  ||  
													   isUcFlgRouteTalkData(  pMsg->input.ucFlg  )  )  )  {
													   //  说明时从其他的客户端发过来，通知临时组变化的。直接发到 dlgAvRes_mem_hzj上去显示分组成员。
													   //traceLog((TCHAR*)  _T(  "not finished. need to send to dlgAvRes_mem_hzj"  )  );
													   //
													   if  (  !IsWindow(  pProcInfo->hWall_hzj  )  )  {
														   traceLog((TCHAR*)  _T(  "hWall_hzj is invalid. imGrp can't be processed"  )  );
														   break;
													   }
													   //
													   ::SendMessage(  pProcInfo->hWall_hzj,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );													   
													   //
													   break;
												   }

												   //
												   hWnd  =  pProcInfo->cfgGrp.hWnd_cfgGrp;
												   //
												   if  (  IsWindow(  hWnd  )  )  {
													   ::SendMessage(  hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );
													   break;
												   }
												   //
												   notifyProgressEnd(  &pQyMc->gui.progress,  pMsg->input.uiTranNo,  0  );  
												   
												   //
												   break;
											 case  CONST_imCommType_confReq:
												   bMsgProcessed  =  true;
												   //
												   if (isUcFlgResp(pMsg->input.ucFlg)) {
													   //
													   if (findTalker_shadow(pQyMc, pContent->confReq.idInfo_imGrp_related.ui64Id,  0, &hWnd)) {
														   break;
													   }
													   //
													   ::SendMessage(hWnd, CONST_qyWm_comm, 0, (LPARAM)pMsg);

													   //
													   break;
												   }

												   //
												   #ifdef  __DEBUG__
														   traceLog((TCHAR*)  _T(  "confReq recved"  )  );
												   #endif
												   //
												   mainWnd_procMsgInput_confReq(  hMainWnd,  pVar,  &pMsg->input  );
												   //
												   break;
											 case  CONST_imCommType_taskInteractionReq:
												   //												 
												   if (isUcFlgResp(pMsg->input.ucFlg)) {
												 
													   QY_MESSENGER_ID  idInfo_peer;
													   idInfo_peer = pContent->taskInteractionReq.idInfo_imGrp_related;
													   if (!idInfo_peer.ui64Id)  idInfo_peer.ui64Id = pMsg->input.data.route.idInfo_from.ui64Id;
													   //
													   if (findTalker(pQyMc, &idInfo_peer, &hWnd)) {
														   break;
													   }
													   //
													   ::SendMessage(hWnd, CONST_qyWm_comm, 0, (LPARAM)pMsg);
													   //

												   }
												   break;

											 default:
													break;
									 }
									 if  (  bMsgProcessed  )  break;

									 //
									 if  (  !pMsg->input.addr_logicalPeer.idInfo.ui64Id  )  {	
										 switch  (  pContent->uiType  )  {
												 case  CONST_imCommType_refreshDynBmps: 
												 case  CONST_imCommType_verifyViewDynBmp:
													   ::SendMessage(  pProcInfo->hWnd_shareDynBmps,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );
													   break;
												 case  CONST_imCommType_retrieveCustomerServiceObjListReq:
													   //
													   #ifdef  __DEBUG__
															   traceLog((TCHAR*)  _T(  "Not finished, CONST_imCommType_retrieveCustomerServiceObjListReq"  )  );
													   	   	   for  (  i  =  0;  i  <  pContent->retrieveCustomerServiceObjListReq.usCnt;  i  ++  )  {
																   traceLog((TCHAR*)  _T(  "mems[%d]: %I64u, %s"  ),  i,  pContent->retrieveCustomerServiceObjListReq.mems[i].idInfo.ui64Id,  pContent->retrieveCustomerServiceObjListReq.mems[i].displayName  );
															   }
													   #endif
													   //
													   for  (  i  =  0;  i  <  mycountof(  pProcInfo->customerService.objs  );  i  ++  )  {
														    if  (  i  <  pContent->retrieveCustomerServiceObjListReq.usCnt  )  {
																memcpy(  &pProcInfo->customerService.objs[i],  &pContent->retrieveCustomerServiceObjListReq.mems[i],  sizeof(  pProcInfo->customerService.objs[i]  )  );
																}
															else  {
																  memset(  &pProcInfo->customerService.objs[i],  0,  sizeof(  pProcInfo->customerService.objs[i]  )  );
															}
													   }
													   PostMessage(  pQyMc->gui.hMainWnd,  WM_COMMAND,  MAKEWPARAM(  ID_refreshLayout,  0  ),  0  );
													   break;
												 default:
													     TCHAR  tBuf[128];
														 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "mainWnd_OnPostComm: msgInput, unprocessed content.type %d"  ),  pContent->uiType  );
														 showInfo_open0(  0,  0,  tBuf  );
														 break;
										 }
										 break;
									 }

									 //
									 memset(  &addr_logicalPeer,  0,  sizeof(  addr_logicalPeer  )  );
									 lstrcpyn(  addr_logicalPeer.misServName,  pMisCnt->cfg.misServName,  mycountof(  addr_logicalPeer.misServName  )  );
									 addr_logicalPeer.idInfo.ui64Id  =  pMsg->input.addr_logicalPeer.idInfo.ui64Id;		//  ÔÚÈ¡webMessengerµÄ×´Ì¬Ê±£¬»áÓÃµ½Õâ¸öÀàÐÍ¡£
																														//  Ã»ÓÐ¶ÀÁ¢Æô¶¯´°¿ÚµÄÄÜÁ¦£¬µ«ÊÇ¿ÉÒÔ·¢ÏÖ´°¿Ú£¬È»ºó½«ÏûÏ¢ËÍµ½´°¿ÚÄÇÀï¡£
								 

									 hWnd  =  NULL;

									 //  2013/09/09

									 //
									 if  (  !hWnd  )  {

										 if (pProcInfo->cfg.ucb_talkToMsgr_manually) {
											 if (findTalker(pQyMc, &addr_logicalPeer.idInfo, &hWnd))  goto  errLabel;
											 }
										 else {
											 //  2014/01/14
											 BOOL  bNeedNotShowWnd = FALSE;
											 if (pProcInfo->tryToTalkToMessenger_any(mynull, addr_logicalPeer.idInfo.ui64Id, 0, bNeedNotShowWnd, FALSE, &hWnd))  goto  errLabel;
										 }
									 }

 									 ::SendMessage(  hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );
									 								     
									 }

								     break;

							   case  CONST_misMsgType_taskStatus:  {
								     HWND						hWnd		=	NULL;
									 MSGR_ADDR					addr_logicalPeer;
									 //  QY_MESSENGER_ID			idInfo_peer;

									 
									 if  (  pMsg->taskStatus.ucbNotification  )  {
										 displayNotification(  pProcInfo,  &pMsg->taskStatus  );
										 break;
									 }

									 MIS_CNT				*	pMisCnt		=	NULL;
									 if  (  !(  pMisCnt  =  (  MIS_CNT  *  )pMsg->taskStatus.pMisCnt  )  )  goto  errLabel;

									 memset(  &addr_logicalPeer,  0,  sizeof(  addr_logicalPeer  )  );
									 lstrcpyn(  addr_logicalPeer.misServName,  pMisCnt->cfg.misServName,  mycountof(  addr_logicalPeer.misServName  )  );
									 addr_logicalPeer.idInfo.ui64Id  =  pMsg->taskStatus.idInfo_logicalPeer.ui64Id;

									 //
									 bool  bNeeded_applyForOrgReq  =  false;

									 //
#ifdef  __DEBUG__
									 if (pMsg->taskStatus.iStatus == CONST_imTaskStatus_canceledBySender) {
										 int  ii = 0;
									 }
									 if (pMsg->taskStatus.iStatus == CONST_imTaskStatus_canceledByReceiver) {
										 int  ii = 0;
									 }
#endif

									 //
									 if (pMsg->taskStatus.iStatus == CONST_imTaskStatus_canceledBySender) {
										 //
										 pProcInfo->gui_notify_clearTask(pMsg->taskStatus.iTaskId);
									 }

									 //
									 if  (  pMsg->taskStatus.iStatus  ==  CONST_imTaskStatus_err_cantGet_index_activeMems_from  )  {
										 bNeeded_applyForOrgReq  =  true;
										 int  ii  =  0;
										 }
									 else  {

										 //
										 if (!pQyMc->appParams.bConfServer) {
											 if (pMsg->taskStatus.iStatus == CONST_imTaskStatus_err_missingOrgReq
												 && addr_logicalPeer.idInfo.ui64Id)
											 {
												 DWORD  tickCnt = myGetTickCount(mynull);
												 int  iDiffInMs = tickCnt - pProcInfo->av.acceptTaskAv.dwLastTickCnt_avReply;
												 if (abs(iDiffInMs) > 5000) {
													 //
													 QY_MESSENGER_ID  idInfo_imGrp_related;
													 idInfo_imGrp_related.ui64Id = 0;
													 //
													 MSGR_ADDR addr = { 0 };
													 addr.idInfo.ui64Id = pMsg->taskStatus.idInfo_taskSender.ui64Id;
													 procSendTaskProcReq(pMisCnt, CONST_qyCmd_sendMedia, CONST_imOp_recv_cancel, pMsg->taskStatus.tStartTime, pMsg->taskStatus.uiTranNo, pMsg->taskStatus.uiContentType, idInfo_imGrp_related, 0, 0, mynull, 0, true, _T(""), &addr);
													 //
												 }
												 //
												 break;
											 }
										 }


										//
										 if  (  pMsg->taskStatus.iStatus  ==  CONST_imTaskStatus_err_missingOrgReq
											 ||  !addr_logicalPeer.idInfo.ui64Id  )  
										 {		//  2014/11/21. 这里性能不是很好，因为每次find都要轮询一遍。不过这样处理比较简单
											 qTraverse(  &pMisCnt->talkingFriendQ,  tmpHandler_findMissingOrgReq,  0,  pMsg  );
											 //
											 if  (  pMsg->taskStatus.ucbFound  )  {
												 addr_logicalPeer.idInfo.ui64Id  =  pMsg->taskStatus.idInfo_logicalPeer.ui64Id;
											 }
										 }

										 //									 
										 //  if  (  talkToMessenger(  pQyMc,  &addr_logicalPeer,  NULL,  TRUE,  FALSE,  &hWnd  )  )  goto  errLabel;
										 if  (  !findTalker(  pQyMc,  &addr_logicalPeer,  0,  &hWnd  )  )  {
											 ::SendMessage(  hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );
										 }

										 if  (  (  pMsg->taskStatus.iStatus  ==  CONST_imTaskStatus_err_missingOrgReq  &&  !hWnd  )
											 ||  pMsg->taskStatus.ucbNeeded_applyForOrgReq  )  
										 {
											 bNeeded_applyForOrgReq  =  true;
										 }
									 }

									 //
									 if  (  bNeeded_applyForOrgReq  )  {
										 //
										 TCHAR  tBuf[128];

										 //
										 if  (  pQyMc->appParams.bMcu  )  {
											 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "For mcu: need not to applyForOrgReq. skipped"  )  );
											 showInfo_open0(  0,  0,  tBuf  );
											 break;
										 }

										 //
										 if (!bNeed_applyForOrgReq_av(&pMsg->taskStatus)) {
											 break;
										 }

										 //
										 TASK_PROC_REQ		taskProcReq;
										 int				lenInBytes;
										 memset(  &taskProcReq,  0,  sizeof(  taskProcReq  )  );
										 taskProcReq.uiType  =  CONST_imCommType_taskProcReq;
										 taskProcReq.usOp  =  CONST_imOp_recv_applyForOrgReq;
										 //  taskProcReq.tStartTime_org  =  0;
										 taskProcReq.uiTranNo_org  =  pMsg->taskStatus.uiTranNo;
										 //  taskProcReq.uiSerialNo_org  =  0;
										 taskProcReq.uiContentType_org  =  pMsg->taskStatus.uiContentType;
										 //	
										 lenInBytes  =  sizeof(  taskProcReq  );			
										 //					
										 MACRO_prepareForTran(  );						
										 
										 //  2017/10/11
										 if  (  pMsg->taskStatus.iStatus  ==  CONST_imTaskStatus_err_cantGet_index_activeMems_from  )  {
											 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "cantGet_index_activeMems_from."  )  );
										 }
										 else  {
											   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "taskAvOrgReq not found."  )  );
										 }
										 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s send taskProcReq to %I64u to retrieve orgReq. tn %d."  ),  tBuf,  pMsg->taskStatus.idInfo_taskSender.ui64Id,  uiTranNo  );
										 #ifdef  __DEBUG__
												 traceLog((TCHAR*)  _T(  "%s"  ),  tBuf  );
										 #endif
										 showInfo_open0(  0,  0,  tBuf  );

										 //
										 if  (  pProcInfo->postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  pMsg->taskStatus.cmdCode,  tStartTran,  uiTranNo,  0,  0,  0,  (  char  *  )&taskProcReq,  lenInBytes,  &addr_logicalPeer.idInfo,  NULL,  NULL,  &pMsg->taskStatus.idInfo_taskSender,  0,  NULL,  FALSE  )  )  goto  errLabel;

										 //  2017/10/03
										 pProcInfo->status.dwTickCnt_sendTo_applyForOrgReq  =  GetTickCount(  );

									 }

									 
									}
								     break;
							   case  CONST_misMsgType_refreshContactsStatus_qmc:  
							   case  CONST_misMsgType_refreshMeStatus_qmc:  {
								     //  QY_WMBUF
								     ::SendMessage(  pMsg->refreshContactsStatus_qmc.hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );
									 }
								     break;
							   case  CONST_misMsgType_applyForPlayer_qmc:  
								     pProcInfo->doApplyForPlayer(  hMainWnd,  pMsg  );
								     break;

									 //  2011/12/10
							   case  CONST_misMsgType_notifyTaskEnd_qmc:
								     ::SendMessage(  pMsg->notifyTaskEnd.hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  );  
								     break;

							   case  CONST_misMsgType_displayRecentFriends_qmc: {
								     pProcInfo->displayRecentFriends(&pMsg->displayRecentFriends_qmc);								     
									 }
								     break;

							   default:
								        traceLogA(  (char*)  "CMainFrame::OnQyPostComm: msgArrive:  unprocessed: msgType: %d",  pMsg->uiType  );
										break;
					   }

					   //
					   continue;
				  }
				  }
				  break;			

			case  CONST_qyWmParam_task_end:
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "CMainFrame: task end, to tryToFreeSharedObjs"  )  );
				  #endif
				  tryToFreeSharedObjs( pProcInfo );
				  break;

			case  CONST_qyWmParam_chkTask:
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "CMainFrame: to chk task"  )  );
				  #endif
				  qmcChkTasks_gui( pProcInfo );
				  break;

			case  CONST_qyWmParam_toStartLocalAudioPlayer:		//  2013/05/26
				  #ifdef  __DEBUG__						  traceLog((TCHAR*)  _T(  "MainFrm: get Msg toStartLocalAudioPlayer"  )  );
				  #endif
				  startLocalAudioPlayer(  pProcInfo  );
				  break;

			case  CONST_qyWmParam_closeConsoleWall:
				  pFuncs->isCliD3d.pf_closeConsoleWall(pQyMc->pGBuf_d3d);
				  break;

			case  CONST_qyWmParam_needRefreshImgs: {
				  int  iTaskId = (  int  )lParam;
				  int  index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, iTaskId);

				  QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
				  if (!pTaskInfo)  break;
				  QMC_taskData_common* pTaskData = (QMC_taskData_common*)pTaskInfo->var.pTaskData;
				  if (!pTaskData)  break;
				  if (pTaskData->uiType != CONST_taskDataType_conf) break;
				  QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskData;
				  if (pTc->common.msgU.uiType != CONST_misMsgType_task)  break;
				  MIS_MSG_TASK* pMsgTask = &pTc->common.msgU.task;
				  //
				  HWND  hTalk;
				  if (findTalker(pQyMc, &pMsgTask->addr_logicalPeer.idInfo, &hTalk))  break;

				  dyn_d3dWall_refreshImgs(hTalk,  (TCHAR*)_T(  "mainWnd_OnQyPostComm.1264"  ));

				  int  ii = 0;
				  }
				  break;

			default:
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "mainWnd_OnQyPostComm: unknown wParam"  )  );
					#endif
					break;
	}

	lRet  =  QY_RC_WMOK;
errLabel:
	return	lRet;
}


//
 int showState_tasks( QY_MC_mainWndVar &var)
{
	CCtxQyMc *pQyMc = g_pQyMc;
	CCtxQmc *pProcInfo = (CCtxQmc  *  )pQyMc->get_pProcInfo();

	QMC_TASK_INFO *pTaskInfo = mynull;

	QY_DMITEM* pTaskTypeTable = getResTable(0, &pQyMc->cusRes, CONST_resId_imTaskTypeTable);
	std::wstring wstr;

	//
#if DEBUG
#endif
		
	//
	SYSTEMTIME when;
	GetLocalTime(& when);

	//
	int iPos = 0;
	int i;
	std::wstring str;
	int index_taskInfo;
	uint uiTickCnt_now = myGetTickCount(mynull);

	//
	TCHAR  tBuf[256];


	//
	for (index_taskInfo = 0; index_taskInfo < pProcInfo->cfg.usMaxCnt_taskInfos; index_taskInfo++)
	{
		pTaskInfo = (QMC_TASK_INFO*)pProcInfo->getQmcTaskInfoByIndex( index_taskInfo);
		if (!pTaskInfo->bUsed) continue;
		QMC_taskData_common *pTaskData = pTaskInfo->var.pTaskData;
		if (pTaskData == mynull) continue;
		//
		str = _T("task[")  +  std::to_wstring(index_taskInfo)  +  std::wstring(_T(  "]: "  )  );
		//
		MIS_MSG_TASK* pMsgTask = &pTaskData->msgU.task;
		{
			if (pMsgTask->uiType != CONST_misMsgType_task)
			{
				continue;
			}

			//
			str += std::to_wstring(pMsgTask->data.route.idInfo_from.ui64Id)  + std::wstring(_T("->"))  +  std::to_wstring(pMsgTask->data.route.idInfo_to.ui64Id)  +  _T(", peer ")  +  std::to_wstring(pMsgTask->addr_logicalPeer.idInfo.ui64Id)  +  _T(  "."  );

			//
			IM_CONTENTU* pContent = (IM_CONTENTU*)pMsgTask->data.buf;
			//
			switch (pContent->uiType)
			{
			case CONST_imCommType_transferAvInfo:
				str += _T(" av");

				//
				showState_open(0, _T("showTasks"), str.c_str(), CONST_stateType_tasks, 0, &when, iPos, pTaskInfo->var.iTaskId); iPos++;

				//
				wstr = qyGetDesByType1(pTaskTypeTable, pMsgTask->uiTaskType);
				str = _T("taskType ") + wstr;
				showState_open(0, _T("showTasks"), str.c_str(), CONST_stateType_tasks, 0, &when, iPos, pTaskInfo->var.iTaskId); iPos++;


				//
				//
				str = _T("");
				str += _T("tn_a ")+ std::to_wstring(pContent->transferAvInfo.ass.tranInfo.audio.uiTranNo_openAvDev) + std::wstring(_T(", tn_v "))+ std::to_wstring(pContent->transferAvInfo.ass.tranInfo.video.uiTranNo_openAvDev);

				showState_open(0, _T("showTasks"), str.c_str(), CONST_stateType_tasks, 0, & when, iPos, pTaskInfo->var.iTaskId); iPos++;

				//
				if (pTaskData->uiType != CONST_taskDataType_conf) break;
				QMC_taskData_conf* pTc; 
				pTc = (QMC_taskData_conf*)pTaskData;
				DLG_TALK_videoConference* videoConference;
				videoConference= &pTc->videoConference;

				//
				//
				str = _T("maxSpeakers ") + std::to_wstring(pContent->transferAvInfo.confCfg.usMaxSpeakers);
				str += _T(", maxActiveMems ") + std::to_wstring(videoConference->usCntLimit_activeMems_from);					
				if (pContent->transferAvInfo.confCfg.idInfo_initiator.ui64Id) {				
					str += _T(", initiator ") + std::to_wstring(pContent->transferAvInfo.confCfg.idInfo_initiator.ui64Id);					
				}
				str += _T(", 2Streams ") + std::to_wstring(pTc->ucb2Streams);
				showState_open(0, _T("showTasks"), str.c_str(), CONST_stateType_tasks, 0, &when, iPos, pTaskInfo->var.iTaskId); iPos++;



				//
				int a;
				for (a = 0; a < mycountof(videoConference->activeMems_from); a++)
				{
					DLG_TALK_videoConferenceActiveMemFrom *pActiveMem_from = &videoConference->activeMems_from[a];
					//
					if (pActiveMem_from->avStream.idInfo.ui64Id != 0)
					{
						char  fourccStr[4 + 1];
						iFourcc2Str(pActiveMem_from->avStream.obj.tranInfo.video.vh_stream.dwFourcc, fourccStr, mycountof(fourccStr));
						TCHAR  wFourccStr[4 + 1];
						myUtf82TChar(fourccStr, wFourccStr, mycountof(wFourccStr));
						//
						str = _T("");
						str += _T("act"  )  +  std::to_wstring(a)+ _T(  ":"  )+ std::to_wstring(pActiveMem_from->avStream.idInfo.ui64Id);
						str += _T(",") + std::to_wstring(pActiveMem_from->avStream.obj.resObj.uiObjType);
						str += _T(",a(")  +  std::to_wstring(pActiveMem_from->avStream.obj.tranInfo.audio.uiTranNo_openAvDev) + _T(",")
							+ std::to_wstring((int)pActiveMem_from->avStream.obj.tranInfo.audio.compressor.common.ucCompressors) + _T( ")"  );
						str += _T(" v("  )  +  std::to_wstring(pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev) + _T(  ",")
							+ std::to_wstring((int)pActiveMem_from->avStream.obj.tranInfo.video.compressor.common.ucCompressors)  +  _T(",")
							//
							+ std::to_wstring((int)pActiveMem_from->avStream.obj.tranInfo.video.compressor.common.usMaxFps_toShareBmp)+_T(",")
							//
							+ std::to_wstring(pActiveMem_from->avStream.obj.tranInfo.video.vh_decompress.bih.biWidth) + _T("x") + std::to_wstring(pActiveMem_from->avStream.obj.tranInfo.video.vh_decompress.bih.biHeight)  +_T(",")
							+  wFourccStr  
							+  _T(")");
						//
						if (pActiveMem_from->ucbNvr) {
							str += _T(" nvr");
						}
						//
						showState_open(0, _T("showTasks"), str.c_str(), CONST_stateType_tasks, 0, & when, iPos, pTaskInfo->var.iTaskId); iPos++;

					}
				}

				//
#if 0
				Param_tmp_showState_task param = new Param_tmp_showState_task();
				param.usStateType = Consts.CONST_stateType_tasks;
				param.usStateSubtype = 0;
				param.when = when;
				param.iPos = iPos;
				pProcInfo.processQ_media.qTraverse(null, tmp_showState_task, param, null); iPos = param.iPos;
#endif

				//
				break;
			default:
				str += _T(" other");

				//
				showState_open(0, _T("showTasks"), str.c_str(), CONST_stateType_tasks, 0, &when, iPos, pTaskInfo->var.iTaskId); iPos++;

				break;
			}





		}



		//
		if (qmcTaskInfo_bAlive( pProcInfo, index_taskInfo))
		{
			str = _T("task alive.");
		}
		else
		{
			str = _T("task not alive. ");
			if (pTaskInfo->var.bClosed) str += _T("closed.");
		}
		//
		//str += _T(" iStatus "  )  +  pMsgTask->iStatus;
		str += _T(" iStatus ")  +  std::to_wstring(pMsgTask->iStatus)  +  _T(" " );
		str += qyGetDesByType1(CONST_qyStatusTable_en, pMsgTask->iStatus);
		str += _T(".");

		//
		int iElapseInMs;
		iElapseInMs = abs((int)(uiTickCnt_now - pTaskInfo->var.dwTickCnt_recv_lastRefreshed));
		str += _T(" lastRecv: "  )  + std::to_wstring(iElapseInMs)+  _T("ms elapsed");
		showState_open(0, _T("showTasks"), str.c_str(), CONST_stateType_tasks, 0, &when, iPos, pTaskInfo->var.iTaskId); iPos++;

		//
		if (pQyMc->appParams.bConfServer) {
			MSG_ROUTE* pRca = &pTaskInfo->var.curRoute_sendLocalAv.route_confAv;
			tBuf[0] = 0;
			_sntprintf(tBuf, mycountof(tBuf), _T("route_confAv: to %I64u,"), pRca->idInfo_to.ui64Id);
			int  j;
			for (j = 0; j < mycountof(pRca->mems_to); j++) {
				if (!pRca->mems_to[j].idInfo.ui64Id)  break;
				_sntprintf(tBuf, mycountof(tBuf), _T("%s%d %I64u,"), tBuf, j, pRca->mems_to[j].idInfo.ui64Id);
			}
			showState_open(0, _T("showTasks"), tBuf, CONST_stateType_tasks, 0, &when, iPos, pTaskInfo->var.iTaskId); iPos++;
		}

		//
		str = _T("");
		showState_open(0, _T("showTasks"), str.c_str(), CONST_stateType_tasks, 0, &when, iPos, pTaskInfo->var.iTaskId); iPos++;




		//
		continue;
	}

	//
	str = _T("process_mediaQ.nQNodes "  )  + std::to_wstring(pProcInfo->processQ_media.m_var.uiQNodes);
	showState_open(0, _T("showTasks"), str.c_str(), CONST_stateType_tasks, 0, & when, iPos, 0); iPos++;

	//
	str = _T("notifyTaskStatus: ");
	str += _T("bAvCall ") + std::to_wstring(var.notifyTaskStatus.bAvCall) + _T(". ") + _T("bExists_task") + std::to_wstring(var.notifyTaskStatus.bExists_task) + _T(". ");
	str += _T("taskId ") + std::to_wstring(var.notifyTaskStatus.iTaskId)  +  _T(  ". "  );
	str += std::wstring(_T("hTool ")) + (IsWindow(var.notifyTaskStatus.hTool_dlgAvAccept) ? _T("ok") : _T("null"))  +  _T(  ". "  );
	showState_open(0, _T("showTasks"), str.c_str(), CONST_stateType_tasks, 0, &when, iPos, 0); iPos++;

	//
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	str = _T("");
	MIS_CHANNEL* pChannel;
	pChannel = getChannelByType(pMisCnt, CONST_channelType_talking);
	Param_dbg  param;
	param.m_pHint=(TCHAR*)_T("showState_task.1485");
	param.m_bShowInfo = false;
	//
	if (bChannelOk(pChannel,&param)) {
		str += _T("t ok ");
	}
	else {
		str += _T("t err ");
	}
	pChannel = getChannelByType(pMisCnt, CONST_channelType_media);
	if (bChannelOk(pChannel,&param)) {
		str += _T("v ok ");
	}
	pChannel = getChannelByType(pMisCnt, CONST_channelType_realTimeMedia);
	if (bChannelOk(pChannel,&param)) {
		str += _T("a ok");
	}
	showState_open(0, _T("showTasks"), str.c_str(), CONST_stateType_tasks, 0, &when, iPos, 0); iPos++;

	//
	str = _T("bExists_meeting ");
	str += (pProcInfo->status.avStatus.bExists_meeting ? _T("true") : _T("false"));
	showState_open(0, _T("showTasks"), str.c_str(), CONST_stateType_tasks, 0, &when, iPos, 0); iPos++;

	//
	_sntprintf(tBuf, mycountof(tBuf), _T("mix: ind_player %d, tn %d"), pProcInfo->av.mixProcInfo.iIndex_localPlayer, pProcInfo->av.mixProcInfo.uiTranNo_openAvDev_a);
	showState_open(0, _T("showTasks"), tBuf, CONST_stateType_tasks, 0, &when, iPos, 0); iPos++;

	




	//
	showState_open(0, _T("showTasks"), _T(""), CONST_stateType_tasks, 0, &when, iPos, 0); iPos++;

	//
	for (i = 0; i < pProcInfo->av.usCnt_players; i++) {
		QY_PLAYER* pPlayer = getPlayerByIndex(pProcInfo, i);
		if (!pPlayer->audio.uiPlayType
			&& !pPlayer->video.uiPlayType)
		{
			continue;
		}
		//
		_sntprintf(tBuf, mycountof(tBuf), _T("player[%d]: %I64u, a %d, v %d. aType %d. nodes %d"), i, pPlayer->idInfo_recorder.ui64Id, pPlayer->audio.uiTranNo, pPlayer->video.uiTranNo,  pPlayer->audio.uiPlayType,  getQ2Nodes(&pPlayer->audio.q2));
		showState_open(0, _T("showTasks"), tBuf, CONST_stateType_tasks, 0, &when, iPos, pPlayer->iTaskId); iPos++;
	}

	//
	showState_open(0, _T("showTasks"), _T(""), CONST_stateType_tasks, 0, &when, iPos, 0); iPos++;

	//
	AEC_layout* pAecLayout = &pProcInfo->av.aecInfo.aecLayout;
	if (pAecLayout->iTaskId) {
		for (i = 0; i < pAecLayout->usCntLimit_activeMems_from; i++) {
			AEC_player_cfg* pMem = &pAecLayout->mems[i];
			if (pMem->tn_a) {
				QY_PLAYER* pPlayer = getPlayerByIndex(pProcInfo, pMem->playerId.index_player);
				if (pPlayer) {
					if (pPlayer->playerId.uiTranNo_player == pMem->playerId.uiTranNo_player
						&& pPlayer->idInfo_recorder.ui64Id == pMem->idInfo.ui64Id
						&& pPlayer->audio.uiTranNo == pMem->tn_a)
					{
						_sntprintf(tBuf, mycountof(tBuf), _T("aec[%d]: %I64u %d, player%d"), i, pMem->idInfo.ui64Id,  pMem->tn_a,  pMem->playerId.index_player);
						showState_open(0, _T("showTasks"), tBuf, CONST_stateType_tasks, 0, &when, iPos, 0); iPos++;
					}

				}
			}
		}
	}
	



	//
	showState_open(0, _T("showTasks"), _T(""), CONST_stateType_tasks, 0, & when, -1, 0);


#if false

	if (0 == (var.loopCtrl % 2))
	{
		qyFuncs.showState_open(0, ("kk"), "kk", Consts.CONST_stateType_tasks, 0, ref when, 0);
		qyFuncs.showState_open(0, ("kk"), "kk1", Consts.CONST_stateType_tasks, 0, ref when, 1);
		qyFuncs.showState_open(0, ("kk"), "kk1", Consts.CONST_stateType_tasks, 0, ref when, -1);
	}
	else
	{
		qyFuncs.showState_open(0, ("mm"), "mm", Consts.CONST_stateType_tasks, 0, ref when, 0);
		qyFuncs.showState_open(0, ("mm"), "mm1", Consts.CONST_stateType_tasks, 0, ref when, 1);
		qyFuncs.showState_open(0, ("mm"), "mm2", Consts.CONST_stateType_tasks, 0, ref when, 2);
		qyFuncs.showState_open(0, ("mm"), "mm2", Consts.CONST_stateType_tasks, 0, ref when, -1);

			}
#endif

errLabel:

	return 0;
}


//


//
int  showState_sys(  )
{				
	static  int  stickCnt_last  =  0;
	DWORD  dwTickCnt  =  myGetTickCount(  mynull  );
	//if  (  dwTickCnt  -  stickCnt_last  >  1000  )  
	{

		CCtxQyMc  *  pQyMc  =  QY_GET_GBUF(  );
		CCtxQmc  *  pProcInfo  =  (  CCtxQmc  *  )pQyMc->get_pProcInfo(  );
		MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByIndex(  0  );
		if  (  !pMisCnt  )  return  -1;

		//
		TCHAR  tBuf[128]  =  _T(  ""  );

		//
					//
		int iPos = 0;

		//
		SYSTEMTIME when;
		GetLocalTime(& when);



		//
		TCHAR  tServ[128];
		myStr2TChar(  pMisCnt->server.ip,  tServ,  mycountof(  tServ  )  );
		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "FPS:% 6.1f IO:% 8.3f,% 8.3f t(%s,%03d) a(% 6.2f,% 6.2f %s,%03d) v(% 6.1f,% 6.1f %s,%03d) f(% 6.1f,% 6.1f %s,%03d) CPU %d%% %s"  ),  
			pProcInfo->status.render.fps,
			pProcInfo->status.netStat.ins.uiInSpeedInKbps  /  1000.,  pProcInfo->status.netStat.ins.uiOutSpeedInKbps  /  1000.,  
			pProcInfo->av.talk.bChannelReady  ?  _T(  "  "  )  :  _T(  "no"  ),
			pProcInfo->av.talk.iThreadsStatus,
			pProcInfo->status.netStat.uiInSpeedInKbps_a  /  1000.,  pProcInfo->status.netStat.uiOutSpeedInKbps_a  /  1000.,
			pProcInfo->av.audio.bChannelReady  ?  _T(  "  "  )  :  _T(  "no"  ),
			pProcInfo->av.audio.iThreadsStatus,
			pProcInfo->status.netStat.uiInSpeedInKbps_v  /  1000.,  pProcInfo->status.netStat.uiOutSpeedInKbps_v  /  1000.,
			pProcInfo->av.video.bChannelReady  ?  _T(  "  "  )  :  _T(  "no"  ),
			pProcInfo->av.video.iThreadsStatus,
			pProcInfo->status.netStat.uiInSpeedInKbps_f  /  1000.,  pProcInfo->status.netStat.uiOutSpeedInKbps_f  /  1000.,
			pProcInfo->av.robot.bChannelReady  ?  _T(  "  "  )  :  _T(  "no"  ),
			pProcInfo->av.robot.iThreadsStatus,
			pProcInfo->status.cpu.iCpuUsage,
			tServ
			);		
		//
		_sntprintf(pProcInfo->status.tSysStateDesc, mycountof(pProcInfo->status.tSysStateDesc), _T("FPS: %6.1f, %s"), pProcInfo->status.render.fps, tServ);
			
					
		//
		//showStatus_open(  0,  0,  tBuf,  0  );
		showState_open(0, _T(""), tBuf, CONST_stateType_sys, 0, & when, iPos, 0); iPos++;

		//
		showState_open(0, _T(""), _T(""), CONST_stateType_sys, 0, &when, -1, 0);

		
		//		
		stickCnt_last  =  dwTickCnt;			
	}

	//
	return  0;
}


//
//int 


int  tmpHandler_showTalks(void* p0, void* p1, MIS_MSGU* pMsgElem)
{
	COMMON_PARAM* pCommonParam = (COMMON_PARAM*)p0;
	// p1;

	int& iPos = *(int*)pCommonParam->p0;
	SYSTEMTIME& when = *(SYSTEMTIME*)pCommonParam->p1;


	TCHAR		tBuf[512] = _T("");
	int			i = 0;
	char		timeBuf[CONST_qyTimeLen + 1] = "";
	char		displayBuf[255 + 1] = "";
	int			j;
	QY_MC* pQyMc = QY_GET_GBUF();


	if (pMsgElem->uiType == CONST_misMsgType_talkingFriend_qmc) {
		HWND			hDlgTalk = pMsgElem->talkingFriend_qmc.hWnd;
		//  CDlgTalk	*	pDlg	=	(  CDlgTalk  *  )CWnd::FromHandle(  pMsg->talkingFriend_qmc.hWnd  );
		CHelp_getDlgTalkVar	help_getDlgTalkVar;
		DLG_talk_var* pDlgTalkVar = (DLG_talk_var*)help_getDlgTalkVar.getVar(hDlgTalk);
		if (!pDlgTalkVar)  goto  errLabel;
		DLG_talk_var& m_var = *pDlgTalkVar;

		//
		_sntprintf(tBuf, mycountof(tBuf), _T("talk %I64u, tn %d"), m_var.addr.idInfo.ui64Id, m_var.addr.uiTranNo_shadow);
		if (bObjTypeGrp(m_var.addr.uiObjType))  _sntprintf(tBuf, mycountof(tBuf), _T("%s grp"), tBuf);

		//
		showState_open(0, _T(""), tBuf, CONST_stateType_talks, 0, &when, iPos, 0); iPos++;

		//
		if (isTalkerShadowMgr(m_var.addr)) {
			if (m_var.av.taskInfo.bTaskExists) {
				_sntprintf(tBuf, mycountof(tBuf), _T("conf taskId %d"), m_var.av.taskInfo.iTaskId);
				//
				showState_open(0, _T(""), tBuf, CONST_stateType_talks, 0, &when, iPos, 0); iPos++;

			}
		}




	}

	errLabel:
	return  0;
}


//
int  showState_talks()
{
	static  int  stickCnt_last = 0;
	DWORD  dwTickCnt = myGetTickCount(mynull);
	//if  (  dwTickCnt  -  stickCnt_last  >  1000  )  
	{

		CCtxQyMc* pQyMc = QY_GET_GBUF();
		CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
		MIS_CNT* pMisCnt = pProcInfo->getMisCntByIndex(0);
		if (!pMisCnt)  return  -1;

		//
		TCHAR  tBuf[128] = _T("");

		//
					//
		int iPos = 0;

		//
		SYSTEMTIME when;
		GetLocalTime(&when);


		//
		COMMON_PARAM commonParam;
		MACRO_makeCommonParam3(&iPos, &when, 0, commonParam);

		//
		qTraverse(&pMisCnt->talkingFriendQ, (PF_commonHandler)tmpHandler_showTalks, &commonParam, 0);
		


		//
		showState_open(0, _T(""), _T(""), CONST_stateType_talks, 0, &when, -1, 0);


		//		
		stickCnt_last = dwTickCnt;
	}

	//
	return  0;
}



//
int  mainWnd_showStatus(QY_MC_mainWndVar  &  var)
{


	//
	showState_sys();

	int n_showState_tasks = 3;
#ifdef  __DEBUG__
	n_showState_tasks = 1;
#endif
	if (!(var.loopCtrl % n_showState_tasks)) {
		showState_tasks(var);


		//
		showState_talks();
	}




	//
	return  0;
}









#ifdef  __DEBUG__
//   CQyTick	tmpTick;
#endif

__declspec(dllexport)  int  mainWnd_OnTimer(HWND  hMainWnd, void* pVar, UINT  nIDEvent)
{
	int			iErr = -1;

	if (!pVar)  return  -1;
	QY_MC_mainWndVar& var = *(QY_MC_mainWndVar*)pVar;

	QY_MC* pQyMc = var.pQyMc;
	if (!pQyMc)  return  -1;

	MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return  -1;
	if (pProcInfo->m_iCtxType != CONST_ctxType_qmc) {
		return  -1;
	}
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt) {
		return -1;
	}
	//
	char		licenseInfo[128] = "";
	//static  int	siCnt				=	0;

	var.loopCtrl++;

	//
	{
		MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
		__int64 id = pMisCnt->idInfo.ui64Id;
		if (id) {
			int ii = 0;
		}
	}



	//
	if (pQyMc->bQuit) {		//  Èç¹û£¬ÒªÍË³öÁË£¬¾Í·¢¸ö¹Ø±ÕÏûÏ¢°É£®
		//if (!pProcInfo->bAppQt()) 
		{
			SendMessage(hMainWnd, WM_CLOSE, 0, 0);
		}
		//
		iErr = CONST_qyRet_quit;  goto  errLabel;
	}
	if (pQyMc->bGuiQuit) {	//  ÕâÀïÊÇ£¬Òª¿´ÓÐÃ»ÓÐ½çÃæÔªËØÐèÒªÇå³ý¡£ÒªÊÇÃ»ÓÐ£¬¾Í½«bQuitÉèÎªtrue

		pQyMc->usTimes_tryToQuit++;

		if (isIsCli(pQyMc)) {

			//  
			stopAll_avRecord();
			stopAll_sharedObjs(pProcInfo);

			freeAllSharedObjs(pProcInfo);

			closeOtherPlayers(pProcInfo);

#if  0
			if (pQyMc->usTimes_tryToQuit < 7) {

				//  avRecord
				if (!bNoSharedObjExists(pProcInfo)) {
					OutputDebugString(_T("Shared Objects still exist.\n"));
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("Gui"), NULL, _T(""), _T(""), _T("SharedObjects still exits. %d times"), pQyMc->usTimes_tryToQuit);

					//  ÊÔÍ¼»ØÊÕ×ÊÔ´
					tryToFreeSharedObjs(pProcInfo);

					iErr = CONST_qyRet_quit;	goto  errLabel;
				}

			}
#endif

		}

		pQyMc->bQuit = TRUE;
		SendMessage(hMainWnd, WM_CLOSE, 0, 0);
		iErr = CONST_qyRet_quit;	goto  errLabel;
	}

#ifndef  __WINCE__
#if  !defined(  __isCli__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
	if (var.pm_wndStatusBar) {
		getQnmLicenseInfo(&pQyMc->licenseCtx, licenseInfo, sizeof(licenseInfo));
		int  iIndex = var.pm_wndStatusBar->CommandToIndex(ID_INDICATOR_licenseInfo);
		if (iIndex < 0) {
#ifdef  __DEBUG__
			traceLog((TCHAR*)_T("mainWnd_OnTimer: statusBar.CommandToIndex failed"));
#endif
		}
		else {
			var.pm_wndStatusBar->SetPaneText(iIndex, CQyString(licenseInfo), TRUE);
		}
	}
#endif
#endif


	if (isIsCli(pQyMc)) {

		//  		
		if (!(var.loopCtrl % 1))  bChkMessengerChannelsReady(pQyMc);

		//
		if (pQyMc->cfg.ucbUseTrayIcon) {


			//  
			if (!(var.loopCtrl % 5)) {
#ifndef  __WINCE__	
				int		iIDR_iconStr = bMeOnline(pQyMc) ? IDR_TRAY_online : IDR_TRAY_offline;;
				sendTrayMsg(pQyMc->g_hInst, hMainWnd, pQyMc->cfg.iIDR_TRAY, NIM_MODIFY, iIDR_iconStr, CONST_qyWm_trayNotify);
#endif
			}
		}

		if (pProcInfo) {

			if (!(var.loopCtrl % pProcInfo->cfg.loopCtrl_chkPlayers)
				|| pProcInfo->ctrl.bNeedChkPlayers)
			{
				pProcInfo->ctrl.bNeedChkPlayers = FALSE;  //  2018/06/16
				//
				chkPlayers(pProcInfo);
			}
			//
			if (GetTickCount() - pProcInfo->status.notification.dwTickCnt_lastDisplayed > 900)  displayNotification(NULL, NULL);
			//
#ifdef  __DEBUG__
		//  viewNotification(  );
#endif

			if (pProcInfo->status.waitToQuit.dwTickCnt_start) {
				if (GetTickCount() - pProcInfo->status.waitToQuit.dwTickCnt_start > pProcInfo->status.waitToQuit.dwTimeInMs) {
					traceLog((TCHAR*)_T("It's time to quit"));
					notifyPanicToApp(pQyMc, -1, _T(""));
				}
			}

			//
			if (!(var.loopCtrl % pProcInfo->cfg.loopCtrl_chkTasks)
				|| pProcInfo->ctrl.bNeedChkTasks)
			{
				pProcInfo->ctrl.bNeedChkTasks = FALSE;  //  2018/06/16
				//			
				mainWnd_chk_tasks(hMainWnd, &var);
			}

			//  2011/03/30
			if (pProcInfo->g_hVWall) {
				if (!IsWindow(pProcInfo->g_hVWall))  pProcInfo->g_hVWall = NULL;
			}

			if (1) {
				HWND	hFore;
				if (pQyMc->gui.hWnd_menu) {
					if (!IsWindow(pQyMc->gui.hWnd_menu))  pQyMc->gui.hWnd_menu = NULL;
					else {
						hFore = GetForegroundWindow();
						if (hFore != pQyMc->gui.hWnd_menu) {
							if (bDlgTalkAbove(pQyMc->gui.hWnd_menu)) {
								traceLog((TCHAR*)_T("Wnd_menu is blow a dlgTalk, so setForegroundWindow menu"));
								SetForegroundWindow(pQyMc->gui.hWnd_menu);
							}
						}
					}
				}
				if (pQyMc->gui.hWnd_fileDialog) {
					if (!IsWindow(pQyMc->gui.hWnd_fileDialog))  pQyMc->gui.hWnd_fileDialog = NULL;
					else {
						if (GetTickCount() - pQyMc->gui.dwStartTickCnt_fileDialog > 30000) {
#ifdef  __DEBUG__
							traceLog((TCHAR*)_T("fileDialog timeout"));
#endif
							PostMessage(pQyMc->gui.hWnd_fileDialog, WM_CLOSE, 0, 0);
						}
						hFore = GetForegroundWindow();
						if (hFore != pQyMc->gui.hWnd_fileDialog) {
							SetForegroundWindow(pQyMc->gui.hWnd_fileDialog);
						}
					}
				}
				else {
					if (pQyMc->gui.hWnd_modal) {
						if (!IsWindow(pQyMc->gui.hWnd_modal))  pQyMc->gui.hWnd_modal = NULL;
						else {
							hFore = GetForegroundWindow();
							if (hFore != pQyMc->gui.hWnd_modal) {
								if (bDlgTalkAbove(pQyMc->gui.hWnd_modal)) {
									traceLog((TCHAR*)_T("wnd_modal is below a dlgTalk, so setForegroundWindow modal"));
									SetForegroundWindow(pQyMc->gui.hWnd_modal);
								}
							}
						}
					}
				}
			}

#ifdef  __isCli__
			//  2012/08/01
#if  0  //  2015/09/20
			if (pProcInfo->ptz.pComPort) {
				if (!IsWindow(pProcInfo->ptz.hWnd_localPtzControl)) {
					if (!isActive_comPort_ptz()) {

						qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("mainWnd_OnTimer, comPort is not active, to exitPtz "));

						exitPtz();
					}
				}
			}
#endif

			//  2013/03/07
			if (!(var.loopCtrl % 5)) {
				qisChkDb_gui_myDb();
				//  2014/12/22
				if (pProcInfo->status.sysErr.bFailed_newSharedObj) {
					pProcInfo->status.sysErr.bFailed_newSharedObj = FALSE;
					//
					showInfo_open0(0, 0, _T("mainWnd_timer: bFailed_newSharedObj true. to chk sharedObj"));
					//  2009/12/28
					PostMessage(pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_task_end, 0);
				}
			}

			//  2013/08/07

			//  2013/08/01
			if (pMisCnt->retrieveImObjList.ulbAllContactsRetrieved) {
				if (pMisCnt->retrieveImObjList.nTimes_refresh < 5) {
					DWORD	dwTickCnt = GetTickCount();
					if (dwTickCnt - pMisCnt->retrieveImObjList.dwTickCnt_lastRefreshed > 2000) {
						pMisCnt->retrieveImObjList.nTimes_refresh++;
						pMisCnt->retrieveImObjList.dwTickCnt_lastRefreshed = dwTickCnt;
						//
						PostMessage(pQyMc->gui.hMainWnd, WM_COMMAND, MAKEWPARAM(ID_qyRefresh, 0), 0);
					}
				}
			}

			//   2017/09/13
			if (!(var.loopCtrl % 30)) {
				chkSharedObjs(pProcInfo);
			}

#endif

			//
			if (pProcInfo) {
				pProcInfo->chkDualSystemHotBackup();
			}

			//
#ifdef  __DEBUG__
#if  0
			int  iCurTickCnt = timeGetTime();//GetTickCount(  );
			int  t = myGetTickCount(NULL);
			TCHAR  tBuf[128];
			_sntprintf(tBuf, mycountof(tBuf), _T("mainWnd_OnTimer: tickCnt  -  tick.tickCnt %d"), iCurTickCnt - t);
			showInfo_open0(0, 0, tBuf);
#endif
#ifdef  __isCli__
			test_myDb(_T("mainWnd"));
#endif
#endif


		}

		//
		//
		pProcInfo->do_mainWnd_OnTimer(hMainWnd, pVar, nIDEvent);

		//
		mainWnd_showStatus(var);

		//
#if 0
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
#endif


	}

	//
#if 0
	if (pProcInfo->av.doConf.bStartToQuitApp) {
		MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
		if (pMisCnt == NULL)  goto  errLabel;
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
#endif

	//
	//chkSmTmpLogFile();

	//


	//
	if (pProcInfo->m_bUseKeyToLogin_forQmcGui) {
		TCHAR  tBuf[128];
		_sntprintf(tBuf, mycountof(tBuf), _T("%d"), pQyMc->appParams.iSeqNoSelected_appObjPrefix);
		Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
		if (pCtxSm) {
			_sntprintf(tBuf, mycountof(tBuf), _T("%s: %s %s"), tBuf, pCtxSm->smTerminalInitCfg.devPrefix,  pCtxSm->smTerminalInitCfg.fake_usrName);
		}
		//
		_sntprintf(tBuf, mycountof(tBuf), _T("%s: %s %s"), tBuf, pProcInfo->av.confLayout.login_termialName,  pProcInfo->av.confLayout.login_userName);
		//
		SetWindowText(pQyMc->gui.hGuiWnd, tBuf);

	}


	//
#ifdef  __DEBUG__
	//
	//pProcInfo->testFunc();
	if (pQyMc->bLogon) {
		


		int send_showInfo(int mainWnd_loopCtrl);

		//send_showInfo(0);
	}
	//
	//traceLog((TCHAR *)_T("commEncCtx.type %d"), pMisCnt->commEncCtx.common.type);
	//traceLog((TCHAR*)_T("localIp %S"), pProcInfo->authInfo.ip);

	//
	//logForHg(CONST_hgLogType_sxrzsb, (TCHAR*)_T("失败了"));



	//
	//traceLog(_T(  "d3d.fps %f"  ), pProcInfo->status.render.fps);

	//
	

#endif


	//
	iErr = 0;

errLabel:

	return  iErr;
}





 __declspec(  dllexport  )  int  mainWnd_OnQyQuitMainWnd(  HWND  hMainWnd,  void  *  pVar  )  
 {
	 if  (  !pVar  )  return  -1;
	 QY_MC_mainWndVar  &  var  =	*(  QY_MC_mainWndVar  *  )pVar;
	 
	 QY_MC	*	pQyMc	=	var.pQyMc;
	 if  (  !pQyMc  )  return  -1;
	 MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pQyMc->get_pProcInfo(  );
	 if  (  !pProcInfo  )  return  -1;
	 if  (  pProcInfo->m_iCtxType  !=  CONST_ctxType_qmc  )  return  -1;

	 //
	 showInfo_open0(0, 0, _T("mainWnd_OnQyQuitMainWnd called"));


	 {
		 CQySyncFlg  syncFlg;
		 if  (  syncFlg.sync(  &pQyMc->bPrepareToGuiQuit  )  )  {
			 showInfo_open0(  0,  0,  _T(  "mainWnd_OnQyQuitMainWnd failed, sync bPrepareToGuiQuit failed"  )  );
			 return  -1;
		 }

		 //  2017/10/03
		 if  (  pProcInfo->status.waitToQuit.dwTickCnt_start  )  {
			 pQyMc->bGuiQuit  =  TRUE;
		 }

		 //
		 //cloc



		 //
		 if  (  isIsCli(  pQyMc  )  )  {
			 //
			 pProcInfo->gui_notify_clear();
			 //
			BOOL		bConversationExists		=	FALSE;	
			//  
			closeAllConversations(  pQyMc,  &bConversationExists  );
			if  (  bConversationExists  )  {
				#ifdef  __DEBUG__
						traceLogA(  (char*)  "try to close all conversations, but some still exist."  );	
				#endif
				return  -1;
			}	
			#ifdef  __DEBUG__
					traceLogA(  (char*)  "All conversations are closed."  );
			#endif

			//  
			BOOL		bOtherWndExists  =  FALSE;
			closeOtherWnds_isCli(  &bOtherWndExists  );
			if  (  bOtherWndExists  )  {
				#ifdef  __DEBUG__
						traceLog((TCHAR*)  _T(  "try to close all other wnds, but some still exist"  )  );
				#endif
				return  -1;
			}

			//
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "All other wnds are closed"  )  );
			#endif

		}
		if  (  isIsMgr(  pQyMc  )  )  {
			closeOtherWnds_isMgr(  NULL  );
		}
		else  {
			TCHAR  tBuf[256];

			if  (  !pQyMc->appParams.iSeqNoSelected_appObjPrefix  )  {
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
			}
			else  {
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\%d"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  pQyMc->appParams.iSeqNoSelected_appObjPrefix  );			
			}
		
			//
			qySetRegCfgT(  HKEY_CURRENT_USER,  tBuf,  _T(  CONST_regValName_ucbAutoLogon  ),  _T(  "0"  )  );   
		
		}

	 }

	//
	pQyMc->bGuiQuit  =  TRUE;

	//  再一次的清理
	if  (  isIsCli(  pQyMc  )  )  {
		//  maybe new talker tiggered. 2010/09/06
		closeAllConversations(  pQyMc,  NULL  );
		//  2011/10/15
		closeOtherWnds_isCli(  NULL  );
		
		//  2017/01/04. imObjView应该最后一个关闭
		if  (  IsWindow(  pProcInfo->hWnd_imObjView  )  )  {
			SendMessage(  pProcInfo->hWnd_imObjView,  WM_CLOSE,  0,  0  );
			if  (  !IsWindow(  pProcInfo->hWnd_imObjView  )  )  pProcInfo->hWnd_imObjView  =  NULL;	
		}

		//  2015/06/08. ts_3d时，3d wnd实际当主窗口用，所以在这里关闭		
		//  2013/07/03
		MC_VAR_common  *  pProcInfoCommon  =  (MC_VAR_common*)pQyMc->get_pProcInfo(  );
		if  (  dyn_closeConsoleWall(  pProcInfoCommon,  pQyMc->pGBuf_d3d  )  )  {
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "closeOtherWnds_isCli: closeTestWnd_d3d failed"  )  );
			#endif			
		}
		//  2017/01/04



		

	}

	//  2012/05/16
	exitTestGps(  );

	//
	ipcProc_exit();

	//
	if (pProcInfo->bAppQt()) {
		Sleep(2 * 1000);
		SendMessage(hMainWnd, WM_CLOSE, 0, 0);
	}
	else {
		SendMessage(hMainWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
	}

	//
	return  0;
}


 __declspec(  dllexport  )  int  mainWnd_OnClose(  HWND  hMainWnd,  void  *  pVar  )  
 {
	 if  (  !pVar  )  return  -1;
	 QY_MC_mainWndVar  &  var  =	*(  QY_MC_mainWndVar  *  )pVar;
	 
	 QY_MC	*	pQyMc					=	var.pQyMc;
	 if  (  !pQyMc  )  return  -1;

	 //
	 #ifdef  __DEBUG__
			 traceLog((TCHAR*)  _T(  "CMainFrame::OnClose"  )  );
	 #endif

	//
	if  (  pQyMc->iAppType  !=  CONST_qyAppType_client  )  {		//  Ö»ÓÐ·Ç¿Í»§¶ËµÄ²ÅÖ±½ÓÍË³ö£®
		if  (  !pQyMc->bGuiQuit  )  {
			mainWnd_OnQyQuitMainWnd(  hMainWnd,  &var  );
			return  1;
		}
	}

	if  (  !pQyMc->bQuit  )  {		
		#if  1  //  !defined(  __WINCE__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
				SendMessage(  hMainWnd,  WM_SYSCOMMAND,  SC_MINIMIZE,  0  );
		#endif
		return  1;
	}

	return  0;
}


#if defined(  __WINCE__  )  ||  defined(  __APP_qyMc_touchscreen__  )
  int  tmpHandler_displayNotification(  void  *  p0,  LPCTSTR  tBuf,  void  *  pElem  )
{
	MIS_MSGU	*	pMsg	=	(  MIS_MSGU  *  )pElem;
	if  (  pMsg->uiType  ==  CONST_misMsgType_talkingFriend_qmc  )  {
		//  Send
		#if  0
			CDlgTalk_ce		*	pWnd	=	(  CDlgTalk_ce  *  )CQyWnd::FromHandle(  pMsg->talkingFriend_qmc.hWnd  );
			if  (  pWnd  )  {
				PF_commonHandler	pf	=	(  PF_commonHandler  )pWnd->m_var.guiData.pf_displayNotification_talk_ce;
				if  (  pf  )  pf(  pWnd->m_hWnd,  pWnd->getGuiData(  ),  (  void  *  )tBuf  );			
			}
		#endif
			CHelp_getDlgTalkVar	help_getDlgTalkVar;
			DLG_TALK_var	*	pDlgTalkVar	=	(  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  pMsg->talkingFriend_qmc.hWnd  );
			if  (  pDlgTalkVar  )  {
				PF_commonHandler	pf	=	(  PF_commonHandler  )pDlgTalkVar->guiData.pf_displayNotification_talk_ce;
				if  (  pf  )  pf(  pMsg->talkingFriend_qmc.hWnd,  &pDlgTalkVar->guiData,  (  void  *  )tBuf  );			
			}

	}

	return  0;
}
#else
  int  tmpHandler_displayNotification(  void  *  p0,  LPCTSTR  tBuf,  void  *  pElem  )
{
	return  0;
}
#endif

  //
  BOOL  bEnable_showNotification(  MC_VAR_isCli  *  pProcInfo  )
 {
	if  (  !pProcInfo  )  return  FALSE;

	if  (  !pProcInfo->cfg.policy.ucbShowNotification  )  return  FALSE;
	
	if  (  dyn_bFullScreen_d3dWnd(  pProcInfo,  NULL  )  )  return  FALSE;

	return  TRUE;
 }

  //
 int  displayNotification(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_taskStatus  *  pStatus  )
{
	int					iErr		=	-1;
	//
	if  (  !pProcInfo  )  return  -1;

	//
	pProcInfo->status.notification.dwTickCnt_lastDisplayed  =  GetTickCount(  );

#if 1//defined(  __SUPPORT_dlgNotification__  )  
			
	if  (  pStatus
		&&  bEnable_showNotification(  pProcInfo  )	//  pProcInfo->cfg.policy.ucbShowNotification  
		)  
	{

		 if  (  !IsWindow(  pProcInfo->hWnd_notification  )  )  {
			 popupNotificationWnd(  );
		 }

		 if  (  !IsWindow(  pProcInfo->hWnd_notification  )  )  goto  errLabel;

		 if  (  addNotification(  pStatus  )  )  goto  errLabel;
	}

#endif

	//
	MIS_CNT* pMisCnt; pMisCnt = pProcInfo->getMisCntByName(_T(""));
	if  (  !pMisCnt  )  goto  errLabel;


#if defined(  __WINCE__  )  ||  defined(  __APP_qyMc_touchscreen__  )

    //  这里将通知显示在bar或status上。
	if  (  !pStatus  )  {
		if  (  isQEmpty(  &pMisCnt->talkingFriendQ  )  )  {
			//  2012/07/07
			_sntprintf(  pProcInfo->status.notification.tBuf,  mycountof(  pProcInfo->status.notification.tBuf  ),  _T(  "%I64u, %s. ( Menu )"  ),  pMisCnt->idInfo.ui64Id,  pMisCnt->talkerDesc  );
			pProcInfo->status.notification.tBuf[mycountof(  pProcInfo->status.notification.tBuf  )  -  1]  =  0;
			pProcInfo->status.notification.len  =  lstrlen(  pProcInfo->status.notification.tBuf  );
			//
			::SetDlgItemText(  g_pQyMc->gui.hMainWnd,  IDC_BUTTON_bar,  pProcInfo->status.notification.tBuf  );
			//
			iErr  =  0;  goto  errLabel;
		}
	}

	if  (  pStatus  )  {	
		pProcInfo->status.notification.tBuf[0]  =  0;
		if  (  pStatus->u.notification.idInfo_from.ui64Id  )  {
			getTalkerDesc(  pStatus->u.notification.idInfo_from,  NULL,  0,  pProcInfo->status.notification.tBuf,  mycountof(  pProcInfo->status.notification.tBuf  )  );
			_sntprintf(  pProcInfo->status.notification.tBuf,  mycountof(  pProcInfo->status.notification.tBuf  ),  _T(  "%s: "  ),  pProcInfo->status.notification.tBuf  );
		}
		if  (  pStatus->uiContentType  )  {
			_sntprintf(  pProcInfo->status.notification.tBuf,  mycountof(  pProcInfo->status.notification.tBuf  ),  _T(  "%s%s, "  ),  pProcInfo->status.notification.tBuf,  qyGetDesByType1(  getResTable(  0,  &g_pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pStatus->uiContentType  )  );
		}
		if  (  pStatus->u.notification.tBuf[0]  )  {
			_sntprintf(  pProcInfo->status.notification.tBuf,  mycountof(  pProcInfo->status.notification.tBuf  ),  _T(  "%s%s"  ),  pProcInfo->status.notification.tBuf,  pStatus->u.notification.tBuf  );
		}
		pProcInfo->status.notification.tBuf[mycountof(  pProcInfo->status.notification.tBuf  )  -  1]  =  0;
		pProcInfo->status.notification.len  =  lstrlen(  pProcInfo->status.notification.tBuf  );
	}
	pProcInfo->status.notification.tBuf[pProcInfo->status.notification.len]  =  0;

	//  2010/07/28
	if  (  !isQEmpty(  &pMisCnt->talkingFriendQ  )  )  {
		TCHAR	tBuf1[128]	=  _T(  ""  );
		int		iIndex  =  getSharedObjIndex_localAv(  );
		QY_SHARED_OBJ	*	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex  );
		if  (  pSharedObj  
			&&  !pSharedObj->bQuit
			&&  pSharedObj->bUsed  )
		{
			int	iIndex_capBmp  =  pSharedObj->iIndex_capBmp;
			CAP_procInfo_bmpU  *  pCapBmp  =  getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );
			if  (  pCapBmp  )  {
				_sntprintf(  tBuf1,  mycountof(  tBuf1  ),  _T(  " (%dX%d),"  ),  pCapBmp->common.compressVideo.vh_decompress.bih.biWidth,  pCapBmp->common.compressVideo.vh_decompress.bih.biHeight  );  
			}
		}
		//
		_sntprintf(  pProcInfo->status.notification.tBuf,  mycountof(  pProcInfo->status.notification.tBuf  ),  _T(  "%s | %d%%,%dM,%s (%d,%d)"  ),  pProcInfo->status.notification.tBuf,  pProcInfo->status.cpu.iCpuUsage,  pProcInfo->status.memory.dwAvailPhys  /  (  1024  *  1024  ),  tBuf1,  pProcInfo->status.netStat.ins.uiInSpeedInKbps,  pProcInfo->status.netStat.ins.uiOutSpeedInKbps  );
	}

	//
#if  0
	traceLog((TCHAR*)  _T(  "diaplayNotification: %s"  ),  pProcInfo->status.notification.tBuf  );
#endif

	//
	if  (  !isQEmpty(  &pMisCnt->talkingFriendQ  )  )  {

		 qTraverse(  &pMisCnt->talkingFriendQ,  (  PF_commonHandler  )tmpHandler_displayNotification,  0,  (  void  *  )pProcInfo->status.notification.tBuf  );

		}
	else  {
		  CQyWnd  *  pWnd  =  CQyWnd::FromHandle(  g_pQyMc->gui.hMainWnd  );
		  if  (  pWnd  )  {
			  WND_guiData_main	*	pGuiData  =  (  WND_guiData_main  *  )pWnd->getGuiData(  );
			  if  (  pGuiData  )  {
				  PF_commonHandler	pf	=	(  PF_commonHandler  )pGuiData->pf_displayNotification_mainWnd;
				  if  (  pf  )  pf(  pWnd,  pWnd->m_hWnd,  (  void  *  )pProcInfo->status.notification.tBuf  );
			  }
		  }		  
	}

#endif

	iErr  =  0;

errLabel:

	return  0;	//  iErr;

}



////

