  
#ifndef  __QNMSCOMMPROC_H__
#define  __QNMSCOMMPROC_H__		/*  {  */


#ifdef  __cplusplus
 extern  "C"  {
#endif


//  将入库，不能修改
//  #define			CONST_ruleType_null								0
//  #define			CONST_ruleType_switch							1000
//  #define			CONST_ruleType_switchPort						1001
//
//  注：2006/07/16，将上面的定义重新改为以下的定义，从而将这些参数统一起来
//
#define		CONST_ruleType_switch									CONST_pcCommType_switchRule
#define		CONST_ruleType_switchPort								CONST_pcCommType_switchPortRule

//  extern  QY_DMITEM  CONST_snmpBoolTable[];
//	extern  QY_DMITEM  CONST_ruleTypeTable[];
//
extern  QY_DMITEM  CONST_portAdminStatusTable[];
extern  QY_DMITEM  CONST_portOperStatusTable[];
extern  QY_DMITEM  CONST_iCpsSecureMacAddrTypeTable[];
extern  QY_DMITEM  CONST_iCpsIfViolationActionTable[];
extern  QY_DMITEM  CONST_iCpsIfPortSecurityStatusTable[];


//  手工指定的设备的信息
typedef  struct  __qnmMacDesRcd_t		{
				 char					mac[CONST_qyMacLen  +  1];
				 char					ip[CONST_qyMaxIpLen  +  1];			//  ip12格式
				 TCHAR					devType[64  +  1];
				 TCHAR					des0[255  +  1];
				 TCHAR					comment0[255  +  1];
}		 QNM_MACDES_RCD;		



typedef  struct  __qnmMacInfo_t			{
		char							mac[CONST_qyMacLen  +  1];

		unsigned  char					ucbPc;
		unsigned  char					ucbSnmpObj;
		unsigned  char					ucbOtherMacs;

		union							{
			struct						{
				QNM_PC_INFO				pcInfo;
				QNM_REG_INFO			regInfo;
			}							pcInfo;
			struct						{
				QY_SNMPOBJ_HEAD			snmpObjHead;
				QY_SWITCHPORT_RCD		portInfo;
			}							switchInfo;
			struct						{
				QNM_MACDES_RCD			macDes;
			}							otherInfo;
		}								u;
}										QNM_MAC_INFO;





int  setScanStruct(  int  iNmsOp,  int  iNmsOpCmd,  void  *  pfThreadProc,  void  *  pfScanFunc,  void  *  pDaemon,  NMS_SCAN_STRUCT  *  pScanStruct  );
BOOL  bGetDefSnmpPolicy(  void  *  p0,  void  *  pEncCtx,  QY_SNMPOBJPOLICY_RCD  *  pPolicy  );
BOOL  bSetDefSnmpPolicy(  void  *  p0,  void  *  pEncCtx,  QY_SNMPOBJPOLICY_RCD  *  pPolicy  );


int  getMacInfo(  void  *  pDb,  char  *  mac,  QNM_MAC_INFO  *  pMacInfo  );
void  showMacInfo(  QY_OBJ_DB  *  pObjDb,  char  *  mac,  unsigned  char  ucbShowPortInfo  );
void  showPcAssetInfo(  QY_OBJ_DB  *  pObjDb,  int  id  );
//  void  showOsSpInfo(  void  *  pDb,  int  id  );



#ifdef  __cplusplus
 }
#endif



#endif  /*  }  */

