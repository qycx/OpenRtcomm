

#include	"stdafx.h"
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qmcAcm.h"
#include	"qyAvRecordPublic.h" 
#include	"qyVk.h"
#include	"qyMcMainInternalBak.h"
#include	<assert.h>
#include	"qmcDmoPublic.h"
#include	"tmpCeLib.h"

#include	<WinSock2.h>
#include	<MSWSock.h>
#include	"mtSock_iocp.h"

#include	"qmcCommFunc_isCli.h"
#include	"atMsgFunc.h"

//
#define DEFAULT_PORT        "5001"
#define MAX_BUFF_SIZE       8192
#define MAX_WORKER_THREAD   16

#if  0
typedef enum _IO_OPERATION {
    ClientIoAccept,
    ClientIoRead,
    ClientIoWrite
} IO_OPERATION, *PIO_OPERATION;
#endif

#if  0
//
// data to be associated for every I/O operation on a socket
//
typedef  struct  _PER_IO_CONTEXT					{
				 WSAOVERLAPPED						Overlapped;
				 char								Buffer[CONST_dataBufSize_iocp];
				 WSABUF								wsabuf;
				 int								nTotalBytes;
				 int								nIoBytes;
				 IO_OPERATION						IOOperation;
				 QY_MSG_HEAD						msgHead;
				 unsigned  short					usCode_org;							//  2007/05/03, 

				 unsigned  char						ucbCommHeadDone;
				 unsigned  char						ucbDataDone;

} PER_IO_CONTEXT, *PPER_IO_CONTEXT;

//
// For AcceptEx, the IOCP key is the PER_SOCKET_CONTEXT for the listening socket,
// so we need to another field SocketAccept in PER_IO_CONTEXT. When the outstanding
// AcceptEx completes, this field is our connection socket handle.
//

//
// data to be associated with every socket added to the IOCP
//
typedef struct _PER_SOCKET_CONTEXT {
    SOCKET                      Socket;

    //  LPFN_ACCEPTEX               fnAcceptEx;

	//
    //linked list for all outstanding i/o on the socket
	//
    PPER_IO_CONTEXT             pIOContext_i;  
	PPER_IO_CONTEXT             pIOContext_o;  


} PER_SOCKET_CONTEXT, *PPER_SOCKET_CONTEXT;
#endif


#define xmalloc(s) HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,(s))
#define xfree(p)   HeapFree(GetProcessHeap(),0,(p))


typedef  struct  __ctx_io_iocp_t								{
				 //  2015/09/09
#if  0
				 HANDLE											hThread_input;									//  2008/05/23
				 DWORD											dwThreadId_input;
#endif

				 //
				 HANDLE											hThread_toSend;									//  2008/05/23
				 DWORD											dwThreadId_toSend;
				 
				 //
				 HANDLE											hIOCP;

				 HANDLE											hThreads_work_iocp[2];
				 DWORD											dwThreadIds_work_iocp[2];

				 //
				 PPER_SOCKET_CONTEXT							pPerSocketContext;
				 TCHAR											mutexName_syncSending[64];

				 //
				 struct											{
					 MIS_MSG_INPUT						*		pMsg;
					 QY_BUF								*		pBuf_help;
					 MIS_MSGU							*		pMsgBuf;
				 }												i;

				 //
				 struct											{

					 BOOL										bChkTimeoutInSToSwitch;
					 unsigned  short						*	pusTimeoutInMsToSwitch;


					 DWORD										dwTickCnt_toGetMsg;
					 DWORD										dwTickCnt_startToSend;

					 MIS_MSGU							*		pMsg;
					 QY_BUF								*		pBuf_help;


				 }												o;

				 //
				 LPCTSTR										where_showInfo;	


}		 CTX_io_iocp;


VOID CtxtDelete(PPER_SOCKET_CONTEXT lpPerSocketContext);


//  2014/09/08
#ifdef  __DEBUG__

#define		__PRINT_DATA__

  int  printData(  LPCTSTR  hint,  char  *  pData,  unsigned  int  dataLen  )
 {
	 char  buf[128]  =  "";
	 TCHAR  tBuf[128]  =  _T(  "a987654321a98765432"  );
	 int  i;
	 int  maxCnt;	//  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  /  2  -  1;

	 if  (  !hint  )  return  -1;

	 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s: dataLen %d,"  ),  hint,  dataLen  );
	 TCHAR  *  pT  =  tBuf  +  lstrlen(  tBuf  );
	 maxCnt  =  (  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  -  lstrlen(  tBuf  )  -  1  )  /  2;
	 int  tmpLen  =  min(  dataLen,  maxCnt  );
	 qybuf2x(  pData,  tmpLen,  buf  );
	 buf[tmpLen  *  2]  =  0;
	 myUtf82TChar(  buf,  pT,  2  *  tmpLen  +  1  );
	 pT[2  *  tmpLen]  =  0;
	 //
	 //OutputDebugString(  tBuf  );  OutputDebugString(  _T(  "\n"  )  );
	 //
	 showInfo_open0(  0,  0,  tBuf  );

	 return  0;
 }


#endif


//
// Allocate a socket context for the new connection.  
//
PPER_SOCKET_CONTEXT CtxtAllocate(SOCKET sd, ENUM_IO_OPERATION ClientIO) 
{
	int		iErr	=	-1;

	PPER_SOCKET_CONTEXT pPerSocketContext	=	NULL;

	pPerSocketContext = (PPER_SOCKET_CONTEXT)xmalloc(sizeof(PER_SOCKET_CONTEXT));
	if( !pPerSocketContext ) goto  errLabel;
	
	memset(  pPerSocketContext,  0,  sizeof(  PER_SOCKET_CONTEXT  )  );
	
	pPerSocketContext->sockFd = sd;
	//  lpPerSocketContext->pCtxtBack = NULL;
	//  lpPerSocketContext->pCtxtForward = NULL;

	PPER_IO_CONTEXT  pIOContext; pIOContext = &pPerSocketContext->inputContext;

	pIOContext->overlapped.Internal = 0;
	pIOContext->overlapped.InternalHigh = 0;
	pIOContext->overlapped.Offset = 0;
	pIOContext->overlapped.OffsetHigh = 0;
	pIOContext->overlapped.hEvent = NULL;
	pIOContext->ioOperation = ClientIO;
	//  pIOContext->pIOContextForward = NULL;
	pIOContext->nTotalBytes = 0;
	pIOContext->dwIoBytes  = 0;
	pIOContext->wsaBuf.buf  = pIOContext->buf;
	pIOContext->wsaBuf.len  = sizeof(pIOContext->buf);

	ZeroMemory(pIOContext->wsaBuf.buf, pIOContext->wsaBuf.len);

	pIOContext  =  &pPerSocketContext->outputContext;

	pIOContext->overlapped.Internal = 0;
	pIOContext->overlapped.InternalHigh = 0;
	pIOContext->overlapped.Offset = 0;
	pIOContext->overlapped.OffsetHigh = 0;
	pIOContext->overlapped.hEvent = NULL;
	pIOContext->ioOperation = ClientIO;
	//  pIOContext->pIOContextForward = NULL;
	pIOContext->nTotalBytes = 0;
	pIOContext->dwIoBytes  = 0;
	pIOContext->wsaBuf.buf  = pIOContext->buf;
	pIOContext->wsaBuf.len  = sizeof(pIOContext->buf);

	ZeroMemory(pIOContext->wsaBuf.buf, pIOContext->wsaBuf.len);


	GENERIC_Q_CFG	tmpqCfg;					//  2008/05/25

	memset(  &tmpqCfg,  0,  sizeof(  tmpqCfg  )  );
	_sntprintf(  tmpqCfg.name,  mycountof(  tmpqCfg.name  ),  _T(  "qmcOutCacheQ%d"  ),  getuiNextTranNo(  0,  0,  0  )  );
	tmpqCfg.uiMaxQNodes  =  CONST_uiMaxQNodes_perSocketContextOutCacheQ;
	if  (  initGenericQ(  &tmpqCfg,  mymalloc,  0,  0,  myfree,  NULL,  &pPerSocketContext->cli.outCacheQ  )  )  goto  errLabel;
	pPerSocketContext->cli.bOutCacheQInited  =  TRUE;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pPerSocketContext  )  {
			CtxtDelete(  pPerSocketContext  );  pPerSocketContext  =  NULL;
		}
	}

	return(pPerSocketContext);
} 

