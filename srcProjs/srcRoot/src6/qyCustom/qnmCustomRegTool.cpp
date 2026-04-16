
#include	"stdafx.h"

#include	"qyPrecomp.h"

#include	<windows.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"myresource.h"
#include	"qyCommon.h"
#include	"qyGuiCommon.h"
#include	"qyWmComm.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommCommon.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qyLangCommProc.h"
#include	"qnmCustom.h"
#include	"qnmCustomGui.h"
#include	"qwmAllHints.h"
#include	"qyCusResPublic.h"
#include	"qnmResDefs.h"




//  定制注册界面的说明
//		pTable0 包括全部的控件列表
//		pCb*Tables包含对ComboBox的特定选项的界面改变，仅提供五个ComboBox, 其中pCb*Tables[n]指
//				选择第n项的界面改变
//		pCb*Tables[]的最后的一项必须为NULL
//
//  样例：
//		QY_IDCITEM  *  gpTable0		=	CONST_zjgaTable0;	//  总的控件列表
//		QY_IDCITEM  *  gpCb0Tables[]	=	{  NULL,  };
//		QY_IDCITEM  *  gpCb1Tables[]	=	{  NULL,  };
//		QY_IDCITEM  *  gpCb2Tables[]	=	{  NULL,  };
//		QY_IDCITEM  *  gpCb3Tables[]	=	{  NULL,  };
//		QY_IDCITEM  *  gpCb4Tables[]	=	{  NULL,  };
//
//  注：
//		对edit, 输入限制在pTable0中确定后，将不能在后面的pCb*Tables中改变
//


#ifndef  __WINCE__

 //  升级的界面布局	//  2003/09/13
 QY_IDCITEM  CONST_updateTable[]  =  
{
	{	IDC_title,			CONST_qyIdcType_static,  NULL,							0,				0,				NULL,					64,   63,  16,  192, 18,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgHide,																							NULL,  NULL,				-1,	},
	//  {	IDC_hint0,			CONST_qyIdcType_static,  NULL,							0,				0,				NULL,					64,   29,  41,  138, 9,		CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgHide,																							NULL,  NULL,				-1,	},
	//  {	IDC_hint1,			CONST_qyIdcType_static,  NULL,							0,				0,				NULL,					64,   17,  8, 264, 10,	CONST_qyIdcFlgPermitAll,																							NULL,  NULL,				-1,	},
	{	IDC_hint0,			CONST_qyIdcType_static,  NULL,							0,				0,				NULL,					64,   17,  8, 264, 10,	CONST_qyIdcFlgPermitAll,																							NULL,  NULL,				-1,	},
	{	IDC_PROGRESS_reg,	CONST_qyIdcType_progress,NULL,							0,				0,				NULL,					64,   17,  18, 186, 10,	CONST_qyIdcFlgHide,																									NULL,  NULL,				-1,	},
	{	IDOK,				CONST_qyIdcType_button,  NULL,							0,				0,				NULL,					64,   70,  33, 50,  14,	CONST_qyIdcFlgPermitAll,																							NULL,  NULL,				-1,	},
	{	IDCANCEL,			CONST_qyIdcType_button,  NULL,							0,				0,				NULL,					64,   196, 33, 50,  14,	CONST_qyIdcFlgPermitAll,																							NULL,  NULL,				-1,	},
	{	-1,																																																																													},
};


