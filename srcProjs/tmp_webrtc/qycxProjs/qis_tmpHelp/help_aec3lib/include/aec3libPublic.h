
#ifndef  __aec3libPublic_h__
#define  __aec3libPublic_h__  //  {


int aec3lib_doTest();

//
int aec3lib_doTest888();
//



//
int initAec3Obj(int sampleRate, void** ppObj);
int exitAec3Obj(void** ppObj);
int aec3Obj_doAec(void* pObjParam,
                  char* render_data,
                  unsigned int render_dataLen,
                  char* mic_data,
                  unsigned int mic_dataLen);



#endif  //  }



