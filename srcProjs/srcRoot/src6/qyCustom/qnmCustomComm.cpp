
#include	"stdafx.h"

#include	"qyPrecomp.h"

//  #include	<afxdb.h>
#include	<sqlucode.h>

#include	<windowsx.h>
#include	<winsock2.h>
#include	<tchar.h>
#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<MSAcm.h>
#endif

#include	"qmCommon.h"
#ifndef  __WINCE__
	#include	"qyDbCommon.h"
#endif
#include	"qyTCharCommProc.h"



//  以下是的入库信息  {
/*
#if  DEFAULT_qyCustomId  ==  CONST_qyCustomId_shhg
	   
 QY_DMITEM  CONST_shhgRegColsTable[]  =  
{
	{	0,		(TCHAR*)_T(  "用户类型"  ),				},				//  qyPcRegInfoTab.col0
	{	1,		(TCHAR*)_T(  "临时用户单位"  ),		},				//  qyPcRegInfoTab.col1
	{	2,		(TCHAR*)_T(  "关(处)名"  ),				},
	{	3,		(TCHAR*)_T(  "科室"  ),					},	   
	{	4,		(TCHAR*)_T(  "用户姓名"  ),				},
	{	5,		(TCHAR*)_T(  "联系电话"  ),				},
	{	6,		(TCHAR*)_T(  "设备型号"  ),				},
	{	7,		(TCHAR*)_T(  "设备序列号"  ),			},
	{	8,		(TCHAR*)_T(  "关产编号"  ),				},
	{	9,		(TCHAR*)_T(  "使用地点"  ),				},
	{	10,		(TCHAR*)_T(  "机器类型"  ),				},
	{	11,		(TCHAR*)_T(  "主要用途"  ),				},
	{	-1,		NULL,					},
};


 QY_DMITEM  CONST_shhgRegEventRegColsTable[]  =			//  产生注册事件用
{
	{	0,		(TCHAR*)_T(  "用户类型"  ),				},				//  qyPcEventTab.col0
	{	1,		(TCHAR*)_T(  "临时用户单位"  ),		},				//  qyPcEventTab.col1
	{	2,		(TCHAR*)_T(  "关(处)名"  ),				},
	{	3,		(TCHAR*)_T(  "科室"  ),					},	   
	{	4,		(TCHAR*)_T(  "用户姓名"  ),				},
	{	-1,		NULL,					},	
};


 QY_DMITEM  CONST_shhgEventRegColsTable[]  =			//  产生普通事件用
{
	{	0,		(TCHAR*)_T(  "用户类型"  ),				},				//  qyPcEventTab.col0
	{	1,		(TCHAR*)_T(  "临时用户单位"  ),		},				//  qyPcEventTab.col1
	{	2,		(TCHAR*)_T(  "关(处)名"  ),				},
	{	3,		(TCHAR*)_T(  "科室"  ),					},	   
	{	4,		(TCHAR*)_T(  "用户姓名"  ),				},
	{	-1,		NULL,					},	
};


 QY_DMITEM  CONST_rasEventDesColsTable[]  =
{
	{	0,		(TCHAR*)_T(  "拨号权限"  ),				},
	{	1,		(TCHAR*)_T(  "电话号码"  ),				},
	{	-1,		NULL,					},
};


QY_DMITEM	*	gpRegColsTable			=	CONST_shhgRegColsTable;				//  入库注册信息
QY_DMITEM	*	gpRegEventRegColsTable  =	CONST_shhgRegEventRegColsTable;		//  产生注册事件的注册信息
QY_DMITEM	*	gpEventRegColsTable		=	CONST_shhgEventRegColsTable;		//  qyPcRegInfoTab中需要摘取到qyPcEventTab的信息
QY_DMITEM	*	gpRasEventDesColsTable  =	CONST_rasEventDesColsTable;		

#endif
*/
//  }  以上是的入库信息


