

#ifndef  __isCliExPublic_h__
#define  __isCliExPublic_h__  //  {


extern  "C"  _declspec(  dllexport  )  BOOL  bSupported_rtsp(  );

//  2014/05/03
extern  "C"  _declspec(  dllexport  )  BOOL  bSupported_gps_default(  );


//  2014/08/03
extern  "C"  _declspec(  dllexport  )  BOOL  bSupported_remoteStorage_default(  );
extern  "C"  __declspec(  dllexport  )  BOOL  bSupported_fileServer_default(  );


//
extern  "C"  __declspec(  dllexport  )  BOOL  bUse_imObjView_as_guiWnd(  );

  //  2017/06/06
extern  "C"  __declspec(  dllexport  )    BOOL  bSupport_ts(  );



#endif  //  }


