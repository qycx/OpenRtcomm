
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	<mmsystem.h>
#include	<mmreg.h>
#include	<msacm.h>
#include	<math.h>
#include	"qmcAcm.h"

BOOL  CALLBACK  DriverEnumProc(  HACMDRIVERID  hadid,  DWORD  dwInstance,  DWORD  fdwSupport  );
 

//  寻找一个支持给定格式的驱动并返回其ID;
typedef		struct			{
							HACMDRIVERID	hadid;
							BOOL			bMatched;
							//
							WORD			wFormatTag;
							WORD			nChannels;         /* number of channels (i.e. mono, stereo...) */
    						DWORD			nSamplesPerSec;    /* sample rate */
							WORD			wBitsPerSample;    /* Number of bits per sample of mono data */
}			FIND_DRIVER_INFO;

//  用来枚举格式的回调函数
 BOOL  CALLBACK  find_format_enum(  HACMDRIVERID  hadid,  LPACMFORMATDETAILS  padf,  DWORD_PTR  dwInstance,  DWORD  fdwSupport  )
{
	FIND_DRIVER_INFO  *pdi;
	pdi  =  (  FIND_DRIVER_INFO  *  )dwInstance;

	if  (  padf->dwFormatTag  !=  (  DWORD  )pdi->wFormatTag
		||  padf->pwfx->nChannels  !=  pdi->nChannels  
			||  padf->pwfx->nSamplesPerSec  !=  pdi->nSamplesPerSec  )  
	{
		return TRUE;		//  没找到，继续枚举
	}
	if  (  pdi->wBitsPerSample  &&  padf->pwfx->wBitsPerSample  !=  pdi->wBitsPerSample  )  return  TRUE;
	
	//  找到了，停止枚举
	//  pdi->hadid  =  hadid;
	pdi->bMatched  =  TRUE;

	return  FALSE;
}

//  用来枚举驱动的回调函数
 BOOL  CALLBACK  find_driver_enum(  HACMDRIVERID  hadid,  DWORD_PTR  dwInstance,  DWORD  fdwSupport  )
{
	FIND_DRIVER_INFO	*		pdi		=	(  FIND_DRIVER_INFO  *  )dwInstance;
	BOOL						bRet	=	FALSE;
	WAVEFORMATEX		*		pwf		=	NULL;
	BOOL						bOpen	=	FALSE;
	HACMDRIVER					had		=	NULL;
	MMRESULT					mmr;
	
	mmr  =  acmDriverOpen(  &had,  hadid,  0  );
	if  (  mmr  )  goto  errLabel;		//  出错了，停止枚举
	bOpen  =  TRUE;

	DWORD  dwSize;dwSize = 0;
	mmr  =  acmMetrics(  (  HACMOBJ  )had,  ACM_METRIC_MAX_SIZE_FORMAT,  &dwSize  );
	if  (  mmr  )  goto  errLabel;
	if  (  dwSize  <  sizeof(  WAVEFORMATEX  )  )  dwSize  =  sizeof(  WAVEFORMATEX  );		//  for MS-PCM

	pwf	= (  WAVEFORMATEX  *)mymalloc(  dwSize  );
	if  (  !pwf  )  goto  errLabel;
	memset(  pwf,  0,  dwSize  );
	pwf->cbSize  =  LOWORD(  dwSize  )  -  sizeof(  WAVEFORMATEX  );
	pwf->wFormatTag  =  pdi->wFormatTag;

	ACMFORMATDETAILS  fd;
	memset(  &fd,  0,  sizeof(  fd  )  );
	fd.cbStruct  =  sizeof(  fd  );
	fd.pwfx  =  pwf;
	fd.cbwfx  =  dwSize;
	fd.dwFormatTag  =  pdi->wFormatTag;

	mmr  =  acmFormatEnum(  had,  &fd,  find_format_enum,  (  DWORD_PTR  )(  VOID  *  )pdi,  0  );
	if  (  mmr  )  goto  errLabel;
	if  (  pdi->bMatched  )  {  		//  找到了或者有错误，停止枚举
		pdi->hadid  =  hadid;			//  2010/04/27
		bRet  =  FALSE;  goto  errLabel;
	}

	bRet  =  TRUE;

errLabel:

	if  (  pwf  )	free(  pwf  );
	if  (  bOpen  )  acmDriverClose(  had,  0  );	

	return  bRet;

}

//  寻找给定格式标签的第一个驱动
 HACMDRIVERID  find_driver(  WORD  wformatTag,  WORD  nChannels,  DWORD  nSamplesPerSec,  WORD  wBitsPerSample  )
{
	FIND_DRIVER_INFO  fdi;

	memset(  &fdi,  0,  sizeof(  fdi  )  );
	fdi.hadid  =  NULL;
	fdi.wFormatTag  =  wformatTag;
	fdi.nChannels  =  nChannels;
	fdi.nSamplesPerSec  =  nSamplesPerSec;
	fdi.wBitsPerSample  =  wBitsPerSample;

	MMRESULT  mmr  =  acmDriverEnum(  find_driver_enum,  (DWORD_PTR)(VOID *)&fdi,  0 );
	if  (  mmr  )  return  NULL;

	return  fdi.hadid;
}

// 获取驱动的描述，该驱动为第一个支持给定格式标签的驱动
 WAVEFORMATEX  *  get_driver_format(  HACMDRIVERID  hadid,  WORD  wFormatTag,  WORD  nChannels,  DWORD  nSamplesPerSec,  WORD  wBitsPerSample  )
{
	int					iErr	=	-1;
	HACMDRIVER			had		=	NULL;
	WAVEFORMATEX  *		pwf		=	NULL;
	BOOL				bOpen	=	FALSE;

	MMRESULT  mmr  =  acmDriverOpen(  &had,  hadid,  0  );
	if  (  mmr  )  return  NULL;
	bOpen  =  TRUE;
	
	//  获取描述
	DWORD  dwSize  =  0;
	mmr  =  acmMetrics(  (  HACMOBJ  )had,  ACM_METRIC_MAX_SIZE_FORMAT,  &dwSize  );
	if  (  mmr  )  goto  errLabel;
	if  (  dwSize  <  sizeof(  WAVEFORMATEX  )  )  dwSize  =  sizeof(  WAVEFORMAT  );		//  for MS-PCM

	pwf	= (  WAVEFORMATEX  *)mymalloc(  dwSize  );
	if  (  !pwf  )  goto  errLabel;
	memset(  pwf,  0,  dwSize  );
	pwf->cbSize  =  LOWORD(  dwSize  )  -  sizeof(  WAVEFORMATEX  );
	pwf->wFormatTag  =  wFormatTag;

	ACMFORMATDETAILS  fd;
	memset(  &fd,  0,  sizeof(  fd  )  );
	fd.cbStruct  =  sizeof(  fd  );
	fd.pwfx  =  pwf;
	fd.cbwfx  =  dwSize;
	fd.dwFormatTag  =  wFormatTag;


	//  建立一个控制枚举的结构
	FIND_DRIVER_INFO  fdi;
	fdi.hadid  =  NULL;
	fdi.wFormatTag  = wFormatTag;
	fdi.nChannels  =  nChannels;
	fdi.nSamplesPerSec  =  nSamplesPerSec;
	fdi.wBitsPerSample  =  wBitsPerSample;

	mmr  =  acmFormatEnum(  had,  &fd, find_format_enum,  (DWORD_PTR)(VOID*)&fdi,  0  );
	if  (  mmr  )  goto  errLabel;
	if  (  !fdi.bMatched  )  goto  errLabel;

	iErr  =  0;

errLabel:

	if  (  bOpen  )  acmDriverClose(  had,  0  );

	if  (  iErr  )  {
        if  (  pwf  )  free(  pwf  );
	}

	return  iErr  ?  NULL  :  pwf;	
}


