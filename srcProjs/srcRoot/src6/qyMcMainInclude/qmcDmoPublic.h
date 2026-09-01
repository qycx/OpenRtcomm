

#ifndef  __QMCDMOPUBLIC_H__
#define  __QMCDMOPUBLIC_H__		//  {

class  CCtxQyMc;


 int  enumDmos(  void  *  pDynLib_dx,  const  GUID  *  clsid_category,  HWND    hComboBox  );
 int  getDmoInfoBySth(  CCtxQyMc  *  pQyMc,  void  *  pDynLib_dx,  const  GUID  *  clsid_category,  LPCTSTR  dmoName,  const  GUID  *  clsid_input,  QY_AUDIO_HEADER  *  pAh_input,  const  GUID  *  clsid_output,  QY_AUDIO_HEADER  *  pAh_output,  GUID  *  pDmoClsid,  void  *  pCompressor  );
 int  enumDmoIoTypes(  CCtxQyMc  *  pQyMc,  const  GUID  *  clsid,  const  GUID  *  clsid_input,  QY_AUDIO_HEADER  *  pAh_input,  BOOL  *  pbInputSupported,  const  GUID  *  clsid_output,  QY_AUDIO_HEADER  *  pAh_output,  BOOL  *  pbOutputSupported,  HWND  hComboBox  );


  int  getComplexitySettings(  const  GUID  *  gMyClsid,  DWORD  fourcc,  DWORD* pLive, DWORD* pOffline, DWORD* pMax);


 int  initCompressVideo_dmo(  VIDEO_COMPRESSOR_CFG  *  pCompressor,  QY_VIDEO_HEADER  *  pVh_decompress,  QY_VIDEO_HEADER  *  pVh_compress,  MY_DMO_INFO  *  pDmoInfo  );
 int  exitCompressVideo_dmo(  MY_DMO_INFO  *  pDmoInfo  );
 int  compressVideo_dmo(  MY_DMO_INFO  *  pDmoInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput  );

int  initDecompressVideo_dmo(  const  VIDEO_COMPRESSOR_CFG  *  pCompressor,  QY_VIDEO_HEADER  *  pVh_compress,  QY_VIDEO_HEADER  *  pVh_decompress,  MY_DEBUG_STEP  *  pDebugStep,  MY_DMO_INFO  *  pDmoInfo  );
int  exitDecompressVideo_dmo(  MY_DMO_INFO  *  pDmoInfo  );
int  decompressVideo_dmo(  MY_DMO_INFO  *  pDmoInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  );


#if  0
int  initDecompressVideo_filterGraph(  const  VIDEO_COMPRESSOR_CFG  *  pCompressor,  QY_VIDEO_HEADER  *  pVh_compress,  QY_VIDEO_HEADER  *  pVh_decompress,  MY_DEBUG_STEP  *  pDebugStep,  MY_DMO_INFO  *  pDmoInfo  );
int  decompressVideo_filterGraph(  MY_DMO_INFO  *  pDmoInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  );


//int  exitDecompress_filterGraph(  MY_DMO_INFO  *  pDmoInfo,  MY_DEBUG_STEP  *  pDebugStep  );
#endif


//
 int  getDmoOutputByIndex(  MY_DMO_INFO  *  pDmoInfo,  int  index,  BYTE *  pbOutData,  unsigned  int  *  puiDataSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  pui_rtTimeLen  );
 int  dmoClearOutputs(  MY_DMO_INFO  *  pDmoInfo  );
 void  freeDmoOutputs(  MY_DMO_INFO  *  pDmoInfo  );



