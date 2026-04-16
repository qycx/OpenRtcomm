

#include	"stdafx.h"
#include	<stdio.h>
#include	"qyMcMainCommon.h"
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

#include	"qyOpenShellCommon.h"
#include	"funcsForIsCliHelp.h"
//
#include	"qmcCommFunc_isCli.h"
#include	"smLoginProc.h"


//
 int  qElemInit_displayedWnd(  void  *  pParam  )
{
	int							iErr			=	-1;
	MC_CTX_DISPLAYEDWND		*	pDisplayedWnd	=	(  MC_CTX_DISPLAYEDWND  *  )pParam;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );
	unsigned  int				len;

	if  (  !pDisplayedWnd  )  return  -1;

	unsigned  int  uiMaxQNodes  =  0;
	//  uiMaxQNodes  =  pQyMc->cfg.usMaxDisplayedWnds;
	uiMaxQNodes  =  pQyMc->cfg.usMaxDisplayedElemsPerWnd;	//  2014/02/10
	if  (  initGenericQ(  pDisplayedWnd->wndName,  0,  0,  uiMaxQNodes, mymalloc,  myfree,  &pDisplayedWnd->displayedElemQ  )  )  goto  errLabel;
	pDisplayedWnd->bQInited  =  TRUE;
	len  =  pQyMc->cfg.usMaxDisplayedElemsPerWnd  *  sizeof(  void  *  );
	pDisplayedWnd->ppDisplayedElems_sortedByKey  =  (  void  **  )mymalloc(  len  );				  
	if  (  !pDisplayedWnd->ppDisplayedElems_sortedByKey  )  goto  errLabel;				  
	memset(  pDisplayedWnd->ppDisplayedElems_sortedByKey,  0,  len  );				  

	iErr  =  0;
errLabel:
	return  iErr;
}

void  qElemExit_displayedWnd(  void  *  pParam  )
{
	MC_CTX_DISPLAYEDWND		*	pDisplayedWnd	=	(  MC_CTX_DISPLAYEDWND  *  )pParam;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );

	if  (  !pDisplayedWnd  )  return;

	if  (  pDisplayedWnd->ppDisplayedElems_sortedByKey  )  free(  pDisplayedWnd->ppDisplayedElems_sortedByKey  );
	if  (  pDisplayedWnd->bQInited  )  {
		exitGenericQ(  &pDisplayedWnd->displayedElemQ  );  pDisplayedWnd->bQInited  =  NULL;
	}
	return;

}


 int  __cdecl  myCompare_searchDisplayedElemByKey(  const  void  *  key,  const  void  *  pElem  )
{
	DISPLAYEDELEM_U				*	pElemU			=	(  DISPLAYEDELEM_U  *  )key;
	DISPLAYEDELEM_MESSENGER_WND	*	pDisplayedElem	=	*(  DISPLAYEDELEM_MESSENGER_WND  **  )pElem;
	__int64							iDiff			=	0;


	switch  (  pElemU->uiType  )  {
			case  CONST_displayedElemType_messengerWnd:
				  if  (  pElemU->messengerWnd.pMisCnt  !=  pDisplayedElem->pMisCnt  )  return  (  int  )pElemU->messengerWnd.pMisCnt  -  (  int  )pDisplayedElem->pMisCnt;
				  //
				  iDiff  =  pElemU->messengerWnd.idInfo.ui64Id  -  pDisplayedElem->idInfo.ui64Id;
				  break;
			default:
					break;
	}

	if  (  iDiff  <  0  )  return  -1;
	if  (  !iDiff  )  return  0;
	return  1;
	
}