// 获取驱动的描述，该驱动为第一个支持给定格式标签的驱动
 WAVEFORMATEX  *  get_driver_suggestedFormat(  HACMDRIVERID  hadid,  WAVEFORMATEX  *  pWfSrc,  WORD  wFormatTag,  WORD  nChannels,  DWORD  nSamplesPerSec,  WORD  wBitsPerSample  )
{
	int					iErr	=	-1;
	HACMDRIVER			had		=	NULL;
	WAVEFORMATEX  *		pwf		=	NULL;
	BOOL				bOpen	=	FALSE;

	MMRESULT  mmr  =  acmDriverOpen(  &had,  hadid,  0  );
	if  (  mmr  )  return  NULL;
	bOpen  =  TRUE;
	
	//  获取描述
	DWORD  dwSize  =  0;
	mmr  =  acmMetrics(  (  HACMOBJ  )had,  ACM_METRIC_MAX_SIZE_FORMAT,  &dwSize  );
	if  (  mmr  )  goto  errLabel;
	if  (  dwSize  <  sizeof(  WAVEFORMATEX  )  )  dwSize  =  sizeof(  WAVEFORMAT  );		//  for MS-PCM

	pwf	= (  WAVEFORMATEX  *)mymalloc(  dwSize  );
	if  (  !pwf  )  goto  errLabel;
	memset(  pwf,  0,  dwSize  );
	pwf->cbSize  =  LOWORD(  dwSize  )  -  sizeof(  WAVEFORMATEX  );
	pwf->wFormatTag  =  wFormatTag;

	/*
	ACMFORMATDETAILS  fd;
	memset(  &fd,  0,  sizeof(  fd  )  );
	fd.cbStruct  =  sizeof(  fd  );
	fd.pwfx  =  pwf;
	fd.cbwfx  =  dwSize;
	fd.dwFormatTag  =  wFormatTag;


	//  建立一个控制枚举的结构
	FIND_DRIVER_INFO  fdi;
	fdi.hadid  =  NULL;
	fdi.wFormatTag  = wFormatTag;
	fdi.nChannels  =  nChannels;
	fdi.nSamplesPerSec  =  nSamplesPerSec;
	fdi.wBitsPerSample  =  wBitsPerSample;

	mmr  =  acmFormatEnum(  had,  &fd, find_format_enum,  (DWORD)(VOID*)&fdi,  0  );
	if  (  mmr  )  goto  errLabel;
	if  (  !fdi.hadid  )  goto  errLabel;
	*/

	mmr  =  acmFormatSuggest(  had,  pWfSrc,  pwf,  dwSize,  ACM_FORMATSUGGESTF_WFORMATTAG  );
	if  (  mmr  )  goto  errLabel;

	iErr  =  0;

errLabel:

	if  (  bOpen  )  acmDriverClose(  had,  0  );

	if  (  iErr  )  {
        if  (  pwf  )  free(  pwf  );
	}

	return  iErr  ?  NULL  :  pwf;	
}



 




 int  showAcm(  )
{
	TCHAR		tBuf[256]	=	_T(  ""  );
	DWORD		dwACMVer  = acmGetVersion(  );

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "ACM Version %u %02u build %u"  ),  HIWORD(  dwACMVer  )  >>  8, HIWORD(  dwACMVer  )  &  0xFF,  LOWORD(  dwACMVer  )  );
	if  (  LOWORD(  dwACMVer  )  ==  0  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ReTail"  ),  tBuf  );
	OutputDebugString(  tBuf  );  OutputDebugString(  _T(  "\n"  )  );  tBuf[0]  =  0;

	//  显示一些ACM信息
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ACM  metrics. "  ),  tBuf  );

	DWORD		dwCodecs  =  0;
	MMRESULT	mmr  =  acmMetrics(  NULL,  ACM_METRIC_COUNT_CODECS,  &dwCodecs  );
	if  (  mmr  )  return  0;
	else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %lu  codecs installed.\n"  ),  tBuf,  dwCodecs  );
	OutputDebugString(  tBuf  );  OutputDebugString(  _T(  "\n"  )  );  tBuf[0]  =  0;

	//  枚举所有允许的驱动程序
	OutputDebugString(  _T(  "Enable  drivers  \n"  )  );
	mmr  =  acmDriverEnum(  (  ACMDRIVERENUMCB  )DriverEnumProc,  0,  0  );
    if  (  mmr  )  return  0;

	return  0;
}

 BOOL  CALLBACK  FormatEnumProc(  HACMDRIVERID  hadid,  LPACMFORMATDETAILS  pafd,  DWORD_PTR  dwInstance,  DWORD  fdwSupport  )
 {
	 TCHAR	tBuf[256]  =  _T(  ""  );

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%4.4XH,  %s\n"  ),  pafd->dwFormatTag,  pafd->szFormat  );
	 OutputDebugString(  tBuf  );

	 return  TRUE;
 }

 BOOL  CALLBACK  DriverEnumProc(  HACMDRIVERID  hadid,  DWORD  dwInstance,  DWORD  fdwSupport  )
{
	BOOL				bRet		=	FALSE;
	BOOL				bOpen		=	FALSE;
	WAVEFORMATEX	*	pwf			=	NULL;
	TCHAR				tBuf[256]	=	_T(  ""  );
	HACMDRIVER  had;had = NULL;

	traceLogA(  (char*)  "id:  %8.8lxH  supports\n",  hadid  );

	if  (  fdwSupport  &  ACMDRIVERDETAILS_SUPPORTF_ASYNC  )  traceLogA(  (char*)  "async conversions. \n"  );
	if  (  fdwSupport  &  ACMDRIVERDETAILS_SUPPORTF_CODEC  )  traceLogA(  (char*)  "different  format conversions. \n"  );
	if  (  fdwSupport  &  ACMDRIVERDETAILS_SUPPORTF_CONVERTER  )  traceLogA(  (char*)  "same  format  conversions. \n"  );
	if  (  fdwSupport  &  ACMDRIVERDETAILS_SUPPORTF_FILTER  )  traceLogA(  (char*)  "async conversions. \n"  );

	//  获得一些具体信息
	ACMDRIVERDETAILS  dd;
	dd.cbStruct  =  sizeof(  dd  );
	MMRESULT  mmr  =  acmDriverDetails(  hadid,  &dd,  0  );
	if  (  mmr  )  goto  errLabel;
	
	traceLogA(  (char*)  "Short Name:	%S",  dd.szShortName  );
	traceLogA(  (char*)  "Long Name:  %S",  dd.szLongName  );
	traceLogA(  (char*)  "CopyRight:  %S",  dd.szCopyright  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Licensing:  %s\n"  ),  dd.szLicensing  );  
	OutputDebugString(  tBuf  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Features:	%s\n"  ),  dd.szFeatures  );
	OutputDebugString(  tBuf  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Supports	%u  formats  \n"  ),  dd.cFormatTags  );
	OutputDebugString(  tBuf  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Supports	%u  filters  \n"  ),  dd.cFilterTags  );
	OutputDebugString(  tBuf  );

	//  打开驱动程序
	//HACMDRIVER  had;had = NULL;
	mmr  =  acmDriverOpen(  &had,  hadid,  0  );
	if  (  mmr  )  goto  errLabel;
	bOpen  =  TRUE;

	DWORD  dwSize;dwSize = 0;
	mmr  =  acmMetrics(  (  HACMOBJ  )had,  ACM_METRIC_MAX_SIZE_FORMAT,  &dwSize  );
	if  (  mmr  )  goto  errLabel;
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "dwSize  %d,  WAVEFORMAT  %d, \n"  ),  dwSize,  sizeof(  WAVEFORMATEX  )  );
	OutputDebugString(  tBuf  );

	dwSize  =  max(  sizeof(  WAVEFORMATEX  ),  dwSize  );
	pwf  =  (  WAVEFORMATEX  *)  mymalloc(  dwSize  );
	if  (  !pwf  )  goto  errLabel;

	memset(  pwf,  0,  dwSize  );
	pwf->cbSize  =  LOWORD(  dwSize  )  -  sizeof(  WAVEFORMATEX  );
	pwf->wFormatTag  =  WAVE_FORMAT_UNKNOWN;

	ACMFORMATDETAILS  fd;
	memset(  &fd,  0,  sizeof(  fd  )  );
	fd.cbStruct  =  sizeof(  fd  );
	fd.pwfx  =  pwf;
	fd.cbwfx  =  dwSize;
	fd.dwFormatTag	=  WAVE_FORMAT_UNKNOWN;

	mmr  =  acmFormatEnum(  had,  &fd,  FormatEnumProc,  0,  0  );
	if  (  mmr  )  goto  errLabel;
		
	bRet  =  TRUE;	//  继续枚举

errLabel:

	if  (  pwf  )  free(  pwf  );
	if  (  bOpen  )  acmDriverClose(  had,  0  );

	return  bRet;		

}


 int unused_convertAudio(  HACMDRIVERID  hadid,  WAVEFORMATEX  *  pWfSrc,  WAVEFORMATEX  *  pWfPcm,  WAVEFORMATEX  *  pWfDst,  CONVERT_AUDIO_CTX  *  pCtx  )
{
	int					iErr			=	-1;

	HACMDRIVER			had					=	NULL;
	HACMSTREAM			hstr				=	NULL;
	HACMSTREAM			hstr2				=	NULL;
	MMRESULT			mmr;

	BOOL				bOpen_hstr			=	FALSE;
	BOOL				bOpen_hstr2			=	FALSE;
	BOOL				bPrepared			=	FALSE;
	BOOL				bPrepared2			=	FALSE;

	DWORD				dwSrcSize_strhdr	=	0;
	DWORD				dwDstSize_strhdr	=	0;

	DWORD				dwSrcSize			=	0;
	DWORD				dwPcmSize			=	0;
	DWORD				dwDstSize			=	0;

	//  traceLogA(  (char*)  "错误的convertAudio is called."  );

	if  (  !pWfSrc  ||  !pCtx->pSrcBuf  )  return  -1;
	if  (  !pWfSrc->nSamplesPerSec  ||  !pWfSrc->nAvgBytesPerSec  ||  !pWfSrc->nBlockAlign  ||  !pWfSrc->nChannels  )  return  -1;

	pCtx->uiDstLen  =  0;

	//  
	//  第一步,用codec将wave转换为PCM

	mmr	=  acmStreamOpen(  &hstr,  had,  pWfSrc,  pWfPcm,  NULL,  NULL,  0,  ACM_STREAMOPENF_NONREALTIME  );
	if  (  mmr  )  goto  errLabel;
	bOpen_hstr  =  TRUE;
	
	//  为转换数据分配buf
	DWORD	dwPcmBytes;dwPcmBytes = (DWORD)(pCtx->uiSrcLen * pWfPcm->nAvgBytesPerSec * 1. / (pWfSrc->nAvgBytesPerSec));
	if  (  dwPcmBytes  >=  pCtx->dwPcmBufSize  -  pCtx->uiPcmLen  )  {
		traceLogA(  (char*)  "dwPcmByfSize too small"  );
		goto  errLabel;
	}


	//  2, 把PCM转换为最终格式
	//  
	mmr	=	acmStreamOpen(  &hstr2,  NULL,  pWfPcm,  pWfDst,  NULL,  NULL,  0,  ACM_STREAMOPENF_NONREALTIME  );
	if  (  mmr  )  goto  errLabel;
	bOpen_hstr2  =  TRUE;

	//  为转换数据分配buf
	DWORD  dwDstBytes;dwDstBytes = pWfDst->nAvgBytesPerSec * pCtx->uiPcmLen / (pWfPcm->nAvgBytesPerSec);
	if  (  dwDstBytes  >=  pCtx->dwDstBufSize  )  {
		traceLogA(  (char*)  "dwDstBufSize too small"  );
		goto  errLabel;
	}


	dwSrcSize  =  pCtx->uiSrcLen;
	mmr  =  acmStreamSize(  hstr,  dwSrcSize,  &dwPcmSize,  ACM_STREAMSIZEF_SOURCE  );
	if  (  mmr  )  goto  errLabel;
	mmr  =  acmStreamSize(  hstr2,  dwPcmSize,  &dwDstSize,  ACM_STREAMSIZEF_SOURCE  );
	if  (  mmr  )  goto  errLabel;
	mmr  =  acmStreamSize(  hstr2,  dwDstSize,  &dwPcmSize,  ACM_STREAMSIZEF_DESTINATION  );
	if  (  mmr  )  goto  errLabel;
	mmr  =  acmStreamSize(  hstr,  dwPcmSize,  &dwSrcSize,  ACM_STREAMSIZEF_DESTINATION  );
	if  (  mmr  )  goto  errLabel;

	/*
	if  (  pWfSrc->wFormatTag  ==  WAVE_FORMAT_PCM  )  {
		dwSrcSize  =  pCtx->uiSrcLen;
		mmr  =  acmStreamSize(  hstr,  dwSrcSize,  &dwDstSize,  ACM_STREAMSIZEF_SOURCE  );
		if  (  mmr  )  goto  errLabel;
		}
	else  if  (  pWfSrc->nBlockAlign  >  pWfPcm->nBlockAlign  )  {
		mmr  =  acmStreamSize(  hstr,  pWfSrc->nBlockAlign,  &dwDstSize,  ACM_STREAMSIZEF_SOURCE  );
		if  (  mmr  )  goto  errLabel;
		mmr  =  acmStreamSize(  hstr,  dwDstSize,  &dwSrcSize,  ACM_STREAMSIZEF_DESTINATION  );
		if  (  mmr  )  goto  errLabel;
		}
	else  {
		  mmr  =  acmStreamSize(  hstr,  pWfPcm->nBlockAlign,  &dwSrcSize,  ACM_STREAMSIZEF_DESTINATION  );
		  if  (  mmr  )  goto  errLabel;
		  mmr  =  acmStreamSize(  hstr,  dwSrcSize,  &dwDstSize,  ACM_STREAMSIZEF_SOURCE  );
		  if  (  mmr  )  goto  errLabel;
	}
	*/


	//  填入转换数据
	ACMSTREAMHEADER		strhdr;
	{
		CQyMalloc			mallocObj_srcBuf;
		CQyMalloc			mallocObj_dstBuf;

		dwSrcSize_strhdr  =  min(  dwSrcSize,  pCtx->uiSrcLen  );
		dwDstSize_strhdr  =  dwPcmSize;

		memset(  &strhdr,  0,  sizeof(  strhdr  )  );
		strhdr.cbStruct		=	sizeof(  strhdr  );
		strhdr.pbSrc		=	(  BYTE  *  )mallocObj_srcBuf.mallocf(  dwSrcSize_strhdr  );							// 源
		if  (  !strhdr.pbSrc  )  goto  errLabel;
		strhdr.cbSrcLength	=	dwSrcSize_strhdr;
		strhdr.pbDst		=	(  BYTE  *  )mallocObj_dstBuf.mallocf(  dwDstSize_strhdr  );						//  目的
		if  (  !strhdr.pbDst  )  goto  errLabel;
		strhdr.cbDstLength	=	dwDstSize_strhdr;
		//  填写字头
		mmr	=	acmStreamPrepareHeader(  hstr,  &strhdr,  0  );
		if  (  mmr  )  {
			traceLogA(  (char*)  "asrStreamPrepareHeader faile.d"  );
			goto  errLabel;
		}
		bPrepared  =  TRUE;

		BOOL		bFirst			=	TRUE;
		BOOL		bLast			=	FALSE;
		int			nIn				=	0;
		DWORD		flg;

		for  (  ;  ;  )  {

			 if  (  pCtx->uiSrcLen  -  nIn  <  dwSrcSize_strhdr  )  break;
			 memcpy(  strhdr.pbSrc,  pCtx->pSrcBuf  +  nIn,  dwSrcSize_strhdr  );    
		 		 
			 if  (  bFirst  )  flg  =  (  ACM_STREAMCONVERTF_BLOCKALIGN  |  ACM_STREAMCONVERTF_START  );
			 else  if  (  bLast  )  flg  =  ACM_STREAMCONVERTF_END;
			 else  flg  =  ACM_STREAMCONVERTF_BLOCKALIGN;
		 
			 mmr	=	acmStreamConvert(  hstr,  &strhdr,  flg  );
			 if  (  mmr  )  goto  errLabel;
			 bFirst  =  FALSE;

			 if  (  !(  strhdr.fdwStatus  &  ACMSTREAMHEADER_STATUSF_DONE  )  )  goto  errLabel;

			 memcpy(  pCtx->pPcmBuf  +  pCtx->uiPcmLen,  strhdr.pbDst,  strhdr.cbDstLengthUsed  );
			 pCtx->uiPcmLen  +=  strhdr.cbDstLengthUsed;

			 nIn  +=  strhdr.cbSrcLengthUsed;

			 if  (  strhdr.cbSrcLengthUsed  !=  strhdr.cbSrcLength  )  break;

		}

		if  (  (  int  )pCtx->uiSrcLen  >  nIn  )  {	//  剩余的不足一个block的数据
			memcpy(  pCtx->pSrcBuf,  pCtx->pSrcBuf  +  nIn,  pCtx->uiSrcLen  -  nIn  );
			pCtx->uiSrcLen  =  pCtx->uiSrcLen  -  nIn;
			}
		else 
			pCtx->uiSrcLen  =  0;

		strhdr.cbSrcLength  =  0;
		mmr  =  acmStreamConvert(  hstr,  &strhdr,  ACM_STREAMCONVERTF_END  );
		if  (  mmr  )  goto  errLabel;

		//  关闭
		if  (  bPrepared  )  {
			acmStreamUnprepareHeader(  hstr,  &strhdr,  0  );
			bPrepared  =  FALSE;
		}
		acmStreamClose(  hstr,  0  );	hstr	=	NULL;
		bOpen_hstr  =  FALSE;

	}

	
	/*
	if  (  pWfDst->wFormatTag  ==  WAVE_FORMAT_PCM  )  {
		dwSrcSize  =  pCtx->uiPcmLen;
		mmr  =  acmStreamSize(  hstr2,  dwSrcSize,  &dwDstSize,  ACM_STREAMSIZEF_SOURCE  );
		if  (  mmr  )  goto  errLabel;
		}
	else  if  (  pWfPcm->nBlockAlign  >  pWfDst->nBlockAlign  )  {
		mmr  =  acmStreamSize(  hstr2,  pWfPcm->nBlockAlign,  &dwDstSize,  ACM_STREAMSIZEF_SOURCE  );
		if  (  mmr  )  goto  errLabel;
		mmr  =  acmStreamSize(  hstr2,  dwDstSize,  &dwSrcSize,  ACM_STREAMSIZEF_DESTINATION  );
		if  (  mmr  )  goto  errLabel;
		}
	else  {
		  mmr  =  acmStreamSize(  hstr2,  pWfDst->nBlockAlign,  &dwSrcSize,  ACM_STREAMSIZEF_DESTINATION  );
		  if  (  mmr  )  goto  errLabel;
		  mmr  =  acmStreamSize(  hstr2,  dwSrcSize,  &dwDstSize,  ACM_STREAMSIZEF_SOURCE  );
		  if  (  mmr  )  goto  errLabel;
	}
	*/


	//  填入转换数据
	ACMSTREAMHEADER		strhdr2;
	{
		CQyMalloc			mallocObj_srcBuf;
		CQyMalloc			mallocObj_dstBuf;

		dwSrcSize_strhdr  =  min(  dwPcmSize,  pCtx->uiPcmLen  );
		dwDstSize_strhdr  =  dwDstSize;

		memset(  &strhdr2,  0,  sizeof(  strhdr2  )  );
		strhdr2.cbStruct		=	sizeof(  strhdr2  );
		strhdr2.pbSrc			=	(  BYTE  *  )mallocObj_srcBuf.mallocf(  dwSrcSize_strhdr  );
		if  (  !strhdr2.pbSrc  )  goto  errLabel;
		strhdr2.cbSrcLength		=	dwSrcSize_strhdr;
		strhdr2.pbDst			=	(  BYTE  *  )mallocObj_dstBuf.mallocf(  dwDstSize_strhdr  );
		if  (  !strhdr2.pbDst  )  goto  errLabel;
		strhdr2.cbDstLength		=	dwDstSize_strhdr;
		
		//  填写字头
		mmr	=	acmStreamPrepareHeader(  hstr2,  &strhdr2,  0  );
		if  (  mmr  )  goto  errLabel;
		bPrepared2  =  TRUE;

	
		BOOL	bFirst			=	TRUE;
		BOOL	bLast			=	FALSE; 
		DWORD	flg;
		int		nIn				=	0;

		for  (  ;  ;  )  {

			 if  (  pCtx->uiPcmLen  -  nIn  <  dwSrcSize_strhdr  )  break;
		 	 memcpy(  strhdr2.pbSrc,  pCtx->pPcmBuf  +  nIn,  dwSrcSize_strhdr  );    

		 	 if  (  bFirst  )  flg  =  (  ACM_STREAMCONVERTF_BLOCKALIGN  |  ACM_STREAMCONVERTF_START  );
		 	 else  if  (  bLast  )  flg  =  ACM_STREAMCONVERTF_END;
		 	 else  flg  =  ACM_STREAMCONVERTF_BLOCKALIGN;
		 
			 mmr	=	acmStreamConvert(  hstr2,  &strhdr2,  flg  );
			 if  (  mmr  )  goto  errLabel;		 
			 bFirst  =  FALSE;

			 if  (  !(  strhdr2.fdwStatus  &  ACMSTREAMHEADER_STATUSF_DONE  )  )  goto  errLabel;

			 memcpy(  pCtx->pDstBuf  +  pCtx->uiDstLen,  strhdr2.pbDst,  strhdr2.cbDstLengthUsed  );
			 pCtx->uiDstLen  +=  strhdr2.cbDstLengthUsed;

			 nIn  +=  strhdr2.cbSrcLengthUsed;

			 if  (  strhdr2.cbSrcLengthUsed  !=  strhdr2.cbSrcLength  )  break;
			 
		}	

		if  (  (  int  )pCtx->uiPcmLen  >  nIn  )  {	//  剩余的不足一个block的数据
			memcpy(  pCtx->pPcmBuf,  pCtx->pPcmBuf  +  nIn,  pCtx->uiPcmLen  -  nIn  );
			pCtx->uiPcmLen  =  pCtx->uiPcmLen  -  nIn;
			}
		else
			pCtx->uiPcmLen  =  0;		

		strhdr2.cbSrcLength  =  0;
		mmr  =  acmStreamConvert(  hstr2,  &strhdr2,  ACM_STREAMCONVERTF_END  );
		if  (  mmr  )  goto  errLabel;
	
	}
	
	iErr  =  0;

errLabel:
	
	if  (  bPrepared  )  acmStreamUnprepareHeader(  hstr,  &strhdr,  0  );
	if  (  hstr  )  acmStreamClose(  hstr,  0  );

	if  (  bPrepared2  )  acmStreamUnprepareHeader(  hstr2,  &strhdr2,  0  );
	if  (  hstr2  )  acmStreamClose(  hstr2,  0  );

	if  (  had  )  acmDriverClose(  had,  0  );

	if  (  iErr  )  {
		pCtx->uiSrcLen  =  0;
		pCtx->uiPcmLen  =  0;
		pCtx->uiDstLen  =  0;
	}

	
	return  iErr;
}




/*
 int convertAudio(  HACMDRIVERID  hadid,  WAVEFORMATEX  *  pWfSrc,  BYTE  *  pSrcData,  DWORD  dwSrcBytes,  WAVEFORMATEX  *  pWfPcm,  BYTE  *  pPcmBuf,  DWORD  dwPcmBufSize,  WAVEFORMATEX  *  pWfDrv,  BYTE  *  pDstData,  DWORD  *  pdwDstBytes  )
{
	int					iErr		=	-1;
	HACMDRIVER			had			=	NULL;
	HACMSTREAM			hstr		=	NULL;
	BOOL				bOpen_hstr	=	FALSE;
	BOOL				bPrepared	=	FALSE;		//  2009/03/16
	BOOL				bPrepared2	=	FALSE;		//  2009/03/16
	MMRESULT			mmr;
	//  2009/03/16
	//  CQySyncObj			syncObj;
	//  if  (  syncObj.sync(  _T(  "acm"  )  )  )  return  -1;

	if  (  !pWfSrc  ||  !pSrcData  )  return  -1;
	if  (  !pWfSrc->nSamplesPerSec  ||  !pWfSrc->nAvgBytesPerSec  ||  !pWfSrc->nBlockAlign  ||  !pWfSrc->nChannels  )  return  -1;


	//  第一步,用codec将wave转换为PCM
	try  {
		 mmr	=  acmStreamOpen(  &hstr,  had,  pWfSrc,  pWfPcm,  NULL,  NULL,  0,  ACM_STREAMOPENF_NONREALTIME  );
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   mmr  =  -1;
	}
	if  (  mmr  )  goto  errLabel;
	bOpen_hstr  =  TRUE;
	
	//  为转换数据分配buf
	DWORD	dwPcmBytes		=	(  DWORD  )(  dwSrcBytes  *  pWfPcm->nAvgBytesPerSec  *  1.  /  (  pWfSrc->nAvgBytesPerSec  )  );
	if  (  dwPcmBytes  >=  dwPcmBufSize  )  goto  errLabel;

	//  填入转换数据
	ACMSTREAMHEADER		strhdr;
	memset(  &strhdr,  0,  sizeof(  strhdr  )  );
	strhdr.cbStruct		=	sizeof(  strhdr  );
	strhdr.pbSrc		=	pSrcData;		// 源
	strhdr.cbSrcLength	=	dwSrcBytes;
	strhdr.pbDst		=	pPcmBuf;		//  目的
	strhdr.cbDstLength	=	dwPcmBufSize;
	//  填写字头
	try  {
		 mmr	=	acmStreamPrepareHeader(  hstr,  &strhdr,  0  );
	    }
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   mmr  =  -1;
	}
	if  (  mmr  )  {
		if  (  strhdr.fdwStatus  &  ACMSTREAMHEADER_STATUSF_PREPARED  )  bPrepared  =  TRUE;
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  "convertAudio"  ),  _T(  ""  ),  _T(  "acmStreamPrepareHeader failed. bPrepared %d"  ),  bPrepared  );
		goto  errLabel;			//  2009/03/16
	}
	bPrepared  =  TRUE;						//  2009/03/16

	try  {
		mmr	=	acmStreamConvert(  hstr,  &strhdr,  0  );
	    }
	catch  (  CException  *  e  ){
		   e->Delete(  );
		   mmr  =  -1;
	}
	if  (  mmr  )  goto  errLabel;

	acmStreamUnprepareHeader(  hstr,  &strhdr,  0  );	//  2009/03/16
	bPrepared  =  FALSE;								//  2009/03/16

	//  关闭
	acmStreamClose(  hstr,  0  );	hstr	=	NULL;
	bOpen_hstr  =  FALSE;

	//  pcm转换后得到的字节数
	dwPcmBytes  =  strhdr.cbDstLengthUsed;

	//  最后一步,把PCM转换为最终格式
	try  {
		mmr	=	acmStreamOpen(  &hstr,  NULL,  pWfPcm,  pWfDrv,  NULL,  NULL,  0,  ACM_STREAMOPENF_NONREALTIME  );
	    }
	catch  (  CException  *  e  )  {
		   e->Delete(  );   
		   mmr  =  -1;
	}
	if  (  mmr  )  goto  errLabel;
	bOpen_hstr  =  TRUE;

	//  为转换数据分配buf
	DWORD	dwDstBytes		=	pWfDrv->nAvgBytesPerSec  *  dwPcmBytes  /  (  pWfPcm->nAvgBytesPerSec  );
	if  (  dwDstBytes  >=  *pdwDstBytes  )  goto  errLabel;

	//  填入转换数据
	ACMSTREAMHEADER		strhdr2;
	memset(  &strhdr2,  0,  sizeof(  strhdr2  )  );
	strhdr2.cbStruct		=	sizeof(  strhdr2  );
	strhdr2.pbSrc			=	pPcmBuf;
	strhdr2.cbSrcLength		=	dwPcmBytes;
	strhdr2.pbDst			=	pDstData;
	strhdr2.cbDstLength		=	*pdwDstBytes;
	//  填写字头
	try  {
		mmr	=	acmStreamPrepareHeader(  hstr,  &strhdr2,  0  );
	    }
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   mmr  =  -1;
	}
	if  (  mmr  )  {
		if  (  strhdr2.fdwStatus  &  ACMSTREAMHEADER_STATUSF_PREPARED  )  bPrepared2  =  TRUE;
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  "convertAudio"  ),  _T(  ""  ),  _T(  "acmStreamPrepareHeader failed. bPrepared2 %d"  ),  bPrepared2  );
		goto  errLabel;
	}
	bPrepared2  =  TRUE;

	try  {	
		mmr	=	acmStreamConvert(  hstr,  &strhdr2,  0  );
    	}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   mmr  =  -1;
	}
	if  (  mmr  )  goto  errLabel;
	
	*pdwDstBytes  =  strhdr2.cbDstLengthUsed;

	iErr  =  0;

errLabel:

	if  (  bPrepared2  )  {		
		acmStreamUnprepareHeader(  hstr,  &strhdr2,  0  );
	}
	if  (  bPrepared  )  {
		acmStreamUnprepareHeader(  hstr,  &strhdr,  0  );
	}

	if  (  bOpen_hstr  )  {
		if  (  hstr  )  acmStreamClose(  hstr,  0  );
	}
	if  (  had  )  acmDriverClose(  had,  0  );

	return  iErr;
}
*/



 int convertAudio(  HACMSTREAM  hstr1,  HACMSTREAM  hstr2,  WAVEFORMATEX  *  pWfSrc,  BYTE  *  pSrcData,  DWORD  dwSrcBytes,  WAVEFORMATEX  *  pWfPcm,  BYTE  *  pPcmBuf,  DWORD  dwPcmBufSize,  WAVEFORMATEX  *  pWfDrv,  BYTE  *  pDstData,  DWORD  *  pdwDstBytes  )
{
	int					iErr		=	-1;
	HACMDRIVER			had			=	NULL;
	//  HACMSTREAM			hstr		=	NULL;
	//  BOOL				bOpen_hstr	=	FALSE;
	BOOL				bPrepared	=	FALSE;		//  2009/03/16
	BOOL				bPrepared2	=	FALSE;		//  2009/03/16
	MMRESULT			mmr;
	//  2009/03/16
	//  CQySyncObj			syncObj;
	//  if  (  syncObj.sync(  _T(  "acm"  )  )  )  return  -1;

	if  (  !hstr1  ||  !hstr2  )  return  -1;
	if  (  !pWfSrc  ||  !pSrcData  )  return  -1;
	if  (  !pWfSrc->nSamplesPerSec  ||  !pWfSrc->nAvgBytesPerSec  ||  !pWfSrc->nBlockAlign  ||  !pWfSrc->nChannels  )  return  -1;


	//  第一步,用codec将wave转换为PCM
	/*
	try  {
		 mmr	=  acmStreamOpen(  &hstr,  had,  pWfSrc,  pWfPcm,  NULL,  NULL,  0,  ACM_STREAMOPENF_NONREALTIME  );
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   mmr  =  -1;
	}
	if  (  mmr  )  goto  errLabel;
	bOpen_hstr  =  TRUE;
	*/
	
	//  为转换数据分配buf
	DWORD	dwPcmBytes		=	(  DWORD  )(  dwSrcBytes  *  pWfPcm->nAvgBytesPerSec  *  1.  /  (  pWfSrc->nAvgBytesPerSec  )  );
	if  (  dwPcmBytes  >=  dwPcmBufSize  )  goto  errLabel;

	//  填入转换数据
	ACMSTREAMHEADER		strhdr;
	memset(  &strhdr,  0,  sizeof(  strhdr  )  );
	strhdr.cbStruct		=	sizeof(  strhdr  );
	strhdr.pbSrc		=	pSrcData;		// 源
	strhdr.cbSrcLength	=	dwSrcBytes;
	strhdr.pbDst		=	pPcmBuf;		//  目的
	strhdr.cbDstLength	=	dwPcmBufSize;
	//  填写字头
	try  {
		 mmr	=	acmStreamPrepareHeader(  hstr1,  &strhdr,  0  );
	    }
#ifndef  __noMfc__
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   mmr  =  -1;
	}
#endif
	catch  (  ...  )  {
		   mmr  =  -1;
	}
	if  (  mmr  )  {
		if  (  strhdr.fdwStatus  &  ACMSTREAMHEADER_STATUSF_PREPARED  )  bPrepared  =  TRUE;
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  "convertAudio"  ),  _T(  ""  ),  _T(  "acmStreamPrepareHeader failed. bPrepared %d"  ),  bPrepared  );
		goto  errLabel;			//  2009/03/16
	}
	bPrepared  =  TRUE;						//  2009/03/16

	try  {
		mmr	=	acmStreamConvert(  hstr1,  &strhdr,  0  );
	    }
