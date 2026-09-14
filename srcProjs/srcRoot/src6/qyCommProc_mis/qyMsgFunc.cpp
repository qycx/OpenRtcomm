
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<stdlib.h>
#include	<stdio.h>
#include	<stddef.h>
#include	<winsock2.h>
#include	<windows.h>
#include	<Wincrypt.h>
#include	<tchar.h>

#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyMsgFunc.h"
#include	"qyCommProc.h"
#include	"qyWmComm.h"
#include	"qnmCommProc.h"
#include	"qysyncCommProc.h"

#include	<tchar.h>
#include	"qmCrypt.h"
#ifndef  __WINCE__
	#include	<errno.h>
#else
	#include	"myerrno.h"

#ifndef  __TEST__
 int  tmp_errno  =  0;
 int * __cdecl _errno(void)
{
	return  &tmp_errno;
}
#endif

#endif

 //
#include <anCommProc.h>



// Use select() to determine when
// data is waiting to be read
//  返回值：>  0  为有数据
//			== 0  为超时
//			<  0  为失败
 extern  "C"  int  qyWaitForRead(  int  fd,  int  timeout  )
{
	 while  (  true  )  {
    	    fd_set rfds;
   			struct timeval tv;
       
			tv.tv_sec = timeout / 1000;
    		tv.tv_usec = (timeout % 1000) * 1000;
    
			FD_ZERO(&rfds);
			FD_SET(fd, &rfds);
			int n = select(fd+1, &rfds, 0, 0, &tv);
			if  (  n  !=  -1  ||  errno  !=  EINTR  )  return  n;
			traceLogA(  (char*)  "select returned EINTR"  );
	 }
}

 extern  "C"  int  qyWaitForWrite(  int  fd,  int  timeout  )
{
	 while  (  true  )  {
    	    fd_set wfds;
   			struct timeval tv;
       
			tv.tv_sec = timeout / 1000;
    		tv.tv_usec = (timeout % 1000) * 1000;
    
			FD_ZERO(&wfds);
			FD_SET(fd, &wfds);
			int n = select(fd+1, 0,  &wfds, 0, &tv);
			if  (  n  !=  -1  ||  errno  !=  EINTR  )  return  n;
			traceLogA(  (char*)  "select returned EINTR"  );
	 }
}


#if  0  //  2010/04/24
 extern  "C"  int  iiqyRecvMsg(  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  QY_MSG_HEAD * pMsgHead,  char  *  dataBuf,  unsigned  int  bufSize  )
{
	 int				iErr		=	-1;
	 char			*	encBuf		=	NULL;
	 unsigned  int		encLen		=	CONST_maxReqDataLen_enc_is;		  

	 if  (  qyRecvX(  pSock, ( char * )pMsgHead,  sizeof(  QY_MSG_HEAD  ), pTo->iRead  )  )  goto  errLabel;
	 MACRO_ntohs(  pMsgHead->usLen  );
	 MACRO_ntohs(  pMsgHead->usCode  );
	 MACRO_ntohl64(  pMsgHead->i64StartTime  );	//  2007/05/07
	 MACRO_ntohl(  pMsgHead->uiTranNo  );
	 MACRO_ntohl(  pMsgHead->uiSeqNo  );
	 
	 if  (  !(  encBuf  =  (  char  *  )mymalloc(  encLen  )  )  )  goto  errLabel;

	 if  (  pMsgHead->usLen  >  encLen  )  {
		 traceLogA(  (char*)  "qyRecvMsg err, dataLen [%d] > encLen [%d]",  pMsgHead->usLen,  encLen  );
		 goto  errLabel;
	 }
	 if  (  pMsgHead->usLen  )  {
	 	 if  (  qyRecvX(  pSock,  encBuf,  pMsgHead->usLen,  pTo->iRead  )  )  goto  errLabel;

		 if  (  pSession->service.encType  ==  CONST_qyEncType_qwm  )  {
			 if  (  qnmDecData(  &pSession->commEncCtx,  encBuf,  pMsgHead->usLen,  dataBuf,  &bufSize  )  )  {
				 traceLogA(  (char*)  "qyRecvReq里qnmDecData failed"  );  goto  errLabel;
			 }
			 pMsgHead->usLen  =  bufSize;
			 }
		 else  if  (  pMsgHead->usLen  >  bufSize  )  {  
			       traceLogA(  (char*)  "qyRecvMsg err, dataLen [%d] > bufSize [%d]",  pMsgHead->usLen,  bufSize  );
				   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  _T(  ""  ),  _T(  ""  ),  _T(  "qyRecvMsg err. "  ),  _T(  "收到数据过大, dataLen [%d] "  ),  pMsgHead->usLen  );
				   iErr  =  -2;  goto  errLabel;  
				   }
		 else  
			 memcpy(  dataBuf,  encBuf,  pMsgHead->usLen  );
	 }

	 //
	 if  (  isUcFlgResp(  pMsgHead->ucFlg  )  )  pSession->usLastRespCode_i  =  pMsgHead->usCode;
	 else  pSession->usLastReqCode_i  =  pMsgHead->usCode;

	 iErr	=		0;

