

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"myresource.h"
#include	"qmcCmdProc.h"


#include	"qyOpenShellCommon.h"


#include	"qyMcMainWndProc.h"
//

#include	"dlgTalkProc.h"



//
#include	"qyComPortEx.h"


#if  0
  int  printImMsgContent_n(  void  *  pSessionParam,  MSG_ROUTE  *  pRoute,  IM_CONTENTU  *  pContent_n,  int  iContentLen,  TCHAR  *  tBuf,  unsigned  int  maxuiBufCnt  )
  {
	  return  -1;
  }
#endif

   int  netMc_procEvent(  void  *  pQyMcParam,  void  *  pDoc,  void  *  pEventInfoParam  )
{
		return  -1;
}


   


int  initVar_isGui_mgr(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	  return  -1;
}
int  exitVar_isGui_mgr(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	  return  -1;
}


 extern "C" DWORD WINAPI mcThreadProc( LPVOID lpParameter )
{
	  return  0;
}
 extern "C" DWORD WINAPI mcThreadProc_isMgr( LPVOID lpParameter )
{
	  return  0;
}

  int  updateFileMonRules(  void  *  pDb,  char  *  mac0,  PC_FILEMON_RULES  *  pInfo  )
  {
	  return  -1;
  }
int  resetDefaultFileMonRules(  void  *  pDb,  unsigned  int  uiOldChangesId,  unsigned  char  ucbMonAll,  PC_FILEMON_RULES  *  pInfo  )
{
	return  -1;
}

 BOOL  initModuleExt(  )
{
	traceLog(  _T(  "initModuleExt,  test_isCli"  )  );
	return  FALSE;
}

  int  getSize_moduleExt(  )
{
	traceLog(  _T(  "getSize_moduleExt,  test_isCli"  )  );
	return  -1;
}

 void  exitModuleExt(  )
{
	traceLog(  _T(  "exitModuleExt,  test_isCli"  )  );
	return;
}

   QYMC_HOTKEY	gHotKeys_main[] = 
{
	//  {  ID_HKF5, 0, VK_F5, 0  },		//  不要热键了，不方便, 容易和别的软件冲突
	//  {  ID_HKF6, 0, VK_F6, 0  },
	//  {  ID_HKF7, 0, VK_F7, 0  },
	{	-1,					},
};

 int  closeOtherWnds_isMgr(  BOOL  *  pbOtherWndExists  )
{
	traceLog(  _T(  "closeOtherWnds_isMgr,  test_isCli"  )  );
	return  -1;
}

#if  0
  int  getLvColContent(  HWND  hParent,  HWND  hList,  int  curnItem,  LPCTSTR  colName,  TCHAR  *  buf,  unsigned  int  size  )
{
	  return  -1;
}

int  enumLvSelEventFunc(  QY_EVENTINFO  *  pEventInfo,  PF_procLvEventFunc  pf,  void  *  pObjDb,  int  iLvType,  void  *  pParam  )
{
	  return  -1;
}
#endif

BOOL  qyMcView_bAddColumns(  void  *  pView,  QY_COLUMNINFO * pColumns,  void  *  p2  )
{
	return  FALSE;
}
void  qyMcView_delAllColumns(  void  *  pView,  void  *  p1,  void  *  p2  )
{
	  return;
}

BOOL  bQyOpenMcView(  QY_MCVIEW_SEL  *  pParam,  void  *  p1,  void  *  p2  )
{
	return  FALSE;
}



BOOL  bQnmCmdEnable(  int  cmdId  )
{
	traceLog(  _T(  "bQnmCmdEnable not supported"  )  );
	return  FALSE;
}

 int  getSnmpObjImages(  QY_MC  *  pQyMc,  QY_SNMPOBJ_HEAD  *  pObj,  int  *  pnImage,  int  *  pnSelectedImage  )
 {
	 return  -1;
 }

 int  getSnmpPortImages(  QY_MC  *  pQyMc,  QY_SWITCHPORT_RCD  *  pPort,  int  *  pnImage,  int  *  pnSelectedImage  )
 {
	 return  -1;
 }

  BOOL  bQyMcNewTreeView(  QY_MC_SEL  *  pSel  )
  {
	  return  FALSE;
  }


    BOOL  bQyMcNewTreeListView(  QY_MC_SEL  *  pSel  )
	{
		return  FALSE;
	}


 int  procTvEventFunc_netMc(  void  *  pQyMcParam,  void  *  pDocParamReserved,  void  *  pSelParam,  void  *  pEventInfoParam,  unsigned  int  uiCmd,  LPCTSTR  colName  )
 {
#ifdef  __DEBUG__
		traceLog(  _T(  "Not finished"  )  );
#endif
	 return  -1;
 }

  BOOL  bImportKnowledge(  unsigned  int  uiType  )
  {
	  return  FALSE;
  }

   BOOL  bExportKnowledge(  unsigned  int  uiType  )
   {
	   return  FALSE;
   }

    BOOL  bClearupKnowledge(  unsigned  int  uiType  )
	{
		return  FALSE;
	}

#if 10
	int  netMc_procLvEventFunc(  void  *  pQyMcParam,  void  *  pDocParam,  void  *  pSelParam,  void  *  pEventInfoParam,  unsigned  int  uiCmd,  LPCTSTR  colName  )
	 {
		 return  -1;
	 }
