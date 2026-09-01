
#ifndef  __qdcLyraPublic_h__
#define  __qdcLyraPublic_h__  // {

//
#include	"qmOpenCommon.h"

//
__declspec(dllexport)int  qdcInit_lyra(  QDC_MGR  *  p  );
__declspec(dllexport)int  qdcExit_lyra(  QDC_MGR  *  p  );

 //
__declspec(dllexport) int  qdcInitCompressAudio_lyra(  void  *  pAudioCompressorCfg_reserved,  QY_AUDIO_HEADER  *  pAh_decompress,  QY_AUDIO_HEADER  *  pAh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  );
__declspec(dllexport) int  qdcExitCompressAudio_lyra(  QDC_OBJ_INFO  *  pQdcObjInfo  );
__declspec(dllexport) int  qdcCompressAudio_lyra(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_decompress,  BYTE  *  pInput,  unsigned  int  uiInputSize,  int  iSampleTimeInMs  );
__declspec(dllexport) int  qdcCompressAudioRun_lyra(  QDC_OBJ_INFO  *  pQdcObjInfo  );
__declspec(dllexport) int  qdcGetOutputByIndex_lyra(  QDC_OBJ_INFO  *  pQdcObjInfo,  int  index,  BYTE *  pbOutData,  unsigned  int  *  puiDataSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  pui_rtTimeLen  );
__declspec(dllexport) int  qdcClearOutputs_lyra(  QDC_OBJ_INFO  *  pQdcObjInfo  );

//
__declspec(dllexport)  int  qdcInitDecompressAudio_lyra(  void  *  pAudioCompressorCfg,  QY_AUDIO_HEADER  *  pAh_compress,  QY_AUDIO_HEADER  *  pAh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  );
__declspec(dllexport)  int  qdcExitDecompressAudio_lyra(  QDC_OBJ_INFO  *  pQdcObjInfo  );
__declspec(dllexport)  int  qdcDecompressAudio_lyra(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_compress,  BYTE  *  pInput,  unsigned  int  uiInputLen,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  );
__declspec(dllexport)  int  qdcDecompressAudioRun_lyra(  QDC_OBJ_INFO  *  pQdcObjInfo  );



#endif  //  }


