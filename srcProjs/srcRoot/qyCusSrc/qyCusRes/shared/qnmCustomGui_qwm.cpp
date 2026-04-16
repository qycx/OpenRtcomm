
#include	"stdafx.h"
#include	<tchar.h>
//  #include	"qyCommon.h"
//  #include	"afxres.h"
//  #include	"resource_statusTool.h"

//  #include	"qyCusResCommon.h"
#include	"qyCusResPublic.h"
#include	"qyCusResTemp.h"
//
#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_netMc.h"

extern  QY_DMITEM			CONST_jqlxTable[];						//  2009/01/17


 QY_DMITEM  CONST_nullTable[]  =
{
	 {	-1,	},
};


#ifndef  CONST_str_localUsr		//  2005/11/27,  暂时用来充数，呵呵
		 #define		CONST_str_localUsr					_T(  "本单位用户"  )
#endif
#ifndef  CONST_str_otherUsr
		 #define		CONST_str_otherUsr					_T(  "其它单位用户"  )
#endif


 QY_DMITEM  CONST_zjgaYhlxTable[]  =
{
	{	0,							CONST_str_localUsr,		},
	{	CONST_qyStatType_others,	CONST_str_otherUsr,		},
	{	-1,							NULL,				},
};

 QY_DMITEM	gYhGrpTable[CONST_maxnYhGrpTable  +  1]	=
{
	{	-1,		},
};

 QY_DMITEM  gEventYhGrpTable[CONST_maxnYhGrpTable  +  1]  =
{
	{	-1,		},
};




  //  客户端的检查项, 2006/05/04
 QY_DMITEM  CONST_secChkEventTypeTable_qwm[]  =
{
 	{	CONST_qyEventType_secChk_recent,				CONST_str_secChk_recent,			},
	{	CONST_qyEventType_secChk_fileHistory,			CONST_str_secChk_fileHistory,				},
	{	CONST_qyEventType_secChk_cookie,				CONST_str_secChk_cookie,				},
	{	CONST_qyEventType_secChk_ieHistory,				CONST_str_secChk_ieHistory,				},
	{	CONST_qyEventType_secChk_shareDirectory,		CONST_str_secChk_shareDirectory,					},
	{	CONST_qyEventType_secChk_sharePrinter,			CONST_str_secChk_sharePrinter,				},
	{	CONST_qyEventType_secChk_rasPhoneBk,			CONST_str_secChk_rasPhoneBk,				    },
	{	CONST_qyEventType_secChk_proxyCfg,				CONST_str_secChk_proxyCfg,				},
	{	CONST_qyEventType_secChk_diskFile,				CONST_str_secChk_diskFile,					},
	{	CONST_qyEventType_secChk_diskFileDel,			CONST_str_secChk_diskFileDel,					},
	{	CONST_qyEventType_nm_onInternet,				CONST_str_nm_onInternet,			},
	{	-1,												NULL,					},
};


 QY_DMITEM  CONST_tableTable_qwm[]  =
{
	//  { 	CONST_resId_qnmEventTypeTable0,			(  TCHAR  *  )CONST_qnmEventTypeTable0,		},
	//  {	CONST_resId_qnmEventTypeTable_pc,		(  TCHAR  *  )CONST_qnmEventTypeTable_netMc2,		},
	//  {	CONST_resId_qnmEventTypeTable_op,		(  TCHAR  *  )CONST_qnmEventTypeTable_op,		},
	//  {	CONST_resId_qnmEventTypeTable_netDev,	(  TCHAR  *  )CONST_qnmEventTypeTable_nmsNetDev,	},
	{	CONST_resId_secChkEventTypeTable,			(  TCHAR  *  )CONST_secChkEventTypeTable_qwm,		},
	//  {	CONST_resId_ipScanOfficeLevelTable,		(  TCHAR  *  )CONST_ipScanOfficeLevelTable,	},
	{	CONST_resId_zjgaYhlxTable,					(  TCHAR  *  )CONST_zjgaYhlxTable,			},
	{	CONST_resId_gYhGrpTable,					(  TCHAR  *  )gYhGrpTable,					},
	{	CONST_resId_gEventYhGrpTable,				(  TCHAR  *  )gEventYhGrpTable,				},
	//  {	CONST_resId_qnmEventTypeTable_secChk,	(  TCHAR  *  )CONST_qnmEventTypeTable_secChk,	},
	{	CONST_resId_qyNullTable,					(  TCHAR  *  )CONST_nullTable,				},
	{	CONST_resId_jqlxTable,						(  TCHAR  *  )CONST_jqlxTable,					},
	{	-1,		NULL,		},
};


 QY_DMITEM  CONST_cusResTable_qwm[]  =
{
 	//  {	CONST_resType_str,						(  TCHAR  *  )CONST_strTable,						},
	{	CONST_resType_table,					(  TCHAR  *  )CONST_tableTable_qwm,				},
	{	-1,		NULL,		},
};


