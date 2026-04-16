
#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyWnd.h"
#include	"qmcCmdProc.h"
#include	"qmcVWall.h"
#include	"dlgTalkPublic.h"
#include	"qmcVideoCapture_isCli.h"







//
 QY_DMITEM  CONST_capTypeTable[]  =
{
	{	CONST_capType_av,				(TCHAR*)_T(  "av"  ),	},
	{	CONST_capType_screen,			(TCHAR*)_T(  "screen"  ),	},
	{	CONST_capType_mediaFile,		(TCHAR*)_T(  "mediaFile"  ),	},
	{	CONST_capType_mediaDevice,		(TCHAR*)_T(  "mediaDevice"  ),  },
	{	CONST_capType_mosaic,			(TCHAR*)_T(  "d3dWall"  ),		},	//  2013/12/10

	{	-1,				},
};

 QY_DMITEM  CONST_subCapTypeTable[]  =
{
	{	CONST_subCapType_null,			(TCHAR*)_T(  "0"  ),	},
	{	CONST_subCapType_webcam,		(TCHAR*)_T(  "webcam"  ),	},
	//  2015/03/11
	{	CONST_subCapType_unresizable,	(TCHAR*)_T(  "unresizable"  ),	}, 
	//
	{	-1,													},	
};

 QY_DMITEM  CONST_capUsageTable[]  =
{
	{	CONST_capUsage_null,			(TCHAR*)_T(  "0"  ),		},
	{	CONST_capUsage_conf,			(TCHAR*)_T(  "conf"  ),		},
	{	CONST_capUsage_3dConf,			(TCHAR*)_T(  "3dConf"  ),	},			//  2014/12/15
	{	-1,													},	
};




 //
  QY_DMITEM  CONST_rulePriorityTable[]  =
 {
	 {	CONST_vwRuleType_dynBmp,				(  TCHAR  *  )20,	},
	 {	CONST_vwRuleType_conference_imGrp,		(  TCHAR  *  )5,	},
	 {	CONST_vwRuleType_conference_imGrpMem,	(  TCHAR  *  )8,	},
	 //
	 {	CONST_vwRuleType_talkers,				(  TCHAR  *  )1,	},		//  2012/04/02
	 {	CONST_vwRuleType_messenger,				(  TCHAR  *  )2,	},
	 //
	 {	CONST_vwRuleType_bgMemVideo,			(  TCHAR  *  )3,	},		//  2017/09/25
	 {	-1,		},
 };

 //  2012/04/02. 仅用来显示
 QY_DMITEM  CONST_vwRuleTypeTable[]  =
 {
	 {	CONST_vwRuleType_dynBmp,					(TCHAR*)_T(  "Img"  ),		},
	 {	CONST_vwRuleType_conference_imGrp,			(TCHAR*)_T(  "Grp"  ),		},
	 {	CONST_vwRuleType_conference_imGrpMem,		(TCHAR*)_T(  "GrpMem"  ),		},
	 //
	 {	CONST_vwRuleType_bgMemVideo,				(TCHAR*)_T(  "bgMemVideo"  ),		},
	 //
	 {	CONST_vwRuleType_talkers,					(TCHAR*)_T(  "Talkers"  ),	},
	 {	CONST_vwRuleType_messenger,					(TCHAR*)_T(  "Msgr"  ),	},
	 //
	 {	CONST_vwRuleType_walls,						(TCHAR*)_T(  "Walls"  ),	},
	 {	-1,		},
 };



 //
 int  setModalWnd(  QY_MC  *  pQyMc,  HWND  hDlg  )
{
	//
	return  setModalWnd_func(  pQyMc,  hDlg,  FALSE  );
}



 //
 int  setModalWnd_func(  QY_MC  *  pQyMc,  HWND  hDlg,  BOOL  bFileDialog  )
{
	int					iErr		=	-1;

	if  (  !pQyMc  )  return  -1;

	if  (  IsWindow(  pQyMc->gui.hWnd_menu  )  )  return  -1;

	if  (  !bFileDialog  )  {
		if  (  IsWindow(  pQyMc->gui.hWnd_modal  )  )  {
			SendMessage(  pQyMc->gui.hWnd_modal,  WM_CLOSE,  0,  0  );
		}
		if  (  IsWindow(  pQyMc->gui.hWnd_modal  )  )  goto  errLabel;
		
		pQyMc->gui.hWnd_modal  =  hDlg;
		}
	else  {
		  if  (  IsWindow(  pQyMc->gui.hWnd_fileDialog  )  )  {
			  SendMessage(  pQyMc->gui.hWnd_fileDialog,  WM_CLOSE,  0,  0  );
		  }
		  if  (  IsWindow(  pQyMc->gui.hWnd_fileDialog  )  )  goto  errLabel;

		  //  pProcInfo->bWndModal_fileDialog  =  bFileDialog;
		  pQyMc->gui.hWnd_fileDialog  =  hDlg;
		  pQyMc->gui.dwStartTickCnt_fileDialog  =  GetTickCount(  );
	}

	iErr  =  0;
errLabel:
	return  iErr;
}




  __declspec(  dllexport  )  void  *  qyWnd_getGuiData(  void  *  pDlg  )
{
	if  (  !pDlg  )  return  NULL;
	return  (  (  CQyWnd  *  )pDlg  )->getGuiData(  );
}


  __declspec(  dllexport  )  void  *  qyWnd_getVar(  void  *  pDlg  )
{
	if  (  !pDlg  )  return  NULL;
	return  (  (  CQyWnd  *  )pDlg  )->getVar(  );
}

 __declspec(  dllexport  )  HWND  qyWnd_getHwnd(  void  *  pDlg  )
{
	if  (  !pDlg  )  return  NULL;
	return  (  (  CQyWnd  *  )pDlg  )->m_hWnd;
}

 __declspec(  dllexport  )  BOOL  qyWnd_Attach(  void  *  pDlgParam,  HWND hWndNew  )
{
	if  (  !pDlgParam  )  return  FALSE;
	if  (  !IsWindow(  hWndNew  )  )  return  FALSE;

	CQyWnd  *  pDlg  =  (  CQyWnd  *  )pDlgParam;

	//  SetWindowLong(  hWndNew,  GWLP_USERDATA,  (  LONG_PTR  )pDlg  );
	SetWindowLongPtr(  hWndNew,  GWLP_USERDATA,  (  LONG_PTR  )pDlg  );
	pDlg->m_hWnd  =  hWndNew;

	return  TRUE;
}

  __declspec(  dllexport  )  void  freeQyWnd(  void  *  pWndParam  )
 {
	 if  (  pWndParam  )  {
		 CQyWnd  *  pWnd  =  (  CQyWnd  *  )pWndParam;
		 if  (  IsWindow(  pWnd->m_hWnd  )  )  {
			 MACRO_qyAssert(  0,  (TCHAR*)_T(  "Serious error: freeQyWnd, hWnd is still alive"  )  );
		 }

		 delete  (  CQyWnd  *  )pWnd;
	 }
 }

 

 MIS_CNT  *  getMisCntByName(  MC_VAR_common  *  pProcInfo,  LPCTSTR  misServName  )
{
	 int						iErr								=	-1;
	 //QY_MC					*	pQyMc								=	(  QY_MC  *  )pQyMcParam;
	 int						i;

	 if  (  !pProcInfo  )  return  NULL;

	 return  (  MIS_CNT  *  )pProcInfo->getMisCntByName(  misServName  );

}


 MIS_CNT  *  getMisCntByIndex(  void  *  p0,  MC_VAR_isCli  *  pProcInfo,  int  iIndex  )
{
	if  (  !pProcInfo  )   return  NULL;
	return  (  MIS_CNT  *  )pProcInfo->getMisCntByIndex(  iIndex  );

#if  0
	if  (  iIndex  <  0  ||  iIndex  >  mycountof(  pProcInfo->misCnts  )  )  return  NULL;

	return  &pProcInfo->misCnts[iIndex];
#endif

}


 int  getMisCntIndexByName(  void  *  p0,  MC_VAR_isCli  *  pProcInfo,  LPCTSTR  misServName  )
{
	int							iErr							=	-1;
	int							i								=	0;

	if  (  !misServName  )  return  -1;

#if  0
	for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  {
		if  (  !lstrcmpi(  pProcInfo->misCnts[i].cfg.misServName,  misServName  )  )  return  i;
	}
#endif
	for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  {
		MIS_CNT  *  pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  i  );
		if  (  !pMisCnt  )  continue;
		//
		if  (  !lstrcmpi(  pMisCnt->cfg.misServName,  misServName  )  )  return  i;
	}


