#ifndef  __SQ_WIN32_AEC_H__
#define  __SQ_WIN32_AEC_H__

#ifdef  __cplusplus
extern  "C"  {
#endif

	DWORD  WINAPI  msAecRecThreadFunc(  LPVOID ignored  );

	//  2017/01/28
	DWORD  WINAPI  coreAudioRecThreadFunc(  LPVOID ignored  );



#ifdef  __cplusplus
};
#endif


#endif