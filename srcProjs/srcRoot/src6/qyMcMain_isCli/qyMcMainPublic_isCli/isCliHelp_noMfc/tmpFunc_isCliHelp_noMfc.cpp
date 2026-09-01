
#include	"stdafx.h"

#include	<wincrypt.h>
#include	"qyMcMainCommon.h"
#include	"qvcfDefs.h"
#include	"ctxQmc.h"
#include	"isCliHelpPublic.h"
#include <dlgtalkproc.h>
#include <makeDynaMenu.h>

//
int  listObjs_dlgMsgList_myDb(void* pDbParam, void* pQueryParam, HWND  hListCtrlParam, QY_MESSENGER_ID* pIdInfoParam)
{
	return -1;
}

void  fillImObjs_msgr_myDb(HWND  hDlg, void* pVar, void* pDb)
{

}

void  fillImObjs_grp_myDb(HWND  hDlg, void* pVar, void* pDb)
{

}



int  selectImTask_dlgTalk_loadTasks_myDb(HWND  hDlgTalk, void* pTmpParam, void* pDbParam)
{
	return -1;
}

BOOL  bViewImTaskList_unproced_myDb(QY_OBJ_DB* pObjDb, LPCTSTR  docName, LPCTSTR  wherePart)
{
	return false;
}


BOOL  bViewImTaskList_cur_myDb(QY_OBJ_DB* pObjDb, LPCTSTR  docName, LPCTSTR  wherePart)
{
	return false;
}


BOOL  bViewImTaskList_his_myDb(QY_OBJ_DB* pObjDb, LPCTSTR  docName, LPCTSTR  wherePart)
{
	return false;
}

BOOL  bViewImObjList_myDb(QY_OBJ_DB* pObjDb, LPCTSTR  docName, LPCTSTR  wherePart)
{
	return false;
}


BOOL  bViewImGrpList_myDb(QY_MC  *  pQyMc,  QY_OBJ_DB* pObjDb, LPCTSTR  docName, LPCTSTR  wherePart)
{
	return false;
}


BOOL  bViewImGrpMemList_isClient_myDb(QY_MC  *  pQyMc,  QY_OBJ_DB* pObjDb, LPCTSTR  docName, LPCTSTR  wherePart)
{
	return false;
}

BOOL  bViewImObjRuleList_is_myDb(QY_MC *pQyMc,QY_OBJ_DB* pObjDb)
{
	return false;
}

BOOL  bViewRegInfoList_myDb(QY_OBJ_DB* pObjDb, LPCTSTR  docName, LPCTSTR  wherePart)
{
	return false;
}

BOOL  bInsertPhoneGuest_procMsgTalk_work_myDb(void* pDbParam, int  iDbType, void* pQyMcParam, MIS_MSG_TALK* pMsg, void* pGuestParam)
{
	return false;
}

BOOL  bUpdateImTask_bChkQyMcEnv_mis_myDb(void* pDb, int  iStatus_set, int  iStatus_0, int  iStatus_1)
{
	return false;
}

int  deleteOldDynBmp_mcProcResp_retrieveDynBmps_myDb(void* pDb, int  iDbType, char* pTimeBuf)
{
	return -1;
}

BOOL  bInsertDynBmp_mcProcResp_retrieveDynBmps_myDb(void* pDb, void* pMisCntParam, QIS_dynBmp_info* pMem, char* pTimeBuf)
{
	return false;
}

BOOL  bUpdateDynBmp_mcProcResp_retrieveDynBmps_myDb(void* pDb, QIS_dynBmp_info* pMem, char* pTimeBuf, int  rcdId)
{
	return false;
}

BOOL  bUpdateDynBmp_mcProcResp_retrieveDynBmps2_myDb(void* pDb, QIS_dynBmp_info* pMem, char* pTimeBuf, int  rcdId)
{
	return false;
}

BOOL  bUpdateImObjRegInfo_procMsgInput_scheduler_myDb(void* pDb, void* pSciParam, void* pMisCntParam, QY_MESSENGER_ID* pIdInfo)
{
	return false;
}


BOOL  bStatImTasks_myDb(void* pProcInfoParam, void* pMisCntParam, void* pDb, int  iDbType)
{
	return false;
}

BOOL  bDeleteFromTabById_myDb(void* pDb, int  iDbType, LPCTSTR  pTabName, int  id)
{
	return  FALSE;
}
BOOL  bDeleteFromTabByIdInfo_myDb(void* pDb, int  iDbType, LPCTSTR  pTabName, LPCTSTR  misServName, QY_MESSENGER_ID* pIdInfo)
{
	return  FALSE;
}

