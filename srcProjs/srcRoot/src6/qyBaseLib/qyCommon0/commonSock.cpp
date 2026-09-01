

#include	<winsock2.h>  
#include	"qyCommon.h"
//  #include	"commonFunc1.h"
//  #include	"commonSock.h"
//WIN32;<不同选项>

// *pLen不允许为0
// timeoutVal is in milliseconds.
 extern "C" int _cdecl asrRecv( void *pAsrSockParam, char *buf, int *pLen, int timeoutVal )
{
	int iErr = -1;
	ASR_SOCK *pAsrSock = ( ASR_SOCK * )pAsrSockParam;
	int nRead = -1;

	if  (  !*pLen  )	return  -1;

	TIMEVAL tv;
	int nRet;
	tv.tv_sec = timeoutVal / 1000;
	tv.tv_usec = ( timeoutVal % 1000 ) * 1000;
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(pAsrSock->sockFd,&rfds);
	nRet=select(1,&rfds,NULL,NULL,&tv);
	if(nRet==SOCKET_ERROR) goto errLabel;
	if(nRet==0) {
		iErr = 1;
		goto errLabel;
	}

	nRead = recv( pAsrSock->sockFd, buf, *pLen, 0 );
	if ( nRead <= 0 ) goto errLabel;

	*pLen = nRead;
	iErr = 0;

errLabel:

	return iErr;

}


 // 持续接收内容，将内容接收完全。
 extern "C" int _cdecl asrRecvX( void *pAsrSockParam, char *buf, int len, int timeoutVal )
{
	int nRead = 0;

	if ( len <= 0 ) return -1;
	
	do {
		nRead = len;
		if ( asrRecv( pAsrSockParam, buf, &nRead, timeoutVal ) ) return -1;
		len -= nRead;
		buf += nRead;
		
	} while ( len > 0 );

	return 0;

}


 // len不允许为0
 extern "C" int _cdecl asrSend( void *pAsrSockParam, char *buf, int len, int timeoutVal )
{
	int iErr = -1;
	ASR_SOCK *pAsrSock = ( ASR_SOCK * )pAsrSockParam;
	int nSent = -1;

	if  (  !len  )  return  -1;

	int ret;
	TIMEVAL tm;
	fd_set wfds;
	FD_ZERO(&wfds);
	FD_SET( pAsrSock->sockFd, &wfds );
	tm.tv_sec = timeoutVal / 1000;
	tm.tv_usec = ( timeoutVal % 1000 ) * 1000;
	if ( ( ret = select( 0, NULL, &wfds, NULL, &tm ) ) <= 0 )  {
		qyDisplayLastError(  "asrSend: select failed"  );  goto errLabel;
	}

	nSent = send( pAsrSock->sockFd, buf, len, 0 );
	if ( nSent != len ) {
		qyDisplayLastError(  "asrSend: send failed"  );  goto errLabel;
	}

	iErr = 0;

errLabel:

	return iErr;
	

}

  extern "C" int asrConnect( char *ipaddr, int port, int timeoutVal, void *pAsrSockParam )
{
    
	 int iErr = -1;
	 int tmp;
	 struct sockaddr_in server;
	 ASR_SOCK *pAsrSock = ( ASR_SOCK * )pAsrSockParam;
	 unsigned long arg;
	
	 //  if ( pAsrSock->sockFd >= 0 ) return -1;
	 if  (  !isSocketInvalid(  pAsrSock->sockFd  )  )  return  -1;	//  2014/02/08

	 pAsrSock->sockFd = socket( AF_INET, SOCK_STREAM, 0 );
	 //  if ( pAsrSock->sockFd < 0 ) goto errLabel;
	 if  (  isSocketInvalid(  pAsrSock->sockFd  )  )  goto  errLabel;	//  2014/02/08

	 // traceLog2( "asrConnect( ): now call setsockopt( )", "" );

	 BOOL sopt;
	 sopt=TRUE;
	 setsockopt(pAsrSock->sockFd,IPPROTO_TCP,TCP_NODELAY,(char *)&sopt,sizeof(BOOL));
	 sopt=TRUE;
	 setsockopt(pAsrSock->sockFd,SOL_SOCKET,SO_DONTLINGER,(char *)&sopt,sizeof(BOOL));
	

	 arg = 1;
	 tmp = ioctlsocket( pAsrSock->sockFd, FIONBIO, &arg );
	 if ( tmp ) goto errLabel;


	 server.sin_family =	AF_INET; 
	 server.sin_addr.S_un.S_addr = inet_addr( ipaddr );
	 server.sin_port = htons( ( u_short )port );

 	 tmp = connect( pAsrSock->sockFd, ( struct sockaddr * )&server, sizeof( server ) );
 	 
	 if ( tmp != 0 ) {
		 tmp = WSAGetLastError( );
		 if ( tmp != WSAEWOULDBLOCK ) goto errLabel;
			 
		 int ret;
		 TIMEVAL tm;
		 fd_set wfds;
		 
		 FD_ZERO(&wfds);
		 FD_SET( pAsrSock->sockFd, &wfds );
		 tm.tv_sec = timeoutVal / 1000;
		 tm.tv_usec = ( timeoutVal % 1000 ) * 1000;
		 if ( ( ret = select( 0, NULL, &wfds, NULL, &tm ) ) <= 0 ) 
			 goto errLabel;
		 
	 }
	
	 arg = 0;
	 tmp = ioctlsocket( pAsrSock->sockFd, FIONBIO, &arg );
	 if ( tmp ) goto errLabel;

	 iErr = 0;

errLabel:

	 if ( iErr ) {
		//  if ( pAsrSock->sockFd >= 0 ) 
		 if  (  !isSocketInvalid(  pAsrSock->sockFd  )  )
		{
			closesocket( pAsrSock->sockFd ); pAsrSock->sockFd = -1;
		}
	 }
	 
	 return iErr;

}



 extern  "C"  void  asrDisconnect(  void  *  pAsrSockParam  )
{
	ASR_SOCK  *  pAsrSock  =  (  ASR_SOCK  *  )pAsrSockParam;
	
	//  if  (  pAsrSock->sockFd  <  0  )  return;
	if  (  isSocketInvalid(  pAsrSock->sockFd  )  )  return;	//  2014/02/08

	closesocket(  pAsrSock->sockFd  );
	pAsrSock->sockFd  =  -1;

	return;
}

 extern "C" int getHostIp( char *name, char *ipBuf )
{
	int iErr = -1;
	char buf[256];
	struct hostent *p;

	if ( !name ) gethostname( buf, sizeof( buf ) );
	else if ( strlen( name ) < sizeof( buf ) )
		sprintf( buf, "%s", name );
	else 
		goto errLabel;

	p = gethostbyname( buf );
	if ( !p ) goto errLabel;

	sprintf( ipBuf, "%s", inet_ntoa( *( struct in_addr * )p->h_addr_list[0] ) );

	iErr = 0;

errLabel:
	
	return iErr;

}
 
 // iTimeout is in milliseconds.
 //  extern "C" int asrAccept( int sockFd, int *piCliSockFd, int iTimeout )
 extern "C" int asrAccept( SOCKET sockFd, SOCKET *piCliSockFd, int iTimeout )
{
	
	int iErr = -1;
	// Check for connection
	fd_set rdfds;
	TIMEVAL tm;
	SOCKADDR_IN saddr;
	int len=sizeof(SOCKADDR_IN);
	SOCKET accs;


	FD_ZERO( &rdfds );
	FD_SET( sockFd, &rdfds );
	
	tm.tv_sec=iTimeout / 1000;
	tm.tv_usec=( iTimeout % 1000 ) * 1000;

	if ( select( 0, &rdfds, NULL, NULL, &tm ) <= 0 ) {
		goto errLabel;
	}

	// Accept socket

	accs=accept( sockFd,(SOCKADDR *)&saddr,&len);
	if(accs==INVALID_SOCKET) return NULL;

	BOOL sopt;
	sopt=TRUE;
	setsockopt(accs,IPPROTO_TCP,TCP_NODELAY,(char *)&sopt,sizeof(BOOL));
	sopt=TRUE;
	setsockopt(accs,SOL_SOCKET,SO_DONTLINGER,(char *)&sopt,sizeof(BOOL));

	*piCliSockFd = accs;
	
	iErr = 0;

errLabel:
		
	return iErr;
}

 
 //int asrListen( int nPort, int *pSockFd )
 int asrListen( int nPort, SOCKET *pSockFd )	//  2014/02/08
{
	int iErr = -1;
	struct in_addr bindAddr;
	SOCKET s = -1;

	s = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if ( s == INVALID_SOCKET ) goto errLabel;
	
	BOOL sopt;
	sopt=TRUE;
	setsockopt(s,IPPROTO_TCP,TCP_NODELAY,(char *)&sopt,sizeof(BOOL));
	sopt=TRUE;
	setsockopt(s,SOL_SOCKET,SO_DONTLINGER,(char *)&sopt,sizeof(BOOL));
	
	bindAddr.S_un.S_addr=INADDR_ANY;
	
	// Bind socket and listen
	SOCKADDR_IN saddr;
	memset(&saddr,0,sizeof(SOCKADDR_IN));
	saddr.sin_addr=bindAddr;
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons((WORD)nPort);
	
	if(bind(s,(SOCKADDR *) &saddr,sizeof(SOCKADDR_IN))==SOCKET_ERROR) {
		goto errLabel;
	}
	if(listen(s,SOMAXCONN)!=0) {
		goto errLabel;
	}
	
	*pSockFd = s;
	
	iErr = 0;

errLabel:
	
	if ( iErr ) {
		//  if ( s >= 0 ) 
		if  (  !isSocketInvalid(  s  )  )  {
			closesocket( s );
		}
	}

	return iErr;

}

 extern  "C"  int  setSockTimeout(  SOCK_TIMEOUT  *  p  )
{
	p->iAccept  =  DEFAULT_QY_ACCEPT_TIMEOUT;
	p->iConnect  =  DEFAULT_QY_CONNECT_TIMEOUT;
	p->iRead  =  DEFAULT_QY_READ_TIMEOUT;
	p->iWrite  =  DEFAULT_QY_WRITE_TIMEOUT;
	p->iSelect  =  DEFAULT_qyTo_select;
	
	return 0;
}

