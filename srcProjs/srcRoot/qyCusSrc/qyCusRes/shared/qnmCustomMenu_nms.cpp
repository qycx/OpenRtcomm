
#include	"stdafx.h"
#include	<tchar.h>
//  #include	"qyCommon.h"
#include	"myresource_main.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"
#include	"isCmdConst.h"

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_netMc.h"




 QY_DMITEM	CONST_menuTable_jiSuanJiGuanLi_nms[]  =
{
	{	ID_qyPcList,	},
	{	ID_qyPcSpList,	},
	{	-1,		},
};
 
 QY_DMITEM	CONST_menuTable_yongHuGuanLi_nms[]  =
{
	{		ID_qyPcUsrList,	0,		0,	},
	{		ID_qyPcUsrInTab1List,	0,		0,	},
	{	-1,		},
};

 QY_DMITEM	CONST_menuTable_wangLuoGuanLi_nms[]  =
{
	{	ID_qyNetworkView,					},		//  		(  TCHAR  *  )_T(  "设备管理视图(&S)"  ),		},			//  (  "网络联接视图(&S)"  )
	{	ID_qyConnectionView,				},		//		(  TCHAR  *  )_T(  "用户管理视图(&J)"  ),            },		//  (  "用户接入视图(&J)
	{	ID_qyNetworkSpeedView,				},		//	(  TCHAR  *  )_T(  "流量管理视图(&L)"  ),            },		//  (  "网络流量视图(&L)"  )
	{		-2,				},
	{	ID_snmpObjRuleList,					},		//	(  TCHAR  *  )_T(  "设备管理策略列表(&C)"  ),		},    //  (  "网络设备管理策略列表(&C)"  )
	{		-2,				},
	{	ID_conflictConnList,				},		// 	(  TCHAR  *  )_T(  "MAC绑定列表(&D)"  ),		},        //  (  "联接绑定列表(&D)"  )
	{		-2,				},
	{	ID_directConnList,					},		//	(  TCHAR  *  )_T(  "接入列表(J)"  ),					},			//  (  "接入列表(J)"  )
	{		-1,				NULL,			},
};

 QY_DMITEM	CONST_menuTable_shiJianChaKan_nms[]  =
{
	 {	ID_qyEventAll,				(  TCHAR  *  )ID_qyEventAll1,	},
	 {	ID_qyNetDevEventAll,	},					//		(  TCHAR  *  )_T(  "网络设备事件(&W)"  ),		},
	 {	-2,				},
	 {	ID_qyOpEventAll,	0,		0,	},
	 {	-1,				NULL,			},
};

 QY_DMITEM  CONST_menuTable_chaXun_nms[]  =
{
	{	ID_qySearch_netDevEvent,		},		//	(  TCHAR  *  )_T(  "网络设备事件查询(&W)"  ),        },
	{	ID_qySearch_pcEvent,			},		//	(  TCHAR  *  )_T(  "计算机事件查询(&S)"  ),          },
	{	ID_qySearch_pcList,				},		//	(  TCHAR  *  )_T(  "计算机查询(&J)"  ),              },
	{	ID_qySearch_pcSpList,			},		//	(  TCHAR  *  )_T(  "补丁查询(B)"  ),                 },
	{	ID_qySearch_mac,				},		//	(  TCHAR  *  )_T(  "MAC查询(&M)"  ),                 },
	{	ID_qySearch_ip,					},		//	(  TCHAR  *  )_T(  "IP查询(&I)"  ),						},
	{	ID_qySearch_unusedConn,			},		//	(  TCHAR  *  )_T(  "无效联接查询(&W)"  ),            },
	{		-1,				NULL,			},
};


