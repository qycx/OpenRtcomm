

#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//#include	"qmcVideoCapture_isCli.h"
//#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
//  #include	"myfourcc.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

#include	"qmcVideoCapture_rtsp.h"

//#include	"isCliHelpPublic.h"
#include	"qmcCfg.h"


//
int smplYUVWriter_WriteNextFrame_pre_1(void* pQdcObjInfoParam, void* pQDC_OBJ_transCommon, void* pYUVWriter_var)
{
	int  sts = -1;
	BOOL  bMsgGot = FALSE;

	QDC_OBJ_transCommon* pTrans = (QDC_OBJ_transCommon*)pQDC_OBJ_transCommon;
	YUVWriter_var1& m_var = *(YUVWriter_var1*)pYUVWriter_var;

	if (!pTrans->bInited2)  return  0;

	//
	QDC_OBJ_INFO* pQdcObjInfo = (QDC_OBJ_INFO*)m_var.pQdcObjInfoParam;
	//
	DEBUG_step_dec* pDebugStepDec = (DEBUG_step_dec*)getDebugStep_sth(0, CONST_debugStepType_dec, (MY_DEBUG_STEP*)pQdcObjInfo->var.pDebugStep);
	if (!pDebugStepDec)  return  -1;
	//
	if (pQdcObjInfo->cfg.v.uiTransformType_pParent != CONST_uiTransformType_dec)  return  -1;// goto  errLabel;
	QY_TRANSFORM* pTransform = (QY_TRANSFORM*)pQdcObjInfo->cfg.v.pParent_transform;
	//
	MC_VAR_common* pProcInfoCommon = (MC_VAR_common*)pTransform->pProcInfo;


	//
	int  nTimeInMs = pDebugStepDec->nTimeInMs_smplYUVWriter_WriteNextFrame0;
	int  tmp_fps = 0;
	if (nTimeInMs) {
		tmp_fps = 1000 / nTimeInMs;
		pQdcObjInfo->cfg.v.tmp_max_dec_fps = tmp_fps;
	}
	else {
		tmp_fps = pQdcObjInfo->cfg.v.tmp_max_dec_fps;
	}
	if (tmp_fps > 1) {
		//
#if  0  //  2021/05/23
		TCHAR  tBuf[128];
		_sntprintf(tBuf, mycountof(tBuf), _T("%I64u.smplYUVWriter_WriteNextFrame_pre"), pTransform->video.idInfo.ui64Id);
		//
		if (setPktInputInfo(pProcInfoCommon, &pQdcObjInfo->cfg.v.inputInfo, tmp_fps, FALSE, NULL, tBuf)) {
#ifdef  __DEBUG__
			traceLog(_T("smplYUVWriter_WriteNextFrame_pre: pkt skipped"));
			showInfo_open0(0, 0, _T("smplYUVWriter_WriteNextFrame_pre: pkt skipped"));
#endif
			goto  errLabel;
		}
#endif
	}


	sts = 0;

errLabel:

	return  sts;
}


