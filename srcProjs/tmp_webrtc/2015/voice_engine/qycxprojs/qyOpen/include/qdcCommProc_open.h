

#ifndef  __QDCCOMMPROC_OPEN_H__
#define  __QDCCOMMPROC_OPEN_H__		//  {

//  2015/10/30
#include	"qisD3dDefs_open.h"


//
#define		CONST_qdcCompressorId_null								0
#define		CONST_qdcCompressorId_test								1

#define		CONST_qdcCompressorId_user								32768
//

//  2011/12/21
#define		CONST_qdcRet_bufTooSmall								-2101
#define		CONST_qdcRet_exception									-2102	//  2014/08/11


//  2014/08/28
#define		DEFAULT_keyDistanceInS									30		//  2015/11/06	//  7
//  2014/12/06
#define		DEFAULT_keyDistanceInS_mosaic							30



//  2016/12/17
#define		CONST_qoiType_null			0
#define		CONST_qoiType_encA			1
#define		CONST_qoiType_decA			2
#define		CONST_qoiType_encV			3
#define		CONST_qoiType_decV			4


//  2015/10/03				 
typedef  struct  __qdcObjInfo_varCommon_t							{
				 //
				 void									*			pObj;

				 //
				 unsigned  char										ucbTransformFuncsOk;						//  2014/03/26

				 //
				 DWORD												cbInputBuffer;
				 DWORD												cbOutputBuffer;

				 int												iDiffInMs_tStartAudio;						//  2009/05/26
				 void										*		pDebugStep;									//  2010/04/28

				 
				 //  2014/08/25
				 struct												{
						 BOOL										bNeed_forceKeyFrame;
						 //
						 DWORD										dwLastTickCnt_insertKeyFrame;
				 }													encInfo;
				 //
				 struct												{
				 }													decInfo;

				 //  2015/09/27
				 unsigned  short									usPktResType_dec;				 
				 //
				 struct  {
					 unsigned  int									uiSeqNo_lastRender;							//  2015/10/06
				 }													sharedTex;
				 	
				 //  2015/10/17
				 struct												{
					 int											min_qNodes_left;
					 //
					 DWORD											dwTgt_start;
				 }													mql;

}		 QDC_objInfo_varCommon;




//
#if  0  //  2016/04/18
typedef  struct  __qdcObjInfo_t										{
				 
				 //  2014/03/25
				 VIDEO_COMPRESSOR_cfgCommon							cfg;

				 //
				 QDC_objInfo_varCommon								var;

}		 QDC_OBJ_INFO;
#endif


//  2016/04/18
typedef  BOOL  (  *PF_qoi_bGetLongProperty  )(  void  *  pQdcObjInfoParam,  int  propertyId,  long  *  pVal  );
typedef  BOOL  (  *PF_qoi_bSetLongProperty  )(  void  *  pQdcObjInfoParam,  int  propertyId,  long  val  );
//
typedef  BOOL  (  *PF_qoi_bGetStrProperty  )(  void  *  pQdcObjInfoParam,  int  propertyId,  TCHAR  *  tBuf,  int  tBufCnt  );
typedef  BOOL  (  *PF_qoi_bSetStrProperty  )(  void  *  pQdcObjInfoParam,  int  propertyId,  LPCTSTR  val  );
//
typedef  void  *  (  *PF_qoi_getPtrProperty  )(  void  *  pQdcObjInfoParam,  int  propertyId  );
typedef  BOOL  (  *PF_qoi_bSetPtrProperty  )(  void  *  pQdcObjInfoParam,  int  propertyId,  void  *  ptr  );
typedef  void  *  (  *PF_qoi_getSpecialPtrProperty  )(  void  *  pQdcObjInfoParam,  int  propertyId,  void  *  p0,  void  *  p1  );
typedef  BOOL  (  *PF_qoi_bSetSpecialProperty  )(  void  *  pQdcObjInfoParam,  int  propertyId,  void  *  p0,  void  *  p1,  void  *  p2  );



