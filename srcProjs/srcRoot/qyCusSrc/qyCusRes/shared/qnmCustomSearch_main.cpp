
#include	"stdafx.h"
#include	<tchar.h>
#include	<commctrl.h>
//  #include	"qyCommon.h"
#include	"myresource_main.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
//
#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_netMc.h"


//  int  i  =  SQL_WCHAR;

/*
//  以下是的定制信息  {  
#if  DEFAULT_qyCustomId  ==  CONST_qyCustomId_shhg
 
//  主机列表查询条件定制
 QY_IDCITEM  CONST_shhgPcListSearchTable0[]  =
{
	{	IDC_STATIC_hint,	CONST_qyIdcType_static,  CONST_str_input,				0,	0,		NULL,					64,   29,  15,  64,  11,	0,															NULL,					_T(  "提示0"  ),			},
	{	IDC_STATIC0,		CONST_qyIdcType_static,  _T(  "用户类型:"  ),					0,	0,		NULL,					64,   22,  43,  47,  10,	0,															NULL,					_T(  "static用户类型"  ),	},
	{   IDC_COMBO0,			CONST_qyIdcType_combo,   CONST_yhlx_bdwyh,				0,	0,		CONST_shhgRegYhlxTable,	64,   70,  41,  64,  12,	0,															_T(  "qyPcRegInfoTab.col0"  ),	_T(  "用户类型"  ),			},
	{	IDC_STATIC1,		CONST_qyIdcType_static,  _T(  "临时用户单位:"  ),				0,	0,		NULL,					64,   147, 43,  57,  10,	CONST_qyIdcFlgHide,											NULL,					_T(  "static外单位名称"  ),	},
	{   IDC_EDIT0,			CONST_qyIdcType_edit,    NULL,							0,	0,		NULL,					64,   198, 41,  64,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgHide,				_T(  "qyPcRegInfoTab.col1"  ),	_T(  "外单位名称"  ),			},
	{	IDC_STATIC2,		CONST_qyIdcType_static,  _T(  "关(处)名:"  ),					0,	0,		NULL,					64,   22,  70,  47,  10,	0,															NULL,					_T(  "static关处名"  ),		},
	{   IDC_EDIT1,			CONST_qyIdcType_edit,    NULL,							0,	0,		NULL,					64,   70,  68,  64,  14,	CONST_qyIdcFlgPermitZw,										_T(  "qyPcRegInfoTab.col2"  ),	_T(  "关处名"  ),			},
	{	IDC_STATIC3,		CONST_qyIdcType_static,  _T(  "IP:"  ),							0,	0,		NULL,					64,   22,  96,  34,  14,	0,															NULL,					_T(  "staticIP"  ),			},
	{   IDC_IP,				CONST_qyIdcType_ip,		 NULL,							0,	0,		NULL,					64,   70,  96,  76,  14,	0,															_T(  "qyPcTab.ip"  ),			_T(  "IP"  ),				},
	{	IDC_STATIC4,		CONST_qyIdcType_static,  _T(  "MAC:"  ),						0,	0,		NULL,					64,   164, 96,  20,  14,	0,															NULL,					_T(  "static MAC"  ),		},
	{   IDC_EDIT_mac,		CONST_qyIdcType_edit,	 NULL,							0,	0,		NULL,					12,   207, 96,  64,  14,	CONST_qyIdcFlgPermitXdigit,									NULL,					_T(  "MAC"  ),				},
	{   IDC_EDIT_nDays,		CONST_qyIdcType_edit,	 NULL,							0,	0,		NULL,					64,   23,  124, 22,  14,	CONST_qyIdcFlgPermitDigit,									NULL,					_T(  "nDays"  ),			},
	{	IDC_STATIC_nDays,	CONST_qyIdcType_static,  CONST_str_tooLong,			0,	0,		NULL,					64,   58,  126, 94,  14,	0,															NULL,					_T(  "static nDays"  ),		},
	{	IDOK,				CONST_qyIdcType_button,	 CONST_str_OK,						0,	0,		NULL,					64,	  75,  160, 50,  14,	0,															NULL,					_T(  "IDOK"  ),				},
	{	IDCANCEL,			CONST_qyIdcType_button,	 CONST_str_CANCEL,						0,	0,		NULL,					64,	  180, 160, 50,  14,	0,															NULL,					_T(  "IDCANCEL"  ),			},
	{	-1,																																																													},
};

 QY_IDCITEM  CONST_shhgPcListSearchCb0Table0[]  =
{	
	{	IDC_STATIC1,		CONST_qyIdcType_static,  _T(  "临时用户单位:"  ),					0,	0,		NULL,					64,   147, 43,  57,  10,	CONST_qyIdcFlgHide,											NULL,					NULL,	},
	{   IDC_EDIT0,			CONST_qyIdcType_edit,    NULL,							0,	0,		NULL,					64,   198, 41,  64,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgHide,				_T(  "qyPcRegInfoTab.col1"  ),	NULL,	},
	{	-1,					NULL,		},
};

 QY_IDCITEM  CONST_shhgPcListSearchCb0Table1[]  =
{	
	{	IDC_STATIC1,		CONST_qyIdcType_static,  _T(  "临时用户单位:"  ),					0,	0,		NULL,					64,   147, 43,  57,  10,	0,															NULL,					NULL,	},
	{   IDC_EDIT0,			CONST_qyIdcType_edit,    NULL,							0,	0,		NULL,					64,   198, 41,  64,  14,	CONST_qyIdcFlgPermitAll,									_T(  "qyPcRegInfoTab.col1"  ),	NULL,	},
	{	-1,					NULL,		},
};

 //  事件列表查询条件定制
 QY_IDCITEM  CONST_shhgEventListSearchTable0[]  =
{
	{	IDC_STATIC_hint,		CONST_qyIdcType_static,  CONST_str_input,				0,	0,		NULL,						64,   29,  17,  64,  11,	0,														NULL,					_T(  "提示0"  ),			},
	{	IDC_STATIC_eventType,	CONST_qyIdcType_static,  CONST_str_eventType,					0,	0,		NULL,						64,   24,  38,  40,  14,	0,														NULL,					_T(  "static事件类型"  ),	},
	{   IDC_COMBO_eventType,	CONST_qyIdcType_combo,   _T(  ""  ),							0,	0,		CONST_qnmEventTypeTable,	64,   68,  40,  113, 12,	0,														NULL,					_T(  "事件类型"  ),			},
	{	IDC_STATIC0,			CONST_qyIdcType_static,  _T(  "用户类型:"  ),					0,	0,		NULL,						64,   24,  63,  50,  14,	0,														NULL,					_T(  "static用户类型"  ),	},
	{   IDC_COMBO0,				CONST_qyIdcType_combo,   _T(  ""  ),							0,	0,		CONST_shhgRegYhlxTable,		64,   68,  61,  64,  12,	0,														_T(  "qyPcEventTab.col0"  ),	_T(  "用户类型"  ),			},
	{	IDC_STATIC1,			CONST_qyIdcType_static,  _T(  "临时用户单位:"  ),				0,	0,		NULL,						64,   151, 63,  57,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgHide,			NULL,					_T(  "static外单位名称"  ),	},
	{   IDC_EDIT0,				CONST_qyIdcType_edit,    NULL,							0,	0,		NULL,						64,   204, 61,  64,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgHide,			_T(  "qyPcEventTab.col1"  ),	_T(  "外单位名称"  ),			},
	{	IDC_STATIC2,			CONST_qyIdcType_static,  _T(  "关(处)名:"  ),					0,	0,		NULL,						64,   24,  84,  40,  14,	0,														NULL,					_T(  "static关处名"  ),		},
	{   IDC_EDIT1,				CONST_qyIdcType_edit,    NULL,							0,	0,		NULL,						64,   68,  84,  64,  14,	CONST_qyIdcFlgPermitZw,									_T(  "qyPcEventTab.col2"  ),	_T(  "关处名"  ),			},
	{	IDC_STATIC3,			CONST_qyIdcType_static,  _T(  "IP:"  ),							0,	0,		NULL,						64,   24,  107, 34,  14,	0,														NULL,					_T(  "staticIP"  ),			},
	{   IDC_IP,					CONST_qyIdcType_ip,		 NULL,							0,	0,		NULL,						64,   68,  107, 76,  14,	0,														_T(  "qyPcEventTab.ip"  ),		_T(  "IP"  ),				},
	{	IDC_STATIC4,			CONST_qyIdcType_static,  _T(  "MAC:"  ),						0,	0,		NULL,						64,   163, 107, 20,  14,	0,														NULL,					_T(  "static MAC"  ),		},
	{   IDC_EDIT2,				CONST_qyIdcType_edit,	 NULL,							0,	0,		NULL,						12,   204, 107, 64,  14,	CONST_qyIdcFlgPermitXdigit,								_T(  "qyPcEventTab.mac0"  ),	_T(  "MAC"  ),				},
	{	IDC_STATIC5,			CONST_qyIdcType_static,  CONST_str_startTime,					0,	0,		NULL,						64,   24,  133, 40,  14,	0,														NULL,					_T(  "static start time"  ),		},
	{   IDC_STARTDATE,			CONST_qyIdcType_time,	 NULL,							0,	0,		NULL,						64,   68,  133, 65,  14,	0,														NULL,					_T(  "startDate"  ),			},
	{   IDC_STARTTIME,			CONST_qyIdcType_time,	 NULL,							0,	0,		NULL,						64,   149, 133, 52,  14,	0,														NULL,					_T(  "startTime"  ),			},
	{	IDC_STATIC6,			CONST_qyIdcType_static,  CONST_str_endTime,					0,	0,		NULL,						64,   24,  156, 40,  14,	0,														NULL,					_T(  "static end time"  ),		},
	{   IDC_ENDDATE,			CONST_qyIdcType_time,	 NULL,							0,	0,		NULL,						64,   68,  156, 65,  14,	0,														NULL,					_T(  "endDate"  ),			},
	{   IDC_ENDTIME,			CONST_qyIdcType_time,	 NULL,							0,	0,		NULL,						64,   150, 156, 52,  14,	0,														NULL,					_T(  "endTime"  ),			},
	{	IDOK,					CONST_qyIdcType_button,	 CONST_str_OK,						0,	0,		NULL,						64,	  71,  190, 50,  14,	0,														NULL,					_T(  "IDOK"  ),				},
	{	IDCANCEL,				CONST_qyIdcType_button,	 CONST_str_CANCEL,						0,	0,		NULL,						64,	  172, 190, 50,  14,	0,														NULL,					_T(  "IDCANCEL"  ),			},
	{	-1,					NULL,			},
};

 QY_IDCITEM  CONST_shhgEventListSearchCb0Table0[]  =
{	
	{	IDC_STATIC1,			CONST_qyIdcType_static,  _T(  "临时用户单位:"  ),				0,	0,		NULL,						64,   151, 63,  57,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgHide,			NULL,					_T(  "static外单位名称"  ),	},
	{   IDC_EDIT0,				CONST_qyIdcType_edit,    NULL,							0,	0,		NULL,						64,   204, 61,  64,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgHide,			_T(  "qyPcEventTab.col1"  ),	_T(  "外单位名称"  ),			},
	{	-1,						NULL,		},
};

 QY_IDCITEM  CONST_shhgEventListSearchCb0Table1[]  =
{	
	{	IDC_STATIC1,			CONST_qyIdcType_static,  _T(  "临时用户单位:"  ),				0,	0,		NULL,						64,   151, 63,  57,  14,	CONST_qyIdcFlgPermitZw,									NULL,					_T(  "static外单位名称"  ),	},
	{   IDC_EDIT0,				CONST_qyIdcType_edit,    NULL,							0,	0,		NULL,						64,   204, 61,  64,  14,	CONST_qyIdcFlgPermitZw,									_T(  "qyPcEventTab.col1"  ),	_T(  "外单位名称"  ),			},
	{	-1,						NULL,		},
};

QY_IDCITEM  *	gpPcListSearchTable0			=	CONST_shhgPcListSearchTable0;
QY_IDCITEM	*	gpPcListSearchCb0Tables[]		=	{	CONST_shhgPcListSearchCb0Table0,  CONST_shhgPcListSearchCb0Table1,  NULL,	};
QY_IDCITEM	*	gpPcListSearchCb1Tables[]		=	{	NULL,	};
QY_IDCITEM	*	gpEventListSearchTable0			=	CONST_shhgEventListSearchTable0;
QY_IDCITEM	*	gpEventListSearchCb0Tables[]	=	{	CONST_shhgEventListSearchCb0Table0,  CONST_shhgEventListSearchCb0Table1,  NULL,	};
QY_IDCITEM	*	gpEventListSearchCb1Tables[]	=	{	NULL,	};

#endif
//  }  以上是的定制信息
*/


