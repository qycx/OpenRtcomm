



#ifndef  __QYCOMMPROC_OPEN_H__
#define  __QYCOMMPROC_OPEN_H__	//  {

//
#include	<mmreg.h>
#include	<mmeapi.h>


//
#define		isCapTypeScreen(  uiCapType  )							(  uiCapType  ==  2  )		//  2014/12/02
//
#define		isCapTypeMediaFile(  uiCapType  )						(  uiCapType  ==  3  )		//  2012/11/04
#define		isCapTypeMediaDevice(  uiCapType  )						(  uiCapType  ==  4  )
//  2014/12/02
#define		isCapTypeMosaic(  uiCapType  )							(  uiCapType  ==  20  )		//  2014/12/02

//  2012/06/12
#define		isSubCapType_webcam(  uiSubCapType  )					(  uiSubCapType  ==  1  )



//  2014/06/21
#define		CONST_fourcc_YUY2			MAKEFOURCC(  'Y',  'U',  'Y',  '2'  )		//  2010/05/31
#define		CONST_fourcc_YV12			MAKEFOURCC(  'Y',  'V',  '1',  '2'  )		//  2010/07/11
#define		CONST_fourcc_I420			MAKEFOURCC(  'I',  '4',  '2',  '0'  )		//  2010/07/11
#define		CONST_fourcc_HDYC			MAKEFOURCC(  'H',  'D',  'Y',  'C'  )		//  2012/01/03

//
#define		CONST_fourcc_NV21			MAKEFOURCC('N', 'V', '2', '1')
#define		CONST_fourcc_NV12			MAKEFOURCC('N', 'V', '1', '2')



//
#define		CONST_fourcc_v210			MAKEFOURCC(  'v',  '2',  '1',  '0'  )		//  2012/02/23

//  
#define		CONST_fourcc_h264			MAKEFOURCC(  'h',  '2',  '6',  '4'  )		//  2014/02/24
//
#define		CONST_fourcc_AVC			MAKEFOURCC('A','V','C',' ')					//  2017/10/08
#define		CONST_fourcc_HEVC			MAKEFOURCC('H','E','V','C')					//  2017/10/08

//
#define		CONST_fourcc_AV01			MAKEFOURCC('A','V','0','1')					//

//
//  #define		CONST_fourcc_MP2T	MAKEFOURCC(  'M',  'P',  '2',  'T'	)			//  2014/03/05

//
//  #define		CONST_fourcc_vp8		0x00385056									//  2014/07/19
#define		CONST_fourcc_vp80			0x30385056									//  2014/08/06
#define		CONST_fourcc_vp8_bad		0x00385056									//  2014/07/19

//
#define		CONST_fourcc_MJPG			MAKEFOURCC('M', 'J', 'P', 'G')


//
#if  0
	#define  WAVE_FORMAT_LEAD_VORBIS                0x564C /* LEAD Technologies */
	//
	#define  WAVE_FORMAT_OGG_VORBIS_MODE_1          0x674F /* Ogg Vorbis */
	#define  WAVE_FORMAT_OGG_VORBIS_MODE_2          0x6750 /* Ogg Vorbis */
	#define  WAVE_FORMAT_OGG_VORBIS_MODE_3          0x6751 /* Ogg Vorbis */
	#define  WAVE_FORMAT_OGG_VORBIS_MODE_1_PLUS     0x676F /* Ogg Vorbis */
	#define  WAVE_FORMAT_OGG_VORBIS_MODE_2_PLUS     0x6770 /* Ogg Vorbis */
	#define  WAVE_FORMAT_OGG_VORBIS_MODE_3_PLUS     0x6771 /* Ogg Vorbis */
#endif
//  2016/12/05
#define		CONST_fourcc_vorbis						0x564C


		//

		// 在实际应用中（如封装 MELP 数据到 WAV 容器或通过 Windows API 处理时），通常会使用 自定义的 wFormatTag 值，即超出标准预定义范围的数值（例如 0x0100 以上，避免与标准标签冲突）。
		//
