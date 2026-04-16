// qisCompress.cpp : Defines the exported functions for the DLL application.
//

#include	"stdafx.h"
#include	<tchar.h>
#include	<stdlib.h>
//  #include	<Dshow.h>

#include	"qySyncObj.h"
#include	"qisCompressProc.h"


//
#define	CONST_ver_qisCompress		"02660142"	//  2017/08/20	"02650115"		//  2016/12/14,"02630335"	//  2016/04/14,"02630295"		//  2016/04/10,"02630243"			//  2015/11/02,"02630239"			//  2015/10/24,"02630228"	//  2015/10/17,"02630211"	//  2015/10/05	//  "026132"	//	2014/05/13,"025982";		// 2014/02/27,"02592301";		//  2013/03/06,"02550501";  2012/11/12

 
//
//
//
//#define  CONST_fourcc_h264		MAKEFOURCC('h','2','6','4')
//#define  CONST_fourcc_YV12		MAKEFOURCC('Y','V','1','2')

/*/////////////////////////////////////////////////////////////////////////////////////////// 
// This is a simple code to get started to use H.264 decoder. For more of the code sample, check 
// simpleplaeyr application in the UMC sample code */ 
//#include 
//#include 
#include "ipp.h" 
#include "umc_defs.h" 
#include "umc_video_decoder.h" 
#include "umc_video_data.h" 
#include "umc_h264_video_decoder.h" 
#include "umc_structures.h" 
#include <mmreg.h>
#include "umc_video_processing.h"

//#define MAXFRAME 100000 
//#define MAXVIDEOSIZE 100000000 
//#define MAXYUVSIZE 200000000 

//  UMC::Status mywriteVideoFrame( UMC::VideoData *pData,  char  *  cYUVData,  int  iSize);

int makeBmpInfoHeader_yv12(  unsigned int bits,  int iWidth,  int iHeight,  BITMAPINFOHEADER  *  p  );

#if 0
QIS_guiOpen		*  g_pGuiOpen	=	NULL;
int		tmp_showInfo(  TCHAR  *  hint  )
{
	if  (  g_pGuiOpen  )  g_pGuiOpen->pf_showInfo(  0,  0,  hint  ); 
	return  0;
}
#endif

#if  10
 // wxrÐ´ÔÚ2003/09/12
 extern  "C"  static  int  tmp_qyGetRegCfg1(  HKEY  hKeyRoot0,  LPCTSTR  rootKey,  LPCTSTR  cfgName,  LPBYTE  cfgVal,  int  size,  unsigned  int  *  puiType  )
{
	int		iRet		=	-1;
	BOOL	bKeyOpen	=	FALSE;
	HKEY	hKey;
	int		lRet		=	0;
	long	cb;
	DWORD	type;
			
	if  (  !rootKey  || !rootKey[0]  )  return  -1;
	if  (  !hKeyRoot0  )  hKeyRoot0  =  HKEY_LOCAL_MACHINE;

	//  lRet  =  RegOpenKey(  hKeyRoot0,  rootKey,  & hKey  );
	lRet  =  RegOpenKeyEx(  hKeyRoot0,  rootKey,  0,  KEY_QUERY_VALUE,  & hKey  );
	if  (  lRet  !=  ERROR_SUCCESS  )  {
		//  traceLogA(  "qyGetRegCfg(  ):  RegOpenKey( %s )  failed.",  rootKey  );
		goto  errLabel;
	}
	bKeyOpen  =  TRUE;
	
	cb  =  size;
	if  (  RegQueryValueEx(  hKey,  cfgName,  0,  & type,  (  unsigned  char  *  )cfgVal, 
			(  unsigned  long  *  ) & cb  )  !=  ERROR_SUCCESS  ) 
	{
		//  traceLogA(  "qyGetRegCfg(  ):  RegQueryValueEx( %s )  failed.",  cfgName  );
		goto errLabel;
	}
	//  2003/09/12¼ÓÈëÁË¶ÔÀàÐÍµÄÅÐ¶Ï£¬½ö¶Ô×Ö·û´®×÷½áÎ²
	if  (  type  ==  REG_SZ  ||  type  ==  REG_MULTI_SZ  ||  type  ==  REG_EXPAND_SZ   )  {
		TCHAR	*	pT  =  (  TCHAR  *  )cfgVal;
		cb  =  cb  /  sizeof(  TCHAR  );
		if  (  cb  <  1  )  pT[0]	=	0;
		else  pT[cb - 1] = 0;
	}
	
	iRet  =  0;
	
errLabel:

	if ( bKeyOpen ) RegCloseKey( hKey );

	if  (  !iRet  )  {
		if  (  puiType  )  *  puiType  =  type;		//  2004/08/06¼Ó
	}

	return iRet;

}

#endif


#if  0
void DecodeStream( Ipp8u *cVideoData,int VideoDataSize, Ipp8u *cYUVData, int& imgWidth, int & imgHeight, int & frameNumber ) 
{ 
	UMC::Status status; UMC::MediaData DataIn; UMC::VideoData DataOut; UMC::VideoDecoderParams Params; UMC::H264VideoDecoder H264Decoder; 
	int frameSize=0; 
	DataIn.SetBufferPointer(cVideoData,VideoDataSize); 
	DataIn.SetDataSize(VideoDataSize); 
	Params.m_pData = &DataIn; 
	Params.lFlags=0; 
	Params.numThreads=1; 
	if(status = H264Decoder.Init(&Params)!=UMC::UMC_OK) return; 
	H264Decoder.GetInfo(&Params); 
	imgWidth=Params.info.clip_info.width; 
	imgHeight=Params.info.clip_info.height; 
	frameSize = imgWidth*imgHeight*3/2; 
	DataOut.Init(imgWidth,imgHeight,UMC::YV12,8); 
	DataOut.SetBufferPointer(cYUVData,frameSize); 
	int exit_flag=0; frameNumber=0; 
	do{ 
		status = H264Decoder.GetFrame(&DataIn, &DataOut); 
		if (status == UMC::UMC_OK){ cYUVData += (imgWidth*imgHeight*3/2); DataOut.SetBufferPointer(cYUVData,frameSize); frameNumber++; } 
		if((status !=UMC::UMC_OK)||(frameNumber >=MAXFRAME)) exit_flag = 1; 
	}while (exit_flag!=1); 
	do{ 
		status = H264Decoder.GetFrame(NULL, &DataOut); 
		if (status == UMC::UMC_OK) { cYUVData += frameSize; DataOut.SetBufferPointer(cYUVData,frameSize); frameNumber++; } 
	}while(status == UMC::UMC_OK); return; 
} 
#endif


 



UMC::Status  tmp_H264Decoder_GetFrame(  UMC::H264VideoDecoder &H264Decoder,  UMC::MediaData  * pDataIn,  UMC::VideoData  *  pDataOut  )
{
	int			iErr	=	-1;
	UMC::Status  status  =  UMC::UMC_ERR_FAILED;
	TCHAR  tBuf[256];

		
	//__try  
	try
	{
			status = H264Decoder.GetFrame(pDataIn, pDataOut); 
			}
	//  __except(  1  )  
	catch  (  ...  )
	{
		   //  _sntprintf(  tBuf,  sizeof(  tBuf  ) /  sizeof(  tBuf[0]  ),  _T(  "H264Decoder.GetFrame failed, __except, %d"  ),  GetExceptionCode(  )  );
		_sntprintf(  tBuf,  sizeof(  tBuf  ) /  sizeof(  tBuf[0]  ),  _T(  "H264Decoder.GetFrame failed, __except, %d"  ),  -1  );
		   tmp_showInfo(  tBuf  );
		   goto  errLabel;			
	}

	iErr  =  0;
	
errLabel:

	return  iErr  ?  UMC::UMC_ERR_FAILED  :  status;


}

//
UMC::Status  tmp_H264Decoder_Init(  UMC::H264VideoDecoder  &H264Decoder,  UMC::VideoDecoderParams  *  pParams  )
{
	int		iErr	=	-1;
	UMC::Status  status  =  UMC::UMC_ERR_FAILED;
	TCHAR  tBuf[256];


	//  __try  
	try
	{
			status = H264Decoder.Init(pParams);
			}
	//__except(  1  )  
	catch  (  ...  )
	{
		   //  _sntprintf(  tBuf,  sizeof(  tBuf  ) /  sizeof(  tBuf[0]  ),  _T(  "H264Decoder.Init failed, __except, %d"  ),  GetExceptionCode(  )  );
		_sntprintf(  tBuf,  sizeof(  tBuf  ) /  sizeof(  tBuf[0]  ),  _T(  "H264Decoder.Init failed, __except, %d"  ),  -1  );
		   tmp_showInfo(  tBuf  );
		   goto  errLabel;			
	}

	iErr  =  0;
	
errLabel:

	return  iErr  ?  UMC::UMC_ERR_FAILED  :  status;


}


UMC::Status  tmp_H264Decoder_GetInfo(  UMC::H264VideoDecoder  &H264Decoder,  UMC::VideoDecoderParams  *  pParams  )
{
	int		iErr	=	-1;
	UMC::Status  status  =  UMC::UMC_ERR_FAILED;
	TCHAR  tBuf[256];


	//__try  
	try
	{
	
			status  =  H264Decoder.GetInfo(pParams); 
			}
	//__except(  1  )  
	catch  (  ...  )
	{
		   //  _sntprintf(  tBuf,  sizeof(  tBuf  ) /  sizeof(  tBuf[0]  ),  _T(  "H264Decoder.GetInfo failed, __except, %d"  ),  GetExceptionCode(  )  );
		_sntprintf(  tBuf,  sizeof(  tBuf  ) /  sizeof(  tBuf[0]  ),  _T(  "H264Decoder.GetInfo failed, __except, %d"  ),  -1  );
		   tmp_showInfo(  tBuf  );
		   goto  errLabel;			
	}

	iErr  =  0;
	
errLabel:

	return  iErr  ?  UMC::UMC_ERR_FAILED  :  status;


}

#if  0	//  2014/02/26
//  2012/09/19
void  20120919_myDecodeStream(   QDC_OBJ_h264Dec  *  pObj,  BOOL  *  pbInited,  Ipp8u *cVideoData,int VideoDataSize, Ipp8u *cYUVData, int imgWidth, int  imgHeight, int & frameNumber ) 
{ 
	int		iErr	=	-1;

	if  (  !pObj
		||  !pObj->pDecoder
		||  !pObj->pVideoDecoderParams
		||  !pObj->pVideoProc
		||  !pObj->pVccParams
		)
	{
		tmp_showInfo(  _T(  "myDecodeStream: params err"  )  );
		return;
	}

	//
	UMC::H264VideoDecoder  *  pH264Decoder  =  (  UMC::H264VideoDecoder  *  )pObj->pDecoder;


	//  2012/05/27
	BOOL	tmp_bInited  =  *pbInited;
	if  (  !tmp_bInited  )   {
		tmp_showInfo(  _T(  "myDecodeStream: not inited"  )  );
	}

	//
	UMC::Status status; 
	UMC::H264VideoDecoder &H264Decoder  =  *pH264Decoder; 
	UMC::MediaData  & DataIn  =  *(  UMC::MediaData  *  )pObj->pDataIn; 
	UMC::VideoData &  DataOut  =  *(  UMC::VideoData  *  )pObj->pDataOut; 
	int frameSize=0; 
	int  maxFrame  =  frameNumber;  frameNumber  =  0;
	TCHAR	tBuf[256];


	DataIn.SetBufferPointer(cVideoData,VideoDataSize); 
	DataIn.SetDataSize(VideoDataSize);


#if  10
	if  (  !*pbInited  )  {

		//  2012/05/27
		CQySyncObj	syncObj;
		if  (  syncObj.sync(  _T(  "qSyncDecode"  ),  1000  )  )  {
			tmp_showInfo(  _T(  "myDecodeStream: sync failed"  )  );
			return;
		}

		UMC::VideoDecoderParams  & Params  =  *(  UMC::VideoDecoderParams  *)pObj->pVideoDecoderParams;
		UMC::VideoProcessing	&  videoProc  =  *(  UMC::VideoProcessing  *  )pObj->pVideoProc;
		UMC::VideoColorConversionParams &  vccParams  =  *(  UMC::VideoColorConversionParams  *  )pObj->pVccParams;


		//
		Params.m_pData = &DataIn; 
		Params.m_iFlags=0; 
		Params.m_iThreads=1; 
		//
		Params.m_pPostProcessor  =  &videoProc;
		//
		//  status = H264Decoder.Init(&Params);
		status  =  tmp_H264Decoder_Init(  H264Decoder,  &Params  );
		if  (  status  !=  UMC::UMC_OK  )  {
			//  2012/05/26
			_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "myDecodeStream: Decoder.init failed, status %d"  ),  status  );
			tmp_showInfo(  tBuf  );

			return; 
		}

		//  H264Decoder.GetInfo(&Params); 
		tmp_H264Decoder_GetInfo(  H264Decoder,  &Params  );
		//  imgWidth=Params.info.clip_info.width; 
		//  imgHeight=Params.info.clip_info.height;

		if  (  imgWidth  !=  Params.m_info.videoInfo.m_iWidth
			||  imgHeight  !=  Params.m_info.videoInfo.m_iHeight  )  
		{
			_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "myDecodeStream: Decoder init failed, w,h (%d,%d) != clip(%d,%d)\n"  ),  
				imgWidth,  imgHeight,  Params.m_info.videoInfo.m_iWidth,  Params.m_info.videoInfo.m_iHeight  );
			
			//  2012/05/25
			tmp_showInfo(  tBuf  );

			return;
		}

		*pbInited  =  TRUE;
	}
