

#include	"stdafx.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainCommon.h"

//  #include	"DlgObjs.h"
//  #include	"DlgTalk_ce.h"
#include	"dlgObjsProc.h"
#include	"qnmResDefs.h"
#include	"dlgTalkProc.h"

#include	"myDb.h"


#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
	#include	<fcntl.h>
	#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#ifndef  __WINCE__
#pragma include_alias( "dxtrans.h", "myqedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__
	//  #include	<Qedit.h>
	#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>
#include	<dsound.h>

#include	"qmcDmoPublic.h"

#include	"qmcVideoCapture_dx.h"

#include	"myfourcc.h"
#include	"mywmcodecconst.h"

#include	"qmcCmdProc.h"
#include	"qyCusResTemp.h"

#include	"funcsForIsCliHelp.h"
#include	"isCliHelpPublic.h"
#include	"qmcDynBmp.h"

#include	"qmcCommFunc_iscli.h"

#include	"isCliD3dPublic.h"
#include	"objtype_tmp.h"


char  *  displayShortTime(  time_t  t,  char  *  timeBuf,  unsigned  int  len  );


#ifdef  __NOTSUPPORT_DB__

 int  tmpHandler_printQmObjQ(  void  *  p0,  void  *  p1,  QM_OBJQ_MEM  *  pMem  )
{
	int							iErr	=	-1;
	//  CDlgObjs				*   pDlg	=  (  CDlgObjs  *  )p0;
	HWND						hDlg	=	(  HWND  )p0;
	DLG_objs_var			*	pVar	=	(  DLG_objs_var  *  )p1;
	if  (  !pVar  )  return  -1;
	DLG_objs_var			&	m_var	=	*pVar;

	QY_MC					*	pQyMc	=	QY_GET_GBUF(  );
	QY_DMITEM				*	pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
	//  char						idStr[32]	=  "";
				  

	QMEM_MESSENGER_CLI		*	pQMemObj;

	pQMemObj  =  (  QMEM_MESSENGER_CLI  *  )pMem->pQMemObj;

	switch  (  m_var.guiData.param.uiType  )  {
			case  CONST_objType_imGrp:
				  if  (  pQMemObj->uiType  !=  CONST_objType_imGrp  )  {
					  iErr  =  0;  goto  errLabel;
				  }
				  break;
			case  CONST_objType_messenger:
				  if  (  pQMemObj->uiType  ==  CONST_objType_imGrp  )  {
					  iErr  =  0;  goto  errLabel;
				  }
				  break;
			default:
				    iErr  =  0;  goto  errLabel;
	}

	//  _snprintf(  idStr, mycountof(  idStr  ),  "%I64u",  pQMemObj->idInfo.ui64Id  );

	HWND	hCtl	=	GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  );
	TCHAR	tBuf[256];
	int		tmpiRet;

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u %s"  ),  pQMemObj->idInfo.ui64Id,  pQMemObj->talkerDesc  );
	tmpiRet  =  SendMessage(  hCtl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\t%d,  %s, idInfo is %I64u, talkerDesc %s"  ),  m_var.usItemCount,  qyGetDesByType1(  pTable,  pQMemObj->uiType  ),  pQMemObj->idInfo.ui64Id,  pQMemObj->talkerDesc  );
	OutputDebugString(  tBuf  );
	OutputDebugString(  _T(  "\n"  )  );


	m_var.usItemCount  ++;

	iErr  =  0;
errLabel:
	return  iErr;
}

 #else  __NOTSUPPORT_DB__

int  tmpHandler_getDynBmps(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int				iErr		=	-1;
	COMMON_PARAM	*  pCommonParam0	=  (  COMMON_PARAM  *  )p0;
	COMMON_PARAM	*  pCommonParam1	=  (  COMMON_PARAM  *  )p1;
	MIS_MSGU  *  pMsg			=  (  MIS_MSGU  *  )p2;

	unsigned  int		uiTranNo		=  0;
	BOOL				bRemove			=	FALSE;

	if  (  !pCommonParam0  )  return  0;
	uiTranNo  =  (  unsigned  int  )pCommonParam0->p1;
	bRemove  =  (  BOOL  )pCommonParam0->p2;

	if  (  pMsg->uiType  !=  CONST_misMsgType_input  )  {
		iErr  =  0;  goto  errLabel;
	}
	if  (  !(  isUcFlgRouteTalkData(  pMsg->input.ucFlg  )  
		//||  isUcFlgTalkData(  pMsg->input.ucFlg  )  
		)  )  {
		iErr  =  0;  goto  errLabel;								
	}								
	if  (  !isUcFlgResp(  pMsg->input.ucFlg  )  )  {
		iErr  =  0;  goto  errLabel;
	}
	if  (  pMsg->input.uiTranNo  !=  uiTranNo  )  {
		iErr  =  0;  goto  errLabel;
	}
	IM_CONTENTU  *  pContent  =  M_getMsgContent(  pMsg->input.ucFlg,  &pMsg->input.data  );
	if  (  pContent->uiType  !=  CONST_imCommType_retrieveDynBmps  )  {
		iErr  =  0;  goto  errLabel;
	}
	if  (  !bRemove  )  {
		QIS_dynBmp_info		*  pDynBmps			=  NULL;
		unsigned  int		maxCnt			=	0;
		unsigned  int	*  puiCnt			=  NULL;
		
		if  (  !pCommonParam1  )  goto  errLabel;
		pDynBmps  =  (  QIS_dynBmp_info  *  )pCommonParam1->p0;
		maxCnt  =  (  unsigned  int  )pCommonParam1->p1;
		puiCnt  =  (  unsigned  int  *  )pCommonParam1->p2;
	

		if  (  !pDynBmps  )  goto  errLabel;
		//
		if  (  *puiCnt  >=  maxCnt  )  {
			iErr  =  1;  goto  errLabel;
		}
		//
		int  n  =min(  maxCnt  -  *puiCnt,  pContent->retrieveDynBmps.usCnt  );
		memcpy(  pDynBmps  +  *puiCnt,  pContent->retrieveDynBmps.mems,  n  *  sizeof(  QIS_dynBmp_info  )  );
		*puiCnt  +=  n;
		}
	else  {
		  iErr  =  1;  goto  errLabel;
	}


	iErr  =  0;
errLabel:
	return  iErr;
}


