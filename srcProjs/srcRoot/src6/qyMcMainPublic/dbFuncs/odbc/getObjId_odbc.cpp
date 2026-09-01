
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"objType_tmp.h"



 int  getObjIndex_odbc(  QY_OBJ_DB  *  pObjDb,  int  iObjId,  QY_OBJINDEX_RCD  *  pObjIndex  )
{
	 int			iRet			=		-1;
	 char			sqlBuf[1024  +  1];
	 CDBVariant		varVals[20];
	 int			index;
	 CQnmDb			db;
	 void		*	pDb				=		NULL;


	 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;	//  2007/01/01

	 if  (  !(  pDb  =  db.getAvailableDb(  pObjDb->iDsnIndex  )  )  )  goto  errLabel;
	 
	 _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select usageType,usageName,servName,objType,objId0,objId1,objId2,objIdStr0,objIdStr1,objIdStr2,col0,col1,col2,col3,col4,comment0 from qyObjIndexTab where id=%d",  iObjId  );
	 if  (  !bQyGetRcdBySql(  pDb,  CString(  sqlBuf  ).GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;

	 memset(  pObjIndex,  0,  sizeof(  pObjIndex[0]  )  );
	 //
	 pObjIndex->id  =  iObjId;
	 //
	 index  =  0;  //  usageType,
	 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  pObjIndex->usageType  =  varVals[index].m_lVal;
	 index  ++  ;  //  usageName,
	 MACRO_sqlStr(  varVals[index],  pObjIndex->usageName,  mycountof(  pObjIndex->usageName  )  );  //  if  (  varVals[index].m_dwType  ==  DBVT_STRING  )  {  MACRO_CStringTrim(  *varVals[index].m_pstring  );  lstrcpyn(  pObjIndex->usageName,  varVals[index].m_pstring->GetBuffer(  0  ),  sizeof(  pObjIndex->usageName  )  /  sizeof(  pObjIndex->usageName[0]  )  );  }
	 index  ++  ;  //  servName
	 MACRO_sqlStr(  varVals[index],  pObjIndex->servName,  mycountof(  pObjIndex->servName  )  );	//  2007/08/06
	 index  ++  ;  //  objType,
	 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  pObjIndex->objType  =  varVals[index].m_lVal;
	 index  ++  ;  //  objId0,
	 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  pObjIndex->objId0  =  varVals[index].m_lVal;
	 index  ++  ;  //  objId1,
	 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  pObjIndex->objId1  =  varVals[index].m_lVal;
	 index  ++  ;  //  objId2,
	 if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  pObjIndex->objId2  =  varVals[index].m_lVal;
	 index  ++  ;  //  objIdStr0,  
	 MACRO_sqlStr(  varVals[index],  pObjIndex->objIdStr0,  sizeof(  pObjIndex->objIdStr0  )  /  sizeof(  pObjIndex->objIdStr0[0]  )  );  
	 index  ++  ;  //  objIdStr1,
	 MACRO_sqlStr(  varVals[index],  pObjIndex->objIdStr1,  sizeof(  pObjIndex->objIdStr1  )  /  sizeof(  pObjIndex->objIdStr1[0]  )  );  
	 index  ++  ;  //  objIdStr2,
	 MACRO_sqlStr(  varVals[index],  pObjIndex->objIdStr2,  sizeof(  pObjIndex->objIdStr2  )  /  sizeof(  pObjIndex->objIdStr2[0]  )  );  
	 index  ++  ;  //  col0,
	 MACRO_sqlStr(  varVals[index],  pObjIndex->col0,  sizeof(  pObjIndex->col0  )  /  sizeof(  pObjIndex->col0[0]  )  );  
	 index  ++  ;  //  col1,
	 MACRO_sqlStr(  varVals[index],  pObjIndex->col1,  sizeof(  pObjIndex->col1  )  /  sizeof(  pObjIndex->col1[0]  )  );  
	 index  ++  ;  //  col2,
	 MACRO_sqlStr(  varVals[index],  pObjIndex->col2,  sizeof(  pObjIndex->col2  )  /  sizeof(  pObjIndex->col2[0]  )  );  
	 index  ++  ;  //  col3,
	 MACRO_sqlStr(  varVals[index],  pObjIndex->col3,  sizeof(  pObjIndex->col3  )  /  sizeof(  pObjIndex->col3[0]  )  );  
	 index  ++  ;  //  col4,
	 MACRO_sqlStr(  varVals[index],  pObjIndex->col4,  sizeof(  pObjIndex->col4  )  /  sizeof(  pObjIndex->col4[0]  )  );  
	 index  ++  ;  //  comment0 
	 MACRO_sqlStr(  varVals[index],  pObjIndex->comment,  sizeof(  pObjIndex->comment  )  /  sizeof(  pObjIndex->comment[0]  )  );  
	 index  ++  ;

	 iRet  =  0;

errLabel:
	 return  iRet;	 
}

//  取得对象在索引表中的id, 当表中没有时，需立马建一个
 __declspec(  dllexport  )  int  getObjId(  QY_OBJ_DB  *  pObjDb,  int  iUsageType,  LPCTSTR  servName,  int  iObjType,  void  *  pObjParam  )
{
	 int					iRet			=		-1;
	 QY_MC			*		pQyMc			=		QY_GET_GBUF(  );
	 CDBVariant				varVals[10];
	 TCHAR					sqlBuf[1024];
	 QY_OBJINDEX_RCD		objIndex;
	 CQnmDb					db;
	 int					iDbType;
	 int					iDataType		=		SQL_WVARCHAR;
	 void			*		pDb				=		NULL;
	 char					buf[256]		=		"";

	 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;	//  2007/01/01
	 iDbType  =  pObjDb->cfg.iDbType;

	 pDb  =  db.getAvailableDb(  pObjDb->iDsnIndex  );

	 memset(  &objIndex,  0,  sizeof(  objIndex  )  );
	 objIndex.usageType  =  iUsageType;
	 if  (  servName  )  lstrcpyn(  objIndex.servName,  servName,  mycountof(  objIndex.servName  )  );
	 objIndex.objType  =  iObjType;
	 myStr2TChar(  CONST_objIdStr,  objIndex.objIdStr0,  sizeof(  objIndex.objIdStr0  )  /  sizeof(  objIndex.objIdStr0[0]  )  );
	 myStr2TChar(  CONST_objIdStr,  objIndex.objIdStr1,  sizeof(  objIndex.objIdStr1  )  /  sizeof(  objIndex.objIdStr1[0]  )  );
	 myStr2TChar(  CONST_objIdStr,  objIndex.objIdStr2,  sizeof(  objIndex.objIdStr2  )  /  sizeof(  objIndex.objIdStr2[0]  )  );

	 switch  (  iObjType  )  {
			 case  CONST_objType_qySwitch:  {
				   QY_SNMP_OBJ  *  pObj  =  (  QY_SNMP_OBJ  *  )pObjParam;
				   myStr2TChar(  pObj->mac,  objIndex.objIdStr0,  sizeof(  objIndex.objIdStr0  )  /  sizeof(  objIndex.objIdStr0[0]  )  );				   
					}
				   break;
			 case  CONST_objType_qySwitchPort:  {
				   QY_SWITCHPORT_RCD  *  pSwitchPort  =  (  QY_SWITCHPORT_RCD  *  )pObjParam;
				   myStr2TChar(  pSwitchPort->switchMac,  objIndex.objIdStr0,  sizeof(  objIndex.objIdStr0  )  /  sizeof(  objIndex.objIdStr0[0]  )  );				   
				   objIndex.objId0  =  pSwitchPort->iPortIfIndex;				
					}
				   break;
			 case  CONST_objType_zb:  {
				   unsigned  int		uiFieldId		=	CONST_fieldId_zb;
				   COMMON_PARAM		*	pCommonParam	=	(  COMMON_PARAM  *  )pObjParam;
				   unsigned  int	*	puiType			=	(  unsigned  int  *  )pCommonParam->p1;
				   int					i				=	0;
				   if  (  (  i  =  getRegIndexByFieldId(  uiFieldId  )  )  <  0  )  goto  errLabel;
				   objIndex.objId0  =  (  int  )pCommonParam->p0;
				   if  (  puiType[0]  ==  CONST_imCommType_messengerRegInfo  )  {
					   QY_MESSENGER_REGINFO	*	pRegInfo		=	(  QY_MESSENGER_REGINFO  *  )puiType;
					   //
					   lstrcpyn(  objIndex.objIdStr0,  pRegInfo->u.cols[i],  sizeof(  objIndex.objIdStr0  )  /  sizeof(  objIndex.objIdStr0[0]  )  );
					   }
				   else  {
					     QNM_REG_INFO		*	pRegInfo		=	(  QNM_REG_INFO  *  )puiType;
					     //				   
                         lstrcpyn(  objIndex.objIdStr0,  (  TCHAR  *  )pRegInfo->u.cols[i],  sizeof(  objIndex.objIdStr0  )  /  sizeof(  objIndex.objIdStr0[0]  )  );
				   }
					}
				   break;
			 case  CONST_objType_bb:  {
				   unsigned  int		uiFieldId		=	CONST_fieldId_bb;
				   COMMON_PARAM		*	pCommonParam	=	(  COMMON_PARAM  *  )pObjParam;
				   unsigned  int	*	puiType			=	(  unsigned  int  *  )pCommonParam->p1;
				   int					i				=	0;
				   if  (  (  i  =  getRegIndexByFieldId(  uiFieldId  )  )  <  0  )  goto  errLabel;
				   objIndex.objId0  =  (  int  )pCommonParam->p0;
				   if  (  puiType[0]  ==  CONST_imCommType_messengerRegInfo  )  {
					   QY_MESSENGER_REGINFO	*	pRegInfo		=	(  QY_MESSENGER_REGINFO  *  )puiType;
					   //
					   lstrcpyn(  objIndex.objIdStr0,  pRegInfo->u.cols[i],  sizeof(  objIndex.objIdStr0  )  /  sizeof(  objIndex.objIdStr0[0]  )  );
					   }
				   else  {
					     QNM_REG_INFO		*	pRegInfo		=	(  QNM_REG_INFO  *  )puiType;
					     //				   
                         lstrcpyn(  objIndex.objIdStr0,  (  TCHAR  *  )pRegInfo->u.cols[i],  sizeof(  objIndex.objIdStr0  )  /  sizeof(  objIndex.objIdStr0[0]  )  );
				   }
				   	}
				   break;
			 case  CONST_objType_dw:  {
				   unsigned  int		uiFieldId		=	CONST_fieldId_dw;
				   COMMON_PARAM		*	pCommonParam	=	(  COMMON_PARAM  *  )pObjParam;
				   unsigned  int	*	puiType			=	(  unsigned  int *  )pCommonParam->p1;
				   int					i				=	0;
				   //
				   if  (  (  i  =  getRegIndexByFieldId(  uiFieldId  )  )  <  0  )  goto  errLabel;
				   objIndex.objId0  =  (  int  )pCommonParam->p0;
				   if  (  puiType[0]  ==  CONST_imCommType_messengerRegInfo  )  {
					   QY_MESSENGER_REGINFO	*	pRegInfo		=	(  QY_MESSENGER_REGINFO  *  )puiType;
					   //
					   lstrcpyn(  objIndex.objIdStr0,  pRegInfo->u.cols[i],  sizeof(  objIndex.objIdStr0  )  /  sizeof(  objIndex.objIdStr0[0]  )  );
					   }
				   else  {
					     QNM_REG_INFO		*	pRegInfo		=	(  QNM_REG_INFO  *  )puiType;
					     //				   
                         lstrcpyn(  objIndex.objIdStr0,  (  TCHAR  *  )pRegInfo->u.cols[i],  sizeof(  objIndex.objIdStr0  )  /  sizeof(  objIndex.objIdStr0[0]  )  );
				   }
				   //
				   	}
				   break;
			 case  CONST_objType_bm:  {
				   unsigned  int		uiFieldId		=	CONST_fieldId_bm;
				   COMMON_PARAM		*	pCommonParam	=	(  COMMON_PARAM  *  )pObjParam;
				   unsigned  int	*	puiType			=	(  unsigned  int  *  )pCommonParam->p1;
				   int					i				=	0;
				   //
				   if  (  (  i  =  getRegIndexByFieldId(  uiFieldId  )  )  <  0  )  goto  errLabel;
				   objIndex.objId0  =  (  int  )pCommonParam->p0;
				   if  (  puiType[0]  ==  CONST_imCommType_messengerRegInfo  )  {
					   QY_MESSENGER_REGINFO	*	pRegInfo		=	(  QY_MESSENGER_REGINFO  *  )puiType;
					   //
					   lstrcpyn(  objIndex.objIdStr0,  pRegInfo->u.cols[i],  sizeof(  objIndex.objIdStr0  )  /  sizeof(  objIndex.objIdStr0[0]  )  );
					   }
				   else  {
					     QNM_REG_INFO		*	pRegInfo		=	(  QNM_REG_INFO  *  )puiType;
					     //				   
                         lstrcpyn(  objIndex.objIdStr0,  (  TCHAR  *  )pRegInfo->u.cols[i],  sizeof(  objIndex.objIdStr0  )  /  sizeof(  objIndex.objIdStr0[0]  )  );
				   }
				   //
				   	}
				   break;
			 case  CONST_objType_syr:  {
				   unsigned  int	*	puiType			=	(  unsigned  int  *  )pObjParam;
				   //
				   if  (  puiType[0]  ==  CONST_imCommType_messengerRegInfo  )  {
					   QY_MESSENGER_REGINFO  *  pRegInfo		=  (  QY_MESSENGER_REGINFO  *  )puiType;
					   //
					   idInfo2Str(  &pRegInfo->addr.idInfo,  buf,  mycountof(  buf  )  );  myStr2TChar(  buf,  objIndex.objIdStr0,  mycountof(  objIndex.objIdStr0  )  );
						}
				   else  {
					     QNM_REG_INFO		*	pRegInfo		=	(  QNM_REG_INFO  *  )puiType;
						 //
						 myStr2TChar(  pRegInfo->mac0,  objIndex.objIdStr0,  sizeof(  objIndex.objIdStr0  )  /  sizeof(  objIndex.objIdStr0[0]  )  );
					}
				    //
					}
				   break;
			 case  CONST_objType_unRegGrp:  {
				   lstrcpyn(  objIndex.objIdStr0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_unRegGrp  ),  mycountof(  objIndex.objIdStr0  )  );
					}
				   break;
			 case  CONST_objType_othersGrp:  {
				   lstrcpyn(  objIndex.objIdStr0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_othersGrp  ),  mycountof(  objIndex.objIdStr0  )  );
					}
				   break;
			 case  CONST_objType_unRegPc:  {
				   QNM_PC_INFO	*	pPcInfo  =  (  QNM_PC_INFO  *  )pObjParam;
				   myStr2TChar(  pPcInfo->macs[0],  objIndex.objIdStr0,  sizeof(  objIndex.objIdStr0  )  /  sizeof(  objIndex.objIdStr0[0]  )  );  
					}
				    break;
			 case  CONST_objType_otherPc:  {
				   char			*	pMac	=	(  char  *  )pObjParam;
				   myStr2TChar(  pMac,  objIndex.objIdStr0,  sizeof(  objIndex.objIdStr0  )  /  sizeof(  objIndex.objIdStr0[0]  )  );
					}
				   break;
			 case  CONST_objType_pcUsrInfo:					//  2006/08/14
			 case  CONST_objType_pcStatus:  
			 case  CONST_objType_pcOpNode:
			 case  CONST_objType_pcOsClass:  {			//  2006/08/14
				   COMMON_PARAM		*	pCommonParam	=	(  COMMON_PARAM  *  )pObjParam;
				   objIndex.objId0  =  (  int  )pCommonParam->p0;
				   //
				   switch  (  objIndex.objId0  )  {
						   case  CONST_objType_messenger:
							     char  *  idStr;
								 idStr  =  (  char  *  )pCommonParam->p1;
								 //
								 myStr2TChar(  idStr,  objIndex.objIdStr0,  mycountof(  objIndex.objIdStr0  )  );
								 break;
						   case  CONST_objType_pc:
							     char			*	pMac;
								 pMac  =  (  char  *  )pCommonParam->p1;
								 //
                                 myStr2TChar(  pMac,  objIndex.objIdStr0,  mycountof(  objIndex.objIdStr0  )  );				   
								 break;
						   default:
							      goto  errLabel;
				   }
					}
				   break;
			 case  CONST_objType_pcEnv:  
			 case  CONST_objType_os:  {
				   QY_OBJINDEX_RCD		*	pObjIndex  =  (  QY_OBJINDEX_RCD  *  )pObjParam;
				   objIndex.objId0  =  pObjIndex->objId0;
				   objIndex.objId1  =  pObjIndex->objId1;
				   objIndex.objId2  =  pObjIndex->objId2;
				   lstrcpyn(  objIndex.objIdStr0,  pObjIndex->objIdStr0,  sizeof(  objIndex.objIdStr0  )  /  sizeof(  objIndex.objIdStr0[0]  )  );
				   lstrcpyn(  objIndex.objIdStr1,  pObjIndex->objIdStr1,  sizeof(  objIndex.objIdStr1  )  /  sizeof(  objIndex.objIdStr1[0]  )  );
				   lstrcpyn(  objIndex.objIdStr2,  pObjIndex->objIdStr2,  sizeof(  objIndex.objIdStr2  )  /  sizeof(  objIndex.objIdStr2[0]  )  );
					}
				   break;
			 case  CONST_objType_cfgSpOs:  {
				   int						iPlatformId	=	(  int  )pObjParam;
				   objIndex.objId0  =  iPlatformId;
					}
				   break;
			 case  CONST_objType_cfgSpServicePack:  {
				   QY_OSSP_RCD			*	pOsSp  =  (  QY_OSSP_RCD  *  )pObjParam;
				   objIndex.objId0  =  pOsSp->iPlatformId;
				   lstrcpyn(  objIndex.objIdStr0,  pOsSp->servicePack,  sizeof(  objIndex.objIdStr0  )  /  sizeof(  objIndex.objIdStr0[0]  )  );
				   objIndex.objId1  =  pOsSp->uiLangId;				   
					}
				   break;
			 case  CONST_objType_imGrps:		//  2007/08/23
				   break;
			 case  CONST_objType_imGrps_msg:	//  2014/01/31
				   break;
			 case  CONST_objType_imGrps_av:
				   break;
			 case  CONST_objType_messenger:  
			 case  CONST_objType_imGrp:  {
			 	   QY_MESSENGER_ID		*	pIdInfo  =  (  QY_MESSENGER_ID  *  )pObjParam;
				   char						idStr[CONST_qyMessengerIdStrLen  +  1]	=	"";
				   //
				   if  (  !idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
				   myStr2TChar(  idStr,  objIndex.objIdStr0,  mycountof(  objIndex.objIdStr0  )  );
				   }
				   break;
			 case  CONST_objType_me:  {
				   //
				   }
				   break;
			 default:
				    traceLogA(  "Failed: unknown objType: %d",  iObjType  );  goto  errLabel;					
					
	 }

	 //  查询对象索引，
	 _sntprintf(  sqlBuf,  sizeof(  sqlBuf  )  /  sizeof(  sqlBuf[0]  ),  _T(  "select id from qyObjIndexTab where usageType=%d and servName=%s and objType=%d and objId0=%d and objId1=%d and objId2=%d and objIdStr0=%s and objIdStr1=%s and objIdStr2=%s"  ),
							objIndex.usageType,  getDbValStr(  iDbType,  iDataType,  objIndex.servName  ),  objIndex.objType,  objIndex.objId0,  objIndex.objId1,  objIndex.objId2,  getDbValStr(  iDbType,  iDataType,  objIndex.objIdStr0  ),  getDbValStr(  iDbType,  iDataType,  objIndex.objIdStr1  ),  getDbValStr(  iDbType,  iDataType,  objIndex.objIdStr2  )  );
	 //  traceLogA(  "sqlBuf is %s",  sqlBuf  );
	 if  (  bQyGetRcdBySql(  pDb,  CString(  sqlBuf  ).GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  
		 &&  varVals[0].m_dwType  ==  DBVT_LONG  )  
	 {
		 iRet  =  varVals[0].m_lVal;  goto  errLabel;
	 }	

	 //  若没有索引，则将对象放入对象索引表中
	 _sntprintf(  sqlBuf,  sizeof(  sqlBuf  )  /  sizeof(  sqlBuf[0]  ),  _T(  "insert into qyObjIndexTab(usageType,usageName,servName,objType,objId0,objId1,objId2,objIdStr0,objIdStr1,objIdStr2,col0,col1,col2,col3,col4,comment0) values(%d,%s,%s,%d,%d,%d,%d,%s,%s,%s,%s,%s,%s,%s,%s,%s)"  ),
					objIndex.usageType, 
					getDbValStr(  iDbType,  iDataType,  objIndex.usageName  ),
					getDbValStr(  iDbType,  iDataType,  objIndex.servName  ),  
					objIndex.objType,
					objIndex.objId0,
					objIndex.objId1,
					objIndex.objId2,
					getDbValStr(  iDbType,  iDataType,  objIndex.objIdStr0  ),
					getDbValStr(  iDbType,  iDataType,  objIndex.objIdStr1  ),
					getDbValStr(  iDbType,  iDataType,  objIndex.objIdStr2  ),
					getDbValStr(  iDbType,  iDataType,  objIndex.col0  ),
					getDbValStr(  iDbType,  iDataType,  objIndex.col1  ),
					getDbValStr(  iDbType,  iDataType,  objIndex.col2  ),
					getDbValStr(  iDbType,  iDataType,  objIndex.col3  ),
					getDbValStr(  iDbType,  iDataType,  objIndex.col4  ),
					getDbValStr(  iDbType,  iDataType,  objIndex.comment  )  );
	 traceLogA(  "sqlBuf is %S",  sqlBuf  );
	 bQyExecSql(  pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  );
		
	 //  再次查询对象索引，
	 _sntprintf(  sqlBuf,  sizeof(  sqlBuf  ),  _T(  "select id from qyObjIndexTab where usageType=%d and servName=%s and objType=%d and objId0=%d and objId1=%d and objId2=%d and objIdStr0=%s and objIdStr1=%s and objIdStr2=%s"  ),
							objIndex.usageType,  getDbValStr(  iDbType,  iDataType,  objIndex.servName  ),  objIndex.objType,  objIndex.objId0,  objIndex.objId1,  objIndex.objId2,  getDbValStr(  iDbType,  iDataType,  objIndex.objIdStr0  ),  getDbValStr(  iDbType,  iDataType,  objIndex.objIdStr1  ),  getDbValStr(  iDbType,  iDataType,  objIndex.objIdStr2  )  );
	 if  (  !bQyGetRcdBySql(  pDb,  CString(  sqlBuf  ).GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  
		 ||  varVals[0].m_dwType  !=  DBVT_LONG  )
	 {
		 goto  errLabel;
	 }
				 
	 iRet  =  varVals[0].m_lVal;  goto  errLabel;
	 
errLabel:

	 return  iRet;

}


