/**********
This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
**********/
// Copyright (c) 1996-2014, Live Networks, Inc.  All rights reserved
// A common framework, used for the "openRTSP" and "playSIP" applications
// Implementation
//
// NOTE: If you want to develop your own RTSP client application (or embed RTSP client functionality into your own application),
// then we don't recommend using this code as a model, because it is too complex (with many options).
// Instead, we recommend using the "testRTSPClient" application code as a model.

#include	"stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>
#include	<stddef.h>
#include	<mmsystem.h>
#include    <string>


#include <iostream>
#include <sstream>

#include	"rtspCliHelpCommon.h"

#include	"OutputFile.hh"

#include "myplayCommon.hh"
#include "BasicUsageEnvironment.hh"
#include "GroupsockHelper.hh"

#include "qvcfDefs.h"


#if defined(__WIN32__) || defined(_WIN32)
#define snprintf _snprintf
#else
#include <signal.h>
#define USE_SIGNALS 1
#endif

extern "C" { FILE __iob_func[3] = { *stdin,*stdout,*stderr }; }

//
GBUF_rtspCliHelp	gBuf_rtspCliHelp;
BOOL				bDone_set_PF_BufferCB_rtsp  =  FALSE;
QIS_guiOpen			g_guiOpen;

//
bool  g_bDbg = false;

//
bool  bRespCliQuit();


//  #define DUMMY_SINK_RECEIVE_BUFFER_SIZE 100000
#define DUMMY_SINK_RECEIVE_BUFFER_SIZE 8  *  100000



#ifdef  _DEBUG
		//
		//
 
#endif



// Forward function definitions:
void continueAfterClientCreation0(RTSPClient* client, Boolean requestStreamingOverTCP);
void continueAfterClientCreation1();
void continueAfterOPTIONS(RTSPClient* client, int resultCode, char* resultString);
void continueAfterDESCRIBE(RTSPClient* client, int resultCode, char* resultString);
void continueAfterSETUP(RTSPClient* client, int resultCode, char* resultString);
void continueAfterPLAY(RTSPClient* client, int resultCode, char* resultString);
void continueAfterTEARDOWN(RTSPClient* client, int resultCode, char* resultString);

void createOutputFiles(char const* periodicFilenameSuffix);
void createPeriodicOutputFiles();
void setupStreams();
void closeMediaSinks();
void subsessionAfterPlaying(void* clientData);
void subsessionByeHandler(void* clientData);
void sessionAfterPlaying(void* clientData = NULL);
void sessionTimerHandler(void* clientData);
void periodicFileOutputTimerHandler(void* clientData);
void shutdown(int exitCode = 1);
void signalHandlerShutdown(int sig);
void checkForPacketArrival(void* clientData);
void checkInterPacketGaps(void* clientData);
void beginQOSMeasurement();

char const* progName;
UsageEnvironment* env;
Medium* ourClient = NULL;
Authenticator* ourAuthenticator = NULL;
char const* streamURL = NULL;
MediaSession* session = NULL;
TaskToken sessionTimerTask = NULL;
TaskToken arrivalCheckTimerTask = NULL;
TaskToken interPacketGapCheckTimerTask = NULL;
TaskToken qosMeasurementTimerTask = NULL;
TaskToken periodicFileOutputTask = NULL;
Boolean createReceivers = True;
Boolean outputQuickTimeFile = False;
Boolean generateMP4Format = False;
QuickTimeFileSink* qtOut = NULL;
Boolean outputAVIFile = False;
AVIFileSink* aviOut = NULL;
Boolean audioOnly = False;
Boolean videoOnly = False;
char const* singleMedium = NULL;
int verbosityLevel = 1; // by default, print verbose output
double duration = 0;
double durationSlop = -1.0; // extra seconds to play at the end
double initialSeekTime = 0.0f;
char* initialAbsoluteSeekTime = NULL;
float scale = 1.0f;
double endTime;
unsigned interPacketGapMaxTime = 0;
unsigned totNumPacketsReceived = ~0; // used if checking inter-packet gaps
Boolean playContinuously = False;
int simpleRTPoffsetArg = -1;
Boolean sendOptionsRequest = True;
Boolean sendOptionsRequestOnly = False;
Boolean oneFilePerFrame = False;
Boolean notifyOnPacketArrival = False;
Boolean streamUsingTCP = False;
Boolean forceMulticastOnUnspecified = False;
unsigned short desiredPortNum = 0;
portNumBits tunnelOverHTTPPortNum = 0;
char* username = NULL;
char* password = NULL;
char* proxyServerName = NULL;
unsigned short proxyServerPortNum = 0;
unsigned char desiredAudioRTPPayloadFormat = 0;
char* mimeSubtype = NULL;
unsigned short movieWidth = 240; // default
Boolean movieWidthOptionSet = False;
unsigned short movieHeight = 180; // default
Boolean movieHeightOptionSet = False;
unsigned movieFPS = 15; // default
Boolean movieFPSOptionSet = False;
char const* fileNamePrefix = "";
unsigned fileSinkBufferSize = 2  *  100000;	//  100000;	//  2014/03/23
unsigned socketInputBufferSize = 0;
Boolean packetLossCompensate = False;
Boolean syncStreams = False;
Boolean generateHintTracks = False;
Boolean waitForResponseToTEARDOWN = True;
unsigned qosMeasurementIntervalMS = 0; // 0 means: Don't output QOS data
char* userAgent = NULL;
unsigned fileOutputInterval = 0; // seconds
unsigned fileOutputSecondsSoFar = 0; // seconds
Boolean createHandlerServerForREGISTERCommand = False;
portNumBits handlerServerForREGISTERCommandPortNum = 0;
HandlerServerForREGISTERCommand* handlerServerForREGISTERCommand;
char* usernameForREGISTER = NULL;
char* passwordForREGISTER = NULL;
UserAuthenticationDatabase* authDBForREGISTER = NULL;

struct timeval startTime;

void usage() {
  *env << "Usage: " << progName
       << " [-p <startPortNum>] [-r|-q|-4|-i] [-a|-v] [-V] [-d <duration>] [-D <max-inter-packet-gap-time> [-c] [-S <offset>] [-n] [-O]"
	   << (controlConnectionUsesTCP ? " [-t|-T <http-port>]" : "")
       << " [-u <username> <password>"
	   << (allowProxyServers ? " [<proxy-server> [<proxy-server-port>]]" : "")
       << "]" << (supportCodecSelection ? " [-A <audio-codec-rtp-payload-format-code>|-M <mime-subtype-name>]" : "")
       << " [-s <initial-seek-time>]|[-U <absolute-seek-time>] [-z <scale>] [-g user-agent]"
       << " [-k <username-for-REGISTER> <password-for-REGISTER>]"
       << " [-P <interval-in-seconds>]"
       << " [-w <width> -h <height>] [-f <frames-per-second>] [-y] [-H] [-Q [<measurement-interval>]] [-F <filename-prefix>] [-b <file-sink-buffer-size>] [-B <input-socket-buffer-size>] [-I <input-interface-ip-address>] [-m] [<url>|-R [<port-num>]] (or " << progName << " -o [-V] <url>)\n";
  shutdown();
}


//////////////////////////
class CMyDummySink: public FileSink {
public:
  static CMyDummySink* createNew(UsageEnvironment& env,
			      MediaSubsession& subsession, // identifies the kind of data that's being received
			      char const* streamId = NULL); // identifies the stream itself (optional)

private:
  //  CMyDummySink(UsageEnvironment& env, MediaSubsession& subsession, char const* streamId);
  CMyDummySink(UsageEnvironment& env, MediaSubsession& subsession, FILE  *  fid,  unsigned  bufferSize,  char const* streamId);


    // called only by "createNew()"
  virtual ~CMyDummySink();

  static void afterGettingFrame(void* clientData, unsigned frameSize,
                                unsigned numTruncatedBytes,
				struct timeval presentationTime,
                                unsigned durationInMicroseconds);
  virtual void afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
			 struct timeval presentationTime, unsigned durationInMicroseconds);

private:
  // redefined virtual functions:
  virtual Boolean continuePlaying();

private:
  u_int8_t* fReceiveBuffer;
  MediaSubsession& fSubsession;
  char* fStreamId;
  //
  BOOL fHaveWrittenFirstFrame;

};


// Implementation of "DummySink":

// Even though we're not going to be doing anything with the incoming data, we still need to receive it.
// Define the size of the buffer that we'll use:

CMyDummySink* CMyDummySink::createNew(UsageEnvironment& env, MediaSubsession& subsession, char const* streamId) {
	FILE  *  fid  =  stdout;
  return new CMyDummySink(env, subsession, fid,  DUMMY_SINK_RECEIVE_BUFFER_SIZE,  streamId);
}

CMyDummySink::CMyDummySink(UsageEnvironment& env, MediaSubsession& subsession, FILE  *  fid,  unsigned  bufferSize,  char const* streamId)
  : FileSink(env,  fid,  bufferSize,  streamId  ),
    fSubsession(subsession) {
  fStreamId = strDup(streamId);
  fReceiveBuffer = new u_int8_t[DUMMY_SINK_RECEIVE_BUFFER_SIZE];
  //
  fHaveWrittenFirstFrame  =  FALSE;

}

CMyDummySink::~CMyDummySink() {
  delete[] fReceiveBuffer;
  delete[] fStreamId;
}

void CMyDummySink::afterGettingFrame(void* clientData, unsigned frameSize, unsigned numTruncatedBytes,
				  struct timeval presentationTime, unsigned durationInMicroseconds) {
  CMyDummySink* sink = (CMyDummySink*)clientData;
  sink->afterGettingFrame(frameSize, numTruncatedBytes, presentationTime, durationInMicroseconds);
}

// If you don't want to see debugging output for each received frame, then comment out the following line:
#define DEBUG_PRINT_EACH_RECEIVED_FRAME 1

void CMyDummySink::afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
				  struct timeval presentationTime, unsigned /*durationInMicroseconds*/) {
  // We've just received a frame of data.  (Optionally) print out information about it:
#ifdef DEBUG_PRINT_EACH_RECEIVED_FRAME
  if (fStreamId != NULL) envir() << "Stream \"" << fStreamId << "\"; ";
  envir() << fSubsession.mediumName() << "/" << fSubsession.codecName() << ":\tReceived " << frameSize << " bytes";
  if (numTruncatedBytes > 0) envir() << " (with " << numTruncatedBytes << " bytes truncated)";
  char uSecsStr[6+1]; // used to output the 'microseconds' part of the presentation time
  sprintf(uSecsStr, "%06u", (unsigned)presentationTime.tv_usec);
  envir() << ".\tPresentation time: " << (int)presentationTime.tv_sec << "." << uSecsStr;
  if (fSubsession.rtpSource() != NULL && !fSubsession.rtpSource()->hasBeenSynchronizedUsingRTCP()) {
    envir() << "!"; // mark the debugging output to indicate that this presentation time is not RTCP-synchronized
  }
#ifdef DEBUG_PRINT_NPT
  envir() << "\tNPT: " << fSubsession.getNormalPlayTime(presentationTime);
#endif
  envir() << "\n";
#endif
  
  int  iErr  =  -1;


  //
  if  (  !gBuf_rtspCliHelp.pMediaDataForSpl_toPost  ||  !gBuf_rtspCliHelp.pStreamDataQ  )  
	  goto  errLabel;

  //
#if  0
  if  (  gBuf_rtspCliHelp.spl.bStopped  )
	  goto  errLabel;
#endif 
  if (bRespCliQuit()) {
	  goto  errLabel;
  }

 
#if  10

	
  //  送到splitter去	
  QDC_MEDIA_data  *  pMediaData  =  (  QDC_MEDIA_data  *  )gBuf_rtspCliHelp.pMediaDataForSpl_toPost;
  if  (  frameSize  >  sizeof(  pMediaData->buf  )  )  {
	  #ifdef  _DEBUG					
			  OutputDebugString(  _T(  "Err: mediaData_forSplitter too small\n"  )  );
	  #endif		
	  dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  _T(  "sink::afterGettingFrame failed: mediaData too small"  )  );
	  goto  errLabel;			
  }			 
  pMediaData->head.uiLen  =  frameSize;
	
  //  
  memcpy(  pMediaData->buf,  this->fReceiveBuffer,  pMediaData->head.uiLen  );
			
  //	
  int  len  =  offsetof(  QDC_MEDIA_data,  buf  )  +  pMediaData->head.uiLen;	
  if  (  isCliHelp_streamDataQ_qPostMsg(  pMediaData,  len,  gBuf_rtspCliHelp.pStreamDataQ  )  )  {		  
	  goto  errLabel;
  }

  TCHAR  tBuf[128];
#ifdef  _DEBUG
  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qPostMsg ok, streamDataQ %d, len %d\n"  ),  isCliHelp_streamDataQ_qNodes(  gBuf_rtspCliHelp.pStreamDataQ,  0,  0  ),  len  );
  OutputDebugString(  tBuf  );
#endif
   	
  //
  int  cnt  =  isCliHelp_streamDataQ_qNodes(  gBuf_rtspCliHelp.pStreamDataQ,  0,  0  );
  int  iWaitInMs  =   0;  
  if  (  !gBuf_rtspCliHelp.spl.bInited_splInfo  )  {
	  //
	  if  (  cnt  >  CONST_qNodes_toInitSpl  )  {	//  放慢一点
		  iWaitInMs  =  10;
		  Sleep(  iWaitInMs  );
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Sink::afterGettingFrame: Sleep(  %dms  ). qNodes %d, not inited\n"  ),  iWaitInMs,  cnt  );
		  dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  tBuf  );
	  }
  }

  //
  iWaitInMs  =   0;  
  if  (  cnt  >  gBuf_rtspCliHelp.uiMaxQNodes_streamDataQ  *  2  -  40  )  {
	  iWaitInMs  =  25;
  }
  else if  (  cnt  >  60  )  {
		   iWaitInMs  =  10;
  }
  if  (  iWaitInMs  )  {
	  Sleep(  iWaitInMs  );		
	  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Sink::afterGettingFrame: Sleep(  %dms  ). qNodes %d\n"  ),  iWaitInMs,  cnt  );
	  dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  tBuf  );
  }

