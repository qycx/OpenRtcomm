
#include	"stdafx.h"
#include	<tchar.h>
#include	<commctrl.h>
//  #include	"qyCommon.h"
#include	"myresource_main.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_netMc.h"


 //  显示在线日志列表
 QY_COLUMNINFO  CONST_bhbLogSqlColumns[]  =
{
	{	6,	_T(  "onlineComputerTab.officeName"  ),			SQL_CHAR,	},		//	6
	{	0,  _T(  "onlineComputerTab.subOfficeName"  ),		SQL_CHAR,	},		//	0
	{	1,	_T(  "onlineComputerTab.ip"  ),					SQL_CHAR,	},		//	1
	{	2,	_T(  "onlineComputerTab.mac"  ),				SQL_CHAR,	},		//  2
	{	3,	_T(  "onlineComputerTab.compName"  ),			SQL_CHAR,	},		//  3
	{	4,	_T(  "onlineComputerTab.usrName"  ),			SQL_CHAR,	},		//  4
	//  {	4,	"onlineComputerTab.is_server"  ),			SQL_CHAR,	},		//  4
	{	5,	_T(  "onlineComputerTab.firstRecvdTime"  ),		SQL_CHAR,	},		//  5
	{	-1,	NULL,											},
};

 QY_COLUMNINFO	 CONST_bhbLogDisplayColumns[]  = 
{
	{	CONST_qyColumnDisplayType_str,	CONST_str_danWei,				SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,	CONST_str_buMen,				SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  2
	{	CONST_qyColumnDisplayType_str,	_T(  "IP"  ),					SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_str,	_T(  "MAC"  ),					SQL_CHAR,		LVCFMT_LEFT, 100,  1, 50,	},	//  3
	{	CONST_qyColumnDisplayType_str,	CONST_str_jiSuanJiMing,			SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  3
	{	CONST_qyColumnDisplayType_str,	CONST_str_yongHuMing,			SQL_CHAR,		LVCFMT_LEFT, 100,  1, 50,	},	//  3
	//  {	CONST_qyColumnDisplayType_bool,	_T(  "是否服务器"  ),		SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  3
	{	CONST_qyColumnDisplayType_time,	CONST_str_lianTongShiJian,			SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  4
	{	-1,	NULL,														},
};

 QNM_QUERY_STRUCT  CONST_bhbLogQueryStruct  =  
{
	 CONST_bhbLogSqlColumns,	CONST_bhbLogDisplayColumns,
};


 //  显示离线日志列表
 QY_COLUMNINFO  CONST_bhbOfflineLogSqlColumns[]  =
{
	{	6,	_T(  "offlineComputerLogTab.officeName"  ),			SQL_CHAR,	},		//	6
	{	0,  _T(  "offlineComputerLogTab.subOfficeName"  ),		SQL_CHAR,	},		//	0
	{	1,	_T(  "offlineComputerLogTab.ip"  ),					SQL_CHAR,	},		//	1
	{	2,	_T(  "offlineComputerLogTab.mac"  ),				SQL_CHAR,	},		//  2
	{	3,	_T(  "offlineComputerLogTab.compName"  ),			SQL_CHAR,	},		//  3
	{	4,	_T(  "offlineComputerLogTab.usrName"  ),			SQL_CHAR,	},		//  4
	//  {	4,	_T(  "offlineComputerLogTab.is_server"  ),			SQL_CHAR,	},		//  4
	{	5,	_T(  "offlineComputerLogTab.firstRecvdTime"  ),		SQL_CHAR,	},		//  5
	{	5,	_T(  "offlineComputerLogTab.lastRecvdTime"  ),		SQL_CHAR,	},		//  5
	{	-1,	NULL,											},
};

 QY_COLUMNINFO	 CONST_bhbOfflineLogDisplayColumns[]  = 
{
	{	CONST_qyColumnDisplayType_str,	CONST_str_danWei,				SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,	CONST_str_buMen,				SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  2
	{	CONST_qyColumnDisplayType_str,	_T(  "IP"  ),					SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_str,	_T(  "MAC"  ),					SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  3
	{	CONST_qyColumnDisplayType_str,	CONST_str_jiSuanJiMing,			SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  3
	{	CONST_qyColumnDisplayType_str,	CONST_str_yongHuMing,			SQL_CHAR,		LVCFMT_LEFT, 100,  1, 50,	},	//  3
	//  {	CONST_qyColumnDisplayType_bool,	_T(  "是否服务器"  ),		SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  3
	{	CONST_qyColumnDisplayType_time,	CONST_str_lianTongShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  4
	{	CONST_qyColumnDisplayType_time,	CONST_str_duanKaiShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  4
	{	-1,	NULL,									},
};

 QNM_QUERY_STRUCT  CONST_bhbOfflineLogQueryStruct  =  
{
	 CONST_bhbOfflineLogSqlColumns,	CONST_bhbOfflineLogDisplayColumns,
};



 //  显示ScannedIP列表的结构	//  注：该结构对所有的版本一致，不需要定制
 QY_COLUMNINFO  CONST_scannedIpListSqlColumns[]  =
{
	{	6,	_T(  "qyPcTab.lastCommTime"  ),				SQL_CHAR,	},		//	6
	{	0,  _T(  "qnmScannedIpTab.ip"  ),				SQL_CHAR,	},		//	0
	{	1,	_T(  "qnmScannedIpTab.officeName"  ),		SQL_CHAR,	},		//	1
	{	2,	_T(  "qnmScannedIpTab.subOfficeName"  ),	SQL_CHAR,	},		//  2
	{	3,	_T(  "qnmScannedIpTab.mac"  ),				SQL_CHAR,	},		//  3
	{	4,	_T(  "qnmScannedIpTab.firstScannedTime"  ),	SQL_CHAR,	},		//  4
	{	5,	_T(  "qnmScannedIpTab.lastScannedTime"  ),	SQL_CHAR,	},		//  5
	{	-1,	NULL,											},
};

  QY_COLUMNINFO	 CONST_scannedIpListDisplayColumns[]  = 
{
	{	CONST_qyColumnDisplayType_time,	CONST_str_zuiJinLianXiShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  6	
	{	CONST_qyColumnDisplayType_ip12,	_T(  "IP"  ),						SQL_CHAR,		LVCFMT_LEFT, 100, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_str,	CONST_str_danWei,					SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,	CONST_str_buMen,					SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  2
	{	CONST_qyColumnDisplayType_str,	_T(  "MAC"  ),						SQL_CHAR,		LVCFMT_LEFT, 90,  1, 50,	},	//  3
	{	CONST_qyColumnDisplayType_time,	CONST_str_shouCiSaoMiaoShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  4
	{	CONST_qyColumnDisplayType_time,	CONST_str_zuiJinSaoMiaoShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  5
	{	-1,	NULL,									},
};

 QNM_QUERY_STRUCT  CONST_scannedIpListQueryStruct  =  
{
	 CONST_scannedIpListSqlColumns,	CONST_scannedIpListDisplayColumns,
};

/*
QNM_QUERY_STRUCT	*	gpBhbLogQueryStruct			=	&CONST_bhbLogQueryStruct;
QNM_QUERY_STRUCT	*	gpBhbOfflineLogQueryStruct	=	&CONST_bhbOfflineLogQueryStruct;
QNM_QUERY_STRUCT	*	gpScannedIpListQueryStruct	=	&CONST_scannedIpListQueryStruct;
*/

//  以下是的界面显示信息  {
#if  DEFAULT_qyCustomId  ==  CONST_qyCustomId_shhg

 //  简单用户信息的结构 
 QY_COLUMNINFO	CONST_shhgSimpleUsrSqlColumns[]  =  
{
	//  {	0,  _T(  "qyPcRegInfoTab.col0"  ),		SQL_CHAR,	},		//	0
	{	1,  _T(  "qyPcRegInfoTab.col1"  ),		SQL_CHAR,	},		//	1
	{	2,  _T(  "qyPcRegInfoTab.col2"  ),		SQL_CHAR,	},		//	2
	{	3,	_T(  "qyPcRegInfoTab.col3"  ),		SQL_CHAR,	},		//	3
	{	4,	_T(  "qyPcRegInfoTab.col4"  ),		SQL_CHAR,	},		//	4
	{	-1,											},
};

 QY_COLUMNINFO	CONST_shhgSimpleUsrDisplayColumns[]  = 
{
#if  0
    //  {	CONST_qyColumnDisplayType_str,	_T(  "用户类型"  ),		SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },	//  0
	{	CONST_qyColumnDisplayType_str,	_T(  "临时用户单位"  ),	SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },	//  1
	{	CONST_qyColumnDisplayType_str,	_T(  "关(处)名"  ),		SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },	//  2
	{	CONST_qyColumnDisplayType_str,	_T(  "科室"  ),			SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },	//  3
	{	CONST_qyColumnDisplayType_str,	_T(  "用户姓名"  ),		SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },	//  4
#endif 
	//
	{	-1,																						},
};

 QNM_QUERY_STRUCT  CONST_shhgSimpleUsrQueryStruct  =  
{
	 CONST_shhgSimpleUsrSqlColumns,  CONST_shhgSimpleUsrDisplayColumns,
};


 //  显示主机列表的结构 
 QY_COLUMNINFO	CONST_shhgPcListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcRegInfoTab.auditTime"  ),	SQL_CHAR,	},		//  0
	//  {	0,  _T(  "qyPcRegInfoTab.col0"  ),		SQL_CHAR,	},		//	0
	{	1,  _T(  "qyPcRegInfoTab.col1"  ),		SQL_CHAR,	},		//	1
	{	2,  _T(  "qyPcRegInfoTab.col2"  ),		SQL_CHAR,	},		//	2
	{	3,	_T(  "qyPcRegInfoTab.col3"  ),		SQL_CHAR,	},		//	3
	{	4,	_T(  "qyPcRegInfoTab.col4"  ),		SQL_CHAR,	},		//	4
	{	5,	_T(  "qyPcTab.ip"  ),				SQL_CHAR,	},		//	5
	{	6,	_T(  "qyPcTab.nMacs"  ),			SQL_CHAR,	},		//	6
	{	7,	_T(  "qyPcTab.osName"  ),			SQL_CHAR,	},		//	7
	{	8,	_T(  "qyPcTab.servicePack"  ),		SQL_CHAR,	},		//  8
	//  {	9,	_T(  "qyPcTab.proxyServer"  ),		SQL_CHAR,	},		//	9
	{	10,	_T(  "qyPcTab.mac0"  ),				SQL_CHAR,	},		//	10							
	{	11,	_T(  "qyPcTab.qwmVer"  ),			SQL_CHAR,	},		//  11
	{	-1,											},
};

 QY_COLUMNINFO	CONST_shhgPcListDisplayColumns[]  = 
{
#if  0
	{	CONST_qyColumnDisplayType_time,	_T(  "审核时间"  ),		SQL_CHAR,		LVCFMT_LEFT, 130, 1, 50, },	//  0
	//  {	CONST_qyColumnDisplayType_str,	_T(  "用户类型"  ),		SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },	//  0
	{	CONST_qyColumnDisplayType_str,	_T(  "临时用户单位"  ),	SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },	//  1
	{	CONST_qyColumnDisplayType_str,	_T(  "关(处)名"  ),		SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },	//  2
	{	CONST_qyColumnDisplayType_str,	_T(  "科室"  ),			SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },	//  3
	{	CONST_qyColumnDisplayType_str,	_T(  "用户姓名"  ),		SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },	//  4
	{	CONST_qyColumnDisplayType_ip12,	_T(  "IP"  ),			SQL_CHAR,		LVCFMT_LEFT, 100, 1, 50, },	//  5
	{	CONST_qyColumnDisplayType_str,	_T(  "网卡数"  ),		SQL_CHAR,		LVCFMT_LEFT, 60, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,	_T(  "操作系统"  ),		SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50,	},	//  7
	{	CONST_qyColumnDisplayType_str,	_T(  "ServicePack"  ),	SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50,	},	//  8
	//  {	CONST_qyColumnDisplayType_str,	_T(  "代理设置"  ),		SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50,	},	//  9
	{	CONST_qyColumnDisplayType_str,	_T(  "mac"  ),			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  10
	{	CONST_qyColumnDisplayType_str,	_T(  "客户端版本"  ),	SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  11
#endif 
	//
	{	-1,															},
};


 QNM_QUERY_STRUCT  CONST_shhgPcListQueryStruct  =  
{
	 CONST_shhgPcListSqlColumns,	CONST_shhgPcListDisplayColumns,
};



  //  显示免干扰主机列表的结构 
 QY_COLUMNINFO	CONST_shhgUnchkedPcListSqlColumns[]  =  
{
	//  {	0,  _T(  "qyPcRegInfoTab.col0"  ),		SQL_CHAR,	},		//	0
	{	1,  _T(  "qyPcRegInfoTab.col1"  ),		SQL_CHAR,	},		//	1
	{	2,  _T(  "qyPcRegInfoTab.col2"  ),		SQL_CHAR,	},		//	2
	{	3,	_T(  "qyPcRegInfoTab.col3"  ),		SQL_CHAR,	},		//	3
	{	4,	_T(  "qyPcRegInfoTab.col4"  ),		SQL_CHAR,	},		//	4
	{	5,	_T(  "qyPcTab.ip"  ),				SQL_CHAR,	},		//	5
	{	8,	_T(  "qyPcTab.mac0"  ),				SQL_CHAR,	},		//	8
	{	-1,											},
};

 QY_COLUMNINFO	CONST_shhgUnchkedPcListDisplayColumns[]  = 
{
#if  0
	//  {	CONST_qyColumnDisplayType_str,	_T(  "用户类型"  ),		SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },	//  0
	{	CONST_qyColumnDisplayType_str,	_T(  "临时用户单位"  ),		SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  1
	{	CONST_qyColumnDisplayType_str,	_T(  "关(处)名"  ),		SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  2
	{	CONST_qyColumnDisplayType_str,	_T(  "科室"  ),			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  3
	{	CONST_qyColumnDisplayType_str,	_T(  "用户姓名"  ),		SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  4
	{	CONST_qyColumnDisplayType_ip12,	_T(  "IP"  ),				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  4
	{	CONST_qyColumnDisplayType_str,	_T(  "mac"  ),				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50,	},	//  7
#endif 
	//
	{	-1,															},
};


  QNM_QUERY_STRUCT  CONST_shhgUnchkedPcListQueryStruct  =  
{
	 CONST_shhgUnchkedPcListSqlColumns,	CONST_shhgUnchkedPcListDisplayColumns,
};


 //  显示拨号权限列表的结构 
 QY_COLUMNINFO	CONST_shhgPcRuleListSqlColumns[]  =  
{
	//  {   0,	_T(  "qyPcRegInfoTab.col0"  ),			SQL_CHAR,	},		//  0
	{	1,	_T(  "qyPcRegInfoTab.col1"  ),			SQL_CHAR,	},		//  1
	{	2,	_T(  "qyPcRegInfoTab.col2"  ),			SQL_CHAR,	},		//	2
	{	3,	_T(  "qyPcRegInfoTab.col3"  ),			SQL_CHAR,	},		//	3
	{	4,	_T(  "qyPcRegInfoTab.col4"  ),			SQL_CHAR,	},		//	4
	{	5,	_T(  "qyPcTab.ip"  ),					SQL_CHAR,	},		//	5
	{	6,	_T(  "qyPcRuleTab.rasCmd"  ),			SQL_CHAR,	},		//	6							
	{   7,  _T(  "qyPcRuleTab.stopMon"  ),			SQL_CHAR,	},		//  7
	{	8,	_T(  "qyPcRuleTab.bUnchked"  ),			SQL_CHAR,	},		//  8
	{	9,	_T(  "qyPcTab.mac0"  ),					SQL_CHAR,	},		//	9
	{	-1,									},
};

 QY_COLUMNINFO	CONST_shhgPcRuleListDisplayColumns[] = 
{
#if  0
	//  {	CONST_qyColumnDisplayType_str,		_T(  "用户类型"  ),				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },
	{	CONST_qyColumnDisplayType_str,		_T(  "临时用户单位"  ),		SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },						   
	{	CONST_qyColumnDisplayType_str,		_T(  "关(处)名"  ),				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },
	{	CONST_qyColumnDisplayType_str,		_T(  "科室"  ),					SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },
	{	CONST_qyColumnDisplayType_str,		_T(  "用户姓名"  ),				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },
	{	CONST_qyColumnDisplayType_ip12,		_T(  "IP"  ),					SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },
	{	CONST_qyColumnDisplayType_rasCmd,	CONST_str_boHaoQuanXian,				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50,	},					   
	{	CONST_qyColumnDisplayType_bool,		_T(  "卸载"  ),					SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },		
	{	CONST_qyColumnDisplayType_bool,		_T(  "免检"  ),					SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },		
	{	CONST_qyColumnDisplayType_str,		_T(  "MAC"  ),					SQL_CHAR,		LVCFMT_LEFT, 80, 1,	50,	},
#endif 
	//
	{	-1,																	},
};

 QNM_QUERY_STRUCT  CONST_shhgPcRuleListQueryStruct  =  
{
	 CONST_shhgPcRuleListSqlColumns,	CONST_shhgPcRuleListDisplayColumns,
};


  //  显示用户列表的结构 
 QY_COLUMNINFO	CONST_shhgPcUsrListSqlColumns[]  =  
{
	{   0,	_T(  "qyPcRegInfoTab.col0"  ),			SQL_CHAR,	},		//  0
	{	1,	_T(  "qyPcRegInfoTab.col1"  ),			SQL_CHAR,	},		//  1
	{	2,	_T(  "qyPcRegInfoTab.col2"  ),			SQL_CHAR,	},		//	2
	{	3,	_T(  "qyPcRegInfoTab.col3"  ),			SQL_CHAR,	},		//	3
	{	4,	_T(  "qyPcRegInfoTab.col4"  ),			SQL_CHAR,	},		//	4
	{	5,	_T(  "qyPcRegInfoTab.col5"  ),			SQL_CHAR,	},		//	5
	{	6,	_T(  "qyPcRegInfoTab.col6"  ),			SQL_CHAR,	},		//	6
	{	7,	_T(  "qyPcRegInfoTab.col7"  ),			SQL_CHAR,	},		//	7
	{	8,	_T(  "qyPcRegInfoTab.col8"  ),			SQL_CHAR,	},		//	8
	{	9,	_T(  "qyPcRegInfoTab.col9"  ),			SQL_CHAR,	},		//	9
	{	10,	_T(  "qyPcRegInfoTab.col10"  ),			SQL_CHAR,	},		//	10
	{	11,	_T(  "qyPcRegInfoTab.col11"  ),			SQL_CHAR,	},		//	11
	{	12,	_T(  "qyPcTab.ip"  ),					SQL_CHAR,	},		//	12
	{	13,	_T(  "qyPcRegInfoTab.mac0"  ),			SQL_CHAR,	},		//	13
	{	-1,									},
};


 QY_COLUMNINFO	CONST_shhgPcUsrListDisplayColumns[] = 
{
#if  0
	{	CONST_qyColumnDisplayType_str,		_T(  "用户类型"  ),				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  0
	{	CONST_qyColumnDisplayType_str,		_T(  "临时用户单位"  ),		SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  1					   
	{	CONST_qyColumnDisplayType_str,		_T(  "关(处)名"  ),				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  2					   
	{	CONST_qyColumnDisplayType_str,		_T(  "科室"  ),					SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  3					   
	{	CONST_qyColumnDisplayType_str,		_T(  "用户姓名"  ),				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  4					   
	{	CONST_qyColumnDisplayType_str,		_T(  "联系电话"  ),				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  5					   
	{	CONST_qyColumnDisplayType_str,		CONST_str_sheBeiXingHao,				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  6					   
	{	CONST_qyColumnDisplayType_str,		_T(  "设备序列号"  ),			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  7					   
	{	CONST_qyColumnDisplayType_str,		_T(  "关产编号"  ),				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  8					   
	{	CONST_qyColumnDisplayType_str,		CONST_str_shiYongDiDian,				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  9					   
	{	CONST_qyColumnDisplayType_str,		_T(  "机器类型"  ),				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  10					   
	{	CONST_qyColumnDisplayType_str,		_T(  "主要用途"  ),				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  11					   
	{	CONST_qyColumnDisplayType_ip12,		_T(  "IP"  ),					SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  12					   
	{	CONST_qyColumnDisplayType_str,		_T(  "MAC"  ),					SQL_CHAR,		LVCFMT_LEFT, 80, 1,	50,	},	//  13					   
#endif 
	{	-1,																									},
};


 QNM_QUERY_STRUCT  CONST_shhgPcUsrListQueryStruct  =
{
	 CONST_shhgPcUsrListSqlColumns,  CONST_shhgPcUsrListDisplayColumns,
};



 //  显示所有事件列表的结构 
 QY_COLUMNINFO	CONST_shhgPcEventAllSqlColumns[]  =  
{
	{	0,	_T(  "qyPcEventTab.eventType"  ),		SQL_INTEGER,	},		//	0
	//  {	1,	_T(  "qyPcEventTab.col0"  ),			SQL_CHAR,		},		//  1
	{	2,	_T(  "qyPcEventTab.col1"  ),			SQL_CHAR,		},		//  2
	{	3,	_T(  "qyPcEventTab.col2"  ),			SQL_CHAR,		},		//	3
	{	4,	_T(  "qyPcEventTab.col3"  ),			SQL_CHAR,		},		//	4
	{	5,	_T(  "qyPcEventTab.col4"  ),			SQL_CHAR,		},		//	5
	{	6,	_T(  "qyPcEventTab.ip"  ),				SQL_CHAR,		},		//	6
	{	7,	_T(  "qyPcEventTab.cntEventTime"  ),	SQL_CHAR,		},		//	7
	{	8,	_T(  "qyPcEventTab.localEventTime"  ),	SQL_CHAR,		},		//	8
	{	9,	_T(  "qyPcEventTab.mac0"  ),			SQL_CHAR,		},		//	9
	{	10,	_T(  "qyPcEventTab.comment0"  ),			SQL_CHAR,		},		//  10
	{	-1,										},
};
 
 QY_COLUMNINFO	CONST_shhgPcEventAllDisplayColumns[] = 
{
#if  0
   {	CONST_qyColumnDisplayType_eventType,	CONST_str_event,				SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50, },	//  0
   //  {	CONST_qyColumnDisplayType_str,			_T(  "用户类型"  ),			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  1
   {	CONST_qyColumnDisplayType_str,			_T(  "临时用户单位"  ),		SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  2
   {	CONST_qyColumnDisplayType_str,			_T(  "关(处)名"  ),			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  3
   {	CONST_qyColumnDisplayType_str,			_T(  "科室"  ),				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//	4
   {	CONST_qyColumnDisplayType_str,			_T(  "用户姓名"  ),			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//	5
   {	CONST_qyColumnDisplayType_str,			_T(  "IP"  ),				SQL_CHAR,		LVCFMT_LEFT, 80, 1,	50,	},	//	6
   {	CONST_qyColumnDisplayType_time,			CONST_str_guanLiZhongXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50,	},	//	7
   {	CONST_qyColumnDisplayType_time,			CONST_str_benDiShiJian,			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//	8
   {	CONST_qyColumnDisplayType_str,			_T(  "MAC"  ),				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//	9
   {	CONST_qyColumnDisplayType_str,			CONST_str_beiZhu,				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//	10
#endif 
   //
   {	-1,																},
};


 QNM_QUERY_STRUCT  CONST_shhgPcEventAllQueryStruct  =  
{
	 CONST_shhgPcEventAllSqlColumns,	CONST_shhgPcEventAllDisplayColumns,
};



 //  显示拨号事件列表的结构 
 QY_COLUMNINFO	CONST_shhgPcRasEventSqlColumns[]  =  
{
	{	0,	_T(  "qyPcEventTab.eventType"  ),		SQL_INTEGER,	},		//	0
	//  {	1,	_T(  "qyPcEventTab.col0"  ),			SQL_CHAR,		},		//  1
	{	2,	_T(  "qyPcEventTab.col1"  ),			SQL_CHAR,		},		//  2
	{	3,	_T(  "qyPcEventTab.col2"  ),			SQL_CHAR,		},		//	3
	{	4,	_T(  "qyPcEventTab.col3"  ),			SQL_CHAR,		},		//	4
	{	5,	_T(  "qyPcEventTab.col4"  ),			SQL_CHAR,		},		//	5
	{	6,	_T(  "qyPcEventTab.des0"  ),			SQL_CHAR,		},		//  10
	{	7,	_T(  "qyPcEventTab.des1"  ),			SQL_CHAR,		},		//  11
	{	8,	_T(  "qyPcEventTab.cntEventTime"  ),	SQL_CHAR,		},		//	7
	{	9,	_T(  "qyPcEventTab.localEventTime"  ),	SQL_CHAR,		},		//	8
	{	10,	_T(  "qyPcEventTab.ip"  ),				SQL_CHAR,		},		//	6
	{	11,	_T(  "qyPcEventTab.mac0"  ),			SQL_CHAR,		},		//	9
	{	-1,													},
};
 
 QY_COLUMNINFO	CONST_shhgPcRasEventDisplayColumns[] = 
{
#if  0
   {	CONST_qyColumnDisplayType_eventType,	CONST_str_event,				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  0
   //  {	CONST_qyColumnDisplayType_str,			_T(  "用户类型"  ),			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  1
   {	CONST_qyColumnDisplayType_str,			_T(  "临时用户单位"  ),	SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  2
   {	CONST_qyColumnDisplayType_str,			_T(  "关(处)名"  ),			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  3
   {	CONST_qyColumnDisplayType_str,			_T(  "科室"  ),				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//	4
   {	CONST_qyColumnDisplayType_str,			_T(  "用户姓名"  ),			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//	5
   {	CONST_qyColumnDisplayType_str,			CONST_str_boHaoQuanXian,			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//	9
   {	CONST_qyColumnDisplayType_str,			CONST_str_boHaoHaoMa,			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//	9
   {	CONST_qyColumnDisplayType_time,			CONST_str_guanLiZhongXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50,	},	//	7
   {	CONST_qyColumnDisplayType_time,			CONST_str_benDiShiJian,			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//	8
   {	CONST_qyColumnDisplayType_str,			_T(  "IP"  ),				SQL_CHAR,		LVCFMT_LEFT, 80, 1,	50,	},	//	6
   {	CONST_qyColumnDisplayType_str,			_T(  "MAC"  ),				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//	9
#endif 
   //
   {	-1,																									},
};


 QNM_QUERY_STRUCT  CONST_shhgPcRasEventQueryStruct  =  
{
	 CONST_shhgPcRasEventSqlColumns,	CONST_shhgPcRasEventDisplayColumns,
};

  //  显示用户列表的结构 
 QY_COLUMNINFO	CONST_shhgPcUsrInTab1ListSqlColumns[]  =  
{
	{   0,	_T(  "qyPcRegInfoTab1.col0"  ),			SQL_CHAR,	},		//  0
	{	1,	_T(  "qyPcRegInfoTab1.col1"  ),			SQL_CHAR,	},		//  1
	{	2,	_T(  "qyPcRegInfoTab1.col2"  ),			SQL_CHAR,	},		//	2
	{	3,	_T(  "qyPcRegInfoTab1.col3"  ),			SQL_CHAR,	},		//	3
	{	4,	_T(  "qyPcRegInfoTab1.col4"  ),			SQL_CHAR,	},		//	4
	{	5,	_T(  "qyPcRegInfoTab1.col5"  ),			SQL_CHAR,	},		//	5
	{	6,	_T(  "qyPcRegInfoTab1.col6"  ),			SQL_CHAR,	},		//	6
	{	7,	_T(  "qyPcRegInfoTab1.col7"  ),			SQL_CHAR,	},		//	7
	{	8,	_T(  "qyPcRegInfoTab1.col8"  ),			SQL_CHAR,	},		//	8
	{	9,	_T(  "qyPcRegInfoTab1.col9"  ),			SQL_CHAR,	},		//	9
	{	10,	_T(  "qyPcRegInfoTab1.col10"  ),		SQL_CHAR,	},		//	10
	{	11,	_T(  "qyPcRegInfoTab1.col11"  ),		SQL_CHAR,	},		//	11
	{	12,	_T(  "qyPcTab.ip"  ),					SQL_CHAR,	},		//	12
	{	13,	_T(  "qyPcRegInfoTab1.mac0"  ),			SQL_CHAR,	},		//	13
	{	-1,									},
};


 QNM_QUERY_STRUCT  CONST_shhgPcUsrInTab1ListQueryStruct  =
{
	 CONST_shhgPcUsrInTab1ListSqlColumns,  CONST_shhgPcUsrListDisplayColumns,
};


QNM_QUERY_STRUCT	*	gpSimpleUsrQueryStruct			=  &CONST_shhgSimpleUsrQueryStruct;
QNM_QUERY_STRUCT	*	gpPcListQueryStruct				=  &CONST_shhgPcListQueryStruct;
QNM_QUERY_STRUCT	*	gpUnchkedPcListQueryStruct		=  &CONST_shhgUnchkedPcListQueryStruct;
QNM_QUERY_STRUCT	*	gpWillAttackPcListQueryStruct	=  &CONST_shhgUnchkedPcListQueryStruct;  //  &CONST_zjgaWillAttackPcListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcRasRuleListQueryStruct		=  &CONST_shhgPcRuleListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcUsrListQueryStruct			=  &CONST_shhgPcUsrListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcUsrInTab1ListQueryStruct	=  &CONST_shhgPcUsrInTab1ListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcEventAllQueryStruct			=  &CONST_shhgPcEventAllQueryStruct;
QNM_QUERY_STRUCT	*	gpPcRasEventQueryStruct			=  &CONST_shhgPcRasEventQueryStruct;

#endif
//  }  以上是的界面显示信息


//  以下是的界面显示信息  {
#if  DEFAULT_qyCustomId  ==  CONST_qyCustomId_zjga



 QY_COLUMNINFO  CONST_zjgaSimpleUsrSqlColumns[]  =
{
	 MACRO_zjgaSimpleUsrSqlColumns
	{	-1,											},

};

 QY_COLUMNINFO  CONST_zjgaSimpleUsrDisplayColumns[]  =
{
	 MACRO_zjgaSimpleUsrDisplayColumns
	{	-1,																							},
};

 QNM_QUERY_STRUCT  CONST_zjgaSimpleUsrQueryStruct  =  
{
	 CONST_zjgaSimpleUsrSqlColumns,	CONST_zjgaSimpleUsrDisplayColumns,
};



 //  显示主机列表的结构 
 QY_COLUMNINFO	CONST_zjgaPcListSqlColumns[]  =  
{
	//  {	0,	_T(  "qyPcRegInfoTab.auditTime"  ),		SQL_CHAR,	},
	{	15,		_T(  "qyPcTab.lastCommTime"  ),			SQL_CHAR,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,		_T(  "qyPcTab.ip"  ),					SQL_CHAR,	},		//	5
	{	6,		_T(  "qyPcTab.pcName"  ),				SQL_CHAR,	},		//	6		//  {	6,	"qyPcTab.nMacs"  ),		SQL_CHAR,	},		//	6
	{	7,		_T(  "qyPcTab.osName"  ),				SQL_CHAR,	},		//	7
	{	7,		_T(  "qyPcTab.servicePack"  ),			SQL_CHAR,	},		//	7
	//  {	7,	_T(  "qyPcTab.ucbAddedManually"  ),	SQL_CHAR,	},		//	7
	{	8,		_T(  "qyPcTab.mac0"  ),					SQL_CHAR,	},		//	8
	{	8,		_T(  "qyPcStatusTab.startTime"  ),		SQL_CHAR,	},
	{	-1,											},
};

 QY_COLUMNINFO	CONST_zjgaPcListDisplayColumns[]  = 
{
	//  {	CONST_qyColumnDisplayType_time,	CONST_str_shenHeShiJian,			SQL_CHAR,		LVCFMT_LEFT, 130, 1, 50, },	//  0
	{	CONST_qyColumnDisplayType_time,	CONST_str_zuiJinLianXiShiJian,	SQL_CHAR,		LVCFMT_LEFT, 115,  0, 0, },	//  8					   
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,	_T(  "IP"  ),					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  4
	{	CONST_qyColumnDisplayType_str,	CONST_str_jiSuanJiMing,			SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  5	//  {	CONST_qyColumnDisplayType_str,	"网卡数",			SQL_CHAR,		LVCFMT_LEFT, 50, 1, 50, },	//  5
	{	CONST_qyColumnDisplayType_str,	CONST_str_caoZuoXiTong,			SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,	CONST_str_buDing,				SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	//  {	CONST_qyColumnDisplayType_bool,	_T(  "手工登记"  ),			SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,	_T(  "mac"  ),					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50,	},	//  7
	{	CONST_qyColumnDisplayType_time,	CONST_str_caoZuoQiShiShiJian,	SQL_CHAR,		LVCFMT_LEFT, 100,1, 50,	},	//  7
	{	-1,																},
};


 QNM_QUERY_STRUCT  CONST_zjgaPcListQueryStruct  =  
{
	 CONST_zjgaPcListSqlColumns,	CONST_zjgaPcListDisplayColumns,
};


//////////////////////////


  //  显示主机列表的结构 
 QY_COLUMNINFO	CONST_zjgaPcListSqlColumns_netMc2[]  =  
{
	{	15,		_T(  "qyPcTab.lastCommTime"  ),			SQL_CHAR,	},
	{	15,		_T(  "qyPcTab.lastCommTime"  ),			SQL_CHAR,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,		_T(  "qyPcTab.ip"  ),					SQL_CHAR,	},		//	5
	{	6,		_T(  "qyPcTab.pcName"  ),				SQL_CHAR,	},		//	6		//  {	6,	"qyPcTab.nMacs"  ),		SQL_CHAR,	},		//	6
	{	7,		_T(  "qyPcTab.osName"  ),				SQL_CHAR,	},		//	7
	{	7,		_T(  "qyPcTab.servicePack"  ),			SQL_CHAR,	},		//	7
	//  {	7,	_T(  "qyPcTab.ucbAddedManually"  ),	SQL_CHAR,	},		//	7
	{	8,		_T(  "qyPcTab.mac0"  ),					SQL_CHAR,	},		//	8
	{	8,		_T(  "qyPcStatusTab.startTime"  ),		SQL_CHAR,	},
	{	-1,											},
};

 QY_COLUMNINFO	CONST_zjgaPcListDisplayColumns_netMc2[]  = 
{
	{	CONST_qyColumnDisplayType_bOnLine,		CONST_str_zhuangTai,			SQL_CHAR,		LVCFMT_LEFT, 60,  0, 0, },	//  8					   
	{	CONST_qyColumnDisplayType_time,			CONST_str_zuiJinLianXiShiJian,	SQL_CHAR,		LVCFMT_LEFT, 130,  0, 0, },	//  8					   
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,			_T(  "IP"  ),					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  4
	{	CONST_qyColumnDisplayType_str,			CONST_str_jiSuanJiMing,			SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  5	//  {	CONST_qyColumnDisplayType_str,	"网卡数",			SQL_CHAR,		LVCFMT_LEFT, 50, 1, 50, },	//  5
	{	CONST_qyColumnDisplayType_str,			CONST_str_caoZuoXiTong,			SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,			CONST_str_buDing,				SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	//  {	CONST_qyColumnDisplayType_bool,		_T(  "手工登记"  ),				SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,			_T(  "mac"  ),					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50,	},	//  7
	{	CONST_qyColumnDisplayType_time,			CONST_str_caoZuoQiShiShiJian,	SQL_CHAR,		LVCFMT_LEFT, 100,1, 50,	},	//  7
	{	-1,																},
};


 QNM_QUERY_STRUCT  CONST_zjgaPcListQueryStruct_netMc2  =  
{
	 CONST_zjgaPcListSqlColumns_netMc2,	CONST_zjgaPcListDisplayColumns_netMc2,
};



 //////////////////////



  //  显示主机资产列表的结构 
 QY_COLUMNINFO	CONST_zjgaPcAssetListSqlColumns[]  =  
{
	MACRO_zjgaSimpleUsrSqlColumns
	{	4,	_T(  "qyPcTab.ip"  ),				SQL_CHAR,	},		//	5
	{	5,	_T(  "qyPcAssetTab.iType"  ),		SQL_INTEGER,},
	{	6,	_T(  "qyPcAssetTab.name"  ),		SQL_CHAR,	},
	{	7,	_T(  "qyPcAssetTab.des0"  ),		SQL_CHAR,	},
	{	8,	_T(  "qyPcTab.pcName"  ),			SQL_CHAR,	},		//	6		
	{	9,	_T(  "qyPcAssetTab.endTime"  ),		SQL_CHAR,	},
	{	10,	_T(  "qyPcAssetTab.startTime"  ),	SQL_CHAR,	},
	{	11, _T(  "qyPcAssetTab.uiLangId"  ),	SQL_INTEGER,},
	{	11,	_T(  "qyPcAssetTab.iPlatformId"  ),	SQL_INTEGER,},		//	7
	{	12,	_T(  "qyPcAssetTab.winDir"  ),		SQL_CHAR,	},		//	7
	{	13,	_T(  "qyPcAssetTab.mac0"  ),		SQL_CHAR,	},		//	8
	{	-1,											},
};

 QY_COLUMNINFO	CONST_zjgaPcAssetListDisplayColumns[]  = 
{
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,			_T(  "IP"  ),					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  4
	{	CONST_qyColumnDisplayType_assetType,	CONST_str_sheBeiLeiXing,		SQL_CHAR,		LVCFMT_LEFT, 80,1, 50, },	//  4
	{	CONST_qyColumnDisplayType_str,			CONST_str_mingChen,				SQL_CHAR,		LVCFMT_LEFT, 200,1, 50, },	//  5	//  {	CONST_qyColumnDisplayType_str,	"网卡数",			SQL_CHAR,		LVCFMT_LEFT, 50, 1, 50, },	//  5
	{	CONST_qyColumnDisplayType_str,			CONST_str_miaoShu,				SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,			CONST_str_jiSuanJiMing,			SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_time,			CONST_str_zuiJinJianCeShiJian,	SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50, },	//  6
	{	CONST_qyColumnDisplayType_time,			CONST_str_shouCiJianCeShiJian,	SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50, },	//  6
	{	CONST_qyColumnDisplayType_langId,		CONST_str_yuYan,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },
	{	CONST_qyColumnDisplayType_platformId,	CONST_str_caoZuoXiTong,			SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,			CONST_str_xiTongMuLu,			SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,			_T(  "MAC"  ),					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50,	},	//  7
	{	-1,															},
};


 QNM_QUERY_STRUCT  CONST_zjgaPcAssetListQueryStruct  =  
{
	 CONST_zjgaPcAssetListSqlColumns,	CONST_zjgaPcAssetListDisplayColumns,
};




  //  显示主机硬件资产报表的结构 
 QY_COLUMNINFO	CONST_zjgaPcAssetReportListSqlColumns[]  =  
{
	MACRO_zjgaSimpleUsrSqlColumns
	{	CONST_fieldId_zcbh0,	_T(  "qyPcRegInfoTab.col13"  ),			SQL_CHAR,	0,  0,  0,	},		
	{	4,						_T(  "qnmTmpTab.des0"  ),				SQL_CHAR,	},
	{	5,						_T(  "qnmTmpTab.des1"  ),				SQL_CHAR,	},
	{	6,						_T(  "qnmTmpTab.des2"  ),				SQL_CHAR,	},
	{	7,						_T(  "qnmTmpTab.des3"  ),				SQL_CHAR,	},
	{	8,						_T(  "qnmTmpTab.des4"  ),				SQL_CHAR,	},
	{	4,						_T(  "qnmTmpTab.des5"  ),				SQL_CHAR,	},
	{	4,						_T(  "qnmTmpTab.des6"  ),				SQL_CHAR,	},
	{	13,						_T(  "qnmTmpTab.mac"  ),				SQL_CHAR,	},		//	8
	{	CONST_fieldId_zcbh1,	_T(  "qyPcRegInfoTab.col14"  ),			SQL_CHAR,	0,  0,  1,	},		//	8
	{	CONST_fieldId_zcsm1,	_T(  "qyPcRegInfoTab.col15"  ),			SQL_CHAR,	0,  0,  1,	},		//	8
	{	CONST_fieldId_zcbh2,	_T(  "qyPcRegInfoTab.col16"  ),			SQL_CHAR,	0,  0,  2,	},		//	8
	{	CONST_fieldId_zcsm2,	_T(  "qyPcRegInfoTab.col17"  ),			SQL_CHAR,	0,  0,  2,	},		//	8
	{	13,						_T(  "qnmTmpTab.col0"  ),				SQL_CHAR,	},
	{	13,						_T(  "qnmTmpTab.col1"  ),				SQL_CHAR,	},
	{	13,						_T(  "qnmTmpTab.col2"  ),				SQL_CHAR,	},
	{	-1,											},
};

  QY_COLUMNINFO	CONST_zjgaPcAssetReportListDisplayColumns[]  = 
{
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_str,			CONST_str_ziChanBianHao,		SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  4
	{	CONST_qyColumnDisplayType_str,			_T(  "CPU"  ),					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  4
	{	CONST_qyColumnDisplayType_str,			CONST_str_neiCun,				SQL_CHAR,		LVCFMT_LEFT, 70,1, 50, },	//  5	//  {	CONST_qyColumnDisplayType_str,	"网卡数"  ),			SQL_CHAR,		LVCFMT_LEFT, 50, 1, 50, },	//  5
	{	CONST_qyColumnDisplayType_str,			_T(  "Bios"  ),					SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,			CONST_str_yingPan,				SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,			CONST_str_guangQu,				SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,			CONST_str_wangKa,				SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50, },	//  6
	{	CONST_qyColumnDisplayType_str,			CONST_str_xianKa,				SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50, },	//  6
	{	CONST_qyColumnDisplayType_str,			_T(  "MAC"  ),					SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },
	{	CONST_qyColumnDisplayType_str,			CONST_str_ziChanBianHao1,		SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  4
	{	CONST_qyColumnDisplayType_str,			CONST_str_ziChanShuoMing1,		SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  4
	{	CONST_qyColumnDisplayType_str,			CONST_str_ziChanBianHao2,		SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  4
	{	CONST_qyColumnDisplayType_str,			CONST_str_ziChanShuoMing2,		SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  4
	{	CONST_qyColumnDisplayType_str,			CONST_str_yuYan,				SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,			CONST_str_caoZuoXiTong,			SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,			CONST_str_xiTongMuLu,			SQL_CHAR,		LVCFMT_LEFT, 100,1, 50,	},	//  7
	{	-1,															},
};


 QY_COLUMNINFO	CONST_zjgaPcAssetReportListDisplayColumns_en[]  = 
{
	MACRO_zjgaSimpleUsrDisplayColumns_en
	{	CONST_qyColumnDisplayType_str,			_T(  "AssetsNo"  ),			SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  4
	{	CONST_qyColumnDisplayType_str,			_T(  "CPU"  ),				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  4
	{	CONST_qyColumnDisplayType_str,			_T(  "Mem"  ),				SQL_CHAR,		LVCFMT_LEFT, 70,1, 50, },	//  5	//  {	CONST_qyColumnDisplayType_str,	"网卡数",			SQL_CHAR,		LVCFMT_LEFT, 50, 1, 50, },	//  5
	{	CONST_qyColumnDisplayType_str,			_T(  "Bios"  ),				SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,			_T(  "Disk"  ),				SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,			_T(  "Cdrom"  ),			SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,			_T(  "NetworkCard"  ),		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50, },	//  6
	{	CONST_qyColumnDisplayType_str,			_T(  "Display"  ),			SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50, },	//  6
	{	CONST_qyColumnDisplayType_str,			_T(  "MAC"  ),				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },
	{	CONST_qyColumnDisplayType_str,			_T(  "AssetsNo1"  ),		SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  4
	{	CONST_qyColumnDisplayType_str,			_T(  "AssetsDesc1"  ),		SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  4
	{	CONST_qyColumnDisplayType_str,			_T(  "AssetsNo2"  ),		SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  4
	{	CONST_qyColumnDisplayType_str,			_T(  "AssetsDesc2"  ),		SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//  4
	{	CONST_qyColumnDisplayType_str,			_T(  "Language"  ),			SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,			_T(  "OS"  ),				SQL_CHAR,		LVCFMT_LEFT, 70, 1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,			_T(  "WinDir"  ),			SQL_CHAR,		LVCFMT_LEFT, 100,1, 50,	},	//  7
	{	-1,															},
};


 QNM_QUERY_STRUCT  CONST_zjgaPcAssetReportListQueryStruct  =  
{
	 CONST_zjgaPcAssetReportListSqlColumns,	CONST_zjgaPcAssetReportListDisplayColumns,
};

 QNM_QUERY_STRUCT  CONST_zjgaPcAssetReportListQueryStruct_en  =  
{
	 CONST_zjgaPcAssetReportListSqlColumns,	CONST_zjgaPcAssetReportListDisplayColumns_en,
};





 

 //  显示补丁列表的结构 
 QY_COLUMNINFO	CONST_zjgaPcSpListSqlColumns[]  =  
{
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),				SQL_CHAR,	},		//	5
	{	7,	_T(  "qyPcSpTab.osName"  ),			SQL_CHAR,	},		//	7
	{	7,	_T(  "qyPcSpTab.servicePack"  ),	SQL_CHAR,	},		//	7
	{	7,	_T(  "qyPcSpTab.spName"  ),			SQL_CHAR,	},
	{	7,	_T(  "qyCusNameTab.cusName0"  ),		SQL_CHAR,	},
	{	7,	_T(  "qyPcSpTab.lastTime"  ),		SQL_CHAR,	},
	{	8,	_T(  "qyPcTab.mac0"  ),				SQL_CHAR,	},		//	8
	{	7,	_T(  "qyPcSpTab.winDir"  ),			SQL_CHAR,	},		//  7
	{	-1,											},
};

 QY_COLUMNINFO	CONST_zjgaPcSpListDisplayColumns[]  = 
{
 	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,		_T(  "IP"  ),					SQL_CHAR,		LVCFMT_LEFT, 100,	1,	50, },	//  4
	{	CONST_qyColumnDisplayType_str,		CONST_str_caoZuoXiTong,			SQL_CHAR,		LVCFMT_LEFT, 70,	1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,		_T(  "Service Pack"  ),			SQL_CHAR,		LVCFMT_LEFT, 160,	1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_pcSp,		CONST_str_buDing,				SQL_CHAR,		LVCFMT_LEFT, 70,	1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,		CONST_str_buDingBieMing,		SQL_CHAR,		LVCFMT_LEFT, 70,	1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_time,		CONST_str_zuiJinJianCeShiJian,	SQL_CHAR,		LVCFMT_LEFT, 130,	1,	50,	},	//  6
	{	CONST_qyColumnDisplayType_str,		_T(  "MAC"  ),					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50,	},	//  7
	{	CONST_qyColumnDisplayType_str,		CONST_str_xiTongMuLu,			SQL_CHAR,		LVCFMT_LEFT, 80,	1,	50,	},	//  6
	{	-1,																	},
};


 QNM_QUERY_STRUCT  CONST_zjgaPcSpListQueryStruct  =  
{
	 CONST_zjgaPcSpListSqlColumns,	CONST_zjgaPcSpListDisplayColumns,
};


  //  显示特殊补丁列表的结构 
 QY_COLUMNINFO	CONST_zjgaPcSpSpecialListSqlColumns[]  =  
{
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),				SQL_CHAR,	},		//	5
	{	7,	_T(  "qyPcTab.osName"  ),			SQL_CHAR,	},		//	7
	//  {	7,	_T(  "qyPcSpTab.servicePack"  ),	SQL_CHAR,	},		//	7
	{	7,	_T(  "qnmTmpTab.des0"  ),			SQL_CHAR,	},
	//  {	7,	_T(  "qyPcSpTab.spName"  ),			SQL_CHAR,	},
	{	7,	_T(  "qnmTmpTab.col0"  ),			SQL_CHAR,	},
	{	7,	_T(  "qyCusNameTab.cusName0"  ),		SQL_CHAR,	},
	//  {	7,	_T(  "qyPcSpTab.lastTime"  ),		SQL_CHAR,	},
	{	7,	_T(  "qnmTmpTab.des1"  ),			SQL_CHAR,	},
	{	8,	_T(  "qyPcTab.mac0"  ),				SQL_CHAR,	},		//	8
	{	7,	_T(  "qyPcTab.winDir"  ),			SQL_CHAR,	},
	{	-1,											},
};

#define		CONST_zjgaPcSpSpecialListDisplayColumns		CONST_zjgaPcSpListDisplayColumns

 QNM_QUERY_STRUCT  CONST_zjgaPcSpSpecialListQueryStruct  =  
{
	 CONST_zjgaPcSpSpecialListSqlColumns,	CONST_zjgaPcSpSpecialListDisplayColumns,
};


 ////////////////////////////////////////////////

 //
 //  显示用户列表的结构 
 QY_COLUMNINFO	CONST_zjgaPcUsrListSqlColumns[]  =  
{
	{	0,						_T(  "qyPcRegInfoTab.auditTime"  ),		SQL_CHAR,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	CONST_fieldId_jqlx,		_T(  "qyPcRegInfoTab.col5"  ),			SQL_CHAR,	0,  0,  0,	},		//	5
	{	CONST_fieldId_zcbh0,	_T(  "qyPcRegInfoTab.col13"  ),			SQL_CHAR,	0,  0,  0,	},		
	{	CONST_fieldId_zyyt,		_T(  "qyPcRegInfoTab.col6"  ),			SQL_CHAR,	0,  0,  0,	},		//	6
	{	CONST_fieldId_lxdh,		_T(  "qyPcRegInfoTab.col7"  ),			SQL_CHAR,	0,  0,  0,	},		//	7
	{	CONST_fieldId_sydd,		_T(  "qyPcRegInfoTab.col10"  ),			SQL_CHAR,	0,  0,  0,	},		//	10
	{	CONST_fieldId_zcbh1,	_T(  "qyPcRegInfoTab.col14"  ),			SQL_CHAR,	0,  0,  1,	},		//	8
	{	CONST_fieldId_zcsm1,	_T(  "qyPcRegInfoTab.col15"  ),			SQL_CHAR,	0,  0,  1,	},		//	8
	{	CONST_fieldId_zcbh2,	_T(  "qyPcRegInfoTab.col16"  ),			SQL_CHAR,	0,  0,  2,	},		//	8
	{	CONST_fieldId_zcsm2,	_T(  "qyPcRegInfoTab.col17"  ),			SQL_CHAR,	0,  0,  2,	},		//	8
	{	11,						_T(  "qyPcTab.ip"  ),					SQL_CHAR,	0,  0,  0,	},		//	11
	{	12,						_T(  "qyPcRegInfoTab.mac0"  ),			SQL_CHAR,	0,  0,  0,	},		//	12
	{	-1,									},
};

 QY_COLUMNINFO	CONST_zjgaPcUsrListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_time,		CONST_str_shenHeShiJian,			SQL_CHAR,		LVCFMT_LEFT, 130, 1, 50, },	//  0
	MACRO_zjgaSimpleUsrDisplayColumns
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
	{	CONST_qyColumnDisplayType_str,		_T(  "MAC"  ),						SQL_CHAR,		LVCFMT_LEFT, 100,1,	50,	},	//  12					   
	{	-1,																									},
};


 QNM_QUERY_STRUCT  CONST_zjgaPcUsrListQueryStruct  =
{
	 CONST_zjgaPcUsrListSqlColumns,  CONST_zjgaPcUsrListDisplayColumns,
};

  //  显示用户重复注册列表的结构 
 QY_COLUMNINFO	CONST_zjgaPcUsrInTab1ListSqlColumns[]  =  
{
	//  {   0,	_T(  "qyPcRegInfoTab1.bOk"  ),			SQL_CHAR,	},		//  0
 	{	0,						_T(  "qyPcRegInfoTab1.auditTime"  ),		SQL_CHAR,	},
	MACRO_zjgaSimpleUsrInTab1SqlColumns
	{	CONST_fieldId_jqlx,		_T(  "qyPcRegInfoTab1.col5"  ),				SQL_CHAR,	0,  0,  0,	},		//	5
	{	CONST_fieldId_zcbh0,	_T(  "qyPcRegInfoTab1.col13"  ),			SQL_CHAR,	0,  0,  0,	},		
	{	CONST_fieldId_zyyt,		_T(  "qyPcRegInfoTab1.col6"  ),				SQL_CHAR,	0,  0,  0,	},		//	6
	{	CONST_fieldId_lxdh,		_T(  "qyPcRegInfoTab1.col7"  ),				SQL_CHAR,	0,  0,  0,	},		//	7
	{	CONST_fieldId_sydd,		_T(  "qyPcRegInfoTab1.col10"  ),			SQL_CHAR,	0,  0,  0,	},		//	10
	{	CONST_fieldId_zcbh1,	_T(  "qyPcRegInfoTab1.col14"  ),			SQL_CHAR,	0,  0,  1,	},		//	8
	{	CONST_fieldId_zcsm1,	_T(  "qyPcRegInfoTab1.col15"  ),			SQL_CHAR,	0,  0,  1,	},		//	8
	{	CONST_fieldId_zcbh2,	_T(  "qyPcRegInfoTab1.col16"  ),			SQL_CHAR,	0,  0,  2,	},		//	8
	{	CONST_fieldId_zcsm2,	_T(  "qyPcRegInfoTab1.col17"  ),			SQL_CHAR,	0,  0,  2,	},		//	8
	{	11,						_T(  "qyPcTab.ip"  ),						SQL_CHAR,	},		//	11
	{	12,						_T(  "qyPcRegInfoTab1.mac0"  ),				SQL_CHAR,	},		//	12
	{	-1,									},
};


 QNM_QUERY_STRUCT  CONST_zjgaPcUsrInTab1ListQueryStruct  =
{
	 CONST_zjgaPcUsrInTab1ListSqlColumns,  CONST_zjgaPcUsrListDisplayColumns,
};


 //  2005/05/10, 客户端列表
 QY_COLUMNINFO  CONST_zjgaQwmSvrListSqlColumns[]  =
{
	 MACRO_zjgaSimpleUsrSqlColumns
	 {	11,						_T(  "qyPcTab.ip"  ),						SQL_CHAR,	},		//	11
	 {	13,						_T(  "qyPcTab.qwmVer"  ),					SQL_CHAR,	},
	 {	13,						_T(  "qwmSvrTab.seqNo"  ),						SQL_CHAR,	},
	 {	14,						_T(  "qyPcTab.startTime"  ),				SQL_CHAR,	},
	 {	15,						_T(  "qyPcTab.lastCommTime"  ),				SQL_CHAR,	},
	 {	12,						_T(  "qyPcTab.mac0"  ),						SQL_CHAR,	},		//	12
	 {	16,						_T(  "qyPcTab.uiLangId"  ),					SQL_INTEGER,},
	 {	17,						_T(  "qyPcTab.iPlatformId"  ),				SQL_INTEGER,},
	 {	18,						_T(  "qyPcTab.winDir"  ),					SQL_CHAR,	},
	 {	-1,						},
};

 QY_COLUMNINFO  CONST_zjgaQwmSvrListDisplayColumns[]  =
{	 
	 MACRO_zjgaSimpleUsrDisplayColumns
	 {	CONST_qyColumnDisplayType_ip12,			_T(  "IP"  ),					SQL_CHAR,		LVCFMT_LEFT, 100,  0, 0, },	//  8					   
	 {	CONST_qyColumnDisplayType_str,			CONST_str_banBen,				SQL_CHAR,		LVCFMT_LEFT, 80,  0, 0, },	//  8					   
	 {	CONST_qyColumnDisplayType_str,			CONST_str_biaoShiFu,			SQL_CHAR,		LVCFMT_LEFT, 80,  0, 0, },	//  8					   
	 {	CONST_qyColumnDisplayType_time,			CONST_str_fenFaShiJian,			SQL_CHAR,		LVCFMT_LEFT, 115,  0, 0, },	//  8					   
	 {	CONST_qyColumnDisplayType_time,			CONST_str_zuiJinLianXiShiJian,	SQL_CHAR,		LVCFMT_LEFT, 115,  0, 0, },	//  8					   
	 {	CONST_qyColumnDisplayType_str,			_T(  "MAC"  ),					SQL_CHAR,		LVCFMT_LEFT, 90,  0, 0, },	//  8					   
	 {	CONST_qyColumnDisplayType_langId,		CONST_str_yuYan,				SQL_CHAR,		LVCFMT_LEFT, 70,  0, 0, },	//  8					   
	 {	CONST_qyColumnDisplayType_platformId,	CONST_str_caoZuoXiTong,			SQL_CHAR,		LVCFMT_LEFT, 70,  0, 0, },	//  8					   
	 {	CONST_qyColumnDisplayType_str,			CONST_str_xiTongMuLu,			SQL_CHAR,		LVCFMT_LEFT, 90,  0, 0, },	//  8					   


	 {	-1,						},
};


 QNM_QUERY_STRUCT  CONST_zjgaQwmSvrListQueryStruct  =
{
	 CONST_zjgaQwmSvrListSqlColumns,  CONST_zjgaQwmSvrListDisplayColumns,
};


//////////////////////////////////////////


 //  显示拨号权限列表的结构 
 QY_COLUMNINFO	CONST_zjgaPcRuleListSqlColumns0[]  =  
{
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),					SQL_CHAR,	},		//	5
	{	6,	_T(  "qyPcRuleTab.col1"  ),				SQL_CHAR,	},
	{	6,	_T(  "qyPcRuleTab.col0"  ),				SQL_CHAR,	},
	{	6,	_T(  "qyPcRuleTab.col2"  ),				SQL_CHAR,	},		//  
	{	6,	_T(  "qyPcRuleTab.col3"  ),				SQL_CHAR,	},		//  
	{	6,	_T(  "qyPcRuleTab.col4"  ),				SQL_CHAR,	},		//  
	{	6,	_T(  "qyPcRuleTab.col5"  ),				SQL_CHAR,	},		//  
	{	6,	_T(  "qyPcRuleTab.col6"  ),				SQL_CHAR,	},		//  
	{	6,	_T(  "qyPcRuleTab.col7"  ),				SQL_CHAR,	},		//  
	{	6,	_T(  "qyPcRuleTab.col8"  ),				SQL_CHAR,	},		//  
	{	6,	_T(  "qyPcRuleTab.col9"  ),				SQL_CHAR,	},		//  
	{	6,	_T(  "qyPcRuleTab.col10"  ),			SQL_CHAR,	},		//  
	//
	{	6,	_T(  "qyPcRuleTab.col11"  ),			SQL_CHAR,	},		//  
	{	6,	_T(  "qyPcRuleTab.col12"  ),			SQL_CHAR,	},		//  
	{	6,	_T(  "qyPcRuleTab.col13"  ),			SQL_CHAR,	},		//  
	{	6,	_T(  "qyPcRuleTab.col14"  ),			SQL_CHAR,	},		//  
	//
	{   7,  _T(  "qyPcRuleTab.stopMon"  ),			SQL_CHAR,	},		//  7
	{	8,	_T(  "qyPcRuleTab.bUnchked"  ),			SQL_CHAR,	},		//  8
	{	9,	_T(  "qyPcRuleTab.bDoSecChk"  ),		SQL_CHAR,	},
	//  {	9,	_T(  "qyPcTab.mac0"  ),					SQL_CHAR,	},		//	9
	{	9,	_T(  "qyPcRuleTab.mac0"  ),					SQL_CHAR,	},		//	9
	{	-1,									},
};

 QY_COLUMNINFO	CONST_zjgaPcRuleListDisplayColumns0[] = 
{
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,				_T(  "IP"  ),						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_yuanChengShangWangBaoJing,SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_anQuanMoShi,				SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_xiTongShiJianShenJi,		SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_caoZuoXiTongYongHuShenJi,	SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_daYinJiShenJi,			SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_netStatShenJi,			SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_str,				CONST_str_wenJianShenJiMuLu,		SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_pingMuKaoBei,				SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_jinChengMoKuaiShenJi,		SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_zhuCeBiaoJianKong,		SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_netFlowRule,		CONST_str_liuLiangGuanLi,			SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	//
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_autorunCmd,				SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_netShareCmd,				SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_adminCmd,					SQL_CHAR,		LVCFMT_LEFT, 78,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_ucHideQwmCmd,				SQL_CHAR,		LVCFMT_LEFT, 98,1, 50, },
	//
	{	CONST_qyColumnDisplayType_bool,				CONST_str_xieZai,					SQL_CHAR,		LVCFMT_LEFT, 50, 1, 50, },		
	{	CONST_qyColumnDisplayType_bool,				CONST_str_mianJian,					SQL_CHAR,		LVCFMT_LEFT, 50, 1, 50, },		
	{	CONST_qyColumnDisplayType_bool,				CONST_str_anQuanJianCha,			SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },		
	{	CONST_qyColumnDisplayType_str,				_T(  "MAC"  ),						SQL_CHAR,		LVCFMT_LEFT, 100,1,	50,	},
	{	-1,																		},
};

 QNM_QUERY_STRUCT  CONST_zjgaPcRuleListQueryStruct0  =  
{
	 CONST_zjgaPcRuleListSqlColumns0,	CONST_zjgaPcRuleListDisplayColumns0,
};


 ////////////

  //  显示拨号权限列表的结构 
 QY_COLUMNINFO	CONST_zjgaPcRuleListSqlColumns1[]  =  
{
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),					SQL_CHAR,	},		//	5
	{	6,	_T(  "qyPcRuleTab.floppyCmd"  ),		SQL_CHAR,	},
	{	6,	_T(  "qyPcRuleTab.cdromCmd"  ),			SQL_CHAR,	},
	{	6,	_T(  "qyPcRuleTab.usbCmd"  ),			SQL_CHAR,	},
	{	6,	_T(  "qyPcRuleTab.col15"  ),			SQL_CHAR,	},		//  2010/05/20
	{	6,	_T(  "qyPcRuleTab.rasCmd"  ),			SQL_CHAR,	},		//	6	

	{	6,	_T(  "qyPcRuleTab.col16"  ),			SQL_CHAR,	},		//  
	{	6,	_T(  "qyPcRuleTab.col17"  ),			SQL_CHAR,	},		//  
	{	6,	_T(  "qyPcRuleTab.col18"  ),			SQL_CHAR,	},		//  
	{	6,	_T(  "qyPcRuleTab.col19"  ),			SQL_CHAR,	},		//  
	{	6,	_T(  "qyPcRuleTab.col20"  ),			SQL_CHAR,	},		//  
	{	6,	_T(  "qyPcRuleTab.col21"  ),			SQL_CHAR,	},		//  
	{	6,	_T(  "qyPcRuleTab.col22"  ),			SQL_CHAR,	},		//  


	//  {	9,	_T(  "qyPcTab.mac0"  ),					SQL_CHAR,	},		//	9
	{	9,	_T(  "qyPcRuleTab.mac0"  ),					SQL_CHAR,	},		//	9	//  2011/09/21
	{	-1,									},
};

 QY_COLUMNINFO	CONST_zjgaPcRuleListDisplayColumns1[] = 
{
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,				_T(  "IP"  ),						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_ruanQu,					SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_guangQu,					SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			_T(  "USB"  ),						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_wLanAdapter,				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_rasCmd,			CONST_str_boHaoQuanXian,			SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50,	},					   

	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_blueTooth,				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_infrared,					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_1394,						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_wpd,						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_sdHostAdapter,			SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_mobileDevice,				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_devCmd,			CONST_str_usbNetworkCard,			SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },


	{	CONST_qyColumnDisplayType_str,				_T(  "MAC"  ),						SQL_CHAR,		LVCFMT_LEFT, 100,1,	50,	},
	{	-1,																		},
};

 QNM_QUERY_STRUCT  CONST_zjgaPcRuleListQueryStruct1  =  
{
	 CONST_zjgaPcRuleListSqlColumns1,	CONST_zjgaPcRuleListDisplayColumns1,
};





 //  终端的网络连接属性, 2005/05/25
 QY_COLUMNINFO	CONST_zjgaPcAdapterListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcAdapterTab.id"  ),					SQL_INTEGER,	},
	{	0,	_T(  "qyPcAdapterTab.iStatus"  ),				SQL_INTEGER,	},
	MACRO_zjgaSimpleUsrSqlColumns
	//  {	5,	_T(  "qyPcTab.ip"  ),								SQL_CHAR,		},		//	5
	{	5,	_T(  "qyPcTab.pcName"  ),						SQL_CHAR,		},
	//  {	6,	_T(  "qyPcAdapterTab.uiType"  ),				SQL_INTEGER,	},
	{	6,	_T(  "qyPcAdapterTab.des0"  ),					SQL_CHAR,		},
	{	6,	_T(  "qyPcAdapterTab.devDesc"  ),				SQL_CHAR,		},
	{	6,	_T(  "qyPcAdapterTab.uiAdapterType"  ),			SQL_INTEGER,	},
	{	6,	_T(  "qyPcAdapterTab.mac"  ),					SQL_CHAR,	},		//
	{	6,	_T(  "qyPcAdapterTab.ipBuf"  ),					SQL_CHAR,	},
	{	6,	_T(  "qyPcAdapterTab.ipMaskBuf"  ),				SQL_CHAR,	},
	{	6,	_T(  "qyPcAdapterTab.gatewayBuf"  ),			SQL_CHAR,	},
	{	6,	_T(  "qyPcAdapterTab.ucbDhcpEnabled"  ),		SQL_CHAR,	},
	{	6,	_T(  "qyPcAdapterTab.dhcpServerIp"  ),			SQL_CHAR,	},
	{	6,	_T(  "qyPcAdapterTab.ucbAutoDns"  ),			SQL_CHAR,	},
	{	6,	_T(  "qyPcAdapterTab.dnsBuf"  ),				SQL_CHAR,	},
	//  {	6,	_T(  "qyPcAdapterTab.proxyBuf"  ),				SQL_CHAR,	},
	{	6,	_T(  "qyPcAdapterTab.ucbHaveWins"  ),			SQL_CHAR,	},
	{	6,	_T(  "qyPcAdapterTab.primaryWinsServerIp"  ),	SQL_CHAR,	},
	{	6,	_T(  "qyPcAdapterTab.secondaryWinsServerIp"  ),	SQL_CHAR,	},
	{	6,	_T(  "qyPcAdapterTab.lastTime"  ),				SQL_CHAR,	},
	//
	{	9,	_T(  "qyPcAdapterTab.mac0"  ),					SQL_CHAR,	},		//	9
	{	-1,									},
};

 QY_COLUMNINFO	CONST_zjgaPcAdapterListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,					SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	{	CONST_qyColumnDisplayType_pcAdapterStatus,		CONST_str_zhuangTai,				SQL_CHAR,		LVCFMT_LEFT, 80,1, 50, },
	MACRO_zjgaSimpleUsrDisplayColumns
	//  {	CONST_qyColumnDisplayType_ip12,					_T(  "IP"  ),					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_jiSuanJiMing,				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//  {	CONST_qyColumnDisplayType_pcNetworkPropType,	CONST_str_leiXing,				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_miaoShu,					SQL_CHAR,		LVCFMT_LEFT, 0,  1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_mingChen,					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_adapterType,			CONST_str_wangKaLeiXing,			SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_wangKaMAC,				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_wangKaIP,					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_yanMa,					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_luYou,					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_shiFoQiDongDHCP,			SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_DHCPFuWuQi,				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_shiFoZiDongHuoDeDNS,		SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	{	CONST_qyColumnDisplayType_str,					_T(  "DNS"  ),						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//  {	CONST_qyColumnDisplayType_str,					_T(  "Proxy"  ),				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_shiFoQiYongWINS,			SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_WINSZhuFuWuQi,			SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_WINSErJiZhuFuWuQi,		SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_time,					CONST_str_zuiXinShuaXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	//
	{	CONST_qyColumnDisplayType_str,					_T(  "MAC"  ),						SQL_CHAR,		LVCFMT_LEFT, 100,1,	50,	},
	{	-1,																	},
};



 QNM_QUERY_STRUCT  CONST_zjgaPcAdapterListQueryStruct  =
{
	 CONST_zjgaPcAdapterListSqlColumns,  CONST_zjgaPcAdapterListDisplayColumns,
};

//


 //  终端的代理设置属性, 2005/05/25
 QY_COLUMNINFO	CONST_zjgaPcProxyCfgListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcAdapterTab.id"  ),						SQL_INTEGER,	},
	{	0,	_T(  "qyPcAdapterTab.iStatus"  ),					SQL_INTEGER,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),								SQL_CHAR,		},		//	5
	//  {	6,	_T(  "qyPcAdapterTab.uiType"  ),				SQL_INTEGER,	},
	{	6,	_T(  "qyPcAdapterTab.iParam0"  ),					SQL_INTEGER,	},
	{	6,	_T(  "qyPcAdapterTab.paramStr0"  ),					SQL_CHAR,		},
	{	6,	_T(  "qyPcAdapterTab.iProp0"  ),					SQL_INTEGER,	},	//	pUsrInfo->ucbEnableAutodial;  uiProps  ++  ;
	{	6,	_T(  "qyPcAdapterTab.iProp1"  ),					SQL_INTEGER,	},	//  pUsrInfo->ucbNoNetAutodial;  uiProps  ++  ;
	{	6,	_T(  "qyPcAdapterTab.iProp2"  ),					SQL_INTEGER,	},	//  pUsrInfo->ucbAutoDetectSettings;  uiProps  ++  ;
	{	6,	_T(  "qyPcAdapterTab.propStr2"  ),					SQL_CHAR,		},	//  pUsrInfo->AutoConfigURL,  pRcd->propStrs[uiPropStrs],  sizeof(  pRcd->propStrs[uiPropStrs]  )  );  uiPropStrs  ++  ;
	{	6,	_T(  "qyPcAdapterTab.iProp3"  ),					SQL_INTEGER,	},	//  pUsrInfo->ucbProxyEnable;  uiProps  ++  ;
	{	6,	_T(  "qyPcAdapterTab.propStr0"  ),					SQL_CHAR,		},		//  pUsrInfo->proxyServer,  pRcd->propStrs[uiPropStrs],  sizeof(  pRcd->propStrs[uiPropStrs]  )  );  uiPropStrs  ++  ;
	{	6,	_T(  "qyPcAdapterTab.propStr1"  ),					SQL_CHAR,		},		//  pUsrInfo->proxyOverride,  pRcd->propStrs[uiPropStrs],  sizeof(  pRcd->propStrs[uiPropStrs]  )  );  uiPropStrs  ++  ;
	{	6,	_T(  "qyPcAdapterTab.lastTime"  ),					SQL_CHAR,		},
	//
	{	9,	_T(  "qyPcAdapterTab.mac0"  ),						SQL_CHAR,		},		//	9
	{	-1,									},
};

 QY_COLUMNINFO	CONST_zjgaPcProxyCfgListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	{	CONST_qyColumnDisplayType_pcAdapterStatus,		CONST_str_zhuangTai,								SQL_CHAR,		LVCFMT_LEFT, 80,1, 50, },
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,					_T(  "IP"  ),								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//  {	CONST_qyColumnDisplayType_pcNetworkPropType,	CONST_str_leiXing,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_platformId,			CONST_str_caoZuoXiTong,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_yongHuMing,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_iBool,				CONST_str_keZiDongBoHao,						SQL_CHAR,		LVCFMT_LEFT, 75,1, 50, },
	{	CONST_qyColumnDisplayType_iBool,				CONST_str_ziDongBoHaoShiKaolvTCPIP,			SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },		
	{	CONST_qyColumnDisplayType_iBool,				CONST_str_ziDongJianCeSheZhi,						SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_ziDongPeiZhiJiaoBen,					SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	{	CONST_qyColumnDisplayType_iBool,				CONST_str_qiYongDaiLi,							SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_daiLiSheZhi,							SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_buShiYongDaiLiDeDiZhi,					SQL_CHAR,		LVCFMT_LEFT, 110,1, 50, },
	//
	{	CONST_qyColumnDisplayType_time,					CONST_str_zuiXinShuaXinShiJian,						SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	//
	{	CONST_qyColumnDisplayType_str,					_T(  "MAC"  ),					SQL_CHAR,		LVCFMT_LEFT, 100,1,	50,	},
	{	-1,																	},
};



 QNM_QUERY_STRUCT  CONST_zjgaPcProxyCfgListQueryStruct  =
{
	 CONST_zjgaPcProxyCfgListSqlColumns,  CONST_zjgaPcProxyCfgListDisplayColumns,
};

 ////////////////////////////////////////
 //

#if  0
 //  终端的计算机信息设置属性, 2005/05/25
 QY_COLUMNINFO	CONST_zjgaPcComputerPropListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcAdapterTab.id"  ),						SQL_INTEGER,	},
	{	0,	_T(  "qyPcAdapterTab.iStatus"  ),					SQL_INTEGER,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),								SQL_CHAR,		},		//	5
	//  {	6,	_T(  "qyPcAdapterTab.uiType"  ),				SQL_INTEGER,	},
	{	7,	_T(  "qyPcAdapterTab.propStr0"  ),					SQL_CHAR,		},		//	pComputer->activeComputerName,  pRcd->propStrs[uiPropStrs],  sizeof(  pRcd->propStrs[uiPropStrs]  )  );  uiPropStrs  ++  ;
	{	7,	_T(  "qyPcAdapterTab.propStr1"  ),					SQL_CHAR,		},		//  pComputer->computerName,  pRcd->propStrs[uiPropStrs],  sizeof(  pRcd->propStrs[uiPropStrs]  )  );  uiPropStrs  ++  ;
	{	7,	_T(  "qyPcAdapterTab.propstr2"  ),					SQL_CHAR,		},
	{	6,	_T(  "qyPcAdapterTab.iParam0"  ),					SQL_INTEGER,	},		//  pComputer->iPlatformId;  uiKeyParams  ++  ;
	{	6,	_T(  "qyPcAdapterTab.iParam1"  ),					SQL_INTEGER,	},		//  pComputer->uiLangId;  uiKeyParams  ++  ;
	{	7,	_T(  "qyPcAdapterTab.paramStr0"  ),					SQL_CHAR,		},		//  pComputer->winDir,  pRcd->paramStrs[uiKeyParamStrs],  sizeof(  pRcd->paramStrs[uiKeyParamStrs]  )  );  uiKeyParamStrs  ++  ;
	//
	{	6,	_T(  "qyPcAdapterTab.lastTime"  ),					SQL_CHAR,		},
	{	9,	_T(  "qyPcAdapterTab.mac0"  ),						SQL_CHAR,		},		//	9
	{	-1,									},
};

 QY_COLUMNINFO	CONST_zjgaPcComputerPropListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	{	CONST_qyColumnDisplayType_pcAdapterStatus,		CONST_str_zhuangTai,								SQL_CHAR,		LVCFMT_LEFT, 80,1, 50, },
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,					_T(  "IP"  ),								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//  {	CONST_qyColumnDisplayType_pcNetworkPropType,	CONST_str_leiXing,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_dangQianJiSuanJiMing,						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_NetbiosJiSuanJiMing,					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_jiSuanJiMing,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_platformId,			CONST_str_caoZuoXiTong,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_langId,				CONST_str_yuYan,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_xiTongMuLu,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_time,					CONST_str_zuiXinShuaXinShiJian,						SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	{	CONST_qyColumnDisplayType_str,					_T(  "MAC"  ),					SQL_CHAR,		LVCFMT_LEFT, 100,1,	50,	},
	{	-1,																	},
};



 QNM_QUERY_STRUCT  CONST_zjgaPcComputerPropListQueryStruct  =
{
	 CONST_zjgaPcComputerPropListSqlColumns,  CONST_zjgaPcComputerPropListDisplayColumns,
};


  //  终端的计算机信息策略, 2005/05/25
 QY_COLUMNINFO	CONST_zjgaPcComputerRuleListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcAdapterTab.id"  ),						SQL_INTEGER,	},
	{	0,	_T(  "qyPcAdapterTab.iStatus"  ),					SQL_INTEGER,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),								SQL_CHAR,		},		//	5
	//  {	6,	_T(  "qyPcAdapterTab.uiType"  ),				SQL_INTEGER,	},
	{	7,	_T(  "qyPcAdapterTab.propStr1"  ),					SQL_CHAR,		},		//  pComputer->computerName,  pRcd->propStrs[uiPropStrs],  sizeof(  pRcd->propStrs[uiPropStrs]  )  );  uiPropStrs  ++  ;
	{	7,	_T(  "qyPcAdapterTab.propStr2"  ),					SQL_CHAR,		},		//  pComputer->computerName,  pRcd->propStrs[uiPropStrs],  sizeof(  pRcd->propStrs[uiPropStrs]  )  );  uiPropStrs  ++  ;
	{	7,	_T(  "qyPcAdapterTab.iProp0"  ),					SQL_INTEGER,	},
	{	6,	_T(  "qyPcAdapterTab.iParam0"  ),					SQL_INTEGER,	},		//  pComputer->iPlatformId;  uiKeyParams  ++  ;
	{	6,	_T(  "qyPcAdapterTab.iParam1"  ),					SQL_INTEGER,	},		//  pComputer->uiLangId;  uiKeyParams  ++  ;
	{	7,	_T(  "qyPcAdapterTab.paramStr0"  ),					SQL_CHAR,		},		//  pComputer->winDir,  pRcd->paramStrs[uiKeyParamStrs],  sizeof(  pRcd->paramStrs[uiKeyParamStrs]  )  );  uiKeyParamStrs  ++  ;
	//  {	7,	_T(  "qyPcAdapterTab.propStr0"  ),					SQL_CHAR,		},		//	pComputer->activeComputerName,  pRcd->propStrs[uiPropStrs],  sizeof(  pRcd->propStrs[uiPropStrs]  )  );  uiPropStrs  ++  ;
	//
	{	6,	_T(  "qyPcAdapterTab.lastTime"  ),					SQL_CHAR,		},
	{	9,	_T(  "qyPcAdapterTab.mac0"  ),						SQL_CHAR,		},		//	9
	{	-1,									},
};

 QY_COLUMNINFO	CONST_zjgaPcComputerRuleListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	{	CONST_qyColumnDisplayType_pcAdapterStatus,		CONST_str_zhuangTai,								SQL_CHAR,		LVCFMT_LEFT, 80,1, 50, },
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,					_T(  "IP"  ),								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//  {	CONST_qyColumnDisplayType_pcNetworkPropType,	CONST_str_leiXing,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_NetbiosJiSuanJiMing,						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_jiSuanJiMing,						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_iBool,				CONST_str_shiFoChongQi,					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_platformId,			CONST_str_caoZuoXiTong,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_langId,				CONST_str_yuYan,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_xiTongMuLu,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//  {	CONST_qyColumnDisplayType_str,					_T(  "当前计算机名"  ),						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_time,					CONST_str_zuiXinShuaXinShiJian,						SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	{	CONST_qyColumnDisplayType_str,					_T(  "MAC"  ),					SQL_CHAR,		LVCFMT_LEFT, 100,1,	50,	},
	{	-1,																	},
};



 QNM_QUERY_STRUCT  CONST_zjgaPcComputerRuleListQueryStruct  =
{
	 CONST_zjgaPcComputerRuleListSqlColumns,  CONST_zjgaPcComputerRuleListDisplayColumns,
};

#endif

 //  {

 //  终端的计算机信息策略, 2005/05/25
 QY_COLUMNINFO	CONST_zjgaPcWindowsUpdatePolicyListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcAdapterTab.id"  ),						SQL_INTEGER,	},
	{	0,	_T(  "qyPcAdapterTab.iStatus"  ),					SQL_INTEGER,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),								SQL_CHAR,		},		//	5
	//
	{	5,	_T(  "qyPcAdapterTab.iProp12"  ),					SQL_INTEGER,	},		//  pPolicy->AutoUpdate_AUOptions;				uiProps  ++  ;		//  10
	{	5,	_T(  "qyPcAdapterTab.iProp13"  ),					SQL_INTEGER,	},		//  pPolicy->AutoUpdate_ScheduledInstallDay;	uiProps  ++  ;		//  11
	{	5,	_T(  "qyPcAdapterTab.iProp14"  ),					SQL_INTEGER,	},		//  pPolicy->AutoUpdate_ScheduledInstallTime;	uiProps  ++  ;		//  12
	//
	{	5,	_T(  "qyPcAdapterTab.propStr3"  ),					SQL_CHAR,		},		//
	//
	{	5,	_T(  "qyPcAdapterTab.iProp3"  ),					SQL_INTEGER,	},		//  pPolicy->NoAutoUpdate;						uiProps  ++  ;		//  3
	{	5,	_T(  "qyPcAdapterTab.iProp4"  ),					SQL_INTEGER,	},		//  pPolicy->AUOptions;						uiProps  ++  ;			//  4
	{	5,	_T(  "qyPcAdapterTab.iProp5"  ),					SQL_INTEGER,	},		//  pPolicy->ScheduledInstallDay;				uiProps  ++  ;		//  5
	{	5,	_T(  "qyPcAdapterTab.iProp6"  ),					SQL_INTEGER,	},		//  pPolicy->ScheduledInstallTime;				uiProps  ++  ;		//  6
	{	5,	_T(  "qyPcAdapterTab.iProp9"  ),					SQL_INTEGER,	},		//  pPolicy->UseWUServer;						uiProps  ++  ;		//  7
	{	5,	_T(  "qyPcAdapterTab.propStr0"  ),					SQL_CHAR,		},		//  pPolicy->WUServer,  pRcd->propStrs[uiPropStrs],  sizeof(  pRcd->propStrs[uiPropStrs]  )  );		uiPropStrs  ++  ;						//  0
	{	5,	_T(  "qyPcAdapterTab.propStr1"  ),					SQL_CHAR,		},		//  pPolicy->WUStatusServer,  pRcd->propStrs[uiPropStrs],  sizeof(  pRcd->propStrs[uiPropStrs]  )  );  uiPropStrs  ++  ;						//  1
	{	5,	_T(  "qyPcAdapterTab.iProp1"  ),					SQL_INTEGER,	},		//  pPolicy->RescheduleWaitTimeEnabled;		uiProps  ++  ;		//  1
	{	5,	_T(  "qyPcAdapterTab.iProp0"  ),					SQL_INTEGER,	},		//  pPolicy->RescheduleWaitTime;				uiProps  ++  ;		//  0
	{	5,	_T(  "qyPcAdapterTab.iProp7"  ),					SQL_INTEGER,	},		//  pPolicy->DetectionFrequencyEnabled
	{	5,	_T(  "qyPcAdapterTab.iProp8"  ),					SQL_INTEGER,	},		//  pPolicy->DetectionFrequency
	{	5,	_T(  "qyPcAdapterTab.iProp2"  ),					SQL_INTEGER,	},		//  pPolicy->NoAutoRebootWithLoggedOnUsers;	uiProps  ++  ;		//  2
	{	5,	_T(  "qyPcAdapterTab.iProp10"  ),					SQL_INTEGER,	},		//  pPolicy->ElevateNonAdmins;					uiProps  ++  ;		//  8
	{	5,	_T(  "qyPcAdapterTab.iProp11"  ),					SQL_INTEGER,	},		//  pPolicy->TargetGroupEnabled;				uiProps  ++  ;		//  9
	{	5,	_T(  "qyPcAdapterTab.propStr2"  ),					SQL_CHAR,	},			//  pPolicy->TargetGroup,  pRcd->propStrs[uiPropStrs],  sizeof(  pRcd->propStrs[uiPropStrs]  )  );		uiPropStrs  ++  ;						//  2
	//
	{	6,	_T(  "qyPcAdapterTab.lastTime"  ),					SQL_CHAR,		},
	{	9,	_T(  "qyPcAdapterTab.mac0"  ),						SQL_CHAR,		},		//	9
	{	-1,									},
};

 QY_COLUMNINFO	CONST_zjgaPcWindowsUpdatePolicyListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	{	CONST_qyColumnDisplayType_pcAdapterStatus,		CONST_str_zhuangTai,							SQL_CHAR,		LVCFMT_LEFT, 80,1, 50, },
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,					_T(  "IP"  ),									SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_dwRegVal,				_T(  "AutoUpdate\\AUOptions"  ),				SQL_INTEGER,	LVCFMT_LEFT, 135,1, 50, },
	{	CONST_qyColumnDisplayType_dwRegVal,				_T(  "AutoUpdate\\ScheduledInstallDay"  ),		SQL_INTEGER,	LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_dwRegVal,				_T(  "AutoUpdate\\ScheduledInstallTime"  ),		SQL_INTEGER,	LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_bool,					CONST_str_shiFouShiYongWSus,					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_dwRegVal,				_T(  "NoAutoUpdate"  ),							SQL_INTEGER,	LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_dwRegVal,				_T(  "AUOptions"  ),							SQL_INTEGER,	LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_dwRegVal,				_T(  "ScheduledInstallDay"  ),					SQL_INTEGER,	LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_dwRegVal,				_T(  "ScheduledInstallTime"  ),					SQL_INTEGER,	LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_dwRegVal,				_T(  "UseWUServer"  ),							SQL_INTEGER,	LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					_T(  "WUServer"  ),								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					_T(  "WUStatusServer"  ),						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_dwRegVal,				_T(  "RescheduleWaitTimeEnabled"  ),			SQL_INTEGER,	LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_dwRegVal,				_T(  "RescheduleWaitTime"  ),					SQL_INTEGER,	LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_dwRegVal,				_T(  "DetectionFrequencyEnabled"  ),					SQL_INTEGER,	LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_dwRegVal,				_T(  "DetectionFrequency"  ),					SQL_INTEGER,	LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_dwRegVal,				_T(  "NoAutoRebootWithLoggedOnUsers"  ),		SQL_INTEGER,	LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_dwRegVal,				_T(  "ElevateNonAdmins"  ),						SQL_INTEGER,	LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_dwRegVal,				_T(  "TargetGroupEnabled"  ),					SQL_INTEGER,	LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					_T(  "TargetGroup"  ),							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_time,					CONST_str_zuiXinShuaXinShiJian,					SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	{	CONST_qyColumnDisplayType_str,					_T(  "MAC"  ),									SQL_CHAR,		LVCFMT_LEFT, 100,1,	50,	},
	{	-1,																	},
};


 QNM_QUERY_STRUCT  CONST_zjgaPcWindowsUpdatePolicyListQueryStruct  =
{
	 CONST_zjgaPcWindowsUpdatePolicyListSqlColumns,		CONST_zjgaPcWindowsUpdatePolicyListDisplayColumns,
 };

 //  }

 //  终端的打印机信息, 2005/05/25
 QY_COLUMNINFO	CONST_zjgaPcPrinterPropListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcPrinterTab.id"  ),						SQL_INTEGER,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),								SQL_CHAR,		},		//	5
	{	7,	_T(  "qyPcPrinterTab.name"  ),						SQL_CHAR,		},		//  pComputer->computerName,  pRcd->propStrs[uiPropStrs],  sizeof(  pRcd->propStrs[uiPropStrs]  )  );  uiPropStrs  ++  ;
	//
	{	7,	_T(  "qyPcPrinterTab.iPlatformId"  ),				SQL_INTEGER,	},
	{	7,	_T(  "qyPcPrinterTab.uiLangId"  ),					SQL_INTEGER,	},
	{	7,	_T(  "qyPcPrinterTab.winDir"  ),					SQL_CHAR,		},
	{	6,	_T(  "qyPcPrinterTab.lastTime"  ),					SQL_CHAR,		},
	{	9,	_T(  "qyPcPrinterTab.mac0"  ),						SQL_CHAR,		},		//	9
	{	-1,																},
};

 QY_COLUMNINFO	CONST_zjgaPcPrinterPropListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,					_T(  "IP"  ),								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_mingChen,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//  
	{	CONST_qyColumnDisplayType_platformId,			CONST_str_caoZuoXiTong,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_langId,				CONST_str_yuYan,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_xiTongMuLu,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_time,					CONST_str_zuiXinShuaXinShiJian,						SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	{	CONST_qyColumnDisplayType_str,					_T(  "MAC"  ),					SQL_CHAR,		LVCFMT_LEFT, 100,1,	50,	},
	{	-1,																	},
};



 QNM_QUERY_STRUCT  CONST_zjgaPcPrinterPropListQueryStruct  =
{
	 CONST_zjgaPcPrinterPropListSqlColumns,  CONST_zjgaPcPrinterPropListDisplayColumns,
};

 //
 ////////////////////////////////////


 //  pcRegistryList

 //  终端的计算机信息策略, 2005/05/25
 QY_COLUMNINFO	CONST_zjgaPcRegistryListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcRegistryValTab.id"  ),						SQL_INTEGER,	},
	{	0,	_T(  "qyPcRegistryValTab.iRuleId"  ),					SQL_INTEGER,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),									SQL_CHAR,		},		//	5
	//
	{	5,	_T(  "qyPcRegistryRuleTab.iRootKey"  ),					SQL_INTEGER,	},
	{	5,	_T(  "qyPcRegistryValTab.szSidKey"  ),					SQL_CHAR,	},
	{	5,	_T(  "qyPcRegistryValTab.usrName"  ),					SQL_CHAR,	},
	{	5,	_T(  "qyPcRegistryRuleTab.subKey"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryValTab.cfgName"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryValTab.ucbKey"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryValTab.iValType"  ),					SQL_INTEGER,	},
	{	5,	_T(  "qyPcRegistryValTab.cfgVal"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryValTab.uiValLenInBytes"  ),			SQL_INTEGER,	},	
	{	5,	_T(  "qyPcRegistryValTab.ucbERROR_MORE_DATA"  ),		SQL_CHAR,		},
	//
	{	5,	_T(  "qyPcRegistryKnowledgeTab.name"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.suggestedVal"  ),			SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.ucbVirus"  ),				SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.ucbBackDoor"  ),			SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.ucbSys"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.ucbSpy"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.ucbAdvertisement"  ),		SQL_CHAR,		},
	//
	{	6,	_T(  "qyPcRegistryValTab.lastTime"  ),					SQL_CHAR,		},
	//
	{	7,	_T(  "qyPcRegistryValTab.iPlatformId"  ),				SQL_INTEGER,	},
	{	7,	_T(  "qyPcRegistryValTab.uiLangId"  ),					SQL_INTEGER,	},
	{	7,	_T(  "qyPcRegistryValTab.winDir"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryValTab.mac0"  ),						SQL_CHAR,		},
	{	-1,																},
};

 QY_COLUMNINFO	CONST_zjgaPcRegistryListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	{	CONST_qyColumnDisplayType_long,					_T(  "iRuleId"  ),								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,					_T(  "IP"  ),									SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_iRootKey,				CONST_str_genJian,								SQL_CHAR,		LVCFMT_LEFT, 45,1, 50, },
	{	CONST_qyColumnDisplayType_str,					_T(  "Sid"  ),									SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_zhangHuMing,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_ziJian,								SQL_CHAR,		LVCFMT_LEFT, 350,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_mingChen,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbKey,								SQL_CHAR,		LVCFMT_LEFT, 50,1, 50, },
	{	CONST_qyColumnDisplayType_regType,				CONST_str_leiXing,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_shuZhi,								SQL_CHAR,		LVCFMT_LEFT, 300,1, 50, },
	{	CONST_qyColumnDisplayType_long,					CONST_str_zhiZiJieShu,							SQL_CHAR,		LVCFMT_RIGHT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbERROR_MORE_DATA,					SQL_CHAR,		LVCFMT_LEFT, 110,1, 50, },
	//
	{	CONST_qyColumnDisplayType_str,					CONST_str_bieMing,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_jianYiZhi,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbVirus,								SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbBackDoor,							SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbSys,								SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbSpy,								SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbAdvertisement,						SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	//
	{	CONST_qyColumnDisplayType_time,					CONST_str_zuiXinShuaXinShiJian,					SQL_CHAR,		LVCFMT_LEFT, 126,1, 50, },
	//
	{	CONST_qyColumnDisplayType_platformId,			CONST_str_caoZuoXiTong,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_langId,				CONST_str_yuYan,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_xiTongMuLu,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					_T(  "MAC"  ),								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	-1,					},
};



 QNM_QUERY_STRUCT  CONST_zjgaPcRegistryListQueryStruct  =  
{
	 CONST_zjgaPcRegistryListSqlColumns,  CONST_zjgaPcRegistryListDisplayColumns,
};

//////////////////////////////


 //  终端的计算机信息策略, 2005/05/25
 QY_COLUMNINFO	CONST_zjgaPcRegistryRuleStatusListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcRegistryValTab.id"  ),						SQL_INTEGER,	},
	{	0,	_T(  "qyPcRegistryValTab.iRuleId"  ),					SQL_INTEGER,	},
	{	0,	_T(  "qyPcRegistryValTab.iStatus"  ),					SQL_INTEGER,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),									SQL_CHAR,		},		//	5
	//
	{	5,	_T(  "qyPcRegistryRuleTab.iRootKey"  ),					SQL_INTEGER,	},
	{	5,	_T(  "qyPcRegistryValTab.szSidKey"  ),					SQL_CHAR,	},
	{	5,	_T(  "qyPcRegistryValTab.usrName"  ),					SQL_CHAR,	},
	{	5,	_T(  "qyPcRegistryRuleTab.subKey"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryValTab.cfgName"  ),					SQL_CHAR,		},
	//
	{	6,	_T(  "qyPcRegistryValTab.lastTime"  ),					SQL_CHAR,		},
	//
	{	7,	_T(  "qyPcRegistryValTab.iPlatformId"  ),				SQL_INTEGER,	},
	{	7,	_T(  "qyPcRegistryValTab.uiLangId"  ),					SQL_INTEGER,	},
	{	7,	_T(  "qyPcRegistryValTab.winDir"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryValTab.mac0"  ),						SQL_CHAR,		},
	{	-1,																},
};

 QY_COLUMNINFO	CONST_zjgaPcRegistryRuleStatusListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	{	CONST_qyColumnDisplayType_long,					_T(  "iRuleId"  ),								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	{	CONST_qyColumnDisplayType_qyStatus,				CONST_str_zhuangTai,							SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,					_T(  "IP"  ),									SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_iRootKey,				CONST_str_genJian,								SQL_CHAR,		LVCFMT_LEFT, 45,1, 50, },
	{	CONST_qyColumnDisplayType_str,					_T(  "Sid"  ),									SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_zhangHuMing,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_ziJian,								SQL_CHAR,		LVCFMT_LEFT, 350,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_mingChen,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_time,					CONST_str_zuiXinShuaXinShiJian,					SQL_CHAR,		LVCFMT_LEFT, 126,1, 50, },
	//
	{	CONST_qyColumnDisplayType_platformId,			CONST_str_caoZuoXiTong,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_langId,				CONST_str_yuYan,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_xiTongMuLu,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					_T(  "MAC"  ),								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	-1,					},
};



 QNM_QUERY_STRUCT  CONST_zjgaPcRegistryRuleStatusListQueryStruct  =  
{
	 CONST_zjgaPcRegistryRuleStatusListSqlColumns,  CONST_zjgaPcRegistryRuleStatusListDisplayColumns,
};


//////////////////////


 //  终端的计算机信息策略, 2005/05/25
 QY_COLUMNINFO	CONST_zjgaPcEventLogListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcEventLogTab.id"  ),						SQL_INTEGER,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),								SQL_CHAR,		},		//	5
	{	5,	_T(  "qyPcEventLogTab.wEventType"  ),				SQL_INTEGER,	},
	{	5,	_T(  "qyPcEventLogTab.timeGeneratedBuf"  ),			SQL_CHAR,		},
	{	5,	_T(  "qyPcEventLogTab.sourceName"  ),				SQL_CHAR,		},
	//  {	5,	_T(  "qyPcEventLogTab.wEventCategory"  ),			SQL_INTEGER,	},
	{	5,	_T(  "qyPcEventLogTab.dwEventId"  ),				SQL_INTEGER,	},
	{	5,	_T(  "qyPcEventLogTab.accountName"  ),				SQL_CHAR,		},
	{	5,	_T(  "qyPcEventLogTab.computerName"  ),				SQL_CHAR,		},
	{	5,	_T(  "qyPcEventLogTab.eventLogDesc"  ),				SQL_CHAR,		},
	//
	{	7,	_T(  "qyPcEventLogTab.iPlatformId"  ),				SQL_INTEGER,	},
	{	7,	_T(  "qyPcEventLogTab.uiLangId"  ),					SQL_INTEGER,	},
	{	7,	_T(  "qyPcEventLogTab.winDir"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcEventLogTab.mac0"  ),						SQL_CHAR,		},
	{	-1,																},
};

 QY_COLUMNINFO	CONST_zjgaPcEventLogListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,					_T(  "IP"  ),								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_pcEventLogType,		CONST_str_leiXing,								SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_time,					CONST_str_shiJian,								SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_laiYuan,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//  {	CONST_qyColumnDisplayType_long,				_T(  "分类"  ),								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_pcEventId,			CONST_str_shiJianID,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_yongHuMing,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_jiSuanJiMing,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_miaoShu,								SQL_CHAR,		LVCFMT_LEFT, 360,1, 50, },
	//
	{	CONST_qyColumnDisplayType_platformId,			CONST_str_caoZuoXiTong,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_langId,				CONST_str_yuYan,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_xiTongMuLu,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					_T(  "MAC"  ),								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	-1,					},
};



 QNM_QUERY_STRUCT  CONST_zjgaPcEventLogListQueryStruct  =  
{
	 CONST_zjgaPcEventLogListSqlColumns,  CONST_zjgaPcEventLogListDisplayColumns,
};



  QY_COLUMNINFO	CONST_zjgaPcOsUsrListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcOsUsrTab.id"  ),						SQL_INTEGER,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),							SQL_CHAR,		},		//	5
	{	5,	_T(  "qyPcOsUsrTab.usrName"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcOsUsrTab.ucbDisabled"  ),				SQL_CHAR,		},
	//
	{	7,	_T(  "qyPcOsUsrTab.iPlatformId"  ),				SQL_INTEGER,	},
	{	7,	_T(  "qyPcOsUsrTab.uiLangId"  ),				SQL_INTEGER,	},
	{	7,	_T(  "qyPcOsUsrTab.winDir"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcOsUsrTab.mac0"  ),					SQL_CHAR,		},
	{	-1,															},
};

 QY_COLUMNINFO	CONST_zjgaPcOsUsrListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,					_T(  "IP"  ),								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_zhangHuMing,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_shiFoJinYong,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_platformId,			CONST_str_caoZuoXiTong,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_langId,				CONST_str_yuYan,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_xiTongMuLu,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					_T(  "MAC"  ),								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	-1,					},
};



 QNM_QUERY_STRUCT  CONST_zjgaPcOsUsrListQueryStruct  =  
{
	 CONST_zjgaPcOsUsrListSqlColumns,  CONST_zjgaPcOsUsrListDisplayColumns,
};



 QY_COLUMNINFO	CONST_zjgaPcNetStatListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcNetStatTab.id"  ),						SQL_INTEGER,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),								SQL_CHAR,		},		//	5
	{	5,	_T(  "qyPcNetStatTab.uiType"  ),					SQL_INTEGER,	},
	{	5,	_T(  "qyPcNetStatTab.localIp"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcNetStatTab.dwLocalPort"  ),				SQL_INTEGER,	},
	{	5,	_T(  "qyPcNetStatTab.remoteIp"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcNetStatTab.dwRemotePort"  ),				SQL_INTEGER,	},
	{	5,	_T(  "qyPcNetStatTab.dwState"  ),					SQL_INTEGER,	},
	{	5,	_T(  "qyPcNetStatTab.lastTime"  ),					SQL_CHAR,		},
	//
	//  {	7,	_T(  "qyPcNetStatTab.iPlatformId"  ),				SQL_INTEGER,	},
	//  {	7,	_T(  "qyPcNetStatTab.uiLangId"  ),					SQL_INTEGER,	},
	//  {	7,	_T(  "qyPcNetStatTab.winDir"  ),					SQL_CHAR,		},
	//
	{	5,	_T(  "qyPcNetStatTab.mac0"  ),						SQL_CHAR,		},
	{	-1,															},
};

 QY_COLUMNINFO	CONST_zjgaPcNetStatListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,					_T(  "IP"  ),								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_pcCommType,			CONST_str_leiXing,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_ip12,					CONST_str_benDiIP,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_long,					CONST_str_benDiDuanKou,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_ip12,					CONST_str_yuanDuanIP,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_long,					CONST_str_yuanDuanDuanKou,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_tcpState,				CONST_str_zhuangTai,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_time,					CONST_str_zuiXinShuaXinShiJian,							SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	//
	//  {	CONST_qyColumnDisplayType_platformId,			_T(  "操作系统"  ),							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//  {	CONST_qyColumnDisplayType_langId,				_T(  "语言"  ),								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//  {	CONST_qyColumnDisplayType_str,					_T(  "winDir"  ),							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_str,					_T(  "MAC"  ),								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	-1,					},
};



 QNM_QUERY_STRUCT  CONST_zjgaPcNetStatListQueryStruct  =  
{
	 CONST_zjgaPcNetStatListSqlColumns,  CONST_zjgaPcNetStatListDisplayColumns,
};


 QY_COLUMNINFO	CONST_zjgaPcProcessPropListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcProcessTab.id"  ),							SQL_INTEGER,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),									SQL_CHAR,		},		//	5
	{	5,	_T(  "qyPcProcessTab.dwPid"  ),							SQL_INTEGER,	},
	{	5,	_T(  "qyPcProcessTab.moduleName"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessTab.modulePath"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessTab.cmdLine"  ),						SQL_CHAR,		},
	//
	{	5,	_T(  "qyPcProcessKnowledgeTab.name"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbVirus"  ),				SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbBackDoor"  ),			SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbSys"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbSpy"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbAdvertisement"  ),		SQL_CHAR,		},
	//
	{	7,	_T(  "qyPcProcessTab.iPlatformId"  ),					SQL_INTEGER,	},
	{	7,	_T(  "qyPcProcessTab.uiLangId"  ),						SQL_INTEGER,	},
	{	7,	_T(  "qyPcProcessTab.winDir"  ),						SQL_CHAR,		},
	//
	{	6,	_T(  "qyPcProcessTab.lastTime"  ),						SQL_CHAR,		},
	//
	{	5,	_T(  "qyPcProcessTab.mac0"  ),							SQL_CHAR,		},
	{	-1,															},
};

 QY_COLUMNINFO	CONST_zjgaPcProcessPropListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,					_T(  "IP"  ),									SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_uLong,				_T(  "PID"  ),									SQL_CHAR,		LVCFMT_LEFT, 45,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_jinChengMingChen,						SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_luJing,								SQL_CHAR,		LVCFMT_LEFT, 300,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_cmdLine,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	//
	{	CONST_qyColumnDisplayType_str,					CONST_str_bieMing,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbVirus,								SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbBackDoor,							SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbSys,								SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbSpy,								SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbAdvertisement,						SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	//
	{	CONST_qyColumnDisplayType_platformId,			CONST_str_caoZuoXiTong,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_langId,				CONST_str_yuYan,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_xiTongMuLu,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_time,					CONST_str_zuiXinShuaXinShiJian,							SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	//
	{	CONST_qyColumnDisplayType_str,					_T(  "MAC"  ),								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	-1,					},
};



 QNM_QUERY_STRUCT  CONST_zjgaPcProcessPropListQueryStruct  =
{
	 CONST_zjgaPcProcessPropListSqlColumns,  CONST_zjgaPcProcessPropListDisplayColumns,
};


 //////////////////



  QY_COLUMNINFO	CONST_zjgaPcProcessModulePropListSqlColumns[]  =  
{
	{	0,	_T(  "B.id"  ),								SQL_INTEGER,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),						SQL_CHAR,		},		//	5
	{	5,	_T(  "A.dwPid"  ),							SQL_INTEGER,	},
	{	5,	_T(  "A.moduleName"  ),						SQL_CHAR,		},
	{	5,	_T(  "A.cmdLine"  ),						SQL_CHAR,		},
	{	5,	_T(  "B.moduleName"  ),						SQL_CHAR,		},
	{	5,	_T(  "B.modulePath"  ),						SQL_CHAR,		},
	//
	{	5,	_T(  "qyPcProcessKnowledgeTab.name"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbVirus"  ),				SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbBackDoor"  ),			SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbSys"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbSpy"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbAdvertisement"  ),		SQL_CHAR,		},
	//
	{	7,	_T(  "A.iPlatformId"  ),					SQL_INTEGER,	},
	{	7,	_T(  "A.uiLangId"  ),						SQL_INTEGER,	},
	{	7,	_T(  "A.winDir"  ),							SQL_CHAR,		},
	//
	{	6,	_T(  "B.lastTime"  ),						SQL_CHAR,		},
	//
	{	5,	_T(  "A.mac0"  ),							SQL_CHAR,		},
	{	-1,															},
};

 QY_COLUMNINFO	CONST_zjgaPcProcessModulePropListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,					_T(  "IP"  ),									SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_uLong,				_T(  "PID"  ),									SQL_CHAR,		LVCFMT_LEFT, 45,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_jinChengMingChen,						SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_cmdLine,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_moKuaiMingChen,						SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_luJing,								SQL_CHAR,		LVCFMT_LEFT, 300,1, 50, },
	//
	{	CONST_qyColumnDisplayType_str,					CONST_str_bieMing,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbVirus,								SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbBackDoor,							SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbSys,								SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbSpy,								SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbAdvertisement,						SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	//
	{	CONST_qyColumnDisplayType_platformId,			CONST_str_caoZuoXiTong,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_langId,				CONST_str_yuYan,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_xiTongMuLu,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_time,					CONST_str_zuiXinShuaXinShiJian,							SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	//
	{	CONST_qyColumnDisplayType_str,					_T(  "MAC"  ),								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	-1,					},
};



 QNM_QUERY_STRUCT  CONST_zjgaPcProcessModulePropListQueryStruct  =
{
	 CONST_zjgaPcProcessModulePropListSqlColumns,  CONST_zjgaPcProcessModulePropListDisplayColumns,
};















 /////////////////


  QY_COLUMNINFO	CONST_zjgaPcProcessRuleListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcProcessRuleTab.id"  ),					SQL_INTEGER,	},
	{	5,	_T(  "qyPcProcessRuleTab.uiType"  ),				SQL_INTEGER,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),								SQL_CHAR,		},		//	5
	{	5,	_T(  "qyPcProcessRuleTab.moduleName"  ),			SQL_CHAR,		},
	//
	{	5,	_T(  "qyPcProcessRuleTab.mac0"  ),					SQL_CHAR,		},
	{	-1,															},
};

 QY_COLUMNINFO	CONST_zjgaPcProcessRuleListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	//  {	CONST_qyColumnDisplayType_pcProcessRuleType,	CONST_str_ceLue,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_ruleCmd,				CONST_str_ceLue,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,					_T(  "IP"  ),									SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_jinChengMingChen,						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_mac,					_T(  "MAC"  ),									SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	-1,															},
};

 QNM_QUERY_STRUCT  CONST_zjgaPcProcessRuleListQueryStruct  =
{
	 CONST_zjgaPcProcessRuleListSqlColumns,  CONST_zjgaPcProcessRuleListDisplayColumns,
};


 //
 //////////////////////////////////////////////



  QY_COLUMNINFO	CONST_zjgaPcProcessKnowledgeListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcProcessKnowledgeTab.id"  ),						SQL_INTEGER,	},
	{	0,	_T(  "qyPcProcessKnowledgeTab.uiType"  ),					SQL_INTEGER,	},
	{	5,	_T(  "qyPcProcessKnowledgeTab.auditTime"  ),				SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.fileName"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.cmdLine"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.name"  ),						SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbVirus"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbBackDoor"  ),				SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbSpy"  ),						SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbAdvertisement"  ),			SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.des0"  ),						SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.company"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.product"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbSys"  ),						SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbDaemon"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbUseNet"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.ucbHardware"  ),				SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.commonErr"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.memInfo"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.securityLevel"  ),				SQL_INTEGER,	},
	{	5,	_T(  "qyPcProcessKnowledgeTab.provider"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.providerAddr"  ),				SQL_CHAR,		},
	{	5,	_T(  "qyPcProcessKnowledgeTab.providerTime"  ),				SQL_CHAR,		},
	//  {	5,	_T(  "qyPcProcessKnowledgeTab.lastTime"  ),					SQL_CHAR,		},
	{	-1,															},
};

 QY_COLUMNINFO	CONST_zjgaPcProcessKnowledgeListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	{	CONST_qyColumnDisplayType_pcCommType,			CONST_str_leiXing,								SQL_CHAR,		LVCFMT_LEFT, 80,1, 50, },
	{	CONST_qyColumnDisplayType_time,					CONST_str_shenHeShiJian,						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_moKuaiMingChen,						SQL_CHAR,		LVCFMT_LEFT, 250,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_cmdLine,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_bieMing,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbVirus,								SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbBackDoor,							SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbSpy,								SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbAdvertisement,						SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_miaoShu,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_suoShuQiYe,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_suoShuChanPin,						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbSys,								SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbDaemon,							SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbUseNet,							SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbHardware,							SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_commonErr,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_memInfo,								SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_long,					CONST_str_securityLevel,						SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_providerName,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str__providerAddr,						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_providerTime,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//  {	CONST_qyColumnDisplayType_time,					CONST_str_zuiXinShuaXinShiJian,					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	-1,															},
};

 QNM_QUERY_STRUCT  CONST_zjgaPcProcessKnowledgeListQueryStruct  =
{
	 CONST_zjgaPcProcessKnowledgeListSqlColumns,  CONST_zjgaPcProcessKnowledgeListDisplayColumns,
};

//


 QY_COLUMNINFO	CONST_zjgaPcRegistryKnowledgeListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcRegistryKnowledgeTab.id"  ),						SQL_INTEGER,	},
	{	0,	_T(  "qyPcRegistryKnowledgeTab.uiType"  ),					SQL_INTEGER,	},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.auditTime"  ),				SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.iRootKey"  ),					SQL_INTEGER,	},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.subKey"  ),						SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.cfgName"  ),						SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.name"  ),						SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.suggestedVal"  ),				SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.ucbVirus"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.ucbBackDoor"  ),				SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.ucbSpy"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.ucbAdvertisement"  ),			SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.des0"  ),						SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.company"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.product"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.ucbSys"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.ucbDaemon"  ),				SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.ucbUseNet"  ),				SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.ucbHardware"  ),				SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.commonErr"  ),				SQL_CHAR,		},
	//  {	5,	_T(  "qyPcRegistryKnowledgeTab.memInfo"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.securityLevel"  ),			SQL_INTEGER,	},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.provider"  ),					SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.providerAddr"  ),				SQL_CHAR,		},
	{	5,	_T(  "qyPcRegistryKnowledgeTab.providerTime"  ),				SQL_CHAR,		},
	//  {	5,	_T(  "qyPcProcessKnowledgeTab.lastTime"  ),					SQL_CHAR,		},
	{	-1,															},
};

 QY_COLUMNINFO	CONST_zjgaPcRegistryKnowledgeListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	{	CONST_qyColumnDisplayType_pcCommType,			CONST_str_leiXing,								SQL_CHAR,		LVCFMT_LEFT, 80,1, 50, },
	{	CONST_qyColumnDisplayType_time,					CONST_str_shenHeShiJian,						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_iRootKey,				CONST_str_genJian,								SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_ziJian,								SQL_CHAR,		LVCFMT_LEFT, 300,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_mingChen,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_bieMing,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_jianYiZhi,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbVirus,								SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbBackDoor,							SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbSpy,								SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbAdvertisement,						SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_miaoShu,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_suoShuQiYe,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_suoShuChanPin,						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbSys,								SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbDaemon,							SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbUseNet,							SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_bool,					CONST_str_ucbHardware,							SQL_CHAR,		LVCFMT_LEFT, 85,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_commonErr,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//  {	CONST_qyColumnDisplayType_str,					CONST_str_memInfo,								SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_long,					CONST_str_securityLevel,						SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_providerName,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str__providerAddr,						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_providerTime,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//  {	CONST_qyColumnDisplayType_time,					CONST_str_zuiXinShuaXinShiJian,					SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	-1,															},
};

 QNM_QUERY_STRUCT  CONST_zjgaPcRegistryKnowledgeListQueryStruct  =
{
	 CONST_zjgaPcRegistryKnowledgeListSqlColumns,  CONST_zjgaPcRegistryKnowledgeListDisplayColumns,
};


 //


 QY_COLUMNINFO	CONST_zjgaPcNetFlowListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcNetFlowTab.id"  ),						SQL_INTEGER,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),								SQL_CHAR,		},		//	5
	{	0,	_T(  "qyPcNetFlowTab.dwType"  ),					SQL_INTEGER,	},
	{	0,	_T(  "qyPcNetFlowTab.bPhysAddr"  ),					SQL_CHAR,	},
	{	6,	_T(  "qyPcAdapterTab.devDesc"  ),					SQL_CHAR,		},
	//
	{	0,	_T(  "qyPcNetFlowTab.dwSpeed"  ),					SQL_INTEGER,	},
	{	0,	_T(  "qyPcNetFlowTab.dwInSpeed"  ),					SQL_INTEGER,	},
	{	0,	_T(  "qyPcNetFlowTab.dwOutSpeed"  ),				SQL_INTEGER,	},
	{	0,	_T(  "qyPcNetFlowTab.dwInOctets"  ),				SQL_INTEGER,	},
	{	0,	_T(  "qyPcNetFlowTab.dwOutOctets"  ),				SQL_INTEGER,	},
	//
	{	7,	_T(  "qyPcNetFlowTab.iPlatformId"  ),					SQL_INTEGER,	},
	{	7,	_T(  "qyPcNetFlowTab.uiLangId"  ),						SQL_INTEGER,	},
	{	7,	_T(  "qyPcNetFlowTab.winDir"  ),							SQL_CHAR,		},
	//
	{	6,	_T(  "qyPcNetFlowTab.lastTime"  ),						SQL_CHAR,		},
	//
	{	5,	_T(  "qyPcNetFlowTab.mac0"  ),							SQL_CHAR,		},
	{	-1,	},
};

 QY_COLUMNINFO	CONST_zjgaPcNetFlowListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,					_T(  "IP"  ),									SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_adapterType,			CONST_str_wangKaLeiXing,						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_wangKaMAC,							SQL_CHAR,		LVCFMT_LEFT, 90,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_mingChen,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_uLong,				CONST_str_daiKuan_kbps,							SQL_CHAR,		LVCFMT_RIGHT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_uLong,				CONST_str_ruLiuLiang_kbps,						SQL_CHAR,		LVCFMT_RIGHT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_uLong,				CONST_str_chuLiuLiang_kbps,						SQL_CHAR,		LVCFMT_RIGHT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_uLong,				CONST_str_ruZiJieShu,							SQL_CHAR,		LVCFMT_RIGHT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_uLong,				CONST_str_chuZiJieShu,							SQL_CHAR,		LVCFMT_RIGHT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_platformId,			CONST_str_caoZuoXiTong,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_langId,				CONST_str_yuYan,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_xiTongMuLu,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_time,					CONST_str_zuiXinShuaXinShiJian,							SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	//
	{	CONST_qyColumnDisplayType_mac,					_T(  "MAC"  ),									SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	-1,		},
};


 QNM_QUERY_STRUCT  CONST_zjgaPcNetFlowListQueryStruct  =
{
	 CONST_zjgaPcNetFlowListSqlColumns,  CONST_zjgaPcNetFlowListDisplayColumns,
};

 //////////////

 QY_COLUMNINFO	CONST_zjgaPcNetShareListSqlColumns[]  =  
{
	{	0,	_T(  "qyPcNetShareTab.id"  ),						SQL_INTEGER,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),								SQL_CHAR,		},		//	5
	//
	{	6,	_T(  "qyPcNetShareTab.shi502_netname"  ),			SQL_CHAR,		},
	{	6,	_T(  "qyPcNetShareTab.shi502_path"  ),				SQL_CHAR,		},
	{	6,	_T(  "qyPcNetShareTab.shi502_type"  ),				SQL_INTEGER,		},
	//
	{	7,	_T(  "qyPcNetShareTab.iPlatformId"  ),					SQL_INTEGER,	},
	{	7,	_T(  "qyPcNetShareTab.uiLangId"  ),						SQL_INTEGER,	},
	{	7,	_T(  "qyPcNetShareTab.winDir"  ),							SQL_CHAR,		},
	//
	{	6,	_T(  "qyPcNetShareTab.lastTime"  ),						SQL_CHAR,		},
	//
	{	5,	_T(  "qyPcNetShareTab.mac0"  ),							SQL_CHAR,		},
	{	-1,	},
};

 QY_COLUMNINFO	CONST_zjgaPcNetShareListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,					_T(  "IP"  ),									SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_str,					CONST_str_shi502_netname,						SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_luJing,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_netShareType,			CONST_str_leiXing,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_platformId,			CONST_str_caoZuoXiTong,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_langId,				CONST_str_yuYan,								SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_xiTongMuLu,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	//
	{	CONST_qyColumnDisplayType_time,					CONST_str_zuiXinShuaXinShiJian,							SQL_CHAR,		LVCFMT_LEFT, 120,1, 50, },
	//
	{	CONST_qyColumnDisplayType_mac,					_T(  "MAC"  ),									SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	-1,		},
};


 QNM_QUERY_STRUCT  CONST_zjgaPcNetShareListQueryStruct  =
{
	 CONST_zjgaPcNetShareListSqlColumns,  CONST_zjgaPcNetShareListDisplayColumns,
};

 //////////////

#if  0
 QY_COLUMNINFO	CONST_zjgaPcAutoLogonListSqlColumns[]  =  
{
	{	0,	_T(  "autoLogonTab.id"  ),						SQL_INTEGER,	},
	MACRO_zjgaSimpleUsrSqlColumns
	{	5,	_T(  "qyPcTab.ip"  ),							SQL_CHAR,		},		//	5
	{	5,	_T(  "autoLogonTab.domainName"  ),				SQL_CHAR,		},
	{	5,	_T(  "autoLogonTab.logonName"  ),				SQL_CHAR,		},
	{	5,	_T(  "autoLogonTab.procedTime"  ),				SQL_CHAR,		},
	//
	{	5,	_T(  "autoLogonTab.mac0"  ),					SQL_CHAR,		},
	{	-1,															},
};

 QY_COLUMNINFO	CONST_zjgaPcAutoLogonListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,								SQL_CHAR,		LVCFMT_LEFT, 0,1, 50, },
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,					_T(  "IP"  ),									SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_domainName,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_str,					CONST_str_logonName,							SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	CONST_qyColumnDisplayType_time,					CONST_str_procedTime,							SQL_CHAR,		LVCFMT_LEFT, 130,1, 50,	},	//  13  
	//
	{	CONST_qyColumnDisplayType_mac,					_T(  "MAC"  ),									SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },
	{	-1,															},
};

 QNM_QUERY_STRUCT  CONST_zjgaPcAutoLogonListQueryStruct  =
{
	 CONST_zjgaPcAutoLogonListSqlColumns,  CONST_zjgaPcAutoLogonListDisplayColumns,
};
#endif


 ///////////////////////////////////


  //  显示网络设备管理策略列表的结构, 2005/03/05
 QY_COLUMNINFO  CONST_zjgaSnmpObjRuleListSqlColumns[]  =
{
	{	0,	_T(  "qySnmpObjRuleTab.id"  ),							SQL_INTEGER,												},
	{	0,	_T(  "qySnmpObjRuleTab.iType"  ),						SQL_INTEGER,												},
	{	0,	_T(  "qySnmpObjTab.productName"  ),						SQL_CHAR,													},
	{	0,	_T(  "qySnmpObjTab.cusName"  ),							SQL_CHAR,													},
	{	0,	_T(  "qySnmpObjTab.ip"  ),								SQL_CHAR,													},
	{	0,	_T(  "qySnmpObjPolicyTab.grpName"  ),					SQL_CHAR,													},
	{	0,	_T(  "qySnmpObjRuleTab.ibDirectConn"  ),				SQL_INTEGER,													},
	{	0,	_T(  "qySwitchPortTab.portIfDescr"  ),					SQL_CHAR,													},
	{	0,	_T(  "qySnmpObjRuleTab.ibDownPortIfMacChanged"  ),		SQL_INTEGER,													},
	{	0,	_T(  "qySnmpObjRuleTab.ibDownPortIfMacChangePort"  ),	SQL_INTEGER,													},
	{	0,	_T(  "qySnmpObjRuleTab.ibNotLogIfMacChanged"  ),		SQL_INTEGER,													},
	{	0,	_T(  "qySnmpObjRuleTab.warnPercentOfBand"  ),			SQL_INTEGER,													},
	{	0,	_T(  "qySnmpObjRuleTab.iProcType"  ),					SQL_INTEGER,													},
	{	0,	_T(  "qySnmpObjRuleTab.switchMac"  ),					SQL_CHAR,													},
	{	-1,	NULL,	},
};

 QY_COLUMNINFO  CONST_zjgaSnmpObjRuleListDisplayColumns[]  =
{
	{	CONST_qyColumnDisplayType_long,				CONST_str_xuHao,								SQL_INTEGER,	LVCFMT_LEFT, 60,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_ruleType,			CONST_str_leiXing,								SQL_INTEGER,	LVCFMT_LEFT, 100,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,				CONST_str_wangLuoSheBeiXingHao,					SQL_CHAR,		LVCFMT_LEFT, 150,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,				CONST_str_bieMing,								SQL_CHAR,		LVCFMT_LEFT, 60,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_ip12,				_T(  "IP"  ),									SQL_CHAR,		LVCFMT_LEFT, 100,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,				CONST_str_snmpZuCeLue,							SQL_CHAR,		LVCFMT_LEFT, 80,	1, 50,	},	//  13  
 	{	CONST_qyColumnDisplayType_snmpBool,			CONST_str_shiFoJieRu,							SQL_CHAR,		LVCFMT_LEFT, 60,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,				CONST_str_duanKou,								SQL_CHAR,		LVCFMT_LEFT, 120,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_snmpBool,			CONST_str_shiFouZuDuanXinZengLianJie,			SQL_CHAR,		LVCFMT_LEFT, 110,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_snmpBool,			CONST_str_shiFouZuDuanLianJieGengHuanDuanKou,	SQL_CHAR,		LVCFMT_LEFT, 140,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_snmpBool,			CONST_str_buJiLuLianJieBianGeng,				SQL_CHAR,		LVCFMT_LEFT, 110,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_withFactor,		CONST_str_baoJingLiuLiang,						SQL_CHAR,		LVCFMT_RIGHT, 135,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_snmpBool,			CONST_str_liuLiangBaoJingShiShiFouZuDuan,		SQL_CHAR,		LVCFMT_LEFT, 120,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_mac,				_T(  "MAC"  ),									SQL_CHAR,		LVCFMT_LEFT, 110,	1, 50,	},	//  13  
	{	-1,																									},
};

 QNM_QUERY_STRUCT  CONST_zjgaSnmpObjRuleListQueryStruct  =
{
	 CONST_zjgaSnmpObjRuleListSqlColumns,	CONST_zjgaSnmpObjRuleListDisplayColumns,
};

  //  显示网络设备管理策略列表的结构, 2005/03/05
 QY_COLUMNINFO  CONST_zjgaConflictConnListSqlColumns[]  =
{
	{	0,	_T(  "qnmConflictConnTab.id"  ),					SQL_INTEGER,												},
	{	0,	_T(  "qnmConflictConnTab.ucbLocked"  ),				SQL_CHAR,													},
	{	0,	_T(  "qySnmpObjTab.productName"  ),					SQL_CHAR,													},
	{	0,	_T(  "qySnmpObjTab.cusName"  ),						SQL_CHAR,													},
	{	0,	_T(  "qySnmpObjTab.ip"  ),							SQL_CHAR,													},
	{	0,	_T(  "qySwitchPortTab.portIfDescr"  ),				SQL_CHAR,													},
	{	0,	_T(  "qnmConflictConnTab.connectedMac"  ),			SQL_CHAR,													},
	{	0,	_T(  "qyPcTab.pcName"  ),							SQL_CHAR,													},
	{	0,	_T(  "qyPcTab.ip"  ),								SQL_CHAR,													},
	{	-1,						},
};

 QY_COLUMNINFO  CONST_zjgaConflictConnListDisplayColumns[]  =
{
	{	CONST_qyColumnDisplayType_long,				CONST_str_xuHao,				SQL_INTEGER,	LVCFMT_LEFT, 60,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_bool,				CONST_str_shiFoBangDing,			SQL_CHAR,		LVCFMT_LEFT, 60,	1, 50,	},
	{	CONST_qyColumnDisplayType_str,				CONST_str_wangLuoSheBeiXingHao,		SQL_CHAR,		LVCFMT_LEFT, 150,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,				CONST_str_bieMing,				SQL_CHAR,		LVCFMT_LEFT, 60,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_ip12,				_T(  "IP"  ),				SQL_CHAR,		LVCFMT_LEFT, 100,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,				CONST_str_bangDingDuanKou,			SQL_CHAR,		LVCFMT_LEFT, 120,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_mac,				_T(  "MAC"  ),				SQL_CHAR,		LVCFMT_LEFT, 87,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,				CONST_str_jiSuanJiMing,			SQL_CHAR,		LVCFMT_LEFT, 120,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_ip12,				CONST_str_jisuanjiIP,			SQL_CHAR,		LVCFMT_LEFT, 120,	1, 50,	},	//  13  
	{	-1,						},
};


 QNM_QUERY_STRUCT  CONST_zjgaConflictConnListQueryStruct  =
{
	 CONST_zjgaConflictConnListSqlColumns,	CONST_zjgaConflictConnListDisplayColumns,
};



 //  显示接入列表的结构, 2005/03/05
 QY_COLUMNINFO  CONST_zjgaDirectConnListSqlColumns[]  =
{
	{	0,	_T(  "qySnmpObjTab.productName"  ),					SQL_CHAR,													},
	{	0,	_T(  "qySnmpObjTab.cusName"  ),						SQL_CHAR,													},
	{	0,	_T(  "qySnmpObjTab.ip"  ),							SQL_CHAR,													},
	{	0,	_T(  "qySwitchPortTab.portIfDescr"  ),				SQL_CHAR,													},
	{	0,	_T(  "qyPcTab.pcName"  ),							SQL_CHAR,													},
	MACRO_zjgaSimpleUsrSqlColumns
	{	0,	_T(  "qyPcTab.ip"  ),								SQL_CHAR,													},
	{	0,	_T(  "qySwitchConnectedPcTab.connectedMac"  ),		SQL_CHAR,													},
	{	-1,						},
};

 QY_COLUMNINFO  CONST_zjgaDirectConnListDisplayColumns[]  =
{
	{	CONST_qyColumnDisplayType_str,				CONST_str_wangLuoSheBeiXingHao,		SQL_CHAR,		LVCFMT_LEFT, 150,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,				CONST_str_bieMing,				SQL_CHAR,		LVCFMT_LEFT, 60,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_ip12,				_T(  "IP"  ),				SQL_CHAR,		LVCFMT_LEFT, 100,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,				CONST_str_duanKou,				SQL_CHAR,		LVCFMT_LEFT, 120,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,				CONST_str_jiSuanJiMing,			SQL_CHAR,		LVCFMT_LEFT, 120,	1, 50,	},	//  13  
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ip12,				CONST_str_jisuanjiIP,			SQL_CHAR,		LVCFMT_LEFT, 120,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_mac,				_T(  "MAC"  ),				SQL_CHAR,		LVCFMT_LEFT, 87,	1, 50,	},	//  13  
	{	-1,						},
};



 QNM_QUERY_STRUCT  CONST_zjgaDirectConnListQueryStruct  =
{
	 CONST_zjgaDirectConnListSqlColumns,  CONST_zjgaDirectConnListDisplayColumns,
};

  //  显示网络设备联接列表的结构 
 QY_COLUMNINFO	CONST_zjgaNetDevConnListSqlColumns[]  =  
{
	{	0,	_T(  "qySwitchConnectedPcTab.lastTime"  ),			SQL_CHAR,													},		//  0
	{	0,	_T(  "qySnmpObjTab.place"  ),						SQL_CHAR,													},		//  0
	{	0,	_T(  "qySnmpObjTab.productName"  ),					SQL_CHAR,													},		//  0
	{	0,	_T(  "qySnmpObjTab.ip"  ),							SQL_CHAR,													},		//  0
	{	0,	_T(  "qySnmpObjTab.mac"  ),							SQL_CHAR,													},		//  0
	{	0,	_T(  "qySnmpObjTab.cusName"  ),						SQL_CHAR,													},		//  0
	{	0,	_T(  "qySwitchPortTab.portIfIndex"  ),				SQL_INTEGER,												},		//  0
	{	0,	_T(  "qySwitchConnectedPcTab.ucbDirectConn"  ),		SQL_CHAR,													},		//  0
	{	0,	_T(  "qySwitchConnectedPcTab.connectedIp"  ),		SQL_CHAR,													},		//  0
	{	0,	_T(  "qySwitchConnectedPcTab.connectedMac"  ),		SQL_CHAR,													},		//  0
	{	-1,																									},
};

 QY_COLUMNINFO	CONST_zjgaNetDevConnListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_time,		CONST_str_zuiJinLianXiShiJian,		SQL_CHAR,		LVCFMT_LEFT, 100,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,		CONST_str_shiYongDiDian,			SQL_CHAR,		LVCFMT_LEFT, 100,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,		CONST_str_wangLuoSheBeiXingHao,		SQL_CHAR,		LVCFMT_LEFT, 100,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_ip12,		_T(  "IP"  ),				SQL_CHAR,		LVCFMT_LEFT, 110,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_mac,		_T(  "MAC"  ),				SQL_CHAR,		LVCFMT_LEFT, 0,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,		CONST_str_bieMing,				SQL_CHAR,		LVCFMT_LEFT, 100,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_long,		CONST_str_duanKou,				SQL_INTEGER,	LVCFMT_LEFT, 50,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_bool,		CONST_str_shiFoJieRu,			SQL_CHAR,		LVCFMT_LEFT, 60,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_ip12,		CONST_str_lianJieIP,			SQL_CHAR,		LVCFMT_LEFT, 110,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_mac,		CONST_str_lianJieMAC,			SQL_CHAR,		LVCFMT_LEFT, 87,	1, 50,	},	//  13  
	{	-1,																									},
};


 QNM_QUERY_STRUCT  CONST_zjgaNetDevConnListQueryStruct  =
{
	 CONST_zjgaNetDevConnListSqlColumns,  CONST_zjgaNetDevConnListDisplayColumns,
};



 //  显示查询结果的结构 
 QY_COLUMNINFO	CONST_zjgaSearchListSqlColumns[]  =  
{
	{	0,	_T(  "qnmTmpTab.col0"  ),			SQL_CHAR,													},
	{	0,	_T(  "qnmTmpTab.mac"  ),			SQL_CHAR,													},		//  0
	{	0,	_T(  "qnmTmpTab.ip"  ),				SQL_CHAR,													},		//  0
	{	0,	_T(  "qnmTmpTab.des0"  ),			SQL_CHAR,													},		//  0
	{	-1,																									},
};


 QY_COLUMNINFO	CONST_zjgaSearchListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_str,		CONST_str_leiXing,		SQL_CHAR,		LVCFMT_LEFT, 100,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_mac,		_T(  "MAC"  ),		SQL_CHAR,		LVCFMT_LEFT, 100,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_ip12,		_T(  "IP"  ),		SQL_CHAR,		LVCFMT_LEFT, 120,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,		CONST_str_miaoShu,		SQL_CHAR,		LVCFMT_LEFT, 400,	1, 50,	},	//  13  
	{	-1,																									},
};


 QNM_QUERY_STRUCT  CONST_zjgaSearchListQueryStruct  =
{
	 CONST_zjgaSearchListSqlColumns,  CONST_zjgaSearchListDisplayColumns,
};



  //  显示所有系统事件列表的结构 
 QY_COLUMNINFO	CONST_zjgaOpEventListSqlColumns_netMc[]  =  
{
	{	0,	_T(  "qyPcEventTab.eventType"  ),		SQL_INTEGER,	},		//	0
	{	6,	_T(  "qyPcEventTab.usrName"  ),			SQL_CHAR,		},		//	6
	{	11,	_T(  "qyPcEventTab.des0"  ),			SQL_CHAR,		},		//	11	为检查工具使用
	{	7,	_T(  "qyPcEventTab.cntEventTime"  ),	SQL_CHAR,		},		//	7
	{	6,	_T(  "qyPcEventTab.dsnName"  ),			SQL_CHAR,		},	
	{	10,	_T(  "qyPcEventTab.comment0"  ),		SQL_CHAR,		},		//	10
	{	-1,										},
};
 
 QY_COLUMNINFO	CONST_zjgaOpEventListDisplayColumns_netMc[] = 
{
   {	CONST_qyColumnDisplayType_eventType,	CONST_str_event,				SQL_CHAR,		LVCFMT_LEFT, 120,	1,	50,		},	//  0
   {	CONST_qyColumnDisplayType_str,			CONST_str_yongHu,				SQL_CHAR,		LVCFMT_LEFT, 80,	1,	50,		},	//	12
   {	CONST_qyColumnDisplayType_str,			CONST_str_miaoShu,				SQL_CHAR,		LVCFMT_LEFT, 250,	1,	50,		},	//	5
   {	CONST_qyColumnDisplayType_time,			CONST_str_guanLiZhongXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 130,	1,	50,		},	//	6
   {	CONST_qyColumnDisplayType_str,			CONST_str_dsnName,				SQL_CHAR,		LVCFMT_LEFT, 80,	1,	50,		},	//	12
   {	CONST_qyColumnDisplayType_str,			CONST_str_beiZhu,				SQL_CHAR,		LVCFMT_LEFT, 80,	1,	50,		},	//	9
   {	-1,																},
};


 QNM_QUERY_STRUCT  CONST_zjgaOpEventListQueryStruct_netMc  =  
{
	 CONST_zjgaOpEventListSqlColumns_netMc,	CONST_zjgaOpEventListDisplayColumns_netMc,
};


 //  显示所有事件列表的结构 
 QY_COLUMNINFO	CONST_zjgaPcEventAllSqlColumns[]  =  
{
	{	0,	_T(  "qyPcEventTab.eventType"  ),		SQL_INTEGER,	},		//	0
	MACRO_zjgaEventSimpleUsrSqlColumns
	{	6,	_T(  "qyPcEventTab.ip"  ),				SQL_CHAR,		},		//	6

	{	11,	_T(  "qyPcEventTab.des2"  ),			SQL_CHAR,		},		//	11	为检查工具使用

	{	11,	_T(  "qyPcEventTab.des0"  ),			SQL_CHAR,		},		//	11	为检查工具使用
	{	11,	_T(  "qyPcEventTab.des1"  ),			SQL_CHAR,		},		//	11	为检查工具使用
	{	12, _T(  "qyPcEventTab.usrName"  ),			SQL_CHAR,		},		//	12
	{	8,	_T(  "qyPcEventTab.localEventTime"  ),	SQL_CHAR,		},		//	8
	{	7,	_T(  "qyPcEventTab.cntEventTime"  ),	SQL_CHAR,		},		//	7
	{	9,	_T(  "qyPcEventTab.mac0"  ),			SQL_CHAR,		},		//	9
	{	10,	_T(  "qyPcEventTab.comment0"  ),			SQL_CHAR,		},		//	10
	{	-1,										},
};
 
 QY_COLUMNINFO	CONST_zjgaPcEventAllDisplayColumns[] = 
{
   {	CONST_qyColumnDisplayType_eventType,	CONST_str_event,				SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50, },	//  0
   MACRO_zjgaEventSimpleUsrDisplayColumns
   {	CONST_qyColumnDisplayType_str,			_T(  "IP"  ),					SQL_CHAR,		LVCFMT_LEFT, 105,1, 50, },	//	5
  
   {	CONST_qyColumnDisplayType_qwmDevType,	CONST_str_miaoShu,				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//	5
 
   {	CONST_qyColumnDisplayType_str,			CONST_str_miaoShu,				SQL_CHAR,		LVCFMT_LEFT, 250,1, 50, },	//	5
   {	CONST_qyColumnDisplayType_str,			CONST_str_fuJiaMiaoShu,			SQL_CHAR,		LVCFMT_LEFT, 150,1, 50, },	//	5
   {	CONST_qyColumnDisplayType_str,			CONST_str_dengLvYongHu,			SQL_CHAR,		LVCFMT_LEFT, 80,1, 50, },	//	12
   {	CONST_qyColumnDisplayType_time,			CONST_str_benDiShiJian,			SQL_CHAR,		LVCFMT_LEFT, 110, 1, 50,	},	//	7
   {	CONST_qyColumnDisplayType_time,			CONST_str_guanLiZhongXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 110, 1,	50,	},	//	6
   {	CONST_qyColumnDisplayType_mac,			_T(  "MAC"  ),				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//	8
   {	CONST_qyColumnDisplayType_str,			CONST_str_beiZhu,				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//	9
   {	-1,																},
};


 QNM_QUERY_STRUCT  CONST_zjgaPcEventAllQueryStruct  =  
{
	 CONST_zjgaPcEventAllSqlColumns,	CONST_zjgaPcEventAllDisplayColumns,
};


  //  显示检查事件列表的结构 
 QY_COLUMNINFO	CONST_zjgaPcSecChkEventAllSqlColumns[]  =  
{
	{	0,	_T(  "qyPcSecChkEventTab.eventType"  ),		SQL_INTEGER,	},		//	0
	MACRO_eventSimpleUsrSqlColumnsEx(  "qyPcSecChkEventTab"  )
	{	6,	_T(  "qyPcSecChkEventTab.ip"  ),				SQL_CHAR,		},		//	6
	{	11,	_T(  "qyPcSecChkEventTab.des0"  ),			SQL_CHAR,		},		//	11	为检查工具使用
	{	11,	_T(  "qyPcSecChkEventTab.des1"  ),			SQL_CHAR,		},		//	11	为检查工具使用
	{	12, _T(  "qyPcSecChkEventTab.usrName"  ),			SQL_CHAR,		},		//	12
	{	8,	_T(  "qyPcSecChkEventTab.localEventTime"  ),	SQL_CHAR,		},		//	8
	{	7,	_T(  "qyPcSecChkEventTab.cntEventTime"  ),	SQL_CHAR,		},		//	7
	{	9,	_T(  "qyPcSecChkEventTab.mac0"  ),			SQL_CHAR,		},		//	9
	{	10,	_T(  "qyPcSecChkEventTab.comment0"  ),			SQL_CHAR,		},		//	10
	{	-1,										},
};


 QY_COLUMNINFO	CONST_zjgaPcSecChkEventAllDisplayColumns[] = 
{
   {	CONST_qyColumnDisplayType_eventType,	CONST_str_event,				SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50, },	//  0
   MACRO_zjgaEventSimpleUsrDisplayColumns
   {	CONST_qyColumnDisplayType_str,			_T(  "IP"  ),				SQL_CHAR,		LVCFMT_LEFT, 105,1, 50, },	//	5
   {	CONST_qyColumnDisplayType_str,			CONST_str_miaoShu,				SQL_CHAR,		LVCFMT_LEFT, 250,1, 50, },	//	5
   {	CONST_qyColumnDisplayType_str,			CONST_str_fuJiaMiaoShu,			SQL_CHAR,		LVCFMT_LEFT, 150,1, 50, },	//	5
   {	CONST_qyColumnDisplayType_str,			CONST_str_dengLvYongHu,			SQL_CHAR,		LVCFMT_LEFT, 80,1, 50, },	//	12
   {	CONST_qyColumnDisplayType_lTime,		CONST_str_benDiShiJian,			SQL_CHAR,		LVCFMT_LEFT, 110, 1, 50,	},	//	7
   {	CONST_qyColumnDisplayType_time,			CONST_str_guanLiZhongXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 110, 1,	50,	},	//	6
   {	CONST_qyColumnDisplayType_mac,			_T(  "MAC"  ),				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//	8
   {	CONST_qyColumnDisplayType_str,			CONST_str_beiZhu,				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//	9
   {	-1,																},
};


  QNM_QUERY_STRUCT  CONST_zjgaPcSecChkEventAllQueryStruct  =  
{
	 CONST_zjgaPcSecChkEventAllSqlColumns,	CONST_zjgaPcSecChkEventAllDisplayColumns,
};



  //  显示所有网络设备事件列表的结构 
 QY_COLUMNINFO	CONST_zjgaNetDevEventAllSqlColumns[]  =  
{
	{	0,	_T(  "qyPcEventTab.eventType"  ),		SQL_INTEGER,	},		//	0
	{	2,	_T(  "qyPcEventTab.col5"  ),			SQL_CHAR,		},		//  2
	{	5,	_T(  "qyPcEventTab.productName"  ),		SQL_CHAR,		},		//	5
	{	6,	_T(  "qyPcEventTab.ip"  ),				SQL_CHAR,		},		//	6
	{	11,	_T(  "qyPcEventTab.des0"  ),			SQL_CHAR,		},		//	11	为检查工具使用
	{	7,	_T(  "qyPcEventTab.cntEventTime"  ),	SQL_CHAR,		},		//	7
	{	9,	_T(  "qyPcEventTab.mac0"  ),			SQL_CHAR,		},		//	9
	{	11,	_T(  "qyPcEventTab.connectedMac"  ),	SQL_CHAR,		},		//  11
	{	10,	_T(  "qyPcEventTab.comment0"  ),		SQL_CHAR,		},		//	10
	{	-1,										},
};
 
 QY_COLUMNINFO	CONST_zjgaNetDevEventAllDisplayColumns[] = 
{
   {	CONST_qyColumnDisplayType_eventType,	CONST_str_event,				SQL_CHAR,		LVCFMT_LEFT, 120,	1, 50, },	//  0
   {	CONST_qyColumnDisplayType_str,			CONST_str_shiYongDiDian,			SQL_CHAR,		LVCFMT_LEFT, 60,	1, 50, },	//  3
   {	CONST_qyColumnDisplayType_str,			CONST_str_sheBeiXingHao,			SQL_CHAR,		LVCFMT_LEFT, 100,	1, 50, },	//  3
   {	CONST_qyColumnDisplayType_str,			_T(  "IP"  ),				SQL_CHAR,		LVCFMT_LEFT, 105,	1, 50, },	//	5
   {	CONST_qyColumnDisplayType_str,			CONST_str_miaoShu,				SQL_CHAR,		LVCFMT_LEFT, 380,	1, 50, },	//	5
   {	CONST_qyColumnDisplayType_time,			CONST_str_guanLiZhongXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 110,	1, 50, },	//	6
   {	CONST_qyColumnDisplayType_mac,			_T(  "MAC"  ),				SQL_CHAR,		LVCFMT_LEFT, 100,	1, 50, },	//	8
   {	CONST_qyColumnDisplayType_mac,			CONST_str_lianJieMAC,			SQL_CHAR,		LVCFMT_LEFT, 100,	1, 50, },	//	8
   {	CONST_qyColumnDisplayType_str,			CONST_str_beiZhu,				SQL_CHAR,		LVCFMT_LEFT, 80,	1, 50, },	//	9
   {	-1,																},
};



 QNM_QUERY_STRUCT  CONST_zjgaNetDevEventAllQueryStruct  =
{
	 CONST_zjgaNetDevEventAllSqlColumns,	CONST_zjgaNetDevEventAllDisplayColumns,
};

 //  显示拨号事件列表的结构 
 QY_COLUMNINFO	CONST_zjgaPcRasEventSqlColumns[]  =  
{
	{	0,	_T(  "qyPcEventTab.eventType"  ),		SQL_INTEGER,	},		//	0
	MACRO_zjgaEventSimpleUsrSqlColumns
	{	6,	_T(  "qyPcEventTab.des0"  ),			SQL_CHAR,		},		//	6
	{	7,	_T(  "qyPcEventTab.des1"  ),			SQL_CHAR,		},		//  7
	{	8,	_T(  "qyPcEventTab.cntEventTime"  ),	SQL_CHAR,		},		//  8
	{	9,	_T(  "qyPcEventTab.localEventTime"  ),	SQL_CHAR,		},		//	9
	{	10,	_T(  "qyPcEventTab.ip"  ),				SQL_CHAR,		},		//	10
	{	11,	_T(  "qyPcEventTab.mac0"  ),			SQL_CHAR,		},		//	11
	{	-1,													},
};




 
 QY_COLUMNINFO	CONST_zjgaPcRasEventDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_eventType,	CONST_str_event,				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  0
	MACRO_zjgaEventSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_str,			CONST_str_boHaoQuanXian,			SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },	//	
	{	CONST_qyColumnDisplayType_str,			CONST_str_boHaoHaoMa,			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//	9
	{	CONST_qyColumnDisplayType_time,			CONST_str_guanLiZhongXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 110, 1, 50, },	//	9
	{	CONST_qyColumnDisplayType_time,			CONST_str_benDiShiJian,			SQL_CHAR,		LVCFMT_LEFT, 110, 1, 50,	},	//	7
	{	CONST_qyColumnDisplayType_str,			_T(  "IP"  ),				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//	8
	{	CONST_qyColumnDisplayType_str,			_T(  "MAC"  ),				SQL_CHAR,		LVCFMT_LEFT, 100,1,	50,	},	//	6
	{	-1,																									},
};


 QNM_QUERY_STRUCT  CONST_zjgaPcRasEventQueryStruct  =  
{
	 CONST_zjgaPcRasEventSqlColumns,	CONST_zjgaPcRasEventDisplayColumns,
};

/*
 //  显示所有安检事件列表的结构 
 QY_COLUMNINFO	CONST_zjgaSecChkEventAllSqlColumns[]  =  
{
	{	0,	_T(  "qyPcEventTab.eventType"  ),		SQL_INTEGER,	},		//	0
	//  MACRO_zjgaSimpleUsrSqlColumns								//  2005/05/04, 为了符合普通管理单位的需要，将当前用户改为历史用户信息
	MACRO_zjgaEventSimpleUsrSqlColumns
	{	6,	_T(  "qyPcEventTab.ip"  ),				SQL_CHAR,		},		//	6
	{	11,	_T(  "qyPcEventTab.des0"  ),			SQL_CHAR,		},		//	11	为检查工具使用
	{	11,	_T(  "qyPcEventTab.des1"  ),			SQL_CHAR,		},		//	11	为检查工具使用
	{	12, _T(  "qyPcEventTab.usrName"  ),			SQL_CHAR,		},		//	12
	{	8,	_T(  "qyPcEventTab.localEventTime"  ),	SQL_CHAR,		},		//	8
	{	7,	_T(  "qyPcEventTab.cntEventTime"  ),	SQL_CHAR,		},		//	7
	{	9,	_T(  "qyPcEventTab.mac0"  ),			SQL_CHAR,		},		//	9
	{	10,	_T(  "qyPcEventTab.comment0"  ),			SQL_CHAR,		},		//	10
	{	-1,										},
};
 
 QY_COLUMNINFO	CONST_zjgaSecChkEventAllDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_eventType,	CONST_str_event,				SQL_CHAR,		LVCFMT_LEFT, 100, 1, 50, },	//  0
	MACRO_zjgaSimpleUsrDisplayColumns
   	{	CONST_qyColumnDisplayType_str,			_T(  "IP"  ),				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//	5
	{	CONST_qyColumnDisplayType_str,			CONST_str_miaoShu,				SQL_CHAR,		LVCFMT_LEFT, 250,1, 50, },	//	5
	{	CONST_qyColumnDisplayType_str,			CONST_str_fuJiaMiaoShu,			SQL_CHAR,		LVCFMT_LEFT, 50,1, 50, },	//	5
	{	CONST_qyColumnDisplayType_str,			CONST_str_dengLvYongHu,			SQL_CHAR,		LVCFMT_LEFT, 80,1, 50, },	//	12
   	{	CONST_qyColumnDisplayType_time,			CONST_str_benDiShiJian,			SQL_CHAR,		LVCFMT_LEFT, 110, 1, 50,	},	//	7
   	{	CONST_qyColumnDisplayType_time,			CONST_str_guanLiZhongXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 110, 1,	50,	},	//	6
   	{	CONST_qyColumnDisplayType_str,			_T(  "MAC"  ),				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//	8
   	{	CONST_qyColumnDisplayType_str,			CONST_str_beiZhu,				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//	9
	{	-1,																},
};


 QNM_QUERY_STRUCT  CONST_zjgaSecChkEventAllQueryStruct  =
{
	 CONST_zjgaSecChkEventAllSqlColumns,	CONST_zjgaSecChkEventAllDisplayColumns,
};
*/

 /*
QNM_QUERY_STRUCT	*	gpSimpleUsrQueryStruct				=  &CONST_zjgaSimpleUsrQueryStruct;
QNM_QUERY_STRUCT	*	gpPcListQueryStruct					=  &CONST_zjgaPcListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcAssetListQueryStruct			=  &CONST_zjgaPcAssetListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcAssetReportListQueryStruct		=  &CONST_zjgaPcAssetReportListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcAssetReportListQueryStruct_en	=  &CONST_zjgaPcAssetReportListQueryStruct_en;
QNM_QUERY_STRUCT	*	gpPcSpListQueryStruct				=  &CONST_zjgaPcSpListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcSpSpecialListQueryStruct		=  &CONST_zjgaPcSpSpecialListQueryStruct;
//  QNM_QUERY_STRUCT	*	gpUnchkedPcListQueryStruct			=  &CONST_zjgaUnchkedPcListQueryStruct;
//  QNM_QUERY_STRUCT	*	gpWillAttackPcListQueryStruct		=  &CONST_zjgaUnchkedPcListQueryStruct;  //  &CONST_zjgaWillAttackPcListQueryStruct;
//
QNM_QUERY_STRUCT	*	gpPcUsrListQueryStruct				=  &CONST_zjgaPcUsrListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcUsrInTab1ListQueryStruct		=  &CONST_zjgaPcUsrInTab1ListQueryStruct;
QNM_QUERY_STRUCT	*	gpQwmSvrListQueryStruct				=  &CONST_zjgaQwmSvrListQueryStruct;
//
QNM_QUERY_STRUCT	*	gpPcRasRuleListQueryStruct			=  &CONST_zjgaPcRuleListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcAdapterListQueryStruct			=  &CONST_zjgaPcAdapterListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcProxyCfgListQueryStruct			=  &CONST_zjgaPcProxyCfgListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcComputerPropListQueryStruct		=  &CONST_zjgaPcComputerPropListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcComputerRuleListQueryStruct		=  &CONST_zjgaPcComputerRuleListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcPrinterPropListQueryStruct		=  &CONST_zjgaPcPrinterPropListQueryStruct;
//
QNM_QUERY_STRUCT	*	gpPcEventLogListQueryStruct			=  &CONST_zjgaPcEventLogListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcOsUsrListQueryStruct			=  &CONST_zjgaPcOsUsrListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcNetStatListQueryStruct			=  &CONST_zjgaPcNetStatListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcProcessPropListQueryStruct		=  &CONST_zjgaPcProcessPropListQueryStruct;
QNM_QUERY_STRUCT	*	gpPcProcessRuleListQueryStruct		=  &CONST_zjgaPcProcessRuleListQueryStruct;
//
QNM_QUERY_STRUCT	*	gpSnmpObjRuleListQueryStruct		=  &CONST_zjgaSnmpObjRuleListQueryStruct;
QNM_QUERY_STRUCT	*	gpConflictConnListQueryStruct		=  &CONST_zjgaConflictConnListQueryStruct;
QNM_QUERY_STRUCT	*	gpDirectConnListQueryStruct			=  &CONST_zjgaDirectConnListQueryStruct;
QNM_QUERY_STRUCT	*	gpNetDevConnListQueryStruct			=  &CONST_zjgaNetDevConnListQueryStruct;
QNM_QUERY_STRUCT	*	gpSearchListQueryStruct				=  &CONST_zjgaSearchListQueryStruct;
QNM_QUERY_STRUCT	*	gpOpEventAllQueryStruct				=  &CONST_zjgaOpEventAllQueryStruct;
QNM_QUERY_STRUCT	*	gpPcEventAllQueryStruct				=  &CONST_zjgaPcEventAllQueryStruct;
QNM_QUERY_STRUCT	*	gpNetDevEventAllQueryStruct			=  &CONST_zjgaNetDevEventAllQueryStruct;
QNM_QUERY_STRUCT	*	gpPcRasEventQueryStruct				=  &CONST_zjgaPcRasEventQueryStruct;
QNM_QUERY_STRUCT	*	gpSecChkEventAllQueryStruct			=  &CONST_zjgaSecChkEventAllQueryStruct;
*/
extern  QNM_QUERY_STRUCT  CONST_simpleUsrQueryStruct_is;
extern  QNM_QUERY_STRUCT  CONST_messengerAuthListQueryStruct;
extern  QNM_QUERY_STRUCT  CONST_messengerAuthNeedAuditedListQueryStruct;
extern  QNM_QUERY_STRUCT  CONST_imAmListQueryStruct;
extern  QNM_QUERY_STRUCT  CONST_phoneMessengerListQueryStruct;
//
extern  QNM_QUERY_STRUCT  CONST_imGrpAuthListQueryStruct_isMgr;
extern  QNM_QUERY_STRUCT  CONST_imGrpListQueryStruct_isMgr;
extern  QNM_QUERY_STRUCT  CONST_imGrpListQueryStruct_isClient;
extern  QNM_QUERY_STRUCT  CONST_imGrpAuthMemListQueryStruct_isMgr;
extern  QNM_QUERY_STRUCT  CONST_imGrpMemListQueryStruct_isMgr;
extern  QNM_QUERY_STRUCT  CONST_imGrpMemListQueryStruct_isClient;
extern  QNM_QUERY_STRUCT  CONST_imObjListQueryStruct_isMgr;
extern  QNM_QUERY_STRUCT  CONST_imObjListQueryStruct_isClient;
extern  QNM_QUERY_STRUCT  CONST_imObjUsrListQueryStruct_isMgr;
extern  QNM_QUERY_STRUCT  CONST_imObjUsrListQueryStruct_isClient;
extern  QNM_QUERY_STRUCT  CONST_imObjUsrInTab1ListQueryStruct_is;
extern  QNM_QUERY_STRUCT  CONST_clientListQueryStruct_is;
extern  QNM_QUERY_STRUCT  CONST_customerServiceListQueryStruct_is;
extern  QNM_QUERY_STRUCT  CONST_webContactListQueryStruct_is;
extern  QNM_QUERY_STRUCT  CONST_ipKnowledgeListQueryStruct_is;
extern  QNM_QUERY_STRUCT  CONST_phoneGuestListQueryStruct_is;
extern  QNM_QUERY_STRUCT  CONST_gsmModemListQueryStruct_isMgr;
extern  QNM_QUERY_STRUCT  CONST_smContactListQueryStruct_isMgr;
extern  QNM_QUERY_STRUCT  CONST_sharedDynBmpListQueryStruct_isMgr;
extern  QNM_QUERY_STRUCT  CONST_sharedDynBmpRuleListQueryStruct_isMgr;
extern  QNM_QUERY_STRUCT  CONST_imObjRuleListQueryStruct_isMgr;
extern  QNM_QUERY_STRUCT  CONST_imObjRuleListQueryStruct_isClient;

//
extern  QNM_QUERY_STRUCT  CONST_imTaskListQueryStruct;
extern  QNM_QUERY_STRUCT  CONST_imMsgListQueryStruct_isMgr;
extern  QNM_QUERY_STRUCT  CONST_imMsgListQueryStruct_isClient;
extern  QNM_QUERY_STRUCT  CONST_imEventListQueryStruct_is;
extern  QNM_QUERY_STRUCT  CONST_opEventListQueryStruct_is;





 QY_DMITEM  CONST_queryTable[]  =
{
	{	CONST_resId_gpBhbLogQueryStruct,						(  TCHAR  *  )&CONST_bhbLogQueryStruct,			},
	{	CONST_resId_gpBhbOfflineLogQueryStruct,					(  TCHAR  *  )&CONST_bhbOfflineLogQueryStruct,	},
	{	CONST_resId_gpScannedIpListQueryStruct,					(  TCHAR  *  )&CONST_scannedIpListQueryStruct,	},
	//
	{	CONST_resId_gpSimpleUsrQueryStruct,						(  TCHAR  *  )&CONST_zjgaSimpleUsrQueryStruct,	},
	{	CONST_resId_gpPcListQueryStruct,						(  TCHAR  *  )&CONST_zjgaPcListQueryStruct,	},
	{	CONST_resId_gpPcListQueryStruct_netMc2,					(  TCHAR  *  )&CONST_zjgaPcListQueryStruct_netMc2,	},
	{	CONST_resId_gpPcAssetListQueryStruct,					(  TCHAR  *  )&CONST_zjgaPcAssetListQueryStruct,	},
	{	CONST_resId_gpPcAssetReportListQueryStruct,				(  TCHAR  *  )&CONST_zjgaPcAssetReportListQueryStruct,	},
	{	CONST_resId_gpPcAssetReportListQueryStruct_en,			(  TCHAR  *  )&CONST_zjgaPcAssetReportListQueryStruct_en,	},
	{	CONST_resId_gpPcSpListQueryStruct,						(  TCHAR  *  )&CONST_zjgaPcSpListQueryStruct,	},
	{	CONST_resId_gpPcSpSpecialListQueryStruct,				(  TCHAR  *  )&CONST_zjgaPcSpSpecialListQueryStruct,	},
	//	{	CONST_resId_gpUnchkedPcListQueryStruct,				(  TCHAR  *  )&CONST_zjgaUnchkedPcListQueryStruct,	},
	//  {	CONST_resId_gpWillAttackPcListQueryStruct,			(  TCHAR  *  )&CONST_zjgaUnchkedPcListQueryStruct,	},  //  &CONST_zjgaWillAttackPcListQueryStruct,	},
	//
	{	CONST_resId_gpPcUsrListQueryStruct,						(  TCHAR  *  )&CONST_zjgaPcUsrListQueryStruct,	},
	{	CONST_resId_gpPcUsrInTab1ListQueryStruct,				(  TCHAR  *  )&CONST_zjgaPcUsrInTab1ListQueryStruct,	},
	{	CONST_resId_gpClientListQueryStruct_netMc,				(  TCHAR  *  )&CONST_zjgaQwmSvrListQueryStruct,	},
	//
	{	CONST_resId_gpPcSecChkEventAllQueryStruct,				(  TCHAR  *  )&CONST_zjgaPcSecChkEventAllQueryStruct,	},	
	//  {	CONST_resId_gpSecChkEventAllQueryStruct,			(  TCHAR  *  )&CONST_zjgaSecChkEventAllQueryStruct,	},
	//
	{	CONST_resId_gpPcRuleListQueryStruct0,					(  TCHAR  *  )&CONST_zjgaPcRuleListQueryStruct0,	},
	{	CONST_resId_gpPcRuleListQueryStruct1,					(  TCHAR  *  )&CONST_zjgaPcRuleListQueryStruct1,	},

	{	CONST_resId_gpPcAdapterListQueryStruct,					(  TCHAR  *  )&CONST_zjgaPcAdapterListQueryStruct,	},
	{	CONST_resId_gpPcProxyCfgListQueryStruct,				(  TCHAR  *  )&CONST_zjgaPcProxyCfgListQueryStruct,	},
	//  {	CONST_resId_gpPcComputerPropListQueryStruct,			(  TCHAR  *  )&CONST_zjgaPcComputerPropListQueryStruct,	},
	//  {	CONST_resId_gpPcComputerRuleListQueryStruct,			(  TCHAR  *  )&CONST_zjgaPcComputerRuleListQueryStruct,	},
	{	CONST_resId_gpPcWindowsUpdatePolicyListQueryStruct,		(  TCHAR  *  )&CONST_zjgaPcWindowsUpdatePolicyListQueryStruct,	},
	{	CONST_resId_gpPcPrinterPropListQueryStruct,				(  TCHAR  *  )&CONST_zjgaPcPrinterPropListQueryStruct,	},
	//
	{	CONST_resId_gpPcRegistryListQueryStruct,				(  TCHAR  *  )&CONST_zjgaPcRegistryListQueryStruct,	},
	{	CONST_resId_gpPcRegistryRuleStatusListQueryStruct,		(  TCHAR  *  )&CONST_zjgaPcRegistryRuleStatusListQueryStruct,	},
	{	CONST_resId_gpPcEventLogListQueryStruct,				(  TCHAR  *  )&CONST_zjgaPcEventLogListQueryStruct,	},
	{	CONST_resId_gpPcOsUsrListQueryStruct,					(  TCHAR  *  )&CONST_zjgaPcOsUsrListQueryStruct,	},
	{	CONST_resId_gpPcNetStatListQueryStruct,					(  TCHAR  *  )&CONST_zjgaPcNetStatListQueryStruct,	},
	{	CONST_resId_gpPcProcessPropListQueryStruct,				(  TCHAR  *  )&CONST_zjgaPcProcessPropListQueryStruct,	},
	{	CONST_resId_gpPcProcessModulePropListQueryStruct,		(  TCHAR  *  )&CONST_zjgaPcProcessModulePropListQueryStruct,	},
	{	CONST_resId_gpPcProcessRuleListQueryStruct,				(  TCHAR  *  )&CONST_zjgaPcProcessRuleListQueryStruct,	},
	{	CONST_resId_gpPcProcessKnowledgeListQueryStruct,		(  TCHAR  *  )&CONST_zjgaPcProcessKnowledgeListQueryStruct,	},
	{	CONST_resId_gpPcRegistryKnowledgeListQueryStruct,		(  TCHAR  *  )&CONST_zjgaPcRegistryKnowledgeListQueryStruct,	},
	{	CONST_resId_gpPcNetFlowListQueryStruct,					(  TCHAR  *  )&CONST_zjgaPcNetFlowListQueryStruct,				},
	{	CONST_resId_gpPcNetShareListQueryStruct,				(  TCHAR  *  )&CONST_zjgaPcNetShareListQueryStruct,				},
	//
	//  {	CONST_resId_gpPcAutoLogonListQueryStruct,				(  TCHAR  *  )&CONST_zjgaPcAutoLogonListQueryStruct,	},
	//
	{	CONST_resId_gpSnmpObjRuleListQueryStruct,				(  TCHAR  *  )&CONST_zjgaSnmpObjRuleListQueryStruct,	},
	{	CONST_resId_gpConflictConnListQueryStruct,				(  TCHAR  *  )&CONST_zjgaConflictConnListQueryStruct,	},
	{	CONST_resId_gpDirectConnListQueryStruct,				(  TCHAR  *  )&CONST_zjgaDirectConnListQueryStruct,	},
	{	CONST_resId_gpNetDevConnListQueryStruct,				(  TCHAR  *  )&CONST_zjgaNetDevConnListQueryStruct,	},
	{	CONST_resId_gpSearchListQueryStruct,					(  TCHAR  *  )&CONST_zjgaSearchListQueryStruct,	},
	{	CONST_resId_gpOpEventListQueryStruct_netMc,				(  TCHAR  *  )&CONST_zjgaOpEventListQueryStruct_netMc,	},
	{	CONST_resId_gpPcEventAllQueryStruct,					(  TCHAR  *  )&CONST_zjgaPcEventAllQueryStruct,	},
	{	CONST_resId_gpNetDevEventAllQueryStruct,				(  TCHAR  *  )&CONST_zjgaNetDevEventAllQueryStruct,	},
	{	CONST_resId_gpPcRasEventQueryStruct,					(  TCHAR  *  )&CONST_zjgaPcRasEventQueryStruct,	},
	//
	//
	{	CONST_resId_gpSimpleUsrQueryStruct_is,					(  TCHAR  *  )&CONST_simpleUsrQueryStruct_is,			},
	{	CONST_resId_gpMessengerAuthListQueryStruct,				(  TCHAR  *  )&CONST_messengerAuthListQueryStruct,			},
	{	CONST_resId_gpMessengerAuthNeedAuditedListQueryStruct,	(  TCHAR  *  )&CONST_messengerAuthNeedAuditedListQueryStruct,			},
	{	CONST_resId_gpImAmListQueryStruct,						(  TCHAR  *  )&CONST_imAmListQueryStruct,					},
	{	CONST_resId_gpPhoneMessengerListQueryStruct,			(  TCHAR  *  )&CONST_phoneMessengerListQueryStruct,			},
	//
	{	CONST_resId_gpImGrpAuthListQueryStruct_isMgr,			(  TCHAR  *  )&CONST_imGrpAuthListQueryStruct_isMgr,			},
	//  {	CONST_resId_gpImGrpAuthListQueryStruct_isClient,	(  TCHAR  *  )&CONST_imGrpAuthListQueryStruct_isClient,			},
	//
	{	CONST_resId_gpImGrpListQueryStruct_isMgr,				(  TCHAR  *  )&CONST_imGrpListQueryStruct_isMgr,			},
	{	CONST_resId_gpImGrpListQueryStruct_isClient,			(  TCHAR  *  )&CONST_imGrpListQueryStruct_isClient,			},
	{	CONST_resId_gpImGrpAuthMemListQueryStruct_isMgr,		(  TCHAR  *  )&CONST_imGrpAuthMemListQueryStruct_isMgr,			},
	{	CONST_resId_gpImGrpMemListQueryStruct_isMgr,			(  TCHAR  *  )&CONST_imGrpMemListQueryStruct_isMgr,			},
	{	CONST_resId_gpImGrpMemListQueryStruct_isClient,			(  TCHAR  *  )&CONST_imGrpMemListQueryStruct_isClient,			},
	{	CONST_resId_gpImObjListQueryStruct_isMgr,				(  TCHAR  *  )&CONST_imObjListQueryStruct_isMgr,			},
	{	CONST_resId_gpImObjListQueryStruct_isClient,			(  TCHAR  *  )&CONST_imObjListQueryStruct_isClient,			},
	{	CONST_resId_gpImObjUsrListQueryStruct_isMgr,			(  TCHAR  *  )&CONST_imObjUsrListQueryStruct_isMgr,		},
	{	CONST_resId_gpImObjUsrInTab1ListQueryStruct_isMgr,		(  TCHAR  *  )&CONST_imObjUsrListQueryStruct_isMgr,		},
	{	CONST_resId_gpImObjUsrListQueryStruct_isClient,			(  TCHAR  *  )&CONST_imObjUsrListQueryStruct_isClient,		},
	{	CONST_resId_gpImObjUsrInTab1ListQueryStruct_isClient,	(  TCHAR  *  )&CONST_imObjUsrInTab1ListQueryStruct_is,		},
	{	CONST_resId_gpClientListQueryStruct_is,					(  TCHAR  *  )&CONST_clientListQueryStruct_is,				},
	{	CONST_resId_gpCustomerServiceListQueryStruct_is,		(  TCHAR  *  )&CONST_customerServiceListQueryStruct_is,		},
	{	CONST_resId_gpWebContactListQueryStruct_is,				(  TCHAR  *  )&CONST_webContactListQueryStruct_is,				},
	{	CONST_resId_gpIpKnowledgeListQueryStruct_is,			(  TCHAR  *  )&CONST_ipKnowledgeListQueryStruct_is,			},
	{	CONST_resId_gpPhoneGuestListQueryStruct_is,				(  TCHAR  *  )&CONST_phoneGuestListQueryStruct_is,			},
	{	CONST_resId_gpGsmModemListQueryStruct_isMgr,			(  TCHAR  *  )&CONST_gsmModemListQueryStruct_isMgr,			},
	{	CONST_resId_gpSmContactListQueryStruct_isMgr,			(  TCHAR  *  )&CONST_smContactListQueryStruct_isMgr,		},
	{	CONST_resId_gpSharedDynBmpListQueryStruct_isMgr,		(  TCHAR  *  )&CONST_sharedDynBmpListQueryStruct_isMgr,		},
	{	CONST_resId_gpSharedDynBmpRuleListQueryStruct_isMgr,	(  TCHAR  *  )&CONST_sharedDynBmpRuleListQueryStruct_isMgr,	},
	{	CONST_resId_gpImObjRuleListQueryStruct_isMgr,			(  TCHAR  *  )&CONST_imObjRuleListQueryStruct_isMgr,				},
	{	CONST_resId_gpImObjRuleListQueryStruct_isClient,		(  TCHAR  *  )&CONST_imObjRuleListQueryStruct_isClient,				},
	//
	{	CONST_resId_gpImTaskListQueryStruct,					(  TCHAR  *  )&CONST_imTaskListQueryStruct,			},
	{	CONST_resId_gpImMsgListQueryStruct_isMgr,				(  TCHAR  *  )&CONST_imMsgListQueryStruct_isMgr,				},
	{	CONST_resId_gpImMsgListQueryStruct_isClient,			(  TCHAR  *  )&CONST_imMsgListQueryStruct_isClient,				},

	//
	{	CONST_resId_gpEventListQueryStruct_is,					(  TCHAR  *  )&CONST_imEventListQueryStruct_is,		},
	{	CONST_resId_gpOpEventListQueryStruct_is,				(  TCHAR  *  )&CONST_opEventListQueryStruct_is,	},


	//
	{	-1,		},
};


#endif	
//  }  以上是的界面显示信息