errLabel:

	 if  (  encBuf  )  free(  encBuf  );

	 return  iErr;

}
#endif
 

 //
  extern  "C"  int  qyRecvMsg(  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  QY_MSG_HEAD_h * pMsgHead,  char  *  dataBuf,  unsigned  int  bufSize  )
{
	 int				iErr		=	-1;
	 char			*	encBuf		=	NULL;
	 unsigned  int		encLen		=	CONST_maxReqDataLen_enc_is;	
	 //
	 CTX_caller			caller(_T("qyRecvMsg"));

	 //
	 byte  ucFlg;  ucFlg = 0;

	 if (qyRecvX(pSock, (char*)&ucFlg, sizeof(ucFlg), pTo->iRead))  goto  errLabel;

	 //
	 int  headLen;  headLen = 0;
	 if (isUcFlgHead14(ucFlg)) {
		 headLen = 14;
	 }
	 else {
		 headLen = 22;
	 }
	 if (!isUcFlgMoreData(ucFlg)) {
		 headLen -= 2;
	 }

	 int flgLen; flgLen = 1;

	 //
	 if (isUcFlgHead14(ucFlg)) {
		 AT_MSG_HEAD14_n  msgHead14_n;

		 memset(&msgHead14_n, 0, sizeof(msgHead14_n));
		 memcpy(msgHead14_n.ucFlg_buf, &ucFlg, sizeof(ucFlg));
		 //
		 if (qyRecvX(pSock, ((char*)&msgHead14_n) + flgLen, headLen - flgLen, pTo->iRead))  goto  errLabel;
		 //
		 AT_MSG_HEAD14_ntoh(&caller,pSession->service.i64StartTime_base, &msgHead14_n, pMsgHead);

	 }
	 else {

		 AT_MSG_HEAD22_n  msgHead_n;
		 memset(&msgHead_n, 0, sizeof(msgHead_n));
		 memcpy(msgHead_n.ucFlg_buf, &ucFlg, sizeof(ucFlg));

		 //
		 if (qyRecvX(pSock, ((char*)&msgHead_n) + flgLen, headLen - flgLen, pTo->iRead))  goto  errLabel;
		 //
		 AT_MSG_HEAD22_ntoh(&caller,pSession->service.i64StartTime_base, &msgHead_n, pMsgHead);
	 }
	 //
	 pMsgHead->ucFlg &= ~CONST_atCommFlg_head14;

	 //
	 if  (  pMsgHead->uiLen  )  {

		 if  (  pSession->service.encType  ==  CONST_qyEncType_qwm  )  {

			 if  (  !(  encBuf  =  (  char  *  )mymalloc(  encLen  )  )  )  goto  errLabel;

			 if  (  pMsgHead->uiLen  >  encLen  )  {
				 traceLogA(  (char*)  "qyRecvMsg err, dataLen [%d] > encLen [%d]",  pMsgHead->uiLen,  encLen  );
				 goto  errLabel;
			 }

			 if  (  qyRecvX(  pSock,  encBuf,  pMsgHead->uiLen,  pTo->iRead  )  )  goto  errLabel;

			 if  (  qnmDecData(  &pSession->commEncCtx,  encBuf,  pMsgHead->uiLen,  dataBuf,  &bufSize  )  )  {
				 traceLogA(  (char*)  "qyRecvReq里qnmDecData failed"  );  
				 goto  errLabel;
			 }
			 pMsgHead->uiLen  =  bufSize;

			 }  
		 else  {

			   if  (  pMsgHead->uiLen  >  bufSize  )  {  
			       traceLogA(  (char*)  "qyRecvMsg err, dataLen [%d] > bufSize [%d]",  pMsgHead->uiLen,  bufSize  );
				   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)"",  _T(  "IsClient"  ),  _T(  ""  ),  _T(  ""  ),  _T(  "qyRecvMsg err. "  ),  _T(  "收到数据过大, dataLen [%d] "  ),  pMsgHead->uiLen  );
				   iErr  =  -2;  goto  errLabel;  		
			   }

			   if (qyRecvX(pSock, dataBuf, pMsgHead->uiLen, pTo->iRead)) {
				   goto  errLabel;
			   }
		 }
	 }

	 //
	 if  (  isUcFlgResp(  pMsgHead->ucFlg  )  )  pSession->usLastRespCode_i  =  pMsgHead->usCode;
	 else  pSession->usLastReqCode_i  =  pMsgHead->usCode;

	 iErr	=		0;

