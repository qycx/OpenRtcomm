

#ifndef  __QYSOCKPUBLIC_H__
#define  __QYSOCKPUBLIC_H__	/*  {  */

#ifdef  __cplusplus
  extern  "C"  {
#endif

int  _cdecl  qyTcpStart(  );
int  _cdecl  qyTcpEnd(  );
void  clearQySock(  QY_SOCK * pSock );
int  qyRecv( void *pQySockParam, char *buf, int *pLen, int timeoutVal );
//  int  qyRecvEx( void *pQySockParam, char *buf, int len, int timeoutVal );
#define		qyRecvEx( pQySockParam, buf, len, timeoutVal )  asrRecvX( pQySockParam, buf, len, timeoutVal )
#define		qyRecvX(  pQySockParam,  buf,  len,  timeoutVal  )	qyRecvEx(  pQySockParam,  buf,  len,  timeoutVal  )
int  qySend( void *pQySockParam, char *buf, int len, int timeoutVal );
int  qyConnect( char *ipaddr, int port, void *pQySockParam, int timeoutVal );
void  qyDisconnect( void *pQySockParam );
int  getHostIp( char *name, char *ipBuf );
//int  qyListen( int nPort, int *pSockFd );
int  qyListen( int nPort, SOCKET *pSockFd );	//  2014/02/07

//
int setSockTimeout( SOCK_TIMEOUT *p );

//  int  qyAccept(int sockFd, int *piCliSockFd, int timeout );
int  qyAccept(SOCKET sockFd, SOCKET *piCliSockFd, int timeout );
//  int  qyWaitForRead(  int  s,  unsigned  long  timeoutVal  );
int  getHostIp( char *name, char *ipBuf );
//  int  getLocalIpBySocket(  int  s,  char  *  ip  );
int  getLocalIpBySocket(  SOCKET  s,  char  *  ip  );
//  int  getRemoteIpBySocket(  int  s,  char  *  ip  );
int  getRemoteIpBySocket(  SOCKET  s,  char  *  ip  );
BOOL  bQySockOpen(  QY_SOCK  *  pSock  );

BOOL  bulIpValid(  unsigned  long  ulIp  );
BOOL  bIpValid(  char  *  ip  );
BOOL  bMacValid(  char  *  mac  );
BOOL  bQyTimeValid(  char  *  timeBuf  );
BOOL  bQyIpLocal(  unsigned  long  ulAddr  );


#ifdef  __cplusplus
  }
#endif

#endif	/*  }  */