#ifdef  __isCli__
 int  fillImObjs_selectRemoteVideo(  HWND  hDlg,  void  *  pVarParam  )
 {
	int  iRet  =  -1;
	QY_MC		*pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	MIS_CNT	*	pMisCnt  =  (  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;
	
	unsigned  int	maxCnt	=	32;
	QIS_dynBmp_info	*	pDynBmps  =  NULL;
	int				size;
	unsigned  int	cnt		=	0;
	
	DLG_objs_var  *  pVar  =  (  DLG_objs_var  *  )pVarParam;
	if  (  !IsWindow(  pVar->guiData.param.hCurTalk  )  )  goto  errLabel;		//  2013/06/10
	DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )pVar->guiData.param.pCurVar;	//  getDlgTalkVar(  pVar->guiData.param.hCurTalk  );
	if  (  !pDlgTalkVar  )  goto  errLabel;
	DLG_TALK_var  *	 pMgrVar	  =	 (  DLG_TALK_var  *  )pVar->guiData.param.pMgrVar;	//  pDlgTalkVar;
	if  (  !pMgrVar  )  goto  errLabel;


	//  2014/05/30
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;	
	if  (  !pShadowMgr  )  goto  errLabel;


	//
	size  =  maxCnt  *  sizeof(  QIS_dynBmp_info  );
	pVar->uiSize_pData  =  size;
	pVar->iType_pData  =  CONST_iType_pData_dynBmps;
	pVar->pData  =  (  QIS_dynBmp_info  *  )mymalloc(  size  );
	if  (  !pVar->pData  )  goto  errLabel;
	memset(  pVar->pData,  0,  size  );
	pDynBmps  =  (  QIS_dynBmp_info  *  )pVar->pData;

	//
	//if  (  bSupported_queryRemoteVideo(  )  )  
	{
		//  2014/05/03
		unsigned  int  uiTranNo  =  0;
		if  (  sndRetrieveDynBmpsReqToMsgr_qmc(  pMisCnt,  TRUE,  0,  FALSE,  NULL,  FALSE,  &pMgrVar->addr.idInfo,  &uiTranNo  )  )  goto  errLabel;	
		pShadowMgr->selectRemoteVideo.uiTranNo  =  uiTranNo;	//  2014/09/04
		//
		HWND  hParent  =  pVar->guiData.param.hCurTalk;
		//  2016/08/09
		if  (  IsWindow(  pVar->m_hParent  )  )  hParent  =  pVar->m_hParent;
		//  2015/06/05
		if  (  !pProcInfo->bUse_imObjView_as_guiWnd(  )  )  {
			if  (  bApp_ts_3d(  pQyMc  )  )  {
				GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
				if  (  !pGBuf  )  goto  errLabel;
				if  (  !IsWindow(  pGBuf->hWall_d3d  )  )  goto  errLabel;
				hParent  =  pGBuf->hWall_d3d;
			}
		}
		//
		if  (  showProgress(  &pQyMc->gui.progress,  &pQyMc->cusRes,  hParent,  _T(  "Please waiting"  ),  NULL,  30,  -1,  uiTranNo  )  !=  IDOK  )  {		
			goto  errLabel;					  
		}
	
		COMMON_PARAM	commonParam3_i;
		COMMON_PARAM	commonParam3_o;
		BOOL			bRemove  =  FALSE;

		MACRO_makeCommonParam3(  0,  (  void  *  )uiTranNo,  (  void  *  )bRemove,  commonParam3_i  );
		MACRO_makeCommonParam3(  (  void  *  )pDynBmps,  (  void  *  )maxCnt,  (  void  *  )&cnt,  commonParam3_o  );
		qTraverse(  pMgrVar->m_pProcessQ,  tmpHandler_getDynBmps,  &commonParam3_i,  &commonParam3_o  );
		//
		bRemove  =  TRUE;
		MACRO_makeCommonParam3(  0,  (  void  *  )uiTranNo,  (  void  *  )bRemove,  commonParam3_i  );		
		qRemoveMsg(  pMgrVar->m_pProcessQ,  tmpHandler_getDynBmps,  &commonParam3_i,  NULL  );
	}
	 
	//
	HWND	hCtl	=	GetDlgItem(  hDlg,  pVar->guiData.iIDC_LIST0  );

	int		tmpiRet;

	//if  (  bSupported_queryRemoteVideo(  )  )  
	{
		int  n  =  cnt;
		if  (  n  <  0  )  goto  errLabel;
		pVar->uiSize_pData_items  =  n  *  sizeof(  QY_COLUMNINFO  );
		pVar->pData_items  =  mymalloc(  pVar->uiSize_pData_items  );
		if  (  !pVar->pData_items  )  goto  errLabel;
		memset(  pVar->pData_items,  0,  pVar->uiSize_pData_items  );

		pVar->nItems  =  n;
		QY_COLUMNINFO  *  pColumns  =  (  QY_COLUMNINFO  *  )pVar->pData_items;
		for  (  n  =  0;  ;  n  ++  )  {
			 if  (  n  >=  cnt  )  break;
			 //
			 QY_DMITEM  *  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

			 _sntprintf(  pColumns[n].label,  mycountof(  pColumns[n].label  ),  _T(  "%s %d"  ),  qyGetDesByType1(  pTable,  pDynBmps[n].qisResObj.resObj.uiObjType  ),  (  int  )pDynBmps[n].qisResObj.resObj.usIndex_obj  );
			 if  (  pDynBmps[n].qisResObj.resObj.usHelp_subIndex  )  _sntprintf(  pColumns[n].label,  mycountof(  pColumns[n].label  ),  _T(  "%s.%d"  ),  pColumns[n].label,  (  int  )pDynBmps[n].qisResObj.resObj.usHelp_subIndex  );
			 _sntprintf(  pColumns[n].label,  mycountof(  pColumns[n].label  ),  _T(  "%s %s %s"  ),  pColumns[n].label,  pDynBmps[n].name,  pDynBmps[n].cusName  );
			 //
			 if  (  tmpF_bViewRemoteVideo(  &pShadowMgr->vwRuleCmd_manual,  pDynBmps[n].qisResObj.resObj.uiObjType,  pDynBmps[n].qisResObj.resObj.usIndex_obj,  pDynBmps[n].qisResObj.resObj.usHelp_subIndex  )  )  pColumns[n].lParam  =  TRUE;
			 if  (  pColumns[n].lParam  )  _sntprintf(  pColumns[n].label,  mycountof(  pColumns[n].label  ),  _T(  "%s ( %s )"  ),  pColumns[n].label,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_manuallyStarted  )  );
			 //
			 tmpiRet  =  SendMessage(  hCtl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )pColumns[n].label  );    
	
		}


		}


	 iRet  =  0;
