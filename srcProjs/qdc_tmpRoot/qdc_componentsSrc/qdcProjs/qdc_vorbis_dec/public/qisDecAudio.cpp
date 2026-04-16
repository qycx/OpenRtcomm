

#include	"stdafx.h"
#include	<tchar.h>
#include	<stdlib.h>
#include	<Dshow.h>

#include	<mmreg.h>

#include	"qisCompressProc_decA.h"




//
extern  "C"  int  __declspec(  dllexport  )qdcInitDecompressAudio(  void  *  pAudioCompressorCfg,  QY_AUDIO_HEADER  *  pAh_compress,  QY_AUDIO_HEADER  *  pAh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{	
	int						iErr	=	-1;
	//QDC_OBJ_INFO			qdcObjInfo;
	QDC_OBJ_test_decA	*	pObj	=	NULL;	

	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->var.pObj  )  return  -1;

	//
	AUDIO_COMPRESSOR_cfgCommon	*	pCompressor	=	(  AUDIO_COMPRESSOR_cfgCommon  *  )pAudioCompressorCfg;

	//
	memcpy(  &pQdcObjInfo->cfg.a,  pCompressor,  sizeof(  pQdcObjInfo->cfg.a  )  );

	//
	pQdcObjInfo->var.ucbTransformFuncsOk  =  TRUE;



	//memset(  &qdcObjInfo,  0,  sizeof(  qdcObjInfo  )  );
	pObj  =  (  QDC_OBJ_test_decA  *  )malloc(  sizeof(  QDC_OBJ_test_decA  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	pObj->common.uiType  =  CONST_qdcObjType_decA;
	//
	//
	pQdcObjInfo->var.pObj  =  pObj;

	//  qdcObjInfo.
	pQdcObjInfo->var.cbOutputBuffer  =  pAh_decompress->wfx.nAvgBytesPerSec  *  2;
	pQdcObjInfo->var.cbInputBuffer  =  pQdcObjInfo->var.cbOutputBuffer;

	//
	memcpy(  pAh_compress,  pAh_decompress,  sizeof(  pAh_compress[0]  )  );

	//	
	pObj->common.outs[0].size  =  pQdcObjInfo->var.cbOutputBuffer;
	if  (  !pObj->common.outs[0].pBuf  )  {
		pObj->common.outs[0].pBuf  =  (  BYTE  *  )malloc(  pQdcObjInfo->var.cbOutputBuffer  );
		if  (  !pObj->common.outs[0].pBuf  )  goto  errLabel;
	}

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		qdcExitDecompressAudio(  pQdcObjInfo  );
	}
	if  (  !iErr  )  {
		//memcpy(  pQdcObjInfo,  &qdcObjInfo,  sizeof(  pQdcObjInfo[0]  )  );
	}
	return  iErr;
}

extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	QDC_OBJ_test_decA	*	pObj  =  (  QDC_OBJ_test_decA  *  )pQdcObjInfo->var.pObj;

	if  (  pObj  )  {
		//
		qdcFreeOutputs(  pQdcObjInfo  );
		//
		free(  pObj  );	
	}
	pQdcObjInfo->var.pObj  =  NULL;

	return  0;
}

extern  "C"  int  __declspec(  dllexport  )qdcDecompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_compress,  BYTE  *  pInput,  unsigned  int  uiInputSize,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  )
{	
	QDC_OBJ_test	*	pObj	=	(  QDC_OBJ_test  *  )pQdcObjInfo->var.pObj;

	if  (  uiInputSize  >  pQdcObjInfo->var.cbInputBuffer  )  return  -1;

	int  index  =  0;
	memcpy(  pObj->outs[index].pBuf,  pInput,  uiInputSize  );
	pObj->outs[index].len  =  uiInputSize;
	pObj->outs[index].rtStart  =  iSampleTimeInMs  *  1000  *  10;

	return  0;
}