//  以下是的入库信息  {
#if  1  //  DEFAULT_qyCustomId  ==  CONST_qyCustomId_zjga

/*
 QY_DMITEM  CONST_zjgaRegColsTable[]  =  
{
	{	0,		"用户类型",			},					//  qyPcRegInfoTab.col0
	{	1,		"其它单位",			},					//  qyPcRegInfoTab.col1
	{	2,		"单位",				},					//  qyPcRegInfoTab.col2
	{	3,		"部门",				},					//	qyPcRegInfoTab.col3
	{	4,		"使用人",			},					//  qyPcRegInfoTab.col4
	{	5,		"机器类型",			},					//  qyPcRegInfoTab.col5
	{	6,		"主要用途",			},					//  qyPcRegInfoTab.col6
#ifdef  __ZJST__
	{	7,		"联系电话",			},					//  qyPcRegInfoTab.col7
	{	8,		"手机虚拟号",		},					//  qyPcRegInfoTab.col8
//	{	9,		"搬迁前地点",		},					//  qyPcRegInfoTab.col9
//	{	10,		"搬迁后地点",		},					//  qyPcRegInfoTab.col10
#else
	{	7,		"联系电话",			},					//  qyPcRegInfoTab.col7
	{	8,		"备注1",			},					//  qyPcRegInfoTab.col8
//	{	9,		"使用地点",			},					//  qyPcRegInfoTab.col9
//	{	10,		"备注2",			},					//  qyPcRegInfoTab.col10
#endif  __ZJST__
	{	9,		"备注2",			},					//  qyPcRegInfoTab.col9
	{	10,		"使用地点",			},					//  qyPcRegInfoTab.col10
	{	-1,		NULL,				},
};
*/


 QY_DMITEM  CONST_zjgaRegEventRegColsTable[]  =			//  产生注册事件用
{
#if  10
	{	0,		(TCHAR*)(TCHAR*)_T(  "yhlx"  ),			},					//  qyPcEventTab.col0
	{	1,		(TCHAR*)_T(  "qtdw"  ),			},					//  qyPcEventTab.col1
	{	2,		(TCHAR*)_T(  "dw"  ),				},					//  qyPcEventTab.col2
	{	3,		(TCHAR*)_T(  "bm"  ),				},					//  qyPcEventTab.col3
	{	4,		(TCHAR*)_T(  "syr"  ),			},					//  qyPcEventTab.col4
	{	11,		(TCHAR*)_T(  "zb"  ),				},					//  qyPcEventTab.col5
	{	12,		(TCHAR*)_T(  "bb"  ),				},					//  qyPcEventTab.col6
#endif
	{	-1,		NULL,				},					
};


 QY_DMITEM  CONST_zjgaEventRegColsTable[]  =			//  产生普通事件用
{
#if  10
	{	0,		(TCHAR*)_T(  "yhlx"  ),			},					//  qyPcEventTab.col0
	{	1,		(TCHAR*)_T(  "qtdw"  ),			},					//  qyPcEventTab.col1
	{	2,		(TCHAR*)_T(  "dw"  ),				},					//  qyPcEventTab.col2
	{	3,		(TCHAR*)_T(  "bm"  ),				},					//  qyPcEventTab.col3
	{	4,		(TCHAR*)_T(  "syr"  ),			},					//  qyPcEventTab.col4
	{	11,		(TCHAR*)_T(  "zb"  ),				},					//  qyPcEventTab.col5
	{	12,		(TCHAR*)_T(  "bb"  ),				},					//  qyPcEventTab.col6
#endif
	{	-1,		NULL,				},					
};


 QY_DMITEM  CONST_rasEventDesColsTable[]  =
{
#if  10
	{	0,		(TCHAR*)_T(  "bhqx"  ),				},
	{	1,		(TCHAR*)_T(  "dhhm"  ),				},
#endif

	{	-1,		NULL,					},
};


