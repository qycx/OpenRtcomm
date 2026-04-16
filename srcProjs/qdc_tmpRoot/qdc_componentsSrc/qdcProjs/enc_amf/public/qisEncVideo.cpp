


#include	"stdafx.h"
#include	<tchar.h>
#include	<stdlib.h>
#include	<Dshow.h>

#include	<mmreg.h>

#include	"qisCompressProc.h"



extern  "C"  int  __declspec(  dllexport  )qdcInitCompressVideo(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_decompress,  QY_VIDEO_HEADER  *  pVh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{	
	int						iErr	=	-1;
	//QDC_OBJ_INFO			qdcObjInfo;
	QDC_OBJ_test		*	pObj	=	NULL;	

	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->var.pObj  )  return  -1;


	VIDEO_COMPRESSOR_cfgCommon	*	pCompressor	=	(  VIDEO_COMPRESSOR_cfgCommon  *  )pVideoCompressorCfg_reserved;

	//
	memcpy(  &pQdcObjInfo->cfg.v,  pCompressor,  sizeof(  pQdcObjInfo->cfg.v  )  );


	//memset(  &qdcObjInfo,  0,  sizeof(  qdcObjInfo  )  );
	pObj  =  (  QDC_OBJ_test  *  )malloc(  sizeof(  QDC_OBJ_test  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	pQdcObjInfo->var.pObj  =  pObj;


		//
	pQdcObjInfo->var.ucbTransformFuncsOk  =  TRUE;	//  bTransformFuncsOk(  pQdcObjInfo  );
	if  (  !pQdcObjInfo->var.ucbTransformFuncsOk  )  {
		#ifdef  _DEBUG
				OutputDebugString(  _T(  "initDecV failed, bTransformFuncs false\n"  )  );
		#endif
		goto  errLabel;
	}



	//  qdcObjInfo.
	pQdcObjInfo->var.cbOutputBuffer  =  pVh_decompress->bih.biSizeImage;
	pQdcObjInfo->var.cbInputBuffer  =  pQdcObjInfo->var.cbOutputBuffer;

	//
	makeBmpInfoHeader_i420(  12,  pVh_decompress->bih.biWidth,  pVh_decompress->bih.biHeight,  &pVh_decompress->bih  );

	//
	memcpy(  pVh_compress,  pVh_decompress,  sizeof(  pVh_compress[0]  )  );
	pVh_compress->bih.biCompression  =  CONST_fourcc_vp80;


	//
	pObj->bsWriter.m_pQdcObjInfoParam  =  pQdcObjInfo;	
	pObj->bsWriter.size_pPkt  =  pQdcObjInfo->cfg.v.size_pCurPkt;
	if  (  pObj->bsWriter.pPkt  )  {
		//tmp_showInfo(  _T(  "encPipeline::InitWriter failed, fileWriter.pPkt is not null"  )  );
		goto  errLabel;
	}
	pObj->bsWriter.pPkt  =  malloc(  pObj->bsWriter.size_pPkt  );
	if  (  !pObj->bsWriter.pPkt  )  {
		//tmp_showInfo(  _T(  "encPipeline::InitWriter failed, fileWriter.pPkt malloc failed"  )  );
		goto  errLabel;
	}


	//
#if  0
	if  (  !pObj->outs[0].pBuf  )  {
		pObj->outs[0].pBuf  =  (  BYTE  *  )malloc(  pQdcObjInfo->cbOutputBuffer  );
		if  (  !pObj->outs[0].pBuf  )  goto  errLabel;
	}
#endif

#ifdef  _DEBUG
		#if  0
			OutputDebugString(  _T(  "²âÊÔ, err\n"  )  );
			goto  errLabel;
		#endif
#endif

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		qdcExitCompressVideo(  pQdcObjInfo  );
	}
	if  (  !iErr  )  {
		//  memcpy(  pQdcObjInfo,  &qdcObjInfo,  sizeof(  pQdcObjInfo[0]  )  );
	}
	return  iErr;
}

extern  "C"  int  __declspec(  dllexport  )qdcExitCompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	QDC_OBJ_test	*	pObj	=	(  QDC_OBJ_test  *  )pQdcObjInfo->var.pObj;

	if  (  pObj  )  {
		//
		qdcFreeOutputs(  pQdcObjInfo  );
		
		//  2014/07/21
		if  (  pObj->bsWriter.pPkt  )  {		
			free(  pObj->bsWriter.pPkt  );  pObj->bsWriter.pPkt  =  NULL;	
		}

		//
		free(  pObj  );	
	}
	pQdcObjInfo->var.pObj  =  NULL;

	return  0;
}

