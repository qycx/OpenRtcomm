

#include	"stdafx.h"

#include <qySyncObj.h>
#include <qysynccommproc.h>
#include	"ancCommProc_open.h"
#include <qytcharcommproc.h>

#include	"tmpLyraCommon.h"
#include	"qdcLyraPublic.h"

#include	"lyraEncAPublic.h"
#include	"lyraDecAPublic.h"



#if  10

//
__declspec(dllexport)
int  qdcInit_lyra(  QDC_MGR  *  p  )
{
	//
	return 0;
}

__declspec(dllexport)
int  qdcExit_lyra(  QDC_MGR  *  p  )
{
	//
	return 0;
}


//
int  enc_th_in(void* p0, void* p1, void* p2, void* p3)
{
	CQdcObj_lyra* pObj = (CQdcObj_lyra*)p0;
	//p1
	char* buf_i = (char*)p2;
	int* pLen_i = (int*)p3;

	if (!*pLen_i) { 
		OutputDebugString(_T("enc_th_in failed, *pLen_i is 0\n"));
		return  -1; 
	}

	//
	if (pObj->m_var.bQuit) {
		return  -1;
	}

	//tmpiRet = fread(buf_i, 1, *pLen_i, pIoHelp->fp_in);

	for (; ; ) {
		if (pObj->m_var.bQuit) {
			break;
		}
		if (*pLen_i <= pObj->in.len)  break;
		//
		TmpAPkt pkt;
		unsigned  int  pktLen;
		memset(&pkt, 0, offsetof(TmpAPkt, buf));
		pktLen = sizeof(TmpAPkt);
		if (qGetMsg(&pObj->m_q_in, &pkt, &pktLen)) {
			//  如果没数据了,就要等待
			Sleep(20);
			continue;
		}
		if (pkt.len + pObj->in.len > pObj->in.iBufSize) {
			OutputDebugString(_T("enc_th_in failed, l66\n"));
			break;
		}
		memcpy(pObj->in.pBuf + pObj->in.len, pkt.buf, pkt.len);
		pObj->in.len += pkt.len;

		//
		continue;
	}
	
	if (*pLen_i > pObj->in.len)  return  -1;
	
	memcpy(buf_i, pObj->in.pBuf, *pLen_i);
	pObj->in.len -= *pLen_i;
	if (pObj->in.len) {
		memcpy(pObj->in.pBuf, pObj->in.pBuf + *pLen_i, pObj->in.len);
	}

	//
	return  0;
}

int enc_th_out(void* p0, void* p1, void* p2, void* p3)
{
	CQdcObj_lyra* pObj = (CQdcObj_lyra*)p0;
	//p1
	char* buf_i = (char*)p2;
	int* pLen_i = (int*)p3;
	//
	if (*pLen_i <= 0)  return  -1;

	//
	pObj->m_var.last_pts++;

	//fwrite(buf_i, *pLen_i, 1, pIoHelp->fp_out);
	TmpAPkt tmpPkt;
	memset(&tmpPkt, 0, offsetof(TmpAPkt, buf));
	if (*pLen_i > sizeof(tmpPkt.buf)) {
		return -1;
	}
	memcpy(tmpPkt.buf, buf_i, *pLen_i);
	tmpPkt.len = *pLen_i;
	//
	tmpPkt.uiPts = pObj->m_var.last_pts;
	//
	int pktLen;
	pktLen = offsetof(TmpAPkt, buf) + tmpPkt.len;
	if (qPostMsg(&tmpPkt, pktLen, &pObj->m_q_out, _T(""))) {
		OutputDebugString(_T("enc_th_out failed,qPostMsg failed\n"));
		return  -1;
	}

	//
	return  0;
}


