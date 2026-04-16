// DlgStatusCli.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qyMc.h"
#include	"myresource.h"
#include	"DlgStatusCli.h"
#include	"qyCusResTemp.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcDynBmp.h"

#include	"myDb.h"
#include	"iscliHelpPublic.h"
#include	"qmcCommFunc_isCli.h"
#include	"qmcTaskInfo.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


 int  tmp_displayQ(  GENERIC_Q	*	pQ,  int  &cnt,  STATUS_qList  *  pCur,  CListCtrl  *  pListCtrl  )
{
	TCHAR	tBuf[256];
	int		index;
	BOOL	bInsert			=	FALSE;

	if  (  !pQ  )  return  -1;
	if  (  cnt  >=  mycountof(  pCur->mems  )  )  return  -1;

	if  (  !isQEmpty(  pQ  )  )  
	{

		if  (  pCur->usCnt  <=  cnt  ){
			 bInsert  =  TRUE;		 
		}

		index  =  0;	
		if  (  bInsert  ||  pCur->mems[cnt].pQ  !=  pQ  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pQ->cfg.name  );
			if  (  bInsert  )pListCtrl->InsertItem(  cnt,  tBuf  );
			else  pListCtrl->SetItemText(  cnt,  index,  tBuf  );
			pCur->mems[cnt].pQ  =  pQ; 
		}
		
		 index  ++  ;	
#if  0
		 tBuf[0]  =  0;
		 if  (  bInsert  &&  tBuf[0]  !=  0  ) pListCtrl->SetItemText(  cnt,  index,  tBuf  );
#endif

		 index  ++  ;
		 if  (  bInsert  ||  pQ->cfg.uiMaxQNodes  !=  pCur->mems[cnt].uiMaxQNodes  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pQ->cfg.uiMaxQNodes  );
			 pListCtrl->SetItemText(  cnt,  index,  tBuf  );
			 pCur->mems[cnt].uiMaxQNodes  =  pQ->cfg.uiMaxQNodes;
		 }

		 index  ++  ;
		 if  (  bInsert  ||  pQ->uiQNodes  !=  pCur->mems[cnt].iNodes0  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pQ->uiQNodes  );
			 pListCtrl->SetItemText(  cnt,  index,  tBuf  );
			 pCur->mems[cnt].iNodes0  =  pQ->uiQNodes;
			 pCur->mems[cnt].iNodes1  =  0;
		 }
		 
		 cnt  ++  ;
	 }

	return  0;
 }




 int  tmp_displayQ2(  QY_Q2  *  pQ2,  LPCTSTR  desc,  int  &cnt,  STATUS_qList  *  pCur,  CListCtrl  *  pListCtrl  )
{
	TCHAR	tBuf[256];
	int		index;
	BOOL	bInsert	=  FALSE;

	if  (  !pQ2  )  return  -1;
	if  (  cnt  >=  mycountof(  pCur->mems  )  )  return  -1;

	//
	if  (  !desc  )  desc  =  _T(  ""  );

	//
	if  (  !isQ2Empty(  pQ2  )  )  
	{
		if  (  pCur->usCnt  <=  cnt  ) {
			bInsert  =  TRUE;
		}

		index  =  0;
		if  (   bInsert  ||  pCur->mems[cnt].pQ  !=  pQ2  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pQ2->cfg.name  );
			if  (  bInsert  )  pListCtrl->InsertItem(  cnt,  tBuf  );	
			else  pListCtrl->SetItemText(  cnt,  index,  tBuf  );
			pCur->mems[cnt].pQ  =  pQ2;			
		}


		index  ++  ;
#if  0
		tBuf[0]  =  0;
		if  (  bInsert  &&  tBuf[0]  !=  0  )	pListCtrl->SetItemText(  cnt,  index,  tBuf  );
#endif

		index  ++  ;
		if  (  bInsert  ||  pQ2->cfg.uiMaxQNodes  !=  pCur->mems[cnt].uiMaxQNodes  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pQ2->cfg.uiMaxQNodes  );
			 if  (  desc[0]  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  desc  );
			 pListCtrl->SetItemText(  cnt,  index,  tBuf  );
			 pCur->mems[cnt].uiMaxQNodes  =  pQ2->cfg.uiMaxQNodes;
		}

		index  ++  ;	
		int  iNodes0,iNodes1;
#if  0
		iNodes0		=	getQ2Nodes_toGetMsg(  pQ2  );
		iNodes1		=	getQ2Nodes_toPostMsg(  pQ2  );
