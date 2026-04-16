
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<stdlib.h>

#include	"qyCommon.h"
#include	"qyMtSock.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	<tchar.h>
#include	"qyTCharCommProc.h"
#include	"qySyncCommProc.h"

#include	"qyLicense.h"
#include	"qyCommProc.h"
#include	"qyLangCommProc.h"						//  2005/01/24
#include	"qnmCommProc.h"

#include	"qnmCommProc.h"


extern  "C"  DWORD WINAPI mtServSockThreadProc( LPVOID lpParameter );
extern  "C"  DWORD WINAPI mtCliSockThreadProc( LPVOID lpParameter );


 //  MT_SOCK  gMS;

 extern  "C"  BOOL  bQyMtSockQuit(  void  *  pMtSockParam  )
{
	 MT_SOCK_COMMON  *  pMtSock  =  (  MT_SOCK_COMMON  *  )pMtSockParam;

	 if  (  !pMtSock  )  return  TRUE;

	 return  pMtSock->bQuit;
}


 /*
 extern  "C"  MT_SERVWORK  *  getQyMtSockServWork(  )
{
	 return  &pMtSock->servWork;
}
*/


 extern  "C"  int  initQyMtSock(  char  *  servIp,  unsigned  short  port,  MT_SERVWORK  *  pServWork,  void  *  pParentParam,  int  iType_pParentParam,  void  **  ppMtSock  )
{
	int				iErr				=	-1;
	DWORD			dwThreadDaemonId;
	int				i;
	MT_SOCK		*	pMtSock				=	0;
	//  COMMON_PARAM	commonParam;

	if  (  !pServWork  )  return  -1;
	if  (  pServWork->usMaxConns  >  MAX_CONNS  )  {
		traceLogA(  "参数过大：MT_SERVWORK中的并发连接数不能大于%d",  MAX_CONNS  );
		return  -1;
	}
	if  (  !ppMtSock  ||  *ppMtSock  )  return  -1;	//  此*ppMtSock为了将指针传出去

	if  (  !(  pMtSock  =  (  MT_SOCK  *  )mymalloc(  sizeof(  MT_SOCK  )  )  )  )  goto  errLabel;
	memset(  pMtSock,  0,  sizeof(  pMtSock[0]  )  );
	
	pMtSock->servSockFd = -1;
	for ( i = 0; i < MAX_CONNS; i ++ )	pMtSock->cliSockFds[i] = -1;

	//
	pMtSock->pParentParam		=	pParentParam;
	pMtSock->iType_pParentParam  =  iType_pParentParam;	//  2015/07/19

	//
	if  (  servIp  &&  strlen( servIp ) <= MAX_IP_ADDR_LEN  ) strcpy( pMtSock->servIp, servIp );
	else  { 
			traceLogA(  "initQyMtSock: servIp is null or too long string, 因此将绑定本机上任意IP"  );
			strcpy( pMtSock->servIp, ""  );
	}
	pMtSock->port				=	port;

	memcpy(  &pMtSock->servWork,  pServWork,  sizeof(  MT_SERVWORK  )  );
	if  (  lstrlen(  pMtSock->servWork.mutexName  )  >=  mycountof(  pMtSock->servWork.mutexName  )  )  goto  errLabel;
	if  (  !pMtSock->servWork.sT.iAccept  ||  !pMtSock->servWork.sT.iRead  )  {
		//
		//traceLogA(  "没有赋超时参数，将取缺省超时值"  );
		//
		setSockTimeout(  &pMtSock->servWork.sT  );
	}
	//  memcpy(  &pMtSock->sT,  &pMtSock->servWork.sT,  sizeof(  pMtSock->sT  )  );
	if  (  !pMtSock->servWork.usMaxConns  )  pMtSock->servWork.usMaxConns  =  MAX_CONNS;
	
	pMtSock->iWaitTimeout  =  3000;

	for  (  i  =  0;  i  <  pMtSock->servWork.usMaxConns;  i  ++  )  {
		 pMtSock->hEvents[i]  =  CreateEvent(  NULL,  FALSE,  FALSE,  NULL  );
		 if  (  !pMtSock->hEvents[i]  )  goto  errLabel;
	}

	pMtSock->bQuit = FALSE;
	pMtSock->hServThread = CreateThread( NULL, 0, mtServSockThreadProc, pMtSock, 0, &dwThreadDaemonId );
	if ( !pMtSock->hServThread ) goto errLabel;
	traceLogA(  "initMtSock: CreateThread(  ) [%lu] runs ...",  dwThreadDaemonId  );
	
	// if ( pf ) pMtSock->pfDoServWork = pf;

	for  (  i  =  0;  i  <  pMtSock->servWork.usMaxConns;  i  ++  )  {
		 //  MACRO_makeCommonParam3(  pMtSock,  (  void  *  )i,  0,  commonParam  );
		 pMtSock->hCliThreads[i]  =  CreateThread(  NULL,  0,  mtCliSockThreadProc,  (  LPVOID  )pMtSock,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
		 if  (  !pMtSock->hCliThreads[i]  )  goto  errLabel;
		 pMtSock->dwThreadIds[i]  =  dwThreadDaemonId;	//  2007/03/29, 为了引入这个标记，以便mtCliSockThreadProc能够在pMtSock里找到存放的物理位置，故要先挂起一下，然后再恢复
		 if  (  ResumeThread(  pMtSock->hCliThreads[i]  )  ==  -1  )  goto  errLabel;
		 traceLogA(  "initMtSock( ): CreateThread(  ) [%lu] runs ...",  dwThreadDaemonId  );		 
	}
	
	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pMtSock  )  {
	
			pMtSock->bQuit = TRUE;
		
			for ( i = 0; i < MAX_CONNS; i ++ ) {
				if ( pMtSock->hCliThreads[i] ) {
					::WaitForSingleObject( pMtSock->hCliThreads[i], INFINITE );
					pMtSock->hCliThreads[i] = NULL;
				}
				if ( pMtSock->hEvents[i] ) {
					CloseHandle( pMtSock->hEvents[i] );
					pMtSock->hEvents[i] = NULL;
				}
			}

			if ( pMtSock->hServThread ) {
				::WaitForSingleObject( pMtSock->hServThread, INFINITE );
				pMtSock->hServThread = NULL;
			}

			free(  pMtSock  );	//  这里要释放掉

		}		
	}

	if  (  !iErr  )  {
		*ppMtSock  =  pMtSock;
	}

	return iErr;

}


 extern "C" void exitQyMtSock(  void  *  pMtSockParam  )
{
	MT_SOCK	*	pMtSock  =  (  MT_SOCK  *  )pMtSockParam;
	int			i;
	
	if  (  !pMtSock  )  return;

	pMtSock->bQuit = TRUE;
		
	for ( i = 0; i < MAX_CONNS; i ++ ) {
		if ( pMtSock->hEvents[i] ) SetEvent( pMtSock->hEvents[i] ); 
		if ( pMtSock->hCliThreads[i] ) {
			debugLog( "exitMtSock( ): before WaitFor thread[%d]", i );
			::WaitForSingleObject( pMtSock->hCliThreads[i], INFINITE );
			if ( CloseHandle( pMtSock->hCliThreads[i] ) ) {
				debugLog( "exitMtSock( ): CloseHandle( hCliThread[%d] ) succeeded", i );
			}
			else debugLog(  "exitMtSock( ): CloseHandle( hCliThread[%d] ) failed.", i );
			pMtSock->hCliThreads[i] = NULL;
		}		
		if ( pMtSock->hEvents[i] ) {
			debugLog( "exitMtSock( ): before CloseHandle( hEvent[%d] )", i );
			CloseHandle( pMtSock->hEvents[i] );
			pMtSock->hEvents[i] = NULL;
		}		
	}

	if ( pMtSock->hServThread ) {
		::WaitForSingleObject( pMtSock->hServThread, INFINITE );
		if ( CloseHandle( pMtSock->hServThread ) ) {
			debugLog( "exitMtSock( ): CloseHandle( hServThread[%d] ) succeeded", i );
			}
		else debugLog(  "exitMtSock( ): CloseHandle( hServThread[%d] ) failed.", i );
		pMtSock->hServThread = NULL;
	}

	myfree(  pMtSock  );		//  这里要释放，不要忘了

	return;
	
}

 extern  "C"  DWORD  WINAPI  mtServSockThreadProc(  LPVOID  lpParameter  )
{
	int				iErr		=	-1;
	MT_SOCK		*	pMtSock		=	(  MT_SOCK  *  )lpParameter;
	int				i;

	traceLogA(  "mtServSockThreadProc enters"  );

	if  (  asrListen(  pMtSock->port,  &pMtSock->servSockFd  )  )  {
		pMtSock->bListenFailed  =  TRUE;
		traceLogA(  "不能监听端口%d",  pMtSock->port  );
		goto  errLabel;
	}
	traceLogA(  "监听端口%d",  pMtSock->port  );
	qyShowInfo1(  CONST_qyShowType_sysInfo,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  "Listen on "  ),  _T(  "%u"  ),  pMtSock->port  ); 


	//
	while  (  !pMtSock->bQuit  )  {
		   //  OutputDebugString( "try to get an available socket.\n" );
		   while  (  !pMtSock->bQuit  )  {
				  for  (  i  =  0;  i  <  pMtSock->servWork.usMaxConns;  i  ++  )  {
					   if  (  !pMtSock->bUseds[i]  )  break;
				  }
				  if  (  i  <  pMtSock->servWork.usMaxConns  )  break;
				  Sleep( 1500 );
				  //  OutputDebugString( "no availabel socket, wait.\n" );			
		   }
		   if  (  pMtSock->bQuit  )  break;

		   if  (  asrAccept(  pMtSock->servSockFd,  &pMtSock->cliSockFds[i],  pMtSock->servWork.sT.iAccept  )  )  continue;
		   //  OutputDebugString(  "asrAccept .. succeeded.\n"  );
		   pMtSock->bUseds[i] = TRUE;
		   if  (  !SetEvent(  pMtSock->hEvents[i]  )  )  goto errLabel;
		
		   continue;

	}

