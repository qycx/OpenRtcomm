
#ifndef  __audioProcPublic_h__
#define  __audioProcPublic_h__  //  {

//
typedef int (*PF_inStream4)(void* p0, void* p1, void* p2,void *p3);     //play

//
typedef int (*PF_outStream)(void* p0, void* p1, void* p2);



//
extern "C" __declspec(dllexport) int aec_doTest();

extern "C" __declspec(dllexport) int initAecObj(int sampleRate, void** ppObj);
extern "C" __declspec(dllexport) int exitAecObj(void** ppObj);
extern "C" __declspec(dllexport) int aecObj_doAec(void* pObjParam,
                  char* render_data,
                  unsigned int render_dataLen,
                  char* mic_data,
                  unsigned int mic_dataLen);


extern "C" __declspec(dllexport) int initAudioMixerObj(int sampleRate, int nSources,
                                                        PF_inStream4 pf, void *  p0,
                                                       void** ppObj);

extern "C" __declspec(dllexport) int exitAudioMixerObj(void** ppObj);
extern "C" __declspec(dllexport) int audioMixerObj_doMix(void* pObjParam,
                                                         char* dataBuf,
                                                         unsigned int* puiSize);




#endif  //  }