//  以下是的定制信息  {
#if  DEFAULT_qyCustomId  ==  CONST_qyCustomId_zjga


	#ifndef  __OTHER__

		 #define		MACRO_zjgaEventSearchUsrPart_netMc2																																																																												\
							{	IDC_STATIC0,			CONST_qyIdcType_static,  CONST_str_depart,						0,	0,		NULL,						64,   24,  61,  40,  14,	0,																					NULL,							_T(  "static单位"  ),						},			\
							{   IDC_COMBO0,				CONST_qyIdcType_combo,   _T(  ""  ),							0,	0,		CONST_zjgaDwTable,			64,   68,  61,  64,  12,	CONST_qyIdcFlgPermitAll,							_T(  "qyPcEventTab.col2"  ),	_T(  "单位"  ),				SQL_WVARCHAR,	},			\
							{	IDC_STATIC1,			CONST_qyIdcType_static,  CONST_str_otherDepart,					0,	0,		NULL,						64,   151, 61,  50,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgHide,		NULL,							_T(  "static其它单位"  ),					},			\
							{   IDC_EDIT0,				CONST_qyIdcType_edit,    NULL,									0,	0,		NULL,						64,   204, 61,  64,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgHide,		_T(  "qyPcEventTab.col1"  ),	_T(  "其它单位"  ),			SQL_WVARCHAR,	},			\
							{	IDC_STATIC2,			CONST_qyIdcType_static,  CONST_str_unit,						0,	0,		NULL,						64,   24,  84,  40,  14,	0,													NULL,							_T(  "static科室"  ),						},			\
							{   IDC_EDIT1,				CONST_qyIdcType_edit,    NULL,									0,	0,		NULL,						64,   68,  84,  64,  14,	CONST_qyIdcFlgPermitAll,							_T(  "qyPcEventTab.col3"  ),	_T(  "科室"  ),				SQL_WVARCHAR,	},


		 #define		MACRO_zjgaEventSearchUsrPart_secChk																																																																												\
							{	IDC_STATIC0,			CONST_qyIdcType_static,  CONST_str_depart,						0,	0,		NULL,						64,   24,  61,  40,  14,	0,													NULL,							_T(  "static单位"  ),						},			\
							{   IDC_COMBO0,				CONST_qyIdcType_combo,   _T(  ""  ),							0,	0,		CONST_zjgaDwTable,			64,   68,  61,  64,  12,	CONST_qyIdcFlgPermitAll,							_T(  "qyPcRegInfoTab.col2"  ),	_T(  "单位"  ),				SQL_WVARCHAR,	},			\
							{	IDC_STATIC1,			CONST_qyIdcType_static,  CONST_str_otherDepart,					0,	0,		NULL,						64,   151, 61,  50,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgHide,		NULL,							_T(  "static其它单位"  ),					},			\
							{   IDC_EDIT0,				CONST_qyIdcType_edit,    NULL,									0,	0,		NULL,						64,   204, 61,  64,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgHide,		_T(  "qyPcRegInfoTab.col1"  ),	_T(  "其它单位"  ),			SQL_WVARCHAR,	},			\
							{	IDC_STATIC2,			CONST_qyIdcType_static,  CONST_str_unit,						0,	0,		NULL,						64,   24,  84,  40,  14,	0,													NULL,							_T(  "static科室"  ),						},			\
							{   IDC_EDIT1,				CONST_qyIdcType_edit,    NULL,									0,	0,		NULL,						64,   68,  84,  64,  14,	CONST_qyIdcFlgPermitAll,							_T(  "qyPcRegInfoTab.col3"  ),	_T(  "科室"  ),				SQL_WVARCHAR,	},
	#else
		 #define		MACRO_zjgaEventSearchUsrPart																																																																												\
							{	IDC_STATIC0,			CONST_qyIdcType_static,  CONST_str_depart,						0,	0,		NULL,						64,   163, 41,  40,  14,	CONST_qyIdcFlgPermitAll,							NULL,							_T(  "static单位"  ),						},			\
							{   IDC_EDIT3,				CONST_qyIdcType_edit,    _T(  ""  ),							0,	0,		NULL,						64,   204, 40,  64,  14,	CONST_qyIdcFlgPermitAll,							_T(  "qyPcEventTab.col2"  ),	_T(  "单位"  ),				SQL_WVARCHAR,	},			\
							{	IDC_STATIC2,			CONST_qyIdcType_static,  CONST_str_unit,						0,	0,		NULL,						64,   24,  61,  40,  14,	0,													NULL,							_T(  "static科室"  ),						},			\
							{   IDC_EDIT1,				CONST_qyIdcType_edit,    NULL,									0,	0,		NULL,						64,   72,  60,  64,  14,	CONST_qyIdcFlgPermitAll,							_T(  "qyPcEventTab.col3"  ),	_T(  "科室"  ),				SQL_WVARCHAR,	},			\
							{	IDC_STATIC8,			CONST_qyIdcType_static,  CONST_str_usr,							0,	0,		NULL,						64,   163, 61,  40,  14,	0,													NULL,							_T(  "static使用人"  ),						},			\
							{   IDC_EDIT5,				CONST_qyIdcType_edit,    NULL,									0,	0,		NULL,						64,   204, 60,  64,  14,	CONST_qyIdcFlgPermitAll,							_T(  "qyPcEventTab.col4"  ),	_T(  "使用人"  ),			SQL_WVARCHAR,	},


		 #define		MACRO_zjgaSecChkEventSearchUsrPart_netMc2																																																																												\
							{	IDC_STATIC0,			CONST_qyIdcType_static,  CONST_str_depart,						0,	0,		NULL,						64,   163, 41,  40,  14,	CONST_qyIdcFlgPermitAll,							NULL,							_T(  "static单位"  ),						},			\
							{   IDC_EDIT3,				CONST_qyIdcType_edit,    _T(  ""  ),							0,	0,		NULL,						64,   204, 40,  64,  14,	CONST_qyIdcFlgPermitAll,							_T(  "qyPcSecChkEventTab.col2"  ),	_T(  "单位"  ),				SQL_WVARCHAR,	},			\
							{	IDC_STATIC2,			CONST_qyIdcType_static,  CONST_str_unit,						0,	0,		NULL,						64,   24,  61,  40,  14,	0,													NULL,							_T(  "static科室"  ),						},			\
							{   IDC_EDIT1,				CONST_qyIdcType_edit,    NULL,									0,	0,		NULL,						64,   72,  60,  64,  14,	CONST_qyIdcFlgPermitAll,							_T(  "qyPcSecChkEventTab.col3"  ),	_T(  "科室"  ),				SQL_WVARCHAR,	},			\
							{	IDC_STATIC8,			CONST_qyIdcType_static,  CONST_str_usr,							0,	0,		NULL,						64,   163, 61,  40,  14,	0,													NULL,							_T(  "static使用人"  ),						},			\
							{   IDC_EDIT5,				CONST_qyIdcType_edit,    NULL,									0,	0,		NULL,						64,   204, 60,  64,  14,	CONST_qyIdcFlgPermitAll,							_T(  "qyPcSecChkEventTab.col4"  ),	_T(  "使用人"  ),			SQL_WVARCHAR,	},
    
		 #define		MACRO_zjgaSecChkEventSearchUsrPart_secChk																																																																												\
							{	IDC_STATIC0,			CONST_qyIdcType_static,  CONST_str_depart,						0,	0,		NULL,						64,   163, 41,  40,  14,	CONST_qyIdcFlgPermitAll,							NULL,							_T(  "static单位"  ),						},			\
							{   IDC_EDIT3,				CONST_qyIdcType_edit,    _T(  ""  ),							0,	0,		NULL,						64,   204, 40,  64,  14,	CONST_qyIdcFlgPermitAll,							_T(  "qyPcRegInfoTab.col2"  ),	_T(  "单位"  ),				SQL_WVARCHAR,	},			\
							{	IDC_STATIC2,			CONST_qyIdcType_static,  CONST_str_unit,						0,	0,		NULL,						64,   24,  61,  40,  14,	0,													NULL,							_T(  "static科室"  ),						},			\
							{   IDC_EDIT1,				CONST_qyIdcType_edit,    NULL,									0,	0,		NULL,						64,   72,  60,  64,  14,	CONST_qyIdcFlgPermitAll,							_T(  "qyPcRegInfoTab.col3"  ),	_T(  "科室"  ),				SQL_WVARCHAR,	},			\
							{	IDC_STATIC8,			CONST_qyIdcType_static,  CONST_str_usr,							0,	0,		NULL,						64,   163, 61,  40,  14,	0,													NULL,							_T(  "static使用人"  ),						},			\
							{   IDC_EDIT5,				CONST_qyIdcType_edit,    NULL,									0,	0,		NULL,						64,   204, 60,  64,  14,	CONST_qyIdcFlgPermitAll,							_T(  "qyPcRegInfoTab.col4"  ),	_T(  "使用人"  ),			SQL_WVARCHAR,	},


	#endif  __OTHER__
		
	#define			MACRO_zjgaEventSearchUsrPart_cb0																																																																						\
							{	IDC_STATIC1,			CONST_qyIdcType_static,  CONST_str_otherDepart,					0,	0,		NULL,						64,   151, 61,  50,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgHide,			NULL,							_T(  "static其它单位"  ),					},			\
							{   IDC_EDIT0,				CONST_qyIdcType_edit,    NULL,									0,	0,		NULL,						64,   204, 61,  64,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgHide,			_T(  "qyPcEventTab.col1"  ),	_T(  "其它单位"  ),			SQL_WVARCHAR,	},

	#define			MACRO_zjgaEventSearchUsrPart_cb1																																																																						\
							{	IDC_STATIC1,			CONST_qyIdcType_static,  CONST_str_otherDepart,					0,	0,		NULL,						64,   151, 61,  50,  14,	CONST_qyIdcFlgPermitZw,									NULL,							_T(  "static其它单位"  ),					},			\
							{   IDC_EDIT0,				CONST_qyIdcType_edit,    NULL,									0,	0,		NULL,						64,   204, 61,  64,  14,	CONST_qyIdcFlgPermitZw,									_T(  "qyPcEventTab.col1"  ),	_T(  "其它单位"  ),			SQL_WVARCHAR,	},