#ifdef  __SUPPORT_SECCHK__	//  2011/02/06

 //				  			// start by 2003/11/12
 QY_IDCITEM	 CONST_secChkTable0_smallScreen[]  =		//  主要为640  *  480做的布局，2005/08/20
{
	{	IDC_title,			CONST_qyIdcType_static,			NULL,							0,			0,					NULL,									64,		63,  18,  192, 18,	CONST_qyIdcFlgHide,										NULL,	NULL,				-1,	},
	{	IDC_hint0,			CONST_qyIdcType_static,			NULL,							0,			0,					NULL,									64,     30,  47,  138, 9,	CONST_qyIdcFlgHide,										NULL,   NULL,               -1, },
	//  {	IDC_STATIC0,		CONST_qyIdcType_static, 	_T(  " 输入单位名称:"  ),		0,			IDC_EDIT0,			NULL,									64,		17,  12,  71,  13,	CONST_qyIdcFlgPermitAll,								NULL,	NULL,				-1,	},
	//  {	IDC_EDIT0,			CONST_qyIdcType_edit,		NULL,							IDC_STATIC0,0,					NULL,									64,		103, 11,  132, 12,  CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitDigit,								NULL,	_T(  "edit单位"  ),			2,			CONST_fieldId_dw,	2,	},	//  2005/02/13增加了对fieldId
	{	IDC_STATIC0,		CONST_qyIdcType_static, 		_T(  " 单位:"  ),				0,			IDC_EDIT0,			NULL,									64,		17,  12,  31,  13,	CONST_qyIdcFlgPermitAll,								NULL,	NULL,				-1,	},
	{	IDC_EDIT0,			CONST_qyIdcType_edit,			NULL,							IDC_STATIC0,0,					NULL,									64,		63,  11,  40,  12,  CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitDigit,								NULL,	_T(  "edit单位"  ),			2,			CONST_fieldId_dw,	2,	},	//  2005/02/13增加了对fieldId
	{	IDC_STATIC2,		CONST_qyIdcType_static, 		_T(  " 部门:"  ),				0,			IDC_EDIT1,			NULL,									64,		123, 12,  31,  13,	CONST_qyIdcFlgPermitAll,								NULL,	NULL,				-1,	},
	{	IDC_EDIT1,			CONST_qyIdcType_edit,			NULL,							IDC_STATIC2,0,					NULL,									64,		169, 11,  40,  12,  CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitDigit,								NULL,	_T(  "edit部门"  ),			3,			CONST_fieldId_bm,	1,	},	//  2005/02/13增加了对fieldId
	{	IDC_STATIC3,		CONST_qyIdcType_static, 		_T(  " 使用人:"  ),				0,			IDC_EDIT2,			NULL,									64,		229, 12,  31,  13,	CONST_qyIdcFlgPermitAll,								NULL,	NULL,				-1,	},
	{	IDC_EDIT2,			CONST_qyIdcType_edit,			NULL,							IDC_STATIC3,0,					NULL,									64,		275, 11,  40,  12,  CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitDigit,								NULL,	_T(  "edit使用人"  ),		4,			CONST_fieldId_syr,	0,	},	//  2005/02/13增加了对fieldId
	{	IDC_STATIC_licenseHint,	CONST_qyIdcType_static,		NULL,							0,			0,					NULL,									64,		375, 12,  60,  12,	CONST_qyIdcFlgPermitAll,								NULL,	NULL,				-1,	},	 	//  2006/05/13	
	{	IDC_STATIC1,		CONST_qyIdcType_static, 		_T(  " 选择需要检查的项目:"  ),	0,			IDC_COMBO_secChk,	NULL,									64, 	16,  31,  83,  13,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNotForEdit,	NULL,	NULL,				-1,	},
	{	IDC_COMBO_secChk,	CONST_qyIdcType_combo,			NULL,							IDC_STATIC1,0,					CONST_resId_secChkEventTypeTable,		64,		103, 31,  132, 12,  CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNotForEdit,	NULL,	_T(  "combo诊断类型"  ),	-1,	},
	{	IDC_PROGRESS_reg,	CONST_qyIdcType_progress,		NULL,							0,			0,					NULL,									64,		260, 33,  110, 10,	CONST_qyIdcFlgHide,										NULL,	_T(  "进度条"  ),			-1,	},
	{	IDC_line,			CONST_qyIdcType_static,			NULL,							0,			0,					NULL,									64,     16,  3,   335, 24,	CONST_qyIdcFlgPermitAll,								NULL,   NULL,               -1, },
	//  {	IDC_line,			CONST_qyIdcType_static,		NULL,							0,			0,					NULL,									64,     16,  3,   261, 24,	CONST_qyIdcFlgPermitAll,								NULL,   NULL,               -1, },
	{	IDC_hint1,			CONST_qyIdcType_static, 		_T(  "检查进度:"  ),			0,			0,					NULL,									64,     20,  52,  281, 13,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNotForEdit,	NULL,  	_T(  "static结果"  ),       -1, },
	//  {	IDC_PROGRESS_reg,	CONST_qyIdcType_progress,	NULL,							0,			0,					NULL,									64,		93,  52,  176, 10,	CONST_qyIdcFlgHide,										NULL,	_T(  "进度条"  ),			-1,	},
	//  {	IDC_LIST_secChk,	CONST_qyIdcType_listBox,	NULL,							0,			0,					NULL,									64,		18,  65,  258, 147,	CONST_qyIdcFlgPermitAll,								NULL,	_T(  "listBox"  ),			-1,	},
	{	IDC_LIST_secChk,	CONST_qyIdcType_listBox,		NULL,							0,			0,					NULL,									64,		18,  65,  374, 170,	CONST_qyIdcFlgPermitAll,								NULL,	_T(  "listBox"  ),			-1,	},
	{	IDOK,				CONST_qyIdcType_button,			NULL,							0,			0,					NULL,									64, 	55,  48,  50,  14,	CONST_qyIdcFlgHide  |  CONST_qyIdcFlgOnlyForEdit,		NULL,	NULL,				-1,	},
	{	IDCANCEL,			CONST_qyIdcType_button,			NULL,							0,			0,					NULL,									64, 	179, 48,  50,  14,	CONST_qyIdcFlgHide  |  CONST_qyIdcFlgOnlyForEdit,		NULL,	NULL,				-1,	},
	{	-1,																																							},
 };


  QY_IDCITEM	 CONST_secChkTable0[]  =				//  为800  *  600以上做的布局，2005/08/20
{
	{	IDC_title,			CONST_qyIdcType_static,			NULL,								0,			0,					NULL,								64,		63,  18,  192, 18,	CONST_qyIdcFlgHide,										NULL,	NULL,				-1,	},
	{	IDC_hint0,			CONST_qyIdcType_static,			NULL,								0,			0,					NULL,								64,     30,  47,  138, 9,	CONST_qyIdcFlgHide,										NULL,   NULL,               -1, },
	//  {	IDC_STATIC0,		CONST_qyIdcType_static, 	_T(  " 输入单位名称:"  ),			0,			IDC_EDIT0,			NULL,								64,		17,  12,  71,  13,	CONST_qyIdcFlgPermitAll,								NULL,	NULL,				-1,	},
	//  {	IDC_EDIT0,			CONST_qyIdcType_edit,		NULL,								IDC_STATIC0,0,					NULL,								64,		103, 11,  132, 12,  CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitDigit,								NULL,	_T(  "edit单位"  ),			2,			CONST_fieldId_dw,	2,	},	//  2005/02/13增加了对fieldId
	{	IDC_STATIC0,		CONST_qyIdcType_static, 		_T(  " 单位:"  ),					0,			IDC_EDIT0,			NULL,								64,		17,  12,  31,  13,	CONST_qyIdcFlgPermitAll,								NULL,	NULL,				-1,	},
	{	IDC_EDIT0,			CONST_qyIdcType_edit,			NULL,								IDC_STATIC0,0,					NULL,								64,		63,  11,  40,  12,  CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitDigit,								NULL,	_T(  "edit单位"  ),			2,			CONST_fieldId_dw,	2,	},	//  2005/02/13增加了对fieldId
	{	IDC_STATIC2,		CONST_qyIdcType_static, 		_T(  " 部门:"  ),					0,			IDC_EDIT1,			NULL,								64,		123, 12,  31,  13,	CONST_qyIdcFlgPermitAll,								NULL,	NULL,				-1,	},
	{	IDC_EDIT1,			CONST_qyIdcType_edit,			NULL,								IDC_STATIC2,0,					NULL,								64,		169, 11,  40,  12,  CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitDigit,								NULL,	_T(  "edit部门"  ),			3,			CONST_fieldId_bm,	1,	},	//  2005/02/13增加了对fieldId
	{	IDC_STATIC3,		CONST_qyIdcType_static, 		_T(  " 使用人:"  ),					0,			IDC_EDIT2,			NULL,								64,		229, 12,  31,  13,	CONST_qyIdcFlgPermitAll,								NULL,	NULL,				-1,	},
	{	IDC_EDIT2,			CONST_qyIdcType_edit,			NULL,								IDC_STATIC3,0,					NULL,								64,		275, 11,  40,  12,  CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitDigit,								NULL,	_T(  "edit使用人"  ),		4,			CONST_fieldId_syr,	0,	},	//  2005/02/13增加了对fieldId
	{	IDC_STATIC_licenseHint,	CONST_qyIdcType_static,		NULL,								0,			0,					NULL,								64,		375, 12,  60,  12,	CONST_qyIdcFlgPermitAll,								NULL,	NULL,				-1,	},	 	//  2006/05/13	
	{	IDC_STATIC1,		CONST_qyIdcType_static, 		_T(  " 选择需要检查的项目:"  ),		0,			IDC_COMBO_secChk,	NULL,								64, 	16,  31,  93,  13,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNotForEdit,	NULL,	NULL,				-1,	},
	{	IDC_COMBO_secChk,	CONST_qyIdcType_combo,			NULL,								IDC_STATIC1,0,					CONST_resId_secChkEventTypeTable,	64,		113, 31,  132, 12,  CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNotForEdit,	NULL,	_T(  "combo诊断类型"  ),	-1,	},
	{	IDC_PROGRESS_reg,	CONST_qyIdcType_progress,		NULL,								0,			0,					NULL,								64,		260, 33,  206, 10,	CONST_qyIdcFlgHide,										NULL,	_T(  "进度条"  ),			-1,	},
	//  {	IDC_line,			CONST_qyIdcType_static,		NULL,								0,			0,					NULL,								64,     16,  3,   261, 24,	CONST_qyIdcFlgPermitAll,								NULL,   NULL,               -1, },
	{	IDC_line,			CONST_qyIdcType_static,			NULL,								0,			0,					NULL,								64,     16,  3,   335, 24,	CONST_qyIdcFlgPermitAll,								NULL,   NULL,               -1, },
	//  {	IDC_hint1,			CONST_qyIdcType_static, 	_T(  "检查进度:"  ),				0,			0,					NULL,								64,     20,  52,  73,  13,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNotForEdit,	NULL,  	_T(  "static结果"  ),       -1, },
	{	IDC_hint1,			CONST_qyIdcType_static, 		_T(  "检查进度:"  ),				0,			0,					NULL,								64,     20,  52,  273,  13,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNotForEdit,	NULL,  	_T(  "static结果"  ),       -1, },
	//  {	IDC_PROGRESS_reg,	CONST_qyIdcType_progress,	NULL,								0,			0,					NULL,								64,		93,  52,  176, 10,	CONST_qyIdcFlgHide,										NULL,	_T(  "进度条"  ),			-1,	},
	//  {	IDC_LIST_secChk,	CONST_qyIdcType_listBox,	NULL,								0,			0,					NULL,								64,		18,  65,  258, 147,	CONST_qyIdcFlgPermitAll,								NULL,	_T(  "listBox"  ),			-1,	},
	{	IDC_LIST_secChk,	CONST_qyIdcType_listBox,		NULL,								0,			0,					NULL,								64,		18,  65,  473, 197,	CONST_qyIdcFlgPermitAll,								NULL,	_T(  "listBox"  ),			-1,	},
	{	IDOK,				CONST_qyIdcType_button,			NULL,								0,			0,					NULL,								64, 	55,  48,  50,  14,	CONST_qyIdcFlgHide  |  CONST_qyIdcFlgOnlyForEdit,		NULL,	NULL,				-1,	},
	{	IDCANCEL,			CONST_qyIdcType_button,			NULL,								0,			0,					NULL,								64, 	179, 48,  50,  14,	CONST_qyIdcFlgHide  |  CONST_qyIdcFlgOnlyForEdit,		NULL,	NULL,				-1,	},
	{	-1,																																						},
 };

#endif  //  __SUPPORT_SECCHK__

#endif



