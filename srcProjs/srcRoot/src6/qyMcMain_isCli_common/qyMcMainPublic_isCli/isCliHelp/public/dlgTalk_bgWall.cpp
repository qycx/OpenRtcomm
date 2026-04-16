
#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	<time.h>
#include	<stddef.h>
#include	<ShellAPI.h>

#include	"qymcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"

#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"


#include	"tmpCeLib.h"
#include	"qyWnd.h"

#include	"qyRtcCommProc.h"
#ifndef  __WINCE__
#include	"dlgVideosProc.h"
#endif
#include	<assert.h>
#include	"qmcDxSurfacePublic.h"
#ifndef  __WINCE__
#include	"qmcConferenceWall.h"
#include	"isCliHelpPublic.h"
#endif
#include	"qmcCmdProc.h"

#include	"policyAvParams.h"

#include	"dlgTalkProc.h"
#include	"qmcSharePublic.h"

#include	"DlgWalls.h"

#include	"gpsCommProc.h"
#include	"qmcGpsProc.h"


#include	"qmcVWall.h"
#include	"dlgDesktopsMonProc.h"

#include	"sp.h"
#include	"myDb.h"
#include	"isCliHelpPublic.h"

#include	"imgProcessPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"dlgMsgToolProc.h"
#include	"qmcVideoCapture_rtsp.h"
#include	"qmcDynBmp.h"

#include	"qyCusResTemp.h"
#include	"qmcTaskInfo.h"
#include	"syncMtCnt.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliD3dPublic.h"





//
__declspec(  dllexport  )  int  procBgWallMem(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  CONF_mem  *  pConfMem,  myZONE  *  pZone  )
{
	int  iErr  =  -1;
	int  i;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	QY_DMITEM	*	pTable				=					getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
	DWORD	dwTickCnt_now  =  GetTickCount(  );

	if  (  !pDLG_TALK_var  )  return  -1;
	DLG_TALK_var  *  pm_var  =  (  DLG_TALK_var  *  )pDLG_TALK_var;
	DLG_TALK_var  &  m_var  =  *pm_var;

	//
	//if  (  !pQMC_taskData_conf  )  return  -1;
	//QMC_taskData_conf  *  pTaskData1  =  (  QMC_taskData_conf  *  )pQMC_taskData_conf;

	//
	//
	CAP_IMAGES  &  images  =  pZone->images;

				
	
	//  is active
	for  (  i  =  0;  i  <  mycountof(  images.mems  );  i  ++  )  {	 
		 CAP_IMAGE	*	pImg	=  &images.mems[i];
	
		 BOOL  bActive  =  FALSE;
	
		 if  (  dwTickCnt_now  -  pImg->dwTickCnt_lastDrawing  <  15  *  1000  )   { 		
			 if  (  pImg->iTaskId  &&  pImg->iTaskId  ==  pConfMem->view.mem.talkerDynBmp.taskInfo.iTaskId  )  {
				 bActive  =  TRUE;
			 }
			 if  (  pConfMem->idInfo.ui64Id  ==  pm_var->pMisCnt->idInfo.ui64Id  )  {
				 bActive  =  TRUE;
			 }
			 //
			 if  (  bActive  )  {
				 #ifdef  __DEBUG__
					     //traceLog(  _T(  "procConfWallMem: index_toDisplay %d active"  ),  index_toDisplay  );
				 #endif
				 //			
				 iErr  =  0;  goto  errLabel;		
			 }	

			 //
			 if  (  !bActive  )  {
				 if  (  pImg->iTaskId  )  {
					//int  idc  =  m_var.av.idc_bgWall;
					//
					//dlgTalk_freeCapImageBySth_bgWall_mgr(  hDlgTalk,  pImg->iTaskId,  NULL  );
					int  lParam  =  pImg->iTaskId;
					PostMessage(  hDlgTalk,  CONST_qyWm_postComm,  CONST_qyWmParam_freeCapImageBySth_bgWall,  lParam  );
				}
			}

		 }
	}


	//
	if  (  !pConfMem->idInfo.ui64Id  )  {
		MACRO_qyAssert(  0,  _T(  "Error: wallMem.idInfo is 0"  )  );
		goto  errLabel;
	}
	if  (  pm_var->pMisCnt->idInfo.ui64Id  ==  pConfMem->idInfo.ui64Id  )  {
#ifdef  __DEBUG__
		traceLog(  _T(  "Note: skip me"  )  );
#endif
		iErr  =  0;  goto  errLabel;
	}
	
	{
		//if  (  dwTickCnt_now  -  pWallMem->dynBmps.m

			TCHAR  tHint[128]  =  _T(  ""  );
			
			unsigned  int  uiObjType  =  CONST_objType_smallStream;
			unsigned  short	usIndex_obj  =  0;
			
			_sntprintf(  tHint,  mycountof(  tHint  ),  _T(  "try to retrieve: %I64u, %s, %d."  ),  pConfMem->idInfo.ui64Id,  qyGetDesByType1(  pTable,  uiObjType  ),  usIndex_obj  );
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Talker%I64u: %s"  ),  pm_var->addr.idInfo.ui64Id,  tHint  );
#ifdef  __DEBUG__
			traceLog(  _T(  "%s"  ),  tHint  );
#endif
			//
			unsigned  int  uiTranNo  =  0;
			if  (  sndRetrieveDynBmpsReqToMsgr_qmc(  pm_var->pMisCnt,  FALSE,  uiObjType,  FALSE,  &pm_var->addr.idInfo,  false,  &pConfMem->idInfo,  &uiTranNo  )  )  goto  errLabel;	
			pConfMem->dynBmps.uiTranNo_retrieve  = uiTranNo;

			iErr  =  0;  goto  errLabel;

	}


	iErr  =  0;
errLabel:
	
	return  iErr;
}


 //  2014/10/07
