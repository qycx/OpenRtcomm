

#include	"stdafx.h"
#include	<tchar.h>
//  #include	"qyCommon.h"
#include	"myresource_main.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"
#include	"isCmdConst.h"

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_is.h"


 QY_DMITEM  CONST_menuTable_lianXiRenGuanLi_misMgr[]  =
{
	{	ID_qyMessengerView,						},
	{	-2,										},
	{	ID_qyNewMessenger,						},
	{	-2,										},
	{	ID_qyMessengerAuthList,					},
	//  {	ID_qyMessengerAuthList_needAudited,	},		//  2007/09/10, ½«´ËÏîÔÝÊ±¹Øµô¡£ÒÔºóÓ¦´ò¿ª£¬ÒÔ¿ÉÒÔÊÖ¹¤ÉóºË
	{	-2,										},
	{	ID_qyImAmList,							},
	{	-2,										},
#ifdef  __SUPPORT_sm__
	{	ID_qyPhoneMessengerList,				},
	{	-2,										},
#endif
	{	ID_qyMessengerList,						},
	{	-2,										},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_yongHuGuanLi,				(  TCHAR  *  )CONST_menuTable_yongHuGuanLi_netMc2,	},
	{	-1,		},
 };

 QY_DMITEM  CONST_menuTable_fenZuGuanLi_misMgr[]  =
{
	{	ID_qyNewImGrp,				},
	{	-2,							},
	{	ID_qyImGrpAuthList,			},
	{	ID_qyImGrpList,				},
	{	-2,			},
	{	ID_qyImGrpAuthMemList,		},
	{	ID_qyImGrpMemList,			},
	{	-1,		},
};

#ifdef  __SUPPORT_customerService__
 QY_DMITEM  CONST_menuTable_customerService_isMgr[]  =
{
	{		ID_customerServiceList,	},
	{		-1,				},
};
#endif

#ifdef  __SUPPORT_wwwQm__
  QY_DMITEM  CONST_menuTable_wwwQm_misMgr[]  =
{
	{		ID_wwwQmCfgList,		0,		0,	},
	{		-2,									},
	{		ID_ipKnowledgeList,					},
	{		-1,				},
};
#endif

 QY_DMITEM  CONST_ruleTypeTable_is[]  =
 {
	 {		CONST_ruleType_autoAnswer_av,						CONST_IDC_STATIC_autoAnswer_av,					},
	 {		CONST_ruleType_autoAnswer_screen,					CONST_IDC_STATIC_autoAnswer_screen,				},
	 {		CONST_ruleType_autoAnswer_mediaFile,				CONST_IDC_STATIC_autoAnswer_mediaFile,			},
	 //
	 {		CONST_ruleType_conferenceId_shareWebcam,			CONST_IDC_CHECK_shareWebcamInConference,		},
	 {		CONST_ruleType_ucbNoLocalVideoInThisConference,		CONST_IDC_CHECK_noLocalVideoInThisConference,	},			//  是否在这个会议中启动视频. 2011/10/22
	 {		CONST_ruleType_ucbDistinguishSharedWebcams,			CONST_IDC_CHECK_distinguishSharedWebcams,		},			//  是否区分被共享的摄像机，（是否使用序号）

	 {		-1,				},
 };

  QY_DMITEM  CONST_menuTable_sharedResources_misMgr[]  =
{
	{	ID_sharedDynBmpList,				},
	{	-2,									},
	{	ID_sharedDynBmpRuleList,			},
	{	-1,		},
};

 QY_DMITEM  CONST_menuTable_xiaoXiChaKan_misMgr[]  =
{
	{		ID_qyMsgList,		0,		0,	},
	{		-1,				},
};

 QY_DMITEM  CONST_menuTable_shiJianChaKan_misMgr[]  =
{
	{		ID_qyEventAll,		0,		0,	},
	{		-2,									},
	{		ID_qyOpEventAll,	0,		0,	},
	{		-1,				NULL,			},
};


