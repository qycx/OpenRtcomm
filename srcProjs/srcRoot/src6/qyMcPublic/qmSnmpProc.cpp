

#include	<afxdb.h>
#include	<windowsx.h>
#include	<winsock2.h>
#include	<vfw.h>

#include	"qmCommon.h"
#include	"qyDbCommon.h"
#include	"qySnmpCommProc.h"
#include	"qmSnmpProc.h"

#include	"qyCusResPublic.h"
#include	"qyCusResTemp.h"
#include	"myDb.h"
#include	"pcCommType_defs.h"


//  注意：QY_SNMP_OBJ不仅是数据库记录
//  当switchMac有效时，通过switchMac取switch信息
//  当switchMac无效时，通过switchIp取switch信息
 BOOL  bGetSnmpObjHeadInfoBySth(  void  *  pDbParam,  char  *  switchMac,  char  *  switchIp,  QY_SNMPOBJ_HEAD  *  pObj  )
{
	 BOOL			bRet			=	FALSE;
	 char			sqlBuf[1024];
	 CDBVariant		varVals[40];
	 int			index;
	 char			ip12[12  +  1];
	 int			iType;
	 TCHAR		*	pStopString;
	 TCHAR			tBuf[1024];
	 
	 if  (  !pDbParam  )  goto  errLabel;
	 _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select iIpForwarding,ucbBridge,ucbHost,sysDescr,iMaker,maker,productName,lNetDevType,ip,mac,dot1dBaseNumPorts,iManagementDomainLocalMode,iCpsGlobalMaxSecureAddress,iCpsGlobalTotalSecureAddress,iCpsGlobalPortSecurityEnable,lStatus,cusName,place,firstTime,lastTime,auditTime from qySnmpObjTab"  );
	 if  (  bMacValid(  switchMac  )  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s where mac='%s'",  sqlBuf,  switchMac  );
	 else  if  (  !switchIp  ||  !bulIpValid(  inet_addr(  switchIp  )  )  )  goto  errLabel;
	 else  {  
			qyStdToIp12(  switchIp,  ip12  );  
	 		_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s where ip='%s'",  sqlBuf,  ip12  );
	 }
		 
	 //  traceLogA(  "sqlBuf is %s",  sqlBuf  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  CString(  sqlBuf  ).GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;
	 
	 //  清空snmpObj中属于数据库记录的字段，保留其他的相关信息
	 iType  =  pObj->iType;
	 memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	 pObj->iType  =  iType;

	 index  =  0;	//  iIpForwarding
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  pObj->iIpForwarding  =  _tcstol(  tBuf,  &pStopString,  10  );    
	 index  ++  ;	//  ucbBridge
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  pObj->ucbBridge  =  (  unsigned  char  )_tcstol(  tBuf,  &pStopString,  10  );    
	 index  ++  ;	//  ucbHost
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  pObj->ucbHost  =  (  unsigned  char  )_tcstol(  tBuf,  &pStopString,  10  );    
	 index  ++  ;	//  sysDescr	 
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pObj->sysDescr,  tBuf,  mycountof(  pObj->sysDescr  )  );    
	 index  ++  ;	//  iMaker,
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  pObj->iMaker  =  _tcstol(  tBuf,  &pStopString,  10  );    
	 index  ++  ;	//  maker,
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pObj->maker,  tBuf,  mycountof(  pObj->maker  )  );    
	 index  ++  ;	//  productName,
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pObj->productName,  tBuf,  mycountof(  pObj->productName  )  );    
	 index  ++  ;	//  lNetDevType,
	 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pObj->lNetDevType  =  varVals[index].m_lVal;    }
	 index  ++  ;	//  ip,
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  pObj->ip  );    
	 index  ++  ;	//  mac,
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pObj->mac,  sizeof(  pObj->mac  )  );    
	 index  ++  ;	//  dot1dBaseNumPorts
	 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pObj->uiIfNumber  =  varVals[index].m_lVal;    }
	 index  ++  ;	//  managementDomainLocalMode
	 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pObj->iManagementDomainLocalMode  =  varVals[index].m_lVal;  }
	 index  ++  ;	//  iCpsGlobalMaxSecureAddress
	 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pObj->iCpsGlobalMaxSecureAddress  =  varVals[index].m_lVal;  }
	 index  ++  ;	//  iCpsGlobalTotalSecureAddress		
	 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pObj->iCpsGlobalTotalSecureAddress  =  varVals[index].m_lVal;  }
	 index  ++  ;	//  "iCpsGlobalPortSecurityEnable		
	 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pObj->ucbCpsGlobalPortSecurityEnable  =  (  (  varVals[index].m_lVal  ==  1  )  ?  TRUE  :  FALSE  );  }
	 index  ++  ;	//  lStatus
	 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pObj->lStatus  =  varVals[index].m_lVal;    }
	 index  ++  ;	//  cusName
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pObj->cusName,  tBuf,  mycountof(  pObj->cusName  )  );    
	 index  ++  ;	//  place
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pObj->place,  tBuf,  mycountof(  pObj->place  )  );    
	 index  ++  ;	//  firstTime
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pObj->firstTime,  sizeof(  pObj->firstTime  )  );    
	 index  ++  ;	//  lastTime
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pObj->lastTime,  sizeof(  pObj->lastTime  )  );    
	 index  ++  ;	//  auditTime
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pObj->auditTime,  sizeof(  pObj->auditTime  )  );    
	 index  ++  ;	
	 
	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