//  errLabel:
	return  -1;
}

 
 


 MIS_CHANNEL  *  getChannelByType(  MIS_CNT  *  pMisCnt,  unsigned  int  uiChannelType  )
{
	int		i;
	
	if  (  !pMisCnt  )  return  NULL;

	if  (  !uiChannelType  )  return  &pMisCnt->channels[0];

	for  (  i  =  0;  i  <  mycountof(  pMisCnt->channels  );  i  ++  )  {
		 if  (  pMisCnt->channels[i].uiType  ==  uiChannelType  )  return  &pMisCnt->channels[i];
	}

	return  &pMisCnt->channels[0];

}



 BOOL  bChannelOk(  MIS_CHANNEL  *	pChannel,  Param_dbg  *  pParam  )
{
	if  (  !pChannel  )  return  FALSE;
	MIS_CNT  *  pMisCnt  =  pChannel->pMisCnt;  
	if  (  !pMisCnt  )  return  FALSE;	
	MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  FALSE;	
	QY_MC  *  pQyMc  =  pProcInfo->pQyMc;  
	if  (  !pQyMc  )  return  FALSE;

	//
	Param_dbg  param;
	if (pParam) {
		param.m_bShowInfo = pParam->m_bShowInfo;
		param.m_pHint = pParam->m_pHint;
	}

	//
	if  (  pChannel->bSessionOpen  )  {
		DWORD	dwTickCnt  =  myGetTickCount(  NULL  );
		//
		int  iDiffInMs_startChannel  =  dwTickCnt  -  pChannel->status.dwTickCnt_startChannel;			
		int  iDiffInMs_lastStartToRecv  =  dwTickCnt  -  pChannel->status.dwTickCnt_lastStartToRecv;
		int  iDiffInMs_lastEndSending  =  dwTickCnt  -  pChannel->status.dwTickCnt_lastEndSending;

		//
		if  (  pChannel->uiType  !=  CONST_channelType_talking  )  {
			//
			if  (  abs(iDiffInMs_startChannel)  >  5000  )  {
				if  (  abs(iDiffInMs_lastStartToRecv)  >  pQyMc->cfg.iTimeoutInMs_channelIdle_others				
					&&  abs(iDiffInMs_lastEndSending)  >  pQyMc->cfg.iTimeoutInMs_channelIdle_others  )			
				{
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Channel %s timeout, idle too long, iTimeoutInMs_channelsIdle_others %d"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  ),  pQyMc->cfg.iTimeoutInMs_channelIdle_others  );
					return  FALSE;
				}
			}
			//
			}
		else  {
			  if  (  abs(iDiffInMs_startChannel  )  >  5000  )  {
				  //
				  if  (  abs(iDiffInMs_lastStartToRecv)  >  pQyMc->cfg.iTimeoutInMs_channelIdle_recv_talk  )  						  
				  {				
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Channel %s timeout, idle too long, iTimeoutInMs_channelsIdle_recv_talk %d"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  ),  pQyMc->cfg.iTimeoutInMs_channelIdle_recv_talk  );
					  return  FALSE;
				  }

				  //  2012/05/21.以下为了防止误判,用另一个变量做了一个辅助. 这样让判断至少在超时2次后才生效
				  BOOL	tmp_bOk  =  TRUE;
				  if  (  !isQ2Empty(  &pChannel->toSendQ2  )  )  {	//  2012/05/21
					  if  (  abs(iDiffInMs_lastEndSending)  >  pQyMc->cfg.iTimeoutInMs_channelIdle_others  )  {
						  tmp_bOk  =  FALSE;
					  }
				  }
				  if  (  tmp_bOk  )  pChannel->status.dwTickCnt_noSending_start  =  0;
				  if  (  pChannel->status.dwTickCnt_noSending_start  )  {
					  int  iDiffInMs_noSending_start  =  dwTickCnt  -  pChannel->status.dwTickCnt_noSending_start;
					  if  (  abs(iDiffInMs_noSending_start  )  >  pQyMc->cfg.iTimeoutInMs_channelIdle_others  +  5000  )  {
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Channel %s timeout, haha idle too long, iTimeoutInMs_channelsIdle_others %d"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  ),  pQyMc->cfg.iTimeoutInMs_channelIdle_others  );
						  return  FALSE;
					  }
				  }
				  if  (  !tmp_bOk  )  {
					  if  (  !pChannel->status.dwTickCnt_noSending_start  )  {
						  pChannel->status.dwTickCnt_noSending_start  =  dwTickCnt;
					  }
				  }
			  }
		}	
	}
	
	//  2015/9/11
	if  (  pProcInfo  )  {
		if  (  pProcInfo->status.waitToQuit.dwTickCnt_start  )  {
			//
			showInfo_open0(0, 0, _T("bChannelOk: false, waitToQuit.dwTickCnt_start is not 0"));
			//
			return  FALSE;
		}
	}

	//
#if 0
	if (pMisCnt->servIp_suggested.dwServIp) {
		if (pMisCnt->servIp_suggested.dwServIp != inet_addr(pMisCnt->server.ip)) {
			//
			if (param.m_bShowInfo) {
				TCHAR  tBuf[128];
				char servIp_suggested[128] = "";
				ulIp2Str(pMisCnt->servIp_suggested.dwServIp, servIp_suggested, mycountof(servIp_suggested));
				_sntprintf(tBuf, mycountof(tBuf), _T("bChannelOk: false, dwServIp_suggested %S != serv.ip %S. %s"),
					servIp_suggested, pMisCnt->server.ip, qyGetDesByType1(CONST_channelTypeTable, pChannel->uiType));;
				showInfo_open0(0, param.m_pHint, tBuf);
			}
			//
			return false;
		}
	}
#endif
	if (pMisCnt->server.ip[0]) {
		if (inet_addr(pMisCnt->server.ip) != inet_addr(pChannel->curServer.ip)) {
			//
			if (param.m_bShowInfo) {
				TCHAR  tBuf[128];
				_sntprintf(tBuf, mycountof(tBuf), _T("bChannelOk: false, cnt.ServIp %S != channel.ip %S. %s"),
					pMisCnt->server.ip, pChannel->curServer.ip, qyGetDesByType1(CONST_channelTypeTable, pChannel->uiType));;
				showInfo_open0(0, param.m_pHint, tBuf);
			}
			//
			return false;
		}
	}

	//
	if (pProcInfo->av.hk.portStatus.bDisable_network) {
		showInfo_open0(0, param.m_pHint, _T("bChannelOk: false, bDisable_network true"));
		return  false;
	}

	//

	return  (  !pQyMc->bQuit  &&  pQyMc->bLogon  &&  pChannel->bSessionOpen  &&  !pChannel->status.ulbSessionErr  );

}


 //
 BOOL  bMeOnline(  QY_MC  *  pQyMc  )
{
	BOOL					bRet	=	FALSE;
	//
	if  (  !pQyMc  )  return  FALSE;
	MC_VAR_isCli  *  pVar  =  (  MC_VAR_isCli  *  )pQyMc->get_pProcInfo(  );
	if  (  !pVar  )  return  FALSE;
	if  (  pVar->m_iCtxType  !=  CONST_ctxType_qmc  )  return  FALSE;

	int						i;

	//  2015/07/01
	for  (  i  =  0;  i  <  pVar->ucCnt_misCnts;  i  ++  )  {
		 MIS_CNT  *  pMisCnt  =  getMisCntByIndex(  0,  pVar,  i  );
		 if  (  !pMisCnt  )  continue;
		 //
		 if  (  pMisCnt->cfg.dynCfg.cnt.usCntPort  )  {
			 Param_dbg param;
			 param.m_pHint=(TCHAR*)_T("bMeOnline.364");
			 param.m_bShowInfo = false;
			 //
			 if  (  bChannelOk(  getChannelByType(  pMisCnt,  CONST_channelType_talking  ),  &param  )  )  {
				 bRet  =  TRUE;  goto  errLabel;
			 }
		 }
	}




errLabel:
	return  bRet;

}
 

 //  2013/06/13
 BOOL  bApp_ts(  QY_MC  *  pQyMc  )
 {
	 if  (  !pQyMc  )  return  FALSE;

	 return  pQyMc->ucbApp_ts;

 }


 //  2015/06/02. 是否用3d来实现ts程序. 
 BOOL  bApp_ts_3d(  QY_MC  *  pQyMc  )
 {
	 if  (  !bApp_ts(  pQyMc  )  )  return  FALSE;
	 //
#ifdef  __DEBUG__
		#if  0
			 return  FALSE;
		#endif
#endif
	 //
	 return  TRUE;
 }


 

 //  2007/10/07
 BOOL  bMisCntOnline(  QY_MC  *  pQyMc,  MIS_CNT  *  pMisCnt  )
{
	if  (  !pMisCnt  )  return  FALSE;

	if  (  pMisCnt->cfg.dynCfg.cnt.usCntPort  )  {
		Param_dbg param;
		param.m_pHint=(TCHAR*)_T("bMisCntOnline.415");
		param.m_bShowInfo = false;
		//
		if  (  bChannelOk(  getChannelByType(  pMisCnt,  CONST_channelType_talking  ),  &param  )  )  return  TRUE;
	}

	return  FALSE;
}


 int  myCompare_sortMessengerTreeByKey(  const  void  *  p1,  const  void  *  p2  )
{
	DISPLAYEDELEM_MESSENGER_TREE	*	pElem1  =  *(  DISPLAYEDELEM_MESSENGER_TREE  **  )p1;
	DISPLAYEDELEM_MESSENGER_TREE	*	pElem2  =  *(  DISPLAYEDELEM_MESSENGER_TREE  **  )p2;
	_int64								iDiff	=	0;				

	if  (  pElem1->pMisCnt  !=  pElem2->pMisCnt  )  return  (  MIS_CNT  *  )pElem1->pMisCnt  -  (  MIS_CNT  *  )pElem2->pMisCnt;
	//
	if  (  pElem1->uiType  !=  pElem2->uiType  )  return  pElem1->uiType  -  pElem2->uiType;
	//
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

int  addToDisplayedObjQ(  MC_CTX_DISPLAYEDWND  *  pCtx,  QMOBJQ_PARAM_MISCLIENT  *  pParam,  HWND  hWnd,  int  iObjId  )
{
	return  addToDisplayedObjQ(  pCtx,  pParam,  hWnd,  (  HTREEITEM  )iObjId  );		//  ÒòÎªÕâ2¸öÖµ´óÐ¡Ò»Ñù£¬¹ÊÔÝÊ±ÓÃÕâ¸öÀ´´úÌæ
}

 int  addToDisplayedObjQ(  MC_CTX_DISPLAYEDWND  *  pCtx,  QMOBJQ_PARAM_MISCLIENT  *  pParam,  HWND  hWnd,  HTREEITEM  hItem  )
{
	int									iErr				=		-1;
	MIS_MSG_DISPLAYEDELEM_QMC			msg;

	switch  (  pParam->iObjType  )  {
			case  CONST_objType_me:  {
				  DISPLAYEDELEM_MESSENGER_TREE			elem;
				  //
				  memset(  &elem,  0,  sizeof(  elem  )  );
				  elem.uiType  =  CONST_displayedElemType_meTree;
				  elem.pMisCnt  =  pParam->pMisCnt;
				  elem.hItem  =  hItem;

				  if  (  qPostMsg(  &elem,  sizeof(  elem  ),  &pCtx->displayedElemQ,  _T(  "addToDisplayedObjQ"  )))  goto  errLabel;
				  pCtx->ppDisplayedElems_sortedByKey[pCtx->displayedElemQ.uiQNodes  -  1]  =  (  void  *  )pCtx->displayedElemQ.pRear->qElemMemory.m_pBuf;

				  //
				  //traceLogA(  (char*)  "addToDisplayedObjQ: ÅÅÐòÇ°"  );
				  //  printDisplayedObjQ(  pCtx->ppDisplayedElems_sortedByKey,  pCtx->displayedElemQ.uiQNodes  );

				  qsort(  pCtx->ppDisplayedElems_sortedByKey,  pCtx->displayedElemQ.uiQNodes,  sizeof(  void  *  ),  myCompare_sortMessengerTreeByKey  );

				  //
				  //traceLogA(  (char*)  "addToDisplayedObjQ: ÅÅÐòºó"  );
				  //  printDisplayedObjQ(  pCtx->ppDisplayedElems_sortedByKey,  pCtx->displayedElemQ.uiQNodes  );

				  //  ÎÒ½Úµã²»ÓÃ·¢¸ødisplayQ, ÒòÎªÊµ¼ÊÉÏÕâÖ»ÊÇ¸ömisCntµÄÐèÄâÖ¸³Æ£¬Ò²²»¹Ì¶¨id

				  }				  
				  break;
			case  CONST_objType_messenger:  {
				  DISPLAYEDELEM_MESSENGER_TREE			elem;
				  //				  
				  memset(  &elem,  0,  sizeof(  elem  )  );
				  elem.uiType  =  CONST_displayedElemType_messengerTree;
				  elem.pMisCnt  =  pParam->pMisCnt;
				  elem.idInfo.ui64Id  =  (  (  QY_MESSENGER_INFO  *  )pParam->pClient  )->idInfo.ui64Id;
				  elem.hItem  =  hItem;

				  if  (  qPostMsg(  &elem,  sizeof(  elem  ),  &pCtx->displayedElemQ,  _T(  "addToDisplayedObjQ1"  )))  goto  errLabel;
				  pCtx->ppDisplayedElems_sortedByKey[pCtx->displayedElemQ.uiQNodes  -  1]  =  (  void  *  )pCtx->displayedElemQ.pRear->qElemMemory.m_pBuf;

				  traceLogA(  (char*)  "addToDisplayedObjQ: ÅÅÐòÇ°"  );
				  //  printDisplayedObjQ(  pCtx->ppDisplayedElems_sortedByKey,  pCtx->displayedElemQ.uiQNodes  );

				  qsort(  pCtx->ppDisplayedElems_sortedByKey,  pCtx->displayedElemQ.uiQNodes,  sizeof(  void  *  ),  myCompare_sortMessengerTreeByKey  );

				  traceLogA(  (char*)  "addToDisplayedObjQ: ÅÅÐòºó"  );
				  //  printDisplayedObjQ(  pCtx->ppDisplayedElems_sortedByKey,  pCtx->displayedElemQ.uiQNodes  );

				  traceLogA(  (char*)  "ÏÂÃæÒª·¢¸ødisplayÏß³Ì£¬¸æËßÓÐÕâÃ´Ò»¸öÏÔÊ¾ÔªËØ"  );
				  memset(  &msg,  0,  sizeof(  msg  )  );
				  //
				  msg.uiType  =  CONST_misMsgType_displayedElem_qmc;
				  msg.elemU.uiType  =  CONST_displayedElemType_messengerWnd;
				  msg.elemU.messengerWnd.pMisCnt  =  pParam->pMisCnt;
				  msg.elemU.messengerWnd.idInfo.ui64Id  =  (  (  QY_MESSENGER_INFO  *  )pParam->pClient  )->idInfo.ui64Id;
				  msg.elemU.messengerWnd.hWnd  =  hWnd;

				  if  (   qPostMsgAndTrigger(  &msg,  sizeof(  msg  ),  &(  (  MC_VAR_isCli  *  )pParam->pSci->pVar  )->displayQ,  _T(  "addToDisplayedObjQ 2"  )))  goto  errLabel;

				 }

				 break;
			default:
					break;
	}
					 
	iErr  =  0;
errLabel:
	return  iErr;
}


 int  getMessengerImages(  QY_MC  *  pQyMc,  unsigned  short  usRunningStatus,  int  *  pnImage,  int  *  pnSelectedImage  )
{
	int  nImage,  nSelectedImage;

    switch  (  usRunningStatus  )  {
		    case  CONST_usRunningStatus_online:
				  nImage  =  nSelectedImage  =  pQyMc->cfg.image.normal.nImage_pcNormal;
				  break;
			case  CONST_usRunningStatus_away:
				  nImage  =  nSelectedImage  =  pQyMc->cfg.image.normal.nImage_pcWait;
				  break;
			case  CONST_usRunningStatus_hide:
			case  CONST_usRunningStatus_offline:
			default:
				    nImage  =  nSelectedImage  =  pQyMc->cfg.image.offline.nImage_pcNormal;
					break;
	}				   

	if  (  pnImage  )  *pnImage  =  nImage;
	if  (  pnSelectedImage  )  *pnSelectedImage  =  nSelectedImage;

	return  0;
}


 void  myPostQuitMessage(  int nExitCode  )
{
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "myPostQuitMessage called"  )  );
#endif
	PostQuitMessage(  nExitCode  );
}


  //  2014/05/31
 //BOOL  tmpF_bViewRemoteVideo(  VW_rule_messengerCmd  *  pCmd,  unsigned  int  uiObjType,  unsigned  short  usIndex_obj  )
 BOOL  tmpF_bViewRemoteVideo(  VW_rule_messengerCmd  *  pCmd,  unsigned  int  uiObjType,  unsigned  short  usIndex_obj,  unsigned  short  usHelp_subIndex  )
{
	BOOL  bRet  =  FALSE;
	int		i;

	if  (  !uiObjType  )  return  FALSE;

	for  (  i  =  0;  i  <  mycountof(  pCmd->dynBmpRules  );  i  ++  )  {
		if  (  pCmd->dynBmpRules[i].dynBmp.resObj.uiObjType  ==  uiObjType  )  {
			//  2014/09/02
			if  (  !pCmd->dynBmpRules[i].dynBmp.resObj.usIndex_obj  )  return  TRUE;
			//
			if  (  pCmd->dynBmpRules[i].dynBmp.resObj.usIndex_obj  ==  usIndex_obj  
				&&  pCmd->dynBmpRules[i].dynBmp.resObj.usHelp_subIndex  ==  usHelp_subIndex		//  2016/07/23
				)  
			{
				return  TRUE;		 
			}
		}
	}

	return  FALSE;
}


 //
 int  tmpF_setViewRemoteVideo(  DYN_BMP_RULE  *  pDynBmp,  BOOL  bView,  VW_rule_messengerCmd  *  pCmd  )
{
	int		iErr	=	-1;
	int		i;

	if  (  !pDynBmp->dynBmp.resObj.uiObjType  )  return  -1;

	if  (  tmpF_bViewRemoteVideo(  pCmd,  pDynBmp->dynBmp.resObj.uiObjType,  pDynBmp->dynBmp.resObj.usIndex_obj,  pDynBmp->dynBmp.resObj.usHelp_subIndex  )  )  {
		//
		if  (  bView  )  return  0;
		//
		for  (  i  =  0;  i  <  mycountof(  pCmd->dynBmpRules  );  i  ++  )  {
			 #if  0
				  if  (  pCmd->dynBmpRules[i].dynBmp.resObj.uiObjType  ==  pDynBmp->dynBmp.resObj.uiObjType				
					  &&  pCmd->dynBmpRules[i].dynBmp.resObj.usIndex_obj  ==  pDynBmp->dynBmp.resObj.usIndex_obj  )		 
			 #endif
			 //  2016/07/24
			 if  (  isSame_resObj(  &pCmd->dynBmpRules[i].dynBmp.resObj,  &pDynBmp->dynBmp.resObj  )  )
			 {
				 memset(  &pCmd->dynBmpRules[i],  0,  sizeof(  pCmd->dynBmpRules[i]  )  );
				 continue;
			 }
		 }
		return  0;
	}

	//
	if  (  !bView  )  return  0;

	for  (  i  =  0;  i  <  mycountof(  pCmd->dynBmpRules  );  i  ++  )  {
		if  (  !pCmd->dynBmpRules[i].dynBmp.resObj.uiObjType  )  {
			 //
			 break;
		 }
	}
	if  (  i  ==  mycountof(  pCmd->dynBmpRules  )  )  return  -1;

	memcpy(  &pCmd->dynBmpRules[i],  pDynBmp,  sizeof(  pCmd->dynBmpRules[i]  )  );

	return  0;
}


 int  tmpF_setViewRemoteVideo(  unsigned  int  uiObjType,  unsigned  short  usIndex_obj,  unsigned  char  ucbSaveVideo,  BOOL  bView,  VW_rule_messengerCmd  *  pCmd  )
 {
	 DYN_BMP_RULE	dynBmp;
	 memset(  &dynBmp,  0,  sizeof(  dynBmp  )  );
	 dynBmp.dynBmp.resObj.uiObjType  =  uiObjType;
	 dynBmp.dynBmp.resObj.usIndex_obj  =  usIndex_obj;
	 dynBmp.ucbSaveVideo  =  ucbSaveVideo;	//  2014/08/04

	 return  tmpF_setViewRemoteVideo(  &dynBmp,  bView,  pCmd  );
 }

  //  2014/06/04
 BOOL  isEmpty_ROUTE_sendLocalAv(  ROUTE_sendLocalAv  *  pRoute  )
 {
	 BOOL  bRet  =  FALSE;

	 if  (  pRoute->videoConference_idInfo_to.ui64Id  )  goto  errLabel;
	 if  (  pRoute->route.idInfo_to.ui64Id  )  goto  errLabel;
	 int  i;
	 for  (  i  =  0;  i  <  mycountof(  pRoute->route.mems_to  );  i  ++  )  {
		  if  (  pRoute->route.mems_to[i].idInfo.ui64Id  )  goto  errLabel;
	 }

	 bRet  =  TRUE;
errLabel:

	 return  bRet;
 }


 #if  10
 


