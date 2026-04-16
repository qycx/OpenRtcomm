

#include	"stdafx.h"
#include	<afxdb.h>
#include	<windowsx.h>
#include	<winsock2.h>
#include	<vfw.h>

#include	"qmCommon.h"
#include	"qyDbCommon.h"
#include	"qyTCharCommProc.h"
#include	"myDb.h"

#ifdef  __isCli__
		#include	"qyMcMainCommon.h"
		
		#include	"qmcCommFunc_iscli.h"

#endif





 //  pc 
// int  qnmLogPcEvent(  void  *  pDb,  int  iDbType,  QNM_PC_INFO  *  pPcInfo,  QNM_PC_EVENT  *  pEvent  )
int  qnmLogPcEvent(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QNM_PC_INFO  *  pPcInfo,  QNM_PC_EVENT  *  pEvent  )
{	 
	int							iErr			=  -1;
			
	//
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &g_dbFuncs  =  *pDbFuncs;


	if  (  pEvent->iCustomId  !=  qyGetCustomId(  )  )  {
		traceLogA(  "iCustomId 出现了不一致: qmd's customId is %d, but get the event  pEvent->lEventType %d  from  pEvent->iCustomId  %d",  qyGetCustomId(  ),  pEvent->lEventType,  pEvent->iCustomId  );  
		goto  errLabel;
	}
	if  (  !pEvent->macs[0][0]  )  {
		MACRO_qyAssert(  0,  _T(  "macs[0] must be filled."  )  );  
		goto  errLabel;
	}
	if  (  !pEvent->ip[0]  )  {
		MACRO_qyAssert(  0,  _T(  "ip must be filled."  )  );  
		goto  errLabel;
	}
	if  (  !pEvent->localEventTime[0]  )  {
		MACRO_qyAssert(  0,  _T(  "localEventTime must be filled."  )  );  
		goto  errLabel;
	}

	getCurTime(  pEvent->cntEventTime  );
	
	switch  (  pEvent->lEventType  )  {
					// 新增机器
			case  CONST_qyEventType_nm_newPc:
			  	  safeStrnCpy(  pPcInfo->macs[1],  pEvent->macs[1],  sizeof(  pEvent->macs[1]  )  );
			  	  safeStrnCpy(  pPcInfo->macs[2],  pEvent->macs[2],  sizeof(  pEvent->macs[2]  )  );
			  	  safeStrnCpy(  pPcInfo->ip,  pEvent->ip,  sizeof(  pEvent->ip  )  );
			  	  if  (  !g_dbFuncs.pf_bLogPcEventFunc(  pDb,  iDbType,  pEvent  )  )  goto  errLabel;
				  break;
					// 网卡变更
			case  CONST_qyEventType_nm_macsModified:
			case  CONST_qyEventType_nm_ipChanged:
				  if  (  g_dbFuncs.pf_getPcEventInfoByMac0(  pDb,  pEvent  )  )  goto  errLabel;
				  if  (  !g_dbFuncs.pf_bLogPcEventFunc(  pDb,  iDbType,  pEvent  )  )  goto  errLabel;
				  break;
			case  CONST_qyEventType_nm_macsModifiedPc:
				  goto  errLabel;
			case  CONST_qyEventType_nm_delPc:
				  goto  errLabel;
					// 首次注册
			case  CONST_qyEventType_nm_newReg:
				  if  (  !g_dbFuncs.pf_bLogPcEventFunc(  pDb,  iDbType,  pEvent  )  )  goto  errLabel;
				  break;
					// 重复注册
			case  CONST_qyEventType_nm_reReg:
				  if  (  !g_dbFuncs.pf_bLogPcEventFunc(  pDb,  iDbType,  pEvent  )  )  goto  errLabel;
				  break;
					// 受控端异常
			case  CONST_qyEventType_nm_qwmDel:
			case  CONST_qyEventType_nm_osChanged:
				  goto  errLabel;
					// 拨号、外联
			case  CONST_qyEventType_nm_rasStart:				  
			case  CONST_qyEventType_nm_rasProhibited:
			case  CONST_qyEventType_nm_onInternet:
				  if  (  g_dbFuncs.pf_getPcEventInfoByMac0(  pDb,  pEvent  )  )  goto  errLabel;
				  if  (  !g_dbFuncs.pf_bLogPcEventFunc(  pDb,  iDbType,  pEvent  )  )  goto  errLabel;
				  if  (  !setQnmWarnInfo(  NULL  )  )  goto  errLabel;
				  break;
			case  CONST_qyEventType_nm_rasEnd:
			case  CONST_qyEventType_nm_offInternet:
			case  CONST_qyEventType_nm_proxyServerSet:
			case  CONST_qyEventType_nm_proxyServerClear:
			case  CONST_qyEventType_secChk_recent:
			case  CONST_qyEventType_secChk_cookie:
			case  CONST_qyEventType_secChk_proxyCfg:
			case  CONST_qyEventType_secChk_ieHistory:
			case  CONST_qyEventType_secChk_fileHistory:
			case  CONST_qyEventType_secChk_shareDirectory:
			case  CONST_qyEventType_secChk_sharePrinter:
			case  CONST_qyEventType_secChk_rasPhoneBk:
			case  CONST_qyEventType_secChk_diskFile:
			case  CONST_qyEventType_secChk_diskFileDel:
			default:
				  if  (  g_dbFuncs.pf_getPcEventInfoByMac0(  pDb,  pEvent  )  )  goto  errLabel;
				  if  (  !g_dbFuncs.pf_bLogPcEventFunc(  pDb,  iDbType,  pEvent  )  )  goto  errLabel;
				  break;
	}

	iErr  =  0;

errLabel:

	return  iErr;

}