errLabel:

	 if  (  encBuf  )  free(  encBuf  );

	 return  iErr;

}

  //
  //bool  g_bUse_head16 = false;

  //
  extern  "C"  int  qySendMsg(QY_COMM_SESSION* pSession, QY_SOCK* pSock, SOCK_TIMEOUT* pTo, unsigned  char  ucFlg, unsigned  short  cmdCode, time_t  uiStartTime, unsigned  int  uiTranNo, unsigned  short  usSeqNo, char* data, unsigned  int  dataLen)
  {
	  int					iErr = -1;
	  QY_MSG_HEAD_h			tmpHead;
	  char* encBuf = NULL;
	  unsigned  int			encLen = CONST_maxReqDataLen_enc_is;
	  //
	  CTX_caller	caller(_T("qySendMsg"));

	  //
	  ucFlg &= ~CONST_atCommFlg_head14;

	  //
	  memset(&tmpHead, 0, sizeof(tmpHead));
	  tmpHead.usCode = cmdCode;// qyhtons(cmdCode);
	  tmpHead.ucFlg = ucFlg;

	  if (!data)  dataLen = 0;

	  if (dataLen) {		//  2004/01/02里加入了加密的处理
		  if (pSession->service.encType == CONST_qyEncType_qwm) {

			  if (!(encBuf = (char*)mymalloc(encLen)))  goto  errLabel;

			  if (qnmEncData(&pSession->commEncCtx, data, dataLen, encBuf, &encLen)) {
				  traceLogA((char*)"qySendReq里qnmEncData failed.");
				  goto  errLabel;
			  }

			  //  {
			  //		 char  buf1[8192];  unsigned  int  len1  =  sizeof(  buf1  );
			  //		 qnmDecData(  &pSession->commEncCtx,  encBuf,  encLen,  buf1,  &len1  );
			  //	 }


			  data = encBuf;  dataLen = encLen;
		  }
	  }

	  tmpHead.uiLen = (unsigned  int)dataLen;
	  if (tmpHead.uiLen != dataLen) {
		  traceLogA((char*)"dataLen");
		  goto  errLabel;		//  这里要防止dataLen是个过大的数
	  }
	  //MACRO_htonl(  tmpHead.uiLen  );
	  tmpHead.i64StartTime = uiStartTime;// qyhtonl64(uiStartTime);	//  2007/05/07
	  tmpHead.uiTranNo = uiTranNo;// qyhtonl(uiTranNo);
	  tmpHead.usSeqNo = usSeqNo;// qyhtons(usSeqNo);			//  2007/05/02
	  //
	  int nBytes;  nBytes = 0;
	  //
#if  0
	  if (g_bUse_head16) {
		  AT_MSG_HEAD16_n  tmpHead_n;
		  AT_MSG_HEAD16_hton(&caller,pSession->service.i64StartTime_base, &tmpHead, &tmpHead_n);
		  //
		  if (qySend(pSock, (char*)&tmpHead_n, sizeof(tmpHead_n), pTo->iWrite)) {
			  traceLogA((char*)"qySend msgHead failed");  goto  errLabel;
		  }
	  }
	  else
#endif 
	  {
		  //
		  bool  bHead14;  bHead14 = false;
		   //
		  if (tmpHead.usCode < 255
			  && tmpHead.uiLen < INT24_MAX)
		  {
			  __int64  l3 = uiStartTime - pSession->service.i64StartTime_base;
			  if (l3 <= INT24_MAX && l3 >= INT24_MIN) {
				  bHead14 = true;
			  }
		   }
		  //
		  if (bHead14) {
			  AT_MSG_HEAD14_n tmpHead14_n;
			  memset(&tmpHead14_n, 0, sizeof(tmpHead14_n));
			  if (AT_MSG_HEAD14_hton(&caller, pSession->service.i64StartTime_base, &tmpHead, &tmpHead14_n, &nBytes)) {
				  goto  errLabel;
			  }
			  //
			  if (qySend(pSock, (char*)&tmpHead14_n, nBytes, pTo->iWrite)) {
				  traceLogA((char*)"qySend msgHead failed");
				  goto  errLabel;
			  }
		  }
		  else {
			  AT_MSG_HEAD22_n tmpHead22_n;
			  memset(&tmpHead22_n, 0, sizeof(tmpHead22_n));
			  if (AT_MSG_HEAD22_hton(&caller, pSession->service.i64StartTime_base, &tmpHead, &tmpHead22_n, &nBytes)) {
				  goto  errLabel;
			  }
			  //
			  if (qySend(pSock, (char*)&tmpHead22_n, nBytes, pTo->iWrite)) {
				  traceLogA((char*)"qySend msgHead failed");
				  goto  errLabel;
			  }
		  }
		   //		    
	  }
	 //
	 if (0) {
		 TCHAR  tBuf[128];
		 _sntprintf(tBuf, mycountof(tBuf), _T("qySendMsg: dataLen %d"), dataLen);
		 showInfo_open0(0, 0, tBuf);
	 }
	 //
	 if  (  dataLen  )  {	
		 if  (  qySend(  pSock,  data,  dataLen,  pTo->iWrite  )  )  {
			 qyDisplayLastError(  (char*)"qySend data failed"  );  
			 goto  errLabel;
		 }
	 }
 
	 iErr  =  0;
	 
errLabel:

	 if  (  encBuf  )  free(  encBuf  );

	 return  iErr;

}