extern  "C"  __declspec(  dllexport  )  int  qdcGetSpsPps(  QDC_OBJ_INFO  *  pQdcObjInfo,  char  *  spsBuf,  unsigned  int  *  puiSpsSize,  char  *  ppsBuf,  unsigned  int  *  puiPpsSize,  char  *  kk,  unsigned  int  *  puiKkSize  )
{
	if  (  !spsBuf  ||  !puiSpsSize  ||  !ppsBuf  ||  !puiPpsSize  )  return  -1;

	if  (  *puiSpsSize  )  {
		spsBuf[0]  =  0;
		*puiSpsSize  =  0;
	}
	if  (  *puiPpsSize  )  {
		ppsBuf[0]  =  0;
		*puiPpsSize  =  0;
	}

	return  0;
}

extern  "C"  int  __declspec(  dllexport  )qdcCompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs  )
{
	QDC_OBJ_test	*	pObj	=	(  QDC_OBJ_test  *  )pQdcObjInfo->var.pObj;

	//
	if  (  g_pGuiOpen  )  {
		g_pGuiOpen->pf_showInfo(  0,  0,  _T(  "qdcCompressVideo called"  )  );
	}


	//
	if  (  pBmpInfo_input->bmiHeader.biSizeImage  >  pQdcObjInfo->var.cbInputBuffer  )  return  -1;

	int  index  =  0;
	memcpy(  pObj->outs[index].pBuf,  pInput,  pBmpInfo_input->bmiHeader.biSizeImage  );
	pObj->outs[index].len  =  pBmpInfo_input->bmiHeader.biSizeImage;

	return  0;
}


typedef  struct  {
				QDC_OBJ_test  *  pObj;
				//CMySmplYUVReader  *  p;
				//mfxFrameSurface1			*	pSurface;
}		 PARAM_CMySmplYUVReader_myLoadNextFrame;

int  CMySmplYUVReader_myLoadNextFrame(  char  *  pInput,  unsigned  int  uiInputSize,  PARAM_CMySmplYUVReader_myLoadNextFrame  *  pParam  )
{
	int  iErr  =  -1;

	QDC_OBJ_test  *  pObj  =  pParam->pObj;
	if  (  uiInputSize  >  pObj->outs[0].size  ||  !pObj->outs[0].pBuf  )  {
		if  (  pObj->outs[0].pBuf  )  {
			free(  pObj->outs[0].pBuf  );  pObj->outs[0].pBuf  =  NULL;
		}
		pObj->outs[0].size  =  uiInputSize;
		pObj->outs[0].pBuf  =  (  unsigned  char  *  )malloc(  pObj->outs[0].size  );
		if  (  !pObj->outs[0].pBuf  )  goto  errLabel;
	}
	pObj->outs[0].len  =  0;
	memcpy(  pObj->outs[0].pBuf,  pInput,  uiInputSize  );
	pObj->outs[0].len  =  uiInputSize;

	//return  pParam->p->myLoadNextFrame(  (  BYTE  *  )pInput,  uiInputSize,  pParam->pSurface  );
	
	iErr  =  0;
errLabel:

	return  iErr;
}


extern  "C"  int  __declspec(  dllexport  )  qdcCompressVideoRun(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int  iErr  =  -1;
	QDC_OBJ_test	*	pObj	=	(  QDC_OBJ_test  *  )pQdcObjInfo->var.pObj;

	if  (  pObj->status.bDone_run  )  {
		tmp_showInfo(  _T(  "qdcCompressVideoRun failed: bDone_run is true"  )  );
		return  -1;
	}


	try  {

	for  (  ;  ;  )  {
	
		 PARAM_CMySmplYUVReader_myLoadNextFrame  param;
		 memset(  &param,  0,  sizeof(  param  )  );
		 param.pObj  =  pObj;
		 //param.p  =  this;
		 //param.pSurface  =  pSurface;
		 if  (  pQdcObjInfo->cfg.v.enc.pf_smplYUVReader_LoadNextFrame(  pQdcObjInfo,  &pObj->old_lPktId,  (  PF_myLoadNextFrame  )CMySmplYUVReader_myLoadNextFrame,  &param,  &pQdcObjInfo->var.encInfo.bNeed_forceKeyFrame  )  )  {
			 goto  errLabel;
		 }
		 //
		 {	 
			 char  *  pInput  =  (  char  *  )(  pObj->outs[0].pBuf  );
			 int  inputSize  =  pObj->outs[0].len;
			 int  iSampleTimeInMs  =  0;					 
			 pQdcObjInfo->cfg.v.enc.pf_doPostEnc(  pQdcObjInfo,  pInput,  inputSize,  iSampleTimeInMs,  pObj->bsWriter.pPkt  );		  

		 }

		}
		}
	catch  (  ...  )  {
			tmp_showInfo(  _T(  "qdcCompressVideoRun failed: exception"  )  );
			goto  errLabel;
	}

	iErr  =  0;
errLabel:

	//if  (  pObj->
	pObj->status.bDone_run  =  TRUE;

	return  iErr;
}



