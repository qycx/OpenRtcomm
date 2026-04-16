

#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
	#include	<fcntl.h>
	#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#ifndef  __WINCE__
#pragma include_alias( "dxtrans.h", "myqedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__

	//  #include	<Qedit.h>
	#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>


#include	<dvdmedia.h>


#include	"qmcDmo.h"
#include	"qmcVideoCapture.h"
#ifndef  __WINCE__
	#include	"qmcVideoCapture_dx.h"
#endif

#include	"qyDynLib.h"

#include	"mywmcodecconst.h"
#include	"mywmcodeciface.h"
#include	"myfourcc.h"

//#include	"qyAvRecord.h"
//#include	"qyAvRecord_dx.h"

#include	"qySampleGrabberPublic.h"

#include	"qmcDirectX.h"

/*
 QY_DMITEM  CONST_waveFormatTable[]	=
{	
	 {	WAVE_FORMAT_MSAUDIO1,			_T(  "MSAUDIO1"  ),		},
	 {	WAVE_FORMAT_WMAUDIO2,			_T(  "WMAUDIO2"  ),		},
	 {	WAVE_FORMAT_WMAUDIO3,			_T(  "WMAUDIO3"  ),		},
	 {	WAVE_FORMAT_WMAUDIO_LOSSLESS,	_T(  "WMAUDIO_LOSSLESS"  ),		},
	 {	WAVE_FORMAT_WMASPDIF,			_T(  "WMASPDIF"  ),				},
	 {	-1,								NULL,							},
};
*/

//


 BOOL  bFourccWmv(  DWORD  dwTag  )  
{
	BOOL	bWmv  =  FALSE;

	switch  (  dwTag  )  {
			 case  WMCFOURCC_WMV1:
			 case  WMCFOURCC_WMV2:
			 case  WMCFOURCC_WMV3:
			 case  WMCFOURCC_WMVP:
				   bWmv  =  TRUE;
				   break;
			 default:
					 bWmv  =  FALSE;
					 break;
	}

	return  bWmv;
}



HRESULT CreateBuffer(DWORD cbMaxLength, CMediaBuffer **ppBuffer)
{
#include	"unDeclareDebugNew.h"
    CMediaBuffer *pBuffer = new CMediaBuffer( cbMaxLength );
#include	"declareDebugNew.h"

	#ifdef  __DEBUG__	//  2009/12/11
			//  traceLogA(  (char*)  "CreateBuffer: cbMaxLength %d",  cbMaxLength  );
	#endif

    if ( pBuffer == NULL || FAILED( pBuffer->Init() ) ) {
		if  (  pBuffer  )  {			//  2012/03/20
		    delete pBuffer;
		}
		//
        *ppBuffer = NULL;

        return E_OUTOFMEMORY;
    }

    *ppBuffer = pBuffer;
    (*ppBuffer)->AddRef();

    return S_OK;
}





//     clsid  =  &DMOCATEGORY_VIDEO_ENCODER;
//	clsid  =  &DMOCATEGORY_VIDEO_DECODER;
 int  enumDmos(  void  *  pDynLib_dx,  const  GUID  *  clsid_category,  HWND  hComboBox  )
{
    HRESULT			hr;    
    IEnumDMO	*	pEnum = NULL;
	DWORD			dwFlags;
	DYN_LIB_DX	*	pDynLib		=	(  DYN_LIB_DX  *  )pDynLib_dx;
	
	if  (  !pDynLib  ||  !pDynLib->pDMOEnum  )  return  -1;

	//  DWORD dwFlags = m_bCheckKeyed.IsChecked() ? DMO_ENUMF_INCLUDE_KEYED : 0;
	//  dwFlags  =  0;
	dwFlags  =  DMO_ENUMF_INCLUDE_KEYED;	// Included keyed DMOs

    // Read the CLSID pointer from our hard-coded array of
    // documented filter categories
	
    // Enumerate all DMOs of the selected category  
    hr = pDynLib->pDMOEnum(*clsid_category, dwFlags, 0, NULL, 0, NULL, &pEnum);
	if  (  SUCCEEDED(  hr  )  ) {
		int nFilters=0;
		CLSID clsidDMO;
		WCHAR* wszName;

		do  {
			hr = pEnum->Next(1, &clsidDMO, &wszName, NULL);
			if (hr == S_OK)  {  
				// Now wszName holds the friendly name of the DMO, 
				// and clsidDMO holds the CLSID. 

				nFilters  ++  ;


				TCHAR	tBuf[256];

				StringFromGUID2(  clsidDMO,  tBuf,  mycountof(  tBuf  )  );
				traceLogA(  (char*)  "wszName %S, %S",  wszName,  tBuf    );

				if  (  hComboBox  )  {
					//  (  (  CComboBox  *  )pComboBox  )->InsertString(  -1,  wszName  );
					SendMessage(  hComboBox,  CB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )wszName  );
				}

				// Remember to release wszName!
				CoTaskMemFree(wszName);
			}
		} while (hr == S_OK);
		pEnum->Release();
	}

	return  0;
}

 //  clsid = &DMOCATEGORY_VIDEO_ENCODER;
 int  getDmoInfoBySth(  QY_MC  *  pQyMc,  void  *  pDynLib_dx,  const  GUID  *  clsid_category,  LPCTSTR  dmoName,  const  GUID  *  clsid_input,  QY_AUDIO_HEADER  *  pAh_input,  const  GUID  *  clsid_output,  QY_AUDIO_HEADER  *  pAh_output,  GUID  *  pDmoClsid,  void  *  pCompressor  )
{
    HRESULT			hr;    
    IEnumDMO	*	pEnum		=	NULL;
	DWORD			dwFlags;
	DYN_LIB_DX	*	pDynLib		=	(  DYN_LIB_DX  *  )pDynLib_dx;
	BOOL			bFound		=	FALSE;

	
	if  (  !pDynLib  ||  !pDynLib->pDMOEnum  )  return  -1;

	//  DWORD dwFlags = m_bCheckKeyed.IsChecked() ? DMO_ENUMF_INCLUDE_KEYED : 0;
	//  dwFlags  =  0;
	dwFlags  =  DMO_ENUMF_INCLUDE_KEYED;	// Included keyed DMOs

    // Read the CLSID pointer from our hard-coded array of
    // documented filter categories
	
    // Enumerate all DMOs of the selected category  
    hr = pDynLib->pDMOEnum(*clsid_category, dwFlags, 0, NULL, 0, NULL, &pEnum);
	if  (  SUCCEEDED(  hr  )  ) {
		int nFilters=0;
		CLSID clsidDMO;
		WCHAR* wszName;

		do  {
			hr = pEnum->Next(1, &clsidDMO, &wszName, NULL);
			if (hr == S_OK)  {  
				// Now wszName holds the friendly name of the DMO, 
				// and clsidDMO holds the CLSID. 

				nFilters  ++  ;


				TCHAR	tBuf[256];

				StringFromGUID2(  clsidDMO,  tBuf,  mycountof(  tBuf  )  );
				traceLogA(  (char*)  "wszName %S, %S",  wszName,  tBuf    );

				if  (  dmoName  )  {
					if  (  !_tcsicmp(  wszName,  dmoName  )  )  {
						bFound  =  TRUE;
					}
					}
				else  {
					  BOOL  bInputSupported  =  FALSE;
					  BOOL  bOutputSupported  =  FALSE;
					  if  (  !enumDmoIoTypes(  pQyMc,  &clsidDMO,  clsid_input,  pAh_input,  &bInputSupported,  clsid_output,  pAh_output,  &bOutputSupported,  NULL  )  )  {
						  if  (  clsid_input  &&  clsid_output  )  {
							  if  (  bInputSupported  &&  bOutputSupported  )  bFound  =  TRUE;
							  }
						  else  if  (  clsid_input  )  {
								    if  (  bInputSupported  )  bFound  =  TRUE;
								    }
						  else  if  (  clsid_output  )  {
								    if  (  bOutputSupported  )  bFound  =  TRUE;
									}
						  else  if  (  pAh_input  &&  pAh_output  )  {
									if  (  bInputSupported  &&  bOutputSupported  )  bFound  =  TRUE;
									}
						  else  if  (  pAh_input  )  {
								    if  (  bInputSupported  )  bFound  =  TRUE;
						  }
						  else  if  (  pAh_output  )  {
									if  (  bOutputSupported  )  bFound  =  TRUE;
						  }
						  
					  }
				}
				if  (  bFound  ) {
					if  (  pDmoClsid  )  *pDmoClsid  =  clsidDMO;
					if  (  pCompressor  )  {
						if  (  *clsid_category  ==  DMOCATEGORY_VIDEO_ENCODER  )  {
							VIDEO_COMPRESSOR_CFG	*	pCfg  =  (  VIDEO_COMPRESSOR_CFG  *  )pCompressor;
							lstrcpyn(  pCfg->compressorName,  wszName,  mycountof(  pCfg->compressorName  )  );  
						}
						if  (  *clsid_category  ==  DMOCATEGORY_AUDIO_ENCODER  )  {
							AUDIO_COMPRESSOR_CFG	*	pCfg  =  (  AUDIO_COMPRESSOR_CFG  *  )pCompressor;
							lstrcpyn(  pCfg->compressorName,  wszName,  mycountof(  pCfg->compressorName  )  );  
						}
					}
				}
				
				// Remember to release wszName!
				CoTaskMemFree(wszName);
			}
		} while (  hr  ==  S_OK  &&  !bFound  );
		pEnum->Release();
	}

//  errLabel:
	return  bFound  ?  0  :  -1;
}



 int  enumDmoIoTypes(  QY_MC  *  pQyMc,  const  GUID  *  clsid,  const  GUID  *  clsid_input,  QY_AUDIO_HEADER  *  pAh_input,  BOOL  *  pbInputSupported,  const  GUID  *  clsid_output,  QY_AUDIO_HEADER  *  pAh_output,  BOOL  *  pbOutputSupported,  HWND  hComboBox  )
{	
	int					iErr								=	-1;
	//QY_MC			*	pQyMc								=	QY_GET_GBUF(  );
	DYN_LIB_DX		*	pDynLib								=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	IMediaObject	*	m_pObject							=	NULL;
	BOOL				bInputSupported						=	FALSE;
	BOOL				bOutputSupported					=	FALSE;

	BOOL				bZero_pAh_output_nAvgBytesPerSec	=	FALSE;
	BOOL				bWfxMatched							=	FALSE;

	CQyString			descStr;
#ifdef  __DEBUG__
		BOOL			bPrint								=	0;	//  TRUE;
#endif

	if  (  pAh_output  )  {
		if  (  !pAh_output->wfx.nAvgBytesPerSec  )  bZero_pAh_output_nAvgBytesPerSec  =  TRUE;
	}


    // create DMO
    HRESULT hr = CoCreateInstance( *clsid,
                         NULL,
                         CLSCTX_INPROC,
                         IID_IMediaObject,
                         (void **) &m_pObject);
    if  (  FAILED(  hr  )  )  {
		traceLogA(  (char*) ("Can't create this DMO.") );
		goto  errLabel;
    }

	DWORD  cInput  =  0,  cOutput  =  0;
	hr  =  m_pObject->GetStreamCount(  &cInput,  &cOutput  );
	if  (  FAILED(  hr  )  )  goto  errLabel;

	DMO_MEDIA_TYPE		mt;
	DWORD				dwType  =  0;
	TCHAR				tBuf[256];
	TCHAR				tBuf1[256]  =  _T(  ""  );
#ifdef  __DEBUG__
#endif
	int					i;
	char				fourccStr[4  +  1];

	for  (  i  =  0;  i  <  (  int  )cInput;  i  ++  )  {
		 while  (  hr  =  m_pObject->GetInputType(  i,  dwType,  &mt  ),  SUCCEEDED(  hr  )  )  {

			    
				iFourcc2Str(  mt.subtype.Data1,  fourccStr,  mycountof(  fourccStr  )  );
				
				#ifdef  __DEBUG__

						StringFromGUID2(  mt.majortype,  tBuf1,  mycountof(  tBuf1  )  );
				        StringFromGUID2(  mt.subtype,  tBuf,  mycountof(  tBuf  )  );
						if  (  bPrint  )  traceLog((TCHAR*)  _T(  "inputType ( %d,%d ): %s, %s, fourcc %s"  ),  i,  dwType,  tBuf,  getMediaSubtypeName(  mt.subtype  ), CQyString(  fourccStr  )  );
				#endif

				if  (  i  ==  0  )  {
					if  (  !bInputSupported  )  {
						if  (  clsid_input  )  {
							if  (  mt.subtype  ==  *clsid_input  )  bInputSupported  =  TRUE;
						}
					}
				
					//  if  (  pComboBox  )  {
					//  	(  (  CComboBox  *  )pComboBox  )->InsertString(  -1,  CString(  fourccStr  )  +  " : "  +  tBuf  );
					//  }
				}

				pDynLib->pMoFreeMediaType(  &mt  );
				dwType  ++  ;
		 }
	}

	for  (  i  =  0;  i  <  (  int  )cOutput;  i  ++  )  {
		dwType  =  0;
		while  (  hr  =  m_pObject->GetOutputType(  i,  dwType,  &mt  ),  SUCCEEDED(  hr  )  )  {

				StringFromGUID2(  mt.subtype,  tBuf,  mycountof(  tBuf  )  );

				descStr  =  _T(  ""  );

				if  (  mt.formattype  ==  FORMAT_WaveFormatEx  )  {

					if  (  mt.pbFormat  &&  mt.cbFormat  >=  sizeof(  WAVEFORMATEX  )  )  {
						WAVEFORMATEX	*	pWfx  =  (  WAVEFORMATEX  *  )mt.pbFormat;

						_sntprintf(  tBuf1,  mycountof(  tBuf1  ),  _T(  "tag 0x%x, nChannels %d, nSamplesPerSec %d, wBits %d, nAvg %d, cbSize %d"  ),  (  int  )pWfx->wFormatTag,  (  int  )pWfx->nChannels,  pWfx->nSamplesPerSec,  (  int  )pWfx->wBitsPerSample,  pWfx->nAvgBytesPerSec,  (  int  )pWfx->cbSize  );

						descStr  =  descStr  +  getWaveFormatExStr(  0,  pWfx,  tBuf,  mycountof(  tBuf  )  );

					}

					//  traceLogA(  (char*)  "outputType ( %d,%d ): %S, %S, tag 0x%x. ",  i,  dwType,  tBuf,  getMediaSubtypeName(  mt.subtype  ),  mt.subtype.Data1  );
					//  traceLogA(  (char*)  "tBuf1 %S",  tBuf1  );
			  
					}
				else  {
					  fourccStr[0]  =  0;				

					  FOURCCMap	map(  mt.subtype.Data1  );
					  if  (  map  ==  mt.subtype  )  {
						  iFourcc2Str(  mt.subtype.Data1,  fourccStr,  mycountof(  fourccStr  )  );
					  }

					  descStr  =  CQyString(  fourccStr  )  +  CQyString(  _T(  " : "  )  );	//    +  _T(  ""  );	//  tBuf;

					  #ifdef  __DEBUG__
							  if  (  bPrint  )  traceLog((TCHAR*)  _T(  "outputType ( %d,%d ): %s, %s, format %s, fourcc %S."  ),  i,  dwType,  tBuf,  getMediaSubtypeName(  mt.subtype  ),  getFormatTypeName(  mt.formattype  ),  fourccStr  );
					  #endif
				}
				
				if  (  i  ==  0  )  {
					if  (  !bOutputSupported  )  {
						if  (  clsid_output  )  {
							if  (  mt.subtype  ==  *clsid_output  )  bOutputSupported  =  TRUE;
						}			
						if  (  pAh_output  )  {
							if  (  mt.formattype  ==  FORMAT_WaveFormatEx  )  {
								if  (  mt.pbFormat  &&  mt.cbFormat  >=  sizeof(  WAVEFORMATEX  )  )  {
									WAVEFORMATEX  *  pWfx  =  (  WAVEFORMATEX  *  )mt.pbFormat;
									if  (  pWfx->wFormatTag  ==  pAh_output->wfx.wFormatTag
										&&  pWfx->nChannels  ==  pAh_output->wfx.nChannels
											&&  pWfx->nSamplesPerSec  ==  pAh_output->wfx.nSamplesPerSec
												&&  pWfx->wBitsPerSample  ==  pAh_output->wfx.wBitsPerSample  )
									{
										if  (  pWfx->cbSize  >  sizeof(  pAh_output->bExtraData  )  )  {
											traceLogA(  (char*)  "enumDmoIoTypes failed, outputWfx.cbSize %d >  sizeof(  bExtraData  ) %d",  pWfx->cbSize,  sizeof(  pAh_output->bExtraData  )  );
											goto  errLabel;
										}

										if  (  !bZero_pAh_output_nAvgBytesPerSec
											&&  pAh_output->wfx.nAvgBytesPerSec  ==  pWfx->nAvgBytesPerSec  )
										{
											memcpy(  &pAh_output->wfx,  pWfx,  sizeof(  WAVEFORMATEX  )  +  pWfx->cbSize  );  											
											bOutputSupported  =  TRUE;
										}
										if  (  bZero_pAh_output_nAvgBytesPerSec  )  {
											if  (  !bWfxMatched  )  {
												memcpy(  &pAh_output->wfx,  pWfx,  sizeof(  WAVEFORMATEX  )  +  pWfx->cbSize  );  											
												bWfxMatched  =  TRUE;
												}
											else  if  (  pAh_output->wfx.nAvgBytesPerSec  >  pWfx->nAvgBytesPerSec  )  {
												      memcpy(  &pAh_output->wfx,  pWfx,  sizeof(  WAVEFORMATEX  )  +  pWfx->cbSize  );  														  
											}
										}
									}							
								}						
							}					
						}
					}
					if  (  hComboBox  )  {						
						//  (  (  CComboBox  *  )pComboBox  )->InsertString(  -1,  descStr  );						  
						SendMessage(  hComboBox,  CB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )descStr.GetBuffer(  0  )  );
					}
				}

				pDynLib->pMoFreeMediaType(  &mt  );
				dwType  ++  ;
		}
	}

	//
	if  (  bZero_pAh_output_nAvgBytesPerSec  &&  bWfxMatched  )  bOutputSupported  =  TRUE;

	iErr  =  0;