#ifdef  __SUPPORT_sm__
 QY_DMITEM  CONST_menuTable_modulesGuanLi_isMgr[]  =
{
	{		ID_qyGsmModemList,	},
	{		ID_qySmContactList,	},
	{		-1,				},
};
#endif


 QY_DMITEM  CONST_menuTable_keHuDuanGuanLi_isMgr[]  =
{
	{		ID_qwmSvrList,	0,		0,	},		
	{		-2,							},
	{		ID_imObjRuleList,	0,	0	},
	{		-1,				NULL,			},
};


 QY_DMITEM  CONST_menuTable_guanLi_misMgr[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_lianXiRenGuanLi,				(  TCHAR  *  )CONST_menuTable_lianXiRenGuanLi_misMgr,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_fenZuGuanLi,					(  TCHAR  *  )CONST_menuTable_fenZuGuanLi_misMgr,	},
#ifdef  __SUPPORT_customerService__
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_customerService,				(  TCHAR  *  )CONST_menuTable_customerService_isMgr,	},
#endif
#ifdef  __SUPPORT_wwwQm__
	{	-3,		(  TCHAR  *  )CONST_resId_menu_wwwQm,						(  TCHAR  *  )CONST_menuTable_wwwQm_misMgr,		},
#endif
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_sharedResources,				(  TCHAR  *  )CONST_menuTable_sharedResources_misMgr,			},
	{	-2,		},
	{	ID_mcuList,	},
	{	-2,		},
#ifdef  __SUPPORT_sm__
	{	-3,		(  TCHAR  *  )CONST_resId_menu_modulesGuanLi_isMgr,			(  TCHAR  *  )CONST_menuTable_modulesGuanLi_isMgr,	},
	{	-2,		},
#endif
	{	-3,		(  TCHAR  *  )CONST_resId_menu_keHuDuanGuanLi,				(  TCHAR  *  )CONST_menuTable_keHuDuanGuanLi_isMgr,	},
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_xiaoXiChaKan,				(  TCHAR  *  )CONST_menuTable_xiaoXiChaKan_misMgr,		},
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_shiJianChaKan,				(  TCHAR  *  )CONST_menuTable_shiJianChaKan_misMgr,	},	
	{	-1,		NULL,			},

};

