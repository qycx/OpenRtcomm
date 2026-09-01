
#ifndef  __QYAVRECORDPUBLIC_H__
#define  __QYAVRECORDPUBLIC_H__		//  {

//
#include	"qmcCommFunc_is_open.h"
#include	"ctxQmc.h"


//  #define		IMonRelease(  x  )	MACRO_safeRelease(  x  )


 __declspec(  dllexport  )  int  initAvRecordMgr(  HINSTANCE  g_hInst  );
 __declspec(  dllexport  )  void  exitAvRecordMgr(  );


 BOOL  bDSoundToPlayInited(  );
 int initDSoundToPlay2( void  *  pDynLib_dx,  LPCGUID lpcGUID,  HWND  hWnd,  void  *  p2  );
 void  exitDSoundToPlay2(  void  *  pDynLib_dx,  void  *  p1,  void  *  p2  );


//__declspec(  dllexport  ) int  toSelectRegion(  HWND  hWndStarter,  BOOL  bCapFullScreen,  BOOL  bRemoteAssist,  BOOL  bDirectX,  int  iParam  =  -1  );	
__declspec(  dllexport  ) int  toSelectRegion1(  HWND  hWndStarter,  BOOL  bCapFullScreen,  BOOL  bRemoteAssist,  BOOL  bDirectX,  int  level,  int  iParam  =  -1  );

 __declspec(  dllexport  )  RECT  getSelectedRect(  );
 //  int  setSelectedRect(  int  biWidth,  int  biHeight  );
 __declspec(  dllexport  )  BOOL  bRemoteAssist_avRecord(  );
 __declspec(  dllexport  )  BOOL  bDirectX_avRecord(  );
 __declspec(  dllexport  )  int  getLevel_avRecord(  );
 __declspec(  dllexport  )  int  getiParam_avRecord(  );


#ifdef  __DEBUG__
		int  getBmpInfo_avRecord(  int  left,  int  top,  int  width,  int  height,  BITMAPINFO  *  pBmpInfo  );
#endif


 int  chkRectSizePos(  );
 
 __declspec(  dllexport  )  int  setFps_capScreen(  int  fps  );

__declspec(  dllexport  ) void  stopAll_avRecord(  );

__declspec(  dllexport  )  int  getSize_qyAvRecord(  );


//
void  *  CAP_STUFF_new(  );
void  CAP_STUFF_free(  void  *  pCap  );
void  CAP_STUFF_exit(  void  *  pCap  );

 BOOL  CAP_STUFF_bAudio(  void  *  p  );
 BOOL  CAP_STUFF_bVideo(  void  *  p  );

 //
 void  myChooseDevices(  void  *  p_gcap,void  *  pIMoniker_v, void  *  pIMoniker_a  );

 //
 int  get_iNumADevices(void* pCapParam);
 int get_iNumVCapDevices(void* pCapParam);


 int  get_iNumADevices(void* pCapParam, QY_DMITEM* pSkippedTable,bool bPrint);
 int get_iNumVCapDevices(void* pCapParam, QY_DMITEM* pSkppedTable,bool bPrint);



 //
void  *  getADeviceGuid(  void  *  pCapParam,  int  iMenuId,  TCHAR  *  devDesc,  int  devDescCnt  );		//  2011/10/24
void  *  getMoniker_a(  void  *  pCapParam,  int  iMenuId  );



//
int  getADevFriendlyName(  void  *  pCapParam,  BOOL  bIncludeAudio,  int  iMenuId,  TCHAR  *  name,  int  cnt  );



void  addDevicesToMenu(  void  *  pCap,  BOOL  bIncludeACap,  HWND  hWnd  );
void  addDevicesToMenu_shadow(  void  *  pCapParam,  BOOL  bIncludeACap,  HWND  hWnd  );

//  
void  chooseAvDevice(  void  *  pCap,  BOOL  bIncludeACap,  HWND  hWnd,  HWND  hWndStatus,  int  iMenuId  );
void  chooseAvDevice_shadow(  void  *  pCapParam_mgr,  BOOL  bIncludeACap,  HWND  hShadow,  HWND  hWndStatus,  int  iMenuId  );


