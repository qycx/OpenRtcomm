

#include	"stdafx.h"
//  #include	"qyCommon.h"
#include	"qyCusResCommon.h"


extern  QY_DMITEM  CONST_cusResTable_bhb[];
extern  QY_DMITEM  CONST_cusResTable_netMc2[];
extern  QY_DMITEM  CONST_cusResTable_nms[];
extern  QY_DMITEM  CONST_cusResTable_secChk[];
extern  QY_DMITEM  CONST_cusResTable_assetMgr[];
//  extern  QY_DMITEM  CONST_cusResTable_isCli_default[];
extern  QY_DMITEM  CONST_cusResTable_isCli_noMfc[];
extern  QY_DMITEM  CONST_cusResTable_isCli_ts[];

extern  QY_DMITEM  CONST_cusResTable_isCliHelp[];
extern  QY_DMITEM  CONST_cusResTable_qyMessengerHelp[];
extern  QY_DMITEM  CONST_cusResTable_qisGuiPublic[];
extern  QY_DMITEM  CONST_cusResTable_qmdCliHelp[];




extern  QY_DMITEM  CONST_cusResTable_isMgr[];
extern  QY_DMITEM  CONST_cusResTable_statusTool[];
extern  QY_DMITEM  CONST_cusResTable_warningTool[];
//  extern  QY_DMITEM  CONST_cusResTable_rtcTool[];
extern  QY_DMITEM  CONST_cusResTable_vDevComs[];



 QY_DMITEM  CONST_qnmResTable[]  =
{
	{	CONST_resId_sys_bhb_intraMon,		(  TCHAR  *  )CONST_cusResTable_bhb,					},
	{	CONST_resId_sys_bhb_interMon,		(  TCHAR  *  )CONST_cusResTable_bhb,					},
	{	CONST_resId_sys_netMc2,				(  TCHAR  *  )CONST_cusResTable_netMc2,					},
	{	CONST_resId_sys_nms,				(  TCHAR  *  )CONST_cusResTable_nms,					},
	{	CONST_resId_sys_secChk,				(  TCHAR  *  )CONST_cusResTable_secChk,					},
	{	CONST_resId_sys_assetMgr,			(  TCHAR  *  )CONST_cusResTable_assetMgr,				},
	{	CONST_resId_sys_isCli_noMfc,		(  TCHAR  *  )CONST_cusResTable_isCli_noMfc,			},			//  2013/07/30
	{	CONST_resId_sys_isCli_ts,			(  TCHAR  *  )CONST_cusResTable_isCli_ts,				},		//  2007/03/07

	{	CONST_resId_sys_isCliHelp,			(  TCHAR  *  )CONST_cusResTable_isCliHelp,				},		//  2013/06/15
	{	CONST_resId_sys_qyMessengerHelp,	(  TCHAR  *  )CONST_cusResTable_qyMessengerHelp,		},
	{	CONST_resId_sys_qisGuiPublic,		(  TCHAR  *  )CONST_cusResTable_qisGuiPublic,			},		//  2015/07/02
	{	CONST_resId_sys_qmdCliHelp,			(  TCHAR  *  )CONST_cusResTable_qmdCliHelp,				},		//  2015/07/17

	{	CONST_resId_sys_isMgr,				(  TCHAR  *  )CONST_cusResTable_isMgr,					},		//  2007/03/07
	{	CONST_resId_app_statusTool,			(  TCHAR  *  )CONST_cusResTable_statusTool,				},
	{	CONST_resId_app_warningTool,		(  TCHAR  *  )CONST_cusResTable_warningTool,			},
	//  {	CONST_resId_app_rtcTool,			(  TCHAR  *  )CONST_cusResTable_rtcTool,			},
	{	CONST_resId_app_vDevComs,			(  TCHAR  *  )CONST_cusResTable_vDevComs,				},
	//
	{	-1,		NULL,		},
};


 extern  "C"  __declspec( dllexport )  void  *  getQnmResTable(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 return  (  void  *  )CONST_qnmResTable;
}