BOOL  bDeleteImOtherRegInfoByAddr_myDb(void* pDb, int  iDbType, LPCTSTR  misServName, LPCTSTR  pTabName, MSGR_ADDR* pAddr)
{
	return  FALSE;
}

int  iSelectImGrpMem_dlgSelect_isCli_myDb(void* pDb, int  iDbType, LPCTSTR  misServName, QY_MESSENGER_ID* pIdInfo, HWND  idc_hWnd)
{
	return  -1;
}

int  iSelectImObj_dlgSelect_isCli_myDb(void* pDb, int  iDbType, LPCTSTR  misServName, HWND  idc_hWnd)
{
	return -1;
}

int  iSelectDynBmp_dlgSelect_isCli_myDb(void* pDb, int  iDbType, LPCTSTR  misServName, HWND  idc_hWnd)
{
	return -1;
}

__declspec(dllexport)  int  getPcStatusInfo(QM_dbFuncs* pDbFuncs, void* pDb, char* mac0, QY_DMITEM* pFieldIdTable, PC_STATUS_INFO* pInfo)
{
	return -1;
}

__declspec(dllexport)  void* getDlgDesktopsMonVar(HWND  hDlgDesktopsMon)
{
	return NULL;
}

__declspec(dllexport)  void* getDlgDynBmpsVar(HWND  hDlgDynBmps)
{
	return NULL;
}

__declspec(dllexport) int  myDrawTxt(LPCTSTR  str, int nPointSize, LPCTSTR lpszFaceName, COLORREF crColor, int  iX, int iY, int  iW, int  iH, HWND  hWnd_dst, HDC  hDc)
{
	return -1;
}

__declspec(dllexport)  int  myListCtrl_InsertColumn(HWND  hListCtrl, int nCol, const LVCOLUMN* pColumn)
{
	return -1;
}


__declspec(dllexport)  BOOL myListCtrl_SetItemText(HWND  hListCtrl, int nItem, int nSubItem, LPCTSTR lpszText)
{
	return -1;
}

__declspec(dllexport)  BOOL myListCtrl_SetItemData(HWND  hListCtrl, int nItem, DWORD_PTR dwData)
{
	return false;
}

__declspec(dllexport)  BOOL myListCtrl_DeleteAllItems(HWND  hListCtrl)
{
	return false;
}
_declspec(dllexport)  int  myListCtrl_InsertItem(HWND  hListCtrl, int nItem, LPCTSTR lpszItem)
{
	return -1;
}

__declspec(dllexport)  int  myListCtrl_InsertItem(HWND  hListCtrl, int nItem, LPCTSTR lpszItem, int nImage)
{
	return -1;
}


__declspec(dllexport)  int  refreshGrpMemListStatus(HWND  hCurTalk)
{
	return -1;
}

__declspec(dllexport)  int  closeInstantAssistant(HWND  hDlgTalk)
{
	return -1;
}

__declspec(dllexport)  int  dlgTalk_doLayout(HWND  hDlgTalk)
{
	return -1;
}

__declspec(dllexport)  LRESULT  myGuiSendMessage(HWND hWnd, int  iWndContentType, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}


__declspec(dllexport)  int  fillTalkerList_func(HWND  hCurTalk, HWND  hTool, void* pVIDEO_CONFERENCE_STATUS, int  idcList)
{
	return -1;
}

#if  0
__declspec(dllexport)  void  exitAvRecord(void* pCOMPRESS_VIDEO)
{
	return;
}
#endif



int  WINAPI  myMessageBox(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
	return -1;
}

__declspec(dllexport)  BOOL  bClearQnmTmpTab(QY_MC* pQyMc)
{
	return TRUE;
}

__declspec(dllexport)  int  showDlgObjs(HINSTANCE  g_hInst, HWND  hParent, void* pDLG_guiDataParam_objs)
{
	return -1;
}

#if  0
__declspec(dllexport)  int  startAvRecord(MC_VAR_common* pProcInfo, int  iIndex_screenCapProcInfo, HWND  hWnd_notifyEnd)
{
	return -1;
}

__declspec(dllexport) RECT  getSelectedRect()
{
	RECT rc;
	memset(&rc, 0, sizeof(rc));
	return rc;
}


__declspec(dllexport)  BOOL  bRemoteAssist_avRecord()
{
	return false;
}


__declspec(dllexport)  BOOL  bDirectX_avRecord()
{
	return false;
}

__declspec(dllexport)  int  getiParam_avRecord()	//  2009/09/13
{
	return -1;
}