//  可根据iPortIfIndex查询portInfo
//  或根据iBridgePort查询portInfo,  此时iPortIfIndex输入-1
//  或根据connectedMac查询portInfo, 此时iPortIfIndex输入-1, iBridgePort输入-1,  该功能暂时失效，要求输入NULL
 BOOL  bGetPortInfoBySth(  void  *  pDbParam,  char  *  switchMac,  
							int  iPortIfIndex,  int  iBridgePort,  char  *  connectedMac,
							QY_SWITCHPORT_RCD  *  pPortInfo,  QY_SWITCHIFPORTSECURITY_RCD  *  pPortSecurityInfo  )
{
	 BOOL				bRet		=		FALSE;
	 char				sqlBuf[2048];
	 CDBVariant			varVals[40];
	 int				index		=		0;
	 TCHAR			*	pStopString;
	 TCHAR				tBuf[1024];

	 if  (  !pDbParam  ||  !bMacValid(  switchMac  )  )  goto  errLabel;
	 MACRO_qyAssert(  !connectedMac,  _T(  "bGetPortInfoBySth: 暂时不允许通过mac来直接查询qySwitchPortTab"  )  );
														//				0							1							2							3								4								5									6							7						8							9
	 _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select qySwitchPortTab.portIfIndex,qySwitchPortTab.portIfDescr,qySwitchPortTab.portIfType,qySwitchPortTab.portIfPhysAddress,qySwitchPortTab.portIfAdminStatus,qySwitchPortTab.portIfOperStatus,qySwitchPortTab.bridgePort,qySwitchPortTab.vlanId,qySwitchPortTab.iVmVlanType,qySwitchPortTab.comment0"
													",qySwitchIfPortSecurityTab.portIfIndex"				
													",qySwitchIfPortSecurityTab.iCpsIfPortSecurityEnable"	//  true(1), false(2)
													",qySwitchIfPortSecurityTab.iCpsIfPortSecurityStatus"
													",qySwitchIfPortSecurityTab.iCpsIfMaxSecureMacAddr"
													",qySwitchIfPortSecurityTab.iCpsIfCurrentSecureMacAddrCount"
													",qySwitchIfPortSecurityTab.iCpsIfViolationAction"
													",qySwitchIfPortSecurityTab.lastTime"
				" from qySwitchPortTab left join qySwitchIfPortSecurityTab on (qySwitchPortTab.switchMac=qySwitchIfPortSecurityTab.switchMac and qySwitchPortTab.portIfIndex=qySwitchIfPortSecurityTab.portIfIndex) where qySwitchPortTab.switchMac='%s'",  switchMac  );
	 if  (  iPortIfIndex  >=  0  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s and qySwitchPortTab.portIfIndex=%d",  sqlBuf,  iPortIfIndex  );
	 else  if  (  iBridgePort  >=  0  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s and qySwitchPortTab.bridgePort=%d",  sqlBuf,  iBridgePort  );
	 else  goto  errLabel;

	 if  (  !bQyGetRcdBySql(  pDbParam,  CString(  sqlBuf  ).GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;

	 index  =  0;

	 if  (  !pPortInfo  )  index  +=  10;
	 else  {

		   //  复位
	 	   memset(  pPortInfo,  0,  sizeof(  pPortInfo[0]  )  );
	 	   safeStrnCpy(  switchMac,  pPortInfo->switchMac,  sizeof(  pPortInfo->switchMac  )  );  
	 	   pPortInfo->iPortIfIndex  =  -1;
	 	   pPortInfo->iPortIfAdminStatus  =	-1;
	 	   pPortInfo->iPortIfOperStatus	=   -1;
	 	   pPortInfo->iBridgePort			=	-1;
	 
						 //  portIfIndex
		   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pPortInfo->iPortIfIndex  =  varVals[index].m_lVal;    }
		   index  ++  ;  //  portIfDescr
		   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPortInfo->portIfDescr,  sizeof(  pPortInfo->portIfDescr  )  );    
		   index  ++  ;  //  portIfType
		   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pPortInfo->iPortIfType  =  varVals[index].m_lVal;  }
		   index  ++  ;  //  portIfPhysAddress
		   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPortInfo->portIfPhysAddress,  sizeof(  pPortInfo->portIfPhysAddress  )  );    
		   index  ++  ;  //  portIfAdminStatus
		   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  pPortInfo->iPortIfAdminStatus  =  _tcstol(  tBuf,  &pStopString,  10  );    
		   index  ++  ;  //  portIfOperStatus
		   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  pPortInfo->iPortIfOperStatus  =  _tcstol(  tBuf,  &pStopString,  10  );    
		   index  ++  ;  //  bridgePort,
		   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pPortInfo->iBridgePort  =  varVals[index].m_lVal;    }
		   index  ++  ;  //  vlanId		
		   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pPortInfo->lVlanId  =  varVals[index].m_lVal;    }
		   index  ++  ;  //  iVmVlanType
		   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pPortInfo->iVmVlanType  =  varVals[index].m_lVal;  }
		   index  ++  ;
		   //  //  comment0
		   //  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  safeStrnCpy(  tBuf,  pPortInfo->comment,  sizeof(  pPortInfo->comment  )  );    }
		   index  ++  ;			
		   
	 }

	 if  (  index  !=  10  )  {
		 //MACRO_qyAssert(  0,  _T(  "bGetPortInfoBySth 的取值顺序错误。"  )  );  
		 goto  errLabel;
	 }

	 if  (  pPortSecurityInfo  )  {
		 memset(  pPortSecurityInfo,  0,  sizeof(  pPortSecurityInfo[0]  )  );
		 safeStrnCpy(  switchMac,  pPortSecurityInfo->switchMac,  sizeof(  pPortSecurityInfo->switchMac  )  );  
		 pPortSecurityInfo->iPortIfIndex  =  -1;

					   //  portIfIndex
		 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pPortSecurityInfo->iPortIfIndex  =  varVals[index].m_lVal;    }
		 index  ++  ;  //  qySwitchIfPortSecurityTab.iCpsIfPortSecurityEnable"	//  true(1), false(2)
		 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pPortSecurityInfo->ucbCpsIfPortSecurityEnable  =  (  (  varVals[index].m_lVal  ==  1  )  ?  TRUE  :  FALSE  );  }
		 index  ++  ;  //  qySwitchIfPortSecurityTab.iCpsIfPortSecurityStatus
		 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pPortSecurityInfo->iCpsIfPortSecurityStatus  =  varVals[index].m_lVal;  }
		 index  ++  ;  //  qySwitchIfPortSecurityTab.iCpsIfMaxSecureMacAddr
		 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pPortSecurityInfo->iCpsIfMaxSecureMacAddr  =  varVals[index].m_lVal;  }
		 index  ++  ;  //  qySwitchIfPortSecurityTab.iCpsIfCurrentSecureMacAddrCount
		 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pPortSecurityInfo->iCpsIfCurrentSecureMacAddrCount  =  varVals[index].m_lVal;  }
		 index  ++  ;  //  qySwitchIfPortSecurityTab.iCpsIfViolationAction
		 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pPortSecurityInfo->iCpsIfViolationAction  =  varVals[index].m_lVal;  }
		 index  ++  ;  //  qySwitchIfPortSecurityTab.lastTime		 
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPortSecurityInfo->lastTime,  sizeof(  pPortSecurityInfo->lastTime  )  );  
		 index  ++  ;
			 
	 }
				
	 
	 bRet  =  TRUE;
	 
