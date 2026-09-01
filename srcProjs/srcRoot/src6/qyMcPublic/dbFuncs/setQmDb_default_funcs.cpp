

#include	"stdafx.h"
//  #include	<afxdb.h>
#include	<windowsx.h>
#include	<winsock2.h>
#include	<vfw.h>
#include	<tchar.h>

#include	"qmCommon.h"
#include	"qyDbCommon.h"
#include	"qyTCharCommProc.h"
#include	"myDb.h"


//
BOOL  bGetImAmRcdBySth_null(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  short  usAuthType,  LPCTSTR  messengerName,  int  id,  QY_imAm_RCD  *  pObj  )
{
	return  FALSE;
}
//
BOOL  bGetMessengerRegInfoBySth_null(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  pTabName,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_REGINFO  *  pRegInfo  )
{
	return  FALSE;
}
//
BOOL  bGetImOtherRegInfoBySth_null(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  pTabName,  MSGR_ADDR  *  pAddr,  int  iRcdId,  QY_MESSENGER_REGINFO  *  pRegInfo  )
{
	return  FALSE;
}

BOOL  bGetMeInfoBySth_null(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_INFO  *  pObj  )
{
	return  FALSE;
}

BOOL  bGetMessengerInfoBySth_null(  QM_dbFuncs  *  pDbFuncs,  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_INFO  *  pObjParam,  QY_MESSENGER_REGINFO  *  pRegInfo,  QY_MESSENGER_REGINFO  *  pRegInfoInTab1,  QY_MESSENGER_phoneInfo  *  pPhoneInfo  )
{
	return  FALSE;
}


int insertImObj_recoverMessenger_null(  QM_dbFuncs  *  pDbFuncs,  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj,  time_t  tLastModifiedTime  )
{
	return  -1;
}

int updateImObj_recoverMessenger_null(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj,  time_t  tLastModifiedTime,  int  iRcdId  )
{
	return  -1;
}

int updateImObj_recoverMessenger2_null(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj,  time_t  tLastModifiedTime,  int  iRcdId  )
{
	return  -1;
}


//
int insertImObj_recoverImGrp_null(  void  *  pDb,  int  iDbType,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime  )
{
	return  -1;
}

int updateImObj_recoverImGrp_null(  void  *  pDb,  int  iDbType,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime,  int  iRcdId  )
{
	return  -1;
}

int updateImObj_recoverImGrp2_null(  void  *  pDb,  int  iDbType,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime,  int  iRcdId  )
{
	return  -1;
}

BOOL bGetImGrpInfoBySth_null(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  IM_GRP_INFO  *  pRcd  )
{
	return  FALSE;
}

int insertImGrp_recoverImGrp_null(  void  *  pDbParam,  int  iDbType,  IM_GRP_INFO  *  pGrpInfo  )
{
	return  -1;
}

int updateImGrp_recoverImGrp_null(  void  *  pDbParam,  int  iDbType,  IM_GRP_INFO  *  pGrpInfo,  int  iRcdId  )
{
	return  -1;
}

BOOL bGetImGrpMemBySth_null(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo_grp,  QY_MESSENGER_ID  *  pIdInfo_mem,  int  iRcdId,  IM_GRP_MEM  *  pRcd  )
{
	return  FALSE;
}

int insertImGrpMem_recoverImGrpMem_null(  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime  )
{
	return  -1;
}

int updateImGrpMem_recoverImGrpMem_null(  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime,  int  iRcdId  )
{
	return  -1;
}

int updateImGrpMem_recoverImGrpMem2_null(  void  *  pDbParam,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime,  int  iRcdId  )
{
	return  -1;
}

BOOL bIdInfoExistedInImObjRegInfoTab_null(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_ID  *  pIdInfo,  LPCTSTR  tabName  )
{
	return  FALSE;
}

int insertImObjRegInfo_qisRegUsrInfoInTab_null(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  )
{
	return  -1;
}

int updateImObjRegInfo_qisRegUsrInfoInTab_null(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  )
{
	return  -1;
}

int qnmRegUsrInfo_null(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo  )
{
	return  -1;
}

int qisRegUsrInfo_null(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QY_MESSENGER_INFO  *  pMessengerInfo,  QY_MESSENGER_REGINFO  *  pRegInfo,  BOOL  bLogReRegEvent  )
{
	return  -1;
}