__declspec(  dllexport  )  int  confStarter_stopConfWall(  HWND  hDlgTalk,  DLG_TALK_var  *  pm_var  )
 {
	 int		iErr	=	-1;

#ifdef  __DEBUG__
		CCtxQmc  *  pProcInfo  =  QY_GET_procInfo_isCli();
		if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
			traceLog(_T("Not finished: confStarter_stopConfWall"));
		}
#endif

	 return  iErr;
 }


 //  2014/10/10  0
 int  drawWallMemTxt(  HWND  hDlgTalk,  DLG_TALK_var  *  pm_var,  QMC_taskData_conf  *  pTaskData,  HDC  hDc  )
{
	int		iErr	=	-1;
	DLG_TALK_var  &  m_var  =  *pm_var;

	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
 
	if  (  !pTaskData->bInited  )  return  -1;



	 //
#define		CONST_fontColor_bgWallMem			RGB(  0,  0,  64  )
#define		CONST_faceName_bgWallMem				"Arial"

		//  2014/10/10
		//CAP_IMAGES  &  images  =  m_var.av.bgWallImages;
	int  i;

		for  (  i  =  0;  i  <  pTaskData->cur_toDisplay.usCnt;  i  ++  )  {
			 //if  (  pTaskData->cur_toDisplay.usStartMemIndex  +  i  >=  pTaskData->usCnt_pMems  )  break;
			 //CONF_mem  *  pConfWallMem  =  &pTaskData->pMems[pTaskData->cur_toDisplay.usStartMemIndex  +  i];	
			 if  (  i  >=  pTaskData->usCnt_pMems  )  break;
			 CONF_mem  *  pConfWallMem  =  &pTaskData->pMems[i];  //  2017/12/29
			 
			 //
			 int  index_toDisplay  =  i;
			 //if  (  index_toDisplay  <  0  ||  index_toDisplay  >=  mycountof(  images.mems  )  )  goto  errLabel;
			 //CAP_RECT  *  pCapRect  =  &images.locations[index_toDisplay].rect;
			 //CAP_IMAGE	*	pImg	=  &images.mems[index_toDisplay];
			 if  (  index_toDisplay  <  0  ||  index_toDisplay  >=  mycountof(  m_var.av.bgWall.mems  )  )  goto  errLabel;
			 myZONE  *  pZone  =  &m_var.av.bgWall.mems[index_toDisplay];


			 int  iX  =  0;
			 int  iY  =  0;
			 int  iW  =  0;
			 int  iH  =  0;
			 //
#if  0
			 iX  =  pCapRect->iX;
			 iY  =  pCapRect->iY;
			 iW  =  pCapRect->iW;
			 iH  =  pCapRect->iH;
#endif
			 //
			 iX  =  pZone->iX;
			 iY  =  pZone->iY;
			 iW  =  pZone->iW;
			 iH  =  pZone->iH;
			 //
			 TCHAR  shortName[32]  =  _T(  ""  );
			 getTalkerDesc(  pConfWallMem->idInfo,  NULL,  0,  shortName,  mycountof(  shortName  )  ); 

			 //
			 myDrawTxt(  shortName,  90,  _T(  CONST_faceName_bgWallMem  ),  CONST_fontColor_bgWallMem,  iX,  iY,  iW,  iH,  GetDlgItem(  hDlgTalk,  m_var.av.idc_bgWall_conf  ),  hDc  );  		 
			 //TextOut(  *phDc,  iX,  iY,  shortName,  lstrlen(  shortName  )  );  
		}

		iErr  =  0;

errLabel:
		return  iErr;
 }


