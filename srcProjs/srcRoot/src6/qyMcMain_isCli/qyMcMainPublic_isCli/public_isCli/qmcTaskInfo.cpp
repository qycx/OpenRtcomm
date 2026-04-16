

#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
//  #include	"myfourcc.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

#include	"qmcVideoCapture_rtsp.h"

#include	"isCliHelpPublic.h"
//#include	"rtspCliHelpPublic.h"
#include	"qmcTaskInfo.h"
#include	"funcsForIsCliHelp.h"

//
int  getSize_QMC_TASK_INFO(  )
{
	return  sizeof(  QMC_TASK_INFO  );
}



 //


//  2014/09/24
 /*
 BOOL  bNotExists_taskInSharedObjs(  MC_VAR_isCli  *  pProcInfo,  int  iTaskId  )
{
	BOOL	bRet  =  FALSE;
	int  i;
	BOOL	bFound  =  FALSE;

	if  (  !pProcInfo  )  return  FALSE;
	
	//
	if  (  !iTaskId  )  return  TRUE;

	//
	for  (  i  =  0;  i  <  pProcInfo->cfg.usMaxCnt_pSharedObjs;  i  ++  )  {
		 //
		 if  (  bFound  )  break;
		 //
		 QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  i  );
		 if  (  !pSharedObj  )  continue;
		 if  (  !pSharedObj->bUsed  )  continue;
		 int  j;
		 for  (  j  =  0;  j  <  mycountof(  pSharedObj->usrs  );  j  ++  )  {
			  SHARED_OBJ_USR    *  pUsr  =  &pSharedObj->usrs[j];
			  if  (  pUsr->iTaskId  ==  iTaskId  )  {
				  bFound  =  TRUE;  break;
			  }
		 }
	}

	if  (  !bFound  )  bRet  =  TRUE;

errLabel:
	return  bRet;
}
*/

 //
 /*
 int  tmpHandler_bExists_taskInTaskQ(  void  *  p0,  void  *  p1,  void  *  pMsgParamElem  )
{
	int				iErr					=	-1;
	//  p0
	int				iTaskId					=	(  int  )p1;
	MIS_MSGU	*	pMsg					=	(  MIS_MSGU  *  )pMsgParamElem;
	//

	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_task:  {
				  if  (  iTaskId  ==  pMsg->task.iTaskId  )  {
					  iErr  =  1;  goto  errLabel;
				  }
				  }
				  break;
			default:
					break;					
	}

	iErr  =  0;
errLabel:
	return  iErr;
 }

 BOOL  bNotExists_taskInTaskQs(  MC_VAR_isCli  *  pProcInfo,  int  iTaskId  )
 {
	BOOL	bRet  =  FALSE;

	int  tmpiRet;

	//
	if  (  !pProcInfo  )  return  FALSE;

	//
	if  (  !iTaskId  )  return  TRUE;

	tmpiRet  =  pProcInfo->processQ_media.qTraverse(  tmpHandler_bExists_taskInTaskQ,  0,  (  void  *  )iTaskId  );
	if  (  tmpiRet  <  0  )  goto  errLabel;
	if  (  tmpiRet  >  0  )  {
		bRet  =  FALSE;  goto  errLabel;
	}
	
	//
#if  0
	tmpiRet  =  pProcInfo->processQ_robot.qTraverse(  tmpHandler_bExists_taskInTaskQ,  0,  (  void  *  )iTaskId  );
	if  (  tmpiRet  <  0  )  goto  errLabel;
	if  (  tmpiRet  >  0  )  {
		bRet  =  FALSE;  goto  errLabel;
	}
#endif

	//
	bRet  =  TRUE;

errLabel:
	return  bRet;

 }
 */

 //
 int  getVal_bExists_taskInWnd(  QY_MC  *  pQyMc,  int  iTaskId,  HWND  hWnd_task,  BOOL  *  pbExists  )
 {
	 int  iErr  =  -1;
	 BOOL  bExists  =  FALSE;

	 if  (  !pQyMc  )  return  -1;

	 if  (  !pbExists  )  return  -1;

	 //
	 if  (  !iTaskId  
		 ||  !IsWindow(  hWnd_task  )  )  
	 {
		 iErr  =  0;  goto  errLabel;
	 }
	 
	 //
	 _ASSERT(  pQyMc->gui.ctx_gui_thread.dwThreadId9  ==  GetCurrentThreadId(  )  );

	 
	 //  以下函数通常被gui调用。在exitVar时，因为窗口都已经被关闭，所以调用不会有副作用
	 QY_WMBUF_COMM	wmBuf;
	 	 								
	 memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );	 
	 wmBuf.uiType  =  CONST_qyWmParam_chkTask;								
	 wmBuf.u.chkTask.iTaskId  =  iTaskId;
	 if  (  CONST_qyWmRc_ok  !=  SendMessage(  hWnd_task,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  )  )  goto  errLabel;
	 bExists  =  !wmBuf.u.chkTask.bNotExists;

	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *pbExists  =  bExists;
	 }
	 return  iErr;

 }



 //
