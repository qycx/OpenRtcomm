
#include	"stdafx.h"
#include	"qyPrecomp.h"

#include	<stdlib.h>
#include	<stdio.h>
#include	<stddef.h>
#include	<windows.h>
#include	<WinSock2.h>
#include	"qyCommon.h"
#include	"qyCommCommon.h"

#include	<tchar.h>

//
//
extern  "C"  bool  isImGrp(int  uiType)
{
	bool  bRet = false;

	switch (uiType) {
	case  CONST_objType_imGrp:
		bRet = true;
		break;
	default:
		break;
	}
	return  bRet;
}


//
 extern  "C"  int  qyTellService(  unsigned  int  serviceId,  char * version,  void  *  pCommEncCtx,  char * data,  int dataLen,  QY_SOCK * pSock,  SOCK_TIMEOUT * pTo,  QY_COMM_SESSION * pSession )
{
	 int					iErr			=		-1;
	 QY_COMM_SERVICE_n		service; 
	 unsigned  int			len;
	 
	 //  traceLogA(  (char*)"qyTellService(  ) enters."  );

	 //  清空pSession->service
	 memset(  &pSession->service,  0,  sizeof(  pSession->service  )  );

	 //  重新组织service
 	 memset(  &service,  ' ',  sizeof(  service  )  );
	 service.serviceId  =  qyhtonl(  serviceId  );
	 MACRO_safeStrMemCpy(  version,  service.version,  sizeof(  service.version  )  );
	 if  (  pCommEncCtx  )  service.encType  =  qyhtonl(  (  (  QY_ENC_CTX  *  )pCommEncCtx  )->type  );
	 memcpy(  service.data,  data,  min(  dataLen,  sizeof(  service.data  )  )  );

	 len  =  offsetof(  QY_COMM_SERVICE_n,  data  )  +  min(  dataLen,  sizeof(  service.data  )  );	//  2007/04/19, 原来发送的len为sizeof(  service  ), 现在做了修改。主要为了让发送的数据能灵活控制
	 if  (  qySendReq(  pSession,  pSock,  pTo,  CONST_qyCmd_tellService,  (  char  *  )&service,  len  )  )  goto  errLabel;

	 //  将service赋入pSession中
	 service.serviceId  =  serviceId;			//
	 if  (  pCommEncCtx  )  {
		 service.encType  =  (  (  QY_ENC_CTX  *  )pCommEncCtx  )->type;	 
	 }
	 memcpy(  &pSession->service,  &service,  sizeof(  service  )  );
	 if  (  pCommEncCtx  )  {
		 memcpy(  &pSession->commEncCtx,  pCommEncCtx,  sizeof(  pSession->commEncCtx  )  );	//  2004/01/03添加对加密的支持
	 }
	 
	 iErr  =  0;

errLabel:

	 //  traceLogA(  (char*)"qyTellService(  ) leaves, %s",  iErr  ?  "失败"  :  "成功"  );

	 return  iErr;
	 
}

  extern  "C"  unsigned  int  getNextSessionId(  )
{
	 unsigned  int				uiSessionId					=	0;
	 static  unsigned  int		suiIdSeed					=	0;
	 HANDLE						hMutex						=	NULL;
	 TCHAR					*	mutexName					=	(TCHAR*)_T(  "qmdSessMutex"  );
	 DWORD						dwRet						=	0;

	 hMutex = CreateMutex(  NULL,  FALSE,  mutexName  );
	 if  (  !hMutex  )  goto  errLabel;
	 dwRet  =  WaitForSingleObject(  hMutex,  INFINITE  );
	 if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;

	 suiIdSeed  ++  ;
	 uiSessionId  =  suiIdSeed;

errLabel:

	 if  (  hMutex  )  {	//  释放Mutex
		 ReleaseMutex(  hMutex  );  CloseHandle(  hMutex  );
	 }

	 return  uiSessionId;
}


 extern  "C"  int  qyAcceptService(  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  char  *   startTime,  QY_COMM_SESSION  *  pSession  )
{
	 int					iErr  =  -1;
	 QY_COMM_REQ			tmpReq;
	 
	 //  traceLogA(  (char*)"qyAcceptService(  ) enters."  );

	 if  (  qyRecvReq(  pSession,  pSock,  pTo,  &tmpReq,  (  char  *  )&tmpReq.u.service,  sizeof(  tmpReq.u.service  )  )  )  goto  errLabel;
	 if  (  tmpReq.head.usCode  !=  CONST_qyCmd_tellService  )  goto  errLabel;
	 tmpReq.u.service.serviceId  =  qyntohl(  tmpReq.u.service.serviceId  );
	 tmpReq.u.service.encType  =  qyntohl(  tmpReq.u.service.encType  );
	 memcpy(  &pSession->service,  &tmpReq.u.service,  sizeof(  tmpReq.u.service  )  );

	 //  getCurTime(  pSession->startTime  );
	 safeStrnCpy(  startTime,  pSession->startTime,  mycountof(  pSession->startTime  )  );
	 getRemoteIpBySocket(  pSock->sockFd,  pSession->clientIp  );	//  2007/04/01
 
	 pSession->uiSessionId  =  getNextSessionId(  );					//  2007/04/20

	 iErr  =  0;

errLabel:

	 //  traceLogA(  (char*)"qyAcceptService(  ) leaves."  );
	 
	 return  iErr;
	 
}


 extern  "C"  int  qyRecvReq(  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  QY_COMM_REQ  *  pReq,  char  *  dataBuf,  unsigned  int  bufSize  )
{
	 int				iErr		=	-1;
	 char			*	encBuf		=	NULL;		  
	 unsigned  int		encLen		=	CONST_maxReqDataLen_enc_netMc;

	 if  (  qyRecvX(  pSock, ( char * )pReq,  sizeof(  QY_COMM_HEAD  ), pTo->iRead  )  )  goto  errLabel;
	 pReq->head.len  =  qyntohl(  pReq->head.len  );

	 //
#ifdef  __DEBUG__
	 if  (  pReq->head.len  ==  4624  )  {
		 int  ii  =  0;
	 }
#endif

	 //
	 if  (  !(  encBuf  =  (  char  *  )malloc(  encLen  )  )  )  {
		 goto  errLabel;
	 }

	 if  (  pReq->head.len  >  encLen  )  {  iErr  =  -2;  goto  errLabel;  }
	 if  (  pReq->head.len  )  {
	 	 if  (  qyRecvX(  pSock,  encBuf,  pReq->head.len,  pTo->iRead  )  )  goto  errLabel;

		 if  (  pSession->service.encType  ==  CONST_qyEncType_qwm  )  {
			 if  (  qnmDecData(  &pSession->commEncCtx,  encBuf,  pReq->head.len,  dataBuf,  &bufSize  )  )  {
				 traceLogA(  (char*)"qyRecvReq里qnmDecData failed"  );  goto  errLabel;
			 }
			 pReq->head.len  =  bufSize;
			 }
		 else  if (pSession->pf_dec) {
			 if (pSession->pf_dec(pSession, pSession->pmyHgSessionEnc, encBuf, pReq->head.len, dataBuf, &bufSize)) {
				 goto  errLabel;
			 }
			 pReq->head.len = bufSize;
		 }
		 else  if  (  pReq->head.len  >  bufSize  )  {  iErr  =  -2;  goto  errLabel;  }
		 else  memcpy(  dataBuf,  encBuf,  pReq->head.len  );
	 }

	 pReq->head.usCode  =  qyntohs(  pReq->head.usCode  );
	 pSession->usLastReqCode_i  =  pReq->head.usCode;

	 iErr	=		0;

errLabel:
	 
	 if  (  encBuf  )  free(  encBuf  );

	 return  iErr;

}

 // 接收响应包
 extern  "C"  int  qyRecvResp(  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  QY_COMM_RESP  *  pResp,  char  *  dataBuf,  unsigned  int  bufSize )
{
	 int				iErr		=	-1;
	 char			*	encBuf		=	NULL;
	 unsigned  int		encLen		=	CONST_maxReqDataLen_enc_netMc;		  

	 if  (  qyRecvX(  pSock, ( char * )pResp,  sizeof(  QY_COMM_HEAD  ), pTo->iRead  )  )  goto  errLabel;
	 pResp->head.len  =  qyntohl(  pResp->head.len  );

	 if  (  !(  encBuf  =  (  char  *  )malloc(  encLen  )  )  )  goto  errLabel;

	 if  (  pResp->head.len  >  encLen  )  goto  errLabel;
	 if  (  pResp->head.len  )  {
	 	 if  (  qyRecvX(  pSock,  encBuf,  pResp->head.len,  pTo->iRead  )  )  goto  errLabel;

		 if  (  pSession->service.encType  ==  CONST_qyEncType_qwm  )  {
			 if  (  qnmDecData(  &pSession->commEncCtx,  encBuf,  pResp->head.len,  dataBuf,  &bufSize  )  )  {
				 traceLogA(  (char*)"qyRecvReq里qnmDecData failed"  );  
				 goto  errLabel;
			 }
			 pResp->head.len  =  bufSize;
			 }
		 else  if  (  pResp->head.len  >  bufSize  )  {  iErr  =  -2;  goto  errLabel;  }
		 else  memcpy(  dataBuf,  encBuf,  pResp->head.len  );
	 }


	 pResp->head.usCode  =  qyntohs(  pResp->head.usCode  );
	 pSession->usLastRespCode_i  =  pResp->head.usCode;

	 iErr	=		0;

errLabel:

	 if  (  encBuf  )  free(  encBuf  );

	 return  iErr;

}

 

 

 extern  "C"  int  tmpqySendReq(  QY_COMM_SESSION  * pSession, QY_SOCK * pSock, SOCK_TIMEOUT * pTo, BOOL  bResp,  unsigned  short  cmdCode,  char  *  data,  unsigned  int  dataLen  )
{
	 int					iErr		=	-1;
	 QY_COMM_HEAD			tmpHead;
	 char				*	encBuf		=	NULL;
	 unsigned  int			encLen		=	CONST_maxReqDataLen_enc_netMc;
	 
	 memset(  &tmpHead,  0,  sizeof(  tmpHead  )  );
	 tmpHead.usCode  =  qyhtons(  cmdCode  );
	 if  (  !data  )  dataLen  =  0;

	 if  (  dataLen  )  {		//  2004/01/02里加入了加密的处理
		 if  (  pSession->service.encType  ==  CONST_qyEncType_qwm  )  {
			 
			 if  (  !(  encBuf  =  (  char  *  )malloc(  encLen  )  )  )  goto  errLabel;

			 if  (  qnmEncData(  &pSession->commEncCtx,  data,  dataLen,  encBuf,  &encLen  )  )  {
				 traceLogA(  (char*)"qySendReq里qnmEncData failed."  );  goto  errLabel;
			 }

			 //  {
			 //		 char  buf1[8192];  unsigned  int  len1  =  sizeof(  buf1  );
			 //		 qnmDecData(  &pSession->commEncCtx,  encBuf,  encLen,  buf1,  &len1  );
			 //	 }


			 data  =  encBuf;  dataLen  =  encLen;
		 }
		 else if (pSession->pf_enc) {

			 if (!(encBuf = (char*)malloc(encLen)))  goto  errLabel;

			 if (pSession->pf_enc(pSession, pSession->pmyHgSessionEnc, data, dataLen, encBuf, &encLen)) {
				 goto  errLabel;
			 }

			 //
			 data = encBuf;  dataLen = encLen;

		 }


	 }

	 tmpHead.len  =  qyhtonl(  dataLen  );
	 if  (  qySend(  pSock,  (  char  *  )&tmpHead,  sizeof(  tmpHead  ),  pTo->iWrite  )  )  goto  errLabel;
	 if  (  dataLen  )  {		
		 if  (  qySend(  pSock,  data,  dataLen,  pTo->iWrite  )  )  goto  errLabel;
	 }

	 //  2007/04/25
	 if  (  !bResp  )  pSession->usLastReqCode_o  =  cmdCode;
	 else  pSession->usLastRespCode_o  =  cmdCode;

	 iErr  =  0;
	 
errLabel:

	 if  (  encBuf  )  free(  encBuf  );

	 return  iErr;

}

  extern  "C"  int  qySendReq(  QY_COMM_SESSION  * pSession, QY_SOCK * pSock, SOCK_TIMEOUT * pTo, unsigned  short  cmdCode,  char  *  data,  unsigned  int  dataLen  )
{
	  return  tmpqySendReq(  pSession,  pSock,  pTo,  FALSE,  cmdCode,  data,  dataLen  );
}


  extern  "C"  int  qySendResp(  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT * pTo,  unsigned  short  respCode,  char  *  data,  unsigned  int  dataLen  )
{
	 return  tmpqySendReq(  pSession,  pSock,  pTo,  TRUE,  respCode,  data,  dataLen  );
	 
}

 
 void  showCommHead(  QY_COMM_HEAD * pHead  )
{
 	 	 
	 traceLogA(  (char*)"cmd is [%d],  len is %d",  pHead->usCode,  pHead->len  );

	 return;

}

 void  showReq(  QY_COMM_REQ * pReq  )
{

	 traceLogA(  (char*)"cmd is [%d],  len is %d",  pReq->head.usCode,  pReq->head.len  );

	 return;
	 
}

 void  showResp(  QY_COMM_RESP * pResp  )
{
	 traceLogA(  (char*)"respCode is [%d],  len is %d",  pResp->head.usCode,  pResp->head.len  );

	 return;
}


 void  debugSend(  QY_SOCK * pSock, SOCK_TIMEOUT * pTo  )
{
	 static  int  i  =  0;
	 char	buf[256];

	 for  (  int  j  =  0;  j  <  3; j  ++  )  {

	 	 _snprintf(  buf,  sizeof(  buf  ),  "%d time sent.",  i  );
	 	 if (  qySend(  pSock,  buf,  sizeof(  buf  ),  pTo->iWrite  )  )
			 traceLogA(  (char*)"debugSend(  ) failed."  );
		 else
			 traceLogA(  (char*)"[%s] send.",  buf  );

		 i ++;

	 }

	 return;

}
 
  void  debugRecv(  QY_SOCK * pSock, SOCK_TIMEOUT * pTo  )
{
	 int	len ;
	 char	buf[256];

	 for  (  int  i = 0;  i  <  3;  i  ++  )  {
	 
		 len  =  sizeof(  buf  );
	 	 if (  qyRecv(  pSock,  buf,  &len,  pTo->iWrite  )  )  {
			 traceLogA(  (char*)"debugRecv(  ) failed."  );
			 }
	 	 else
			 traceLogA( (char*)"%d bytes [%s] recved.", len, buf  );

	 }
	 
	 return;

}






