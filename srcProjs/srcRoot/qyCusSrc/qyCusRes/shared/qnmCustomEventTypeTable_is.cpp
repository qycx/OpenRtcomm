
#include	"stdafx.h"
#include	<tchar.h>
//  #include	"qyCommon.h"
//  #include	"resource_main.h"
//  #include	"afxres.h"

#include	"qyCusResCommon.h"
//  #include	"qyCusResPublic.h" 

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_is.h"

  //  事件类型总表
 QY_DMITEM  CONST_qnmEventTypeTable0_is[]  =  
{
	//
	{	CONST_qyEventType_nm_newReg,				CONST_str_nm_newReg,		},	//			_T(  "首次注册"  ),					},	
	{	CONST_qyEventType_nm_reReg,					CONST_str_nm_reReg,		},	//				_T(  "重新注册"  ),					},


	//  以下是应用系统操作日志			//									
	{	CONST_qyEventType_nm_logon,								CONST_str_nm_logon,		},	//				_T(  "登录"  ),					
	{	CONST_qyEventType_nm_logoff,							CONST_str_nm_logoff,		},	//			_T(  "离录"  ),						},
	{	CONST_qyEventType_nm_addUsr,							CONST_str_nm_addUsr,		},	//			_T(  "添加用户"  ),					},	
	{	CONST_qyEventType_nm_delUsr,							CONST_str_nm_delUsr,		},	//			_T(  "删除用户"  ),					},	
	{	CONST_qyEventType_nm_modifyUsr,							CONST_str_nm_modifyUsr,		},	//			_T(  "修改用户"  ),					},	
	{	CONST_qyEventType_nm_clearupEvent,						CONST_str_nm_clearupEvent,		},	//		_T(  "清空事件"  ),					},		
	{	CONST_qyEventType_nm_pzcz,								CONST_str_nm_pzcz,		},	//				_T(  "配置操作"  ),					},
	{	CONST_qyEventType_nm_sysWarn,							CONST_str_nm_sysWarn,		},	//			_T(  "系统告警"  ),					},	
	{	CONST_qyEventType_nm_logonFailed,						CONST_str_nm_logonFailed,			},		//  2006/02/25
	{	CONST_qyEventType_nm_export,							CONST_str_nm_export,		},				//  导出
	{	CONST_qyEventType_nm_bak,								CONST_str_nm_bak,			},				//  备份
	{	CONST_qyEventType_nm_import,							CONST_str_nm_import,		},				//  导入
	//
	{	CONST_qyEventType_nm_clearupImMsg,						CONST_str_nm_clearupImMsg,	},				//  清空消息
	{	CONST_qyEventType_nm_clearupImHisTask,					CONST_str_nm_clearupImHisTask,	},			//  清空历史任务

	//
	//
	{	CONST_qyEventType_is_newMessenger,			CONST_str_is_newMessenger,			},
	{	CONST_qyEventType_is_messengerLogon,		CONST_str_is_messengerLogon,			},
	{	CONST_qyEventType_is_messengerLogoff,		CONST_str_is_messengerLogoff,			},
	{	CONST_qyEventType_is_connErr,				CONST_str_is_connErr,					},
	{	CONST_qyEventType_is_memoryErr,				CONST_str_is_memoryErr,			},
	{	CONST_qyEventType_im_daemonStart,			CONST_str_is_daemonStart,			},
	{	CONST_qyEventType_im_daemonStop,			CONST_str_is_daemonStop,			},

	//
	{	-1,											NULL,						},
};


 QY_DMITEM  CONST_qnmEventTypeTable_op_is[]  =  
{
	{	CONST_qyEventType_nm_logon,								CONST_str_nm_logon,						},
	{	CONST_qyEventType_nm_logoff,							CONST_str_nm_logoff,					},
	{	CONST_qyEventType_nm_addUsr,							CONST_str_nm_addUsr,					},
	{	CONST_qyEventType_nm_delUsr,							CONST_str_nm_delUsr,					},
	{	CONST_qyEventType_nm_modifyUsr,							CONST_str_nm_modifyUsr,					},
	{	CONST_qyEventType_nm_clearupEvent,						CONST_str_nm_clearupEvent,				},
	//  {	CONST_qyEventType_nm_pzcz,								CONST_str_nm_pzcz,					},
	//  {	CONST_qyEventType_nm_sysWarn,							CONST_str_nm_sysWarn,				},
	{	CONST_qyEventType_nm_logonFailed,						CONST_str_nm_logonFailed,				},	//  2006/02/25
	{	CONST_qyEventType_nm_export,							CONST_str_nm_export,					},	//  导出
	{	CONST_qyEventType_nm_bak,								CONST_str_nm_bak,						},	//  备份
	{	CONST_qyEventType_nm_import,							CONST_str_nm_import,					},	//  导入
	//
	{	CONST_qyEventType_nm_clearupImMsg,						CONST_str_nm_clearupImMsg,				},				//  清空消息
	{	CONST_qyEventType_nm_clearupImHisTask,					CONST_str_nm_clearupImHisTask,			},			//  清空历史任务
	//
	{	-1,														NULL,									},
};



 QY_DMITEM  CONST_qnmEventTypeTable_misMgr[]  =  
{
	{	CONST_qyEventType_is_newMessenger,			CONST_str_is_newMessenger,			},
	{	CONST_qyEventType_is_messengerLogon,		CONST_str_is_messengerLogon,			},
	{	CONST_qyEventType_is_messengerLogoff,		CONST_str_is_messengerLogoff,			},
	{	CONST_qyEventType_is_connErr,				CONST_str_is_connErr,					},
	{	CONST_qyEventType_is_memoryErr,				CONST_str_is_memoryErr,			},
	{	CONST_qyEventType_im_daemonStart,			CONST_str_is_daemonStart,			},
	{	CONST_qyEventType_im_daemonStop,			CONST_str_is_daemonStop,			},

	
	{	-1,											NULL,					},
};



    //  2011/08/08
  QY_DMITEM  CONST_policyAvLevelTable_basic[]  =
{
	{	CONST_policyAvLevel_240p,				CONST_IDC_BUTTON_set240pSettings,		},
	{	CONST_policyAvLevel_480p,				CONST_IDC_BUTTON_set480pSettings,	},
	{	CONST_policyAvLevel_576p,					CONST_IDC_BUTTON_set576pSettings,	},

	{	-1,				NULL,				},
};


    //  2011/08/08
  QY_DMITEM  CONST_policyAvLevelTable_standard[]  =
{
	{	CONST_policyAvLevel_240p,					CONST_IDC_BUTTON_set240pSettings,		},
	{	CONST_policyAvLevel_480p,					CONST_IDC_BUTTON_set480pSettings,	},
	{	CONST_policyAvLevel_576p,					CONST_IDC_BUTTON_set576pSettings,	},
	{	CONST_policyAvLevel_720p,					CONST_IDC_BUTTON_set720pSettings,	},
	//
	{	-1,				NULL,				},
};

    //  2011/08/08
  QY_DMITEM  CONST_policyAvLevelTable_high[]  =
{
	{	CONST_policyAvLevel_240p,					CONST_IDC_BUTTON_set240pSettings,		},
	{	CONST_policyAvLevel_480p,					CONST_IDC_BUTTON_set480pSettings,	},
	{	CONST_policyAvLevel_576p,					CONST_IDC_BUTTON_set576pSettings,	},
	{	CONST_policyAvLevel_720p,					CONST_IDC_BUTTON_set720pSettings,	},
	{	CONST_policyAvLevel_1080p,					CONST_IDC_BUTTON_set1080pSettings,},
	//
	{	-1,				NULL,				},
};


  //  2014/11/15
  QY_DMITEM  CONST_policyAvLevelTable_mosaic_video[]  =
{
	{	CONST_policyAvLevel_848x480,					CONST_IDC_BUTTON_848x480Settings,		},
	{	-1,				NULL,				},
};

  QY_DMITEM  CONST_policyAvLevelTable_mosaic_resource[]  =
{
	{	CONST_policyAvLevel_dev_5fps1,				CONST_IDC_BUTTON_setDev5fpsSettings1,		},
	{	-1,											NULL,								},
};

  //  2016/04/06
  QY_DMITEM  CONST_policyAvLevelTable_slave_video[]  =
{
	{	CONST_policyAvLevel_240p,					CONST_IDC_BUTTON_set240pSettings,		},
	//
	{	-1,											NULL,								},
};


  //
  QY_DMITEM  CONST_policyAvLevelTable_screen_basic[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_5fps,				CONST_IDC_BUTTON_setDev5fpsSettings,},
	//  2012/10/29
	{	CONST_policyAvLevel_dev_5fps1,				CONST_IDC_BUTTON_setDev5fpsSettings1,},

	{	-1,											NULL,								},
};
  QY_DMITEM  CONST_policyAvLevelTable_screen_standard[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_5fps,				CONST_IDC_BUTTON_setDev5fpsSettings,},
	//  2012/10/29
	{	CONST_policyAvLevel_dev_5fps1,				CONST_IDC_BUTTON_setDev5fpsSettings1,},
	{	CONST_policyAvLevel_dev_5fps2,				CONST_IDC_BUTTON_setDev5fpsSettings2,},
