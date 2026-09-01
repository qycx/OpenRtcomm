

#include	"stdafx.h"
#include	<tchar.h>
#include	<stdlib.h>
#include	<Dshow.h>

#include	<mmreg.h>

#include	"qisCompressProc_encA.h"




 
extern  "C"  int  __declspec(  dllexport  )qdcInitCompressAudio(  void  *  pAudioCompressorCfg_reserved,  QY_AUDIO_HEADER  *  pAh_decompress,  QY_AUDIO_HEADER  *  pAh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int						iErr	=	-1;
	//QDC_OBJ_INFO			qdcObjInfo;
	QDC_OBJ_test_encA		*	pObj	=	NULL;	

	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->var.pObj  )  return  -1;

#if  10
	//
	AUDIO_COMPRESSOR_cfgCommon	*	pCompressor	=	(  AUDIO_COMPRESSOR_cfgCommon  *  )pAudioCompressorCfg_reserved;

	//
	memcpy(  &pQdcObjInfo->cfg.a,  pCompressor,  sizeof(  pQdcObjInfo->cfg.a  )  );
	
	//
	//memset(  &qdcObjInfo,  0,  sizeof(  qdcObjInfo  )  );
	pObj  =  (  QDC_OBJ_test_encA  *  )malloc(  sizeof(  QDC_OBJ_test_encA  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	pObj->common.uiType  =  CONST_qdcObjType_encA;
	//
	pQdcObjInfo->var.pObj  =  pObj;

	//
	//
	pQdcObjInfo->var.ucbTransformFuncsOk  =  TRUE;	//  bTransformFuncsOk(  pQdcObjInfo  );
	if  (  !pQdcObjInfo->var.ucbTransformFuncsOk  )  {
		#ifdef  _DEBUG
				OutputDebugString(  _T(  "initDecV failed, bTransformFuncs false\n"  )  );
		#endif
		goto  errLabel;
	}


	//  qdcObjInfo.
	pQdcObjInfo->var.cbInputBuffer  =  pAh_decompress->wfx.nAvgBytesPerSec  *  2;
	pQdcObjInfo->var.cbOutputBuffer  =  pQdcObjInfo->var.cbInputBuffer;

	//  2016/12/06
	memcpy(  pAh_compress,  pAh_decompress,  sizeof(  pAh_compress[0]  )  );
	pAh_compress->wfx.wFormatTag  =  CONST_fourcc_vorbis;
	
	//
	pObj->bsWriter.m_pQdcObjInfoParam  =  pQdcObjInfo;	
	pObj->bsWriter.size_pPkt  =  pQdcObjInfo->cfg.a.size_pCurPkt;
	if  (  pObj->bsWriter.pPkt  )  {
		//tmp_showInfo(  _T(  "encPipeline::InitWriter failed, fileWriter.pPkt is not null"  )  );
		goto  errLabel;
	}
	pObj->bsWriter.pPkt  =  malloc(  pObj->bsWriter.size_pPkt  );
	if  (  !pObj->bsWriter.pPkt  )  {
		//tmp_showInfo(  _T(  "encPipeline::InitWriter failed, fileWriter.pPkt malloc failed"  )  );
		goto  errLabel;
	}

#endif
	//	
#if  0
	if  (  !pObj->outs[0].pBuf  )  {
		pObj->outs[0].pBuf  =  (  BYTE  *  )malloc(  qdcObjInfo.var.cbOutputBuffer  );
		if  (  !pObj->outs[0].pBuf  )  goto  errLabel;
	}
#endif

	//  2016/12/17
	if  (  !pQdcObjInfo->pf_qoi_bSetPtrProperty  )  goto  errLabel;
	if  (  !pQdcObjInfo->pf_qoi_bSetPtrProperty(  pQdcObjInfo,  CONST_qdcPropId_PF_qdcGetVorbisHeaders,  qdcGetVorbisHeaders  )  )  {
		goto  errLabel;
	}



	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		qdcExitCompressAudio(  pQdcObjInfo  );
	}
	if  (  !iErr  )  {
		//memcpy(  pQdcObjInfo,  &qdcObjInfo,  sizeof(  pQdcObjInfo[0]  )  );
	}
	return  iErr;
}

extern  "C"  int  __declspec(  dllexport  )qdcExitCompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	QDC_OBJ_test_encA	*	pObj  =  (  QDC_OBJ_test_encA  *  )pQdcObjInfo->var.pObj;

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



//  2016/12/17
extern  "C"  int  qdcGetVorbisHeaders(  QDC_OBJ_INFO  *  pQdcObjInfo,  char  *  pBuf_header0,  unsigned  int  *  puiBufSize_header0,  char  *  pBuf_header1,  unsigned  int  *  puiBufSize_header1,  char  *  pBuf_header2,  unsigned  int  *  puiBufSize_header2  )
{
	int  iErr  =  -1;

	*puiBufSize_header0  =  0;
	*puiBufSize_header1  =  0;
	*puiBufSize_header2  =  0;


	iErr  =  0;
	return  iErr;
}


//
extern  "C"  int  __declspec(  dllexport  )qdcCompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_decompress,  BYTE  *  pInput,  unsigned  int  uiInputSize,  int  iSampleTimeInMs  )
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
typedef  struct  {
				QDC_OBJ_test_encA  *  pObj;
				//CMySmplYUVReader  *  p;
				//mfxFrameSurface1			*	pSurface;
}		 PARAM_CMySmplPCMReader_myLoadNextFrame;

//
int  CMySmplPCMReader_myLoadNextFrame(  unsigned  short  usPktResType,  char  *  pInput,  unsigned  int  uiInputSize,  PARAM_CMySmplPCMReader_myLoadNextFrame  *  pParam  )
{
	int  iErr  =  -1;

	QDC_OBJ_test  *  pObj  =  &pParam->pObj->common;
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



//  2016/12/05
extern  "C"  int  __declspec(  dllexport  )  qdcCompressAudioRun(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int					iErr	=	-1;
	QDC_OBJ_test_encA	*	pObj	=	(  QDC_OBJ_test_encA  *  )pQdcObjInfo->var.pObj;
	TCHAR				tBuf[256]	=	_T(  ""  );

	//
	if  (  pObj->status.bDone_run  )  {
		tmp_showInfo(  _T(  "qdcCompressVideoRun failed: bDone_run is true"  )  );
		return  -1;
	}


	try  {

	for  (  ;  ;  )  {
	
		 PARAM_CMySmplPCMReader_myLoadNextFrame  param;
		 memset(  &param,  0,  sizeof(  param  )  );
		 param.pObj  =  pObj;
		 //param.p  =  this;
		 //param.pSurface  =  pSurface;
		 if  (  pQdcObjInfo->cfg.a.enc.pf_smplPCMReader_LoadNextFrame(  pQdcObjInfo,  &pObj->old_lPktId,  (  PF_myLoadNextFrame  )CMySmplPCMReader_myLoadNextFrame,  &param,  &pQdcObjInfo->var.encInfo.bNeed_forceKeyFrame  )  )  {
			 goto  errLabel;
		 }
		 //
		 {	 
			 char  *  pInput  =  (  char  *  )(  pObj->common.outs[0].pBuf  );
			 int  inputSize  =  pObj->common.outs[0].len;
			 int  iSampleTimeInMs  =  0;					 
			 //
			 unsigned  int  uiPts  =  0;  //  2016/12/09
			 //
			 pQdcObjInfo->cfg.a.enc.pf_doPostEnc(  pQdcObjInfo,  pInput,  inputSize,  iSampleTimeInMs,  uiPts,  pObj->bsWriter.pPkt  );		  

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


