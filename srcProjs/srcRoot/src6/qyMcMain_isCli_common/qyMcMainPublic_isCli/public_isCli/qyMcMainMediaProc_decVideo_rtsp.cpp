
#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>

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
#include	"testOnly.h"
#include	"qmcCfg.h"
#include	"qmcTaskInfo.h"


//
int  doDecVideoPkt(  QY_TRANSFORM  *  pTransform,  myDRAW_VIDEO_DATA  *  pPkt,  MIS_MSGU  *  pMsgBuf  );
#ifdef  __DEBUG__
extern  "C"  int  __declspec(  dllexport  )  qdcDecompressVideoRun(  QDC_OBJ_INFO  *  pQdcObjInfo  );
#endif


//  2015/02/14
BOOL  bTransformAudioQuit(  void  *  pQY_TRANSFORM,  void  *  p1,  void  *  p2  )
{
	QY_TRANSFORM  *  pTransform  =  (  QY_TRANSFORM  *  )pQY_TRANSFORM;

#ifdef  __DEBUG__
	if  (  pTransform->audio.bQuit  )  {
		int  i;
		i  =  1;
	}
#endif

	return  pTransform->audio.bQuit;
}



//
BOOL  bTransformVideoQuit(  void  *  pQY_TRANSFORM,  void  *  p1,  void  *  p2  )
{
	QY_TRANSFORM  *  pTransform  =  (  QY_TRANSFORM  *  )pQY_TRANSFORM;

#ifdef  __DEBUG__
	if  (  pTransform->video.bQuit  )  {
		int  i;
		i  =  1;
	}
#endif

	return  pTransform->video.bQuit;
}

// int  transformGetSpsPps(  void  *  pQY_TRANSFORM,  char  *  pBuf,  unsigned  int  *  puiSize  )
int  transformGetSpsPps(unsigned  int  uiTransformType, void* pQY_TRANSFORM, int  index_pMems_from, char* pBuf, unsigned  int* puiSize)
{
	int  iErr = -1;
	QY_TRANSFORM* pTransform = (QY_TRANSFORM*)pQY_TRANSFORM;
	TRANSFORM_VIDEO_procInfo* pTransformVideo = &pTransform->video;

	int  total = 0;
	int  i;

	//
	if (pTransformVideo->tv.vh_stream.usCnt > mycountof(pTransformVideo->tv.vh_stream.mems))  return  -1;
	//
	for (i = 0; i < pTransformVideo->tv.vh_stream.usCnt; i++) {
		if (total + pTransformVideo->tv.vh_stream.mems[i].usLen > *puiSize)  return  -1;
		memcpy(pBuf + total, pTransformVideo->tv.vh_stream.mems[i].spsPps, pTransformVideo->tv.vh_stream.mems[i].usLen);
		total += pTransformVideo->tv.vh_stream.mems[i].usLen;

		//  2014/08/31
		if (pTransform->pTask) {
			PROC_TASK_AV* pTask = (PROC_TASK_AV*)pTransform->pTask;
			//
			if (pTask->saveVideo.ucbSaveVideo_req
				|| pTransform->bInited_saver)
			{
				//
				char* video = pTransform->video.tv.vh_stream.mems[i].spsPps;
				int  len = pTransform->video.tv.vh_stream.mems[i].usLen;
				//postVPktToSave(  CONST_uiTransformType_dec,  pTransform,  index_pMems_from,  0,  0,  video,  len  );  										   
				//postVPktToSave()
			}
		}
	}
	if (pTransform->bInited_saver) {
		Param_saveAv param = { 0 };
		param.pSaveAvPktU = &pTransform->video.transSaveAv.tmpBuf_saveAvPkt;
		//
		param.pSave = pTransform->pSaver;
		//
		int  iFourcc = pTransform->video.tv.vh_stream.dwFourcc;
		//
		char  buf[1024];
		unsigned  int  bufLen = mycountof(buf);
		makeSpsPps(&pTransform->video.tv.vh_stream, buf, &bufLen);
		//
		int  index_activeMems_from = pTransform->index_activeMems_from;
		__int64  idInfo_from = pTransform->video.idInfo.ui64Id;
		int tn = pTransform->video.tv.uiTranNo_openAvDev;
		//
		postVPktToSave(& param, false, index_activeMems_from, idInfo_from, tn, iFourcc, 0, 0, buf, bufLen);
		//

	}

	//
	TCHAR  tBuf[128] = _T("");
	_sntprintf(tBuf, mycountof(tBuf), _T("transformGetSpsPps: %I64u, cnt %d"), pTransform->video.idInfo.ui64Id, (int)pTransformVideo->tv.vh_stream.usCnt);
	for (i = 0; i < pTransformVideo->tv.vh_stream.usCnt; i++) {
		_sntprintf(tBuf, mycountof(tBuf), _T("%s,%d"), tBuf, (int)pTransformVideo->tv.vh_stream.mems[i].usLen);
	}
	showInfo_open0(0, 0, tBuf);

	//
	*puiSize = total;
	return  0;
}



 //
 int  transformGetBih(  void  *  pQY_TRANSFORM,  BITMAPINFOHEADER  *  pBih,  void  *  p2  )
 {
	int  iErr  =  -1;
	QY_TRANSFORM  *  pTransform  =  (  QY_TRANSFORM  *  )pQY_TRANSFORM;
	TRANSFORM_VIDEO_procInfo  *  pTransformVideo  =  &pTransform->video;

	memcpy(  pBih,  &pTransformVideo->tv.vh_decompress.bih,  sizeof(  pBih[0]  )  );

	iErr  =  0;
	return  iErr;
 }



 

 


 // 
  int  dec_parseEncAPkt_i_useAudioQ2(  unsigned  int  uiTransformType,  void  *  pParent_transform,  PKT_info_toDec  *  pPktInfo_toDec_param,  long  *  p_old_lPktId_getNewPkt,  unsigned  char  **  ppInput,  unsigned  int  *puiSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  puiPts  )
{
	int		iErr	=	-1;
	MC_VAR_common  *  pProcInfo  =  NULL;	//  QY_GET_procInfo_isCli(  );
	TCHAR	tBuf[256]  =  _T(  ""  );


	//  myDRAW_VIDEO_DATA  *  pPkt  =  pTransform->video.pCurPkt;
	PKT_info_toDec  *  pPktInfo_toDec  =  (  PKT_info_toDec  *  )pPktInfo_toDec_param;
			
	//  检查一下。每个包都只能处理一次，否则，容易死循环
	if  (  !p_old_lPktId_getNewPkt  )  return  -1;
	if  (  !pPktInfo_toDec->lPktId_getNewPkt  )  {
		showInfo_open0(  0,  0,  _T(  "failed: lPktId_alloc 0"  )  );
		return  -1;
	}
	if  (  pPktInfo_toDec->lPktId_getNewPkt  ==  *p_old_lPktId_getNewPkt  )  {
		showInfo_open0(  0,  0,  _T(  "failed: lPkdId_alloc==old"  )  );
		return  -1;			  
	}
	*p_old_lPktId_getNewPkt  =  pPktInfo_toDec->lPktId_getNewPkt;
	
	//
	if  (  uiTransformType  !=  CONST_uiTransformType_dec  )  {
		MACRO_qyAssert(  0,  _T(  "dec_parseEncVPkt failed, transformType err"  )  );
		return  -1;
	}
	QY_TRANSFORM  *  pTransform  =  (  QY_TRANSFORM  *  )pParent_transform;
	pProcInfo  =  (  MC_VAR_common  *  )pTransform->pProcInfo;
	if  (  !pProcInfo  )  return  -1;

	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;

	//
	if  (  !pPktInfo_toDec->bGot_msg  )  return  -1;
	if  (  !pPktInfo_toDec->info.bGot_pkt  )  return  -1;

	
			
			//  2015/09/11
			MIS_MSGU  *  pMsg  =  (  MIS_MSGU  *  )pPktInfo_toDec->pMIS_MSGU;
			if  (  pMsg->uiType  !=  CONST_misMsgType_task  )  goto  errLabel;
			IM_CONTENTU* pContent; pContent = (IM_CONTENTU*)pMsg->task.data.buf;
			if  (  pContent->uiType  !=  CONST_imCommType_transferAudioData  )  goto  errLabel;

			//
			TRANSFER_AUDIO_DATA* pReq; pReq = &pContent->transferAudioData;
			TRANSFER_AUDIO_dataMemHead  *  pMem;
			int  i;
			int  iPos;

			//
			iPos  =  pPktInfo_toDec->info.iPos;
			if  (  pPktInfo_toDec->info.index_mems  <0  ||  pPktInfo_toDec->info.index_mems  >=  pReq->usCnt  )  goto  errLabel;
			i  =  pPktInfo_toDec->info.index_mems;

			
			//				
			pMem  =  &pReq->mems[i];
				 
				 if  (  iPos  +  pReq->mems[i].uiLen  >  pReq->uiLen  )  {
					 #ifdef  __DEBUG__
							 traceLogA(  (char*)  "procTasAudio: "  );			 
					 #endif
					 goto  errLabel;		 
				 }		 
				 if  (  !pMem->uiLen  )  {
					 #ifdef  __DEBUG__
							 traceLogA(  (char*)  "procTaskAudio warning: mem.uiLen is 0"  );
					 #endif
					 goto  errLabel; 
				 }
				 if  (  1  )  {
					 if  (  pMem->uiPts  )  {
						if  (  !pTransform->audio.decInfo.pts.uiPts_lastRecvd  )  {
							pTransform->audio.decInfo.pts.uiPts_first  =  pMem->uiPts;
							pTransform->audio.decInfo.pts.dwTickCnt_start  =  GetTickCount(  );
							}
						else  {
							  if  (  pMem->uiPts  !=  pTransform->audio.decInfo.pts.uiPts_lastRecvd  +  1  )  {			
								  //
								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "dec_parseEncAPkt_i failed: pts err. pkt.pts %d, last %d"  ),  pMem->uiPts,  pTransform->audio.decInfo.pts.uiPts_lastRecvd  );
								  showInfo_open0(  0,  0,  tBuf  );
								  //  2015/02/20
								  goto  errLabel;						
							  }						  
							  //
						}					
						//pTransform->video.decInfo.pts.uiPts_lastRecvd  =  pPkt->head.uiPts;		
					}
				 }				
				//  2015/06/18
				if  (  pMem->uiPts  )  {
					pTransform->audio.decInfo.pts.uiPts_lastRecvd  =  pMem->uiPts;		
				}
				//
				QMC_debugStatusInfo* pDbgStatusInfo; pDbgStatusInfo = pProcInfo->get_qmc_debugStatusInfo();
				if  (  pDbgStatusInfo  )  {
					if  (  pDbgStatusInfo->ucbShowPreDecAStatus  )  {
						TCHAR  tBufff[129];
						_sntprintf(  tBufff,  mycountof(  tBufff  ),  _T(  "dec_parseEncAPkt_i: %I64u, mems[%d], pts %d"  ),  pMem->idInfo.ui64Id,  i,  pMem->uiPts  );
						showInfo_open0(  0,  0,  tBufff  );
					}
				}
			
				//
				char* encData; encData = pReq->buf + iPos;


		 //
		 *ppInput  =  (  unsigned  char  *  )encData;
		 *puiSize  =  pMem->uiLen;
		 //  2015/01/28
		 if  (  puiSampleTimeInMs  )  {
			 *puiSampleTimeInMs  =  pMem->uiSampleTimeInMs;
		 }
		 //  2015/02/09
		 if  (  puiPts  )  {
			 *puiPts  =  pMem->uiPts;
		 }

		 //  2016/12/15
		 pTransform->audio.decInfo.st.last_iSampleTimeInMs_preDec  =  pMem->uiSampleTimeInMs;


		 iErr  =  0;
