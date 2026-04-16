


#include	"stdafx.h"
#include	<stddef.h>
#include	<time.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"
#include	"tmpCeLib.h"
#include	"qmcVideoCapture.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#include	"qmcCmdProc.h"

#include	"qySqlFunc.h"
#include	"qmcCfg.h"

#include	"sei_packet.h"



//
//
__declspec(  dllexport  )  BOOL  bCapBmpQuit(  void  *  pCAP_procInfo_bmpCommon,  void  *  p1,  void  *  p2  )
{
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  FALSE;
	MC_VAR_common			*	pProcInfo	=	(MC_VAR_common*)pQyMc->get_pProcInfo(  );  //  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;

	CAP_procInfo_bmpCommon  *  pCapProcInfo  =  (  CAP_procInfo_bmpCommon  *  )pCAP_procInfo_bmpCommon;
	if  (  !pCapProcInfo  )  return  FALSE;

	QY_SHARED_OBJ			*	pSharedObj	=	getSharedObjByIndex(  pProcInfo,  pCapProcInfo->iIndex_sharedObj  );
	if  (  !pSharedObj  )  return  FALSE;

	if  (  !bSharedObjActive(  pProcInfo,  pCapProcInfo->iIndex_sharedObj  )  )  {
		return  TRUE;
	}
	return  pCapProcInfo->thread.bQuit;
}


//
__declspec(  dllexport  )  int  capBmpGetSpsPps(  unsigned  int  uiTransformType,  void  *  pCAP_procInfo_bmpCommon,  int  index_pMem_from_unused,  char  *  pBuf,  unsigned  int  *  puiSize  )
{
	int  iErr  =  -1;
	CAP_procInfo_bmpCommon  *  pCapProcInfo  =  (  CAP_procInfo_bmpCommon  *  )pCAP_procInfo_bmpCommon;

	VH_stream  &  vh_stream  =  pCapProcInfo->compressVideo.vh_stream;

	int  total  =  0;
	int  i;
	if  (  vh_stream.usCnt  >  mycountof(  vh_stream.mems  )  )  return  -1;

	for  (  i  =  0;  i  <  vh_stream.usCnt;  i  ++  )  {
		 if  (  total  +  vh_stream.mems[i].usLen  >  *puiSize  )  return  -1;
		 memcpy(  pBuf  +  total,  vh_stream.mems[i].spsPps,  vh_stream.mems[i].usLen  );
		 total  +=  vh_stream.mems[i].usLen;
	}

	*puiSize  =  total;
	return  0;
}


 //
 __declspec(  dllexport  )  int  capBmpGetBih(  void  *  pCAP_procInfo_bmpCommon,  BITMAPINFOHEADER  *  pBih,  void  *  p2  )
 {
	int  iErr  =  -1;
	CAP_procInfo_bmpCommon  *  pCapProcInfo  =  (  CAP_procInfo_bmpCommon  *  )pCAP_procInfo_bmpCommon;

	memcpy(  pBih,  &pCapProcInfo->compressVideo.vh_decompress.bih,  sizeof(  pBih[0]  )  );

	iErr  =  0;
	return  iErr;
 }


 //
 //
 __declspec(  dllexport  )  BOOL  bSharedObjActive(  MC_VAR_common  *  pProcInfo,  int  index  )
{
	QY_SHARED_OBJ	*	pSharedObj	=	getSharedObjByIndex(  pProcInfo,  index  );
	if  (  !pSharedObj  )  return  FALSE;
	
	//
	if  (  pSharedObj->bQuit  )  return  FALSE;

	//
	if  (  pSharedObj->bThreadEnd  )  return  FALSE;

	DWORD	dwExitCode  =  0;

	//
	if  (  GetExitCodeThread(  pSharedObj->hThread,  &dwExitCode  )  &&  dwExitCode  ==  STILL_ACTIVE  )  return  TRUE;

#if  0
	if  (  pSharedObj->hProcess  )  {
		QM_SHM_CMD	*	pShmCmd  =  (  QM_SHM_CMD  *  )pProcInfo->getQmShmCmdByIndex(  pSharedObj->iIndex_shmCmd  );
		if  (  pShmCmd  
			&&  pShmCmd->uiTranNo_sharedObj  ==  pSharedObj->uiTranNo  )  
		{
			if  (  pShmCmd->ucbProcessEnd  )  return  FALSE;
		}

		if  (  GetExitCodeProcess(  pSharedObj->hProcess,  &dwExitCode  )  &&  dwExitCode  ==  STILL_ACTIVE  )  return  TRUE;	//  2009/12/23
	}
#endif


	//
	return  TRUE;
}



