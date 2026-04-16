/*
 *  Copyright 2012 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

// clang-format off
// clang formating would change include order.
#include <windows.h>
#include <shellapi.h>  // must come after windows.h
// clang-format on

#include <string>
#include <vector>

#include "absl/flags/parse.h"
#include "examples/peerconnection/client/conductor.h"
#include "examples/peerconnection/client/flag_defs.h"
#include "examples/peerconnection/client/main_wnd.h"
#include "examples/peerconnection/client/peer_connection_client.h"
#include "rtc_base/checks.h"
//#include "rtc_base/constructor_magic.h"
#include "rtc_base/ssl_adapter.h"
#include "rtc_base/string_utils.h"  // For ToUtf8
#include "rtc_base/win32_socket_init.h"
//#include "rtc_base/win32_socket_server.h"
#include "system_wrappers/include/field_trial.h"
#include "test/field_trial.h"

//#include "modules/audio_processing/aec3/qycxProjs/qis_tmpHelp/help_webrtc/include/tmpFunc.h"
#include "qycxProjs/qis_tmpHelp/help_audioProc/include/audioProcPublic.h"


//
namespace {
// A helper class to translate Windows command line arguments into UTF8,
// which then allows us to just pass them to the flags system.
// This encapsulates all the work of getting the command line and translating
// it to an array of 8-bit strings; all you have to do is create one of these,
// and then call argc() and argv().
class WindowsCommandLineArguments {
 public:
  WindowsCommandLineArguments();

  int argc() { return argv_.size(); }
  char** argv() { return argv_.data(); }

 private:
  // Owned argument strings.
  std::vector<std::string> args_;
  // Pointers, to get layout compatible with char** argv.
  std::vector<char*> argv_;

 private:
  //RTC_DISALLOW_COPY_AND_ASSIGN(WindowsCommandLineArguments);
};

WindowsCommandLineArguments::WindowsCommandLineArguments() {
  // start by getting the command line.
  LPCWSTR command_line = ::GetCommandLineW();
  // now, convert it to a list of wide char strings.
  int argc;
  LPWSTR* wide_argv = ::CommandLineToArgvW(command_line, &argc);

  // iterate over the returned wide strings;
  for (int i = 0; i < argc; ++i) {
    args_.push_back(rtc::ToUtf8(wide_argv[i], wcslen(wide_argv[i])));
    // make sure the argv array points to the string data.
    argv_.push_back(const_cast<char*>(args_.back().c_str()));
  }
  LocalFree(wide_argv);
}

}  // namespace

//
#define  NN  160

//
#if  10
int testAec() {
  {
    int iErr = -1;
    FILE *ref_fp = NULL, *mic_fp = NULL, *out_fp = NULL;
    short ref_buf[NN], mic_buf[NN];
    //short out_buf[NN];

    //class AudioBuffer ref(NN, 1, NN, 1, NN);  // render
    //class AudioBuffer mic(NN, 1, NN, 1, NN);  // capture

    //
    const char* fn_mic = "c:\\tttbbb\\124\\mic.pcm";
    const char* fn_ref = "c:\\tttbbb\\124\\162_deced.pcm";
    const char* fn_out = "c:\\tttbbb\\124\\aec_out.";

    //
    fn_mic= "d:\\ly\\pcm\\ly1.pcm";
    fn_ref ="d:\\ly\\pcm\\ly2.pcm";
    fn_out="d:\\ly\\pcm\\aec_out.";


    //
    int delayInMs = 0;
    char fileName_out[256];
    _snprintf(fileName_out, sizeof(fileName_out), "%s%d.pcm", fn_out,
              delayInMs);

    //
    mic_fp = fopen(fn_mic, "rb");
    ref_fp = fopen(fn_ref, "rb");
    out_fp = fopen(fileName_out, "wb");

    void* pObj = NULL;


    if (initAecObj(16000, &pObj))
      return -1;

  
    while (!feof(mic_fp) && !feof(ref_fp)) {
      fread(mic_buf, sizeof(short), NN, mic_fp);
      fread(ref_buf, sizeof(short), NN, ref_fp);

      //
      if (aecObj_doAec(pObj, (char*)ref_buf, NN * 2, (char*)mic_buf, NN * 2)) {
        goto errLabel;
      
      }

      /*
      for (int i = 0; i < NN; i += 1) {
        out_buf[i] = (short)(mic.channels_f()[0][i] + 0.5);
      }
      */


      //fwrite(out_buf, sizeof(short), NN, out_fp);
      fwrite(mic_buf, NN * 2, 1, out_fp);
    }
    iErr = 0;

  errLabel:

    exitAecObj(&pObj);

    fclose(out_fp);
    fclose(ref_fp);
    fclose(mic_fp);

    return iErr;
  }
}
#endif

//
typedef struct __tmpMixerInfo_t {
  FILE *fp_1, *fp_2, *fp_out;
  int ii;

} Tmp_mixer_info;


