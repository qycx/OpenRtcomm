



#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
	#include	<fcntl.h>
	#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#ifndef  __WINCE__
#pragma include_alias( "dxtrans.h", "myqedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__

	//  #include	<Qedit.h>
	#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>

#include	"qmcDmoPublic.h"
#ifndef  __WINCE__
	#include	"qmcVideoCapture_dx.h"
#endif
#include	"myfourcc.h"

#include	"qyCusResTemp.h"

//  #include	"qyMc.h"
#include	"qyGuiCommProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecordPublic.h"

#include	"myresource.h"

#include	"qyOpenShellCommon.h"
#include	"wallTalkers.h"
#include	"DlgShareDynBmpsProc.h"

#include	"dlgTalkProc.h"
#include	"qmcCmdProc.h"

//  #include	"DlgProgress.h"
#include	"tmpCeLib.h"

#include	"qyComPortEx.h"
#include	"qmcGpsProc.h"

#include	"myDb.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"qmcCommFunc_isCli.h"

//
#include	"qmcVideoCapture_rtsp.h"


//  2015/10/21
//int  getVal_bSupported_pktResType_sharedTex(  MC_VAR_common  *  pProcInfo,  unsigned  int  uiModuleType,  int  iFourcc,  int  propId,  BOOL  *  pbVal   )
int  getVal_bSupported_pktResType_sharedTex(  void * pProcInfoParam,  unsigned  int  uiModuleType,  int  propId,  void  *  pParam_input,  BOOL  *  pbVal   )
{
	if  (  !pbVal  )  return  -1;
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pProcInfoParam;
	//  unsigned int  uiModuleType  =  getModuleTypeBySth(  pProcInfo,  ucCompressors  );
	CUS_MODULES				*	pCusModules			=	(  CUS_MODULES  *  )pProcInfo->getCusModules(  );
	if  (  !pCusModules  )  return  -1;
	
	CUS_MODULE_U	*	pModule	=	NULL;
				  
	M_getCompressModule(  pCusModules,  uiModuleType,  pModule  );	//  2012/09/09	
	if  (  !pModule  ||  !pModule->common.bLoaded  ||  !pModule->compress.pf_qdcGetProp  )  {	
		return  -1;		  
	}

	BOOL  bSupported  =  FALSE;
	//  int  propId  =  CONST_qdcPropId_bSupport_sharedTex_enc;
	if  (  pModule->compress.pf_qdcGetProp(  propId,  pParam_input,  &bSupported  )  )  return  -1;

	*pbVal  =  bSupported;

	return  0;
}


