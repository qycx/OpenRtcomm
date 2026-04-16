

#include	"stdafx.h"
#include	<windows.h>
#include	<tchar.h>
#include	<mmsystem.h>
#include	"qyCommon.h"
#include	"qyCommProc.h"
#include	"qyLangCommProc.h"
#include	"tmpCeLib.h"
#include	"qmOpenCommon.h"
#include	"makeDynaMenu.h"



 //  2012/05/23
 //  extern  "C"  HMENU  newSubMenu(  QNM_CUSRES_INFO  *  pResInfo,  QY_DMITEM  *  pTable,  PF_commonHandler  pf,  void  *  p0  )
extern  "C"  HMENU  newSubMenu(  QNM_CUSRES_INFO  *  pResInfo,  QY_DMITEM  *  pTable,  PF_getMenuStatus  pf,  QY_MC  *  pQyMc,  void  *  p0  )
{
	int					iErr		=	-1;
    HMENU				hMenu		=	NULL;      
	QY_DMITEM	*		pItem		=	NULL;
	HMENU				hSubMenu	=	NULL;
	int						iMenuStatus	=	0;
	unsigned  int			uFlags;

	if  (  !pTable  )  {
		traceLogA(  "newSubMenu(  ) error: pTable is null"  );  goto  errLabel;
	}

	/* Create a new menu into the menubar on the fly */     
	if  (  !(  hMenu  =  CreateMenu(  )  )  )  goto  errLabel;

	//
	BOOL	bSeparatorLast	=	FALSE;

	/* Append the state menu items to it */     
	for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  {
		 if  (  pItem->type  ==  -2  )  {
			  bSeparatorLast  =  TRUE;
			  continue;
		 }
		 if  (  pItem->type  ==  -3  )  {
			 if  (  !(  hSubMenu  =  newSubMenu(  pResInfo,  (  QY_DMITEM  *  )pItem->pData,  pf,  pQyMc,  p0  )  )  )  goto  errLabel;

			 //
			 if  (  bSeparatorLast  )  AppendMenu(  hMenu,  MF_SEPARATOR,  0,  0  );  
			 bSeparatorLast  =  FALSE;

			 if  (  !AppendMenu(  hMenu,  MF_STRING  |  MF_POPUP,  (  UINT_PTR  )hSubMenu,  getResStr(  0,  pResInfo,  (  int  )pItem->des  )  )  )  goto  errLabel;

			 continue;
		 }

		 //  if  (  !bMenuIdSupported(  pItem->type  )  )  continue;

		  iMenuStatus  =  0;	//  这里加上了菜单的状态变化处理，2006/02/11
		  if  (  pf  )  {
			  if  (  pf(  pQyMc,  p0,  (  void  *  )pItem->type,  &iMenuStatus  )  )  continue;
		  }
		  //
		  if  (  iMenuStatus  )  uFlags  =  MF_GRAYED  |  MF_STRING;
		  else  uFlags  =  MF_STRING;

		  //
		  if  (  bSeparatorLast  )  AppendMenu(  hMenu,  MF_SEPARATOR,  0,  0  );  
		  bSeparatorLast  =  FALSE;

		  AppendMenu(  hMenu,  uFlags, (  int  )pItem->type,  getResStr(  0,  pResInfo,  pItem->des  ?  (  int  )pItem->des  :  (  int  )pItem->type  )  );     
	}
	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		if  (  hMenu  )  DestroyMenu(  hMenu  );
	}
	return  iErr  ?  NULL  :  hMenu;

}



 //  2012/05/23
 //  2005/11/06, 动态生成菜单
//   __declspec(  dllexport  )  extern  "C"  int  makeDynaMenu(  void  *  pResInfoParam,  HMENU  hMenu,  QY_DMITEM  *  pTable,  PF_commonHandler  pf,  void  *  p0  )
__declspec(  dllexport  )  extern  "C"  int  makeDynaMenu(  void  *  pResInfoParam,  HMENU  hMenu,  QY_DMITEM  *  pTable,  PF_getMenuStatus  pf,  QY_MC  *  pQyMc,  void  *  p0  )
{
	int						iErr		=		-1;
	QNM_CUSRES_INFO		*	pResInfo	=	(  QNM_CUSRES_INFO  *  )pResInfoParam;
	int						iPos;
	QY_DMITEM			*	pItem;
	HMENU					hSubMenu;
	int						iMenuStatus	=	0;
	unsigned  int			uFlags;
	
	if  (  !hMenu  )  return  -1;
	if  (  !pTable  )  goto  errLabel;

	//  First, delete all items but ID_COLOR_OPTIONS at position 0
#if  0
	for  (  iPos  =  GetMenuItemCount(  hMenu  )  -  1;  iPos  >=  0;  iPos  --  )  DeleteMenu(  hMenu,  iPos,  MF_BYPOSITION  );
#else
	for  (  ;  ;  )  {
		 if  (  !DeleteMenu(  hMenu,  0,  MF_BYPOSITION  )  )  break;
	}
#endif

	//  2012/05/23
	BOOL	bSeparatorLast  =  FALSE;

	//  Then, add a separator and an item for each available text color
	for  (  pItem  =  pTable, iPos  =  0;  pItem->type  !=  -1;  pItem  ++,  iPos  ++  )  {
		  if  (  pItem->type  ==  -2  )  {
			  bSeparatorLast  =  TRUE;
			  continue;
		  }
		  if  (  pItem->type  ==  -3  )  {
			  if  (  !(  hSubMenu  =  newSubMenu(  pResInfo,  (  QY_DMITEM  *  )pItem->pData,  pf,  pQyMc,  p0  )  )  )  goto  errLabel;

			  //
			  if  (  bSeparatorLast  )  AppendMenu(  hMenu,  MF_SEPARATOR,  0,  0  );  
			  bSeparatorLast  =  FALSE;

			  //
			  if  (  !AppendMenu(  hMenu,  MF_STRING  |  MF_POPUP,  (  UINT_PTR  )hSubMenu,  getResStr(  0,  pResInfo,  (  int  )pItem->des  )  )  )  {
				  qyDisplayLastError(  "makeDynaMenu: Append subMenu failed"  );
				  //  goto  errLabel;
			  }
			  continue;
		  }

		  //  if  (  !bMenuIdSupported(  pItem->type  )  )  continue;

		  iMenuStatus  =  0;	//  这里加上了菜单的状态变化处理，2006/02/11
		  if  (  pf  )  {
			  if  (  pf(  pQyMc,  p0,  (  void  *  )pItem->type,  &iMenuStatus  )  )  continue;
		  }
		  //
		  if  (  iMenuStatus  )  uFlags  =  MF_GRAYED  |  MF_STRING;
		  else  uFlags  =  MF_STRING;
	  
		  //
		  if  (  bSeparatorLast  )  AppendMenu(  hMenu,  MF_SEPARATOR,  0,  0  );  
		  bSeparatorLast  =  FALSE;
	
		  //
		  if  (  !AppendMenu(  hMenu,  uFlags,  pItem->type, getResStr(  0,  pResInfo,  pItem->des  ?  (  int  )pItem->des  :  (  int  )pItem->type  )  )  )  {
			  qyDisplayLastError(  "makeDynaMenu: AppendMenu failed"  );
		  }

	}
	iErr  =  0;
errLabel:
	return  iErr;
}