#if  0
 QY_DMITEM  CONST_menuTable_guanLi_misMgr_mini[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_lianXiRenGuanLi,				(  TCHAR  *  )CONST_menuTable_lianXiRenGuanLi_misMgr,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_fenZuGuanLi,					(  TCHAR  *  )CONST_menuTable_fenZuGuanLi_misMgr,	},
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_keHuDuanGuanLi,				(  TCHAR  *  )CONST_menuTable_keHuDuanGuanLi_isMgr,	},
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_xiaoXiChaKan,				(  TCHAR  *  )CONST_menuTable_xiaoXiChaKan_misMgr,		},
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_shiJianChaKan,				(  TCHAR  *  )CONST_menuTable_shiJianChaKan_misMgr,	},	
	{	-1,		NULL,			},

};
#endif


 QY_DMITEM	CONST_menuTable_peiZhi_misMgr[]  =
{
	{	ID_cfgSystemParams,			},
	{	-2,							},
	{	ID_cfgRasOptions,				},
#ifdef  __SUPPORT_customerService__
	{	-2,								},
	{	ID_cfgImAuthCond,				},
#endif
 	{	-2,								},
	{	ID_qyCfgCustom,					},
	{	ID_qyCfgStandardNames,			},
	{	-2,								},
	{	ID_cfgOptions					},
	{	ID_cfgAdvancedOptions			},
	{	-2,								},
	{	ID_CFGUSR						},
#ifdef  _DEBUG
	{	-2,								},
	{	ID_test_createUsr,				},
#endif
	{	-1,		NULL,		},
};

  QY_DMITEM  CONST_menuTable_whatToShow_isMgr[]  =
{
	{		ID_showPktInOn,					0,		0,	},
	{		ID_showPktInOff,				0,		0,	},
	{	-2,												},
	{		ID_showPktOutOn,				0,		0,	},
	{		ID_showPktOutOff,				0,		0,	},
	{	-2,												},
	{		ID_showProcBtOn,				0,		0,	},
	{		ID_showProcBtOff,				0,		0,	},
	{	-2,												},
	{		ID_showPSelfOn,					0,		0,	},
	{		ID_showPSelfOff,				0,		0,	},
	{	-2,												},
	{		ID_showNoCorrespondingOn,		0,		0,	},
	{		ID_showNoCorrespondingOff,		0,		0,	},
	{	-2,												},
	{		ID_showPostMsg2OutputQ_msgrOn,	0,		0,	},
	{		ID_showPostMsg2OutputQ_msgrOff,	0,		0,	},
	{	-2,												},
	{		ID_showBigElapseOn,				0,		0,	},
	{		ID_showBigElapseOff,			0,		0,	},
	{	-2,												},
	{		ID_showSwitchRouteQOn,			0,		0,	},
	{		ID_showSwitchRouteQOff,			0,		0,	},
	//
	{	-1,												},
};


 QY_DMITEM  CONST_menuTable_chaKan_isMgr[]  =
{
	{	ID_VIEW_TOOLBAR,		},		//  MENUITEM "¹¤¾ßÀ¸(&T)",                  
	{	ID_VIEW_STATUS_BAR,		},		//  MENUITEM "×´Ì¬À¸(&S)",                  
	{	-2,						},		//  MENUITEM SEPARATOR
#ifndef  __WINCE__
	{	ID_viewQnmStatus,		},		//  MENUITEM "ÏµÍ³×´Ì¬´°(&Z)",   
	{	-3,		(  TCHAR  *  )ID_whatToShow,				(  TCHAR  *  )CONST_menuTable_whatToShow_isMgr,	},
	{	-2,						},
	{	ID_viewDaemonStatus0,	},
	{	ID_viewDaemonStatus1,	},
	{	ID_viewDaemonStatus2,	},
#endif
	{	-2,						},		//  MENUITEM SEPARATOR
	{	ID_qyRefresh,			},		//  MENUITEM "Ë¢ÐÂ(&R)  F5",                
	{	-1,		NULL,			},
};


 QY_DMITEM  CONST_mainMenuTable_misMgr[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_wenJian,		(  TCHAR  *  )CONST_menuTable_wenJian,			},	//  2006/12/17
	{	-3,		(  TCHAR  *  )CONST_resId_menu_guanLi,		(  TCHAR  *  )CONST_menuTable_guanLi_misMgr,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,		(  TCHAR  *  )CONST_menuTable_peiZhi_misMgr,	},	
	{	ID_qyMakeClients,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chaKan,		(  TCHAR  *  )CONST_menuTable_chaKan_isMgr,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_bangZhu,		(  TCHAR  *  )CONST_menuTable_bangZhu,	},	
	{	-1,		NULL,			},
 };

#if  0
 QY_DMITEM  CONST_mainMenuTable_misMgr_mini[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_wenJian,		(  TCHAR  *  )CONST_menuTable_wenJian,			},	//  2006/12/17
	{	-3,		(  TCHAR  *  )CONST_resId_menu_guanLi,		(  TCHAR  *  )CONST_menuTable_guanLi_misMgr_mini,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,		(  TCHAR  *  )CONST_menuTable_peiZhi_misMgr,	},	
	{	ID_qyMakeClients,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chaKan,		(  TCHAR  *  )CONST_menuTable_chaKan_isMgr,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_bangZhu,		(  TCHAR  *  )CONST_menuTable_bangZhu,	},	
	{	-1,		NULL,			},
 };