#if 0 
	{	CONST_policyAvLevel_dev_5fps3,				CONST_IDC_BUTTON_setDev5fpsSettings3,},
	{	CONST_policyAvLevel_dev_5fps4,				CONST_IDC_BUTTON_setDev5fpsSettings4,},
	{	CONST_policyAvLevel_dev_5fps5,				CONST_IDC_BUTTON_setDev5fpsSettings5,},
#endif
	//
	{	-1,											NULL,								},
};
  QY_DMITEM  CONST_policyAvLevelTable_screen_high[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_5fps,				CONST_IDC_BUTTON_setDev5fpsSettings,},
	//  2012/10/29
	{	CONST_policyAvLevel_dev_5fps1,				CONST_IDC_BUTTON_setDev5fpsSettings1,},
	{	CONST_policyAvLevel_dev_5fps2,				CONST_IDC_BUTTON_setDev5fpsSettings2,},
#if  0
	{	CONST_policyAvLevel_dev_5fps3,				CONST_IDC_BUTTON_setDev5fpsSettings3,},
	{	CONST_policyAvLevel_dev_5fps4,				CONST_IDC_BUTTON_setDev5fpsSettings4,},
	{	CONST_policyAvLevel_dev_5fps5,				CONST_IDC_BUTTON_setDev5fpsSettings5,},
