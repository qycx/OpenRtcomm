

#include	"stdafx.h"

#include	<winsock2.h>
#include	<mswsock.h>
#include	<windows.h>
#include	<stdlib.h>
#include	<tchar.h>

#include	"qyCommon.h"
#include	"qyTCharCommProc.h"
#include	"qySyncCommProc.h"
#include	"genericQueue.h"

#include	"qyWmComm.h"
#include	"qyCommCommon.h"

#include	"qyLicense.h"
#include	"qyCommProc.h"
#include	"qyLangCommProc.h"						//  2005/01/24

#include	"qyMsgFunc.h"
#include	"mtSock_iOCP.h"

#include	"qnmCommProc.h"

#include	"qySyncCommProc.h"
#include <anCommProc.h>



//
  BOOL  bCliIndexValid(  MT_SOCK_IOCP  *  pMtSock,  unsigned  int  uiCliIndex  )
{
	 return  (  uiCliIndex  <  mycountof(  pMtSock->cliInfos  )  );
}

 //  accept
 extern  "C"  int  getRemoteIpBySocket_iocp(  MT_SOCK_IOCP  *  pMtSock,  PER_IO_CONTEXT  *  pIoContext_servSock,  char  *  remoteIp,  unsigned  int  size  )
{			
	 int			iErr		=	-1;
	 SOCKADDR  *	remote		=	NULL;
	 SOCKADDR  *	local		=	NULL;
	 int			remote_len  =	sizeof(  SOCKADDR_IN  );
	 int			local_len	=	sizeof(  SOCKADDR_IN  );
	 char		*	ptr			=	NULL;
	
	 if  (  !pMtSock  ||  !pMtSock->lpfnGetAcceptExSockAddrs  ||  !pIoContext_servSock  )  return  -1;
	 if  (  pIoContext_servSock->ioOperation  !=  CONST_io_accept  )  return  -1;

	 pMtSock->lpfnGetAcceptExSockAddrs(  pIoContext_servSock->buf,  0,  sizeof(  SOCKADDR_IN  )  +  16,  sizeof(  SOCKADDR_IN  )  +  16,  &local,  &local_len,  &remote,  &remote_len  );
	 if  (  remote  )  ptr  =  inet_ntoa(  (  (  struct  sockaddr_in  *  )remote  )->sin_addr  );
	 //		 
	 if  (  !ptr  )  remoteIp[0]  =  0;
	 else  _snprintf(  remoteIp,  size,  "%s",  ptr  );
							 
	 return  0;
}

  //  这个函数为超时而做的
 void  setIoTime(  PER_SOCKET_CONTEXT  *  pPerSocketContext,  ENUM_IO_OPERATION  io,  BOOL  bStart  )
{
	 DWORD					dwTickCnt			=	GetTickCount(  );

	 //
	 if  (  !pPerSocketContext  )  return;

	 //
	 switch  (  io  )  {
			 case  CONST_io_null:
				   memset(  &pPerSocketContext->status.recv,  0,  sizeof(  pPerSocketContext->status.recv  )  );
				   memset(  &pPerSocketContext->status.snd,  0,  sizeof(  pPerSocketContext->status.snd  )  );
				   break;
			 case  CONST_io_read:  				   
				   if  (  bStart  )  {
					   memset(  &pPerSocketContext->status.recv,  0,  sizeof(  pPerSocketContext->status.recv  )  );
					   pPerSocketContext->status.recv.dwTickCnt_recv_start  =  GetTickCount(  );
					   }
				   else  {
				   }
				   break;
			 case  CONST_io_write:
				   if  (  bStart  )  {
					   memset(  &pPerSocketContext->status.snd,  0,  sizeof(  pPerSocketContext->status.snd  )  );
					   pPerSocketContext->status.snd.dwTickCnt_snd_start  =  GetTickCount(  );
					   }
				   else  {					     
				   }
				   break;
			 default:
					break;
					
	 }

	 
	 return;
}




