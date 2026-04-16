
#ifndef  __audioProc_public_h__
#define  __audioProc_public_h__	//  {

//
//
 extern  "C"  __declspec(dllexport  )  int  tmp_removeOldAudio(  QY_Q2  *  pPlayAudioQ2,  DWORD  dwTickCnt_now,  QY_PLAYER  *  pPlayer  );

 //
 extern "C" __declspec(  dllexport  )  int start_playAudio_webRtc( QY_PLAYER  *  pPlayer );
 extern "C" __declspec(  dllexport  )  int stop_playAudio_webRtc( QY_PLAYER  *  pPlayer );

 //
 extern  "C"  __declspec(  dllexport  )  int  start_recordAudio_webRtc(  CAP_procInfo_recordSound  *  pRecordSoundProcInfo  );
 extern  "C"  __declspec(  dllexport  )  int  stop_recordAudio_webRtc(  CAP_procInfo_recordSound  *  pRecordSoundProcInfo  );



#endif  //  }


