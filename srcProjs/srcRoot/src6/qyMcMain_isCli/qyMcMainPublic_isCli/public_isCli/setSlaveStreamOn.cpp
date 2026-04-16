


#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>


#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//  #include	"qmcVideoCapture_isCli.h"
//#include	"qyAvRecordPublic.h"
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

//#include	"isCliHelpPublic.h"
//#include	"dlgShareDynBmpsProc.h"
//#include	"isClid3dpublic.h"
#include	"qmcTaskPublic.h"

#include	"qmcCommFunc_isCli.h"
#include	"qmcCfg.h"

#include	"qmcVideoCapture_isCli.h"
#include	"GuiShare.h"





//
 //
//
 //
int  setSlaveStreamOn(  HWND  hMgr,  BOOL  bOn  )
{
	int  iErr  =  -1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	int  iIndex_master  =  getSharedObjIndex_localAv(  );
	QY_SHARED_OBJ  *  pSharedObj_master  =  getSharedObjByIndex(  pProcInfo,  iIndex_master  );
	if  (  !pSharedObj_master  )  goto  errLabel;
	//
	int  iIndex_slave  =  pSharedObj_master->master.slaveKey.iIndex_sharedObj;		
	QY_SHARED_OBJ  *  pSharedObj_slave  =  getSharedObjByIndex(  pProcInfo,  iIndex_slave  );
	if  (  !pSharedObj_slave  )  goto  errLabel;
	//
	if  (  !isSlaveOfMaster(  iIndex_slave,  pSharedObj_slave,  iIndex_master,  pSharedObj_master  )  )  goto  errLabel;
	//
	int  i;
	SHARED_OBJ_USR  *  pSharedObjUsr  =  NULL;
	for  (  i  =  0;  i  <  mycountof(  pSharedObj_slave->usrs  );  i  ++  )  {
		pSharedObjUsr  =  &pSharedObj_slave->usrs[i];
		if  (  pSharedObjUsr->hWnd_starter  ==  hMgr  )  break;		 
	}
	if  (  i  ==  mycountof(  pSharedObj_slave->usrs  )  )  goto  errLabel;
	//
	int  index_taskInfo  =  GuiShare.pf_getQmcTaskInfoIndexBySth(  pProcInfo,  pSharedObjUsr->iTaskId  );
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )GuiShare.pf_getQmcTaskInfoByIndex(  pProcInfo,  index_taskInfo  );
	if  (  !pTaskInfo  )  goto  errLabel;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;
	if  (  pTc->common.uiType  !=  CONST_taskDataType_conf  )  goto  errLabel;
	//		
	pTc->ucbNotSendData  =  !bOn;
	
	iErr  =  0;
errLabel:
	return  iErr;
}