BOOL bSelectImMsg_logImMsg_null(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  IM_MSG_RCD  *  pRcd  )
{
	return  FALSE;
}

int insertImMsg_logImMsg_null(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  IM_MSG_RCD  *  pRcd  )
{
	return  -1;
}

int auditNewMessenger_null(  void  *  pReserved,  QY_MESSENGER_ID  *  pLastIdInfo,  void  *  pLicenseCtx,  void  *  pDb,  int  iDbType,  POLICY_imAuthCond  *  pAuthCond,  QY_MESSENGERAUTHTMP_RCD  *  pNewMessenger  )
{
	return  -1;
}

BOOL bGetImMsgRcdBySth_null(  void  *  pDbParam,  int  iDbType,  int  id,  IM_MSG_RCD  *  pObj  )
{
	return  FALSE;
}

BOOL bGetPcInfoByMac_null(  void  *  pDbParam,  char  *  mac,  unsigned  char  ucbMac0,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo  )
{
	return  FALSE;
}

BOOL bGetPcInfoByMacEx_null(  void  *  pDbParam,  char  *  mac,  unsigned  char  ucbMac0,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo,  QNM_REG_INFO  *  pRegInfoInTab1  )
{
	return  FALSE;
}

BOOL bLogEventFunc_is_null(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QIS_EVENT  *  pEvent  )
{
	return  FALSE;
}

int getEventInfoBySth_null(  void  *  pDbParam,  int  iDbType,  QIS_EVENT  *  pEvent  )
{
	return  -1;
}

int getPcEventInfoByMac0_null(  void  *  pDbParam,  QNM_PC_EVENT  *  pEvent  )
{
	return  -1;
}

BOOL bLogPcEventFunc_null(  void  *  pDb,  int  iDbType,  QNM_PC_EVENT  *  pEvent  )
{
	return  FALSE;
}

int qisRegOtherInfoInTab_null(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  MSGR_ADDR  *  pAddr,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  )
{
	return  -1;
}

BOOL bClearupImMsg_isCli_null(  void  *  pDb,  int  iDbType,  LPCTSTR  wherePart  )
{
	return  FALSE;
}

BOOL bClearupEvent_is_null(  QY_CLEARUPINFO  *  pClearupInfo  )
{
	return  FALSE;
}

BOOL bClearupImMsg_null(  QY_CLEARUPINFO  *  pClearupInfo  )
{
	return  FALSE;
}

BOOL bClearupImHisTask_null(  QY_CLEARUPINFO  *  pClearupInfo  )
{
	return  FALSE;
}

int getObjIndex_null(  QY_OBJ_DB  *  pObjDb,  int  iObjId,  QY_OBJINDEX_RCD  *  pObjIndex  )
{
	return  -1;
}

BOOL bGetMessengerPhoneInfoBySth_null(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiDevType,  LPCTSTR  wDevIdStr,  QY_MESSENGER_ID  *  pIdInfo,  int  id,  QY_MESSENGER_phoneInfo  *  pRcd  )
{
	return  FALSE;
}

int recoverMessengerPhoneInfo_null(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  MSGR_ADDR  *  pAddr,  void  *  p1  )
{
	return  -1;
}


int updateImObj_me_null(  void  *  pDb,  int  iDbType,  QY_MESSENGER_INFO  *  pObj_me  )
{
	return  -1;
}

BOOL bGetImObjRulesReq_null(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  QY_MESSENGER_ID	*	pIdInfo_related,  LPCTSTR  condPart,  unsigned  short  usMaxMemsPerSnd,  REFRESH_imObjRules_req  *  pReq  )
{
	return  FALSE;
}

BOOL bGetImObjRuleRcdBySth_null(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem  *  pMem,  int  iRcdId,  QY_imObjRule_rcd  *  pRcd  )
{
	return  FALSE;
}

int insertImObjRule_recoverImObjRules_null(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  time_t  tLastModifiedTime  )
{
	return  -1;
}

int deleteImObjRule_recoverImObjRules_null(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  int  rcdId  )
{
	return  -1;
}

int updateImObjRule_recoverImObjRules_null(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  time_t  tLastModifiedTime,  int  rcdId  )
{
	return  -1;
}

