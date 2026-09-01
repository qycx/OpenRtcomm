


#include	"stdafx.h"
#include	<tchar.h>

#include	"myresource_qisGuiPublic.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"isCmdConst.h"

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_is.h"


  QY_DMITEM  CONST_cusMenusTable_qisGuiPublic[]  =
{
	//{	CONST_resId_popupMenu,				(  TCHAR  *  )CONST_popupMenuTable_isCli,					},

	{	-1,		NULL,		},
};

 extern  QY_DMITEM  CONST_strTable_qisGuiPublic[];
 extern  QY_DMITEM  CONST_dlgTable_qisGuiPublic[];

 QY_DMITEM  CONST_cusResTable_qisGuiPublic[]  =
{
 	{	CONST_resType_str,						(  TCHAR  *  )CONST_strTable_qisGuiPublic,						},

	{	CONST_resType_dlg,						(  TCHAR  *  )CONST_dlgTable_qisGuiPublic,						},

 	{	CONST_resType_menu,						(  TCHAR  *  )CONST_cusMenusTable_qisGuiPublic,				},
	  {	CONST_resType_query,					(  TCHAR  *  )CONST_queryTable_mis,						},
	  {	CONST_resType_search,					(  TCHAR  *  )CONST_searchTable,						},
	  {	CONST_resType_columnInfo,				(  TCHAR  *  )CONST_columnInfoTable,				},
	{	-1,		NULL,		},
};