//public final static int WAVE_FORMAT_MELP						=	0x0100 + 1;		//  makeFOURCC('M','E',‘L’，‘P')     //  这个可能不是标准定义
#define		myWAVE_FORMAT_unknown									0x0100 + 2;					//										//  这个可能不是标准定义


//
#define		CONST_iTargetUsage_null									0
#define		CONST_iTargetUsage_bestQuality							10									
#define		CONST_iTargetUsage_balanced								20
#define		CONST_iTargetUsage_bestSpeed							30

//
#define		DEFAULT_iTargetUsage									CONST_iTargetUsage_balanced

//  2014/03/29
//
#define		CONST_hdAccl_auto										0												//  2014/03/29
#define		CONST_hdAccl_msdk_software								1
#define		CONST_hdAccl_msdk_hardware								2
#define		CONST_hdAccl_nv											3												//  2014/06/25
#define		CONST_hdAccl_amf										4												//  2015/04/30
//
#define		DEFAULT_hdAccl											CONST_hdAccl_auto			

//
typedef  int  (  *PF_transformGetSpsPps  )(  unsigned  int  uiTransformType,  void  *  pQY_TRANSFORM,  int  index_pMems_from,  char  *  pBuf,  unsigned  int  *  puiSize  );

//  
typedef  int  (  *PF_parseVPkt_i  )(  unsigned  int  uiTransformType,  void  *  pParent_transform,  void  *  pPkt_myDRAW_VIDEO_DATA,  long  *  p_old_lPktId_alloc,  unsigned  char  **  ppInput,  unsigned  int  *puiSize  );


//
typedef  int  (  *PF_parseDecAPkt_o  )(  void  *  pPktParam,  void  **  ppWfx,  unsigned  char  **  ppOutput,  unsigned  int  *puiSize  );
typedef  int  (  *PF_parseDecVPkt_o  )(  void  *  pPktParam,  void  **  ppBih,  unsigned  char  **  ppOutput,  unsigned  int  *puiSize  );

//
typedef  void  (  *PF_clean_myPLAY_AUDIO_DATA  )(  void  *  pmyPLAY_AUDIO_DATA,  LPCTSTR  hint  );
typedef  void  (  *PF_clean_myDRAW_VIDEO_DATA  )(  void  *  pmyDRAW_VIDEO_DATA,  LPCTSTR  hint  );


typedef  int  (  *PF_detachPkt  )(  void  *  pPkt_myDRAW_VIDEO_DATA,  void  *  p1  );

typedef  int  (  *PF_updateDecVideoParam  )(  BITMAPINFOHEADER  *  pBih,  double  dFrameRate,  void  *  pParent_transform,  unsigned  int  uiTransformType  );

//
typedef  int  (  *PF_doPostEnc  )(  void  *  pQDC_OBJ_INFO,  char  *  pInput,  unsigned  int  inputSize,  int  iSampleTimeInMs,  unsigned  int  uiPts,  void  *  pBuf_pkt  );


//  2015/10/29
typedef  int  (  *old_PF_myLoadNextFrame  )(  unsigned  short  usPktResType,  void  *  p0_pInput,  void  *  p1_uiInputSize,  void  *  p2_myLoadNextFrame  );		

//
//typedef  int  (*PF_myLoadNextFrame)(unsigned  short  usPktResType, int  iFourcc,  void* p0_pInput, void* p1_uiInputSize, void* p2_myLoadNextFrame);
typedef  int  (*PF_myLoadNextFrame)(unsigned  short  usPktResType, int  iFourcc, void* p0_pInput, void* p1_uiInputSize, unsigned  int uiSampleTimeInMs,  void* p2_myLoadNextFrame);