#endif


  
  // Then continue, to request the next frame of data:
  continuePlaying();


  iErr  =  0;
errLabel:
  if  (  iErr  )  {
	  signalHandlerShutdown(  1  );
  }
}

Boolean CMyDummySink::continuePlaying() {
  if (fSource == NULL) return False; // sanity check (should not happen)

  // Request the next frame of data from our input source.  "afterGettingFrame()" will get called later, when it arrives:
  fSource->getNextFrame(fReceiveBuffer, DUMMY_SINK_RECEIVE_BUFFER_SIZE,
                        afterGettingFrame, this,
                        onSourceClosure, this);
  return True;
}


//////////////////////////
class CMyPcmaSink : public FileSink {
public:
	static CMyPcmaSink* createNew(UsageEnvironment& env,
		MediaSubsession& subsession, // identifies the kind of data that's being received
		int sample, int config,
		char const* streamId = NULL); // identifies the stream itself (optional)

private:
	//  CMyDummySink(UsageEnvironment& env, MediaSubsession& subsession, char const* streamId);
	CMyPcmaSink(UsageEnvironment& env, MediaSubsession& subsession, FILE* fid, unsigned  bufferSize, char const* streamId, uint32_t sample, uint32_t config);


	// called only by "createNew()"
	virtual ~CMyPcmaSink();

	static void afterGettingFrame(void* clientData, unsigned frameSize,
		unsigned numTruncatedBytes,
		struct timeval presentationTime,
		unsigned durationInMicroseconds);
	virtual void afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
		struct timeval presentationTime, unsigned durationInMicroseconds);

private:
	// redefined virtual functions:
	virtual Boolean continuePlaying();

private:
	u_int8_t* fReceiveBuffer;
	MediaSubsession& fSubsession;
	char* fStreamId;
	//
	BOOL fHaveWrittenHead;
	uint32_t m_sample;
	uint32_t m_config;
	
};


// Implementation of "DummySink":

// Even though we're not going to be doing anything with the incoming data, we still need to receive it.
// Define the size of the buffer that we'll use:

CMyPcmaSink* CMyPcmaSink::createNew(UsageEnvironment& env, MediaSubsession& subsession, int sample, int config, char const* streamId) {
	FILE* fid = stdout;
	return new CMyPcmaSink(env, subsession, fid, DUMMY_SINK_RECEIVE_BUFFER_SIZE, streamId, sample, config);
}

CMyPcmaSink::CMyPcmaSink(UsageEnvironment& env, MediaSubsession& subsession, FILE* fid, unsigned  bufferSize, char const* streamId, 
	uint32_t sample, uint32_t config)
	: FileSink(env, fid, bufferSize, streamId),
	fSubsession(subsession) {
	fStreamId = strDup(streamId);
	fReceiveBuffer = new u_int8_t[DUMMY_SINK_RECEIVE_BUFFER_SIZE];
	//
	fHaveWrittenHead = FALSE;

	this->m_config = config;
	this->m_sample = sample;

	
	
}

CMyPcmaSink::~CMyPcmaSink() {
	delete[] fReceiveBuffer;
	delete[] fStreamId;

	
}

#define			CONST_codecType_null			0
#define			CONST_codecType_h264			1
//  #define		CONST_codecType_MP2T			2
#define			CONST_codecType_HEVC			3		//  2017/10/08
#define			CONST_codecType_PCMA			4


void CMyPcmaSink::afterGettingFrame(void* clientData, unsigned frameSize, unsigned numTruncatedBytes,
	struct timeval presentationTime, unsigned durationInMicroseconds) {
	CMyPcmaSink* sink = (CMyPcmaSink*)clientData;
	sink->afterGettingFrame(frameSize, numTruncatedBytes, presentationTime, durationInMicroseconds);
}



// If you don't want to see debugging output for each received frame, then comment out the following line:
#define DEBUG_PRINT_EACH_RECEIVED_FRAME 1

#define		CONST_audioCompressors_ffmpeg							21
#define		CONST_videoCompressors_ffmpeg							22

#define		CONST_audioCompressors_aac   							25

void CMyPcmaSink::afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
	struct timeval presentationTime, unsigned /*durationInMicroseconds*/) {
	// We've just received a frame of data.  (Optionally) print out information about it:
#ifdef DEBUG_PRINT_EACH_RECEIVED_FRAME
	if (fStreamId != NULL) envir() << "Stream \"" << fStreamId << "\"; ";
	envir() << fSubsession.mediumName() << "/" << fSubsession.codecName() << ":\tReceived " << frameSize << " bytes";
	if (numTruncatedBytes > 0) envir() << " (with " << numTruncatedBytes << " bytes truncated)";
	char uSecsStr[6 + 1]; // used to output the 'microseconds' part of the presentation time
	sprintf(uSecsStr, "%06u", (unsigned)presentationTime.tv_usec);
	envir() << ".\tPresentation time: " << (int)presentationTime.tv_sec << "." << uSecsStr;
	if (fSubsession.rtpSource() != NULL && !fSubsession.rtpSource()->hasBeenSynchronizedUsingRTCP()) {
		envir() << "!"; // mark the debugging output to indicate that this presentation time is not RTCP-synchronized
	}
#ifdef DEBUG_PRINT_NPT
	envir() << "\tNPT: " << fSubsession.getNormalPlayTime(presentationTime);
#endif
	envir() << "\n";
#endif

	int  iErr = -1;


	if (gBuf_rtspCliHelp.common.pf_BufferCB_rtsp) {

		
		int		iMediumType = CONST_mediumType_audio;
		int		iCodecType = CONST_codecType_PCMA;

		unsigned  __int64  ui64ValInMs = presentationTime.tv_sec * 1000 + presentationTime.tv_usec / 1000;
		unsigned  int  uiPts = 0;	
		bool  bNeedResp = false;	


		if (!fHaveWrittenHead) {
			char  buf[2048] = "";

			/*
			QY_AUDIO_HEADER ah;
			ah.wfx.wFormatTag = WAVE_FORMAT_PCM;
			int len = sizeof(ah);
			memcpy(buf, &ah, len);

			CB_rtsp_res  res;
			memset(&res, 0, sizeof(res));
			if (gBuf_rtspCliHelp.common.pf_BufferCB_rtsp(&gBuf_rtspCliHelp, gBuf_rtspCliHelp.common.iIndex_capProcInfo,
				iMediumType, iCodecType, ui64ValInMs, uiPts, CONST_vcfDataType_ah, (unsigned  char*)buf, len, TRUE, 0, FALSE, bNeedResp, &res)) {
				goto  errLabel;
			}*/

			buf[0] = CONST_audioCompressors_aac;

			int bufLen = 1;

			uint32_t netSample = htonl(m_sample); 
			std::memcpy(buf+ bufLen, &netSample, sizeof(netSample));
			bufLen += sizeof(netSample);

			uint32_t netConfig = htonl(m_config);
			std::memcpy(buf + bufLen, &netConfig, sizeof(netConfig));
			bufLen += sizeof(netConfig);

			CB_rtsp_res  res;
			memset(&res, 0, sizeof(res));
			if (gBuf_rtspCliHelp.common.pf_BufferCB_rtsp(&gBuf_rtspCliHelp, gBuf_rtspCliHelp.common.iIndex_capProcInfo,
				iMediumType, iCodecType, ui64ValInMs, uiPts, CONST_vcfDataType_ucCompressors, (unsigned  char*)buf, bufLen, TRUE, 0, FALSE, bNeedResp, &res)) {
				goto  errLabel;
			}
  
			fHaveWrittenHead = True; // for next time  

		}		

		CB_rtsp_res  res;
		memset(&res, 0, sizeof(res));
		if (gBuf_rtspCliHelp.common.pf_BufferCB_rtsp(&gBuf_rtspCliHelp, gBuf_rtspCliHelp.common.iIndex_capProcInfo,
			iMediumType, iCodecType, ui64ValInMs, uiPts, 0, this->fReceiveBuffer, frameSize, FALSE, 0, FALSE, bNeedResp, &res)) {
			goto  errLabel;
		}
		

		//
#ifdef  _DEBUG

#if  10
		static  bool  bClean = FALSE;
		FILE* fp = NULL;
		char* fn = "c:\\tttbbb\\kk.aac";
		if (!bClean) {
			fp = fopen(fn, "wb");
			if (fp) {
				fclose(fp);  fp = NULL;
			}
			bClean = TRUE;;
		}
		if (bClean) {
			fp = fopen(fn, "ab+");
			if (fp) {
				fwrite(this->fReceiveBuffer, frameSize, 1, fp);
				fclose(fp);  fp = NULL;
			}
		}
#endif
		
#endif

	}

	// Then continue, to request the next frame of data:
	continuePlaying();


	iErr = 0;
errLabel:
	if (iErr) {
		signalHandlerShutdown(1);
	}
}

Boolean CMyPcmaSink::continuePlaying() {
	if (fSource == NULL) return False; // sanity check (should not happen)

	// Request the next frame of data from our input source.  "afterGettingFrame()" will get called later, when it arrives:
	fSource->getNextFrame(fReceiveBuffer, DUMMY_SINK_RECEIVE_BUFFER_SIZE,
		afterGettingFrame, this,
		onSourceClosure, this);
	return True;
}


/////////////////////////  2014/02/22
class CMyH264Sink: public H264VideoFileSink {
public:
    static CMyH264Sink* createNew(UsageEnvironment& env, char const* fileName, int  CodecType,
				      char const* sPropParameterSetsStr = NULL,
      // "sPropParameterSetsStr" is an optional 'SDP format' string
      // (comma-separated Base64-encoded) representing SPS and/or PPS NAL-units
      // to prepend to the output
				      unsigned bufferSize = 100000,
				      Boolean oneFilePerFrame = False);
	static CMyH264Sink* createNew(UsageEnvironment& env, char const* fileName, int  CodecType,
		char const* sPropParameterSetsStr1 = NULL,
		char const* sPropParameterSetsStr2 = NULL,
		char const* sPropParameterSetsStr3 = NULL,
		// "sPropParameterSetsStr" is an optional 'SDP format' string
		// (comma-separated Base64-encoded) representing SPS and/or PPS NAL-units
		// to prepend to the output
		unsigned bufferSize = 100000,
		Boolean oneFilePerFrame = False);
      // See "FileSink.hh" for a description of these parameters.

private:
	CMyH264Sink(UsageEnvironment& env, FILE* fid, int  CodecType,
		    char const* sPropParameterSetsStr,
		    unsigned bufferSize, char const* perFrameFileNamePrefix);
	CMyH264Sink(UsageEnvironment& env, FILE* fid, int  CodecType,
		char const* sPropParameterSetsStr1,
		char const* sPropParameterSetsStr2,
		char const* sPropParameterSetsStr3,
		unsigned bufferSize, char const* perFrameFileNamePrefix);
      // called only by createNew()
  virtual ~CMyH264Sink();

  static void afterGettingFrame(void* clientData, unsigned frameSize,
                                unsigned numTruncatedBytes,
				struct timeval presentationTime,
                                unsigned durationInMicroseconds);
  void afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
			 struct timeval presentationTime, unsigned durationInMicroseconds);

private:
  // redefined virtual functions:
  virtual Boolean continuePlaying();

#if  10
private:
  u_int8_t* fReceiveBuffer;
  //MediaSubsession& fSubsession;
  char* fStreamId;
  int   iCodeType;
  //
  BOOL fHaveWrittenFirstFrame;
  char const* fSPropParameterSetsStr[3];

#endif
};

// Even though we're not going to be doing anything with the incoming data, we still need to receive it.
// Define the size of the buffer that we'll use:

CMyH264Sink
::CMyH264Sink(UsageEnvironment& env, FILE* fid, int  CodecType,
		    char const* sPropParameterSetsStr,
		    unsigned bufferSize, char const* perFrameFileNamePrefix)
  : H264VideoFileSink(env, fid, sPropParameterSetsStr,  bufferSize, perFrameFileNamePrefix  ) 
{
	//
	char const* streamId  =  "kk";
	//
	fStreamId = strDup(streamId);
	fReceiveBuffer = new u_int8_t[DUMMY_SINK_RECEIVE_BUFFER_SIZE];
	fHaveWrittenFirstFrame  =  FALSE;
	//
	fSPropParameterSetsStr[0] = sPropParameterSetsStr;
	fSPropParameterSetsStr[1] = 0;
	fSPropParameterSetsStr[2] = 0;

	iCodeType = CodecType;
}

CMyH264Sink
::CMyH264Sink(UsageEnvironment& env, FILE* fid, int  CodecType,
	char const* sPropParameterSetsStr1,
	char const* sPropParameterSetsStr2,
	char const* sPropParameterSetsStr3,
	unsigned bufferSize, char const* perFrameFileNamePrefix)
	: H264VideoFileSink(env, fid, sPropParameterSetsStr1, sPropParameterSetsStr2, sPropParameterSetsStr3, bufferSize, perFrameFileNamePrefix)
{
	//
	char const* streamId = "kk";
	//
	fStreamId = strDup(streamId);
	fReceiveBuffer = new u_int8_t[DUMMY_SINK_RECEIVE_BUFFER_SIZE];
	fHaveWrittenFirstFrame = FALSE;
	//
	fSPropParameterSetsStr[0] = sPropParameterSetsStr1;
	fSPropParameterSetsStr[1] = sPropParameterSetsStr2;
	fSPropParameterSetsStr[2] = sPropParameterSetsStr3;

	iCodeType = CodecType;


}