__declspec(  dllexport  )   int  dlgTalk_drawItem_bgWall(   HWND  hCurTalk,  void  *  pDLG_TALK_var,  HDC  hDc  )
{
	int		iErr	=	-1;
	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	CQySyncCnt			syncCnt;
	PARAM_task_info		param;

	DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var  *  )pDLG_TALK_var;

	COLORREF  color_bg  =  CONST_bkColor_meDesc;

	//brushDc(  color_bg,  hDc,  0,  0,  pCurVar->guiData.bgWallCapRect.iW,  pCurVar->guiData.bgWallCapRect.iH  );
	brushDc(  color_bg,  hDc,  0,  0,  pCurVar->av.bgWall.iW,  pCurVar->av.bgWall.iH  );

	//
	DLG_TALK_var	*	pMgrVar		=	NULL;	
	if  (  isTalkerShadowMgr(  pCurVar->addr  )  )  pMgrVar  =  pCurVar;
	else  {								    
		  TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pCurVar->pShadowInfo;			
		  if  (  !pShadow  )  goto  errLabel;
		  pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pShadow->hMgr  );
		  if  (  !pMgrVar  )  goto  errLabel;							  
	}


	//
	if  (  syncToGetTaskInfo(  pMgrVar,  syncCnt,  param  )  )  goto  errLabel;

	QMC_taskData_conf  *  pTaskData  =  param.pTaskData;
	if  (  !pTaskData->bInited  )  goto  errLabel;
	
	drawWallMemTxt(  hCurTalk,  pCurVar,  pTaskData,  hDc  );

	iErr  =  0;
errLabel:

	return  iErr;
}

 //
 __declspec(  dllexport  )  int  dlgTalk_getBgWallMemInfo(  HWND  hCurTalk,  void  *  pDLG_TALK_var,  int  index_rect,  QY_MESSENGER_ID  *  pIdInfo_o  )
 {
	int		iErr	=	-1;
	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	CQySyncCnt			syncCnt;
	PARAM_task_info		param;

	if  (  !pIdInfo_o  )  return  -1;
	DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var  *  )pDLG_TALK_var;

	
	//
	DLG_TALK_var	*	pMgrVar		=	NULL;	
	if  (  isTalkerShadowMgr(  pCurVar->addr  )  )  pMgrVar  =  pCurVar;
	else  {								    
		  TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pCurVar->pShadowInfo;			
		  if  (  !pShadow  )  goto  errLabel;
		  pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pShadow->hMgr  );
		  if  (  !pMgrVar  )  goto  errLabel;							  
	}


	//
	if  (  syncToGetTaskInfo(  pMgrVar,  syncCnt,  param  )  )  goto  errLabel;

	QMC_taskData_conf  *  pTaskData  =  param.pTaskData;
	if  (  !pTaskData->bInited  )  goto  errLabel;
	
	//
	if  (  index_rect  <  0  )  goto  errLabel;
	if  (  pTaskData->cur_toDisplay.usStartMemIndex  +  index_rect  >=  pTaskData->usCnt_pMems  )  goto  errLabel;
	CONF_mem  *  pConfWallMem  =  &pTaskData->pMems[pTaskData->cur_toDisplay.usStartMemIndex  +  index_rect];	

	//
	pIdInfo_o->ui64Id  =  pConfWallMem->idInfo.ui64Id;

	iErr  =  0;
errLabel:
	return  iErr;
 }




