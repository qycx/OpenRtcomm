

#ifndef __QYCOMMFUNC_H__
#define __QYCOMMFUNC_H__	/* { */

#ifdef  __cplusplus
  extern  "C"  {
#endif


//  
//  #define		CONST_maxReqDataLen_enc				8192			//  2004/01/02
//  #define		CONST_maxReqDataLen_enc				16384			//  2004/07/26, 
#define		CONST_maxReqDataLen_enc_netMc			16384			//  2004/07/26, 
#define		CONST_maxReqDataLen_enc_is				1024  *  1024	//  2008/03/20, 
//
#define		CONST_qnmReqBufSize_netMc				32768			//  netMc
//
																



unsigned  int  getNextSessionId(  );

//
bool  isImGrp(int  uiType);


//  extern  "C"  int  qyTellService(  unsigned  int  serviceId,  char  *  version,  char  *  data,  int  dataLen,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  QY_COMM_SESSION  *  pSession  );
int  qyTellService(  unsigned  int  serviceId,  char * version,  void  *  pCommEncCtx,  char * data,  int dataLen,  QY_SOCK * pSock,  SOCK_TIMEOUT * pTo,  QY_COMM_SESSION * pSession );
int  qyAcceptService(  QY_SOCK  * pSock,  SOCK_TIMEOUT  *  pTo,  char  *  startTime,  QY_COMM_SESSION  *  pSession  );
int  qyRecvReq(  QY_COMM_SESSION  * pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  QY_COMM_REQ  *  pReq,  char  *  dataBuf,  unsigned  int  bufSize  );
int  qyRecvResp(  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  QY_COMM_RESP * pResp,  char  *  dataBuf,  unsigned  int  bufSize  );
int  qySendReq(  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  unsigned  short  cmdCode,  char  *  data,  unsigned  int  dataLen  );
int  qySendResp(  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  unsigned  short  respCode,  char  *  data,  unsigned  int  dataLen  );

#ifdef  __cplusplus
  }
#endif




void  showCommHead(  QY_COMM_HEAD * head  );
void  showResp(  QY_COMM_RESP * pResp  );
void  showReq(  QY_COMM_REQ * pReq  );

void  debugRecv(  QY_SOCK * pSock, SOCK_TIMEOUT * pTo  );
void  debugSend(  QY_SOCK * pSock, SOCK_TIMEOUT * pTo  );


#endif /* } */

