
#include "qycxProjs/qis_tmpHelp/help_audioMixerLib/include/audioMixerLibPublic.h"


//

extern "C" __declspec(dllexport) int initAudioMixerObj(int sampleRate,
                                           int nSources,
                                           PF_inStream4 pf,
                                           void* p0,
                                           void** ppObj)

{
  return initAudioMixerLibObj(sampleRate, nSources, pf,p0,ppObj);
}

extern "C" __declspec(dllexport) int exitAudioMixerObj(void** ppObj) {
  return exitAudioMixerLibObj(ppObj);
}

extern "C" __declspec(dllexport) int audioMixerObj_doMix(void* pObjParam,
    char* dataBuf,
    unsigned int* puiSize) 
{
  return audioMixerLibObj_doMix(pObjParam, dataBuf, puiSize);

}