//BOOL  confStarter_bTaskInConfWall(  HWND  hDlgTalk,  void  *  pDLG_talk_var,  int  iTaskId  )
__declspec(  dllexport  )  BOOL  confStarter_bTaskInBgWall(  HWND  hDlgTalk,  void  *  pDLG_talk_var,  int  iTaskId,  QIS_res_obj  *  pDynBmp_o,  unsigned  short  *  pusIndex_active  )
{
	BOOL				bRet			=  FALSE;

	DLG_TALK_var  &		m_var			=  *(  DLG_TALK_var  *  )pDLG_talk_var;

	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	CQySyncCnt			syncCnt;
	PARAM_task_info		param;

	unsigned  short		usIndex_active	=	0;
	int					tmpIndex		=	0;
	
	if  (  !iTaskId  )  return  FALSE;

	if  (  syncToGetTaskInfo(  &m_var,  syncCnt,  param  )  )  goto  errLabel;

	QMC_taskData_conf  *  pTaskData  =  param.pTaskData;
	if  (  !pTaskData->bInited  )  goto  errLabel;


	CONF_mem  *  pConfWallMem  =  NULL;
	int  i;
	for  (  i  =  0;  i  <  pTaskData->cur_toDisplay.usCnt;  i  ++  )  {	
		 tmpIndex  =  i;	//  pTaskData->cur_toDisplay.usStartMemIndex  +  i;
		 if  (  tmpIndex  >=  pTaskData->usCnt_pMems  )  goto  errLabel;
		 pConfWallMem  =  &pTaskData->pMems[tmpIndex];

		 if  (  pConfWallMem->view.mem.talkerDynBmp.taskInfo.iTaskId  ==  iTaskId  )  {
			break;
		}
	}
	if  (  i  ==  pTaskData->cur_toDisplay.usCnt  )  goto  errLabel;

	//
	if  (  pDynBmp_o  )  {
		memcpy(  pDynBmp_o,  &pConfWallMem->dynBmps.mem,  sizeof(  pDynBmp_o[0]  )  );
	}


	//
	usIndex_active  =  i;
	
	//
	bRet  =  TRUE;

errLabel:

	if  (  bRet  )  {
		if  (  pusIndex_active  )  *pusIndex_active  =  usIndex_active;
	}

	return  bRet;


}


//  2014/11/29
__declspec(  dllexport  )  BOOL  confStarter_bMeOnBgWall(  HWND  hDlgTalk,  void  *  pDLG_talk_var,  QIS_res_obj  *  pDynBmp_o,  unsigned  short  *  pusIndex_active  )
{
	BOOL				bRet			=  FALSE;

	DLG_TALK_var  &		m_var			=  *(  DLG_TALK_var  *  )pDLG_talk_var;

	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	CQySyncCnt			syncCnt;
	PARAM_task_info		param;

	unsigned  short		usIndex_active	=	0;
	int					tmpIndex		=	0;
	
	//if  (  !iTaskId  )  return  FALSE;

	if  (  syncToGetTaskInfo(  &m_var,  syncCnt,  param  )  )  goto  errLabel;

	QMC_taskData_conf  *  pTaskData  =  param.pTaskData;
	if  (  !pTaskData->bInited  )  goto  errLabel;


	CONF_mem  *  pConfWallMem  =  NULL;
	int  i;
	for  (  i  =  0;  i  <  pTaskData->cur_toDisplay.usCnt;  i  ++  )  {	
		 tmpIndex  =  i;	//  pTaskData->cur_toDisplay.usStartMemIndex  +  i;
		 if  (  tmpIndex  >=  pTaskData->usCnt_pMems  )  goto  errLabel;
		 pConfWallMem  =  &pTaskData->pMems[tmpIndex];

#if  0
		 if  (  pConfWallMem->view.mem.talkerDynBmp.taskInfo.iTaskId  ==  iTaskId  )  {
			break;
		}
#endif
		 if  (  pConfWallMem->idInfo.ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  )  {
			 break;
		 }

	}
	if  (  i  ==  pTaskData->cur_toDisplay.usCnt  )  goto  errLabel;

	//
	if  (  pDynBmp_o  )  {
		memcpy(  pDynBmp_o,  &pConfWallMem->dynBmps.mem,  sizeof(  pDynBmp_o[0]  )  );
	}


	//
	usIndex_active  =  i;
	
	//
	bRet  =  TRUE;

errLabel:

	if  (  bRet  )  {
		if  (  pusIndex_active  )  *pusIndex_active  =  usIndex_active;
	}

	return  bRet;


}



