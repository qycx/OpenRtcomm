
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include <taskAv.h>
#include	"confCli_func.h"
#include	"ancTaskAvOutput_confCli.h"
#include	"ctxQmc.h"





//
int  confCli_newTaskAvOutput(CCtxQmc* pProcInfo)
{
	if (pProcInfo->pTaskAvOutput)  return  -1;

	pProcInfo->pTaskAvOutput = new  CAncTaskAvOutput_confCli();

	return  0;
}





//
int  confCli_initTaskAvOutput(CCtxQmc  *  pProcInfo,  int  iTaskId, MuxStreamsCfg* pMuxStreamsCfg, PROC_TASK_AV* pTaskAv)
{
	int  iErr = -1;

	if (!pTaskAv)  return  -1;
	if (!pProcInfo->pTaskAvOutput) {
		return  -1;
	}

	//
	int  nStreams = 1;

	//
	do {	

		//
		if (pProcInfo->pTaskAvOutput->init(iTaskId,  nStreams)) {
			break;
		}


		//
		iErr = 0;
	} while (false);
	
	//
	return  iErr;
}


int confCli_exitTaskAvOutput(CCtxQmc  *  pProcInfo,  int  iTaskId,  PROC_TASK_AV  *  pTaskAv)
{
	//
	if (!pTaskAv)  return  -1;

	//
	if (pProcInfo->pTaskAvOutput) {
		
		//
		pProcInfo->pTaskAvOutput->exit(iTaskId);

		//
	}


	return  0;
}
