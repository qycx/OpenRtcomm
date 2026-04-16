
#include	"stdafx.h"
#include	<tchar.h>
//  #include	"qyCommon.h"
#include	"myresource_main.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_netMc.h"

#ifndef  __WINCE__

 QY_DMITEM  CONST_dlg_qyCfgSystem[]  =
{
	{	IDC_STATIC_systemName,				},
	{	IDC_STATIC_systemId,				},
	{	IDC_STATIC_dbTypeName,				},
	{	IDC_STATIC_ucbDsnless,				},
	{	IDC_STATIC_dbServIp,				},
	{	IDC_STATIC_dbName,					(  TCHAR  *  )CONST_resId_dbNameOrDsnName,			},
	{	IDC_BUTTON_browseDir,						},
	{	IDC_STATIC_uid,						},
	{	IDC_STATIC_pwd,						},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_qyCfgSystems[]  =
{
	{	IDC_ADD,	},
	{	IDC_MODIFY,	},
	{	IDC_DEL,	},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_cfgSystemParams[]  =
{
	{	IDC_STATIC_getCfgInterval,				},	//(  TCHAR  *  )CONST_resId_STATIC_getCfgInterval,	},
	{	IDC_STATIC_queryCfgsInterval,			},
	{	IDC_STATIC_getOpCmdInterval,			},
	{	IDC_STATIC_showPcNetworkPropInterval,	},	//  (  TCHAR  *  )CONST_resId_STATIC_showPcNetworkPropInterval,	},
	{	IDC_STATIC_sndEventLogInterval,			},	//  (  TCHAR  *  )CONST_resId_STATIC_sndEventLogInterval,			},
	{	IDC_STATIC_sndUsrInfoInterval,			},	//  (  TCHAR  *  )CONST_resId_STATIC_sndUsrInfoInterval,			},
	{	IDC_STATIC_sndNetStatInterval,			},	//  (  TCHAR  *  )CONST_resId_STATIC_sndNetStatInterval,			},
	{	IDC_STATIC_showProcessInterval,			},	//  (  TCHAR  *  )CONST_resId_STATIC_showProcessInterval,			},
	{	IDC_STATIC_showModulesInterval,			},
	{	IDC_STATIC_showNetFlowInterval,			},
	{	IDC_STATIC_showWindowsUpdatePolicyInterval,	},
	{	IDC_STATIC_sndPrintersInterval,				},
	{	IDC_STATIC_showPcNetShareInterval,				},
	{	IDC_STATIC_showPcArpInterval,				},
	//
	{	IDC_STATIC_nProcessQmObjQInterval,			},
	{	IDC_STATIC_nRefreshQmObjQLastCommTime,		},
	{	IDC_STATIC_maxLogs,						},	//  (  TCHAR  *  )CONST_resId_STATIC_maxLogs,						},
	{	IDC_STATIC_nMaxConns,					},
	{	IDOK,									},
	{	IDCANCEL,								},	
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cfgSystemParams_is[]  =
{
	{	IDC_STATIC_usIntervalInS_refreshRecentFriends,			},
	{	IDC_STATIC_usIntervalInS_refreshContactList,			},
	{	IDC_STATIC_cliThreads,									},						//  2015/08/23
	{	IDC_STATIC_mgrThreads_cs,								},						//  2015/08/21
	{	IDC_STATIC_mgrThreads_route,							},						//  2015/09/1
	{	IDC_STATIC_mgrThreads_sw,								},						//  2015/09/03
	{	IDOK,													},
	{	IDCANCEL,												},	
	{	-1,		},
};


 //  这里是这样定义的，
 QY_DMITEM  CONST_dlg_qnmCfgRasOptions[]  =
{
	{	IDC_STATIC_floppyCmd,			(  TCHAR  *  )CONST_resId_STATIC_floppyCmd,	},
	{	IDC_STATIC_cdromCmd,			(  TCHAR  *  )CONST_resId_STATIC_cdromCmd,	},
	{	IDC_STATIC_usbCmd,				(  TCHAR  *  )CONST_resId_STATIC_usbCmd,	},
	{	IDC_STATIC_wLanAdapterCmd,		},
	{	IDC_STATIC_rasCmd,				(  TCHAR  *  )CONST_resId_STATIC_rasCmd,	},
	{	IDC_STATIC_ucBlueToothCmd,		},
	{	IDC_STATIC_ucInfraredCmd,		},
	{	IDC_STATIC_uc1394Cmd,			},
	{	IDC_STATIC_ucWpdCmd,			},
	{	IDC_STATIC_ucSdHostAdapterCmd,			},
	{	IDC_STATIC_ucMobileDeviceCmd,			},
	{	IDC_STATIC_ucUsbNetworkCardCmd,			},
	{	IDC_STATIC_autorunCmd,			},
	{	IDC_STATIC_netShareCmd,			},
	{	IDC_STATIC_safeModeCmd,			},
	{	IDC_STATIC_adminCmd,			},
	{	IDC_STATIC_ucHideQwmCmd,		},
	{	IDC_STATIC_sndEventLogCmd,		(  TCHAR  *  )CONST_resId_STATIC_sndEventLogCmd,	},
	{	IDC_STATIC_sndPrinterCmd,		(  TCHAR  *  )CONST_resId_STATIC_sndPrinterCmd,	},
	{	IDC_STATIC_sndNetStatCmd,		(  TCHAR  *  )CONST_resId_STATIC_sndNetStatCmd,	},
	{	IDC_STATIC_sndModuleInfoCmd,	},
	{	IDC_STATIC_sndPcRegistryValCmd,	},

	{	IDC_STATIC_specialPhoneNum,		(  TCHAR  *  )CONST_resId_STATIC_specialPhoneNum,  },
	{	IDC_ADD,						(  TCHAR  *  )CONST_resId_add,						},
	{	IDC_DEL,						(  TCHAR  *  )CONST_resId_del,						},
	{	IDC_CHECK_bNotChkOnInternet,	(  TCHAR  *  )CONST_resId_CHECK_bNotChkOnInternet,	},
	{	IDOK,										},
	{	IDCANCEL,								},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_qnmCfgPcNetworkOptions[]  =
{
	{	IDC_STATIC_bindPcNetworkOptions,				(  TCHAR  *  )CONST_resId_STATIC_bindPcNetworkOptions,	},
	{	IDC_BUTTON_bindPcNetworkOptions,				(  TCHAR  *  )CONST_resId_BUTTON_bindPcNetworkOptions,	},
	{	IDC_STATIC_cancelPcNetworkOptionsBindings,		(  TCHAR  *  )CONST_resId_STATIC_cancelPcNetworkOptionsBindings,		},
	{	IDC_BUTTON_cancelPcNetworkOptionsBindings,		(  TCHAR  *  )CONST_resId_BUTTON_cancelPcNetworkOptionsBindings,		},
	{	IDC_STATIC_cfgWindowsUpdatePolicy,		},
	{	IDC_BUTTON_cfgWindowsUpdatePolicy,		},
	{	IDC_STATIC_netFlow,						},
	{	IDC_STATIC_uiWarnPercent,				},
	{	IDC_STATIC_percentSym,					},
	{	IDC_STATIC_ucWarnedNetworkCardCmd,		},
	{	IDC_STATIC_ucDetectTimesBeforeWarn,		},
	{	IDC_CHECK_ucbPopupToWarn,				},
	{	IDC_STATIC_stopNetworkCardTime,			},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_pcNetworkOptions_sel[]  =
{
	{	IDC_CHECK_pcAdapter,				},
	{	IDC_CHECK_proxy,					},
	{	IDC_CHECK_computer,					},
	{	IDC_CHECK_windowsUpdatePolicy,		},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};



 QY_DMITEM  CONST_dlg_qnmCfgPcMonOptions[]  =		//  2006/03/04
{
	{	IDC_STATIC_GROUP_capScreen,				},
	{	IDC_STATIC_capScreenCmd,				},
	{	IDC_STATIC_staticCapScreenDir,				},
	{	IDC_BUTTON_browseDir,						},
	{	IDC_STATIC_capScreenInterval,			},
	{	IDC_CHECK_ucbSaveAsGif,					},
	{	IDC_STATIC_monPics_row,					},
	{	IDC_STATIC_monPics_col,					},
	//
	//  {	IDC_STATIC_cfgFileMonFilter,				},
	//  {	IDC_STATIC_fileMon,								},
	{	IDC_BUTTON_cfgFileMonFilter,			},
	{	IDC_BUTTON_cfgPcRegistry,				},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_cfgFileMonFilter[]  =
{
	{	IDC_STATIC_filterRules,				},
	{	IDC_CHECK_filterSysDir,				},
	{	IDC_CHECK_filterWinDir,				},
	{	IDC_CHECK_filterWinTmpDir,			},
	{	IDC_CHECK_filterUsrTmpDir,			},
	{	IDC_CHECK_filterRename,				},
	{	IDC_CHECK_filterModify,				},
	{	IDC_ADD,						},
	{	IDC_DEL,						},
	{	IDC_reset,				},
	{	IDOK,												},
	{	IDCANCEL,										},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_addFileMonRule[]  =
{
	{	IDC_STATIC_hint,					(  TCHAR  *  )CONST_resId_hint_addFileMonRule,	},
	{	IDOK,												},
	{	IDCANCEL,										},
	{	-1,			},
};

  QY_DMITEM  CONST_dlg_cfgPcRegistrys[]  =
{
	//  {	IDOK,												},
	//  {	IDCANCEL,										},
	{	IDC_ADD,	},
	{	IDC_MODIFY,	},
	{	IDC_DEL,	},
	{	-1,			},
};

 QY_DMITEM  CONST_dlg_cfgPcRegistry[]  =
{
	{	IDC_STATIC_iRootKey,														},
	{	IDC_STATIC_subKey,															},
	{	IDC_STATIC_cfgName,															},
	{	IDC_STATIC_nIntervals,														},
	{	IDC_CHECK_unsupport98,														},
	{	IDC_CHECK_unsupportMe,														},
	{	IDC_CHECK_unsupport2000,													},
	{	IDC_CHECK_unsupportXp,														},
	{	IDC_CHECK_unsupport2003,													},
	{	IDC_CHECK_ucbNotLogAdd,														},
	{	IDC_CHECK_ucbNotLogDel,														},
	{	IDC_CHECK_ucbNotLogModify,													},
	{	IDC_STATIC_cfgPcRegistryHint,												},
	{	IDOK,											},
	{	IDCANCEL,									},
	{	-1,			},
};



 QY_DMITEM  CONST_dlg_policyImAuthCond[]  =
{
	{	IDC_STATIC_hint,					(  TCHAR  *  )CONST_resId_imAuthCond_hint,	},
	{	IDC_CHECK_ucbUseMac,							},
	{	IDC_CHECK_ucbUsePcName,							},	
	{	IDC_CHECK_ucbUseDomainName,						},
	{	IDC_CHECK_ucbUseOsUsrName,						},
	{	IDC_CHECK_ucbUseMessengerName,					},
	{	IDC_CHECK_ucbAutoVerification,					},
	{	IDC_CHECK_ucbNeedValidIpForDevice,				},
	{	IDC_STATIC_qiShiIP,								},
	{	IDC_STATIC_jieShuIP,							},
	{	IDOK,											},
	{	IDCANCEL,									},
	{	-1,			},
};







 

 QY_DMITEM  CONST_dlg_cfgCustom[]  =
{
	{	IDC_STATIC_nDwLevels,				(  TCHAR  *  )CONST_resId_STATIC_nDwLevels,	},
	{	IDC_STATIC_nZcbhs,					(  TCHAR  *  )CONST_resId_STATIC_nZcbhs,		},
	{	IDC_STATIC_qrtTitle,				(  TCHAR  *  )CONST_resId_STATIC_qrtTitle,	},
	{	IDC_STATIC_hint,					(  TCHAR  *  )CONST_resId_STATIC_hint,		},
	{	IDC_STATIC_clientWelcomeMsg,		(  TCHAR  *  )CONST_resId_STATIC_clientWelcomeMsg,	},				//  2016/08/10
	{	IDOK,												},
	{	IDCANCEL,										},
	{	-1,			},
};

 
 QY_DMITEM  CONST_dlg_cfgStandardName[]  =
{
	{	IDC_STATIC_hint_cfgStandardName,		},
	{	IDC_STATIC_preStandardName,									},
	{	IDC_STATIC_standardName,									},
	{	IDC_CHECK_zb,										},
	{	IDC_CHECK_bb,											},
	{	IDC_CHECK_dw,											},
	{	IDC_CHECK_bm,											},
	{	IDC_CHECK_syr,									},
	{	IDOK,												},
	{	IDCANCEL,										},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cfgStandardNames[]  =
{
	{	IDC_ADD,													},
	{	IDC_MODIFY,												},
	{	IDC_DEL,													},
	{	IDC_BUTTON_cfgStandardNames,									},
	{	-1,		},
};
 

 QY_DMITEM	CONST_dlg_passwdForStopMon[]  =
{
	{	IDC_STATIC_passwdForStopMon,		(  TCHAR  *  )CONST_resId_STATIC_passwdForStopMon,	},
	{	IDOK,												},
	{	IDCANCEL,										},
	{	-1,			},
};

#endif

#ifndef  __WINCE__
 QY_DMITEM  CONST_dlg_qnmCfgOptions[]  =
{
	{	IDC_STATIC_centerAddr,				(  TCHAR  *  )CONST_resId_STATIC_centerIp,		},
	{	IDC_CHECK_cntIp,		},
	{	IDC_STATIC_cntAddr1,	},
	{	IDC_STATIC_cntAddr2,	},	
	{	IDC_STATIC_cntPort,		},
	{	IDC_STATIC_qyRegToolDir,			(  TCHAR  *  )CONST_resId_STATIC_qyRegToolDir,	},
	{	IDC_BUTTON_browseDir,						},
	{	IDOK,													},
	{	IDCANCEL,											},
	{	-1,			},
};

 QY_DMITEM  CONST_dlg_exportClients[] =
{
	{	IDC_RADIO_default,	},
	{	IDC_RADIO_ts_logon,	},
	{	IDC_RADIO_ts_dev,	},
	{	-1,			},

};

#if  0
 QY_DMITEM  CONST_dlg_qnmCfgOptions_isClient[]  =
{
	{	IDC_STATIC_cntName,		},
	{	IDC_STATIC_centerAddr,				(  TCHAR  *  )CONST_resId_STATIC_centerIp,		},
	{	IDC_STATIC_cntAddr0,	},
	{	IDC_STATIC_cntAddr1,	},
	{	IDC_STATIC_cntAddr2,	},
	{	IDC_STATIC_cntPort,		},
	{	IDC_ADD,				},
	{	IDC_MODIFY,				},
	{	IDC_DEL,				},
	{	IDOK,													},
	{	IDCANCEL,											},
	{	-1,			},
};
#endif
#endif


#ifndef  __WINCE__
 QY_DMITEM  CONST_dlg_qnmCfgPcRule[]  =
{
	{	IDC_STATIC_floppyCmd,				(  TCHAR  *  )CONST_resId_STATIC_floppyCmd,		},
	{	IDC_STATIC_cdromCmd,				(  TCHAR  *  )CONST_resId_STATIC_cdromCmd,		},
	{	IDC_STATIC_usbCmd,					(  TCHAR  *  )CONST_resId_STATIC_usbCmd,			},
	{	IDC_STATIC_wLanAdapterCmd,			},
	{	IDC_STATIC_rasCmd,					(  TCHAR  *  )CONST_resId_STATIC_rasCmd,				},
	{	IDC_STATIC_ucBlueToothCmd,			},
	{	IDC_STATIC_ucInfraredCmd,			},
	{	IDC_STATIC_uc1394Cmd,			},	
	{	IDC_STATIC_ucWpdCmd,			},	
	{	IDC_STATIC_ucSdHostAdapterCmd,			},
	{	IDC_STATIC_ucMobileDeviceCmd,			},
	{	IDC_STATIC_ucUsbNetworkCardCmd,			},

	//  {	IDC_STATIC_warnToInternetCmd,		(  TCHAR  *  )CONST_resId_STATIC_warnToInternetCmd,	},
	{	IDC_STATIC_autorunCmd,			},
	{	IDC_STATIC_netShareCmd,			},
	{	IDC_STATIC_safeModeCmd,			},
	{	IDC_STATIC_adminCmd,			},
	{	IDC_STATIC_ucHideQwmCmd,		},
	{	IDC_STATIC_sndEventLogCmd,			(  TCHAR  *  )CONST_resId_STATIC_sndEventLogCmd,		},
	{	IDC_STATIC_sndUsrInfoCmd,			(  TCHAR  *  )CONST_resId_STATIC_sndUsrInfoCmd,		},
	{	IDC_STATIC_sndPrinterCmd,			(  TCHAR  *  )CONST_resId_STATIC_sndPrinterCmd,		},
	{	IDC_STATIC_sndNetStatCmd,			(  TCHAR  *  )CONST_resId_STATIC_sndNetStatCmd,		},
	{	IDC_STATIC_sndModuleInfoCmd,		},
	{	IDC_CHECK_bMonAllDisks,				},
	{	IDC_STATIC_auditDir,				(  TCHAR  *  )CONST_resId_STATIC_auditDir,			},
	{	IDC_STATIC_sndPcRegistryValCmd,		},
	{	IDC_STATIC_capScreenCmd,			},
	{	IDC_STATIC_uiWarnPercent,				},
	{	IDC_STATIC_percentSym,					},
	{	IDC_STATIC_ucWarnedNetworkCardCmd,	},
	{	IDC_STATIC_stopMon,					(  TCHAR  *  )CONST_resId_STATIC_stopMon,			},
	{	IDC_CHECK_unchk,					(  TCHAR  *  )CONST_resId_CHECK_unchk,				},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_qnmEditPcUsrInfo[]  =
{
	{	IDC_hint0,							(  TCHAR  *  )CONST_resId_hint0,				},
	{	IDC_hint1,							(  TCHAR  *  )CONST_resId_hint1,				},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_aboutBox[]  = 
{
	{	IDC_STATIC_ver,						(  TCHAR  *  )CONST_resId_ver,						},
	{	IDC_STATIC_qycxCopyRight,			(  TCHAR  *  )CONST_resId_qycxCopyRight,				},
	{	IDOK,														},
	{	-1,		},

};

 QY_DMITEM  CONST_dlg_cfgUsr[]  = 
{
	{	IDC_STATIC_name,					(  TCHAR  *  )CONST_resId_name,						},
	{	IDC_STATIC_passwd0,								},
	{	IDC_STATIC_passwd1,								},
	{	IDC_STATIC_scope,					},
	{	IDC_STATIC_zb,						},
	{	IDC_STATIC_bb,						},
	{	IDC_STATIC_dw,						},
	{	IDC_STATIC_bm,						},	
	{	IDOK,																					},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cfgUsrs[]  = 
{
	{	IDC_STATIC_minPasswdLen,			},
	{	IDC_STATIC_maxInvalidLogonAttempts,			},
	{	IDC_HINT,							(  TCHAR  *  )CONST_resId_HINT,						},
	{	IDC_ADD,							(  TCHAR  *  )CONST_resId_ADD,						},
	{	IDC_MODIFY,							(  TCHAR  *  )CONST_resId_MODIFY,					},
	{	IDC_DEL,							(  TCHAR  *  )CONST_resId_DEL,						},
	{	IDOK,		},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cfgWarn[]  = 
{
	{	IDC_WARNON,							(  TCHAR  *  )CONST_resId_WARNON,					},
	{	IDC_STATIC_cfgWarn,					(  TCHAR  *  )CONST_resId_STATIC_cfgWarn,			},
	{	IDC_WARNUNTILUSRSTOPIT,				(  TCHAR  *  )CONST_resId_WARNUNTILUSRSTOPIT,		},
	{	IDC_STATIC_maxWarnElapse,			(  TCHAR  *  )CONST_resId_STATIC_maxWarnElapse,		},
	{	IDC_CHECK_popupToWarn,				},
	{	IDC_STATIC_popupToWarnStartTime,	},
	{	IDC_STATIC_popupToWarnStartTimeVal,	},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cleanupEventCond[]  = 
{
	{	IDC_STATIC_condition,							},
	{	IDC_STATIC_startTime,							},
	{	IDC_STATIC_endTime,								},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cusPcSp[]  = 
{
	{	IDC_STATIC_buDing,					(  TCHAR  *  )CONST_resId_STATIC_buDing,				},
	{	IDC_STATIC_bieMing,					(  TCHAR  *  )CONST_resId_STATIC_bieMing,			},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_qnmCfgPcGrp[]  = 
{
	{	IDC_STATIC_qiShiIP,					(  TCHAR  *  )CONST_resId_STATIC_qiShiIP,		},
	{	IDC_STATIC_jieShuIP,				(  TCHAR  *  )CONST_resId_STATIC_jieShuIP,		},
	{	IDC_STATIC_danWei,					(  TCHAR  *  )CONST_resId_STATIC_danWei,		},
	{	IDC_STATIC_buMen,					(  TCHAR  *  )CONST_resId_STATIC_buMen,		},
	{	IDC_STATIC_scanedObj,				(  TCHAR  *  )CONST_resId_STATIC_scanedObj,		},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_pcProperties[]  =
{

	{	IDC_pc0_zongBu,		(  TCHAR  *  )CONST_resId_pc0_zongBu,		},
	{	IDC_pc2_benBu,		(  TCHAR  *  )CONST_resId_pc2_benBu,		},
	{	IDC_pc4_danWei,		(  TCHAR  *  )CONST_resId_pc4_danWei,		},
	{	IDC_pc6_qiTaDanWei,		(  TCHAR  *  )CONST_resId_pc6_qiTaDanWei,		},
	{	IDC_pc8_buMen,		(  TCHAR  *  )CONST_resId_pc8_buMen,		},
	{	IDC_pc10_shiYongRen,		(  TCHAR  *  )CONST_resId_pc10_shiYongRen,		},
	{	IDC_pc12_jiQiLeiXing,		(  TCHAR  *  )CONST_resId_pc12_jiQiLeiXing,		},
	{	IDC_pc14_ziChanBianHao,		(  TCHAR  *  )CONST_resId_pc14_ziChanBianHao,		},
	{	IDC_pc16_zhuYaoYongTu,		(  TCHAR  *  )CONST_resId_pc16_zhuYaoYongTu,		},
	{	IDC_pc18_lianXiDianHua,		(  TCHAR  *  )CONST_resId_pc18_lianXiDianHua,		},
	{	IDC_pc20_shiYongDiDian,		(  TCHAR  *  )CONST_resId_pc20_shiYongDiDian,		},
	{	IDC_pc22_shiYongDiDian,		(  TCHAR  *  )CONST_resId_pc22_shiYongDiDian,		},
	{	IDC_pc24_ziChanBianHao1,		(  TCHAR  *  )CONST_resId_pc24_ziChanBianHao1,		},
	{	IDC_pc26_ziChanShuoMing1,		(  TCHAR  *  )CONST_resId_pc26_ziChanShuoMing1,		},
	{	IDC_pc28_ziChanBianHao2,		(  TCHAR  *  )CONST_resId_pc28_ziChanBianHao2,		},
	{	IDC_pc30_ziChanShuoMing2,		(  TCHAR  *  )CONST_resId_pc30_ziChanShuoMing2,		},
	//	 
	{	IDC_STATIC_usrInfoZone,				(  TCHAR  *  )CONST_resId_STATIC_usrInfoZone,		},
	{	IDC_STATIC_pcName,					(  TCHAR  *  )CONST_resId_STATIC_pcName,		},
	{	IDC_STATIC_ip,						(  TCHAR  *  )CONST_resId_STATIC_ip,		},
	{	IDC_STATIC_osName,					(  TCHAR  *  )CONST_resId_STATIC_osName,		},
	{	IDC_STATIC_servicePack,				(  TCHAR  *  )CONST_resId_STATIC_servicePack,		},
	{	IDC_STATIC_mac0,					(  TCHAR  *  )CONST_resId_STATIC_mac0,		},
	{	IDC_STATIC_mac1,					(  TCHAR  *  )CONST_resId_STATIC_mac1,		},
	{	IDC_STATIC_mac2,					(  TCHAR  *  )CONST_resId_STATIC_mac2,		},
	{	IDC_STATIC_ip0,						(  TCHAR  *  )CONST_resId_STATIC_ip0,		},
	{	IDC_STATIC_ip1,						(  TCHAR  *  )CONST_resId_STATIC_ip1,		},
	{	IDC_STATIC_ip2,						(  TCHAR  *  )CONST_resId_STATIC_ip2,		},
	//
	{	IDC_STATIC_qwmVer,					(  TCHAR  *  )CONST_resId_STATIC_qwmVer,		},
	{	IDC_STATIC_regTime,					(  TCHAR  *  )CONST_resId_STATIC_regTime,		},
	{	IDC_STATIC_auditTime,				(  TCHAR  *  )CONST_resId_STATIC_auditTime,		},
	{	IDC_STATIC_startTime,				(  TCHAR  *  )CONST_resId_STATIC_clientStartTime,		},
	{	IDC_STATIC_lastCommTime,			(  TCHAR  *  )CONST_resId_STATIC_lastCommTime,		},
	//
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};



 //  2007/07/30
 QY_DMITEM  CONST_dlg_messengerProperties[]  =
{

	{	IDC_pc0_zongBu,		(  TCHAR  *  )CONST_resId_pc0_zongBu,		},
	{	IDC_pc2_benBu,		(  TCHAR  *  )CONST_resId_pc2_benBu,		},
	{	IDC_pc4_danWei,		(  TCHAR  *  )CONST_resId_pc4_danWei,		},
	{	IDC_pc6_qiTaDanWei,		(  TCHAR  *  )CONST_resId_pc6_qiTaDanWei,		},
	{	IDC_pc8_buMen,		(  TCHAR  *  )CONST_resId_pc8_buMen,		},
	{	IDC_pc10_shiYongRen,		(  TCHAR  *  )CONST_resId_pc10_shiYongRen,		},
	{	IDC_pc12_jiQiLeiXing,		(  TCHAR  *  )CONST_resId_pc12_jiQiLeiXing,		},
	{	IDC_pc14_ziChanBianHao,		(  TCHAR  *  )CONST_resId_pc14_ziChanBianHao,		},
	{	IDC_pc16_zhuYaoYongTu,		(  TCHAR  *  )CONST_resId_pc16_zhuYaoYongTu,		},
	{	IDC_pc18_lianXiDianHua,		(  TCHAR  *  )CONST_resId_pc18_lianXiDianHua,		},
	{	IDC_pc20_shiYongDiDian,		(  TCHAR  *  )CONST_resId_pc20_shiYongDiDian,		},
	{	IDC_pc22_shiYongDiDian,		(  TCHAR  *  )CONST_resId_pc22_shiYongDiDian,		},
	{	IDC_pc24_ziChanBianHao1,		(  TCHAR  *  )CONST_resId_pc24_ziChanBianHao1,		},
	{	IDC_pc26_ziChanShuoMing1,		(  TCHAR  *  )CONST_resId_pc26_ziChanShuoMing1,		},
	{	IDC_pc28_ziChanBianHao2,		(  TCHAR  *  )CONST_resId_pc28_ziChanBianHao2,		},
	{	IDC_pc30_ziChanShuoMing2,		(  TCHAR  *  )CONST_resId_pc30_ziChanShuoMing2,		},
	//	 
	{	IDC_STATIC_staticMessengerId,	},
	//  {	IDC_STATIC_usrInfoZone,				(  TCHAR  *  )CONST_resId_STATIC_usrInfoZone,		},
	//  {	IDC_STATIC_pcName,					(  TCHAR  *  )CONST_resId_STATIC_pcName,		},
	//  {	IDC_STATIC_ip,						(  TCHAR  *  )CONST_resId_STATIC_ip,		},
	//  {	IDC_STATIC_osName,					(  TCHAR  *  )CONST_resId_STATIC_osName,		},
	//  {	IDC_STATIC_servicePack,				(  TCHAR  *  )CONST_resId_STATIC_servicePack,		},
	//  {	IDC_STATIC_mac0,					(  TCHAR  *  )CONST_resId_STATIC_mac0,		},
	//  {	IDC_STATIC_mac1,					(  TCHAR  *  )CONST_resId_STATIC_mac1,		},
	//  {	IDC_STATIC_mac2,					(  TCHAR  *  )CONST_resId_STATIC_mac2,		},
	//  {	IDC_STATIC_ip0,						(  TCHAR  *  )CONST_resId_STATIC_ip0,		},
	//  {	IDC_STATIC_ip1,						(  TCHAR  *  )CONST_resId_STATIC_ip1,		},
	//  {	IDC_STATIC_ip2,						(  TCHAR  *  )CONST_resId_STATIC_ip2,		},
	//
	//  {	IDC_STATIC_qwmVer,					(  TCHAR  *  )CONST_resId_STATIC_qwmVer,		},
	//  {	IDC_STATIC_regTime,					(  TCHAR  *  )CONST_resId_STATIC_regTime,		},
	//  {	IDC_STATIC_auditTime,				(  TCHAR  *  )CONST_resId_STATIC_auditTime,		},
	//  {	IDC_STATIC_startTime,				(  TCHAR  *  )CONST_resId_STATIC_clientStartTime,		},
	//  {	IDC_STATIC_lastCommTime,			(  TCHAR  *  )CONST_resId_STATIC_lastCommTime,		},
	//
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 
  QY_DMITEM  CONST_dlg_imGrpProperties[]  =
{
	{	IDC_STATIC_staticName,							},
	{	IDC_STATIC_staticMessengerId,							},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},

};


 QY_DMITEM  CONST_dlg_imGrp[]  =
{
	{	IDC_STATIC_staticName,							},
	{	IDC_STATIC_subtype,							},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},

};

 QY_DMITEM  CONST_dlg_policy_isMgr[]  =
{
	{	IDC_CHECK_ucbLogImMsg,		},
	{	IDC_STATIC_hintForMcu,},
	{	IDC_STATIC_startMcuId,	},
	{	IDC_STATIC_cntofMcus,	},
	{	IDC_STATIC_hintForMcuUsr,	},
	{	IDC_STATIC_mcuUsrName,	},
	{	IDC_STATIC_mcuPasswd,	},
	{	IDC_STATIC_mcuDomainName,	},

	{	IDC_STATIC_offlineResServDir,	},
	{	IDC_CHECK_bUseManuallySetResServId,	},

	{	IDC_STATIC_hintForTmpMessengerId,	},
	{	IDC_STATIC_startTmpMessengerId,	},
	{	IDC_STATIC_endTmpMessengerId,	},
	//{	IDC_STATIC_offlineResServID,	},
	{	IDC_STATIC_usTimeoutInMsToSwitch,	},
	{	IDC_STATIC_usMaxMsgs_allowedToSwitchToTalkChannel_robot,	},
	{	IDC_STATIC_usMaxMsgs_allowedToSwitchToTalkChannel_media,	},
	//
	{	IDC_CHECK_ucbUseDynBmpRule,	},
	{	IDC_CHECK_notUseP2pCall,	},
	//
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cfgCustomerService[]  =
{
	{	IDC_STATIC_lang,	},
	{	IDC_STATIC_category,	},
	{	IDC_STATIC_startIp,	},
	{	IDC_STATIC_endIp,	},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

   #endif

 QY_DMITEM  CONST_dlg_msgList[]  =
{
	{	IDC_BUTTON_export,		},
	{	IDC_BUTTON_clear,		},
	{	IDCANCEL,				},
	{	-1,						},

};

 QY_DMITEM  CONST_dlg_objs[]  =
{
	{	IDOK,					},
	{	IDCANCEL,				},
	{	-1,				},
};


#ifndef  __WINCE__

 QY_DMITEM  CONST_dlg_imTaskProperties[]  =
{
	{	IDC_STATIC_staticType,								},
	{	IDC_STATIC_staticImTaskStatus,						},
	{	IDC_STATIC_staticSender,	},
	{	IDC_STATIC_staticReceiver,	},
	{	IDC_STATIC_staticSendTime,	},
	{	IDC_STATIC_staticRecvTime,	},
	{	IDC_STATIC_staticSubject,	},
	{	IDC_STATIC_staticContent,	},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_imMsgProperties[]  =
{
	{	IDC_STATIC_staticType,								},
	{	IDC_STATIC_staticSender,	},
	{	IDC_STATIC_staticReceiver,	},
	{	IDC_STATIC_staticSendTime,	},
	{	IDC_STATIC_staticRecvTime,	},
	{	IDC_STATIC_staticContent,	},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};



 QY_DMITEM  CONST_dlg_qyExport[]  = 
{
	{	IDC_RADIO_exportCurQuery,			(  TCHAR  *  )CONST_resId_RADIO_exportCurQuery,		},
	{	IDC_RADIO_exportBakData,			(  TCHAR  *  )CONST_resId_RADIO_exportBakData,		},
	{	IDC_RADIO_exportCfg,				(  TCHAR  *  )CONST_resId_RADIO_exportCfg,		},
	{	IDC_STATIC_hint,					(  TCHAR  *  )CONST_resId_STATIC_exportHint,		},
	{	IDC_RADIO_exportBhbCfg,				(  TCHAR  *  )CONST_resId_RADIO_exportBhbCfg,		},
	{	IDC_RADIO_exportRegInfo,			(  TCHAR  *  )CONST_resId_RADIO_exportRegInfo,		},
	{	IDC_RADIO_procDj,					(  TCHAR  *  )CONST_resId_RADIO_procDj,		},
	{	IDC_RADIO_procModuleKnowlege,		},
	{	IDC_RADIO_procRegistryKnowlege,		},
	{	IDC_RADIO_procIpKnowledge,			},
	{	IDC_RADIO_procPhoneGuest,			},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_qnmClearup[]  = 
{
	{	IDD_qnmClearup,					 	(  TCHAR  *  )CONST_resId_IDD_qnmClearup,		},
	{	IDC_STATIC_clearHint, 				(  TCHAR  *  )CONST_resId_STATIC_clearHint,		},
	{	IDC_RADIO_clearupScannedIp, 	 	(  TCHAR  *  )CONST_resId_RADIO_clearupScannedIp,		},
	{	IDC_RADIO_clearupEvent, 	 		(  TCHAR  *  )CONST_resId_RADIO_clearupEvent,		},
	{	IDC_RADIO_procModuleKnowlege,	},
	{	IDC_RADIO_procRegistryKnowlege,		},
	{	IDC_RADIO_procImMsg,				},
	{	IDC_RADIO_procImHisTask,				},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

  QY_DMITEM  CONST_dlg_pcAssetProperties[]  = 
{
	{	IDC_STATIC_staticDw,				(  TCHAR  *  )CONST_resId_STATIC_staticDw,		},
	{	IDC_STATIC_staticBm,				(  TCHAR  *  )CONST_resId_STATIC_staticBm,		},
	{	IDC_STATIC_staticSyr,				(  TCHAR  *  )CONST_resId_STATIC_staticSyr,		},
	{	IDC_STATIC_staticIp,				(  TCHAR  *  )CONST_resId_STATIC_staticIp,		},
	{	IDC_STATIC_staticMac0,				(  TCHAR  *  )CONST_resId_STATIC_staticMac0,		},
	{	IDC_STATIC_osName,					(  TCHAR  *  )CONST_resId_STATIC_osName,		},
	{	IDC_STATIC_staticAssetType,			(  TCHAR  *  )CONST_resId_STATIC_staticAssetType,		},
	{	IDC_STATIC_staticName,						},
	{	IDC_STATIC_staticDes0,				(  TCHAR  *  )CONST_resId_STATIC_staticDes0,		},
	{	IDC_STATIC_staticStartTime,			(  TCHAR  *  )CONST_resId_STATIC_staticStartTime,		},
	{	IDC_STATIC_staticEndTime,			(  TCHAR  *  )CONST_resId_STATIC_staticEndTime,		},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};



  QY_DMITEM  CONST_dlg_qnmSearch[]  = 
{
	{	IDC_STATIC_queryType,				(  TCHAR  *  )CONST_resId_STATIC_queryType,			},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};


  QY_DMITEM  CONST_dlg_qnmEventSearch[]  =
{
	{	IDC_STATIC_hint,			},	//  CONS"请输入查询条件:",
	{	IDC_STATIC_startTime,		},	//	"起始时间:"
	{	IDC_STATIC_endTime,			},	//  "截止时间:"
	{	IDC_STATIC_eventType,		},	//  "事件类型:"

	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},

};

  QY_DMITEM  CONST_dlg_qnmPcAssetListSearch[]  =
{
	{	IDC_CHECK_onlyLast,					},
	{	IDC_STATIC_staticDw,				(  TCHAR  *  )CONST_resId_STATIC_staticDw,		},
	{	IDC_STATIC_staticBm,				(  TCHAR  *  )CONST_resId_STATIC_staticBm,		},
	{	IDC_STATIC_staticSyr,				(  TCHAR  *  )CONST_resId_STATIC_staticSyr,		},
	{	IDC_STATIC_pcName,					(  TCHAR  *  )CONST_resId_STATIC_pcName,	},
	{	IDC_STATIC_staticIp,				(  TCHAR  *  )CONST_resId_STATIC_staticIp,		},
	{	IDC_STATIC_staticDes0,				(  TCHAR  *  )CONST_resId_STATIC_staticDes0,		},
	{	IDC_STATIC_deviceType,				},
	{	IDC_STATIC_keySearch,				},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_qnmPcListSearch[]  =
{	
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_qnmPcSpListSearch[]  =
{

	{	IDC_STATIC_osName,					(  TCHAR  *  )CONST_resId_STATIC_osName,		},
	{	IDC_STATIC_buDing,					(  TCHAR  *  )CONST_resId_STATIC_buDing,		},
	{	IDC_STATIC_bieMing,					(  TCHAR  *  )CONST_resId_STATIC_bieMing,		},		
	{	IDOK,													},
	{	IDCANCEL,											},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_qnmCfgPcGrps[]  =
{	
	{	IDC_ADD,							(  TCHAR  *  )CONST_resId_qnmCfgPcGrps_ADD,		},
	{	IDC_MODIFY,							(  TCHAR  *  )CONST_resId_qnmCfgPcGrps_MODIFY,		},
	{	IDC_DEL,							(  TCHAR  *  )CONST_resId_qnmCfgPcGrps_DEL,		},
	{	IDC_CHECK_bNotAllAllowed,			},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_qnmCfgAdvancedOptions[]  =
{	
	{	IDC_STATIC_dbTypeName,				},
	{	IDC_STATIC_dbServName,				},
	{	IDC_RADIO_useWinAuth,				},				//  2014/02/07
	{	IDC_RADIO_useSqlAuth,				},				//  2014/02/07
	{	IDC_STATIC_uid,						},
	{	IDC_STATIC_pwd,						},
	{	IDC_STATIC_dbName					},
	{	IDC_CHECK_default,					},
	{	IDOK,								},
	{	IDCANCEL,							},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_prop_pcNetwork[]  =
{
	{	IDC_RADIO_ucbDhcpEnabled,			},
	{	IDC_RADIO_staticIp,					},
	{	IDC_STATIC_staticDevIp,				},
	{	IDC_STATIC_staticIpMask,			},		//			_T(  "子网掩码:"  ),		},
	{	IDC_STATIC_staticGateway,			},		//		_T(  "默认网关:"  ),		},
	{	IDC_RADIO_autoDns,					},		//	_T(  "自动获得DNS服务器地址"  ),		},
	{	IDC_RADIO_staticDns,				},		//	_T(  "使用下面的DNS服务器地址"  ),		},
	{	IDC_STATIC_staticFirstDns,			},		//  _T(  "首选DNS服务器:"  ),		},
	{	IDC_STATIC_pcNetworkPropType,		},		//	_T(  "网络连接"  ),		},
	{	IDC_STATIC_staticSecondaryDns,		},		//	_T(  "备用DNS服务器:"  ),		},
	{	IDC_STATIC_staticDw,				(  TCHAR  *  )CONST_resId_STATIC_staticDw,		},
	{	IDC_STATIC_staticBm,				(  TCHAR  *  )CONST_resId_STATIC_staticBm,		},
	{	IDC_STATIC_staticSyr,				(  TCHAR  *  )CONST_resId_STATIC_staticSyr,		},
	{	IDC_STATIC_staticIp,				(  TCHAR  *  )CONST_resId_STATIC_staticIp,		},
	{	IDC_STATIC_staticType,				(  TCHAR  *  )CONST_resId_STATIC_staticType,	},
	{	IDC_STATIC_staticDes0,				(  TCHAR  *  )CONST_resId_STATIC_staticDes0,	},
	{	IDC_STATIC_staticName,					},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_qnmCfgPcNetworkRule[]  =
{
	{	IDC_RADIO_ucbDhcpEnabled,			},
	{	IDC_RADIO_staticIp,					},
	{	IDC_STATIC_staticDevIp,				},
	{	IDC_STATIC_staticIpMask,			},		//			_T(  "子网掩码:"  ),		},
	{	IDC_STATIC_staticGateway,			},		//		_T(  "默认网关:"  ),		},
	{	IDC_RADIO_autoDns,					},		//	_T(  "自动获得DNS服务器地址"  ),		},
	{	IDC_RADIO_staticDns,				},		//	_T(  "使用下面的DNS服务器地址"  ),		},
	{	IDC_STATIC_staticFirstDns,			},		//  _T(  "首选DNS服务器:"  ),		},
	{	IDC_STATIC_pcNetworkPropType,		},		//	_T(  "网络连接"  ),		},
	{	IDC_STATIC_staticSecondaryDns,		},		//	_T(  "备用DNS服务器:"  ),		},
	{	IDC_STATIC_staticDw,				(  TCHAR  *  )CONST_resId_STATIC_staticDw,		},
	{	IDC_STATIC_staticBm,				(  TCHAR  *  )CONST_resId_STATIC_staticBm,		},
	{	IDC_STATIC_staticSyr,				(  TCHAR  *  )CONST_resId_STATIC_staticSyr,		},
	{	IDC_STATIC_staticIp,				(  TCHAR  *  )CONST_resId_STATIC_staticIp,		},
	{	IDC_STATIC_staticType,				(  TCHAR  *  )CONST_resId_STATIC_staticType,	},
	{	IDC_STATIC_staticDes0,				(  TCHAR  *  )CONST_resId_STATIC_staticDes0,	},
	{	IDC_STATIC_staticName,					},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_prop_pcProxyCfg[]  =
{
	{	IDC_STATIC_staticDw,				(  TCHAR  *  )CONST_resId_STATIC_staticDw,		},
	{	IDC_STATIC_staticBm,				(  TCHAR  *  )CONST_resId_STATIC_staticBm,		},
	{	IDC_STATIC_staticSyr,				(  TCHAR  *  )CONST_resId_STATIC_staticSyr,		},
	{	IDC_STATIC_staticIp,				(  TCHAR  *  )CONST_resId_STATIC_staticIp,		},
	{	IDC_STATIC_staticType,				(  TCHAR  *  )CONST_resId_STATIC_staticType,	},
	{	IDC_STATIC_dialSetting,				(  TCHAR  *  )CONST_resId_STATIC_dialSetting,	},
	{	IDC_RADIO_ucbEnableAutodial,		(  TCHAR  *  )CONST_resId_RADIO_ucbEnableAutodial,	},
	{	IDC_RADIO_ucbNoNetAutodial,			(  TCHAR  *  )CONST_resId_RADIO_ucbNoNetAutodial,	},
	{	IDC_RADIO_defaultDial,				(  TCHAR  *  )CONST_resId_RADIO_defaultDial,		},
	{	IDC_STATIC_lanSetting,				(  TCHAR  *  )CONST_resId_STATIC_lanSetting,		},
	{	IDC_CHECK_autoDetect,				(  TCHAR  *  )CONST_resId_CHECK_autoDetect,			},
	{	IDC_CHECK_autoConfigUrl,				},
	{	IDC_STATIC_autoConfigUrl,				},
	{	IDC_CHECK_enableProxy,				(  TCHAR  *  )CONST_resId_CHECK_enableProxy,		},
	{	IDC_STATIC_staticIpAddress,			(  TCHAR  *  )CONST_resId_STATIC_staticIpAddress,	},
	{	IDC_STATIC_staticPort,				(  TCHAR  *  )CONST_resId_STATIC_staticPort,		},
	{	IDC_CHECK_proxyOverride,			(  TCHAR  *  )CONST_resId_CHECK_proxyOverride,		},
	{	IDOK,														},
	{	IDCANCEL,												},

	{	-1,		},

 };

 QY_DMITEM  CONST_dlg_qnmCfgPcProxyCfg[]  =
{	
	{	IDC_STATIC_staticDw,					(  TCHAR  *  )CONST_resId_STATIC_staticDw,			},	//  (  TCHAR  *  )_T(  "单位:"  ),								},
	{	IDC_STATIC_staticBm,					(  TCHAR  *  )CONST_resId_STATIC_staticBm,			},
	{	IDC_STATIC_staticSyr,					(  TCHAR  *  )CONST_resId_STATIC_staticSyr,			},	//  _T(  "使用人:"  ),								},
	{	IDC_STATIC_staticIp,					(  TCHAR  *  )CONST_resId_STATIC_staticIp,			},	//  _T(  "IP:"  ),									},
	{	IDC_STATIC_staticType,					(  TCHAR  *  )CONST_resId_STATIC_staticType,		},	//  _T(  "类型:"  ),								},
	{	IDC_STATIC_dialSetting,					(  TCHAR  *  )CONST_resId_STATIC_dialSetting,		},	//  _T(  "拨号和虚拟专用网络设置"  ),				},
	{	IDC_RADIO_ucbEnableAutodial,			(  TCHAR  *  )CONST_resId_RADIO_ucbEnableAutodial,	},	//  _T(  "从不进行拨号连接"  ),					},
	{	IDC_RADIO_ucbNoNetAutodial,				(  TCHAR  *  )CONST_resId_RADIO_ucbNoNetAutodial,	},	//  _T(  "不论网络连接是否存在都进行拨号"  ),		},
	{	IDC_RADIO_defaultDial,					(  TCHAR  *  )CONST_resId_RADIO_defaultDial,		},	//  _T(  "始终拨默认连接"  ),						},
	{	IDC_STATIC_lanSetting,					(  TCHAR  *  )CONST_resId_STATIC_lanSetting,		},	//  _T(  "局域网(LAN)设置"  ),						},
	{	IDC_CHECK_autoDetect,					(  TCHAR  *  )CONST_resId_CHECK_autoDetect,			},	//  _T(  "自动检测设置(自动设置会覆盖手工设置)"	),			},
	{	IDC_CHECK_autoConfigUrl,				},
	{	IDC_STATIC_autoConfigUrl,				},
	{	IDC_CHECK_enableProxy,					(  TCHAR  *  )CONST_resId_CHECK_enableProxy,		},	//  _T(  "为LAN使用代理服务器"  ),					},
	{	IDC_STATIC_staticIpAddress,				(  TCHAR  *  )CONST_resId_STATIC_staticIpAddress,	},	//  _T(  "地址:"  ),								},
	{	IDC_STATIC_staticPort,					(  TCHAR  *  )CONST_resId_STATIC_staticPort,		},	//  _T(  "端口:"  ),								},
	{	IDC_CHECK_proxyOverride,				(  TCHAR  *  )CONST_resId_CHECK_proxyOverride,		},	//  _T(  "对本地地址不使用代理服务器"  ),			},
	{	IDOK,															},
	{	IDCANCEL,													},
	{	-1,		},
}; 

#if  0
 QY_DMITEM  CONST_dlg_prop_pcComputer[]  =
{	
	{	IDC_STATIC_staticDw,					(  TCHAR  *  )CONST_resId_STATIC_staticDw,			},	//  (  TCHAR  *  )_T(  "单位:"  ),								},
	{	IDC_STATIC_staticBm,					(  TCHAR  *  )CONST_resId_STATIC_staticBm,			},
	{	IDC_STATIC_staticSyr,					(  TCHAR  *  )CONST_resId_STATIC_staticSyr,			},	//  _T(  "使用人:"  ),								},
	{	IDC_STATIC_staticIp,					(  TCHAR  *  )CONST_resId_STATIC_staticIp,			},	//  _T(  "IP:"  ),									},
	{	IDC_STATIC_staticType,					(  TCHAR  *  )CONST_resId_STATIC_staticType,		},	//  _T(  "类型:"  ),								},
	{	IDC_STATIC_hint_activeComputerName,		},		//  _T(  "当前计算机名:"  ),		},
	{	IDC_STATIC_newPcName,					},		//  _T(  "将用计算机名:"  ),		},
	{	IDC_CHECK_ucbAutoRestartIfChanged,		},		//  _T(  "修改计算机名后是否自动重起"  ),		},
	{	IDOK,															},
	{	IDCANCEL,													},
	{	-1,		},
}; 

 QY_DMITEM  CONST_dlg_qnmCfgPcComputer[]  =
{	
	{	IDC_STATIC_leiXing,					(  TCHAR  *  )CONST_resId_STATIC_leiXing,				},	//  _T(  "类型"  ),		},
	{	IDC_STATIC_jiSuanJiMing,			(  TCHAR  *  )CONST_resId_STATIC_jiSuanJiMing			},	//  _T(  "计算机名"  ),		},
	{	IDC_STATIC_zhuYi,					(  TCHAR  *  )CONST_resId_STATIC_zhuYi					},	//  _T(  "注：只用来修改工作组中的计算机名"  ),		},
	{	IDC_CHECK_ucbAutoRestartIfChanged,	(  TCHAR  *  )CONST_resId_CHECK_ucbAutoRestartIfChanged	},	//  _T(  "修改后立即重起"  ),		},
	{	IDOK,															},
	{	IDCANCEL,													},
	{	-1,		},
};
#endif

 QY_DMITEM  CONST_dlg_prop_windowsUpdatePolicy[]  =
{
	{	IDC_STATIC_group_autoUpdate,			},
	{	IDC_STATIC_autoUpdate,		},
	{	IDC_STATIC_staticAUOptions_autoUpdate,	},
	{	IDC_STATIC_staticScheduledInstallDay_autoUpdate,	},
	{	IDC_STATIC_staticScheduledInstallTime_autoUpdate,	},
	//
	{	IDC_RADIO_ucbWSusPolicyExists,			},
	{	IDC_STATIC_wsus,						},
	{	IDC_STATIC_staticNoAutoUpdate,			},
	{	IDC_STATIC_staticAUOptions,	},
	{	IDC_STATIC_staticScheduledInstallDay,	},
	{	IDC_STATIC_staticScheduledInstallTime,	},
	{	IDC_STATIC_staticUseWUServer,			},
	{	IDC_STATIC_staticWUServer,				},
	{	IDC_STATIC_staticWUStatusServer,		},
	{	IDC_STATIC_staticRescheduleWaitTime,	},
	{	IDC_STATIC_staticRescheduleWaitTimeEnabled,		},
	{	IDC_STATIC_staticDetectionFrequencyEnabled,		},
	{	IDC_STATIC_staticDetectionFrequency,		},
	{	IDC_STATIC_staticNoAutoRebootWithLoggedOnUsers,		},
	{	IDC_STATIC_staticElevateNonAdmins,					},
	{	IDC_STATIC_staticTargetGroupEnabled,				},
	{	IDC_STATIC_staticTargetGroup,						},
	//
	{	IDOK,															},
	{	IDCANCEL,													},
	{	-1,		},
 };


 QY_DMITEM  CONST_dlg_qnmCfgWindowsUpdatePolicy[]  =
{
	{	IDC_STATIC_staticType,								(  TCHAR  *  )CONST_resId_STATIC_staticType,			},
	//
	{	IDC_STATIC_group_autoUpdate,																				},
	{	IDC_STATIC_autoUpdate,																						},
	{	IDC_STATIC_staticAUOptions_autoUpdate,	},
	{	IDC_STATIC_staticScheduledInstallDay_autoUpdate,	},
	{	IDC_STATIC_staticScheduledInstallTime_autoUpdate,	},
	//	
	{	IDC_RADIO_ucbWSusPolicyExists,			},
	{	IDC_BUTTON_import,									(  TCHAR  *  )CONST_resId_importWSusTmpl,	},
	{	IDC_STATIC_wsus,															},
	{	IDC_CHECK_staticNoAutoUpdate,						(  TCHAR  *  )IDC_STATIC_staticNoAutoUpdate,			},
	{	IDC_CHECK_staticAUOptions,							(  TCHAR  *  )IDC_STATIC_staticAUOptions,		},
	{	IDC_CHECK_staticScheduledInstallDay,				(  TCHAR  *  )IDC_STATIC_staticScheduledInstallDay,	},
	{	IDC_CHECK_staticScheduledInstallTime,				(  TCHAR  *  )IDC_STATIC_staticScheduledInstallTime,	},
	{	IDC_CHECK_staticUseWUServer,						(  TCHAR  *  )IDC_STATIC_staticUseWUServer,			},
	{	IDC_STATIC_staticWUServer,																				},
	{	IDC_STATIC_staticWUStatusServer,																		},
	{	IDC_CHECK_staticRescheduleWaitTime,					(  TCHAR  *  )IDC_STATIC_staticRescheduleWaitTime,	},
	{	IDC_CHECK_staticRescheduleWaitTimeEnabled,			(  TCHAR  *  )IDC_STATIC_staticRescheduleWaitTimeEnabled,		},
	{	IDC_CHECK_staticDetectionFrequencyEnabled,			(  TCHAR  *  )IDC_STATIC_staticDetectionFrequencyEnabled,				},
	{	IDC_CHECK_staticDetectionFrequency,					(  TCHAR  *  )IDC_STATIC_staticDetectionFrequency,					},
	{	IDC_CHECK_staticNoAutoRebootWithLoggedOnUsers,		(  TCHAR  *  )IDC_STATIC_staticNoAutoRebootWithLoggedOnUsers,		},
	{	IDC_CHECK_staticElevateNonAdmins,					(  TCHAR  *  )IDC_STATIC_staticElevateNonAdmins,				},
	{	IDC_CHECK_staticTargetGroupEnabled,					(  TCHAR  *  )IDC_STATIC_staticTargetGroupEnabled,			},
	{	IDC_STATIC_staticTargetGroup,																				},
	//
	{	IDOK,															},
	{	IDCANCEL,													},
	{	IDC_BUTTON_DEL,		},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_qnmCfgIpScan[]  =
{	
	{	IDC_MODIFY,							},		//  (  TCHAR  *  )_T(  "修改"  ),		},
	{	IDC_ADD,							},		//  (  TCHAR  *  )_T(  "新增"  ),		},
	{	IDC_DEL,							(  TCHAR  *  )CONST_resId_DEL,		},
	{	IDOK,															},
	{	IDCANCEL,													},
	{	-1,		},
};
 
 QY_DMITEM  CONST_dlg_qnmCfgIpGrp[]  =
{	
	{	IDC_STATIC_qiShiIP,					(  TCHAR  *  )CONST_resId_STATIC_qiShiIP,		},
	{	IDC_STATIC_jieShuIP,				(  TCHAR  *  )CONST_resId_STATIC_jieShuIP,		},
	{	IDC_STATIC_danWei,					(  TCHAR  *  )CONST_resId_STATIC_danWei,		},
	{	IDC_STATIC_buMen,					(  TCHAR  *  )CONST_resId_STATIC_buMen,		},
	{	IDOK,															},
	{	IDCANCEL,													},
	{	-1,		},
};
 
 QY_DMITEM  CONST_dlg_qnmCfgUnchk[]  =
{	

	{	IDC_STATIC_unchkedHint,				},		//  _T(  "下面列表中的IP, 将被免于注册检查。"  ),		},
	{	IDC_STATIC_unchkedIp,				},		//  _T(  "永久性免检:"  ),		},
	{	IDC_STATIC_tmpUnchkedIp,			},		//  _T(  "临时免检 2 天:"  ),		},
	{	IDC_ADD,							(  TCHAR  *  )CONST_resId_ADD,		},		//  (  TCHAR  *  )_T(  "新增"  ),		},
	{	IDC_DEL,							(  TCHAR  *  )CONST_resId_DEL,		},
	{	IDOK,															},
	{	IDCANCEL,													},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_qnmCfgUnchkedIpGrp[]  =
{	
	{	IDC_STATIC_qiShiIP,					(  TCHAR  *  )CONST_resId_STATIC_qiShiIP,		},
	{	IDC_STATIC_jieShuIP,				(  TCHAR  *  )CONST_resId_STATIC_jieShuIP,		},
	{	IDC_STATIC_staticType,				(  TCHAR  *  )CONST_resId_STATIC_staticType,	},
	{	IDOK,															},
	{	IDCANCEL,													},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cfgSkippedMacs[]  =
 {
	 {	IDC_STATIC_hint,					(  TCHAR  *  )CONST_resId_skippedMacsHint,	},
	 {	IDC_STATIC_mac0,		},
	 {	IDC_STATIC_mac1,		},
	 {	IDC_STATIC_mac2,		},
	 {	IDC_STATIC_mac3,		},
	 {	IDC_STATIC_mac4,		},
	 {	IDOK,															},
	 {	IDCANCEL,													},
	 //
	 {	-1,		},
 };

 QY_DMITEM  CONST_dlg_cfgPcProcessRule[]  =
{	
	{	IDC_STATIC_processName,				},
	{	IDOK,															},
	{	IDCANCEL,													},
	{	-1,		},
};
 
 QY_DMITEM  CONST_dlg_qnmOtherMacInfo[]  =
{	
	{	IDC_STATIC_staticDes0,				(  TCHAR  *  )CONST_resId_STATIC_staticDes0,			},
	{	IDOK,															},
	{	IDCANCEL,													},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_phoneNum[]  =
{
	{	IDOK,															},
	{	IDCANCEL,													},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cfgSwitchPolicyGrps[]  =
{

	{	IDC_modifyDefSnmpPolicy,			},				//  _T(  "修改缺省策略"  ),				},
	{	IDC_STATIC_snmpPolicyHint,			},				//  _T(  "    注：snmp策略组用于提供非缺省的snmp协议策略，缺省的策略为 v1, 只读community为public, 可写community为private"  ),		},
	{	IDC_ADD,							(  TCHAR  *  )CONST_resId_ADD,						},
	{	IDC_MODIFY,							(  TCHAR  *  )CONST_resId_MODIFY,					},
	{	IDC_DEL,							(  TCHAR  *  )CONST_resId_DEL,						},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cfgSwitchPolicyGrp[]  =
{

	{	IDC_STATIC_snmpVer,						},				//	_T(  "snmp协议版本:"  ),		},
	{	IDC_STATIC_getCommunity,				},				// 	_T(  "只读community:"  ),		},
	{	IDC_STATIC_setCommunity,				},				//  _T(  "可写community:"  ),		},
	{	IDC_STATIC_usrName,						},				//  _T(  "用户名:"  ),			},
	{	IDC_STATIC_securityLevel,				},				//  _T(  "安全等级:"  ),		},
	{	IDC_STATIC_grpName,						},				//  _T(  "组名:"  ),		},
	{	IDC_STATIC_cfgSwitchPolicyGrpWarning,	},				//  _T(  "    警告：  本系统提供方便的管理功能，没有对这里存储的community采用强加密保存方式。建议不要在这里设置可写community，或者使用完成后将可写community清除。"  ),		},
	{	IDOK,															},
	{	IDCANCEL,													},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_mgrSwitchPolicyGrps[]  =
{
	{	IDC_ADD,								(  TCHAR  *  )CONST_resId_ADD,						},
	{	IDC_MODIFY,								(  TCHAR  *  )CONST_resId_MODIFY,					},
	{	IDC_DEL,								(  TCHAR  *  )CONST_resId_DEL,						},
	{	IDOK,															},
	{	IDCANCEL,													},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_addSwitchToGrp[]  =
{
	{	IDC_STATIC_ipAddress1,					},				//	_T(  "设备IP:"  ),		},
	{	IDC_STATIC_cusName,						},				//	_T(  "设备标识:"  ),		},
	{	IDC_STATIC_addSwitchToGrpHint,			},				//  _T(  "    注：当该设备已在设备视图中有标识时，该设备的标识将以视图中的标识为准。"  ),		},
	{	IDOK,															},
	{	IDCANCEL,													},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_qnmEditMacInfo[]  =
{
	{	IDC_CHECK_ucbDirectConn,				},	//		_T(  "   确定在此端口接入"  ),		},
	{	IDC_STATIC_devDes0,						},	//	_T(  "联接设备描述:"  ),		},
	{	IDC_qnmEditMacInfo_switch,				},	//  _T(  "网络设备:"  ),		},
	{	IDC_qnmEditMacInfo_mac,					},	//  _T(  "联接设备地址:"  ),		},
	{	IDC_qnmEditMacInfo_switchPort,			},	//  _T(  "联接端口:"  ),		},
	{	IDC_qnmEditMacInfo_auditTime,			},	//  _T(  "审核时间:"  ),		},
	{	IDOK,															},
	{	IDCANCEL,													},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_qnmSnmpObjProperties[]  =
{
	{	IDC_qnmSnmpObjProperties_productName,		},		//  _T(  "产品型号:"  ),		},
	{	IDC_qnmSnmpObjProperties_cusName,			},		//  _T(  "别名:"  ),		},
	{	IDC_qnmSnmpObjProperties_IP,				},		//  _T(  "IP:"  ),		},
	{	IDC_qnmSnmpObjProperties_place,				},		//  _T(  "使用地点:"  ),		},
	{	IDC_qnmSnmpObjProperties_numPorts,			},		//  _T(  "端口总数:"  ),		},
	{	IDC_qnmSnmpObjProperties_sysDescr,			},		//  _T(  "描述:"  ),		},
	{	IDC_STATIC_prePortIfDescr,					},		//  _T(  "端口名称:"  ),		},
	{	IDC_STATIC_prePortIfIndex,					},		//  _T(  "端口序号:"  ),		},
	{	IDC_STATIC_preICpsGlobalMaxSecureAddress,	},		//  _T(  "最大绑定MAC数:"  ),		},
	{	IDC_STATIC_preICpsGlobalTotalSecureAddress,	},		//  _T(  "当前绑定MAC数:"  ),		},
	{	IDOK,																},
	{	IDCANCEL,														},
	{	-1,		},
};



  QY_DMITEM  CONST_dlg_qnmSnmpObjPortProperties[]  =
{
	{	IDC_STATIC_prePortIfDescr,					},		//		_T(  "端口名称:"  ),		},
	{	IDC_STATIC_prePortIfIndex,					},		//		_T(  "端口序号:"  ),		},
	{	IDC_STATIC_preVlanId,						},		//		_T(  "Vlan号:"  ),		},
	{	IDC_STATIC_preICpsIfMaxSecureMacAddr,		},		//		_T(  "最大端口绑定MAC数:"  ),		},
	{	IDC_STATIC_preICpsIfSecureMacAddrCount,		},		//		_T(  "当前绑定MAC数:"  ),		},
	{	IDC_STATIC_preICpsIfPortSecurityStatus,		},		//		_T(  "端口绑定状态:"  ),		},
	{	IDC_STATIC_preICpsIfViolationAction,		},		//		_T(  "冲突响应方式:"  ),		},
	{	IDC_STATIC_iCpsIfViolationAction,			},		//		_T(  "丢包"  ),		},
	{	IDOK,																},
	{	IDCANCEL,														},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cfgSwitchDefaultPolicyGrp[]  =
{	
	{	IDC_default_snmpVer,						},		//  _T(  "snmp协议版本:"  ),		},
	{	IDC_default_getCommunity,					},		//	_T(  "只读community:"  ),		},
	{	IDC_default_setCommunity,					},		//  _T(  "可写community:"  ),		},
	{	IDC_default_cfgSwitchPolicyGrpWarning,		},		//  _T(  "    警告：  本系统提供方便的管理功能，没有对这里存储的community采用强加密保存方式。建议不要在这里设置可写community，或者使用完成后将可写community清除。"  ),		},
	{	IDC_cfgSwitchDefaultPolicyGrp_hint,			},		//  _T(  "    注：标准的缺省snmp策略为 v1, 只读community为public, 可写community为private"  ),		},
	{	IDOK,																},
	{	IDCANCEL,														},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_editSwitchInfo[]  =
{
	{	IDC_STATIC_cusName,							(  TCHAR  *  )CONST_resId_STATIC_bieMing,				},
	{	IDC_STATIC_place,							(  TCHAR  *  )CONST_resId_pc20_shiYongDiDian,			},
	{	IDC_STATIC_staticAuditTime,					(  TCHAR  *  )CONST_resId_STATIC_auditTime,			},
 	{	IDOK,																},
	{	IDCANCEL,														},
	{	-1,		},
};
 

 QY_DMITEM  CONST_dlg_qnmCfgSnmpObjRule[]  =
{
	{	IDC_STATIC_staticRuleType,					},				//				"策略类型:",IDC_STATIC,25,18,48,14,SS_CENTERIMAGE
	{	IDC_STATIC_staticProductName,				},				//				"设备型号：",IDC_STATIC,25,33,48,14,SS_CENTERIMAGE
	{	IDC_CHECK_ibDirectConn,						},				//				"是否接入层设备:",IDC_CHECK_ibDirectConn,"Button",
	{	IDC_STATIC_portIfDescrHint,					},				//				"端口:",IDC_STATIC_portIfDescrHint,27,67,49,14,
	{	IDC_STATIC_ibDownPortIfMacChanged,			},				//				"新增联接MAC时是否阻断:",IDC_STATIC,27,87,89,14,
	{	IDC_STATIC_ibDownPortIfMacChangePort,		},				//				"联接MAC更换端口时是否阻断
	{	IDC_STATIC_ibNotLogIfMacChanged,			},				//				"否记录联接MAC变化事件
	{	IDC_STATIC_warnPercentOfBand,			},				//				报警流量(带宽百分比)
	{	IDC_STATIC_warnPercentOfBandUnit,			},				//			
	{	IDC_STATIC_ibDownPortIfWarnSpeed,					},				//				流量报警后是否阻断
 	{	IDOK,																},
	{	IDCANCEL,														},
	{	-1,		},
 };


 QY_DMITEM  CONST_dlg_cfgModuleKnowlege[]  =
{
	{	IDC_STATIC_cfgModuleKnowlegeHint,																},
	{	IDC_STATIC_staticFileName,																		},
	{	IDC_STATIC_staticCmdLine,				},
	{	IDC_CHECK_bCmdLineGiven,				},
	{	IDC_STATIC_name,							(  TCHAR  *  )CONST_resId_STATIC_bieMing,			},
	{	IDC_STATIC_des0,																				},
	{	IDC_STATIC_company,				},
	{	IDC_STATIC_product,				},
	{	IDC_STATIC_commonErr,			},
	{	IDC_STATIC_memInfo,				},
	{	IDC_STATIC_securityLevel,		},
	{	IDC_CHECK_ucbSys,				},
	{	IDC_CHECK_ucbDaemon,			},
	{	IDC_CHECK_ucbUseNet,			},
	{	IDC_CHECK_ucbHardware,			},
	{	IDC_CHECK_ucbSpy,				},
	{	IDC_CHECK_ucbAdvertisement,		},
	{	IDC_CHECK_ucbVirus,				},
	{	IDC_CHECK_ucbBackDoor,			},
	{	IDC_STATIC_providerName,		},
	{	IDC_STATIC_providerAddr,		},
	{	IDC_STATIC_providerTime,		},
	{	IDC_STATIC_staticAuditTime,		},
	{	IDC_STATIC_auditTime,			},
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_qnmPcProcessModuleListSearch[]  =
 {
	{	IDC_STATIC_qnmPcProcessModuleListSearch,	},
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
 };

 QY_DMITEM  CONST_dlg_moduleKnowlegeOptions[]  =
{
	{	IDC_RADIO_unAudited,					},
	{	IDC_RADIO_audited,				},
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_cfgPcRegistryKnowledge[]  =
{
	{	IDC_STATIC_cfgPcRegistryKnowlegeHint,														},
	{	IDC_STATIC_iRootKey,																		},
	{	IDC_STATIC_subKey,																			},
	{	IDC_STATIC_cfgName,																			},
	{	IDC_STATIC_staticFileName,					(  TCHAR  *  )CONST_resId_absolutePcRegistry,	},
	{	IDC_STATIC_suggestedVal,																	},
	//  {	IDC_STATIC_staticFileName,																	},
	{	IDC_STATIC_name,							(  TCHAR  *  )CONST_resId_STATIC_bieMing,			},
	{	IDC_STATIC_des0,																				},
	{	IDC_STATIC_company,				},
	{	IDC_STATIC_product,				},
	{	IDC_STATIC_commonErr,			},
	//  {	IDC_STATIC_memInfo,				},
	{	IDC_STATIC_securityLevel,		},
	{	IDC_CHECK_ucbSys,				},
	{	IDC_CHECK_ucbDaemon,			},
	{	IDC_CHECK_ucbUseNet,			},
	{	IDC_CHECK_ucbHardware,			},
	{	IDC_CHECK_ucbSpy,				},
	{	IDC_CHECK_ucbAdvertisement,		},
	{	IDC_CHECK_ucbVirus,				},
	{	IDC_CHECK_ucbBackDoor,			},
	{	IDC_STATIC_providerName,		},
	{	IDC_STATIC_providerAddr,		},
	{	IDC_STATIC_providerTime,		},
	{	IDC_STATIC_staticAuditTime,		},
	{	IDC_STATIC_auditTime,			},
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
};

 #endif

 QY_DMITEM  CONST_dlg_selectDsn[]  =
{
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
};

#ifndef  __WINCE__
 QY_DMITEM  CONST_dlg_imMsgSearch[]  =
{
	{	IDC_STATIC_staticTalker,		},
	{	IDC_STATIC_staticId,			},
	{	IDC_STATIC_content,				},
	{	IDC_STATIC_startTime,			},
	{	IDC_STATIC_endTime,				},
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_wwwQmContact[]  =
{
	{	IDC_STATIC_staticMessengerId,	},
	{	IDC_CHECK_ucbPublic,			},
	{	IDC_STATIC_grpDisplayName,		},
	{	IDC_EDIT_grpDisplayName,		},
	{	IDC_STATIC_displayName,		},
	{	IDC_EDIT_displayName,		},
	{	IDC_CHECK_ucbImSwitchable,		},
	{	IDC_STATIC_wAdvertisement,		},
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
};


  QY_DMITEM  CONST_dlg_cfgIpKnowledge[]  =
{
	{	IDC_STATIC_startIp,				},
	{	IDC_STATIC_endIp,				},
	{	IDC_STATIC_wLocation,			},
	{	IDC_STATIC_iWeight,				},
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_cfgPhoneMessenger[]  =
{
	{	IDC_STATIC_dw,					},
	{	IDC_STATIC_bm,					},
	{	IDC_STATIC_syr,					},
	{	IDC_STATIC_countryCode,			},
	{	IDC_STATIC_phoneNo,				},
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cfgGsmModem[]  =
{
	{	IDC_CHECK_ucbPublic,			},
	{	IDC_STATIC_idStr_vDev,			},
	{	IDC_STATIC_wDevIdStr,			},
	{	IDC_CHECK_ucbDefaultSmServer,	},
	{	IDC_STATIC_name,				},
	{	IDC_STATIC_cusName,				},
	{	IDC_CHECK_ucbDefault,				(  TCHAR  *  )CONST_resId_ucbDefaultSmContact,			},
	{	IDC_STATIC_staticMessengerId,		(  TCHAR  *  )CONST_resId_smContactMsgrId,				},
	{	IDC_STATIC_displayName,			},
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_verifyPhoneList[]  =
{
	{	IDC_STATIC_hint,					(  TCHAR  *  )CONST_resId_verifyPhoneListHint,			},
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
};

#endif

#if  0
 QY_DMITEM  CONST_dlg_talk[]  =
{
	{	IDC_STATIC_instantStatus,	},
	{	IDC_BUTTON_font,			},
	{	IDC_STATIC_peerName,		},
	{	IDC_STATIC_peerDesc,		},
	{	IDCANCEL,		},
	{	-1,		},
};

#endif

 QY_DMITEM  CONST_dlg_desktopsMon[]  =
{
	{	IDC_STATIC30,		},
	{	IDC_STATIC31,		},
	{	IDC_STATIC32,		},
	{	IDC_STATIC33,		},
	{	IDC_STATIC34,		},
	{	IDC_STATIC35,		},
	{	IDC_STATIC36,		},
	{	IDC_STATIC37,		},
	{	IDC_STATIC38,		},
	{	IDC_STATIC39,		},
	{	IDC_STATIC40,		},
	{	IDC_STATIC41,		},
	{	IDC_STATIC42,		},
	{	IDC_STATIC43,		},
	{	IDC_STATIC44,		},
	{	IDC_STATIC45,		},
	{	IDOK,		},
	{	IDCANCEL,		},
	{	-1,		},
};


#if  0

 QY_DMITEM  CONST_dlg_selectAvDev[]  =  
 {
	 {  IDC_STATIC_aDev,  },
	 {  IDC_STATIC_vDev,  },
	 {  IDC_BUTTON_cfgCaptureFilter_v,  },
	 {  IDC_BUTTON_cfgCapturePin_v,  },
	 {	IDC_BUTTON_cfgCrossBar_v,  },				
	 {	IDOK,			},
	 {	IDCANCEL,		},
	 {	-1,				},
 };


 QY_DMITEM  CONST_dlg_cfgWmv[]  =
 {
	 {	IDC_STATIC_encodingMode,	},
	 {	IDC_CBR,		},
	 {	IDC_QUALITY_VBR,	},
	 {	IDC_STATIC_VBRQUALITY,	},
	 {	IDC_STATIC_QUALITY,	},
	 {	IDC_STATIC_COMPLEXITY,	},
	 {	IDC_STATIC_PROFILES,		},
	 {	IDC_STATIC_FRAMERATE,		},
	 {	IDC_STATIC_BITRATE,			},
	 {	IDC_STATIC_BUFFERDELAY,		},
	 {	IDC_STATIC_MAXKEYDISTANCE,	},
	 {	IDOK,			},
	 {	IDCANCEL,		},
	 {	-1,				},
 };

 QY_DMITEM  CONST_dlg_mediaControl[]  =
 {
	 //  {	IDC_BUTTON_PLAY,	},
	 {	IDC_BUTTON_STOP,	},
	 {	IDC_BUTTON_FRAMESTEP,	},
	 {	IDC_CHECK_PLAYTHROUGH,							},
	 {	IDC_CHECK_LOOP,									},
	 {	IDC_CHECK_MUTE,									},

	 {	-1,				},
 };
 

 QY_DMITEM  CONST_dlg_shareDynBmps[]  =
{
	{	IDC_STATIC00,	},
	{	IDC_STATIC01,	},
	{	IDC_STATIC02,	},
	{	IDC_STATIC_sharingScreen0,	},
	{	IDC_STATIC_sharingScreen1,	},
	{	IDC_STATIC_sharingScreen2,	},
	{	IDC_STATIC10,	},
	{	IDC_STATIC11,	},
	{	IDC_STATIC12,	},
	{	IDC_STATIC_webcam0,	},
	{	IDC_STATIC_webcam1,	},
	{	IDC_STATIC_webcam2,	},
	{	IDC_STATIC_pic0,	},
	//
	{	IDC_STATIC_gps,		},
	{	IDC_STATIC_gpsStatus,		},
	{	IDC_BUTTON_gps,		},
	//
	{	IDC_CHECK_shareBmp,	},
	//
	{	IDOK,			},
	{	IDCANCEL,		},
	{	-1,				},
};


 QY_DMITEM  CONST_dlg_progress[]  =
{
	{	IDC_STATIC_progress,	},
	{	IDOK,					},
	{	IDCANCEL,				},
	{	-1,				},
};

 QY_DMITEM  CONST_dlg_mcClientLogon[]  =
{
	{	IDC_STATIC_logonServer,	},
	{	IDC_STATIC_usrName,		},
	{	IDC_STATIC_passwd,		},
	{	IDC_BUTTON_option,		},
	{	IDOK,					},
	{	IDCANCEL,				},
	{	-1,				},
};
#endif

#ifndef  __WINCE__
 QY_DMITEM	CONST_dlg_messenger[]	=
{
	{	IDC_STATIC_hint1,		 },
	{	IDC_STATIC_messengerName,},   //  IDC_STATIC_staticName
	{	IDC_STATIC_passwd0,		},
	{	IDC_STATIC_passwd1,		},
	{	IDOK,					 },
	{	IDCANCEL,				 },
	{	-1,				},
};

 QY_DMITEM	CONST_dlg_messengerIsClient[]	=
{
	{	IDC_STATIC_hint1,		 },
	{	IDC_STATIC_messengerName,},   //  IDC_STATIC_staticName
	{	IDC_STATIC_passwd0,		},
	{	IDC_STATIC_passwd1,		},
	{	IDOK,					 },
	{	IDCANCEL,				 },
	{	-1,				},
};

 QY_DMITEM  CONST_dlg_imObjRule[]  =
{
	{	IDC_STATIC_hint_imObjRule,					},
	{	IDC_CHECK_shareWebcamInConference,			},
	{	IDC_STATIC_conferenceId_shareWebcam,		},
	{	IDC_CHECK_noLocalVideoInThisConference,		},
	{	IDC_CHECK_distinguishSharedWebcams,			},

	{	IDC_STATIC_autoAnswer_av,					},
	{	IDC_STATIC_autoAnswer_screen,				},
	{	IDC_STATIC_autoAnswer_mediaFile,			},
	{	IDOK,										},
	{	IDCANCEL,									},
	{	-1,											},
};

#endif

#ifdef  __WINCE__
 QY_DMITEM  CONST_dlg_qnmCfgOptions_isClient_ce[]  =
{
	{	IDC_BUTTON_contact,		},
	{	IDC_BUTTON_group,		},
	{	IDC_BUTTON_status,		},
	{	IDCANCEL,				 },
	{	-1,						},

};

#endif





 QY_DMITEM  CONST_dlgTable[]  =
{
#ifndef  __WINCE__
	{	IDD_qyCfgSystem,					(  TCHAR  *  )CONST_dlg_qyCfgSystem,				},
	{	IDD_qyCfgSystems,					(  TCHAR  *  )CONST_dlg_qyCfgSystems,				},
	//
	{	IDD_cfgSystemParams,				(  TCHAR  *  )CONST_dlg_cfgSystemParams,						},
	{	IDD_cfgSystemParams_is,				(  TCHAR  *  )CONST_dlg_cfgSystemParams_is,				},
		
	//	
	{	IDD_qnmCfgRasOptions,				(  TCHAR  *  )CONST_dlg_qnmCfgRasOptions,			(  TCHAR  *  )CONST_resId_IDD_qnmCfgRasOptions,			},
	{	IDD_qnmCfgPcNetworkOptions,			(  TCHAR  *  )CONST_dlg_qnmCfgPcNetworkOptions,	(  TCHAR  *  )CONST_resId_IDD_qnmCfgPcNetworkOptions,	},	
	{	IDD_pcNetworkOptions_sel,			(  TCHAR  *  )CONST_dlg_pcNetworkOptions_sel,		},
	{	IDD_qnmCfgPcMonOptions,				(  TCHAR  *  )CONST_dlg_qnmCfgPcMonOptions,		},	
	{	IDD_cfgFileMonFilter,				(  TCHAR  *  )CONST_dlg_cfgFileMonFilter,			},
	{	IDD_addFileMonRule,					(  TCHAR  *  )CONST_dlg_addFileMonRule,		},
	{	IDD_cfgPcRegistrys,					(  TCHAR  *  )CONST_dlg_cfgPcRegistrys,				},
	{	IDD_cfgPcRegistry,					(  TCHAR  *  )CONST_dlg_cfgPcRegistry,				},
	{	IDD_policy_imAuthCond,				(  TCHAR  *  )CONST_dlg_policyImAuthCond,			},

	{	IDD_cfgCustom,						(  TCHAR  *  )CONST_dlg_cfgCustom,									},
	{	IDD_cfgStandardName,				(  TCHAR  *  )CONST_dlg_cfgStandardName,	},
	{	IDD_cfgStandardNames,				(  TCHAR  *  )CONST_dlg_cfgStandardNames,	},
	{	IDD_qnmCfgOptions,					(  TCHAR  *  )CONST_dlg_qnmCfgOptions,							},
	{	IDD_exportClients,					(  TCHAR  *  )CONST_dlg_exportClients,			},				//  2011/03/28
#endif
#if  0
	{	IDD_qnmCfgOptions_isClient,			(  TCHAR  *  )CONST_dlg_qnmCfgOptions_isClient,					},
#endif
#ifndef  __WINCE__
	{	IDD_qnmCfgPcRule,					(  TCHAR  *  )CONST_dlg_qnmCfgPcRule,				(  TCHAR  *  )CONST_resId_IDD_qnmCfgPcRule,				},
	{	IDD_qnmEditPcUsrInfo ,				(  TCHAR  *  )CONST_dlg_qnmEditPcUsrInfo,			(  TCHAR  *  )CONST_resId_IDD_qnmEditPcUsrInfo,			},
	//  2005/11/09
	{	IDD_ABOUTBOX,						(  TCHAR  *  )CONST_dlg_aboutBox,					(  TCHAR  *  )CONST_resId_IDD_ABOUTBOX,					},
	{	IDD_CFGUSR,							(  TCHAR  *  )CONST_dlg_cfgUsr,					(  TCHAR  *  )CONST_resId_IDD_CFGUSR,					},
	{	IDD_CFGUSRS,						(  TCHAR  *  )CONST_dlg_cfgUsrs,					(  TCHAR  *  )CONST_resId_IDD_CFGUSRS,					},
	{	IDD_CFGWARN,						(  TCHAR  *  )CONST_dlg_cfgWarn,					(  TCHAR  *  )CONST_resId_IDD_CFGWARN,					},
	{	IDD_clearupEventCond,				(  TCHAR  *  )CONST_dlg_cleanupEventCond,			(  TCHAR  *  )CONST_resId_IDD_clearupEventCond,			},
	{	IDD_qnmSearch,						(  TCHAR  *  )CONST_dlg_qnmSearch,					(  TCHAR  *  )CONST_resId_IDD_qnmSearch,				    },
	{	IDD_cusPcSp,						(  TCHAR  *  )CONST_dlg_cusPcSp,					(  TCHAR  *  )CONST_resId_IDD_cusPcSp,					},
	{	IDD_qnmCfgPcGrp,					(  TCHAR  *  )CONST_dlg_qnmCfgPcGrp,				(  TCHAR	 *  )CONST_resId_IDD_qnmCfgPcGrp,				},
	{	IDD_shhgPcProperties,				(  TCHAR  *  )CONST_dlg_pcProperties,				(  TCHAR  *  )CONST_resId_IDD_shhgPcProperties,			},

	{	IDD_prop_messenger,					(  TCHAR  *  )CONST_dlg_messengerProperties,		},
	{	IDD_prop_imGrp,						(  TCHAR  *  )CONST_dlg_imGrpProperties,			},
	{	IDD_imGrp,							(  TCHAR  *  )CONST_dlg_imGrp,				},
	{	IDD_policy_isMgr,					(  TCHAR  *  )CONST_dlg_policy_isMgr,		},
	{	IDD_cfgCustomerService,				(  TCHAR  *  )CONST_dlg_cfgCustomerService,	},
#endif
#if  0
	{	IDD_policy_isClient,				(  TCHAR  *  )CONST_dlg_policy_isClient,	},
	{	IDD_menu_isCli_walls,				(  TCHAR  *  )CONST_dlg_menu_isCli_wallsbar,},
	{	IDD_qyBar,							(  TCHAR  *  )CONST_dlg_bar,				},
	//  {	IDD_policyAv,						(  TCHAR  *  )CONST_dlg_policyAv,			},
#endif
#ifndef  __WINCE__
	{	IDD_prop_imTask,					(  TCHAR  *  )CONST_dlg_imTaskProperties,	},
	{	IDD_prop_imMsg,						(  TCHAR  *  )CONST_dlg_imMsgProperties,	},
	{	IDD_qyExport,						(  TCHAR  *  )CONST_dlg_qyExport,					(  TCHAR  *  )CONST_resId_IDD_qyExport,					},
	{	IDD_qnmClearup,						(  TCHAR  *  )CONST_dlg_qnmClearup,					(  TCHAR  *  )CONST_resId_IDD_qnmClearup,				},
	{	IDD_passwdForStopMon,				(  TCHAR  *  )CONST_dlg_passwdForStopMon,			(  TCHAR  *  )CONST_resId_IDD_passwdForStopMon,			},
	{	IDD_pcAssetProperties,				(  TCHAR  *  )CONST_dlg_pcAssetProperties,			(  TCHAR  *  )CONST_resId_IDD_pcAssetProperties,			},
	{	IDD_qnmSearch,						(  TCHAR  *  )CONST_dlg_qnmSearch,					(  TCHAR  *  )CONST_resId_IDD_qnmSearch,				},
	{	IDD_qnmEventSearch,					(  TCHAR  *  )CONST_dlg_qnmEventSearch,			},
	{	IDD_qnmPcAssetListSearch,			(  TCHAR  *  )CONST_dlg_qnmPcAssetListSearch,		},
	{	IDD_qnmPcListSearch,				(  TCHAR  *  )CONST_dlg_qnmPcListSearch,			},
	{	IDD_qnmPcSpListSearch,				(  TCHAR  *  )CONST_dlg_qnmPcSpListSearch,			},
	{	IDD_qnmCfgPcGrps,					(  TCHAR  *  )CONST_dlg_qnmCfgPcGrps,				},
	{	IDD_qnmCfgAdvancedOptions,			(  TCHAR  *  )CONST_dlg_qnmCfgAdvancedOptions,		},
	{	IDD_prop_pcNetwork,					(  TCHAR  *  )CONST_dlg_prop_pcNetwork,			},
	{	IDD_qnmCfgPcNetworkRule,			(  TCHAR  *  )CONST_dlg_qnmCfgPcNetworkRule,		},
	{	IDD_prop_pcProxyCfg,				(  TCHAR  *  )CONST_dlg_prop_pcProxyCfg,			},
	{	IDD_qnmCfgPcProxyCfg,				(  TCHAR  *  )CONST_dlg_qnmCfgPcProxyCfg,			},
	//  {	IDD_prop_pcComputer,				(  TCHAR  *  )CONST_dlg_prop_pcComputer,			},
	//  {	IDD_qnmCfgPcComputer,				(  TCHAR  *  )CONST_dlg_qnmCfgPcComputer,		(  TCHAR  *  )CONST_resId_IDD_qnmCfgPcComputer,			},
	{	IDD_prop_windowsUpdatePolicy,		(  TCHAR  *  )CONST_dlg_prop_windowsUpdatePolicy,		},
	{	IDD_qnmCfgWindowsUpdatePolicy,		(  TCHAR  *  )CONST_dlg_qnmCfgWindowsUpdatePolicy,		},
	{	IDD_qnmCfgIpScan,					(  TCHAR  *  )CONST_dlg_qnmCfgIpScan,			(  TCHAR  *  )CONST_resId_IDD_qnmCfgIpScan,				},
	{	IDD_qnmCfgIpGrp,					(  TCHAR  *  )CONST_dlg_qnmCfgIpGrp,				},
	{	IDD_qnmCfgUnchk,					(  TCHAR  *  )CONST_dlg_qnmCfgUnchk,		},
	{	IDD_qnmCfgUnchkedIpGrp,				(  TCHAR  *  )CONST_dlg_qnmCfgUnchkedIpGrp,		},
	{	IDD_cfgSkippedMacs,					(  TCHAR  *  )CONST_dlg_cfgSkippedMacs,	},
	{	IDD_cfgPcProcessRule,				(  TCHAR  *  )CONST_dlg_cfgPcProcessRule,		},
	{	IDD_qnmOtherMacInfo,				(  TCHAR  *  )CONST_dlg_qnmOtherMacInfo,		},
	{	IDD_phoneNum,						(  TCHAR  *  )CONST_dlg_phoneNum,				},	
	//  2005/12/11
	{	IDD_cfgSwitchPolicyGrps,			(  TCHAR  *  )CONST_dlg_cfgSwitchPolicyGrps,		},
	{	IDD_cfgSwitchPolicyGrp,				(  TCHAR  *  )CONST_dlg_cfgSwitchPolicyGrp,		},
	{	IDD_mgrSwitchPolicyGrps,			(  TCHAR  *  )CONST_dlg_mgrSwitchPolicyGrps,		},
	{	IDD_addSwitchToGrp,					(  TCHAR  *  )CONST_dlg_addSwitchToGrp,		},
	{	IDD_qnmEditMacInfo,					(  TCHAR  *  )CONST_dlg_qnmEditMacInfo,		},
	{	IDD_qnmSnmpObjProperties,			(  TCHAR  *  )CONST_dlg_qnmSnmpObjProperties,		},
	{	IDD_qnmSnmpObjPortProperties,		(  TCHAR  *  )CONST_dlg_qnmSnmpObjPortProperties,		},
	{	IDD_cfgSwitchDefaultPolicyGrp,		(  TCHAR  *  )CONST_dlg_cfgSwitchDefaultPolicyGrp,		},
	{	IDD_editSwitchInfo,					(  TCHAR  *  )CONST_dlg_editSwitchInfo,				},
	{	IDD_qnmCfgSnmpObjRule,				(  TCHAR  *  )CONST_dlg_qnmCfgSnmpObjRule,				},
	//
	{	IDD_cfgModuleKnowlege,				(  TCHAR  *  )CONST_dlg_cfgModuleKnowlege,				},
	{	IDD_prop_moduleKnowlege,			(  TCHAR  *  )CONST_dlg_cfgModuleKnowlege,				},
	{	IDD_qnmPcProcessModuleListSearch,	(  TCHAR  *  )CONST_dlg_qnmPcProcessModuleListSearch,	},
	{	IDD_moduleKnowlegeOptions,			(  TCHAR  *  )CONST_dlg_moduleKnowlegeOptions,			},
	//
	{	IDD_cfgPcRegistryKnowledge,			(  TCHAR  *  )CONST_dlg_cfgPcRegistryKnowledge,		},
	{	IDD_prop_pcRegistryKnowledge,		(  TCHAR  *  )CONST_dlg_cfgPcRegistryKnowledge,		},
	//
	{	IDD_selectDsn,						(  TCHAR  *  )CONST_dlg_selectDsn,						},
	{	IDD_select,							(  TCHAR  *  )CONST_dlg_selectDsn,						},
	{	IDD_imMsgSearch,					(  TCHAR  *  )CONST_dlg_imMsgSearch,					},
	{	IDD_wwwQmCfg,						(  TCHAR  *  )CONST_dlg_wwwQmContact,					},
	{	IDD_cfgIpKnowledge,					(  TCHAR  *  )CONST_dlg_cfgIpKnowledge,				},
	{	IDD_prop_ipKnowledge,				(  TCHAR  *  )CONST_dlg_cfgIpKnowledge,				},
	{	IDD_cfgPhoneMessenger,				(  TCHAR  *  )CONST_dlg_cfgPhoneMessenger,				},
	{	IDD_cfgGsmModem,					(  TCHAR  *  )CONST_dlg_cfgGsmModem,						},
#endif
#if  0
	{	IDD_talk,							(  TCHAR  *  )CONST_dlg_talk,						},
#endif
	{	IDD_desktopsMon,					(  TCHAR  *  )CONST_dlg_desktopsMon,				},
#if  0
	{	IDD_cfgVideoConference,				(  TCHAR  *  )CONST_dlg_cfgVideoConference,			},
	{	IDD_videoCompressors,				(  TCHAR  *  )CONST_dlg_videoCompressors,			},
#endif
	{	IDD_msgList,						(  TCHAR  *  )CONST_dlg_msgList,					},
	{	IDD_objs,							(  TCHAR  *  )CONST_dlg_objs,						},

#if  0
	{	IDD_cfgWmv,							(  TCHAR  *  )CONST_dlg_cfgWmv,						},
	{	IDD_mediaControl,					(  TCHAR  *  )CONST_dlg_mediaControl,				},
	{	IDD_shareDynBmps,					(  TCHAR  *  )CONST_dlg_shareDynBmps,				},
	{	IDD_progress,						(  TCHAR  *  )CONST_dlg_progress,					},
	{	IDD_mcClient_logon,					(  TCHAR  *  )CONST_dlg_mcClientLogon,				},
	{	IDD_messenger_isClient,				(  TCHAR  *  )CONST_dlg_messengerIsClient,			},
#endif

#ifndef  __WINCE__
	{	IDD_messenger,						(  TCHAR  *  )CONST_dlg_messenger,					},
	{	IDD_imObjRule,						(  TCHAR  *  )CONST_dlg_imObjRule,					},
#endif
	//
#ifdef  __WINCE__
	{	IDD_qnmCfgOptions_isClient_ce,		(  TCHAR  *  )CONST_dlg_qnmCfgOptions_isClient_ce,  },
#endif 

#if 0
	{	IDD_instantAssistant_vw,			(  TCHAR  *  )CONST_dlg_instantAssistant_vw,			},
	{	IDD_selectAvDev,					(  TCHAR  *  )CONST_dlg_selectAvDev,				},
#endif  

	{	-1,		},
};