//
//
int  dec_th_in(void* p0, void* p1, void* p2, void* p3)
{
	int  iErr = -1;
	CQdcObj_lyra* pObj = (CQdcObj_lyra*)p0;
	//p1
	char* buf_i = (char*)p2;
	int* pLen_i = (int*)p3;

	//
	if (pObj->m_var.bQuit) {
		return  -1;
	}


	//	
	for (;;) {
		//
		if (pObj->m_var.bQuit) {
			return  -1;
		}

		TmpAPkt pkt;
		memset(&pkt, 0, offsetof(TmpAPkt, buf));
		unsigned  int pktLen;
		pktLen = sizeof(pkt);
		if (qGetMsg(&pObj->m_q_in, &pkt, &pktLen)) {
			Sleep(20);
			continue;
		}

		//
		if (*pLen_i < pkt.len) {
			OutputDebugString(_T("dec_th_in failed, *pLen_i  <  pkt.len\n"));
			break;
		}

		//
		memcpy(buf_i, pkt.buf, pkt.len);
		*pLen_i = pkt.len;

		//
		iErr = 0;

		break;
	}

	
	return  iErr;
}

int dec_th_out(void* p0, void* p1, void* p2, void* p3)
{
	int  iErr = -1;
	CQdcObj_lyra* pObj = (CQdcObj_lyra*)p0;
	//p1
	char* buf_i = (char*)p2;
	int* pLen_i = (int*)p3;
	//
	if (*pLen_i <= 0)  return  -1;

	do {

		//fwrite(buf_i, *pLen_i, 1, pIoHelp->fp_out);

		TmpAPkt pkt;
		memset(&pkt, 0, offsetof(TmpAPkt, buf));
		if (*pLen_i > sizeof(pkt.buf)) {
			break;
		}
		memcpy(pkt.buf, buf_i, *pLen_i);
		pkt.len = *pLen_i;
		
		int pktLen;
		pktLen = offsetof(TmpAPkt, buf) + pkt.len;

		if (qPostMsg(&pkt, pktLen, &pObj->m_q_out, _T("")) ){
			OutputDebugString(_T("dec_th_out.qPostMsg failed\n"));
			break;
		}

		iErr = 0;
	} while (false);

	//
	return  iErr;
}


//
extern "C" DWORD WINAPI lyra_mcThreadProc_enc(LPVOID lpParameter)
{
	CQdcObj_lyra* pObj = (CQdcObj_lyra*)lpParameter;
	
	int  tmpiRet = -1;
	int  iStep = 0;

	//
	tmpiRet =  doLyraEncA(pObj->m_var.pLyra_encDec,&iStep);

	//
	return  0;
}

//
extern "C" DWORD WINAPI lyra_mcThreadProc_dec(LPVOID lpParameter)
{
	CQdcObj_lyra* pObj = (CQdcObj_lyra*)lpParameter;

	int  tmpiRet = -1;
	int  iStep = 0;

	//
	tmpiRet = doLyraDecA(pObj->m_var.pLyra_encDec,&iStep);

	//
	return  0;
}


//
int  get_model_path(char* modelPath, int cntof_modelPath)
{
	//
	int  iErr = -1;
	TCHAR				tmpFileName[MAX_PATH + 1];
	TCHAR				pathBuf[MAX_PATH + 1];
	TCHAR* filePart;

	do {
		GetModuleFileName(NULL, tmpFileName, sizeof(tmpFileName) / sizeof(tmpFileName[0]));
		if (!GetFullPathName(tmpFileName, sizeof(pathBuf) / sizeof(pathBuf[0]), pathBuf, &filePart)) {
			break;
		}
		filePart[0] = 0;

		//
		char model_path[256];  model_path[0] = 0;
		myTChar2Utf8(pathBuf, model_path, mycountof(model_path));
		char* subDir; subDir = (char*)"lyra\\model_coeffs\\";
		_snprintf(model_path, sizeof(model_path), "%s\\%s", model_path, subDir);

		//
		if (!modelPath || !cntof_modelPath)  break;
		_snprintf(modelPath, cntof_modelPath, "%s", model_path  );

		//
		iErr = 0;
	} while (false);

	
	return  iErr;
}