#ifndef  __noMfc__
	catch  (  CException  *  e  ){
		   e->Delete(  );
		   mmr  =  -1;
	}
#endif
	catch  (  ...  )  {
		   mmr  =  -1;
	}
	if  (  mmr  )  goto  errLabel;

	acmStreamUnprepareHeader(  hstr1,  &strhdr,  0  );	//  2009/03/16
	bPrepared  =  FALSE;								//  2009/03/16

	//  关闭
	/*
	acmStreamClose(  hstr,  0  );	hstr	=	NULL;
	bOpen_hstr  =  FALSE;
	*/

	//  pcm转换后得到的字节数
	dwPcmBytes  =  strhdr.cbDstLengthUsed;

	//  最后一步,把PCM转换为最终格式
	/*
	try  {
		mmr	=	acmStreamOpen(  &hstr,  NULL,  pWfPcm,  pWfDrv,  NULL,  NULL,  0,  ACM_STREAMOPENF_NONREALTIME  );
	    }
	catch  (  CException  *  e  )  {
		   e->Delete(  );   
		   mmr  =  -1;
	}
	if  (  mmr  )  goto  errLabel;
	bOpen_hstr  =  TRUE;
	*/

	//  为转换数据分配buf
	DWORD	dwDstBytes;dwDstBytes = pWfDrv->nAvgBytesPerSec * dwPcmBytes / (pWfPcm->nAvgBytesPerSec);
	if  (  dwDstBytes  >=  *pdwDstBytes  )  goto  errLabel;

	//  填入转换数据
	ACMSTREAMHEADER		strhdr2;
	memset(  &strhdr2,  0,  sizeof(  strhdr2  )  );
	strhdr2.cbStruct		=	sizeof(  strhdr2  );
	strhdr2.pbSrc			=	pPcmBuf;
	strhdr2.cbSrcLength		=	dwPcmBytes;
	strhdr2.pbDst			=	pDstData;
	strhdr2.cbDstLength		=	*pdwDstBytes;
	//  填写字头
	try  {
		mmr	=	acmStreamPrepareHeader(  hstr2,  &strhdr2,  0  );
	    }