//  主机列表查询条件定制
 QY_IDCITEM  CONST_zjgaPcListSearchTable0[]  =
{
#if  0
	{	IDC_STATIC_hint,	CONST_qyIdcType_static, 	CONST_str_input,						0,	0,		NULL,					64,   29,  15,  64,  11,	0,													NULL,							_T(  "提示0"  ),								},
#ifndef  __OTHER__
	{	IDC_STATIC0,		CONST_qyIdcType_static, 	CONST_str_depart,						0,	0,		NULL,					64,   22,  43,  47,  10,	0,													NULL,							_T(  "static单位"  ),							},
	{   IDC_COMBO0,			CONST_qyIdcType_combo,		NULL,									0,	0,		CONST_zjgaDwTable,		64,   70,  41,  64,  12,	CONST_qyIdcFlgPermitAll,							_T(  "qyPcRegInfoTab.col2"  ),	_T(  "单位"  ),				SQL_WVARCHAR,		},
#else
	{	IDC_STATIC0,		CONST_qyIdcType_static, 	CONST_str_depart,						0,	0,		NULL,					64,   22,  43,  47,  10,	CONST_qyIdcFlgPermitAll,							NULL,							_T(  "static单位"  ),							},
	{   IDC_EDIT3,			CONST_qyIdcType_edit,		NULL,									0,	0,		NULL,					64,   70,  41,  64,  12,	CONST_qyIdcFlgPermitAll,							_T(  "qyPcRegInfoTab.col2"  ),	_T(  "单位"  ),				SQL_WVARCHAR,		},
#endif  __OTHER__
	{	IDC_STATIC1,		CONST_qyIdcType_static, 	CONST_str_otherDepart,					0,	0,		NULL,					64,   147, 43,  47,  10,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgHide,		NULL,							_T(  "static其它单位"  ),						},
	{   IDC_EDIT0,			CONST_qyIdcType_edit,		NULL,									0,	0,		NULL,					64,   198, 41,  64,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgHide,		_T(  "qyPcRegInfoTab.col1"  ),	_T(  "其它单位"  ),			SQL_WVARCHAR,		},
	{	IDC_STATIC2,		CONST_qyIdcType_static, 	CONST_str_unit,							0,	0,		NULL,					64,   22,  70,  47,  10,	0,													NULL,							_T(  "static科室"  ),							},
	{   IDC_EDIT1,			CONST_qyIdcType_edit,		NULL,									0,	0,		NULL,					64,   70,  68,  64,  14,	CONST_qyIdcFlgPermitAll,							_T(  "qyPcRegInfoTab.col3"  ),	_T(  "科室"  ),											SQL_WVARCHAR,		},
	{	IDC_STATIC5,		CONST_qyIdcType_static, 	CONST_str_usr,							0,	0,		NULL,					64,   164, 70,  47,  10,	0,													NULL,							_T(  "static syr"  ),							},
	{   IDC_EDIT4,			CONST_qyIdcType_edit,		NULL,									0,	0,		NULL,					64,   207, 68,  64,  14,	CONST_qyIdcFlgPermitAll,							_T(  "qyPcRegInfoTab.col4"  ),	_T(  "使用人"  ),			SQL_WVARCHAR,		},
	{	IDC_STATIC3,		CONST_qyIdcType_static, 	_T(  "IP:"  ),							0,	0,		NULL,					64,   22,  96,  34,  14,	0,													NULL,							_T(  "static IP"  ),							},
	{   IDC_IP,				CONST_qyIdcType_ip,			NULL,									0,	0,		NULL,					64,   70,  96,  86,  14,	0,													_T(  "qyPcTab.ip"  ),			_T(  "IP"  ),				SQL_VARCHAR,		},
	{	IDC_STATIC4,		CONST_qyIdcType_static, 	_T(  "MAC:"  ),							0,	0,		NULL,					64,   164, 96,  20,  14,	0,													NULL,							_T(  "static MAC"  ),							},
	{   IDC_EDIT2,			CONST_qyIdcType_edit,		NULL,									0,	0,		NULL,					12,   207, 96,  64,  14,	CONST_qyIdcFlgPermitXdigit,							_T(  "qyPcTab.mac0"  ),			_T(  "MAC"  ),				SQL_CHAR,			},
	{   IDC_EDIT_nDays,		CONST_qyIdcType_edit,		NULL,									0,	0,		NULL,					64,   23,  124, 22,  14,	CONST_qyIdcFlgPermitDigit,							NULL,							_T(  "nDays"  ),								},
	{	IDC_STATIC_nDays,	CONST_qyIdcType_static, 	CONST_str_tooLong,						0,	0,		NULL,					64,   58,  126, 94,  14,	0,													NULL,							_T(  "static nDays"  ),							},
	{	IDOK,				CONST_qyIdcType_button,		CONST_str_OK,							0,	0,		NULL,					64,	  75,  160, 50,  14,	0,													NULL,							_T(  "IDOK"  ),									},
	{	IDCANCEL,			CONST_qyIdcType_button,		CONST_str_CANCEL,						0,	0,		NULL,					64,	  180, 160, 50,  14,	0,													NULL,							_T(  "IDCANCEL"  ),								},
#endif 
//
	{	-1,																																																													},
};


 QY_IDCITEM  CONST_zjgaPcListSearchCb0Table0[]  =
{	
	{	IDC_STATIC1,		CONST_qyIdcType_static, 	CONST_str_otherDepart,					0,	0,		NULL,					64,   147, 43,  47,  10,	CONST_qyIdcFlgHide,																	NULL,							NULL,											},
	{   IDC_EDIT0,			CONST_qyIdcType_edit,		NULL,									0,	0,		NULL,					64,   198, 41,  64,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgHide,										_T(  "qyPcRegInfoTab.col1"  ),	NULL,						SQL_WVARCHAR,		},
	{	-1,					NULL,		},
};

 QY_IDCITEM  CONST_zjgaPcListSearchCb0Table1[]  =
{	
	{	IDC_STATIC1,		CONST_qyIdcType_static, 	CONST_str_otherDepart,					0,	0,		NULL,					64,   147, 43,  47,  10,	0,																					NULL,							NULL,											},
	{   IDC_EDIT0,			CONST_qyIdcType_edit,		NULL,									0,	0,		NULL,					64,   198, 41,  64,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgPermitDigit,								_T(  "qyPcRegInfoTab.col1"  ),	NULL,						SQL_WVARCHAR,		},
	{	-1,					NULL,		},
};

 //  事件列表查询条件定制
 QY_IDCITEM  CONST_zjgaEventListSearchTable0[]  =
{
#if  0
	{	IDC_STATIC_hint,		CONST_qyIdcType_static, 			CONST_str_input,					0,	0,		NULL,								64,   29,  17,  134,  11,	0,																												NULL,							_T(  "提示0"  ),												},
	{	IDC_STATIC_eventType,	CONST_qyIdcType_static,				CONST_str_eventType,				0,	0,		NULL,								64,   24,  38,  40,  14,	0,																												NULL,							_T(  "static事件类型"  ),										},
	{   IDC_COMBO_eventType,	CONST_qyIdcType_combo,				_T(  ""  ),							0,	0,		CONST_resId_qnmEventTypeTable_pc,	64,   72,  40,  84,  12,	CONST_qyIdcFlgAddNullItem,																						NULL,							_T(  "事件类型"  ),							SQL_INTEGER,		},
	MACRO_zjgaEventSearchUsrPart
	{	IDC_STATIC3,			CONST_qyIdcType_static, 		_T(  "IP:"  ),							0,	0,		NULL,								64,   24,  81,	34,  14,	0,																														NULL,							_T(  "staticIP"  ),												},
	{   IDC_IP,					CONST_qyIdcType_ip,				NULL,									0,	0,		NULL,								64,   72,  80,	88,  14,	0,																														_T(  "qyPcEventTab.ip"  ),		_T(  "IP"  ),								SQL_VARCHAR,		},
	{	IDC_STATIC4,			CONST_qyIdcType_static, 		_T(  "MAC:"  ),							0,	0,		NULL,								64,   167, 81,	20,  14,	0,																														NULL,							_T(  "static MAC"  ),											},
	{   IDC_EDIT2,				CONST_qyIdcType_edit,			NULL,									0,	0,		NULL,								12,   208, 80,	64,  14,	CONST_qyIdcFlgPermitXdigit,																								_T(  "qyPcEventTab.mac0"  ),	_T(  "MAC"  ),								SQL_CHAR,			},
	{	IDC_STATIC7,			CONST_qyIdcType_static, 		CONST_str_likeSearch,					0,	0,		NULL,								64,   24,  107, 40,  14,	0,																														NULL,							_T(  "static模糊查询"  ),										},
	{   IDC_EDIT4,				CONST_qyIdcType_edit,			NULL,									0,	0,		NULL,								64,   72,  107, 122, 14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgSearchUsingLike,	_T(  "qyPcEventTab.des0"  ),	CONST_str_likeSearch/*_T(  "模糊查询"  )*/,	SQL_WVARCHAR,		},
	{	IDC_STATIC5,			CONST_qyIdcType_static, 			CONST_str_startTime,				0,	0,		NULL,								64,   24,  133, 40,  14,	0,																														NULL,							_T(  "static start time"  ),									},
	{   IDC_STARTDATE,			CONST_qyIdcType_time,				NULL,								0,	0,		NULL,								64,   72,  133, 65,  14,	0,																														NULL,							_T(  "startDate"  ),											},
	{   IDC_STARTTIME,			CONST_qyIdcType_time,				NULL,								0,	0,		NULL,								64,   153, 133, 52,  14,	0,																														NULL,							_T(  "startTime"  ),											},
	{	IDC_STATIC6,			CONST_qyIdcType_static, 			CONST_str_endTime,					0,	0,		NULL,								64,   24,  156, 40,  14,	0,																														NULL,							_T(  "static end time"  ),										},
	{   IDC_ENDDATE,			CONST_qyIdcType_time,				NULL,								0,	0,		NULL,								64,   72,  156, 65,  14,	0,																														NULL,							_T(  "endDate"  ),												},
	{   IDC_ENDTIME,			CONST_qyIdcType_time,				NULL,								0,	0,		NULL,								64,   154, 156, 52,  14,	0,																														NULL,							_T(  "endTime"  ),												},
	{	IDOK,					CONST_qyIdcType_button,				CONST_str_OK,						0,	0,		NULL,								64,	  71,  190, 50,  14,	0,																														NULL,							_T(  "IDOK"  ),													},
	{	IDCANCEL,				CONST_qyIdcType_button,				CONST_str_CANCEL,					0,	0,		NULL,								64,	  172, 190, 50,  14,	0,																														NULL,							_T(  "IDCANCEL"  ),												},
#endif

	{	-1,						NULL,			},
};

 QY_IDCITEM  CONST_zjgaEventListSearchCb0Table0[]  =
{	
	//  {	IDC_STATIC1,			CONST_qyIdcType_static, 		CONST_str_otherDepart,					0,	0,		NULL,						64,   151, 61,  50,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgHide,			NULL,					_T(  "static其它单位"  ),	},
	//  {   IDC_EDIT0,				CONST_qyIdcType_edit,			NULL,									0,	0,		NULL,						64,   204, 61,  64,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgHide,			_T(  "qyPcEventTab.col1"  ),	_T(  "其它单位"  ),			},
	MACRO_zjgaEventSearchUsrPart_cb0
	{	-1,						NULL,		},
};

 QY_IDCITEM  CONST_zjgaEventListSearchCb0Table1[]  =
{	
	//  {	IDC_STATIC1,			CONST_qyIdcType_static, 		CONST_str_otherDepart,					0,	0,		NULL,						64,   151, 61,  50,  14,	CONST_qyIdcFlgPermitZw,									NULL,					_T(  "static其它单位"  ),	},
	//  {   IDC_EDIT0,				CONST_qyIdcType_edit,			NULL,									0,	0,		NULL,						64,   204, 61,  64,  14,	CONST_qyIdcFlgPermitZw,									_T(  "qyPcEventTab.col1"  ),	_T(  "其它单位"  ),			},
	MACRO_zjgaEventSearchUsrPart_cb1
	{	-1,						NULL,		},
};

  //  网络事件列表查询条件定制
 QY_IDCITEM  CONST_zjgaNetDevEventListSearchTable0[]  =
{
	{	IDC_STATIC_hint,		CONST_qyIdcType_static, 	CONST_str_input,				0,	0,		NULL,									64,   29,  17,  64,  11,	0,																					NULL,					_T(  "提示0"  ),			},
	{	IDC_STATIC_eventType,	CONST_qyIdcType_static, 	CONST_str_eventType,					0,	0,		NULL,									64,   24,  38,  40,  14,	0,																					NULL,					_T(  "static事件类型"  ),	},
	{   IDC_COMBO_eventType,	CONST_qyIdcType_combo,  	_T(  ""  ),								0,	0,		CONST_resId_qnmEventTypeTable_netDev,	64,   68,  40,  64,  12,	CONST_qyIdcFlgAddNullItem,															NULL,					_T(  "事件类型"  ),			},
	{	IDC_STATIC3,			CONST_qyIdcType_static, 	_T(  "IP:"  ),							0,	0,		NULL,									64,   24,  107, 34,  14,	0,																					NULL,					_T(  "staticIP"  ),			},
	{   IDC_IP,					CONST_qyIdcType_ip,			NULL,									0,	0,		NULL,									64,   68,  107, 86,  14,	0,																					_T(  "qyPcEventTab.ip"  ),		_T(  "IP"  ),				},
	{	IDC_STATIC4,			CONST_qyIdcType_static, 	_T(  "MAC:"  ),							0,	0,		NULL,									64,   163, 107, 20,  14,	0,																					NULL,					_T(  "static MAC"  ),		},
	{   IDC_EDIT2,				CONST_qyIdcType_edit,		NULL,									0,	0,		NULL,									12,   204, 107, 64,  14,	CONST_qyIdcFlgPermitXdigit,															_T(  "qyPcEventTab.mac0"  ),	_T(  "MAC"  ),				},
	{	IDC_STATIC5,			CONST_qyIdcType_static, 	CONST_str_startTime,					0,	0,		NULL,									64,   24,  133, 40,  14,	0,																					NULL,					_T(  "static start time"  ),		},
	{   IDC_STARTDATE,			CONST_qyIdcType_time,		NULL,									0,	0,		NULL,									64,   68,  133, 65,  14,	0,																					NULL,					_T(  "startDate"  ),			},
	{   IDC_STARTTIME,			CONST_qyIdcType_time,		NULL,									0,	0,		NULL,									64,   149, 133, 52,  14,	0,																					NULL,					_T(  "startTime"  ),			},
	{	IDC_STATIC6,			CONST_qyIdcType_static, 	CONST_str_endTime,					0,	0,		NULL,									64,   24,  156, 40,  14,	0,																					NULL,					_T(  "static end time"  ),		},
	{   IDC_ENDDATE,			CONST_qyIdcType_time,		NULL,									0,	0,		NULL,									64,   68,  156, 65,  14,	0,																					NULL,					_T(  "endDate"  ),			},
	{   IDC_ENDTIME,			CONST_qyIdcType_time,		NULL,									0,	0,		NULL,									64,   150, 156, 52,  14,	0,																					NULL,					_T(  "endTime"  ),			},
	{	IDOK,					CONST_qyIdcType_button,		CONST_str_OK,							0,	0,		NULL,									64,	  71,  190, 50,  14,	0,																					NULL,					_T(  "IDOK"  ),				},
	{	IDCANCEL,				CONST_qyIdcType_button,		CONST_str_CANCEL,							0,	0,		NULL,									64,	  172, 190, 50,  14,	0,																					NULL,					_T(  "IDCANCEL"  ),			},
	{	-1,						NULL,			},
};


 //  2006/02/25, 系统事件列表查询条件定制
 QY_IDCITEM  CONST_zjgaOpEventListSearchTable0[]  =
{
	{	IDC_STATIC_hint,		CONST_qyIdcType_static, 			CONST_str_input,		0,	0,		NULL,								64,   29,  17,  134,  11,	0,																					NULL,					_T(  "提示0"  ),			},
	{	IDC_STATIC_eventType,	CONST_qyIdcType_static,				CONST_str_eventType,	0,	0,		NULL,								64,   24,  38,  44,  14,	0,																					NULL,					_T(  "static事件类型"  ),	},
	{   IDC_COMBO_eventType,	CONST_qyIdcType_combo,				_T(  ""  ),				0,	0,		CONST_resId_qnmEventTypeTable_op,	64,   78,  40,  134,  12,	CONST_qyIdcFlgAddNullItem,															NULL,					_T(  "事件类型"  ),			},
	{	IDC_STATIC5,			CONST_qyIdcType_static, 			CONST_str_startTime,	0,	0,		NULL,								64,   24,  133, 44,  14,	0,																					NULL,					_T(  "static start time"  ),		},
	{   IDC_STARTDATE,			CONST_qyIdcType_time,				NULL,					0,	0,		NULL,								64,   78,  133, 65,  14,	0,																					NULL,					_T(  "startDate"  ),			},
	{   IDC_STARTTIME,			CONST_qyIdcType_time,				NULL,					0,	0,		NULL,								64,   159, 133, 52,  14,	0,																					NULL,					_T(  "startTime"  ),			},
	{	IDC_STATIC6,			CONST_qyIdcType_static, 			CONST_str_endTime,		0,	0,		NULL,								64,   24,  156, 44,  14,	0,																					NULL,					_T(  "static end time"  ),		},
	{   IDC_ENDDATE,			CONST_qyIdcType_time,				NULL,					0,	0,		NULL,								64,   78,  156, 65,  14,	0,																					NULL,					_T(  "endDate"  ),			},
	{   IDC_ENDTIME,			CONST_qyIdcType_time,				NULL,					0,	0,		NULL,								64,   160, 156, 52,  14,	0,																					NULL,					_T(  "endTime"  ),			},
	{	IDOK,					CONST_qyIdcType_button,				CONST_str_OK,			0,	0,		NULL,								64,	  71,  190, 50,  14,	0,																					NULL,					_T(  "IDOK"  ),				},
	{	IDCANCEL,				CONST_qyIdcType_button,				CONST_str_CANCEL,		0,	0,		NULL,								64,	  172, 190, 50,  14,	0,																					NULL,					_T(  "IDCANCEL"  ),			},
	{	-1,						NULL,			},
};



  //  安检结果查询条件定制
 QY_IDCITEM  CONST_zjgaSecChkEventListSearchTable0_netMc2[]  =
{
#if  0
	{	IDC_STATIC_hint,		CONST_qyIdcType_static, 			CONST_str_input,						0,	0,		NULL,								64,   29,  17,  64,  11,	0,																												NULL,							_T(  "提示0"  ),												},
	{	IDC_STATIC_eventType,	CONST_qyIdcType_static,				CONST_str_eventType,					0,	0,		NULL,								64,   24,  38,  40,  14,	0,																												NULL,							_T(  "static事件类型"  ),										},
	{   IDC_COMBO_eventType,	CONST_qyIdcType_combo,				_T(  ""  ),								0,	0,		CONST_resId_secChkEventTypeTable,	64,   68,  40,  64,  12,	CONST_qyIdcFlgAddNullItem,																						NULL,							_T(  "事件类型"  ),							SQL_INTEGER,		},
	//  #ifndef  __OTHER__
		//  {	IDC_STATIC0,			CONST_qyIdcType_static, 	CONST_str_depart,						0,	0,		NULL,						64,   24,  61,  40,  14,	0,																														NULL,							_T(  "static单位"  ),											},
		//  {   IDC_COMBO0,				CONST_qyIdcType_combo,  	_T(  ""  ),								0,	0,		CONST_zjgaDwTable,			64,   68,  61,  64,  12,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitAlpha,										_T(  "qyPcSecChkEventTab.col2"  ),	_T(  "单位"  ),								SQL_WVARCHAR,		},
		//  {	IDC_STATIC1,			CONST_qyIdcType_static, 	CONST_str_otherDepart,					0,	0,		NULL,						64,   151, 61,  50,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgHide,																			NULL,							_T(  "static其它单位"  ),										},
		//  {   IDC_EDIT0,				CONST_qyIdcType_edit,		NULL,									0,	0,		NULL,						64,   204, 61,  64,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgHide,											_T(  "qyPcSecChkEventTab.col1"  ),	_T(  "其它单位"  ),							SQL_WVARCHAR,		},
	//  #else
		//  {	IDC_STATIC0,			CONST_qyIdcType_static, 	CONST_str_depart,						0,	0,		NULL,						64,   24,  61,  40,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitAlpha,										NULL,							_T(  "static单位"  ),											},
		//  {   IDC_EDIT3,				CONST_qyIdcType_edit,   	_T(  ""  ),								0,	0,		NULL,						64,   68,  61,  64,  12,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitAlpha,										_T(  "qyPcSecChkEventTab.col2"  ),	_T(  "单位"  ),								SQL_WVARCHAR,		},
	//  #endif  __OTHER__
	//  {	IDC_STATIC2,			CONST_qyIdcType_static, 		CONST_str_unit,							0,	0,		NULL,						64,   24,  84,  40,  14,	0,																														NULL,							_T(  "static科室"  ),											},
	//  {   IDC_EDIT1,				CONST_qyIdcType_edit,			NULL,									0,	0,		NULL,						64,   68,  84,  64,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitAlpha,										_T(  "qyPcSecChkEventTab.col3"  ),	_T(  "科室"  ),								SQL_WVARCHAR,		},
	//
	//  #if		qyGetSystemId(  )  ==  CONST_qySystemId_netMc2
		MACRO_zjgaSecChkEventSearchUsrPart_netMc2
		{	IDC_STATIC3,			CONST_qyIdcType_static, 		_T(  "IP:"  ),							0,	0,		NULL,						64,   24,  81,	34,  14,	0,																														NULL,							_T(  "staticIP"  ),												},
		{   IDC_IP,					CONST_qyIdcType_ip,				NULL,									0,	0,		NULL,						64,   68,  80,	88,  14,	0,																														_T(  "qyPcSecChkEventTab.ip"  ),_T(  "IP"  ),								SQL_VARCHAR,		},
		{	IDC_STATIC4,			CONST_qyIdcType_static, 		_T(  "MAC:"  ),							0,	0,		NULL,						64,   163, 81,	20,  14,	0,																														NULL,							_T(  "static MAC"  ),											},
		{   IDC_EDIT2,				CONST_qyIdcType_edit,			NULL,									0,	0,		NULL,						12,   204, 80,	64,  14,	CONST_qyIdcFlgPermitXdigit,																								_T(  "qyPcSecChkEventTab.mac0"  ),	_T(  "MAC"  ),								SQL_CHAR,			},
		{	IDC_STATIC7,			CONST_qyIdcType_static, 		CONST_str_likeSearch,					0,	0,		NULL,						64,   24,  107, 40,  14,	0,																														NULL,							_T(  "static模糊查询"  ),										},
		{   IDC_EDIT4,				CONST_qyIdcType_edit,			NULL,									0,	0,		NULL,						64,   68,  107, 122,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgSearchUsingLike,	_T(  "qyPcSecChkEventTab.des0"  ),	CONST_str_likeSearch/*_T(  "模糊查询"  )*/,	SQL_WVARCHAR,		},
	//  #endif
	//
	{	IDC_STATIC5,			CONST_qyIdcType_static, 			CONST_str_startTime,					0,	0,		NULL,						64,   24,  133, 40,  14,	0,																														NULL,							_T(  "static start time"  ),									},
	{   IDC_STARTDATE,			CONST_qyIdcType_time,				NULL,									0,	0,		NULL,						64,   68,  133, 65,  14,	0,																														NULL,							_T(  "startDate"  ),											},
	{   IDC_STARTTIME,			CONST_qyIdcType_time,				NULL,									0,	0,		NULL,						64,   149, 133, 52,  14,	0,																														NULL,							_T(  "startTime"  ),											},
	{	IDC_STATIC6,			CONST_qyIdcType_static, 			CONST_str_endTime,						0,	0,		NULL,						64,   24,  156, 40,  14,	0,																														NULL,							_T(  "static end time"  ),										},
	{   IDC_ENDDATE,			CONST_qyIdcType_time,				NULL,									0,	0,		NULL,						64,   68,  156, 65,  14,	0,																														NULL,							_T(  "endDate"  ),												},
	{   IDC_ENDTIME,			CONST_qyIdcType_time,				NULL,									0,	0,		NULL,						64,   150, 156, 52,  14,	0,																														NULL,							_T(  "endTime"  ),												},
	{	IDOK,					CONST_qyIdcType_button,				CONST_str_OK,							0,	0,		NULL,						64,	  71,  190, 50,  14,	0,																														NULL,							_T(  "IDOK"  ),													},
	{	IDCANCEL,				CONST_qyIdcType_button,				CONST_str_CANCEL,						0,	0,		NULL,						64,	  172, 190, 50,  14,	0,																														NULL,							_T(  "IDCANCEL"  ),												},
#endif 
	 //
	{	-1,						NULL,			},
};

  //  安检结果查询条件定制
 QY_IDCITEM  CONST_zjgaSecChkEventListSearchTable0_secChk[]  =
{
#if  0
	{	IDC_STATIC_hint,		CONST_qyIdcType_static, 			CONST_str_input,						0,	0,		NULL,								64,   29,  17,  64,  11,	0,																												NULL,							_T(  "提示0"  ),												},
	{	IDC_STATIC_eventType,	CONST_qyIdcType_static,				CONST_str_eventType,					0,	0,		NULL,								64,   24,  38,  40,  14,	0,																												NULL,							_T(  "static事件类型"  ),										},
	{   IDC_COMBO_eventType,	CONST_qyIdcType_combo,				_T(  ""  ),								0,	0,		CONST_resId_secChkEventTypeTable,	64,   68,  40,  64,  12,	CONST_qyIdcFlgAddNullItem,																						NULL,							_T(  "事件类型"  ),							SQL_INTEGER,		},
	//  #ifndef  __OTHER__
		//  {	IDC_STATIC0,			CONST_qyIdcType_static, 	CONST_str_depart,						0,	0,		NULL,						64,   24,  61,  40,  14,	0,																														NULL,							_T(  "static单位"  ),											},
		//  {   IDC_COMBO0,				CONST_qyIdcType_combo,  	_T(  ""  ),								0,	0,		CONST_zjgaDwTable,			64,   68,  61,  64,  12,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitAlpha,										_T(  "qyPcSecChkEventTab.col2"  ),	_T(  "单位"  ),								SQL_WVARCHAR,		},
		//  {	IDC_STATIC1,			CONST_qyIdcType_static, 	CONST_str_otherDepart,					0,	0,		NULL,						64,   151, 61,  50,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgHide,																			NULL,							_T(  "static其它单位"  ),										},
		//  {   IDC_EDIT0,				CONST_qyIdcType_edit,		NULL,									0,	0,		NULL,						64,   204, 61,  64,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgHide,											_T(  "qyPcSecChkEventTab.col1"  ),	_T(  "其它单位"  ),							SQL_WVARCHAR,		},
	//  #else
		//  {	IDC_STATIC0,			CONST_qyIdcType_static, 	CONST_str_depart,						0,	0,		NULL,						64,   24,  61,  40,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitAlpha,										NULL,							_T(  "static单位"  ),											},
		//  {   IDC_EDIT3,				CONST_qyIdcType_edit,   	_T(  ""  ),								0,	0,		NULL,						64,   68,  61,  64,  12,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitAlpha,										_T(  "qyPcSecChkEventTab.col2"  ),	_T(  "单位"  ),								SQL_WVARCHAR,		},
	//  #endif  __OTHER__
	//  {	IDC_STATIC2,			CONST_qyIdcType_static, 		CONST_str_unit,							0,	0,		NULL,						64,   24,  84,  40,  14,	0,																														NULL,							_T(  "static科室"  ),											},
	//  {   IDC_EDIT1,				CONST_qyIdcType_edit,			NULL,									0,	0,		NULL,						64,   68,  84,  64,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitAlpha,										_T(  "qyPcSecChkEventTab.col3"  ),	_T(  "科室"  ),								SQL_WVARCHAR,		},
	//
	//  #if		qyGetSystemId(  )  ==  CONST_qySystemId_secChk
		//  {	IDC_STATIC0,			CONST_qyIdcType_static, 	CONST_str_depart,						0,	0,		NULL,						64,   24,  61,  40,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitAlpha,										NULL,							_T(  "static单位"  ),											},
		//  {   IDC_EDIT3,				CONST_qyIdcType_edit,   	_T(  ""  ),								0,	0,		NULL,						64,   68,  61,  64,  12,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitAlpha,										_T(  "qyPcSecChkEventTab.col2"  ),	_T(  "单位"  ),								SQL_WVARCHAR,		},
		//  {	IDC_STATIC2,			CONST_qyIdcType_static, 	CONST_str_unit,							0,	0,		NULL,						64,   163, 61,  40,  14,	0,																														NULL,							_T(  "static科室"  ),											},
		//  {   IDC_EDIT1,				CONST_qyIdcType_edit,		NULL,									0,	0,		NULL,						64,   204, 61,  64,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitAlpha,										_T(  "qyPcSecChkEventTab.col3"  ),	_T(  "科室"  ),								SQL_WVARCHAR,		},
		MACRO_zjgaSecChkEventSearchUsrPart_secChk
		{	IDC_STATIC3,			CONST_qyIdcType_static, 		_T(  "IP:"  ),							0,	0,		NULL,						64,   24,  81,	34,  14,	0,																														NULL,							_T(  "staticIP"  ),												},
		{   IDC_IP,					CONST_qyIdcType_ip,				NULL,									0,	0,		NULL,						64,   68,  80,	88,  14,	0,																														_T(  "qyPcSecChkEventTab.ip"  ),_T(  "IP"  ),								SQL_VARCHAR,		},
		{	IDC_STATIC4,			CONST_qyIdcType_static, 		_T(  "MAC:"  ),							0,	0,		NULL,						64,   163, 81,	20,  14,	0,																														NULL,							_T(  "static MAC"  ),											},
		{   IDC_EDIT2,				CONST_qyIdcType_edit,			NULL,									0,	0,		NULL,						12,   204, 80,	64,  14,	CONST_qyIdcFlgPermitXdigit,																								_T(  "qyPcSecChkEventTab.mac0"  ),	_T(  "MAC"  ),								SQL_CHAR,			},
		{	IDC_STATIC7,			CONST_qyIdcType_static, 		CONST_str_likeSearch,					0,	0,		NULL,						64,   24,  107, 40,  14,	0,																														NULL,							_T(  "static模糊查询"  ),										},
		{   IDC_EDIT4,				CONST_qyIdcType_edit,			NULL,									0,	0,		NULL,						64,   68,  107, 122,  14,	CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgSearchUsingLike,	_T(  "qyPcSecChkEventTab.des0"  ),	CONST_str_likeSearch/*_T(  "模糊查询"  )*/,	SQL_WVARCHAR,		},
	//  #endif
	{	IDC_STATIC5,			CONST_qyIdcType_static, 			CONST_str_startTime,					0,	0,		NULL,						64,   24,  133, 40,  14,	0,																														NULL,							_T(  "static start time"  ),									},
	{   IDC_STARTDATE,			CONST_qyIdcType_time,				NULL,									0,	0,		NULL,						64,   68,  133, 65,  14,	0,																														NULL,							_T(  "startDate"  ),											},
	{   IDC_STARTTIME,			CONST_qyIdcType_time,				NULL,									0,	0,		NULL,						64,   149, 133, 52,  14,	0,																														NULL,							_T(  "startTime"  ),											},
	{	IDC_STATIC6,			CONST_qyIdcType_static, 			CONST_str_endTime,						0,	0,		NULL,						64,   24,  156, 40,  14,	0,																														NULL,							_T(  "static end time"  ),										},
	{   IDC_ENDDATE,			CONST_qyIdcType_time,				NULL,									0,	0,		NULL,						64,   68,  156, 65,  14,	0,																														NULL,							_T(  "endDate"  ),												},
	{   IDC_ENDTIME,			CONST_qyIdcType_time,				NULL,									0,	0,		NULL,						64,   150, 156, 52,  14,	0,																														NULL,							_T(  "endTime"  ),												},
	{	IDOK,					CONST_qyIdcType_button,				CONST_str_OK,							0,	0,		NULL,						64,	  71,  190, 50,  14,	0,																														NULL,							_T(  "IDOK"  ),													},
	{	IDCANCEL,				CONST_qyIdcType_button,				CONST_str_CANCEL,						0,	0,		NULL,						64,	  172, 190, 50,  14,	0,																														NULL,							_T(  "IDCANCEL"  ),												},
#endif 

	{	-1,						NULL,			},
};