errLabel:

	 return  iRet;
 }


 //  2013/06/24
 int  fillImObjs_selectLayoutType(  HWND  hDlg,  void  *  pVarParam  )
 {
	int  iRet  =  -1;
	QY_MC		*pQyMc		=	QY_GET_GBUF(  );
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	//
	DLG_objs_var  *  pVar  =  (  DLG_objs_var  *  )pVarParam;
	if  (  !IsWindow(  pVar->guiData.param.hCurTalk  )  )  goto  errLabel;		//  2013/06/10
	DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )pVar->guiData.param.pCurVar;	//  getDlgTalkVar(  pVar->guiData.param.hCurTalk  );
	if  (  !pDlgTalkVar  )  goto  errLabel;
	DLG_TALK_var  *	 pMgrVar	  =	 (  DLG_TALK_var  *  )pVar->guiData.param.pMgrVar;	//  pDlgTalkVar;
	if  (  !pMgrVar  )  goto  errLabel;

	 
	QY_DMITEM	*	pTable	=	getResTable(  0,  &pQyMc->cusRes,  CONST_resId_usLayoutTypeTable  );
	QY_DMITEM	*	pItem;
	HWND	hCtl	=	GetDlgItem(  hDlg,  pVar->guiData.iIDC_LIST0  );

	int		tmpiRet;
#if 0

	int		n  =  getnItems(  pTable  );
	if  (  n  <  0  )  goto  errLabel;
	pVar->uiSize_pData_items  =  n  *  sizeof(  QY_COLUMNINFO  );
	pVar->pData_items  =  mymalloc(  pVar->uiSize_pData_items  );
	if  (  !pVar->pData_items  )  goto  errLabel;
	memset(  pVar->pData_items,  0,  pVar->uiSize_pData_items  );

	pVar->nItems  =  n;
	QY_COLUMNINFO  *  pColumns  =  (  QY_COLUMNINFO  *  )pVar->pData_items;
	for  (  n  =  0,  pItem  =  pTable;  pItem->type  !=  -1;  n  ++  ,  pItem  ++  )  {
		if  (  n  >=  pVar->nItems  )  goto  errLabel;
		 pColumns[n].type  =  pItem->type;
		 safeTcsnCpy(  pItem->des,  pColumns[n].label,  mycountof(  pColumns[n].label  )  );
		 //
		 if  (  pItem->type  ==  dlgTalk_get_usLayoutType_local(  pVar->guiData.param.hCurTalk  )  )  pColumns[n].lParam  =  TRUE;
		 if  (  pColumns[n].lParam  )  _sntprintf(  pColumns[n].label,  mycountof(  pColumns[n].label  ),  _T(  "%s ( %s )"  ),  pColumns[n].label,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_current  )  );
		 //
		 tmpiRet  =  SendMessage(  hCtl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )pColumns[n].label  );    

	}
#endif

	//
	do {
		if (!pMgrVar->av.taskInfo.bTaskExists)  break;
		//
		int index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, pMgrVar->av.taskInfo.iTaskId);

		QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
		if (!pTaskInfo)break;
		QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;
		if (!pTaskData)break;
		if (pTaskData->uiType != CONST_taskDataType_conf)break;
		QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskData;
		DLG_TALK_videoConference* pVc = &pTc->videoConference;
		TCHAR  tBuf[256];
		int i;

		//
		for (i = 0; i < pVc->usCntLimit_activeMems_from; i++) {
			DLG_TALK_videoConferenceActiveMemFrom* pActiveMem = &pVc->activeMems_from[i];
			if (!pActiveMem->avStream.idInfo.ui64Id)  continue;
			
			if (pActiveMem->avStream.obj.resObj.uiObjType == CONST_objType_mosaicStream_video)  continue;
			if (pActiveMem->avStream.obj.resObj.uiObjType == CONST_objType_mosaicStream_resource)  continue;

			//
			_sntprintf(tBuf, mycountof(tBuf), _T("%I64u,%d: %s"), pActiveMem->avStream.idInfo.ui64Id, pActiveMem->avStream.obj.tranInfo.video.uiTranNo_openAvDev, pActiveMem->desc);

			//
			tmpiRet = SendMessage(hCtl, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)tBuf);

			//
			continue;
		}

		//
	} while (false);




	//
	 iRet  =  0;
