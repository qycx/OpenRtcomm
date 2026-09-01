
//
#ifndef  __confCli_func_h__
#define  __confCli_func_h__		//  {

//
int confCli_channelsInit(Param_channelsInit* pParam, MIS_CNT* pMisCnt);
int confCli_channelsExit(MIS_CNT* pMisCnt);



//
int  confCli_doCmd_startAvCall(HWND  hParent, HWND  hCurTalk, int  level, BOOL  b3D, unsigned  char  ucbAvConsole, PARAM_startAvCall* pParam);
int  confCli_dlgTalk_closeTaskAv_afterTaskClosed(HWND  hDlgTalk, void* pm_var);


//
int  confCli_newTaskAvOutput(CCtxQmc* pProcInfo);


//
int  confCli_initTaskAvOutput(CCtxQmc  *  pProcInfo, int  iTaskId, MuxStreamsCfg* pMuxStreamsCfg, PROC_TASK_AV* pTaskAv);
int  confCli_exitTaskAvOutput(CCtxQmc  *  pProcInfo,  int  iTaskId,  PROC_TASK_AV  *  pTaskAv);




#endif  //  }