////统计
////////////////////  2008/12/19
 QY_IDCITEM	 CONST_statIpScanTable0[]  =
{
	{	IDC_STATIC0,		CONST_qyIdcType_static,		CONST_str_according,					0,	0,		NULL,					64,   41,  36,  12,  11,	0,															NULL,					_T(  "static"  ),			},
	{   IDC_COMBO0,			CONST_qyIdcType_comboDesc,	_T(  "单位"  ) /*  CONST_ipScanOfficeLevelTable[0].des  */,	0,	0,		CONST_resId_ipScanOfficeLevelTable,	64,   65,  34,  52,  12,	0,							NULL,					_T(  "分组级别"  ),			},
	{	IDC_STATIC1,		CONST_qyIdcType_static,		CONST_str_contentOfStat,				0,	0,		NULL,					64,   20,  60,  38,  14,	0,															NULL,					_T(  "static统计内容"  ),	},
	{   IDC_CHECK_ip,		CONST_qyIdcType_chk,		CONST_str_detectedIp,					0,	0,		NULL,					1,	  65,  60,  72,  14,	0,															NULL,					_T(  "ip"  ),				},
	{	-1,					NULL,		},
};

 QY_IDCITEM  CONST_zjgaStatPcInfoTable0[]  =
{
#if  0
	{	IDC_STATIC0,		CONST_qyIdcType_static,		CONST_str_userType,						0,  0,		NULL,					64,	  20,  31,  42,  14,	CONST_qyIdcFlgHide,											NULL,					_T(  "static用户类型"  ),	},
	{	IDC_COMBO0,			CONST_qyIdcType_combo,		0/*CONST_zjgaYhlxTable[0].des*/,		0,	0,		CONST_resId_zjgaYhlxTable,	64,	  65,  31,  69,  12,	CONST_qyIdcFlgHide,										_T(  "qyPcRegInfoTab.col0"  ),	_T(  "用户类型"  ),	},
	{	IDC_STATIC1,		CONST_qyIdcType_static,		CONST_str_according,					0,	0,		NULL,					64,	  41,  52,  14,  13,	0,															NULL,					_T(  "static按"  ),			},
	{	IDC_COMBO1,			CONST_qyIdcType_comboDesc,	0/*gYhGrpTable[0].des*/,				0,	0,		CONST_resId_gYhGrpTable,	64,	  65,  53,  69,  12,	0,														NULL,					_T(  "统计分组单位"  ),		},
	{	IDC_COMBO2,			CONST_qyIdcType_comboDesc,	NULL,									0,	0,		NULL,					64,	  65,  53,  69,  12,	CONST_qyIdcFlgHide,											NULL,					_T(  "统计分组单位"  ),		},
	{	IDC_STATIC2,		CONST_qyIdcType_static,		CONST_str_contentOfStat,				0,	0,		NULL,					64,	  17,  73,  40,  14,	0,															NULL,					_T(  "static统计内容"  ),	},
	{	IDC_CHECK_pc,		CONST_qyIdcType_chk,		CONST_str_pcCount,						0,	0,		CONST_resId_qyNullTable,		1,	  65,  73,  72,  14,	0,													NULL,					_T(  "计算机数"  ),			},
	{	IDC_CHECK_os,		CONST_qyIdcType_chk,		CONST_str_caoZuoXiTong,					0,	0,		NULL,					0,	  65,  90,  72,  14,	0,															NULL,					_T(  "操作系统"  ),			},
	{	IDC_CHECK_mac,		CONST_qyIdcType_chk,		CONST_str_wangKa,						0,	0,		NULL,					0,	  65,  107, 72,  14,	0,															NULL,					_T(  "网卡"  ),				},
#endif 
	//
	{	-1,					NULL,										},
};

 QY_IDCITEM  CONST_zjgaStatPcInfoCb0Table0[]  =
{
	{	IDC_COMBO1,			CONST_qyIdcType_comboDesc,	0/*gYhGrpTable[0].des*/,				0,	0,		CONST_resId_gYhGrpTable,	64,	  65,  53,  69,  12,	0,															NULL,					_T(  "统计分组单位"  ),		},
	{	IDC_COMBO2,			CONST_qyIdcType_comboDesc,	NULL,									0,	0,		NULL,					64,	  65,  53,  69,  12,	CONST_qyIdcFlgHide,											NULL,					_T(  "统计分组单位"  ),		},
	{	-1,					NULL,																			},
};

 QY_IDCITEM  CONST_zjgaStatPcInfoCb0Table1[]  =
{
	{	IDC_COMBO1,			CONST_qyIdcType_comboDesc,	0/*gYhGrpTable[0].des*/,				0,	0,		CONST_resId_gYhGrpTable,	64,	  65,  53,  69,  12,	CONST_qyIdcFlgHide,											NULL,					_T(  "统计分组单位"  ),		},
	{	IDC_COMBO2,			CONST_qyIdcType_comboDesc,	NULL,									0,	0,		NULL,					64,	  65,  53,  69,  12,	0,															NULL,					_T(  "统计分组单位"  ),		},
	{	-1,					NULL,										},
};

 QY_IDCITEM  CONST_zjgaStatUsrInfoTable0[]  =
{
#if  0
	{	IDC_STATIC0,		CONST_qyIdcType_static,		CONST_str_userType,						0,  0,		NULL,					64,	  20,  31,  42,  14,	CONST_qyIdcFlgHide,											NULL,					_T(  "static用户类型"  ),	},
	{	IDC_COMBO0,			CONST_qyIdcType_combo,		0/*CONST_zjgaYhlxTable[0].des*/,		0,	0,		CONST_resId_zjgaYhlxTable,	64,	  65,  31,  69,  12,	CONST_qyIdcFlgHide,											_T(  "qyPcRegInfoTab.col0"  ),	_T(  "用户类型"  ),			},
	{	IDC_STATIC1,		CONST_qyIdcType_static,		CONST_str_according,					0,	0,		NULL,					64,	  41,  52,  14,  13,	0,															NULL,					_T(  "static按"  ),			},
	{	IDC_COMBO1,			CONST_qyIdcType_comboDesc,	0/*gYhGrpTable[0].des*/,				0,	0,		CONST_resId_gYhGrpTable,	64,	  65,  53,  69,  12,	0,															NULL,					_T(  "统计分组单位"  ),		},
	{	IDC_COMBO2,			CONST_qyIdcType_comboDesc,	NULL,									0,	0,		NULL,					64,	  65,  53,  69,  12,	CONST_qyIdcFlgHide,											NULL,					_T(  "统计分组单位"  ),		},
	{	IDC_STATIC2,		CONST_qyIdcType_static,		CONST_str_contentOfStat,				0,	0,		NULL,					64,	  17,  73,  40,  14,	0,															NULL,					_T(  "static统计内容"  ),	},
	{	IDC_CHECK_usr,		CONST_qyIdcType_chk,		CONST_str_userCount,					0,	0,		NULL,					1,	  65,  73,  72,  14,	0,															_T(  "qyPcRegInfoTab.regTime"  ),_T(  "注册用户数"  ),		},
	{	IDC_CHECK0,			CONST_qyIdcType_chk,		CONST_str_jiQiLeiXing,					0,	0,		CONST_resId_jqlxTable,	0,	  65,  90,  72,  14,	0,															_T(  "qyPcRegInfoTab.col5"  ),	_T(  "机器类型"  ),			},
#endif 
	//
	{	-1,					NULL,										},
};


 QY_IDCITEM  CONST_zjgaStatUsrInfoCb0Table0[]  =
{
	{	IDC_COMBO1,			CONST_qyIdcType_comboDesc,	0/*gYhGrpTable[0].des*/,	0,	0,		CONST_resId_gYhGrpTable,	64,	  65,  53,  69,  12,	0,															NULL,					_T(  "统计分组单位"  ),		},
	{	IDC_COMBO2,			CONST_qyIdcType_comboDesc,	NULL,							0,	0,		NULL,					64,	  65,  53,  69,  12,	CONST_qyIdcFlgHide,											NULL,					_T(  "统计分组单位"  ),		},
	{	-1,					NULL,										},
};	

 QY_IDCITEM  CONST_zjgaStatUsrInfoCb0Table1[]  =
{
	{	IDC_COMBO1,			CONST_qyIdcType_comboDesc,	0/*gYhGrpTable[0].des*/,	0,	0,		CONST_resId_gYhGrpTable,	64,	  65,  53,  69,  12,	CONST_qyIdcFlgHide,											NULL,					_T(  "统计分组单位"  ),		},
	{	IDC_COMBO2,			CONST_qyIdcType_comboDesc,	NULL,							0,	0,		NULL,					64,	  65,  53,  69,  12,	0,															NULL,					_T(  "统计分组单位"  ),		},
	{	-1,					NULL,										},
};

 QY_IDCITEM  CONST_zjgaStatGeneralTable0[]  =
{
#if  0
	{	IDC_STATIC0,		CONST_qyIdcType_static,		CONST_str_userType,							0,	0,		NULL,							64,   19,  20,  38,  11,	CONST_qyIdcFlgHide,															NULL,					_T(  "static用户类型"  ),	},
	{   IDC_COMBO0,			CONST_qyIdcType_combo,		0/*CONST_zjgaYhlxTable[0].des*/,				0,	0,		CONST_resId_zjgaYhlxTable,			64,   65,  18,  52,  12,	CONST_qyIdcFlgHide,															_T(  "qyPcEventTab.col0"  ),	_T(  "用户类型"  ),			},
	{	IDC_STATIC1,		CONST_qyIdcType_static,		CONST_str_according,									0,	0,		NULL,							64,	  43,  42,  12,  11,	0,															NULL,					_T(  "static按"  ),			},
	{	IDC_COMBO1,			CONST_qyIdcType_comboDesc,	0/*gEventYhGrpTable[0].des*/,					0,	0,		CONST_resId_gEventYhGrpTable,		64,	  65,  40,  52,  12,	0,															NULL,					_T(  "统计分组单位"  ),		},
	{	IDC_COMBO2,			CONST_qyIdcType_comboDesc,	NULL,											0,	0,		NULL,							64,	  65,  40,  52,  12,	CONST_qyIdcFlgHide,											NULL,					_T(  "统计分组单位"  ),		},
	{	IDC_STATIC2,		CONST_qyIdcType_static,		CONST_str_startTime,							0,	0,		NULL,							64,	  19,  64,  38,  11,	0,															NULL,					_T(  "static起始时间"  ),	},
	{	IDC_STARTDATE,		CONST_qyIdcType_time,		NULL,											0,	0,		NULL,							64,	  65,  64,  65,  14,	0,															NULL,					_T(  "startDate"  ),		},
	{	IDC_STARTTIME,		CONST_qyIdcType_time,		NULL,											0,	0,		NULL,							64,	  142, 64,  52,  14,	0,															NULL,					_T(  "startTime"  ),		},
	{	IDC_STATIC3,		CONST_qyIdcType_static,		CONST_str_endTime,							0,	0,		NULL,							64,	  19,  86,  38,  11,	0,															NULL,					_T(  "static截止时间"  ),	},
	{	IDC_ENDDATE,		CONST_qyIdcType_time,		NULL,											0,	0,		NULL,							64,	  65,  86,  65,  14,	0,															NULL,					_T(  "endDate"  ),			},
	{	IDC_ENDTIME,		CONST_qyIdcType_time,		NULL,											0,	0,		NULL,							64,	  142, 86,  52,  14,	0,															NULL,					_T(  "endTime"  ),			},
	{	IDC_STATIC4,		CONST_qyIdcType_static,		CONST_str_contentOfStat,							0,	0,		NULL,							64,	  19,  113, 38,  11,	0,															NULL,					_T(  "static统计内容"  ),	},
	{	IDC_CHECK_yhzc,		CONST_qyIdcType_chk,		_T(  "用户注册"  ),							0,	0,		NULL,							1,	  65,  113, 57,  14,	CONST_qyIdcFlgHide,											NULL,					_T(  "check用户注册"  ),	},	//隐藏。2003/8/25。
	{	IDC_CHECK_jsjbd,	CONST_qyIdcType_chk,		_T(  "计算机变动"  ),							0,	0,		NULL,							1,	  65,  113, 57,  14,	0,														NULL,					_T(  "check计算机"  ),		},
	{	IDC_CHECK_bhxw,		CONST_qyIdcType_chk,		_T(  "拨号行为"  ),								0,	0,		NULL,							1,	  65,  127, 57,  14,	0,															NULL,					_T(  "check拨号事件"  ),	},
	//{	IDC_CHECK_yhzc,		CONST_qyIdcType_chk,		_T(  "用户注册"  ),								0,	0,		NULL,							1,	  65,  142, 57,  14,	CONST_qyIdcFlgHide,											NULL,					_T(  "check用户注册"  ),	},	//模拟“拨号事件”的位置。2003/8/25。
	{	IDC_CHECK_zysj,		CONST_qyIdcType_chk,		CONST_str_keyEvent,								0,	0,		NULL,							1,	  65,  113, 57,  14,	0,															NULL,					_T(  "check主要事件"  ),	},
#endif 
	//
	{	-1,					NULL,																																																							},
};


 QY_IDCITEM  CONST_zjgaStatGeneralCb0Table0[]  =
{	
	{	IDC_COMBO1,			CONST_qyIdcType_comboDesc,	0/*gEventYhGrpTable[0].des*/,			0,	0,		CONST_resId_gEventYhGrpTable,		64,	  65,  40,  52,  12,	0,															NULL,					_T(  "统计分组单位"  ),		},
	{	IDC_COMBO2,			CONST_qyIdcType_comboDesc,	NULL,									0,	0,		NULL,								64,	  65,  40,  52,  12,	CONST_qyIdcFlgHide,											NULL,					_T(  "统计分组单位"  ),		},
	{	-1,					NULL,		},
};

 QY_IDCITEM  CONST_zjgaStatGeneralCb0Table1[]  =
{	
	{	IDC_COMBO1,			CONST_qyIdcType_comboDesc,	0/*gEventYhGrpTable[0].des*/,			0,	0,		CONST_resId_gEventYhGrpTable,		64,	  65,  40,  52,  12,	CONST_qyIdcFlgHide,											NULL,					_T(  "统计分组单位"  ),		},
	{	IDC_COMBO2,			CONST_qyIdcType_comboDesc,	NULL,									0,	0,		NULL,								64,	  65,  40,  52,  12,	0,															NULL,					_T(  "统计分组单位"  ),		},
	{	-1,					NULL,		},
};


 QY_IDCITEM  CONST_zjgaStatOthersTable0[]  =
{
	{	IDC_STATIC0,		CONST_qyIdcType_static,		CONST_str_startTime,					0,	0,		NULL,								64,   19,  52,  38,  11,	0,															NULL,					_T(  "static起始时间"  ),	},
	{	IDC_STARTDATE,		CONST_qyIdcType_time,		NULL,									0,	0,		NULL,								64,   65,  52,  65,  14,	0,															NULL,					_T(  "起始日期"  ),			},
	{	IDC_STARTTIME,		CONST_qyIdcType_time,		NULL,									0,	0,		NULL,								64,   142, 52,  52,  14,	0,															NULL,					_T(  "起始时间"  ),			},
	{	IDC_STATIC1,		CONST_qyIdcType_static,		CONST_str_endTime,						0,	0,		NULL,								64,   19,  74,  38,  11,	0,															NULL,					_T(  "static截止时间"  ),	},
	{	IDC_ENDDATE,		CONST_qyIdcType_time,		NULL,									0,	0,		NULL,								64,   65,  74,  65,  14,	0,															NULL,					_T(  "截止日期"  ),			},
	{	IDC_ENDTIME,		CONST_qyIdcType_time,		NULL,									0,	0,		NULL,								64,   142, 74,  52,  14,	0,															NULL,					_T(  "截止时间"  ),			},
	{	IDC_STATIC2,		CONST_qyIdcType_static,		CONST_str_contentOfStat,				0,	0,		NULL,								64,   19,  105, 41,  12,	0,															NULL,					_T(  "static统计内容"  ),	},
	{	IDC_CHECK_mszjjr,	CONST_qyIdcType_chk,		CONST_str_qyIntraConn,					0,	0,		NULL,								64,   65,  104, 78,  13,	CONST_qyIdcFlgHide,											NULL,					_T(  "chk陌生主机接入"  ),	},
	{	-1,					NULL,		},
};

   QY_IDCITEM  CONST_statMessengerInfoTable0[]  =
{
#if  0
	{	IDC_STATIC0,		CONST_qyIdcType_static,		CONST_str_userType,					0,  0,		NULL,							64,	  20,  31,  42,  14,	CONST_qyIdcFlgHide,											NULL,								_T(  "static用户类型"  ),	},
	{	IDC_COMBO0,			CONST_qyIdcType_combo,		0/*CONST_zjgaYhlxTable[0].des*/,	0,	0,		CONST_resId_zjgaYhlxTable,		64,	  90,  31,  69,  12,	CONST_qyIdcFlgHide,											_T(  "qyImObjRegInfoTab.col0"  ),	_T(  "用户类型"  ),			},
	{	IDC_STATIC1,		CONST_qyIdcType_static,		CONST_str_according,				0,	0,		NULL,							64,	  17,  52,  60,  13,	0,															NULL,								_T(  "static按"  ),			},
	{	IDC_COMBO1,			CONST_qyIdcType_comboDesc,	0/*gYhGrpTable[0].des*/,			0,	0,		CONST_resId_gYhGrpTable,		64,	  90,  53,  69,  12,	0,															NULL,								_T(  "统计分组单位"  ),		},
	{	IDC_COMBO2,			CONST_qyIdcType_comboDesc,	NULL,								0,	0,		NULL,							64,	  90,  53,  69,  12,	CONST_qyIdcFlgHide,											NULL,								_T(  "统计分组单位"  ),		},
	{	IDC_STATIC2,		CONST_qyIdcType_static,		CONST_str_contentOfStat,			0,	0,		NULL,							64,	  17,  73,  60,  14,	0,															NULL,								_T(  "static统计内容"  ),	},
	{	IDC_CHECK_messenger,CONST_qyIdcType_chk,		CONST_str_msgCount,					0,	0,		CONST_resId_qyNullTable,		1,	  90,  73,  72,  14,	0,															NULL,								_T(  "计算机数"  ),			},
#endif 
	//
	{	-1,					NULL,										},
};

 QY_IDCITEM  CONST_statMessengerInfoCb0Table0[]  =
{
	{	IDC_COMBO1,			CONST_qyIdcType_comboDesc,	0/*gYhGrpTable[0].des*/,			0,	0,		CONST_resId_gYhGrpTable,		64,	  90,  53,  69,  12,	0,															NULL,					_T(  "统计分组单位"  ),		},
	{	IDC_COMBO2,			CONST_qyIdcType_comboDesc,	NULL,								0,	0,		NULL,							64,	  90,  53,  69,  12,	CONST_qyIdcFlgHide,											NULL,					_T(  "统计分组单位"  ),		},
	{	-1,					NULL,										},
};

 QY_IDCITEM  CONST_statMessengerInfoCb0Table1[]  =
{
	{	IDC_COMBO1,			CONST_qyIdcType_comboDesc,	0/*gYhGrpTable[0].des*/,				0,	0,		CONST_resId_gYhGrpTable,		64,	  65,  53,  69,  12,	CONST_qyIdcFlgHide,											NULL,					_T(  "统计分组单位"  ),		},
	{	IDC_COMBO2,			CONST_qyIdcType_comboDesc,	NULL,									0,	0,		NULL,							64,	  65,  53,  69,  12,	0,															NULL,					_T(  "统计分组单位"  ),		},
	{	-1,					NULL,										},
};

 QY_IDCITEM	 CONST_pcPropertiesTable0[]  =
{
	{	IDC_pc0_zongBu,				CONST_qyIdcType_static,		CONST_IDC_CHECK_zb,				0,	0,	NULL,	64,	  24,  31,  40,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zb,		4,		},
 	{	IDC_pc1,					CONST_qyIdcType_static,	 NULL,					0,	0,	NULL,	64,	  72,  31,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zb,		4,		},
	{	IDC_pc2_benBu,				CONST_qyIdcType_static,		CONST_IDC_CHECK_bb,				0,	0,	NULL,	64,	  147, 31,  40,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_bb,		3,		},
 	{	IDC_pc3,					CONST_qyIdcType_static,	 NULL,					0,	0,	NULL,	64,	  201, 31,  40,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_bb,		3,		},
	{	IDC_pc4_danWei,				CONST_qyIdcType_static,		CONST_IDC_CHECK_dw,				0,	0,	NULL,	64,	  24,  42,  40,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_dw,		2,		},
	{	IDC_pc5,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,	  71,  42,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_dw,		2,		},
	{	IDC_pc6_qiTaDanWei,			CONST_qyIdcType_static, 	CONST_str_otherDepart,			0,	0,	NULL,	64,   147, 42,  48,  9,		CONST_qyIdcFlgHide,		NULL,	NULL,	0,	CONST_fieldId_qtdw,		2,		},
	{   IDC_pc7,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   201, 42,  72,  9,		CONST_qyIdcFlgHide,		NULL,	NULL,	0,	CONST_fieldId_qtdw,		2,		},
	{	IDC_pc8_buMen,				CONST_qyIdcType_static, 	CONST_IDC_CHECK_bm,				0,	0,	NULL,	64,   24,  53,  38,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_bm,		1,		},
	{   IDC_pc9,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   71,  53,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_bm,		1,		},
	{	IDC_pc10_shiYongRen,		CONST_qyIdcType_static, 	CONST_IDC_CHECK_syr,				0,	0,	NULL,	64,   147, 53,  48,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_syr,		0,		},
	{   IDC_pc11,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,	  201, 53,  72,	 9, 	0,						NULL,	NULL,	0,	CONST_fieldId_syr,		0,		},
	{	IDC_pc12_jiQiLeiXing,		CONST_qyIdcType_static, 	COSNT_IDC_jiQiLeiXing,			0,	0,	NULL,	64,   24,  64,  40,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_jqlx,		0,		},
	{   IDC_pc13,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   71,  64,	72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_jqlx,		0,		},
	{	IDC_pc14_ziChanBianHao,		CONST_qyIdcType_static, 	CONST_IDC_ziChanBianHao,			0,	0,	NULL,	64,   147, 64,  48,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zcbh0,	0,		},
	{   IDC_pc15,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   201, 64,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zcbh0,	0,		},
	{	IDC_pc16_zhuYaoYongTu,		CONST_qyIdcType_static, 	CONST_IDC_zhuYaoYongTu,			0,	0,	NULL,	64,   24,  75,  40,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zyyt,		0,		},
	{   IDC_pc17,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   71,  75,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zyyt,		0,		},
	{	IDC_pc18_lianXiDianHua,		CONST_qyIdcType_static, 	CONST_IDC_lianXiDianHua,			0,	0,	NULL,	64,   147, 75,  48,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_lxdh,		0,		},
	{   IDC_pc19,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   201, 75,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_lxdh,		0,		},
	{	IDC_pc20_shiYongDiDian,		CONST_qyIdcType_static, 	CONST_IDC_shiYongDiDian,			0,	0,	NULL,	64,   24,  86,  40,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_sydd,		0,		},
	{   IDC_pc21,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   71,  86,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_sydd,		0,		},
	{	IDC_pc22_shiYongDiDian,		CONST_qyIdcType_static, 	CONST_IDC_shiYongDiDian,			0,	0,	NULL,	64,   147, 86,  48,  9,		CONST_qyIdcFlgHide,		NULL,	NULL,	0,	CONST_fieldId_null,		0,		},
	{   IDC_pc23,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   201, 86,  72,  9,		CONST_qyIdcFlgHide,		NULL,	NULL,	0,	CONST_fieldId_null,		0,		},
	{	IDC_pc24_ziChanBianHao1,	CONST_qyIdcType_static, 	CONST_IDC_ziChanBianHao1,			0,	0,	NULL,	64,   24,  97,  40,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zcbh1,	1,		},
	{   IDC_pc25,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   71,  97,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zcbh1,	1,		},
	{	IDC_pc26_ziChanShuoMing1,	CONST_qyIdcType_static, 	CONST_IDC_ziChanShuoMing1,			0,	0,	NULL,	64,   147, 97,  48,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zcsm1,	1,		},
	{   IDC_pc27,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   201, 97,  72,  9,		0,						NULL,	NULL,	0,	CONST_fieldId_zcsm1,	1,		},
	{	IDC_pc28_ziChanBianHao2,	CONST_qyIdcType_static, 	CONST_IDC_ziChanBianHao2,			0,	0,	NULL,	64,   24,  109,  40,  9,	0,						NULL,	NULL,	0,	CONST_fieldId_zcbh2,	2,		},
	{   IDC_pc29,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   71,  109,  72,  9,	0,						NULL,	NULL,	0,	CONST_fieldId_zcbh2,	2,		},
	{	IDC_pc30_ziChanShuoMing2,	CONST_qyIdcType_static, 	CONST_IDC_ziChanShuoMing2,			0,	0,	NULL,	64,   147, 109,  48,  9,	0,						NULL,	NULL,	0,	CONST_fieldId_zcsm2,	2,		},
	{   IDC_pc31,					CONST_qyIdcType_static,  NULL,					0,	0,	NULL,	64,   201, 109,  72,  9,	0,						NULL,	NULL,	0,	CONST_fieldId_zcsm2,	2,		},
	{	-1,																																																							},
};


