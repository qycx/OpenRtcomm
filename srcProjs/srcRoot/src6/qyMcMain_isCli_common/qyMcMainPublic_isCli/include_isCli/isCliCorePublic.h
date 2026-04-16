

#ifndef  __isCliCorePublic_h__
#define  __isCliCorePublic_h__	//  {

//
#include	"zone_objs.h"
#include	"ctxQmc.h"

//
extern  "C" __declspec(dllexport)  int   set_g_pQyMc_isCliCore(  void  *  pQyMcParam  );


 //
 __declspec(  dllexport  )  int  addWndToZoneObjs(  CCtxQmc  *  pProcInfo,  CTX_qm_thread  *  pCqt,  HWND  hWnd,  int  iWndContentType,  QY_MESSENGER_ID  *  pIdInfo1,  int  iParam_reserved,  ZONE_objs  *  pZoneObjs,  int  *  piIndex_wall  );
 __declspec(  dllexport  )  int  removeWndFromZoneObjs(  CCtxQmc  *  pProcInfo,  CTX_qm_thread  *  pCqt,  HWND  hDlgTalk,  int  iWndContentType,  ZONE_objs  *  pZoneObjs  );



 //
 __declspec(  dllexport  )  int  set_enlarged_gZone(  CCtxQmc  *  pProcInfo,  HWND  hWnd  );
 __declspec(  dllexport  )  int  set_recentAvRecvd_gZone(  CCtxQmc  *  pProcInfo,  HWND  hWnd  );



 //
__declspec(  dllexport  )  int  chkZoneObjs(  CTX_qm_thread  *  pCqt,  ZONE_objs  *  pZoneObjs  );


//
//
__declspec(  dllexport  ) int  get_zoneObjs_layoutInfo(  CCtxQmc  *  pProcInfo,  ZONE_objs  *  pZoneObjs,  RECT  rc_zone,  BOOL  bAutoEnlarge,  void  *  pZONE_objs_info  );
//
__declspec(  dllexport  ) int  get_zoneObjs_layoutInfo_d3d(  CCtxQmc  *  pProcInfo,  ZONE_objs  *  pZoneObjs,  RECT  rc_zone,  BOOL  bAutoEnlarge,  void  *  pZONE_objs_info  );


//
//
__declspec(  dllexport  )  int  addTalkerToGZone(  CTX_qm_thread  *  pCqt,  HWND  hDlgTalk,  int  iWndContentType,  QY_MESSENGER_ID  *  pIdInfo,  int  iParam_reserved,  int  *  piIndex_wall  );
__declspec(  dllexport  )  int  removeTalkerFromGZone(  CCtxQmc  *  pProcInfo,  HWND  hDlgTalk,  int  iWndContentType  );
__declspec(  dllexport  )  BOOL  isTalkerInGZone(  HWND  hDlgTalk,  int  iWndContentType,  int  *  piIndex_wall  );



#endif  //  }