#if 0
 //  2012/02/25, 准备改成更通用的
 int  2026_0801_qyRecvMsg_iocp(  MT_SOCK_IOCP  *  pMtSock,  PER_SOCKET_CONTEXT  *  pPerSocketContext,  PER_IO_CONTEXT  *  pIoContext,  unsigned  char  *  pucbDataDone  )
{
	 int						iErr		=	-1;
	 unsigned		int			uiCliIndex  =	pPerSocketContext->uiCliIndex;
	 QY_MSG_HEAD_h			*	pReqHead	=	0;;			
	 int						iRet;
	 DWORD						dwIoBytes	=	0;
	 DWORD						dwFlags		=	0;
	 MT_SOCK_CLIINFO_IOCP	*	pCliInfo	=	&pMtSock->cliInfos[uiCliIndex];
	 char					*	encBuf		=	NULL;		  
	 unsigned  int				encLen		=	CONST_maxReqDataLen_enc_is;
	 QY_MSG_HEAD_h			*	pMsgHead	=	0;
	 //QY_COMM_SESSION		*	pSession	=	(  QY_COMM_SESSION  *  )pMtSock->pSessions[uiCliIndex];
	 //  char					*	dataBuf		=	0;
	 unsigned  int				bufSize		=	0;
	 unsigned  char				ucbDataDone	=	FALSE;

	 if  (  pIoContext->ucbDataDone  )  return  -1;

	 pIoContext->nTotalBytes  +=  pIoContext->dwIoBytes;	//  ÕâÊÇ±íÃ÷ÒÑ¾­¶ÁÈ¡¹ýÁË

	 if  (  !pIoContext->nTotalBytes  )  {	//  ¸Õ¿ªÊ¼¸³ÉÏÆðÊ¼Ê±¼ä
		 setIoTime(  pPerSocketContext,  CONST_io_read,  TRUE  );	
		}
	 else  {
		   if  (  !pPerSocketContext->status.recv.dwTickCnt_recv_first  )  pPerSocketContext->status.recv.dwTickCnt_recv_first  =  GetTickCount(  );
	 }

	 if  (  pIoContext->nTotalBytes  <  sizeof(  QY_MSG_HEAD_n  )  )  {	//  ÏÈ¶ÁÒ»¸öhead
		 pIoContext->ioOperation  =  CONST_io_read;
		 pIoContext->wsaBuf.len  =  sizeof(  QY_MSG_HEAD_n  )  -  pIoContext->nTotalBytes;
		 pIoContext->wsaBuf.buf  =  pIoContext->buf  +  pIoContext->nTotalBytes;
		 memset(  &pIoContext->overlapped,  0,  sizeof(  pIoContext->overlapped  )  );
		 iRet = WSARecv(  pMtSock->cliInfos[uiCliIndex].cliSockFd,  &(pIoContext->wsaBuf),  1,  &dwIoBytes,  &dwFlags,  &pIoContext->overlapped,  NULL  );
		 if  (  iRet  ==  SOCKET_ERROR  &&  (  ERROR_IO_PENDING  !=  WSAGetLastError(  )  )  )  {
			 qyDisplayLastError(  (char*)"Initial WSARecv Failed"  );  goto  errLabel;
		 }						 

		 iErr  =  0;  goto  errLabel;
	 }
	 if  (  !pIoContext->ucbCommHeadDone  )  {
		 //
		 QY_MSG_HEAD_n  tmpHead;
#if  0
		 memcpy(  &pIoContext->msgHead,  pIoContext->buf,  sizeof(  pIoContext->msgHead  )  );
		 MACRO_ntohs(  pIoContext->msgHead.usCode  );
		 MACRO_ntohl(  pIoContext->msgHead.uiLen  );
		 MACRO_ntohl64(  pIoContext->msgHead.i64StartTime  );
		 MACRO_ntohl(  pIoContext->msgHead.uiTranNo  );
		 MACRO_ntohs(  pIoContext->msgHead.usSeqNo  );
#endif 
		 memcpy(&tmpHead, pIoContext->buf, sizeof(tmpHead));
		 //
		 AT_MSG_HEAD_ntoh(pCliInfo->i64StartTime_base,  &tmpHead, &pIoContext->msgHead);		 
		 //
		 pIoContext->ucbCommHeadDone  =  TRUE;
	 }

	 //  if  (  pIoContext->msgHead.uiLen  +  sizeof(  pIoContext->msgHead  )  >  sizeof(  pIoContext->buf  )  )  
	 if  (  pIoContext->msgHead.uiLen  >  sizeof(  pIoContext->buf  )  -  sizeof(  QY_MSG_HEAD_n  )  )  //  注意：这里的uiLen可能会很大，如果使用上面的+会产生溢出。
	 {
		 traceLogA(  (char*)  "qyRecvMsg err, dataLen is %d",  pIoContext->msgHead.uiLen  );
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  pPerSocketContext->clientIp,  _T(  "Server"  ),  _T(  ""  ),  _T(  ""  ),  _T(  "qyRecvMsg err. "  ),  _T(  "too large data, dataLen is %d"  ),  pIoContext->msgHead.uiLen  );
		 goto  errLabel;
	 }

	 if  (  pIoContext->msgHead.uiLen  +  sizeof(  QY_MSG_HEAD_n  )  >  pIoContext->nTotalBytes  )  {
		 pIoContext->ioOperation  =  CONST_io_read;		 
		 pIoContext->wsaBuf.len  =  pIoContext->msgHead.uiLen  +  sizeof(  QY_MSG_HEAD_n  )  -  pIoContext->nTotalBytes;
		 pIoContext->wsaBuf.buf  =  pIoContext->buf  +  pIoContext->nTotalBytes;
		 memset(  &pIoContext->overlapped,  0,  sizeof(  pIoContext->overlapped  )  );
		 iRet = WSARecv(  pMtSock->cliInfos[uiCliIndex].cliSockFd,  &(pIoContext->wsaBuf),  1,  &dwIoBytes,  &dwFlags,  &pIoContext->overlapped,  NULL  );
		 if  (  iRet  ==  SOCKET_ERROR  &&  (  ERROR_IO_PENDING  !=  WSAGetLastError(  )  )  )  {
			 qyDisplayLastError(  (char*)"Initial WSARecv Failed"  );  goto  errLabel;
		 }						 
		 iErr  =  0;  goto  errLabel;
	 }

	 if  (  pIoContext->msgHead.uiLen  +  sizeof(  QY_MSG_HEAD_n  )  !=  pIoContext->nTotalBytes  )  {
		 traceLogA(  (char*)  "msgHead error"  );  goto  errLabel;
		 //  
	 }

	 //  
	 setIoTime(  pPerSocketContext,  CONST_io_read,  FALSE  );

	 pMsgHead  =  &pIoContext->msgHead;

	 if  (  pMsgHead->uiLen  )  {	 	 

#if  0
		 memcpy(  encBuf,  pIoContext->buf  +  sizeof(  QY_MSG_HEAD  ),  pIoContext->msgHead.usLen  );

		 dataBuf  =  pIoContext->buf;
#endif

		 bufSize  =  sizeof(  pIoContext->buf  );
		 //
#if  0  //  2015/08/25
		 if  (  pSession->service.encType  ==  CONST_qyEncType_qwm  )  {
			 if  (  !(  encBuf  =  (  char  *  )mymalloc(  encLen  )  )  )  goto  errLabel;
	 
			 if  (  pMsgHead->uiLen  >  encLen  )  {  
				 traceLogA(  (char*)  "qyRecvMsg_iocp error, pMsgHead->usLen [%d] > encLen [%d].",  pMsgHead->uiLen,  encLen  );
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  pPerSocketContext->clientIp,  _T(  "Server"  ),  _T(  ""  ),  _T(  ""  ),  _T(  "qyRecvMsg err. "  ),  _T(  "too large data, dataLen [%d] "  ),  pMsgHead->uiLen  );
				 iErr  =  -2;  goto  errLabel;  
			 }

			 memcpy(  encBuf,  pIoContext->buf  +  sizeof(  QY_MSG_HEAD  ),  pIoContext->msgHead.uiLen  );
	
			 char  *  dataBuf  =  pIoContext->buf;

			 if  (  qnmDecData(  &pSession->commEncCtx,  encBuf,  pMsgHead->uiLen,  dataBuf,  &bufSize  )  )  {
				 traceLogA(  (char*)  "qyRecvReqÀïqnmDecData failed"  );  goto  errLabel;
			 }
			 pMsgHead->uiLen  =  bufSize;
			 }
		 else
#endif
			 //
			 if  (  pMsgHead->uiLen  >  bufSize  )  {  iErr  =  -2;  goto  errLabel;  }
		 else  {
			   //  memcpy(  dataBuf,  encBuf,  pMsgHead->usLen  );
			   memcpy(  pIoContext->buf,  pIoContext->buf  +  sizeof(  QY_MSG_HEAD_n  ),  pMsgHead->uiLen  );
		 }
	 }
	 
	 if  (  isUcFlgResp(  pMsgHead->ucFlg  )  )  pCliInfo->sessionData.usLastRespCode_i  =  pMsgHead->usCode;
	 else  pCliInfo->sessionData.usLastReqCode_i  =  pMsgHead->usCode;

	 pIoContext->ucbDataDone  =  TRUE;
	 
	 ucbDataDone  =  TRUE;		//  2011/01/24

	 //  2011/01/10
	 if  (  pCliInfo->sessionData.bAdmin1  )  {
		 pMtSock->status.netStat_admin.ui64MsgDataLenRecvd  +=  pIoContext->nTotalBytes;
		 }
	 else  {
		   pPerSocketContext->status.netStat.ui64MsgDataLenRecvd  +=  pIoContext->nTotalBytes;
	 }

	 //
	 iErr  =  0;