int updateImObjRule_recoverImObjRules2_null(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  time_t  tLastModifiedTime,  int  rcdId  )
{
	return  -1;
}

int  updateImObj_refreshImGrps_end_null(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiObjType,  time_t  tLastModifiedTime  )
{
	return  -1;
}


BOOL  bNeedRetrieveImGrpMems_null(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName  )
{
	return  FALSE;
}

int  updateImGrpMem_refreshImGrpMems_end_null(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  time_t  tLastModifiedTime  )
{
	return  -1;
}

int  updateImObj_refreshContacts_end_null(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  time_t  tLastModifiedTime  )
{
	return  -1;
}

//
int  deleteOldImObjRule_mcProcResp_refreshImObjRulesReq_null(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  MIS_MSG_INPUT  *  pMsgInput,  void  *  pCtxParam  )
{
	return  -1;
}

int  selectNextImObjRule_mcProcResp_refreshImObjRulesReq_null(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  MIS_MSG_INPUT  *  pMsgInput,  void  *  pCtxParam,  QY_MESSENGER_ID  *	 pIdInfo_related  )
{
	return  -1;
}

void  fillImObjs_msgr_null(  HWND  hDlg,  void  *  pVar,  void  *  pDb  )
{
	return;
}

void  fillImObjs_grp_null(  HWND  hDlg,  void  *  pVar,  void  *  pDb  )
{
	return;
}

int  selectImTask_dlgTalk_loadTasks_null(  HWND  hDlgTalk,  void  *  pTmpParam,  void  *  pDbParam  )
{
	return  -1;
}
BOOL  bSelectImTask_storeTaskInDb_null(  void  *  pDb,  int  iDbType,  void  *  pMisCntParam,  IM_TASK_RCD  *  pRcd,  BOOL  bInHis  )
{
	return  FALSE;
}

int  insertImTask_storeTaskInDb_null(  void  *  pDb,  int  iDbType,  void  *  pMisCntParam,  int  iTaskId_suggested,  IM_TASK_RCD  *  pRcd,  BOOL  bInHis  )
{
	return  -1;
}
int  updateTaskStatus_null(  void  *  pDb,  int  iStatus,  int  iTaskId  )
{
	return  -1;
}
BOOL  bMoveTask2His_null(  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  )
{
	return  FALSE;
}

BOOL  bClearupDeletedImObjs_isClient_null(  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  )
{
	return  FALSE;
}

BOOL  bGetImTaskRcdBySth_null(  void  *  pDb,  int  iDbType,  BOOL  bHisTab,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  time_t  tSendTime,  unsigned  int  uiTranNo,  int  id,  IM_TASK_RCD  *  pRcd  )
{
	return  FALSE;
}


int  listObjs_dlgMsgList_null(  void  *  pDbParam,  void  *  pQueryParam,  HWND  hListCtrlParam,  QY_MESSENGER_ID  *  pIdInfoParam  )
{
	return  -1;
}

BOOL  bGetQyDynBmpRcdBySth_null(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex,  int  id,  QY_dynBmp_RCD  *  pRcd  )
{
	return  FALSE;
}

//
BOOL  bViewImTaskList_unproced_null(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	return  FALSE;
}

BOOL  bViewImTaskList_cur_null(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	return  FALSE;
}

BOOL  bViewImTaskList_his_null(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	return  FALSE;
}

BOOL  bViewImObjList_null(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	return  FALSE;
}

BOOL  bViewRegInfoList_null(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	return  FALSE;
}

BOOL  bViewImGrpList_null(   QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	return  FALSE;
}

BOOL  bViewImGrpMemList_isClient_null(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	return  FALSE;
}


//
BOOL  bViewImObjRuleList_is_null(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  )
{
	return  FALSE;
}


//
BOOL  bInsertPhoneGuest_procMsgTalk_work_null(  void  *  pDbParam,  int  iDbType,  void  *  pQyMcParam,  MIS_MSG_TALK  *  pMsg,  void  *  pGuestParam  )
{
	return  FALSE;
}

BOOL  bUpdateImTask_bChkQyMcEnv_mis_null(  void  *  pDb,  int  iStatus_set,  int  iStatus_0,  int  iStatus_1  )
{
	return  FALSE;
}


