
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
#include	"ctxQmc.h"
#include <dumpVideo.h>
#include	"qyq2.h"

//

 //
__declspec(dllexport)  int  chkToForceKeyFrame(  QY_TRANSFORM  *  pTransform  )
 {
	 int  iErr  =  -1;
	 MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pTransform->pProcInfo;//QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;
	 	

	 //
	 if  (  !pTransform->pTranInfo_unused  )  return  -1;
	 if  (  !pTransform->pTask
		 ||  !pTransform->pMsgTask  
		 )  		 
	 {			
		 return  -1;
	 }
	 	
	 AV_TRAN_INFO  *  pAvTran_unused  =  (  AV_TRAN_INFO  *  )pTransform->pTranInfo_unused;	 		
	 PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pTransform->pTask;
	 MIS_MSG_TASK  *  pMsgTask  =  (  MIS_MSG_TASK  *  )pTransform->pMsgTask;
	 MIS_CNT		*	pMisCnt	=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
	 if  (  !pMisCnt  )  {
		 goto  errLabel;
	 }

	 //
#if  0
	 //  2015/02/15
	 if  (  pTransform->video.decInfo.cnt_preDec  >  1
		 &&  pTransform->video.decInfo.cnt_preDec  <=  4  )  
	 {
		 iErr  =  0;  goto  errLabel;
	 }
#endif 
	 
	 //
	 DWORD  dwTickCnt  =  GetTickCount(  );
	 if  (  dwTickCnt  -  pTransform->video.decInfo.applyForKeyFrame.dwLastTickCnt_applyForKeyFrame  <  500  )  
	 {
		 iErr  =  0;  goto  errLabel;
	 }
	 pTransform->video.decInfo.applyForKeyFrame.dwLastTickCnt_applyForKeyFrame  =  dwTickCnt;

	 //
	 showInfo_open0(0, 0, _T("chkToForceKeyFrame called"));

	 //
	 unsigned  short	cmdCode  =  CONST_qyCmd_sendMedia;
	 TASK_PROC_REQ		taskProcReq;			
	 int				lenInBytes;
	 memset(  &taskProcReq,  0,  sizeof(  taskProcReq  )  );
	 taskProcReq.uiType  =  CONST_imCommType_taskProcReq;
	 //
	 taskProcReq.usOp  =  CONST_imOp_recv_applyForKeyFrame;
	 //
	 taskProcReq.usTaskProcObjType  =  CONST_usTaskProcObjType_vStream;

	
	 if  (  pTransform->video.idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
		 showInfo_open0(  0,  0,  _T(  "chkToForceKeyFrame failed. vStream not deced is mine."  )  );
		 goto  errLabel;
	 }

	
	 // 
	 QY_MESSENGER_ID	idInfo_dst;
	 if  (  pTask->ucbVideoConferenceStarter  )  {
		 idInfo_dst.ui64Id  =  pTransform->video.idInfo.ui64Id;
		 //
		 taskProcReq.vStream.uiTranNo_openAvDev  =  pTransform->video.tv.uiTranNo_openAvDev;
		 }
	 else  if  (  pTask->ucbVideoConference  )  {
#if  0
			   idInfo_dst.ui64Id  =  pMsgTask->idInfo_taskSender.ui64Id;		
			   //
			   taskProcReq.vStream.uiTranNo_openAvDev  =  pTask->mem0_from.video.uiTranNo_openAvDev;
			   //
			   taskProcReq.vStream.idInfo_src.ui64Id  =  pTransform->video.idInfo.ui64Id;
			   taskProcReq.vStream.uiTranNo_openAvDev_src  =  pTransform->video.uiTranNo_openAvDev;
#endif
			   //  2014/08/28. 暂时不考虑代理模式，所以直接发给视频源
			   idInfo_dst.ui64Id  =  pTransform->video.idInfo.ui64Id;
			   //
			   taskProcReq.vStream.uiTranNo_openAvDev  =  pTransform->video.tv.uiTranNo_openAvDev;
			   }
	 else  {
		   idInfo_dst.ui64Id  =  pTransform->video.idInfo.ui64Id;
		   //
		   taskProcReq.vStream.uiTranNo_openAvDev  =  pTransform->video.tv.uiTranNo_openAvDev;
	 }

	 


	 //		
	 lenInBytes  =  sizeof(  taskProcReq  );					
	 //					
	 MACRO_prepareForTran(  );												

	 //
	 TCHAR  tBuf[128];
	 _sntprintf(tBuf,mycountof(tBuf), _T("chkToForceKeyFrame : dst %I64u, tn %d, nTimes_needKeyFrame %d"), idInfo_dst.ui64Id,  uiTranNo, pTransform->video.decInfo.nTimes_needKeyFrame);
	 showInfo_open(0, 0, 0, tBuf);



	 //										 
	 if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  cmdCode,  tStartTran,  uiTranNo,  0,  0,  0,  (  char  *  )&taskProcReq,  lenInBytes,  &pMsgTask->addr_logicalPeer.idInfo,  NULL,  NULL,  &idInfo_dst,  0,  NULL,  FALSE  )  )  goto  errLabel;
				
	 iErr  =  0;