//
typedef  int  (  *PF_smplPCMReader_LoadNextFrame  )(  void  *  pQdcObjInfoParam,  long  *  pold_lPktId,  old_PF_myLoadNextFrame  pf_myLoadNextFrame,  void  *  p2_myLoadNextFrame,  BOOL  *  pbNeed_forceKeyFrame  );

//  2014/07/08
//typedef  int  (  *PF_smplYUVReader_LoadNextFrame  )(  void  *  pQdcObjInfoParam,  long  *  pold_lPktId,  old_PF_myLoadNextFrame  pf_myLoadNextFrame,  void  *  p2_myLoadNextFrame,  BOOL  *  pbNeed_forceKeyFrame  );
typedef  int  (  *PF_smplYUVReader_LoadNextFrame  )(  void  *  pQdcObjInfoParam,  long  *  pold_lPktId,  PF_myLoadNextFrame  pf_myLoadNextFrame,  void  *  p2_myLoadNextFrame,  BOOL  *  pbNeed_forceKeyFrame  );

//
typedef  int  (  *PF_smplBitstreamReader_ReadNextFrame_func  )(  void  *  pQdcObjInfoParam,  long  *  pold_lPktId,  unsigned  int  uiToInMs,  char  *  pBsBuf,  unsigned  int  *  puiBsBufSize,  unsigned  int  *  puiSampleTimeInMs  );


//
typedef  int  (  *PF_data_to_pcm  )(  void  *  pQdcObjInfoParam,  void  *  pData,  void  *  pYUVWriter_var  );


//
typedef  int  (  *PF_img_to_yuv  )(  void  *  pQdcObjInfoParam,  void  *  pImg,  unsigned  int  cropW,  unsigned  int  cropH,  unsigned  int  pitch,  unsigned  int  w,  unsigned  int  h,  void  *  pYUVWriter_var  );


//
typedef  int (  *PF_smplPCMWriter_WriteNextFrame  )(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  int  iFourcc,  void  *  pYUVWriter_var,  void *pImg,  PF_data_to_pcm  pf_data_to_pcm,  double  dFrameRate,  LPCTSTR  hint  );

//
typedef  int (  *PF_smplYUVWriter_WriteNextFrame  )(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  int  iFourcc,  void  *  pYUVWriter_var,  void *pImg,  unsigned  int  cropW,  unsigned  int  cropH,  unsigned  int  pitch,  PF_img_to_yuv  pf_img_to_yuv,  double  dFrameRate,  LPCTSTR  hint  );



//
#define		CONST_uiTransformType_null					0
#define		CONST_uiTransformType_encVideo				1
//  
#define		CONST_uiTransformType_dec					2
//
#define		CONST_uiTransformType_encAudio				3
//



