
#ifndef  __ctxQmc_gui_h__
#define  __ctxQmc_gui_h__	//  {

//
//#include	"ctxQmcTmpl.h"
#include	"ctxQmc.h"

#include	"qyMcMainCommon.h"
#include	"qmcCfg.h"
#include	"smLoginProc.h"
#include	"qmCfg_isCli.h"
#include	"smCommProc.h"


//
class  CCtxQmc_gui : public  CCtxQmc
{
public:
	CCtxQmc_gui();
	virtual  ~CCtxQmc_gui();

	///////////////
	//typedef  struct  __mcVar_isCli_t								{
				 //MACRO_mcVar_common

				 //
	struct				{

		//
		Ctx_sm			ctxSm;


		//
	}					m_var;

	//
	char  _start;

#if  1
	int  test1;
#endif



#if  1
	int  test2;
#endif

	char  _bEnd;

	//}		 MC_VAR_isCli;


			//  2016/09/26
	virtual  int  setQmDbFuncs(int  iDbType, QM_dbFuncs* pDbFuncs);

	virtual  int  initInfrared() {
		return  -1;
	}
	virtual  int  exitInfrared() {
		return  -1;
	}


	//
	virtual int  loadCusModules(void* pQyMcParam);
	virtual int  unloadCusModules(void* pQyMcParam);
	//
	virtual int  initCusModules(void* pQyMcParam);
	virtual int  startCusModules(void* pQyMcParam);
	virtual int  stopCusModules(void* pQyMcParam);

	//	
	//
	virtual Ctx_sm* getCtxSm() {
		return  &m_var.ctxSm;
	}
	
	//		
	virtual int getSmCfgInfo(TCHAR* cfgDirName, int cfgDirNameLen);

	//
	virtual  int  initVar_post(void* p0, void* p1, void* p2);
	virtual  int  exitVar_pre(void* p0, void* p1, void* p2);
	virtual  int  exitVar_post(void* p0, void* p1, void* p2);


	//  2016/09/27		
	virtual  int  qyShowMainWndFunc(HWND  hMainWnd, void* pVar, BOOL  bShow);

	//
	virtual  int  getAuthType();




	//
	//  2016/08/14
	virtual  int  postMsg2Mgr_mc(void* pMIS_CNT, MSG_ROUTE* pRoute, unsigned  int  uiMisMsgType, unsigned  char  ucFlg, unsigned  short  usCode, time_t  tStartTime, unsigned  int  uiTranNo, unsigned  int  uiSeqNo, char* data, unsigned  int  dataLen, QY_MESSENGER_ID* pIdInfo_logicalPeer, QY_MESSENGER_ID* pIdInfo_dst, unsigned  int  uiChannelType, MIS_MSGU* pMsgBuf, BOOL  bLog);
	virtual  int  postMsgTask2Mgr_mc(void* pMIS_CNT, unsigned  int  uiMisMsgType, unsigned  char  ucFlg, unsigned  short  usCode, time_t  tStartTime, unsigned  int  uiTranNo, unsigned  int  uiSeqNo, int  iTaskId, unsigned  int  uiTaskType, char* data, unsigned  int  dataLen, QY_MESSENGER_ID* pIdInfo_logicalPeer, QY_MESSENGER_ID* pIdInfo_taskSender, QY_MESSENGER_ID* pIdInfo_taskReceiver, QY_MESSENGER_ID* pIdInfo_dst, unsigned  int  uiChannelType, MIS_MSGU* pMsgBuf, BOOL  bLog);
	virtual  int  postImMsg2Log_isClient(MIS_MSGU* pMsg, int  lenInBytes_msg);
	//
	virtual  int  recoverMessenger(QM_dbFuncs* pDbFuncs, void* pDb, int  iDbType, QY_DMITEM* pFieldIdTable, QY_MESSENGER_INFO* pObj, QY_MESSENGER_REGINFO* pRegInfo, time_t  tLastModifiedTime, BOOL  bLog, GENERIC_Q* pLogQ);
	virtual  int  recoverImObjRules(QM_dbFuncs* pDbFuncs, void* pDb, int  iDbType, LPCTSTR  misServName, QY_MESSENGER_ID* pIdInfo, REFRESH_imObjRules_req* pReq, time_t  tLastModifiedTime);
	virtual  int  recoverImGrp(QM_dbFuncs* pDbFuncs, void* pDb, int  iDbType, QY_DMITEM* pFieldIdTable, unsigned  int  uiObjType, IM_GRP_INFO* pGrpInfo, time_t  tLastModifiedTime, BOOL  bNoGrpName);
	virtual  int  recoverImGrpMem(QM_dbFuncs* pDbFuncs, void* pDb, int  iDbType, IM_GRP_MEM* pGrpMem, time_t  tLastModifiedTime);