errLabel:
	 if  (  encBuf  )  free(  encBuf  );

	 if  (  !iErr  )  {
		 if  (  pucbDataDone  )  *pucbDataDone  =  ucbDataDone;
	 }

	 if  (  iErr  )  {
		 traceLog((TCHAR*)  _T(  "qyRecvMsg_iocp failed."  )  );
	 }

	 return  iErr;
}
#endif

//
//  2012/02/25, 准备改成更通用的
int  qyRecvMsg_iocp(MT_SOCK_IOCP * pMtSock, PER_SOCKET_CONTEXT * pPerSocketContext, PER_IO_CONTEXT * pIoContext, unsigned  char* pucbDataDone)
{
	int						iErr = -1;
	unsigned		int			uiCliIndex = pPerSocketContext->uiCliIndex;
	QY_MSG_HEAD_h* pReqHead = 0;;
	int						iRet;
	DWORD						dwIoBytes = 0;
	DWORD						dwFlags = 0;
	MT_SOCK_CLIINFO_IOCP* pCliInfo = &pMtSock->cliInfos[uiCliIndex];
	char* encBuf = NULL;
	unsigned  int				encLen = CONST_maxReqDataLen_enc_is;
	QY_MSG_HEAD_h* pMsgHead = 0;
	//QY_COMM_SESSION		*	pSession	=	(  QY_COMM_SESSION  *  )pMtSock->pSessions[uiCliIndex];
	//  char					*	dataBuf		=	0;
	unsigned  int				bufSize = 0;
	unsigned  char				ucbDataDone = FALSE;
	//
	CTX_caller					caller(_T("qyRecvMsg_iocp"));

	//
#ifdef  __DEBUG__
		//
#endif 

	//
	if (pIoContext->ucbDataDone)  return  -1;

	pIoContext->nTotalBytes += pIoContext->dwIoBytes;	//  ÕâÊÇ±íÃ÷ÒÑ¾­¶ÁÈ¡¹ýÁË

	if (!pIoContext->nTotalBytes) {	//  ¸Õ¿ªÊ¼¸³ÉÏÆðÊ¼Ê±¼ä
		setIoTime(pPerSocketContext, CONST_io_read, TRUE);
	}
	else {
		if (!pPerSocketContext->status.recv.dwTickCnt_recv_first)  pPerSocketContext->status.recv.dwTickCnt_recv_first = GetTickCount();
	}

	// 先讀一個flg
	//
	if (pIoContext->nTotalBytes < sizeof(byte)) {	//  ÏÈ¶ÁÒ»¸öhead
		pIoContext->ioOperation = CONST_io_read;
		pIoContext->wsaBuf.len = sizeof(byte) - pIoContext->nTotalBytes;
		pIoContext->wsaBuf.buf = pIoContext->buf + pIoContext->nTotalBytes;
		memset(&pIoContext->overlapped, 0, sizeof(pIoContext->overlapped));
		iRet = WSARecv(pMtSock->cliInfos[uiCliIndex].cliSockFd, &(pIoContext->wsaBuf), 1, &dwIoBytes, &dwFlags, &pIoContext->overlapped, NULL);
		if (iRet == SOCKET_ERROR && (ERROR_IO_PENDING != WSAGetLastError())) {
			qyDisplayLastError((char*)"Initial WSARecv Failed");  goto  errLabel;
		}

		iErr = 0;  goto  errLabel;
	}
	if (!pIoContext->ucbFlgDone) {
		//
		byte  ucFlg;
		//
		memcpy(&ucFlg, pIoContext->buf, sizeof(ucFlg));
		//
		int  headLen = 0;
		//
#if  0
		if (pMtSock->pMtSockDbgStatus->m_var.bUse_head16) {
			headLen = 16;// sizeof(AT_MSG_HEAD_n);
		}
		else 
#endif
		{
			if (isUcFlgHead14(ucFlg)) {
				headLen = 14;// sizeof(AT_MSG_HEAD14_n);
				if (!isUcFlgMoreData(ucFlg))  headLen -= 2;
			}
			else {
				headLen = 22;// sizeof(AT_MSG_HEAD22_n);
				if (!isUcFlgMoreData(ucFlg))  headLen -= 2;
			}
		}
		//
		pIoContext->headLen = headLen;
		//
		pIoContext->ucbFlgDone = TRUE;
	}

	//
	if (pIoContext->nTotalBytes < pIoContext->headLen) {	//  ÏÈ¶ÁÒ»¸öhead
		pIoContext->ioOperation = CONST_io_read;
		pIoContext->wsaBuf.len = pIoContext->headLen - pIoContext->nTotalBytes;
		pIoContext->wsaBuf.buf = pIoContext->buf + pIoContext->nTotalBytes;
		memset(&pIoContext->overlapped, 0, sizeof(pIoContext->overlapped));
		iRet = WSARecv(pMtSock->cliInfos[uiCliIndex].cliSockFd, &(pIoContext->wsaBuf), 1, &dwIoBytes, &dwFlags, &pIoContext->overlapped, NULL);
		if (iRet == SOCKET_ERROR && (ERROR_IO_PENDING != WSAGetLastError())) {
			qyDisplayLastError((char*)"Initial WSARecv Failed");  goto  errLabel;
		}

		iErr = 0;  goto  errLabel;
	}
	if (!pIoContext->ucbCommHeadDone) {
		//  讀完head,就要轉成本地結構
		byte  ucFlg = pIoContext->buf[0];
		//
#if  0
		if (pMtSock->pMtSockDbgStatus->m_var.bUse_head16) {
			AT_MSG_HEAD16_n  tmpHead_n;
			//		
			memcpy(&tmpHead_n, pIoContext->buf, pIoContext->headLen);
			//
			AT_MSG_HEAD16_ntoh(&caller,pCliInfo->i64StartTime_base2, &tmpHead_n, &pIoContext->msgHead);
		}
		else
#endif 
		{
			//
			if (isUcFlgHead14(ucFlg)) {
				AT_MSG_HEAD14_n  tmpHead14_n;
				memset(&tmpHead14_n, 0, sizeof(tmpHead14_n));
				//		
				memcpy(&tmpHead14_n, pIoContext->buf, pIoContext->headLen);
				//
				AT_MSG_HEAD14_ntoh(&caller, pCliInfo->i64StartTime_base2, &tmpHead14_n, &pIoContext->msgHead);
			}
			else {
				AT_MSG_HEAD22_n  tmpHead22_n;
				memset(&tmpHead22_n, 0, sizeof(tmpHead22_n));
				//		
				memcpy(&tmpHead22_n, pIoContext->buf, pIoContext->headLen);
				//
				AT_MSG_HEAD22_ntoh(&caller, pCliInfo->i64StartTime_base2, &tmpHead22_n, &pIoContext->msgHead);
			}
			//
			pIoContext->msgHead.ucFlg &= ~CONST_atCommFlg_head14;
		}
		//
#ifdef  __DEBUG__
		if (0) {
			TCHAR  tBuf[128];
			_sntprintf(tBuf, mycountof(tBuf), _T("qyRecvMsg_iocp: bCommHeadDone, cliIndex %d"), uiCliIndex);
			showInfo_open(0, 0, 0, tBuf);
		}
		//
		if (pIoContext->msgHead.uiTranNo == 1025) {
			int  ii = 0;
		}
#endif 
		//
		pIoContext->ucbCommHeadDone = TRUE;
	}

	//  if  (  pIoContext->msgHead.uiLen  +  sizeof(  pIoContext->msgHead  )  >  sizeof(  pIoContext->buf  )  )  
	if (pIoContext->msgHead.uiLen > sizeof(pIoContext->buf) - pIoContext->headLen)  //  注意：这里的uiLen可能会很大，如果使用上面的+会产生溢出。
	{
		traceLogA((char*)"qyRecvMsg err, dataLen is %d", pIoContext->msgHead.uiLen);
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, pPerSocketContext->clientIp, _T("Server"), _T(""), _T(""), _T("qyRecvMsg err. "), _T("too large data, dataLen is %d"), pIoContext->msgHead.uiLen);
		goto  errLabel;
	}

	if (pIoContext->msgHead.uiLen + pIoContext->headLen > pIoContext->nTotalBytes) {
		pIoContext->ioOperation = CONST_io_read;
		pIoContext->wsaBuf.len = pIoContext->msgHead.uiLen + pIoContext->headLen - pIoContext->nTotalBytes;
		pIoContext->wsaBuf.buf = pIoContext->buf + pIoContext->nTotalBytes;
		memset(&pIoContext->overlapped, 0, sizeof(pIoContext->overlapped));
		iRet = WSARecv(pMtSock->cliInfos[uiCliIndex].cliSockFd, &(pIoContext->wsaBuf), 1, &dwIoBytes, &dwFlags, &pIoContext->overlapped, NULL);
		if (iRet == SOCKET_ERROR && (ERROR_IO_PENDING != WSAGetLastError())) {
			qyDisplayLastError((char*)"Initial WSARecv Failed");  goto  errLabel;
		}
		iErr = 0;  goto  errLabel;
	}

	if (pIoContext->msgHead.uiLen + pIoContext->headLen != pIoContext->nTotalBytes) {
		traceLogA((char*)"msgHead error");  
		goto  errLabel;
		//  
	}

	//  
	setIoTime(pPerSocketContext, CONST_io_read, FALSE);

	pMsgHead = &pIoContext->msgHead;

	if (pMsgHead->uiLen) {

		//
		bufSize = sizeof(pIoContext->buf);
		//
		if (pMsgHead->uiLen > bufSize) { iErr = -2;  goto  errLabel; }
		else {
			//  memcpy(  dataBuf,  encBuf,  pMsgHead->usLen  );
			memcpy(pIoContext->buf, pIoContext->buf + pIoContext->headLen, pMsgHead->uiLen);
		}
	}

	if (isUcFlgResp(pMsgHead->ucFlg))  pCliInfo->sessionData.usLastRespCode_i = pMsgHead->usCode;
	else  pCliInfo->sessionData.usLastReqCode_i = pMsgHead->usCode;

	//
	pIoContext->ucbDataDone = TRUE;

	ucbDataDone = TRUE;		//  2011/01/24

	//  2011/01/10
	if (pCliInfo->sessionData.bAdmin1) {
		pMtSock->status.netStat_admin.ui64MsgDataLenRecvd += pIoContext->nTotalBytes;
	}
	else {
		pPerSocketContext->status.netStat.ui64MsgDataLenRecvd += pIoContext->nTotalBytes;
	}

	//
