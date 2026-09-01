

#ifndef  __QMCOMMONFUNC_H__
#define  __QMCOMMONFUNC_H__	/*  {  */


//
#include	"qmStruct_defs.h"


//
#define		CONST_qyFileObjName_qrgBak							"qrg"							//  ×¢²áÐÅÏ¢±¸·Ý,  ÎÄ¼þÀà
#define		CONST_qyFileObjName_qbhBak							"qbh"
#define		CONST_qyFileObjName_qvwBak							"qvw"							//  2009/10/07

#define		CONST_tabName_qyPcTab								_T(  "qyPcTab"  )				//  PC±í,		Êý¾ÝÀà
#define		CONST_tabName_qyPcRegInfoTab						_T(  "qyPcRegInfoTab"  )		//  ×¢²áÐÅÏ¢±í, Êý¾ÝÀà
#define		CONST_tabName_qyPcRegInfoTab1						_T(  "qyPcRegInfoTab1"  )		//  ÁÙÊ±×¢²áÐÅÏ¢±í, Êý¾ÝÀà

#define		CONST_qyFileObjName_qyPcSpTab						_T(  "qyPcSpTab"  )				//  ²¹¶¡±í,		Êý¾ÝÀà
#define		CONST_tabName_qyCusNameTab							_T(  "qyCusNameTab"  )
#define		CONST_qyFileObjName_qyOsSpTab						_T(  "qyOsSpTab"  )				//  2006/05/21
#define		CONST_qyFileObjName_bhbScannedIpTab					_T(  "scannedIpTab"  )
#define		CONST_qyFileObjName_qnmMacDesTab					_T(  "qnmMacDesTab"  )
#define		CONST_qyFileObjName_qnmIpScanTab					_T(  "qnmIpScanTab"  )
#define		CONST_qyFileObjName_qnmPcGrpTab						_T(  "qnmPcGrpTab"  )
#define		CONST_qyFileObjName_qySnmpObjTab					_T(  "qySnmpObjTab"  )
#define		CONST_qyFileObjName_qySwitchPortTab					_T(  "qySwitchPortTab"  )
#define		CONST_qyFileObjName_qySwitchConnectedPcTab			_T(  "qySwitchConnectedPcTab"  )
#define		CONST_qyFileObjName_qySnmpPolicyGrpTab				_T(  "qySnmpPolicyGrpTab"  )
#define		CONST_qyFileObjName_qySnmpObjPolicyTab				_T(  "qySnmpObjPolicyTab"  )
#define		CONST_qyFileObjName_qySnmpObjRuleTab				_T(  "qySnmpObjRuleTab"  )				//  2005/10/23					
#define		CONST_qyFileObjName_qyPcRuleTab						_T(  "qyPcRuleTab"  )					//  2006/03/08
#define		CONST_qyFileObjName_qyPcProcessRuleTab				_T(  "qyPcProcessRuleTab"  )			//  2006/03/08
#define		CONST_qyFileObjName_qyPcFileMonRuleTab				_T(  "qyPcFileMonRuleTab"  )			//  2006/03/25
#define		CONST_qyFileObjName_qyPcAdapterTab					_T(  "qyPcAdapterTab"  )				//  2006/04/26
//
#define		CONST_qyFileObjName_qyPcProcessKnowledgeTab			_T(  "qyPcProcessKnowledgeTab"  )		//  2006/08/17
#define		CONST_qyFileObjName_qyPcRegistryKnowledgeTab		_T(  "qyPcRegistryKnowledgeTab"  )		//  2006/08/17
#define		CONST_qyFileObjName_qyPcRegistryRuleTab				_T(  "qyPcRegistryRuleTab"  )			//  2006/08/17
//
#define		CONST_qyFileObjName_qyTestTab						_T(  "qyTestTab"  )						//  2006/04/25


//  2008/09/03
#define		CONST_qyFileObjName_qyGrpTab						_T(  "qyGrpTab"  )
#define		CONST_qyFileObjName_qyUsrTab						_T(  "qyUsrTab"  )
#define		CONST_qyFileObjName_qyGrpUsrRelationTab				_T(  "qyGrpUsrRelationTab"  )