CMyH264Sink::~CMyH264Sink() {
	//
	delete[] fReceiveBuffer; 
	delete[] fStreamId;
}

CMyH264Sink*
CMyH264Sink::createNew(UsageEnvironment& env, char const* fileName, int  CodecType,
			     char const* sPropParameterSetsStr,
			     unsigned bufferSize, Boolean oneFilePerFrame) {
  do {
    FILE* fid;
    char const* perFrameFileNamePrefix;
    if (oneFilePerFrame) {
      // Create the fid for each frame
      fid = NULL;
      perFrameFileNamePrefix = fileName;
    } else {
      // Normal case: create the fid once
      //fid = OpenOutputFile(env, fileName);
	  fid = stdout;	//  2014/03/02
      if (fid == NULL) break;
      perFrameFileNamePrefix = NULL;
    }

    return new CMyH264Sink(env, fid, CodecType, sPropParameterSetsStr, bufferSize, perFrameFileNamePrefix);
  } while (0);

  return NULL;
}

CMyH264Sink*
CMyH264Sink::createNew(UsageEnvironment& env, char const* fileName, int  CodecType,
	char const* sPropParameterSetsStr1,
	char const* sPropParameterSetsStr2,
	char const* sPropParameterSetsStr3,
	unsigned bufferSize, Boolean oneFilePerFrame) {
	do {
		FILE* fid;
		char const* perFrameFileNamePrefix;
		if (oneFilePerFrame) {
			// Create the fid for each frame
			fid = NULL;
			perFrameFileNamePrefix = fileName;
		}
		else {
			// Normal case: create the fid once
			//fid = OpenOutputFile(env, fileName);
			fid = stdout;	//  2014/03/02
			if (fid == NULL) break;
			perFrameFileNamePrefix = NULL;
		}

		return new CMyH264Sink(env, fid, CodecType, sPropParameterSetsStr1, sPropParameterSetsStr2, sPropParameterSetsStr3, bufferSize, perFrameFileNamePrefix);
	} while (0);

	return NULL;
}

void CMyH264Sink::afterGettingFrame(void* clientData, unsigned frameSize, unsigned numTruncatedBytes,
				  struct timeval presentationTime, unsigned durationInMicroseconds) {
  CMyH264Sink* sink = (CMyH264Sink*)clientData;
  sink->afterGettingFrame(frameSize, numTruncatedBytes, presentationTime, durationInMicroseconds);
}


BOOL  bStartCodeExistsFunc(  unsigned  char  *  fBuffer,  int  frameSize  )
{
	BOOL	bStartCodeExists  =  FALSE;
	
	  if  (  frameSize  >=  4  )  {
		  if  (  fBuffer[0]  ==  0
			  &&  fBuffer[1]  ==  0  )
		  {
			  if  (  fBuffer[2]  ==  1  )  {
				  bStartCodeExists  =  TRUE;
				  }
			  else  if  (  fBuffer[2]  ==  0
						&&  fBuffer[3]  ==  1  )
			  {
				  bStartCodeExists  =  TRUE;
			  }
		  }
	  }

	  return  bStartCodeExists;
}


//  2014/08/10
void mysignalHandlerShutdown(int /*sig*/) 
{
	//
	dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  _T(  "mysignalHandlerShutdown called. exit now"  )  );
	Sleep(  100  );

	//
	exit(  0  );
}


// If you don't want to see debugging output for each received frame, then comment out the following line:
//  #define DEBUG_PRINT_EACH_RECEIVED_FRAME 1

void CMyH264Sink::afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
				  struct timeval presentationTime, unsigned /*durationInMicroseconds*/) {
  // We've just received a frame of data.  (Optionally) print out information about it:
#ifdef DEBUG_PRINT_EACH_RECEIVED_FRAME
  if (fStreamId != NULL) envir() << "Stream \"" << fStreamId << "\"; ";
  //  envir() << fSubsession.mediumName() << "/" << fSubsession.codecName() << ":\tReceived " << frameSize << " bytes";
  envir() << ":\tReceived " << frameSize << " bytes";
  //
  if (numTruncatedBytes > 0) envir() << " (with " << numTruncatedBytes << " bytes truncated)";
  char uSecsStr[6+1]; // used to output the 'microseconds' part of the presentation time
  sprintf(uSecsStr, "%06u", (unsigned)presentationTime.tv_usec);
  envir() << ".\tPresentation time: " << (int)presentationTime.tv_sec << "." << uSecsStr;
#if  0
  if (fSubsession.rtpSource() != NULL && !fSubsession.rtpSource()->hasBeenSynchronizedUsingRTCP()) {
    envir() << "!"; // mark the debugging output to indicate that this presentation time is not RTCP-synchronized
  }
#endif
#ifdef DEBUG_PRINT_NPT
  envir() << "\tNPT: " << fSubsession.getNormalPlayTime(presentationTime);
#endif
  envir() << "\n";
#endif


  //
#ifdef  _DEBUG
  {
  TCHAR	tBuf[128];
  if (fStreamId != NULL)  {
	  _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "Stream \"%S\"\n"  ),  fStreamId  );
	  OutputDebugString(  tBuf  );
  }
	
  //
  _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "\tReceived %d bytes\n"  ),  frameSize  );	
  OutputDebugString(  tBuf  );

  if (numTruncatedBytes > 0) {
	  _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  " (with %d bytes truncated)\n"  ),  numTruncatedBytes  );
	  OutputDebugString(  tBuf  );
  }
  char uSecsStr[6+1]; // used to output the 'microseconds' part of the presentation time
  sprintf(uSecsStr, "%06u", (unsigned)presentationTime.tv_usec);
  _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  ".\tPresentation time: %d .%S\n"  ),  (int)presentationTime.tv_sec,  uSecsStr  );
  OutputDebugString(  tBuf  );
  }
#endif
  
  //
  int  iErr  =  -1;

//  2014/03/15

  //
  if  (  gBuf_rtspCliHelp.common.pf_BufferCB_rtsp  )  {
	  unsigned char const start_code[4] = {0x00, 0x00, 0x00, 0x01};

	  //
	  int		iMediumType  =  CONST_mediumType_video;
	  int		iCodecType = this->iCodeType;// CONST_codecType_HEVC;//CONST_codecType_h264;

	  unsigned  __int64  ui64ValInMs  =  presentationTime.tv_sec  *  1000  +  presentationTime.tv_usec  /  1000;
	  unsigned  int  uiPts  =  0;	//  2015/02/09
	  bool  bNeedResp  =  false;	//  2015/01/30
	  
	  //
	  if (!fHaveWrittenFirstFrame) {
		  char  buf[2048]  =  "";
		  int	index		=	0;
		  
		  // If we have NAL units encoded in "sprop parameter strings", prepend these to the file:
		  for (unsigned j = 0; j < 3; ++j) {
			  unsigned numSPropRecords;
			  SPropRecord* sPropRecords = parseSPropParameterSets(fSPropParameterSetsStr[j], numSPropRecords);
			 
			  for (unsigned i = 0; i < numSPropRecords; ++i) {
				  //  2014/04/05
				  if  (  !sPropRecords[i].sPropLength  )  continue;
				  //
				  //addData(start_code, 4, presentationTime);
				  // addData(sPropRecords[i].sPropBytes, sPropRecords[i].sPropLength, presentationTime);
				  //
				  int  len  =  0;
				  if  (  bStartCodeExistsFunc(  sPropRecords[i].sPropBytes, sPropRecords[i].sPropLength  )  )  {
					  memcpy(  buf,  sPropRecords[i].sPropBytes, sPropRecords[i].sPropLength  );
					  len  =  sPropRecords[i].sPropLength;
					  }
				  else  {
					    memcpy(  buf,  start_code,  4  );
						memcpy(  buf  +  4,  sPropRecords[i].sPropBytes, sPropRecords[i].sPropLength  );
						len  =  sPropRecords[i].sPropLength  +  4;
				  }
				  //
				  CB_rtsp_res  res;
				  memset(  &res,  0,  sizeof(  res  )  );
				  if  (  gBuf_rtspCliHelp.common.pf_BufferCB_rtsp(  &gBuf_rtspCliHelp,  gBuf_rtspCliHelp.common.iIndex_capProcInfo,  iMediumType,  iCodecType,  ui64ValInMs,  uiPts,  0,  (  unsigned  char  *  )buf,  len,  TRUE,  index,  FALSE,  bNeedResp,  &res  )  )  {
					  goto  errLabel;
				  }
				  index  ++  ;      
			  }
			  delete[] sPropRecords;    
		  }
		  //		  
		  CB_rtsp_res  res;
		  memset(  &res,  0,  sizeof(  res  )  );
		  if  (  gBuf_rtspCliHelp.common.pf_BufferCB_rtsp(  &gBuf_rtspCliHelp,  gBuf_rtspCliHelp.common.iIndex_capProcInfo,  iMediumType,  iCodecType,  ui64ValInMs,  uiPts,  0,  NULL,  0,  TRUE,  index,  TRUE,  bNeedResp,  &res  )  <  0  )  {
			  goto  errLabel;
		  }
		  //  这里，不应该每次都加sps,应该第一次发送的时候就发过去。就不用经常在包里加了。   
		  fHaveWrittenFirstFrame = True; // for next time  
	  }

	  //  这里因该队长度做较验.
	  BOOL  bStartCodeExists  =  FALSE;

#if  0
	  if  (  frameSize  >=  4  )  {
		  if  (  fReceiveBuffer[4]  ==  0
			  &&  fReceiveBuffer[5]  ==  0  )
		  {
			  if  (  fReceiveBuffer[6]  ==  1  )  {
				  bStartCodeExists  =  TRUE;
				  }
			  else  if  (  fReceiveBuffer[6]  ==  0
						&&  fReceiveBuffer[7]  ==  1  )
			  {
				  bStartCodeExists  =  TRUE;
			  }
		  }
	  }
#endif
	  bStartCodeExists  =  bStartCodeExistsFunc(  fReceiveBuffer  +  4,  frameSize  );


	  //
	  if  (  !bStartCodeExists  )  {
		  memcpy(  this->fReceiveBuffer,  start_code,  4  );
	  }
	  
	  unsigned  char  *  p  =  this->fReceiveBuffer;
	  int  len  =  frameSize;
	  //
	  if  (  !bStartCodeExists  )  {
		  p  =  fReceiveBuffer;
		  len  =  4  +  frameSize;
		  }
	  else  {
		    p  =  fReceiveBuffer  +  4;
			len  =  frameSize;
	  }

	  //
	  CB_rtsp_res  res;		
	  memset(  &res,  0,  sizeof(  res  )  );
	  if  (  gBuf_rtspCliHelp.common.pf_BufferCB_rtsp(  &gBuf_rtspCliHelp,  gBuf_rtspCliHelp.common.iIndex_capProcInfo,  
		  iMediumType,  iCodecType,  ui64ValInMs,  uiPts,  0,  p,  len,  FALSE,  0,  FALSE,  bNeedResp,  &res  )  )  {
		  goto  errLabel;
	  }

	  //
#ifdef  _DEBUG
	    //
	    static  int  nCalled  =  0;  nCalled  ++  ;
	    int  nalType  =  M_nalType_h264(  this->fReceiveBuffer  );
		static  int  nCnt_idr  =  0;
		static  int  nCnt_sps  =  0;
		static  int  nCnt_pps  =  0;
		//
		switch  (  nalType  )  {
				case  5:
						nCnt_idr  ++  ;
						break;
				case  7:
					    nCnt_sps  ++  ;
						break;
				case  8:
					    nCnt_pps  ++  ;
						break;
				default:
						break;

		}

		if  (  nCalled  >  1  )  {
		#if  10
			static  bool  bClean  =  FALSE;
			FILE  *  fp  =  NULL;
			char  *  fn  =  "c:\\tttbbb\\kk.h264";
			if  (  !bClean  )  {
				fp  =  fopen(  fn,  "wb"  );
				if (fp) {
					fclose(fp);  fp = NULL;
				}
				bClean  =  TRUE;;
			}
			if  (  bClean  )  {				
				fp  =  fopen(  fn,  "ab+"  );
				if (fp) {
					fwrite(this->fReceiveBuffer, 4 + frameSize, 1, fp);
					fclose(fp);  fp = NULL;
				}
			}
		#endif
		}
#endif

  } 


  // Then continue, to request the next frame of data:
  continuePlaying();

  iErr  =  0;
errLabel:
  if  (  iErr  )  {
	  //
	  dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  _T(  "CMyH264Sink::afterGettingFrame failed"  )  );
	  //
	  //  signalHandlerShutdown(  1  );
	  mysignalHandlerShutdown(  1  );
  }
}


Boolean CMyH264Sink::continuePlaying() {
  if (fSource == NULL) return False; // sanity check (should not happen)

  // Request the next frame of data from our input source.  "afterGettingFrame()" will get called later, when it arrives:
  fSource->getNextFrame(fReceiveBuffer  +  4, DUMMY_SINK_RECEIVE_BUFFER_SIZE,
                        afterGettingFrame, this,
                        onSourceClosure, this);
  return True;
}

//
int		tmpHandler_showInfo(  void  *  p0,  LPCTSTR  tWhere,  LPCTSTR  hint  )
{
	dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  hint  );
	return  0;
}

