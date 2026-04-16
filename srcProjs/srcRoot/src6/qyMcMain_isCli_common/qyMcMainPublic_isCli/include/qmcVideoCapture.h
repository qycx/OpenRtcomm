
#ifndef  __qmcVideoCapture_h__
#define  __qmcVideoCapture_h__	//  {

//
#include	"ctxQmc.h"
#include	"videoInputInfo1.h"


//


//
#define		CONST_videoCompressors_null								0
#define		CONST_videoCompressors_vcm								1	//  "vcm"
#define		CONST_videoCompressors_dmo								2	//  "dmo"
#define		CONST_audioCompressors_acm								3	//  "acm"					//  2009/05/16
#define		CONST_audioCompressors_dmo								4	//  "dmo"					//  2009/05/16
#define		CONST_videoCompressors_custom							5	//  "custom"				//  2010/04/28
#define		CONST_audioCompressors_custom							6	//  "custom"				//  2010/04/28
//
#define		CONST_audioCompressors_ipp								7	//
#define		CONST_videoCompressors_ipp								8	//	"h264"					//  2011/07/30
//
#define		CONST_audioCompressors_hwAccl							9	//
#define		CONST_videoCompressors_hwAccl							10	//	"h264"					//  2011/11/25
//
#if  0		//  2014/08/24
	#define		CONST_audioCompressors_cuda								11	//							//  cuda应该扔掉。2014/07/19
	#define		CONST_videoCompressors_cuda								12	//	"h264"					//  2012/06/17
#endif
//
//  13
#define		CONST_videoCompressors_stream							14	//  "h264"					//  for rtsp. 2014/02/25
//
#define		CONST_audioCompressors_vorbis							15	//
#define		CONST_videoCompressors_vp8								16	//	"vp8"					//  2014/07/19

//
#define		CONST_audioCompressors_ffmpeg							21
#define		CONST_videoCompressors_ffmpeg							22

#define		CONST_audioCompressors_aac   							25

//
#define		CONST_audioCompressors_lyra								27								//  2025/10/29

//
#define		DEFAULT_fourccStr_vcm									"msvc"							//  2008/06/01
#define		DEFAULT_fourccStr_dmo_video								"WMV3"							//  2009/04/02
//  #define		DEFAULT_fourccStr_dmo_screen						"MSS2"							//  2009/04/02
#define		DEFAULT_fourccStr_dmo_screen							"WMV3"							//  2009/12/31

//#define		DEFAULT_fourccStr_ipp									"h264"							//  2011/08/01
//
#define		DEFAULT_fourccStr_mediaSdk								"h264"							//  2011/11/25
#define		DEFAULT_fourccStr_cuda									"h264"							//  2012/06/17

#define		DEFAULT_fourccStr_vp8									"VP8"							//  2014/07/19

//
#define		DEFAULT_fourccStr_video4k								"HEVC"



//  2011/07/31
typedef enum {
		 H264_PROFILE_CAVLC444				=	44,
		 H264_PROFILE_BASELINE				=	66,
		 H264_PROFILE_MAIN					=	77,
		 H264_PROFILE_SCALABLE_BASELINE		=	83,		// ANNEX G
		 H264_PROFILE_SCALABLE_HIGN			=	86,		// ANNEX G
		 H264_PROFILE_EXTENDED				=	88,		
		 H264_PROFILE_HIGH					=	100,	
		 H264_PROFILE_HIGH10				=	110,
		 H264_PROFILE_MULTIVIEW_HIGH		=	118,	// ANNEX H		
		 H264_PROFILE_HIGH422				=	122,	
		 H264_PROFILE_SREREO_HIGH			=	128,	// ANNEX H		
		 H264_PROFILE_HIGH444				=	144,
		 H264_PROFILE_HIGH444_PRED			=	244,

}	 H264_PROFILE_IDC;


//
//


//  
int  openLocalVideo(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiCamCapType,  LPCTSTR  displayName,  void  **ppCapStuff,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressorParam,  int  iIndex_sharedObj  );
//  2014/06/02
 int  prepareForOpeningRtsp(  MC_VAR_common  *  pProcInfoCommon,  int  iIndex_sharedObj  );