errLabel:

	MACRO_safeRelease(  m_pObject  );

	if  (  !iErr  )  {
		if  (  pbInputSupported  )  *pbInputSupported  =  bInputSupported;
		if  (  pbOutputSupported  )  *pbOutputSupported  =  bOutputSupported;
	}


	return  iErr;
}






////////////////////



 

 

 

 void  tmp_setEncodingDefaults_video(  float fFps,  DWORD  fourcc,  VIDEO_ENC_PARAMS  *  pParams  )
{
	if  (  !fourcc  ||  !pParams  )  return;
	
	DWORD ComplexityLive = 0;
	DWORD ComplexityOffline = 0;
	DWORD ComplexityMax = 0;
	HRESULT hr = S_OK;

	if  (  fFps  <  11  )  {
		pParams->fFrameRate = 5;		//  29.97F;
		//  pParams->fFrameRate = 10;	//  29.97F;
		}
	else  {
		  pParams->fFrameRate  =  fFps;
	}
	//
	if  (  pParams->fFrameRate  <  0.001  )  pParams->fFrameRate  =  5;
    
    // Other codecs not supported in this sample
    pParams->dwTag = fourcc;	//  WMCFOURCC_WMV3;
	pParams->bWmv  =  bFourccWmv(  pParams->dwTag  );

    pParams->fIsVBR = FALSE;
    pParams->nBitrate = 0;
    pParams->nBufferDelay = 1000;	//  5000;
    pParams->nKeyDistInMs = 800;	//  8000;
    pParams->nProfile = P_MAIN;
    pParams->nQuality = 75;
    pParams->nVBRQuality = 98;


	QY_MC* pQyMc = nullptr;// QY_GET_GBUF();
	return;
	DYN_LIB_DX	*	pDynLib	=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	GUID			clsid_mOutSubType;
	GUID			clsid;

	clsid_mOutSubType  =  FOURCCMap(  fourcc  );
	if  (  !getDmoInfoBySth(  pQyMc,  pDynLib,  &DMOCATEGORY_VIDEO_ENCODER,  NULL,  &MEDIASUBTYPE_RGB24,  NULL,  &clsid_mOutSubType,  NULL,  &clsid,  NULL  )  )  {

		//  Get the complexity levels for the codec.
		if  (  !getComplexitySettings(  &clsid,  fourcc,  &ComplexityLive,  &ComplexityOffline,  &ComplexityMax  )  )  {
		}

	}

	//  2009/03/31
	pParams->nComplexity  =  ComplexityLive;

	return;
}


 void  tmp_setEncodingDefaults_screen(  float  fFps,  DWORD  fourcc,  VIDEO_ENC_PARAMS  *  pParams  )
{
	if  (  !fourcc  ||  !pParams  )  return;
	
	DWORD ComplexityLive = 0;
	DWORD ComplexityOffline = 0;
	DWORD ComplexityMax = 0;
	HRESULT hr = S_OK;

	if  (  fFps  <  11  )  {
		pParams->fFrameRate =   5;	//  29.97F;
		}
	else  {
		  pParams->fFrameRate  =  fFps;
	}
	if  (  pParams->fFrameRate  <  0.001  )  pParams->fFrameRate  =  5;
    
    // Other codecs not supported in this sample
    pParams->dwTag = fourcc;	//  WMCFOURCC_WMV3;
	pParams->bWmv  =  bFourccWmv(  pParams->dwTag  );

    pParams->fIsVBR = FALSE;
    pParams->nBitrate = 0;
    pParams->nBufferDelay = 1500;	//  5000;
    pParams->nKeyDistInMs =   500;
    pParams->nProfile = P_MAIN;
    pParams->nQuality = 75;
    pParams->nVBRQuality = 98;


	QY_MC* pQyMc = nullptr;// QY_GET_GBUF();
	return;
	DYN_LIB_DX	*	pDynLib	=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	GUID			clsid_mOutSubType;
	GUID			clsid;

	clsid_mOutSubType  =  FOURCCMap(  fourcc  );
	if  (  !getDmoInfoBySth(  pQyMc,  pDynLib,  &DMOCATEGORY_VIDEO_ENCODER,  NULL,  &MEDIASUBTYPE_RGB24,  NULL,  &clsid_mOutSubType,  NULL,  &clsid,  NULL  )  )  {

		//  Get the complexity levels for the codec.
		if  (  !getComplexitySettings(  &clsid,  fourcc,  &ComplexityLive,  &ComplexityOffline,  &ComplexityMax  )  )  {
		}

	}


	//  2009/03/31
	pParams->nComplexity  =  ComplexityLive;

	return;
}

  void  tmp_setEncodingDefaults_mediaFile(  float  fFps,  DWORD  fourcc,  VIDEO_ENC_PARAMS  *  pParams  )
{
	if  (  !fourcc  ||  !pParams  )  return;
	
	DWORD ComplexityLive = 0;
	DWORD ComplexityOffline = 0;
	DWORD ComplexityMax = 0;
	HRESULT hr = S_OK;

    //  pParams->fFrameRate = 29.97F;
	pParams->fFrameRate  =  fFps;
	if  (  pParams->fFrameRate  <  0.001  )  pParams->fFrameRate  =  29.97;
    
    // Other codecs not supported in this sample
    pParams->dwTag = fourcc;	//  WMCFOURCC_WMV3;
	pParams->bWmv  =  bFourccWmv(  pParams->dwTag  );

    pParams->fIsVBR = FALSE;
    pParams->nBitrate = 0;
    pParams->nBufferDelay = 1000;	//  5000;
    pParams->nKeyDistInMs = 800;	//  8000;
    pParams->nProfile = P_MAIN;
    pParams->nQuality = 75;
    pParams->nVBRQuality = 98;


	QY_MC* pQyMc = nullptr;// QY_GET_GBUF();
	return;
	DYN_LIB_DX	*	pDynLib	=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	GUID			clsid_mOutSubType;
	GUID			clsid;

	clsid_mOutSubType  =  FOURCCMap(  fourcc  );
	if  (  !getDmoInfoBySth(  pQyMc,  pDynLib,  &DMOCATEGORY_VIDEO_ENCODER,  NULL,  &MEDIASUBTYPE_RGB24,  NULL,  &clsid_mOutSubType,  NULL,  &clsid,  NULL  )  )  {

		//  Get the complexity levels for the codec.
		if  (  !getComplexitySettings(  &clsid,  fourcc,  &ComplexityLive,  &ComplexityOffline,  &ComplexityMax  )  )  {
		}

	}

	//  2009/03/31
	pParams->nComplexity  =  ComplexityLive;

	return;
}



 void  setEncodingDefaults_video(  unsigned  int  uiCapType,  float  fFps,  DWORD  fourcc,  VIDEO_ENC_PARAMS  *  pParams  )
{
	if  (  !pParams  )  return;

	memset(  pParams,  0,  sizeof(  pParams[0]  )  );

	switch  (  uiCapType  )  {
			case  CONST_capType_screen:
				  tmp_setEncodingDefaults_screen(  fFps,  fourcc,  pParams  );
				  break;
			case  CONST_capType_mediaFile:
				  tmp_setEncodingDefaults_mediaFile(  fFps,  fourcc,  pParams  );
				  break;
			default:
				    tmp_setEncodingDefaults_video(  fFps,  fourcc,  pParams  );
					break;
	}

	return;

}


 HRESULT DefaultVideoBitrate( AM_MEDIA_TYPE *pmt, double dFramesPerSec, int *pBitrate )
{
    if( pmt == NULL || pBitrate == NULL )
        return E_INVALIDARG;
    
    if( pmt->pbFormat == NULL || pmt->cbFormat <= 0 )
        return E_INVALIDARG;
    
    if( pmt->formattype == FORMAT_VideoInfo ){
        VIDEOINFOHEADER *pvih = (VIDEOINFOHEADER*)pmt->pbFormat;
        
        // 0.4 bits per pixel will generate good quality content at a reasonable bitrate
        *pBitrate = ( pvih->bmiHeader.biWidth * pvih->bmiHeader.biHeight * 2 ) / 5;
        if( dFramesPerSec == 0 ) { // use the input rate
            if( pvih->AvgTimePerFrame > 0 )
                dFramesPerSec = 10000000.0 / pvih->AvgTimePerFrame;
            else
                dFramesPerSec = 29.97;   // 30 frames per sec
        }
    } 
	
	else if( pmt->formattype == FORMAT_VideoInfo2 ){
        VIDEOINFOHEADER2 *pvih = (VIDEOINFOHEADER2*)pmt->pbFormat;
        
        // 0.4 bits per pixel will generate good quality content at a reasonable bitrate
        *pBitrate = ( pvih->bmiHeader.biWidth * pvih->bmiHeader.biHeight * 2 ) / 5;
        
        if( dFramesPerSec == 0 ) { // use the input rate
            if( pvih->AvgTimePerFrame > 0 )
                dFramesPerSec = 10000000.0 / pvih->AvgTimePerFrame;
            else
                dFramesPerSec = 29.97;   // 30 frames per sec
        }
    }
	
	else
        return -1;
    *pBitrate = (int)( *pBitrate * dFramesPerSec );
    
    return S_OK;
}

 HRESULT SetVideoParams_enc( IMediaObject *pDMO, VIDEO_ENC_PARAMS *pParams )
 {
    HRESULT      hr = S_OK;
    VARIANT      varg;
    BSTR         bstrIn=mynull;
    IPropertyBag *pPropertyBag = NULL;
    
    if( pDMO == NULL || pParams == NULL )
        return E_INVALIDARG;
    
    do {
        // Get the IPropertyBag IF and set the appropriate params
        hr = pDMO->QueryInterface(IID_IPropertyBag, (void**)&pPropertyBag);
        if( FAILED( hr ) ){
            break;
        }
        
#ifndef  __WINCE__

        //set the encoder in VBR mode if required
        if( pParams->fIsVBR == TRUE ){
            ::VariantInit(&varg);
            varg.vt      = VT_BOOL;
            varg.boolVal = TRUE;
            
            hr = pPropertyBag->Write( g_wszWMVCVBREnabled, &varg );
            if( FAILED( hr ) ){
                hr = -1;
                break;
            }
            
            ::VariantInit(&varg);
            varg.vt = VT_I4;
            varg.lVal = pParams->nVBRQuality;
            hr = pPropertyBag->Write( g_wszWMVCVBRQuality, &varg );
            if( FAILED( hr ) ){
                hr = -1;
                break;
            }
        }
        
        // set the bitrate if not VBR
        if( pParams->fIsVBR == FALSE ){
            ::VariantInit(&varg);
            varg.vt = VT_I4;
            varg.lVal = pParams->nBitrate;
            hr = pPropertyBag->Write( g_wszWMVCAvgBitrate, &varg );
            if( FAILED( hr ) ){
                hr = -1;
                break;
            }
        }
        
        // set the buffer window
        ::VariantInit(&varg);
        varg.vt = VT_I4;
        varg.lVal = pParams->nBufferDelay;
        hr = pPropertyBag->Write( g_wszWMVCVideoWindow, &varg );
        if( FAILED( hr ) ){
            hr = -1;
            break;
        }
        

        // set the profile for WMV# only
        if( pParams->dwTag == WMCFOURCC_WMV3 ){
            switch( pParams->nProfile ){
            case P_MAIN:
                bstrIn = ::SysAllocString(L"MP");
                break;
            case P_SIMPLE:
                bstrIn = ::SysAllocString(L"SP");
                break;
            case P_COMPLEX:
                bstrIn = ::SysAllocString(L"CP");
                break;
            default:
                hr = -1;
                break;
            }
            ::VariantInit(&varg);
            varg.vt      = VT_BSTR;
            varg.bstrVal = bstrIn;
            hr = pPropertyBag->Write( g_wszWMVCDecoderComplexityRequested, &varg );
            ::SysFreeString( bstrIn );
            if( FAILED( hr ) ){
                hr = -1;
                break;
            }
        }
        
#endif

		//  if  (  pParams->bWmv  )  
		{

        // set the ecoder complexity
        ::VariantInit(&varg);
        varg.vt = VT_I4;
        varg.lVal = pParams->nComplexity;
        hr = pPropertyBag->Write(g_wszWMVCComplexityEx, &varg);
        if( FAILED( hr ) ){
            hr = -1;
            break;
        }
        
        // set the max distance between the key frames
        ::VariantInit(&varg);
        varg.vt = VT_I4;
        varg.lVal = pParams->nKeyDistInMs;
        hr = pPropertyBag->Write( g_wszWMVCKeyframeDistance, &varg );
        if( FAILED( hr ) ){
            hr = -1;
            break;
        }
        
#ifndef  __WINCE__
        // set the crispness params for WMV# only
        if( pParams->dwTag == WMCFOURCC_WMV3 ){
            ::VariantInit(&varg);
            varg.vt = VT_I4;
            varg.lVal = pParams->nQuality;
            hr = pPropertyBag->Write( g_wszWMVCCrisp, &varg );
            if( FAILED( hr ) ){
                hr = -1;
                break;
            }
        }
#endif

		}
        
    } while( FALSE );

    SAFERELEASE( pPropertyBag );
    return hr;
}

