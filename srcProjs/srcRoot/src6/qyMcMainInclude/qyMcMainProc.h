

#ifndef __QYMCMAINPROC_H__
#define __QYMCMAINPROC_H__	/* { */



#ifdef  __DEBUG__		//  ¿ÕÏÐ³¬Ê±²ÎÊý
		#define		CONST_qyMcMainIdleTimeout						(  10  *  60  *  1000  )		//  2005/10/01, ½çÃæ¿ÕÏÐ³¬Ê±Öµ£¬ÒÔºÁÃëÎªµ¥Î»£¬±£ÃÜ¾Ö²âÆÀ½¨ÒéÓÃ3·ÖÖÓ£¬Õý³£²úÆ·½¨ÒéÎª30·ÖÖÓ
#else
		#define		CONST_qyMcMainIdleTimeout						(  30  *  60  *  1000  )		//  2005/10/01, ½çÃæ¿ÕÏÐ³¬Ê±Öµ£¬ÒÔºÁÃëÎªµ¥Î»£¬±£ÃÜ¾Ö²âÆÀ½¨ÒéÓÃ3·ÖÖÓ£¬Õý³£²úÆ·½¨ÒéÎª30·ÖÖÓ
#endif




typedef  struct  __messengerStatusInfo_t							{
				 TCHAR												misServName[CONST_maxMisServNameLen  +  1];

				 QY_MESSENGER_ID									idInfo;
				 QY_MESSENGER_INFO									messengerInfo;
				 QY_MESSENGER_phoneInfo								phoneInfo;
}		 MESSENGER_STATUS_INFO;


typedef  struct  __objStausInfo_t									{
				int													iObjType;
				QY_OBJ_DB								*			pObjDb;
				union												{
                    PC_STATUS_INFO									pc;
					struct											{
						int											ucbLoaded;
					}												procedObj;
					//
					MESSENGER_STATUS_INFO							messengerStatus;
					//
					struct											{
						IM_GRP_MEM									grpMem;
					}												imGrpMem;

				}													u;
}		 OBJ_STATUS_INFO;

//
 int  getObjStatusInfo(  void  *  p0,  QY_OBJ_DB  *  pObjDb,  OBJ_STATUS_INFO  *  pU  );



//
int  getDynCfg_isClient(  QY_MC  *  pQyMc,  QNM_CNT_CFG  *  pDynCfg  );

BOOL bChkQyMcEnv(  QY_MC  *  pQyMc  );
BOOL bChkQyMcEnv_db(  QY_MC  *  pQyMc  );

int  initQyMcSys(  QY_MC  *  pQyMc  );
__declspec(  dllexport  )  BOOL  bClearQnmTmpTab(  QY_MC  *  pQyMc  );



void	exitAllDaemonThreads(  QY_MC  * pQM  );



int  initQyMcMainHook(  );
void  exitQyMcMainHook(  );
unsigned  int  getLastActiveTickCnt(  );

int  setServiceGuiCfg(  QY_SERVICEGUI_CFG  *  pServiceClientCfg,  QY_MC  *  pQyMc  );
QY_SERVICEGUI_INFO  *  getServiceGuiInfo(  QY_MC  *  pQyMc,  int  iServiceId  );


GENERIC_Q  *  getDisplayQ(  QY_MC  *  pQyMc,  void  *  p1,  void  *  p2  );


unsigned  int  getVarSize_is(  void  *  pQyMc  );
//  2015/01/20
#if  0  //  2016/08/12
int  newVar_isCli(  void  *  p0,  void  *  p1,  void  *  p2  );
int  freeVar_isCli(  void  *  p0,  void  *  p1,  void  *  p2  );
#endif
//
int  initVar_isGui(  void  *  p0,  void  *  p1,  void  *  p2  );
int  init_afterLogon_isGui(  void  *  p0,  void  *  p1,  void  *  p2  );
int  exitVar_isGui(  void  *  p0,  void  *  p1,  void  *  p2  );
int  closeOtherWnds_isCli(  BOOL  *  pbOtherWndExists  );

//  int  initPolicyAvParams(  );	//  要在登陆后立即运行此函数. 2011/10/22

//
int  initVar_isGui_mgr(  void  *  p0,  void  *  p1,  void  *  p2  );
int  exitVar_isGui_mgr(  void  *  p0,  void  *  p1,  void  *  p2  );
int  closeOtherWnds_isMgr(  BOOL  *  pbOtherWndExists  );

//  2012/05/16
__declspec(  dllexport  )  void  exitTestGps(  );
__declspec(  dllexport  )  int  initTestGps(  );
 __declspec(  dllexport  )  int  myTestData_gps(  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  nCtrls_test,  void  *  pmyGPS_POSITION  );


//
//BOOL  bGetLongProperty_open(  void  *  p0,  void  *  propertyIdParam,  void  *  plVal  );
//
//int  postHint2Mgr_mc_open(  void  *  pQyVDevParam,  WCHAR  *  who,  time_t  tStartTime,  unsigned  int  uiTranNo,  LPCTSTR  str  );
//



