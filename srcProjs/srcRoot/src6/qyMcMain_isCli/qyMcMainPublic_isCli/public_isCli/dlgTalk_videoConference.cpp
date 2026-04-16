

#include	"stdafx.h"
#include	<time.h>
#include	<windowsx.h>
#include	<math.h>
#include	"qymcMainCommon.h"


#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"

#include	"qyOpenShellCommon.h"


#include	"tmpCeLib.h"

#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"

#include	"myresource.h"

#include	<assert.h>
#include	"qmcDxSurfacePublic.h"
#ifndef  __WINCE__
		 #include	"qmcConferenceWall.h"
#endif
#include	"qmcCmdProc.h"
#include	"dlgTalkProc.h"
#include	"isCliHelpPublic.h"
#include	"isCliD3dPublic.h"

#include	"qmcCommFunc_isCli.h"
//
#include	"funcsForIsCliHelp.h"
#include	"smLoginProc.h"


// int  refreshTaskAv_videoConferenceStarter(  HWND    hDlgTalk  )
 int  refreshTaskAv_videoConferenceStarter(  HWND    hDlgTalk,  void  *  pMsgTask  )
{
	int  iErr  =  -1;
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pm_var	=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk,  _T(  "refreshTaskAv_videoConferenceStarter"  )  );
	if  (  !pm_var  )  return  -1;
	DLG_TALK_var	&	m_var	=	*pm_var;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

	if  (  !m_var.av.taskInfo.bTaskExists  )  return  0;
	//  if  (  !m_var.av.taskInfo.ucbVideoConferenceStarter  )  return  0;
	if  (  !m_var.av.taskInfo.ucbStarter  )  return  0;

	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  m_var.av.taskInfo.iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;					  
	if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  return -1;// goto  errLabel;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

	//return	pProcInfo->processQ_media.qTraverse(  tmpHandler_refreshTaskAv_videoConferenceStarter,  (  void  *  )hDlgTalk,  pMsgTask  );

	if  (  pTc->videoConference.bNeedRefresh_activeMems_from  )  {
		pTc->videoConference.bNeedRefresh_activeMems_from  =  false;
	}


	iErr  =  0;

errLabel:

	//
	return  iErr;

}




 //  2009/05/31
 int  refreshTaskAv_videoConferenceOthers(  HWND  hDlg  )
{
	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var	*	pm_var	=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlg  );;
	if  (  !pm_var  )  return  -1;
	DLG_TALK_var	&	m_var	=	*pm_var;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

	if  (  !m_var.av.taskInfo.bTaskExists  )  return  0;
	//  if  (  m_var.av.taskInfo.ucbVideoConferenceStarter  )  return  0;
	if  (  m_var.av.taskInfo.ucbStarter  )  return  0;

	//return  pProcInfo->processQ_media.qTraverse(  tmpHandler_refreshTaskAv_videoConferenceOthers,  0,  (  void  *  )hDlg  );

	return  0;
}


#ifdef  __DEBUG__
 int  printDlgTalkVideoConference(  DLG_TALK_videoConference  *  p  )
{
	int		i;
	
	traceLogA(  (char*)  "printDlgTalkVideoConference starts"  );

	//
#if 0
	for  (  i  =  0;  i  <  p->usCntLimit_mems_from;  i  ++  )  {
		 if  (  p->pMems_from[i].idInfo.ui64Id  )  {		 
			 traceLogA(  (char*)  "\tmems_from[%d].idInfo %I64u",  i,  p->pMems_from[i].idInfo.ui64Id  );
		 }
	}
#endif
	//
	unsigned  short  usCntLimit_activeMems_from  =  p->usCntLimit_activeMems_from;
	if  (  !usCntLimit_activeMems_from  )  usCntLimit_activeMems_from  =  mycountof(  p->activeMems_from  );
	for  (  i  =  0;  i  <  usCntLimit_activeMems_from;  i  ++  )  {
		if  (  p->activeMems_from[i].avStream.idInfo.ui64Id  )  {
			traceLogA(  (char*)  "\tactiveMems[%d].idInfo %I64u, desc %S,  usIndex_mems_from %d",  i,  p->activeMems_from[i].avStream.idInfo.ui64Id,  p->activeMems_from[i].desc,  0  );
		 }
	}

	traceLogA(  (char*)  "printDlgTalkVideoConference ends"  );

	return  0;
}
#endif

  //
 BOOL  isMemFromActive(  DLG_TALK_videoConference  *  pDLG_TALK_videoConference,  QY_MESSENGER_ID  *  pIdInfo_from,  RES_obj_simple  *  pResObj_from,  int  *  pIndex_activeMems_from  )
{

	int		i;

	DLG_TALK_videoConference  *  pVc  =  (  DLG_TALK_videoConference  *  )pDLG_TALK_videoConference;

	//  2014/11/30
	if  (  !pIdInfo_from  ||  !pIdInfo_from->ui64Id  )  {
		showInfo_open0(  0,  0,  _T(  "Note: isMemFromActive returns false, for idInfo_from is 0"  )  );
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "isMemFromActive failed"  )  );
		#endif
		return  FALSE;
	}
	RES_obj_simple  resObj_from={0};
	if  (  pResObj_from  )  {
		resObj_from  =  *pResObj_from;
	}

	//
	for  (  i  =  0;  i  <  mycountof(  pVc->activeMems_from  );  i  ++  )  {
		DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pVc->activeMems_from[i];
		if  (  pIdInfo_from->ui64Id  ==  pActiveMem_from->avStream.idInfo.ui64Id
			&&  resObj_from.uiObjType  ==  pActiveMem_from->avStream.obj.resObj.uiObjType
			&&  resObj_from.usIndex_obj  ==  pActiveMem_from->avStream.obj.resObj.usIndex_obj  )  			
		{		
			break;
		}
	}
	if  (  i  ==  mycountof(  pVc->activeMems_from  )  )  return  FALSE;

	if  (  pIndex_activeMems_from  )  *pIndex_activeMems_from  =  i;

	return  TRUE;
}

 //
 BOOL  isVideoActive(  MIS_CNT  *  pMisCnt,  DLG_TALK_videoConference  *  pVc,  QY_MESSENGER_ID  *  pIdInfo_from,  unsigned  int  tn_video,  int  *  pIndex_activeMems_from  )
 {
	 if  (  !pIdInfo_from  )  return  false;
	 if  (  !tn_video  )  return  false;

	 QY_MESSENGER_ID  idInfo_from  =  {0};
	 if  (  pIdInfo_from  )  idInfo_from.ui64Id  =  pIdInfo_from->ui64Id;
	 if  (  !idInfo_from.ui64Id  )  idInfo_from.ui64Id  =  pMisCnt->idInfo.ui64Id;

	 int  i;
	 for  (  i  =  0;  i  <  pVc->usCntLimit_activeMems_from;  i  ++   )  {
		 DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  = &pVc->activeMems_from[i];
		 if  (  !pActiveMem_from->avStream.idInfo.ui64Id  )  continue;
		 if  (  pActiveMem_from->avStream.idInfo.ui64Id  ==  idInfo_from.ui64Id
			 &&  pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev  ==  tn_video  )
		 {
			 break;
		 }
	 }

	 if  (  i  ==  pVc->usCntLimit_activeMems_from  )  return  false;

	 if  (  pIndex_activeMems_from  )  *pIndex_activeMems_from  =  i;
	 return  true;
 }




 //
 int  addTo_activeMems_from(  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo,  AV_stream_simple  *  pAss,  DLG_TALK_videoConference  *  pVc  )
 {
	 int  iErr  =  -1;

	 if  (  !pAss  )  return  -1;

	 if  (  isMemFromActive(  pVc,  pIdInfo,  &pAss->resObj,  mynull  )  )  return 0;
	 int  i;
	 DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from;
	 for  (  i  =  0;i  <  pVc->usCntLimit_activeMems_from;  i  ++  )  {
		 pActiveMem_from  =  &pVc->activeMems_from[i];
		 if  (  pActiveMem_from->avStream.idInfo.ui64Id  ==  0  )  break;
	 }
	 if  (  i  ==  pVc->usCntLimit_activeMems_from  )  {
		 showInfo_open0(  0,  0,  _T(  "addTo_activeMems_from failed, too many activeMems"  )  );
		 return  -1;
	 }
	 pActiveMem_from  =  &pVc->activeMems_from[i];
		 
	 pActiveMem_from->avStream.idInfo=*pIdInfo;
	 pActiveMem_from->avStream.obj  =  *pAss;

	 //
	 M_getActiveMemDesc(  pMisCnt,  &pActiveMem_from->avStream.idInfo,  pActiveMem_from->desc,  mycountof(  pActiveMem_from->desc  )  );


	 iErr  =  0;


	 return  iErr;
 }

 //
 int  removeFrom_activeMems_from(  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo,  AV_stream_simple  *  pAss,  DLG_TALK_videoConference  *  pVc  )
 {
	 int  iErr  =  -1;

	 if  (  !pAss  )  return  -1;

	 if  (  !isMemFromActive(  pVc,  pIdInfo,  &pAss->resObj,  mynull  )  )  return 0;
	 int  i;
	 DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from;
	 for  (  i  =  0;i  <  pVc->usCntLimit_activeMems_from;  i  ++  )  {
		 pActiveMem_from  =  &pVc->activeMems_from[i];
		 if  (  pActiveMem_from->avStream.idInfo.ui64Id  ==  pIdInfo->ui64Id
			 &&  pActiveMem_from->avStream.obj.resObj.uiObjType  ==  pAss->resObj.uiObjType
			 &&  pActiveMem_from->avStream.obj.resObj.usIndex_obj  ==  pAss->resObj.usIndex_obj  )  break;
	 }
	 if  (  i  ==  pVc->usCntLimit_activeMems_from  )  {
		 showInfo_open0(  0,  0,  _T(  "addTo_activeMems_from failed, too many activeMems"  )  );
		 return  -1;
	 }
	 pActiveMem_from  =  &pVc->activeMems_from[i];
		 
	 memset(  pActiveMem_from,  0,  sizeof(  pActiveMem_from[0]  )  );

	 iErr  =  0;


	 return  iErr;
 }




 //
 BOOL  isMemFromRequesting(  DLG_TALK_videoConference  *  pVc,  QY_MESSENGER_ID  *  pIdInfo_from  )
{
	int		i;

	for  (  i  =  0;  i  <  mycountof(  pVc->requestingMems_from  );  i  ++  )  {
		if  (  pIdInfo_from->ui64Id  ==  pVc->requestingMems_from[i].avStream.idInfo.ui64Id  )  break;
	}
	if  (  i  ==  mycountof(  pVc->requestingMems_from  )  )  return  FALSE;

	return  TRUE;
}

  int  addTo_requestingMems_from(  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo,  LPCTSTR  talkerDesc,  DLG_TALK_videoConference  *  pVc  )
{
	int		i;
	if (!talkerDesc)talkerDesc = _T("");

	if  (  !pIdInfo  ||  !pIdInfo->ui64Id  )  return  -1;

	if  (  isMemFromRequesting(  pVc,  pIdInfo  )  )  return  0;
	for  (  i  =  0;  i  <  mycountof(  pVc->requestingMems_from  );  i  ++  )  {
		if  (  !pVc->requestingMems_from[i].avStream.idInfo.ui64Id  )  break;
	}
	if  (  i  ==  mycountof(  pVc->requestingMems_from  )  )  return  -1;
	
	pVc->requestingMems_from[i].avStream.idInfo.ui64Id  =  pIdInfo->ui64Id;
	//
	if  (  talkerDesc[0]) safeTcsnCpy(talkerDesc, pVc->requestingMems_from[i].desc, mycountof(pVc->requestingMems_from[i].desc));
	else {
		//  getTalkerDesc(  pMisCnt,  pIdInfo,  pVc->requestingMems_from[i].desc,  mycountof(  pVc->requestingMems_from[i].desc  ),  0,  0  );
		M_getActiveMemDesc(pMisCnt, pIdInfo, pVc->requestingMems_from[i].desc, mycountof(pVc->requestingMems_from[i].desc));
	}

	return  0;
}

 int  removeFrom_requestingMems_from(  DLG_TALK_videoConference  *  pVc,  QY_MESSENGER_ID  *  pIdInfo  )
{
	int  i;
	for  (  i  =  0;  i  <  mycountof(  pVc->requestingMems_from  );  i  ++  )  {
		if  (  pVc->requestingMems_from[i].avStream.idInfo.ui64Id  ==  pIdInfo->ui64Id  )  {
			memset(  &pVc->requestingMems_from[i],  0,  sizeof(  pVc->requestingMems_from[i]  )  );
			break;			
		}
	}

	return  0;
}