__declspec(dllexport)  int  setFps_capScreen(int  fps)
{
	return -1;
}

__declspec(dllexport)  int  getSize_qyAvRecord()
{
	return 0;
}
#endif

__declspec(dllexport)  int  dlg_YTCmd_shareDynBmps(HWND  hDlg_ptz, int  nResourceID, void* p0, void* p1)
{
	return -1;
}

__declspec(dllexport)  int iidoRemotePtzCmd(void* p0, PTZ_control_cmd* pReq, PARAM_viewLocalPtzControl* pParam, QIS_ptz_wnd* pPtzWnd)
{
	return -1;
}

__declspec(dllexport)  int  myListCtrl_GetItemCount(HWND  hListCtrl)
{
	return -1;
}

__declspec(dllexport)  BOOL myListCtrl_SetItemState(HWND  hListCtrl, int nItem, UINT nState, UINT nMask)
{
	return false;
}

__declspec(dllexport)  BOOL myListCtrl_GetColumn(HWND  hListCtrl, int nCol, LVCOLUMN* pColumn)
{
	return false;
}

__declspec(dllexport)  int  myListCtrl_FindItem(HWND  hListCtrl, LVFINDINFO* pFindInfo, int nStart)
{
	return -1;
}

__declspec(dllexport)  BOOL myListCtrl_GetItem(HWND  hListCtrl, LVITEM* pItem)
{
	return false;
}

__declspec(dllexport)  BOOL myListCtrl_SetItem(HWND  hListCtrl, LVITEM* pItem)
{
	return false;
}

__declspec(dllexport)  BOOL myListCtrl_Update(HWND  hListCtrl, int nItem)
{
	return false;
}

__declspec(dllexport)  BOOL myListCtrl_ModifyStyle(HWND  hListCtrl, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	return false;
}

__declspec(dllexport)  DWORD myListCtrl_SetExtendedStyle(HWND  hListCtrl, DWORD dwNewStyle)
{
	return 0;
}

__declspec(dllexport)  void* myListCtrl_SetImageList(HWND  hListCtrl, void* pImageList, int nImageList)
{
	return mynull;
}

#if  0
__declspec(dllexport)  int  getLevel_avRecord()		//  2012/10/29
{
	return 0;
}
#endif

__declspec(dllexport)  void* getDlgMsgToolVar(HWND  hDlgMsgTool)
{
	return mynull;
}

__declspec(dllexport)  int  getSubtitlesCfg(int  iCapType, int  iCapSubType, int  iUsage, SUBTITLES_cfg* pSubtitlesCfg)
{
	return -1;
}


__declspec(dllexport)  int  addToWallGpsMgr(HWND  hDlgTalk, int  iIndex_shadow, void* pmyGPS_POSITION, HWND  hDlgWall)
{
	return -1;
}

__declspec(dllexport)  int  removeNotification(QY_MESSENGER_ID* pIdInfo_logicalPeer)
{
	return -1;
}

__declspec(dllexport)  int  doDoc_doTable_byRowId_param(void* pDLG_TALK_var, void* pPARAM_PROC_ROW)
{
	return -1;
}


__declspec(dllexport)	int  printHtmlEdit(void* pCMyHtmlEditCtrl)
{
	return -1;
}

__declspec(dllexport)  int  sizeAllControls_dlgTalk(HWND  hDlg, void* pDLG_TALK_var, RECT* pRect)
{
	return -1;
}

__declspec(dllexport)  int  dlgTalk_OnCmd_shareScreen(HWND  hCurTalk, BOOL  bRemoteAssist)
{
	return -1;
}

__declspec(dllexport)  int  activateImTask(HWND  hDlgTalk, void* pDLG_TALK_var, int  iTaskId_activated)
{
	return -1;
}

__declspec(dllexport)  int  dlgTalk_SetPicRect(HWND  hDlgTalk, int  w, int  h, BOOL  bMoveWindow)
{
	return -1;
}

__declspec(dllexport)  int  dlgTalk_processPointerEvent(HWND  hCurTalk, int  x, int  y, UINT nFlags, BOOL  bMouseMove, BOOL  bSendForce)
{
	return -1;
}