//  2015/10/20
 __declspec(dllexport)  int  doPostEnc_mediaSdk_new(void* pQDC_OBJ_INFO, char* pInput, unsigned  int  inputSize, int  iSampleTimeInMs, unsigned  int  uiPts, void* pBuf_pkt_unused)
 {
	 int	iErr = -1;
	 QY_MC* pQyMc = QY_GET_GBUF();
	 if (!pQyMc) {
		 return  -1;
	 }
	 CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();  //  QY_GET_procInfo_isCli(  );
	 if (!pProcInfo) {
		 return  -1;
	 }
	 QMC_cfg* pQmcCfg = (QMC_cfg*)pProcInfo->get_qmc_cfg();
	 if (!pQmcCfg)  return  -1;
	 //
	 QDC_OBJ_INFO* pQdcObjInfo = (QDC_OBJ_INFO*)pQDC_OBJ_INFO;
	 if (!pQdcObjInfo)  return  -1;
	 CAP_procInfo_bmpCommon* pCapProcInfo = (CAP_procInfo_bmpCommon*)pQdcObjInfo->cfg.v.pParent_transform;

	 //
	 CQyMalloc  mallocObj_pkt_withSei;

	 //
	 myDRAW_VIDEO_DATA  tmpPkt; memset(&tmpPkt, 0, sizeof(tmpPkt));
	 void* pBuf_pkt = &tmpPkt;
	 myDRAW_VIDEO_DATA* pPkt = (myDRAW_VIDEO_DATA*)pBuf_pkt;
	 BOOL  bMsgGot = FALSE;



	 QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, pCapProcInfo->iIndex_sharedObj);
	 if (!pSharedObj)  goto  errLabel;

	 //
#if  0
	 showInfo_open(0, 0, 0, _T("doPostEnc enters. l156"));
