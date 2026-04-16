

#include	"stdafx.h"
#include	<stdlib.h>
#include	<math.h>
#include	<tchar.h>
#include	<commdlg.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"
#include	"qmcVWall.h"
#include	"WallTalkers.h"

#include	"dlgDesktopsMonProc.h"
#include	"DlgDynBmpsProc.h"
#include	"dlgVideosProc.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyVk.h"

#include	"qmcDxSurfacePublic.h"

#include	"qyCusResTemp.h"

#include	"qyAvRecordPublic.h"

#include	"sp.h"



#include	"dlgTalkProc.h"

#include	"qmcGpsProc.h"
//
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"dlgSelect_isCli_public.h"

#include	"myDb.h"
#include	"isCliD3dPublic.h"

#include	"qyCusResTemp.h"
#include	"qmcCmdProc.h"

#include	"qisWallsProc.h"


 //  __declspec(  dllexport  )  BOOL  d3dWall_isUserActive(  )
__declspec(  dllexport  )  BOOL  d3dWall_isUserActive(  int  *  piElapseInMs_userActive  )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;

#define		CONST_minIntervalInMs_ui	20000
	DWORD  dwTickCnt  =  GetTickCount(  );
	
#if  0
	if  (  dwTickCnt  -  pProcInfo->status.param_d3dWall.command.dwLastTickCnt  <  CONST_minIntervalInMs_ui
		||  dwTickCnt  -  pProcInfo->status.param_d3dWall.mousemove.dwLastTickCnt  <  CONST_minIntervalInMs_ui
		||  dwTickCnt  -  pProcInfo->status.param_d3dWall.lButtonDown.dwLastTickCnt  <  CONST_minIntervalInMs_ui  )
	{
		return  TRUE;
	}