//  
 QY_DMITEM  CONST_shhgRegYhlxTable[]  =
{
#if  0
	{	0,	_T(  "本单位用户"  ),		},
	{	1,	_T(  "外单位临时用户"  ),	},
#endif 
	//
	{	-1,	NULL,				},
};

 QY_DMITEM  CONST_shhgYhlxTable[]  =
{
#if  0
	{	0,							_T(  "本单位用户"  ),		},
	{	1,							_T(  "外单位临时用户"  ),	},
	{	CONST_qyStatType_others,	_T(  "未注册用户"  ),		},
#endif
	//
	{	-1,							NULL,				},
};


//  以下是的定制信息  {
/*
#if  DEFAULT_qyCustomId  ==  CONST_qyCustomId_shhg

 QRT_CUSTOM_INFO  qyCustomInfo  =  {  "业务管理网登记表"  ),  NULL,  NULL,  };


 QY_DMITEM  CONST_shhgJqlxTable[]  =
{
	{	0,							"微机",				},
	{	1,							"便携机",			},
	{   2,							"服务器",			},
	{	CONST_qyStatType_others,	"其它",				},
	{	-1,							NULL,				},
};


 QY_IDCITEM	 CONST_shhgTable0[]  =
{
	{	IDC_title,			CONST_qyIdcType_static,  NULL,							0,				0,				NULL,					64,   63,  16,  192, 18,	CONST_qyIdcFlgPermitAll,																							NULL,  NULL,				-1,	},
	{	IDC_hint0,			CONST_qyIdcType_static,  NULL,							0,				0,				NULL,					64,   29,  41,  138, 9,		CONST_qyIdcFlgPermitAll,																							NULL,  NULL,				-1,	},
	{	IDC_STATIC0,		CONST_qyIdcType_static,  "用户类型",					0,				IDC_COMBO0,		NULL,					64,	  19,  58,  40,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,																	NULL,  NULL,				-1,	},
	{	IDC_COMBO0,			CONST_qyIdcType_combo,   CONST_yhlx_bdwyh,				IDC_STATIC0,	0,				CONST_shhgRegYhlxTable,	64,	  70,  58,  77,  12,	CONST_qyIdcFlgPermitAll	 |	CONST_qyIdcFlgChkNotNull,																NULL,  "combo用户类型",		0,	},
	{	IDC_STATIC1,		CONST_qyIdcType_static,  "临时用户单位",					0,				IDC_EDIT0,		NULL,					64,   161, 58,  56,  14,	CONST_qyIdcFlgHide,																									NULL,  NULL,				-1,	},
	{   IDC_EDIT0,			CONST_qyIdcType_edit,    NULL,						    IDC_STATIC1,    0,				NULL,					64,   214, 58,  77,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgHide,																		NULL,  "edit单位名称",		1,	},
	{	IDC_STATIC2,		CONST_qyIdcType_static,  "关(处)名",					0,				IDC_EDIT1,		NULL,					64,   19,  75,  40,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,																	NULL,  NULL,				-1,	},
	{   IDC_EDIT1,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC2,    0,				NULL,					64,   70,  75,  77,  14,	CONST_qyIdcFlgChkNotNull |  CONST_qyIdcFlgPermitZw,																	NULL,  "edit关(处)名",		2,	},
	{	IDC_STATIC3,		CONST_qyIdcType_static,  "科室",						0,				IDC_EDIT2,		NULL,					64,   161, 75,  30,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,																	NULL,  NULL,				-1,	},
	{   IDC_EDIT2,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC3,    0,				NULL,					64,   214, 75,  77,  14,	CONST_qyIdcFlgChkNotNull |  CONST_qyIdcFlgPermitZw,																	NULL,  "edit科室",			3,	},
	{	IDC_STATIC4,		CONST_qyIdcType_static,  "用户姓名",					0,				IDC_EDIT3,		NULL,					64,   19,  93,  38,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,																	NULL,  NULL,				-1,	},
	{   IDC_EDIT3,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC4,    0,				NULL,					64,   70,  93,  77,  14,	CONST_qyIdcFlgChkNotNull |  CONST_qyIdcFlgPermitZw,																	NULL,  "edit用户姓名",		4,	},
	{	IDC_STATIC5,		CONST_qyIdcType_static,  "联系电话",					0,				IDC_EDIT4,		NULL,					64,   161, 93,  41,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,																	NULL,  NULL,				-1,	},
	{   IDC_EDIT4,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC5,    0,				NULL,					64,   214, 93,  77,  14,	CONST_qyIdcFlgChkNotNull |  CONST_qyIdcFlgPermitDigit | CONST_qyIdcFlgPermitComma  |  CONST_qyIdcFlgPermitSpace,	NULL,  "edit联系电话",		5,	},
	{	IDC_STATIC6,		CONST_qyIdcType_static,  "设备型号",					0,				IDC_EDIT5,		NULL,					64,   19,  111, 38,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,																	NULL,  NULL,				-1,	},
	{   IDC_EDIT5,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC6,    0,				NULL,					64,   70,  111, 77,  14,	CONST_qyIdcFlgChkNotNull |  CONST_qyIdcFlgPermitAlpha | CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitMinus,	NULL,  "edit设备型号",		6,	},
	{	IDC_STATIC7,		CONST_qyIdcType_static,  "设备序列号",					0,				IDC_EDIT6,		NULL,					64,   161, 111, 46,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,																	NULL,  NULL,				-1,	},
	{   IDC_EDIT6,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC7,    0,				NULL,					64,   214, 111, 77,  14,	CONST_qyIdcFlgChkNotNull |  CONST_qyIdcFlgPermitAlpha | CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitMinus,	NULL,  "edit设备序列号",	7,	},
	{	IDC_STATIC8,		CONST_qyIdcType_static,  "关产编号",					0,				IDC_EDIT7,		NULL,					64,   19,  129, 37,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,																	NULL,  NULL,				-1,	},
	{   IDC_EDIT7,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC8,    0,				NULL,					64,   70,  129, 77,  14,	CONST_qyIdcFlgChkNotNull |  CONST_qyIdcFlgPermitAlpha | CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitMinus,	NULL,  "edit关产编号",		8,	},
	{	IDC_STATIC9,		CONST_qyIdcType_static,  "使用地点",					0,				IDC_EDIT8,		NULL,					64,   161, 129, 43,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,																	NULL,  NULL,				-1,	},
	{   IDC_EDIT8,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC9,    0,				NULL,					64,   214, 129, 77,  14,	CONST_qyIdcFlgPermitAll	 |	CONST_qyIdcFlgChkNotNull  | CONST_qyIdcFlgPermitMinus,									NULL,  "edit使用地点",		9,	},
	{	IDC_STATIC10,		CONST_qyIdcType_static,  "机器类型",					0,				IDC_EDIT9,		NULL,					64,   19,  147, 41,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,																	NULL,  NULL,				-1,	},
	{   IDC_COMBO1,			CONST_qyIdcType_combo,   CONST_jqlx_wj,					IDC_STATIC10,   0,				CONST_shhgJqlxTable,	64,   70,  147, 77,  12,	CONST_qyIdcFlgChkNotNull |  CONST_qyIdcFlgPermitAlpha | CONST_qyIdcFlgPermitDigit,									NULL,  "combo机器类型",		10,	},
	{	IDC_STATIC11,		CONST_qyIdcType_static,  "主要用途",					0,				IDC_EDIT9,		NULL,					64,   161, 147, 42,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,																	NULL,  NULL,				-1,	},
	{   IDC_EDIT9,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC11,   0,				NULL,					64,   214, 147, 77,  14,	CONST_qyIdcFlgPermitAll	 |	CONST_qyIdcFlgChkNotNull,																NULL,  "edit主要用途",		11,	},
	{	IDC_hint1,			CONST_qyIdcType_static,  NULL,							0,				0,				NULL,					64,   17,  173, 264, 10,	CONST_qyIdcFlgPermitAll,																							NULL,  NULL,				-1,	},
	{	IDC_PROGRESS_reg,	CONST_qyIdcType_progress,NULL,							0,				0,				NULL,					64,   17,  183, 186, 10,	CONST_qyIdcFlgHide,																									NULL,  NULL,				-1,	},
	{	IDOK,				CONST_qyIdcType_button,  NULL,							0,				0,				NULL,					64,   70,  198, 50,  14,	CONST_qyIdcFlgPermitAll,																							NULL,  NULL,				-1,	},
	{	IDCANCEL,			CONST_qyIdcType_button,  NULL,							0,				0,				NULL,					64,   196, 198, 50,  14,	CONST_qyIdcFlgPermitAll,																							NULL,  NULL,				-1,	},
	{	-1,																																																																													},
};


 QY_IDCITEM  CONST_cb0Table0[]  =
{
	{	IDC_STATIC1,		CONST_qyIdcType_static,  "临时用户单位",				0,				IDC_EDIT0,		NULL,						64,   161, 58,  42,  14,	CONST_qyIdcFlgHide,											},
	{   IDC_EDIT0,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC1,    0,				NULL,						64,   214, 58,  77,  14,	CONST_qyIdcFlgHide,											},
	{	IDC_STATIC2,		CONST_qyIdcType_static,  "关(处)名",					0,				IDC_EDIT1,		NULL,						64,   19,  75,  40,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,			},
	{   IDC_EDIT1,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC2,    0,				NULL,						64,   70,  75,  77,  14,	CONST_qyIdcFlgPermitAll	 |	CONST_qyIdcFlgChkNotNull,		},
	{	IDC_STATIC3,		CONST_qyIdcType_static,  "科室",						0,				IDC_EDIT2,		NULL,						64,   161, 75,  30,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,			},
	{   IDC_EDIT2,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC3,    0,				NULL,						64,   214, 75,  77,  14,	CONST_qyIdcFlgPermitAll	 |	CONST_qyIdcFlgChkNotNull,		},
	{	IDC_STATIC6,		CONST_qyIdcType_static,  "设备型号",					0,				IDC_EDIT5,		NULL,						64,   19,  111, 38,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,																	NULL,  NULL,				-1,	},
	{   IDC_EDIT5,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC6,    0,				NULL,						64,   70,  111, 77,  14,	CONST_qyIdcFlgChkNotNull |  CONST_qyIdcFlgPermitAlpha | CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitMinus,	NULL,  "edit设备型号",		6,	},
	{	IDC_STATIC7,		CONST_qyIdcType_static,  "设备序列号",					0,				IDC_EDIT6,		NULL,						64,   161, 111, 46,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,																	NULL,  NULL,				-1,	},
	{   IDC_EDIT6,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC7,    0,				NULL,						64,   214, 111, 77,  14,	CONST_qyIdcFlgChkNotNull |  CONST_qyIdcFlgPermitAlpha | CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitMinus,	NULL,  "edit设备序列号",	7,	},
	{	IDC_STATIC8,		CONST_qyIdcType_static,  "关产编号",					0,				IDC_EDIT7,		NULL,						64,   19,  129, 37,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,																	NULL,  NULL,				-1,	},
	{   IDC_EDIT7,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC8,    0,				NULL,						64,   70,  129, 77,  14,	CONST_qyIdcFlgChkNotNull |  CONST_qyIdcFlgPermitAlpha | CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitMinus,	NULL,  "edit关产编号",		8,	},
		{	-1,																																						},
};

 
 QY_IDCITEM  CONST_cb0Table1[]  =
{
	{	IDC_STATIC1,		CONST_qyIdcType_static,  "临时用户单位",				0,				IDC_EDIT0,		NULL,						64,   161, 58,  42,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,			},
	{   IDC_EDIT0,			CONST_qyIdcType_edit,    NULL,					    IDC_STATIC1,    0,				NULL,						64,   214, 58,  77,  14,	CONST_qyIdcFlgPermitAll	 |	CONST_qyIdcFlgChkNotNull,		},
	{	IDC_STATIC2,		CONST_qyIdcType_static,  "关(处)名",				0,				IDC_EDIT1,		NULL,						64,   19,  75,  40,  14,	CONST_qyIdcFlgPermitAll,									},
	{   IDC_EDIT1,			CONST_qyIdcType_edit,    NULL,						IDC_STATIC2,    0,				NULL,						64,   70,  75,  77,  14,	CONST_qyIdcFlgPermitAll,									},
	{	IDC_STATIC3,		CONST_qyIdcType_static,  "科室",					0,				IDC_EDIT2,		NULL,						64,   161, 75,  30,  14,	CONST_qyIdcFlgPermitAll,									},
	{   IDC_EDIT2,			CONST_qyIdcType_edit,    NULL,						IDC_STATIC3,    0,				NULL,						64,   214, 75,  77,  14,	CONST_qyIdcFlgPermitAll,									},
	{	IDC_STATIC6,		CONST_qyIdcType_static,  "设备型号",				0,				IDC_EDIT5,		NULL,					64,   19,  111, 38,  14,	CONST_qyIdcFlgPermitAll,		},
	{   IDC_EDIT5,			CONST_qyIdcType_edit,    NULL,						IDC_STATIC6,    0,				NULL,					64,   70,  111, 77,  14,	CONST_qyIdcFlgPermitAlpha | CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitMinus,	},
	{	IDC_STATIC7,		CONST_qyIdcType_static,  "设备序列号",				0,				IDC_EDIT6,		NULL,					64,   161, 111, 46,  14,	CONST_qyIdcFlgPermitAll,		},
	{   IDC_EDIT6,			CONST_qyIdcType_edit,    NULL,						IDC_STATIC7,    0,				NULL,					64,   214, 111, 77,  14,	CONST_qyIdcFlgPermitAlpha | CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitMinus,	},
	{	IDC_STATIC8,		CONST_qyIdcType_static,  "关产编号",				0,				IDC_EDIT7,		NULL,					64,   19,  129, 37,  14,	CONST_qyIdcFlgPermitAll,		},
	{   IDC_EDIT7,			CONST_qyIdcType_edit,    NULL,						IDC_STATIC8,    0,				NULL,					64,   70,  129, 77,  14,	CONST_qyIdcFlgPermitAlpha | CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitMinus,	},
	{	-1,																																						},
};

 QY_IDCITEM	 CONST_shhgPcPropertiesTable0[]  =
{	 
	{	IDC_pc0,			CONST_qyIdcType_static,	 "用户类型",				0,				0,				NULL,						64,	  24,  31,  40,  9,		0,		0,  "用户类型尝试"	},
	{	IDC_pc1,			CONST_qyIdcType_static,  NULL,						0,				0,				NULL,						64,	  72,  31,  72,  9,		0,			},
	{	IDC_pc2,			CONST_qyIdcType_static,  "临时用户单位",			0,				0,				NULL,						64,   151, 32,  48,  9,		0,			},
	{   IDC_pc3,			CONST_qyIdcType_static,  NULL,					    0,				0,				NULL,						64,   201, 32,  72,  9,		0,			},
	{	IDC_pc4,			CONST_qyIdcType_static,  "关(处)名",				0,				0,				NULL,						64,   24,  42,  40,  9,		0,			},
	{   IDC_pc5,			CONST_qyIdcType_static,  NULL,						0,				0,				NULL,						64,   71,  42,  72,  9,		0,			},
	{	IDC_pc6,			CONST_qyIdcType_static,  "科室",					0,				0,				NULL,						64,   151, 42,  48,  9,		0,			},
	{   IDC_pc7,			CONST_qyIdcType_static,  NULL,						0,				0,				NULL,						64,   201, 42,  72,  9,		0,			},
	{	IDC_pc8,			CONST_qyIdcType_static,  "用户姓名",				0,				0,				NULL,						64,   24,  53,  38,  9,		0,			},
	{   IDC_pc9,			CONST_qyIdcType_static,  NULL,						0,				0,				NULL,						64,   71,  53,	72,  9,		0,			},
	{	IDC_pc10,			CONST_qyIdcType_static,  "联系电话",				0,				0,				NULL,						64,   151, 53,  48,  9,		0,			},
	{   IDC_pc11,			CONST_qyIdcType_static,  NULL,						0,				0,				NULL,						64,   201, 53,  72,  9,		0,			},
	{	IDC_pc12,			CONST_qyIdcType_static,  "设备型号",				0,				0,				NULL,						64,   24,  64,  38,  9,		0,			},
	{   IDC_pc13,			CONST_qyIdcType_static,  NULL,						0,				0,				NULL,						64,   71,  64,  72,  9,		0,			},
	{	IDC_pc14,			CONST_qyIdcType_static,  "设备序列号",				0,				0,				NULL,						64,   151, 64,  46,  9,		0,			},
	{   IDC_pc15,			CONST_qyIdcType_static,  NULL,						0,				0,				NULL,						64,   201, 64,  72,  9,		0,			},
	{	IDC_pc16,			CONST_qyIdcType_static,  "关产编号",				0,				0,				NULL,						64,   24,  75,  37,  9,		0,			},
	{   IDC_pc17,			CONST_qyIdcType_static,  NULL,						0,				0,				NULL,						64,   71,  75,  72,  9,		0,			},
	{	IDC_pc18,			CONST_qyIdcType_static,  "使用地点",				0,				0,				NULL,						64,   151, 75,  43,  9,		0,			},
	{   IDC_pc19,			CONST_qyIdcType_static,  NULL,						0,				0,				NULL,						64,   201, 75,  72,  9,		0,			},
	{	IDC_pc20,			CONST_qyIdcType_static,  "机器类型",				0,				0,				NULL,						64,   24,  86,  41,  9,		0,			},
	{   IDC_pc21,			CONST_qyIdcType_static,  NULL,						0,				0,				NULL,						64,   71,  86,  72,  9,		0,			},
	{	IDC_pc22,			CONST_qyIdcType_static,  "主要用途",				0,				0,				NULL,						64,   151, 86,  72,  9,		0,			},
	{	IDC_pc23,			CONST_qyIdcType_static,  NULL,						0,				0,				NULL,						64,   201, 86,  72,  9,		0,			},
	{	-1,																																																							},
};

// for test
QY_IDCITEM  *  gpTable0			=	CONST_shhgTable0;	//  总的控件列表
QY_IDCITEM  *  gpCb0Tables[]	=	{  CONST_cb0Table0,  CONST_cb0Table1,  NULL,  };
QY_IDCITEM  *  gpCb1Tables[]	=	{  NULL,  };
QY_IDCITEM  *  gpCb2Tables[]	=	{  NULL,  };
QY_IDCITEM  *  gpCb3Tables[]	=	{  NULL,  };
QY_IDCITEM  *  gpCb4Tables[]	=	{  NULL,  };

QY_IDCITEM  *  gpPcPropertiesTable  =  CONST_shhgPcPropertiesTable0;

#endif
*/
//  }  以上是的定制信息

