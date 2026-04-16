

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMc.h"
#include	"qyMcMainHint.h"
#include	"qyMcView.h"
#include	"myDb.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


 



 BOOL bGetMcRootDisplayCfg(  void  *  pQyMcViewParam,  QY_MC_DISPLAYCFG * pDisplayCfg  )
{
	BOOL							bRet					=		FALSE;
	CQyMcView  * pMcView  =  (  CQyMcView  *  )pQyMcViewParam;

	 
	if  (  pDisplayCfg->m_iViewType  !=  QY_VIEWTYPE_MCROOTLIST  )  {
		qyDebugHint(  _T(  "bGetMcBarDisplayCfg(  ) only supports QY_VIEWTYPE_MCROOTLIST. "  )  );
		goto  errLabel;
	}
	
	//  2005/11/23, 把下面的语句给屏蔽了，似乎没什么用
	//  pDisplayCfg->u.rootList.columnsBuf.nColumns  =  sizeof( sQyMcRootListColumns ) / sizeof( QY_COLUMNINFO )  -  1;
	//  memcpy(  &pDisplayCfg->u.rootList.columnsBuf.columns,  &sQyMcRootListColumns,  sizeof(  sQyMcRootListColumns  )  );				  
	

	bRet  =  TRUE;

errLabel:

	return	bRet;

}



 int  getSnmpObjImages(  QY_MC  *  pQyMc,  QY_SNMPOBJ_HEAD  *  pObj,  int  *  pnImage,  int  *  pnSelectedImage  )
{
	 BOOL					bOnline				=	(  pObj->lStatus  !=  CONST_snmpObjStatus_offline  );
	 long					lNetDevType			=	pObj->lNetDevType;
	 QNM_IMAGE_SET		*	pImageSet			=	NULL;
	 TCHAR					productName[64]		=	_T(  ""  );

	 if  (  lNetDevType  ==  CONST_netDevType_null  )  {
		 if  (  pObj->iIpForwarding  ==  1  )  {
			 if  (  !pObj->ucbBridge  )  {  lNetDevType  =  CONST_netDevType_router;  }
			 else  {   lNetDevType  =  CONST_netDevType_3switch;  }
			 }
	 	 else  {
			   if  (  pObj->ucbBridge  )  {   lNetDevType  =  CONST_netDevType_2switch;  }
	 	 }
	 }

	 //  2004/04/11, 当pc机具有路由功能时，作为软路由处理
	 if  (  lNetDevType  ==  CONST_netDevType_pc  )  {
		 if  (  pObj->iIpForwarding  ==  1  )  lNetDevType  =  CONST_netDevType_router;
	 }
	
	 if  (  !pQyMc->cfg.ucbStartRegScan  )  pImageSet  =  bOnline  ?  &pQyMc->cfg.image.normal  :  &pQyMc->cfg.image.offline;
	 else  pImageSet  =  bOnline  ?  (  pObj->auditTime[0]  ?  &pQyMc->cfg.image.normal  :  &pQyMc->cfg.image.normalWarn  )  :  (  pObj->auditTime[0]  ?  &pQyMc->cfg.image.offline  :  &pQyMc->cfg.image.offlineWarn  );
	 
	 switch  (  lNetDevType  )  {
			 case  CONST_netDevType_pc:
				   *  pnImage  =  *  pnSelectedImage  =  pImageSet->nImage_pcNormal;  
				   break;				   
		     case  CONST_netDevType_2switch:
				   *  pnImage  =  *  pnSelectedImage  =  pImageSet->nImage_switcher2;  
				   break;
			 case  CONST_netDevType_3switch:
				   *  pnImage  =  *  pnSelectedImage  =  pImageSet->nImage_switcher3;  
				   break;
			 case  CONST_netDevType_router:
				   *  pnImage  =  *  pnSelectedImage  =  pImageSet->nImage_router;  
				   break;
			 default:
				    lstrcpyn(  productName,  pObj->productName,  mycountof(  productName  )  );
					tTrim(  productName  );
					if  (  productName[0]  )  *  pnImage  =  *  pnSelectedImage  =  pImageSet->nImage_pcNormal;	
					else  *  pnImage  =  *  pnSelectedImage  =  pImageSet->nImage_unknown;	
					break;
	 }

	 return  0;
	 
}

 int  getSnmpPortImages(  QY_MC  *  pQyMc,  QY_SWITCHPORT_RCD  *  pPort,  int  *  pnImage,  int  *  pnSelectedImage  )
{
	 if  (  pPort->iPortIfAdminStatus  ==  CONST_portStatus_down  )  {
		 *  pnImage  =  *  pnSelectedImage  =  pQyMc->cfg.image.nImage_portAdminDown;
		}
	 else  if  (  pPort->iPortIfOperStatus  !=  CONST_portStatus_up  )  {
			   *  pnImage  =  *  pnSelectedImage  =  pQyMc->cfg.image.nImage_portWait;
		}
	 else  {
		   *  pnImage  =  *  pnSelectedImage  =  pQyMc->cfg.image.nImage_portUp;
	 }
		
	 return  0;

}

 int  getMacImages(  QY_MC  *  pQyMc,  QY_SNMPOBJ_HEAD  *  pSnmpObjHead,  QY_SWITCHPORT_RCD  *  pPort,  QY_SWITCHIFPORTSECURITY_RCD  *  pPortSecurity,  QY_SWITCHCONNECTEDPC_RCD  *  pConnInfo,  QY_SWITCHSECUREMAC_RCD  *  pSecureMac,  int  *  pnImage,  int  *  pnSelectedImage  )
{
	 QNM_IMAGE_SET	*	pImageSet	=	NULL;

	 if  (  pSnmpObjHead  &&  pSnmpObjHead->ucbCpsGlobalPortSecurityEnable  &&  pPortSecurity  &&  pPortSecurity->ucbCpsIfPortSecurityEnable  &&  pSecureMac  &&  pSecureMac->iCpsSecureMacAddrType  )  pImageSet  =  &pQyMc->cfg.image.secureConn;
	 else  if  (  pQyMc->cfg.ucbStartRegScan  &&  !pConnInfo->auditTime[0]  )  pImageSet  =  &pQyMc->cfg.image.normalWarn;
	 else  if  (  pConnInfo->ucbDirectConn  )  pImageSet  =  &pQyMc->cfg.image.directConn;
	 else  pImageSet  =  &pQyMc->cfg.image.normal;

	 if  (  pPort->iPortIfAdminStatus  ==  CONST_portStatus_down  )  {
		 *  pnImage  =  *  pnSelectedImage  =  pImageSet->nImage_pcAdminDown;
		}
	 else  if  (  pPort->iPortIfOperStatus  !=  CONST_portStatus_up  )  {
			   *  pnImage  =  *  pnSelectedImage  =  pImageSet->nImage_pcWait;
		}
	 else  if  (  !b2TimeNear(  pSnmpObjHead->lastTime,  pConnInfo->lastTime,  180  )  )  {
			   *  pnImage  =  *  pnSelectedImage  =  pImageSet->nImage_pcWait;
		}
	 else  {
		   *  pnImage  =  *  pnSelectedImage  =  pImageSet->nImage_pcNormal;
	 }
		
	 return  0;

}


 int  getDesOfMac(  QY_OBJ_DB  *  pObj,  char  *  mac,  TCHAR  *  devDescr,  unsigned  int  size,  unsigned  char  *  pucbDesManually  )
{
	 int				iErr					=		-1;
	 QY_MC			*	pQyMc					=		QY_GET_GBUF(  );
	 CDBVariant			varVals[5];
	 char				sqlBuf[1024];
	 int				index;
	 char				portIfDescr[255  +  1]  =  "",  productName[255  +  1]  =  "",  switchIp[CONST_qyMaxIpLen  +  1]  =  "";
	 char				ip12[12  +  1]			=  "";
	 CRecordset			rs;
	 int				nFields;
	 int				cnt						=	0;
	 QNM_PC_INFO		pcInfo;
	 unsigned  char		ucbDesManually			=	FALSE;	
	 CQnmDb				db;
	 TCHAR				tBuf[1024];
	 void			*	pDb						=	NULL;


	 QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	 if  (  !db.getAvailableDb(  pObj->iDsnIndex  )  )  goto  errLabel;
	 pDb  =  db.getAvailableDb(  pObj->iDsnIndex  );
	 rs.m_pDatabase  =  (  CDatabase  *  )pDb;
	 	 
	 memset(  &pcInfo,  0,  sizeof(  pcInfo  )  );
	 if  (  g_dbFuncs.pf_bGetPcInfoByMac(  pDb,  mac,  FALSE,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  &pcInfo,  NULL  )  )  {
		 _sntprintf(  devDescr,  size,  _T(  "Computer  ( %s )"  ),  CString(  pcInfo.ip  )  );
		 iErr  =  0;  goto  errLabel;
	 }

	 _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select qySwitchPortTab.portIfDescr,qySnmpObjTab.productName,qySnmpObjTab.ip from qySwitchPortTab,qySnmpObjTab where qySwitchPortTab.portIfPhysAddress='%s' and qySwitchPortTab.switchMac=qySnmpObjTab.mac",  mac  );

	 try  {
		 
		  if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
		  	  traceLogA(  "rs open() failed."  );  goto  errLabel;
		  }
	  			 
		
		  nFields  =  rs.GetODBCFieldCount(  );
		  //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
		  for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  ),  cnt  ++  )  {

			   if  (  cnt  >=  1  )  {  cnt  =  2;  break;  }
		
			   for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
	
	 		   index  =  0;		//  qySwitchPortTab.portIfDescr
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  portIfDescr,  sizeof(  portIfDescr  )  );    
			   index  ++  ;		//  qySnmpObjTab.productName
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  productName,  sizeof(  productName  )  );    
			   index  ++  ;		//  qySnmpObjTab.ip
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  switchIp  );    
			   index  ++  ;		
		  }

		  rs.Close(  );
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "getDesOfMac failed."  )  );
		   goto  errLabel;
	}
	
	 if  (  cnt  ==  0  )  _sntprintf(  devDescr,  size,  _T(  ""  )  );
	 else if  (  cnt  ==  1  )  _sntprintf(  devDescr,  size,  _T(  "%s( %s )%s"  ),  CString(  productName  ),  CString(  switchIp  ),  CString(  portIfDescr  )  );
	 else  _sntprintf(  devDescr,  size,  _T(  "%s( %s )"  ),  CString(  productName  ),  CString(  switchIp  )  );
	 
	 if  (  !devDescr[0]  )  {
		 QNM_MACDES_RCD		macDes;
		 
		 memset(  &macDes,  0,  sizeof(  macDes  )  );
		 if  (  bGetMacDesByMac(  pDb,  mac,  &macDes  )  )  {
			 _sntprintf(  devDescr,  size,  _T(  "%s %s"  ),  CString(  macDes.devType  ),  CString(  macDes.des0  )  );
			 ucbDesManually  =  TRUE;
		 }
	 }

	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 if  (  pucbDesManually  )  *pucbDesManually  =  ucbDesManually;
	 }
	 return  iErr;
}


 BOOL  bDisplayMcRootContent_allDevices(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CQyMcDoc						*	pDoc					=			pMcView->GetDocument(  );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 int								index					=			0;
	 //  QY_MCROOTLIST_DISPLAYCFG		*	pCfg					=			&pCfgParam->u.rootList;
	 char								sqlBuf[1024];
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	 CRecordset							rs(  (  CDatabase  *  )pObjDb->pDb  );   int	 nFields;
	 CDBVariant							varVals[20];	 
	 QY_SNMPOBJ_HEAD					snmpObj;
	 QY_SNMPOBJ_HEAD				*	pObj					=			&snmpObj;
	 int								cnt						=			0;
	 char								portStatusBuf[256]		=			"";
	 int								nImage,  nSelectedImage;
	 char								timeBuf[32  +  1];
	 TCHAR							*	pStopString;
	 char								buf[256];
	 TCHAR								tBuf[1024];
	 	 
	 
	 try  {		
	 
		  if  (  pMcView->var.m_superSel.u.rootTree.bRoot  )  {
			  
			  //  显示所有的交换机

			  pMcView->delAllColumns(  );
			  if  (  !pMcView->bAddColumns(  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_networkViewTable  )  )  )  goto  errLabel;

			  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select iIpForwarding,ucbBridge,ucbHost,sysDescr,iMaker,maker,productName,lNetDevType,ip,mac,dot1dBaseNumPorts,lStatus,cusName,place,firstTime,lastTime,auditTime from qySnmpObjTab %s %s order by productName",  pDoc->m_docStruct.u.treeList.tree.wherePart[0]  ?  "where"  :  "",  pDoc->m_docStruct.u.treeList.tree.wherePart  );
		  	  if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
		  		  debugLog(  "rs open() failed."  );  goto  errLabel;
		  	  }
	  			 
			  nFields  =  rs.GetODBCFieldCount(  );
			  //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
			  for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
						   
				   for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   	   
				   memset(  pObj,  0,  sizeof(  pObj[0]  )  ); 
						
				   index  =  0;		//  iIpForwarding
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  pObj->iIpForwarding  =  _tcstol(  tBuf,  &pStopString,  10  );    
				   index  ++  ;		//  ucbBridge
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  pObj->ucbBridge  =  (  unsigned  char  )_tcstol(  tBuf,  &pStopString,  10  );    
	 			   index  ++  ;		//  ucbHost
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  pObj->ucbHost  =  (  unsigned  char  )_tcstol(  tBuf,  &pStopString,  10  );    
	 			   index  ++  ;		//  sysDescr	 
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pObj->sysDescr,  tBuf,  mycountof(  pObj->sysDescr  )  );    
	 			   index  ++  ;		//  iMaker,
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  pObj->iMaker  =  _tcstol(  tBuf,  &pStopString,  10  );    
	 			   index  ++  ;		//  maker,
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pObj->maker,  tBuf,  mycountof(  pObj->maker  )  );    
	 			   index  ++  ;		//  productName,
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pObj->productName,  tBuf,  mycountof(  pObj->productName  )  );    
				   index  ++  ;		//  lNetDevType
				   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )	   {  pObj->lNetDevType  =  varVals[index].m_lVal;    }				   
	 			   index  ++  ;		//  ip,
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );  qyIp12ToStd(  buf,  pObj->ip  );    
	 			   index  ++  ;		//  mac,
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pObj->mac,  sizeof(  pObj->mac  )  );    
	 			   index  ++  ;		//  dot1dBaseNumPorts
				   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pObj->uiIfNumber  =  varVals[index].m_lVal;    }
				   index  ++  ;		//  lStatus
				   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pObj->lStatus  =  varVals[index].m_lVal;    }
	 			   index  ++  ;		//  cusName
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pObj->cusName,  tBuf,  mycountof(  pObj->cusName  )  );    
	 			   index  ++  ;		//  place
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pObj->place,  tBuf,  mycountof(  pObj->place  )  );    
	 			   index  ++  ;		//  firstTime
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pObj->firstTime,  sizeof(  pObj->firstTime  )  );    
	 			   index  ++  ;		//  lastTime
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pObj->lastTime,  sizeof(  pObj->lastTime  )  );    
	 			   index  ++  ;		//  auditTime
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pObj->auditTime,  sizeof(  pObj->auditTime  )  );    
	 			   index  ++  ;		//  
				   
				   //  暂时不略去, 2003/10/25
				   //  if  (  pObj->ucbHost  )  {
				   // 	   traceLogA(  "%s是主机，不显示",  pObj->ip  );  continue;
				   //  }
	 			  		
				   _strlwr(  snmpObj.mac  );
				   getSnmpObjImages(  pQyMc,  pObj,  &nImage,  &nSelectedImage  );

			   	   ListCtrl.InsertItem(  cnt,  CString(  snmpObj.productName  ).GetBuffer(  0  ),  nImage  );
				   ListCtrl.SetItemText(  cnt,  1,  CString(  snmpObj.ip  ).GetBuffer(  0  )  );	
				   ListCtrl.SetItemText(  cnt,  2,  CString(  snmpObj.cusName  ).GetBuffer(  0  )  );
				   ListCtrl.SetItemText(  cnt,  3,  CString(  snmpObj.place  ).GetBuffer(  0  )  );
				   ListCtrl.SetItemText(  cnt,  4,  CString(  qyDisplayTime(  snmpObj.auditTime,  timeBuf,  sizeof(  timeBuf  )  )  ).GetBuffer(  0  )  );
				   ListCtrl.SetItemText(  cnt,  5,  CString(  qyDisplayTime(  snmpObj.lastTime,  timeBuf,  sizeof(  timeBuf  )  )  ).GetBuffer(  0  )  );
				   ListCtrl.SetItemText(  cnt,  6,  CString(  snmpObj.mac  ).GetBuffer(  0  )  );

				   cnt  ++  ;

			  }
			
			  rs.Close(  );

			}
		  
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bDisplayMcRootContent_allDevices failed."  )  );
		   goto  errLabel;
	}
		 
	 bRet  =  TRUE;

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	 return  bRet;		

}


