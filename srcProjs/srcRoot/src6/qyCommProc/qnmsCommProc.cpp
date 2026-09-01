
#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qnmPcComm.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qyLangCommProc.h"
#include	"qySnmpCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmCommProc1.h"
#include	"qnmCustom.h"
#include	"qnmsCommProc.h"
#include	"qnmAssetsCommProc.h"
#include	"qyTCharCommProc.h"


/*
 QY_DMITEM  CONST_ruleTypeTable[]  =
{
	{	CONST_ruleType_switch,		_T(  "设备策略"  ),			},
	{	CONST_ruleType_switchPort,	_T(  "端口策略"  ),			},
	{	-1,							NULL,				},
};
*/


 QY_DMITEM  CONST_portAdminStatusTable[]  =
{
#if  0
	{	CONST_portStatus_up,		(TCHAR*)_T(  "开通"  ),			},
	{	CONST_portStatus_down,		(TCHAR*)_T(  "断开"  ),			},
	{	CONST_portStatus_test,		(TCHAR*)_T(  "管理测试"  ),		},
#endif
	//
	{	-1,							NULL,			},
};

 QY_DMITEM  CONST_portOperStatusTable[]  =
{
#if  0
	{	CONST_portStatus_up,		(TCHAR*)_T(  "连通"  ),		},
	{	CONST_portStatus_down,		(TCHAR*)_T(  "未通"  ),		},
	{	CONST_portStatus_test,		(TCHAR*)_T(  "测试"  ),		},
#endif
	//
	{	-1,							NULL,		},
};

 QY_DMITEM  CONST_iCpsSecureMacAddrTypeTable[]  =
{
#if  0
	{	1,							(TCHAR*)_T(  "静态绑定"  ),		},
	{	2,							(TCHAR*)_T(  "动态绑定"  ),		},
#endif
	{	-1,							NULL,			},
};


 QY_DMITEM  CONST_iCpsIfViolationActionTable[]  =  
{
#if  0
	{	1,							(TCHAR*)_T(  "断开"  ),			},
	{	2,							(TCHAR*)_T(  "丢包并报警"  ),	},
	{	3,							(TCHAR*)_T(  "丢包"  ),			},
#endif
	{	-1,							NULL,			},
};

 QY_DMITEM  CONST_iCpsIfPortSecurityStatusTable[]  =
{
#if  0
	{	1,							(TCHAR*)_T(  "绑定启用"  ),		},
	{	2,							(TCHAR*)_T(  "绑定失效"  ),		},
	{	3,							(TCHAR*)_T(  "绑定断开"  ),		},
#endif
	{	-1,							(TCHAR*)_T(  ""  ),				},
};


 QY_DMITEM	CONST_pcEnvTypeTable[]  =
{
#if 0
 	{	CONST_pcEnvType_hardware,				(TCHAR*)_T(  "硬件"  ),								},
 	{	CONST_pcEnvType_software,				(TCHAR*)_T(  "软件"  ),								},
	{	CONST_pcEnvType_registry,				(TCHAR*)_T(  "注册表"  ),							},
#endif
	//
	{	-1,										NULL,								},
};



 int  setScanStruct(  int  iNmsOp1,  int  iNmsOpCmd1,  void  *  pfThreadProc1,  void  *  pf1,  void  *  pDaemon1,  NMS_SCAN_STRUCT  *  pScanStruct  )
{
	 int							iErr		=	-1;

	 pScanStruct->iNmsOp		=  (  iNmsOp1  );																					
	 pScanStruct->iNmsOpCmd		=  (  iNmsOpCmd1  );																				
	 pScanStruct->pfThreadProc	=  (  pfThreadProc1  );																				
	 pScanStruct->pf			=  (  pf1  );																						
	 pScanStruct->pParentParam	=  (  pDaemon1  );																					
																																	
	 switch  (  iNmsOp1  )  {																										
			 case  CONST_nmsOp_snmpScan:																							
                   switch  (  iNmsOpCmd1  )  {																						
						   case  CONST_snmpOpCmd_monFlow:
							     lstrcpyn(  pScanStruct->showWho,  CONST_showWho_snmpNetFlow,  mycountof(  pScanStruct->showWho  )  );				
				   				 pScanStruct->pRegValName  = (TCHAR*)_T(  CONST_regValName_stopSnmpNetFlow  );
			       				 break;																											
						   default:
								   lstrcpyn(  pScanStruct->showWho,  CONST_showWho_snmpScan,  mycountof(  pScanStruct->showWho  )  );					
				   				   pScanStruct->pRegValName  = (TCHAR*)_T(  CONST_regValName_stopSnmpScan  );
				   				   _snprintf(  pScanStruct->whereClause,  sizeof(  pScanStruct->whereClause  ),											
											   " (ucbStopSnmpScan<>'1' or ucbStopSnmpScan is null) "  );												
								   break;																											
				   }
				   break;
			 case  CONST_nmsOp_nbtScan:																								
				   lstrcpyn(  pScanStruct->showWho,  CONST_showWho_nbtScan,  mycountof(  pScanStruct->showWho  )  );					
				   pScanStruct->pRegValName  = (TCHAR*)_T(  CONST_regValName_stopNbtScan  );
				   _snprintf(  pScanStruct->whereClause,  sizeof(  pScanStruct->whereClause  ),											
							   " (ucbStopMacScan<>'1' or ucbStopMacScan is null) "  );												
				   break;																											
			 default:																												
					goto  errLabel;																											
																																	
	 }

	 iErr  =  0;

errLabel:
	 return  iErr;
}