//
#if  0
 int  old_confOthers_requestToSpeak(  HWND  hDlgTalk,  BOOL  bRequestToSpeak  )
{
	int						iErr				=		-1;
	CHelp_getDlgTalkVar		help_getDlgTalkVar;
	DLG_TALK_var		*	pm_var				=		(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pm_var  )  return  -1;	
	DLG_TALK_var		&	m_var				=		*pm_var;
	MC_VAR_isCli			*	pProcInfo			=		QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	//
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	//
	if  (  !m_var.av.taskInfo.bTaskExists  )  return  -1;
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  m_var.av.taskInfo.iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;



	//
	TASK_INTERACTION_REQ	req;
	int						lenInBytes			=		0;
	
	if  (  bRequestToSpeak  )  {
		QY_SHARED_OBJ	*	pSharedObj		=  NULL;

		if  (  !(  pSharedObj  =	getSharedObjByIndex(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv  )  )  )  goto  errLabel;

		if  (  pSharedObj->iIndex_curUsr  ==  m_var.av.iIndex_usr_localAv  )  {
			if  (  !pTaskInfo->var.curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  {
				#ifdef  __DEBUG__
						traceLog((TCHAR*)  _T(  "Warning: requestToSpeak_videoConferenceOthers: idInfo_to is 0"  )  );
				#endif
					//
					if  (  addToMsgrs_sendLocalAv(  pProcInfo,  m_var.pMisCnt,  &m_var.av.taskInfo.idInfo_starter,  FALSE,  &pTaskInfo->var.curRoute_sendLocalAv  )  )  {
					#ifdef  __DEBUG__
							traceLogA(  (char*)  "requestToSpeak_videoConferenceOthers: addToMsgrs_sendLocalAv failed."  );		//  对视频会议的情况，如果已经有了，就不能再加进去了。但是不妨碍其他人参与视频会议。所以不能退出。
					#endif
					goto  errLabel;
				}
			}
			
			//  2014/08/25			
			setFlg_forceKeyFrame(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv  );

			//
			pFuncs->pf_resumeLocalAudioRecorder(  m_var.av.iIndex_sharedObj_localAv  );

		}
	}

	memset(  &req,  0,  sizeof(  req  )  );
	req.uiType  =  CONST_imCommType_taskInteractionReq;
	req.usOp  =  bRequestToSpeak  ?  CONST_imOp_requestToSpeak  :  CONST_imOp_stopSpeaking;
	req.tStartTime_org  =  m_var.av.taskInfo.tStartTime_org;
	req.uiTranNo_org  =  m_var.av.taskInfo.uiTranNo_org;
	//req.uiContentType_org  =  m_var.av.taskInfo.uiContentType_org;
	//
	//  2015/02/17
	if  (  bRequestToSpeak  )  {
		req.avStream.obj.tranInfo  =  m_var.av.taskInfo.local_avStream.tranInfo;
		//
#ifdef  __DEBUG__
		#if  1
		TCHAR  tBuf[128];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "send. a %d, v %d"  ),  req.avStream.obj.tranInfo.audio.uiTranNo_openAvDev,  req.avStream.obj.tranInfo.video.uiTranNo_openAvDev  );
		showInfo_open0(  0,  0,  tBuf  );
		#endif
#endif
	}
	//
	if  (  m_var.av.taskInfo.ucbVideoConference  )  req.idInfo_imGrp_related.ui64Id  =  m_var.addr.idInfo.ui64Id;
	//	
	lenInBytes  =  sizeof(  req  );			
	//					
	MACRO_prepareForTran(  );						
	//	
	if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendTask,  tStartTran,  uiTranNo,  0,  0,  0,  (  char  *  )&req,  lenInBytes,  NULL,  NULL,  NULL,  &m_var.av.taskInfo.idInfo_starter,  0,  NULL,  FALSE  )  )  goto  errLabel;

	//
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  bRequestToSpeak  ?  _T(  "Request to speak"  )  :  _T(  "Request to stop speaking"  )  );

	iErr  =  0;
