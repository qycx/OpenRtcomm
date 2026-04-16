
#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"qyCusResTemp.h"

#ifndef  __NOTSUPPORT_MULTIDOC__
	//#include	"mainClient.h"
	//#include	"mainFrm.h"
#endif
#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	"qmcVideoCapture_isCli.h"

#include	"myresource.h"

#ifdef  __WINCE__
		#ifndef  __TEST__
				 #include	"ceMenuBar.h"
		#endif
		#include	"dlgTalk_ce.h"
#else
		#include	"dlgtalkproc.h"
#endif

#include	"QyPlaySound_wave.h"
#include	"qmcDxSurfacePublic.h"
#include	"qyWnd.h"

#include	"dlgMcClientLogon.h"
#ifdef  __WINCE__
		#include	"dlg_qyMc_winCe.h"
		#include	"dlgObjs.h"
#endif
#include	"DlgQnmCfgOptionsIsClient.h"
#include	"module_qisCamCap.h"

#ifndef  __NOTSUPPORT_MULTIDOC__
		 //#include	"dlgNotification.h"
#endif

//  
#include	"mmDeviceProc.h"
#include	"isCliHelpPublic.h"
#include	"wallTalkers.h"
#include	"isCliD3dPublic.h"
#include	"isCliCorePublic.h"
#include	"dyn_isCliD3d_public.h"



//
 BOOL  bViewActiveImObjList(  )
{
	BOOL						bRet	=	FALSE;
	QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();

	DLG_guiDataParam_objs		param;

	memset(  &param,  0,  sizeof(  param  )  );
	param.ucbActiveTalker  =  TRUE;

	showDlgObjs(  pQyMc->g_hInst,  pQyMc->gui.hMainWnd,  &param  );

	if  (  !param.o.ui64Id_selected  )  goto  errLabel;
	
#if  0
	talkToMessenger(  param.ui64Id_selected,  FALSE,  TRUE,  NULL  );
#endif
	tryToTalkToMessenger_id( mynull, param.o.ui64Id_selected,  0,  TRUE,  NULL,  0,  NULL  );


	bRet  =  TRUE;

errLabel:

	return  bRet;
}