errLabel:

	return  iErr;
}


 

 int dec_parseEncAPkt_i(uint uiTransformType, void *  pParent_transform, PKT_info_toDec  * pPktInfo_toDec_param, long* p_old_lPktId_getNewPkt, byte** ppInput, uint* puiSize, uint* puiSampleTimeInMs, uint* puiPts)
{
	int iErr = -1;
	CCtxQyMc * pQyMc = QY_GET_GBUF();
	CCtxQmc *pProcInfo = (CCtxQmc *  )pQyMc->get_pProcInfo();    //  QY_GET_procInfo_isCli(  );
												  TCHAR tBuf[256] = _T("");


	//  myDRAW_VIDEO_DATA  *  pPkt  =  pTransform.video.pCurPkt;
	PKT_info_toDec* pPktInfo_toDec = pPktInfo_toDec_param;
	{
		;

		//  检查一下。每个包都只能处理一次，否则，容易死循环
		if (mynull == p_old_lPktId_getNewPkt) return -1;
		if (0 == pPktInfo_toDec->lPktId_getNewPkt)
		{
			showInfo_open0(0, mynull, _T("failed: lPktId_alloc 0"));
			return -1;
		}
		if (pPktInfo_toDec->lPktId_getNewPkt == *p_old_lPktId_getNewPkt)
		{
			showInfo_open0(0, mynull, _T("failed: lPkdId_alloc==old"));
			return -1;
		}
		*p_old_lPktId_getNewPkt = pPktInfo_toDec->lPktId_getNewPkt;

		//
		if (uiTransformType != CONST_uiTransformType_dec)
		{
			//MACRO_qyAssert(0, _T("dec_parseEncVPkt failed, transformType err"));
			return -1;
		}
		QY_TRANSFORM *pTransform = (QY_TRANSFORM*)pParent_transform;
		//pProcInfo = (MC_VAR_common*)pTransform.pProcInfo;
		if (mynull == pProcInfo) return -1;

		QMC_cfg *pQmcCfg = &pProcInfo->cfg;
		//if (!pQmcCfg) return -1;

		//
		if (!pPktInfo_toDec->bGot_msg) return -1;
		if (!pPktInfo_toDec->info.bGot_pkt) return -1;


		TRANSFER_AUDIO_dataMemHead* pMem;

#if 0//false
		//  2015/09/11
		MIS_MSGU* pMsg = (MIS_MSGU*)pPktInfo_toDec->pMIS_MSGU;
		if (pMsg->uiType != Consts.CONST_misMsgType_input)
		{
			traceLog("dec_parseEncAPkt_i failed, only input msg accepted");
			goto errLabel;
		}
		IM_CONTENTU* pContent = (IM_CONTENTU*)pMsg->input.data.buf;
		if (pContent->uiType != Consts.CONST_imCommType_transferAudioData) goto errLabel;

		//
		TRANSFER_AUDIO_DATA* pReq = &pContent->transferAudioData;
		int i;
		int iPos;

		//
		iPos = pPktInfo_toDec->info.iPos;
		if (pPktInfo_toDec->info.index_mems < 0 || pPktInfo_toDec->info.index_mems >= pReq->usCnt) goto errLabel;
		i = pPktInfo_toDec->info.index_mems;

		TRANSFER_AUDIO_dataMemHead* pReq_mems = (TRANSFER_AUDIO_dataMemHead*)pReq->buf_TRANSFER_AUDIO_dataMemHead_mems;
		int bufSize = Consts.bufSize_TRANSFER_AUDIO_dataMemHead_mems;
		//				
		pMem = getMem(pReq_mems, bufSize, i);// &pReq_mems[i];

		if (iPos + pMem->uiLen > pReq->uiLen)
		{
#if __DEBUG__
			traceLogA("procTasAudio: ");
#endif
			goto errLabel;
		}
#endif
		pMem = &pPktInfo_toDec->pkt_encA.memHead_a;
		if (0 == pMem->uiLen)
		{
#ifdef  __DEBUG__
			traceLogA((char*)"procTaskAudio warning: mem.uiLen is 0");
#endif
			goto errLabel;
		}





		//
		if (true)
		{
			if (0 != pMem->uiPts)
			{
				if (0 == pTransform->audio.decInfo.pts.uiPts_lastRecvd)
				{
					pTransform->audio.decInfo.pts.uiPts_first = pMem->uiPts;
					pTransform->audio.decInfo.pts.dwTickCnt_start = myGetTickCount(mynull);
				}
				else
				{
					if (pMem->uiPts != pTransform->audio.decInfo.pts.uiPts_lastRecvd + 1)
					{
						//
						int nErr = pMem->uiPts - (  pTransform->audio.decInfo.pts.uiPts_lastRecvd + 1  );
						pProcInfo->status.pktsStat.ui64_a_pkts_err+=abs(nErr);

						//string str;
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "dec_parseEncAPkt_i: {%d}: pts err, pkt {%d}, last {%d}"  ), pMem->idInfo.ui64Id, pMem->uiPts, pTransform->audio.decInfo.pts.uiPts_lastRecvd);
						showInfo_open0(0, mynull, tBuf);
						//  2015/02/20
						goto errLabel;
					}
					//
				}
				//pTransform.video.decInfo.pts.uiPts_lastRecvd  =  pPkt->head.uiPts;		
			}
			//
			pProcInfo->status.pktsStat.ui64_a_pkts_ok++;
		}
		//  2015/06/18
		if (0 != pMem->uiPts)
		{
			pTransform->audio.decInfo.pts.uiPts_lastRecvd = pMem->uiPts;
		}
		//
		QMC_debugStatusInfo* pDbgStatusInfo = &pProcInfo->cfg.debugStatusInfo;
		//if (pDbgStatusInfo)
		{
			if (pDbgStatusInfo->ucbShowPreDecAStatus)
			{
				/*
				TCHAR tBufff[129];
				_sntprintf(tBufff, mycountof(tBufff), _T("dec_parseEncAPkt_i: %I64u, mems[%d], pts %d"), pMem->idInfo.ui64Id, i, pMem->uiPts);
				showInfo_open0(0, 0, tBufff);
				*/
			}
		}

		//
		byte* encData = mynull;// pReq->buf + iPos;
		encData = (byte*)pPktInfo_toDec->pkt_encA.buf;
		if (pPktInfo_toDec->pkt_encA.len != pMem->uiLen)
		{
			int ii = 0;
		}


		//
		*ppInput = (byte*)encData;
		*puiSize = pMem->uiLen;
		//  2015/01/28
		if (mynull != puiSampleTimeInMs)
		{
			*puiSampleTimeInMs = pMem->uiSampleTimeInMs;
		}
		//  2015/02/09
		if (mynull != puiPts)
		{
			*puiPts = pMem->uiPts;
		}

		//  2016/12/15
		pTransform->audio.decInfo.st.last_iSampleTimeInMs_preDec = (int)pMem->uiSampleTimeInMs;

	}

	iErr = 0;