HRESULT MakeVideoOutputType(IMediaObject   *pDMO,    
                            AM_MEDIA_TYPE  *pmtIn,   
                            VIDEO_ENC_PARAMS *pParams, 
                            AM_MEDIA_TYPE  *pmt      ) 
{
    
    HRESULT             hr                   = -1;
    VIDEOINFOHEADER2    *pvih2               = NULL;
    VIDEOINFOHEADER     vih;
    IWMCodecPrivateData *pWMCodecPrivateData = NULL;
    DWORD               cbPrivateData        = 0;
    BYTE                *pbPrivateData       = NULL;
    BYTE                *pNewFormat          = NULL;
    
    if( pDMO == NULL || pmtIn == NULL || pParams == NULL || pmt == NULL )
        return E_INVALIDARG;
    
    if( pmtIn->pbFormat == NULL || pmtIn->cbFormat <= 0 )
        return E_INVALIDARG;
    
    // make up a partial media type
#if !defined(  __WINCE__  )  ||  defined(  __TEST__  )
    pmt->majortype            = MEDIATYPE_Video;
#else
	pmt->majortype			  = MEDIATYPE_VideoBuffered;
#endif
    pmt->formattype           = FORMAT_VideoInfo;
    pmt->bFixedSizeSamples    = FALSE;
    pmt->bTemporalCompression = TRUE;
    
    if( pmtIn->formattype == FORMAT_VideoInfo ){
        vih = *(VIDEOINFOHEADER*)pmtIn->pbFormat; 
    } else if( pmtIn->formattype == FORMAT_VideoInfo2 ){
        pvih2 = (VIDEOINFOHEADER2*)pmtIn->pbFormat;
        vih.rcSource        = pvih2->rcSource;
        vih.rcTarget        = pvih2->rcTarget;
        vih.AvgTimePerFrame = pvih2->AvgTimePerFrame;
        vih.bmiHeader       = pvih2->bmiHeader;
    } else
        return -1;
    
    vih.dwBitRate            = (DWORD)pParams->nBitrate;
    vih.dwBitErrorRate       = 0;
    vih.bmiHeader.biPlanes   = 1;
    vih.bmiHeader.biBitCount = 24;
    
    switch  (  pParams->dwTag  )  {
			case  WMCFOURCC_WMV3:
				  pmt->subtype = WMCMEDIASUBTYPE_WMV3;
				  vih.bmiHeader.biCompression = WMCFOURCC_WMV3;
				  break;
			case  WMCFOURCC_MSS2:
				  pmt->subtype  =  WMCMEDIASUBTYPE_MSS2;
				  vih.bmiHeader.biCompression  =  WMCFOURCC_MSS2;	//  pmt->subtype.Data1;
				  break;
			default:
				    pmt->subtype  =  FOURCCMap(  pParams->dwTag  );
					vih.bmiHeader.biCompression  =  pParams->dwTag;
				    break;
    }
    
    //use the fake format above to get the private data
    pmt->pbFormat = (BYTE*)&vih;
    pmt->cbFormat = sizeof( vih );
    pmt->pUnk = NULL;
    
    hr = pDMO->QueryInterface(IID_IWMCodecPrivateData, (void**)&pWMCodecPrivateData);    
	if  (  !FAILED(  hr  )  )  {
      
		hr = pWMCodecPrivateData->SetPartialOutputType( (  DMO_MEDIA_TYPE  *  )pmt );
		if  (  FAILED(  hr  )  )  goto  errLabel;
		
		hr = pWMCodecPrivateData->GetPrivateData( NULL, &cbPrivateData );
		if  (  FAILED(  hr  )  )  goto  errLabel;
	}

    if  (  cbPrivateData  !=  0  )  {
#include	"unDeclareDebugNew.h"
        pbPrivateData = new BYTE[ cbPrivateData ];
#include	"declareDebugNew.h"
        if  (  pbPrivateData  ==  NULL  )  goto  errLabel;
		
        // get the private data
        hr = pWMCodecPrivateData->GetPrivateData( pbPrivateData, &cbPrivateData );
        if( FAILED( hr ) ) goto  errLabel;
    }
	SAFERELEASE( pWMCodecPrivateData );
    
    //modify the media type accordingly
    pNewFormat = (BYTE*)CoTaskMemAlloc( sizeof( VIDEOINFOHEADER) + cbPrivateData );
    if( pNewFormat == NULL )  goto  errLabel;
	
    memcpy( pNewFormat, pmt->pbFormat, sizeof( VIDEOINFOHEADER));
    if( pbPrivateData != NULL )
        memcpy( pNewFormat + sizeof( VIDEOINFOHEADER), pbPrivateData, cbPrivateData);
    SAFEDELETE( pbPrivateData );
    
    pmt->pbFormat = pNewFormat;
    pmt->cbFormat = sizeof( VIDEOINFOHEADER) + cbPrivateData;
    ((VIDEOINFOHEADER*)pmt->pbFormat)->bmiHeader.biSize += cbPrivateData;
    
	hr  =  S_OK;

errLabel:

	SAFEDELETE(  pbPrivateData  );
	SAFERELEASE(  pWMCodecPrivateData  );
	if  (  hr  !=  S_OK  )  {
		if  (  pNewFormat  )  CoTaskMemFree(  pNewFormat  );
		memset(  pmt,  0,  sizeof(  pmt[0]  )  );
	}


    return  hr;
}


 int setVideoTypes_enc( IMediaObject   *pDMO,    \
                      AM_MEDIA_TYPE  *pmtIn,   \
                      VIDEO_ENC_PARAMS *pParams, \
                      AM_MEDIA_TYPE  *pmtOut,  \
                      DWORD *pcbIn,            \
                      DWORD *pcbOut )
{
	int		iErr	=	-1;
    HRESULT hr;
    DWORD   dwDummy;
    
    //Now we can make the output type...
    hr = MakeVideoOutputType( pDMO, pmtIn, pParams, pmtOut );
    if  ( FAILED( hr ) )  {
		traceLogA(  (char*)  "Failed MakeVideoOutputType"  );
		goto  errLabel;
    }
    
    //... and set it on the DMO just to check whether it is accepted or not
    hr = pDMO->SetOutputType(0, (  DMO_MEDIA_TYPE  *  )pmtOut, 0);
    if  (  FAILED( hr ) )  {
		traceLogA(  (char*)  "Failed SetOutputType"  );
		goto  errLabel;
    }
    
    //     
    hr = pDMO->GetInputSizeInfo( 0, pcbIn, &dwDummy, &dwDummy);
    if  ( FAILED(hr) )  {
		traceLogA(  (char*)  "Failed GetInputSizeInfo"  );
		goto  errLabel;
    }
    
    hr = pDMO->GetOutputSizeInfo( 0, pcbOut, &dwDummy);
    if  ( FAILED( hr ) )  {
		traceLogA(  (char*)  "Failed GetOutputSizeInfo"  );
		goto  errLabel;
    }
    
	iErr  =  0;
errLabel:
    return  iErr;
} 


  int  initializeVideoEncoder(  AM_MEDIA_TYPE *pmtInput, 
                               VIDEO_ENC_PARAMS *pParams, 
                               IMediaObject   *pDMO,  
                               AM_MEDIA_TYPE  *pmtOutput  )
 {
	int			  iErr				=	-1;
    HRESULT       hr;
    DWORD         cbInputBuffer		=	0;
    DWORD         cbOutputBuffer	=	0;
    
    if( pmtInput == NULL || pParams == NULL || pDMO == NULL )  return  -1;
	    
        //check to see if the video bitrate has been set; if not calculate the default
    if  (  pParams->nBitrate <= 0  )  {
        hr  =  DefaultVideoBitrate( pmtInput, pParams->fFrameRate, &pParams->nBitrate );
        if  (  FAILED(  hr  )  )  goto  errLabel;
    }
    
    
#if 1	//  ndef  __WINCE__
    hr = SetVideoParams_enc( pDMO, pParams );
	if  (  FAILED(  hr  )  )  goto  errLabel;
#endif
        
	// cbInputBuffer and cbOutputBuffer are actually not used here.
	if  (  setVideoTypes_enc( pDMO, pmtInput, pParams, pmtOutput, &cbInputBuffer, &cbOutputBuffer )  )  goto  errLabel;
    
	if  (  pmtInput->formattype  !=  FORMAT_VideoInfo  )  goto  errLabel;
	if  (  pmtInput->cbFormat  <  sizeof(  VIDEOINFOHEADER  )  )  goto  errLabel;
	if  (  !pmtInput->pbFormat  )  goto  errLabel;
	VIDEOINFOHEADER  *  pVih;
	pVih  =  (  VIDEOINFOHEADER  *  )pmtInput->pbFormat;
	if  (  pVih->bmiHeader.biSizeImage  <  cbInputBuffer  )  goto  errLabel;

	if  (  pmtOutput->formattype  !=  FORMAT_VideoInfo  )  goto  errLabel;
	if  (  pmtOutput->cbFormat  <  sizeof(  VIDEOINFOHEADER  )  )  goto  errLabel;
	if  (  !pmtOutput->pbFormat  )  goto  errLabel;
	pVih  =  (  VIDEOINFOHEADER  *  )pmtOutput->pbFormat;
	
	if  (  pVih->bmiHeader.biSizeImage  <  cbOutputBuffer  )  pVih->bmiHeader.biSizeImage  =  cbOutputBuffer;


	iErr  =  0;
errLabel:
    return  iErr;     
}

 
 int  configureDMO_enc(   VIDEO_ENC_PARAMS  *  pEncParams,  IMediaObject* pDMO, AM_MEDIA_TYPE* pmtIn, AM_MEDIA_TYPE* pmtOut)
{
	int		iErr	=	-1;
    HRESULT hr		=  E_FAIL;

    if  (  FORMAT_VideoInfo  ==  pmtIn->formattype  ||  FORMAT_VideoInfo2  ==  pmtIn->formattype  ) {
        if  (  initializeVideoEncoder( pmtIn, pEncParams, pDMO, pmtOut )  )  goto  errLabel;
		}
	else  
		goto  errLabel;
		  
	iErr  =  0;
errLabel:    
    return  iErr;
}


 struct VideoDecParams {
    int    nWidth;
    int    nHeight;
    double dFrameRate;

    DWORD  dwTag;
    DWORD  dwBitsPerPixel;
    
    VideoDecParams(){
        memset(  this, 0, sizeof( VideoDecParams ) );
        dwBitsPerPixel = 24;
    }
};

 
 #ifdef  __DEBUG__

  int  testDmoCompressVideoInit(  )
{
	   return  0;

	 //  enumDmo(  );
	   QY_MC* pQyMc = nullptr;// QY_GET_GBUF();
	 DYN_LIB_DX	*	pDynLib	=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	 GUID			clsid;
	 GUID			clsid_mOutSubType;
	 DWORD			dwTag;
	 BOOL			bWmv	=	FALSE;
	 int			iWidth	=	1440;
	 int			iHeight  =  900;
	 IMediaObject        *m_pObject  =  NULL;
	 VIDEO_ENC_PARAMS  encParams;


	 //  CLSID_CWMVEncMediaObject2;
	 /*
	 clsid  =  CLSID_MSScreen9_Encoder_DMO;
	 clsid_mOutSubType  =  WMCMEDIASUBTYPE_MSS2;
	 dwTag  =  WMCFOURCC_MSS2;
	 bWmv  =  FALSE;
	 */
	 clsid  =  CLSID_WMVideo9_Encoder_DMO;
	 clsid_mOutSubType  =  WMCMEDIASUBTYPE_WMV3;
	 dwTag  =  WMCFOURCC_WMV3;
	 bWmv  =  TRUE;


	 memset(  &encParams,  0,  sizeof(  encParams  )  );
	 setEncodingDefaults_video(  0,  0,  dwTag,  &encParams  );



    // create DMO
    HRESULT hr = CoCreateInstance( clsid,
                         NULL,
                         CLSCTX_INPROC,
                         IID_IMediaObject,
                         (void **) &m_pObject);
    if ( FAILED( hr ) ){
		traceLogA(  (char*) ("Can't create this DMO.") );
        return hr;
    }

	DWORD  cInput  =  0,  cOutput  =  0;
	hr  =  m_pObject->GetStreamCount(  &cInput,  &cOutput  );

	DMO_MEDIA_TYPE		mt;
	DWORD				dwType  =  0;
	TCHAR				tBuf[256];
	int					i;

	while  (  hr  =  m_pObject->GetInputType(  0,  dwType,  &mt  ),  SUCCEEDED(  hr  )  )  {

			StringFromGUID2(  mt.subtype,  tBuf,  mycountof(  tBuf  )  );
			traceLogA(  (char*)  "inputType %d:%S, %S",  dwType,  tBuf,  getMediaSubtypeName(  mt.subtype  )  );
						

			pDynLib->pMoFreeMediaType(  &mt  );
			dwType  ++  ;
	}

	for  (  i  =  0;  i  <  (  int  )cOutput;  i  ++  )  {
		dwType  =  0;
		while  (  hr  =  m_pObject->GetOutputType(  i,  dwType,  &mt  ),  SUCCEEDED(  hr  )  )  {

				StringFromGUID2(  mt.subtype,  tBuf,  mycountof(  tBuf  )  );
				traceLogA(  (char*)  "outputType ( %d,%d ): %S, %S, %S, %S",  i,  dwType,  getMediaTypeName(  mt.majortype  ),  tBuf,  getMediaSubtypeName(  mt.subtype  ),  getFormatTypeName(  mt.formattype  )  );
						
				pDynLib->pMoFreeMediaType(  &mt  );

				dwType  ++  ;
		}
	}

	DMO_MEDIA_TYPE      mIn;
	memset(  &mIn,  0, sizeof(  mIn  )  );
	hr  =  pDynLib->pMoInitMediaType(  &mIn,  sizeof(  VIDEOINFOHEADER  )  );


	DMO_MEDIA_TYPE		mOut;
	/*
	memset(  &mOut,  0,  sizeof(  mOut  )  );
	hr  =  MoInitMediaType(  &mOut,  sizeof(  VIDEOINFOHEADER  )  );

	
    m_mt.majortype  = MEDIATYPE_Audio;
    m_mt.subtype    = MEDIASUBTYPE_PCM;
    m_mt.formattype = FORMAT_WaveFormatEx;
    m_mt.cbFormat   = sizeof(WAVEFORMATEX);
    //  m_mt.pbFormat   = (BYTE*) (m_pwfx);
    m_mt.pUnk = NULL;       // CopyMediaType will crash if we don't intialize this
	*/

	mIn.majortype  =  MEDIATYPE_Video;
	mIn.subtype  =  MEDIASUBTYPE_RGB24;
	mIn.formattype  =  FORMAT_VideoInfo;
	mIn.lSampleSize  =  1;
	VIDEOINFOHEADER  *  pvihi  =  (  VIDEOINFOHEADER  *  )mIn.pbFormat;
	memset(  pvihi,  0,  sizeof(  VIDEOINFOHEADER  )  );
	pvihi->AvgTimePerFrame	=	DEFAULT_AvgTimePerFrame;	//  1000000;
	makeBmpInfoHeader_rgb(  24,  iWidth,  iHeight,  &pvihi->bmiHeader  );

	//  int  len  =  sizeof(  VIDEOINFOHEADER  );

	/*
	ULONG	biCompression;
	mOut.majortype  =  MEDIATYPE_Video;
	mOut.subtype  =  clsid_mOutSubType;
	mOut.formattype  =  GUID_NULL;
	
	biCompression  =  mOut.subtype.Data1;
	VIDEOINFOHEADER  *  pVihO  =  (  VIDEOINFOHEADER  *  )mOut.pbFormat;
	memset(  pVihO,  0,  sizeof(  VIDEOINFOHEADER  )  );
	pVihO->bmiHeader.biSize  =  sizeof(  BITMAPINFOHEADER  );
	pVihO->bmiHeader.biWidth  =  iWidth;
	pVihO->bmiHeader.biHeight  =  iHeight;
	pVihO->bmiHeader.biPlanes  =  1;
	pVihO->bmiHeader.biBitCount  =  16;
	pVihO->bmiHeader.biCompression  =  biCompression;

	iFourcc2Str(  biCompression,  NULL,  0  );
	*/

	hr  =  m_pObject->SetInputType(  0,  &mIn,  0  );
	if  (  hr  )  return  -1;
	
	if  (  configureDMO_enc(  &encParams,  m_pObject,  (  AM_MEDIA_TYPE  *  )&mIn,  (  AM_MEDIA_TYPE  *  )&mOut  )  )  {
		traceLogA(  (char*)  "ConfigureDMO failed."  );
		return  -1;
	}
	traceLogA(  (char*)  "ConfigureDMO ok"  );



	 return  0;
}