//
//  2016/04/18
typedef  struct  __qdcObjInfo_t										{
				 unsigned  int										uiType;								//  2016/04/18
				 unsigned  short									usSubtype;							//  2016/04/18
				 int												iUsage;								//  2016/04/18
				 
				 //
				 PF_qoi_bGetLongProperty							pf_qoi_bGetLongProperty;
				 PF_qoi_bSetLongProperty							pf_qoi_bSetLongProperty;
				 //
				 PF_qoi_bGetStrProperty								pf_qoi_bGetStrProperty;
				 PF_qoi_bSetStrProperty								pf_qoi_bSetStrProperty;
				 
				 //
				 PF_qoi_getPtrProperty								pf_qoi_getPtrProperty;				//  dll get sth from qm
				 PF_qoi_bSetPtrProperty								pf_qoi_bSetPtrProperty;				//  dll set sth in qm
				 PF_qoi_getSpecialPtrProperty						pf_qoi_getSpecialPtrProperty;
				 PF_qoi_bSetSpecialProperty							pf_qoi_bSetSpecialProperty;

				 
				 //  2014/03/25
				 struct  {
					 AUDIO_COMPRESSOR_cfgCommon						a;		//  2016/12/06			
					 VIDEO_COMPRESSOR_cfgCommon						v;		//  cfg;
				 }													cfg;

				 //
				 QDC_objInfo_varCommon								var;

}		 QDC_OBJ_INFO,  QOI_common;





//  2011/12/03
typedef  int  (  *PF_yuy2ToRgb24  )(  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );
typedef  int  (  *PF_uyvyToRgb24  )(  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );	//  2012/02/23
typedef  int  (  *PF_yuy2ToYv12  )(  char  *  inBuff,  char  *  outBuff,  int  width,  int  height  );
typedef  int  (  *PF_rgb24ToYv12  )(  unsigned  char  *  rgb,  unsigned  char  *  yuv,  int  width,  int  height,  BOOL  bFlipImg  );
typedef  int  (  *PF_yv12ToRgb24  )( unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );


typedef  struct  __qdcMgr_t											{
				 QIS_guiOpen								*		pGuiOpen;						//  2011/12/14
				 //
				 int												iCompressorId;
				 TCHAR												name[32];
				 //
				 PF_yuy2ToRgb24										pf_yuy2ToRgb24;					//  2011/12/03
				 PF_yuy2ToYv12										pf_yuy2ToYv12;
				 PF_rgb24ToYv12										pf_rgb24ToYv12;
				 PF_yv12ToRgb24										pf_yv12ToRgb24;
				 PF_uyvyToRgb24										pf_uyvyToRgb24;					//  2012/02/23	//  void	*			p4_reserved;
				 void									*			p5_reserved;
				 void									*			p6_reserved;
				 void									*			p7_reserved;
				 void									*			p8_reserved;
				 void									*			p9_reserved;
				 //
				 void									*			p;								//  给模块dll保留的一个参数
				 //
				 unsigned  char										ucbNotSupported_hw;				//  2011/11/26
				 //
				 unsigned  char										ucbNotSupported_dec_h264;		//  2012/09/09
				 //
				 char												ver[8  +  1];					//  2014/12/02

}		 QDC_MGR;


typedef  struct  __qdcOutput_t										{
				 BYTE									*			pBuf;
				 unsigned  int										size;			//  2014/07/21
				 unsigned  int										len;
				 //
				 __int64											rtStart;		//  REFERENCE_TIME			rtStart;
				 __int64											rtTimeLen;		//  REFERENCE_TIME			rtTimeLen;

}		 QDC_OUTPUT;


//
typedef  struct  __qdcObj_transCommon_t								{

				 //  QDC_OUTPUT										outs[1];
				 QDC_OUTPUT											outs[10];	// 2011/09/04

					
				 BOOL												bInited;					//  2014/02/26.等ipp解出sps,pps
				 BOOL												bInited2;					//  2014/02/26.等ipp解除sps后,需要分配一些内存

}		 QDC_OBJ_transCommon;

#define	QDC_OBJ_h264Common	QDC_OBJ_transCommon


//
typedef  struct  __qdcObj_hdDec_t									{
				 QDC_OBJ_h264Common									common;

				 //  2014/03/24
				    
				 //  
				 void										*		pPipeline;

				
				 //  2011/11/26
				 unsigned  char										ucbFlipped;
				 
}		 QDC_OBJ_hdDec;

//
typedef  struct  __qdcObj_trans_t									{
				 
				 QDC_OBJ_h264Common									common;


				 //
				 void										*		pPipeline;
				 void										*		p_init_params;		//  2012/09/01
						
}		 QDC_OBJ_trans;


//
//  2016/04/09
#define		MAX_pkts_sharedTexInfo_forYuvWriter						10
//
typedef  struct  __pkts_sharedTexInfo_forYuvWriter_t				{
				 //  2015/09/29
				 PKT_sharedTex_info									mems[MAX_pkts_sharedTexInfo_forYuvWriter];
				 unsigned  char										ucCnt;
}		 PKTS_sharedTexInfo_forYuvWriter;