errLabel:

	 return  bRet;
}


 QY_SWITCHPORT_RCD  *  getPortInSwitch(  QY_SNMP_OBJ  *  pSwitch,  int  iPortIfIndex  )
{
	 for  (  unsigned  int  i  =  0;  i  <  pSwitch->uiIfNumber;  i  ++  )  {
		  if  (  pSwitch->ports[i].iPortIfIndex  ==  iPortIfIndex  )  return  &pSwitch->ports[i];
	 }
	 return  NULL;
}

 BOOL  bGetConnectedDevInfoBySth(  void  *  pDbParam,  char  *  switchMac,  int  iPortIfIndex,  long  unused_lDeviceIndex,  QY_SWITCHCONNECTEDDEV_RCD  *  pDevInfo  )
{
	 BOOL				bRet		=		FALSE;
	 char				sqlBuf[2048];
	 CDBVariant			varVals[20];
	 int				index		=		0;
	 char				ip12[12  +  1];
	 TCHAR				tBuf[1024];

	 if  (  !pDbParam  ||  !bMacValid(  switchMac  )  ||  !pDevInfo  )  goto  errLabel;
	 _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select portIfIndex,deviceIndex,addressType,address,version,devicePortDescr,platform,comment0"
				" from qySwitchConnectedDevTab where switchMac='%s' and portIfIndex=%d",  switchMac,  iPortIfIndex  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  CString(  sqlBuf  ).GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;
	 
	 //  复位
	 memset(  pDevInfo,  0,  sizeof(  pDevInfo[0]  )  );
	 safeStrnCpy(  switchMac,  pDevInfo->switchMac,  sizeof(  pDevInfo->switchMac  )  );  
	 pDevInfo->iPortIfIndex  =  iPortIfIndex;
	 
	 //  address,version,devicePortDescr,platform,comment0"

	 index  =  0;  //  portIfIndex
	 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pDevInfo->iPortIfIndex  =  varVals[index].m_lVal;    }
	 index  ++  ;  //  deviceIndex
	 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pDevInfo->lDeviceIndex  =  varVals[index].m_lVal;    }
	 index  ++  ;  //  addressType
	 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pDevInfo->lAddressType  =  varVals[index].m_lVal;    }
	 index  ++  ;  //  address
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pDevInfo->address,  sizeof(  pDevInfo->address  )  );    
	 index  ++  ;  //  version
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pDevInfo->version,  sizeof(  pDevInfo->version  )  );    
	 index  ++  ;  //  devicePortDescr
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pDevInfo->devicePortDescr,  sizeof(  pDevInfo->devicePortDescr  )  );    
	 index  ++  ;  //  platform
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pDevInfo->platform,  sizeof(  pDevInfo->platform  )  );    
	 index  ++  ;  //  comment0
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pDevInfo->comment,  sizeof(  pDevInfo->comment  )  );    
	 index  ++  ;			
	 
	 if  (  pDevInfo->lAddressType  ==  CONST_ciscoNetworkProtocolType_ip  )  {  safeStrnCpy(  pDevInfo->address,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  pDevInfo->address  );  }

	 bRet  =  TRUE;
	 