//  2014/09/26
__declspec(  dllexport  )  int  confMem_sndRetrieveDynBmpsRespToMsgr(  HWND  hDlgTalk,  void  *  pDLG_talk_var,  MIS_MSGU  *  pMsg  )
{
	int		iErr	=	-1;
	DLG_TALK_var		  &  m_var  =  *(  DLG_talk_var  *  )pDLG_talk_var;
	
	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;
	if  (  pMsg->uiType  !=  CONST_misMsgType_input  )  return  -1;

	QY_MESSENGER_ID  *  pIdInfo_dst  =  &pMsg->input.data.route.idInfo_from;

	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	RETRIEVE_DYN_BMPS		resp;
	MACRO_prepareForTran(  );
	int						len;
	int						i,  j;

	QY_DMITEM	*	pTable				=					getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );


	if  (  !bMeOnline(  (  QY_MC  *  )pProcInfo->pQyMc  )  )  return  -1;


	//
	IM_CONTENTU			*	pContent	=	M_getMsgContent(  pMsg->input.ucFlg,  &pMsg->input.data  );									 

	//
	if  (  isUcFlgResp(  pMsg->input.ucFlg  )  )  return  -1;
	if  (  pContent->uiType  !=  CONST_imCommType_retrieveDynBmps  )  return  -1;
	if  (  pContent->retrieveDynBmps.u.req.uiObjType  !=  CONST_objType_smallStream  )  return  -1;

	
	//
	if  (  !m_var.av.taskInfo.bTaskExists  )  return  -1;
	if  (  !m_var.av.taskInfo.ucbVideoConference  )  return  -1;


	//
	memset(  &resp,  0,  sizeof(  resp  )  );
	resp.uiType  =  CONST_imCommType_retrieveDynBmps;
	resp.ucbResp  =  TRUE;
	
	//
	unsigned  int  uiObjType  =  CONST_objType_smallStream;
			  
	//	
	if  (  resp.usCnt  >=  mycountof(  resp.mems  )  )  goto  errLabel;		
	//
	resp.mems[resp.usCnt].qisResObj.resObj.uiObjType  =  uiObjType;		
	resp.mems[resp.usCnt].qisResObj.resObj.usIndex_obj  =  2;
	resp.usCnt  ++  ;	

	//	
	if  (  !resp.usCnt  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "retrieveOne failed. no sharedObj"  )  );
			#endif
			//
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "retrieveOne failed, no %s shared"  ),  qyGetDesByType1(  pTable,  uiObjType  )  );		
			goto  errLabel;		
	}

	//
	resp.conf.idInfo_imGrp_related.ui64Id  =  pContent->retrieveDynBmps.conf.idInfo_imGrp_related.ui64Id;

		#ifdef  __DEBUG__
				int  ii;
				ii  =  1;
		#endif
		//
		

	//
	unsigned  char  ucFlg  =  CONST_commFlg_resp;
	unsigned  short  usCode  =  CONST_qyRc_ok;
	tStartTran  =  pMsg->input.tStartTime;
	uiTranNo  =  pMsg->input.uiTranNo;
	//
	len  =  offsetof(  REFRESH_DYN_BMPS,  mems  )  +  resp.usCnt  *  sizeof(  resp.mems[0]  );
	//
	postMsg2Mgr_mc(  m_var.pMisCnt,  NULL,  CONST_misMsgType_task,  ucFlg,   usCode,  tStartTran,  uiTranNo,  0,  (  char  *  )&resp,  len,  NULL,  pIdInfo_dst,  0,  NULL,  0  ); 

	//  2014/06/04
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_sndRetrieveDynBmpsRespToMsgr: to %I64u, cnt %d"  ),  pIdInfo_dst->ui64Id,  (  int  )resp.usCnt  );		


	iErr  =  0;
errLabel:
	

	return  iErr;
}