//  2004/05/06¼Ó
#define		CONST_ver_0206										"0206"
#define		CONST_qyColsStr_bhbScannedIpTab0206					_T(  " interMonIp,officeName,subOfficeName,startIp,endIp"  )
#define		CONST_qyColsStr_qyPcTab0206							_T(  " mac0,mac1,mac2,otherMacs,nMacs,ip,qwmVer,startTime,lastCommTime,osName,pcName"  )
#define		CONST_qyColsStr_qyPcRegInfoTab0206					_T(  " mac0,regTime,ownerName,officeName,subOfficeName,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,col20,col21,col22,col23,col24,col25,col26,col27,col28,col29"  )
//
//  2006/04/28
#define		CONST_ver_0319										"0319"		//  Õâ°æÒÔÇ°¶¼ÊÇansi, ÒÔºó¶¼ÊÇutf8¸ñÊ½µÄ
#define		CONST_qyColsStr_qySnmpObjRuleTab0319				_T(  "iType,switchMac,portIfIndex,ibDirectConn,ibDownPortIfMacChanged,warnPercentOfBand,iProcType,comment0"  )				//  2005/10/23
//
#define		CONST_qyColsStr_qyCusNameTab0326					_T(  "iType,objName,cusName,comment0"  )

//
#define		CONST_ver_0335										"0335"		//  0335

#define		CONST_qyColsStr_qyGrpTab							_T(  "name,right0"  )
#define		CONST_qyColsStr_qyUsrTab							_T(  "name,passwd,zbStr,bbStr,dwStr,bmStr,comment0"  )
#define		CONST_qyColsStr_qyGrpUsrRelationTab					_T(  "grpName,usrName"  )

#define		CONST_ver_0339										"0339"		//  2011/08/28
#define		CONST_qyColsStr_qyPcRuleTab0339						_T(  "mac0,stopMon,rasCmd,delProxy,startProxy,bUnchked,bWillAttack,bDoSecChk,floppyCmd,cdromCmd,usbCmd,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,comment0"  )			//  2006/03/08


//
//
#define		CONST_qyColsStr_bhbScannedIpTab						CONST_qyColsStr_bhbScannedIpTab0206
#define		CONST_qyColsStr_qyPcTab								CONST_qyColsStr_qyPcTab0206
#define		CONST_qyColsStr_qyPcRegInfoTab						_T(  " mac0,regTime,auditTime,ownerName,officeName,subOfficeName,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,col20,col21,col22,col23,col24,col25,col26,col27,col28,col29"  )
#define		CONST_qyColsStr_qyPcSpTab							_T(  "mac0,osName,servicePack,spName,firstTime,lastTime,comment0"  )
#define		CONST_qyColsStr_qyCusNameTab						_T(  "iType,uiLangId,objName0,cusName0,objName1,cusName1,objName2,cusName2,objName3,cusName3,objName4,cusName4,objName5,cusName5,objName6,cusName6,objName7,cusName7,comment0"  )	//  2006/09/02ÐÞ¸Ä
#define		CONST_qyColsStr_qyOsSpTab							_T(  "iType,iPlatformId,prog,servicePack,spName,uiLangId,cusName,des0,url,comment0"  )		//  2006/05/21
#define		CONST_qyColsStr_qnmMacDesTab						_T(  "mac,ip,devType,des0"  )
#define		CONST_qyColsStr_qnmIpScanTab						_T(  "startIp,endIp,officeName,subOfficeName,flg"  )
#define		CONST_qyColsStr_qnmPcGrpTab							_T(  "startIp,endIp,officeName,subOfficeName,lanName,ucbStopSnmpScan,ucbStopMacScan,glCntIp,mac,fBwd,flg"  )										
#define		CONST_qyColsStr_qySnmpObjTab						_T(  "iIpForwarding,ucbBridge,ucbHost,sysDescr,iMaker,maker,productName,lNetDevType,ip,mac,dot1dBaseNumPorts,lStatus,cusName,place,firstTime,lastTime,auditTime,comment0"  )
#define		CONST_qyColsStr_qySwitchPortTab						_T(  "switchMac,portIfIndex,portIfDescr,portIfType,portIfSpeedInK,portIfPhysAddress,portIfAdminStatus,portIfOperStatus,portIfInOctets,portIfOutOctets,portIfInSpeedInK,portIfOutSpeedInK,bridgePort,vlanId,vlanName,firstTime,lastTime,comment0"  )
#define		CONST_qyColsStr_qySwitchConnectedPcTab				_T(  "switchMac,connectedMac,connectedIp,portIfIndex,firstTime,lastTime,auditTime,ucbDirectConn,comment0"  )
#define		CONST_qyColsStr_qySnmpPolicyGrpTab					_T(  "name,snmpVer,getCommunity,setCommunity,usmName,securityLevel,authMethod,authStr,privMethod,privStr,engineId,col0,col1,col2,col3,col4,comment0"  )
#define		CONST_qyColsStr_qySnmpObjPolicyTab					_T(  "ip,cusName,grpName,snmpVer,getCommunity,setCommunity,usmName,securityLevel,authMethod,authStr,privMethod,privStr,engineId,col0,col1,col2,col3,col4,comment0"  )
#define		CONST_qyColsStr_qySnmpObjRuleTab					_T(  "iType,switchMac,portIfIndex,ibDirectConn,ibDownPortIfMacChanged,ibDownPortIfMacChangePort,ibNotLogIfMacChanged,warnPercentOfBand,iProcType,comment0"  )				//  2005/10/23
#define		CONST_qyColsStr_qyPcRuleTab							_T(  "mac0,stopMon,rasCmd,delProxy,startProxy,bUnchked,bWillAttack,bDoSecChk,floppyCmd,cdromCmd,usbCmd,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,col20,col21,col22,col23,col24,col25,col26,col27,col28,col29,col30,col31,col32,col33,col34,col35,col36,col37,col38,col39,col40,col41,col42,col43,col44,col45,col46,col47,col48,col49,comment0"  )			//  2011/08/28