//  QY_DMITEM	*	gpRegColsTable			=	CONST_zjgaRegColsTable;				//  入库注册信息
QY_DMITEM	*	gpRegEventRegColsTable  =	CONST_zjgaRegEventRegColsTable;		//  产生注册事件的注册信息
QY_DMITEM	*	gpEventRegColsTable		=	CONST_zjgaEventRegColsTable;		//  qyPcRegInfoTab中需要摘取到qyPcEventTab的信息
QY_DMITEM	*	gpRasEventDesColsTable  =	CONST_rasEventDesColsTable;		


#endif	
//  }  以上是的入库信息


 QY_DMITEM		CONST_regInfo2DbTable[]  =
{
	{	CONST_fieldId_yhlx,		(  TCHAR  *  )0,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	CONST_fieldId_syr,		(  TCHAR  *  )4,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	CONST_fieldId_bm,		(  TCHAR  *  )3,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	CONST_fieldId_dw,		(  TCHAR  *  )2,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	CONST_fieldId_qtdw,		(  TCHAR  *  )1,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	CONST_fieldId_bb,		(  TCHAR  *  )12,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	CONST_fieldId_zb,		(  TCHAR  *  )11,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	CONST_fieldId_zcbh0,	(  TCHAR  *  )13,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	CONST_fieldId_zcbh1,	(  TCHAR  *  )14,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	CONST_fieldId_zcbh2,	(  TCHAR  *  )16,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	CONST_fieldId_zcsm1,	(  TCHAR  *  )15,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	CONST_fieldId_zcsm2,	(  TCHAR  *  )17,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	CONST_fieldId_jqlx,		(  TCHAR  *  )5,		(  TCHAR  *  )SQL_WVARCHAR,			}, 
	{	CONST_fieldId_zyyt,		(  TCHAR  *  )6,		(  TCHAR  *  )SQL_WVARCHAR,			}, 
	{	CONST_fieldId_lxdh,		(  TCHAR  *  )7,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	CONST_fieldId_sydd,		(  TCHAR  *  )10,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	-1,		NULL,	},
};


 //  事件表中的字段定义, 2008/09/06
 QY_DMITEM  CONST_eventDbIndexTable[]  =
{
	{	CONST_fieldId_zb,		(  TCHAR  *  )5,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	CONST_fieldId_bb,		(  TCHAR  *  )6,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	CONST_fieldId_dw,		(  TCHAR  *  )2,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	CONST_fieldId_bm,		(  TCHAR  *  )3,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	CONST_fieldId_syr,		(  TCHAR  *  )4,		(  TCHAR  *  )SQL_WVARCHAR,			},
	{	-1,	},
};

 extern  "C"  int  qnmSetFieldIdInRegInfo(  QNM_REG_INFO  *  pRegInfo  )
{
	 int			i;
	 QY_DMITEM	*	pItem	=	NULL;
	 for  (  i  =  0;  i  <  sizeof(  pRegInfo->uiFieldIds  )  /  sizeof(  pRegInfo->uiFieldIds[0]  );  i  ++  )  {
		  for  (  pItem  =  CONST_regInfo2DbTable;  pItem->type  !=  -1;  pItem  ++  )  {
			   if  (  (  int  )pItem->des  ==  i  )  break;
		  }
		  if  (  pItem->type  ==  -1  )  continue;
		  pRegInfo->uiFieldIds[i]  =  pItem->type;
	 }
	 return  0;
}


 //  此函数的fields[]的次序，代表了将存入qyPcRegInfoTab的cols的次序
 //  在产品投入市场后，不应经常变动，要注意兼容性
 extern  "C"  int  qnmSetPtrs(  QY_DMITEM  *  pFiledIdTable,  QNM_REG_INFO  *  pRegInfo1,  QNM_FIELD  fields[CONST_qnmMaxRegFields]  )
{
	 int					iErr		=	-1;
	 int					index		=	0;
	 QY_DMITEM		*		pItem		=	NULL;
	 
	 /*
	 */
	 for  (  index  =  0;  index  <  CONST_qnmMaxRegFields;  index  ++  )  {
		  fields[index].ptr  =  (TCHAR*)_T(  ""  );	 fields[index].pName  =  (TCHAR*)_T(  ""  );
	 }
	 
	 for  (  index  =  0;  index  <  sizeof(  pRegInfo1->uiFieldIds  )  /  sizeof(  pRegInfo1->uiFieldIds[0]  );  index  ++  )  {
		  if  (  !(  pItem  =  qyGetDmItemByType(  CONST_regInfo2DbTable,  pRegInfo1->uiFieldIds[index],  sizeof(  QY_DMITEM  )  )  )  )  continue;
		  unsigned  int			i;
		  if  (  (  i  =  (  unsigned  int  )pItem->des  )  >=  CONST_qnmMaxRegFields  )  continue;
		  fields[i].pName  =  qyGetDesByType1(  pFiledIdTable,  pRegInfo1->uiFieldIds[index]  );
		  fields[i].ptr  =  (  TCHAR  *  )pRegInfo1->u.cols[index];
		  fields[i].bufSize  =  sizeof(  pRegInfo1->u.cols[index]  )  /  sizeof(  TCHAR  );
		  fields[i].iDataType  =  (  int  )pItem->pData;
	 }

	 iErr  =  0;

//  errLabel:

	 return  iErr;

}


 //  以下函数原则上是为了取得regInfo.u.cols[]中的索引，但是按照现在的设计，实际和数据库中的是一样的, 2006/09/03增加说明
 extern  "C"  int  getRegIndexByFieldId(  unsigned  int  uiFieldId  )
{
	 int				iRet	=	-1;
	 QY_DMITEM	*		pItem	=	NULL;
	 if  (  !(  pItem  =  qyGetDmItemByType(  CONST_regInfo2DbTable,  uiFieldId,  0  )  )  )  goto  errLabel;
	 if  (  (  unsigned  int  )pItem->des  >=  CONST_qnmMaxRegFields  )  goto  errLabel;
	 iRet  =  0;
errLabel:
	 return  iRet  ?  iRet  :  (  int  )pItem->des;
}


 //  2006/09/03, 取得在数据库中的序号
 extern  "C"  int  getRegDbIndexByFieldId(  unsigned  int  uiFieldId  )
{
	 return  getRegIndexByFieldId(  uiFieldId  );
}



 extern  "C"  int  getEventDbIndexByFieldId(  unsigned  int  uiFieldId  )
{
	 int				iRet	=	-1;
	 QY_DMITEM	*		pItem	=	NULL;
	 if  (  !(  pItem  =  qyGetDmItemByType(  CONST_eventDbIndexTable,  uiFieldId,  0  )  )  )  goto  errLabel;
	 if  (  (  unsigned  int  )pItem->des  >=  CONST_qnmMaxEventRegFields  )  goto  errLabel;
	 iRet  =  0;
errLabel:
	 return  iRet  ?  iRet  :  (  int  )pItem->des;
}



 int  regInfo2Desc(  void  *  p0,  QY_MESSENGER_REGINFO  *  pRegInfo,  MY_REG_DESC  *  pDesc,  TCHAR  *  talkerDesc,  unsigned  int  uiCnt_talkerDesc,  TCHAR  *  displayName,  unsigned  int  uiCnt_displayName  )
{
	int						iErr		=	-1;
	int						index;
	//  unsigned  int			uiFieldId;

	if  (  (  index  =  getRegIndexByFieldId(  CONST_fieldId_zb  )  )  <  0  )  goto  errLabel;
	if  (  index  >=  mycountof(  pRegInfo->u.cols  )  )  goto  errLabel;
	pDesc->pZb  =  pRegInfo->fields[index].ptr;
	//
	if  (  (  index  =  getRegIndexByFieldId(  CONST_fieldId_bb  )  )  <  0  )  goto  errLabel;
	if  (  index  >=  mycountof(  pRegInfo->u.cols  )  )  goto  errLabel;
	pDesc->pBb  =  pRegInfo->fields[index].ptr;
	//
	if  (  (  index  =  getRegIndexByFieldId(  CONST_fieldId_dw  )  )  <  0  )  goto  errLabel;
	if  (  index  >=  mycountof(  pRegInfo->u.cols  )  )  goto  errLabel;
	pDesc->pDw  =  pRegInfo->fields[index].ptr;
	//
	if  (  (  index  =  getRegIndexByFieldId(  CONST_fieldId_bm  )  )  <  0  )  goto  errLabel;
	if  (  index  >=  mycountof(  pRegInfo->u.cols  )  )  goto  errLabel;
	pDesc->pBm  =  pRegInfo->fields[index].ptr;
	//
	if  (  (  index  =  getRegIndexByFieldId(  CONST_fieldId_syr  )  )  <  0  )  goto  errLabel;
	if  (  index  >=  mycountof(  pRegInfo->u.cols  )  )  goto  errLabel;
	pDesc->pSyr  =  pRegInfo->fields[index].ptr;

	if  (  !pDesc->pZb  )  pDesc->pZb  =  (TCHAR*)_T(  ""  );
	if  (  !pDesc->pBb  )  pDesc->pBb  =  (TCHAR*)_T(  ""  );
	if  (  !pDesc->pDw  )  pDesc->pDw  =  (TCHAR*)_T(  ""  );
	if  (  !pDesc->pBm  )  pDesc->pBm  =  (TCHAR*)_T(  ""  );
	if  (  !pDesc->pSyr  )  pDesc->pSyr  =  (TCHAR*)_T(  ""  );

	if  (  pDesc->pSyr[0]  )  {
		if  (  talkerDesc  )  _sntprintf(  talkerDesc,  uiCnt_talkerDesc,  _T(  "%s %s %s"  ),  pDesc->pDw,  pDesc->pBm,  pDesc->pSyr  );  
		if  (  displayName  )  _sntprintf(  displayName,  uiCnt_displayName,  _T(  "%s"  ),  pDesc->pSyr  );
		}
	else  {
		  if  (  talkerDesc  )  _sntprintf(  talkerDesc,  uiCnt_talkerDesc,  _T(  "(%I64u)"  ),  pRegInfo->addr.idInfo.ui64Id  );
		  if  (  displayName  )  _sntprintf(  displayName,  uiCnt_displayName,  _T(  "(%I64u)"  ),  pRegInfo->addr.idInfo.ui64Id  );
	}
	if  (  talkerDesc  )  tTrim(  talkerDesc  );
	if  (  displayName  )  tTrim(  displayName  );

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		  pDesc->pZb  =  (TCHAR*)_T(  ""  );		
		  pDesc->pBb  =  (TCHAR*)_T(  ""  );
		  pDesc->pDw  =  (TCHAR*)_T(  ""  );
		  pDesc->pBm  =  (TCHAR*)_T(  ""  );
          pDesc->pSyr  =  (TCHAR*)_T(  ""  );
	}

	return  iErr;
}


 
 int  grpInfo2Desc(  void  *  p0,  IM_GRP_INFO  *  pGrpInfo,  TCHAR  *  talkerDesc,  unsigned  int  uiCnt_talkerDesc,  TCHAR  *  displayName,  unsigned  int  uiCnt_displayName  )
{
	int		iErr	=	-1;

	if  (  pGrpInfo->name[0]  )  {
		if  (  talkerDesc  )  _sntprintf(  talkerDesc,  uiCnt_talkerDesc,  _T(  "%s"  ),  pGrpInfo->name  );
		if  (  displayName  )  _sntprintf(  displayName,  uiCnt_displayName,  _T(  "%s"  ),  pGrpInfo->name  );
	}
	else  {
		  if  (  talkerDesc  )  _sntprintf(  talkerDesc,  uiCnt_talkerDesc,  _T(  "(%I64u)"  ),  pGrpInfo->idInfo.ui64Id  );
		  if  (  displayName  )  _sntprintf(  displayName,  uiCnt_displayName,  _T(  "(%I64u)"  ),  pGrpInfo->idInfo.ui64Id  );
	}

	iErr  =  0;
//  errLabel:
	 return  iErr;
}

 ///////////////


  QY_DMITEM  CONST_qyCmdTable_cn[]  =
{
	//  低端保留：
	{	CONST_qyCmd_tellService,						(TCHAR*)_T(  "启动服务"  ),					},
	{	CONST_qyCmd_end,								(TCHAR*)_T(  "结束会话"  ),					},
#if  0
	//  用户定义:
	{	CONST_qyCmd_base,								(TCHAR*)_T(  "CONST_qyCmd_base"  ),			},
	{	CONST_qyCmd_getGlCntIp,							(TCHAR*)_T(  "CONST_qyCmd_getGlCntIp"  ),	},
	{	CONST_qyCmd_getCfgs,							(TCHAR*)_T(  "下载配置"  ),					},
	{	CONST_qyCmd_sndLog,								(TCHAR*)_T(  "上传日志"  ),					},
	{	CONST_qyCmd_reg,								(TCHAR*)_T(  "注册"  ),						},
	//  {	CONST_qyCmd_commWithGlCnt,					(TCHAR*)_T(  "和管理中心互通信息"  ),		},
	{	CONST_qyCmd_showQwmInfo,						(TCHAR*)_T(  "上传终端信息"  ),				},
	{	CONST_qyCmd_queryReg,							(TCHAR*)_T(  "查询是否注册"  ),				},
	{	CONST_qyCmd_getProxyCfgs,						(TCHAR*)_T(  "下载代理配置"  ),				},
	{	CONST_qyCmd_putProxyChkedPcsInfo,				(TCHAR*)_T(  "上传检查结果"  ),				},
	{	CONST_qyCmd_getProxyChkedPcsInfo,				(TCHAR*)_T(  "下载检查要求"  ),				},
	{	CONST_qyCmd_getMacByIp,							(TCHAR*)_T(  "取指定主机MAC"  ),			},
	{	CONST_qyCmd_refreshProxyPolicy,					(TCHAR*)_T(  "刷新代理策略"  ),				},
	{	CONST_qyCmd_getProxyStatusParams,				(TCHAR*)_T(  "取得状态显示参数"  ),			},
	{	CONST_qyCmd_policyChanged,						(TCHAR*)_T(  "策略已修改"  ),				},
	{	CONST_qyCmd_quit,								(TCHAR*)_T(  "客户端卸载"  ),				},
	{	CONST_qyCmd_sndSecChkLog,						(TCHAR*)_T(  "上传安全检查结果"  ),			},
	{	CONST_qyCmd_secChkGetCfgs,						(TCHAR*)_T(  "下载安全检查要求"  ),			},
	{	CONST_qyCmd_showQwmInfoEx,						(TCHAR*)_T(  "上传终端详细信息"  ),			},
	{	CONST_qyCmd_showQwmAssetsInfo,					(TCHAR*)_T(  "上传终端资产信息"  ),			},
	{	CONST_qyCmd_endShowQwmAssetsInfo,				(TCHAR*)_T(  "结束上传终端资产信息"  ),		},
	{	CONST_qyCmd_queryPcSp,							(TCHAR*)_T(  "查询补丁信息"  ),				},
	{	CONST_qyCmd_showQwmSvrStatus,					(TCHAR*)_T(  "显示客户端运行状态"  ),		},
	{	CONST_qyCmd_showPcNetworkProp,					(TCHAR*)_T(  "上传远程桌面管理"  ),			},
	{	CONST_qyCmd_tryToConnectToServer,				(TCHAR*)_T(  "尝试连接服务器"  ),			},
	{	CONST_qyCmd_showPcProcess,						(TCHAR*)_T(  "上传进程信息"  ),				},
	{	CONST_qyCmd_sndEventLog,						(TCHAR*)_T(  "上传系统日志"  ),				},
	{	CONST_qyCmd_sndUsrInfo,							(TCHAR*)_T(  "上传操作系统用户信息"  ),		},
	{	CONST_qyCmd_sndNetStat,							(TCHAR*)_T(  "上传NetStat信息"  ),			},
	{	CONST_qyCmd_sndPrinters,						(TCHAR*)_T(  "上传打印机信息"  ),			},
	
	{	CONST_qyCmd_queryAutoLogon,						(TCHAR*)_T(  "查询自动登录信息"  ),			},
	{	CONST_qyCmd_sndAutoLogon,						(TCHAR*)_T(  "上报自动登录信息"  ),			},
	{	CONST_qyCmd_getOpCmd,							(TCHAR*)_T(  "取实时操作指令"  ),			},
	{	CONST_qyCmd_sndCapScreen,						(TCHAR*)_T(  "上传屏幕图像"  ),				},
	{	CONST_qyCmd_queryCfgs,							(TCHAR*)_T(  "查询增量配置信息"  ),			},
	{	CONST_qyCmd_showPcProcessModule,				(TCHAR*)_T(  "上传进程调用模块信息"  ),		},
	{	CONST_qyCmd_retrieveWarningMsg,					(TCHAR*)_T(  "取报警信息"  ),				},
	{	CONST_qyCmd_sndRegistryVals,					(TCHAR*)_T(  "上传注册表信息"  ),			},
	{	CONST_qyCmd_showPcNetFlow,						(TCHAR*)_T(  "上传流量信息"  ),				},
	{	CONST_qyCmd_showPcNetShare,						(TCHAR*)_T(  "上传网络共享信息"  ),			},
	//
	{	CONST_qyCmd_talkTo,								(TCHAR*)_T(  "发言"  ),						},	//  2007/04/09
	{	CONST_qyCmd_refreshImObjListReq,				(TCHAR*)_T(  "更新联系人列表"  ),			},	//  2007/05/06
	{	CONST_qyCmd_refreshRecentFriendsReq,			(TCHAR*)_T(  "获取最近联系人状态"  ),			},
	{	CONST_qyCmd_sendTask,							(TCHAR*)_T(  "发送任务"  ),					},
	{	CONST_qyCmd_sendTaskReply,						(TCHAR*)_T(  "回复任务"  ),					},
	{	CONST_qyCmd_sendRobotTask,						(TCHAR*)_T(  "发送持久任务"  ),				},
	{	CONST_qyCmd_sendRobotTaskReply,					(TCHAR*)_T(  "Re: 持久任务"  ),				},
	{	CONST_qyCmd_sendRobotTaskData,					(TCHAR*)_T(  "传输任务数据"  ),				},
	//
	{	CONST_qyCmd_sendMedia,							(TCHAR*)_T(  "Cmd_sendMedia"  ),				},	//  2008/03/15
	//
	{	CONST_qyCmd_lastMsgInSession,					(TCHAR*)_T(  "Cmd_lastMsgInSession"  ),				},	//  2007/12/11
	//
	{	CONST_qyCmd_sendVDevReq,						(TCHAR*)_T(  "Cmd_sendVDevReq"  ),				},	//  2008/01/24
	//
	//  高端保留：
	{	CONST_qyCmd_upReserved,							(TCHAR*)_T(  "CONST_qyCmd_upReserved"  ),	},
	{	CONST_qyCmd_update,								(TCHAR*)_T(  "更新"  ),						},
	{	CONST_qyCmd_getFile,							(TCHAR*)_T(  "取文件"  ),					},
	{	CONST_qyCmd_getDigest,							(TCHAR*)_T(  "取重复信息"  ),				},
#endif
	//
	{	-1,												NULL,						},
};




