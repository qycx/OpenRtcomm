
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
#include	"isCliHelpPublic.h"




//
//__declspec(  dllexport  )  int  getDescByIdInfo(  void  *  p0,  QY_MESSENGER_ID  *  pIdInfo,  TCHAR  *  talkerDesc,  unsigned  int  uiCnt_talkerDesc,  TCHAR  *  displayName,  unsigned  int  uiCnt_displayName  )
__declspec(  dllexport  )  int  getDescByIdInfo(  PARAM_getDesc  *  pParam,  QY_MESSENGER_ID  *  pIdInfo,  TCHAR  *  talkerDesc,  unsigned  int  uiCnt_talkerDesc,  TCHAR  *  displayName,  unsigned  int  uiCnt_displayName  )
{
		int  iErr  =  -1;
		QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
		CCtxQmc  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
		
		//
		if  (  !pIdInfo  ||  !pIdInfo->ui64Id  )  return  -1;

		//
		PARAM_getDesc  param  =  {0};
		if  (  pParam  )  param  =  *pParam;
		
		//
		if  (  param.iTaskId  )  {
			int  index_taskInfo  =  getQmcTaskInfoIndexBySth(  pProcInfo,  param.iTaskId  );
			QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  index_taskInfo  );
			if  (  !pTaskInfo  )  goto  errLabel;
			QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;
			if  (  pTc->common.uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;
			//
			int  i;
			DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from;
			pActiveMem_from = mynull;
			for  (  i  =  0;  i  <  pTc->videoConference.usCntLimit_activeMems_from;  i  ++  )  {
				pActiveMem_from=&pTc->videoConference.activeMems_from[i];
				if  (  pActiveMem_from->avStream.idInfo.ui64Id  ==  pIdInfo->ui64Id  )  break;
			}
			if  (  i  ==  pTc->videoConference.usCntLimit_activeMems_from  )  goto  errLabel;
			//
			//  
			safeTcsnCpy(  pActiveMem_from->desc,  talkerDesc,  uiCnt_talkerDesc  );
			safeTcsnCpy(  pActiveMem_from->desc,  displayName,  uiCnt_displayName  );
			//
			iErr  =  0;  goto  errLabel;
		}

		{

		//
		void					*	pDb				=		NULL;
		//	
		CQnmDb						db;
		if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
		pDb  =  db.m_pDbMem->pDb;
	
		//
		QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
		if  (  !pDbFuncs  )  goto  errLabel;
		QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

		//
		QY_MESSENGER_REGINFO  regInfo;
		//
		int  iDbType  =  CONST_dbType_myDb;
		if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pDb,  iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  _T(  ""  ),  pIdInfo,  0,  &regInfo  )  )  {
			memset(  &regInfo,  0,  sizeof(  regInfo  )  );
		}
		//
		MY_REG_DESC  desc;
		//
		regInfo2Desc(  0,  &regInfo,  &desc,  talkerDesc,  uiCnt_talkerDesc,  displayName,  uiCnt_displayName   );  

		}

		//
		iErr  =  0;

errLabel:

		return  iErr;
}


