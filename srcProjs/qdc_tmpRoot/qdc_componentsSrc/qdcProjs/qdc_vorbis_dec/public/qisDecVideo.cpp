


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
	if  (  pQdcObjInfo->pObj  )  return  -1;


	VIDEO_COMPRESSOR_cfgCommon	*	pCompressor	=	(  VIDEO_COMPRESSOR_cfgCommon  *  )pVideoCompressorCfg_reserved;

	//
	memcpy(  &pQdcObjInfo->cfg,  pCompressor,  sizeof(  pQdcObjInfo->cfg  )  );


	//memset(  &qdcObjInfo,  0,  sizeof(  qdcObjInfo  )  );
	pObj  =  (  QDC_OBJ_test  *  )malloc(  sizeof(  QDC_OBJ_test  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	pQdcObjInfo->pObj  =  pObj;

	//  qdcObjInfo.
	pQdcObjInfo->cbOutputBuffer  =  pVh_decompress->bih.biSizeImage;
	pQdcObjInfo->cbInputBuffer  =  pQdcObjInfo->cbOutputBuffer;

	//

	//	
	if  (  !pObj->outs[0].pBuf  )  {
		pObj->outs[0].pBuf  =  (  BYTE  *  )malloc(  pQdcObjInfo->cbOutputBuffer  );
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
	QDC_OBJ_test	*	pObj	=	(  QDC_OBJ_test  *  )pQdcObjInfo->pObj;

	if  (  pObj  )  {
		//
		qdcFreeOutputs(  pQdcObjInfo  );
		//
		free(  pObj  );	
	}
	pQdcObjInfo->pObj  =  NULL;

	return  0;
}

extern  "C"  int  __declspec(  dllexport  )qdcDecompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs  )
{
	QDC_OBJ_test	*	pObj	=	(  QDC_OBJ_test  *  )pQdcObjInfo->pObj;

	if  (  pBmpInfo_input->bmiHeader.biSizeImage  >  pQdcObjInfo->cbInputBuffer  )  return  -1;

	int  index  =  0;
	memcpy(  pObj->outs[index].pBuf,  pInput,  pBmpInfo_input->bmiHeader.biSizeImage  );
	pObj->outs[index].len  =  pBmpInfo_input->bmiHeader.biSizeImage;

	return  0;
}

extern  "C"  int  __declspec(  dllexport  )qdcDecompressVideoAndOutput(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  BITMAPINFO  *  pBmpInfo_output,  BYTE  *  pOutput  )
{
	QDC_OBJ_test	*	pObj	=	(  QDC_OBJ_test  *  )pQdcObjInfo->pObj;

	if  (  !pOutput  )  return  -1;

	if  (  pBmpInfo_input->bmiHeader.biSizeImage  >  pQdcObjInfo->cbInputBuffer  )  return  -1;

	int  outputLen  =  pBmpInfo_input->bmiHeader.biSizeImage;
	if  (  outputLen  >  pBmpInfo_output->bmiHeader.biSizeImage  )  return  -1;

	//  int  index  =  0;
	memcpy(  pOutput,  pInput,  outputLen  );
	pBmpInfo_output->bmiHeader.biSizeImage  =  outputLen;

	return  0;

}


extern  "C"  int  __declspec(  dllexport  )  qdcDecompressVideoRun(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	return  -1;
}



