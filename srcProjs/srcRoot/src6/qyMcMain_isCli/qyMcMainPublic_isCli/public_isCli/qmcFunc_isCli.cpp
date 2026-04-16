
#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyWnd.h"
#include	"qmcCmdProc.h"
//#include	"qmcVWall.h"
//#include	"dlgTalkPublic.h"
#include	"qyThread.h"

#include	"ctxQmc.h"
#include	"qyCusResTemp.h"
#include	"qmcCmdProc.h"


//
BOOL  isSame_resObj(  RES_obj_simple  *  p1,  RES_obj_simple  *  p2  )
{
	if  (  p1->uiObjType  ==  p2->uiObjType
		&&  p1->usIndex_obj  ==  p2->usIndex_obj
		&&  p1->usHelp_subIndex  ==  p2->usHelp_subIndex  )
	{
		return  TRUE;
	}

	return  FALSE;
}

//  2016/08/03
BOOL  isSame_qisResObj(  QIS_res_obj  *  p1,  QIS_res_obj  *  p2  )
{
	if  (  p1->idInfo.ui64Id  ==  p2->idInfo.ui64Id  
		&&  isSame_resObj(  &p1->resObj,  &p2->resObj  )  )
	{
		return  TRUE;
	}

	return  FALSE;
}



//
int  getStr_welcomeToUse(  MC_VAR_isCli  *  pProcInfo,  TCHAR  *  tHint,  int  tHintCnt  )
{
	if  (  !pProcInfo  )  return  -1;
	QY_MC  *  pQyMc  =  pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;

	if  (  !tHint  )  return  -1;
	//  
	_sntprintf(  tHint,  tHintCnt,  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_welcomeToUse  )  );
	//
	QM_SHM_CMDS	*	pShmCmds  =  QY_GET_shmCmds(  pProcInfo  );				   
	if  (  pShmCmds  )  {
		if  (  pShmCmds->ucbDaemonDemo  )  {
			TCHAR  *  pT  =  (TCHAR*)_T(  ""  );
			//
			unsigned  short  usLangId  =  pQyMc->env.usLangId;
			//
#ifdef  __DEBUG__
		#if  1
			usLangId  =  0;
			traceLog(  (TCHAR*)_T(  "TEST: usLangId is set to 0"  )  );
		#endif
#endif
			//
			switch  (  usLangId  )  {
					case  CONST_langId_PRC:
						  pT  =  (TCHAR*)_T(  " 试用. www.qycx.com"  );
						  break;
					case  CONST_langId_tw:
						  pT  =  (TCHAR*)_T(  " Trial. www.qycx.com"  );
						  break;
					default:
						    pT  =  (TCHAR*)_T(  " Trial. www.qycx.com"  );
							break;				
			}
			
			_sntprintf(  tHint,  tHintCnt,  (TCHAR*)_T(  "%s%s "  ),  tHint,  pT  );		
		}

		
	}
	
	return  0;
}


