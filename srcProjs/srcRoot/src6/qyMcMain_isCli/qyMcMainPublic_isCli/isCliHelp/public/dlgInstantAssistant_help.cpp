
#include	"stdafx.h"
#include	"qyMcMainCommon.h"

#include	"tmpCeLib.h"

#include	"qyOpenShellCommon.h"
#include	"dlgTalkProc.h"
#include	"WallTalkers.h"
#include	"myresource.h"
//#include	"DlgInstantAssistant.h"
#include	"qyCusResTemp.h"
#include	"qmcVideoCapture_isCli.h"

#include	"qyAvRecordPublic.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"isclid3dpublic.h"
#include	"qmShellPublic.h"


__declspec(dllexport)  bool  isActiveMemsFull(int  iTaskId, bool bSpeaker)
{
	bool  bRet = false;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	//
	int  index_taskInfo = getQmcTaskInfoIndexBySth(pProcInfo, iTaskId);
	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
	if (!pTaskInfo)  goto  errLabel;
	QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
	if (pTc->common.uiType != CONST_taskDataType_conf)  goto  errLabel;

	int  i;
	TCHAR  tBuf[128];

	//					  
	if (!bSpeaker) {
		//
		for (i = 0; i < mycountof(pTc->videoConference.activeMems_from); i++) {
			if (!pTc->videoConference.activeMems_from[i].avStream.idInfo.ui64Id)  break;
		}
		if (i < mycountof(pTc->videoConference.activeMems_from)) {
			goto  errLabel;
		}

		//
	}
	else {
		//
		int nSpeakers = 0;
		//
		for (i = 0; i < mycountof(pTc->videoConference.activeMems_from); i++) {
			if (pTc->videoConference.activeMems_from[i].avStream.idInfo.ui64Id
				&& !pTc->videoConference.activeMems_from[i].avStream.obj.resObj.uiObjType)
			{
				nSpeakers++;
			}
		}

		//
		if (nSpeakers < pTc->videoConference.usMaxSpeakers)  goto  errLabel;

		//
	}

	//					  	
	bRet = true;

errLabel:
	return  bRet;

}