errLabel:

	 return  bRet;

}


 //  一般用switchMac,connectedMac作为索引查询pcInfo
 //  对路由器，由于只能使用ip，故将connectedMac为NULL时，可以使用switchMac,connectedIp作为索引
 BOOL  bGetConnectedPcInfoBySth(  void  *  pDbParam,  char  *  switchMac,  char  *  connectedMac,  char  *  connectedIp,  QY_SWITCHCONNECTEDPC_RCD  *  pConnectedPcInfo  ,  QY_SWITCHSECUREMAC_RCD  *  pSecureMacInfo  )
{
	 BOOL				bRet		=		FALSE;
	 char				sqlBuf[2048];
	 CDBVariant			varVals[40];
	 int				index		=		0;
	 char				ip12[12  +  1];
	 TCHAR			*	pStopString;
	 TCHAR				tBuf[1024];

	 if  (  !pDbParam  ||  !bMacValid(  switchMac  )  )  goto  errLabel;
														//						0									1								2									3								4								5									6								7	
	 _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select qySwitchConnectedPcTab.connectedMac,qySwitchConnectedPcTab.connectedIp,qySwitchConnectedPcTab.portIfIndex,qySwitchConnectedPcTab.firstTime,qySwitchConnectedPcTab.lastTime,qySwitchConnectedPcTab.auditTime,qySwitchConnectedPcTab.ucbDirectConn,qySwitchConnectedPcTab.comment0"
												" ,qySwitchSecureMacTab.secureMac,qySwitchSecureMacTab.portIfIndex, qySwitchSecureMacTab.iCpsSecureMacAddrType, qySwitchSecureMacTab.iCpsSecureMacAddrRowStatus, qySwitchSecureMacTab.lastTime"
				" from qySwitchConnectedPcTab left join qySwitchSecureMacTab on (qySwitchSecureMactab.switchMac=qySwitchConnectedPcTab.switchMac and qySwitchSecureMacTab.portIfIndex=qySwitchConnectedPcTab.portIfIndex and qySwitchSecureMacTab.secureMac=qySwitchConnectedPcTab.connectedMac ) where qySwitchConnectedPcTab.switchMac='%s'",  switchMac  );
	 if  (  bMacValid(  connectedMac  )  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s and qySwitchConnectedPcTab.connectedMac='%s'",  sqlBuf,  connectedMac  );
	 else  if  (  bulIpValid(  inet_addr(  connectedIp  )  )  )  {
				qyStdToIp12(  connectedIp,  ip12  );
				_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s and qySwitchConnectedPcTab.connectedIp='%s'",  sqlBuf,  ip12  );
			}
	 else  goto  errLabel;

	 if  (  !bQyGetRcdBySql(  pDbParam,  CString(  sqlBuf  ).GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;
	 
	 index  =  0;

	 if  (  !pConnectedPcInfo  )  index  +=  8;
	 else  {

		   //  复位
	 	   memset(  pConnectedPcInfo,  0,  sizeof(  pConnectedPcInfo[0]  )  );
	 	   safeStrnCpy(  switchMac,  pConnectedPcInfo->switchMac,  sizeof(  pConnectedPcInfo->switchMac  )  );
	 	 	 
				//  connectedMac
		   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pConnectedPcInfo->connectedMac,  sizeof(  pConnectedPcInfo->connectedMac  )  );  
	 	   index  ++  ;	//  connectedIp
		   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  pConnectedPcInfo->connectedIp  );    
	 	   index  ++  ;	//  portIfIndex
	 	   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pConnectedPcInfo->iPortIfIndex  =  varVals[index].m_lVal;    }
	 	   index  ++  ;	//  firstTime
		   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pConnectedPcInfo->firstTime,  sizeof(  pConnectedPcInfo->firstTime  )  );    
	 	   index  ++  ;	//  lastTime
		   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pConnectedPcInfo->lastTime,  sizeof(  pConnectedPcInfo->lastTime  )  );    
	 	   index  ++  ;	//  auditTime
		   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pConnectedPcInfo->auditTime,  sizeof(  pConnectedPcInfo->auditTime  )  );    
	 	   index  ++  ;	//  ucbDirectConn
		   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  pConnectedPcInfo->ucbDirectConn  =  _tcstol(  tBuf,  &pStopString,  10  )  ?  TRUE  :  FALSE;    
	 	   index  ++  ;	//  comment0
		   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pConnectedPcInfo->comment,  sizeof(  pConnectedPcInfo->comment  )  );    
	 	   index  ++  ;			
	 
	 	   //  修正mac显示
	 	   _strlwr(  pConnectedPcInfo->connectedMac  );
		   
	 }

	 if  (  index  !=  8  )  {
		 //MACRO_qyAssert(  0,  _T(  "bGetConnectedPcInfoBySth 取值顺序错误"  )  );  
		 goto  errLabel;
	 }

	 if  (  pSecureMacInfo  )  {
		 memset(  pSecureMacInfo,  0,  sizeof(  pSecureMacInfo[0]  )  );
		 safeStrnCpy(  switchMac,  pSecureMacInfo->switchMac,  sizeof(  pSecureMacInfo->switchMac  )  );

						//  qySwitchSecureMacTab.secureMac
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pSecureMacInfo->secureMac,  sizeof(  pSecureMacInfo->secureMac  )  );  
		 index  ++  ;	//  qySwitchSecureMacTab.iPortIfIndex
	 	 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {   pSecureMacInfo->iPortIfIndex  =  varVals[index].m_lVal;  }
		 index  ++  ;  //  iCpsSecureMacAddrType
		 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pSecureMacInfo->iCpsSecureMacAddrType  =  varVals[index].m_lVal;  }
		 index  ++  ;  //  iCpsSecureMacAddrRowStatus
		 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pSecureMacInfo->iCpsSecureMacAddrRowStatus  =  varVals[index].m_lVal;  }
		 index  ++  ;	//  qySwitchSecureMacTab.lastTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pSecureMacInfo->lastTime,  sizeof(  pSecureMacInfo->lastTime  )  );  
		 index  ++  ;
	 }

	 bRet  =  TRUE;
	 