//  2014/02/23
int  openLocalVideo_rtsp(  MC_VAR_common  *  pProcInfoCommon,  LPCTSTR  url,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressorParam,  int  iIndex_sharedObj  );
//
int  openLocalVideo_rtsp_step0(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiRtspType,  LPCTSTR  url,  int  tn_rtspCliPipe,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressorParam,  LPCTSTR  tHint,  BOOL  bCapDev,  int  iIndex_sharedObj  );
int  openLocalVideo_rtsp_step1(  MC_VAR_common  *  pProcInfoCommon,  LPCTSTR  url,  BOOL  bWait,  LPCTSTR  tHint,  int  iIndex_sharedObj  );
int  openLocalVideo_rtsp_step2(  MC_VAR_common  *  pProcInfoCommon,  LPCTSTR  url,  LPCTSTR  tHint,  int  iIndex_sharedObj  );

//
int  openLocalQvcf_rtsp_step0(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiRtspType,  LPCTSTR  url,  int  tn_rtspCliPipe,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressorParam,  LPCTSTR  tHint,  int  iIndex_sharedObj  );



//  2014/09/29
int  openLocalVideo_slave(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiCamCapType,  int  iIndex_sharedObj_master,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressorParam,  int  iIndex_sharedObj  );

//  2014/10/31
int  openLocalVideo_mosaic(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiCamCapType,  BITMAPINFOHEADER  *  pBih_photomosaic,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressorParam,  int  iIndex_sharedObj  );


//
int  closeLocalVideo(  MC_VAR_common  *  pProcInfoCommon,  int  iIndex_sharedObj  );

//  2017/09/13
int  resumeLocalVideo(  MC_VAR_common  *  pProcInfoCommon,  int  iIndex_sharedObj  );


//////////////////////
//
int  yuy2ToRgb24(  void  *  pCusModulesParam,  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );
int  rgb24ToYuy2(  unsigned  char  *  rgb,  unsigned  char  *  yuy2,  int  width,  int  height  );

//  2015/01/22
int  uyvyToRgb24(  void  *  pCusModulesParam,  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );


//
int  hdycToRgb24(  void  *  pCusModulesParam,  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );	//  2012/01/03
int  v210ToRgb24(  void  *  pCusModulesParam,  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );	//  2012/02/23





//
int  rgb565ToRgb24(  unsigned  char  *  src,  unsigned  char  *  rgb,  int  width,  int  height  );


int  rgb24To32(  unsigned  char  *  src,  unsigned  char  *  dst,  int  iWidth,  int  iHeight  );				//  2013/10/06
#define	 rgb24To32_inPlace(  src,  iWidth,  iHeight  )	rgb24To32(  src,  src,  iWidth,  iHeight  )

//  2014/01/29.调整图像的长宽，使是4的倍数，以便压缩
int  rgb24To24(  unsigned  char  *  src,  int  w_src,  int  h_src,  unsigned  char  *  dst,  int  w_dst,  int  h_dst  );
#define  rgb24To24_inPlace(  src,  w_src,  h_src,  w_dst,  h_dst  )	rgb24To24(  src,  w_src,  h_src,  src,  w_dst,  h_dst  )


//  2011/12/05
int  yuy2ToYv12(  char  *  inBuff,  char  *  outBuff,  int  width,  int  height  );


/////////////////




/////////////////

//  2015/02/24
typedef  struct  __smplBsRead_param_t	{
				 unsigned  int			dwTickCnt_doPretrans;
}		 SMPL_bsRead_param;


//
int  updateDecVideoParam(  BITMAPINFOHEADER  *  pBih,  double  dFrameRate,  void  *  pParent_transform,  unsigned  int  uiTransformType  );

//
int  dec_parseEncAPkt_i_useAudioQ2(  unsigned  int  uiTransformType,  void  *  pParent_transform,  PKT_info_toDec  *  pPktInfo_toDec_param,  long  *  p_old_lPktId_getNewPkt,  unsigned  char  **  ppInput,  unsigned  int  *puiSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  puiPts  );
//
int dec_parseEncAPkt_i(uint uiTransformType, void* pParent_transform, PKT_info_toDec* pPktInfo_toDec_param, long* p_old_lPktId_getNewPkt, byte** ppInput, uint* puiSize, uint* puiSampleTimeInMs, uint* puiPts);

