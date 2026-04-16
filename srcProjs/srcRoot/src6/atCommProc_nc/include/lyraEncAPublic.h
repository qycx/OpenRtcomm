
#ifndef  __lyraEncAPublic_h__
#define  __lyraEncAPublic_h__		//  {


//
#include "myTypes_basic.h"
#include "qyDefs_open.h"



#ifdef _WIN32
#ifdef MATH_EXPORTS
#define MATH_API __declspec(dllexport)
#else
#define MATH_API __declspec(dllimport)
#endif
#else
#define MATH_API
#endif


//
extern "C" {
/*
         MATH_API bool EncodeWav(const std::vector<int16_t>& wav_data, int
   num_channels, int sample_rate_hz, int bitrate, bool enable_preprocessing,
               bool enable_dtx, const std::string& model_path,
               std::vector<uint8_t>* encoded_features);
               */

MATH_API int lyraEncA_init(int bitrate, char* str_model_path,
                             PF_commonHandler4 pf_in, void* p0_in,
                             PF_commonHandler4 pf_out, void* p0_out,
                             void** ppLyraEncA);

    MATH_API int lyraEncA_exit(void** ppLyraEncA);

MATH_API int doLyraEncA(void* pLyraEncAParam, int* piStep);


}




//
#endif  //  }


