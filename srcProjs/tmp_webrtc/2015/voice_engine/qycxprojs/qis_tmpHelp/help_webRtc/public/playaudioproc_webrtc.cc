

//#include	"stdafx.h"
#include	<tchar.h>
#include	<stdlib.h>

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

//
extern VoiceEngine* g_voe;
extern VoEBase* g_base;
//
extern  VoEAudioProcessing* g_ptrVoEAp;


//
typedef  int(*PF_inStream)(void  *  p0, void  *  p1, void  *  p2);


//
class  myInStream : public webrtc::InStream {
public:
	// Reads |len| bytes from file to |buf|. Returns the number of bytes read
	// or -1 on error.
	virtual int Read(void* buf, size_t len);

	//
	virtual int Rewind();

	//
	void  *  m_pPlayer;
	PF_inStream  m_pf_inStream;


};


//
int  myInStream::Read(void  * buf, size_t len)
{
	int  nRead;  nRead = 0;

	if (m_pf_inStream) {
		nRead = m_pf_inStream(m_pPlayer, buf, (  void  *  )len);
	}

	return  nRead;
}

int myInStream::Rewind()
{
	return  0;
}



//
typedef  struct  __voe_play_t {
				 VoEFile* g_file;	// = NULL;
				 int  g_ch;			// = -1;
				 //
				 myInStream  *  g_pinStream;
}		 VOE_play;



//
extern "C" __declspec(dllexport)  int voe_play_exit(void  **  ppVoePlay);


//
 //int  exitPlay_dx(  void  *  pDynLib_dx,  PLAY_AUDIO_procInfo  *  pPlayAudio,  myPLAY_SOUND_dx  *  p  );
 //__declspec(  dllexport  )  void  clean_myPLAY_AUDIO_DATA(  myPLAY_AUDIO_DATA  *  p,  LPCTSTR  hint  );





 //
 extern "C" __declspec(  dllexport  )  int voe_play_init( void  *  pPlayer,  PF_inStream  pf,  void  **  ppVoePlay )
 {
	 int  iErr  =  -1;

	 int  size = sizeof(VOE_play);
	 VOE_play  *  p = (  VOE_play  *  )malloc(size);
	 if (!p)  goto  errLabel;
	 memset(p, 0, sizeof(p[0]));
	 p->g_ch = -1;
	 //
	 *ppVoePlay = p;

	 //
	 p->g_file = VoEFile::GetInterface(g_voe);
	 p->g_ch = g_base->CreateChannel();

	 p->g_pinStream = new  myInStream;
	 if (!p->g_pinStream)  goto  errLabel;

	 p->g_pinStream->m_pPlayer = pPlayer;
	 p->g_pinStream->m_pf_inStream = pf;


	 //
	 int  iRet;
	 iRet = p->g_file->StartPlayingFileLocally(p->g_ch, p->g_pinStream);

	 g_base->StartPlayout(p->g_ch);


	 iErr  =  0;
errLabel:

	 if (iErr) {
		 voe_play_exit(ppVoePlay);
	 }

	 return  0;
 }


 extern "C" __declspec(  dllexport  )  int voe_play_exit( void  **  ppVoePlay )
 {
	 if (!ppVoePlay)  return  0;
	 VOE_play  *  p = *(  VOE_play  **  )ppVoePlay;
	 if (!p)  return  0;

	 if (p->g_ch != -1) {
		 g_base->StopPlayout(p->g_ch);  
	 }
	 if (p->g_file) {
		 p->g_file->StopPlayingFileLocally(p->g_ch);
	 }
	 //g_file->StopPlayingFileAsMicrophone(g_ch);

	 if (p->g_ch != -1) {
		 g_base->DeleteChannel(p->g_ch);  p->g_ch = -1;
	 }

	 if (p->g_file) {
		 p->g_file->Release();  p->g_file = 0;
	 }

	 //
	 if (p->g_pinStream) {
		 delete  p->g_pinStream;  p->g_pinStream = NULL;
	 }

	 //
	 free(p);
	 *ppVoePlay = 0;


	 return  0;
 }








