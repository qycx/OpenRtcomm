
#include	"stdafx.h"

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
	#include	<myQedit.h>
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>
#include	<dsound.h>


////
#include <shellapi.h>
//  #include <commctrl.h>




///
#include	"qmcDmoPublic.h"

#include	"qmcVideoCapture_dx.h"

#include	"myfourcc.h"
#include	"mywmcodecconst.h"

#include	"qmcCmdProc.h"

#include	"cPropertyBag.h"

#include	"qyCusResTemp.h"
#include	"qmcDirectX.h"

//  #include	"myresource.h"
#ifdef  __SUPPORT_CUS_sampleGrabber__
		#include	"qySampleGrabberPublic.h"
#endif

//#include	"myresource.h"
#include	"isCliHelpPublic.h"



  //  2012/04/22
  int  viewGpsVWall(  HWND  hParent,  LPCTSTR  misServName  )
{
	int					iErr				=	-1;
	MC_VAR_isCli	*	pProcInfo			=	QY_GET_procInfo_isCli(  );
	HWND				hWall				=	NULL;
	int					iWndContentType		=	CONST_qyWndContentType_vWall;	//  2013/07/12
	int					iVWallSubType		=	CONST_vwSubtype_gps;
	BOOL				bNewVirtualWall		=	TRUE;

	if  (  viewVWall(  hParent,  misServName,  iVWallSubType,  bNewVirtualWall,  NULL,  FALSE,  &hWall  )  )  goto  errLabel;

	iErr  =  0;

errLabel:

	return  iErr;
}



 //
 int  viewGlobalVWall(  HWND  hParent,  LPCTSTR  misServName,  LPCTSTR  init_qvwFile,  BOOL  bNeedNotShowWnd  ) 
{
	int					iErr				=	-1;
	MC_VAR_isCli	*	pProcInfo			=	QY_GET_procInfo_isCli(  );
	HWND				hWall				=	NULL;
	int					iWndContentType		=	CONST_qyWndContentType_vWall;	//  2013/07/12
	int					iVWallSubType		=	CONST_vwSubtype_confWall;
	BOOL				bNewVirtualWall		=	FALSE;

	if  (  IsWindow(  pProcInfo->g_hVWall  )  )  {
		MACRO_SetForegroundWindow(  pProcInfo->g_hVWall  );
		iErr  =  0;  goto  errLabel;
	}

	if  (  viewVWall(  hParent,  misServName,  iVWallSubType,  bNewVirtualWall,  init_qvwFile,  bNeedNotShowWnd,  &hWall  )  )  goto  errLabel;

	pProcInfo->g_hVWall  =  hWall;
	pProcInfo->iWndContentType_g_hVWall  =  iWndContentType;

	iErr  =  0;

errLabel:

	return  iErr;
}


  int  viewGlobalGpsVWall(  HWND  hParent,  LPCTSTR  misServName  )
{
	int					iErr				=	-1;
	MC_VAR_isCli	*	pProcInfo			=	QY_GET_procInfo_isCli(  );
	HWND				hWall				=	NULL;
	int					iWndContentType		=	CONST_qyWndContentType_vWall;	//  2013/07/12
	int					iVWallSubType		=	CONST_vwSubtype_globalGps;
	BOOL				bNewVirtualWall		=	FALSE;

	if  (  IsWindow(  pProcInfo->g_hVWall  )  )  {
		MACRO_SetForegroundWindow(  pProcInfo->g_hVWall  );
		iErr  =  0;  goto  errLabel;
	}

	if  (  viewVWall(  hParent,  misServName,  iVWallSubType,  bNewVirtualWall,  NULL,  FALSE,  &hWall  )  )  goto  errLabel;

	pProcInfo->g_hVWall  =  hWall;
	pProcInfo->iWndContentType_g_hVWall  =  iWndContentType;

	iErr  =  0;

errLabel:

	return  iErr;
}