#endif

	frameSize = imgWidth*imgHeight*3/2; 


	frameNumber  =  0;
	
	//  DataOut.Reset(  );
	DataOut.SetBufferPointer(cYUVData,frameSize); 

	//  status = H264Decoder.GetFrame(&DataIn, &DataOut); 
	status  =  tmp_H264Decoder_GetFrame(  H264Decoder,  &DataIn,  &DataOut  );
	if  (  status  ==  UMC::UMC_ERR_FAILED  )  goto  errLabel;
	
	if (status == UMC::UMC_OK)  {
		#if  0
		if  (  mywriteVideoFrame(  &DataOut,  (  char  *  )cYUVData,  frameSize  )  )  {
			goto  errLabel;
		}
		#endif
		frameNumber++; 
	}
	
	do{ 
		//  DataOut.Reset(  );
		DataOut.SetBufferPointer(cYUVData,frameSize); 

		//  status = H264Decoder.GetFrame(NULL, &DataOut); 
		status  =  tmp_H264Decoder_GetFrame(  H264Decoder,  NULL,  &DataOut  );
		if  (  status  ==  UMC::UMC_ERR_FAILED  )  goto  errLabel;

		if (status == UMC::UMC_OK) { 
			//  
			#if  0
			if  (  mywriteVideoFrame(  &DataOut,  (  char  *  )cYUVData,  frameSize  )  )  {
				goto  errLabel;
			}
			#endif
			frameNumber++; 
		} 
	}while(status == UMC::UMC_OK); 



	iErr  =  0;

errLabel:

	//  2012/05/27
	if  (  !tmp_bInited  )   {
		tmp_showInfo(  _T(  "myDecodeStream: inited"  )  );
	}
	if  (  iErr  ||  frameNumber  !=  1  )  {
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "decode failed, frameNumber %d"  ),  frameNumber  );
		tmp_showInfo(  tBuf  );
	}

	//
	return; 
} 
#endif


void  myDecodeStream_init(   QDC_OBJ_h264Dec  *  pObj,  BOOL  *  pbInited,  Ipp8u *cVideoData,int VideoDataSize, long  *  pimgWidth, long  *  pimgHeight ) 
{ 
	int		iErr	=	-1;
	
	//
	if  (  !pimgWidth  ||  !pimgHeight  )  return;
	int  imgWidth  =  *pimgWidth;
	int  imgHeight  =  *pimgHeight;

	//
	if  (  !pObj
		||  !pObj->pDecoder
		||  !pObj->pVideoDecoderParams
		||  !pObj->pVideoProc
		||  !pObj->pVccParams
		)
	{
		tmp_showInfo(  _T(  "myDecodeStream_init: params err"  )  );
		return;
	}

	//
	UMC::H264VideoDecoder  *  pH264Decoder  =  (  UMC::H264VideoDecoder  *  )pObj->pDecoder;


	//  2012/05/27
	BOOL	tmp_bInited  =  *pbInited;
	if  (  !tmp_bInited  )   {
		tmp_showInfo(  _T(  "myDecodeStream_init: not inited"  )  );
	}

	//
	UMC::Status status; 
	UMC::H264VideoDecoder &H264Decoder  =  *pH264Decoder; 
	UMC::MediaData  & DataIn  =  *(  UMC::MediaData  *  )pObj->pDataIn; 
	UMC::VideoData &  DataOut  =  *(  UMC::VideoData  *  )pObj->pDataOut; 
	int frameSize=0; 
	//int  maxFrame  =  frameNumber;  frameNumber  =  0;
	TCHAR	tBuf[256];


	DataIn.SetBufferPointer(cVideoData,VideoDataSize); 
	DataIn.SetDataSize(VideoDataSize);


#if  10
	if  (  !*pbInited  )  {

		//  2012/05/27
		CQySyncObj	syncObj;
		if  (  syncObj.sync(  _T(  "qSyncDecode"  ),  1000  )  )  {
			tmp_showInfo(  _T(  "myDecodeStream_init: sync failed"  )  );
			return;
		}

		UMC::VideoDecoderParams  & Params  =  *(  UMC::VideoDecoderParams  *)pObj->pVideoDecoderParams;
		UMC::VideoProcessing	&  videoProc  =  *(  UMC::VideoProcessing  *  )pObj->pVideoProc;
		UMC::VideoColorConversionParams &  vccParams  =  *(  UMC::VideoColorConversionParams  *  )pObj->pVccParams;


		//
		Params.m_pData = &DataIn; 
		Params.m_iFlags=0; 
		Params.m_iThreads=1; 
		//
		Params.m_pPostProcessor  =  &videoProc;
		//
		//  status = H264Decoder.Init(&Params);
		status  =  tmp_H264Decoder_Init(  H264Decoder,  &Params  );
		if  (  status  !=  UMC::UMC_OK  )  {
			//  2012/05/26
			_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "myDecodeStream_init: Decoder.init failed, status %d"  ),  status  );
			tmp_showInfo(  tBuf  );

			return; 
		}

		//  H264Decoder.GetInfo(&Params); 
		status  =  tmp_H264Decoder_GetInfo(  H264Decoder,  &Params  );
		if  (  status  !=  UMC::UMC_OK  )  {
			//  2012/05/26
			_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "myDecodeStream_init: Decoder.GetInfo failed, status %d"  ),  status  );
			tmp_showInfo(  tBuf  );

			return; 
		}
		//  imgWidth=Params.info.clip_info.width; 
		//  imgHeight=Params.info.clip_info.height;

		//
		if  (  !Params.m_info.videoInfo.m_iWidth
			||  !Params.m_info.videoInfo.m_iHeight  )  
		{
			_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "myDecodeStream_init: Decoder init failed, w,h (%d,%d) != clip(%d,%d)\n"  ),  
				imgWidth,  imgHeight,  Params.m_info.videoInfo.m_iWidth,  Params.m_info.videoInfo.m_iHeight  );
			
			//  2012/05/25
			tmp_showInfo(  tBuf  );

			return;
		}


		//
		if  ( imgWidth  &&  imgHeight  )  {
			if  (  imgWidth  !=  Params.m_info.videoInfo.m_iWidth
				||  imgHeight  !=  Params.m_info.videoInfo.m_iHeight  )  
			{
				_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "myDecodeStream_init: Decoder init failed, w,h (%d,%d) != clip(%d,%d)\n"  ),  
					imgWidth,  imgHeight,  Params.m_info.videoInfo.m_iWidth,  Params.m_info.videoInfo.m_iHeight  );
			
				//  2012/05/25
				tmp_showInfo(  tBuf  );

				return;
			}
		}

		//
		*pimgWidth  =  Params.m_info.videoInfo.m_iWidth;
		*pimgHeight  =  Params.m_info.videoInfo.m_iHeight;
		imgWidth  =  *pimgWidth;
		imgHeight  =  *pimgHeight;

		//
		*pbInited  =  TRUE;
	}
#endif



	iErr  =  0;

errLabel:

	//  2012/05/27
	if  (  !tmp_bInited  )   {
		tmp_showInfo(  _T(  "myDecodeStream_init: inited"  )  );
	}
	if  (  iErr  )  {
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "myDecodeStream_init failed"  )  );
		tmp_showInfo(  tBuf  );
	}

	//
	return; 
} 


void  myDecodeStream_init2(  QDC_OBJ_INFO  *  pQdcObjInfo,  QDC_OBJ_h264Dec  *  pObj,  int  imgWidth,  int  imgHeight  )
{
	int				iErr		=	-1;
	QDC_OBJ_INFO  &  qdcObjInfo  =  *pQdcObjInfo;

	if  (  pObj->common.bInited2  )  return;

	if  (  !imgWidth  ||  !imgHeight  )  {
		tmp_showInfo(  _T(  "myDeode_init2 failed, imgWidth or imgH is 0"  )  );
		return;
	}
	
#if  10  //  2014/02/26,因为w和h可能无法确定,所以,要移到解码的初始化后去.

	if  (  !pQdcObjInfo->cfg.v.dec.pf_updateDecVideoParam  )  {
		tmp_showInfo(  _T(  "decPipeline failed: updateDecVideoParam is null"  )  );
		return;
	}
	//	
	BITMAPINFOHEADER  bih;
	int  iFourcc  =  CONST_fourcc_YV12;	
	double  dFrameRate  =  0;
	makeBmpInfoHeader_yv12(  12,  imgWidth,  imgHeight,  &bih  );	
	if  (  pQdcObjInfo->cfg.v.dec.pf_updateDecVideoParam(  &bih,  dFrameRate,  pQdcObjInfo->cfg.v.pParent_transform,  pQdcObjInfo->cfg.v.uiTransformType_pParent  )  )  {
		tmp_showInfo(  _T(  "decPipeline failed: updateDecVideoParam  failed"  )  );
		return;	
	}


	//
	int  biBitCount  =  12;
	int  biSizeImage  =  (  imgWidth  *  biBitCount  +  31  )  /  32  *  4  *  imgHeight;

	//
	//  qdcObjInfo.
	qdcObjInfo.var.cbOutputBuffer  =  biSizeImage;
	qdcObjInfo.var.cbInputBuffer  =  qdcObjInfo.var.cbOutputBuffer;


	//
	UMC::VideoData  *  pDataOut  =  (  UMC::VideoData  *  )pObj->pDataOut;

	try  {			//  2014/05/13
		if  (  pDataOut->Init(imgWidth,imgHeight,UMC::YV12,8)  )  goto  errLabel;
		//  if  (  pDataOut->Alloc(  )  )  goto  errLabel;
	}
	catch(  ...  )  {
		tmp_showInfo(  _T(  "myDeode_init2 failed, try and catch"  )  );
		goto  errLabel;
	}
		
	//
	makeBmpInfoHeader_yv12(  12,  imgWidth,  imgHeight,  &pObj->outputForDec.vh_decompress_real.bih  );
	pObj->outputForDec.uiBufSize  =  pObj->outputForDec.vh_decompress_real.bih.biSizeImage;

	if  (  pObj->outputForDec.pBuf  )  {
		free(  pObj->outputForDec.pBuf  );  pObj->outputForDec.pBuf  =  NULL;
	}
	pObj->outputForDec.pBuf  =  (  char  *  )malloc(  pObj->outputForDec.uiBufSize  );
	if  (  !pObj->outputForDec.pBuf  )  goto  errLabel;


	//	
	if  (  pObj->common.outs[0].pBuf  )  {
		free(  pObj->common.outs[0].pBuf  );  pObj->common.outs[0].pBuf  =  NULL;
	}
	if  (  !pObj->common.outs[0].pBuf  )  {
		pObj->common.outs[0].pBuf  =  (  BYTE  *  )malloc(  qdcObjInfo.var.cbOutputBuffer  );
		if  (  !pObj->common.outs[0].pBuf  )  goto  errLabel;
	}


#endif

	//		
	tmp_showInfo(  _T(  "myDeode_init2 (eha) ok"  )  );

	//
	pObj->common.bInited2  =  TRUE;
	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pObj->outputForDec.pBuf  )  {
			free(  pObj->outputForDec.pBuf  );  pObj->outputForDec.pBuf  =  NULL;
		}
		if  (  pObj->common.outs[0].pBuf  )  {
			free(  pObj->common.outs[0].pBuf  );  pObj->common.outs[0].pBuf  =  NULL;
		}
	}
	return;

}



