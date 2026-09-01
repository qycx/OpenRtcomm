
#include	"stdafx.h"
#include	<stddef.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	"qmcCmdProc.h"

#include	"isCliHelpPublic.h"

 //  2009/12/22
 int  newShmCmdIndex(  MC_VAR_common  *  pProcInfo,  int  iIndex_sharedObj  )
{
	if  (  !pProcInfo  )  return  -1;

	return  pProcInfo->newShmCmdIndex(  iIndex_sharedObj  );

#if  0
	if  (  iIndex_sharedObj  <  0  ||  iIndex_sharedObj  >=  pProcInfo->cmdsShm.usMaxCnt_qmCmds  )  return  -1;
	
#if  1	
	QM_SHM_CMD	*	pShmCmd		=	getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  iIndex_sharedObj  );
	if  (  !pShmCmd  )  return  -1;
	memset(  pShmCmd,  0,  sizeof(  pShmCmd[0]  )  );
#endif

	return  iIndex_sharedObj;
#endif

}





 //  2005/05/01
 int  doCmdBySubProcess(  void  *  p0,  LPCTSTR  cmdStr,  LPCTSTR  cmdParam,  HANDLE  *  phProcess,  DWORD  *  pdwProcessId  )
{
	 int							iErr		=		-1;
	 TCHAR							buf[4096];
	 STARTUPINFO					si;
	 PROCESS_INFORMATION			pi;
	 TCHAR							tmpFileName[MAX_PATH  +  1];

	 if  (  !cmdStr  )  return  -1;

	 memset(  &pi,  0,  sizeof(  pi  )  );
	 memset(  &si,  0,  sizeof(  STARTUPINFO  )  );
	 si.cb  =  sizeof(  STARTUPINFO  );
#ifndef  __WINCE__
	 si.dwFlags  =  STARTF_FORCEOFFFEEDBACK;
#endif

	 GetModuleFileName(  NULL,  tmpFileName,  mycountof(  tmpFileName  )  );
	 if  (  tQyQuoteFileName(  tmpFileName,  mycountof(  tmpFileName  )  )  )  goto  errLabel;

	 _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s %s"  ),  tmpFileName,  cmdStr  );
	 if  (  cmdParam  )  _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s%s"  ),  buf,  cmdParam  );
	 if  (  !CreateProcess(  NULL,  buf,  NULL,  NULL,  0,  0,  NULL,  NULL,  &si,  &pi  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 if  (  pi.hThread  )  {  CloseHandle(  pi.hThread  );  pi.hThread  =  NULL;  }
	 if  (  iErr  )  {
		 if  (  pi.hProcess  )  {  CloseHandle(  pi.hProcess  );  pi.hProcess  =  NULL;  }
	 }

	 if  (  !iErr  )  {
		 if  (  phProcess  )  *phProcess  =  pi.hProcess;
		 else  {  CloseHandle(  pi.hProcess  );  pi.hProcess  =  NULL;  }	//  2005/10/08，增加这一句，以方便在不需要传出句柄时，将句柄清除
		 if  (  pdwProcessId  )  *pdwProcessId  =  pi.dwProcessId;
	 }


	 //  traceLogA(  "doCmdBySubProcess{%s}%s, pid is %d",  buf,  (  iErr  ?  "failed"  :  "ok?  ),  pi.dwProcessId  );  

	 return  iErr;
}