//
//  Remove a client context structure from the global list of context structures.
//
VOID CtxtDelete(PPER_SOCKET_CONTEXT lpPerSocketContext) {

	PPER_IO_CONTEXT     pNextIO     = NULL;
	PPER_IO_CONTEXT     pTempIO     = NULL;

	

	if( lpPerSocketContext ) {
		//  pBack       = lpPerSocketContext->pCtxtBack;
		//  pForward    = lpPerSocketContext->pCtxtForward;



		//
		// Free all i/o context structures per socket
		//
		pTempIO = (PPER_IO_CONTEXT)&lpPerSocketContext->inputContext;

		//
		//The overlapped structure is safe to free when only the posted i/o has
		//completed. Here we only need to test those posted but not yet received 
		//by PQCS in the shutdown process.
		//
#if  0

		//  if( g_bEndServer )
		{
			while( !HasOverlappedIoCompleted((LPOVERLAPPED)pTempIO) ) Sleep(0);
		}
#endif
		pTempIO = NULL;


		pTempIO = (PPER_IO_CONTEXT)&lpPerSocketContext->outputContext;


		//
		if  (  lpPerSocketContext->cli.bOutCacheQInited  )  exitGenericQ(  &lpPerSocketContext->cli.outCacheQ  );

		//
		xfree(lpPerSocketContext);
		lpPerSocketContext = NULL;

	} else {
		traceLogA(  (char*)"CtxtListDeleteFrom: lpPerSocketContext is NULL\n");
	}

	return;
}



//
//  Close down a connection with a client.  This involves closing the socket (when 
//  initiated as a result of a CTRL-C the socket closure is not graceful).  Additionally, 
//  any context data associated with that socket is free'd.
//
VOID CloseClient (PPER_SOCKET_CONTEXT lpPerSocketContext,
				  BOOL bGraceful) {


	if( lpPerSocketContext ) {
#if  0
		if( g_bVerbose )
			myprintf("CloseClient: Socket(%d) connection closing (graceful=%s)\n",
				   lpPerSocketContext->Socket, (bGraceful?"TRUE":"FALSE"));
#endif
		if  (  INVALID_SOCKET  !=  lpPerSocketContext->sockFd  )  {

			if( !bGraceful ) {

				//
				// force the subsequent closesocket to be abortative.
				//
				LINGER  lingerStruct;

				lingerStruct.l_onoff = 1;
				lingerStruct.l_linger = 0;
				setsockopt(lpPerSocketContext->sockFd, SOL_SOCKET, SO_LINGER,
					   (char *)&lingerStruct, sizeof(lingerStruct) );
			}
			closesocket(lpPerSocketContext->sockFd);
			lpPerSocketContext->sockFd = INVALID_SOCKET;
		}
		CtxtDelete(lpPerSocketContext);
		lpPerSocketContext = NULL;
	} else {
		traceLogA(  (char*)"CloseClient: lpPerSocketContext is NULL\n");
	}


	return;    
} 


//
//  Allocate a context structures for the socket and add the socket to the IOCP.  
//  Additionally, add the context structure to the global list of context structures.
//
PPER_SOCKET_CONTEXT UpdateCompletionPort(HANDLE  g_hIOCP,  SOCKET sd, ENUM_IO_OPERATION ClientIo,
										 BOOL bAddToList) {

	PPER_SOCKET_CONTEXT lpPerSocketContext;

	lpPerSocketContext = CtxtAllocate(sd, ClientIo);
	if( lpPerSocketContext == NULL )
		return(NULL);

	HANDLE	hIOCP	=	NULL;
	hIOCP = CreateIoCompletionPort((HANDLE)sd, g_hIOCP, (DWORD_PTR)lpPerSocketContext, 0);
	if( hIOCP == NULL ) {
		traceLogA(  (char*)"CreateIoCompletionPort() failed: %d\n", GetLastError());
		CtxtDelete(lpPerSocketContext);
		return(NULL);
	}

    //
	//The listening socket context (bAddToList is FALSE) is not added to the list.
	//All other socket contexts are added to the list.
	//
#if  0
	if( bAddToList ) CtxtListAddTo(lpPerSocketContext);

	if( g_bVerbose )
		myprintf("UpdateCompletionPort: Socket(%d) added to IOCP\n", lpPerSocketContext->Socket);
#endif

	return(lpPerSocketContext);
}


