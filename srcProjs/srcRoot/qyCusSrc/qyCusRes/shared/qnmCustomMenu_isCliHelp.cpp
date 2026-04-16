

#include	"stdafx.h"
#include	<tchar.h>

#include	"myresource_main_isCliHelp.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"isCmdConst.h"

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_is.h"

  extern  QY_DMITEM		CONST_popupMenuTable_isCliHelp[];





///////////////////////////////////  }


 QY_DMITEM  CONST_cusMenusTable_misClientHelp[]  =
{
	//  {	CONST_resId_mainMenu,				(  TCHAR  *  )CONST_mainMenuTable_misClient,			},
	//  {	CONST_resId_childFrmMenu,			(  TCHAR  *  )CONST_childFrmMenuTable_misClient,		},
	{	CONST_resId_popupMenu,				(  TCHAR  *  )CONST_popupMenuTable_isCliHelp,			},
	//  {	CONST_resId_winceMenu,				(  TCHAR  *  )CONST_winCeMenuTable_misClient,			},			//  2010/04/13
	{	-1,		NULL,		},
};

  QY_DMITEM  CONST_queryTypeTable_isCliHelp[]  =
{
	{	CONST_qyQueryType_imMsgList,				CONST_str_imMsgChaXun,		},
#if 0
	{	CONST_qyQueryType_opEventList,				CONST_str_xiTongShiJianChaXun,			},		//  2006/02/25
#endif
	{	-1,											NULL,					},
};

  //  2008/12/29
 QY_DMITEM  CONST_imTaskTypeTable_isCliHelp[]  =
{
	{	CONST_imTaskType_sendFile,					CONST_str_sendFile,						},
	{	CONST_imTaskType_recvFile,					CONST_str_recvFile,						},
	//
	{	CONST_imTaskType_transferAvInfo,			CONST_str_av,							},
	{	CONST_imTaskType_shareScreen,				CONST_str_shareScreen,					},
	{	CONST_imTaskType_remoteAssist,				CONST_str_remoteAssist,					},
	{	CONST_imTaskType_shareMediaFile,			CONST_str_shareMediaFile,		},
	{	CONST_imTaskType_shareDynBmp,				CONST_str_shareDynBmp,			},
	{	CONST_imTaskType_viewDynBmp,				CONST_str_viewDynBmp,			},
	{	CONST_imTaskType_queryCustomerServiceOfficer,CONST_str_queryCustomerServiceOfficer,	},
	//
	{	CONST_imTaskType_shareGps,					CONST_str_shareGps,				},
	{	CONST_imTaskType_viewGps,					CONST_str_viewGps,				},

	//
	{	-1,											},
};