errLabel:
	return  iErr;
}
#endif


 //
 int  fill_resObj(  QY_SHARED_OBJ  *  pSharedObj,  AV_stream  *  pAs  )
 {
	 int  objType  =  0;
	 
	 //
	 switch  (  pSharedObj->uiType1  )  {
			 case  CONST_sharedObjType_screen:
				   objType  =  CONST_objType_screen;
				   break;
			 case  CONST_sharedObjType_mediaDevice:
				   if  (  isAvFlg_unresizable(pSharedObj->taskAvProps.v.ucAvFlg)) {					
					   objType  =  CONST_objType_screen;
				   }
				   break;
			 default:
					break;
	 }

	 //
	 pAs->obj.resObj.uiObjType  =  objType;
	 
	 return  0;
 }


 //
 //
 //int  confStarter_requestToSpeak(  HWND  hDlgTalk,  QY_MESSENGER_ID  *  pIdInfo,  AV_stream_simple  *  pAss,  BOOL  bRequestToSpeak  )
 int  confStarter_requestToSpeak(  HWND  hDlgTalk,  QY_MESSENGER_ID  *  pIdInfo,  AV_stream_simple  *  pAss,  LPCTSTR  talkerDesc,  BOOL  bRequestToSpeak  )
{
	int								iErr								=	-1;
	CHelp_getDlgTalkVar				help_getDlgTalkVar;
	DLG_TALK_var				*	pm_var								=(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pm_var  )  return  -1;
	DLG_TALK_var				&	m_var								=	*pm_var;
	MC_VAR_isCli					*	pProcInfo							=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	QY_MC* pQyMc = m_var.pQyMc;// QY_GET_GBUF();
	//
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	//
	int								i;
	int								index_activeMems_from;
	BOOL							bNeedRefresh_requestingMems_from	=	FALSE;
	BOOL							bNeedRefresh_display				=	FALSE;


	if  (  !pIdInfo  ||  !pIdInfo->ui64Id  )  return  -1;
	if  (  !talkerDesc  )  talkerDesc  =  _T(  ""  );

	//
	if  (  !m_var.av.taskInfo.bTaskExists  )  return  -1;
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  m_var.av.taskInfo.iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;
	
	//		
	DLG_TALK_videoConference	*	pVc									=	&pTc->videoConference;;

	//
	if  (  refreshTaskAv_videoConferenceStarter(  hDlgTalk,  NULL  )  <  0  )  return  -1;

	#ifdef  __DEBUG__
			printDlgTalkVideoConference(  pVc  );
	#endif

	//
	RES_obj_simple  ros  =  {0};
	if  (  pAss  )  {
		ros  =  pAss->resObj;
	}

	//
	if  (  bRequestToSpeak  )  {

		int  index_active  =  0;

		if  (  !isMemFromActive(  pVc,  pIdInfo,  &ros,  &index_active  )  )  {				
			for  (  i  =  0;  i  <  pVc->usCntLimit_activeMems_from;  i  ++  )  {
				if  (  !pVc->activeMems_from[i].avStream.idInfo.ui64Id  )  break;			
			}
			//
			bool  bSpeakerListFull = false;
			if (!ros.uiObjType && isActiveMemsFull(m_var.av.taskInfo.iTaskId, true)) bSpeakerListFull = true;
			//
			if  (  i  ==  pVc->usCntLimit_activeMems_from  
				||  bSpeakerListFull
				)  
			{
				#ifdef  __DEBUG__
						traceLogA(  (char*)  "ativeMems_from is full, try to add to requestingMems"  );  
				#endif
				TCHAR  tBuf[128];
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u %s. %s %d"  ),  pIdInfo->ui64Id,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotSpeak  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_micListFull  ),  (  int  )pVc->usCntLimit_activeMems_from  );
				showNotification_open(  0,  0,  0,  tBuf  );
				showNotification_d3d(  hDlgTalk,  tBuf  );  
				//
				if  (  !isMemFromRequesting(  pVc,  pIdInfo  )  )  {
					if  (  !addTo_requestingMems_from(  m_var.pMisCnt,  pIdInfo,  talkerDesc,  pVc  )  )  bNeedRefresh_requestingMems_from  =  TRUE;
				}
				}
			else  {
				    index_activeMems_from  =  i;
										
					DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pVc->activeMems_from[index_activeMems_from];
					//
					memset(  pActiveMem_from,  0,  sizeof(  pActiveMem_from[0]  )  );
					//
					pVc->activeMems_from[index_activeMems_from].avStream.idInfo.ui64Id  =  pIdInfo->ui64Id;//pVc->pMems_from[i].idInfo.ui64Id;
					//pVc->activeMems_from[index_activeMems_from].usIndex_pMems_from  =  -1;//i;
					if  (  pAss  )  {
							  //pVc->activeMems_from[index_activeMems_from].avStream.obj.tranInfo  =  pAss->tranInfo;
							  pVc->activeMems_from[index_activeMems_from].avStream.obj  =  *pAss;
					}
					//
					if  (  talkerDesc[0]  )  safeTcsnCpy(  talkerDesc,  pActiveMem_from->desc,  mycountof(  pActiveMem_from->desc  )  );
					else  M_getActiveMemDesc(  m_var.pMisCnt,  &pActiveMem_from->avStream.idInfo,  pActiveMem_from->desc,  mycountof(  pActiveMem_from->desc  )  );
					
					//					
					pVc->bNeedRefresh_activeMems_from  =  TRUE;

						
					traceLogA(  (char*)  "alloc activeMems_from[%d] for %I64u, %d",  index_activeMems_from,  pIdInfo->ui64Id,  i  );	

					
					if  (  isMemFromRequesting(  pVc,  pIdInfo  )  )  {					
						removeFrom_requestingMems_from(  pVc,  pIdInfo  );  						
						bNeedRefresh_requestingMems_from  =  TRUE;					
					}					
					
			  }
			//
			}
		else  {
			  DLG_TALK_videoConferenceActiveMemFrom  *  pActive  =  &pTc->videoConference.activeMems_from[index_active];
			  if  (  pAss  )  {
				  if  (  pAss->tranInfo.audio.uiTranNo_openAvDev  ==  0  &&  pAss->tranInfo.video.uiTranNo_openAvDev  ==  0  )  goto  errLabel;
				  if  (  pActive->avStream.obj.tranInfo.audio.uiTranNo_openAvDev  !=  pAss->tranInfo.audio.uiTranNo_openAvDev  
					  ||  pActive->avStream.obj.tranInfo.video.uiTranNo_openAvDev  !=  pAss->tranInfo.video.uiTranNo_openAvDev  )  
				  {
					  pActive->avStream.obj.tranInfo  =  pAss->tranInfo;
					  //
					  showInfo_open0(  0,  0,  _T(  "update activeMem"  )  );
					  //
					  pVc->bNeedRefresh_activeMems_from  =  true;
				  }		
			  }
		}
		//
		}
	else  {  //  stop speaking
		  for  (  i  =  0;  i  <  pVc->usCntLimit_activeMems_from;  i  ++  )  {
			   if  (  pVc->activeMems_from[i].avStream.idInfo.ui64Id  ==  pIdInfo->ui64Id  
				   &&  pVc->activeMems_from[i].avStream.obj.resObj.uiObjType  ==  ros.uiObjType
				   &&  pVc->activeMems_from[i].avStream.obj.resObj.usIndex_obj  ==  ros.usIndex_obj  )  				
			   {
					   break;
			   }
		  }
		  if  (  i  <  pVc->usCntLimit_activeMems_from  )  {
			  memset(  &pVc->activeMems_from[i],  0,  sizeof(  pVc->activeMems_from[i]  )  );
			  //
			  pVc->bNeedRefresh_activeMems_from  =  TRUE;
		  }
		  //
		  if  (  isMemFromRequesting(  pVc,  pIdInfo  )  )  {
			  removeFrom_requestingMems_from(  pVc,  pIdInfo  );
			  bNeedRefresh_requestingMems_from  =  TRUE;
		  }
	}

	if  (  pVc->bNeedRefresh_activeMems_from  )  {
		if  (  refreshTaskAv_videoConferenceStarter(  hDlgTalk,  NULL  )  <  0  )  goto  errLabel;
		bNeedRefresh_display  =  TRUE;
		
		//  2010/09/12
		if  (  !bRequestToSpeak  )  {
			dlgTalk_freeCapImageBySth_mgr(  hDlgTalk,  m_var.av.taskInfo.iTaskId,  pIdInfo  );	//  2010/09/12
		}
	}
	if  (  bNeedRefresh_requestingMems_from  )  bNeedRefresh_display  =  TRUE;

	if  (  pIdInfo->ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  
		&&  ros.uiObjType  ==  0  )  
	{	//  It is me
		QY_SHARED_OBJ	*	pSharedObj		=  NULL;
		SHARED_OBJ_USR	*	pSharedObjUsr	=	NULL;
		unsigned  char		ucbNotSendData	=	!isMemFromActive(  pVc,  pIdInfo,  mynull,  NULL  );

	    #ifdef  __DEBUG__
				traceLogA(  (char*)  "requestToSpeak: iIndex_sharedObj %d",  m_var.av.iIndex_sharedObj_localAv  );
		#endif

		pSharedObj  =  getSharedObjByIndex(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv  );
		if  (  !pSharedObj  )  goto  errLabel;
		pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  m_var.av.iIndex_usr_localAv  );
		if  (  !pSharedObjUsr  )  goto  errLabel;

		if  (  pTc->ucbNotSendData  !=  ucbNotSendData  )  {
			pTc->ucbNotSendData  =  ucbNotSendData;
			bNeedRefresh_display  =  TRUE;
		}
		//
		if  (  !ucbNotSendData  )  {

			//  2009/05/30			
			//isMemFromActive(  pVc,  pIdInfo,  null,  &pSharedObjUsr->iIndex_activeMems_from_videoConferenceStarter  );

			//
			if  (  pSharedObj->iIndex_curUsr  ==  m_var.av.iIndex_usr_localAv  )  {
				//
				if  (  !m_var.av.taskInfo.ucbVideoConference  )  {
					#ifdef  __DEBUG__
							if  (  !pTaskInfo->var.curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  {
								traceLog((TCHAR*)  _T(  "requestToSpeak_videoConferenceStarter: inInfo_to error"  )  );				
							}
					#endif
					}
				else  {
					  if  (  !pTaskInfo->var.curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  )  {	
						  //
						  //if  (  addToMsgrs_sendLocalAv(  pProcInfo,  m_var.pMisCnt,  &m_var.addr.idInfo,  TRUE,  false,  &pTaskInfo->var.curRoute_sendLocalAv,  _T( "confStater_requestToSpeak.628"  ))) 
						  if (addToMsgrs_sendLocalAv(pProcInfo, m_var.pMisCnt, &m_var.addr.idInfo, TRUE, &pTaskInfo->var.curRoute_sendLocalAv, false, _T("confStater_requestToSpeak.628")))
						  {
							#ifdef  __DEBUG__
									traceLogA(  (char*)  "requestToSpeak_videoConferenceStarter: addToMsgrs_sendLocalAv failed."  );		//  对视频会议的情况，如果已经有了，就不能再加进去了。但是不妨碍其他人参与视频会议。所以不能退出。
							#endif
							//
							goto  errLabel;					
						  }				
					  }	
				}
			
				//  2014/08/25
				//int  setFlg_forceKeyFrame(  int  iIndex_sharedObj  )
				setFlg_forceKeyFrame(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv  );
  
				//
				pFuncs->pf_resumeLocalAudioRecorder(  pQyMc,  m_var.av.iIndex_sharedObj_localAv  );

				//  2017/09/13
				pFuncs->pf_resumeLocalVideo(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv  );  

			}
		}

	}

	//
	if  (  bNeedRefresh_display  )  {

		refreshTalkerList(  hDlgTalk  );
		
	}

	//  2013/07/20
	//  refreshImgs_d3dWall(  hDlgTalk  );
	dyn_d3dWall_refreshWallMemByTalker(  hDlgTalk  );

	//
	iErr  =  0;
errLabel:
	return  iErr;
}


 //
 int  confOthers_requestToSpeak(  HWND  hDlgTalk,  int  index_sharedObj,  RES_obj_simple  *  pRos_toStop,  BOOL  bRequestToSpeak  )
{
	int						iErr				=		-1;
	CHelp_getDlgTalkVar		help_getDlgTalkVar;
	DLG_TALK_var		*	pm_var				=		(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pm_var  )  return  -1;	
	DLG_TALK_var		&	m_var				=		*pm_var;
	MC_VAR_isCli			*	pProcInfo			=		QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	//
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	//
	MIS_CNT  *  pMisCnt  =  m_var.pMisCnt;

	//
	if  (  !m_var.av.taskInfo.bTaskExists  )  return  -1;
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  m_var.av.taskInfo.iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;

	//
	int  iTaskId  =  m_var.av.taskInfo.iTaskId;

	//
	TASK_INTERACTION_REQ	req;
	int						lenInBytes			=		0;
	
	if  (  bRequestToSpeak  )  {
		if  (  index_sharedObj  ==  m_var.av.iIndex_sharedObj_localAv  )  {
			//
		QY_SHARED_OBJ	*	pSharedObj		=  NULL;

		if  (  !(  pSharedObj  =	getSharedObjByIndex(  pProcInfo,  index_sharedObj  )  )  )  goto  errLabel;

		if  (  pSharedObj->iIndex_curUsr  ==  m_var.av.iIndex_usr_localAv  )  {
			if  (  !pTaskInfo->var.curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  {
				#ifdef  __DEBUG__
						traceLog((TCHAR*)  _T(  "Warning: requestToSpeak_videoConferenceOthers: idInfo_to is 0"  )  );
				#endif
					//
					if  (  addToMsgrs_sendLocalAv(  pProcInfo,  m_var.pMisCnt,  &m_var.av.taskInfo.idInfo_starter,  FALSE,  &pTaskInfo->var.curRoute_sendLocalAv,  false,  _T(  "confOthers_requestToSpeak.711"  ))) {
					#ifdef  __DEBUG__
							traceLogA(  (char*)  "requestToSpeak_videoConferenceOthers: addToMsgrs_sendLocalAv failed."  );		//  对视频会议的情况，如果已经有了，就不能再加进去了。但是不妨碍其他人参与视频会议。所以不能退出。
					#endif
					goto  errLabel;
				}
			}
			
			//  2014/08/25			
			setFlg_forceKeyFrame(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv  );

			//
			pFuncs->pf_resumeLocalAudioRecorder(  pProcInfo->pQyMc,  m_var.av.iIndex_sharedObj_localAv  );

		}
		}
	}

	//
	memset(  &req,  0,  sizeof(  req  )  );
	req.uiType  =  CONST_imCommType_taskInteractionReq;
	req.usOp  =  bRequestToSpeak  ?  CONST_imOp_requestToSpeak  :  CONST_imOp_stopSpeaking;
	req.tStartTime_org  =  m_var.av.taskInfo.tStartTime_org;
	req.uiTranNo_org  =  m_var.av.taskInfo.uiTranNo_org;
	//req.uiContentType_org  =  m_var.av.taskInfo.uiContentType_org;
	//
	//  2015/02/17
	if  (  bRequestToSpeak  )  {
		if  (  index_sharedObj  ==  m_var.av.iIndex_sharedObj_localAv  )  {
			req.avStream.obj.tranInfo  =  m_var.av.taskInfo.local_avStream.tranInfo;
			//
			req.iHkStatus = get_iHkStatus();	//  2023/05/04
			//
			req.ucbNvr = bNvr();

			}
		else  {
			  QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  index_sharedObj  );
			  if  (  !pSharedObj  )  goto  errLabel;
			  //
			  fill_resObj(  pSharedObj,  &req.avStream  );
			  //
			  int  index_shareObjUsr  =  getSharedObjUsrIndex(  pProcInfo,  iTaskId,  index_sharedObj  );
			  if  (  index_shareObjUsr  <  0  )  goto  errLabel;
			  SHARED_OBJ_USR  *  pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  index_shareObjUsr  );
			  //
			  CAP_procInfo_bmpU  *  pCapV  =  getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
			  if  (  pCapV  )  {
			  
				  req.avStream.obj.tranInfo.video.uiTranNo_openAvDev  =  pSharedObjUsr->uiTranNo_openAvDev_v;
				  req.avStream.obj.tranInfo.video.compressor  =  pCapV->common.compressVideo.compressor;
				  req.avStream.obj.tranInfo.video.vh_decompress  =  pCapV->common.compressVideo.vh_decompress;
				  req.avStream.obj.tranInfo.video.vh_compress  =  pCapV->common.compressVideo.vh_compress;
				  req.avStream.obj.tranInfo.video.vh_stream  =  pCapV->common.compressVideo.vh_stream;
			  }
			  //
			  CAP_procInfo_audioU* pCapA = getCapAudioBySth(pProcInfo, pSharedObj->iIndex_capAudio, 0);
			  if (pCapA) {

				  req.avStream.obj.tranInfo.audio.uiTranNo_openAvDev = pSharedObjUsr->uiTranNo_openAvDev_a;
				  req.avStream.obj.tranInfo.audio.compressor = pCapA->common.compressAudio.compressor;
				  req.avStream.obj.tranInfo.audio.ah_decompress = pCapA->common.compressAudio.ah_decompress;
				  req.avStream.obj.tranInfo.audio.ah_compress = pCapA->common.compressAudio.ah_compress;
				  req.avStream.obj.tranInfo.audio.ah_stream = pCapA->common.compressAudio.ah_stream;
			  }


		}

		//
		if (pProcInfo->m_iCtxSubtype == CONST_ctxSubtype_qmcSm) {
			Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
			if (pCtxSm &&
				pCtxSm->smTerminalInitCfg.fake_talkerDesc[0])
			{
				safeTcsnCpy(pCtxSm->smTerminalInitCfg.fake_talkerDesc, req.talkerDesc, mycountof(req.talkerDesc));
			}
			else {
				safeTcsnCpy(pProcInfo->av.confLayout.login_termialName, req.talkerDesc, mycountof(req.talkerDesc));
			}
			//
			}
		else {
			getTalkerDesc(pMisCnt->idInfo, req.talkerDesc, mycountof(req.talkerDesc), NULL, 0);
		}

		//
#ifdef  __DEBUG__
		#if  1
		TCHAR  tBuf[128];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "send. a %d, v %d"  ),  req.avStream.obj.tranInfo.audio.uiTranNo_openAvDev,  req.avStream.obj.tranInfo.video.uiTranNo_openAvDev  );
		showInfo_open0(  0,  0,  tBuf  );
		#endif
