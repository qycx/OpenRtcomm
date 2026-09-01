
#include	"stdafx.h"
#include	<tchar.h>
//  #include	"qyCommon.h"
#include	"myresource_main.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"isCmdConst.h"


 // -0
 QY_DMITEM  CONST_popupMenuTable_0[]  =
{
	{	ID_qyProperties,	},
	{	-1,		NULL,	},
};

 // -1
 QY_DMITEM  CONST_popupMenuTable_viewPcList[]  =
{
	{	ID_qyEdit,		(  TCHAR  *  )CONST_resId_yongHuXinXiBianJiShenHe,        },
	{	ID_qyCfgStandardName,	},											//  20060904
	//  {	-2,		},
	//  {	ID_qySendMsg,	(  TCHAR  *  )CONST_str_qySendMsg,                },
	{	-2,		},
	{	ID_qyDel,	},
	{	-2,		},
	{	ID_qyProperties,	},
	{	-1,		NULL,	},
 };

 // -2
 QY_DMITEM  CONST_popupMenuTable_viewPcUsrList_netMc2[]  =		//  8
{
	{	ID_qyEdit,	(  TCHAR  *  )CONST_resId_yongHuXinXiBianJiShenHe,	},	//  "用户信息编辑审核(&B)",        
	{	ID_qyCfgStandardName,	},
	{	-2,		},
	{	ID_qyDelPcUsr,	},
	{	-2,		},   
	{	ID_qyProperties,	},  
	{	-1,		NULL,	},
};

 // -3
 QY_DMITEM  CONST_popupMenuTable_viewPcRuleList[]  =		//  8
{
	{	ID_qyCfgPcRule,		},	//  "配置单机管理策略(&D)",        
	{	-2,		},
	{	ID_qyDelPcRule,	}, 
	{	-1,		NULL,	},
};

 // -4
 QY_DMITEM	CONST_popupMenuTable_viewVlanMgrList[]		=
{
	{	ID_qyRefreshVlanPolicy,	},
	{	-2,		},
	{	ID_qyCfgProxyRule,	},
	{	-2,		},
	{	ID_qyDelProxy,	},
	{	-1,		NULL,	},
};

 // -5
 QY_DMITEM	CONST_popupMenuTable_viewUnchkedPcList[]	=
{
	{	ID_qyStopUnchk,	},
	{	-1,		NULL,	},
};

 // -6
 QY_DMITEM	CONST_popupMenuTable_viewWillAttackPcList[]	=
{
	{	ID_qyStopWillAttack,	},
	{	-1,		NULL,	},
};

 // -7
 QY_DMITEM	CONST_popupMenuTable_viewPcUsrInTab1List[]	=
{
	{	ID_qyEditPcUsrInTab1,	(  TCHAR  *  )CONST_resId_qyEdit1,	},
	{	-2,						},
	{	ID_qyDelPcUsrInTab1,	(  TCHAR  *  )ID_qyDel,				},
	{	-1,		NULL,	},
};


 /*
 //  -8.1
 QY_DMITEM  CONST_menuTable_anQuanGuanLi[]  =
{
	{	ID_qyCfgPcRule,				},	//  "配置单机管理策略(&D)",        
	{	-1,		NULL,		},
};
*/

 // -8.2
 QY_DMITEM  CONST_menuTable_yuanChengZhuoMianGuanLi[]  =
{
	{	ID_viewRemoteDesktop,			},
	{	ID_cancelRemoteDesktop,			},
	{	-2,								},
	{	ID_queryNetworkProp,			},			//				"显示网络连接(&W)",            
	{	ID_queryProxyCfg,				},			//              "显示代理服务器配置(&D)",      
	//  {	ID_queryComputerInfo,			},			//				"显示计算机信息配置(&J)",      
	{	-2,								},
	{	ID_qyPcSpList,																		},		//			"补丁列表(&B)",                
	{	ID_queryPcWindowsUpdatePolicyProp,	},		//				"显示补丁分发配置
	{	-2,		},
	{	ID_pcProcessPropList,			},			//             "进程列表(&J)",                
	{	ID_pcProcessModulePropList,	},
	{	-2,			},
	{	ID_pcNetFlowPropList_ethernet,			},
	{	ID_pcNetFlowPropList,			},
	{	-2,			},
	{	ID_pcNetSharePropList,			},
	{	-1,		NULL,	},
};
  
 // -8.3
 QY_DMITEM  CONST_menuTable_jianKongYuShenJi[]  =
{
	{	ID_monDesktop,																		},
	{	ID_cancelMonDesktop,																},
	{	-2,																					},
	{	ID_doSecChk,				(  TCHAR  *  )CONST_resId_monIe,						},
	{	ID_undoSecChk,																		},
	{	-2,																					},
	{	ID_pcSecChkEventList,		(  TCHAR  *  )CONST_resId_pcSecChkEventList_netMc2,		},
	{	-2,																					},
	{	ID_pcRegistryList,																	},
	{	ID_pcRegistryRuleStatusList,														},
	{	-2,																					},
	{	ID_pcEventLogList,																	},			//			"系统日志列表(&T)",            
	{	ID_pcOsUsrList,																		},			//			"操作系统用户列表(&Z)",        
	{	ID_qyPcNetStatList,																	},			//			"NetStat列表(&L)",             
	{	ID_pcPrinterPropList,																},			//			"打印机列表(&Y)",              
	{	-1,		NULL,	},
};

 // -8
 QY_DMITEM  CONST_popupMenuTable_viewPcList_netMc2[]  =		//  8
{
	{	-3,			(  TCHAR  *  )CONST_resId_jianKongYuShenJi,			(  TCHAR  *  )CONST_menuTable_jianKongYuShenJi,			},	// 监控与审计(&J)
	//  {	-3,			(  TCHAR  *  )CONST_resId_anQuanGuanLi,				(  TCHAR  *  )CONST_menuTable_anQuanGuanLi,				},	
	{	ID_qyCfgPcRule,				},	//  "配置单机管理策略(&D)",        
	{	-3,			(  TCHAR  *  )CONST_resId_yuanChengZhuoMianGuanLi,	(  TCHAR  *  )CONST_menuTable_yuanChengZhuoMianGuanLi,	},
	{	-2,			},
	{	ID_qyEdit,	(  TCHAR  *  )CONST_resId_yongHuXinXiBianJiShenHe,	},	//  "用户信息编辑审核(&B)",        
	{	ID_qyCfgStandardName,	},
	{	-2,		},
	{	ID_qyDel,	},
	{	-2,		},
	//  {	ID_qySendMsg,	},	//  "发送消息(&F)",                
	{	ID_qyProperties,	},  
	{	-1,		NULL,	},
};

 // -9
 QY_DMITEM	CONST_popupMenuTable_tree_network[]	=
{
	{	ID_qyProperties_network,	},
	{	-1,		NULL,				},
};

 // -10
 QY_DMITEM	CONST_popupMenuTable_tree_switch[]	=
{
	{	ID_qyRefresh,	},
	{	-2,				},
	{	ID_qyEdit_switchInfo,	},
	{	ID_qyEdit_switchAndAllConns,	},
	{	ID_qyCancel_switchAndAllConns,	},
	{	ID_qyCancel_allConns,	},
	{	-2,						},
	{	ID_qyCfgSnmpObjRule,	},
	{	-2,						},
	{	ID_qyDel_switch,	},
	{	-2,						},
	{	ID_qyProperties_switch,	},
	{	-1,		NULL,				},
};

 // -11
 QY_DMITEM	CONST_popupMenuTable_tree_switchPort[]	=
{
	{	ID_qyWillAttack,	},
	{	ID_qyStopWillAttack	,	},
	{	-2,						},
	{	ID_beStaticAccessModeAndEnablePortSecurity,		},
	{	ID_disablePortSecurity,		},
	{	-2,						},
	{	ID_setCpsIfMaxSecureMacAddr,	},
	{	-2,						},
	{	ID_qyCfgSnmpObjPortRule,	},
	{	-2,						},
	{	ID_qyProperties_switchPort,	},
	{	-1,		NULL,				},
};

 // -12
 QY_DMITEM	CONST_popupMenuTable_rootList[]	=
{
	{	ID_qySearch_mac,	},
	{	ID_qySearchConnection	,	},
	{	-2,						},
	{	ID_qyEdit_portUsrInfo,		},
	{	ID_qyCancel_portUsrInfo,		},
	{	-2,						},
	{	ID_qyDel_connection,	},
	{	-2,						},
	{	ID_secureMac,	},
	{	ID_cancelSecureMac,			},
	{	-2,					},
	{	ID_qyProperties,	},
	{	-1,		NULL,				},
};

 // -13
 QY_DMITEM	CONST_popupMenuTable_viewPcList_secChk[]	=
{
	{	ID_doSecChk,														},
	{	ID_undoSecChk,														},
	{	-2,																	},
	{	ID_pcSecChkEventList,												},
	{	-2,																	},
	{	ID_qyCfgPcRule,														},
	{	-2,																	},
	{	ID_qyEdit,	(  TCHAR  *  )CONST_resId_yongHuXinXiBianJiShenHe,		},	//  "用户信息编辑审核(&B)",        
	{	ID_qyCfgStandardName,	},												//  20060904
	//  {	-2,																},
	//  {	ID_qySendMsg,														},
	{	-2,																	},
	{	ID_qyDel,															},
	{	-2,																	},
	{	ID_qyProperties,													},
	{	-1,		NULL,														},
};

 // -14
 QY_DMITEM	CONST_popupMenuTable_viewNetDevConn[]	=
{
	{	ID_qySearchSwitchPort,	},
	{	-2,						},
	{	ID_qyProperties,		},
	{	ID_qyProperties_viewNetDevConn,	},
	{	-1,		NULL,			},
};

 // -15
 QY_DMITEM	CONST_popupMenuTable_viewPcList_nms[]	=
{
	{	ID_qySearchConnection,	},
	{	-2,				},
	{	ID_qyEdit,		(  TCHAR  *  )CONST_resId_qyEdit1,		},
	{	ID_qyCfgStandardName,	},												//  20060904
	//  {	-2,				},
	//  {	ID_qySendMsg,	},
	{	-2,				},
	{	ID_qyDel,		},
	{	-2,				},
	{	ID_qyProperties,	},
	{	-1,		NULL,			},
};

 // -16
 QY_DMITEM	CONST_popupMenuTable_viewPcEventList_nms[]	=
{
	{	ID_qySearchConnection,	},
	{	-2,				},
	{	ID_qyProperties,		},
	{	-1,		NULL,			},
};

 // -17
 QY_DMITEM	CONST_popupMenuTable_viewNetDevEventList_nms[]	=
{
	{	ID_qySearchSwitchPort,	},
	{	-2,				},
	{	ID_qyProperties,		},
	{	ID_qyProperties_viewNetDevConn,		},
	{	-1,		NULL,			},
};

 // -18
 QY_DMITEM	CONST_popupMenuTable_viewSearchList_nms[]	=
{
	{	ID_qySearchSwitchPort,	},
	{	ID_qySearchConnection,	},
	{	-2,						},
	{	ID_qyProperties,		},
	{	-1,		NULL,			},
};

 // -19
 QY_DMITEM	CONST_popupMenuTable_viewPcSpList[]	=
{
	{	ID_qySearchPcSp,	},
	{	-2,				},
	{	ID_qyCusPcSp,	},
	{	-2,				},
	{	ID_qyDelPcSp,		},
	{	-2,				},
	{	ID_qyProperties,		},
	{	-1,		NULL,			},
};

 // -20
 QY_DMITEM	CONST_popupMenuTable_viewPcList_assetMgr[]	=
{
	{	ID_qyCfgPcRule,	},
	{	-2,				},
	{	ID_qyEdit,		(  TCHAR  *  )CONST_resId_qyEdit1,	},
	{	ID_qyCfgStandardName,	},											//  20060904
	//  {	-2,				},
	//  {	ID_qySendMsg,			},
	{	-2,				},
	{	ID_qyDel,				},
	{	-2,				},
	{	ID_qyProperties,		},
	{	-1,		NULL,			},
};

 // -21
 QY_DMITEM	CONST_popupMenuTable_pc[]	=
{
	{	ID_qyDel,				},
	{	-2,				},
	{	ID_qyProperties,		},
	{	-1,		NULL,			},
};

 // -22
 QY_DMITEM	CONST_popupMenuTable_viewAssets_os[]	=
{
	{	ID_qyDel,				},
	{	-1,		NULL,			},
};

 // -23
 QY_DMITEM	CONST_popupMenuTable_cfgSp_os[]	=
{
	{	ID_addServicePack,		},
	{	-1,		NULL,			},
};

 // -24
 QY_DMITEM	CONST_popupMenuTable_cfgSp_servicePack[]	=
{
	{	ID_addSp,	},
	{	ID_qyEdit,	},
	{	-2,				},
	{	ID_delServicePack,		},
	{	-2,				},
	{	ID_qyProperties,		},
	{	-1,		NULL,			},
};

 // -25
 QY_DMITEM	CONST_popupMenuTable_viewSp[]	=
{
	{	ID_qyEdit,	},
	{	-2,			},
	{	ID_qyDel,	},
	{	-2,				},
	{	ID_qyProperties,		},
	{	-1,		NULL,			},
};

 // -26
 QY_DMITEM	CONST_popupMenuTable_viewSnmpObjRuleList[]	=
{
	{	ID_qyCfgSnmpObjRule,	},
	{	-2,			},
	{	ID_qyDelSnmpObjRule,	},
	{	-1,		NULL,			},
};
 
 // -27
 QY_DMITEM	CONST_popupMenuTable_viewConflictConnList[]	=
{
	{	ID_qyCancelConnLock,	},
	{	-2,					},
	{	ID_qyDelConnLock,		},
	{	-2,						},
	{	ID_qyDelSwitchConnLock,	},
	{	-1,		NULL,			},
};

 // -28
 QY_DMITEM	CONST_popupMenuTable_viewPcNetworkProp[]	=
{
	{	ID_qyEdit_pcNetwork,	},
	{	-2,		},
	{	ID_qyDel_pcNetwork,		},
	{	-2,		},
	{	ID_qyProperties	,	(  TCHAR  *  )CONST_resId_qyProperties1,	},
	{	-2,		},
	{	ID_qyProp_pcNetwork	,	},
	{	-1,		NULL,	},
};

 // -29
 QY_DMITEM	CONST_popupMenuTable_view_auditSth[]	=
{
	{	ID_qyDel,	},
	{	-2,			},
	{	ID_qyProperties,	},
	{	-1,		NULL,			},
};

 // -30
 QY_DMITEM	CONST_popupMenuTable_viewPcProcess[]	=
{
	{	ID_qyProhibit,	},
	{	ID_qyProhibitAll,		},
	{	-2,			},
	{	ID_qyDel,		},
	{	-2,				},
	{	ID_addPcProcessPermitRule,		},
	{	ID_viewPcProcessRule,	},
	{	-2,				},
	{	ID_editPcModuleKnowlege,		},
	{	-2,				},
	{	ID_qyProp_pcModuleKnowlege,		},
	{	-2,				},
	{	ID_qyProperties,		},
	{	-1,	NULL,				},
};

 //  -31
 QY_DMITEM  CONST_popupMenuTable_cfgPcModuleKnowlege_notSelected[]  =
{
	{	ID_addModuleKnowlege,				},
	{	-2,									},
	{	ID_importModuleKnowlege,			},
	{	ID_exportModuleKnowlege,			},
	{	ID_clearupModuleKnowlege,			},
	{	-1,				},
};

 //  -32
 QY_DMITEM  CONST_popupMenuTable_cfgPcModuleKnowlege[]  =
{
	{	ID_editModuleKnowlege,		(  TCHAR  *  )ID_qyEdit,		},
	{	-2,		},
	{	ID_delModuleKnowlege,		(  TCHAR  *  )ID_qyDel,		},
	{	-2,		},
	{	ID_qyProp_pcModuleKnowlege,	(  TCHAR  *  )ID_qyProperties,				},
	{	-1,				},
};


 QY_DMITEM  CONST_popupMenuTable_viewPcRegistry[]  =
{
	{	ID_qyDel,		},
	{	-2,				},
	{	ID_editPcModuleKnowlege,		(  TCHAR  *  )CONST_resId_editPcRegistryKnowledge,			},
	{	-2,																							},
	{	ID_qyProp_pcModuleKnowlege,		(  TCHAR  *  )CONST_resId_prop_pcRegistryKnowledge,			},															
	{	-2,								},
	{	ID_qyProperties,			},
	{	-1,				},
};


 QY_DMITEM  CONST_popupMenuTable_viewPcList_multiSel[]  =
{
	{	ID_qyDel,		},
	{	-1,				},
};

  QY_DMITEM  CONST_popupMenuTable_viewProcedObj_load[]  =	//  通用的装载之前的数据源菜单，2007/09/16
{
	{	ID_loadProcedObj,	},					
	//  {	ID_unloadProcedObj,	},
	{	-1,				},
};


 QY_DMITEM  CONST_popupMenuTable_viewProcedObj_bhb[]  =
{
	//  {	ID_loadProcedObj,	},							//  因为BHB不再深入开发，所以不再显示菜单项
	//  {	ID_unloadProcedObj,	},
	{	-1,				},
};


  QY_DMITEM  CONST_popupMenuTable_viewProcedObj_netMc2[]  =
{
	{	ID_loadProcedObj,	},
	//  {	ID_unloadProcedObj,	},
	{	-2,				},
	{	-3,								(  TCHAR  *  )CONST_resId_menu_guanLi,		(  TCHAR  *  )CONST_menuTable_guanLi_netMc2,	},
	{	-1,				},
};

 QY_DMITEM  CONST_popupMenuTable_viewProcedObj_nms[]  =
{
	{	ID_loadProcedObj,	},
	//  {	ID_unloadProcedObj,	},
	{	-2,				},
	{	-3,								(  TCHAR  *  )CONST_resId_menu_guanLi,		(  TCHAR  *  )CONST_menuTable_guanLi_nms,	},
	{	-1,				},
};

 QY_DMITEM  CONST_popupMenuTable_viewProcedObj_secChk[]  =
{
	{	ID_loadProcedObj,	},
	//  {	ID_unloadProcedObj,	},
	{	-2,				},
	{	-3,								(  TCHAR  *  )CONST_resId_menu_guanLi,		(  TCHAR  *  )CONST_menuTable_guanLi_secChk,	},
	{	-1,				},
};

 QY_DMITEM  CONST_popupMenuTable_viewProcedObj_assetMgr[]  =
{
	{	ID_loadProcedObj,	},
	//  {	ID_unloadProcedObj,	},
	{	-2,				},
	{	-3,								(  TCHAR  *  )CONST_resId_menu_guanLi,		(  TCHAR  *  )CONST_menuTable_guanLi_assetMgr,	},
	{	-1,				},
};

 QY_DMITEM  CONST_popupMenuTable_viewProcedObj_misClient[]  =
{
	{	ID_loadProcedObj,	},
	//  {	ID_unloadProcedObj,	},
	{	-2,				},
	{	-3,								(  TCHAR  *  )CONST_resId_menu_guanLi,		(  TCHAR  *  )CONST_menuTable_guanLi_misClient,	},
	{	-1,				},
};

 QY_DMITEM  CONST_popupMenuTable_viewProcedObj_misMgr[]  =
{
	{	ID_loadProcedObj,	},
	//  {	ID_unloadProcedObj,	},
	{	-2,				},
	{	-3,								(  TCHAR  *  )CONST_resId_menu_guanLi,		(  TCHAR  *  )CONST_menuTable_guanLi_misMgr,	},
	{	-1,				},
};


 extern  QY_DMITEM  CONST_popupMenuTable_viewMessengerAuthList_isMgr[];
 extern  QY_DMITEM  CONST_popupMenuTable_viewMessengerAuthList_multiSel_isMgr[];
 //  extern  QY_DMITEM  CONST_popupMenuTable_viewMessengerAuthList_isMgr_mini[];
 //  extern  QY_DMITEM  CONST_popupMenuTable_viewMessengerList_isMgr[];
 //  extern  QY_DMITEM  CONST_popupMenuTable_viewMessengerList_multiSel_isMgr[];
 extern  QY_DMITEM  CONST_popupMenuTable_viewMessengerList_multiSel_isClient[];
  //
 extern  QY_DMITEM  CONST_popupMenuTable_viewMessengerNeedAuditedList_isMgr[];
 //
 extern  QY_DMITEM  CONST_popupMenuTable_imAmList_isMgr[];
 //
 extern  QY_DMITEM  CONST_popupMenuTable_viewPhoneMessengerList_isMgr[];
 extern  QY_DMITEM  CONST_popupMenuTable_viewPhoneMessengerList_multiSel_isMgr[];
 extern  QY_DMITEM  CONST_popupMenuTable_viewPhoneMessengerList_notSel_isMgr[];
 //
 extern  QY_DMITEM  CONST_popupMenuTable_mcuList[];
 extern  QY_DMITEM  CONST_popupMenuTable_mcu[];


 //

 extern  QY_DMITEM  CONST_popupMenuTable_viewImGrpList_isMgr[];
 //
 extern  QY_DMITEM  CONST_popupMenuTable_viewImGrpMemList_isMgr[];
 extern  QY_DMITEM  CONST_popupMenuTable_viewImGrpMemList_multiSel_isMgr[];

 //
 extern  QY_DMITEM  CONST_popupMenuTable_customerServiceList_isMgr[];
 extern  QY_DMITEM  CONST_popupMenuTable_wwwQmCfgList_isMgr[];
 extern  QY_DMITEM  CONST_popupMenuTable_phoneGuestList[];
 extern  QY_DMITEM  CONST_popupMenuTable_phoneGuestList_multiSel[];

 extern  QY_DMITEM  CONST_popupMenuTable_gsmModemList[];
 extern  QY_DMITEM  CONST_popupMenuTable_sharedDynBmpList_isMgr[];
 extern  QY_DMITEM  CONST_popupMenuTable_sharedDynBmpList_multiSel_isMgr[];
 
 extern  QY_DMITEM  CONST_popupMenuTable_sharedDynBmpRuleList_isMgr[];
 //
 extern  QY_DMITEM  CONST_popupMenuTable_viewImTaskList_isMgr[];
 //
 extern  QY_DMITEM  CONST_popupMenuTable_commonList_notSel[];
 extern  QY_DMITEM  CONST_popupMenuTable_commonList[];

 //
 extern  QY_DMITEM  CONST_menuTable_dlgTalk_messenger[];
 extern  QY_DMITEM  CONST_menuTable_dlgTalk_imGrp[];
 extern  QY_DMITEM  CONST_menuTable_dlgVideos[];
 extern  QY_DMITEM  CONST_menuTable_dlgSharedWebcams[];
 extern  QY_DMITEM  CONST_menuTable_dlgVWall[];
 extern  QY_DMITEM  CONST_menuTable_dlgRemoteAssist[];

 //
 extern  QY_DMITEM  CONST_popupMenuTable_messenger_isMgr[];
 extern  QY_DMITEM  CONST_popupMenuTable_imGrp_isMgr[];

 //
 

 QY_DMITEM  CONST_popupMenuTable_netMc[]  =
{
	{	CONST_resId_popup0,													0,		(  TCHAR  *  )CONST_popupMenuTable_0,			},									//  -0
	{	CONST_resId_popup_viewPcList,										0,		(  TCHAR  *  )CONST_popupMenuTable_viewPcList,	},									//  -1
	{	CONST_resId_popup_viewPcUsrList,									0,		(  TCHAR  *  )CONST_popupMenuTable_viewPcUsrList_netMc2,	},					//  -2
	{	CONST_resId_popup_viewPcRuleList,									0,		(  TCHAR  *  )CONST_popupMenuTable_viewPcRuleList,	},						//  -3
	{	CONST_resId_popup_viewVlanMgrList,									0,		(  TCHAR  *  )CONST_popupMenuTable_viewVlanMgrList,	},						//  -4
	{	CONST_resId_popup_viewUnchkedPcList,								0,		(  TCHAR  *  )CONST_popupMenuTable_viewUnchkedPcList,	},				//  -5
	{	CONST_resId_popup_viewWillAttackPcList,								0,		(  TCHAR  *  )CONST_popupMenuTable_viewWillAttackPcList,	},			//  -6
	{	CONST_resId_popup_viewPcUsrInTab1List,								0,		(  TCHAR  *  )CONST_popupMenuTable_viewPcUsrInTab1List,	},		//	-7
	{	CONST_resId_popup_viewPcList_netMc2,								0,		(  TCHAR  *  )CONST_popupMenuTable_viewPcList_netMc2,	},						//  -8
	 
	{	CONST_resId_popup_tree_network,										0,		(  TCHAR  *  )CONST_popupMenuTable_tree_network,	},							//  -9
	{	CONST_resId_popup_tree_switch,										0,		(  TCHAR  *  )CONST_popupMenuTable_tree_switch,	},								//  -10
	{	CONST_resId_popup_tree_switchPort,									0,		(  TCHAR  *  )CONST_popupMenuTable_tree_switchPort,	},							//  -11
	{	CONST_resId_popup_rootList,											0,		(  TCHAR  *  )CONST_popupMenuTable_rootList,	},									//  -12
	{	CONST_resId_popup_viewPcList_secChk,								0,		(  TCHAR  *  )CONST_popupMenuTable_viewPcList_secChk,	},					//  -13
	{	CONST_resId_popup_viewNetDevConn,									0,		(  TCHAR  *  )CONST_popupMenuTable_viewNetDevConn,	},						//  -14
	{	CONST_resId_popup_viewPcList_nms,									0,		(  TCHAR  *  )CONST_popupMenuTable_viewPcList_nms,	},						//  -15
	{	CONST_resId_popup_viewPcEventList_nms,								0,		(  TCHAR  *  )CONST_popupMenuTable_viewPcEventList_nms,	},					//  -16
	{	CONST_resId_popup_viewNetDevEventList_nms,							0,		(  TCHAR  *  )CONST_popupMenuTable_viewNetDevEventList_nms,	},				//  -17
	{	CONST_resId_popup_viewSearchList_nms,								0,		(  TCHAR  *  )CONST_popupMenuTable_viewSearchList_nms,	},					//  -18
	{	CONST_resId_popup_viewPcSpList,										0,		(  TCHAR  *  )CONST_popupMenuTable_viewPcSpList,	},						//  -19
	{	CONST_resId_popup_viewPcList_assetMgr,								0,		(  TCHAR  *  )CONST_popupMenuTable_viewPcList_assetMgr,	},					//  -20
	{	CONST_resId_popup_pc,												0,		(  TCHAR  *  )CONST_popupMenuTable_pc,	},						//  -21
	{	CONST_resId_popup_viewAssets_os,									0,		(  TCHAR  *  )CONST_popupMenuTable_viewAssets_os,	},						//  -22
	{	CONST_resId_popup_cfgSp_os,											0,		(  TCHAR  *  )CONST_popupMenuTable_cfgSp_os,	},							//  -23
	{	CONST_resId_popup_cfgSp_servicePack,								0,		(  TCHAR  *  )CONST_popupMenuTable_cfgSp_servicePack,	},					//  -24
	{	CONST_resId_popup_viewSp,											0,		(  TCHAR  *  )CONST_popupMenuTable_viewSp,	},								//  -25
	{	CONST_resId_popup_viewSnmpObjRuleList,								0,		(  TCHAR  *  )CONST_popupMenuTable_viewSnmpObjRuleList,	},					//  -26
	{	CONST_resId_popup_viewConflictConnList,								0,		(  TCHAR  *  )CONST_popupMenuTable_viewConflictConnList,	},				//  -27	
	{	CONST_resId_popup_viewPcNetworkProp,								0,		(  TCHAR  *  )CONST_popupMenuTable_viewPcNetworkProp,	},					//  -28
	{	CONST_resId_popup_view_auditSth,									0,		(  TCHAR  *  )CONST_popupMenuTable_view_auditSth,	},						//  -29
	{	CONST_resId_popup_viewPcProcess,									0,		(  TCHAR  *  )CONST_popupMenuTable_viewPcProcess,	},						//  -30
	{	CONST_resId_popup_cfgPcModuleKnowlege_notSel,						0,		(  TCHAR  *  )CONST_popupMenuTable_cfgPcModuleKnowlege_notSelected,		},
	{	CONST_resId_popup_cfgPcModuleKnowlege,								0,		(  TCHAR  *  )CONST_popupMenuTable_cfgPcModuleKnowlege,					},
	{	CONST_resId_popup_viewPcRegistry,									0,		(  TCHAR  *  )CONST_popupMenuTable_viewPcRegistry,						},
	{	CONST_resId_popup_viewPcList_multiSel,								0,		(  TCHAR  *  )CONST_popupMenuTable_viewPcList_multiSel,					},
	//
	//
	//
	//  2007/05/17
	{	CONST_resId_popup_viewMessengerAuthList_isMgr,						0,		(  TCHAR  *  )CONST_popupMenuTable_viewMessengerAuthList_isMgr,				},
	{	CONST_resId_popup_viewMessengerAuthList_multiSel_isMgr,				0,		(  TCHAR  *  )CONST_popupMenuTable_viewMessengerAuthList_multiSel_isMgr,				},
	//  {   CONST_resId_popup_viewMessengerAuthList_isMgr_mini,					0,		(  TCHAR  *  )CONST_popupMenuTable_viewMessengerAuthList_isMgr_mini,			},
	{   CONST_resId_popup_viewMessengerAuthList_isMgr_mini,					0,		(  TCHAR  *  )CONST_popupMenuTable_viewMessengerAuthList_isMgr,			},
	{	CONST_resId_popup_viewMessengerList_isMgr,							0,		(  TCHAR  *  )CONST_popupMenuTable_viewMessengerAuthList_isMgr,					},	//  101
	{	CONST_resId_popup_viewMessengerList_multiSel_isMgr,					0,		(  TCHAR  *  )CONST_popupMenuTable_viewMessengerAuthList_multiSel_isMgr,			},	//  101
	//
	{	CONST_resId_popup_viewMessengerNeedAuditedList_isMgr,				0,		(  TCHAR  *  )CONST_popupMenuTable_viewMessengerNeedAuditedList_isMgr,			},
	//
	{	CONST_resId_popup_imAmList_isMgr,									0,		(  TCHAR  *  )CONST_popupMenuTable_imAmList_isMgr,								},
	//
	{	CONST_resId_popup_viewPhoneMessengerList_isMgr,						0,		(  TCHAR  *  )CONST_popupMenuTable_viewPhoneMessengerList_isMgr,			},
	{	CONST_resId_popup_viewPhoneMessengerList_multiSel_isMgr,			0,		(  TCHAR  *  )CONST_popupMenuTable_viewPhoneMessengerList_multiSel_isMgr,	},
	{	CONST_resId_popup_viewPhoneMessengerList_notSel_isMgr,				0,		(  TCHAR  *  )CONST_popupMenuTable_viewPhoneMessengerList_notSel_isMgr,		},		
	//
	{	CONST_resId_popup_mcuList,											0,		(  TCHAR  *  )CONST_popupMenuTable_mcuList,	},
	{	CONST_resId_popup_mcu,												0,		(  TCHAR  *  )CONST_popupMenuTable_mcu,	},


	//
	{	CONST_resId_popup_viewImGrpList_isMgr,								0,		(  TCHAR  *  )CONST_popupMenuTable_viewImGrpList_isMgr,						},
	
	{	CONST_resId_popup_viewImGrpMemList_isMgr,							0,		(  TCHAR  *  )CONST_popupMenuTable_viewImGrpMemList_isMgr,					},
	{	CONST_resId_popup_viewImGrpMemList_multiSel_isMgr,					0,		(  TCHAR  *  )CONST_popupMenuTable_viewImGrpMemList_multiSel_isMgr,			},
	//
	{	CONST_resId_popup_viewImTaskList_isMgr,								0,		(  TCHAR  *  )CONST_popupMenuTable_viewImTaskList_isMgr,						},
	//
	{	CONST_resId_popup_customerServiceList_isMgr,						0,		(  TCHAR  *  )CONST_popupMenuTable_customerServiceList_isMgr,							},

	{	CONST_resId_popup_wwwQmCfgList_isMgr,								0,		(  TCHAR  *  )CONST_popupMenuTable_wwwQmCfgList_isMgr,							},
#ifdef  __SUPPORT_sm__
	{	CONST_resId_popup_phoneGuestList,									0,		(  TCHAR  *  )CONST_popupMenuTable_phoneGuestList,								},
	{	CONST_resId_popup_phoneGuestList_multiSel,							0,		(  TCHAR  *  )CONST_popupMenuTable_phoneGuestList_multiSel,						},
	//
	{	CONST_resId_popup_gsmModemList,										0,		(  TCHAR  *  )CONST_popupMenuTable_gsmModemList,							},
#endif
	{	CONST_resId_popup_sharedDynBmpList_isMgr,							0,		(  TCHAR  *  )CONST_popupMenuTable_sharedDynBmpList_isMgr,				},
	{	CONST_resId_popup_sharedDynBmpList_multiSel_isMgr,					0,		(  TCHAR  *  )CONST_popupMenuTable_sharedDynBmpList_multiSel_isMgr,				},

	//
	{	CONST_resId_popup_sharedDynBmpRuleList_isMgr,						0,		(  TCHAR  *  )CONST_popupMenuTable_sharedDynBmpRuleList_isMgr,			},


	//
	//
	{	CONST_resId_popup_messenger_isMgr,									0,		(  TCHAR  *  )CONST_popupMenuTable_messenger_isMgr,						},
	{	CONST_resId_popup_imGrp_isMgr,										0,		(  TCHAR  *  )CONST_popupMenuTable_imGrp_isMgr,							},


	//
	{	CONST_resId_popup_commonList,										0,		(  TCHAR  *  )CONST_popupMenuTable_commonList,							},

	//  2007/10/04
	{	CONST_resId_menu_dlgTalk_messenger,									0,		(  TCHAR  *  )CONST_menuTable_dlgTalk_messenger,						},
	{	CONST_resId_menu_dlgTalk_imGrp,										0,		(  TCHAR  *  )CONST_menuTable_dlgTalk_imGrp,							},
	{	CONST_resId_menu_dlgVideos,											0,		(  TCHAR  *  )CONST_menuTable_dlgVideos,								},
	{	CONST_resId_menu_dlgSharedWebcams,									0,		(  TCHAR  *  )CONST_menuTable_dlgSharedWebcams,							},
	{	CONST_resId_menu_dlgVWall,											0,		(  TCHAR  *  )CONST_menuTable_dlgVWall,							},
	{	CONST_resId_menu_dlgRemoteAssist,									0,		(  TCHAR  *  )CONST_menuTable_dlgRemoteAssist,						},
	//
	MACRO_popup_viewProcedObjs
	//
	{	-1,		NULL,		},
};