//  2014/09/26
__declspec(  dllexport  )  int  confStarter_procRetrieveDynBmpsResp(  HWND  hDlgTalk,  void  *  pDLG_talk_var,  MIS_MSGU  *  pMsg  )
{

	int		iErr	=	-1;
	DLG_TALK_var		  &  m_var  =  *(  DLG_talk_var  *  )pDLG_talk_var;
	
	if  (  pMsg->uiType  !=  CONST_misMsgType_input  )  return  -1;
	//
	IM_CONTENTU			*	pContent	=	M_getMsgContent(  pMsg->input.ucFlg,  &pMsg->input.data  );									 

	
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	
	QY_MC				*	pQyMc		=	QY_GET_GBUF(  );
	QY_DMITEM			*	pTable		=	getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
	CQySyncCnt				syncCnt;
	PARAM_task_info			param;
	
#ifdef  __DEBUG__
		traceLog(  _T(  "dlgTalk_procRetrieveDynBmpsRespToMsgr called"  )  );
#endif

	//
	if  (  syncToGetTaskInfo(  &m_var,  syncCnt,  param  )  )  goto  errLabel;
	QMC_taskData_conf  *  pTaskData  =  param.pTaskData;
	if  (  !pTaskData->bInited  )  goto  errLabel;

	//
	CONF_mem  *  pWallMem  =  NULL;
	int  i;
	for  (  i  =  0;  i  <  pTaskData->cur_toDisplay.usCnt;  i  ++  )  {
		 //if  (  pTaskData->cur_toDisplay.usStartMemIndex  +  i  >=  pTaskData->usCnt_pMems  )  
		 if  (  i  >=  pTaskData->usCnt_pMems  )  
		 {
			 #ifdef  __DEBUG__
					 MACRO_qyAssert(  0,  _T(  "dlgTalk_procRetrieveDynBmpsRespToMsgr: i err"  )  );
			 #endif
			 goto  errLabel;
		 }
		 //
		 pWallMem  =  &pTaskData->pMems[i];
		 //
		 if  (  pWallMem->idInfo.ui64Id  !=  pMsg->input.data.route.idInfo_from.ui64Id  )  continue;
		 if  (  pWallMem->dynBmps.uiTranNo_retrieve  !=  pMsg->input.uiTranNo  )  continue;

		 break;
	}
	if  (  i  ==  pTaskData->cur_toDisplay.usCnt  )  goto  errLabel;

	#ifdef  __DEBUG__
				 traceLog(  _T(  "dlgTalk_procRetrieveDynBmpsRespToMsgr: resp matched"  )  );	
	#endif

	//
	if  (  !pContent->retrieveDynBmps.usCnt  )  goto  errLabel;	
	if  (  pContent->retrieveDynBmps.mems[0].qisResObj.idInfo.ui64Id  &&  pContent->retrieveDynBmps.mems[0].qisResObj.idInfo.ui64Id  !=  pWallMem->idInfo.ui64Id  )  goto  errLabel;
	//
	memcpy(  &pWallMem->dynBmps.mem,  &pContent->retrieveDynBmps.mems[0],  sizeof(  pWallMem->dynBmps.mem  )  );
	pWallMem->dynBmps.mem.idInfo.ui64Id  =  pWallMem->idInfo.ui64Id;

	#ifdef  __DEBUG__
	traceLog(  _T(  "dlgTalk_procRetrieveDynBmpsRespToMsgr: wallMem: %I64u, uiObjType %s, usIndex_obj %d"  ),  pWallMem->idInfo.ui64Id,  qyGetDesByType1(  pTable,  pWallMem->dynBmps.mem.resObj.uiObjType  ),  (  int  )pWallMem->dynBmps.mem.resObj.usIndex_obj  );	
	#endif


	//		
	DYN_BMP_rule  dynBmpRule;
	memset(  &dynBmpRule,  0,  sizeof(  dynBmpRule  )  );
	dynBmpRule.dynBmp  =  pWallMem->dynBmps.mem;

	BOOL  bNeedProgress  =  FALSE;
	BOOL  bImgRestarted  =  FALSE;

	if  (  confStarter_chkToViewDynBmp(  hDlgTalk,  &m_var,  &dynBmpRule,  &pWallMem->view.mem.talkerDynBmp,  bNeedProgress,  &bImgRestarted  )  )  goto  errLabel;
	
	//
	iErr  =  0;
errLabel:
	return  iErr;

}

//
 //  int  conf_chkToViewDynBmp(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  int  talkerRuleIndex,  BOOL  bNeedProgress,  BOOL  *  pbImgRestarted  ) 