#define		CONST_qyColsStr_qyPcProcessRuleTab					_T(  "uiType,mac0,moduleName,modulePath,iProp0,iProp1,iProp2,iProp3,iProp4,iProp5,iProp6,iProp7,iProp8,iProp9,propStr0,propStr1,propStr2,propStr3,propStr4,propStr5,propStr6,propStr7,propStr8,propStr9,firstTime,lastTime,iStatus,comment0"  )	//  2006/03/08
#define		CONST_qyColsStr_qyPcFileMonRuleTab					_T(  "mac0,uiType,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,iCol0,iCol1,iCol2,iCol3,iCol4,comment0"  )		//2005/03/25
//  #define		CONST_qyColsStr_qyPcAdapterTab						_T(  "ucbRule,uiType,mac0,des0,des1,des2,devIdStr,devIndex,devDesc,uiAdapterType,mac,ipBuf,ipMaskBuf,gatewayBuf,gatewayMetricBuf,ucbDhcpEnabled,dhcpServerIp,lLeaseObtained,ucbHaveWins,primaryWinsServerIp,secondaryWinsServerIp,ucbAutoDns,dnsBuf,curUsrName,proxyBuf,iParam0,iParam1,iParam2,iParam3,iParam4,iParam5,iParam6,iParam7,iParam8,iParam9,iParam10,iParam11,iParam12,iParam13,iParam14,iParam15,iParam16,iParam17,iParam18,iParam19,paramStr0,paramStr1,paramStr2,paramStr3,paramStr4,paramStr5,paramStr6,paramStr7,paramStr8,paramStr9,locationInfo,iProp0,iProp1,iProp2,iProp3,iProp4,iProp5,iProp6,iProp7,iProp8,iProp9,propStr0,propStr1,propStr2,propStr3,propStr4,propStr5,propStr6,propStr7,propStr8,propStr9,firstTime,lastTime,iStatus,comment0"  )
#define		CONST_qyColsStr_qyPcAdapterTab						_T(  "ucbRule,uiType,mac0,des0,des1,des2,devIdStr,devIndex,devDesc,uiAdapterType,mac,ipBuf,ipMaskBuf,gatewayBuf,gatewayMetricBuf,ucbDhcpEnabled,dhcpServerIp,lLeaseObtained,ucbHaveWins,primaryWinsServerIp,secondaryWinsServerIp,ucbAutoDns,dnsBuf,curUsrName,proxyBuf,iParam0,iParam1,iParam2,iParam3,iParam4,iParam5,iParam6,iParam7,iParam8,iParam9,iParam10,iParam11,iParam12,iParam13,iParam14,iParam15,iParam16,iParam17,iParam18,iParam19,paramStr0,paramStr1,paramStr2,paramStr3,paramStr4,paramStr5,paramStr6,paramStr7,paramStr8,paramStr9,locationInfo,iProp0,iProp1,iProp2,iProp3,iProp4,iProp5,iProp6,iProp7,iProp8,iProp9,iProp10,iProp11,iProp12,iProp13,iProp14,iProp15,iProp16,iProp17,iProp18,iProp19,propStr0,propStr1,propStr2,propStr3,propStr4,propStr5,propStr6,propStr7,propStr8,propStr9,propStr10,propStr11,propStr12,propStr13,propStr14,propStr15,propStr16,propStr17,propStr18,propStr19,firstTime,lastTime,iStatus,comment0"  )
//
#define		CONST_qyColsStr_qyPcProcessKnowledgeTab				_T(  "uiType,fileName,name,des0,company,product,ucbSys,ucbDaemon,ucbUseNet,ucbHardware,commonErr,memInfo,securityLevel,ucbSpy,ucbAdvertisement,ucbVirus,ucbBackDoor,iProp0,iProp1,iProp2,iProp3,iProp4,iProp5,iProp6,iProp7,iProp8,iProp9,propStr0,propStr1,propStr2,propStr3,propStr4,propStr5,propStr6,propStr7,propStr8,propStr9,provider,providerAddr,providerTime,auditTime,firstTime,lastTime,iStatus,comment0"  )		//  2006/08/17
#define		CONST_qyColsStr_qyPcRegistryKnowledgeTab			_T(  "uiType,iRootKey,subKey,cfgName,suggestedVal,name,des0,company,product,ucbSys,ucbDaemon,ucbUseNet,ucbHardware,commonErr,memInfo,securityLevel,ucbSpy,ucbAdvertisement,ucbVirus,ucbBackDoor,iProp0,iProp1,iProp2,iProp3,iProp4,iProp5,iProp6,iProp7,iProp8,iProp9,propStr0,propStr1,propStr2,propStr3,propStr4,propStr5,propStr6,propStr7,propStr8,propStr9,provider,providerAddr,providerTime,auditTime,firstTime,lastTime,iStatus,comment0"  )		//  2006/08/17
#define		CONST_qyColsStr_qyPcRegistryRuleTab					_T(  "uiType,mac0,uiLangId,iPlatformId,winDir,iRootKey,usrName,subkey,ucbKey,uiCfgNameLen,cfgName,iValType,uiValLenInBytes,iCfgVal,cfgVal,nIntervals,unsupport98,unsupportMe,unsupportNt,unsupport2k,unsupportXp,unsupport2003,unsupportVista,unsupportOs10,unsupportOs11,unsupportOs12,unsupportOs13,unsupportOs14,ucbNotLogAdd,ucbNotLogDel,ucbNotLogModify,iProp0,iProp1,iProp2,iProp3,iProp4,iProp5,iProp6,iProp7,iProp8,iProp9,propStr0,propStr1,propStr2,propStr3,propStr4,propStr5,propStr6,propStr7,propStr8,propStr9,firstTime,lastTime,iStatus,comment0"  )			//  2006/08/17