errLabel:

	 return  iRet;
 }


 //
 int  fillImObjs_selectIpc(HWND  hDlg, void* pVarParam)
 {
	 int  iRet = -1;
	 QY_MC* pQyMc = QY_GET_GBUF();
	 CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	 //
	 DLG_objs_var* pVar = (DLG_objs_var*)pVarParam;
	 if (!IsWindow(pVar->guiData.param.hCurTalk))  goto  errLabel;		//  2013/06/10
	 DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)pVar->guiData.param.pCurVar;	//  getDlgTalkVar(  pVar->guiData.param.hCurTalk  );
	 if (!pDlgTalkVar)  goto  errLabel;
	 DLG_TALK_var* pMgrVar = (DLG_TALK_var*)pVar->guiData.param.pMgrVar;	//  pDlgTalkVar;
	 if (!pMgrVar)  goto  errLabel;


	 QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_usLayoutTypeTable);
	 QY_DMITEM* pItem;
	 HWND	hCtl = GetDlgItem(hDlg, pVar->guiData.iIDC_LIST0);

	 int		tmpiRet;

	 //
	 do {
		 if (!pMgrVar->av.taskInfo.bTaskExists)  break;
		 //
		 int index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, pMgrVar->av.taskInfo.iTaskId);

		 QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
		 if (!pTaskInfo)break;
		 QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;
		 if (!pTaskData)break;
		 if (pTaskData->uiType != CONST_taskDataType_conf)break;
		 QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskData;
		 DLG_TALK_videoConference* pVc = &pTc->videoConference;
		 TCHAR  tBuf[256];
		 int i;

		 //
		 NvrInfo  *  pNvrInfo  =  &pProcInfo->m_ipcProc.op.nvrInfo;

		 //
		 if (pNvrInfo->usCnt) {
			 _sntprintf(tBuf, mycountof(tBuf), _T("%d, %S, %s"), -1, "", _T("(所有)"));
			 tmpiRet = SendMessage(hCtl, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)tBuf);
		 }

		 //
		 for (i = 0; i < pNvrInfo->usCnt; i++) {
			 IpcInfo* pMem = &pNvrInfo->mems[i];

			 //
			 _sntprintf(tBuf, mycountof(tBuf), _T("%d, %S, %s"), pMem->iChannel, pMem->ip,  pMem->name);

			 //
			 tmpiRet = SendMessage(hCtl, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)tBuf);

			 //
			 continue;
		 }

		 //
	 } while (false);




	 //
	 iRet = 0;
 errLabel:

	 return  iRet;
 }


 //
 //  2013/06/24
 int  fillImObjs_selOneBig(HWND  hDlg, void* pVarParam)
 {
	 int  iRet = -1;
	 QY_MC* pQyMc = QY_GET_GBUF();
	 CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	 //
	 DLG_objs_var* pVar = (DLG_objs_var*)pVarParam;
	 if (!IsWindow(pVar->guiData.param.hCurTalk))  goto  errLabel;		//  2013/06/10
	 DLG_TALK_var* pDlgTalkVar = (DLG_TALK_var*)pVar->guiData.param.pCurVar;	//  getDlgTalkVar(  pVar->guiData.param.hCurTalk  );
	 if (!pDlgTalkVar)  goto  errLabel;
	 DLG_TALK_var* pMgrVar = (DLG_TALK_var*)pVar->guiData.param.pMgrVar;	//  pDlgTalkVar;
	 if (!pMgrVar)  goto  errLabel;


	 QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_usLayoutTypeTable);
	 QY_DMITEM* pItem;
	 HWND	hCtl = GetDlgItem(hDlg, pVar->guiData.iIDC_LIST0);

	 int		tmpiRet;

	 //
	 do {
		 if (!pMgrVar->av.taskInfo.bTaskExists)  break;
		 //
		 int index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, pMgrVar->av.taskInfo.iTaskId);

		 QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
		 if (!pTaskInfo)break;
		 QMC_taskData_common* pTaskData = pTaskInfo->var.pTaskData;
		 if (!pTaskData)break;
		 if (pTaskData->uiType != CONST_taskDataType_conf)break;
		 QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskData;
		 DLG_TALK_videoConference* pVc = &pTc->videoConference;
		 TCHAR  tBuf[256];
		 int i;

		 //
		 for (i = 0; i < pVc->usCntLimit_activeMems_from; i++) {
			 DLG_TALK_videoConferenceActiveMemFrom* pActiveMem = &pVc->activeMems_from[i];
			 if (!pActiveMem->avStream.idInfo.ui64Id)  continue;

			 if (pActiveMem->avStream.obj.resObj.uiObjType == CONST_objType_mosaicStream_video)  continue;
			 if (pActiveMem->avStream.obj.resObj.uiObjType == CONST_objType_mosaicStream_resource)  continue;

			 //
			 _sntprintf(tBuf, mycountof(tBuf), _T("%I64u,%d: %s"), pActiveMem->avStream.idInfo.ui64Id, pActiveMem->avStream.obj.tranInfo.video.uiTranNo_openAvDev, pActiveMem->desc);

			 //
			 tmpiRet = SendMessage(hCtl, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)tBuf);

			 //
			 continue;
		 }

		 //
	 } while (false);




	 //
	 iRet = 0;
 errLabel:

	 return  iRet;
 }







 //
 int  fillImObjs_selectRemotePtz(  HWND  hDlg,  void  *  pVarParam  )
 {
	int  iRet  =  -1;
	QY_MC		*pQyMc		=	QY_GET_GBUF(  );

	DLG_objs_var  *  pVar  =  (  DLG_objs_var  *  )pVarParam;
	if  (  !IsWindow(  pVar->guiData.param.hCurTalk  )  )  goto  errLabel;		//  2013/06/10
	DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )pVar->guiData.param.pCurVar;	//  getDlgTalkVar(  pVar->guiData.param.hCurTalk  );
	if  (  !pDlgTalkVar  )  goto  errLabel;
	DLG_TALK_var  *	 pMgrVar	  =	 (  DLG_TALK_var  *  )pVar->guiData.param.pMgrVar;	//  pDlgTalkVar;
	if  (  !pMgrVar  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;


	//
	HWND	hCtl	=	GetDlgItem(  hDlg,  pVar->guiData.iIDC_LIST0  );

	int		tmpiRet;
	int  i;

	int		n  =  0;	//  getnItems(  pTable  );
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->talkerDynBmps  );  i  ++  )  {
		 TALKER_dynBmp  *  pMem  =  &pShadowMgr->talkerDynBmps[i];
		 if  (  pMem->taskInfo.iTaskId  
			 &&  pMem->dynBmpRule.dynBmp.resObj.uiObjType  ==  CONST_objType_rtspStream  )
		 {
			 n  ++  ;
		 }
	}
	//
	n  +=  1;  //  old ptz;
	if  (  n  <  0  )  goto  errLabel;


	//
	int  size;
	int  maxCnt  =  n;
	//
	size  =  maxCnt  *  sizeof(  QIS_dynBmp_info  );
	pVar->uiSize_pData  =  size;
	pVar->iType_pData  =  CONST_iType_pData_dynBmps;
	pVar->pData  =  (  QIS_dynBmp_info  *  )mymalloc(  size  );
	if  (  !pVar->pData  )  goto  errLabel;
	memset(  pVar->pData,  0,  size  );
	QIS_dynBmp_info  *  pDynBmps  =  (  QIS_dynBmp_info  *  )pVar->pData;



	//
	pVar->uiSize_pData_items  =  n  *  sizeof(  QY_COLUMNINFO  );
	pVar->pData_items  =  mymalloc(  pVar->uiSize_pData_items  );
	if  (  !pVar->pData_items  )  goto  errLabel;
	memset(  pVar->pData_items,  0,  pVar->uiSize_pData_items  );

	//
	pVar->nItems  =  n;

	//
	QY_COLUMNINFO  *  pColumns  =  (  QY_COLUMNINFO  *  )pVar->pData_items;
	n  =  0;
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->talkerDynBmps  );  i  ++  )  {
		 TALKER_dynBmp  *  pMem  =  &pShadowMgr->talkerDynBmps[i];
		 if  (  !pMem->taskInfo.iTaskId  )  continue;
		 if  (  pMem->dynBmpRule.dynBmp.resObj.uiObjType  !=  CONST_objType_rtspStream  )  continue;

		 //
		 if  (  n  >=  pVar->nItems  )  goto  errLabel;		

		 //
		 pDynBmps[n].qisResObj.resObj  =  pMem->dynBmpRule.dynBmp.resObj;

		 //
		 pColumns[n].type  =  pMem->dynBmpRule.dynBmp.resObj.uiObjType;

		 QY_DMITEM  *  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
		
		 TCHAR  *  pName  =  _T(  ""  );
		 TCHAR  *  cusName  =  _T(  ""  );
		 pName  =  pMem->dynBmpRule.name;
		 cusName  =  pMem->dynBmpRule.cusName;
		 _sntprintf(  pColumns[n].label,  mycountof(  pColumns[n].label  ),  _T(  "%s %d"  ),  qyGetDesByType1(  pTable,  pMem->dynBmpRule.dynBmp.resObj.uiObjType  ),  (  int  )pMem->dynBmpRule.dynBmp.resObj.usIndex_obj  );
		 if  (  pMem->dynBmpRule.dynBmp.resObj.usHelp_subIndex  )  _sntprintf(  pColumns[n].label,  mycountof(  pColumns[n].label  ),  _T(  "%s.%d"  ),  pColumns[n].label,  pMem->dynBmpRule.dynBmp.resObj.usHelp_subIndex  );
		 _sntprintf(  pColumns[n].label,  mycountof(  pColumns[n].label  ),  _T(  "%s %s %s"  ),  pColumns[n].label,  pName,  cusName  );
		 
		 //
		 tmpiRet  =  SendMessage(  hCtl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )pColumns[n].label  );   

		 //
		 n  ++  ;

		 //
		 continue;
	}

	//
	if  (  n  >=  pVar->nItems  )  goto  errLabel;		

	//	
	pColumns[n].type  =  0;
	_sntprintf(  pColumns[n].label,  mycountof(  pColumns[n].label  ),  _T(  "not onvif ptz"  )  );
			 
	//	
	tmpiRet  =  SendMessage(  hCtl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )pColumns[n].label  );   
	
	//	 
	iRet  =  0;

