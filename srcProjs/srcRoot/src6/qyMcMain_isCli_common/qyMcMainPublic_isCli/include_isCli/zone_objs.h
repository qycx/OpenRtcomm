

#ifndef  __zone_objs_h__
#define  __zone_objs_h__	//  {

//
#include	"qyTimestamp.h"
#include	"qmcDefs.h"

//
#define		MAX_zoneObjs								MAX_activeTalkers	//  16


//  2015/12/04
typedef  struct  __zoneObj_t							{
				 HWND									hWndWallMem;
				 //
				 QY_MESSENGER_ID						idInfo;
				 int									iParam_reserved;
				 //
				 int									index;
				 DWORD									dwTickCnt_recent_avRecvd;
				 //
				 struct									{
					 BOOL								bWait;				 
					 DWORD								dwTickCnt_startToWait;
				 }										waitForPreRender;
				 //
}		 ZONE_obj;


//
typedef  struct  __recentAvRecvdMem_t					{
				 int									iIndex_zoneObj;
				 HWND									hTalker;
				 DWORD									dwTickCnt_recent_avRecvd;					
}		 RECENT_avRecvd_mem;




//
typedef  struct  __zoneObjs_t							{
				 //
				 QY_timestamp							ts_zoneObjs;
				 //  DWORD								dwModifiedTickCnt_zoneObjs;
				 //
				 int									iIndex_enlarged1;			//  被放大的index. 
				 //
				 struct									{
					 RECENT_avRecvd_mem					mems[2];
					 //
					 unsigned  int						uiCnt_recentAvRecvd;
				 }										recentAvRecvd;
				 //
				 ZONE_obj								mems[MAX_zoneObjs];
}		 ZONE_objs;


//
#define  isZoneObjIndexValid(  index  ) 	(  index  >=  0  &&  index  <  MAX_zoneObjs  )


#endif  //  }