//
int my_in(void* p0, void* p1, void* p2, void* p3) 
{
  Tmp_mixer_info* pTmi = (Tmp_mixer_info*)p0;
  int index_source = (int)(long long)p1;
  char* buf = (char*)p2;
  int size = (int)(long long)p3;

  #if 0
  printf("%d", pTmi->ii);
  printf("%d",index_source);
  printf("%s",buf);
  printf("%d",size);
  #endif

  int n = 0;
  //
  switch (index_source) { 
    case 0:
      n=fread(buf, size, 1, pTmi->fp_1);
      break;
    case 1:
      n = fread(buf, size, 1, pTmi->fp_2);
      break;
    default:
      break;

  }
  if (n != 1) {
    return 0;
  }

  return size;
}


//
int testAudioMixer() {
  void* pObj = nullptr;

  //
  Tmp_mixer_info tmi;
  memset(&tmi, 0, sizeof(tmi));
  
  //
  //
  const char* fn_1 = "c:\\tttbbb\\124\\mic.pcm";
  const char* fn_2 = "c:\\tttbbb\\124\\162_deced.pcm";
  const char* fn_out = "c:\\tttbbb\\124\\aec_out.";

  //
  fn_1 = "d:\\ly\\pcm\\ly1.pcm";
  fn_2 = "d:\\ly\\pcm\\ly2.pcm";
  fn_out = "d:\\ly\\pcm\\mix_out.";

  //
  int delayInMs = 0;
  char fileName_out[256];
  _snprintf(fileName_out, sizeof(fileName_out), "%s%d.pcm", fn_out, delayInMs);

  //
  tmi.fp_1 = fopen(fn_1, "rb");
  tmi.fp_2 = fopen(fn_2, "rb");
  tmi.fp_out = fopen(fileName_out, "wb");


  //
  if(initAudioMixerObj(16000, 2, my_in, &tmi, &pObj))  goto  errLabel;

  //
  char buf[16000 * 2];
  unsigned int len;


  //
  for (;;) {
    len = sizeof(buf);

    if (audioMixerObj_doMix(pObj, buf, &len)) {
      break;
    }

    //
    fwrite(buf, len, 1, tmi.fp_out);


    //
    continue;
  }


errLabel:

  exitAudioMixerObj(&pObj);

      fclose(tmi.fp_out);
  fclose(tmi.fp_1);
  fclose(tmi.fp_2);

  return 0;
}




//
  int PASCAL wWinMain(HINSTANCE instance,
                    HINSTANCE prev_instance,
                    wchar_t* cmd_line,
                    int cmd_show) {
  //rtc::WinsockInitializer winsock_init;
  //rtc::Win32SocketServer w32_ss;
  //rtc::Win32Thread w32_thread(&w32_ss);
  //rtc::ThreadManager::Instance()->SetCurrentThread(&w32_thread);

  WindowsCommandLineArguments win_args;
  int argc = win_args.argc();
  char** argv = win_args.argv();

  absl::ParseCommandLine(argc, argv);

  //
  int ii=0;
  //ii  =  aec_doTest();
  printf("%d", ii);
  //testAec();
testAudioMixer();
  return 0;

  #if  0
  // InitFieldTrialsFromString stores the char*, so the char array must outlive
  // the application.
  const std::string forced_field_trials =
      absl::GetFlag(FLAGS_force_fieldtrials);
  webrtc::field_trial::InitFieldTrialsFromString(forced_field_trials.c_str());

  // Abort if the user specifies a port that is outside the allowed
  // range [1, 65535].
  if ((absl::GetFlag(FLAGS_port) < 1) || (absl::GetFlag(FLAGS_port) > 65535)) {
    printf("Error: %i is not a valid port.\n", absl::GetFlag(FLAGS_port));
    return -1;
  }

  const std::string server = absl::GetFlag(FLAGS_server);
  MainWnd wnd(server.c_str(), absl::GetFlag(FLAGS_port),
              absl::GetFlag(FLAGS_autoconnect), absl::GetFlag(FLAGS_autocall));
  if (!wnd.Create()) {
    RTC_NOTREACHED();
    return -1;
  }

  rtc::InitializeSSL();
  PeerConnectionClient client;
  rtc::scoped_refptr<Conductor> conductor(
      new rtc::RefCountedObject<Conductor>(&client, &wnd));

  // Main loop.
  MSG msg;
  BOOL gm;
  while ((gm = ::GetMessage(&msg, NULL, 0, 0)) != 0 && gm != -1) {
    if (!wnd.PreTranslateMessage(&msg)) {
      ::TranslateMessage(&msg);
      ::DispatchMessage(&msg);
    }
  }

  if (conductor->connection_active() || client.is_connected()) {
    while ((conductor->connection_active() || client.is_connected()) &&
           (gm = ::GetMessage(&msg, NULL, 0, 0)) != 0 && gm != -1) {
      if (!wnd.PreTranslateMessage(&msg)) {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
      }
    }
  }
  #endif


  //rtc::CleanupSSL();
  //return 0;
}