#endif
 
 QY_DMITEM  CONST_childFrmMenuTable_misMgr[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_wenJian,		(  TCHAR  *  )CONST_menuTable_wenJian,			},	//  2006/12/17
	{	-3,		(  TCHAR  *  )CONST_resId_menu_guanLi,		(  TCHAR  *  )CONST_menuTable_guanLi_misMgr,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,		(  TCHAR  *  )CONST_menuTable_peiZhi_misMgr,	},	
	{	ID_qyMakeClients,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chaKan,		(  TCHAR  *  )CONST_menuTable_chaKan_isMgr,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chuangKou,	(  TCHAR  *  )CONST_menuTable_chuangKou,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_bangZhu,		(  TCHAR  *  )CONST_menuTable_bangZhu,	},	
	{	-1,		NULL,		},
};



 QY_DMITEM  CONST_cusMenusTable_misMgr[]  =
{
	{	CONST_resId_mainMenu,				(  TCHAR  *  )CONST_mainMenuTable_misMgr,			},
	//{	CONST_resId_mainMenu_mini,			(  TCHAR  *  )CONST_mainMenuTable_misMgr_mini,		},
	{	CONST_resId_childFrmMenu,			(  TCHAR  *  )CONST_childFrmMenuTable_misMgr,		},
	{	CONST_resId_popupMenu,				(  TCHAR  *  )CONST_popupMenuTable_mis,					},
	{	-1,		NULL,		},
};


 QY_DMITEM  CONST_queryTypeTable_isMgr[]  =
{
	{	CONST_qyQueryType_imMsgList,				CONST_str_imMsgChaXun,		},
	{	CONST_qyQueryType_opEventList,				CONST_str_xiTongShiJianChaXun,			},		//  2006/02/25
	{	-1,											NULL,					},

};


  QY_DMITEM  CONST_tableTable_misMgr[]  =
{
	{ 	CONST_resId_qnmEventTypeTable0,			(  TCHAR  *  )CONST_qnmEventTypeTable0_is,		},
	{	CONST_resId_qnmEventTypeTable_pc,		(  TCHAR  *  )CONST_qnmEventTypeTable_misMgr,		},
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
	{	CONST_resId_imGrpMemRoleTable,			(  TCHAR  *  )CONST_imGrpMemRoleTable,				},
	//
	{	CONST_resId_imObjRoleTable,				(  TCHAR  *  )CONST_imObjRoleTable,				},
	
	//
	{	CONST_resId_queryTypeTable,				(  TCHAR  *  )CONST_queryTypeTable_isMgr,		},

	{	CONST_resId_fieldIdTable,				(  TCHAR  *  )CONST_fieldIdTable,					},
	//  2009/01/01
	{	CONST_resId_qyCommTypeTable,			(  TCHAR  *  )CONST_qyCommTypeTable,				},
	{	CONST_resId_pcCommTypeTable,			(  TCHAR  *  )CONST_pcCommTypeTable,				},
	{	CONST_resId_grpNameTable,				(  TCHAR  *  )CONST_grpNameTable,					},
	{	CONST_resId_usRunningStatusTable,		(  TCHAR  *  )CONST_usRunningStatusTable,			},
	//
	{	CONST_resId_ruleTypeTable,				(  TCHAR  *  )CONST_ruleTypeTable_is,				},
	{	CONST_resId_ruleCmdTable,				(  TCHAR  *  )CONST_ruleCmdTable,					},

	{	-1,		NULL,		},
};


 QY_DMITEM  CONST_cusResTable_isMgr[]  =
{
 	{	CONST_resType_str,						(  TCHAR  *  )CONST_strTable_isMgr,						},
	{	CONST_resType_table,					(  TCHAR  *  )CONST_tableTable_misMgr,			},
	{	CONST_resType_dlg,						(  TCHAR  *  )CONST_dlgTable,						},
 	{	CONST_resType_menu,						(  TCHAR  *  )CONST_cusMenusTable_misMgr,				},
	{	CONST_resType_query,					(  TCHAR  *  )CONST_queryTable_mis,						},
	{	CONST_resType_search,					(  TCHAR  *  )CONST_searchTable,						},
	{	CONST_resType_columnInfo,				(  TCHAR  *  )CONST_columnInfoTable,				},
	{	-1,		NULL,		},
};



