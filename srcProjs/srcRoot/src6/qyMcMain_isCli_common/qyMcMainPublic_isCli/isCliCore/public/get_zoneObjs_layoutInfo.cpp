

#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
//  #include	"qyMc_touchscreen.h"

#include	"qyCusResPublic.h"
#include	"qyOpenShellCommon.h"
#include	"qmOpenCommon.h"
//  #include	"qmShell_open.h"

#include	"tmpCeLib.h"

#include	"DlgWalls.h"

//  #include	"DlgMenuIsCli.h"
//#include	"myresource.h"

#include	"qyCusResTemp.h"
#include	"ctxQmc.h"

//  #include	"DlgPolicyIsClient.h"
//  #include	"DlgCfgVideoConference.h"
//  #include	"DlgMsgList.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"
#include	"qmcCommFunc_isCli.h"
#include	"isCliCorePublic.h"


//
#if  0  //  2015/12/18
__declspec(  dllexport  ) int  iiget_zoneObjs_layoutInfo(  ZONE_objs  *  pZoneObjs,  RECT  rc_zone,  BOOL  bAutoEnlarge,  void  *  pZONE_objs_info  )
{
	int  iErr  =  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return  -1;
	ZONE_objs_info  *  pVar  =  (  ZONE_objs_info  *  )pZONE_objs_info;

	int  index;
	int  cnt  =  0;

	//  2015/12/05
#if  0
	if  (  !pVar->guiData.w_org  ||  !pVar->guiData.h_org  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "layoutWalls failed, w_org or h_org is 0"  )  );
		#endif
		return  -1;
	}
#endif

	//
	chkZoneObjs(  pZoneObjs  );
	//
	for  (  index  =  0;  index  <  mycountof(  pVar->mems  );  index  ++  )  {
		 if  (  !pZoneObjs->mems[index].hWndWallMem  )  continue;
		 if  (  !IsWindow(  pZoneObjs->mems[index].hWndWallMem  )  )  {
			 //
			 memset(  &pVar->mems[index],  0,  sizeof(  pVar->mems[index]  )  );
			 continue;
		 }
		 cnt  ++  ;
	}
	//  2015/12/04
	if  (  bAutoEnlarge  )  {
		if  (  cnt  ==  1  )  {
			if  (  !isZoneObjIndexValid(  pVar->iIndex_enlarged  )  ||  !IsWindow(  pZoneObjs->mems[pVar->iIndex_enlarged].hWndWallMem  )  )  {
				for  (  index  =  0;  index  <  mycountof(  pVar->mems  );  index  ++  )  {
					if  (  IsWindow(  pZoneObjs->mems[index].hWndWallMem  )  )  {
						pVar->iIndex_enlarged  =  index;
						break;
					}
				}
			}
		}
	}
	//
	int  cnt_active  =  0;
	if  (  isZoneObjIndexValid(  pVar->iIndex_enlarged  )  )  {
		if  (  !IsWindow(  pZoneObjs->mems[pVar->iIndex_enlarged].hWndWallMem  )  )  pVar->iIndex_enlarged  =  -1;
		else  {
			  cnt_active  =  1;
		}
	}

	//
	int  w,  h;
	w  =  rc_zone.right  -  rc_zone.left;
	h  =  rc_zone.bottom  -  rc_zone.top;


#ifdef  __DEBUG__

