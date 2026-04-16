

#include	"stdafx.h"
#include	<tchar.h>

#include	"myresource_main_ts.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"isCmdConst.h"



///////////////////////////////////  }

 QY_DMITEM  CONST_cusMenusTable_isCli_ts[]  =
{
#if  0
	{	CONST_resId_mainMenu,				(  TCHAR  *  )CONST_mainMenuTable_misClient,			},
	{	CONST_resId_childFrmMenu,			(  TCHAR  *  )CONST_childFrmMenuTable_misClient,		},
	{	CONST_resId_winceMenu,				(  TCHAR  *  )CONST_winCeMenuTable_misClient,			},			//  2010/04/13
#endif
	{	CONST_resId_popupMenu,				(  TCHAR  *  )CONST_popupMenuTable_mis_ts,					},
	{	-1,		NULL,		},
};


  QY_DMITEM  CONST_queryTypeTable_isCli_ts[]  =
{
#if  0
	{	CONST_qyQueryType_imMsgList,				CONST_str_imMsgChaXun,		},
	{	CONST_qyQueryType_opEventList,				CONST_str_xiTongShiJianChaXun,			},		//  2006/02/25
#endif
	{	-1,											NULL,					},
};





 



  QY_DMITEM  CONST_tableTable_isCli_ts[]  =
{
	{ 	CONST_resId_qnmEventTypeTable0,			(  TCHAR  *  )CONST_qnmEventTypeTable0_is,		},
	{	CONST_resId_qnmEventTypeTable_pc,		(  TCHAR  *  )CONST_qnmEventTypeTable_assetMgr,		},
	{	CONST_resId_qnmEventTypeTable_op,		(  TCHAR  *  )CONST_qnmEventTypeTable_op_is,		},
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
	{	CONST_resId_objTypeTable,				(  TCHAR  *  )CONST_objTypeTable,					},
	{	CONST_resId_queryTypeTable,				(  TCHAR  *  )CONST_queryTypeTable_isCli_ts,		},
	{	CONST_resId_fieldIdTable,				(  TCHAR  *  )CONST_fieldIdTable,					},
	//
	{	CONST_resId_imTaskTypeTable,			(  TCHAR  *  )CONST_imTaskTypeTable,				},
	{	CONST_resId_qyStatusTable,				(  TCHAR  *  )CONST_qyStatusTable,					},
	{	CONST_resId_imTaskStatusTable,			(  TCHAR  *  )CONST_imTaskStatusTable,				},
	//  2009/01/01
	{	CONST_resId_qyCommTypeTable,			(  TCHAR  *  )CONST_qyCommTypeTable,				},
	{	CONST_resId_pcCommTypeTable,			(  TCHAR  *  )CONST_pcCommTypeTable,				},
	{	CONST_resId_grpNameTable,				(  TCHAR  *  )CONST_grpNameTable,					},
	{	CONST_resId_usRunningStatusTable,		(  TCHAR  *  )CONST_usRunningStatusTable,			},

	//
	{	CONST_resId_ruleTypeTable,				(  TCHAR  *  )CONST_ruleTypeTable_is,					},
	{	CONST_resId_usLayoutTypeTable,			(  TCHAR  *  )CONST_usLayoutTypeTable,				},
	{	CONST_resId_usLayoutTypeTable_resource,	(  TCHAR  *  )CONST_usLayoutTypeTable_resource,		},
	{	CONST_resId_ruleCmdTable,				(  TCHAR  *  )CONST_ruleCmdTable,					},
	{	CONST_resId_ruleCmdTable_autoAnswer,	(  TCHAR  *  )CONST_ruleCmdTable_autoAnswer,		},

	//  {	CONST_resId_remoteVideoTable,			(  TCHAR  *  )CONST_remoteVideoTable,				},
	//
	//  {	CONST_resId_menu_conferenceWall,		(  TCHAR  *  )CONST_menuTable_conferenceWall,		},
	{	CONST_resId_policyAvLevelTable_basic,	(  TCHAR  *  )CONST_policyAvLevelTable_basic,		},
	{	CONST_resId_policyAvLevelTable_standard,(  TCHAR  *  )CONST_policyAvLevelTable_standard,	},
	{	CONST_resId_policyAvLevelTable_high,	(  TCHAR  *  )CONST_policyAvLevelTable_high,		},
#if  0
	{	CONST_resId_policyAvLevelTable_screen_basic,		(  TCHAR  *  )CONST_policyAvLevelTable_screen_basic,		},
	{	CONST_resId_policyAvLevelTable_screen_standard,		(  TCHAR  *  )CONST_policyAvLevelTable_screen_standard,		},
	{	CONST_resId_policyAvLevelTable_screen_high,			(  TCHAR  *  )CONST_policyAvLevelTable_screen_high,		},
	{	CONST_resId_policyAvLevelTable_mediaFile_basic,		(  TCHAR  *  )CONST_policyAvLevelTable_mediaFile_basic,	},
	{	CONST_resId_policyAvLevelTable_mediaFile_standard,	(  TCHAR  *  )CONST_policyAvLevelTable_mediaFile_standard,	},
	{	CONST_resId_policyAvLevelTable_mediaFile_high,		(  TCHAR  *  )CONST_policyAvLevelTable_mediaFile_high,	},
	{	CONST_resId_policyAvLevelTable_mediaDevice_basic,	(  TCHAR  *  )CONST_policyAvLevelTable_mediaDevice_basic,  },
	{	CONST_resId_policyAvLevelTable_mediaDevice_standard,(  TCHAR  *  )CONST_policyAvLevelTable_mediaDevice_standard,  },
	{	CONST_resId_policyAvLevelTable_mediaDevice_high,	(  TCHAR  *  )CONST_policyAvLevelTable_mediaDevice_high,  },
	{	CONST_resId_policyAvLevelTable_webcam_basic,		(  TCHAR  *  )CONST_policyAvLevelTable_webcam_basic,		},
	{	CONST_resId_policyAvLevelTable_webcam_standard,		(  TCHAR  *  )CONST_policyAvLevelTable_webcam_standard,		},
#endif
	{	-1,		NULL,		},
};


 QY_DMITEM  CONST_cusResTable_isCli_ts[]  =
{
 	{	CONST_resType_str,						(  TCHAR  *  )CONST_strTable_ts,						},
	{	CONST_resType_table,					(  TCHAR  *  )CONST_tableTable_isCli_ts,			},
	{	CONST_resType_dlg,						(  TCHAR  *  )CONST_dlgTable_ts,						},
 	{	CONST_resType_menu,						(  TCHAR  *  )CONST_cusMenusTable_isCli_ts,				},
	{	CONST_resType_query,					(  TCHAR  *  )CONST_queryTable_mis,						},
	{	CONST_resType_search,					(  TCHAR  *  )CONST_searchTable,						},
	{	CONST_resType_columnInfo,				(  TCHAR  *  )CONST_columnInfoTable,				},
	{	-1,		NULL,		},
};



