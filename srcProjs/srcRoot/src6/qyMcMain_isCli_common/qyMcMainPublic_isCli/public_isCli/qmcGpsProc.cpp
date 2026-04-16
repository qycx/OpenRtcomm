

#include	"stdafx.h"
#include	<stddef.h>
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"gpsCommProc.h"
#include	"qmcGpsProc.h"

#include	"qmcVideoCapture_isCli.h"

#include	"qyComPortEx.h"
#include	"dlgtalkproc.h"
#include	"dlgDynBmpsProc.h"
#include	"isCliHelpPublic.h"

#include	"qmcCommFunc_isCli.h"


int parseGpsStr(  void  *  pCComPortEx,  char  *  str  )
{
	CComPortEx  *  pPort  =  (  CComPortEx  *  )pCComPortEx;
	//
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	if  (  pProcInfo->cfg.ucbTestGps  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "parseGpsStr failed: ucbTestGps is true"  )  );
		#endif
		return  -1;
	}

	OutputDebugString(  _T(  "parseGpsStr:["  )  );
	OutputDebugString(  CQyString(  str  )  );
	OutputDebugString(  _T(  "]\n"  )  );


	if  (  pProcInfo->cfg.debugStatusInfo.ucbShowVPktInputInfo  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "parseGpsStr [%s]"  ),  CQyString(  str  )  );
	}

	//
	char  *  pStart  =  str;

	for  (  ; pStart  &&  *pStart; pStart ++  ){

		myGPS_POSITION	pos;
		memset(  &pos,  0,  sizeof(  pos  )  );

		pStart  =  strchr(  pStart,  '$'  );
		if  (  !pStart  )  return  -1;
		char  *  pCR  =  strchr(  pStart,  0x0d  );
		char  *  pLF  =  strchr(  pStart,  0x0a  );
		if  (  !pCR  ||  !pLF  )  return  -1;

		if  (  pLF  !=  pCR  +  1  )  {
			return  -1;
		}
		char  msg[512];
		int len = pCR  -  pStart;
		if  (  len  >=  sizeof(  msg  )  )  return  -1;
		memcpy(  msg,  pStart,  len  );
		msg[len]  =  0;

		#define  CONST_str_gprmc  "$GPRMC"
		if  (  strnicmp(  msg, CONST_str_gprmc,  strlen(  CONST_str_gprmc  )  )  )  continue;

		OutputDebugString(  _T(  "msg:["  )  );
		OutputDebugString(  CQyString(  msg  )  );
		OutputDebugString(  _T(  "]\n"  )  );

		char  *  p  =  strchr(  msg,  ','  );
		if  (  !p  )  continue;
		p  ++;

		char  *  pTime;
		pTime  =  p;
		int hour,min,sec;
		char temp[9];
		memset(  temp, 0, 9  );
		memcpy(  temp,  pTime,  2  );
		memcpy(  temp + 3,  pTime + 2,  2  );
		memcpy(  temp + 6,  pTime + 4,  2  );
		hour  =  atoi(  temp  );
		min  =  atoi(  temp + 3  );
		sec  =  atoi(  temp + 6  );

		char  buf[256];
		TCHAR  tBuf[256];
		_sntprintf(  tBuf,  sizeof(  tBuf  ) / sizeof(  tBuf[0]  ),  _T(  "%d:%d:%d"  ),  hour,  min,  sec  );
		OutputDebugString(  tBuf  );  OutputDebugString(  _T(  "\n"  )  );

		//
		pos.stUTCTime.wHour  =  hour;
		pos.stUTCTime.wMinute  =  min;
		pos.stUTCTime.wSecond  =  sec;

		//
		char statusStr[2];
		p  =  strchr(  p,  ','  );
		if  (  !p  ) continue;
		p  ++;
		statusStr[0]  =  *p;
		statusStr[1]  =  0;

		p  =  strchr(  p,  ','  );
		if  (  !p  )  continue;
		p  ++;

		my_Latitude	la;

		safeStrnCpy(  p,  buf,  3  );
		la.dd  =  atol(  buf  );
		p  +=  2;
		safeStrnCpy(  p,  buf,  3  );
		la.mm  =  atol(  buf  );
		p  +=  3;
		safeStrnCpy(  p,  buf,  5  );
		la.ss100  =  atol(  buf  )  *  60  /  100;

		//
		pos.dblLatitude  =  la.dd  +  la.mm  /  60.  +  la.ss100  /  100.  /  3600.;

		//
		char  cNS;

		p  =  strchr(  p,  ','  );
		if  (  !p  )  continue;
		p  ++;
		cNS  =  *p;

		//
		switch  (  cNS  )  {
				case  'N':
					  //  Positive numbers indicate north latitude
					  break;
				case  'S':
					  pos.dblLatitude  =  -1  *  pos.dblLatitude;
					  break;
				default:
						//  error
					    continue;
						break;
		}

		//
		p  =  strchr(  p,  ','  );
		if  (  !p  )  continue;
		p  ++;

		my_Longitude	lo;

		safeStrnCpy(  p,  buf,  4  );
		lo.ddd  =  atol(  buf  );
		p  +=  3;
		safeStrnCpy(  p,  buf,  3  );
		lo.mm  =  atol(  buf  );
		p  +=  3;
		safeStrnCpy(  p,  buf,  5  );
		lo.ss100  =  atol(  buf  )  *  60  /  100;

		//
		pos.dblLongitude  =  lo.ddd  +  lo.mm  /  60.  +  lo.ss100  /  100.  /  3600.;

		//
		char  cEW;

		p  =  strchr(  p,  ','  );
		if  (  !p  )  continue;
		p  ++;

		cEW  =  *p;

		switch  (  cEW  )  {
				case  'E':
					  //  Positive numbers indicate east longitude
					  break;
				case  'W':
					  pos.dblLongitude  =  -1  *  pos.dblLongitude;					  
					  break;
				default:
						//  error
						continue;
						break;
		}


		//
		OutputDebugString(  _T(  "finished\n"  )  );

		DWORD	dwTickCnt	=	GetTickCount(  );
		int		iDiff		=	dwTickCnt  -  pPort->m_var.dwTickCnt_toShareGps;
		if  (  iDiff  <  1000  )  {
			if  (  pProcInfo->cfg.debugStatusInfo.ucbShowVPktInputInfo  )  {
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "parseGpsStr, iElapse %dms, too small, skipped"  ),  iDiff  );
			}
			//
			}
		else  {
			  //
			  QY_SHARED_OBJ	*	pSharedObj	=	NULL;
			  int					iIndex_sharedObj	=	pPort->m_var.iUsrData;
			  if  (  iIndex_sharedObj  )  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
			  //
			  if  (  pSharedObj  )  {
				  toShareGps(  pProcInfo,  pPort,  0,  &pos,  pSharedObj,  NULL,  (  MIS_MSGU  *  )pPort->m_var.pMsgBuf  );
			  }

			  //  2012/05/24
			  pPort->m_var.dwTickCnt_toShareGps  =  dwTickCnt;
		}

		//
		setGpsPos(  pPort,  &pos  );		

	}

		return  0;
}



