

#include	"stdafx.h"
//  #include	<afxdb.h>
#include	<windowsx.h>
#include	<winsock2.h>
#include	<vfw.h>

#include	"qmCommon.h"
#include	"qyDbCommon.h"
#include	"qyTCharCommProc.h"
#include	"myDb.h"










 //
 //  2013/01/30
BOOL  bGetImAmRcdBySth_odbc(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  short  usAuthType,  LPCTSTR  messengerName,  int  id,  QY_imAm_RCD  *  pObj  );
//
BOOL  bGetMessengerRegInfoBySth_odbc(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  pTabName,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_REGINFO  *  pRegInfo  );
BOOL  bGetImOtherRegInfoBySth_odbc(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  pTabName,  MSGR_ADDR  *  pAddr,  int  iRcdId,  QY_MESSENGER_REGINFO  *  pRegInfo  );
BOOL  bGetMeInfoBySth_odbc(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_INFO  *  pObj  );
BOOL  bGetMessengerInfoBySth_odbc(  QM_dbFuncs  *  pDbFuncs,  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_INFO  *  pObjParam,  QY_MESSENGER_REGINFO  *  pRegInfo,  QY_MESSENGER_REGINFO  *  pRegInfoInTab1,  QY_MESSENGER_phoneInfo  *  pPhoneInfo  );
int  insertImObj_recoverMessenger_odbc(  QM_dbFuncs  *  pDbFuncs,  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj,  time_t  tLastModifiedTime  );
int  updateImObj_recoverMessenger_odbc(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj,  time_t  tLastModifiedTime,  int  iRcdId  );
int  updateImObj_recoverMessenger2_odbc(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj,  time_t  tLastModifiedTime,  int  iRcdId  );


int  insertImObj_recoverImGrp_odbc(  void  *  pDb,  int  iDbType,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime  );
int  updateImObj_recoverImGrp_odbc(  void  *  pDb,  int  iDbType,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime,  int  iRcdId  );
int  updateImObj_recoverImGrp2_odbc(  void  *  pDb,  int  iDbType,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime,  int  iRcdId  );

BOOL  bGetImGrpInfoBySth_odbc(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  IM_GRP_INFO  *  pRcd  );
int  insertImGrp_recoverImGrp_odbc(  void  *  pDbParam,  int  iDbType,  IM_GRP_INFO  *  pGrpInfo  );
int  updateImGrp_recoverImGrp_odbc(  void  *  pDbParam,  int  iDbType,  IM_GRP_INFO  *  pGrpInfo,  int  iRcdId  );
BOOL  bGetImGrpMemBySth_odbc(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo_grp,  QY_MESSENGER_ID  *  pIdInfo_mem,  int  iRcdId,  IM_GRP_MEM  *  pRcd  );
//  int  insertImGrpMem_recoverImGrpMem_odbc(  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem  );
int  insertImGrpMem_recoverImGrpMem_odbc(  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime  );
//  int  updateImGrpMem_recoverImGrpMem_odbc(  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  int  iRcdId  );
int  updateImGrpMem_recoverImGrpMem_odbc(  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime,  int  iRcdId  );
int  updateImGrpMem_recoverImGrpMem2_odbc(  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime,  int  iRcdId  );
BOOL  bIdInfoExistedInImObjRegInfoTab_odbc(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_ID  *  pIdInfo,  LPCTSTR  tabName  );
int  insertImObjRegInfo_qisRegUsrInfoInTab_odbc(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  );
int  updateImObjRegInfo_qisRegUsrInfoInTab_odbc(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  );

//
int  qnmRegUsrInfo_odbc(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo  );
//
int  qisRegUsrInfo_odbc(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QY_MESSENGER_INFO  *  pMessengerInfo,  QY_MESSENGER_REGINFO  *  pRegInfo,  BOOL  bLogReRegEvent  );
BOOL  bSelectImMsg_logImMsg_odbc(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  IM_MSG_RCD  *  pRcd  );
int  insertImMsg_logImMsg_odbc(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  IM_MSG_RCD  *  pRcd  );
int  auditNewMessenger_odbc(  void  *  pReserved,  QY_MESSENGER_ID  *  pLastIdInfo,  void  *  pLicenseCtx,  void  *  pDb,  int  iDbType,  POLICY_imAuthCond  *  pAuthCond,  QY_MESSENGERAUTHTMP_RCD  *  pNewMessenger  );
BOOL  bGetImMsgRcdBySth_odbc(  void  *  pDbParam,  int  iDbType,  int  id,  IM_MSG_RCD  *  pObj  );
BOOL  bGetPcInfoByMac_odbc(  void  *  pDbParam,  char  *  mac,  unsigned  char  ucbMac0,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo  );
BOOL  bGetPcInfoByMacEx_odbc(  void  *  pDbParam,  char  *  mac,  unsigned  char  ucbMac0,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo,  QNM_REG_INFO  *  pRegInfoInTab1  );
BOOL  bLogEventFunc_is_odbc(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QIS_EVENT  *  pEvent  );
int  getEventInfoBySth_odbc(  void  *  pDbParam,  int  iDbType,  QIS_EVENT  *  pEvent  );
int  getPcEventInfoByMac0_odbc(  void  *  pDbParam,  QNM_PC_EVENT  *  pEvent  );
BOOL  bLogPcEventFunc_odbc(  void  *  pDb,  int  iDbType,  QNM_PC_EVENT  *  pEvent  );
int  qisRegOtherInfoInTab_odbc(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  MSGR_ADDR  *  pAddr,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  );
BOOL  bClearupImMsg_isCli_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  wherePart  );
BOOL  bClearupEvent_is_odbc(  QY_CLEARUPINFO  *  pClearupInfo  );
BOOL  bClearupImMsg_odbc(  QY_CLEARUPINFO  *  pClearupInfo  );
BOOL  bClearupImHisTask_odbc(  QY_CLEARUPINFO  *  pClearupInfo  );
int  getObjIndex_odbc(  QY_OBJ_DB  *  pObjDb,  int  iObjId,  QY_OBJINDEX_RCD  *  pObjIndex  );
//
__declspec(  dllexport  )  int  listObjs_dlgMsgList_odbc(  void  *  pDbParam,  void  *  pQueryParam,  HWND  hListCtrlParam,  QY_MESSENGER_ID  *  pIdInfoParam  );
//
BOOL  bGetMessengerPhoneInfoBySth_odbc(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiDevType,  LPCTSTR  wDevIdStr,  QY_MESSENGER_ID  *  pIdInfo,  int  id,  QY_MESSENGER_phoneInfo  *  pRcd  );
int  recoverMessengerPhoneInfo_odbc(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  MSGR_ADDR  *  pAddr,  void  *  p1  );