int  proc_io_read(  MIS_CHANNEL  *  pChannel,  PER_SOCKET_CONTEXT  *  pPerSocketContext  )
{
	int					iErr		=	-1;
	if  (  !pChannel  )  return  -1;
	CTX_io_iocp		*	pCtx		=	(  CTX_io_iocp  *  )pChannel->p0;
	MIS_MSG_INPUT	*	pMsg		=	pCtx->i.pMsg;
	QY_BUF			&	buf_help	=	*pCtx->i.pBuf_help;
	MIS_MSGU		*	pMsgBuf		=	pCtx->i.pMsgBuf;

	//		
	MIS_CNT			*	pMisCnt		=	pChannel->pMisCnt;
	if  (  !pMisCnt  )  return  -1;
	MC_VAR_isCli	*	pProcInfo	=	(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	QY_MC			*	pQyMc		=	(  QY_MC  *   )pProcInfo->pQyMc;	//  
	if  (  !pQyMc  )  return  -1;

	//
	QY_MSG_HEAD_h			msgHead;
	TCHAR				where_showInfo[128]		=	_T(  ""  );
	int					tmpiRet;

	//  2015/09/05
	_sntprintf(  where_showInfo,  mycountof(  where_showInfo  ),  _T(  "%s proc_io_read"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  )  );


			  //  2009/02/25
		  pChannel->status.dwTickCnt_lastStartToRecv  =  myGetTickCount(mynull  );

		  MACRO_memset_misMsgInput(  pMsg  );
#if  0
		  //  ÕâÀïÊÇÕæÓÐÊý¾ÝÀ´ÁË
		  if  (  qyRecvMsg(  &pChannel->session,  &pChannel->sock,  &pQyMc->cfg.to,  &msgHead,  (  char  *  )&pMsg->data,  sizeof(  pMsg->data  )  )  )  {
			  traceLogA(  (char*)  "mcThreadProc_mis_io: qyRecvMsg(  ) failed"  );  
			  goto  errLabel;
		  }
#endif
		  memcpy(  &msgHead,  &pPerSocketContext->inputContext.msgHead,  sizeof(  msgHead  )  );
		  if  (  msgHead.uiLen  >  sizeof(  pMsg->data  )  )  goto  errLabel;
		  memcpy(  &pMsg->data,  pPerSocketContext->inputContext.buf,  msgHead.uiLen  );

		  //
		  pMsg->tStartTime  =  (  time_t  )msgHead.i64StartTime;
		  pMsg->uiTranNo  =  msgHead.uiTranNo;
		  pMsg->usSeqNo  =  msgHead.usSeqNo;
		  pMsg->ucFlg  =  msgHead.ucFlg;
		  pMsg->usCode  =  msgHead.usCode;
		  pMsg->uiChannelType  =  pChannel->uiType;		//  2008/04/17
		  pMsg->lenInBytes  =  msgHead.uiLen;
 
		  if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewIoStatus  )  {	
			  #if  0
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  where_showInfo,  _T(  ""  ),  _T(  "recv: len %d, tn %d, sn %d"  ),  pMsg->lenInBytes,  pMsg->uiTranNo,  pMsg->usSeqNo  );
			  #endif
		  }
		  
		  if  (  isUcFlgMoreData(  pMsg->ucFlg  )  )  {
			  if  (  procMisMsg_moreData(  &pChannel->inCacheQ,  pMsg,  NULL  )  )  goto  errLabel;
			  iErr  =  0;  goto  errLabel;
		  }
		  if  (  pMsg->usSeqNo  )  {
			  BOOL  bMsgSkipped			=	FALSE;		//  ÊÇ·ñ´Ë°üÐèÒªºöÂÔ?
			  //
			  if  (  procMisMsg_moreData(  &pChannel->inCacheQ,  pMsg,  &bMsgSkipped  )  )  goto  errLabel;
			  if  (  bMsgSkipped  )  {
				  iErr  =  0;  goto  errLabel;
			  }
			  //
			  //  traceLogA(  (char*)  "µÃµ½Ò»¸ö´ó°ü£¬³¤¶ÈÎª%d, tStartTime is %d, uiTranNo is %d",  pMsg->lenInBytes,  pMsg->tStartTime,  pMsg->uiTranNo  );
		  }

		  //  traceLogA(  (char*)  "mcThreadProc_mis_io: get, ³¤¶È %d, tStartTime is %d, uiTranNo is %d",  pMsg->lenInBytes,  pMsg->tStartTime,  pMsg->uiTranNo  );
		  pChannel->status.netStat.ui64MsgDataLenRecvd  +=  sizeof(  msgHead  )  +  pMsg->lenInBytes;		//  2009/10/10

		  if  (  decryptData(  &pChannel->commEncCtx,  &buf_help,  (  char  *  )&pMsg->data,  &pMsg->lenInBytes  )  )  {
			  qyShowInfo1(  CONST_qyShowType_warning,  0, (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  where_showInfo,  _T(  ""  ),  _T(  ""  ),  _T(  "io: decryptData failed."  )  );
			  goto  errLabel;
		  }

		  //  pChannel->status.netStat.nMsgRecvd  ++  ;

		  //  2015/08/09
		  if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewIoStatus  )  {				
				  static  int  kk  =  0;  kk  ++  ;
				   //  traceLogA(  (char*)  "get code %S,  msgHead.usLen %d,  kk  =  %d",  qyGetDesByType1(  CONST_qyCmdTable,  msgHead.usCode  ),  msgHead.usLen,  kk  );
				  if  (  10  )  {
					  //
					  if  (  isUcFlgResp(  msgHead.ucFlg  )  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  where_showInfo,  _T(  ""  ),  _T(  "  tn %d, resp: %s, dataLen %d"  ),  msgHead.uiTranNo,  qyGetDesByType1(  CONST_qyRcTable,  msgHead.usCode  ),  pMsg->lenInBytes  );
					  else  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  NULL,  where_showInfo,  _T(  ""  ),  _T(  " tn %d, req %s, dataLen %d"  ),  msgHead.uiTranNo,  qyGetDesByType1(  CONST_qyCmdTable,  msgHead.usCode  ),  pMsg->lenInBytes  );
				  }
		  }

		  //  2017/07/26
		  #ifdef  __DEBUG__
				  if  (  isUcFlgResp(  msgHead.ucFlg  )  )  {
					  int  kk  =  0;
					  traceLog((TCHAR*)  _T(  "here a resp"  )  );
				  }			

		  #endif

		  //
		  if  (  (  tmpiRet  =  pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_input,  msgHead.ucFlg,  msgHead.usCode,  (  time_t  )msgHead.i64StartTime,  msgHead.uiTranNo,  0,  (  char  *  )&pMsg->data,  pMsg->lenInBytes,  0,  0,  pChannel->uiType,  pMsgBuf,  FALSE  )  )  )  {
			  if  (  tmpiRet  ==  CONST_qyRet_qFull  )  {
                  switch  (  pChannel->uiType  )  {
						  case  CONST_channelType_media:
						  case  CONST_channelType_realTimeMedia:
							    qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  where_showInfo,  _T(  ""  ),  _T(  "postMsg2Mgr_mc returns qFull, skipped."  )  );							   
								iErr  =  0;  goto  errLabel;
						  default:
								  break;
				  }						
			  }
			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  where_showInfo,  _T(  ""  ),  _T(  "postMsg2Mgr_mc failed."  )  );							   
			  goto  errLabel;
		  }

		  iErr  =  0;

errLabel:

		  return  iErr;


}

