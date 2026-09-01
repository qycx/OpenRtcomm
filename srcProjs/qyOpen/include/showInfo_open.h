


#ifndef  __showInfo_open_h__
#define  __showInfo_open_h__	//  {

//
#ifdef  __cplusplus
  extern  "C"  {
#endif



//
__declspec(  dllexport  )  int  set_who_showInfo(  LPCTSTR  name  );
__declspec(dllexport)  int  set_who_showInfoA(char* name);

//
__declspec(  dllexport  )  int  showInfo_open0(  void  *  p0,  LPCTSTR  tWhere,  LPCTSTR  hint  );
__declspec(dllexport)  int  showInfo_openA(void* p0, char* where, char* hint);

//
__declspec(dllexport)  int  showInfo_open(void* p0, LPCTSTR  tWhere, unsigned  int* puiStep, LPCTSTR  hint);

//__declspec(  dllexport  )  int  showStatus_open(  void  *  p0,  LPCTSTR  tWhere,  LPCTSTR  hint,  int  iPos_toDisplay  );
__declspec(  dllexport  )  int  showState_open(  void* p0,  LPCTSTR tWhere, LPCTSTR hint, unsigned  short usStateType, unsigned  short usStateSubtype, SYSTEMTIME * when, int iPos_toDisplay, int iTaskId);




//
__declspec(dllexport)  int  initShowInfo_cli(void* p0, LPCTSTR  mutexName_syncQ, char* servIp, void** ppCtx_showInfo);
__declspec(dllexport) int  initShowInfo_func(void* p0, LPCTSTR  mutexName_syncQ, LPCTSTR  errHintWndCls, BOOL  bUsePipe, BOOL  bUseSock, char* servIp, BOOL  bCli, void** ppCtx_showInfo);

__declspec(dllexport)  void  exitShowInfo(void** ppCtx_showInfo);




//
#ifdef  __cplusplus
  }
#endif



#endif  //  }


