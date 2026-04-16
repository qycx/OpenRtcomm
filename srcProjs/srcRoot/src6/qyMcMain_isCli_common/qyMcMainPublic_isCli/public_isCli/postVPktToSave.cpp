

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"
#include	"tmpCeLib.h"
#ifndef  __WINCE__
//  #include	"DlgVideos.h"
#endif
//  #include	"qmcVideoCapture_isCli.h"
#include	"qmcVideoCapture.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#ifndef  __WINCE__
//#include	"qmcVWall.h"
//  #include	"DlgDynBmps.h"
#endif
#include	"qmcCmdProc.h"

#include	"qySqlFunc.h"
//#include	"qyAvRecordPublic.h"
#include	"saveAvProc_open.h"

#include	"qvcfDefs.h"

#include	<stddef.h>
#include	"qmcCfg.h"




//

//
__declspec(  dllexport  )  int  postAPktToSave(  Param_saveAv  *  pParam,  bool  bResource,  int  index_activeMems_from, unsigned  __int64  ui64Id_from, unsigned  int  tn_openAvDev, unsigned  short wFormatTag,  unsigned  int  uiSampleTimeInMs,  unsigned  int  uiPts,	 char  *  audio,  int  len  )
{
	return  postAvPktToSave(  pParam,bResource,index_activeMems_from,  ui64Id_from,tn_openAvDev,  CONST_vcfMediaType_a, wFormatTag,  uiSampleTimeInMs,  uiPts,	 audio,  len  );
}


//
__declspec(  dllexport  )  int  postVPktToSave(  Param_saveAv  *  pParam,  bool  bResource,  int  index_activeMems_from, unsigned  __int64  ui64Id_from, unsigned  int  tn_openAvDev, int  iFourcc,  unsigned  int  uiSampleTimeInMs,  unsigned  int  uiPts,	 char  *  video,  int  len  )
{
	return  postAvPktToSave(  pParam, bResource, index_activeMems_from,  ui64Id_from,tn_openAvDev, CONST_vcfMediaType_v,  iFourcc,  uiSampleTimeInMs,  uiPts,	 video,  len  );
}



 //