#ifdef  __DEBUG__

		DEFINE_GUID(  CLSID_WMVideo8_Encoder_DMO, 0x7E320092,0x596A,0x41B2,0xBB,0xEB,0x17,0x5D,0x10,0x50,0x4E,0xB6  );
		DEFINE_GUID(  CLSID_WMVideo9_Encoder_DMO, 0xD23B90D0,0x144F,0x46BD,0x84,0x1D,0x59,0xE4,0xEB,0x19,0xDC,0x59  );
		DEFINE_GUID(  CLSID_MSScreen9_Encoder_DMO, 0xF7FFE0A0,0xA4F5,0x44B5,0x94,0x9E,0x15,0xED,0x2B,0xC6,0x6F,0x9D  );

		DEFINE_GUID(  CLSID_WMVideo_Decoder_DMO, 0x82D353DF,0x90BD,0x4382,0x8B,0xC2,0x3F,0x61,0x92,0xB7,0x6E,0x34  );


		//
		DEFINE_GUID(  CLSID_WMSpeech_Encoder_DMO, 0x1F1F4E1A,0x2252,0x4063,0x84,0xBB,0xEE,0xE7,0x5F,0x88,0x56,0xD5  );
		DEFINE_GUID(  CLSID_WMSpeech_Decoder_DMO, 0x874131CB,0x4ECC,0x443B,0x89,0x48,0x74,0x6B,0x89,0x59,0x5D,0x20  );

		DEFINE_GUID(  CLSID_WMAudio_Encoder_DMO, 0x70F598E9,0xF4AB,0x495A,0x99,0xE2,0xA7,0xC4,0xD3,0xD8,0x9A,0xBF  );
		DEFINE_GUID(  CLSID_WMAudio_Decoder_DMO, 0x2EEB4ADF,0x4578,0x4D10,0xBC,0xA7,0xBB,0x95,0x5F,0x56,0x32,0x0A  );

		DEFINE_GUID(  CLSID_MP3_Decoder_DMO,	 0xBBEEA841,0x0A63,0x4F52,0xA7,0xAB,0xA9,0xB3,0xA8,0x4E,0xD3,0x8A  );


#endif

#ifndef MEDIASUBTYPE_NV11_DEFINED
#define MEDIASUBTYPE_NV11_DEFINED
		DEFINE_GUID(  MEDIASUBTYPE_NV11,  0x3131564E, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71  );
#endif

		DEFINE_GUID(  MEDIASUBTYPE_WMVR,  0x52564D57, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71  );
		DEFINE_GUID(  MEDIASUBTYPE_WVC1,  0x31435657, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71  );

		DEFINE_GUID(  MEDIASUBTYPE_WVP2,  0x32505657, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71  );

		DEFINE_GUID(  MEDIASUBTYPE_HDYC,  0x43594448,0x0000,0x0010,0x80,0x00,0x00,0xAA,0x00,0x38,0x9B,0x71  );					//  2010/08/02

		//  2012/02/22
		DEFINE_GUID(  MEDIASUBTYPE_v210,  0x30313276,0x0000,0x0010,0x80,0x00,0x00,0xAA,0x00,0x38,0x9B,0x71  );					//  2010/08/02


		//
		DEFINE_GUID(  WMCMEDIASUBTYPE_WMVA,  0x41564D57, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71  ); 

		DEFINE_GUID(  WMCMEDIASUBTYPE_ADPCM, 0x00000002, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71  ); 

		DEFINE_GUID(  WMCMEDIASUBTYPE_GSM610, 0x00000031, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71  );	//  2010/04/27

		DEFINE_GUID(  WMCMEDIASUBTYPE_MP3, 0x00000055,0x0000,0x0010,0x80,0x00,0x00,0xAA,0x00,0x38,0x9B,0x71  );					//  2010/08/02

		//


#ifdef  __WINCE__
#ifndef  __TEST__
		DEFINE_GUID(	MEDIASUBTYPE_ARGB32, 0x773c9ac0, 0x3274, 0x11d0, 0xb7, 0x24, 0x0, 0xaa, 0x0, 0x6c, 0x1a, 0x1 );			//  2010/04/01
		//  DEFINE_GUID(	MEDIASUBTYPE_IYUV,  0x56555949, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);
		//  DEFINE_GUID(	MEDIASUBTYPE_NV12,  0x3231564E, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);
#endif
#endif

		DEFINE_GUID(IID_IDirectSoundNotify, 0xb0210783, 0x89cd, 0x11d0, 0xaf, 0x8, 0x0, 0xa0, 0xc9, 0x25, 0xcd, 0x16);


 enum { P_MAIN = 0, P_SIMPLE, P_COMPLEX };

 
 
TCHAR  *  getMediaTypeName(  GUID  &  clsid  );
TCHAR  *  getMediaSubtypeName(  GUID  &  clsid  );
int  getMediaSubtypeByName(  LPCTSTR  name,  GUID  *  pclsid  );
TCHAR  *  getFormatTypeName(  GUID  &  clsid  );




#endif  //  }