//
IM_TASK_RCD  *  msg2TaskRcd(  void  *  pMisCntParam,  MIS_MSG_TASK  *  pMsg,  unsigned  short  usRespCode,  IM_TASK_RCD  *  pRcd  )
{
	int							iErr				=	-1;
	MIS_CNT					*	pMisCnt				=	(  MIS_CNT  *  )pMisCntParam;
	MIS_MSG_routeTalkData	*	pTalkData			=	NULL;
	IM_CONTENTU			*	pContent			=	NULL;
	char						buf[255  +  1]		=	"";
		
	if  (  !pMisCnt  ||  !pMsg  ||  !pRcd  )  return  NULL;

	pTalkData  =  &pMsg->data;
	pContent  =  (  IM_CONTENTU  *  )pTalkData->buf;
	
	if  (  !pTalkData  ||  !pContent  )  goto  errLabel;

	memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );
	//
	lstrcpyn(  pRcd->misServName,  pMisCnt->cfg.misServName,  mycountof(  pRcd->misServName  )  );
	pRcd->idInfo_send.ui64Id  =  pMsg->idInfo_taskSender.ui64Id;
	pRcd->tSendTime  =  pMsg->tStartTime;
	pRcd->uiTranNo  =  pMsg->uiTranNo;
	pRcd->idInfo_recv.ui64Id  =  pMsg->idInfo_taskReceiver.ui64Id;
	//
	pRcd->uiContentType  =  pContent->uiType;	//  2008/05/29
	//
	mytime(  &pRcd->tRecvTime  );
	pRcd->usRespCode  =  usRespCode;
	//
	pRcd->id  =  pMsg->iTaskId;					//  2010/04/23
	pRcd->uiMode  =  0;
	pRcd->uiType  =  pMsg->uiTaskType;
	pRcd->iStatus  =  pMsg->iStatus;

	switch  (  pContent->uiType  )  {
			case  CONST_imCommType_transferFileReq:
				  //
				  lstrcpyn(  pRcd->subject,  pContent->transferFileReq.fileName,  mycountof(  pRcd->subject  )  );
				  lstrcpyn(  pRcd->content,  pContent->transferFileReq.fullFilePath,  mycountof(  pRcd->content  )  );
				  //
				  _sntprintf(  pRcd->propStrs[0],  mycountof(  pRcd->propStrs[0]  ),  (TCHAR*)_T(  "%I64u"  ),  pContent->transferFileReq.ui64FileLen  );

				  break;
			case  CONST_imCommType_rtcCallReq:
				  //
				  ulIp2Str(  pContent->rtcCallReq.ulIp_caller,  buf,  mycountof(  buf  )  );
				  myStr2TChar(  buf,  pRcd->subject,  mycountof(  pRcd->subject  )  );
				  //
				  break;
			case  CONST_imCommType_transferAvInfo:
				  //
				  _sntprintf(  pRcd->subject,  mycountof(  pRcd->subject  ),  _T(  "%d * %d"  ),  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biWidth,  pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biHeight  );
				  //
				  break;
			case  CONST_imCommType_queryCustomerServiceOfficerReq:		//  2011/04/06
				  break;
			case  CONST_imCommType_transferGpsInfo:						//  2012/04/19
				  break;
			default:
					#ifdef  __DEBUG__
							traceLog(  (TCHAR*)_T(  "msg2TaskRcd failed, unknown contentType"  )  );
					#endif
				    goto  errLabel;
					break;
	}


	iErr  =  0;
errLabel:

	return  iErr  ?  NULL  :  pRcd;
}






int calc_conf_param(bool bConference, unsigned  int  uiTaskType, unsigned  short* pusMaxSpeakers, unsigned  short* pusCntLimit_activeMems_from)
{
	if (!bConference) {
		switch (uiTaskType) {
		case  CONST_imTaskType_transferAvInfo:
			//
			*pusMaxSpeakers = 2;
			//
			*pusCntLimit_activeMems_from = *pusMaxSpeakers + MAX_resourceMems_taskAv_p2p;

			//
			//pTc->videoConference.usCntLimit_mems_from = 2;						//  2010/08/31

			break;
		default:
			//
			*pusCntLimit_activeMems_from = 1;

			//
			//pTc->videoConference.usCntLimit_mems_from = 2;					//  2010/09/03

			break;
		}
	}
	else {
		//
		//pTc->videoConference.usMaxSpeakers = pContent_myTask->videoConferenceCfg.usMaxSpeakers;
		//
		*pusCntLimit_activeMems_from = *pusMaxSpeakers + MAX_mosaicMems_taskAv + MAX_resourceMems_taskAv_conf;

	}

	//
	return  0;
}






