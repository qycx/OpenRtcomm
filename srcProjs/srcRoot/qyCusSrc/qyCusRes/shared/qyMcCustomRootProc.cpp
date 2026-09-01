
#include	"stdafx.h"
#include	<tchar.h>
#include	<commctrl.h>
//  #include	"myresource_main.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
//
#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_netMc.h"


 QY_COLUMNINFO  sQyMcRootListColumns[]  =  
{
		{	0,	CONST_str_mingChen,			0,	LVCFMT_LEFT, 	120,	1	},
		{	0,	CONST_str_miaoShu,			0,	LVCFMT_LEFT,	200,	1	},
		{	-1,															},
};

  QY_COLUMNINFO  CONST_networkViewTable[]  =
{
		{	0,	CONST_str_sheBeiXingHao,		0,	LVCFMT_LEFT, 	120,	1  },
		{	0,	_T(  "IP"  ),					0,	LVCFMT_LEFT, 	110,	1  },
		{	0,	CONST_str_bieMing,				0,	LVCFMT_LEFT,	90,		1  },
		{	0,	CONST_str_shiYongDiDian,		0,	LVCFMT_LEFT,	120,	1  },
		{	0,	CONST_str_shenHeShiJian,		0,	LVCFMT_LEFT,	120,	1  },
		{	0,	CONST_str_zuiJinSaoMiaoShiJian,	0,	LVCFMT_LEFT,	120,	1  },
		{	0,	_T(  "MAC"  ),					0,	LVCFMT_LEFT,	120,	1  },
		{	-1,	_T(  ""  ),						0,	LVCFMT_LEFT, 	120,	1  },
};
  
 QY_COLUMNINFO  CONST_switchViewTable[]  =
{
		{	0,	CONST_str_duanKou,					0,	LVCFMT_LEFT, 	40,		1  },
		{	0,	_T(  "MAC" ),						0,	LVCFMT_LEFT, 	90,		1  },
		{	0,	CONST_str_lianJieSheBeiMiaoShu_IP,	0,	LVCFMT_LEFT, 	240,	1  },
		{	0,	CONST_str_duanKouZhuangTai,			0,	LVCFMT_LEFT, 	60,		1  },
		{	0,	CONST_str_shiFouJieRu,				0,	LVCFMT_LEFT, 	60,		1  },
		{	0,	CONST_str_duanKouBangDingZhuangTai,	0,	LVCFMT_LEFT, 	100,		1  },
		{	0,	CONST_str_bangDingLeiXing,			0,	LVCFMT_LEFT, 	60,		1  },
		{	0,	CONST_str_shenHeShiJian,			0,	LVCFMT_LEFT, 	100,	1  },
		{	0,	CONST_str_zuiJinSaoMiaoShiJian,		0,	LVCFMT_LEFT, 	100,	1  },
		{	-1,	_T(  "" ),							0,	LVCFMT_LEFT, 	120,	1  },
};

 QY_COLUMNINFO  CONST_switchPortViewTable[]  =
{
		{	0,	_T(  "MAC"  ),						0,	LVCFMT_LEFT, 	110,	1  },
		{	0,	CONST_str_lianJieSheBeiMiaoShu_IP,	0,	LVCFMT_LEFT, 	350,	1  },
		{	0,	CONST_str_shiFouJieRu,				0,	LVCFMT_LEFT, 	60,		1  },
		{	0,	CONST_str_duanKouBangDingZhuangTai,	0,	LVCFMT_LEFT, 	100,	1  },
		{	0,	CONST_str_bangDingLeiXing,			0,	LVCFMT_LEFT, 	60,		1  },
		{	0,	CONST_str_shenHeShiJian,			0,	LVCFMT_LEFT, 	100,	1  },
		{	0,	CONST_str_zuiJinSaoMiaoShiJian,		0,	LVCFMT_LEFT, 	100,	1  },
		{	-1,	_T(  ""  ),							0,	LVCFMT_LEFT, 	120,	1  },
};

 QY_COLUMNINFO  CONST_switchUsrConnectionViewTable[]  =
{
		{	0,	CONST_str_duanKou,					0,	LVCFMT_LEFT, 	40,		1  },
		{	0,	_T(  "MAC" ),						0,	LVCFMT_LEFT, 	90,		1  },
		{	0,	_T(  "IP"  ),						0,	LVCFMT_LEFT, 	100,	1  },
		{	0,	CONST_str_jiSuanJiMing,				0,	LVCFMT_LEFT, 	100,	1  },
		{	0,	CONST_str_zuiJinLianXiShiJian,		0,	LVCFMT_LEFT, 	100,	1  },
		{	-1,	_T(  "" ),							0,	LVCFMT_LEFT, 	120,	1  },
};

 QY_COLUMNINFO  CONST_switchPortUsrConnectionViewTable[]  =
{	
		{	0,	_T(  "MAC" ),						0,	LVCFMT_LEFT, 	90,		1  },
		{	0,	_T(  "IP"  ),						0,	LVCFMT_LEFT, 	100,	1  },
		{	0,	CONST_str_jiSuanJiMing,				0,	LVCFMT_LEFT, 	100,	1  },
		{	0,	CONST_str_zuiJinLianXiShiJian,		0,	LVCFMT_LEFT, 	100,	1  },
		{	-1,	_T(  "" ),							0,	LVCFMT_LEFT, 	120,	1  },

};

 QY_COLUMNINFO  CONST_switchNetworkSpeedViewTable[]  =
{
		{	0,	CONST_str_duanKou,					0,	LVCFMT_RIGHT, 	40,		1	},
		{	0,	CONST_str_daiKuan_kbps,				0,	LVCFMT_RIGHT, 	75,		1	},
		{	0,	CONST_str_ruLiuLiang_kbps,			0,	LVCFMT_RIGHT, 	85,		1	},
		{	0,	CONST_str_chuLiuLiang_kbps,			0,	LVCFMT_RIGHT, 	85,		1	},
		{	0,	CONST_str_ruZiJieShu,				0,	LVCFMT_RIGHT, 	70,		1	},
		{	0,	CONST_str_chuZiJieShu,				0,	LVCFMT_RIGHT, 	70,		1	},
		{	0,	CONST_str_saoMiaoShiJian,			0,	LVCFMT_RIGHT,	130,	1	},
		{	-1,	_T(  "" ),													},
};

 QY_COLUMNINFO  CONST_switchPortNetworkSpeedViewTable[]  =
{
		{	0,	CONST_str_daiKuan_kbps,				0,	LVCFMT_RIGHT, 	75,		1	},
		{	0,	CONST_str_ruLiuLiang_kbps,			0,	LVCFMT_RIGHT, 	85,		1	},
		{	0,	CONST_str_chuLiuLiang_kbps,			0,	LVCFMT_RIGHT, 	85,		1	},
		{	0,	CONST_str_ruZiJieShu,				0,	LVCFMT_RIGHT, 	70,		1	},
		{	0,	CONST_str_chuZiJieShu,				0,	LVCFMT_RIGHT, 	70,		1	},
		{	0,	CONST_str_saoMiaoShiJian,			0,	LVCFMT_RIGHT,	130,	1	},
		{	-1,	_T(  "" ),													},
};


 //  qyMcMainAssetProc.cpp
  QY_COLUMNINFO  COSNT_col4ListColumns_netMc[]  =  
{
		{	0,	CONST_str_xingMing,					0,	LVCFMT_LEFT, 	120,	1	},
		{	1,	_T( "IP"  ),						0,	LVCFMT_LEFT,	120,	1	},
		{	1,	_T( "MAC"  ),						0,	LVCFMT_LEFT,	120,	1	},
		{	-1,															},
};

  QY_COLUMNINFO  COSNT_col4ListColumns_is[]  =  
{
		{	0,	CONST_str_xingMing,					0,	LVCFMT_LEFT, 	120,	1	},
		{	1,	_T( "IP"  ),						0,	LVCFMT_LEFT,	120,	1	},
		{	0,	CONST_str_servName,					0,	LVCFMT_LEFT,	0,		1,	},
		{	1,	CONST_str_idStr,					0,	LVCFMT_LEFT,	120,	1	},
		{	-1,															},
};


 QY_COLUMNINFO  COSNT_unRegGrpMemListColumns_netMc[]  =  
{
		{	0,	_T( "IP" ),							0,	LVCFMT_LEFT, 	120,	1	},
		{	1,	_T( "MAC"  ),						0,	LVCFMT_LEFT,	120,	1	},
		{	-1,															},
};


 QY_COLUMNINFO  COSNT_unRegGrpMemListColumns_is[]  =  
{
		{	1,	CONST_str_idStr,					0,	LVCFMT_LEFT,	120,	1	},
		{	0,	_T( "IP" ),							0,	LVCFMT_LEFT, 	120,	1	},
		{	-1,															},
};

 QY_COLUMNINFO  COSNT_imGrpListColumns_is[]  =  
{
		{	0,	CONST_str_mingChen,					0,	LVCFMT_LEFT, 	120,	1	},
		{	1,	CONST_str_idStr_grp,				0,	LVCFMT_LEFT,	120,	1	},
		{	1,	CONST_str_xuHao,					0,	LVCFMT_LEFT,	0,		1,	},
		{	-1,															},
};

 //
 QY_COLUMNINFO  CONST_imGrpMemListColumns_isMgr[]  =
{
		{	1,						CONST_str_idStr,					0,	LVCFMT_LEFT,	130,	1	},
		{	1,						CONST_str_xuHao,					0,	LVCFMT_LEFT,	0,		1,	},
		{	CONST_resId_status,		CONST_str_zhuangTai,				0,	LVCFMT_LEFT,	270,		1,	},
		{	-1,		},
};


 QY_COLUMNINFO  CONST_imGrpMemListColumns_isCli[]  =
{
		{	0,						CONST_str_name,						0,	LVCFMT_LEFT,	200,		1,	},
		{	1,						CONST_str_idStr,					0,	LVCFMT_LEFT,	40,			1,	},
		{	1,						CONST_str_xuHao,					0,	LVCFMT_LEFT,	0,			1,	},
		{	CONST_resId_status,		CONST_str_zhuangTai,				0,	LVCFMT_LEFT,	80,			1,	},
		{	-1,		},
};


 //
 QY_COLUMNINFO  COSNT_othersGrpMemListColumns[]  =  
{
		{	1,	_T( "MAC"  ),						0,	LVCFMT_LEFT,	120,	1	},
		{	1,	CONST_str_danWei,					0,	LVCFMT_LEFT,	120,	1	},
		{	1,	CONST_str_buMen,					0,	LVCFMT_LEFT,	120,	1	},
		{	1,	CONST_str_shiYongRen,				0,	LVCFMT_LEFT,	120,	1	},
		{	-1,															},
};


 //
  //
 QY_COLUMNINFO  CONST_confListColumns_isMgr[]  =
{
		{	1,						CONST_str_xuHao,					0,	LVCFMT_LEFT,	0,		1,	},
		{	1,						CONST_str_idStr_mcu,				0,	LVCFMT_LEFT,	150,	1	},
		{	1,						CONST_str_idStr_conf,				0,	LVCFMT_LEFT,	100,	1	},
		{	1,						CONST_str_conf_desc,				0,	LVCFMT_LEFT,	200,	1	},
		{	1,						CONST_str_idStr_initiator,			0,	LVCFMT_LEFT,	100,	1	},
		{	1,						CONST_str_initiator_desc,			0,	LVCFMT_LEFT,	200,	1	},
		{	1,						CONST_str_startTime,				0,	LVCFMT_LEFT,	130,	1	},
		
		//
		{	CONST_resId_status,		CONST_str_zhuangTai,				0,	LVCFMT_LEFT,	100,	1,	},
		//
		{	1,						CONST_str_msgrIo,					0,	LVCFMT_LEFT,	300,	1,	},

		{	-1,		},
};



 //
 QY_COLUMNINFO	CONST_pcMgrClassListColumns[]  =
{
		{	0,	CONST_str_leiBie,					0,	LVCFMT_LEFT, 	120,	1	},
		{	-1,															},
};

 QY_COLUMNINFO  CONST_pcOpNodememListColumns_netMc[]  =
{
		{	0,	CONST_str_mingChen,			0,	LVCFMT_LEFT, 	120,	1	},
		{	0,	CONST_str_miaoShu,			0,	LVCFMT_LEFT,	200,	1	},
		{	0,	CONST_str_servName,			0,	LVCFMT_LEFT,	0,		1,	},
		{	0,	_T(  "MAC"  ),				0,	LVCFMT_LEFT,	120,	1	},
		{	-1,																},

};

  QY_COLUMNINFO  CONST_pcOpNodememListColumns_is[]  =
{
		{	0,	CONST_str_mingChen,			0,	LVCFMT_LEFT, 	120,	1	},
		{	0,	CONST_str_miaoShu,			0,	LVCFMT_LEFT,	200,	1	},
		{	0,	CONST_str_servName,			0,	LVCFMT_LEFT,	0,		1,	},
		{	0,	CONST_str_idStr,			0,	LVCFMT_LEFT,	120,	1	},
		{	-1,																},

};


 QY_COLUMNINFO  COSNT_pcEnvListColumns[]  =  
{
		{	0,	CONST_str_mingChen,					0,	LVCFMT_LEFT, 	120,	1	},
		{	-1,															},
};

 QY_COLUMNINFO  COSNT_pcOsListColumns[]  =  
{
		{	0,	CONST_str_caoZuoXiTong,				0,	LVCFMT_LEFT, 	200,	1	},
		{	-1,															},
};



 QY_COLUMNINFO  COSNT_pcAssetListColumns[]  =  
{
		{	0,	CONST_colName_assetType,			0,	LVCFMT_LEFT, 	100,	1	},
		{	1,	CONST_colName_assetName,			0,	LVCFMT_LEFT,	260,	1	},
		{	1,	CONST_colName_assetDes0,			0,	LVCFMT_LEFT,	120,	1	},
		{	1,	CONST_colName_assetDes1,			0,	LVCFMT_LEFT,	0,		1	},
		{	1,	CONST_colName_assetEndTime,			0,	LVCFMT_LEFT,	120,	1	},
		{	1,	CONST_colName_assetStartTime,		0,	LVCFMT_LEFT,	120,	1	},
		{	-1,															},
};