errLabel:

	return iErr;
}

 




//
int  updateDecVideoParam(  BITMAPINFOHEADER  *  pBih,  double  dFrameRate,  void  *  pParent_transform,  unsigned  int  uiTransformType  )
{
	int  iErr  =  -1;

	if  (  !pBih  )  return  -1;
	if  (  !pParent_transform  )  return  -1;
	if  (  uiTransformType  !=  CONST_uiTransformType_dec  )  return  -1;

	BITMAPINFOHEADER  &  bih_enc  =  *pBih;
	QY_TRANSFORM  *  pTransform  =  (  QY_TRANSFORM  *  )pParent_transform;
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pTransform->pProcInfo;	//  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;

	//
	BOOL			bNotMatched  =  FALSE;
	BOOL			bModified	=	FALSE;		//  2014/08/05

	
	if  (  bih_enc.biWidth  &&  bih_enc.biHeight  )  {
		
		CQySyncObj	syncObj;		
		TCHAR		mutexName[128];
		
		//  2011/07/03
		M_getMutexName_syncActiveMem(  pQmcCfg,  pTransform->iTaskId,  mutexName,  mycountof(  mutexName  )  );
		if  (  syncObj.sync(  mutexName,  1000  )  )  goto  errLabel;

		//
		if  (  pTransform->video.tv.vh_compress.bih.biWidth  &&  pTransform->video.tv.vh_compress.bih.biHeight  )  {			
			if  (  pTransform->video.tv.vh_compress.bih.biWidth  !=  bih_enc.biWidth  )  {
				bNotMatched  =  true;
				//  goto  errLabel;												   
			}								
			if  (  pTransform->video.tv.vh_compress.bih.biHeight  !=  bih_enc.biHeight  )  {			
				bNotMatched  =  TRUE;
				//  goto  errLabel;												   
			}								
			}			
		else  {			
			  pTransform->video.tv.vh_compress.bih.biWidth  =  bih_enc.biWidth;				
			  pTransform->video.tv.vh_compress.bih.biHeight  =  bih_enc.biHeight;											   
			  //
			  bModified  =  TRUE;
		}
											   
		//		
		if  (  pTransform->video.tv.vh_decompress.bih.biWidth  &&  pTransform->video.tv.vh_decompress.bih.biHeight  )  {			
			if  (  pTransform->video.tv.vh_decompress.bih.biWidth  !=  bih_enc.biWidth  )  {
				bNotMatched  =  TRUE;
				//  goto  errLabel;												   
			}								
			if  (  pTransform->video.tv.vh_decompress.bih.biHeight  !=  bih_enc.biHeight  )  {			
				bNotMatched  =  TRUE;
				//  goto  errLabel;												   		
			}				
			}			
		else  {			  
			  pTransform->video.tv.vh_decompress.bih.biWidth  =  bih_enc.biWidth;				
			  pTransform->video.tv.vh_decompress.bih.biHeight  =  bih_enc.biHeight;											   
			  //
			  bModified  =  TRUE;
		}				

		//  2014/08/05
		if  (  bModified  )  {
			pTransform->video.dwLastmodifiedTickCnt_keyParams  =  GetTickCount(  );
		}
	}

	//  2014/04/22
	pTransform->video.decInfo.dFrameRate_dec  =  dFrameRate;


	iErr  =  0;
errLabel:

	TCHAR  tBuf[128]  =  _T(  ""  );
	if  (  iErr  ||  bNotMatched  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "updateDecVideoParam failed: bih_enc %d,%d. vh_compress %d,%d, vh_dec %d,%d"  ),  bih_enc.biWidth,  bih_enc.biHeight,  pTransform->video.tv.vh_compress.bih.biWidth,  pTransform->video.tv.vh_compress.bih.biHeight,  pTransform->video.tv.vh_decompress.bih.biWidth,  pTransform->video.tv.vh_decompress.bih.biHeight  );
		}
	else  {
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "updateDecVideoParam ok: bih_enc %d,%d. frameRate %f"  ),  bih_enc.biWidth,  bih_enc.biHeight,  (  float  )pTransform->video.decInfo.dFrameRate_dec  );		
	}
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  tBuf  );

	return  iErr;

}




//  mediaSdk的处理和其他的解压缩不同，是一直自己循环。为了避免从其他的解压缩处理中间跳到这里，需要先exitTaskVideo。清理一下
int  doDecodeVideo_mediaSdk(  QY_TRANSFORM  *  pTransform,  int  index_pMems_from1,  int  index_activeMems_from,  MIS_MSGU  *  pMsgBuf  )
{
	int					iErr	=	-1;
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pTransform->pProcInfo;//QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
#if  0
	QY_MC			*	pQyMc	=	(  QY_MC  *  )pProcInfo->pQyMc;//QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
#endif
	CUS_MODULES  *  pCusModules  =  (  CUS_MODULES  *  )pProcInfo->getCusModules(  );
	if  (  !pCusModules  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "doDecV_msdk failed, pCusModules is null"  )  );
		#endif
		return  -1;
	}	
	MSGR_ADDR			*	pAddr				=	pTransform->pAddr_logicalPeer;
	if  (  !pAddr  )  return  -1;
	int						iTaskId				=	pTransform->iTaskId;
	//
	AV_TRAN_INFO		*	pTranInfo_unused			=	(  AV_TRAN_INFO  *  )pTransform->pTranInfo_unused;
	if  (  !pTranInfo_unused  )  return  -1;
	//
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pTransform->pTask;
	if  (  !pTask  )  return  -1;

	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  (  CCtxQmc  *  )pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  ) return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

#if  0
	TASK_AV_FROM		*	pFrom				=	NULL;

	pFrom  =  getTaskAvFrom(  pTransform,  index_pMems_from,  pTransform->index_activeMems_from,  _T(  "doDecodeVideo_msdk"  )  );
	if  (  !pFrom  )  return  -1;
#endif
	if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTc->videoConference.usCntLimit_activeMems_from  )  return  -1;
	DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pTc->videoConference.activeMems_from[index_activeMems_from];
	//
	exitTaskAvFrom_video(  pProcInfo,  pTransform  );
	

	MACRO_setMyStep(  pTransform->video.debugStep,  21  );

		 //  if  (  !pFrom->video.ucbInited  )  
		 if  (  !pTransform->video.ucbInited  )  
		 {
			 unsigned  int  uiModuleType_suggested  =  CONST_moduleType_mediaSdk_dec;
			 BOOL  bUseDecTool  =  FALSE;
			 if  (  initTaskAvFrom_video(  pProcInfo,  pActiveMem_from,  index_activeMems_from,  pTransform->iTaskId,  uiModuleType_suggested,  bUseDecTool,  pTransform  )  )  goto  errLabel;
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskVideo: initTaskAvFrom_video %d"  ),  index_activeMems_from  );
		 }
		 if  (  !pTransform->video.ucbInited  )  {
			 traceLogA(  (char*)  "procTaskVideo failed: video is not inited"  );
			 goto  errLabel;
		 }

		 //
		 if  (  pTransform->video.uiModuleType_toDec  !=  CONST_moduleType_mediaSdk_dec  )  {
			 #ifdef  __DEBUG__
					 traceLog((TCHAR*)  _T(  "doTransformVideo_mediaSdk failed, uiModuleType_toDec is not mediaSdk_dec"  )  );
			 #endif
			 goto  errLabel;
		 }

		 //
		 if  (  !pCusModules->pMediaSdk_dec
			 ||  !pCusModules->pMediaSdk_dec->compress.pf_qdcDecompressVideoRun  )
		 {
			 goto  errLabel;
		 }

		 __try  {
				if  (  pCusModules->pMediaSdk_dec->compress.pf_qdcDecompressVideoRun(  &pTransform->video.u.qoi.myQoi.common  )  )  goto  errLabel;
				 }
		 __except  (  1  )  {
				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "qdcDecompressVideoRun exception"  )  );
				   #endif
				   goto  errLabel;
		 }


		 iErr  =  0;
errLabel:

		 //  2015/01/17
		 if  (  pTransform->video.debugStep.dec.sts_SyncOperation324  ==  -17  )  {
			 showNotification_open(  0,  0,  0,  _T(  "Note: SyncOperation returns DEVICE_FAILED"  )  );
		 }

		 //
		 exitTaskAvFrom_video(  pProcInfo,  pTransform  );  

	return  iErr;
}



int  doDecodeVideo_vpl(QY_TRANSFORM* pTransform, int  index_pMems_from1, int  index_activeMems_from, MIS_MSGU* pMsgBuf)
{
	int					iErr = -1;
	MC_VAR_common* pProcInfo = (MC_VAR_common*)pTransform->pProcInfo;//QY_GET_procInfo_isCli(  );
	if (!pProcInfo)  return  -1;
#if  0
	QY_MC* pQyMc = (QY_MC*)pProcInfo->pQyMc;//QY_GET_GBUF(  );
	if (!pQyMc)  return  -1;
#endif
	CUS_MODULES* pCusModules = (CUS_MODULES*)pProcInfo->getCusModules();
	if (!pCusModules) {
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("doDecV_msdk failed, pCusModules is null"));
#endif
		return  -1;
	}
	MSGR_ADDR* pAddr = pTransform->pAddr_logicalPeer;
	if (!pAddr)  return  -1;
	int						iTaskId = pTransform->iTaskId;
	//
	AV_TRAN_INFO* pTranInfo_unused = (AV_TRAN_INFO*)pTransform->pTranInfo_unused;
	if (!pTranInfo_unused)  return  -1;
	//
	PROC_TASK_AV* pTask = (PROC_TASK_AV*)pTransform->pTask;
	if (!pTask)  return  -1;

	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex((CCtxQmc*)pProcInfo, pTask->iIndex_taskInfo);
	if (!pTaskInfo) return  -1;
	if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  return  -1;
	QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;