//
__declspec(  dllexport  )  int  set_PF_BufferCB_rtsp(  PF_BufferCB_rtsp  pf_BufferCB_rtsp,  PF_rtspCliHelp_exit  pf_exit,  int  iIndex_capProcInfo,  LPCTSTR  appObjPrefix,  int  tn  )
{
	int  iErr  =  -1;

	memset(  &gBuf_rtspCliHelp,  0,  sizeof(  gBuf_rtspCliHelp  )  );
#if  0
	gBuf_rtspCliHelp.common.pf_BufferCB_rtsp  =  pf_BufferCB_rtsp;
	gBuf_rtspCliHelp.common.pf_rtspCliHelp_exit  =  pf_exit;
	gBuf_rtspCliHelp.common.iIndex_capProcInfo  =  iIndex_capProcInfo;
	gBuf_rtspCliHelp.common.tn_rtspCliPipe  =  tn;
	
	//
	if  (  !gBuf_rtspCliHelp.common.pRTSP_msg  )  {
		gBuf_rtspCliHelp.common.pRTSP_msg  =  malloc(  sizeof(  RTSP_msg  )  );
		if  (  !gBuf_rtspCliHelp.common.pRTSP_msg  )  goto  errLabel;
	}
#endif
	if  (  rtspCliCommon_init(  pf_BufferCB_rtsp,  pf_exit,  iIndex_capProcInfo,  appObjPrefix,  tn,  &gBuf_rtspCliHelp.common  )  )  {
		goto  errLabel;
	}
	
	//
	dyn_isCliHelp_initShowInfo(  &gBuf_rtspCliHelp.pCtx_showInfo  );
	
	//
	if  (  !gBuf_rtspCliHelp.pMediaDataForSpl_toPost  )  {
		gBuf_rtspCliHelp.pMediaDataForSpl_toPost  =  malloc(  sizeof(  QDC_MEDIA_data  )  );
		if  (  !gBuf_rtspCliHelp.pMediaDataForSpl_toPost  )  goto  errLabel;
	}


	//
	if  (  isCliHelp_streamDataQ_init(  tn,  &gBuf_rtspCliHelp  )  )  goto  errLabel;

	//
	memset(  &g_guiOpen,  0,  sizeof(  g_guiOpen  )  );
	//
	g_guiOpen.pf_showInfo  =  tmpHandler_showInfo;
	//
	QDC_MGR  qdcMgr;
	memset(  &qdcMgr,  0,  sizeof(  qdcMgr  )  );
	qdcMgr.pGuiOpen  =  &g_guiOpen;
	qdcInit(  &qdcMgr  );
	////
	bDone_set_PF_BufferCB_rtsp  =  TRUE;

	iErr  =  0;
errLabel:

	return  iErr;
}
 
int  rtspCliHelp_main_exit(  )
{
	//
	dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  _T(  "rtspCliHelp_main_exit enters"  )  );


	//
	gBuf_rtspCliHelp.bQuit  =  TRUE;
	//
	WaitForSingleObject(  gBuf_rtspCliHelp.hThread_spl,  1000  );
	WaitForSingleObject(  gBuf_rtspCliHelp.hThread_cmdProc,  1000  );


	//
	if  (  gBuf_rtspCliHelp.common.pf_rtspCliHelp_exit  )  {
		gBuf_rtspCliHelp.common.pf_rtspCliHelp_exit(  &gBuf_rtspCliHelp  );
	}

	//
	if  (  gBuf_rtspCliHelp.pStreamDataQ  )  {
		isCliHelp_streamDataQ_exit(  &gBuf_rtspCliHelp  );
	}

	//
	if  (  gBuf_rtspCliHelp.pMediaDataForSpl_toPost  )  {
		free(  gBuf_rtspCliHelp.pMediaDataForSpl_toPost  );  gBuf_rtspCliHelp.pMediaDataForSpl_toPost  =  NULL;
	}

	//
	if  (  gBuf_rtspCliHelp.common.pRTSP_msg  )  {
		free(  gBuf_rtspCliHelp.common.pRTSP_msg  );  gBuf_rtspCliHelp.common.pRTSP_msg  =  NULL;
	}

	//
	dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  _T(  "rtspCliHelp_main_exit leaves"  )  );
	
	//
	dyn_isCliHelp_exitShowInfo(  &gBuf_rtspCliHelp.pCtx_showInfo  );

	return  0;
}

//
//
int  BufferCB_rtspCli(  void  *  pGBUF_rtspCliHelp,  int  iIndex_capProcInfo,  int  iMediumType,  int  iCodecType,  int  iSampleTimeInMs,  
	unsigned  int  uiPts,  int  iDataType,  unsigned  char  *  pBuffer,  long  BufferLen,  bool  bSpsPps,  int  index_spsPps, 
	bool  bFinished_spsPps,  bool  bNeedResp,  CB_rtsp_res  *  pRes  )
{
	HRESULT						hr					=	-1;

	if  (  !pRes  )  return  -1;
	GBUF_rtspCliHelp  *  pGBuf  =  (  GBUF_rtspCliHelp  *  )pGBUF_rtspCliHelp;
	if  (  !pGBuf  )  return  -1;
	
	BOOL		fSuccess;

	//  2014/06/06
	if  (  pGBuf->cmdProc.bStopped  )  {

		dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  _T(  "rtspCli::BufferCB_rtspCli: shall stop soon................."  )  );

		goto  errLabel;
	}

#if  0
	//  2014/06/06
	pGBuf->common.status.dwLastTickCnt_BufferCB_rtspCli  =  GetTickCount(  );

	//
	if  (  !isHandleValid_open(  pGBuf->common.pipe.hPipe  )  )  {	
		//
		TCHAR	pipeName[256];
		int  tn_rtspCliPipe  =  0;
		_sntprintf(  pipeName,  mycountof(  pipeName  ),  _T(  "%s%d"  ),  CONST_rtspCliPipePrefix,  pGBuf->common.tn_rtspCliPipe  );

		//
		pGBuf->common.pipe.hPipe = CreateFile( 
							pipeName,   // pipe name 
							GENERIC_READ |  // read and write access 
							GENERIC_WRITE, 
							0,              // no sharing 
							NULL,           // default security attributes
							OPEN_EXISTING,  // opens existing pipe 
							0,              // default attributes 
							NULL);          // no template file   						
		if (  pGBuf->common.pipe.hPipe == INVALID_HANDLE_VALUE  )  {
#ifdef  _DEBUG
			OutputDebugString(  _T(  "BufferCB_rtspCli failed: CreateFile failed\n"  )  );
#endif
			goto  errLabel;
		}

		
		//traceLogA(  "showInfoThreadProc: pipe created"  );
		DWORD  dwMode = PIPE_READMODE_MESSAGE; 
		fSuccess  = SetNamedPipeHandleState( 
							pGBuf->common.pipe.hPipe,    // pipe handle 
							&dwMode,  // new pipe mode 
							NULL,     // don't set maximum bytes 
							NULL);    // don't set maximum time 					
		if (!fSuccess)  {
							//  qyDisplayLastError(  "SetNamedPipeHandleState failed"  ); 							
			goto  errLabel;						
		} 

	}
						
	

	if  (  !pGBuf->common.pRTSP_msg  )  goto  errLabel;
	RTSP_msg  &	msg  =  *(  RTSP_msg  *  )pGBuf->common.pRTSP_msg;
	memset(  &msg,  0,  offsetof(  RTSP_msg,  buf  )  );

	msg.iMediumType  =  iMediumType;
	msg.iCodecType  =  iCodecType;
	msg.iSampleTimeInMs  =  iSampleTimeInMs;
	msg.bSpsPps  =  bSpsPps;
	msg.index_spsPps  =  index_spsPps;
	msg.bFinished_spsPps  =  bFinished_spsPps;
	if  (  BufferLen  >  sizeof(  msg.buf  )  )  goto  errLabel;
	memcpy(  msg.buf,  pBuffer,  BufferLen  );
	msg.uiLen  =  BufferLen;
	//
	int  msgLen  =  offsetof(  RTSP_msg,  buf  )  +  msg.uiLen;
						
	DWORD  cbWritten  =  0;
	//
	fSuccess = WriteFile( 
						pGBuf->common.pipe.hPipe,                  // pipe handle 
						&msg,             // message 
						msgLen, // message length 
						&cbWritten,             // bytes written 
						NULL);                  // not overlapped 
	
	if  (  !fSuccess  )  {		
		//traceLogA("WriteFile failed"); 	
		goto  errLabel;	
	}
	if  (  cbWritten  !=  msgLen  )  {
#ifdef  __DEBUG__
		traceLog(  _T(  "BufferCB_rtspCli: WriteFile err, cbWritten err"  )  );
#endif
		goto  errLabel;
	}	
#endif

	//  2015/01/27
	if  (  BufferCB_rtspCliCommon(  &pGBuf->common,  iIndex_capProcInfo,  iMediumType,  iCodecType,  iSampleTimeInMs,  uiPts, 
		iDataType,  pBuffer,  BufferLen,  bSpsPps,  index_spsPps,  bFinished_spsPps,  bNeedResp,  pRes  )  )  {
		goto  errLabel;
	}


	hr  =  S_OK;

errLabel:
	
	if  (  FAILED(  hr  )  )  {
		//
		dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  _T(  "rtspCli::BufferCB_rtspCli failed"  )  );
		//
#if  0
		if  (  pGBuf->common.pipe.hPipe  !=  INVALID_HANDLE_VALUE  )  {
			CloseHandle(  pGBuf->common.pipe.hPipe  );  pGBuf->common.pipe.hPipe  =  NULL;
		}
#endif
	}

	return  hr;
}

int  myrtspCliHelp_exit(  void  *  pGBUF_rtspCliHelp  )
{
	GBUF_rtspCliHelp  *  pGBuf  =  (  GBUF_rtspCliHelp  *  )pGBUF_rtspCliHelp;
	if  (  !pGBuf  )  return  -1;

#if  0
	if  (  pGBuf->common.pipe.hPipe  !=  INVALID_HANDLE_VALUE  )  {
			CloseHandle(  pGBuf->common.pipe.hPipe  );  pGBuf->common.pipe.hPipe  =  NULL;
	}
#endif
	//  2015/01/27
	rtspCliCommon_exit(  &pGBuf->common  );

	return  0;
}

//  2016/04/03
#define		CONST_qnmVer_rtsp							"02630322"				//  2015/08/21	//  "02622960"				//  

//
extern  "C"  char  *  qnmVerStr_rtsp(  )
{
	char	*	p	=	"";


	p  =  CONST_qnmVer_rtsp;


	return  p;
}




