
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
#include	"qnmCustomStr_is.h"


extern  QY_DMITEM  CONST_menuTable_jiSuanJiGuanLi_netMc2[];


 QY_DMITEM  CONST_menuTable_jiSuanJiGuanLi_netMc2[]  =
{
	{	ID_qyPcView,	},
	{	-2,				},
	{	ID_qyPcList,	},
	//  {	ID_qyPcSpList,	},
	{	-1,		},
 };

  QY_DMITEM  CONST_menuTable_yongHuGuanLi_netMc2[]  =
{
	{		ID_qyPcUsrList,	0,		0,	},
	{		ID_qyPcUsrInTab1List,	0,		0,	},	
	{		-1,				NULL,			},
};

   QY_DMITEM  CONST_menuTable_keHuDuanGuanLi_netMc2[]  =
{
	{		ID_qwmSvrList,	0,		0,	},		
	{		-1,				NULL,			},
};

/*
	  QY_DMITEM  CONST_menuTable_jiSuanJiAnQuanGuanLi_netMc2[]  =
{
	{		ID_pcRuleList,	0,		0,	},
	{		-1,				NULL,			},
};
*/

	   QY_DMITEM  CONST_menuTable_yuanChengZhuoMianGuanLi_netMc2[]  =
{
	{		ID_pcNetworkPropList,					0,		0,	},
	{		ID_pcNetworkRuleList,					0,		0,	},
	{		-2,													},
	{		ID_pcProxyCfgPropList,					0,		0,	},
	{		ID_pcProxyCfgRuleList,					0,		0,	},
	{		-2,													},
	{		ID_pcComputerPropList,					0,		0,	},
	{		ID_pcComputerRuleList,					0,		0,	},
	{		-2,													},
	{		ID_qyPcSpList,							0,		0,	},
	{		ID_pcWindowsUpdatePolicyPropList,		0,		0,	},
	{		ID_pcWindowsUpdatePolicyRuleList,		0,		0,	},
	{		-2,									},
	{		ID_pcProcessPropList,	0,		0,	},
	{		ID_pcProcessModulePropList,	},
	{		ID_pcProcessRuleList,	0,		0,	},
	{		-2,									},
	{		ID_pcNetFlowPropList_ethernet,			},
	{		ID_pcNetFlowPropList,				},
	{		-2,									},
	{		ID_pcNetSharePropList,				},
	{		-1,				NULL,			},
};

	   QY_DMITEM  CONST_menuTable_jianKongYuShenJi_netMc2[]  =
{
	{		ID_pcSecChkEventList,		(  TCHAR  *  )CONST_resId_pcSecChkEventList_netMc2,		},
	{		-2,										},
	{		ID_pcRegistryList,			0,		0,	},
	{		ID_pcRegistryRuleStatusList,			},
	{		-2,										},
	{		ID_pcEventLogList,			0,		0,	},
	{		ID_pcOsUsrList,				0,		0,	},
	{		ID_qyPcNetStatList,			0,		0,	},
	{		ID_pcPrinterPropList,		0,		0,	},
	{		-1,				NULL,			},
};

	 QY_DMITEM  CONST_menuTable_shiJianChaKan_netMc2[]  =
{
	{		ID_qyEventAll,	0,		0,	},
	{		-2,									},
	{		ID_qyRas,	0,		0,	},
	{		ID_qyProxyServer,	0,		0,	},
	{		ID_qyOnInternet,	0,		0,	},
	{		ID_qyIntraConn,	0,		0,	},
	{		ID_qyDevChanged,	0,		0,	},
	{		ID_qyQwmDel,	0,		0,	},
	{		-2,									},
	{		ID_qyOpEventAll,	0,		0,	},
	{		-1,				NULL,			},
};




 QY_DMITEM  CONST_menuTable_guanLi_netMc2[]  =
{
	{	ID_qyScannedIpList,		},		//	      MENUITEM "扫描检测IP列表(&I)",          
	{	-2,						},		//        MENUITEM SEPARATOR
	{	-3,		(  TCHAR  *  )CONST_resId_menu_jiSuanJiGuanLi,				(  TCHAR  *  )CONST_menuTable_jiSuanJiGuanLi_netMc2,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_yongHuGuanLi,				(  TCHAR  *  )CONST_menuTable_yongHuGuanLi_netMc2,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_keHuDuanGuanLi,				(  TCHAR  *  )CONST_menuTable_keHuDuanGuanLi_netMc2,	},
	{	-2,						},			
	{	-3,		(  TCHAR  *  )CONST_resId_menu_jianKongYuShenJi,			(  TCHAR  *  )CONST_menuTable_jianKongYuShenJi_netMc2,	},	
	//  {	-3,		(  TCHAR  *  )CONST_resId_menu_jiSuanJiAnQuanGuanLi,		(  TCHAR  *  )CONST_menuTable_jiSuanJiAnQuanGuanLi_netMc2,	},
	{	ID_pcRuleList0,	0,		0,	},
	{	ID_pcRuleList1,	0,		0,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_yuanChengZhuoMianGuanLi,		(  TCHAR  *  )CONST_menuTable_yuanChengZhuoMianGuanLi_netMc2,	},	
	//  {	ID_autoLogonList,		},
	{	-2,						},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_shiJianChaKan,				(  TCHAR  *  )CONST_menuTable_shiJianChaKan_netMc2,	},	
	//  {	-3,		(  TCHAR  *  )CONST_resId_menu_yongHuGuanLi,				CONST_menuTable_yongHuGuanLi_netMc2,	},	//  POPUP "用户管理(&Y)"
	//  {	-3,		(  TCHAR  *  )CONST_resId_menu_keHuDuanGuanLi,			CONST_menuTable_keHuDuanGuanLi_netMc2,	},		//  POPUP "客户端管理(&K)"
	//{	-2,						},
	//  {	-3,		(  TCHAR  *  )CONST_resId_menu_jiSuanJiAnQuanGuanLi,		COSNT_menuTable_jiSuanJiAnQuanGuanLi_netMc2,	},	//  POPUP "计算机安全管理(&A)"
	{	-1,		NULL,			},

};



  QY_DMITEM  CONST_menuTable_xiTong_netMc2[]  =
{
#if  0
	{	ID_qyStopMon,		},
	{	ID_qyStartMon,		},
	//  {	-2,						},
#endif
	{	ID_qyStopIpScan		},
	{	ID_qyStartIpScan		},
	{	ID_qyStopRegScan		},
	{	ID_qyStartRegScan	},
	{	-2,						},
	{	ID_stopFileMon,			},
	{	ID_startFileMon,		},
	{	ID_stopModuleMon,		},
	{	ID_startModuleMon,		},
	{	ID_stopPcRegistryMon,	},
	{	ID_startPcRegistryMon,	},
	{	-2,						},
	{	ID_qyStartUpdate		},
	{	ID_qyStopUpdate		},
	{	-1,		NULL,			},

};
  QY_DMITEM CONST_menuTable_peiZhi_netMc2[]	=
  {
	{	ID_qyCfgIpScan,				},
	{	ID_qyMgrPcGrp,				},
	{	ID_qyCfgUnchk,				},
	{	ID_qyCfgSkippedMacs,			},
	{	-2,							},
	{	ID_cfgSystemParams,			},
	{	-2,							},
	{	ID_cfgPcMonOptions,			},
	{	ID_cfgRasOptions,			},
	{	ID_cfgPcNetworkOptions,		},
	{	-2,							},
	//  {	ID_qyCfgBoard,				},
	//  {	ID_qyCfgSp,					},
	{	ID_qyCfgModuleInfo,			},
	{	ID_qyCfgPcRegistryKnowledge,	},
	//  {	-2,							},
	//  {	ID_qyCfgAutoLogon,			},
	{	-2,							},
	{	ID_qyCfgCustom,				},
	{	ID_qyCfgStandardNames,		},
	{	-2,							},
	{	ID_cfgOptions				},
	{	ID_cfgAdvancedOptions		},
	{	ID_CFGWARN,					},
	{	-2,							},
	{	ID_CFGUSR					},
	{	-1,		NULL,			},
 };

 QY_DMITEM  CONST_mainMenuTable_netMc2[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_wenJian,		(  TCHAR  *  )CONST_menuTable_wenJian,			},	//  2006/12/17
	{	-3,		(  TCHAR  *  )CONST_resId_menu_guanLi,		(  TCHAR  *  )CONST_menuTable_guanLi_netMc2,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_xiTong,		(  TCHAR  *  )CONST_menuTable_xiTong_netMc2,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,		(  TCHAR  *  )CONST_menuTable_peiZhi_netMc2,},
	{	ID_qyMakeClients,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chaKan,		(  TCHAR  *  )CONST_menuTable_chaKan_netMc,  },
	{	-3,		(  TCHAR  *  )CONST_resId_menu_bangZhu,		(  TCHAR  *  )CONST_menuTable_bangZhu,},
	{	-1,		NULL,		},
};



 QY_DMITEM  CONST_childFrmMenuTable_netMc2[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_wenJian,	(  TCHAR  *  )CONST_menuTable_wenJian,			},	//  2006/12/17
	{	-3,		(  TCHAR  *  )CONST_resId_menu_guanLi,  (  TCHAR  *  )CONST_menuTable_guanLi_netMc2,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_xiTong,	(  TCHAR  *  )CONST_menuTable_xiTong_netMc2,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,	(  TCHAR  *  )CONST_menuTable_peiZhi_netMc2,},
	{	ID_qyMakeClients,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chaKan,	(  TCHAR  *  )CONST_menuTable_chaKan_netMc,},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chuangKou,	(  TCHAR  *  )CONST_menuTable_chuangKou,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_bangZhu,	(  TCHAR  *  )CONST_menuTable_bangZhu,},
	{	-1,		NULL,		},
};



 QY_DMITEM  CONST_cusMenusTable_netMc2[]  =
{
	{	CONST_resId_mainMenu,				(  TCHAR  *  )CONST_mainMenuTable_netMc2,			},
	{	CONST_resId_childFrmMenu,			(  TCHAR  *  )CONST_childFrmMenuTable_netMc2,		},
	{	CONST_resId_popupMenu,				(  TCHAR  *  )CONST_popupMenuTable_netMc,			},
	{	-1,		NULL,		},
};


  QY_DMITEM  CONST_ipScanOfficeLevelTable[]  =
{
	{	0,		CONST_str_danWei,		_T(  "qnmScannedIpTab.officeName"  ),	},
	{	1,		CONST_str_buMen,		_T(  "qnmScannedIpTab.subOfficeName"  ),	},
	{	-1,		NULL,		},
};




 QY_DMITEM  CONST_jqlxTable[]  =
{
	{	CONST_jqlx_wj,			CONST_str_jqlx_wj,	},
	{	CONST_jqlx_bxj,			CONST_str_jqlx_bxj,	},
	{   CONST_jqlx_fwq,			CONST_str_jqlx_fwq,	},
	{	CONST_jqlx_xxj,			CONST_str_jqlx_xxj,	},	
	{	-1,						NULL,			},
};


 ////////////  2008/12/15

  QY_DMITEM  CONST_qySystemIdTable[]  =
{
	{	CONST_qySystemId_bha,							CONST_qySystemId_str_bha,						},
	//  {	CONST_qySystemId_bhb,						_T(  "清扬创新拨号上网监管系统(检测版)"  ),		},
	{	CONST_qySystemId_bhb,							CONST_qySystemId_str_bhb,						},
	{	CONST_qySystemId_netMc2,						CONST_qySystemId_str_netMc2,					},
	{	CONST_qySystemId_nms,							CONST_qySystemId_str_nms,						},
	{	CONST_qySystemId_secChk,						CONST_qySystemId_str_secChk,					},
	{	CONST_qySystemId_assetMgr,						CONST_qySystemId_str_assetMgr,					},
	{	CONST_qySystemId_messenger,						_T(  "Messenger"  ),							},
	{	-1,												NULL,											},
};

 QY_DMITEM  CONST_ucbDsnlessTable[]  =
{
	{	CONST_ucbDsnless_true,							CONST_str_ucbDsnless,  },
	{	FALSE,											CONST_str_usbDsn,	},
	{	-1,				},
};


 QY_DMITEM  CONST_qnmStopMonTable[]  =  
{
	{  (  unsigned  char  )FALSE,			CONST_str_notUninstall,				},
	{  (  unsigned  char  )TRUE,			CONST_str_uninstall,				},
	{	-1,									NULL,								},
};


 QY_DMITEM  CONST_qnmCfgRasCmdTable[]  =
{
	{	CONST_rasCmd_permitted,				CONST_str_dialUpAllowed,		_T(  CONST_rasCmdStr_permitted  ),			},
	{	CONST_rasCmd_prohibited,			CONST_str_dialUpForbidden,		_T(  CONST_rasCmdStr_prohibited  ),			},
	{	CONST_rasCmd_offlinePermitted,		CONST_str_offlineDialUpAllowed,	_T(  CONST_rasCmdStr_offlinePermitted  ),	},
	{	-1,									NULL,												},
};

 QY_DMITEM  CONST_qnmRasCmdTable[]  =
{
	{	CONST_rasCmd_default,				CONST_str_default,				},
	{	CONST_rasCmd_permitted,				CONST_str_dialUpAllowed,			},
	{	CONST_rasCmd_prohibited,			CONST_str_dialUpForbidden,			},
	{	CONST_rasCmd_offlinePermitted,		CONST_str_offlineDialUpAllowed,			},
	{	CONST_rasCmd_zdhmyx,				CONST_str_phoneNoAllowed,		},		
	{	-1,									NULL,				},
};


 QY_DMITEM  CONST_objTypeTable[]  =
{
	{	CONST_objType_null,					_T(  ""  ),						},
	{	CONST_objType_qySwitch,				_T(  "Switch"  ),				},
	{	CONST_objType_qySwitchPort,			_T(  "SwitchPort"  ),			},
	{	CONST_objType_col2,					_T(  "col2"  ),					},
	{	CONST_objType_col3,					_T(  "col3"  ),					},
	{	CONST_objType_col4,					_T(  "col4"  ),					},
	{	CONST_objType_unRegGrp,				_T(  "unRegGrp"  ),				},
	{	CONST_objType_othersGrp,			_T(  "othersGrp"  ),			},
	//  {	CONST_objType_unRegPc,				_T(  "unRegPc"  ),				},
	{	CONST_objType_pc,					_T(  "PC"  ),					},
	{	CONST_objType_otherPc,				_T(  "otherPc"  ),				},
	{	CONST_objType_mac,					_T(  "MAC"  ),					},
	{	CONST_objType_os,					_T(  "os"  ),					},
	{	CONST_objType_pcEnv,				_T(  "pcEnv"  ),				},
	{	CONST_objType_cfgSpOs,				_T(  "cfgSpOs"  ),				},
	{	CONST_objType_cfgSpServicePack,		_T(  "cfgSpServicePack"  ),		},
	{	CONST_objType_zb,					_T(  "zb"  ),					},
	{	CONST_objType_bb,					_T(  "bb"  ),					},
	{	CONST_objType_dw,					_T(  "dw"  ),					},
	{	CONST_objType_bm,					_T(  "bm"  ),					},
	{	CONST_objType_syr,					_T(  "syr"  ),					},
	{	CONST_objType_pcStatus,				_T(  "pcStatus"  ),				},
	{	CONST_objType_pcUsrInfo,			CONST_IDC_pcUsrInfo,		},
	{	CONST_objType_pcOsClass,			CONST_str_os,		},
	{	CONST_objType_pcOpNode,				CONST_str_opNode,				},
	{	CONST_objType_procedObj,			CONST_str_dataSources,				},
	//
	{	CONST_objType_browser,				_T(  "Browser"  ),				},
	//
	{	CONST_objType_phone,				_T(  "Phone"  ),				},
	{	CONST_objType_dev,					_T(  "Dev"  ),					},
	//
	{	CONST_objType_toPath,				CONST_str_sendChannel,				},
	{	CONST_objType_webcam,				_T(  "Webcam"  ),					},
	{	CONST_objType_screen,				_T(  "Screen"  ),					},
	{	CONST_objType_rtspStream,			_T(  "Rtsp"  ),				},
	{	CONST_objType_smallStream,				_T(  "Small Stream"  ),			},		//  2014/09/25
	{	CONST_objType_ic,			        _T("IC"),				},
	
	//
	//  2007/05/12, 以下为mis系统的类型定义
	{	CONST_objType_mis_base,				_T(  "mis_base"  ),				},
	//
	{	CONST_objType_admin,				CONST_str_admin,				},
	//
	{	CONST_objType_me,					CONST_objIdStr_me,					},
	//
	{	CONST_objType_messenger,			CONST_str_contact,				},
	{	CONST_objType_webGuest,				_T(  "Web Guest"  ),			},
	//
	{	CONST_objType_phoneMessenger,		CONST_str_phoneContact,			},
	{	CONST_objType_phoneGuest,			_T(  "Phone Guest"  ),			},
	//
	{	CONST_objType_newDevGuest,			_T(  "New device Guest"  ),		},
	//
	{	CONST_objType_imGrps,				CONST_objIdStr_imGrps,			},

	{	CONST_objType_imGrp,				CONST_str_group,					},
	//
	{	CONST_objType_tmpGrp,				CONST_str_tempGroup,				},
	//
	{	CONST_objType_newDev,					_T(  "New device"  ),			},	
	//
	{	CONST_objType_mosaicStream_video,		_T(  "mosaicV"  ),				},
	{	CONST_objType_mosaicStream_resource,	_T(  "mosaicR"  ),			},

	//
	{	-1,																	},
};

 QY_DMITEM  CONST_imGrpSubtypeTable[]  =
 {
	 {	CONST_imGrpSubtype_av,				CONST_str_imGrps_av,		},
	 {	CONST_imGrpSubtype_msg,				CONST_str_imGrps_msg,		},
	 {	CONST_imGrpSubtype_resource,		CONST_str_imGrps_resource,	},	//  2018/07/09
	 {	CONST_imGrpSubtype_initConf,		CONST_str_imGrp_initConf,	},
	 //
	 {	CONST_imGrpSubtype_mgr,				CONST_str_imGrp_mgr,	},
	 //
	 {	-1,				},
 };

 //  2015/07/28
 QY_DMITEM  CONST_imGrpMemRoleTable[]  =
 {
	 {	CONST_imGrpMemRole_mgr,		CONST_str_mgr,		},
	 {	-1,	},
 };

 //  2017/08/14
 QY_DMITEM  CONST_imObjRoleTable[]  =
 {
	 {	CONST_imObjRole_superAdmin,		CONST_str_superAdmin,		},
	 {	-1,	},
 };
 

 //  2008/12/28
 QY_DMITEM  CONST_fieldIdTable[]  =
{
	{	CONST_fieldId_yhlx,					_T(  "用户类型"  ),				},
	{	CONST_fieldId_syr,					CONST_str_shiYongRen,				},
	{	CONST_fieldId_bm,					CONST_str_buMen,					},
	{	CONST_fieldId_dw,					CONST_str_danWei,					},
	{	CONST_fieldId_bb,					CONST_str_benBu,					},
	{	CONST_fieldId_zb,					CONST_str_zongBu,					},
	{	CONST_fieldId_qtdw,					CONST_str_qiTaDanWei,				},
	//
	{	CONST_fieldId_zcbh0,				CONST_str_ziChanBianHao,				},
	{	CONST_fieldId_zcbh1,				CONST_str_ziChanBianHao1,			},
	{	CONST_fieldId_zcbh2,				CONST_str_ziChanBianHao2,			},
	//  #define		CONST_fieldId_zcsm0								123
	{	CONST_fieldId_zcsm1,				CONST_str_ziChanShuoMing1,			},
	{	CONST_fieldId_zcsm2,				CONST_str_ziChanShuoMing2,			},
	{	CONST_fieldId_jqlx,					CONST_str_jiQiLeiXing,				},
	{	CONST_fieldId_lxdh,					CONST_str_lianXiDianHua,				},
	{	CONST_fieldId_sydd,					CONST_str_shiYongDiDian,				},
	{	CONST_fieldId_zyyt,					CONST_str_zhuYaoYongTu,				},
	{	CONST_fieldId_bz1,					_T(  "备注1"  ),				},
	{	CONST_fieldId_bz2,					_T(  "备注2"  ),				},
	//
	{	-1,									NULL,					},
};

 //  2009/01/01
 QY_DMITEM  CONST_qyCommTypeTable[]  =
{
#if  0
	{	CONST_pcNetworkPropType_adapter,					CONST_IDC_STATIC_pcNetworkPropType,				},
	{	CONST_pcNetworkPropType_proxy,						CONST_str_proxy,			},
	{	CONST_pcNetworkPropType_computer,					CONST_str_jiSuanJiMing,				},
	{	CONST_pcCommType_cleanNetworkProp,					CONST_str_clearNetworkConfig,	},
	{	CONST_pcCommType_process,							CONST_str_process,					},
	{	CONST_pcCommType_eventLog,							CONST_str_systemLog,				},
	{	CONST_pcCommType_usrInfo,							CONST_str_computerUser,			},
	{	CONST_pcCommType_tcpTable,							CONST_str_tcpConnection,				},
	{	CONST_pcCommType_udpTable,							CONST_str_udpConnection,				},
	{	CONST_pcCommType_printers,							CONST_str_printer,				},
	{	CONST_pcCommType_processRule,						CONST_str_processRule,				},
	{	CONST_pcCommType_processModule,						CONST_str_module,					},
	{	CONST_pcCommType_windowsUpdatePolicy,				CONST_str_wsusCfg,			},
	{	CONST_pcCommType_registryVal,						CONST_str_register,			},
	{	CONST_pcCommType_netFlow,							CONST_str_netFlow,					},
	{	CONST_pcCommType_netShare,							CONST_str_netShareCmd,				},
	//
	{	CONST_pcCommType_switchRule,						CONST_str_snmpObjRule,				},
	{	CONST_pcCommType_switchPortRule,					CONST_str_snmpObjPortRule,				},
	//
	//  {	CONST_pcCommType_pcFileMonRules					2		//  2006/07/16, 历史遗留问题，此定义不能改
	{	CONST_pcCommType_registryRule,						CONST_str_registerRule,			},
	{	CONST_pcCommType_registryRuleStatus,				CONST_str_statusOfRegRule,	},
	{	CONST_pcCommType_queryCfgs,							CONST_str_requestToGetCfg,		},
	{	CONST_pcCommType_pcProcessKnowledge,				CONST_str_processKnowledge,				},
	{	CONST_pcCommType_pcRegistryKnowledge,				CONST_str_registerKnowledge,			},
#endif 
	//
	//  mis系统的参数在下面定义，2007/05/07
	{	CONST_imCommType_htmlContent,						CONST_str_htmlContent,			},
	{	CONST_imCommType_simpleResp,						CONST_str_simpleResponse,				},
	//	{	CONST_imCommType_streamContent,						CONST_str_streamDate,			},
	//  {	CONST_imCommType_msgRoute,							_T(  "消息路由"  ),				},
	//  {	CONST_imCommType_dataContent,						_T(  "raw数据"  ),				},
	{	CONST_imCommType_lStream,							CONST_str_longStreamDate,				},
	//  
	{	CONST_imCommType_retrieveImGrpListReq,				CONST_str_retrieveImGrpListReq,		},
	{	CONST_imCommType_retrieveImGrpListResp,				CONST_str_retrieveImGrpListResp,		},
	{	CONST_imCommType_retrieveImGrpMemListReq,			CONST_str_retrieveImGrpMemListReq,		},
	{	CONST_imCommType_retrieveImGrpMemListResp,			CONST_str_retrieveImGrpMemListResp,		},
	{	CONST_imCommType_retrieveContactListReq,			CONST_str_retrieveContactListReq,		},
	{	CONST_imCommType_retrieveContactListResp,			CONST_str_retrieveContactListResp,		},
	{	CONST_imCommType_retrieveImObjListEndReq,			CONST_str_retrieveImObjListEndReq,	},
	{	CONST_imCommType_retrieveImObjListEndResp,			CONST_str_retrieveImObjListEndResp,	},
	//
	{	CONST_imCommType_messengerRegInfo,					CONST_str_messengerRegInfo,	},
	{	CONST_imCommType_messengerPcInfo,					CONST_str_messengerPcInfo,		},
	//
	{	CONST_imCommType_refreshRecentFriendsReq,			CONST_str_refreshRecentFriendsReq,	},
	{	CONST_imCommType_refreshRecentFriendsResp,			CONST_str_refreshRecentFriendsResp,	},
	//
	{	CONST_imCommType_transferFileReq,					CONST_str_transferFileReq,				},
	{	CONST_imCommType_transferFileReplyReq,				CONST_str_transferFileReplyReq,			},
	{	CONST_imCommType_transferFileDataReq,				CONST_str_transferFileDataReq,		},
	{	CONST_imCommType_transferFileDataResp,				CONST_str_transferFileDataResp,		},
	{	CONST_imCommType_transferFileEndReq,				CONST_str_transferFileEndReq,		},
	{	CONST_imCommType_transferFileEndResp,				CONST_str_transferFileEndResp,		},
	{	CONST_imCommType_taskProcReq,						CONST_str_taskProcReq,			},
	{	CONST_imCommType_taskProcResp,						CONST_str_taskProcResp,			},
	//
	{	CONST_imCommType_rtcCallReq,						_T(  "Rtc Call Req"  ),			},
	//
	{	CONST_imCommType_transferAvInfo,					CONST_str_transferAvInfo,				},
	{	CONST_imCommType_transferAvReplyInfo,				CONST_str_transferAvReplyInfo,				},
	{	CONST_imCommType_transferVideoData,					CONST_str_transferVideoData,			},
	{	CONST_imCommType_transferVideoDataResp,				CONST_str_transferVideoDataResp,		},
	//
	{	CONST_imCommType_transferAudioData,					CONST_str_transferAudioData,			},
	{	CONST_imCommType_transferAudioDataResp,				CONST_str_transferAudioDataResp,		},
	//
	{	CONST_imCommType_transferGpsInfo,					CONST_str_transferGpsInfo,		},
	//
	//
	//  {	CONST_imCommType_transferFileStatus,				_T(  "传送文件状态"  ),			},
	//
	{	CONST_imCommType_imGrp,								CONST_str_imGrp,				},
	{	CONST_imCommType_refreshImGrp,						CONST_str_refreshImGrp,				},
	//
	{	CONST_imCommType_retrieveWebContactListReq,			CONST_str_retrieveWebContactListReq,	},
	{	CONST_imCommType_retrieveWebContactListResp,		CONST_str_retrieveWebContactListResp,	},
    //
	{	CONST_imCommType_refreshWebContactsInfo,			CONST_str_refreshWebContactsInfo,		},
	{	CONST_imCommType_ipKnowledge,						CONST_str_ipKnowledge,			},
	//
	{	CONST_imCommType_retrieveCustomerServiceObjListReq,	CONST_str_retrieveCustomerServiceObjListReq,	},
	{	CONST_imCommType_queryCustomerServiceOfficerReq,	CONST_str_queryCustomerServiceOfficerReq,		},
	//
	{	CONST_imCommType_smPkt,								_T(  "Short Message Packet"  ),	},
	{	CONST_imCommType_phoneGuest,						_T(  "Phone Guest"  ),			},
	{	CONST_imCommType_vDevComs,							_T(  "VDev Coms"  ),			},
	{	CONST_imCommType_retrieveSmPolicy,					CONST_str_retrieveSmPolicy,			},
	//
	{	CONST_imCommType_vDevData,							_T(  "VDev Data"  ),			},
	//	
	{	-1,													NULL,				},
};

 QY_DMITEM  CONST_ruleCmdTable[]  =
{
	{	CONST_ruleCmd_prohibit,								CONST_str_prohibit,/*_T(  "禁止"  ),*/				},
	{	CONST_ruleCmd_prohibitAll,							CONST_str_prohibitAll,/*_T(  "统一禁止"  ),*/		},
	{	CONST_ruleCmd_permit,								CONST_str_permit,/*_T(  "允许"  ),*/				},
	{	CONST_ruleCmd_permitAll,							CONST_str_permitAll,/*_T(  "统一允许"  ),*/			},
	//
	{	CONST_ruleCmd_permitAndFullscreen,					CONST_str_permitAndFullscreen,	},
	{	-1,			NULL,			},
};

 QY_DMITEM  CONST_grpNameTable[]  =
{
	{	0,	_T(  CONST_grpName_admin  ),	CONST_str_adminGrp,		},
	{	0,	_T(  CONST_grpName_xtpz  ),		CONST_str_cfgGrp,		},
	{	0,	_T(  CONST_grpName_rzsj  ),		CONST_str_logGrp,		},
	{	-1,	NULL,									},
};

 QY_DMITEM  CONST_usRunningStatusTable[]  =
{
#if  0
	{		CONST_usRunningStatus_null,							_T(  ""  ),			},
	{		CONST_usRunningStatus_online,						CONST_str_online,		},
	{		CONST_usRunningStatus_offline,						CONST_str_offline,		},
	{		CONST_usRunningStatus_away,							_T(  "离开"  ),		},
	{		CONST_usRunningStatus_hide,							_T(  "隐身"  ),		},
	{		CONST_usRunningStatus_neverLogon,					_T(  "未上线"  ),	},
#endif 
	{		-1,																		},
};



 QY_DMITEM  CONST_AUOptionsTable[]  =
{
	{	1,		CONST_str_turnOffUpdating,				},
	{	2,		CONST_str_beNotifiedDownAndInstall,		},
	{	3,		CONST_str_beNotifiedInstall,		},
	{	4,		CONST_str_scheduledInstall,		},
	{	5,		CONST_str_chooseSettings,		},
	{	-1,		},
};

 QY_DMITEM  CONST_NoAutoUpdateTable[]  =
{
	{	0,		CONST_str_turnOnUpdating,				},
	{	1,		CONST_str_turnOffUpdating,				},
	{	-1,		},
};

 QY_DMITEM  CONST_RescheduleWaitTimeEnabledTable[]  =
{
	{	0,		CONST_str_notRescheduleAutomaticUpdating,	},
	{	1,		CONST_str_rescheduleAutomaticUpdating,	},
	{	-1,			},
};

 QY_DMITEM  CONST_DetectionFrequencyEnabledTable[]  = 
{
	{	0,		CONST_str_disableDetectionFrequency,				},
	{	1,		CONST_str_enableDetectionFrequency,					},
	{	-1,		},
 };

 QY_DMITEM  CONST_NoAutoRebootWithLoggedOnUsersTable[]  =
{
	{	0,		CONST_str_autoRebootWithLoggedOnUsers,	},
	{	1,		CONST_str_noAutoRebootWithLoggedOnUsers,	},
	{	-1,			},
};

 QY_DMITEM  CONST_ElevateNonAdminsTable[]  =
{
	{	0,		CONST_str_elevateAdmins,	},
	{	1,		CONST_str_elevateNonAdmins,	},
	{	-1,			},
};

 QY_DMITEM  CONST_TargetGroupEnabledTable[]  =
{
	{	0,		CONST_str_targetGroupDisable,	},
	{	1,		CONST_str_targetGroupEnable,	},
	{	-1,			},
};

