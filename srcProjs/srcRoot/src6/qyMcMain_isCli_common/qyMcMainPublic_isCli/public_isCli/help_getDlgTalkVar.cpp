
#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"

#ifdef  __SUPPORT_HTMLEDIT__
//	#include	"myHtmlEditCtrl.h"
#endif

#include	"tmpCeLib.h"

#include	"qyOpenShellCommon.h"
#include	"DlgTalkProc.h"
#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"

#include	<assert.h>
#ifndef  __WINCE__
	//  #include	"qyPs.h"
#endif
#include	"qmcDxSurfacePublic.h"
#include	"qmcConferenceWall.h"
//  #include	"dlgProgress.h"
#include	"isCliHelpPublic.h"
#include	"qmcCmdProc.h"
#include	"isCmdConst.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include	"wallTalkers.h"

#include	"qmcSharePublic.h"
#include	"amCapPublic.h"
#include	"funcsforIsCliHelp.h"





//
void  *  CHelp_getDlgTalkVar::getVar(  HWND  hDlgTalk,  LPCTSTR  hint  )
{
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	//  2017/09/24
	if  (  !hint  )  hint  =  _T(  ""  );

	//
	DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )pProcInfo->tmp_getDlgTalkVar(  hDlgTalk  );
	if  (  !pDlgTalkVar  )  return  NULL;

	if  (  sync(  &pDlgTalkVar->syncFlgs.lCnt_getDlgVar,  hint  )  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "help_getDlgTalkVar::getVar failed, sync failed"  )  );
		#endif
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "help_getDlgTalkVar::getVar failed, sync failed, %I64u, tn %d, lCnt_getDlgTalkVar %d"  ),  pDlgTalkVar->addr.idInfo.ui64Id,  pDlgTalkVar->addr.uiTranNo_shadow,  pDlgTalkVar->syncFlgs.lCnt_getDlgVar  ); 

		return  NULL;
	}

	#ifdef  __DEBUG__
			//  traceLog((TCHAR*)  _T(  "help_getDlgTalkVar::getVar, lCnt %d"  ),  pDlgTalkVar->syncFlgs.lCnt_getDlgVar  );
			if  (  pDlgTalkVar->syncFlgs.lCnt_getDlgVar  >=  4  )  {
				if  (  !hint  )  {
					int  i  =  1;
				}
			}
			//
		//qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "help_getDlgTalkVar::getVar failed, %I64u, tn %d, bShouldQuit"  ),  pDlgTalkVar->addr.idInfo.ui64Id,  pDlgTalkVar->addr.uiTranNo_shadow  ); 

	#endif

	//
	return  pDlgTalkVar;
}



/////////
//
int  getAvBtnStatus(  DLG_TALK_var  *  pMgrVar  )
{
	int  iErr  =  -1;

	if  (  !pMgrVar  )  return  -1;

	int  iAvBtnStatus  =  0;

	if  (  !pMgrVar->av.taskInfo.bTaskExists  )  {
	   DWORD  dwTickCnt  =  GetTickCount(  );
	   int  iDiffInMs  =  dwTickCnt  -  pMgrVar->guiData.av.canceledTask_av.dwTickCnt_recentlyRefreshed;

	   if  (  abs(  iDiffInMs  )  <  CONST_intervalInMs_task_av_re_accept  )  {
		   iAvBtnStatus  =  CONST_avBtnStatus_re_accept;
	   }
	   else  {
		     iAvBtnStatus  =  CONST_avBtnStatus_av;
	   }
	}
	else  {
		iAvBtnStatus  =  CONST_avBtnStatus_cancel;
	}

	iErr  =  0;
errLabel:
	return  iErr  ?  iErr  :  iAvBtnStatus;
}