#ifdef  __DEBUG__
		//
		if (pIoContext->msgHead.uiTranNo == 345) {
			int  ii = 0;
		}
		if (pIoContext->msgHead.uiTranNo == 444) {
			int  ii = 0;
		}
#endif 


	//
	iErr = 0;
errLabel:
	if (encBuf)  free(encBuf);

	if (!iErr) {
		if (pucbDataDone)  *pucbDataDone = ucbDataDone;
	}

	if (iErr) {
		traceLog((TCHAR*)_T("qyRecvMsg_iocp failed."));
	}

	return  iErr;
}










#if  0
 //  2012/02/25, 准备改成更通用的
 int  unused_qyRecvMsg_iocp(  PER_SOCKET_CONTEXT  *  pPerSocketContext,  QY_COMM_SESSION  *  pSession,  IM_NET_STAT  *  pNetStat_admin,  PER_IO_CONTEXT  *  pIoContext,  unsigned  char  *  pucbDataDone  )
{
	 int						iErr		=	-1;
	 unsigned		int			uiCliIndex  =	pPerSocketContext->uiCliIndex;
	 QY_MSG_HEAD_h			*	pReqHead	=	0;;			
	 int						iRet;
	 DWORD						dwIoBytes	=	0;
	 DWORD						dwFlags		=	0;
	 //  MT_SOCK_CLIINFO_IOCP	*	pCliInfo	=	&pMtSock->cliInfos[uiCliIndex];
	 char					*	encBuf		=	NULL;		  
	 unsigned  int				encLen		=	CONST_maxReqDataLen_enc_is;
	 QY_MSG_HEAD_h			*	pMsgHead	=	0;
	 //  QY_COMM_SESSION		*	pSession	=	(  QY_COMM_SESSION  *  )pMtSock->pSessions[uiCliIndex];
	 //  char					*	dataBuf		=	0;
	 unsigned  int				bufSize		=	0;
	 unsigned  char				ucbDataDone	=	FALSE;

	 if  (  pIoContext->ucbDataDone  )  return  -1;

	 pIoContext->nTotalBytes  +=  pIoContext->dwIoBytes;	//  ÕâÊÇ±íÃ÷ÒÑ¾­¶ÁÈ¡¹ýÁË

	 if  (  !pIoContext->nTotalBytes  )  {	//  ¸Õ¿ªÊ¼¸³ÉÏÆðÊ¼Ê±¼ä
		 setIoTime(  pPerSocketContext,  CONST_io_read,  TRUE  );	
		}
	 else  {
		   if  (  !pPerSocketContext->status.recv.dwTickCnt_recv_first  )  pPerSocketContext->status.recv.dwTickCnt_recv_first  =  GetTickCount(  );
	 }

	 if  (  pIoContext->nTotalBytes  <  sizeof(  QY_MSG_HEAD_n  )  )  {	//  ÏÈ¶ÁÒ»¸öhead
		 pIoContext->ioOperation  =  CONST_io_read;
		 pIoContext->wsaBuf.len  =  sizeof(  QY_MSG_HEAD_n  )  -  pIoContext->nTotalBytes;
		 pIoContext->wsaBuf.buf  =  pIoContext->buf  +  pIoContext->nTotalBytes;
		 memset(  &pIoContext->overlapped,  0,  sizeof(  pIoContext->overlapped  )  );
		 iRet = WSARecv(  pPerSocketContext->sockFd,  &(pIoContext->wsaBuf),  1,  &dwIoBytes,  &dwFlags,  &pIoContext->overlapped,  NULL  );
		 if  (  iRet  ==  SOCKET_ERROR  &&  (  ERROR_IO_PENDING  !=  WSAGetLastError(  )  )  )  {
			 qyDisplayLastError(  (char*)"Initial WSARecv Failed"  );  goto  errLabel;
		 }						 

		 iErr  =  0;  goto  errLabel;
	 }
	 if  (  !pIoContext->ucbCommHeadDone  )  {
		 QY_MSG_HEAD_n  msgHead_n;
#if  0
		 memcpy(  &pIoContext->msgHead,  pIoContext->buf,  sizeof(  pIoContext->msgHead  )  );
		 MACRO_ntohs(  pIoContext->msgHead.usCode  );
		 MACRO_ntohl(  pIoContext->msgHead.uiLen  );
		 MACRO_ntohl64(  pIoContext->msgHead.i64StartTime  );
		 MACRO_ntohl(  pIoContext->msgHead.uiTranNo  );
		 MACRO_ntohs(  pIoContext->msgHead.usSeqNo  );
#endif 
		 //
		 memcpy(&msgHead_n, pIoContext->buf, sizeof(msgHead_n));
		 AT_MSG_HEAD_ntoh(pSession->service.i64StartTime_base,  &msgHead_n, &pIoContext->msgHead);
		 //
		 pIoContext->ucbCommHeadDone  =  TRUE;
	 }

	 //  if  (  pIoContext->msgHead.uiLen  +  sizeof(  pIoContext->msgHead  )  >  sizeof(  pIoContext->buf  )  )  
	 if  (  pIoContext->msgHead.uiLen  >  sizeof(  pIoContext->buf  )  -  sizeof(  QY_MSG_HEAD_n  )  )  //  注意：这里的uiLen可能会很大，如果使用上面的+会产生溢出。
	 {
		 traceLogA(  (char*)  "qyRecvMsg err, dataLen is %d",  pIoContext->msgHead.uiLen  );
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  pPerSocketContext->clientIp,  _T(  "Server"  ),  _T(  ""  ),  _T(  ""  ),  _T(  "qyRecvMsg err. "  ),  _T(  "too large data, dataLen is %d"  ),  pIoContext->msgHead.uiLen  );
		 goto  errLabel;
	 }

	 if  (  pIoContext->msgHead.uiLen  +  sizeof(  QY_MSG_HEAD_n  )  >  pIoContext->nTotalBytes  )  {
		 pIoContext->ioOperation  =  CONST_io_read;		 
		 pIoContext->wsaBuf.len  =  pIoContext->msgHead.uiLen  +  sizeof(  QY_MSG_HEAD_n  )  -  pIoContext->nTotalBytes;
		 pIoContext->wsaBuf.buf  =  pIoContext->buf  +  pIoContext->nTotalBytes;
		 memset(  &pIoContext->overlapped,  0,  sizeof(  pIoContext->overlapped  )  );
		 iRet = WSARecv(  pPerSocketContext->sockFd,  &(pIoContext->wsaBuf),  1,  &dwIoBytes,  &dwFlags,  &pIoContext->overlapped,  NULL  );
		 if  (  iRet  ==  SOCKET_ERROR  &&  (  ERROR_IO_PENDING  !=  WSAGetLastError(  )  )  )  {
			 qyDisplayLastError(  (char*)"Initial WSARecv Failed"  );  goto  errLabel;
		 }						 
		 iErr  =  0;  goto  errLabel;
	 }

	 if  (  pIoContext->msgHead.uiLen  +  sizeof(  QY_MSG_HEAD_n  )  !=  pIoContext->nTotalBytes  )  {
		 traceLogA(  (char*)  "msgHead error"  );  goto  errLabel;
		 //  
	 }

	 //  
	 setIoTime(  pPerSocketContext,  CONST_io_read,  FALSE  );

	 pMsgHead  =  &pIoContext->msgHead;

	 if  (  pMsgHead->uiLen  )  {	 	 

#if  0
		 memcpy(  encBuf,  pIoContext->buf  +  sizeof(  QY_MSG_HEAD  ),  pIoContext->msgHead.usLen  );

		 dataBuf  =  pIoContext->buf;
#endif

		 bufSize  =  sizeof(  pIoContext->buf  );
		 //
		 if  (  pSession  &&  pSession->service.encType  ==  CONST_qyEncType_qwm  )  {
			 if  (  !(  encBuf  =  (  char  *  )mymalloc(  encLen  )  )  )  goto  errLabel;
	 
			 if  (  pMsgHead->uiLen  >  encLen  )  {  
				 traceLogA(  (char*)  "qyRecvMsg_iocp error, pMsgHead->usLen [%d] > encLen [%d].",  pMsgHead->uiLen,  encLen  );
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  pPerSocketContext->clientIp,  _T(  "Server"  ),  _T(  ""  ),  _T(  ""  ),  _T(  "qyRecvMsg err. "  ),  _T(  "too large data, dataLen [%d] "  ),  pMsgHead->uiLen  );
				 iErr  =  -2;  goto  errLabel;  
			 }

			 memcpy(  encBuf,  pIoContext->buf  +  sizeof(  QY_MSG_HEAD_n  ),  pIoContext->msgHead.uiLen  );
	
			 char  *  dataBuf  =  pIoContext->buf;

			 if  (  qnmDecData(  &pSession->commEncCtx,  encBuf,  pMsgHead->uiLen,  dataBuf,  &bufSize  )  )  {
				 traceLogA(  (char*)  "qyRecvReqÀïqnmDecData failed"  );  goto  errLabel;
			 }
			 pMsgHead->uiLen  =  bufSize;
			 }
		 else  if  (  pMsgHead->uiLen  >  bufSize  )  {  iErr  =  -2;  goto  errLabel;  }
		 else  {
			   //  memcpy(  dataBuf,  encBuf,  pMsgHead->usLen  );
			   memcpy(  pIoContext->buf,  pIoContext->buf  +  sizeof(  QY_MSG_HEAD_n  ),  pMsgHead->uiLen  );
		 }
	 }
	 
	 if  (  pSession  )  {
		 if  (  isUcFlgResp(  pMsgHead->ucFlg  )  )  pSession->usLastRespCode_i  =  pMsgHead->usCode;
		 else  pSession->usLastReqCode_i  =  pMsgHead->usCode;
	 }

	 pIoContext->ucbDataDone  =  TRUE;
	 
	 ucbDataDone  =  TRUE;		//  2011/01/24

	 //  2011/01/10
	 if  (  pSession  &&  pSession->bAdmin  )  {
		 //  pMtSock->status.netStat_admin.ui64MsgDataLenRecvd  +=  pIoContext->nTotalBytes;
		 if  (  pNetStat_admin  )  pNetStat_admin->ui64MsgDataLenRecvd  +=  pIoContext->nTotalBytes;
		 }
	 else  {
		   pPerSocketContext->status.netStat.ui64MsgDataLenRecvd  +=  pIoContext->nTotalBytes;
	 }

	 //
	 iErr  =  0;
