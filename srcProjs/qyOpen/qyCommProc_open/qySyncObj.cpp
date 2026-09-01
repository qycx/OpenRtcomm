
#include	"stdafx.h"

#include	<windows.h>
#include	"qySyncObj.h"
//  #include	"qyCommon.h"



 HANDLE  syncQmObjQ(  LPCTSTR  mutexName,  unsigned  int  uiTimeoutInMilliSeconds  )
{
	 int		iErr			=	-1;
	 HANDLE		hMutex			=	NULL;
	 DWORD		dwRet			=	0;
	 
	 if  (  !mutexName  )  goto  errLabel;

	 //  _sntprintf(  mutexName,  mycountof(  mutexName  ),  _T(  "syncQmObjQ"  )  );
	 if  (  !uiTimeoutInMilliSeconds  )  {				//  2008/05/22, ÔÚuiTimeoutInMilliSecondsÎª0Ê±£¬ÒâÎ¶×ÅÐèÒªÒ»¸ö¿ìËÙ»ñÈ¡¿ØÖÆÈ¨µÄ·½·¨¡£Èç¹û²»ÄÜ£¬¾Í·ÅÆú
		 hMutex  =  CreateMutex(  NULL,  TRUE,  mutexName  );
		 if  (  !hMutex  ||  GetLastError(  )  ==  ERROR_ALREADY_EXISTS  )  {
			 //  traceLogA(  "CreateMutex failed: %s,  lastError is %d",  (  hMutex  ?  "hMutex is ok"  :  "hMutex is null"  ),  GetLastError(  )  );  //  2004/05/13
			 goto  errLabel;
		 }
		}
	 else  {
		   hMutex = CreateMutex(  NULL,  0,  mutexName  );
		   if  (  !hMutex  )  {
			   #ifdef  __DEBUG__
					   TCHAR  tBuf[256];
					   _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "CreateMutex failed: %s,  lastError is %d\n"  ),  (  hMutex  ?  _T(  "hMutex is ok"  )  :  _T(  "hMutex is null"  )  ),  GetLastError(  )  );  //  2004/05/13
					   OutputDebugString(  tBuf  );
			   #endif
			   goto  errLabel;
		   }

		   dwRet  =  WaitForSingleObject(  hMutex,  uiTimeoutInMilliSeconds  );		
		   if ( dwRet == WAIT_FAILED || dwRet == WAIT_TIMEOUT )  goto  errLabel;
	 }

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {

		 if  (  hMutex  )  {
			 ReleaseMutex(  hMutex  );  CloseHandle(  hMutex  );  hMutex  =  NULL;
		 }

	 }

	 return  hMutex;
}


 void  cancelSyncQmObjQ(  HANDLE  hMutex  )
{

	 if  (  hMutex  )  {
		 ReleaseMutex(  hMutex  );  CloseHandle(  hMutex  );  hMutex  =  NULL;
	 }
}
