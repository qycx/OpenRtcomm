
//
#include "modules/audio_processing/aec3/echo_canceller3.h"
#include "qycxProjs/qis_tmpHelp/help_aec3lib/include/aec3libCommon.h"


#include <deque>
#include <memory>
#include <string>
#include <utility>
#include <vector>


#include "modules/audio_processing/aec3/aec3_common.h"


#include "modules/audio_processing/aec3/block_processor.h"
#include "modules/audio_processing/aec3/frame_blocker.h"

#include "modules/audio_processing/aec3/mock/mock_block_processor.h"


#include "modules/audio_processing/audio_buffer.h"
#include "modules/audio_processing/high_pass_filter.h"
#include "modules/audio_processing/utility/cascaded_biquad_filter.h"


#include "rtc_base/strings/string_builder.h"
#include "test/field_trial.h"
#include "test/gmock.h"
#include "test/gtest.h"


////////////////////////






//
namespace webrtc {

    /*
#define SAMPLE_RATE (16000)
#define NN (160 * 2)  // frame * channel num

    
int test_main(int argc, char** argv) {
  FILE *ref_fp=NULL, *mic_fp=NULL, *out_fp=NULL;
  short ref_buf[NN], mic_buf[NN], out_buf[NN];

  class AudioBuffer ref(NN >> 1, 2, NN >> 1, 2, NN >> 1);  // render  
  class AudioBuffer mic(NN >> 1, 2, NN >> 1, 2, NN >> 1);  // capture

  //
  const char* fn_mic = "c:\\tttbbb\\124\\mic.pcm";
  const char* fn_ref = "c:\\tttbbb\\124\\164_deced.pcm";
  const char* fn_out = "c:\\tttbbb\\124\\aec_out.pcm";



  //
  mic_fp = fopen(fn_mic, "rb");
  ref_fp = fopen(fn_ref, "rb");
  out_fp = fopen(fn_out, "wb");

  class EchoCanceller3 aec3(EchoCanceller3Config(), SAMPLE_RATE, 1,1);

  while (!feof(mic_fp) && !feof(ref_fp)) {
    fread(mic_buf, sizeof(short), NN, mic_fp);
    fread(ref_buf, sizeof(short), NN, ref_fp);

    for (int i = 0; i < NN; i += 2) {
      mic.channels_f()[0][i >> 1] = (float)(mic_buf[i]);
      mic.channels_f()[1][i >> 1] = (float)(mic_buf[i + 1]);
      ref.channels_f()[0][i >> 1] = (float)(ref_buf[i]);
      ref.channels_f()[1][i >> 1] = (float)(ref_buf[i + 1]);
    }

    aec3.AnalyzeCapture(&mic);
    aec3.AnalyzeRender(&ref);
    aec3.ProcessCapture(&mic, false);

    for (int i = 0; i < NN; i += 2) {
      out_buf[i] = (short)(mic.channels_f()[0][i >> 1] + 0.5);
      out_buf[i + 1] = (short)(mic.channels_f()[1][i >> 1] + 0.5);
    }

    fwrite(out_buf, sizeof(short), NN, out_fp);
  }

  fclose(out_fp);
  fclose(ref_fp);
  fclose(mic_fp);

  

  return 0;
}
*/

    #define SAMPLE_RATE 16000
    #define MY_input_num_channels   1
#define NN (160 * 1)  // frame * channel num

    int test_main(int argc, char** argv) 
    {

  AudioBuffer ref(NN, (size_t)MY_input_num_channels, (size_t)NN, (size_t)1, (size_t)NN, (size_t)1);  // render

         #if  10
 
  FILE *ref_fp = NULL, *mic_fp = NULL, *out_fp = NULL;
  short ref_buf[NN], mic_buf[NN], out_buf[NN];

  class AudioBuffer mic(NN , 1, NN , 1, NN,1 );  // capture

  //
  const char* fn_mic = "c:\\tttbbb\\124\\mic.pcm";
  const char* fn_ref = "c:\\tttbbb\\124\\162_deced.pcm";
  const char* fn_out = "c:\\tttbbb\\124\\aec_out.";

  int delayInMs = 0;
  char fileName_out[256];
  _snprintf(fileName_out, sizeof(fileName_out), "%s%d.pcm", fn_out, delayInMs);

  //
  mic_fp = fopen(fn_mic, "rb");
  ref_fp = fopen(fn_ref, "rb");
  out_fp = fopen(fileName_out, "wb");

  class EchoCanceller3 aec3(EchoCanceller3Config(), absl::nullopt,  SAMPLE_RATE, 1,                            1);

  aec3.SetAudioBufferDelay(delayInMs);
    
  while (!feof(mic_fp) && !feof(ref_fp)) {
    fread(mic_buf, sizeof(short), NN, mic_fp);
    fread(ref_buf, sizeof(short), NN, ref_fp);

    for (int i = 0; i < NN; i += 1) {
      mic.channels_f()[0][i] = (float)(mic_buf[i]);
      ref.channels_f()[0][i ] = (float)(ref_buf[i]);
    }
    //
    //
    aec3.AnalyzeCapture(&mic);
    aec3.AnalyzeRender(&ref);
    aec3.ProcessCapture(&mic, false);

    for (int i = 0; i < NN; i += 1) {
      out_buf[i] = (short)(mic.channels_f()[0][i] + 0.5);
    }

    fwrite(out_buf, sizeof(short), NN, out_fp);
  }

  fclose(out_fp);
  fclose(ref_fp);
  fclose(mic_fp);

  #endif

  return 0;
}




  int test1()
{
  //EchoCanceller3Tester tt(16000);
  //doTest888();

  return 0;
}




}  // namespace webrtc




    int aec3lib_doTest() 
{
  //int ii = 0;
  //ii++;

  webrtc::test_main(0, NULL);
  //webrtc::test1();
  //aec3lib_doTest888();
  
  //
  

  return 567;
}

    
//
//