///////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////
//
// Media buffer helper
//
//////////////////////////////////////////////////////////////////////////////
#if  0
class CHandlingMediaBuffer : public IMediaBuffer {
    BYTE *m_pData;
    ULONG m_ulSize;
    ULONG m_ulData;
    ULONG m_cRef;
    BYTE bInterlaceProperty;
public:
    CHandlingMediaBuffer(): bInterlaceProperty( 0 ) {
        m_cRef = 1;
    }
    
    void set_Buffer(BYTE *pData, DWORD ulData, DWORD ulSize) {
        m_pData = pData;
        m_ulSize = ulSize;
        m_ulData = ulData;
    }
    
    //
    // IUnknown
    //
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv) {
        if (riid == IID_IUnknown) {
            AddRef();
            *ppv = /*reinterpret_cast<IUnknown*>*(IUnknown*)( this );
            return ( NOERROR );
        } else if (riid == IID_IMediaBuffer) {
            AddRef();
            *ppv = /*reinterpret_cast<IMediaBuffer*>*/(IMediaBuffer*)( this );
            return ( NOERROR );
        } else {
            return ( E_NOINTERFACE );
        }
    }
    
    STDMETHODIMP_(ULONG) AddRef() {
        return InterlockedIncrement((long*)&m_cRef);
    }
    STDMETHODIMP_(ULONG) Release() {
        long l = InterlockedDecrement((long*)&m_cRef);
        if (l == 0)
            delete this;
        return l;
    }
    
    //
    // IMediaBuffer
    //
    STDMETHODIMP GetLength(DWORD *pulLength ){
        if( NULL == pulLength ){
            return ( E_POINTER );
        }
        *pulLength = m_ulData;
        return ( NOERROR );
    }

    STDMETHODIMP SetLength(DWORD ulLength ){
        m_ulData = ulLength;
        return ( NOERROR );
    }
    
    STDMETHODIMP GetMaxLength(DWORD *pcbMaxLength){
        *pcbMaxLength = m_ulSize;
        return ( NOERROR );
    }
    STDMETHODIMP GetBufferAndLength(BYTE **ppBuffer, DWORD *pcbLength) {
        if( NULL != ppBuffer ){
            *ppBuffer = m_pData;
        }
        if( NULL != pcbLength ){
            *pcbLength = m_ulData;
        }
        return ( NOERROR );
    }
};

struct HandlingContext {
    CHandlingMediaBuffer *pInputBuffer;
    CHandlingMediaBuffer *pOutputBuffer;

    BYTE                 *pbBuffer;
    LONG                 cbBuffer;

    AM_MEDIA_TYPE        mtIn;
    AM_MEDIA_TYPE        mtOut;
 
    PAVISTREAM           pAviInStream;
    PAVISTREAM           pAviOutStream;
    PGETFRAME            pGetFrame;
    DWORD                dwScale;
    DWORD                dwRate;

    IMediaObject         *pDMO;

    REFERENCE_TIME       rtFrameDuration;
    REFERENCE_TIME       rtTimeStamp;
};

struct GeneralParams {
    TCHAR *pszInput;
    TCHAR *pszOutput;
    BOOL  fAudioOnly;
    BOOL  fVideoOnly;

    GeneralParams(){
        memset(this, 0, sizeof( GeneralParams) );
    }
    ~GeneralParams(){
        SAFEFREE(pszInput);
        SAFEFREE(pszOutput);
    }
};

HRESULT MatchVideoParams( IMediaObject   *pDMO,
                          VideoDecParams *pParams,
                          AM_MEDIA_TYPE  *pmt       ) {
    VIDEOINFOHEADER *pvih = NULL;
    int             c     = 0;
    BOOL            fDone = FALSE;
    
    do {
        HRESULT hr = pDMO->GetOutputType(0, c, (  DMO_MEDIA_TYPE  *  )pmt);
        if ( FAILED( hr ) ){
            break;
        }
        if( pmt->formattype != FORMAT_VideoInfo      ||
            pmt->pbFormat   == NULL                  ||
            pmt->cbFormat   < sizeof( VIDEOINFOHEADER ) )
            return ( -1 );
        
        pvih = (VIDEOINFOHEADER*)pmt->pbFormat;
        
        if( pvih->bmiHeader.biCompression == pParams->dwTag          &&
            pvih->bmiHeader.biBitCount    == pParams->dwBitsPerPixel ){            
            fDone = TRUE;
        }
        
        if( fDone == FALSE ){
            CoTaskMemFree( pmt->pbFormat );
            memset(pmt, 0, sizeof( *pmt ) );
        }
        c++;
    } while( fDone == FALSE );
    
    return ( fDone == TRUE ? S_OK : ( -1 ) );
}

HRESULT SetVideoTypes_dec( IMediaObject   *pDMO,    \
                      AM_MEDIA_TYPE  *pmtIn,   \
                      VideoDecParams *pParams, \
                      AM_MEDIA_TYPE  *pmtOut,  \
                      DWORD *pcbIn,            \
                      DWORD *pcbOut ){
    HRESULT hr;
    DWORD   dwDummy;
    
    hr = pDMO->SetInputType(0, (  DMO_MEDIA_TYPE  *  )pmtIn, 0);
    if( S_OK != hr ){
        return ( hr );
    }
    
    hr = MatchVideoParams( pDMO, pParams, pmtOut );
    if( FAILED( hr ) ){
        return ( hr );
    }
    
    hr = pDMO->SetOutputType(0, (  DMO_MEDIA_TYPE  *  )pmtOut, 0);
    if( S_OK != hr ){
        return ( hr );
    }
    
    hr = pDMO->GetInputSizeInfo( 0, pcbIn, &dwDummy, &dwDummy);
    if( FAILED(hr) ){
        return ( hr );
    }
    
    hr = pDMO->GetOutputSizeInfo( 0, pcbOut, &dwDummy);
    if( FAILED( hr ) ){
        return ( hr );
    }
    
    return ( hr == S_FALSE ? -1: hr );
} 


HRESULT InitializeVideoDecoder(  AM_MEDIA_TYPE      *pmtInput,
                                VideoDecParams       *pParams,
                                IMediaObject         **ppDMO,
                                AM_MEDIA_TYPE        *pmtOutput,
                                CHandlingMediaBuffer *pMediaBuffer ){
    HRESULT       hr             = S_OK;
    DWORD         cbInputBuffer  = 0;
    DWORD         cbOutputBuffer = 0;
    
    if( NULL == pmtInput || NULL == pParams || NULL == ppDMO ){
        return ( E_INVALIDARG );
    }

    *ppDMO = NULL;
    
    do {
        //
        // Create the DMO Encoder
        //
        hr = CoCreateInstance( CLSID_CWMVDecMediaObject,
                NULL,
                CLSCTX_INPROC_SERVER,
                IID_IMediaObject,
                (void**)ppDMO);
        if( FAILED( hr ) ){
            break;
        }

        hr = SetVideoTypes_dec( *ppDMO, pmtInput, pParams, pmtOutput, &cbInputBuffer, &cbOutputBuffer );
        if( FAILED( hr ) ){
            break;
        }

    } while ( FALSE );

    if( S_OK != hr ){
        SAFERELEASE( *ppDMO );
    }
    
    return ( hr );     
}


void FreeContext( HandlingContext  *pHContext ){
    if( NULL != pHContext->pDMO ){
        SAFERELEASE( pHContext->pDMO );
    }
    if( NULL != pHContext->mtOut.pbFormat ){
        CoTaskMemFree( pHContext->mtOut.pbFormat );
        memset( &pHContext->mtOut, 0, sizeof( AM_MEDIA_TYPE ) );
    }
    if( NULL != pHContext->mtIn.pbFormat ){
        CoTaskMemFree( pHContext->mtIn.pbFormat );
        memset( &pHContext->mtIn, 0, sizeof( AM_MEDIA_TYPE ) );
    }
    if( NULL != pHContext->pAviInStream ){
        AVIStreamRelease( pHContext->pAviInStream );
    }
    if( NULL != pHContext->pAviOutStream ){
        AVIStreamRelease( pHContext->pAviOutStream );
    }
    
    if( NULL != pHContext->pGetFrame ){
        AVIStreamGetFrameClose( pHContext->pGetFrame );
        pHContext->pGetFrame = NULL;
    }
    
    SAFEDELETE ( pHContext->pbBuffer );
    SAFEDELETES( pHContext->pInputBuffer );        
    SAFEDELETES( pHContext->pOutputBuffer );        
    SAFEDELETES( pHContext );        
}



HRESULT InitializeDecoder( void                 *pParams,
                           IMediaObject         **ppDMO,
                           AM_MEDIA_TYPE        *pmtIn,
                           AM_MEDIA_TYPE        *pmtOut,
                           CHandlingMediaBuffer *pMediaBuffer){
    HRESULT         hr = S_OK;
    
    if( NULL == pParams ||
        NULL == ppDMO   ||
        NULL == pmtIn   ||
        NULL == pmtOut  ){
        return ( E_INVALIDARG );
    }
    
    if( FORMAT_WaveFormatEx == pmtIn->formattype ) {
        //  hr = InitializeAudioDecoder( pmtIn, (AudioDecParams*)pParams, ppDMO, pmtOut );
		hr  =  -1;
    } else if ( FORMAT_VideoInfo  == pmtIn->formattype  ||
        FORMAT_VideoInfo2 == pmtIn->formattype ){
        hr = InitializeVideoDecoder( pmtIn, 
                                    (VideoDecParams*)pParams,
                                     ppDMO,
                                     pmtOut,
                                     pMediaBuffer );
    } else {
        CoTaskMemFree( pmtIn->pbFormat );
        memset( pmtIn, 0, sizeof( AM_MEDIA_TYPE ) );
        hr = ( -1 );
    }
    return ( hr );    
}

HRESULT SetUpDecoder( void           *pParams,
                      HandlingContext *pContext ){
    HRESULT  hr      = S_OK;
    DWORD    dwFlags;

    if( NULL    == pContext ||
        NULL    == pParams  ){
        return ( E_INVALIDARG );
    }
    
    pContext->pDMO               = NULL;
    
    do{
        pContext->pInputBuffer    = new CHandlingMediaBuffer;
        if( pContext->pInputBuffer == NULL ){
            hr = E_OUTOFMEMORY;
            break;
        }
        
        pContext->pOutputBuffer   = new CHandlingMediaBuffer;
        if( pContext->pOutputBuffer == NULL ){
            hr = E_OUTOFMEMORY;
            break;
        }
        
        //
        //instantiate the DMO encoder
        //
        hr = InitializeDecoder( pParams,
                                &pContext->pDMO,
                                &pContext->mtIn,
                                &pContext->mtOut,
                                pContext->pInputBuffer );
        if( FAILED( hr ) ){
            break;
        }
        //
        // The codecs used in this sample don't perform lookahead on the incoming data.
        // If this changes the scheme used here may not work.
        // FAIL is the encoder uses lookahead.
        //
        hr = pContext->pDMO->GetInputStreamInfo( 0, &dwFlags );
        if( FAILED( hr ) ){
            break;
        }
        if( dwFlags & DMO_INPUT_STREAMF_HOLDS_BUFFERS ){
            //  hr = E_NEEDS_LOOKAHEAD;
			hr  =  -1;
            break;
        }        
    } while( FALSE );
    
    return ( hr );
}

HRESULT GetFormat( PAVISTREAM paviStream, BYTE **ppbFormat, int *pcbFormat ){
    HRESULT hr       = S_OK;
    BYTE   *pbFormat = NULL;
    LONG   cbFormat  = 0;
    
    if( NULL == paviStream ||
        NULL == ppbFormat  ||
        NULL == pcbFormat  ){
        return ( E_INVALIDARG );
    }
    
    *ppbFormat = NULL;
    *pcbFormat = NULL;
    do {
        hr = AVIStreamFormatSize( paviStream, 0, &cbFormat );
        if( S_OK != hr ){
            break;
        }
        if( 0 >= cbFormat ){
            hr = -1;
            break;
        }
        
        pbFormat = (BYTE*)CoTaskMemAlloc( cbFormat );
        if( NULL == pbFormat ){
            hr = E_OUTOFMEMORY;
            break;
        }
        hr = AVIStreamReadFormat( paviStream, 0, pbFormat, &cbFormat );
        if( S_OK != hr ){
            break;
        }
    }while( FALSE );
    
    if( S_OK != hr ){
        if( NULL != pbFormat ){
            CoTaskMemFree( pbFormat );
        }
    } else {
        *ppbFormat = pbFormat;
        *pcbFormat = cbFormat;
    }
    return ( hr );   
}

HRESULT GetVideoMediaType( AVISTREAMINFO   *streamInfo,
                           BYTE            *pbFormat,
                           int             cbFormat,
                           HandlingContext *pContext ){
    HRESULT          hr           = S_OK;
    DWORD            *pdwMask     = NULL;
    VIDEOINFOHEADER  *pvih        = NULL;
    BITMAPINFOHEADER *pbmi        = NULL;
    BITMAPINFOHEADER *pbmiIn      = NULL;
    PGETFRAME        pGetFrame    = NULL;
    BOOL             fUnsupported = FALSE;
    LONG             lFormat      = 0;
    BYTE             *pbVideoBits = NULL;

    if( NULL                       == streamInfo ||
        NULL                       == pbFormat   ||
        sizeof( BITMAPINFOHEADER ) >  cbFormat   ||
        NULL                       == pContext   ){
        return ( E_INVALIDARG );
    }
    
    
    do {
        //
        //check the fourcc
        //
        pbmi = (BITMAPINFOHEADER*)pbFormat;
        pbmiIn = pbmi;
        switch( pbmi->biCompression ){
        case mmioFOURCC( 'W', 'M', 'V', '3' ):
            pContext->mtIn.subtype = WMCMEDIASUBTYPE_WMV3;
            break;
        default:
            fUnsupported = TRUE;
        }
        
        if( fUnsupported ){
            hr = -1;
            break;
        }

        lFormat = sizeof( VIDEOINFOHEADER ) + pbmiIn->biSize - sizeof( BITMAPINFOHEADER ) + pbmiIn->biClrUsed * 4;
        pvih = (VIDEOINFOHEADER*)CoTaskMemAlloc( lFormat );
        if( NULL == pvih ){
            hr = E_OUTOFMEMORY;
            break;
        }
        
        memset( pvih, 0, lFormat );
        //
        //Fill the format fields
        //
        pvih->rcSource.left   = 0;
        pvih->rcSource.top    = 0;
        pvih->rcSource.right  = pbmiIn->biWidth;
        pvih->rcSource.bottom = pbmiIn->biHeight;
        pvih->rcTarget        = pvih->rcSource;
        pvih->dwBitErrorRate  = 0;
        if( 0 != streamInfo->dwRate ){
            pContext->rtFrameDuration = (REFERENCE_TIME)streamInfo->dwScale * 10000000 / streamInfo->dwRate;
            pvih->AvgTimePerFrame     = pContext->rtFrameDuration;
        }
        if( 0 != streamInfo->dwScale ){
            pvih->dwBitRate       = (DWORD)((__int64)pbmiIn->biSizeImage *  streamInfo->dwRate * 8 / streamInfo->dwScale );
        }
        memcpy( &pvih->bmiHeader, pbmiIn, pbmiIn->biSize + pbmiIn->biClrUsed * 4 );
        //
        //Fill the media type fields
        //
        pContext->mtIn.majortype            = MEDIATYPE_Video;
        pContext->mtIn.formattype           = FORMAT_VideoInfo;
        pContext->mtIn.bFixedSizeSamples    = FALSE;
        pContext->mtIn.bTemporalCompression = FALSE;
        pContext->mtIn.lSampleSize          = 0;
        pContext->mtIn.pbFormat             = (BYTE*)pvih;
        pContext->mtIn.cbFormat             = lFormat;
    } while ( FALSE );
    
    return ( hr );
}

