
#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	"qymcMainCommon.h"
#include	"myresource.h"


#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_iscli.h"

#ifdef  __SUPPORT_HTMLEDIT__
	#include	"myHtmlEditCtrl.h"
#endif

#include	"tmpCeLib.h"

#include	"qyOpenShellCommon.h"
//#include	"DlgTalk.h"
#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"

//#include	"DlgInstantAssistant.h"

#include	<assert.h>
#ifndef  __WINCE__
	//#include	"qyPs.h"
#endif
#include	"qmcDxSurfacePublic.h"
#include	"qmcConferenceWall.h"

#include	"isCliHelpPublic.h"
#include	"qmcCmdProc.h"
#include	"isCmdConst.h"

#include	"funcsForIsCliHelp.h"
#include	"isCliD3dPublic.h"
#include	"wallTalkers.h"

//#include	"DlgMsgTool.h"

#include	"qmcCommFunc_isCli.h"
#include	<time.h>



//  2015/02/16
__declspec(  dllexport  )  int  sendNotification(  LPCTSTR  str,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_dst  )
{
	int  iErr  = -1;
	QY_MC				*	pQyMc				=	QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProcInfo			=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	MIS_CNT					*	pMisCnt				=	NULL;
	pMisCnt  =  (  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;

	//
	if  (  !pIdInfo_dst  ||  !pIdInfo_dst->ui64Id  )  return  -1;

	//
	unsigned  char		ucFlg;
	IM_HTML_CONTENT		content;
	int					lenInBytes;
	//
	ucFlg  =  0;
	//
	memset(  &content,  0,  sizeof(  content  )  );
	content.uiType  =  CONST_imCommType_htmlContent;
	//  2015/02/16
	//content.ucbNotification  =  TRUE;
	if  (  pIdInfo_logicalPeer  )  {
		content.idInfo_logicalPeer.ui64Id  =  pIdInfo_logicalPeer->ui64Id;
	}
	//
	lstrcpyn(  content.wBuf,  str,  mycountof(  content.wBuf  )  );
	lenInBytes  =  offsetof(  IM_HTML_CONTENT,  wBuf  )  +  (  lstrlen(  content.wBuf  )  +  1  )  *  sizeof(  content.wBuf[0]  );
	//
	MSG_ROUTE	route;
	memset(  &route,  0,  sizeof(  route  )  );
	//
	route.idInfo_from.ui64Id  =  pMisCnt->idInfo.ui64Id;
	//
	{
		route.idInfo_to.ui64Id  =  pIdInfo_dst->ui64Id;

		MACRO_prepareForTran(  );

		if  (  postMsg2Mgr_mc(  pMisCnt,  &route,  CONST_misMsgType_talk,  ucFlg,  CONST_qyCmd_talkTo,  tStartTran,  uiTranNo,  0,  (  char  *  )&content,  lenInBytes,  NULL,  pIdInfo_dst,  0,  NULL,  FALSE  )  )  goto  errLabel;

	}

	iErr  =  0;
errLabel:

	return  iErr;
}
