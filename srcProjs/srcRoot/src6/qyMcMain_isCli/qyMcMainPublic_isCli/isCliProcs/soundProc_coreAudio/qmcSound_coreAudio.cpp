

#include	"stdafx.h"
#include	<stddef.h>
 
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>

#include	<string>

#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"
#include	"qmcSound_dx.h"

#include	"qmcVideoCapture_isCli.h"
#include	<mmdeviceapi.h>
#include	<Audioclient.h>
#include	"policyAvParams.h"
#include	"qyAvRecordPublic.h"

#include	"tmpFfmpegPublic.h"
#include	"tmpFfmpegCommon.h"
#include	"GuiShare.h"
#include	"aecPublic.h"

//
#define		REFTIMES_PER_SEC			10000000
#define		REFTIMES_PER_MILLISEC		10000

#define		EXIT_ON_ERROR(hres  )	\
				if  (  FAILED(  hres  )  )  {  goto  Exit;  }
#define		SAFE_RELEASE(  punk  )  \
				if  (  (  punk  )  !=  NULL  )  \
				{  (  punk  )->Release(  );  (  punk  )  =  NULL;  }

const  CLSID  CLSID_MMDeviceEnumerator  =  __uuidof(  MMDeviceEnumerator  );
const  IID  IID_IMMDeviceEnumerator  =  __uuidof(  IMMDeviceEnumerator  );
const  IID  IID_IAudioClient  =  __uuidof(  IAudioClient  );
const  IID  IID_IAudioCaptureClient  =  __uuidof(  IAudioCaptureClient  );

typedef  struct  {
}		 MyAudioSink;