#ifndef  __noMfc__
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   mmr  =  -1;
	}
#endif
	catch  (  ...  )  {
		   mmr  =   -1;
	}
	if  (  mmr  )  {
		if  (  strhdr2.fdwStatus  &  ACMSTREAMHEADER_STATUSF_PREPARED  )  bPrepared2  =  TRUE;
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  "convertAudio"  ),  _T(  ""  ),  _T(  "acmStreamPrepareHeader failed. bPrepared2 %d"  ),  bPrepared2  );
		goto  errLabel;
	}
	bPrepared2  =  TRUE;

	try  {	
		mmr	=	acmStreamConvert(  hstr2,  &strhdr2,  0  );
    	}
#ifndef  __noMfc__
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   mmr  =  -1;
	}
#endif
	catch  (  ...  )  {
		   mmr  =  -1;
	}
	if  (  mmr  )  goto  errLabel;
	
	*pdwDstBytes  =  strhdr2.cbDstLengthUsed;

	iErr  =  0;

errLabel:

	if  (  bPrepared2  )  {		
		acmStreamUnprepareHeader(  hstr2,  &strhdr2,  0  );
	}
	if  (  bPrepared  )  {
		acmStreamUnprepareHeader(  hstr1,  &strhdr,  0  );
	}

	/*
	if  (  bOpen_hstr  )  {
		if  (  hstr  )  acmStreamClose(  hstr,  0  );
	}
	*/
	if  (  had  )  acmDriverClose(  had,  0  );

	return  iErr;
}