#if  0
	TASK_AV_FROM* pFrom = NULL;

	pFrom = getTaskAvFrom(pTransform, index_pMems_from, pTransform->index_activeMems_from, _T("doDecodeVideo_msdk"));
	if (!pFrom)  return  -1;
#endif
	if (index_activeMems_from < 0 || index_activeMems_from >= pTc->videoConference.usCntLimit_activeMems_from)  return  -1;
	DLG_TALK_videoConferenceActiveMemFrom* pActiveMem_from = &pTc->videoConference.activeMems_from[index_activeMems_from];
	//
	exitTaskAvFrom_video(pProcInfo, pTransform);


	MACRO_setMyStep(pTransform->video.debugStep, 21);

	//  if  (  !pFrom->video.ucbInited  )  
	if (!pTransform->video.ucbInited)
	{
		unsigned  int  uiModuleType_suggested = CONST_moduleType_dec_vpl;
		BOOL  bUseDecTool = FALSE;
		if (initTaskAvFrom_video(pProcInfo, pActiveMem_from, index_activeMems_from, pTransform->iTaskId, uiModuleType_suggested, bUseDecTool, pTransform))  goto  errLabel;
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("procTaskVideo: initTaskAvFrom_video %d"), index_activeMems_from);
	}
	if (!pTransform->video.ucbInited) {
		traceLogA((char*)"procTaskVideo failed: video is not inited");
		goto  errLabel;
	}

	//
	if (pTransform->video.uiModuleType_toDec != CONST_moduleType_dec_vpl) {
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("doTransformVideo_mediaSdk failed, uiModuleType_toDec is not dec_vpl"));
#endif
		goto  errLabel;
	}

	//
	CUS_MODULE_U* pModule; pModule = pCusModules->pDec_vpl;

	//
	if (!pModule
		|| !pModule->compress.pf_qdcDecompressVideoRun)
	{
		goto  errLabel;
	}

	__try {
		if (pModule->compress.pf_qdcDecompressVideoRun(&pTransform->video.u.qoi.myQoi.common))  goto  errLabel;
	}
	__except (1) {
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("qdcDecompressVideoRun exception"));
#endif
		goto  errLabel;
	}


	iErr = 0;
errLabel:

	//  2015/01/17
	if (pTransform->video.debugStep.dec.sts_SyncOperation324 == -17) {
		showNotification_open(0, 0, 0, _T("Note: SyncOperation returns DEVICE_FAILED"));
	}

	//
	exitTaskAvFrom_video(pProcInfo, pTransform);

	return  iErr;
}




//  2014/06/25
int  doDecodeVideo_nv(  QY_TRANSFORM  *  pTransform,  int  index_pMems_from,  int  index_activeMems_from, MIS_MSGU  *  pMsgBuf  )
{
	int					iErr	=	-1;
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pTransform->pProcInfo;//QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
#if  0
	QY_MC			*	pQyMc	=	(  QY_MC  *  )pProcInfo->pQyMc;//QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
#endif
		CUS_MODULES  *  pCusModules  =  (  CUS_MODULES  *  )pProcInfo->getCusModules(  );
	if  (  !pCusModules  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "doDecV_nv failed, pCusModules is null"  )  );
		#endif
		return  -1;
	}	

	
	MSGR_ADDR			*	pAddr				=	pTransform->pAddr_logicalPeer;
	if  (  !pAddr  )  return  -1;
	int						iTaskId				=	pTransform->iTaskId;
	//
	AV_TRAN_INFO		*	pTranInfo_unused			=	(  AV_TRAN_INFO  *  )pTransform->pTranInfo_unused;
	if  (  !pTranInfo_unused  )  return  -1;
	//
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pTransform->pTask;
	if  (  !pTask  )  return  -1;
	//
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  (  CCtxQmc  *  )pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return -1;
	QMC_taskData_conf  *  pTc =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

	
#if  0
	TASK_AV_FROM		*	pFrom				=	NULL;
	pFrom  =  getTaskAvFrom(  pTransform,  index_pMems_from,  pTransform->index_activeMems_from,  _T(  "doDecodeVideo_nv"  )  );
	if  (  !pFrom  )  return  -1;
#endif
	if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTc->videoConference.usCntLimit_activeMems_from  )  return -1;
	DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pTc->videoConference.activeMems_from[index_activeMems_from];

	//
	exitTaskAvFrom_video(  pProcInfo,  pTransform  );
	

	MACRO_setMyStep(  pTransform->video.debugStep,  21  );

		 //  if  (  !pFrom->video.ucbInited  )  
		 if  (  !pTransform->video.ucbInited  )  
		 {
			 unsigned  int  uiModuleType_suggested  =  CONST_moduleType_dec_nv;
			 BOOL  bUseDecTool  =  FALSE;
			 if  (  initTaskAvFrom_video(  pProcInfo,  pActiveMem_from,  index_activeMems_from,  pTransform->iTaskId,  uiModuleType_suggested,  bUseDecTool,  pTransform  )  )  goto  errLabel;
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskVideo: initTaskAvFrom_video %d"  ),  index_pMems_from  );
		 }
		 if  (  !pTransform->video.ucbInited  )  {
			 traceLogA(  (char*)  "procTaskVideo failed: video is not inited"  );
			 goto  errLabel;
		 }

		 //
		 if  (  pTransform->video.uiModuleType_toDec  !=  CONST_moduleType_dec_nv  )  {
			 #ifdef  __DEBUG__
					 traceLog((TCHAR*)  _T(  "doTransformVideo_mediaSdk failed, uiModuleType_toDec is not mediaSdk_dec"  )  );
			 #endif
			 goto  errLabel;
		 }

		 //
		 if  (  !pCusModules->pDec_nv
			 ||  !pCusModules->pDec_nv->compress.pf_qdcDecompressVideoRun  )
		 {
			 goto  errLabel;
		 }

		 __try  {
			    if  (  pCusModules->pDec_nv->compress.pf_qdcDecompressVideoRun(  &pTransform->video.u.qoi.myQoi.common  )  )  goto  errLabel;
				 }
		 __except  (  1  )  {
				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "qdcDecompressVideoRun exception"  )  );
				   #endif
				   goto  errLabel;
		 }


		 iErr  =  0;
errLabel:

		 exitTaskAvFrom_video(  pProcInfo,  pTransform  );  

	return  iErr;
}


//
//  2014/06/25
int  doDecodeVideo_decD3d_nv(QY_TRANSFORM* pTransform, int  index_pMems_from, int  index_activeMems_from, MIS_MSGU* pMsgBuf)
{
	int					iErr = -1;
	MC_VAR_common* pProcInfo = (MC_VAR_common*)pTransform->pProcInfo;//QY_GET_procInfo_isCli(  );
	if (!pProcInfo)  return  -1;
#if  0
	QY_MC* pQyMc = (QY_MC*)pProcInfo->pQyMc;//QY_GET_GBUF(  );
	if (!pQyMc)  return  -1;
#endif
	CUS_MODULES* pCusModules = (CUS_MODULES*)pProcInfo->getCusModules();
	if (!pCusModules) {
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("doDecV_nv failed, pCusModules is null"));
#endif
		return  -1;
	}


	MSGR_ADDR* pAddr = pTransform->pAddr_logicalPeer;
	if (!pAddr)  return  -1;
	int						iTaskId = pTransform->iTaskId;
	//
	AV_TRAN_INFO* pTranInfo_unused = (AV_TRAN_INFO*)pTransform->pTranInfo_unused;
	if (!pTranInfo_unused)  return  -1;
	//
	PROC_TASK_AV* pTask = (PROC_TASK_AV*)pTransform->pTask;
	if (!pTask)  return  -1;
	//
	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex((CCtxQmc*)pProcInfo, pTask->iIndex_taskInfo);
	if (!pTaskInfo)  return  -1;
	if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  return -1;
	QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;


#if  0
	TASK_AV_FROM* pFrom = NULL;
	pFrom = getTaskAvFrom(pTransform, index_pMems_from, pTransform->index_activeMems_from, _T("doDecodeVideo_nv"));
	if (!pFrom)  return  -1;
