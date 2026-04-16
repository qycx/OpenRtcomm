

//#include	"stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <conio.h>
#include <assert.h>

#include <memory>
#include <vector>

#include "webrtc/base/ssladapter.h"
#include "webrtc/base/win32socketinit.h"
#include "webrtc/base/win32socketserver.h"
//
#include "webrtc/voice_engine/include/voe_audio_processing.h"
//
#include "webrtc/voice_engine/include/voe_hardware.h"

//
#include "webrtc\voice_engine\voe_file_impl.h"
#include "webrtc\voice_engine\include\voe_base.h"
#include "webrtc/modules/audio_device/include/audio_device.h"

#include "webrtc/modules/audio_device/include/audio_device.h"
#include "webrtc/common_audio/resampler/include/resampler.h"
//#include "webrtc/modules/audio_processing/aec/include/echo_cancellation.h"
#include "webrtc/common_audio/vad/include/webrtc_vad.h"
//#include "log.cpp"

//#include "dbgtool.h"
//#include "string_useful.h"


using namespace webrtc;
VoiceEngine* g_voe = NULL;
VoEBase* g_base = NULL;
//
VoEHardware* g_hardware = NULL;

//
VoEAudioProcessing* g_ptrVoEAp = NULL;



//
VoEFile* g_file_rec = NULL;
int  g_ch_rec = -1;

//
class my_outStream;
my_outStream  *  g_pOutStream  =  NULL;

//
extern  "C"  __declspec(dllexport)  int  voe_init();
extern  "C"  __declspec(dllexport)  int  voe_exit();


//
int  set_apm(VoEAudioProcessing  *  ptrVoEAp)
{
	//
	int  error;

	//
	error = ptrVoEAp->SetAgcStatus(1);
	if (error != 0)
	{
		printf("ERROR in VoEAudioProcess::SetAgcStatus\n");
		return error;

	}
	error = ptrVoEAp->SetEcStatus(1);
	if (error != 0)
	{
		printf("ERROR in VoEAudioProcess::SetEcStatus\n");
		return error;
	}
	error = ptrVoEAp->SetNsStatus(1);
	if (error != 0)
	{
		printf("ERROR in VoEAudioProcess::SetNsStatus\n");
		return error;
	}
#if  0
	error = ptrVoEAp->SetRxAgcStatus(audiochannel, 1);
	if (error != 0)
	{
		printf("ERROR in VoEAudioProcess::SetRxAgcStatus\n");
		return error;
	}
	error = ptrVoEAp->SetRxNsStatus(audiochannel, 1);
	if (error != 0)
	{
		printf("ERROR in VoEAudioProcess::SetRxNsStatus\n");
		return error;
	}
#endif

	return  0;

}


//
extern  "C"  __declspec(dllexport)  int  voe_init()
{
	rtc::InitializeSSL();

	g_voe = VoiceEngine::Create();
	//
	g_base = VoEBase::GetInterface(g_voe);
	//
	g_ptrVoEAp = webrtc::VoEAudioProcessing::GetInterface(  g_voe  );

	//
	g_hardware = VoEHardware::GetInterface(g_voe);


	//
	g_base->Init();



	return  0;
}

//
extern  "C"  __declspec(dllexport)  int  voe_exit()
{
	//
	g_base->Terminate();
	g_base->Release();
	//
	g_hardware->Release();
	//
	g_ptrVoEAp->Release();

	//
	VoiceEngine::Delete(g_voe);

	//
	rtc::CleanupSSL();

	return  0;
}

//
typedef  int(*PF_outStream)(void  *  p0, void  *  p1, void  *  p2);



//
class my_outStream : public OutStream
{
public:
	// Writes |len| bytes from |buf| to file. The actual writing may happen
	// some time later. Call Flush() to force a write.
	virtual bool Write(const void* buf, size_t len);
	virtual int Rewind();

public:
	void  *  m_pRecordSoundProcInfo;
	PF_outStream  m_pf_outStream;
	


};


