

#ifndef  __QMCVIDEOCAPTUREDX_H__
#define  __QMCVIDEOCAPTUREDX_H__	//  {


#include	"qySampleGrabberPublic.h"

#ifdef  __WINCE__
		#define __RPC__deref_out   
#endif

 ////
 class  CMySampleGrabberCB  :  
			#ifndef  __SUPPORT_CUS_sampleGrabber__
					 public  ISampleGrabberCB
			#else
					 public  ISampleGrabberCB_is	
			#endif
{
    public:

		SAMPLE_grabberCb_var			m_var;

		CMySampleGrabberCB(  )  {
			OutputDebugString(  _T(  "CMySampleGrabberCB called"  )  );
			memset(  &m_var,  0,  sizeof(  m_var  )  );
			return;
		}
		~CMySampleGrabberCB(  )  {
			OutputDebugString(  _T(  "~CMySampleGrabberCB called"  )  );
#if  0
			if  (  m_var.pBuf  )  {
				MACRO_qyAssert(  0,  _T(  "SampleGrabber: pBuf should be free in exitVideoCapDev(  )."  )  );				
			}
			MACRO_safeFree(  m_var.pBuf  );
#endif
			//
			if  (  m_var.pMsgBuf  )  {
				MACRO_qyAssert(  0,  _T(  "SampleGrabber: pMsgBuf should be free in exitVideoCapDev(  )."  )  );			
			}
			MACRO_safeFree(  m_var.pMsgBuf  );
			//
			MACRO_safeFree(  m_var.cache.pBuf  );
			return;
		}


        virtual HRESULT STDMETHODCALLTYPE SampleCB( 
            double SampleTime,
            IMediaSample *pSample);
        
        virtual HRESULT STDMETHODCALLTYPE BufferCB( 
            double SampleTime,
            BYTE *pBuffer,
            long BufferLen);

		virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
                /* [in] */ REFIID riid,
                /* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject)
		{
				#ifndef  __SUPPORT_CUS_sampleGrabber__
					if  (  riid  ==  IID_ISampleGrabberCB  ||  riid  ==  IID_IUnknown  )  {
						 *ppvObject  =  (  void  *  )static_cast<  ISampleGrabberCB  *  >(  this  );
						return  NO_ERROR;
					}
				#else
					if  (  riid  ==  IID_ISampleGrabberCB_is  ||  riid  ==  IID_IUnknown  )  {			
						*ppvObject  =  (  void  *  )static_cast<  ISampleGrabberCB_is  *  >(  this  );		
						return  NO_ERROR;			
					}									
				#endif

				return  E_NOINTERFACE;
		}

         
		virtual ULONG STDMETHODCALLTYPE AddRef( void)  {
			OutputDebugString(  _T(  "Not finished here: CMySampleGrabberCB.AddRef\n"  )  );
			return  2;
		}

		virtual ULONG STDMETHODCALLTYPE Release( void)  {
			OutputDebugString(  _T(  "Not finished here: CMySampleGrabberCB.Release\n"  )  );
			return  1;
		}
		
        
};


//  2011/12/26
typedef  struct  __sampleGrabberInfo_t					{
	
				 IBaseFilter						*	m_pGrabberFilter;
				 #ifndef  __SUPPORT_CUS_sampleGrabber__
						  ISampleGrabber			*	m_pGrabber;
				 #else
						  ISampleGrabber_is			*	m_pGrabber;
				 #endif
				 IBaseFilter						*	m_pNullRenderer;

				 CMySampleGrabberCB					*	m_pCallBack;
				 
}		 SAMPLE_grabber_info;


#if !defined(  __WINCE__  )  ||  defined(  __TEST__  )

#if  0
 typedef  struct _capstuff
{
    WCHAR wszCaptureFile[_MAX_PATH];
    WORD wCapFileSize;  // size in Meg
    
	//  ISampleCaptureGraphBuilder *pBuilder;
	ICaptureGraphBuilder2	*	pBuilder;

    IVideoWindow *pVW;
    IMediaEventEx *pME;
    IAMDroppedFrames *pDF;
    IAMVideoCompression *pVC;
    //  IAMVfwCaptureDialogs *pDlg;
    IAMStreamConfig *pASC;      // for audio cap
    IAMStreamConfig *pVSC;      // for video cap
    IBaseFilter *pRender;
    IBaseFilter *pVCap, *pACap;
    IGraphBuilder *pFg;
    IFileSinkFilter *pSink;
    IConfigAviMux *pConfigAviMux;
    int  iMasterStream;
    BOOL fCapturing;

	BOOL fPreviewing;

    BOOL fMPEG2;
    BOOL fCapAudio;
    BOOL fCapCC;
    BOOL fCCAvail;
    BOOL fCapAudioIsRelevant;

    //  bool fDeviceMenuPopulated;
 
	IMoniker *rgpmVideoMenu[10];
	IMoniker *rgpmAudioMenu[10];
#ifdef  __DEBUG__
      IMoniker *pmVideo;
      IMoniker *pmAudio;
#endif

	int		iMenuIds_video[10];
	int		iMenuIds_audio[10];
	int		iMenuId_selectedVideo;
	int		iMenuId_selectedAudio;
	TCHAR	names_video[10][64  +  1];
	TCHAR	names_audio[10][64  +  1];

	GUID	guid_audio[10];				//  2011/10/23

	double	FrameRate;

	BOOL fWantPreview;

    long	lCapStartTime;
    long	lCapStopTime;
    //  WCHAR	wachFriendlyName[120];
    BOOL	fUseTimeLimit;
    BOOL	fUseFrameRate;
    DWORD	dwTimeLimit;
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
    //  CCrossbar *pCrossbar;
    int iVideoInputMenuPos;
    LONG NumberOfVideoInputs;
    HMENU hMenuPopup;

    //  int iNumVDevices;
	//  int	iNumADevices;
	int	iNumVCapDevices;
	int	iNumACapDevices;

} CAP_STUFF;
#endif

//  2011/12/28
#define	CAP_STUFF	AV_capStuff


#endif

 typedef  struct  __qmcCaptureGraphBuilder_t	{
	 	 
				 BOOL						bInited;

				 ICaptureGraphBuilder2	*	m_pCapture;

				 IGraphBuilder			*	m_pGB;
				 IMediaControl			*	m_pMC;
				 IVideoWindow			*	m_pVW;
				 IMediaEventEx			*	m_pME;					//  2013/03/19


				 IMoniker				*	m_pMoniker;				//  2009/08/16
				 IBaseFilter			*	m_pBF;

				 IAMStreamConfig		*	m_pVSC;					//  for video cap
				 IAMStreamConfig		*	m_pASC;					// for audio cap


				 IBaseFilter			*	m_pDecFilter;			//  for mjpg. 2009/04/10

				 //  2012/03/22
				 BOOL						bCalled_Run;			//  

				 //  2012/03/21
				 int						nStep_FillBuffer;
				 BOOL						bFailed_FillBuffer;
				 DWORD						dwTickCnt_leave_FillBuffer;
				 int						iDiffInMs_leave_2_enter_FillBuffer;

}		  QMC_captureGraphBuilder;


#include	"amCapProc.h"



 typedef  struct  __VIDEO_capDev_dx_t		{

				  //	 
				  void					*	p_gcap;
				  				
				  //				 
				  SAMPLE_grabber_info		video;
				  				  
				  //				 
				  BOOL						bQuit;
				  QY_Q2					*	pQ2;
				  BOOL						bQInited;
				  
				  unsigned  int				uiBufSize_pPkt;				 
				  char					*	pPkt;

}		 VIDEO_capDev_dx;


 //  2013/03/19
 typedef  struct  __audioCapDevDx_t			{

				  BOOL						bInited;

				  QMC_captureGraphBuilder	m_captureGraphBuilder;
				  //
				  SAMPLE_grabber_info		audio;

 }		  AUDIO_capDev_dx;



 //
int  initCaptureGraphBuilder(  QMC_captureGraphBuilder  *  p,  void  *  pDebugStepParam  );
int  exitCaptureGraphBuilder(  QMC_captureGraphBuilder  *  p,  void  *  pDebugStepParam  );


 typedef  struct  __qmcFilterGraph_t		{

				 QMC_captureGraphBuilder	m_captureGraphBuilder;

				 //
				 IBaseFilter			*	m_pGrabberFilter;
				 #ifndef  __SUPPORT_CUS_sampleGrabber__
						  ISampleGrabber			*	m_pGrabber;
				 #else
						  ISampleGrabber_is			*	m_pGrabber;
				 #endif
				 
				 IBaseFilter			*	m_pNullRenderer;

				 CMySampleGrabberCB		*	m_pCallBack;


				 BOOL						bQuit;
				 QY_Q2					*	pQ2;
				 BOOL						bQInited;

				 unsigned  int				uiBufSize_pPkt;
				 char					*	pPkt;

}		 QMC_FILTER_GRAPH;


 //
//  #define	exitFilterGraph(  ppFilterGraph  )	exitVideoCapDev_dx(  ppFilterGraph  )
int  exitFilterGraph(  void  **  ppVideoCapDevParam,  void  *  pDebugStepParam  );





//
HRESULT myCopyMediaType(__out AM_MEDIA_TYPE *pmtTarget, const AM_MEDIA_TYPE *pmtSource);

void myFreeMediaType(  AM_MEDIA_TYPE& mt);

void WINAPI myDeleteMediaType(__inout_opt AM_MEDIA_TYPE *pmt);


EXTERN_C const CLSID CLSID_NullRenderer;


#endif  //  }



