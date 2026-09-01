
#include	"stdafx.h"

#include	<stddef.h>
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>
#include	<time.h>
#include	<tchar.h>

//#include	"qyMcMainCommon.h"
#if 0
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"tmpCeLib.h"
#endif

//#include	"qyAvRecord.h"
//#include	"qyAvRecord_dx.h"
//#include	"qmcSound_dx.h"

//#include	"qmcVideoCapture_isCli.h"
#include	"qmOpenCommon.h"
#include	"saveAvProc_open.h"
#include <showInfo_open.h>
#include <stdio.h>
//#include	"ctxMcThread.h"




int  doFileHead_qvcf(  void  *  pTransform,  LPCTSTR  fileName,  int  iFourcc,  SAVE_av_procInfo  *  pSave,  void  *  pCTX_mc_saveAv  )
{
	int		iErr	=	-1;
	CTX_mc_saveAv  *  pCtx  =  (  CTX_mc_saveAv  *  )pCTX_mc_saveAv;

#if 0

	if  (  pSave->fp  )  return  -1;

	pSave->fp  =  _tfopen(  fileName,  _T(  "wb"  )  );
	if  (  !pSave->fp  )  {
		showInfo_open0(  0,  0,  _T(  "doFileHead_vwf failed"  )  );
		goto  errLabel;
	}
	
	unsigned  char  *  pBuf  =  pCtx->pBuf_forSaving;
	unsigned  int  len  =  pCtx->uiBufSize_pBuf;

	//
	if  (  qvcf_write_fileHeader(  qvcfVer(  ),  (  char  *  )pBuf,  &len,  pSave->fp  )  )  goto  errLabel;
	
	//
	VCF_streamInfo_u  vsu;

	//
	{
	memset(  &vsu,  0,  sizeof(  vsu  )  );	
	VCF_streamInfo_ucCompressors  &  vsc  =  vsu.ucCompressors;
	vsc.idInfo.ui64Id  =  pSave->audio.idInfo.ui64Id;
	vsc.uiTranNo  =  pSave->audio.ta.uiTranNo_openAvDev;
	vsc.ucMediaType  =  CONST_vcfMediaType_a;
	vsc.usDataType  =  CONST_vcfDataType_ucCompressors;
	//
	vsc.ucCompressors  =  pSave->audio.ta.compressor.common.ucCompressors;

	//
	len  =  pCtx->uiBufSize_pBuf;

	//
	if  (  qvcf_write_streamInfo(  (  VCF_streamInfo_common  *  )&vsc,  (  char  *  )pBuf,  &len,  pSave->fp  )  )  goto  errLabel;
	}


	//  ah_compress
	{
	memset(  &vsu,  0,  sizeof(  vsu  )  );	
	VCF_streamInfo_ah  &  vsa  =  vsu.ah;
	vsa.idInfo.ui64Id  =  pSave->audio.idInfo.ui64Id;
	vsa.uiTranNo  =  pSave->audio.ta.uiTranNo_openAvDev;
	vsa.ucMediaType  =  CONST_vcfMediaType_a;
	vsa.usDataType  =  CONST_vcfDataType_ah;
	//
	vsa.ah  =  pSave->audio.ta.ah_compress;

	//
	len  =  pCtx->uiBufSize_pBuf;

	//
	if  (  qvcf_write_streamInfo(  (  VCF_streamInfo_common  *  )&vsa,  (  char  *  )pBuf,  &len,  pSave->fp  )  )  goto  errLabel;
	}
	
	//  ah_decompress
	{
	memset(  &vsu,  0,  sizeof(  vsu  )  );	
	VCF_streamInfo_ah  &  vsa  =  vsu.ah;
	
	vsa.idInfo.ui64Id  =  pSave->audio.idInfo.ui64Id;
	vsa.uiTranNo  =  pSave->audio.ta.uiTranNo_openAvDev;
	vsa.ucMediaType  =  CONST_vcfMediaType_a;
	vsa.usDataType  =  CONST_vcfDataType_ah;
	//
	vsa.ah  =  pSave->audio.ta.ah_decompress;

	//
	len  =  pCtx->uiBufSize_pBuf;

	//
	if  (  qvcf_write_streamInfo(  (  VCF_streamInfo_common  *  )&vsa,  (  char  *  )pBuf,  &len,  pSave->fp  )  )  goto  errLabel;
	}

	//
	{
	memset(  &vsu,  0,  sizeof(  vsu  )  );	
	VCF_streamInfo_ucCompressors  &  vsc  =  vsu.ucCompressors;
	vsc.idInfo.ui64Id  =  pSave->video.idInfo.ui64Id;
	vsc.uiTranNo  =  pSave->video.tv.uiTranNo_openAvDev;
	vsc.ucMediaType  =  CONST_vcfMediaType_v;
	vsc.usDataType  =  CONST_vcfDataType_ucCompressors;
	//
	vsc.ucCompressors  =  pSave->video.tv.compressor.common.ucCompressors;

	//
	len  =  pCtx->uiBufSize_pBuf;

	//
	if  (  qvcf_write_streamInfo(  (  VCF_streamInfo_common  *  )&vsc,  (  char  *  )pBuf,  &len,  pSave->fp  )  )  goto  errLabel;
	}

	//
	{
	memset(  &vsu,  0,  sizeof(  vsu  )  );	
	VCF_streamInfo_vh  &  vsv  =  vsu.vh;
	vsv.idInfo.ui64Id  =  pSave->video.idInfo.ui64Id;
	vsv.uiTranNo  =  pSave->video.tv.uiTranNo_openAvDev;
	vsv.ucMediaType  =  CONST_vcfMediaType_v;
	vsv.usDataType  =  CONST_vcfDataType_vh;
	//
	vsv.vh  =  pSave->video.tv.vh_compress;

	//
	len  =  pCtx->uiBufSize_pBuf;

	//
	if  (  qvcf_write_streamInfo(  (  VCF_streamInfo_common  *  )&vsv,  (  char  *  )pBuf,  &len,  pSave->fp  )  )  goto  errLabel;
	}



	//
	{
	memset(  &vsu,  0,  sizeof(  vsu  )  );	
	VCF_streamInfo_spsPps  &  vss  =  vsu.spsPps;
	vss.idInfo.ui64Id  =  pSave->video.idInfo.ui64Id;
	vss.uiTranNo  =  pSave->video.tv.uiTranNo_openAvDev;
	vss.ucMediaType  =  CONST_vcfMediaType_v;
	vss.usDataType  =  CONST_vcfDataType_spsPps;
	//
	vss.vh_stream  =  pSave->video.tv.vh_stream;

	//
	len  =  pCtx->uiBufSize_pBuf;

	//
	if  (  qvcf_write_streamInfo(  (  VCF_streamInfo_common  *  )&vss,  (  char  *  )pBuf,  &len,  pSave->fp  )  )  goto  errLabel;
	}

	//
	{
	memset(  &vsu,  0,  sizeof(  vsu  )  );	
	VCF_streamInfo_vh  &  vsv  =  vsu.vh;
	vsv.idInfo.ui64Id  =  pSave->video.idInfo.ui64Id;
	vsv.uiTranNo  =  pSave->video.tv.uiTranNo_openAvDev;
	vsv.ucMediaType  =  CONST_vcfMediaType_v;
	vsv.usDataType  =  CONST_vcfDataType_vh;
	//
	vsv.vh  =  pSave->video.tv.vh_decompress;

	//
	len  =  pCtx->uiBufSize_pBuf;

	//
	if  (  qvcf_write_streamInfo(  (  VCF_streamInfo_common  *  )&vsv,  (  char  *  )pBuf,  &len,  pSave->fp  )  )  goto  errLabel;
	}


#endif


	//
	iErr  =  0;	
errLabel:
	return  iErr;
}

