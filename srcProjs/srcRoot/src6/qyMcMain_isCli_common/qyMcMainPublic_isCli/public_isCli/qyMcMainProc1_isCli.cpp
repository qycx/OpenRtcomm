
#include	"stdafx.h"
#include	"qyMcMainCommon.h"

#include	"myresource.h"
#include	"qyRestrictEdit.h"

//  #include	"dlgQnmSearch.h"
#ifndef  __isCli__
#include	"dlgQnmPcListSearch.h"
#include	"dlgQnmPcProcessModuleListSearch.h"
#include	"dlgQnmPcSpListSearch.h"
#endif

//  #include	"dlgQnmEventSearch.h"

#ifndef  __isCli__
#include	"dlgQnmPcAssetListSearch.h"
#endif

//  #include	"dlgImMsgSearch.h"
#ifndef  __isCli__
#include	"dlgShhgPcProperties.h"
#include	"dlgQnmSnmpObjProperties.h"
#include	"dlgQnmOtherMacInfo.h"
#include	"DlgPcAssetProperties.h"
//  #include	"DlgSpProperties.h"
#endif
//  #include	"dlgIp.h"
//  #include	"dlgNum.h"
#ifndef  __isCli__
#include	"dlgMac.h"
#endif

#include	"qyCusResTemp.h"
#include	"myDb.h"
#include	"isCliHelpPublic.h"

 typedef  int  (  *  PF_searchHandler  )(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );

 //
 MY_DB_BUF  myDbBufs[CONST_maxMyDbBufs]	=	
 {
	 {	CONST_dbType_access,	_T(  ""  ),	},
	 {	CONST_dbType_sqlServer,	_T(  ""  ),	},
	 {	-1,	},
 };

 MY_DB_BUF  CONST_myDbBufs[CONST_maxMyDbBufs]	=	
{
	 {	CONST_dbType_access,	_T(  ""  ),	},
	 {	CONST_dbType_sqlServer,	_T(  ""  ),	},
	 {	-1,	},
 };

 int  resetMyDbBufs(  MY_DB_BUF  *  pBufs,  unsigned  int  cnt  )
{
	int		i;

	if  (  !pBufs  ||  cnt  <  mycountof(  CONST_myDbBufs  )  )  return  -1;
	memcpy(  pBufs,  CONST_myDbBufs,  sizeof(  CONST_myDbBufs  )  );
	for  (  i  =  0;  ;  i  ++  )  {
		 if  (  pBufs[i].iDbType  ==  -1  )  break;
		 pBufs[i].tBuf[0]  =  0;
	}
	return  0;
}

 //
 void  doQnmSearch_bhb(  int  iQueryType  );
 
 void  doQnmSearch(  int  iQueryType  )
{
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	int					i;
	PF_searchHandler	pf			=	NULL;
	CString				docName;
	//  CString				wherePart;
	int					iDbType;

	if  (  pQyMc->iSystemId  ==  CONST_qySystemId_bhb  )  {
		#if  0
			CLogQuery	dlg;
			dlg.DoModal(  );
		#endif
			
		#ifndef  __isCli__
			doQnmSearch_bhb(  iQueryType  );
		#endif
 
			return;
	}

	if  (  iQueryType  ==  -1  )  {
#if  0
		CDlgQnmSearch		dlg;
		if  (  IDOK  ==  dlg.DoModal(  )  )  iQueryType  =  dlg.m_var.iQueryType;
#endif
		int  iTmp  =  0;
		if  (  showDlgQnmSearch(  NULL,  &iTmp  )  ==  IDOK  )  {

			iQueryType  =  iTmp;
		}
	}
	if  (  iQueryType  ==  -1  )  goto  errLabel;

	resetMyDbBufs(  myDbBufs,  mycountof(  myDbBufs  )  );

	switch  (  iQueryType  )  {
			case  CONST_qyQueryType_netMcPcList:  {

				  if  (  pQyMc->curUsrInfo.right.bRzsj  )  {
					  ::MessageBox(  NULL,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_NoPrivilegesToOpenPcList  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_warning  ), MB_ICONSTOP );  goto  errLabel;
				  }
			
				  #ifndef  __isCli__
				  CDlgQnmPcListSearch		dlg;
				  if  (  !dlg.bSetDlgInfo(  myDbBufs  )  )  goto  errLabel;
				  if  (  dlg.DoModal(  )  ==  IDOK  )  {						//  wherePart在对话框中已经填写好了

					  //  bNetMcViewPcListFunc(  pObjDb,  dlg.m_var.col0,  dlg.m_var.wherePart  );
					  pf  =  bNetMcViewPcListFunc;
					  docName  =  CString(  dlg.m_var.col0  );
					  //  wherePart  =  dlg.m_var.wherePart;
				  }
				  #endif

				  }
				  break;
			case  CONST_qyQueryType_pcProcessList:
			case  CONST_qyQueryType_pcProcessModuleList:  {
				  #ifndef  __isCli__
				  CDlgQnmPcProcessModuleListSearch		dlg;
				  CString								str;

				  if  (  dlg.DoModal(  )  !=  IDOK  )  break;
				  if  (  iQueryType  ==  CONST_qyQueryType_pcProcessList  )  {

					  for  (  i  =  0;  ;  i  ++  )  {
						   if  (  myDbBufs[i].iDbType  ==  -1  )  break;
						   iDbType  =  myDbBufs[i].iDbType;

						   str  =  CString(  ""  )  +  "qyPcProcessTab.modulepath like "  +  getDbValStr(  iDbType,  CONST_iDataType_modulePath,  CString(  "%"  )  +  dlg.m_var.moduleName  +  "%"  );
						   str  =  str  +  " or qyPcProcessTab.myModulePath like "  +  getDbValStr(  iDbType,  CONST_iDataType_modulePath,  CString(  "%"  )  +  dlg.m_var.moduleName  +  "%"  );
						   str  =  str  +  " or qyPcProcessKnowledgeTab.name like "  +  getDbValStr(  iDbType,  CONST_iDataType_cusName,  CString(  "%"  )  +  dlg.m_var.moduleName  +  "%"  );
						   
						   lstrcpyn(  myDbBufs[i].tBuf,  str,  mycountof(  myDbBufs[i].tBuf  )  );
					  }

					  //  bNetMcViewPcProcessPropList(  pObjDb,  str  );
					  pf  =  bNetMcViewPcProcessPropList;
					  docName  =  _T(  ""  );
					  //  wherePart  =  str;

					  
						}
				  else  {

					    for  (  i  =  0;  ;  i  ++  )  {
							 if  (  myDbBufs[i].iDbType  ==  -1  )  break;
							 iDbType  =  myDbBufs[i].iDbType;

							 str  =  CString(  ""  )  +  "a.modulepath like "  +  getDbValStr(  iDbType,  CONST_iDataType_modulePath,  CString(  "%"  )  +  dlg.m_var.moduleName  +  "%"  );
							 str  =  str  +  " or a.myModulePath like "  +  getDbValStr(  iDbType,  CONST_iDataType_modulePath,  CString(  "%"  )  +  dlg.m_var.moduleName  +  "%"  );
							 str  =  str  +  " or b.modulepath like "  +  getDbValStr(  iDbType,  CONST_iDataType_modulePath,  CString(  "%"  )  +  dlg.m_var.moduleName  +  "%"  );
							 str  =  str  +  " or b.myModulePath like "  +  getDbValStr(  iDbType,  CONST_iDataType_modulePath,  CString(  "%"  )  +  dlg.m_var.moduleName  +  "%"  );
							 str  =  str  +  " or qyPcProcessKnowledgeTab.name like "  +  getDbValStr(  iDbType,  CONST_iDataType_cusName,  CString(  "%"  )  +  dlg.m_var.moduleName  +  "%"  );

							 lstrcpyn(  myDbBufs[i].tBuf,  str,  mycountof(  myDbBufs[i].tBuf  )  );
						}

					  //  bNetMcViewPcProcessModulePropList(  pObjDb,  str  );
					  pf  =  bNetMcViewPcProcessModulePropList;
					  docName  =  _T(  ""  );
					  //  wherePart  =  str;							

				  }
				  #endif
				  
				  }
				  break;
			case  CONST_qyQueryType_pcRegistryList:  {
				  #ifndef  __isCli__
				  CDlgQnmPcProcessModuleListSearch		dlg;
				  CString								str;
				  
#define		CONST_iDataType_subKey		SQL_WVARCHAR	
#define		CONST_iDataType_cfgName		SQL_WVARCHAR	
#define		CONST_iDataType_cfgVal		SQL_WVARCHAR


				  dlg.bSetDlgInfo(  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_searchReg  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_searchRegProm  )  );
				  if  (  dlg.DoModal(  )  !=  IDOK  )  break;
				  if  (  dlg.m_var.moduleName[0]  )  {

					  for  (  i  =  0;  ;  i  ++  )  {
						   if  (  myDbBufs[i].iDbType  ==  -1  )  break;
						   iDbType  =  myDbBufs[i].iDbType;

						   str  =  CString(  ""  )  +  "qyPcRegistryRuleTab.subkey like "  +  getDbValStr(  iDbType,  CONST_iDataType_subKey,  CString(  "%"  )  +  dlg.m_var.moduleName  +  "%"  );
						   str  =  str  +  " or qyPcRegistryValTab.cfgName like "  +  getDbValStr(  iDbType,  CONST_iDataType_subKey,  CString(  "%"  )  +  dlg.m_var.moduleName  +  "%"  );
						   str  =  str  +  " or qyPcRegistryValTab.cfgVal like "  +  getDbValStr(  iDbType,  CONST_iDataType_subKey,  CString(  "%"  )  +  dlg.m_var.moduleName  +  "%"  );
						   str  =  str  +  " or qyPcRegistryKnowledgeTab.name like "  +  getDbValStr(  iDbType,  CONST_iDataType_subKey,  CString(  "%"  )  +  dlg.m_var.moduleName  +  "%"  );

						   lstrcpyn(  myDbBufs[i].tBuf,  str,  mycountof(  myDbBufs[i].tBuf  )  );
					  }
				  }

				  //  bNetMcViewPcRegistryPropList(  pObjDb,  str  );
				  pf  =  bNetMcViewPcRegistryPropList;
				  docName  =  _T(  ""  );
				  //  wherePart  =  str;

				  #endif
				  }				  
				  break;
			case  CONST_qyQueryType_netMcPcSpList:  {
				  #ifndef  __isCli__

				  CDlgQnmPcSpListSearch		dlg;
				  if  (  dlg.DoModal(  )  ==  IDOK  )  {

					  //  doQnmSearchPcSp(  pObjDb,  CString(  dlg.m_var.osName  ),  CString(  dlg.m_var.spName  )  );

					  for  (  i  =  0;  ;  i  ++  )  {
						   if  (  myDbBufs[i].iDbType  ==  -1  )  break;
						   iDbType  =  myDbBufs[i].iDbType;

						   lstrcpyn(  myDbBufs[i].tBuf,  CString(  dlg.m_var.spName  ),  mycountof(  myDbBufs[i].tBuf  )  );
					  }

					  pf  =  doQnmSearchPcSp;
					  docName  =  CString(  dlg.m_var.osName  );
					  //  wherePart  =  CString(  dlg.m_var.spName  );
				  }
			      #endif
				  }
				  break;
			case  CONST_qyQueryType_netMcEventList:  {
				  #ifndef  __isCli__
				  CDlgQnmEventSearch	dlg;
				  if  (  !dlg.bSetDlgInfo(  myDbBufs,  0  )  )  goto  errLabel;
			  	  if  (  dlg.DoModal(  )  ==  IDOK  )  {
					  if  (  dlg.m_var.iEventType  ==  CONST_qyEventType_nm_rasStart  
						  ||  dlg.m_var.iEventType  ==  CONST_qyEventType_nm_rasEnd  
							  ||  dlg.m_var.iEventType  ==  CONST_qyEventType_nm_rasProhibited  )  
					  {

						  //  bNetMcViewRasEventListFunc(  pObjDb,  dlg.m_var.eventTypeName,  dlg.m_var.wherePart  );
						  pf  =  bNetMcViewRasEventListFunc;
						  docName  =  dlg.m_var.eventTypeName;
						  //  wherePart  =  dlg.m_var.wherePart;
						}
					  else  {

						    //  bNetMcViewPcEventListFunc(  pObjDb,  dlg.m_var.eventTypeName,  dlg.m_var.wherePart  );
						    pf  =  bViewPcEventListFunc_netMc;
							docName  =  dlg.m_var.eventTypeName;
							//  wherePart  =  dlg.m_var.wherePart;
					  }
			  	  }
				  #endif

				  }
				  break;
			case  CONST_qyQueryType_opEventList:  {		//  2006/02/25
#ifndef  __isCli__
				  CDlgQnmEventSearch	dlg;
				  if  (  !dlg.bSetDlgInfo(  myDbBufs,  iQueryType  )  )  goto  errLabel;
			  	  if  (  dlg.DoModal(  )  ==  IDOK  )  {

					  //  bNetMcViewOpEventListFunc(  pObjDb,  dlg.m_var.eventTypeName,  dlg.m_var.wherePart  );				
					  pf  =  bViewOpEventListFunc;
					  docName  =  dlg.m_var.eventTypeName;
					  //  wherePart  =  dlg.m_var.wherePart;
				  }
#endif
				  }
				  break;
			case  CONST_qyQueryType_netDevEventList:  {
#ifndef  __isCli__
				  CDlgQnmEventSearch	dlg;
			  	  if  (  !dlg.bSetDlgInfo(  myDbBufs,  iQueryType  )  )  goto  errLabel;
				  if  (  dlg.DoModal(  )  ==  IDOK  )  {

					  //  bNetMcViewNetDevEventListFunc(  pObjDb,  dlg.m_var.eventTypeName,  dlg.m_var.wherePart  );
					  pf  =  bNetMcViewNetDevEventListFunc;
					  docName  =  dlg.m_var.eventTypeName;
					  //  wherePart  =  dlg.m_var.wherePart;
				  }
#endif
				  }
				  break;
			case  CONST_qyQueryType_secChkEventList:  {
#ifndef  __isCli__
				  CDlgQnmEventSearch	dlg;
				  if  (  !dlg.bSetDlgInfo(  myDbBufs,  iQueryType  )  )  goto  errLabel;
				  if  (  dlg.DoModal(  )  ==  IDOK  )  {

					  //  bNetMcViewPcSecChkEventList(  pObjDb,  dlg.m_var.wherePart  );
					  pf  =  bNetMcViewPcSecChkEventList;
					  docName  =  _T(  ""  );
					  //  wherePart  =  dlg.m_var.wherePart;
				  }
#endif
				  }
				  break;
			case  CONST_qyQueryType_mac:  {
				  #ifndef  __isCli__

				  CDlgMac	dlg;

				  if  (  !dlg.bSetDlgInfo(  0,  NULL,  getResStr(  0,  &pQyMc->cusRes,  IDC_mac_hint  ),  getResStr(  0,  &pQyMc->cusRes,  IDOK  ),  getResStr(  0,  &pQyMc->cusRes,  IDCANCEL  )  )  )  goto  errLabel;
				  if  (  dlg.DoModal(  )  ==  IDOK  )  {

					  for  (  i  =  0;  ;  i  ++  )  {
						   if  (  myDbBufs[i].iDbType  ==  -1  )  break;
						   iDbType  =  myDbBufs[i].iDbType;

						   lstrcpyn(  myDbBufs[i].tBuf,  CString(  dlg.m_var.mac  ),  mycountof(  myDbBufs[i].tBuf  )  );
					  }

					  //  doQnmSearchMac(  pObjDb,  dlg.m_var.mac  );
					  pf  =  doQnmSearchMac;
					  docName  =  _T(  ""  );
					  //  wherePart  =  CString(  dlg.m_var.mac  );
				  }
				  #endif 
				  }
				  break;
			case  CONST_qyQueryType_ip:  {
				  #ifndef  __isCli__
				  CDlgIp	dlg;

				  if  (  !dlg.bSetDlgInfo(  0,  NULL,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_searchIp  ),  getResStr(  0,  &pQyMc->cusRes,  IDOK  ),  getResStr(  0,  &pQyMc->cusRes,  IDCANCEL  )  )  )  goto  errLabel;
				  if  (  dlg.DoModal(  )  ==  IDOK  )  {

					  for  (  i  =  0;  ;  i  ++  )  {
						   if  (  myDbBufs[i].iDbType  ==  -1  )  break;
						   iDbType  =  myDbBufs[i].iDbType;

						   lstrcpyn(  myDbBufs[i].tBuf,  CString(  dlg.m_var.ipBuf  ),  mycountof(  myDbBufs[i].tBuf  )  );
					  }

					  //  doQnmSearchIp(  pObjDb,  dlg.m_var.ipBuf  );
					  pf  =  doQnmSearchIp;
					  docName  =  _T(  ""  );
					  //  wherePart  =  CString(  dlg.m_var.ipBuf  );
				  }
				  #endif
			  
				  }
				  break;
			case  CONST_qyQueryType_unusedConn:  {
				  #ifndef  __isCli__

				  CDlgNum	dlg;
				  CString	condCStr,  titleCStr;
				  char		buf[256];
				  char		curTimeBuf[CONST_qyTimeLen  +  1],  timeBuf[CONST_qyTimeLen  +  1];
				  

				  if  (  !dlg.bSetDlgInfo(  0,  NULL,  getResStr(  0,  &pQyMc->cusRes,  IDD_num  ),  getResStr(  0,  &pQyMc->cusRes,  IDC_num_hint  ),  getResStr(  0,  &pQyMc->cusRes,  IDOK  ),  getResStr(  0,  &pQyMc->cusRes,  IDCANCEL  ),  2  )  )  goto  errLabel;
				  if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
				  if  (  dlg.m_var.n  <  0  )  goto  errLabel;
				  getCurTime(  curTimeBuf  );
				  if  (  getTimeByInterval(  curTimeBuf,  -1  *  dlg.m_var.n  *  24  *  3600,  timeBuf,  mycountof(  timeBuf  )  )  )  goto  errLabel;  
				  condCStr  =  CString(  "qySwitchConnectedPcTab.connectedMac not in (select qySwitchConnectedPcTab.connectedMac from qySwitchConnectedPcTab where qySwitchConnectedPcTab.lastTime>'"  )  +timeBuf  +  "')";
				  titleCStr  =  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_searchResult  )  )  +  _ltoa(  dlg.m_var.n,  buf,  10  )  +  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_daysCannotBeFound  );
				  
				  for  (  i  =  0;  ;  i  ++  )  {
					   if  (  myDbBufs[i].iDbType  ==  -1  )  break;
					   iDbType  =  myDbBufs[i].iDbType;

					   lstrcpyn(  myDbBufs[i].tBuf,  condCStr,  mycountof(  myDbBufs[i].tBuf  )  );
				  }

				  //  bNetMcViewNetDevConnListFunc(  pObjDb,  CONST_qyQueryType_unusedConn,  titleCStr,  condCStr  );
				  pf  =   bNetMcViewNetDevConnListFunc_unusedConn;
				  docName  =  titleCStr;
				  //  wherePart  =  condCStr;

				  #endif 												 
				  }
				  break;
			case  CONST_qyQueryType_pcAssetList:  {
				  
				  #ifndef  __isCli__
				  CDlgQnmPcAssetListSearch	dlg;
				  if  (  !dlg.bSetDlgInfo(  myDbBufs  )  )  goto  errLabel;
				  if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

				  //  bNetMcViewPcAssetListFunc(  pObjDb,  _T(  ""  ),  dlg.m_var.wherePart  );
				  pf  =  bNetMcViewPcAssetListFunc;
				  docName  =  _T(  ""  );
				  //  wherePart  =  dlg.m_var.wherePart;
				  #endif
				  }
				  break;
			case  CONST_qyQueryType_imMsgList:  {
#if  0
				  CDlgImMsgSearch		dlg;
				  if  (  !dlg.bSetDlgInfo(  myDbBufs,  iQueryType  )  )  goto  errLabel;
				  if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
#endif
				  if  (  showDlgImMsgSearch(  NULL,  myDbBufs,  iQueryType  )  !=  IDOK  )  goto  errLabel;
				  //
				  #ifndef  __isCli__
						   pf  =  bViewImMsgListFunc_isMgr;
				  #else  
						   pf  =  bViewImMsgListFunc;
				  #endif
				  docName  =  _T(  ""  );

				  }
				  break;
			default:
				   traceLogA(  "iQueryType error: iQueryType is %d",  iQueryType  );
				   break;
	}
	
	if  (  pf  )  {
		QY_OBJ_DB		*	pObjDb		=	NULL;
		CString				wherePart;
		int					j;
		for  (  i  =  0;  i  <  (  int  )getProcedObjDbsMaxCnt(  pQyMc  );  i  ++  )  {
			 pObjDb  =  getProcedObjDb(  pQyMc,  0,  i );
			 if  (  !bObjDbAvail(  pObjDb  )  )  continue;
			 //  2007/01/03, 因为不同的数据库对wvarchar的字符表示不同，所以造成了不同的句法，需要用不同的str来存储，下面就是要把相应的str找出来
			 for  (  j  =  0;  ;  j  ++  )  {
				  if  (  myDbBufs[j].iDbType  ==  -1  )  break;
				  if  (  myDbBufs[j].iDbType  ==  pObjDb->cfg.iDbType  )  break;
				  continue;
			 }
			 if  (  myDbBufs[j].iDbType  ==  -1  )  {
				 traceLogA(  "doQnmSearch: error iDbType"  );
				 continue;		
			 }
			 wherePart  =  myDbBufs[j].tBuf;
			 //
			 pf(  pQyMc,  pObjDb,  docName,  wherePart  );
		}
	}

