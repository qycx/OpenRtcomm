

#include	"stdafx.h"
#include	<tchar.h>
#include	<math.h>

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


//
////////////////
//  2016/02/08
//
__declspec(  dllexport  ) int  get_zoneObjs_layoutInfo_d3d(  CCtxQmc  *  pProcInfo,  ZONE_objs  *  pZoneObjs,  RECT  rc_zone,  BOOL  bAutoEnlarge,  void  *  pZONE_objs_info  )
{
	int  iErr  =  -1;

	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	ZONE_objs_info  *  pVar  =  (  ZONE_objs_info  *  )pZONE_objs_info;
	
	//
	int  zone_w,  zone_h;
	zone_w  =  rc_zone.right  -  rc_zone.left;
	zone_h  =  rc_zone.bottom  -  rc_zone.top;

	//
	if  (  !zone_w  ||  !zone_h  )  return  -1;
	
	//
	int  iX,  iY,  iW,  iH;
	int  index;
	float  factorX =  24.;	// 16.;
	float  factorY =  9.;	// 9.;

	
	//
	if  (  pVar->d3d.zone_w  !=  zone_w  ||  pVar->d3d.zone_h  !=  zone_h  )  {
		//
		showInfo_open0(  0,  _T(  "get_zoneObjs_layoutInfo_d3d"  ),  _T(  "zone_w or zone_h changed"  )  );
		//
		int  iSpace  =  1;
		int  iEdge_x  =  1;
		int  iEdge_y  =  1;
		//
		//  float  fAspect6X1  =  4.  /  (  (  3  +  iSpace  )  *  6  );
		float  fAspect6X1  =  factorX  /  (  (  factorY  +  iSpace  )  *  6  );
		//  float  fAspect1_2X2_1_v  =  9.  /  (  (  6  +  iSpace  )  +  (  3  +  iSpace  )  *  2  +  (  3  +  iSpace  )  );
		float  fAspect1_2X2_1_v  =  (  factorX * 2  +  iSpace  )  /  (  (  factorY * 2  +  iSpace  )  +  (  factorY  +  iSpace  )  *  2  +  (  factorY   +  iSpace  ) );
		//  float  fAspect1_2X1_1X3  =  (  9.  +  iSpace  +  4  )  /  (  (  3  +  iSpace  )  *  2  +  (  3  +  iSpace  )  );
		float  fAspect1_2X1_1X3  =  (  factorX * 3  +  iSpace   )  /  (  factorY * 3  +  iSpace  *  3  );
		//  float  fAspect1_2X2_1_h  =  (  (  8.  +  iSpace  )  +  (  4  +  iSpace  )  *  2  +  (  4  +  iSpace  )  )  /  7;
		float  fAspect1_2X2_1_h  =  (  factorX * 5  +  iSpace * 4  )  /  (  factorY * 2  +  iSpace  );
		//  float  fAspect1X6  =  (  (  4.  +  iSpace  )  *  6  )  /  3;
		float  fAspect1X6  =  (  (  factorX  +  iSpace  )  *  6  )  /  factorY;
		//
		float  fAspect  =  1.  *  zone_w  /  zone_h;
		if  (  fAspect  <  fAspect1_2X2_1_v  )  pVar->d3d.layoutType  =  CONST_zoneLayoutType_6X1;
		else  if  (  fAspect  <  fAspect1_2X1_1X3  )  pVar->d3d.layoutType  =  CONST_zoneLayoutType_1_2X2_1_v;
		else  if  (  fAspect  <  fAspect1_2X2_1_h  )  pVar->d3d.layoutType  =  CONST_zoneLayoutType_1_2X1_1X3;
		else  if  (  fAspect  <  fAspect1X6  )  pVar->d3d.layoutType  =  CONST_zoneLayoutType_1_2X2_1_h;
		else  pVar->d3d.layoutType  =  CONST_zoneLayoutType_1X6;


		int  iVal_x,iVal_y;		
		float  fUnitH, fUnitW;
		CAP_RECT  cr;

		//
		switch  (  pVar->d3d.layoutType  )  {
				case  CONST_zoneLayoutType_6X1:{
					  iVal_x  =  zone_w  -  2  *  iEdge_x  -  0  *  iSpace;
					  if  (  iVal_x  <  0  )  goto  errLabel;
					  iVal_y  =  zone_h  -  2  *  iEdge_y  -  5  *  iSpace;
					  if  (  iVal_y  <  0  )  goto  errLabel;
					  fUnitW  =  iVal_x;
					  //  fUnitH  =  fUnitW  *  3.  /  4;
					  fUnitH  =  iVal_y  /  6;	//  fUnitW  *  factorY  /  factorX;
					  //
					  index  =  0;
					  cr.iW  =  fUnitW  *  1;
					  cr.iH  =  fUnitH  *  1;
					  cr.iX  =  iEdge_x;
					  cr.iY  =  iEdge_y;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iW  =  fUnitW;
					  cr.iH  =  fUnitH;
					  cr.iX  =  iEdge_x  +  0  *  fUnitW  +  0  *  iSpace;
					  cr.iY  =  iEdge_y  +  1  *  fUnitH  +  1  *  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x  +  0  *  fUnitW  +  0  *  iSpace;
					  cr.iY  =  iEdge_y  +  2  *  fUnitH  +  2  *  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x  +  0  *  fUnitW  +  0  *  iSpace;
					  cr.iY  =  iEdge_y  +  3  *  fUnitH  +  3  *  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x  +  0  *  fUnitW  +  0  *  iSpace;
					  cr.iY  =  iEdge_y  +  4  *  fUnitH  +  4  *  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x  +  0  *  fUnitW  +  0  *  iSpace;
					  cr.iY  =  iEdge_y  +  5  *  fUnitH  +  5  *  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;

					  //
					  MACRO_qyAssert(  index  <=  mycountof(  pVar->d3d.crs  ),  _T(  ""  )  );

					  }
					  break;
				case  CONST_zoneLayoutType_1_2X2_1_v:{
					  iVal_x  =  zone_w  -  2  *  iEdge_x  -  1  *  iSpace;
					  if  (  iVal_x  <  0  )  goto  errLabel;
					  iVal_y  =  zone_h  -  2  *  iEdge_y  -  3  *  iSpace;
					  if  (  iVal_y  <  0  )  goto  errLabel;
					  fUnitW  =  iVal_x  /  2;
					  //  fUnitH  =  fUnitW  *  3.  /  4;
					  fUnitH  =  fUnitW  *  factorY  /  factorX;
					  //
					  index  =  0;
					  cr.iW  =  fUnitW  *  2;
					  cr.iH  =  fUnitH  *  2;
					  cr.iX  =  iEdge_x;
					  cr.iY  =  iEdge_y;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iW  =  fUnitW;
					  cr.iH  =  fUnitH;
					  cr.iX  =  iEdge_x;
					  cr.iY  =  iEdge_y  +  fUnitH  *  2  +  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x;
					  cr.iY  =  iEdge_y  +  fUnitH  *  2  +  iSpace  +  fUnitH  +  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x  +  fUnitW  *  1  +  iSpace;
					  cr.iY  =  iEdge_y  +  fUnitH  *  2  +  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x  +  fUnitW  *  1  +  iSpace;
					  cr.iY  =  iEdge_y  +  fUnitH  *  2  +  iSpace  +  fUnitH  +  iSpace;					  
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iW  =  fUnitW  *  2  +  iSpace;
					  cr.iH  =  fUnitH;
					  cr.iX  =  iEdge_x;
					  cr.iY  =  iEdge_y  +  fUnitH  *  2  +  (  iSpace  +  fUnitH  )  *  2  +  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;

					  //
					  MACRO_qyAssert(  index  <=  mycountof(  pVar->d3d.crs  ),  _T(  ""  )  );

					  }
					  break;
				case  CONST_zoneLayoutType_1_2X1_1X3:{
					  iVal_x  =  zone_w  -  2  *  iEdge_x  -  2  *  iSpace;
					  if  (  iVal_x  <  0  )  goto  errLabel;
					  iVal_y  =  zone_h  -  2  *  iEdge_y  -  2  *  iSpace;
					  if  (  iVal_y  <  0  )  goto  errLabel;
					  fUnitH  =  iVal_y  /  3;
					  //  fUnitW  =  fUnitH  /  3.  *  4;
					  fUnitW  =  fUnitH  /  factorY  *  factorX;
					  //
					  index  =  0;
					  cr.iW  =  fUnitW  *  2;
					  cr.iH  =  fUnitH  *  2;
					  cr.iX  =  iEdge_x;
					  cr.iY  =  iEdge_y;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iW  =  fUnitW;
					  cr.iH  =  fUnitH;
					  cr.iX  =  iEdge_x  +  fUnitW  *  2  +  2  *  iSpace;
					  cr.iY  =  iEdge_y;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x  +  fUnitW  *  2  +  2  *  iSpace;
					  cr.iY  =  iEdge_y  +  fUnitH  *  1  +  1  *  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x;
					  cr.iY  =  iEdge_y  +  fUnitH  *  2  +  2  *  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x  +  fUnitW  *  1  +  1  *  iSpace;
					  cr.iY  =  iEdge_y  +  fUnitH  *  2  +  2  *  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x  +  fUnitW  *  2  +  2  *  iSpace;
					  cr.iY  =  iEdge_y  +  fUnitH  *  2  +  2  *  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;

					  //
					  MACRO_qyAssert(  index  <=  mycountof(  pVar->d3d.crs  ),  _T(  ""  )  );

					  }
					  break;
				case  CONST_zoneLayoutType_1_2X2_1_h:  {
					  iVal_x  =  zone_w  -  2  *  iEdge_x  -  3  *  iSpace;
					  if  (  iVal_x  <  0  )  goto  errLabel;
					  iVal_y  =  zone_h  -  2  *  iEdge_y  -  iSpace;
					  if  (  iVal_y  <  0  )  goto  errLabel;
					  fUnitH  =  iVal_y  /  2;
					  //  fUnitW  =  fUnitH  /  3.  *  4;
  					  fUnitW  =  fUnitH  /  factorY  *  factorX;

					  //
					  index  =  0;
					  cr.iW  =  fUnitW  *  2;
					  cr.iH  =  fUnitH  *  2;
					  cr.iX  =  iEdge_x;
					  cr.iY  =  iEdge_y;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iW  =  fUnitW;
					  cr.iH  =  fUnitH;
					  cr.iX  =  iEdge_x  +  fUnitW  *  2  +  iSpace;
					  cr.iY  =  iEdge_y;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x  +  fUnitW  *  2  +  iSpace  +  fUnitW  +  iSpace;
					  cr.iY  =  iEdge_y;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x  +  fUnitW  *  2  +  iSpace;
					  cr.iY  =  iEdge_y  +  fUnitH  +  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x  +  fUnitW  *  2  +  iSpace  +  fUnitW  +  iSpace;					  
					  cr.iY  =  iEdge_y  +  fUnitH  +  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iW  =  fUnitW;
					  cr.iH  =  fUnitH  *  2  +  iSpace;
					  cr.iX  =  iEdge_x  +  fUnitW  *  2  +  (  iSpace  +  fUnitW  )  *  2  +  iSpace;
					  cr.iY  =  iEdge_y;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;

					  //
					  MACRO_qyAssert(  index  <=  mycountof(  pVar->d3d.crs  ),  _T(  ""  )  );

					  }
					  break;
				case  CONST_zoneLayoutType_1X6:{
					  iVal_x  =  zone_w  -  2  *  iEdge_x  -  5  *  iSpace;
					  if  (  iVal_x  <  0  )  goto  errLabel;
					  iVal_y  =  zone_h  -  2  *  iEdge_y  -  0  *  iSpace;
					  if  (  iVal_y  <  0  )  goto  errLabel;
					  fUnitH  =  iVal_y;
					  //  fUnitW  =  fUnitH  /  3.  *  4;
  					  fUnitW  =  fUnitH  /  factorY  *  factorX;
					  //
					  index  =  0;
					  cr.iW  =  fUnitW  *  1;
					  cr.iH  =  fUnitH  *  1;
					  cr.iX  =  iEdge_x;
					  cr.iY  =  iEdge_y;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iW  =  fUnitW;
					  cr.iH  =  fUnitH;
					  cr.iX  =  iEdge_x  +  1  *  fUnitW  +  1  *  iSpace;
					  cr.iY  =  iEdge_y  +  0  *  fUnitH  +  0  *  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x  +  2  *  fUnitW  +  2  *  iSpace;
					  cr.iY  =  iEdge_y  +  0  *  fUnitH  +  0  *  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x  +  3  *  fUnitW  +  3  *  iSpace;
					  cr.iY  =  iEdge_y  +  0  *  fUnitH  +  0  *  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x  +  4  *  fUnitW  +  4  *  iSpace;
					  cr.iY  =  iEdge_y  +  0  *  fUnitH  +  0  *  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;
					  //
					  cr.iX  =  iEdge_x  +  5  *  fUnitW  +  5  *  iSpace;
					  cr.iY  =  iEdge_y  +  0  *  fUnitH  +  0  *  iSpace;
					  pVar->d3d.crs[index]  =  cr;
					  index  ++  ;

					  //
					  MACRO_qyAssert(  index  <=  mycountof(  pVar->d3d.crs  ),  _T(  ""  )  );

					  }
					  break;
				default:
						goto  errLabel;
						break;
		}


		//
		pVar->d3d.zone_w  =  zone_w;
		pVar->d3d.zone_h  =  zone_h;
	}


	//  2015/12/05
	//
	int  cnt  =  0;
	for  (  index  =  0;  index  <  mycountof(  pVar->mems  );  index  ++  )  {
		 if  (  !pZoneObjs->mems[index].hWndWallMem  )  continue;
		 cnt  ++  ;
	}

	//
	int  cnt_total  =  cnt;

	//  2015/12/04
	//
	int  cnt_active  =  0;
	if  (  isZoneObjIndexValid(  pZoneObjs->iIndex_enlarged1  )  )  {
		if  (  !IsWindow(  pZoneObjs->mems[pZoneObjs->iIndex_enlarged1].hWndWallMem  )  )  pZoneObjs->iIndex_enlarged1  =  -1;
		else  {
			  cnt_active  =  1;
		}
	}

	//
	int  cnt_left  =  cnt_total;
	if  (  !cnt_left  )  {
		iErr  =  0;  goto  errLabel;
	}

	//
	ZONE_obj_info	*	pMem;

	//
	pVar->d3d.tn_to_get_zoneObjs_layoutInfo_d3d  ++  ;
	
	//
	if  (  cnt_active  )  {			//  只有左区。			  //  单独一个图像		
		pMem  =  &pVar->mems[pZoneObjs->iIndex_enlarged1];	
		//
		pMem->rect.iX  =  rc_zone.left  +  pVar->d3d.crs[0].iX;
		pMem->rect.iY  =  rc_zone.top  +  pVar->d3d.crs[0].iY;
		pMem->rect.iW  =  pVar->d3d.crs[0].iW;
		pMem->rect.iH  =  pVar->d3d.crs[0].iH;
		//
		pMem->bSmallest  =  FALSE;
		//
		pMem->tn_to_get_zoneObjs_layoutInfo_d3d  =  pVar->d3d.tn_to_get_zoneObjs_layoutInfo_d3d;

		//
		cnt_left  --  ;
	}

	// 
	int  i;
	//
	if  (  cnt_left  )  {
		int  cnt_recvd  =  0;
		//
		for  (  i  =  0;  i  <  mycountof(  pZoneObjs->recentAvRecvd.mems  );  i  ++  )  {
			 //
			 if  (  !cnt_left  )  break;
			 if  (  cnt_recvd  >=  MAX_recentZoneObjs  )  break;
			 //
			 index  =  pZoneObjs->recentAvRecvd.uiCnt_recentAvRecvd  -  1  -  i;
			 if  (  index  <  0  )  break;
			 index  =  index  %  mycountof(  pZoneObjs->recentAvRecvd.mems  );
			 //
			 RECENT_avRecvd_mem  *  pRecvdMem  =  &pZoneObjs->recentAvRecvd.mems[index];
			 if  (  !pRecvdMem->dwTickCnt_recent_avRecvd  )  break;

			 if  (  !isZoneObjIndexValid(  pRecvdMem->iIndex_zoneObj  )  )  goto  errLabel;
			 ZONE_obj  *  pZoneObj  =  &pZoneObjs->mems[pRecvdMem->iIndex_zoneObj];
			 pMem  =  &pVar->mems[pRecvdMem->iIndex_zoneObj];
			 //
			 if  (  pZoneObj->hWndWallMem  !=  pRecvdMem->hTalker  )  continue;
			 if  (  pMem->tn_to_get_zoneObjs_layoutInfo_d3d  ==  pVar->d3d.tn_to_get_zoneObjs_layoutInfo_d3d  )  continue;

			 //
			 CAP_RECT  *  pCr_dst  =  &pVar->d3d.crs[1  +  cnt_recvd];
			 pMem->rect.iX  =  rc_zone.left  +  pCr_dst->iX;
			 pMem->rect.iY  =  rc_zone.top  +  pCr_dst->iY;
			 pMem->rect.iW  =  pCr_dst->iW;
			 pMem->rect.iH  =  pCr_dst->iH;
			 //
			 pMem->bSmallest  =  FALSE;
			 //
			 pMem->tn_to_get_zoneObjs_layoutInfo_d3d  =  pVar->d3d.tn_to_get_zoneObjs_layoutInfo_d3d;
			 //
			 pVar->d3d.index_recents[cnt_recvd]  =  pRecvdMem->iIndex_zoneObj;
			 //
			 cnt_recvd  ++;
			 cnt_left  --  ;

		}
		pVar->d3d.cnt_recents  =  cnt_recvd;
	}
	//
	if  (  cnt_left  )  {
		int  cnt_bigs  =  0;
		unsigned  int  uiIndex_toBeBig;
		//
		for  (  i  =  0;  i  <  mycountof(  pZoneObjs->mems  );  i  ++  )  {
			 if  (  !cnt_left  )  break;
			 if  (  cnt_bigs  >=  MAX_bigZoneObjs  ) break;
			 //
			 uiIndex_toBeBig  =  pVar->d3d.startIndex_toBeBig  +  i;
			 uiIndex_toBeBig  =  uiIndex_toBeBig  %  mycountof(  pZoneObjs->mems  );
			 //
			 ZONE_obj  *  pZoneObj  =  &pZoneObjs->mems[uiIndex_toBeBig];
			 pMem  =  &pVar->mems[uiIndex_toBeBig];
			 //
			 if  (  !pZoneObj->hWndWallMem  )  continue;
			 if  (  pMem->tn_to_get_zoneObjs_layoutInfo_d3d  ==  pVar->d3d.tn_to_get_zoneObjs_layoutInfo_d3d  )  continue;
			 //
			 CAP_RECT  *  pCr_dst  =  &pVar->d3d.crs[3  +  cnt_bigs];
			 pMem->rect.iX  =  rc_zone.left  +  pCr_dst->iX;
			 pMem->rect.iY  =  rc_zone.top  +  pCr_dst->iY;
			 pMem->rect.iW  =  pCr_dst->iW;
			 pMem->rect.iH  =  pCr_dst->iH;
			 //
			 pMem->bSmallest  =  FALSE;
			 //
			 pMem->tn_to_get_zoneObjs_layoutInfo_d3d  =  pVar->d3d.tn_to_get_zoneObjs_layoutInfo_d3d;
			 //
			 pVar->d3d.index_bigs[cnt_bigs]  =  uiIndex_toBeBig;
			 //
			 cnt_bigs  ++;
			 cnt_left  --  ;
		}
		pVar->d3d.cnt_bigs  =  cnt_bigs;
		//
		DWORD  dwTickCnt  =  GetTickCount(  );
		int  iDiff  =  dwTickCnt  -  pVar->d3d.dwLastModifiedTickCnt_startIndex_toBeBig;
		if  (  abs(  iDiff  )  >  3000  )  {
			if  (  cnt_bigs  )  pVar->d3d.startIndex_toBeBig  =  pVar->d3d.index_bigs[cnt_bigs  -  1]  +  1;
			else  pVar->d3d.startIndex_toBeBig  +=  MAX_bigZoneObjs;
			//
			pVar->d3d.startIndex_toBeBig  =  pVar->d3d.startIndex_toBeBig  %  mycountof(  pZoneObjs->mems  );
			pVar->d3d.dwLastModifiedTickCnt_startIndex_toBeBig  =  dwTickCnt;
			//
			#ifdef  __DEBUG__
					traceLog(  _T(  "startIndex_toBeBig %d"  ),  pVar->d3d.startIndex_toBeBig  );
			#endif
		}
	}


	//
	cnt  =  cnt_left;
	if  (  cnt  )  {
		 int  iRows  =  (  int  )sqrt(  (  double  )cnt  );
		 if  (  iRows  *  iRows  <  cnt  )  iRows  ++  ;
		 //
		 int  iX_desc  =  pVar->d3d.crs[5].iX;
		 int  iY_desc  =  pVar->d3d.crs[5].iY;
		 int  iW_desc  =  pVar->d3d.crs[5].iW;
		 int  iH_desc  =  pVar->d3d.crs[5].iH;
		 //
		 cnt  =  0;
		 for  (  index  =  0;  index  <  mycountof(  pZoneObjs->mems  );  index  ++  )  {
			  int  iRow,  iCol;
			  iRow  =  cnt  %  iRows;
			  iCol  =  cnt  /  iRows;

			  //  int  iX,  iY;
			  iX  =  iX_desc  +  (  int  )(  iRow  *  iW_desc  /  (  float  )iRows  );
			  iY  =  iY_desc  +  (  int  )(  iCol  *  iH_desc  /  (  float  )iRows  );

			  //
			  //				
			  ZONE_obj  *  pZoneObj  =  &pZoneObjs->mems[index];	//  2015/12/05
			  pMem  =  &pVar->mems[index];				   				
			  
			  if  (  !pZoneObj->hWndWallMem  )  continue;
			  if  (  pMem->tn_to_get_zoneObjs_layoutInfo_d3d  ==  pVar->d3d.tn_to_get_zoneObjs_layoutInfo_d3d  )  continue;

			  //
			  pMem->rect.iX  =  rc_zone.left  +  iX;
			  pMem->rect.iY  =  rc_zone.top  +  iY;
			  pMem->rect.iW  =  iW_desc  /  iRows;
			  pMem->rect.iH  =  iH_desc  /  iRows;
			  //
			  pMem->bSmallest  =  TRUE;
			  //
			  pMem->tn_to_get_zoneObjs_layoutInfo_d3d  =  pVar->d3d.tn_to_get_zoneObjs_layoutInfo_d3d;

			  //
			  cnt  ++  ;
		 }
	}



	iErr  =  0;
errLabel:
	return  iErr;

}