//
__declspec(  dllexport  )  int  dec_parseEncVPkt_i(  unsigned  int  uiTransformType,  void  *  pParent_transform,  void  *  pPkt_myDRAW_VIDEO_DATA,  long  *  p_old_lPktId_alloc,  unsigned  char  **  ppInput,  unsigned  int  *puiSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  puiPts,  SMPL_bsRead_param  *  pParam  );
//
int  parseDecAPkt_o(  void  *  pPktParam,  void  **ppAh,  unsigned  char  **  ppOutput,  unsigned  int  *puiSize  );
int  parseDecVPkt_o(  void  *  pPktParam,  void  **ppBih,  unsigned  char  **  ppOutput,  unsigned  int  *puiSize  );

//  2015/02/13
__declspec(  dllexport  )  int  enc_parseOrgAPkt_i(  unsigned  int  uiTransformType,  void  *  pParent_transform,  void  *  pPkt_myPLAY_AUDIO_DATA,  long  *  p_old_lPktId_getNewPkt,  unsigned  char  **  ppInput,  unsigned  int  *puiSize,  BOOL  *  pbNeed_forceKeyFrame  );

//
__declspec(  dllexport  )  int  enc_parseOrgVPkt_i(  unsigned  int  uiTransformType,  void  *  pParent_transform,  void  *  pPkt_myDRAW_VIDEO_DATA,  long  *  p_old_lPktId_alloc,  unsigned  char  **  ppInput,  unsigned  int  *puiSize,  BOOL  *  pbNeed_forceKeyFrame  );


//
__declspec(  dllexport  )  int  tmp_playLocalAudioData(  QDC_OBJ_INFO  *  pQdcObjInfo  );



//
__declspec(  dllexport  )  int  smplPCMReader_LoadNextFrame(  void  *  pQdcObjInfoParam,  long  *  pold_lPktId,  old_PF_myLoadNextFrame  pf_myLoadNextFrame,  void  *  p2_myLoadNextFrame,  BOOL  *  pbNeed_forceKeyFrame  );

//
int  old_smplYUVReader_LoadNextFrame(  void  *  pQdcObjInfoParam,  long  *  pold_lPktId,  old_PF_myLoadNextFrame  pf_myLoadNextFrame,  void  *  p2_myLoadNextFrame,  BOOL  *  pbNeed_forceKeyFrame  );
//
int  smplYUVReader_LoadNextFrame(void* pQdcObjInfoParam, long* pold_lPktId, PF_myLoadNextFrame  pf_myLoadNextFrame, void* p2_myLoadNextFrame, BOOL* pbNeed_forceKeyFrame);


//  2016/12/09
int  doPostEnc_audio(  void  *  pQDC_OBJ_INFO,  char  *  pInput,  unsigned  int  inputSize,  int  iSampleTimeInMs,  unsigned  int  uiPts,  void  *  pBuf_pkt  );
//
//int  doPostEnc_mediaSdk(  void  *  pQDC_OBJ_INFO,  char  *  pInput,  unsigned  int  inputSize,  int  iSampleTimeInMs,  void  *  pBuf_pkt  );
//  2015/10/20
__declspec(  dllexport  )  int  doPostEnc_mediaSdk_new(  void  *  pQDC_OBJ_INFO,  char  *  pInput,  unsigned  int  inputSize,  int  iSampleTimeInMs,  unsigned  int  uiPts,  void  *  pBuf_pkt_unused  );


//
 int  smplBitstreamReader_ReadNextFrame_func_a(  void  *  pQdcObjInfoParam,  long  *  pold_lPktId,  unsigned  int  uiToInMs,  char  *  pBsBuf,  unsigned  int  *  puiBsBufSize,  unsigned  int  *  puiSampleTimeInMs  );
 int  smplBitstreamReader_ReadNextFrame_func_a_new(  void  *  pQdcObjInfoParam,  long  *  pold_lPktId,  unsigned  int  uiToInMs,  char  *  pBsBuf,  unsigned  int  *  puiBsBufSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  puiPts,  SMPL_bsRead_param  *  pParam  );