int  getGpsPos(  void  *  pComPortEx,  myGPS_POSITION  *  pPos,  DWORD  *  pdwTickCnt_modified  )
{
	CComPortEx  *  pPort  =  (  CComPortEx  *  )pComPortEx;
	if  (  !pPort  )  return  -1;

	CQySyncObj	syncObj;

	if  (  syncObj.sync(  CONST_mutexName_syncComPort  )  )  return  -1;

	memcpy(  pPos,  &pPort->m_var.gpsPos,  sizeof(  *pPos  )  );
	*pdwTickCnt_modified  =  pPort->m_var.dwTickCnt_modified_gpsPos;

	return  0;
}


 int  toShareGps(  void  *  pMC_VAR_isCli,  void  *  pComPortEx,  int  iSampleTimeInMs,  void  *  pmyGPS_POSITION,  QY_SHARED_OBJ  *  pSharedObj,  BOOL  *  pbHaveMsgrs_sendLocalAv,  MIS_MSGU  *  pMsgBuf  )
{
	MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pMC_VAR_isCli;
	 myGPS_POSITION		*	pGpsPos						=	(  myGPS_POSITION  *  )pmyGPS_POSITION;

	 int					iErr						=	-1;
	 CComPortEx			*	pPort						=	(  CComPortEx  *  )pComPortEx;
	 if  (  !pPort  )  return  -1;

	 MACRO_prepareForTran(  );

	 unsigned  int			uiChannelType				=	CONST_channelType_media;
	 unsigned  char				ucbNeedShowFrameInfo		=	FALSE;



	SHARED_OBJ_USR	*	pSharedObjUsr	=	NULL;
	if  (  !pSharedObj  )  goto  errLabel;
	pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
	if  (  !pSharedObjUsr  )  goto  errLabel;

	//
	if  (  pPort->m_var.tLastTime_sendGps  !=  tStartTran  )  {		//  表明是一秒的开始
		pPort->m_var.tLastTime_sendGps  =  tStartTran;

		 //  定期向客户端下发帧速信息		
		if  (  (  int  )(  tStartTran  -  pPort->m_var.tLastTime_showFrameInfo  )  >  pProcInfo->cfg.usNeedShowFrameInfoIntervalInS  )  {
			 //
			 ucbNeedShowFrameInfo  =  TRUE;
		 }
	}


	 //
	 if  (  !pProcInfo->av.video.bChannelReady  )  {
		static  DWORD	sdwTickCnt_applyForChkChannels	=	0;
		//
		if  (  true )
		{
					   MIS_CNT							*	pMisCnt		=	NULL;
					   MIS_MSG_applyForChkChannels_qmc		msg_applyForChkChannels;
					   int	dwTickCnt;						dwTickCnt  =  GetTickCount(  );
					   int									i;
					   //  CQyQ2Help								q2Help;

					   if  (  dwTickCnt  -  sdwTickCnt_applyForChkChannels  >  4000  )  {
						   //for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
						   for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
						   {
							   pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  i  );//&pProcInfo->misCnts[i];
							   if  (  !pMisCnt  )  continue;
							   //
							   if  (  !pMisCnt->cfg.dynCfg.cnt.usCntPort  )  continue;

							   //  traceLogA(  "toShareBmp: applyForChkChannels"  );
							   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "toShareGps: media Channel not Ready, applyForChkChannels"  )  );

							   //
							   memset(  &msg_applyForChkChannels,  0,  sizeof(  msg_applyForChkChannels  )  );
							   msg_applyForChkChannels.uiType  =  CONST_misMsgType_applyForChkChannels_qmc;
							   msg_applyForChkChannels.pMisCnt  =  pMisCnt;
							   //
							   if  (  q2PostMsgAndTrigger(  &msg_applyForChkChannels,  sizeof(  msg_applyForChkChannels  ),  &pProcInfo->mediaQ2,  _T(  "toShareGps"  ))) {
								   showNotification(  0,  0,  0,  0,  0,  0,  _T(  "toShareGps: applyForChkChannels failed"  )  );
							   }
						   }
						   sdwTickCnt_applyForChkChannels  =  dwTickCnt;
					   }
				   
		}		  
	
		//  
		iErr  =  0;  goto  errLabel;
	}


	 unsigned  char			ucFlg						=	CONST_commFlg_routeTalkData;	//  0;


	 TRANSFER_GPS_DATA	req;
	 memset(  &req,  0,  sizeof(  req  )  );
	 req.uiType  =  CONST_imCommType_transferGpsData;
	 
	 TRANSFER_GPS_dataMem	*	pMem	=	&req.mems[0];
	 pMem->iLaInM10000f  =  pGpsPos->dblLatitude  *  60  *  10000;
	 pMem->iLoInM10000f  =  pGpsPos->dblLongitude  *  60  *  10000;
	 req.usCnt  =  1;


	 TRANSFER_GPS_DATA  *  pReq  =  &req;
	 //  2010/09/12				  
	 if  (  !pReq->usCnt  )  {	
		 //  traceLog((TCHAR*)  _T(  "toShareAudio failed: req.usCnt is 0"  )  );
		 goto  errLabel;
	 }

	 //  2010/09/12
	 if  (  ucbNeedShowFrameInfo  )  {
		 ucFlg  |=  CONST_commFlg_routeTalkData;		
		 pReq->tLastTime_showFrameInfo_020534  =  pPort->m_var.tLastTime_showFrameInfo;								//  设置标记						
		 //
		 pPort->m_var.tLastTime_showFrameInfo  =  tStartTran;												
		 //
		 #ifdef  __DEBUG__
				 qyShowInfo1(  CONST_qyShowType_debug,  0,  (char*)"",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "send gps, NeedShowFrameInfo"  )  );
		 #endif
	 }


	 int  lenInBytes;

	 lenInBytes  =  sizeof(  TRANSFER_GPS_DATA  );
	 //
	 unsigned  char		ucbHaveMsgrs_sendLocalAv;	ucbHaveMsgrs_sendLocalAv  =  FALSE;
	 unsigned  char		ucbFixedRate;				ucbFixedRate  =  FALSE;		
	 MIS_CNT			*	pMisCnt;					pMisCnt  =	NULL;		


	 pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  0  );
	 if  (  pMisCnt  &&  pMisCnt->cfg.dynCfg.cnt.usCntPort  )  {
		 //  
#if  0  //  2014/10/29
		 if  (  pSharedObj->curRoute_sendLocalAv.route.uiMsgRouteId  !=  pSharedObj->route_sendLocalAv.route.uiMsgRouteId  )  {
			 CQySyncObj	syncObj;
			 if  (  !syncObj.sync(  pProcInfo->cfg.mutexName_syncSendAv,  0  )  )  {
				 memcpy(  &pSharedObj->curRoute_sendLocalAv,  &pSharedObj->route_sendLocalAv,  sizeof(  pSharedObj->curRoute_sendLocalAv  )  );
			     #ifdef  __DEBUG__
						 traceLog((TCHAR*)  _T(  "toShareBmp: curRoute_sendLocalAv refreshed"  )  );
				 #endif		
			 }				
		 }
#endif


		#if  0
			 if  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  )  {	//  
				 if  (  postMsg2MgrFunc_mc(  pMisCnt,  &pSharedObj->curRoute_sendLocalAv.route,  CONST_misMsgType_outputTask_toMix,  ucFlg,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  pSharedObjUsr->iTaskId,  0,  (  char  *  )pReq,  lenInBytes,  &pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to,  NULL,  NULL,  0,  uiChannelType,  pMsgBuf,  FALSE  )  )  traceLog((TCHAR*)  _T(  "postMsg2MgrFunc_mc failed"  )  );
				 }							   	
			 else  
		#endif
			 {
#if 1
				 showInfo_open0(  0,  0,  _T(  "toShareGps failed, not finished"  )  );
				 goto errLabel;
#else
				 if  (  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  {		
					 if  (  postMsg2MgrFunc_mc(  pMisCnt,  &pSharedObj->curRoute_sendLocalAv.route,  CONST_misMsgType_outputTask,  ucFlg,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  pSharedObjUsr->iTaskId,  0,  (  char  *  )pReq,  lenInBytes,  0,  NULL,  NULL,  0,  uiChannelType,  pMsgBuf,  FALSE  )  )  traceLog((TCHAR*)  _T(  "postMsg2MgrFunc_mc failed"  )  );		  
				 }
#endif
			 }

	 }


	 iErr  =  0;

