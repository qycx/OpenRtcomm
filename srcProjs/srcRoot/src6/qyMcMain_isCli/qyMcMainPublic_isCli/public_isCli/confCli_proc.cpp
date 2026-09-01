


#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include <taskAv.h>
#include	"confCli_func.h"
#include	"ancTaskAvOutput_confCli.h"
#include	"ctxQmc.h"
#include	"confCli_func.h"
#include	"qmcFunc.h"



int confCli_channelsInit(Param_channelsInit* pParam, MIS_CNT* pMisCnt)
{
	
		int  iErr = -1;
		
		CCtxQmc* pProcInfo = (CCtxQmc*)pMisCnt->pProcInfoParam;
		CCtxQyMc* pQyMc = pProcInfo->pQyMc;



		int				j;
		GENERIC_Q_CFG		tmpqCfg;

		//
		pMisCnt->iCnt_channels = CONST_maxConnsPerCli_mis;

		//
		int size;
		size = sizeof(MIS_CHANNEL) * pMisCnt->iCnt_channels;
		pMisCnt->pChannels = (  MIS_CHANNEL*)mymalloc(size);
		if (!pMisCnt->pChannels) {
			goto  errLabel;
		}
		memset((char*)pMisCnt->pChannels, 0, size);



		//
		pMisCnt->pChannels[0].uiType = CONST_channelType_talking;
		pMisCnt->pChannels[1].uiType = CONST_channelType_robot;
		pMisCnt->pChannels[2].uiType = CONST_channelType_media;
		pMisCnt->pChannels[3].uiType = CONST_channelType_rtMedia;	//  2008/04/17
		pMisCnt->pChannels[4].uiType = CONST_channelType_rtOp;	//  2008/04/17

		//
		int  cnt;
		//cnt = mycountof(pMisCnt->channels);
		cnt = pMisCnt->iCnt_channels;
		for (j = 0; j < cnt; j++) {
			MIS_CHANNEL* pChannel = &pMisCnt->pChannels[j];

#if  0
			if (1) {

				//  2016/09/09
				pChannel->pMisCnt = pMisCnt;

				//  
				memcpy(&tmpqCfg, &pMisCnt->cfg.inCacheQ, sizeof(tmpqCfg));
				_sntprintf(tmpqCfg.name, mycountof(tmpqCfg.name), _T("%s-%u"), tmpqCfg.name, j);
				_sntprintf(tmpqCfg.mutexName_prefix, mycountof(tmpqCfg.mutexName_prefix), _T("%s-%u"), tmpqCfg.mutexName_prefix, j);
				if (initGenericQ(&tmpqCfg, mymalloc, 0, 0, myfree, NULL, &pChannel->inCacheQ))  goto  errLabel;

				//  2015/09/09
#if  0
				memcpy(&tmpqCfg, &pMisCnt->cfg.inputQ, sizeof(tmpqCfg));
				_sntprintf(tmpqCfg.name, mycountof(tmpqCfg.name), _T("%s-%u"), tmpqCfg.name, j);
				_sntprintf(tmpqCfg.mutexName_prefix, mycountof(tmpqCfg.mutexName_prefix), _T("%s-%u"), tmpqCfg.mutexName_prefix, j);
				//  if  (  initGenericQ(  &tmpqCfg,  mymalloc,  0,  0,  myfree,  &pChannel->toSendQ  )  )  goto  errLabel;
				if (initQyQ2(&tmpqCfg, &pQyMc->cfg.rwLockParam, 1, NULL, mallocMemory, mymalloc, 0, 0, freeMemory, myfree, NULL, &pChannel->inputQ2))  goto  errLabel;
#endif

				//
				memcpy(&tmpqCfg, &pMisCnt->cfg.toSendQ, sizeof(tmpqCfg));
				_sntprintf(tmpqCfg.name, mycountof(tmpqCfg.name), _T("%s-%u"), tmpqCfg.name, j);
				_sntprintf(tmpqCfg.mutexName_prefix, mycountof(tmpqCfg.mutexName_prefix), _T("%s-%u"), tmpqCfg.mutexName_prefix, j);
				//  if  (  initGenericQ(  &tmpqCfg,  mymalloc,  0,  0,  myfree,  &pChannel->toSendQ  )  )  goto  errLabel;
				if (initQyQ2(&tmpqCfg, &pQyMc->cfg.rwLockParam, 1, NULL, mallocMemory, mymalloc, 0, 0, freeMemory, myfree, NULL, &pChannel->toSendQ2))  goto  errLabel;

				//
				memcpy(&tmpqCfg, &pMisCnt->cfg.outputQ, sizeof(tmpqCfg));
				_sntprintf(tmpqCfg.name, mycountof(tmpqCfg.name), _T("%s-%u"), tmpqCfg.name, j);
				_sntprintf(tmpqCfg.mutexName_prefix, mycountof(tmpqCfg.mutexName_prefix), _T("%s-%u"), tmpqCfg.mutexName_prefix, j);
				//  if  (  initGenericQ(  &tmpqCfg,  mymalloc,  0,  0,  myfree,  &pChannel->outputQ  )  )  goto  errLabel;  
				if (initQyQ2(&tmpqCfg, &pQyMc->cfg.rwLockParam, 1, NULL, mallocMemory, mymalloc, 0, 0, freeMemory, myfree, NULL, &pChannel->outputQ2))  goto  errLabel;

			}
#endif 
			//
			if (initChannel(pMisCnt, j, pChannel)) {
				goto  errLabel;
			}

		}

		iErr = 0;
	errLabel:


		//
		return  iErr;
	
}



int confCli_channelsExit(MIS_CNT* pMisCnt)
{
	//  ¹Ø±Õ´¥·¢ÐÅºÅµÆ
	int  j;
	int  cnt;
	//cnt = mycountof(pMisCnt->channels);
	
	if (pMisCnt->pChannels) {
		cnt = pMisCnt->iCnt_channels;
		for (j = 0; j < cnt; j++) {
			MIS_CHANNEL* pChannel = &pMisCnt->pChannels[j];
			//  
#if  0
			if (1) {
				//
				exitQyQ2(&pChannel->outputQ2);
				exitQyQ2(&pChannel->toSendQ2);
#if  0
				exitQyQ2(&pChannel->inputQ2);	//  2015/09/09
#endif
				//
				exitGenericQ(&pChannel->inCacheQ);
			}
#endif 
			//
			exitChannel(pChannel);

		}
	}

	//
	MACRO_safeFree(pMisCnt->pChannels);
	pMisCnt->iCnt_channels = 0;



	return  0;
}