#endif
		}
	else  {
		  if  (  pRos_toStop  )  {
			  req.avStream.obj.resObj  =  *pRos_toStop;		
		  }
	}

	//
	if  (  m_var.av.taskInfo.ucbVideoConference  )  req.idInfo_imGrp_related.ui64Id  =  m_var.addr.idInfo.ui64Id;
	
	//
	req.ucStep = 5;  //  for test	
	
	//	
	lenInBytes  =  sizeof(  req  );			
	//					
	MACRO_prepareForTran(  );						
	//	
	if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendTask,  tStartTran,  uiTranNo,  0,  0,  0,  (  char  *  )&req,  lenInBytes,  NULL,  NULL,  NULL,  &m_var.av.taskInfo.idInfo_starter,  0,  NULL,  FALSE  )  )  goto  errLabel;

	//
	if (bRequestToSpeak) {
		if (index_sharedObj == m_var.av.iIndex_sharedObj_localAv) {
			//
			pProcInfo->av.confLayout.taskInfo.localAv.tranInfo  =  m_var.av.taskInfo.local_avStream.tranInfo;
			pProcInfo->av.confLayout.taskInfo.localAv.idInfo_imGrp_related = m_var.addr.idInfo;
			pProcInfo->av.confLayout.taskInfo.localAv.idInfo_starter = m_var.av.taskInfo.idInfo_starter;
		}
	}



	//
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  bRequestToSpeak  ?  _T(  "Request to speak"  )  :  _T(  "Request to stop speaking"  )  );

	iErr  =  0;