//  2014/05/20
//
typedef  struct  __audioCompressorCfgCommon_t						{
				 unsigned  char										ucCompressors;								//  acm or dmo
				 
				 //
				 short											    wFormatTag;        /* format type */
				 int												sample_fmt;
				 
				 //  2014/05/20
				 int												iAvgBitrateInKbps;

				 /////////////////////
				 //  2016/12/09
				 //  2014/03/25
 				 void										*		pCurPkt;
				 int												size_pCurPkt;
				 void										*		pInDataCacheQ;
				 void										*		pAudioQ2;
				 //
				 void										*		unused_pTmpDataQ;
				 //
				 unsigned  int										uiTransformType_pParent;
				 void										*		pParent_transform;
				 //
				 PF_bCommonHandler									pf_bTransformAudioQuit;		//  bTransformQuit(  void  *  pTransform,  0,  0  )
				 //
				 
				 
				 
				 //
				 //  PF_transformGetSpsPps								pf_transformGetSpsPps;		// 

				 //PF_commonHandler									pf_transformGetAh;			//  (  void  *  pQY_TRANSFORM, QY_AUDIO_HEADER * pAh, void *  p2  )
				 PF_commonHandler									pf_transformGetWfx;			//  (  void  *  pQY_TRANSFORM, WAVEFORMATEX * pWfx, void *  p2  )
				 //

				 //
				 PF_commonHandler									pf_getNextAPkt;				//   int  getNextVPkt(  myDRAW_VIDEO_DATA  *  pCurPkt,  GENERIC_Q  *	pInDataCacheQ,  QY_Q2  *	pVideoQ2  )

				 //
				 PF_parseDecAPkt_o									pf_parseDecAPkt_o;

				 //
				 PF_detachPkt										pf_detachPkt;				//  pPkt,  0

				 PF_clean_myPLAY_AUDIO_DATA							pf_clean_myPLAY_AUDIO_DATA;
				 //				 
				 int												iDecParam_index_pMems_from;							//  2014/09/07
				 //
				 //
				 struct												{
					 //
					 PF_smplBitstreamReader_ReadNextFrame_func		pf_smplBitstreamReader_ReadNextFrame_func;	//  2014/07/9
					 //
					 //  2015/01/17
					 PF_commonHandler								pf_smplPCMWriter_WriteNextFrame_pre;		//  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  void  *  pYUVWriter_var					 
					 PF_smplPCMWriter_WriteNextFrame				pf_smplPCMWriter_WriteNextFrame0;
					 PF_commonHandler								pf_smplPCMWriter_WriteNextFrame1;			//  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  void  *  pYUVWriter_var

					 //
					 PF_smplPCMWriter_WriteNextFrame				pf_smplPCMWriter_WriteNextFrame_all;
					 //
					 PF_commonHandler								pf_postAPktToRender;						//  void  *  pQY_TRANSFORM,  void  *  pmyPLAY_PLAY_DATA,  BOOL  *  unused_pbPktRedirected  
				 }													dec;

				 //
				 struct												{
					 //
					 PF_smplPCMReader_LoadNextFrame					pf_smplPCMReader_LoadNextFrame;				//  2014/07/09
					 //
					 PF_doPostEnc									pf_doPostEnc;								//  void  *  pParent,  void  *  pInput,  uiSize  )
				 }													enc;
		
				 /////////////////



}		 AUDIO_COMPRESSOR_cfgCommon;





//  2014/11/13
typedef  struct  __videoInputInfo_t								{
				 time_t											tStartTran;													//  2011/08/30
				 unsigned  short								usFramesThisSecond;			
				 
				 //  2011/08/30
				 unsigned  short								usFps;														//  2011/08/30				

				 //
				 TCHAR											tBuf[32];													//  2014/11/26
				 //
}		 VIDEO_input_info;