#endif
		iNodes0		=	pQ2->qs[0].uiQNodes;
		iNodes1		=	pQ2->qs[1].uiQNodes;
		if  (  bInsert  ||  pCur->mems[cnt].iNodes0  !=  iNodes0     ||  pCur->mems[cnt].iNodes1  !=  iNodes1  )  {
			//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d,%d"  ),  getQ2Nodes_toGetMsg(  pQ2  ),  getQ2Nodes_toPostMsg(  pQ2  )  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d,%d"  ),  iNodes0,  iNodes1  );
			pListCtrl->SetItemText(  cnt,  index,  tBuf  );
			pCur->mems[cnt].iNodes0  =  iNodes0;
			pCur->mems[cnt].iNodes1  =  iNodes1;
		}
		 
		cnt  ++  ;
	}

	return  0;
}

  //
  int  tmp_displayQ2(  QY_Q2  *  pQ2,  int  &cnt,  STATUS_qList  *  pCur,  CListCtrl  *  pListCtrl  )
  {
	  return  tmp_displayQ2(  pQ2,  NULL,  cnt,  pCur,  pListCtrl  );
  }


  //
  int  tmpHandler_displayRealTimeTasks_q(  QY_MC  *  pQyMc,  void  *  p0,  void  *  p1,  TASK_common * taskElem  )
{
	//  p0
	COMMON_PARAM  *  pCommonParam1	=	(  COMMON_PARAM  *  )p1;

	int  *  piCnt  =  (  int  *  )pCommonParam1->p0;
	STATUS_qList	*	pStatus_qList	=	(  STATUS_qList  *  )pCommonParam1->p1;
	CListCtrl  *  pListCtrl	=	(  CListCtrl  *  )pCommonParam1->p2;  
	  
	//
	//CCtxQyMc *pQyMc=g_pQyMc;
	CCtxQmc * pProcInfo=(CCtxQmc*)pQyMc->get_pProcInfo();
	QMC_TASK_INFO * pTaskInfo=(QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, taskElem->m_index_taskInfo  );
	if(pTaskInfo==NULL  )  return  -1;
	MIS_MSGU  *  pMsgElem=&pTaskInfo->var.pTaskData->msgU;

	//
	TCHAR		tBuf[512]							=	_T(  ""  );
	//int			index;
	int			i									=	0;
	char		timeBuf[CONST_qyTimeLen  +  1]		=	"";
	char		displayBuf[255  +  1]				=	"";
	int			j;
	//QY_MC	*	pQyMc								=	QY_GET_GBUF(  );

	if  (  !pListCtrl  ||  !piCnt  ||  !pMsgElem  )  return  -1;

	//index  =  *piCnt;


	if  (  pMsgElem->uiType  ==  CONST_misMsgType_task  )  {
		IM_CONTENTU		*	pContent		=	(  IM_CONTENTU  *  )pMsgElem->task.data.buf;
		MIS_CNT			*	pMisCnt			=  (  MIS_CNT  *  )pMsgElem->task.pMisCnt;
		MC_VAR_isCli		*	pProcInfo			=	NULL;
		if  (  pMisCnt  )  pProcInfo		=  QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;

		switch  (  pContent->uiType  )  {
				case  CONST_imCommType_transferAvInfo:  
				case  CONST_imCommType_transferAvReplyInfo:  {
  					  AV_TRAN_INFO  *  pAvTran  =  NULL;
					  PROC_TASK_AV  *  pTask  =  NULL;
					  QY_SHARED_OBJ	*	pSharedObj		=	NULL;		

					  TASK_transferAv  *  task =(TASK_transferAv  *  )taskElem;

					  if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
						  //
						  pAvTran  =  &pContent->transferAvInfo.ass.tranInfo;
						  //
						  pTask  =  &task->myTask;//get_transferAvInfo_pTask(  &pContent->transferAvInfo,  _T(  ""  )  );	//  &pTransferAvTask->myTask;
						  if  (  !pTask  )  break;
						  }
					  else  {
						    pAvTran  =  &pContent->transferAvReplyInfo.tranInfo;		
							//
							//pTask  =  &pContent->transferAvReplyInfo.myTask;							
							pTask  =  &task->myTask;//get_transferAvReplyInfo_pTask(  &pContent->transferAvReplyInfo,  _T(  ""  )  );
							if  (  !pTask  )  break;
					  }
					  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pTask->iIndex_sharedObj  );


					  for  (  j  =  0;  j  <  pTask->usCntLimit_transforms;  j  ++  )  {
						   QY_TRANSFORM  *  pTransform  =  &pTask->pTransforms[j];

						   //if  (  pTransform->audio.bRunning  )  							   
						   {
								   tmp_displayQ2(  &pTransform->audio.q2,  *piCnt,  pStatus_qList,  pListCtrl  );
						   }
						   //if  (  pTransform->v_preTransThread.bRunning  )  							   
						   {
								   tmp_displayQ2(  &pTransform->v_preTransThread.q2,  *piCnt,  pStatus_qList,  pListCtrl  );	//  2012/09/07
						   }
						   //if  (  pTransform->video.bRunning  )  							   
						   {
								   tmp_displayQ2(  &pTransform->video.q2,  *piCnt,  pStatus_qList,  pListCtrl  );
						   }
					  }

					  //  2011/12/08
					  for  (  j  =  0;  j  <  pTask->usCntLimit_dispatchs;  j  ++  )  {
						   QIS_DISPATCH  *  pDispatch  =  &pTask->pDispatchs[j];

						   //if  (  pDispatch->audio.bRunning  )  							
						   {
								   tmp_displayQ2(  &pDispatch->audio.q2,  *piCnt,  pStatus_qList,  pListCtrl  );
						   }
						   //if  (  pDispatch->video.bRunning  )  							   
						   {
								   tmp_displayQ2(  &pDispatch->video.q2,  *piCnt,  pStatus_qList,  pListCtrl  );
						   }
					  }
									
					  if  (  pSharedObj  )  {
						  CAP_procInfo_audioU	*	pCapAudio  =  getCapAudioBySth(  pProcInfo,  pSharedObj->iIndex_capAudio,  0  );
						  if  (  pCapAudio  )  {
							  tmp_displayQ2(  &pCapAudio->common.thread.q2,  *piCnt,  pStatus_qList,  pListCtrl  );
						  }
						  CAP_procInfo_bmpU	*	pCapBmp  =  getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
						  if  (  pCapBmp  )  {
							  tmp_displayQ2(  &pCapBmp->common.vppThread.q2,  *piCnt,  pStatus_qList,  pListCtrl  );	//  2011/12/05
							  tmp_displayQ2(  &pCapBmp->common.thread.q2,  *piCnt,  pStatus_qList,  pListCtrl  );
							  tmp_displayQ2(  &pCapBmp->common.postThread.q2,  *piCnt,  pStatus_qList,  pListCtrl  );
						  }
					  }

					  tmp_displayQ2(  pTask->mixer.pOutputQ2,  *piCnt,  pStatus_qList,  pListCtrl  );
					  tmp_displayQ2(  pTask->photomosaic.pOutputQ2,  *piCnt,  pStatus_qList,  pListCtrl  );


					  }
					  break;
				default:
						break;
		}

	}

	return  0;
}


#include	"dlgtalkProc.h"