//__declspec(dllexport)  int  addToRecentMsg(HWND  hDlgTalk, void* pDLG_TALK_var, long  lRowIndex, int  iTaskId, MIS_MSG_TASK  * pMsgTask,  QY_MESSENGER_ID* pIdInfo_talker, LPCTSTR  talkerDesc, unsigned  short  usOp, int  iStatus, char* timeBuf, LPCTSTR  rowIdStr, LPCTSTR  content, BOOL  bFollowingRows, BOOL  bScrollIntoView, TCHAR* txtBuf, unsigned  int  uiTxtBufCnt)
//__declspec(dllexport)  int  addToRecentMsg(HWND  hDlgTalk, void* pDLG_TALK_var, long  lRowIndex, int  iTaskId, MIS_MSG_TASK* pMsgTask, MIS_MSG_taskStatus* pMsgTaskStatus, QY_MESSENGER_ID idInfo_talker, LPCTSTR  talkerDesc, unsigned  short  usOp, int  iStatus, char* timeBuf, LPCTSTR  rowIdStr, LPCTSTR  content, BOOL  bFollowingRows, BOOL  bScrollIntoView, TCHAR* txtBuf, unsigned  int  uiTxtBufCnt)
__declspec(dllexport)  int  addToRecentMsg(HWND  hDlgTalk, void* pDLG_TALK_var, long  lRowIndex, int  iTaskId, MIS_MSGU* pMsgU, MIS_MSG_taskStatus* pMsgTaskStatus, QY_MESSENGER_ID idInfo_talker, LPCTSTR  talkerDesc, unsigned  short  usOp, int  iStatus, char* timeBuf, LPCTSTR  rowIdStr, LPCTSTR  content, BOOL  bFollowingRows, BOOL  bScrollIntoView, TCHAR* txtBuf, unsigned  int  uiTxtBufCnt)
{
	CCtxQyMc* pQyMc = QY_GET_GBUF();
	CCtxQmc* pProcInfo = (CCtxQmc  *  )pQyMc->get_pProcInfo();
	return pProcInfo->do_addToRecentMsg(hDlgTalk, pDLG_TALK_var, lRowIndex, iTaskId, pMsgU,  pMsgTaskStatus,  idInfo_talker, talkerDesc, usOp, iStatus, timeBuf, rowIdStr, content, bFollowingRows,bScrollIntoView, txtBuf, uiTxtBufCnt);
}

__declspec(dllexport)  int  modifyRow(void* p0, void* pPARAM_PROC_ROW, void* pIHTMLTableRow)
{
	return -1;
}

__declspec(dllexport)  BOOL  dlgTalk_bEnableScrollBar(HWND  hDlgTalk, BOOL  bEnable)
{
	return false;
}

__declspec(dllexport)  int  get_conf_stat(HWND  hDlgTalk_mgr)
{
	return -1;
}

__declspec(dllexport)  CQyString		getNextRowIdStr(HWND  hDlgTalk)
{
	return CQyString("");
}

__declspec(dllexport)  void  dlgTalk_OnIsCmd_noSync(HWND  m_hWnd, DLG_TALK_var* pm_var, UINT  iMenuId, QY_wmBuf_command* pWmBuf)
{
	return;
}

__declspec(dllexport)  extern  "C"  int  makeDynaMenu(void* pResInfoParam, HMENU  hMenu, QY_DMITEM * pTable, PF_getMenuStatus  pf, QY_MC * pQyMc, void* p0)
{
	return -1;
}

__declspec(dllexport)  BOOL  bFillImGrpMem_confCtrl_myDb(HWND  hDlgTalkParam, void* pDbParam, void* pParam, GRP_confCtrl* pConfCtrl)
{
	return false;
}

__declspec(dllexport)  int  refreshTalkToInfo_mgr(HWND  hDlgTalk_mgr)
{
	return -1;
}


__declspec(dllexport)  int  showRemoteAssistWnd(HWND  hParent, HWND  hDlg_org, BOOL  bDlgTalk, void* pPARAM_dlgVideos, CAP_subWnds* pSubWnds)
{
	return -1;
}

__declspec(dllexport)  int  qyBrowseForFile(HWND  hwndOwner, BOOL bOpen, LPCTSTR  lpszDefExt, DWORD  dwFlags, LPCTSTR  lpszFilter, LPCTSTR  title, LPCTSTR  initialFile, CCtxQyMcTmpl* pQyMcTmpl, CQyString& fileStr)
{
	return -1;
}

__declspec(dllexport) int  viewDlgSelectAvCompressor(HWND  hParent, HWND  hCurTalk, unsigned  int  uiCapType, unsigned  int  uiSubCapType, int  iCapUsage, BOOL  b3D, unsigned  short  usConfType)
{
	return -1;
}

__declspec(dllexport)  int  delImObj(void* pDb, int  iDbType, BOOL  bClient, LPCTSTR  misServName, QY_MESSENGER_ID* pIdInfo)
{
	return -1;
}

__declspec(dllexport)  int  myOnAppAbout(HWND  hParent)
{
	return -1;
}