//  2014/02/26. //  2012/09/19
//  void  myDecodeStream(   QDC_OBJ_h264Dec  *  pObj,  BOOL  *  pbInited,  BOOL  bEnd,  Ipp8u *cVideoData,int VideoDataSize, Ipp8u *cYUVData, int    imgWidth, int    imgHeight, int & frameNumber ) 
int  myDecodeStream(   QDC_OBJ_INFO  *  pQdcObjInfo,  BOOL  *  pbInited,  BOOL  bEnd,  Ipp8u *cVideoData,int VideoDataSize, Ipp8u *cYUVData, int    imgWidth, int    imgHeight, int maxFrames ) 
{ 
	int		iErr	=	-1;
	
	void  *  pDebugStep  =  pQdcObjInfo->var.pDebugStep;
	DEBUG_step_dec	*	pDebugStepDec  =  (  DEBUG_step_dec  *  )tmp_getDebugStep_sth(  0,  CONST_debugStepType_dec,  pQdcObjInfo->var.pDebugStep  );
	if  (  !pDebugStepDec  )  return  -1;

	
	//	
	QDC_OBJ_h264Dec  *  pObj  =  (  QDC_OBJ_h264Dec  *  )pQdcObjInfo->var.pObj;  
	//
	if  (  !pObj
		||  !pObj->pDecoder
		||  !pObj->pVideoDecoderParams
		||  !pObj->pVideoProc
		||  !pObj->pVccParams
		)
	{
		tmp_showInfo(  _T(  "myDecodeStream: params err"  )  );
		return  -1;
	}

	//
	UMC::H264VideoDecoder  *  pH264Decoder  =  (  UMC::H264VideoDecoder  *  )pObj->pDecoder;


	//  2012/05/27
	BOOL	tmp_bInited  =  *pbInited;
	if  (  !tmp_bInited  )   {
		tmp_showInfo(  _T(  "myDecodeStream: not inited"  )  );
		return  -1;
	}

	//
	UMC::Status status; 
	UMC::H264VideoDecoder &H264Decoder  =  *pH264Decoder; 
	UMC::MediaData  & DataIn  =  *(  UMC::MediaData  *  )pObj->pDataIn; 
	UMC::VideoData &  DataOut  =  *(  UMC::VideoData  *  )pObj->pDataOut; 
	int frameSize=0; 
	//  int  maxFrame  =  frameNumber;  
	int  frameNumber  =  0;
	TCHAR	tBuf[256];

#define  MAX_FRAMES		3
#define  MAX_FRAMES_end	10000

	if  (  !maxFrames  )  maxFrames  =  3;	
	if  (  bEnd  )  {
		maxFrames  =  min(  maxFrames,  MAX_FRAMES_end  );
		}
	else  {
		  maxFrames  =  min(  maxFrames,  MAX_FRAMES  );
	}
		
	//
	if  (  !imgWidth  ||  !imgHeight  )  {
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "myDecodeStream failed, imgWidth or imgHeight err"  )  );
		tmp_showInfo(  tBuf  );
		return  -1;
	}


	//
	frameSize = imgWidth*imgHeight*3/2; 


	frameNumber  =  0;
	

	if  (  !bEnd  )  {
		
		DataIn.SetBufferPointer(cVideoData,VideoDataSize); 
		DataIn.SetDataSize(VideoDataSize);

		do  {
			//  DataOut.Reset(  );		
			DataOut.SetBufferPointer(cYUVData,frameSize); 

			//
			tmp_mySetDebugStep(  0,  pDebugStep,  307  );

			//  status = H264Decoder.GetFrame(&DataIn, &DataOut); 	
			status  =  tmp_H264Decoder_GetFrame(  H264Decoder,  &DataIn,  &DataOut  );	

			//
			tmp_mySetDebugStep(  0,  pDebugStep,  308  );

			//
			//if  (  status  ==  UMC::UMC_ERR_FAILED  )  goto  errLabel;
			if  (  status  ==  UMC::UMC_ERR_NOT_ENOUGH_DATA  )  break;
			if  (  status  !=  UMC::UMC_OK  )  {
				//
				pDebugStepDec->bException  =  TRUE;
				//
				goto  errLabel;
			}
		
			if (status == UMC::UMC_OK)  {
				#if  0
					if  (  mywriteVideoFrame(  &DataOut,  (  char  *  )cYUVData,  frameSize  )  )  {
						goto  errLabel;
				}
				#endif
				frameNumber++; 
				}
			else  {
				  break;
			}

			//
			if  (  frameNumber  >=  maxFrames  )  break;

		}  while  (  status  == UMC::UMC_OK  ); 
	
		}
	else  {

		  do{ 
			//  DataOut.Reset(  );
			DataOut.SetBufferPointer(cYUVData,frameSize); 

			//  status = H264Decoder.GetFrame(NULL, &DataOut); 
			status  =  tmp_H264Decoder_GetFrame(  H264Decoder,  NULL,  &DataOut  );
			if  (  status  ==  UMC::UMC_ERR_FAILED  )  goto  errLabel;

			if (status == UMC::UMC_OK) { 
				//  
				#if  0
					if  (  mywriteVideoFrame(  &DataOut,  (  char  *  )cYUVData,  frameSize  )  )  {
					goto  errLabel;
				}
				#endif
				frameNumber++; 
				}
			else  {
				  break;
			}

			//
			if  (  frameNumber  >=  maxFrames  )  break;
		
		  }while(status == UMC::UMC_OK); 

	}


	iErr  =  0;

errLabel:

	//  2012/05/27
	if  (  !tmp_bInited  )   {
		tmp_showInfo(  _T(  "myDecodeStream: inited"  )  );
	}
	if  (  iErr  )  {
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "decode failed, frameNumber %d"  ),  frameNumber  );
		tmp_showInfo(  tBuf  );
	}

	//
	return  iErr  <  0  ?  iErr  : frameNumber; 
} 


#if  0
int ReadVideoData(char* strFilename,Ipp8u *cVideoData,int &VideoDataSize) { FILE* fp = fopen(strFilename, "rb"); if(fp==NULL) return 0; VideoDataSize=fread(cVideoData,1,MAXVIDEOSIZE,fp); fclose(fp); } 
void WriteYUVData(char* strFilename,Ipp8u * cYUVData,int imgWidth, int imgHeight, int frameNumber) { FILE* outfp = fopen(strFilename, "wb"); if(outfp==NULL) return ; fwrite(cYUVData,frameNumber*imgWidth*imgHeight*3/2,1,outfp); fclose(outfp); } 
int main(int argc, vm_char* argv[]) { Ipp8u *cVideoData = ippsMalloc_8u(MAXVIDEOSIZE); Ipp8u *cYUVData = ippsMalloc_8u(MAXYUVSIZE); int VideoDataSize,imgWidth, imgHeight, frameNumber; char * InputVideofileName, *OutputYUVFileName; InputVideofileName = "teststream.h264"; OutputYUVFileName = "testoutput.yuv"; ReadVideoData(InputVideofileName,cVideoData,VideoDataSize); DecodeStream(cVideoData,VideoDataSize,cYUVData,imgWidth, imgHeight, frameNumber); WriteYUVData(OutputYUVFileName,cYUVData,imgWidth, imgHeight, frameNumber); return 0; } 
#endif


#include <stdio.h>
#include <stdlib.h>

#include "ipp.h"
#include "umc_defs.h"
#include "umc_video_data.h"
#include "umc_h264_video_encoder.h"
#include "umc_structures.h"
#include "umc_video_encoder.h"


//#define MAXVIDEOSIZE  100000000
//#define MAXYUVSIZE  200000000

#if  0
void EncodeStream(Ipp8u *cYUVData, int imgWidth, int imgHeight, int frameNumber,
                  Ipp8u *cVideoData,int &VideoDataSize ) 
{

   UMC::Status status;
   UMC::MediaData  DataOut; UMC::VideoData DataIn;
   int FrameSize;
   
   UMC::H264EncoderParams Params;
   UMC::H264VideoEncoder H264Encoder;; 

   Params.key_frame_controls.method=1;
   Params.info.clip_info.height=imgHeight;
   Params.info.clip_info.width=imgWidth;
   Params.info.bitrate = 1000000;
   Params.numThreads = 1; 
   
   if((status = H264Encoder.Init(&Params))!=UMC::UMC_OK)
	  return;

   FrameSize = imgWidth*imgHeight*3/2; 
   DataIn.Init(imgWidth,imgHeight,UMC::YV12,8);
   DataIn.SetBufferPointer(cYUVData,FrameSize);
   DataIn.SetDataSize(FrameSize);

   DataOut.SetBufferPointer(cVideoData,MAXVIDEOSIZE);

   VideoDataSize=0;
   int nEncodedFrames=0;
   while ( nEncodedFrames < frameNumber)
   {
	    status = H264Encoder.GetFrame(&DataIn, &DataOut);	    
        if (status == UMC::UMC_OK)
        {   
               nEncodedFrames++;
        
               VideoDataSize+=DataOut.GetDataSize();
	           DataOut.MoveDataPointer(DataOut.GetDataSize());
   
               cYUVData+=FrameSize;
	           DataIn.SetBufferPointer(cYUVData,FrameSize);
	           DataIn.SetDataSize(FrameSize);             
        }
	}
    return;  
}
#endif


#if  0	//  2012/09/15
void myEncodeStream(QDC_OBJ_INFO  *  pQdcObjInfo, 
					//  UMC::H264VideoEncoder  *  pH264Encoder,  
					Ipp8u *cYUVData, int imgWidth, int imgHeight, int frameNumber
					//  Ipp8u *cVideoData,int &VideoDataSize 
					) 
{
	QDC_OBJ_h264Enc  *  pObj  =  (  QDC_OBJ_h264Enc  *  )pQdcObjInfo->pObj;
	UMC::H264VideoEncoder  *  pH264Encoder  =  (  UMC::H264VideoEncoder  *  )pObj->pEncoder;

	TCHAR  tBuf[256]  = _T(  ""  );

   UMC::Status status;
   UMC::MediaData  DataOut; UMC::VideoData DataIn;
   int FrameSize;
   
   //  UMC::H264EncoderParams Params;
   UMC::H264VideoEncoder & H264Encoder  =  *pH264Encoder; 

#if  0
   Params.key_frame_controls.method=1;
   Params.info.clip_info.height=imgHeight;
   Params.info.clip_info.width=imgWidth;
   Params.info.bitrate = 1000000;
   Params.numThreads = 1; 
   
   if((status = H264Encoder.Init(&Params))!=UMC::UMC_OK)
	  return;
#endif

   FrameSize = imgWidth*imgHeight*3/2; 
   DataIn.Init(imgWidth,imgHeight,UMC::YV12,8);
   DataIn.SetBufferPointer(cYUVData,FrameSize);
   DataIn.SetDataSize(FrameSize);

   int  index  =  0;
   if  (  !pObj->common.outs[index].pBuf  )  {
	   pObj->common.outs[index].pBuf  =  (  BYTE  *  )malloc(  pQdcObjInfo->cbOutputBuffer  );
	   if (  !pObj->common.outs[index].pBuf  )  goto  errLabel;
   }
   //  DataOut.SetBufferPointer(cVideoData,MAXVIDEOSIZE);
   DataOut.SetBufferPointer(  pObj->common.outs[index].pBuf,  pQdcObjInfo->cbOutputBuffer  );

   int  VideoDataSize=0;
   int nEncodedFrames=0;
   while ( nEncodedFrames < frameNumber)
   {
	    status = H264Encoder.GetFrame(&DataIn, &DataOut);	    
        if (status == UMC::UMC_OK)
        {   
               nEncodedFrames++;
        
               VideoDataSize+=DataOut.GetDataSize();
			   pObj->common.outs[index].len  =  DataOut.GetDataSize(  );
	           //  DataOut.MoveDataPointer(DataOut.GetDataSize());
			   index  ++;
			   if  (  index  >=  sizeof( pObj->common.outs  )  /  sizeof(  pObj->common.outs[0]  )  )  {
				   goto  errLabel; 
			   }
			   if  (  !pObj->common.outs[index].pBuf  )  {
				   pObj->common.outs[index].pBuf  =  (  BYTE  *  )malloc(  pQdcObjInfo->cbOutputBuffer  );
				   if  (  !pObj->common.outs[index].pBuf  )  goto  errLabel;
			   }
			   DataOut.SetBufferPointer(  pObj->common.outs[index].pBuf,  pQdcObjInfo->cbOutputBuffer  );
   
               cYUVData+=FrameSize;
	           DataIn.SetBufferPointer(cYUVData,FrameSize);
	           DataIn.SetDataSize(FrameSize);             
        }
		else {
			 #if  1  //  def  _DEBUG
					 OutputDebugString(  _T(  "myEncodeStream err\n"  )  );
			 #endif
			 break;
		}
	}

errLabel:
//  #ifdef  _DEBUG
#if  1
		_sntprintf(  tBuf,  sizeof(  tBuf  )/  sizeof(  tBuf[0]  ),  _T(  "nEncodedFrames is %d, index %d, videoDataSize is %d\n"  ),nEncodedFrames,  index,  VideoDataSize  );
		OutputDebugString(  tBuf	    );
#endif

    return;  
}
#endif


UMC::Status myreadVideoFrame(char  *  cYUVData,  int  iSize, UMC::VideoData *pData)
{
    UMC::Status status;
    UMC::VideoData::PlaneData *pPlane;
    size_t iLenght;
    Ipp32u i;
    Ipp32s j;

	int  iLen  =  0;

    for(i = 0; i < pData->GetPlanesNumber(); i++)
    {
        pPlane = pData->GetPtrToPlane(i);
        iLenght = pPlane->m_size.width * pPlane->m_iSamples * pPlane->m_iSampleSize;

        for(j = 0; j < pPlane->m_size.height; j++)
        {
            //  status = pReader->GetData(pPlane->m_pPlane + pPlane->m_iPitch*j, iLenght);

			if  (  iLen  +  iLenght  >  iSize  )  {
				return  UMC::UMC_ERR_FAILED;
			}
			memcpy(  pPlane->m_pPlane + pPlane->m_iPitch*j, cYUVData,  iLenght);
			cYUVData  +=  iLenght;
			iLen  +=  iLenght;
			status  =  0;

            if(status != UMC::UMC_OK)
                return status;
        }
    }

    return UMC::UMC_OK;
}


#if  0
UMC::Status mywriteVideoFrame( UMC::VideoData *pData,  char  *  cYUVData,  int  iSize)
{
    UMC::Status status;
    UMC::VideoData::PlaneData *pPlane;
    size_t iLenght;
    Ipp32u i;
    Ipp32s j;

	int  iLen  =  0;

    for(i = 0; i < pData->GetPlanesNumber(); i++)
    {
        pPlane = pData->GetPtrToPlane(i);
        iLenght = pPlane->m_size.width * pPlane->m_iSamples * pPlane->m_iSampleSize;

        for(j = 0; j < pPlane->m_size.height; j++)
        {
            //  status = pWriter->PutData(pPlane->m_pPlane + pPlane->m_iPitch*j, iLenght);
			if  (  iLen  +  iLenght  >  iSize  )  {
				return  UMC::UMC_ERR_FAILED;
			}
			memcpy(  cYUVData,  pPlane->m_pPlane + pPlane->m_iPitch*j,  iLenght  );
			cYUVData  +=  iLenght;
			iLen  +=  iLenght;
			status  =  0;

            if(status != UMC::UMC_OK)
                return status;
        }
    }

    return UMC::UMC_OK;
}
#endif