//  未完成
//  应该学习daemon, 将包拆分到pPerSocketContext->outCacheQ. 然后从这里再逐个读取发送
 int  procOutputQ_iocp_isCli(  MIS_CHANNEL  *  pChannel,  PER_SOCKET_CONTEXT  *  pPerSocketContext,  BOOL  *  pbMsgExists  )
{
	int					iErr		=	-1;
	if  (  !pChannel  )  return  -1;
	CTX_io_iocp		*	pCtx		=	(  CTX_io_iocp  *  )pChannel->p0;

	//
	MIS_CNT			*	pMisCnt		=	pChannel->pMisCnt;
	if  (  !pMisCnt  )  return  -1;
	MC_VAR_isCli	*	pProcInfo	=	(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	QY_MC			*	pQyMc		=	(  QY_MC  *  )pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;

	//
	MIS_MSGU					*	pMsg						=	pCtx->o.pMsg;
	QY_BUF						&	buf_help					=	*pCtx->o.pBuf_help;

	BOOL							bMsgExists	=	TRUE;

	unsigned  int					len;

	int								iElapse;
	TCHAR							tBuf[128]	=	_T(  ""  );


	pCtx->o.dwTickCnt_toGetMsg  =  GetTickCount(  );


	//  
	len  =  sizeof(  pMsg[0]  );
	 if  (  qGetMsg(  &pPerSocketContext->cli.outCacheQ,  pMsg,  &len  )  )  {		//  

		 for  (  ;  ;  )  {
	  
			  len  =  sizeof(  pMsg[0]  );			//  2007/05/02, 
			  if  (  q2GetMsg(  &pChannel->outputQ2,  pMsg,  &len,  _T(  "procOutput_iocp"  ))) {
				  bMsgExists  =  FALSE;
				   
				  //  
				  //  qyShowInfo1(  CONST_qyShowType_debug,  _T(  ""  ),  pSession->whoBuf_showInfo_serv,  pSession->whoBuf_showInfo_cli,  pSession->whereBuf_showInfo,  _T(  ""  ),  _T(  "¶ÓÁÐÔÝÎÞÊý¾Ý"  )  );
				  //
				  iErr  =  0;  goto  errLabel;
			  }

			  //  这里可以添加对
			  switch  (  pMsg->uiType  )  {

					   case  CONST_misMsgType_task:  
					   case  CONST_misMsgType_outputTask:  {

						     //  2008/11/20
						     if  (  pCtx->o.bChkTimeoutInSToSwitch  )  {
								 if  (  pMsg->task.dwTickCnt_start  )  {
									 iElapse  =  GetTickCount(  )  -  pMsg->task.dwTickCnt_start;
									 if  (  iElapse  >  *pCtx->o.pusTimeoutInMsToSwitch  )  {
										 BOOL	bTaskFound  =  FALSE;
										 //
										 if  (  pMsg->task.iTaskId  )  {	//  2010/09/23
											 if  (  pChannel->uiType  ==  CONST_channelType_media  )  {
												 int	i;
												 for  (  i  =  0;  i  <  pProcInfo->cfg.usMaxCnt_pSharedObjs;  i  ++  )  {
													  QY_SHARED_OBJ	*	tmppSharedObj  =  getSharedObjByIndex(  pProcInfo,  i  );
													  SHARED_OBJ_USR	*	pSharedObjUsr  =  getSharedObjUsr(  tmppSharedObj,  tmppSharedObj->iIndex_curUsr  );
													  if  (  pSharedObjUsr  
														  &&  pSharedObjUsr->iTaskId  ==  pMsg->task.iTaskId  )  
													  {
														  CAP_procInfo_bmpU  *  pCapProcInfo  =  getCapBmpBySth(  pProcInfo,  tmppSharedObj->iIndex_capBmp,  0  );		
														  if  (  pCapProcInfo  )  {
															  COMPRESS_VIDEO  *  pCompressVideo  =  &pCapProcInfo->common.compressVideo;
															  if  (  pCompressVideo  )  {
																  pCompressVideo->usTimes_failure  +=  MAX_failures_frames_perSecond  +  1;
																  bTaskFound  =  TRUE;
															  }
														  }
													  }
												 }
											 }
										 }
										 //
										 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "snd: %dms elapsed, skipped. tn %d, %s."  ),  iElapse,  pMsg->task.uiTranNo,  bTaskFound  ?  _T(  "to adjust speed."  )  :  _T(  ""  )  );
										 if  (  pMsg->task.dwTickCnt_toSend  )  {
											 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s -2Snd %dms."  ),  tBuf,  pMsg->task.dwTickCnt_toSend  -  pMsg->task.dwTickCnt_start  );
										 }
										 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s last->s %dms."  ),  tBuf,  pCtx->o.dwTickCnt_startToSend  -  pChannel->status.dwTickCnt_lastEndSending  );
										 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  pCtx->where_showInfo,  _T(  ""  ),  _T(  "%s"  ),  tBuf  );								 
										 //  这里表明这个包需要被放弃
										 continue;
									 }
								 }
							 }

							 }
							 break;
					   default:
							  break;							
			  }

			
			  break;
		 }
	
			   //  2009/02/25
			   pCtx->o.dwTickCnt_startToSend  =  GetTickCount(  );

			   //  traceLogA(  (char*)  "mcThreadproc_mis_snd: µÃµ½Ò»ÌõÏûÏ¢[%S]",  qyGetDesByType1(  CONST_misMsgTypeTable,  pMsg->uiType  )  ); 
	  		  
			   switch  (  pMsg->uiType  )  {
					   case  CONST_misMsgType_req:

						     qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  pCtx->where_showInfo,  _T(  ""  ),  _T(  "snd: %s,  tn %d"  ),  qyGetDesByType1(  CONST_qyCmdTable,  pMsg->req.usCode  ),  pMsg->req.uiTranNo  );

							 if  (  encryptData(  &pChannel->commEncCtx,  &buf_help,  (  char  *  )&pMsg->req.data,  &pMsg->req.lenInBytes,  sizeof(  pMsg->req.data  )  )  )  {
								 qyShowInfo1(  CONST_qyShowType_warning,  0, (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  pCtx->where_showInfo,  _T(  ""  ),  _T(  "snd req: encryptData failed"  )  );
								 goto  errLabel;
							 }

							#if  0
							 if  (  qySendMsg(  &pChannel->session,  &pChannel->sock,  &pQyMc->cfg.to,  pMsg->req.ucFlg,  pMsg->req.usCode,  pMsg->req.tStartTime,  pMsg->req.uiTranNo,  pMsg->req.usSeqNo,  (  char  *  )&pMsg->req.data,  pMsg->req.lenInBytes  )  )  {
								 traceLogA(  (char*)  "qySendMsg failed"  );  goto  errLabel;
							 }
							 //  2009/10/11
							 pChannel->status.netStat.ui64MsgDataLenSent  +=  sizeof(  QY_MSG_HEAD  )  +  pMsg->req.lenInBytes;
							#endif


						     break;
					   case  CONST_misMsgType_talk:  {
							
						     //  
						     if  (  !isUcFlgResp(  pMsg->task.ucFlg  )  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  pCtx->where_showInfo,  _T(  ""  ),  _T(  "snd: tn %d, %s: len %d"  ),  pMsg->task.uiTranNo,  qyGetDesByType1(  CONST_qyCmdTable,  pMsg->task.usCode  ),  pMsg->task.lenInBytes  );
						     else  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  pCtx->where_showInfo,  _T(  ""  ),  _T(  "snd: tn %d, resp: %s "  ),  pMsg->task.uiTranNo,  qyGetDesByType1(  CONST_qyRcTable,  pMsg->task.usCode  )  );

							 //  2014/09/08
							 #ifdef  __DEBUG__
									 #ifdef  __PRINT_DATA__
											 printData(  _T(  "orgTalk"  ),  (  char  *  )&pMsg->talk.data,  pMsg->talk.lenInBytes  );
									 #endif							 
							 #endif

							 //
							 if  (  encryptData(  &pChannel->commEncCtx,  &buf_help,  (  char  *  )&pMsg->talk.data,  &pMsg->talk.lenInBytes,  sizeof(  pMsg->talk.data  )  )  )  {
								 qyShowInfo1(  CONST_qyShowType_warning,  0, (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  pCtx->where_showInfo,  _T(  ""  ),  _T(  "snd talk: encryptData failed"  )  );
								 goto  errLabel;
							 }

							 //  2014/09/08
							 #ifdef  __DEBUG__
									 #ifdef  __PRINT_DATA__
											 printData(  _T(  "encTalk"  ),  (  char  *  )&pMsg->talk.data,  pMsg->talk.lenInBytes  );
									 #endif							 
							 #endif


							#if  0
						     if  (  qySendMsg(  &pChannel->session,  &pChannel->sock,  &pQyMc->cfg.to,  pMsg->talk.ucFlg,  pMsg->talk.usCode,  pMsg->talk.tStartTime,  pMsg->talk.uiTranNo,  pMsg->talk.usSeqNo,  (  char  *  )&pMsg->talk.data,  pMsg->talk.lenInBytes  )  )  {
								 traceLogA(  (char*)  "qySendMsg failed"  );  goto  errLabel;
							 }
							 //  2009/10/11
							 pChannel->status.netStat.ui64MsgDataLenSent  +=  sizeof(  QY_MSG_HEAD  )  +  pMsg->talk.lenInBytes;
							#endif

							}
						     break;
					   case  CONST_misMsgType_task:  
					   case  CONST_misMsgType_outputTask:  {

						     //  2016/0328
							#if  0
						     int  tn_openAvDev_org  =  0;
						     if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewIoStatus  )  {		
								 IM_CONTENTU  *  pContent  =  M_getMsgContent(  pMsg->task.ucFlg,  &pMsg->task.data  );  
								 switch  (  pContent->uiType  )  {
										 case  CONST_imCommType_transferVideoData:
											   tn_openAvDev_org  =  pContent->transferVideoData.uiTranNo_openAvDev;
											   break;
										 default:
												break;
								 }
							 }
							#endif

						     //  2008/11/20
							 //
							 if  (  encryptData(  &pChannel->commEncCtx,  &buf_help,  (  char  *  )&pMsg->task.data,  &pMsg->task.lenInBytes,  sizeof(  pMsg->task.data  )  )  )  {
								 qyShowInfo1(  CONST_qyShowType_warning,  0, (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  pCtx->where_showInfo,  _T(  ""  ),  _T(  "snd task: encryptData failed"  )  );
								 goto  errLabel;
							 }

							 unsigned  int  uiSizePerSnd_media  =  pMisCnt->cfg.uiSizePerSnd_media;		//  2011/01/30
							 if  (  !uiSizePerSnd_media  )  uiSizePerSnd_media  =  MIN_uiSizePerSnd_media;

							 if  (  pMsg->task.lenInBytes  >  uiSizePerSnd_media  )  {		//  
                                 	char			*	p					=	NULL;
                                    unsigned  int		nLeft				=	0;
									unsigned  int		uiSeqNo				=	0;
									unsigned  int		nSend				=	uiSizePerSnd_media;
									unsigned  char		ucFlg_org			=	0;
									//  unsigned  char		ucFlg				=	0;
									//  TCHAR				tBuf[255  +  1]		=	_T(  ""  );
									//
                                    p  =  (  char  *  )&pMsg->task.data;
									nLeft  =  pMsg->task.lenInBytes;
									ucFlg_org  =  pMsg->task.ucFlg;

									Param_dbg param;
									param.m_pHint=(TCHAR*)_T("procOutputQ_iocp_isCli.713");
									//
									for  (  uiSeqNo  =  0;  nLeft  &&  bChannelOk(  pChannel, &param  );  uiSeqNo  ++  )  {
										 nSend  =  min(  nSend,  nLeft  );
										 //
										 //  ucFlg  =  (  nLeft  >  nSend  )  ?  (  ucFlg_org  |  CONST_commFlg_moreData  )  :  ucFlg_org;
										 //
										 if  (  uiSeqNo  )  memcpy(  &pMsg->task.data,  p,  nSend  );	//  memcpyÒªÈÆ¹ýµÚ0´Î
										 //
										 pMsg->task.ucFlg  =  (  nLeft  >  nSend  )  ?  (  ucFlg_org  |  CONST_commFlg_moreData  )  :  (  ucFlg_org  &  ~CONST_commFlg_moreData  );
										 pMsg->task.usSeqNo  =  uiSeqNo;

										 #ifdef  __DEBUG__
												 if  (  0  )  {
													 if  (  nLeft  >  nSend  )  {													 
														 OutputDebugString(  _T(  "\n"  )  );												 
													 }
													 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "before qySendMsg: uiSeqNo [%d], nSend [%d], lenInBytes [%d]\n"  ),  uiSeqNo,  nSend,  pMsg->task.lenInBytes  );
													 OutputDebugString(  tBuf  );
												 }
										 #endif
										 //
									#if  0
                                         if  (  qySendMsg(  &pChannel->session,  &pChannel->sock,  &pQyMc->cfg.to,  ucFlg,  pMsg->task.usCode,  pMsg->task.tStartTime,  pMsg->task.uiTranNo,  uiSeqNo,  p,  nSend  )  )  {
											 traceLogA(  (char*)  "qySendMsg failed"  );  goto  errLabel;
										 }
										 //  2009/10/11
										 pChannel->status.netStat.ui64MsgDataLenSent  +=  sizeof(  QY_MSG_HEAD  )  +  pMsg->task.lenInBytes;
									#endif

										 //				
										 pMsg->task.lenInBytes  =  nSend;					
										 len  =  pMsg->task.lenInBytes  +  offsetof(  MIS_MSG_TASK,  data  );					  
										 if  (  qPostMsg(  pMsg,  len,  &pPerSocketContext->cli.outCacheQ,  _T(  "procOutputQ_iocp_is"  ))) {
					 					     #ifdef  __DEBUG__
													 traceLogA(  (char*)  "qPostMsg failed"  );  
											 #endif
											 goto  errLabel;					  
										 }

										 //
										 nLeft  -=  nSend;
										 p  +=  nSend;		
										 continue;
									}

									//
									//  
									len  =  sizeof(  pMsg[0]  );
									if  (  qGetMsg(  &pPerSocketContext->cli.outCacheQ,  pMsg,  &len  )  )  {
									    #ifdef  __DEBUG__							   
												traceLogA(  (char*)  "qGetMsg failed"  );  
										#endif
										goto  errLabel;
									}

							 }

						#if  10
							 //  2011/01/22
							 DWORD	dwTickCnt_endSending  =  GetTickCount(  );
							 if  (  pQyMc->env.bDebugInfo  &&  pProcInfo->cfg.debugStatusInfo.ucbViewIoStatus  )  {				   
								 if  (  !isUcFlgResp(  pMsg->task.ucFlg  )  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "snd: tn %d, %s: len %d."  ),  pMsg->task.uiTranNo,  qyGetDesByType1(  CONST_qyCmdTable,  pMsg->task.usCode  ),  pMsg->task.lenInBytes  );
								 else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "snd: tn %d, resp: %s."  ),  pMsg->task.uiTranNo,  qyGetDesByType1(  CONST_qyRcTable,  pMsg->task.usCode  )  );
								 //

								 //
								 //  if  (  pMsg->task.index_debugInfo  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s index %d."  ),  tBuf,  pMsg->task.index_debugInfo  );
								 if  (  pMsg->task.dwTickCnt_start  )  {
									 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s s-snt %d."  ),  tBuf,  dwTickCnt_endSending  -  pMsg->task.dwTickCnt_start  );
								 }								 							
								 if  (  pMsg->task.dwTickCnt_toSend  )  {								
									 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s -2Snd %u."  ),  tBuf,  pMsg->task.dwTickCnt_toSend  -  pMsg->task.dwTickCnt_start  );										 
								 }
								 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s l-m-s-end %d, %d, %d."  ),  tBuf,  pCtx->o.dwTickCnt_toGetMsg  -  pChannel->status.dwTickCnt_lastEndSending,  pCtx->o.dwTickCnt_startToSend  -  pCtx->o.dwTickCnt_toGetMsg,  dwTickCnt_endSending  -  pCtx->o.dwTickCnt_startToSend  );
								 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s nQ %d."  ),  tBuf,  getQ2Nodes_toGetMsg(  &pChannel->outputQ2  )  );
								 
								 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  pCtx->where_showInfo,  _T(  ""  ),  _T(  "%s"  ),  tBuf  );								 
							 }
						#endif


							 }
							 break;
					   default:
					   							 
						        qyShowInfo1(  CONST_qyShowType_debug,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "msThreadProc_mis_snd: Î´´¦ÀíµÄÏûÏ¢%S"  ),  qyGetDesByType1(  CONST_misMsgTypeTable,  pMsg->uiType  )  );
								traceLogA(  (char*)  "err,  [%S]",  qyGetDesByType1(  CONST_misMsgTypeTable,  pMsg->uiType  )  );
								goto  errLabel;
								break;
			   }


	 }

     //  pChannel->status.netStat.nMsgSent  ++  ;	
	 pChannel->status.dwTickCnt_lastEndSending  =  myGetTickCount( mynull );	//  2011/01/23