#endif 

	 //
	 if (pCapProcInfo->iIndex_sharedObj == 0) {
		 pProcInfo->av.localAv.dwLastTickCnt_vCap = myGetTickCount(mynull);
	 }

	 //
	 unsigned  int  size = sizeof(pPkt[0]);
	 if (qGetMsg((GENERIC_Q*)pQdcObjInfo->cfg.v.pTmpDataQ, pPkt, &size)) {
		 showInfo_open0(0, 0, _T("doPostEnc_mediaSdk failed, qGetMsg failed"));
		 goto  errLabel;
	 }
	 bMsgGot = TRUE;

	 //
	 if (!pPkt->memory.m_pBuf) {
		 goto  errLabel;
	 }

	 //  注意：这个初始化非常重要，涉及压缩数据有效性					
	 TRANSFER_VIDEO_DATA* pReq = (TRANSFER_VIDEO_DATA*)(pPkt->memory.m_pBuf + pPkt->uiSize_dec);
	 memset(pReq, 0, offsetof(TRANSFER_VIDEO_DATA, buf));


	 //	
	 SHARED_OBJ_USR* pSharedObjUsr = getSharedObjUsr(pSharedObj, pSharedObj->iIndex_curUsr);
	 if (!pSharedObjUsr) {
#ifdef  __DEBUG__
		 traceLog(_T("mcThread_toShareBmp: pSharedObjUsr is null"));
#endif
		 goto  errLabel;
	 }


	 BOOL  bInited_pReq = FALSE;
	 int  myuiSampleTimeInMs = 0;
	 unsigned  int  myuiPts = 0;	//  2015/01/15
	 //int  usIndex_activeMems_from  =  0;


	 //
	 int  iFourcc = fourccStr2i(pCapProcInfo->compressVideo.compressor.common.fourccStr);

	 //
	 char  buf[128];
	 iFourcc2Str(iFourcc, buf, mycountof(buf));

	 //
	 char  sei[128];
	 char  content[24] = "hello";
	 int  seiLen;
	 //
	 content[0] = pProcInfo->av.confLayout.taskInfo.ucMbFlg;
	 content[1] = 0;
	 //
	 if (iFourcc == CONST_fourcc_h264) {
		 int nalType = M_nalType_h264(pInput);
		 if (nalType == 5) {
			 int  ii = 0;
			 seiLen = sizeof(sei);
			 fill_sei_packet_h264((unsigned  char*)sei, &seiLen, true, content, strlen(content));
			 //
			 int  tmpLen = inputSize + seiLen;
			 char* tmp_pInput = mallocObj_pkt_withSei.mallocf(tmpLen);
			 if (!tmp_pInput)  goto  errLabel;
			 memcpy(tmp_pInput, sei, seiLen);
			 memcpy(tmp_pInput + seiLen, pInput, inputSize);
			 pInput = tmp_pInput;
			 inputSize = tmpLen;
			 //
			 ii = 1;
			 ii++;
		 }
	 }
	 else  if (iFourcc == CONST_fourcc_HEVC) {
		 int  nalType = M_nalType_h265(pInput);
		 switch (nalType) {
		 case  19:
		 case  20:
			 if (10)
			 {
				 //
#ifdef  __DEBUG__
					  //char  tttBuf[128];
					  //memcpy(tttBuf, pInput, min(inputSize, mycountof(tttBuf)));
#endif
					  //
#if 10
					  //
				 seiLen = sizeof(sei);
				 fill_sei_packet_h265((unsigned  char*)sei, &seiLen, true, content, strlen(content));

				 //
				 int  tmp_nalType = M_nalType_h265(sei);
				 //
				 int  tmpLen = inputSize + seiLen;
				 char* tmp_pInput = mallocObj_pkt_withSei.mallocf(tmpLen);
				 if (!tmp_pInput)  goto  errLabel;
				 //
				 memcpy(tmp_pInput, pInput, inputSize);
				 memcpy(tmp_pInput + inputSize, sei, seiLen);
				 //
				 pInput = tmp_pInput;
				 inputSize = tmpLen;
#endif
			 }
			 //
			 break;
		 default:
			 break;

		 }
		 //
		 unsigned  char  ucbKeyFrame = false;
		 //
		 switch (nalType) {
				 case  NAL_IDR_W_RADL:
				 case  NAL_IDR_N_LP:
					 ucbKeyFrame = true;
					 break;
				 case  NAL_VPS: {
					 ucbKeyFrame = true;
					 //
					 if (0) {
						 char  sps[128];
						 char  pps[128];
						 char  vps[128];
						 unsigned  int  spsLen = sizeof(sps);
						 unsigned  int  ppsLen = sizeof(pps);
						 unsigned  int vpsLen = sizeof(vps);
						 if (!parseSpsPps(iFourcc, pInput, inputSize, sps, &spsLen, pps, &ppsLen, vps, &vpsLen)) {
							 int  ii = 0;
						 }
						 //
					 }
					 //
					 }
					 //
							  break;
				 default:		
					 break;					 
		 }

		 //
		 if (ucbKeyFrame) {
			 showInfo_open(0, 0, 0, _T("doPostEnc. 265, keyFrame"));
		 }

	 }




	 //
	 if (pCapProcInfo->uiSubtype == CONST_subCapType_mosaic_video
		 || pCapProcInfo->uiSubtype == CONST_subCapType_mosaic_resource)
	 {
		 int  ii = 0;
		 Param_saveAv param = { 0 };
		 param.pSaveAvPktU = &pCapProcInfo->capBmpSaveAv.tmpBuf_saveAvPkt;

		 //
		 int  index_saver = 0;
		 switch (pCapProcInfo->uiSubtype) {
		 case  CONST_subCapType_mosaic_video:
			 index_saver = 0;
			 break;
		 case  CONST_subCapType_mosaic_resource:
			 index_saver = 1;
			 break;
		 default:
			 break;
		 }
		 param.pSave = getSaver(index_saver);
		 if (!param.pSave)  goto  errLabel;

		 //
		 if (!pCapProcInfo->capBmpSaveAv.bPost_spspps) {
			 char  buf[1024];
			 unsigned  int  bufLen = mycountof(buf);
			 makeSpsPps(&pCapProcInfo->compressVideo.vh_stream, buf, &bufLen);
			 //
			 postVPktToSave(&param, false, 0, 0, 0, iFourcc, 0, 0, buf, bufLen);
			 //
			 pCapProcInfo->capBmpSaveAv.bPost_spspps = true;
		 }
		 //
		 postVPktToSave(&param, false, 0, 0, 0, iFourcc, iSampleTimeInMs, uiPts, pInput, inputSize);
	 }




	 //
	 if (!bInited_pReq) {
		 if (pReq) {
			 //  memset(  pReq,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );
			 pReq->uiType = CONST_imCommType_transferVideoData;
			 //  pReq->uiTranNo_openAvDev  =  pCompressVideo->uiTranNo_openAvDev;
			 pReq->uiTranNo_openAvDev = pSharedObjUsr->uiTranNo_openAvDev_v;			//  2010/09/04
			 //
		 }
		 //
		 bInited_pReq = TRUE;
	 }

	 if (sizeof(pReq->buf) <= pReq->uiLen) {
		 traceLogA("toShareBmp failed: sizeof(  pReq->buf  ) %d  <=  pReq->len %d", sizeof(pReq->buf), pReq->uiLen);
		 goto  errLabel;
	 }

	 //  int  tmpiRet  =  pModule->compress.pf_qdcGetOutputByIndex(  &pCompressVideo->u.custom,  index_output,  (  BYTE  *  )pReq->buf  +  pReq->uiLen,  &pReq->mems[pReq->usCnt].uiLen,  NULL,  NULL  );
	 if (sizeof(pReq->buf) - pReq->uiLen < inputSize) {
		 showInfo_open0(0, 0, _T("doPostEnc_mediaSdk failed, buf too small"));
		 goto  errLabel;
	 }
	 memcpy(pReq->buf + pReq->uiLen, pInput, inputSize);
	 pReq->mems[pReq->usCnt].uiLen = inputSize;