//
 int  my_data_to_pcm(  void  *  pQdcObjInfoParam,  void  *  pData,  void  *  pYUVWriter_var  )
 {
	 QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )pQdcObjInfoParam;

	 if  (  !pYUVWriter_var  )  return  -1;
	 YUVWriter_var  &  m_var  =  *(  YUVWriter_var  *  )pYUVWriter_var;

	 
	 //
	 QDC_OBJ_test	*	pObj	=	(  QDC_OBJ_test  *  )pQdcObjInfo->var.pObj;

	 if  (  pObj->outs[0].len  >  m_var.outputInfo.uiOutputSize  )  return  -1;
	 memcpy(  m_var.outputInfo.pBuf,  pObj->outs[0].pBuf,  pObj->outs[0].len  );
	 m_var.outputInfo.len  =  pObj->outs[0].len;

	 return  0;
 }


//  2016/12/05
extern  "C"  int  __declspec(  dllexport  )  qdcDecompressAudioRun(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int					iErr	=	-1;
	
	QDC_OBJ_test_decA	*	pObj	=	(  QDC_OBJ_test_decA  *  )pQdcObjInfo->var.pObj;

	if  (  pObj->common.status.bDone_run  )  {
		tmp_showInfo(  _T(  "qdcDecompressVideoRun failed: bDone_run is true"  )  );
		return  -1;
	}



#if  10

	pObj->yuvWriter.m_var.pQdcObjInfoParam  =  pQdcObjInfo;
	//
	pObj->yuvWriter.m_var.size_pPkt  =  pQdcObjInfo->cfg.a.size_pCurPkt;
	if  (  pObj->yuvWriter.m_var.pPkt  )  {
		tmp_showInfo(  _T(  "decPipeline::myRun failed, fileWriter.pPkt is not null"  )  );
		goto  errLabel;
	}
	pObj->yuvWriter.m_var.pPkt  =  malloc(  pObj->yuvWriter.m_var.size_pPkt  );
	if  (  !pObj->yuvWriter.m_var.pPkt  )  {
		tmp_showInfo(  _T(  "decPipeline::myRun failed, fileWriter.pPkt malloc failed"  )  );
		goto  errLabel;
	}
	memset(  pObj->yuvWriter.m_var.pPkt,  0,  pObj->yuvWriter.m_var.size_pPkt  );
#endif


#if  10
		try  {

	for  (  ;  ;  )  {
		 //
		unsigned  int  nBytesRead  =  pObj->common.outs[0].size;
		unsigned  int  uiSampleTimeInMs  =  0;
		if  (  pQdcObjInfo->cfg.a.dec.pf_smplBitstreamReader_ReadNextFrame_func(  pQdcObjInfo,  &pObj->old_lPktId,  0,  (  char  *  )(  pObj->common.outs[0].pBuf  ),  &nBytesRead,  &uiSampleTimeInMs  )  )  {		
			goto  errLabel;	 
		}
		pObj->common.outs[0].len  =  nBytesRead;    

		//
#if  10
		int  iFourcc  =  CONST_fourcc_I420;
		int  CropW  =  0;
		//CropW  =  pObj->iWidth;
		int  CropH  =  0;
		//  CropH  =  pObj->iHeight;
		int	Pitch  =  0;

		double  dFrameRate  =  0;
#endif

		//
		if  (  pQdcObjInfo->cfg.a.dec.pf_smplPCMWriter_WriteNextFrame_all(  pQdcObjInfo,  &pObj->common,  iFourcc,  &pObj->yuvWriter.m_var,  0,  my_data_to_pcm,  dFrameRate,  _T( ""  )  )  )  goto  errLabel;
	

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
		//  2016/12/13
		pQdcObjInfo->cfg.a.pf_clean_myPLAY_AUDIO_DATA(  pObj->yuvWriter.m_var.pPkt,  _T(  ""  )  );
		//
		free(  pObj->yuvWriter.m_var.pPkt  );  pObj->yuvWriter.m_var.pPkt  =  NULL;
	}
	
	//if  (  pObj->
	pObj->common.status.bDone_run  =  TRUE;

	return  iErr;


}




