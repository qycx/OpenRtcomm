
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
//#include	"qmcVideoTool.h"


//
void  postAPktToRender(  void  *  pQY_TRANSFORM,  void  *  pmyPLAY_AUDIO_DATA,  BOOL  *  unused_pbPktRedirected  )
{
	int				iErr		=	-1;
	QY_TRANSFORM  *  pTransform  =  (  QY_TRANSFORM  *  )pQY_TRANSFORM;
	myPLAY_AUDIO_DATA  *  pPkt  =  (  myPLAY_AUDIO_DATA  *  )pmyPLAY_AUDIO_DATA;
	//MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pTransform->pProcInfo;//QY_GET_procInfo_isCli(  );
	MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)pTransform->pProcInfo;
	if  (  !pProcInfo  )  return;
		
	
	//
	if (pTransform->pCapDev_rtsp) {

		CAP_dev_rtspCommon* pRtsp = (CAP_dev_rtspCommon*)pTransform->pCapDev_rtsp;

		QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, pRtsp->iIndex_sharedObj);
		if (!pSharedObj)  goto  errLabel;

		CAP_procInfo_audioCommon* pVc = NULL;

		pVc = (CAP_procInfo_audioCommon*)getCapAudioBySth(pProcInfo, pSharedObj->iIndex_capAudio, 0);

		//CAP_procInfo_audioU* pVc = (CAP_procInfo_audioU*)getCapAudioBySth(pProcInfo, pSharedObj->iIndex_capBmp, 0);
		if (!pVc)  goto  errLabel;
		TRANSINFO_stream* pTransInfo = (TRANSINFO_stream*)pSharedObj->pTransInfo_stream;
		if (!pTransInfo)  goto  errLabel;
		if (!pTransInfo->myTask.pTransforms)  goto  errLabel;

		//pInDataCacheQ

		if (!pVc->appThread.bQInited) {
			showInfo_open0(0, 0, _T("postAPktToRender failed: app.q not inited"));
			goto  errLabel;
		}

		//if  (  pRtsp->uiType  ==  CONST_rtspType_decV  )  {

		CQyMalloc				mallocObj;

		myPLAY_AUDIO_DATA* p;
		int							len;

		len = sizeof(myPLAY_AUDIO_DATA);


		myPLAY_AUDIO_DATA	tmp_myPLAY_AUDIO_DATA;
		p = &tmp_myPLAY_AUDIO_DATA;	//  (  myPLAY_AUDIO_DATA  *  )m_var.pBuf;
		if (!p)  goto  errLabel;
		memset(p, 0, len);

		//  2016/12/10
		//unsigned  int  uiSize_dec = pPkt->head.uiLen;
		unsigned  int  uiSize_dec = pProcInfo->cfg.uiBufSize_myPlayAudioData;

		//  2011/12/06		
		unsigned  int  uiSize_enc = 0;	//  sizeof(  TRANSFER_AUDIO_DATA  );

		//
		//  p->head.uiLen  =  dwNumBytes;
		
		//
		p->head.uiSampleTimeInMs = pPkt->head.uiSampleTimeInMs;
		//  
		if (!mallocObj.mallocf(uiSize_dec))  goto  errLabel;
		if (mallocObj.get(&p->memory))  goto  errLabel;
		//memcpy(  p->memory.m_pBuf,  pbInput1,  p->head.uiLen  );
		p->memory.uiBufSize = uiSize_dec;
		memcpy(p->memory.m_pBuf, pPkt->memory.m_pBuf, pPkt->head.uiLen);	//  2016/12/14

		p->head.uiLen = pPkt->head.uiLen;	//  2016/12/10
		p->uiSize_dec = pPkt->head.uiLen;					//  2016/12/10


		if (!q2PostMsgAndTrigger(p, len, &pVc->appThread.q2, _T("postAPktToRender 1"))) {
			*unused_pbPktRedirected = TRUE;
			mallocObj.detach();
		}

	}
	else  {		
		  //  
		  //  pProcInfo->drawVideoData(  pPkt,  1  *  sizeof(  pPkt[0]  ),  &bPktsRedirected,  pTransform  );		 				
		  pProcInfo->playAudioData(  pPkt->head.uiSampleTimeInMs,  pPkt->head.uiPts,  (  BYTE  *  )pPkt->memory.m_pBuf,  pPkt->uiSize_dec,  pTransform->iIndex_player  );

	}

	//
	iErr  =  0;

errLabel:
			  


			  return;

}



