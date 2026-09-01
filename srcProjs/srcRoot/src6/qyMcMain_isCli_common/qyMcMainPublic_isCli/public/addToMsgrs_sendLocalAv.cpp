
#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>


#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"

//#include	"qmcVideoCapture_isCli.h"
//
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

#include	"qmcTaskPublic.h"

#include	"qmcCfg.h"

//
typedef  struct  __param_addToMsgRoute_t {
				 //
				 bool  bAudio;

}		 Param_addToMsgRoute;


//
int addToMsgRoute(Param_addToMsgRoute  *  pParam,  __int64  ui64Id, MSG_ROUTE* pRoute)
{
	int  iErr = -1;
	TCHAR  tBuf[128];
	int i;

	//
	if (!pParam) {
		showInfo_open(0, 0, 0, _T("addToMsgRoute failed, pParam is null"));
		return  -1;
	}

	//
	if (ui64Id == 0) {
		return  -1;
	}

	//
	TCHAR* tag;
	if (pParam->bAudio)  tag = _T(  "addToMsgRoute a"  );
	else  tag = _T("addToMsgRoute v");


	//
	QY_MESSENGER_ID  idInfo;
	idInfo.ui64Id = ui64Id;
	QY_MESSENGER_ID* pIdInfo = &idInfo;

	//
	bool  bFound = false;
	//
	MSG_ROUTE* pRca = pRoute;
	//
	if (pRca->idInfo_to.ui64Id == pIdInfo->ui64Id) {
		bFound = true;
	}
	else {
		for (i = 0; i < mycountof(pRca->mems_to); i++) {
			if (pRca->mems_to[i].idInfo.ui64Id == 0)  break;
			//
			if (pIdInfo->ui64Id == pRca->mems_to[i].idInfo.ui64Id) {
				bFound = true;  break;
			}
		}
	}
	//
	if (bFound) {
		_sntprintf(tBuf, mycountof(tBuf), _T("%s:  %I64u already in msgRoute"), tag, pIdInfo->ui64Id);
		showInfo_open0(0, 0, tBuf);
	}
	//
	if (!bFound) {
		if (!pRca->idInfo_to.ui64Id)  pRca->idInfo_to.ui64Id = pIdInfo->ui64Id;
		else {
			for (i = 0; i < mycountof(pRca->mems_to); i++) {
				if (pRca->mems_to[i].idInfo.ui64Id == 0)  break;
			}
			if (i == mycountof(pRca->mems_to)) {
				showInfo_open0(0, 0, _T("addToMsgRoute failed, rca is full"));
				goto  errLabel;
			}
			pRca->mems_to[i].idInfo.ui64Id = pIdInfo->ui64Id;
		}
		//
		_sntprintf(tBuf, mycountof(tBuf), _T("%s:  %I64u added to msgRroute"), tag,  pIdInfo->ui64Id);
		showInfo_open0(0, 0, tBuf);
	}

	//
	iErr = 0;

errLabel:
	return  iErr;
}


int  Tmp_MSG_ROUTE_2_MSG_ROUTE(Tmp_MSG_ROUTE* pTmr, bool  bAudio, MSG_ROUTE* pRoute)
{
	int  i;

	memset(pRoute, 0, sizeof(pRoute[0]));

	if (bAudio) {
		TmpMemTo* pTmpMemTo;
		pTmpMemTo = &pTmr->memTo;
		if (pTmpMemTo->idInfo.ui64Id) {
			//
			Param_addToMsgRoute  param = { 0 };
			param.bAudio = bAudio;
			//
			addToMsgRoute(&param, pTmpMemTo->idInfo.ui64Id, pRoute);
		}
		for (i = 0; i < mycountof(pTmr->mems_to); i++) {
			TmpMemTo* pTmpMemTo = &pTmr->mems_to[i];
			if (pTmpMemTo->idInfo.ui64Id == 0)  break;
			//
			Param_addToMsgRoute  param = { 0 };
			param.bAudio = bAudio;
			//
			addToMsgRoute(&param, pTmpMemTo->idInfo.ui64Id, pRoute);
		}
	}
	else {
		TmpMemTo* pTmpMemTo;
		pTmpMemTo = &pTmr->memTo;
		if (pTmpMemTo->idInfo.ui64Id) {
			if (!pTmpMemTo->var.ucbNoVDownload) {
				//
				Param_addToMsgRoute  param = { 0 };
				param.bAudio = bAudio;
				//
				addToMsgRoute(&param,  pTmpMemTo->idInfo.ui64Id, pRoute);
			}
		}
		for (i = 0; i < mycountof(pTmr->mems_to); i++) {
			TmpMemTo* pTmpMemTo = &pTmr->mems_to[i];
			if (pTmpMemTo->idInfo.ui64Id == 0)  break;
			//			
			if (!pTmpMemTo->var.ucbNoVDownload) {
				//
				Param_addToMsgRoute  param = { 0 };
				param.bAudio = bAudio;
				//
				addToMsgRoute(&param, pTmpMemTo->idInfo.ui64Id, pRoute);
			}
		}

	}

	//
	return  0;
}
//

