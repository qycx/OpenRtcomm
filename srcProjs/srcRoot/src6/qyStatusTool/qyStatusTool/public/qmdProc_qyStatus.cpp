
#include	"stdafx.h"
#include	"qyStatusDaemon.h"
#include	"qyPs.h"
#include	"qyStatusToolCommon.h"

//
int showSmall2Struct(QY_SHOW_SMALL* pSmall, QY_SHOW_STRUCT* pStruct)
{
	memset(pStruct, 0, sizeof(pStruct[0]));

	pStruct->iType = pSmall->iType;
		//
	pStruct->usStateType = pSmall->usStateType;						//  2022/01/27
	pStruct->usStateSubtype = pSmall->usStateSubtype;						//  2022/01/27
		//
	pStruct->iPos_toDisplay = pSmall->iPos_toDisplay;
		//
	pStruct->iTaskId = pSmall->iTaskId;							//  2022/01/27
		//
	pStruct->ulClientIp = pSmall->ulClientIp;							//  2007/08/21 socket clientIp
	//
	_sntprintf(pStruct->who_from, mycountof(pStruct->who_from), _T("phone %I64u"), pSmall->who_from);
	//
	if (pSmall->who_to) {
		_sntprintf(pStruct->who_to, mycountof(pStruct->who_to), _T("%I64u"), pSmall->who_to);
	}
	//
	safeTcsnCpy(pSmall->whereBuf, pStruct->whereBuf, mycountof(pStruct->whereBuf));
	pStruct->when = pSmall->when;								//  2007/06/01, 
	pStruct->usStep = pSmall->usStep;								//  2008/04/28, 
	pStruct->ucPercent_showInfoQ=pSmall->ucPercent_showInfoQ;
		//
	pStruct->dwProcessId = pSmall->dwProcessId;						//  2015/08/30
	pStruct->dwThreadId = pSmall->dwThreadId;							//  2015/08/20
		//
	safeTcsnCpy(pSmall->doStr, pStruct->doStr, mycountof(pStruct->doStr));
	safeTcsnCpy(pSmall->what, pStruct->what, mycountof(pStruct->what));

#ifdef  __DEBUG__
	pStruct->testBytes = pSmall->testBytes;							//  2010/09/06. 这个字节是为了发现一个大小为424字节数的内存泄露。故意增加了一个测试字节。
																	   //  等问题解决了后，应该去除。
#endif
	

	//
	return  0;
}


