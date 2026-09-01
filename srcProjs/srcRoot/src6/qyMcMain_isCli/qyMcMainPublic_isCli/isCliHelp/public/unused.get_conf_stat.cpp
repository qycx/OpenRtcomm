
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


//
 //
__declspec(  dllexport  )  int  get_conf_stat(  HWND  hDlgTalk_mgr  )
 {
	 int  iErr  =  -1;
	 QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 //
	 CFile					file;
	 TCHAR  fileName[MAX_PATH]  =  _T(  ""  );
	 char  timeStr[32];

	 //
	 showInfo_open0(  0,  0,  _T(  "get_conf_stat enters"  )  );

	 //
	 CHelp_getDlgTalkVar  help_getDlgTalkVar_mgr;
	 DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar_mgr.getVar(  hDlgTalk_mgr  );
	 if  (  !pMgrVar  )  return  -1;
	 if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  return  -1;

	 MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMgrVar->pMisCnt;
	 if  (  !pMisCnt  )  {
		 return  -1;
	 }

	 //
	 if  (  !pMgrVar->av.taskInfo.bTaskExists  )  return  -1;
	 if  (  !pMgrVar->av.taskInfo.ucbStarter  )  return  -1;

	 //
	 QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pMgrVar->av.iIndex_sharedObj_localAv  );
	 if  (  !pSharedObj  )  return  -1;
	 SHARED_OBJ_USR  *  pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  pMgrVar->av.iIndex_usr_localAv  );
	 if  (  !pSharedObjUsr  )  return  -1;

	 TASK_respInfo  *  pRespInfo  =  get_respInfo(  pProcInfo,  pMgrVar->av.taskInfo.iIndex_taskInfo  );
	 if  (  !pRespInfo  )  return  -1;

	 //
	 time_t  tEnd;  time(  &tEnd  );  
	
	 //
	 TCHAR  talkerDesc[128];
	 getTalkerDesc(  pMgrVar->addr.idInfo,  talkerDesc,  mycountof(  talkerDesc  ),  0,  0  );  

	 //
	 _sntprintf(  fileName,  mycountof(  fileName  ),  _T(  "%s%s"  ),  pProcInfo->cfg.policy.dirToSaveMsg,  _T(  CONST_subDir_conf  )  );
	 if  (  !bDir(  fileName  )  )  {
		 BOOL  bRet  =  CreateDirectory(  fileName,  NULL  );
		 if  (  !bRet  &&  GetLastError(  )  !=  ERROR_ALREADY_EXISTS  )  {
					//qyDisplayLastError(  "Creating msgDir"  );  
					goto  errLabel;		   
		 }
	 }	 		   
	 //
	 _sntprintf(  fileName,  mycountof(  fileName  ),  _T(  "%s%s_%s_%I64u"  ),  fileName,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_stat  ),  talkerDesc,  pMgrVar->addr.idInfo.ui64Id   );
	 getTimelStr(  pMgrVar->av.taskInfo.tStartTime_org,  timeStr,  mycountof(  timeStr  )  );
	 _sntprintf(  fileName,  mycountof(  fileName  ),  _T(  "%s_%S.xls"  ),  fileName,  timeStr  );

	 //
	 if  (  !file.Open(  CString(  fileName  ),  CFile::modeCreate | CFile::modeWrite  )  )  goto  errLabel;
	 	 
	 //
	 char  buf[128];
	 buf[0]  =  (  char  )0xff;  buf[1]  =  (  char  )0xfe;
	 file.Write(  buf,  2  );
									
	 //
#ifdef  __DEBUG__
		traceLog(  _T(  "start to print conf state"  )  );