int  myCompare_sortDisplayedElemByKey(  const  void  *  p1,  const  void  *  p2  )
{
	DISPLAYEDELEM_U		*	pElemU1		=	*(  DISPLAYEDELEM_U  **  )p1;
	DISPLAYEDELEM_U		*	pElemU2		=	*(  DISPLAYEDELEM_U  **  )p2;
	__int64					iDiff		=	0;

	if  (  pElemU1->uiType  !=  pElemU2->uiType  )  return  pElemU1->uiType  -  pElemU2->uiType;

	switch  (  pElemU1->uiType  )  {
			case  CONST_displayedElemType_messengerWnd:
				  if  (  pElemU1->messengerWnd.pMisCnt  !=  pElemU2->messengerWnd.pMisCnt  )  return  (  int  )pElemU1->messengerWnd.pMisCnt  -  (  int  )pElemU2->messengerWnd.pMisCnt;
				  iDiff  =  pElemU1->messengerWnd.idInfo.ui64Id  -  pElemU2->messengerWnd.idInfo.ui64Id;
				  break;
			default:
					break;
	}

	if  (  iDiff  <  0  )  return  -1;
	if  (  !iDiff  )  return  0;
	return  1;

}



 int  tmpHandler_notifyMessengerStatusChanged(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int								iErr			=	-1;
	COMMON_PARAM				*	pCommonParam	=	(  COMMON_PARAM  *  )p0;
	//  p1
	MC_CTX_DISPLAYEDWND			*	pDisplayedWnd	=	(  MC_CTX_DISPLAYEDWND  *  )p2;
	//
	MC_CTX_DISPLAY				*	pCtx			=	(  MC_CTX_DISPLAY  *  )pCommonParam->p0;
	MIS_CNT						*	pMisCnt			=	(  MIS_CNT  *  )pCommonParam->p1;
	REFRESH_RECENTFRIENDS_RESP_h	*	pStatus			=	(  REFRESH_RECENTFRIENDS_RESP_h  *  )pCommonParam->p2;
	//
	QY_MC						*	pQyMc			=	QY_GET_GBUF(  );
	int								i;
	REFRESH_RECENTFRIENDS_RESP_h		tmpStatus;
	DISPLAYEDELEM_MESSENGER_WND		elem;

	
	memset(  &tmpStatus,  0,  sizeof(  tmpStatus  )  );
	for  (  i  =  0;  i  <  pStatus->usCnt;  i  ++  )  {
		 elem.uiType  =  CONST_displayedElemType_messengerWnd;
		 elem.pMisCnt  =  pMisCnt;
		 elem.idInfo.ui64Id  =  pStatus->mems[i].idInfo.ui64Id;
		 if  (  bsearch(  &elem,  pDisplayedWnd->ppDisplayedElems_sortedByKey,  pDisplayedWnd->displayedElemQ.uiQNodes,  sizeof(  void  *  ),  myCompare_searchDisplayedElemByKey  )  )  {
			 memcpy(  &tmpStatus.mems[tmpStatus.usCnt],  &pStatus->mems[i],  sizeof(  tmpStatus.mems[0]  )  );
			 tmpStatus.usCnt  ++  ;
		 }
	}

	if  (  tmpStatus.usCnt  )  {
		MIS_MSG_REFRESHCONTACTSSTATUS_QMC				msg;

		memset(  &msg,  0,  sizeof(  msg  )  );
		msg.uiType  =  CONST_misMsgType_refreshContactsStatus_qmc;
		msg.hWnd  =  pDisplayedWnd->hWnd;
		memcpy(  &msg.status,  &tmpStatus,  sizeof(  msg.status  )  );
		if  (  qPostMsg(  &msg,  sizeof(  msg  ),  &pQyMc->gui.processQ,  _T(  "tmp_notifyMessengerStatusChanged"  )))  goto  errLabel;

		if  (  pCtx->hMainWnd  )  PostMessage(  pCtx->hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    

	}

	iErr  =  0;
errLabel:
	return  iErr;
}



 int  procMsgInput_display_resp(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_INPUT  *  pMsgInput,  unsigned  int  lenInBytes_msg,  MC_CTX_DISPLAY  *  pCtx  )
{
	 int					iErr		=	-1;
	 QY_MC				*	pQyMc		=	QY_GET_GBUF(  );
	 int					dataLen		=	0;
	 int					msgLen		=	0;
	 int					i;
     MIS_CNT			*	pMisCnt		=	(  MIS_CNT  *  )pMsgInput->pMisCnt;
	 IM_CONTENTU	*	pContent	=	NULL;
	 	 						     
	 if  (  !pMisCnt  ||  !pMsgInput  )  return  -1;
	 if  (  !isUcFlgResp(  pMsgInput->ucFlg  )  )  return  -1;	

	 if  (  isUcFlgRouteTalkData(  pMsgInput->ucFlg  )  
		 //||  isUcFlgTalkData(  pMsgInput->ucFlg  )  
		 )  
	 {

		 traceLogA(  (char*)  "display²»ÐèÒªÓÐaddrµÄÐÅÏ¢, ´íÎó"  );  goto  errLabel;
		}
	 else  {
		   pContent  =  (  IM_CONTENTU  *  )&pMsgInput->data;
	 }
	 if  (  !pContent  )  goto  errLabel;

	 switch  (  pContent->uiType  )  {				   
		     case  CONST_imCommType_refreshRecentFriendsResp:  {
			
				   REFRESH_RECENTFRIENDS_RESP_h		*	pResp;
				   QM_OBJQ_MEM							mem;
				   COMMON_PARAM							commonParam;
				   REFRESH_RECENTFRIEND_RESP_h		*	pRespMem;
				
				   pResp  =  &pContent->refreshRecentFriendsResp;
								 
				   if  (  pResp->usCnt  >  mycountof(  pResp->mems  )  )  goto  errLabel;

				   //
				   if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
					   qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("    refreshRecentFriendsResp.207 cnt %d"), pResp->usCnt, pMsgInput->uiTranNo);
				   }

				   //
				   if  (  !pResp->usCnt  )  break;	//  Ã»Ê²Ã´¿É×öµÄ

				   //
#ifdef  __DEBUG__
				   //printRefreshRecentFriendsResp(  pResp  );
#endif
				   		
				   //
				   MIS_MSG_displayRecentFriends_qmc		msg_drf;
				   memset(&msg_drf, 0, sizeof(msg_drf));
				   msg_drf.uiType = CONST_misMsgType_displayRecentFriends_qmc;
				   REFRESH_RECENTFRIENDS_RESP_h			&newStatus=msg_drf.resp;		//  ÕâÀï¿ÉÒÔ´æ·ÅºÍobjQ
				   //memset(  &newStatus,  0,  sizeof(  newStatus  )  );

				   //
				   for  (  i  =  0;  i  <  pResp->usCnt;  i  ++  )  {
					    pRespMem  =  &pResp->mems[i];
						if  (  !pRespMem->usRunningStatus  										 
							&&  !pRespMem->ulIp
								&&  !pRespMem->ulDetectedIp  )											
						{
							continue;		//  Õâ±íÃ÷Ã»ÓÐÈÎºÎÄÚÈÝ
						}

						//printQmObjQ(  (  QM_OBJQ  *  )pMisCnt->pObjQ  );

						if  (  findQMemByKey(  0,  pMisCnt->pObjQ,  &pRespMem->idInfo,  &mem  )  )  {
							traceLogA(  (char*)  "refreshRecentFriendsResp: findQMemKey failed, %I64u",  pRespMem->idInfo.ui64Id  );  
							continue;
						}
						QMEM_MESSENGER_CLI* pRecentFriend;
						pRecentFriend  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;

						//
						bool  bSame = false;

						if (pRespMem->usRunningStatus == pRecentFriend->usRunningStatus
							&& pRespMem->ulIp == pRecentFriend->ulIp
							&& pRespMem->ulDetectedIp == pRecentFriend->ulDetectedIp)
						{
							bSame = true;
							}
						else {

							//
							if (pRespMem->usRunningStatus) {
#ifdef  __DEBUG__
								//  traceLogA(  (char*)  "%I64uµÄ×´Ì¬ÓÉ %S ×ªÎª %S",  pRecentFriend->idInfo.ui64Id,  qyGetDesByType1(  CONST_usRunningStatusTable_en,  pRecentFriend->usRunningStatus  ),  qyGetDesByType1(  CONST_usRunningStatusTable_en,  pRespMem->usRunningStatus  )  );
#endif
								pRecentFriend->usRunningStatus = pRespMem->usRunningStatus;
							}
							if (pRespMem->ulIp)  pRecentFriend->ulIp = pRespMem->ulIp;
							if (pRespMem->ulDetectedIp)  pRecentFriend->ulDetectedIp = pRespMem->ulDetectedIp;
						}
						//
						pRecentFriend->tLastRefreshedTickCnt_misServ  =  (  time_t  )pResp->tLastRefreshedTime_misServ;
						//
						if (!bSame
							|| !pRecentFriend->bRefreshed_byGui)
						{
							//  
							memcpy(&newStatus.mems[newStatus.usCnt], &pResp->mems[i], sizeof(newStatus.mems[0]));
							newStatus.usCnt++;
						}
						//
						continue;
				   }

				   //
				   if (newStatus.usCnt) {
					   qPostMsg(&msg_drf, sizeof(msg_drf), &pQyMc->gui.processQ,_T("procMsgInput_display_resp"));
					   PostMessage(pQyMc->gui.hMainWnd, CONST_qyWm_postComm, CONST_qyWmParam_msgArrive, 0);
				   }

				   //  ½«newStatusÔÚdisplayObjQÀï±éÀú¸÷´°¿Ú£¬¶ÔÓÐ±ä»¯µÄÒª·¢ËÍ³öÈ¥£¬ÒÔÊ¹×´Ì¬Ë¢ÐÂ
				   //  ÒòÎªÕâÀïÊÇµ¥Ïß³ÌµÄ´¦Àí¹¤×÷£¬ËùÒÔ£¬²»ÐèÒª¿¼ÂÇdisplayObjQµÄ±ä»¯
				   MACRO_makeCommonParam3(  pCtx,  pMisCnt,  &newStatus,  commonParam  );
				   qTraverse(  &pCtx->displayedObjQ,  tmpHandler_notifyMessengerStatusChanged,  &commonParam,  0  );				   

				   pMisCnt->refreshRecentFriends.tLastRefreshedTime_misServ  =  (  time_t  )pResp->tLastRefreshedTime_misServ;

				  }
				  break;
				   
			 default:
				    traceLogA(  (char*)  "ÊÕµ½Ò»¸ö%SµÄÏìÓ¦°ü, contentType is %d, %S, Î´´¦Àí",  qyGetDesByType1(  CONST_qyCmdTable,  pMsgInput->usCode_org  ),  pContent->uiType,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
				    goto  errLabel;
					break;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}


  int  __cdecl  myCompare_searchDisplayedObjByHandle(  const  void  *  key,  const  void  *  pElem  )
{
	DISPLAYEDELEM_U				*	pElemU			=	(  DISPLAYEDELEM_U  *  )key;
	MC_CTX_DISPLAYEDWND			*	pDisplayedWnd	=	*(  MC_CTX_DISPLAYEDWND  **  )pElem;

	switch  (  pElemU->uiType  )  {
		    case  CONST_displayedElemType_wndInfo:
				  return  (  int  )pElemU->wndInfo.hWnd  -  (  int  )pDisplayedWnd->hWnd;
			case  CONST_displayedElemType_messengerWnd:
				  return  (  int  )pElemU->messengerWnd.hWnd  -  (  int  )pDisplayedWnd->hWnd;
			default:
					break;
	}

	return  -1;
	
}

 int  __cdecl  myCompare_sortDisplayedObjByHandle(  const  void  *  p1,  const  void  *  p2  )
{
	MC_CTX_DISPLAYEDWND			*	pDisplayedWnd1	=	*(  MC_CTX_DISPLAYEDWND  **  )p1;
	MC_CTX_DISPLAYEDWND			*	pDisplayedWnd2	=	*(  MC_CTX_DISPLAYEDWND  **  )p2;

	return  (  int  )pDisplayedWnd1->hWnd  -  (  int  )pDisplayedWnd2->hWnd;
	
}

 int  printDisplayedWnd(  int  i,  MC_CTX_DISPLAYEDWND  *  p  )
{
	//  traceLogA(  (char*)  "µÚ%d¸ö£¬wndName is %S, hWnd is %d",  i,  p->wndName,  p->hWnd  );
	return  0;
}

int  printDisplayedWnds(  MC_CTX_DISPLAYEDWND  **  pp,  int  cnt  )
{
	int	i;
	for  (  i  =  0;  i  <  cnt;  i  ++  )  {
		 printDisplayedWnd(  i,  pp[i]  );
	}

	return  0;
}



  //  Òª°Ñ´Ë´°¿Ú¼ÓÈëdisplayedObjQ
 int  addDisplayedWnd(  QY_MC  *  pQyMc,  DISPLAYEDELEM_WNDINFO  *  pWndInfo,  MC_CTX_DISPLAY  *  pCtx  )
{
	int								iErr				=		-1;
	MC_CTX_DISPLAYEDWND		**		ppDisplayedWnd		=		NULL;
	MC_CTX_DISPLAYEDWND				displayedWnd;
	
#ifdef  __DEBUG__
	static  int	i  =  0;
	_sntprintf(  pWndInfo->wndName,  mycountof(  pWndInfo->wndName  ),  _T(  "displayedWndName%d"  ),  i  );
	i  ++  ;
	traceLogA(  (char*)  "In addToDisplayedWnd"  );
#endif

	if  (  !pWndInfo->hWnd  )  return  -1;


	//
	memset(  &displayedWnd,  0,  sizeof(  displayedWnd  )  );
	displayedWnd.iType  =  0;
	displayedWnd.hWnd  =  pWndInfo->hWnd;
	lstrcpyn(  displayedWnd.wndName,  pWndInfo->wndName,  mycountof(  displayedWnd.wndName  )  );

	//
	ppDisplayedWnd  =  (  MC_CTX_DISPLAYEDWND  **  )bsearch(  pWndInfo,  pCtx->ppDisplayedObjs_sortedByHandle,  pCtx->displayedObjQ.uiQNodes,  sizeof(  void  *  ),  myCompare_searchDisplayedObjByHandle  );  
	if  (  ppDisplayedWnd  )  goto  errLabel;

	if  (  pCtx->displayedObjQ.uiQNodes  >=  pCtx->displayedObjQ.cfg.uiMaxQNodes  )  {
		traceLogA(  (char*)  "procMsg_diplayedElem_qmc: ÏÔÊ¾µÄ´°¿ÚÒÑ¾­µ½´ï×î´óÏÞ¶ÈµÄ%d¸ö£¬¼Ó²»½øÈ¥ÁË",  pCtx->displayedObjQ.uiQNodes  );
		goto  errLabel;
	}

	if  (  qPostMsg(  &displayedWnd,  sizeof(  MC_CTX_DISPLAYEDWND  ),  &pCtx->displayedObjQ,  _T(  "addDisplayedWnd"  )))  goto  errLabel;

	pCtx->ppDisplayedObjs_sortedByHandle[pCtx->displayedObjQ.uiQNodes  -  1]  =  pCtx->displayedObjQ.pRear->qElemMemory.m_pBuf;

	printDisplayedWnds(  (  MC_CTX_DISPLAYEDWND  **  )pCtx->ppDisplayedObjs_sortedByHandle,  pCtx->displayedObjQ.uiQNodes  );

	qsort(  pCtx->ppDisplayedObjs_sortedByHandle,  pCtx->displayedObjQ.uiQNodes,  sizeof(  void  *  ),  myCompare_sortDisplayedObjByHandle  );

	printDisplayedWnds(  (  MC_CTX_DISPLAYEDWND  **  )pCtx->ppDisplayedObjs_sortedByHandle,  pCtx->displayedObjQ.uiQNodes  );


	iErr  =  0;
errLabel:
	if  (  iErr  )  {
	}
	traceLogA(  (char*)  "addDisplayedWnd %S %s",  pWndInfo->wndName,  iErr  ?  "failed"  :  "ok"  );  
	return  iErr;
}

BOOL  bRemoveCond_byDisplayedWnd(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	//  p0
	DISPLAYEDELEM_WNDINFO		*	pWndInfo	=	(  DISPLAYEDELEM_WNDINFO  *  )p1;
	MC_CTX_DISPLAYEDWND			*	pWnd		=	(  MC_CTX_DISPLAYEDWND  *  )p2;

	if  (  pWndInfo->hWnd  ==  pWnd->hWnd  )  {
		traceLogA(  (char*)  "wndName %S ½«±»É¾³ý",  pWnd->wndName  );
		return  TRUE;
	}
	return  FALSE;

}

 int  set_ppDisplayedObjs_sortedByHandle(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	MC_CTX_DISPLAY			*	pCtx			=	(  MC_CTX_DISPLAY  *  )p0;
	int						*	pI				=	(  int  *  )p1;
	MC_CTX_DISPLAYEDWND		*	pDisplayedWnd	=  (  MC_CTX_DISPLAYEDWND  *  )p2;


	pCtx->ppDisplayedObjs_sortedByHandle[*pI]  =  p2;
	(  *pI  )  ++  ;  

	return  0;
}





 int  printDisplayedElem(  int  i,  DISPLAYEDELEM_U  *  p  )
 {
	 switch  (  p->uiType   )  {
			 case  CONST_displayedElemType_messengerWnd:
				   //  traceLogA(  (char*)  "µÚ%d¸ö, id is %I64u,  hWnd is %d",  i,  p->messengerWnd.idInfo.ui64Id,  p->messengerWnd.hWnd  );
				   break;
			 default:
					break;
	 }

	 return  0;
 }


 int  printDisplayedElems(  DISPLAYEDELEM_U  **  ppDisplayedElems,  int  cnt  )
{
	int		i;
	
	for  (  i  =  0;  i  <  cnt;  i  ++  )  {
		 printDisplayedElem(  i,  ppDisplayedElems[i]  );
	}

	return  0;
}
				  



  int  procMsg_diplayedElem_qmc(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_DISPLAYEDELEM_QMC  *  pMsg,  unsigned  int  lenInBytes_msg,  MC_CTX_DISPLAY  *  pCtx  )
{
	int										iErr				=		-1;
	QY_MC							*		pQyMc				=		QY_GET_GBUF(  );
	MC_CTX_DISPLAYEDWND				**		ppDisplayedWnd		=		NULL;
	int										i;
	DISPLAYEDELEM_MESSENGER_WND		**		ppDisplayedElem		=		NULL;
	
	traceLogA(  (char*)  "procMsg_displayedElem_qmc enters"  );

	if  (  !pCtx  )  return  -1;

	switch  (  pMsg->elemU.uiType  )  {
			case  CONST_displayedElemType_wndInfo:  

				  if  (  !pMsg->elemU.wndInfo.bClosed  )  {
				  	  if  (  addDisplayedWnd(  pQyMc,  &pMsg->elemU.wndInfo,  pCtx  )  )  {
						  traceLogA(  (char*)  "addToDisplayedWnd failed"  );  goto  errLabel;
					  }
					}
				  else  {
					    qRemoveMsg(  &pCtx->displayedObjQ,  bRemoveCond_byDisplayedWnd,  0,  &pMsg->elemU.wndInfo  );

						//  ÒòÎªÉ¾³ýÁËÒ»¸ö½Úµã£¬ËùÒÔÒª¶ÔdisplayedObjQÖØÐÂÅÅÐò
						i  =  0;
						qTraverse(  &pCtx->displayedObjQ,  set_ppDisplayedObjs_sortedByHandle,  pCtx,  &i  );
						
						printDisplayedWnds(  (  MC_CTX_DISPLAYEDWND  **  )pCtx->ppDisplayedObjs_sortedByHandle,  pCtx->displayedObjQ.uiQNodes  );
						qsort(  pCtx->ppDisplayedObjs_sortedByHandle,  pCtx->displayedObjQ.uiQNodes,  sizeof(  void  *  ),  myCompare_sortDisplayedObjByHandle  );
						printDisplayedWnds(  (  MC_CTX_DISPLAYEDWND  **  )pCtx->ppDisplayedObjs_sortedByHandle,  pCtx->displayedObjQ.uiQNodes  );


				  }

				  break;
			case  CONST_displayedElemType_messengerWnd:  {
				  
				  if  (  !pMsg->elemU.messengerWnd.hWnd  )  goto  errLabel;

				  ppDisplayedWnd  =  (  MC_CTX_DISPLAYEDWND  **  )bsearch(  &pMsg->elemU,  pCtx->ppDisplayedObjs_sortedByHandle,  pCtx->displayedObjQ.uiQNodes,  sizeof(  void  *  ),  myCompare_searchDisplayedObjByHandle  );  
				  if  (  !ppDisplayedWnd  )  {
					  traceLogA(  (char*)  "ppDisplayedWnd is null"  );  
					  goto  errLabel;
				  }
				  
				  printDisplayedWnd(  0,  ppDisplayedWnd[0]  );

				  traceLogA(  (char*)  ""  );	
				  ppDisplayedElem  =  (  DISPLAYEDELEM_MESSENGER_WND  **  )bsearch(  &pMsg->elemU,  ppDisplayedWnd[0]->ppDisplayedElems_sortedByKey,  ppDisplayedWnd[0]->displayedElemQ.uiQNodes,  sizeof(  void  *  ),  myCompare_searchDisplayedElemByKey  );
				  if  (  ppDisplayedElem  )  break;
				  if  (  qPostMsg(  &pMsg->elemU,  sizeof(  pMsg->elemU.messengerWnd  ),  &ppDisplayedWnd[0]->displayedElemQ,  _T(  "procmsg_displayedElem"  )))  goto  errLabel;
				  //
				  ppDisplayedWnd[0]->ppDisplayedElems_sortedByKey[ppDisplayedWnd[0]->displayedElemQ.uiQNodes  -  1]  =  ppDisplayedWnd[0]->displayedElemQ.pRear->qElemMemory.m_pBuf;

				  printDisplayedElems(  (  DISPLAYEDELEM_U  **  )ppDisplayedWnd[0]->ppDisplayedElems_sortedByKey,  ppDisplayedWnd[0]->displayedElemQ.uiQNodes  );

				  qsort(  ppDisplayedWnd[0]->ppDisplayedElems_sortedByKey,  ppDisplayedWnd[0]->displayedElemQ.uiQNodes,  sizeof(  void  *  ),  myCompare_sortDisplayedElemByKey  );

				  printDisplayedElems(  (  DISPLAYEDELEM_U  **  )ppDisplayedWnd[0]->ppDisplayedElems_sortedByKey,  ppDisplayedWnd[0]->displayedElemQ.uiQNodes  );
				  
				  }
				  break;
			default:
					break;

	}


	iErr  =  0;
errLabel:

	traceLogA(  (char*)  "procMsg_displayedElem_qmc leaves"  );

	return  iErr;
}


  int  tmpHandler_procMsg_refreshMeStatus_qmc(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	MC_CTX_DISPLAY					*		pCtx				=		(  MC_CTX_DISPLAY  *  )p0;
	MIS_MSG_REFRESHMESTATUS_QMC		*		pMsg				=		(  MIS_MSG_REFRESHMESTATUS_QMC  *  )p1;
	MC_CTX_DISPLAYEDWND				*		pDisplayedWnd		=		(  MC_CTX_DISPLAYEDWND  *  )p2;
	//
	QY_MC							*		pQyMc				=		QY_GET_GBUF(  );

	pMsg->hWnd  =  pDisplayedWnd->hWnd;
	if  (  pCtx->hMainWnd  )  qPostMsg(  pMsg,  sizeof(  pMsg[0]  ),  &pQyMc->gui.processQ,  _T(  "tmp_procMsg_refreshMe"  ));

	return  0;
}


   int  procMsg_refreshMeStatus_qmc(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_REFRESHMESTATUS_QMC  *  pMsg,  unsigned  int  lenInBytes_msg,  MC_CTX_DISPLAY  *  pCtx  )
{
	int										iErr				=		-1;
	QY_MC							*		pQyMc				=		QY_GET_GBUF(  );

	traceLogA(  (char*)  "procMsg_refreshMeStatus_qmc enters"  );

	if  (  !pCtx  )  return  -1;

	qTraverse(  &pCtx->displayedObjQ,  tmpHandler_procMsg_refreshMeStatus_qmc,  pCtx,  pMsg  );

	//  ×îºó´¥·¢½çÃæÀ´Ë¢ÐÂÏÔÊ¾
	if  (  pCtx->hMainWnd  )  PostMessage(  pCtx->hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    

	iErr  =  0;

//  errLabel:

	traceLogA(  (char*)  "procMsg_refreshMeStatus_qmc enters"  );

	return  iErr;
}



extern "C" DWORD WINAPI mcThreadProc_mis_display( LPVOID lpParameter )
{
	 QY_MC						*		pQyMc							=	QY_GET_GBUF(  );
	 QY_SERVICEGUI_INFO			*		pSci							=	(  QY_SERVICEGUI_INFO  *  )lpParameter;
	 if  (  !pSci  )  return  -1;
	 MC_VAR_isCli					*		pProcInfo						=	(  MC_VAR_isCli  *  )pSci->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs   ) return  -1;
	 int								loopCtrl						=	0;
	 int								i;
	 DWORD								dwThreadId						=	GetCurrentThreadId(  );
	 CQyMalloc							mallocObj;
	 MIS_MSGU					*		pMsg							=	(  MIS_MSGU  *  )mallocObj.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  );
	 unsigned  int						len;
	 DWORD								dwRet;
	 //
	 MC_CTX_DISPLAY						ctx;
	 //
	 //  CWnd						*		pMainWnd						=	AfxGetApp(  )->m_pMainWnd;
	 //	 
	 DWORD								dwCurTickCnt					=	0;

#ifdef  __DEBUG__
	 traceLogA(  (char*)  "mcThreadProc_mis_display:  enters"  );
#endif

	 //
	 memset(  &ctx,  0,  sizeof(  ctx  )  );

	 if  (  !pMsg  )  goto  errLabel;

	 if  (  initGenericQ(  _T(  "displayWndQ"  ),  0,  0,  pQyMc->cfg.usMaxDisplayedWnds,  mallocMemory,  mymalloc,  qElemInit_displayedWnd,  qElemExit_displayedWnd,  freeMemory,  myfree,  NULL,  &ctx.displayedObjQ  )  )  goto  errLabel;
	 ctx.bQInited  =  TRUE;
	 len  =  sizeof(  void  *  )  *  pQyMc->cfg.usMaxDisplayedWnds;
	 ctx.ppDisplayedObjs_sortedByHandle  =  (  void  **  )mymalloc(  len   );
	 if  (  !ctx.ppDisplayedObjs_sortedByHandle  )  goto  errLabel;
	 memset(  ctx.ppDisplayedObjs_sortedByHandle,  0,  len  );
	 
	 //
	 for  (  ;  !pQyMc->bQuit;  )  {
		 if (!pQyMc->bLogon) {
			 break;
		 }

		  //  if  (  !pMainWnd  )  pMainWnd					=	AfxGetApp(  )->m_pMainWnd;
		  if  (  !pQyMc->gui.hMainWnd  )  {
			  Sleep(  1000  );  continue;
		  }
		  ctx.hMainWnd  =  pQyMc->gui.hMainWnd;

		  //
		  dwRet  =  WaitForSingleObject(  pProcInfo->displayQ.hSemaTrigger,  1000  );
		  if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
		  
		  //
		  for  (  ;  !pQyMc->bQuit;  )  {
			   len  =  sizeof(  pMsg[0]  );
			   if  (  qGetMsg(  &pProcInfo->displayQ,  pMsg,  &len  )  )  break;
			   memset(  (  (  char  *  )pMsg  )  +  len,  0,  min(  256,  sizeof(  pMsg[0]  )  -  len  )  );			   
			   switch  (  pMsg->uiType  )  {
				       case  CONST_misMsgType_input:
						     if  (  isUcFlgResp(  pMsg->input.ucFlg  )  )  {
							   	 procMsgInput_display_resp(  pProcInfo,  &pMsg->input,  len,  &ctx  );
							   	 break;								
							 }							 
						     break;
					   case  CONST_misMsgType_displayedElem_qmc:
						     procMsg_diplayedElem_qmc(  pProcInfo,  &pMsg->displayedElem_qmc,  len,  &ctx  );
						     break;
					   case  CONST_misMsgType_refreshMeStatus_qmc:
						     procMsg_refreshMeStatus_qmc(  pProcInfo,  &pMsg->refreshMeStatus_qmc,  len,  &ctx  );
						     break;
					   default:
						        traceLogA(  (char*)  "%SµÄmisMsgÎ´µÃµ½´¦Àí",  qyGetDesByType1(  CONST_misMsgTypeTable,  pMsg->uiType  )  );
								break;
			   }
		
#if 0
			   dwRet  =  WaitForSingleObject(  pProcInfo->displayQ.hSemaTrigger,  50  );
			   if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;			   
#endif
		  }

		  dwCurTickCnt  =  GetTickCount(  );

		  //  2014/02/11
		  pProcInfo->status.display.uiQNodes_displayedObjQ  =  ctx.displayedObjQ.uiQNodes;

		  //
		  //  for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
		  for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
		  {
			   MIS_CNT					*		pMisCnt						=	getMisCntByIndex(  0,  pProcInfo,  i  );  //  &pProcInfo->misCnts[i];
			   MIS_CHANNEL				*		pChannel					=	NULL;
			   //
			   if  (  !pMisCnt->cfg.dynCfg.cnt.usCntPort  )  continue;
			   //
			   if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  CONST_channelType_talking  )  )  )  continue;

			   Param_dbg param;
			   param.m_pHint=(TCHAR*)_T("thread_display.679");
			   param.m_bShowInfo = false;
			   //
			   if  (  !bChannelOk(  pChannel,  &param  )  )  continue;
		
			   //
			   if (pProcInfo->m_iCtxSubtype == CONST_ctxSubtype_qmcSm) {
				   Ctx_sm* pCtxSm = pProcInfo->getCtxSm();
				   if (pCtxSm) {
					   Var_ca_dev_qmc* pVc = &pCtxSm->ca_dev;

					   //
					   if (!pVc->flgs.sxrz.bDone_sxrz
						   ||  !pVc->flgs.sxrz.bDone_sqm  ) 
					   {
						   continue;
					   }
				   }
			   }


			   //
			   if  (  pMisCnt->refreshRecentFriends.bRefreshAtOnce
				   ||  dwCurTickCnt  -  pMisCnt->refreshRecentFriends.dwLastTickCnt  >  (  DWORD  )(  pMisCnt->cfg.usIntervalInS_refreshRecentFriends  *  1000  )  )  
			   {
				   pMisCnt->refreshRecentFriends.bRefreshAtOnce = false;

				   //  traceLogA(  (char*)  ""  );
				   MIS_MSGU  *  pMsgBuf	=	pMsg;	//  注意：这里因为pMsg离开了取消息的循环，所以没有在使用中。这里可以当pMsgBuf使用。2009/12/11
				   pFuncs->pf_startToRefreshRecentFriends(  pMisCnt,  pMsgBuf  );
				   pMisCnt->refreshRecentFriends.dwLastTickCnt  =  dwCurTickCnt;
			   }
		  }

	 }


