

#include	<afxdb.h>
#include	<windowsx.h>
#include	<winsock2.h>
#include	"qyCommonEx.h"
#include	"qyString.h"
#include	"qyDbCommon.h"

#include	"qyPreCustom.h"
#include	"qyCustom.h"

#include	"qyWmComm.h"
#include	"qyCommCommon.h"

#include	"qyLicense.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmCommProc1.h"

#include	"qySnmpCommProc.h"
#include	"qnmsCommProc.h" 
#include	"qyTCharCommProc.h"
#include	"qnmPcComm.h"

#include	"qyDaemonPublic.h"


//  没有写完
 int  qyGetRemoteMacByIp(  char  *  ipBuf,  char  *  macBuf,  unsigned  int  macSize  )  
{
	 return  0;
}


 extern  "C"  int  qnmScanFunc(  void  *  installDirParam,  void  *  pScanStructParam,  void  *  pPcGrpInfoParam  )
{
	 int						iErr			=		-1;
	 TCHAR					*	installDir		=		(  TCHAR  *  )installDirParam;
	 NMS_SCAN_STRUCT		*	pScanStruct		=		(  NMS_SCAN_STRUCT  *  )pScanStructParam;
	 QNM_PCGRP_RCD			*	pPcGrpInfo		=		(  QNM_PCGRP_RCD  *  )pPcGrpInfoParam;
	 TCHAR						cmdBuf[1024];
	 STARTUPINFO				si;
	 PROCESS_INFORMATION		pi;
	 BOOL						bProcessCreated				=		FALSE;
	 DWORD						dwExitCode;
	 	 
	 _sntprintf(  cmdBuf,  mycountof(  cmdBuf  ),  _T(  "%sbin\\%s"  ),  installDir,  _T(  CONST_qyAppName_qySnmpHelp  )  );
	 if  (  tQyQuoteFileName(  cmdBuf,  mycountof(  cmdBuf  )  )  )  goto  errLabel;
	 _sntprintf(  cmdBuf,  mycountof(  cmdBuf  ),  _T(  "%s -d%s -c%d -s%s -e%s"  ),  cmdBuf,  qyGetDesByType1(  CONST_nmsOpTable,  pScanStruct->iNmsOp  ),  pScanStruct->iNmsOpCmd,  CString(  pPcGrpInfo->startIp  ),  CString(  pPcGrpInfo->endIp  )  ); 
 	 
	 memset(  &si,  0,  sizeof(  si  )  );
	 memset(  &pi,  0,  sizeof(  pi  )  );
		 
	 traceLogA(  "Now start %S",  cmdBuf  );
	 memset(  &si,  0,  sizeof(  STARTUPINFO  )  );
 	 si.cb  =  sizeof(  STARTUPINFO  );
 	 si.dwFlags  =  STARTF_FORCEOFFFEEDBACK;
	 
	 
	 if  (  !CreateProcess(  NULL,  cmdBuf,  NULL,  NULL,  0,  0,  NULL,  NULL,  &si,  &pi  )  )  goto  errLabel;
	 bProcessCreated  =  TRUE;
	 traceLogA(  "CreateProcess %s succeeded,  new processId is %d,  new threadId is %d.",  cmdBuf,  pi.dwProcessId,  pi.dwThreadId  );

	 iErr  =  0;

errLabel:

	 if  (  bProcessCreated  )  {

		 ::WaitForSingleObject(  pi.hProcess,  INFINITE  );

		 if  (  GetExitCodeProcess(  pi.hProcess,  &dwExitCode  )  &&  !dwExitCode  )  {
			 traceLogA(  "snmpScanSwitch: 命令完成"  );
		 }
			 
		 
		 if  (  pi.hThread  )  {  CloseHandle(  pi.hThread  );  pi.hThread  =  NULL;  }
		 if  (  pi.hProcess  ) {  CloseHandle(  pi.hProcess  ); pi.hProcess  =  NULL;  }

	 }

	 return  iErr;

}

 
#define		CONST_maxSnmpObjsPerMon			5		
 extern  "C"  DWORD  WINAPI  qnmSnmpNetFlowThreadProc(  LPVOID  lp  )
{
	 NMS_SCAN_STRUCT		*	pScanStruct				=  (  NMS_SCAN_STRUCT  *  )lp;
	 CQyGenericDaemon		*	pDaemon					=  (  CQyGenericDaemon  *  )pScanStruct->pParentParam;
	 CDatabase					db;
	 MT_SUBTHREADINFO			subThreadInfo;
	 long						nInterval				=	5000;
	 CRecordset					rs;
	 char						sqlBuf[CONST_maxSqlBufLen  +  1];
	 CDBVariant					varVals[10];
	 int						nFields,  index;
	 QNM_PCGRP_RCD				pcGrpInfo;
	 char						startIp12[12  +  1]  =  "",  endIp12[12  +  1]  =  "";
	 int						cnt						=	0;
	 WCHAR						wBuf1[256];
	 WCHAR						wBuf2[256];
	 QY_SERVICE_INFO		*	pServiceInfo			=	NULL;
	 char						buf[128];

	 pServiceInfo  =  (  QY_SERVICE_INFO  *  )pDaemon->getSpecialPtrProperty(  CONST_qyPropertyId_serviceInfo_byServiceId,  (  void  *  )CONST_qyServiceId_netMc,  0  );
	 if  (  !pServiceInfo  )  return  -1;
	 	 
	 memset(  &subThreadInfo,  0,  sizeof(  subThreadInfo  )  );
	 //  设置log环境
	 subThreadInfo.pLogCtx  =  pDaemon->getPtrProperty(  CONST_qyPropertyId_logCtx  );	
	 
	 traceInfo(  subThreadInfo.pLogCtx,  "qySnmpNetFlowProc enters"  );
	 	 
	 //  关联全局数据区
	 subThreadInfo.pParentParam  =  pDaemon;

	 
	 //  打开数据库
	 if  (  !bQyOpenDb(  pServiceInfo->cfg.db.connectStr,  &db  )  )  goto  errLabel;
	 subThreadInfo.pDb  =  &db;
	 
	 rs.m_pDatabase  =  &db;
	 
	 for  (  ;  !pDaemon->bQuit(  );  Sleep(  1000  )  )  {
				
		  if  (  pScanStruct->ucbStopScan  )  {  Sleep(  nInterval  );  continue;  }
		  
		  TRY  {

			  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select qySnmpObjTab.ip from qySnmpObjTab,qySnmpObjRuleTab where qySnmpObjRuleTab.iType=%d and qySnmpObjTab.mac=qySnmpObjRuleTab.switchMac",  CONST_ruleType_switch  );
			  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s and qySnmpObjTab.ip>'%s'",  sqlBuf,  startIp12  );
			  if  (  pScanStruct->whereClause[0]  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s and %s",  sqlBuf,  pScanStruct->whereClause  );
			  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s order by qySnmpObjTab.ip",  sqlBuf  );

			  if (  !rs.Open(  CRecordset::forwardOnly,  CString(  sqlBuf  )  )  )  goto  errLabel;

			  nFields  =  rs.GetODBCFieldCount(  );
			  if  (  nFields  >  sizeof(  varVals  ) /  sizeof(  varVals[0]  )  )  goto  errLabel;
			  
			  cnt  =  0;
			  for  (  ;  !pDaemon->bQuit(  )  &&  !rs.IsEOF(  );  rs.MoveNext(  )  )  {

				  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );

				  memset(  &pcGrpInfo,  0,  sizeof(  pcGrpInfo  )  );

				  index  =  0;	//  ip
				  if  (  varVals[index].m_dwType  ==  DBVT_STRING  &&  varVals[index].m_pstring->GetLength(  )  >=  12  )  {
					  myTChar2Str(  varVals[index].m_pstring->GetBuffer(  0  ),  buf,  mycountof(  buf  )  );  qyIp12ToStd(  buf,  pcGrpInfo.endIp  );  
				  }
				  index  ++  ;

				  if  (  !bIpValid(  pcGrpInfo.endIp  )  )  continue;
				  cnt  ++  ;
				  if  (  cnt  >=  CONST_maxSnmpObjsPerMon  )  break;

			  }

			  rs.Close(  );

			  if  (  !cnt  )  {			//  当扫描完毕时，作一停留
				  startIp12[0]  =  0;
				  Sleep(  nInterval  );  				  		  
				  qyShowInfo1(  CONST_qyShowType_addChkingType,  NULL,  NULL,  pScanStruct->showWho,  0,  L"",  L"",  L""  );
				  qyShowInfo1(  CONST_qyShowType_qnmChking,  NULL,  NULL,  pScanStruct->showWho,  0,  L"",  L"",  L"开始一轮监控..."  );
				  continue;
			  }
			  qyIp12ToStd(  startIp12,  pcGrpInfo.startIp  );
			  
			  //  下面将调用qnmSnmpHelp.exe来处理这一网段
			  qyShowInfo1(  CONST_qyShowType_qnmChking,  NULL,  NULL,  pScanStruct->showWho,  0,  L"",  L"",  L"监控%s%s%s的流量",  myStr2WChar(  pcGrpInfo.startIp,  wBuf1,  mycountof(  wBuf1  )  ),  (  pcGrpInfo.startIp[0]  ?  L"-"  :  L""  ),  myStr2WChar(  pcGrpInfo.endIp,  wBuf2,  mycountof(  wBuf2  )  )  );
		  	  if  (  pScanStruct->pf  )  (  (  PF_commonHandler  )pScanStruct->pf  )(  pDaemon->getStrProperty(  CONST_qyPropertyId_installDir  ),  pScanStruct,  &pcGrpInfo  );
			
			  qyStdToIp12(  pcGrpInfo.endIp,  startIp12  );  //  留作下一次扫描的上限
			  

			}
		  CATCH  (  CDBException, e  )  {
			 	 traceLogA(  "DBException caught, [%s]",  e->m_strError  );
				 goto  errLabel;
			 }
		  END_CATCH
 	
	 }
		  
errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );
	if  (  db.IsOpen(  )  )  qyCloseDb(  &db  );

	traceInfo(  subThreadInfo.pLogCtx,  "qnmSnmpNetFlowProc leaves"  );

	return  0;

}


 extern  "C"  DWORD  WINAPI  qnmCommonScanThreadProc(  LPVOID  lp  )
{
	 NMS_SCAN_STRUCT		*	pScanStruct				=  (  NMS_SCAN_STRUCT  *  )lp;
	 CQyGenericDaemon		*	pDaemon					=  (  CQyGenericDaemon  *  )pScanStruct->pParentParam;
	 CDatabase					db;
	 MT_SUBTHREADINFO			subThreadInfo;
	 QY_LOG_CTX					logCtx;
	 CRecordset					rs;
	 CString					sqlBuf;
	 CDBVariant					varVals[10];
	 int						nFields,  index;
	 unsigned  long				ulStartIp  =  0,  ulEndIp  =  0;
	 long						nInterval				=	5000;
	 QNM_PCGRP_RCD				pcGrpInfo;
	 WCHAR						wBuf[256];
	 WCHAR						wBuf1[256];
	 WCHAR						wBuf2[256];
	 WCHAR						wBuf3[256];
	 TCHAR						tBuf[256];
	 char						buf[256];
	 TCHAR				*		pStop;
	 QY_SERVICE_INFO	*		pServiceInfo			=  (  QY_SERVICE_INFO  *  )pDaemon->getSpecialPtrProperty(  CONST_qyPropertyId_serviceInfo_byServiceId,  (  void  *  )CONST_qyServiceId_netMc,  0  );
	 if  (  !pServiceInfo  )  return  -1;
	 	 
	 memset(  &subThreadInfo,  0,  sizeof(  subThreadInfo  )  );

	 //  设置log环境
	 memcpy(  &logCtx,  pDaemon->getPtrProperty(  CONST_qyPropertyId_logCtx  ),  sizeof(  logCtx  )  );	
	 _snprintf(  logCtx.regValName,  sizeof(  logCtx.regValName  ),  "%s : %s",  logCtx.regValName,  pScanStruct->showWho  );
	 subThreadInfo.pLogCtx  =  &logCtx;
		 
	 traceInReg(  subThreadInfo.pLogCtx,  "qnmCommonScanThreadProc enters"  );

	 //  关联全局数据区
	 subThreadInfo.pParentParam  =  pDaemon;
	 //  打开数据库
	 if  (  !bQyOpenDb(  pServiceInfo->cfg.db.connectStr,  &db  )  )  goto  errLabel;
	 subThreadInfo.pDb  =  &db;
	 
	 rs.m_pDatabase  =  &db;

	 sqlBuf  =  CString(  "select startIp,endIp,officeName,subOfficeName,ucbStopSnmpScan,ucbStopMacScan from qnmPcGrpTab"  );
	 if  (  pScanStruct->whereClause[0]  )  sqlBuf  =  sqlBuf  +  " where "  +  pScanStruct->whereClause;

	 for  (  ;  !pDaemon->bQuit(  );  Sleep(  nInterval  )  )  {
				
		  if  (  pScanStruct->ucbStopScan  )  continue;

		  qyShowInfo1(  CONST_qyShowType_qnmChking,  NULL,  NULL,  pScanStruct->showWho,  0,  L"",  L"",  L"开始一轮扫描..."  );
		  
		  TRY  {

			  if (  !rs.Open(  CRecordset::forwardOnly,  sqlBuf  )  )  goto  errLabel;

			  nFields  =  rs.GetODBCFieldCount(  );
			  if  (  nFields  >  sizeof(  varVals  ) /  sizeof(  varVals[0]  )  )  goto  errLabel;

			  for  (  ;  !pDaemon->bQuit(  )  &&  !rs.IsEOF(  );  rs.MoveNext(  )  )  {

				  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );

				  memset(  &pcGrpInfo,  0,  sizeof(  pcGrpInfo  )  );
				  
				  index  =  0;	//  startIp
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
				  if  (  strlen(  buf  )  >=  12  )  {
				  	  qyIp12ToStd(  buf,  pcGrpInfo.startIp  );  
					  ulStartIp  =  inet_addr(  pcGrpInfo.startIp  );
				  }
				  index  ++  ;	//  endIp
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
				  if  (  strlen(  buf  )  >=  12  )  {
					  qyIp12ToStd(  buf,  pcGrpInfo.endIp  );
					  ulEndIp  =  inet_addr(  pcGrpInfo.endIp  );
				  }
				  if  (  ulStartIp  ==  INADDR_NONE  ||  ulEndIp  ==  INADDR_NONE  )  continue;
				  index  ++  ;	//  officeName
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pcGrpInfo.officeName,  sizeof(  pcGrpInfo.officeName  )  );
				  index  ++  ;	//  subOfficeName
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pcGrpInfo.subOfficeName,  sizeof(  pcGrpInfo.subOfficeName  )  );
				  index  ++  ;	//  ucbStopSnmpScan
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  if  (  _tcstol(  tBuf,  &pStop,  10  )  ==  1  )  pcGrpInfo.ucbStopSnmpScan  =  TRUE;
				  index  ++  ;	//  ucbStopMacScan
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  if  (  _tcstol(  tBuf,  &pStop,  10  )  ==  1  )  pcGrpInfo.ucbStopMacScan  =  TRUE;
				  index  ++  ;

				  qyShowInfo1(  CONST_qyShowType_qnmChking,  NULL,  NULL,  L"",  L"",  L"",  L"现在开始扫描",  L" %s %s %s - %s",  myStr2WChar(  pcGrpInfo.officeName,  wBuf,  mycountof(  wBuf  )  ),  myStr2WChar(  pcGrpInfo.subOfficeName,  wBuf1,  mycountof(  wBuf1  )  ),  myStr2WChar(  pcGrpInfo.startIp,  wBuf2,  mycountof(  wBuf2  )  ),  myStr2WChar(  pcGrpInfo.endIp,  wBuf3,  mycountof(  wBuf3  )  )  );
				  Sleep(  2000  );

				  //  下面将调用qnmSnmpHelp.exe来处理这一网段
				  //  if  (  pScanStruct->pf  )  (  (  PF_commonHandler  )pScanStruct->pf  )(  pDaemon,  pScanStruct,  &pcGrpInfo  );
				  //  准备将扫描网段切开，每512台一次
				  {
					  unsigned  long			hulStartIp,  hulEndIp;
					  unsigned  long			ulSegStartIp,  ulSegEndIp;
					  unsigned  long			hulSegStartIp,  hulSegEndIp;
					  QNM_PCGRP_RCD				tmpPcGrpInfo;
					  
					  #define		CONST_qnmsScanSegSize	511

					  hulStartIp  =  ntohl(  ulStartIp  );
					  hulEndIp  =  ntohl(  ulEndIp  );
				  					  
					  traceLogA(  "%s: 开始扫描网段 %s - %s",  pScanStruct->showWho,  pcGrpInfo.startIp,  pcGrpInfo.endIp  );
					  for  (  hulSegStartIp  =  hulStartIp;  hulSegStartIp  <=  hulEndIp;  )  {
						   
						   if  (  pScanStruct->ucbStopScan  )  break;

						   if  (  hulSegStartIp  +  CONST_qnmsScanSegSize  >  hulEndIp  )  hulSegEndIp  =  hulEndIp;
						   else  hulSegEndIp  =  hulSegStartIp  +  CONST_qnmsScanSegSize;

						   memcpy(  &tmpPcGrpInfo,  &pcGrpInfo,  sizeof(  pcGrpInfo  )  );
						   ulSegStartIp  =  htonl(  hulSegStartIp  );
						   ulSegEndIp  =  htonl(  hulSegEndIp  );
						   safeStrnCpy(  inet_ntoa(  *(  in_addr  *  )&ulSegStartIp  ),  tmpPcGrpInfo.startIp,  sizeof(  tmpPcGrpInfo.startIp  )  );
						   safeStrnCpy(  inet_ntoa(  *(  in_addr  *  )&ulSegEndIp  ),  tmpPcGrpInfo.endIp,  sizeof(  tmpPcGrpInfo.endIp  )  );

						   traceLogA(  "%s: 分段 %s - %s",  pScanStruct->showWho,  tmpPcGrpInfo.startIp,  tmpPcGrpInfo.endIp  );
						   //  下面将调用qnmSnmpHelp.exe来处理这一网段
						   if  (  pScanStruct->pf  )  (  (  PF_commonHandler  )pScanStruct->pf  )(  pDaemon->getStrProperty(  CONST_qyPropertyId_installDir  ),  pScanStruct,  &tmpPcGrpInfo  );

						   Sleep(  2000  );			  						   
						   hulSegStartIp  =  hulSegEndIp  +  1;
					  }

				  }
				  
			  }

			  rs.Close(  );

			}
		  CATCH  (  CDBException, e  )  {
			 	 traceLogA(  "DBException caught, [%s]",  e->m_strError  );
				 goto  errLabel;
			 }
		  END_CATCH
 	
		  qyShowInfo1(  CONST_qyShowType_qnmChking,  NULL,  NULL,  pScanStruct->showWho,  0,  L"",  L"",  L"扫描结束"  );
		  
	 }
		  
errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );
	if  (  db.IsOpen(  )  )  qyCloseDb(  &db  );

	traceInReg(  subThreadInfo.pLogCtx,  "qnmCommonScanThreadProc leaves"  );

	return  0;

}