HRESULT GetMediaType( PAVISTREAM paviStream, DWORD dwType, HandlingContext *pContext ){
    HRESULT          hr         = S_OK;
    BYTE             *pbFormat  = NULL;
    int              cbFormat   = 0;
    DWORD            *pdwMask   = NULL;
    WAVEFORMATEX     *pwfx      = NULL;
    VIDEOINFOHEADER  *pvih      = NULL;
    BITMAPINFOHEADER *pbmi      = NULL;
    BITMAPINFOHEADER *pbmiIn    = NULL;
    AVISTREAMINFO    streamInfo;
    PGETFRAME        pGetFrame  = NULL;
    
    if( NULL == paviStream || NULL == pContext ){
        return ( E_INVALIDARG );
    }

    if( streamtypeVIDEO != dwType && streamtypeAUDIO != dwType ){
        return ( E_INVALIDARG );
    }
    
    memset( &pContext->mtIn, 0, sizeof( AM_MEDIA_TYPE ) );
    memset( &streamInfo,     0, sizeof( AVISTREAMINFO ) );
    
    do {
        hr = AVIStreamInfo( paviStream, &streamInfo, sizeof( AVISTREAMINFO ) );
        if( S_OK != hr ){
            break;
        }
        pContext->dwRate  = streamInfo.dwRate;
        pContext->dwScale = streamInfo.dwScale;
        
        hr = GetFormat( paviStream, &pbFormat, &cbFormat );
        if( S_OK != hr ){
            break;
        }
        if( streamtypeVIDEO == dwType ){
            hr = GetVideoMediaType( &streamInfo, pbFormat, cbFormat, pContext );
            if( S_OK != hr ){
                break;
            }
        } else {
            //  hr = GetAudioMediaType( &streamInfo, pbFormat, cbFormat, pContext );
			hr  =  -1;
            if( S_OK != hr ){
                break;
            }
            pbFormat = NULL;
        }
    } while( FALSE );
    
    if( NULL != pbFormat ){
        CoTaskMemFree( pbFormat );
    }
    return ( hr );
}


HRESULT ConfigVideoStreams( PAVIFILE        paviInput,
                           PAVIFILE        paviOutput,
                           GeneralParams   *pIOParams,
                           VideoDecParams  *pVideoParams,
                           HandlingContext **ppVideoContext ){
    PAVISTREAM      paviStreamVideoIn  = NULL;
    PAVISTREAM      paviStreamVideoOut = NULL;
    HandlingContext *pVideoContext     = NULL;
    HRESULT         hr                 = S_OK;
    AVISTREAMINFO   streamInfo;  
    
    if( NULL == paviInput    ||
        NULL == paviOutput   ||
        NULL == pVideoParams ||
        NULL == pIOParams    ){
        return ( E_INVALIDARG );
    }
    
    memset( &streamInfo, 0, sizeof( streamInfo ) );
    
    do {
        hr = AVIFileGetStream( paviInput, &paviStreamVideoIn, streamtypeVIDEO, 0 );
        if( S_OK != hr ){
            break;
        }
        
        pVideoContext = new HandlingContext;
        if( NULL == pVideoContext ){
            hr = E_OUTOFMEMORY;
            break;
        }
        memset( pVideoContext, 0, sizeof( HandlingContext ) );
        pVideoContext->pAviInStream = paviStreamVideoIn;
        AVIStreamAddRef( pVideoContext->pAviInStream );
        hr = GetMediaType( paviStreamVideoIn, streamtypeVIDEO, pVideoContext );
        if( S_OK != hr ){
            break;
        }
        
        hr = SetUpDecoder( pVideoParams, pVideoContext );
        if( FAILED( hr ) ){
            break;
        }
        //
        //Add the video out stream
        //
        hr = AVIStreamInfo( paviStreamVideoIn, &streamInfo, sizeof( AVISTREAMINFO ) );
        if( FAILED( hr ) ){
            break;
        }
        streamInfo.fccHandler            = pVideoParams->dwTag;
        streamInfo.dwSuggestedBufferSize = 0;
        streamInfo.dwStart               = 0;
        
        hr = AVIFileCreateStream( paviOutput, &paviStreamVideoOut, &streamInfo );
        if( FAILED( hr ) ){
            break;
        }
        
        hr = AVIStreamSetFormat( paviStreamVideoOut,
            0,
            &((VIDEOINFOHEADER*)pVideoContext->mtOut.pbFormat)->bmiHeader,
            ((VIDEOINFOHEADER*)pVideoContext->mtOut.pbFormat)->bmiHeader.biSize );
        if( FAILED( hr ) ){
            break;
        }
        pVideoContext->pAviOutStream = paviStreamVideoOut;
        AVIStreamAddRef( pVideoContext->pAviOutStream );
        
    } while( FALSE );
    
    if( S_OK == hr ){
        *ppVideoContext = pVideoContext;
    } else {
        SAFEDELETES( pVideoContext );
    }
    
    if( NULL != paviStreamVideoIn ){
        AVIStreamRelease( paviStreamVideoIn);
    }
    
    if( NULL != paviStreamVideoOut ){
        AVIStreamRelease( paviStreamVideoOut);
    }
    
    return ( hr );
}

#endif


/*
 int  testDmoDecompressInit(  )
{
	GeneralParams			IOParams;
	VideoDecParams			VideoParams;
	HandlingContext		*	pVideoContext     = NULL;
	HRESULT					hr;


	
	hr = ConfigVideoStreams(  NULL,  NULL, &IOParams, &VideoParams, &pVideoContext );



	if( NULL != pVideoContext ){
        FreeContext( pVideoContext );
    }



	return  0;
}
*/


 int  testDmoDecompress(  void  *  pCompressVideoParam,  QMC_DMO  *  pDmo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput  )
{
		int					iErr			=	-1;
		COMPRESS_VIDEO  *  pCompressVideo	=	(  COMPRESS_VIDEO  *  )pCompressVideoParam;
		if  (  !pCompressVideo  )  return  -1;

		if  (  !pDmo  )  return  -1;

	    //  BYTE					*	pOut			=	NULL;
        CMediaBuffer            *	pInputBuffer	=	NULL;
        const REFERENCE_TIME		rtStart			=	0;
        const REFERENCE_TIME		rtStop			=	0;
        BYTE					*	pBuffer			=	NULL;
        DWORD						dwLength;
		HRESULT						hr;

        // create and fill CMediaBuffer
		hr = CreateBuffer(  pBmpInfo_input->bmiHeader.biSizeImage, &pInputBuffer);
        if( FAILED( hr ) )  return  -1;
        
        hr = pInputBuffer->GetBufferAndLength( &pBuffer, &dwLength );
        if( FAILED( hr ) )  goto  errLabel;

		CopyMemory(  pBuffer,  pInput,  pBmpInfo_input->bmiHeader.biSizeImage  );

		hr = pInputBuffer->SetLength(  pBmpInfo_input->bmiHeader.biSizeImage  );
        if( FAILED( hr ) )  goto  errLabel;
        
        // call processInput
        hr = pDmo->m_pObject->ProcessInput( 0,
                                pInputBuffer,
                                DMO_INPUT_DATA_BUFFERF_SYNCPOINT,
                                rtStart,
                                rtStop - rtStart);
        if( FAILED( hr ) )  goto  errLabel;

        //release input buffer
        MACRO_safeRelease( pInputBuffer );

        // retrieve the output data from DMO and put into pOut
        if(S_FALSE == hr)  goto  errLabel;

		static  char  buf[10  *  1024  *  1024];
		DWORD	len;
		len  =  mycountof(  buf  );
		//  hr = dmoProcessOutputs(  pDmo,  (  BYTE  *  )buf, len  );
		if( FAILED( hr ) )  goto  errLabel;
		
		/*
		{
	QY_MC				*	pQyMc		=		QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci		=		getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  return  -1;
	MC_VAR_isCli			*	pProcInfo1		=		(  MC_VAR_isCli  *  )pSci->pVar;
	BYTE				*	pData_allocated	=		NULL;

		CAP_procInfo_video  *  pVc;
		pVc  =  &pProcInfo1->av.localAv.videoCaptureProcInfo;
		if  (  !pVc->bLocalVideoShowed  &&  pProcInfo1->av.localAv.videoCaptureProcInfo.curhWnd  )  {
			QY_MC					*	pQyMc	=	(  QY_MC  *  )pProcInfo1->pQyMcParam;
			MIS_MSG_procVideo_qmc		msg;
			memset(  &msg,  0,  sizeof(  msg  )  );
			msg.uiType  =  CONST_misMsgType_procVideo_qmc;
			//  msg.ucbLocalAv  =  TRUE;
			memcpy(  &msg.bih,  &pBmpInfo_input->bmiHeader,  sizeof(  msg.bih  )  );
			msg.data  =  pData_allocated  =  (  BYTE  *  )mymalloc(  msg.bih.biSizeImage  );
			if  (  !msg.data  )  goto  errLabel;
			memcpy(  msg.data,  pInput,  pBmpInfo_input->bmiHeader.biSizeImage  );

			if  (  qPostMsg(  &msg,  sizeof(  msg  ),  &pQyMc->gui.guiQ  )  )  goto  errLabel;
			pData_allocated  =  NULL;		//  this means the allocated data should be freed by the thread who get the msg.

			PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_guiMsgArrive,  0  );   

			pVc->bLocalVideoShowed  =  TRUE;
		}

		}
		*/



		iErr  =  0;
errLabel:

		//release input buffer
        MACRO_safeRelease( pInputBuffer );

		return  iErr;
}


 int  testDmoDecompressInit(  COMPRESS_VIDEO  *  pCompressVideo  )
{

	 //  enumDmo(  );
	 QY_MC* pQyMc = nullptr;// QY_GET_GBUF();
	 return -1;
	 DYN_LIB_DX	*	pDynLib	=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	 GUID			clsid;
	 GUID			clsid_mInSubType;
	 DWORD			dwTag;
	 BOOL			bWmv	=	FALSE;
	 int			iWidth	=	pCompressVideo->vh_decompress.bih.biWidth;
	 int			iHeight	=	pCompressVideo->vh_decompress.bih.biHeight;
	 QMC_DMO		dmo;
	 VideoDecParams  VideoParams;

	 memset(  &dmo,  0,  sizeof(  dmo  )  );

	 //  CLSID_CWMVEncMediaObject2;
	 /*
	 clsid  =  CLSID_MSScreen9_Encoder_DMO;
	 clsid_mOutSubType  =  WMCMEDIASUBTYPE_MSS2;
	 dwTag  =  WMCFOURCC_MSS2;
	 bWmv  =  FALSE;
	 */
	 /*
	 clsid  =  CLSID_WMVideo_Decoder_DMO;
	 clsid_mInSubType  =  WMCMEDIASUBTYPE_WMV3;
	 dwTag  =  WMCFOURCC_WMV3;
	 bWmv  =  TRUE;
	 */
	 clsid  =  CLSID_WMVideo_Decoder_DMO;
	 clsid_mInSubType  =  WMCMEDIASUBTYPE_WMV1;
	 dwTag  =  WMCFOURCC_WMV1;
	 bWmv  =  TRUE;



	 //  SetEncodingDefaults(  encParams,  NULL, dwTag,  bWmv  );
	 


    // create DMO
    HRESULT hr = CoCreateInstance( clsid,
                         NULL,
                         CLSCTX_INPROC,
                         IID_IMediaObject,
                         (void **) &dmo.m_pObject);
    if ( FAILED( hr ) ){
		traceLogA(  (char*) ("Can't create this DMO.") );
        return hr;
    }


	/*
	DWORD  cInput  =  0,  cOutput  =  0;
	hr  =  m_pObject->GetStreamCount(  &cInput,  &cOutput  );

	DMO_MEDIA_TYPE		mt;
	DWORD				dwType  =  0;
	TCHAR				tBuf[256];
	char				fourccStr[16];
	int					i;

	while  (  hr  =  m_pObject->GetInputType(  0,  dwType,  &mt  ),  SUCCEEDED(  hr  )  )  {

			StringFromGUID2(  mt.subtype,  tBuf,  mycountof(  tBuf  )  );
			iFourcc2Str(  mt.subtype.Data1,  fourccStr,  mycountof(  fourccStr  )  );

			traceLogA(  (char*)  "inputType %d:%S, %S, fourccStr %s",  dwType,  tBuf,  getMediaSubtypeName(  mt.subtype  ),  fourccStr  );
						

			pDynLib->pMoFreeMediaType(  &mt  );
			dwType  ++  ;
	}

	for  (  i  =  0;  i  <  cOutput;  i  ++  )  {
		dwType  =  0;
		while  (  hr  =  m_pObject->GetOutputType(  i,  dwType,  &mt  ),  SUCCEEDED(  hr  )  )  {

				StringFromGUID2(  mt.subtype,  tBuf,  mycountof(  tBuf  )  );
				iFourcc2Str(  mt.subtype.Data1,  fourccStr,  mycountof(  fourccStr  )  );

				traceLogA(  (char*)  "outputType ( %d,%d ): %S, %S,  fourccStr %s",  i,  dwType,  tBuf,  getMediaSubtypeName(  mt.subtype  ),  fourccStr  );
						
				pDynLib->pMoFreeMediaType(  &mt  );

				dwType  ++  ;
		}
	}
	*/

	DMO_MEDIA_TYPE      mIn;
	DMO_MEDIA_TYPE		mOut;
	memset(  &mIn,  0, sizeof(  mIn  )  );
	memset(  &mOut,  0,  sizeof(  mOut  )  );

	hr  =  pDynLib->pMoInitMediaType(  &mIn,  sizeof(  VIDEOINFOHEADER  )  +  pCompressVideo->vh_compress.bih.biSize  -  sizeof(  BITMAPINFOHEADER  )  );
	if  (  FAILED(  hr  )  )  goto  errLabel;
	mIn.majortype  =  MEDIATYPE_Video;
	mIn.subtype  =  clsid_mInSubType;
	mIn.formattype  =  FORMAT_VideoInfo;	
	VIDEOINFOHEADER  *  pViho;	pViho  =  (  VIDEOINFOHEADER  *  )mIn.pbFormat;
	memcpy(  &pViho->bmiHeader,  &pCompressVideo->vh_compress.bih,  pCompressVideo->vh_compress.bih.biSize  );

	hr  =  pDynLib->pMoInitMediaType(  &mOut,  sizeof(  VIDEOINFOHEADER  )  );
	if  (  FAILED(  hr  )  )  goto  errLabel;

	mOut.majortype  =  MEDIATYPE_Video;
	mOut.subtype  =  MEDIASUBTYPE_RGB24;
	mOut.formattype  =  FORMAT_VideoInfo;
	mOut.lSampleSize  =  1;
	VIDEOINFOHEADER  *  pvihi  =  (  VIDEOINFOHEADER  *  )mOut.pbFormat;
	memset(  pvihi,  0,  sizeof(  VIDEOINFOHEADER  )  );
	pvihi->AvgTimePerFrame	=	DEFAULT_AvgTimePerFrame;	//  1000000;
	makeBmpInfoHeader_rgb(  24,  iWidth,  iHeight,  &pvihi->bmiHeader  );

	//  int  len  =  sizeof(  VIDEOINFOHEADER  );

	hr  =  dmo.m_pObject->SetInputType(  0,  &mIn,  0  );
	if  (  hr  )  goto  errLabel;
	
	hr  =  dmo.m_pObject->SetOutputType(  0,  &mOut,  0  );
	if  (  FAILED(  hr  )  )  goto  errLabel;

	/*
	if  (  configureDMO_enc(  encParams,  m_pObject,  (  AM_MEDIA_TYPE  *  )&mIn,  (  AM_MEDIA_TYPE  *  )&mOut  )  )  {
		traceLogA(  (char*)  "ConfigureDMO failed."  );
		return  -1;
	}
	*/
	traceLogA(  (char*)  "ConfigureDMO ok"  );

	testDmoDecompress(  pCompressVideo,  &dmo,  (  BITMAPINFO  *  )&pCompressVideo->vh_compress.bih,  (  BYTE  *  )pCompressVideo->pCompressBuf  );


errLabel:
	
	pDynLib->pMoFreeMediaType(  &mIn  );
	pDynLib->pMoFreeMediaType(  &mOut  );

	MACRO_safeRelease(  dmo.m_pObject  );

	 return  0;
}



