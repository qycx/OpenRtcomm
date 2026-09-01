
#ifndef  __audioMixerLibPublic_h__
#define  __audioMixerLibPublic_h__  //  {

//
#include    "qycxProjs/qis_tmpHelp/help_audioProc/include/audioProcPublic.h"

//
int initAudioMixerLibObj(int sampleRate,
                         int nSources,
                         PF_inStream4 pf,
                         void* p0,
                         void** ppObj);

  int exitAudioMixerLibObj(void** ppObj);
  //
  int audioMixerLibObj_doMix(void* pObjParam,
                             char* dataBuf,
                             unsigned int* puiSize);





#endif  //  }


