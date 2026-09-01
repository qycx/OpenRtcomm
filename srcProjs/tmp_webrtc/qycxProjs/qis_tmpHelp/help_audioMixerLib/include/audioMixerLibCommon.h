
#ifndef  __audioMixerLibCommon_h__
#define  __audioMixerLibCommon_h__	//  {

//
#include	"audioMixerLibPublic.h"


//
typedef struct __audioMixerObj_t {

				void* pTMP_mixer_obj;

				    PF_inStream4 pf_in;                                
					void* p0_in;

					PF_outStream pf_out;
                    void* p0_out;


} AudioMixer_obj;





#endif  //  }


