
#include "api/audio/audio_mixer.h"

#include <cstring>
#include <iostream>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "common_audio/wav_file.h"
#include "modules/audio_mixer/audio_mixer_impl.h"
#include "modules/audio_mixer/default_output_rate_calculator.h"
#include "rtc_base/strings/string_builder.h"


#include "qycxProjs/qis_tmpHelp/help_audioMixerLib/include/audioMixerLibCommon.h"

//
typedef  struct  __tmp_param_playA_t {
                 //
                 PF_inStream4 pf_in;
                 void *p0_in;

                 //
                 int    index_source;
                 //
                 int    sample_rate;
                 int    number_of_channels;  
  int ii;
               
} Tmp_param_playA;

//
class CTmpReader {
    struct  {
        Tmp_param_playA  param;
    }   m_var;

public:
CTmpReader(Tmp_param_playA param)
{
memset(&m_var,0,sizeof(m_var));
m_var.param=param;
int  ii  =  0;
printf(  "%d",ii);

}
~CTmpReader()
{
int  ii  =  0;
printf(  "%d",ii);

}


//
size_t ReadSamples(const size_t num_samples, 
                              int16_t* const samples) 
{
    //
    int len = num_samples*sizeof(int16_t);
    if  (  len !=m_var.param.pf_in(m_var.param.p0_in,(void*)(long long)m_var.param.index_source,(void*)(long long)samples,(void*)(long long)len)  )  {
return 0;
}
    
    //
return num_samples;
}


};


//
namespace webrtc {
namespace test {

class myFilePlayingSource : public AudioMixer::Source {
 public:
     explicit myFilePlayingSource(Tmp_param_playA param) {


//WavReader kk("ddd");
        wav_reader_=std::unique_ptr<CTmpReader>(new CTmpReader(param));
sample_rate_hz_=param.sample_rate;
samples_per_channel_=sample_rate_hz_/100;
number_of_channels_=param.number_of_channels;


       return;
  }

     #if  0
     //
  explicit myFilePlayingSource(std::string filename)
      : wav_reader_(new WavReader(filename)),
        sample_rate_hz_(wav_reader_->sample_rate()),
        samples_per_channel_(sample_rate_hz_ / 100),
        number_of_channels_(wav_reader_->num_channels()) 
  {
    int ii = 0;
    printf("%d", ii);
  }
      #endif

  AudioFrameInfo GetAudioFrameWithInfo(int target_rate_hz,
                                       AudioFrame* frame) override {
    frame->samples_per_channel_ = samples_per_channel_;
    frame->num_channels_ = number_of_channels_;
    frame->sample_rate_hz_ = target_rate_hz;

    RTC_CHECK_EQ(target_rate_hz, sample_rate_hz_);

    const size_t num_to_read = number_of_channels_ * samples_per_channel_;
    const size_t num_read =
        wav_reader_->ReadSamples(num_to_read, frame->mutable_data());

    file_has_ended_ = num_to_read != num_read;
    if (file_has_ended_) {
      frame->Mute();
    }
    return file_has_ended_ ? AudioFrameInfo::kMuted : AudioFrameInfo::kNormal;
  }

  int Ssrc() const override { return 0; }

  int PreferredSampleRate() const override { return sample_rate_hz_; }

  bool FileHasEnded() const { return file_has_ended_; }

  std::string ToString() const {
    rtc::StringBuilder ss;
#if 0
    ss << "{rate: " << sample_rate_hz_ << ", channels: " << number_of_channels_
       << ", samples_tot: " << wav_reader_->num_samples() << "}";
#endif
ss <<"rate";
    return ss.Release();
  }

 private:
  //std::unique_ptr<WavReader> wav_reader_;
std::unique_ptr<CTmpReader> wav_reader_;
  int sample_rate_hz_;
  int samples_per_channel_;
  int number_of_channels_;
  bool file_has_ended_ = false;
};
}  // namespace test
}  // namespace webrtc


const std::vector<Tmp_param_playA> parse_input_files(int  nSources,PF_inStream4 pf_in, void *p0_in) 
{
  std::vector<Tmp_param_playA> result;
  for (int i  = 0;  i <nSources;  i++  )  {
  #if  0
    char buf[128];
    auto x = std::string(ltoa(i,buf,10));
    if (!x.empty()) 

  
      result.push_back(x);
    }
    #endif

    //
    Tmp_param_playA  param;
    memset(&param,0,sizeof(param));
    param.index_source  =  i;  
   param.pf_in=pf_in;
    param.p0_in=p0_in;
      
      param.sample_rate =  16000;
       param.number_of_channels=1;
        //        
        result.push_back(param);
  }
  return result;
}


//
class CTmp_mixer_obj {

    rtc::scoped_refptr<webrtc::AudioMixerImpl> mixer;
    std::vector<webrtc::test::myFilePlayingSource> sources;