//  2014/12/23
  int  tmpHandler_displayTalkers_q(  void  *  p0,  void  *  p1,  MIS_MSGU  *  pMsgElem  )
{
	//  p0
	COMMON_PARAM  *  pCommonParam1	=	(  COMMON_PARAM  *  )p1;

	int  *  piCnt  =  (  int  *  )pCommonParam1->p0;
	STATUS_qList	*	pStatus_qList	=	(  STATUS_qList  *  )pCommonParam1->p1;
	CListCtrl  *  pListCtrl	=	(  CListCtrl  *  )pCommonParam1->p2;  
	  
	TCHAR		tBuf[512]							=	_T(  ""  );
	int			i									=	0;
	char		timeBuf[CONST_qyTimeLen  +  1]		=	"";
	char		displayBuf[255  +  1]				=	"";
	int			j;
	QY_MC	*	pQyMc								=	QY_GET_GBUF(  );

	if  (  !pListCtrl  ||  !piCnt  ||  !pMsgElem  )  return  -1;

			 
	if  (  pMsgElem->uiType  ==  CONST_misMsgType_talkingFriend_qmc  )  {
		 HWND			hDlgTalk  =  pMsgElem->talkingFriend_qmc.hWnd;
		 //  CDlgTalk	*	pDlg	=	(  CDlgTalk  *  )CWnd::FromHandle(  pMsg->talkingFriend_qmc.hWnd  );
		 CHelp_getDlgTalkVar	help_getDlgTalkVar;
		 DLG_talk_var  *  pDlgTalkVar  =  (  DLG_talk_var  *  )help_getDlgTalkVar.getVar(  hDlgTalk  );
		 if  (  !pDlgTalkVar  )  goto  errLabel;
		 DLG_talk_var  &  m_var  =  *pDlgTalkVar;
		 if  (  !isTalkerShadowMgr(  m_var.addr  )  )  goto  errLabel;

		 //  printQ_mis(  m_var.m_pProcessQ,  FALSE  );
		 tmp_displayQ(  m_var.m_pProcessQ,  *piCnt,  pStatus_qList,  pListCtrl  );
		 
	
	}
errLabel:

	return  0;
}



  int  listStatus_qList(  CDlgStatusCli  *  pDlg  )
  {
	  int		iErr  =  -1;
	  DLG_statusCli_var  &  m_var  =  pDlg->m_var;
	  
	  QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli					*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	CListCtrl						*	pListCtrl				=			(  CListCtrl  *  )pDlg->GetDlgItem(  IDC_LIST_deamonStatus  );
	int									cnt						=			0;
	MIS_CNT							*	pMisCnt					=			(  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );
	int									i = 0;


	  	//
	 int  j;
	 for  (  j  =  0;  j  <  mycountof(  pMisCnt->channels  );  j  ++  )  {
		  MIS_CHANNEL	*	pChannel  =  &pMisCnt->channels[j];

		  tmp_displayQ(  &pChannel->inCacheQ,  cnt,  &m_var.u.qList,  pListCtrl  );
		  tmp_displayQ2(  &pChannel->toSendQ2,  cnt,  &m_var.u.qList,  pListCtrl  );
		  tmp_displayQ2(  &pChannel->outputQ2,  cnt,  &m_var.u.qList,  pListCtrl  );
	 }

	 tmp_displayQ(  &pProcInfo->mgrQ,  cnt,  &m_var.u.qList,  pListCtrl  );	 
	 tmp_displayQ(  &pProcInfo->robotQ,  cnt,  &m_var.u.qList,  pListCtrl  );
	 tmp_displayQ(  &pProcInfo->displayQ,  cnt,  &m_var.u.qList,  pListCtrl  );
	 tmp_displayQ(  &pProcInfo->workQ,  cnt,  &m_var.u.qList,  pListCtrl  );
	 tmp_displayQ(  &pProcInfo->schedulerQ,  cnt,  &m_var.u.qList,  pListCtrl  );
	 tmp_displayQ2(  &pProcInfo->mediaQ2,  cnt,  &m_var.u.qList,  pListCtrl  );
	 tmp_displayQ2(  &pProcInfo->realTimeMediaQ2,  cnt,  &m_var.u.qList,  pListCtrl  );

	 COMMON_PARAM	commonParam;
	 MACRO_makeCommonParam3(  &cnt,  &m_var.u.qList,  pListCtrl,  commonParam  );
	 pProcInfo->processQ_media.qTraverse(  tmpHandler_displayRealTimeTasks_q,  NULL,  &commonParam  );

	 //
#ifndef  __DEBUG__
	 //tmp_displayQ(  &pProcInfo->processQ_media.m_q,  cnt,  &m_var.u.qList,  pListCtrl  );
#endif
	 TCHAR	tBuf[256];
	 {
		 int  index;  
		 int	id  =  5;

		 BOOL	bInsert  =  FALSE;
		 if  (  m_var.u.qList.usCnt  <=  cnt  ) {
			 bInsert  =  TRUE;
		 }

		 index  =  0;
		 if  (   bInsert  ||  m_var.u.qList.mems[cnt].pQ  !=  (  void  *  )id  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "nQNodes_processQ_task"  )  );

			if  (  bInsert  )  pListCtrl->InsertItem(  cnt,  tBuf  );	
			else  pListCtrl->SetItemText(  cnt,  index,  tBuf  );
			m_var.u.qList.mems[cnt].pQ  =  (  void  *  )id;			
		}
		index  ++  ;
		index  ++  ;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pProcInfo->processQ_media.m_var.uiQNodes  );
		pListCtrl->SetItemText(  cnt,  index,  tBuf  );
		index  ++  ;
		time_t	t;	time(  &t  );
		char	timeBuf[128];
		getCurTime(  timeBuf  );
		char	displayBuf[128];
		qyDisplayTime(  timeBuf,  displayBuf,  sizeof(  displayBuf  )  );
		pListCtrl->SetItemText(  cnt,  index,  CString(  displayBuf  )  );
		cnt  ++  ;
	 }

	 //
	 tmp_displayQ(  &pMisCnt->talkingFriendQ,  cnt,  &m_var.u.qList,  pListCtrl  );
	 //
	 MACRO_makeCommonParam3(  &cnt,  &m_var.u.qList,  pListCtrl,  commonParam  );	 
	 qTraverse(  &pMisCnt->talkingFriendQ,  (  PF_commonHandler  )tmpHandler_displayTalkers_q,  NULL,  &commonParam  );

	 //
	 tmp_displayQ(  &pMisCnt->recentFriendQ,  cnt,  &m_var.u.qList,  pListCtrl  );	//  2014/02/11

	 //
	 for  (  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
		  QY_PLAYER				*	pPlayer	=	&pProcInfo->av.pPlayers[i];
		  //
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pPlayer->idInfo_recorder.ui64Id  );
		  //
		  tmp_displayQ2(  &pPlayer->audio.q2,  tBuf,  cnt,  &m_var.u.qList,  pListCtrl  );
		  tmp_displayQ2(  &pPlayer->video.q2,  tBuf,  cnt,  &m_var.u.qList,  pListCtrl  );
		  tmp_displayQ2(  &pPlayer->video.displayQ2,  tBuf,  cnt,  &m_var.u.qList,  pListCtrl  );		  
	 }

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "local"  )  );
	 tmp_displayQ2(  &pProcInfo->av.localAv.player.audio.q2,  tBuf,  cnt,  &m_var.u.qList,  pListCtrl  );
	 tmp_displayQ2(  &pProcInfo->av.localAv.player.video.q2,  tBuf,  cnt,  &m_var.u.qList,  pListCtrl  );
	 tmp_displayQ2(  &pProcInfo->av.localAv.player.video.displayQ2,  tBuf,  cnt,  &m_var.u.qList,  pListCtrl  );

	 //  2012/05/07
	 for  (  i  =  0;  i  <  pProcInfo->gps.usCnt_players;  i  ++  )  {
		  QY_PLAYER_gps  *  pPlayer_gps  =  &pProcInfo->gps.pPlayers[i];
		  tmp_displayQ2(  &pPlayer_gps->q2,  cnt,  &m_var.u.qList,  pListCtrl  );
	 }

	 //  2012/03/25
	 {
		 int  index;  TCHAR	tBuf[256];
		 int	id  =  1;

		 BOOL	bInsert  =  FALSE;
		 if  (  m_var.u.qList.usCnt  <=  cnt  ) {
			 bInsert  =  TRUE;
		 }

		 index  =  0;
		 if  (   bInsert  ||  m_var.u.qList.mems[cnt].pQ  !=  (  void  *  )id  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "nThreads_dec"  )  );

			if  (  bInsert  )  pListCtrl->InsertItem(  cnt,  tBuf  );	
			else  pListCtrl->SetItemText(  cnt,  index,  tBuf  );
			m_var.u.qList.mems[cnt].pQ  =  (  void  *  )id;			
		}
		index  ++  ;
		index  ++  ;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pProcInfo->status.nThreads_dec  );
		pListCtrl->SetItemText(  cnt,  index,  tBuf  );
		index  ++  ;
		time_t	t;	time(  &t  );
		char	timeBuf[128];
		getCurTime(  timeBuf  );
		char	displayBuf[128];
		qyDisplayTime(  timeBuf,  displayBuf,  sizeof(  displayBuf  )  );
		pListCtrl->SetItemText(  cnt,  index,  CString(  displayBuf  )  );
		cnt  ++  ;
	 }

	 //  2013/08/27
	 {
		 int  index;  TCHAR	tBuf[256];
		 int	id  =  2;

		 BOOL	bInsert  =  FALSE;
		 if  (  m_var.u.qList.usCnt  <=  cnt  ) {
			 bInsert  =  TRUE;
		 }

		 index  =  0;
		 if  (   bInsert  ||  m_var.u.qList.mems[cnt].pQ  !=  (  void  *  )id  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "nThreads_dispatch"  )  );

			if  (  bInsert  )  pListCtrl->InsertItem(  cnt,  tBuf  );	
			else  pListCtrl->SetItemText(  cnt,  index,  tBuf  );
			m_var.u.qList.mems[cnt].pQ  =  (  void  *  )id;			
		}
		index  ++  ;
		index  ++  ;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pProcInfo->status.nThreads_dispatch  );
		pListCtrl->SetItemText(  cnt,  index,  tBuf  );
		index  ++  ;
		time_t	t;	time(  &t  );
		char	timeBuf[128];
		getCurTime(  timeBuf  );
		char	displayBuf[128];
		qyDisplayTime(  timeBuf,  displayBuf,  sizeof(  displayBuf  )  );
		pListCtrl->SetItemText(  cnt,  index,  CString(  displayBuf  )  );
		cnt  ++  ;
	 }

	 //  2012/03/30
	 {
		 int  index;  TCHAR	tBuf[256];
		 int	id  =  4;

		 BOOL	bInsert  =  FALSE;
		 if  (  m_var.u.qList.usCnt  <=  cnt  ) {
			 bInsert  =  TRUE;
		 }

		 index  =  0;
		 if  (   bInsert  ||  m_var.u.qList.mems[cnt].pQ  !=  (  void  *  )id  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "nThreads_player"  )  );

			if  (  bInsert  )  pListCtrl->InsertItem(  cnt,  tBuf  );	
			else  pListCtrl->SetItemText(  cnt,  index,  tBuf  );
			m_var.u.qList.mems[cnt].pQ  =  (  void  *  )id;			
		}
		index  ++  ;
		index  ++  ;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pProcInfo->status.nThreads_player  );
		pListCtrl->SetItemText(  cnt,  index,  tBuf  );
		index  ++  ;
		time_t	t;	time(  &t  );
		char	timeBuf[128];
		getCurTime(  timeBuf  );
		char	displayBuf[128];
		qyDisplayTime(  timeBuf,  displayBuf,  sizeof(  displayBuf  )  );
		pListCtrl->SetItemText(  cnt,  index,  CString(  displayBuf  )  );
		cnt  ++  ;
	 }


	 //  2015/05/20
	 {
		 int  index;  TCHAR	tBuf[256];
		 int	id  =  5;

		 BOOL	bInsert  =  FALSE;
		 if  (  m_var.u.qList.usCnt  <=  cnt  ) {
			 bInsert  =  TRUE;
		 }

		 index  =  0;
		 if  (   bInsert  ||  m_var.u.qList.mems[cnt].pQ  !=  (  void  *  )id  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "nThreads_aTrans"  )  );

			if  (  bInsert  )  pListCtrl->InsertItem(  cnt,  tBuf  );	
			else  pListCtrl->SetItemText(  cnt,  index,  tBuf  );
			m_var.u.qList.mems[cnt].pQ  =  (  void  *  )id;			
		}
		index  ++  ;
		index  ++  ;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pProcInfo->status.nThreads_aTrans  );
		pListCtrl->SetItemText(  cnt,  index,  tBuf  );
		index  ++  ;
		time_t	t;	time(  &t  );
		char	timeBuf[128];
		getCurTime(  timeBuf  );
		char	displayBuf[128];
		qyDisplayTime(  timeBuf,  displayBuf,  sizeof(  displayBuf  )  );
		pListCtrl->SetItemText(  cnt,  index,  CString(  displayBuf  )  );
		cnt  ++  ;
	 }

	 //  2015/05/20
	 {
		 int  index;  TCHAR	tBuf[256];
		 int	id  =  6;

		 BOOL	bInsert  =  FALSE;
		 if  (  m_var.u.qList.usCnt  <=  cnt  ) {
			 bInsert  =  TRUE;
		 }

		 index  =  0;
		 if  (   bInsert  ||  m_var.u.qList.mems[cnt].pQ  !=  (  void  *  )id  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "nThreads_vTrans"  )  );

			if  (  bInsert  )  pListCtrl->InsertItem(  cnt,  tBuf  );	
			else  pListCtrl->SetItemText(  cnt,  index,  tBuf  );
			m_var.u.qList.mems[cnt].pQ  =  (  void  *  )id;			
		}
		index  ++  ;
		index  ++  ;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pProcInfo->status.nThreads_vTrans  );
		pListCtrl->SetItemText(  cnt,  index,  tBuf  );
		index  ++  ;
		time_t	t;	time(  &t  );
		char	timeBuf[128];
		getCurTime(  timeBuf  );
		char	displayBuf[128];
		qyDisplayTime(  timeBuf,  displayBuf,  sizeof(  displayBuf  )  );
		pListCtrl->SetItemText(  cnt,  index,  CString(  displayBuf  )  );
		cnt  ++  ;
	 }

	 //  2016/03/15
	 {
		 int  index;  TCHAR	tBuf[256];
		 int	id  =  6;

		 BOOL	bInsert  =  FALSE;
		 if  (  m_var.u.qList.usCnt  <=  cnt  ) {
			 bInsert  =  TRUE;
		 }

		 index  =  0;
		 if  (   bInsert  ||  m_var.u.qList.mems[cnt].pQ  !=  (  void  *  )id  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "nThreads_talkerProc"  )  );

			if  (  bInsert  )  pListCtrl->InsertItem(  cnt,  tBuf  );	
			else  pListCtrl->SetItemText(  cnt,  index,  tBuf  );
			m_var.u.qList.mems[cnt].pQ  =  (  void  *  )id;			
		}
		index  ++  ;
		index  ++  ;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pProcInfo->status.nThreads_talkerProc  );
		pListCtrl->SetItemText(  cnt,  index,  tBuf  );
		index  ++  ;
		time_t	t;	time(  &t  );
		char	timeBuf[128];
		getCurTime(  timeBuf  );
		char	displayBuf[128];
		qyDisplayTime(  timeBuf,  displayBuf,  sizeof(  displayBuf  )  );
		pListCtrl->SetItemText(  cnt,  index,  CString(  displayBuf  )  );
		cnt  ++  ;
	 }

	 
	 //  2016/06/15
	 {
		 int  index;  TCHAR	tBuf[256];
		 int	id  =  6;

		 BOOL	bInsert  =  FALSE;
		 if  (  m_var.u.qList.usCnt  <=  cnt  ) {
			 bInsert  =  TRUE;
		 }

		 index  =  0;
		 if  (   bInsert  ||  m_var.u.qList.mems[cnt].pQ  !=  (  void  *  )id  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "nThreads_shareDynBmpsProc"  )  );

			if  (  bInsert  )  pListCtrl->InsertItem(  cnt,  tBuf  );	
			else  pListCtrl->SetItemText(  cnt,  index,  tBuf  );
			m_var.u.qList.mems[cnt].pQ  =  (  void  *  )id;			
		}
		index  ++  ;
		index  ++  ;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pProcInfo->status.nThreads_shareDynBmps  );
		pListCtrl->SetItemText(  cnt,  index,  tBuf  );
		index  ++  ;
		time_t	t;	time(  &t  );
		char	timeBuf[128];
		getCurTime(  timeBuf  );
		char	displayBuf[128];
		qyDisplayTime(  timeBuf,  displayBuf,  sizeof(  displayBuf  )  );
		pListCtrl->SetItemText(  cnt,  index,  CString(  displayBuf  )  );
		cnt  ++  ;
	 }


	 //  2014/02/11
	 {
		 int  index;  TCHAR	tBuf[256];
		 int	id  =  5;

		 BOOL	bInsert  =  FALSE;
		 if  (  m_var.u.qList.usCnt  <=  cnt  ) {
			 bInsert  =  TRUE;
		 }

		 index  =  0;
		 if  (   bInsert  ||  m_var.u.qList.mems[cnt].pQ  !=  (  void  *  )id  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "nQNodes_displayObjQ"  )  );

			if  (  bInsert  )  pListCtrl->InsertItem(  cnt,  tBuf  );	
			else  pListCtrl->SetItemText(  cnt,  index,  tBuf  );
			m_var.u.qList.mems[cnt].pQ  =  (  void  *  )id;			
		}
		index  ++  ;
		index  ++  ;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pProcInfo->status.display.uiQNodes_displayedObjQ  );
		pListCtrl->SetItemText(  cnt,  index,  tBuf  );
		index  ++  ;
		time_t	t;	time(  &t  );
		char	timeBuf[128];
		getCurTime(  timeBuf  );
		char	displayBuf[128];
		qyDisplayTime(  timeBuf,  displayBuf,  sizeof(  displayBuf  )  );
		pListCtrl->SetItemText(  cnt,  index,  CString(  displayBuf  )  );
		cnt  ++  ;
	 }

	 //  2014/05/27
	 {
		 int  index;  TCHAR	tBuf[256];
		 int	id  =  6;

		 BOOL	bInsert  =  FALSE;
		 if  (  m_var.u.qList.usCnt  <=  cnt  ) {
			 bInsert  =  TRUE;
		 }

		 index  =  0;
		 if  (   bInsert  ||  m_var.u.qList.mems[cnt].pQ  !=  (  void  *  )id  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "hashTbl_info"  )  );

			if  (  bInsert  )  pListCtrl->InsertItem(  cnt,  tBuf  );	
			else  pListCtrl->SetItemText(  cnt,  index,  tBuf  );
			m_var.u.qList.mems[cnt].pQ  =  (  void  *  )id;			
		}
		index  ++  ;
		index  ++  ;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "total %d, max %d"  ),  pProcInfo->status.hashTbl_leftView_db.nTotal,  pProcInfo->status.hashTbl_leftView_db.maxiTotal  );
		pListCtrl->SetItemText(  cnt,  index,  tBuf  );
		index  ++  ;
		time_t	t;	time(  &t  );
		char	timeBuf[128];
		getCurTime(  timeBuf  );
		char	displayBuf[128];
		qyDisplayTime(  timeBuf,  displayBuf,  sizeof(  displayBuf  )  );
		pListCtrl->SetItemText(  cnt,  index,  CString(  displayBuf  )  );
		cnt  ++  ;
	 }

	 //
	 if  (  cnt  <  m_var.u.qList.usCnt  )  {
		 for  (  i = 0; i < m_var.u.qList.usCnt - cnt;  i ++  )  pListCtrl->DeleteItem(  cnt  );
	 }
	 m_var.u.qList.usCnt  =  cnt;

	 iErr  =  0;
