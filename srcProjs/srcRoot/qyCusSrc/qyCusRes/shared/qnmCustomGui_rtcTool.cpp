

#include	"stdafx.h"
#include	<tchar.h>
//  #include	"qyCommon.h"
#include	"afxres.h"
#include	"resource_rtcTool.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#if  0

 QY_DMITEM  CONST_strTable_rtcTool[]  =
{
	{	CONST_resId_null,						_T(  ""  ),				},

	{	IDOK,									CONST_str_disconnect,					},
	//  {	IDCANCEL,								CONST_str_CANCEL,					},
	//
	{	IDC_TUNING,								CONST_str_tuning,		},

	{	-1,		},

	
};


 QY_DMITEM  CONST_tableTable_rtcTool[]  =
{
	{ 	CONST_resId_qnmEventTypeTable0,			(  TCHAR  *  )CONST_qnmEventTypeTable0,				},
	{	CONST_resId_qnmEventTypeTable_pc,		(  TCHAR  *  )CONST_qnmEventTypeTable_netMc2,		},
	{	CONST_resId_qnmEventTypeTable_op,		(  TCHAR  *  )CONST_qnmEventTypeTable_op_netMc,			},
	{	CONST_resId_qnmEventTypeTable_netDev,	(  TCHAR  *  )CONST_qnmEventTypeTable_nmsNetDev,	},
	{	-1,		NULL,		},
};

  QY_DMITEM  CONST_dlgTable_qyRtcToolDialog[]	=
{
	{	IDOK,					},
	{	IDC_TUNING,				},
	{	-1,			},
};


 QY_DMITEM  CONST_dlgTable_rtcTool[]  =
{
	//  {	IDD_ABOUTBOX,						(  TCHAR  *  )CONST_dlgTable_ABOUTBOX,							},
	{	IDD_QYRTCTOOL_DIALOG,					(  TCHAR  *  )CONST_dlgTable_qyRtcToolDialog,							},
	{	-1,						},
};


 QY_DMITEM  CONST_cusResTable_rtcTool[]  =
{
 	{	CONST_resType_str,						(  TCHAR  *  )CONST_strTable_rtcTool,						},
	{	CONST_resType_dlg,						(  TCHAR  *  )CONST_dlgTable_rtcTool,						},
	{	CONST_resType_menu,						(  TCHAR  *  )CONST_nullTable,				},
	{	CONST_resType_table,					(  TCHAR  *  )CONST_tableTable_rtcTool,				},
	{	-1,		NULL,		},
};


#endif

