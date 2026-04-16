

#include "stdafx.h"

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

//#include	"qyMessenger_ts_noMfc.h"

#include	"isCliHelpPublic.h"
#include	"isCliD3dPublic.h"
//#include	"qyMc_tsDlg_noMfc.h"

//#include	"ctxQmc_gui.h"
#include	"dyn_isCliD3d_public.h"
#include	"qyMessengerHelpPublic.h"
#include	"GuiShare.h"
#include	"tmpFfmpegPublic.h"
#include	"qmcVideoCapture.h"
#include	"dlgTalkProc.h"

//
int mainWnd_gui_procMsg(void* pMsgParam);
int gui_notify_chk();



//
int  GuiShare_init(  )
{
	memset(  &GuiShare,  0,  sizeof(  GuiShare  )  );
	
#ifndef  __qmdConn__
	//
	GuiShare.pf_initResample  =  initResample;
	GuiShare.pf_exitResample  =  exitResample;
	GuiShare.pf_doResample  =  doResample;

	//
	GuiShare.pf_freeSharedObjByIndex  =  freeSharedObjByIndex;
	GuiShare.pf_chkResources  =  chkResources;
	GuiShare.pf_getQmcTaskInfoByIndex  =  getQmcTaskInfoByIndex;
	GuiShare.pf_getQmcTaskInfoIndexBySth  =  getQmcTaskInfoIndexBySth;

	//
	GuiShare.pf_doPre_createConsoleWall  =  doPre_createConsoleWall;

	//
	GuiShare.pf_gui_procMsg = mainWnd_gui_procMsg;

	//
	GuiShare.pf_gui_notify_chk = gui_notify_chk;
#endif


	//
	return  0;
}