#ifdef  __DEBUG__
	 if (pQmcCfg->debugStatusInfo.ucb__Dump_h265_enc__) {
		 //if ( pCapProcInfo->iIndex_sharedObj==0)

		 char* pBuffer = pReq->buf + pReq->uiLen;
		 int  BufferLen = pReq->mems[pReq->usCnt].uiLen;

		 if (iFourcc == CONST_fourcc_AV01) {
			 //
			 {
				 //
				 int obu_type = 0;
				 int extension_flag = 0;
				 int has_size_field = 0;
				 unsigned  __int64 payload_size = 0;

#if  0
				 parse_obu_header((const unsigned  char*)pBuffer, BufferLen,
					 &obu_type,
					 &extension_flag,
					 &has_size_field,
					 &payload_size);

				 //
				 traceLog(_T("obuType %d"), obu_type);
#endif 

			 }
			 //
			 dumpVideo(0, 0, pBuffer, BufferLen, &pCapProcInfo->compressVideo.dumpVideoObj);
		 }
		 else
		 {
			 FILE* fp = NULL;
			 char* fn = CONST_fn_dump_h265_enc;
			 fp = fopen(fn, "ab+");
			 if (fp) {
				 //
				 fwrite(pBuffer, BufferLen, 1, fp);
				 fclose(fp);
			 }
			 static  int  uiCnt_fn = 0;
			 uiCnt_fn++;
			 if (uiCnt_fn == 2000) {
				 int  i;
				 i = 1;
			 }
		 }
	 }
	 //
#endif


//  2014/04/22
#if  1						
	   //int  nIntervalInMs  =  40;
#if  0
	 if (pCapProcInfo->compressVideo.compressor.common.usMaxFps_toShareBmp) {
		 nIntervalInMs = 1000 / pCapProcInfo->compressVideo.compressor.common.usMaxFps_toShareBmp;
	 }