//
__declspec(  dllexport  )  int rtspCliHelp_main(int argc, char** argv) 
{	
	//
	int		tn_rtspCliHelp  =  0;
	TCHAR	appObjPrefix[32]  =  _T(  ""  );	//  2015/02/02


  // Begin by setting up our usage environment:
  TaskScheduler* scheduler = BasicTaskScheduler::createNew();
  env = BasicUsageEnvironment::createNew(*scheduler);

  progName = argv[0];

  gettimeofday(&startTime, NULL);

#ifdef USE_SIGNALS
  // Allow ourselves to be shut down gracefully by a SIGHUP or a SIGUSR1:
  signal(SIGHUP, signalHandlerShutdown);
  signal(SIGUSR1, signalHandlerShutdown);
#endif

  // unfortunately we can't use getopt() here, as Windoze doesn't have it
  while (argc > 1) {
    char* const opt = argv[1];
    if (opt[0] != '-') {
      if (argc == 2) break; // only the URL is left
      usage();
    }

	//  2014/03/01. 在这里取一下tn
	//
	if  (  opt[1]  ==  't'  &&  opt[2]  ==  'n'  &&  opt[3]  ==  '='  &&  opt[4]  )  {
		tn_rtspCliHelp  =  atol(  opt  +  4  );
		//
		++argv; --argc;
		//
		continue;
	}
	//  2015/02/02
	if  (  opt[1]  ==  'a'  &&  opt[2]  ==  'q'  &&  opt[3]  ==  'm'  &&  opt[4]  )  {
		int  iVal  =  atol(  opt  +  5  );
		_sntprintf(  appObjPrefix,  mycountof(  appObjPrefix  ),  _T(  "qm=%d"  ),  iVal  );
		//
		++argv; --argc;
		//
		continue;
	}

	//
	if (opt[1] == 'd' && opt[2] == 'b' && opt[3] == 'g' && opt[4] == '=') {
		g_bDbg = atol(opt + 5);
		//
		++argv; --argc;
		//
		continue;
	}


	//
    switch (opt[1]) {
    case 'p': { // specify start port number
      int portArg;
      if (sscanf(argv[2], "%d", &portArg) != 1) {
	usage();
      }
      if (portArg <= 0 || portArg >= 65536 || portArg&1) {
	*env << "bad port number: " << portArg
		<< " (must be even, and in the range (0,65536))\n";
	usage();
      }
      desiredPortNum = (unsigned short)portArg;
      ++argv; --argc;
      break;
    }

    case 'r': { // do not receive data (instead, just 'play' the stream(s))
      createReceivers = False;
      break;
    }

    case 'q': { // output a QuickTime file (to stdout)
      outputQuickTimeFile = True;
      break;
    }

    case '4': { // output a 'mp4'-format file (to stdout)
      outputQuickTimeFile = True;
      generateMP4Format = True;
      break;
    }

    case 'i': { // output an AVI file (to stdout)
      outputAVIFile = True;
      break;
    }

    case 'I': { // specify input interface...
      NetAddressList addresses(argv[2]);
      if (addresses.numAddresses() == 0) {
	*env << "Failed to find network address for \"" << argv[2] << "\"";
	break;
      }
      ReceivingInterfaceAddr = *(unsigned*)(addresses.firstAddress()->data());
      ++argv; --argc;
      break;
    }

    case 'a': { // receive/record an audio stream only
      audioOnly = True;
      singleMedium = "audio";
      break;
    }

    case 'v': { // receive/record a video stream only
      videoOnly = True;
      singleMedium = "video";
      break;
    }

    case 'V': { // disable verbose output
      verbosityLevel = 0;
      break;
    }

    case 'd': { // specify duration, or how much to delay after end time
      float arg;
      if (sscanf(argv[2], "%g", &arg) != 1) {
	usage();
      }
      if (argv[2][0] == '-') { // not "arg<0", in case argv[2] was "-0"
	// a 'negative' argument was specified; use this for "durationSlop":
	duration = 0; // use whatever's in the SDP
	durationSlop = -arg;
      } else {
	duration = arg;
	durationSlop = 0;
      }
      ++argv; --argc;
      break;
    }

    case 'D': { // specify maximum number of seconds to wait for packets:
      if (sscanf(argv[2], "%u", &interPacketGapMaxTime) != 1) {
	usage();
      }
      ++argv; --argc;
      break;
    }

    case 'c': { // play continuously
      playContinuously = True;
      break;
    }

    case 'S': { // specify an offset to use with "SimpleRTPSource"s
      if (sscanf(argv[2], "%d", &simpleRTPoffsetArg) != 1) {
	usage();
      }
      if (simpleRTPoffsetArg < 0) {
	*env << "offset argument to \"-S\" must be >= 0\n";
	usage();
      }
      ++argv; --argc;
      break;
    }

    case 'm': { // output multiple files - one for each frame
      oneFilePerFrame = True;
      break;
    }

    case 'n': { // notify the user when the first data packet arrives
      notifyOnPacketArrival = True;
      break;
    }

    case 'O': { // Don't send an "OPTIONS" request before "DESCRIBE"
      sendOptionsRequest = False;
      break;
    }

    case 'o': { // Send only the "OPTIONS" request to the server
      sendOptionsRequestOnly = True;
      break;
    }

    case 'P': { // specify an interval (in seconds) between writing successive output files
      int fileOutputIntervalInt;
      if (sscanf(argv[2], "%d", &fileOutputIntervalInt) != 1 || fileOutputIntervalInt <= 0) {
	usage();
      }
      fileOutputInterval = (unsigned)fileOutputIntervalInt;
      ++argv; --argc;
      break;
    }

    case 't': {
      // stream RTP and RTCP over the TCP 'control' connection
      if (controlConnectionUsesTCP) {
	streamUsingTCP = True;
      } else {
	usage();
      }
      break;
    }

    case 'T': {
      // stream RTP and RTCP over a HTTP connection
      if (controlConnectionUsesTCP) {
	if (argc > 3 && argv[2][0] != '-') {
	  // The next argument is the HTTP server port number:
	  if (sscanf(argv[2], "%hu", &tunnelOverHTTPPortNum) == 1
	      && tunnelOverHTTPPortNum > 0) {
	    ++argv; --argc;
	    break;
	  }
	}
      }

      // If we get here, the option was specified incorrectly:
      usage();
      break;
    }

    case 'u': { // specify a username and password
      if (argc < 4) usage(); // there's no argv[3] (for the "password")
      username = argv[2];
      password = argv[3];
      argv+=2; argc-=2;
      if (allowProxyServers && argc > 3 && argv[2][0] != '-') {
	// The next argument is the name of a proxy server:
	proxyServerName = argv[2];
	++argv; --argc;

	if (argc > 3 && argv[2][0] != '-') {
	  // The next argument is the proxy server port number:
	  if (sscanf(argv[2], "%hu", &proxyServerPortNum) != 1) {
	    usage();
	  }
	  ++argv; --argc;
	}
      }

      ourAuthenticator = new Authenticator(username, password);
      break;
    }

    case 'k': { // specify a username and password to be used to authentication an incoming "REGISTER" command (for use with -R)
      if (argc < 4) usage(); // there's no argv[3] (for the "password")
      usernameForREGISTER = argv[2];
      passwordForREGISTER = argv[3];
      argv+=2; argc-=2;

      if (authDBForREGISTER == NULL) authDBForREGISTER = new UserAuthenticationDatabase;
      authDBForREGISTER->addUserRecord(usernameForREGISTER, passwordForREGISTER);
      break;
    }

    case 'A': { // specify a desired audio RTP payload format
      unsigned formatArg;
      if (sscanf(argv[2], "%u", &formatArg) != 1
	  || formatArg >= 96) {
	usage();
      }
      desiredAudioRTPPayloadFormat = (unsigned char)formatArg;
      ++argv; --argc;
      break;
    }

    case 'M': { // specify a MIME subtype for a dynamic RTP payload type
      mimeSubtype = argv[2];
      if (desiredAudioRTPPayloadFormat==0) desiredAudioRTPPayloadFormat =96;
      ++argv; --argc;
      break;
    }

    case 'w': { // specify a width (pixels) for an output QuickTime or AVI movie
      if (sscanf(argv[2], "%hu", &movieWidth) != 1) {
	usage();
      }
      movieWidthOptionSet = True;
      ++argv; --argc;
      break;
    }

    case 'h': { // specify a height (pixels) for an output QuickTime or AVI movie
      if (sscanf(argv[2], "%hu", &movieHeight) != 1) {
	usage();
      }
      movieHeightOptionSet = True;
      ++argv; --argc;
      break;
    }

    case 'f': { // specify a frame rate (per second) for an output QT or AVI movie
      if (sscanf(argv[2], "%u", &movieFPS) != 1) {
	usage();
      }
      movieFPSOptionSet = True;
      ++argv; --argc;
      break;
    }

    case 'F': { // specify a prefix for the audio and video output files
      fileNamePrefix = argv[2];
      ++argv; --argc;
      break;
    }

    case 'g': { // specify a user agent name to use in outgoing requests
      userAgent = argv[2];
      ++argv; --argc;
      break;
    }

    case 'b': { // specify the size of buffers for "FileSink"s
      if (sscanf(argv[2], "%u", &fileSinkBufferSize) != 1) {
	usage();
      }
      ++argv; --argc;
      break;
    }

    case 'B': { // specify the size of input socket buffers
      if (sscanf(argv[2], "%u", &socketInputBufferSize) != 1) {
	usage();
      }
      ++argv; --argc;
      break;
    }

    // Note: The following option is deprecated, and may someday be removed:
    case 'l': { // try to compensate for packet loss by repeating frames
      packetLossCompensate = True;
      break;
    }

    case 'y': { // synchronize audio and video streams
      syncStreams = True;
      break;
    }

    case 'H': { // generate hint tracks (as well as the regular data tracks)
      generateHintTracks = True;
      break;
    }

    case 'Q': { // output QOS measurements
      qosMeasurementIntervalMS = 1000; // default: 1 second

      if (argc > 3 && argv[2][0] != '-') {
	// The next argument is the measurement interval,
	// in multiples of 100 ms
	if (sscanf(argv[2], "%u", &qosMeasurementIntervalMS) != 1) {
	  usage();
	}
	qosMeasurementIntervalMS *= 100;
	++argv; --argc;
      }
      break;
    }

    case 's': { // specify initial seek time (trick play)
      double arg;
      if (sscanf(argv[2], "%lg", &arg) != 1 || arg < 0) {
	usage();
      }
      initialSeekTime = arg;
      ++argv; --argc;
      break;
    }

    case 'U': {
      // specify initial absolute seek time (trick play), using a string of the form "YYYYMMDDTHHMMSSZ" or "YYYYMMDDTHHMMSS.<frac>Z"
      initialAbsoluteSeekTime = argv[2];
      ++argv; --argc;
      break;
    }

    case 'z': { // scale (trick play)
      float arg;
      if (sscanf(argv[2], "%g", &arg) != 1 || arg == 0.0f) {
	usage();
      }
      scale = arg;
      ++argv; --argc;
      break;
    }

    case 'R': {
      // set up a handler server for incoming "REGISTER" commands
      createHandlerServerForREGISTERCommand = True;
      if (argc > 2 && argv[2][0] != '-') {
	// The next argument is the REGISTER handler server port number:
	if (sscanf(argv[2], "%hu", &handlerServerForREGISTERCommandPortNum) == 1 && handlerServerForREGISTERCommandPortNum > 0) {
	  ++argv; --argc;
	  break;
	}
      }
      break;
    }

    case 'C': {
      forceMulticastOnUnspecified = True;
      break;
    }

    default: {
      *env << "Invalid option: " << opt << "\n";
      usage();
      break;
    }
    }

    ++argv; --argc;
  }

  //
  if  (  !bDone_set_PF_BufferCB_rtsp  )  {
		   int  iIndex_capBmp  =  0;
		   if  (  set_PF_BufferCB_rtsp(  BufferCB_rtspCli,  myrtspCliHelp_exit,  iIndex_capBmp,  appObjPrefix,  tn_rtspCliHelp  )  )  {
			   goto  errLabel;
		   }
  }
  //

  //
  TCHAR  tBuf[128]  =  _T(  ""  );
  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "rtspCliHelp starts. %S"  ),  qnmVerStr_rtsp(  )  );
  dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  tBuf  );
  //MessageBox(  0,  _T(  "kk"  ),  _T(  ""  ),  MB_OK  );


  //
  DWORD  dwThreadDaemonId;
  //
  gBuf_rtspCliHelp.bQuit  =  FALSE;
  //
  gBuf_rtspCliHelp.hThread_spl  =  CreateThread(  NULL,  0,  mcThreadProc_spl,  0,  CREATE_SUSPENDED,  &dwThreadDaemonId  );	
  if  (  !gBuf_rtspCliHelp.hThread_spl  )  goto  errLabel;					
  gBuf_rtspCliHelp.dwThreadId_spl  =  dwThreadDaemonId;					
  if  (  ResumeThread(  gBuf_rtspCliHelp.hThread_spl  )  ==  -1  )  goto  errLabel;									 

  //  2014/06/06
  gBuf_rtspCliHelp.hThread_cmdProc  =  CreateThread(  NULL,  0,  mcThreadProc_cmdProc,  0,  CREATE_SUSPENDED,  &dwThreadDaemonId  );	
  if  (  !gBuf_rtspCliHelp.hThread_cmdProc  )  goto  errLabel;					
  gBuf_rtspCliHelp.dwThreadId_cmdProc  =  dwThreadDaemonId;					
  if  (  ResumeThread(  gBuf_rtspCliHelp.hThread_cmdProc  )  ==  -1  )  goto  errLabel;									 


#ifdef  _DEBUG
#endif


  // There must be exactly one "rtsp://" URL at the end (unless '-R' was used, in which case there's no URL)
  if (!( (argc == 2 && !createHandlerServerForREGISTERCommand) || (argc == 1 && createHandlerServerForREGISTERCommand) )) usage();
  if (outputQuickTimeFile && outputAVIFile) {
    *env << "The -i and -q (or -4) options cannot both be used!\n";
    usage();
  }
  Boolean outputCompositeFile = outputQuickTimeFile || outputAVIFile;
  if (!createReceivers && (outputCompositeFile || oneFilePerFrame || fileOutputInterval > 0)) {
    *env << "The -r option cannot be used with -q, -4, -i, -m, or -P!\n";
    usage();
  }
  if (oneFilePerFrame && fileOutputInterval > 0) {
    *env << "The -m and -P options cannot both be used!\n";
    usage();
  }
  if (outputCompositeFile && !movieWidthOptionSet) {
    *env << "Warning: The -q, -4 or -i option was used, but not -w.  Assuming a video width of "
	 << movieWidth << " pixels\n";
  }
  if (outputCompositeFile && !movieHeightOptionSet) {
    *env << "Warning: The -q, -4 or -i option was used, but not -h.  Assuming a video height of "
	 << movieHeight << " pixels\n";
  }
  if (outputCompositeFile && !movieFPSOptionSet) {
    *env << "Warning: The -q, -4 or -i option was used, but not -f.  Assuming a video frame rate of "
	 << movieFPS << " frames-per-second\n";
  }
  if (audioOnly && videoOnly) {
    *env << "The -a and -v options cannot both be used!\n";
    usage();
  }
  if (sendOptionsRequestOnly && !sendOptionsRequest) {
    *env << "The -o and -O options cannot both be used!\n";
    usage();
  }
  if (initialAbsoluteSeekTime != NULL && initialSeekTime != 0.0f) {
    *env << "The -s and -U options cannot both be used!\n";
    usage();
  }
  if (authDBForREGISTER != NULL && !createHandlerServerForREGISTERCommand) {
    *env << "If \"-k <username> <password>\" is used, then -R (or \"-R <port-num>\") must also be used!\n";
    usage();
  }
  if (tunnelOverHTTPPortNum > 0) {
    if (streamUsingTCP) {
      *env << "The -t and -T options cannot both be used!\n";
      usage();
    } else {
      streamUsingTCP = True;
    }
  }
  if (!createReceivers && notifyOnPacketArrival) {
    *env << "Warning: Because we're not receiving stream data, the -n flag has no effect\n";
  }
  if (durationSlop < 0) {
    // This parameter wasn't set, so use a default value.
    // If we're measuring QOS stats, then don't add any slop, to avoid
    // having 'empty' measurement intervals at the end.
    durationSlop = qosMeasurementIntervalMS > 0 ? 0.0 : 5.0;
  }

  streamURL = argv[1];

  // Create (or arrange to create) our client object:
  if (createHandlerServerForREGISTERCommand) {
    handlerServerForREGISTERCommand
      = HandlerServerForREGISTERCommand::createNew(*env, continueAfterClientCreation0,
						   handlerServerForREGISTERCommandPortNum, authDBForREGISTER,
						   verbosityLevel, progName);
    if (handlerServerForREGISTERCommand == NULL) {
      *env << "Failed to create a server for handling incoming \"REGISTER\" commands: " << env->getResultMsg() << "\n";
    } else {
      *env << "Awaiting an incoming \"REGISTER\" command on port " << handlerServerForREGISTERCommand->serverPortNum() << "\n";
    }
  } else {
    ourClient = createClient(*env, streamURL, verbosityLevel, progName);
    if (ourClient == NULL) {
      *env << "Failed to create " << clientProtocolName << " client: " << env->getResultMsg() << "\n";
      shutdown();
    }
    continueAfterClientCreation1();
  }

  // All subsequent activity takes place within the event loop:
  env->taskScheduler().doEventLoop(); // does not return