int  postAvPktToSave(Param_saveAv* pParam, bool  bResource, int  index_activeMems_from, unsigned  __int64  ui64Id_from, unsigned  int  tn_openAvDev, unsigned  char  ucMediaType, int  iFourcc, unsigned  int  uiSampleTimeInMs, unsigned  int  uiPts, char* data, int  len)
{
	int  iErr = -1;
	//
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	TCHAR  tWhere[128];  tWhere[0] = 0;


	//
#if  10
	

	//
	SAVE_av_procInfo* pSave = pParam->pSave;// getSaver(index_saver);
	if (!pSave) {
		//
		if (pProcInfo->cfg.debugStatusInfo.bDbgDetail_saveAv) {
			showInfo_open(0, tWhere, 0, _T("postAvPktToSave failed: pSave is null"));
		}
		//
		return  -1;
	}

	//
	if (pProcInfo->cfg.debugStatusInfo.bDbgDetail_saveAv) {
		//
		_sntprintf(tWhere, mycountof(tWhere), _T("save%d,%d,%I64u"), pSave->iType, index_activeMems_from, ui64Id_from);
					
		//		
		showInfo_open(0, tWhere, 0, _T("postAvPktToSave called. l63"));
	}

	//
	if (pSave->iType == CONST_saverType_conf) {		//  会议流受标志位管理，转换流先不管
		
		//
		if (!pProcInfo->cfg.bSaveAv_conf) {
			//
			if (pProcInfo->cfg.debugStatusInfo.bDbgDetail_saveAv) {
				showInfo_open(0, tWhere, 0, _T("postAvPktToSave failed. bSaveAvAv_conf false. l63"));
			}
			//
			return  -1;
		}

		//
		if (!pSave->bRecord_conf && !pSave->bLive) {
			//
			if (pProcInfo->cfg.debugStatusInfo.bDbgDetail_saveAv) {
				showInfo_open(0, tWhere, 0, _T("postAvPktToSave failed. bRecord_conf false, bLive false. l103"));
			}
			//
			return  0;
		}
	}
	if (pSave->iType == CONST_saverType_trans) {

		//
		if (!pProcInfo->cfg.bSaveAv_trans) {
			//
			if (pProcInfo->cfg.debugStatusInfo.bDbgDetail_saveAv) {
				showInfo_open(0, tWhere, 0, _T("postAvPktToSave failed. bSaveAv_trans false. l115"));
			}
			//
			return  -1;
		}

		//
		if (!pSave->bRecord_trans ) {
			//
			if (pProcInfo->cfg.debugStatusInfo.bDbgDetail_saveAv) {
				showInfo_open(0, tWhere, 0, _T("postAvPktToSave failed. bRecord_trans false. l125"));
			}
			//
			return  0;
		}

	}

	//
	memset(&pParam->pSaveAvPktU->common, 0, sizeof(pParam->pSaveAvPktU->common));

	//  2015/05/19
	switch (ucMediaType) {
	case  CONST_vcfMediaType_a: {
		//
		SAVE_audio_pkt* pSap = (SAVE_audio_pkt*)&pParam->pSaveAvPktU->aPkt;
		if (pSap) {
			pSap->uiMediaType = ucMediaType;

			//
			pSap->index_activeMems_from = index_activeMems_from;

			//		
			pSap->idInfo.ui64Id = ui64Id_from;
			pSap->uiTranNo_openAvDev = tn_openAvDev;
			//
			pSap->bAudio = true;
			//
#if  10
			pSap->wFormatTag = (unsigned  short)iFourcc;//wFormatTag;	//  video.tv.vh_stream.dwFourcc;
			//  2015/05/12
			pSap->uiSampleTimeInMs = uiSampleTimeInMs;
			pSap->uiPts = uiPts;

			//		
			if (sizeof(pSap->buf) < len) {
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("postAvPktToSave failed: svp->buf %d < len %d"), sizeof(pSap->buf), len);
				goto  errLabel;
			}

			memcpy(pSap->buf, data, len);
			pSap->uiLen = len;
			len += offsetof(SAVE_audio_pkt, buf);
			q2PostMsgAndTrigger(pSap, len, &pSave->q2, _T("postAvPktToSave.109"));
#endif

#ifdef  __DEBUG__
			traceLog((TCHAR*)_T("postAvPktToSave: aPkt, sap->uiLen %d, len %d "), pSap->uiLen, len);
#endif	
		}

	}

							  break;
	case  CONST_vcfMediaType_v: {
		//
		SAVE_video_pkt* pSvp = (SAVE_video_pkt*)&pParam->pSaveAvPktU->vPkt;
		if (pSvp) {
			pSvp->uiMediaType = ucMediaType;

			//
			pSvp->index_activeMems_from = index_activeMems_from;

			//		
			pSvp->idInfo.ui64Id = ui64Id_from;
			pSvp->uiTranNo_openAvDev = tn_openAvDev;
			//
			pSvp->iFourcc = iFourcc;
			//  2015/05/12
			pSvp->uiSampleTimeInMs = uiSampleTimeInMs;
			pSvp->uiPts = uiPts;

			//		
			if (sizeof(pSvp->buf) < len) {
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("doDecVideoPkt failed: svp->buf %d < len %d"), sizeof(pSvp->buf), len);
				goto  errLabel;
			}

			memcpy(pSvp->buf, data, len);
			pSvp->uiLen = len;
			len += offsetof(SAVE_video_pkt, buf);
			q2PostMsgAndTrigger(pSvp, len, &pSave->q2, _T("postAvPktToSave"));

#ifdef  __DEBUG__
			traceLog((TCHAR*)_T("postAvPktToSave: vPkt, svp->uiLen %d, len %d "), pSvp->uiLen, len);
#endif	
		}

	}
							  break;
	default:
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("unprocessed mediaType"));
#endif
		break;
	}

	//
#endif


	iErr = 0;
errLabel:
	return  iErr;
}



