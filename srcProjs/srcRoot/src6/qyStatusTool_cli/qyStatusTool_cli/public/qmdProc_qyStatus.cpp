
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
	_sntprintf(pStruct->who_from, mycountof(pStruct->who_from), _T("%I64u p"), pSmall->who_from);
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
					memset(&tmp_ss, 0, sizeof(tmp_ss));
					if (tmpReq.head.usCode == CONST_qyCmd_showInfo_small) {
						QY_SHOW_SMALL* pSmall = (QY_SHOW_SMALL*)dataBuf;
						//
						showSmall2Struct(pSmall, &tmp_ss);
						//
						pSs = &tmp_ss;
					}

					//
					if (tmp_ss.iType == 7) {
						int  ii = 0;
					}


					//
					qPostMsg(pSs, sizeof(pSs[0]), &g_pStatusStruct->inputQ,  _T( "getAndProcReq_qyStatus"  ));

				   //

				   }				   
				   break;
			 case  CONST_qyCmd_showInfo_small_java:
			 {
				 //
				 QY_SHOW_STRUCT* pSs = (QY_SHOW_STRUCT*)dataBuf;

				 QY_SHOW_STRUCT  tmp_ss;
				 if (tmpReq.head.usCode == CONST_qyCmd_showInfo_small_java) {
					 QY_SHOW_SMALL_java tmp;
					 memcpy(&tmp, dataBuf, sizeof(tmp));
					 QY_SHOW_SMALL_java* pSmall = (QY_SHOW_SMALL_java*)&tmp;// dataBuf;
					 //
					 pSmall->iType = qyntohl(pSmall->iType);
					 pSmall->usStateType = qyntohs(pSmall->usStateType);
					 pSmall->usStateSubtype = qyntohs(pSmall->usStateSubtype);
					 pSmall->iPos_toDisplay= qyntohl(pSmall->iPos_toDisplay);
					 pSmall->iTaskId= qyntohl(pSmall->iTaskId);
					 pSmall->ulClientIp = qyntohl(pSmall->ulClientIp);

					 unsigned  __int64 who_from, who_to;
					 memcpy(&who_from, pSmall->who_from, 8);
					 who_from = qyntohl64(who_from);
					 memcpy(&who_to, pSmall->who_to, 8);
					 who_to = qyntohl64(who_to);
					 //pSmall->who_from= qyntohl(pSmall->who_from);
					 //pSmall->who_to = qyntohl(pSmall->who_to);

					 char  buf[256];
					 TCHAR  tBuf[256];

					 //
					 int  jj = offsetof(QY_SHOW_SMALL_java, who_to);
					 int  ii = offsetof(QY_SHOW_SMALL_java, whereBuf);
					 int kk = offsetof(QY_SHOW_SMALL_java, when);


					 //
					 memcpy(buf, pSmall->whereBuf, mycountof(pSmall->whereBuf) * sizeof(TCHAR));
					 myUtf82TChar(buf, tBuf, mycountof(tBuf));
					 //safeTcsnCpy(tBuf, pSmall->whereBuf, mycountof(pSmall->whereBuf));

					 //
					 pSmall->when.wYear = qyntohs(pSmall->when.wYear);
					 pSmall->when.wMonth = qyntohs(pSmall->when.wMonth);
					 pSmall->when.wDay = qyntohs(pSmall->when.wDay);
					 pSmall->when.wHour = qyntohs(pSmall->when.wHour);
					 pSmall->when.wMinute = qyntohs(pSmall->when.wMinute);
					 pSmall->when.wSecond = qyntohs(pSmall->when.wSecond);
					 pSmall->when.wMilliseconds = qyntohs(pSmall->when.wMilliseconds);
					 pSmall->when.wDayOfWeek= qyntohs(pSmall->when.wDayOfWeek);


					 pSmall->usStep = qyntohs(pSmall->usStep);
					 pSmall->dwProcessId= qyntohl(pSmall->dwProcessId);
					 pSmall->dwThreadId= qyntohl(pSmall->dwThreadId);

					 memcpy(buf, pSmall->doStr, mycountof(pSmall->doStr) * sizeof(TCHAR));
					 myUtf82TChar(buf, tBuf, mycountof(tBuf));
					 //safeTcsnCpy(tBuf, pSmall->doStr, mycountof(pSmall->doStr));

					 memcpy(buf, pSmall->what, mycountof(pSmall->what) * sizeof(TCHAR));
					 myUtf82TChar(buf, tBuf, mycountof(tBuf));
					 //safeTcsnCpy(tBuf, pSmall->what, mycountof(pSmall->what));

					 
					 //
					 //showSmall2Struct(pSmall, &tmp_ss);
					 //
					 tmp_ss.iType = pSmall->iType;
					 tmp_ss.usStateType = pSmall->usStateType;
					 tmp_ss.usStateSubtype= pSmall->usStateSubtype;
					 tmp_ss.iPos_toDisplay = pSmall->iPos_toDisplay;
					 tmp_ss.iTaskId= pSmall->iTaskId;
					 tmp_ss.ulClientIp = pSmall->ulClientIp;
					 _sntprintf(tmp_ss.who_from, mycountof(tmp_ss.who_from), _T("%I64u"), who_from);
					 _sntprintf(tmp_ss.who_to, mycountof(tmp_ss.who_to), _T("%I64u"), who_to);
					 myUtf82TChar(pSmall->whereBuf, tmp_ss.whereBuf, mycountof(tmp_ss.whereBuf));
					 tmp_ss.when = pSmall->when;
					 tmp_ss.usStep = pSmall->usStep;
					 tmp_ss.ucPercent_showInfoQ = pSmall->ucPercent_showInfoQ;
					 tmp_ss.uc_reserved = pSmall->uc_reserved;
					 tmp_ss.dwProcessId = pSmall->dwProcessId;
					 tmp_ss.dwThreadId = pSmall->dwThreadId;

					 
					 myUtf82TChar(pSmall->doStr, tmp_ss.doStr, mycountof(tmp_ss.doStr));
					 myUtf82TChar(pSmall->what, tmp_ss.what, mycountof(tmp_ss.what));


					 if (tmp_ss.iType == 7) {
						 int  ii = 0;
					 }



					 // 
					 // 
					 //
					 pSs = &tmp_ss;
				 }

				 //
				 qPostMsg(pSs, sizeof(pSs[0]), &g_pStatusStruct->inputQ, _T("getAndProcReq_qyStatus"));

				 //

			 }
			 break;

			 default:
					 goto  errLabel;
					 break;
	 }

	 iErr  =  0;

errLabel:

	 if  (  tmpReq.head.usCode  !=  CONST_qyCmd_end
		 &&  tmpReq.head.usCode  !=  CONST_qyCmd_showQwmSvrStatus  )  
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