////////////////////


QY_IDCITEM  *	gpPcListSearchTable0					=	CONST_zjgaPcListSearchTable0;
#ifdef  __ZJST__
		QY_IDCITEM	*	gpPcListSearchCb0Tables[]		=	{  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,   CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table1,  NULL,	};
#endif __ZJST__
QY_IDCITEM	*	gpPcListSearchCb1Tables[]				=	{	NULL,	};
QY_IDCITEM	*	gpEventListSearchTable0					=	CONST_zjgaEventListSearchTable0;
#ifdef  __ZJST__
		QY_IDCITEM	*	gpEventListSearchCb0Tables[]	=	{  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,   CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table1,  NULL,	};
#endif __ZJST__
#ifdef  __HZSJ__
		QY_IDCITEM	*	gpPcListSearchCb0Tables[]		=	{  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,   CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table0,  CONST_zjgaPcListSearchCb0Table1,  NULL,	 };
		QY_IDCITEM	*	gpEventListSearchCb0Tables[]	=	{  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,   CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table0,  CONST_zjgaEventListSearchCb0Table1,  NULL,	};
#endif  __HZSJ__
#ifdef  __OTHER__
		QY_IDCITEM	*	gpPcListSearchCb0Tables[]		=	{	NULL,   };
		QY_IDCITEM	*	gpEventListSearchCb0Tables[]	=	{	NULL,	};
