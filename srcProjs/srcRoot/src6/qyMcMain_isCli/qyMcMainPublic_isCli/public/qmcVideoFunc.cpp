

#include	"stdafx.h"
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





 
#if 0 

 int  tmpHandler_bMediaTaskExists(  void  *  p0,  void  *  p1,  MIS_MSGU  *  pMsg  )
{
	int	iTaskId =  (  int  )p0;

	if  (  pMsg->uiType  ==  CONST_misMsgType_task  )  {
		if  (  pMsg->task.iTaskId  ==  iTaskId  )  return 1;
	}

	return  0;
}
#endif

 BOOL  bMediaTaskExists(  MC_VAR_common  *  pProcInfo,  int  iTaskId  )
{
#if  0
	BOOL		bRet	=	FALSE;

	if  (  pProcInfo->processQ_media.qTraverse(  (  PF_commonHandler  )tmpHandler_bMediaTaskExists,  (  void  *  )iTaskId,  0  )  <=  0  )  goto  errLabel;

	bRet  =  TRUE;
errLabel:
	return  bRet;
#endif
	if  (  !pProcInfo  )  return  FALSE;
	return  pProcInfo->bMediaTaskExists(  iTaskId  );
}

//



 // #define		getSharedObjUsr(  pSharedObj,  iIndex_usr  )		(  (  (  pSharedObj  )  &&  (  iIndex_usr  )  >=0  &&  (  iIndex_usr  )  <  MAX_sharedObjUsrs  )  ?  &(  pSharedObj  )->usrs[iIndex_usr]  :  NULL  )
 SHARED_OBJ_USR  *  getSharedObjUsr(  QY_SHARED_OBJ  *  pSharedObj,  int  iIndex_usr  )
{
	return  (  (  (  pSharedObj  )  &&  (  iIndex_usr  )  >=0  &&  (  iIndex_usr  )  <  MAX_sharedObjUsrs  )  ?  &(  pSharedObj  )->usrs[iIndex_usr]  :  NULL  );
}


 int  getSharedObjIndex_localAv(  )
{
	return  0;
}

 //
 //  void  askSharedObjToStop(  MC_VAR_isCli  *  pProcInfo,  QY_SHARED_OBJ  *  pSharedObj,  HWND  hWnd_notifyEnd  )
 void  askSharedObjToStop(  MC_VAR_common  *  pProcInfo,  QY_SHARED_OBJ  *  pSharedObj,  HWND  hWnd_notifyEnd,  LPCTSTR  hint  )

{
	 if  (  !pSharedObj  )  return;

	 TCHAR  tBuf[128]  =  _T(  ""  );

	 if  (  !hint  )  hint  =  _T(  ""  );
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "askSharedObjToStop called, %d, %s"  ),  pSharedObj->index_sharedObj,  hint  );
	 //
	 showInfo_open0(  0,  0,  tBuf  );
 
	 //
	 if  (  !pSharedObj->bQuit  ) {
		 pSharedObj->bQuit  =  TRUE;
	 }

#if  0
	 QM_SHM_CMD		*	pShmCmd		=	NULL;
	 //  pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pSharedObj->iIndex_shmCmd  );
	 pShmCmd  =  (  QM_SHM_CMD  *  )pProcInfo->getQmShmCmdByIndex(  pSharedObj->iIndex_shmCmd  );
	 if  (  pShmCmd  )  pShmCmd->bQuit  =  TRUE;
#endif
	
	 PostMessage(  hWnd_notifyEnd,  CONST_qyWm_postComm,  CONST_qyWmParam_task_end,  0  );	

	 return;
}