//  以下是的定制信息  {
#if  1  //  DEFAULT_qyCustomId  ==  CONST_qyCustomId_zjga


QRT_CUSTOM_INFO  qyCustomInfo  =  {		_T(  "Welcome"  ),  NULL,  NULL,  };

#ifdef  __ZJST__
 QY_DMITEM  CONST_zjgaDwTable[]  = 
{
	{  0,	_T( 	_T(  "厅长"  ),  },
	{  1, 	_T(  "机要室"  ),  },
	{  2, 	_T(  "政治部"  ),  },
	{  3, 	_T(  "教训处"  ),  },
	{  4, 	_T(  "纪监处"  ),  },
	{  5, 	_T(  "警务警察"  ),  },
	{  6, 	_T(  "机关党委"  ),  },
	{  7, 	_T(  "审计室"  ),  },
	{  8, 	_T(  "老干处"  ),  },
	{  9, 	_T(  "办公室"  ),  },
	{  10,	_T(  "后勤处"  ),  },
	{  11,	_T(  "一处"  ),  },
	{  12,	_T(  "二处"  ),  },
	{  13,	_T(  "三处"  ),  },
	{  14,	_T(  "四处"  ),  },
	{  15,	_T(  "五处"  ),  },
	{  16,	_T(  "六处"  ),  },
	{  17,	_T(  "七处"  ),  },
	{  18,	_T(  "八处"  ),  },
	{  19,	_T(  "九处"  ),  },
	{  20,	_T(  "十处"  ),  },
	{  21,	_T(  "十一处"  ),  },
	{  22,	_T(  "十二处"  ),  },
	{  23,	_T(  "十三处"  ),  },
	{  24,	_T(  "十五处"  ),  },
	{  25,	_T(  "十六处"  ),  },
	{  26,	_T(  "十七处"  ),  },
	{  27,	_T(  "十八处"  ),  },
	{  28,	_T(  "十九处"  ),  },
	{  29,	_T(  "二十处"  ),  },
	{  30,	_T(  "高速公路支队"  ),  },
	{  31,	_T(  "报刊社"  ),  },
	{  32,	_T(  "省警察专科学校"  ),  },
	{  33,	_T(  "警察学会"  ),  },
	{  34,	_T(  "其它"  ),  },
	{  -1,	NULL,	},
};
#endif

#ifdef  __HZSJ__
 QY_DMITEM  CONST_zjgaDwTable[]  = 
{
	{  0, 	_T(  "局领导"  ),  },
	{  1, 	_T(  "办公室"  ),  },
	{  2, 	_T(  "指挥中心"  ),  },
	{  3, 	_T(  "政治部"  ),  },
	{  4, 	_T(  "纪委、监察室"  ),  },
	{  5, 	_T(  "后勤处"  ),  },
	{  6, 	_T(  "信息通信处"  ),  },
	{  7, 	_T(  "网监支队"  ),  },
	{  8, 	_T(  "法制处"  ),  },
	{  9, 	_T(  "禁毒支队"  ),  },
	{  10,	_T(  "经济犯罪侦查支队"  ),  },
	{  11,	_T(  "国内安全保卫支队"  ),  },
	{  12,	_T(  "经文保支队"  ),  },
	{  13,	_T(  "治安支队"  ),  },
	{  14,	_T(  "行动技术支队"  ),  },
	{  15,	_T(  "监管支队"  ),  },
	{  16,	_T(  "六处"  ),  },
	{  17,	_T(  "刑侦支队"  ),  },
	{  18,	_T(  "八处"  ),  },
	{  19,	_T(  "警校"  ),  },
	{  20,	_T(  "交警"  ),  },
	{  21,	_T(  "特警"  ),  },
	{  22,	_T(  "西湖风景名胜分局"  ),  },
	{  23,	_T(  "消防"  ),  },
	{  24,	_T(  "交通治安分局"  ),  },
	{  25,	_T(  "上城分局"  ),  },
	{  26,	_T(  "下城分局"  ),  },
	{  27,	_T(  "拱墅分局"  ),  },
	{  28,	_T(  "江干分局"  ),  },
	{  29,	_T(  "西湖分局"  ),  },
	{  30,	_T(  "滨江分局"  ),  },
	{  31,	_T(  "之江分局"  ),  },
	{  32,	_T(  "下沙分局"  ),  },
	{  33,	_T(  "萧山分局"  ),  },
	{  34,	_T(  "余杭分局"  ),  },
	{  35,	_T(  "富阳市局"  ),  },
	{  36,	_T(  "桐庐县局"  ),  },
	{  37,	_T(  "临安市局"  ),  },
	{  38,	_T(  "建德市局"  ),  },
	{  39,	_T(  "淳安县局"  ),  },
	{  40,	_T(  "其它"  ),  },
	{  -1,	NULL,	},
};
#endif


 QY_DMITEM  CONST_jqlxTable[]  =		//  2009/01/17. 实际是CONST_jqlxTable_qwm.
{
	{	CONST_jqlx_wj,		gAllHints.wj,	},
	{	CONST_jqlx_bxj,		gAllHints.bxj,	},
	{   CONST_jqlx_fwq,		gAllHints.fwq,	},
	{	CONST_jqlx_xxj,		gAllHints.xxj,	},
	{	-1,					NULL,			},
};


 QY_IDCITEM	 CONST_zjgaTable0[]  =
{
#if  0
	{	IDC_title,			CONST_qyIdcType_static,  NULL,							0,			0,			NULL,				64,		63,  21,  192, 18,	CONST_qyIdcFlgPermitAll,																																						NULL,	NULL,				-1,	},
	//  {	IDC_hint0,			CONST_qyIdcType_static,  NULL,							0,			0,			NULL,				64, 	30,  60,  138, 9,	CONST_qyIdcFlgPermitAll,																																					NULL,	NULL,				-1,	},
	{	IDC_hint0,			CONST_qyIdcType_static,  NULL,							0,			0,			NULL,				64, 	30,  60,  318, 24,	CONST_qyIdcFlgPermitAll,																																						NULL,	NULL,				-1,	},
	{	IDC_EDIT0,			CONST_qyIdcType_edit,	 CONST_yhlx_bdwyh,				0,			0,			NULL,				64, 	30,  47,  138, 12,	CONST_qyIdcFlgNeeded  |  CONST_qyIdcFlgHide,																																	NULL, 	_T(  "edit用户类型"  ),		0,		CONST_fieldId_yhlx,	0,	},
	//  2005/02/06加，以实现对单位的级数扩充
	{	IDC_STATIC11,		CONST_qyIdcType_static,  gAllHints.zb,					0,			0,			NULL,				64,		0,  0,  0,  0,		0,																																												NULL,	NULL,				-1,		CONST_fieldId_zb,	4,	},		
	{	IDC_EDIT11,			CONST_qyIdcType_edit,		_T(  ""  ),					IDC_STATIC11,0,			NULL,				64,		0,	0,  0,  0,		CONST_qyIdcFlgPermitDigit |  CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitMinus  |  CONST_qyIdcFlgPermitSpace,									NULL,	_T(  "edit总部"  ),			11,		CONST_fieldId_zb,	4,	},
	{	IDC_STATIC12,		CONST_qyIdcType_static,  gAllHints.bb,					0,			0,			NULL,				64,		0,  0,  0,  0,		0,																																												NULL,	NULL,				-1,		CONST_fieldId_bb,	3,	},		
	{	IDC_EDIT12,			CONST_qyIdcType_edit,		_T(  ""  ),					IDC_STATIC12,0,			NULL,				64,		0,	0,  0,  0,		CONST_qyIdcFlgPermitDigit |  CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitMinus  |  CONST_qyIdcFlgPermitSpace,									NULL,	_T(  "edit本部"  ),			12,		CONST_fieldId_bb,	3,	},
	//
#ifndef __OTHER__
	{	IDC_STATIC0,		CONST_qyIdcType_static,  gAllHints.dw,					0,			IDC_COMBO0,	NULL,				64, 	24,  79,  40,  14,	CONST_qyIdcFlgNeeded,																																							NULL,	NULL,				-1,		CONST_field_dw,		2,	},
	{	IDC_COMBO0,			CONST_qyIdcType_combo,   NULL,							IDC_STATIC0,0,			CONST_zjgaDwTable,	64,		75,  77,  77,  12,  CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgChkNotNull,																															NULL,	_T(  "combo单位"  ),		2,		CONST_field_dw,		2,	},
	{	IDC_STATIC1,		CONST_qyIdcType_static,  gAllHints.qtdw,				0,			IDC_EDIT1,	NULL,				64,		165, 79,  40,  14,	CONST_qyIdcFlgHide,																																								NULL,	NULL,				-1,		CONST_fieldId_qtdw,	2,	},
	{	IDC_EDIT1,			CONST_qyIdcType_edit,	 NULL,							IDC_STATIC1,0,			NULL,				64,		218, 77,  77,  12,	CONST_qyIdcFlgHide  |  CONST_qyIdcFlgPermitAll,																																	NULL,	_T(  "edit其他单位"  ),		1,		CONST_fieldId_qtdw,	2,	},
#else
	{	IDC_STATIC0,		CONST_qyIdcType_static,  gAllHints.dw,					0,			IDC_EDIT9,	NULL,				64,		24,  79,  40,  14,	CONST_qyIdcFlgNeeded,																																							NULL,	NULL,				-1,		CONST_fieldId_dw,	2,	},
	{	IDC_EDIT9,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC0,0,			NULL,				64,		75,  77,  77,  14,	CONST_qyIdcFlgChkNotNull  |  CONST_qyIdcFlgPermitDigit |  CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitMinus  |  CONST_qyIdcFlgPermitSpace,		NULL,	_T(  "edit单位"  ),			2,		CONST_fieldId_dw,	2,	},
#endif
	{	IDC_STATIC2,		CONST_qyIdcType_static,  gAllHints.bm,					0,			IDC_EDIT2,	NULL,				64,		24,  97,  40,  14,	CONST_qyIdcFlgNeeded,	  																																						NULL,	NULL,				-1,		CONST_fieldId_bm,	1,	},
	{	IDC_EDIT2,			CONST_qyIdcType_edit,	 NULL,							IDC_STATIC2,0,			NULL,				64,		75,  95,  77,  14,	CONST_qyIdcFlgChkNotNull  |  CONST_qyIdcFlgPermitDigit |  CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitMinus  |  CONST_qyIdcFlgPermitSpace,		NULL,	_T(  "edit部门"  ),			3,		CONST_fieldId_bm,	1,	},
	{  	IDC_STATIC3,		CONST_qyIdcType_static,  gAllHints.syr,					0,			IDC_EDIT3,	NULL,				64,		165, 97,  40,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded,																																NULL,	NULL,				-1,		CONST_fieldId_syr,	0,	},
	{	IDC_EDIT3,			CONST_qyIdcType_edit,	 NULL,							IDC_STATIC3,0,			NULL,				64,		218, 95,  77,  14,	CONST_qyIdcFlgChkNotNull  |  CONST_qyIdcFlgPermitDigit |  CONST_qyIdcFlgPermitZw  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitMinus  |  CONST_qyIdcFlgPermitSpace,		NULL,	_T(  "edit使用人"  ),		4,		CONST_fieldId_syr,	0,	},

	{	IDC_STATIC4,		CONST_qyIdcType_static,  gAllHints.jqlx,				0,			IDC_COMBO1,	NULL,				64,		24,  115, 40,  14,	CONST_qyIdcFlgPermitAll,																																						NULL,	NULL,				-1,	},
	{	IDC_COMBO1,			CONST_qyIdcType_combo,   CONST_jqlx_wj,					IDC_STATIC4,0,			CONST_resId_jqlxTable,64,		75,  113, 77,  12,  CONST_qyIdcFlgPermitAll,																																					NULL,	_T(  "combo机器类型"  ),	5,		CONST_fieldId_jqlx,	0,	}, 
	//
	{	IDC_STATIC13,		CONST_qyIdcType_static,  gAllHints.zcbh,					0,			0,			NULL,				64,		0,  0,  0,  0,		CONST_qyIdcFlgNeeded,																																						NULL,	NULL,				-1,		CONST_fieldId_zcbh0,0,	},		
	{	IDC_EDIT13,			CONST_qyIdcType_edit,		_T(  ""  ),							IDC_STATIC13,0,			NULL,				64,		0,	0,  0,  0,		CONST_qyIdcFlgChkNotNull  |  CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitMinus,														NULL,	_T(  "edit资产编号"  ),		13,		CONST_fieldId_zcbh0,0,	},
	//
	{	IDC_STATIC5,		CONST_qyIdcType_static,  gAllHints.zyyt,				0,			IDC_EDIT4,	NULL,				64,		165, 115, 40,  14,	CONST_qyIdcFlgPermitAll,																															NULL,	NULL,				-1,	},
	{	IDC_EDIT4,			CONST_qyIdcType_edit,	 NULL,							IDC_STATIC5,0,			NULL,				64,		218, 113, 77,  12,	CONST_qyIdcFlgPermitAll,																															NULL,	_T(  "edit主要用途"  ),		6,		CONST_fieldId_zyyt,	0,	}, 
	{	IDC_STATIC6,		CONST_qyIdcType_static,  gAllHints.lxdh,				0,			IDC_EDIT5,	NULL,				64,		24,  133, 40,  14,	CONST_qyIdcFlgPermitAll,																															NULL,	NULL,				-1,	},
	{	IDC_EDIT5,			CONST_qyIdcType_edit,	 NULL,							IDC_STATIC6,0,			NULL,				64,		75,  131, 77,  14,	CONST_qyIdcFlgPermitDigit | CONST_qyIdcFlgPermitComma  |  CONST_qyIdcFlgPermitSpace  |  CONST_qyIdcFlgPermitMinus,									NULL,	_T(  "edit联系电话"  ),		7,		CONST_fieldId_lxdh,	0,	},
#ifdef __ZJST__
	{	IDC_STATIC7,		CONST_qyIdcType_static, 	_T(  "手机虚拟号"  ),					0,			IDC_EDIT6,	NULL,				64,		165, 133, 49,  14,	CONST_qyIdcFlgPermitAll,																															NULL,	NULL,				-1,	},
	{	IDC_EDIT6,			CONST_qyIdcType_edit,	 NULL,							IDC_STATIC7,0,			NULL,				64,		218, 131, 77,  14,	CONST_qyIdcFlgPermitDigit | CONST_qyIdcFlgPermitComma  |  CONST_qyIdcFlgPermitSpace,																NULL,	_T(  "edit手机虚拟号"  ),	8,	},
//	{	IDC_STATIC8,		CONST_qyIdcType_static,  "搬迁前地点"  ),					0,			IDC_EDIT7,	NULL,				64,		24,  151, 49,  14,	CONST_qyIdcFlgPermitAll,																															NULL,	NULL,				-1,	},
//	{	IDC_EDIT7,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC8,0,			NULL,				64,		75,  149, 77,  14,	CONST_qyIdcFlgPermitAll,																															NULL,	_T(  "edit搬迁前地点"  ),	9,	},
//	{	IDC_STATIC9,		CONST_qyIdcType_static,  "搬迁后地点"  ),					0,			IDC_EDIT8,	NULL,				64,		165, 151, 49,  14,	CONST_qyIdcFlgPermitAll,																															NULL,	NULL,				-1,	},
//	{	IDC_EDIT8,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC9,0,			NULL,				64,		218, 149, 77,  14,	CONST_qyIdcFlgPermitAll,																															NULL,	_T(  "edit搬迁后地点"  ),	10,	},
	{	IDC_STATIC8,		CONST_qyIdcType_static,  "备注2"  ),					0,			IDC_EDIT7,	NULL,					64,		24,  151, 49,  14,	CONST_qyIdcFlgHide,																																	NULL,	NULL,				-1,	},
	{	IDC_EDIT7,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC8,0,			NULL,				64,		75,  149, 77,  14,	CONST_qyIdcFlgPermitAll | CONST_qyIdcFlgHide,																										NULL,	_T(  "edit搬迁前地点"  ),	9,	},
//	{	IDC_STATIC9,		CONST_qyIdcType_static,  "使用地点"  ),					0,			IDC_EDIT8,	NULL,				64,		165, 151, 49,  14,	CONST_qyIdcFlgPermitAll,																															NULL,	NULL,				-1,	},
//	{	IDC_EDIT8,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC9,0,			NULL,				64,		218, 149, 77,  14,	CONST_qyIdcFlgPermitAll,																															NULL,	_T(  "edit搬迁后地点"  ),	10,	},
	{	IDC_STATIC9,		CONST_qyIdcType_static,  "使用地点"  ),					0,			IDC_EDIT8,	NULL,				64,		24,  151, 49,  14,	CONST_qyIdcFlgPermitAll,																															NULL,	NULL,				-1,	},
	{	IDC_EDIT8,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC9,0,			NULL,				64,		75,  149, 220, 14,	CONST_qyIdcFlgPermitAll,																															NULL,	_T(  "edit搬迁后地点"  ),	10,	},
	{	IDC_hint1,			CONST_qyIdcType_static,  NULL,							0,			0,			NULL,				64, 	25,  178, 265, 10,	CONST_qyIdcFlgPermitAll,																															NULL,	NULL,				-1,	},
	{	IDC_PROGRESS_reg,	CONST_qyIdcType_progress,NULL,							0,			0,			NULL,				64, 	25,  188, 186, 10,	CONST_qyIdcFlgHide,																																	NULL,	NULL,				-1,	},
	{	IDOK,				CONST_qyIdcType_button,  NULL,							0,			0,			NULL,				64, 	229, 199, 50,  14,	CONST_qyIdcFlgPermitAll,																															NULL,	NULL,				-1,	},
	{	IDCANCEL,			CONST_qyIdcType_button,  NULL,							0,			0,			NULL,				64, 	199, 190, 50,  14,	CONST_qyIdcFlgHide,																																	NULL,	NULL,				-1,	},
