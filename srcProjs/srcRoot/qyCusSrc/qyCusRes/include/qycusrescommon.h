

#ifndef  __QYCUSRESCOMMON_H__
#define  __QYCUSRESCOMMON_H__	//  {

#ifndef  __WINCE__
	#include	<sql.h>
#else

#define SQL_UNKNOWN_TYPE    0
#define SQL_CHAR            1
#define SQL_NUMERIC         2
#define SQL_DECIMAL         3
#define SQL_INTEGER         4
#define SQL_SMALLINT        5
#define SQL_FLOAT           6
#define SQL_REAL            7
#define SQL_DOUBLE          8
#if (ODBCVER >= 0x0300)
#define SQL_DATETIME        9
#endif
#define SQL_VARCHAR        12

#endif

#include	"qyDefs_open.h"
#include	"qyCusResPublic.h"
#include	"imCommType_defs.h"
#include	"qnmResDefs.h"
#include	"qyCusResTemp.h"

//  #include	"qnmCustomStr.h"


#ifndef		__OTHER__
	#define		MACRO_zjgaSimpleUsrSqlColumns													\
						/*  {	0,  _T(  "qyPcRegInfoTab.col0"  ),		SQL_CHAR,	},	//	0  */	\
						{	1,  _T(  "qyPcRegInfoTab.col2"  ),		SQL_CHAR,	},		/*	1  */	\
						{	2,  _T(  "qyPcRegInfoTab.col1"  ),		SQL_CHAR,	},	/*	2  */	\
						{	3,	_T(  "qyPcRegInfoTab.col3"  ),		SQL_CHAR,	},		/*	3  */	\
						{	4,	_T(  "qyPcRegInfoTab.col4"  ),		SQL_CHAR,	},		/*	4  */	

	#define		MACRO_zjgaEventSimpleUsrSqlColumns											\
						/*	{	1,	_T(  "qyPcEventTab.col0"  ),	SQL_CHAR,	},	//  1  */	\
						{	2,	_T(  "qyPcEventTab.col2"  ),		SQL_CHAR,	},	/*	2  */	\
						{	3,	_T(  "qyPcEventTab.col1"  ),		SQL_CHAR,	},	/*	3  */		\
						{	4,	_T(  "qyPcEventTab.col3"  ),		SQL_CHAR,	},	/*	4  */	\
						{	5,	_T(  "qyPcEventTab.col4"  ),		SQL_CHAR,	},	/*	5  */

	#define		MACRO_zjgaSimpleUsrDisplayColumns												\
						/*  {	CONST_qyColumnDisplayType_str,	_T(  "用户类型"  ),		SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },		//  0  */	\
						{	CONST_qyColumnDisplayType_str,	CONST_str_danWei,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  1  */	\
						{	CONST_qyColumnDisplayType_str,	CONST_str_qiTaDanWei,			SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },	/*  2  */	\
						{	CONST_qyColumnDisplayType_str,	CONST_str_buMen,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  3  */	\
						{	CONST_qyColumnDisplayType_str,	CONST_str_shiYongRen,			SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },		/*  4  */	

#else
	#define		MACRO_zjgaSimpleUsrSqlColumns													\
						/*  {	CONST_fieldId_yhlx,  _T(  "qyPcRegInfoTab.col0"  ),		SQL_CHAR,	0,	0,	0,	0,	},	//	0  */	\
						{	CONST_fieldId_zb,		_T(  "qyPcRegInfoTab.col11"  ),		SQL_CHAR,	0,	0,	4,	0,	},		/*	1  */	\
						{	CONST_fieldId_bb,		_T(  "qyPcRegInfoTab.col12"  ),		SQL_CHAR,	0,	0,	3,	0,	},		/*	1  */	\
						{	CONST_fieldId_dw,		_T(  "qyPcRegInfoTab.col2"  ),		SQL_CHAR,	0,	0,	2,	0,	},		/*	1  */	\
						{	CONST_fieldId_bm,		_T(  "qyPcRegInfoTab.col3"  ),		SQL_CHAR,	0,	0,	1,	0,	},		/*	3  */	\
						{	CONST_fieldId_syr,		_T(  "qyPcRegInfoTab.col4"  ),		SQL_CHAR,	0,	0,	0,	0,	},		/*	4  */	

	#define		MACRO_zjgaSimpleUsrInTab1SqlColumns													\
						/*  {	CONST_fieldId_yhlx,  _T(  "qyPcRegInfoTab1.col0"  ),	SQL_CHAR,	0,	0,	0,	0,	},	//	0  */	\
						{	CONST_fieldId_zb,		_T(  "qyPcRegInfoTab1.col11"  ),	SQL_CHAR,	0,	0,	4,	0,	},		/*	1  */	\
						{	CONST_fieldId_bb,		_T(  "qyPcRegInfoTab1.col12"  ),	SQL_CHAR,	0,	0,	3,	0,	},		/*	1  */	\
						{	CONST_fieldId_dw,		_T(  "qyPcRegInfoTab1.col2"  ),		SQL_CHAR,	0,	0,	2,	0,	},		/*	1  */	\
						{	CONST_fieldId_bm,		_T(  "qyPcRegInfoTab1.col3"  ),		SQL_CHAR,	0,	0,	1,	0,	},		/*	3  */	\
						{	CONST_fieldId_syr,		_T(  "qyPcRegInfoTab1.col4"  ),		SQL_CHAR,	0,	0,	0,	0,	},		/*	4  */	

	#define		MACRO_zjgaEventSimpleUsrSqlColumns											\
						/*	{	CONST_fieldId_yhlx,	_T(  "qyPcEventTab.col0"  ),		SQL_CHAR,	0,	0,	0,	0,	},	//  1  */	\
						{	CONST_fieldId_zb,	_T(  "qyPcEventTab.col5"  ),			SQL_CHAR,	0,	0,	4,	0,	},				\
						{	CONST_fieldId_bb,	_T(  "qyPcEventTab.col6"  ),			SQL_CHAR,	0,	0,	3,	0,	},				\
						{	CONST_fieldId_dw,	_T(  "qyPcEventTab.col2"  ),			SQL_CHAR,	0,	0,	2,	0,	},	/*	2  */	\
						{	CONST_fieldId_bm,	_T(  "qyPcEventTab.col3"  ),			SQL_CHAR,	0,	0,	1,	0,	},	/*	4  */	\
						{	CONST_fieldId_syr,	_T(  "qyPcEventTab.col4"  ),			SQL_CHAR,	0,	0,	0,	0,	},	/*	5  */


	#define		MACRO_zjgaSimpleUsrDisplayColumns												\
						/*  {	CONST_qyColumnDisplayType_str,	_T(  "用户类型"  ),		SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },		//  0  */	\
						{	CONST_qyColumnDisplayType_str,	CONST_str_zongBu,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  1  */	\
						{	CONST_qyColumnDisplayType_str,	CONST_str_benBu,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  1  */	\
						{	CONST_qyColumnDisplayType_str,	CONST_str_danWei,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  1  */	\
						{	CONST_qyColumnDisplayType_str,	CONST_str_buMen,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  3  */	\
						{	CONST_qyColumnDisplayType_str,	CONST_str_shiYongRen,			SQL_CHAR,		LVCFMT_LEFT, 110, 1, 50, },		/*  4  */	

	#define		MACRO_zjgaSimpleUsrDisplayColumns_en												\
						/*  {	CONST_qyColumnDisplayType_str,	_T(  "用户类型"  ),		SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },		//  0  */	\
						{	CONST_qyColumnDisplayType_str,	_T(  "Company"  ),			SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  1  */	\
						{	CONST_qyColumnDisplayType_str,	_T(  "Group"  ),			SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  1  */	\
						{	CONST_qyColumnDisplayType_str,	_T(  "Dept"  ),				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  1  */	\
						{	CONST_qyColumnDisplayType_str,	_T(  "Unit"  ),				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  3  */	\
						{	CONST_qyColumnDisplayType_str,	_T(  "User"  ),				SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },		/*  4  */	

	#define		MACRO_zjgaEventSimpleUsrDisplayColumns												\
						/*  {	CONST_qyColumnDisplayType_str,	_T(  "用户类型"  ),		SQL_CHAR,		LVCFMT_LEFT, 80, 1, 50, },		//  0  */	\
						{	CONST_qyColumnDisplayType_str,	CONST_str_zongBu,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  1  */	\
						{	CONST_qyColumnDisplayType_str,	CONST_str_benBu,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  1  */	\
						{	CONST_qyColumnDisplayType_str,	CONST_str_danWei,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  1  */	\
						{	CONST_qyColumnDisplayType_str,	CONST_str_buMen,				SQL_CHAR,		LVCFMT_LEFT, 70, 1, 50, },		/*  3  */	\
						{	CONST_qyColumnDisplayType_str,	CONST_str_shiYongRen,			SQL_CHAR,		LVCFMT_LEFT, 60, 1, 50, },		/*  4  */	
	

#endif



extern  QY_COLUMNINFO  CONST_zjgaSimpleUsrDisplayColumns[];

extern  QY_DMITEM  CONST_menuTable_wenJian[];
extern  QY_DMITEM  CONST_menuTable_chaKan_netMc[];
extern  QY_DMITEM  CONST_menuTable_chuangKou[];
extern  QY_DMITEM  CONST_ipScanOfficeLevelTable[];
extern  QY_DMITEM  CONST_menuTable_guanLi_netMc2[];
extern  QY_DMITEM  CONST_menuTable_guanLi_nms[];
extern  QY_DMITEM  CONST_menuTable_guanLi_secChk[];
extern  QY_DMITEM  CONST_menuTable_guanLi_assetMgr[];
extern  QY_DMITEM  CONST_menuTable_guanLi_misClient[];
extern  QY_DMITEM  CONST_menuTable_guanLi_misMgr[];

extern  QY_DMITEM  CONST_menuTable_chaKan_isMgr[];

extern  QY_DMITEM  CONST_menuTable_xiaoXiChaKan_misClient[];
extern  QY_DMITEM  CONST_menuTable_yongHuGuanLi_netMc2[];
extern  QY_DMITEM  CONST_menuTable_keHuDuanGuanLi_netMc2[];


extern  QY_DMITEM  CONST_nullTable[];
extern  QY_DMITEM  CONST_cusResTable_qwm[];
extern	QY_DMITEM  CONST_jqlxTable[];
extern  QY_DMITEM  CONST_qnmStopMonTable[];
extern	QY_DMITEM  CONST_qySystemIdTable[];
extern	QY_DMITEM  CONST_ucbDsnlessTable[];
extern	QY_DMITEM	myCONST_yhGrpTable_netMc[];
extern	QY_DMITEM	myCONST_eventYhGrpTable_netMc[];
extern	QY_DMITEM	myCONST_yhGrpTable_is[];
extern	QY_DMITEM	myCONST_eventYhGrpTable_is[];
//
extern  QY_DMITEM  CONST_zjgaYhlxTable[];
extern  QY_DMITEM  gYhGrpTable[CONST_maxnYhGrpTable  +  1];
extern  QY_DMITEM  gEventYhGrpTable[CONST_maxnYhGrpTable  +  1];
//

extern  QY_DMITEM  CONST_queryTypeTable_isClient[];		//  2013/07/30
extern  QY_DMITEM  CONST_imTaskTypeTable[];
extern  QY_DMITEM	CONST_ruleCmdTable_autoAnswer[];
extern  QY_DMITEM	CONST_ruleCmdTable_autoAnswer_av[];
extern  QY_DMITEM  CONST_qyStatusTable[];
//extern  QY_DMITEM	CONST_remoteVideoTable[];



extern  QY_DMITEM  CONST_objTypeTable[];
extern  QY_DMITEM  CONST_imGrpSubtypeTable[];
extern  QY_DMITEM  CONST_imGrpMemRoleTable[];		//  2015/07/29
//
extern  QY_DMITEM  CONST_imObjRoleTable[];		//  2015/07/29
//
extern  QY_DMITEM  CONST_ruleCmdTable[];
extern	QY_DMITEM  CONST_fieldIdTable[];			//  2008/12/28
extern	QY_DMITEM  CONST_qyCommTypeTable[];			//	2009/01/01	
//
#define		CONST_pcCommTypeTable		CONST_qyCommTypeTable
//
extern  QY_DMITEM  CONST_grpNameTable[];			//  2009/01/02
extern  QY_DMITEM  CONST_usRunningStatusTable[];	//  2009/01/08

extern  QY_DMITEM  CONST_ruleTypeTable_is[];
extern  QY_DMITEM  CONST_usLayoutTypeTable[];		//  2010/12/20
extern  QY_DMITEM  CONST_usLayoutTypeTable_resource[];		//  2010/12/20

#if  0
extern  QY_DMITEM  CONST_table_shareFullScreen[];		//  2012/11/03
extern  QY_DMITEM  CONST_table_startShareMediaFile[];		//  2012/11/03
extern  QY_DMITEM  CONST_table_startShareMediaDevice[];		//  2012/11/03
#endif

extern  QY_DMITEM  CONST_menuTable_conferenceWall[];
extern  QY_DMITEM		CONST_policyAvLevelTable_basic[];
extern  QY_DMITEM		CONST_policyAvLevelTable_standard[];
extern  QY_DMITEM		CONST_policyAvLevelTable_high[];
//
extern  QY_DMITEM 		CONST_policyAvLevelTable_mosaic_video[];		//  2014/11/15
extern  QY_DMITEM 		CONST_policyAvLevelTable_mosaic_resource[];		//  2014/12/01
//
extern  QY_DMITEM 		CONST_policyAvLevelTable_slave_video[];		//  2014/11/15
//
extern  QY_DMITEM		CONST_iTargetUsageTable[];
extern  QY_DMITEM		CONST_iAvgBitrateTable_h264_720p[];
extern  QY_DMITEM		CONST_iAvgBitrateTable_h264_1080p[];
extern  QY_DMITEM		CONST_iAvgBitrateTable_h265_720p[];
extern  QY_DMITEM		CONST_iAvgBitrateTable_h265_1080p[];


extern  QY_DMITEM  CONST_policyAvLevelTable_screen_basic[];
extern  QY_DMITEM  CONST_policyAvLevelTable_screen_standard[];
extern  QY_DMITEM  CONST_policyAvLevelTable_screen_high[];


//
#endif  //  }