//
#if  0
//  HRESULT  RecordAudioStream(  void  *  pMySink  )
extern  "C"  DWORD  WINAPI  old_coreAudioRecThreadFunc(  LPVOID ignored  )
{
	int								iErr						=	-1;
	QY_MC						*	pQyMc						=	QY_GET_GBUF(  );
	MC_VAR_isCli				*	pProcInfo					=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	CAP_procInfo_recordSound	*  pRecordSoundProcInfo			=  &pProcInfo->av.localAv.recordSoundProcInfo;
	QY_qThreadProcInfo_common	*  pRecThread					=	&pRecordSoundProcInfo->recThread;

	CQyMalloc						mallocObj_pAudioDataBuf;
	 char						*	pAudioDataBuf				=	NULL;
	 int							dataLen_pAudioDataBuf		=	0;

	 CQyMalloc						mallocObj_pMsgBuf;
	 MIS_MSGU					*	pMsgBuf						=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsgBuf  )  return  -1;

	 //
	 AUDIO_COMPRESSOR_CFG  *  pCompressor  =  &pRecordSoundProcInfo->compressAudio.compressor;
	LPGUID  pGuid  =  &pRecordSoundProcInfo->guid_aDevice;

	//
	HRESULT  hr;
	REFERENCE_TIME  hnsRequestedDuration  =  REFTIMES_PER_SEC;
	//REFERENCE_TIME  hnsActualDuration;
	UINT32  bufferFrameCount;
	UINT32  numFramesAvailable;
	IMMDeviceEnumerator  *  pEnumerator  =  NULL;
	IMMDevice  *  pDevice  =  NULL;
	IAudioClient  *  pAudioClient  =  NULL;
	IAudioCaptureClient  *  pCaptureClient  =  NULL;
	WAVEFORMATEX  *  pwfx  =  NULL;
	UINT32  packetLength  =  0;
	BOOL  bDone  =  FALSE;
	BYTE  *  pData;
	DWORD  flags;
	//
	BOOL  b_audioClient_started  =  FALSE;

	//
	hr  =  CoCreateInstance(
		CLSID_MMDeviceEnumerator,  NULL,
		CLSCTX_ALL,  IID_IMMDeviceEnumerator,
		(  void ** )&pEnumerator  );
	EXIT_ON_ERROR(  hr  );

	//
	EDataFlow  dataFlow  =  eCapture;
	//dataFlow  =  eRender;
	//
	hr  =  pEnumerator->GetDefaultAudioEndpoint(
						dataFlow,  eConsole,  &pDevice  );
	EXIT_ON_ERROR(  hr  );

	hr  =  pDevice->Activate(
					IID_IAudioClient,  CLSCTX_ALL,
					NULL,  (  void  **  )&pAudioClient  );
	EXIT_ON_ERROR(  hr  );

	hr  =  pAudioClient->GetMixFormat(  &pwfx  );
	EXIT_ON_ERROR(  hr  );

	//
	WAVEFORMATEX  wfx;
	//wfx  =  pRecordSoundProcInfo->compressAudio.ah_decompress.wfx;
	//
	makeWaveFormat_pcm(  1,  pwfx->nSamplesPerSec,  16,  &wfx  );
	WAVEFORMATEX  * pClosestMatch  =  NULL;
	hr  =  pAudioClient->IsFormatSupported(  AUDCLNT_SHAREMODE_SHARED,  &wfx,  &pClosestMatch  );
	if  (  pClosestMatch  )  {
		CoTaskMemFree(  pClosestMatch  );  pClosestMatch  =  NULL;
	}
	EXIT_ON_ERROR(  hr  );
	
	//
	DWORD  StreamFlags  =  0;
	//StreamFlags  =  AUDCLNT_STREAMFLAGS_LOOPBACK;

	//
	hr  =  pAudioClient->Initialize(
								AUDCLNT_SHAREMODE_SHARED,
								StreamFlags,
								hnsRequestedDuration,
								0,
								&wfx,
								NULL  );
	EXIT_ON_ERROR(  hr  );

	//
	hr  =  pAudioClient->GetBufferSize(  &bufferFrameCount  );
	EXIT_ON_ERROR(  hr  );

	hr  =  pAudioClient->GetService(
							IID_IAudioCaptureClient,
							(  void  **  )&pCaptureClient  );
	EXIT_ON_ERROR(  hr  );

	//
	//hnsActualDuration  =  pMySink->SetFormat(  pwfx  );
	EXIT_ON_ERROR(  hr  );

	//hnsActualDuration  =  (  double  )REFTIMES_PER_SEC  *  bufferFrameCount  /  pwfx->nSamplesPerSec;
	hr  =  pAudioClient->Start(  );
	EXIT_ON_ERROR(  hr  );
	//  2017/01/28
	b_audioClient_started  =  TRUE;
	

	//
	 int	bufSize_pAudioDataBuf  =  pProcInfo->cfg.uiBufSize_myPlayAudioData;
	 if  (  !(  pAudioDataBuf  =  (  char  *  )mallocObj_pAudioDataBuf.mallocf(  bufSize_pAudioDataBuf  )  )  )  goto  errLabel;

	 //
	 unsigned  int  uiBytesRecorded_perBlockAlign  =  0;
	 AUDIO_COMPRESSOR_CFG  audioCompressor  =  {0};
	 PolicyAvParams		&	gAvParams	=	*pProcInfo->p_gAvParams;	//  QY_GET_PolicyAvParams(  );
	 audioCompressor.playCfg  =  gAvParams.CONST_audioPlayCfg_07s;
	  uiBytesRecorded_perBlockAlign  =  MACRO_getuiBytesRecorded_perBlockAlign(  audioCompressor,  &wfx  );		



	 int	iCapTimeInMs  =  40;
	 int  nBytes_toRecord  =  uiBytesRecorded_perBlockAlign  *  wfx.nBlockAlign;
	 int  nAvgBytesPerSec  =  wfx.nAvgBytesPerSec;
	 
	 if  (  !nAvgBytesPerSec  )  goto  errLabel;
	 iCapTimeInMs  =  nBytes_toRecord  *  1000  /  nAvgBytesPerSec;
	 if  (  iCapTimeInMs  <=  10  )  goto  errLabel;


	//  2017/01/28
	 //pRecThread->bQuit  =  FALSE;
	 pRecThread->bRunning  =  TRUE;
	 pRecordSoundProcInfo->usErrors_processInput  =  0;
	 
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "AEC record sound starts"  )  );

	 //
	 broadcastRecorderStatus(  pQyMc  );
	 

	//
	while  (  bDone  ==  FALSE  &&  !pRecThread->bQuit  )  
	{
		//  Sleep for half the buffer duration
		//int  iVal  =  hnsActualDuration  /  REFTIMES_PER_MILLISEC  /  2;
		//Sleep(  hnsActualDuration  /  REFTIMES_PER_MILLISEC  /  2  );
		Sleep(  iCapTimeInMs  );

		hr  =  pCaptureClient->GetNextPacketSize(  &packetLength  );
		EXIT_ON_ERROR(  hr  );

		while  (  packetLength  !=  0  )  
		{
			hr  =  pCaptureClient->GetBuffer(
										&pData,
										&numFramesAvailable,
										&flags,  NULL,  NULL  );
			EXIT_ON_ERROR(  hr  );

			if  (  flags  &  AUDCLNT_BUFFERFLAGS_SILENT  )
			{
				pData  =  NULL;
			}

			//  Copy the available capture data to the audio sink
			//hr  =  pMySink->CopyData(  pData,  numFramesAvailable, &bDone  );
			//EXIT_ON_ERROR(  hr  );

			if  (  pData  )  {
				//
				int  dataLength  =  numFramesAvailable  *  wfx.nBlockAlign;				
				char  *  gBuf  =  (  char  *  )pData;
				//
				if  (  dataLength  +  dataLen_pAudioDataBuf  <  bufSize_pAudioDataBuf  )  {				
					memcpy(  pAudioDataBuf  +  dataLen_pAudioDataBuf,  gBuf,  dataLength  );			
					dataLen_pAudioDataBuf  +=  dataLength;					
				}
			}


			//
			hr  =  pCaptureClient->ReleaseBuffer(  numFramesAvailable  );
			EXIT_ON_ERROR(  hr  );

			hr  =  pCaptureClient->GetNextPacketSize(  &packetLength  );
			EXIT_ON_ERROR(  hr  );
		}
		
		//
		//
		#ifdef  _DEBUG
				#if  0
					TCHAR	tBuf[128]  =  _T(  ""  );
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "get audio %d bytes\n"  ),  dataLen_pAudioDataBuf  );
					OutputDebugString(  tBuf  );
				#endif
		#endif


		for  (  ;  ;  )  {
			 if  (  dataLen_pAudioDataBuf  <  nBytes_toRecord  )  break;								
			 //
			 processInput_post(  pProcInfo,  nAvgBytesPerSec,  (  BYTE  *  )pAudioDataBuf,  nBytes_toRecord,  pMsgBuf  );				    					
			 memcpy(  pAudioDataBuf,  pAudioDataBuf  +  nBytes_toRecord,  dataLen_pAudioDataBuf  -  nBytes_toRecord  );
			 dataLen_pAudioDataBuf  -=  nBytes_toRecord;			 
		}			

	}


