
#ifndef  __QMSNMPPROC_H__
#define  __QMSNMPPROC_H__	/*  {  */

//  2016/09/07
#include	"qmStruct_defs.h"


//
QY_SWITCHPORT_RCD  *  getPortInSwitch(  QY_SNMP_OBJ  *  pSwitch,  int  iPortIfIndex  );


BOOL  bGetSnmpObjHeadInfoBySth(  void  *  pDbParam,  char  *  switchMac,  char  *  switchIp,  QY_SNMPOBJ_HEAD  *  pObj  );
BOOL  bGetPortInfoBySth(  void  *  pDbParam,  char  *  switchMac,  int  iPortIfIndex,  int  iBridgePort,  char  *  connectedMac,  QY_SWITCHPORT_RCD  *  pPortInfo,  QY_SWITCHIFPORTSECURITY_RCD  *  pPortSecurityInfo  );
BOOL  bGetConnectedPcInfoBySth(  void  *  pDbParam,  char  *  switchMac,  char  *  connectedMac,  char  *  connectedIp,  QY_SWITCHCONNECTEDPC_RCD  *  pConnectedPcInfo  ,  QY_SWITCHSECUREMAC_RCD  *  pSecureMacInfo  );
BOOL  bGetConnectedDevInfoBySth(  void  *  pDbParam,  char  *  switchMac,  int  iPortIfIndex,  long  lDeviceIndex,  QY_SWITCHCONNECTEDDEV_RCD  *  pDevInfo  );
BOOL  bGetSnmpObjPolicyBySth(  void  *  pDb,  char  *  switchIp,  QY_SNMPOBJPOLICY_RCD  *  pPolicy  );
BOOL  bGetSnmpObjRuleBySth(  void  *  pDb,  char  *  switchMac,  int  iPortIfIndex,  int  id,  QY_SNMPOBJRULE_RCD  *  pSnmpObjRule  );
BOOL  bGetSnmpObjAllRules(  void  *  pDb,  char  *  switchMac,  QY_SNMP_OBJ  *  pObj  );
BOOL  bGetConflictConnBySth(  void  *  pDb,  char  *  switchMac,  char  *  connectedMac,  int  id,  QNM_CONFLICTCONN_RCD  *  pConflictConn  );
//
int  qnmLogNetDevEvent(  QM_dbFuncs  *  pDbFuncs,  void  *  pDbParam,  int  iDbType,  long  lEventType,  int  iCustomId,  char  *  mac,  char  *  ip,  QNM_PC_EVENT  *  pEvent  );

 int  printSnmpObjRule(  QY_SNMPOBJRULE_RCD  *  pRule  );

#endif  /*  }  */