int  confStarter_chkToViewDynBmp(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  DYN_BMP_rule  *  pRuleDynBmp,  TALKER_dynBmp		*	pObjElem,  BOOL  bNeedProgress,  BOOL  *  pbImgRestarted  ) 
{
	int					iErr		=	-1;
	DLG_TALK_var	&	m_var		=	*(  DLG_TALK_var  *  )pDLG_TALK_var;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	int					tmpiRet		=	-1;

	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;
			
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;
		
	//
	CAP_IMAGES		&	images  =  m_var.av.peerZone.images;

	//
	if  (  chkIfDynBmpRuleUnmatched(  hDlgTalk,  &m_var,  pRuleDynBmp,  pObjElem  )  )  goto  errLabel;

	BOOL			bActive  =  FALSE;
	time_t	t;  mytime(  &t  );

	if  (  pObjElem->taskInfo.iTaskId  )  {

		//  2014/09/06
		bActive  =  bActive_talkerDynBmp(  t,  &images,  pObjElem  );

		//
		if  (  bActive  )  {
			//pObjElem->taskInfo.tLastTime_active  =  t;
			iErr  =  0;  goto  errLabel;
		}

	}

	//
	if  (  !bActive  )  {				 
		QY_DMITEM	*	pTable				=					getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

		

		//  
		if  (  !pRuleDynBmp->dynBmp.resObj.usIndex_obj  )  goto  errLabel;
		
		//
		QY_MESSENGER_ID  content_idInfo_logicalPeer;
		content_idInfo_logicalPeer.ui64Id  =  m_var.addr.idInfo.ui64Id;
		//
		sndViewDynBmpReq(  hDlgTalk,  pDLG_TALK_var,  bNeedProgress,  pbImgRestarted,  pObjElem,  &content_idInfo_logicalPeer  );
		
		
		//  sndViewDynBmpReq(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  BOOL  bNeedProgress,  BOOL  *  pbImgRestarted,  TALKER_dynBmp		*	pObjElem  )


	}

	iErr  =  0;
errLabel:

	return  iErr;
	
}


//  2014/09/28
#if  0
__declspec(  dllexport  )  int  iiconfMem_procReq_transferAvInfo(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  MIS_MSGU  *  pMsg  )
{
	int		iErr	=	-1;

	DLG_TALK_var	&	m_var		=	*(  DLG_TALK_var  *  )pDLG_TALK_var;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	int					tmpiRet		=	-1;
	
	CQySyncCnt		syncCnt;
	PARAM_task_info	param;

	if  (  pMsg->uiType  !=  CONST_misMsgType_task  )  return  -1;
	IM_CONTENTU  *  pContent  =  M_getMsgContent(  pMsg->task.ucFlg,  &pMsg->task.data  );

	if  (  pContent->uiType  !=  CONST_imCommType_transferAvInfo  )  return  -1;

	//  这里应该校验下是不是发起人发过来的请求

	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;
	if  (  !m_var.av.taskInfo.bTaskExists  )  return  -1;
	if  (  m_var.av.taskInfo.ucbStarter  )  return  -1;
	
	QY_SHARED_OBJ  *  pSharedObj_master  =  NULL;
	QY_SHARED_OBJ  *  pSharedObj_slave  =  NULL;
	int				iIndex_sharedObj_slave  =  -1;

	if  (  !m_var.av.ucbGot_iIndex_sharedObj_localAv  )  goto  errLabel;
	pSharedObj_master  =  getSharedObjByIndex(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv  );
	if  (  !pSharedObj_master  )  goto  errLabel;
	if  (  pSharedObj_master->bSlave  )  goto  errLabel;
	//
	iIndex_sharedObj_slave  =  pSharedObj_master->master.slaveKey.iIndex_sharedObj;
	pSharedObj_slave  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj_slave  );
	if  (  !pSharedObj_slave  )  goto  errLabel;
	if  (  !pSharedObj_slave->bSlave  )  goto  errLabel;

	//
	unsigned  int  uiObjType  =  pContent->transferAvInfo.viewDynBmp.resObj.uiObjType;
	if  (  uiObjType  !=  CONST_objType_smallStream  )  goto  errLabel;
	unsigned  short  usIndex_obj  =  pContent->transferAvInfo.viewDynBmp.resObj.usIndex_obj;
	if  (  usIndex_obj  !=  CONST_usIndex_avStream_slave  )  goto  errLabel;
	
	//  2014/09/04	
	DYN_BMP_rule	dynBmp;					
	memset(  &dynBmp,  0,  sizeof(  dynBmp  )  );
	dynBmp.dynBmp.resObj.uiObjType  =  uiObjType;
	dynBmp.dynBmp.resObj.usIndex_obj  =  usIndex_obj;	//  pShare->mems[i].usIndex_obj;

	//	
	MSGR_ADDR  addr;
	memset(  &addr,  0,  sizeof(  addr  )  );
	addr.idInfo.ui64Id  =  pMsg->task.data.route.idInfo_from.ui64Id;
	if  (  procSendAvReplyInfo(  m_var.pMisCnt,  hDlgTalk,  &pMsg->task,  TRUE,  iIndex_sharedObj_slave,  &dynBmp,  NULL,  &addr  )  )  goto  errLabel;									 
		


	iErr  =  0;