//  2012/09/15
void myEncodeStream(QDC_OBJ_INFO  *  pQdcObjInfo, 
					//  UMC::H264VideoEncoder  *  pH264Encoder,  
					Ipp8u *cYUVData, int imgWidth, int imgHeight, int frameNumber
					//  Ipp8u *cVideoData,int &VideoDataSize 
					) 
{
	QDC_OBJ_h264Enc  *  pObj  =  (  QDC_OBJ_h264Enc  *  )pQdcObjInfo->var.pObj;
	UMC::H264VideoEncoder  *  pH264Encoder  =  (  UMC::H264VideoEncoder  *  )pObj->pEncoder;

	TCHAR  tBuf[256]  = _T(  ""  );

   UMC::Status status;
   //  UMC::MediaData  DataOut; UMC::VideoData DataIn;
   int FrameSize;
   
   //  UMC::H264EncoderParams Params;
   UMC::H264VideoEncoder & H264Encoder  =  *pH264Encoder; 
      //
   UMC::VideoProcessing  &  videoProc  =  *(  UMC::VideoProcessing  *  )pObj->pVideoProc;
   

   UMC::VideoData  &  DataIn  =  *(  UMC::VideoData  *  )pObj->pDataIn;
   UMC::VideoData  &  DataCvt  =  *(  UMC::VideoData  *  )pObj->pDataCvt;
   UMC::MediaData  &  DataOut  =  *(  UMC::MediaData  *  )pObj->pDataOut;



   FrameSize = imgWidth*imgHeight*3/2; 

   int  index  =  0;
   if  (  !pObj->common.outs[index].pBuf  )  {
	   pObj->common.outs[index].pBuf  =  (  BYTE  *  )malloc(  pQdcObjInfo->var.cbOutputBuffer  );
	   if (  !pObj->common.outs[index].pBuf  )  goto  errLabel;
   }

   int  VideoDataSize=0;
   int nEncodedFrames=0;
   while ( nEncodedFrames < frameNumber)
   {

	   if  (  myreadVideoFrame(  (  char  *  )cYUVData,  FrameSize,  &DataCvt  )  )  goto  errLabel;
	   status    = videoProc.GetFrame(&DataCvt, &DataIn);
	   if  (  status  )  goto  errLabel;
 

	   int  kk  =  DataIn.GetDataSize(  );
	   int  kk1  =  DataCvt.GetDataSize(  );
	   DataOut.Reset(  );
	   //  2012/11/06
	   DataOut.SetBufferPointer(  pObj->common.outs[index].pBuf,  pQdcObjInfo->var.cbOutputBuffer  );
   
	   //
	   __try  {
			status = H264Encoder.GetFrame(&DataIn, &DataOut);	    
	        }
	   __except(  1  )  {
		   _sntprintf(  tBuf,  sizeof(  tBuf  ) /  sizeof(  tBuf[0]  ),  _T(  "H264Encoder.GetFrame failed, __except, %d"  ),  GetExceptionCode(  )  );
		   tmp_showInfo(  tBuf  );
		   goto  errLabel;
	   }
        if (status == UMC::UMC_OK)
        {   
               nEncodedFrames++;
        
               VideoDataSize+=DataOut.GetDataSize();
			   pObj->common.outs[index].len  =  DataOut.GetDataSize(  );
	           //  DataOut.MoveDataPointer(DataOut.GetDataSize());
			   //  memcpy(  pObj->common.outs[index].pBuf,  DataOut.GetDataPointer(  ),  DataOut.GetDataSize(  )  );  

			   index  ++;
			   if  (  index  >=  sizeof( pObj->common.outs  )  /  sizeof(  pObj->common.outs[0]  )  )  {
				   goto  errLabel; 
			   }
			   if  (  !pObj->common.outs[index].pBuf  )  {
				   pObj->common.outs[index].pBuf  =  (  BYTE  *  )malloc(  pQdcObjInfo->var.cbOutputBuffer  );
				   if  (  !pObj->common.outs[index].pBuf  )  goto  errLabel;
			   }
			   //  DataOut.SetBufferPointer(  pObj->common.outs[index].pBuf,  pQdcObjInfo->cbOutputBuffer  );
   
               cYUVData+=FrameSize;
#if  0
	           DataIn.SetBufferPointer(cYUVData,FrameSize);
	           DataIn.SetDataSize(FrameSize);             
#endif
        }
		else {
			 #if  1  //  def  _DEBUG
					 OutputDebugString(  _T(  "myEncodeStream err\n"  )  );
			 #endif
			 break;
		}
	}

errLabel:
//  #ifdef  _DEBUG
#if  1
		_sntprintf(  tBuf,  sizeof(  tBuf  )/  sizeof(  tBuf[0]  ),  _T(  "nEncodedFrames is %d, index %d, videoDataSize is %d\n"  ),nEncodedFrames,  index,  VideoDataSize  );
		OutputDebugString(  tBuf	    );
#endif

    return;  
}


#if  0
void ReadYUVData(char* strFilename,Ipp8u *cYUVData, int imgWidth, int imgHeight, int frameNumber)
{
	FILE* infp = fopen(strFilename, "rb");
	if(infp==NULL)
		return ;
	fread(cYUVData,1,frameNumber*imgWidth*imgHeight*3/2, infp);
	fclose(infp);
}

void WriteVideoData(char* strFilename,Ipp8u * cVideoData,int VideoDataSize)
{
	FILE* fp = fopen(strFilename, "wb");
	if(fp==NULL)
		return;
	fwrite(cVideoData,VideoDataSize,1, fp);
	fclose(fp);
}



int main(int argc, vm_char* argv[]) {
	
   Ipp8u *cVideoData = ippsMalloc_8u(MAXVIDEOSIZE);
   Ipp8u *cYUVData = ippsMalloc_8u(MAXYUVSIZE);
   int VideoWidth=352,VideoHeight=288,FrameNumber=200;
   int VideoDataSize;
   char * InputYUVFileName, *OutputVideoFileName;
   
   InputYUVFileName = "teststream.yuv";
   OutputVideoFileName = "testoutput.h264";

   ReadYUVData( InputYUVFileName,cYUVData,VideoWidth,VideoHeight,FrameNumber);
   EncodeStream(cYUVData,VideoWidth,VideoHeight,FrameNumber,cVideoData,VideoDataSize);
   WriteVideoData(OutputVideoFileName,cVideoData,VideoDataSize);
   return 0;
} 
#endif




///////////////////////////////
int  yuy2ToRgb24_ipp(  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );
int  uyvyToRgb24_ipp(  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );
int  yuy2ToYv12_ipp(  char  *  inBuff,  char  *  outBuf,  int  width,  int  height  );
int  rgb24ToYv12_ipp(  unsigned  char  *  rgb,  unsigned  char  *  yuv,  int  width,  int  height,  BOOL  bFlipImg  );
int  yv12ToRgb24_ipp( unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );





 extern  "C"  __declspec(  dllexport  )  int  qdcInit(  QDC_MGR  *  p  )
{

	//  MessageBox(  NULL,  _T("qdcInit enter"),  _T("qycx"),  MB_OK  );

	OutputDebugString(  _T(  "qdcInit\n"  )  );

	g_pGuiOpen  =  p->pGuiOpen;
	//
	g_iDebugStepType  =  CONST_debugStepType_dec;


	p->iCompressorId  =  1;
	_tcsncpy(  p->name,  _T(  "test"  ),  sizeof(  p->name  )  /  sizeof(  p->name[0]  )  );
	//  2014/12/02
	strncpy(  p->ver,  CONST_ver_qisCompress,  mycountof(  p->ver  )  );  

	//
	p->pf_yuy2ToRgb24  =  yuy2ToRgb24_ipp;
	p->pf_yuy2ToYv12  =  yuy2ToYv12_ipp;  
	p->pf_rgb24ToYv12  =  rgb24ToYv12_ipp;
	p->pf_yv12ToRgb24  =  yv12ToRgb24_ipp;
	p->pf_uyvyToRgb24  =  uyvyToRgb24_ipp;		//  2012/02/23

	//  2012/05/26
	TCHAR	tBuf[128];
	_sntprintf(  tBuf,  sizeof(  tBuf  )/sizeof(  tBuf[0]  ),  _T(  "qdcInit called. ipp,%s"  ),  _T(  CONST_ver_qisCompress  )  );
	tmp_showInfo(  tBuf  );

	return  0;
}


 extern  "C"  int  __declspec(  dllexport  )qdcExit(  QDC_MGR  *  p  )
{

	OutputDebugString(  _T(  "qdcExit\n"  )  );

	return  0;
}



 extern  "C"  int  __declspec(  dllexport  )qdcGetCompressVideoCfg(  char  *  fourccStr,  unsigned  int  size  )
{
	//  strncpy(  fourccStr,  "test",  size  );

	strncpy(  fourccStr,  "h264",  size  );

	return  0;
}


 void  qdcFreeOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	QDC_OBJ_h264Common  *  pObj	=	(  QDC_OBJ_h264Common  *  )pQdcObjInfo->var.pObj;
	int			i;

	for  (  i  =  0;  i  <  sizeof(  pObj->outs  )  /  sizeof(  pObj->outs[0]  );  i  ++  )  {
		 if  (  pObj->outs[i].pBuf  )  free(  pObj->outs[i].pBuf  );
	}
	memset(  &pObj->outs,  0,  sizeof(  pObj->outs  )  );
}

 

 int makeBmpInfoHeader_yv12(  unsigned int bits,  int iWidth,  int iHeight,  BITMAPINFOHEADER  *  p  )
{
	if(  !p  )  return  -1;

	memset(  p,  0,  sizeof(  p[0]  )  );

	p->biSize  =  sizeof(  BITMAPINFOHEADER  );
	p->biWidth  =  iWidth;
	p->biHeight  =  iHeight;
	p->biPlanes  =  1;
	p->biBitCount  =  12;
	p->biCompression  =  CONST_fourcc_YV12;
	p->biSizeImage  =  (  p->biWidth  *  p->biBitCount  +  31  )  / 32  *  4  *  p->biHeight;
	p->biClrUsed  =  (  bits  <=  8  )  ?  1<<bits  :  0;

	return  0;

}


 struct EncoderParams
{
	UMC::ParserCfg      *pParser;
    UMC::VideoStreamType videoStreamType;
    IppiSize size;
    Ipp64f   fFramerate;
    Ipp32u   iBitrate;
    Ipp32u   iThreads;
    Ipp32u   iFramesLimit;
    Ipp32u   iFlags;

    EncoderParams()
    {
        videoStreamType = UMC::UNDEF_VIDEO;
        pParser         = NULL;
        size.width      = 0;
        size.height     = 0;
        fFramerate      = 30;
        iBitrate        = 2000000;
        iThreads        = 0;
        iFramesLimit    = 0;
        iFlags          = 0;
    };
};