#endif




  int  initCompressVideo_dmo(  VIDEO_COMPRESSOR_CFG  *  pCompressor,  QY_VIDEO_HEADER  *  pVh_decompress,  QY_VIDEO_HEADER  *  pVh_compress,  MY_DMO_INFO  *  pDmoInfo  )
{
	 int			iErr					=	-1;
	 //
	 traceLogA(  (char*)  "initDmoCompressVideo enters"  );

	 if  (  !pDmoInfo  )  return  -1;
	 if  (  pDmoInfo->pDmo  )  return  -1;
	 //
	 QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();
	 DYN_LIB_DX			*	pDynLib			=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	 GUID					clsid;
	 GUID					clsid_mInSubType;
	 GUID					clsid_mOutSubType;
	 int					iWidth			=	pVh_decompress->bih.biWidth;
	 int					iHeight			=	pVh_decompress->bih.biHeight;

	 MY_DMO_INFO			myDmoInfo;
	 QMC_DMO			*	pDmo			=	NULL;

	 DMO_MEDIA_TYPE			mIn;
	 BOOL					bInited_mIn		=	FALSE;
	 DMO_MEDIA_TYPE			mOut;	
	 BOOL					bInited_mOut	=	FALSE;


	 memset(  &myDmoInfo,  0,  sizeof(  myDmoInfo  )  );
	 pDmo  =  (  QMC_DMO  *  )mymalloc(  sizeof(  QMC_DMO  )  );
	 if  (  !pDmo  )  goto  errLabel;
	 memset(  pDmo,  0,  sizeof(  QMC_DMO  )  );
	 myDmoInfo.pDmo  =  pDmo;

	 /*
	 clsid  =  CLSID_MSScreen9_Encoder_DMO;
	 clsid_mOutSubType  =  WMCMEDIASUBTYPE_MSS2;
	 dwTag  =  WMCFOURCC_MSS2;
	 bWmv  =  FALSE;
	 */
	 /*
	 clsid  =  CLSID_WMVideo9_Encoder_DMO;
	 clsid_mOutSubType  =  WMCMEDIASUBTYPE_WMV3;
	 dwTag  =  WMCFOURCC_WMV3;
	 bWmv  =  TRUE;
	 */

	 if  (  pCompressor->params.dwTag  !=  fourccStr2i(  pCompressor->common.fourccStr  )  )  {
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initDmoCompressVideo failed: dwTag != fourcc"  )  );
		 goto  errLabel;
	 }
	 if  (  !pCompressor->params.dwTag  )  {
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initDmoCompressVideo failed: dwTag is 0"  )  );
		 goto  errLabel;
	 }

	 clsid_mOutSubType  =  FOURCCMap(  pCompressor->params.dwTag  );
	 clsid_mInSubType  =  MEDIASUBTYPE_RGB24;
	 if  (  getDmoInfoBySth(  pQyMc,pDynLib,  &DMOCATEGORY_VIDEO_ENCODER,  NULL,  &clsid_mInSubType,  NULL,  &clsid_mOutSubType,  NULL,  &clsid,  NULL  )  )  {
		 clsid_mInSubType  =  MEDIASUBTYPE_YUY2;
		 if  (  getDmoInfoBySth(  pQyMc,  pDynLib,  &DMOCATEGORY_VIDEO_ENCODER,  NULL,  &clsid_mInSubType,  NULL,  &clsid_mOutSubType,  NULL,  &clsid,  NULL  )  )  {
			 traceLog((TCHAR*)  _T(  "initDmoCompressVideo: No correct video encoder found"  )  );
			 goto  errLabel;
		 }
	 }

#ifdef  __DEBUG__
		#if  0
			traceLog((TCHAR*)  _T(  "initDmoCompressVideo: for test, dwTag_input is set to yuy2"  )  );
			clsid_mInSubType  =  MEDIASUBTYPE_YUY2;

		#endif
#endif


    // create DMO
    HRESULT hr = CoCreateInstance( clsid,
                         NULL,
                         CLSCTX_INPROC,
                         IID_IMediaObject,
                         (void **) &pDmo->m_pObject);
    if ( FAILED( hr ) ){
		traceLogA(  (char*) ("Can't create this DMO.") );
		goto  errLabel;
    }

	//
	memset(  &mIn,  0, sizeof(  mIn  )  );
	hr  =  pDynLib->pMoInitMediaType(  &mIn,  sizeof(  VIDEOINFOHEADER  )  );
	if  (  FAILED(  hr  )  )  goto  errLabel;
	bInited_mIn  =  TRUE;

	memset(  &mOut,  0,  sizeof(  mOut  )  );
	bInited_mOut  =  TRUE;

#if !defined(  __WINCE__  )  ||  defined(  __TEST__  )
	mIn.majortype  =  MEDIATYPE_Video;
#else
	mIn.majortype  =  MEDIATYPE_VideoBuffered;
#endif
	mIn.subtype  =  clsid_mInSubType;
	mIn.formattype  =  FORMAT_VideoInfo;
	VIDEOINFOHEADER  *  pvihi  =  (  VIDEOINFOHEADER  *  )mIn.pbFormat;
	memset(  pvihi,  0,  sizeof(  VIDEOINFOHEADER  )  );

	if  (  pCompressor->common.usMaxFps_toShareBmp  <  11  )  {
		pvihi->AvgTimePerFrame  =  DEFAULT_AvgTimePerFrame;
		}
	else  {
		  if  (  pCompressor->params.fFrameRate  <  0.001  )  pvihi->AvgTimePerFrame	=	DEFAULT_AvgTimePerFrame;	//  1000000;
		  else  pvihi->AvgTimePerFrame  =  10000000. / pCompressor->params.fFrameRate;
	}

#if  10
	if  (  clsid_mInSubType  ==  MEDIASUBTYPE_RGB24  )  {
		makeBmpInfoHeader_rgb(  24,  iWidth,  iHeight,  &myDmoInfo.inputForEnc.vh_decompress_real.bih  );
		}
	else  if  (  clsid_mInSubType  ==  MEDIASUBTYPE_YUY2  )  {
			  makeBmpInfoHeader_yuy2(  16,  iWidth,  iHeight,  &myDmoInfo.inputForEnc.vh_decompress_real.bih  );
			  myDmoInfo.inputForEnc.uiBufSize  =  myDmoInfo.inputForEnc.vh_decompress_real.bih.biSizeImage;
			  myDmoInfo.inputForEnc.pBuf  =  (  char  *  )mymalloc(  myDmoInfo.inputForEnc.uiBufSize  );
			  if  (  !myDmoInfo.inputForEnc.pBuf  )  goto  errLabel;
			}
	else  {
		  goto  errLabel;
	}
	memcpy(  &pvihi->bmiHeader,  &myDmoInfo.inputForEnc.vh_decompress_real.bih,  sizeof(  BITMAPINFOHEADER  )  );
#endif
	//
	if  (  1  )  {
		mIn.lSampleSize  =  1;		
	}
#if  0
	else  
	{
		  mIn.bFixedSizeSamples  =  TRUE;	
		  mIn.lSampleSize  =  pvihi->bmiHeader.biSizeImage;
	}
#endif

	hr  =  pDmo->m_pObject->SetInputType(  0,  &mIn,  0  );
	if  (  hr  )  goto  errLabel;
	
	if  (  configureDMO_enc(  &pCompressor->params,  pDmo->m_pObject,  (  AM_MEDIA_TYPE  *  )&mIn,  (  AM_MEDIA_TYPE  *  )&mOut  )  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initCompressVideo_dmo:ConfigureDMO failed."  )  );
		traceLogA(  (char*)  "ConfigureDMO failed."  );
		goto  errLabel;
	}
	traceLogA(  (char*)  "ConfigureDMO ok"  );

	if  (  mOut.formattype  ==  FORMAT_VideoInfo
		&&  mOut.cbFormat  >=  sizeof(  VIDEOINFOHEADER  )
			&&  mOut.pbFormat  )  
	{
		VIDEOINFOHEADER	*	pVih  =  (  VIDEOINFOHEADER  *  )mOut.pbFormat;

		if  (  pVih->bmiHeader.biSize  >  sizeof(  pVh_compress[0]  )  )  {
			traceLogA(  (char*)  "initDmoCompressVideo failed: biSize > sizeof(  vh_compress ), %d",  pVih->bmiHeader.biSize  );
			goto  errLabel;
		}
		memcpy(  &pVh_compress->bih,  &pVih->bmiHeader,  pVih->bmiHeader.biSize  );

		//
		}
	else  {
		  traceLogA(  (char*)  "initDmoCompressVideo: mOut format error"  );
		  goto  errLabel;
	}


	//  2009/05/19
	myDmoInfo.cbInputBuffer  =  pVh_decompress->bih.biSizeImage;
	myDmoInfo.cbOutputBuffer  =  pVh_compress->bih.biSizeImage;

	// create and fill CMediaBuffer
	//  hr = CreateBuffer(  pVh_decompress->bih.biSizeImage, &pDmo->pInputBuffer  );
	//  if  (  FAILED(  hr  )  )  goto  errLabel;
	//  hr = CreateBuffer(  pVh_compress->bih.biSizeImage,  &pDmo->pOutputBuffer );
	//  if  (  FAILED( hr ) ) goto  errLabel;
	
	iErr  =  0;

errLabel:

	if  (  bInited_mOut  )  pDynLib->pMoFreeMediaType(  &mOut  );
	if  (  bInited_mIn  )  pDynLib->pMoFreeMediaType(  &mIn  );
	
	if  (  iErr  )  {
		exitCompressVideo_dmo(  &myDmoInfo  );		
	}
	if  (  !iErr  )  {
		memcpy(  pDmoInfo,  &myDmoInfo,  sizeof(  pDmoInfo[0]  )  );
	}

	traceLogA(  (char*)  "initDmoCompressVideo leaves"  );

	return  iErr;
}



 int  exitCompressVideo_dmo(  MY_DMO_INFO  *  pDmoInfo  )
{

	traceLogA(  (char*)  "exitDmoCompressVideo enters"  );

	if  (  !pDmoInfo  )  return  0;
	if  (  !pDmoInfo->pDmo  )  return  0;
	QMC_DMO  *  pDmo  =  (  QMC_DMO  *  )pDmoInfo->pDmo;

	if  (  pDmoInfo->inputForEnc.uiBufSize  )  {
		MACRO_safeFree(  pDmoInfo->inputForEnc.pBuf  );
		memset(  &pDmoInfo->inputForEnc,  0,  sizeof(  pDmoInfo->inputForEnc  )  );
	}

	if  (  pDmo  )  {
		freeDmoOutputs(  pDmoInfo  );
		MACRO_safeRelease(  pDmo->pInputBuffer  );

		//  2012/03/18
		HRESULT		hr;
		if  (  pDmo->m_pObject  )  {
			try  {
				//  Send Discontinuity on output stream
				hr = pDmo->m_pObject->Discontinuity( 0 );
				if ( FAILED( hr ) ) {
				}

			}
#ifdef  __useMfc__
			catch  (  CException  *  e  )  {
				e->Delete(  );
			}
#endif
			catch  (  ...  )  {
			}
		}

		//
		MACRO_safeRelease(  pDmo->m_pObject  );
	}
	MACRO_safeFree(  pDmo  );

	pDmoInfo->pDmo  =  NULL;

	traceLogA(  (char*)  "exitDmoCompressVideo leaves"  );

	return  0;
}




 //  
 int  getDmoOutputByIndex(  MY_DMO_INFO  *  pDmoInfo,  int  index,  BYTE *  pbOutData,  unsigned  int  *  puiDataSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  pui_rtTimeLen  )
{
	int							iErr	=	-1;

	//  2010/06/14
	if  (  pDmoInfo->bFilterGraph  )  return  -1;
	
	//
	QMC_DMO					*	pDmo	=	(  QMC_DMO  *  )pDmoInfo->pDmo;
	//  HRESULT						hr;
	ULONG						ulSize			=	0;
    BYTE					*	pOut			=	0;

	if  (  index  <  0  ||  index  >=  mycountof(  pDmo->outs  )  )  return  -1;
	if  (   !pDmo->outs[index].pBuf  )  return  -1;


	//  hr  =  pDmo->pOutputBuffers[index]->GetBufferAndLength(&pOut, &ulSize);
	//  if  (  FAILED(  hr  )  )  return  -1;
	pOut  =  pDmo->outs[index].pBuf;
	ulSize  =  pDmo->outs[index].len;
	if  (  !ulSize  )  return  -1;

	//
	if  (  *puiDataSize  <  ulSize  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "getDmoOutputByIndex failed: index %d, uiDataSize %d < ulSize %d"  ),  index,  *puiDataSize,  ulSize  );
		#endif
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "getDmoOutputByIndex failed: index %d, uiDataSize %d < ulSize %d"  ),  index,  *puiDataSize,  ulSize  );
		return  CONST_qdcRet_bufTooSmall;
	}
	*puiDataSize  =  min(  *puiDataSize,  ulSize  );
	CopyMemory(  pbOutData, pOut, *puiDataSize);
	if  (  puiSampleTimeInMs  )  {
		*puiSampleTimeInMs  =  (  unsigned  int  )(  pDmo->outs[index].rtStart  /  (  10  *  1000  )  );
		if  (  (  (  int  )*puiSampleTimeInMs  )  <  0  )  {
			traceLogA(  (char*)  "getDmoOutputByIndex err: *puiSampleTimeInMs %d < 0. force to set 0",  *puiSampleTimeInMs  );
			//  pDmoInfo->bErr_getDmoOutputByIndex  =  TRUE;
			*puiSampleTimeInMs  =  0;
		}
	}
	if  (  pui_rtTimeLen  )  {
		*pui_rtTimeLen  =  (  unsigned  int  )pDmo->outs[index].rtTimeLen;
	}

#ifdef  __DEBUG__
	    if  (  pDmoInfo->bAudio  )  {
			//  traceLogA(  (char*)  "getDmoOutputByIndex: uiSize %d, uiSampleTimeInMs %d",  ulSize,  (  puiSampleTimeInMs  ?  *puiSampleTimeInMs  :  0  )  );
		}
#endif

	pDmo->outs[index].len  =  0;
	pDmo->outs[index].rtStart  =  0;
	pDmo->outs[index].rtTimeLen  =  0;

	iErr  =  0;