//
#if  0
int		myM_ton_l64(__int64 l64,char  *  ptr, int len)  
{  
	__int64 n_l64;  
	n_l64  =  qyhtonl64(l64);  
	memcpy(  ptr,  &n_l64, 8  );  
	len  =  8;  
	ptr  +=  len;  
	//
	return  0;
}
#endif 



 //  2008/06/09, usCmd固定使用CONST_qyCmd_tellService。
 //  extern  "C"  int  qyTellService_msg(  unsigned  int  serviceId,  char * version,  unsigned  short  usCmd,  void  *  pCommEncCtx,  char * data,  int dataLen,  QY_SOCK * pSock,  SOCK_TIMEOUT * pTo,  QY_COMM_SESSION * pSession )
 extern  "C"  int  qyTellService_msg(  unsigned  int  serviceId,  char * version,  void  *  pCommEncCtx,  __int64  i64StartTime_base,  unsigned  short  usCmd,  time_t  tStartTime,  unsigned  int  uiTranNo,  char * data,  int dataLen,  QY_SOCK * pSock,  SOCK_TIMEOUT * pTo,  QY_COMM_SESSION * pSession )
{
	 int					iErr			=		-1;
	 QY_COMM_SERVICE_n		service; 
	 int					len;
	 //
	 char* encBuf = NULL;
	 unsigned  int			encLen = CONST_maxReqDataLen_enc_is;

	 //  unsigned  int			uiStartTime		=		0;
	 //  unsigned  int			uiTranNo		=		0;		//
#ifdef  __DEBUG__		
#endif
	 
	 //  traceLogA(  (char*)  "qyTellService(  ) enters."  );

	 if  (  !data  ||  dataLen  <=  0  )  return  -1;

	 //  清空pSession->service
	 memset(  &pSession->service,  0,  sizeof(  pSession->service  )  );

	 //  重新组织service
 	 memset(  &service,  ' ',  sizeof(  service  )  );
	 service.serviceId  =  serviceId;
	 MACRO_safeStrMemCpy(  version,  service.version,  sizeof(  service.version  )  );
	 if  (  pCommEncCtx  )  service.encType  =  (  (  QY_ENC_CTX  *  )pCommEncCtx  )->type;
	 else  service.encType  =  0;	 

	 //
	 switch  (  service.encType  )  {
		     case  CONST_qyEncType_rsa:  {	//  
				   ENC_CTX_session	*	pEncCtx  =  (  ENC_CTX_session  *  )pCommEncCtx;
	
				   //  这里应该用hPublicKey加密。
				   if  (  !pEncCtx  ||  !pEncCtx->key_rsa.hKey  )  goto  errLabel;
				   DWORD	dwBlockLen  =  pEncCtx->key_rsa.dwBlockLen_encrypt;
				   int		nIn  =  0;
				   int		nOut  =  0;
				   int		bufLen  =  0;

				   if  (  !dwBlockLen  )  goto  errLabel;

				   for  (  nIn  =  0,  nOut  =  0;  nIn  <  (  int  )dataLen  &&  nOut  <=  sizeof(  service.data  );  )  {
					    len  =  min(  dataLen  -  nIn,  (  int  )dwBlockLen  );

						memcpy(  service.data  +  nOut,  data  +  nIn,  len  );
						bufLen  =  len;

						if  (  !CryptEncrypt(  pEncCtx->key_rsa.hKey,  0,  (  len  >=  (  int  )(  dataLen  -  nIn  )  ),  0,  (  BYTE  *  )(  service.data  +  nOut  ),  (  DWORD  *  )&bufLen,  sizeof(  service.data  )  -  nOut  )  )  {
							qyDisplayLastError(  (char*)"qyTellService_msg CryptEncrypt failed."  );
							goto  errLabel;
						}

						nIn  +=  len;
						nOut  +=  bufLen;				   		 
				   }

				   dataLen  =  nOut;
				   }
				   break;
				   //
			 case  CONST_qyEncType_qwm:
				 if (dataLen) {		//  2004/01/02里加入了加密的处理
					 //if (pSession->service.encType == CONST_qyEncType_qwm)
					 {

						 if (!(encBuf = (char*)mymalloc(encLen)))  goto  errLabel;

						 if (qnmEncData(pCommEncCtx, data, dataLen, encBuf, &encLen)) {
							 traceLogA((char*)"qySendReq里qnmEncData failed.");
							 goto  errLabel;
						 }

#ifdef  __DEBUG__
						 if (0)
						 {
#if  0
							 ENC_CTX_session  commEncCtx;

							 QY_ENC_CTX  encCtx;
							 memset(&encCtx, 0, sizeof(encCtx));
							 if (initQnmEnc(&encCtx, 0, 0, &commEncCtx)) {
								 goto  errLabel;
							 }
							 commEncCtx.ucbEncInited = TRUE;

							 char  buf1[8192];  unsigned  int  len1 = sizeof(buf1);
							 int  tmpiRet;
							 tmpiRet = qnmDecData(&commEncCtx, encBuf, encLen, buf1, &len1);
							 //tmpiRet  =  qnmDecData(&pSession->commEncCtx, encBuf, encLen, buf1, &len1);
							 //
							 int  ii = 0;

#endif 
						 }

#endif 


						 data = encBuf;  dataLen = encLen;
						 //
						 memcpy(service.data, data, dataLen);
					 }
				 }
				 break;

			 default:
				 	 dataLen  =  min(  dataLen,  sizeof(  service.data  )  );
					 memcpy(  service.data,  data,  dataLen  );
					 break;
	 }

	 //
	 MACRO_htonl(  service.serviceId  );
	 MACRO_htonl(  service.encType  );
	 
	 //
	 service.ucCommServiceType = 0;
	 
	 // 
	 char* tmp_p;
	 int  tmpLen;  tmpLen = 0;
	 tmp_p = service.i64StartTime_base_buf;
	 M_ton_l64(i64StartTime_base, tmp_p, tmpLen);
	 
	 //
#if  0
	 __int64  l64;
	 memcpy(&l64, service.i64StartTime_base_buf, 8);
	 __int64  l64_h;  l64_h = qyntohl64(l64);
#endif 

	 
	 //  将service赋入pSession中
	 pSession->service.serviceId = serviceId;			//  
	 MACRO_safeStrMemCpy(version, pSession->service.version, sizeof(pSession->service.version));
	 //
	 //pSession->service.i64StartTime_base = i64StartTime_base;
	 memcpy(pSession->service.data, service.data, dataLen);
	 pSession->service_dataLen = dataLen;
	 //
	 if (pCommEncCtx)  memcpy(&pSession->commEncCtx, pCommEncCtx, sizeof(pSession->commEncCtx));	//  2004/01/03添加对加密的支持



	 //
	 int  ii;
	 ii  = offsetof(QY_COMM_SERVICE_n, data);
	 //
	 len  =  offsetof(  QY_COMM_SERVICE_n,  data  )  +  dataLen;		//  2007/04/19, 原来发送的len为sizeof(  service  ), 现在做了修改。主要为了让发送的数据能灵活控制
	 if  (  qySendMsg(  pSession,  pSock,  pTo,  0,  usCmd,  tStartTime,  uiTranNo,  0,  (  char  *  )&service,  len  )  )  goto  errLabel;

	 //
	 pSession->service.i64StartTime_base = i64StartTime_base;
	 //
	 if (pCommEncCtx)  pSession->service.encType = ((QY_ENC_CTX*)pCommEncCtx)->type;
	 

	 //
	 iErr  =  0;

errLabel:

	 //
	 MACRO_safeFree(encBuf);

	 //  traceLogA(  (char*)  "qyTellService(  ) leaves, %s",  iErr  ?  "失败"  :  "成功"  );

	 //
	 return  iErr;	 
}