#else
	{	IDC_STATIC9,		CONST_qyIdcType_static,  gAllHints.sydd,				0,			IDC_EDIT8,	NULL,				64,		24,  151, 49,  14,	CONST_qyIdcFlgPermitAll,																															NULL,	NULL,				-1,	},
	{	IDC_EDIT8,			CONST_qyIdcType_edit,    NULL,							IDC_STATIC9,0,			NULL,				64,		75,  149, 220, 14,	CONST_qyIdcFlgPermitAll,																															NULL,	_T(  "edit使用地点"  ),		10,		CONST_fieldId_sydd,	0,	},
	{	IDC_STATIC14,		CONST_qyIdcType_static,  gAllHints.zcbh1,				0,			0,			NULL,				64,		0,  0,  0,  0,		0,																																					NULL,	NULL,				-1,		CONST_fieldId_zcbh1,1,	},		
	{	IDC_EDIT14,			CONST_qyIdcType_edit,	 _T(  ""  ),							IDC_STATIC14,0,			NULL,				64,		0,	0,  0,  0,		CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitMinus,																NULL,	_T(  "edit资产编号1"  ),	14,		CONST_fieldId_zcbh1,1,	},
	{	IDC_STATIC15,		CONST_qyIdcType_static,  gAllHints.zcsm1,				0,			0,			NULL,				64,		0,  0,  0,  0,		0,																																					NULL,	NULL,				-1,		CONST_fieldId_zcsm1,1,	},		
	{	IDC_EDIT15,			CONST_qyIdcType_edit,	 _T(  ""  ),							IDC_STATIC15,0,			NULL,				64,		0,	0,  0,  0,		CONST_qyIdcFlgPermitAll,																															NULL,	_T(  "edit资产说明1"  ),	15,		CONST_fieldId_zcsm1,1,	},
	{	IDC_STATIC16,		CONST_qyIdcType_static,  gAllHints.zcbh2,				0,			0,			NULL,				64,		0,  0,  0,  0,		0,																																					NULL,	NULL,				-1,		CONST_fieldId_zcbh2,2,	},		
	{	IDC_EDIT16,			CONST_qyIdcType_edit,	 _T(  ""  ),							IDC_STATIC16,0,			NULL,				64,		0,	0,  0,  0,		CONST_qyIdcFlgPermitDigit  |  CONST_qyIdcFlgPermitAlpha  |  CONST_qyIdcFlgPermitMinus,																NULL,	_T(  "edit资产编号2"  ),	16,		CONST_fieldId_zcbh2,2,	},
	{	IDC_STATIC17,		CONST_qyIdcType_static,  gAllHints.zcsm2,				0,			0,			NULL,				64,		0,  0,  0,  0,		0,																																					NULL,	NULL,				-1,		CONST_fieldId_zcsm2,2,	},		
	{	IDC_EDIT17,			CONST_qyIdcType_edit,	 _T(  ""  ),							IDC_STATIC17,0,			NULL,				64,		0,	0,  0,  0,		CONST_qyIdcFlgPermitAll,																															NULL,	_T(  "edit资产说明2"  ),	17,		CONST_fieldId_zcsm2,2,	},
	//
	{	IDC_hint1,			CONST_qyIdcType_static,  NULL,							0,			0,			NULL,				64, 	25,  171, 265, 12,	CONST_qyIdcFlgPermitAll,																															NULL,	NULL,				-1,	},
	{	IDC_PROGRESS_reg,	CONST_qyIdcType_progress,NULL,							0,			0,			NULL,				64, 	25,  181, 186, 10,	CONST_qyIdcFlgHide,																																	NULL,	NULL,				-1,	},
	{	IDOK,				CONST_qyIdcType_button,  gAllHints.ok,					0,			0,			NULL,				64, 	75,  195, 50,  14,	CONST_qyIdcFlgPermitAll,																															NULL,	NULL,				-1,	},
	{	IDCANCEL,			CONST_qyIdcType_button,  gAllHints.cancel,				0,			0,			NULL,				64, 	199, 195, 50,  14,	CONST_qyIdcFlgPermitAll,																															NULL,	NULL,				-1,	},
