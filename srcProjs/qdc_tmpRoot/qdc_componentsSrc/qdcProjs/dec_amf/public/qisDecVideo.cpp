


#include	"stdafx.h"
#include	<tchar.h>
#include	<stdlib.h>
#include	<Dshow.h>

#include	<mmreg.h>

#include	"qisCompressProc.h"

extern  "C"  int  __declspec(  dllexport  )qdcInitDecompressVideo(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_compress,  QY_VIDEO_HEADER  *  pVh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{	
	int						iErr	=	-1;
	//QDC_OBJ_INFO			qdcObjInfo;
	QDC_OBJ_test		*	pObj	=	NULL;	

	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->var.pObj  )  return  -1;


	VIDEO_COMPRESSOR_cfgCommon	*	pCompressor	=	(  VIDEO_COMPRESSOR_cfgCommon  *  )pVideoCompressorCfg_reserved;

	//
	memcpy(  &pQdcObjInfo->cfg.v,  pCompressor,  sizeof(  pQdcObjInfo->cfg.v  )  );

	//
	pQdcObjInfo->var.ucbTransformFuncsOk  =  TRUE;


	//memset(  &qdcObjInfo,  0,  sizeof(  qdcObjInfo  )  );
	pObj  =  (  QDC_OBJ_test  *  )malloc(  sizeof(  QDC_OBJ_test  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	pQdcObjInfo->var.pObj  =  pObj;

	//  qdcObjInfo.
	pQdcObjInfo->var.cbOutputBuffer  =  pVh_decompress->bih.biSizeImage;
	pQdcObjInfo->var.cbInputBuffer  =  pQdcObjInfo->var.cbOutputBuffer;

	//
	pObj->iWidth  =  pVh_compress->bih.biWidth;
	pObj->iHeight  =  pVh_compress->bih.biHeight;

	//	
	pObj->outs[0].size  =  pQdcObjInfo->var.cbOutputBuffer;
	if  (  !pObj->outs[0].pBuf  )  {
		pObj->outs[0].pBuf  =  (  BYTE  *  )malloc(  pObj->outs[0].size  );
		if  (  !pObj->outs[0].pBuf  )  goto  errLabel;
	}

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		qdcExitDecompressVideo(  pQdcObjInfo  );
	}
	if  (  !iErr  )  {
		//memcpy(  pQdcObjInfo,  &qdcObjInfo,  sizeof(  pQdcObjInfo[0]  )  );
	}
	return  iErr;
}

extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	QDC_OBJ_test	*	pObj	=	(  QDC_OBJ_test  *  )pQdcObjInfo->var.pObj;

	if  (  pObj  )  {
		//
		qdcFreeOutputs(  pQdcObjInfo  );
		//
		free(  pObj  );	
	}
	pQdcObjInfo->var.pObj  =  NULL;

	return  0;
}

extern  "C"  int  __declspec(  dllexport  )qdcDecompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs  )
{
	QDC_OBJ_test	*	pObj	=	(  QDC_OBJ_test  *  )pQdcObjInfo->var.pObj;

	if  (  pBmpInfo_input->bmiHeader.biSizeImage  >  pQdcObjInfo->var.cbInputBuffer  )  return  -1;

	int  index  =  0;
	memcpy(  pObj->outs[index].pBuf,  pInput,  pBmpInfo_input->bmiHeader.biSizeImage  );
	pObj->outs[index].len  =  pBmpInfo_input->bmiHeader.biSizeImage;

	return  0;
}

