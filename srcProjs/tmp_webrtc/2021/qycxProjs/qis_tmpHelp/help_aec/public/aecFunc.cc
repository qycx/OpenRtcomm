


#include    "qycxProjs/qis_tmpHelp/help_aec3Lib/include/aec3libPublic.h"

////////////////////////








__declspec(dllexport) int aec_doTest() {
  int ii = 0;
  ii++;

  //
  aec3lib_doTest();
 
  aec3lib_doTest888();


  

  return 567;
}




extern "C" __declspec(dllexport)  int initAecObj(int sampleRate, void** ppObj) {
  return initAec3Obj(sampleRate, ppObj);
}


extern "C" __declspec(dllexport) int exitAecObj(void** ppObj) {
  return exitAec3Obj(ppObj);
}

extern "C" __declspec(dllexport) int aecObj_doAec(void* pObj,
    char* render_data,
    unsigned int render_dataLen,
    char* mic_data,
    unsigned int mic_dataLen) {

    return aec3Obj_doAec(pObj, render_data, render_dataLen, mic_data, mic_dataLen);

}