//
  QY_DMITEM	CONST_qnmDevCmdTable[]  =
{
	{	CONST_devCmd_permitted,				CONST_str_enable,				},
	{	CONST_devCmd_prohibited,			CONST_str_disable,				},
	{	-1,									NULL,					},
};

 QY_DMITEM	CONST_qnmDevCmd1Table[]  =
{
	{	CONST_devCmd_permitted,				CONST_str_enable,				},
	{	CONST_devCmd_prohibited,			CONST_str_disable,				},
	{	CONST_devCmd_prohibitedCanReboot,	CONST_str_disableCanReboot,				},
	{	-1,									NULL,					},
};

 QY_DMITEM	CONST_qnmDevCmd2Table[]  =
{
	{	CONST_devCmd_permitted,				CONST_str_enable,				},
	{	-1,									NULL,					},
};


 QY_DMITEM  CONST_qnmDevCmdTable0[]	=		//  ÓÃÀ´»ã×ÜËùÓÐµÄÃüÁî£¬ÔÚÏÔÊ¾ÖÐÒ²·½±ã. 2005/06/22
{
	{	CONST_devCmd_permitted,				CONST_str_enable,				},
	{	CONST_devCmd_permittedAndLog,		CONST_str_log,	},	//  fileMonitoring,			
	{	CONST_devCmd_prohibited,			CONST_str_disable,				},
	{	CONST_devCmd_restartToProhibit,		CONST_str_rebootToBlock,				},		//  2005/06/22
	{	CONST_devCmd_prohibitedCanReboot,	CONST_str_disableCanReboot,				},
	{	CONST_devCmd_none,					CONST_str_noSetting,				},		//  2007/02/13
	{	-1,									NULL,					},
};

 QY_DMITEM  CONST_qnmUsbCmdTable[]  =
{
	{	CONST_devCmd_permitted,				CONST_str_enable,				},
	#ifndef  __NOTSUPPORT_FILEMON__
			{	CONST_devCmd_permittedAndLog,		CONST_str_log,				},	//  CONST_str_fileMonitoring,			
	#endif
	{	CONST_devCmd_prohibited,			CONST_str_disable,				},
	{	CONST_devCmd_restartToProhibit,		CONST_str_rebootToBlock,				},		//  2005/06/22
	{	-1,									NULL,					},
};

 //  2010/05/20
  QY_DMITEM  CONST_wLanAdapterCmdTable[]  =
{
	{	CONST_devCmd_permitted,				CONST_str_enable,				},
#if  0
	{	CONST_devCmd_permittedAndLog,		CONST_str_log,					},
#endif
	{	CONST_devCmd_prohibited,			CONST_str_disable,				},
	{	-1,									NULL,					},
};


 QY_DMITEM  CONST_qnmAutorunCmdTable[]  =	//  2007/02/13
{
	{	CONST_devCmd_none,					CONST_str_noSetting,				},		//  2007/02/13
	{	CONST_devCmd_permitted,				CONST_str_enable,				},
	{	CONST_devCmd_prohibited,			CONST_str_disable,				},
	{	-1,									NULL,					},
};

 QY_DMITEM  CONST_pcAdapterStatusTable[]  =  
{
	{	CONST_pcAdapterStatus_null,								_T(  ""  ),				},
	{	CONST_pcAdapterStatus_willBeLocked,						CONST_str_locking,		},
	{	CONST_pcAdapterStatus_locked,							CONST_str_locked,		},
	{	CONST_pcAdapterStatus_cantBeLocked,						CONST_str_unableToBeLocked,		},
	{	-1,														NULL,			},
};







  //   
 //  以下是的定制信息  {