#endif
#if  0
	 unsigned  short  usFps = min(pCapProcInfo->compressVideo.input1.videoInputInfo.usFps, pCapProcInfo->compressVideo.compressor.common.usMaxFps_toShareBmp);
	 if (!usFps || abs(usFps - pCapProcInfo->compressVideo.compressor.common.usMaxFps_toShareBmp) < 3) {
		 usFps = pCapProcInfo->compressVideo.compressor.common.usMaxFps_toShareBmp;
	 }
	 if (usFps) {
		 nIntervalInMs = 1000 / usFps;
	 }
#endif
	 //
#if  0
	 int  iNextIndex_preEnc = pCapProcInfo->compressVideo.encInfo.iNextIndex_preEnc;
	 int  iLastIndex_preEnc = 0;
	 if (!iNextIndex_preEnc)  iLastIndex_preEnc = mycountof(pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array) - 1;
	 else  iLastIndex_preEnc = iNextIndex_preEnc - 1;
	 //
	 if (pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc >= mycountof(pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array)) {
		 qyShowInfo1(CONST_qyShowType_qwmComm, 0, "", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("doPostEnc failed: iIndex_postEnc too big"));
		 goto  errLabel;
	 }
	 //
	 int  iDiff_index = mycountof(pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array) + iNextIndex_preEnc - pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc;
	 iDiff_index = iDiff_index % mycountof(pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array);
	 int  max_iDiff_index = 10;
	 if (iDiff_index > max_iDiff_index) {
		 pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc = mycountof(pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array) + iNextIndex_preEnc - 6;
		 pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc = pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc % mycountof(pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array);
		 //
		 qyShowInfo1(CONST_qyShowType_qwmComm, 0, "", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("doPostEnc: iDiff_index %d, adjusted: ind_preEnc %d, ind_postEnc %d"), iDiff_index, iNextIndex_preEnc, pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc);
	 }
	 //
	 iSampleTimeInMs = pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array[pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc];
#endif
	 //  2024/11/02
	 {
		 int arraySize = mycountof(pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array);
		 int  iNextIndex_postEnc = pCapProcInfo->compressVideo.encInfo.cnt_postEnc % arraySize;
		 iSampleTimeInMs = pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array[iNextIndex_postEnc];

		 //
		 int  iDiff_index = pCapProcInfo->compressVideo.encInfo.cnt_preEnc - pCapProcInfo->compressVideo.encInfo.cnt_postEnc;
		 int  max_iDiff_index = 10;
		 TCHAR  tBuf[128] = _T("");

		 if (iDiff_index  <  0 || iDiff_index  >  max_iDiff_index)
		 {
			 _sntprintf(tBuf, mycountof(tBuf), _T("doPostEnc: sharedObj %d:  iDiff_index %d, err: cnt_pre %d, cnt_post %d "), pCapProcInfo->iIndex_sharedObj, iDiff_index, pCapProcInfo->compressVideo.encInfo.cnt_preEnc, pCapProcInfo->compressVideo.encInfo.cnt_postEnc);
			 showInfo_open0(0, 0, tBuf);
		 }
		 if (0) {
			 int  iDiffInMs = iSampleTimeInMs - pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_postEnc;
			 _sntprintf(tBuf, mycountof(tBuf), _T("doPostEnc: sharedObj %d, iDiffInMs %dms. cnt_postEnc %d"), pCapProcInfo->iIndex_sharedObj, iDiffInMs, pCapProcInfo->compressVideo.encInfo.cnt_postEnc);
			 showInfo_open0(0, 0, tBuf);
		 }


	 }



	 //
	 if (!pCapProcInfo->compressVideo.ucbUseEvt) {
		 //  2015/01/15
		 BOOL  bNeedPts = TRUE;
		 //
#if  0  //  2015/09/10. vp8也用pts
		 if (pCapProcInfo->compressVideo.compressor.common.ucCompressors == CONST_videoCompressors_vp8)  bNeedPts = FALSE;
#endif

		 //
		 if (bNeedPts) {
			 //
			 if (uiPts) {
				 myuiPts = uiPts;
			 }
			 else {
				 myuiPts = pCapProcInfo->compressVideo.encInfo.cnt_postEnc;
			 }
		 }
	 }
	 else {  //  2015/10/20
		 myuiPts = uiPts;
	 }


	 //
	 pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_postEnc = iSampleTimeInMs;

	 //