#endif





 
//
int  calc_me_bgWall_rect(  DLG_talk_layout  *  pLayout,  int  iW_wallMem,  int  iH_wallMem,  int  *  piW_meDesc,  int  *  piH_meDesc,  int  *  piW_bgWall,  int  *  piH_bgWall  )
{
	int  iErr  =  -1;
	int  iW_meDesc  =  0,  iH_meDesc  =  0;
	int			iW_bgWall						=	0;				//  2014/10/01
	int			iH_bgWall						=	0;				//  2014/10/01
	int			iW_bgWallMem					=	0;
	int			iH_bgWallMem					=	0;

	float  fMe  =  0.15;	//0.18;
	

	//
	iW_meDesc  =  iW_wallMem  /  3;		
	iH_meDesc  =  iH_wallMem  *  fMe;
	
	//	
	int  iRows  =  1;		
	int  iCols  =  1;
	if  (  pLayout->ucbShowBgWall  )  {
			 iRows  =  pLayout->bgWallLayoutCfg.usRows_bg;
			 if  (  !iRows  )  iRows  =  1;
			 //
			 iCols  =  pLayout->bgWallLayoutCfg.usCols_bg  +  iRows;
			 iW_meDesc  =  iW_wallMem  /  (  float  )iCols  *  iRows;		 
	}


	//
	float  fx  =  iW_meDesc  /  320.;	
	float  fy  =  iH_meDesc  /  240.;
	float  f  =  min(  fx,  fy  );	
	
	iW_meDesc  =  f  *  320;	
	iH_meDesc  =  f  *  240;
	
	//
			 //
		 if  (  pLayout->ucbShowBgWall  )  {
			 //  iW_bgWall  =  iW_right  /  (  float  )iCols  *  (  iCols  -  iRows  );
			 iW_bgWall  =  iW_wallMem  -  iW_meDesc;
			 iH_bgWall  =  iH_meDesc;

			 iW_bgWallMem  =  iW_bgWall  /  (  float  )(  iCols  );
			 iH_bgWallMem  =  iH_bgWall  /  (  float  )(  iRows  );

			 float  fx  =  iW_bgWallMem  /  320.;
			 float  fy  =  iH_bgWallMem  /  180.;	//240.;

			 float  f   =  min(  fx,  fy  );

			 iW_bgWallMem  =  f  *  320.;
			 iH_bgWallMem  =  f  *  180.;	//  240.;

			 if  (  iRows  ==  1  )  {
#if  0
				 iH_bgWallMem  =  iH_meDesc;
				 iW_bgWallMem  =  iH_bgWall  /  9  *  16;
#endif
				 //
				 iW_bgWallMem  =  iW_meDesc;
				 iH_bgWallMem  =  iW_bgWallMem  /  16  *  9;
			 }

			 iW_bgWall  =  iW_bgWallMem  *  (  iCols  -  iRows  );
			 iH_bgWall  =  iH_meDesc;

			 pLayout->bgWallLayout.iW_bgWallMem  =  iW_bgWallMem;
			 pLayout->bgWallLayout.iH_bgWallMem  =  iH_bgWallMem;	
		 }



	iErr  =  0;
errLabel:
	
	if  (  !iErr  )  {
		if  (  piW_meDesc  )  *piW_meDesc  =  iW_meDesc;
		if  (  piH_meDesc  )  *piH_meDesc  =  iH_meDesc;
		if  (  piW_bgWall  )  *piW_bgWall  =  iW_bgWall;
		if  (  piH_bgWall  )  *piH_bgWall  =  iH_bgWall;
	}
	return  iErr;

}