    //
    webrtc::AudioFrame frame;

    bool all_streams_finished = false;
  

    //
   public:
    CTmp_mixer_obj(int nSources,PF_inStream4 pf_in, void *p0_in) {
        //
        mixer=      webrtc::AudioMixerImpl::Create(
          std::unique_ptr<webrtc::OutputRateCalculator>(
              new webrtc::DefaultOutputRateCalculator()),
                true  );

        //
        const std::vector<Tmp_param_playA> input_files = parse_input_files(nSources,pf_in,p0_in);
  
        //
        //const int num_channels = 1;  // absl::GetFlag(FLAGS_stereo) ? 2 : 1;
        sources.reserve(input_files.size());
        for (const auto& input_file : input_files) 
        {
          sources.emplace_back(input_file);
        }

        for (auto& source : sources) {
          auto error = mixer->AddSource(&source);
          RTC_CHECK(error);
        }

        if (sources.empty()) {
          std::cout << "Need at least one source!\n";
          return;
        }


        return;
    }
    ~CTmp_mixer_obj() {

    }


    //
    int doMix(char *  dataBuf, unsigned  int  *puiSize ) { 
        int iErr = -1;

        if (!dataBuf||!puiSize)
          return -1;

        if (this->all_streams_finished)
          return -1;

        //
        int num_channels = 1;
        int sample_rate = 16000;

        //
        mixer->Mix(num_channels, &frame);
        RTC_CHECK_EQ(sample_rate / 100, frame.samples_per_channel_);
        RTC_CHECK_EQ(sample_rate, frame.sample_rate_hz_);
        RTC_CHECK_EQ(num_channels, frame.num_channels_);
        #if  0
        wav_writer.WriteSamples(frame.data(),
                                num_channels * frame.samples_per_channel_);
        #endif
        int nWrite =
            num_channels * frame.samples_per_channel_ * sizeof(int16_t);
        if (nWrite > (int)*puiSize) {
          goto errLabel;
        }
        memcpy(dataBuf, frame.data(), nWrite);
        *puiSize = nWrite;

        //
        all_streams_finished =
            std::all_of(sources.begin(), sources.end(),
                        [](const webrtc::test::myFilePlayingSource& source) {
                          return source.FileHasEnded();
                        });

        iErr = 0;
    errLabel:

        return iErr;
    }

};





//
int initAudioMixerLibObj(int sampleRate,int nSources,                                                                   
    PF_inStream4  pf_in,  void* p0_in,                       
    void** ppObj)
{
  int iErr = -1;

  if (sampleRate != 16000) {
    return -1;
  }
  if (nSources == 0) {
    return -1;
  }
  if (!ppObj) {
    return -1;
  }
  if (*ppObj) {
    return -1;
  }
  AudioMixer_obj* pObj = NULL;
  int size = sizeof(AudioMixer_obj);
  pObj = (AudioMixer_obj*)malloc(size);
  if (pObj == NULL) {
    return -1;
  }
  memset(pObj, 0, size);
  //pObj->sample_rate = sampleRate;
  //
  pObj->pTMP_mixer_obj = new CTmp_mixer_obj(nSources,pf_in,p0_in);
  if (pObj->pTMP_mixer_obj == nullptr)
    goto errLabel;

//
pObj->pf_in=pf_in;
pObj->p0_in=p0_in;


  //
  *ppObj = pObj;

  iErr = 0;
errLabel:

  if (iErr) {
    exitAudioMixerLibObj((void**)&pObj);
  }

  return 0;
}

int exitAudioMixerLibObj(void** ppObj) 
{   
   if (ppObj == nullptr) {     
    return 0;
  }
  if (!*ppObj) {
    return 0;
  }
  //
  AudioMixer_obj* pObj = (AudioMixer_obj*)*ppObj;

  //
  if (pObj->pTMP_mixer_obj) {
    CTmp_mixer_obj* p = (CTmp_mixer_obj*)pObj->pTMP_mixer_obj;
    delete p;
    //
    pObj->pTMP_mixer_obj = nullptr;
  }


  free(pObj);
  *ppObj = NULL;

  return 0;
}


//
int audioMixerLibObj_doMix(void *pObjParam,char *dataBuf, unsigned  int  *puiSize)
{
int  iErr =  -1;

 AudioMixer_obj* pObj = (AudioMixer_obj*)pObjParam;
 if  (  !pObj)return  -1;

CTmp_mixer_obj  * pTmpMixerObj  =  (  CTmp_mixer_obj*)pObj->pTMP_mixer_obj;
if  (  !pTmpMixerObj)return  -1;


if (pTmpMixerObj->doMix(dataBuf, puiSize))
  goto errLabel;



//
iErr  =  0;
errLabel:
return  iErr;
}