int  updateImObj_me_odbc(  void  *  pDb,  int  iDbType,  QY_MESSENGER_INFO  *  pObj_me  );
BOOL  bGetImObjRulesReq_odbc(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  QY_MESSENGER_ID	*	pIdInfo_related,  LPCTSTR  condPart,  unsigned  short  usMaxMemsPerSnd,  REFRESH_imObjRules_req  *  pReq  );
BOOL  bGetImObjRuleRcdBySth_odbc(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem  *  pMem,  int  iRcdId,  QY_imObjRule_rcd  *  pRcd  );
int  insertImObjRule_recoverImObjRules_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  time_t  tLastModifiedTime  );
int  deleteImObjRule_recoverImObjRules_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  int  rcdId  );
int  updateImObjRule_recoverImObjRules_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  time_t  tLastModifiedTime,  int  rcdId  );
int  updateImObjRule_recoverImObjRules2_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  time_t  tLastModifiedTime,  int  rcdId  );
//
//  isCli
int  updateImObj_refreshImGrps_end_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiObjType,  time_t  tLastModifiedTime  );

BOOL	bNeedRetrieveImGrpMems_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName  );

int  updateImGrpMem_refreshImGrpMems_end_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  time_t  tLastModifiedTime  );

int  updateImObj_refreshContacts_end_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  time_t  tLastModifiedTime  );

//
int  deleteOldImObjRule_mcProcResp_refreshImObjRulesReq_odbc(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  MIS_MSG_INPUT  *  pMsgInput,  void  *  pCtxParam  );
int  selectNextImObjRule_mcProcResp_refreshImObjRulesReq_odbc(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  MIS_MSG_INPUT  *  pMsgInput,  void  *  pCtxParam,  QY_MESSENGER_ID	  *  pIdInfo_related  );
void  fillImObjs_msgr_odbc(  HWND  hDlg,  void  *  pVar,  void  *  pDb  );
void  fillImObjs_grp_odbc(  HWND  hDlg,  void  *  pVar,  void  *  pDb  );
int  selectImTask_dlgTalk_loadTasks_odbc(  HWND  hDlgTalk,  void  *  pTmpParam,  void  *  pDbParam  );
BOOL  bSelectImTask_storeTaskInDb_odbc(  void  *  pDb,  int  iDbType,  void  *  pMisCntParam,  IM_TASK_RCD  *  pRcd,  BOOL  bInHis  );
int  insertImTask_storeTaskInDb_odbc(  void  *  pDb,  int  iDbType,  void  *  pMisCntParam,  int  iTaskId_suggested,  IM_TASK_RCD  *  pRcd,  BOOL  bInHis  );
int  updateTaskStatus_odbc(  void  *  pDb,  int  iStatus,  int  iTaskId  );
BOOL  bMoveTask2His_odbc(  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  );
BOOL  bClearupDeletedImObjs_isClient_odbc(  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  );
BOOL  bGetImTaskRcdBySth_odbc(  void  *  pDb,  int  iDbType,  BOOL  bHisTab,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  time_t  tSendTime,  unsigned  int  uiTranNo,  int  id,  IM_TASK_RCD  *  pRcd  );
//BOOL  bSelectImGrpMem_dlgTalk_OnInitDialog_odbc(  HWND  hDlgTalkParam,  void  *  pDbParam,  void  *  pParam  );
BOOL  bGetQyDynBmpRcdBySth_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex,  int  id,  QY_dynBmp_RCD  *  pRcd  );
//
BOOL  bViewImTaskList_unproced_odbc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImTaskList_cur_odbc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImTaskList_his_odbc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImObjList_odbc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImGrpList_odbc(   QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImGrpMemList_isClient_odbc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImObjRuleList_is_odbc(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  );
//BOOL  bViewSharedDynBmpList_isClient_odbc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewRegInfoList_odbc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bInsertPhoneGuest_procMsgTalk_work_odbc(  void  *  pDb,  int  iDbType,  void  *  pQyMcParam,  MIS_MSG_TALK  *  pMsg,  void  *  pGuestParam  );
BOOL  bUpdateImTask_bChkQyMcEnv_mis_odbc(  void  *  pDb,  int  iStatus_set,  int  iStatus_0,  int  iStatus_1  );

int  deleteOldDynBmp_mcProcResp_retrieveDynBmps_odbc(  void  *  pDb,  int  iDbType,  char  *  pTimeBuf  );
//  int  deleteDynBmp_tmpHandler_delOld_dynBmpQ_odbc(  void  *  pDb,  int  id  );
//  __declspec(  dllexport  )  int  init_mcProcResp_retrieveDynBmps_odbc(  void  *  pDb,  void  *  pCtxParam  );
BOOL  bInsertDynBmp_mcProcResp_retrieveDynBmps_odbc(  void  *  pDb,  void  *  pMisCntParam,  QIS_dynBmp_info  *  pMem,  char  *  pTimeBuf  );
BOOL  bUpdateDynBmp_mcProcResp_retrieveDynBmps_odbc(  void  *  pDb,  QIS_dynBmp_info  *  pMemParam,  char  *  pTimeBuf,  int  rcdId  );
BOOL  bUpdateDynBmp_mcProcResp_retrieveDynBmps2_odbc(  void  *  pDb,  QIS_dynBmp_info  *  pMemParam,  char  *  pTimeBuf,  int  rcdId  );

BOOL  bUpdateImObjRegInfo_procMsgInput_scheduler_odbc(  void  *  pDb,  void  *  pSciParam,  void  *  pMisCntParam,  QY_MESSENGER_ID  *  pIdInfo  );
__declspec(  dllexport  )  BOOL  bStatImTasks_odbc(  void  *  pProcInfoParam,  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  );
BOOL  bDeleteFromTabById_odbc(  void  *  pDb,  int  iDbType, LPCTSTR  pTabName,  int  id  );
BOOL  bDeleteFromTabByIdInfo_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  pTabName,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );
BOOL  bDeleteImOtherRegInfoByAddr_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  LPCTSTR  pTabName,  MSGR_ADDR  *  pAddr  );
__declspec(  dllexport  )  int  iSelectImGrpMem_dlgSelect_isCli_odbc(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  HWND  idc_hWnd  );
__declspec(  dllexport  )  int  iSelectImObj_dlgSelect_isCli_odbc(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  );
#if  0
int  iSelectImObjAuth2_dlgSelect_isCli_odbc(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  );
#endif
__declspec(  dllexport  )  int  iSelectDynBmp_dlgSelect_isCli_odbc(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  );