//  2015/01/17
//  2014/07/23
int smplYUVWriter_WriteNextFrame0_1(void* pQdcObjInfoParam, void* pQDC_OBJ_transCommon, int  iFourcc, void* pYUVWriter_var, void* pImg, unsigned  int  cropW, unsigned  int  cropH, unsigned  int  pitch, PF_img_to_yuv  pf_img_to_yuv, double  dFrameRate, LPCTSTR  hint)
{
	int  sts = -1;
	BOOL  bMsgGot = FALSE;

	QDC_OBJ_transCommon* pTrans = (QDC_OBJ_transCommon*)pQDC_OBJ_transCommon;
	YUVWriter_var1& m_var = *(YUVWriter_var1*)pYUVWriter_var;

	//  2015/10/04
	if (!hint)  hint = _T("");

	//
	unsigned  int  i, j, h, w;

	//  2011/12/04. 因为只能存放一祯，所以需要清0
	if (!m_var.pQdcObjInfoParam
		|| !m_var.pPkt1)
	{
		showInfo_open0(0, 0, _T("yuvWrite::write failed, pPkt is null. skipped"));
		return  0;
	}
	QDC_OBJ_INFO* pQdcObjInfo = (QDC_OBJ_INFO*)m_var.pQdcObjInfoParam;

	DEBUG_step_dec* pDebugStepDec = (DEBUG_step_dec*)getDebugStep_sth(0, CONST_debugStepType_dec, (MY_DEBUG_STEP*)pQdcObjInfo->var.pDebugStep);
	if (!pDebugStepDec)  return  -1;

	//
	DWORD  dwTickCnt_start = GetTickCount();


	//
#if  10
	if (!pTrans->bInited2) {

		int  imgWidth = cropW;	//  pInfo->CropW;
		int  imgHeight = cropH;	//  pInfo->CropH;
		if (!imgWidth || !imgHeight) {
			showInfo_open0(0, 0, _T("smplYUVWriter_WriteNextFrame failed, imgW or imgH is 0"));
			goto  errLabel;
		}

		//  2014/04/22	 
		//
		BITMAPINFOHEADER  bih;
		//  makeBmpInfoHeader_yv12(  12,  imgWidth,  imgHeight,  &bih  );
		makeBmpInfoHeader_yuv(iFourcc, 12, imgWidth, imgHeight, &bih);
		if (pQdcObjInfo->cfg.v.dec.pf_updateDecVideoParam(&bih, dFrameRate, pQdcObjInfo->cfg.v.pParent_transform, pQdcObjInfo->cfg.v.uiTransformType_pParent)) {
			showInfo_open0(0, 0, _T("decPipeline: updateDecVideoParam  failed"));
			goto  errLabel;
		}

		//  qdcObjInfo.
		pQdcObjInfo->var.cbOutputBuffer = M_sizeImage_open(24, imgWidth, imgHeight);
		pQdcObjInfo->var.cbInputBuffer = pQdcObjInfo->var.cbOutputBuffer;


		//
		//
		memset(&m_var.outputInfo, 0, sizeof(m_var.outputInfo));

		//
		pTrans->bInited2 = TRUE;


	}


#endif


	//
	BITMAPINFOHEADER	bih_trans;
	if (pQdcObjInfo->cfg.v.pf_transformGetBih(pQdcObjInfo->cfg.v.pParent_transform, &bih_trans, 0)) {
		goto  errLabel;
	}
	if (!bih_trans.biWidth || !bih_trans.biHeight) {
		showInfo_open0(0, 0, _T("failed: bih_trans.w,h is 0"));
		goto  errLabel;
	}
	//  makeBmpInfoHeader_yv12(  12,  bih_trans.biWidth,  bih_trans.biHeight,  &bih_trans  );
	makeBmpInfoHeader_yuv(iFourcc, 12, bih_trans.biWidth, bih_trans.biHeight, &bih_trans);


	//
	for (; ; ) {

		//  2015/01/17
		pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(m_var.pPkt1, _T("smplYUVWriter"));

		//
		unsigned  int  size = m_var.size_pPkt;
		if (qGetMsg((GENERIC_Q*)pQdcObjInfo->cfg.v.pTmpDataQ, m_var.pPkt1, &size)) {
			TCHAR  tBuf[128] = _T("");
			if (!hint)  hint = _T("");
			_sntprintf(tBuf, mycountof(tBuf), _T("yuvWrite::write failed, qGetMsg failed. %s"), hint);
			showInfo_open0(0, 0, tBuf);
			return  -1;
		}
		bMsgGot = TRUE;
		//
		BITMAPINFOHEADER* pBih = NULL;
		if (pQdcObjInfo->cfg.v.pf_parseDecVPkt_o(m_var.pPkt1, (void**)&pBih, &m_var.outputInfo.pBuf, &m_var.outputInfo.uiOutputSize)) {
			showInfo_open0(0, 0, _T("parseDecVPkt_o failed"));
			goto  errLabel;
		}
		//
		m_var.outputInfo.bBufTooSmall = FALSE;
		m_var.outputInfo.DataOffset = 0;
		m_var.outputInfo.len = 0;


		//
		if (pQdcObjInfo->var.usPktResType_dec != CONST_pktResType_sharedTex) {

			//
			if (bih_trans.biSizeImage > m_var.outputInfo.uiOutputSize) {
				TCHAR  tBuf[128];
				_sntprintf(tBuf, mycountof(tBuf), _T("YUVWriter.writeNextFrame: trans.sizeImg %d > outputSize %d. skipped"), bih_trans.biSizeImage, m_var.outputInfo.uiOutputSize);
				showInfo_open0(0, 0, tBuf);

				//  
				//sts  =  0;  goto  errLabel;		
				continue;

			}
		}

		//
		memcpy(pBih, &bih_trans, sizeof(pBih[0]));

		//
		break;
	}

	//
	if (pQdcObjInfo->var.usPktResType_dec != CONST_pktResType_sharedTex) {

		//
		if (bih_trans.biSizeImage > m_var.outputInfo.uiOutputSize) {
			TCHAR  tBuf[128];
			_sntprintf(tBuf, mycountof(tBuf), _T("YUVWriter.writeNextFrame: trans.sizeImg %d > outputSize %d. skipped"), bih_trans.biSizeImage, m_var.outputInfo.uiOutputSize);
			showInfo_open0(0, 0, tBuf);

			//  
			sts = 0;  goto  errLabel;

		}

		//
		int  imgW = bih_trans.biWidth;
		int  imgH = bih_trans.biHeight;

		//
		int  yuvLen = imgW * imgH + imgW * (imgH >> 1);

		//
		if (yuvLen > m_var.outputInfo.uiOutputSize) {
			m_var.outputInfo.bBufTooSmall = TRUE;
		}
		else {
			if (pf_img_to_yuv) {
				pf_img_to_yuv(pQdcObjInfo, pImg, cropW, cropH, pitch, imgW, imgH, &m_var);
				m_var.outputInfo.len = yuvLen;
			}
		}

		//
		if (m_var.outputInfo.bBufTooSmall) {
			TCHAR  tBuf[128];
			_sntprintf(tBuf, mycountof(tBuf), _T("yuvWrite::write err, bufTooSmall. bufSize %d, w %d, h %d"), m_var.outputInfo.uiOutputSize, cropW, cropH);
			showInfo_open0(0, 0, tBuf);
			OutputDebugString(_T("qdcSetOutput failed: uiOutputSize too big\n"));
		}

	}



#ifdef  __TEST_save__
	CHECK_NOT_EQUAL(
		fwrite(m_var.outputInfo.pBuf, m_var.outputInfo.len, 1, m_fDest),
		1, MFX_ERR_UNDEFINED_BEHAVIOR);
#endif


	//
	sts = 0;

errLabel:

	//
	pDebugStepDec->nTimeInMs_smplYUVWriter_WriteNextFrame0 = GetTickCount() - dwTickCnt_start;

	return sts;	//  MFX_ERR_NONE;
}



