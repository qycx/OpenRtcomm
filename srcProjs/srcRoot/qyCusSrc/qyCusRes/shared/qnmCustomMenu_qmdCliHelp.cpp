


#include	"stdafx.h"
#include	<tchar.h>

#include	"myresource_qisGuiPublic.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"isCmdConst.h"

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_is.h"

 extern QY_DMITEM  CONST_strTable_qmdCliHelp[];


  QY_DMITEM  CONST_cusMenusTable_qmdCliHelp[]  =
{
	//{	CONST_resId_popupMenu,				(  TCHAR  *  )CONST_popupMenuTable_isCli,					},

	{	-1,		NULL,		},
};

   QY_DMITEM  CONST_dlgTable_qmdCliHelp[]  =
{
	{	-1,		NULL,		},
};


 QY_DMITEM  CONST_cusResTable_qmdCliHelp[]  =
{
 	{	CONST_resType_str,						(  TCHAR  *  )CONST_strTable_qmdCliHelp,						},

	{	CONST_resType_dlg,						(  TCHAR  *  )CONST_dlgTable_qmdCliHelp,						},

 	{	CONST_resType_menu,						(  TCHAR  *  )CONST_cusMenusTable_qmdCliHelp,				},
	  {	CONST_resType_query,					(  TCHAR  *  )CONST_queryTable_mis,						},
	  {	CONST_resType_search,					(  TCHAR  *  )CONST_searchTable,						},
	  {	CONST_resType_columnInfo,				(  TCHAR  *  )CONST_columnInfoTable,				},
	{	-1,		NULL,		},
};
