

#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyTCharCommProc.h"

#include	"qyCommProc.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qnmCommProc.h"
#include	"qySyncCommProc.h"

#include	"qyThread.h"


static DWORD WINAPI threadProc_internal(  LPVOID lpParameter  )
{
	int				iErr	=	-1;
	CQyThread	*	pThread	=	(  CQyThread  *  )lpParameter;
	if  (  !pThread  )  return  -1;

	if  (  !pThread->InitInstance(  )  )  goto  errLabel;


	MSG msg;
	while (GetMessage(&msg, NULL, 0,0) ) {
		//vnclog.Print(LL_INTINFO, VNCLOG("message %d recieved\n"), msg.message);

		pThread->procMsg(  msg.message,  msg.wParam,  msg.lParam  );

		DispatchMessage(&msg);
	}


	iErr  =  0;
errLabel:
	pThread->ExitInstance(  );

	return  iErr;
}



CQyThread::CQyThread(  )
{
	this->m_hThread  =  NULL;
	this->m_nThreadID  =  0;
}

CQyThread::~CQyThread(  )
{
}


BOOL CQyThread::CreateThread(  DWORD dwCreateFlags,  UINT nStackSize,  LPSECURITY_ATTRIBUTES lpSecurityAttrs )
{
	BOOL	bRet	=	FALSE;
	DWORD	dwThreadDaemonId;
	m_hThread  =  ::CreateThread(  NULL,  0,  threadProc_internal,  this,  CREATE_SUSPENDED,  &dwThreadDaemonId  );		
	if  (  !m_hThread  )  goto  errLabel;				
	this->m_nThreadID  =  dwThreadDaemonId;			
	bRet  =  TRUE;
errLabel:
	return  FALSE;
}
 

DWORD CQyThread::ResumeThread()
{
	return  ::ResumeThread(  this->m_hThread  );
}

BOOL CQyThread::PostThreadMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	return  ::PostThreadMessage(  this->m_nThreadID,  message,  wParam,  lParam  );
	
}


BOOL CQyThread::InitInstance()
{
	return  TRUE;
}

int CQyThread::ExitInstance() // default will 'delete this'
{
	TCHAR	tBuf[128]	=	_T(  ""  );

	//  CloseHandle(  m_hThread  );
	delete  this;

	return  0;
}
		

LRESULT CQyThread::procMsg(  UINT  msg,  WPARAM wParam, LPARAM lParam)
{
	return  0;
}


