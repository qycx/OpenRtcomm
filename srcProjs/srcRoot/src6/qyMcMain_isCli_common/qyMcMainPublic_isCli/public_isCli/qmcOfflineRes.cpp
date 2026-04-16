


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



__declspec(  dllexport  )  int  sndProcOfflineResReq_qmc(  MIS_CNT  *  pMisCnt,  BOOL  bNeedProgress, unsigned  int  *puiTranNo  )
{
	int				iErr		=	-1;
	if  (  !pMisCnt  )  return  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	
	PROC_offlineRes_u	req;
	MACRO_prepareForTran(  );
	int					len;

	//
	//if  (  !bMeOnline(  (  QY_MC  *  )pProcInfo->pQyMc  )  )  goto  errLabel;
			

	//  2014/05/03
	if  (  bNeedProgress  )  {
		startProgress(  &pQyMc->gui.progress,  uiTranNo  );
	}


	//  2014/04/19
#if  0
	pMisCnt->retrieveDynBmps.tStartTime  =  tStartTran;
	pMisCnt->retrieveDynBmps.uiTranNo  =  uiTranNo;
#endif

	//
	memset(  &req,  0,  sizeof(  req  )  );
	req.common.uiType  =  CONST_imCommType_procOfflineRes;
	req.common.usSubtype  =  CONST_procOfflineResSubtype_getCfgs;
	//
	len  =  sizeof(  PROC_offlineRes_u  );  //offsetof(  PROC_offline_res,  mems  )  +  req.usCnt  *  sizeof(  req.mems[0]  );
	//
	postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_sendVDevReq,  tStartTran,  uiTranNo,  0,  (  char  *  )&req,  len,  NULL,  0,  0,  NULL,  0  ); 

	iErr  =  0;
errLabel:


	if  (  !iErr  )  {
		if  (  puiTranNo  )  *puiTranNo  =  uiTranNo;
	}


	return  iErr;
 }



//
__declspec(  dllexport  )  int  sndProcOfflineResToMsgr_qmc(  MIS_CNT  *  pMisCnt,  BOOL  bNeedProgress,  void  *  pPROC_offlineRes_u,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  *puiTranNo  )
{
	int				iErr		=	-1;
	if  (  !pMisCnt  )  return  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	PROC_offlineRes_u  *  pInput  =  (  PROC_offlineRes_u  *  )pPROC_offlineRes_u;
	if  (  !pInput  )  return  -1;
	
	PROC_offlineRes_u	req;
	MACRO_prepareForTran(  );
	int					len;

	if  (  !bMeOnline(  (  QY_MC  *  )pProcInfo->pQyMc  )  )  goto  errLabel;
	
	//  2014/05/03
	if  (  bNeedProgress  )  {
		startProgress(  &pQyMc->gui.progress,  uiTranNo  );
	}


	//
	memset(  &req,  0,  sizeof(  req  )  );
	req.common.uiType  =  CONST_imCommType_procOfflineRes;
	req.common.usSubtype  =  pInput->common.usSubtype;
	if  (  req.common.usSubtype  ==  CONST_procOfflineResSubtype_retrieve  )  {
		req.retrieve.req  =  pInput->retrieve.req;
		}
	else  if  (  req.common.usSubtype  ==  CONST_procOfflineResSubtype_download  )  {
			  req.download.idInfo_logicalPeer.ui64Id  =  pInput->download.idInfo_logicalPeer.ui64Id;
			  safeTcsnCpy(  pInput->download.fileName,  req.download.fileName,  mycountof(  req.download.fileName  )  );
			  req.download.idInfo_sender.ui64Id  =  pInput->download.idInfo_sender.ui64Id;  //  2015/08/09
			  req.download.tCreationTime  =  pInput->download.tCreationTime;  //  2015/08/12
			  }
	else  if  (  req.common.usSubtype  ==  CONST_procOfflineResSubtype_del  )  {  //2015/08/07
			  req.del.idInfo_logicalPeer.ui64Id  =  pInput->del.idInfo_logicalPeer.ui64Id;
			  safeTcsnCpy(  pInput->del.fileName,  req.del.fileName,  mycountof(  req.del.fileName  )  );
			  req.del.idInfo_sender.ui64Id  =  pInput->del.idInfo_sender.ui64Id;
			  req.del.tCreationTime  =  pInput->del.tCreationTime;  //  2015/08/12
	}

	//  2014/09/04
	//
	len  =  sizeof(  PROC_offlineRes_u  );  //  offsetof(  RETRIEVE_DYN_BMPS,  mems  )  +  req.usCnt  *  sizeof(  req.mems[0]  );
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
