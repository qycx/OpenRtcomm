
#ifndef  __ctxQmc_gui_h__
#define  __ctxQmc_gui_h__	//  {

//
//#include	"ctxQmcTmpl.h"
#include	"ctxQmc.h"

#include	"qyMcMainCommon.h"
#include	"qmcCfg.h" 


//
int  viewDlg2ndScreen_qt();
int  closeDlg2ndScreen_qt();



//
class  CCtxQmc_qt: public  CCtxQmc
{
public:
	CCtxQmc_qt(  );
	virtual  ~CCtxQmc_qt(  );

	///////////////
	//typedef  struct  __mcVar_isCli_t								{
				 //MACRO_mcVar_common

				 //
				 struct				{
					 void	*		pDBManager;
					 //
					 TCHAR			installDir_qt[256];
					 //
					 HWND			hTalk_video;
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
		virtual  int  setQmDbFuncs(  int  iDbType,  QM_dbFuncs  *  pDbFuncs  );

		virtual  int  initInfrared() {
			return  -1;
		}
		virtual  int  exitInfrared() {
			return  -1;
		}

		
		//  2016/09/27		
		virtual  int  qyShowMainWndFunc(  HWND  hMainWnd,  void  *  pVar,  BOOL  bShow  );


		//
		//  2016/08/14
		virtual  int  postMsg2Mgr_mc(  void  *  pMIS_CNT,  MSG_ROUTE  *  pRoute,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  char  *  data,  unsigned  int  dataLen,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  uiChannelType,  MIS_MSGU  *  pMsgBuf,  BOOL  bLog  );
		virtual  int  postMsgTask2Mgr_mc(  void  *  pMIS_CNT,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  int  iTaskId,  unsigned  int  uiTaskType,  char  *  data,  unsigned  int  dataLen,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_taskSender,  QY_MESSENGER_ID  *  pIdInfo_taskReceiver,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  uiChannelType,  MIS_MSGU  *  pMsgBuf,  BOOL  bLog  );
		virtual  int  postImMsg2Log_isClient(  MIS_MSGU  *  pMsg,  int  lenInBytes_msg  ); 
		//
		virtual  int  recoverMessenger(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QY_MESSENGER_INFO  *  pObj,  QY_MESSENGER_REGINFO  *  pRegInfo,  time_t  tLastModifiedTime,  BOOL  bLog,  GENERIC_Q  *  pLogQ  );
		virtual  int  recoverImObjRules(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRules_req	*	pReq,  time_t  tLastModifiedTime  );
		virtual  int  recoverImGrp(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime,  BOOL  bNoGrpName  );
		virtual  int  recoverImGrpMem(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime  );
		
		//
		virtual  FUNCS_for_isCliHelp  *  FUNCS_for_isCliHelp_new(  );
		virtual  void  FUNCS_for_isCliHelp_free(  void  **  ppFuncs  );

					
		//
		virtual  int  tryToTalkToMessenger_any( HWND hParent, unsigned  __int64  ui64Id,  int  iTalkSubtype,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phWnd  );
		virtual  int  talkToMessenger(  unsigned  __int64  ui64Id,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phWnd  );
		virtual  int  doApplyForPlayer(  HWND  hMainWnd,  MIS_MSGU  *  pMsg  );

		//
		//  2016/09/09
		virtual  int  removeMosaicFromD3dWall(  int  iIndex_sharedObj  );
		virtual  int  getVal_bExists_mosaic(  int  iIndex_sharedObj,  BOOL  *  pbExists  );

		//
		virtual  int  stopLocalAudioRecorder(  int  index_sharedObj,  int  nTries  );

		//
		virtual int  talkToMessenger(void* pQyMcParam, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkUsage, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd);
		virtual void* tmp_getDlgTalkVar(HWND  hDlgTalk);
		virtual int  getTalkerShadow(HWND  hParent, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkerSubType, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd);

		virtual  int  do_talk_afterInit(HWND  hDlgTalk);
		virtual  int  do_talk_refreshLayout(HWND  hDlgTalk);
		virtual  int  do_addToRecentMsg(HWND  hDlgTalk, void* pDLG_TALK_var, long  lRowIndex, int  iTaskId, MIS_MSGU* pMsgU, MIS_MSG_taskStatus  *  pMsgTaskStatus,  QY_MESSENGER_ID idInfo_talker, LPCTSTR  talkerDesc, unsigned  short  usOp, int  iStatus, char* timeBuf, LPCTSTR  rowIdStr, LPCTSTR  content, BOOL  bFollowingRows, BOOL  bScrollIntoView, TCHAR* txtBuf, unsigned  int  uiTxtBufCnt);
		virtual  int  do_talk_OnTimer(HWND  hDlgTalk,void *pDLG_TALK_var);

		//
		virtual int do_talk_shareDevice(HWND  hDlgTalk, void* pDLG_TALK_var, bool  bEnable, bool  bSaveSpeakState)
		{
			return  -1;
		}


		//
		virtual bool myDestroyWindow(HWND  hWnd);

