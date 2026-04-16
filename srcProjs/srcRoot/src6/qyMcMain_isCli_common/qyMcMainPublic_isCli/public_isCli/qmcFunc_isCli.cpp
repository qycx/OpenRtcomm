
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
#if 0
bool  ii_is4k(int iW, int iH)
{
	if (iW * iH > (1920 + 200) * (1080 + 200)) {
		return  true;
	}
	return false;
}
#endif 