//
int  smplBitstreamReader_ReadNextFrame_func_v(  void  *  pQdcObjInfoParam,  long  *  pold_lPktId,  unsigned  int  uiToInMs,  char  *  pBsBuf,  unsigned  int  *  puiBsBufSize,  unsigned  int  *  puiSampleTimeInMs  );
int  smplBitstreamReader_ReadNextFrame_func_v_new(  void  *  pQdcObjInfoParam,  long  *  pold_lPktId,  unsigned  int  uiToInMs,  char  *  pBsBuf,  unsigned  int  *  puiBsBufSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  puiPts,  SMPL_bsRead_param  *  pParam  );


//  2016/12/10
int smplPCMWriter_WriteNextFrame_pre(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  void  *  pYUVWriter_var  );
int smplPCMWriter_WriteNextFrame0(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  int  iFourcc,  void  *  pYUVWriter_var,  void *pImg,  PF_data_to_pcm  pf_data_to_pcm,  double  dFrameRate,  LPCTSTR  hint  );
int smplPCMWriter_WriteNextFrame1(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  void  *  pYUVWriter_var  );

int smplPCMWriter_WriteNextFrame_all(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  int  iFourcc,  void  *  pYUVWriter_var,  void *pImg,  PF_data_to_pcm  pf_data_to_pcm,  double  dFrameRate,  LPCTSTR  hint  );


//
int  smplYUVWriter_WriteNextFrame_pre(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  void  *  pYUVWriter_var  );
int  smplYUVWriter_WriteNextFrame0(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  int  iFourcc,  void  *  pYUVWriter_var,  void *pImg,  unsigned  int  cropW,  unsigned  int  cropH,  unsigned  int  pitch,  PF_img_to_yuv  pf_img_to_yuv,  double  dFrameRate,  LPCTSTR  hint  );
int  smplYUVWriter_WriteNextFrame1(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  void  *  pYUVWriter_var  );
//
int  smplYUVWriter_WriteNextFrame_all(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  int  iFourcc,  void  *  pYUVWriter_var,  void *pImg,  unsigned  int  cropW,  unsigned  int  cropH,  unsigned  int  pitch,  PF_img_to_yuv  pf_img_to_yuv,  double  dFrameRate,  LPCTSTR  hint  );


//
int  smplYUVWriter_WriteNextFrame_pre_1(void* pQdcObjInfoParam, void* pQDC_OBJ_transCommon, void* pYUVWriter_var);
int  smplYUVWriter_WriteNextFrame0_1(void* pQdcObjInfoParam, void* pQDC_OBJ_transCommon, int  iFourcc, void* pYUVWriter_var, void* pImg, unsigned  int  cropW, unsigned  int  cropH, unsigned  int  pitch, PF_img_to_yuv  pf_img_to_yuv, double  dFrameRate, LPCTSTR  hint);
int  smplYUVWriter_WriteNextFrame1_1(void* pQdcObjInfoParam, void* pQDC_OBJ_transCommon, void* pYUVWriter_var);
//
int  smplYUVWriter_WriteNextFrame_all_1(void* pQdcObjInfoParam, void* pQDC_OBJ_transCommon, int  iFourcc, void* pYUVWriter_var, void* pImg, unsigned  int  cropW, unsigned  int  cropH, unsigned  int  pitch, PF_img_to_yuv  pf_img_to_yuv, double  dFrameRate, LPCTSTR  hint);




//
void  postAPktToRender(  void  *  pQY_TRANSFORM,  void  *  pmyPLAY_AUDIO_DATA,  BOOL  *  unused_pbPktRedirected  );
void  postVPktToRender(  void  *  pQY_TRANSFORM,  void  *  pmyDRAW_VIDEO_DATA,  BOOL  *  pbPktRedirected  );




/////////////

//
 BOOL  canSave_fourcc(  int  iFourcc  );





//




//
typedef  struct  __param_setPktInputInfo_t {
				 unsigned  int				uiCapType;
				 unsigned  int				uiCapSubtype;
				 //
				 bool						bFromMosaic;
				 int						index_mosaic;
				 
				 //
				 bool						bTest_tStartTran;
				 time_t						tStartTran;

				 //
}		 Param_setPktInputInfo;

//
//  2014/11/12
int  setPktInputInfo(  MC_VAR_common  *  pProcInfoCommon,  VIDEO_input_info1  *  pInput,  unsigned  short  usFrames_perSecond_expected,  BOOL  bNoSkip,  void  *  pmyDRAW_VIDEO_DATA,  Param_setPktInputInfo  *  pParam,  LPCTSTR  hint  );