errLabel:

  // 
  rtspCliHelp_main_exit(  );

  return 0; // only to prevent compiler warning
}

void continueAfterClientCreation0(RTSPClient* newRTSPClient, Boolean requestStreamingOverTCP) {
  if (newRTSPClient == NULL) return;

  streamUsingTCP = requestStreamingOverTCP;

  assignClient(ourClient = newRTSPClient);
  streamURL = newRTSPClient->url();

  // Having handled one "REGISTER" command (giving us a "rtsp://" URL to stream from), we don't handle any more:
  Medium::close(handlerServerForREGISTERCommand); handlerServerForREGISTERCommand = NULL;

  continueAfterClientCreation1();
}

void continueAfterClientCreation1() {
  setUserAgentString(userAgent);

  if (sendOptionsRequest) {
    // Begin by sending an "OPTIONS" command:
    getOptions(continueAfterOPTIONS);
  } else {
    continueAfterOPTIONS(NULL, 0, NULL);
  }
}

void continueAfterOPTIONS(RTSPClient*, int resultCode, char* resultString) {
  if (sendOptionsRequestOnly) {
    if (resultCode != 0) {
      *env << clientProtocolName << " \"OPTIONS\" request failed: " << resultString << "\n";
    } else {
      *env << clientProtocolName << " \"OPTIONS\" request returned: " << resultString << "\n";
    }
    shutdown();
  }
  delete[] resultString;

  // Next, get a SDP description for the stream:
  getSDPDescription(continueAfterDESCRIBE);
}

void continueAfterDESCRIBE(RTSPClient*, int resultCode, char* resultString) {
  if (resultCode != 0) {
    *env << "Failed to get a SDP description for the URL \"" << streamURL << "\": " << resultString << "\n";
    delete[] resultString;
    shutdown();
  }

  char* sdpDescription = resultString;
  *env << "Opened URL \"" << streamURL << "\", returning a SDP description:\n" << sdpDescription << "\n";

  // Create a media session object from this SDP description:
  session = MediaSession::createNew(*env, sdpDescription);
  delete[] sdpDescription;
  if (session == NULL) {
    *env << "Failed to create a MediaSession object from the SDP description: " << env->getResultMsg() << "\n";
    shutdown();
  } else if (!session->hasSubsessions()) {
    *env << "This session has no media subsessions (i.e., no \"m=\" lines)\n";
    shutdown();
  }

  // Then, setup the "RTPSource"s for the session:
  MediaSubsessionIterator iter(*session);
  MediaSubsession *subsession;
  Boolean madeProgress = False;
  char const* singleMediumToTest = singleMedium;
  while ((subsession = iter.next()) != NULL) {
    // If we've asked to receive only a single medium, then check this now:
    if (singleMediumToTest != NULL) {
      if (strcmp(subsession->mediumName(), singleMediumToTest) != 0) {
		  *env << "Ignoring \"" << subsession->mediumName()
			  << "/" << subsession->codecName()
			  << "\" subsession, because we've asked to receive a single " << singleMedium
			  << " session only\n";
	continue;
      } else {
	// Receive this subsession only
	singleMediumToTest = "xxxxx";
	    // this hack ensures that we get only 1 subsession of this type
      }
    }

    if (desiredPortNum != 0) {
      subsession->setClientPortNum(desiredPortNum);
      desiredPortNum += 2;
    }

    if (createReceivers) {
      if (!subsession->initiate(simpleRTPoffsetArg)) {
	*env << "Unable to create receiver for \"" << subsession->mediumName()
	     << "/" << subsession->codecName()
	     << "\" subsession: " << env->getResultMsg() << "\n";
      } else {
	*env << "Created receiver for \"" << subsession->mediumName()
	     << "/" << subsession->codecName()
	     << "\" subsession (client ports " << subsession->clientPortNum()
	     << "-" << subsession->clientPortNum()+1 << ")\n";
	madeProgress = True;
	
	if (subsession->rtpSource() != NULL) {
	  // Because we're saving the incoming data, rather than playing
	  // it in real time, allow an especially large time threshold
	  // (1 second) for reordering misordered incoming packets:
	  unsigned const thresh = 1000000; // 1 second
	  subsession->rtpSource()->setPacketReorderingThresholdTime(thresh);
	  
	  // Set the RTP source's OS socket buffer size as appropriate - either if we were explicitly asked (using -B),
	  // or if the desired FileSink buffer size happens to be larger than the current OS socket buffer size.
	  // (The latter case is a heuristic, on the assumption that if the user asked for a large FileSink buffer size,
	  // then the input data rate may be large enough to justify increasing the OS socket buffer size also.)
	  int socketNum = subsession->rtpSource()->RTPgs()->socketNum();
	  unsigned curBufferSize = getReceiveBufferSize(*env, socketNum);
	  if (socketInputBufferSize > 0 || fileSinkBufferSize > curBufferSize) {
	    unsigned newBufferSize = socketInputBufferSize > 0 ? socketInputBufferSize : fileSinkBufferSize;
	    newBufferSize = setReceiveBufferTo(*env, socketNum, newBufferSize);
	    if (socketInputBufferSize > 0) { // The user explicitly asked for the new socket buffer size; announce it:
	      *env << "Changed socket receive buffer size for the \""
		   << subsession->mediumName()
		   << "/" << subsession->codecName()
		   << "\" subsession from "
		   << curBufferSize << " to "
		   << newBufferSize << " bytes\n";
	    }
	  }
	}
      }
    } else {
      if (subsession->clientPortNum() == 0) {
	*env << "No client port was specified for the \""
	     << subsession->mediumName()
	     << "/" << subsession->codecName()
	     << "\" subsession.  (Try adding the \"-p <portNum>\" option.)\n";
      } else {
		madeProgress = True;
      }
    }
  }
  if (!madeProgress) shutdown();

  // Perform additional 'setup' on each subsession, before playing them:
  setupStreams();
}

MediaSubsession *subsession;
Boolean madeProgress = False;
void continueAfterSETUP(RTSPClient*, int resultCode, char* resultString) {
  if (resultCode == 0) {
      *env << "Setup \"" << subsession->mediumName()
	   << "/" << subsession->codecName()
	   << "\" subsession (client ports " << subsession->clientPortNum()
	   << "-" << subsession->clientPortNum()+1 << ")\n";
      madeProgress = True;
  } else {
    *env << "Failed to setup \"" << subsession->mediumName()
	 << "/" << subsession->codecName()
	 << "\" subsession: " << resultString << "\n";
  }
  delete[] resultString;

  // Set up the next subsession, if any:
  setupStreams();
}

std::string toLower(const std::string& s) {
	std::string result;
	for (char c : s) {
		result += tolower(c);
	}
	return result;
}

std::string extractSpecContent(const char* content, const std::string& searchStr, const std::string& endMarker = "")
{
	std::istringstream iss(content);
	std::string line;
	//const std::string searchStr = "MPEG4-GENERIC";

	while (std::getline(iss, line)) {
		if (!line.empty() && line.back() == '\r') {
			line.pop_back();
		}

		size_t startPos = toLower(line).find(toLower(searchStr));
		if (startPos != std::string::npos) {
			size_t endPos = std::string::npos;

			if (!endMarker.empty()) {
				endPos = line.find(endMarker, startPos + searchStr.length());
			}

			std::string result;
			if (endPos == std::string::npos) {
				result = line.substr(startPos + searchStr.length());
			}
			else {
				int len = endPos - startPos - searchStr.length();
				result = line.substr(startPos + searchStr.length(), len);
			}

			//std::cout << "Extracted: " << result << std::endl;

			return result;
		}
	}

	return "";
}


#include <cstdint>
#include <stdexcept>

uint32_t string_to_uint32(const std::string& str, int base) {
	try {
		unsigned long value = std::stoul(str, nullptr, base);
		if (value > UINT32_MAX) {
			throw std::out_of_range("Value exceeds UINT32_MAX");
		}
		return static_cast<uint32_t>(value);
	}
	catch (const std::invalid_argument& e) {
		throw std::invalid_argument("Invalid argument: not a valid number");
	}
	catch (const std::out_of_range& e) {
		throw std::out_of_range("Out of range: number too large for uint32_t");
	}
}


void createOutputFiles(char const* periodicFilenameSuffix) {
  char outFileName[1000];

  if (outputQuickTimeFile || outputAVIFile) {
    if (periodicFilenameSuffix[0] == '\0') {
      // Normally (unless the '-P <interval-in-seconds>' option was given) we output to 'stdout':
      sprintf(outFileName, "stdout");
    } else {
      // Otherwise output to a type-specific file name, containing "periodicFilenameSuffix":
      char const* prefix = fileNamePrefix[0] == '\0' ? "output" : fileNamePrefix;
      snprintf(outFileName, sizeof outFileName, "%s%s.%s", prefix, periodicFilenameSuffix,
	       outputAVIFile ? "avi" : generateMP4Format ? "mp4" : "mov");
    }

    if (outputQuickTimeFile) {
      qtOut = QuickTimeFileSink::createNew(*env, *session, outFileName,
					   fileSinkBufferSize,
					   movieWidth, movieHeight,
					   movieFPS,
					   packetLossCompensate,
					   syncStreams,
					   generateHintTracks,
					   generateMP4Format);
      if (qtOut == NULL) {
	*env << "Failed to create a \"QuickTimeFileSink\" for outputting to \""
	     << outFileName << "\": " << env->getResultMsg() << "\n";
	shutdown();
      } else {
	*env << "Outputting to the file: \"" << outFileName << "\"\n";
      }
      
      qtOut->startPlaying(sessionAfterPlaying, NULL);
    } else { // outputAVIFile
      aviOut = AVIFileSink::createNew(*env, *session, outFileName,
				      fileSinkBufferSize,
				      movieWidth, movieHeight,
				      movieFPS,
				      packetLossCompensate);
      if (aviOut == NULL) {
	*env << "Failed to create an \"AVIFileSink\" for outputting to \""
	     << outFileName << "\": " << env->getResultMsg() << "\n";
	shutdown();
      } else {
	*env << "Outputting to the file: \"" << outFileName << "\"\n";
      }
      
      aviOut->startPlaying(sessionAfterPlaying, NULL);
    }
  } 
  else {
    // Create and start "FileSink"s for each subsession:
    madeProgress = False;
    MediaSubsessionIterator iter(*session);
    while ((subsession = iter.next()) != NULL) {
      if (subsession->readSource() == NULL) continue; // was not initiated
      
      // Create an output file for each desired stream:
      if (singleMedium == NULL || periodicFilenameSuffix[0] != '\0') {
	// Output file name is
	//     "<filename-prefix><medium_name>-<codec_name>-<counter><periodicFilenameSuffix>"
	static unsigned streamCounter = 0;
	snprintf(outFileName, sizeof outFileName, "%s%s-%s-%d%s",
		 fileNamePrefix, subsession->mediumName(),
		 subsession->codecName(), ++streamCounter, periodicFilenameSuffix);
      } else {
	// When outputting a single medium only, we output to 'stdout
	// (unless the '-P <interval-in-seconds>' option was given):
	sprintf(outFileName, "stdout");
      }

      FileSink* fileSink = NULL;
      Boolean createOggFileSink = False; // by default
	  const char* mediuName = subsession->mediumName();
	  const char* codeName = subsession->codecName();

	  const char* sdpLine = subsession->savedSDPLines();
      if (strcmp(subsession->mediumName(), "video") == 0) {
		  if (strcmp(subsession->codecName(), "H264") == 0) {
			  // For H.264 video stream, we use a special sink that adds 'start codes',
			  // and (at the start) the SPS and PPS NAL units:

			  /*#if  0
				  fileSink = H264VideoFileSink::createNew(*env, outFileName,
						  subsession->fmtp_spropparametersets(),
						  fileSinkBufferSize, oneFilePerFrame);
			  #else
					fileSink = CMyH264Sink::createNew(*env, outFileName,
						  subsession->fmtp_spropparametersets(),
						  fileSinkBufferSize, oneFilePerFrame);
			  #endif*/
			  fileSink = CMyH264Sink::createNew(*env,  "H264", CONST_codecType_h264, subsession->fmtp_spropparametersets(), fileSinkBufferSize, oneFilePerFrame);

			  } 
		  else if (strcmp(subsession->codecName(), "H265") == 0) {
				  // For H.265 video stream, we use a special sink that adds 'start codes',
			      // and (at the start) the VPS, SPS, and PPS NAL units:
			      
				  /*fileSink = H265VideoFileSink::createNew(*env, outFileName,
						  subsession->fmtp_spropvps(),
						  subsession->fmtp_spropsps(),
						  subsession->fmtp_sproppps(),
						  fileSinkBufferSize, oneFilePerFrame);*/
			      //fileSink = CMyDummySink::createNew(*env, *subsession, "H265");
			      fileSink = CMyH264Sink::createNew(*env, "H265", CONST_codecType_HEVC, subsession->fmtp_spropvps(), subsession->fmtp_spropsps(),
					  subsession->fmtp_sproppps(),  fileSinkBufferSize, oneFilePerFrame);
				  } 
		  else if (strcmp(subsession->codecName(), "THEORA") == 0) {
				  createOggFileSink = True;	
				  }
		  else  if  (  strcmp(  subsession->codecName(),  "MP2T"  )  ==  0  )  {
					fileSink  =  CMyDummySink::createNew(  *env,  *subsession,  "MP2T"  );
		  }
		  //
		  #ifdef  _DEBUG
				  const  char  *  pStr  =  subsession->codecName(  );		  
				  int  j  =  0;
		  #endif
		  //
		  } 
	  else if (strcmp(subsession->mediumName(), "audio") == 0) {
		  //
			  if (strcmp(subsession->codecName(), "AMR") == 0 ||
				  strcmp(subsession->codecName(), "AMR-WB") == 0) 
			  {				
				  // For AMR audio streams, we use a special sink that inserts AMR frame hdrs:
				  fileSink = AMRAudioFileSink::createNew(*env, outFileName,
						 fileSinkBufferSize, oneFilePerFrame);	
				  } 
			  else if (strcmp(subsession->codecName(), "VORBIS") == 0 ||
					  strcmp(subsession->codecName(), "OPUS") == 0) 
			  {
				  createOggFileSink = True;	
			  }//MPEG4-GENERIC
			  else if (strcmp(subsession->codecName(), "MPEG4-GENERIC"/*"PCMA"*/) == 0)
			  {
				  std::string strSample = extractSpecContent(sdpLine, "MPEG4-GENERIC/", "/");
				  std::string strConfig = extractSpecContent(sdpLine, "config=", ";");
				  uint32_t sample = 16000;
				  uint32_t config = 0x1408;

				  try {
					  if (!strSample.empty())
						  sample = string_to_uint32(strSample, 10);
					  if (!strConfig.empty())
						  config = string_to_uint32(strConfig, 16);
				  }
				  catch (const std::exception& e) {
					  std::cerr << "Error: " << e.what() << std::endl;
				  }

				  fileSink = CMyPcmaSink::createNew(*env, *subsession, sample, config, "PCMA");
			  }
      }
	  
	  //
      if (createOggFileSink) {
	fileSink = OggFileSink
	  ::createNew(*env, outFileName,
		      subsession->rtpTimestampFrequency(), subsession->fmtp_config());
      } else if (fileSink == NULL) {
	// Normal case:
	fileSink = FileSink::createNew(*env, outFileName,
				       fileSinkBufferSize, oneFilePerFrame);
      }
      subsession->sink = fileSink;

      if (subsession->sink == NULL) {
	*env << "Failed to create FileSink for \"" << outFileName
	     << "\": " << env->getResultMsg() << "\n";
      } else {
	if (singleMedium == NULL) {
	  *env << "Created output file: \"" << outFileName << "\"\n";
	} else {
	  *env << "Outputting data from the \"" << subsession->mediumName()
	       << "/" << subsession->codecName()
	       << "\" subsession to \"" << outFileName << "\"\n";
	}
	
	if (strcmp(subsession->mediumName(), "video") == 0 &&
	    strcmp(subsession->codecName(), "MP4V-ES") == 0 &&
	    subsession->fmtp_config() != NULL) {
	  // For MPEG-4 video RTP streams, the 'config' information
	  // from the SDP description contains useful VOL etc. headers.
	  // Insert this data at the front of the output file:
	  unsigned configLen;
	  unsigned char* configData
	    = parseGeneralConfigStr(subsession->fmtp_config(), configLen);
	  struct timeval timeNow;
	  gettimeofday(&timeNow, NULL);
	  fileSink->addData(configData, configLen, timeNow);
	  delete[] configData;
	}
	
	subsession->sink->startPlaying(*(subsession->readSource()),
				       subsessionAfterPlaying,
				       subsession);
	
	// Also set a handler to be called if a RTCP "BYE" arrives
	// for this subsession:
	if (subsession->rtcpInstance() != NULL) {
	  subsession->rtcpInstance()->setByeHandler(subsessionByeHandler, subsession);
	}
	
	madeProgress = True;
      }
    }
    if (!madeProgress) shutdown();
  }
}

