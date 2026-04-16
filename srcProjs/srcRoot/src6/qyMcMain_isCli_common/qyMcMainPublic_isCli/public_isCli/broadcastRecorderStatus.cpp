

//
#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	<time.h>
#include	<stddef.h>
#include	<ShellAPI.h>
#include	<tchar.h>

#include	"qymcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"

#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"


#include	"tmpCeLib.h"
#include	"qyWnd.h"

#include	"qyRtcCommProc.h"
#ifndef  __WINCE__
#include	"dlgVideosProc.h"
#endif
#include	<assert.h>
#include	"qmcDxSurfacePublic.h"
#ifndef  __WINCE__
#include	"qmcConferenceWall.h"
#include	"isCliHelpPublic.h"
#endif
#include	"qmcCmdProc.h"

#include	"policyAvParams.h"

#include	"dlgTalkProc.h"
#include	"qmcSharePublic.h"

#include	"DlgWalls.h"

#include	"gpsCommProc.h"
#include	"qmcGpsProc.h"

#include	"qyCusResTemp.h"

#include	"qmcVWall.h"
#include	"dlgDesktopsMonProc.h"

#include	"sp.h"
#include	"myDb.h"
#include	"isCliHelpPublic.h"

#include	"imgProcessPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"dlgMsgToolProc.h"
#include	"qmcVideoCapture_rtsp.h"
#include	"qmcDynBmp.h"

#include	"qyCusResTemp.h"
#include	"dlgShareDynBmpsProc.h"
#include	"isCliD3dPublic.h"
#include	"policyIsClientFunc.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliExPublic.h"
#include	"isCliCorePublic.h"
#include	"dyn_isCliD3d_public.h"
#include	"myTChar.h"

#ifdef  __TEST_ONLY__
		#include	"testOnly.h"
#endif





//

  int  tmpHandler_broadcastRecorderStatus(  void  *  p0,  void  *  p1,  void  *  pQElem  )
{
	 int					iRet				=	-1;
	 COMMON_PARAM		*	pCommonParam0		=	(  COMMON_PARAM  *  )p0;
	 COMMON_PARAM		*	pCommonParam1		=	(  COMMON_PARAM  *  )p1;
	 //
	 //
	 MIS_MSGU			*	pMsg				=	(  MIS_MSGU  *  )pCommonParam1->p1;
	 unsigned  int			uiMsgLen			=	(  unsigned  int  )pCommonParam1->p2;
	 //  
	 MIS_MSGU			*	pMsgElem			=	(  MIS_MSGU  *  )pQElem;
	 //
	 BOOL					bMatched			=	FALSE;
	 //
	 HWND					hWnd				=	NULL;
	 //  CDlgTalk			*	pDlg				=	NULL;


	 if  (  pMsgElem->uiType  ==  CONST_misMsgType_talkingFriend_qmc  )  {

		 PostMessage(  pMsgElem->talkingFriend_qmc.hWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_broadcastRecorderStatus,  0  );  

	 }

	 return  0;
 }


  //
  __declspec(  dllexport  )   int  broadcastRecorderStatus(  void  *  pQyMcParam  )
{
	 int						iErr								=	-1;
	 QY_MC					*	pQyMc								=	(  QY_MC  *  )pQyMcParam;
	 COMMON_PARAM				commonParam0;
	 COMMON_PARAM				commonParam1;
	 MIS_CNT				*	pMisCnt								=	NULL;
	 int						iRet;
	 //     
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	 if  (  !(  pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  )  )  )  goto  errLabel;
	 
	 MACRO_makeCommonParam3(  0,  (  void  *  )0,  0,  commonParam0  );
	 MACRO_makeCommonParam3(  (  void  *  )0,  0,  0,  commonParam1  );
	 //
	 iRet  =  qTraverse(  &pMisCnt->talkingFriendQ,  tmpHandler_broadcastRecorderStatus,  &commonParam0,  &commonParam1  );  
	 if  (  iRet  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return  iErr;
 }