errLabel:
	return  iErr;
}









//
 int  confOthers_requestToOp(HWND  hDlgTalk, int  index_sharedObj, RES_obj_simple* pRos_toStop, int  op)
 {
	 int						iErr = -1;
	 CHelp_getDlgTalkVar		help_getDlgTalkVar;
	 DLG_TALK_var* pm_var = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hDlgTalk);
	 if (!pm_var)  return  -1;
	 DLG_TALK_var& m_var = *pm_var;
	 MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	 //
	 FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	 if (!pFuncs)  return  -1;
	 //
	 MIS_CNT* pMisCnt = m_var.pMisCnt;

	 TASK_INTERACTION_REQ	req;

	 memset(&req, 0, sizeof(req));
	 req.uiType = CONST_imCommType_taskInteractionReq;
	 req.usOp = op;//bRequestToSpeak ? CONST_imOp_requestToSpeak : CONST_imOp_stopSpeaking;
	 req.tStartTime_org = m_var.av.taskInfo.tStartTime_org;
	 req.uiTranNo_org = m_var.av.taskInfo.uiTranNo_org;

	 if (m_var.av.taskInfo.ucbVideoConference)  req.idInfo_imGrp_related.ui64Id = m_var.addr.idInfo.ui64Id;

	 int lenInBytes = sizeof(req);
	 //					
	 MACRO_prepareForTran();

	 if (postMsgTask2Mgr_mc(m_var.pMisCnt, CONST_misMsgType_task, 0, CONST_qyCmd_sendTask, tStartTran, uiTranNo, 0, 0, 0, (char*)&req, lenInBytes, NULL, NULL, NULL, &m_var.av.taskInfo.idInfo_starter, 0, NULL, FALSE))  goto  errLabel;

	 iErr = 0;

 errLabel:

	 return iErr;

 }

//
int  confOthers_sendStreamInfo()
{
	int						iErr = -1;

	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	//
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	if (!pFuncs)  return  -1;
	//
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	//



	//
	TASK_INTERACTION_REQ	req;
	int						lenInBytes = 0;
	

	//
	memset(&req, 0, sizeof(req));
	req.uiType = CONST_imCommType_taskInteractionReq;
	req.usOp = CONST_imOp_sendStreamInfo;
	//req.tStartTime_org = m_var.av.taskInfo.tStartTime_org;
	//req.uiTranNo_org = m_var.av.taskInfo.uiTranNo_org;
	//req.uiContentType_org  =  m_var.av.taskInfo.uiContentType_org;
	//
	//  2015/02/17

	//if (index_sharedObj == m_var.av.iIndex_sharedObj_localAv) 
	{
		req.avStream.obj.tranInfo = pProcInfo->av.confLayout.taskInfo.localAv.tranInfo;
		//
		req.iHkStatus = get_iHkStatus();	//  2023/05/04
	}


		//
#ifdef  __DEBUG__
#if  1
		TCHAR  tBuf[128];
		_sntprintf(tBuf, mycountof(tBuf), _T("send. a %d, v %d"), req.avStream.obj.tranInfo.audio.uiTranNo_openAvDev, req.avStream.obj.tranInfo.video.uiTranNo_openAvDev);
		showInfo_open0(0, 0, tBuf);
#endif
#endif
	

	//
	req.idInfo_imGrp_related.ui64Id = pProcInfo->av.confLayout.taskInfo.localAv.idInfo_imGrp_related.ui64Id;
	//	
	lenInBytes = sizeof(req);
	//					
	MACRO_prepareForTran();
	//
	QY_MESSENGER_ID  idInfo_starter = pProcInfo->av.confLayout.taskInfo.localAv.idInfo_starter;
	//	
	if (postMsgTask2Mgr_mc(pMisCnt, CONST_misMsgType_task, 0, CONST_qyCmd_sendTask, tStartTran, uiTranNo, 0, 0, 0, (char*)&req, lenInBytes, NULL, NULL, NULL, &idInfo_starter, 0, NULL, FALSE))  goto  errLabel;

	//
	//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%s"), bRequestToSpeak ? _T("Request to speak") : _T("Request to stop speaking"));

	//
	iErr = 0;
errLabel:
	return  iErr;
}









 //  2015/07/30. not starter.