__declspec(dllexport)
int  qdcInitCompressAudio_lyra(  void  *  pAudioCompressorCfg_reserved,  QY_AUDIO_HEADER  *  pAh_decompress,  QY_AUDIO_HEADER  *  pAh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int iErr = -1;
	bool bDbg=true;
	
	//
	AUDIO_COMPRESSOR_cfgCommon  *  pCompressor  =  (  AUDIO_COMPRESSOR_cfgCommon  *  )pAudioCompressorCfg_reserved;
	if  (  !pCompressor  )  return  -1;

	//
	if(pQdcObjInfo->var.pObj) return -1;

	do {


		//
		pQdcObjInfo->var.pObj = new CQdcObj_lyra();
		if (!pQdcObjInfo->var.pObj) goto errLabel;
		CQdcObj_lyra* pObj;
		pObj = (CQdcObj_lyra*)pQdcObjInfo->var.pObj;

		{
			CQySyncObj syncObj;
			if (syncObj.sync(CONST_mutexName_syncLyra))goto errLabel;

			//pObj->m_index_qdcUnit=newQdcUnitIndex();
			//if(pObj->m_index_qdcUnit<0)goto errLabel;
		}
		//
		int bit_rate;
		bit_rate = pCompressor->iAvgBitrateInKbps * 1000;

		//
		unsigned  int uiMaxQNodes = 125 * 2;     //  2 seconds, 25 pkts per second
		TCHAR  tBuf[128];


		//
		_sntprintf(tBuf, mycountof(tBuf), _T("lyra_encQ_in"));
		if (initGenericQ(tBuf, tBuf, 0, uiMaxQNodes, mymalloc, myfree, &pObj->m_q_in)) {
			break;
		}
		pObj->m_bInited_q_in = true;

		_sntprintf(tBuf, mycountof(tBuf), _T("lyra_encQ_out"));
		if (initGenericQ(tBuf, tBuf, 0, uiMaxQNodes, mymalloc, myfree, &pObj->m_q_out)) {
			break;
		}
		pObj->m_bInited_q_out = true;
		
		//
#if  0
		TCHAR				tmpFileName[MAX_PATH + 1];
		TCHAR				pathBuf[MAX_PATH + 1];
		TCHAR* filePart;

		GetModuleFileName(NULL, tmpFileName, sizeof(tmpFileName) / sizeof(tmpFileName[0]));
		if (!GetFullPathName(tmpFileName, sizeof(pathBuf) / sizeof(pathBuf[0]), pathBuf, &filePart))  goto  errLabel;
		filePart[0] = 0;

		//
		char model_path[256];  model_path[0] = 0;
		myTChar2Utf8(pathBuf, model_path, mycountof(model_path));
		char* subDir;subDir = (char*)"lyra\\model_coeffs\\";
		_snprintf(model_path, sizeof(model_path), "%s\\%s", model_path, subDir);
#endif 
		//
		char model_path[256];  model_path[0] = 0;
		get_model_path(model_path, mycountof(model_path));

		//		
		if (lyraEncA_init(3200, model_path,  enc_th_in, pQdcObjInfo->var.pObj, enc_th_out, pQdcObjInfo->var.pObj, &pObj->m_var.pLyra_encDec)) {
			break;
		}

		//
		memcpy(pAh_compress, pAh_decompress, sizeof(pAh_compress[0]));
		pAh_compress->wfx.wFormatTag = myWAVE_FORMAT_unknown;// WAVE_FORMAT_MPEGLAYER3;

		//
		int nAvgBytesPerSec;
		nAvgBytesPerSec = pAh_decompress->wfx.nSamplesPerSec * pAh_decompress->wfx.nChannels * pAh_decompress->wfx.wBitsPerSample / 8;
		if (nAvgBytesPerSec == 0)goto errLabel;

		//
		pObj->in.iBufSize = 2 * nAvgBytesPerSec;
		pObj->in.pBuf = (char*)mymalloc(pObj->in.iBufSize);
		if (pObj->in.pBuf == NULL)goto errLabel;

		//		
		pObj->output.iBufSize = 2 * nAvgBytesPerSec;
		pObj->output.pBuf = (char*)mymalloc(pObj->output.iBufSize);
		if (pObj->output.pBuf == NULL)goto errLabel;

		//
		DWORD  dwThreadDaemonId;
		pObj->m_var.hThread_encDec = CreateThread(NULL, 0, lyra_mcThreadProc_enc, pObj, CREATE_SUSPENDED, &dwThreadDaemonId);
		if (!pObj->m_var.hThread_encDec)  goto  errLabel;
		pObj->m_var.dwThreadId_encDec = dwThreadDaemonId;
		if (ResumeThread(pObj->m_var.hThread_encDec) == -1)  goto  errLabel;

		//
		iErr = 0;

	} while (false);

errLabel:
	if ( iErr ) {
		qdcExitCompressAudio_lyra(pQdcObjInfo);
	}
	return iErr;
}