//
#define		CONST_qyColsStr_qyTestTab							_T(  "col0,col_int,col_Integer"  )



	 






typedef  int  (  *PF_qnmAttackHost  )(  char  *  ip,  void  *  l  );



//  2015/11/16
#define		bFileExists(  fileName  )  (  fileName  &&  (  GetFileAttributes(  fileName  )  !=  0xFFFFFFFF  )  )



//
extern  "C"  BOOL  bBoolSame(  BOOL  b1,  BOOL  b2  );
extern  "C"  BOOL  bMacLocal(  QY_ENV  *  pEnv,  char  *  mac  );
extern  "C"  BOOL  bMacsInfoValid(  QWM_MACS_INFO  *  pMacsInfo  );
BOOL  bIfIndexValid(  int  ifIndex  );


BOOL  bQnmDbOk(  void  *  pDb  );
unsigned  int  qnmGetnPcs(  void  *  pDb  );
unsigned  int  qnmGetnSwitchs(  void  *  pDb  );
unsigned  int  qnmGetnMessengers(  void  *  pDb  );
unsigned  int  qnmGetnPhoneMessengers(  void  *  pDb  );
unsigned  int  qnmGetnImGrps(  void  *  pDb  );
unsigned  int  qnmGetnLogs(  void  *  pDb  );
//
__declspec(  dllexport  )  BOOL  bSqlObjExists(  void  *  pDb,  LPCTSTR  sqlBuf  );
//  BOOL  bLogPcEventFunc(  void  *  pDb,  int  iDbType,  QNM_PC_EVENT  *  pEvent  );
BOOL  bLogPcSecChkEventFunc(  void  *  pDb,  int  iDbType,  QNM_PC_EVENT  *  pEvent  );
//  int  getPcEventInfoByMac0(  void  *  pDb,  QNM_PC_EVENT  *  pEvent  );
int  getMac0OfChkedPc(  void  *  pDb,  QNM_CHKEDIP_STRUCT  *  pChkedPc  );
//  int  qnmRegUsrInfo(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo  );	//  ½«ÓÃ»§ÐÅÏ¢µÇ¼ÇÈë¿â,  2008/12/28
int  qnmRegPcInfo(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QNM_PC_INFO	 *  pPcInfo  );									//  ½«PCÐÅÏ¢µÇ¼ÇÈë¿â
//
int  qnmLogOpEvent(  int  iServiceId,  QM_dbFuncs  *  pDbFuncs,  void  *  pDbParam,  int  iDbType,  int  iEventType,  LPCTSTR  usr,  LPCTSTR  dsnName,  LPCTSTR  des  );
int  qnmLogOpEvent(  int  iServiceId,  QM_dbFuncs  *  pDbFuncs,  void  *  pDbParam,  int  iDbType,  int  iEventType,  LPCTSTR  usr,  LPCTSTR  des  );
int  qnmLogOpEvent(  int  iServiceId,  QM_dbFuncs  *  pDbFuncs,  QY_OBJ_DB  *  pObjDb,  int  iEventType,  LPCTSTR  des  );		//  2007/01/02
//
int  qnmLogPcEvent(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QNM_PC_INFO  *  pPcInfo,  QNM_PC_EVENT  *  pEvent  );
//
int  qnmLogPcSecChkEvent(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QNM_PC_INFO  *  pPcInfo,  QNM_PC_EVENT  *  pEvent  );
//
int  qnmLogChkEvent(  QM_dbFuncs  *  pDbFuncs,  void  *  pDbParam,  int  iDbType,  int  iEventType,  int  iCustomId,  char  *  mac,  char  *  ip,  char  *  localEventTime,  QNM_PC_EVENT  *  pEvent  );
//
BOOL  bQnmPcProxy(  void  *  pDb,  QNM_CHKEDIP_STRUCT  *  pChkedPc  );
BOOL  bQnmPcUnchked(  void  *  pDb,  char  *  ip,  char  *  mac  );
BOOL  bQnmPcWillAttacked(  void  *  pDb,  char  *  ip,  char  *  mac  );
BOOL  bQnmPcAudited(  void  *  pDb,  QNM_CHKEDIP_STRUCT  *  pPc  );
int  getCmdOfChkedPc(  void  *  pDb,  QNM_CHKEDIP_STRUCT  *  pChkedPc,  unsigned  char  ucbStartRespForUnreg,  QNM_CHKEDPC_CMDINFO  *  pCmdInfo  );
int  processNewPc(  void  *  pLicenseCtx,  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QNM_PC_INFO  *  pPcInfo  );