	//
	virtual  FUNCS_for_isCliHelp* FUNCS_for_isCliHelp_new();
	virtual  void  FUNCS_for_isCliHelp_free(void** ppFuncs);


	//
	virtual  int  tryToTalkToMessenger_any(HWND  hParent,unsigned  __int64  ui64Id, int  iTalkSubtype,  BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd);
	virtual  int  talkToMessenger(unsigned  __int64  ui64Id, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd);
	virtual  int  doApplyForPlayer(HWND  hMainWnd, MIS_MSGU* pMsg);

	//
	//  2016/09/09
	virtual  int  removeMosaicFromD3dWall(int  iIndex_sharedObj);
	virtual  int  getVal_bExists_mosaic(int  iIndex_sharedObj, BOOL* pbExists);

	//
	virtual  int  stopLocalAudioRecorder(int  index_sharedObj, int  nTries);

	//
	virtual int  talkToMessenger(void* pQyMcParam, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkUsage, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd);
	virtual void* tmp_getDlgTalkVar(HWND  hDlgTalk);
	virtual int  getTalkerShadow(HWND  hParent, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkerSubType, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd);

	virtual  int  do_addToRecentMsg(HWND  hDlgTalk, void* pDLG_TALK_var, long  lRowIndex, int  iTaskId, MIS_MSGU  *  pMsgU,  MIS_MSG_taskStatus  *  pMsgTaskStatus,  QY_MESSENGER_ID idInfo_talker, LPCTSTR  talkerDesc, unsigned  short  usOp, int  iStatus, char* timeBuf, LPCTSTR  rowIdStr, LPCTSTR  content, BOOL  bFollowingRows, BOOL  bScrollIntoView, TCHAR* txtBuf, unsigned  int  uiTxtBufCnt)
	{
		return -1;
	} 

	virtual  int  do_talk_OnTimer(HWND  hDlgTalk, void* pDLG_TALK_var);

	//
	virtual int do_talk_shareDevice(HWND  hDlgTalk, void* pDLG_TALK_var, bool  bEnable, bool  bSaveSpeakState)
	{
		return  -1;

	}

	//
	virtual  int  do_talk_afterInit(HWND  hDlgTalk) {
		int  iWndContentType = CONST_qyWndContentType_talker;
		return old_doSth_afterInitDlgTalk(hDlgTalk, iWndContentType);
	}

	//
	virtual  int  do_talk_refreshLayout(HWND  hDlgTalk) {
		return  -1;
	}

	//
	virtual bool myDestroyWindow(HWND  hWnd);

	virtual int  getDirAndFinalName(LPCTSTR  svFileName, TCHAR* dirName, unsigned  int  size, TCHAR* finalName, unsigned  int  finalNameSize);


	virtual int do_test(HWND  hWnd,int iWndContentType) { return -1; }

	virtual bool bAppQt() { return false; }

	virtual int do_initDb() {
		return 0;
	}

	virtual  int  do_logImMsg_isCli(void* pDb, int  iDbType, void  *  pDBManger,  IM_MSG_RCD* pRcd) {
		return  -1;
	}

