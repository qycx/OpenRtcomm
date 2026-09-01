


#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	"qyCusResTemp.h"
#include	"myresource.h"
#include	"tmpCeLib.h"

#include	"qmcDynBmp.h"
#include	"qmcVWall.h"
//#include	"DlgDynBmps.h"
#include	"myDb.h"

//  #include	"dlgTalkProc.h"
#include	"funcsForIsCliHelp.h"
#include	"isClihelppublic.h"

 __declspec(  dllexport  )  int  sndRetrieveDynBmpsReq_qmc(  MIS_CNT  *  pMisCnt,  BOOL  bRetrieveAll  )
{
	int				iErr		=	-1;
	if  (  !pMisCnt  )  return  -1;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );	//(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	
	RETRIEVE_DYN_BMPS	req;
	MACRO_prepareForTran(  );
	int					len;

	if  (  !bMeOnline(  (  QY_MC  *  )pProcInfo->pQyMc  )  )  goto  errLabel;
				
	//  pProcInfo->dwTickCnt_toRetrieveSharedDynBmps  =  GetTickCount(  );

	//  2011/10/31. 此标志位为了让mcProcResp_retrieveDynBmps有个初始化的机会
	//pProcInfo->bInited_mcProcResp_retrieveDynBmps  =  FALSE;

	//  2014/04/19
	pMisCnt->retrieveDynBmps.tStartTime  =  tStartTran;
	pMisCnt->retrieveDynBmps.uiTranNo  =  uiTranNo;

	//
	memset(  &req,  0,  sizeof(  req  )  );
	req.uiType  =  CONST_imCommType_retrieveDynBmps;
	if  (  !bRetrieveAll  )  req.tLastRefreshedTime_misServ  =  pProcInfo->tLastRefreshedTime_misServ_sharedDynBmps;				
	//
	len  =  offsetof(  RETRIEVE_DYN_BMPS,  mems  )  +  req.usCnt  *  sizeof(  req.mems[0]  );
	//
	postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_sendVDevReq,  tStartTran,  uiTranNo,  0,  (  char  *  )&req,  len,  NULL,  0,  0,  NULL,  0  ); 

	iErr  =  0;
errLabel:
	return  iErr;
 }



// __declspec(  dllexport  )  int  sndRetrieveDynBmpsReqToMsgr_qmc(  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_dst,  BOOL  bNeedProgress,  unsigned  int  uiObjType,  BOOL  bRetrieveOne,  unsigned  int  *puiTranNo  )
 __declspec(  dllexport  )  int  sndRetrieveDynBmpsReqToMsgr_qmc(  MIS_CNT  *  pMisCnt,  BOOL  bNeedProgress,  unsigned  int  uiObjType,  BOOL  bRetrieveOne,  QY_MESSENGER_ID  *  pIdInfo_imGrp_conf,  BOOL  bAvConsole,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  *puiTranNo  )
{
	int				iErr		=	-1;
	if  (  !pMisCnt  )  return  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	
	RETRIEVE_DYN_BMPS	req;
	MACRO_prepareForTran(  );
	int					len;

	if  (  !bMeOnline(  (  QY_MC  *  )pProcInfo->pQyMc  )  )  goto  errLabel;
	
	//  2014/05/03
	if  (  bNeedProgress  )  {
		startProgress(  &pQyMc->gui.progress,  uiTranNo  );
	}

	//
	memset(  &req,  0,  sizeof(  req  )  );
	req.uiType  =  CONST_imCommType_retrieveDynBmps;
	//  2014/09/04
	if  (  uiObjType  )  {
		req.u.req.uiObjType  =  uiObjType;
	}
	if  (  bRetrieveOne  )  {
		req.u.req.ucbRetrieveOne  =  TRUE;
	}
	//  2014/09/25
	if  (  pIdInfo_imGrp_conf  &&  pIdInfo_imGrp_conf->ui64Id  )  {
		req.conf.idInfo_imGrp_related.ui64Id  =  pIdInfo_imGrp_conf->ui64Id;
	}
	//  2017/06/11
	req.ucbAvConsole  =  bAvConsole;
	//
	len  =  offsetof(  RETRIEVE_DYN_BMPS,  mems  )  +  req.usCnt  *  sizeof(  req.mems[0]  );
	//
	postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_task,  0,   CONST_qyCmd_sendVDevReq,  tStartTran,  uiTranNo,  0,  (  char  *  )&req,  len,  NULL,  pIdInfo_dst,  0,  NULL,  0  ); 

	//
	//if  (  pFuncs->pf_postMsg2Mgr_mc(  pMisCnt,  &route,  CONST_misMsgType_talk,  ucFlg,  CONST_qyCmd_talkTo,  tStartTran,  uiTranNo,  0,  (  char  *  )&content,  lenInBytes,  &pDlgTalkVar->addr.idInfo,  NULL,  0,  pMsgBuf,  TRUE  )  )  goto  errLabel;
	//if  (  postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  CONST_qyCmd_sendMedia,  tStartTran,  uiTranNo,  0,  pMsg->iTaskId,  pMsg->uiTaskType,  (  char  *  )pContent,  lenInBytes,  (  pAddr  ?  &pAddr->idInfo  :  NULL  ),  &pMsg->idInfo_taskSender,  &pMsg->idInfo_taskReceiver,  (  pAddr  ?  &pAddr->idInfo  :  NULL  ),  CONST_channelType_media,  NULL,  FALSE  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	if  (  !iErr  )  {
		if  (  puiTranNo  )  *puiTranNo  =  uiTranNo;
	}
	return  iErr;
 }


