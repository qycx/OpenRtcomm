

#include	"stdafx.h"
#include	<stdio.h>
#include	<stddef.h>
#include	<time.h>

#include	"qyMcMainCommon.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture_isCli.h"
#include	"tmpCeLib.h"




 int  showDebugInfo(  MC_VAR_isCli  *  pProcInfo,  LPCTSTR  hint,  MIS_MSG_INPUT  *  pMsgInput  )
{
	char	timeBuf[CONST_qyTimeLen  +  1];

	if  (  !hint  )  hint  =  _T(  ""  );

	 	if  (  pMsgInput->data.route.debugInfo.tTime_start  )  {

			pMsgInput->data.route.debugInfo.usElapsed_resp_end  =  (  unsigned  short  )(  GetTickCount(  )  -  pMsgInput->data.route.debugInfo.dwTickCnt_resp_recved  );
		
			time_t	tNow;	mytime(  &tNow  );
			getTimelStr(  (  time_t  )pMsgInput->data.route.debugInfo.tTime_start,  timeBuf,  mycountof(  timeBuf  )  );
			qyShowInfo1(  CONST_qyShowType_qwmComm,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  
				_T(  "%s 0: tn %d, start %s, toSend %u"  ), 
				hint,
				pMsgInput->uiTranNo,
				CQyString(  timeBuf  +  8  ),
				pMsgInput->data.route.debugInfo.usElapsed_toSend  );

			getTimelStr(  (  time_t  )pMsgInput->data.route.debugInfo.req.tTime_serv_startToRecv,  timeBuf,  mycountof(  timeBuf  )  );
			qyShowInfo1(  CONST_qyShowType_qwmComm,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  
				_T(  "%s 1:  s_t_startToRecv %s, s_toProcess %u, s_toFindDst %u, s_toBeSwitched %u, s_toSend %u"  ), 
				hint,
				CQyString(  timeBuf  +  8  ),
				pMsgInput->data.route.debugInfo.req.usElapsed_serv_startToProcess,
				pMsgInput->data.route.debugInfo.req.usElapsed_serv_toFindDst,
				pMsgInput->data.route.debugInfo.req.usElapsed_serv_toBeSwitched,
				pMsgInput->data.route.debugInfo.req.usElapsed_serv_toSend  );

			getTimelStr(  (  time_t  )pMsgInput->data.route.debugInfo.tTime_peer_recved,  timeBuf,  mycountof(  timeBuf  )  );
			qyShowInfo1(  CONST_qyShowType_qwmComm,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  
				_T(  "%s 2:  p_t_recved %s, p_resp_toSend %u"  ), 
				hint,
				CQyString(  timeBuf  +  8  ),
				pMsgInput->data.route.debugInfo.usElapsed_peer_resp_toSend  );

			getTimelStr(  (  time_t  )pMsgInput->data.route.debugInfo.resp.tTime_serv_startToRecv,  timeBuf,  mycountof(  timeBuf  )  );
			qyShowInfo1(  CONST_qyShowType_qwmComm,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  
				_T(  "%s 3: s_r_t_startToRecv %s, s_r_toProcess %u, s_r_toFindDst %u, s_r_toBeSwitched %u, s_r_toSend %u"  ),
				hint,
				CQyString(  timeBuf  +  8  ),
				pMsgInput->data.route.debugInfo.resp.usElapsed_serv_startToProcess,
				pMsgInput->data.route.debugInfo.resp.usElapsed_serv_toFindDst,
				pMsgInput->data.route.debugInfo.resp.usElapsed_serv_toBeSwitched,
				pMsgInput->data.route.debugInfo.resp.usElapsed_serv_toSend  );
			
			getTimelStr(  tNow,  timeBuf,  mycountof(  timeBuf  )  );
			qyShowInfo1(  CONST_qyShowType_qwmComm,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  
				_T(  "%s 4: resp_recved %s, resp_end %u"  ),
				hint,
				CQyString(  timeBuf  +  8  ),
				pMsgInput->data.route.debugInfo.usElapsed_resp_end  );

				
	}

	 return  0;
 }











 



/*
 int  procTaskAvResp_orgReqMissed(  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_INPUT  *  pMsgInput,  IM_SIMPLE_RESP  *  pResp,  AV_TRAN_INFO  *  pTranInfo,  PROC_TASK_AV  *  pTask  )
{															 
	int					iErr									=		-1;
	char				timeBuf[32]								=		"";
	TCHAR				tHintBuf[255  +  1]						=		_T(  "TaskAvResp_orgReqMissed:"  );
	//
	time_t				tSelectTime								=		0;
	int					i;
	unsigned  short		usDelay									=		0;

	QY_SHARED_OBJ		*	pSharedObj							=		getSharedObjByIndex(  pProcInfo,  pTask->iIndex_sharedObj  );		//  这里应该用index来获取
	if  (  !pSharedObj  )  return  -1;
	
	//  pTask->hWnd_task


	iErr  =  0;
errLabel:

	if  (  tHintBuf[0]  )  	qyShowInfo1(  CONST_qyShowType_qwmComm,  &pMsgInput->uiStep,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tHintBuf  );

	return   iErr;

 }
*/