errLabel:


	 return  iErr;
 }




   //  hWall要是非0的话,就表明是defer, 不在这个函数里移动位置
 //  int  talkerShadow_procGps(  void  *  pProcInfoParam,  HWND  hDlgTalk,  BOOL  bForceRefreshPos,  int  index_shadow,  void  *  pDlgWall_param,  int  index_wallGpsMgrMem  )
 int  talkerShadow_procGps(  void  *  pProcInfoParam,  HWND  hDlgTalk,  BOOL  bForceRefreshPos,  int  index_shadow,  HWND  hDlgDynBmps_param,  void  *  pDlgDynBmpsVar_param,  int  index_wallGpsMgrMem  )
{
	//  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int			iErr	=	-1;
	MC_VAR_isCli	*	pProcInfo	=	(  MC_VAR_isCli  *  )pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	QY_MC* pQyMc = pProcInfo->pQyMc;// QY_GET_GBUF();


	CHelp_getDlgTalkVar	help_getDlgTalkVar;
	DLG_TALK_var  *  pDlgTalkVar	=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pDlgTalkVar  )  return  -1;
	DLG_TALK_var  &  m_var			=	*pDlgTalkVar;

	if  (  isTalkerShadowMgr(  m_var.addr  )  )  return  -1;
	TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
	if  (  !pTalkerShadow  )  return  -1;


	CHelp_getDlgTalkVar	help_getDlgTalkVar_mgr;
	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var	*	)help_getDlgTalkVar_mgr.getVar(  pTalkerShadow->hMgr  );
	if  (  !pMgrVar  )  goto  errLabel;

	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

	if  (  bForceRefreshPos  )  {
		for  (  index_shadow  =  0;  index_shadow  <  mycountof(  pShadowMgr->shadows  );  index_shadow  ++  )  {
			 if  (  pShadowMgr->shadows[index_shadow].hShadow  ==  hDlgTalk  )  break;
		}
		if  (  index_shadow  ==  mycountof(  pShadowMgr->shadows  )  )  goto  errLabel;
	}
	if  (  index_shadow  <  0  ||  index_shadow  >=  mycountof(  pShadowMgr->shadows  )  )  goto  errLabel;
	if  (  pShadowMgr->shadows[index_shadow].hShadow  !=  hDlgTalk  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "Serious err, index_shadow not correct"  )  );
		#endif
		goto  errLabel;
	}
	if  (  pShadowMgr->shadows[index_shadow].iWndContentType_wall  !=  CONST_qyWndContentType_vWall  )  {
		goto  errLabel;
	}
	HWND	hWall_gps  =  pShadowMgr->shadows[index_shadow].hWall;

	if  (  !bForceRefreshPos  )  {
		if  (  pShadowMgr->viewGps.dwTickCnt_lastRecvd  ==  pTalkerShadow->viewGps.dwTickCnt_lastRecvd  )  {
			iErr  =  0;  goto  errLabel;
		}
	}
	myGPS_POSITION	gpsPos;
	memcpy(  &gpsPos,  &pShadowMgr->viewGps.gpsPos,  sizeof(  gpsPos  )  );
	pTalkerShadow->viewGps.dwTickCnt_lastRecvd  =  pShadowMgr->viewGps.dwTickCnt_lastRecvd;
	
	//  这里最好是先读取墙的坐标类型
	//  CDlgDynBmps  *  pDlgWall  =  NULL;
	DLG_dynBmps_var  *  pDlgDynBmpsVar  =  NULL;
	
	if  (  IsWindow(  hDlgDynBmps_param  )  &&  pDlgDynBmpsVar_param  )  pDlgDynBmpsVar  =  (  DLG_dynBmps_var  *  )pDlgDynBmpsVar_param;
	else  pDlgDynBmpsVar  =  (  DLG_dynBmps_var  *  )getDlgDynBmpsVar(  hWall_gps  );

	if  (  !pDlgDynBmpsVar  )  goto  errLabel;

	if  (  hDlgDynBmps_param  !=  hWall_gps  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "talkerShadow_procGps failed, hWall not matched"  )  );
		goto  errLabel;
	}


	POINT	point_xy;
	gps2Pnt(  0,  &gpsPos,  pDlgDynBmpsVar->vWall.coord.zoom,  &point_xy  );
	