#endif

 BOOL  bGetPortInfoBySth(  void  *  pDbParam,  char  *  switchMac,  
							int  iPortIfIndex,  int  iBridgePort,  char  *  connectedMac,
							QY_SWITCHPORT_RCD  *  pPortInfo,  QY_SWITCHIFPORTSECURITY_RCD  *  pPortSecurityInfo  )
 {
	 return  FALSE;
 }

  BOOL  bGetConnectedPcInfoBySth(  void  *  pDbParam,  char  *  switchMac,  char  *  connectedMac,  char  *  connectedIp,  QY_SWITCHCONNECTEDPC_RCD  *  pConnectedPcInfo  ,  QY_SWITCHSECUREMAC_RCD  *  pSecureMacInfo  )
  {
	  return  FALSE;
  }

   BOOL  bGetSnmpObjHeadInfoBySth(  void  *  pDbParam,  char  *  switchMac,  char  *  switchIp,  QY_SNMPOBJ_HEAD  *  pObj  )
   {
	   return  FALSE;
   }

#if  0
   void  qisSizePcPropertiesControls(  QNM_CUSRES_INFO  *  pCusRes,  HWND  hDlg,  QY_MESSENGER_REGINFO  *  pRegInfo  )
 {
 }
  int  setPcPropertiesLayout(  QNM_CUSTOM_COMM  *  pCustom,  QY_IDCITEM  *  pTable0  )
  {
	  return  -1;
  }
#endif

   BOOL bGetMcRootDisplayCfg(  void  *  pQyMcView,  QY_MC_DISPLAYCFG * pDisplayCfg  )
{
	   return  FALSE;
}


 BOOL  bDisplayMcRootContent(  void  *  pQyMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCROOTTREE_SEL  *  pSel  )
 {
	 return  FALSE;
 }

 BOOL  bQyMcNewIe(  QY_MC_SEL  *  pSel  )
 {
	 return  FALSE;
 }

  BOOL  bQyMcNewWebView(  QY_MC_SEL  *  pSel  )
  {
	  return  FALSE;
  }

 BOOL  bNetMcMonIfFlow(  QY_MC  *  pQyMc,  char  *  switchMac,  int  iPortIfIndex  )
 {
	 return  FALSE;
 }


   int  qnmLogNetDevEvent(  void  *  pDbParam,  int  iDbType,  long  lEventType,  int  iCustomId,  char  *  mac,  char  *  ip,  QNM_PC_EVENT  *  pEvent  )
   {
	   return  -1;
   }

 int  getDesOfMac(  QY_OBJ_DB  *  pObj,  char  *  mac,  TCHAR  *  devDescr,  unsigned  int  size,  unsigned  char  *  pucbDesManually  )
 {
	 return  0;
 }

 int  displayListContent_assets(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 return  -1;
 }

  int  refreshItem_assets(  void  *  p0,  void  *  p1,  void  *  p2  )
  {
	  return  -1;
  }

   int  displayContent_assets(  void  *  p0,  void  *  p1,  void  *  p2  )
   {
	   return  -1;
   }
   //
 unsigned  int  getVarSize_netMc(  void  *  pQyMc  )
   {
	   return  -1;
   }
 int  initVar_netMcGui(  void  *  p0,  void  *  p1,  void  *  p2  )
   {
	   return  -1;
   }
 int  exitVar_netMcGui(  void  *  p0,  void  *  p1,  void  *  p2  )
   {
	   return  -1;
   }
BOOL  bGetQySmContactRcdBySth(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  WCHAR  *  wDevIdStr,  unsigned  char  ucbDefaultSmServer,  int  id,  QY_SMCONTACT_RCD  *  pRcd  )
{
	return  FALSE;
}
BOOL  bGetQyVDevComRcdBySth(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  WCHAR  *  wDevIdStr,  int  id,  QY_VDEVCOM_RCD  *  pRcd  )
{
	return  FALSE;
}
 BOOL  bGetPhoneGuestRcdBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiDevType,  LPCTSTR  wDevIdStr,  int  id,  PHONE_GUEST_RCD  *  pRcd  )
{
	return  FALSE;
}
 
 BOOL  bGetMessengerAuthRcdBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  POLICY_imAuthCond  *  pAuthCond,  QY_COMM_AUTHINFO_MIS  *  pAuthInfo,  int  iRcdId,  QY_MESSENGERAUTH_RCD  *  pObj  )
{
	return  FALSE;
}
 int  getPcStatusInfo(  void  *  pDb,  char  *  mac0,  QY_DMITEM  *  pFieldIdTable,  PC_STATUS_INFO  *  pInfo  )
{
	return  -1;
}

 BOOL  bGetPcRule(  unsigned  char  ucbAdvancedVer,  void  *  pDb,  char  *  mac0,  QNM_PC_RULES  *  pPcRule  )
{
	return  FALSE;
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


 BOOL  bViewAllPcEventList_netMc(  QY_OBJ_DB  *  pObjDb  )
{
	return  FALSE;
}
 

 int  guiDoSnmpOpCmd(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  char  *  switchMac,  int  iPortIfIndex,  char  *  mac,  char  *  ip,  int  iSnmpOpCmd,  char  *  param  )
 {
	 return  -1;
 }

int  displayNotification_talk_ts(  HWND  hDlg,  void  *  pGuiDataParam,  LPCTSTR  hint  )
{
	 return  -1;
 }

 int  applyForServWork(  unsigned  int  uiContentType,  unsigned  short  usOp,  void  *  p0,  void  *  p1,  void  *  p2  )	//  申请服务器做一些工作
 {
	 return  -1;
 }