int  deleteOldDynBmp_mcProcResp_retrieveDynBmps_null(  void  *  pDb,  int  iDbType,  char  *  pTimeBuf  )
{
	return  -1;
}

BOOL  bInsertDynBmp_mcProcResp_retrieveDynBmps_null(  void  *  pDb,  void  *  pMisCntParam,  QIS_dynBmp_info  *  pMem,  char  *  pTimeBuf  )
{
	return  FALSE;
}

BOOL  bUpdateDynBmp_mcProcResp_retrieveDynBmps_null(  void  *  pDb,  QIS_dynBmp_info  *  pMem,  char  *  pTimeBuf,  int  rcdId  )
{
	return  FALSE;
}

BOOL  bUpdateImObjRegInfo_procMsgInput_scheduler_null(  void  *  pDb,  void  *  pSciParam,  void  *  pMisCntParam,  QY_MESSENGER_ID  *  pIdInfo  )
{
	return  FALSE;
}


BOOL  bStatImTasks_null(  void  *  pProcInfoParam,  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  )
{
	return  FALSE;
}

BOOL  bDeleteFromTabById_null(  void  *  pDb,  int  iDbType,  LPCTSTR  pTabName,  int  id  )
{
	return  FALSE;
}

BOOL  bDeleteFromTabByIdInfo_null(  void  *  pDb,  int  iDbType,  LPCTSTR  pTabName,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  )
{
	return  FALSE;
}

BOOL  bDeleteImOtherRegInfoByAddr_null(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  LPCTSTR  pTabName,  MSGR_ADDR  *  pAddr  )
{
	return  FALSE;
}

int  iSelectImGrpMem_dlgSelect_isCli_null(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  HWND  idc_hWnd  )
{
	return  -1;
}

int  iSelectImObj_dlgSelect_isCli_null(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  )
{
	return  -1;
}

int  iSelectDynBmp_dlgSelect_isCli_null(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  )
{
	return  -1;
}