#if  0
 BOOL  bGetDefSnmpPolicy(  void  *  p0,  void  *  pEncCtx,  QY_SNMPOBJPOLICY_RCD  *  pPolicy  )
{
	QY_REG		reg;

	memset(  pPolicy,  0,  sizeof(  pPolicy[0]  )  );
	_snprintf(  pPolicy->snmpVer,  sizeof(  pPolicy->snmpVer  ),  CONST_defSnmpVer  );
	
	memset(  &reg,  0,  sizeof(  reg  )  );
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  _T(  CONST_qyRootKey_qnmScheduler  )  );
	reg.pEncCtx  =  pEncCtx;
	if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_communityRo  ),  pPolicy->getCommunity,  sizeof(  pPolicy->getCommunity  )  )  )  pPolicy->getCommunity[0]  =  0;
	if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_communityRw  ),  pPolicy->setCommunity,  sizeof(  pPolicy->setCommunity  )  )  )  pPolicy->setCommunity[0]  =  0;
	trim(  pPolicy->snmpVer  );
	trim(  pPolicy->getCommunity  );
	trim(  pPolicy->setCommunity  );

	if  (  !pPolicy->getCommunity[0]  )  _snprintf(  pPolicy->getCommunity,  sizeof(  pPolicy->getCommunity  ),  CONST_defCommunityRo  );
	if  (  !pPolicy->setCommunity[0]  )  _snprintf(  pPolicy->setCommunity,  sizeof(  pPolicy->setCommunity  ),  CONST_defCommunityRw  );
	

	return  TRUE;
}
#endif

 //  2011/01/19
  BOOL  bGetDefSnmpPolicy(  void  *  p0,  void  *  pEncCtx,  QY_SNMPOBJPOLICY_RCD  *  pPolicy  )
{
	QY_REG		reg;
	TCHAR		tBuf[256];

	memset(  pPolicy,  0,  sizeof(  pPolicy[0]  )  );
	_snprintf(  pPolicy->snmpVer,  sizeof(  pPolicy->snmpVer  ),  CONST_defSnmpVer  );
	
	memset(  &reg,  0,  sizeof(  reg  )  );
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  _T(  CONST_qyRootKey_qnmScheduler  )  );
	reg.pEncCtx  =  pEncCtx;
	if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_communityRo  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  tBuf[0]  =  0;
	myTChar2Utf8(  tBuf,  pPolicy->getCommunity,  sizeof(  pPolicy->getCommunity  )  );
	if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_communityRw  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  tBuf[0]  =  0;
	myTChar2Utf8(  tBuf,  pPolicy->setCommunity,  sizeof(  pPolicy->setCommunity  )  );
	trim(  pPolicy->snmpVer  );
	trim(  pPolicy->getCommunity  );
	trim(  pPolicy->setCommunity  );

	if  (  !pPolicy->getCommunity[0]  )  _snprintf(  pPolicy->getCommunity,  sizeof(  pPolicy->getCommunity  ),  CONST_defCommunityRo  );
	if  (  !pPolicy->setCommunity[0]  )  _snprintf(  pPolicy->setCommunity,  sizeof(  pPolicy->setCommunity  ),  CONST_defCommunityRw  );
	

	return  TRUE;
}


 BOOL  bSetDefSnmpPolicy(  void  *  p0,  void  *  pEncCtx,  QY_SNMPOBJPOLICY_RCD  *  pPolicy  )
{
	QY_REG		reg;
	TCHAR		tBuf[256];

	trim(  pPolicy->snmpVer  );
	trim(  pPolicy->getCommunity  );
	trim(  pPolicy->setCommunity  );

	if  (  !pPolicy->getCommunity[0]  )  _snprintf(  pPolicy->getCommunity,  sizeof(  pPolicy->getCommunity  ),  CONST_defCommunityRo  );
	if  (  !pPolicy->setCommunity[0]  )  _snprintf(  pPolicy->setCommunity,  sizeof(  pPolicy->setCommunity  ),  CONST_defCommunityRw  );

	memset(  &reg,  0,  sizeof(  reg  )  );
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  _T(  CONST_qyRootKey_qnmScheduler  )  );
	reg.pEncCtx  =  pEncCtx;

	if  (  !_stricmp(  pPolicy->getCommunity,  CONST_defCommunityRo  )  )  qyDelRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_communityRo  )  );
	else  {
		  myStr2TChar(  pPolicy->getCommunity,  tBuf,  mycountof(  tBuf  )  );
		  qySetRegCfgEx(  &reg,  _T(  CONST_regValName_communityRo  ),  tBuf  );
	}
	if  (  !_stricmp(  pPolicy->setCommunity,  CONST_defCommunityRw  )  )  qyDelRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_communityRw  )  );
	else  {
		  myStr2TChar(  pPolicy->setCommunity,  tBuf,  mycountof(  tBuf  )  );
		  qySetRegCfgEx(  &reg,  _T(  CONST_regValName_communityRw  ),  tBuf  );
	}

	 return  TRUE;
}