errLabel:

	 if  (  ctx.ppDisplayedObjs_sortedByHandle  )  free(  ctx.ppDisplayedObjs_sortedByHandle  );
	 if  (  ctx.bQInited  )  exitGenericQ(  &ctx.displayedObjQ  );

#ifdef  __DEBUG__
	 traceLogA(  (char*)  "mcThreadProc_mis_display:  leaves"  );
#endif

	 //
	 pProcInfo->status.threadsStatus.ulbDisplayQuit  =  TRUE;

	 return  0;
}

///////////////////////////
//////////////////////////

 int  myCompare_searchMessengerTreeByKey(  const  void  *  p1,  const  void  *  p2  )
{
	DISPLAYEDELEM_MESSENGER_TREE	*	pElem1  =  (  DISPLAYEDELEM_MESSENGER_TREE  *  )p1;
	DISPLAYEDELEM_MESSENGER_TREE	*	pElem2  =  *(  DISPLAYEDELEM_MESSENGER_TREE  **  )p2;
	_int64								iDiff	=	0;				

	if  (  pElem1->uiType  !=  pElem2->uiType  )  return  pElem1->uiType  -  pElem2->uiType;

	switch  (  pElem1->uiType  )  {
			case  CONST_displayedElemType_messengerTree:
				  iDiff  =  pElem1->idInfo.ui64Id  -  pElem2->idInfo.ui64Id;
				  break;
			default:
					break;
	}

	if  (  iDiff  <  0  )  return  -1;
	if  (  !iDiff  )  return  0;
	return  1;

}


 BOOL  bRefreshContactsStatus_wnd(  MIS_MSG_REFRESHCONTACTSSTATUS_QMC  *  pMsg,  MC_CTX_DISPLAYEDWND  *  pCtx,  PF_commonHandler  pf,  void  *  pWndParam  )
{
	BOOL								bRet				=	FALSE;
	//  CLeftView						*	pLeftView			=	(  CLeftView  *  )pWndParam;
	QY_MC							*	pQyMc				=	QY_GET_GBUF(  );
	int									i;
	DISPLAYEDELEM_MESSENGER_TREE		elem;
	DISPLAYEDELEM_MESSENGER_TREE	**	ppMessengerTree		=	NULL;
	DISPLAYEDELEM_MESSENGER_TREE	**	pp;
	//  TCHAR								tBuf[256];
	//  TCHAR							*	displayName			=	tBuf;	
	//  int									nImage,  nSelectedImage;
			 

	traceLogA(  (char*)  "bRefreshFriendsStatus_leftView enters"  );
	
	if  (  pMsg->status.usCnt  >  mycountof(  pMsg->status.mems  )  )  goto  errLabel;

	for  (  i  =  0;  i  <  pMsg->status.usCnt;  i  ++  )  {
		 memset(  &elem,  0,  sizeof(  elem  )  );
		 elem.uiType  =  CONST_displayedElemType_messengerTree;
		 elem.pMisCnt  =  pMsg->pMisCnt;
		 elem.idInfo.ui64Id  =  pMsg->status.mems[i].idInfo.ui64Id;
		 ppMessengerTree  =  (  DISPLAYEDELEM_MESSENGER_TREE  **  )bsearch(  &elem,  pCtx->ppDisplayedElems_sortedByKey, pCtx->displayedElemQ.uiQNodes,  sizeof(  void  *  ),  myCompare_searchMessengerTreeByKey  );
		 if  (  !ppMessengerTree  )  {
			 #ifdef  __DEBUG__
					 traceLogA(  (char*)  "ppMessengerTree null"  );  
			 #endif
			 continue;
		 }
		 //
		 //  ÒòÎªmessengerTree²»ÊÇÒ»¸öÏÔÊ¾½ÚµãºÍÒ»¸ömessengerÒ»Ò»¶ÔÓ¦µÄ£¬ ¶øÊÇ¿ÉÒÔÒ»¸ömessengerÔÚºÜ¶à½ÚµãÀï³öÏÖ¡£
		 //  ËùÒÔ£¬ÔÚbearchÀïÕÒµ½µÄ²»ÊÇÎ¨Ò»Ò»¸ö¡£ÏÂÃæÓÃbsarch·µ»ØµÄ£¬À´ÕÒµ½¶ÓÁÐÖÐµÚÒ»¸öÍ¬ÑùmessengerµÄ£¬È»ºó£¬°ÑËùÓÐµÄºóÐøµÄÍ¬ÑùmessengerµÄ½Úµã¶¼Ë¢ÐÂÒ»±é
		 //
		 for  (  pp  =  ppMessengerTree;  pp  >=  (  DISPLAYEDELEM_MESSENGER_TREE  **  )pCtx->ppDisplayedElems_sortedByKey;  pp  --  )  {
			  if  (  pp[0]->uiType  !=  ppMessengerTree[0]->uiType  ||  pp[0]->pMisCnt  !=  ppMessengerTree[0]->pMisCnt  ||  pp[0]->idInfo.ui64Id  !=  ppMessengerTree[0]->idInfo.ui64Id  )  break;
		 }
		 pp  ++  ;	//  »Øµ½µÚÒ»¸öºÏÊÊµÄ
		 if  (  pp  >  ppMessengerTree  ||  pp  <  (  DISPLAYEDELEM_MESSENGER_TREE  **  )pCtx->ppDisplayedElems_sortedByKey  )  {
			 #ifdef  __DEBUG__
					 traceLogA(  (char*)  "pp err"  );  
			 #endif
			 goto  errLabel;
		 }

		 for  (  ;  pp  <=  (  DISPLAYEDELEM_MESSENGER_TREE  **  )&pCtx->ppDisplayedElems_sortedByKey[pCtx->displayedElemQ.uiQNodes  -  1]   ;  pp  ++  )  {
			  if  (  pp[0]->uiType  !=  ppMessengerTree[0]->uiType  ||  pp[0]->pMisCnt  !=  ppMessengerTree[0]->pMisCnt  ||  pp[0]->idInfo.ui64Id  !=  ppMessengerTree[0]->idInfo.ui64Id  )  break;

			  //
			  if  (  pp  &&  pp[0]  )  {

				  if  (  pf  &&  pf(  pp[0],  &pMsg->status.mems[i], pWndParam  )  )  goto  errLabel;
				  /*
				  //  Ö»Ë¢ÐÂÕ¹¿ª½Úµã
				  TVITEM				tvItem;
			 
				  tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
				  tvItem.hItem  =  (  HTREEITEM  )pp[0]->hItem;
				  tvItem.pszText  =  tBuf;
				  tvItem.cchTextMax  =  mycountof(  tBuf  );
				  if  (  !pLeftView->m_TreeCtrl->GetItem(  &tvItem  )  )  {
					  traceLogA(  (char*)  "bRefreshFriendsStatus_leftView: GetItem failed, ¿ÉÄÜÊÇ´Ë½ÚµãÒÑ¾­±»É¾³ýÁË"  );
					  continue;
				  }
		   
				  displayName  =  tBuf;	//  ÕâÀï¹ÊÒâÈÃdisplayNameÖ¸ÏòtBuf, ÊÇÒòÎªÕâÀïÔÝÊ±Ö»ÐèÒª±ä»¯Í¼±ê

				  getMessengerImages(  pQyMc,  pMsg->status.mems[i].usRunningStatus,  &nImage,  &nSelectedImage  );

				  if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
					  _sntprintf(  tBuf,  sizeof(  tBuf  ) /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
					  tvItem.iImage  =  nImage;
					  tvItem.iSelectedImage  =  nSelectedImage;
					  pLeftView->m_TreeCtrl->SetItem(  &tvItem  );
				  }
				  */

			  }
		 }
	}



	bRet  =  TRUE;

errLabel:
	traceLogA(  (char*)  "bRefreshFriendsStatus_leftView leaves"  );
	
	return  bRet;
}






 BOOL  bRefreshMeStatus_wnd(  MIS_MSG_REFRESHMESTATUS_QMC  *  pMsg,  MC_CTX_DISPLAYEDWND  *  pCtx,  PF_commonHandler  pf,  void  *  pWndParam  )
{
	BOOL								bRet				=	FALSE;
	//  CLeftView						*	pLeftView			=	(  CLeftView  *  )pLeftViewParam;
	QY_MC							*	pQyMc				=	QY_GET_GBUF(  );
	MIS_CNT							*	pMisCnt				=	(  MIS_CNT  *  )pMsg->pMisCnt;
	if  (  !pMisCnt  )  return  FALSE;
	//  TCHAR								tBuf[256];
	//  TCHAR								displayName[128]	=	_T(  ""  );	
	//  int									nImage,  nSelectedImage;
	//
	DISPLAYEDELEM_MESSENGER_TREE		elem;
	DISPLAYEDELEM_MESSENGER_TREE	**	ppMessengerTree		=	NULL;
	DISPLAYEDELEM_MESSENGER_TREE	**	pp;
	//
	//  QMEM_MESSENGER_CLI				*	pQMemObj			=	NULL;
	//  QM_OBJQ_MEM							mem;
		 
	
	traceLogA(  (char*)  "bRefreshMeStatus_leftView enters"  );
	

	MIS_MSG_REFRESHCONTACTSSTATUS_QMC				msg;

	memset(  &msg,  0,  sizeof(  msg  )  );
	msg.uiType  =  CONST_misMsgType_refreshContactsStatus_qmc;
	msg.hWnd  =  pMsg->hWnd;
	msg.pMisCnt  =  pMisCnt;
	msg.status.mems[0].idInfo.ui64Id  =  pMisCnt->idInfo.ui64Id;
	msg.status.mems[0].usRunningStatus  =  pMisCnt->status.usRunningStatus;
	msg.status.usCnt  =  1;

	bRefreshContactsStatus_wnd(  &msg,  pCtx,  pf,  pWndParam  );
	

	/*
	//  ÕÒÒ»ÏÂ¹ÜÀí¶ÓÁÐ
	if  (  findQMemByKey(  0,  pMisCnt->pObjQ,  &pMisCnt->idInfo,  &mem  )  )  goto  errLabel;
	pQMemObj  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
	if  (  !pQMemObj  )  goto  errLabel;
	*/

	memset(  &elem,  0,  sizeof(  elem  )  );
	elem.uiType  =  CONST_displayedElemType_meTree;
	elem.pMisCnt  =  pMsg->pMisCnt;

	ppMessengerTree  =  (  DISPLAYEDELEM_MESSENGER_TREE  **  )bsearch(  &elem,  pCtx->ppDisplayedElems_sortedByKey, pCtx->displayedElemQ.uiQNodes,  sizeof(  void  *  ),  myCompare_searchMessengerTreeByKey  );
	if  (  !ppMessengerTree  )  {
		traceLogA(  (char*)  "displayedObjQÀïÃ»ÓÐMeµÄ½ÚµãÐÅÏ¢£¬´íÎó"  );  
		goto  errLabel;
	}

	pp  =  ppMessengerTree;
	if  (  pf  &&  pf(  pp[0],  0,  pWndParam  )  )  goto  errLabel;
	//
	/*
	{
		//  Ö»Ë¢ÐÂÕ¹¿ª½Úµã
		TVITEM				tvItem;
			 
		tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
		tvItem.hItem  =  (  HTREEITEM  )pp[0]->hItem;
		tvItem.pszText  =  tBuf;
		tvItem.cchTextMax  =  mycountof(  tBuf  );
		if  (  !pLeftView->m_TreeCtrl->GetItem(  &tvItem  )  )  {
			traceLogA(  (char*)  "bRefreshMeStatus_leftView: GetItem failed, ¿ÉÄÜÊÇ´Ë½ÚµãÒÑ¾­±»É¾³ýÁË, ÓÐ´íÎó"  );  goto  errLabel;
		}

	
		_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s(%I64u)"  ),  pMisCnt->displayName,  pMisCnt->idInfo.ui64Id  );
		if  (  pMisCnt->stat.uiCnt_unprocedTasks  )  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s - Î´Íê³É%d"  ),  displayName,  pMisCnt->stat.uiCnt_unprocedTasks  );
		if  (  pMisCnt->stat.uiCnt_processingTasks  )  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s - ´¦ÀíÖÐ%d"  ),  displayName,  pMisCnt->stat.uiCnt_processingTasks  );
		if  (  pMisCnt->stat.uiCnt_processBreakTasks  )  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s - ÖÐ¶Ï%d"  ),  displayName,  pMisCnt->stat.uiCnt_processBreakTasks  );

		//		  
		getMessengerImages(  pQyMc,  pQMemObj->usRunningStatus,  &nImage,  &nSelectedImage  );
		  
		if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
			_sntprintf(  tBuf,  sizeof(  tBuf  ) /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
			tvItem.iImage  =  nImage;
			tvItem.iSelectedImage  =  nSelectedImage;
			pLeftView->m_TreeCtrl->SetItem(  &tvItem  );
		}

	}
	*/

	bRet  =  TRUE;

errLabel:

	traceLogA(  (char*)  "bRefreshMeStatus_leftView leaves"  );

	return  bRet;

}


 //
 int isCli_addTo_qmObjQ(QY_MESSENGER_ID  idInfo)
 {
	 int  iErr = -1;
	 CCtxQyMc* pQyMc = g_pQyMc;
	 CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	 MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	 QY_SERVICEGUI_INFO* pSci = (QY_SERVICEGUI_INFO*)pProcInfo->pSgiParam;

	 CQnmDb  db;
	 void* pDb = NULL;

	 //
	 if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
	 pDb = db.m_pDbMem->pDb;


	 QM_OBJQ_MEM	mem;
	 QY_MESSENGER_INFO  obj;

	 //
	 unsigned int uiObjType; uiObjType = 0;
	 getTalkerDesc(idInfo, &uiObjType, mynull, 0, mynull, mynull, mynull, 0, mynull, 0, mynull, 0);


	 //
	 memset(&obj, 0, sizeof(obj));



	 //
	 lstrcpyn(obj.misServName, pMisCnt->cfg.misServName, mycountof(obj.misServName));
	 obj.uiType = uiObjType;
	 obj.idInfo.ui64Id = idInfo.ui64Id;

	 //  ÕâÀï·Åµ½¹ÜÀí¶ÓÁÐÖÐÈ¥
	 if (procQmObjQ(pSci, (QM_OBJQ*)pMisCnt->pObjQ, pDb, pQyMc->cfg.db.iDbType, obj.uiType, &obj, &mem))  goto  errLabel;

	 iErr = 0;
 errLabel:
	 return  iErr;

 }