#endif
	if (index_activeMems_from < 0 || index_activeMems_from >= pTc->videoConference.usCntLimit_activeMems_from)  return -1;
	DLG_TALK_videoConferenceActiveMemFrom* pActiveMem_from = &pTc->videoConference.activeMems_from[index_activeMems_from];

	//
	exitTaskAvFrom_video(pProcInfo, pTransform);


	MACRO_setMyStep(pTransform->video.debugStep, 21);

	//  if  (  !pFrom->video.ucbInited  )  
	if (!pTransform->video.ucbInited)
	{
		unsigned  int  uiModuleType_suggested = CONST_moduleType_decD3d_nv;
		BOOL  bUseDecTool = FALSE;
		if (initTaskAvFrom_video(pProcInfo, pActiveMem_from, index_activeMems_from, pTransform->iTaskId, uiModuleType_suggested, bUseDecTool, pTransform))  goto  errLabel;
		qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("procTaskVideo: initTaskAvFrom_video %d"), index_pMems_from);
	}
	if (!pTransform->video.ucbInited) {
		traceLogA((char*)"procTaskVideo failed: video is not inited");
		goto  errLabel;
	}

	//
	if (pTransform->video.uiModuleType_toDec != CONST_moduleType_decD3d_nv) {
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("doTransformVideo_mediaSdk failed, uiModuleType_toDec is not mediaSdk_dec"));
#endif
		goto  errLabel;
	}

	//
	if (!pCusModules->pDecD3d_nv
		|| !pCusModules->pDecD3d_nv->compress.pf_qdcDecompressVideoRun)
	{
		goto  errLabel;
	}

	__try {
		if (pCusModules->pDecD3d_nv->compress.pf_qdcDecompressVideoRun(&pTransform->video.u.qoi.myQoi.common))  goto  errLabel;
	}
	__except (1) {
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("qdcDecompressVideoRun exception"));
#endif
		goto  errLabel;
	}


	iErr = 0;
errLabel:

	exitTaskAvFrom_video(pProcInfo, pTransform);

	return  iErr;
}





//  2015/04/30
int  doDecodeVideo_amf(  QY_TRANSFORM  *  pTransform,  int  index_pMems_from,  MIS_MSGU  *  pMsgBuf  )
{
	int					iErr	=	-1;
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pTransform->pProcInfo;//QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
#if  0
	QY_MC			*	pQyMc	=	(  QY_MC  *  )pProcInfo->pQyMc;//QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
#endif
		CUS_MODULES  *  pCusModules  =  (  CUS_MODULES  *  )pProcInfo->getCusModules(  );
	if  (  !pCusModules  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "doDecV_nv failed, pCusModules is null"  )  );
		#endif
		return  -1;
	}	

	
	MSGR_ADDR			*	pAddr				=	pTransform->pAddr_logicalPeer;
	if  (  !pAddr  )  return  -1;
	int						iTaskId				=	pTransform->iTaskId;
	//
	AV_TRAN_INFO		*	pTranInfo_unused			=	(  AV_TRAN_INFO  *  )pTransform->pTranInfo_unused;
	if  (  !pTranInfo_unused  )  return  -1;
	//
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pTransform->pTask;
	if  (  !pTask  )  return  -1;

#if  0
	TASK_AV_FROM		*	pFrom				=	NULL;
	pFrom  =  getTaskAvFrom(  pTransform,  index_pMems_from,  pTransform->index_activeMems_from,  _T(  "doDecodeVideo_nv"  )  );
	if  (  !pFrom  )  return  -1;

	//
	exitTaskAvFrom_video(  pProcInfo,  pTransform  );
	

	MACRO_setMyStep(  pTransform->video.debugStep,  21  );

		 //  if  (  !pFrom->video.ucbInited  )  
		 if  (  !pTransform->video.ucbInited  )  
		 {
			 unsigned  int  uiModuleType_suggested  =  CONST_moduleType_dec_amf;
			 BOOL  bUseDecTool  =  FALSE;
			 if  (  initTaskAvFrom_video(  pProcInfo,  pFrom,  index_pMems_from,  pTransform->iTaskId,  uiModuleType_suggested,  bUseDecTool,  pTransform  )  )  goto  errLabel;
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskVideo: initTaskAvFrom_video %d"  ),  index_pMems_from  );
		 }
		 if  (  !pTransform->video.ucbInited  )  {
			 traceLogA(  (char*)  "procTaskVideo failed: video is not inited"  );
			 goto  errLabel;
		 }

		 //
		 if  (  pTransform->video.uiModuleType_toDec  !=  CONST_moduleType_dec_amf  )  {
			 #ifdef  __DEBUG__
					 traceLog((TCHAR*)  _T(  "doTransformVideo_mediaSdk failed, uiModuleType_toDec is not dec_amf"  )  );
			 #endif
			 goto  errLabel;
		 }

		 //
		 if  (  !pCusModules->pDec_amf
			 ||  !pCusModules->pDec_amf->compress.pf_qdcDecompressVideoRun  )
		 {
			 goto  errLabel;
		 }

		 __try  {
				if  (  pCusModules->pDec_amf->compress.pf_qdcDecompressVideoRun(  &pTransform->video.u.qoi.myQoi.common  )  )  goto  errLabel;
				 }
		 __except  (  1  )  {
				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "qdcDecompressVideoRun exception"  )  );
				   #endif
				   goto  errLabel;
		 }
#endif

		 iErr  =  0;
errLabel:

		 exitTaskAvFrom_video(  pProcInfo,  pTransform  );  

	return  iErr;
}


//  2014/07/21
int  doDecodeVideo_vp8(  QY_TRANSFORM  *  pTransform,  int  index_pMems_from1,  int index_activeMems_from,  MIS_MSGU  *  pMsgBuf  )
{
	int					iErr	=	-1;
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pTransform->pProcInfo;//QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
#if  0
	QY_MC			*	pQyMc	=	(  QY_MC  *  )pProcInfo->pQyMc;//QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
#endif
		CUS_MODULES  *  pCusModules  =  (  CUS_MODULES  *  )pProcInfo->getCusModules(  );
	if  (  !pCusModules  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "doDecV_vp8 failed, pCusModules is null"  )  );
		#endif
		return  -1;
	}	

	
	MSGR_ADDR			*	pAddr				=	pTransform->pAddr_logicalPeer;
	if  (  !pAddr  )  return  -1;
	int						iTaskId				=	pTransform->iTaskId;
	//
	AV_TRAN_INFO		*	pTranInfo_unused			=	(  AV_TRAN_INFO  *  )pTransform->pTranInfo_unused;
	if  (  !pTranInfo_unused  )  return  -1;
	//
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pTransform->pTask;
	if  (  !pTask  )  return  -1;

	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  (  CCtxQmc  *  )pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

#if  0
	TASK_AV_FROM		*	pFrom				=	NULL;

	pFrom  =  getTaskAvFrom(  pTransform,  index_pMems_from,  pTransform->index_activeMems_from,  _T(  "doDecodeVideo_vp8"  )  );
	if  (  !pFrom  )  return  -1;
#endif
	if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTc->videoConference.usCntLimit_activeMems_from  )  return  -1;
	DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from = &pTc->videoConference.activeMems_from[index_activeMems_from];

	//
	exitTaskAvFrom_video(  pProcInfo,  pTransform  );
	

	MACRO_setMyStep(  pTransform->video.debugStep,  21  );

		 //  if  (  !pFrom->video.ucbInited  )  
		 if  (  !pTransform->video.ucbInited  )  
		 {
			 unsigned  int  uiModuleType_suggested  =  CONST_moduleType_dec_vp8;
			 BOOL  bUseDecTool  =  FALSE;
			 if  (  initTaskAvFrom_video(  pProcInfo,  pActiveMem_from,  index_activeMems_from,  pTransform->iTaskId,  uiModuleType_suggested,  bUseDecTool,  pTransform  )  )  goto  errLabel;
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskVideo: initTaskAvFrom_video %d"  ),  index_activeMems_from  );
		 }
		 if  (  !pTransform->video.ucbInited  )  {
			 traceLogA(  (char*)  "procTaskVideo failed: video is not inited"  );
			 goto  errLabel;
		 }

		 //
		 if  (  pTransform->video.uiModuleType_toDec  !=  CONST_moduleType_dec_vp8  )  {
			 #ifdef  __DEBUG__
					 traceLog((TCHAR*)  _T(  "doTransformVideo_mediaSdk failed, uiModuleType_toDec is not mediaSdk_dec"  )  );
			 #endif
			 goto  errLabel;
		 }

		 //
		 if  (  !pCusModules->pDec_vp8
			 ||  !pCusModules->pDec_vp8->compress.pf_qdcDecompressVideoRun  )
		 {
			 goto  errLabel;
		 }

		 __try  {
				if  (  pCusModules->pDec_vp8->compress.pf_qdcDecompressVideoRun(  &pTransform->video.u.qoi.myQoi.common  )  )  goto  errLabel;
				 }
		 __except  (  1  )  {
				   #ifdef  __DEBUG__
						   traceLog((TCHAR*)  _T(  "qdcDecompressVideoRun exception"  )  );
				   #endif
				   goto  errLabel;
		 }


		 iErr  =  0;
errLabel:

		 exitTaskAvFrom_video(  pProcInfo,  pTransform  );  

	return  iErr;
}