QY_DMITEM  CONST_menuTable_guanLi_nms[]  =
{	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_jiSuanJiGuanLi,			(  TCHAR  *  )CONST_menuTable_jiSuanJiGuanLi_nms,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_yongHuGuanLi,			(  TCHAR  *  )CONST_menuTable_yongHuGuanLi_nms,	},
	{	-2,						},			
	{	-3,		(  TCHAR  *  )CONST_resId_menu_wangLuoGuanLi,			(  TCHAR  *  )CONST_menuTable_wangLuoGuanLi_nms,	},
	{	-2,						},			
	{	-3,		(  TCHAR  *  )CONST_resId_menu_shiJianChaKan,			(  TCHAR  *  )CONST_menuTable_shiJianChaKan_nms,	},	
	{	-2,						},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chaXun,					(  TCHAR  *  )CONST_menuTable_chaXun_nms,			},
	//  {	ID_qyStat,		},
	//  {	-2,						},
	//  {	ID_qyImport,		},
	//  {	ID_qyExport,		},
	//  {	ID_qyClearUp,		},
	//  {	-2,						},
	//  {	ID_FILE_PRINT_SETUP,		},
	//  {	ID_FILE_PRINT,		},
	//  {	-2,						},
	//  {	ID_APP_EXIT,		},
	{	-1,		NULL,			},

};

 QY_DMITEM	CONST_menuTable_xiTong_nms[]  =
{
	{	ID_qyStopSnmpScan,		},		//		(  TCHAR  *  )_T(  "停止扫描网络设备(&J)"  ),        (  TCHAR  *  )_T(   "停止扫描网络设备"  ),			},
	{	ID_qyStartSnmpScan,		},		//		(  TCHAR  *  )_T(  "启动扫描网络设备(&R)"  ),        (  TCHAR  *  )_T(   "启动扫描网络设备"  ),			},
	{	ID_qyStopMacScan,		},
	{	ID_qyStartMacScan,		},
	{	-2,						},
	{	ID_qyStopWatchIp,		},
	{	ID_qyStartWatchIp,		},
	{	-2,						},
	{	ID_qyStopDownPortIfMacChanged,		},		//  (  TCHAR  *  )_T(  "停止在关联MAC变化时阻断端口(&Z)"  ),		 (  TCHAR  *  )_T(  "在关联MAC变化时不阻断端口"  ),		},
	{	ID_qyStartDownPortIfMacChanged,		},		//  (  TCHAR  *  )_T(  "启用在关联MAC变化时阻断端口(&D)"  ),		 (  TCHAR  *  )_T(  "启用在关联MAC变化时阻断端口(&D)"  ),		},
	{	ID_qyStopDownPortIfWarnSpeed,		},
	{	ID_qyStartDownPortIfWarnSpeed,		},
	{	-2,						},
	{	ID_qyStopRegScan,		(  TCHAR  *  )ID_qyStopRegScan1,			},		//  	(  TCHAR  *  )_T(  "停止内网审核检查(&A)"  ),		(  TCHAR  *  )_T(  "停止内网审核检查"  ),		},
	{	ID_qyStartRegScan,		(  TCHAR  *  )ID_qyStartRegScan1,			},		//  	(  TCHAR  *  )_T(  "启动内网审核检查(&H)"  ),		(  TCHAR  *  )_T(  "启动内网审核检查"  ),		},
	{	-2,						},
	{	ID_qyStartUpdate		},
	{	ID_qyStopUpdate			},
	{	-1,		NULL,			},
};
 QY_DMITEM	CONST_menuTable_peiZhi_nms[]  =
{
	{	ID_qyMgrPcGrp,	(  TCHAR  *  )ID_qyMgrPcGrp1,	},
	{	ID_qyCfgSwitchPolicyGrps,		},		//	( TCHAR  *  )_T(  "snmp组策略配置(&J)"  ),          ( TCHAR  *  )_T(  "按照不同的Community值,划分为不同的组"  ),  },
	{	ID_qyMgrSwitchPolicyGrps,		},		//	(  TCHAR  *  )_T(  "网络设备分组配置(&S)"  ),        (  TCHAR  *  )_T(  "将网络设备IP指定到不同的Community分组中"  ),  },
	{	-2,						},
	{	ID_cfgSystemParams,		},
	//	{	ID_qyCfgBoard,		},				//  2008/12/28
	//	{	ID_qyCfgSp			},				//  2008/12/28
	{	-2,						},
	{	ID_qyCfgCustom,			},
	{	ID_qyCfgStandardNames,	},
	{	-2,						},
	{	ID_cfgOptions	},
	{	ID_cfgAdvancedOptions		},
	{	ID_CFGWARN,					},			//  2006/06/02
	{	-2,						},
	{	ID_CFGUSR		},
	{	-1,		NULL,			},
};
 


  QY_DMITEM  CONST_menuTable_chaKan_nms[]  =
{
	{	ID_VIEW_TOOLBAR,		},		//  MENUITEM "工具栏(&T)",                  
	{	ID_VIEW_STATUS_BAR,		},		//  MENUITEM "状态栏(&S)",                  
	{	-2,						},		//  MENUITEM SEPARATOR
#ifndef  __WINCE__
	{	ID_viewQnmStatus,		},		//  MENUITEM "系统状态窗(&Z)",   
	{	-2,						},
	{	ID_viewWarningTool,		},
#endif
	{	-2,						},		//  MENUITEM SEPARATOR
	{	ID_qyRefresh,			},		//  MENUITEM "刷新(&R)  F5",                
	{	-1,		NULL,			},
};


 QY_DMITEM  CONST_childFrmMenuTable_nms[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_wenJian,		(  TCHAR  *  )CONST_menuTable_wenJian,			},	//  2006/12/17
	{	-3,		(  TCHAR  *  )CONST_resId_menu_guanLi,  (  TCHAR  *  )CONST_menuTable_guanLi_nms,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_xiTong,  (  TCHAR  *  )CONST_menuTable_xiTong_nms,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,  (  TCHAR  *  )CONST_menuTable_peiZhi_nms,	},	
	{	ID_qyMakeClients,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chaKan,  (  TCHAR  *  )CONST_menuTable_chaKan_nms,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chuangKou,	(  TCHAR  *  )CONST_menuTable_chuangKou,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_bangZhu,  (  TCHAR  *  )CONST_menuTable_bangZhu,	},	
	{	-1,		NULL,		},
};

 QY_DMITEM  CONST_mainMenuTable_nms[]  =  
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_wenJian,		(  TCHAR  *  )CONST_menuTable_wenJian,			},	//  2006/12/17
	{	-3,		(  TCHAR  *  )CONST_resId_menu_guanLi,  (  TCHAR  *  )CONST_menuTable_guanLi_nms,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_xiTong,  (  TCHAR  *  )CONST_menuTable_xiTong_nms,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,  (  TCHAR  *  )CONST_menuTable_peiZhi_nms,	},	
	{	ID_qyMakeClients,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chaKan,  (  TCHAR  *  )CONST_menuTable_chaKan_nms,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_bangZhu,  (  TCHAR  *  )CONST_menuTable_bangZhu,	},	
	{	-1,		NULL,		},
};

 QY_DMITEM  CONST_cusMenusTable_nms[]  =
{
 	{	CONST_resId_mainMenu,				(  TCHAR  *  )CONST_mainMenuTable_nms,			},
	{	CONST_resId_childFrmMenu,			(  TCHAR  *  )CONST_childFrmMenuTable_nms,		},
	{	CONST_resId_popupMenu,				(  TCHAR  *  )CONST_popupMenuTable_netMc,					},
	{	-1,		},
};

 QY_DMITEM  CONST_ruleTypeTable_nms[]  =
{
#if  0
	{	CONST_ruleType_switch,		CONST_str_snmpObjRule,			},
	{	CONST_ruleType_switchPort,	CONST_str_snmpObjPortRule,			},
#endif 
	{	-1,							NULL,				},
};





 QY_DMITEM  CONST_queryTypeTable_nms[]  =
{
	{	CONST_qyQueryType_netDevEventList,			CONST_str_wangLuoSheBeiShiJianChaXun/*  _T(  "网络设备事件查询"  )  */,		},
	{	CONST_qyQueryType_netMcEventList,			CONST_str_jiSuanJiShiJianChaXun/*  _T(  "计算机事件查询"  )  */,		},
	{	CONST_qyQueryType_netMcPcList,				CONST_str_jiSuanJiChaXun/*  _T(  "计算机查询"  )  */,			},
	{	CONST_qyQueryType_netMcPcSpList,			CONST_str_buDingChaXun/*  _T(  "补丁查询"  )  */,				},
	{	CONST_qyQueryType_mac,						CONST_str_macChaXun/*  _T(  "MAC查询"  )  */,				},
	{	CONST_qyQueryType_ip,						CONST_str_ipChaXun/*  _T(  "IP查询"  )  */,				},
	{	CONST_qyQueryType_unusedConn,				CONST_str_wuXiaoLianJieChaXun/*  _T(  "无效联接查询"  )  */,			},
	{	CONST_qyQueryType_opEventList,				CONST_str_xiTongShiJianChaXun/*  _T(  "系统事件查询"  )  */,			},		//  2006/02/25
	{	-1,											NULL,					},

};