//  2016/04/09
int smplYUVWriter_WriteNextFrame1_1(void* pQdcObjInfoParam, void* pQDC_OBJ_transCommon, void* pYUVWriter_var)
{
	int  sts = -1;
	BOOL  bMsgGot = FALSE;

	QDC_OBJ_transCommon* pTrans = (QDC_OBJ_transCommon*)pQDC_OBJ_transCommon;
	YUVWriter_var1& m_var = *(YUVWriter_var1*)pYUVWriter_var;

	//
	unsigned  int  i, j, h, w;

	//  2011/12/04. 因为只能存放一祯，所以需要清0
	if (!m_var.pQdcObjInfoParam
		|| !m_var.pPkt1)
	{
		showInfo_open0(0, 0, _T("yuvWrite::write failed, pPkt is null. skipped"));
		return  0;
	}
	QDC_OBJ_INFO* pQdcObjInfo = (QDC_OBJ_INFO*)m_var.pQdcObjInfoParam;

	DEBUG_step_dec* pDebugStepDec = (DEBUG_step_dec*)getDebugStep_sth(0, CONST_debugStepType_dec, (MY_DEBUG_STEP*)pQdcObjInfo->var.pDebugStep);
	if (!pDebugStepDec)  return  -1;

	//
	DWORD  dwTickCnt_start = GetTickCount();

	//  2015/01/17
	myDRAW_VIDEO_DATA* pPkt = (myDRAW_VIDEO_DATA*)m_var.pPkt1;
	if (!pPkt->memory.m_pBuf)  return  -1;

	//  2015/09/30
	if (m_var.outputInfo.usPktResType == CONST_pktResType_sharedTex) {
#if  0
		pPkt->usPktResType = CONST_pktResType_sharedTex;
		//
		//pPkt->sharedTex.pktSharedTexInfo  =  m_var.outputInfo.pktSharedTexInfo;
		pPkt->sharedTex.pktSharedTexInfo = m_var.outputInfo.pkts_sharedTexInfo.mems[0];
#endif
		pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(pPkt, _T("smplYUVWriter_WriteNextFrame1_1"));
		myDRAW_VIDEO_DATA  tmpPkt = pPkt[0];
		//memset(&tmpPkt.memory, 0, sizeof(tmpPkt.memory));
		tmpPkt.usPktResType = CONST_pktResType_sharedTex;
		//		
		if (!chkFromPlayerIndex_v(pQdcObjInfo->cfg.v.uiTransformType_pParent, pQdcObjInfo->cfg.v.pParent_transform, (myDRAW_VIDEO_DATA*)&tmpPkt, 0)) {

			//
			if (!m_var.outputInfo.pkts_sharedTexInfo.ucCnt) {
				showInfo_open0(0, _T("smplYUVWriter_1_1"), _T("ERR: pkts_sharedTex.ucCnt is 0"));
			}
			if (m_var.outputInfo.pkts_sharedTexInfo.ucCnt != 1) {
				showInfo_open0(0, _T("smplYUVWriter_1_1"), _T("ERR: pkts_sharedTex.ucCnt is not 1"));
			}

			//
			if (m_var.outputInfo.pkts_sharedTexInfo.ucCnt) {
				QY_TRANSFORM* pTransform = (QY_TRANSFORM*)pQdcObjInfo->cfg.v.pParent_transform;
				//
				PKT_sharedTex_info1* pMem = &m_var.outputInfo.pkts_sharedTexInfo.mems[0];
				
				//
				tmpPkt.head.uiPts = pTransform->lastPkt_pts_v;
				tmpPkt.head.uiSampleTimeInMs = pTransform->lastPkt_uiSampleTimeInMs_v;
				
				//
				pMem->dbg_ui64Id = pTransform->video.idInfo.ui64Id;
				pMem->dbg_pts = pTransform->lastPkt_pts_v;


				//
#ifdef  _DEBUG

				TCHAR  tBuf[128];
				_sntprintf(tBuf, mycountof(tBuf), _T("smplYuvWrite_1_1: %I64u: pkts_sharedTex.ucCnt is %d. pts %d"), pTransform->video.idInfo.ui64Id,  (int)m_var.outputInfo.pkts_sharedTexInfo.ucCnt, pMem->dbg_pts );

				//showInfo_open0(0, 0, tBuf);
#endif

			}

			//
			for (i = 0; i < m_var.outputInfo.pkts_sharedTexInfo.ucCnt; i++) {
				tmpPkt.sharedTex.pktSharedTexInfo = m_var.outputInfo.pkts_sharedTexInfo.mems[i];
				//  
				BOOL  bPktRedirected;
				bPktRedirected = FALSE;
				pQdcObjInfo->cfg.v.dec.pf_postVPktToRender(pQdcObjInfo->cfg.v.pParent_transform, &tmpPkt, &bPktRedirected);
			}
		}
		//
		sts = 0;  goto  errLabel;
	}

	//
#if  10
	//
	if (!chkFromPlayerIndex_v(pQdcObjInfo->cfg.v.uiTransformType_pParent, pQdcObjInfo->cfg.v.pParent_transform, (myDRAW_VIDEO_DATA*)m_var.pPkt1, 0))
	{

		//  
		BOOL  bPktRedirected;
		bPktRedirected = FALSE;
		pQdcObjInfo->cfg.v.dec.pf_postVPktToRender(pQdcObjInfo->cfg.v.pParent_transform, m_var.pPkt1, &bPktRedirected);
		if (bPktRedirected) {
			pQdcObjInfo->cfg.v.pf_detachPkt(m_var.pPkt1, 0);
		}
		else {
			pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(m_var.pPkt1, _T(""));
		}
		bMsgGot = FALSE;

	}
#endif

	sts = 0;
errLabel:

	pDebugStepDec->nTimeInMs_smplYUVWriter_WriteNextFrame1 = GetTickCount() - dwTickCnt_start;
#ifdef  __DEBUG__
#if  0
	TCHAR  tBuf[128];
	GENERIC_Q* pTmpQ = (GENERIC_Q*)pQdcObjInfo->cfg.pTmpDataQ;
	_sntprintf(tBuf, mycountof(tBuf), _T("nTime0_write %dms, nTime1_write %dms"), pDebugStepDec->nTimeInMs_smplYUVWriter_WriteNextFrame0, pDebugStepDec->nTimeInMs_smplYUVWriter_WriteNextFrame1);
	if (pTmpQ) {
		_sntprintf(tBuf, mycountof(tBuf), _T("%s. cnt_tmpQ %d"), tBuf, pTmpQ->uiQNodes);
	}
	showInfo_open0(0, 0, tBuf);
#endif
#endif

	return  sts;
}




///
int smplYUVWriter_WriteNextFrame_all_1(void* pQdcObjInfoParam, void* pQDC_OBJ_transCommon, int  iFourcc, void* pYUVWriter_var, void* pImg, unsigned  int  cropW, unsigned  int  cropH, unsigned  int  pitch, PF_img_to_yuv  pf_img_to_yuv, double  dFrameRate, LPCTSTR  hint)
{
	if (!hint)  hint = _T("");
	//
	if (smplYUVWriter_WriteNextFrame0_1(pQdcObjInfoParam, pQDC_OBJ_transCommon, iFourcc, pYUVWriter_var, pImg, cropW, cropH, pitch, pf_img_to_yuv, dFrameRate, hint))  return  -1;
	if (smplYUVWriter_WriteNextFrame1_1(pQdcObjInfoParam, pQDC_OBJ_transCommon, pYUVWriter_var))  return  -1;
	return  0;
}