//
void  postVPktToRender(  void  *  pQY_TRANSFORM,  void  *  pmyDRAW_VIDEO_DATA,  BOOL  *  pbPktRedirected  )
{
	int				iErr		=	-1;
	QY_TRANSFORM  *  pTransform  =  (  QY_TRANSFORM  *  )pQY_TRANSFORM;
	myDRAW_VIDEO_DATA  *  pPkt  =  (  myDRAW_VIDEO_DATA  *  )pmyDRAW_VIDEO_DATA;
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pTransform->pProcInfo;//QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
		
	BOOL  bPktsRedirected  =  FALSE;			

	//
	if  (  pTransform->pCapDev_rtsp  )  {
				  //VIDEO_capDev_rtsp				*	pRtsp							=	(  VIDEO_capDev_rtsp  *  )pTransform->pCapDev_rtsp;
				  CAP_dev_rtspCommon				*	pRtsp							=	(  CAP_dev_rtspCommon  *  )pTransform->pCapDev_rtsp;
			 
				  QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pRtsp->iIndex_sharedObj  );			 
				  if  (  !pSharedObj  )  goto  errLabel;
				  CAP_procInfo_video  *  pVc  =  (  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
				  if  (  !pVc  )  goto  errLabel;
				  TRANSINFO_stream				*	pTransInfo					=	(  TRANSINFO_stream  *  )pSharedObj->pTransInfo_stream;
				  if  (  !pTransInfo  )  goto  errLabel;
				  if  (  !pTransInfo->myTask.pTransforms  )  goto  errLabel;
			 

				  //  dec可能是异步的，所以可能没输出数据。这时候，pkt.bih没赋值，所以需要判断下. 2014/03/16					 
				  if  (  pPkt->bih.biWidth  &&  pPkt->bih.biHeight  )  {
					  //
					  if  (  pPkt->bih.biWidth  !=  pVc->vh_org.bih.biWidth  ||  pPkt->bih.biHeight  !=  pVc->vh_org.bih.biHeight  )  {
						  #ifdef  __DEBUG__
								  traceLog((TCHAR*)  _T(  "postVPktToRender failed, pkt %dx%d != pVc.vh_org %dx%d"  ),  pPkt->bih.biWidth,  pPkt->bih.biHeight,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight  );
						  #endif
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "postVPktToRender failed, pkt %dx%d != pVc.vh_org %dx%d"  ),  pPkt->bih.biWidth,  pPkt->bih.biHeight,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight  );
						  goto  errLabel;
					  }
					  
					  //
					  if  (  pRtsp->uiType  ==  CONST_rtspType_decV  )  {
						  VIDEO_capDev_rtsp  *  pRtsp1  =  (  VIDEO_capDev_rtsp  *  )pRtsp;
						  //  2015/02/01
						  if  (  !pRtsp1->bQInited_dvt_decV  )  {
							  showInfo_open0(  0,  0,  _T(  "postVPktTotender failed: cacheQ not inited"  )  );						  
							  goto  errLabel;
						  }
						  //
						  //  2015/10/06
						  QMC_cfg  *  pCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
						  if  (  pCfg  &&  pCfg->debugStatusInfo.ucbShowRenderStatus  )  {
								  if  (  pPkt->usPktResType  ==  CONST_pktResType_sharedTex  )  {
									  TCHAR  tBuf[128];
									  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "postVPktToRender: sn %d ok"  ),  pPkt->sharedTex.pktSharedTexInfo.uiSeqNo  );
									  showInfo_open0(  0,  0,  tBuf  );
								  }
						  }
						  //
						  #ifdef  __DEBUG__  //  2015/10/06
								  //showInfo_open0(  0,  0,  _T(  "postVPktTotender: haha"  )  );			
						  #endif
						  //
						  if  (  !q2PostMsgAndTrigger(  pPkt,  1  *  sizeof(  pPkt[0]  ),  &pRtsp1->cacheQ2_dvt_decV,  _T(  "postVPktToRender"  ))) {
							  bPktsRedirected  =  TRUE;																					 						  
						  }											 					  

						  }
#if  0
					  else  if  (  pRtsp->uiType  ==  CONST_rtspType_qvcf  )  {
						        //  2015/05/12
								int  i;
								i  =  99;
								drawLocalVideoData(
								}
#endif
					  else  {

						    //  2014/09/08
						    if  (  !pVc->vppThread.bQInited  )  {						  
								showInfo_open0(  0,  0,  _T(  "postVPktToRender failed: vpp.q not inited"  )  );
								goto  errLabel;				  					  
							}
							
							//
							BOOL  bNoSkip  =  FALSE;
							//
							if  (  pSharedObj->uiType1  ==  CONST_sharedObjType_qvcf  )  {	//  2015/05/25. 本地播放，不需要帧速控制
								bNoSkip  =  TRUE;
							}
							//				 
							if  (  !setPktInputInfo(  pProcInfo,  &pVc->compressVideo.input_BufferCB,  pVc->compressVideo.usFrames_perSecond_expected,  bNoSkip,  pPkt,  mynull,  NULL  )  )  {														  
								//
								if  (  !q2PostMsgAndTrigger(  pPkt,  1  *  sizeof(  pPkt[0]  ),  &pVc->vppThread.q2,  _T(  "postVPktToRender 1"  ))) {
									bPktsRedirected  =  TRUE;																					 						  
								}											 					  
							}		

					  }
				  }			 
	
		}		
	else  {		
		  //  drawVideoData(  pProcInfo,  pPkt,  1  *  sizeof(  pPkt[0]  ),  &bPktsRedirected,  pTransform->iIndex_player  );		
		  pProcInfo->drawVideoData(  pPkt,  1  *  sizeof(  pPkt[0]  ),  &bPktsRedirected,  pTransform  );		 		
	}

	//
	iErr  =  0;

errLabel:
			  if  (  pbPktRedirected  )  {
				  *pbPktRedirected  =  bPktsRedirected;
			  }
			  return;

}


//
int  doDecodeVideo_default(  QY_TRANSFORM  *  pTransform,  int  index_pMems_from1,  int  index_activeMems_from,  MIS_MSGU  *  pMsgBuf  )
{
	int					iErr	=	-1;
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pTransform->pProcInfo;//QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	MSGR_ADDR			*	pAddr				=	pTransform->pAddr_logicalPeer;
	if  (  !pAddr  )  return  -1;
	int						iTaskId				=	pTransform->iTaskId;
	//
	AV_TRAN_INFO		*	pTranInfo_unused			=	(  AV_TRAN_INFO  *  )pTransform->pTranInfo_unused;
	if  (  !pTranInfo_unused  )  return  -1;
	//
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pTransform->pTask;
	if  (  !pTask  )  return  -1;

	//
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  (  CCtxQmc  *  )pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

	//				 
#if  0
	if  (  index_pMems_from  <  0  ||  index_pMems_from  >=  pTc->videoConference.usCntLimit_mems_from  )  {
			 #ifdef  __DEBUG__
					 traceLog((TCHAR*)  _T(  "doDecVideo: index_pMems_from err"  )  );
			 #endif
			 return  -1;
	
	}	
	TASK_AV_FROM		*	pFrom				=	NULL;	//  &pTask->pMems_from[index_pMems_from];
		
	pFrom  =  getTaskAvFrom(  pTransform,  index_pMems_from,  pTransform->index_activeMems_from,  _T(  "doDecodeVideo_default"  )  );
	if  (  !pFrom  )  return  -1;
#endif
	if  (  index_activeMems_from  <  0  ||  index_activeMems_from >=  pTc->videoConference.usCntLimit_activeMems_from  )  return  -1;
	DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  =  &pTc->videoConference.activeMems_from[index_activeMems_from];


	//  2014/05/08
	_sntprintf(  pTransform->video.debugStep.showInfo.tWhere,  mycountof(  pTransform->video.debugStep.showInfo.tWhere  ),  _T(  "tt=%d"  ),  iTaskId  );
	pTransform->video.debugStep.showInfo.uiStep  =  0;
	
	//
	MACRO_setMyStep(  pTransform->video.debugStep,  21  );

		 //  if  (  !pFrom->video.ucbInited  )  
		 if  (  !pTransform->video.ucbInited  )  
		 {
			 if  (  initTaskAvFrom_video(  pProcInfo,  pActiveMem_from,  index_activeMems_from,  pTransform->iTaskId,  0,  FALSE,  pTransform  )  )  goto  errLabel;
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskVideo: initTaskAvFrom_video %d"  ),  index_activeMems_from  );
		 }
		 if  (  !pTransform->video.ucbInited  )  {
			 traceLogA(  (char*)  "procTaskVideo failed: video is not inited"  );
			 goto  errLabel;
		 }

		 long  old_pktId; old_pktId = 0;
		 //
		 for  (  ;  ;  )  {
			  if  (  bTransformVideoQuit(  pTransform,  0,  0  )  )  {
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "doTrans_default failed：quit is true"  )  );
				  #endif
				  goto  errLabel;
			  }
			  //
			  MACRO_setMyStep(  pTransform->video.debugStep,  100  );	//  2014/07/17
			  //
			  for  (  ;  ;  )  {
				   if  (  bTransformVideoQuit(  pTransform,  0,  0  )  )  goto  errLabel;
				   //
				   MACRO_setMyStep(  pTransform->video.debugStep,  105  );	//  2014/07/17
				   //
				   if  (  !getNextVPkt(  pTransform->video.pCurPkt,  pTransform->video.pInDataCacheQ,  &pTransform->video.q2  )  )  break;
				   //
				   MACRO_setMyStep(  pTransform->video.debugStep,  106  );	//  2014/07/17
				   //
				   Sleep(  100  );
			  }
			  //
			  MACRO_setMyStep(  pTransform->video.debugStep,  108  );	//  2014/07/17
			  //
			  unsigned  char  *  pInput  =  NULL;
			  unsigned  int  uiInputSize  =  0;
			  unsigned  int  uiSampleTimeInMs  =  0;
			  unsigned  int  uiPts  =  0;	//  2015/02/09
			  //  2015/02/24
			  SMPL_bsRead_param  param;
			  memset(  &param,  0,  sizeof(  param  )  );
			  //
			  if  (  dec_parseEncVPkt_i(  CONST_uiTransformType_dec,  pTransform,  pTransform->video.pCurPkt,  &old_pktId,  &pInput,  &uiInputSize,  &uiSampleTimeInMs,  &uiPts,  &param  )  )  {
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "doDecodeVideo_default failed, parsePkt failed"  )  );
				  #endif
				  goto  errLabel;  
			  }

			  //			  	
			  MACRO_setMyStep(  pTransform->video.debugStep,  109  );	//  2014/07/17


			  //
			  myDRAW_VIDEO_DATA  * pPkt  =  pTransform->video.pCurPkt;

			  doDecVideoPkt(  pTransform,  pPkt,  pMsgBuf  );

			  //
			  MACRO_setMyStep(  pTransform->video.debugStep,  110  );	//  2014/07/17
			  

			  //  2014/08/11
			  if  (  pTransform->video.status.ucbDecFailed  )  {
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doDecodeVideo_default: decFailed, need to reinited. %d"  ),  index_activeMems_from  );
				  goto  errLabel;
			  }

			  //  2014/04/07
			  if  (  pTransform->video.status.ucbNeedReinited  )  {
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doDecodeVideo_default: need to reinited. %d"  ),  index_activeMems_from  );
				  goto  errLabel;
			  }

			  //
			  BOOL  bPktsRedirected  =  FALSE;			
			  //
			  postVPktToRender(  pTransform,  pPkt,  &bPktsRedirected  );
			  if  (  bPktsRedirected  )  {
				  detachVPkt(  pPkt,  0  );
				  }
			  else  {
				    clean_myDRAW_VIDEO_DATA(  pTransform->video.pCurPkt,  _T(  ""  )  );
			  }

			  //
			  continue;
		 }


		 iErr  =  0;