#endif

	//
	int  iX,  iY,  iW,  iH;

	//
	ZONE_obj_info	*	pMem;

	
	if  (  cnt_active  &&  cnt  ==  cnt_active  )  {			//  只有左区。			  //  单独一个图像		
		pMem  =  &pVar->mems[pVar->iIndex_enlarged];			
		pMem->rect.iX  =  rc_zone.left;
		pMem->rect.iY  =  rc_zone.top;
		pMem->rect.iW  =  w;
		pMem->rect.iH  =  h;
		}
	else  if  (  cnt  )  {	//  两个分区

			  #define		MAX_factor_h_selected		0.6

			  float		factor_l  =  0.75;
			  int		nCols  =  1;
			  int		nRows  =  cnt  -  cnt_active;


			  //  先计算被选中的要多少宽。这个应该可以固定。
			  
			  int  iW_mem  =  w  *  (  1  -  factor_l  );
			  int  iH_mem  =  1.0  *  h  /  (  cnt  -  cnt_active  );
			  if  (  iW_mem  *  1.0  /  iH_mem  >  1.5  *  1024.  /  768.  )  {
				  nCols  =  2;
				  nRows  =  (  nRows  +  nCols  -  1  )  /  nCols;
				  iW_mem  =  iW_mem  /  nCols;  
				  iH_mem  =  iH_mem  *  nCols;
			  }

			  int	iW_selected  =  0;
			  int	iH_selected  =  0;
			  if  (  isZoneObjIndexValid(  pVar->iIndex_selected  )  
				  &&  pVar->iIndex_selected  !=  pVar->iIndex_enlarged  )
			  {
				  //  iW_selected  =  200;	//  假设
				  #ifdef  __APP_qyMc_touchscreen__
						  iW_selected  =  424;	//  假设
						  iH_selected  =  100;
				  #else
						iW_selected  =  424;
						iH_selected  =  100;
				  #endif

				  //  2011/03/27
				  G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )pFuncs->pf_get_g_guiData(  );
				  iW_selected  *=  pGuiData->fx;
				  iH_selected  *=  pGuiData->fy;

				  //
				  if  (  iW_selected  <=  iW_mem  )  iW_selected  =  iW_mem;
				  else  {	//  这里才需要调整。
					    if  (  iW_selected  >  factor_l  *  w  )  {							
							iW_selected  =  w  *  factor_l;						  
						}
						factor_l  =  1.0  *  (  w  -  (  iW_selected  +  (  nCols  -  1  )  *  iW_mem  )  )  /  w;
				  }
				  if  (  iH_selected  <=  iH_mem  )  iH_selected  =  iH_mem;
				  else  {
					    if  (  iH_selected  >  MAX_factor_h_selected  *  h  )  iH_selected  =  h  *  MAX_factor_h_selected;							
				  }			
				  //
				  if  (  nCols  >  1  )  iW_mem  =  (  w  -  w  *  factor_l  -  iW_selected  )  /  (  nCols  -  1  );
				  if  (  nRows  >  1  )  iH_mem  =  (  h  -  iH_selected  )  /  (  nRows  -  1  );
			  }

			  //
			  if  (  cnt_active  )  {
				  pMem  =  &pVar->mems[pVar->iIndex_enlarged];
				  pMem->rect.iX  =  rc_zone.left;
				  pMem->rect.iY  =  rc_zone.top;
				  pMem->rect.iW  =  w  *  factor_l;
				  pMem->rect.iH  =  h;
			  }


			  int	n	=	0;
			  int	i	=	0;
			  int	j	=	0;

			  if  (  !isZoneObjIndexValid(  pVar->iIndex_selected  )
				  ||  pVar->iIndex_selected  ==  pVar->iIndex_enlarged  )
			  {
				  //				  
				  n	=	0;				  
				  i	=	0;				  
				  j	=	0;
				  for  (  index  =  0;  index  <  mycountof(  pVar->mems  );  index  ++  )  {
					   //
					   ZONE_obj  *  pZoneObj  =  &pZoneObjs->mems[index];	//  2015/12/05
					   //
					   pMem  =  &pVar->mems[index];				   
					   if  (  !pZoneObj->hWndWallMem  )  continue;
					   if  (  index  ==  pVar->iIndex_enlarged  )  continue;
					   i  =  n  %  nCols;
					   j  =  n  /  nCols;					   
				   
					   pMem->rect.iX  =  rc_zone.left  +  w  *  factor_l  +  i  *  iW_mem;
					   pMem->rect.iY  =  rc_zone.top  +  j  *  iH_mem;
					   if  (  i  <  nCols  -  1  )  pMem->rect.iW  =  iW_mem;
					   else  pMem->rect.iW  =  w  -  w  *  factor_l  -  (  nCols  -  1  )  *  iW_mem;
					   if  (  j  <  nRows  -  1  )  pMem->rect.iH  =  iH_mem;						   
					   else  pMem->rect.iH  =  h  -  (  nRows  -  1  )  *  iH_mem;

					   n  ++  ;
				  }
				  #ifdef  __DEBUG__
						  traceLog(  _T(  "layoutWalls: here"  )  );
				  #endif
				  }				
			  else  {
					n  =  0;				
					i  =  0;						
					j  =  0;
					int	i_selected	=  0;
					int	j_selected  =  0;
					for  (  index  =  0;  index  <  mycountof(  pVar->mems  );  index  ++  )  {
						 //
						 ZONE_obj  *  pZoneObj  =  &pZoneObjs->mems[index];	//  2015/12/05
						 //
						 pMem  =  &pVar->mems[index];				   
						 if  (  !pZoneObj->hWndWallMem  )  continue;
						 if  (  index  ==  pVar->iIndex_enlarged  )  continue;
						 if  (  pVar->iIndex_selected  ==  index )  {
							 i_selected  =  n  %  nCols;
							 j_selected  =  n  /  nCols;					   
							 break;
						 }
						 //  
						 n  ++  ;
					}
					//
					n  =  0;
					i  =  0;
					j  =  0;
					iY  =  rc_zone.top;
					for  (  index  =  0;  index  <  mycountof(  pVar->mems  );  index  ++  )  {
						 //
						 ZONE_obj  *  pZoneObj  =  &pZoneObjs->mems[index];	//  2015/12/05
						 //
						 pMem  =  &pVar->mems[index];
						 if  (  !pZoneObj->hWndWallMem  )  continue;
						 if  (  index  ==  pVar->iIndex_enlarged  )  continue;
						 i  =  n  %  nCols;
						 j  =  n  /  nCols;

						 if  (  !i  )  {
							 iX  =  rc_zone.left  +  w  *  factor_l;
						 }
						 if  (  i  ==  i_selected  )  iW  =  iW_selected;
						 else  iW  =  iW_mem;
						 if  (  j  ==  j_selected  )  iH  =  iH_selected;
						 else  iH  =  iH_mem;

						 pMem->rect.iX  =  iX;
						 pMem->rect.iY  =  iY;							 
						 pMem->rect.iW  =  iW;
						 pMem->rect.iH  =  iH;
							 
						 iX  +=  iW;
						 if  (  i  ==  nCols  -  1  )  iY  +=  iH;
						 //
						 n  ++  ;
					}					    
			  }
		}
	else  {
		  //iErr  =  0;  goto  errLabel;
	}

	iErr  =  0;
