



#ifndef  __shareAv_h__
#define  __shareAv_h__	//  {


//
 DWORD WINAPI mcThreadProc_app( LPVOID lpParameter );


//
DWORD WINAPI mcThreadProc_toShareAudio( LPVOID lpParameter );

//  2015/10/11
int  newstartQThreadToShareAv(  MC_VAR_common  *  pProcInfo,  int  iIndex_sharedObj,  BOOL  bAudio  );	//  2011/07/29
extern int  newstartQThreadToSaveIC(MC_VAR_common* pProcInfo);
extern int  newstartQThreadToCheckICFile(MC_VAR_common* pProcInfo);
extern bool  createSaveICPath();

#endif  //  }