errLabel:
	return  iErr;
}
#endif


#if  10
__declspec(  dllexport  )  int  confMem_procReq_transferAvInfo(  HWND  hWnd_task,  int  iIndex_sharedObj_localAv,  MIS_MSGU  *  pMsg  )
{
	int		iErr	=	-1;

	//DLG_TALK_var	&	m_var		=	*(  DLG_TALK_var  *  )pDLG_TALK_var;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	//
	int					tmpiRet		=	-1;
	
	CQySyncCnt		syncCnt;
	PARAM_task_info	param;

	if  (  pMsg->uiType  !=  CONST_misMsgType_task  )  return  -1;
	IM_CONTENTU  *  pContent  =  M_getMsgContent(  pMsg->task.ucFlg,  &pMsg->task.data  );

	if  (  pContent->uiType  !=  CONST_imCommType_transferAvInfo  )  return  -1;

	//  这里应该校验下是不是发起人发过来的请求

#if  0
	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  return  -1;
	if  (  !m_var.av.taskInfo.bTaskExists  )  return  -1;
	if  (  m_var.av.taskInfo.ucbStarter  )  return  -1;
#endif

	//
	QY_SHARED_OBJ  *  pSharedObj_master  =  NULL;
	QY_SHARED_OBJ  *  pSharedObj_slave  =  NULL;
	int				iIndex_sharedObj_slave  =  -1;

	//if  (  !m_var.av.ucbGot_iIndex_sharedObj_localAv  )  goto  errLabel;
	pSharedObj_master  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj_localAv  );
	if  (  !pSharedObj_master  )  goto  errLabel;
	//
	if  (  !pSharedObj_master->bUsed  )  goto  errLabel;
	if  (  !bSharedObjActive(  pProcInfo,  iIndex_sharedObj_localAv  )  )  goto  errLabel;
	//
	if  (  pSharedObj_master->bSlave  )  goto  errLabel;
	//
	iIndex_sharedObj_slave  =  pSharedObj_master->master.slaveKey.iIndex_sharedObj;
	pSharedObj_slave  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj_slave  );
	if  (  !pSharedObj_slave  )  goto  errLabel;
	if  (  !pSharedObj_slave->bSlave  )  goto  errLabel;

	//
	SHARED_OBJ_USR  *  pSharedObjUsr  =  getSharedObjUsr(  pSharedObj_slave,  pSharedObj_slave->iIndex_curUsr  );
	if  (  !pSharedObjUsr  )  goto  errLabel;
	int  iTaskId  =  pSharedObjUsr->iTaskId;

	//
	unsigned  int  uiObjType  =  pContent->transferAvInfo.ass.resObj.uiObjType;
	if  (  uiObjType  !=  CONST_objType_smallStream  )  goto  errLabel;
	unsigned  short  usIndex_obj  =  pContent->transferAvInfo.ass.resObj.usIndex_obj;
	if  (  usIndex_obj  !=  CONST_usIndex_avStream_slave  )  goto  errLabel;
	
	//  2014/09/04	
	DYN_BMP_rule	dynBmp;					
	memset(  &dynBmp,  0,  sizeof(  dynBmp  )  );
	dynBmp.dynBmp.resObj.uiObjType  =  uiObjType;
	dynBmp.dynBmp.resObj.usIndex_obj  =  usIndex_obj;	//  pShare->mems[i].usIndex_obj;

	//	
	MSGR_ADDR  addr;
	memset(  &addr,  0,  sizeof(  addr  )  );
	addr.idInfo.ui64Id  =  pMsg->task.data.route.idInfo_from.ui64Id;
	if  (  procSendAvReplyInfo(  pMisCnt,  hWnd_task,  &pMsg->task,  TRUE,  iIndex_sharedObj_slave,  iTaskId,  &dynBmp,  NULL,  &addr  )  )  goto  errLabel;									 
		


	iErr  =  0;
errLabel:
	return  iErr;
}
#endif