#endif

	 //
	 int  tmp_usCnt  =  min(  pRespInfo->usCnt,  MAX_taskRespInfoMems  );
	 //
	 int  ii;
	 for  (  ii  =  0;  ii  <  tmp_usCnt;  ii  ++  )  {
		  TASK_respInfo_mem  *  pMem  =  &pRespInfo->mems[ii];
		  if  (  !pMem->idInfo.ui64Id  )  continue;
		  //
#if  0
		  TCHAR  talkerDesc[128];
		  getDescByIdInfo(  0,  &pMem->idInfo,  talkerDesc,  mycountof(  talkerDesc  ),  0,  0  );  
#endif
		  //
		  CONF_logs  *  pLogs  =  &pMem->var.logs;
		  //
		  if  (  pMem->idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
			  pLogs->stat.tTime_join  =  pMgrVar->av.taskInfo.tStartTime_org;
			  pLogs->stat.tTime_leave  =  tEnd;
			  pLogs->stat.iTimeInS_inConf  =  tEnd  -  pMgrVar->av.taskInfo.tStartTime_org;
			  continue;
		  }
		  //
		  int  j;
		  for  (  j  =  0;  j  <  pLogs->usCnt;  j  ++  )  {
			   CONF_log  *  pLog  =  &pLogs->mems[j];
			   //
			#if  0
			   //getTimeStr(  pLog->tTime,  timeStr,  mycountof(  timeStr  )  );
			   getTimelStr(  pLog->tTime,  timeStr,  mycountof(  timeStr  )  );
			   //
			   traceLog(  _T(  "%s %I64u %S %s"  ),  talkerDesc,  pMem->idInfo.ui64Id,  timeStr,  qyGetDesByType1(  CONST_taskRespInfoMemStateTable,  pLog->iState  )  );
			   //
			   _ftprintf(  fp,  _T(  "%s %I64u %S %s\n"  ),  talkerDesc,  pMem->idInfo.ui64Id,  timeStr,  qyGetDesByType1(  CONST_taskRespInfoMemStateTable,  pLog->iState  )  );
			#endif
			   //
		  }

		  //
		  if  (  pLogs->usCnt  )  {
			  CONF_log  *  pLog  =  &pLogs->mems[0];
			  if  (  pLog->iState  ==  CONST_taskRespInfoMemState_join  )  pLogs->stat.tTime_join  =  pLog->tTime;
			  CONF_log  *  pLast  =  &pLogs->mems[pLogs->usCnt  -  1];
			  switch  (  pLast->iState  )  {
					  case  CONST_taskRespInfoMemState_leave:
					  case  CONST_taskRespInfoMemState_notInConf:						  
					  case  CONST_taskRespInfoMemState_offline:
						    pLogs->stat.tTime_leave  =  pLast->tTime;
						    break;
					  default:
						      pLogs->stat.tTime_leave  =  tEnd;
							  break;
			  }
			  //
			  BOOL  bStart  =  FALSE;
			  time_t  tStart  =  0;
			  int  iTimeInS  =  0;
			  int  i;
			  for  (  i  =  0;  i  <  pLogs->usCnt;  i  ++  )  {
				   CONF_log  *  pLog  =  &pLogs->mems[i];
				   if  (  !bStart  )  {
					   switch  (  pLog->iState  )  {
							   case  CONST_taskRespInfoMemState_join:
							   case  CONST_taskRespInfoMemState_ok:
							   case  CONST_taskRespInfoMemState_warning:
								     bStart  =  TRUE;
									 tStart  =  pLog->tTime;
									 break;
							   default:
									   break;
					   }
					   }
				   else  {
					     switch  (  pLog->iState  )  {
								 case  CONST_taskRespInfoMemState_leave:
								 case  CONST_taskRespInfoMemState_notInConf:
								 case  CONST_taskRespInfoMemState_offline:
									   iTimeInS  +=  pLog->tTime  -  tStart;
									   bStart  =  FALSE;
									   break;
								 default:
										 break;
						 }

				   }
			  }
			  if  (  bStart  )  {				
				  iTimeInS  +=  tEnd  -  tStart;									
				  bStart  =  FALSE;				
			  }
			  pLogs->stat.iTimeInS_inConf  =  iTimeInS;			  
		  }
	 }

	 //
	 int  iTimeInS_conf  =  tEnd  -  pMgrVar->av.taskInfo.tStartTime_org;
	 if  (  !iTimeInS_conf  )  goto  errLabel;
	 //
	 int  iTotal_join  =  0;
	 int  iTotal_leave  =  0;
	 //
	 for  (  ii  =  0;  ii  <  tmp_usCnt;  ii  ++  )  {
		  TASK_respInfo_mem  *  pMem  =  &pRespInfo->mems[ii];
		  //
		  CONF_logs  *  pLogs  =  &pMem->var.logs;
		  //
		  //if  (  pLogs->stat.tTime_join  )  iTotal_join  ++  ;
		  //
		  int  percent_inConf  =  pLogs->stat.iTimeInS_inConf  *  100  /  iTimeInS_conf;
		  //
		  if  (  pLogs->stat.iTimeInS_inConf  )  {
			  //
			  if  (  percent_inConf  >  1  )  {		//  2017/10/28
				  iTotal_join  ++  ;
			  }
			  //
			  if  (  percent_inConf  <  60  )  {
				  iTotal_leave  ++  ;
			  }
		  }
	 }

	 //
	 TCHAR  tBuf[1024];
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "会议统计\r\n"  )  );
	 file.Write(  tBuf,  lstrlen(  tBuf  )  *  sizeof(  TCHAR  )  );
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\t%s\t%s\t%s\t%s\t%s\r\n"  ),  _T(  "应有人数"  ),  _T(  "参会人数"  ),  _T(  "中途离开"  ),  _T(  "起始时间"  ),  _T(  "结束时间"  ),  _T(  "总时长(s)"  )  );
	 file.Write(  tBuf,  lstrlen(  tBuf  )  *  sizeof(  TCHAR  )  );
	 
	 //
	 char  tStartStr[128];  getTimelStr(  pMgrVar->av.taskInfo.tStartTime_org,  tStartStr,  mycountof(  tStartStr  )  );
	 char  tStart_displayBuf[128];  qyDisplaylTime(  tStartStr,  tStart_displayBuf,  mycountof(  tStart_displayBuf  )  );
	 char  tEndStr[128];  getTimelStr(  tEnd,  tEndStr,  mycountof(  tEndStr  )  );
	 char  tEnd_displayBuf[128];  qyDisplaylTime(  tEndStr,  tEnd_displayBuf,  mycountof(  tEnd_displayBuf  )  );  
	 //
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d\t%d\t%d\t%S\t%S\t%d\r\n"  ),  (  int  )pRespInfo->usCnt,  iTotal_join,  iTotal_leave,  tStart_displayBuf,  tEnd_displayBuf,  iTimeInS_conf  );
	 file.Write(  tBuf,  lstrlen(  tBuf  )  *  sizeof(  TCHAR  )  );

	 //
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\r\n\r\n\r\n"  )  );
	 file.Write(  tBuf,  lstrlen(  tBuf  )  *  sizeof(  TCHAR  )  );


	 //
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\t%s\t%s\t%s\t%s\t%s\r\n"  ),  _T(  "姓名"  ),  _T(  "ID"  ),  _T(  "是否参会"  ),  _T(  "入会时间"  ),  _T(  "离开时间"  ),  _T(  "参会时长(s)"  )  );
	 file.Write(  tBuf,  lstrlen(  tBuf  )  *  sizeof(  TCHAR  )  );

	 //
	 for  (  ii  =  0;  ii  <  pRespInfo->usCnt;  ii  ++  )  {
		  TASK_respInfo_mem  *  pMem  =  &pRespInfo->mems[ii];
		  if  (  !pMem->idInfo.ui64Id  )  continue;
		  //
		  TCHAR  talkerDesc[128]  =  _T(  ""  );
		  getDescByIdInfo(  0,  &pMem->idInfo,  talkerDesc,  mycountof(  talkerDesc  ),  0,  0  );  
		  //
		  CONF_logs  *  pLogs  =  &pMem->var.logs;
		  //
		  char  tStartStr[128]  =  "";  
		  char  tStart_displayBuf[128]  =  "";  
		  if  (  pLogs->stat.tTime_join  )  {
			  getTimelStr(  pLogs->stat.tTime_join,  tStartStr,  mycountof(  tStartStr  )  );		  
			  qyDisplaylTime(  tStartStr,  tStart_displayBuf,  mycountof(  tStart_displayBuf  )  );
		  }
		  char  tEndStr[128]  =  "";  
		  char  tEnd_displayBuf[128]  =  "";  
		  if  (  pLogs->stat.tTime_leave  )  {
			  getTimelStr(  pLogs->stat.tTime_leave,  tEndStr,  mycountof(  tEndStr  )  );			
			  qyDisplaylTime(  tEndStr,  tEnd_displayBuf,  mycountof(  tEnd_displayBuf  )  );  
		  }
		  //
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\t%I64u\t%s\t%S\t%S\t%d\r\n"  ),  talkerDesc,  pMem->idInfo.ui64Id,  pLogs->stat.tTime_join  ?  _T(  "y"  )  :  _T(  "n"  ),  tStart_displayBuf,  tEnd_displayBuf,  pLogs->stat.iTimeInS_inConf  );
		  file.Write(  tBuf,  lstrlen(  tBuf  )  *  sizeof(  TCHAR  )  );

	 }

	 	 //
#ifdef  __DEBUG__
		traceLog(  _T(  "end printing conf state"  )  );
#endif


	 iErr  =  0;
errLabel:

	 
	 //
	 showInfo_open0(  0,  0,  _T(  "get_conf_stat leaves"  )  );

	 //
	 return  iErr;
 }