#endif
	int  iElapseInMs_command  =  dwTickCnt  -  pProcInfo->status.param_d3dWall.command.dwLastTickCnt;
	int  iElapseInMs_mousemove  =  dwTickCnt  -  pProcInfo->status.param_d3dWall.mousemove.dwLastTickCnt;
	int  iElapseInMs_lButtonDown  =  dwTickCnt  -  pProcInfo->status.param_d3dWall.lButtonDown.dwLastTickCnt;
	
	int  min_iElapseInMs  =  999000;
	if  (  iElapseInMs_command  >=  0  )  min_iElapseInMs  =  min(  min_iElapseInMs,  iElapseInMs_command  );
	if  (  iElapseInMs_mousemove  >=  0  )  min_iElapseInMs  =  min(  min_iElapseInMs,  iElapseInMs_mousemove  );
	if  (  iElapseInMs_lButtonDown  >=  0  )  min_iElapseInMs  =  min(  min_iElapseInMs,  iElapseInMs_lButtonDown  );

	//
	if  (  piElapseInMs_userActive  )  {
		*piElapseInMs_userActive  =  min_iElapseInMs;
	}

	
	//
	if  (  min_iElapseInMs  <  CONST_minIntervalInMs_ui  )
	{
		return  TRUE;
	}


	return  FALSE;
}





  




 //
  __declspec(  dllexport  )  int  dlgTalk_getTaskInfo(  void  *  pProcInfoParam,  HWND  hTalkerMgr,  void  *  pTALKER_task_info  )
 {
	 int  iErr  =  -1;
	 MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pProcInfoParam;
	 if  (  !pProcInfo  )  return  -1;
	 TALKER_task_info  *  pTaskInfo  =  (  TALKER_task_info  *  )pTALKER_task_info;
	 if  (  !pTaskInfo  )  return  -1;

	 memset(  pTaskInfo,  0,  sizeof(  pTaskInfo[0]  )  );

	 TALKER_task_info  &  taskInfo  =  *pTaskInfo;
	 
			CHelp_getDlgTalkVar	help_getDlgTalkVar;
			
			DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hTalkerMgr  );
			if  (  !pMgrVar  )  goto  errLabel;
			if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;
			//
			int  nScreens  =  0,  nMediaFiles  =  0;
			int  iW_screen  =  0,  iH_screen  =  0;
			BOOL	bExists_resource  =  FALSE;
			
			//  2014/11/30
			taskInfo.av.bTaskExists1  =  pMgrVar->av.taskInfo.bTaskExists;
			taskInfo.av.ucbStarter  =  pMgrVar->av.taskInfo.ucbStarter;
			taskInfo.av.ucbVideoConference  =  pMgrVar->av.taskInfo.ucbVideoConference;

			taskInfo.av.iTaskId  =  pMgrVar->av.taskInfo.iTaskId;

			//
			if  (  taskInfo.av.bTaskExists1  )  {
				if  (  taskInfo.av.ucbStarter  )  {
					taskInfo.av.mosaicVideo.bih  =  pMgrVar->av.taskInfo.mosaicMaker.video.bih_mosaic;
					taskInfo.av.mosaicVideo.bSupported_pktResType_sharedTex2  =  pMgrVar->av.taskInfo.mosaicMaker.video.var.bSupported_pktResType_sharedTex3;			//  2015/10/21
					{
						 int  iIndex_sharedObj  =  pMgrVar->av.taskInfo.mosaicMaker.video.var.iIndex_sharedObj;	 
						 //
						 QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );		
						 if  (  !pSharedObj  )  goto  errLabel;	 
			
						 int  iIndex_capBmp  =  pSharedObj->iIndex_capBmp;
						 CAP_procInfo_bmpU  *  pCapBmp  =  getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );
						 if  (  !pCapBmp  )  goto  errLabel;
						 
						 //
						 taskInfo.av.mosaicVideo.usMaxFps_toShareBmp  =  pCapBmp->common.compressVideo.usFrames_perSecond_expected;	 
					}
					//
					taskInfo.av.mosaicResource.bih  =  pMgrVar->av.taskInfo.mosaicMaker.resource.bih_mosaic;
					taskInfo.av.mosaicResource.bSupported_pktResType_sharedTex2  =  pMgrVar->av.taskInfo.mosaicMaker.resource.var.bSupported_pktResType_sharedTex3;	//  2015/10/21
					{
						 int  iIndex_sharedObj  =  pMgrVar->av.taskInfo.mosaicMaker.resource.var.iIndex_sharedObj;	 
						 //
						 QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );		
						 if  (  !pSharedObj  )  goto  errLabel;	 
			
						 int  iIndex_capBmp  =  pSharedObj->iIndex_capBmp;
						 CAP_procInfo_bmpU  *  pCapBmp  =  getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );
						 if  (  !pCapBmp  )  goto  errLabel;
						 
						 //
						 taskInfo.av.mosaicResource.usMaxFps_toShareBmp  =  pCapBmp->common.compressVideo.usFrames_perSecond_expected;	 

						 //
						 TCHAR  tBuf[128];
						 _sntprintf(tBuf, mycountof(tBuf), _T("rtt:getTaskInfo: resource.fps %d"), taskInfo.av.mosaicResource.usMaxFps_toShareBmp);
						 showInfo_open0(0, 0, tBuf);
					}
					}
				else  {  //  2017/09/02
					  if  (  pMgrVar->av.taskInfo.mosaicTrans.bExists_confMosaic  )  {
						#if  0
						  taskInfo.av.mosaicVideo.uiTranNo_openAvDev  =  pMgrVar->av.taskInfo.mosaicTrans.uiTranNo_openAvDev_confMosaic_video;
						  taskInfo.av.mosaicResource.uiTranNo_openAvDev  =  pMgrVar->av.taskInfo.mosaicTrans.uiTranNo_openAvDev_confMosaic_resource;
						#endif
					  }

				}
			}

			//
			bExists_resource  =  bTaskExists_recvResource(  pMgrVar,  &nScreens,  &nMediaFiles,  NULL,  &iW_screen,  &iH_screen,  NULL  );

			taskInfo.recvdResource.bExists_resource  =  bExists_resource;
			taskInfo.recvdResource.nScreens  =  nScreens;
			taskInfo.recvdResource.nMediaFiles  =  nMediaFiles;
			taskInfo.recvdResource.iW_screen  =  iW_screen;
			taskInfo.recvdResource.iH_screen  =  iH_screen;
		

			//  2014/12/01
			 if  (  bTaskExists_sendingResource(  pMgrVar,  &nScreens,  &nMediaFiles,  NULL,  NULL,  NULL,  NULL  )  )  {
				 taskInfo.sendingResource.bExists_resource1  =  TRUE;
				 taskInfo.sendingResource.nScreens  =  nScreens;
				 taskInfo.sendingResource.nMediaFiles  =  nMediaFiles;
			}


			 //
			 unsigned  char  ucb2Streams = 0;
			 if (pMgrVar->av.taskInfo.bTaskExists) {
				 QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex((CCtxQmc*)pProcInfo, pMgrVar->av.taskInfo.iIndex_taskInfo);
				 if (pTaskInfo) {
					 if (pTaskInfo->var.pTaskData->uiType == CONST_taskDataType_conf) {
						 QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
						 ucb2Streams = pTc->ucb2Streams;
					 }
				 }
			 }
			 taskInfo.av.ucb2Streams = ucb2Streams;



	 
	 iErr  =  0;