	virtual int  viewDlgSelectAvCompressor(HWND  hParent, QY_MESSENGER_ID idInfo, unsigned  int  uiCapType, unsigned  int  uiSubCapType, int  iCapUsage, BOOL  b3D, unsigned  short  usConfType);

	virtual void gui_notify_clearTask(int  iTaskId) {
		return;
	}
	virtual void gui_notify_clear() {
		return;
	}

	virtual void* DBManager_new() {
		return mynull;
	}
	virtual void DBManager_free(void** ppDBManager) {
		return;
	}
	//
	virtual int initDBManager(void* pDBManager) {
		return -1;
	}

	//
	virtual int  do_dlgTalk_procTask_transferAvInfo(HWND  hTalk) {
		return  -1;
	}


	//
	virtual int AEC_layout_chk(AEC_layout* pLayout)
	{
		return ::AEC_layout_chk(pLayout);
	}

	virtual int  do_mainWnd_OnTimer(HWND  hMainWnd, void* pVar, UINT  nIDEvent);


	//
	virtual  int  displayRecentFriends(MIS_MSG_displayRecentFriends_qmc* pMsg);

	//
	virtual  int  confKeyChanged(HWND  hDlgTalk)
	{
		return -1;
	}

	//
	virtual int do_requestToSpeak(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_from) 		//  自己申请发言
	{
		return  -1;
	}

	virtual int do_stopSpeaking(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_from) 			//  自己停止发言
	{
		return  -1;
	}

	//
	virtual int do_permitToSpeak(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_from)
	{
		return  -1;
	}
	virtual int do_prohibitSpeaking(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_from)
	{
		return  -1;
	}
	//
	virtual int do_pleaseSpeak(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_from);			//  主持人邀请发言
	virtual int do_pleaseStopSpeaking(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_from);	//  主持人请停止发言



	//
	virtual int do_dlgTalk_proc_recvd_confCtrlState(HWND  hDlgTalk)
	{
		return  -1;
	}
		
	//
	virtual  bool  bNeedUsrLogin_sm() {
		return  false;
	}

	virtual int  showDlgSelectAvDev(HWND  hParent, void* pCapStuff, int  iMenuId_selected, BOOL* pbUnresizable);



	//
	virtual int sxrz_yq(QIS_ca_req* p);


	
	



	//
	virtual int reportToHg_meetingOn(unsigned  __int64 ui64MeetingId_hg, int  iMeetingType, unsigned  __int64  ui64Id_grp,  bool  bOn)
	{
		return  ::reportToHg_meetingOn(ui64MeetingId_hg, iMeetingType, ui64Id_grp,  bOn);
	}

	virtual int reportToHg_saveAv(unsigned  __int64  uiMeetingId_hg, char* video_url, char* resource_url)
	{
		return  -1;
	}

	virtual int chkDualSystemHotBackup();

	virtual unsigned  char  getMbFlg(int  iMeetingLevel)
	{
		return  0;
	}


	//
	virtual int do_afterLogonOk();

	//
	virtual int  tmpHandler_showMsg_task(void* hDlgTalkParam, void* pDLG_TALK_var, void* p1, void* pMsgParam);


	//
	virtual BOOL  bSupported_emergencyCommand() { return  true; }
	
	
	//
	virtual   int  doCmd_startAvCall(HWND  hParent, HWND  hCurTalk, int  level, BOOL  b3D, unsigned  char  ucbAvConsole, PARAM_startAvCall* pParam);



	//////////////////////

};

//
int  newVar_isCli_gui(  void  *  p0,  void  *  p1,  void  *  p2  );
int  freeVar_isCli_gui(  void  *  p0,  void  *  p1,  void  *  p2  );
 
//
 //
__declspec(dllexport)  int  talkToMessenger_mfc(void* pQyMcParam, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkUsage, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd);
__declspec(dllexport) void* tmp_getDlgTalkVar_mfc(HWND  hDlgTalk);
__declspec(dllexport)  int  getTalkerShadow_mfc(HWND  hParent, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkerSubType, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd);




#endif  //  }


