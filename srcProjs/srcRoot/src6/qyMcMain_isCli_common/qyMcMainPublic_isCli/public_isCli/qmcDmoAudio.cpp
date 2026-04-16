

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
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
#include	"qmcVideoCapture_isCli.h"
#ifndef  __WINCE__
	#include	"qmcVideoCapture_dx.h"
#endif

#include	"qyDynLib.h"

#include	"mywmcodecconst.h"
#include	"mywmcodeciface.h"
#include	"myfourcc.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"

#include	"qyMcMainRealTimeMediaProc.h"
#include	"myfourcc.h"

#include	"funcsForIsCliHelp.h"



 void  setEncodingDefaults_audio(  DWORD  dwTag,  WORD  nChannels,  DWORD  nSamplesPerSec,  WORD  wBitsPerSample,  DWORD  nAvgBytesPerSec,  AUDIO_ENC_PARAMS  *  pParams  )
 {	 
	 return;
 }

 HRESULT SetAudioParams_enc( IMediaObject *pDMO, AUDIO_ENC_PARAMS *pParams )
 {
	 return  S_OK;
 }


 HRESULT MakeAudioOutputType(IMediaObject   *pDMO,    
                            AM_MEDIA_TYPE  *pmtIn,   
                            AUDIO_ENC_PARAMS *pParams, 
                            AM_MEDIA_TYPE  *pmt      ) 
{
    
    HRESULT             hr                   = -1;
	QY_AUDIO_HEADER		ah;
	DWORD               cbPrivateData        = 0;
    BYTE                *pNewFormat          = NULL;
    
    if( pDMO == NULL || pmtIn == NULL || pParams == NULL || pmt == NULL )
        return E_INVALIDARG;
    
    if( pmtIn->pbFormat == NULL || pmtIn->cbFormat <= 0 )
        return E_INVALIDARG;
    
	if  (  !pParams->pAh  )  return  -1;

	if( pmtIn->formattype == FORMAT_WaveFormatEx ){
		ah.wfx = *(WAVEFORMATEX*)pmtIn->pbFormat; 
		} 
	else
        return -1;

	memcpy(  &ah,  pParams->pAh,  sizeof(  ah  )  );

    // make up a partial media type
    pmt->majortype            = MEDIATYPE_Audio;
	pmt->subtype  =  FOURCCMap(  ah.wfx.wFormatTag  );
    pmt->formattype           = FORMAT_WaveFormatEx;
	pmt->bFixedSizeSamples  =  TRUE;
    pmt->bTemporalCompression = FALSE;
	pmt->lSampleSize  =  ah.wfx.nBlockAlign;

	//
    //use the fake format above to get the private data
    pmt->pbFormat = (BYTE*)&ah.wfx;
    pmt->cbFormat = sizeof( ah.wfx );
    pmt->pUnk = NULL;
    
	cbPrivateData  =  ah.wfx.cbSize;
    
    //modify the media type accordingly
    pNewFormat = (BYTE*)CoTaskMemAlloc( sizeof( WAVEFORMATEX) + cbPrivateData );
    if( pNewFormat == NULL )  goto  errLabel;
	
    memcpy( pNewFormat, pmt->pbFormat, sizeof( WAVEFORMATEX)  +  cbPrivateData  );
    
    pmt->pbFormat = pNewFormat;
    pmt->cbFormat = sizeof( WAVEFORMATEX) + cbPrivateData;
    
	hr  =  S_OK;

errLabel:

	if  (  hr  !=  S_OK  )  {
		if  (  pNewFormat  )  CoTaskMemFree(  pNewFormat  );
		memset(  pmt,  0,  sizeof(  pmt[0]  )  );
	}


    return  hr;
}


  int setAudioTypes_enc( IMediaObject   *pDMO,    \
                      AM_MEDIA_TYPE  *pmtIn,   \
                      AUDIO_ENC_PARAMS *pParams, \
                      AM_MEDIA_TYPE  *pmtOut,  \
                      DWORD *pcbIn,            \
                      DWORD *pcbOut )
{
	int		iErr	=	-1;
    HRESULT hr;
    DWORD   dwDummy;
    
    //Now we can make the output type...
    hr = MakeAudioOutputType( pDMO, pmtIn, pParams, pmtOut );
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




  int  initializeAudioEncoder(  AM_MEDIA_TYPE *pmtInput, 
                               AUDIO_ENC_PARAMS *pParams, 
                               IMediaObject   *pDMO,  
                               AM_MEDIA_TYPE  *pmtOutput  )
 {
	int			  iErr				=	-1;
    HRESULT       hr;
    DWORD         cbInputBuffer		=	0;
    DWORD         cbOutputBuffer	=	0;
    
    if( pmtInput == NULL || pParams == NULL || pDMO == NULL )  return  -1;
	    
    hr = SetAudioParams_enc( pDMO, pParams );
	if  (  FAILED(  hr  )  )  goto  errLabel;
    	
	// cbInputBuffer and cbOutputBuffer are actually not used here.
	if  (  setAudioTypes_enc( pDMO, pmtInput, pParams, pmtOutput, &cbInputBuffer, &cbOutputBuffer )  )  goto  errLabel;
    
	/*
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
	*/


	iErr  =  0;
errLabel:
    return  iErr;     
}


 int  configureDMO_enc_audio(   AUDIO_ENC_PARAMS  *  pEncParams,  IMediaObject* pDMO, AM_MEDIA_TYPE* pmtIn, AM_MEDIA_TYPE* pmtOut)
{
	int		iErr	=	-1;
    HRESULT hr		=  E_FAIL;

    if  (  FORMAT_WaveFormatEx  ==  pmtIn->formattype  ) {
        if  (  initializeAudioEncoder( pmtIn, pEncParams, pDMO, pmtOut )  )  goto  errLabel;
		}
	else  
		goto  errLabel;
		  
	iErr  =  0;
errLabel:    
    return  iErr;
}


  int  initCompressAudio_dmo(  QY_MC  *  pQyMc,  AUDIO_COMPRESSOR_CFG  *  pCompressor,  QY_AUDIO_HEADER  *  pAh_decompress,  QY_AUDIO_HEADER  *  pAh_compress,  MY_DMO_INFO  *  pDmoInfo  )
 {
	 int			iErr					=	-1;
	 //
	 traceLogA(  (char*)  "initDmoCompressAudio enters"  );

	 if  (  !pDmoInfo  )  return  -1;
	 if  (  pDmoInfo->pDmo  )  return  -1;
	 //
	 //QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	 DYN_LIB_DX			*	pDynLib			=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	 GUID					clsid;

	 MY_DMO_INFO			myDmoInfo;
	 QMC_DMO			*	pDmo			=	NULL;

	 DMO_MEDIA_TYPE			mIn;
	 BOOL					bInited_mIn		=	FALSE;
	 DMO_MEDIA_TYPE			mOut;	
	 BOOL					bInited_mOut	=	FALSE;

	 AUDIO_ENC_PARAMS		params;
	 QY_AUDIO_HEADER		ah;

	 memset(  &myDmoInfo,  0,  sizeof(  myDmoInfo  )  );
	 pDmo  =  (  QMC_DMO  *  )mymalloc(  sizeof(  QMC_DMO  )  );
	 if  (  !pDmo  )  goto  errLabel;
	 memset(  pDmo,  0,  sizeof(  QMC_DMO  )  );
	 myDmoInfo.pDmo  =  pDmo;

	 if  (  !pCompressor->wf_compress.wFormatTag  )  {
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initDmoCompressAudio failed: compress.dwTag is 0"  )  );
		 goto  errLabel;
	 }
	 if  (  pAh_decompress->wfx.wFormatTag  !=  WAVE_FORMAT_PCM
		 ||  !pAh_decompress->wfx.nAvgBytesPerSec  )  
	 {
		 traceLogA(  (char*)  "initDmoCompressAudio failed: decompress error"  );
		 goto  errLabel;
	 }

	 memcpy(  &ah.wfx,  &pCompressor->wf_compress,  sizeof(  ah.wfx  )  );
	 if  (  getDmoInfoBySth(  pQyMc,  pDynLib,  &DMOCATEGORY_AUDIO_ENCODER,  NULL,  NULL,  NULL,  NULL,  &ah,  &clsid,  NULL  )  )  goto  errLabel;
	 

	 memcpy(  &params,  &pCompressor->params,  sizeof(  params  )  );
	 params.pAh  =  &ah;


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

	memset(  &mIn,  0, sizeof(  mIn  )  );
	hr  =  pDynLib->pMoInitMediaType(  &mIn,  sizeof(  WAVEFORMATEX  )  );
	if  (  FAILED(  hr  )  )  goto  errLabel;
	bInited_mIn  =  TRUE;

	memset(  &mOut,  0,  sizeof(  mOut  )  );
	bInited_mOut  =  TRUE;

	mIn.majortype  =  MEDIATYPE_Audio;
	mIn.subtype  =  MEDIASUBTYPE_PCM;
	mIn.formattype  =  FORMAT_WaveFormatEx;
	mIn.bFixedSizeSamples  =  1;
	mIn.bTemporalCompression  =  0;
	mIn.lSampleSize  =  pAh_decompress->wfx.nBlockAlign;
	WAVEFORMATEX  *  pwfx  =  (  WAVEFORMATEX  *  )mIn.pbFormat;
	*pwfx  =  pAh_decompress->wfx;


	hr  =  pDmo->m_pObject->SetInputType(  0,  &mIn,  0  );
	if  (  hr  )  goto  errLabel;
	
	if  (  configureDMO_enc_audio(  &params,  pDmo->m_pObject,  (  AM_MEDIA_TYPE  *  )&mIn,  (  AM_MEDIA_TYPE  *  )&mOut  )  )  {
		traceLogA(  (char*)  "ConfigureDMO failed."  );
		goto  errLabel;
	}
	traceLogA(  (char*)  "ConfigureDMO ok"  );

	DWORD  cbIn,  cbOut,  dwDummy;
	//     
	hr  =  pDmo->m_pObject->GetInputSizeInfo( 0, &cbIn, &dwDummy, &dwDummy);
    if  (  FAILED(  hr  )  )  {
		traceLogA(  (char*)  "Failed GetInputSizeInfo"  );
		goto  errLabel;
    }
	myDmoInfo.cbInputBuffer  =  max(  (  pAh_decompress->wfx.nAvgBytesPerSec  *  2  ),  cbIn  );
    
	hr = pDmo->m_pObject->GetOutputSizeInfo( 0, &cbOut, &dwDummy);
    if  (  FAILED(  hr  )  )  {
		traceLogA(  (char*)  "Failed GetOutputSizeInfo"  );
		goto  errLabel;
    }
	myDmoInfo.cbOutputBuffer  =  cbOut;


	if  (  mOut.formattype  ==  FORMAT_WaveFormatEx
		&&  mOut.cbFormat  >=  sizeof(  WAVEFORMATEX  )
			&&  mOut.pbFormat  )  
	{
		WAVEFORMATEX	*	pWfx  =  (  WAVEFORMATEX  *  )mOut.pbFormat;

		if  (  pWfx->cbSize  >  sizeof(  pAh_compress->bExtraData  )  )  {
			traceLogA(  (char*)  "initDmoCompressVideo failed: biSize > sizeof(  vh_compress ), %d",  pWfx->cbSize  );
			goto  errLabel;
		}
		memcpy(  &pAh_compress->wfx,  pWfx,  sizeof(  WAVEFORMATEX  )  +  pWfx->cbSize  );

		//
		}
	else  {
		  traceLogA(  (char*)  "initDmoCompressAudio: mOut format error"  );
		  goto  errLabel;
	}

	
	// create and fill CMediaBuffer
	hr = CreateBuffer(  myDmoInfo.cbInputBuffer, &pDmo->pInputBuffer  );
	if  (  FAILED(  hr  )  )  goto  errLabel;
	//  hr = CreateBuffer(  myDmoInfo.cbOutputBuffer,  &pDmo->pOutputBuffer );
	//  if  (  FAILED( hr ) ) goto  errLabel;

	iErr  =  0;

errLabel:

	if  (  bInited_mOut  )  pDynLib->pMoFreeMediaType(  &mOut  );
	if  (  bInited_mIn  )  pDynLib->pMoFreeMediaType(  &mIn  );
	
	if  (  iErr  )  {
		exitCompressAudio_dmo(  &myDmoInfo  );		
	}
	if  (  !iErr  )  {
		memcpy(  pDmoInfo,  &myDmoInfo,  sizeof(  pDmoInfo[0]  )  );
		#ifdef  __DEBUG__
				pDmoInfo->bAudio  =  TRUE;
		#endif
	}

	traceLogA(  (char*)  "initDmoCompressAudio leaves"  );

	return  iErr;
}


 int  exitCompressAudio_dmo(  MY_DMO_INFO  *  pDmoInfo  )
{

	traceLogA(  (char*)  "exitDmoCompressAudio enters"  );

	if  (  !pDmoInfo  )  return  0;
	if  (  !pDmoInfo->pDmo  )  return  0;
	QMC_DMO  *  pDmo  =  (  QMC_DMO  *  )pDmoInfo->pDmo;

	if  (  pDmo  )  {
 
		//  MACRO_safeRelease(  pDmo->pOutputBuffer  );
		freeDmoOutputs(  pDmoInfo  );
		MACRO_safeRelease(  pDmo->pInputBuffer  );


		//  2012/03/18
		HRESULT		hr;
		if  (  pDmo->m_pObject  )  {
			//  Send Discontinuity on output stream
			hr = pDmo->m_pObject->Discontinuity( 0 );
			if ( FAILED( hr ) ) {
			}
		}

		//
		MACRO_safeRelease(  pDmo->m_pObject  );
	}
	MACRO_safeFree(  pDmo  );

	pDmoInfo->pDmo  =  NULL;

	traceLogA(  (char*)  "exitDmoCompressAudio leaves"  );

	return  0;
}




 int  compressAudio_dmo(  MY_DMO_INFO  *  pDmoInfo,  QY_AUDIO_HEADER  *  pAh_decompress,  BYTE  *  pInput,  unsigned  int  uiInputLen,  int  iSampleTimeInMs  )
{
		int					iErr			=	-1;
		if  (  !pDmoInfo  )  return  -1;
		QMC_DMO  *  pDmo  =  (  QMC_DMO  *  )pDmoInfo->pDmo;
		if  (  !pDmo  )  {
			traceLogA(  (char*)  "dmoCompressVideo failed: pDmo is null"  );
			return  -1;
		}

        REFERENCE_TIME				rtStart			=	0;
        //  REFERENCE_TIME			rtStop			=	0;
		REFERENCE_TIME				rtTimeLen		=	0;	//  rtStop - rtStart
        BYTE					*	pBuffer			=	NULL;
        DWORD						dwLength;
		HRESULT						hr;

		//  MACRO_safeRelease(  pDmo->pInputBuffer  );
		//  freeDmoOutputs(  pDmoInfo  );

		DWORD	dwFlags	=	0;
		hr  =  pDmo->m_pObject->GetInputStatus(  0,  &dwFlags  );
		if  (  FAILED(  hr  )  )  goto  errLabel;

		if  (  dwFlags  &  DMO_INPUT_STATUSF_ACCEPT_DATA  )  {

			//  2009/05/26
			rtStart  =  (  REFERENCE_TIME  )(  pDmoInfo->ui64_total_inputBytes  *  1000.  *  1000  *  10 /  pAh_decompress->wfx.nAvgBytesPerSec  );
			rtTimeLen  =  (  REFERENCE_TIME  )(  uiInputLen  *  1000.  *  1000  *  10  /  pAh_decompress->wfx.nAvgBytesPerSec  );
			if  (  iSampleTimeInMs  &&  rtStart  )  {
				int  mySampleTimeInMs  =  (  int  )(  rtStart  /  (  1000.  *  10  )  );
				if  (  pDmoInfo->iDiffInMs_tStartStream  +  mySampleTimeInMs  !=  iSampleTimeInMs  )  {
					pDmoInfo->iDiffInMs_tStartStream  =  iSampleTimeInMs  -  mySampleTimeInMs;
					#ifdef  __DEBUG__
							//  traceLogA(  (char*)  "dmoCompressAudio: iDiffInMs_tStartAudio %d",  pDmoInfo->iDiffInMs_tStartAudio  );
					#endif
				}
			}
			pDmoInfo->ui64_total_inputBytes  +=  uiInputLen;

			//
			if  (  !pDmo->pInputBuffer  )  {
				hr = CreateBuffer(  pDmoInfo->cbInputBuffer, &pDmo->pInputBuffer  );
				if  (  FAILED(  hr  )  )  {
					traceLogA(  (char*)  "dmoCompressAudio: CreateBuffer failed."  );
					goto  errLabel;
				}
				}
			else  {
				  hr  =  pDmo->pInputBuffer->SetLength(  0  );
				  if  (  FAILED(  hr  )  )  goto  errLabel;
			}

			if  (  uiInputLen  >  pDmo->pInputBuffer->m_cbMaxLength  )  {
				traceLogA(  (char*)  "dmoCompressAudio failed: uiInputLen %d > m_cbMaxLength %d.",  uiInputLen,  pDmo->pInputBuffer->m_cbMaxLength  );
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dmoCompressAudio failed: uiInputLen %d > cbMaxLength %d"  ),  uiInputLen,  pDmo->pInputBuffer->m_cbMaxLength  );
				goto  errLabel;
			}
        
		    hr  =  pDmo->pInputBuffer->GetBufferAndLength( &pBuffer, &dwLength );
			if  (  FAILED(  hr  )  )  {
				traceLogA(  (char*)  "dmoCompressAudio: GetBufferAndLength failed."  );
				goto  errLabel;
			}

			CopyMemory(  pBuffer,  pInput,  uiInputLen  );

			hr  =  pDmo->pInputBuffer->SetLength(  uiInputLen  );
		    if  (  FAILED(  hr  )  )  goto  errLabel;
        
			DWORD	dwFlgs;
			dwFlgs  =  iSampleTimeInMs  ?  (  DMO_INPUT_DATA_BUFFERF_TIME  |  DMO_OUTPUT_DATA_BUFFERF_TIMELENGTH  |  DMO_INPUT_DATA_BUFFERF_SYNCPOINT  )  :  DMO_INPUT_DATA_BUFFERF_SYNCPOINT;

			// call processInput
		    hr  =  pDmo->m_pObject->ProcessInput( 0,
                                pDmo->pInputBuffer,
                                dwFlgs,
                                rtStart,
                                rtTimeLen  );

			//  2012/03/19
			MACRO_safeRelease(  pDmo->pInputBuffer  );

			//
			if  (  hr  ==  DMO_E_NOTACCEPTING  )  traceLogA(  (char*)  "dmoCompressAudio: processInput: not accepting."  );
			else  if  (  FAILED(  hr  )  )  {
					  traceLogA(  (char*)  "dmoCompressAudio: ProcessInput failed."  );
					  goto  errLabel;
					  }
			else  if  (  S_FALSE  ==  hr  )  {
					  iErr  =  0;  goto  errLabel;
			}
		}

		//  
		if  (  dmoProcessOutputs(  pDmoInfo  )  )  {
			traceLogA(  (char*)  "dmoCompressVideo: processOutputs failed"  );
			goto  errLabel;
		}

		iErr  =  0;

errLabel:

		#ifdef  __DEBUG__
				if  (  1  )  {
					//  if  (  !iErr  )  traceLogA(  (char*)  "dmoCompressAudio: uiInputLen %d , uiSampleTimeInMs %d, ok",  uiInputLen,  iSampleTimeInMs  );
				}
		#endif

		if  (  iErr  )  {			
			traceLogA(  (char*)  "dmoCompressAudio failed"  );
			MACRO_safeRelease(  pDmo->pInputBuffer  );
			freeDmoOutputs(  pDmoInfo  );
		}

		return  iErr;
}

/////////////////////////////
#if  0
int  initCompressAudio_filterGraph(  AUDIO_COMPRESSOR_CFG  *  pCompressor,  QY_AUDIO_HEADER  *  pVh_decompress,  QY_AUDIO_HEADER  *  pVh_compress,  MY_DMO_INFO  *  pDmoInfo  )
{
	traceLog(  _T(  "Not finished"  )  );
	return  -1;
}

int  exitCompressAudio_filterGraph(  MY_DMO_INFO  *  pDmoInfo  )
{
	traceLog(  _T(  "Not finished"  )  );
	return  -1;
}
int  compressAudio_filterGraph(  MY_DMO_INFO  *  pDmoInfo,  QY_AUDIO_HEADER  *  pAh_decompress,  BYTE  *  pInput,  unsigned  int  uiInputSize,  int  iSampleTimeInMs  )
{
	traceLog(  _T(  "Not finished"  )  );
	return  -1;
}
#endif


///////////////////////////////////////


 /*
struct AudioDecParams {
}; 
*/


  //  
 int  initDecompressAudio_dmo(  QY_MC  *  pQyMc,  const  AUDIO_COMPRESSOR_CFG  *  pCompressor,  QY_AUDIO_HEADER  *  pAh_compress,  QY_AUDIO_HEADER  *  pAh_decompress,  MY_DMO_INFO  *  pDmoInfo  )
{
	 int					iErr	=	-1;

	 if  (  !pDmoInfo  )  return  -1;
	 if  (  pDmoInfo->pDmo  )  return  -1;

	 //QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	 DYN_LIB_DX			*	pDynLib	=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	 GUID					clsid;
	 GUID					clsid_mInSubType;
	 DWORD					dwTag;
	 BOOL					bWmv	=	FALSE;
	 //  int					iWidth	=	pVh_decompress->bih.biWidth;
	 //  int					iHeight	=	pVh_decompress->bih.biHeight;
	 MY_DMO_INFO			myDmoInfo;
	 QMC_DMO			*	pDmo	=	NULL;
	 //  AudioDecParams			AudioParams;

	 DMO_MEDIA_TYPE			mIn;
	 DMO_MEDIA_TYPE			mOut;
	 memset(  &mIn,  0, sizeof(  mIn  )  );
	 memset(  &mOut,  0,  sizeof(  mOut  )  );


	 memset(  &myDmoInfo,  0,  sizeof(  myDmoInfo  )  );
	 pDmo  =  (  QMC_DMO  *  )mymalloc(  sizeof(  QMC_DMO  )  );
	 if  (  !pDmo  )  goto  errLabel;
	 memset(  pDmo,  0,  sizeof(  QMC_DMO  )  );
	 myDmoInfo.pDmo  =  pDmo;


	 if  (  !pAh_compress->wfx.wFormatTag  )  {
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initDmoDecompressAudio failed: compress.dwTag is 0"  )  );
		 goto  errLabel;
	 }
	 if  (  pAh_decompress->wfx.wFormatTag  !=  WAVE_FORMAT_PCM  )  {
		 traceLogA(  (char*)  "initDmoDecompressAudio failed: decompress.dwTage is not pcm"  );
		 goto  errLabel;
	 }

	 try  {

	 dwTag  =  pAh_compress->wfx.wFormatTag;
	 clsid_mInSubType  =  FOURCCMap(  dwTag  );

	 if  (  getDmoInfoBySth(  pQyMc,  pDynLib,  &DMOCATEGORY_AUDIO_DECODER,  NULL,  &clsid_mInSubType,  NULL,  NULL,  NULL,  &clsid,  NULL  )  )  goto  errLabel;


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

	hr  =  pDynLib->pMoInitMediaType(  &mIn,  sizeof(  WAVEFORMATEX  )  +  pAh_compress->wfx.cbSize  );
	if  (  FAILED(  hr  )  )  goto  errLabel;
	mIn.majortype  =  MEDIATYPE_Audio;
	mIn.subtype  =  clsid_mInSubType;
	mIn.formattype  =  FORMAT_WaveFormatEx;	
	mIn.bFixedSizeSamples  =  1;
	mIn.bTemporalCompression  =  0;
	mIn.lSampleSize  =  pAh_compress->wfx.nBlockAlign;
	WAVEFORMATEX  *  pWfx;	pWfx  =  (  WAVEFORMATEX  *  )mIn.pbFormat;
	memcpy(  pWfx,  pAh_compress,  sizeof(  WAVEFORMATEX  )  +  pAh_compress->wfx.cbSize  );

	hr  =  pDynLib->pMoInitMediaType(  &mOut,  sizeof(  WAVEFORMATEX  )  );
	if  (  FAILED(  hr  )  )  goto  errLabel;

	mOut.majortype  =  MEDIATYPE_Audio;
	mOut.subtype  =  MEDIASUBTYPE_PCM;
	mOut.formattype  =  FORMAT_WaveFormatEx;
	mOut.bFixedSizeSamples  =  1;
	mOut.bTemporalCompression  =  0;
	mOut.lSampleSize  =  pAh_decompress->wfx.nBlockAlign;
	pWfx  =  (  WAVEFORMATEX  *  )mOut.pbFormat;
	memset(  pWfx,  0,  sizeof(  WAVEFORMATEX  )  );
	makeWaveFormat_pcm(  pAh_decompress->wfx.nChannels,  pAh_decompress->wfx.nSamplesPerSec,  pAh_decompress->wfx.wBitsPerSample,  pWfx  );

	//  int  len  =  sizeof(  VIDEOINFOHEADER  );

	hr  =  pDmo->m_pObject->SetInputType(  0,  &mIn,  0  );
	if  (  hr  )  goto  errLabel;

	/*
	if  (  configureDMO_enc(  encParams,  m_pObject,  (  AM_MEDIA_TYPE  *  )&mIn,  (  AM_MEDIA_TYPE  *  )&mOut  )  )  {
		traceLogA(  (char*)  "ConfigureDMO failed."  );
		return  -1;
	}
	traceLogA(  (char*)  "ConfigureDMO ok"  );
	*/

	hr  =  pDmo->m_pObject->SetOutputType(  0,  &mOut,  0  );
	if  (  FAILED(  hr  )  )  goto  errLabel;

	DWORD  cbIn,  cbOut,  dwDummy;
	//     
	hr  =  pDmo->m_pObject->GetInputSizeInfo( 0, &cbIn, &dwDummy, &dwDummy);
    if  (  FAILED(  hr  )  )  {
		traceLogA(  (char*)  "Failed GetInputSizeInfo"  );
		goto  errLabel;
    }
	myDmoInfo.cbInputBuffer  =  max(  (  pAh_decompress->wfx.nAvgBytesPerSec  *  2  ),  cbIn  );
    
	hr = pDmo->m_pObject->GetOutputSizeInfo( 0, &cbOut, &dwDummy);
    if  (  FAILED(  hr  )  )  {
		traceLogA(  (char*)  "Failed GetOutputSizeInfo"  );
		goto  errLabel;
    }
	myDmoInfo.cbOutputBuffer  =  max(  (  pAh_decompress->wfx.nAvgBytesPerSec  *  2  ),  cbOut  );


	// create and fill CMediaBuffer
	//  hr  =  CreateBuffer(  myDmoInfo.cbInputBuffer, &pDmo->pInputBuffer  );
	//  if  (  FAILED(  hr  )  )  goto  errLabel;

	//  hr  =  CreateBuffer(  myDmoInfo.cbOutputBuffer,  &pDmo->pOutputBuffer  );
	//  if  (  FAILED(  hr  )  )  goto  errLabel;


	 }
#ifndef  __noMfc__
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
	
	pDynLib->pMoFreeMediaType(  &mIn  );
	pDynLib->pMoFreeMediaType(  &mOut  );

	if  (  iErr  )  {
		exitDecompressAudio_dmo(  &myDmoInfo  );	
	}
	if  (  !iErr  )  {
		memcpy(  pDmoInfo,  &myDmoInfo,  sizeof(  pDmoInfo[0]  )  );
		#ifdef  __DEBUG__
				pDmoInfo->bAudio  =  TRUE;
		#endif
	}

	 return  iErr;
}

 int  exitDecompressAudio_dmo(  MY_DMO_INFO  *  pDmoInfo  )
{
	traceLogA(  (char*)  "exitDmoDecompressAudio enters"  );

	if  (  !pDmoInfo  ||  !pDmoInfo->pDmo  )  return  0;
	QMC_DMO  *  pDmo  =  (  QMC_DMO  *  )pDmoInfo->pDmo;

	if  (  pDmo  )  {
		MACRO_safeRelease(  pDmo->pInputBuffer  );
		freeDmoOutputs(  pDmoInfo  );

		//  2012/03/18
		HRESULT		hr;
		if  (  pDmo->m_pObject  )  {
			try  {
				//  Send Discontinuity on output stream
				hr = pDmo->m_pObject->Discontinuity( 0 );
				if ( FAILED( hr ) ) {
				}
				}
#ifndef  __noMfc__
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

	traceLogA(  (char*)  "exitDmoDecompressAudio leaves"  );

	return  0;
}



 int  decompressAudio_dmo(  MY_DMO_INFO  *  pDmoInfo,  QY_AUDIO_HEADER  *  pAh_compress,  BYTE  *  pInput,  unsigned  int  uiInputLen,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  )
{
		int					iErr			=	-1;
		if  (  !pDmoInfo  )  return  -1;
		if  (  !pDmoInfo->pDmo  )  {
			traceLogA(  (char*)  "dmoDecomprss failed: pDmo is null"  );
			return  -1;
		}
		QMC_DMO  *  pDmo  =  (  QMC_DMO  *  )pDmoInfo->pDmo;

        REFERENCE_TIME				rtStart			=	0;
        //  REFERENCE_TIME				rtStop			=	0;
		REFERENCE_TIME				rtTimeLen		=	0;		//  rtStop  -  rtStart
        BYTE					*	pBuffer			=	NULL;
        DWORD						dwLength;
		HRESULT						hr;

		//  MACRO_safeRelease(  pDmo->pInputBuffer  );
		//  freeDmoOutputs(  pDmoInfo  );


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

			if  (  dwFlags  &  DMO_INPUT_STATUSF_ACCEPT_DATA  )  {

				#ifdef  __DEBUG__
						//  traceLogA(  (char*)  "dmoDecompressAudio: iSampleTime %d, rtTimeLen %d",  iSampleTimeInMs,  ui_rtTimeLen  );
				#endif
				rtStart  =  pDmoInfo->rt_total_rtTimeLen;
				rtTimeLen  =  ui_rtTimeLen;
				if  (  iSampleTimeInMs  &&  rtStart  )  {
					int  mySampleTimeInMs  =  (  int  )(  rtStart  /  (  1000.  *  10  )  );
					if  (  pDmoInfo->iDiffInMs_tStartStream  +  mySampleTimeInMs  !=  iSampleTimeInMs  )  {
						pDmoInfo->iDiffInMs_tStartStream  =  iSampleTimeInMs  -  mySampleTimeInMs;
						//  traceLogA(  (char*)  "dmoDecompressAudio: iDiffInMs_tStartAudio %d",  pDmoInfo->iDiffInMs_tStartAudio  );
					}
				}
				pDmoInfo->rt_total_rtTimeLen  +=  ui_rtTimeLen;


				//
				if  (  !pDmo->pInputBuffer  )  {
					hr = CreateBuffer(  pDmoInfo->cbInputBuffer, &pDmo->pInputBuffer  );
					if  (  FAILED(  hr  )  )  goto  errLabel;
					}
				else  {
					  hr  =  pDmo->pInputBuffer->SetLength(  0  );
					  if  (  FAILED(  hr  )  )  goto  errLabel;
				}

				if  (  uiInputLen  >  pDmo->pInputBuffer->m_cbMaxLength  )  {
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dmoDecompressAudio failed: uiInputLen %d > cbMaxLength %d"  ),  uiInputLen,  pDmo->pInputBuffer->m_cbMaxLength  );
					goto  errLabel;
				}
	    
				hr = pDmo->pInputBuffer->GetBufferAndLength( &pBuffer, &dwLength );
			    if( FAILED( hr ) )  goto  errLabel;

				CopyMemory(  pBuffer,  pInput,  uiInputLen  );

				hr = pDmo->pInputBuffer->SetLength(  uiInputLen  );
				if( FAILED( hr ) )  goto  errLabel;
        
				DWORD	dwFlgs;
				dwFlgs  =  iSampleTimeInMs  ?  (  DMO_INPUT_DATA_BUFFERF_TIME  |  DMO_OUTPUT_DATA_BUFFERF_TIMELENGTH  |  DMO_INPUT_DATA_BUFFERF_SYNCPOINT  )  :  DMO_INPUT_DATA_BUFFERF_SYNCPOINT;

			     // call processInput
				 hr = pDmo->m_pObject->ProcessInput( 0,
                                pDmo->pInputBuffer,
                                dwFlgs,
                                rtStart,
                                rtTimeLen  );

				 //  2012/03/19
				 MACRO_safeRelease(  pDmo->pInputBuffer  );


				//
				if  (  hr  ==  DMO_E_NOTACCEPTING  )  {
					#ifdef  __DEBUG__
							traceLogA(  (char*)  "dmoDecompressAudio: processInput: not accepting"  );
					#endif
					}
				else  if( FAILED( hr ) )  goto  errLabel;
				else  if  (  S_FALSE  ==  hr  )  {
						  #ifdef  __DEBUG__
								  traceLogA(  (char*)  "dmoDecompressAudio: no output"  );
						  #endif
					      iErr  =  0;  goto  errLabel;
				}

			}

			}
#ifndef  __noMfc__
		catch  (  CException  *  e  )  {
			   e->Delete(  );
			   goto  errLabel;
		}
#endif
		catch  (  ...  )  {
				goto  errLabel;
		}


		if  (  dmoProcessOutputs(  pDmoInfo  )  )  {
			#ifdef  __DEBUG__
					traceLogA(  (char*)  "dmoDecompressVideo: processOutputs failed"  );
			#endif
			goto  errLabel;
		}

		

		iErr  =  0;

errLabel:


		#ifdef  __DEBUG__
				if  (  !iErr  )  {
					//  if  (  1  )  traceLogA(  (char*)  "dmoDecompressAudio: uiInputLen %d, dwLength_dec %d. iSampleTimeInMs %d",  uiInputLen,  dwLength,  iSampleTimeInMs  );
				}
		#endif

		if  (  iErr  )  {
			#ifdef  __DEBUG__
					traceLogA(  (char*)  "dmoDecompressAudio failed."  );
			#endif
			MACRO_safeRelease(  pDmo->pInputBuffer  );
			freeDmoOutputs(  pDmoInfo  );
		}

		return  iErr;
}


/////////////////////////////////////////////////









#ifdef  __DEBUG__

#include	<Dmodshow.h>

#if  0
 BOOL  testFilterGraph(  )
{


	AM_MEDIA_TYPE	mt;
	memset(  &mt,  0,  sizeof(  mt  )  );
	GUID	k	=	GUID_NULL;

	
	IGraphBuilder  *  pGraph  =  NULL;
	ICaptureGraphBuilder2 *pBuilder = NULL;

	IMediaControl  *  pControl  =  NULL;
	IMediaEvent  *  pEvent  =  NULL;

	CComPtr<IBaseFilter>            pASFMultiplexer;
	CComPtr<IFileSinkFilter>        pFileSinkFilter;


	IPin  *  pStreamOut  =  NULL,  *  pStreamRender  =  NULL;


	// initialize  COM,  create  the filter graph manager,  and  query  for the event and control interfaces
	HRESULT  hr  =  CoInitialize(  NULL  );
	if  (  FAILED(  hr  ) )  return  FALSE;

	// Create the Filter Graph Manager.
	hr =  CoCreateInstance(CLSID_FilterGraph, NULL,
		CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pGraph);
	if (!SUCCEEDED(hr))  goto  errLabel;

#if  10
	

		// Create the Capture Graph Builder.
		hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL,
			CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, 
			(void **)&pBuilder);
		if (SUCCEEDED(hr))
		{
			pBuilder->SetFiltergraph(pGraph);
		}
#endif
		
		IBaseFilter	*	pSource;

		if  (  myGetNewFilter(  g_pEnv,  CLSID_VCam_is,  (  void  **  )&pSource  )  )  goto  errLabel;

		hr  =  pGraph->AddFilter(  pSource,  L"Source"  );

		if  (  !SUCCEEDED(  hr  )  )  goto  errLabel;

		GUID	clsid;
		GUID	 clsid_mOutSubType  =  WMCMEDIASUBTYPE_WMV3;
		if  (  getDmoInfoBySth(  (  (  QY_DYN_LIBS  *  )g_pEnv->pDynLibs  )->pLib_dx,  &DMOCATEGORY_VIDEO_ENCODER,  NULL,  NULL,  NULL,  &clsid_mOutSubType,  NULL,  &clsid,  NULL  )  )  goto  errLabel;

		IBaseFilter	*	pFilter_w;
		hr  =  CoCreateInstance(  CLSID_DMOWrapperFilter,  NULL,  CLSCTX_INPROC_SERVER,  IID_IBaseFilter,  (  void  **  )&pFilter_w  );
		if  (  SUCCEEDED(  hr  )  )  {
			IDMOWrapperFilter	*	pWrapper;
			hr  =  pFilter_w->QueryInterface(  IID_IDMOWrapperFilter,  (  void  **  )&pWrapper  );
			if  (  SUCCEEDED(  hr  )  )  {
				hr  =  pWrapper->Init(  clsid,  DMOCATEGORY_VIDEO_ENCODER  );
				//  pWrapper->Release(  );
			}
			if  (  SUCCEEDED(  hr  )  )  {
				hr  =  pGraph->AddFilter(  pFilter_w,  _T(  "Enc"  )  );
			}
			//  pFilter_w->Release(  );
		}

		IBaseFilter		*  pGrabberF;
		ISampleGrabber_is  *	m_pGrabber;

		IBaseFilter  *  pNullRenderer;

#if  0

		myGetNewFilter(  g_pEnv,  CLSID_SampleGrabber_is,  (  void  **  )&pGrabberF  );

		hr  =  pGraph->AddFilter(  pGrabberF,  L"Sample  Grabber"  );
		if  (  FAILED(  hr  )  )  return  FALSE;

		pGrabberF->QueryInterface(  IID_ISampleGrabber_is,  (  void  **  )&m_pGrabber  );

		ZeroMemory(  &mt,  sizeof(  AM_MEDIA_TYPE  )  );
		mt.majortype  =  MEDIATYPE_Video;
		//  mt.subtype  =  MEDIASUBTYPE_RGB24;
		//  mt.subtype  =  WMCMEDIASUBTYPE_WMV3;


		mt.formattype  =  FORMAT_VideoInfo;

		VIDEOINFOHEADER  vih;
		memset(  &vih,  0,  sizeof(  vih  )  );
		mt.cbFormat  =  sizeof(  vih  );
		mt.pbFormat  =  (  BYTE  *  )&vih;

		hr  =  m_pGrabber->SetMediaType(  &(  mt  )  );
		//  hr  =  pGrabberF->SetMediaType(  PINDIR_INPUT,  &CMediaType(  mt  )  );

#if  0
		hr  =  CoCreateInstance(  CLSID_NullRenderer,  NULL,  CLSCTX_INPROC_SERVER,  IID_IBaseFilter,  (  void  **  )&pNullRenderer  );
#else
		myGetNewFilter(  g_pEnv,  CLSID_NullRenderer_is,  (  void  **  )&pNullRenderer  );
#endif

		hr  =  pGraph->AddFilter(  pNullRenderer,  L"Null  Renderer"  );


#endif

#if  0
		IPin  *   pGrabInPin  =  NULL;
		hr  =  myGetPin(  pGrabberF,  PINDIR_INPUT,  &pGrabInPin  );
		AM_MEDIA_TYPE  mt1;
		hr  =  pGrabInPin->ConnectionMediaType(  &mt1  );
		myDisplayType(  (  "connectedMediaType"  ),  &mt1  );
		pGrabInPin->Release(  );
#endif

#if  0
		IPin   *  pGrabOutPin  =  NULL;
		hr  =  myGetPin(  pGrabberF,  PINDIR_OUTPUT,  &pGrabOutPin  );
		hr  =  pGraph->Render(  pGrabOutPin  );
		if  (  FAILED(  hr  )  )  
		{
			myMessageBox(  NULL,  _T(  ""  ),  _T(  "Could  not  render  grabber output pin\r\n"  ),  MB_OK  );
			return  FALSE;
		}
		pGrabOutPin->Release(  );
#endif


		hr  =  pBuilder->SetOutputFileName( &MEDIASUBTYPE_Asf, L"c:\\tttbbb\\video1.asf", &pASFMultiplexer, &pFileSinkFilter );


		//  hr  =  pBuilder->RenderStream(  NULL,  NULL,  pSource,  NULL,  pGrabberF  );
		//  hr  =  pBuilder->RenderStream(  NULL,  NULL,  pSource,  NULL,  pFilter_w  );
			
		hr  =  pBuilder->RenderStream( &PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, pSource, NULL,  pFilter_w  );
		
		myDumpGraph(  pGraph,  0  );

		hr  =  pBuilder->RenderStream(  NULL,  NULL,  pFilter_w,  NULL,  pASFMultiplexer );

		hr  =  pBuilder->RenderStream(  NULL,  NULL,  pSource,  pFilter_w,  pASFMultiplexer  );
		if  (  FAILED(  hr  )  )  {
			qyDisplayLastError(  "ll"  );
		}
		hr  =  pBuilder->RenderStream(  NULL,  NULL,  pFilter_w,  NULL,  pASFMultiplexer  );
	
	
		hr  =  pBuilder->RenderStream(  NULL,  NULL,  pGrabberF,  NULL,  pNullRenderer  );
		//  hr  =  pBuilder->RenderStream(  NULL,  NULL,  pGrabberF,  NULL,  NULL  );


		myDumpGraph(  pGraph,  0  );  

		hr  =  pGraph->QueryInterface(  IID_IMediaEvent,  (  void  **  )&pEvent  );
		if  (  FAILED(  hr  )  )  return  FALSE;

		hr  =  pGraph->QueryInterface(  IID_IMediaControl,  (  void  **  )&pControl  );
		if  (  FAILED(  hr  )  )  return  FALSE;

		//  pGrabberF->RegisterCallback(  myProc  );

		long  evCode  =  0;
		hr  =  pControl->Run(  );
		hr  =  pEvent->WaitForCompletion(  INFINITE,  &evCode  );
		Sleep(  1000  );

		//  pGrabberF->RegisterCallback(  NULL  );


		//  pGrabOutPin->Release(  );

		//  pGrabberF->Release(  );

errLabel:

		if  (  pControl  )  {
				pControl->Stop(  );
		pControl->Release(  );
		}
		if  (  m_pGrabber  )  m_pGrabber->Release(  );
		if  (  pEvent  )  pEvent->Release(  );
		if  (  pGraph  )  pGraph->Release(  );
		if  (  pBuilder  )  pBuilder->Release(  );

		if  (  pNullRenderer  )  pNullRenderer->Release(  );

		return  TRUE;
}
#endif



 int  tmpShowQuality(  WAVEFORMATEX  *  p  )
{
	DWORD	dwBps  =  p->nAvgBytesPerSec;

	if  (  (  dwBps  &  0x7fffff00  )  ==  0x7fffff00  )  {
		traceLogA(  (char*)  "VBR Qualigy %d%%",  dwBps  &  0x000000ff  );
		}
	else
		traceLogA(  (char*)  "Not a valid VBR quality value"  );
	
	return  0;
}

  int  testDmoCompressAudioInit(  )
{
	   //  return  0;

	  QY_MC* pQyMc = nullptr;//QY_GET_GBUF(  );
		  return -1;
	GUID	clsid_category  =  DMOCATEGORY_AUDIO_ENCODER;
	GUID	clsid;

	 //  wszName WM Speech Encoder DMO, {1F1F4E1A-2252-4063-84BB-EEE75F8856D5}
	 //  wszName WMAudio Encoder DMO, {70F598E9-F4AB-495A-99E2-A7C4D3D89ABF}
	 //
	 //  wszName WMAudio Decoder DMO, {2EEB4ADF-4578-4D10-BCA7-BB955F56320A}
	 //  wszName WMAPro over S/PDIF DMO, {5210F8E4-B0BB-47C3-A8D9-7B2282CC79ED}
	 //  wszName WMSpeech Decoder DMO, {874131CB-4ECC-443B-8948-746B89595D20}
	 //  wszName MP3 Decoder DMO, {BBEEA841-0A63-4F52-A7AB-A9B3A84ED38A}

#if  10
    clsid_category  =  DMOCATEGORY_AUDIO_DECODER;
	enumDmos(  (  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx,  &clsid_category,  NULL  );
	
	 clsid  =  CLSID_MP3_Decoder_DMO;
	 enumDmoIoTypes(  pQyMc,&clsid,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL  );
#endif


#if  0
	clsid_category  =  DMOCATEGORY_VIDEO_ENCODER;
	enumDmos(  (  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx,  &clsid_category,  NULL  );

	clsid  =  CLSID_WMVideo9_Encoder_DMO;
	enumDmoIoTypes(  &clsid,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL  );
#endif

	
#if  0
	clsid_category  =  DMOCATEGORY_VIDEO_DECODER;
	enumDmos(  (  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx,  &clsid_category,  NULL  );
	
	 clsid  =  CLSID_WMVideo_Decoder_DMO;
	 enumDmoIoTypes(  &clsid,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL  );
#endif

		
	//  enumDmoIoTypes(  &CLSID_WMSpeech_Encoder_DMO,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL  );

		
	    return  0;

	 //  QY_MC			*	pQyMc	=	QY_GET_GBUF(  );
	 DYN_LIB_DX			*	pDynLib	=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	 GUID					clsid_mOutSubType;
	 DWORD					dwTag;
	 IMediaObject       *	m_pObject  =  NULL;
	 AUDIO_ENC_PARAMS		encParams;
	 QY_AUDIO_HEADER		ah;


	 clsid  =  CLSID_WMAudio_Encoder_DMO;
	 clsid_mOutSubType  =  WMCMEDIASUBTYPE_WMA9;
	 dwTag  =  WAVE_FORMAT_WMAUDIO2;


	 memset(  &encParams,  0,  sizeof(  encParams  )  );
	 setEncodingDefaults_audio(  dwTag,  2,  44100,  16,  3998,  &encParams  );

	 if  (  getDmoInfoBySth(  pQyMc,  pDynLib,  &clsid_category,  NULL,  NULL,  NULL,  NULL,  &ah,  &clsid,  NULL  )  )  goto  errLabel;
	 encParams.pAh  =  &ah;


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


	DMO_MEDIA_TYPE      mIn;
	memset(  &mIn,  0, sizeof(  mIn  )  );
	hr  =  pDynLib->pMoInitMediaType(  &mIn,  sizeof(  WAVEFORMATEX  )  );


	DMO_MEDIA_TYPE		mOut;
	/*
	
    m_mt.majortype  = MEDIATYPE_Audio;
    m_mt.subtype    = MEDIASUBTYPE_PCM;
    m_mt.formattype = FORMAT_WaveFormatEx;
    m_mt.cbFormat   = sizeof(WAVEFORMATEX);
    //  m_mt.pbFormat   = (BYTE*) (m_pwfx);
    m_mt.pUnk = NULL;       // CopyMediaType will crash if we don't intialize this
	*/

	mIn.majortype  =  MEDIATYPE_Audio;
	mIn.subtype  =  MEDIASUBTYPE_PCM;
	mIn.formattype  =  FORMAT_WaveFormatEx;
	WAVEFORMATEX  *  pwfx  =  (  WAVEFORMATEX  *  )mIn.pbFormat;
	//  makeWaveFormat_pcm(  DEFAULT_audio_nChannels,  DEFAULT_audio_iHertz,  DEFAULT_audio_wBitsPerSample,  pwfx  );
	makeWaveFormat_pcm(  2,  44100,  16,  pwfx  );
	//  makeWaveFormat_pcm(  2,  8000,  16,  pwfx  );
	


	hr  =  m_pObject->SetInputType(  0,  &mIn,  0  );
	if  (  hr  )  return  -1;
	
	if  (  configureDMO_enc_audio(  &encParams,  m_pObject,  (  AM_MEDIA_TYPE  *  )&mIn,  (  AM_MEDIA_TYPE  *  )&mOut  )  )  {
		traceLogA(  (char*)  "ConfigureDMO failed."  );
		return  -1;
	}
	traceLogA(  (char*)  "ConfigureDMO ok"  );


errLabel:
	 return  0;
}



#endif