errLabel:
		
	return  iRet;
 }


 //
  int  fillImObjs_selectADev(  HWND  hDlg,  void  *  pVarParam  )
 {
	int  iRet  =  -1;
	QY_MC		*pQyMc		=	QY_GET_GBUF(  );
	DLG_objs_var  *  pVar  =  (  DLG_objs_var  *  )pVarParam;
	

	if  (  !pVar->guiData.param.p0  )  return  -1;
	CAP_STUFF	&	gcap	=	*(  CAP_STUFF  *  )pVar->guiData.param.p0;

	int		tmpiRet;
	HWND	hCtl	=	GetDlgItem(  hDlg,  pVar->guiData.iIDC_LIST0  );

	int		i;
	int		iSel  =  -1;
	for  (  i  =  0;  i  <  min(  mycountof(  gcap.old_audioDevices.mems  ),  gcap.old_audioDevices.iNumADevices  );  i  ++  )  {
		tmpiRet  =  SendMessage(  hCtl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )gcap.old_audioDevices.mems[i].names_audio  );    		
		 if  (  pVar->guiData.param.iMenuId_selectedDev
			 &&  gcap.old_audioDevices.mems[i].iMenuIds_audio  ==  pVar->guiData.param.iMenuId_selectedDev  )
		 {
			 iSel  =  i;
		 }
	}

	//
	if  (  iSel  >=  0  )  {
		tmpiRet  =  SendMessage(  hCtl,  LB_SETCURSEL,  (  WPARAM  )iSel,  (  LPARAM  )0  );    		 		 
	}
	
	//
	iRet  =  0;

errLabel:
	return  iRet;
  }

   #define		CONST_moniker_FriendlyName		_T(  "FriendlyName"  )
   int  fillImObjs_selectVDev(  HWND  hDlg,  void  *  pVarParam  )
 {
	int  iRet  =  -1;
	QY_MC		*pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	
	//
	DLG_objs_var  *  pVar  =  (  DLG_objs_var  *  )pVarParam;
	
	if  (  !pVar->guiData.param.p0  )  return  -1;
	CAP_STUFF	&	gcap	=	*(  CAP_STUFF  *  )pVar->guiData.param.p0;

	int		tmpiRet;
	HWND	hCtl	=	GetDlgItem(  hDlg,  pVar->guiData.iIDC_LIST0  );

	int		i;
	int		iSel  =  -1;
	for  (  i  =  0;  i  <  min(  mycountof(  gcap.rgpmVideoMenu  ),  gcap.iNumVCapDevices  );  i  ++  )  {
		TCHAR	tBuf[256];
		//  getMonikerFriendlyName(  gcap.rgpmVideoMenu[i],  tBuf,  mycountof(  tBuf  )  );
		pFuncs->moniker.pf_getMonikerProp(  gcap.rgpmVideoMenu[i],  CONST_moniker_FriendlyName,  tBuf,  mycountof(  tBuf  )  );
		 tmpiRet  =  SendMessage(  hCtl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    		
		 if  (  pVar->guiData.param.iMenuId_selectedDev
			 &&  pFuncs->moniker.pf_getMoniker_v(  &gcap,  pVar->guiData.param.iMenuId_selectedDev  )  ==  gcap.rgpmVideoMenu[i]  )
		 {
			 iSel  =  i;
		 }
	}

	//
	if  (  iSel  >=  0  )  {
		tmpiRet  =  SendMessage(  hCtl,  LB_SETCURSEL,  (  WPARAM  )iSel,  (  LPARAM  )0  );    		 		 
	}


	iRet  =  0;

errLabel:
	return  iRet;
  }
#endif


//
 int  fillImObjs(  HWND  hDlg,  void  *  pVar  )
{
	int				iErr	=	-1;
	DLG_objs_var			&	m_var	=	*(  DLG_objs_var  *  )pVar;
	QY_MC					*	pQyMc	=	QY_GET_GBUF(  );
	QM_dbFuncs				&	g_dbFuncs  =  *pQyMc->p_g_dbFuncs;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	QY_OBJ_DB				*	pObjDb  =  pFuncs->pf_getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );
	if  (  !pObjDb  )  return  -1;
	//TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];
	//CDBVariant		varVals[10];

	switch  (  m_var.guiData.param.uiType  )  {
			case  CONST_objType_messenger:

				  g_dbFuncs.pf_fillImObjs_msgr(  hDlg,  pVar,  pObjDb->pDb  );
				  break;

			case  CONST_objType_imGrp:

				  g_dbFuncs.pf_fillImObjs_grp(  hDlg,  pVar,  pObjDb->pDb  );
				  break;
			
#ifdef  __isCli__
			case  CONST_objType_selectRemoteVideo:
				  if  (  fillImObjs_selectRemoteVideo(  hDlg,  pVar  )  )  goto  errLabel;
				  break;
			case  CONST_objType_selectADev:
				  fillImObjs_selectADev(  hDlg,  pVar  );
				  break;
			case  CONST_objType_selectVDev:
				  fillImObjs_selectVDev(  hDlg,  pVar  );
				  break;
			case  CONST_objType_selectLayoutType:
				  fillImObjs_selectLayoutType(  hDlg,  pVar  );
				  break;
			case  CONST_objType_selectIpc:
				  fillImObjs_selectIpc(hDlg, pVar);
				  break;
			case  CONST_objType_selOneBig:
				  fillImObjs_selOneBig(hDlg, pVar);
				  break;
			case  CONST_objType_selectRemotePtz:  //  2016/07/19
				  fillImObjs_selectRemotePtz(  hDlg,  pVar  );
				  break;
#endif
			default:
					break;
	}


	iErr  =  0;
errLabel:
	return  iErr;
 }