#ifdef  __DEBUG__
		//  qyShowInfo1(  CONST_qyShowType_debug,  0,  0,  _T(  "IsClient"  ),  _T(  ""  ),  pCtx->where_showInfo,  _T(  ""  ),  _T(  "procOutputQ_iocp: to sendMsg"  )  ); 						   
#endif


#if  10
 
	 MACRO_memset_perIoContext(  pPerSocketContext->outputContext  );
	 switch  (  pMsg->uiType  )  {
		     case  CONST_misMsgType_req:
				   #if  0
							 if  (  qySendMsg(  &pChannel->session,  &pChannel->sock,  &pQyMc->cfg.to,  pMsg->req.ucFlg,  pMsg->req.usCode,  pMsg->req.tStartTime,  pMsg->req.uiTranNo,  pMsg->req.usSeqNo,  (  char  *  )&pMsg->req.data,  pMsg->req.lenInBytes  )  )  {
								 traceLogA(  (char*)  "qySendMsg failed"  );  goto  errLabel;
							 }
							 //  2009/10/11
							 pChannel->status.netStat.ui64MsgDataLenSent  +=  sizeof(  QY_MSG_HEAD  )  +  pMsg->req.lenInBytes;
				   #endif

				   if  (  qySendMsg_iocp(  pPerSocketContext,  &pChannel->session,  NULL,  &pPerSocketContext->outputContext,  pMsg->req.ucFlg,  pMsg->req.usCode,  0,  pMsg->req.tStartTime,  pMsg->req.uiTranNo,  pMsg->req.usSeqNo,  (  char  *  )&pMsg->req.data,  pMsg->req.lenInBytes  )  )  {
   					   #ifdef  __DEBUG__
							   traceLogA(  (char*)  "qySendMsg failed"  );  
					   #endif
					   goto  errLabel;
				   }
				   pChannel->status.netStat.ui64MsgDataLenSent  +=  sizeof(  QY_MSG_HEAD_n  )  +  pMsg->req.lenInBytes;

				   break;
			 case  CONST_misMsgType_talk:  
							

				   #if  0
						     if  (  qySendMsg(  &pChannel->session,  &pChannel->sock,  &pQyMc->cfg.to,  pMsg->talk.ucFlg,  pMsg->talk.usCode,  pMsg->talk.tStartTime,  pMsg->talk.uiTranNo,  pMsg->talk.usSeqNo,  (  char  *  )&pMsg->talk.data,  pMsg->talk.lenInBytes  )  )  {
								 traceLogA(  (char*)  "qySendMsg failed"  );  goto  errLabel;
							 }
							 //  2009/10/11
							 pChannel->status.netStat.ui64MsgDataLenSent  +=  sizeof(  QY_MSG_HEAD  )  +  pMsg->talk.lenInBytes;
				   #endif

				   if  (  qySendMsg_iocp(  pPerSocketContext,  NULL,  NULL,  &pPerSocketContext->outputContext,  pMsg->talk.ucFlg,  pMsg->talk.usCode,  pMsg->talk.usCode_org,  pMsg->talk.tStartTime,  pMsg->talk.uiTranNo,  pMsg->talk.usSeqNo,  (  char  *  )&pMsg->talk.data,  pMsg->talk.lenInBytes  )  )  {				
   					   #ifdef  __DEBUG__
							   traceLogA(  (char*)  "qySendMsg failed"  );  
					   #endif
					   goto  errLabel;
				   }
				   pChannel->status.netStat.ui64MsgDataLenSent  +=  sizeof(  QY_MSG_HEAD_n  )  +  pMsg->talk.lenInBytes;

				   break;				
			 case  CONST_misMsgType_task:  
			 case  CONST_misMsgType_outputTask:  

				   #if  0
                                         if  (  qySendMsg(  &pChannel->session,  &pChannel->sock,  &pQyMc->cfg.to,  ucFlg,  pMsg->task.usCode,  pMsg->task.tStartTime,  pMsg->task.uiTranNo,  uiSeqNo,  p,  nSend  )  )  {
											 traceLogA(  (char*)  "qySendMsg failed"  );  goto  errLabel;
										 }
										 //  2009/10/11
										 pChannel->status.netStat.ui64MsgDataLenSent  +=  sizeof(  QY_MSG_HEAD  )  +  pMsg->task.lenInBytes;
				   #endif

				   if  (  qySendMsg_iocp(  pPerSocketContext,  &pChannel->session,  NULL,  &pPerSocketContext->outputContext,  pMsg->task.ucFlg,  pMsg->task.usCode,  pMsg->task.usCode_org,  pMsg->task.tStartTime,  pMsg->task.uiTranNo,  pMsg->task.usSeqNo,  (  char  *  )&pMsg->task.data,  pMsg->task.lenInBytes  )  )  {
					   #ifdef  __DEBUG__
							   traceLogA(  (char*)  "qySendMsg failed"  );  
					   #endif
					   goto  errLabel;
				   }
					
				   //  2009/10/11
				   pChannel->status.netStat.ui64MsgDataLenSent  +=  sizeof(  QY_MSG_HEAD_n  )  +  pMsg->task.lenInBytes;

				   break;

			 default:
				    #ifdef  __DEBUG__
							traceLogA(  (char*)  "procOutputQ_iocp: unprocessed msgType"  );
				    #endif
					goto  errLabel;				
	 }
