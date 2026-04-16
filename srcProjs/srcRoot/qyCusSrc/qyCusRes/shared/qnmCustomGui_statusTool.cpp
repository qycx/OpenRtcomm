

#include	"stdafx.h"
#include	<tchar.h>
//  #include	"qyCommon.h"
#include	"afxres.h"
#include	"resource_statusTool.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"qnmCustomStr_common.h"

 QY_DMITEM  CONST_strTable_statusTool[]  =
{
	{	CONST_resId_null,						_T(  ""  ),				},
	{	IDD_qyCommStatus,						_T(  "StatusTool"  ),			},
		{	IDC_RADIO_qwmComm,					CONST_str_qwmCommStatus,		},
		{	IDC_RADIO_qnmChking,				CONST_str_qnmChkingStatus,	},
		{	IDC_RADIO_scanningIp,				CONST_str_scanningIpStatus,	},
	//
	{	IDD_qnmChkingStatus,					CONST_str_qnmChkingStatus,		},
		{	IDC_STATIC_serviceStatus_netMc,			CONST_str_serviceStatus,	},
		{	IDC_STATIC_serviceStatus_is,			CONST_str_serviceStatus,	},
		{	IDC_STATIC_nm,							CONST_str_nm,		},
	{	IDD_qwmCommStatus,						CONST_str_qwmCommStatus,		},
	/*
	{	IDD_ABOUTBOX,							_T(  "关于qycx Monitor"		),			},
		{	IDC_STATIC_ver,							_T(  "qyStatusTool 1.0 版"  ),		},	
		{	IDC_STATIC_qycxCopyRight,				_T(  "版权所有 (C) 2002 北京清扬创新公司 www.qycx.com"  ),		},
	*/
	{	CONST_resId_communicationStatus,		CONST_str_communicationStatus,	},
	{	CONST_resId_communicationStatusWithFilters,	CONST_str_communicationStatusWithFilters,	},
	{	CONST_resId_export,							CONST_str_export,							},
	{	CONST_resId_uninstallClient,				CONST_str_uninstallClient,					},
	{	CONST_resId_allClientsAllowed,				CONST_str_allClientsAllowed,					},
	{	CONST_resId_onlyMgrRegList,					CONST_str_onlyMgrRegList,					},
	{	CONST_resId_mgrAnyOne,						CONST_str_mgrAnyOne,						},		
	{	CONST_resId_serviceIsRunning,				CONST_str_serviceIsRunning,					},
	{	CONST_resId_serviceHaveStopped,				CONST_str_serviceHaveStopped,				},
	{	CONST_resId_hintToEmpty,					CONST_str_hintToEmpty,					},
	{	CONST_resId_resetWhenUpTo,					CONST_str_resetWhenUpTo,					},

	{	IDC_CHECK_autoClearup,						CONST_str_hintToEmpty,						},

	{	IDD_ip,									CONST_str_ip,		},
		{	IDOK,								CONST_str_OK,					},
		{	IDCANCEL,							CONST_str_CANCEL,					},
	{	IDD_scanningIpStatus,					CONST_str_scanningIpStatus,		},
		{	IDC_STATIC_ipScan,						CONST_str_ipScan,		},
		{	IDC_STATIC_scanningNetworkSegment,		CONST_str_scanningNetworkSegment,		},
		{	IDC_STATIC_scanningIp,					CONST_str_scanningIp,		},
		{	IDC_STATIC_bhbScanningNetworkSegment,	CONST_str_bhbScanningNetworkSegment,		},
	{	IDD_filters,							CONST_str_filters,								},
		{	IDC_STATIC_clientIp0,					CONST_str_clientIp0,							},		//  _T(  "Client IP0:"  )
		{	IDC_STATIC_clientIp1,					CONST_str_clientIp1,							},		//  _T(  "Client IP1:"  )
		{	IDC_STATIC_staticFilter0,				CONST_str_staticFilter0,		},
		{	IDC_STATIC_staticFilter1,				CONST_str_staticFilter1,		},
		{	IDC_STATIC_staticFilter2,				CONST_str_staticFilter2,		},
		{	IDC_STATIC_staticFilter3,				CONST_str_staticFilter3,		},

	{	-1,		},

	
};
/*
 QY_DMITEM  CONST_dlgTable_ABOUTBOX[]  =
{
	{	IDC_STATIC_ver,							},	//  _T(  "qyStatusTool 1.0 版"  ),		},	
	{	IDC_STATIC_qycxCopyRight,				},	//  _T(  "版权所有 (C) 2002 北京清扬创新公司 www.qycx.com"  ),		},
	{	-1,		},
};
*/

 QY_DMITEM  CONST_dlgTable_qyCommStatus[]  =
{
	{	IDC_STATIC_serviceStatus_netMc,		},
	{	IDC_STATIC_serviceStatus_is,		},
	{	IDC_STATIC_nm,						},
	{	IDC_RADIO_qwmComm,					},
	{	IDC_RADIO_qnmChking,				},
	{	IDC_RADIO_scanningIp,					},

	{	-1,	},
 };


 QY_DMITEM  CONST_dlgTable_qnmChkingStatus[]  =
{
	//{
	{	IDC_STATIC_serviceStatus_netMc,		},
	{	IDC_STATIC_nm,						},		
	{	-1,	},
 };

 QY_DMITEM  CONST_dlgTable_qwmCommStatus[]  =
{
	{	IDC_STATIC_serviceStatus_netMc,		},
	{	IDC_STATIC_serviceStatus_is,		},
	{	IDC_STATIC_nm,						},

	{	-1,	},
 };

 QY_DMITEM	CONST_dlgTable_scanningIpStatus[]	=
{
	{	IDC_STATIC_serviceStatus_netMc,			},		//  _T(  "即将显示应用系统服务状态"  ),		},
	{	IDC_STATIC_ipScan,						},		//  _T(  "即将显示IP扫描检测控制状态"  ),		},
	{	IDC_STATIC_scanningNetworkSegment,		},		//  _T(  "即将显示扫描检测网段"  ),		},
	{	IDC_STATIC_scanningIp,					},		//  _T(  "即将显示扫描主机状态"  ),		},
	{	IDC_STATIC_bhbScanningNetworkSegment,	},		//  _T(  "即将显示拨号检测的扫描进程"  ),		},
	{	-1,			},
};

 QY_DMITEM	CONST_dlgTable_filters[]	=
{
	{	IDC_STATIC_clientIp0,		},
	{	IDC_STATIC_clientIp1,		},
	{	IDC_STATIC_staticFilter0,	},		//  _T(  "即将显示拨号检测的扫描进程"  ),		},
	{	IDC_STATIC_staticFilter1,	},
	{	IDC_STATIC_staticFilter2,	},
	{	IDC_STATIC_staticFilter3,	},
	{	IDOK,							},
	{	IDCANCEL,						},

	{	-1,			},
};


 QY_DMITEM  CONST_dlgTable_statusTool[]  =
{
	//  {	IDD_ABOUTBOX,						(  TCHAR  *  )CONST_dlgTable_ABOUTBOX,							},
	{	IDD_filters,						(  TCHAR  *  )CONST_dlgTable_filters,							},
	{	IDD_qnmChkingStatus,				(  TCHAR  *  )CONST_dlgTable_qnmChkingStatus,  					},
	{	IDD_qwmCommStatus,					(  TCHAR  *  )CONST_dlgTable_qwmCommStatus,						},
	{	IDD_scanningIpStatus,				(  TCHAR  *  )CONST_dlgTable_scanningIpStatus,					},
	{	IDD_qyCommStatus,					(  TCHAR  *  )CONST_dlgTable_qyCommStatus,						},
	{	-1,						},
};

 QY_DMITEM  CONST_cusResTable_statusTool[]  =
{
 	{	CONST_resType_str,						(  TCHAR  *  )CONST_strTable_statusTool,						},
	{	CONST_resType_dlg,						(  TCHAR  *  )CONST_dlgTable_statusTool,						},
	{	CONST_resType_menu,						(  TCHAR  *  )CONST_nullTable,			},
	{	-1,		NULL,		},
};