errLabel:
	 return  iErr;

 }


  //
  //int  dlgTalk_getTaskList(  TALKER_task_list  *  pTaskList  )	
  __declspec(  dllexport  )  int  dlgTalk_getTaskList(  void  *  pProcInfoParam,  HWND  hTalkerMgr,  void  *  pTALKER_task_list,  BOOL  *  pbModified  )
 {
	 int  iErr  =  -1;
	 MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pProcInfoParam;
	 if  (  !pProcInfo  )  return  -1;
	 TALKER_task_list  *  pTaskList  =  (  TALKER_task_list  *  )pTALKER_task_list;
	 if  (  !pTaskList  )  return  -1;

	 memset(  pTaskList,  0,  sizeof(  pTaskList[0]  )  );

	 TALKER_task_list  &  taskList  =  *pTaskList;
	 			
	 CHelp_getDlgTalkVar	help_getDlgTalkVar;
		
	 DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hTalkerMgr  );	
	 if  (  !pMgrVar  )  goto  errLabel;
	 if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;

	 //
	 if  (  !pMgrVar->m_pProcessQ  )  goto  errLabel;
	 GENERIC_Q		&	m_processQ		=	*pMgrVar->m_pProcessQ;
	 Q_NODE  *  pQNode;
	 MIS_MSGU  *  pMsg;
	 IM_CONTENTU  *  pContent;

#ifdef  __DEBUG__
		printQ_mis(  &m_processQ,  FALSE  );
#endif

	//
	unsigned  short  usCnt_tasks  =  0;
	BOOL  bModified  =  FALSE;

#if  0
	//
	for  (  pQNode  =  m_processQ.front.pNext;  pQNode;  pQNode  =  pQNode->pNext  )  {
		pMsg  =  (  MIS_MSGU  *  )pQNode->qElemMemory.m_pBuf;
		if  (  pMsg->uiType  !=  CONST_misMsgType_task  )  continue;


		//
		pContent  =  (  IM_CONTENTU  *  )pMsg->task.data.buf;
		if  (  pContent->uiType  !=  CONST_imCommType_transferAvInfo  )  continue;
		//
		if  (  pContent->transferAvInfo.tmp_usSubtype  !=  CONST_transferAvInfo_subtype_task  )  {
			#ifdef  __DEBUG__
					MACRO_qyAssert(  0,  _T(  "transferAvInfo.subtype err: not transferAvTask"  )  );
			#endif
			continue;
		}

		TRANSFER_AV_task  *  pTransferAvTask  =  (  TRANSFER_AV_task  *  )pContent;
		//
		if  (  !bTaskAlive(  pMsg->task.iStatus  )  
			&&  !pTransferAvTask->myTask.canceledTask_status.bWaitingTo_beRe_accepted  )  			
		{
			continue;
		}

		//
		switch  (  pContent->transferAvInfo.uiTaskType  )  {
				case  CONST_imTaskType_shareScreen:
					  break;
				case  CONST_imTaskType_shareMediaFile:
					  //
					  break;
				default:
						break;
		}
		//
		TASK_list_mem  tlm  =  {0};
		tlm.iTaskId  =  pMsg->task.iTaskId;
		tlm.uiTaskType  =  pMsg->task.uiTaskType;
		tlm.idInfo_sender.ui64Id  =  pMsg->task.idInfo_taskSender.ui64Id;
		tlm.iStatus  =  pMsg->task.iStatus;
		tlm.bWaitingTo_beRe_accepted  =  pTransferAvTask->myTask.canceledTask_status.bWaitingTo_beRe_accepted;
		//
		if  (  memcpy(  &taskList.mems[usCnt_tasks],  &tlm,  sizeof(  tlm  )  )  )  {
			bModified  =  TRUE;
			taskList.mems[usCnt_tasks]  =  tlm;
		}
		usCnt_tasks  ++  ;
		if  (  usCnt_tasks  ==  mycountof(  taskList.mems  )  )  {
			break;
		}

	}
	//
	if  (  taskList.usCnt  !=  usCnt_tasks  )  {
		bModified  =  TRUE;
		//
		taskList.usCnt  =  usCnt_tasks;
	}
