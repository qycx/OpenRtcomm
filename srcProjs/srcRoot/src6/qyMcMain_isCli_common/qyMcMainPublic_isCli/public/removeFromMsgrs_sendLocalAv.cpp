
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
//__declspec(  dllexport  )  int  removeFromMsgrs_sendLocalAv(  MC_VAR_common  *  pProcInfo,  void  *  pMIS_CNT,  QY_MESSENGER_ID  *  pIdInfo,  QY_SHARED_OBJ  *  pSharedObj1  )
__declspec(  dllexport  )  int  removeFromMsgrs_sendLocalAv(  MC_VAR_common  *  pProcInfo,  void  *  pMIS_CNT,  QY_MESSENGER_ID  *  pIdInfo,  ROUTE_sendLocalAv  *  pRoute, bool  bConfAv,  LPCTSTR  hint  )
{
	int						iErr		=		-1;
	CQySyncObj				syncObj;
	int						i			=		0;
	TCHAR  tBuf[128];

	//
	if (!hint)  hint = _T("");

	//
	MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMIS_CNT;
	
	if  (  !pMisCnt  ||  !pIdInfo  ||  !pIdInfo->ui64Id  )  return  -1;

	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;


	//pRoute  =  &pSharedObj1->curRoute_sendLocalAv;

	if  (  syncObj.sync(  pQmcCfg->mutexName_syncSendAv  )  )  goto  errLabel;

	//
	_sntprintf(tBuf, mycountof(tBuf), _T("remove %I64u from %s, %s"), pIdInfo->ui64Id, (  bConfAv  ?  _T(  "route_confAv"  )  :  _T(  "route"  )  ),  hint);
	showInfo_open0(0, 0, tBuf);

	//
	if  (  !bConfAv  )  {
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
		MSG_ROUTE* pRca = &pRoute->route_confAv;
		//
		if (pRca->idInfo_to.ui64Id == pIdInfo->ui64Id) {
			pRca->idInfo_to.ui64Id = 0;
			pRca->idInfo_to.ui64Id = pRca->mems_to[0].idInfo.ui64Id;
			//
			for (i = 0; i < mycountof(pRca->mems_to)  -  1; i++) {
				pRca->mems_to[i] = pRca->mems_to[i + 1];
				if (pRca->mems_to[i].idInfo.ui64Id == 0)  break;
			}
		}
		else {
			for (i = 0; i < mycountof(pRca->mems_to); i++) {
				if (pRca->mems_to[i].idInfo.ui64Id == 0)  break;
				if (pRca->mems_to[i].idInfo.ui64Id == pIdInfo->ui64Id) {
					int  j;
					for (j = i; j < mycountof(pRca->mems_to)  -  1; j++) {
						pRca->mems_to[j].idInfo.ui64Id = pRca->mems_to[j + 1].idInfo.ui64Id;
						if (pRca->mems_to[j].idInfo.ui64Id == 0)  break;
					}
				}
			 }
		}


	}

	//  更新一下修改时间戳
	pRoute->route.uiMsgRouteId  =  getuiNextTranNo(  0,  0,  0  );

	iErr  =  0;

errLabel:
	
	if  (  !iErr  )  {
	}

	return  iErr;
}