errLabel:
	 if  (  encBuf  )  free(  encBuf  );

	 if  (  !iErr  )  {
		 if  (  pucbDataDone  )  *pucbDataDone  =  ucbDataDone;
	 }

	 if  (  iErr  )  {
		 traceLog((TCHAR*)  _T(  "qyRecvMsg_iocp failed."  )  );
	 }

	 return  iErr;
}
#endif 



#if  0
//  2012/02/25, 准备改为更通用的
 int  2026_0801_qySendMsg_iocp(  MT_SOCK_IOCP  *  pMtSock,  PER_SOCKET_CONTEXT  *  pPerSocketContext,  PER_IO_CONTEXT  *  pIoContext,  unsigned  char  ucFlg,  unsigned  short  cmdCode,  unsigned  short  usCode_org,  time_t  uiStartTime,  unsigned  int  uiTranNo,  unsigned  short  usSeqNo,  char  *  data,  unsigned  int  dataLen  )
{
	 int					iErr			=	-1;
	 unsigned		int		uiCliIndex		=	pPerSocketContext->uiCliIndex;
	 if  (  !bCliIndexValid(  pMtSock,  uiCliIndex  )  )  return  -1;
	 MT_SOCK_CLIINFO_IOCP  *  pCliInfo  =  &pMtSock->cliInfos[uiCliIndex];
	 //QY_COMM_SESSION	*	pSession		=	(  QY_COMM_SESSION  *  )pMtSock->pSessions[uiCliIndex];
	 //
	 char				*	encBuf			=	NULL;
	 unsigned  int			encLen			=	CONST_maxReqDataLen_enc_is;
	 DWORD					dwFlags			=	0;
	 DWORD					dwSendNumBytes	=	0;
	 int					iRet			=	-1;


	 if  (  pIoContext->ucbDataDone  )  return  -1;

	 pIoContext->nTotalBytes  +=  pIoContext->dwIoBytes;

	 if  (  !pIoContext->nTotalBytes  )  {	//  
		 setIoTime(  pPerSocketContext,  CONST_io_write,  TRUE  );	
		 
		 pIoContext->msgHead.usCode  =  cmdCode;		
		 pIoContext->msgHead.ucFlg  =  ucFlg;
	 
		 if  (  !data  )  dataLen  =  0;

		 if  (  dataLen  )  {		//  2004/01/02
			 //
		 }
		 pIoContext->msgHead.uiLen  =  dataLen;
		 pIoContext->msgHead.i64StartTime  =  uiStartTime;	//  2007/05/07
		 pIoContext->msgHead.uiTranNo  =  uiTranNo;			//  2007/05/06
		 pIoContext->msgHead.usSeqNo  =  usSeqNo;
		 pIoContext->usCode_org  =  usCode_org;				//  2007/05/03
	 
		 //
		 if  (  sizeof(  QY_MSG_HEAD16_n  )  +  dataLen  >  sizeof(  pIoContext->buf  )  )  {
			 traceLogA(  (char*)  "qySendMsg_iocp:  Òª·¢ËÍµÄÊý¾Ý¹ý´óÁË£¬²»ÄÜ·¢ËÍ"  );  
			 goto  errLabel;
		 }

		 //  ÏÂÃæÎª½«ÉÏÊöÊý¾Ý×ª»¯ÎªÒª·¢ËÍµÄÊý¾Ý
		 QY_MSG_HEAD16_n			tmpHead;

#if  0
		 memcpy(  &tmpHead,  &pIoContext->msgHead,  sizeof(  tmpHead  )  );
		 MACRO_htons(  tmpHead.usCode  );
		 MACRO_htonl(  tmpHead.uiLen  );
		 MACRO_htonl64(  tmpHead.i64StartTime  );
		 MACRO_htonl(  tmpHead.uiTranNo  );
		 MACRO_htons(  tmpHead.usSeqNo  );
#endif 
		 //
		 AT_MSG_HEAD16_hton(pCliInfo->i64StartTime_base,  &pIoContext->msgHead, &tmpHead);

		 //
		 memcpy(  pIoContext->buf,  &tmpHead,  sizeof(  tmpHead  )  );
		 if  (  dataLen  )  memcpy(  pIoContext->buf  +  sizeof(  tmpHead  ),  data,  dataLen  );
		 
	 }


	 if  (  pIoContext->nTotalBytes  <  pIoContext->msgHead.uiLen  +  sizeof(  QY_MSG_HEAD16_n  )  )  {
		 pIoContext->ioOperation  =  CONST_io_write;		 
		 pIoContext->wsaBuf.buf  =  pIoContext->buf  +  pIoContext->nTotalBytes;
		 pIoContext->wsaBuf.len  =  pIoContext->msgHead.uiLen  +  sizeof(  QY_MSG_HEAD16_n  )  -  pIoContext->nTotalBytes;
		 memset(  &pIoContext->overlapped,  0, sizeof(  pIoContext->overlapped  )  );
		 iRet  =  WSASend(  pMtSock->cliInfos[uiCliIndex].cliSockFd,  &pIoContext->wsaBuf,  1,  &dwSendNumBytes,  dwFlags,  &(pIoContext->overlapped),  NULL  );  
		 if  (  SOCKET_ERROR  ==  iRet  &&  (  ERROR_IO_PENDING  !=  WSAGetLastError(  )  )  )  {
			 qyDisplayLastError(  (char*)"Initial WSASend Failed"  );  goto  errLabel;
		 }
		 iErr  =  0;  goto  errLabel;
	 }
	 
	 setIoTime(  pPerSocketContext,  CONST_io_write,  FALSE  );	

	 //  if  (  isUcFlgResp(  pIoContext->msgHead.ucFlg  )  )  pSession->usLastRespCode_o  =  pIoContext->msgHead.usCode;
	 //  else  pSession->usLastReqCode_o  =  pIoContext->msgHead.usCode;

	 pIoContext->ucbDataDone  =  TRUE;
 
	 //  2011/01/10
	 if  (  pCliInfo->sessionData.bAdmin1  )  {
		 pMtSock->status.netStat_admin.ui64MsgDataLenSent  +=  pIoContext->nTotalBytes;
		 }
	 else  {
		    pPerSocketContext->status.netStat.ui64MsgDataLenSent  +=  pIoContext->nTotalBytes;
	 }

	 //
	 iErr  =  0;
	 
errLabel:

	 if  (  encBuf  )  free(  encBuf  );

	 return  iErr;

}
#endif 