void createPeriodicOutputFiles() {
  // Create a filename suffix that notes the time interval that's being recorded:
  char periodicFileNameSuffix[100];
  snprintf(periodicFileNameSuffix, sizeof periodicFileNameSuffix, "-%05d-%05d",
	   fileOutputSecondsSoFar, fileOutputSecondsSoFar + fileOutputInterval);
  createOutputFiles(periodicFileNameSuffix);

  // Schedule an event for writing the next output file:
  periodicFileOutputTask
    = env->taskScheduler().scheduleDelayedTask(fileOutputInterval*1000000,
					       (TaskFunc*)periodicFileOutputTimerHandler,
					       (void*)NULL);
}

void setupStreams() {
  static MediaSubsessionIterator* setupIter = NULL;
  if (setupIter == NULL) setupIter = new MediaSubsessionIterator(*session);
  while ((subsession = setupIter->next()) != NULL) {
    // We have another subsession left to set up:
    if (subsession->clientPortNum() == 0) continue; // port # was not set

    setupSubsession(subsession, streamUsingTCP, forceMulticastOnUnspecified, continueAfterSETUP);
    return;
  }

  // We're done setting up subsessions.
  delete setupIter;
  if (!madeProgress) shutdown();

  // Create output files:
  if (createReceivers) {
    if (fileOutputInterval > 0) {
      createPeriodicOutputFiles();
    } else {
      createOutputFiles("");
    }
  }

  // Finally, start playing each subsession, to start the data flow:
  if (duration == 0) {
    if (scale > 0) duration = session->playEndTime() - initialSeekTime; // use SDP end time
    else if (scale < 0) duration = initialSeekTime;
  }
  if (duration < 0) duration = 0.0;

  endTime = initialSeekTime;
  if (scale > 0) {
    if (duration <= 0) endTime = -1.0f;
    else endTime = initialSeekTime + duration;
  } else {
    endTime = initialSeekTime - duration;
    if (endTime < 0) endTime = 0.0f;
  }

  char const* absStartTime = initialAbsoluteSeekTime != NULL ? initialAbsoluteSeekTime : session->absStartTime();
  if (absStartTime != NULL) {
    // Either we or the server have specified that seeking should be done by 'absolute' time:
    startPlayingSession(session, absStartTime, session->absEndTime(), scale, continueAfterPLAY);
  } else {
    // Normal case: Seek by relative time (NPT):
    startPlayingSession(session, initialSeekTime, endTime, scale, continueAfterPLAY);
  }
}

void continueAfterPLAY(RTSPClient*, int resultCode, char* resultString) {
  if (resultCode != 0) {
    *env << "Failed to start playing session: " << resultString << "\n";
    delete[] resultString;
    shutdown();
    return;
  } else {
    *env << "Started playing session\n";
  }
  delete[] resultString;

  if (qosMeasurementIntervalMS > 0) {
    // Begin periodic QOS measurements:
    beginQOSMeasurement();
  }

  // Figure out how long to delay (if at all) before shutting down, or
  // repeating the playing
  Boolean timerIsBeingUsed = False;
  double secondsToDelay = duration;
  if (duration > 0) {
    // First, adjust "duration" based on any change to the play range (that was specified in the "PLAY" response):
    double rangeAdjustment = (session->playEndTime() - session->playStartTime()) - (endTime - initialSeekTime);
    if (duration + rangeAdjustment > 0.0) duration += rangeAdjustment;

    timerIsBeingUsed = True;
    double absScale = scale > 0 ? scale : -scale; // ASSERT: scale != 0
    secondsToDelay = duration/absScale + durationSlop;

    int64_t uSecsToDelay = (int64_t)(secondsToDelay*1000000.0);
    sessionTimerTask = env->taskScheduler().scheduleDelayedTask(uSecsToDelay, (TaskFunc*)sessionTimerHandler, (void*)NULL);
  }

  char const* actionString
    = createReceivers? "Receiving streamed data":"Data is being streamed";
  if (timerIsBeingUsed) {
    *env << actionString
		<< " (for up to " << secondsToDelay
		<< " seconds)...\n";
  } else {
#ifdef USE_SIGNALS
    pid_t ourPid = getpid();
    *env << actionString
		<< " (signal with \"kill -HUP " << (int)ourPid
		<< "\" or \"kill -USR1 " << (int)ourPid
		<< "\" to terminate)...\n";
#else
    *env << actionString << "...\n";
#endif
  }

  // Watch for incoming packets (if desired):
  checkForPacketArrival(NULL);
  checkInterPacketGaps(NULL);
}

void closeMediaSinks() {
  Medium::close(qtOut); qtOut = NULL;
  Medium::close(aviOut); aviOut = NULL;

  if (session == NULL) return;
  MediaSubsessionIterator iter(*session);
  MediaSubsession* subsession;
  while ((subsession = iter.next()) != NULL) {
    Medium::close(subsession->sink);
    subsession->sink = NULL;
  }
}

void subsessionAfterPlaying(void* clientData) {
  // Begin by closing this media subsession's stream:
  MediaSubsession* subsession = (MediaSubsession*)clientData;
  Medium::close(subsession->sink);
  subsession->sink = NULL;

  // Next, check whether *all* subsessions' streams have now been closed:
  MediaSession& session = subsession->parentSession();
  MediaSubsessionIterator iter(session);
  while ((subsession = iter.next()) != NULL) {
    if (subsession->sink != NULL) return; // this subsession is still active
  }

  // All subsessions' streams have now been closed
  sessionAfterPlaying();
}

void subsessionByeHandler(void* clientData) {
  struct timeval timeNow;
  gettimeofday(&timeNow, NULL);
  unsigned secsDiff = timeNow.tv_sec - startTime.tv_sec;

  MediaSubsession* subsession = (MediaSubsession*)clientData;
  *env << "Received RTCP \"BYE\" on \"" << subsession->mediumName()
	<< "/" << subsession->codecName()
	<< "\" subsession (after " << secsDiff
	<< " seconds)\n";

  // Act now as if the subsession had closed:
  subsessionAfterPlaying(subsession);
}

void sessionAfterPlaying(void* /*clientData*/) {
  if (!playContinuously) {
    shutdown(0);
  } else {
    // We've been asked to play the stream(s) over again.
    // First, reset state from the current session:
    if (env != NULL) {
      env->taskScheduler().unscheduleDelayedTask(periodicFileOutputTask);
      env->taskScheduler().unscheduleDelayedTask(sessionTimerTask);
      env->taskScheduler().unscheduleDelayedTask(arrivalCheckTimerTask);
      env->taskScheduler().unscheduleDelayedTask(interPacketGapCheckTimerTask);
      env->taskScheduler().unscheduleDelayedTask(qosMeasurementTimerTask);
    }
    totNumPacketsReceived = ~0;

    startPlayingSession(session, initialSeekTime, endTime, scale, continueAfterPLAY);
  }
}

void sessionTimerHandler(void* /*clientData*/) {
  sessionTimerTask = NULL;

  sessionAfterPlaying();
}

void periodicFileOutputTimerHandler(void* /*clientData*/) {
  fileOutputSecondsSoFar += fileOutputInterval;

  // First, close the existing output files:
  closeMediaSinks();

  // Then, create new output files:
  createPeriodicOutputFiles();
}

class qosMeasurementRecord {
public:
  qosMeasurementRecord(struct timeval const& startTime, RTPSource* src)
    : fSource(src), fNext(NULL),
      kbits_per_second_min(1e20), kbits_per_second_max(0),
      kBytesTotal(0.0),
      packet_loss_fraction_min(1.0), packet_loss_fraction_max(0.0),
      totNumPacketsReceived(0), totNumPacketsExpected(0) {
    measurementEndTime = measurementStartTime = startTime;

    RTPReceptionStatsDB::Iterator statsIter(src->receptionStatsDB());
    // Assume that there's only one SSRC source (usually the case):
    RTPReceptionStats* stats = statsIter.next(True);
    if (stats != NULL) {
      kBytesTotal = stats->totNumKBytesReceived();
      totNumPacketsReceived = stats->totNumPacketsReceived();
      totNumPacketsExpected = stats->totNumPacketsExpected();
    }
  }
  virtual ~qosMeasurementRecord() { delete fNext; }

  void periodicQOSMeasurement(struct timeval const& timeNow);

public:
  RTPSource* fSource;
  qosMeasurementRecord* fNext;

public:
  struct timeval measurementStartTime, measurementEndTime;
  double kbits_per_second_min, kbits_per_second_max;
  double kBytesTotal;
  double packet_loss_fraction_min, packet_loss_fraction_max;
  unsigned totNumPacketsReceived, totNumPacketsExpected;
};

static qosMeasurementRecord* qosRecordHead = NULL;

static void periodicQOSMeasurement(void* clientData); // forward

static unsigned nextQOSMeasurementUSecs;

static void scheduleNextQOSMeasurement() {
  nextQOSMeasurementUSecs += qosMeasurementIntervalMS*1000;
  struct timeval timeNow;
  gettimeofday(&timeNow, NULL);
  unsigned timeNowUSecs = timeNow.tv_sec*1000000 + timeNow.tv_usec;
  int usecsToDelay = nextQOSMeasurementUSecs - timeNowUSecs;

  qosMeasurementTimerTask = env->taskScheduler().scheduleDelayedTask(
     usecsToDelay, (TaskFunc*)periodicQOSMeasurement, (void*)NULL);
}