////////////////////////// 2008/12/16
 QY_COLUMNINFO  CONST_qyCfgSystemsColumns[]  =
{
	{		CONST_qyColumnDisplayType_str,	_T(  "ID"  ),						SQL_CHAR,	LVCFMT_LEFT,	30,				1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_systemName,				SQL_CHAR,	LVCFMT_LEFT,	100,			1,	},
	{		CONST_qyColumnDisplayType_long,	CONST_long_systemType,				SQL_CHAR,	LVCFMT_LEFT,	150,			1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_databaseType,				SQL_CHAR,	LVCFMT_LEFT,	100,			1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_databaseConnectionMode,	SQL_CHAR,	LVCFMT_LEFT,	100,			1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_databaseServerIp,			SQL_CHAR,	LVCFMT_LEFT,	100,			1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_databaseName,				SQL_CHAR,	LVCFMT_LEFT,	100,			1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_yongHuMing,				SQL_CHAR,	LVCFMT_LEFT,	100,			1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_zhuangTai,				SQL_CHAR,	LVCFMT_LEFT,	60,				1,	},
	{		-1,								_T(  ""  ),							SQL_CHAR,	LVCFMT_LEFT,	105,			1,	},
};

 QY_COLUMNINFO  CONST_procedObjsViewTable[]  =
{
	{	0,	_T(  "ID"  ),						0,	LVCFMT_LEFT,	60,		1	},
	{	0,	CONST_str_systemName,					0,	LVCFMT_LEFT,	160,		1	},
	{	0,	CONST_long_systemType,					0,	LVCFMT_LEFT,	160,		1	},
	{	0,	CONST_str_zhuangTai,						0,	LVCFMT_LEFT,	160,		1	},
	{	-1,	_T(  "" ),							0,	LVCFMT_LEFT, 	120,	1  },
};

 QY_COLUMNINFO  CONST_qnmCfgPcGrpsColumns_nms[]  =
{
	{		CONST_qyColumnDisplayType_ip12,	CONST_str_startIp,			SQL_CHAR,	LVCFMT_LEFT, 	105,		1,	},
	{		CONST_qyColumnDisplayType_ip12,	CONST_str_endIp,			SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_danWei,			SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_buMen,			SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
	{		CONST_qyColumnDisplayType_bool,	CONST_str_pcScan,			SQL_CHAR,	LVCFMT_LEFT,	75,		1,	},
	{		CONST_qyColumnDisplayType_bool,	CONST_str_snmpObjScan,		SQL_CHAR,	LVCFMT_LEFT,	85,		1,	},
	{		-1,								_T(  ""  ),					SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
};
// 2008/12/27
 QY_COLUMNINFO	CONST_qnmCfgSwitchPolicyGrpsColumns[]  =
{
	{		CONST_qyColumnDisplayType_str,	CONST_str_STATIC_grpName,						SQL_CHAR,	LVCFMT_LEFT,	89,			1,  },
	{		CONST_qyColumnDisplayType_str,	CONST_str_STATIC_snmpVer,						SQL_CHAR,	LVCFMT_LEFT,	40,			1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_STATIC_getCommunity,					SQL_CHAR,	LVCFMT_LEFT,	90,			1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_STATIC_setCommunity,					SQL_CHAR,	LVCFMT_LEFT,	90,			1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_STATIC_usrName,						SQL_CHAR,	LVCFMT_LEFT,	84,			1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_STATIC_securityLevel,					SQL_CHAR,	LVCFMT_LEFT,	80,			1,	},
	{		-1,								_T(  ""  ),																		},
};
//  2008/12/28
 QY_COLUMNINFO  CONST_qnmMgrSwitchPolicyColumns[]  =
{
	{		CONST_qyColumnDisplayType_ip12,	_T(  "IP"  )/*_T(  "Éè±¸IP"  )*/,			SQL_CHAR,	LVCFMT_LEFT,	120,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_wDevIdStr,			SQL_CHAR,	LVCFMT_LEFT,	95,		1,	},
	{		-1,								_T(  ""  ),					SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
};

 QY_COLUMNINFO  CONST_cfgStandardNameColumns[]  =
{
	{		CONST_qyColumnDisplayType_str,	_T(  "ID"  ),					SQL_CHAR,	LVCFMT_LEFT,	0,			1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_zongBu,				SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_benBu,				SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_danWei,				SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_buMen,				SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_shiYongRen,			SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_guiFan_zongBu,		SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_guiFan_benBu,			SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_guiFan_danWei,		SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_guiFan_buMen,			SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_guiFan_shiYongRen,	SQL_CHAR,	LVCFMT_LEFT,	80,		1,	},
	{		-1,								_T(  ""  ),						SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
};

 //	2008/12/29
 QY_COLUMNINFO  CONST_realTimeImTaskListColumns[]  =
{
	{	0,	CONST_str_xuHao,						0,	LVCFMT_LEFT,	0,			1	},
	{	0,	CONST_str_leiXing,						0,	LVCFMT_LEFT,	190,		1	},
	{	0,	CONST_str_taskId,						0,	LVCFMT_LEFT,	100,			1,	},
	{	0,	CONST_str_requestId,					0,	LVCFMT_LEFT,	70,			1	},
	{	0,	CONST_str_responseId,					0,	LVCFMT_LEFT,	80,			1	},
	{	0,	CONST_str_talker,						0,	LVCFMT_LEFT,	80,			1,	},
	{	0,	CONST_str_miaoShu,						0,	LVCFMT_LEFT,	1050,		1	},
	{	0,	CONST_str_zhuangTai,					0,	LVCFMT_LEFT,	160,		1	},
	{	0,	CONST_str_startTime,					0,	LVCFMT_LEFT,	160,		1	},
	{	-1,	_T(  "" ),								0,	LVCFMT_LEFT, 	120,		1  },
};

  QY_COLUMNINFO  CONST_taskInfoListColumns[]  =
{
	{	0,	CONST_str_xuHao,						0,	LVCFMT_LEFT,	60,			1	},
	{	0,	CONST_str_taskId,						0,	LVCFMT_LEFT,	50,			1,	},
	{	0,	CONST_str_miaoShu,						0,	LVCFMT_LEFT,	360,		1,	},
	{	0,	CONST_str_miaoShu,						0,	LVCFMT_LEFT,	600,		1	},
	{	0,	CONST_str_zhuangTai,					0,	LVCFMT_LEFT,	400,		1	},
	{	0,	CONST_str_device,						0,	LVCFMT_LEFT,	200,		1	},
	{	-1,	_T(  "" ),								0,	LVCFMT_LEFT, 	120,		1  },
};


  QY_COLUMNINFO  CONST_sharingObjectListColumns[]  =
{
	{	0,	CONST_str_xuHao,						0,	LVCFMT_LEFT,	60,			1	},
	{	0,	CONST_str_taskId,						0,	LVCFMT_LEFT,	50,			1,	},
	{	0,	CONST_str_destination,					0,	LVCFMT_LEFT,	360,		1,	},
	{	0,	CONST_str_miaoShu,						0,	LVCFMT_LEFT,	600,		1	},
	{	0,	CONST_str_zhuangTai,					0,	LVCFMT_LEFT,	400,		1	},
	{	0,	CONST_str_device,						0,	LVCFMT_LEFT,	200,		1	},
	{	-1,	_T(  "" ),								0,	LVCFMT_LEFT, 	120,		1  },
};


 QY_COLUMNINFO  CONST_playerListColumns[]  =
{
	{	0,	CONST_str_xuHao,						0,	LVCFMT_LEFT,	60,			1	},
	{	0,	CONST_str_taskId,						0,	LVCFMT_LEFT,	50,			1,	},
	{	0,	CONST_str_idStr,						0,	LVCFMT_LEFT,	160,		1	},
	{	0,	CONST_str_miaoShu,						0,	LVCFMT_LEFT,	160,		1	},
	{	0,	CONST_str_tranNo,						0,	LVCFMT_LEFT,	160,		1	},
	{	0,	CONST_str_waveFormat,					0,	LVCFMT_LEFT,	220,		1,	},
	{	0,	CONST_str_zhuangTai,					0,	LVCFMT_LEFT,	1000,		1	},
	{	-1,	_T(  "" ),								0,	LVCFMT_LEFT, 	120,	1  },
};


  QY_COLUMNINFO  CONST_wallListColumns[]  =
{
	{	0,	CONST_str_name,							0,	LVCFMT_LEFT,	130,		1	},
	{	0,	CONST_str_leiXing,						0,	LVCFMT_LEFT,	100,			1	},
	{	0,	CONST_str_wLocation,					0,	LVCFMT_LEFT,	60,			1	},
	{	0,	CONST_str_taskId,						0,	LVCFMT_LEFT,	50,			1,	},
	{	0,	CONST_str_miaoShu,						0,	LVCFMT_LEFT,	760,		1	},
	{	0,	CONST_str_zhuangTai,					0,	LVCFMT_LEFT,	1000,		1	},
	{	-1,	_T(  "" ),								0,	LVCFMT_LEFT, 	120,	1  },
};

  QY_COLUMNINFO  CONST_ipCamListColumns[]  =
{
	{	0,	CONST_str_ipAddr,						0,	LVCFMT_LEFT,	130,		1	},
	{	0,	CONST_str_deviceAddr,					0,	LVCFMT_LEFT,	100,			1	},
	{	0,	CONST_str_ptzAddr,						0,	LVCFMT_LEFT,	100,			1	},
	{	0,	CONST_str_rtspAddr,						0,	LVCFMT_LEFT,	100,			1,	},
	{	0,	CONST_str_zhuangTai,					0,	LVCFMT_LEFT,	1000,		1	},
	{	-1,	_T(  "" ),								0,	LVCFMT_LEFT, 	120,	1  },
};


  QY_COLUMNINFO  CONST_imNetStatListColumns[]  =
{
	{	0,  CONST_str_xuHao,						0,	LVCFMT_LEFT,	50,		1	},
	{	0,  CONST_str_channelType,					0,	LVCFMT_LEFT,	120,		1	},
	{	0,	CONST_str_inOctets,						0,	LVCFMT_RIGHT, 	145,		1	},
	{	0,	CONST_str_outOctets,					0,	LVCFMT_RIGHT, 	145,		1	},
	{	0,	CONST_str_inSpeed,						0,	LVCFMT_RIGHT, 	90,		1	},
	{	0,	CONST_str_outSpeed,						0,	LVCFMT_RIGHT, 	90,		1	},
	{	-1,	_T(  "" ),								0,	LVCFMT_LEFT, 	120,	1  },
};

  QY_COLUMNINFO  *  CONST_talkerListColumns  =     CONST_realTimeImTaskListColumns;
#if  0
  QY_COLUMNINFO  CONST_talkerListColumns[]  =
{
	{	0,	CONST_str_xuHao,						0,	LVCFMT_LEFT,	130,		1	},
	{	0,	CONST_str_leiXing,						0,	LVCFMT_LEFT,	70,			1	},
	{	0,	CONST_str_taskId,						0,	LVCFMT_LEFT,	50,			1,	},
	{	0,	CONST_str_requestId,					0,	LVCFMT_LEFT,	50,			1	},
	{	0,	CONST_str_responseId,					0,	LVCFMT_LEFT,	50,			1	},
	{	0,	CONST_str_miaoShu,						0,	LVCFMT_LEFT,	160,		1	},
	{	0,	CONST_str_zhuangTai,					0,	LVCFMT_LEFT,	1000,		1	},

	{	-1,	_T(  "" ),								0,	LVCFMT_LEFT, 	120,	1  },
};
#endif


  QY_COLUMNINFO  CONST_messengerStatusListColumns[]  =
{
	{	0,	CONST_str_name,							0,	LVCFMT_LEFT,	130,		1	},
	{	0,	CONST_str_zhuangTai,					0,	LVCFMT_LEFT,	1000,		1	},

	{	-1,	_T(  "" ),								0,	LVCFMT_LEFT, 	120,	1  },
};


  QY_COLUMNINFO  CONST_qListColumns[]  =
{
	{	0,	CONST_str_name,							0,	LVCFMT_LEFT,	130,		1	},
	{	0,	CONST_str_leiXing,						0,	LVCFMT_LEFT,	0,			1	},
	{	0,	CONST_str_miaoShu,						0,	LVCFMT_LEFT,	100,		1	},
	{	0,	CONST_str_zhuangTai,					0,	LVCFMT_LEFT,	1000,		1	},

	{	-1,	_T(  "" ),								0,	LVCFMT_LEFT, 	120,	1  },
};

 QY_COLUMNINFO	CONST_imTaskListColumns[] =										//  2013/02/17
{
	{	0,	CONST_str_xuHao,					0,	LVCFMT_LEFT, 0,		1	},	//  13  
	{	0,	CONST_str_leiXing,					0,	LVCFMT_LEFT, 70,	1	},	//  1
	{	0,	CONST_str_senderDesc,				0,	LVCFMT_LEFT, 130,	1	},	//  1
	{	0,	CONST_str_receiverDesc,				0,	LVCFMT_LEFT, 130,	1	},	//  1
	{	0,	CONST_str_zhuangTai,				0,	LVCFMT_LEFT, 60,	1	},	//  1
	{	0,	CONST_str_subject,					0,	LVCFMT_LEFT, 130,	1	},	//  1
	{	0,	CONST_str_sendTime,					0,	LVCFMT_LEFT, 130,	1	},	//  1
	{	0,	CONST_str_tranNo,					0,	LVCFMT_LEFT,  60,	1	},
	{	0,	CONST_str_recvTime,					0,	LVCFMT_LEFT, 130,	1	},	//  1
	{	0,	CONST_str_content,					0,	LVCFMT_LEFT, 130,	1	},	//  1
	{	0,	CONST_str_idStr_send,				0,	LVCFMT_LEFT, 60,	1	},	//  1
	{	0,	CONST_str_idStr_recv,				0,	LVCFMT_LEFT, 60,	1	},	//  1
	{	0,	CONST_str_lastModifiedTime,			0,	LVCFMT_LEFT, 130,	1	},	//  1	//  2014/07/30
	{	-1,																	},
};

 //  2008/12/31
#define		CONST_rowIdStr_cur					_T(  "rowIdStr_cur"  )		//  2007/07/22
#define		CONST_iStatus_cur					_T(  "iStatus_cur"  )		//  2007/07/23
//  #define		CONST_iW_memberList					150						//  
//  #define		CONST_iW_subject				113
    #define		CONST_iW_subject				90
#define		CONST_iW_contacter					65
#define		CONST_iW_shortTime					60


#if  0
 QY_COLUMNINFO  CONST_taskListColumns[]  =
{
	{		CONST_qyColumnDisplayType_str,	_T(  "ID"  ),				SQL_CHAR,	LVCFMT_LEFT,	0,						1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "rowIdStr"  ),			SQL_CHAR,	LVCFMT_LEFT,	0,						1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_rowIdStr_cur,			SQL_CHAR,	LVCFMT_LEFT,	0,						1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_iStatus_cur,			SQL_CHAR,	LVCFMT_LEFT,	0,						1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_leiXing,			SQL_CHAR,	LVCFMT_LEFT,	60,						1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_subject,			SQL_CHAR,	LVCFMT_LEFT,	CONST_iW_subject,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_zhuangTai,		SQL_CHAR,	LVCFMT_LEFT,	65,						1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_senderDesc,		SQL_CHAR,	LVCFMT_LEFT,	0,						1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_sendTime,			SQL_CHAR,	LVCFMT_LEFT,	CONST_iW_shortTime,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_recvTime,			SQL_CHAR,	LVCFMT_LEFT,	0,						1,	},
	{		-1,								_T(  ""  ),					SQL_CHAR,	LVCFMT_LEFT,	105,					1,	},
};
#endif

 QY_COLUMNINFO  CONST_taskListColumns[]  =
{
	{		CONST_qyColumnDisplayType_str,	_T(  "ID"  ),				SQL_CHAR,	LVCFMT_LEFT,	0,						1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "rowIdStr"  ),			SQL_CHAR,	LVCFMT_LEFT,	0,						1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_rowIdStr_cur,			SQL_CHAR,	LVCFMT_LEFT,	0,						1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_iStatus_cur,			SQL_CHAR,	LVCFMT_LEFT,	0,						1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_senderDesc,		SQL_CHAR,	LVCFMT_LEFT,	55,						1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_leiXing,			SQL_CHAR,	LVCFMT_LEFT,	60,						1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_zhuangTai,		SQL_CHAR,	LVCFMT_LEFT,	58,						1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_subject,			SQL_CHAR,	LVCFMT_LEFT,	CONST_iW_subject,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_sendTime,			SQL_CHAR,	LVCFMT_LEFT,	CONST_iW_shortTime,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_recvTime,			SQL_CHAR,	LVCFMT_LEFT,	0,						1,	},
	{		-1,								_T(  ""  ),					SQL_CHAR,	LVCFMT_LEFT,	105,					1,	},
};



 QY_COLUMNINFO  CONST_instantAssistant_talkerListcolumns[]  =
{
	{		CONST_qyColumnDisplayType_str,	CONST_str_speaker,				SQL_CHAR,	LVCFMT_LEFT,	200,						1,	},
	{		-1,							},
};

 //  2011/01/16
 QY_COLUMNINFO	CONST_deamonStatus_listColumn[]  =
{
	{		CONST_qyColumnDisplayType_str,	_T(  "ID"	),				SQL_CHAR,	LVCFMT_LEFT,	40,							1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "aIn"	),				SQL_CHAR,	LVCFMT_LEFT,	50,							1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "aOut"	),				SQL_CHAR,	LVCFMT_LEFT,	50,							1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "vIn"	),				SQL_CHAR,	LVCFMT_LEFT,	50,							1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "vOut"	),				SQL_CHAR,	LVCFMT_LEFT,	50,							1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "fIn"	),				SQL_CHAR,	LVCFMT_LEFT,	50,							1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "fOut"	),				SQL_CHAR,	LVCFMT_LEFT,	50,							1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "oIn"	),				SQL_CHAR,	LVCFMT_LEFT,	50,							1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "oOut"	),				SQL_CHAR,	LVCFMT_LEFT,	50,							1,	},
	{		-1,							},

};

 //  2011/01/28
 QY_COLUMNINFO  CONST_deamonStatus_listColumnOfChannel[]  =  
 {
	{		CONST_qyColumnDisplayType_str,	_T(  "Index"	),			SQL_CHAR,	LVCFMT_LEFT,	50,							1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "Recving"	),			SQL_CHAR,	LVCFMT_LEFT,	120,						1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "Sending"	),			SQL_CHAR,	LVCFMT_LEFT,	120,						1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "In"	),				SQL_CHAR,	LVCFMT_LEFT,	50,							1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "Out"	),				SQL_CHAR,	LVCFMT_LEFT,	50,							1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "ID"	),				SQL_CHAR,	LVCFMT_LEFT,	40,							1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "Type"	),				SQL_CHAR,	LVCFMT_LEFT,	80,							1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "IP"	),				SQL_CHAR,	LVCFMT_LEFT,	120,							1,	},
	{		CONST_qyColumnDisplayType_str,	_T(  "SessionId"	),		SQL_CHAR,	LVCFMT_LEFT,	100,							1,	},

	{		-1,							},
};

 //  2009/04/11
 QY_COLUMNINFO  CONST_qnmCfgIpScanColumns[]  =
{
	{		CONST_qyColumnDisplayType_ip12,	_T(  "Starting IP"  ),			SQL_CHAR,	LVCFMT_LEFT, 	105,		1,	},
	{		CONST_qyColumnDisplayType_ip12,	_T(  "Ending IP"  ),			SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_danWei,				SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_buMen,				SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
	{		-1,								_T(  ""  ),					SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
};

 QY_COLUMNINFO  CONST_qnmCfgPcGrpsColumns[]  =
{
	{		CONST_qyColumnDisplayType_ip12,	_T(  "Starting IP"  ),			SQL_CHAR,	LVCFMT_LEFT, 	105,		1,	},
	{		CONST_qyColumnDisplayType_ip12,	_T(  "Ending IP"  ),			SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_danWei,				SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_buMen,				SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
	{		CONST_qyColumnDisplayType_bool,	CONST_str_pcScan,		SQL_CHAR,	LVCFMT_LEFT,	75,		1,	},
	{		-1,								_T(  ""  ),					SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
};
 QY_COLUMNINFO  CONST_pcRegistryColumns[]  =
{
	{		CONST_qyColumnDisplayType_str,	_T(  "ID"  ),				SQL_CHAR,	LVCFMT_LEFT,	0,			1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_genJian,				SQL_CHAR,	LVCFMT_LEFT,	200,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_jianLuJing,			SQL_CHAR,	LVCFMT_LEFT,	380,		1,	},
	{		CONST_qyColumnDisplayType_str,	CONST_str_mingChen,				SQL_CHAR,	LVCFMT_LEFT,	120,		1,	},
	{		CONST_qyColumnDisplayType_long,	CONST_str_detectionFrequency,		SQL_CHAR,	LVCFMT_LEFT,	80,			1,	},
	{		-1,								_T(  ""  ),					SQL_CHAR,	LVCFMT_LEFT,	105,		1,	},
};


 QY_COLUMNINFO	 CONST_imObjListColumns[]  = 
{
	{	CONST_qyColumnDisplayType_long,				CONST_str_xuHao,					SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_objType,			CONST_str_leiXing,				SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,			CONST_str_idStr,				SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,				CONST_str_danWei,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  1  */	\
	{	CONST_qyColumnDisplayType_str,				CONST_str_buMen,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  3  */	\
	{	CONST_qyColumnDisplayType_str,				CONST_str_shiYongRen,			SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },		/*  4  */	
	//
	{	CONST_qyColumnDisplayType_imObjRole,		CONST_str_role,				SQL_INTEGER,	LVCFMT_LEFT,  80,  1,  50,  },
	//
	{	CONST_qyColumnDisplayType_str,				CONST_str_phoneNo,				SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_time,				CONST_str_gengXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_qyStatus,			CONST_str_zhuangTai,							SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	-1,	NULL,														},
};

  QY_COLUMNINFO	 CONST_imGrpListColumns[]  = 
{
	{	CONST_qyColumnDisplayType_long,		CONST_str_xuHao,								SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_objType,	CONST_str_leiXing,								SQL_INTEGER,	LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,	CONST_str_idStr_grp,							SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	//
	{	CONST_qyColumnDisplayType_str,		CONST_str_mingChen,								SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_imGrpSubtype,		CONST_str_subtype,						SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	//
	{	CONST_qyColumnDisplayType_idStr,	CONST_str_idStr_creator,						SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	
	//
	{	CONST_qyColumnDisplayType_time,		CONST_str_zhuCeShiJian,							SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_time,		CONST_str_gengXinShiJian,						SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_qyStatus,	CONST_str_zhuangTai,			SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	-1,	NULL,														},
};

    QY_COLUMNINFO	 CONST_imGrpMemListColumns[]  = 	
{
	{	CONST_qyColumnDisplayType_long,		CONST_str_xuHao,					SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_objType,	CONST_str_leiXing,				SQL_INTEGER,	LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,	CONST_str_idStr_grp,			SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,		CONST_str_mingChen,				SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_idStr,	CONST_str_idStr,				SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	//
	//MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_str,	CONST_str_danWei,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  1  */	\
	{	CONST_qyColumnDisplayType_str,	CONST_str_buMen,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  3  */	\
	{	CONST_qyColumnDisplayType_str,	CONST_str_shiYongRen,			SQL_CHAR,		LVCFMT_LEFT, 110, 1, 50, },		/*  4  */		
	//  2015/07/28
	{	CONST_qyColumnDisplayType_imGrpMemRole,CONST_str_role,				SQL_INTEGER,	LVCFMT_LEFT,  80,  1,  50,  },
	//
	{	CONST_qyColumnDisplayType_time,		CONST_str_gengXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_qyStatus,	CONST_str_zhuangTai,			SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },

	{	-1,	NULL,														},
};

	
QY_COLUMNINFO	 CONST_imObjRuleListColumns[]  = 	
{
	{	CONST_qyColumnDisplayType_long,			CONST_str_xuHao,				SQL_INTEGER,	LVCFMT_LEFT, 0,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr,				SQL_CHAR,		LVCFMT_LEFT, 0,		1, 50,	},	//  13  
	//
	//  MACRO_zjgaEventSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_str,	CONST_str_danWei,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  1  */	\
	{	CONST_qyColumnDisplayType_str,	CONST_str_buMen,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  3  */	\
	{	CONST_qyColumnDisplayType_str,	CONST_str_shiYongRen,			SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },		/*  4  */		
	//
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr_related,		SQL_CHAR,		LVCFMT_LEFT, 120,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_ruleType,		CONST_str_leiXing,				SQL_INTEGER,	LVCFMT_LEFT, 200,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_ruleCmd,		CONST_str_ceLue,				SQL_INTEGER,	LVCFMT_LEFT, 160,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_miaoShu,				SQL_CHAR,		LVCFMT_LEFT, 100,  1,  50,  },
	{	CONST_qyColumnDisplayType_time,		CONST_str_gengXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0

	{	-1,	NULL,														},
};


 QY_COLUMNINFO	CONST_regInfoListColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,		CONST_str_xuHao,					SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_idStr,	CONST_str_idStr,					SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,	CONST_str_danWei,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  1  */	\
	{	CONST_qyColumnDisplayType_str,	CONST_str_buMen,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  3  */	\
	{	CONST_qyColumnDisplayType_str,	CONST_str_shiYongRen,			SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },		/*  4  */	
	{	CONST_qyColumnDisplayType_jqlx,		CONST_str_jiQiLeiXing,				SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },	//  5
	{	CONST_qyColumnDisplayType_str,		CONST_str_ziChanBianHao,			SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },  
	{	CONST_qyColumnDisplayType_str,		CONST_str_zhuYaoYongTu,				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  6
	{	CONST_qyColumnDisplayType_str,		CONST_str_lianXiDianHua,			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  7					   
	{	CONST_qyColumnDisplayType_str,		CONST_str_shiYongDiDian,			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  10					   
	{	CONST_qyColumnDisplayType_str,		CONST_str_ziChanBianHao1,			SQL_CHAR,		LVCFMT_LEFT, 70,  0, 0, },	//  8					   
	{	CONST_qyColumnDisplayType_str,		CONST_str_ziChanShuoMing1,			SQL_CHAR,		LVCFMT_LEFT, 70,  0,  0, },	//  9					   
	{	CONST_qyColumnDisplayType_str,		CONST_str_ziChanBianHao2,			SQL_CHAR,		LVCFMT_LEFT, 70,  0, 0, },	//  8					   
	{	CONST_qyColumnDisplayType_str,		CONST_str_ziChanShuoMing2,			SQL_CHAR,		LVCFMT_LEFT, 70,  0,  0, },	//  9					   
	{	CONST_qyColumnDisplayType_ip12,		_T(  "IP"  ),						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  11					   
	{	CONST_qyColumnDisplayType_time,		CONST_str_gengXinShiJian,			SQL_CHAR,		LVCFMT_LEFT, 130,  0,  0, },	//  9					   
	{	-1,																									},
};

 QY_COLUMNINFO  CONST_dynBmpListColumns[]  = 
{
	{	CONST_qyColumnDisplayType_long,			CONST_str_xuHao,				SQL_INTEGER,	LVCFMT_LEFT, 0,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,	CONST_str_danWei,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  1  */	\
	{	CONST_qyColumnDisplayType_str,	CONST_str_buMen,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  3  */	\
	{	CONST_qyColumnDisplayType_str,	CONST_str_shiYongRen,			SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },		/*  4  */	
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr,				SQL_CHAR,		LVCFMT_LEFT, 85,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_objType,		CONST_str_leiXing,				SQL_INTEGER,	LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_long,			_T(  "Index"  ),				SQL_INTEGER,	LVCFMT_LEFT, 60,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,			CONST_str_name,					SQL_CHAR,		LVCFMT_LEFT, 180,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,			CONST_str_bieMing,				SQL_CHAR,		LVCFMT_LEFT, 120,		1, 50,	},	//  13  
	//
	{	-1,	NULL,														},
};


 QY_DMITEM  CONST_columnInfoTable[]  =
{
	{	CONST_resId_COLUMNINFO_sQyMcRootListColumns,				(  TCHAR  *  )sQyMcRootListColumns,		},	
	{	CONST_resId_COLUMNINFO_networkViewTable,					(  TCHAR  *  )CONST_networkViewTable,	},
	{	CONST_resId_COLUMNINFO_switchViewTable,						(  TCHAR  *  )CONST_switchViewTable,	},
	{	CONST_resId_COLUMNINFO_switchPortViewTable,					(  TCHAR  *  )CONST_switchPortViewTable,	},
	{	CONST_resId_COLUMNINFO_switchUsrConnectionViewTable,		(  TCHAR  *  )CONST_switchUsrConnectionViewTable,	},
	{	CONST_resId_COLUMNINFO_switchPortUsrConnectionViewTable,	(  TCHAR  *  )CONST_switchPortUsrConnectionViewTable,	},	
	{	CONST_resId_COLUMNINFO_switchNetworkSpeedViewTable,			(  TCHAR  *  )CONST_switchNetworkSpeedViewTable,	},
	{	CONST_resId_COLUMNINFO_switchPortNetworkSpeedViewTable,		(  TCHAR  *  )CONST_switchPortNetworkSpeedViewTable,	},
	//
	{	CONST_resId_COLUMNINFO_col4ListColumns_netMc,				(  TCHAR  *  )COSNT_col4ListColumns_netMc,	},
	{	CONST_resId_COLUMNINFO_col4ListColumns_is,					(  TCHAR  *  )COSNT_col4ListColumns_is,		},
	//
	{	CONST_resId_COLUMNINFO_unRegGrpMemListColumns_netMc,		(  TCHAR  *  )COSNT_unRegGrpMemListColumns_netMc,	},
	{	CONST_resId_COLUMNINFO_unRegGrpMemListColumns_is,			(  TCHAR  *  )COSNT_unRegGrpMemListColumns_is,	},
	//
	{	CONST_resId_COLUMNINFO_othersGrpMemListColumns,				(  TCHAR  *  )COSNT_othersGrpMemListColumns,		},
	{	CONST_resId_COLUMNINFO_pcMgrClassListColumns,				(  TCHAR  *  )CONST_pcMgrClassListColumns,		},
	{	CONST_resId_COLUMNINFO_pcOpNodeMemListColumns_netMc,		(  TCHAR  *  )CONST_pcOpNodememListColumns_netMc,		},
	{	CONST_resId_COLUMNINFO_pcOpNodeMemListColumns_is,			(  TCHAR  *  )CONST_pcOpNodememListColumns_is,		},
	//
	{	CONST_resId_COLUMNINFO_pcEnvListColumns,					(  TCHAR  *  )COSNT_pcEnvListColumns,		},
	{	CONST_resId_COLUMNINFO_pcOsListColumns,						(  TCHAR  *  )COSNT_pcOsListColumns,		},
	{	CONST_resId_COLUMNINFO_pcAssetListColumns,					(  TCHAR  *  )COSNT_pcAssetListColumns,		},
	//
	{	CONST_resId_COLUMNINFO_qnmCfgIpScanColumns,					(  TCHAR  *  )CONST_qnmCfgIpScanColumns,	},
	{	CONST_resId_COLUMNINFO_qnmCfgPcGrpsColumns,					(  TCHAR  *  )CONST_qnmCfgPcGrpsColumns,	},
	{	CONST_resId_COLUMNINFO_pcRegistryColumns,					(  TCHAR  *  )CONST_pcRegistryColumns,		},

	//
	{	CONST_resId_COLUMNINFO_imGrpListColumns,					(  TCHAR  *  )COSNT_imGrpListColumns_is,		},
	{	CONST_resId_COLUMNINFO_imGrpMemListColumns_isMgr,			(  TCHAR  *  )CONST_imGrpMemListColumns_isMgr,		},
	{	CONST_resId_COLUMNINFO_imGrpMemListColumns_isCli,			(  TCHAR  *  )CONST_imGrpMemListColumns_isCli,		},

	//
	{	CONST_resId_COLUMNINFO_confListColumns_isMgr,				(  TCHAR  *  )CONST_confListColumns_isMgr,		},
	

	{	CONST_resId_COLUMNINFO_qyCfgSystemsColumns,					(  TCHAR  *  )CONST_qyCfgSystemsColumns,		},
	{	CONST_resId_COLUMNINFO_procedObjsViewTable,					(  TCHAR  *  )CONST_procedObjsViewTable,		},
	//
	{	CONST_resId_COLUMNINFO_qnmCfgPcGrpsColumns_nms,				(  TCHAR  *  )CONST_qnmCfgPcGrpsColumns_nms,	},
	{	CONST_resId_qnmCfgSwitchPolicyGrpsColumns,					(  TCHAR  *  )CONST_qnmCfgSwitchPolicyGrpsColumns,  },
	{	CONST_resId_qnmMgrSwitchPolicyColumns,						(  TCHAR  *  )CONST_qnmMgrSwitchPolicyColumns,  },
	{	CONST_resId_cfgStandardNameColumns,							(  TCHAR  *  )CONST_cfgStandardNameColumns,		},
	{	CONST_resId_realTimeImTaskListColumns,						(  TCHAR  *  )CONST_realTimeImTaskListColumns,	},	
	{	CONST_resId_taskInfoListColumns,							(  TCHAR  *  )CONST_taskInfoListColumns,	},
	{	CONST_resId_sharingObjectListColumns,						(  TCHAR  *  )CONST_sharingObjectListColumns,		},
	{	CONST_resId_playerListColumns,								(  TCHAR  *  )CONST_playerListColumns,		},
	{	CONST_resId_wallListColumns,								(  TCHAR  *  )CONST_wallListColumns,		},
	{	CONST_resId_ipCamListColumns,								(  TCHAR  *  )CONST_ipCamListColumns,		},				//  2016/07/30
	{	CONST_resId_imNetStatListColumns,							(  TCHAR  *  )CONST_imNetStatListColumns,			},
	{	CONST_resId_talkerListColumns,								(  TCHAR  *  )CONST_talkerListColumns,			},
	{	CONST_resId_messengerStatusColumns,							(  TCHAR  *  )CONST_messengerStatusListColumns,	},
	{	CONST_resId_qListColumns,									(  TCHAR  *  )CONST_qListColumns,				},
	{	CONST_resId_imTaskListColumns,								(  TCHAR  *  )CONST_imTaskListColumns,			},
	{	CONST_resId_imObjListColumns,								(  TCHAR  *  )CONST_imObjListColumns,	},	
	{	CONST_resId_regInfoListColumns,								(TCHAR  *  )CONST_regInfoListColumns,	},	
	{	CONST_resId_imGrpListColumns,								(  TCHAR  *  )CONST_imGrpListColumns,	},
	{	CONST_resId_imGrpMemListColumns,							(  TCHAR  *  )CONST_imGrpMemListColumns,	},
	{	CONST_resId_imObjRuleListColumns,							(  TCHAR  *  )CONST_imObjRuleListColumns,	},
	{	CONST_resId_dynBmpListColumns,								(  TCHAR  *  )CONST_dynBmpListColumns,		},
	
	{	CONST_resId_taskListColumns,								(  TCHAR  *  )CONST_taskListColumns,			},

	//  {	CONST_resId_taskListColumns_showMembers,					(  TCHAR  *  )CONST_taskListColumns_showMembers,},
	{	CONST_resId_instantAssistant_talkerListColumns,				(  TCHAR  *  )CONST_instantAssistant_talkerListcolumns,	},
	{	CONST_resId_deamonStatus_listColumns,						(  TCHAR  *  )CONST_deamonStatus_listColumn,	},		
	{	CONST_resId_deamonStatus_listColumnsOfChannel,				(  TCHAR  *  )CONST_deamonStatus_listColumnOfChannel,	},

	{	-1,			},
};