#endif  __OTHER__
QY_IDCITEM	*	gpEventListSearchCb1Tables[]			=	{	NULL,	};

QY_IDCITEM		*	gpNetDevEventListSearchTable0		=	CONST_zjgaNetDevEventListSearchTable0;			//	查询网络事件列表的条件设置
QY_IDCITEM		*	gpNetDevEventListSearchCb0Tables[]	=	{	NULL,	};
QY_IDCITEM		*	gpNetDevEventListSearchCb1Tables[]	=	{	NULL,	};

QY_IDCITEM		*	gpOpEventListSearchTable0			=	CONST_zjgaOpEventListSearchTable0;					//	查询系统事件列表的条件设置
QY_IDCITEM		*	gpOpEventListSearchCb0Tables[]		=	{	NULL,	};
QY_IDCITEM		*	gpOpEventListSearchCb1Tables[]		=	{	NULL,	};

//  QY_IDCITEM		*	gpSecChkEventListSearchTable0		=	CONST_zjgaSecChkEventListSearchTable0;
QY_IDCITEM		*	gpSecChkEventListSearchCb0Tables[]	=	{	NULL,	};
QY_IDCITEM		*	gpSecChkEventListSearchCb1Tables[]	=	{	NULL,	};

//  统计
//	统计列表的条件设置
QY_IDCITEM	*	gpStatIpScanTable0				=	CONST_statIpScanTable0;
QY_IDCITEM	*	gpStatPcInfoTable0				=	CONST_zjgaStatPcInfoTable0;
QY_IDCITEM	*	gpStatPcInfoCb0Tables[]			=	{	CONST_zjgaStatPcInfoCb0Table0,  CONST_zjgaStatPcInfoCb0Table1,  NULL,	};
QY_IDCITEM	*	gpStatUsrInfoTable0				=	CONST_zjgaStatUsrInfoTable0;
QY_IDCITEM	*	gpStatUsrInfoCb0Tables[]		=	{	CONST_zjgaStatUsrInfoCb0Table0,  CONST_zjgaStatUsrInfoCb0Table1,  NULL,	};
QY_IDCITEM  *	gpStatGeneralTable0				=	CONST_zjgaStatGeneralTable0;
QY_IDCITEM	*	gpStatGeneralCb0Tables[]		=	{	CONST_zjgaStatGeneralCb0Table0,  CONST_zjgaStatGeneralCb0Table1,  NULL,	};
QY_IDCITEM  *	gpStatOthersTable0				=	CONST_zjgaStatOthersTable0;