#if  0
 //  2010/09/08
 QY_DMITEM	CONST_ruleCmdTable_autoAnswer_isCliHelp[]  =
{
	{	CONST_ruleCmd_null,									_T(  ""  ),	},
	{	CONST_ruleCmd_permit,								CONST_str_permit,	},
	{	CONST_ruleCmd_permitAndFullscreen,					CONST_str_permitAndFullscreen,	},
	{	-1,			},
};

 QY_DMITEM	CONST_remoteVideoTable_isCliHelp[]  =
{
	{	CONST_resId_selectScreen,	CONST_IDC_STATIC00,	},
	{	CONST_resId_selectWebcam0,	CONST_IDC_STATIC10,	},
	{	CONST_resId_selectWebcam1,	CONST_IDC_STATIC11,	},
	{	CONST_resId_selectWebcam2,	CONST_IDC_STATIC12,	},
	{	-1,			},
};
#endif

 //  2014/06/03
 QY_DMITEM	CONST_dynBmpTypeTable_isCliHelp[]  =
{
	{	CONST_objType_webcam,				_T(  "Webcam"  ),				},
	{	CONST_objType_screen,				_T(  "Screen"  ),				},
	{	CONST_objType_rtspStream,			_T(  "Rtsp"  ),					},

	//
	{	CONST_objType_smallStream,				_T(  "Small Stream"  ),				},		//  2018/12/14
	{	CONST_objType_ic,			        _T("IC"),					},

	{	-1,			},
};

 //  2009/01/01
 QY_DMITEM  CONST_qyStatusTable_isCliHelp[]  =
{
	{	CONST_qyStatus_ok,										_T(  "OK"  ),						},
	//	
	{	CONST_qyStatus_del,										_T(  "Del"  ),						},
	{	CONST_qyStatus_update,									_T(  "Update"  ),					},
	//
	{	CONST_qyStatus_err,										_T(  "Error"  ),					},		//  这里是-1，所以Error显示不了了
	//
	{	CONST_imTaskStatus_req,									CONST_str_qingqiu,					},		//  2007/10/07
	{	CONST_imTaskStatus_resp,								CONST_str_xiangYing,				},
	//
	{	CONST_imTaskStatus_applyToSend,							CONST_str_reqToSend,				},
	{	CONST_imTaskStatus_waitToSend,							CONST_str_waitToSend,				},
	{	CONST_imTaskStatus_applyToRecv,							CONST_str_reqToRecv,				},
	{	CONST_imTaskStatus_waitToRecv,							CONST_str_waitToRecv,				},
    //
	{	CONST_imTaskStatus_sending,								CONST_str_sending,					},
	{	CONST_imTaskStatus_receiving,							CONST_str_receiving,				},
	//
	{	CONST_imTaskStatus_sendBreak,							CONST_str_sendBreak,				},
	{	CONST_imTaskStatus_recvBreak,							CONST_str_recvBreak,				},
	//
	{	CONST_imTaskStatus_recvFinished,						CONST_str_finished,					},
	{	CONST_imTaskStatus_sendFinished,						CONST_str_finished,					},
	//
	{	CONST_imTaskStatus_acceptedByReceiver,					CONST_str_acceptedByReceiver,		},
	{	CONST_imTaskStatus_dualByReceiver,						CONST_str_dualByReceiver,		},
	//
	{	CONST_imTaskStatus_err_missingOrgReq,					CONST_str_err_missingOrgReq,		},
    //
	{	CONST_imTaskStatus_canceledBySender,					CONST_str_canceledBySender,			},
	{	CONST_imTaskStatus_canceledByReceiver,					CONST_str_canceledByReceiver,		},
	{	CONST_imTaskStatus_deniedByReceiver,					CONST_str_deniedByReceiver,			},
	//
	//
	{	-1,																		},
};
 
  QY_DMITEM  CONST_policyAvLevelTable_screen_basic_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	-1,											NULL,								},
};
  QY_DMITEM  CONST_policyAvLevelTable_screen_standard_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_5fps,				CONST_IDC_BUTTON_setDev5fpsSettings,},
	//  2012/10/29
	{	CONST_policyAvLevel_dev_5fps1,				CONST_IDC_BUTTON_setDev5fpsSettings1,},
	//  2015/11/06
	{	CONST_policyAvLevel_dev_5fps2,				CONST_IDC_BUTTON_setDev5fpsSettings2,},
#if 0 
	{	CONST_policyAvLevel_dev_5fps3,				CONST_IDC_BUTTON_setDev5fpsSettings3,},
	{	CONST_policyAvLevel_dev_5fps4,				CONST_IDC_BUTTON_setDev5fpsSettings4,},
	{	CONST_policyAvLevel_dev_5fps5,				CONST_IDC_BUTTON_setDev5fpsSettings5,},
#endif
	//
	{	-1,											NULL,								},
};
  QY_DMITEM  CONST_policyAvLevelTable_screen_high_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_5fps,				CONST_IDC_BUTTON_setDev5fpsSettings,},
	//  2012/10/29
	{	CONST_policyAvLevel_dev_5fps1,				CONST_IDC_BUTTON_setDev5fpsSettings1,},
	//  2015/11/06
	{	CONST_policyAvLevel_dev_5fps2,				CONST_IDC_BUTTON_setDev5fpsSettings2,},
#if  0
	{	CONST_policyAvLevel_dev_5fps3,				CONST_IDC_BUTTON_setDev5fpsSettings3,},
	{	CONST_policyAvLevel_dev_5fps4,				CONST_IDC_BUTTON_setDev5fpsSettings4,},
	{	CONST_policyAvLevel_dev_5fps5,				CONST_IDC_BUTTON_setDev5fpsSettings5,},
