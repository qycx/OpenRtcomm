

#ifndef  __qyMessengerHelpPublic_h__
#define  __qyMessengerHelpPublic_h__	//  {

  __declspec(dllexport)  int   set_g_pQyMc_qyMessengerHelp(  void  *  pQyMc  );
  __declspec(dllexport)  int   set_g_dbPool_qyMessengerHelp(  void  *  pPool  );

   __declspec(  dllexport  )  BOOL  dll_PreTranslateMessage_qyMessengerHelp(  MSG  *  pMsg  );

  __declspec(  dllexport  )  BOOL  bViewImObjView_isCli(  HWND  hParent  );

  __declspec(  dllexport  )  int viewDlgLeftView_db(  HWND  hParent,  int  iWndContentType,  void  *  pSelParam  );

//
__declspec(  dllexport  )  int  toEditRtspUrlForConf(  TCHAR  *  url,  unsigned  int  cnt  );



//
__declspec(  dllexport  )  int  dyn_myOnAppAbout(  MC_VAR_isCli  *  pProcInfo,  HWND  hParent  );

//
int  viewDlgFileTransfer(  HWND  hParent  );








#endif