#if  10
 int  confMgr_requestToSpeak(  HWND  hDlgTalk,  QY_MESSENGER_ID  *  pIdInfo_speaker,  BOOL  bRequestToSpeak  )
{
	int						iErr				=		-1;
	CHelp_getDlgTalkVar		help_getDlgTalkVar;
	DLG_TALK_var		*	pm_var				=		(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pm_var  )  return  -1;	
	DLG_TALK_var		&	m_var				=		*pm_var;
	MC_VAR_isCli			*	pProcInfo			=		QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	TASK_INTERACTION_REQ	req;
	int						lenInBytes			=		0;
	
	//
	if  (  !pIdInfo_speaker  ||  !pIdInfo_speaker->ui64Id  )  return  -1;
	if  (  !m_var.av.taskInfo.bTaskExists
		||  !m_var.av.taskInfo.ucbVideoConference
		||  m_var.av.taskInfo.ucbStarter  )
	{
		return  -1;
	}



	memset(  &req,  0,  sizeof(  req  )  );
	req.uiType  =  CONST_imCommType_taskInteractionReq;
	req.usOp  =  bRequestToSpeak  ?  CONST_imOp_requestToSpeak  :  CONST_imOp_stopSpeaking;
	req.tStartTime_org  =  m_var.av.taskInfo.tStartTime_org;
	req.uiTranNo_org  =  m_var.av.taskInfo.uiTranNo_org;
	//req.uiContentType_org  =  m_var.av.taskInfo.uiContentType_org;
	//
	//  2015/02/17
	//
	req.avStream.idInfo.ui64Id  =  pIdInfo_speaker->ui64Id;
	//
	if  (  m_var.av.taskInfo.ucbVideoConference  )  req.idInfo_imGrp_related.ui64Id  =  m_var.addr.idInfo.ui64Id;
	//	
	lenInBytes  =  sizeof(  req  );			
	//					
	MACRO_prepareForTran(  );						
	//	
	if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendTask,  tStartTran,  uiTranNo,  0,  0,  0,  (  char  *  )&req,  lenInBytes,  NULL,  NULL,  NULL,  &m_var.av.taskInfo.idInfo_starter,  0,  NULL,  FALSE  )  )  goto  errLabel;

	//
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "confMgr: let %I64u %s"  ),  pIdInfo_speaker->ui64Id,  bRequestToSpeak  ?  _T(  "speak"  )  :  _T(  "stop speaking"  )  );

	iErr  =  0;
errLabel:
	return  iErr;
}
#endif


 //  2017/07/07. 下面这个函数可能是不对的
 int  confMgr_permitToSpeak(  HWND  hDlgTalk_mgr,  QY_MESSENGER_ID  *  pIdInfo_speaker,  BOOL  bPermitToSpeak  )
{
	int						iErr				=		-1;
	CHelp_getDlgTalkVar		help_getDlgTalkVar;
	DLG_TALK_var		*	pm_var				=		(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk_mgr  );
	if  (  !pm_var  )  return  -1;	
	DLG_TALK_var		&	m_var				=		*pm_var;
	MC_VAR_isCli			*	pProcInfo			=		QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	TASK_INTERACTION_REQ	req;
	int						lenInBytes			=		0;
	
	//
	if  (  !pIdInfo_speaker  ||  !pIdInfo_speaker->ui64Id  )  return  -1;
	if  (  !m_var.av.taskInfo.bTaskExists
		||  !m_var.av.taskInfo.ucbVideoConference
		)
	{
		return  -1;
	}



	memset(  &req,  0,  sizeof(  req  )  );
	req.uiType  =  CONST_imCommType_taskInteractionReq;
	req.usOp  =  bPermitToSpeak  ?  CONST_imOp_permitToSpeak  :  CONST_imOp_prohibitSpeaking;
	req.tStartTime_org  =  m_var.av.taskInfo.tStartTime_org;
	req.uiTranNo_org  =  m_var.av.taskInfo.uiTranNo_org;
	//req.uiContentType_org  =  m_var.av.taskInfo.uiContentType_org;
	//
	//  2015/02/17
	//
	//req.idInfo_speaker.ui64Id  =  pIdInfo_speaker->ui64Id;
	//
	if  (  m_var.av.taskInfo.ucbVideoConference  )  req.idInfo_imGrp_related.ui64Id  =  m_var.addr.idInfo.ui64Id;
	//	
	lenInBytes  =  sizeof(  req  );			
	//					
	MACRO_prepareForTran(  );						
	//
	QY_MESSENGER_ID  idInfo_dst;
	idInfo_dst.ui64Id  =  pIdInfo_speaker->ui64Id;
	//
	if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendTask,  tStartTran,  uiTranNo,  0,  0,  0,  (  char  *  )&req,  lenInBytes,  NULL,  NULL,  NULL,  &idInfo_dst,  0,  NULL,  FALSE  )  )  goto  errLabel;

	//
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "confCtrl: let %I64u %s"  ),  pIdInfo_speaker->ui64Id,  bPermitToSpeak  ?  _T(  "permit to speak"  )  :  _T(  "prohibit speaking"  )  );

	iErr  =  0;
errLabel:
	return  iErr;
}

