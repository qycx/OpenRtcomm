
#ifndef __COMMONSOCK_H__
#define __COMMONSOCK_H__	/* { */

#ifdef  __cplusplus
  extern  "C"  {
#endif

#include	"myTypes.h"
	  //
#if  0
#include <winsock2.h>  // 确保包含正确的头文件
#include <ws2tcpip.h>
#endif 

	  //
#include	"commonSock_open.h"


	  //
typedef  struct  __qy_sock_t  {
				 //  int		  sockFd;		//	第一个成员是asrSock的，应予以保持，包括成员与在结构中的位置	
				 SOCKET			  sockFd;		//	2014/02/07. 第一个成员是asrSock的，应予以保持，包括成员与在结构中的位置	
}		 QY_SOCK;

#define  ASR_SOCK	QY_SOCK

//
#define	isSocketInvalid(  s  )	(  (  s  )  ==  INVALID_SOCKET  )	//  2013/02/08

//
#if  0
//
typedef  struct  __sock_timeout_t  {
				 int				iAccept;
				 int				iConnect;
				 int				iRead;
				 int				iWrite;
				 int				iSelect;		//  仅在某些试探状态中使用，读写数据时使用iRead, iWrite
}		 SOCK_TIMEOUT;
//
#endif 

//
extern int _cdecl asrRecv( void *pAsrSockParam, char *buf, int *pLen, int timeoutVal );
extern int _cdecl asrRecvX( void *pAsrSockParam, char *buf, int len, int timeoutVal );
extern int _cdecl asrSend( void *pAsrSockParam, char *buf, int len, int timeoutVal );
extern int asrConnect( char *ipaddr, int port, int timeoutVal, void *pAsrSockParam );
extern void asrDisconnect( void *pAsrSockParam );
extern int getHostIp( char *name, char *ipBuf );
//  extern int asrListen( int nPort, int *pSockFd );
extern int asrListen( int nPort, SOCKET *pSockFd );	//  2014/02/08
//  extern int asrAccept(int sockFd, int *piCliSockFd, int timeout );
extern int asrAccept(SOCKET sockFd, SOCKET *piCliSockFd, int timeout );
int getHostIp( char *name, char *ipBuf );


#ifdef  __DEBUG__
		#define		DEFAULT_QY_ACCEPT_TIMEOUT		10000
		#define		DEFAULT_QY_CONNECT_TIMEOUT		4000
		#define		DEFAULT_QY_WRITE_TIMEOUT		10000
		#define		DEFAULT_QY_READ_TIMEOUT			100000
		#define		DEFAULT_qyTo_select				3000
#else
		#define		DEFAULT_QY_ACCEPT_TIMEOUT		8000	//  5000
		#define		DEFAULT_QY_CONNECT_TIMEOUT		5000	//  2000
		#define		DEFAULT_QY_WRITE_TIMEOUT		5000	//  2000
		#define		DEFAULT_QY_READ_TIMEOUT			20000	//  10000
		#define		DEFAULT_qyTo_select				5000
#endif

#define DEFAULT_ASR_CONNECT_TIMEOUT		DEFAULT_QY_CONNECT_TIMEOUT
#define DEFAULT_ASR_SEND_TIMEOUT		DEFAULT_QY_WRITE_TIMEOUT		
#define DEFAULT_ASR_RECV_TIMEOUT		DEFAULT_QY_READ_TIMEOUT		



#define DEFAULT_ASR_RECV_LONG_TIMEOUT	20000

#ifdef __cplusplus
 }
#endif

#endif /* } */