#endif


	 //
	 iErr  =  0;

errLabel:

	 //
	 if  (  !iErr  )  {
		 if  (  pbModified  )  {
			 *pbModified  =  bModified;
		 }
	 }

	 return  iErr;

  }













 




 
 


 

  __declspec(  dllexport  )  int  d3dWall_setBg(  HWND  hWall_d3d  )
 {
	 int	iErr	=	-1;
	 TCHAR	tBuf[128];
	 BOOL	bShared  =  FALSE;
	int  iIndex_sharedObj;
	int  iIndex_sharedObjUsr;
	QY_SHARED_OBJ	*  pSharedObj  =  NULL;
	SHARED_OBJ_USR	*	pSharedObjUsr	=	NULL;

#if  0
	 	 
	 QY_MC	*	pQyMc  =  QY_GET_GBUF(  );	
	 GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	 if  (  !pFuncs  )  return  -1;
	 

	 CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;	
	 DLG_TALK_var  *  pMgrVar  =  NULL;
	 CQySyncCnt  syncCnt_talkerDataCfg;
	 
	 int  iGrpType  =  CONST_wmGrpType_gZone;

	 WALLMem_common  *  pWallMem  =  (  WALLMem_common  * )dyn_getCurWmVar(  pGBuf,  iGrpType  );	
	 if  (  !pWallMem  )  goto  errLabel;
	 				
	 if  (  pWallMem->head.uiType  !=  CONST_wallMemType_talker  )  {
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "d3dWall_setBg failed: not talker"  )  );
		 #endif
		 myMessageBox(  hWall_d3d,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_viewDlgTalk_note  ),  _T(  "www.qycx.com"  ),  MB_OK  );
		 goto  errLabel;	
	 }
	 WALLMemData_talker  *  pWallTalker  =  (  WALLMemData_talker  *  )dyn_getD3dTalkerData(  pWallMem  );

	 //
	 D3D_talkerData_cfg  *  pTalkerDataCfg  =  get_D3D_talkerData_cfg(  pProcInfo,  pWallTalker->iIndex_talkerInfo,  &syncCnt_talkerDataCfg  );
	  if  (  !pTalkerDataCfg  )  goto  errLabel;

	
#ifdef  __DEBUG__
		traceLog(  _T(  "d3dWall_setBg called"  )  );
