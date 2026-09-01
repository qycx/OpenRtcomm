
#ifndef  __tmpAACPublic_h__
#define  __tmpAAcPublic_h__  

//#include "qyCommProc_open.h"

int  qdcInit_aac(QDC_MGR* p);
int  qdcExit_aac(QDC_MGR* p);

int  qdcInitDecompressAudio_aac(void* pAudioCompressorCfg, QY_AUDIO_HEADER* pAh_compress, QY_AUDIO_HEADER* pAh_decompress, QDC_OBJ_INFO* pQdcObjInfo);
int  qdcExitDecompressAudio_aac(QDC_OBJ_INFO* pQdcObjInfo);
int  qdcDecompressAudio_aac(QDC_OBJ_INFO* pQdcObjInfo, QY_AUDIO_HEADER* pAh_compress, BYTE* pInput, unsigned  int  uiInputLen, int  iSampleTimeInMs, unsigned  int  ui_rtTimeLen);
int  qdcDecompressAudioRun_aac(QDC_OBJ_INFO* pQdcObjInfo);
int  qdcGetOutputByIndex_aac(QDC_OBJ_INFO* pQdcObjInfo, int  index, BYTE* pbOutData, unsigned  int* puiDataSize, unsigned  int* puiSampleTimeInMs, unsigned  int* pui_rtTimeLen);
int  qdcClearOutputs_aac(QDC_OBJ_INFO* pQdcObjInfo);


#endif