errLabel:

		 exitTaskAvFrom_video(  pProcInfo,  pTransform  );  

	return  iErr;
}




//
int  doDecodeVideo(  QY_TRANSFORM  *  pTransform,  MIS_MSGU  *  pMsgBuf  )
{
	int		iErr	=	-1;	 

	int	i;
	MC_VAR_common		*				pProcInfo					=	(  MC_VAR_common  *  )pTransform->pProcInfo;//QY_GET_procInfo_isCli(  );
	if (  !pProcInfo  )  return  -1;	 
#if  10
	QY_MC				*				pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;//QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
#endif

	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;
	

	MSGR_ADDR			*	pAddr				=	pTransform->pAddr_logicalPeer;
	if  (  !pAddr  )  return  -1;
	int						iTaskId				=	pTransform->iTaskId;
	//
	AV_TRAN_INFO		*	pTranInfo_unused			=	(  AV_TRAN_INFO  *  )pTransform->pTranInfo_unused;
	if  (  !pTranInfo_unused  )  return  -1;
	//
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pTransform->pTask;
	if  (  !pTask  )  return  -1;

	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO *  )getQmcTaskInfoByIndex(  (  CCtxQmc  *  )pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc   =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;



	//
	TRANSFORM_VIDEO_procInfo		*	pTransformVideo				=	&pTransform->video;

	myDRAW_VIDEO_DATA  *     pPkt  =  pTransformVideo->pCurPkt;

			 int  index_pMems_from  =  pPkt->decInfo.index_pMems_from;
			 int  index_activeMems_from  =  pTransform->index_activeMems_from;
		 
		 //		
		 if  (  pPkt->head.uiLen  >  pPkt->memory.uiBufSize  
			 ||  pPkt->uiSize_dec  +  pPkt->uiOffset_enc  +  pPkt->uiLen_enc  >  pPkt->head.uiLen  )  			 
		 {
				#ifdef  __DEBUG__
						 traceLog((TCHAR*)  _T(  "doDecVideo: uiSize_dec or uiLen error"  )  );
				#endif
				return  -1;		 			 
		 }		 
		 char	*	encData	=  pPkt->memory.m_pBuf  +  pPkt->uiSize_dec  +  pPkt->uiOffset_enc;
		 myDRAW_VIDEO_DATA	*	pPkt_dec  =  pPkt;

		 //
#if  0
		 TASK_AV_FROM		*	pFrom				=	NULL;

		 //  2014/11/12
		 pFrom  =  getTaskAvFrom(  pTransform,  index_pMems_from,  index_activeMems_from,  _T(  "doDecodeVideo"  )  );
		 if  (  !pFrom  )  return  -1;
#endif
		 if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTc->videoConference.usCntLimit_activeMems_from  )  return  -1;
		 DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from  = &pTc->videoConference.activeMems_from[index_activeMems_from];
		 
		 //  2015/04/23
#ifdef  __DEBUG__
		 //showInfo_open0(  0,  0,  _T(  "kk"  )  );
#endif


		 //
		 unsigned  int  uiModuleType_toDec  =  0;
		 switch  (  pActiveMem_from->avStream.obj.tranInfo.video.compressor.common.ucCompressors  )  {
				 case  CONST_videoCompressors_stream:
				 case  CONST_videoCompressors_hwAccl:
				 case CONST_videoCompressors_ffmpeg:
					   uiModuleType_toDec  =  CONST_moduleType_mediaSdk_dec;
					   break;
				 case  CONST_videoCompressors_ipp:
					   uiModuleType_toDec  =  CONST_moduleType_ipp;					   
					   break;
				 case  CONST_videoCompressors_vp8:							//  2014/07/21
					   uiModuleType_toDec  =  CONST_moduleType_dec_vp8;
					   break;
				 default:
						break;
		 }
		 //
		 adjustModuleType_decV(pQyMc,&uiModuleType_toDec);
		 		 
		 //
		 #ifdef  __DEBUG__
			   #if  0
				    if  (  uiModuleType_toDec  )  {
						#if  10
							uiModuleType_toDec  =  CONST_moduleType_mediaSdk_dec;
							traceLog((TCHAR*)  _T(  "For test, use mediaSdk to dec "  )  );
						#else
							uiModuleType_toDec  =  CONST_moduleType_ipp;
							traceLog((TCHAR*)  _T(  "For test, use ipp to dec "  )  );
						#endif
					}
			   #endif
		#endif


		//  2015/01/19		
		if  (  pProcInfo->bSupported_dvt(  uiModuleType_toDec  )  ){			
			if  (  !pProcInfo->m_pf_doDecodeVideo_dvtCli  )  {
				showInfo_open0(  0,  0,  _T(  "doDecodeVideo failed, m_pf_doDecodeVideo_dvtCli is null"  )  );
				goto  errLabel;
			}
			return  pProcInfo->m_pf_doDecodeVideo_dvtCli(  pTransform,  index_pMems_from,  uiModuleType_toDec,  pMsgBuf  );				   						   
		}

		 //
		 switch  (  uiModuleType_toDec  )  {
				 case  CONST_moduleType_mediaSdk_dec:		 
					   doDecodeVideo_mediaSdk(  pTransform,  index_pMems_from,  index_activeMems_from,  pMsgBuf  );
					   break;
				 case  CONST_moduleType_dec_vpl:
					   doDecodeVideo_vpl(pTransform, index_pMems_from, index_activeMems_from, pMsgBuf);
					   break;
				 case  CONST_moduleType_dec_nv:	//  2014/06/25
					   doDecodeVideo_nv(  pTransform,  index_pMems_from,  index_activeMems_from,  pMsgBuf  );
					   break;
				 case  CONST_moduleType_decD3d_nv:
					   doDecodeVideo_decD3d_nv(pTransform, index_pMems_from, index_activeMems_from, pMsgBuf);
					   break;
				 case  CONST_moduleType_dec_amf:	//  2015/05/06
					   doDecodeVideo_amf(  pTransform,  index_pMems_from,  pMsgBuf  );
					   break;
				 case  CONST_moduleType_dec_vp8:
					   doDecodeVideo_vp8(  pTransform,  index_pMems_from,  index_activeMems_from,  pMsgBuf  );
					   break;
				 default:
					 //
					 doDecodeVideo_default(pTransform, index_pMems_from, index_activeMems_from, pMsgBuf);
					 break;
		 }



	iErr  =  0;

errLabel:

	//  	
	return  iErr;
}




 //  2014/03/24
 extern  "C"  DWORD WINAPI mcThreadProc_decVideo( LPVOID lpParameter )
{
	QY_TRANSFORM					*	pTransform						=	(  QY_TRANSFORM  *  )lpParameter;
	if  (  !pTransform  )  return  -1;
	 MC_VAR_common						*	pProcInfo					=	(  MC_VAR_common  *  )pTransform->pProcInfo;//QY_GET_procInfo_isCli(  );
	 if (  !pProcInfo  )  return  -1;	 

	 //  
	 TRANSFORM_VIDEO_procInfo		*	pTransformVideo				=	&pTransform->video;

	 QY_MC							*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;
	 //  DYN_LIB_DX						*	pDynLib						=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	 //  int								i;


	 //  2009/12/24

	 //
	 DWORD								dwThreadId					=	GetCurrentThreadId(  );

	 int								i;

	 //  
	 myDRAW_VIDEO_DATA					pkts[CONST_pkts_decVideo];
	 unsigned  int						uiLens[CONST_pkts_encVideo];		//  
	 int								nLens							=	mycountof(  uiLens  );		//  一次最多处理的包数。

	 int								nPkts;

	 //
#if  0
	 MIS_CNT						*	pMisCnt						=	(  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );
	 if  (  !pMisCnt  )  {
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "thread_decVideo failed, pMisCnt is null"  )  );
		 #endif
		 return  -1;	 	 
	 }