Exit:
errLabel:
	
	if  (  b_audioClient_started  )  {
		hr  =  pAudioClient->Stop(  );
		//  EXIT_ON_ERROR(  hr  );
	}

	//
	if  (  pwfx  )  CoTaskMemFree(  pwfx  );
	SAFE_RELEASE(  pEnumerator  );
	SAFE_RELEASE(  pDevice  );
	SAFE_RELEASE(  pAudioClient  );
	SAFE_RELEASE(  pCaptureClient  );
	

	//
	pRecThread->bRunning  =  FALSE;

	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "AEC record sound ends"  )  );
	 
	 broadcastRecorderStatus(  pQyMc  );



	return  hr;
	
}
#endif



std::string  getSubFormatStr(  GUID  subformat  )
 {
	 std::string  str  =  "unknown subformat";

	 //
	 if  (  subformat  ==  KSDATAFORMAT_SUBTYPE_PCM  )  {
		 str="pcm";
	 }
	 else  if  (  subformat  ==  KSDATAFORMAT_SUBTYPE_IEEE_FLOAT  )  {
		 str="float";
	 }
	 else  if  (  subformat  ==  KSDATAFORMAT_SUBTYPE_DRM  )  {
		 str="drm";
	 }
	 else  if  (  subformat  ==  KSDATAFORMAT_SUBTYPE_ALAW  )  {
		 str=  "alaw";
	 }
	 else  if  (  subformat  ==  KSDATAFORMAT_SUBTYPE_MULAW  )  {
		 str  =  "mulaw";
	 }
	 else  if  (  subformat  ==  KSDATAFORMAT_SUBTYPE_ADPCM  )  {
		 str  =  "adpcm";
	 }

	 return  str;
}
 
 