/*
 BOOL  bDisplayMcRootContent_switch(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  )

*/
 
 //  上面的函数是原先的显示函数，性能不理想
 //  由此作如下修改
 BOOL  bDisplayMcRootContent_switch(   QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 //  LV_ITEM							lvi;
	 int								index					=			0;
	 //  QY_MCROOTLIST_DISPLAYCFG		*	pCfg					=			&pCfgParam->u.rootList;
	 TCHAR								sqlBuf[CONST_qyMaxSqlBufLen  +  1];
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;				//  2007/01/05
	 CRecordset							rs(  (  CDatabase  *  )pObjDb->pDb  );   int	 nFields;
	 CRecordset							rs_mac;  int  nFields_mac;
	 CDBVariant							varVals[20];
	 QY_SNMPOBJ_HEAD					snmpObjHead;
	 QY_SWITCHPORT_RCD					switchPort;
	 QY_SWITCHIFPORTSECURITY_RCD		portSecurity;
	 QY_SWITCHCONNECTEDDEV_RCD			connectedDev;
	 QY_SWITCHCONNECTEDPC_RCD			connectedPc;
	 QNM_MACDES_RCD						macDes;
	 QY_SWITCHSECUREMAC_RCD				secureMac;
	 char								mac0[CONST_qyMacLen  +  1],  ip[CONST_qyMaxIpLen  +  1];
	 char								switchMac[CONST_qyMacLen  +  1];
	 char								ip12[12  +  1];
	 TCHAR								devDescr[255  +  1];
	 int								cnt						=			0;
	 TCHAR								portStatusBuf[32]		=			_T(  ""  );
	 TCHAR								portSecureStatusBuf[32]	=			_T(  ""  );
	 int								nImage,  nSelectedImage;
	 TCHAR								displayName[512];
	 char								timeBuf[128];
	 unsigned  char						ucbMacExistsInPort		=			0;
	 unsigned  char						ucbRcdRetrieved			=			FALSE;
	 CQnmDb								rs_macDb,  db;
	 TCHAR					*			pStopString;
	 TCHAR								tBuf[1024];

	 if  (  !rs_macDb.getAvailableDb(  pObjDb->iDsnIndex  )  )  goto  errLabel;
	 if  (  !db.getAvailableDb(  pObjDb->iDsnIndex  )  )  goto  errLabel;
	 rs_mac.m_pDatabase  =  (  CDatabase  *  )rs_macDb.getAvailableDb(  pObjDb->iDsnIndex  );

	 try  {		
	 
		  if  (  !pMcView->var.m_superSel.u.rootTree.bRoot  )  {
				
			  	 int				iObjId				=	pMcView->var.m_superSel.u.rootTree.iHelpId;
				 //  int				ilastPortIfIndex	=	-1;

	 			 if  (  pObjIndex->objType  ==  CONST_objType_qySwitch  )  {

					 //  2005/11/06, 先取得交换机的MAC
					 myTChar2Str(  pObjIndex->objIdStr0,  switchMac,  sizeof(  switchMac  )  /  sizeof(  switchMac[0]  )  );

					 //  显示交换机中所有的端口信息和mac信息

					 pMcView->delAllColumns(  );
					 if  (  !pMcView->bAddColumns(  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_switchViewTable  )  )  )  goto  errLabel;

					 memset(  &snmpObjHead,  0,  sizeof(  snmpObjHead  )  );
					 if  (  !bGetSnmpObjHeadInfoBySth(  pObjDb->pDb,  switchMac,  NULL,  &snmpObjHead  )  )  goto  errLabel;
					 																//  0							1							2							3								4									5			
					 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "SELECT qySwitchPortTab.switchMac,qySwitchPortTab.portIfIndex,qySwitchPortTab.portIfDescr,qySwitchPortTab.portIfAdminStatus,qySwitchPortTab.portIfOperStatus,qySwitchPortTab.bridgePort"  )
																_T(  " ,qySwitchIfPortSecurityTab.iCpsIfPortSecurityEnable,qySwitchIfPortSecurityTab.iCpsIfPortSecurityStatus,qySwitchIfPortSecurityTab.iCpsIfMaxSecureMacAddr,qySwitchIfPortSecurityTab.iCpsIfCurrentSecureMacAddrCount"  )
										_T(  " from qySwitchPortTab left join qySwitchIfPortSecurityTab on (qySwitchIfPortSecurityTab.switchMac=qySwitchPortTab.switchMac and qySwitchIfPortSecurityTab.portIfIndex=qySwitchPortTab.portIfIndex ) where qySwitchPortTab.switchMac='%s' order by qySwitchPortTab.portIfIndex"  ),  pObjIndex->objIdStr0  );
		 			 traceLogA(  "%s",  sqlBuf  );
		 			 if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
						 traceLogA(  "rs open() failed."  );  goto  errLabel;
					 }
					 nFields  =  rs.GetODBCFieldCount(  );					 
					 																	//    0								      1									 2									 3									4								5									6		
					 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select distinct qySwitchConnectedPcTab.connectedMac,qySwitchConnectedPcTab.connectedIp,qySwitchConnectedPcTab.portIfIndex,qySwitchConnectedPcTab.ucbDirectConn,qySwitchConnectedPcTab.auditTime,qySwitchConnectedPcTab.firstTime,qySwitchConnectedPcTab.lastTime"  )
										//		  7				8
										_T(  " ,qyPcTab.mac0,qyPcTab.ip"  )
										//				  9												
										_T(  " ,qySwitchPortTab.switchMac"  )
										//				10				11				12					   
										_T(  " ,qnmMacDesTab.ip,qnmMacDesTab.devType,qnmMacDesTab.des0"  )
										//						13
										_T(  " ,qySwitchSecureMacTab.iCpsSecureMacAddrType"  )
										//
										_T(  " from ((((qySwitchConnectedPcTab left join qyPcTab on (qyPcTab.mac0=qySwitchConnectedPcTab.connectedMac or qyPcTab.mac1=qySwitchConnectedPcTab.connectedMac or qyPcTab.mac2=qySwitchConnectedPcTab.connectedMac))"  )
										_T(  " left join qySwitchPortTab on qySwitchPortTab.portIfPhysAddress=qySwitchConnectedPcTab.ConnectedMac)"  )
										_T(  " left join qnmMacDesTab on (qnmMacDesTab.mac=qySwitchConnectedPcTab.connectedMac))"  )
										_T(  " left join qySwitchSecureMacTab on (qySwitchSecureMacTab.switchMac=qySwitchConnectedPcTab.switchMac and qySwitchSecureMacTab.portIfIndex=qySwitchConnectedPcTab.portIfIndex and qySwitchSecureMacTab.secureMac=qySwitchConnectedPcTab.connectedMac))"  )
										//
										_T(  " where qySwitchConnectedPcTab.portIfIndex is not null and qySwitchConnectedPcTab.switchMac='%s' order by qySwitchConnectedPcTab.portIfIndex"  ),  
										//
										pObjIndex->objIdStr0  );
					 traceLogA(  "sqlBuf is [%.900s]",  sqlBuf  );
					 traceLogA(  "sqlBuf  +  900 is %s",  sqlBuf  +  900  );
					 if  (  !rs_mac.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
						 traceLogA(  "rs open() failed."  );  goto  errLabel;
					 }
					 nFields_mac  =  rs_mac.GetODBCFieldCount(  );					 
					 
					 for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
						  memset(  &switchPort,  0,  sizeof(  switchPort  )  ); 
						  memset(  &portSecurity,  0,  sizeof(  portSecurity  )  );
						  devDescr[0]  =  0;
								   
			  			  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   				  
			  			  index  =  0;  //  switchMac
						  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  switchPort.switchMac,  sizeof(  switchPort.switchMac  )  );  
			  			  index  ++  ;	//  iPortIfIndex,
			  			  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.iPortIfIndex  =  varVals[index].m_lVal;  }
			  			  index  ++  ;  //  portIfDescr,
						  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  switchPort.portIfDescr,  sizeof(  switchPort.portIfDescr  )  );  
			  			  index  ++  ;  //  iPortIfAdminStatus,
						  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  switchPort.iPortIfAdminStatus  =  _tcstol(  tBuf,  &pStopString,  10  );  
			  			  index  ++  ;  //  iPortIfOperStatus,
						  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  switchPort.iPortIfOperStatus  =  _tcstol(  tBuf,  &pStopString,  10  );  
			  			  index  ++  ;  //  iBridgePort,
			  			  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.iBridgePort  =  varVals[index].m_lVal;  }
						  index  ++  ;	//  qySwitchIfPortSecurityTab.iCpsIfPortSecurityEnable
						  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  portSecurity.ucbCpsIfPortSecurityEnable  =  (  (  varVals[index].m_lVal  ==  CONST_snmpTrue  )  ?  TRUE  :  FALSE  );  }
						  index  ++  ;  //  iCpsIfPortSecurityStatus
			  			  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  portSecurity.iCpsIfPortSecurityStatus  =  varVals[index].m_lVal;  }
						  index  ++  ;	//  iCpsIfMaxSecureMacAddr
						  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  portSecurity.iCpsIfMaxSecureMacAddr  =  varVals[index].m_lVal;  }
						  index  ++  ;  //  iCpsIfCurrentSecureMacAddrCount
			  			  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  portSecurity.iCpsIfCurrentSecureMacAddrCount  =  varVals[index].m_lVal;  }
						  index  ++  ;  //  
						
						  if  (  switchPort.iPortIfAdminStatus  ==  CONST_portStatus_down  )  lstrcpyn(  portStatusBuf,  qyGetDesByType1(  CONST_portAdminStatusTable,  switchPort.iPortIfAdminStatus  ),  mycountof(  portStatusBuf  )  );
						  else  lstrcpyn(  portStatusBuf,  qyGetDesByType1(  CONST_portOperStatusTable,  switchPort.iPortIfOperStatus  ),  mycountof(  portStatusBuf  )  );
						  if  (  portSecurity.ucbCpsIfPortSecurityEnable  )  _sntprintf(  portSecureStatusBuf,  mycountof(  portSecureStatusBuf  ),  _T(  "%s(%d/%d)"  ),  qyGetDesByType1(  CONST_iCpsIfPortSecurityStatusTable,  portSecurity.iCpsIfPortSecurityStatus  ),  portSecurity.iCpsIfCurrentSecureMacAddrCount,  portSecurity.iCpsIfMaxSecureMacAddr  );
						  else  portSecureStatusBuf[0]  =  0;
		  
						  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%d"  ),  switchPort.iPortIfIndex  );
						  
						  //  先填充连接设备信息
						  if  (  bGetConnectedDevInfoBySth(  db.getAvailableDb(  pObjDb->iDsnIndex  ),  switchPort.switchMac,  switchPort.iPortIfIndex,  0,   &connectedDev  )  )  {
							  ListCtrl.InsertItem(  cnt,  CString(  displayName  ).GetBuffer(  0  ),  pQyMc->cfg.image.nImage_connectedDev  );
							  _sntprintf(  devDescr,  mycountof(  devDescr  ),  _T(  "%s ( %s ) %s"  ),  CString(  connectedDev.platform  ),  CString(  connectedDev.address  ),  CString(  connectedDev.devicePortDescr  )  );
							  ListCtrl.SetItemText(  cnt,  2,  CString(  devDescr  ).GetBuffer(  0  )  );						  
							  cnt  ++  ;
						  }

						  //  再填充mac信息
						  ucbMacExistsInPort  =  FALSE;
						  for  (  ;  ucbRcdRetrieved  ||  !rs_mac.IsEOF(  );  rs_mac.MoveNext(  )  )  {
							   
							   if  (  !ucbRcdRetrieved  )  {
					   
								   for  (  index  =  0;  index  <  nFields_mac;  index  ++  )  rs_mac.GetFieldValue(  index,  varVals[index]  );

								   memset(  &connectedPc,  0,  sizeof(  connectedPc  )  ); 
								   memset(  &macDes,  0,  sizeof(  macDes  )  );
								   memset(  &secureMac,  0,  sizeof(  secureMac  )  );
								   mac0[0]  =  0;  ip[0]  =  0;
								   switchMac[0]  =  0;

								   index  =  0;  //  qySwitchConnectedPcTab.connectedMac	0
								   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  connectedPc.connectedMac,  sizeof(  connectedPc.connectedMac  )  );  
								   index  ++  ;	//  qySwitchConnectedPcTab.connectedIp		1
								   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  connectedPc.connectedIp  );  
								   index  ++  ;	//  qySwitchConnectedPcTab.portIfIndex		2
								   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  connectedPc.iPortIfIndex  =  varVals[index].m_lVal;  }			  			  						
								   index  ++  ;	//  qySwitchConnectedPcTab.ucbDirectConn	3
								   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  connectedPc.ucbDirectConn  =  (  unsigned  char  )_tcstol(  tBuf,  &pStopString,  10  );  
								   index  ++  ;	//  qySwitchConnectedPcTab.auditTime		4
								   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  connectedPc.auditTime,  sizeof(  connectedPc.auditTime  )  );  
								   index  ++  ;	//  qySwitchConnectedPcTab.firstTime		5
								   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  connectedPc.firstTime,  sizeof(  connectedPc.firstTime  )  );  
								   index  ++  ;	//  qySwitchConnectedPcTab.lastTime			6
								   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  connectedPc.lastTime,  sizeof(  connectedPc.lastTime  )  );  
								   index  ++  ;	//  qyPcTab.mac0							7
								   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  mac0,  sizeof(  mac0  )  );
								   index  ++  ;  //  qyPcTab.ip								8
								   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  ip  );
								   index  ++  ;	 //  qySwitchPortTab.switchMac				9
								   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  switchMac,  sizeof(  switchMac  )  );  
								   index  ++  ;	 //  qnmMacDesTab.ip						10
								   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  macDes.ip  );  
								   index  ++  ;	//  qnmMacDesTab.devType					11
								   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  macDes.devType,  tBuf,  mycountof(  macDes.devType  )  );  
								   index  ++  ;  //  qnmMacDesTab.des0						12
								   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  macDes.des0,  tBuf,  mycountof(  macDes.des0  )  );  
								   index  ++  ;  //  qySwitchSecureMacTab.iCpsSecureMacAddrType
								   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  secureMac.iCpsSecureMacAddrType  =  varVals[index].m_lVal;  }
								   index  ++  ;
								   
								   ucbRcdRetrieved  =  TRUE;

							   }
						  
							   if  (  connectedPc.iPortIfIndex  >  switchPort.iPortIfIndex  )  break;							   
							   ucbMacExistsInPort  =  TRUE;

							   _strlwr(  connectedPc.connectedMac  );	//  2004/05/04
							   getMacImages(  pQyMc,  &snmpObjHead,  &switchPort,  &portSecurity,  &connectedPc,  &secureMac,  &nImage,  &nSelectedImage  );
							   if  (  mac0[0]  )  _sntprintf(  devDescr,  mycountof(  devDescr  ),  _T(  "Computer  ( %s )"  ),  CString(  ip  )  );
							   else  if  (  switchMac[0]  )  getDesOfMac(  pObjDb,  connectedPc.connectedMac,  devDescr,  mycountof(  devDescr  ),  NULL  );
							   else  _sntprintf(  devDescr,  mycountof(  devDescr  ),  _T(  "%s %s"  ),  CString(  macDes.devType  ),  CString(  macDes.des0  )  );
							   _sntprintf(  devDescr,  mycountof(  devDescr  ),  _T(  "%s <-> %s"  ),  devDescr,  CString(  connectedPc.connectedIp  )  );
												
							   ListCtrl.InsertItem(  cnt,  CString(  displayName  ).GetBuffer(  0  ),  nImage  );
							   ListCtrl.SetItemText(  cnt,  1,  CString(  connectedPc.connectedMac  ).GetBuffer(  0  )  );
							   ListCtrl.SetItemText(  cnt,  2,  devDescr[0]  ?  devDescr  :  CString(  connectedPc.connectedIp  )  );
							   ListCtrl.SetItemText(  cnt,  3,  CString(  portStatusBuf  ).GetBuffer(  0  )  );
							   ListCtrl.SetItemText(  cnt,  4,  CString(  connectedPc.ucbDirectConn  ?  "Plugged"  :  ""  ).GetBuffer(  0  )  );
							   ListCtrl.SetItemText(  cnt,  5,  CString(  portSecureStatusBuf  ).GetBuffer(  0  )  );
							   ListCtrl.SetItemText(  cnt,  6,  CString(  qyGetDesByType1(  CONST_iCpsSecureMacAddrTypeTable,  secureMac.iCpsSecureMacAddrType  )  ).GetBuffer(  0  )  );    
							   ListCtrl.SetItemText(  cnt,  7,  CString(  qyDisplayTime(  connectedPc.auditTime,  timeBuf,  sizeof(  timeBuf  )  )  ).GetBuffer(  0  )  );
							   ListCtrl.SetItemText(  cnt,  8,  CString(  qyDisplayTime(  connectedPc.lastTime,  timeBuf,  sizeof(  timeBuf  )  )  ).GetBuffer(  0  )  );

							  if  (  pMcView->var.m_superSel.u.rootTree.selectedMac[0]  
								  &&  !_stricmp(  pMcView->var.m_superSel.u.rootTree.selectedMac,  connectedPc.connectedMac  )  )
							  {
								  ListCtrl.SetItemState(  cnt,  LVIS_SELECTED,  LVIS_SELECTED  );
								  ListCtrl.EnsureVisible(  cnt,  FALSE  );
								  pMcView->var.m_superSel.u.rootTree.selectedMac[0]  =  0;
							  }

							  ucbRcdRetrieved  =  FALSE;

							  cnt  ++  ;
						
							  if  (  rs_mac.IsEOF(  )  )  break;

						  }

						  //  实在没有mac信息，只好显示端口
						  if  (  !ucbMacExistsInPort  )  {
							  //  char			portStatusBuf[32]  =  "";

							  //  if  (  switchPort.iPortIfAdminStatus  ==  CONST_portStatus_down  )  safeStrnCpy(  qyGetDesByType1(  CONST_portAdminStatusTable,  switchPort.iPortIfAdminStatus  ),  portStatusBuf,  sizeof(  portStatusBuf  )  );
							  //  else  safeStrnCpy(  qyGetDesByType1(  CONST_portOperStatusTable,  switchPort.iPortIfOperStatus  ),  portStatusBuf,  sizeof(  portStatusBuf  )  );
							  //  if  (  portSecurity.ucbCpsIfPortSecurityEnable  )  _snprintf(  portStatusBuf,  sizeof(  portStatusBuf  ),  "%s/%s(%d)",  portStatusBuf,  qyGetDesByType1(  CONST_iCpsIfPortSecurityStatusTable,  portSecurity.iCpsIfPortSecurityStatus  ),  portSecurity.iCpsIfCurrentSecureMacAddrCount  );
							  
							  getSnmpPortImages(  pQyMc,  &switchPort,  &nImage,  &nSelectedImage  );
							  ListCtrl.InsertItem(  cnt,  CString(  displayName  ).GetBuffer(  0  ),  nImage  );
							  ListCtrl.SetItemText(  cnt,  3,  CString(  portStatusBuf  ).GetBuffer(  0  )  );
							  ListCtrl.SetItemText(  cnt,  5,  CString(  portSecureStatusBuf  ).GetBuffer(  0  )  );
							
							  cnt  ++  ;

						  }
						  						  
						  
									
					 }
					 
					 rs.Close(  );
					 rs_mac.Close(  );
				
				 }
				 
		  }
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bDisplayMcRootContent_switch failed."  )  );
		   goto  errLabel;
	}
		 
	 bRet  =  TRUE;

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );
	 if  (  rs_mac.IsOpen(  )  )  rs_mac.Close(  );
	
	 return  bRet;		

}


 BOOL  bDisplayMcRootContent_switchUsrConnection(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 //  LV_ITEM							lvi;
	 int								index					=			0;
	 //  QY_MCROOTLIST_DISPLAYCFG		*	pCfg					=			&pCfgParam->u.rootList;
	 TCHAR								sqlBuf[CONST_qyMaxSqlBufLen  +  1];
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;			//  2007/01/07
	 CRecordset							rs(  (  CDatabase  *  )pObjDb->pDb  );   int	 nFields;
	 CDBVariant							varVals[40];
	 QY_SNMPOBJ_HEAD					snmpObjHead;
	 QY_SWITCHPORT_RCD					switchPort;
	 QY_SWITCHIFPORTSECURITY_RCD		portSecurity;
	 QY_SWITCHCONNECTEDPC_RCD			connectedPc;
	 QY_SWITCHSECUREMAC_RCD				secureMac;
	 char								ip12[12  +  1];
	 //  char								devDescr[255  +  1];
	 int								cnt						=			0;
	 TCHAR								portStatusBuf[256]		=			_T(  ""  );
	 int								nImage,  nSelectedImage;
	 TCHAR								displayName[512];
	 char								displayTime[128];
	 int								i;
	 QNM_PC_INFO						pcInfo;
	 QNM_REG_INFO						regInfo;
	 QY_MC_QUERY						query;
	 TCHAR						*		pStopString;
	 char								switchMac[CONST_qyMacLen  +  1];
	 TCHAR								tBuf[1024];

	 try  {		
	 
		  if  (  pMcView->var.m_superSel.u.rootTree.bRoot  ||  pObjIndex->objType  !=  CONST_objType_qySwitch  )  goto  errLabel;

		  //  2005/11/06, 先取得交换机MAC
		  myTChar2Str(  pObjIndex->objIdStr0,  switchMac,  sizeof(  switchMac  )  /  sizeof(  switchMac[0]  )  );

		  memset(  &query,  0,  sizeof(  query  )  );
		  setQueryColumns(  pQyMc,0,  (  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpSimpleUsrQueryStruct  ),  &query  );

		  //  显示交换机中所有的端口信息和mac信息
		  pMcView->delAllColumns(  );
		  if  (  !pMcView->bAddColumns(  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_switchUsrConnectionViewTable  )  )  )  goto  errLabel;
		  if  (  !pMcView->bAddColumns(  query.columns  )  )  goto  errLabel;

		  memset(  &snmpObjHead,  0,  sizeof(  snmpObjHead  )  );
		  if  (  !bGetSnmpObjHeadInfoBySth(  pObjDb->pDb,  switchMac,  NULL,  &snmpObjHead  )  )  goto  errLabel;

			 										//						0						  1							 2							  3								    4								5								   6									7				                  8			                       9							    10                              11                    12          13			14									15
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "SELECT qySwitchPortTab.switchMac,qySwitchPortTab.portIfIndex,qySwitchPortTab.portIfDescr,qySwitchPortTab.portIfAdminStatus,qySwitchPortTab.portIfOperStatus,qySwitchPortTab.bridgePort,qySwitchConnectedPcTab.connectedMac,qySwitchConnectedPcTab.connectedIp,qySwitchConnectedPcTab.auditTime,qySwitchConnectedPcTab.firstTime,qySwitchConnectedPcTab.lastTime,qySwitchConnectedPcTab.ucbDirectConn,qyPcTab.ip,qyPcTab.pcName,qyPcTab.lastCommTime,qySwitchSecureMacTab.iCpsSecureMacAddrType"  )  );
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s %s"  ),  sqlBuf,  _T(  " ,qySwitchIfPortSecurityTab.iCpsIfPortSecurityEnable,qySwitchIfPortSecurityTab.iCpsIfPortSecurityStatus,qySwitchIfPortSecurityTab.iCpsIfCurrentSecureMacAddrCount"  )  );
		  for  (  i  =  0;  query.sqlColumns[i].type  !=  -1;  i  ++  )  {
			   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s,%s"  ),  sqlBuf,  query.sqlColumns[i].label  );
		  }		  
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s from ( ( ( ( ( qySwitchPortTab left join qySwitchIfPortSecurityTab on (qySwitchPortTab.switchMac=qySwitchIfPortSecurityTab.switchMac and qySwitchPortTab.portIfIndex=qySwitchIfPortSecurityTab.portIfIndex) ) left join qySwitchConnectedPcTab on (qySwitchPortTab.switchMac=qySwitchConnectedPcTab.switchMac and qySwitchPortTab.portIfIndex=qySwitchConnectedPcTab.portIfIndex)) left join qyPcTab on (  qySwitchConnectedPcTab.connectedMac=qyPcTab.mac0  or  qySwitchConnectedPcTab.connectedMac=qyPcTab.mac1  or  qySwitchConnectedPcTab.connectedMac=qyPcTab.mac2  )  ) left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0  ) left join qySwitchSecureMacTab on (qySwitchSecureMacTab.switchMac=qySwitchConnectedPcTab.switchMac and qySwitchSecureMacTab.portIfIndex=qySwitchConnectedPcTab.portIfIndex and qySwitchSecureMacTab.secureMac=qySwitchConnectedPcTab.connectedMac ) ) where qySwitchPortTab.switchMac='%s' order by qySwitchPortTab.portIfIndex"  ),  sqlBuf,  pObjIndex->objIdStr0  );
		  traceLogA(  "%.800s%s",  sqlBuf,  sqlBuf  +  800  );
		  if  (  !rs.Open( CRecordset::forwardOnly,  sqlBuf  )  )  {
			  traceLogA(  "rs open() failed."  );  goto  errLabel;
		  }
	  			 
		  nFields  =  rs.GetODBCFieldCount(  );
		  if  (  nFields  >  sizeof(  varVals  )  /  sizeof(  varVals[0]  )  )  {
			  //
			  //MACRO_qyAssert(  0,  _T(  "varVals 空间不够大"  )  );  
			  //
			  goto  errLabel;
		  }
		  //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
		  for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
			   memset(  &switchPort,  0,  sizeof(  switchPort  )  ); 
			   memset(  &portSecurity,  0,  sizeof(  portSecurity  )  );
			   memset(  &connectedPc,  0,  sizeof(  connectedPc  )  ); 
			   memset(  &secureMac,  0,  sizeof(  secureMac  )  );
			   memset(  &pcInfo,  0,  sizeof(  pcInfo  )  );
			   memset(  &regInfo,  0,  sizeof(  regInfo  )  );
			   //  devDescr[0]  =  0;
								   
			   for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   				  
			   index  =  0;		//  switchMac
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  switchPort.switchMac,  sizeof(  switchPort.switchMac  )  );  
			   index  ++  ;		//  iPortIfIndex,
			   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.iPortIfIndex  =  varVals[index].m_lVal;  }
			   index  ++  ;		//  portIfDescr,
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  switchPort.portIfDescr,  sizeof(  switchPort.portIfDescr  )  );  
			   index  ++  ;		//  iPortIfAdminStatus,
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  switchPort.iPortIfAdminStatus  =  _tcstol(  tBuf,  &pStopString,  10  );  
			   index  ++  ;		//  iPortIfOperStatus,
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  switchPort.iPortIfOperStatus  =  _tcstol(  tBuf,  &pStopString,  10  );  
			   index  ++  ;		//  iBridgePort,
			   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.iBridgePort  =  varVals[index].m_lVal;  }
			   index  ++  ;		//  qySwitchConnectedPcTab.connectedMac
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  connectedPc.connectedMac,  sizeof(  connectedPc.connectedMac  )  );  
			   index  ++  ;		//  qySwitchConnectedPcTab.connectedIp
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  connectedPc.connectedIp  );  
			   index  ++  ;		//  qySwitchConnectedPcTab.auditTime
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  connectedPc.auditTime,  sizeof(  connectedPc.auditTime  )  );    
			   index  ++  ;		//  qySwitchConnectedPcTab.firstTime
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  connectedPc.firstTime,  sizeof(  connectedPc.firstTime  )  );    
			   index  ++  ;		//  qySwitchConnectedPcTab.lastTime
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  connectedPc.lastTime,  sizeof(  connectedPc.lastTime  )  );    
			   index  ++  ;		//  qySwitchConnectedPcTab.ucbDirectConn
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  connectedPc.ucbDirectConn  =  _tcstol(  tBuf,  &pStopString,  10  )  ?  TRUE  :  FALSE;  
			   index  ++  ;		//	qyPcTab.ip
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  pcInfo.ip  );  //  2007/02/20
			   index  ++  ;		//	qyPcTab.pcName
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pcInfo.pcName,  sizeof(  pcInfo.pcName  )  );  
			   index  ++  ;		//  qyPcTab.lastCommTime
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pcInfo.lastCommTime,  sizeof(  pcInfo.lastCommTime  )  );  
			   index  ++  ;		//  qySwitchSecureMacTab.iCpsSecureMacAddrType
			   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  secureMac.iCpsSecureMacAddrType  =  varVals[index].m_lVal;  }
			   index  ++  ;	//  qySwitchIfPortSecurityTab.iCpsIfPortSecurityEnable
			   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  portSecurity.ucbCpsIfPortSecurityEnable  =  (  (  varVals[index].m_lVal  ==  CONST_snmpTrue  )  ?  TRUE  :  FALSE  );  }
			   index  ++  ;  //  iCpsIfPortSecurityStatus
			   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  portSecurity.iCpsIfPortSecurityStatus  =  varVals[index].m_lVal;  }
			   index  ++  ;  //  iCpsIfCurrentSecureMacAddrCount
			   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  portSecurity.iCpsIfCurrentSecureMacAddrCount  =  varVals[index].m_lVal;  }
			   index  ++  ;		//  取各用户信息
			   for  (  i  =  0;  query.columns[i].type  !=  -1;  i  ++  )  {
				    MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  (  TCHAR  *  )regInfo.u.cols[i],  tBuf,  sizeof(  regInfo.u.cols[i]  )  /  sizeof(  TCHAR  )  );    
				   index  ++  ;
			   }
			   
			   if  (  switchPort.iPortIfAdminStatus  ==  CONST_portStatus_down  )  lstrcpyn(  portStatusBuf,  qyGetDesByType1(  CONST_portAdminStatusTable,  switchPort.iPortIfAdminStatus  ),  mycountof(  portStatusBuf  )  );
			   else  lstrcpyn(  portStatusBuf,  qyGetDesByType1(  CONST_portOperStatusTable,  switchPort.iPortIfOperStatus  ),  mycountof(  portStatusBuf  )  );
		  
			   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%d"  ),  switchPort.iPortIfIndex  );
			   if  (  !qyDisplayTime(  pcInfo.lastCommTime,  displayTime,  sizeof(  displayTime  )  )  )  displayTime[0]  =  0;
						  
			   if  (  connectedPc.connectedMac[0]  )  {
				   _strlwr(  connectedPc.connectedMac  );
				   getMacImages(  pQyMc,  &snmpObjHead,  &switchPort,  &portSecurity,  &connectedPc,  &secureMac,  &nImage,  &nSelectedImage  );
				   //  if  (  getDesOfMac(  pObjDb->pDb,  connectedPc.connectedMac,  devDescr,  sizeof(  devDescr  ),  NULL  )  )  devDescr[0]  =  0;
				   ListCtrl.InsertItem(  cnt,  CString(  displayName  ).GetBuffer(  0  ),  nImage  );
				   ListCtrl.SetItemText(  cnt,  1,  CString(  connectedPc.connectedMac  ).GetBuffer(  0  )  );
				   ListCtrl.SetItemText(  cnt,  2,  CString(  pcInfo.ip  ).GetBuffer(  0  )  );
				   ListCtrl.SetItemText(  cnt,  3,  CString(  pcInfo.pcName  ).GetBuffer(  0  )  );
				   ListCtrl.SetItemText(  cnt,  4,  CString(  displayTime  ).GetBuffer(  0  )  );
				   index  =  5;				   
				   for  (  i  =  0;  query.columns[i].type  !=  -1;  i  ++  )  {
					    ListCtrl.SetItemText(  cnt,  i  +  index,  (  TCHAR  *  )regInfo.u.cols[i]  );						
				   }
				   
				   }
			   else  {
				     getSnmpPortImages(  pQyMc,  &switchPort,  &nImage,  &nSelectedImage  );
					 ListCtrl.InsertItem(  cnt,  CString(  displayName  ),  nImage  );
			   }
						  						  
			   cnt  ++  ;
									
		  }
				
		  rs.Close(  );
		  
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bDisplayMcRootContent_switchUsrConnection failed."  )  );
		   goto  errLabel;
	}
		 
	 bRet  =  TRUE;

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	 return  bRet;		

}


 BOOL  bDisplayMcRootContent_switchNetworkSpeed(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 //  LV_ITEM							lvi;
	 int								index					=			0;
	 //  QY_MCROOTLIST_DISPLAYCFG		*	pCfg					=			&pCfgParam->u.rootList;
	 TCHAR								sqlBuf[1024];
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;			//  2007/01/05
	 CRecordset							rs(  (  CDatabase  *  )pObjDb->pDb  );   int	 nFields;
	 CDBVariant							varVals[20];	 
	 QY_SWITCHPORT_RCD					switchPort;
	 int								cnt						=			0;
	 TCHAR								portStatusBuf[256]		=			_T(  ""  );
	 int								nImage,  nSelectedImage;
	 TCHAR								displayName[512];
	 char								displayTime[128];
	 TCHAR						*		pStopString;
	 TCHAR								tBuf[1024];
	 
	 try  {		
	 
		  if  (  pMcView->var.m_superSel.u.rootTree.bRoot  ||  pObjIndex->objType  !=  CONST_objType_qySwitch  )  goto  errLabel;
		  //  显示交换机中所有的端口信息和mac信息
		  pMcView->delAllColumns(  );
		  if  (  !pMcView->bAddColumns(  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_switchNetworkSpeedViewTable  )  )  )  goto  errLabel;
			 																//  0							1							2							3								 4								5								6									7							  8								  9		
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "SELECT qySwitchPortTab.switchMac,qySwitchPortTab.portIfIndex,qySwitchPortTab.portIfAdminStatus,qySwitchPortTab.portIfOperStatus,qySwitchPortTab.portIfSpeedInK,qySwitchPortTab.portIfInSpeedInK,qySwitchPortTab.portIfOutSpeedInK,qySwitchPortTab.portIfInOctets,qySwitchPortTab.portIfOutOctets,qySwitchPortTab.lastTime"  )  );
		  //  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s from ( ( qySwitchPortTab left join qySwitchConnectedPcTab on (qySwitchPortTab.switchMac=qySwitchConnectedPcTab.switchMac and qySwitchPortTab.portIfIndex=qySwitchConnectedPcTab.portIfIndex)) left join qyPcTab on qySwitchConnectedPcTab.connectedMac=qyPcTab.mac0) left join qyPcRegInfoTab on qySwitchConnectedPcTab.connectedMac=qyPcRegInfoTab.mac0 where qySwitchPortTab.switchMac='%s' order by qySwitchPortTab.portIfIndex",  sqlBuf,  pObjIndex->objIdStr0  );
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s from qySwitchPortTab where qySwitchPortTab.switchMac='%s' order by qySwitchPortTab.portIfIndex"  ),  sqlBuf,  pObjIndex->objIdStr0  );
		  traceLogA(  "%s",  sqlBuf  );
		  if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  )  )  )  {
			  traceLogA(  "rs open() failed."  );  goto  errLabel;
		  }
	  			 
		  nFields  =  rs.GetODBCFieldCount(  );
		  //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
		  for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
			   memset(  &switchPort,  0,  sizeof(  switchPort  )  ); 
								   
			   for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   				  
			   index  =  0;		//  switchMac
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  switchPort.switchMac,  sizeof(  switchPort.switchMac  )  );  
			   index  ++  ;		//  iPortIfIndex,
			   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.iPortIfIndex  =  varVals[index].m_lVal;  }
			   index  ++  ;		//  iPortIfAdminStatus,
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  switchPort.iPortIfAdminStatus  =  _tcstol(  tBuf,  &pStopString,  10  );  
			   index  ++  ;		//  iPortIfOperStatus,
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  switchPort.iPortIfOperStatus  =  _tcstol(  tBuf,  &pStopString,  10  );  
			   index  ++  ;		//  qySwitchPortTab.portIfSpeedInK
			   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.iPortIfSpeedInK  =  varVals[index].m_lVal;  }
			   index  ++  ;		//  qySwitchPortTab.portIfInSpeedInK
			   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.iPortIfInSpeedInK  =  varVals[index].m_lVal;  }
			   index  ++  ;		//  qySwitchPortTab.portIfOutSpeedInK
			   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.iPortIfOutSpeedInK  =  varVals[index].m_lVal;  }
			   index  ++  ;		//  qySwitchPortTab.portIfInOctets
			   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.i64PortIfInOctets  =  varVals[index].m_lVal;  }
			   index  ++  ;		//  qySwitchPortTab.portIfOutOctets
			   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.i64PortIfOutOctets  =  varVals[index].m_lVal;  }
			   index  ++  ;		//  lastTime
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  switchPort.lastTime,  sizeof(  switchPort.lastTime  )  );  
			   index  ++  ;		
			   
			   if  (  switchPort.iPortIfAdminStatus  ==  CONST_portStatus_down  )  lstrcpyn(  portStatusBuf,  qyGetDesByType1(  CONST_portAdminStatusTable,  switchPort.iPortIfAdminStatus  ),  mycountof(  portStatusBuf  )  );
			   else  lstrcpyn(  portStatusBuf,  qyGetDesByType1(  CONST_portOperStatusTable,  switchPort.iPortIfOperStatus  ),  mycountof(  portStatusBuf  )  );
						   
			   index  =  0;  
			   getSnmpPortImages(  pQyMc,  &switchPort,  &nImage,  &nSelectedImage  );
			   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%d"  ),  switchPort.iPortIfIndex  );
			   ListCtrl.InsertItem(  cnt,  CString(  displayName  ),  nImage  );
			   index  ++  ;
			   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%d"  ),  switchPort.iPortIfSpeedInK  );
			   ListCtrl.SetItemText(  cnt,  index,  CString(  displayName  )  );
			   index  ++  ;
			   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%d"  ),  switchPort.iPortIfInSpeedInK  );
			   ListCtrl.SetItemText(  cnt,  index,  CString(  displayName  )  );
			   index  ++  ;
			   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%d"  ),  switchPort.iPortIfOutSpeedInK  );
			   ListCtrl.SetItemText(  cnt,  index,  CString(  displayName  )  );
			   index  ++  ;					//  这里先将进出字节数的显示修正了，以后应将数据结构的类型作无符号调整，切切。2004/01/08
			   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u"  ),  switchPort.i64PortIfInOctets  );
			   ListCtrl.SetItemText(  cnt,  index,  CString(  displayName  )  );
			   index  ++  ;
			   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u"  ),  switchPort.i64PortIfOutOctets  );
			   ListCtrl.SetItemText(  cnt,  index,  CString(  displayName  )  );
			   index  ++  ;
			   if  (  !qyDisplayTime(  switchPort.lastTime,  displayTime,  sizeof(  displayTime  )  )  )  displayTime[0]  =  0;
			   ListCtrl.SetItemText(  cnt,  index,  CString(  displayTime  )  );
			   index  ++  ;
			   
			   cnt  ++  ;
									
		  }
				
		  rs.Close(  );
		  
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bDisplayMcRootContent_switchNetworkSpeed failed."  )  );
		   goto  errLabel;
	}
		 
	 bRet  =  TRUE;

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	 return  bRet;		

}




 BOOL  bDisplayMcRootContent_switchPort(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 //  LV_ITEM							lvi;
	 int								index					=			0;
	 //  QY_MCROOTLIST_DISPLAYCFG		*	pCfg					=			&pCfgParam->u.rootList;
	 TCHAR								sqlBuf[CONST_qyMaxSqlBufLen  +  1];
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;			//  2007/01/05
	 CRecordset							rs(  (  CDatabase  *  )pObjDb->pDb  );   int	 nFields;
	 CRecordset							rs_mac;  int  nFields_mac;
	 CDBVariant							varVals[20];
	 QY_SNMPOBJ_HEAD					snmpObjHead;
	 QY_SWITCHPORT_RCD					switchPort;
	 QY_SWITCHIFPORTSECURITY_RCD		portSecurity;
	 QY_SWITCHCONNECTEDDEV_RCD			connectedDev;
	 QY_SWITCHCONNECTEDPC_RCD			connectedPc;
	 QNM_MACDES_RCD						macDes;
	 QY_SWITCHSECUREMAC_RCD				secureMac;
	 char								mac0[CONST_qyMacLen  +  1],  ip[CONST_qyMaxIpLen  +  1];
	 char								switchMac[CONST_qyMacLen  +  1];
	 char								ip12[12  +  1];
	 TCHAR								devDescr[255  +  1];
	 int								cnt						=			0;
	 TCHAR								portStatusBuf[32]		=			_T(  ""  );
	 TCHAR								portSecureStatusBuf[32]	=			_T(  ""  );
	 int								nImage,  nSelectedImage;
	 TCHAR								displayName[512];
	 char								timeBuf[128];
	 unsigned  char						ucbMacExistsInPort		=			0;
	 unsigned  char						ucbRcdRetrieved			=			FALSE;
	 CQnmDb								rs_macDb,  db;
	 TCHAR						*		pStopString;
	 TCHAR								tBuf[1024];

	 if  (  !rs_macDb.getAvailableDb(  pObjDb->iDsnIndex  )  )  goto  errLabel;
	 if  (  !db.getAvailableDb(  pObjDb->iDsnIndex  )  )  goto  errLabel;
	 rs_mac.m_pDatabase  =  (  CDatabase  *  )rs_macDb.getAvailableDb(  pObjDb->iDsnIndex  );

	 try  {		

		 if  (  pObjIndex->objType  ==  CONST_objType_qySwitchPort  )  {

			 //  2005/11/06，先取得交换机MAC
			 myTChar2Str(  pObjIndex->objIdStr0,  switchMac,  sizeof(  switchMac  )  /  sizeof(  switchMac[0]  )  );
					 
			 //  显示一个端口的关联信息
			 pMcView->delAllColumns(  );
			 if  (  !pMcView->bAddColumns(  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_switchPortViewTable  )  )  )  goto  errLabel;

			 memset(  &snmpObjHead,  0,  sizeof(  snmpObjHead  )  );
			 if  (  !bGetSnmpObjHeadInfoBySth(  pObjDb->pDb,  switchMac,  NULL,  &snmpObjHead  )  )  goto  errLabel;
			 																//  0							1							2							3								4									5			
			 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "SELECT qySwitchPortTab.switchMac,qySwitchPortTab.portIfIndex,qySwitchPortTab.portIfDescr,qySwitchPortTab.portIfAdminStatus,qySwitchPortTab.portIfOperStatus,qySwitchPortTab.bridgePort"  )
														_T(  " ,qySwitchIfPortSecurityTab.iCpsIfPortSecurityEnable,qySwitchIfPortSecurityTab.iCpsIfPortSecurityStatus,qySwitchIfPortSecurityTab.iCpsIfMaxSecureMacAddr,qySwitchIfPortSecurityTab.iCpsIfCurrentSecureMacAddrCount"  )
														_T(  " from qySwitchPortTab left join qySwitchIfPortSecurityTab on (qySwitchPortTab.switchMac=qySwitchIfPortSecurityTab.switchMac and qySwitchPortTab.portIfIndex=qySwitchIfPortSecurityTab.portIfIndex ) where qySwitchPortTab.switchMac='%s' and qySwitchPortTab.portIfIndex=%d order by qySwitchPortTab.portIfIndex"  ),  pObjIndex->objIdStr0,  pObjIndex->objId0  );
 			 traceLogA(  "%s",  sqlBuf  );
 			 if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  )  )  )  {
				 traceLogA(  "rs open() failed."  );  goto  errLabel;
			 }
			 nFields  =  rs.GetODBCFieldCount(  );					 
					 																	//    0								      1									 2									 3									4								5									6		
			 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select distinct qySwitchConnectedPcTab.connectedMac,qySwitchConnectedPcTab.connectedIp,qySwitchConnectedPcTab.portIfIndex,qySwitchConnectedPcTab.ucbDirectConn,qySwitchConnectedPcTab.auditTime,qySwitchConnectedPcTab.firstTime,qySwitchConnectedPcTab.lastTime"  )
									//		  7				8
									_T(  " ,qyPcTab.mac0,qyPcTab.ip"  )
									//				  9												
									_T(  " ,qySwitchPortTab.switchMac"  )
									//				10				11				12					   
									_T(  " ,qnmMacDesTab.ip,qnmMacDesTab.devType,qnmMacDesTab.des0"  )
									//						13
									_T(  " ,qySwitchSecureMacTab.iCpsSecureMacAddrType"  )
									//
									_T(  " from ((((qySwitchConnectedPcTab left join qyPcTab on (qyPcTab.mac0=qySwitchConnectedPcTab.connectedMac or qyPcTab.mac1=qySwitchConnectedPcTab.connectedMac or qyPcTab.mac2=qySwitchConnectedPcTab.connectedMac))"  )
									_T(  " left join qySwitchPortTab on qySwitchPortTab.portIfPhysAddress=qySwitchConnectedPcTab.ConnectedMac)"  )
									_T(  " left join qnmMacDesTab on (qnmMacDesTab.mac=qySwitchConnectedPcTab.connectedMac))"  )
									_T(  " left join qySwitchSecureMacTab on (qySwitchSecureMacTab.switchMac=qySwitchConnectedPcTab.switchMac and qySwitchSecureMacTab.portIfIndex=qySwitchConnectedPcTab.portIfIndex and qySwitchSecureMacTab.secureMac=qySwitchConnectedPcTab.connectedMac))"  )
									//
									_T(  " where qySwitchConnectedPcTab.portIfIndex is not null and qySwitchConnectedPcTab.switchMac='%s' and qySwitchConnectedPcTab.portIfIndex=%d order by qySwitchConnectedPcTab.portIfIndex"  ),  
									//
									pObjIndex->objIdStr0,  pObjIndex->objId0  );
			 traceLogA(  "sqlBuf is [%.900s]",  sqlBuf  );
			 traceLogA(  "sqlBuf  +  900 is %s",  sqlBuf  +  900  );
			 if  (  !rs_mac.Open( CRecordset::forwardOnly,  CString(  sqlBuf  )  )  )  {
				 traceLogA(  "rs open() failed."  );  goto  errLabel;
			 }
			 nFields_mac  =  rs_mac.GetODBCFieldCount(  );					 
					 
			 for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
				  memset(  &switchPort,  0,  sizeof(  switchPort  )  ); 
				  memset(  &portSecurity,  0,  sizeof(  portSecurity  )  );
				  devDescr[0]  =  0;
								   
	  			  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   				  
	  			  index  =  0;  //  switchMac
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  switchPort.switchMac,  sizeof(  switchPort.switchMac  )  );  
	  			  index  ++  ;	//  iPortIfIndex,
	  			  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.iPortIfIndex  =  varVals[index].m_lVal;  }
	  			  index  ++  ;  //  portIfDescr,
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  switchPort.portIfDescr,  sizeof(  switchPort.portIfDescr  )  );  
	  			  index  ++  ;  //  iPortIfAdminStatus,
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  switchPort.iPortIfAdminStatus  =  _tcstol(  tBuf,  &pStopString,  10  );  
	  			  index  ++  ;  //  iPortIfOperStatus,
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  switchPort.iPortIfOperStatus  =  _tcstol(  tBuf,  &pStopString,  10  );  
	  			  index  ++  ;  //  iBridgePort,
	  			  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.iBridgePort  =  varVals[index].m_lVal;  }
				  index  ++  ;  //  qySwitchIfPortSecurityTab.iCpsIfPortSecurityEnable
				  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  portSecurity.ucbCpsIfPortSecurityEnable  =  (  (  varVals[index].m_lVal  ==  CONST_snmpTrue  )  ?  TRUE  :  FALSE  );  }
				  index  ++  ;  //  qySwitchIfPortSecurityTab.iCpsIfPortSecurityStatus
				  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  portSecurity.iCpsIfPortSecurityStatus  =  varVals[index].m_lVal;  }
				  index  ++  ;	//  iCpsIfMaxSecureMacAddr
				  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  portSecurity.iCpsIfMaxSecureMacAddr  =  varVals[index].m_lVal;  }
				  index  ++  ;  //  iCpsIfCurrentSecureMacAddrCount
				  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  portSecurity.iCpsIfCurrentSecureMacAddrCount  =  varVals[index].m_lVal;  }
				  index  ++  ;  //  
					
				  if  (  switchPort.iPortIfAdminStatus  ==  CONST_portStatus_down  )  lstrcpyn(  portStatusBuf,  qyGetDesByType1(  CONST_portAdminStatusTable,  switchPort.iPortIfAdminStatus  ),  mycountof(  portStatusBuf  )  );
				  else  lstrcpyn(  portStatusBuf,  qyGetDesByType1(  CONST_portOperStatusTable,  switchPort.iPortIfOperStatus  ),  mycountof(  portStatusBuf  )  );
				  if  (  portSecurity.ucbCpsIfPortSecurityEnable  )  _sntprintf(  portSecureStatusBuf,  mycountof(  portSecureStatusBuf  ),  _T(  "%s(%d/%d)"  ),  qyGetDesByType1(  CONST_iCpsIfPortSecurityStatusTable,  portSecurity.iCpsIfPortSecurityStatus  ),  portSecurity.iCpsIfCurrentSecureMacAddrCount,  portSecurity.iCpsIfMaxSecureMacAddr  );
				  else  portSecureStatusBuf[0]  =  0;
	  
				  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%d"  ),  switchPort.iPortIfIndex  );
						  
				  //  先填充连接设备信息
				  if  (  bGetConnectedDevInfoBySth(  pObjDb->pDb,  switchPort.switchMac,  switchPort.iPortIfIndex,  0,   &connectedDev  )  )  {
	  				  ListCtrl.InsertItem(  cnt,  CString(  ""  ),  pQyMc->cfg.image.nImage_connectedDev  );
				 	  _sntprintf(  devDescr,  mycountof(  devDescr  ),  _T(  "%s ( %s ) %s"  ),  CString(  connectedDev.platform  ),  CString(  connectedDev.address  ),  CString(  connectedDev.devicePortDescr  )  );
				 	  ListCtrl.SetItemText(  cnt,  1,  CString(  devDescr  )  );						  
				 	  cnt  ++  ;
				  }

				  //  再填充mac信息
				  ucbMacExistsInPort  =  FALSE;
				  for  (  ;  ucbRcdRetrieved  ||  !rs_mac.IsEOF(  );  rs_mac.MoveNext(  )  )  {
						   
					   if  (  !ucbRcdRetrieved  )  {
					   
						   for  (  index  =  0;  index  <  nFields_mac;  index  ++  )  rs_mac.GetFieldValue(  index,  varVals[index]  );

						   memset(  &connectedPc,  0,  sizeof(  connectedPc  )  ); 
						   memset(  &macDes,  0,  sizeof(  macDes  )  );
						   memset(  &secureMac,  0,  sizeof(  secureMac  )  );
						   mac0[0]  =  0;  ip[0]  =  0;
						   switchMac[0]  =  0;

						   index  =  0;  //  qySwitchConnectedPcTab.connectedMac	0
						   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  connectedPc.connectedMac,  sizeof(  connectedPc.connectedMac  )  );  
						   index  ++  ;	//  qySwitchConnectedPcTab.connectedIp		1
						   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  connectedPc.connectedIp  );  
						   index  ++  ;	//  qySwitchConnectedPcTab.portIfIndex		2
						   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  connectedPc.iPortIfIndex  =  varVals[index].m_lVal;  }			  			  						
						   index  ++  ;	//  qySwitchConnectedPcTab.ucbDirectConn	3
						   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  connectedPc.ucbDirectConn  =  (  unsigned  char  )_tcstol(  tBuf,  &pStopString,  10  );  
						   index  ++  ;	//  qySwitchConnectedPcTab.auditTime		4
						   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  connectedPc.auditTime,  sizeof(  connectedPc.auditTime  )  );  
						   index  ++  ;	//  qySwitchConnectedPcTab.firstTime		5
						   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  connectedPc.firstTime,  sizeof(  connectedPc.firstTime  )  );  
						   index  ++  ;	//  qySwitchConnectedPcTab.lastTime			6
						   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  connectedPc.lastTime,  sizeof(  connectedPc.lastTime  )  );  
						   index  ++  ;	//  qyPcTab.mac0							7
						   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  mac0,  sizeof(  mac0  )  );
						   index  ++  ;  //  qyPcTab.ip								8
						   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  ip  );	//  2007/02/20
						   index  ++  ;	 //  qySwitchPortTab.switchMac				9
						   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  switchMac,  sizeof(  switchMac  )  );  
						   index  ++  ;	 //  qnmMacDesTab.ip						10
						   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  macDes.ip  );  
						   index  ++  ;	//  qnmMacDesTab.devType					11
						   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  macDes.devType,  tBuf,  mycountof(  macDes.devType  )  );  
						   index  ++  ;  //  qnmMacDesTab.des0						12
						   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  macDes.des0,  tBuf,  mycountof(  macDes.des0  )  );  
						   index  ++  ;  //  qySwitchSecureMacTab.iCpsSecureMacAddrType
						   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  secureMac.iCpsSecureMacAddrType  =  varVals[index].m_lVal;  }
						   index  ++  ;
							   
						   ucbRcdRetrieved  =  TRUE;

					   }
						  
					   if  (  connectedPc.iPortIfIndex  >  switchPort.iPortIfIndex  )  break;							   
					   ucbMacExistsInPort  =  TRUE;

					   _strlwr(  connectedPc.connectedMac  );	//  2004/05/04
					   getMacImages(  pQyMc,  &snmpObjHead,  &switchPort,  &portSecurity,  &connectedPc,  &secureMac,  &nImage,  &nSelectedImage  );
					   if  (  mac0[0]  )  _sntprintf(  devDescr,  mycountof(  devDescr  ),  _T(  "Computer  ( %s )"  ),  CString(  ip  )  );
					   else  if  (  switchMac[0]  )  getDesOfMac(  pObjDb,  connectedPc.connectedMac,  devDescr,  mycountof(  devDescr  ),  NULL  );
					   else  _sntprintf(  devDescr,  mycountof(  devDescr  ),  _T(  "%s %s"  ),  CString(  macDes.devType  ),  CString(  macDes.des0  )  );

					   _sntprintf(  devDescr,  mycountof(  devDescr  ),  _T(  "%s <-> %s"  ),  devDescr,  CString(  connectedPc.connectedIp  )  );

					   ListCtrl.InsertItem(  cnt,  CString(  connectedPc.connectedIp  ),  nImage  );
					   ListCtrl.SetItemText(  cnt,  0,  CString(  connectedPc.connectedMac  )  );
					   ListCtrl.SetItemText(  cnt,  1,  devDescr[0]  ?  devDescr  :  CString(  connectedPc.connectedIp  )  );
					   ListCtrl.SetItemText(  cnt,  2,  connectedPc.ucbDirectConn  ?  _T(  "Plugged"  )  :  _T(  ""  )  );
					   ListCtrl.SetItemText(  cnt,  3,  portSecureStatusBuf  );
					   ListCtrl.SetItemText(  cnt,  4,  qyGetDesByType1(  CONST_iCpsSecureMacAddrTypeTable,  secureMac.iCpsSecureMacAddrType  )  );    
					   ListCtrl.SetItemText(  cnt,  5,  CString(  qyDisplayTime(  connectedPc.auditTime,  timeBuf,  sizeof(  timeBuf  )  )  )  );
					   ListCtrl.SetItemText(  cnt,  6,  CString(  qyDisplayTime(  connectedPc.lastTime,  timeBuf,  sizeof(  timeBuf  )  )  )  );

					  ucbRcdRetrieved  =  FALSE;

					  cnt  ++  ;
						
					  if  (  rs_mac.IsEOF(  )  )  break;
					
				  }

				  //  实在没有mac信息，不显示
				  if  (  !ucbMacExistsInPort  )  {
					  ;
				  }
				  }
							
				  rs.Close(  );
				  rs_mac.Close(  );
		
			}
			}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bDisplayMcRootContent_switchPort failed."  )  );
		   goto  errLabel;
	}
		 
	 bRet  =  TRUE;

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );
	 if  (  rs_mac.IsOpen(  )  )  rs_mac.Close(  );
	
	 return  bRet;		

}




 BOOL  bDisplayMcRootContent_switchPortUsrConnection(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 //  LV_ITEM							lvi;
	 int								index					=			0;
	 //  QY_MCROOTLIST_DISPLAYCFG		*	pCfg					=			&pCfgParam->u.rootList;
	 TCHAR								sqlBuf[CONST_maxSqlBufLen  +  1];
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;			//  2007/01/05
	 CRecordset							rs(  (  CDatabase  *  )pObjDb->pDb  );   int	 nFields;
	 CDBVariant							varVals[40];
	 QY_SNMPOBJ_HEAD					snmpObjHead;
	 QY_SWITCHPORT_RCD					switchPort;
	 QY_SWITCHIFPORTSECURITY_RCD		portSecurity;
	 QY_SWITCHCONNECTEDPC_RCD			connectedPc;
	 QY_SWITCHSECUREMAC_RCD				secureMac;
	 char								ip12[12  +  1];
	 int								cnt						=			0;
	 TCHAR								portStatusBuf[256]		=			_T(  ""  );
	 int								nImage,  nSelectedImage;
	 int								i;
	 QNM_PC_INFO						pcInfo;
	 QNM_REG_INFO						regInfo;
	 char								displayTime[128];
	 QY_MC_QUERY						query;
	 TCHAR					*			pStopString;
	 char								switchMac[CONST_qyMacLen  +  1];
	 TCHAR								tBuf[1024];
	
	
	 try  {		
	 
		  
		 if  (  pObjIndex->objType  ==  CONST_objType_qySwitchPort  )  {
			
			 //  2005/11/06,
			 myTChar2Str(  pObjIndex->objIdStr0,  switchMac,  sizeof(  switchMac  )  /  sizeof(  switchMac[0]  )  );

			 memset(  &query,  0,  sizeof(  query  )  );
			 setQueryColumns(  pQyMc,0,  (  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpSimpleUsrQueryStruct  ),  &query  );

			 //  显示一个端口的关联信息
			 pMcView->delAllColumns(  );
			 if  (  !pMcView->bAddColumns(  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_switchPortUsrConnectionViewTable  )  )  )  goto  errLabel;
			 if  (  !pMcView->bAddColumns(  query.columns  )  )  goto  errLabel;

			 memset(  &snmpObjHead,  0,  sizeof(  snmpObjHead  )  );
			 if  (  !bGetSnmpObjHeadInfoBySth(  pObjDb->pDb,  switchMac,  NULL,  &snmpObjHead  )  )  goto  errLabel;
						 		
			 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "SELECT qySwitchPortTab.portIfAdminStatus,qySwitchPortTab.portIfOperStatus,qySwitchConnectedPcTab.connectedMac,qySwitchConnectedPcTab.connectedIp,qySwitchConnectedPcTab.switchMac,qySwitchConnectedPcTab.portIfIndex,qySwitchConnectedPcTab.auditTime,qySwitchConnectedPcTab.firstTime,qySwitchConnectedPcTab.lastTime,qySwitchConnectedPcTab.ucbDirectConn,qySwitchConnectedPcTab.comment0,qyPcTab.ip,qyPcTab.pcName,qyPcTab.lastCommTime,qySwitchSecureMacTab.iCpsSecureMacAddrType"  )  );
			 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s %s"  ),  sqlBuf,  _T(  " ,qySwitchIfPortSecurityTab.iCpsIfPortSecurityEnable,qySwitchIfPortSecurityTab.iCpsIfPortSecurityStatus,qySwitchIfPortSecurityTab.iCpsIfCurrentSecureMacAddrCount"  )  );
			 for  (  i  =  0;  query.sqlColumns[i].type  !=  -1;  i  ++  )  {
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s,%s"  ),  sqlBuf,  query.sqlColumns[i].label  );
		  	 }		  	 
			 //  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s from ( ( qySwitchConnectedPcTab left join qySwitchPortTab on (qySwitchPortTab.switchMac=qySwitchConnectedPcTab.switchMac and qySwitchPortTab.portIfIndex=qySwitchConnectedPcTab.portIfIndex ) ) left join qyPcTab on qySwitchConnectedPcTab.connectedMac=qyPcTab.mac0) left join qyPcRegInfoTab on qySwitchConnectedPcTab.connectedMac=qyPcRegInfoTab.mac0 where qySwitchConnectedPcTab.switchMac='%s' and qySwitchConnectedPcTab.portIfIndex=%d",  sqlBuf,  pObjIndex->objIdStr0,  pObjIndex->objId0  );
			 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s from ( ( ( ( ( qySwitchConnectedPcTab left join qySwitchPortTab on (qySwitchPortTab.switchMac=qySwitchConnectedPcTab.switchMac and qySwitchPortTab.portIfIndex=qySwitchConnectedPcTab.portIfIndex ) ) left join qySwitchIfPortSecurityTab on ( qySwitchPortTab.switchMac=qySwitchIfPortSecurityTab.switchMac and qySwitchPortTab.portIfIndex=qySwitchIfPortSecurityTab.portIfIndex ) ) left join qyPcTab on (  qySwitchConnectedPcTab.connectedMac=qyPcTab.mac0  or  qySwitchConnectedPcTab.connectedMac=qyPcTab.mac1  or  qySwitchConnectedPcTab.connectedMac=qyPcTab.mac2  )  ) left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0 ) left join qySwitchSecureMacTab on (qySwitchSecureMacTab.switchMac=qySwitchConnectedPcTab.switchMac and qySwitchSecureMacTab.portIfIndex=qySwitchConnectedPcTab.portIfIndex and qySwitchSecureMacTab.secureMac=qySwitchConnectedPcTab.connectedMac) ) where qySwitchConnectedPcTab.switchMac='%s' and qySwitchConnectedPcTab.portIfIndex=%d"  ),  sqlBuf,  pObjIndex->objIdStr0,  pObjIndex->objId0  );
			 if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  )  )  )  {
				 traceLogA(  "rs open() failed."  );  goto  errLabel;
			 }
	  					
			 nFields  =  rs.GetODBCFieldCount(  );
			 if  (  nFields  >  sizeof(  varVals  )  /  sizeof(  varVals[0]  )  )  {
				 MACRO_qyAssert(  0,  _T(  "varVals 空间太小"  )  );  goto  errLabel;
			 }			 
			 for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
				  memset(  &switchPort,  0,  sizeof(  switchPort  )  ); 
				  memset(  &portSecurity,  0,  sizeof(  portSecurity  )  );
				  memset(  &connectedPc,  0,  sizeof(  connectedPc  )  ); 
				  memset(  &secureMac,  0,  sizeof(  secureMac  )  );
				  memset(  &pcInfo,  0,  sizeof(  pcInfo  )  );
				  memset(  &regInfo,  0,  sizeof(  regInfo  )  );

			  	  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   				  	
				  index  =  0;  //  portIfAdminStatus
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  switchPort.iPortIfAdminStatus  =  _tcstol(  tBuf,  &pStopString,  10  );  
			  	  index  ++  ;  //  iPortIfOperStatus,
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  switchPort.iPortIfOperStatus  =  _tcstol(  tBuf,  &pStopString,  10  );  
				  index  ++  ;	//  connectedMac
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  connectedPc.connectedMac,  sizeof(  connectedPc.connectedMac  )  );  
				  index  ++  ;	//  connectedIp
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  connectedPc.connectedIp  );  
				  index  ++  ;  //  switchMac
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  connectedPc.switchMac,  sizeof(  connectedPc.switchMac  )  );  
			  	  index  ++  ;	//  iPortIfIndex,
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  connectedPc.iPortIfIndex  =  _tcstol(  tBuf,  &pStopString,  10  );  
			 	  index  ++  ;	//  auditTime,
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  connectedPc.auditTime,  sizeof(  connectedPc.auditTime  )  );  
			 	  index  ++  ;	//  firstTime,
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  connectedPc.firstTime,  sizeof(  connectedPc.firstTime  )  );  
			 	  index  ++  ;	//  lastTime,
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  connectedPc.lastTime,  sizeof(  connectedPc.lastTime  )  );  
			 	  index  ++  ;	//  ucbDirectConn,
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  connectedPc.ucbDirectConn  =  _tcstol(  tBuf,  &pStopString,  10  )  ?  TRUE  :  FALSE;  
				  index  ++  ;  //  comment0暂时不取
				  //  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  safeStrnCpy(  tBuf,  switchPort.comment,  sizeof(  switchPort.comment  )  );  }
			  	  index  ++  ;	//  qyPcTab.ip
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12,  sizeof(  ip12  )  );  qyIp12ToStd(  ip12,  pcInfo.ip  );  
			  	  index  ++  ;	//  qyPcTab.pcName
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pcInfo.pcName,  sizeof(  pcInfo.pcName  )  );  
				  index  ++  ;	//  qyPcTab.lastCommTime
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pcInfo.lastCommTime,  sizeof(  pcInfo.lastCommTime  )  );  
				  index  ++  ;  //  qySwitchSecureMacTab.iCpsSecureMacAddrType
				  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  secureMac.iCpsSecureMacAddrType  =  varVals[index].m_lVal;  }
				  index  ++  ;	//  qySwitchIfPortSecurityTab.iCpsIfPortSecurityEnable
				  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  portSecurity.ucbCpsIfPortSecurityEnable  =  (  (  varVals[index].m_lVal  ==  CONST_snmpTrue  )  ?  TRUE  :  FALSE  );  }
				  index  ++  ;  //  iCpsIfPortSecurityStatus
				  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  portSecurity.iCpsIfPortSecurityStatus  =  varVals[index].m_lVal;  }
				  index  ++  ;  //  iCpsIfCurrentSecureMacAddrCount
				  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  portSecurity.iCpsIfCurrentSecureMacAddrCount  =  varVals[index].m_lVal;  }
				  index  ++  ;		//  取各用户信息
				  for  (  i  =  0;  query.columns[i].type  !=  -1;  i  ++  )  {
					   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  (  TCHAR   *  )regInfo.u.cols[i],  tBuf,  sizeof(  regInfo.u.cols[i]  )  /  sizeof(  TCHAR  )  );  
				   	   index  ++  ;
			   	  }

				  if  (  !qyDisplayTime(  pcInfo.lastCommTime,  displayTime,  sizeof(  displayTime  )  )  )  displayTime[0]  =  0;
						
				  _strlwr(  connectedPc.connectedMac  );
				  getMacImages(  pQyMc,  &snmpObjHead,  &switchPort,  &portSecurity,  &connectedPc,  &secureMac,  &nImage,  &nSelectedImage  );
				  ListCtrl.InsertItem(  cnt,  CString(  connectedPc.connectedIp  ),  nImage  );
				  index  =  0;
				  ListCtrl.SetItemText(  cnt,  index,  CString(  connectedPc.connectedMac  )  );  index  ++  ;
				  ListCtrl.SetItemText(  cnt,  index,  CString(  pcInfo.ip  )  );  index  ++  ;
				  ListCtrl.SetItemText(  cnt,  index,  CString(  pcInfo.pcName  )  );  index  ++  ;
				  ListCtrl.SetItemText(  cnt,  index,  CString(  displayTime  )  );  index  ++  ;
				  for  (  i  =  0;  query.columns[i].type  !=  -1;  i  ++  )  {
					   ListCtrl.SetItemText(  cnt,  i  +  index,  (  TCHAR  *  )regInfo.u.cols[i]  );						
				  }

				  cnt  ++  ;
							
			 }
			
			 rs.Close(  );

		 }
	  
		 }
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bDisplayMcRootContent_switchPortUsrConnection failed."  )  );
		   goto  errLabel;
	}
		 
	 bRet  =  TRUE;

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	 return  bRet;		

}


 BOOL  bDisplayMcRootContent_switchPortNetworkSpeed(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 //  LV_ITEM							lvi;
	 int								index					=			0;
	 //  QY_MCROOTLIST_DISPLAYCFG		*	pCfg					=			&pCfgParam->u.rootList;
	 TCHAR								sqlBuf[1024];
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;			//  2007/01/07
	 CRecordset							rs(  (  CDatabase  *  )pObjDb->pDb  );   int	 nFields;
	 CDBVariant							varVals[20];	 
	 QY_SWITCHPORT_RCD					switchPort;
	 int								cnt						=			0;
	 TCHAR								portStatusBuf[256]		=			_T(  ""  );
	 int								nImage,  nSelectedImage;
	 TCHAR								displayName[512];
	 char								displayTime[128];
	 TCHAR						*		pStopString;
	 TCHAR								tBuf[1024];
	 
	 try  {		
	 
		  if  (  pMcView->var.m_superSel.u.rootTree.bRoot  ||  pObjIndex->objType  !=  CONST_objType_qySwitchPort  )  goto  errLabel;
		  //  显示交换机中所有的端口信息和mac信息
		  pMcView->delAllColumns(  );
		  if  (  !pMcView->bAddColumns(  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_switchPortNetworkSpeedViewTable  )  )  )  goto  errLabel;
			 																//  0							1							2							3								 4								5								6									7							  8								  9		
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "SELECT qySwitchPortTab.switchMac,qySwitchPortTab.portIfIndex,qySwitchPortTab.portIfAdminStatus,qySwitchPortTab.portIfOperStatus,qySwitchPortTab.portIfSpeedInK,qySwitchPortTab.portIfInSpeedInK,qySwitchPortTab.portIfOutSpeedInK,qySwitchPortTab.portIfInOctets,qySwitchPortTab.portIfOutOctets,qySwitchPortTab.lastTime"  )  );
		  //  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s from ( ( qySwitchPortTab left join qySwitchConnectedPcTab on (qySwitchPortTab.switchMac=qySwitchConnectedPcTab.switchMac and qySwitchPortTab.portIfIndex=qySwitchConnectedPcTab.portIfIndex)) left join qyPcTab on qySwitchConnectedPcTab.connectedMac=qyPcTab.mac0) left join qyPcRegInfoTab on qySwitchConnectedPcTab.connectedMac=qyPcRegInfoTab.mac0 where qySwitchPortTab.switchMac='%s' and qySwitchPortTab.portIfIndex=%d",  sqlBuf,  pObjIndex->objIdStr0,  pObjIndex->objId0  );
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s from qySwitchPortTab where qySwitchPortTab.switchMac='%s' and qySwitchPortTab.portIfIndex=%d"  ),  sqlBuf,  pObjIndex->objIdStr0,  pObjIndex->objId0  );
		  traceLogA(  "%s",  sqlBuf  );
		  if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  )  )  )  {
			  traceLogA(  "rs open() failed."  );  goto  errLabel;
		  }
	  			 
		  nFields  =  rs.GetODBCFieldCount(  );
		  //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
		  for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
			   memset(  &switchPort,  0,  sizeof(  switchPort  )  ); 
								   
			   for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   				  
			   index  =  0;		//  switchMac
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  switchPort.switchMac,  sizeof(  switchPort.switchMac  )  );  
			   index  ++  ;		//  iPortIfIndex,
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  switchPort.iPortIfIndex  =  _tcstol(  tBuf,  &pStopString,  10  );  
			   index  ++  ;		//  iPortIfAdminStatus,
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  switchPort.iPortIfAdminStatus  =  _tcstol(  tBuf,  &pStopString,  10  );  
			   index  ++  ;		//  iPortIfOperStatus,
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  switchPort.iPortIfOperStatus  =  _tcstol(  tBuf,  &pStopString,  10  );  
			   index  ++  ;		//  qySwitchPortTab.portIfSpeedInK
			   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.iPortIfSpeedInK  =  varVals[index].m_lVal;  }
			   index  ++  ;		//  qySwitchPortTab.portIfInSpeedInK
			   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.iPortIfInSpeedInK  =  varVals[index].m_lVal;  }
			   index  ++  ;		//  qySwitchPortTab.portIfOutSpeedInK
			   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.iPortIfOutSpeedInK  =  varVals[index].m_lVal;  }
			   index  ++  ;		//  qySwitchPortTab.portIfInOctets
			   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.i64PortIfInOctets  =  varVals[index].m_lVal;  }
			   index  ++  ;		//  qySwitchPortTab.portIfOutOctets
			   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.i64PortIfOutOctets  =  varVals[index].m_lVal;  }
			   index  ++  ;		//  lastTime
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  switchPort.lastTime,  sizeof(  switchPort.lastTime  )  );  
			   index  ++  ;		
			   
			   if  (  switchPort.iPortIfAdminStatus  ==  CONST_portStatus_down  )  lstrcpyn(  portStatusBuf,  qyGetDesByType1(  CONST_portAdminStatusTable,  switchPort.iPortIfAdminStatus  ),  mycountof(  portStatusBuf  )  );
			   else  lstrcpyn(  portStatusBuf,  qyGetDesByType1(  CONST_portOperStatusTable,  switchPort.iPortIfOperStatus  ),  mycountof(  portStatusBuf  )  );
						   
			   index  =  0;  
			   getSnmpPortImages(  pQyMc,  &switchPort,  &nImage,  &nSelectedImage  );
			   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%d"  ),  switchPort.iPortIfSpeedInK  );
			   ListCtrl.InsertItem(  cnt,  CString(  displayName  ),  nImage  );
			   index  ++  ;
			   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%d"  ),  switchPort.iPortIfInSpeedInK  );
			   ListCtrl.SetItemText(  cnt,  index,  CString(  displayName  )  );
			   index  ++  ;
			   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%d"  ),  switchPort.iPortIfOutSpeedInK  );
			   ListCtrl.SetItemText(  cnt,  index,  CString(  displayName  )  );
			   index  ++  ;
			   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u"  ),  switchPort.i64PortIfInOctets  );
			   ListCtrl.SetItemText(  cnt,  index,  CString(  displayName  )  );
			   index  ++  ;
			   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u"  ),  switchPort.i64PortIfOutOctets  );
			   ListCtrl.SetItemText(  cnt,  index,  CString(  displayName  )  );
			   index  ++  ;
			   if  (  !qyDisplayTime(  switchPort.lastTime,  displayTime,  sizeof(  displayTime  )  )  )  displayTime[0]  =  0;
			   ListCtrl.SetItemText(  cnt,  index,  CString(  displayTime  )  );
			   index  ++  ;
			   
			   cnt  ++  ;
									
		  }
				
		  rs.Close(  );
		  
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bDisplayMcRootContent_switchPortNetworkSpeed failed."  )  );
		   goto  errLabel;
	}
		 
	 bRet  =  TRUE;

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	 return  bRet;		

}




 BOOL  bDisplayMcRootContent(  void  *  pQyMcViewParam,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCROOTTREE_SEL  *  pSel  )
{
	 BOOL								bRet					=			FALSE;
	 CQyMcView  * pMcView  =  (  CQyMcView  *  )pQyMcViewParam;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 QY_OBJ_DB						*	pObjDb					=			NULL;  
	 
	 	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  FALSE;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	 if  (  pCfgParam->m_iViewType  !=  QY_VIEWTYPE_MCROOTLIST  )  {
		 //
		 //traceLogA( "CQyMcView::bDisplayContent(  ) 仅有对McRootList的实现，请用派生类来重载此函数。"  );
		 //
		 return FALSE;
	 }

	 //  2004/07/27
	 if  (  pSel->pfDisplayListContent  )  return  (  pSel->pfDisplayListContent(  pMcView,  pCfgParam,  pSel  )  ?  FALSE  :  TRUE  );

	 if  (  !(  pObjDb  =  getProcedObjDb(  pQyMc,  0,  pSel->iDsnIndex  )  )  )  goto  errLabel;
	 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	 ListCtrl.DeleteAllItems(  );

	 try  {		
	 
		  if  (  pMcView->var.m_superSel.u.rootTree.bRoot  )  {
			  
			  //  显示所有的交换机
			  if  (  !bDisplayMcRootContent_allDevices(  pObjDb,  pMcView,  pCfgParam  )  )  goto  errLabel;
			 
			}
		  else  {
			  	 int				iObjId				=	pMcView->var.m_superSel.u.rootTree.iHelpId;
				 QY_OBJINDEX_RCD	objIndex;
				 int				ilastPortIfIndex	=	-1;

	 			 if  (  g_dbFuncs.pf_getObjIndex(  pObjDb,  iObjId,  &objIndex  )  )  goto  errLabel;
	 			 if  (  objIndex.objType  ==  CONST_objType_qySwitch  )  {

					 //  显示交换机中所有的端口信息和mac信息
					 switch  (  pSel->type  )  {
							 case  CONST_qyTreeType_switch:
								   if  (  !bDisplayMcRootContent_switch(  pObjDb,  pMcView,  pCfgParam,  &objIndex  )  )  goto  errLabel;
								   break;
							 case  CONST_qyTreeType_usrConnection:
								   if  (  !bDisplayMcRootContent_switchUsrConnection(  pObjDb,  pMcView,  pCfgParam,  &objIndex  )  )  goto  errLabel;
								   break;
							 case  CONST_qyTreeType_networkSpeed:
								   if  (  !bDisplayMcRootContent_switchNetworkSpeed(  pObjDb,  pMcView,  pCfgParam,  &objIndex  )  )  goto  errLabel;
								   break;
							 default:
									goto  errLabel;		
					 }
					}
				 else  if  (  objIndex.objType  ==  CONST_objType_qySwitchPort  )  {

					   //  显示一个端口的关联信息
					   switch  (  pSel->type  )  {
								case  CONST_qyTreeType_switch:
									  if  (  !bDisplayMcRootContent_switchPort(  pObjDb,  pMcView,  pCfgParam,  &objIndex  )  )  goto  errLabel;
									  break;
								case  CONST_qyTreeType_usrConnection:
									  if  (  !bDisplayMcRootContent_switchPortUsrConnection(  pObjDb,  pMcView,  pCfgParam,  &objIndex  )  )  goto  errLabel;
									  break;
								case  CONST_qyTreeType_networkSpeed:
									  if  (  !bDisplayMcRootContent_switchPortNetworkSpeed(  pObjDb,  pMcView,  pCfgParam,  &objIndex  )  )  goto  errLabel;
									  break;
								default:
										goto  errLabel;
					   }
					 
				 }
		  }
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bDisplayMcRootContent failed."  )  );
		   goto  errLabel;
	}
		 
	 bRet  =  TRUE;

errLabel:
	
	
	 return  bRet;		

}

