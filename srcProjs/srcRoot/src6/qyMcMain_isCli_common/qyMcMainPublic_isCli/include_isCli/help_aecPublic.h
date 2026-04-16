
#ifndef  __help_aecPublic_h__
#define  __help_aecPublic_h__	//  {


int dyn_initAecObj(int sampleRate, void** ppObj);
int dyn_exitAecObj(void** ppObj);
int dyn_aecObj_doAec(void* pObjParam, char* render_data, unsigned int render_dataLen, char* mic_data, unsigned int mic_dataLen);





#endif //  }


