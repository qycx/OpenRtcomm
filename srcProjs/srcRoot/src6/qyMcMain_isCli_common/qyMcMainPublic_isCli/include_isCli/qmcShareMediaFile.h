

#ifndef  __QMCSHAREMEDIAFILE_H__
#define  __QMCSHAREMEDIAFILE_H__	//  {

#define		CONST_volume_full		0L
#define		CONST_volume_silence	-10000L



typedef  struct  __shareMediaFile_t			{
			
				 BOOL							bInited;
				 
				 TCHAR							tFile[MAX_PATH];

				 IGraphBuilder				*	m_pGB;

				 IMediaControl				*	m_pMC;
				 IMediaEventEx				*	m_pME;
				 IVideoWindow				*	m_pVW;
				 IBasicAudio				*	m_pBA;
				 IBasicVideo				*	m_pBV;
				 IMediaSeeking				*	m_pMS;
				 IMediaPosition				*	m_pMP;
				 IVideoFrameStep			*	m_pFS;

				 //
				 BOOL							g_bAudioOnly;
				 BOOL							g_bNoAudio;

				 //  2014/10/17
				 IBaseFilter				*	m_pFileSource;


				 SAMPLE_grabber_info			audio,  video;

				 //
				 FILTER_STATE					psCurrent;			//   = State_Stopped;






}		 SHARE_MEDIA_FILE;




#endif  //  }