/*
 int convertPcm(  WAVEFORMATEX  *  pWfSrc,  BYTE  *  pSrcData,  DWORD  dwSrcBytes,  WAVEFORMATEX  *  pWfPcm,  BYTE  *  pPcmBuf,  DWORD  *  pdwPcmBufBytes  )
{
	int					iErr		=	-1;
	HACMDRIVER			had			=	NULL;
	HACMSTREAM			hstr		=	NULL;
	BOOL				bOpen_hstr	=	FALSE;
	BOOL				bPrepared	=	FALSE;		//  2009/03/16
	MMRESULT			mmr;
	//  2009/03/16
	//  CQySyncObj			syncObj;
	//  if  (  syncObj.sync(  _T(  "acm"  )  )  )  return  -1;

	if  (  !pWfSrc  ||  !pSrcData  )  return  -1;
	if  (  pWfSrc->wFormatTag  !=  WAVE_FORMAT_PCM  )  return  -1;
	if  (  !pWfSrc->nSamplesPerSec  ||  !pWfSrc->nAvgBytesPerSec  ||  !pWfSrc->nBlockAlign  ||  !pWfSrc->nChannels  )  return  -1;


	//  第一步,用codec将wave转换为PCM
	try  {
		 mmr	=  acmStreamOpen(  &hstr,  had,  pWfSrc,  pWfPcm,  NULL,  NULL,  0,  ACM_STREAMOPENF_NONREALTIME  );
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   mmr  =  -1;
	}
	if  (  mmr  )  goto  errLabel;
	bOpen_hstr  =  TRUE;
	
	//  为转换数据分配buf
	DWORD	dwPcmBytes		=	(  DWORD  )(  dwSrcBytes  *  pWfPcm->nAvgBytesPerSec  *  1.  /  (  pWfSrc->nAvgBytesPerSec  )  );
	if  (  dwPcmBytes  >=  *pdwPcmBufBytes  )  goto  errLabel;

	//  填入转换数据
	ACMSTREAMHEADER		strhdr;
	memset(  &strhdr,  0,  sizeof(  strhdr  )  );
	strhdr.cbStruct		=	sizeof(  strhdr  );
	strhdr.pbSrc		=	pSrcData;		// 源
	strhdr.cbSrcLength	=	dwSrcBytes;
	strhdr.pbDst		=	pPcmBuf;		//  目的
	strhdr.cbDstLength	=	*pdwPcmBufBytes;
	//  填写字头
	try  {
		 mmr	=	acmStreamPrepareHeader(  hstr,  &strhdr,  0  );
	    }
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   mmr  =  -1;
	}
	if  (  mmr  )  goto  errLabel;			//  2009/03/16
	bPrepared  =  TRUE;						//  2009/03/16

	try  {
		mmr	=	acmStreamConvert(  hstr,  &strhdr,  0  );
	    }
	catch  (  CException  *  e  ){
		   e->Delete(  );
		   mmr  =  -1;
	}
	if  (  mmr  )  goto  errLabel;

	acmStreamUnprepareHeader(  hstr,  &strhdr,  0  );	//  2009/03/16
	bPrepared  =  FALSE;								//  2009/03/16

	//  关闭
	acmStreamClose(  hstr,  0  );	hstr	=	NULL;
	bOpen_hstr  =  FALSE;

	//  pcm转换后得到的字节数
	*pdwPcmBufBytes  =  strhdr.cbDstLengthUsed;

	iErr  =  0;

errLabel:

	if  (  bPrepared  )  {
		acmStreamUnprepareHeader(  hstr,  &strhdr,  0  );
	}

	if  (  bOpen_hstr  )  {
		if  (  hstr  )  acmStreamClose(  hstr,  0  );
	}
	if  (  had  )  acmDriverClose(  had,  0  );

	return  iErr;
}
*/