errLabel:
				
	 return  iErr;

 }





//
//
 __declspec(dllexport)  int  dec_parseEncVPkt_i(unsigned  int  uiTransformType, void* pParent_transform, void* pPkt_myDRAW_VIDEO_DATA, long* p_old_lPktId_alloc, unsigned  char** ppInput, unsigned  int* puiSize, unsigned  int* puiSampleTimeInMs, unsigned  int* puiPts, SMPL_bsRead_param* pParam)
 {
	 int		iErr = -1;
	 MC_VAR_common* pProcInfo = NULL;	//  QY_GET_procInfo_isCli(  );
	 TCHAR	tBuf[256] = _T("");


	 //  myDRAW_VIDEO_DATA  *  pPkt  =  pTransform->video.pCurPkt;
	 myDRAW_VIDEO_DATA* pPkt = (myDRAW_VIDEO_DATA*)pPkt_myDRAW_VIDEO_DATA;

	 //  检查一下。每个包都只能处理一次，否则，容易死循环
	 if (!p_old_lPktId_alloc)  return  -1;
	 if (!pPkt->lPktId_alloc) {
		 showInfo_open0(0, 0, _T("failed: lPktId_alloc 0"));
		 return  -1;
	 }
	 if (pPkt->lPktId_alloc == *p_old_lPktId_alloc) {
		 showInfo_open0(0, 0, _T("failed: lPkdId_alloc==old"));
		 return  -1;
	 }
	 *p_old_lPktId_alloc = pPkt->lPktId_alloc;

	 //
	 if (uiTransformType != CONST_uiTransformType_dec) {
		 MACRO_qyAssert(0, _T("dec_parseEncVPkt failed, transformType err"));
		 return  -1;
	 }
	 QY_TRANSFORM* pTransform = (QY_TRANSFORM*)pParent_transform;
	 pProcInfo = (MC_VAR_common*)pTransform->pProcInfo;
	 if (!pProcInfo)  return  -1;

	 QMC_cfg* pQmcCfg = (QMC_cfg*)pProcInfo->get_qmc_cfg();
	 if (!pQmcCfg)  return  -1;

	 //  2015/06/18
	 QMC_status* pQmcStatus = (QMC_status*)pProcInfo->get_qmc_status();
	 if (!pQmcStatus)  return  -1;

	 //
	 //
	 if (pPkt->head.uiLen > pPkt->memory.uiBufSize
		 || pPkt->uiSize_dec + pPkt->uiOffset_enc + pPkt->uiLen_enc > pPkt->head.uiLen)
	 {
#ifdef  __DEBUG__
		 traceLog(_T("doDecVideo: uiSize_dec or uiLen error"));
#endif
		 return  -1;
	 }
	 char* encData = pPkt->memory.m_pBuf + pPkt->uiSize_dec + pPkt->uiOffset_enc;


	 //
#ifdef  __DEBUG__
	 {
		 int  iFourcc_enc = pTransform->video.tv.vh_stream.dwFourcc;
		 if (iFourcc_enc == CONST_fourcc_HEVC) {

			 //
			 int nalType = M_nalType_h265(encData);

			 //
#ifdef  __DEBUG__
#if 10
			 _sntprintf(tBuf, mycountof(tBuf), _T("dec_parseEncVPkt_i: nalType %d, pts %d, st %d, len %d"), nalType, pPkt->head.uiPts, pPkt->head.uiSampleTimeInMs,  pPkt->uiLen_enc);
			 showInfo_open0(0, 0, tBuf);
#endif
#endif
		 }
		 //
	 }
#endif 

	 //  2014/04/22	
	 if (uiTransformType == CONST_uiTransformType_dec) {
		 QY_TRANSFORM* pTransform = (QY_TRANSFORM*)pParent_transform;

		 //			
		 if (pTransform->video.decInfo.iNextIndex_preDec >= mycountof(pTransform->video.decInfo.iSampleTimeInMs_preDec_array)) {
			 qyShowInfo1(CONST_qyShowType_qwmComm, 0, "", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("dec_parseEncVPkt_i failed, iNextIndex_preDec too large"));
			 goto  errLabel;
		 }

		 //
		 int  iNextIndex_preDec = pTransform->video.decInfo.iNextIndex_preDec;
		 int  iLastIndex_preDec = 0;
		 if (!iNextIndex_preDec)  iLastIndex_preDec = mycountof(pTransform->video.decInfo.iSampleTimeInMs_preDec_array) - 1;
		 else  iLastIndex_preDec = iNextIndex_preDec - 1;

		 //
		 if (pPkt->head.usElapseInMs_fromLastPkt) {
			 int real_iSampleTimeInMs = pPkt->head.usElapseInMs_fromLastPkt + pTransform->video.decInfo.iSampleTimeInMs_lastPkt;
			 if (0 != pPkt->head.uiSampleTimeInMs) {
				 if (real_iSampleTimeInMs != pPkt->head.uiSampleTimeInMs) {
					 traceLog((TCHAR*)_T("dec_parseEncVPkt_i: real_iSampleTimeInMs != pMem.iSampleTimeInMs"));
				 }
			 }
			 pPkt->head.uiSampleTimeInMs = real_iSampleTimeInMs;
		 }
		 //
		 pTransform->video.decInfo.iSampleTimeInMs_lastPkt = pPkt->head.uiSampleTimeInMs;


		 //  2015/05/12
		 if (!pPkt->head.uiSampleTimeInMs) {
			 showInfo_open0(0, 0, _T("Warning: dec_parseEncVPkt_i: uiSampleTimeInMS is 0"));
		 }

		 //
#if  0
		 if (pPkt->head.uiSampleTimeInMs
			 && pTransform->video.decInfo.iSampleTimeInMs_preDec_array[iLastIndex_preDec] != pPkt->head.uiSampleTimeInMs)			 
#endif 
		 {		//  很多包是数据控制包，不是图像数据，时间戳和图像包一样，所以不能入队列。2014/07/11
			 //				  

			 //  2015/06/18
			 if (pTransform->video.bUseDecTool) {
				 if (pPkt->head.uiPts) {
					 if (pTransform->video.pts.uiPts_lastRecvd) {
						 if (pPkt->head.uiPts != pTransform->video.pts.uiPts_lastRecvd + 1) {
							 pTransform->transPtsInfo.v.uiCnt_ptsErr++;
							 int  iDiff = pPkt->head.uiPts - (pTransform->video.pts.uiPts_lastRecvd + 1);
							 if (iDiff > 0) {
								 pTransform->transPtsInfo.v.uiCnt_notRecvd_pts += iDiff;
							 }
						 }
					 }
					 //
					 DWORD  dwTickCnt = GetTickCount();
					 int  iElapseInMs = dwTickCnt - pTransform->transPtsInfo.v.dwTickCnt_calc_start;
					 if (iElapseInMs > 1000) {
						 //
						 if (pQmcCfg->pDebugStatusInfo->ucbShowPreDecV_pts) {
							 TCHAR  tBuf[128];
							 _sntprintf(tBuf, mycountof(tBuf), _T("ptsErr: cnt %d/s. taskId %d"), pTransform->transPtsInfo.v.uiCnt_ptsErr, pTransform->iTaskId);
							 showInfo_open0(0, 0, tBuf);
						 }
						 //
						 if (pTransform->transPtsInfo.v.uiCnt_ptsErr) {  //  应该报警，													 
							 //  在procInfo里加一个
							 InterlockedExchangeAdd(&pQmcStatus->ptsStat.transPtsInfo_sum.v.uiCnt_ptsErr, pTransform->transPtsInfo.v.uiCnt_ptsErr);
							 InterlockedExchangeAdd(&pQmcStatus->ptsStat.transPtsInfo_sum.v.uiCnt_notRecvd_pts, pTransform->transPtsInfo.v.uiCnt_notRecvd_pts);
						 }

						 //
						 memset(&pTransform->transPtsInfo.v, 0, sizeof(pTransform->transPtsInfo.v));
						 pTransform->transPtsInfo.v.dwTickCnt_calc_start = dwTickCnt;
					 }
				 }
			 }

			 //  
			 //  注意这里，使用decTool的时候，这里不校验pts, 让dvt来校验. 2015/02/09
			 
			 //
			 bool  bPtsErr;  bPtsErr = false;
			 
			 //
			 if (!pTransform->video.bUseDecTool) {

				 //  2015/01/15
				 if (pPkt->head.uiPts) {
					 if (!pTransform->video.pts.uiPts_lastRecvd) {
						 pTransform->video.pts.uiPts_first = pPkt->head.uiPts;
						 pTransform->video.pts.dwTickCnt_start = GetTickCount();
					 }
					 else {
						 if (pPkt->head.uiPts != pTransform->video.pts.uiPts_lastRecvd + 1) {
							 //
							 int nErr = pPkt->head.uiPts - (pTransform->video.pts.uiPts_lastRecvd + 1);
							 pQmcStatus->pktsStat.ui64_v_pkts_err += abs(nErr);
							 //
							 _sntprintf(tBuf, mycountof(tBuf), _T("%I64u,%d: dec_parseEncVPkt_i failed: pts err. pkt.pts %d, last %d"), pTransform->video.idInfo.ui64Id, pTransform->video.tv.uiTranNo_openAvDev, pPkt->head.uiPts, pTransform->video.pts.uiPts_lastRecvd);
							 showInfo_open0(0, 0, tBuf);
							 //
							 bPtsErr = true;
						 }
						 //
					 }
					 //
					 pQmcStatus->pktsStat.ui64_v_pkts_ok++;
					 //
					 //pTransform->video.decInfo.pts.uiPts_lastRecvd  =  pPkt->head.uiPts;		
				 }
			 }
			 //  2015/06/18
			 if (pPkt->head.uiPts) {
				 pTransform->video.pts.uiPts_lastRecvd = pPkt->head.uiPts;
			 }

			 //
			 if (bPtsErr) {
				 //
				 traceLog((TCHAR*)_T("dec_parseEncVPkt_i failed: bPtsErr true"));
				 //
				 goto  errLabel;
			 }

			 //
			 //
			 int  d_pre = 0;
			 int  d_pretrans = 0;
			 int  e_pretrans = 0;
			 //
			 if (pQmcCfg && pQmcCfg->pDebugStatusInfo->ucbShowPreDecVStatus) {
				 //
#ifdef  __DEBUG__
				 traceLog(_T("dec_parseEncVPkt_i: pkt.sm %dms. iDiff %dms"), pPkt->head.uiSampleTimeInMs, pPkt->head.uiSampleTimeInMs - pTransform->video.decInfo.iSampleTimeInMs_preDec_array[iLastIndex_preDec]);
#endif
				 //  2015/02/24
				 d_pre = pPkt->head.uiSampleTimeInMs - pTransform->video.decInfo.iSampleTimeInMs_preDec_array[iLastIndex_preDec];
				 d_pretrans = pPkt->debugInfo.dwTickCnt_doPretrans - pTransform->video.decInfo.dwTickCnt_doPretrans[iLastIndex_preDec];
				 e_pretrans = GetTickCount() - pPkt->debugInfo.dwTickCnt_doPretrans;
				 //
				 _sntprintf(tBuf, mycountof(tBuf), _T("dec_parseEncVPkt_i: %I64u,%d: pts %d. sm %dms. d_pre %dms, i_pre %d. lDiff_pre_post %d. d_preTrans %d"),
					 pTransform->video.idInfo.ui64Id, pTransform->video.tv.uiTranNo_openAvDev,
					 pPkt->head.uiPts, pPkt->head.uiSampleTimeInMs, d_pre, iNextIndex_preDec, pTransform->video.decInfo.lDiff_pre_post, d_pretrans);
			 }
			 pTransform->video.decInfo.iSampleTimeInMs_preDec_array[iNextIndex_preDec] = pPkt->head.uiSampleTimeInMs;
			 pTransform->video.decInfo.uiPts_preDec_array[iNextIndex_preDec] = pPkt->head.uiPts;	//  2015/02/19
			 //  2015/02/24
			 pTransform->video.decInfo.dwTickCnt_doPretrans[iNextIndex_preDec] = pPkt->debugInfo.dwTickCnt_doPretrans;
			 //
			 {
				 CQySyncObj	syncObj;
				 TCHAR		tName[128];
				 _sntprintf(tName, mycountof(tName), _T("%s%d"), CONST_mutexName_syncIndex_dec, pTransform->iTaskId);
				 if (syncObj.sync(tName))  goto  errLabel;

				 pTransform->video.decInfo.iNextIndex_preDec++;
				 if (pTransform->video.decInfo.iNextIndex_preDec >= mycountof(pTransform->video.decInfo.iSampleTimeInMs_preDec_array)) {
					 pTransform->video.decInfo.iNextIndex_preDec = pTransform->video.decInfo.iNextIndex_preDec % mycountof(pTransform->video.decInfo.iSampleTimeInMs_preDec_array);
				 }
				 if (pTransform->video.decInfo.lDiff_pre_post < mycountof(pTransform->video.decInfo.iSampleTimeInMs_preDec_array)) {
					 pTransform->video.decInfo.lDiff_pre_post++;
				 }
			 }
			 //
			 pTransform->video.decInfo.cnt_preDec++;
			 //
			 if (pQmcCfg && pQmcCfg->pDebugStatusInfo->ucbShowPreDecVStatus) {  //  2015/02/24
				 _sntprintf(tBuf, mycountof(tBuf), _T("%s, cnt_pre %d, e_pretrans %d. transQ %d+%d"), tBuf, pTransform->video.decInfo.cnt_preDec, e_pretrans, pTransform->video.q2.qs[0].uiQNodes, pTransform->video.q2.qs[1].uiQNodes);
				 qyShowInfo1(CONST_qyShowType_qwmComm, 0, "", pProcInfo->who_showInfo, 0, _T("preDec"), _T(""), _T("%s"), tBuf);
			 }
		 }

	 }


	 //
	 myDRAW_VIDEO_DATA* pPkt_dec = pPkt;

	 //
	 int  index_pMems_from = pPkt->decInfo.index_pMems_from;

	 //
	 if (uiTransformType == CONST_uiTransformType_dec) {
		 QY_TRANSFORM* pTransform = (QY_TRANSFORM*)pParent_transform;

		 PROC_TASK_AV* pTask = (PROC_TASK_AV*)pTransform->pTask;
		 if (!pTask)  goto  errLabel;

		 int  index_activeMems_from = pTransform->index_activeMems_from;

		 //
		 QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex((CCtxQmc*)pProcInfo, pTask->iIndex_taskInfo);
		 if (!pTaskInfo)  goto  errLabel;
		 if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  goto  errLabel;
		 QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;

		 //
		 if (index_activeMems_from < 0 || index_activeMems_from >= pTc->videoConference.usCntLimit_activeMems_from)  goto  errLabel;
		 DLG_TALK_videoConferenceActiveMemFrom* pActiveMem_from = &pTc->videoConference.activeMems_from[index_activeMems_from];


		 //
		 if (pTransform->video.ucbInited) {
			 if (pTransform->video.index_activeMems_from != index_activeMems_from
				 || pTransform->video.idInfo.ui64Id != pActiveMem_from->avStream.idInfo.ui64Id
				 || pTransform->video.tv.uiTranNo_openAvDev != pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev
				 || pTransform->video.status.ucbDecFailed											//  2012/03/19
				 )
			 {
				 //  2014/04/07
				 pTransform->video.status.ucbNeedReinited = TRUE;
				 //
				 qyShowInfo1(CONST_qyShowType_qwmComm, 0, "", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("dec_parseEncVPkt_i failed: trans.active_from %d,idInfo %I64u, tn %d, decFailed %d != %d,%I64u,%d,%d"),
					 pTransform->video.index_activeMems_from, pTransform->video.idInfo.ui64Id, pTransform->video.tv.uiTranNo_openAvDev, (int)pTransform->video.status.ucbDecFailed,
					 index_pMems_from, pActiveMem_from->avStream.idInfo.ui64Id, pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev, 0);
				 goto  errLabel;
			 }

		 }


		 //
		 int  iFourcc_enc = pTransform->video.tv.vh_stream.dwFourcc;
		 if (iFourcc_enc == CONST_fourcc_HEVC) {

			 //
			 int nalType = M_nalType_h265(encData);

			 //
#ifdef  __DEBUG__
#if 0
			 _sntprintf(tBuf, mycountof(tBuf), _T("dec_parseEncVPkt_i: nalType %d, pts %d, len %d"), nalType, pPkt->head.uiPts, pPkt->uiLen_enc);
			 showInfo_open0(0, 0, tBuf);
#endif
#endif

			 //
			 if (!pTransform->video.decInfo.bGot_keyFrame)
			 {
				 unsigned  char  ucbKeyFrame = false;
				 //
				 switch (nalType) {
				 case  NAL_IDR_W_RADL:
				 case  NAL_IDR_N_LP:
					 ucbKeyFrame = true;
					 break;
				 case  NAL_VPS:
					 ucbKeyFrame = true;
					 break;
				 default:
				 {
					 int ii = 0;
				 }
				 break;
				 }
				 //
				 if (!ucbKeyFrame)
				 {
					 //
					 int  nQNodes = getQ2Nodes(&pTransform->video.q2);

					 //
					 _sntprintf(tBuf, mycountof(tBuf), _T("dec_parseEncVPkt_i failed, %I64u, %d, not a keyFrame: need a keyFrame first. nQNodes %d"),
						 pTransform->video.idInfo.ui64Id, pTransform->video.tv.uiTranNo_openAvDev,  nQNodes );
					 showInfo_open0(0, 0, tBuf);
					 //
					 chkToForceKeyFrame(pTransform);
					 //
					 iErr = CONST_qyRet_needKeyFrameFirst;
					 //
					 goto errLabel;
				 }
				 pTransform->video.decInfo.bGot_keyFrame = true;
			 }
		 }



		 //  2014/12/06
		 DWORD  dwTickCnt = myGetTickCount(mynull);
		 BOOL  bNeedChk = FALSE;
		 if (!pTransform->video.decInfo.cnt_postDec)  bNeedChk = TRUE;
		 else {
			 if (dwTickCnt < pTransform->video.decInfo.dwLastTickCnt_postDec + 2000) {
				 pTransform->video.decInfo.nTimes_needKeyFrame = 0;
			 }
			 else {
				 pTransform->video.decInfo.nTimes_needKeyFrame++;
				 if (pTransform->video.decInfo.nTimes_needKeyFrame > 20) {
					 bNeedChk = TRUE;
				 }
			 }
		 }



		 //  2014/08/26
		 if (bNeedChk) {

			 //
			 chkToForceKeyFrame(pTransform);

			 //
#ifdef  __DEBUG__
		//  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dec_parseEncVPkt_i : cnt_preDec %d, cnt_postDec %d"  ),  pTransform->video.decInfo.cnt_preDec,  pTransform->video.decInfo.cnt_postDec  );
#endif


		 }

		 //  2014/
#ifdef  __DEBUG__
		//			
		 if (pQmcCfg->pDebugStatusInfo->ucb__Dump_h265_dec__) {
			 char* video = encData;
			 int  len = pPkt->uiLen_enc;
			 dumpVideo(NULL, _T(CONST_fn_dump_h265_dec), video, len, mynull);
		 }
		 //						
#endif

//  這裏要計算解碼的包數. 2026/08/09
		 if (1) {
			 //
			 //compressor.common.pVideoQ2 = &pTransformVideo->q2;
			 //
			 int  nQNodes = getQ2Nodes(&pTransform->video.q2);
			 //
			 if (nQNodes) {
				 _sntprintf(tBuf, mycountof(tBuf), _T("dec_parseEncVPkt_i: nQNodes %d"), nQNodes);
				 showInfo_open(0, 0, 0, tBuf);
			 }
		 }

	 }


	 //
	 *ppInput = (unsigned  char*)encData;
	 *puiSize = pPkt->uiLen_enc;
	 //  2015/01/28
	 if (puiSampleTimeInMs) {
		 *puiSampleTimeInMs = pPkt->head.uiSampleTimeInMs;
	 }
	 //  2015/02/09
	 if (puiPts) {
		 *puiPts = pPkt->head.uiPts;
	 }
	 //  2015/02/24
	 if (pParam) {
		 pParam->dwTickCnt_doPretrans = pPkt->debugInfo.dwTickCnt_doPretrans;
	 }


	 iErr = 0;
 errLabel:

	 return  iErr;
 }