#endif
	//
	{	-1,											NULL,								},
};

#if  0
 QY_DMITEM  CONST_policyAvLevelTable_mediaFile_basic_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_10fps,				CONST_IDC_BUTTON_setDev10fpsSettings,},
	{	-1,											NULL,								},
};

 QY_DMITEM  CONST_policyAvLevelTable_mediaFile_standard_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_5fps1,				CONST_IDC_BUTTON_setDev5fpsSettings1,},
#if  0
	{	CONST_policyAvLevel_dev_5fps2,				CONST_IDC_BUTTON_setDev5fpsSettings2,},
	{	CONST_policyAvLevel_dev_5fps3,				CONST_IDC_BUTTON_setDev5fpsSettings3,},
#endif
#if  0
	{	CONST_policyAvLevel_dev_sd24fps,			CONST_IDC_BUTTON_setDevSd24fpsSettings,},
	{	CONST_policyAvLevel_dev_sd25fps,			CONST_IDC_BUTTON_setDevSd25fpsSettings,},
	{	CONST_policyAvLevel_dev_sd30fps,			CONST_IDC_BUTTON_setDevSd30fpsSettings,},
#endif
	//
	{	CONST_policyAvLevel_dev_24fps,				CONST_IDC_BUTTON_setDev24fpsSettings,},
	{	CONST_policyAvLevel_dev_25fps,				CONST_IDC_BUTTON_setDev25fpsSettings,},
	{	CONST_policyAvLevel_dev_30fps,				CONST_IDC_BUTTON_setDev30fpsSettings,},

	{	-1,											NULL,								},
};

 QY_DMITEM  CONST_policyAvLevelTable_mediaFile_high_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_5fps1,				CONST_IDC_BUTTON_setDev5fpsSettings1,},
#if  0
	{	CONST_policyAvLevel_dev_5fps2,				CONST_IDC_BUTTON_setDev5fpsSettings2,},
	{	CONST_policyAvLevel_dev_5fps3,				CONST_IDC_BUTTON_setDev5fpsSettings3,},
#endif
#if  0
	{	CONST_policyAvLevel_dev_sd24fps,			CONST_IDC_BUTTON_setDevSd24fpsSettings,},
	{	CONST_policyAvLevel_dev_sd25fps,			CONST_IDC_BUTTON_setDevSd25fpsSettings,},
	{	CONST_policyAvLevel_dev_sd30fps,			CONST_IDC_BUTTON_setDevSd30fpsSettings,},
#endif
	{	CONST_policyAvLevel_dev_24fps,				CONST_IDC_BUTTON_setDev24fpsSettings,},
	{	CONST_policyAvLevel_dev_25fps,				CONST_IDC_BUTTON_setDev25fpsSettings,},
	{	CONST_policyAvLevel_dev_30fps,				CONST_IDC_BUTTON_setDev30fpsSettings,},
	{	-1,											NULL,								},
};

 QY_DMITEM  CONST_policyAvLevelTable_mediaDevice_basic_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	-1,											NULL,								},
};
 QY_DMITEM  CONST_policyAvLevelTable_mediaDevice_standard_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_5fps1,				CONST_IDC_BUTTON_setDev5fpsSettings1,},
#if  0
	{	CONST_policyAvLevel_dev_5fps2,				CONST_IDC_BUTTON_setDev5fpsSettings2,},
	{	CONST_policyAvLevel_dev_5fps3,				CONST_IDC_BUTTON_setDev5fpsSettings3,},
#endif
	{	CONST_policyAvLevel_dev_sd24fps,			CONST_IDC_BUTTON_setDevSd24fpsSettings,},
	{	CONST_policyAvLevel_dev_sd25fps,			CONST_IDC_BUTTON_setDevSd25fpsSettings,},
	{	CONST_policyAvLevel_dev_sd30fps,			CONST_IDC_BUTTON_setDevSd30fpsSettings,},
	{	-1,											NULL,								},
};
 QY_DMITEM  CONST_policyAvLevelTable_mediaDevice_high_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_5fps1,				CONST_IDC_BUTTON_setDev5fpsSettings1,},
