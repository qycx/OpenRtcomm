

#ifndef  __QMCACM_H__
#define	 __QMCACM_H__	//  {


 typedef  struct  __convertAudioCtx_t			{
				 BYTE					*		pSrcBuf;
				 DWORD							dwSrcBufSize;
				 unsigned  int					uiSrcLen;

				 BYTE					*		pPcmBuf;
				 DWORD							dwPcmBufSize;
				 unsigned  int					uiPcmLen;

				 BYTE					*		pDstBuf;
				 DWORD							dwDstBufSize;
				 unsigned  int					uiDstLen;


				 HACMDRIVER			had;
				 HACMSTREAM			hstr;
				 HACMSTREAM			hstr2;

}		 CONVERT_AUDIO_CTX;


 HACMDRIVERID  find_driver(  WORD  wformatTag,  WORD  nChannels,  DWORD  nSamplesPerSec,  WORD  wBitsPerSample  );

 WAVEFORMATEX  *  get_driver_format(  HACMDRIVERID  hadid,  WORD  wFormatTag,  WORD  nChannels,  DWORD  nSamplesPerSec,  WORD  wBitsPerSample  );
 WAVEFORMATEX  *  get_driver_suggestedFormat(  HACMDRIVERID  hadid,  WAVEFORMATEX  *  pWfSrc,  WORD  wFormatTag,  WORD  nChannels,  DWORD  nSamplesPerSec,  WORD  wBitsPerSample  );



 //  int convertAudio(  HACMDRIVERID  hadid,  WAVEFORMATEX  *  pWfSrc,  BYTE  *  pSrcData,  DWORD  dwSrcBytes,  WAVEFORMATEX  *  pWfPcm,  BYTE  *  pPcmBuf,  DWORD  dwPcmBufSize,  WAVEFORMATEX  *  pWfDrv,  BYTE  *  pDstData,  DWORD  *  pdwDstBytes  );
 int convertAudio(  HACMSTREAM  hstr1,  HACMSTREAM  hstr2,  WAVEFORMATEX  *  pWfSrc,  BYTE  *  pSrcData,  DWORD  dwSrcBytes,  WAVEFORMATEX  *  pWfPcm,  BYTE  *  pPcmBuf,  DWORD  dwPcmBufSize,  WAVEFORMATEX  *  pWfDrv,  BYTE  *  pDstData,  DWORD  *  pdwDstBytes  );


#endif	//  }


