

#ifndef  __QISCAMCAP_OPEN_H__
#define  __QISCAMCAP_OPEN_H__	//  {

typedef  int  (  *  PF_setGuiOpen  )(  QIS_guiOpen  *  pGuiOpen  );


//  2010/08/02
typedef  int  (  *  PF_doInitRecordSound  )(  );
typedef  int  (  *  PF_doExitRecordSound  )(  );



//
typedef  int  (  *  PF_initVideoCapDev  )(  void  *  p_reserved,  LPCTSTR  devicePath_selected,  BITMAPINFOHEADER  *  pBih_suggested,  BOOL  bForConfig,  HWND hWnd,  void  **  ppVideoCapDevParam  );
typedef  int  (  *  PF_exitVideoCapDev  )(  void  **  ppVideoCapDevParam  );

typedef  BOOL  (  *  PF_bGetCapturePara  )(  void  *  pProcInfo,  int  iIndex_capBmp,  PF_BufferCB_av  pf,  unsigned  int  uiBufSize_pMsgBuf,  unsigned  int  uiBufSize_pBuf,  void  *  pVideoCapDevParam,  QY_VIDEO_HEADER  *  pVh_org  );

typedef  int  (  *  PF_startCapture  )(  void  *  pVideoCapDevParam  );
typedef  int  (  *  PF_stopCapture  )(  void  *  pVideoCapDevParam  );


//
typedef  struct  __param_sendCapPara_t		{
				  BITMAPINFOHEADER			bih_org;			//  图像数据应该是rgb的
 }		  PARAM_sendCapPara;

typedef  struct  __param_sendOutputPara_t	{
				 BOOL						canOutput;				
}		 PARAM_sendOutputPara;

//
#if  0
extern  "C"  __declspec(  dllexport  )  int  capDev_createNotifyWnd(  HINSTANCE  hInst,  LPCTSTR  appObjPrefix,  int  id,  HWND  *  phWnd  );
extern  "C"  __declspec(  dllexport  )  HWND  capDev_findPlayerNotifyWnd(  LPCTSTR  appObjPrefix,  int  id  );
extern  "C"  __declspec(  dllexport  )  int  capDev_waitForCapPara(  HWND  hCapDevNotifyWnd,  unsigned  int  dwTimeoutInMs,  BITMAPINFOHEADER  *  pbih_org  );
extern  "C"  __declspec(  dllexport  )  int  capDev_sendOutputPara(  PARAM_sendOutputPara  *  pParam,  HWND  hPlayerNotifyWnd  );


extern  "C"  __declspec(  dllexport  )  int  player_createNotifyWnd(  HINSTANCE  hInst,  LPCTSTR  appObjPrefix,  int  id,  HWND  *  phWnd  );
extern  "C"  __declspec(  dllexport  )  HWND  player_findCapDevNotifyWnd(  LPCTSTR  appObjPrefix,  int  id  );
extern  "C"  __declspec(  dllexport  )  int  player_sendCapPara(  PARAM_sendCapPara  *  pParam,  HWND  hCapDevNotifyWnd  );
extern  "C"  __declspec(  dllexport  )  int  player_waitToOutput(  HWND  hPlayerNotifyWnd,  LPCTSTR  appObjPrefix,  int  id,  unsigned  int  dwTimeoutInMs  );
#endif



#endif  //  }




