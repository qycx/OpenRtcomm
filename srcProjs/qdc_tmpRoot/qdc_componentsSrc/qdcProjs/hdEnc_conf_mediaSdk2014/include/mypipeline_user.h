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

//  #include "pipeline_encode.h"
#include "video_conf_pipeline.h"




/* This class implements the following pipeline: user plugin (frame rotation) -> mfxENCODE */
class CMyUserPipeline : public VideoConfPipeline	//  CEncodingPipeline
{
public:

    CMyUserPipeline();
    virtual ~CMyUserPipeline();

	//
	int  MakeSPSPPS(  char  *  spsBuf,  unsigned  int  *  puiSpsSize,  char  *  ppsBuf,  unsigned  int  *  puiPpsSize  );

	//
    virtual mfxStatus Run();
	virtual mfxStatus   Init(IInitParams *);

    //virtual void Close();
	//virtual mfxStatus ResetMFXComponents(sInputParams* pParams);


	//struct sInputParams				m_params;		//  2011/12/14
	struct							{
		void				*		pQdcObjInfo;	//  2012/08/24

		//
		BOOL						bFailed;
		mfxStatus					sts_failed;

		

		//

	}								m_var;

	//
	mfxStatus InitMfxEncParamsLowLatency();


};


#endif // __PIPELINE_USER_H__ 