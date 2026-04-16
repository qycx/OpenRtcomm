


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
	memcpy(  pVh_compress,  pVh_decompress,  sizeof(  pVh_compress[0]  )  );

	//	
	if  (  !pObj->outs[0].pBuf  )  {
		pObj->outs[0].pBuf  =  (  BYTE  *  )malloc(  pQdcObjInfo->cbOutputBuffer  );
		if  (  !pObj->outs[0].pBuf  )  goto  errLabel;
	}

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
	QDC_OBJ_test	*	pObj	=	(  QDC_OBJ_test  *  )pQdcObjInfo->pObj;

	//
	if  (  g_pGuiOpen  )  {
		g_pGuiOpen->pf_showInfo(  0,  0,  _T(  "qdcCompressVideo called"  )  );
	}


	//
	if  (  pBmpInfo_input->bmiHeader.biSizeImage  >  pQdcObjInfo->cbInputBuffer  )  return  -1;

	int  index  =  0;
	memcpy(  pObj->outs[index].pBuf,  pInput,  pBmpInfo_input->bmiHeader.biSizeImage  );
	pObj->outs[index].len  =  pBmpInfo_input->bmiHeader.biSizeImage;

	return  0;
}


extern  "C"  int  __declspec(  dllexport  )  qdcCompressVideoRun(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	return  -1;
}