//
  //  2017/07/07. 下面这个函数可能是不对的
 int  confCompere_pleaseSpeak(HWND  hDlgTalk_mgr, QY_MESSENGER_ID* pIdInfo_speaker, BOOL  bSpeak)
 {
	 int						iErr = -1;
	 CHelp_getDlgTalkVar		help_getDlgTalkVar;
	 DLG_TALK_var* pm_var = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hDlgTalk_mgr);
	 if (!pm_var)  return  -1;
	 DLG_TALK_var& m_var = *pm_var;
	 MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	 TASK_INTERACTION_REQ	req;
	 int						lenInBytes = 0;

	 //
	 if (!pIdInfo_speaker || !pIdInfo_speaker->ui64Id)  return  -1;
	 if (!m_var.av.taskInfo.bTaskExists
		 || !m_var.av.taskInfo.ucbVideoConference
		 )
	 {
		 return  -1;
	 }



	 memset(&req, 0, sizeof(req));
	 req.uiType = CONST_imCommType_taskInteractionReq;
	 req.usOp = bSpeak ? CONST_imOp_pleaseSpeak : CONST_imOp_pleaseStopSpeaking;
	 req.tStartTime_org = m_var.av.taskInfo.tStartTime_org;
	 req.uiTranNo_org = m_var.av.taskInfo.uiTranNo_org;
	 //req.uiContentType_org  =  m_var.av.taskInfo.uiContentType_org;
	 //
	 //  2015/02/17
	 //
	 //req.idInfo_speaker.ui64Id  =  pIdInfo_speaker->ui64Id;
	 //
	 if (m_var.av.taskInfo.ucbVideoConference)  req.idInfo_imGrp_related.ui64Id = m_var.addr.idInfo.ui64Id;
	 //	
	 lenInBytes = sizeof(req);
	 //					
	 MACRO_prepareForTran();
	 //
	 QY_MESSENGER_ID  idInfo_dst;
	 idInfo_dst.ui64Id = pIdInfo_speaker->ui64Id;
	 //
	 if (postMsgTask2Mgr_mc(m_var.pMisCnt, CONST_misMsgType_task, 0, CONST_qyCmd_sendTask, tStartTran, uiTranNo, 0, 0, 0, (char*)&req, lenInBytes, NULL, NULL, NULL, &idInfo_dst, 0, NULL, FALSE))  goto  errLabel;

	 //
	 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("confCtrl: let %I64u %s"), pIdInfo_speaker->ui64Id, bSpeak ? _T("please speak") : _T("please stop speaking"));

	 iErr = 0;
 errLabel:
	 return  iErr;
 }


 //  2017/08/26
  //  2017/07/07
 __declspec(  dllexport  )  int  requestToControlDesktop_yz(  HWND  hDlgTalk_mgr,  QY_MESSENGER_ID  *  pIdInfo_speaker,  BOOL  bStart  )
{
	int						iErr				=		-1;
	CHelp_getDlgTalkVar		help_getDlgTalkVar;
	DLG_TALK_var		*	pm_var				=		(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk_mgr  );
	if  (  !pm_var  )  return  -1;	
	DLG_TALK_var		&	m_var				=		*pm_var;
	MC_VAR_isCli			*	pProcInfo			=		QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	TASK_INTERACTION_REQ	req;
	int						lenInBytes			=		0;
	
	//
	if  (  !pIdInfo_speaker  ||  !pIdInfo_speaker->ui64Id  )  return  -1;
	if  (  bStart  )  {
		if  (  !m_var.av.taskInfo.bTaskExists
			||  !m_var.av.taskInfo.ucbVideoConference
			)
		{
			return  -1;
		}
	}



	memset(  &req,  0,  sizeof(  req  )  );
	req.uiType  =  CONST_imCommType_taskInteractionReq;
	req.usOp  =  bStart  ?  CONST_imOp_requestToControlDesktop_yz  :  CONST_imOp_stopControlDesktop_yz;
	req.tStartTime_org  =  m_var.av.taskInfo.tStartTime_org;
	req.uiTranNo_org  =  m_var.av.taskInfo.uiTranNo_org;
	//req.uiContentType_org  =  m_var.av.taskInfo.uiContentType_org;
	//
	//  2015/02/17
	//
	//req.idInfo_speaker.ui64Id  =  pIdInfo_speaker->ui64Id;
	//
	if  (  m_var.addr.uiObjType  ==  CONST_objType_imGrp  )  req.idInfo_imGrp_related.ui64Id  =  m_var.addr.idInfo.ui64Id;
	//	
	lenInBytes  =  sizeof(  req  );			
	//					
	MACRO_prepareForTran(  );						
	//
	QY_MESSENGER_ID  idInfo_dst;
	idInfo_dst.ui64Id  =  pIdInfo_speaker->ui64Id;
	//
	if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendTask,  tStartTran,  uiTranNo,  0,  0,  0,  (  char  *  )&req,  lenInBytes,  NULL,  NULL,  NULL,  &idInfo_dst,  0,  NULL,  FALSE  )  )  goto  errLabel;

	//
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "confCtrl: let %I64u %s"  ),  pIdInfo_speaker->ui64Id,  bStart  ?  _T(  "start to control desktop"  )  :  _T(  "stop controlling "  )  );

	iErr  =  0;
errLabel:
	return  iErr;
}




 //
 int  requestToRefreshActiveMems_videoConferenceOthers(  HWND  hDlgTalk  )
{
	int						iErr				=		-1;

	CHelp_getDlgTalkVar		help_getDlgTalkVar;
	DLG_TALK_var		*	pm_var				=		(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pm_var  )  return  -1;
	DLG_TALK_var		&	m_var				=		*pm_var;
	MC_VAR_isCli			*	pProcInfo			=		QY_GET_procInfo_isCli(  ); //(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	TASK_INTERACTION_REQ	req;
	int						lenInBytes			=		0;
		

	memset(  &req,  0,  sizeof(  req  )  );
	req.uiType  =  CONST_imCommType_taskInteractionReq;
	//  req.usOp  =  bRequestToSpeak  ?  CONST_imOp_requestToSpeak  :  CONST_imOp_stopSpeaking;
	req.tStartTime_org  =  m_var.av.taskInfo.tStartTime_org;
	req.uiTranNo_org  =  m_var.av.taskInfo.uiTranNo_org;
	//req.uiContentType_org  =  m_var.av.taskInfo.uiContentType_org;
	req.idInfo_imGrp_related.ui64Id  =  m_var.addr.idInfo.ui64Id;
	//	
	lenInBytes  =  sizeof(  req  );			
	//					
	MACRO_prepareForTran(  );						
	//	
	if  (  postMsgTask2Mgr_mc(  m_var.pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendTask,  tStartTran,  uiTranNo,  0,  0,  0,  (  char  *  )&req,  lenInBytes,  NULL,  NULL,  NULL,  &m_var.av.taskInfo.idInfo_starter,  0,  NULL,  FALSE  )  )  goto  errLabel;

	iErr  =  0;
errLabel:

	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "requestToRefreshActiveMems %s"  ),  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  )  );

	return  iErr;
}












 //  VIDEO_CONFERNECE_LAYOUT

 int  sendConfLayout(unsigned char ucbResp , unsigned  short  usLayoutType, unsigned  short  usOp, ConfLayoutParam* pParam, QY_MESSENGER_ID  idInfo_imGrp_related, QY_MESSENGER_ID  idInfo_requester, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint)

{
	int								iErr		=		-1;
#if 0
	CHelp_getDlgTalkVar				help_getDlgTalkVar;
	DLG_TALK_var				*	pm_var		=		(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pm_var  )  return  -1;
	DLG_TALK_var				&	m_var		=		*pm_var;
#endif
	MC_VAR_isCli					*	pProcInfo	=		QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	CONF_LAYOUT			layout;
	int								i;
	int								lenInBytes;

	if  (  !hint  )  hint  =  _T(  ""  );


	//
	QY_MESSENGER_ID  *  pIdInfo_to  =  &idInfo_to;
	if  (  !pIdInfo_to  ||  !pIdInfo_to->ui64Id  )  return  -1;
	
	//
	//if  (  !m_var.av.taskInfo.bTaskExists  )  return  -1;
	//
	//if  (  !m_var.av.taskInfo.ucbStarter  )  return  -1;

	//
	memset(  &layout,  0,  sizeof(  layout  )  );
	layout.uiType  =  CONST_imCommType_confLayout;
	//if  (  m_var.av.taskInfo.ucbVideoConference  )  layout.idInfo_imGrp_related.ui64Id  =  m_var.addr.idInfo.ui64Id;
	layout.idInfo_imGrp_related.ui64Id = idInfo_imGrp_related.ui64Id;

	layout.ucbResp = ucbResp;

	layout.usLayoutType  =  usLayoutType;
	//
	layout.usOp = usOp;
	//
	if (pParam)  layout.confLayoutParam = *pParam;
	
	//
	lenInBytes  =  sizeof(  layout  );			
	//					
	MACRO_prepareForTran(  );						
	//	
	if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendTask,  tStartTran,  uiTranNo,  0,  0,  0,  (  char  *  )&layout,  lenInBytes,  NULL,  NULL,  NULL,  pIdInfo_to,  0,  NULL,  FALSE  )  )  goto  errLabel;

	iErr  =  0;
