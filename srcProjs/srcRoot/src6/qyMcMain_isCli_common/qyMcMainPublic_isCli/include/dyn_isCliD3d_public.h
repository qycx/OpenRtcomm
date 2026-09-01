
#ifndef  __dyn_isCliD3d_public_h__
#define  __dyn_isCliD3d_public_h__	//  {

//
//
BOOL  dyn_bD3dUsing(  CCtxQmc		*	pProcInfo,  BOOL  *  pm_bActive  );
BOOL  dyn_bFullScreen_d3dWnd(  CCtxQmc  *  pProcInfo,  HWND  hD3dWnd  );

//
int  dyn_removeMosaicFromD3dWall(  CCtxQmcTmpl  *  pProcInfoCommon,  int  iIndex_sharedObj  );
int  dyn_getVal_bExists_mosaic(  CCtxQmcTmpl  *  pProcInfoCommon,  int  iIndex_sharedObj,  BOOL  *  pbExists  );

//
//
int  dyn_tryToTalkToMessenger_d3dWall(  CCtxQmc  *  pProcInfo,  QY_MESSENGER_ID  *  pIdInfo,  int  iTalkUsage,  BOOL  bNeedExist_hWnd,  HWND  *  phWnd_mgr  );

//
int  dyn_closeConsoleWall(  CCtxQmcTmpl  *  pProcInfoCommon,  void  *  pGBuf_d3d  );

 

#endif  //  }