#endif


 //  2012/04/21
  int  tmpHandler_showActiveTalker(  void  *  p0,  void  *  p1,  MIS_MSGU  *  pMsg  )
{
	//  CDlgObjs  *		pDlg				=  (  CDlgObjs  *  )p0;
	HWND			hDlg				=	(  HWND  )p0;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;	
	FUNCS_for_isCliHelp		*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	DLG_objs_var	*	pVar			=	(  DLG_objs_var  *  )p1;
	if  (  !pVar  )  return  -1;
	DLG_objs_var	&	m_var			=	*pVar;
	//
	TCHAR			tBuf[256]			=	_T(  ""  );
	char			buf[32]				=	"";
	
	MIS_CNT			*	pMisCnt			=	(  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;

	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	TCHAR	talkerDesc[128];

	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_talkingFriend_qmc:
				  
				  //  影子窗口不需要显示
				  if  (  pMsg->talkingFriend_qmc.addr.uiTranNo_shadow  )  break;

				  //
				  pFuncs->pf_getTalkerDesc(  pMsg->talkingFriend_qmc.addr.idInfo,  0,  0,  talkerDesc,  mycountof(  talkerDesc  )  );

				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u %s"  ),  pMsg->talkingFriend_qmc.addr.idInfo.ui64Id,  talkerDesc  );

				  //  2012/05/24
#if  1  //  ndef  __DEBUG__
				  DLG_TALK_var  *  pDlgTalkVar;
				  pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  pMsg->talkingFriend_qmc.hWnd  );
				  if  (  pDlgTalkVar  )  {
					  if  (  pDlgTalkVar->ucbTmpMsgr  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( Tmp )"  ),  tBuf  );
				  }
#endif
				  //
				  SendMessage(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  ),  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    
				  break;
			default:
					break;
	}

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\t%d"  ),  m_var.usItemCount );
	OutputDebugString(  tBuf  );
	OutputDebugString(  _T(  "\n"  )  );
	



	return  0;
}


  int  tmpHandler_showImMsgLogQ(  void  *  p0,  void  *  p1,  MIS_MSGU  *  pMsg  )
{
	//  CDlgObjs  *		pDlg				=  (  CDlgObjs  *  )p0;
	HWND			hDlg				=	(  HWND  )p0;
	DLG_objs_var	*	pVar			=	(  DLG_objs_var  *  )p1;
	if  (  !pVar  )  return  -1;
	DLG_objs_var	&	m_var			=	*pVar;
	//
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	//
	TCHAR			tBuf[256]			=	_T(  ""  );
	char			buf[32]				=	"";
	TCHAR			senderDesc[64]		=	_T(  ""  );
	TCHAR			receiverDesc[64]	=	_T(  ""  );
	IM_CONTENTU	*	pContent			=	NULL;
	
	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_talk:
				  pContent  =  (  IM_CONTENTU  *  )pMsg->talk.data.buf;
				  displayShortTime(  pMsg->talk.tStartTime,  buf,  mycountof(  buf  )  );
				  pFuncs->pf_getTalkerDesc(  pMsg->talk.data.route.idInfo_from,  0,  0,  senderDesc,  mycountof(  senderDesc  )  );
				  pFuncs->pf_getTalkerDesc(  pMsg->talk.data.route.idInfo_to,  0,  0,  receiverDesc,  mycountof(  receiverDesc  )  );

				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u %s->%I64u %s"  ),  CQyString(  buf  ),  pMsg->talk.data.route.idInfo_from.ui64Id,  senderDesc,  pMsg->talk.data.route.idInfo_to.ui64Id,  receiverDesc  );
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: %s"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &g_pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
				  if  (  pContent->uiType  ==  CONST_imCommType_htmlContent  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %s"  ),  tBuf,  pContent->html.wBuf  );
				  }

				  SendMessage(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  ),  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    
				  break;
			case  CONST_misMsgType_task:
				  pContent  =  (  IM_CONTENTU  *  )pMsg->task.data.buf;
				  displayShortTime(  pMsg->task.tStartTime,  buf,  mycountof(  buf  )  );
				  pFuncs->pf_getTalkerDesc(  pMsg->task.data.route.idInfo_from,  0,  0,  senderDesc,  mycountof(  senderDesc  )  );
				  pFuncs->pf_getTalkerDesc(  pMsg->task.data.route.idInfo_to,  0,  0,  receiverDesc,  mycountof(  receiverDesc  )  );

				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u %s->%I64u %s"  ),  CQyString(  buf  ),  pMsg->task.data.route.idInfo_from.ui64Id,  senderDesc,  pMsg->task.data.route.idInfo_to.ui64Id,  receiverDesc  );
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: %s"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &g_pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
				  if  (  pContent->uiType  ==  CONST_imCommType_htmlContent  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %s"  ),  tBuf,  pContent->html.wBuf  );
				  }

				  SendMessage(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  ),  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    

				  break;
			default:
					break;
	}

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\t%d"  ),  m_var.usItemCount );
	OutputDebugString(  tBuf  );
	OutputDebugString(  _T(  "\n"  )  );
	



	return  0;
}



 __declspec(  dllexport  )  BOOL  dlgObjs_bFillContent(  HWND  hDlg,  void  *  pVar,  int  iObjType  )
{
	BOOL	bRet	=	FALSE;

	if  (  !pVar  )  return  FALSE;
	DLG_objs_var  &  m_var  =  *(  DLG_objs_var  *  )pVar;


	HWND	hCtl	=	GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  );

	SendMessage(  hCtl,  LB_RESETCONTENT,  0,  0  );
	m_var.usItemCount  =  0;

	int				iErr		=	-1;
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	int				idc_hidden	=	0;
	BOOL			bHidden;
	int				idc;
	MIS_CNT		*	pMisCnt		=	NULL;

	m_var.pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );  
	pMisCnt  =  (  MIS_CNT  *  )m_var.pMisCnt;

	m_var.guiData.param.uiType  =  iObjType;

	switch  (  m_var.guiData.param.uiType  )  {
			case  CONST_objType_messenger:
				  #ifdef  __NOTSUPPORT_DB__
						  qmObjQTraverse(  0,  pMisCnt->pObjQ,  (  PF_commonHandler  )tmpHandler_printQmObjQ,  hDlg,  &m_var  );
				  #else
						fillImObjs(  hDlg,  pVar  );
				  #endif
				  idc_hidden  =  m_var.guiData.iIDC_BUTTON_contact;
				  break;
			case  CONST_objType_imGrp:
				  #ifdef  __NOTSUPPORT_DB__
						  qmObjQTraverse(  0,  pMisCnt->pObjQ,  (  PF_commonHandler  )tmpHandler_printQmObjQ,  hDlg,  &m_var  );
				  #else
						fillImObjs(  hDlg,  pVar  );
				  #endif
				  idc_hidden  =  m_var.guiData.iIDC_BUTTON_group;
				  break;

			case  CONST_objType_selectRemoteVideo:
				  if  (  fillImObjs(  hDlg,  pVar  )  )  {
					  goto  errLabel;
				  }
				  break;				  
				  
			case  CONST_objType_selectADev:			//  2013/04/04
			case  CONST_objType_selectVDev:			//  2013/04/04
				  fillImObjs(  hDlg,  pVar  );
				  break;				  

			case  CONST_objType_selectLayoutType:	//  2013/06/24
			case  CONST_objType_selectRemotePtz:	//  2016/07/19
				  fillImObjs(  hDlg,  pVar  );
				  break;
			case  CONST_objType_selectIpc:
				  fillImObjs(  hDlg,  pVar  );
				  break;
			case  CONST_objType_selOneBig:
				  fillImObjs(hDlg, pVar);
				  break;
			default:
				    if  (  m_var.guiData.param.ucbActiveTalker  )  {		//  2012/04/21
						if  (  !pMisCnt  )  goto  errLabel;
						qTraverse(  &pMisCnt->talkingFriendQ,  (  PF_commonHandler  )tmpHandler_showActiveTalker,  hDlg,  &m_var  );
					
						break;
					}

				    qTraverse(  &pProcInfo->imMsgLogQ,  (  PF_commonHandler  )tmpHandler_showImMsgLogQ,  hDlg,  &m_var  );
					idc_hidden  =  m_var.guiData.iIDC_BUTTON_status;
					break;
	}

	idc  =  m_var.guiData.iIDC_BUTTON_contact;
	bHidden  =  idc_hidden  ==  idc;
	ShowWindow(  GetDlgItem(  hDlg,  idc  ),  bHidden  ?  SW_HIDE  :  SW_SHOW  );

	idc  =  m_var.guiData.iIDC_BUTTON_group;
	bHidden  =  idc_hidden  ==  idc;
	ShowWindow(  GetDlgItem(  hDlg,  idc  ),  bHidden  ?  SW_HIDE  :  SW_SHOW  );

	idc  =  m_var.guiData.iIDC_BUTTON_status;
	bHidden  =  idc_hidden  ==  idc;
	ShowWindow(  GetDlgItem(  hDlg,  idc  ),  bHidden  ?  SW_HIDE  :  SW_SHOW  );

	bRet  =  TRUE;