#define		CONST_bp_compression		6500
extern  "C"  int  __declspec(  dllexport  )qdcInitCompressVideo(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_decompress,  QY_VIDEO_HEADER  *  pVh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{	
	//  MessageBox(  NULL,  _T("qdcInitCompressVideo enter"),  _T("qycx"),  MB_OK  );

	int						iErr	=	-1;
	QDC_OBJ_h264Enc		*	pObj	=	NULL;	
	UMC::Status status;
	TCHAR  tBuf[128]  =  _T(  ""  );
 

	 VIDEO_COMPRESSOR_cfgCommon  *  pVideoCfgCommon  =  (  VIDEO_COMPRESSOR_cfgCommon  *  )pVideoCompressorCfg_reserved;
 

	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->var.pObj  )  return  -1;

	//
	QDC_OBJ_INFO	&		qdcObjInfo  =  *pQdcObjInfo;
	
	memset(  &qdcObjInfo,  0,  sizeof(  qdcObjInfo  )  );
	pObj  =  (  QDC_OBJ_h264Enc  *  )malloc(  sizeof(  QDC_OBJ_h264Enc  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	qdcObjInfo.var.pObj  =  pObj;

	//  qdcObjInfo.
	qdcObjInfo.var.cbOutputBuffer  =  pVh_decompress->bih.biSizeImage;
	qdcObjInfo.var.cbInputBuffer  =  qdcObjInfo.var.cbOutputBuffer;

	//  2011/12/12
	//pObj->ucbFlippedImg  =  pVideoCfgCommon->ucbOutputFlippedImg;

	//  2012/11/08
	if  (  pVideoCfgCommon->usMaxFps_toShareBmp  >=  24  )  {
		if  (  pVh_decompress->bih.biWidth  >=  1280  &&  pVh_decompress->bih.biHeight  >=  720  )  {
			_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "w %d, h %d, %dfps can't be supported"  ),  (  int  )pVh_decompress->bih.biWidth,  (  int   )pVh_decompress->bih.biHeight,    (  int  )pVideoCfgCommon->usMaxFps_toShareBmp  );
			tmp_showInfo(  tBuf  );
			goto errLabel;
		}
	}

	//
	memcpy(  pVh_compress,  pVh_decompress,  sizeof(  pVh_compress[0]  )  );
	pVh_compress->bih.biCompression  =   CONST_fourcc_h264;


	UMC::H264VideoEncoder *  pH264Encoder  =  NULL;
	UMC::VideoEncoderParams  *pEncoderParams = NULL;


	try  {
	//
	pObj->pEncoder  =  new  UMC::H264VideoEncoder;; 
	if  (  !pObj->pEncoder  )  goto  errLabel;
	//
	pH264Encoder  =  (  UMC::H264VideoEncoder  *  )pObj->pEncoder;
	//

	//  2012/09/16
	pObj->pParams  =  new  EncoderParams;	//  params;
	if  (  !pObj->pParams  )  goto  errLabel;

	EncoderParams  &kkparams  =  *(  EncoderParams  *  )pObj->pParams;
	kkparams.videoStreamType  =  UMC::H264_VIDEO;

	//
	pObj->pVideoEncoderParams  =  new  UMC::H264EncoderParams;
	if  (  !pObj->pVideoEncoderParams  )  goto  errLabel;

	pEncoderParams  =  (  UMC::H264EncoderParams  *  )pObj->pVideoEncoderParams;

	//
	 pObj->pVideoProc  =  new  UMC::VideoProcessing;	//      videoProc;
	 if  (  !pObj->pVideoProc  )  goto  errLabel;
	 pObj->pDataIn  =  new  UMC::VideoData;			//            dataIn;
	 if  (  !pObj->pDataIn  )  goto  errLabel;
	 pObj->pDataCvt  =  new  UMC::VideoData;			//            dataCvt;
	 if  (  !pObj->pDataCvt  )  goto  errLabel;
	 pObj->pDataOut  =  new  UMC::MediaData;			//            dataOut;
	 if  (  !pObj->pDataOut  )  goto  errLabel;


	 pObj->pVccParams  =  new  UMC::VideoColorConversionParams;		// vccParams;
	 if  (  !pObj->pVccParams  )  goto  errLabel;

	}
	catch  (  ...  )  {
		tmp_showInfo(  _T(  "qdcInitCompressVideo: new failed"  )  );
		goto  errLabel;
	}


	//	
	int  imgWidth  =  pVh_decompress->bih.biWidth;
	int  imgHeight  =  pVh_decompress->bih.biHeight;

	//
#if  0	  
	pVideoEncParams->m_info.videoInfo.m_iWidth  = pParams->size.width;
    pVideoEncParams->m_info.videoInfo.m_iHeight = pParams->size.height;
    pVideoEncParams->m_info.fFramerate          = pParams->fFramerate;
    pVideoEncParams->m_info.iBitrate            = pParams->iBitrate;
    pVideoEncParams->m_iThreads                 = pParams->iThreads;
    pVideoEncParams->m_iFlags                   = pParams->iFlags;

    pVideoEncParams->ReadParams(pParams->pParser);
#endif



	UMC::H264EncoderParams &Params  =  *(  UMC::H264EncoderParams  *  )pObj->pVideoEncoderParams;

#if  0
   Params.key_frame_controls.method=1;
   Params.info.clip_info.height=imgHeight;
   Params.info.clip_info.width=imgWidth;
   Params.info.bitrate = 1000000;
   Params.numThreads = 1; 
   
   // tmp   
   Params.key_frame_controls.interval  =  20;
   Params.key_frame_controls.idr_interval  =  1;

#elif  10
   //  Params.rate_controls.method  =  1;				//  .key_frame_controls.method=1;
   Params.m_info.videoInfo.m_iHeight=imgHeight;
   Params.m_info.videoInfo.m_iWidth=imgWidth;
   Params.m_info.iBitrate = 0;
   Params.m_iThreads = 0;				//  2011/09/04 
   
   // tmp   
   Params.key_interval  =  pVideoCfgCommon->usMaxFps_toShareBmp  *  1;		//.key_frame_controls.interval  =  pVideoCfgCommon->usMaxFps_toShareBmp  *  3;		// 4frame/s;10s跟踪时间,就是40interval;
   Params.idr_interval  =  0;			//  .key_frame_controls.idr_interval  =  1;
   //  Params.profile_idc  =  (  UMC::H264_PROFILE_IDC  )pVideoCfgCommon->profile_idc;								//  100 0             // profile_idc (77-main, 100-high); level_idc (set 0 for automatic selection) (check that num_ref_frames and frame size are in accordance with the level)  
   Params.m_info.fFramerate  =  pVideoCfgCommon->usMaxFps_toShareBmp;					//  5                 // frame_rate_code [0,8] (0-30 fps,1-15 fps,2-24 fps,3-25 fps,4-30 fps,5-30 fps,6-50 fps,7-60 fps,8-60 fps)
   //  Params.level_idc  =  13;

   //  2012/09/18
#ifdef  _DEBUG
	#if  0
		imgWidth  =  720;	//  768;
		imgHeight  =  576;
	#endif
#endif

   //
   //if  (  pVideoCfgCommon->ucbScreenSharing  )  
		if  (  isCapTypeScreen(  pVideoCfgCommon->uiCapType  )  )	//  2014/12/02
   {
	   if  (  pVideoCfgCommon->iAvgBitrate  )  Params.m_info.iBitrate  =  pVideoCfgCommon->iAvgBitrate;
	   else  Params.m_info.iBitrate  =  300000;
		}
   else  if  (  isCapTypeMediaFile(  pVideoCfgCommon->uiCapType  )
			 ||  isCapTypeMediaDevice(  pVideoCfgCommon->uiCapType  )  )  
			{
				if  (  pVideoCfgCommon->iAvgBitrate  )  Params.m_info.iBitrate  =  pVideoCfgCommon->iAvgBitrate;
				else  Params.m_info.iBitrate  =  800000;			//  2012/02/08
			}
   else    
   {
	   Params.m_info.iBitrate  =  (((  imgWidth  *  imgHeight  )  *  Params.m_info.fFramerate  /  CONST_bp_compression  )  / 10  )  *  10000;
	   if  (  1
		   //  &&  isSubCapType_webcam(  pVideoCfgCommon->uiSubCapType  )  
		   &&  (  Params.m_info.fFramerate  >=  15  )  )  
	   {
		   Params.m_info.iBitrate  =  Params.m_info.iBitrate  *  0.54; 
	   }
   }

   //
   _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "bitrate: %d. key_int: %d"  ),  Params.m_info.iBitrate,  Params.key_interval  );
   tmp_showInfo(  tBuf  );


#elif  0
   {
	   TCHAR  tBuf[15];
	   int  result;
   
   	   result = tmp_qyGetRegCfg1(  HKEY_LOCAL_MACHINE,  _T(  "SOFTWARE\\QYCX\\misClient\\Scheduler"  ),  _T(  "bitrate"  ),  (  LPBYTE  )tBuf,  sizeof(  tBuf  ),  NULL  );
	   if  (  !result  )Params.info.bitrate  =  _ttoi(  tBuf  );

	   result = tmp_qyGetRegCfg1(  HKEY_LOCAL_MACHINE,  _T(  "Software\\QYCX\\misClient\\Scheduler"  ),  _T(  "fps"  ),  (  LPBYTE  )tBuf,  sizeof(  tBuf  ),  NULL  );

	   if  (  !result  )  
	   {
		   Params.key_frame_controls.interval  =  _ttoi(  tBuf  )  *  3;
		   Params.info.framerate  =  _ttoi(  tBuf  );
	   }

	   result = tmp_qyGetRegCfg1(  HKEY_LOCAL_MACHINE,  _T(  "Software\\QYCX\\misClient\\Scheduler"  ),  _T(  "profileIdc"  ),  (  LPBYTE  )tBuf,  sizeof(  tBuf  ),  NULL  );
	   if  (  !result  )  Params.profile_idc  =  (  UMC::H264_PROFILE_IDC  )_ttoi(  tBuf  );

	   if  (  Params.profile_idc  ==  UMC::H264_PROFILE_HIGH  )  {
		   Params.B_frame_rate  =  0;						//  3 1   //  Number of B frames between I (or P) and next P, treat B as a reference (only 0 is supported!) 
		   Params.treat_B_as_reference  =  0;
		   Params.num_ref_frames  =   2;					//  4 1 0  // num_ref_frames (2-16), minimum length of list1 for backward prediction (only 1 is supported!), number of slices.
		   Params.num_ref_to_start_code_B_slice  =  1;
		   Params.num_slices  = (Ipp16s)1;   //  ---------------------------------------------------------

		   Params.level_idc  =  30;
		   Params.info.framerate  =  pVideoCfgCommon->usMaxFps_toShareBmp;					//  5                 // frame_rate_code [0,8] (0-30 fps,1-15 fps,2-24 fps,3-25 fps,4-30 fps,5-30 fps,6-50 fps,7-60 fps,8-60 fps)

		   // tmp   
      	   Params.chroma_format_idc  =  1;					//  1 8 8             /* High profile: chroma_format_idc (0 - monochrom, 1 - 420, 2 - 422), bit_depth_luma [8,12], bit_depth_chroma [8,12] 
		   Params.bit_depth_luma  =   8;
		   Params.bit_depth_chroma  =  8;

		   Params.aux_format_idc  =  0;						//  0 8 0 0 0         /* High profile: aux_format_idc: [0,3], bit_depth_aux: [8,12], alpha_incr_flag: 0, 1; alpha_opaque_value: [0, 2^(bit_depth_aux + 9) -1]; alpha_transparent_value: [0, 2^(bit_depth_aux + 9) - 1]  
		   Params.bit_depth_aux =  8;
		   Params.alpha_incr_flag  =  0;
		   Params.alpha_opaque_value  =  0;
		   Params.alpha_transparent_value  =  0;

		   Params.rate_controls.method  =  UMC::H264_RCM_VBR;	//  2 0 0 0 1000000   /* RC method(0 - quant_codes, 1 - CBR MBwise, 2 - CBR framewise, 3 - Debug); start qp values for I, P, B slices; bitrate (bits per second) 
		   Params.rate_controls.quantI  =  30;
		   Params.rate_controls.quantP  =  30;
		   Params.rate_controls.quantB  =  30;

		   Params.use_weighted_pred  =  0;					//  0 0 0             /* weighted prediction, weighted biprediction implicit weighted biprediction (not supported!)
   		   Params.use_weighted_bipred  =  0;
   		   Params.use_implicit_weighted_bipred  =  0;

   		   Params.direct_pred_mode  =   (Ipp8s)1;					//  1 0               /* direct type (0 - temporal 1 - spatial 2 - auto); direct_inference_flag 
   		   Params.use_direct_inference  =  1;


   		   Params.mv_search_method  =  2;					//  2 1 8 8           /* ME method (1-6), subblock split, search x,search_y 
   		   Params.me_split_mode  =  0;						//0 – 16x16 only,1 – down to 8x8,2 – down to 4x4.
   		   Params.me_search_x  =  8;
   		   Params.me_search_y  =  8;

   		   Params.deblocking_filter_idc  =   (Ipp8s)0;				//  0 0 0             /* disable_deblocking_idc: 1-- off, 0 - on, 2 -- on(without crossing slice boundaries); deblocking_filter_alpha, deblocking_filter_beta
   		   Params.deblocking_filter_alpha  =   (Ipp8s)0;
   		   Params.deblocking_filter_beta  =   (Ipp8s)0;

		   Params.transform_8x8_mode_flag  =  TRUE;			//	1 0 0             /* High profile: transform_8x8_mode: 0 -- off, 1 - on; 0 -- use standard, 1 -- use default scaling matrices for 8x8 quantization; qpprime_y_zero_transform_bypass_flag: (0, 1) 
   		   Params.use_default_scaling_matrix  =  0;
   		   Params.qpprime_y_zero_transform_bypass_flag  =  0;

   		   Params.entropy_coding_mode  =  0;
   		   Params.cabac_init_idc  =   (Ipp8s)2;

   		   Params.coding_type = 0;
   		   Params.m_QualitySpeed = 0;

	   }
   }

#elif  0
   Params.key_frame_controls.method=1;
   Params.info.clip_info.height=imgHeight;
   Params.info.clip_info.width=imgWidth;
   Params.info.bitrate = 0;
   Params.numThreads = 1; 

   TCHAR  tBuf[15];
   
   int result = tmp_qyGetRegCfg1(  HKEY_LOCAL_MACHINE,  _T(  "SOFTWARE\\QYCX\\misClient\\Scheduler"  ),  _T(  "bitrate"  ),  (  LPBYTE  )tBuf,  sizeof(  tBuf  ),  NULL  );

   Params.info.bitrate  =  _ttoi(  tBuf  );
   // tmp   
   Params.key_frame_controls.interval  =  pVideoCfgCommon->usMaxFps_toShareBmp  *  3;		// 4frame/s;10s跟踪时间,就是40interval;
   Params.key_frame_controls.idr_interval  =  1;
   Params.B_frame_rate  =  0;						//  3 1   //  Number of B frames between I (or P) and next P, treat B as a reference (only 0 is supported!) 
   Params.treat_B_as_reference  =  0;
   Params.num_ref_frames  =   4;					//  4 1 0  // num_ref_frames (2-16), minimum length of list1 for backward prediction (only 1 is supported!), number of slices.
   //  Params.num_ref_to_start_code_B_slice  =  1;
   
   Params.profile_idc  =  UMC::H264_PROFILE_HIGH;	//  100 0             // profile_idc (77-main, 100-high); level_idc (set 0 for automatic selection) (check that num_ref_frames and frame size are in accordance with the level)  
   Params.level_idc  =  0;
   Params.info.framerate  =  pVideoCfgCommon->usMaxFps_toShareBmp;					//  5                 // frame_rate_code [0,8] (0-30 fps,1-15 fps,2-24 fps,3-25 fps,4-30 fps,5-30 fps,6-50 fps,7-60 fps,8-60 fps)

   Params.num_slices  = (Ipp16s)2;   //  ---------------------------------------------------------
   Params.entropy_coding_mode  =  1;