//  2014/12/02
//
typedef  struct  __videoCompressorCfgCommon_t						{
				 unsigned  char										ucCompressors;								//  vcm or dmo
				 
				 char												fourccStr[4  +  1];
				 //
				 unsigned  char										ucSeconds_perFrame;							//  2011/08/08
				 //
				 unsigned  short									usMaxFps_toShareBmp;						//  2008/12/06
				 unsigned  short									usMinFps_toShareBmp;						//  2009/12/09
				 
				 //  2014/04/20. 
				 int												iWidth_pic;									//  2011/08/07
				 int												iHeight_pic;								//  2011/08/07

				 //
				 int												profile_idc;								//  2011/07/30\

				 //
				 unsigned  int										uiCapType;									//  2012/02/08.
				 unsigned  int										uiSubCapType;								//  2012/06/12
				 int												iCapUsage;									//  2014/12/02

				 //
				 int												iTargetUsage;								//  2012/02/08

				 //  2012/06/27
				 int												iAvgBitrate;
				 int												iPeekBitrate;

				 //  2014/03/29
				 unsigned  char										ucHardwareAccl;

				 //  2014/03/25
 				 void										*		pCurPkt;
				 int												size_pCurPkt;
				 void										*		pInDataCacheQ;
				 void										*		pVideoQ2;
				 void										*		pTmpDataQ;
				 //
				 unsigned  int										uiTransformType_pParent;
				 void										*		pParent_transform;
				 //
				 PF_bCommonHandler									pf_bTransformVideoQuit;		//  bTransformQuit(  void  *  pTransform,  0,  0  )
				 //
				 PF_transformGetSpsPps								pf_transformGetSpsPps;		//  
				 PF_commonHandler									pf_transformGetBih;			//  (  void  *  pQY_TRANSFORM, bitmapinfoheader * pBih, void *  p2  )
				 //
				 PF_commonHandler									pf_getNextVPkt;				//   int  getNextVPkt(  myDRAW_VIDEO_DATA  *  pCurPkt,  GENERIC_Q  *	pInDataCacheQ,  QY_Q2  *	pVideoQ2  )
				 //
				 PF_parseDecVPkt_o									pf_parseDecVPkt_o;
				 PF_detachPkt										pf_detachPkt;				//  pPkt,  0
				 PF_clean_myDRAW_VIDEO_DATA							pf_clean_myDRAW_VIDEO_DATA;
				 //				 
				 int												iDecParam_index_pMems_from;							//  2014/09/07
				 //
				 struct												{
					 //
					 PF_smplBitstreamReader_ReadNextFrame_func		pf_smplBitstreamReader_ReadNextFrame_func;	//  2014/07/9
					 //
					 //  2015/01/17			
					 PF_commonHandler								pf_smplYUVWriter_WriteNextFrame_pre;		//  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  void  *  pYUVWriter_var
					 PF_smplYUVWriter_WriteNextFrame				pf_smplYUVWriter_WriteNextFrame0;				 
					 PF_commonHandler								pf_smplYUVWriter_WriteNextFrame1;			//  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  void  *  pYUVWriter_var
					 //
					 PF_smplYUVWriter_WriteNextFrame				pf_smplYUVWriter_WriteNextFrame_all;
					 
					 //
					 PF_updateDecVideoParam							pf_updateDecVideoParam;						//  pBih,  pTransform,  transformType
					 PF_commonHandler								pf_postVPktToRender;						//  void  *  pQY_TRANSFORM,  void  *  pmyDRAW_VIDEO_DATA,  BOOL  *  pbPktRedirected  
				 }													dec;
				 //
				 struct												{
					 //
					 unsigned  char									ucbResizable;								//  2014/04/20
					 int											iW_org;
					 int											iH_org;
					 //
					 PF_smplYUVReader_LoadNextFrame					pf_smplYUVReader_LoadNextFrame;				//  2014/07/09
					 //
					 PF_doPostEnc									pf_doPostEnc;								//  void  *  pParent,  void  *  pInput,  uiSize  )
				 }													enc;
				 
				 //
				 int												tmp_max_dec_fps;
				 VIDEO_input_info									inputInfo;
				 //  2015/10/04
				 unsigned  short									usPktResType_suggested;						//  2015/10/04. 


				 //
}		 VIDEO_COMPRESSOR_cfgCommon;


//  for nv. 2024/10/19
#define		M_VideoCompressorCfgCommonEx							VIDEO_COMPRESSOR_cfgCommon		common;					\
																	int								adapterLuid_LowPart;	\
																	int								adapterLuid_HighPart;


//  for nv. 2024/10/19
typedef  struct {
				M_VideoCompressorCfgCommonEx
}		VIDEO_COMPRESSOR_cfgCommonEx;



//
#define		CONST_bufSize_bPrivateData								1024  +  256
typedef  struct	 __qyVideoHeader_t									{						//  2009/03/29
				 BITMAPINFOHEADER									bih;
				 char												bPrivateData[CONST_bufSize_bPrivateData];
}		 QY_VIDEO_HEADER;


#define		CONST_bufSize_bExtraData								512
typedef  struct  __qyAudioHeader_t									{						//  2009/05/16
				 WAVEFORMATEX										wfx;
				 char												bExtraData[CONST_bufSize_bExtraData];
}		 QY_AUDIO_HEADER;