#endif
	//
#endif 
	{	-1,																																						},
 };


 QY_IDCITEM  CONST_cb0Table0[]  =
{
	{	IDC_EDIT0,			CONST_qyIdcType_edit,	 CONST_yhlx_bdwyh,			0,				0,				NULL,					64, 30,	 47,  138, 9,	CONST_qyIdcFlgNeeded  |  CONST_qyIdcFlgHide,																		NULL,  _T(  "edit用户类型"  ),		0,	},
	{	IDC_STATIC1,		CONST_qyIdcType_static,  _T(  "其它单位"  ),				0,				IDC_EDIT1,		NULL,					64,	165, 64,  40,  14,	CONST_qyIdcFlgHide,																									NULL,	NULL,				-1,	},
	{	IDC_EDIT1,			CONST_qyIdcType_edit,	 NULL,						IDC_STATIC1,	0,				NULL,					64,	218, 64,  77,  12,	CONST_qyIdcFlgHide  |  CONST_qyIdcFlgPermitAll,																		NULL,	_T(  "edit其他单位"  ),		1,	},
	{	IDC_STATIC2,		CONST_qyIdcType_static,  _T(  "部门"  ),					0,				IDC_EDIT2,		NULL,					64,	24,  82,  40,  14,	CONST_qyIdcFlgPermitAll,	  																						NULL,	NULL,				-1,	},
	{	IDC_EDIT2,			CONST_qyIdcType_edit,	 NULL,						IDC_STATIC2,	0,				NULL,					64,	75,	 82,  77,  14,	CONST_qyIdcFlgPermitAll,																							NULL,	_T(  "edit科室"  ),			3,	},
	{	-1,																																											},
};


 QY_IDCITEM  CONST_cb0Table1[]  =
{
	{	IDC_EDIT0,			CONST_qyIdcType_edit,	 CONST_yhlx_bdwyh,			0,				0,				NULL,					64, 30,	 47,  138, 9,	CONST_qyIdcFlgNeeded  |  CONST_qyIdcFlgHide,																		NULL,  _T(  "edit用户类型"  ),		0,	},
	{	IDC_STATIC1,		CONST_qyIdcType_static,  _T(  "其它单位"  ),				0,				IDC_EDIT1,		NULL,					64,	165, 64,  40,  14,	CONST_qyIdcFlgHide,																									NULL,	NULL,				-1,	},
	{	IDC_EDIT1,			CONST_qyIdcType_edit,	 NULL,						IDC_STATIC1,	0,				NULL,					64,	218, 64,  77,  12,	CONST_qyIdcFlgHide  |  CONST_qyIdcFlgPermitAll,																		NULL,	_T(  "edit其他单位"  ),		1,	},
	{	IDC_STATIC2,		CONST_qyIdcType_static,  _T(  "部门"  ),					0,				IDC_EDIT2,		NULL,					64,	24,  82,  40,  14,	CONST_qyIdcFlgNeeded,	  																							NULL,	NULL,				-1,	},
	{	IDC_EDIT2,			CONST_qyIdcType_edit,	 NULL,						IDC_STATIC2,	0,				NULL,					64,	75,	 82,  77,  14,	CONST_qyIdcFlgChkNotNull  |  CONST_qyIdcFlgPermitDigit |  CONST_qyIdcFlgPermitZw,									NULL,	_T(  "edit部门"  ),			3,	},
	{	-1,																																											},
};