void  removeFromQnmChkedIpTmpTab(  void  *  pDb,  char  *  mac  );
int  addToQnmChkedIpTmpTab(  void  *  pDb,  char  *  mac,  char  *  ip,  BOOL  fBwd  );
void  updateQnmChkedIpTmpTabEndTime(  void  *  pDb,  char  *  mac  );
void  setLogAttackedFlg(  void  *  pDb,  char  *  mac,  BOOL  bAttacked  );

//
int  qnmChkPc(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  unsigned  char  ucbStartRespForUnreg,  QNM_SCANNED_PCINFO  *  pScannedPcInfo,  PF_qnmAttackHost  attackProc,  QNM_CHKEDPC_CMDINFO  *  pCmdInfo  );

//  BOOL	bQmUpdateObjStatus(  void  *  pDb, char  *  objName,  char  *  des  );
//  BOOL	bQmRefreshPolicyTime(  void  *  pDb,  char * timeBuf  );
//  BOOL	bQmRefreshPolicyExecTime(  void  *  pDb,  char  *  timeBuf  );
//  BOOL	bQmRefreshPolicyDigest(  void  *  pDb,  char  *  digest,  unsigned  int  len  );
//  BOOL	bQmGetPolicyTime(  void  *  pDb,  char  *  timeBuf,  int  size  );
//  BOOL	bQmGetPolicyExecTime(  void  * pDb,  char  *  timeBuf,  int  size  );
//  BOOL	bQmGetPolicyDigest(  void  * pDb,  char  *  buf,  unsigned  int  *  pLen  );