errLabel:

	return  bRet;
}

 __declspec(  dllexport  )  int dlgObjs_OnOK(  HWND  hDlg,  void  *  pVarParam  )
{
	int		iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	if  (  !pVarParam  )  return  -1;
	DLG_objs_var	&	m_var  =  *(  DLG_objs_var  *  )pVarParam;
	MIS_CNT			*	pMisCnt	=	(  MIS_CNT  *  )m_var.pMisCnt;
	
	// TODO: Add your specialized code here and/or call the base class
	//
	CQyMalloc	mallocObj;
	TCHAR  *	pT	=	NULL;

	HWND	hCtrl  =  GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  );

	int			iItemSelected	=	SendMessage(  hCtrl,  LB_GETCURSEL,  0,  0  );	
	if  (  iItemSelected  <  0  )  goto  errLabel;

	int		len  =  SendMessage(  hCtrl,  LB_GETTEXTLEN,  iItemSelected,  0  );
	if  (  len  <  0  )  goto  errLabel;
	len  ++  ;

	pT  =  (  TCHAR  *  )mallocObj.mallocf(  sizeof(  TCHAR  )  *  len  );
	if  (  !pT  )  goto  errLabel;
	SendMessage(  hCtrl,  LB_GETTEXT,  iItemSelected,  (  LPARAM  )pT  );

	char						buf[32];
	QY_MESSENGER_ID				idInfo_selected;
	TCHAR					*	pT1;


	switch  (  m_var.guiData.param.uiType  )  {
			case  CONST_objType_messenger:
			case  CONST_objType_imGrp:
				  pT1  =  _tcschr(  pT,  _T(  ' '  )  );
				  if  (  !pT1  )  goto  errLabel;
				  *pT1  =  0;

				  myTChar2Str(  pT,  buf,  mycountof(  buf  )  );
				  idStr2Info(  buf,  &idInfo_selected  );
				  //
				  if  (  idInfo_selected.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  goto  errLabel;
				  //
				  m_var.guiData.param.o.ui64Id_selected  =  idInfo_selected.ui64Id;
				  break;
			case  CONST_objType_selectRemoteVideo:  {
				  //  2013/02/13
				  QY_COLUMNINFO  *  pColumns  =  (  QY_COLUMNINFO  *  )m_var.pData_items;
				  if  (  iItemSelected  <  0  ||  iItemSelected  >=  m_var.nItems  )  goto  errLabel;

				  m_var.guiData.param.o.iVal_selected  =  pColumns[iItemSelected].type;
				  m_var.guiData.param.o.iSel  =  iItemSelected;	//  2014/05/13

				  //
				  if  (  !m_var.guiData.param.pObjBuf_selected  )  goto  errLabel;
				  if  (  m_var.guiData.param.uiSize_pObjBuf_selected  <  sizeof(  DYN_BMP_RULE  )  )  goto  errLabel;

				  QIS_dynBmp_info  *  pDynBmps  =  (  QIS_dynBmp_info  *  )m_var.pData;
				  DYN_BMP_RULE  *  pDynBmpRule_selected  =  (  DYN_BMP_RULE  *  )m_var.guiData.param.pObjBuf_selected;
				  //  memcpy(  m_var.guiData.param.pObjBuf_selected,   &pDynBmps[iItemSelected],  sizeof(  QIS_dynBmp_info  )  );
				  memcpy(  &pDynBmpRule_selected->dynBmp,   &pDynBmps[iItemSelected],  sizeof(  QIS_res_obj  )  );
				  safeTcsnCpy(  pDynBmps[iItemSelected].name,  pDynBmpRule_selected->name,  mycountof(  pDynBmpRule_selected->name  )  );
				  safeTcsnCpy(  pDynBmps[iItemSelected].cusName,  pDynBmpRule_selected->cusName,  mycountof(  pDynBmpRule_selected->cusName  )  );

				  }
				  break;
			case  CONST_objType_selectLayoutType:  
			case  CONST_objType_selOneBig:  {
				  //
				  pT1 = _tcschr(pT, ',');
				  if (!pT1)  goto  errLabel;
				  *pT1 = 0;
				  myTChar2Utf8(pT, buf, mycountof(buf));
				  QY_MESSENGER_ID idInfo;
				  idStr2Info(buf, &idInfo);
				  m_var.guiData.param.o.ui64Id_selected = idInfo.ui64Id;
				  pT1++;
				  m_var.guiData.param.o.iVal_selected = _ttol(pT1);

				  //
				  }
				  break;

			case  CONST_objType_selectIpc: {
				//
				pT1 = _tcschr(pT, ',');
				if (!pT1)  goto  errLabel;
				*pT1 = 0;
				//myTChar2Utf8(pT, buf, mycountof(buf));
				m_var.guiData.param.o.iVal_selected = _ttol(pT);

				//
			}
												break;

			case  CONST_objType_selectRemotePtz:  {
				  //  2013/06/24
				  QY_COLUMNINFO  *  pColumns  =  (  QY_COLUMNINFO  *  )m_var.pData_items;
				  if  (  iItemSelected  <  0  ||  iItemSelected  >=  m_var.nItems  )  goto  errLabel;

				  m_var.guiData.param.o.iVal_selected  =  pColumns[iItemSelected].type;
				  //
				  //
				  if  (  !m_var.guiData.param.pObjBuf_selected  )  goto  errLabel;
				  if  (  m_var.guiData.param.uiSize_pObjBuf_selected  <  sizeof(  DYN_BMP_RULE  )  )  goto  errLabel;

				  //
				  QIS_dynBmp_info  *  pDynBmps  =  (  QIS_dynBmp_info  *  )m_var.pData;
				  DYN_BMP_RULE  *  pDynBmpRule_selected  =  (  DYN_BMP_RULE  *  )m_var.guiData.param.pObjBuf_selected;
				  //
				  pDynBmpRule_selected->dynBmp.resObj.uiObjType  =  pColumns[iItemSelected].type;
				  //  2016/07/24
				  if  (  pDynBmpRule_selected->dynBmp.resObj.uiObjType  ==  CONST_objType_rtspStream  )  {
					  pDynBmpRule_selected->dynBmp.resObj  =  pDynBmps[iItemSelected].qisResObj.resObj;
				  }
				  

				  }
				  break;

			case  CONST_objType_selectADev:	{
				  if  (  !m_var.guiData.param.p0  )  goto  errLabel;
				  CAP_STUFF  &  gcap  =  *(  CAP_STUFF  *  )m_var.guiData.param.p0;
				  if  (  iItemSelected  <  0  ||  iItemSelected  >=  mycountof(  gcap.old_audioDevices.mems  )  )  goto  errLabel;
				  m_var.guiData.param.o.iSel  =  iItemSelected;
				  }
				  break;
			case  CONST_objType_selectVDev:  {
				  if  (  !m_var.guiData.param.p0  )  goto  errLabel;
				  CAP_STUFF  &  gcap  =  *(  CAP_STUFF  *  )m_var.guiData.param.p0;
				  if  (  iItemSelected  <  0  ||  iItemSelected  >=  mycountof(  gcap.rgpmVideoMenu  )  )  goto  errLabel;
				  m_var.guiData.param.o.iSel  =  iItemSelected;
				  }
				  break;
			default:

				  //  2012/04/21
				  if  (  m_var.guiData.param.ucbActiveTalker  )  {
					  pT1  =  _tcschr(  pT,  _T(  ' '  )  );
					  if  (  !pT1  )  goto  errLabel;
					  *pT1  =  0;

					  myTChar2Str(  pT,  buf,  mycountof(  buf  )  );
					  idStr2Info(  buf,  &idInfo_selected  );
					  //
					  if  (  idInfo_selected.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  goto  errLabel;
					  //
					  m_var.guiData.param.o.ui64Id_selected  =  idInfo_selected.ui64Id;
					  break;
				  }

				  pT1  =  _tcschr(  pT,  _T(  ' '  )  );
				  if  (  !pT1  )  goto  errLabel;
				  pT1  ++  ;
				  pT  =  pT1;  

				  pT1  =  _tcschr(  pT,  _T(  '>'  )  );
				  if  (  !pT1  )  goto  errLabel;
				  *pT1  =  0;  pT1  ++  ;

				  tTrim(  pT  );
				  myTChar2Str(  pT,  buf,  mycountof(  buf  )  );
				  idStr2Info(  buf,  &idInfo_selected  );
				  if  (  idInfo_selected.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					  pT  =  pT1;
					  pT1  =  _tcschr(  pT,  _T(  ':'  )  );
					  if  (  !pT1  )  goto  errLabel;
					  *pT1  =  0;

					  myTChar2Str(  pT,  buf,  mycountof(  buf  )  );
		
					  idStr2Info(  buf,  &idInfo_selected  );
				  }	
				  m_var.guiData.param.o.ui64Id_selected  =  idInfo_selected.ui64Id;
				  break;
	}

	iErr  =  0;
errLabel:
	return  iErr;
	
}

 __declspec(  dllexport  )  int dlgObjs_OnLbnSelchangeList0(  HWND  hDlg,  void  *  pVarParam  )
{
	int  iErr  =  -1;

	DLG_objs_var  *  pVar	=  (  DLG_objs_var  *  )pVarParam;
	QY_MC		  *  pQyMc	=  QY_GET_GBUF(  );

	CQyMalloc	mallocObj;
	TCHAR  *  pT	=  NULL;

	HWND	hCtrl  =  GetDlgItem(  hDlg,  pVar->guiData.iIDC_LIST0  );

	int  iItemSelected  =  SendMessage(  hCtrl,  LB_GETCURSEL,  0,  0  );
	if  (  iItemSelected  ==  LB_ERR  )  goto  errLabel;

	int  len  =  SendMessage(  hCtrl, LB_GETTEXTLEN,  iItemSelected,  0  );
	if  (  !len  )  goto  errLabel;
	len  ++;

	pT  =  (  TCHAR  *  )mallocObj.mallocf(  sizeof(  TCHAR  )  *  len  );
	if  (  !pT  )  goto  errLabel;
	SendMessage(  hCtrl,  LB_GETTEXT,  iItemSelected,  (  LPARAM  )pT  );


	switch  (  pVar->guiData.param.uiType  )  {
			case  CONST_objType_selectRemoteVideo:  {
				  //QY_DMITEM	   *  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_remoteVideoTable  );
				  QY_COLUMNINFO  *  pColumns  =  (  QY_COLUMNINFO  *  )pVar->pData_items;
				  int				  n;

				  if  (  iItemSelected  <  0  ||  iItemSelected  >=  pVar->nItems  )  goto  errLabel;

				  if  (  pColumns[iItemSelected].lParam  )  SetDlgItemText(  hDlg,  pVar->guiData.iIDOK,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_stop  )  );
				  else  SetDlgItemText(  hDlg,  pVar->guiData.iIDOK,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_start  )  );
				  }
				  break;
			default:
					break;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}