void  *  newQmcTaskData(  unsigned  int  uiType  )
{
	int						iErr	=	-1;
	QMC_taskData_common  *	p		=  NULL;
	int						len		=  0;

	switch  (  uiType  )  {
			case  CONST_taskDataType_conf:
				  len  =  sizeof(  QMC_taskData_conf  );
				  break;
			case  CONST_taskDataType_transferFile:
				  len  =  sizeof(  QMC_taskData_transferFile  );
				  break;
			default:
				    TCHAR  tBuf[128];
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "newQmcTaskData failed, unknown type %d"  ),  uiType  );
					showInfo_open0(  0,  0,  tBuf  );
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  tBuf  );
					#endif
					goto  errLabel;
					break;
	}
	p  =  (  QMC_taskData_common  *  )mymalloc(  len  );
	if  (  !p  )  return  NULL;
	memset(  p,  0,  len  );
	p->uiType  =  uiType;

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		freeQmcTaskData(  p  );  p  =  NULL;
	}
	return  p;
}



 //
 void  freeQmcTaskData(  void  *  pTaskData  )
 {
	 if  (  !pTaskData  )  return;
	 QMC_taskData_common  *  p  =  (  QMC_taskData_common  *  )pTaskData;

	 switch  (  p->uiType  )  {
			 case  CONST_taskDataType_conf:  {
				   QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )p;
				   MACRO_safeFree(  pTc->pMems  );
				   }
				   break;
			 case  CONST_taskDataType_transferFile: {
				   QMC_taskData_transferFile * pTf=(QMC_taskData_transferFile*)p;
				   //
				   }
				   break;
			 default:
					break;
	 }

	 myfree(  pTaskData  );
	 return;
 }


 //
 int  newTaskInfoIndex(  CCtxQmc  *  pProcInfo,  unsigned  int  uiTaskDataType,  HWND  hWnd_task,  int  iTaskId,  LPCTSTR  hint  )
 {
	 int				iErr  =  -1;

	 if  (  !pProcInfo  )  return  -1;
	 if  (  !hint  )  hint  =  _T(  ""  );

	 //
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return  -1;
	 //
	 QMC_taskData_common	*	pTaskData  =  NULL;
	 QMC_TASK_INFO  *  pTaskInfo  =  NULL;;
	 int  i;

	 //
	 //if  (  !IsWindow(  hWnd_task  )  )  return  -1;
	 //
	 if  (  !iTaskId  )  {
		 traceLogA(  (char*)"newTaskInfoIndex failed, iTaskId is 0");
		 showInfo_open0(  0,  0,  _T(  "newTaskInfoIndex failed, iTaskId is 0"  )  );
		 return  -1;
	 }

	 //
	 //	 			
	 i = getQmcTaskInfoIndexBySth(pProcInfo, iTaskId);		
	 if(i>=0)            
	 {
				traceLogA(  (char*)"newTaskInfoIndex failed, iTaskId already has a taskInfo");
				showInfo_open0(0,0,_T(  "newTaskInfoIndex failed, iTaskId already has a taskInfo")  );
				return -1;            
	 }

	 //  Note: start from 1.
	 for  (  i  =  1;  i  <  pProcInfo->cfg.usMaxCnt_taskInfos;  i  ++  )  {
		  pTaskInfo  =  (  QMC_TASK_INFO  *  )pProcInfo->getQmcTaskInfoByIndex(  i  );
		  if  (  !pTaskInfo  )  continue;

		  if  (  !pTaskInfo->bUsed  )  break;
	 }
	 if  (  i  ==  pProcInfo->cfg.usMaxCnt_taskInfos  )  {
		 showInfo_open0(  0,  0,  _T(  "newTaskInfoIndex failed, no free taskInfo"  )  );
		 goto  errLabel;
	 }

	 //
	 MACRO_qyAssert(  !pTaskInfo->var.pTaskData,  _T(  "taskData is not null"  )  );

	 //
	 pTaskData  =  (  QMC_taskData_common  *  )newQmcTaskData(  uiTaskDataType  );
	 if  (  !pTaskData  )  goto  errLabel;

	 //
	 memset(  &pTaskInfo->var,  0,  sizeof(  pTaskInfo->var  )  );
	 pTaskInfo->var.hWnd_task  =  hWnd_task;
	 pTaskInfo->var.iTaskId  =  iTaskId;
	 pTaskInfo->var.dwTickCnt_start = myGetTickCount(NULL);
	 pTaskInfo->var.dwTickCnt_recv_lastRefreshed = myGetTickCount(NULL);


	 //
	 pTaskInfo->var.pTaskData  =  pTaskData;  pTaskData  =  NULL;

	 //
	 //  pTaskInfo->uiTranNo  =  getuiNextTranNo(  0,  0,  0  );
	 //syncMtCnt_start(  &pTaskInfo->syncMtCnt,  getuiNextTranNo  );
	 //
	 pTaskInfo->bUsed  =  TRUE;

	 //
	 TCHAR  tBuf[128];
	 _sntprintf(  tBuf,  mycountof(tBuf),  _T(  "newTaskInfovvvvvv %d . %s"  ),  i,  hint  );
	 showInfo_open0(0, 0, tBuf);
#ifdef  __DEBUG__
	 traceLog((TCHAR*)  _T(  "newTaskInfo, %d. %s"  ),  i,  hint  );
#endif

	 //
	 iErr  =  0;

errLabel:

	 if  (  pTaskData  )  {
		 freeQmcTaskData(  pTaskData  );
	 }

	 return  iErr  ?  iErr  :  i;
 }


 //
 int  freeTaskInfo(  CCtxQmc  *	pProcInfo,  int  index_taskInfo,  LPCTSTR  hint  )
 {
	 int				iErr  =  -1;

	 if  (  !pProcInfo  )  return  -1;	 
	 if  (  index_taskInfo  <  0  ||  index_taskInfo  >=  pProcInfo->cfg.usMaxCnt_taskInfos  )  return  -1;
	 if(  !hint  )  hint  =  _T(  ""  );

	 //	 	
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "freeTaskInfo %d enters. %s"  ),  index_taskInfo,  hint  );

	 //
	 QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )pProcInfo->getQmcTaskInfoByIndex(  index_taskInfo  );
	 if  (  !pTaskInfo  )  return  0;
	 //
	 if  (  !pTaskInfo->bUsed  )  return  0;