__declspec(dllexport)
int  qdcExitCompressAudio_lyra(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int iErr = -1;
	bool bDbg=true;

	if( !pQdcObjInfo->var.pObj )  return 0;
	CQdcObj_lyra * pObj=(CQdcObj_lyra*)pQdcObjInfo->var.pObj;

	//
	pObj->m_var.bQuit = true;
	//
	waitForObject(&pObj->m_var.hThread_encDec, 10000);
	if (pObj->m_var.hThread_encDec) {
		OutputDebugString(_T("qdcExitCompressAudio_lyra err. hThread_enc is still alive\n"));
	}

	//
	lyraEncA_exit(&pObj->m_var.pLyra_encDec);

	//
	if (pObj->m_bInited_q_in) {
		exitGenericQ(&pObj->m_q_in);
		pObj->m_bInited_q_in = false;
	}
	if (pObj->m_bInited_q_out) {
		exitGenericQ(&pObj->m_q_out);
		pObj->m_bInited_q_out = false;
	}
	
	{
		CQySyncObj syncObj;
		if(!syncObj.sync(CONST_mutexName_syncLyra )){
#if  0
			freeQdcUnitIndex(pObj->m_index_qdcUnit);
			pObj->m_index_qdcUnit=-1;
#endif 
		}
	}
	
	//
	if(pObj->output.pBuf){
		myfree(pObj->output.pBuf);pObj->output.pBuf=NULL;
	}
	if (pObj->in.pBuf) {
		myfree(pObj->in.pBuf); pObj->in.pBuf = NULL;
	}

	//
	delete pObj;
	pQdcObjInfo->var.pObj=NULL;

	iErr = 0;
errLabel:
	return iErr;
}

__declspec(dllexport)
int  qdcCompressAudio_lyra(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_decompress,  BYTE  *  pInput,  unsigned  int  uiInputSize,  int  iSampleTimeInMs  )
{
	int iErr = -1;
	bool bDbg=false;//true;

	if(!pQdcObjInfo->var.pObj) return -1;
	CQdcObj_lyra * pObj=(CQdcObj_lyra*)pQdcObjInfo->var.pObj;

	do {



		//
		TmpAPkt pkt;
		memset(&pkt, 0, offsetof(TmpAPkt, buf));
		pkt.iSampleTimeInMs = iSampleTimeInMs;
		if (uiInputSize > sizeof(pkt.buf)) {
			break;
		}
			
		memcpy(pkt.buf, pInput, uiInputSize);
		pkt.len = uiInputSize;
		int pktLen;
		pktLen = offsetof(TmpAPkt, buf) + pkt.len;
		if (qPostMsg(&pkt, pktLen, &pObj->m_q_in, _T("")  )) {
			//
			OutputDebugString(_T("qdcCompressAudio_lyra failed, qPostMsg failed\n"));
			//
			break;
		}
	


			//
			iErr = 0;
	} while (false);

errLabel:
	return iErr;
}

//  2016/12/05
__declspec(dllexport)
int  qdcCompressAudioRun_lyra(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	//traceLog((TCHAR*)_T("not finished"));

	return -1;
}