//
int  calc_other_rect(  DLG_talk_layout  *  pLayout,  float fZoomFactor,  int  iW_wallMem,  int  iH_wallMem,  int  *  piW_otherDesc,  int  *  piH_otherDesc  )
{
	int  iW_otherDesc,  iH_otherDesc;
	//
	float  fVal  =  3;
	//
	fVal  =  5;

	//
	if (  fZoomFactor > 0.01  &&  fZoomFactor  <  1.0000001  ) {
		fVal = 1. / fZoomFactor;
	}

	//
#ifdef  __DEBUG__
		//fVal = 1;
#endif
	//
	iW_otherDesc  =  iW_wallMem  /  fVal;		
	iH_otherDesc  =  iH_wallMem  /  fVal;
	//
	float  fW  =  1024.;
	float  fH  =  768.;
	//
	fW  =  1280;
	fH  =  720;
	//
	fW = 1920;
	fH = 1080;

	//
	float  fx  =  iW_otherDesc  /  fW;	
	float  fy  =  iH_otherDesc  /  fH;
	float  f  =  min(  fx,  fy  );	
	
	iW_otherDesc  =  f  *  fW;	
	iH_otherDesc  =  f  *  fH;

	if  (  piW_otherDesc  )  *piW_otherDesc  =  iW_otherDesc;
	if  (  piH_otherDesc  )  *piH_otherDesc  =  iH_otherDesc;

	return  0;
}