//
//
//
__declspec(  dllexport  )  int  chkFromPlayerIndex_v(  unsigned  int  uiTransformType,  void  *  pQY_TRANSFORM,  myDRAW_VIDEO_DATA  *  pPkt,  void  *  p2  );

//
//
BOOL  bCapAudioQuit(  void  *  pCAP_procInfo_audioCommon,  void  *  p1,  void  *  p2  );
__declspec(  dllexport  )  BOOL  bCapBmpQuit(  void  *  pCAP_procInfo_bmpCommon,  void  *  p1,  void  *  p2  );

//int  capBmpGetSpsPps(  void  *  pCAP_procInfo_bmpCommon,  char  *  pBuf,  unsigned  int  *  puiSize  );
__declspec(  dllexport  )  int  capBmpGetSpsPps(  unsigned  int  uiTransformType,  void  *  pCAP_procInfo_bmpCommon,  int  index_pMem_from_unused,  char  *  pBuf,  unsigned  int  *  puiSize  );

//  2016/12/09
int  capAudioGetWfx(  void  *  pCAP_procInfo_audioCommon,  WAVEFORMATEX  *  pWfx,  void  *  p2  );
__declspec(  dllexport  )  int  capBmpGetBih(  void  *  pCAP_procInfo_bmpCommon,  BITMAPINFOHEADER  *  pBih,  void  *  p2  );

//
int  transformGetWfx(  void  *  pQY_TRANSFORM,  WAVEFORMATEX  *  pWfx,  void  *  p2  );
int  transformGetBih(  void  *  pQY_TRANSFORM,  BITMAPINFOHEADER  *  pBih,  void  *  p2  );


//  2015/10/16
typedef  struct  __param_initVideoCapDev_ttsp_t  {
				 void  *  pQdcObjInfo;
}		 PARAM_initVideoCapDev_rtsp;
//
int  initVideoCapDev_rtsp(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiRtspType,  LPCTSTR  url_selected,  int  tn_rtspCliPipe,  BITMAPINFOHEADER  *  pBih_suggested,  BOOL  bForConfig,  HWND hWnd_notify,  int  iIndex_sharedObj,  PARAM_initVideoCapDev_rtsp  *  pParam,  void  **  ppVideoCapDevParam  );
int  exitVideoCapDev_rtsp(  MC_VAR_common  *  pProcInfoCommon,  void  **  ppVideoCapDevParam  );
BOOL  bGetCapturePara_rtsp(  void  *  pProcInfo,  int  iIndex_capBmp,  PF_BufferCB_av  pf,  unsigned  int  uiBufSize_pMsgBuf,  BOOL  bWait,  void  *  pVideoCapDevParam,  QY_VIDEO_HEADER  *  pVh_org  );

int  startCapture_rtsp(  void  *  pVideoCapDevParam  );
int  stopCapture_rtsp(  void  *  pVideoCapDevParam  );

/////////////////
int  initQvcf_rtsp(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiRtspType,  LPCTSTR  url_selected,  int  tn_rtspCliPipe,  BITMAPINFOHEADER  *  pBih_suggested,  BOOL  bForConfig,  HWND hWnd_notify,  int  iIndex_sharedObj,  void  **  ppQvcfParam  );
int  exitQvcf_rtsp(  MC_VAR_common  *  pProcInfoCommon,  void  **  ppQvcfParam  );



///////////////////////
//  2014/09/30
QY_sharedObj_sync  *  getSharedObjSyncByIndex(  MC_VAR_common  *  pProcInfo,  int  index  );
QY_SHARED_OBJ  *  getSharedObjByIndex(  MC_VAR_common  *  pProcInfo,  int  index  );
//
int  getSharedObjUsrIndex(  CCtxQmcTmpl  *  pProcInfo,  int  iTaskId,  int  index_sharedObj  );

//
CAP_procInfo_bmpU  *  getCapBmpBySth(  MC_VAR_common  *  pProcInfo,  int  index,  unsigned  int  uiCapType  );
CAP_procInfo_audioU  *  getCapAudioBySth(  MC_VAR_common  *  pProcInfo,  int  index,  unsigned  int  uiCapType  );