//
__declspec(dllexport)
int  qdcGetOutputByIndex_lyra(  QDC_OBJ_INFO  *  pQdcObjInfo,  int  index,  BYTE *  pbOutData,  unsigned  int  *  puiDataSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  pui_rtTimeLen  )
{		
	int iErr = -1;
	bool bDbg=true;

	if(!pQdcObjInfo->var.pObj) return -1;
	CQdcObj_lyra * pObj=(CQdcObj_lyra*)pQdcObjInfo->var.pObj;

	do {
		//
		if (pObj->bDec) {
			//if(decV_getOutputByIndex(pObj->m_index_qdcUnit,index,pbOutData,puiDataSize,bDbg ))goto errLabel;

						//
			TmpAPkt tmpPkt;
			unsigned  int  pktLen = sizeof(tmpPkt);
			if (qGetMsg(&pObj->m_q_out, &tmpPkt, &pktLen)) {
				break;
			}
			//
			if (*puiDataSize < tmpPkt.len) {
				OutputDebugString(_T("qdcGetOutputByIndex_lyra failed. puiDataSize < tmpPkt.len\n"));
				break;
			}
			memcpy(pbOutData, tmpPkt.buf, tmpPkt.len);
			*puiDataSize = tmpPkt.len;

			//
		
		}
		else {
			//
#if  0
			if (!pObj->output.len) return -1;
			if (*puiDataSize < pObj->output.len) return -1;
			memcpy(pbOutData, pObj->output.pBuf, pObj->output.len);
			*puiDataSize = pObj->output.len;
			//
			pObj->output.len = 0;
#endif 
			//
			TmpAPkt tmpPkt;
			unsigned  int  pktLen = sizeof(tmpPkt);
			if (qGetMsg(&pObj->m_q_out, &tmpPkt, &pktLen)) {
				break;
			}
			//
			if (*puiDataSize < tmpPkt.len) {
				OutputDebugString(_T("qdcGetOutputByIndex_lyra failed. puiDataSize < tmpPkt.len\n"));
				break;
			}
			memcpy(pbOutData, tmpPkt.buf, tmpPkt.len);
			*puiDataSize = tmpPkt.len;

			//
		}

		iErr = 0;

	} while (false);


	
errLabel:
	return iErr;

}


__declspec(dllexport)
int  qdcClearOutputs_lyra(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
		
	int iErr = -1;

	//traceLog((TCHAR*)_T("not finished"));

	return -1;

	iErr = 0;
errLabel:
	return iErr;

}


//
__declspec(dllexport)
int  qdcInitDecompressAudio_lyra(  void  *  pAudioCompressorCfg,  QY_AUDIO_HEADER  *  pAh_compress,  QY_AUDIO_HEADER  *  pAh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int iErr = -1;
	bool bDbg = true;
			
	if(pQdcObjInfo->var.pObj) return -1;

	do {
		pQdcObjInfo->var.pObj = new CQdcObj_lyra();
		if (!pQdcObjInfo->var.pObj) goto errLabel;
		CQdcObj_lyra* pObj;
		pObj = (CQdcObj_lyra*)pQdcObjInfo->var.pObj;

		{
			CQySyncObj syncObj;
			if (syncObj.sync(CONST_mutexName_syncLyra))goto errLabel;

			//pObj->m_index_qdcUnit=newQdcUnitIndex();
			//if(pObj->m_index_qdcUnit<0)goto errLabel;
		}
		//
		pObj->bDec = true;


		//				
		//
		unsigned  int uiMaxQNodes = 125 * 2;     //  2 seconds, 25 pkts per second
		TCHAR  tBuf[128];

		//
		int  threadId = GetCurrentThreadId();

		//
		_sntprintf(tBuf, mycountof(tBuf), _T("lyra_decQ_in-%d"), threadId);
		if (initGenericQ(tBuf, tBuf, 0, uiMaxQNodes, mymalloc, myfree, &pObj->m_q_in)) {
			break;
		}
		pObj->m_bInited_q_in = true;

		//
		_sntprintf(tBuf, mycountof(tBuf), _T("lyra_decQ_out-%d"), threadId);
		if (initGenericQ(tBuf, tBuf, 0, uiMaxQNodes, mymalloc, myfree, &pObj->m_q_out)) {
			break;
		}
		pObj->m_bInited_q_out = true;


		//
		char model_path[256];  model_path[0] = 0;
		get_model_path(model_path, mycountof(model_path));

		//
		//if(decA_init(pObj->m_index_qdcUnit,WAVE_FORMAT_MPEGLAYER3,bDbg ) ) goto errLabel;
		//
		if (lyraDecA_init(3200, model_path,  dec_th_in, pObj, dec_th_out, pObj, &pObj->m_var.pLyra_encDec)) {
			break;
		}

		//
		DWORD  dwThreadDaemonId;
		pObj->m_var.hThread_encDec = CreateThread(NULL, 0, lyra_mcThreadProc_dec, pObj, CREATE_SUSPENDED, &dwThreadDaemonId);
		if (!pObj->m_var.hThread_encDec)  goto  errLabel;
		pObj->m_var.dwThreadId_encDec = dwThreadDaemonId;
		if (ResumeThread(pObj->m_var.hThread_encDec) == -1)  goto  errLabel;



		//
		iErr = 0;

	} while (false);

errLabel:
	if(iErr ){
		qdcExitDecompressAudio_lyra(pQdcObjInfo);
	}
	return iErr;
}