#if  0
	 pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc++;
	 if (pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc >= mycountof(pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array)) {
		 pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc = pCapProcInfo->compressVideo.encInfo.iNextIndex_postEnc % mycountof(pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_preEnc_array);
	 }
#endif

	 //
	 pCapProcInfo->compressVideo.encInfo.cnt_postEnc++;
#endif

	 //  2008/11/12, 
	 if (iSampleTimeInMs) {
		 //  
		 pReq->mems[pReq->usCnt].uiSampleTimeInMs = myuiSampleTimeInMs = iSampleTimeInMs;// -pSharedObj->iDiffInMs_tStartAudio;	//  2009/05/26

		 //
		 int  iDiffInMs = iSampleTimeInMs - pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_startToCalcElapseInMs_fromLastPkt;
		 if (abs(iDiffInMs) > 3000) {
			 pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_startToCalcElapseInMs_fromLastPkt = iSampleTimeInMs;
			 pReq->mems[pReq->usCnt].usElapseInMs_fromLastPkt = 0;
		 }
		 else {
			 pReq->mems[pReq->usCnt].usElapseInMs_fromLastPkt = iSampleTimeInMs - pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_lastPkt;
		 }
		 //
		 pCapProcInfo->compressVideo.encInfo.iSampleTimeInMs_lastPkt = iSampleTimeInMs;

		 //
#ifdef  __DEBUG__
		 if (1) {
		 }
#endif 

	 }

	 //  2015/01/15
	 pReq->mems[pReq->usCnt].uiPts = myuiPts;
	 
	 //
#if  0
	 if (pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id) {
		 //pReq->mems[pReq->usCnt].usIndex_ii  =  
		 usIndex_activeMems_from = pSharedObjUsr->iIndex_activeMems_from_videoConferenceStarter;
	 }
#endif

	 //
	 pReq->uiLen += pReq->mems[pReq->usCnt].uiLen;
	 pReq->usCnt++;


	 //
	 DWORD  dwTickCnt;
#if  1
	 dwTickCnt = GetTickCount();
	 pPkt->debugInfo.usEncedInMs = dwTickCnt - pPkt->debugInfo.dwTickCnt_start;
	 //  2012/01/06
	 unsigned  char  ucbFpsUnmatched = FALSE;
	 if (pCapProcInfo->compressVideo.usFrames_perSecond_expected >= pCapProcInfo->compressVideo.input_BufferCB.videoInputInfo.usFps + 5) {		//  如果设置29.但是输入是24,那么也需要警告提示,所以是 >=
		 ucbFpsUnmatched = TRUE;
	 }
	 if (pSharedObj->status.ucbFpsUnmatched != ucbFpsUnmatched)  pSharedObj->status.ucbFpsUnmatched = ucbFpsUnmatched;
#endif

	 //
	 BOOL		bPktRedirected = FALSE;
	 if (!q2PostMsgAndTrigger(pPkt, 1 * sizeof(pPkt[0]), &pCapProcInfo->postThread.q2, _T("doPostEnc_mediaSdk"))) {
		 bPktRedirected = TRUE;
	 }
	 if (bPktRedirected) {
		 detachVPkt(pPkt, 0);
	 }
	 else {
		 clean_myDRAW_VIDEO_DATA(pPkt, _T(""));
	 }
	 bMsgGot = FALSE;


	 iErr = 0;
 errLabel:

	 if (bMsgGot) {
		 pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(pPkt, _T(""));
	 }

	 //
#if  0
	 if (iErr) {
		 //
		 showInfo_open(0, 0, 0, _T("doPostEnc leaves failed. l554"));
	 }
	 else {
		 showInfo_open(0, 0, 0, _T("doPostEnc leaves ok. l557"));
	 }
#endif 


	 //
	 return  iErr;
 }