#if  0  //  2016/04/09
//  2014/06/22
typedef  struct														{
		void												*		pQdcObjInfoParam;

		//
		void												*		pPkt;
		unsigned  int												size_pPkt;

		//
		struct														{
			BYTE											*		pBuf;
			unsigned  int											uiOutputSize;
			unsigned  int											DataOffset;
			int														len;
			BOOL													bBufTooSmall;

			//  2015/09/30
			unsigned  short											usPktResType;
			PKT_sharedTex_info										pktSharedTexInfo;
		}															outputInfo;
}		old_YUVWriter_var;
#endif

//
//  2016/04/09
//  2014/06/22
typedef  struct														{
		void												*		pQdcObjInfoParam;

		//
		void												*		pPkt;
		unsigned  int												size_pPkt;

		//
		struct														{
			BYTE											*		pBuf;
			unsigned  int											uiOutputSize;
			unsigned  int											DataOffset;
			int														len;
			BOOL													bBufTooSmall;

			//  2015/09/30
			unsigned  short											usPktResType;
			//PKT_sharedTex_info										pktSharedTexInfo;
			PKTS_sharedTexInfo_forYuvWriter							pkts_sharedTexInfo;

		}															outputInfo;
}		YUVWriter_var;




//  2014/07/08
typedef  struct														{
		void												*		m_pQdcObjInfoParam;
		
		//
		void												*		pPkt;
		unsigned  int												size_pPkt;

}		BitstreamWriter_var;



//  2015/10/20
 //
#define		CONST_qdcPropId_null														0
#define		CONST_qdcPropId_bSupport_sharedTex_dec										1
#define		CONST_qdcPropId_bSupport_sharedTex_enc										2
//
#define		CONST_qdcPropId_bShowDec_sharedTexStatus									100			//  2016/04/09
#define		CONST_qdcPropId_uiXql_player												101			//  2016/04/14

//  2016/04/26
#define		CONST_qdcPropId_PF_DEC_d3d11_devVar_new										200
#define		CONST_qdcPropId_PF_DEC_d3d11_devVar_free									201
#define		CONST_qdcPropId_PF_decDev_my_RenderFrame									202

//  2016/05/02
#define		CONST_qdcPropId_PF_ENC_d3d11_devVar_new										220
#define		CONST_qdcPropId_PF_ENC_d3d11_devVar_free									221
#define		CONST_qdcPropId_PF_encDev_YUVReader_myLoadNextFrame							222
#define		CONST_qdcPropId_PF_preForTest_encDev_YUVReader_myLoadNextFrame				223


//  2016/05/06
#define		CONST_qdcPropId_PF_getSize_QIS_chromaKey_effect								250
#define		CONST_qdcPropId_PF_initQisChromaKeyEffect									251
#define		CONST_qdcPropId_PF_exitQisChromaKeyEffect									252

//
#define		CONST_qdcPropId_PF_createQuad												260
#define		CONST_qdcPropId_PF_freeQuad													261
//
#define		CONST_qdcPropId_PF_getOrtho2DMats											265
//
#define		CONST_qdcPropId_PF_myCopyTex_rtt											268			//  2016/05/07

//  2016/05/06
//  #define		CONST_qdcPropId_fn_ck													250
#define		CONST_qdcPropId_fn_ck														280			//  2016/12/17


//
#define		CONST_qdcPropId_PF_qdcGetVorbisHeaders										360			//  2016/12/17


//  2016/065/06
#define		MAX_qdcPropId_open															3000


//  2011/06/19
typedef  int  (  *PF_qdcInit  )(  QDC_MGR  *  p  );
typedef  int  (  *PF_qdcExit  )(  QDC_MGR  *  p  );

//  2015/10/20
typedef  int  (  *PF_qdcGetProp  )(  int  iPropId,  void  *  pParam_input,  void  *  pParam_output  );
//  2016/04/08
typedef  int  (  *PF_qdcSetProp  )(  int  iPropId,  void  *  pParam_input,  void  *  pParam_output  );


//
typedef  int  (  *PF_qdcGetCompressAudioCfg  )(  WAVEFORMATEX  *  pWf_decompress,  WAVEFORMATEX  *  pWf_compress  );
typedef  int  (  *PF_qdcGetCompressVideoCfg  )(  char  *  fourccStr,  unsigned  int  size  );

typedef  int  (  *PF_qdcInitCompressAudio  )(  void  *  pAudioCompressorCfg_reserved,  QY_AUDIO_HEADER  *  pAh_decompress,  QY_AUDIO_HEADER  *  pAh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  );
typedef  int  (  *PF_qdcExitCompressAudio  )(  QDC_OBJ_INFO  *  pQdcObjInfo  );
typedef  int  (  *PF_qdcCompressAudio  )(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_decompress,  BYTE  *  pInput,  unsigned  int  uiInputSize,  int  iSampleTimeInMs  );

