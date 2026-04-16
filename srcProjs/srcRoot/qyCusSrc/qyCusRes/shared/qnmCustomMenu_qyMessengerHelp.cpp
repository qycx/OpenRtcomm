


#include	"stdafx.h"
#include	<tchar.h>

#include	"myresource_main_qyMessengerHelp.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"isCmdConst.h"

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_is.h"

 extern QY_DMITEM  CONST_strTable_qyMessengerHelp[];
 extern QY_DMITEM  CONST_tableTable_misClientHelp[];
 extern  QY_DMITEM		CONST_dlgTable_qyMessengerHelp[];


 //
 extern  QY_DMITEM  CONST_mainMenuTable_isCli_noMfc[];


 


 //
  QY_DMITEM  *  CONST_mainMenuTable_qyMessengerHelp  =  CONST_mainMenuTable_isCli_noMfc;


  //
  QY_DMITEM  CONST_cusMenusTable_qyMessengerHelp[]  =
{
	{	CONST_resId_mainMenu,				(  TCHAR  *  )CONST_mainMenuTable_qyMessengerHelp,			},
	//
	//  {	CONST_resId_childFrmMenu,			(  TCHAR  *  )CONST_childFrmMenuTable_misClient,		},
	//
	{	CONST_resId_popupMenu,				(  TCHAR  *  )CONST_popupMenuTable_isCli,					},
	//
	//  {	CONST_resId_winceMenu,				(  TCHAR  *  )CONST_winCeMenuTable_misClient,			},			//  2010/04/13

	{	-1,		NULL,		},
};

  /*
  QY_DMITEM  CONST_dlgTable_qyMessengerHelp[]  =
{
	{	-1,		NULL,		},
};
*/


 QY_DMITEM  CONST_cusResTable_qyMessengerHelp[]  =
{
 	{	CONST_resType_str,						(  TCHAR  *  )CONST_strTable_qyMessengerHelp,						},
	//  2016/08/15
	{	CONST_resType_table,					(  TCHAR  *  )CONST_tableTable_misClientHelp,			},
	//
	{	CONST_resType_dlg,						(  TCHAR  *  )CONST_dlgTable_qyMessengerHelp,						},

 	{	CONST_resType_menu,						(  TCHAR  *  )CONST_cusMenusTable_qyMessengerHelp,				},
	  {	CONST_resType_query,					(  TCHAR  *  )CONST_queryTable_mis,						},
	  {	CONST_resType_search,					(  TCHAR  *  )CONST_searchTable,						},
	  {	CONST_resType_columnInfo,				(  TCHAR  *  )CONST_columnInfoTable,				},
	{	-1,		NULL,		},
};