#endif
	//
	{	-1,											NULL,								},
};


 QY_DMITEM  CONST_usLayoutTypeTable[]  =
{
	{		CONST_usLayoutType_null,							CONST_str_layout_auto,				},
	{		CONST_usLayoutType_dialog,							CONST_str_layout_dialog,			},
	{		CONST_usLayoutType_conference,						CONST_str_layout_conference,		},
	{		CONST_usLayoutType_training,						CONST_str_layout_training,			},
	{		CONST_usLayoutType_videoOnly,						CONST_str_layout_videoOnly,		},
	{		CONST_usLayoutType_resourceOnly,					CONST_str_layout_resourceOnly,		},
	{		-1,						},
};

 QY_DMITEM  CONST_usLayoutTypeTable_resource[]  =
{
	{		CONST_usLayoutType_null,							CONST_str_layout_auto,				},
	{		CONST_usLayoutType_dialog,							CONST_str_layout_dialog,			},
	{		CONST_usLayoutType_resourceOnly,					CONST_str_layout_resourceOnly,		},
	{		-1,						},
};

 QY_DMITEM	CONST_iTargetUsageTable[]  =
{
	{	CONST_iTargetUsage_bestQuality,				CONST_str_bestQuality,		},
	{	CONST_iTargetUsage_balanced,				CONST_str_balanced,			},
	{	CONST_iTargetUsage_bestSpeed,				CONST_str_bestSpeed,		},
	{	-1,				NULL,				},
};

 //
 QY_DMITEM  CONST_iAvgBitrateTable_h264_720p[]  =  
{
	{		CONST_iAvgBitrate_1_5m,						_T(  "1.5Mbps"  ),			},
	{		CONST_iAvgBitrate_1_7m,						_T(  "1.7Mbps"  ),			},
	{		CONST_iAvgBitrate_2m,						_T(  "2.0Mbps"  ),			},
	{	-1,											NULL,					},
};

 //
  QY_DMITEM  CONST_iAvgBitrateTable_h264_1080p[]  =  
{
	{		CONST_iAvgBitrate_3_5m,						_T(  "3.5Mbps"  ),			},
	{		CONST_iAvgBitrate_4m,						_T(  "4Mbps"  ),			},
	{	-1,											NULL,					},
};

//
   //
 QY_DMITEM  CONST_iAvgBitrateTable_h265_720p[]  =  
{
	{		CONST_iAvgBitrate_1m,						_T(  "1.0Mbps"  ),			},
	{	-1,											NULL,					},
};

 //
  QY_DMITEM  CONST_iAvgBitrateTable_h265_1080p[]  =  
{
	{		CONST_iAvgBitrate_2m,						_T(  "2.0Mbps"  ),			},
	{	-1,											NULL,					},
};



//  
#if  0
 QY_DMITEM  CONST_qnmEventTypeTable_null[]  =  
{
	{	-1,											NULL,					},
};
#endif