		virtual int  getDirAndFinalName(LPCTSTR  svFileName, TCHAR* dirName, unsigned  int  size, TCHAR* finalName, unsigned  int  finalNameSize);


		//
		virtual int do_test(HWND  hWnd,  int  iWndContentType);

		virtual bool  bAppQt() { return true; }


		virtual  int  do_logImMsg_isCli(void* pDb, int  iDbType, void  * pDBManager,  IM_MSG_RCD* pRcd);

		virtual  int  viewDlgSelectAvCompressor(HWND  hParent, QY_MESSENGER_ID idInfo, unsigned  int  uiCapType, unsigned  int  uiSubCapType, int  iCapUsage, BOOL  b3D, unsigned  short  usConfType);
		virtual void gui_notify_clearTask(int  iTaskId);
		virtual void gui_notify_clear();

		virtual void* DBManager_new();
		virtual void DBManager_free(void** ppDBManager);
		//
		virtual int initDBManager(void *pDBManager);

		//
		virtual int  do_dlgTalk_procTask_transferAvInfo(HWND  hTalk);


		//
		virtual int AEC_layout_chk(AEC_layout* pLayout)
		{
			return ::AEC_layout_chk(pLayout);
		}

		virtual int  do_mainWnd_OnTimer(HWND  hMainWnd, void* pVar, UINT  nIDEvent);

		//
		virtual  int  displayRecentFriends(MIS_MSG_displayRecentFriends_qmc* pMsg);
				
		//
		virtual  int  confKeyChanged(HWND  hDlgTalk);

		virtual int popup_permitToSpeak(HWND  hDlgTalk);

		virtual int do_dlgTalk_proc_recvd_confCtrlState(HWND  hDlgTalk);

		//
		virtual  bool  bNeedUsrLogin_sm() {
			return false;
		}

		virtual int sxrz_yq(QIS_ca_req* p)  	//  双向认证，客户端验签
		{
			return  -1;
		}


		//

		virtual int  closeDlg2ndScreen()
		{
			int iRet = 0;
			iRet =  ::closeDlg2ndScreen_qt();
			return  iRet;
		}

		//
		virtual int getSmCfgInfo(TCHAR* cfgDirName, int cfgDirNameLen)
		{
			return  -1;
		}

		//
		virtual int reportToHg_meetingOn(unsigned  __int64 ui64MeetingId_hg, int  iMeetingType, unsigned  __int64  ui64Id_grp,  bool  bOn)
		{
			//return  ::reportToHg_meetingOn(ui64MeetingId_hg, iMeetingType, bOn);
			return  -1;
		}

		virtual int reportToHg_saveAv(unsigned  __int64  uiMeetingId_hg, char* video_url, char* resource_url)
		{
			return  -1;
		}

		virtual int chkDualSystemHotBackup()
		{
			return  -1;
		}


		virtual unsigned  char  getMbFlg(int  iMeetingLevel)
		{
			return  0;
		}
	
		//////////////////////
		virtual int do_afterLogonOk()
		{
			return  0;
		}

		//
		virtual int  tmpHandler_showMsg_task(void* hDlgTalkParam, void* pDLG_TALK_var, void* p1, void* pMsgParam);




};

#define COUNT_chat_count		15  //第一次加载聊天记录条数
#define COUNT_chat_more_count	30 //加载聊天更多的条数

#define COUNT_display_height_value    801; //分辨率 高
#define COUNT_display_width_value     900;  //分辨率  宽

//
int  newVar_isCli_gui(  void  *  p0,  void  *  p1,  void  *  p2  );
int  freeVar_isCli_gui(  void  *  p0,  void  *  p1,  void  *  p2  );

//
QString  getInstallDir_qt();


 //
__declspec(dllexport)  int  talkToMessenger_qt(void* pQyMcParam, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkUsage, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd);
__declspec(dllexport) void* tmp_getDlgTalkVar_qt(HWND  hDlgTalk);
__declspec(dllexport) int  getTalkerShadow_qt(HWND  hParent, MSGR_ADDR* pAddr, GENERIC_Q* pTmpGrpMemQ, int  iTalkerSubType, BOOL  bNeedNotShowWnd, BOOL  bActivateWnd, HWND* phWnd);

//
void* getObjAddr(HWND  hWnd);

//
int viewDlgAvAccept();
int  closeDlgAvAccept();

//
int viewInviteHint(HWND  hDlgTalk);
//
int  getAvCallerInfo(QY_MESSENGER_ID* pidInfo_logicalPeer, QY_MESSENGER_ID* pidInfo_from);

int acceptTaskAv(int  iTaskId);

//
int doAvRecover(int iTaskId);

//
int do_cancelTask1(int iTaskId, bool bAutoCancel, LPCTSTR hint);

//
int gui_notify_chk();
void gui_notify_clear();
void gui_notify_clearTask(int  iTaskId);

//
int  talk_doAv(HWND  hParent, QY_MESSENGER_ID idInfo,bool bStartConf);


//
int doMcClientLogonOK(void* pQmcLogin, char* m_server, LPTSTR m_name, LPTSTR m_passwd);




#endif  //  }


