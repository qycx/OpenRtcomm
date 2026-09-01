
#include	"stdafx.h"
#include	<tchar.h>
//  #include	"qyCommon.h"
#include	"afxres.h"
#include	"resource_vDevComs.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_is.h"


 QY_DMITEM  CONST_strTable_vDevComs[]  =
{
	{	CONST_resId_null,						_T(  ""  ),					},

	//{	ID_qyTest,								_T(  "Test(&T)"  ),			},
	{	ID_qyConfig,							_T(  "Config(&C)"  ),		},
	//  {	ID_qyProperties,						CONST_str_qyProperties,		},
	{	IDD_qyTest,								_T(  "Test"  ),		},
		{	IDC_BUTTON_clear,						_T(  "Clear"  ),			},
		{	IDC_BUTTON_restart,						_T(  "Reset"  ),			},
		{	IDC_STATIC_input,						_T(  "Text:"  ),			},
		{	IDC_STATIC_countryCode,					_T(  "Country Code:"  ),		},
		{	IDC_STATIC_phoneNo,						_T(  "Phone:"  ),			},	
		{	IDC_BUTTON_sendToPhone,					_T(  "Send"  ),			},
		{	IDOK1,									CONST_str_OK,					},
	{	IDOK,									CONST_str_OK,					},
	{	IDCANCEL,								CONST_str_CANCEL,					},
	
	{	-1,		},

	
};


///////////////////////////////////


 QY_DMITEM  CONST_dlg_qyTest[]	=
{
	{	IDC_BUTTON_clear,		},
	{	IDC_BUTTON_restart,		},
	{	IDC_STATIC_input,		},
	{	IDC_STATIC_countryCode,	},
	{	IDC_STATIC_phoneNo,		},
	{	IDC_BUTTON_sendToPhone,	},
	{	IDOK1,					},
	{	IDCANCEL,				},
	{	-1,			},
};


 QY_DMITEM  CONST_dlgTable_vDevComs[]  =
{
	{	IDD_qyTest,					(  TCHAR  *  )CONST_dlg_qyTest,							},
	{	-1,						},
};

/////////////////////////////////////

  QY_DMITEM  CONST_popupMenuTable_vDevCom[]  =
{
	//{	ID_qyTest,			},
	//  {	-2,					},
	//  {	ID_qyConfig,		},
	{	-1,		NULL,	},
 };


  QY_DMITEM  CONST_popupMenuTable_vDevComs[]  =
{
	{	CONST_resId_popup_vDevCom,										0,		(  TCHAR  *  )CONST_popupMenuTable_vDevCom,			},									//  -0
	{	-1,			},
};



  QY_DMITEM  CONST_cusMenusTable_vDevComs[]  =
{
	{	CONST_resId_popupMenu,				(  TCHAR  *  )CONST_popupMenuTable_vDevComs,					},
	{	-1,		NULL,		},
};

/////////////////////////

 QY_DMITEM  CONST_tableTable_vDevComs[]  =
{
	{ 	CONST_resId_qnmEventTypeTable0,			(  TCHAR  *  )CONST_qnmEventTypeTable0_is,				},
	{	CONST_resId_qnmEventTypeTable_pc,		(  TCHAR  *  )CONST_qnmEventTypeTable_netMc2,		},
	{	CONST_resId_qnmEventTypeTable_op,		(  TCHAR  *  )CONST_qnmEventTypeTable_op_netMc,			},
	{	CONST_resId_qnmEventTypeTable_netDev,	(  TCHAR  *  )CONST_qnmEventTypeTable_nmsNetDev,	},
	{	-1,		NULL,		},
};


////

 QY_DMITEM  CONST_cusResTable_vDevComs[]  =
{
 	{	CONST_resType_str,						(  TCHAR  *  )CONST_strTable_vDevComs,						},
	{	CONST_resType_dlg,						(  TCHAR  *  )CONST_dlgTable_vDevComs,						},
	{	CONST_resType_menu,						(  TCHAR  *  )CONST_cusMenusTable_vDevComs,					},
	{	CONST_resType_table,					(  TCHAR  *  )CONST_tableTable_vDevComs,					},
	{	-1,		NULL,		},
};


