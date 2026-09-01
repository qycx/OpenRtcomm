// qisCompress.cpp : Defines the exported functions for the DLL application.
//

#include	"stdafx.h"
#include	<tchar.h>
#include	<stdlib.h>
#include	<Dshow.h>

#include	<mmreg.h>

#include	"qisCompressProc.h"
#include	"tmpGuiOpenFunc.h"

#define		CONST_ver_vorbis			"02650117"	//  2016/12/16

//QIS_guiOpen  *  g_pGuiOpen	=	NULL;

int  yuy2ToRgb24(  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height  )
{
	OutputDebugString(  _T(  "Not finished, yuy2ToRgb24\n"  )  );
	return  -1;
}



 extern  "C"  __declspec(  dllexport  )  int  qdcInit(  QDC_MGR  *  p  )
{
	//
	OutputDebugString(  _T(  "qdcInit\n"  )  );

	//
	g_pGuiOpen  =  p->pGuiOpen;

	//
	p->iCompressorId  =  1;
	_tcsncpy(  p->name,  _T(  "test"  ),  sizeof(  p->name  )  /  sizeof(  p->name[0]  )  );

	//  p->pf_yuy2ToRgb24  =  yuy2ToRgb24;

#ifdef  _DEBUG
		//  p->ucbNotSupported  =  TRUE;
#endif
	//  2016/12/16
	strncpy(  p->ver,  CONST_ver_vorbis,  mycountof(  p->ver  )  );  

	return  0;
}


 extern  "C"  int  __declspec(  dllexport  )qdcExit(  QDC_MGR  *  p  )
{

	OutputDebugString(  _T(  "qdcExit\n"  )  );

	return  0;
}


 extern  "C"  int  __declspec(  dllexport  )qdcGetCompressAudioCfg(  WAVEFORMATEX  *  pWf_decompress,  WAVEFORMATEX  *  pWf_compress  )
{
	memset(  pWf_decompress,  0,  sizeof(  pWf_decompress[0]  )  );
	memset(  pWf_compress,  0,  sizeof(  pWf_compress[0]  )  );

#if  0
	pWf_compress->wFormatTag			=	WAVE_FORMAT_PCM;
	pWf_compress->nChannels				=	1;
	pWf_compress->wBitsPerSample		=	16;
	pWf_compress->cbSize				=	0;
	pWf_compress->nSamplesPerSec		=	8000;

	pWf_compress->nBlockAlign		=	(  pWf_compress->wBitsPerSample  /  8  )  *  pWf_compress->nChannels;
	pWf_compress->nAvgBytesPerSec	=	pWf_compress->nSamplesPerSec  *  pWf_compress->nBlockAlign;

	memcpy(  pWf_decompress,  pWf_compress,  sizeof(  pWf_decompress[0]  )  );

#else
	pWf_compress->wFormatTag			=	CONST_fourcc_vorbis;	//  2016/12/05	//  WAVE_FORMAT_MPEGLAYER3;
	pWf_compress->nChannels				=	2;
	pWf_compress->wBitsPerSample		=	16;
	pWf_compress->cbSize				=	0;
	pWf_compress->nSamplesPerSec		=	44100;

	//
	pWf_decompress->wFormatTag			=	WAVE_FORMAT_PCM;
	pWf_decompress->nChannels				=	2;
	pWf_decompress->wBitsPerSample		=	16;
	pWf_decompress->cbSize				=	0;
	pWf_decompress->nSamplesPerSec		=	44100;

	pWf_decompress->nBlockAlign		=	(  pWf_decompress->wBitsPerSample  /  8  )  *  pWf_decompress->nChannels;
	pWf_decompress->nAvgBytesPerSec	=	pWf_decompress->nSamplesPerSec  *  pWf_decompress->nBlockAlign;

#endif


	return  0;
}

 extern  "C"  int  __declspec(  dllexport  )qdcGetCompressVideoCfg(  char  *  fourccStr,  unsigned  int  size  )
{
	strncpy(  fourccStr,  "test",  size  );
	return  0;
}


 void  qdcFreeOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	QDC_OBJ_test  *  pObj	=	(  QDC_OBJ_test  *  )pQdcObjInfo->var.pObj;
	int			i;

	for  (  i  =  0;  i  <  sizeof(  pObj->outs  )  /  sizeof(  pObj->outs[0]  );  i  ++  )  {
		 if  (  pObj->outs[i].pBuf  )  free(  pObj->outs[i].pBuf  );
	}
	memset(  &pObj->outs,  0,  sizeof(  pObj->outs  )  );
}







//
extern  "C"  int  __declspec(  dllexport  )qdcGetOutputByIndex(  QDC_OBJ_INFO  *  pQdcObjInfo,  int  index,  BYTE *  pbOutData,  unsigned  int  *  puiDataSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  pui_rtTimeLen  )
{
	QDC_OBJ_test	*	pObj	=	(  QDC_OBJ_test  *  )pQdcObjInfo->var.pObj;

	if  (  index  <  0  ||  index  >=  sizeof(  pObj->outs  )  /  sizeof(  pObj->outs[0]  )  )  return  -1;

#ifdef  _DEBUG
		//  return  CONST_qdcRet_bufTooSmall;
#endif

	if  (  *puiDataSize  <  pObj->outs[index].len  )  {
		return  -1;
	}

	if  (  !pObj->outs[index].len  )  return  -1;	

	*puiDataSize  =  pObj->outs[index].len;

	memcpy(  pbOutData,  pObj->outs[index].pBuf,  pObj->outs[index].len  );

	if  (  puiSampleTimeInMs  )  {
		*puiSampleTimeInMs  =  (  unsigned  int  )(  pObj->outs[index].rtStart  /  (  10  *  1000  )  );
		if  (  (  (  int  )*puiSampleTimeInMs  )  <  0  )  {
			*puiSampleTimeInMs  =  0;
		}
	}
	if  (  pui_rtTimeLen  )  {
		*pui_rtTimeLen  =  (  unsigned  int  )pObj->outs[index].rtTimeLen;
	}

	pObj->outs[index].len  =  0;

	return  0;
}



extern  "C"  int  __declspec(  dllexport  )qdcClearOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	QDC_OBJ_test	*	pObj	=	(  QDC_OBJ_test  *  )pQdcObjInfo->var.pObj;
	int		i;

	for  (  i  =  0;  i  <  sizeof(  pObj->outs  )  /  sizeof(  pObj->outs[0]  );  i  ++  )  {
		 pObj->outs[i].len  =  0;
	}

	return  0;
}