#ifdef  __DEBUG__
 int testConvert(  HACMDRIVERID  hadid,  WORD  wFormatTag,  WORD  nChannels,  DWORD  nSamplesPerSec,  WORD  wBitsPerSample  )
{
	int					iErr		=	-1;
	HACMDRIVER			had			=	NULL;
	HACMSTREAM			hstr		=	NULL;
	MMRESULT			mmr;
	BOOL				bOpen_hstr	=	FALSE;
	WAVEFORMATEX	*	pWfDrv		=	NULL;
	WAVEFORMATEX	*	pWfPcm		=	NULL;
	WAVEFORMATEX	*	pWfSrc		=	NULL;


	//  if  (  !pWfSrc  ||  !pSrcData  )  return  -1;
	//  if  (  !pWfSrc->nSamplesPerSec  ||  !pWfSrc->nAvgBytesPerSec  ||  !pWfSrc->nBlockAlign  ||  !pWfSrc->nChannels  )  return  -1;


	//  建立数据源	
	WAVEFORMATEX  wfSrc;
	memset(  &wfSrc,  0,  sizeof(  WAVEFORMATEX  )  );
	wfSrc.cbSize			=	0;
	wfSrc.wFormatTag		=	WAVE_FORMAT_PCM;
	wfSrc.nChannels			=	1;
	wfSrc.nSamplesPerSec	=	11025;
	wfSrc.wBitsPerSample	=	8;
	wfSrc.nBlockAlign		=	wfSrc.nChannels  *  wfSrc.wBitsPerSample / 8;
	wfSrc.nAvgBytesPerSec	=	wfSrc.nSamplesPerSec  *  wfSrc.nBlockAlign;

	DWORD	dwSrcBytes  =  wfSrc.nAvgBytesPerSec;
#include	"unDeclareDebugNew.h"
	BYTE	*	pSrcData	=	new BYTE [dwSrcBytes];
#include	"declareDebugNew.h"
	BYTE	*	pData		=	pSrcData;
	double	f				=	1000.0;
	double	pi				=	4.0  *  atan(  1.0  );
	double	w				=	2.0  *  pi  *  f;
	//
	for  (  DWORD	dw = 0;  dw < dwSrcBytes; dw ++  )  {
		double  t	=	( double )dw  /  ( double )wfSrc.nSamplesPerSec;
		*pData		=	128  +  (  BYTE  )(  127  +  sin(  w  *  f  )  );
	}

	pWfSrc  =  &wfSrc;
	

	//  找到给定标签的对应的格式
	pWfDrv	=	get_driver_format(  hadid,  wFormatTag,  nChannels,  nSamplesPerSec,  wBitsPerSample  );
	if  (  !pWfDrv  )  goto  errLabel;
	traceLogA(  (char*)  "Driver format:%u bits,  %lu samples ps, %d channels\n ",  pWfDrv->wBitsPerSample,  pWfDrv->nSamplesPerSec,  pWfDrv->nChannels  );

	//  找到给定标签对应的驱动
	pWfPcm	=	get_driver_format(  hadid,	WAVE_FORMAT_PCM,  nChannels,  nSamplesPerSec,  wBitsPerSample  );
	if  (  !pWfPcm	)  goto  errLabel;
	traceLogA(  (char*)  "PCM  format: %u bits,  %lu samples ps, %d channels\n",  pWfPcm->wBitsPerSample,  pWfPcm->nSamplesPerSec,  pWfPcm->nChannels  );

	char  pcmBuf[100000];
	char  dstBuf[100000];
	DWORD	dstBytes;

	dstBytes  =  mycountof(  dstBuf  );
	//  if  (  convertAudio(  hadid,  pWfSrc,  pSrcData,  dwSrcBytes,  pWfPcm,  (  BYTE  *  )pcmBuf,  mycountof(  pcmBuf  ),  pWfDrv,  (  BYTE  *  )dstBuf,  &dstBytes  )  )  goto  errLabel;

	//
	char decBuf[100000];
	DWORD  decBytes;
	decBytes  =  mycountof(  decBuf  );
	//  convertAudio(  hadid,  pWfDrv,  (  BYTE  *  )dstBuf,  dstBytes,  pWfPcm,  (  BYTE  *  )pcmBuf,  mycountof(  pcmBuf  ),  pWfSrc,  (  BYTE  *  )decBuf,  &decBytes  );


	iErr  =  0;  goto  errLabel;


	//  第一步,用codec将wave转换为PCM
	mmr	=  acmStreamOpen(  &hstr,  had,  pWfSrc,  pWfPcm,  NULL,  NULL,  0,  ACM_STREAMOPENF_NONREALTIME  );
	if  (  mmr  )  goto  errLabel;
	bOpen_hstr  =  TRUE;
	
	//  为转换数据分配buf
	//  DWORD	dwSrcBytes	=	pWfSrc->nSamplesPerSec  *  wfSrc.wBitsPerSample  /  8;
	//  DWORD	dwDst1Samples	=	dwSrcSamples  *  pwfPCM->nSamplesPerSec  /  wfSrc.nSamplesPerSec;
	DWORD	dwDst1Bytes;dwDst1Bytes = (DWORD)(dwSrcBytes * pWfPcm->nAvgBytesPerSec * pWfPcm->nChannels * 1. / (pWfSrc->nAvgBytesPerSec * pWfSrc->nChannels));
#include	"unDeclareDebugNew.h"
	BYTE* pDst1Data;pDst1Data = new BYTE[dwDst1Bytes];
#include	"declareDebugNew.h"

	//  填入转换数据
	ACMSTREAMHEADER		strhdr;
	memset(  &strhdr,  0,  sizeof(  strhdr  )  );
	strhdr.cbStruct		=	sizeof(  strhdr  );
	strhdr.pbSrc		=	pSrcData;		// 源
	strhdr.cbSrcLength	=	dwSrcBytes;
	strhdr.pbDst		=	pDst1Data;		//  目的
	strhdr.cbDstLength	=	dwDst1Bytes;
	//  填写字头
	mmr	=	acmStreamPrepareHeader(  hstr,  &strhdr,  0  );
	mmr	=	acmStreamConvert(  hstr,  &strhdr,  0  );
	if  (  mmr  )  goto  errLabel;
	//  关闭
	acmStreamClose(  hstr,  0  );	hstr	=	NULL;
	bOpen_hstr  =  FALSE;


	//  最后一步,把PCM转换为最终格式
	mmr	=	acmStreamOpen(  &hstr,  NULL,  pWfPcm,  pWfDrv,  NULL,  NULL,  0,  ACM_STREAMOPENF_NONREALTIME  );
	if  (  mmr  )  goto  errLabel;
	bOpen_hstr  =  TRUE;

	//  为转换数据分配buf
	DWORD	dwDst2Bytes;dwDst2Bytes = pWfDrv->nAvgBytesPerSec * pWfDrv->nChannels * dwDst1Bytes / (pWfPcm->nAvgBytesPerSec * pWfPcm->nChannels);
	dwDst2Bytes				=	dwDst2Bytes  *  3  /  2;
#include	"unDeclareDebugNew.h"
	BYTE* pDst2Data;pDst2Data = new  BYTE[dwDst2Bytes];
#include	"declareDebugNew.h"
	//  填入转换数据
	ACMSTREAMHEADER		strhdr2;
	memset(  &strhdr2,  0,  sizeof(  strhdr2  )  );
	strhdr2.cbStruct		=	sizeof(  strhdr2  );
	strhdr2.pbSrc			=	pDst1Data;
	strhdr2.cbSrcLength		=	dwDst1Bytes;
	strhdr2.pbDst			=	pDst2Data;
	strhdr2.cbDstLength		=	dwDst2Bytes;
	//  填写字头
	mmr	=	acmStreamPrepareHeader(  hstr,  &strhdr2,  0  );
	mmr	=	acmStreamConvert(  hstr,  &strhdr2,  0  );
	if  (  mmr  )  return  -1;

	iErr  =  0;

errLabel:

	if  (  hstr  )  acmStreamClose(  hstr,  0  );
	if  (  had  )  acmDriverClose(  had,  0  );

	return  0;
}


 int  testAcm(  )
{
	showAcm(  );

	//  WORD	wFormatTag  =  WAVE_FORMAT_PCM;
	/*
	WORD	wFormatTag		=	WAVE_FORMAT_GSM610;
    WORD	nChannels		=	1;	
	DWORD	nSamplesPerSec	=	22050;
	WORD	wBitsPerSample  =	0;
	*/
	WORD	wFormatTag		=	WAVE_FORMAT_MPEGLAYER3;
    WORD	nChannels		=	2;	
	DWORD	nSamplesPerSec	=	11025;
	WORD	wBitsPerSample  =	0;

	goto  errLabel;

	HACMDRIVERID	hadid;hadid = find_driver(wFormatTag, nChannels, nSamplesPerSec, wBitsPerSample);
	if  (  hadid  ==  NULL  )  {
		traceLogA(  (char*)  "No dirver found."  );
		goto  errLabel;
	}
	traceLogA(  (char*)  "Driver found ( hadid: %4.4lxh)\n",  hadid  );

	if  (  testConvert(  hadid,  wFormatTag,  nChannels,  nSamplesPerSec,  wBitsPerSample  )  )  goto  errLabel;

	traceLogA(  (char*)  "ok"  );

errLabel:

	return  0;
}


//  因为音频压缩和解压缩可能较慢,不能及时完成.可以在音频数据里增加一个标志位,表明是否压缩.不能压缩的,可以用原始包发送和处理.





#endif