errLabel:

	 return  bRet;
}


 /*
 BOOL  bGetSecureMacInfoBySth(  void  *  pDb,  char  *  switchMac,  char  *  secureMac,  QY_SWITCHSECUREMAC_RCD  *  pSecureMacInfo  )
{
	 BOOL				bRet				=	FALSE;
	 char				sqlBuf[1024];
	 CDBVariant			varVals[10];
	 int				index			=		0;

	 if  (  !bMacValid(  switchMac  )  ||  !bMacValid(  secureMac  )  )  goto  errLabel;

	 _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select qySwitchSecureMacTab.portIfIndex, qySwitchSecureMacTab.iCpsSecureMacAddrType, qySwitchSecureMacTab.iCpsSecureMacAddrRowStatus, qySwitchSecureMacTab.lastTime from qySwitchSecureMacTab where qySwitchSecureMacTab.switchMac='%s' and qySwitchSecureMacTab.secureMac='%s'",  switchMac,  secureMac  );
	 if  (  !bQyGetRcdBySql(  pDb,  sqlBuf,  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;

	 if  (  pSecureMacInfo  )  {
		 memset(  pSecureMacInfo,  0,  sizeof(  pSecureMacInfo[0]  )  );
		 safeStrnCpy(  switchMac,  pSecureMacInfo->switchMac,  sizeof(  pSecureMacInfo->switchMac  )  );
		 safeStrnCpy(  secureMac,  pSecureMacInfo->secureMac,  sizeof(  pSecureMacInfo->secureMac  )  );
		 				//  qySwitchSecureMacTab.iPortIfIndex
	 	 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {   pSecureMacInfo->iPortIfIndex  =  varVals[index].m_lVal;  }
		 index  ++  ;  //  iCpsSecureMacAddrType
		 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pSecureMacInfo->iCpsSecureMacAddrType  =  varVals[index].m_lVal;  }
		 index  ++  ;  //  iCpsSecureMacAddrRowStatus
		 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pSecureMacInfo->iCpsSecureMacAddrRowStatus  =  varVals[index].m_lVal;  }
		 index  ++  ;	//  qySwitchSecureMacTab.lastTime
		 if  (  varVals[index].m_dwType  ==  DBVT_STRING  )  {  MACRO_CStringTrim(  *varVals[index].m_pstring  );  safeStrnCpy(  varVals[index].m_pstring->GetBuffer(  0  ),  pSecureMacInfo->lastTime,  sizeof(  pSecureMacInfo->lastTime  )  );  }
		 index  ++  ;
	 }

	 bRet  =  TRUE;

errLabel:

	 return  bRet;
	 
}
*/

 BOOL  bGetSnmpObjPolicyBySth(  void  *  pDb,  char  *  switchIp,  QY_SNMPOBJPOLICY_RCD  *  pPolicy  )
{
	 BOOL				bRet				=	FALSE;
	 char				sqlBuf[1024  +  1];
	 char				ip12[12  +  1];
	 CDBVariant			varVals[30];
	 int				index;
	 TCHAR				tBuf[1024];

	 if  (  !qyStdToIp12(  switchIp,  ip12  )  )  goto  errLabel;
	 _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select qySnmpObjPolicyTab.ip,qySnmpObjPolicyTab.cusName,qySnmpObjPolicyTab.grpName,qySnmpPolicyGrpTab.snmpVer,qySnmpPolicyGrpTab.getCommunity,qySnmpPolicyGrpTab.setCommunity,qySnmpPolicyGrpTab.usmName,qySnmpPolicyGrpTab.securityLevel,qySnmpPolicyGrpTab.authMethod,qySnmpPolicyGrpTab.authStr,qySnmpPolicyGrpTab.privMethod,qySnmpPolicyGrpTab.privStr,qySnmpPolicyGrpTab.engineId from qySnmpObjPolicyTab left join qySnmpPolicyGrpTab on qysnmpObjPolicyTab.grpName=qySnmpPolicyGrptab.name where qySnmpObjPolicyTab.ip='%s'",  ip12  );
	 if  (  !bQyGetRcdBySql(  pDb,  CString(  sqlBuf  ).GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;

	 index  =  0;		//  qySnmpObjPolicyTab.ip
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  pPolicy->ip  );  
	 index  ++  ;		//  qySnmpObjPolicyTab.cusName
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pPolicy->cusName,  tBuf,  mycountof(  pPolicy->cusName  )  );  
	 index  ++  ;		//  qySnmpObjPolicyTab.grpName
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pPolicy->grpName,  tBuf,  mycountof(  pPolicy->grpName  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.snmpVer
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->snmpVer,  sizeof(  pPolicy->snmpVer  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.getCommunity
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->getCommunity,  sizeof(  pPolicy->getCommunity  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.setCommunity
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->setCommunity,  sizeof(  pPolicy->setCommunity  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.usmName
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->usmName,  sizeof(  pPolicy->usmName  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.securityLevel
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->securityLevel,  sizeof(  pPolicy->securityLevel  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.authMethod
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->authMethod,  sizeof(  pPolicy->authMethod  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.authStr
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->authStr,  sizeof(  pPolicy->authStr  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.privMethod
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->privMethod,  sizeof(  pPolicy->privMethod  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.privStr
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->privStr,  sizeof(  pPolicy->privStr  )  );  
	 index  ++  ;		//  qySnmpPolicyGrpTab.engineId 
	 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPolicy->engineId,  sizeof(  pPolicy->engineId  )  );  
	 index  ++  ;

	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}


 //  switchMac有效时采用switchMac + iPortIfIndex为参数
 //  switchMac无效时采用id为参数
 BOOL  bGetSnmpObjRuleBySth(  void  *  pDb,  char  *  switchMac,  int  iPortIfIndex,  int  id,  QY_SNMPOBJRULE_RCD  *  pSnmpObjRule  )
{
	BOOL			bRet								=	FALSE;
	char			sqlBuf[CONST_maxSqlBufLen  +  1]	=	"";
	CDBVariant		varVals[10];
	int				iType;
	int				index								=	0;
	TCHAR			tBuf[256];

	if  (  !pSnmpObjRule  )  return  FALSE;
	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select  id,iType,switchMac,PortIfIndex,ibDirectConn,ibDownPortIfMacChanged,ibDownPortIfMacChangePort,ibNotLogIfMacChanged,warnPercentOfBand,iProcType from qySnmpObjRuleTab where "  );
	if  (  bMacValid(  switchMac  )  )  {
		iType  =  bIfIndexValid(  iPortIfIndex  )  ?  CONST_ruleType_switchPort  :  CONST_ruleType_switch;
		_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s iType = %d and switchMac='%s'",  sqlBuf,  iType,  switchMac  );
		if  (  bIfIndexValid(  iPortIfIndex  )  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s and portIfIndex=%d",  sqlBuf,  iPortIfIndex  );
		}
	else  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s id=%d",  sqlBuf,  id  );
	
	if  (  !bQyGetRcdBySql(  pDb,  CString(  sqlBuf  ).GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;
	
	memset(  pSnmpObjRule,  0,  sizeof(  pSnmpObjRule[0]  )  );
	index  =  0;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->id  );
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->iType  );
	index  ++  ;  {  MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pSnmpObjRule->switchMac,  sizeof(  pSnmpObjRule->switchMac  )  );  }
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->iPortIfIndex  );
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->ibDirectConn  );
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->ibDownPortIfMacNew  );
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->ibDownPortIfMacChangePort  );		//  2006/04/28
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->ibNotLogIfMacChanged  );			//  2006/04/28
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->warnPercentOfBandWithFactor  );
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->ibDownPortIfWarnSpeed  );			//  2006/05/29, 将iProcType改为ibDownPortIfWarnSpeed
	index  ++  ;

	//  这里还要做一个简单的有效性处理, 2006/05/30
	if  (  pSnmpObjRule->warnPercentOfBandWithFactor  <  0  ||  pSnmpObjRule->warnPercentOfBandWithFactor  >  100  *  CONST_fakedFactor_percentOfBand  )  pSnmpObjRule->warnPercentOfBandWithFactor  =  0;


	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 BOOL  tmpHandler_bGetRule(  LPVOID  pDb,  LPVOID  p1,  LPVOID  p2  )	//  返回TRUE or FALSE
{
	BOOL						bRet			=	FALSE;
	QY_SNMP_OBJ				*	pObj			=	(  QY_SNMP_OBJ  *  )p1;
	CDBVariant				*	varVals			=	(  CDBVariant  *  )p2;
	QY_SNMPOBJRULE_RCD			tmpRule;
	QY_SNMPOBJRULE_RCD		*	pSnmpObjRule	=	&tmpRule;
	int							index			=	0;
	TCHAR						tBuf[256];
	QY_SWITCHPORT_RCD		*	pPort			=	NULL;


	memset(  pSnmpObjRule,  0,  sizeof(  pSnmpObjRule[0]  )  );
	index  =  0;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->id  );
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->iType  );
	index  ++  ;  {  MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pSnmpObjRule->switchMac,  sizeof(  pSnmpObjRule->switchMac  )  );  }
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->iPortIfIndex  );
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->ibDirectConn  );
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->ibDownPortIfMacNew  );
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->ibDownPortIfMacChangePort  );		//  2006/04/28
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->ibNotLogIfMacChanged  );			//  2006/04/28
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->warnPercentOfBandWithFactor  );
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pSnmpObjRule->ibDownPortIfWarnSpeed  );			//  2006/05/29
	index  ++  ;

	//  这里还要做一个简单的有效性处理, 2006/05/30
	if  (  pSnmpObjRule->warnPercentOfBandWithFactor  <  0  ||  pSnmpObjRule->warnPercentOfBandWithFactor  >  100  *  CONST_fakedFactor_percentOfBand  )  pSnmpObjRule->warnPercentOfBandWithFactor  =  0;

	switch  (  pSnmpObjRule->iType  )  {
			case  CONST_ruleType_switch:
				  memcpy(  &pObj->rule,  pSnmpObjRule,  sizeof(  pObj->rule  )  );
				  break;
			case  CONST_ruleType_switchPort:
				  pPort  =  getPortInSwitch(  pObj,  pSnmpObjRule->iPortIfIndex  );
				  if  (  pPort  )  memcpy(  &pPort->rule,  pSnmpObjRule,  sizeof(  pPort->rule  )  );
				  break;
			default:
					break;
	}


	 bRet  =  TRUE;