//
BOOL  bGetImAmRcdBySth_myDb(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  short  usAuthType,  LPCTSTR  messengerName,  int  id,  QY_imAm_RCD  *  pObj  );
BOOL  bGetMessengerRegInfoBySth_myDb(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  pTabName,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_REGINFO  *  pRegInfo  );
BOOL  bGetImOtherRegInfoBySth_myDb(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  pTabName,  MSGR_ADDR  *  pAddr,  int  iRcdId,  QY_MESSENGER_REGINFO  *  pRegInfo  );
BOOL  bGetMeInfoBySth_myDb(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_INFO  *  pObj  );
BOOL  bGetMessengerInfoBySth_myDb(  QM_dbFuncs  *  pDbFuncs,  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_INFO  *  pObjParam,  QY_MESSENGER_REGINFO  *  pRegInfo,  QY_MESSENGER_REGINFO  *  pRegInfoInTab1,  QY_MESSENGER_phoneInfo  *  pPhoneInfo  );
int  insertImObj_recoverMessenger_myDb(  QM_dbFuncs  *  pDbFuncs,  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj,  time_t  tLastModifiedTime  );
int  updateImObj_recoverMessenger_myDb(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj,  time_t  tLastModifiedTime,  int  iRcdId  );
int  updateImObj_recoverMessenger2_myDb(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj,  time_t  tLastModifiedTime,  int  iRcdId  );

int  insertImObj_recoverImGrp_myDb(  void  *  pDb,  int  iDbType,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime  );
int  updateImObj_recoverImGrp_myDb(  void  *  pDb,  int  iDbType,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime,  int  iRcdId  );
int  updateImObj_recoverImGrp2_myDb(  void  *  pDb,  int  iDbType,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime,  int  iRcdId  );

BOOL  bGetImGrpInfoBySth_myDb(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  IM_GRP_INFO  *  pRcd  );
int  insertImGrp_recoverImGrp_myDb(  void  *  pDbParam,  int  iDbType,  IM_GRP_INFO  *  pGrpInfo  );
int  updateImGrp_recoverImGrp_myDb(  void  *  pDbParam,  int  iDbType,  IM_GRP_INFO  *  pGrpInfo,  int  iRcdId  );
BOOL  bGetImGrpMemBySth_myDb(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo_grp,  QY_MESSENGER_ID  *  pIdInfo_mem,  int  iRcdId,  IM_GRP_MEM  *  pRcd  );
//  int  insertImGrpMem_recoverImGrpMem_myDb(  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem  );
int  insertImGrpMem_recoverImGrpMem_myDb(  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime  );
//  int  updateImGrpMem_recoverImGrpMem_myDb(  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  int  iRcdId  );
int  updateImGrpMem_recoverImGrpMem_myDb(  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime,  int  iRcdId  );
int  updateImGrpMem_recoverImGrpMem2_myDb(  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime,  int  iRcdId  );
BOOL  bIdInfoExistedInImObjRegInfoTab_myDb(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_ID  *  pIdInfo,  LPCTSTR  tabName  );
int  insertImObjRegInfo_qisRegUsrInfoInTab_myDb(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  );
int  updateImObjRegInfo_qisRegUsrInfoInTab_myDb(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  );

int  qnmRegUsrInfo_myDb(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo  );
int  qisRegUsrInfo_myDb(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QY_MESSENGER_INFO  *  pMessengerInfo,  QY_MESSENGER_REGINFO  *  pRegInfo,  BOOL  bLogReRegEvent  );
BOOL  bSelectImMsg_logImMsg_myDb(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  IM_MSG_RCD  *  pRcd  );
int  insertImMsg_logImMsg_myDb(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  IM_MSG_RCD  *  pRcd  );
int  auditNewMessenger_myDb(  void  *  pReserved,  QY_MESSENGER_ID  *  pLastIdInfo,  void  *  pLicenseCtx,  void  *  pDb,  int  iDbType,  POLICY_imAuthCond  *  pAuthCond,  QY_MESSENGERAUTHTMP_RCD  *  pNewMessenger  );
BOOL  bGetImMsgRcdBySth_myDb(  void  *  pDbParam,  int  iDbType,  int  id,  IM_MSG_RCD  *  pObj  );
BOOL  bGetPcInfoByMac_myDb(  void  *  pDbParam,  char  *  mac,  unsigned  char  ucbMac0,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo  );
BOOL  bGetPcInfoByMacEx_myDb(  void  *  pDbParam,  char  *  mac,  unsigned  char  ucbMac0,  QY_DMITEM  *  pFieldIdTable,  QNM_PC_INFO  *  pPcInfo,  QNM_REG_INFO  *  pRegInfo,  QNM_REG_INFO  *  pRegInfoInTab1  );
BOOL  bLogEventFunc_is_myDb(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QIS_EVENT  *  pEvent  );
int  getEventInfoBySth_myDb(  void  *  pDbParam,  int  iDbType,  QIS_EVENT  *  pEvent  );
int  getPcEventInfoByMac0_myDb(  void  *  pDbParam,  QNM_PC_EVENT  *  pEvent  );
BOOL  bLogPcEventFunc_myDb(  void  *  pDb,  int  iDbType,  QNM_PC_EVENT  *  pEvent  );
int  qisRegOtherInfoInTab_myDb(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  MSGR_ADDR  *  pAddr,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  );
BOOL  bClearupImMsg_isCli_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  wherePart  );
BOOL  bClearupEvent_is_myDb(  QY_CLEARUPINFO  *  pClearupInfo  );
BOOL  bClearupImMsg_myDb(  QY_CLEARUPINFO  *  pClearupInfo  );
BOOL  bClearupImHisTask_myDb(  QY_CLEARUPINFO  *  pClearupInfo  );
int  getObjIndex_myDb(  QY_OBJ_DB  *  pObjDb,  int  iObjId,  QY_OBJINDEX_RCD  *  pObjIndex  );