//
//  2016/12/17. especially for vorbis.
//
#define		MAX_aHeaderLen											256
//
typedef  struct  __ah_stream_t										{
				 //
				 struct												{
					 unsigned  short								usLen;
				 }													mems[3];
				 //
				 char												buf[6  *  1024];

}		 AH_stream;


//
//  2014/02/25
#define		MAX_spsPpsLen											256
//
typedef  struct  __vh_stream										{
				 DWORD												dwFourcc;
				 //
				 unsigned  short									usCnt;
				 struct												{
					 unsigned  short								usLen;
					 char											spsPps[MAX_spsPpsLen  +  1];
				 }													mems[6];
				 
}		 VH_stream;



//
//  2015/09/30
#define		CONST_pktResType_null									0							//  2015/09/30
#define		CONST_pktResType_memory									1							//  2015/09/30
#define		CONST_pktResType_sharedTex								2							//  2015/09/30



//
//  2014/07/17
#define		CONST_debugStepType_null		0
#define		CONST_debugStepType_dec			1

//  2015/01/11
#define		M_debugStep_common										int		nStep_debug;	DWORD	dwTickCnt_step_debug;						//  2012/03/21

//  2015/01/11
typedef  struct  __debugStepCommon_t								{
				 M_debugStep_common
}		 DEBUG_step_common;

//
typedef  struct  __debugStep_dec_t									{
				 M_debugStep_common
				 //
				 int												sts_run;
				 BOOL												bException;
				 
				 //  2015/01/15
				 BOOL												bCalled_pipeline_Init;
				 int												sts_pipeline_Init;
				 BOOL												bCalled_RunDecoding;

				 //
				 int												sts_ReadNextFrame;

				 //
				 int												sts_SyncOutputSurface370;
				 //
				 int												sts_SyncOutputSurface396;
				 //
				 int												sts_m_pDeliveredEvent_TimedWait;
				 //
				 int												sts_DecodeFrameAsync;
				 //
				 int												sts_SyncOutputSurface452;
				 //
				 int												sts_SyncOutputSurface482;
				 //
				 int												sts_SyncOperation324;
				 int												sts_DeliverOutput347;
				 BOOL												bHere_375_SyncOutputSurface;
				 
				 //
				 BOOL												bHere_PrintPerFrameStat;
				 
				 //
				 int												nTimeInMs_smplYUVWriter_WriteNextFrame0;
				 int												nTimeInMs_smplYUVWriter_WriteNextFrame1;
				 			 


}		 DEBUG_step_dec;





//
int  parseSpsPps(  int  iFourcc,  char  *  spsPps,  int  spsPpsLen,  char  *  spsBuf,  unsigned  int  *  puiSpsSize,  char  *  ppsBuf,  unsigned  int  *  puiPpsSize,  char  *  vps,  unsigned  int  *  puiVpsSize  );
int  parseSpsPps1(  int  iFourcc,  char  *  spsPps,  int  spsPpsLen,  VH_stream  *  pVh_stream  );
//
int  makeSpsPps(  VH_stream  *  pVh_stream,  char  *  spsPpsParam,  unsigned  int  *  puiSize  );

//
void  mySaveBitmap(  BITMAPINFOHEADER  *  pBih,  void  *  rgb,  BOOL  bFlipImg,  LPCTSTR  szFilename  );
void  mySaveYv12(  int  w,  int  h,  void  *  yv12,  BOOL  bFlipImg, LPCTSTR  szFilename  );
void  mySaveI420(int  w, int  h, void* yv12, BOOL  bFlipImg, LPCTSTR  szFilename);
void  mySaveNv12(int  w, int  h, void* nv12, BOOL  bFlipImg, LPCTSTR  szFilename);


//
extern  "C"  int  waitForObject(HANDLE * ph, DWORD  dwMilliseconds);



#endif  //  }


