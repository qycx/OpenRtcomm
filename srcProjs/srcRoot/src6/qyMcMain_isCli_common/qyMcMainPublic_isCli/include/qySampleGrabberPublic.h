
#ifndef  __QYSAMPLEGRABBERPUBLIC_H__
#define  __QYSAMPLEGRABBERPUBLIC_H__	//  {


DEFINE_GUID(CLSID_SampleGrabber_is,
			0xad5db5b4,  0xd1ab,  0x4f37,  0xa6,  0xd,  0x21,  0x51,  0x54,  0xb4,  0xec,  0xc1  );


DEFINE_GUID(IID_ISampleGrabber_is,
			0x4951bff,  0x696a,  0x4ade,  0x82,  0x8d,  0x42,  0xa5,  0xf1,  0xed,  0xb6,  0x31  );

// {26FCFEEC-708C-4837-99A3-19B2D60CF589}
DEFINE_GUID(IID_ISampleGrabberCB_is, 
			0x26fcfeec, 0x708c, 0x4837, 0x99, 0xa3, 0x19, 0xb2, 0xd6, 0xc, 0xf5, 0x89);

/////////////////////

// {3C5FAF6F-8636-42eb-BED6-BDD5AB6A4CCC}
DEFINE_GUID(CLSID_NullRenderer_is, 
	0x3c5faf6f, 0x8636, 0x42eb, 0xbe, 0xd6, 0xbd, 0xd5, 0xab, 0x6a, 0x4c, 0xcc);


//
// {EED91025-DF77-4e96-8DA6-B9C01D3DDE0F}
DEFINE_GUID(CLSID_VCam_is, 
0xeed91025, 0xdf77, 0x4e96, 0x8d, 0xa6, 0xb9, 0xc0, 0x1d, 0x3d, 0xde, 0xf);

// {2BC237FD-EAC1-4014-9BF3-DF90E1D109B0}
DEFINE_GUID(CLSID_NetSender_is, 
0x2bc237fd, 0xeac1, 0x4014, 0x9b, 0xf3, 0xdf, 0x90, 0xe1, 0xd1, 0x9, 0xb0);




//  2012/02/03
int  getNewFilter(  REFCLSID  rclsid,  void  *  pParam,  void  **  ppIBaseFilter  );


//
typedef  int  (  *  PF_getNewFilter  )(  REFCLSID  rclsid,  void  *  pParam,  void  **  ppIBaseFilter  );
#if  0
typedef  void  *  (  *  PF_newCrossBar  )(  void  *  pStartingInputPin,  HRESULT  *  phr  );
typedef  void  (  *  PF_freeCrossBar  )(  void  *  pCrossBarParam  );
typedef  int  (  *  PF_crossBarGetInputCount  )(  void  *  pCrossBarParam,  long  *  pCount  );
#endif




//
typedef  struct  __ParamVCam_t			{

				 void				*	pAmMediaType;						//  const  AM_MEDIA_TYPE  *  

				 unsigned  int			uiBufSize_pPkt;
				 BOOL					bPkt_MIS_MSG_procVideo_qmc;			//  2012/02/05

				 void				*	pDmoInfo;
				 BOOL				*	pbQuit;
				 void				*	pQ2;
				 void				*	pf_q2GetMsg;
				 void				*	pDebugStep;							//  2012/03/21
				 //
				 int				*	pnStep_FillBuffer;					//  这表明FillBuffer被调用. 2012/03/21
				 BOOL				*	pbFailed_FillBuffer;				//  表明FillBuffer失败
				 DWORD				*	pdwTickCnt_leave_FillBuffer;
				 int				*	piDiffInMs_leave_2_enter_FillBuffer;

				 //
				 unsigned  char			ucbPrint_a;
				 unsigned  char			ucbPrint_v;

}		 PARAM_vCam;


#define  bSubtypeGrabbable(  subtype  )  (  subtype  ==  MEDIASUBTYPE_RGB24		\
										||  subtype  ==  MEDIASUBTYPE_RGB32		\
										||  subtype  ==  MEDIASUBTYPE_YUY2		\
										||  subtype  ==  MEDIASUBTYPE_YV12		\
										||  subtype  ==  WMCMEDIASUBTYPE_I420	\
										||  subtype  ==  MEDIASUBTYPE_RGB565	\
										||  subtype  ==  MEDIASUBTYPE_MJPG	\
										)
				
//////////////////////////////

#ifdef  __strmif_h__



DECLARE_INTERFACE_(ISampleGrabberCB_is,  IUnknown  )
{
    public:
        virtual HRESULT STDMETHODCALLTYPE SampleCB( 
            double SampleTime,
            IMediaSample *pSample) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BufferCB( 
            double SampleTime,
            BYTE *pBuffer,
            long BufferLen) = 0;
        
};

DECLARE_INTERFACE_(ISampleGrabber_is,  IUnknown  )
{
	//  STDMETHOD(  RegisterCallback  )(  MANAGEDCALLBACKPROC  callback  )  PURE;

	virtual HRESULT STDMETHODCALLTYPE SetMediaType( 
            const AM_MEDIA_TYPE *pType) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetConnectedMediaType( 
            AM_MEDIA_TYPE *pType) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetBufferSamples( 
            BOOL BufferThem) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetCallback( 
            ISampleGrabberCB_is *pCallback,
            long WhichMethodToCallback) = 0;


};

HRESULT  myGetPin(  IBaseFilter  *  pFilter,  PIN_DIRECTION  PinDir,  IPin  **  ppPin  );
HRESULT  ConnectFilters(  IGraphBuilder  *  pGraph,  IBaseFilter  *  pFirst,  IBaseFilter  *  pSecond  );
HRESULT  newConnectFilters(  IGraphBuilder  *  pGraph,  IBaseFilter  *  pFirst,  IBaseFilter  *  pSecond,  REFGUID  majorType  );

void WINAPI myDumpGraph(IFilterGraph *pGraph, DWORD dwLevel);
void WINAPI myDisplayType(LPCTSTR label, const AM_MEDIA_TYPE *pmtIn);

 
#endif

#endif

