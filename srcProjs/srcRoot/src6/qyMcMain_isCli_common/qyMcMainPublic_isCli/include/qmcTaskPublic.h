
#ifndef  __qmcTaskPublic_h__
#define  __qmcTaskPublic_h__	//  {


//
int  getVal_bExists_taskInWnd(  QY_MC  *  pQyMc,  int  iTaskId,  HWND  hWnd_task,  BOOL  *  pbExists  );


int  getSize_QMC_TASK_INFO(  );

//  2014/09/24
int  freeTaskInfos(  CCtxQmc  *  pProcInfo  );
int  newTaskInfoIndex(  CCtxQmc  *  pProcInfo,  unsigned  int  uiTaskDataType,  HWND  hWnd_task,  int  iTaskId,  LPCTSTR  hint  );
int  freeTaskInfo(  CCtxQmc  *	pProcInfo,  int  index_taskInfo,  LPCTSTR  hint  );
 

//
void * getQmcTaskInfoByIndex(CCtxQmc * pProcInfo, int index);
		int getQmcTaskInfoIndexBySth(CCtxQmc *pProcInfo, int iTaskId);
				int qmcTaskInfo_setClosed(CCtxQmc * pProcInfo, int index_taskInfo, LPCTSTR hint);
						bool qmcTaskInfo_bAlive(CCtxQmc * pProcInfo, int index_taskInfo);


//
						        int removeTask(int iTaskId);


#endif  //  }