//  用类不如用default_funcs( return -1；  函数。
 int  setQmDb_default_Funcs(  QM_dbFuncs  *  pDbFuncs  )
{

	memset(  pDbFuncs,  0,  sizeof(  pDbFuncs[0]  )  );
	
	//
	pDbFuncs->pf_bGetImAmRcdBySth  =  bGetImAmRcdBySth_null;
	pDbFuncs->pf_bGetMessengerRegInfoBySth  =  bGetMessengerRegInfoBySth_null;
	pDbFuncs->pf_bGetImOtherRegInfoBySth  =  bGetImOtherRegInfoBySth_null;
	pDbFuncs->pf_bGetMeInfoBySth  =  bGetMeInfoBySth_null;			
	pDbFuncs->pf_bGetMessengerInfoBySth  =  bGetMessengerInfoBySth_null;
	pDbFuncs->pf_insertImObj_recoverMessenger  =  insertImObj_recoverMessenger_null;
	pDbFuncs->pf_updateImObj_recoverMessenger  =  updateImObj_recoverMessenger_null;
	pDbFuncs->pf_updateImObj_recoverMessenger2  =  updateImObj_recoverMessenger2_null;


	pDbFuncs->pf_insertImObj_recoverImGrp  =  insertImObj_recoverImGrp_null;
	pDbFuncs->pf_updateImObj_recoverImGrp  =  updateImObj_recoverImGrp_null;
	pDbFuncs->pf_updateImObj_recoverImGrp2  =  updateImObj_recoverImGrp2_null;
	pDbFuncs->pf_bGetImGrpInfoBySth  =  bGetImGrpInfoBySth_null;
	pDbFuncs->pf_insertImGrp_recoverImGrp  =  insertImGrp_recoverImGrp_null;
	pDbFuncs->pf_updateImGrp_recoverImGrp  =  updateImGrp_recoverImGrp_null;
	pDbFuncs->pf_bGetImGrpMemBySth  =  bGetImGrpMemBySth_null;
	pDbFuncs->pf_insertImGrpMem_recoverImGrpMem  =  insertImGrpMem_recoverImGrpMem_null;
	pDbFuncs->pf_updateImGrpMem_recoverImGrpMem  =  updateImGrpMem_recoverImGrpMem_null;
	pDbFuncs->pf_updateImGrpMem_recoverImGrpMem2  =  updateImGrpMem_recoverImGrpMem2_null;
	pDbFuncs->pf_bIdInfoExistedInImObjRegInfoTab  =  bIdInfoExistedInImObjRegInfoTab_null;
	pDbFuncs->pf_insertImObjRegInfo_qisRegUsrInfoInTab  =  insertImObjRegInfo_qisRegUsrInfoInTab_null;
	pDbFuncs->pf_updateImObjRegInfo_qisRegUsrInfoInTab  =  updateImObjRegInfo_qisRegUsrInfoInTab_null;

	pDbFuncs->pf_qnmRegUsrInfo  =  qnmRegUsrInfo_null;
	pDbFuncs->pf_qisRegUsrInfo  =  qisRegUsrInfo_null;
	pDbFuncs->pf_bSelectImMsg_logImMsg  =  bSelectImMsg_logImMsg_null;
	pDbFuncs->pf_insertImMsg_logImMsg  =  insertImMsg_logImMsg_null;
	pDbFuncs->pf_auditNewMessenger  =  auditNewMessenger_null;
	pDbFuncs->pf_bGetImMsgRcdBySth  =  bGetImMsgRcdBySth_null;
	pDbFuncs->pf_bLogEventFunc_is  =  bLogEventFunc_is_null;
	pDbFuncs->pf_bGetPcInfoByMac  =  bGetPcInfoByMac_null;
	pDbFuncs->pf_bGetPcInfoByMacEx  =  bGetPcInfoByMacEx_null;
	pDbFuncs->pf_getEventInfoBySth  =  getEventInfoBySth_null;
	pDbFuncs->pf_getPcEventInfoByMac0  =  getPcEventInfoByMac0_null;
	pDbFuncs->pf_bLogPcEventFunc  =  bLogPcEventFunc_null;
	pDbFuncs->pf_qisRegOtherInfoInTab  =  qisRegOtherInfoInTab_null;
	pDbFuncs->pf_bClearupImMsg_isCli  =  bClearupImMsg_isCli_null;
	pDbFuncs->pf_bClearupEvent_is  =  bClearupEvent_is_null;
	pDbFuncs->pf_bClearupImMsg  =  bClearupImMsg_null;
	pDbFuncs->pf_bClearupImHisTask  =  bClearupImHisTask_null;
	pDbFuncs->pf_getObjIndex  =  getObjIndex_null;

	pDbFuncs->pf_bGetMessengerPhoneInfoBySth  =  bGetMessengerPhoneInfoBySth_null;
	pDbFuncs->pf_recoverMessengerPhoneInfo  =  recoverMessengerPhoneInfo_null;

	pDbFuncs->pf_updateImObj_me  =  updateImObj_me_null;
	pDbFuncs->pf_bGetImObjRulesReq  =  bGetImObjRulesReq_null;
	pDbFuncs->pf_bGetImObjRuleRcdBySth  =  bGetImObjRuleRcdBySth_null;
	pDbFuncs->pf_insertImObjRule_recoverImObjRules  =  insertImObjRule_recoverImObjRules_null;
	pDbFuncs->pf_deleteImObjRule_recoverImObjRules  =  deleteImObjRule_recoverImObjRules_null;
	pDbFuncs->pf_updateImObjRule_recoverImObjRules  =  updateImObjRule_recoverImObjRules_null;
	pDbFuncs->pf_updateImObjRule_recoverImObjRules2  =  updateImObjRule_recoverImObjRules2_null;

//  isCli
	pDbFuncs->pf_updateImObj_refreshImGrps_end  =  updateImObj_refreshImGrps_end_null;
//
	pDbFuncs->pf_bNeedRetrieveImGrpMems  =  bNeedRetrieveImGrpMems_null;
//
	pDbFuncs->pf_updateImGrpMem_refreshImGrpMems_end  =  updateImGrpMem_refreshImGrpMems_end_null;
//
	pDbFuncs->pf_updateImObj_refreshContacts_end  =  updateImObj_refreshContacts_end_null;

//
	pDbFuncs->pf_deleteOldImObjRule_mcProcResp_refreshImObjRulesReq  =  deleteOldImObjRule_mcProcResp_refreshImObjRulesReq_null;
	pDbFuncs->pf_selectNextImObjRule_mcProcResp_refreshImObjRulesReq  =  selectNextImObjRule_mcProcResp_refreshImObjRulesReq_null;

	pDbFuncs->pf_fillImObjs_msgr  =  fillImObjs_msgr_null;
	pDbFuncs->pf_fillImObjs_grp  =  fillImObjs_grp_null;
	pDbFuncs->pf_selectImTask_dlgTalk_loadTasks  =  selectImTask_dlgTalk_loadTasks_null;
	pDbFuncs->pf_bSelectImTask_storeTaskInDb  =  bSelectImTask_storeTaskInDb_null;
	pDbFuncs->pf_insertImTask_storeTaskInDb  =  insertImTask_storeTaskInDb_null;
	pDbFuncs->pf_updateTaskStatus  =  updateTaskStatus_null;
	pDbFuncs->pf_bMoveTask2His  =  bMoveTask2His_null;
	pDbFuncs->pf_bClearupDeletedImObjs_isClient  =  bClearupDeletedImObjs_isClient_null;
	pDbFuncs->pf_bGetImTaskRcdBySth  =  bGetImTaskRcdBySth_null;
	//
	//
	pDbFuncs->pf_listObjs_dlgMsgList  =  listObjs_dlgMsgList_null;
	pDbFuncs->pf_bViewImTaskList_unproced  =  bViewImTaskList_unproced_null;
	pDbFuncs->pf_bViewImTaskList_cur  =  bViewImTaskList_cur_null;
	pDbFuncs->pf_bViewImTaskList_his  =  bViewImTaskList_his_null;

	pDbFuncs->pf_bViewImObjList  =  bViewImObjList_null;
	pDbFuncs->pf_bViewRegInfoList  =  bViewRegInfoList_null;
	pDbFuncs->pf_bViewImGrpList  =  bViewImGrpList_null;
	pDbFuncs->pf_bViewImGrpMemList_isClient  =  bViewImGrpMemList_isClient_null;
	pDbFuncs->pf_bViewImObjRuleList_is  =  bViewImObjRuleList_is_null;

//
	pDbFuncs->pf_bGetQyDynBmpRcdBySth  =  bGetQyDynBmpRcdBySth_null;
	pDbFuncs->pf_bInsertPhoneGuest_procMsgTalk_work  =  bInsertPhoneGuest_procMsgTalk_work_null;
	pDbFuncs->pf_bUpdateImTask_bChkQyMcEnv_mis  =  bUpdateImTask_bChkQyMcEnv_mis_null;
	pDbFuncs->pf_deleteOldDynBmp_mcProcResp_retrieveDynBmps  =  deleteOldDynBmp_mcProcResp_retrieveDynBmps_null;
//
	pDbFuncs->pf_bInsertDynBmp_mcProcResp_retrieveDynBmps  =  bInsertDynBmp_mcProcResp_retrieveDynBmps_null;
	pDbFuncs->pf_bUpdateDynBmp_mcProcResp_retrieveDynBmps  =  bUpdateDynBmp_mcProcResp_retrieveDynBmps_null;
	pDbFuncs->pf_bUpdateDynBmp_mcProcResp_retrieveDynBmps2  =  bUpdateDynBmp_mcProcResp_retrieveDynBmps_null;
//
	pDbFuncs->pf_bUpdateImObjRegInfo_procMsgInput_scheduler  =  bUpdateImObjRegInfo_procMsgInput_scheduler_null;
	pDbFuncs->pf_bStatImTasks  =  bStatImTasks_null;
	pDbFuncs->pf_bDeleteFromTabById  =  bDeleteFromTabById_null;
	pDbFuncs->pf_bDeleteFromTabByIdInfo  =  bDeleteFromTabByIdInfo_null;
	pDbFuncs->pf_bDeleteImOtherRegInfoByAddr  =  bDeleteImOtherRegInfoByAddr_null;
	pDbFuncs->pf_iSelectImGrpMem_dlgSelect_isCli  =  iSelectImGrpMem_dlgSelect_isCli_null;
	pDbFuncs->pf_iSelectImObj_dlgSelect_isCli  =  iSelectImObj_dlgSelect_isCli_null;
//
	pDbFuncs->pf_iSelectDynBmp_dlgSelect_isCli  =  iSelectDynBmp_dlgSelect_isCli_null;

	return  0;
}