//
 int  getAndProcReq_qyStatus(  void  *  pSubThreadInfoParam,  void  *  pSessionParam,  void  *  pSessionBufParam,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo  )
{
	 int						iErr			=  -1;
	 MT_SOCK_SUBTHREADINFO	*	pSubThreadInfo	=	(  MT_SOCK_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 CQyStatusDaemon			*	pDaemon			=	(  CQyStatusDaemon  *  )pSubThreadInfo->pParentParam;
	 QMD_SESSION_qyStatus			*	pSession		=	(  QMD_SESSION_qyStatus  *  )pSessionParam;
	 QY_COMM_REQ				tmpReq;
	 char						dataBuf[CONST_qnmReqBufSize_netMc];
	 char					*	p				=	NULL;
	 
	 //
	 CWinApp	*	pApp		=	AfxGetApp(  );


	 //pSession->cmdDesc[0]  =  0;	//  Çå¿Õ»á»°ÃèÊö£¬2005/06/29
	 
	 memset(  &tmpReq,  0,  sizeof(  tmpReq  )  );	
	 if  (  qyRecvReq(  &pSession->comm,  pSock,  pSubThreadInfo->pTo,  &tmpReq,  dataBuf,  sizeof(  dataBuf  )  )  )  {
		 traceLogA(  "getAndProcNetMcReq:  ½ÓÊÕÇëÇóÊ§°Ü"  );  
		 goto  errLabel;
	 }

	 //  ÏÂÃæ´¦ÀíÃüÁîÇëÇó
	 switch  (  tmpReq.head.usCode  )  {
			 case  CONST_qyCmd_end:
				   goto  errLabel;
				   break;
			 case  CONST_qyCmd_showInfo:  
			 case  CONST_qyCmd_showInfo_small:
				   {
					//
					QY_SHOW_STRUCT* pSs = (QY_SHOW_STRUCT*)dataBuf;

					QY_SHOW_STRUCT  tmp_ss;
					if (tmpReq.head.usCode == CONST_qyCmd_showInfo_small) {
						QY_SHOW_SMALL* pSmall = (QY_SHOW_SMALL*)dataBuf;
						//
						showSmall2Struct(pSmall, &tmp_ss);
						//
						pSs = &tmp_ss;
					}

					//
					qPostMsg(pSs, sizeof(pSs[0]), &g_pStatusStruct->inputQ,  _T(  "getAndProcReq_qyStatus"  )  );

				   //
#if 0
				   COPYDATASTRUCT	tmpCopyData;
			
				   tmpCopyData.lpData  =  pSs;//chRequest;		   
				   tmpCopyData.cbData  =  sizeof(QY_SHOW_STRUCT);//dwByte;

				   //
				   if  (  pApp  )  {			
					   CWnd  *  pMainWnd	=	pApp->m_pMainWnd;
					   HWND			hWnd		=	NULL;

					   if  (  pMainWnd  )  {
						   hWnd  =  pMainWnd->m_hWnd;
						   if  (  hWnd  )  SendMessage(  hWnd,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
					   }
				   }
#endif

				   }				   
				   break;
			 default:
					 goto  errLabel;
					 break;
	 }

	 iErr  =  0;

errLabel:

	 if  (  tmpReq.head.usCode  !=  CONST_qyCmd_end
		 //&&  tmpReq.head.usCode  !=  CONST_qyCmd_showQwmSvrStatus  
		 )  
	 {		 
	 }

	 return  iErr;

}



//
 int  doNetMcMgr_qyStatus(  void  *  pSubThreadInfoParam,  void  *  pSessionParam,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo  )
{
	 int						iErr					=	-1;
	 MT_SOCK_SUBTHREADINFO	*	pSubThreadInfo			=	(  MT_SOCK_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 CQyStatusDaemon			*	pDaemon					=	(  CQyStatusDaemon  *  )pSubThreadInfo->pParentParam;
	 QMD_SESSION_qyStatus			*	pSession				=	(  QMD_SESSION_qyStatus  *  )pSessionParam;
	 int						iRet;
	 char						whereBuf[128]			=	"";
	 QY_COMM_SERVICERESP		serviceResp;
	 unsigned  int				len;
	 QNM_PC_INFO				nmPcInfo;				//  2007/04/20, 将nmPcInfo放到这里来了，qmd_session里将没有了		
	 GENERIC_Q					pcProcessQ;
	 BOOL						bPcProcessQInited		=	FALSE;
	 	
	 //  2015/08/24
	 int  iServiceId  =  CONST_qyServiceId_showInfo;
	 //
	 QY_SERVICE_INFO		*	pServiceInfo	=		(  QY_SERVICE_INFO  *  )pDaemon->getSpecialPtrProperty(  CONST_qyPropertyId_serviceInfo_byServiceId,  (  void  *  )iServiceId,  0  );
	if  (  !pServiceInfo  )  return  -1;


	 //
	 traceLogA(  "doNetMcMgr enters, iSessionId is %d",  pSession->comm.uiSessionId  );

	 //
	 if  (  qySendResp(  &pSession->comm,  pSock,  pSubThreadInfo->pTo,  CONST_qyRc_ok,  0,  0  )  )  goto  errLabel;


	 //
	 for  (  ;  !pDaemon->bQuit(  );  )  {


		  if  (  getAndProcReq_qyStatus(  pSubThreadInfoParam,  pSession,  NULL,  pSock,  pSubThreadInfo->pTo  )  )  {
			  break;		  
		  }
		  pSession->comm.nTalks  ++  ;

		  if  (  pSession->comm.usLastReqCode_i  ==  CONST_qyCmd_end  )  {
			  break;
		  }

	 }

	 //qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  pSession->comm.clientIp,  CString(  (  (  QNM_PC_INFO  *  )pSession->pClient  )->ip  ),  0,  CString(  whereBuf  ),  _T(  "会话结束"  ),  _T(  ""  )  );

	 iErr  =  0;

errLabel:

	 //freeSessionInternalBuf(  pSession  );	//  2007/02/15
	 
	 //cancelSyncSessions(  pSession  );

	 if  (  bPcProcessQInited  )  exitGenericQ(  &pcProcessQ  );	//  2008/02/29

	 traceLogA(  "doNetMcMgr leaves"  );

	 return  iErr;

}

 //

 extern  "C"  int  qmdServWork_qyStatus(  void  *  pp,  int  sockFd,  void  *  p2  )
{
	int							iErr								=	-1;
	MT_SOCK_SUBTHREADINFO	*	pSubThreadInfo						=	(  MT_SOCK_SUBTHREADINFO  *  )pp;
	CQyStatusDaemon				*	pDaemon								=  (  CQyStatusDaemon  *  )pSubThreadInfo->pParentParam;
	QMD_SESSION_qyStatus					tmpSession;
	QY_SOCK						tmpSock;
	QY_SERVICE_INFO			*	pServiceInfo						=	0;
	char						timeBuf[CONST_qyTimeLen  +  1]		=	"";
	
	traceLogA(  "qmdServWork( ) enters."  );
	
	//
	InterlockedIncrement(  &g_pStatusStruct->sock.nConnetions  );
	
	//
	clearQySock(  &tmpSock  );
	tmpSock.sockFd  =  sockFd;

	memset(  &tmpSession,  0,  sizeof(  tmpSession  )  );
	getCurTime(  timeBuf  );
	if  (  qyAcceptService(  &tmpSock,  pSubThreadInfo->pTo,  timeBuf,  &tmpSession.comm  )  )  {
		traceLogA(  "qmdServWork(  ): failed to qyAcceptService(  )."  );  goto  errLabel;
	}
	if  (  tmpSession.comm.service.encType  ==  CONST_qyEncType_qwm  )  {
		//memcpy(  &tmpSession.comm.commEncCtx,  &pDaemon->var.commEncCtx,  sizeof(  QY_ENC_CTX  )  );
	}

	//  sessionId的取得已放入qyAcceptService中了
	//  if  (  !(  tmpSession.comm.uiSessionId  =  getSessionId(  )  )  )  goto  errLabel;

	pServiceInfo  =  (  QY_SERVICE_INFO  *  )pDaemon->getSpecialPtrProperty(  CONST_qyPropertyId_serviceInfo_byServiceId,  (  void  *  )tmpSession.comm.service.serviceId,  0  );
	if  (  !pServiceInfo  )  goto  errLabel;
	//tmpSession.pServiceInfo  =  pServiceInfo;
	//
#if  0
	if  (  !pServiceInfo->pObjQ  ||  !pServiceInfo->ucbQmObjQInited  )  goto  errLabel;
	//
	if  (  pServiceInfo->cfg.uiVarSize  )  {
		if  (  !pServiceInfo->pVar  ||  !pServiceInfo->ucbVarInited  )  goto  errLabel;
	}
#endif


	switch  (  tmpSession.comm.service.serviceId  )  {
			case  CONST_qyServiceId_showInfo:
				  doNetMcMgr_qyStatus(  pSubThreadInfo,  (  void  *  )&tmpSession,  &tmpSock,  pSubThreadInfo->pTo  );
				  break;
			//  case  CONST_qyServiceId_mis:
			//  	  doMisMgr(  pSubThreadInfo,  (  void  *  )&tmpSession,  &tmpSock,  pSubThreadInfo->pTo  );
			//  	  break;
			default:
					qySendResp(  &tmpSession.comm,  &tmpSock,  pSubThreadInfo->pTo,  CONST_qyRc_err,  NULL,  0  );
					break;				
	}
	
	iErr  =  0;
	
errLabel:
	
	//
	InterlockedDecrement(  &g_pStatusStruct->sock.nConnetions  );

	//
	traceLogA(  "qmdServWork( ) leaves." );
  
	return iErr;

}