//
 extern  "C"  void  qnmCloseSession_msg(  CTX_caller  *  pCtxCaller, QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  LPCTSTR  hint  )
{
	 //QY_MSG_HEAD			tmpResp;

	 //
	 TCHAR  tWho[128]  =  _T("");
	 if (pCtxCaller) {
		 safeTcsnCpy(pCtxCaller->m_var.tWho, tWho, mycountof(tWho));
	 }
	 if (!hint)  hint = _T("");

	 //
#ifdef  __DEBUG__
	 traceLog((TCHAR*)_T("%s: qnmCloseSession_msg enters %s"), tWho, hint);
#endif 

	 //
	 if  (  bQySockOpen(  pSock  )  )  {
		 if  (  isRcOk(  pSession->usLastRespCode_i  )  ||  pSession->usLastRespCode_i  ==  CONST_qyRc_user  )  {
#if  0
			 if  (  !qySendMsg(  pSession,  pSock,  pTo,  0,  CONST_qyCmd_end,  0,  0,  0,  NULL,  0  )  )  {
				 char  buf[128*1024];		
				 qyRecvMsg(  pSession,  pSock,  pTo,  &tmpResp,  buf,  sizeof(  buf  )  );
			 }
#endif
		 }
		 qyDisconnect(  pSock  );
	 }

	 //
#ifdef  __DEBUG__
	 traceLog(  (TCHAR*)_T(  "%s: qnmCloseSession_msg leaves %s"),  tWho, hint  );
#endif 

	 //
	 return;
}