errLabel:
		
	return;

}

 void  showMacInfo(  QY_OBJ_DB  *  pObjDb,  char  *  mac,  unsigned  char  ucbShowPortInfo  )
{
	 QNM_MAC_INFO		macInfo;
	 void			*	pDb		=	NULL;

	 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;
	 pDb  =  pObjDb->pDb;
	 
#ifndef  __isCli__
	 memset(  &macInfo,  0,  sizeof(  macInfo  )  );	
	 if  (  getMacInfo(  pDb,  mac,  &macInfo  )  )  goto  errLabel;
	 if  (  macInfo.ucbPc  )  {
		 CDlgShhgPcProperties  dlg;

		 if  (  !dlg.bSetDlgInfo(  pObjDb,  0,  mac  )  )  goto  errLabel;
		 dlg.DoModal(  );							
		 }
	 else  if  (  macInfo.ucbSnmpObj  )  {
			   CDlgQnmSnmpObjProperties  dlg;
						
			   if  (  !dlg.bSetDlgInfo(  pObjDb,  macInfo.u.switchInfo.snmpObjHead.mac,  ucbShowPortInfo  ?  macInfo.u.switchInfo.portInfo.iPortIfIndex  :  -1  )  )  goto  errLabel;
			   dlg.DoModal(  );
		
			}
	 else  {
		   CDlgQnmOtherMacInfo	dlg;

		   if  (  !dlg.bSetDlgInfo(  pObjDb,  mac  )  )  goto  errLabel;
		   dlg.DoModal(  );		   
	 }
#endif

errLabel:
		return;
}


 void  showPcAssetInfo(  QY_OBJ_DB  *  pObjDb,  int  id  )
{
#ifndef  __isCli__
	 CDlgPcAssetProperties	dlg;
	 
	 //  traceLogA(  "mac0为%s, 型号为%s, 名称为%s",  pPcAsset->mac0,  qyGetDesByType1(  CONST_assetTypeTable,  pPcAsset->uiType  ),  pPcAsset->name  );
	 if  (  !dlg.bSetDlgInfo(  pObjDb,  id  )  )  goto  errLabel;
	 dlg.DoModal(  );
#endif

errLabel:
	 return;
}



 