errLabel:

	TCHAR  tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. sendVideoConfLayout to %I64u. %s"  ),  hint,  pIdInfo_to->ui64Id,  iErr  ?  _T(  "failed"  )  :  _T(  ""  )  );
	showInfo_open0(  0,  0,  tBuf  );


	return  iErr;
}

 //
 __declspec(dllexport)  int  sendConfNvrInfo(NvrInfo * pNvrInfo, unsigned  char  ucbResp,  QY_MESSENGER_ID idInfo_imGrp_related,  QY_MESSENGER_ID idInfo_requester, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint)
 {
	 int								iErr = -1;
	 MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	 ConfNvrInfo						req;
	 int								i;
	 int								lenInBytes;

	 if (!hint)  hint = _T("");

	 MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));


	 //
	 QY_MESSENGER_ID* pIdInfo_to = &idInfo_to;
	 if (!pIdInfo_to || !pIdInfo_to->ui64Id)  return  -1;

	 //
	 
	 //
	 memset(&req, 0, sizeof(req));
	 req.uiType = CONST_imCommType_confNvrInfo;
	 req.ucbResp = ucbResp;
	 req.idInfo_imGrp_related.ui64Id = idInfo_imGrp_related.ui64Id;

	 if (pNvrInfo)  req.nvrInfo = *pNvrInfo;

	 req.idInfo_requester = idInfo_requester;

	 //
	 lenInBytes = sizeof(req);
	 //					
	 MACRO_prepareForTran();
	 //	
	 if (postMsgTask2Mgr_mc(pMisCnt, CONST_misMsgType_task, 0, CONST_qyCmd_sendTask, tStartTran, uiTranNo, 0, 0, 0, (char*)&req, lenInBytes, NULL, NULL, NULL, pIdInfo_to, 0, NULL, FALSE))  goto  errLabel;

	 iErr = 0;
 errLabel:

	 TCHAR  tBuf[128];
	 _sntprintf(tBuf, mycountof(tBuf), _T("%s. sendConfNvrInfo to %I64u. %s"), hint, pIdInfo_to->ui64Id, iErr ? _T("failed") : _T(""));
	 showInfo_open0(0, 0, tBuf);


	 return  iErr;
 }





 //
 int  sendConfCtrlState( HWND  hDlgTalk_mgr, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint)
 {
	 int								iErr = -1;
	 CHelp_getDlgTalkVar				help_getDlgTalkVar;
	 DLG_TALK_var* pm_var = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hDlgTalk_mgr);
	 if (!pm_var)  return  -1;
	 DLG_TALK_var& m_var = *pm_var;
	 MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	 CONF_ctrl_state			req;
	 int								i;
	 int								lenInBytes;

	 if (!hint)  hint = _T("");


	 //
	 QY_MESSENGER_ID* pIdInfo_to = &idInfo_to;
	 if (!pIdInfo_to || !pIdInfo_to->ui64Id)  return  -1;

	 //
	 if (!m_var.av.taskInfo.bTaskExists)  return  -1;
	 if (!m_var.av.taskInfo.ucbStarter)  return  -1;

	 //
	 memset(&req, 0, sizeof(req));
	 req.uiType = CONST_imCommType_confCtrlState;
	 if (m_var.av.taskInfo.ucbVideoConference)  req.idInfo_imGrp_related.ui64Id = m_var.addr.idInfo.ui64Id;

	 if (0) {
		 req.idInfo_compere.ui64Id = m_var.av.taskInfo.unused_idInfo_compere.ui64Id;
	 }

	 //
	 lenInBytes = sizeof(req);
	 //					
	 MACRO_prepareForTran();
	 //	
	 if (postMsgTask2Mgr_mc(m_var.pMisCnt, CONST_misMsgType_task, 0, CONST_qyCmd_sendTask, tStartTran, uiTranNo, 0, 0, 0, (char*)&req, lenInBytes, NULL, NULL, NULL, pIdInfo_to, 0, NULL, FALSE))  goto  errLabel;

	 iErr = 0;
 errLabel:

	 TCHAR  tBuf[128];
	 _sntprintf(tBuf, mycountof(tBuf), _T("%s. sendConfCtrlState to %I64u. %s"), hint, pIdInfo_to->ui64Id, iErr ? _T("failed") : _T(""));
	 showInfo_open0(0, 0, tBuf);


	 return  iErr;
 }


 //
 int clearSpeakState(LPCTSTR  hint  )
 {
	 CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	 if (!hint)  hint = _T("");
	 TCHAR  tBuf[128]	=	_T("");

	 //
	 memset(&pProcInfo->av.speakState, 0, sizeof(pProcInfo->av.speakState));

	 //
	 showInfo_open0(0, hint, _T("clearSpeakState"));

	 //
	 return  0;
 }




 //
 int  dlgTalk_requestToSpeak(  HWND  hDlgTalk_mgr,  BOOL  bEnable,  bool  bSaveState  )
{
	int  iErr  =  -1;

	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	DLG_TALK_var	*	pMgrVar	=	(  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  hDlgTalk_mgr  );
	if  (  !pMgrVar  )  return  -1;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return  -1;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  return  -1;
	TCHAR  tBuf[128];

	QY_MC* pQyMc = pMgrVar->pQyMc;// QY_GET_GBUF();
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();

	//
	if  (  !pMgrVar->av.taskInfo.bTaskExists  )  return  -1;
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  pMgrVar->av.taskInfo.iIndex_taskInfo  );
	if  (  !pTaskInfo  )  goto  errLabel;
	QMC_taskData_conf* pTc; pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;

	//  2017/07/11
	if  (  bEnable  )  {
		if  (  pMgrVar->av.taskInfo.bTaskExists
			  &&  pMgrVar->addr.uiObjType  ==  CONST_objType_imGrp
			  &&  pMgrVar->av.taskInfo.ucbConfCtrl
			  &&  !pMgrVar->av.taskInfo.ucbStarter
			  &&  !pShadowMgr->av.ucbMeConfMgr
			  )
		  {
			  if  (  !pMgrVar->av.taskInfo.confMem_confCtrl.ucbPermitToSpeak  )  {
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotSpeak  )  );
				  showNotification(  0,  0,  0,  0,  0,  0,  tBuf  );
				  goto  errLabel;
			  }
		  }

		//
		if  (  pMgrVar->av.taskInfo.ucbVideoConference
			&&  !pMgrVar->av.taskInfo.ucbStarter  )
		{
			//
			if  (  isActiveMemsFull(  pMgrVar->av.taskInfo.iTaskId,true  )  )  {
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "already too many speakers. you cant speak now"  )  );
				//_sntprintf(tBuf, mycountof(tBuf), _T("现在发言人已经满了，你现在不能发言！"));
				showNotification(  0,  0,  0,  0,  0,  0,  tBuf  );				  
				//goto  errLabel;
			}
		}		
	}		

	//  2015/12/08
#ifdef  __DEBUG__
		if  (  bEnable  )  showInfo_open0(  0,  0,  _T(  "requestToSpeak"  )  );
#endif

	//
	//  BOOL							bEnableState	=	m_var.canSpeak;
		BOOL								bEnableState; bEnableState = dlgTalk_canSpeak(hDlgTalk_mgr);


	//  2010/12/19
	//pMgrVar->av.taskInfo.bEnableToSpeak  =  bEnable;
	pTc->ucbNotSendData  =  !bEnable;

	//
	if (bSaveState) {
		if (bObjTypeGrp(pMgrVar->addr.uiObjType)) {
			pProcInfo->av.speakState.bEnableToSpeak = bEnable;
			pProcInfo->av.speakState.idInfo_grp.ui64Id = pMgrVar->addr.idInfo.ui64Id;
			//
		}
	}

	
	//
	if  (  pMgrVar->av.taskInfo.ucbStarter  )  {
		pProcInfo->confStarter_requestToSpeak(  hDlgTalk_mgr,  &pMgrVar->pMisCnt->idInfo,  &pMgrVar->av.taskInfo.local_avStream,  NULL,  bEnable  );
		if  (  (  bEnable  &&  !bEnableState  )  ||  (  !bEnable  &&  bEnableState  )  )  {
			TCHAR  *  hint  =  (TCHAR*)(bEnable  ?  _T(  "requestToSpeak true"  )  :  _T(  "requestToSpeak false"  ));
			pProcInfo->sendConfKey(  hDlgTalk_mgr,  pMgrVar->addr.idInfo,  hint  );
		}
		}	
	else  {
		  //  if  (  (  bEnable  &&  !bEnableState  )  ||  (  !bEnable  &&  bEnableState  )  )  
		  {
			  confOthers_requestToSpeak(  hDlgTalk_mgr,  pMgrVar->av.iIndex_sharedObj_localAv,  mynull,  bEnable  );
		  }
	}


	//
	iErr  =  0;
errLabel:

	return  iErr;
}

 int  dlgTalk_requestToOp(HWND  hDlgTalk_mgr, int op, int  bSaveState)
 {
	 int  iErr = -1;

	 CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	 DLG_TALK_var* pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(hDlgTalk_mgr);
	 if (!pMgrVar)  return  -1;

	 iErr = confOthers_requestToOp(hDlgTalk_mgr, pMgrVar->av.iIndex_sharedObj_localAv, mynull, op);

	 return iErr;
 }