//
//  2012/02/25, 准备改为更通用的
int  qySendMsg_iocp(MT_SOCK_IOCP * pMtSock, PER_SOCKET_CONTEXT * pPerSocketContext, PER_IO_CONTEXT * pIoContext, unsigned  char  ucFlg, unsigned  short  cmdCode, unsigned  short  usCode_org, time_t  uiStartTime, unsigned  int  uiTranNo, unsigned  short  usSeqNo, char* data, unsigned  int  dataLen)
{
	int					iErr = -1;
	unsigned		int		uiCliIndex = pPerSocketContext->uiCliIndex;
	if (!bCliIndexValid(pMtSock, uiCliIndex))  return  -1;
	MT_SOCK_CLIINFO_IOCP* pCliInfo = &pMtSock->cliInfos[uiCliIndex];
	//
	char* encBuf = NULL;
	unsigned  int			encLen = CONST_maxReqDataLen_enc_is;
	DWORD					dwFlags = 0;
	DWORD					dwSendNumBytes = 0;
	int						iRet = -1;
	//
	CTX_caller				caller(_T("qySendMsg_iocp"));

	//
	if (pIoContext->ucbDataDone)  return  -1;

	pIoContext->nTotalBytes += pIoContext->dwIoBytes;

	if (!pIoContext->nTotalBytes) {	//  
		setIoTime(pPerSocketContext, CONST_io_write, TRUE);

		//
		ucFlg &= ~CONST_atCommFlg_head14;

		//
		pIoContext->msgHead.usCode = cmdCode;
		pIoContext->msgHead.ucFlg = ucFlg;

		if (!data)  dataLen = 0;

		if (dataLen) {		//  2004/01/02
			//
		}
		pIoContext->msgHead.uiLen = dataLen;
		pIoContext->msgHead.i64StartTime = uiStartTime;	//  2007/05/07
		pIoContext->msgHead.uiTranNo = uiTranNo;			//  2007/05/06
		pIoContext->msgHead.usSeqNo = usSeqNo;
		pIoContext->usCode_org = usCode_org;				//  2007/05/03

		//
#ifdef  __DEBUG__
		if (uiTranNo == 9876) {
			int  ii = 0;
		}
		byte flg1 = CONST_atCommFlg_routeTalkData | CONST_atCommFlg_head14;
		int  iii = 0;
#endif 

		//  
		//QY_MSG_HEAD16_n			tmpHead;

		//
		bool  bHead14;
		bHead14 = false;
		
		int headLen;
		headLen = 22;
		if (!isUcFlgMoreData(ucFlg))  headLen -= 2;
		//
		// cmd要一個字節
		// 一個之數據長度可以存3個字節
		//  l3需要放3個字節内
		//
		if (cmdCode <= 255
			&& pIoContext->msgHead.uiLen < INT24_MAX
			)
		{
			__int64  l3 = uiStartTime - pCliInfo->i64StartTime_base2;
			if  (  l3  <=  INT24_MAX && l3  >=INT24_MIN  )  {
				bHead14 = true;
			}
		}
		//
#ifdef  __DEBUG__
		if (pMtSock->pMtSockDbgStatus->bNo_head14) {	//  爲了測試，把head14關掉.
			bHead14 = false;
		}
#endif 

		//
		if  (  bHead14  )
		{
			AT_MSG_HEAD14_n  tmpHead14_n;
			memset(&tmpHead14_n, 0, sizeof(tmpHead14_n));
			//
			if (AT_MSG_HEAD14_hton(&caller, pCliInfo->i64StartTime_base2, &pIoContext->msgHead, &tmpHead14_n, &headLen)) {
				goto  errLabel;
			}
			//
			memcpy(pIoContext->buf, &tmpHead14_n, headLen);
		}
		else {
			AT_MSG_HEAD22_n  tmpHead22_n;
			memset(&tmpHead22_n, 0, sizeof(tmpHead22_n));
			//
			if (AT_MSG_HEAD22_hton(&caller,pCliInfo->i64StartTime_base2, &pIoContext->msgHead, &tmpHead22_n, &headLen)) {
				goto  errLabel;
			}
			//
			memcpy(pIoContext->buf, &tmpHead22_n, headLen);
		}

		//
		if (headLen + dataLen > sizeof(pIoContext->buf)) {
			traceLogA((char*)"qySendMsg_iocp: failed. l802");
			goto  errLabel;
		}

		//
		if (dataLen)  memcpy(pIoContext->buf + headLen, data, dataLen);

		//
		pIoContext->headLen = headLen;

	}

	//
	if (pIoContext->nTotalBytes < pIoContext->msgHead.uiLen + pIoContext->headLen) {
		pIoContext->ioOperation = CONST_io_write;
		pIoContext->wsaBuf.buf = pIoContext->buf + pIoContext->nTotalBytes;
		pIoContext->wsaBuf.len = pIoContext->msgHead.uiLen + pIoContext->headLen - pIoContext->nTotalBytes;
		memset(&pIoContext->overlapped, 0, sizeof(pIoContext->overlapped));
		iRet = WSASend(pMtSock->cliInfos[uiCliIndex].cliSockFd, &pIoContext->wsaBuf, 1, &dwSendNumBytes, dwFlags, &(pIoContext->overlapped), NULL);
		if (SOCKET_ERROR == iRet && (ERROR_IO_PENDING != WSAGetLastError())) {
			qyDisplayLastError((char*)"Initial WSASend Failed");  
			goto  errLabel;
		}
		iErr = 0;  goto  errLabel;
	}

	setIoTime(pPerSocketContext, CONST_io_write, FALSE);

	//  if  (  isUcFlgResp(  pIoContext->msgHead.ucFlg  )  )  pSession->usLastRespCode_o  =  pIoContext->msgHead.usCode;
	//  else  pSession->usLastReqCode_o  =  pIoContext->msgHead.usCode;

	pIoContext->ucbDataDone = TRUE;

	//  2011/01/10
	if (pCliInfo->sessionData.bAdmin1) {
		pMtSock->status.netStat_admin.ui64MsgDataLenSent += pIoContext->nTotalBytes;
	}
	else {
		pPerSocketContext->status.netStat.ui64MsgDataLenSent += pIoContext->nTotalBytes;
	}

	//
	iErr = 0;

errLabel:

	if (encBuf)  free(encBuf);

	return  iErr;

}