#endif

	//  2009/02/25
	pCtx->o.dwTickCnt_startToSend  =  GetTickCount(  );

	iErr  =  0;

errLabel:

	 if  (  !iErr  )  {
		 if  (  pbMsgExists  )  *pbMsgExists  =  bMsgExists;
	 }

	return  iErr;
}


 int  procMsgFromMgr_isCli(  MIS_CHANNEL  *  pChannel,  unsigned  int  uiMsgType  )
{
	int					iErr		=	-1;
	if  (  !pChannel  )  return  -1;
	CTX_io_iocp		*	pCtx		=	(  CTX_io_iocp  *  )pChannel->p0;
	
	MIS_CNT			*	pMisCnt		=	pChannel->pMisCnt;
	if  (  !pMisCnt  )  return  -1;
	MC_VAR_isCli	*	pProcInfo	=	(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	QY_MC			*	pQyMc		=	(  QY_MC  *  )pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;

	PER_SOCKET_CONTEXT  *  pPerSocketContext	=	pCtx->pPerSocketContext;  


#ifdef  __DEBUG__
		//  qyShowInfo1(  CONST_qyShowType_debug,  0,  0,  _T(  "IsClient"  ),  _T(  ""  ),  pCtx->where_showInfo,  _T(  ""  ),  _T(  "procMsgFromMgr: enters"  )  ); 						   
#endif


	switch  (  uiMsgType  )  {
			case  CONST_misMsgType_send:
				  BOOL  bMsgExists;	bMsgExists  =  FALSE;	//  ´ËÖµÓÉÏÂÃæµÄº¯ÊýÈ¡µÃ

				  {		
					  CQySyncObj	syncObj_cli_rw;

					  if  (  syncObj_cli_rw.sync(  pCtx->mutexName_syncSending  )  )  {		//  2008/05/22
						  goto  errLabel;
					  }

					  if  (  pPerSocketContext->status.ucbSending  )  {
						  iErr  =  0;  goto  errLabel;
					  }

					  pPerSocketContext->status.ucbSending  =  TRUE;
				  }

				  if  (  procOutputQ_iocp_isCli(  pChannel,  pPerSocketContext,  &bMsgExists  )  )  {
					  qyShowInfo1(  CONST_qyShowType_debug,  0,  0,  _T(  "IsClient"  ),  _T(  ""  ),  _T(  ""  ),  _T(  ""  ),  _T(  "procMsgFromMgr: procOutputQ_iocp failed"  )  ); 						   
					  goto  errLabel;
				  }	

					   
				  //  OutputDebugString(  _T(  "procMsgFromMgr , after msg_send\n"  )  );			   
					
				  if  (  !bMsgExists  )  {						

					  {
						  CQySyncObj	syncObj_cli_rw;

						  if  (  syncObj_cli_rw.sync(  pCtx->mutexName_syncSending  )  )  {		//  2008/05/22
							  goto  errLabel;
						  }

						  pPerSocketContext->status.ucbSending  =  FALSE;
					  }

					  //
					  if  (  q2PostMsgAndTrigger(  0,  0,  &pChannel->toSendQ2,  _T(  "procMsgFromMgr_isCli "))) {
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  0,  _T(  "IsClient"  ),  _T(  ""  ),  _T(  ""  ),  _T(  ""  ),  _T(  "procMsgFromMgr: trigger toSendQ failed"  )  ); 						   
						  goto  errLabel;
					  }
				  }
				  break;

			default:
					#ifdef  __DEBUG__
						    traceLog((TCHAR*)  _T(  "procMsgFromMgr_isCli failed: unprocessed msgType %d"  ),  uiMsgType  );
					#endif
					goto  errLabel;
					break;

	}


	iErr  =  0;

errLabel:

	return  iErr;
 }