//__declspec(  dllexport  )  int  addToMsgrs_sendLocalAv(  MC_VAR_common  *  pProcInfo,  void  *  pMIS_CNT,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  char  ucbVideoConferenceStarter,  ROUTE_sendLocalAv	*	pRoute, bool  bConfAv,  LPCTSTR  hint  )
__declspec(dllexport)  int  addToMsgrs_sendLocalAv(CCtxQmc* pProcInfo, void* pMIS_CNT, TmpMemTo* pMem_to, unsigned  char  ucbVideoConferenceStarter, ROUTE_sendLocalAv* pRoute, bool  bConfAv, LPCTSTR  hint)
{
	int						iErr		=		-1;
	CQySyncObj				syncObj;
	int						i			=		0;
	TCHAR  tBuf[128];

	
	MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMIS_CNT;
	
	//
	if  (  !pMisCnt  ||  !pMem_to  ||  !pMem_to->idInfo.ui64Id  )  return  -1;

	//
	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;


	//pRoute  =  &pSharedObj1->curRoute_sendLocalAv;

	if  (  syncObj.sync(  pQmcCfg->mutexName_syncSendAv  )  )  goto  errLabel;

	//
	_sntprintf(tBuf, mycountof(tBuf), _T("add %I64u to %s, %s"), pMem_to->idInfo.ui64Id, (bConfAv ? _T("route_confAv") : _T("route")), hint);
	showInfo_open0(0, 0, tBuf);

	//
	if  (  ucbVideoConferenceStarter  )  {
		//
		if (!bConfAv) {
			if (!pRoute->videoConference_idInfo_to.ui64Id)  pRoute->videoConference_idInfo_to.ui64Id = pMem_to->idInfo.ui64Id;
			else  if (pRoute->videoConference_idInfo_to.ui64Id != pMem_to->idInfo.ui64Id) {
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("addToMsgrs_sendLocalAv failed: ±¾µØÊÓÆµÒÑ¾­¼ÓÈëÊÓÆµ»áÒéÁË£¬Ö»ÄÜ¼ÓÈëÒ»¸ö."));
				goto  errLabel;
			}
		}
		else {
			 //
			bool  bFound = false;
			//
			Tmp_MSG_ROUTE* pRca = &pRoute->route_confAv1;
			//
			if (pRca->memTo.idInfo.ui64Id == pMem_to->idInfo.ui64Id) {
				bFound = true;
				//
				pRca->memTo.var = pMem_to->var;
			}
			else {
				 for (i = 0; i < mycountof(pRca->mems_to); i++) {
					 if (pRca->mems_to[i].idInfo.ui64Id == 0)  break;
					 //
					 if (pMem_to->idInfo.ui64Id == pRca->mems_to[i].idInfo.ui64Id) {
						 bFound = true;  
						 //
						 pRca->mems_to[i].var = pMem_to->var;
						 //
						 break;
					 }
				 }
			}
			//
			if (bFound) {
				_sntprintf(tBuf, mycountof(tBuf), _T("addToMsgrs_sendLocalAv:  %I64u already in route_confAv"), pMem_to->idInfo.ui64Id);
				showInfo_open0(0, 0, tBuf);
			}
			//
			if (!bFound) {
				if (!pRca->memTo.idInfo.ui64Id) {
					pRca->memTo.idInfo.ui64Id = pMem_to->idInfo.ui64Id;
					pRca->memTo.var = pMem_to->var;
				}
				else {
					for (i = 0; i < mycountof(pRca->mems_to); i++) {
						if (pRca->mems_to[i].idInfo.ui64Id == 0)  break;
					 }
					if (i == mycountof(pRca->mems_to)) {
						showInfo_open0(0, 0, _T("addToMsgrs_sendLocalAv failed, rca is full"));
						goto  errLabel;
					}
					pRca->mems_to[i].idInfo.ui64Id = pMem_to->idInfo.ui64Id;
					pRca->mems_to[i].var = pMem_to->var;
				}
				//
				_sntprintf(tBuf, mycountof(tBuf), _T("addToMsgrs_sendLocalAv:  %I64u added to route_confAv"), pMem_to->idInfo.ui64Id);
				showInfo_open0(0, 0, tBuf);
			}			 
		
			//
			Tmp_MSG_ROUTE_2_MSG_ROUTE(pRca, true, &pRoute->route_a);
			Tmp_MSG_ROUTE_2_MSG_ROUTE(pRca, false, &pRoute->route_v);


		}
		//
        }
	else  {	
		  if  (  pRoute->videoConference_idInfo_to.ui64Id  ==  pMem_to->idInfo.ui64Id  )  {				//  ÒÑÔÚ·¢ËÍÕßÖÐÁË
			  iErr  =  0;  goto  errLabel;
		  }

		  if  (  pRoute->route.idInfo_to.ui64Id  ==  pMem_to->idInfo.ui64Id  )  {							//  ÒÑÔÚ·¢ËÍÕßÖÐÁË
			  iErr  =  0;  goto  errLabel;
		  }
		  for  (  i  =  0;  i  <  mycountof(  pRoute->route.mems_to  );  i  ++  )  {
			   if  (  pMem_to->idInfo.ui64Id  ==  pRoute->route.mems_to[i].idInfo.ui64Id  )  {				//  ÒÑÔÚ·¢ËÍÕßÖÐÁË
				   iErr  =  0;  goto  errLabel;
			   }
		  }

		  //  ÏÂÃæÒªÕÒ¸ö¿ÕÎ»ÖÃ´æ½øÈ¥
		  if  (  !pRoute->route.idInfo_to.ui64Id  )  {												//  ÕÒµ½·¢ËÍµÄÎ»ÖÃ
			  pRoute->route.idInfo_to.ui64Id  =  pMem_to->idInfo.ui64Id;
			  mytime(  &pRoute->routeInfo.tModifiedTime  );										//  2009/09/11
			  }
		  else  {
			    for  (  i  =  0;  i  <  mycountof(  pRoute->route.mems_to  );  i  ++  )  {			//  
					 if  (  !pRoute->route.mems_to[i].idInfo.ui64Id  )  break;
				}
				if  (  i  ==  mycountof(  pRoute->route.mems_to  )  )  {
					#ifdef  __DEBUG__
							traceLogA(  "¶¼ÂúÁË"  );  
					#endif
					goto  errLabel;
				}
				pRoute->route.mems_to[i].idInfo.ui64Id  =  pMem_to->idInfo.ui64Id;
				mytime(  &pRoute->routeInfo.mems[i].tModifiedTime  );							//  2009/
		  }

	}

	//  ÉèÖÃ·¢ËÍÕß
	pRoute->route.idInfo_from.ui64Id  =  pMisCnt->idInfo.ui64Id;

	//  ÐÞ¸ÄÒ»ÏÂuiMsgRouteId. ±íÃ÷ÊÇÕâ¸ömsgRoute±ä»¯ÁË
	pRoute->route.uiMsgRouteId  =  getuiNextTranNo(  0,  0,  0  );

	//
	iErr  =  0;