//  errLabel:
	 return  TRUE;
	 
}

 BOOL  bGetSnmpObjAllRules(  void  *  pDb,  char  *  switchMac,  QY_SNMP_OBJ  *  pObj  )
{
	BOOL			bRet								=	FALSE;
	TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	CDBVariant		varVals[10];

	if  (  !bMacValid(  switchMac  )  )  goto  errLabel;

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select  id,iType,switchMac,PortIfIndex,ibDirectConn,ibDownPortIfMacChanged,ibDownPortIfMacChangePort,ibNotLogIfMacChanged,warnPercentOfBand,iProcType from qySnmpObjRuleTab where switchMac='%s'"  ),  CString(  switchMac  )  );

	if  (  !bEnumSqlQuery(  pDb,  sqlBuf,  tmpHandler_bGetRule,  pDb,  pObj,  varVals,  mycountof(  varVals  )  )  )  goto  errLabel;

	bRet  =  TRUE;

errLabel:

	 return  bRet;
}

 int  printSnmpObjRule(  QY_SNMPOBJRULE_RCD  *  pRule  )
{
	/*
	 QY_MC		*	pQyMc		=  QY_GET_GBUF(  );

	 switch  (  pRule->iType  )  {
			 case  CONST_ruleType_switch:
				   traceLogA(  "设备策略:  %s 接入设备",  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  pRule->ibDirectConn  )  );
				   break;
			 case  CONST_ruleType_switchPort:
				   traceLogA(  "端口策略:"  );
				   break;
			 default:	goto  errLabel;
	 }
	 
	 traceLogA(  "是否阻断新增MAC: %s",  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  pRule->ibDownPortIfMacNew  )  );
	 traceLogA(  "是否阻断MAC换端口: %s",  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  pRule->ibDownPortIfMacChangePort  )  );
	 traceLogA(  "是否记录MAC变化: %s",  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  ),  pRule->ibNotLogIfMacChanged  )  );

	 

errLabel:
	*/ 
	return  0;
}

 BOOL  bGetConflictConnBySth(  void  *  pDb,  char  *  switchMac,  char  *  connectedMac,  int  id,  QNM_CONFLICTCONN_RCD  *  pConflictConn  )
{
	BOOL			bRet								=	FALSE;
	char			sqlBuf[CONST_maxSqlBufLen  +  1]	=	"";
	CDBVariant		varVals[10];
	int				index								=	0;
	TCHAR			tBuf[256];

	if  (  !pConflictConn  )  return  FALSE;
	_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select  id,iType,switchMac,connectedMac,PortIfIndex,firstTime,ucbLocked,iFlg from qnmConflictConnTab where "  );
	if  (  bMacValid(  switchMac  )  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s switchMac='%s' and connectedMac='%s'",  sqlBuf,  switchMac,  connectedMac  );
	else  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s id=%d",  sqlBuf,  id  );

	if  (  !bQyGetRcdBySql(  pDb,  CString(  sqlBuf  ).GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;
	
	memset(  pConflictConn,  0,  sizeof(  pConflictConn[0]  )  );
	index  =  0;  MACRO_sqlLong(  varVals[index],  pConflictConn->id  );
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pConflictConn->iType  );
	index  ++  ;  {  MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pConflictConn->switchMac,  sizeof(  pConflictConn->switchMac  )  );  }
	index  ++  ;  {  MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pConflictConn->connectedMac,  sizeof(  pConflictConn->connectedMac  )  );  }
	index  ++  ;  MACRO_sqlLong(  varVals[index],  pConflictConn->iPortIfIndex  );
	index  ++  ;  {  MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );  myTChar2Str(  tBuf,  pConflictConn->firstTime,  sizeof(  pConflictConn->firstTime  )  );  }
	index  ++  ;  MACRO_sqlUcb(  varVals[index],  pConflictConn->ucbLocked  );
	index  ++  ;  //  MACRO_sqlLong(  varVals[index],  pConflictConn->iFlg  );
	index  ++  ;

	bRet  =  TRUE;