#endif

	 CQyMalloc							mallocObj_pMsgBuf;
	 MIS_MSGU						*	pMsgBuf						=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsgBuf  )  return  -1;


	 DWORD								dwTickCnt;

	 BOOL								bPktsRedirected;

	 CQyCoInit							coInit;		//  2010/06/07

	 //
	 traceLogA(  (char*)  "mcThreadProc_transformVideo enters"  );

	 MACRO_setStep(  pTransformVideo->debugStep,  CONST_threadStep_start  );

	 //
	 pTransformVideo->dwTickCnt_start  =  GetTickCount(  );
	 pTransformVideo->bRunning  =  TRUE;
	 //  memset(  &pTransformVideo->m_var,  0,  sizeof(  pTransformVideo->m_var  )  );


	 //  
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s %d starts"  ),  pTransformVideo->q2.cfg.name,  0  );


#ifdef  __DEBUG__
#endif
	 
	 //
	 //  2014/03/23	 	
	 GENERIC_Q_cfgEx	qCfgEx;	//  2012/11/10
	 GENERIC_Q_CFG		tmpCfg;

	TCHAR	tBuf[128];
#define		CONST_mutexNamePrefix_decV_inDataCacheQ	_T(  "decV_in"  )
#define		CONST_mutexNamePrefix_decV_tmpDataQ		_T(  "decV_tmp"  )
	//
	int		tn  =  GetTickCount(  );
	int		iTaskId  =  pTransform->iTaskId;
	int		index_activeMems_from  =  pTransform->index_activeMems_from;
	//
	int size  =  sizeof(  GENERIC_Q  );
	pTransformVideo->pInDataCacheQ  =  (  GENERIC_Q  *  )mymalloc(  size  );
	if  (  !pTransformVideo->pInDataCacheQ  )  goto  errLabel;
	memset(  pTransformVideo->pInDataCacheQ,  0,  size  );
	size  =  sizeof(  GENERIC_Q  );
	pTransformVideo->pTmpDataQ  =  (  GENERIC_Q  *  )mymalloc(  size  );
	if  (  !pTransformVideo->pTmpDataQ  )  goto  errLabel;
	memset(  pTransformVideo->pTmpDataQ,  0,  size  );

	//
	memset(  &tmpCfg,  0,  sizeof(  tmpCfg  )  );
	_sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-%d-%d-%d"  ),  CONST_mutexNamePrefix_decV_inDataCacheQ,  iTaskId,  index_activeMems_from,  tn  );
	_sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-%d-%d-%d"  ),  CONST_mutexNamePrefix_decV_inDataCacheQ,  iTaskId,  index_activeMems_from,  tn  );
	tmpCfg.uiMaxQNodes  =  100;
	
	memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );		
	memcpy(  &qCfgEx.common,  &tmpCfg,  sizeof(  qCfgEx.common  )  );	
	qCfgEx.pfQElemNewEx  =  mallocMemory;
	qCfgEx.pfQElemNew  =  mymalloc;
	qCfgEx.pfQElemFreeEx  =  freeMemory;
	qCfgEx.pfQElemFree  =  myfree;
	qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_myDRAW_VIDEO_DATA;
	qCfgEx.pfQElemRemove  =  ( PF_qElemRemove  )clean_myDRAW_VIDEO_DATA;

	if  (  initGenericQ(  &qCfgEx,  pTransformVideo->pInDataCacheQ  )  )  goto  errLabel;

	//
	memset(  &tmpCfg,  0,  sizeof(  tmpCfg  )  );
	_sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s-%d-%d-%d"  ),  CONST_mutexNamePrefix_decV_tmpDataQ,  iTaskId,  index_activeMems_from,  tn  );
	_sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s-%d-%d-%d"  ),  CONST_mutexNamePrefix_decV_tmpDataQ,  iTaskId,  index_activeMems_from,  tn  );
	tmpCfg.uiMaxQNodes  =  100;
	
	memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );		
	memcpy(  &qCfgEx.common,  &tmpCfg,  sizeof(  qCfgEx.common  )  );	
	qCfgEx.pfQElemNewEx  =  mallocMemory;
	qCfgEx.pfQElemNew  =  mymalloc;
	qCfgEx.pfQElemFreeEx  =  freeMemory;
	qCfgEx.pfQElemFree  =  myfree;
	qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_myDRAW_VIDEO_DATA;
	qCfgEx.pfQElemRemove  =  ( PF_qElemRemove  )clean_myDRAW_VIDEO_DATA;

	if  (  initGenericQ(  &qCfgEx,  pTransformVideo->pTmpDataQ  )  )  goto  errLabel;
	
	//
	size  =  sizeof(  myDRAW_VIDEO_DATA  );
	pTransformVideo->pCurPkt  =  (  myDRAW_VIDEO_DATA  *  )mymalloc(  size  );
	if  (  !pTransformVideo->pCurPkt  )  goto  errLabel;
	memset(  pTransformVideo->pCurPkt,  0,  size  );

	 /////////////////
	 for  (  ;  !pTransformVideo->bQuit;  )  {
		  
		  //  2010/12/28
		  MACRO_setStep(  pTransformVideo->debugStep,  CONST_threadStep_toWait  );

		  //
		  DWORD  dwEvt  =  MsgWaitForMultipleObjects(							
							 pTransformVideo->q2.cfg.usCnt_hEvents,	//  mycountof(  pPlay->hEvents  ),				// Number of events.
							 pTransformVideo->q2.hEvents,							// Location of handles.
                             FALSE,										// Wait for all?
                             5000,									// How long to wait?
                             0  );										// Any message is an 
																		// event.
		  if  (  dwEvt  ==  WAIT_FAILED  )  goto  errLabel;
	      //
		  dwTickCnt  =  GetTickCount(  );

		  if  (  dwEvt  !=  WAIT_TIMEOUT  )  {
			  dwEvt -= WAIT_OBJECT_0;
			  switch  (  dwEvt  )  {
					  case  0:
						     //  dwTickCnt_lastData  =  dwTickCnt;		//  audio data received
						       //  traceLogA(  (char*)  "mcThreadProcInfo_toShareBmp: event 0."  );
							 break;
					  case  1:
						     traceLogA(  (char*)  "mcThreadProcInfo_toShareBmp: event 1."  );
							 break;
					  default:
						     traceLogA(  (char*)  "unknown event"  );	
		  					 goto  errLabel;
							 break;
			  }
		  }

	
		  for  (  ;  !pTransformVideo->bQuit;  )  {

			   //
			  if  (  getNextVPkt(  pTransformVideo->pCurPkt,  pTransformVideo->pInDataCacheQ,  &pTransformVideo->q2  )  )  break;
			  				
			   //
			   if  (  !pTransform->video.pCurPkt->lPktId_alloc  )  {
				   MACRO_qyAssert(  0,  _T(  "id_pkt is 0"  )  );
			   }
			   //
			   long		old_pktId  =  pTransform->video.pCurPkt->lPktId_alloc;
			   doDecodeVideo(  pTransform,  pMsgBuf  );
			   if  (  pTransform->video.pCurPkt->lPktId_alloc  ==  old_pktId  )  {	//  如果没有处理掉就需要释放
				   clean_myDRAW_VIDEO_DATA(  pTransformVideo->pCurPkt,  _T(  ""  )  );						  
			   }

	
			   continue;
		  }

		  continue;
	 }

	 traceLogA(  (char*)  "mcThreadProc_decVideo will quit"  );

errLabel:

	 //
	 MACRO_setStep(  pTransformVideo->debugStep,  CONST_threadStep_toExit  );

	 //  2009/05/28
	 exitTaskAvFrom_video(  pProcInfo,  pTransform  );
	 
	 //  2014/03/25
	 clean_myDRAW_VIDEO_DATA(  pTransformVideo->pCurPkt,  _T(  "decVideo"  )  );
	 MACRO_safeFree(  pTransformVideo->pCurPkt  );

	 //  2014/03/24
	 if  (  pTransformVideo->pInDataCacheQ  )  {
		 genericQFree(  pTransformVideo->pInDataCacheQ  );  pTransformVideo->pInDataCacheQ  =  NULL;
	 }
	 if  (  pTransformVideo->pTmpDataQ  )  {
		 genericQFree(  pTransformVideo->pTmpDataQ  );  pTransformVideo->pTmpDataQ  =  NULL;
	 }

	 //
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s %d ends."  ),  pTransformVideo->q2.cfg.name,  0  );
	 

	 pTransformVideo->bRunning  =  FALSE;

#if  0
	 //  2012/03/24. 这里退出时通知一下,以便及时清理任务
	 qisApplyForChkingTasks(  CONST_channelType_media  );
#endif

	 //
	 MACRO_setStep(  pTransformVideo->debugStep,  CONST_threadStep_end  );

	 traceLogA(  (char*)  "mcThreadProc_decVideo %S leaves",  pTransformVideo->q2.cfg.name  );
	
	 return  0;

}