#endif

	TCHAR	bkFile[MAX_PATH]  =  _T(  ""  );

	{
		LPCTSTR							lpszDefExt  =	TEXT("*\0");		
		LPCTSTR							lpszFilter	=	CONST_FILE_FILTER_TEXT;
		LPCTSTR							title		=	TEXT("Open Media File...\0");
		CQyString							pathCStr;
		DWORD								dwFlags     =	OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;
		
		if  (  qyBrowseForFile(  hWall_d3d,  TRUE,  lpszDefExt,  dwFlags,  CONST_FILE_FILTER_TEXT,  title,  NULL,  pathCStr  )  )  goto  errLabel;
		safeTcsnCpy(  pathCStr,  bkFile,  mycountof(  bkFile  )  );
	}

	//
	if  (  pWallTalker->bg.bShared  )  {
		pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pWallTalker->bg.iIndex_sharedObj  );
		if  (  !pSharedObj  )  goto  errLabel;
		askSharedObjToStop(  pProcInfo,  pSharedObj,  pQyMc->gui.hMainWnd,  _T(  "d3dWall_setBg. shared"  )  );
		//
		memset(  &pWallTalker->bg,  0,  sizeof(  pWallTalker->bg  )  );
		//
		memset(  &pTalkerDataCfg->bgImage,  0,  sizeof(  pTalkerDataCfg->bgImage  )  );
		pTalkerDataCfg->dwModifiedTickCnt_bgImage  =  GetTickCount(  );
	}
	
	
	//
	if  (  pFuncs->pf_doCmd_startShareMediaFile(  hWall_d3d,  CONST_qyWndContentType_consoleWall,  0,  bkFile,  &iIndex_sharedObj,  &iIndex_sharedObjUsr  )  )  goto  errLabel;
	bShared  =  TRUE;

	//
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  iIndex_sharedObjUsr  );
	if  (  !pSharedObjUsr  )  goto  errLabel;
	CAP_procInfo_mediaFileBmp  *  pCapBmp  =  (  CAP_procInfo_mediaFileBmp  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
	if  (  !pCapBmp  )  goto  errLabel;
	
	if  (  pCapBmp->vh_org.bih.biBitCount  !=  24  )  goto  errLabel;
	if  (  pCapBmp->vh_org.bih.biCompression  !=  BI_RGB  )  goto  errLabel;
	

	//
	CAP_IMAGE	bgImage;
	memset(  &bgImage,  0,  sizeof(  bgImage  )  );
	bgImage.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_v;
	bgImage.iW_org  =  pCapBmp->vh_org.bih.biWidth;
	bgImage.iH_org  =  pCapBmp->vh_org.bih.biHeight;
	bgImage.playerId.index_player  =  pSharedObj->iIndex_localPlayer;	//  -1;
	memcpy(  &pTalkerDataCfg->bgImage,  &bgImage,  sizeof(  pTalkerDataCfg->bgImage  )  );
	pTalkerDataCfg->dwModifiedTickCnt_bgImage  =  GetTickCount(  );	//  实际上这里还没有填完数据,因为iIndex_player无法确定.不过,更新时间以表示数据已经更改
	//
	pWallTalker->bg.iIndex_sharedObj  =  iIndex_sharedObj;
	pWallTalker->bg.iIndex_sharedObjUsr  =  iIndex_sharedObjUsr;
	safeTcsnCpy(  bkFile,  pWallTalker->bg.fileName,  mycountof(  pWallTalker->bg.fileName  )  );
	pWallTalker->bg.bShared  =  TRUE;
	

	//
	iErr  =  0;
errLabel:

	 if  (  iErr  )  {
		 if  (  bShared  )  {
			 askSharedObjToStop(  pProcInfo,  pSharedObj,  pQyMc->gui.hMainWnd,  _T(  "d3dWall_setBg leaves"  )  );
		 }
	 }

	 #endif

	 return  iErr;
  }


  //  2015/11/30
#if  10
   __declspec(  dllexport  )  int  d3dWall_openQvw(  HWND  hWall_d3d  )
 {
	 int	iErr	=	-1;
	 TCHAR	tBuf[128];

	 	 
	 QY_MC	*	pQyMc  =  QY_GET_GBUF(  );	
	 GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return  -1;


	
#ifdef  __DEBUG__
		traceLog(  _T(  "d3dWall_setBg called"  )  );
#endif


	CQyString  csPath;

	qyBrowseForFile(  hWall_d3d,  TRUE,  _T(  "qvw\0"  ),  OFN_FILEMUSTEXIST,  _T(  "QY V-Wall Module(&.qvw)\0*.qvw\0\0"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectFilenameFormat  ),  NULL,  pQyMc,  csPath  );
	if  (  !csPath.GetLength(  )  )  goto  errLabel;

	int  index  =  -1;
	//
	if  (  dyn_addQisWallCfg(  pQyMc->pQisWallsCfg,  CONST_wallType_confWall,  csPath.GetBuffer(  0  ),  &index  )  )  goto  errLabel;
	//
	if  (  dyn_setCurQisWallCfg(  index,  pQyMc->pQisWallsCfg  )  )  goto  errLabel;
		
	//
	iErr  =  0;
errLabel:

	 if  (  iErr  )  {
	 }

	 return  iErr;
  }
#endif



 

 

 