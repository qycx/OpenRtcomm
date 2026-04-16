
#include	"stdafx.h"
#include	<tchar.h>
//  #include	"qyCommon.h"
#include	"myresource_main.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"
#include	"isCmdConst.h"
 			
 //  字段定义，	第0列，	命令ID，		>-0,	有效
 //										-1,		表终止
 //										-2， 表Seperator
 //										当在-3,  表明有下级菜单
 //				第1行,	显示字符串的resId
 //				第2列,	在第0列为-2,	此值指向一下级菜单的Table
 //		







 //  对应每一个产品的菜单都归类为一个总表


 //  公用的一些表可以放在这个文件里  

 QY_DMITEM  CONST_menuTable_wenJian[]  =	//  2006/12/17
{
	{	ID_qyMgrSystems,		},
	{	-2,						},
	{	ID_qyCfgSystems,		},
	{	-2,						},
	{	ID_qySearch,			},
	{	ID_qyStat,				},
	{	-2,						},
	{	ID_qyImport,			},
	{	ID_qyExport,			},
	{	ID_qyClearUp,			},
	{	-2,						},
	{	ID_FILE_PRINT_SETUP,	},
	{	ID_FILE_PRINT,			},
	{	-2,						},
	//  {	ID_APP_EXIT,		},	//  2007/09/14, 因为OnClose(  )在客户端用来提供最小化，所以，需要用另一个菜单来使退出。
	{	ID_qyQuitMainWnd,		},
	{		-1,				},
};


 QY_DMITEM  CONST_menuTable_chaKan_netMc[]  =
{
	{	ID_VIEW_TOOLBAR,		},		//  MENUITEM "工具栏(&T)",                  
	{	ID_VIEW_STATUS_BAR,		},		//  MENUITEM "状态栏(&S)",                  
	{	-2,						},		//  MENUITEM SEPARATOR
#ifndef  __WINCE__
	{	ID_viewQnmStatus,		},		//  MENUITEM "系统状态窗(&Z)",   
#endif
	{	-2,						},		//  MENUITEM SEPARATOR
	{	ID_qyRefresh,			},		//  MENUITEM "刷新(&R)  F5",                
	{	-1,		NULL,			},
};

  QY_DMITEM	CONST_menuTable_chuangKou[]  =
 {
	{	ID_WINDOW_CASCADE,		},
	{	ID_WINDOW_TILE_HORZ,	},
	{	ID_WINDOW_ARRANGE,		},
	{	-1,		NULL,			},
 };

 QY_DMITEM  CONST_menuTable_bangZhu[]  =
 {
	{	ID_HELP,				},		//  MENUITEM "工具栏(&T)",   
	{	-2,						},
	{	ID_APP_ABOUT,			},		//  MENUITEM "状态栏(&S)",                               
	{	-1,		NULL,			},
 };