//	#if  DEFAULT_qyCustomId  ==  CONST_qyCustomId_zjga

 QY_DMITEM	myCONST_yhGrpTable_netMc[]  =
{
	{	4,		CONST_str_zongBu,			_T(  "qyPcRegInfoTab.col11"  ),	},
	{	3,		CONST_str_benBu,			_T(  "qyPcRegInfoTab.col12"  ),	},
	{	2,		CONST_str_danWei,			_T(  "qyPcRegInfoTab.col2"  ),	},
	{	1,		CONST_str_buMen,			_T(  "qyPcRegInfoTab.col3"  ),	},
	{	0,		CONST_str_yongHu,			_T(  "qyPcRegInfoTab.col4"  ),	},
	{	-1,		NULL,									},
};

  QY_DMITEM  myCONST_eventYhGrpTable_netMc[]  =
{
	{	4,		CONST_str_zongBu,			_T(  "qyPcEventTab.col5"  ),	},
	{	3,		CONST_str_benBu,			_T(  "qyPcEventTab.col6"  ),	},
	{	0,		CONST_str_danWei,			_T(  "qyPcEventTab.col2"  ),	},
	{	1,		CONST_str_buMen,			_T(  "qyPcEventTab.col3"  ),	},
	{	2,		CONST_str_yongHu,			_T(  "qyPcEventTab.col4"  ),	},
	{	-1,		NULL,									},

};


  QY_DMITEM	myCONST_yhGrpTable_is[]  =
{
	{	4,		CONST_str_zongBu,			_T(  "qyImObjRegInfoTab.col11"  ),	},
	{	3,		CONST_str_benBu,			_T(  "qyImObjRegInfoTab.col12"  ),	},
	{	2,		CONST_str_danWei,			_T(  "qyImObjRegInfoTab.col2"  ),	},
	{	1,		CONST_str_buMen,			_T(  "qyImObjRegInfoTab.col3"  ),	},
	{	0,		CONST_str_yongHu,			_T(  "qyImObjRegInfoTab.col4"  ),	},
	{	-1,		NULL,									},
};



 QY_DMITEM  myCONST_eventYhGrpTable_is[]  =
{
	{	4,		CONST_str_zongBu,			_T(  "qyImEventTab.col5"  ),	},
	{	3,		CONST_str_benBu,			_T(  "qyImEventTab.col6"  ),	},
	{	0,		CONST_str_danWei,			_T(  "qyImEventTab.col2"  ),	},
	{	1,		CONST_str_buMen,			_T(  "qyImEventTab.col3"  ),	},
	{	2,		CONST_str_yongHu,			_T(  "qyImEventTab.col4"  ),	},
	{	-1,		NULL,									},

};