//
//  这里的参数十分敏感，可以在release和debug各定一套。使性能足够又丢包最少
//  totalPkts是指从开始读取到现在一共顺序到多少个包
//  nPkts_lef是指这一批还剩多少个包。从而能计算出，待播放的是nPkts_left  +  nQNodes
//
bool bPktSkipped(Param_bPktSkipped  *  pParam,  int nWhere, int fps_expected, int nQNodes1, int totalPkts, int nPkts_left,  bool b4k, int* piTotalPkts_lastOk, unsigned  __int64* pnFactor)
{
	//
	if (!pParam) {
		return  false;
	}

#if  0
	if (!b4k) {
		return  false;
	}
#endif 

	//
	bool  bSkip_pkt = false;
	TCHAR  tBuf[128];
	unsigned  __int64 nFactor = 0;

	//
	if (!fps_expected) {
		showInfo_open0(0, 0, _T("bPktSkipped failed, fps_expected is 0"));
		return false;
	}


	//
	if (nPkts_left < 0) {
		int  ii = 0;
	}

	//
	int nQNodes = nQNodes1 + nPkts_left;

	//
	do {

		//
		if (fps_expected < 30) {
			int ii = 0;
			if (1) {
				_sntprintf(tBuf, mycountof(tBuf), _T("Warn: bPktSkipped: fps_expected %d < 30"), fps_expected);
				showInfo_open0(0, 0, tBuf);
			}
		}

		//
		if (fps_expected < 30) {
			//
			break;
		}

		//
		if (piTotalPkts_lastOk) {
			int iDiff = totalPkts - *piTotalPkts_lastOk;
			if (abs(iDiff) > 10) {	//  保证每10个必通过一个
				break;
			}
		}


		//
		unsigned  __int64 n_nQNodes = 4;// 120;
		//
		int min_nQNodes_left = 3;			//  因为这里除了nQNodes外，nPkts还有包。所以，要播放的是nQNodes+npkts,所以nQNodes只要有一个就说明有很多数据包等待播放了
		//
		int n_totalPkts_0 = 4;
		int n_totalPkts_1 = 4;
		int n_totalPkts_2 = 1;
		int n_totalPkts_3 = 1;
		int n_totalPkts_4 = 1;

		//
		int maxVal_0 = 1;
		int maxVal_1 = 2;
		int maxVal_2 = 3;
		int maxVal_3 = 4;
		int maxVal_4 = 50;




		//
		if (fps_expected == 30) {
			n_nQNodes = 4;
			//
			n_totalPkts_0 = 12;
			n_totalPkts_1 = 12;
			n_totalPkts_2 = 4;
			n_totalPkts_3 = 3;
			n_totalPkts_4 = 2;

		}
		else {
			//  60fps
			min_nQNodes_left = 6;

		}

		//
		if (nQNodes <= min_nQNodes_left) {
			//return false;
			break;
		}

		//
		if  (nWhere  ==  CONST_nWhere_vpp  )
		{
			if (fps_expected == 30) {
				n_nQNodes = 4;
				//
				n_totalPkts_0 = 6;
				n_totalPkts_1 = 6;
				n_totalPkts_2 = 4;
				n_totalPkts_3 = 2;
				n_totalPkts_4 = 1;

			}
			else {
			}

		}
		else  if  (  nWhere  ==  CONST_nWhere_playVideo  )
		{
			//  这里似乎不用处理，因为已经有一个消减多余包的机制了
			if  (  !b4k){
				//if (fps_expected == 30) 
				{

					//
					if (pParam->last_mql <= pParam->mql_ok)  break;
					//
					int  n = pParam->last_mql - pParam->mql_ok;
					int  nn = n  / fps_expected;
					//
					if (nn < 1) {    //  多余的包小于1秒
						if (totalPkts % 2) {  //
							bSkip_pkt = true;;

							//
							if (pParam->bDbg) {
								_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("每2个留一个，nn<1. skip"));
							}
							//
							break;
						}
						
						//
							//
						if (pParam->bDbg) {
							_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("每2个留一个，nn<1. ok"));
						}

						//
						break;
					}
					if (nn == 1) {  //  多余的包等于1秒
						//
						if ((totalPkts % 3)) {
							bSkip_pkt = true;
							//
							if (pParam->bDbg) {
								_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("每3个留一个, n==1. skip"));
							}
							//
							break;
						}

						//
						if (pParam->bDbg) {
							_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("每3个留一个. n==1, ok"));
						}

						//
						break;
					}

					//  多余的包多于2秒
					if (n == 2) {
						if ((totalPkts % 4)) {
							bSkip_pkt = true;
							//
							if (pParam->bDbg) {
								_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("每4个留一个。nn %d, skip"), nn);
							}
							//
							break;
						}
						//
						if (pParam->bDbg) {
							_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("每4个留一个， nn==2。ok"));
						}

						//
						break;
					}
					//  多于2秒。
					if (totalPkts % fps_expected) {		//  一秒留一个
						bSkip_pkt = true;

						//
						break;
					}

					//
					break;

				}
				
			}
			else {
				if (fps_expected == 30) {
					//
					if (pParam->last_mql <= pParam->mql_ok)  break;
					//
					int  n = pParam->last_mql - pParam->mql_ok;
					int  nn = fps_expected / n;
					if (nn <= 1) {
						bSkip_pkt = true;
						break;
					}
					if (!(totalPkts % nn)) {
						bSkip_pkt = true;
						break;
					}

					//
					break;
				}
				else {  //  
					//n_nQNodes = 8192  *  8  +  8192  *  8  * 2  *  2  *  2  *  4  *  4  *  4  *  8  *  4  *  1.99;	// 800;	// 480;	// 320;// 256;// 80;	// 16;
					 //n_nQNodes = 8192  *  8  +  8192  *  8  * 2  *  2  *  2  *  4  *  4  *  4  *  8  *  4  *  2.18;	// 800;	// 480;	// 320;// 256;// 80;	// 16;
					 //n_nQNodes = 8192  *  8  +  8192  *  8  * 2  *  2  *  2  *  4  *  4  *  4  *  8  *  4  *  2.3;	// 800;	// 480;	// 320;// 256;// 80;	// 16;
					 //n_nQNodes = 8192  *  8  +  8192  *  8  * 2  *  2  *  2  *  4  *  4  *  4  *  8  *  4  *  5.0;	// 800;	// 480;	// 320;// 256;// 80;	// 16;
					//n_nQNodes = 8192 * 8 + 8192 * 8 * 2 * 2 * 2 * 4 * 4 * 4 * 8 * 4 * 9.0;	// 800;	// 480;	// 320;// 256;// 80;	// 16;						
					n_nQNodes = 8192 * 8 + 8192 * 8 * 2 * 2 * 2 * 4 * 4 * 4 * 8 * 4 * 13.0;	// 800;	// 480;	// 320;// 256;// 80;	// 16;						
					n_nQNodes = 8192;
					//
					//
					n_totalPkts_0 = 9;
					n_totalPkts_1 = 7;
					n_totalPkts_2 = 4;
					n_totalPkts_3 = 3;
					n_totalPkts_4 = 2;

					//
					maxVal_0 = 1;// 1000000000;
					maxVal_1 = 20;	// 3060101100;
					maxVal_2 = 30;	// 6060101100;
					maxVal_3 = 40;	// 8879792300;
					maxVal_4 = 50;	// 70989899800;

				}
			}
		}
		else  if (nWhere == CONST_nWhere_postToDraw) {
			if (fps_expected == 30) {
			}
			else {
				n_nQNodes = 4;// 120;
				//
				n_totalPkts_0 = 4;
				n_totalPkts_1 = 4;
				n_totalPkts_2 = 1;
				n_totalPkts_3 = 1;
				n_totalPkts_4 = 1;

			}
		}
		else  {
		}




		//