__declspec(dllexport)
int  qdcExitDecompressAudio_lyra(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
		bool bDbg=true;

	if( !pQdcObjInfo->var.pObj )  return 0;
	CQdcObj_lyra * pObj=(CQdcObj_lyra*)pQdcObjInfo->var.pObj;

	
	//
	pObj->m_var.bQuit = true;
	//
	waitForObject(&pObj->m_var.hThread_encDec, 10000);
	if (pObj->m_var.hThread_encDec) {
		OutputDebugString(_T("qdcExitDecompressAudio_lyra err. hThread_enc is still alive\n"));
	}


	//decA_exit(pObj->m_index_qdcUnit,bDbg );
	//
	lyraDecA_exit(&pObj->m_var.pLyra_encDec);
	
	{
		CQySyncObj syncObj;
		if(!syncObj.sync(CONST_mutexName_syncLyra )){
			//freeQdcUnitIndex(pObj->m_index_qdcUnit);
			//pObj->m_index_qdcUnit=-1;
		}
	}
	
	//
	if (pObj->m_bInited_q_in) {
		exitGenericQ(&pObj->m_q_in);
		pObj->m_bInited_q_in = false;
	}
	if (pObj->m_bInited_q_out) {
		exitGenericQ(&pObj->m_q_out);
		pObj->m_bInited_q_out = false;
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


__declspec(dllexport)
int  qdcDecompressAudio_lyra(  QDC_OBJ_INFO  *  pQdcObjInfo,  QY_AUDIO_HEADER  *  pAh_compress,  BYTE  *  pInput,  unsigned  int  uiInputLen,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  )
{
	int iErr = -1;
	bool bDbg=true;

	if( !pQdcObjInfo->var.pObj )  return -1;
	CQdcObj_lyra * pObj=(CQdcObj_lyra*)pQdcObjInfo->var.pObj;

	do {
		int inputPaddingSize = 0;
		int nPktDeced = 0;
		int iFmt_dec = 0;
		bool bBufTooSmall = false;

		//if(decA_data(pObj->m_index_qdcUnit,pInput,uiInputLen,inputPaddingSize,&nPktDeced,&iFmt_dec,NULL,NULL,&bBufTooSmall,bDbg )) goto errLabel;

		//
		TmpAPkt pkt;
		memset(&pkt, 0, offsetof(TmpAPkt, buf));
		if (uiInputLen > sizeof(pkt.buf))  break;
		memcpy(pkt.buf, pInput, uiInputLen);
		pkt.len = uiInputLen;
		pkt.iSampleTimeInMs = iSampleTimeInMs;
		int pktLen;
		pktLen = offsetof(TmpAPkt, buf) + pkt.len;
		if (qPostMsg(&pkt, pktLen, &pObj->m_q_in, _T(""))) {
			OutputDebugString(_T("qdcDecA_lyra. qPostMsg failed\n"));
			break;
		}

		//
		iErr = 0;
	} while (false);

errLabel:
	return iErr;
}

//
//  2016/12/05
__declspec(dllexport)
int  qdcDecompressAudioRun_lyra(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int  iErr = -1;

	//traceLog((TCHAR*)_T("not supported"));

	return -1;
}

#endif 