#if  0	//  2014/09/29
	 //
	 pTaskInfo->uiTranNo  =  0;
	 //
	 if  (  pTaskInfo->lCnt_used  )  return  -1;
#endif
	 //  2014/09/29
	 unsigned  int  tn  =  0;
	 CQySyncObj  syncObj;
	 //if  (  syncMtCnt_wLock_noWait(  &pTaskInfo->syncMtCnt,  NULL,  &syncObj,  &tn  )  )  return  -1;

	 //
	 removeTask(pTaskInfo->var.iTaskId);

	 //
	 freeQmcTaskData(  pTaskInfo->var.pTaskData  );  pTaskInfo->var.pTaskData  =  NULL;

	 //
	 memset(  &pTaskInfo->var,  0,  sizeof(  pTaskInfo->var  )  );

	 //
	 pTaskInfo->bUsed  =  FALSE;
	 	 
	 //	 	
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "freeTaskInfo %d leaves ok."  ),  index_taskInfo  );


	 return  0;

 }


 //
 	void * getQmcTaskInfoByIndex(CCtxQmc * pProcInfo, int index)
		{

			//
			QMC_TASK_INFO* pTaskInfos = (QMC_TASK_INFO*)pProcInfo->pQmcTaskInfos;

			if (index < 0 || index >= pProcInfo->cfg.usMaxCnt_taskInfos) return NULL;

			QMC_TASK_INFO * pTaskInfo = (QMC_TASK_INFO*)&pTaskInfos[index];

			return pTaskInfo;
		}




		//
		//
		int getQmcTaskInfoIndexBySth(CCtxQmc *pProcInfo, int iTaskId)
		{
			int i;
			QMC_TASK_INFO *pTaskInfo=NULL;

			if (iTaskId == 0) return -1;

			for (i = 0; i < pProcInfo->cfg.usMaxCnt_taskInfos; i++)
			{
				pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo,i);
				if (!pTaskInfo->bUsed) continue;
				if (pTaskInfo->var.iTaskId == iTaskId) break;
			}
			if (i == pProcInfo->cfg.usMaxCnt_taskInfos) return -1;

			return i;

		}

		//
		int qmcTaskInfo_setClosed(CCtxQmc * pProcInfo, int index_taskInfo, LPCTSTR hint)
        {
			if  (  !hint  )  hint  =  _T(  ""  );

			//
			QMC_TASK_INFO *pTaskInfo = NULL;

			pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
			if (pTaskInfo == NULL) return -1;

			if (!pTaskInfo->bUsed) return -1;

			//
			CCtxQyMc* pQyMc = g_pQyMc;
			DWORD  dwThreadId = GetCurrentThreadId();
			if (pQyMc->gui.ctx_gui_thread.dwThreadId9 != dwThreadId) {
#ifdef  __DEBUG__
				//
				int  ii = 0;
#endif
			}



			//
			TCHAR  tBuf[128];
			_sntprintf(tBuf,mycountof(tBuf),_T(  "qmcTaskInfo_setClosed %d. %s"  ),  index_taskInfo,  hint  );
			showInfo_open0(0, 0, tBuf);
#ifdef  __DEBUG__
			traceLog((TCHAR*)  tBuf  );
#endif
			
			//
			removeTask(pTaskInfo->var.iTaskId);
			//
			pProcInfo->gui_notify_clearTask(pTaskInfo->var.iTaskId);

			//
			showInfo_open0(0, 0, _T("qmcTaskInfo_setClosed: after removeTask"));

			//
			if (pTaskInfo->var.bClosed) return 0;
			pTaskInfo->var.bClosed = true;
			return 0;
		}

		bool qmcTaskInfo_bAlive(CCtxQmc * pProcInfo, int index_taskInfo)
        {
			bool bRet = false;
			QMC_TASK_INFO *pTaskInfo = NULL;

			pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, index_taskInfo);
			if (pTaskInfo == NULL) goto errLabel;

			if (!pTaskInfo->bUsed) goto errLabel;

			if (pTaskInfo->var.bClosed) goto errLabel;

			{
				MIS_MSGU& tmp_pMsg = pTaskInfo->var.pTaskData->msgU;

				if (tmp_pMsg.uiType != CONST_misMsgType_task) goto errLabel;

				if (!bTaskAlive(tmp_pMsg.task.iStatus)) goto errLabel;
			}

			bRet = true;

			errLabel:
			return bRet;
		}



 //  2014/09/24. 
 int  freeTaskInfos(  CCtxQmc  *  pProcInfo  )
 {
	 int				iErr  =  -1;
	 int				i;
	 
	 if  (  !pProcInfo  )  return  -1;
	 QY_MC  *  pQyMc  =  (  QY_MC  *  )pProcInfo->pQyMc;
	 if  (  !pQyMc  )  return  -1;

	 //
	 for  (  i  =  0;  i  <  pProcInfo->cfg.usMaxCnt_taskInfos;  i  ++  )  {
		  QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )pProcInfo->getQmcTaskInfoByIndex(  i  );
		  if  (  !pTaskInfo  )  continue;
		  //
		  if  (  !pTaskInfo->bUsed  )  continue;
		  //
		  if  (  pTaskInfo->var.iTaskId  )  {
			  //if  (  !bNotExists_taskInSharedObjs(  pProcInfo,  pTaskInfo->var.iTaskId  )  )  continue;
			  //
			  //if  (  !bNotExists_taskInTaskQs(  pProcInfo,  pTaskInfo->var.iTaskId  )  )  continue;
			  /*
			  BOOL  tmp_bExists  =  FALSE;
			  if  (  getVal_bExists_taskInWnd(  pQyMc,  pTaskInfo->var.iTaskId,  pTaskInfo->var.hWnd_task,  &tmp_bExists  )  )  continue;
			  if  (  tmp_bExists  )  continue;
			  */
		  }

		  //
		  freeTaskInfo(  pProcInfo,  i,  _T(  "freeTaskInfos"  )  );
	 }


	 //
	 iErr  =  0;
errLabel:
	 return  iErr;
 }