//  errLabel:
	return  iErr;
}

 //  2011/12/24
 int  dmoClearOutputs(  MY_DMO_INFO  *  pDmoInfo  )
{
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dmoClearOutputs called"  )  );

	if  (  pDmoInfo->bFilterGraph  )  return  -1;

	//
	QMC_DMO  *  pDmo	=	(  QMC_DMO  *  )pDmoInfo->pDmo;
	int			i;

	for  (  i  =  0;  i  <  mycountof(  pDmo->outs  );  i  ++  )  {
		 pDmo->outs[i].len  =  0;
	}

	return  0;
}


  void  freeDmoOutputs(  MY_DMO_INFO  *  pDmoInfo  )
{
	//  2010/06/14
	if  (  pDmoInfo->bFilterGraph  )  return;

	//
	QMC_DMO  *  pDmo	=	(  QMC_DMO  *  )pDmoInfo->pDmo;
	int			i;

	MACRO_safeRelease(  pDmo->pOutputBuffer  );

	for  (  i  =  0;  i  <  mycountof(  pDmo->outs  );  i  ++  )  {
		 MACRO_safeFree(  pDmo->outs[i].pBuf  );
	}
	memset(  &pDmo->outs,  0,  sizeof(  pDmo->outs  )  );
}





 //  2013/08/25
 int  dmoProcessOutputs(  MY_DMO_INFO  *  pDmoInfo,  MY_DEBUG_STEP  *  pDebugStep  )
{
	int							iErr			=	-1;
	QMC_DMO					*	pDmo			=	(  QMC_DMO  *  )pDmoInfo->pDmo;
    HRESULT						hr				=	S_OK;
    DWORD						dwStatus		=	0;
    ULONG						ulSize			=	0;
    BYTE					*	pOut			=	0;

    DMO_OUTPUT_DATA_BUFFER		dataBufferStruct;

	//  BOOL						bProcessed		=	FALSE;
	int							index			=	0;
	
	MY_DEBUG_STEP				tmpDebugStep;		//  2009/10/15
	if  (  !pDebugStep  )  pDebugStep  =  &tmpDebugStep;

	//
	CMediaBuffer_new	outputBuffer;	//  s[mycountof(  pDmo->outs  )];

	//  int  i;	//  这里是防止被其他的处理函数先调用addRef,再调用release时,被自动删除
	outputBuffer.AddRef(  );
	

	index  =  0;
    //process until no more data
    if  (  SUCCEEDED(  hr  )  ) do {
	
		MACRO_setMyStep(  *pDebugStep,  70  );

		if  (  index  <  0  ||  index  >=  mycountof(  pDmo->outs  )  )  {
			traceLogA(  (char*)  "dmoProcessOutputs failed. pOutputBuffers_index error"  );
			pDebugStep->nErrs_pOutputBuffers_index  ++  ;
			goto  errLabel;
		}

		try  {

#if  0
			if  (  pDmo->pOutputBuffer  )  {
				//  traceLogA(  (char*)  "dmoProcessOutputs failed: pOutputs[%d] is not null before createBuffer",  index  );
				//  goto  errLabel;
				hr  =  pDmo->pOutputBuffer->SetLength(  0  );
				}
			else  {
				  hr = CreateBuffer(  pDmoInfo->cbOutputBuffer,  &pDmo->pOutputBuffer );
				  if  (  FAILED( hr ) ) goto  errLabel;
			}
#endif
			if  (  !pDmo->outs[index].pBuf  )  {
				pDmo->outs[index].pBuf  =  (  BYTE  *  )mymalloc(  pDmoInfo->cbOutputBuffer  );
				if  (  !pDmo->outs[index].pBuf  )  goto  errLabel;
			}

			//
			outputBuffer.set_Buffer(  pDmo->outs[index].pBuf,  pDmoInfo->cbOutputBuffer,  0  );
			
			//
			MACRO_setMyStep(  *pDebugStep,  72  );

			memset(  &dataBufferStruct,  0,  sizeof(  dataBufferStruct  )  );
			dataBufferStruct.pBuffer  =  &outputBuffer;	//  pDmo->pOutputBuffer;

			DWORD  dwTickCnt_0  =  GetTickCount(  );
	        hr = pDmo->m_pObject->ProcessOutput(  DMO_PROCESS_OUTPUT_DISCARD_WHEN_NO_BUFFER,
                                        1, //output buffer count
                                        &dataBufferStruct,
                                        &dwStatus );
			DWORD  dwTickCnt_1  =  GetTickCount(  );
			int  iDiffInMs  =  dwTickCnt_1  -  dwTickCnt_0;
			if  (  0  )  {				
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dmoProcessOutputs, elapse_processOutput %dms"  ),  iDiffInMs  );
			}
			if  (  iDiffInMs  >  1000  )  {
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dmoProcessOutputs failed, elapse_processOutput %dms"  ),  iDiffInMs  );
				goto  errLabel;
			}

			}
#ifdef  __useMfc__
		catch  (  CException  *  e  )  {
			   e->Delete(  );
			   goto  errLabel;
		}
#endif
		catch  (  ...  )  {
			   goto  errLabel;
		}

		if  (  FAILED(  hr  )  )  {
			traceLogA(  (char*)  "processOutputs: ProcessOutput failed"  );
			pDebugStep->nErrs_ProcessOutput  ++  ;
			goto  errLabel;
		}
		if  (  hr  ==  S_FALSE  )  {
			//  traceLogA(  (char*)  "dmoProcessOutputs: no output"  );
			break;
		}
		
		MACRO_setMyStep(  *pDebugStep,  74  );

        if( SUCCEEDED(hr) && (hr != S_FALSE) ) {
            hr = dataBufferStruct.pBuffer->GetBufferAndLength(&pOut, &ulSize);
			if  (  FAILED(  hr  )  )  {
				traceLogA(  (char*)  "processOutputs: GetBufferAndLength failed"  );
				goto  errLabel;
			}

			pDmo->outs[index].len  =  min(  pDmoInfo->cbOutputBuffer,  ulSize  );
			//  CopyMemory(pDmo->outs[index].pBuf, pOut, pDmo->outs[index].len);

			if  (  dataBufferStruct.dwStatus  &  DMO_OUTPUT_DATA_BUFFERF_TIME  )  pDmo->outs[index].rtStart  =  dataBufferStruct.rtTimestamp;
			if  (  dataBufferStruct.dwStatus  &  DMO_OUTPUT_DATA_BUFFERF_TIMELENGTH  )  pDmo->outs[index].rtTimeLen  =  dataBufferStruct.rtTimelength;

			//  bProcessed  =  TRUE;
        }

		index  ++  ;

    } while ( dataBufferStruct.dwStatus & DMO_OUTPUT_DATA_BUFFERF_INCOMPLETE );


	//
    //  Send Discontinuity on output stream
    //  hr = pDmo->m_pObject->Discontinuity( 0 );
    //  if ( FAILED( hr ) ) {
	//     return hr;
    //   }
	//

	iErr  =  0;

errLabel:

	if  (  !iErr  )  {

	}
	if  (  iErr  )  {	
		traceLogA(  (char*)  "dmoProcessOutputs failed."  );
		freeDmoOutputs(  pDmoInfo  );
	}

	return  iErr;
}






 int  compressVideo_dmo(  MY_DMO_INFO  *  pDmoInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput  )
{
		int					iErr			=	-1;
		if  (  !pDmoInfo  )  return  -1;
		QMC_DMO  *  pDmo  =  (  QMC_DMO  *  )pDmoInfo->pDmo;
		if  (  !pDmo  )  {
			traceLogA(  (char*)  "dmoCompressVideo failed: pDmo is null"  );
			return  -1;
		}

#if  10
		if  (  pDmoInfo->inputForEnc.pBuf  )  {
			if  (  pDmoInfo->inputForEnc.vh_decompress_real.bih.biCompression  !=  CONST_fourcc_YUY2  )  {
				traceLog((TCHAR*)  _T(  "dmoCompressVideo failed: biCompression error"  )  );
				return  -1;
			}
			rgb24ToYuy2(  pInput,  (  unsigned  char  *  )pDmoInfo->inputForEnc.pBuf,  pBmpInfo_input->bmiHeader.biWidth,  pBmpInfo_input->bmiHeader.biHeight  );
			//
			pBmpInfo_input  =  (  BITMAPINFO  *  )&pDmoInfo->inputForEnc.vh_decompress_real.bih;
			pInput  =  (  BYTE  *  )pDmoInfo->inputForEnc.pBuf;
		}
#endif

        const REFERENCE_TIME		rtStart			=	0;
        const REFERENCE_TIME		rtStop			=	0;
        BYTE					*	pBuffer			=	NULL;
        DWORD						dwLength;
		HRESULT						hr;

		//  MACRO_safeRelease(  pDmo->pInputBuffer  );
		//  freeDmoOutputs(  pDmoInfo  );

		try  {

		DWORD	dwFlags	=	0;
		hr  =  pDmo->m_pObject->GetInputStatus(  0,  &dwFlags  );
		if  (  FAILED(  hr  )  )  goto  errLabel;

		if  (  dwFlags  &  DMO_INPUT_STATUSF_ACCEPT_DATA  )  {

			if  (  !pDmo->pInputBuffer  )  {
				hr = CreateBuffer(  pDmoInfo->cbInputBuffer, &pDmo->pInputBuffer  );
				if  (  FAILED(  hr  )  )  goto  errLabel;
				}
			else  {
				  hr  =  pDmo->pInputBuffer->SetLength(  0  );
				  if  (  FAILED(  hr  )  )  goto  errLabel;
			}

			if  (  pBmpInfo_input->bmiHeader.biSizeImage  >  pDmo->pInputBuffer->m_cbMaxLength  )  {
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dmoCompressVideo failed: biSizeImage %d > cbMaxLength %d"  ),  pBmpInfo_input->bmiHeader.biSizeImage,  pDmo->pInputBuffer->m_cbMaxLength  );
				goto  errLabel;
			}
        
			hr  =  pDmo->pInputBuffer->GetBufferAndLength( &pBuffer, &dwLength );
			if  (  FAILED(  hr  )  )  goto  errLabel;

			CopyMemory(  pBuffer,  pInput,  pBmpInfo_input->bmiHeader.biSizeImage  );

			hr  =  pDmo->pInputBuffer->SetLength(  pBmpInfo_input->bmiHeader.biSizeImage  );
			if  (  FAILED(  hr  )  )  goto  errLabel;
        
			// call processInput
			hr  =  pDmo->m_pObject->ProcessInput( 0,
                                pDmo->pInputBuffer,
                                DMO_INPUT_DATA_BUFFERF_SYNCPOINT,
                                rtStart,
                                rtStop - rtStart);

			//  2012/03/19
			MACRO_safeRelease(  pDmo->pInputBuffer  );

			//
			if  (  hr  ==  DMO_E_NOTACCEPTING  )  traceLogA(  (char*)  "dmoCompressVideo: processInput: not accepting."  );
			else  if  (  FAILED(  hr  )  )  {
					  traceLogA(  (char*)  "dmoCompressVideo: ProcessInput failed."  );
					  goto  errLabel;
					  }
			else  if  (  S_FALSE  ==  hr  )  {
					  traceLogA(  (char*)  "dmoCompressvideo: noData"  );
					  iErr  =  0;  goto  errLabel;				  
			}
		}

		}
#ifdef  __useMfc__
		catch  (  CException  *  e  )  {
			e->Delete(  );
			goto  errLabel;
		}
#endif
		catch  (  ...  )  {
			goto  errLabel;
		}

		//  
		/*
		if  (  dmoProcessOutputs(  pDmo,  (  BYTE  *  )pCompressBuf, pVh_compress->bih.biSizeImage  )  )  {
			traceLogA(  (char*)  "dmoCompressVideo: processOutputs failed"  );
			goto  errLabel;
		}
		*/
		if  (  dmoProcessOutputs(  pDmoInfo  )  )  {
			traceLogA(  (char*)  "dmoCompressVideo: processOutputs failed"  );
			goto  errLabel;
		}

		//  if  (  pCompressBuf  )  {
		//		if  (  getDmoOutputByIndex(  pDmoInfo,  0,  pCompressBuf,  (  unsigned  int  *  )&pVh_compress->bih.biSizeImage,  NULL,  NULL  )  )  goto  errLabel;
		//  }
				
		iErr  =  0;

errLabel:

		if  (  iErr  )  {				
			traceLogA(  (char*)  "dmoCompressVideo failed"  );
			MACRO_safeRelease(  pDmo->pInputBuffer  );
			freeDmoOutputs(  pDmoInfo  );
		}

		return  iErr;
}


 //////////////////////////////////
