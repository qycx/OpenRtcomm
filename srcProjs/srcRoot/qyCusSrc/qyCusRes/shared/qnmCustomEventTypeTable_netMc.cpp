
#include	"stdafx.h"
#include	<tchar.h>
//  #include	"qyCommon.h"
//  #include	"resource_main.h"
//  #include	"afxres.h"

#include	"qyCusResCommon.h"
//  #include	"qyCusResPublic.h" 

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_netMc.h"


  //  事件类型总表
 QY_DMITEM  CONST_qnmEventTypeTable0_netMc[]  =  
{
	{	CONST_qyEventType_nm_newPc,					CONST_str_nm_newPc,		},				//	_T(  "新增机器"  ),					},
	{	CONST_qyEventType_nm_macsModified,			CONST_str_nm_macsModified,		},		//		_T(  "网卡变更, 作注销处理"  ),		},					
	{	CONST_qyEventType_nm_macsModifiedPc,		CONST_str_nm_macsModifiedPc,		},	//	_T(  "网卡变更机器"  ),				},				
	{	CONST_qyEventType_nm_newReg,				CONST_str_nm_newReg,		},	//			_T(  "首次注册"  ),					},	
	{	CONST_qyEventType_nm_reReg,					CONST_str_nm_reReg,		},	//				_T(  "重新注册"  ),					},
	{	CONST_qyEventType_nm_qwmDel,				CONST_str_nm_qwmDel,		},	//			_T(  "客户端运行异常"  ),		},				
	{	CONST_qyEventType_nm_qwmDelRecovery,		CONST_str_nm_qwmDelRecovery,		},	//	_T(  "客户端恢复正常"  ),		},						
	{	CONST_qyEventType_nm_qwmDelOffline,			CONST_str_nm_qwmDelOffline,		},	//		_T(  "异常客户端离开内网"  ),		},					
	{	CONST_qyEventType_nm_ipChanged,				CONST_str_nm_ipChanged,		},	//			_T(  "IP更改"  ),					},	
	{	CONST_qyEventType_nm_osChanged,				CONST_str_nm_osChanged,		},	//			_T(  "操作系统变化"  ),				},		
	{	CONST_qyEventType_nm_rasStart,				CONST_str_nm_rasStart,		},	//			_T(  "拨号开始"  ),					},	
	{	CONST_qyEventType_nm_rasEnd,				CONST_str_nm_rasEnd,		},	//			_T(  "拨号结束"  ),					},	
	{	CONST_qyEventType_nm_rasProhibited,			CONST_str_nm_rasProhibited,		},	//		_T(  "拨号禁止"  ),					},		
	{	CONST_qyEventType_nm_onInternet,			CONST_str_nm_onInternet,		},	//		_T(  "连通互联网"  ),				},			
	{	CONST_qyEventType_nm_offInternet,			CONST_str_nm_offInternet,		},	//		_T(  "断开互联网"  ),				},			
	{	CONST_qyEventType_nm_wLanAdapterStart,		CONST_str_nm_wLanAdapterStart,	},	//				505				//  2010/05/20
	{	CONST_qyEventType_nm_wLanAdapterEnd,		CONST_str_nm_wLanAdapterEnd,	},	//					506				//  2010/05/20
	{	CONST_qyEventType_nm_wLanAdapterProhibited,	CONST_str_nm_wLanAdapterProhibited,	},	//			507				//  2010/05/20

	//			//									
	{	CONST_qyEventType_nm_usbStorOnFor9x,		CONST_str_nm_usbStorOnFor9x,		},	//	_T(  "启用9x系统USB"  ),		},	//	2005-1-8			
	{	CONST_qyEventType_nm_usbStorOffFor9x,		CONST_str_nm_usbStorOffFor9x,		},	//	_T(  "禁用9x系统USB"  ),		},	//  2005/01/08				
	{	CONST_qyEventType_nm_usbStorIn,				CONST_str_nm_usbStorIn,				},	//	_T(  "USB磁盘接入"  ),			},	//  2005/01/07	
	{	CONST_qyEventType_nm_usbStorUnallowedIn,	CONST_str_nm_usbStorUnallowedIn,	},	//	_T(  "USB磁盘违规接入"  ),		},						
	{	CONST_qyEventType_nm_usbStorOut,			CONST_str_nm_usbStorOut,			},	//	_T(  "USB磁盘移出"  ),			},	//  2005/01/07		
	{	CONST_qyEventType_nm_usbStorProhibited,		CONST_str_nm_usbStorProhibited,		},	//	_T(  "阻断USB磁盘"  ),			},	//  2005/01/07			
	{	CONST_qyEventType_nm_usbRestartToProhibit,	CONST_str_nm_usbRestartToProhibit,	},	//  _T(  "重起阻断USB磁盘"  ),		},	//  2005/06/26					
	//
	{	CONST_qyEventType_nm_floppyOn,				CONST_str_nm_floppyOn,		},	//			_T(  "启用软驱"  ),					},	//  2005/01/08
	{	CONST_qyEventType_nm_floppyOff,				CONST_str_nm_floppyOff,		},	//			_T(  "禁用软驱"  ),					},	//  2005/01/08
	{	CONST_qyEventType_nm_cdromOn,				CONST_str_nm_cdromOn,		},	//			_T(  "启用光驱"  ),					},	//  2005/01/08
	{	CONST_qyEventType_nm_cdromOff,				CONST_str_nm_cdromOff,		},	//			_T(  "禁用光驱"  ),					},	//  2005/01/08
	//			//									
	{	CONST_qyEventType_nm_safeModeOn,			CONST_str_nm_safeModeOn,		},	//		_T(  "允许安全模式"  ),				},	//  2005/06/25		
	{	CONST_qyEventType_nm_safeModeOff,			CONST_str_nm_safeModeOff,		},	//		_T(  "禁用安全模式"  ),				},	//  2005/06/25		
	{	CONST_qyEventType_nm_netShareMgr,			CONST_str_nm_netShareMgr,		},	//  
	//						
	{	CONST_qyEventType_nm_ucBlueToothProhibited,	CONST_str_nm_ucBlueToothProhibited,		},							//  2010/08/18
	{	CONST_qyEventType_nm_ucInfraredProhibited,	CONST_str_nm_ucInfraredProhibited,		},							//  2010/08/18
	{	CONST_qyEventType_nm_uc1394Prohibited,		CONST_str_nm_uc1394Prohibited,			},							//  2010/08/18
	{	CONST_qyEventType_nm_sdHostAdapterProhibited,	CONST_str_nm_sdHostAdapterProhibited,	},						//  2011/08/28

	//
	{	CONST_qyEventType_nm_devIn,					CONST_str_nm_devIn,						},
	{	CONST_qyEventType_nm_devOut,				CONST_str_nm_devOut,					},
	{	CONST_qyEventType_nm_devProhibited,			CONST_str_nm_devProhibited,				},
	{	CONST_qyEventType_nm_devEnabled,			CONST_str_nm_devEnabled,				},

	//
	{	CONST_qyEventType_nm_strangePc,				CONST_str_nm_strangePc,		},	//			_T(  "陌生主机接入"  ),				},		
	{	CONST_qyEventType_nm_strangePcUnderCtrl,	CONST_str_nm_strangePcUnderCtrl,		},	//				},					
	{	CONST_qyEventType_nm_strangePcOffline,		CONST_str_nm_strangePcOffline,		},	//	_T(  "陌生主机离线"  ),				},				
	{	CONST_qyEventType_nm_pcUnchked,				CONST_str_nm_pcUnchked,		},	//			_T(  "主机免检"  ),					},	
	{	CONST_qyEventType_nm_pcAttacked,			CONST_str_nm_pcAttacked,		},	//		_T(  "阻断主机"  ),					},		
	{	CONST_qyEventType_nm_strangeIp,				CONST_str_nm_strangeIp,		},	//			_T(  "未注册IP"  ),					},	
	{	CONST_qyEventType_nm_delPc,					CONST_str_nm_delPc,		},	//				_T(  "手工删除主机记录"  ),			},		
	{	CONST_qyEventType_nm_proxyServerSet,		CONST_str_nm_proxyServerSet,		},	//	_T(  "代理已设置"  ),				},				
	{	CONST_qyEventType_nm_proxyServerClear,		CONST_str_nm_proxyServerClear,		},	//	_T(  "代理设置清除"  ),				},				
	//			//									
	{	CONST_qyEventType_nm_printerJob,			CONST_str_nm_printerJob,		},	//		_T(  "打印"  ),						},	
	//  {	CONST_qyEventType_nm_fileMon,				CONST_str_nm_fileMon,		},	//			_T(  "文件操作"  ),					},	
	{	CONST_qyEventType_nm_fileAdded,				CONST_str_nm_fileAdded,		},
	{	CONST_qyEventType_nm_fileRemoved,			CONST_str_nm_fileRemoved,	},
	{	CONST_qyEventType_nm_fileModified,			CONST_str_nm_fileModified,	},
	{	CONST_qyEventType_nm_fileRenamed,			CONST_str_nm_fileRenamed,	},
	//
	{	CONST_qyEventType_nm_processMgr,			CONST_str_nm_processMgr,		},	//		_T(  "进程管理"  ),					},		
	//
	{	CONST_qyEventType_nm_usrMgr,				CONST_str_nm_usrMgr,			},	//  2007/02/18
	//
	{	CONST_qyEventType_nm_registryAdded,			CONST_str_nm_registryAdded,	},
	{	CONST_qyEventType_nm_registryRemoved,		CONST_str_nm_registryRemoved,	},
	{	CONST_qyEventType_nm_registryModified,		CONST_str_nm_registryModified,	},
	//
	{	CONST_qyEventType_nm_netFlowWarn,			CONST_str_nm_netFlowWarn,		},
	//			//									
	//  以下是检查结果产生的事件			//									
	{	CONST_qyEventType_secChk_recent,			CONST_str_secChk_recent,		},	//		_T(  "最近使用文件"  ),				},			
	{	CONST_qyEventType_secChk_fileHistory,		CONST_str_secChk_fileHistory,		},	//	_T(  "曾使用文件"  ),				},				
	{	CONST_qyEventType_secChk_cookie,			CONST_str_secChk_cookie,		},	//		_T(  "cookie"  ),					},		
	{	CONST_qyEventType_secChk_ieHistory,			CONST_str_secChk_ieHistory,		},	//		_T(  "上网记录"  ),					},		
	{	CONST_qyEventType_secChk_shareDirectory,	CONST_str_secChk_shareDirectory,		},	//					},				
	{	CONST_qyEventType_secChk_sharePrinter,		CONST_str_secChk_sharePrinter,		},	//	_T(  "共享打印机"  ),				},				
	{	CONST_qyEventType_secChk_rasPhoneBk,		CONST_str_secChk_rasPhoneBk,		},	//	_T(  "拨号连接设置"  ),				},				
	{	CONST_qyEventType_secChk_proxyCfg,			CONST_str_secChk_proxyCfg,		},	//		_T(  "代理设置"  ),					},		
	{	CONST_qyEventType_secChk_diskFile,			CONST_str_secChk_diskFile,		},	//		_T(  "磁盘文件"  ),					},		
	{	CONST_qyEventType_secChk_diskFileDel,		CONST_str_secChk_diskFileDel,		},	//	_T(  "已删文件"  ),					},			
	//  以下是网络设备产生的事件			//									
	{	CONST_qyEventType_nms_newDev,				CONST_str_nms_newDev,		},	//			_T(  "新增设备"  ),					},	
	{	CONST_qyEventType_nms_delDev,				CONST_str_nms_delDev,		},	//			_T(  "删除设备"  ),					},	
	{	CONST_qyEventType_nms_devOnline,			CONST_str_nms_devOnline,		},	//		_T(  "设备恢复在线"  ),				},			
	{	CONST_qyEventType_nms_devOffline,			CONST_str_nms_devOffline,		},	//		_T(  "设备离线"  ),					},		
	{	CONST_qyEventType_nms_willAttack,			CONST_str_nms_willAttack,		},	//		_T(  "端口阻断"  ),					},		
	{	CONST_qyEventType_nms_stopWillAttack,		CONST_str_nms_stopWillAttack,		},	//	_T(  "停止端口阻断"  ),				},				
	{	CONST_qyEventType_nms_newConnection,		CONST_str_nms_newConnection,		},	//	_T(  "新增联接"  ),					},			
	{	CONST_qyEventType_nms_connectionModified,	CONST_str_nms_connectionModified,		},	//					},				
	//  {	CONST_qyEventType_nms_newConnectionIp,	CONST_str_nms_newConnectionIp,		},	//	_T(  "新增联接IP"  ),				},				
	//  {	CONST_qyEventType_nms_connectionIpModified,	CONST_str_nms_connectionIpModified,		},	//				},					
	{	CONST_qyEventType_nms_delConnection,		CONST_str_nms_delConnection,		},	//	_T(  "删除联接"  ),					},			
	{	CONST_qyEventType_nms_warnSpeed,			CONST_str_nms_warnSpeed,			},	//	流量报警，2006/05/30

	//  以下是应用系统操作日志			//									
	{	CONST_qyEventType_nm_logon,								CONST_str_nm_logon,		},	//				_T(  "登录"  ),					
	{	CONST_qyEventType_nm_logoff,							CONST_str_nm_logoff,		},	//			_T(  "离录"  ),						},
	{	CONST_qyEventType_nm_addUsr,							CONST_str_nm_addUsr,		},	//			_T(  "添加用户"  ),					},	
	{	CONST_qyEventType_nm_delUsr,							CONST_str_nm_delUsr,		},	//			_T(  "删除用户"  ),					},	
	{	CONST_qyEventType_nm_modifyUsr,							CONST_str_nm_modifyUsr,		},	//			_T(  "修改用户"  ),					},	
	{	CONST_qyEventType_nm_clearupEvent,						CONST_str_nm_clearupEvent,		},	//		_T(  "清空事件"  ),					},		
	{	CONST_qyEventType_nm_pzcz,								CONST_str_nm_pzcz,		},	//				_T(  "配置操作"  ),					},
	{	CONST_qyEventType_nm_sysWarn,							CONST_str_nm_sysWarn,		},	//			_T(  "系统告警"  ),					},	
	{	CONST_qyEventType_nm_viewRemoteDesktop,					CONST_str_nm_viewRemoteDesktop,		},
	{	CONST_qyEventType_nm_cancelRemoteDesktop,				CONST_str_nm_cancelRemoteDesktop,	},
	{	CONST_qyEventType_nm_denyRd,							CONST_str_nm_denyRd,		},
	{	CONST_qyEventType_nm_autoAcceptRdAndRdStart,			CONST_str_nm_autoAcceptRdAndRdStart,	},
	{	CONST_qyEventType_nm_promptToAcceptRdAndRdStart,		CONST_str_nm_promptToAcceptRdAndRdStart,  },
	{	CONST_qyEventType_nm_logonFailed,						CONST_str_nm_logonFailed,			},		//  2006/02/25
	{	CONST_qyEventType_nm_export,							CONST_str_nm_export,		},				//  导出
	{	CONST_qyEventType_nm_bak,								CONST_str_nm_bak,			},				//  备份
	{	CONST_qyEventType_nm_import,							CONST_str_nm_import,		},				//  导入
	{	CONST_qyEventType_nm_monDesktop,						CONST_str_nm_monDesktop,		},			//  实时监控桌面，2006/02/15
	{	CONST_qyEventType_nm_cancelMonDesktop,					CONST_str_nm_cancelMonDesktop,	},			//  取消实时监控桌面，2006/02/15
	{	CONST_qyEventType_nm_rdReqTimeout,						CONST_str_nm_rdReqTimeout,	},
	//
	{	CONST_qyEventType_nm_clearupImMsg,						CONST_str_nm_clearupImMsg,	},				//  清空消息
	{	CONST_qyEventType_nm_clearupImHisTask,					CONST_str_nm_clearupImHisTask,	},			//  清空历史任务

	//
	//  以下是资产管理日志			//									
	{	CONST_qyEventType_assetMgr_cpuAdd,			CONST_str_assetMgr_cpuAdd,		},	//		_T(  "新增CPU"  ),					},		
	{	CONST_qyEventType_assetMgr_cpuDel,			CONST_str_assetMgr_cpuDel,		},	//		_T(  "CPU遗失"  ),					},		
	{	CONST_qyEventType_assetMgr_memAdd,			CONST_str_assetMgr_memAdd,		},	//		_T(  "新增内存"  ),					},		
	{	CONST_qyEventType_assetMgr_memChanged,		CONST_str_assetMgr_memChanged,		},	//	_T(  "内存变更"  ),					},			
	{	CONST_qyEventType_assetMgr_biosAdd,			CONST_str_assetMgr_biosAdd,		},	//		_T(  "新增BIOS"  ),					},		
	{	CONST_qyEventType_assetMgr_biosDel,			CONST_str_assetMgr_biosDel,		},	//		_T(  "BIOS遗失"  ),					},		
	{	CONST_qyEventType_assetMgr_monitorAdd,		CONST_str_assetMgr_monitorAdd,		},	//	_T(  "新增监视器"  ),				},				
	{	CONST_qyEventType_assetMgr_monitorDel,		CONST_str_assetMgr_monitorDel,		},	//	_T(  "监视器遗失"  ),				},				
	{	CONST_qyEventType_assetMgr_ideDiskAdd,		CONST_str_assetMgr_ideDiskAdd,		},	//	_T(  "新增IDE硬盘"  ),				},				
	{	CONST_qyEventType_assetMgr_ideDiskDel,		CONST_str_assetMgr_ideDiskDel,		},	//	_T(  "IDE硬盘遗失"  ),				},				
	{	CONST_qyEventType_assetMgr_ideCdromAdd,		CONST_str_assetMgr_ideCdromAdd,		},	//	_T(  "新增DVD/CD-ROM"  ),			},					
	{	CONST_qyEventType_assetMgr_ideCdromDel,		CONST_str_assetMgr_ideCdromDel,		},	//	_T(  "DVD/CD-ROM遗失"  ),			},					
	{	CONST_qyEventType_assetMgr_usbDiskAdd,		CONST_str_assetMgr_usbDiskAdd,		},	//	_T(  "新增USB磁盘"  ),				},				
	{	CONST_qyEventType_assetMgr_usbDiskDel,		CONST_str_assetMgr_usbDiskDel,		},	//	_T(  "USB磁盘遗失"  ),				},				
	{	CONST_qyEventType_assetMgr_displayAdd,		CONST_str_assetMgr_displayAdd,		},	//	_T(  "新增显卡"  ),					},			
	{	CONST_qyEventType_assetMgr_displayDel,		CONST_str_assetMgr_displayDel,		},	//	_T(  "显卡遗失"  ),					},			
	{	CONST_qyEventType_assetMgr_networkCardAdd,	CONST_str_assetMgr_networkCardAdd,		},	//					},				
	{	CONST_qyEventType_assetMgr_networkCardDel,	CONST_str_assetMgr_networkCardDel,		},	//					},				
	//			//									
	{	CONST_qyEventType_assetMgr_softwareAdd,		CONST_str_assetMgr_softwareAdd,		},	//	_T(  "新装软件"  ),					},			
	{	CONST_qyEventType_assetMgr_softwareDel,		CONST_str_assetMgr_softwareDel,		},	//	_T(  "软件卸载"  ),					},			
	//
	{	-1,											NULL,						},
};


   //  应用系统操作使用产生的事件类型表
 QY_DMITEM  CONST_qnmEventTypeTable_op_netMc[]  =  
{
	{	CONST_qyEventType_nm_logon,								CONST_str_nm_logon,						},
	{	CONST_qyEventType_nm_logoff,							CONST_str_nm_logoff,						},
	{	CONST_qyEventType_nm_addUsr,							CONST_str_nm_addUsr,					},
	{	CONST_qyEventType_nm_delUsr,							CONST_str_nm_delUsr,					},
	{	CONST_qyEventType_nm_modifyUsr,							CONST_str_nm_modifyUsr,					},
	{	CONST_qyEventType_nm_clearupEvent,						CONST_str_nm_clearupEvent,					},
	{	CONST_qyEventType_nm_pzcz,								CONST_str_nm_pzcz,					},
	{	CONST_qyEventType_nm_sysWarn,							CONST_str_nm_sysWarn,					},
	{	CONST_qyEventType_nm_viewRemoteDesktop,					CONST_str_nm_viewRemoteDesktop,		},
	{	CONST_qyEventType_nm_cancelRemoteDesktop,				CONST_str_nm_cancelRemoteDesktop,	},
	{	CONST_qyEventType_nm_denyRd,							CONST_str_nm_denyRd,		},
	{	CONST_qyEventType_nm_autoAcceptRdAndRdStart,			CONST_str_nm_autoAcceptRdAndRdStart,	},
	{	CONST_qyEventType_nm_promptToAcceptRdAndRdStart,		CONST_str_nm_promptToAcceptRdAndRdStart,  },
	{	CONST_qyEventType_nm_logonFailed,						CONST_str_nm_logonFailed,			},	//  2006/02/25
	{	CONST_qyEventType_nm_export,							CONST_str_nm_export,		},	//  导出
	{	CONST_qyEventType_nm_bak,								CONST_str_nm_bak,			},	//  备份
	{	CONST_qyEventType_nm_import,							CONST_str_nm_import,		},	//  导入
	{	CONST_qyEventType_nm_monDesktop,						CONST_str_nm_monDesktop,		},			//  实时监控桌面，2006/02/15
	{	CONST_qyEventType_nm_cancelMonDesktop,					CONST_str_nm_cancelMonDesktop,	},			//  取消实时监控桌面，2006/02/15
	{	CONST_qyEventType_nm_rdReqTimeout,						CONST_str_nm_rdReqTimeout,	},
	//
	{	CONST_qyEventType_nm_clearupImMsg,						CONST_str_nm_clearupImMsg,	},				//  清空消息
	{	CONST_qyEventType_nm_clearupImHisTask,					CONST_str_nm_clearupImHisTask,	},			//  清空历史任务
	//
	{	-1,														NULL,						},
};


 //  netMc2系统的计算机事件类型表
 QY_DMITEM  CONST_qnmEventTypeTable_netMc2[]  =  
{
	{	CONST_qyEventType_nm_newPc,					CONST_str_nm_newPc,					},
	{	CONST_qyEventType_nm_macsModified,			CONST_str_nm_macsModified,		},
	//  {	CONST_qyEventType_nm_macsModifiedPc,		CONST_str_nm_macsModifiedPc,				},
	{	CONST_qyEventType_nm_newReg,				CONST_str_nm_newReg,					},
	{	CONST_qyEventType_nm_reReg,					CONST_str_nm_reReg,					},
	{	CONST_qyEventType_nm_qwmDel,				CONST_str_nm_qwmDel,		},
	{	CONST_qyEventType_nm_qwmDelRecovery,		CONST_str_nm_qwmDelRecovery,		},
	{	CONST_qyEventType_nm_qwmDelOffline,			CONST_str_nm_qwmDelOffline,		},
	//  {	CONST_qyEventType_nm_ipChanged,				CONST_str_nm_ipChanged,					},
	//  {	CONST_qyEventType_nm_osChanged,				CONST_str_nm_osChanged,				},
	{	CONST_qyEventType_nm_rasStart,				CONST_str_nm_rasStart,					},
	{	CONST_qyEventType_nm_rasEnd,				CONST_str_nm_rasEnd,					},
	{	CONST_qyEventType_nm_rasProhibited,			CONST_str_nm_rasProhibited,					},
	//  {	CONST_qyEventType_nm_onInternet,			CONST_str_nm_onInternet,				},
	//  {	CONST_qyEventType_nm_offInternet,			CONST_str_nm_offInternet,				},
	//  {	CONST_qyEventType_nm_wLanAdapterStart,		CONST_str_nm_wLanAdapterStart,	},	//				505				//  2010/05/20
	//  {	CONST_qyEventType_nm_wLanAdapterEnd,		CONST_str_nm_wLanAdapterEnd,	},	//					506				//  2010/05/20
	{	CONST_qyEventType_nm_wLanAdapterProhibited,	CONST_str_nm_wLanAdapterProhibited,	},	//			507				//  2010/05/20
	//
	{	CONST_qyEventType_nm_usbStorOnFor9x,		CONST_str_nm_usbStorOnFor9x,			},	//	2005/01/08			
	{	CONST_qyEventType_nm_usbStorOffFor9x,		CONST_str_nm_usbStorOffFor9x,			},	//  2005/01/08
	{	CONST_qyEventType_nm_usbStorIn,				CONST_str_nm_usbStorIn,				},	//  2005/01/07
	{	CONST_qyEventType_nm_usbStorUnallowedIn,	CONST_str_nm_usbStorUnallowedIn,			},
	{	CONST_qyEventType_nm_usbStorOut,			CONST_str_nm_usbStorOut,				},	//  2005/01/07
	{	CONST_qyEventType_nm_usbStorProhibited,		CONST_str_nm_usbStorProhibited,				},	//  2005/01/07
	{	CONST_qyEventType_nm_usbRestartToProhibit,	CONST_str_nm_usbRestartToProhibit,			},	//  2005/06/26
	{	CONST_qyEventType_nm_floppyOn,				CONST_str_nm_floppyOn,					},	//  2005/01/08
	{	CONST_qyEventType_nm_floppyOff,				CONST_str_nm_floppyOff,					},	//  2005/01/08
	{	CONST_qyEventType_nm_cdromOn,				CONST_str_nm_cdromOn,					},	//  2005/01/08
	{	CONST_qyEventType_nm_cdromOff,				CONST_str_nm_cdromOff,					},	//  2005/01/08
	//
	{	CONST_qyEventType_nm_safeModeOn,			CONST_str_nm_safeModeOn,				},	//  2005/06/25
	{	CONST_qyEventType_nm_safeModeOff,			CONST_str_nm_safeModeOff,				},	//  2005/06/25
	{	CONST_qyEventType_nm_netShareMgr,			CONST_str_nm_netShareMgr,		},	//  
	//
	{	CONST_qyEventType_nm_ucBlueToothProhibited,	CONST_str_nm_ucBlueToothProhibited,		},							//  2010/08/18
	{	CONST_qyEventType_nm_ucInfraredProhibited,	CONST_str_nm_ucInfraredProhibited,		},							//  2010/08/18
	{	CONST_qyEventType_nm_uc1394Prohibited,		CONST_str_nm_uc1394Prohibited,			},							//  2010/08/18
	{	CONST_qyEventType_nm_sdHostAdapterProhibited,	CONST_str_nm_sdHostAdapterProhibited,	},						//  2011/08/28
	//
	{	CONST_qyEventType_nm_devIn,					CONST_str_nm_devIn,						},
	{	CONST_qyEventType_nm_devOut,				CONST_str_nm_devOut,					},
	{	CONST_qyEventType_nm_devProhibited,			CONST_str_nm_devProhibited,				},
	{	CONST_qyEventType_nm_devEnabled,			CONST_str_nm_devEnabled,				},

	//
	{	CONST_qyEventType_nm_strangePc,				CONST_str_nm_strangePc,					},
	{	CONST_qyEventType_nm_strangePcUnderCtrl,	CONST_str_nm_strangePcUnderCtrl,		},
	{	CONST_qyEventType_nm_strangePcOffline,		CONST_str_nm_strangePcOffline,			},
	//  {	CONST_qyEventType_nm_pcUnchked,				CONST_str_nm_pcUnchked,				},
	//  {	CONST_qyEventType_nm_pcAttacked,			CONST_str_nm_pcAttacked,			},
	{	CONST_qyEventType_nm_strangeIp,				CONST_str_nm_strangeIp,					},
	//  {	CONST_qyEventType_nm_delPc,					CONST_str_nm_delPc,					},
	{	CONST_qyEventType_nm_proxyServerSet,		CONST_str_nm_proxyServerSet,			},
	{	CONST_qyEventType_nm_proxyServerClear,		CONST_str_nm_proxyServerClear,			},
	//
	{	CONST_qyEventType_nm_printerJob,			CONST_str_nm_printerJob,				},
	//  {	CONST_qyEventType_nm_fileMon,				CONST_str_nm_fileMon,				},
	{	CONST_qyEventType_nm_fileAdded,				CONST_str_nm_fileAdded,					},
	{	CONST_qyEventType_nm_fileRemoved,			CONST_str_nm_fileRemoved,				},
	{	CONST_qyEventType_nm_fileModified,			CONST_str_nm_fileModified,				},
	{	CONST_qyEventType_nm_fileRenamed,			CONST_str_nm_fileRenamed,				},
	//
	{	CONST_qyEventType_nm_processMgr,			CONST_str_nm_processMgr,				},
	//
	{	CONST_qyEventType_nm_usrMgr,				CONST_str_nm_usrMgr,			},	//  2007/02/18
	//
	{	CONST_qyEventType_nm_registryAdded,			CONST_str_nm_registryAdded,	},
	{	CONST_qyEventType_nm_registryRemoved,		CONST_str_nm_registryRemoved,	},
	{	CONST_qyEventType_nm_registryModified,		CONST_str_nm_registryModified,	},
	//
	{	CONST_qyEventType_nm_netFlowWarn,			CONST_str_nm_netFlowWarn,		},
	//
	{	-1,											NULL,					},
};


 //  nms系统的计算机事件类型表
 QY_DMITEM  CONST_qnmEventTypeTable_nms[]  =  
{
	{	CONST_qyEventType_nm_newPc,					CONST_str_nm_newPc,					},
	{	CONST_qyEventType_nm_macsModified,			_T(  "网卡变更"  ),					},
	{	CONST_qyEventType_nm_newReg,				CONST_str_nm_newReg,					},
	{	CONST_qyEventType_nm_reReg,					CONST_str_nm_reReg,					},
	{	CONST_qyEventType_nm_ipChanged,				CONST_str_nm_ipChanged,					},
	{	-1,											NULL,					},
};


  //  nms系统的网络设备事件类型表
 QY_DMITEM  CONST_qnmEventTypeTable_nmsNetDev[]  =  
{
	{	CONST_qyEventType_nms_newDev,				CONST_str_nms_newDev,					},
	{	CONST_qyEventType_nms_delDev,				CONST_str_nms_delDev,					},
	{	CONST_qyEventType_nms_devOnline,			CONST_str_nms_devOnline,				},
	{	CONST_qyEventType_nms_devOffline,			CONST_str_nms_devOffline,					},
	{	CONST_qyEventType_nms_willAttack,			CONST_str_nms_willAttack,					},
	{	CONST_qyEventType_nms_stopWillAttack,		CONST_str_nms_stopWillAttack,				},
	{	CONST_qyEventType_nms_newConnection,		CONST_str_nms_newConnection,					},
	{	CONST_qyEventType_nms_connectionModified,	CONST_str_nms_connectionModified,					},
	//  {	CONST_qyEventType_nms_newConnectionIp,		_T(  "新增联接IP"  ),				},
	//  {	CONST_qyEventType_nms_connectionIpModified,	_T(  "联接IP变更"  ),				},
	{	CONST_qyEventType_nms_delConnection,		CONST_str_nms_delConnection,					},
	{	CONST_qyEventType_nms_warnSpeed,			CONST_str_nms_warnSpeed,			},	//	流量报警，2006/05/30

	{	-1,											NULL,					},
};



 //  检查中心的全部事件列表
 QY_DMITEM  CONST_qnmEventTypeTable_secChk[]  =
{
	{	CONST_qyEventType_nm_newPc,					CONST_str_nm_newPc,					},
	{	CONST_qyEventType_nm_macsModified,			CONST_str_nm_macsModified,		},
	//  {	CONST_qyEventType_nm_macsModifiedPc,		CONST_str_nm_macsModifiedPc,				},
	{	CONST_qyEventType_nm_newReg,				CONST_str_nm_newReg,					},
	{	CONST_qyEventType_nm_reReg,					CONST_str_nm_reReg,					},
	//
 	//  {	CONST_qyEventType_secChk_recent,				CONST_str_secChk_recent,			},
	//  {	CONST_qyEventType_secChk_fileHistory,			CONST_str_secChk_fileHistory,				},
	//  {	CONST_qyEventType_secChk_cookie,				CONST_str_secChk_cookie,				},
	//  {	CONST_qyEventType_secChk_ieHistory,				CONST_str_secChk_ieHistory,				},
	//  {	CONST_qyEventType_secChk_shareDirectory,		CONST_str_secChk_shareDirectory,					},
	//  {	CONST_qyEventType_secChk_sharePrinter,			CONST_str_secChk_sharePrinter,				},
	//  {	CONST_qyEventType_secChk_rasPhoneBk,			CONST_str_secChk_rasPhoneBk,				    },
	//  {	CONST_qyEventType_secChk_proxyCfg,				CONST_str_secChk_proxyCfg,				},
	//  {	CONST_qyEventType_secChk_diskFile,				CONST_str_secChk_diskFile,					},
	//  {	CONST_qyEventType_secChk_diskFileDel,			CONST_str_secChk_diskFileDel,					},
	//  {	CONST_qyEventType_nm_onInternet,				CONST_str_nm_onInternet,			},
	{	-1,												NULL,					},
};


 QY_DMITEM  CONST_secChkEventTypeTable_secChk[]  =
{
 	{	CONST_qyEventType_secChk_recent,				CONST_str_secChk_recent,					},
	{	CONST_qyEventType_secChk_fileHistory,			CONST_str_secChk_fileHistory,				},
	{	CONST_qyEventType_secChk_cookie,				CONST_str_secChk_cookie,					},
	{	CONST_qyEventType_secChk_ieHistory,				CONST_str_secChk_ieHistory,					},
	{	CONST_qyEventType_secChk_shareDirectory,		CONST_str_secChk_shareDirectory,			},
	{	CONST_qyEventType_secChk_sharePrinter,			CONST_str_secChk_sharePrinter,				},
	{	CONST_qyEventType_secChk_rasPhoneBk,			CONST_str_secChk_rasPhoneBk,			    },
	{	CONST_qyEventType_secChk_proxyCfg,				CONST_str_secChk_proxyCfg,					},
	{	CONST_qyEventType_secChk_diskFile,				CONST_str_secChk_diskFile,					},
	{	CONST_qyEventType_secChk_diskFileDel,			CONST_str_secChk_diskFileDel,				},
	{	CONST_qyEventType_nm_onInternet,				CONST_str_nm_onInternet,					},	// 注意该事件，在安检和内网管理事件里都出现，在安检表里和事件表里都有
	{	-1,												NULL,					},
};



 QY_DMITEM  CONST_secChkEventTypeTable_netMc2[]  =
{
 	{	CONST_qyEventType_secChk_recent,				CONST_str_secChk_recent,			},
	{	CONST_qyEventType_secChk_fileHistory,			CONST_str_secChk_fileHistory,				},
	{	CONST_qyEventType_secChk_cookie,				CONST_str_secChk_cookie,				},
	{	CONST_qyEventType_secChk_ieHistory,				CONST_str_secChk_ieHistory,				},
	{	CONST_qyEventType_secChk_shareDirectory,		CONST_str_secChk_shareDirectory,					},
	{	CONST_qyEventType_secChk_sharePrinter,			CONST_str_secChk_sharePrinter,				},
	{	-1,												NULL,					},
};



  //  事件类型表
 QY_DMITEM  CONST_qnmEventTypeTable_assetMgr[]  =  
{
	{	CONST_qyEventType_nm_newPc,					CONST_str_nm_newPc,					},
	{	CONST_qyEventType_nm_macsModified,			CONST_str_nms_macsModified,					},
	{	CONST_qyEventType_nm_newReg,				CONST_str_nm_newReg,					},
	{	CONST_qyEventType_nm_reReg,					CONST_str_nm_reReg,					},
	{	CONST_qyEventType_nm_ipChanged,				CONST_str_nm_ipChanged,					},
	//
	{	CONST_qyEventType_assetMgr_cpuAdd,			CONST_str_assetMgr_cpuAdd,					},
	{	CONST_qyEventType_assetMgr_cpuDel,			CONST_str_assetMgr_cpuDel,					},
	{	CONST_qyEventType_assetMgr_memAdd,			CONST_str_assetMgr_memAdd,					},
	{	CONST_qyEventType_assetMgr_memChanged,		CONST_str_assetMgr_memChanged,					},
	{	CONST_qyEventType_assetMgr_biosAdd,			CONST_str_assetMgr_biosAdd,					},
	{	CONST_qyEventType_assetMgr_biosDel,			CONST_str_assetMgr_biosDel,					},
	{	CONST_qyEventType_assetMgr_monitorAdd,		CONST_str_assetMgr_monitorAdd,				},
	{	CONST_qyEventType_assetMgr_monitorDel,		CONST_str_assetMgr_monitorDel,				},
	{	CONST_qyEventType_assetMgr_ideDiskAdd,		CONST_str_assetMgr_ideDiskAdd,				},
	{	CONST_qyEventType_assetMgr_ideDiskDel,		CONST_str_assetMgr_ideDiskDel,				},
	{	CONST_qyEventType_assetMgr_ideCdromAdd,		CONST_str_assetMgr_ideCdromAdd,			},
	{	CONST_qyEventType_assetMgr_ideCdromDel,		CONST_str_assetMgr_ideCdromDel,			},
	{	CONST_qyEventType_assetMgr_usbDiskAdd,		CONST_str_assetMgr_usbDiskAdd,				},
	{	CONST_qyEventType_assetMgr_usbDiskDel,		CONST_str_assetMgr_usbDiskDel,				},
	{	CONST_qyEventType_assetMgr_displayAdd,		CONST_str_assetMgr_displayAdd,					},
	{	CONST_qyEventType_assetMgr_displayDel,		CONST_str_assetMgr_displayDel,					},
	{	CONST_qyEventType_assetMgr_networkCardAdd,	CONST_str_assetMgr_networkCardAdd,					},
	{	CONST_qyEventType_assetMgr_networkCardDel,	CONST_str_assetMgr_networkCardDel,					},
	//
	{	CONST_qyEventType_assetMgr_softwareAdd,		CONST_str_assetMgr_softwareAdd,					},
	{	CONST_qyEventType_assetMgr_softwareDel,		CONST_str_assetMgr_softwareDel,					},
	{	-1,											NULL,					},
};


#if  0
 //  
 QY_DMITEM  CONST_qnmEventTypeTable_null[]  =  
{
	{	-1,											NULL,					},
};
#endif

