

#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	<time.h>
#include	<stddef.h>
#include	<ShellAPI.h>

#include	"qymcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"

#include	"qmcVideoCapture.h"

//#include	"qyAvRecordPublic.h"
//#include	"qmcVideoCapture_isCli.h"


#include	"tmpCeLib.h"
#include	"qyWnd.h"

#include	"qyRtcCommProc.h"
#ifndef  __WINCE__
//#include	"dlgVideosProc.h"
#endif
#include	<assert.h>
//#include	"qmcDxSurfacePublic.h"
#ifndef  __WINCE__
//#include	"qmcConferenceWall.h"
//#include	"isCliHelpPublic.h"
#endif
#include	"qmcCmdProc.h"

#include	"policyAvParams.h"

//#include	"dlgTalkProc.h"
//#include	"qmcSharePublic.h"

//#include	"DlgWalls.h"

#include	"gpsCommProc.h"
//#include	"qmcGpsProc.h"

#include	"qyCusResTemp.h"

//#include	"qmcVWall.h"
//#include	"dlgDesktopsMonProc.h"

#include	"sp.h"
#include	"myDb.h"
//#include	"isCliHelpPublic.h"

//#include	"imgProcessPublic.h"
//#include	"funcsForIsCliHelp.h"

//#include	"dlgMsgToolProc.h"
#include	"qmcVideoCapture_rtsp.h"
//#include	"qmcDynBmp.h"

#include	"qyCusResTemp.h"
//#include	"dlgShareDynBmpsProc.h"
//#include	"isCliD3dPublic.h"
#include	"policyIsClientFunc.h"

#ifdef  __TEST_ONLY__
		#include	"testOnly.h"
#endif




 //  2014/09/29. 建立和移除master和slave的关系，涉及到多线程访问sharedObj数据是否同步的问题。现在因为从master传图像到slave都在界面线程，所以暂时不需要同步。
 //  但是以后，需要将sharedObj扩成struct  {
 //											sharedObj;
//											unsigned  int  uitranNo;
 //											long	lCnt;