////////////// 2008/12/27
 QY_DMITEM  CONST_snmpBoolTable[]  =
{
	{	CONST_snmpTrue,		CONST_str_yes,	},
	{	CONST_snmpFalse,	CONST_str_no,	},
	{	-1,					NULL,	},
};



//////////////



   QY_DMITEM  CONST_tableTable_nms[]  =
{
	{ 	CONST_resId_qnmEventTypeTable0,			(  TCHAR  *  )CONST_qnmEventTypeTable0_netMc,		},
	{	CONST_resId_qnmEventTypeTable_pc,		(  TCHAR  *  )CONST_qnmEventTypeTable_nms,		},
	{	CONST_resId_qnmEventTypeTable_op,		(  TCHAR  *  )CONST_qnmEventTypeTable_op_netMc,		},
	{	CONST_resId_qnmEventTypeTable_netDev,	(  TCHAR  *  )CONST_qnmEventTypeTable_nmsNetDev,	},
	{	CONST_resId_ipScanOfficeLevelTable,		(  TCHAR  *  )CONST_ipScanOfficeLevelTable,	},
	{	CONST_resId_zjgaYhlxTable,				(  TCHAR  *  )CONST_zjgaYhlxTable,			},
	{	CONST_resId_gYhGrpTable,				(  TCHAR  *  )gYhGrpTable,					},
	{	CONST_resId_gEventYhGrpTable,			(  TCHAR  *  )gEventYhGrpTable,				},
	//  {	CONST_resId_qnmEventTypeTable_secChk,	(  TCHAR  *  )CONST_qnmEventTypeTable_secChk,	},
	{	CONST_resId_qyNullTable,				(  TCHAR  *  )CONST_nullTable,				},
	{	CONST_resId_jqlxTable,					(  TCHAR  *  )CONST_jqlxTable,					},
	{	CONST_resId_qySystemIdTable,			(  TCHAR  *  )CONST_qySystemIdTable,				},
	{	CONST_resId_ucbDsnlessTable,			(  TCHAR  *  )CONST_ucbDsnlessTable,				},
	{	CONST_resId_myCONST_yhGrpTable_netMc,	(  TCHAR  *  )myCONST_yhGrpTable_netMc,				},
	{	CONST_resId_myCONST_eventYhGrpTable_netMc,(  TCHAR  *  )myCONST_eventYhGrpTable_netMc,		},
	{	CONST_resId_myCONST_yhGrpTable_is,		(  TCHAR  *  )myCONST_yhGrpTable_is,				},
	{	CONST_resId_myCONST_eventYhGrpTable_is,	(  TCHAR  *  )myCONST_eventYhGrpTable_is,			},
	//
	{	CONST_resId_queryTypeTable,				(  TCHAR  *  )CONST_queryTypeTable_nms,				},
	{	CONST_resId_ruleTypeTable,				(  TCHAR  *  )CONST_ruleTypeTable_nms,					},
	//
	{	CONST_resId_snmpBoolTable,				(  TCHAR  *  )CONST_snmpBoolTable,					},
	{	CONST_resId_fieldIdTable,				(  TCHAR  *  )CONST_fieldIdTable,					},
	//  2009/01/01
	{	CONST_resId_qyCommTypeTable,			(  TCHAR  *  )CONST_qyCommTypeTable,				},
	{	CONST_resId_pcCommTypeTable,			(  TCHAR  *  )CONST_pcCommTypeTable,				},
	{	CONST_resId_grpNameTable,				(  TCHAR  *  )CONST_grpNameTable,					},
	{	CONST_resId_usRunningStatusTable,		(  TCHAR  *  )CONST_usRunningStatusTable,			},


	{	-1,		NULL,		},
};

  QY_DMITEM  CONST_cusResTable_nms[]  =
{

	{	CONST_resType_str,						(  TCHAR  *  )CONST_strTable_netMc,						},
	{	CONST_resType_table,					(  TCHAR  *  )CONST_tableTable_nms,			},
	{	CONST_resType_dlg,						(  TCHAR  *  )CONST_dlgTable,						},
 	{	CONST_resType_menu,						(  TCHAR  *  )CONST_cusMenusTable_nms,			},
	{	CONST_resType_query,					(  TCHAR  *  )CONST_queryTable,						},
	{	CONST_resType_search,					(  TCHAR  *  )CONST_searchTable,						},
	{	CONST_resType_columnInfo,				(  TCHAR  *  )CONST_columnInfoTable,				},
	{	-1,		NULL,		},
};


