#include	"stdafx.h"
//#include	"mytypes.h"
//#include	"tmpAACCommon.h"

//#include	"qyMcMainCommon.h"
//#include	"dumpAudio.h"
//#include	"myinttypes.h"
//
//#include    "qdc_AAC.h"

#include	<tchar.h>
#include	<string>

#include	"qyMcMainCommon.h"


#include "..\\qdc_open\\include\\qdcCommProc_open.h"
#include	"..\\aac\\include\\tmpAACCommon.h"

//

int  qdcInit_aac(QDC_MGR* p)
{
	if (qdc_aac_init())return -1;
	return 0;
}

int  qdcExit_aac(QDC_MGR* p)
{
	qdc_aac_exit();
	return 0;
}

int  qdcGetOutputByIndex_aac(QDC_OBJ_INFO* pQdcObjInfo, int  index, BYTE* pbOutData, unsigned  int* puiDataSize, unsigned  int* puiSampleTimeInMs, unsigned  int* pui_rtTimeLen)
{
	int iErr = -1;
	bool bDbg = true;

	


	if (!pQdcObjInfo->var.pObj) return -1;
	CQdcObj_aac* pObj = (CQdcObj_aac*)pQdcObjInfo->var.pObj;

	pObj->output.pBuf = nullptr;
	pObj->output.len = 0;

	if (pObj->bDec) {
		if (decA_getOutputByIndexAAC(pObj->m_index_qdcUnit, index, pbOutData, puiDataSize, bDbg))goto errLabel;
	}
	else {
		//
		if (!pObj->output.len) return -1;
		if (*puiDataSize < pObj->output.len) return -1;
		memcpy(pbOutData, pObj->output.pBuf, pObj->output.len);
		*puiDataSize = pObj->output.len;
		//
		pObj->output.len = 0;
		//
	}

	iErr = 0;
errLabel:
	return iErr;

}
//
int  qdcClearOutputs_aac(QDC_OBJ_INFO* pQdcObjInfo)
{

	int iErr = -1;

	traceLog((TCHAR*)_T("not finished"));
	return -1;

	iErr = 0;
errLabel:
	return iErr;

}

int  qdcExitDecompressAudio_aac(QDC_OBJ_INFO* pQdcObjInfo)
{
	bool bDbg = true;

	if (!pQdcObjInfo->var.pObj)  return 0;
	CQdcObj_aac* pObj = (CQdcObj_aac*)pQdcObjInfo->var.pObj;

	decA_exit_aac(pObj->m_index_qdcUnit, bDbg);

	{
		CQySyncObj syncObj;
		if (!syncObj.sync(CONST_mutexName_syncAAC)) {
			freeQdcAACUnitIndex(pObj->m_index_qdcUnit);
			pObj->m_index_qdcUnit = -1;
		}
	}

	//
	if (pObj->output.pBuf) {
		myfree(pObj->output.pBuf); pObj->output.pBuf = NULL;
	}

	//
	delete pObj;
	pQdcObjInfo->var.pObj = NULL;

	return 0;
}
//
int  qdcInitDecompressAudio_aac(void* pAudioCompressorCfg, QY_AUDIO_HEADER* pAh_compress, QY_AUDIO_HEADER* pAh_decompress, QDC_OBJ_INFO* pQdcObjInfo)
{
	int iErr = -1;
	bool bDbg = true;

	AUDIO_COMPRESSOR_CFG* cfg = (AUDIO_COMPRESSOR_CFG*)pAudioCompressorCfg;

	if (pQdcObjInfo->var.pObj) return -1;

	pQdcObjInfo->var.pObj = new CQdcObj_aac();
	if (!pQdcObjInfo->var.pObj) goto errLabel;
	CQdcObj_aac* pObj; pObj = (CQdcObj_aac*)pQdcObjInfo->var.pObj;

	{
		CQySyncObj syncObj;
		if (syncObj.sync(CONST_mutexName_syncAAC))goto errLabel;

		pObj->m_index_qdcUnit = newQdcAACUnitIndex();
		if (pObj->m_index_qdcUnit < 0)goto errLabel;
	}
	//
	pObj->bDec = true;

	unsigned int config; config = 0x1408;
	if (cfg)
		config = cfg->common.iAvgBitrateInKbps;
	//
	if (decA_init_aac(pObj->m_index_qdcUnit, config, bDbg)) goto errLabel;


	iErr = 0;
errLabel:
	if (iErr) {
		qdcExitDecompressAudio_aac(pQdcObjInfo);
	}
	return iErr;
}




int  qdcDecompressAudio_aac(QDC_OBJ_INFO* pQdcObjInfo, QY_AUDIO_HEADER* pAh_compress, BYTE* pInput,
	unsigned  int  uiInputLen, int  iSampleTimeInMs, unsigned  int  ui_rtTimeLen)
{
	int iErr = -1;
	bool bDbg = true;

	if (!pQdcObjInfo->var.pObj)  return -1;
	CQdcObj_aac* pObj = (CQdcObj_aac*)pQdcObjInfo->var.pObj;

	int inputPaddingSize = 0;
	int nPktDeced = 0;
	int iFmt_dec = 0;
	bool bBufTooSmall = false;

	if (decA_data_aac(pObj->m_index_qdcUnit, pInput, uiInputLen, inputPaddingSize, &nPktDeced, &iFmt_dec, NULL, NULL, &bBufTooSmall, bDbg)) goto errLabel;

	iErr = 0;
errLabel:
	return iErr;
}

//
//  2016/12/05
int  qdcDecompressAudioRun_aac(QDC_OBJ_INFO* pQdcObjInfo)
{
	int  iErr = -1;

	traceLog((TCHAR*)_T("not supported"));

	return -1;
}