bool  my_outStream::Write(const  void  *  buf, size_t  len)
{
	//
	if (m_pf_outStream) {
		m_pf_outStream(m_pRecordSoundProcInfo, (void  *)buf, (void  *)len);
	}

	return  true;
}

int  my_outStream::Rewind()
{
	return  0;
}




//
extern  "C"  __declspec(  dllexport  )  int  voe_record_init(  void  *  pRecordSoundProcInfo,  PF_outStream  pf  )
{
	//
	g_file_rec = VoEFile::GetInterface(g_voe);
	g_ch_rec = g_base->CreateChannel();

	//
	set_apm(g_ptrVoEAp);


	//
	g_pOutStream = new  my_outStream;
	//
	g_pOutStream->m_pRecordSoundProcInfo = pRecordSoundProcInfo;
	g_pOutStream->m_pf_outStream = pf;

	//
	CodecInst  cinst;
#if  0
	int pltype;
	char plname[RTP_PAYLOAD_NAME_SIZE];
	int plfreq;
	int pacsize;
	size_t channels;
	int rate;  // bits/sec unlike {start,min,max}Bitrate elsewhere in this file!
#endif 
	//{108, "L16", 16000, 160, 1, 256000},

	//初始化L16编解码器参数  	
	strcpy(cinst.plname, "L16");
	

	cinst.plfreq = 16000; // iSAC宽带模式取样频率  
	cinst.pltype = 108;
	cinst.pacsize = 160;   //使用30ms packet size，480kbps  
	cinst.channels = 1;     // 单声道  
	cinst.rate = 256000;    // 信道自适应模式  
	//
	g_file_rec->StartRecordingMicrophone(g_pOutStream,  &cinst);//开始捕获pcm流


	return  0;
}

//
extern  "C"  __declspec(dllexport)  int  voe_record_exit()
{
	//
	g_file_rec->StopRecordingMicrophone();

	//
	if (g_pOutStream) {
		delete  g_pOutStream;  g_pOutStream = NULL;
	}
	//
	if (g_ch_rec != -1) {
		g_base->DeleteChannel(g_ch_rec);  g_ch_rec = -1;
	}
	if (g_file_rec) {
		g_file_rec->Release();  g_file_rec = NULL;
	}

	return  0;
}
   
#include<tchar.h>

//
extern  "C"  __declspec(dllexport)  int  list_device_webRtc(  char  *  recorder_buf,  int  size,  char  *  recorder_selected_utf8  )
{
	TCHAR  tBuf[128] = _T("");
	int  res;
	int rd;  rd = -1;
	int  pd;  pd = -1;
	res = g_hardware->GetNumOfRecordingDevices(rd);
	//VALIDATE;
	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T("Recording devices (%d): \n"  ), rd);
	OutputDebugString(tBuf);

	char dn[128] = { 0 };
	char guid[128] = { 0 };

	//
	for (int j = 0; j < rd; ++j) {
		res = g_hardware->GetRecordingDeviceName(j, dn, guid);
		//VALIDATE;
		_sntprintf(tBuf, sizeof(tBuf) / sizeof(tBuf[0]), _T("  %d: %S \n"), j, dn);
		OutputDebugString(tBuf);
		//
		if (recorder_buf) {
			if (strlen(dn) < size) {
				strcpy(recorder_buf, dn);
			}
		}
		//
		if (recorder_selected_utf8) {		
			if (!strcmp(recorder_selected_utf8, dn)) {			
				OutputDebugString(_T("Selected\n"));		
			}	
		}
	}

	return  0;

}


#if  0
//
extern  "C"  __declspec(dllexport)  int  start_recordAudio_webRtc(  void  *  pRecordSoundProcInfo  )
{
	int			iErr  =  -1;


	//
	voe_record_init(  pRecordSoundProcInfo,  pf  );

	

	iErr  =  0;
//errLabel:

	if  (  iErr  )  {
		stop_recordAudio_webRtc(  pRecordSoundProcInfo  );
	}
	return  iErr;
}


extern  "C"  __declspec(  dllexport  )  int  stop_recordAudio_webRtc(  void  *  pRecordSoundProcInfo  )
{

	
	voe_record_exit();

	return  0;
}
#endif






 






