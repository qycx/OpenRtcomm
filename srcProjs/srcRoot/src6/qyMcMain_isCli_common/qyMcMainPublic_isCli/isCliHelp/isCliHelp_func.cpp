
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"myresource.h"
//  #include	"DlgProgress.h"
#include	"qmcCmdProc.h"


//
#include	"qyComPortEx.h"

int  runShareIc(void* pShareMediaDeviceParam)
{
	return  -1;
}

DWORD WINAPI mcThreadProc_writeShm_dvt( LPVOID lpParameter )
 {
	 return  -1;
 }






#if  0
  int  printImMsgContent_n(  void  *  pSessionParam,  MSG_ROUTE  *  pRoute,  IM_CONTENTU  *  pContent_n,  int  iContentLen,  TCHAR  *  tBuf,  unsigned  int  maxuiBufCnt  )
  {
	  return  -1;
  }
#endif

  int parseGpsStr(  CComPortEx  *  pPort,  char  *  str  )
  {
	  traceLog(  _T(  "not used: parseGpsstr"  )  );
	  return  -1;
  }


   int  getPcStatusInfo(  void  *  pDb,  char  *  mac0,  QY_DMITEM  *  pFieldIdTable,  PC_STATUS_INFO  *  pInfo  )
{
	return  -1;
}

   int  qnmLogOpEvent(  int  iServiceId,  QM_dbFuncs  *  pDbFuncs,  QY_OBJ_DB  *  pObjDb,  int  iEventType,  LPCTSTR  des  )		//  2007/01/02
 {
	 return  -1;
 }
 int  qnmLogOpEvent(  int  iServiceId,  QM_dbFuncs  *  pDbFuncs,  void  *  pDbParam,  int  iDbType,  int  iEventType,  LPCTSTR  usr,  LPCTSTR  dsnName,  LPCTSTR  des  )
 {
	 return  -1;
 }
 int  qnmLogOpEvent(  int  iServiceId,  QM_dbFuncs  *  pDbFuncs,  void  *  pDbParam,  int  iDbType,  int  iEventType,  LPCTSTR  usr,  LPCTSTR  des  )
{
	 return  -1;
 }
 extern  "C"  int  qyGetServiceStatus(						// RETURNS: return code     
						IN LPTSTR  lpszMachineName,          // machine name     
						IN LPTSTR  lpszServiceName,          // service name     
						OUT DWORD  *  lpdwCurrentState  )   // current state 
 {
	 return  -1;
 }


BOOL  bQnmDemo(  )
{
	return  FALSE;
}