errLabel:

	if  (  pMtSock->servSockFd  >=  0  )  {  closesocket(  pMtSock->servSockFd  );  pMtSock->servSockFd  =  -1;  }

	traceLogA(  "mtServSockThreadProc leaves"  );

	return  iErr;

}
 


 
 extern  "C"  DWORD  WINAPI  mtCliSockThreadProc(  LPVOID  lpParameter  )
{
	int						iErr				=	-1;
	int						iRet;
	MT_SOCK			*		pMtSock				=	(  MT_SOCK  *  )lpParameter;
	int						id					=	-1;
	DWORD					dwThreadId			=	GetCurrentThreadId(  );
	int						i;
	//  
	MT_SOCK_SUBTHREADINFO	subThreadInfo;
	BOOL					bServWorkInited		=	FALSE;

	traceLogA(  "mtCliSockThreadProc enters"  );

	for  (  i  =  0;  i  <  mycountof(  pMtSock->dwThreadIds  );  i  ++  )  {
		 if  (  pMtSock->dwThreadIds[i]  ==  dwThreadId  )  break;
	}
	if  (  i  ==  mycountof(  pMtSock->dwThreadIds  )  )  {
		traceLogA(  "Error: id is not found"  );  goto  errLabel;
	}
	id  =  i;

	memset( ( char * )&subThreadInfo, 0, sizeof( subThreadInfo ) );

	subThreadInfo.iServiceId  =  pMtSock->servWork.iServiceId;		//  2007/03/12
	if  (  pMtSock->servWork.mutexName[0]  )  {
		subThreadInfo.hMutex = CreateMutex(  NULL,  FALSE,  pMtSock->servWork.mutexName  );
		if  (  !subThreadInfo.hMutex  )  {
			qyDisplayLastError(  "mtCliSockThreadProc: CreateMutex( ) failed"  );		
			goto  errLabel;
		}
	}
	subThreadInfo.pTo				=	&pMtSock->servWork.sT;
	subThreadInfo.pParentParam		=	pMtSock->pParentParam;

	if  (  pMtSock->servWork.pfInitServWork  &&  pMtSock->servWork.pfInitServWork(  &subThreadInfo, 0  )  )  {
		traceLogA(  "mtCliSockThreadProc(  ): pfInitServWork(  ) failed."  );
		goto  errLabel;
	}
	bServWorkInited					=	TRUE;

	while  (  !pMtSock->bQuit  )  {
		
		   iRet  =  ::WaitForSingleObject(  pMtSock->hEvents[id],  pMtSock->iWaitTimeout  );
		   if  (  iRet  ==  WAIT_FAILED  )  goto errLabel;
		   if  (  iRet  ==  WAIT_TIMEOUT  )  continue;
		   if  (  pMtSock->bQuit  ) break;
		   if  (  pMtSock->servWork.pfDoServWork ) pMtSock->servWork.pfDoServWork(  (  void  *  )&subThreadInfo,  (  void  *  )pMtSock->cliSockFds[id],  0  );
		   else  {
				 traceLogA(  "pfDocCliWork is not given."  );
				 Sleep(  1000  );
		   }
		   closesocket( pMtSock->cliSockFds[id] ); pMtSock->cliSockFds[id] = -1;
		   pMtSock->bUseds[id] = FALSE;
		   continue;
	}
	
	iErr  =  0;

errLabel:

	if  (  bServWorkInited && pMtSock->servWork.pfExitServWork  )  pMtSock->servWork.pfExitServWork(  &subThreadInfo, 0  );

	if  (  subThreadInfo.hMutex  )  {
		ReleaseMutex(  subThreadInfo.hMutex  );		//  为确保所有的Mutex都释放，故在这里强制调用一下ReleaseMutex
		::CloseHandle(  subThreadInfo.hMutex  );	
	}
	
	traceLogA(  "mtCliSockThreadProc leaves"  );

	return iErr;

}


 /*
 extern "C" int doCliWork( int sockFd )
{
	char buf[256];
	ASR_SOCK aS;
	int len = sizeof( buf ) - 1;
	int i = 0;
	int iRet = -1;

	aS.sockFd = sockFd;

	while ( !pMtSock->bQuit ) {
		if ( i == 10 ) break;
		iRet = asrRecv( &aS, buf, &len, pMtSock->sT.iRead );
		if ( iRet < 0 ) break;
		if ( iRet ) continue;
		buf[len] = 0;
		OutputDebugString( buf );
	}
	

	 return 0;
}

*/




