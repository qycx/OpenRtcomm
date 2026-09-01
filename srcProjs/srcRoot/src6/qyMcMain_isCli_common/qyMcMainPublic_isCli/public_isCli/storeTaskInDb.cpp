

#include	"stdafx.h"
#include	<stdio.h>
#include	<stddef.h>
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
//  #include	"myresource.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"

#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	<windows.h>
#include	<windef.h>
#include	<lmcons.h>
#ifndef  __WINCE__
	#include	<lmshare.h>
#endif
#include	<tlhelp32.h>
#include	<iphlpapi.h>

//  #include	"qwmDynFunc.h"

#include	"qmcCmdProc.h"

#include	"tmpCeLib.h"
#include	"qySqlFunc.h"
#include	"qyThread.h"
#include	"isCmdConst.h"
#include	"qyCusResTemp.h"
//
#include	"policyAvParams.h"


#include	"myDb.h"

#include	"isCliCorePublic.h"
#include	"isCliHelpPublic.h"
#include	"qyMessengerHelpPublic.h"
#include	"imgProcessPublic.h"
#include	"isCliD3dPublic.h"
#include	"qisWallsProc.h"
#include	"qmcObjVarPublic.h"
#include	"qmcTaskPublic.h"
#include	"qmcSharePublic.h"
#include	"dlgShareDynBmpsProc.h"
#include	"funcsForIsCliHelp.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliExPublic.h"
#include	"ctxMcThread.h"

//
#include	"qmcVideoTool.h"




#ifdef  __NOTSUPPORT_DB__
 int  tmpHandler_storeTaskInDb(  void  *  p0,  CE_TASK_MEM  *  pRcd,  CE_TASK_MEM  *  pMem  )
{
	int		iErr		=	-1;
	BOOL	bMatched	=	FALSE;

	if  (  pRcd->idInfo_send.ui64Id  )  {
		if  (  pMem->idInfo_send.ui64Id  ==  pRcd->idInfo_send.ui64Id
			&&  pMem->tStartTime  ==  pRcd->tStartTime
			&&  pMem->uiTranNo  ==  pRcd->uiTranNo  )
		{
			bMatched  =  TRUE;
		}
		}
	else  {
		  if  (  pMem->iTaskId  ==  pRcd->iTaskId  )  bMatched  =  TRUE;
	}
	
	if  (  bMatched  )  {	
		pRcd->iTaskId  =  pMem->iTaskId;
		pRcd->iStatus  =  pMem->iStatus;
		iErr  =  1;  goto  errLabel;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}
#endif

 //
 __declspec(  dllexport  )  int  storeTaskInDb(  void  *  pDb,  int  iDbType,  MIS_CNT  *  pMisCnt,  int  iTaskId_suggested,  IM_TASK_RCD  *  pRcd,  BOOL  bInHis  )
{
#ifdef  __NOTSUPPORT_DB__
		MC_VAR_isCli	*	pProcInfo	=	(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
		int				tmpiRet		=	-1;
		CE_TASK_MEM		taskMem;
		
		memset(  &taskMem,  0,  sizeof(  taskMem  )  );
		taskMem.idInfo_send.ui64Id  =  pRcd->idInfo_send.ui64Id;
		taskMem.tStartTime  =  pRcd->tSendTime;
		taskMem.uiTranNo  =  pRcd->uiTranNo;

		tmpiRet  =  qTraverse(  &pProcInfo->memTaskQ,  (  PF_commonHandler  )tmpHandler_storeTaskInDb,  0,  &taskMem  );
		if  (  tmpiRet  <  0  )  return  -1;
		if  (  tmpiRet  )  {
			pRcd->id  =  taskMem.iTaskId;
			pRcd->iStatus  =  taskMem.iStatus;
			return  tmpiRet;
		}

		memset(  &taskMem,  0,  sizeof(  taskMem  )  );
		taskMem.idInfo_send.ui64Id  =  pRcd->idInfo_send.ui64Id;
		taskMem.tStartTime  =  pRcd->tSendTime;
		taskMem.uiTranNo  =  pRcd->uiTranNo;
		taskMem.iTaskId  =  getuiNextTranNo(  0,  0,  0  );
		taskMem.iStatus  =  pRcd->iStatus;

		if  (  qPostMsg(  &taskMem,  sizeof(  taskMem  ),  &pProcInfo->memTaskQ  )  )  return  -1;

		pRcd->id  =  taskMem.iTaskId;

		return  0;
#else
	int						iErr											=	-1;
	QY_MC				*	pQyMc											=	QY_GET_GBUF(  );
	CQySyncObj				syncObj;
	TCHAR				*	pTabName										=	bInHis  ?  CONST_tabName_qyImTaskHisTab  :  CONST_tabName_qyImTaskTab;
	char					idStr_send[CONST_qyMessengerIdStrLen  +  1]		=	"";
	//
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;
	
	if  (  !idInfo2Str(  &pRcd->idInfo_send,  idStr_send,  mycountof(  idStr_send  )  )  )  goto  errLabel;

	if  (  g_dbFuncs.pf_bSelectImTask_storeTaskInDb(  pDb,  iDbType,  pMisCnt,  pRcd,  bInHis  )  ){
		traceLogA(  "storeTaskInDb: "  );
		iErr  =  1;  goto  errLabel;
	}
	//  
	if  (  !bInHis  )  {
		QY_MESSENGER_REGINFO	regInfo;
		MY_REG_DESC				desc;
		//
		if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDbFuncs,  pDb,  iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  pRcd->misServName,  &pRcd->idInfo_send,  0,  NULL,  &regInfo,  NULL,  NULL  )  )  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
		if  (  regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  )  )  goto  errLabel;
		if  (  desc.pSyr[0]  )  _sntprintf(  pRcd->senderDesc,  mycountof(  pRcd->senderDesc  ),  _T(  "%s - %s - %s"  ),  desc.pDw,  desc.pBm,  desc.pSyr  );  
		if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDbFuncs,  pDb,  iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  pRcd->misServName,  &pRcd->idInfo_recv,  0,  NULL,  &regInfo,  NULL,  NULL  )  )  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
		if  (  regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  )  )  goto  errLabel;
		if  (  desc.pSyr[0]  )  _sntprintf(  pRcd->receiverDesc,  mycountof(  pRcd->receiverDesc  ),  _T(  "%s - %s - %s"  ),  desc.pDw,  desc.pBm,  desc.pSyr  );  

		//
		mytime(  &pRcd->firstTime  );
		mytime(  &pRcd->lastTime  );
	}

	if  (  syncObj.sync(  CQyString(  pMisCnt->cfg.mutexNamePrefix_syncTask  )  +  idStr_send  )  )  goto  errLabel;

	if  (  g_dbFuncs.pf_insertImTask_storeTaskInDb(  pDb,  iDbType,  pMisCnt,  iTaskId_suggested,  pRcd,  bInHis  )  )  goto  errLabel;
	if  (  !g_dbFuncs.pf_bSelectImTask_storeTaskInDb(  pDb,  iDbType,  pMisCnt,  pRcd,  bInHis  )  )  goto  errLabel;

	iErr  =  0;

errLabel:

	if  (  iErr  >=  0  )  {
		
	}
	if (iErr < 0) {
#ifdef  __DEBUG__
		traceLog(_T("storeTaskInDb failed"));
#endif
		showInfo_open0(0, _T(""), _T("storeTaskIdDb failed"));
	}

	return  iErr;
#endif
}