//
// Worker thread that handles all I/O requests on any socket handle added to the IOCP.
//
DWORD WINAPI mcThreadProc_mis_work_iocp(LPVOID WorkThreadContext) 
{
	int		iErr	=	-1;
	MIS_CHANNEL	*	pChannel	=	(  MIS_CHANNEL  *  )WorkThreadContext;
	if  (  !pChannel  )  {
		return  -1;
	}
	MIS_CNT		*	pMisCnt		=	pChannel->pMisCnt;
	if  (  !pMisCnt  )  return  -1;
	MC_VAR_isCli	*	pProcInfo	=	(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	QY_MC		*	pQyMc		=	pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;

	//
	CTX_io_iocp	*	pCtx		=	(  CTX_io_iocp  *  )pChannel->p0;
	HANDLE hIOCP = (HANDLE)pCtx->hIOCP;


	BOOL bSuccess = FALSE;
	int nRet = 0;
	LPWSAOVERLAPPED lpOverlapped = NULL;
	PPER_SOCKET_CONTEXT pPerSocketContext = NULL;
	PPER_IO_CONTEXT pIoContext = NULL; 
	WSABUF buffRecv;
	WSABUF buffSend;
	DWORD dwRecvNumBytes = 0;
	DWORD dwSendNumBytes = 0;
	DWORD dwFlags = 0;
	DWORD dwIoSize = 0;

	int  iWaitTimeout  =  5000;


#ifdef  __DEBUG__
	traceLog((TCHAR*)  _T(  "work_iocp starts"  )  );
#endif
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  pCtx->where_showInfo,  _T(  ""  ),  _T(  "work_iocp starts"  )  );


	while  (  TRUE  )  {
		
		Param_dbg param;
		param.m_pHint=(TCHAR*)_T("iocp.1034");
		//
		if  (  !bChannelOk(  pChannel,&param  )  )  {

#ifdef  __DEBUG__
				if  (  pChannel->bSessionOpen  )  {
		DWORD	dwTickCnt  =  GetTickCount(  );
		if  (  pChannel->uiType  !=  CONST_channelType_talking  )  {
			if  (  dwTickCnt  -  pChannel->status.dwTickCnt_lastStartToRecv  >  pQyMc->cfg.iTimeoutInMs_channelIdle_others
				&&  dwTickCnt  -  pChannel->status.dwTickCnt_lastEndSending  >  pQyMc->cfg.iTimeoutInMs_channelIdle_others  )
			{
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Channel %s timeout, idle too long, iTimeoutInMs_channelsIdle_others %d"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  ),  pQyMc->cfg.iTimeoutInMs_channelIdle_others  );
			}
			#if  0
				if  (  dwTickCnt  -  pChannel->status.dwTickCnt_lastStartToRecv  >  pQyMc->cfg.iTimeoutInMs_channelIdle_recv_others  )  {
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Channel %s timeout, idle too long, iTimeoutInMs_channelsIdle_recv_others %d"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  ),  pQyMc->cfg.iTimeoutInMs_channelIdle_recv_others  );
					return  FALSE;
				}
			#endif
			}
		else  {
			  if  (  dwTickCnt  -  pChannel->status.dwTickCnt_lastStartToRecv  >  pQyMc->cfg.iTimeoutInMs_channelIdle_recv_talk  )  {				
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Channel %s timeout, idle too long, iTimeoutInMs_channelsIdle_recv_talk %d"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  ),  pQyMc->cfg.iTimeoutInMs_channelIdle_recv_talk  );
			  }
		}
	}

#endif
			break;
		}

        //
		// continually loop to service io completion packets
		//
		bSuccess = GetQueuedCompletionStatus(hIOCP, &dwIoSize,
											 (PDWORD_PTR)&pPerSocketContext,
											 (LPOVERLAPPED *)&lpOverlapped, 
											 iWaitTimeout);

		if  (  !bSuccess  &&  GetLastError(  )  ==  WAIT_TIMEOUT  )  {
			   //  traceLogA(  (char*)  "GetQueuedCompletionStatus: timeout"  );  
			   continue;
		}

		if( !bSuccess )
			traceLogA(  (char*)"GetQueuedCompletionStatus() failed: %d\n", GetLastError());

		if( pPerSocketContext == NULL ) {
			unsigned  int	uiMsgType	=	dwIoSize;



			if  (  uiMsgType  ==  CONST_misMsgType_null  )  {			
				//
				// CTRL-C handler used PostQueuedCompletionStatus to post an I/O packet with
				// a NULL CompletionKey (or if we get one for any reason).  It is time to exit.
				//
			    #ifdef  __DEBUG__
						traceLog((TCHAR*)  _T(  "work_iocp: get quit msg"  )  );	
				#endif

				iErr  =  0;  goto  errLabel;
			}

			if  (  procMsgFromMgr_isCli(  pChannel,  uiMsgType  )  )  {
				#ifdef  __DEBUG__
						traceLog((TCHAR*)  _T(  "work_iocp: procMsgFromMgr_isCli failed"  )  );
			    #endif
				goto  errLabel;
			}

			continue;
		}

#if  0
		if( g_bEndServer ) {

			//
			// main thread will do all cleanup needed - see finally block
			//
			return(0);
		}
#endif

		if( !bSuccess || (bSuccess && (dwIoSize == 0)) ) {

			//
			// client connection dropped, continue to service remaining (and possibly 
			// new) client connections
			//

			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "work_iocp: client connection dropped"  )  );	
			#endif

			iErr  =  0;  goto  errLabel;
		}

        //
		// determine what type of IO packet has completed by checking the PER_IO_CONTEXT 
		// associated with this socket.  This will determine what action to take.
		//
		pIoContext = (PPER_IO_CONTEXT)lpOverlapped;

		pIoContext->dwIoBytes  =  dwIoSize;

		switch  (  pIoContext->ioOperation  )  {
				case  CONST_io_read:
								   
					  unsigned  char  ucbDataDone;  ucbDataDone  =  FALSE;

					   if  (  !pIoContext->ucbDataDone  )  {
						   if  (  qyRecvMsg_iocp(  pPerSocketContext,  NULL,  NULL,  pIoContext,  &ucbDataDone  )  )  goto  errLabel;
					   }
					   if  (  !ucbDataDone  )  {
						   continue;
					   }

					   if  (  proc_io_read(  pChannel,  pPerSocketContext  )  )  {
						   #ifdef  __DEBUG__
								   traceLog((TCHAR*)  _T(  "work_iocp: proc_io_read failed"  )  );
						   #endif
						   goto  errLabel;
					   }


					   MACRO_memset_perIoContext(  pPerSocketContext->inputContext  );
					   if  (  qyRecvMsg_iocp(  pPerSocketContext,  NULL,  NULL,  &pPerSocketContext->inputContext,  NULL  )  )  {
						   goto  errLabel;
					   }

					  break;

				case  CONST_io_write:

					   if  (  !pIoContext->ucbDataDone  )  {
						   if  (  qySendMsg_iocp(  pPerSocketContext,  &pChannel->session,  NULL,  pIoContext,  0,  0,  0,  0,  0,  0,  0,  0  )  )  goto  errLabel;
					   }
					   if  (  !pIoContext->ucbDataDone  )  {
						   iErr  =  0;  goto  errLabel;
					   }

					   BOOL  bMsgExists;	bMsgExists  =  FALSE;

					   //
					   if  (  procOutputQ_iocp_isCli(  pChannel,  pPerSocketContext,  &bMsgExists  )  )  {
						   qyShowInfo1(  CONST_qyShowType_debug,  0,  0,  _T(  "Server"  ),  _T(  ""  ),  _T(  ""  ),  _T(  ""  ),  _T(  "work_iocp: procOutputQ_iocp failed"  )  ); 						   
						   #ifdef  __DEBUG__
								   traceLog((TCHAR*)  _T(  "work_iocp: procOutputQ_iocp_isCli failed"  )  );
						   #endif
						   goto  errLabel;
					   }

					   if  (  !bMsgExists  )  {

						   {	//  2011/01/25
							   CQySyncObj	syncObj_cli_rw;

							   if  (  syncObj_cli_rw.sync(  pCtx->mutexName_syncSending  )  )  {
								   qyShowInfo1(  CONST_qyShowType_debug,  0,  (char*)(  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""  ),  _T(  "work_iocp: syncObj_cli_w failed"  )  ); 						   
								   goto  errLabel;
							   }

							   pPerSocketContext->status.ucbSending  =  FALSE;
						   }

						   //
						   if  (  q2PostMsgAndTrigger(  0,  0,  &pChannel->toSendQ2,  _T(  "work_iocp"  ))) {
							   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  0,  _T(  "IsClient"  ),  _T(  ""  ),  _T(  ""  ),  _T(  ""  ),  _T(  "work_iocp: trigger toSendQ failed"  )  ); 						   
							   goto  errLabel;
						   }

					   }		  

					  break;
				default:
						break;

		} //switch

		//
		continue;

	} //while

	iErr  =  0;

errLabel:

	 if  (  pMisCnt  )  {
		 pChannel->status.ulbSessionErr  =  TRUE;
		 pChannel->status.ulbSndQuit  =  TRUE;
	 }

	#ifdef  __DEBUG__
			traceLog((TCHAR*)  _T(  "work_iocp: leaves"  )  );	
	#endif
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  pCtx->where_showInfo,  _T(  ""  ),  _T(  "work_iocp leaves"  )  );

	return  iErr;
} 


#if 0
//  2015/09/05
 extern  "C"  int  iisetSockTimeout_toClose(  SOCK_TIMEOUT  *  p  )
{
	p->iAccept  =  1000;
	p->iConnect  =  1000;
	p->iRead  =  1000;
	p->iWrite  =  1000;
	p->iSelect  =  1000;
	
	return 0;
}
#endif



 //