//
QY_IDCITEM	*	gpStatMessengerInfoTable0		=	CONST_statMessengerInfoTable0;
QY_IDCITEM	*	gpStatMessengerInfoCb0Tables[]	=	{	CONST_statMessengerInfoCb0Table0,  CONST_statMessengerInfoCb0Table1,  NULL,	};



#endif	
//  }  以上是的定制信息


 QY_DMITEM  CONST_searchTable[]  =  
{
	{	CONST_resId_gpPcListSearchTable0,				(  TCHAR  *  )gpPcListSearchTable0,	},			//  查询PC列表的条件设置		
	{	CONST_resId_gpPcListSearchCb0Tables,			(  TCHAR  *  )gpPcListSearchCb0Tables,	},
	{	CONST_resId_gpPcListSearchCb1Tables,			(  TCHAR  *  )gpPcListSearchCb1Tables,	},
	//
	{	CONST_resId_gpEventListSearchTable0,			(  TCHAR  *  )gpEventListSearchTable0,	},			//	查询计算机事件列表的条件设置
	{	CONST_resId_gpEventListSearchCb0Tables,			(  TCHAR  *  )gpEventListSearchCb0Tables,	},
	{	CONST_resId_gpEventListSearchCb1Tables,			(  TCHAR  *  )gpEventListSearchCb1Tables,	},
	//
	{	CONST_resId_gpNetDevEventListSearchTable0,		(  TCHAR  *  )gpNetDevEventListSearchTable0,	},		//	查询网络事件列表的条件设置
	{	CONST_resId_gpNetDevEventListSearchCb0Tables,	(  TCHAR  *  )gpNetDevEventListSearchCb0Tables,	},
	{	CONST_resId_gpNetDevEventListSearchCb1Tables,	(  TCHAR  *  )gpNetDevEventListSearchCb1Tables,	},
	//
	{	CONST_resId_gpOpEventListSearchTable0,			(  TCHAR  *  )gpOpEventListSearchTable0,	},		//	查询网络事件列表的条件设置
	{	CONST_resId_gpOpEventListSearchCb0Tables,		(  TCHAR  *  )gpOpEventListSearchCb0Tables,	},
	{	CONST_resId_gpOpEventListSearchCb1Tables,		(  TCHAR  *  )gpOpEventListSearchCb1Tables,	},
	//
	{	CONST_resId_gpSecChkEventListSearchTable0_netMc2,		(  TCHAR  *  )CONST_zjgaSecChkEventListSearchTable0_netMc2,	},		//	查询网络事件列表的条件设置
	{	CONST_resId_gpSecChkEventListSearchTable0_secChk,		(  TCHAR  *  )CONST_zjgaSecChkEventListSearchTable0_secChk,	},		//	查询网络事件列表的条件设置
	//
	{	CONST_resId_gpSecChkEventListSearchCb0Tables,			(  TCHAR  *  )gpSecChkEventListSearchCb0Tables,	},
	{	CONST_resId_gpSecChkEventListSearchCb1Tables,			(  TCHAR  *  )gpSecChkEventListSearchCb1Tables,	},
	///////////
	// net 统计
	{	CONST_resId_gpStatIpScanTable0,							(  TCHAR  *  )gpStatIpScanTable0,				},
	{	CONST_resId_gpStatPcInfoTable0,							(  TCHAR  *  )gpStatPcInfoTable0,				},
	{	CONST_resId_gpStatPcInfoCb0Tables,						(  TCHAR  *  )gpStatPcInfoCb0Tables,			},
	{	CONST_resId_gpStatUsrInfoTable0,						(  TCHAR  *  )gpStatUsrInfoTable0,				},
	{	CONST_resId_gpStatUsrInfoCb0Tables,						(  TCHAR  *  )gpStatUsrInfoCb0Tables,			},
	{	CONST_resId_gpStatGeneralTable0,						(  TCHAR  *  )gpStatGeneralTable0,				},
	{	CONST_resId_gpStatGeneralCb0Tables,						(  TCHAR  *  )gpStatGeneralCb0Tables,			},
	{	CONST_resId_gpStatOthersTable0,							(  TCHAR  *  )gpStatOthersTable0,				},
	// is 统计
	{	CONST_resId_gpStatMessengerInfoTable0,					(  TCHAR  *  )gpStatMessengerInfoTable0,		},
	{	CONST_resId_gpStatMessengerInfoCb0Tables,				(  TCHAR  *  )gpStatMessengerInfoCb0Tables,		},
	//
	{	CONST_resId_pcPropertiesTable0,							(  TCHAR  *  )CONST_pcPropertiesTable0,			},
	{	-1,		},
};