errLabel:
	return  iErr;

}
#endif



////////////////
//  2015/12/18
__declspec(  dllexport  ) int  get_zoneObjs_layoutInfo(  CCtxQmc  *  pProcInfo,  ZONE_objs  *  pZoneObjs,  RECT  rc_zone,  BOOL  bAutoEnlarge,  void  *  pZONE_objs_info  )
{
	int  iErr  =  -1;
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	ZONE_objs_info  *  pVar  =  (  ZONE_objs_info  *  )pZONE_objs_info;

	int  index;
	int  cnt  =  0;

	//  2015/12/05
	//
	for  (  index  =  0;  index  <  mycountof(  pVar->mems  );  index  ++  )  {
		 if  (  !pZoneObjs->mems[index].hWndWallMem  )  continue;
		 cnt  ++  ;
	}
	//  2015/12/04
#if  0
	if  (  bAutoEnlarge  )  {
		if  (  cnt  ==  1  )  {
			if  (  !isZoneObjIndexValid(  pZoneObjs->iIndex_enlarged  )  ||  !IsWindow(  pZoneObjs->mems[pZoneObjs->iIndex_enlarged].hWndWallMem  )  )  {
				for  (  index  =  0;  index  <  mycountof(  pVar->mems  );  index  ++  )  {
					if  (  IsWindow(  pZoneObjs->mems[index].hWndWallMem  )  )  {
						pVar->iIndex_enlarged  =  index;
						break;
					}
				}
			}
		}
	}
#endif
	//
	int  cnt_active  =  0;
	if  (  isZoneObjIndexValid(  pZoneObjs->iIndex_enlarged1  )  )  {
		if  (  !IsWindow(  pZoneObjs->mems[pZoneObjs->iIndex_enlarged1].hWndWallMem  )  )  pZoneObjs->iIndex_enlarged1  =  -1;
		else  {
			  cnt_active  =  1;
		}
	}

	//
	int  w,  h;
	w  =  rc_zone.right  -  rc_zone.left;
	h  =  rc_zone.bottom  -  rc_zone.top;


#ifdef  __DEBUG__

#endif

	//
	int  iX,  iY,  iW,  iH;

	//
	ZONE_obj_info	*	pMem;

	
	if  (  cnt_active  &&  cnt  ==  cnt_active  )  {			//  只有左区。			  //  单独一个图像		
		pMem  =  &pVar->mems[pZoneObjs->iIndex_enlarged1];			
		pMem->rect.iX  =  rc_zone.left;
		pMem->rect.iY  =  rc_zone.top;
		pMem->rect.iW  =  w;
		pMem->rect.iH  =  h;
		}
	else  if  (  cnt  )  {	//  两个分区

			  #define		MAX_factor_h_selected		0.6

			  float		factor_l  =  0.75;
			  int		nCols  =  1;
			  int		nRows  =  cnt  -  cnt_active;


			  //  先计算被选中的要多少宽。这个应该可以固定。
			  
			  int  iW_mem  =  w  *  (  1  -  factor_l  );
			  int  iH_mem  =  1.0  *  h  /  (  cnt  -  cnt_active  );
			  if  (  iW_mem  *  1.0  /  iH_mem  >  1.5  *  1024.  /  768.  )  {
				  nCols  =  2;
				  nRows  =  (  nRows  +  nCols  -  1  )  /  nCols;
				  iW_mem  =  iW_mem  /  nCols;  
				  iH_mem  =  iH_mem  *  nCols;
			  }

			  int	iW_selected  =  0;
			  int	iH_selected  =  0;
			  if  (  isZoneObjIndexValid(  pVar->iIndex_selected  )  
				  &&  pVar->iIndex_selected  !=  pZoneObjs->iIndex_enlarged1  )
			  {
				  //  iW_selected  =  200;	//  假设
				  #ifdef  __APP_qyMc_touchscreen__
						  iW_selected  =  424;	//  假设
						  iH_selected  =  100;
				  #else
						iW_selected  =  424;
						iH_selected  =  100;
				  #endif

				  //  2011/03/27
				  G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )pFuncs->pf_get_g_guiData(  );
				  iW_selected  *=  pGuiData->fx;
				  iH_selected  *=  pGuiData->fy;

				  //
				  if  (  iW_selected  <=  iW_mem  )  iW_selected  =  iW_mem;
				  else  {	//  这里才需要调整。
					    if  (  iW_selected  >  factor_l  *  w  )  {							
							iW_selected  =  w  *  factor_l;						  
						}
						factor_l  =  1.0  *  (  w  -  (  iW_selected  +  (  nCols  -  1  )  *  iW_mem  )  )  /  w;
				  }
				  if  (  iH_selected  <=  iH_mem  )  iH_selected  =  iH_mem;
				  else  {
					    if  (  iH_selected  >  MAX_factor_h_selected  *  h  )  iH_selected  =  h  *  MAX_factor_h_selected;							
				  }			
				  //
				  if  (  nCols  >  1  )  iW_mem  =  (  w  -  w  *  factor_l  -  iW_selected  )  /  (  nCols  -  1  );
				  if  (  nRows  >  1  )  iH_mem  =  (  h  -  iH_selected  )  /  (  nRows  -  1  );
			  }

			  //
			  if  (  cnt_active  )  {
				  pMem  =  &pVar->mems[pZoneObjs->iIndex_enlarged1];
				  pMem->rect.iX  =  rc_zone.left;
				  pMem->rect.iY  =  rc_zone.top;
				  pMem->rect.iW  =  w  *  factor_l;
				  pMem->rect.iH  =  h;
			  }


			  int	n	=	0;
			  int	i	=	0;
			  int	j	=	0;

			  if  (  !isZoneObjIndexValid(  pVar->iIndex_selected  )
				  ||  pVar->iIndex_selected  ==  pZoneObjs->iIndex_enlarged1  )
			  {
				  //				  
				  n	=	0;				  
				  i	=	0;				  
				  j	=	0;
				  for  (  index  =  0;  index  <  mycountof(  pVar->mems  );  index  ++  )  {
					   //
					   ZONE_obj  *  pZoneObj  =  &pZoneObjs->mems[index];	//  2015/12/05
					   //
					   pMem  =  &pVar->mems[index];				   
					   if  (  !pZoneObj->hWndWallMem  )  continue;
					   if  (  index  ==  pZoneObjs->iIndex_enlarged1  )  continue;
					   i  =  n  %  nCols;
					   j  =  n  /  nCols;					   
				   
					   pMem->rect.iX  =  rc_zone.left  +  w  *  factor_l  +  i  *  iW_mem;
					   pMem->rect.iY  =  rc_zone.top  +  j  *  iH_mem;
					   if  (  i  <  nCols  -  1  )  pMem->rect.iW  =  iW_mem;
					   else  pMem->rect.iW  =  w  -  w  *  factor_l  -  (  nCols  -  1  )  *  iW_mem;
					   if  (  j  <  nRows  -  1  )  pMem->rect.iH  =  iH_mem;						   
					   else  pMem->rect.iH  =  h  -  (  nRows  -  1  )  *  iH_mem;

					   n  ++  ;
				  }
				  #ifdef  __DEBUG__
						  traceLog(  _T(  "get_zoneObjs_layoutInfo: here"  )  );
				  #endif
				  }				
			  else  {
					n  =  0;				
					i  =  0;						
					j  =  0;
					int	i_selected	=  0;
					int	j_selected  =  0;
					for  (  index  =  0;  index  <  mycountof(  pVar->mems  );  index  ++  )  {
						 //
						 ZONE_obj  *  pZoneObj  =  &pZoneObjs->mems[index];	//  2015/12/05
						 //
						 pMem  =  &pVar->mems[index];				   
						 if  (  !pZoneObj->hWndWallMem  )  continue;
						 if  (  index  ==  pZoneObjs->iIndex_enlarged1  )  continue;
						 if  (  pVar->iIndex_selected  ==  index )  {
							 i_selected  =  n  %  nCols;
							 j_selected  =  n  /  nCols;					   
							 break;
						 }
						 //  
						 n  ++  ;
					}
					//
					n  =  0;
					i  =  0;
					j  =  0;
					iY  =  rc_zone.top;
					for  (  index  =  0;  index  <  mycountof(  pVar->mems  );  index  ++  )  {
						 //
						 ZONE_obj  *  pZoneObj  =  &pZoneObjs->mems[index];	//  2015/12/05
						 //
						 pMem  =  &pVar->mems[index];
						 if  (  !pZoneObj->hWndWallMem  )  continue;
						 if  (  index  ==  pZoneObjs->iIndex_enlarged1  )  continue;
						 i  =  n  %  nCols;
						 j  =  n  /  nCols;

						 if  (  !i  )  {
							 iX  =  rc_zone.left  +  w  *  factor_l;
						 }
						 if  (  i  ==  i_selected  )  iW  =  iW_selected;
						 else  iW  =  iW_mem;
						 if  (  j  ==  j_selected  )  iH  =  iH_selected;
						 else  iH  =  iH_mem;

						 pMem->rect.iX  =  iX;
						 pMem->rect.iY  =  iY;							 
						 pMem->rect.iW  =  iW;
						 pMem->rect.iH  =  iH;
							 
						 iX  +=  iW;
						 if  (  i  ==  nCols  -  1  )  iY  +=  iH;
						 //
						 n  ++  ;
					}					    
			  }
		}
	else  {
		  //iErr  =  0;  goto  errLabel;
	}

	iErr  =  0;
errLabel:
	return  iErr;

}


