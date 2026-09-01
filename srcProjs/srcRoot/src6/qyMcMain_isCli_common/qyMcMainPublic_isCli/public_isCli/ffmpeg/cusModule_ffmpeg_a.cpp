

#include	"stdafx.h"
#include	"tmpFfmpegCommon.h"


//
int  qdcInit_ffmpeg(  QDC_MGR  *  p  )
{
	if(qdc_init())return -1;
	return 0;
}

int  qdcExit_ffmpeg(  QDC_MGR  *  p  )
{
	qdc_exit();
	return 0;
}



int  qdcInitCompressAudio_ffmpeg(  void  *  pAudioCompressorCfg_reserved,  QY_AUDIO_HEADER  *  pAh_decompress,  QY_AUDIO_HEADER  *  pAh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int iErr = -1;
	bool bDbg=true;
	
	//
	AUDIO_COMPRESSOR_cfgCommon  *  pCompressor  =  (  AUDIO_COMPRESSOR_cfgCommon  *  )pAudioCompressorCfg_reserved;
	if  (  !pCompressor  )  return  -1;

	//
	if(pQdcObjInfo->var.pObj) return -1;

	//
	pQdcObjInfo->var.pObj=new CQdcObj_ffmpeg();
	if ( !pQdcObjInfo->var.pObj ) goto errLabel;
	CQdcObj_ffmpeg* pObj; pObj = (CQdcObj_ffmpeg*)pQdcObjInfo->var.pObj;

	{
		CQySyncObj syncObj;
		if(syncObj.sync(CONST_mutexName_syncFfmpeg))goto errLabel;

		pObj->m_index_qdcUnit=newQdcUnitIndex();
		if(pObj->m_index_qdcUnit<0)goto errLabel;
	}
	//
	int bit_rate; bit_rate = pCompressor->iAvgBitrateInKbps * 1000;
	//
	if(encA_init(pObj->m_index_qdcUnit,WAVE_FORMAT_MPEGLAYER3,bit_rate,bDbg ) ) goto errLabel;
	
	//
	memcpy(  pAh_compress,  pAh_decompress,  sizeof(  pAh_compress[0]  )  );
	pAh_compress->wfx.wFormatTag  =  WAVE_FORMAT_MPEGLAYER3;

	//
	int nAvgBytesPerSec; nAvgBytesPerSec = pAh_decompress->wfx.nSamplesPerSec * pAh_decompress->wfx.nChannels * pAh_decompress->wfx.wBitsPerSample / 8;
	if(nAvgBytesPerSec==0)goto errLabel;
	pObj->output.iBufSize=2*nAvgBytesPerSec;
	pObj->output.pBuf=(char*)mymalloc(pObj->output.iBufSize);
	if(pObj->output.pBuf==NULL)goto errLabel;


	iErr = 0;
errLabel:
	if ( iErr ) {
		qdcExitCompressAudio_ffmpeg(pQdcObjInfo);
	}
	return iErr;
}



int  qdcExitCompressAudio_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int iErr = -1;
	bool bDbg=true;

	if( !pQdcObjInfo->var.pObj )  return 0;
	CQdcObj_ffmpeg * pObj=(CQdcObj_ffmpeg*)pQdcObjInfo->var.pObj;

	encA_exit(pObj->m_index_qdcUnit,bDbg );
	
	{
		CQySyncObj syncObj;
		if(!syncObj.sync(CONST_mutexName_syncFfmpeg )){
			freeQdcUnitIndex(pObj->m_index_qdcUnit);
			pObj->m_index_qdcUnit=-1;
		}
	}
	
	//
	if(pObj->output.pBuf){
		myfree(pObj->output.pBuf);pObj->output.pBuf=NULL;
	}

	//
	delete pObj;
	pQdcObjInfo->var.pObj=NULL;

	iErr = 0;
errLabel:
	return iErr;
}


int  qdcCompressAudio_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_decompress,  BYTE  *  pInput,  unsigned  int  uiInputSize,  int  iSampleTimeInMs  )
{
	int iErr = -1;
	bool bDbg=false;//true;

	if(!pQdcObjInfo->var.pObj) return -1;
	CQdcObj_ffmpeg * pObj=(CQdcObj_ffmpeg*)pQdcObjInfo->var.pObj;

	if(pObj->output.len) {
		traceLog((TCHAR*)_T("qdcCompressAudio_ffmpeg failed, output.len is not 0"));
		goto errLabel;
	}

	int len; len = pObj->output.iBufSize;
	if(encA_data(pObj->m_index_qdcUnit,pInput,uiInputSize,(byte*)pObj->output.pBuf,&len,bDbg ))goto errLabel;

	pObj->output.len=len;

	iErr = 0;
errLabel:
	return iErr;
}