#ifdef  __ZJST__
 QY_IDCITEM  CONST_cb0Table34[]  =
{
	{	IDC_EDIT0,			CONST_qyIdcType_edit,	 CONST_yhlx_bdwyh,			0,				0,				NULL,					64, 30,	 47,  138, 9,	CONST_qyIdcFlgNeeded  |  CONST_qyIdcFlgHide,																		NULL,  "edit用户类型"  ),		0,	},
	{	IDC_STATIC1,		CONST_qyIdcType_static,  _T(  "其它单位"  ),				0,				IDC_EDIT1,		NULL,					64,	165, 64,  40,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded  ,																	NULL,	NULL,				-1,	},
	{	IDC_EDIT1,			CONST_qyIdcType_edit,	 NULL,						IDC_STATIC1,	0,				NULL,					64,	218, 64,  77,  12,	CONST_qyIdcFlgChkNotNull |  CONST_qyIdcFlgPermitAll,																NULL,	_T(  "edit其他单位"  ),		1,	},
	{	IDC_STATIC2,		CONST_qyIdcType_static,  _T(  "部门"  ),					0,				IDC_EDIT2,		NULL,					64,	24,  82,  40,  14,	CONST_qyIdcFlgPermitAll,	  																						NULL,	NULL,				-1,	},
	{	IDC_EDIT2,			CONST_qyIdcType_edit,	 NULL,						IDC_STATIC2,	0,				NULL,					64,	75,	 82,  77,  14,	CONST_qyIdcFlgPermitAll,																							NULL,	_T(  "edit部门"  ),			3,	},
	{	-1,																																													},
};
#endif