int  saveChosenDevice(  void  *  pCapParam,  BOOL  bIncludeACap,  int  iMenuId  );
int  getChosenDevice(  TCHAR  *  recorder_selected,  unsigned  int  uiCnt_recorder_selected,  TCHAR  *  webcam_selected,  unsigned  int  uiCnt_webcam_selected,
						void  *  pCapParam,  BOOL  bIncludeACap,  int  *  piMenuId_selectedAudio,  int  *  piMenuId_selectedVideo  );


//
int  processInput_post(  void  *  pProcInfoParam,  int  nAvgBytesPerSec,  BYTE  *  pbInput1,  unsigned  int  dwNumBytes,  MIS_MSGU  *  pMsgBuf  );


//  2013/03/19
int  initAudioCapDev_dx(  void  *  p_reserved,  LPCTSTR  displayName_selected,  void  **  ppCapStuff,  AUDIO_COMPRESSOR_CFG  *  pCompressor,  BOOL  bForConfig,  HWND hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppAudioCapDevParam  );
int  exitAudioCapDev_dx(  void  **  ppAudioCapDevParam  );
BOOL  bGetCapturePara_audioCapdev(  MC_VAR_common  *  pProcInfo,  int  iIndex_capAudio,  unsigned  int  uiBufSize_pMsgBuf,  void  *  pAudioCapDevParam,  WAVEFORMATEX  *  pWf_org,  SAMPLE_grabberCb_cache  *  pCache  );
int  startAudioCapDev_dx(  void  *  pAudioCapDevParam  );
int  stopAudioCapDev_dx(  void  *  pAudioCapDevParam  );



BOOL  bAudioOnly(  void  *  pSharedMediaFileParam  );
BOOL  bNoAudio(  void  *  pSharedMediaFileParam  );


//
BOOL  bGetCapturePara_shareMediaObj(  MC_VAR_common  *  pProcInfo,  unsigned  int  uiCapType,  
			int  iIndex_capAudio,  unsigned  int  uiBufSize_pMsgBuf_a,  void  *  pSampleGrabberInfo_a,  WAVEFORMATEX  *  pWf_org,  
			int  iIndex_capBmp,  unsigned  int  uiBufSize_pMsgBuf_v,  void  *  pSampleGrabberInfo_v,  QY_VIDEO_HEADER  *  pVh_org,  
			SAMPLE_grabberCb_cache  *  pCache_unused  );




//
int  handleGraphEvent_mediaFile(  void  *  pShareMediaFile,  BOOL  bMediaFile,  BOOL  bLooping,  BOOL  bPlayThrough  );
int  handleGraphEvent_mediaDevice(  void  *  pShareMediaDevice  );
int  handleGraphEvent_videoCapDev_dx(  void  *  pVideoCapDevParam  );
int  handleGraphEvent_audioCapDev_dx(  void  *  pAudioDevCapParam  );


//
//  int  fixPlayCfg(  MC_VAR_isCli  *  pProcInfo,  AUDIO_PLAY_CFG  *  pPlayCfg  );
//  BOOL  tmpHandler_bOldAudio(  void  *  p0,  QY_PLAYER  *  pPlayer,  myPLAY_AUDIO_DATA  *  pPkt  );
BOOL  tmpHandler_bOldAudio(  DWORD  dwTickCnt_now,  QY_PLAYER  *  pPlayer,  myPLAY_AUDIO_DATA  *  pPkt  );



extern "C" DWORD WINAPI mcThreadProc_recordSound( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_aec( LPVOID lpParameter );


extern "C" DWORD WINAPI mcThreadProc_playAudio( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_playVideo( LPVOID lpParameter );




//
//  extern "C" DWORD WINAPI mcThreadProc_decVideo_rtsp( LPVOID lpParameter );


extern "C" DWORD WINAPI mcThreadProc_dispatchAudio( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_dispatchVideo( LPVOID lpParameter );

//  2017/01/28
extern  "C" DWORD  WINAPI  coreAudioRecThreadFunc(LPVOID ignored);



#endif  //  }