#if  0
	{	CONST_policyAvLevel_dev_5fps2,				CONST_IDC_BUTTON_setDev5fpsSettings2,},
	{	CONST_policyAvLevel_dev_5fps3,				CONST_IDC_BUTTON_setDev5fpsSettings3,},
#endif
	{	CONST_policyAvLevel_dev_sd24fps,			CONST_IDC_BUTTON_setDevSd24fpsSettings,},
	{	CONST_policyAvLevel_dev_sd25fps,			CONST_IDC_BUTTON_setDevSd25fpsSettings,},
	{	CONST_policyAvLevel_dev_sd30fps,			CONST_IDC_BUTTON_setDevSd30fpsSettings,},
	{	CONST_policyAvLevel_dev_24fps,				CONST_IDC_BUTTON_setDev24fpsSettings,},
	{	CONST_policyAvLevel_dev_25fps,				CONST_IDC_BUTTON_setDev25fpsSettings,},
	{	CONST_policyAvLevel_dev_30fps,				CONST_IDC_BUTTON_setDev30fpsSettings,},
	{	-1,											NULL,								},
};
#endif
 QY_DMITEM  CONST_usLayoutTypeTable_isCliHelp[]  =
{
	{		CONST_usLayoutType_null,							CONST_str_layout_auto,				},
	{		CONST_usLayoutType_dialog,							CONST_str_layout_dialog,			},
	{		CONST_usLayoutType_conference,						CONST_str_layout_conference,		},
	{		CONST_usLayoutType_training,						CONST_str_layout_training,			},
	{		CONST_usLayoutType_videoOnly,						CONST_str_layout_videoOnly,		},
	{		CONST_usLayoutType_resourceOnly,					CONST_str_layout_resourceOnly,		},
	{		-1,						},
};
 QY_DMITEM  CONST_usLayoutTypeTable_resource_isCliHelp[]  =
{
	{		CONST_usLayoutType_null,							CONST_str_layout_auto,				},
	{		CONST_usLayoutType_dialog,							CONST_str_layout_dialog,			},
	{		CONST_usLayoutType_resourceOnly,					CONST_str_layout_resourceOnly,		},
	{		-1,						},
};


  QY_DMITEM  CONST_tableTable_misClientHelp[]  =
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
	//
	{	CONST_resId_imGrpSubtypeTable,			(  TCHAR  *  )CONST_imGrpSubtypeTable,				},
	{	CONST_resId_imGrpMemRoleTable,			(  TCHAR  *  )CONST_imGrpMemRoleTable,				},			//  2015/07/28
	//
	{	CONST_resId_imObjRoleTable,				(  TCHAR  *  )CONST_imObjRoleTable,				},
	//
	{	CONST_resId_queryTypeTable,				(  TCHAR  *  )CONST_queryTypeTable_isClient,		},
	{	CONST_resId_fieldIdTable,				(  TCHAR  *  )CONST_fieldIdTable,					},
	//
	{	CONST_resId_imTaskTypeTable,			(  TCHAR  *  )CONST_imTaskTypeTable,				},
	{	CONST_resId_qyStatusTable,				(  TCHAR  *  )CONST_qyStatusTable,					},
	{	CONST_resId_imTaskStatusTable,				(  TCHAR  *  )CONST_imTaskStatusTable,				},
	//  2009/01/01
	{	CONST_resId_qyCommTypeTable,			(  TCHAR  *  )CONST_qyCommTypeTable,				},
	{	CONST_resId_pcCommTypeTable,			(  TCHAR  *  )CONST_pcCommTypeTable,				},
	{	CONST_resId_grpNameTable,				(  TCHAR  *  )CONST_grpNameTable,					},
	{	CONST_resId_usRunningStatusTable,		(  TCHAR  *  )CONST_usRunningStatusTable,			},

	//
	{	CONST_resId_ruleTypeTable,				(  TCHAR  *  )CONST_ruleTypeTable_is,				},
	{	CONST_resId_usLayoutTypeTable,			(  TCHAR  *  )CONST_usLayoutTypeTable,				},
	{	CONST_resId_usLayoutTypeTable_resource,	(  TCHAR  *  )CONST_usLayoutTypeTable_resource,		},
	{	CONST_resId_ruleCmdTable,				(  TCHAR  *  )CONST_ruleCmdTable,					},
	{	CONST_resId_ruleCmdTable_autoAnswer,	(  TCHAR  *  )CONST_ruleCmdTable_autoAnswer,		},
	{   CONST_resId_ruleCmdTable_autoAnswer_av,	(  TCHAR  *  )CONST_ruleCmdTable_autoAnswer_av,		},		//  2016/02/15
	//
	{	CONST_resId_dynBmpTypeTable,			(  TCHAR  *  )CONST_dynBmpTypeTable_isCliHelp,			},

	//
	//  {	CONST_resId_menu_conferenceWall,				(  TCHAR  *  )CONST_menuTable_conferenceWall,		},