int  listObjs_dlgMsgList_myDb(  void  *  pDbParam,  void  *  pQueryParam,  HWND  hListCtrlParam,  QY_MESSENGER_ID  *  pIdInfoParam  );
//
BOOL  bGetMessengerPhoneInfoBySth_myDb(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiDevType,  LPCTSTR  wDevIdStr,  QY_MESSENGER_ID  *  pIdInfo,  int  id,  QY_MESSENGER_phoneInfo  *  pRcd  );
int  recoverMessengerPhoneInfo_myDb(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  MSGR_ADDR  *  pAddr,  void  *  p1  );
//
int  updateImObj_me_myDb(  void  *  pDb,  int  iDbType,  QY_MESSENGER_INFO  *  pObj_me  );
BOOL  bGetImObjRulesReq_myDb(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  QY_MESSENGER_ID	*	pIdInfo_related,  LPCTSTR  condPart,  unsigned  short  usMaxMemsPerSnd,  REFRESH_imObjRules_req  *  pReq  );
BOOL  bGetImObjRuleRcdBySth_myDb(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem  *  pMem,  int  iRcdId,  QY_imObjRule_rcd  *  pRcd  );
int  insertImObjRule_recoverImObjRules_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  time_t  tLastModifiedTime  );
int  deleteImObjRule_recoverImObjRules_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  int  rcdId  );
int  updateImObjRule_recoverImObjRules_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  time_t  tLastModifiedTime,  int  rcdId  );
int  updateImObjRule_recoverImObjRules2_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem	*	pReqMem,  time_t  tLastModifiedTime,  int  rcdId  );
//  isCli
int  updateImObj_refreshImGrps_end_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiObjType,  time_t  tLastModifiedTime  );

BOOL	bNeedRetrieveImGrpMems_myDb(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName  );

int  updateImGrpMem_refreshImGrpMems_end_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  time_t  tLastModifiedTime  );

int  updateImObj_refreshContacts_end_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  time_t  tLastModifiedTime  );

//
int  deleteOldImObjRule_mcProcResp_refreshImObjRulesReq_myDb(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  MIS_MSG_INPUT  *  pMsgInput,  void  *  pCtxParam  );
int  selectNextImObjRule_mcProcResp_refreshImObjRulesReq_myDb(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  MIS_MSG_INPUT  *  pMsgInput,  void  *  pCtxParam,  QY_MESSENGER_ID	  *  pIdInfo_related  );
void  fillImObjs_msgr_myDb(  HWND  hDlg,  void  *  pVar,  void  *  pDb  );
void  fillImObjs_grp_myDb(  HWND  hDlg,  void  *  pVar,  void  *  pDb  );
int  selectImTask_dlgTalk_loadTasks_myDb(  HWND  hDlgTalk,  void  *  pTmpParam,  void  *  pDbParam  );
BOOL  bSelectImTask_storeTaskInDb_myDb(  void  *  pDb,  int  iDbType,  void  *  pMisCntParam,  IM_TASK_RCD  *  pRcd,  BOOL  bInHis  );
int  insertImTask_storeTaskInDb_myDb(  void  *  pDb,  int  iDbType,  void  *  pMisCntParam,  int  iTaskId_suggested,  IM_TASK_RCD  *  pRcd,  BOOL  bInHis  );
int  updateTaskStatus_myDb(  void  *  pDb,  int  iStatus,  int  iTaskId  );
BOOL  bMoveTask2His_myDb(  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  );
BOOL  bClearupDeletedImObjs_isClient_myDb(  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  );
BOOL  bGetImTaskRcdBySth_myDb(  void  *  pDb,  int  iDbType,  BOOL  bHisTab,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  time_t  tSendTime,  unsigned  int  uiTranNo,  int  id,  IM_TASK_RCD  *  pRcd  );
//
//BOOL  bSelectImGrpMem_dlgTalk_OnInitDialog_myDb(  HWND  hDlgTalkParam,  void  *  pDbParam,  void  *  pParam  );
//

//
BOOL  bGetQyDynBmpRcdBySth_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex,  int  id,  QY_dynBmp_RCD  *  pRcd  );

