
#ifndef  __tmpFfmpegPublic_h__
#define  __tmpFfmpegPublic_h__  // {

 int  qdcInit_ffmpeg(  QDC_MGR  *  p  );
 int  qdcExit_ffmpeg(  QDC_MGR  *  p  );

 //
int  qdcInitCompressAudio_ffmpeg(  void  *  pAudioCompressorCfg_reserved,  QY_AUDIO_HEADER  *  pAh_decompress,  QY_AUDIO_HEADER  *  pAh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  );
int  qdcExitCompressAudio_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo  );
int  qdcCompressAudio_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_decompress,  BYTE  *  pInput,  unsigned  int  uiInputSize,  int  iSampleTimeInMs  );
int  qdcCompressAudioRun_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo  );
int  qdcGetOutputByIndex_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo,  int  index,  BYTE *  pbOutData,  unsigned  int  *  puiDataSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  pui_rtTimeLen  );
int  qdcClearOutputs_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo  );

//
int  qdcInitDecompressAudio_ffmpeg(  void  *  pAudioCompressorCfg,  QY_AUDIO_HEADER  *  pAh_compress,  QY_AUDIO_HEADER  *  pAh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  );
int  qdcExitDecompressAudio_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo  );
int  qdcDecompressAudio_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_compress,  BYTE  *  pInput,  unsigned  int  uiInputLen,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  );
int  qdcDecompressAudioRun_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo  );

 int qdcInitCompressVideo_ffmpeg(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_decompress,  QY_VIDEO_HEADER  *  pVh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  );

  int qdcExitCompressVideo_ffmpeg( QOI_common *pQdcObjInfo);
  int qdcGetSpsPps_ffmpeg( QOI_common *pQdcObjInfo, char * spsBuf, uint *puiSpsSize, char * ppsBuf,  uint *puiPpsSize, char * vps, uint * puiVpsSize);
  int qdcCompressVideo_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs  );

//
int  qdcInitDecompressVideo_ffmpeg(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_compress,  QY_VIDEO_HEADER  *  pVh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  );
int  qdcExitDecompressVideo_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo  );
int  qdcDecompressVideo_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs  );
int  qdcDecompressVideoAndOutput_ffmpeg(QDC_OBJ_INFO* pQdcObjInfo, BITMAPINFO* pBmpInfo_input, BYTE* pInput, BITMAPINFO* pBmpInfo_output, BYTE* pOutput);






//
int  initResample(  	__int64  src_ch_layout, int src_rate, int src_sample_fmt, int src_nb_samples,  __int64  dst_ch_layout,  int  dst_rate,  int  dst_sample_fmt,  void  **  ppCtx_resample  );
int  exitResample(  void  *  pCtx_resample  );
int  doResample(  void  *  pCtx_resample,  char  *  pInput,  int  inputLen,  char  *  pOutput,  int  *  pOutputSize  );




#endif  //  }