//  2016/12/05
int  qdcCompressAudioRun_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	traceLog((TCHAR*)_T("not finished"));

	return -1;
}

//
int  qdcGetOutputByIndex_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo,  int  index,  BYTE *  pbOutData,  unsigned  int  *  puiDataSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  pui_rtTimeLen  )
{		
	int iErr = -1;
	bool bDbg=true;

	if(!pQdcObjInfo->var.pObj) return -1;
	CQdcObj_ffmpeg * pObj=(CQdcObj_ffmpeg*)pQdcObjInfo->var.pObj;

	if(pObj->bDec){
		if(decV_getOutputByIndex(pObj->m_index_qdcUnit,index,pbOutData,puiDataSize,bDbg ))goto errLabel;
		}
	else {
		//
		if(!pObj->output.len ) return -1;
		if(*puiDataSize<pObj->output.len) return -1;
		memcpy(pbOutData,pObj->output.pBuf,pObj->output.len);
		*puiDataSize=pObj->output.len;
		//
		pObj->output.len=0;
		//
	}



	iErr = 0;
errLabel:
	return iErr;

}

int  qdcClearOutputs_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
		
	int iErr = -1;

	traceLog((TCHAR*)_T("not finished"));
	return -1;

	iErr = 0;
errLabel:
	return iErr;

}


//
int  qdcInitDecompressAudio_ffmpeg(  void  *  pAudioCompressorCfg,  QY_AUDIO_HEADER  *  pAh_compress,  QY_AUDIO_HEADER  *  pAh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int iErr = -1;
	bool bDbg = true;

		if(pQdcObjInfo->var.pObj) return -1;

	pQdcObjInfo->var.pObj=new CQdcObj_ffmpeg();
	if ( !pQdcObjInfo->var.pObj ) goto errLabel;
	CQdcObj_ffmpeg* pObj; pObj = (CQdcObj_ffmpeg*)pQdcObjInfo->var.pObj;

	{
		CQySyncObj syncObj;
		if(syncObj.sync(CONST_mutexName_syncFfmpeg))goto errLabel;

		pObj->m_index_qdcUnit=newQdcUnitIndex();
		if(pObj->m_index_qdcUnit<0)goto errLabel;
	}
	//
	pObj->bDec=true;
	//
	if(decA_init(pObj->m_index_qdcUnit,WAVE_FORMAT_MPEGLAYER3,bDbg ) ) goto errLabel;
	

	iErr = 0;
errLabel:
	if(iErr ){
		qdcExitCompressAudio_ffmpeg(pQdcObjInfo);
	}
	return iErr;
}

int  qdcExitDecompressAudio_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
		bool bDbg=true;

	if( !pQdcObjInfo->var.pObj )  return 0;
	CQdcObj_ffmpeg * pObj=(CQdcObj_ffmpeg*)pQdcObjInfo->var.pObj;

	decA_exit(pObj->m_index_qdcUnit,bDbg );
	
	{
		CQySyncObj syncObj;
		if(!syncObj.sync(CONST_mutexName_syncFfmpeg )){
			freeQdcUnitIndex(pObj->m_index_qdcUnit);
			pObj->m_index_qdcUnit=-1;
		}
	}
	
	//
	if(pObj->output.pBuf){
		myfree(pObj->output.pBuf);pObj->output.pBuf=NULL;
	}

	//
	delete pObj;
	pQdcObjInfo->var.pObj=NULL;

	return 0;
}


int  qdcDecompressAudio_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_compress,  BYTE  *  pInput,  unsigned  int  uiInputLen,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  )
{
	int iErr = -1;
	bool bDbg = false;//

	//
	if (0) {
		//bDbg=  true;
	}

	//
	if( !pQdcObjInfo->var.pObj )  return -1;
	CQdcObj_ffmpeg * pObj=(CQdcObj_ffmpeg*)pQdcObjInfo->var.pObj;

	int inputPaddingSize=0;
	int nPktDeced=0;
	int iFmt_dec=0;
	bool bBufTooSmall=false;

	if(decA_data(pObj->m_index_qdcUnit,pInput,uiInputLen,inputPaddingSize,&nPktDeced,&iFmt_dec,NULL,NULL,&bBufTooSmall,bDbg )) goto errLabel;

	iErr = 0;
errLabel:
	return iErr;
}

//
//  2016/12/05
int  qdcDecompressAudioRun_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int  iErr = -1;

	traceLog((TCHAR*)_T("not supported"));

	return -1;
}



