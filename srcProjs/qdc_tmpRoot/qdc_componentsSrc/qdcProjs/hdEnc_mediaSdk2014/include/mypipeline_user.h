//* ////////////////////////////////////////////////////////////////////////////// */
//*
//
//              INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license  agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in  accordance  with the terms of that agreement.
//        Copyright (c) 2010 Intel Corporation. All Rights Reserved.
//
//
//*/

#ifndef __PIPELINE_USER_H__
#define __PIPELINE_USER_H__

#include "pipeline_encode.h"
#include	"myEncode_render.h"

//
#define		CHECK_POINTER		MSDK_CHECK_POINTER
#define		CHECK_ERROR			MSDK_CHECK_ERROR
#define		ZERO_MEMORY			MSDK_ZERO_MEMORY
#define		CHECK_NOT_EQUAL		MSDK_CHECK_NOT_EQUAL
#define		CHECK_RESULT		MSDK_CHECK_RESULT
#define		ALIGN16				MSDK_ALIGN16
#define		ALIGN32				MSDK_ALIGN32
#define		BREAK_ON_ERROR		MSDK_BREAK_ON_ERROR
#define		INVALID_SURF_IDX	MSDK_INVALID_SURF_IDX
#define		CHECK_RESULT_SAFE	MSDK_CHECK_RESULT_SAFE
#define		IGNORE_MFX_STS		MSDK_IGNORE_MFX_STS
#define		SAFE_DELETE			MSDK_SAFE_DELETE
#define		SAFE_RELEASE		MSDK_SAFE_RELEASE
#define		WAIT_INTERVAL		MSDK_WAIT_INTERVAL
#define		SAFE_DELETE_ARRAY	MSDK_SAFE_DELETE_ARRAY
#define		MAX					MSDK_MAX


/* This class implements the following pipeline: user plugin (frame rotation) -> mfxENCODE */
class CMyUserPipeline : public CEncodingPipeline
{
public:

    CMyUserPipeline();
    virtual ~CMyUserPipeline();

	//
	int  MakeSPSPPS(  char  *  spsBuf,  unsigned  int  *  puiSpsSize,  char  *  ppsBuf,  unsigned  int  *  puiPpsSize  );
	int  MakeVPS(  char  *  vpsBuf,  unsigned  int  *  puiVpsSize  );

	//  2015/10/08
	virtual mfxStatus InitMfxEncParams(sInputParams *pParams);
	//
	virtual mfxStatus InitFileWriter(CSmplBitstreamWriter **ppWriter, const msdk_char *filename);

    //  virtual mfxStatus Init(void  *  pQdcObjInfo,  sInputParams *pParams);	
	virtual mfxStatus Init(sInputParams *pParams);   
    //virtual mfxStatus Run();

	//  2017/10/07
	virtual mfxStatus LoadNextFrame(mfxFrameSurface1* pSurf);




	//
	struct							{
		void				*		pQdcObjInfo;		//  2012/08/24

		//
		BOOL						bFailed;
		mfxStatus					sts_failed;

		//
		unsigned  char				ucbUsing_sharedTex;	//  2015/10/30
		unsigned  char				ucbUsingRender;		//  2015/10/30

	}								m_var;


	//extcoding options for instructing encoder to specify maxdecodebuffering=1 
    mfxExtCodingOption m_extCO;


	//  2015/10/30
	bool                    m_bIsMVC; // enables MVC mode (need to support several files as an output)

#if D3D_SURFACES_SUPPORT
    IGFXS3DControl          *m_pS3DControl;

    CMyEncodeD3DRender         m_d3dRender;
#endif



	//
	int  CMySmplYUVReader_myLoadNextFrame_msdk(  unsigned  short  usPktResType,  void  *  p0_pInput,  void  *  p1_uiInputSize,  PARAM_CMySmplYUVReader_myLoadNextFrame_msdk  *  pParam  );

	//
	virtual mfxStatus CreateHWDevice();

	//
	virtual mfxStatus CreateRenderingWindow(sInputParams *pParams, bool try_s3d);



};


#endif // __PIPELINE_USER_H__ 