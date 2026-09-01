
#ifndef  __AMCAPPROC_H__
#define  __AMCAPPROC_H__		//  {

#include	"mmDeviceProc.h"

//
#ifndef  __SUPPORT_ISampleCaptureGraphBuilder__
			#define	ISampleCaptureGraphBuilder	void
#endif
#ifndef  __SUPPORT_CCrossbar__
			#define	CCrossbar					void
#endif

 typedef  struct _capstuff
{
    WCHAR wszCaptureFile[_MAX_PATH];
    WORD wCapFileSize;  // size in Meg
    ISampleCaptureGraphBuilder *pBuilder;
    IVideoWindow *pVW;
    IMediaEventEx *pME;
    IAMDroppedFrames *pDF;
    IAMVideoCompression *pVC;
    IAMVfwCaptureDialogs *pDlg;
    IAMStreamConfig *pASC;      // for audio cap
    IAMStreamConfig *pVSC;      // for video cap
    IBaseFilter *pRender;
    IBaseFilter *pVCap, *pACap;
    IGraphBuilder *pFg;
    IFileSinkFilter *pSink;
    IConfigAviMux *pConfigAviMux;
    int  iMasterStream;
    BOOL fCaptureGraphBuilt;
    BOOL fPreviewGraphBuilt;
    BOOL fCapturing;
    BOOL fPreviewing;
    BOOL fMPEG2;
    BOOL fCapAudio;
    BOOL fCapCC;
    BOOL fCCAvail;
    BOOL fCapAudioIsRelevant;
    bool fDeviceMenuPopulated;
    IMoniker *rgpmVideoMenu[10];
    IMoniker *rgpmAudioMenu[10];
    IMoniker *pmVideo;
    IMoniker *pmAudio;
    double FrameRate;
    BOOL fWantPreview;
    long lCapStartTime;
    long lCapStopTime;
    WCHAR wachFriendlyName[120];
    BOOL fUseTimeLimit;
    BOOL fUseFrameRate;
    DWORD dwTimeLimit;
    int iFormatDialogPos;
    int iSourceDialogPos;
    int iDisplayDialogPos;
    int iVCapDialogPos;
    int iVCrossbarDialogPos;
    int iTVTunerDialogPos;
    int iACapDialogPos;
    int iACrossbarDialogPos;
    int iTVAudioDialogPos;
    int iVCapCapturePinDialogPos;
    int iVCapPreviewPinDialogPos;
    int iACapCapturePinDialogPos;
    long lDroppedBase;
    long lNotBase;
    BOOL fPreviewFaked;
    CCrossbar *pCrossbar;
    int iVideoInputMenuPos;
    LONG NumberOfVideoInputs;
    HMENU hMenuPopup;
    int iNumVCapDevices;
	int iNumACapDevices;		//  2013/03/19
	//
	//  2011/12/29
	HWND ghwndApp;
	//
	//  2012/01/04
	OLD_audioDevices			old_audioDevices;


} AV_capStuff;	//  gcap;

__declspec(dllexport)  void  *  get_ICaptureGraphBuilder(  void  *  pBuilderParam  );

__declspec(dllexport) void TearDownGraph(  AV_capStuff  &  gcap );

__declspec(dllexport) BOOL InitCapFilters(  AV_capStuff  &  gcap  );
__declspec(dllexport) void FreeCapFilters(  AV_capStuff  &  gcap  );

__declspec(dllexport) BOOL BuildPreviewGraph(  AV_capStuff  &  gcap  );
__declspec(dllexport) BOOL StartPreview(  AV_capStuff  &  gcap  );
__declspec(dllexport) BOOL StopPreview(  AV_capStuff  &  gcap  );

__declspec(dllexport) BOOL StopCapture(AV_capStuff  &  gcap);

void ErrMsg_amCap(LPTSTR szFormat,...);
void ResizeWindow_amCap(HWND  ghwndApp,  int w, int h);
int statusGetHeight_amCap(void);

__declspec(dllexport) void ChooseDevices(AV_capStuff  &  gcap,IMoniker *pmVideo, IMoniker *pmAudio);
__declspec(dllexport) void ChooseDevices(AV_capStuff  &  gcap,TCHAR *szVideo, TCHAR *szAudio);


#define		MENU_ADEVICE0		ID_MENU_ADEVICE0
#define		MENU_VDEVICE0		ID_MENU_VDEVICE0


#define		SAFE_RELEASE( x  )	MACRO_safeRelease(  x  )

__declspec(dllexport) void IMonRelease(IMoniker *&pm);


#include	"amcapPublic.h"


#endif  //  }


