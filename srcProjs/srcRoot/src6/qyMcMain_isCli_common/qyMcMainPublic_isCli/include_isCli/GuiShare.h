
#ifndef  __guiShare_h__
#define  __guiShare_h__

//
#include	"qmcStruct_defs.h"
#include	"qyDefs_open.h"

//
typedef  int  (*PF_initResample)(  	__int64  src_ch_layout, int src_rate, int src_sample_fmt, int src_nb_samples,  __int64  dst_ch_layout,  int  dst_rate,  int  dst_sample_fmt,  void  **  ppCtx_resample  );
typedef  int  (*PF_exitResample)(  void  *  pCtx_resample  );
typedef  int  (*PF_doResample)(  void  *  pCtx_resample,  char  *  pInput,  int  inputLen,  char  *  pOutput,  int  *  pOutputSize  );

//
typedef  int  (*PF_freeSharedObjByIndex)(  CCtxQmcTmpl  *  pProcInfo,  int  index  );
typedef  int  (*PF_chkResources  )(  HWND  hDlgTalk,  BOOL  bFreeCapImages  );
typedef void * (*PF_getQmcTaskInfoByIndex)(CCtxQmc * pProcInfo, int index);
typedef  int (*PF_getQmcTaskInfoIndexBySth)(CCtxQmc *pProcInfo, int iTaskId);

//
typedef  int (*PF_gui_procMsg)(void* pMsgParam);

//
typedef int (*PF_gui_notify_cancel)();
typedef int (*PF_gui_notify_chk)();

	 

//
struct  __guiShare_t  {
		PF_initResample								pf_initResample;
		PF_exitResample								pf_exitResample;
		PF_doResample								pf_doResample;
		//
		PF_freeSharedObjByIndex						pf_freeSharedObjByIndex;
		PF_chkResources								pf_chkResources;
		PF_getQmcTaskInfoByIndex					pf_getQmcTaskInfoByIndex;
		PF_getQmcTaskInfoIndexBySth					pf_getQmcTaskInfoIndexBySth;
		//
		PF_commonHandler							pf_doPre_createConsoleWall;
		//
		PF_gui_procMsg								pf_gui_procMsg;
		//
		//PF_gui_notify_cancel						pf_gui_notify_cancel;
		PF_gui_notify_chk							pf_gui_notify_chk;


};

#ifdef  __DLL_isCliCore__
		extern  __declspec(  dllexport  )  struct __guiShare_t	GuiShare;
#else
		extern __declspec(  dllimport  )  struct __guiShare_t	GuiShare;
#endif

//
int  GuiShare_init(  );







#endif