errLabel:

	if  (  !iErr  )  {
	}
	return  iErr;
}


//
//__declspec(  dllexport  )  int  removeFromMsgrs_sendLocalAv(  MC_VAR_common  *  pProcInfo,  void  *  pMIS_CNT,  QY_MESSENGER_ID  *  pIdInfo,  QY_SHARED_OBJ  *  pSharedObj1  )
__declspec(dllexport)  int  removeFromMsgrs_sendLocalAv(CCtxQmc* pProcInfo, void* pMIS_CNT, QY_MESSENGER_ID* pIdInfo, ROUTE_sendLocalAv* pRoute, bool  bConfAv, LPCTSTR  hint)
{
	int						iErr = -1;
	CQySyncObj				syncObj;
	int						i = 0;
	TCHAR  tBuf[128];

	//
	if (!hint)  hint = _T("");

	//
	MIS_CNT* pMisCnt = (MIS_CNT*)pMIS_CNT;

	if (!pMisCnt || !pIdInfo || !pIdInfo->ui64Id)  return  -1;

	QMC_cfg* pQmcCfg = (QMC_cfg*)pProcInfo->get_qmc_cfg();
	if (!pQmcCfg)  return  -1;


	//pRoute  =  &pSharedObj1->curRoute_sendLocalAv;

	if (syncObj.sync(pQmcCfg->mutexName_syncSendAv))  goto  errLabel;

	//
	_sntprintf(tBuf, mycountof(tBuf), _T("remove %I64u from %s, %s"), pIdInfo->ui64Id, (bConfAv ? _T("route_confAv") : _T("route")), hint);
	showInfo_open0(0, 0, tBuf);

	//
	if (!bConfAv) {
		//
		//
		if (pRoute->videoConference_idInfo_to.ui64Id == pIdInfo->ui64Id) {
			pRoute->videoConference_idInfo_to.ui64Id = 0;
		}
		else {

			if (pRoute->route.idInfo_to.ui64Id == pIdInfo->ui64Id)  pRoute->route.idInfo_to.ui64Id = 0;
			else {
				for (i = 0; i < mycountof(pRoute->route.mems_to); i++) {
					if (pIdInfo->ui64Id == pRoute->route.mems_to[i].idInfo.ui64Id) {
						pRoute->route.mems_to[i].idInfo.ui64Id = 0;
						break;
					}
				}
			}

			if (!pRoute->route.idInfo_to.ui64Id) {		//  如果idInfo_to为空,则从mems_to[]中提取一个到idInfo_to中
				for (i = 0; i < mycountof(pRoute->route.mems_to); i++) {
					if (pRoute->route.mems_to[i].idInfo.ui64Id) {
						pRoute->route.idInfo_to.ui64Id = pRoute->route.mems_to[i].idInfo.ui64Id;
						pRoute->route.mems_to[i].idInfo.ui64Id = 0;
						//
						mytime(&pRoute->routeInfo.tModifiedTime);	//  2009/09/11
						break;
					}
				}
			}

		}
	}
	else {
		//
		Tmp_MSG_ROUTE* pRca = &pRoute->route_confAv1;// route_confAv1;
		//  这里是错的
		//
		if (pRca->mems_to->idInfo.ui64Id == pIdInfo->ui64Id) {
			pRca->mems_to->idInfo.ui64Id = 0;
			pRca->mems_to->idInfo.ui64Id = pRca->mems_to[0].idInfo.ui64Id;
			//
			for (i = 0; i < mycountof(pRca->mems_to) - 1; i++) {
				pRca->mems_to[i] = pRca->mems_to[i + 1];
				if (pRca->mems_to[i].idInfo.ui64Id == 0)  break;
			}
		}
		else {
			for (i = 0; i < mycountof(pRca->mems_to); i++) {
				if (pRca->mems_to[i].idInfo.ui64Id == 0)  break;
				if (pRca->mems_to[i].idInfo.ui64Id == pIdInfo->ui64Id) {
					int  j;
					for (j = i; j < mycountof(pRca->mems_to) - 1; j++) {
						pRca->mems_to[j].idInfo.ui64Id = pRca->mems_to[j + 1].idInfo.ui64Id;
						if (pRca->mems_to[j].idInfo.ui64Id == 0)  break;
					}
				}
			}
		}

		//
		Tmp_MSG_ROUTE_2_MSG_ROUTE(pRca, true, &pRoute->route_a);
		Tmp_MSG_ROUTE_2_MSG_ROUTE(pRca, false, &pRoute->route_v);

	}

	//  更新一下修改时间戳
	pRoute->route.uiMsgRouteId = getuiNextTranNo(0, 0, 0);

	iErr = 0;

errLabel:

	if (!iErr) {
	}

	return  iErr;
}

