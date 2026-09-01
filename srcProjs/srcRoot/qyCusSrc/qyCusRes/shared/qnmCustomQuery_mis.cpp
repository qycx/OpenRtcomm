

#include	"stdafx.h"
#include	<tchar.h>
#include	<commctrl.h>

//  #include	"myresource_main.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
//
#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_is.h"


 QY_COLUMNINFO  CONST_simpleUsrSqlColumns_is[]  =
{
	MACRO_simpleUsrSqlColumnsEx(  "B"  )
	{	-1,											},

};

 QNM_QUERY_STRUCT  CONST_simpleUsrQueryStruct_is  =  
{
	 CONST_simpleUsrSqlColumns_is,	CONST_zjgaSimpleUsrDisplayColumns,
};


 QY_COLUMNINFO  CONST_messengerAuthListSqlColumns[]  =
{
	{	6,	_T(  "qyImObjAuthTab.id"  ),						SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyImObjAuthTab.uiType"  ),					SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyImObjAuthTab.idStr"  ),						SQL_CHAR,	},		//	6
	MACRO_simpleUsrSqlColumnsEx(  "B"  )
	{	1,	_T(  "qyImAmTab.messengerName"  ),					SQL_CHAR,	},		//	1
	//
	{	1,  _T(  "qyImObjAuthTab.iRole"  ),						SQL_INTEGER,	},
	//
	{	1,	_T(  "qyMessengerPhoneInfoTab.wDevIdStr"  ),			SQL_CHAR,	},
	{	1,	_T(  "qyImObjAuthTab.pcName"  ),					SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImObjAuthTab.osUsrName"  ),					SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImObjAuthTab.domainName"  ),				SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImObjAuthTab.mac0"  ),						SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImObjAuthTab.mac1"  ),						SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImObjAuthTab.mac2"  ),						SQL_CHAR,	},		//	1
	{	1,	_T(  "A.startTime"  ),								SQL_CHAR,	},
	{	1,	_T(  "qyImObjAuthTab.tLastModifiedTime"  ),			SQL_CHAR,	},		//	1

	{	-1,	NULL,											},
};

 QY_COLUMNINFO	 CONST_messengerAuthListDisplayColumns[]  = 
{
	{	CONST_qyColumnDisplayType_long,			CONST_str_xuHao,				SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_objType,		CONST_str_leiXing,				SQL_INTEGER,	LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr,				SQL_CHAR,		LVCFMT_LEFT, 85,  1, 50,	},	//  1
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_str,			_T(  "Messenger Name"  ),		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	//
	{	CONST_qyColumnDisplayType_imObjRole,	CONST_str_role,				SQL_INTEGER,	LVCFMT_LEFT,  80,  1,  50,  },
	//
	{	CONST_qyColumnDisplayType_str,			CONST_str_phoneNo,				SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_str,			_T(  "PC Name"  ),				SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_str,			_T(  "OS Usr Name"  ),			SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_str,			_T(  "Domain Name"  ),			SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_str,			_T(  "MAC0"  ),					SQL_CHAR,		LVCFMT_LEFT, 90, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_str,			_T(  "MAC1"  ),					SQL_CHAR,		LVCFMT_LEFT, 90, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_str,			_T(  "MAC2"  ),					SQL_CHAR,		LVCFMT_LEFT, 90, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_time,			CONST_str_qiYongShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_time,			CONST_str_gengXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	-1,	NULL,														},
};

 QNM_QUERY_STRUCT  CONST_messengerAuthListQueryStruct  =  
{
	 CONST_messengerAuthListSqlColumns,		CONST_messengerAuthListDisplayColumns,
};



 QY_COLUMNINFO  CONST_messengerAuthNeedAuditedListSqlColumns[]  =
{
	{	6,	_T(  "qyImObjAuthTmpTab.id"  ),							SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyImObjAuthTmpTab.uiType"  ),						SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyImObjAuthTmpTab.idStr"  ),						SQL_CHAR,	},		//	6
	{	1,	_T(  "qyImObjAuthTmpTab.messengerName"  ),				SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImObjAuthTmpTab.pcName"  ),						SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImObjAuthTmpTab.osUsrName"  ),					SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImObjAuthTmpTab.domainName"  ),					SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImObjAuthTmpTab.mac0"  ),						SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImObjAuthTmpTab.mac1"  ),						SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImObjAuthTmpTab.mac2"  ),						SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImObjAuthTmpTab.startTime"  ),					SQL_CHAR,	},
	{	1,	_T(  "qyImObjAuthTmpTab.tLastModifiedTime"  ),			SQL_CHAR,	},		//	1

	{	-1,	NULL,											},
};

 QY_COLUMNINFO	 CONST_messengerAuthNeedAuditedListDisplayColumns[]  = 
{
	{	CONST_qyColumnDisplayType_long,		CONST_str_xuHao,				SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_objType,	CONST_str_leiXing,				SQL_INTEGER,	LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,	CONST_str_idStr,				SQL_CHAR,		LVCFMT_LEFT, 85,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,		_T(  "Messenger Name"  ),		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_str,		_T(  "PC Name"  ),				SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_str,		_T(  "OS Usr Name"  ),			SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_str,		_T(  "Domain Name"  ),			SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_str,		_T(  "MAC0"  ),					SQL_CHAR,		LVCFMT_LEFT, 90, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_str,		_T(  "MAC1"  ),					SQL_CHAR,		LVCFMT_LEFT, 90, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_str,		_T(  "MAC2"  ),					SQL_CHAR,		LVCFMT_LEFT, 90, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_time,		CONST_str_qiYongShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_time,		CONST_str_gengXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	-1,	NULL,														},
};


 QNM_QUERY_STRUCT  CONST_messengerAuthNeedAuditedListQueryStruct  =  
{
	 CONST_messengerAuthNeedAuditedListSqlColumns,		CONST_messengerAuthNeedAuditedListDisplayColumns,
};
 

