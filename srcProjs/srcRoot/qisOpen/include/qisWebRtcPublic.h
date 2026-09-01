
#ifndef  __qisWebRtcPublic_h__
#define  __qisWebRtcPublic_h__  //  {

//
typedef  int  (*PF_inStream)(void* p0, void* p1, void* p2);
typedef int (*PF_inStream4)(void* p0, void* p1, void* p2, void* p3);     //play
//
typedef  int  (*PF_outStream)(void* p0, void* p1, void* p2);




//
int  init_webRtc(  );
int  exit_webRtc(  );


//
int  startRecord_webRtc(unsigned short usCntLimit_activeMems_from);
int  stopRecord_webRtc(  );

//
int  startPlayAudio_webRtc(  void  *  pPlayer  );
int  stopPlayAudio_webRtc(  void  *  pPlayer  );


//
extern  "C"  __declspec(  dllexport  )  char  *  voe_ver(  );

//
extern  "C"  __declspec(  dllexport  )  int  voe_init(  );
extern  "C"  __declspec(  dllexport  )  int  voe_exit(  );


//
extern  "C"  __declspec(  dllexport  )  int  voe_record_init(  void  *  pRecordSoundProcInfo,  PF_outStream  pf  );
extern  "C"  __declspec(  dllexport  )  int  voe_record_setDevice(  void  *  pRecordSoundProcInfo,  int  index_record  );
extern  "C"  __declspec(  dllexport  )  int  voe_record_start(  void  *  pRecordSoundProcInfo  );
extern  "C"  __declspec(  dllexport  )  int  voe_record_exit(  );

extern  "C"  __declspec(  dllexport  )  int  voe_list_device(  char  *  recorder_buf,  int  size,  char  *  recorder_selected_utf8  );

extern  "C"  __declspec(dllexport)  int  voe_getADeviceIndex(  char  *  recorder_selected_utf8,  int  *  pIndex  );


//
//
//

//
extern  "C"  __declspec(  dllexport  )  int  voe_play_init(  void  *  pPlayer,  PF_inStream  pf,  void  **  ppVoePlay  );
//
extern  "C"  __declspec(  dllexport  )  int  voe_play_exit(  void  **  ppVoePlay  );




#endif  //  }