#elif 0
   Params.key_frame_controls.method=1;
   Params.info.clip_info.height=imgHeight;
   Params.info.clip_info.width=imgWidth;
   Params.info.bitrate = 1000000;
   Params.numThreads = 1; 

   Params.key_frame_controls.interval  =  pVideoCfgCommon->usMaxFps_toShareBmp  *  3;		// 4frame/s;10s跟踪时间,就是40interval;
   Params.key_frame_controls.idr_interval  =  1;
   Params.B_frame_rate  =  0;						//  3 1   //  Number of B frames between I (or P) and next P, treat B as a reference (only 0 is supported!) 
   Params.treat_B_as_reference  =  0;
   Params.num_ref_frames  =   2;					//  4 1 0  // num_ref_frames (2-16), minimum length of list1 for backward prediction (only 1 is supported!), number of slices.
   Params.num_ref_to_start_code_B_slice  =  1;
   Params.num_slices  = (Ipp16s)1;   //  ---------------------------------------------------------
   
   Params.profile_idc  =  UMC::H264_PROFILE_HIGH;	//  100 0             // profile_idc (77-main, 100-high); level_idc (set 0 for automatic selection) (check that num_ref_frames and frame size are in accordance with the level)  
   Params.level_idc  =  30;
   Params.info.framerate  =  pVideoCfgCommon->usMaxFps_toShareBmp;					//  5                 // frame_rate_code [0,8] (0-30 fps,1-15 fps,2-24 fps,3-25 fps,4-30 fps,5-30 fps,6-50 fps,7-60 fps,8-60 fps)

   {
	   TCHAR  tBuf[15];
   
   	   int result = tmp_qyGetRegCfg1(  HKEY_LOCAL_MACHINE,  _T(  "SOFTWARE\\QYCX\\misClient\\Scheduler"  ),  _T(  "bitrate"  ),  (  LPBYTE  )tBuf,  sizeof(  tBuf  ),  NULL  );
	   if  (  !result  )Params.info.bitrate  =  _ttoi(  tBuf  );

	   result = tmp_qyGetRegCfg1(  HKEY_LOCAL_MACHINE,  _T(  "Software\\QYCX\\misClient\\Scheduler"  ),  _T(  "fps"  ),  (  LPBYTE  )tBuf,  sizeof(  tBuf  ),  NULL  );

	   if  (  !result  )  
	   {
		   Params.key_frame_controls.interval  =  _ttoi(  tBuf  )  *  3;
		   Params.info.framerate  =  _ttoi(  tBuf  );
	   } 
   }
   // tmp   

      Params.chroma_format_idc  =  1;					//  1 8 8             /* High profile: chroma_format_idc (0 - monochrom, 1 - 420, 2 - 422), bit_depth_luma [8,12], bit_depth_chroma [8,12] 
   Params.bit_depth_luma  =   8;
   Params.bit_depth_chroma  =  8;

   Params.aux_format_idc  =  0;						//  0 8 0 0 0         /* High profile: aux_format_idc: [0,3], bit_depth_aux: [8,12], alpha_incr_flag: 0, 1; alpha_opaque_value: [0, 2^(bit_depth_aux + 9) -1]; alpha_transparent_value: [0, 2^(bit_depth_aux + 9) - 1]  
   Params.bit_depth_aux =  8;
   Params.alpha_incr_flag  =  0;
   Params.alpha_opaque_value  =  0;
   Params.alpha_transparent_value  =  0;

   Params.rate_controls.method  =  UMC::H264_RCM_VBR;	//  2 0 0 0 1000000   /* RC method(0 - quant_codes, 1 - CBR MBwise, 2 - CBR framewise, 3 - Debug); start qp values for I, P, B slices; bitrate (bits per second) 
   Params.rate_controls.quantI  =  30;
   Params.rate_controls.quantP  =  30;
   Params.rate_controls.quantB  =  30;

   Params.use_weighted_pred  =  0;					//  0 0 0             /* weighted prediction, weighted biprediction implicit weighted biprediction (not supported!)
   Params.use_weighted_bipred  =  0;
   Params.use_implicit_weighted_bipred  =  0;

   Params.direct_pred_mode  =   (Ipp8s)1;					//  1 0               /* direct type (0 - temporal 1 - spatial 2 - auto); direct_inference_flag 
   Params.use_direct_inference  =  1;


   Params.mv_search_method  =  2;					//  2 1 8 8           /* ME method (1-6), subblock split, search x,search_y 
   Params.me_split_mode  =  0;						//0 – 16x16 only,1 – down to 8x8,2 – down to 4x4.
   Params.me_search_x  =  8;
   Params.me_search_y  =  8;

   Params.deblocking_filter_idc  =   (Ipp8s)0;				//  0 0 0             /* disable_deblocking_idc: 1-- off, 0 - on, 2 -- on(without crossing slice boundaries); deblocking_filter_alpha, deblocking_filter_beta
   Params.deblocking_filter_alpha  =   (Ipp8s)0;
   Params.deblocking_filter_beta  =   (Ipp8s)0;

   Params.transform_8x8_mode_flag  =  TRUE;			//	1 0 0             /* High profile: transform_8x8_mode: 0 -- off, 1 - on; 0 -- use standard, 1 -- use default scaling matrices for 8x8 quantization; qpprime_y_zero_transform_bypass_flag: (0, 1) 
   Params.use_default_scaling_matrix  =  0;
   Params.qpprime_y_zero_transform_bypass_flag  =  0;

   Params.entropy_coding_mode  =  0;
   Params.cabac_init_idc  =   (Ipp8s)2;

   Params.coding_type = 0;
   Params.m_QualitySpeed = 0;

#elif  0
   Params.info.clip_info.height=imgHeight;
   Params.info.clip_info.width=imgWidth;
   //  Params.info.bitrate = 2000000;
   //  Params.numThreads = 1; 
   
   // tmp   
   //  Params.numFramesToEncode  =  300000;				//  300               /* number of frames to encode */

   Params.key_frame_controls.method  = 1;
   Params.key_frame_controls.interval  =  200;		//  1 200 1  /*  1(reserved) , N (# of frames in between I frames), IDR interval. */
   Params.key_frame_controls.idr_interval  =  0;
 
   Params.B_frame_rate  =  1;						//  3 1   //  Number of B frames between I (or P) and next P, treat B as a reference (only 0 is supported!) 
   Params.treat_B_as_reference  =  1;

   Params.num_ref_frames  =   2;					//  4 1 0  // num_ref_frames (2-16), minimum length of list1 for backward prediction (only 1 is supported!), number of slices.
   Params.num_ref_to_start_code_B_slice  =  1;
   Params.num_slices  = (Ipp16s)1;   //  ---------------------------------------------------------


   Params.profile_idc  =  UMC::H264_PROFILE_BASELINE;   //UMC::H264_PROFILE_HIGH;	//  100 0             // profile_idc (77-main, 100-high); level_idc (set 0 for automatic selection) (check that num_ref_frames and frame size are in accordance with the level)  
   Params.level_idc  =  (Ipp8s)50;


   Params.info.framerate  =  30;					//  5                 // frame_rate_code [0,8] (0-30 fps,1-15 fps,2-24 fps,3-25 fps,4-30 fps,5-30 fps,6-50 fps,7-60 fps,8-60 fps)


   Params.chroma_format_idc  =  1;					//  1 8 8             /* High profile: chroma_format_idc (0 - monochrom, 1 - 420, 2 - 422), bit_depth_luma [8,12], bit_depth_chroma [8,12] 
   Params.bit_depth_luma  =   8;
   Params.bit_depth_chroma  =  8;


   Params.aux_format_idc  =  0;						//  0 8 0 0 0         /* High profile: aux_format_idc: [0,3], bit_depth_aux: [8,12], alpha_incr_flag: 0, 1; alpha_opaque_value: [0, 2^(bit_depth_aux + 9) -1]; alpha_transparent_value: [0, 2^(bit_depth_aux + 9) - 1]  
   Params.bit_depth_aux =  8;
   Params.alpha_incr_flag  =  0;
   Params.alpha_opaque_value  =  0;
   Params.alpha_transparent_value  =  0;


   Params.rate_controls.method  =  UMC::H264_RCM_QUANT;  //  H264_Rate_Control_Method)2;	//(H264_Rate_Control_Method)2;  2 0 0 0 1000000   /* RC method(0 - quant_codes, 1 - CBR MBwise, 2 - CBR framewise, 3 - Debug); start qp values for I, P, B slices; bitrate (bits per second) 
   Params.rate_controls.quantI  =   (Ipp8s) 30;
   Params.rate_controls.quantP  =   (Ipp8s) 30;
   Params.rate_controls.quantB  =   (Ipp8s) 30;
   Params.info.bitrate = 1000000;


   Params.mv_search_method  =  2;					//  2 1 8 8           /* ME method (1-6), subblock split, search x,search_y 
   Params.me_split_mode  =  0;						//0 – 16x16 only,1 – down to 8x8,2 – down to 4x4.
   Params.me_search_x  =  8;
   Params.me_search_y  =  8;

   Params.use_weighted_pred  =  0;					//  0 0 0             /* weighted prediction, weighted biprediction implicit weighted biprediction (not supported!)
   Params.use_weighted_bipred  =  0;
   Params.use_implicit_weighted_bipred  =  0;


   Params.direct_pred_mode  =   (Ipp8s)1;					//  1 0               /* direct type (0 - temporal 1 - spatial 2 - auto); direct_inference_flag 
   Params.use_direct_inference  =  1;


   Params.deblocking_filter_idc  =   (Ipp8s)0;				//  0 0 0             /* disable_deblocking_idc: 1-- off, 0 - on, 2 -- on(without crossing slice boundaries); deblocking_filter_alpha, deblocking_filter_beta
   Params.deblocking_filter_alpha  =   (Ipp8s)0;
   Params.deblocking_filter_alpha = Params.deblocking_filter_alpha&~1; // must be even, since a value div2 is coded.
   Params.deblocking_filter_beta  =   (Ipp8s)0;
   Params.deblocking_filter_beta = Params.deblocking_filter_beta&~1;


   Params.transform_8x8_mode_flag  =  TRUE;			//	1 0 0             /* High profile: transform_8x8_mode: 0 -- off, 1 - on; 0 -- use standard, 1 -- use default scaling matrices for 8x8 quantization; qpprime_y_zero_transform_bypass_flag: (0, 1) 
   Params.use_default_scaling_matrix  =  0;
   Params.qpprime_y_zero_transform_bypass_flag  =  0;



   Params.entropy_coding_mode  =   (Ipp8s)1;				//  1 2               /* entropy coding mode (0-cavlc,1-cabac); cabac_init_idc (0,1,2) 
   Params.cabac_init_idc  =   (Ipp8s)2;


   Params.coding_type  =   (Ipp8s)0;						//  0                 /* picture coding type (0 - only FRM, 1 - only FLD , 2 - only AFRM, 3  - pure PicAFF(no MBAFF) 4 PicAFF + MBAFF). Only 0 (FRM) is supported! 

   Params.m_QualitySpeed  =   (Ipp8s)1;						//  1 0               /* speed/quality grade [0,3] (0-maximum speed, 3-maximum quality); OptimalQuantization (0, 1) 
   Params.quant_opt_level  =  0;
   
	#elif 0
{
	Params.key_frame_controls.method    = UMC::H264_KFCM_INTERVAL;
Params.key_frame_controls.interval  = 250; // for safety
Params.key_frame_controls.idr_interval = 0;
Params.B_frame_rate = 0;
Params.treat_B_as_reference = 1;
Params.num_ref_frames = 1;
Params.num_ref_to_start_code_B_slice = 1;
Params.num_slices = 0;  // Autoselect
Params.profile_idc = UMC::H264_PROFILE_MAIN;
Params.level_idc = 0;  //Autoselect
Params.chroma_format_idc = 1; // YUV 420.
Params.bit_depth_luma = 8;
Params.bit_depth_chroma = 8;
Params.aux_format_idc = 0;
Params.bit_depth_aux = 8;
Params.alpha_incr_flag = 0;
Params.alpha_opaque_value = 0;
Params.alpha_transparent_value = 0;
Params.rate_controls.method = UMC::H264_RCM_VBR;
Params.rate_controls.quantI = 20;
Params.rate_controls.quantP = 20;
Params.rate_controls.quantB = 20;
Params.info.bitrate = 2222222;
Params.mv_search_method = 2;
Params.me_split_mode = 0;
Params.me_search_x = 8;
Params.me_search_y = 8;
Params.use_weighted_pred = 0;
Params.use_weighted_bipred = 0;
Params.use_implicit_weighted_bipred = 0;
Params.direct_pred_mode = 0;
Params.use_direct_inference = 1;
Params.deblocking_filter_idc  = 0;    // 0 is "on". 1 - "off"
Params.deblocking_filter_alpha  = 2;
Params.deblocking_filter_beta  = 2;
Params.transform_8x8_mode_flag = 1;
Params.use_default_scaling_matrix = 0;
Params.qpprime_y_zero_transform_bypass_flag =0;
Params.entropy_coding_mode = 1;
Params.cabac_init_idc = 1;
Params.coding_type = 0;
Params.m_do_weak_forced_key_frames = false;
Params.write_access_unit_delimiters = 0;
Params.use_transform_for_intra_decision = true;
Params.numFramesToEncode = 0;
Params.m_QualitySpeed = 0;
Params.quant_opt_level = 0;
}
#endif
   //
   if((status = pH264Encoder->Init(&Params))!=UMC::UMC_OK)  goto  errLabel;


   //
   status = pH264Encoder->GetInfo(pEncoderParams);
   if(status != UMC::UMC_OK)  goto  errLabel;


   //
   UMC::VideoProcessing  &  videoProc  =  *(  UMC::VideoProcessing  *  )pObj->pVideoProc;
   
   videoProc.AddFilter(UMC::FILTER_COLOR_CONVERTER, (UMC::BaseCodecParams*)pObj->pVccParams);

   UMC::VideoData  &  dataIn  =  *(  UMC::VideoData  *  )pObj->pDataIn;
   UMC::VideoData  &  dataCvt  =  *(  UMC::VideoData  *  )pObj->pDataCvt;
   UMC::MediaData  &  dataOut  =  *(  UMC::MediaData  *  )pObj->pDataOut;


   if  (  dataCvt.Init(imgWidth,imgHeight,UMC::YV12,8)  )  goto  errLabel;
   if  (  dataCvt.Alloc()  )  goto  errLabel;

   if  (  dataIn.Init(&pEncoderParams->m_info.videoInfo)  )  goto  errLabel;
    dataIn.m_iWidth  = imgWidth;
    dataIn.m_iHeight = imgHeight;
	if  (  dataIn.Alloc()  )  goto  errLabel;

	int  iFrameSize;
    iFrameSize = dataIn.GetMappingSize();
    if  (  dataOut.Alloc(iFrameSize + 1000000)  )  goto  errLabel;

	
	//
	makeBmpInfoHeader_yv12(  12,  pVh_compress->bih.biWidth,  pVh_compress->bih.biHeight,  &pObj->inputForEnc.vh_decompress_real.bih  );
	pObj->inputForEnc.uiBufSize  =  pObj->inputForEnc.vh_decompress_real.bih.biSizeImage;
	pObj->inputForEnc.pBuf  =  (  char  *  )malloc(  pObj->inputForEnc.uiBufSize  );
	if  (  !pObj->inputForEnc.pBuf  )  goto  errLabel;

	//	
	if  (  !pObj->common.outs[0].pBuf  )  {
		pObj->common.outs[0].pBuf  =  (  BYTE  *  )malloc(  qdcObjInfo.var.cbOutputBuffer  );
		if  (  !pObj->common.outs[0].pBuf  )  goto  errLabel;
	}

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
	QDC_OBJ_h264Enc	*	pObj	=	(  QDC_OBJ_h264Enc  *  )pQdcObjInfo->var.pObj;

	if  (  pObj  )  {
		//
		//  2012/09/15
		if  (  pObj->pEncoder  )  {
			UMC::H264VideoEncoder *  pH264Encoder  =  (  UMC::H264VideoEncoder  *  )pObj->pEncoder;
			pH264Encoder->Close(  );
		}
		if  (  pObj->pParams  )  {
			EncoderParams  *  pParams  =  (  EncoderParams  *  )pObj->pParams;
			delete  pParams;
			pObj->pParams  =  NULL;
		}
		if  (  pObj->pVideoEncoderParams  )  {
			UMC::VideoEncoderParams  *pEncoderParams = (  UMC::VideoEncoderParams  *  )pObj->pVideoEncoderParams;
			delete  pEncoderParams;
			pObj->pVideoEncoderParams  =  NULL;
		}
		if  (  pObj->pVideoProc  )  {
			UMC::VideoProcessing  *  pVideoProc  =  (  UMC::VideoProcessing  *  )pObj->pVideoProc;
			delete  pVideoProc;
			pObj->pVideoProc  =  NULL;
		}
		if  (  pObj->pDataIn  )  {
			UMC::VideoData  *  pDataIn  =  (  UMC::VideoData  *  )pObj->pDataIn;
			delete  pDataIn;
			pObj->pDataIn  =  NULL;
		}
		if  (  pObj->pDataCvt  )  {
			UMC::VideoData  *  pDataCvt  =  (  UMC::VideoData  *  )pObj->pDataCvt;
			delete  pDataCvt;
			pObj->pDataCvt  =  NULL;
		}
		if  (  pObj->pDataOut  )  {
			UMC::MediaData  *  pDataOut  =  (  UMC::MediaData  *  )pObj->pDataOut;
			delete  pDataOut;
			pObj->pDataOut  =  NULL;
		}
		if  (  pObj->pVccParams  )  {
			UMC::VideoColorConversionParams  *  pVccParams  =  (  UMC::VideoColorConversionParams  *  )pObj->pVccParams;
			delete  pVccParams;
			pObj->pVccParams  =  NULL;
		}


		//
		if  (  pObj->pEncoder  )  {
			UMC::H264VideoEncoder *  pH264Encoder  =  (  UMC::H264VideoEncoder  *  )pObj->pEncoder;
			delete  pH264Encoder;
			pObj->pEncoder  =  NULL;
		}

		//
		qdcFreeOutputs(  pQdcObjInfo  );
		//
		if  (  pObj->inputForEnc.pBuf  )  {
			free(  pObj->inputForEnc.pBuf  );  pObj->inputForEnc.pBuf  =  NULL;
		}
		//
		free(  pObj  );	
	}
	pQdcObjInfo->var.pObj  =  NULL;

	return  0;
}