//  HRESULT  RecordAudioStream(  void  *  pMySink  )
extern  "C"  DWORD  WINAPI  coreAudioRecThreadFunc(  LPVOID ignored  )
{
	int								iErr						=	-1;
	QY_MC* pQyMc = nullptr;// QY_GET_GBUF();
	if (!pQyMc)return  -1;
	MC_VAR_isCli				*	pProcInfo					=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	CAP_procInfo_recordSound	*  pRecordSoundProcInfo			=  &pProcInfo->av.localAv.recordSoundProcInfo;
	QY_qThreadProcInfo_common	*  pRecThread					=	&pRecordSoundProcInfo->recThread;

	//
	PolicyAvParams& gAvParams = *pProcInfo->p_gAvParams;	//  QY_GET_PolicyAvParams(  );

	//
	CQyMalloc						mallocObj_pAudioDataBuf;
	 char						*	pAudioDataBuf				=	NULL;
	 int							dataLen_pAudioDataBuf		=	0;
	 int							bufSize_pAudioDataBuf;

	 //
	 CQyMalloc						mallocObj_pMsgBuf;
	 MIS_MSGU					*	pMsgBuf						=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsgBuf  )  return  -1;

	 //
	 AUDIO_COMPRESSOR_CFG  *  pCompressor  =  &pRecordSoundProcInfo->compressAudio.compressor;
	LPGUID  pGuid  =  &pRecordSoundProcInfo->guid_aDevice;

	//
	HRESULT  hr;
	REFERENCE_TIME  hnsRequestedDuration  =  REFTIMES_PER_SEC;
	REFERENCE_TIME  hnsActualDuration;
	UINT32  bufferFrameCount;
	UINT32  numFramesAvailable;
	IMMDeviceEnumerator  *  pEnumerator  =  NULL;
	IMMDevice  *  pDevice  =  NULL;
	IAudioClient  *  pAudioClient  =  NULL;
	IAudioCaptureClient  *  pCaptureClient  =  NULL;
	WAVEFORMATEX  *  pwfx  =  NULL;
	UINT32  packetLength  =  0;
	BOOL  bDone  =  FALSE;
	BYTE  *  pData;
	DWORD  flags;
	//
	BOOL  b_audioClient_started  =  FALSE;

	//
	bool  bNeed_resample  =  false;
	void  *  pCtx_resample  =  NULL;
	//
	CQyMalloc  mallocObj_resampleBuf;
	char  *  pResampleBuf=mynull;
	int  dataLen_pResampleBuf  =  0;
	int  bufSize_pResampleBuf;

	//
	TCHAR  tBuf[128];

	//
	hr  =  CoCreateInstance(
		CLSID_MMDeviceEnumerator,  NULL,
		CLSCTX_ALL,  IID_IMMDeviceEnumerator,
		(  void ** )&pEnumerator  );
	EXIT_ON_ERROR(  hr  );

	//
	EDataFlow  dataFlow; dataFlow = eCapture;
	//dataFlow  =  eRender;
	//
	hr  =  pEnumerator->GetDefaultAudioEndpoint(
						dataFlow,  eConsole,  &pDevice  );
	EXIT_ON_ERROR(  hr  );

	hr  =  pDevice->Activate(
					IID_IAudioClient,  CLSCTX_ALL,
					NULL,  (  void  **  )&pAudioClient  );
	EXIT_ON_ERROR(  hr  );

	hr  =  pAudioClient->GetMixFormat(  &pwfx  );
	EXIT_ON_ERROR(  hr  );

	//
	if  (  pwfx->wFormatTag  !=  WAVE_FORMAT_EXTENSIBLE  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "coreAudioRec failed, pwfx->wFormatTag %d, unprocessed"  ),  (int)pwfx->wFormatTag  );
		showInfo_open0(  0,  0,  tBuf  );
		goto  errLabel;
	}
	WAVEFORMATEXTENSIBLE* pwfe; pwfe = (WAVEFORMATEXTENSIBLE*)pwfx;
	//
	__int64 src_ch_layout;
	int src_rate;
	AVSampleFormat src_sample_fmt;
	int src_nb_samples;
	__int64  dst_ch_layout;
	int  dst_rate;
	AVSampleFormat  dst_sample_fmt;
	int  dst_nb_samples;
	int  dst_bufSize;
	int  nAvgBytesPerSec_resample; nAvgBytesPerSec_resample = 0;
	int  nBytes_toRecord_resample; nBytes_toRecord_resample = 0;

	//
	src_rate  =  pwfe->Format.nSamplesPerSec;
	if  (  pwfe->SubFormat  ==  KSDATAFORMAT_SUBTYPE_PCM  )  {
		switch  (  pwfe->Format.wBitsPerSample  )  {
				case  16:
					  src_sample_fmt  =  AV_SAMPLE_FMT_S16;
					  break;
				case  32:
					  src_sample_fmt  =  AV_SAMPLE_FMT_S32;
					  break;
				default:
						_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "coreAudioRec failed, pcm, unprocessed bits, %d"  ),  pwfe->Format.wBitsPerSample  );		
						showInfo_open0(  0,  0,  tBuf  );
						goto  errLabel;
		}
	}
	else  if  (  pwfe->SubFormat  ==  KSDATAFORMAT_SUBTYPE_IEEE_FLOAT  )  {
			  switch  (  pwfe->Format.wBitsPerSample  )  {
					  case  32:
						    src_sample_fmt  =  AV_SAMPLE_FMT_FLT;
							break;
					  default:
						_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "coreAudioRec failed, flt, unprocessed bits, %d"  ),  pwfe->Format.wBitsPerSample  );		
						showInfo_open0(  0,  0,  tBuf  );
							 goto  errLabel;
		
			  }
		 	  }
	else  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "coreAudioRec failed, unprocessed subformat, %s"  ),  getSubFormatStr(  pwfe->SubFormat  )  );
		showInfo_open0(  0,  0,  tBuf  );
		goto  errLabel;
	}
	switch  (  pwfe->Format.nChannels  ) {
			case  1:
				  src_ch_layout  =  AV_CH_LAYOUT_MONO;
				  break;
			case  2:
				  src_ch_layout  =  AV_CH_LAYOUT_STEREO;
				  break;
			case  4:
				  src_ch_layout  =  AV_CH_LAYOUT_2_2;
				  break;
			default:
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "coreAudioRec failed, unprocessed channels %d"  ),  pwfe->Format.nChannels  );
				showInfo_open0(  0,  0,  tBuf  );
				goto  errLabel;				  
				break;
	}
	//
	dst_rate  =  16000;
	dst_ch_layout  =  AV_CH_LAYOUT_MONO;
	dst_sample_fmt  =  AV_SAMPLE_FMT_S16;

	//
	if  (  src_rate  !=  dst_rate
		||  src_ch_layout  !=  dst_ch_layout
		||  src_sample_fmt  !=  dst_sample_fmt  )
	{
		bNeed_resample  =  true;
		//
		if  (  src_rate  %  100  )  {
			_sntprintf(  tBuf,  mycountof( tBuf),  _T(  "coreAudioRec failed, unsupported sampleRate %d"  ),  src_rate  );
			showInfo_open0(0,0, tBuf  );
			goto  errLabel;
		}
		src_nb_samples  =  src_rate  /  100;
		//
		if  (  GuiShare.pf_initResample(  src_ch_layout,  src_rate,  src_sample_fmt,  src_nb_samples,  dst_ch_layout,  dst_rate,  dst_sample_fmt,  &pCtx_resample  )  )  
		{
			goto  errLabel;
		}
		//
		dst_nb_samples  =  dst_rate  /  100;
		dst_bufSize  =  dst_nb_samples  *  2;
		//
		nAvgBytesPerSec_resample  =  dst_rate  *  2;
		nBytes_toRecord_resample  =  dst_bufSize;
		//
		bufSize_pResampleBuf  =  pProcInfo->cfg.uiBufSize_myPlayAudioData;
		pResampleBuf  =  mallocObj_resampleBuf.mallocf(0,bufSize_pResampleBuf  );
		if(  !pResampleBuf  )  goto  errLabel;
	}
	
	//
	DWORD  StreamFlags; StreamFlags = 0;
	//StreamFlags  =  AUDCLNT_STREAMFLAGS_LOOPBACK;

	//
	hr  =  pAudioClient->Initialize(
								AUDCLNT_SHAREMODE_SHARED,
								StreamFlags,
								hnsRequestedDuration,
								0,
								pwfx,
								NULL  );
	EXIT_ON_ERROR(  hr  );

	//
	hr  =  pAudioClient->GetBufferSize(  &bufferFrameCount  );
	EXIT_ON_ERROR(  hr  );

	hr  =  pAudioClient->GetService(
							IID_IAudioCaptureClient,
							(  void  **  )&pCaptureClient  );
	EXIT_ON_ERROR(  hr  );

	//
	//hr  =  pMySink->SetFormat(  pwfx  );
	EXIT_ON_ERROR(  hr  );

	hnsActualDuration  =  (  double  )REFTIMES_PER_SEC  *  bufferFrameCount  /  pwfx->nSamplesPerSec;
	
	hr  =  pAudioClient->Start(  );
	EXIT_ON_ERROR(  hr  );
	//  2017/01/28
	b_audioClient_started  =  TRUE;
	

	//
	 bufSize_pAudioDataBuf  =  pProcInfo->cfg.uiBufSize_myPlayAudioData;
	 if  (  !(  pAudioDataBuf  =  (  char  *  )mallocObj_pAudioDataBuf.mallocf(  bufSize_pAudioDataBuf  )  )  )  goto  errLabel;

	 //
	 unsigned  int  uiBytesRecorded_perBlockAlign; uiBytesRecorded_perBlockAlign = 0;
	 AUDIO_COMPRESSOR_CFG  audioCompressor;
	 memset(&audioCompressor, 0, sizeof(audioCompressor));//= { 0 };
	 //
	 audioCompressor.playCfg  =  gAvParams.CONST_audioPlayCfg_07s;
	 uiBytesRecorded_perBlockAlign  =  MACRO_getuiBytesRecorded_perBlockAlign(  audioCompressor,  pwfx  );		



	 int	iCapTimeInMs; iCapTimeInMs = 40;
	 int  nBytes_toRecord; nBytes_toRecord = uiBytesRecorded_perBlockAlign * pwfx->nBlockAlign;
	 int  nAvgBytesPerSec; nAvgBytesPerSec = pwfx->nAvgBytesPerSec;
	 
	 if  (  !nAvgBytesPerSec  )  goto  errLabel;
	 iCapTimeInMs  =  nBytes_toRecord  *  1000  /  nAvgBytesPerSec;
	 if  (  !iCapTimeInMs  )  goto  errLabel;



	//  2017/01/28
	 //pRecThread->bQuit  =  FALSE;
	 pRecThread->bRunning  =  TRUE;
	 pRecordSoundProcInfo->usErrors_processInput  =  0;
	 
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)"",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "coreAudio starts"  )  );

	 //
	 broadcastRecorderStatus(  pQyMc  );
	 
	 //
	 int iVal_sleep; iVal_sleep = iCapTimeInMs * 0.7;

	 //
	 bool  bFailed_resample; bFailed_resample = false;

	//
	while  (  bDone  ==  FALSE  &&  !pRecThread->bQuit  )  
	{
		//
		if  (  bFailed_resample  )  break;

		//  Sleep for half the buffer duration
		//int  iVal  =  hnsActualDuration  /  REFTIMES_PER_MILLISEC  /  2;
		//Sleep(  hnsActualDuration  /  REFTIMES_PER_MILLISEC  /  2  );
		Sleep(  iVal_sleep  );

		hr  =  pCaptureClient->GetNextPacketSize(  &packetLength  );
		EXIT_ON_ERROR(  hr  );

		while  (  packetLength  !=  0  )  
		{
			hr  =  pCaptureClient->GetBuffer(
										&pData,
										&numFramesAvailable,
										&flags,  NULL,  NULL  );
			EXIT_ON_ERROR(  hr  );

			if  (  flags  &  AUDCLNT_BUFFERFLAGS_SILENT  )
			{
				pData  =  NULL;
			}

			//  Copy the available capture data to the audio sink
			//hr  =  pMySink->CopyData(  pData,  numFramesAvailable, &bDone  );
			//EXIT_ON_ERROR(  hr  );

			if  (  pData  )  {
				//
				int  dataLength  =  numFramesAvailable  *  pwfx->nBlockAlign;				
				char  *  gBuf  =  (  char  *  )pData;
				
				//
				if  (  dataLength  +  dataLen_pAudioDataBuf  <  bufSize_pAudioDataBuf  )  {				
					memcpy(  pAudioDataBuf  +  dataLen_pAudioDataBuf,  gBuf,  dataLength  );			
					dataLen_pAudioDataBuf  +=  dataLength;					
				}

				//
#ifdef  __DEBUG__
#if  0
				static uint stickCnt0=0;
				uint tickCnt1=myGetTickCount(null);
				int iDiffInMs = tickCnt1-stickCnt0;
				stickCnt0=tickCnt1;
				//
				traceLog((TCHAR*)  _T(  "numFramesAvailable %d, diffInMs %dms, packetLength %d. iSleep %dms"  ),  numFramesAvailable,  iDiffInMs,  packetLength, iVal_sleep  );
				//
				if ( pwfx->wFormatTag  ==  WAVE_FORMAT_EXTENSIBLE  )  {
					WAVEFORMATEXTENSIBLE  *  pwfe  =  (  WAVEFORMATEXTENSIBLE  *  )pwfx;
					char  *  fn  =  NULL;
					if(pwfe->SubFormat  ==  KSDATAFORMAT_SUBTYPE_PCM  )  {
						fn =  "c:\\tttbbb\\124\\mic_c.pcm";
					}
					else  if  (  pwfe->SubFormat  ==  KSDATAFORMAT_SUBTYPE_IEEE_FLOAT  )  {
						fn="c:\\tttbbb\\124\\mic_c_flt.pcm";
					}
					//
					if  (  fn  )  {
						FILE  *  fp  =  fopen(  fn,  "ab"  );
						if ( fp  )  {
							fwrite(  pData,  dataLength,  1,  fp  );
							fclose(fp);
						}
					}
				}
#endif
#endif
				//

				if  (  bNeed_resample  )  {

				
					for  (  ;  ;  )  {
						 if  (  dataLen_pAudioDataBuf  <  nBytes_toRecord  )  break;								
			 
						 //
						 if  (  !bFailed_resample  )
						 {						 
							   //
							   #ifdef  __DEBUG__
									   uint tickCnt3  =  myGetTickCount(  mynull  );												   
							   #endif
							   //
							   int  outputSize  =  bufSize_pResampleBuf  -  dataLen_pResampleBuf;					
							   if  (  GuiShare.pf_doResample(  pCtx_resample,  pAudioDataBuf,  nBytes_toRecord,  pResampleBuf  +  dataLen_pResampleBuf,  &outputSize  )  )  {
								   showInfo_open0(  0,  0,  _T(  "coreAudioRec failed, doResample failed"  )  );
								   bFailed_resample  =  true;		
							   }
							   else  {
									 //
									 #ifdef  __DEBUG__
											 if  (  0  )  {
												 uint  tickCnt4=myGetTickCount(mynull);							   
												 traceLog((TCHAR*)  _T(  "resample, diffInMs %dms, outputSize %d"  ),  tickCnt4  -  tickCnt3,  outputSize  );												   
												 //
											     char  *  fn = (char*)"c:\\tttbbb\\124\\resample_mic.pcm";
												 if  (  fn  )  {
													 FILE  *  fp  =  fopen(  fn,  "ab"  );								   
													 if ( fp  )  {
														 fwrite(  pResampleBuf  +  dataLen_pResampleBuf,  outputSize,  1,  fp  );
														 fclose(fp);														   
													 }												   
												 }
											 }
									 #endif							   
									 //							   
									 dataLen_pResampleBuf  +=  outputSize;						 
							   }
						 }

						 //						
						 for  (  ;  ;  )  {
							  if  (  dataLen_pResampleBuf  <  nBytes_toRecord_resample  )  break;

							  //
							  #ifdef  __DEBUG__
									  if  (  0  )  {
										  static  uint  stickCnt0  =  0;
										  uint  tickCnt1=myGetTickCount(  mynull  );
										  int  iDiffInMs  =  tickCnt1  -  stickCnt0;
										  stickCnt0  =  tickCnt1;
										  traceLog((TCHAR*)  _T(  "coreAudio: iDiff_last %dms, nByte_toRecord_resample %d"  ),  iDiffInMs,  nBytes_toRecord_resample  );
									  }
							  #endif
							  
							  //
						#if  10
							  ORG_audio_pkt pkt;
							  memset(  &pkt,  0,  offsetof(ORG_audio_pkt,buf  )  );
							  if(  nBytes_toRecord_resample  >  sizeof(  pkt.buf  )  )  {
								  showInfo_open0(  0,  0,  _T(  "coreAudio error, nBytes_toRecord_resample > sizeof(org_pkt.buf)"));
							  }
							  else  {
								    pkt.len  =  nBytes_toRecord_resample;
									memcpy(  pkt.buf,  pResampleBuf,  nBytes_toRecord_resample  );
									//
									
									if  (  q2PostMsgAndTrigger(  &pkt,  sizeof(  pkt  ),  &pRecordSoundProcInfo->aecThread.q2,_T("coreAudioRecThread"))) {
										traceLog((TCHAR*)  _T(  "coreAudio error: q2PostMsgAndTrigger failed, aec.q2"  )  );
										showInfo_open0(  0,  0,  _T(  "coreAudio error: q2PostMsgAndTrigger failed, aec.q2"  )  );
									}
									
							  }
						#endif

							  //
							  //processInput_post(  pProcInfo,  nAvgBytesPerSec,  (  BYTE  *  )pResampleBuf,  nBytes_toRecord_resample,  pMsgBuf  );				    					

							  //
							  memcpy(  pResampleBuf,  pResampleBuf  +  nBytes_toRecord_resample,  dataLen_pResampleBuf  -  nBytes_toRecord_resample  );
							  dataLen_pResampleBuf  -=  nBytes_toRecord_resample;							
						 }
			 
						 //			 
						 memcpy(  pAudioDataBuf,  pAudioDataBuf  +  nBytes_toRecord,  dataLen_pAudioDataBuf  -  nBytes_toRecord  );			 
						 dataLen_pAudioDataBuf  -=  nBytes_toRecord;			 		
					}				

				}

				//
			}


			//
			hr  =  pCaptureClient->ReleaseBuffer(  numFramesAvailable  );
			EXIT_ON_ERROR(  hr  );

			hr  =  pCaptureClient->GetNextPacketSize(  &packetLength  );
			EXIT_ON_ERROR(  hr  );

			//
			continue;
		}
		
		//
		//
		#ifdef  _DEBUG
				#if  0
					TCHAR	tBuf[128]  =  _T(  ""  );
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "get audio %d bytes\n"  ),  dataLen_pAudioDataBuf  );
					OutputDebugString(  tBuf  );
				#endif
		#endif


		#if  0
		for  (  ;  ;  )  {
			 if  (  dataLen_pAudioDataBuf  <  nBytes_toRecord  )  break;								
			 //
			 processInput_post(  pProcInfo,  nAvgBytesPerSec,  (  BYTE  *  )pAudioDataBuf,  nBytes_toRecord,  pMsgBuf  );				    					
			 memcpy(  pAudioDataBuf,  pAudioDataBuf  +  nBytes_toRecord,  dataLen_pAudioDataBuf  -  nBytes_toRecord  );
			 dataLen_pAudioDataBuf  -=  nBytes_toRecord;			 
		}
		#endif


		//
		continue;
	}


Exit:
errLabel:
	
	if  (  b_audioClient_started  )  {
		hr  =  pAudioClient->Stop(  );
		//  EXIT_ON_ERROR(  hr  );
	}

	//
	if  (  pwfx  )  CoTaskMemFree(  pwfx  );
	SAFE_RELEASE(  pEnumerator  );
	SAFE_RELEASE(  pDevice  );
	SAFE_RELEASE(  pAudioClient  );
	SAFE_RELEASE(  pCaptureClient  );

	//
	if(  pCtx_resample  )  {
		GuiShare.pf_exitResample(  pCtx_resample  );
	}


	//
	pRecThread->bRunning  =  FALSE;

	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)"",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "coreAudio ends"  )  );
	 
	 broadcastRecorderStatus(  pQyMc  );



	return  hr;
	
}