//  2016/12/05
typedef  int  (  *PF_qdcCompressAudioRun  )(  QDC_OBJ_INFO  *  pQdcObjInfo  );


//
typedef  int  (  *PF_qdcInitDecompressAudio  )(  void  *  pAudioCompressorCfg,  QY_AUDIO_HEADER  *  pAh_compress,  QY_AUDIO_HEADER  *  pAh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  );
typedef  int  (  *PF_qdcExitDecompressAudio  )(  QDC_OBJ_INFO  *  pQdcObjInfo  );
typedef  int  (  *PF_qdcDecompressAudio  )(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_compress,  BYTE  *  pInput,  unsigned  int  uiInputLen,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  );

//
//  2016/12/05
typedef  int  (  *PF_qdcDecompressAudioRun  )(  QDC_OBJ_INFO  *  pQdcObjInfo  );


//
typedef  int  (  *PF_qdcInitCompressVideo  )(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_decompress,  QY_VIDEO_HEADER  *  pVh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  );
typedef  int  (  *PF_qdcExitCompressVideo  )(  QDC_OBJ_INFO  *  pQdcObjInfo  );
typedef  int  (  *PF_qdcCompressVideo  )(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs  );	//  2012/06/17

//  2014/04/02
typedef  int  (  *PF_qdcCompressVideoRun  )(  QDC_OBJ_INFO  *  pQdcObjInfo  );


//  2014/03/30
typedef  int  (  *PF_qdcGetSpsPps  )(  QDC_OBJ_INFO  *  pQdcObjInfo,  char  *  spsBuf,  unsigned  int  *  puiSpsSize,  char  *  ppsBuf,  unsigned  int  *  puiPpsSize,  char  *  kk,  unsigned  int  *  puiKkSize  );

//  2016/12/17
typedef  int  (  *PF_qdcGetVorbisHeaders  )(  QDC_OBJ_INFO  *  pQdcObjInfo,  char  *  pBuf_header0,  unsigned  int  *  puiBufSize_header0,  char  *  pBuf_header1,  unsigned  int  *  puiBufSize_header1,  char  *  pBuf_header2,  unsigned  int  *  puiByfSize_header2  );  

//
typedef  int  (  *PF_qdcInitDecompressVideo  )(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_compress,  QY_VIDEO_HEADER  *  pVh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  );
typedef  int  (  *PF_qdcExitDecompressVideo  )(  QDC_OBJ_INFO  *  pQdcObjInfo  );
typedef  int  (  *PF_qdcDecompressVideo  )(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs  );	//  2012/06/17

//  2011/12/10
typedef  int  (  *PF_qdcDecompressVideoAndOutput  )(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  BITMAPINFO  *  pBmpInfo_output,  BYTE  *  pOutput  );

//  2014/03/28
typedef  int  (  *PF_qdcDecompressVideoRun  )(  QDC_OBJ_INFO  *  pQdcObjInfo  );


//
typedef  int  (  *PF_qdcGetOutputByIndex  )(  QDC_OBJ_INFO  *  pQdcObjInfo,  int  index,  BYTE *  pbOutData,  unsigned  int  *  puiDataSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  pui_rtTimeLen  );
typedef  int  (  *PF_qdcClearOutputs  )(  QDC_OBJ_INFO  *  pQdcObjInfo  );

/////////////////
//
//
int  makeBmpInfoHeader_rgb(  unsigned  int  bits,  int  iWidth,  int  iHeight,  BITMAPINFOHEADER  *  p  );
int  makeBmpInfoHeader_yuy2(  unsigned  int  bits,  int  iWidth,  int  iHeight,  BITMAPINFOHEADER  *  p  );
 int makeBmpInfoHeader_yv12(  unsigned int bits,  int iWidth,  int iHeight,  BITMAPINFOHEADER  *  p  );
 int makeBmpInfoHeader_i420(  unsigned int bits,  int iWidth,  int iHeight,  BITMAPINFOHEADER  *  p  );		//  2014/07/20

 //
 int makeBmpInfoHeader_yuv(  int  iFourcc,  unsigned int bits,  int iWidth,  int iHeight,  BITMAPINFOHEADER  *  p  );	//  2014/07/22

 //
#define		CONST_peek_factor				1.14
#define		CONST_peek_factor_720p			1.1
 //
__int64  myGetBitrate(  VIDEO_COMPRESSOR_cfgCommon  *  pVideoCfgCommon,  unsigned  int  w,  unsigned  int  h  );
float  myGetPeekFactor(  VIDEO_COMPRESSOR_cfgCommon  *  pVideoCfgCommon,  unsigned  int  w,  unsigned  int  h  );
 //int  tmp_showInfo(  TCHAR  *  hint  );


#endif  //  }