/////////////////
__declspec(  dllexport  )  int  addToMsgrs_sendLocalAv(  MC_VAR_common  *  pProcInfo,  void  *  pMIS_CNT,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  char  ucbVideoConferenceStarter,  ROUTE_sendLocalAv	*	pRoute, bool  bConfAv,  LPCTSTR  hint  );
__declspec(  dllexport  )  int  removeFromMsgrs_sendLocalAv(  MC_VAR_common  *  pProcInfo,  void  *  pMIS_CNT,  QY_MESSENGER_ID  *  pIdInfo,  ROUTE_sendLocalAv  *  pRoute, bool  bConfAv,  LPCTSTR  hint  );

//
BOOL  isEmpty_ROUTE_sendLocalAv(  ROUTE_sendLocalAv  *  pRoute  );



////////////////////////
//
SHARED_OBJ_USR  *  getSharedObjUsr(  QY_SHARED_OBJ  *  pSharedObj,  int  iIndex_usr  );

//
void  askSharedObjToStop(  MC_VAR_common  *  pProcInfo,  QY_SHARED_OBJ  *  pSharedObj,  HWND  hWnd_notifyEnd,  LPCTSTR  hint  );



//////////
__declspec(dllexport) int  initCompressAudio(  MC_VAR_common  *  pProcInfo,  WAVEFORMATEX  *  pWf_input,  AUDIO_COMPRESSOR_CFG  *  pCompressor,  COMPRESS_AUDIO  *  p  );
__declspec(dllexport) int  exitCompressAudio(  MC_VAR_common  *  pProcInfo,  COMPRESS_AUDIO  *  p  );

//int initResampleAudio(MC_VAR_common* pProcInfo, WAVEFORMATEX* pWf_input, AUDIO_COMPRESSOR_CFG* pCompressor, RESAMPLE_AUDIO* p);
//int exitResampleAudio(MC_VAR_common* pProcInfo, RESAMPLE_AUDIO* p);

//
__declspec(dllexport) int  initCompressVideo(  void  *  pProcInfoParam,  BITMAPINFO  *  pBmpInfo_input,  unsigned  int  uiCapType,  VIDEO_COMPRESSOR_CFG  *  pCompressor,  BOOL  bCapDev,  unsigned  int  uiBufSize_pData,  COMPRESS_VIDEO  *  pCompressVideo  );
__declspec(dllexport) int  exitCompressVideo(  void  *  pProcInfo,  BOOL  bCapDev,  COMPRESS_VIDEO  *  pCompressVideo  );



/////////////////
//  BOOL  bRobotTaskExists(  MC_VAR_isCli  *  pProcInfo,  MIS_CNT  *  pMisCnt,  MIS_MSG_applyForChkChannels_qmc  *  pMsg  );
BOOL  bMediaTaskExists(  MC_VAR_common  *  pProcInfo,  int  iTaskId  );


void  *  getMoniker_v(  void  *  pCapParam,  int  iMenuId  );
int  getMonikerProp(  void  *  pMonikerParam,  LPCTSTR  propName,  TCHAR  *  propVal,  int  propValCnt  ); 


#define		MAX_monikerDisplayNameLen		256

#define		CONST_moniker_DevicePath		_T(  "DevicePath"  )
#define		CONST_moniker_FriendlyName		_T(  "FriendlyName"  )

int  getMonikerDisplayName(  void  *  pMonikerParam,  TCHAR  *  displayName,  int  displayNameCnt  );
int  getMonikerByDisplayName(  LPCTSTR  displayName,  void  **  ppMoniker  );

//  #define  getMonikerDevicePath(  pMonikerParam,  devicePath,  devicePathCnt  )	getMonikerProp(  pMonikerParam,  CONST_moniker_DevicePath,  devicePath,  devicePathCnt  )
#define  getMonikerFriendlyName(  pMonikerParam,  friendlyName,  friendlyNameCnt  )	getMonikerProp(  pMonikerParam,  CONST_moniker_FriendlyName,  friendlyName,  friendlyNameCnt  )

//
int  qmcApplyForRemovingInvliadTasks(  MC_VAR_common  *  pProcInfo,  unsigned  int  uiChannelType  );	//  2009/09/10

