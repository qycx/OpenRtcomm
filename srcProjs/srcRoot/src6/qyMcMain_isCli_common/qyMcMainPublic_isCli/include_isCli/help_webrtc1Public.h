
#ifndef  __help_aecPublic_h__
#define  __help_aecPublic_h__	//  {

//
#include	"qisWebRtcPublic.h"

//
int dyn_initAecObj(int sampleRate, void** ppObj);
int dyn_exitAecObj(void** ppObj);
int dyn_aecObj_doAec(void* pObjParam, char* render_data, unsigned int render_dataLen, char* mic_data, unsigned int mic_dataLen);

//
int dyn_initAudioMixerObj(int sampleRate, int nSources, PF_inStream4 pf, void* p0, void** ppObj);
int dyn_exitAudioMixerObj(void** ppObj);
int dyn_audioMixerObj_doMix(void* pObjParam, char* dataBuf, unsigned int* puiSize);


int dyn_help_webrtc_init(int iCntLimit_activeMems_from,
    PF_inStream4 pf_is,
    void* is_p0,
    PF_outStream pf_os,
    void* os_p0,
    void** ppObj);


void dyn_help_webrtc_exit(void** ppObj);




#endif //  }