BOOL  bViewImTaskList_unproced_myDb(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImTaskList_cur_myDb(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImTaskList_his_myDb(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImObjList_myDb(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImGrpList_myDb(   QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImGrpMemList_isClient_myDb(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImObjRuleList_is_myDb(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb  );
//BOOL  bViewSharedDynBmpList_isClient_myDb(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewRegInfoList_myDb(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bInsertPhoneGuest_procMsgTalk_work_myDb(  void  *  pDbParam,  int  iDbType,  void  *  pQyMcParam,  MIS_MSG_TALK  *  pMsg,  void  *  pGuestParam  );
BOOL  bUpdateImTask_bChkQyMcEnv_mis_myDb(  void  *  pDb,  int  iStatus_set,  int  iStatus_0,  int  iStatus_1  );

int  deleteOldDynBmp_mcProcResp_retrieveDynBmps_myDb(  void  *  pDb,  int  iDbType,  char  *  pTimeBuf  );

//  int  deleteDynBmp_tmpHandler_delOld_dynBmpQ_myDb(  void  *  pDb,  int  id  );
//int  init_mcProcResp_retrieveDynBmps_myDb(  void  *  pDb,  void  *  pCtxParam  );
BOOL  bInsertDynBmp_mcProcResp_retrieveDynBmps_myDb(  void  *  pDb,  void  *  pMisCntParam,  QIS_dynBmp_info  *  pMem,  char  *  pTimeBuf  );
BOOL  bUpdateDynBmp_mcProcResp_retrieveDynBmps_myDb(  void  *  pDb,  QIS_dynBmp_info  *  pMemParam,  char  *  pTimeBuf,  int  rcdId  );
BOOL  bUpdateDynBmp_mcProcResp_retrieveDynBmps2_myDb(  void  *  pDb,  QIS_dynBmp_info  *  pMemParam,  char  *  pTimeBuf,  int  rcdId  );

BOOL  bUpdateImObjRegInfo_procMsgInput_scheduler_myDb(  void  *  pDb,  void  *  pSciParam,  void  *  pMisCntParam,  QY_MESSENGER_ID  *  pIdInfo  );

BOOL  bStatImTasks_myDb(  void  *  pProcInfoParam,  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  );
BOOL  bDeleteFromTabById_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  pTabName,  int  id  );
BOOL  bDeleteFromTabByIdInfo_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  pTabName,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );
BOOL  bDeleteImOtherRegInfoByAddr_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  LPCTSTR  pTabName,  MSGR_ADDR  *  pAddr  );
int  iSelectImGrpMem_dlgSelect_isCli_myDb(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  HWND  idc_hWnd  );
int  iSelectImObj_dlgSelect_isCli_myDb(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  );
#if  0
int  iSelectImObjAuth2_dlgSelect_isCli_myDb(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  );
#endif
int  iSelectDynBmp_dlgSelect_isCli_myDb(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  );




//  2012/01/30
__declspec(  dllexport  )  int  setQmDbFuncs_qm(  int  iDbType,  QM_dbFuncs  *  pDbFuncs  )
{
	int		iErr	=	-1;

	memset(  pDbFuncs,  0,  sizeof(  pDbFuncs[0]  )  );

	//
	setQmDb_default_Funcs(  pDbFuncs  );

	//
	switch  (  iDbType  )  {
			case  CONST_dbType_myDb:
				  #ifndef  __isCli__
						traceLog(  _T(  "Not supported"  )  );
						goto  errLabel;
				  #else
				  //
						pDbFuncs->pf_bGetImAmRcdBySth  =  bGetImAmRcdBySth_myDb;
					    pDbFuncs->pf_bGetMessengerRegInfoBySth  =  bGetMessengerRegInfoBySth_myDb;
						pDbFuncs->pf_bGetImOtherRegInfoBySth  =  bGetImOtherRegInfoBySth_myDb;
						pDbFuncs->pf_bGetMeInfoBySth  =  bGetMeInfoBySth_myDb;
						pDbFuncs->pf_bGetMessengerInfoBySth  =  bGetMessengerInfoBySth_myDb;
						pDbFuncs->pf_insertImObj_recoverMessenger  =  insertImObj_recoverMessenger_myDb;
						pDbFuncs->pf_updateImObj_recoverMessenger  =  updateImObj_recoverMessenger_myDb;
						pDbFuncs->pf_updateImObj_recoverMessenger2  =  updateImObj_recoverMessenger2_myDb;


						pDbFuncs->pf_insertImObj_recoverImGrp  =  insertImObj_recoverImGrp_myDb;					
						pDbFuncs->pf_updateImObj_recoverImGrp  =  updateImObj_recoverImGrp_myDb;
						pDbFuncs->pf_updateImObj_recoverImGrp2  =  updateImObj_recoverImGrp2_myDb;

						pDbFuncs->pf_bGetImGrpInfoBySth  =  bGetImGrpInfoBySth_myDb;
					    pDbFuncs->pf_insertImGrp_recoverImGrp  =  insertImGrp_recoverImGrp_myDb;
						pDbFuncs->pf_updateImGrp_recoverImGrp  =  updateImGrp_recoverImGrp_myDb;
						pDbFuncs->pf_bGetImGrpMemBySth  =  bGetImGrpMemBySth_myDb;

						pDbFuncs->pf_insertImGrpMem_recoverImGrpMem  =  insertImGrpMem_recoverImGrpMem_myDb;
						pDbFuncs->pf_updateImGrpMem_recoverImGrpMem  =  updateImGrpMem_recoverImGrpMem_myDb;
						pDbFuncs->pf_updateImGrpMem_recoverImGrpMem2  =  updateImGrpMem_recoverImGrpMem2_myDb;
						pDbFuncs->pf_bIdInfoExistedInImObjRegInfoTab  =  bIdInfoExistedInImObjRegInfoTab_myDb;
						pDbFuncs->pf_insertImObjRegInfo_qisRegUsrInfoInTab  =  insertImObjRegInfo_qisRegUsrInfoInTab_myDb;
						pDbFuncs->pf_updateImObjRegInfo_qisRegUsrInfoInTab  =  updateImObjRegInfo_qisRegUsrInfoInTab_myDb;
						
						pDbFuncs->pf_qnmRegUsrInfo  =  qnmRegUsrInfo_myDb;
						pDbFuncs->pf_qisRegUsrInfo  =  qisRegUsrInfo_myDb;			      
						pDbFuncs->pf_bSelectImMsg_logImMsg  =   bSelectImMsg_logImMsg_myDb;				  
						pDbFuncs->pf_insertImMsg_logImMsg  =  insertImMsg_logImMsg_myDb;				  
						pDbFuncs->pf_auditNewMessenger  =  auditNewMessenger_myDb;
						pDbFuncs->pf_bGetImMsgRcdBySth  =  bGetImMsgRcdBySth_myDb;
						pDbFuncs->pf_bLogEventFunc_is  =  bLogEventFunc_is_myDb;
						pDbFuncs->pf_bGetPcInfoByMac  =  bGetPcInfoByMac_myDb;
						pDbFuncs->pf_bGetPcInfoByMacEx  =  bGetPcInfoByMacEx_myDb;
						pDbFuncs->pf_getEventInfoBySth  =  getEventInfoBySth_myDb;
						pDbFuncs->pf_getPcEventInfoByMac0  =  getPcEventInfoByMac0_myDb;
						pDbFuncs->pf_bLogPcEventFunc  =  bLogPcEventFunc_myDb;
						pDbFuncs->pf_qisRegOtherInfoInTab  =  qisRegOtherInfoInTab_myDb;
						pDbFuncs->pf_bClearupImMsg_isCli  =  bClearupImMsg_isCli_myDb;
						pDbFuncs->pf_bClearupEvent_is  =  bClearupEvent_is_myDb;
						pDbFuncs->pf_bClearupImMsg  =  bClearupImMsg_myDb;
						pDbFuncs->pf_bClearupImHisTask  =  bClearupImHisTask_myDb;
						pDbFuncs->pf_getObjIndex  =  getObjIndex_myDb;

										  
						pDbFuncs->pf_bGetMessengerPhoneInfoBySth  =  bGetMessengerPhoneInfoBySth_myDb;				  
						pDbFuncs->pf_recoverMessengerPhoneInfo  =  recoverMessengerPhoneInfo_myDb;				  
						//
				  
						pDbFuncs->pf_updateImObj_me  =  updateImObj_me_myDb;				  
						pDbFuncs->pf_bGetImObjRulesReq  =  bGetImObjRulesReq_myDb;				  
						pDbFuncs->pf_bGetImObjRuleRcdBySth  =  bGetImObjRuleRcdBySth_myDb;				  
						pDbFuncs->pf_insertImObjRule_recoverImObjRules  =  insertImObjRule_recoverImObjRules_myDb;				  
						pDbFuncs->pf_deleteImObjRule_recoverImObjRules  =  deleteImObjRule_recoverImObjRules_myDb;				  
						pDbFuncs->pf_updateImObjRule_recoverImObjRules  =  updateImObjRule_recoverImObjRules_myDb;
						
						pDbFuncs->pf_updateImObjRule_recoverImObjRules2  =  updateImObjRule_recoverImObjRules2_myDb;				  
						//
						//  pDbFuncs->pf_mcProcResp_refreshImGrps  =  mcProcResp_refreshImGrps_myDb;
						//  pDbFuncs->pf_mcProcResp_refreshImGrps_end  =  mcProcResp_refreshImGrps_end_myDb;
						
						pDbFuncs->pf_updateImObj_refreshImGrps_end  =  updateImObj_refreshImGrps_end_myDb;

						//
						pDbFuncs->pf_bNeedRetrieveImGrpMems  =  bNeedRetrieveImGrpMems_myDb;
						//  pDbFuncs->pf_mcProcResp_refreshImGrpMems  =  mcProcResp_refreshImGrpMems_myDb;
						//  pDbFuncs->pf_mcProcResp_refreshImGrpMems_end  =  mcProcResp_refreshImGrpMems_end_myDb;
						pDbFuncs->pf_updateImGrpMem_refreshImGrpMems_end  =  updateImGrpMem_refreshImGrpMems_end_myDb;

						//  pDbFuncs->pf_mcProcResp_refreshContacts  =  mcProcResp_refreshContacts_myDb;
						//  pDbFuncs->pf_mcProcResp_refreshContacts_end  =  mcProcResp_refreshContacts_end_myDb;
						pDbFuncs->pf_updateImObj_refreshContacts_end  =  updateImObj_refreshContacts_end_myDb;
						//
						pDbFuncs->pf_deleteOldImObjRule_mcProcResp_refreshImObjRulesReq  =  deleteOldImObjRule_mcProcResp_refreshImObjRulesReq_myDb;
						pDbFuncs->pf_selectNextImObjRule_mcProcResp_refreshImObjRulesReq  =  selectNextImObjRule_mcProcResp_refreshImObjRulesReq_myDb;
						pDbFuncs->pf_fillImObjs_msgr		=  fillImObjs_msgr_myDb;
						pDbFuncs->pf_fillImObjs_grp		=  fillImObjs_grp_myDb;
						pDbFuncs->pf_selectImTask_dlgTalk_loadTasks  =  selectImTask_dlgTalk_loadTasks_myDb;
						pDbFuncs->pf_bSelectImTask_storeTaskInDb  =  bSelectImTask_storeTaskInDb_myDb;
						pDbFuncs->pf_insertImTask_storeTaskInDb  =  insertImTask_storeTaskInDb_myDb;
						pDbFuncs->pf_updateTaskStatus  =  updateTaskStatus_myDb;
						pDbFuncs->pf_bMoveTask2His  =  bMoveTask2His_myDb;
						pDbFuncs->pf_bClearupDeletedImObjs_isClient  =  bClearupDeletedImObjs_isClient_myDb;
						pDbFuncs->pf_bGetImTaskRcdBySth  =  bGetImTaskRcdBySth_myDb;
						//
						//pDbFuncs->pf_bSelectImGrpMem_dlgTalk_OnInitDialog  =  bSelectImGrpMem_dlgTalk_OnInitDialog_myDb;
						//
						pDbFuncs->pf_bGetQyDynBmpRcdBySth  =  bGetQyDynBmpRcdBySth_myDb;
						
						pDbFuncs->pf_listObjs_dlgMsgList  =  listObjs_dlgMsgList_myDb;
						pDbFuncs->pf_bViewImTaskList_unproced  =  bViewImTaskList_unproced_myDb;
						pDbFuncs->pf_bViewImTaskList_cur  =  bViewImTaskList_cur_myDb;
						pDbFuncs->pf_bViewImTaskList_his  =  bViewImTaskList_his_myDb;

						pDbFuncs->pf_bViewImObjList  =  bViewImObjList_myDb;
						pDbFuncs->pf_bViewRegInfoList  =  bViewRegInfoList_myDb;						
						pDbFuncs->pf_bViewImGrpList  =  bViewImGrpList_myDb;
						pDbFuncs->pf_bViewImGrpMemList_isClient  =  bViewImGrpMemList_isClient_myDb;
						pDbFuncs->pf_bViewImObjRuleList_is  =  bViewImObjRuleList_is_myDb;
						//pDbFuncs->pf_bViewSharedDynBmpList_isClient  =  bViewSharedDynBmpList_isClient_myDb;

						pDbFuncs->pf_bInsertPhoneGuest_procMsgTalk_work  =  bInsertPhoneGuest_procMsgTalk_work_myDb;
						pDbFuncs->pf_bUpdateImTask_bChkQyMcEnv_mis  =  bUpdateImTask_bChkQyMcEnv_mis_myDb;
						pDbFuncs->pf_deleteOldDynBmp_mcProcResp_retrieveDynBmps  =  deleteOldDynBmp_mcProcResp_retrieveDynBmps_myDb;
						//  pDbFuncs->pf_deleteDynBmp_tmpHandler_delOld_dynBmpQ  = deleteDynBmp_tmpHandler_delOld_dynBmpQ_myDb;
						//pDbFuncs->pf_init_mcProcResp_retrieveDynBmps  =  init_mcProcResp_retrieveDynBmps_myDb;
						pDbFuncs->pf_bInsertDynBmp_mcProcResp_retrieveDynBmps  =  bInsertDynBmp_mcProcResp_retrieveDynBmps_myDb;
						pDbFuncs->pf_bUpdateDynBmp_mcProcResp_retrieveDynBmps  =  bUpdateDynBmp_mcProcResp_retrieveDynBmps_myDb;
						pDbFuncs->pf_bUpdateDynBmp_mcProcResp_retrieveDynBmps2  =  bUpdateDynBmp_mcProcResp_retrieveDynBmps2_myDb;

						pDbFuncs->pf_bUpdateImObjRegInfo_procMsgInput_scheduler  =  bUpdateImObjRegInfo_procMsgInput_scheduler_myDb;
						pDbFuncs->pf_bStatImTasks  =  bStatImTasks_myDb;
						pDbFuncs->pf_bDeleteFromTabById  =  bDeleteFromTabById_myDb;
						pDbFuncs->pf_bDeleteFromTabByIdInfo  =  bDeleteFromTabByIdInfo_myDb;
						pDbFuncs->pf_bDeleteImOtherRegInfoByAddr  =  bDeleteImOtherRegInfoByAddr_myDb;
						pDbFuncs->pf_iSelectImGrpMem_dlgSelect_isCli  =  iSelectImGrpMem_dlgSelect_isCli_myDb;
						pDbFuncs->pf_iSelectImObj_dlgSelect_isCli  =  iSelectImObj_dlgSelect_isCli_myDb;
#if  0
						pDbFuncs->pf_iSelectImObjAuth2_dlgSelect_isCli  =  iSelectImObjAuth2_dlgSelect_isCli_myDb;
#endif
						pDbFuncs->pf_iSelectDynBmp_dlgSelect_isCli  = iSelectDynBmp_dlgSelect_isCli_myDb;

  				  #endif
				  //
				  break;
			default:
				//
#ifndef  __isCli__
					pDbFuncs->pf_bGetImAmRcdBySth  =   bGetImAmRcdBySth_odbc;
				    pDbFuncs->pf_bGetMessengerRegInfoBySth  =  bGetMessengerRegInfoBySth_odbc;
					pDbFuncs->pf_bGetImOtherRegInfoBySth  =  bGetImOtherRegInfoBySth_odbc;
					pDbFuncs->pf_bGetMeInfoBySth  =  bGetMeInfoBySth_odbc;
					pDbFuncs->pf_bGetMessengerInfoBySth  =  bGetMessengerInfoBySth_odbc;
					pDbFuncs->pf_insertImObj_recoverMessenger  =  insertImObj_recoverMessenger_odbc;
					pDbFuncs->pf_updateImObj_recoverMessenger  =  updateImObj_recoverMessenger_odbc;
					pDbFuncs->pf_updateImObj_recoverMessenger2  =  updateImObj_recoverMessenger2_odbc;

					
					pDbFuncs->pf_insertImObj_recoverImGrp  =  insertImObj_recoverImGrp_odbc;
					pDbFuncs->pf_updateImObj_recoverImGrp  =  updateImObj_recoverImGrp_odbc;
					pDbFuncs->pf_updateImObj_recoverImGrp2  =  updateImObj_recoverImGrp2_odbc;

					pDbFuncs->pf_bGetImGrpInfoBySth  =  bGetImGrpInfoBySth_odbc;
					pDbFuncs->pf_insertImGrp_recoverImGrp  =  insertImGrp_recoverImGrp_odbc;
					pDbFuncs->pf_updateImGrp_recoverImGrp  =  updateImGrp_recoverImGrp_odbc;
					pDbFuncs->pf_bGetImGrpMemBySth  =  bGetImGrpMemBySth_odbc;
					pDbFuncs->pf_insertImGrpMem_recoverImGrpMem  =  insertImGrpMem_recoverImGrpMem_odbc;
					pDbFuncs->pf_updateImGrpMem_recoverImGrpMem  =  updateImGrpMem_recoverImGrpMem_odbc;
					pDbFuncs->pf_updateImGrpMem_recoverImGrpMem2  =  updateImGrpMem_recoverImGrpMem2_odbc;
					pDbFuncs->pf_bIdInfoExistedInImObjRegInfoTab  =  bIdInfoExistedInImObjRegInfoTab_odbc;
					pDbFuncs->pf_insertImObjRegInfo_qisRegUsrInfoInTab  =  insertImObjRegInfo_qisRegUsrInfoInTab_odbc;
					pDbFuncs->pf_updateImObjRegInfo_qisRegUsrInfoInTab  =  updateImObjRegInfo_qisRegUsrInfoInTab_odbc;

					pDbFuncs->pf_qnmRegUsrInfo  =  qnmRegUsrInfo_odbc;
				    pDbFuncs->pf_qisRegUsrInfo  =  qisRegUsrInfo_odbc;
				    pDbFuncs->pf_bSelectImMsg_logImMsg  =  bSelectImMsg_logImMsg_odbc;
					pDbFuncs->pf_insertImMsg_logImMsg  =  insertImMsg_logImMsg_odbc;
					pDbFuncs->pf_auditNewMessenger  =  auditNewMessenger_odbc;
					pDbFuncs->pf_bGetImMsgRcdBySth  =  bGetImMsgRcdBySth_odbc;
					pDbFuncs->pf_bLogEventFunc_is  =  bLogEventFunc_is_odbc;
					pDbFuncs->pf_bGetPcInfoByMac  =  bGetPcInfoByMac_odbc;
					pDbFuncs->pf_bGetPcInfoByMacEx  =  bGetPcInfoByMacEx_odbc;
					pDbFuncs->pf_getEventInfoBySth  =  getEventInfoBySth_odbc;
					pDbFuncs->pf_getPcEventInfoByMac0  =  getPcEventInfoByMac0_odbc;
					pDbFuncs->pf_bLogPcEventFunc  =  bLogPcEventFunc_odbc;
					pDbFuncs->pf_qisRegOtherInfoInTab  =  qisRegOtherInfoInTab_odbc;
					pDbFuncs->pf_bClearupImMsg_isCli  =  bClearupImMsg_isCli_odbc;
					pDbFuncs->pf_bClearupEvent_is  =  bClearupEvent_is_odbc;
					pDbFuncs->pf_bClearupImMsg  =  bClearupImMsg_odbc;
					pDbFuncs->pf_bClearupImHisTask  =  bClearupImHisTask_odbc;
					pDbFuncs->pf_getObjIndex  =  getObjIndex_odbc;

					pDbFuncs->pf_bGetMessengerPhoneInfoBySth  =  bGetMessengerPhoneInfoBySth_odbc;
					pDbFuncs->pf_recoverMessengerPhoneInfo  =  recoverMessengerPhoneInfo_odbc;

					//
					pDbFuncs->pf_updateImObj_me  =  updateImObj_me_odbc;
					pDbFuncs->pf_bGetImObjRulesReq  =  bGetImObjRulesReq_odbc;
					pDbFuncs->pf_bGetImObjRuleRcdBySth  =  bGetImObjRuleRcdBySth_odbc;
					pDbFuncs->pf_insertImObjRule_recoverImObjRules  =  insertImObjRule_recoverImObjRules_odbc;
					pDbFuncs->pf_deleteImObjRule_recoverImObjRules  =  deleteImObjRule_recoverImObjRules_odbc;
					pDbFuncs->pf_updateImObjRule_recoverImObjRules  =  updateImObjRule_recoverImObjRules_odbc;
					pDbFuncs->pf_updateImObjRule_recoverImObjRules2  =  updateImObjRule_recoverImObjRules2_odbc;

					//
					pDbFuncs->pf_updateImObj_refreshImGrps_end  =  updateImObj_refreshImGrps_end_odbc;
					//
					pDbFuncs->pf_bNeedRetrieveImGrpMems  =  bNeedRetrieveImGrpMems_odbc;
					//
					pDbFuncs->pf_updateImGrpMem_refreshImGrpMems_end  =  updateImGrpMem_refreshImGrpMems_end_odbc;
					//
					pDbFuncs->pf_updateImObj_refreshContacts_end  =  updateImObj_refreshContacts_end_odbc;

					//
					pDbFuncs->pf_deleteOldImObjRule_mcProcResp_refreshImObjRulesReq  =  deleteOldImObjRule_mcProcResp_refreshImObjRulesReq_odbc;
					pDbFuncs->pf_selectNextImObjRule_mcProcResp_refreshImObjRulesReq  =  selectNextImObjRule_mcProcResp_refreshImObjRulesReq_odbc;

					pDbFuncs->pf_fillImObjs_msgr		=  fillImObjs_msgr_odbc;
					pDbFuncs->pf_fillImObjs_grp		=  fillImObjs_grp_odbc;
					pDbFuncs->pf_selectImTask_dlgTalk_loadTasks  =  selectImTask_dlgTalk_loadTasks_odbc;
					pDbFuncs->pf_bSelectImTask_storeTaskInDb  =  bSelectImTask_storeTaskInDb_odbc;
					pDbFuncs->pf_insertImTask_storeTaskInDb  =  insertImTask_storeTaskInDb_odbc;
					pDbFuncs->pf_updateTaskStatus  =  updateTaskStatus_odbc;
					pDbFuncs->pf_bMoveTask2His  =  bMoveTask2His_odbc;
					pDbFuncs->pf_bClearupDeletedImObjs_isClient  =  bClearupDeletedImObjs_isClient_odbc;
					pDbFuncs->pf_bGetImTaskRcdBySth  =  bGetImTaskRcdBySth_odbc;
					//
					//pDbFuncs->pf_bSelectImGrpMem_dlgTalk_OnInitDialog  =  bSelectImGrpMem_dlgTalk_OnInitDialog_odbc;
					//
					pDbFuncs->pf_bGetQyDynBmpRcdBySth  =  bGetQyDynBmpRcdBySth_odbc;
					
					pDbFuncs->pf_listObjs_dlgMsgList  =  listObjs_dlgMsgList_odbc;
					pDbFuncs->pf_bViewImTaskList_unproced  =  bViewImTaskList_unproced_odbc;
					pDbFuncs->pf_bViewImTaskList_cur  =  bViewImTaskList_cur_odbc;
					pDbFuncs->pf_bViewImTaskList_his  =  bViewImTaskList_his_odbc;
					
					pDbFuncs->pf_bViewImObjList  =  bViewImObjList_odbc;
					pDbFuncs->pf_bViewRegInfoList  =  bViewRegInfoList_odbc;
					pDbFuncs->pf_bViewImGrpList  =  bViewImGrpList_odbc;
					pDbFuncs->pf_bViewImGrpMemList_isClient  =  bViewImGrpMemList_isClient_odbc;
					pDbFuncs->pf_bViewImObjRuleList_is  =  bViewImObjRuleList_is_odbc;
					//pDbFuncs->pf_bViewSharedDynBmpList_isClient  =  bViewSharedDynBmpList_isClient_odbc;
					
					pDbFuncs->pf_bInsertPhoneGuest_procMsgTalk_work  =  bInsertPhoneGuest_procMsgTalk_work_odbc;
					pDbFuncs->pf_bUpdateImTask_bChkQyMcEnv_mis  =  bUpdateImTask_bChkQyMcEnv_mis_odbc;

					pDbFuncs->pf_deleteOldDynBmp_mcProcResp_retrieveDynBmps  =  deleteOldDynBmp_mcProcResp_retrieveDynBmps_odbc;
					//  pDbFuncs->pf_deleteDynBmp_tmpHandler_delOld_dynBmpQ  =  deleteDynBmp_tmpHandler_delOld_dynBmpQ_odbc;
					//pDbFuncs->pf_init_mcProcResp_retrieveDynBmps  =  init_mcProcResp_retrieveDynBmps_odbc;
					pDbFuncs->pf_bInsertDynBmp_mcProcResp_retrieveDynBmps  =  bInsertDynBmp_mcProcResp_retrieveDynBmps_odbc;
					pDbFuncs->pf_bUpdateDynBmp_mcProcResp_retrieveDynBmps  =  bUpdateDynBmp_mcProcResp_retrieveDynBmps_odbc;
					pDbFuncs->pf_bUpdateDynBmp_mcProcResp_retrieveDynBmps2  =  bUpdateDynBmp_mcProcResp_retrieveDynBmps2_odbc;

					pDbFuncs->pf_bUpdateImObjRegInfo_procMsgInput_scheduler  =  bUpdateImObjRegInfo_procMsgInput_scheduler_odbc;
					pDbFuncs->pf_bStatImTasks  =  bStatImTasks_odbc;
					pDbFuncs->pf_bDeleteFromTabById  =  bDeleteFromTabById_odbc;
					pDbFuncs->pf_bDeleteFromTabByIdInfo  =  bDeleteFromTabByIdInfo_odbc;
					pDbFuncs->pf_bDeleteImOtherRegInfoByAddr  =  bDeleteImOtherRegInfoByAddr_odbc;
					pDbFuncs->pf_iSelectImGrpMem_dlgSelect_isCli  =  iSelectImGrpMem_dlgSelect_isCli_odbc;
					pDbFuncs->pf_iSelectImObj_dlgSelect_isCli  =  iSelectImObj_dlgSelect_isCli_odbc;
#if  0
					pDbFuncs->pf_iSelectImObjAuth2_dlgSelect_isCli  =  iSelectImObjAuth2_dlgSelect_isCli_odbc;
#endif
					pDbFuncs->pf_iSelectDynBmp_dlgSelect_isCli  = iSelectDynBmp_dlgSelect_isCli_odbc;

					//
#endif

					break;
	}

	iErr  =  0;
	errLabel:
	return  iErr;
}


 