errLabel:

	  return  iErr;
}

  int  listStatus_myDb(  CDlgStatusCli  *  pDlg  )
  {
	  int		iErr  =  -1;
	  DLG_statusCli_var  &  m_var  =  pDlg->m_var;
	  
	  QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli					*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	CListCtrl						*	pListCtrl				=			(  CListCtrl  *  )pDlg->GetDlgItem(  IDC_LIST_deamonStatus  );
	int									cnt						=			0;
	MIS_CNT							*	pMisCnt					=			(  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );
	int									i = 0;

	if  (  pQyMc->cfg.db.iDbType  !=  CONST_dbType_myDb  )  return  0;

	CQnmDb	db;
	if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;

	CMyDb  *  pDb  =  (  CMyDb  *  )db.m_pDbMem->pDb;


	tmp_displayQ(  pDb->m_var.pQ_qyImObjTab,  cnt,  &m_var.u.qList,  pListCtrl  );
	tmp_displayQ(  pDb->m_var.pQ_qyImObjRegInfoTab,  cnt,  &m_var.u.qList,  pListCtrl  );
	tmp_displayQ(  pDb->m_var.pQ_qyImObjRegInfoTab1,  cnt,  &m_var.u.qList,  pListCtrl  );
	tmp_displayQ(  pDb->m_var.pQ_qyImGrpInfoTab,  cnt,  &m_var.u.qList,  pListCtrl  );
	tmp_displayQ(  pDb->m_var.pQ_qyImGrpMemTab,  cnt,  &m_var.u.qList,  pListCtrl  );
	tmp_displayQ(  pDb->m_var.pQ_qyImObjRuleTab,  cnt,  &m_var.u.qList,  pListCtrl  );
	tmp_displayQ(  pDb->m_var.pQ_qyImTaskTab,  cnt,  &m_var.u.qList,  pListCtrl  );		
	tmp_displayQ(  pDb->m_var.pQ_qyImMsgTab,  cnt,  &m_var.u.qList,  pListCtrl  );
		
	//
	 if  (  cnt  <  m_var.u.qList.usCnt  )  {
		 for  (  i = 0; i < m_var.u.qList.usCnt - cnt;  i ++  )  pListCtrl->DeleteItem(  cnt  );
	 }
	 m_var.u.qList.usCnt  =  cnt;



	iErr  =  0;
errLabel:
	return  iErr;
  }

 int  CDlgStatusCli::listClientStatus(  )
{
	int									iErr					=			-1;
	QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli					*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	CListCtrl						*	pListCtrl				=			(  CListCtrl  *  )GetDlgItem(  IDC_LIST_deamonStatus  );
	int									cnt						=			0;
	MIS_CNT							*	pMisCnt					=			getMisCntByName(  pProcInfo,  _T(  ""  )  );
	int									i = 0;


	switch  (  m_var.iWndContentType  )  {
			case  CONST_qyWndContentType_qList:
				  listStatus_qList(  this  );
				  break;
			case  CONST_qyLvType_myDbStatus:
				  listStatus_myDb(  this  );
				  break;
			case  CONST_qyLvType_imNetStatList:
				  m_var.pfDisplayListContent(  pListCtrl,  0,  0  );
				  break;
			default:
					break;
	}

	iErr  =  0;
errLabel:
	return  iErr;
 }