#ifdef  __HZSJ__
 QY_IDCITEM  CONST_cb0Table40[]  =
{
	{	IDC_EDIT0,			CONST_qyIdcType_edit,	 CONST_yhlx_bdwyh,			0,				0,				NULL,					64, 30,	 47,  138, 9,	CONST_qyIdcFlgNeeded  |  CONST_qyIdcFlgHide,																		NULL,  "edit用户类型"  ),		0,	},
	{	IDC_STATIC1,		CONST_qyIdcType_static,  _T(  "其它单位"  ),				0,				IDC_EDIT1,		NULL,					64,	165, 64,  40,  14,	CONST_qyIdcFlgPermitAll  |  CONST_qyIdcFlgNeeded  ,																	NULL,	NULL,				-1,	},
	{	IDC_EDIT1,			CONST_qyIdcType_edit,	 NULL,						IDC_STATIC1,	0,				NULL,					64,	218, 64,  77,  12,	CONST_qyIdcFlgChkNotNull |  CONST_qyIdcFlgPermitAll,																NULL,	_T(  "edit其他单位"  ),		1,	},
	{	IDC_STATIC2,		CONST_qyIdcType_static,  _T(  "部门"  ),					0,				IDC_EDIT2,		NULL,					64,	24,  82,  40,  14,	CONST_qyIdcFlgPermitAll,	  																						NULL,	NULL,				-1,	},
	{	IDC_EDIT2,			CONST_qyIdcType_edit,	 NULL,						IDC_STATIC2,	0,				NULL,					64,	75,	 82,  77,  14,	CONST_qyIdcFlgPermitAll,																							NULL,	_T(  "edit部门"  ),			3,	},
	{	-1,																																													},
};
#endif  





QY_IDCITEM  *  gpTable0			=	CONST_zjgaTable0;	//  总的控件列表
#ifdef  __ZJST__
QY_IDCITEM  *  gpCb0Tables[]	=	{  CONST_cb0Table0, CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table34,  NULL,  };
#endif
#ifdef  __HZSJ__
QY_IDCITEM  *  gpCb0Tables[]	=	{  CONST_cb0Table0, CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table1,  CONST_cb0Table40, NULL, };
#endif
#ifdef  __OTHER__
QY_IDCITEM  *  gpCb0Tables[]	=	{  NULL,  };
#endif
QY_IDCITEM  *  gpCb1Tables[]	=	{  NULL,  };
QY_IDCITEM  *  gpCb2Tables[]	=	{  NULL,  };
QY_IDCITEM  *  gpCb3Tables[]	=	{  NULL,  };
QY_IDCITEM  *  gpCb4Tables[]	=	{  NULL,  };

//  QY_IDCITEM  *  gpPcPropertiesTable  =  CONST_zjgaPcPropertiesTable0;

#endif	
//  }  以上是的定制信息