extern  "C"  int  __declspec(  dllexport  )qdcDecompressVideoAndOutput(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  BITMAPINFO  *  pBmpInfo_output,  BYTE  *  pOutput  )
{
	QDC_OBJ_test	*	pObj	=	(  QDC_OBJ_test  *  )pQdcObjInfo->var.pObj;

	if  (  !pOutput  )  return  -1;

	if  (  pBmpInfo_input->bmiHeader.biSizeImage  >  pQdcObjInfo->var.cbInputBuffer  )  return  -1;

	int  outputLen  =  pBmpInfo_input->bmiHeader.biSizeImage;
	if  (  outputLen  >  pBmpInfo_output->bmiHeader.biSizeImage  )  return  -1;

	//  int  index  =  0;
	memcpy(  pOutput,  pInput,  outputLen  );
	pBmpInfo_output->bmiHeader.biSizeImage  =  outputLen;

	return  0;

}

 int  my_surface_to_yuv(  void  *  pQdcObjInfoParam,  void  *  pSurfaceParam,  unsigned  int  cropW,  unsigned  int  cropH,  unsigned  int  pitch,  unsigned  int  imgW,  unsigned  int  imgH,  void  *  pYUVWriter_var  )
 {
	 QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )pQdcObjInfoParam;

	 if  (  !pYUVWriter_var  )  return  -1;
	 YUVWriter_var  &  m_var  =  *(  YUVWriter_var  *  )pYUVWriter_var;

	 BYTE  *  yuv  =  m_var.outputInfo.pBuf;
	 
	 //
	 QDC_OBJ_test	*	pObj	=	(  QDC_OBJ_test  *  )pQdcObjInfo->var.pObj;

	 if  (  pObj->outs[0].len  >  m_var.outputInfo.uiOutputSize  )  return  -1;
	 memcpy(  yuv,  pObj->outs[0].pBuf,  pObj->outs[0].len  );

	 return  0;
 }
extern  "C"  int  __declspec(  dllexport  )  qdcDecompressVideoRun(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
		int  iErr  =  -1;
	QDC_OBJ_test	*	pObj	=	(  QDC_OBJ_test  *  )pQdcObjInfo->var.pObj;

	if  (  pObj->status.bDone_run  )  {
		tmp_showInfo(  _T(  "qdcDecompressVideoRun failed: bDone_run is true"  )  );
		return  -1;
	}



#if  10

	pObj->yuvWriter.m_var.pQdcObjInfoParam  =  pQdcObjInfo;
	//
	pObj->yuvWriter.m_var.size_pPkt  =  pQdcObjInfo->cfg.v.size_pCurPkt;
	if  (  pObj->yuvWriter.m_var.pPkt  )  {
		tmp_showInfo(  _T(  "decPipeline::myRun failed, fileWriter.pPkt is not null"  )  );
		goto  errLabel;
	}
	pObj->yuvWriter.m_var.pPkt  =  malloc(  pObj->yuvWriter.m_var.size_pPkt  );
	if  (  !pObj->yuvWriter.m_var.pPkt  )  {
		tmp_showInfo(  _T(  "decPipeline::myRun failed, fileWriter.pPkt malloc failed"  )  );
		goto  errLabel;
	}
#endif


#if  10
		try  {

	for  (  ;  ;  )  {
		 //
		unsigned  int  nBytesRead  =  pObj->outs[0].size;
		unsigned  int  uiSampleTimeInMs  =  0;
		if  (  pQdcObjInfo->cfg.v.dec.pf_smplBitstreamReader_ReadNextFrame_func(  pQdcObjInfo,  &pObj->input.old_lPktId,  0,  (  char  *  )(  pObj->outs[0].pBuf  ),  &nBytesRead,  &uiSampleTimeInMs  )  )  {		
			goto  errLabel;	 
		}
		pObj->outs[0].len  =  nBytesRead;    

		//
		int  iFourcc  =  CONST_fourcc_I420;
		int  CropW  =  pObj->iWidth;
		int  CropH  =  pObj->iHeight;
		int	Pitch  =  0;

		double  dFrameRate  =  0;


		//
		if  (  pQdcObjInfo->cfg.v.dec.pf_smplYUVWriter_WriteNextFrame(  pQdcObjInfo,  &pObj->common,  iFourcc,  &pObj->yuvWriter.m_var,  0,  CropW,  CropH,  0,  my_surface_to_yuv,  dFrameRate,  _T(  ""  )  )  )  goto  errLabel;
	

		}
		}
	catch  (  ...  )  {
			tmp_showInfo(  _T(  "qdcCompressVideoRun failed: exception"  )  );
			goto  errLabel;
	}
#endif




	iErr  =  0;
errLabel:

	//  2014/08/05
	if  (  pObj->yuvWriter.m_var.pPkt  )  {
		free(  pObj->yuvWriter.m_var.pPkt  );  pObj->yuvWriter.m_var.pPkt  =  NULL;
	}
	
	//if  (  pObj->
	pObj->status.bDone_run  =  TRUE;

	return  iErr;

}



