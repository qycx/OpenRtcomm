
#ifndef  __aecPublic_h__
#define  __aecPublic_h__  //  {

__declspec(dllexport) int aec_doTest();

extern "C" __declspec(dllexport) int initAecObj(int sampleRate, void** ppObj);
extern "C" __declspec(dllexport) int exitAecObj(void** ppObj);
extern "C" __declspec(dllexport) int aecObj_doAec(void* pObjParam,
                  char* render_data,
                  unsigned int render_dataLen,
                  char* mic_data,
                  unsigned int mic_dataLen);



#endif  //  }