//  2014/12/10
  int  snprintRoute(  ROUTE_sendLocalAv  *  pRoute,  TCHAR  *  tOutput,  unsigned  int  cnt  )
{						  
	int		j;
	TCHAR	tBuf[512]	=	_T(  ""  );

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Dst:"  )  );
	if  (  pRoute->videoConference_idInfo_to.ui64Id  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s group %I64u"  ),  tBuf,  pRoute->videoConference_idInfo_to.ui64Id  );
	else  {
		   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u"  ),  tBuf,  pRoute->route.idInfo_to.ui64Id  );
		   if  (  pRoute->route.idInfo_to.ui64Id  )  {
			   for  (  j  =  0;  j  <  mycountof(  pRoute->route.mems_to  )  &&  pRoute->route.mems_to[j].idInfo.ui64Id;  j  ++  )  {
				    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %I64u"  ),  tBuf,  pRoute->route.mems_to[j].idInfo.ui64Id  );												 					
			   }
		   }
	}
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. routeId %d"  ),  tBuf,  pRoute->route.uiMsgRouteId  );

	if  (  tOutput  )  lstrcpyn(  tOutput,  tBuf,  cnt );
	return  0;
}



int  snprintCapImages(  LPCTSTR  hint,  CAP_images_head  *  pImgsHead,  CAP_image  *  pImgMems, int  uiSize_pImgMem,  unsigned  int  uiMaxCnt_imgMems,  TCHAR  *  tOutput,  unsigned int  cnt  )
{
	int  j;
	TCHAR  tBuf[512]  =  _T(  ""  );

	if  (  !hint  )  hint  =  _T(  ""  );


	DWORD  dwTickCnt_now  =  GetTickCount(  );

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  hint  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s cnt %d."  ),  tBuf,  (  int  )pImgsHead->usCnt  );
	for  (  j  =  0;  j  <  uiMaxCnt_imgMems;  j  ++  )  {
		 CAP_IMAGE  *  pImg  =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  j  *  uiSize_pImgMem  );	//&pImgs->mems[j];
		 if  (  !pImg->iW_org  &&  !pImg->iH_org  &&  !pImg->iTaskId  )  continue;
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s mem[%d]: %I64u, %d, org %dX%d, taskId %d, index_player %d, draw_elapse %dms"  ),  tBuf,  j,  pImg->idInfo_sender.ui64Id,  pImg->uiTranNo_openAvDev,  pImg->iW_org,  pImg->iH_org,  pImg->iTaskId,  pImg->playerId.index_player,  dwTickCnt_now  -  pImg->dwTickCnt_lastDrawing  );
	}

	if  (  tOutput  )  lstrcpyn(  tOutput,  tBuf,  cnt );	
	return  0;
}


 __declspec(  dllexport  )  int  qmcApplyForChkingTasks_gui(  QY_MC  *  pQyMc  )	//  2009/09/10
{
	#ifdef  __DEBUG__
			traceLog((TCHAR*)  _T(  "qisApplyForChkingTasks_gui called"  )  );
	#endif

	if  (  pQyMc  )  {
		PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_chkTask,  0  );  
	}

	return  0;
}


 //
 int  chkToApplyForChannel(CCtxQmc* pProcInfo, int  channelType, bool  bForce)
 {
	 int  iErr = -1;

	 bool  bChannelReady = false;
	 QY_Q2* pQ2 = NULL;
	 //	
	 MIS_MSG_applyForChkChannels_qmc		msg_applyForChkChannels;
	 int	dwTickCnt;						dwTickCnt = GetTickCount();
	 
	 //
	 MIS_CHANNEL* pChannel = mynull;

	 //
	 if (!pChannel) {
		 MIS_CNT* pMisCnt = getMisCntByIndex(0, pProcInfo, 0);
		 if (!pMisCnt)  return  -1;
		 pChannel = getChannelByType(pMisCnt, channelType);
		 if (!pChannel)  return  -1;
	 }
	 channelType = pChannel->uiType;

	 //
	 switch (channelType) {
	 case  CONST_channelType_media:
		 bChannelReady = pProcInfo->av.video.bChannelReady;
		 pQ2 = &pProcInfo->mediaQ2;
		 break;

	 case  CONST_channelType_realTimeMedia:
		 bChannelReady = pProcInfo->av.audio.bChannelReady;
		 pQ2 = &pProcInfo->realTimeMediaQ2;
		 break;
	 default:
		 break;
	 }
	 if (!pQ2)  goto  errLabel;

	 //
	 if (!bForce) {
		 if (bChannelReady) {
			 iErr = 0;  goto  errLabel;
		 }

		 //  	
		 if (abs((int)(dwTickCnt - pChannel->status.dwLastTickCnt_applyForChkChannels)) < 2000) {
			 iErr = 0;  goto  errLabel;
		 }
	 }



	 //  traceLogA(  (char*)  "toShareBmp: applyForChkChannels"  );		
	 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("Channel %s not Ready, applyForChkChannels"), qyGetDesByType1(CONST_channelTypeTable, channelType));


	 //
	 memset(&msg_applyForChkChannels, 0, sizeof(msg_applyForChkChannels));
	 msg_applyForChkChannels.uiType = CONST_misMsgType_applyForChkChannels_qmc;
	 msg_applyForChkChannels.pMisCnt = pChannel->pMisCnt;

	 //		
	 if (q2PostMsgAndTrigger(&msg_applyForChkChannels, sizeof(msg_applyForChkChannels), pQ2, _T("chkToApplyForChannel"))) {
		 showNotification(0, 0, 0, 0, 0, 0, _T("chkToApplyForChannels: applyForChkChannels failed"));
	 }

	 //					   	
	 pChannel->status.dwLastTickCnt_applyForChkChannels = dwTickCnt;



	 //  2015/05/12