//  #endif



 QY_DMITEM  CONST_queryTypeTable_netMc2[]  =		//  2006/09/28
{
	{	CONST_qyQueryType_netMcEventList,			CONST_str_jiSuanJiShiJianChaXun,			},
	{	CONST_qyQueryType_netMcPcList,				CONST_str_jiSuanJiChaXun,					},
	{	CONST_qyQueryType_pcProcessList,			CONST_str_jinChengChaXun,					},
	{	CONST_qyQueryType_pcProcessModuleList,		CONST_str_jinChengDiaoYongMoKuaiChaXun,		},
	{	CONST_qyQueryType_pcRegistryList,			CONST_str_zhuCeBiaoChaXun,					},		//  2006/08/15
	{	CONST_qyQueryType_secChkEventList,			CONST_str_jianChaJieGuoChaXun,				},
	{	CONST_qyQueryType_netMcPcSpList,			CONST_str_buDingChaXun,						},
	{	CONST_qyQueryType_opEventList,				CONST_str_xiTongShiJianChaXun,				},		//  2006/02/25
	{	-1,											NULL,					},
};

 

 QY_DMITEM  CONST_tableTable_netMc2[]  =
{
	{ 	CONST_resId_qnmEventTypeTable0,				(  TCHAR  *  )CONST_qnmEventTypeTable0_netMc,				},
	{	CONST_resId_qnmEventTypeTable_pc,			(  TCHAR  *  )CONST_qnmEventTypeTable_netMc2,		},
	{	CONST_resId_qnmEventTypeTable_op,			(  TCHAR  *  )CONST_qnmEventTypeTable_op_netMc,			},
	{	CONST_resId_qnmEventTypeTable_netDev,		(  TCHAR  *  )CONST_qnmEventTypeTable_nmsNetDev,	},
	{	CONST_resId_ipScanOfficeLevelTable,			(  TCHAR  *  )CONST_ipScanOfficeLevelTable,			},
	{	CONST_resId_zjgaYhlxTable,					(  TCHAR  *  )CONST_zjgaYhlxTable,					},
	{	CONST_resId_gYhGrpTable,					(  TCHAR  *  )gYhGrpTable,							},
	{	CONST_resId_gEventYhGrpTable,				(  TCHAR  *  )gEventYhGrpTable,						},
	{	CONST_resId_secChkEventTypeTable,			(  TCHAR  *  )CONST_secChkEventTypeTable_netMc2,	},
	{	CONST_resId_qyNullTable,					(  TCHAR  *  )CONST_nullTable,						},
	{	CONST_resId_jqlxTable,						(  TCHAR  *  )CONST_jqlxTable,						},
	{	CONST_resId_qnmStopMonTable,				(  TCHAR  *  )CONST_qnmStopMonTable,				},
	{	CONST_resId_qnmCfgRasCmdTable,				(  TCHAR  *  )CONST_qnmCfgRasCmdTable,				},
	{	CONST_resId_qnmRasCmdTable,					(  TCHAR  *  )CONST_qnmRasCmdTable,					},
	{	CONST_resId_ucWLanAdapterCmdTable,			(  TCHAR  *  )CONST_wLanAdapterCmdTable,			},
	{	CONST_resId_ucBlueToothCmdTable,			(  TCHAR  *  )CONST_qnmDevCmdTable,					},
	{	CONST_resId_ucInfraredCmdTable,				(  TCHAR  *  )CONST_qnmDevCmdTable,					},		//  2010/08/18
	{	CONST_resId_uc1394CmdTable,					(  TCHAR  *  )CONST_qnmDevCmdTable,					},		//  2010/08/18
	{	CONST_resId_ucWpdCmdTable,					(  TCHAR  *  )CONST_qnmDevCmd1Table,					},		//  2011/08/26
	{	CONST_resId_ucSdHostAdapterCmdTable,		(  TCHAR  *  )CONST_qnmDevCmd1Table,					},		//  2011/08/26
	{	CONST_resId_ucMobileDeviceCmdTable,			(  TCHAR  *  )CONST_qnmDevCmd1Table,					},		//  2011/08/26
	{	CONST_resId_ucUsbNetworkCardCmdTable,		(  TCHAR  *  )CONST_qnmDevCmd2Table,					},		//  2011/11/08


	{	CONST_resId_qySystemIdTable,				(  TCHAR  *  )CONST_qySystemIdTable,				},
	{	CONST_resId_ucbDsnlessTable,				(  TCHAR  *  )CONST_ucbDsnlessTable,				},
	//
	{	CONST_resId_myCONST_yhGrpTable_netMc,		(  TCHAR  *  )myCONST_yhGrpTable_netMc,				},
	{	CONST_resId_myCONST_eventYhGrpTable_netMc,	(  TCHAR  *  )myCONST_eventYhGrpTable_netMc,		},
	{	CONST_resId_myCONST_yhGrpTable_is,			(  TCHAR  *  )myCONST_yhGrpTable_is,				},
	{	CONST_resId_myCONST_eventYhGrpTable_is,		(  TCHAR  *  )myCONST_eventYhGrpTable_is,			},
	//

	//
	{	CONST_resId_objTypeTable,					(  TCHAR  *  )CONST_objTypeTable,					},
	{	CONST_resId_queryTypeTable,					(  TCHAR  *  )CONST_queryTypeTable_netMc2,			},
	//
	{	CONST_resId_fieldIdTable,					(  TCHAR  *  )CONST_fieldIdTable,					},
	{	CONST_resId_qyCommTypeTable,				(  TCHAR  *  )CONST_qyCommTypeTable,				},
	{	CONST_resId_pcCommTypeTable,				(  TCHAR  *  )CONST_pcCommTypeTable,				},
	//  {	CONST_resId_pcProcessRuleTypeTable,			(  TCHAR  *  )CONST_pcProcessRuleTypeTable,			},
	{	CONST_resId_ruleCmdTable,					(  TCHAR  *  )CONST_ruleCmdTable,			},
	{	CONST_resId_grpNameTable,					(  TCHAR  *  )CONST_grpNameTable,					},
	{	CONST_resId_usRunningStatusTable,			(  TCHAR  *  )CONST_usRunningStatusTable,			},
	{	CONST_resId_AUOptionsTable,					(  TCHAR  *  )CONST_AUOptionsTable,					},
	{	CONST_resId_NoAutoUpdateTable,				(  TCHAR  *  )CONST_NoAutoUpdateTable,				},
	{	CONST_resId_RescheduleWaitTimeEnabledTable,	(  TCHAR  *  )CONST_RescheduleWaitTimeEnabledTable,	},
	{	CONST_resId_DetectionFrequencyEnabledTable,	(  TCHAR  *  )CONST_DetectionFrequencyEnabledTable,	},
	{	CONST_resId_NoAutoRebootWithLoggedOnUsersTable,	(  TCHAR  *  )CONST_NoAutoRebootWithLoggedOnUsersTable,  },
	{	CONST_resId_ElevateNonAdminsTable,			(  TCHAR  *  )CONST_ElevateNonAdminsTable,			},
	{	CONST_resId_TargetGroupEnabledTable,		(  TCHAR  *  )CONST_TargetGroupEnabledTable,},
	{	CONST_resId_qnmDevCmdTable,					(  TCHAR  *  )CONST_qnmDevCmdTable,					},
	{	CONST_resId_qnmDevCmdTable0,				(  TCHAR  *  )CONST_qnmDevCmdTable0,				},
	{	CONST_resId_qnmUsbCmdTable,					(  TCHAR  *  )CONST_qnmUsbCmdTable,					},
	{	CONST_resId_qnmAutorunCmdTable,				(  TCHAR  *  )CONST_qnmAutorunCmdTable,				},
	{	CONST_resId_pcAdapterStatusTable,			(  TCHAR  *  )CONST_pcAdapterStatusTable,			},
	//
	{	-1,		NULL,		},
};


 QY_DMITEM  CONST_cusResTable_netMc2[]  =
{
 	{	CONST_resType_str,						(  TCHAR  *  )CONST_strTable_netMc,						},
	{	CONST_resType_table,					(  TCHAR  *  )CONST_tableTable_netMc2,				},
	{	CONST_resType_dlg,						(  TCHAR  *  )CONST_dlgTable,						},
 	{	CONST_resType_menu,						(  TCHAR  *  )CONST_cusMenusTable_netMc2,			},
	{	CONST_resType_query,					(  TCHAR  *  )CONST_queryTable,						},
	{	CONST_resType_search,					(  TCHAR  *  )CONST_searchTable,					},
	{	CONST_resType_columnInfo,				(  TCHAR  *  )CONST_columnInfoTable,				},
	{	-1,		NULL,		},
};