//
#if  0
//  2012/02/25, 准备改为更通用的
 int  unused_qySendMsg_iocp(  PER_SOCKET_CONTEXT  *  pPerSocketContext,  QY_COMM_SESSION	*	pSession,  IM_NET_STAT  *  pNetStat_admin,  PER_IO_CONTEXT  *  pIoContext,  unsigned  char  ucFlg,  unsigned  short  cmdCode,  unsigned  short  usCode_org,  time_t  uiStartTime,  unsigned  int  uiTranNo,  unsigned  short  usSeqNo,  char  *  data,  unsigned  int  dataLen  )
{
	 int					iErr			=	-1;
	 unsigned		int		uiCliIndex		=	pPerSocketContext->uiCliIndex;
	 //  QY_COMM_SESSION	*	pSession		=	(  QY_COMM_SESSION  *  )pMtSock->pSessions[uiCliIndex];
	 char				*	encBuf			=	NULL;
	 unsigned  int			encLen			=	CONST_maxReqDataLen_enc_is;
	 DWORD					dwFlags			=	0;
	 DWORD					dwSendNumBytes	=	0;
	 int					iRet			=	-1;


	 if  (  pIoContext->ucbDataDone  )  return  -1;

	 pIoContext->nTotalBytes  +=  pIoContext->dwIoBytes;

	 if  (  !pIoContext->nTotalBytes  )  {	//  
		 setIoTime(  pPerSocketContext,  CONST_io_write,  TRUE  );	
		 
		 pIoContext->msgHead.usCode  =  cmdCode;		
		 pIoContext->msgHead.ucFlg  =  ucFlg;
	 
		 if  (  !data  )  dataLen  =  0;

		 if  (  dataLen  )  {		//  2004/01/02
			 if  (  pSession  &&  pSession->service.encType  ==  CONST_qyEncType_qwm  )  {
			 			 
				 if  (  !(  encBuf  =  (  char  *  )mymalloc(  encLen  )  )  )  goto  errLabel;
	
				 if  (  qnmEncData(  &pSession->commEncCtx,  data,  dataLen,  encBuf,  &encLen  )  )  {
					 traceLogA(  (char*)  "qySendReqÀïqnmEncData failed."  );  goto  errLabel;
				 }

				 //  {
				 //		 char  buf1[8192];  unsigned  int  len1  =  sizeof(  buf1  );
				 //		 qnmDecData(  &pSession->commEncCtx,  encBuf,  encLen,  buf1,  &len1  );
				 //	 }

				 data  =  encBuf;  dataLen  =  encLen;
			 }
	 
		 }
		 pIoContext->msgHead.uiLen  =  dataLen;
		 pIoContext->msgHead.i64StartTime  =  uiStartTime;	//  2007/05/07
		 pIoContext->msgHead.uiTranNo  =  uiTranNo;			//  2007/05/06
		 pIoContext->msgHead.usSeqNo  =  usSeqNo;
		 pIoContext->usCode_org  =  usCode_org;				//  2007/05/03
	 
		 if  (  sizeof(  QY_MSG_HEAD_n  )  +  dataLen  >  sizeof(  pIoContext->buf  )  )  {
			 traceLogA(  (char*)  "qySendMsg_iocp:  Òª·¢ËÍµÄÊý¾Ý¹ý´óÁË£¬²»ÄÜ·¢ËÍ"  );  goto  errLabel;
		 }

		 //  ÏÂÃæÎª½«ÉÏÊöÊý¾Ý×ª»¯ÎªÒª·¢ËÍµÄÊý¾Ý
		 QY_MSG_HEAD_n			tmpHead;

#if 0
		 memcpy(  &tmpHead,  &pIoContext->msgHead,  sizeof(  tmpHead  )  );
		 MACRO_htons(  tmpHead.usCode  );
		 MACRO_htonl(  tmpHead.uiLen  );
		 MACRO_htonl64(  tmpHead.i64StartTime  );
		 MACRO_htonl(  tmpHead.uiTranNo  );
		 MACRO_htons(  tmpHead.usSeqNo  );
#endif 
		 AT_MSG_HEAD_hton(pSession->service.i64StartTime_base,&pIoContext->msgHead, &tmpHead);


		 //
		 memcpy(  pIoContext->buf,  &tmpHead,  sizeof(  tmpHead  )  );
		 if  (  dataLen  )  memcpy(  pIoContext->buf  +  sizeof(  tmpHead  ),  data,  dataLen  );
		 
	 }


	 if  (  pIoContext->nTotalBytes  <  pIoContext->msgHead.uiLen  +  sizeof(  QY_MSG_HEAD_n  )  )  {
		 pIoContext->ioOperation  =  CONST_io_write;		 
		 pIoContext->wsaBuf.buf  =  pIoContext->buf  +  pIoContext->nTotalBytes;
		 pIoContext->wsaBuf.len  =  pIoContext->msgHead.uiLen  +  sizeof(  QY_MSG_HEAD_n  )  -  pIoContext->nTotalBytes;
		 memset(  &pIoContext->overlapped,  0, sizeof(  pIoContext->overlapped  )  );
		 iRet  =  WSASend(  pPerSocketContext->sockFd,  &pIoContext->wsaBuf,  1,  &dwSendNumBytes,  dwFlags,  &(pIoContext->overlapped),  NULL  );  
		 if  (  SOCKET_ERROR  ==  iRet  &&  (  ERROR_IO_PENDING  !=  WSAGetLastError(  )  )  )  {
			 qyDisplayLastError(  (char*)"Initial WSASend Failed"  );  goto  errLabel;
		 }
		 iErr  =  0;  goto  errLabel;
	 }
	 
	 setIoTime(  pPerSocketContext,  CONST_io_write,  FALSE  );	

	 //  if  (  isUcFlgResp(  pIoContext->msgHead.ucFlg  )  )  pSession->usLastRespCode_o  =  pIoContext->msgHead.usCode;
	 //  else  pSession->usLastReqCode_o  =  pIoContext->msgHead.usCode;

	 pIoContext->ucbDataDone  =  TRUE;
 
	 //  2011/01/10
	 if  (  pSession  &&  pSession->bAdmin  )  {
		 //  pMtSock->status.netStat_admin.ui64MsgDataLenSent  +=  pIoContext->nTotalBytes;
		 if  (  pNetStat_admin  )  pNetStat_admin->ui64MsgDataLenSent  +=  pIoContext->nTotalBytes;
		 }
	 else  {
		    pPerSocketContext->status.netStat.ui64MsgDataLenSent  +=  pIoContext->nTotalBytes;
	 }

	 //
	 iErr  =  0;
	 
errLabel:

	 if  (  encBuf  )  free(  encBuf  );

	 return  iErr;

}
#endif 






