
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


#if  0
//  2010/09/02
__declspec(  dllexport  )  int  iisetROUTE_sendLocalAv(  MC_VAR_common  *  pProcInfo,  void  *  pMIS_CNT,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  char  ucbVideoConferenceStarter,  ROUTE_sendLocalAv	*	pRoute  )
{
	int						iErr		=		-1;
	CQySyncObj				syncObj;
	int						i			=		0;
	//ROUTE_sendLocalAv	*	pRoute		=		NULL;

	MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMIS_CNT;

	if  (  !pProcInfo  )  return  -1;
	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;

	if  (  !pMisCnt  )  return  -1;	//  这里允许pIdInfo或者pIdInfo->ui64Id为0，表示将不是在处理dlgTalk.不需要发送数据.

	//pRoute  =  &pSharedObj->curRoute_sendLocalAv;

	if  (  syncObj.sync(  pQmcCfg->mutexName_syncSendAv  )  )  goto  errLabel;

	memset(  pRoute,  0,  sizeof(  pRoute[0]  )  );

	if  (  pIdInfo  )  {
		if  (  ucbVideoConferenceStarter  )  {
			pRoute->videoConference_idInfo_to.ui64Id  =  pIdInfo->ui64Id;
	        }	
		else  {	
		      pRoute->route.idInfo_to.ui64Id  =  pIdInfo->ui64Id;
			  mytime(  &pRoute->routeInfo.tModifiedTime  );											//  2009/09/11
		}
	}

	//  
	pRoute->route.idInfo_from.ui64Id  =  pMisCnt->idInfo.ui64Id;

	//  
	pRoute->route.uiMsgRouteId  =  getuiNextTranNo(  0,  0,  0  );

	iErr  =  0;

errLabel:

	if  (  !iErr  )  {
	}
	return  iErr;
}
#endif 


//

__declspec(  dllexport  )  int  addToMsgrs_sendLocalAv(  MC_VAR_common  *  pProcInfo,  void  *  pMIS_CNT,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  char  ucbVideoConferenceStarter,  ROUTE_sendLocalAv	*	pRoute, bool  bConfAv,  LPCTSTR  hint  )
{
	int						iErr		=		-1;
	CQySyncObj				syncObj;
	int						i			=		0;
	TCHAR  tBuf[128];

	
	MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMIS_CNT;
	
	if  (  !pMisCnt  ||  !pIdInfo  ||  !pIdInfo->ui64Id  )  return  -1;

	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;


	//pRoute  =  &pSharedObj1->curRoute_sendLocalAv;

	if  (  syncObj.sync(  pQmcCfg->mutexName_syncSendAv  )  )  goto  errLabel;

	//
	_sntprintf(tBuf, mycountof(tBuf), _T("add %I64u to %s, %s"), pIdInfo->ui64Id, (bConfAv ? _T("route_confAv") : _T("route")), hint);
	showInfo_open0(0, 0, tBuf);

	//
	if  (  ucbVideoConferenceStarter  )  {
		//
		if (!bConfAv) {
			if (!pRoute->videoConference_idInfo_to.ui64Id)  pRoute->videoConference_idInfo_to.ui64Id = pIdInfo->ui64Id;
			else  if (pRoute->videoConference_idInfo_to.ui64Id != pIdInfo->ui64Id) {
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("addToMsgrs_sendLocalAv failed: ±¾µØÊÓÆµÒÑ¾­¼ÓÈëÊÓÆµ»áÒéÁË£¬Ö»ÄÜ¼ÓÈëÒ»¸ö."));
				goto  errLabel;
			}
		}
		else {
			 //
			bool  bFound = false;
			MSG_ROUTE* pRca = &pRoute->route_confAv;
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
				_sntprintf(tBuf, mycountof(tBuf), _T("addToMsgrs_sendLocalAv:  %I64u already in route_confAv"), pIdInfo->ui64Id);
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
						showInfo_open0(0, 0, _T("addToMsgrs_sendLocalAv failed, rca is full"));
						goto  errLabel;
					}
					pRca->mems_to[i].idInfo.ui64Id = pIdInfo->ui64Id;
				}
				//
				_sntprintf(tBuf, mycountof(tBuf), _T("addToMsgrs_sendLocalAv:  %I64u added to route_confAv"), pIdInfo->ui64Id);
				showInfo_open0(0, 0, tBuf);
			}			 
			 
		}
		//
        }
	else  {	
		  if  (  pRoute->videoConference_idInfo_to.ui64Id  ==  pIdInfo->ui64Id  )  {				//  ÒÑÔÚ·¢ËÍÕßÖÐÁË
			  iErr  =  0;  goto  errLabel;
		  }

		  if  (  pRoute->route.idInfo_to.ui64Id  ==  pIdInfo->ui64Id  )  {							//  ÒÑÔÚ·¢ËÍÕßÖÐÁË
			  iErr  =  0;  goto  errLabel;
		  }
		  for  (  i  =  0;  i  <  mycountof(  pRoute->route.mems_to  );  i  ++  )  {
			   if  (  pIdInfo->ui64Id  ==  pRoute->route.mems_to[i].idInfo.ui64Id  )  {				//  ÒÑÔÚ·¢ËÍÕßÖÐÁË
				   iErr  =  0;  goto  errLabel;
			   }
		  }

		  //  ÏÂÃæÒªÕÒ¸ö¿ÕÎ»ÖÃ´æ½øÈ¥
		  if  (  !pRoute->route.idInfo_to.ui64Id  )  {												//  ÕÒµ½·¢ËÍµÄÎ»ÖÃ
			  pRoute->route.idInfo_to.ui64Id  =  pIdInfo->ui64Id;
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
				pRoute->route.mems_to[i].idInfo.ui64Id  =  pIdInfo->ui64Id;
				mytime(  &pRoute->routeInfo.mems[i].tModifiedTime  );							//  2009/
		  }

	}

	//  ÉèÖÃ·¢ËÍÕß
	pRoute->route.idInfo_from.ui64Id  =  pMisCnt->idInfo.ui64Id;

	//  ÐÞ¸ÄÒ»ÏÂuiMsgRouteId. ±íÃ÷ÊÇÕâ¸ömsgRoute±ä»¯ÁË
	pRoute->route.uiMsgRouteId  =  getuiNextTranNo(  0,  0,  0  );

	iErr  =  0;

errLabel:

	if  (  !iErr  )  {
	}
	return  iErr;
}


