
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


 QY_DMITEM	CONST_menuTable_jiSuanJiGuanLi_secChk[]  =
{
	{	ID_qyPcList,			},
	{	ID_qyPcSpList,			},
	{	-1,		NULL,			},
};

 QY_DMITEM	CONST_menuTable_yongHuGuanLi_secChk[]  =
{	{	ID_qyPcUsrList,			},
	{	ID_qyPcUsrInTab1List,	},
	{	-1,		NULL,			},
};

 QY_DMITEM	CONST_menuTable_keHuDuanGuanLi_secChk[]  =
{
	{	ID_qwmSvrList,			},
	{	-1,		NULL,			},
};

 QY_DMITEM	CONST_menuTable_jiSuanJiAnQuanGuanLi_secChk[]  =
{
	{	ID_pcRuleList0,			},
	{	-1,		NULL,			},
};

 QY_DMITEM	CONST_menuTable_shiJianChaKan_secChk[]  =
{
	//  {	ID_pcSecChkEventList,			},		//  20060315,wqh
	//  {	-2,								},
	{	ID_qyEventAll,			},
	{	-2,						},
	{	ID_qyOpEventAll,		},
	{	-1,		NULL,			},
};

 QY_DMITEM	CONST_menuTable_guanLi_secChk[] =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_jiSuanJiGuanLi,			(  TCHAR  *  )CONST_menuTable_jiSuanJiGuanLi_secChk,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_yongHuGuanLi,			(  TCHAR  *  )CONST_menuTable_yongHuGuanLi_secChk,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_keHuDuanGuanLi,			(  TCHAR  *  )CONST_menuTable_keHuDuanGuanLi_secChk,	},
	{	-2,						},			
	//  {	-3,		(  TCHAR  *  )CONST_resId_menu_jiSuanJiAnQuanGuanLi,			(  TCHAR  *  )CONST_menuTable_jiSuanJiAnQuanGuanLi_secChk,	},
	{	ID_pcRuleList0,			},
	{	-2,						},
	{	ID_pcSecChkEventList,	},
	{	-2,						},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_shiJianChaKan,			(  TCHAR  *  )CONST_menuTable_shiJianChaKan_secChk,	},	
	//  {	-2,						},
	//  {	ID_qySearch,			},
	//  {	ID_qyStat,				},
	//  {	-2,						},
	//  {	ID_qyImport,			},
	//  {	ID_qyExport,			},
	//  {	ID_qyClearUp,			},
	//  {	-2,						},
	//  {	ID_FILE_PRINT_SETUP,	},
	//  {	ID_FILE_PRINT,			},
	//  {	-2,						},
	//  {	ID_APP_EXIT,			},
	{	-1,		NULL,			},
};

 QY_DMITEM	CONST_menuTable_xiTong_secChk[]  =
{
	{	ID_qyStopSecChk,		},
	{	ID_qyStartSecChk,		},
	{	-1,		NULL,			},
};

 QY_DMITEM	CONST_menuTable_peiZhi_secChk[]  =
{
	{	ID_cfgSystemParams,		},
	{	-2,						},
	{	ID_qyCfgCustom,			},
	{	ID_qyCfgStandardNames,	},
	{	-2,						},
	{	ID_cfgOptions	},
	{	ID_cfgAdvancedOptions		},
	{	-2,						},
	{	ID_CFGUSR		},
	{	-1,		NULL,			},
};

 QY_DMITEM	CONST_mainMenuTable_secChk[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_wenJian,		(  TCHAR  *  )CONST_menuTable_wenJian,			},	//  2006/12/17
	{	-3,		(  TCHAR  *  )CONST_resId_menu_guanLi,  (  TCHAR  *  )CONST_menuTable_guanLi_secChk,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_xiTong,  (  TCHAR  *  )CONST_menuTable_xiTong_secChk,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,  (  TCHAR  *  )CONST_menuTable_peiZhi_secChk,	},	
	{	ID_qyMakeClients,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chaKan,  (  TCHAR  *  )CONST_menuTable_chaKan_netMc,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_bangZhu,  (  TCHAR  *  )CONST_menuTable_bangZhu,	},	
	{	-1,		NULL,			},
};

 QY_DMITEM  CONST_childFrmMenuTable_secChk[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_wenJian,		(  TCHAR  *  )CONST_menuTable_wenJian,			},	//  2006/12/17
	{	-3,		(  TCHAR  *  )CONST_resId_menu_guanLi,  (  TCHAR  *  )CONST_menuTable_guanLi_secChk,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_xiTong,  (  TCHAR  *  )CONST_menuTable_xiTong_secChk,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,  (  TCHAR  *  )CONST_menuTable_peiZhi_secChk,	},	
	{	ID_qyMakeClients,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chaKan,  (  TCHAR  *  )CONST_menuTable_chaKan_netMc,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chuangKou,	(  TCHAR  *  )CONST_menuTable_chuangKou,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_bangZhu,  (  TCHAR  *  )CONST_menuTable_bangZhu,	},	
	{	-1,		NULL,		},
};


   QY_DMITEM  CONST_cusMenusTable_secChk[]  =
{
	{	CONST_resId_mainMenu,				(  TCHAR  *  )CONST_mainMenuTable_secChk,			},
	{	CONST_resId_childFrmMenu,			(  TCHAR  *  )CONST_childFrmMenuTable_secChk,		},
	{	CONST_resId_popupMenu,				(  TCHAR  *  )CONST_popupMenuTable_netMc,					},
	{	-1,		NULL,		},
};

 QY_DMITEM  CONST_qyeryTypeTable_secChk[]  =
{
	{	CONST_qyQueryType_netMcEventList,			CONST_str_jiSuanJiShiJianChaXun/*  _T(  "计算机事件查询"  )  */,		},
	{	CONST_qyQueryType_netMcPcList,				CONST_str_jiSuanJiChaXun/*  _T(  "计算机查询"  )  */,			},
	{	CONST_qyQueryType_secChkEventList,			CONST_str_jianChaJieGuoChaXun,  },
	{	CONST_qyQueryType_netMcPcSpList,			CONST_str_buDingChaXun/*  _T(  "补丁查询"  )  */,				},
	{	CONST_qyQueryType_opEventList,				CONST_str_xiTongShiJianChaXun/*  _T(  "系统事件查询"  )  */,			},		//  2006/02/25
	{	-1,											NULL,					},

};

 QY_DMITEM  CONST_tableTable_secChk[]  =
{
	{ 	CONST_resId_qnmEventTypeTable0,			(  TCHAR  *  )CONST_qnmEventTypeTable0_netMc,					},
	{	CONST_resId_qnmEventTypeTable_pc,		(  TCHAR  *  )CONST_qnmEventTypeTable_secChk,			},
	{	CONST_resId_qnmEventTypeTable_op,		(  TCHAR  *  )CONST_qnmEventTypeTable_op_netMc,				},
	//  {	CONST_resId_qnmEventTypeTable_netDev,	(  TCHAR  *  )CONST_qnmEventTypeTable_nmsNetDev,	},
	{	CONST_resId_ipScanOfficeLevelTable,		(  TCHAR  *  )CONST_ipScanOfficeLevelTable,				},
	{	CONST_resId_zjgaYhlxTable,				(  TCHAR  *  )CONST_zjgaYhlxTable,						},
	{	CONST_resId_gYhGrpTable,				(  TCHAR  *  )gYhGrpTable,								},
	{	CONST_resId_gEventYhGrpTable,			(  TCHAR  *  )gEventYhGrpTable,							},
	{	CONST_resId_secChkEventTypeTable,		(  TCHAR  *  )CONST_secChkEventTypeTable_secChk,		},
	{	CONST_resId_qyNullTable,				(  TCHAR  *  )CONST_nullTable,							},
	{	CONST_resId_jqlxTable,					(  TCHAR  *  )CONST_jqlxTable,							},
	{	CONST_resId_qySystemIdTable,			(  TCHAR  *  )CONST_qySystemIdTable,				},
	{	CONST_resId_ucbDsnlessTable,			(  TCHAR  *  )CONST_ucbDsnlessTable,				},
	{	CONST_resId_myCONST_yhGrpTable_netMc,	(  TCHAR  *  )myCONST_yhGrpTable_netMc,				},
	{	CONST_resId_myCONST_eventYhGrpTable_netMc,(  TCHAR  *  )myCONST_eventYhGrpTable_netMc,		},
	{	CONST_resId_myCONST_yhGrpTable_is,		(  TCHAR  *  )myCONST_yhGrpTable_is,				},
	{	CONST_resId_myCONST_eventYhGrpTable_is,	(  TCHAR  *  )myCONST_eventYhGrpTable_is,			},
	{	CONST_resId_queryTypeTable,				(  TCHAR  *  )CONST_qyeryTypeTable_secChk,				},
	{	CONST_resId_fieldIdTable,				(  TCHAR  *  )CONST_fieldIdTable,					},
	//  2009/01/01
	{	CONST_resId_qyCommTypeTable,			(  TCHAR  *  )CONST_qyCommTypeTable,				},
	{	CONST_resId_pcCommTypeTable,			(  TCHAR  *  )CONST_pcCommTypeTable,				},
	{	CONST_resId_grpNameTable,				(  TCHAR  *  )CONST_grpNameTable,					},
	{	CONST_resId_usRunningStatusTable,		(  TCHAR  *  )CONST_usRunningStatusTable,			},



	{	-1,		NULL,		},
};

 QY_DMITEM  CONST_cusResTable_secChk[]  =
{
 	{	CONST_resType_str,						(  TCHAR  *  )CONST_strTable_netMc,						},
	{	CONST_resType_table,					(  TCHAR  *  )CONST_tableTable_secChk,			},
	{	CONST_resType_dlg,						(  TCHAR  *  )CONST_dlgTable,						},
 	{	CONST_resType_menu,						(  TCHAR  *  )CONST_cusMenusTable_secChk,			},
	{	CONST_resType_query,					(  TCHAR  *  )CONST_queryTable,						},
	{	CONST_resType_search,					(  TCHAR  *  )CONST_searchTable,						},
	{	CONST_resType_columnInfo,				(  TCHAR  *  )CONST_columnInfoTable,				},
	{	-1,		NULL,		},
};
