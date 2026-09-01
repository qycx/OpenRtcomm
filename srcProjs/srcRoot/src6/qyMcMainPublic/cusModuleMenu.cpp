
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCusModule.h"
#include	"qyCusResTemp.h"
#include	"qyVDev.h"
#include	"myresource.h"
#include	"qyCustom.h"
#include	"module_qisCamCap.h"

//  2007/12/30
 //
 BOOL  bFindMenuItem(  HMENU  hMenu, LPCTSTR  MenuString,  int  *  pnPos  )
{
   int	nPos  =  -1;
 
   if  (  !hMenu  ||  !MenuString  )  return  FALSE;

   int  count  =  GetMenuItemCount(  hMenu  );
   for  (  int i = 0; i < count; i++  )  {
	    TCHAR	str[512]	=	_T(  ""  );
        if  (  GetMenuString(  hMenu,  i, str, mycountof(  str  ),  MF_BYPOSITION) &&  (lstrcmpi(str, MenuString) == 0))  {
			nPos  =  i;
			break;
		}         
   }

   if  (  nPos  >  0  )  {
	   if  (  pnPos  )  *pnPos  =  nPos;
   }
   return  (  nPos  >=  0  )  ?  TRUE  :  FALSE; 
}

 //  2010/09/05
  int  cusModuleMenu(  void  *  pQyMcParam,  HMENU  hMenuFrm,  int  iResId_menu_modulesGuanLi  )
{
	QY_MC			*	pQyMc		=	(  QY_MC  *  )pQyMcParam;
	CUS_MODULE_U	*	pModule		=	NULL;
	HMENU				hMenu		=	NULL;
	int					cnt			=	0;
	int					nPos		=	0;
	BOOL				bMenuAdded	=	FALSE;
	//
	if  (  bFindMenuItem(  hMenuFrm,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_menu_guanLi  ),  &nPos  )  )  {
		if  (  (  hMenu  =  GetSubMenu(  hMenuFrm,  nPos  )  )  )  {
			if  (  bFindMenuItem(  hMenu,  getResStr(  0,  &pQyMc->cusRes,  iResId_menu_modulesGuanLi  ),  &nPos  )  )  {
				HMENU	hMenu_guanLi	=  hMenu;
				int		nPos_modules	=	nPos;
				//
				if  (  (  hMenu  =  GetSubMenu(  hMenu,  nPos  )  )  )  {
					for  (  nPos  =  GetMenuItemCount(  hMenu  )  -  1;  nPos  >=  0;  nPos  --  )  DeleteMenu(  hMenu,  nPos,  MF_BYPOSITION  );
					//
					for  (  int  i  =  0;  i  <  pQyMc->cusModules.usCnt;  i  ++  )  {
						 pModule  =  &pQyMc->cusModules.mems[i];
						 switch  (  pModule->common.uiType  )  {								   
								 case  CONST_moduleType_vDev:
									   pModule->vDev.uiCmd  =  ID_cliModule0  +  i;			//  注意，这里是给每个模块分配一个操作菜单．其中ID_cliModule0为起始命令．
									   //							   
									   AppendMenu(  hMenu,  MF_STRING,  pModule->vDev.uiCmd,  pModule->vDev.name  );
									   //
									   bMenuAdded  =  TRUE;											 
									   break;
								 default:
									     break;
						 }
					}					  
				}
				
				if  (  !bMenuAdded  )  {
					traceLogA(  (char*)  "RemoveMenu returns %d",  RemoveMenu(  hMenu_guanLi,  nPos_modules,  MF_BYPOSITION  )  );	//  
					traceLogA(  (char*)  "RemoveMenu returns %d",  RemoveMenu(  hMenu_guanLi,  nPos_modules,  MF_BYPOSITION  )  );	//  
				}
				
			}
		}		
	}

	return  0;

}