#if  0
	{	CONST_resId_menu_shareFullScreen,		(  TCHAR  *  )CONST_table_shareFullScreen,					},
	{	CONST_resId_menu_startShareMediaFile,	(  TCHAR  *  )CONST_table_startShareMediaFile,				},
	{	CONST_resId_menu_startShareMediaDevice,	(  TCHAR  *  )CONST_table_startShareMediaDevice,			},
#endif

	//
	{	CONST_resId_policyAvLevelTable_basic,				(  TCHAR  *  )CONST_policyAvLevelTable_basic,		},
	{	CONST_resId_policyAvLevelTable_standard,			(  TCHAR  *  )CONST_policyAvLevelTable_standard,	},
	{	CONST_resId_policyAvLevelTable_high,				(  TCHAR  *  )CONST_policyAvLevelTable_high,		},
	//  {	CONST_resId_policyAvLevelTable_screen_basic,		(  TCHAR  *  )CONST_policyAvLevelTable_screen_basic,		},
	{	CONST_resId_policyAvLevelTable_screen_basic,		(  TCHAR  *  )CONST_policyAvLevelTable_screen_standard,		},
	{	CONST_resId_policyAvLevelTable_screen_standard,		(  TCHAR  *  )CONST_policyAvLevelTable_screen_standard,		},
	{	CONST_resId_policyAvLevelTable_screen_high,			(  TCHAR  *  )CONST_policyAvLevelTable_screen_high,		},

	//
	{	CONST_resId_iTargetUsageTable,						(  TCHAR  *  )CONST_iTargetUsageTable,				},
	{	CONST_resId_iAvgBitrateTable_h264_720p,				(  TCHAR  *  )CONST_iAvgBitrateTable_h264_720p,				},	
	{	CONST_resId_iAvgBitrateTable_h264_1080p,			(  TCHAR  *  )CONST_iAvgBitrateTable_h264_1080p,				},	
	{	CONST_resId_iAvgBitrateTable_h265_720p,				(  TCHAR  *  )CONST_iAvgBitrateTable_h265_720p,				},	
	{	CONST_resId_iAvgBitrateTable_h265_1080p,			(  TCHAR  *  )CONST_iAvgBitrateTable_h265_1080p,				},	

	{	-1,		NULL,		},
};

  extern  QY_DMITEM		CONST_strTable_isCliHelp[];
  //
  extern  QY_DMITEM		CONST_dlgTable_isCliHelp[];
  //
  //  extern  QY_DMITEM		CONST_searchTable_isCliHelp[];
  
 QY_DMITEM  CONST_cusResTable_isCliHelp[]  =
{
 	{	CONST_resType_str,						(  TCHAR  *  )CONST_strTable_isCliHelp,						},
	{	CONST_resType_table,					(  TCHAR  *  )CONST_tableTable_misClientHelp,			},
	{	CONST_resType_dlg,						(  TCHAR  *  )CONST_dlgTable_isCliHelp,						},
 	{	CONST_resType_menu,						(  TCHAR  *  )CONST_cusMenusTable_misClientHelp,				},
	  {	CONST_resType_query,					(  TCHAR  *  )CONST_queryTable_mis,						},
	  {	CONST_resType_search,					(  TCHAR  *  )CONST_searchTable_isCliHelp,						},
	  {	CONST_resType_columnInfo,				(  TCHAR  *  )CONST_columnInfoTable,				},
	{	-1,		NULL,		},
};