#if  10
  __declspec(  dllexport  )  int viewStatusCli(  int  iWndContentType,  int  iSubType,  LPCTSTR  title,  int  iResId_listColumns,  PF_commonHandler  pfInitDisplayListContent,  PF_commonHandler  pfDisplayListContent  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int								iErr					=	-1;
	QY_MC					*		pQyMc					=	QY_GET_GBUF(  );
	int								iServiceId				=	CONST_qyServiceId_mis;
	MC_VAR_isCli  			*		pProcInfo				=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	CDlgStatusCli			*		pDlg					=	NULL;
	RECT							rect;

	HWND					*		phWnd_status			=	NULL;

	switch  (  iWndContentType  )  {
			case  CONST_qyLvType_realTimeImTaskList:		//  2013/02/06
				  phWnd_status  =  &pProcInfo->hWnd_status_realTimeImTaskList;
				  break;
			case  CONST_qyLvType_taskInfoList:				//  2014/09/25
				  phWnd_status  =  &pProcInfo->hWnd_status_talkerList;
				  break;
			case  CONST_qyLvType_sharingObjectList:
				  phWnd_status  =  &pProcInfo->hWnd_status_sharingObjectList;
				  break;
			case  CONST_qyLvType_playerList:
				  phWnd_status  =  &pProcInfo->hWnd_status_playerList;
				  break;
			case  CONST_qyLvType_wallList:
				  phWnd_status  =  &pProcInfo->hWnd_status_wallList;
				  break;
			case  CONST_qyLvType_ipCamList:
				  phWnd_status  =  &pProcInfo->hWnd_status_ipCamList;
				  break;
			case  CONST_qyLvType_imNetStatList:
				  phWnd_status  =  &pProcInfo->hWnd_status_imNetStatList;
				  break;
			case  CONST_qyLvType_talkerList:
				  phWnd_status  =  &pProcInfo->hWnd_status_talkerList;
				  break;
			case  CONST_qyLvType_messengerStatusList:
				  phWnd_status  =  &pProcInfo->hWnd_status_messengerStatusList;
				  break;
			case  CONST_qyWndContentType_qList:
				  phWnd_status  =  &pProcInfo->hWnd_status_qList;
				  break;
			case  CONST_qyLvType_myDbStatus:
				  phWnd_status  =  &pProcInfo->hWnd_status_myDb;
				  break;
			case  CONST_qyLvType_unprocedImTaskList:			//  2013/02/17
  				  phWnd_status  =  &pProcInfo->hWnd_status_unprocedImTaskList;
				  break;
			case  CONST_qyLvType_currentImTaskList:				//  2013/02/17
				  phWnd_status  =  &pProcInfo->hWnd_status_currentImTaskList;
				  break;
			case  CONST_qyLvType_imObjList:						//  2014/04/17
				  phWnd_status  =  &pProcInfo->hWnd_status_imObjList;
				  break;
			case  CONST_qyLvType_regInfoList:						//  2014/04/17				
				  phWnd_status  =  &pProcInfo->hWnd_status_regInfoList;
				  break;
			case  CONST_qyLvType_imGrpList:						//  2014/04/17
				  phWnd_status  =  &pProcInfo->hWnd_status_imGrpList;
				  break;
			case  CONST_qyLvType_imGrpMemList:						//  2014/04/17
				  phWnd_status  =  &pProcInfo->hWnd_status_imGrpMemList;
				  break;
			case  CONST_qyLvType_imObjRuleList:
				  phWnd_status  =  &pProcInfo->hWnd_status_imObjRuleList;
				  break;
			case  CONST_qyLvType_dynBmpList:
				  phWnd_status  =  &pProcInfo->hWnd_status_dynBmpList;
				  break;
			default:
					#ifdef  __DEBUG__
							traceLog(  _T(  "viewStatusCli failed: wndContentType err %d"  ),  iWndContentType  );
					#endif
					goto  errLabel;
					break;
	}

	//
	if  (  IsWindow(  *phWnd_status  )  )  {
		MACRO_SetForegroundWindow(  *phWnd_status  );
		iErr  =  0;  goto  errLabel;
	}

	*phWnd_status  =  NULL;

	//
	pDlg  =  new  CDlgStatusCli(  CWnd::GetDesktopWindow(  )  );
	if  (  !pDlg  )  goto  errLabel;

	//  2013/02/06
	if  (  !pDlg->bSetDlgInfo(  iWndContentType,  0,  title,  iResId_listColumns,  pfInitDisplayListContent,  pfDisplayListContent  )  )  goto  errLabel;
	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	pDlg->ShowWindow(  SW_SHOW  );

	//  
	*phWnd_status  =  pDlg->m_hWnd;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}
	if  (  !iErr  )  {
	}

	//  traceLogA(  "viewMediaControl leaves, iErr is %d",  iErr  );

	return  iErr;
}
#endif