#ifndef  __DEBUG__
#endif

		//
		if (!n_nQNodes
			|| !min_nQNodes_left
			|| !n_totalPkts_0
			|| !n_totalPkts_1
			|| !n_totalPkts_2
			|| !n_totalPkts_3
			|| !n_totalPkts_4
			)
		{
			showInfo_open0(0, 0, _T("bPktSkipped: param err"));
			//return false;
			break;
		}


		//
		unsigned  __int64 l64 = nQNodes;
		l64 = l64 * l64 * n_nQNodes;
		nFactor =  l64 / fps_expected;


		//
		if (nFactor) {
			//  
			if (nFactor < maxVal_0) {
				if (!(totalPkts % n_totalPkts_0)) {		//  2
					bSkip_pkt = true;
				}
			}
			else if (nFactor < maxVal_1) {
				if (!(totalPkts % n_totalPkts_1)) {		//  2
					bSkip_pkt = true;
				}
			}
			else  if (nFactor < maxVal_2) {
				if (!(totalPkts % n_totalPkts_2)) {
					bSkip_pkt = true;
				}
			}
			else if (nFactor < maxVal_3) {
				if (!(totalPkts % n_totalPkts_3)) {
					bSkip_pkt = true;
				}
			}
			else if (nFactor < maxVal_4) {
				if (!(totalPkts % n_totalPkts_4)) {
					bSkip_pkt = true;
				}
			}
			else {
				bSkip_pkt = true;
			}



		}

	} while (false);

	//
	if (pnFactor)*pnFactor = nFactor;
	if (!bSkip_pkt) {
		if (piTotalPkts_lastOk) {
			*piTotalPkts_lastOk = totalPkts;
		}
	}


	//
	if (bSkip_pkt) {
		int  ii = 0;
	}

	//
	return  bSkip_pkt;

}