int		getCustomComm(  QNM_CUSTOM_COMM  *  pCustom  );
//BOOL	iibGetMacsInfoByMac(  void  *  pDbParam,  char  *  mac,  QWM_MACS_INFO  *  pMacsInfo  );
//  BOOL	bGetPcInfoByMac(  void  *  pDbParam,  char  *  mac,  unsigned  char  ucbMac0,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo  );		//  2008/12/28
//  BOOL	bGetPcInfoByMacEx(  void  *  pDbParam,  char  *  mac,  unsigned  char  ucbMac0,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo,  QNM_REG_INFO  *  pRegInfoInTab1  );	//  2008/12/28
BOOL	bGetPcAssetInfoById(  void  *  pDbParam,  int  id,  QY_PCASSET_RCD  *  pPcAssetInfo  );
//  BOOL  bGetPcRegistryInfoBySth(  void  *  pDbParam,  unsigned  char  ucbRule,  int  iRootKey,  LPCTSTR  subKey,int  id,  QY_PCREGISTRY_RCD  *  pRcd  );
BOOL	bGetPcRegistryRuleBySth(  void  *  pDbParam,  int  iDbType,  int  iRootKey,  LPCTSTR  subKey, int  id,  QY_PCREGISTRYRULE_RCD  *  pRcd  );
BOOL	bGetPcRegistryValBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  osCond,  unsigned  int  uiType,  int  iRuleId,  char  *  szSidKey,  unsigned  char  ucbKey,  unsigned  int  uiCfgNameLen,  LPCTSTR  cfgName,  int  id,  QY_PCREGISTRYVAL_RCD  *  pRcd  );
BOOL	bGetPcProcessInfoBySth(  void  *  pDbParam,  int  id,  QY_PCPROCESS_RCD  *  pRcd  );
BOOL	bGetPcAdapterRcdBySth(  void  *  pDbParam,  unsigned  char  ucbRule,  unsigned  int  uiType,  char  *  mac0,  char  *  devIdStr,  int  devIndex,  char  *  mac,  QY_PCADAPTER_RCD  *  pInputRcd,  int  id,  QY_PCADAPTER_RCD  *  p  );
BOOL	bGetPcModuleKnowledgeBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  fileName,  LPCTSTR  cmdLine,  int  id,  QY_PCMODULEKNOWLEDGE_RCD  *  pRcd  );
BOOL	bGetPcRegistryKnowledgeBySth(  void  *  pDbParam,  int  iDbType,  int  iRootKey,  LPCTSTR  subKey,  LPCTSTR  cfgName,  int  id,  QY_PCREGISTRYKNOWLEDGE_RCD  *  pRcd  );

BOOL	bGetIpKnowledgeBySth(  void  *  pDbParam,  int  iDbType,  char  *  startIp,  char  *  endIp,  char  *  detectedIp,  int  id,  IP_KNOWLEDGE_RCD  *  pRcd  );
BOOL	bGetPhoneGuestRcdBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiDevType,  LPCTSTR  wDevIdStr,  int  id,  PHONE_GUEST_RCD  *  pRcd  );
//

//
int		pcNetworkProp2Rcd(  QY_PCNETWORK_PROPU  *  p,  unsigned  char  ucbRule,  QY_PCADAPTER_RCD  *  pRcd  );
int		pcNetworkRcd2Prop(  QY_PCADAPTER_RCD  *  pRcd,  QY_PCNETWORK_PROPU  *  p  );
BOOL	bPcNetworkPropSame(  long  lhQwnVer,  QY_PCADAPTER_RCD  *  pRcd,  QY_PCNETWORK_PROPU  *  p  );
BOOL	bPcAdapterRuleSame(  QY_PCADAPTER_RCD  *  pRcd0,  QY_PCADAPTER_RCD  *  pRcd1  );
BOOL	bAddPcAdapterRcd(  void  *  pDb,  QY_PCADAPTER_RCD  *  p  );
BOOL	bUpdatePcAdapterRcdBySth(  void  *  pDb,  QY_PCADAPTER_RCD  *  p,  int  id  );
//
BOOL	bGetOsSpRcdBySth(  void  *  pDb,  int  id,  int  iPlatformId,  unsigned  int  uiLangId,  LPCTSTR  servicePack,  LPCTSTR  spName,  QY_OSSP_RCD  *  pOsSp  );
BOOL  bGetCusNameBySth(  void  *  pDb,  int  iDbType,  QY_CUSNAME_RCD  *  pCusNameCond,  int  id,  QY_CUSNAME_RCD  *  pCusName  );