// CDlgStatusCli dialog

IMPLEMENT_DYNAMIC(CDlgStatusCli, CDialog)

CDlgStatusCli::CDlgStatusCli(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStatusCli::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	//
	m_var.m_pParent = pParent;
	m_var.m_nID = CDlgStatusCli::IDD;

}

CDlgStatusCli::~CDlgStatusCli()
{
}


BOOL  CDlgStatusCli::bSetDlgInfo(  int  iWndContentType,  int  iSubType,  LPCTSTR  title,  int  iResId_listColumns,  PF_commonHandler  pfInitDisplayListContent,  PF_commonHandler  pfDisplayListContent  )
{
	BOOL	bRet	=	FALSE;

#if  0
	switch  (  iWndContentType  )  {
			case  CONST_qyWndContentType_qList:
			case  CONST_qyLvType_realTimeImTaskList:
				  break;
			default:
					goto  errLabel;
	}
#endif

	m_var.iWndContentType  =  iWndContentType;
	m_var.iWndContentSubType  =  iSubType;
	safeTcsnCpy(  title,  m_var.title,  mycountof(  m_var.title  )  );
	m_var.iResId_listColumns  =  iResId_listColumns;
	m_var.pfInitDisplayListContent  =  pfInitDisplayListContent;
	m_var.pfDisplayListContent  =  pfDisplayListContent;	//  2014/04/19

	bRet  =  TRUE;
errLabel:

	return  bRet;
}