#ifdef  __DEBUG__
		//traceLog((TCHAR*)  _T(  "toShareVideo_post: bVideoChannelReady false. skipped"  )  );
#endif


	 iErr = 0;

 errLabel:
	 return  iErr;
 }



 //




 //
 BOOL  canShareScreen(  MC_VAR_isCli  *  pProcInfo  )
{
	//
	int								i;

	if  (  !pProcInfo  )  return  FALSE;
	if  (  !pProcInfo->pSharedObjSyncs  )  return  FALSE;

	for  (  i  =  1;  i  <  pProcInfo->cfg.usMaxCnt_pSharedObjs;  i  ++  )  {
		 QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  i  );
		 //  if  (  !pProcInfo->pSharedObjs[i].bUsed  )  return  TRUE;
		 if  (  !pSharedObj->bUsed  )  return  TRUE;
	}

	return  FALSE;
}



 BOOL  canRemoteAssist(  MC_VAR_isCli  *  pProcInfo  )
{
	BOOL							bRet				=	FALSE;
	int								i;
	BOOL							bFull				=	TRUE;

	if  (  !pProcInfo  )  return  FALSE;
	if  (  !pProcInfo->pSharedObjSyncs  )  return  FALSE;

	for  (  i  =  1;  i  <  pProcInfo->cfg.usMaxCnt_pSharedObjs;  i  ++  )  {
		 QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  i  );
		 if  (  !pSharedObj->bUsed  )  {
			 bFull  =  FALSE;
			 continue;
		 }
		 if  (  pSharedObj->bRemoteAssist  )  return  FALSE;		//  Ô¶³ÌÐ­ÖúÖ»ÄÜÒ»¸ö¡£ÒòÎªÊó±ê¼üÅÌÖ»ÓÐÒ»¸ö
	}

	return  !bFull;
}

