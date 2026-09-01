
#include	"stdafx.h"
#include	"ancTaskAvOutput_confCli.h"



CAncTaskAvOutput_confCli::CAncTaskAvOutput_confCli()
{
	memset(&m_var, 0, sizeof(m_var));
}


CAncTaskAvOutput_confCli::~CAncTaskAvOutput_confCli()
{
	return;
}

//
TaskMuxStream_confCli* CAncTaskAvOutput_confCli::getTaskMuxStreamBySth(int  iTaskId)
{
	if (!iTaskId)  return  mynull;

	int  i;
	for (i = 0; i < mycountof(m_var.taskMuxStreams); i++) {
		TaskMuxStream_confCli* pMem = &m_var.taskMuxStreams[i];
		if (pMem->iTaskId == iTaskId) {
			break;
		}
	}
	if (i == mycountof(m_var.taskMuxStreams))  return  mynull;

	return  &m_var.taskMuxStreams[i];

}


//
//  
//
MuxStreamOutputQ* CAncTaskAvOutput_confCli::getMuxStreamOutputQ(int  iTaskId,  int muxStreamIndex)
{
	MuxStreamOutputQ* pRet = mynull;

	do {
		//
		if (!iTaskId)  {
			break;
		}

		//	
		TaskMuxStream_confCli* pMem = getTaskMuxStreamBySth(iTaskId);
		if (!pMem) {
			break;
		}

		//
		return  &pMem->muxStreamOutputQ;

		//
	} while (false);

	//
	return  mynull;

 }


int CAncTaskAvOutput_confCli::init(int  iTaskId, int  nMuxStreams)
{
	int  iErr = -1;

	if (!iTaskId)  return  -1;

	do {
		//
		int  i;
		for (i = 0; i < mycountof(m_var.taskMuxStreams); i++) {
			TaskMuxStream_confCli* pMem = &m_var.taskMuxStreams[i];
			if (pMem->iTaskId == iTaskId)  return  -1;
		}
		//
		for (i = 0; i < mycountof(m_var.taskMuxStreams); i++) {
			TaskMuxStream_confCli* pMem = &m_var.taskMuxStreams[i];
			
			if (!pMem->iTaskId) {
				break;				
			}
		}
		if (i == mycountof(m_var.taskMuxStreams)) {
			break;
		}
		TaskMuxStream_confCli* pTms = &m_var.taskMuxStreams[i];

		//
		int  muxStreamIndex = 0;
		//
		if (initMuxStreamOutputQ(iTaskId, muxStreamIndex,  &pTms->muxStreamOutputQ)) {
			break;
		}

		//
		pTms->iTaskId = iTaskId;

		//
		iErr = 0;
	} while (false);


	return  iErr;
}

int CAncTaskAvOutput_confCli::exit(int  iTaskId)
{
	TaskMuxStream_confCli* pTms = getTaskMuxStreamBySth(iTaskId);
	if (!pTms)  return  -1;

	exitMuxStreamOutputQ(&pTms->muxStreamOutputQ);

	//
	memset(pTms, 0, sizeof(pTms[0]));


	return  0;
}