BOOL CDlgStatusCli::Create(const RECT& rect)
{

	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	//MC_VAR_isMgr			*	pProc		=	NULL;

	/*
	if  (  !m_var.bInfoSet  )  {
		traceLogA(  "CDlgTalk::Create(  ): 在创建对话框之前应先设置初始数据"  );
		return  FALSE;
	}
	*/

	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  FALSE;
	if  (  !m_var.iWndContentType  )  return  FALSE;
	

	//
	if  (  !CDialog::Create(  this->m_var.m_nID, m_var.m_pParent  )  )  goto  errLabel;

	//
	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 BOOL  CDlgStatusCli::bQuitDlg(  )		
{		
	traceLogA(  "CDlgStatusCli(  )::bQuitDlg enters"  );


	//  2009/05/01
	DestroyWindow();				  
		
//  errLabel:

	traceLogA(  "CDlgStatusCli(  )::bQuitDlg leaves"  );

	return  TRUE;
}


 int  CDlgStatusCli::sizeAllControls(  )
{
errLabel:
	return  0;
}


void CDlgStatusCli::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

 LRESULT  CDlgStatusCli::OnQyPostComm( WPARAM wParam, LPARAM lParam )
 {
	 CListCtrl		*	pListCtrl	=  (  CListCtrl  *  )GetDlgItem(  IDC_LIST_deamonStatus  );
	if  (  !pListCtrl  )  goto  errLabel;


	 switch  (  wParam  )  {
			 case  CONST_qyWmParam_refreshContent:
				   #ifdef  __DEBUG__
						   traceLog(  _T(  "dlgStatusCli::OnQyPostComm: refreshContent"  )  );
				   #endif
				   if  (  m_var.pfDisplayListContent  )  m_var.pfDisplayListContent(  pListCtrl,  0,  0  );  
				   break;
			 default:
					break;
	 }

errLabel:

	 return  0;
 }


BEGIN_MESSAGE_MAP(CDlgStatusCli, CDialog)
	ON_MESSAGE(  CONST_qyWm_postComm,  OnQyPostComm  )
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_updateDynBmpList, &CDlgStatusCli::OnBnClickedButtonupdatedynbmplist)
END_MESSAGE_MAP()


// CDlgStatusCli message handlers
void CDlgStatusCli::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();

	delete  this;
}

void CDlgStatusCli::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//  CDialog::OnClose();
	bQuitDlg(  );
}

