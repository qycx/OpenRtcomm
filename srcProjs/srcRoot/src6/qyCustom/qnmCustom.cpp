
#include	"stdafx.h"
#include	<windows.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmCustom.h"
#include	"qnmCustomComm.h"


 QY_DMITEM  CONST_qyMcAppNameTable[]  =  
{
	{	CONST_qyCustomId_null,				(TCHAR*)_T(  "QyMc -清扬创新内网管理系统"  ),			},
	//{	CONST_qyCustomId_hgzh,				(TCHAR*)_T(  "QyMc -内网管理系统"  ),			},
	{	CONST_qyCustomId_shhg,				(TCHAR*)_T(  "QyMc -网络管理系统"  ),				},
	//{	CONST_qyCustomId_gab,				(TCHAR*)_T(  "QyMc -内网管理系统"  ),				},
	{	CONST_qyCustomId_zjga,				(TCHAR*)_T(  "QyMc -内网管理系统"  ),			},
	//{	CONST_qyCustomId_hbga,				(TCHAR*)_T(  "QyMc -内网管理系统"  ),		},
	//{	CONST_qyCustomId_sjs,				(TCHAR*)_T(  "QyMc -内网管理系统"  ),				},
	{	-1,									NULL,									},
};


  QY_DMITEM  CONST_qyMcAppNameTable_netMc2[]  =  
{
#if  0
	{	CONST_qyCustomId_null,				(TCHAR*)_T(  "QyMc -清扬创新内网管理系统"  ),			},
	{	CONST_qyCustomId_shhg,				(TCHAR*)_T(  "QyMc -业务管理网监控管理系统"  ),	},
#ifdef  __HZSJ__
	{	CONST_qyCustomId_zjga,				(TCHAR*)_T(  "QyMc -内网管理系统"  ),		},
#else
	{	CONST_qyCustomId_zjga,				(TCHAR*)_T(  "QyMc -内网管理系统"  ),		},
#endif  __HZSJ__
#endif 
	//
	{	-1,									NULL,									},
};




 QY_DMITEM	CONST_qyRegToolAppNameTable[]  =
{
	{	CONST_qyCustomId_null,  			(TCHAR*)_T(  "qyRegTool.exe"  ),			},
	//{	CONST_qyCustomId_hgzh,				(TCHAR*)_T(  "hgzsRegTool.exe"  ),			},
	{	CONST_qyCustomId_shhg,				(TCHAR*)_T(  "RegTool.exe"  ),			},
	//{	CONST_qyCustomId_gab,				(TCHAR*)_T(  "gabRegTool.exe"  ),			},
	{	CONST_qyCustomId_zjga,				(TCHAR*)_T(  "regTool.exe"  ),			},
	//{	CONST_qyCustomId_hbga,				(TCHAR*)_T(  "hbgaRegTool.exe"  ),			},
	//{	CONST_qyCustomId_sjs,				(TCHAR*)_T(  "sjsRegTool.exe"  ),			},
	{	-1,									NULL,						},
};



 extern  "C"  TCHAR  *  qyGetRegToolAppName(  )
{
	 int		iCustomId;
	 TCHAR	*	pAppName	=	NULL;

	 iCustomId  =  qyGetCustomId(  );
	 pAppName  =  qyGetDesByType(  CONST_qyRegToolAppNameTable,  iCustomId  );

	 return  pAppName  ?  pAppName  :  DEFAULT_regToolAppName;
}
 