//
//
int  notifyCapEnd(  void  *  pQY_MC,  unsigned  int  uiCapType,  int  iIndex_capBmp,  int  iTaskId,  HWND  hWnd  );


//
//
DWORD WINAPI mcThreadProc_vpp( LPVOID lpParameter );
DWORD WINAPI mcThreadProc_vpp1_proc( LPVOID lpParameter ); 
DWORD WINAPI mcThreadProc_vpp2_beforeEnc( LPVOID lpParameter );
//
DWORD WINAPI mcThreadProc_encVideo( LPVOID lpParameter );
DWORD WINAPI mcThreadProc_toShareVideo_post( LPVOID lpParameter );

//
//
extern "C" DWORD WINAPI mcThreadProc_decAudio( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_decAudioRtsp(LPVOID lpParameter);

//
extern "C" DWORD WINAPI mcThreadProc_preTransformVideo( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_decVideo( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_saveAv( LPVOID lpParameter );



//
__declspec(  dllexport  ) int  refreshWebCamSettings(  VIDEO_COMPRESSOR_CFG  *  pVideoCompressorCfg,  CAP_procInfo_video  *  pVc  );
 
//
//
HRESULT  BufferCB_av(  void  *  pProcInfoParam,  int  iIndex_capProcInfo,  void  *  pSampleGrabberCbVar,  int  iSampleTimeInMs,  BYTE  *  pBuffer,  long  BufferLen  );


//
int  initOrg2RgbBuf(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_bmpCommon  *  pVc  );
void  exitOrg2RgbBuf(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_bmpCommon  *  pVc  );
//
//int  org2Rgb(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_bmpCommon  *  pVc,  BYTE  *  pInput,  char  *  pOrg2RgbBuf  );
int  org2Rgb(MC_VAR_common* pProcInfo, CAP_procInfo_bmpCommon* pVc, BITMAPINFOHEADER bih_org, BYTE* pInput, char* pOrg2RgbBuf);


//////////////////

//  
int  initVideoCapDev_dx(  void  *  p_reserved,  LPCTSTR  displayName_selected,  void  **  ppCapStuff,  BITMAPINFOHEADER  *  pBih_suggested,  BOOL  bForConfig,  HWND hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppVideoCapDevParam  );
int  exitVideoCapDev_dx(  void  **  ppVideoCapDevParam  );
BOOL  bGetCapturePara_dx(  void  *  pProcInfo,  int  iIndex_capBmp,  PF_BufferCB_av  pf,  unsigned  int  uiBufSize_pMsgBuf,  void  *  pVideoCapDevParam,  QY_VIDEO_HEADER  *  pVh_org  );
int  startCapture_dx(  void  *  pVideoCapDev  );
int  stopCapture_dx(  void  *  pVideoCapDev  );

//
__declspec(  dllexport  )  int  startAvRecord(  MC_VAR_common  *  pProcInfo,  int  iIndex_screenCapProcInfo,  HWND  hWnd_notifyEnd  );
 __declspec(  dllexport  )  void  exitAvRecord(  void  *  pCOMPRESS_VIDEO  );

 //
 //
int  initShareMediaFile(  LPCTSTR  tFile,  HWND  hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppShareMediaFileParam  );
int  exitShareMediaFile(  void  **  ppShareMediaFileParam  );

//
BOOL  bGetCapturePara_shareMediaFile(  MC_VAR_common  *  pProcInfo,  int  iIndex_capAudio,  int  iIndex_capBmp,  void  *  pShareMediaFile,  WAVEFORMATEX  *  pWf_org,  QY_VIDEO_HEADER  *  pVh_org,  SAMPLE_grabberCb_cache  *  pCache  );

int  runShareMediaFile(  void  *  pShareMediaFileParam  );
int  stopShareMediaFile(  void  *  pShareMediaFileParam  );
int  pauseShareMediaFile(  void  *  pShareMediaFileParam  );
int  getShareMediaFileState(  void  *  pShareMediaFileParam  );

//  int  resumeAudio(  void  *  pShareMediaFileParam  );
//  int  muteAudio(  void  *  pShareMediaFileParam  );

//
int  initShareMediaDevice(  void  **  ppCapStuff,  AUDIO_COMPRESSOR_CFG  *  pAudioCompressor,  BITMAPINFOHEADER  *  pBih_suggested,  HWND  hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppShareMediaDeviceParam  );
int  exitShareMediaDevice(  void  **  ppShareMediaDeviceParam  );

BOOL  bGetCapturePara_shareMediaDevice(  MC_VAR_common  *  pProcInfo,  int  iIndex_capAudio,  int  iIndex_capBmp,  void  *  pShareMediaDevice,  WAVEFORMATEX  *  pWf_org,  QY_VIDEO_HEADER  *  pVh_org,  SAMPLE_grabberCb_cache  *  pCache  );

int  runShareMediaDevice(  void  *  pShareMediaDeviceParam  );
int  stopShareMediaDevice(  void  *  pShareMediaDeviceParam  );


//
int  initShareIc(void** ppCapStuff, AUDIO_COMPRESSOR_CFG* pAudioCompressor, BITMAPINFOHEADER* pBih_suggested, HWND  hWnd_notify, int  index_sharedObj, void** ppShareMediaDeviceParam);
int  exitShareIc(void** ppShareMediaDeviceParam);

BOOL  bGetCapturePara_shareIc(MC_VAR_common* pProcInfo, int  iIndex_capAudio, int  iIndex_capBmp, void* pShareMediaDevice, WAVEFORMATEX* pWf_org, QY_VIDEO_HEADER* pVh_org);

int  runShareIc(void* pShareMediaDeviceParam);
int  stopShareIc(void* pShareMediaDeviceParam);




////////////////////////
int  runSharedMediaObj(  MC_VAR_common  *  pProcInfo,  QY_SHARED_OBJ  *  pSharedObj  );
int  exitSharedMediaObj(  MC_VAR_common  *  pProcInfo,  QY_SHARED_OBJ  *  pSharedObj  );





//
int  shareDynBmp_closeTaskAv(  void  *  pSHARE_dyn_bmp  );


//
//
int  startCapture(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_video  *  pVc  );
int  stopCapture(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_video  *  pVc  );


//
__declspec(  dllexport  )  BOOL  bSharedObjActive(  MC_VAR_common  *  pProcInfo,  int  index  );

//
int  freeSharedObjByIndex(  CCtxQmcTmpl  *  pProcInfo,  int  index  );


///////////////

//
__declspec(dllexport)  int  doAll_setFlg_forceKeyFrame(CCtxQmc* pProcInfo);

//
__declspec(  dllexport  )  int  setFlg_forceKeyFrame(  MC_VAR_common  *  pProcInfo,  int  iIndex_sharedObj  );


//
int  getSharedObjIndex_localAv(  );
int  getNewSharedObjUsr_localAv(  MC_VAR_common  *  pProcInfo,  HWND  hWnd,  int  *  piIndex_sharedObj,  int  *  piIndex_sharedObjUsr,  BOOL  *  pbFirstUsr  );
//int  freeSharedObjUsr_localAv(  void  *  pMC_VAR_isCli,  int  index,  HWND  hWnd  );
int  setCurSharedObjUsr_localAv(  void  *  pMC_VAR_isCli,  int  index_sharedObj,  int index_sharedObjUsr  );
int  resetCurSharedObjUsr_localAv(  void  *  pMC_VAR_isCli,  int  index_sharedObj  );

//
int  newSharedObjIndex(  MC_VAR_common  *  pProcInfo,  HWND  hWnd,  int  iSharedObjType,  int  *  piIndex_sharedObjUsr,  BOOL  *  pbFirstUsr  );
int  getNewSharedObjUsr(  MC_VAR_common  *  pProcInfo,  HWND  hWnd,  int  iIndex_sharedObj,  int  *  piIndex_sharedObjUsr,  BOOL  *  pbFirstUsr  );
int  freeSharedObjUsr(  void  *  pMC_VAR_isCli,  int  index,  HWND  hWnd  );
//int  setCurSharedObjUsr(  MC_VAR_common  *  pProcInfo,  int  index_sharedObj,  HWND  hWnd  );
int  setCurSharedObjUsr(MC_VAR_common* pProcInfo, int  index_sharedObj, int  index_sharedObjUsr);
int  resetCurSharedObjUsr(  void  *  pMC_VAR_isCli,  int  index_sharedObj  );



#endif  //  }