errLabel:
	return  bRet;

}

 // 记录网络设备事件
 //		pEvent在函数中未清0，故须注意在传入时应赋好值
 int  qnmLogNetDevEvent(  QM_dbFuncs  *  pDbFuncs,  void  *  pDbParam,  int  iDbType,  long  lEventType,  int  iCustomId,  char  *  mac,  char  *  ip,  QNM_PC_EVENT  *  pEvent  )
{
	int							iErr			=	-1;
	CDatabase				*	pDb				=	(  CDatabase  *  )pDbParam;
	QY_SNMPOBJ_HEAD				snmpObjHead;
	
	//
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	pEvent->lEventType  =  lEventType;
	pEvent->iCustomId  =  iCustomId;
	if  (  bMacValid(  mac  )  )  safeStrnCpy(  mac,  pEvent->macs[0],  sizeof(  pEvent->macs[0]  )  );
	if  (  ip  &&  bulIpValid(  inet_addr(  ip  )  )  )  safeStrnCpy(  ip,  pEvent->ip,  sizeof(  pEvent->ip  )  );

	getCurTime(  pEvent->cntEventTime  );
	if  (  !pEvent->localEventTime[0]  )  safeStrnCpy(  pEvent->cntEventTime,  pEvent->localEventTime,  sizeof(  pEvent->localEventTime  )  );
	
	switch  (  pEvent->lEventType  )  {
			case  CONST_qyEventType_nms_newDev:					//  新增设备
				  if  (  !g_dbFuncs.pf_bLogPcEventFunc(  pDb,  iDbType,  pEvent  )  )  goto  errLabel;
				  break;
			case  CONST_qyEventType_nms_delDev:					//  删除设备
			case  CONST_qyEventType_nms_devOnline:				//  设备在线
			case  CONST_qyEventType_nms_devOffline:				//  设备离线
			case  CONST_qyEventType_nms_willAttack:				//  指定设备的指定端口阻断
			case  CONST_qyEventType_nms_stopWillAttack:			//  指定设备的指定端口停止阻断
			case  CONST_qyEventType_nms_newConnection:
			case  CONST_qyEventType_nms_connectionModified:		//  联接变更
			//  case  CONST_qyEventType_nms_newConnectionIp:		//  新增联接IP
			//  case  CONST_qyEventType_nms_connectionIpModified:	//  联接IP变更
			case  CONST_qyEventType_nms_delConnection:			//  删除联接
			default:
				  if  (  !bGetSnmpObjHeadInfoBySth(  pDb,  pEvent->macs[0],  pEvent->ip,  &snmpObjHead  )  )  goto  errLabel;
				  if  (  !pEvent->ip[0]  )  safeStrnCpy(  snmpObjHead.ip,  pEvent->ip,  sizeof(  pEvent->ip  )  );
				  lstrcpyn(  pEvent->productName,  snmpObjHead.productName,  mycountof(  pEvent->productName  )  );
				  lstrcpyn(  pEvent->cols[5],  snmpObjHead.place,  mycountof(  pEvent->cols[5]  )  );
				  if  (  !g_dbFuncs.pf_bLogPcEventFunc(  pDb,  iDbType,  pEvent  )  )  goto  errLabel;

				  if  (  pEvent->lEventType  ==  CONST_qyEventType_nms_warnSpeed  )  {	//  2006/06/03, 加入声报警

					  qyShowInfo1(  CONST_qyShowType_qnmChking,  NULL,  "",  _T(  "snmpHelp"  ),  L"",  L"",  L"",  L"     %s too much traffic",  pEvent->productName  );

	  				  if  (  !setQnmWarnInfo(  NULL  )  )  goto  errLabel;
				  }

				  break;
	}

	iErr  =  0;

errLabel:

	 return  iErr;
}