static void periodicQOSMeasurement(void* /*clientData*/) {
  struct timeval timeNow;
  gettimeofday(&timeNow, NULL);

  for (qosMeasurementRecord* qosRecord = qosRecordHead;
       qosRecord != NULL; qosRecord = qosRecord->fNext) {
    qosRecord->periodicQOSMeasurement(timeNow);
  }

  // Do this again later:
  scheduleNextQOSMeasurement();
}

void qosMeasurementRecord
::periodicQOSMeasurement(struct timeval const& timeNow) {
  unsigned secsDiff = timeNow.tv_sec - measurementEndTime.tv_sec;
  int usecsDiff = timeNow.tv_usec - measurementEndTime.tv_usec;
  double timeDiff = secsDiff + usecsDiff/1000000.0;
  measurementEndTime = timeNow;

  RTPReceptionStatsDB::Iterator statsIter(fSource->receptionStatsDB());
  // Assume that there's only one SSRC source (usually the case):
  RTPReceptionStats* stats = statsIter.next(True);
  if (stats != NULL) {
    double kBytesTotalNow = stats->totNumKBytesReceived();
    double kBytesDeltaNow = kBytesTotalNow - kBytesTotal;
    kBytesTotal = kBytesTotalNow;

    double kbpsNow = timeDiff == 0.0 ? 0.0 : 8*kBytesDeltaNow/timeDiff;
    if (kbpsNow < 0.0) kbpsNow = 0.0; // in case of roundoff error
    if (kbpsNow < kbits_per_second_min) kbits_per_second_min = kbpsNow;
    if (kbpsNow > kbits_per_second_max) kbits_per_second_max = kbpsNow;

    unsigned totReceivedNow = stats->totNumPacketsReceived();
    unsigned totExpectedNow = stats->totNumPacketsExpected();
    unsigned deltaReceivedNow = totReceivedNow - totNumPacketsReceived;
    unsigned deltaExpectedNow = totExpectedNow - totNumPacketsExpected;
    totNumPacketsReceived = totReceivedNow;
    totNumPacketsExpected = totExpectedNow;

    double lossFractionNow = deltaExpectedNow == 0 ? 0.0
      : 1.0 - deltaReceivedNow/(double)deltaExpectedNow;
    //if (lossFractionNow < 0.0) lossFractionNow = 0.0; //reordering can cause
    if (lossFractionNow < packet_loss_fraction_min) {
      packet_loss_fraction_min = lossFractionNow;
    }
    if (lossFractionNow > packet_loss_fraction_max) {
      packet_loss_fraction_max = lossFractionNow;
    }
  }
}

void beginQOSMeasurement() {
  // Set up a measurement record for each active subsession:
  struct timeval startTime;
  gettimeofday(&startTime, NULL);
  nextQOSMeasurementUSecs = startTime.tv_sec*1000000 + startTime.tv_usec;
  qosMeasurementRecord* qosRecordTail = NULL;
  MediaSubsessionIterator iter(*session);
  MediaSubsession* subsession;
  while ((subsession = iter.next()) != NULL) {
    RTPSource* src = subsession->rtpSource();
    if (src == NULL) continue;

    qosMeasurementRecord* qosRecord
      = new qosMeasurementRecord(startTime, src);
    if (qosRecordHead == NULL) qosRecordHead = qosRecord;
    if (qosRecordTail != NULL) qosRecordTail->fNext = qosRecord;
    qosRecordTail  = qosRecord;
  }

  // Then schedule the first of the periodic measurements:
  scheduleNextQOSMeasurement();
}

void printQOSData(int exitCode) {
  *env << "begin_QOS_statistics\n";
  
  // Print out stats for each active subsession:
  qosMeasurementRecord* curQOSRecord = qosRecordHead;
  if (session != NULL) {
    MediaSubsessionIterator iter(*session);
    MediaSubsession* subsession;
    while ((subsession = iter.next()) != NULL) {
      RTPSource* src = subsession->rtpSource();
      if (src == NULL) continue;
      
      *env << "subsession\t" << subsession->mediumName()
	   << "/" << subsession->codecName() << "\n";
      
      unsigned numPacketsReceived = 0, numPacketsExpected = 0;
      
      if (curQOSRecord != NULL) {
	numPacketsReceived = curQOSRecord->totNumPacketsReceived;
	numPacketsExpected = curQOSRecord->totNumPacketsExpected;
      }
      *env << "num_packets_received\t" << numPacketsReceived << "\n";
      *env << "num_packets_lost\t" << int(numPacketsExpected - numPacketsReceived) << "\n";
      
      if (curQOSRecord != NULL) {
	unsigned secsDiff = curQOSRecord->measurementEndTime.tv_sec
	  - curQOSRecord->measurementStartTime.tv_sec;
	int usecsDiff = curQOSRecord->measurementEndTime.tv_usec
	  - curQOSRecord->measurementStartTime.tv_usec;
	double measurementTime = secsDiff + usecsDiff/1000000.0;
	*env << "elapsed_measurement_time\t" << measurementTime << "\n";
	
	*env << "kBytes_received_total\t" << curQOSRecord->kBytesTotal << "\n";
	
	*env << "measurement_sampling_interval_ms\t" << qosMeasurementIntervalMS << "\n";
	
	if (curQOSRecord->kbits_per_second_max == 0) {
	  // special case: we didn't receive any data:
	  *env <<
	    "kbits_per_second_min\tunavailable\n"
	    "kbits_per_second_ave\tunavailable\n"
	    "kbits_per_second_max\tunavailable\n";
	} else {
	  *env << "kbits_per_second_min\t" << curQOSRecord->kbits_per_second_min << "\n";
	  *env << "kbits_per_second_ave\t"
	       << (measurementTime == 0.0 ? 0.0 : 8*curQOSRecord->kBytesTotal/measurementTime) << "\n";
	  *env << "kbits_per_second_max\t" << curQOSRecord->kbits_per_second_max << "\n";
	}
	
	*env << "packet_loss_percentage_min\t" << 100*curQOSRecord->packet_loss_fraction_min << "\n";
	double packetLossFraction = numPacketsExpected == 0 ? 1.0
	  : 1.0 - numPacketsReceived/(double)numPacketsExpected;
	if (packetLossFraction < 0.0) packetLossFraction = 0.0;
	*env << "packet_loss_percentage_ave\t" << 100*packetLossFraction << "\n";
	*env << "packet_loss_percentage_max\t"
	     << (packetLossFraction == 1.0 ? 100.0 : 100*curQOSRecord->packet_loss_fraction_max) << "\n";
	
	RTPReceptionStatsDB::Iterator statsIter(src->receptionStatsDB());
	// Assume that there's only one SSRC source (usually the case):
	RTPReceptionStats* stats = statsIter.next(True);
	if (stats != NULL) {
	  *env << "inter_packet_gap_ms_min\t" << stats->minInterPacketGapUS()/1000.0 << "\n";
	  struct timeval totalGaps = stats->totalInterPacketGaps();
	  double totalGapsMS = totalGaps.tv_sec*1000.0 + totalGaps.tv_usec/1000.0;
	  unsigned totNumPacketsReceived = stats->totNumPacketsReceived();
	  *env << "inter_packet_gap_ms_ave\t"
	       << (totNumPacketsReceived == 0 ? 0.0 : totalGapsMS/totNumPacketsReceived) << "\n";
	  *env << "inter_packet_gap_ms_max\t" << stats->maxInterPacketGapUS()/1000.0 << "\n";
	}
	
	curQOSRecord = curQOSRecord->fNext;
      }
    }
  }

  *env << "end_QOS_statistics\n";
  delete qosRecordHead;
}

Boolean areAlreadyShuttingDown = False;
int shutdownExitCode;
void shutdown(int exitCode) {
  if (areAlreadyShuttingDown) return; // in case we're called after receiving a RTCP "BYE" while in the middle of a "TEARDOWN".
  areAlreadyShuttingDown = True;

  shutdownExitCode = exitCode;
  if (env != NULL) {
    env->taskScheduler().unscheduleDelayedTask(periodicFileOutputTask);
    env->taskScheduler().unscheduleDelayedTask(sessionTimerTask);
    env->taskScheduler().unscheduleDelayedTask(arrivalCheckTimerTask);
    env->taskScheduler().unscheduleDelayedTask(interPacketGapCheckTimerTask);
    env->taskScheduler().unscheduleDelayedTask(qosMeasurementTimerTask);
  }

  if (qosMeasurementIntervalMS > 0) {
    printQOSData(exitCode);
  }

  // Teardown, then shutdown, any outstanding RTP/RTCP subsessions
  Boolean shutdownImmediately = True; // by default
  if (session != NULL) {
    RTSPClient::responseHandler* responseHandlerForTEARDOWN = NULL; // unless:
    if (waitForResponseToTEARDOWN) {
      shutdownImmediately = False;
      responseHandlerForTEARDOWN = continueAfterTEARDOWN;
    }
    tearDownSession(session, responseHandlerForTEARDOWN);
  }

  if (shutdownImmediately) continueAfterTEARDOWN(NULL, 0, NULL);
}

void continueAfterTEARDOWN(RTSPClient*, int /*resultCode*/, char* resultString) {
  delete[] resultString;

  // Now that we've stopped any more incoming data from arriving, close our output files:
  closeMediaSinks();
  Medium::close(session);

  // Finally, shut down our client:
  delete ourAuthenticator;
  delete authDBForREGISTER;
  Medium::close(ourClient);

  //  2014/06/06
  OutputDebugString(  _T(  "rtspCli::continueAfterTEARDOWN: exit\n"  )  );
  dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  _T(  "rtspCli::continueAfterTEARDOWN: exit"  )  );
  int  i;  //  wait for showInfo finished
  for  (  i  =  0;  i  <  2  ;  i  ++  )  {
	   Sleep(  50  );
  }


  // Adios...
  exit(shutdownExitCode);
}

void signalHandlerShutdown(int /*sig*/) {
  *env << "Got shutdown signal\n";
  waitForResponseToTEARDOWN = False; // to ensure that we end, even if the server does not respond to our TEARDOWN
  shutdown(0);
}

void checkForPacketArrival(void* /*clientData*/) {
  if (!notifyOnPacketArrival) return; // we're not checking

  // Check each subsession, to see whether it has received data packets:
  unsigned numSubsessionsChecked = 0;
  unsigned numSubsessionsWithReceivedData = 0;
  unsigned numSubsessionsThatHaveBeenSynced = 0;

  MediaSubsessionIterator iter(*session);
  MediaSubsession* subsession;
  while ((subsession = iter.next()) != NULL) {
    RTPSource* src = subsession->rtpSource();
    if (src == NULL) continue;
    ++numSubsessionsChecked;

    if (src->receptionStatsDB().numActiveSourcesSinceLastReset() > 0) {
      // At least one data packet has arrived
      ++numSubsessionsWithReceivedData;
    }
    if (src->hasBeenSynchronizedUsingRTCP()) {
      ++numSubsessionsThatHaveBeenSynced;
    }
  }

  unsigned numSubsessionsToCheck = numSubsessionsChecked;
  // Special case for "QuickTimeFileSink"s and "AVIFileSink"s:
  // They might not use all of the input sources:
  if (qtOut != NULL) {
    numSubsessionsToCheck = qtOut->numActiveSubsessions();
  } else if (aviOut != NULL) {
    numSubsessionsToCheck = aviOut->numActiveSubsessions();
  }

  Boolean notifyTheUser;
  if (!syncStreams) {
    notifyTheUser = numSubsessionsWithReceivedData > 0; // easy case
  } else {
    notifyTheUser = numSubsessionsWithReceivedData >= numSubsessionsToCheck
      && numSubsessionsThatHaveBeenSynced == numSubsessionsChecked;
    // Note: A subsession with no active sources is considered to be synced
  }
  if (notifyTheUser) {
    struct timeval timeNow;
    gettimeofday(&timeNow, NULL);
	char timestampStr[100];
	sprintf(timestampStr, "%ld%03ld", timeNow.tv_sec, (long)(timeNow.tv_usec/1000));
    *env << (syncStreams ? "Synchronized d" : "D")
		<< "ata packets have begun arriving [" << timestampStr << "]\007\n";
    return;
  }

  // No luck, so reschedule this check again, after a delay:
  int uSecsToDelay = 100000; // 100 ms
  arrivalCheckTimerTask
    = env->taskScheduler().scheduleDelayedTask(uSecsToDelay,
			       (TaskFunc*)checkForPacketArrival, NULL);
}

void checkInterPacketGaps(void* /*clientData*/) {
  if (interPacketGapMaxTime == 0) return; // we're not checking

  // Check each subsession, counting up how many packets have been received:
  unsigned newTotNumPacketsReceived = 0;

  MediaSubsessionIterator iter(*session);
  MediaSubsession* subsession;
  while ((subsession = iter.next()) != NULL) {
    RTPSource* src = subsession->rtpSource();
    if (src == NULL) continue;
    newTotNumPacketsReceived += src->receptionStatsDB().totNumPacketsReceived();
  }

  if (newTotNumPacketsReceived == totNumPacketsReceived) {
    // No additional packets have been received since the last time we
    // checked, so end this stream:
    *env << "Closing session, because we stopped receiving packets.\n";
    interPacketGapCheckTimerTask = NULL;
    sessionAfterPlaying();
  } else {
    totNumPacketsReceived = newTotNumPacketsReceived;
    // Check again, after the specified delay:
    interPacketGapCheckTimerTask
      = env->taskScheduler().scheduleDelayedTask(interPacketGapMaxTime*1000000,
				 (TaskFunc*)checkInterPacketGaps, NULL);
  }
}
