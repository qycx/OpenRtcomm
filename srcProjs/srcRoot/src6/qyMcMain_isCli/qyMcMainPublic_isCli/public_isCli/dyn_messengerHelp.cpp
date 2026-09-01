

#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"dlgtalkproc.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qmcDmoPublic.h"

#include	"wallTalkers.h"
#include	"qmcGpsProc.h"
#include	"msAecCommon.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"
#include	"amCapPublic.h"
#include	"isCliD3dPublic.h"
#include	"qyMcMainWndProc.h"
#include	"imgProcessPublic.h"
#include	"saveAvProc_open.h"
#include	"isCliSaveAvPublic.h"
//
#include	"ctxMcThread.h"






__declspec(  dllexport  )  int  dyn_myOnAppAbout(  MC_VAR_isCli  *  pProcInfo,  HWND  hParent  )
{
	//  
	if  (  !pProcInfo  )  return  -1;
	
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->messenger_help.bOk  )  return  -1;

	return  pFuncs->messenger_help.pf_myOnAppAbout(  hParent  );
}