//

  QY_COLUMNINFO  CONST_imAmListSqlColumns[]  =
  {
	  {	6,	_T("qyImAmTab.id"),							SQL_INTEGER,	},		//	6
	  {	6,	_T("qyImObjAuthTab.uiType"),						SQL_INTEGER,	},		//	6
	  MACRO_simpleUsrSqlColumnsEx("B")
	  {	6,	_T("qyImAmTab.idStr"),						SQL_CHAR,	},		//	6
	  {	6,	_T("qyImAmTab.usAuthType"),					SQL_INTEGER, },
	{	1,	_T(  "qyImAmTab.messengerName"  ),				SQL_CHAR,	},		//	1
	{	-1,	},
 };


 QY_COLUMNINFO	 CONST_imAmListDisplayColumns[]  = 
{
	{	CONST_qyColumnDisplayType_long,		CONST_str_xuHao,				SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_objType,	CONST_str_leiXing,				SQL_INTEGER,	LVCFMT_LEFT, 80,  1, 50,	},	//  1
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_idStr,	CONST_str_idStr,				SQL_CHAR,		LVCFMT_LEFT, 150,  1, 50,	},	//  1
	 {	CONST_qyColumnDisplayType_long,		_T("usAuthType"),				SQL_INTEGER,	LVCFMT_LEFT, 150,	1, 50,},	//  13  
	{	CONST_qyColumnDisplayType_str,		_T(  "Messenger Name"  ),		SQL_CHAR,		LVCFMT_LEFT, 200, 1, 50,	},	//  0
	{	-1,	},
};


 QNM_QUERY_STRUCT  CONST_imAmListQueryStruct  =
{
	CONST_imAmListSqlColumns,		CONST_imAmListDisplayColumns,
};


 //
  QY_COLUMNINFO  CONST_phoneMessengerListSqlColumns[]  =
{
	{	6,	_T(  "qyMessengerPhoneInfoTab.id"  ),							SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyImObjAuthTab.uiType"  ),								SQL_INTEGER,	},		//	6
	MACRO_simpleUsrSqlColumnsEx(  "B"  )
	{	6,	_T(  "qyMessengerPhoneInfoTab.wDevIdStr"  ),					SQL_CHAR,		},
	{	6,	_T(  "qyMessengerPhoneInfoTab.idStr"  ),						SQL_CHAR,	},			//	6
	{	1,	_T(  "qyImObjAuthTab.startTime"  ),								SQL_CHAR,	},
	{	1,	_T(  "qyImObjAuthTab.tLastModifiedTime"  ),						SQL_CHAR,	},			//	1

	{	-1,	NULL,											},
};

 QY_COLUMNINFO	 CONST_phoneMessengerListDisplayColumns[]  = 
{
	{	CONST_qyColumnDisplayType_long,		CONST_str_xuHao,				SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_objType,	CONST_str_leiXing,				SQL_INTEGER,	LVCFMT_LEFT, 80,  1, 50,	},	//  1
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_str,		CONST_str_phoneNo,				SQL_CHAR,		LVCFMT_LEFT, 100,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,	CONST_str_idStr,				SQL_CHAR,		LVCFMT_LEFT, 85,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_time,		CONST_str_qiYongShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_time,		CONST_str_gengXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	-1,	NULL,														},
};




 QNM_QUERY_STRUCT  CONST_phoneMessengerListQueryStruct  =
{
	 CONST_phoneMessengerListSqlColumns,			CONST_phoneMessengerListDisplayColumns,
};


 /////////////



 QY_COLUMNINFO  CONST_imGrpAuthListSqlColumns_isMgr[]  =
{
	{	6,	_T(  "qyImObjAuthTab.id"  ),				SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyImObjAuthTab.uiType"  ),			SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyImObjAuthTab.idStr"  ),				SQL_CHAR,	},			//	6
	//
	{	7,	_T(  "qyImGrpInfoTab.name"  ),				SQL_CHAR,	},
	{	7,	_T(  "qyImGrpInfoTab.subtype"  ),			SQL_INTEGER,	},
	//
	{	7,	_T(  "qyImGrpInfoTab.idStr_creator"  ),			SQL_CHAR,	},
	//
	{	1,	_T(  "qyImObjTab.startTime"  ),				SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImGrpInfoTab.tLastModifiedTime"  ),	SQL_CHAR,	},		//	1
	{	-1,	NULL,											},
};

 QY_COLUMNINFO	 CONST_imGrpAuthListDisplayColumns[]  = 
{
	{	CONST_qyColumnDisplayType_long,					CONST_str_xuHao,					SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_objType,				CONST_str_leiXing,				SQL_INTEGER,	LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,				CONST_str_idStr_grp,			SQL_CHAR,		LVCFMT_LEFT, 85,  1, 50,	},	//  1
	//
	{	CONST_qyColumnDisplayType_str,					CONST_str_mingChen,				SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_imGrpSubtype,			CONST_str_subtype,				SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0	
	//
	{	CONST_qyColumnDisplayType_idStr,				CONST_str_idStr_creator,			SQL_CHAR,		LVCFMT_LEFT, 85,  1, 50,	},	//  1
	//
	{	CONST_qyColumnDisplayType_time,					CONST_str_qiYongShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_time,					CONST_str_gengXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	-1,	NULL,														},
};

 QNM_QUERY_STRUCT  CONST_imGrpAuthListQueryStruct_isMgr  =  
{
	 CONST_imGrpAuthListSqlColumns_isMgr,		CONST_imGrpAuthListDisplayColumns,
};



 
 QY_COLUMNINFO  CONST_imGrpListSqlColumns[]  =
{
	{	6,	_T(  "qyImObjTab.id"  ),						SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyImObjTab.uiType"  ),					SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyImObjTab.idStr"  ),						SQL_CHAR,	},			//	6
	//
	{	7,	_T(  "qyImGrpInfoTab.name"  ),					SQL_CHAR,	},
	{	7,	_T(  "qyImGrpInfoTab.subtype"  ),				SQL_INTEGER,	},
	//
	{	7,	_T(  "qyImGrpInfoTab.idStr_creator"  ),			SQL_CHAR,	},
	//
	{	1,	_T(  "qyImObjAuthTab.startTime"  ),				SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImGrpInfoTab.tLastModifiedTime"  ),		SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImObjTab.iStatus"  ),					SQL_INTEGER,	},
	{	-1,	NULL,											},
};

  QY_COLUMNINFO	 CONST_imGrpListDisplayColumns_isMgr[]  = 
{
	{	CONST_qyColumnDisplayType_long,		CONST_str_xuHao,								SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_objType,	CONST_str_leiXing,								SQL_INTEGER,	LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,	CONST_str_idStr_grp,							SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	//
	{	CONST_qyColumnDisplayType_str,		CONST_str_mingChen,								SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_imGrpSubtype,	CONST_str_subtype,								SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	//
	{	CONST_qyColumnDisplayType_idStr,	CONST_str_idStr_creator,							SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	//
	{	CONST_qyColumnDisplayType_time,		CONST_str_zhuCeShiJian,							SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_time,		CONST_str_gengXinShiJian,						SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_qyStatus,	CONST_str_zhuangTai,			SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	-1,	NULL,														},
};


 QNM_QUERY_STRUCT  CONST_imGrpListQueryStruct_isMgr  =  
{
	 CONST_imGrpListSqlColumns,		CONST_imGrpListDisplayColumns_isMgr,
};


  QY_COLUMNINFO	 CONST_imGrpListDisplayColumns_isClient[]  = 
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
	{	CONST_qyColumnDisplayType_time,		CONST_str_zhuCeShiJian,							SQL_CHAR,		LVCFMT_LEFT, 0, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_time,		CONST_str_gengXinShiJian,						SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_qyStatus,	CONST_str_zhuangTai,			SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	-1,	NULL,														},
};


 QNM_QUERY_STRUCT  CONST_imGrpListQueryStruct_isClient  =  
{
	 CONST_imGrpListSqlColumns,		CONST_imGrpListDisplayColumns_isClient,
};




  QY_COLUMNINFO  CONST_imGrpAuthMemListSqlColumns_isMgr[]  =
{
	{	6,	_T(  "qyImGrpMemTab.id"  ),					SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyImObjAuthTab.uiType"  ),			SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyImGrpMemTab.idStr_grp"  ),				SQL_CHAR,	},			//	6
	{	7,	_T(  "qyImGrpInfoTab.name"  ),				SQL_CHAR,	},
	{	7,	_T(  "qyImGrpMemTab.idStr_mem"  ),			SQL_CHAR,	},
	MACRO_simpleUsrSqlColumnsEx(  "qyImObjRegInfoTab"  )
	{	1,  _T(  "qyImGrpMemTab.iRole"  ),				SQL_INTEGER,	},
	{	1,	_T(  "qyImGrpMemTab.tLastModifiedTime"  ),	SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImGrpMemTab.iStatus"  ),			SQL_INTEGER,	},		//	1
	{	-1,	NULL,											},
};

//
  QY_COLUMNINFO  CONST_imGrpMemListSqlColumns_isMgr[]  =
{
	{	6,	_T(  "qyImGrpMemTab.id"  ),					SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyImObjTab.uiType"  ),			SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyImGrpMemTab.idStr_grp"  ),				SQL_CHAR,	},			//	6
	{	7,	_T(  "qyImGrpInfoTab.name"  ),				SQL_CHAR,	},
	{	7,	_T(  "qyImGrpMemTab.idStr_mem"  ),			SQL_CHAR,	},
	MACRO_simpleUsrSqlColumnsEx(  "qyImObjRegInfoTab"  )
	{	1,  _T(  "qyImGrpMemTab.iRole"  ),				SQL_INTEGER,	},
	{	1,	_T(  "qyImGrpMemTab.tLastModifiedTime"  ),	SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImGrpMemTab.iStatus"  ),			SQL_INTEGER,	},		//	1
	{	-1,	NULL,											},
};


 //
 QY_COLUMNINFO	 CONST_imGrpMemListDisplayColumns[]  = 
{
	{	CONST_qyColumnDisplayType_long,		CONST_str_xuHao,					SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_objType,	CONST_str_leiXing,				SQL_INTEGER,	LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,	CONST_str_idStr_grp,			SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,		CONST_str_mingChen,				SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_idStr,	CONST_str_idStr,				SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_imGrpMemRole,CONST_str_role,				SQL_INTEGER,	LVCFMT_LEFT,  80,  1,  50,  },
	{	CONST_qyColumnDisplayType_time,		CONST_str_gengXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_qyStatus,	CONST_str_zhuangTai,			SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	-1,	NULL,														},
};


 //
  QNM_QUERY_STRUCT  CONST_imGrpAuthMemListQueryStruct_isMgr  =  
{
	 CONST_imGrpAuthMemListSqlColumns_isMgr,		CONST_imGrpMemListDisplayColumns,
};




 //
 QNM_QUERY_STRUCT  CONST_imGrpMemListQueryStruct_isMgr  =  
{
	 CONST_imGrpMemListSqlColumns_isMgr,		CONST_imGrpMemListDisplayColumns,
};
 


  QY_COLUMNINFO  CONST_imGrpMemListSqlColumns_isClient[]  =
{
	{	6,	_T(  "qyImGrpMemTab.id"  ),					SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyImObjTab.uiType"  ),				SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyImGrpMemTab.idStr_grp"  ),					SQL_CHAR,	},			//	6
	{	7,	_T(  "qyImGrpInfoTab.name"  ),				SQL_CHAR,	},
	{	7,	_T(  "qyImGrpMemTab.idStr_mem"  ),			SQL_CHAR,	},
	MACRO_simpleUsrSqlColumnsEx(  "qyImObjRegInfoTab"  )
	{	1,  _T(  "qyImGrpMemTab.iRole"  ),				SQL_INTEGER,	},
	{	1,	_T(  "qyImGrpMemTab.tLastModifiedTime"  ),	SQL_CHAR,	},		//	1
	{	1,	_T(  "qyImGrpMemTab.iStatus"  ),			SQL_INTEGER,	},		//	1
	{	-1,	NULL,											},
};

 QNM_QUERY_STRUCT  CONST_imGrpMemListQueryStruct_isClient  =  
{
	 CONST_imGrpMemListSqlColumns_isClient,				CONST_imGrpMemListDisplayColumns,
};


 QY_COLUMNINFO  CONST_imObjListSqlColumns_isMgr[]  =
{
	{	6,	_T(  "A.id"  ),							SQL_INTEGER,	},		//	6
	{	1,	_T(  "A.uiType"  ),						SQL_INTEGER,	},
	{	1,	_T(  "A.usRunningStatus"  ),			SQL_INTEGER,	},
	{	1,	_T(  "A.idStr"  ),						SQL_CHAR,		},		//	6
	MACRO_simpleUsrSqlColumnsEx(  "B"  )
	//
	{	1,  _T(  "A.iRole"  ),						SQL_INTEGER,	},
	//
	{	1,	_T(  "qyMessengerPhoneInfoTab.wDevIdStr"  ),	SQL_CHAR,	},
	{	1,	_T(  "A.detectedIp"  ),					SQL_CHAR,		},		//	1
	{	1,	_T(  "A.ip"  ),							SQL_CHAR,		},		//	1
	{	1,	_T(  "qyImObjAuthTab.startTime"  ),		SQL_CHAR,	},
	{	1,	_T(  "A.tLastModifiedTime"  ),			SQL_CHAR,		},
	{	-1,	NULL,											},
};

 QY_COLUMNINFO	 CONST_imObjListDisplayColumns_isMgr[]  = 
{
	{	CONST_qyColumnDisplayType_long,				CONST_str_xuHao,						SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_objType,			CONST_str_leiXing,						SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_usRunningStatus,	CONST_str_zhuangTai,					SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,			CONST_str_idStr,						SQL_CHAR,		LVCFMT_LEFT, 85,  1, 50,	},	//  1
	MACRO_zjgaSimpleUsrDisplayColumns
	//
	{	CONST_qyColumnDisplayType_imObjRole,		CONST_str_role,				SQL_INTEGER,	LVCFMT_LEFT,  80,  1,  50,  },
	//
	{	CONST_qyColumnDisplayType_str,				CONST_str_phoneNo,						SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_ip12,				CONST_str_detectedIp,					SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_ip12,				_T(  "IP"  ),							SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_time,				CONST_str_zhuCeShiJian,					SQL_CHAR,		LVCFMT_LEFT, 120,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_time,				CONST_str_gengXinShiJian,				SQL_CHAR,		LVCFMT_LEFT, 120,  1, 50,	},	//  1
	{	-1,	NULL,														},
};



 QNM_QUERY_STRUCT  CONST_imObjListQueryStruct_isMgr  =
{
	 CONST_imObjListSqlColumns_isMgr,			CONST_imObjListDisplayColumns_isMgr,	
};


 QY_COLUMNINFO  CONST_imObjListSqlColumns_isClient[]  =
{
	{	6,	_T(  "A.id"  ),									SQL_INTEGER,	},		//	6
	{	1,	_T(  "A.uiType"  ),								SQL_INTEGER,	},
	{	1,	_T(  "A.idStr"  ),								SQL_CHAR,		},		//	6
	MACRO_simpleUsrSqlColumnsEx(  "B"  )
	//	
	{	1,  _T(  "A.iRole"  ),						SQL_INTEGER,	},
	//
	{	1,	_T(  "qyMessengerPhoneInfoTab.wDevIdStr"  ),	SQL_CHAR,	},
	//  {	1,	_T(  "A.ip"  ),								SQL_CHAR,		},		//	1	//  在客户端，这里的IP本来是应该显示的。应该还没有传递下去，所以。暂时隐掉。detectedIp也应该显示
	{	1,	_T(  "A.tLastModifiedTime"  ),					SQL_CHAR,		},
	{	1,	_T(  "A.iStatus"  ),							SQL_INTEGER,	},
	{	-1,	NULL,											},
};

 QY_COLUMNINFO	 CONST_imObjListDisplayColumns_isClient[]  = 
{
	{	CONST_qyColumnDisplayType_long,				CONST_str_xuHao,					SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_objType,			CONST_str_leiXing,				SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,			CONST_str_idStr,				SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	MACRO_zjgaSimpleUsrDisplayColumns
	//
	{	CONST_qyColumnDisplayType_imObjRole,		CONST_str_role,				SQL_INTEGER,	LVCFMT_LEFT,  80,  1,  50,  },
	//
	{	CONST_qyColumnDisplayType_str,				CONST_str_phoneNo,				SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	//  {	CONST_qyColumnDisplayType_ip12,				_T(  "IP"  ),					SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_time,				CONST_str_gengXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_qyStatus,			CONST_str_zhuangTai,							SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	-1,	NULL,														},
};



 QNM_QUERY_STRUCT  CONST_imObjListQueryStruct_isClient  =
{
	 CONST_imObjListSqlColumns_isClient,			CONST_imObjListDisplayColumns_isClient,	
};




 QY_COLUMNINFO	CONST_imObjUsrListSqlColumns_isMgr[]  =  
{
	{	0,						_T(  "B.id"  ),								SQL_INTEGER,	},		//	6
	{	0,						_T(  "B.auditTime"  ),						SQL_CHAR,	},
	{	0,						_T(  "B.idStr"  ),							SQL_CHAR,	},
	MACRO_simpleUsrSqlColumnsEx(  "B"  )
	{	CONST_fieldId_jqlx,		_T(  "B.col5"  ),							SQL_CHAR,	0,  0,  0,	},		//	5
	{	CONST_fieldId_zcbh0,	_T(  "B.col13"  ),							SQL_CHAR,	0,  0,  0,	},		
	{	CONST_fieldId_zyyt,		_T(  "B.col6"  ),							SQL_CHAR,	0,  0,  0,	},		//	6
	{	CONST_fieldId_lxdh,		_T(  "B.col7"  ),							SQL_CHAR,	0,  0,  0,	},		//	7
	{	CONST_fieldId_sydd,		_T(  "B.col10"  ),							SQL_CHAR,	0,  0,  0,	},		//	10
	{	CONST_fieldId_zcbh1,	_T(  "B.col14"  ),							SQL_CHAR,	0,  0,  1,	},		//	8
	{	CONST_fieldId_zcsm1,	_T(  "B.col15"  ),							SQL_CHAR,	0,  0,  1,	},		//	8
	{	CONST_fieldId_zcbh2,	_T(  "B.col16"  ),							SQL_CHAR,	0,  0,  2,	},		//	8
	{	CONST_fieldId_zcsm2,	_T(  "B.col17"  ),							SQL_CHAR,	0,  0,  2,	},		//	8
	{	11,						_T(  "A.ip"  ),								SQL_CHAR,	0,  0,  0,	},		//	11
	{	1,						_T(  "A.startTime"  ),						SQL_CHAR,	},
	{	0,						_T(  "B.tLastModifiedTime"  ),				SQL_CHAR,	0,  0,  0,	},		//	11
	{	-1,									},
};

 QY_COLUMNINFO	CONST_imObjUsrListDisplayColumns_isMgr[] = 
{
	{	CONST_qyColumnDisplayType_long,		CONST_str_xuHao,					SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_time,		CONST_str_shenHeShiJian,			SQL_CHAR,		LVCFMT_LEFT, 130, 1, 50, },	//  0
	{	CONST_qyColumnDisplayType_idStr,	CONST_str_idStr,					SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
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
	{	CONST_qyColumnDisplayType_time,		CONST_str_qiYongShiJian,			SQL_CHAR,		LVCFMT_LEFT, 130,  0,  0, },	//  9					   
	{	CONST_qyColumnDisplayType_time,		CONST_str_gengXinShiJian,			SQL_CHAR,		LVCFMT_LEFT, 130,  0,  0, },	//  9					   
	{	-1,																									},
};


 QNM_QUERY_STRUCT  CONST_imObjUsrListQueryStruct_isMgr  =
{
	 CONST_imObjUsrListSqlColumns_isMgr,  CONST_imObjUsrListDisplayColumns_isMgr,
};



  QY_COLUMNINFO	CONST_imObjUsrListSqlColumns_isClient[]  =  
{
	{	0,						_T(  "B.id"  ),				SQL_INTEGER,	},		//	6
	{	0,						_T(  "B.idStr"  ),			SQL_CHAR,	},
	MACRO_simpleUsrSqlColumnsEx(  "B"  )
	{	CONST_fieldId_jqlx,		_T(  "B.col5"  ),			SQL_CHAR,	0,  0,  0,	},		//	5
	{	CONST_fieldId_zcbh0,	_T(  "B.col13"  ),			SQL_CHAR,	0,  0,  0,	},		
	{	CONST_fieldId_zyyt,		_T(  "B.col6"  ),			SQL_CHAR,	0,  0,  0,	},		//	6
	{	CONST_fieldId_lxdh,		_T(  "B.col7"  ),			SQL_CHAR,	0,  0,  0,	},		//	7
	{	CONST_fieldId_sydd,		_T(  "B.col10"  ),			SQL_CHAR,	0,  0,  0,	},		//	10
	{	CONST_fieldId_zcbh1,	_T(  "B.col14"  ),			SQL_CHAR,	0,  0,  1,	},		//	8
	{	CONST_fieldId_zcsm1,	_T(  "B.col15"  ),			SQL_CHAR,	0,  0,  1,	},		//	8
	{	CONST_fieldId_zcbh2,	_T(  "B.col16"  ),			SQL_CHAR,	0,  0,  2,	},		//	8
	{	CONST_fieldId_zcsm2,	_T(  "B.col17"  ),			SQL_CHAR,	0,  0,  2,	},		//	8
	{	11,						_T(  "A.ip"  ),								SQL_CHAR,	0,  0,  0,	},		//	11
	{	0,						_T(  "B.tLastModifiedTime"  ),				SQL_CHAR,	0,  0,  0,	},		//	11
	{	-1,									},
};

 QY_COLUMNINFO	CONST_imObjUsrListDisplayColumns_isClient[] = 
{
	{	CONST_qyColumnDisplayType_long,		CONST_str_xuHao,					SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_idStr,	CONST_str_idStr,					SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
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
	{	CONST_qyColumnDisplayType_time,		CONST_str_gengXinShiJian,			SQL_CHAR,		LVCFMT_LEFT, 130,  0,  0, },	//  9					   
	{	-1,																									},
};


 QNM_QUERY_STRUCT  CONST_imObjUsrListQueryStruct_isClient  =
{
	 CONST_imObjUsrListSqlColumns_isClient,  CONST_imObjUsrListDisplayColumns_isClient,
};






 QY_COLUMNINFO	CONST_imObjUsrInTab1ListSqlColumns_is[]  =  
{
	{	0,						_T(  "B.id"  ),				SQL_INTEGER,	},		//	6
	{	0,						_T(  "B.idStr"  ),			SQL_CHAR,	},
	MACRO_simpleUsrSqlColumnsEx(  "B"  )
	{	CONST_fieldId_jqlx,		_T(  "B.col5"  ),			SQL_CHAR,	0,  0,  0,	},		//	5
	{	CONST_fieldId_zcbh0,	_T(  "B.col13"  ),			SQL_CHAR,	0,  0,  0,	},		
	{	CONST_fieldId_zyyt,		_T(  "B.col6"  ),			SQL_CHAR,	0,  0,  0,	},		//	6
	{	CONST_fieldId_lxdh,		_T(  "B.col7"  ),			SQL_CHAR,	0,  0,  0,	},		//	7
	{	CONST_fieldId_sydd,		_T(  "B.col10"  ),			SQL_CHAR,	0,  0,  0,	},		//	10
	{	CONST_fieldId_zcbh1,	_T(  "B.col14"  ),			SQL_CHAR,	0,  0,  1,	},		//	8
	{	CONST_fieldId_zcsm1,	_T(  "B.col15"  ),			SQL_CHAR,	0,  0,  1,	},		//	8
	{	CONST_fieldId_zcbh2,	_T(  "B.col16"  ),			SQL_CHAR,	0,  0,  2,	},		//	8
	{	CONST_fieldId_zcsm2,	_T(  "B.col17"  ),			SQL_CHAR,	0,  0,  2,	},		//	8
	{	0,						_T(  "B.tCommitTime"  ),	SQL_CHAR,	0,  0,  2,	},		//	8
	{	0,						_T(  "B.tLastModifiedTime"  ),				SQL_CHAR,	0,  0,  0,	},		//	11
	{	-1,									},
};

 QY_COLUMNINFO	CONST_imObjUsrInTab1ListDisplayColumns_is[] = 
{
	{	CONST_qyColumnDisplayType_long,		CONST_str_xuHao,					SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_idStr,	CONST_str_idStr,					SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
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
	{	CONST_qyColumnDisplayType_time,		CONST_str_tiJiaoShiJian,			SQL_CHAR,		LVCFMT_LEFT, 130,  0,  0, },	//  9					   
	{	CONST_qyColumnDisplayType_time,		CONST_str_gengXinShiJian,			SQL_CHAR,		LVCFMT_LEFT, 130,  0,  0, },	//  9					   
	{	-1,																									},
};


 QNM_QUERY_STRUCT  CONST_imObjUsrInTab1ListQueryStruct_is  =
{
	 CONST_imObjUsrInTab1ListSqlColumns_is,  CONST_imObjUsrInTab1ListDisplayColumns_is,
};

////////////////////


 //  2005/05/10, 客户端列表
 QY_COLUMNINFO  CONST_clientListSqlColumns_is[]  =
{
	 {	12,						_T(  "A.idStr"  ),							SQL_CHAR,	},		//	12
	 MACRO_simpleUsrSqlColumnsEx(  "B"  )
	 {	11,						_T(  "A.ip"  ),								SQL_CHAR,	},		//	11
	 {	13,						_T(  "A.clientVer"  ),						SQL_CHAR,	},
	 {	16,						_T(  "A.usLangId"  ),						SQL_INTEGER,},
	 {	14,						_T(  "A.startTime"  ),						SQL_CHAR,	},
	 {	14,						_T(  "A.tLastModifiedTime"  ),				SQL_CHAR,	},
	 {	-1,						},
};

 QY_COLUMNINFO  CONST_clientListDisplayColumns_is[]  =
{	 
	 {	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr,					SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	 MACRO_zjgaSimpleUsrDisplayColumns
	 {	CONST_qyColumnDisplayType_ip12,			_T(  "IP"  ),					SQL_CHAR,		LVCFMT_LEFT, 100,  0, 0, },	//  8					   
	 {	CONST_qyColumnDisplayType_str,			CONST_str_banBen,				SQL_CHAR,		LVCFMT_LEFT, 80,  0, 0, },	//  8					   
	 {	CONST_qyColumnDisplayType_langId,		CONST_str_yuYan,				SQL_CHAR,		LVCFMT_LEFT, 70,  0, 0, },	//  8					   
	 {	CONST_qyColumnDisplayType_time,			CONST_str_fenFaShiJian,			SQL_CHAR,		LVCFMT_LEFT, 115,  0, 0, },	//  8					   
	 {	CONST_qyColumnDisplayType_time,			CONST_str_gengXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 115,  0, 0, },	//  8					   
	 {	-1,						},
};


 QNM_QUERY_STRUCT  CONST_clientListQueryStruct_is  =
{
	 CONST_clientListSqlColumns_is,  CONST_clientListDisplayColumns_is,
};



 /////////////

  //  2005/05/10, customerService
 QY_COLUMNINFO  CONST_customerServiceListSqlColumns_is[]  =
{
	{	6,	_T(  "qyCustomerServiceObjTab.id"  ),			SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyImObjAuthTab.uiType"  ),				SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyCustomerServiceObjTab.idStr"  ),		SQL_CHAR,	},			//	6
	MACRO_simpleUsrSqlColumnsEx(  "qyImObjRegInfoTab"  )
	{	6,	_T(  "qyCustomerServiceObjTab.uiLangId"  ),		SQL_INTEGER,	},
	{	6,	_T(  "qyCustomerServiceObjTab.uiCategoryId"  ),	SQL_INTEGER,	},

	{	6,	_T(  "qyCustomerServiceObjTab.startIp"  ),		SQL_CHAR,	},
	{	6,	_T(  "qyCustomerServiceObjTab.endIp"  ),		SQL_CHAR,	},

	//
	{	-1,	NULL,											},
};

 QY_COLUMNINFO	 CONST_customerServiceListDisplayColumns_is[]  = 
{
	{	CONST_qyColumnDisplayType_long,		CONST_str_xuHao,				SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_objType,	CONST_str_leiXing,				SQL_INTEGER,	LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,	CONST_str_idStr,				SQL_CHAR,		LVCFMT_LEFT, 140,  1, 50,	},	//  1
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_langId,	CONST_str_yuYan,				SQL_CHAR,		LVCFMT_LEFT, 90,  0, 0, },	//  8					   
	{	CONST_qyColumnDisplayType_long,		CONST_str_category,				SQL_INTEGER,	LVCFMT_LEFT, 90,	1, 50,	},	//  13  

	{	CONST_qyColumnDisplayType_ip12,			CONST_str_startIp,				SQL_CHAR,		LVCFMT_LEFT, 100,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_ip12,			CONST_str_endIp,				SQL_CHAR,		LVCFMT_LEFT, 100,	1, 50,	},	//  13  

	{	-1,	NULL,														},
};



 QNM_QUERY_STRUCT  CONST_customerServiceListQueryStruct_is  =
{
	 CONST_customerServiceListSqlColumns_is,  CONST_customerServiceListDisplayColumns_is,
};


 //  2005/05/10, WwwQmCfg
 QY_COLUMNINFO  CONST_webContactListSqlColumns_is[]  =
{
	{	6,	_T(  "qyWebContactTab.id"  ),					SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyWebContactTab.ucbPublic"  ),			SQL_CHAR,	},
	{	6,	_T(  "qyImObjAuthTab.uiType"  ),			SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyWebContactTab.idStr"  ),				SQL_CHAR,	},			//	6
	//  {	6,	_T(  "qyWebContactTab.grpDisplayName"  ),		SQL_CHAR,	},
	{	6,	_T(  "qyWebContactTab.displayName"  ),		SQL_CHAR,	},
	MACRO_simpleUsrSqlColumnsEx(  "qyImObjRegInfoTab"  )
	//
	//  {	1,	_T(  "qyWebContactTab.tLastModifiedTime"  ),	SQL_CHAR,	},		//	1
	{	1,	_T(  "qyWebContactTab.iStatus"  ),			SQL_INTEGER,	},		//	1
	{	-1,	NULL,											},
};

 QY_COLUMNINFO	 CONST_webContactListDisplayColumns_is[]  = 
{
	{	CONST_qyColumnDisplayType_long,		CONST_str_xuHao,				SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_bool,		CONST_str_ucbPublic,			SQL_CHAR,		LVCFMT_LEFT, 80,1, 50, },
	{	CONST_qyColumnDisplayType_objType,	CONST_str_leiXing,				SQL_INTEGER,	LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,	CONST_str_idStr,				SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	//  {	CONST_qyColumnDisplayType_str,	CONST_str_grpDisplayName,		SQL_CHAR,		LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,		CONST_str_displayName,			SQL_CHAR,		LVCFMT_LEFT, 120,  1, 50,	},	//  1
	MACRO_zjgaSimpleUsrDisplayColumns
	//
	//  {	CONST_qyColumnDisplayType_time,		CONST_str_gengXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	CONST_qyColumnDisplayType_qyStatus,	CONST_str_zhuangTai,			SQL_CHAR,		LVCFMT_LEFT, 60,1, 50, },
	{	-1,	NULL,														},
};



 QNM_QUERY_STRUCT  CONST_webContactListQueryStruct_is  =
{
	 CONST_webContactListSqlColumns_is,  CONST_webContactListDisplayColumns_is,
};

 
///////////


 QY_COLUMNINFO  CONST_ipKnowledgeListSqlColumns_is[]  =
{
	{	6,	_T(  "qyIpKnowledgeTab.id"  ),					SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyIpKnowledgeTab.uiType"  ),				SQL_INTEGER,		},		//	6
	{	6,	_T(  "qyIpKnowledgeTab.startIp"  ),				SQL_CHAR,		},		//	6
	{	6,	_T(  "qyIpKnowledgeTab.endIp"  ),					SQL_CHAR,		},		//	6
	{	6,	_T(  "qyIpKnowledgeTab.wLocation"  ),				SQL_CHAR,		},		//	6
	{	6,	_T(  "qyIpKnowledgeTab.iWeight"  ),				SQL_INTEGER,	},		//	6
	//
	//  {	1,	_T(  "ip2LocationTab.tLastModifiedTime"  ),	SQL_CHAR,	},		//	1
	{	-1,	NULL,											},
};

 QY_COLUMNINFO	 CONST_ipKnowledgeListDisplayColumns_is[]  = 
{
	{	CONST_qyColumnDisplayType_long,			CONST_str_xuHao,				SQL_INTEGER,	LVCFMT_LEFT, 0,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_pcCommType,	CONST_str_leiXing,				SQL_INTEGER,	LVCFMT_LEFT, 80,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_ip12,			CONST_str_startIp,				SQL_CHAR,		LVCFMT_LEFT, 100,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_ip12,			CONST_str_endIp,				SQL_CHAR,		LVCFMT_LEFT, 100,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,			CONST_str_wLocation,			SQL_CHAR,		LVCFMT_LEFT, 150,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_long,			CONST_str_iWeight,				SQL_INTEGER,	LVCFMT_LEFT, 80,	1, 50,	},	//  13  
	//
	//  {	CONST_qyColumnDisplayType_time,		CONST_str_gengXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	{	-1,	NULL,														},
};



 QNM_QUERY_STRUCT  CONST_ipKnowledgeListQueryStruct_is  =
{
	 CONST_ipKnowledgeListSqlColumns_is,  CONST_ipKnowledgeListDisplayColumns_is,
};


//////////////////////


 QY_COLUMNINFO  CONST_phoneGuestListSqlColumns_is[]  =
{
	{	6,	_T(  "qyPhoneGuestTab.id"  ),					SQL_INTEGER,	},		//	6
	MACRO_simpleUsrSqlColumnsEx(  "qyImOtherRegInfoTab"  )
	{	6,	_T(  "qyPhoneGuestTab.misServName"  ),			SQL_CHAR,		},		//	6
	{	6,	_T(  "qyPhoneGuestTab.uiDevType"  ),			SQL_INTEGER,		},		//	6
	{	6,	_T(  "qyPhoneGuestTab.wDevIdStr"  ),			SQL_CHAR,		},		//	6
	{	6,	_T(  "qyPhoneGuestTab.startTime"  ),			SQL_CHAR,		},		//	6
	//
	{	CONST_fieldId_zcbh0,	_T(  "qyImOtherRegInfoTab.col13"  ),			SQL_CHAR,	0,  0,  0,	},		
	{	CONST_fieldId_zyyt,		_T(  "qyImOtherRegInfoTab.col6"  ),			SQL_CHAR,	0,  0,  0,	},		//	6
	{	CONST_fieldId_lxdh,		_T(  "qyImOtherRegInfoTab.col7"  ),			SQL_CHAR,	0,  0,  0,	},		//	7
	{	CONST_fieldId_sydd,		_T(  "qyImOtherRegInfoTab.col10"  ),			SQL_CHAR,	0,  0,  0,	},		//	10
	{	CONST_fieldId_zcbh1,	_T(  "qyImOtherRegInfoTab.col14"  ),			SQL_CHAR,	0,  0,  1,	},		//	8
	{	CONST_fieldId_zcsm1,	_T(  "qyImOtherRegInfoTab.col15"  ),			SQL_CHAR,	0,  0,  1,	},		//	8
	{	CONST_fieldId_zcbh2,	_T(  "qyImOtherRegInfoTab.col16"  ),			SQL_CHAR,	0,  0,  2,	},		//	8
	{	CONST_fieldId_zcsm2,	_T(  "qyImOtherRegInfoTab.col17"  ),			SQL_CHAR,	0,  0,  2,	},		//	8
	{	0,						_T(  "qyImOtherRegInfoTab.tLastModifiedTime"  ),				SQL_CHAR,	0,  0,  0,	},		//	11
	{	-1,									},
};


 QY_COLUMNINFO	 CONST_phoneGuestListDisplayColumns_is[]  = 
{
	{	CONST_qyColumnDisplayType_long,			CONST_str_xuHao,				SQL_INTEGER,	LVCFMT_LEFT, 0,		1, 50,	},	//  13  
	MACRO_zjgaSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_str,			CONST_str_servName,				SQL_CHAR,		LVCFMT_LEFT, 0,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_objType,		CONST_str_leiXing,				SQL_INTEGER,	LVCFMT_LEFT, 80,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,			CONST_str_phoneNo,				SQL_CHAR,		LVCFMT_LEFT, 150,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_time,			CONST_str_startTime,			SQL_CHAR,		LVCFMT_LEFT, 120,	1, 50,	},	//  13  
	//
	{	CONST_qyColumnDisplayType_str,		CONST_str_ziChanBianHao,			SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },  
	{	CONST_qyColumnDisplayType_str,		CONST_str_zhuYaoYongTu,				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  6
	{	CONST_qyColumnDisplayType_str,		CONST_str_lianXiDianHua,			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  7					   
	{	CONST_qyColumnDisplayType_str,		CONST_str_shiYongDiDian,			SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//  10					   
	{	CONST_qyColumnDisplayType_str,		CONST_str_ziChanBianHao1,			SQL_CHAR,		LVCFMT_LEFT, 70,  0, 0, },	//  8					   
	{	CONST_qyColumnDisplayType_str,		CONST_str_ziChanShuoMing1,			SQL_CHAR,		LVCFMT_LEFT, 70,  0,  0, },	//  9					   
	{	CONST_qyColumnDisplayType_str,		CONST_str_ziChanBianHao2,			SQL_CHAR,		LVCFMT_LEFT, 70,  0, 0, },	//  8					   
	{	CONST_qyColumnDisplayType_str,		CONST_str_ziChanShuoMing2,			SQL_CHAR,		LVCFMT_LEFT, 70,  0,  0, },	//  9					   
	{	CONST_qyColumnDisplayType_time,		CONST_str_gengXinShiJian,			SQL_CHAR,		LVCFMT_LEFT, 130,  0,  0, },	//  9					   
	{	-1,	NULL,														},
};



 QNM_QUERY_STRUCT  CONST_phoneGuestListQueryStruct_is  =
{
	 CONST_phoneGuestListSqlColumns_is,  CONST_phoneGuestListDisplayColumns_is,
};

 
 ////////


 QY_COLUMNINFO  CONST_gsmModemListSqlColumns_isMgr[]  =
{
	{	6,	_T(  "qyVDevComTab.id"  ),					SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyVDevComTab.misServName"  ),			SQL_CHAR,		},		//	6
	{	6,	_T(  "qyVDevComTab.idStr"  ),				SQL_CHAR,		},		//	6
	MACRO_simpleUsrSqlColumnsEx(  "qyImObjRegInfoTab"  )
	{	6,	_T(  "qyVDevComTab.wDevIdStr"  ),			SQL_CHAR,	},
	{	6,	_T(  "qyVDevComTab.name"  ),				SQL_CHAR,		},
	{	6,	_T(  "qyVDevComTab.model"  ),				SQL_CHAR,		},
	{	6,	_T(  "qyVDevComTab.smsc"  ),				SQL_CHAR,		},
	
	{	6,	_T(  "qyVDevComTab.endTime"  ),				SQL_CHAR,		},		//	6
	//
	{	-1,									},
};


 QY_COLUMNINFO	 CONST_gsmModemListDisplayColumns_isMgr[]  = 
{
	{	CONST_qyColumnDisplayType_long,			CONST_str_xuHao,					SQL_INTEGER,	LVCFMT_LEFT, 0,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,			CONST_str_servName,					SQL_CHAR,		LVCFMT_LEFT, 0,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr_gsmServer,			SQL_CHAR,		LVCFMT_LEFT, 80,	1, 50,	},	//  13  
	MACRO_zjgaEventSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_str,			CONST_str_wDevIdStr,				SQL_CHAR,		LVCFMT_LEFT, 0,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,			CONST_str_name,						SQL_CHAR,		LVCFMT_LEFT, 45,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,			CONST_str_model,					SQL_CHAR,		LVCFMT_LEFT, 70,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,			CONST_str_smsc,						SQL_CHAR,		LVCFMT_LEFT, 90,		1, 50,	},	//  13  

	{	CONST_qyColumnDisplayType_time,			CONST_str_zuiXinShuaXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120,	1, 50,	},	//  13  
	//
	{	-1,	NULL,														},
};



 QNM_QUERY_STRUCT  CONST_gsmModemListQueryStruct_isMgr  =
{
	 CONST_gsmModemListSqlColumns_isMgr,	CONST_gsmModemListDisplayColumns_isMgr,
};

///////////////


 
 QY_COLUMNINFO  CONST_smContactListSqlColumns_isMgr[]  =
{
	{	6,	_T(  "qySmContactTab.id"  ),					SQL_INTEGER,	},		//	6
	{	6,	_T(  "qySmContactTab.ucbPublic"  ),				SQL_CHAR,		},
	{	6,	_T(  "qySmContactTab.misServName"  ),			SQL_CHAR,		},		//	6
	{	6,	_T(  "qySmContactTab.idStr"  ),					SQL_CHAR,		},		//	6
	{	6,	_T(  "qySmContactTab.ucbDefaultSmServer"  ),	SQL_CHAR,		},
	//	
	{	6,	_T(  "qySmContactTab.wDevIdStr"  ),				SQL_CHAR,	},
	{	6,	_T(  "qySmContactTab.cusName"  ),				SQL_CHAR,		},
	{	6,	_T(  "qySmContactTab.idStr_contact"  ),			SQL_CHAR,		},
	{	6,	_T(  "qySmContactTab.ucbDefault"  ),			SQL_CHAR,		},
	MACRO_simpleUsrSqlColumnsEx(  "qyImObjRegInfoTab"  )
	//
	{	-1,									},
};


 QY_COLUMNINFO	 CONST_smContactListDisplayColumns_isMgr[]  = 
{
	{	CONST_qyColumnDisplayType_long,			CONST_str_xuHao,				SQL_INTEGER,	LVCFMT_LEFT, 0,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_bool,			CONST_str_ucbPublic,			SQL_CHAR,		LVCFMT_LEFT, 70,1, 50, },
	{	CONST_qyColumnDisplayType_str,			CONST_str_servName,				SQL_CHAR,		LVCFMT_LEFT, 0,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr_gsmServer,		SQL_CHAR,		LVCFMT_LEFT, 80,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_bool,			CONST_str_ucbDefaultSmServer,	SQL_CHAR,		LVCFMT_LEFT, 130,1, 50, },
	//	
	{	CONST_qyColumnDisplayType_str,			CONST_str_wDevIdStr,			SQL_CHAR,		LVCFMT_LEFT, 60,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,			CONST_str_bieMing,				SQL_CHAR,		LVCFMT_LEFT, 45,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr_contact,		SQL_CHAR,		LVCFMT_LEFT, 80,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_bool,			CONST_str_ucbDefaultSmContact,	SQL_CHAR,		LVCFMT_LEFT, 105,1, 50, },
	MACRO_zjgaEventSimpleUsrDisplayColumns
	//
	{	-1,	NULL,														},
};



 QNM_QUERY_STRUCT  CONST_smContactListQueryStruct_isMgr  =
{
	 CONST_smContactListSqlColumns_isMgr,	CONST_smContactListDisplayColumns_isMgr,
};




 //////

 QY_COLUMNINFO  CONST_sharedDynBmpListSqlColumns_isMgr[]  =
{
	{	6,	_T(  "qyDynBmptab.id"  ),					SQL_INTEGER,	},		//	6
	MACRO_simpleUsrSqlColumnsEx(  "qyImObjRegInfoTab"  )
	{	6,	_T(  "qyDynBmpTab.idstr"  ),				SQL_CHAR,		},
	{	6,	_T(  "qyDynBmpTab.uiObjType"  ),			SQL_INTEGER,		},
	{	6,	_T(  "qyDynBmpTab.usIndex"  ),				SQL_INTEGER,		},
	{	6,	_T(  "qyDynBmpTab.name"  ),					SQL_CHAR,		},
	{	6,	_T(  "qyDynBmpTab.cusname"  ),				SQL_CHAR,		},
	//
	{	-1,									},
};


 QY_COLUMNINFO	 CONST_sharedDynBmpListDisplayColumns_isMgr[]  = 
{
	{	CONST_qyColumnDisplayType_long,			CONST_str_xuHao,				SQL_INTEGER,	LVCFMT_LEFT, 0,		1, 50,	},	//  13  
	MACRO_zjgaEventSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr,				SQL_CHAR,		LVCFMT_LEFT, 85,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_objType,		CONST_str_leiXing,				SQL_INTEGER,	LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_long,			_T(  "Index"  ),				SQL_INTEGER,	LVCFMT_LEFT, 60,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,			CONST_str_name,					SQL_CHAR,		LVCFMT_LEFT, 180,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,			CONST_str_bieMing,				SQL_CHAR,		LVCFMT_LEFT, 120,		1, 50,	},	//  13  
	//
	{	-1,	NULL,														},
};

 QNM_QUERY_STRUCT  CONST_sharedDynBmpListQueryStruct_isMgr  =
{
	CONST_sharedDynBmpListSqlColumns_isMgr,  CONST_sharedDynBmpListDisplayColumns_isMgr,
};


 //

 QY_COLUMNINFO  CONST_sharedDynBmpRuleListSqlColumns_isMgr[]  =
{
	{	6,	_T(  "qyDynBmpRuletab.id"  ),					SQL_INTEGER,	},		//	6
	{	6,	_T(  "qyDynBmpRuleTab.idstr"  ),				SQL_CHAR,		},
	MACRO_simpleUsrSqlColumnsEx(  "qyImObjRegInfoTab"  )
	{	6,	_T(  "qyDynBmpRuleTab.idStr_visitor"  ),			SQL_CHAR,	},
	{	6,	_T(  "qyImGrpInfoTab.name"  ),					SQL_CHAR,		},
	MACRO_simpleUsrSqlColumnsEx(  "B"  )
	{	6,	_T(  "qyDynBmpRuleTab.uiRuleCmd"  ),			SQL_INTEGER,	},
	//
	{	-1,									},
};


 QY_COLUMNINFO	 CONST_sharedDynBmpRuleListDisplayColumns_isMgr[]  = 
{
	{	CONST_qyColumnDisplayType_long,			CONST_str_xuHao,				SQL_INTEGER,	LVCFMT_LEFT, 0,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr_resource,		SQL_CHAR,		LVCFMT_LEFT, 120,		1, 50,	},	//  13  
	MACRO_zjgaEventSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr_visitor,		SQL_CHAR,		LVCFMT_LEFT, 120,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_str,			CONST_str_mingChen,				SQL_CHAR,		LVCFMT_LEFT, 85, 1, 50,	},	//  0
	MACRO_zjgaEventSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_ruleCmd,		CONST_str_ceLue,				SQL_INTEGER,	LVCFMT_LEFT, 80,  1, 50,	},	//  1
	//
	{	-1,	NULL,														},
};

 QNM_QUERY_STRUCT  CONST_sharedDynBmpRuleListQueryStruct_isMgr  =
{
	CONST_sharedDynBmpRuleListSqlColumns_isMgr,  CONST_sharedDynBmpRuleListDisplayColumns_isMgr,
};

//

 
 QY_COLUMNINFO  CONST_imObjRuleListSqlColumns_isMgr[]  =
{
	{	6,	_T(  "A.id"  ),						SQL_INTEGER,	},		//	6
	{	6,	_T(  "A.idstr"  ),					SQL_CHAR,		},
	MACRO_simpleUsrSqlColumnsEx(  "B"  )
	{	6,	_T(  "A.idStr_related"  ),			SQL_CHAR,	},
	{	6,	_T(  "A.uiRuleType"  ),				SQL_INTEGER,	},
	{	6,	_T(  "A.uiCmd"  ),					SQL_INTEGER,		},
	{	6,	_T(  "A.col0"  ),					SQL_CHAR,			},
	{	6,	_T(  "A.tLastModifiedTime"  ),		SQL_CHAR,			},
	//
	{	-1,									},
};


 QY_COLUMNINFO	 CONST_imObjRuleListDisplayColumns_isMgr[]  = 
{
	{	CONST_qyColumnDisplayType_long,			CONST_str_xuHao,				SQL_INTEGER,	LVCFMT_LEFT, 0,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr,				SQL_CHAR,		LVCFMT_LEFT, 120,		1, 50,	},	//  13  
	MACRO_zjgaEventSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr_related,		SQL_CHAR,		LVCFMT_LEFT, 120,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_ruleType,		CONST_str_leiXing,				SQL_INTEGER,	LVCFMT_LEFT, 200,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_ruleCmd,		CONST_str_ceLue,				SQL_INTEGER,	LVCFMT_LEFT, 80,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_miaoShu,				SQL_CHAR,		LVCFMT_LEFT, 100,  1,  50,  },
	{	CONST_qyColumnDisplayType_time,		CONST_str_gengXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	//
	{	-1,	NULL,														},
};

 QNM_QUERY_STRUCT  CONST_imObjRuleListQueryStruct_isMgr  =
{
	CONST_imObjRuleListSqlColumns_isMgr,  CONST_imObjRuleListDisplayColumns_isMgr,
};



  QY_COLUMNINFO  CONST_imObjRuleListSqlColumns_isClient[]  =
{
	{	6,	_T(  "A.id"  ),						SQL_INTEGER,	},		//	6
	{	6,	_T(  "A.idstr"  ),					SQL_CHAR,		},
	MACRO_simpleUsrSqlColumnsEx(  "B"  )
	{	6,	_T(  "A.idStr_related"  ),			SQL_CHAR,	},
	{	6,	_T(  "A.uiRuleType"  ),				SQL_INTEGER,	},
	{	6,	_T(  "A.uiCmd"  ),					SQL_INTEGER,		},
	{	6,	_T(  "A.col0"  ),					SQL_CHAR,			},
	{	6,	_T(  "A.tLastModifiedTime"  ),		SQL_CHAR,			},
	//
	{	-1,									},
};


 QY_COLUMNINFO	 CONST_imObjRuleListDisplayColumns_isClient[]  = 
{
	{	CONST_qyColumnDisplayType_long,			CONST_str_xuHao,				SQL_INTEGER,	LVCFMT_LEFT, 0,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr,				SQL_CHAR,		LVCFMT_LEFT, 0,		1, 50,	},	//  13  
	MACRO_zjgaEventSimpleUsrDisplayColumns
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr_related,		SQL_CHAR,		LVCFMT_LEFT, 120,		1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_ruleType,		CONST_str_leiXing,				SQL_INTEGER,	LVCFMT_LEFT, 200,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_ruleCmd,		CONST_str_ceLue,				SQL_INTEGER,	LVCFMT_LEFT, 160,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_miaoShu,				SQL_CHAR,		LVCFMT_LEFT, 100,  1,  50,  },
	{	CONST_qyColumnDisplayType_time,		CONST_str_gengXinShiJian,		SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50,	},	//  0
	//
	{	-1,	NULL,														},
};

 QNM_QUERY_STRUCT  CONST_imObjRuleListQueryStruct_isClient  =
{
	CONST_imObjRuleListSqlColumns_isClient,  CONST_imObjRuleListDisplayColumns_isClient,
};


 ///

  QY_COLUMNINFO	CONST_imTaskListSqlColumns[]  =  
{
	{	0,									_T(  "T.id"  ),						SQL_INTEGER,	},
	{	0,									_T(  "T.uiType"  ),					SQL_INTEGER,	},
	{	0,									_T(  "T.senderDesc"  ),				SQL_CHAR,		},
	{	0,									_T(  "T.receiverDesc"  ),			SQL_CHAR,		},
	{	0,									_T(  "T.iStatus"  ),				SQL_INTEGER,	},
	{	0,									_T(  "T.subject"  ),				SQL_CHAR,		},
	{	0,									_T(  "T.tSendTime"  ),				SQL_CHAR,		},  
	{	0,									_T(  "T.uiTranNo"  ),				SQL_INTEGER,	},
	{	0,									_T(  "T.tRecvTime"  ),				SQL_CHAR,		},
	{	0,									_T(  "T.content0"  ),				SQL_CHAR,		},
	{	0,									_T(  "T.idStr_send"  ),				SQL_CHAR,		},
	{	0,									_T(  "T.idStr_recv"  ),				SQL_CHAR,		},
	{	-1,									},
};

 QY_COLUMNINFO	CONST_imTaskListDisplayColumns[] = 
{
	{	CONST_qyColumnDisplayType_long,			CONST_str_xuHao,					SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_imTaskType,	CONST_str_leiXing,					SQL_CHAR,		LVCFMT_LEFT, 70,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_senderDesc,				SQL_CHAR,		LVCFMT_LEFT, 130,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_receiverDesc,				SQL_CHAR,		LVCFMT_LEFT, 130,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_imTaskStatus,	CONST_str_zhuangTai,				SQL_INTEGER,	LVCFMT_LEFT, 60,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_subject,					SQL_CHAR,		LVCFMT_LEFT, 130,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_time,			CONST_str_sendTime,					SQL_CHAR,		LVCFMT_LEFT, 130,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_long,			CONST_str_tranNo,					SQL_INTEGER,	LVCFMT_LEFT,  60,  1,  50,  },
	{	CONST_qyColumnDisplayType_time,			CONST_str_recvTime,					SQL_CHAR,		LVCFMT_LEFT, 130,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_content,					SQL_CHAR,		LVCFMT_LEFT, 130,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr_send,				SQL_CHAR,		LVCFMT_LEFT, 60,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr_recv,				SQL_CHAR,		LVCFMT_LEFT, 60,  1, 50,	},	//  1

		

	{	-1,																									},
};


 QNM_QUERY_STRUCT  CONST_imTaskListQueryStruct  =
{
	CONST_imTaskListSqlColumns,	CONST_imTaskListDisplayColumns,	
};


 QY_COLUMNINFO	CONST_imMsgListSqlColumns_isMgr[]  =  
{
	{	0,									_T(  "qyImMsgTab.id"  ),						SQL_INTEGER,	},
	{	0,									_T(  "qyImMsgTab.uiType"  ),					SQL_INTEGER,	},
	{	0,									_T(  "qyImMsgTab.senderDesc"  ),				SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.receiverDesc"  ),			SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.tSendTime"  ),				SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.content0"  ),				SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.content1"  ),				SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.content2"  ),				SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.content3"  ),				SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.content4"  ),				SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.idStr_send"  ),				SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.idStr_recv"  ),				SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.firstTime"  ),				SQL_CHAR,		},
	{	-1,									},
};

  QY_COLUMNINFO	CONST_imMsgListDisplayColumns_isMgr[] = 
{
	{	CONST_qyColumnDisplayType_long,			CONST_str_xuHao,					SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_pcCommType,	CONST_str_leiXing,					SQL_CHAR,		LVCFMT_LEFT, 70,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_senderDesc,				SQL_CHAR,		LVCFMT_LEFT, 130,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_receiverDesc,				SQL_CHAR,		LVCFMT_LEFT, 130,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_time,			CONST_str_sendTime,					SQL_CHAR,		LVCFMT_LEFT, 130,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_content,					SQL_CHAR,		LVCFMT_LEFT, 230,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_content,					SQL_CHAR,		LVCFMT_LEFT, 230,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_content,					SQL_CHAR,		LVCFMT_LEFT, 230,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_content,					SQL_CHAR,		LVCFMT_LEFT, 230,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_content,					SQL_CHAR,		LVCFMT_LEFT, 230,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr_send,				SQL_CHAR,		LVCFMT_LEFT, 60,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr_recv,				SQL_CHAR,		LVCFMT_LEFT, 60,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_time,			CONST_str_startTime,				SQL_CHAR,		LVCFMT_LEFT, 130,  1, 50,	},	//  1
	{	-1,																									},
};

 QNM_QUERY_STRUCT  CONST_imMsgListQueryStruct_isMgr  =
{
	CONST_imMsgListSqlColumns_isMgr,	CONST_imMsgListDisplayColumns_isMgr,	
};

   QY_COLUMNINFO	CONST_imMsgListSqlColumns_isClient[]  =  
{
	{	0,									_T(  "qyImMsgTab.id"  ),						SQL_INTEGER,	},
	{	0,									_T(  "qyImMsgTab.uiType"  ),					SQL_INTEGER,	},
	{	0,									_T(  "qyImMsgTab.senderDesc"  ),				SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.receiverDesc"  ),				SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.tSendTime"  ),					SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.Content0"  ),					SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.Content1"  ),					SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.Content2"  ),					SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.Content3"  ),					SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.Content4"  ),					SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.idStr_send"  ),				SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.idStr_recv"  ),				SQL_CHAR,		},
	{	0,									_T(  "qyImMsgTab.firstTime"  ),					SQL_CHAR,		},
	{	-1,									},
};


 QY_COLUMNINFO	CONST_imMsgListDisplayColumns_isClient[] = 
{
	{	CONST_qyColumnDisplayType_long,			CONST_str_xuHao,					SQL_INTEGER,	LVCFMT_LEFT, 0,	1, 50,	},	//  13  
	{	CONST_qyColumnDisplayType_pcCommType,	CONST_str_leiXing,					SQL_CHAR,		LVCFMT_LEFT, 70,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_senderDesc,				SQL_CHAR,		LVCFMT_LEFT, 130,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_receiverDesc,				SQL_CHAR,		LVCFMT_LEFT, 130,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_time,			CONST_str_sendTime,					SQL_CHAR,		LVCFMT_LEFT, 130,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_content,					SQL_CHAR,		LVCFMT_LEFT, 230,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_content,					SQL_CHAR,		LVCFMT_LEFT, 230,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_content,					SQL_CHAR,		LVCFMT_LEFT, 230,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_content,					SQL_CHAR,		LVCFMT_LEFT, 230,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_str,			CONST_str_content,					SQL_CHAR,		LVCFMT_LEFT, 230,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr_send,				SQL_CHAR,		LVCFMT_LEFT, 60,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr_recv,				SQL_CHAR,		LVCFMT_LEFT, 60,  1, 50,	},	//  1
	{	CONST_qyColumnDisplayType_time,			CONST_str_startTime,				SQL_CHAR,		LVCFMT_LEFT, 130,  1, 50,	},	//  1
	{	-1,																									},
};


 QNM_QUERY_STRUCT  CONST_imMsgListQueryStruct_isClient  =
{
	CONST_imMsgListSqlColumns_isClient,	CONST_imMsgListDisplayColumns_isClient,	
};



  //  
 QY_COLUMNINFO	CONST_imEventListSqlColumns_is[]  =  
{
	{	0,	_T(  "qyImEventTab.eventType"  ),		SQL_INTEGER,	},		//	0
	MACRO_simpleUsrSqlColumnsEx(  "B"  )
	{	6,	_T(  "qyImEventTab.detectedIp"  ),		SQL_CHAR,		},		//	6
	{	6,	_T(  "qyImEventTab.ip"  ),				SQL_CHAR,		},		//	6
	{	11,	_T(  "qyImEventTab.des0"  ),			SQL_CHAR,		},		//	11	为检查工具使用
	{	11,	_T(  "qyImEventTab.des1"  ),			SQL_CHAR,		},		//	11	为检查工具使用
	{	12, _T(  "qyImEventTab.usrName"  ),			SQL_CHAR,		},		//	12
	{	8,	_T(  "qyImEventTab.localEventTime"  ),	SQL_CHAR,		},		//	8
	{	7,	_T(  "qyImEventTab.cntEventTime"  ),	SQL_CHAR,		},		//	7
	{	9,	_T(  "qyImEventTab.idStr"  ),			SQL_CHAR,		},		//	9
	{	10,	_T(  "qyImEventTab.comment0"  ),		SQL_CHAR,		},		//	10
	{	-1,										},
};
 
 QY_COLUMNINFO	CONST_imEventListDisplayColumns_is[] = 
{
   {	CONST_qyColumnDisplayType_eventType,	CONST_str_event,				SQL_CHAR,		LVCFMT_LEFT, 120, 1, 50, },	//  0
   MACRO_zjgaEventSimpleUsrDisplayColumns
   {	CONST_qyColumnDisplayType_ip12,			CONST_str_detectedIp,			SQL_CHAR,		LVCFMT_LEFT, 105,1, 50, },	//	5
   {	CONST_qyColumnDisplayType_ip12,			_T(  "IP"  ),					SQL_CHAR,		LVCFMT_LEFT, 105,1, 50, },	//	5
   {	CONST_qyColumnDisplayType_str,			CONST_str_miaoShu,				SQL_CHAR,		LVCFMT_LEFT, 250,1, 50, },	//	5
   {	CONST_qyColumnDisplayType_str,			CONST_str_fuJiaMiaoShu,			SQL_CHAR,		LVCFMT_LEFT, 150,1, 50, },	//	5
   {	CONST_qyColumnDisplayType_str,			CONST_str_dengLvYongHu,			SQL_CHAR,		LVCFMT_LEFT, 80,1, 50, },	//	12
   {	CONST_qyColumnDisplayType_time,			CONST_str_benDiShiJian,			SQL_CHAR,		LVCFMT_LEFT, 110, 1, 50,	},	//	7
   {	CONST_qyColumnDisplayType_time,			CONST_str_guanLiZhongXinShiJian,SQL_CHAR,		LVCFMT_LEFT, 110, 1,	50,	},	//	6
   {	CONST_qyColumnDisplayType_idStr,		CONST_str_idStr,				SQL_CHAR,		LVCFMT_LEFT, 100,1, 50, },	//	8
   {	CONST_qyColumnDisplayType_str,			CONST_str_beiZhu,				SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },	//	9
   {	-1,																},
};


 QNM_QUERY_STRUCT  CONST_imEventListQueryStruct_is  =  
{
	 CONST_imEventListSqlColumns_is,	CONST_imEventListDisplayColumns_is,
};




  QY_COLUMNINFO	CONST_opEventListSqlColumns_is[]  =  
{
	{	0,	_T(  "qyImEventTab.eventType"  ),		SQL_INTEGER,	},		//	0
	{	6,	_T(  "qyImEventTab.usrName"  ),			SQL_CHAR,		},		//	6
	{	11,	_T(  "qyImEventTab.des0"  ),			SQL_CHAR,		},		//	11	为检查工具使用
	{	7,	_T(  "qyImEventTab.localEventTime"  ),	SQL_CHAR,		},		//	7
	{	6,	_T(  "qyImEventTab.dsnName"  ),			SQL_CHAR,		},	
	{	10,	_T(  "qyImEventTab.comment0"  ),		SQL_CHAR,		},		//	10
	{	-1,										},
};
 
 QY_COLUMNINFO	CONST_opEventListDisplayColumns_is[] = 
{
   {	CONST_qyColumnDisplayType_eventType,	CONST_str_event,				SQL_CHAR,		LVCFMT_LEFT, 120,	1,	50,		},	//  0
   {	CONST_qyColumnDisplayType_str,			CONST_str_yongHu,				SQL_CHAR,		LVCFMT_LEFT, 80,	1,	50,		},	//	12
   {	CONST_qyColumnDisplayType_str,			CONST_str_miaoShu,				SQL_CHAR,		LVCFMT_LEFT, 250,	1,	50,		},	//	5
   {	CONST_qyColumnDisplayType_time,			CONST_str_benDiShiJian,			SQL_CHAR,		LVCFMT_LEFT, 130,	1,	50,		},	//	6
   {	CONST_qyColumnDisplayType_str,			CONST_str_dsnName,				SQL_CHAR,		LVCFMT_LEFT, 80,	1,	50,		},	//	12
   {	CONST_qyColumnDisplayType_str,			CONST_str_beiZhu,				SQL_CHAR,		LVCFMT_LEFT, 80,	1,	50,		},	//	9
   {	-1,																},
};


 QNM_QUERY_STRUCT  CONST_opEventListQueryStruct_is  =  
{
	 CONST_opEventListSqlColumns_is,	CONST_opEventListDisplayColumns_is,
};



 QY_DMITEM  *  CONST_queryTable_mis  =  CONST_queryTable;


