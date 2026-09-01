
#include	"stdafx.h"
#include	<stdio.h>
#include	<tchar.h>
//#include	"qmOpenCommon.h"
#include	"qyDefs_open.h"
#include	"timeFunc_open.h"
#include	"dbgFunc_open.h"
#include <time.h>


//
 int logStatus(  LPCTSTR  statusLogFile,  LPCTSTR  tWho,  LPCTSTR  tWhere,  int  logType,  LPCTSTR  logDesc  )
 {
	 int  iErr  =  -1;
	 
	 FILE  *  fp  =  NULL;
	 //CQyMcDaemon  *  pDaemon  =  g_pDaemon;
	 TCHAR			tBuf[25600];

	 if (!tWho)  tWho = _T("");
	 if  (  !tWhere  )  tWhere  =  _T(  ""  );
	 if  (  !logDesc  )  logDesc  =  _T(  ""  );

	 do  {  
		 fp=  _tfopen(  statusLogFile,  _T(  "a,ccs=utf-8"  )  );
		 if  (  !fp  )  break;

		 char  timeBuf[CONST_qyTimeLen  +  1];
		 //getCurTime(  timeBuf  );
		 time_t t;  time(&t);
		 getTimelStr_open(t,timeBuf,  mycountof(timeBuf));


		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%S:     %s:     %s:     %d:     %s"  ),  timeBuf,  tWho,  tWhere,  logType,  logDesc  );
		 _ftprintf(  fp,  _T(  "%s\n"  ),  tBuf  );

		 //
	 }  while  (  false  );
	 
	 //
	 if  (  fp  )  {
		 fclose(  fp  );
	 }

	 return iErr;
 }



 //
  int chkStatusLogFile(  int maxFileLen,  LPCTSTR  statusLogFile  )
 {

	 TCHAR			tBuf[256];



	 do  {
		 LPCTSTR  fullFilePath  =  statusLogFile;
		 	
		 struct _stat64 statBuf;
		 if (_tstat64(fullFilePath, &statBuf))  return  -1;
		 unsigned  __int64  ui64FileLen = statBuf.st_size;

		 //
		 //int maxFileLen  =  50  *  1000  *  1000;
		 //
#ifdef  __DEBUG__
		 //maxFileLen  =  50;
#endif
		 //
		 if  (  ui64FileLen  >  maxFileLen  )  {
			 DeleteFile(fullFilePath);
			 //
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "statusLogFile (%I64u) too big, DeleteFile"  ),  ui64FileLen  );
			 logStatus(statusLogFile,  _T( ""  ),  _T(""), 0, tBuf);
		 }

		 //
	 }  while(false);

	 return  0;

 }


