



#include	"qyPrecomp.h"
#include	<stdlib.h>
#include	<Winsock2.h>
#include	<windows.h>
#include	"qyCommon.h"

 extern  "C"  int  _cdecl  qyTcpStart(  )
{
	// Initialize Winsock 1.1
	WSADATA  wsaData;
	
	if  (  WSAStartup(  MAKEWORD(  1,  1  ),  &wsaData  )  !=  0  )  return -1;
	if  (  LOBYTE(  wsaData.wVersion  )  !=  1  ||  HIBYTE(  wsaData.wVersion  )  !=  1  )  {
		WSACleanup(  );
		return   -1;
	}
	
	return  0;
}

 extern  "C"  int  _cdecl  qyTcpEnd(  )
{
	// Clean up Winsock 1.1
	WSACleanup(  );
	return		0;
}

 extern "C" int qyRecv( void *pAsrSockParam, char *buf, int *pLen, int timeoutVal )
{
	 return  asrRecv( pAsrSockParam, buf, pLen, timeoutVal );
}

#if  0
 extern "C" int qyRecvEx( void *pAsrSockParam, char *buf, int len, int timeoutVal )
{
	return asrRecvX( pAsrSockParam, buf, len, timeoutVal );
}
#endif

 extern "C" int qySend( void *pAsrSockParam, char *buf, int len, int timeoutVal )  
{
	return asrSend( pAsrSockParam, buf, len, timeoutVal );
}

 extern "C" int qyConnect( char *ipaddr, int port, void *pAsrSockParam, int timeoutVal  )
{
	 return asrConnect( ipaddr, port, timeoutVal, pAsrSockParam );
}

 extern "C" void qyDisconnect( void *pAsrSockParam )
{
	asrDisconnect( pAsrSockParam );
}

 //  extern "C" int qyListen( int nPort, int *pSockFd )
 extern "C" int qyListen( int nPort, SOCKET *pSockFd )
{
	return asrListen( nPort, pSockFd );
}

 //  extern "C" int qyAccept( int sockFd, int *piCliSockFd, int timeout )
 extern "C" int qyAccept( SOCKET sockFd, SOCKET *piCliSockFd, int timeout )
{
	return asrAccept( sockFd, piCliSockFd, timeout );
}

 extern "C" void clearQySock(  QY_SOCK * pSock )
{
	 memset(  pSock,  0,  sizeof(  QY_SOCK  )  );
	 pSock->sockFd = -1;
}

 extern  "C"  BOOL  bQySockOpen(  QY_SOCK  *  pSock  )
{
	 //  return  (  pSock->sockFd  >=  0  );
	return  pSock->sockFd  !=  INVALID_SOCKET;
}

 //  extern  "C"  int  getLocalIpBySocket(  int  s,  char  *  ip  )
 extern  "C"  int  getLocalIpBySocket(  SOCKET  s,  char  *  ip  )
{	 
	 struct  sockaddr_in  sockip;
	 char  *  ptr  =  NULL;
	 int  len  =  sizeof(  sockip  );

	 sprintf(  ip,  "0.0.0.0"  );
	 if  (  getsockname(  s,  (  struct  sockaddr  *  )&sockip,  &len  )  )  {		 
		 return  -1;
	 }

	 ptr  =  inet_ntoa(  sockip.sin_addr  );
	 if  (  !ptr  )  return  -1;

	 sprintf(  ip,  "%s",  ptr  );
	 
	 return  0;

}


 //  extern  "C"  int  getRemoteIpBySocket(  int  s,  char  *  ip  )
 extern  "C"  int  getRemoteIpBySocket(  SOCKET  s,  char  *  ip  )
{	 
	 struct  sockaddr_in  sockip;
	 char  *  ptr  =  NULL;
	 int  len  =  sizeof(  sockip  );

	 sprintf(  ip,  "0.0.0.0"  );
	 if  (  getpeername(  s,  (  struct  sockaddr  *  )&sockip,  &len  )  )  {		 
		 return  -1;
	 }

	 ptr  =  inet_ntoa(  sockip.sin_addr  );
	 if  (  !ptr  )  return  -1;

	 sprintf(  ip,  "%s",  ptr  );
	 
	 return  0;

}


 // Description: use select() to determine when data is waiting to be read.
 // Parameters:
 //		timeoutVal,		以毫秒计
 // Returns:	
 //		0				成功
 //		1				超时
 //		-1				失败
 //
/*
 extern  "C"  int  invalid_qyWaitForRead(  int  s,  unsigned  long  timeoutVal  )
{
	struct  timeval		Timeout;
	fd_set				readfds;
	int					iSelect		=		-1;

	readfds.fd_count  =  1;
	readfds.fd_array[0]  =  s;
	Timeout.tv_sec  =  (  timeoutVal  /  1000  );
    Timeout.tv_usec  =  (  timeoutVal  %  1000  )  *  1000;		//  微秒

	iSelect  =  select(  1,  &readfds,  NULL,  NULL,  &Timeout  );
	if  (  iSelect  ==  SOCKET_ERROR  )  return  -1;
	if  (  !iSelect  )  return  1;
	return  0;

}
*/

  //  ulIp应该是网络字节顺序的
 extern  "C"  BOOL  bulIpValid(  unsigned  long  ulIp  )
{
	 ulIp  =  qyntohl(  ulIp  );
	 if  (  MACRO_byte0(  ulIp  )  ==  0  ||  MACRO_byte0(  ulIp  )  ==  255  )  return  FALSE;
	 if  (  MACRO_byte3(  ulIp  )  ==  0  ||  MACRO_byte3(  ulIp  )  ==  255  )  return  FALSE;
	 return  TRUE;
}

 extern  "C"  BOOL  bIpValid(  char  *  ip  )
{
	 unsigned  long		ulIp	=	0;

	 if  (  !ip  )  return  FALSE;
	 if  (  (  ulIp  =  inet_addr(  ip  )  )  ==  INADDR_NONE  )  return  FALSE;
	 return  bulIpValid(  ulIp  );
}

 extern  "C"  BOOL  bMacValid(  char  *  mac  )
{
	 int  j;
	 
	 if  (  !mac  )  return  FALSE;
	 
	 for  (  j  =  0;  j  <  CONST_qyMacLen;  j  ++  )  
		  if  (  !qyIsXdigit(  mac[j]  )  )  return  FALSE;

	 if  (  !memcmp(  mac,  CONST_qyNullMac,  CONST_qyMacLen  )  )  return  FALSE;
	 
	 //  2004/02/28添加对mac的全f的过滤
	 for  (  j  =  0;  j  <  CONST_qyMacLen;  j  ++  )
		  if  (  mac[j]  !=  'f'  ||  mac[j]  !='F'  )  break;
     if  (  j  ==  CONST_qyMacLen  )  return  FALSE;

	 return  TRUE;

}

 extern  "C"  BOOL  bQyTimeValid(  char  *  timeBuf  )
{
	 if  (  !timeBuf  )  return  FALSE;

	 for  (  int  i  =  0;  i  <  CONST_qyTimeLen;  i  ++  )  {
		  if  (  !qyIsDigit(  timeBuf[i]  )  )  return  FALSE;
	 }
	 return  TRUE;
}