//  iH_button  =  iHeight  /  12; iW_button  =  iWidth  / 3;
 void  sizeDlg(  CDlgStatusCli  *  pDlg  )
{
	int  iWidth = 0,  iHeight  = 0;
	int  x, y;
	RECT  rect;
	int  iW  = 0,  iH  =  0;
	int  iW_button ,iH_button;
	CWnd  *  pCtrl,  *  pCtrl_button;

	pDlg->GetClientRect(  &rect  );
	iWidth  =  rect.right  -  rect.left;  
	iHeight  =  rect.bottom  -  rect.top;
	if  (  iWidth  <  10  ||  iHeight  <  10  )  goto errLabel;

	iW_button  =  iWidth  /  3;
	iH_button  =  iHeight  /  12;

	pCtrl  =  pDlg->GetDlgItem(  IDC_LIST_deamonStatus  );
	if  (  !pCtrl  )  goto  errLabel;

	pCtrl_button  =  pDlg->GetDlgItem(  IDC_BUTTON_updateDynBmpList  );
	if  (  !pCtrl_button  )  goto  errLabel;

	HDWP	hDwp;
	int  nTotal;  nTotal  =  0;

	if  (  pDlg->m_var.iWndContentType  !=  CONST_qyLvType_dynBmpList  )  
	{
		nTotal  =  1;
		pCtrl_button->ShowWindow(  SW_HIDE  );
		hDwp  =  BeginDeferWindowPos(  nTotal  );
		if  (  hDwp  )  {
			x  =  pDlg->m_var.iEdge_list_x;
			y  =  pDlg->m_var.iTop_list  -  23;
			iW  =  iWidth  -  2  *  pDlg->m_var.iEdge_list_x;
			iH  =  iHeight  -  pDlg->m_var.iTop_list;
			DeferWindowPos(  hDwp,  pCtrl->m_hWnd,  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		
			EndDeferWindowPos(  hDwp  );
		}
	}
	else
	{
		nTotal  =  2;
		hDwp  =  BeginDeferWindowPos(  nTotal  );
		if  (  hDwp  )  {
			x  =  pDlg->m_var.iEdge_list_x;
			y  =  pDlg->m_var.iTop_list  -  23;
			iW  =  iWidth  -  2  *  pDlg->m_var.iEdge_list_x;
			iH  =  iHeight  -  pDlg->m_var.iTop_list  -   2  *  iH_button;
			DeferWindowPos(  hDwp,  pCtrl->m_hWnd,  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		
			//
			x  =  x  +  iW  -  iW_button;
			//  y  =  pDlg->m_var.iTop_list  +  iH  -  iH_button;
			y  +=   iH  +  (iH_button / 2);
			iW  =  iW_button;
			iH  =  iH_button;
			DeferWindowPos(  hDwp,  pCtrl_button->m_hWnd,  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  |  SWP_SHOWWINDOW  );

			EndDeferWindowPos(  hDwp  );
		}

	}

	pDlg->SetWindowText(  pDlg->m_var.title  );

errLabel:
	return;
}

 

/*
#if  1
	 for  (  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
		  QY_PLAYER				*	pPlayer	=	&pProcInfo->av.pPlayers[i];

		  tmp_displayQ2(  &pPlayer->audio.q2, cnt,  pListCtrl  );
		  tmp_displayQ2(  &pPlayer->video.q2,  cnt,  pListCtrl  );
		  tmp_displayQ2(  &pPlayer->video.displayQ2,  cnt,  pListCtrl  );		  
	 }

	 tmp_displayQ2(  &pProcInfo->av.localAv.player.audio.q2,  cnt,  pListCtrl  );
	 tmp_displayQ2(  &pProcInfo->av.localAv.player.video.q2,  cnt,  pListCtrl  );
	 tmp_displayQ2(  &pProcInfo->av.localAv.player.video.displayQ2,  cnt,  pListCtrl  );

	 int  j;
	 for  (  j  =  0;  j  <  mycountof(  pMisCnt->channels  );  j  ++  )  {
		  MIS_CHANNEL	*	pChannel  =  &pMisCnt->channels[j];

		  tmp_displayQ(  &pChannel->cacheQ,  cnt,  pListCtrl  );
		  tmp_displayQ2(  &pChannel->toSendQ2,  cnt,  pListCtrl  );
		  tmp_displayQ2(  &pChannel->outputQ2,  cnt,  pListCtrl  );
	 }
#endif

	 tmp_displayQ(  &pProcInfo->mgrQ,  cnt,  pListCtrl  );	 
	 tmp_displayQ(  &pProcInfo->robotQ,  cnt,  pListCtrl  );
	 tmp_displayQ(  &pProcInfo->displayQ,  cnt,  pListCtrl  );
	 tmp_displayQ(  &pProcInfo->workQ,  cnt,  pListCtrl  );
	 tmp_displayQ(  &pProcInfo->schedulerQ,  cnt,  pListCtrl  );
	 tmp_displayQ2(  &pProcInfo->mediaQ2,  cnt,  pListCtrl  );
	 tmp_displayQ2(  &pProcInfo->realTimeMediaQ2,  cnt,  pListCtrl  );
 
	 iRet  =  0;
errLabel:
	 return  iRet;
}
*/

BOOL CDlgStatusCli::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int					iErr		=	-1;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	QY_COLUMNINFO	*	pColumnInfo	=	NULL;
	int					i,nFields;
	SetWindowText(  m_var.title  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	MIS_CNT	*	pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
	if  (  !pMisCnt  )  goto  errLabel;
	//
	if  (  registerSubWnd(  this->m_hWnd,  m_var.iWndContentType,  m_var.iWndContentSubType,  0,  NULL,  0,  0,  &pMisCnt->subWnds,  NULL  )  )  goto  errLabel;

	CListCtrl		*	pListCtrl	=  (  CListCtrl  *  )GetDlgItem(  IDC_LIST_deamonStatus  );
	if  (  !pListCtrl  )  goto  errLabel;

	//
	pListCtrl->ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
	pListCtrl->SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );

	pColumnInfo		=	(  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  m_var.iResId_listColumns  );
	if  (  !pColumnInfo  )  goto  errLabel;

	//CString			str;
	LV_COLUMN		lvc;
	lvc.mask  =  LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
	for (  i = 0; pColumnInfo[i].type  != -1; i ++  ) {
		lvc.iSubItem  =  i;
		lvc.pszText  =  pColumnInfo[i].label;
		lvc.cx  =  pColumnInfo[i].width;
		lvc.fmt  =  pColumnInfo[i].fmt;
		pListCtrl->InsertColumn(  i,  &lvc  );
	}
	nFields  =  i;

	pListCtrl->DeleteAllItems(  );
	//
	int		iW,iH,iH_button;
	RECT	rect,rc_list,rc_button;

	GetWindowRect(  &rect  );
	iW  =  rect.right  -  rect.left;
	iH  =  rect.bottom  -  rect.top;

	GetDlgItem(  IDC_LIST_deamonStatus  )->GetWindowRect(  &rc_list  );
	m_var.iEdge_list_x  =  (  iW  -  (  rc_list.right  -  rc_list.left  )  )  /  2;
	m_var.iTop_list  =  rc_list.top;



	sizeDlg(  this  );
	//
	if  (  m_var.pfInitDisplayListContent  )  m_var.pfInitDisplayListContent(  pListCtrl,  0,  0  );
	//
	SetTimer(  1,  1000,  NULL  );

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		PostMessage(  WM_CLOSE,  0,  0  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgStatusCli::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	listClientStatus(  );
	CDialog::OnTimer(nIDEvent);
}

void CDlgStatusCli::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	sizeDlg(  this  );
}


void CDlgStatusCli::OnBnClickedButtonupdatedynbmplist()
{
	// TODO: Add your control notification handler code here
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
									    
	MIS_CNT			*	pMisCnt		=	NULL;

	
	if  (  !(  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  )  )  )  goto  errLabel;	
	sndRetrieveDynBmpsReq_qmc(  pMisCnt,  TRUE  );

errLabel:
									
	return;
			
}