//  BOOL	bGetDefaultPcRule(  void  *  pDb,  QNM_PC_RULES  *  pCfg  );
BOOL	bGetDefaultPcRule(    unsigned  char  ucbAdvancedVer,  void  *  pDb,  QNM_PC_RULES  *  pPcRule  );
BOOL	bGetPcRule(  unsigned  char  ucbAdvancedVer,  void  *  pDb,  char  *  mac0,  QNM_PC_RULES  *  pPcRule  );
BOOL	bGetQnmIntervalParams(  QNM_INTERVAL_PARAMS  *  pIntervalParams  );
//
BOOL	bGetDefaultFileMonRules(  void  *  pDb,  PC_FILEMON_RULES  *  pInfo  );
int		resetDefaultFileMonRules(  void  *  pDb,  unsigned  int  uiOldChangesId,  unsigned  char  ucbMonAll,  PC_FILEMON_RULES  *  pInfo  );
int		updateFileMonRules(  void  *  pDb,  char  *  mac0,  PC_FILEMON_RULES  *  pInfo  );
//
BOOL  bGetPcRegistryRules(  void  *  pDb,  char  *  mac0,  QY_PC_COMMU  *  pQueryCfgs,  char  *  queryTime,  QY_PC_REGISTRYRULES  *  pInfo  );

//
__declspec(  dllexport  )  int  getPcStatusInfo(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  char  *  mac0,  QY_DMITEM  *  pFieldIdTable,  PC_STATUS_INFO  *  pInfo  );  //2008/12/28



//
unsigned  int  getQnmnConns(  void  *  pLicenseCtx,  int  iServiceId  );


//
int		clearDoSecChkFlg(  void  *  pDb,  char  *  mac  );

//
BOOL	bGetCurServicePack(  void  *  pDb,  unsigned  int  uiLangId,  int  iPlatformId,  TCHAR  *  servicePack,  unsigned  int  size  );

extern  "C"  int  qyGetServiceStatus(  IN LPTSTR  lpszMachineName,  IN LPTSTR  lpszServiceName,  OUT DWORD  *  lpdwCurrentState  );


BOOL  bEnumSqlQuery(  void  *  pDb,  LPCTSTR  sqlBuf,  PF_bCommonHandler  pfb,  void  *  p0,  void  *  p1,  void  *  pVarValsParam,  unsigned  int  nVarVals  );
__declspec(  dllexport  )  int  enumSqlQuery(  void  *  pDb,  LPCTSTR  sqlBuf,  PF_commonHandler  pf,  void  *  p0,  void  *  p1,  void  *  pVarValsParam,  unsigned  int  nVarVals,  unsigned  int  *  puiRcdCnt  );

#ifndef  __WINCE__
		 #ifdef  CTime
				 CTime getCTimeByQyTime(  char  *  timeBuf  );
		 #endif
#endif


int  setPcOpStatus(  void  *  pDb,  char  *  mac0,  BOOL  bOped  );
int  setRemoteDesktopCanceled(  void  *  pDb,  void  *  p1,  char  *  mac0,  unsigned  char  ucbMonDesktop  );


//  ÓÃÓÚ½çÃæÍ¨ÖªdaemonÁ¢¼´Ë¢ÐÂ²ßÂÔ, 2006/12/10
typedef  struct  __myRefreshedPcOpCmd_t			{
				 int							iType;
				 char							mac[CONST_qyMacLen  +  1];
				 QNM_CMDPARAM_getOpCmd			getOpCmd;				 
}		 myREFRESHED_PCOPCMD;


typedef  struct  __skippedMacs_t				{
				 char							macs[5][CONST_qyMacLen  +  1];
}		 SKIPPED_MACS;
//
int getSkippedMacs(  SKIPPED_MACS  *  p  );


BOOL  bWarnMsgExists(  void  *  pDb,  char  *  popupToWarnStartTime  );
//  int  popupToWarn(  LPCTSTR  installDir  );



#endif  /*  }  */