__declspec(dllexport)  int  viewDlgMsgInput_talk(HWND  hParent, HWND  hCurTalk, HWND* phWnd_msgInput)
{
	return -1;
}

__declspec(dllexport)  BOOL  setMsgInputPos(HWND  hWnd_msgInput, int  iX_screen, int  iY_screen, int  iW, int  iH)
{
	return false;
}

__declspec(dllexport)  int  showDlgPolicyAv(HWND  hParent, unsigned  int  uiCapType, unsigned  int  uiSubCapType, int  iCapUsage)
{
	return -1;
}

__declspec(dllexport)  int  showDlgPolicyIsClient(HWND  hParent)
{
	return -1;
}

__declspec(dllexport)  int  viewWallsBar(HWND  hWndEvent, int  iWndContentType, int  xPos_screen, int  yPos_screen, HWND  hDlgWalls, void* pDLG_wall_var, BOOL  bNoDelayToView)
{
	return -1;
}

__declspec(dllexport)  int  setWallsBarPos(HWND  hDlgWalls, void* pDLG_wall_var, HWND  hBar, int  iBarType)
{
	return -1;
}

__declspec(dllexport)  int  showDlgMsgList(HWND  hParent, LPCTSTR  misServName, QY_MESSENGER_ID* pIdInfo)
{
	return -1;
}

__declspec(dllexport)  int  showMenu_wallsBar(HINSTANCE  hInst, HWND  hParent, int  iWndContentType_hParent, void* p2)
{
	return  -1;
}

__declspec(dllexport)  void* getZoneObjs_dynBmps(HWND  hDlgWalls, int  iWndContentType)
{
	return mynull;
}

__declspec(dllexport)  void* getZoneObjsInfo_dynBmps(HWND  hDlgWalls, int  iWndContentType)
{
	return mynull;
}

__declspec(dllexport)  BOOL  bFullScreen_wnd_default(HWND  hWnd, int  iWndContentType)
{
	return false;
}

__declspec(dllexport)  int  viewVWall(HWND  hParent, LPCTSTR  misServName, int  iSubType, BOOL  bNewVirtualWall, LPCTSTR  init_qvwFile, BOOL  bNeedNotShowWnd, HWND* phWnd)
{
	return -1;
}

__declspec(dllexport)  int  testLocalAv(HWND  hParent)
{
	return -1;
}

__declspec(dllexport)  int mainWnd_OnQyTrayNotify(HWND  hMainWnd, void* pVar, WPARAM  wParam, LPARAM  lParam)
{
	return -1;
}

__declspec(dllexport)  int  showMenu_d3dWall(HINSTANCE  hInst, HWND  hParent, int  iWndContentType_hParent, void* p2)
{
	return -1;
}

__declspec(dllexport)  int  showMenu_generalWall(HINSTANCE  hInst, HWND  hParent, int  iWndContentType_hParent, void* p2)
{
	return -1;
}

#if  0
__declspec(dllexport)  int  toSelectRegion1(HWND  hWndStarter, BOOL  bCapFullScreen, BOOL  bRemoteAssist, BOOL  bDirectX, int  level, int  iParam)
{
	return -1;
}

__declspec(dllexport)  void  stopAll_avRecord()
{
	return;
}
#endif


__declspec(dllexport)  int  addToWalls(HWND  hDlgTalk, HWND  hDlgWalls, int  iWndContentType, int* piIndex_wall)
{
	return -1;
}

__declspec(dllexport)  int  test_myDb(LPCTSTR  hint)
{
	return -1;
}

__declspec(dllexport)  void  clearShiftKeys()
{
	return;
}

#if 0
__declspec(dllexport)  int  getPtzSettings(void* pCOM_PORT_cfg)
{
	return -1;
}
#endif


__declspec(dllexport)  void  exitTestGps()
{

}


#if  0
__declspec(dllexport)  int  initAvRecordMgr(HINSTANCE  g_hInst)
{
	return 0;
}

__declspec(dllexport)  void  exitAvRecordMgr()
{

}
#endif


__declspec(dllexport)  int  qisChkDb_gui_myDb()
{
	return -1;
}

__declspec(dllexport)  int  myListCtrl_GetItemText(HWND  hListCtrl, int nItem, int nSubItem, LPTSTR lpszText, int nLen)
{
	return  -1;
}


__declspec(dllexport)  int  getTaskItem(HWND  hListCtrl, int  iTaskId)
{
	return  -1;
}

DWORD WINAPI mcThreadProc_writeShm_dvt(LPVOID lpParameter)
{
	return  -1;
}