int  yv12ToRgb24(  unsigned char  *  yuv,  unsigned char  *  rgb,  int  width,  int  height  );
int  yv12ToRgb24_ipp(  unsigned char  *  yuv,  unsigned char  *  rgb,  int  width,  int  height  );
int  rgb24ToYv12(  unsigned char  *  rgb,  unsigned char  *  yuv,  int  width,  int  height,  BOOL  bFlip  );
	
 
//  typedef  int  (  *PF_qdcCompressVideo  )(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs  );	//  2012/06/17
extern  "C"  int  __declspec(  dllexport  )qdcCompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs  )
{
	QDC_OBJ_h264Enc	*	pObj	=	(  QDC_OBJ_h264Enc  *  )pQdcObjInfo->var.pObj;

	if  (  pBmpInfo_input->bmiHeader.biSizeImage  >  pQdcObjInfo->var.cbInputBuffer  )  return  -1;


#if  0

	rgb24ToYv12(  pInput,  (  unsigned  char  *  )pObj->inputForEnc.pBuf,  pBmpInfo_input->bmiHeader.biWidth,  pBmpInfo_input->bmiHeader.biHeight,  TRUE  );
	//  yv12ToRgb24(  (  unsigned  char  *  )pObj->inputForEnc.pBuf,  pInput,  pBmpInfo_input->bmiHeader.biWidth,  pBmpInfo_input->bmiHeader.biHeight  );


	//  int  index  =  0;
	//  int  VideoDataSize  =  pQdcObjInfo->cbOutputBuffer;
	//  myEncodeStream(  (  UMC::H264VideoEncoder  *  )pObj->pEncoder,  (  Ipp8u  *  )pObj->inputForEnc.pBuf,  pBmpInfo_input->bmiHeader.biWidth,  pBmpInfo_input->bmiHeader.biHeight,  1,  pObj->common.outs[index].pBuf,  VideoDataSize  );
	//  pObj->common.outs[index].len  =  VideoDataSize;

	myEncodeStream(  pQdcObjInfo,  (  Ipp8u  *  )pObj->inputForEnc.pBuf,  pBmpInfo_input->bmiHeader.biWidth,  pBmpInfo_input->bmiHeader.biHeight,  1  );
#endif

	if  (  pBmpInfo_input->bmiHeader.biCompression  ==  CONST_fourcc_YV12  )  {
		myEncodeStream(  pQdcObjInfo,  (  Ipp8u  *  )pInput,  pBmpInfo_input->bmiHeader.biWidth,  pBmpInfo_input->bmiHeader.biHeight,  1  );
		}
	else  if  (  pBmpInfo_input->bmiHeader.biCompression  ==  BI_RGB
		&&  pBmpInfo_input->bmiHeader.biBitCount  ==  24  )
	{
		if  (  pObj->ucbFlippedImg  )  {
			rgb24ToYv12_ipp(  pInput,  (  unsigned  char  *  )pObj->inputForEnc.pBuf,  pBmpInfo_input->bmiHeader.biWidth,  pBmpInfo_input->bmiHeader.biHeight,  TRUE  );
		    }
		else  {
			  rgb24ToYv12(  pInput,  (  unsigned  char  *  )pObj->inputForEnc.pBuf,  pBmpInfo_input->bmiHeader.biWidth,  pBmpInfo_input->bmiHeader.biHeight,  FALSE  );
		}
	
		myEncodeStream(  pQdcObjInfo,  (  Ipp8u  *  )pObj->inputForEnc.pBuf,  pBmpInfo_input->bmiHeader.biWidth,  pBmpInfo_input->bmiHeader.biHeight,  1  );
	}
	else  {
		  OutputDebugString(  _T(  "compressVideo: input fmt err\n"  )  );
		  return  -1;
	}


#if  0
	int  index  =  0;
	memcpy(  pObj->outs[index].pBuf,  pInput,  pBmpInfo_input->bmiHeader.biSizeImage  );
	pObj->outs[index].len  =  pBmpInfo_input->bmiHeader.biSizeImage;
#endif

	return  0;
}



//  2014/02/26
extern  "C"  int  __declspec(  dllexport  )qdcInitDecompressVideo(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_compress,  QY_VIDEO_HEADER  *  pVh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{	
	int						iErr	=	-1;
	QDC_OBJ_h264Dec		*	pObj	=	NULL;
	//  UMC::Status status; 
	//  UMC::VideoDecoderParams Params; 
	UMC::H264VideoDecoder  * pH264Decoder  =  NULL; 

	if  (  !pQdcObjInfo  )  return  -1;
	if  (  pQdcObjInfo->var.pObj  )  return  -1;
		
	//  2014/08/10
	void  *  pDebugStep  =  pQdcObjInfo->var.pDebugStep;
	//
	tmp_mySetDebugStep(  0,  pDebugStep,  101  );


	//
	VIDEO_COMPRESSOR_cfgCommon  *  pVideoCfgCommon  =  (  VIDEO_COMPRESSOR_cfgCommon  *  )pVideoCompressorCfg_reserved;


	//  2014/08/08
	memcpy(  &pQdcObjInfo->cfg.v,  pVideoCfgCommon,  sizeof(  pQdcObjInfo->cfg.v  )  );

	//
	pQdcObjInfo->var.ucbTransformFuncsOk  =  TRUE;


	//
	pObj  =  (  QDC_OBJ_h264Dec  *  )malloc(  sizeof(  QDC_OBJ_h264Dec  )  );
	if  (  !pObj  )  goto  errLabel;
	memset(  pObj,  0,  sizeof(  pObj[0]  )  );
	pQdcObjInfo->var.pObj  =  pObj;


	//
	pObj->ucCompressors  =  pVideoCfgCommon->ucCompressors;		//  2014/03/02
	//pObj->ucbFlipped  =  pVideoCfgCommon->ucbOutputFlippedImg;



	//
#if  10

	try  {
	//
	pH264Decoder  =  new  UMC::H264VideoDecoder;; 
	if  (  !pH264Decoder  )  goto  errLabel;
	pObj->pDecoder  =  pH264Decoder;

	//  2012/09/15
	pObj->pVideoDecoderParams  =  new  UMC::VideoDecoderParams;	// Params; 
	if  (  !pObj->pVideoDecoderParams  )  goto  errLabel;
	pObj->pVideoProc  =  new  UMC::VideoProcessing;				//	videoProc;
	if  (  !pObj->pVideoProc  )  goto  errLabel;
	pObj->pVccParams  =  new  UMC::VideoColorConversionParams;	// vccParams;
	if  (  !pObj->pVccParams  )  goto  errLabel;

	//
	UMC::VideoProcessing	&  videoProc  =  *(  UMC::VideoProcessing  *  )pObj->pVideoProc;
	UMC::VideoColorConversionParams &  vccParams  =  *(  UMC::VideoColorConversionParams  *  )pObj->pVccParams;

	if  (  !pObj->bInited_VideoProcessing  )  {
			//
			videoProc.AddFilter(UMC::FILTER_COLOR_CONVERTER, (UMC::BaseCodecParams*)&vccParams);
			pObj->bInited_VideoProcessing  =  TRUE;
	}

	//
	pObj->pDataIn  =  new  UMC::MediaData;	//            dataIn;
	if  (  !pObj->pDataIn  )  goto  errLabel;
	pObj->pDataOut  =  new  UMC::VideoData;	//            dataOut;
	if  (  !pObj->pDataOut  )  goto  errLabel;


#if  0  //  2014/02/26,因为w和h可能无法确定,所以,要移到解码的初始化后去.

	//
	//  qdcObjInfo.
	qdcObjInfo.cbOutputBuffer  =  pVh_decompress->bih.biSizeImage;
	qdcObjInfo.cbInputBuffer  =  qdcObjInfo.cbOutputBuffer;

	//
	int  imgWidth  =  pVh_decompress->bih.biWidth;
	int  imgHeight  =  pVh_decompress->bih.biHeight;

	//
	UMC::VideoData  *  pDataOut  =  (  UMC::VideoData  *  )pObj->pDataOut;

	if  (  pDataOut->Init(imgWidth,imgHeight,UMC::YV12,8)  )  goto  errLabel;
	//  if  (  pDataOut->Alloc(  )  )  goto  errLabel;
		
	//
	makeBmpInfoHeader_yv12(  12,  pVh_compress->bih.biWidth,  pVh_compress->bih.biHeight,  &pObj->outputForDec.vh_decompress_real.bih  );
	pObj->outputForDec.uiBufSize  =  pObj->outputForDec.vh_decompress_real.bih.biSizeImage;
	pObj->outputForDec.pBuf  =  (  char  *  )malloc(  pObj->outputForDec.uiBufSize  );
	if  (  !pObj->outputForDec.pBuf  )  goto  errLabel;


	//	
	if  (  !pObj->common.outs[0].pBuf  )  {
		pObj->common.outs[0].pBuf  =  (  BYTE  *  )malloc(  qdcObjInfo.cbOutputBuffer  );
		if  (  !pObj->common.outs[0].pBuf  )  goto  errLabel;
	}


#endif




	}
	catch  (  ...  )  {
			tmp_showInfo(  _T(  "qdcInitDecompressVideo failed, new failed"  )  );
			goto  errLabel;
	}
	



#endif


	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		qdcExitDecompressVideo(  pQdcObjInfo  );
	}
	if  (  !iErr  )  {
		//  memcpy(  pQdcObjInfo,  &qdcObjInfo,  sizeof(  pQdcObjInfo[0]  )  );
	}
	//
	tmp_mySetDebugStep(  0,  pDebugStep,  111  );

#if  0
	tmp_showInfo(  iErr  ?  _T(  "qdcInitDecVideo failed"  )  :  _T(  "qdcInitDecVideo ok"  )  );
#endif
	//
	return  iErr;
}



extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	//  2014/08/10
	void  *  pDebugStep  =  pQdcObjInfo->var.pDebugStep;
	//
	tmp_mySetDebugStep(  0,  pDebugStep,  201  );


	QDC_OBJ_h264Dec	*	pObj	=	(  QDC_OBJ_h264Dec  *  )pQdcObjInfo->var.pObj;

	if  (  pObj  )  {

		//  2012/09/15
		if  (  pObj->pDecoder  )  {
			UMC::H264VideoDecoder  *  pDecoder  =  (  UMC::H264VideoDecoder  *  )pObj->pDecoder;
			//  2014/10/04
			UMC::Status  sts  =  -1;
			sts  =  pDecoder->Reset(  );
			//
			pDecoder->Close(  );
		}

		//
		if  (  pObj->pDataIn  )  {
			UMC::MediaData  *  pDataIn  =  (  UMC::MediaData  *  )pObj->pDataIn;
			delete  pDataIn;
			pObj->pDataIn  =  NULL;
		}
		if  (  pObj->pDataOut  )  {
			UMC::VideoData  *  pDataOut  =  (  UMC::VideoData  *  )pObj->pDataOut;
			delete  pDataOut;
			pObj->pDataOut  =  NULL;
		}

		//
		if  (  pObj->pVideoDecoderParams  )  {
			UMC::VideoDecoderParams  *  pParams  =  (  UMC::VideoDecoderParams  *  )pObj->pVideoDecoderParams;
			delete  pParams;
			pObj->pVideoDecoderParams  =  NULL;
		}
		if  (  pObj->pVideoProc  )  {
			UMC::VideoProcessing  *  pVideoProc  =  (  UMC::VideoProcessing  *  )pObj->pVideoProc;
			delete  pVideoProc;
			pObj->pVideoProc  =  NULL;
		}
		if  (  pObj->pVccParams  )  {
			UMC::VideoColorConversionParams  *  pVccParams  =  (  UMC::VideoColorConversionParams  *  )pObj->pVccParams;
			delete  pVccParams;
			pObj->pVccParams  =  NULL;
		}
				
		//
		if  (  pObj->pDecoder  )  {
			UMC::H264VideoDecoder  *  pDecoder  =  (  UMC::H264VideoDecoder  *  )pObj->pDecoder;
			delete  pDecoder;
			pObj->pDecoder  =  NULL;
		}
		//
		qdcFreeOutputs(  pQdcObjInfo  );
		//
		if  (  pObj->outputForDec.pBuf  )  {
			free(  pObj->outputForDec.pBuf  );  pObj->outputForDec.pBuf  =  NULL;
		}
		//
		free(  pObj  );	
	}
	pQdcObjInfo->var.pObj  =  NULL;


	//  2014/08/10
	//
	tmp_mySetDebugStep(  0,  pDebugStep,  211  );


	return  0;
}

//typedef  int  (  *PF_qdcDecompressVideo  )(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs  );	//  2012/06/17
extern  "C"  int  __declspec(  dllexport  )qdcDecompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs  )
{
	QDC_OBJ_h264Dec	*	pObj		=	(  QDC_OBJ_h264Dec  *  )pQdcObjInfo->var.pObj;
	TCHAR				tBuf[256]	=	_T(  ""  );
		

	tmp_showInfo(  _T(  "Not supported: qdcDecompressVideo"  )  );
	return  -1;
#if  0
	//
	if  (  !pObj->common.bInited  )  {
		myDecodeStream_init(  pObj,  &pObj->common.bInited,  (  Ipp8u  *  )pInput,  pBmpInfo_input->bmiHeader.biSizeImage,  &pBmpInfo_input->bmiHeader.biWidth,  &pBmpInfo_input->bmiHeader.biHeight  );  
		if  (  !pObj->common.bInited  )  return  0;
	}
	//
	int  imgWidth,  imgHeight;
	imgWidth  =  pBmpInfo_input->bmiHeader.biWidth;
	imgHeight  =  pBmpInfo_input->bmiHeader.biHeight;

	//
	if  (  !pObj->common.bInited2  )  {
		myDecodeStream_init2(  pQdcObjInfo,  pObj,  imgWidth,  imgHeight  );
		if  (  !pObj->common.bInited2  )  return  0;
	}

	//
	if  (  pBmpInfo_input->bmiHeader.biSizeImage  >  pQdcObjInfo->cbInputBuffer  )  return  -1;

	int  maxFrames  =  3;
	int  frameNumber  =  1;
	
	//
	int  index  =  0;
	frameNumber  =  myDecodeStream(  pObj,  &pObj->common.bInited,  FALSE,  (  Ipp8u  *  )pInput,  pBmpInfo_input->bmiHeader.biSizeImage,  (  Ipp8u  *  )pObj->common.outs[index].pBuf,  imgWidth,  imgHeight,  maxFrames  );  
	if  (  frameNumber  >  0  )  {
		int  biBitCount  =  12;
		pObj->common.outs[index].len  =  (  pBmpInfo_input->bmiHeader.biWidth  *  biBitCount  +  31  )  /  32  *  4  *  pBmpInfo_input->bmiHeader.biHeight;
	}

	return  frameNumber;
	//  return  0;
#endif
}


//  Note: 压缩也加压缩的函数,返回值: -1失败.0成功或者无结果. >0表明有成果

//  2011/12/10
extern  "C"  int  __declspec(  dllexport  )qdcDecompressVideoAndOutput(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  BITMAPINFO  *  pBmpInfo_output,  BYTE  *  pOutput  )
{
	//  2014/08/10
	void  *  pDebugStep  =  pQdcObjInfo->var.pDebugStep;
	DEBUG_step_dec	*	pDebugStepDec  =  (  DEBUG_step_dec  *  )tmp_getDebugStep_sth(  0,  CONST_debugStepType_dec,  pQdcObjInfo->var.pDebugStep  );
	if  (  !pDebugStepDec  )  return  -1;

	//
	tmp_mySetDebugStep(  0,  pDebugStep,  301  );

	//
	QDC_OBJ_h264Dec	*	pObj		=	(  QDC_OBJ_h264Dec  *  )pQdcObjInfo->var.pObj;
	TCHAR				tBuf[256]	=	_T(  ""  );
	
	//
	if  (  !pObj->common.bInited  )  {
		myDecodeStream_init(  pObj,  &pObj->common.bInited,  (  Ipp8u  *  )pInput,  pBmpInfo_input->bmiHeader.biSizeImage,  &pBmpInfo_input->bmiHeader.biWidth,  &pBmpInfo_input->bmiHeader.biHeight  );  
		if  (  !pObj->common.bInited  )  return  0;
	}
	//
	int  imgWidth,  imgHeight;
	imgWidth  =  pBmpInfo_input->bmiHeader.biWidth;
	imgHeight  =  pBmpInfo_input->bmiHeader.biHeight;

	//
	if  (  !pObj->common.bInited2  )  {
		myDecodeStream_init2(  pQdcObjInfo,  pObj,  imgWidth,  imgHeight  );
		if  (  !pObj->common.bInited2  )  return  0;
	}
	

	//
	if  (  pBmpInfo_input->bmiHeader.biSizeImage  >  pQdcObjInfo->var.cbInputBuffer  )  return  -1;

	//
	int  biBitCount  =  12;
	int  dec_biSizeImage  =  (  imgWidth  *  biBitCount  +  31  )  /  32  *  4  *  imgHeight;
	BOOL  bBufTooSmall  =  FALSE;
	if  (  pBmpInfo_output->bmiHeader.biSizeImage  <  dec_biSizeImage  )  {
		bBufTooSmall  =  TRUE;
		//
		pOutput  =  (  BYTE  *  )pObj->outputForDec.pBuf;		
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "qdcDecompressVideoAndOutput,headerBiSizeImage %d < decBiSizeImage %d"  ),  pBmpInfo_output->bmiHeader.biSizeImage,  dec_biSizeImage  );
		tmp_showInfo(  tBuf  );
	}

	//
	int  maxFrames  =  3;
	int  frameNumber  =  1;
	
	frameNumber  =  myDecodeStream(  pQdcObjInfo,  &pObj->common.bInited,  FALSE,  (  Ipp8u  *  )pInput,  pBmpInfo_input->bmiHeader.biSizeImage,  (  Ipp8u  *  )pOutput,  imgWidth,  imgHeight,  maxFrames  ); 
	if  (  pDebugStepDec->bException  )  {	//  2014/08/11
		return  CONST_qdcRet_exception;
	}
	//  if  (  frameNumber  <=  0  )  
	if  (  frameNumber  <  0  )  {
		#ifdef  _DEBUG
				OutputDebugString(  _T(  "dec failed\n"  )  );
		#endif
	}
	if  (  frameNumber  ==  0  )  
	{
		//  if  (  pObj->ucCompressors  !=  CONST_videoCompressors_stream  )  
		if  (  pObj->ucCompressors  ==  CONST_videoCompressors_ipp  )  //  2014/08/31
		{	
			frameNumber  =  myDecodeStream(  pQdcObjInfo,  &pObj->common.bInited,  TRUE,  (  Ipp8u  *  )NULL,  0,  (  Ipp8u  *  )pOutput,  imgWidth,  imgHeight,  maxFrames  );
			if  (  pDebugStepDec->bException  )  {
				return  CONST_qdcRet_exception;
			}
		}
	}

	//
	if  (  bBufTooSmall  )  {
		return  CONST_qdcRet_bufTooSmall;
	}

	//
	if  (  frameNumber  >  0  )  {
		pBmpInfo_output->bmiHeader.biSizeImage  =  dec_biSizeImage;	//  (  pBmpInfo_input->bmiHeader.biWidth  *  biBitCount  +  31  )  /  32  *  4  *  pBmpInfo_input->bmiHeader.biHeight;
	}


	//  2014/08/10
	tmp_mySetDebugStep(  0,  pDebugStep,  311  );


	//
	return  frameNumber;
	//  return  0;
}




//
extern  "C"  int  __declspec(  dllexport  )qdcGetOutputByIndex(  QDC_OBJ_INFO  *  pQdcObjInfo,  int  index,  BYTE *  pbOutData,  unsigned  int  *  puiDataSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  pui_rtTimeLen  )
{
	TCHAR					tBuf[128]	=	_T(  ""  );
	QDC_OBJ_h264Common	*	pObj	=	(  QDC_OBJ_h264Common  *  )pQdcObjInfo->var.pObj;

	if  (  index  <  0  ||  index  >=  sizeof(  pObj->outs  )  /  sizeof(  pObj->outs[0]  )  )  return  -1;

	if  (  *puiDataSize  <  pObj->outs[index].len  )  {
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "i.qdcGetOutputByIndex failed: buf too small:puiDataSize:%d, outs[%d].len:%d"  ),  *puiDataSize,  index,  pObj->outs[index].len  );
		tmp_showInfo(  _T(  "qdcGetOutputByIndex1 failed: buf too small"  )  );
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