#ifdef  __DEBUG__
		#if  0
			traceLog((TCHAR*)  _T(  "talkerShadow_procGps: get %d,%d"  ),  point_xy.x,  point_xy.y  );
		#endif
#endif

	POINT	point;
	point  =  point_xy;
	//
	point.x  -=  pDlgDynBmpsVar->vWall.coord.origin.x;
	point.y  -=  pDlgDynBmpsVar->vWall.coord.origin.y;

	CQyVWall  *  pWall  =  pDlgDynBmpsVar->pWall;
	if  (  !pWall  )  goto  errLabel;
	SUB_V_WALL	*	pSubWall  =  pWall->getCurSubWall(  );
	if  (  !pSubWall  )  goto  errLabel;
	SP_STRUCT	*	pSp	=	(  SP_STRUCT  *  )pSubWall->pSp;
	if  (  !pSp  )  goto  errLabel;
	if  (  !pSp->spWidth  ||  !pSp->spHeight  )  goto  errLabel;

	//
	BOOL	bSizeChanged  =  FALSE;
	int		x  =  0,  y  =  0;
	int		iW  =  0,  iH  =  0;
	int		i;

	if  (  bForceRefreshPos  )  {
		for  (  i  =  0;  i  <  mycountof(  pSubWall->mems  );  i  ++  )  {
			 if  (  pShadowMgr->shadows[index_shadow].uiTranNo_spObj  ==  pSubWall->mems[i].uiTranNo_spObj  )  {
				 iW  =  pSubWall->mems[i].iW;
				 iH  =  pSubWall->mems[i].iH;
				 break;
			 }
		}
		if  (  iW  &&  iH  )  {
			RECT	rc;
			GetWindowRect(  hDlgTalk,  &rc  );
			if  (  rc.right  -  rc.left  !=  iW
				||  rc.bottom  -  rc.top  !=  iH  )
			{
				bSizeChanged  =  TRUE;
			}
		}
	}

	//
	float  fx  =  1.  *  pSubWall->iW_image  /  pSp->spWidth;
	float  fy  =  1.  *  pSubWall->iH_image  /  pSp->spHeight;

	point.x  =  point.x  *  fx;
	point.y  =  point.y  *  fy;

	point.x  +=  pSubWall->iX_image;
	point.y  +=  pSubWall->iY_image;

	//  2012/05/06
	BOOL	bAdjusted  =  FALSE;

	if  (  point.x  <  pSubWall->iX  )  {
		point.x  =  pSubWall->iX;
		bAdjusted  =  TRUE;
	}
	if  (  point.x  >  pSubWall->iX  +  pSubWall->iW  )  {
		point.x  =  pSubWall->iX  +  pSubWall->iW;
		bAdjusted  =  TRUE;
	}
	if  (  point.y  <  pSubWall->iY  )  {
		point.y  =  pSubWall->iY;
		bAdjusted  =  TRUE;
	}
	if  (  point.y  >  pSubWall->iY  +  pSubWall->iH  )  {
		point.y  =  pSubWall->iY  +  pSubWall->iH;
		bAdjusted  =  TRUE;
	}

	//
	pTalkerShadow->viewGps.point_xy  =  point_xy;
	pTalkerShadow->viewGps.point  =  point;
	pTalkerShadow->viewGps.dwTickCnt_lastRefreshed  =  GetTickCount(  );

	if  (  pShadowMgr->ucbShowGpsData  )  {
		TCHAR	tBuf[256]	=	_T(  ""  );
										
		gps_DisplayStr(  &gpsPos,  tBuf,  mycountof(  tBuf  )  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s -> (%d,%d) -> (%d,%d)"  ),  tBuf,  point_xy.x,  point_xy.y,  point.x,  point.y  );  
		if  (  bAdjusted  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s adjusted"  ),  tBuf  );
		traceLog((TCHAR*)  _T(  "gpsStr %s"  ),  tBuf  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%I64u gps: %s"  ),  pMgrVar->addr.idInfo.ui64Id,  tBuf  );
	}


	//
	MapWindowPoints(  pSubWall->hWnd_subWall,  NULL,  &point,  1  );
	UINT	uFlags  =  SWP_NOSIZE  |  SWP_NOACTIVATE  |  SWP_NOZORDER;
	if  (  bSizeChanged  )  uFlags  =  SWP_NOACTIVATE  |  SWP_NOZORDER;

	//
	x  =  point.x;
	y  =  point.y;


	//
#if  10
	if  (  pDlgDynBmpsVar_param  )  {
		//
		if  (  index_wallGpsMgrMem  <  0  ||  index_wallGpsMgrMem  >=  mycountof(  pDlgDynBmpsVar->wallGpsMgr.mems  )  )  {
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "talkerShadow_procGps failed, index_wallGpsMgrMem err"  )  );
			goto  errLabel;
		}
		WALL_gps_mgrMem  *  pMem  =  &pDlgDynBmpsVar->wallGpsMgr.mems[index_wallGpsMgrMem];
		

		//  对于pDlgWall_param非0的情况,是需要在wall里批量移动的,所以这里就退出了
		pMem->x  =  x;
		pMem->y  =  y;
		pMem->iW  =  iW;
		pMem->iH  =  iH;
		pMem->uFlags  =  uFlags;

		iErr  =  0;  goto  errLabel;

	}
#endif

#if  10
	
	SetWindowPos(  hDlgTalk,  0,  x,  y,  iW,  iH,  uFlags  ); 

#else


	HDWP			hDwp;

	hDwp  =  M_BeginDeferWindowPos(  1  );
	if  (  hDwp  )  {		 

		M_DeferWindowPos(  hDwp,  hDlgTalk,  NULL,  x,  y,  iW,  iH,  uFlags  );

		//
		M_EndDeferWindowPos(  hDwp  );
	}

#endif

	iErr  =  0;
errLabel:

	return  iErr;
}