#if  0
#define		CONST_mutexName_decVideo_dmo	_T(  "qDecVDmo"  )
#endif


 //  
 int  initDecompressVideo_dmo(  const  VIDEO_COMPRESSOR_CFG  *  pCompressor,  QY_VIDEO_HEADER  *  pVh_compress,  QY_VIDEO_HEADER  *  pVh_decompress,  MY_DEBUG_STEP  *  pDebugStep,  MY_DMO_INFO  *  pDmoInfo  )
{
	 int					iErr	=	-1;

	 if  (  !pDmoInfo  )  return  -1;
	 if  (  pDmoInfo->pDmo  )  return  -1;

	 //  2012/03/23.
#if  0
	 CQySyncObj	syncObj;
	 if  (  syncObj.sync(  CONST_mutexName_decVideo_dmo,  1000  )  )  return  -1;
#endif


	 //
	 MY_DEBUG_STEP			tmpDebugStep;
	 if  (  !pDebugStep  )  {		//  2012/03/19
		 memset(  &tmpDebugStep,  0,  sizeof(  tmpDebugStep  )  );
		 pDebugStep  =  &tmpDebugStep;
	 }

	 //  2012/03/19
	 MACRO_setMyStep(  *pDebugStep,  34  );

	 //
	 QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();
	 DYN_LIB_DX			*	pDynLib	=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	 GUID					clsid;
	 GUID					clsid_mInSubType;
	 DWORD					dwTag;
	 BOOL					bWmv	=	FALSE;
	 int					iWidth	=	pVh_decompress->bih.biWidth;
	 int					iHeight	=	pVh_decompress->bih.biHeight;
	 MY_DMO_INFO			myDmoInfo;
	 QMC_DMO			*	pDmo	=	NULL;
	 //  VideoDecParams			VideoParams;
	 TCHAR					tHintBuf[128]	=	_T(  ""  );

	 DMO_MEDIA_TYPE			mIn;
	 DMO_MEDIA_TYPE			mOut;
	 memset(  &mIn,  0, sizeof(  mIn  )  );
	 memset(  &mOut,  0,  sizeof(  mOut  )  );


	 memset(  &myDmoInfo,  0,  sizeof(  myDmoInfo  )  );
	 pDmo  =  (  QMC_DMO  *  )mymalloc(  sizeof(  QMC_DMO  )  );
	 if  (  !pDmo  )  goto  errLabel;
	 memset(  pDmo,  0,  sizeof(  QMC_DMO  )  );
	 myDmoInfo.pDmo  =  pDmo;

	 
	 try  {

	 //  CLSID_CWMVEncMediaObject2;
	 /*
	 clsid  =  CLSID_MSScreen9_Encoder_DMO;
	 clsid_mOutSubType  =  WMCMEDIASUBTYPE_MSS2;
	 dwTag  =  WMCFOURCC_MSS2;
	 bWmv  =  FALSE;
	 */
	 /*
	 clsid  =  CLSID_WMVideo_Decoder_DMO;
	 clsid_mInSubType  =  WMCMEDIASUBTYPE_WMV3;
	 dwTag  =  WMCFOURCC_WMV3;
	 bWmv  =  TRUE;
	 */

	 dwTag  =  fourccStr2i(  pCompressor->common.fourccStr  );
	 clsid_mInSubType  =  FOURCCMap(  dwTag  );
	 if  (  getDmoInfoBySth(  pQyMc,  pDynLib,  &DMOCATEGORY_VIDEO_DECODER,  NULL,  &clsid_mInSubType,  NULL,  NULL,  NULL,  &clsid,  NULL  )  )  goto  errLabel;

	 switch  (  dwTag  )  {
			 case  WMCFOURCC_WMV1:
			 case  WMCFOURCC_WMV2:
			 case  WMCFOURCC_WMV3:
			 case  WMCFOURCC_WMVP:
				   bWmv  =  TRUE;
				   break;
			 default:
					 bWmv  =  FALSE;
					 break;
	 }





	 //  SetEncodingDefaults(  encParams,  NULL, dwTag,  bWmv  );
	 


    // create DMO
    HRESULT hr = CoCreateInstance( clsid,
                         NULL,
                         CLSCTX_INPROC,
                         IID_IMediaObject,
                         (void **) &pDmo->m_pObject);
    if ( FAILED( hr ) ){
		traceLogA(  (char*) ("Can't create this DMO.") );
        //  return hr;
		goto  errLabel;
    }


	//  2012/03/19
	 MACRO_setMyStep(  *pDebugStep,  35  );


	/*
	DWORD  cInput  =  0,  cOutput  =  0;
	hr  =  m_pObject->GetStreamCount(  &cInput,  &cOutput  );

	DMO_MEDIA_TYPE		mt;
	DWORD				dwType  =  0;
	TCHAR				tBuf[256];
	char				fourccStr[16];
	int					i;

	while  (  hr  =  m_pObject->GetInputType(  0,  dwType,  &mt  ),  SUCCEEDED(  hr  )  )  {

			StringFromGUID2(  mt.subtype,  tBuf,  mycountof(  tBuf  )  );
			iFourcc2Str(  mt.subtype.Data1,  fourccStr,  mycountof(  fourccStr  )  );

			traceLogA(  (char*)  "inputType %d:%S, %S, fourccStr %s",  dwType,  tBuf,  getMediaSubtypeName(  mt.subtype  ),  fourccStr  );
						

			pDynLib->pMoFreeMediaType(  &mt  );
			dwType  ++  ;
	}

	for  (  i  =  0;  i  <  cOutput;  i  ++  )  {
		dwType  =  0;
		while  (  hr  =  m_pObject->GetOutputType(  i,  dwType,  &mt  ),  SUCCEEDED(  hr  )  )  {

				StringFromGUID2(  mt.subtype,  tBuf,  mycountof(  tBuf  )  );
				iFourcc2Str(  mt.subtype.Data1,  fourccStr,  mycountof(  fourccStr  )  );

				traceLogA(  (char*)  "outputType ( %d,%d ): %S, %S,  fourccStr %s",  i,  dwType,  tBuf,  getMediaSubtypeName(  mt.subtype  ),  fourccStr  );
						
				pDynLib->pMoFreeMediaType(  &mt  );

				dwType  ++  ;
		}
	}
	*/


	hr  =  pDynLib->pMoInitMediaType(  &mIn,  sizeof(  VIDEOINFOHEADER  )  +  pVh_compress->bih.biSize  -  sizeof(  BITMAPINFOHEADER  )  );
	if  (  FAILED(  hr  )  )  goto  errLabel;
	mIn.majortype  =  MEDIATYPE_Video;
	mIn.subtype  =  clsid_mInSubType;
	mIn.formattype  =  FORMAT_VideoInfo;	
	VIDEOINFOHEADER  *  pViho;	pViho  =  (  VIDEOINFOHEADER  *  )mIn.pbFormat;
	memcpy(  &pViho->bmiHeader,  &pVh_compress->bih,  pVh_compress->bih.biSize  );

	hr  =  pDynLib->pMoInitMediaType(  &mOut,  sizeof(  VIDEOINFOHEADER  )  );
	if  (  FAILED(  hr  )  )  goto  errLabel;

	mOut.majortype  =  MEDIATYPE_Video;
	mOut.subtype  =  MEDIASUBTYPE_RGB24;
	mOut.formattype  =  FORMAT_VideoInfo;
	mOut.lSampleSize  =  1;
	VIDEOINFOHEADER  *  pvihi  =  (  VIDEOINFOHEADER  *  )mOut.pbFormat;
	memset(  pvihi,  0,  sizeof(  VIDEOINFOHEADER  )  );
	pvihi->AvgTimePerFrame	=	DEFAULT_AvgTimePerFrame;	//  1000000;
	makeBmpInfoHeader_rgb(  24,  iWidth,  iHeight,  &pvihi->bmiHeader  );

	//  int  len  =  sizeof(  VIDEOINFOHEADER  );


	//  2012/03/19
	MACRO_setMyStep(  *pDebugStep,  36  );


	//
	hr  =  pDmo->m_pObject->SetInputType(  0,  &mIn,  0  );
	if  (  hr  )  {
		safeTcsnCpy(  _T(  "dmo.SetInputType failed"  ),  tHintBuf,  mycountof(  tHintBuf  )  );
		goto  errLabel;
	}

	/*
	if  (  configureDMO_enc(  encParams,  m_pObject,  (  AM_MEDIA_TYPE  *  )&mIn,  (  AM_MEDIA_TYPE  *  )&mOut  )  )  {
		traceLogA(  (char*)  "ConfigureDMO failed."  );
		return  -1;
	}
	traceLogA(  (char*)  "ConfigureDMO ok"  );
	*/

	hr  =  pDmo->m_pObject->SetOutputType(  0,  &mOut,  0  );
	if  (  FAILED(  hr  )  )  goto  errLabel;


	//  2012/03/19
	MACRO_setMyStep(  *pDebugStep,  37  );


	DWORD  cbIn,  cbOut,  dwDummy;
	//     
	hr  =  pDmo->m_pObject->GetInputSizeInfo( 0, &cbIn, &dwDummy, &dwDummy);
    if  (  FAILED(  hr  )  )  {
		traceLogA(  (char*)  "Failed GetInputSizeInfo"  );
		goto  errLabel;
    }
    
	hr = pDmo->m_pObject->GetOutputSizeInfo( 0, &cbOut, &dwDummy);
    if  (  FAILED(  hr  )  )  {
		traceLogA(  (char*)  "Failed GetOutputSizeInfo"  );
		goto  errLabel;
    }

	if  (  pVh_compress->bih.biSizeImage  <  cbIn  )  pVh_compress->bih.biSizeImage  =  cbIn;

	if  (  pVh_decompress->bih.biSizeImage  <  cbOut  )  {
		traceLogA(  (char*)  "initDmoDecompressVideo failed. biSizeImage < cbIn"  );
		goto  errLabel;
	}

	myDmoInfo.cbInputBuffer  =  pVh_compress->bih.biSizeImage;
	myDmoInfo.cbOutputBuffer  =  pVh_decompress->bih.biSizeImage;

	// create and fill CMediaBuffer
	//  hr  =  CreateBuffer(  pVh_compress->bih.biSizeImage, &pDmo->pInputBuffer  );
	//  if  (  FAILED(  hr  )  )  goto  errLabel;
	//  hr  =  CreateBuffer(  pVh_decompress->bih.biSizeImage,  &pDmo->pOutputBuffer  );
	//  if  (  FAILED(  hr  )  )  goto  errLabel;
	
	}
#ifdef  __useMfc__
	catch  (  CException  *  e  )  {
			e->Delete(  );
			goto  errLabel;
	}
#endif
	catch  (  ...  )  {
		goto  errLabel;
	}


	iErr  =  0;

errLabel:


	//  2012/03/19
	MACRO_setMyStep(  *pDebugStep,  38  );

	//
	pDynLib->pMoFreeMediaType(  &mIn  );
	pDynLib->pMoFreeMediaType(  &mOut  );

	if  (  iErr  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initDecompressVideo_dmo failed: %s"  ),  tHintBuf  );

		//
		exitDecompressVideo_dmo(  &myDmoInfo  );	
	}
	if  (  !iErr  )  {
		//  pDmoInfo->pDmo  =  pDmo;
		memcpy(  pDmoInfo,  &myDmoInfo,  sizeof(  pDmoInfo[0]  )  );
	}


	//  2012/03/19
	MACRO_setMyStep(  *pDebugStep,  39  );


	 return  iErr;
}

 int  exitDecompressVideo_dmo(  MY_DMO_INFO  *  pDmoInfo  )
{
	traceLogA(  (char*)  "exitDmoDecompressVideo enters"  );

	if  (  !pDmoInfo  ||  !pDmoInfo->pDmo  )  return  0;
	QMC_DMO  *  pDmo  =  (  QMC_DMO  *  )pDmoInfo->pDmo;

	//  2012/03/23.
#if  0
	CQySyncObj	syncObj;
	if  (  syncObj.sync(  CONST_mutexName_decVideo_dmo,  INFINITE  )  )  {
		//  这里绝不能失败
		qyExitProcess(  _T(  "Serious err, exitDecompressVideo_dmo sync failed"  )  );
		return  -1;
	}
#endif


	if  (  pDmo  )  {
		freeDmoOutputs(  pDmoInfo  );
		MACRO_safeRelease(  pDmo->pInputBuffer  );

		//  2012/03/18
		HRESULT		hr;
		if  (  pDmo->m_pObject  )  {
			try  {
				//  Send Discontinuity on output stream
				hr = pDmo->m_pObject->Discontinuity( 0 );
				if ( FAILED( hr ) ) {
				}
				}
#ifdef  __useMfc__
			catch  (  CException  *  e  )  {
				e->Delete(  );
			}
#endif
			catch  (  ...  )  {
			}
		}

		//
		MACRO_safeRelease(  pDmo->m_pObject  );
	}
	MACRO_safeFree(  pDmo  );

	pDmoInfo->pDmo  =  NULL;

	traceLogA(  (char*)  "exitDmoDecompressVideo leaves"  );

	return  0;
}

  int  decompressVideo_dmo(  MY_DMO_INFO  *  pDmoInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  )
{
		int					iErr			=	-1;
		if  (  !pDmoInfo  )  return  -1;
		if  (  !pDmoInfo->pDmo  )  {
			traceLogA(  (char*)  "dmoDecomprss failed: pDmo is null"  );
			return  -1;
		}
		MY_DEBUG_STEP  *  pDebugStep	=	(  MY_DEBUG_STEP  *  )pDmoInfo->pDebugStep;		
#if  0		//  temporarily.  2010/04/28
		MY_DEBUG_STEP	tmp;
		pDebugStep  =  &tmp;
#endif
		if  (  !pDebugStep  )  return  -1;

		QMC_DMO  *  pDmo  =  (  QMC_DMO  *  )pDmoInfo->pDmo;

        const REFERENCE_TIME		rtStart			=	0;
        const REFERENCE_TIME		rtStop			=	0;
        BYTE					*	pBuffer			=	NULL;
        DWORD						dwLength;
		HRESULT						hr;

		MACRO_setMyStep(  *pDebugStep,  62  );	//  2009/10/15

		//  MACRO_safeRelease(  pDmo->pInputBuffer  );
		//  freeDmoOutputs(  pDmoInfo  );

		MACRO_setMyStep(  *pDebugStep,  64  );	//  2009/10/15


		try  {

			DWORD	dwFlags	=	0;
			hr  =  pDmo->m_pObject->GetInputStatus(  0,  &dwFlags  );
			if  (  FAILED(  hr  )  )  goto  errLabel;

			//  2012/03/20
#if  0
			if  (  !(  dwFlags  &  DMO_INPUT_STATUSF_ACCEPT_DATA  )  )  {
				goto  errLabel;
			}
#endif

			//
			if  (  dwFlags  &  DMO_INPUT_STATUSF_ACCEPT_DATA  )  {


				if  (  !pDmo->pInputBuffer  )  {
					hr = CreateBuffer(  pDmoInfo->cbInputBuffer, &pDmo->pInputBuffer  );
					if  (  FAILED(  hr  )  )  goto  errLabel;
					}
				else  {
					  hr  =  pDmo->pInputBuffer->SetLength(  0  );
					  if  (  FAILED(  hr  )  )  goto  errLabel;
				}

				if  (  pBmpInfo_input->bmiHeader.biSizeImage  >  pDmo->pInputBuffer->m_cbMaxLength  )  {
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dmoDecompressVideo failed: biSizeImage %d > cbMaxLength %d"  ),  pBmpInfo_input->bmiHeader.biSizeImage,  pDmo->pInputBuffer->m_cbMaxLength  );
					goto  errLabel;
				}
        
				hr = pDmo->pInputBuffer->GetBufferAndLength( &pBuffer, &dwLength );
				if( FAILED( hr ) )  goto  errLabel;

				CopyMemory(  pBuffer,  pInput,  pBmpInfo_input->bmiHeader.biSizeImage  );

				hr = pDmo->pInputBuffer->SetLength(  pBmpInfo_input->bmiHeader.biSizeImage  );
				if( FAILED( hr ) )  goto  errLabel;
        
				MACRO_setMyStep(  *pDebugStep,  66  );	//  2009/10/15

				DWORD	dwTickCnt_0	=	GetTickCount(  );

				 // call processInput
				 hr = pDmo->m_pObject->ProcessInput( 0,
                                pDmo->pInputBuffer,
                                DMO_INPUT_DATA_BUFFERF_SYNCPOINT,
                                rtStart,
                                rtStop - rtStart);

				 DWORD	dwTickCnt_1	=	GetTickCount(  );
				 int  iDiffInMs  =  dwTickCnt_1  -  dwTickCnt_0;
				 //
				 if  (  0  )  {
					 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dmoDecompressVideo, elapse_processInput %dms"  ),  iDiffInMs  );
				 }
				 if  (  iDiffInMs  >  1000  )  {
					 //
					 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dmoDecompressVideo failed, elapse_processInput %dms"  ),  iDiffInMs  );
					 goto  errLabel;
				 }


				 //  2012/03/19
				 MACRO_safeRelease(  pDmo->pInputBuffer  );


				//
				if  (  hr  ==  DMO_E_NOTACCEPTING  )  {
					#ifdef  __DEBUG__
							traceLogA(  (char*)  "dmoDecompressVideo: processInput: not accepting"  );
					#endif
					pDebugStep->uiCnt_DMO_E_NOTACCEPTING  ++  ;
					}
				else  if  (  FAILED(  hr  )  )  {
						  pDebugStep->nErrs_ProcessInput  ++  ;					
						  goto  errLabel;
						  }
				else  if  (  S_FALSE  ==  hr  )  {
						  #ifdef  __DEBUG__
								  traceLogA(  (char*)  "dmoDecompressVideo: no output"  );
						  #endif
					      iErr  =  0;  goto  errLabel;	
				}

				
			}

			
			}
#ifdef  __useMfc__
		catch  (  CException  *  e  )  {
			   e->Delete(  );
			   goto  errLabel;
		}
#endif
		catch  (  ...  )  {
			   goto  errLabel;
		}


		MACRO_setMyStep(  *pDebugStep,  67  );	//  2009/10/15

		//  
		/*
		if  (  dmoProcessOutputs(  pDmo,  (  BYTE  *  )pDecompressBuf,  pVh_decompress->bih.biSizeImage  )  )  {
			traceLogA(  (char*)  "dmoDecompressVideo: processOutputs failed"  );
			goto  errLabel;
		}
		*/
		if  (  dmoProcessOutputs(  pDmoInfo,  pDebugStep  )  )  {
			#ifdef  __DEBUG__
					traceLogA(  (char*)  "dmoDecompressVideo: processOutputs failed"  );
			#endif
			goto  errLabel;
		}

		//  if  (  getDmoOutputByIndex(  pDmoInfo,  0,  pDecompressBuf,  (  unsigned  int  *  )&pVh_decompress->bih.biSizeImage,  NULL,  NULL  )  )  goto  errLabel;
				
		iErr  =  0;

errLabel:

		MACRO_setMyStep(  *pDebugStep,  168  );	//  2009/10/15

		if  (  iErr  )  {
			#ifdef  __DEBUG__
					traceLogA(  (char*)  "dmoDecompressVideo failed"  );
			#endif
			MACRO_safeRelease(  pDmo->pInputBuffer  );
			freeDmoOutputs(  pDmoInfo  );
		}

		MACRO_setMyStep(  *pDebugStep,  169  );	//  2009/10/15

		return  iErr;
}


 //  2012/03/20
 int  startCapture_filterGraph(  void  *  pQmcFilterGraphParam,  void  *  pDebugStepParam  )
{
	int						iErr	=	-1;
	HRESULT					hr;
	QMC_FILTER_GRAPH  *  p		=	(  QMC_FILTER_GRAPH  *  )pQmcFilterGraphParam;
	if  (  !p  )  return  -1;
	MY_DEBUG_STEP		*	pDebugStep	=	(  MY_DEBUG_STEP  *  )pDebugStepParam;

	//
	M_setMyStep(  pDebugStep,  45  );

	//
	if  (  !p->m_captureGraphBuilder.bInited  )  return  -1;

	//
	M_setMyStep(  pDebugStep,  46  );

	OAFilterState  fs;
	hr  =  p->m_captureGraphBuilder.m_pMC->GetState(  1000,  &fs  );
	if  (  pDebugStep  )  {
		pDebugStep->fg.hr_GetState_beforeStart  =  hr;
		pDebugStep->fg.fs_beforeStart  =  fs;
		
		#ifdef  __DEBUG__
				int  kk  =  VFW_S_STATE_INTERMEDIATE;
				kk  =  S_FALSE;
		#endif
				
		//
		pDebugStep->fg.bBeforeRun  =  TRUE;
	}


	//
	hr  =  p->m_captureGraphBuilder.m_pMC->Run(  );
	p->m_captureGraphBuilder.bCalled_Run  =  TRUE;		//  这里表明Run调用过了. 2012/03/22
	//
	if  (  pDebugStep  )  {
		pDebugStep->fg.hr_run  =  hr;
	}
	//
	if  (  FAILED(  hr  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;
}