//									}		sharedInfo;. 就可以利用lCnt来同步了.
 //
 int  addSlaveToMaster(  MC_VAR_common  *  pProcInfo,  int  iIndex_sharedObj_slave,  int  iIndex_sharedObj_master  )
 {
	 int							iErr		=	-1;
	 //QY_MC						*	pQyMc					=	QY_GET_GBUF(  );
	//  MC_VAR_isCli				*	pProcInfo				=	QY_GET_procInfo_isCli(  );
	//FUNCS_for_isCliHelp			*	pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	//if  (  !pFuncs  )  return  -1;

	#ifdef  __DEBUG__
			traceLog((TCHAR*)  _T(  "addSlaveToMaster"  )  );
	#endif


	//			
	BOOL							bInited					=	FALSE;
	unsigned  int					tn_master				=	0;
	unsigned  int					tn_slave				=	0;
	//
	QY_sharedObj_sync			*	pSharedObjInfo_master	=	NULL;
	QY_SHARED_OBJ				*	pSharedObj_master		=	NULL;
	//
	CQySyncObj						syncObj_master;
	CQySyncObj						syncObj_slave;
	//
	QY_sharedObj_sync* pSharedObjInfo_slave = NULL;
	QY_SHARED_OBJ* pSharedObj_slave = NULL;

	//
	pSharedObjInfo_master  =  getSharedObjSyncByIndex(  pProcInfo,  iIndex_sharedObj_master  );
	if  (  !pSharedObjInfo_master  )  goto  errLabel;
	pSharedObj_master  =  &pSharedObjInfo_master->sharedObj;

	//
	pSharedObjInfo_slave  =  getSharedObjSyncByIndex(  pProcInfo,  iIndex_sharedObj_slave  );
	if  (  !pSharedObjInfo_slave  )  goto  errLabel;
	pSharedObj_slave  =  &pSharedObjInfo_slave->sharedObj;

	//
	bInited  =  TRUE;

	//
	if  (  syncMtCnt_wLock_noWait(  &pSharedObjInfo_master->syncMtCnt,  NULL,  &syncObj_master,  &tn_master  )  )  goto  errLabel;
	if  (  syncMtCnt_wLock_noWait(  &pSharedObjInfo_slave->syncMtCnt,  NULL,  &syncObj_slave,  &tn_slave  )  )  goto  errLabel;

	//
	if  (  pSharedObj_master->bSlave  )  goto  errLabel;
	//
	if  (  pSharedObj_slave->slave.masterKey.uiTranNo  )  goto  errLabel;
	if  (  pSharedObj_master->master.slaveKey.uiTranNo  )  goto  errLabel;
	//
	pSharedObj_slave->bSlave  =  TRUE;
	pSharedObj_slave->slave.masterKey.iIndex_sharedObj  =  iIndex_sharedObj_master;
	pSharedObj_slave->slave.masterKey.uiTranNo  =  pSharedObj_master->uiTranNo;
	//
	pSharedObj_master->master.slaveKey.iIndex_sharedObj  =  iIndex_sharedObj_slave;
	pSharedObj_master->master.slaveKey.uiTranNo  =  pSharedObj_slave->uiTranNo;

	iErr  =  0;
errLabel:

	if  (  bInited  )  {
		if  (  tn_master  )  {
			syncMtCnt_start(  &pSharedObjInfo_master->syncMtCnt,  getuiNextTranNo  );
		}
		if  (  tn_slave  )  {
			syncMtCnt_start(  &pSharedObjInfo_slave->syncMtCnt,  getuiNextTranNo  );
		}
	}


	return  iErr;
 }

 //
 BOOL  bExists_slave(  MC_VAR_common  *  pProcInfo,  int  iIndex_sharedObj_master  )
 {
	 BOOL							bRet					=	FALSE;
	//  QY_MC					*	pQyMc					=	QY_GET_GBUF(  );
	//  MC_VAR_isCli			*	pProcInfo				=	QY_GET_procInfo_isCli(  );


	//
	QY_sharedObj_sync			*	pSharedObjInfo_master	=	NULL;
	QY_SHARED_OBJ				*	pSharedObj_master		=	NULL;
	pSharedObjInfo_master  =  getSharedObjSyncByIndex(  pProcInfo,  iIndex_sharedObj_master  );
	if  (  !pSharedObjInfo_master  )  goto  errLabel;
	
	pSharedObj_master  =  &pSharedObjInfo_master->sharedObj;
	if  (  !pSharedObj_master->bUsed  )  goto  errLabel;

	if  (  pSharedObj_master->bSlave  )  goto  errLabel;

	int  iIndex_sharedObj_slave  =  pSharedObj_master->master.slaveKey.iIndex_sharedObj;

	//
	QY_sharedObj_sync			*	pSharedObjInfo_slave	=	NULL;
	QY_SHARED_OBJ				*	pSharedObj_slave		=	NULL;
	pSharedObjInfo_slave  =  getSharedObjSyncByIndex(  pProcInfo,  iIndex_sharedObj_slave  );
	if  (  !pSharedObjInfo_slave  )  goto  errLabel;
	
	pSharedObj_slave  =  &pSharedObjInfo_slave->sharedObj;
	if  (  !pSharedObj_slave->bUsed  )  goto  errLabel;

	if  (  !pSharedObj_slave->bSlave  )  goto  errLabel;
	
	//
	if  (  !isSlaveOfMaster(  iIndex_sharedObj_slave,  pSharedObj_slave,  iIndex_sharedObj_master,  pSharedObj_master  )  )  {
		  goto  errLabel;
	}

	bRet  =  TRUE;
		

errLabel:
	return  bRet;
 }

 BOOL  bExists_master(  MC_VAR_common  *  pProcInfo,  int  iIndex_sharedObj_slave  )
 {
	 BOOL							bRet					=	FALSE;
	//  QY_MC						*	pQyMc					=	QY_GET_GBUF(  );
	//  MC_VAR_isCli				*	pProcInfo				=	QY_GET_procInfo_isCli(  );
	
	//
	QY_sharedObj_sync			*	pSharedObjInfo_slave	=	NULL;
	QY_SHARED_OBJ				*	pSharedObj_slave		=	NULL;
	pSharedObjInfo_slave  =  getSharedObjSyncByIndex(  pProcInfo,  iIndex_sharedObj_slave  );
	if  (  !pSharedObjInfo_slave  )  goto  errLabel;
	
	pSharedObj_slave  =  &pSharedObjInfo_slave->sharedObj;
	if  (  !pSharedObj_slave->bUsed  )  goto  errLabel;

	if  (  !pSharedObj_slave->bSlave  )  goto  errLabel;

	//
	int  iIndex_sharedObj_master  =  pSharedObj_slave->slave.masterKey.iIndex_sharedObj;

	//
	QY_sharedObj_sync			*	pSharedObjInfo_master	=	NULL;
	QY_SHARED_OBJ				*	pSharedObj_master		=	NULL;
	pSharedObjInfo_master  =  getSharedObjSyncByIndex(  pProcInfo,  iIndex_sharedObj_master  );
	if  (  !pSharedObjInfo_master  )  goto  errLabel;
	
	pSharedObj_master  =  &pSharedObjInfo_master->sharedObj;
	if  (  !pSharedObj_master->bUsed  )  goto  errLabel;

	if  (  pSharedObj_master->bSlave  )  goto  errLabel;
		
	
	//
	if  (  !isSlaveOfMaster(  iIndex_sharedObj_slave,  pSharedObj_slave,  iIndex_sharedObj_master,  pSharedObj_master  )  )  {
		  goto  errLabel;
	}

	bRet  =  TRUE;
		

errLabel:
	return  bRet;
 }



 int  removeSlaveFromMaster(  MC_VAR_common  *  pProcInfo,  int  iIndex_sharedObj_slave,  int  iIndex_sharedObj_master  )
 {
	 //
	 int							iErr					=	-1;
	//QY_MC						*	pQyMc					=	QY_GET_GBUF(  );
	//MC_VAR_isCli				*	pProcInfo				=	QY_GET_procInfo_isCli(  );


	#ifdef  __DEBUG__
			traceLog((TCHAR*)  _T(  "removeSlaveFromMaster"  )  );
	#endif

	BOOL							bInited					=	FALSE;
	unsigned  int					tn_master				=	0;
	unsigned  int					tn_slave				=	0;
	//
	CQySyncObj						syncObj_master;
	CQySyncObj						syncObj_slave;
	//
	QY_sharedObj_sync			*	pSharedObjInfo_master	=	NULL;
	QY_SHARED_OBJ				*	pSharedObj_master		=	NULL;
	//
	QY_sharedObj_sync* pSharedObjInfo_slave = NULL;
	QY_SHARED_OBJ* pSharedObj_slave = NULL;

	//
	pSharedObjInfo_master  =  getSharedObjSyncByIndex(  pProcInfo,  iIndex_sharedObj_master  );
	if  (  !pSharedObjInfo_master  )  goto  errLabel;
	
	pSharedObj_master  =  &pSharedObjInfo_master->sharedObj;

	//
	pSharedObjInfo_slave  =  getSharedObjSyncByIndex(  pProcInfo,  iIndex_sharedObj_slave  );
	if  (  !pSharedObjInfo_slave  )  goto  errLabel;
	
	pSharedObj_slave  =  &pSharedObjInfo_slave->sharedObj;

	//
#if  0
	MACRO_qyAssert(  !pSharedObj_master->bSlave,  _T(  "remoteSlaveFromMaster, master is not a master" )  );
	MACRO_qyAssert(  pSharedObj_slave->bSlave,  _T(  "remoteSlaveFromMaster, slave is not a slave" )  );
#endif

	//
	bInited  =  TRUE;

	//
	if  (  syncMtCnt_wLock_noWait(  &pSharedObjInfo_master->syncMtCnt,  NULL,  &syncObj_master,  &tn_master  )  )  goto  errLabel;
	if  (  syncMtCnt_wLock_noWait(  &pSharedObjInfo_slave->syncMtCnt,  NULL,  &syncObj_slave,  &tn_slave  )  )  goto  errLabel;


	//
	if  (  isSlaveOfMaster(  iIndex_sharedObj_slave,  pSharedObj_slave,  iIndex_sharedObj_master,  pSharedObj_master  )  )  {
		memset(  &pSharedObj_master->master.slaveKey,  0,  sizeof(  pSharedObj_master->master.slaveKey  )  );
		memset(  &pSharedObj_slave->slave.masterKey,  0,  sizeof(  pSharedObj_slave->slave.masterKey  )  );
	}

	iErr  =  0;
errLabel:
	if  (  bInited  )  {
		if  (  tn_master  )  {
			syncMtCnt_start(  &pSharedObjInfo_master->syncMtCnt,  getuiNextTranNo  );
		}
		if  (  tn_slave  )  {
			syncMtCnt_start(  &pSharedObjInfo_slave->syncMtCnt,  getuiNextTranNo  );
		}
	}
	return  iErr;

 }