//  2014/06/11
  BOOL  bRemoteAssistExists(  MC_VAR_isCli  *  pProcInfo  )
{
	BOOL							bRet				=	FALSE;
	int								i;
	BOOL							bFull				=	TRUE;

	if  (  !pProcInfo  )  return  FALSE;
	if  (  !pProcInfo->pSharedObjSyncs  )  return  FALSE;

	for  (  i  =  1;  i  <  pProcInfo->cfg.usMaxCnt_pSharedObjs;  i  ++  )  {
		 QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  i  );
		 if  (  !pSharedObj->bUsed  )  {
			 bFull  =  FALSE;
			 continue;
		 }
		 if  (  pSharedObj->bRemoteAssist  )  return  TRUE;		//  Ô¶³ÌÐ­ÖúÖ»ÄÜÒ»¸ö¡£ÒòÎªÊó±ê¼üÅÌÖ»ÓÐÒ»¸ö
	}

	return  FALSE;
}


  BOOL  canRemotePtzControl(  MC_VAR_isCli  *  pProcInfo  )
 {
	 BOOL	bRet	=	FALSE;
	 	 
	 QY_MC				*	pQyMc			=	pProcInfo->pQyMc;
	 unsigned  int			uiChannelType	=	CONST_channelType_media;	
	 MIS_CHANNEL		*	pChannel		=	NULL;
	 
	 if  (  !pProcInfo  )  return  FALSE;
	 MIS_CNT			*	pMisCnt			=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 if  (  !pMisCnt  )  goto  errLabel;
	 
#ifdef  __DEBUG__
		#if  0
			 traceLog((TCHAR*)  _T(  "For test, canRemotePtzControl(  ) returns TRUE"  )  );
			 bRet  =  TRUE;  goto  errLabel;
		#endif
#endif

	 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  goto  errLabel;
	
	 {
		 Param_dbg param;
		 param.m_pHint=(TCHAR*)_T("canRemotePtzControl.1031");
		 //
		 if (!bChannelOk(pChannel, &param))  goto  errLabel;
	 }

	 //
	 bRet  =  TRUE;
errLabel:
	 return  bRet;

 }



 