extern "C" DWORD WINAPI mcThreadProc( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_isCli( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_isMgr( LPVOID lpParameter );


//
BOOL  bQnmCmdEnable(  int  cmdId  );


//
#include	"qmShellPublic.h"


//
BOOL	bQyMcLogon(  QY_MC  * pQyMc,  PF_showDlgMcLogon  pf_showDlgLogon,  PARAM_showDlgMcLogon  *  pParam  );
void	old_qyMcLogoff(  QY_MC  * pQyMc  );


void	showMcSel(  QY_MC_SEL  *  pSelParam  );
char  * qyViewTypeStr(  int  iViewType  );



BOOL	bQySetTmpDisplayCfg( QY_MC_DISPLAYCFG *pStaticCfgParam, QY_MC_DISPLAYCFG *pTmpCfgParam,  QY_COLUMNINFO **	ppColumns, int *pnColumns  );

//
__declspec(  dllexport  )  void  qyMcRefreshAll(  );

//
 BOOL  bRefreshImObjView_isCli(  QY_OBJ_DB  *  pObjDb  );


 //
BOOL	bQyMcNewMcView(  QY_MC_SEL  *  pSel  );
BOOL	bQyMcNewWebView(  QY_MC_SEL  *  pSel  );
BOOL	bQyMcNewIe(  QY_MC_SEL  *  pSel  );
BOOL	bQyMcNewQueryView(  QY_MC_SEL  *  pSel  );
BOOL	bQyMcNewTreeListView(  QY_MC_SEL  *  pSel  );
BOOL	bQyMcNewTreeView(  QY_MC_SEL  *  pSel  );
int  enumAllDocs(  PF_commonHandler  pf,  COMMON_PARAM  *  p0,  BOOL  *  pbStop  );

#ifdef  __isCli__
		__declspec(  dllexport  )  int  myOnAppAbout(  HWND  hParent  );
#else
		int  myOnAppAbout(  HWND  hParent  );
#endif
int  displayNotification_talk_ts(  HWND  hDlg,  void  *  pGuiDataParam,  LPCTSTR  hint  );


#ifndef  __WINCE__
//  CQyString getMcQueryStr(  QY_MC_QUERY  *  pQuery  );
CQyString  getMcQueryCntStr(  QY_MC_QUERY  *  pQuery  );
CQyString  getMcQueryCurnItemStr(  QY_MC_QUERY  *  pQuery  );
#endif
extern  "C"  char * qyStatusStr(  unsigned  char  ucStatus,  char  *  buf,  int  size  );



int  getDesOfMac(  QY_OBJ_DB  *  pObj,  char  *  mac,  TCHAR  *  devDescr,  unsigned  int  size,  unsigned  char  *  pucbDesManually  );


//	extern  QY_COLUMNINFO  CONST_qnmCfgIpScanColumns[];
//	extern  QY_COLUMNINFO	CONST_qnmCfgSwitchPolicyGrpsColumns[];
//	extern  QY_COLUMNINFO  CONST_qnmMgrSwitchPolicyColumns[];




//  BOOL  bQnmImportRegInfo(  QY_IMEXPORTINFO  *  pImportInfo  );
BOOL  bQnmImportBhbCfg(  QY_IMEXPORTINFO  *  pImportInfo  );
BOOL  bQnmImportBakData(  int  iServiceId,  int  iAppType,  QY_IMEXPORTINFO  *  pImportInfo  );
BOOL  bQnmImportDjData(  QY_IMEXPORTINFO  *  pImExport  );

BOOL  bQnmExportCurQuery(  QY_IMEXPORTINFO  *  pExportInfo  );
//  BOOL  bQnmExportRegInfo(  QY_IMEXPORTINFO  *  pExportInfo  );
BOOL  bQnmExportBhbCfg(  int  iServicdId,  QY_IMEXPORTINFO  *  pExportInfo  );
BOOL  bQnmExportBakData(  int  iServiceId,  int  iAppType,  QY_IMEXPORTINFO  *  pExportInfo  );
BOOL  bQnmExportDjTools(  QY_IMEXPORTINFO  *  pExportInfo  );



//
__declspec(  dllexport  )  int  showTaskStatus(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_taskSender,  QY_MESSENGER_ID  *  pIdInfo_mem,  BOOL  bImGrpMem,  unsigned  int  uiContentType,  int  iTaskId,  int  iStatus,  unsigned  char  ucPercent,  unsigned  __int64  ui64Len_recvd,  LPCTSTR  fileName,  LPCTSTR  fullFilePath  );
__declspec(  dllexport  )  int  showTaskStatus(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_taskSender,  QY_MESSENGER_ID  *  pIdInfo_mem,  BOOL  bImGrpMem,  unsigned  short  cmdCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  int  iTaskId,  int  iStatus  );
//
__declspec(  dllexport  )  int  showNotification(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  LPCTSTR  hint  );
__declspec(  dllexport  )  int  showNotification_open(  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  LPCTSTR  hint  );
//int  showInfo_open0(  void  *  p0,  LPCTSTR  tWhere,  LPCTSTR  hint  );

//  2015/02/16
__declspec(  dllexport  )  int  sendNotification(  LPCTSTR  str,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_dst  );
int  showMsg_d3d(  HWND   hDlg,  QY_MESSENGER_ID  *  pIdInfo_from,  LPCTSTR  senderDesc,  LPCTSTR  str  );
int  clearShownMsg_d3d(  HWND  hDlg  );
int  showNotification_d3d(  HWND  hDlg,  LPCTSTR  str  );





//  2015/02/07
void  qyExitProcessEx(  LPCTSTR  hint,  BOOL  bNoGui  );


//
int  tmpPostMessage_cmd(  HWND  hParent_expected,  int  id,  HWND  hTalker  );




#endif /* } */




