

#ifndef  __dlgShareDynBmpsProc_h__
#define  __dlgShareDynBmpsProc_h__	//  {

#include	"qySyncCommProc.h"
#include	"gpsCommProc.h"
#include	"remoteStorageCfg.h"
#include	"qmcShareDynBmp.h"
#include	"syncMtCntDefs.h"
#include	"qyTimestamp.h"
#include	"qisOnvifCommProc_open.h"
#include	"ctxQmc.h"

//
//
#define		CONST_str_rule		_T(  "rule"  )
#define		CONST_str_ipCam		_T(  "ipCam"  )



//
typedef  struct  __shareGps_t				{

				 BOOL						bShare;

				 struct						{
					 #if 0

						BOOL					bUsing;
					//
					#endif

					//				 
					int						iIndex_sharedObj;
					int						iTaskId;
					//
					DWORD					dwTickCnt_start;
					int						portNo;

					//
					myGPS_POSITION			gpsPos;
					DWORD					dwTickCnt_modified_gpsPos;
				 }							var;

}		 SHARE_gps;								

	
//
#define		MIN_usIndex_obj_rtspUrl					1
#define		MAX_usIndex_obj_rtspUrl					20


//
typedef  struct								{
				MIS_MSGU			*		pMsg;
				DWORD						dwTickCnt;							//  dwTickCnt为保存的时刻，如果此包保存时间过长，则清除掉
				struct						{
					unsigned  int			uiTranNo_storeRecvdReq;				//  用来标识recvdReq
					//
					unsigned  int			uiContentType;
					//
					#if  0
						unsigned  int			uiObjType;
						unsigned  short			usIndex_obj;
					#endif
					//  2016/07/24
					RES_obj_simple					resObj;

					//
					unsigned  char			ucbSaveVideo_reply;			//  2014/09/07
					//
					//  2014/09/04
					unsigned  char			ucbRetrieveOne;

					//  2017/06/11
					unsigned  char			ucbAvConsole;				//  2017/06/11

				}							info;
	
}	DLG_shareDynBmp_recvdReq;







//  2016/076/26
#define		CONST_ipDevType_null											0
#define		CONST_ipDevType_rtspUrl											1
#define		CONST_ipDevType_ipCam											2




//  2016/06/27
typedef  struct  __shareDynBmps_onvifRulesInfo_t							{
				 unsigned  short											usCnt;
				 Onvif_rule													mems[20];
				 //
				 QY_timestamp												ts_rulesInfo;
}		 ShareDynBmps_onvif_rulesInfo;


//
typedef  struct  __shareDynBmps_ipDevsInfo_t								{
				 IP_dev														mems[20];		
				 //
				 QY_timestamp												ts_ipDevsInfo;
}		 ShareDynBmps_ipDevsInfo;


//
typedef  struct																{					 
					 //
					 ShareDynBmps_onvif_rulesInfo							rulesInfo;
				
					 //				
					 //  2016/06/25. 从配置的策略里，扫描得到的结果进入ipDevs. 把原来从urls调入shares[].mems. 改为从ipDevs调入.
					 ShareDynBmps_ipDevsInfo								ipDevsInfo;									 
					 //				
					 SYNC_mt_cnt											syncMtCnt_ipDevsInfo;	
}			ShareDynBmpsThread_onvif;


//
//
//  2016/03/15
//  2014/08/04
typedef  struct  __sharedDynBmpsThreadProcInfo_t							{
				 MACRO_qyQThreadProcInfo_common

				 //
				 HWND														hDlgShareDynBmps;
				 void												*		pDlgVarParam;

				 //  2016/07/01
				 unsigned  int												tn_onvifCliPipe;
				 HANDLE														hProcess_onvifCli;

				 //
				 struct														{
					 //
					 BOOL													bTaskExists;
					 //
					 Onvif_rule												rule_beingProcessed;
					 //
					 unsigned  int											uiTranNo_task;
					 //
					 DWORD													dwTickCnt_start;

				 }															taskInfo;				 
				 //
				 struct														{
					 BOOL													bScanExists;
					 //
					 int													last_index_rule;
				 }															scanCtrl;


				 //
				 ShareDynBmpsThread_onvif									onvif;


				 //  2015/05/19
				 //  2014/09/07
				 struct														{
					 long													lTranNo_doOnvifRule;
					 //
				 }															status;

}		 ShareDynBmps_threadProcInfo;




//
typedef  struct  __dlgShareDynBmps_onvif_t									{

				 //
				 ShareDynBmps_onvif_rulesInfo								rulesInfo;
				 //
				 SYNC_mt_cnt												syncMtCnt_cur_rulesInfo;

				 //
				 //  2016/06/25. 从配置的策略里，扫描得到的结果进入ipDevs. 把原来从urls调入shares[].mems. 改为从ipDevs调入.
				 ShareDynBmps_ipDevsInfo									ipDevsInfo;
				
				 //
				 struct														{
					 BOOL													bIpCam;
					 unsigned  short										usIndex_obj_sel;
					 unsigned  short										usHelp_subIndex;
				 }															sel;
				
				 //		
				 struct														{
					BOOL													bSelfTest;
					DWORD													dwTickCnt_startSelfTest;
					//
					unsigned  short											usIndex_obj_selfTest;	//  2014/06/06
					unsigned  short											usHelp_subIndex_selfTest;
					//
					BOOL													bNeedChkRtsp;
				 }															selfTest;

				 //
				 BOOL														bNeedRefreshed;
				 DWORD														dwLastTickCnt_refreshed;
	
}		 DlgShareDynBmps_onvif;	



//
typedef  struct																{
			//  
			HWND															m_hParent;
			int																m_nID;
			BOOL															bInfoSet;
			BOOL															bCreated;					//  Õâ¸ö±êÖ¾Î»ÓÃÀ´±íÃ÷ÊÇ·ñCreate(  )³É¹¦ÁË¡£³É¹¦ÁË£¬Ôò½«×ÊÔ´µÄÊÍ·ÅÁô¸øÁËdlg×Ô¼º(ÔÚPostNcDestroy(  )ÖÐdelete)
			BOOL															bInited;					//  ±íÃ÷htmlEditºÍ¶Ô»°¶¼³õÊ¼»¯ÍêÁË.

			//
			struct															{
				int															iIDC_BUTTON_gps;
				int															iIDC_STATIC_gpsStatus;
				int															iIDC_STATIC_pic0;
				//
				int															iIDC_BUTTON_hide;
				int															iIDCANCAL;
				int															iIDC_BUTTON_add;
				int															iIDC_BUTTON_procRtsp;
				int															iIDC_BUTTON_del;
				int															iIDC_BUTTON_selfTest;
				int															iIDC_BUTTON_ptz;
				int															iIDC_BUTTON_remoteStorageSettings;
				int															iIDC_CHECK_autoPopupAndHideOnStartup;
				//
				int															iIDC_BUTTON_playLocalAudio;

			}																guiData;

			//
			MIS_CNT											*				pMisCnt;
			
			BOOL															bUseDirectX;
			unsigned  char													ucbAutoClip;		//  2014/04/06

			int																iW_pic,  iH_pic;

			//int																idc;
			HWND                                                            hWndIDC;
			HDC																hDc;
			CAP_IMAGES														images;

			//
			void											*				pCapStuff1;

			SHARE_dynBmps													shares[5];		//  0 for screen, 1 for webcam, 2 for rtsp，3 for avStream, 4 for ic

			//
			void											*				pComPort_gps;

			SHARE_gps														share_gps;

			//
			unsigned  int													uiTimerId;
			int																nElapseInMs;
			int																nCtrls;

			//
			unsigned  int													uiTimerId_test;
			int																nElapseInMs_test;
			int																nCtrls_test;

			//
			time_t															tLastModifiedTime;					
			time_t															tLastModifiedTime_ok;			

			MIS_MSGU										*				pMsgBuf_doWnd_guiMsgArrive;			//  2009/12/08


			//
			DLG_shareDynBmp_recvdReq										recvdReqs[10];						//  2011/10/31. 将收到的获取共享请求都存在这里，然后向服务器发送验证请求，如果允许，则发送reply请求，否则就忽略掉
																		

			//  2011/10/15. 在会议自动响应时，自动触发，并设置此标志, 此窗口应自动置前。在启动摄像机共享后，此标志被复位
			//BOOL															bNeed_shareWebcamInConference;

			//  2012/05/08
			DLG_syncFlgs													syncFlgs;


			//  2014/04/30
			HWND															hCtrl_onvifList;
			//
			DlgShareDynBmps_onvif											onvif;

			//  2014/09/11
			struct															{
				BOOL														bNeedProcess;
			}																internalProcess;


			//  2016/06/14
			ShareDynBmps_threadProcInfo										shareDynBmpsThreadInfo;

			//  2014/08/04
			struct															{
				 //  
				 REMOTE_storage_cfg											cfg;

			}																saveVideo;

	}																		DLG_shareDynBmps_var;


//
//
__declspec(  dllexport  ) BOOL  bShared(  SHARE_dyn_bmp  *  pMem  );
__declspec(  dllexport  ) int  shareDynBmp_clear(  SHARE_dyn_bmp  *  pDynBmpMem  );

//  SHARE_dynBmps	*	dlgShareDynBmps_getShareDynBmpsBySth(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  uiObjType  );
__declspec(  dllexport  )  void  *	 dlgShareDynBmps_getShareDynBmpsBySth(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  uiObjType  );


//  2014/09/09
class  CHelp_shareDynBmp;
__declspec(  dllexport  )  SHARE_dyn_bmp  *  help_shareDynBmp_getMemByIndex(  CHelp_shareDynBmp  *  pHelp,  HWND  hDlg_shareDynBmps,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  unsigned  int  index  );
__declspec(  dllexport  )  SHARE_dyn_bmp  *  help_shareDynBmp_getMemByIndex(  CHelp_shareDynBmp  *  pHelp,  SHARE_dynBmps  *  pShare,  unsigned  int  index  );
__declspec(  dllexport  )  int  help_shareDynBmp_getIndexByIndex_obj(  CHelp_shareDynBmp  *  pHelp,  HWND  hDlg_shareDynBmps,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  unsigned  int  index_obj,  unsigned  short  usHelp_subIndex  );
__declspec(  dllexport  )  int  help_shareDynBmp_getNewIndex(  CHelp_shareDynBmp  *  pHelp,  HWND  hDlg_shareDynBmps,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType  );



//  2014/09/09
class  CHelp_shareDynBmp:public  CQySyncFlg
{
public:
	SHARE_dyn_bmp  *  getMemByIndex(  HWND  hDlg_shareDynBmps,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  unsigned  int  index  )  {
						 return  help_shareDynBmp_getMemByIndex(  this,  hDlg_shareDynBmps,  pDLG_shareDynBmps_var,  uiObjType,  index  );						
	};
	//  2014/11/01
	SHARE_dyn_bmp  *  getMemByIndex(  SHARE_dynBmps  *  pShare,  unsigned  int  index  )  {
						 return  help_shareDynBmp_getMemByIndex(  this,  pShare,  index  );						
	};
		
	//
	int  getIndexByIndex_obj(  HWND  hDlg_shareDynBmps,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  unsigned  int  index_obj,  unsigned  short  usHelp_subIndex  )  {
			return  help_shareDynBmp_getIndexByIndex_obj(  this,  hDlg_shareDynBmps,  pDLG_shareDynBmps_var,  uiObjType,  index_obj,  usHelp_subIndex  );
	};

	SHARE_dyn_bmp  *  getMemByIndex_obj(  HWND  hDlg_shareDynBmps,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  unsigned  int  index_obj,  unsigned  short  usHelp_subIndex  )  {
						 int  index  =  getIndexByIndex_obj(  hDlg_shareDynBmps,  pDLG_shareDynBmps_var,  uiObjType,  index_obj,  usHelp_subIndex  );
						 if  (  index  <  0  )  return  NULL;
						 return  help_shareDynBmp_getMemByIndex(  this,  hDlg_shareDynBmps,  pDLG_shareDynBmps_var,  uiObjType,  index  );
	};
	//	
	int  clear(  SHARE_dyn_bmp  *  pDynBmpMem  )  {
		 return  shareDynBmp_clear(  pDynBmpMem  );
	};
	//
	int  getNewIndex(  HWND  hDlg_shareDynBmps,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType  )  {
		 return  help_shareDynBmp_getNewIndex(  this,  hDlg_shareDynBmps,  pDLG_shareDynBmps_var,  uiObjType  );
	};

};


//
__declspec(  dllexport  )  int  initShareDynBmpsThread(  MC_VAR_common  *  pProcInfo,  HWND  hDlgShareDynBmps,  DLG_shareDynBmps_var  *  pDlgVar,  ShareDynBmps_threadProcInfo  *  p  );
__declspec(  dllexport  )  int  exitShareDynBmsThread(  MC_VAR_common  *  pProcInfo,  ShareDynBmps_threadProcInfo	*	p  );


//
__declspec(  dllexport  )  int  storeRecvdReq(  HWND  m_hWnd,  DLG_shareDynBmps_var  *  pVar,  MIS_MSGU  *  pMsg,  unsigned  char  ucbSaveVideo_reply,  int  *piIndex_store  );
 __declspec(  dllexport  )  int  noStoreRecvdReq(  HWND  m_hWnd,  DLG_shareDynBmps_var  *  pVar,  int  iIndex_store  );
 __declspec(  dllexport  )  BOOL  canPeerSaveVideo(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  QY_MESSENGER_ID  *  pIdInfo_peer  );

//
__declspec(  dllexport  )  int  procRetrieveDynBmpsReq(  HWND  m_hWnd,  DLG_shareDynBmps_var  *  pVar,  MIS_MSG_INPUT  *  pMsgInput  );
//
__declspec(  dllexport  )  int  procVerifyViewDynBmpResp_step4(  HWND  m_hWnd,  DLG_shareDynBmps_var  *  pVar,  unsigned  int  uiObjType,  int  index_pShare_mem  );
__declspec(  dllexport  )  int  procVerifyViewDynBmpResp(  HWND  m_hWnd,  DLG_shareDynBmps_var  *  pVar,  MIS_MSG_INPUT  *  pMsgInput  );

//
int  getOnvifRuleIndex(  ShareDynBmps_onvif_rulesInfo  *  pRulesInfo,  unsigned  short  usIndex_obj  );

//
__declspec(  dllexport  )  int  get_realUrl(  IP_dev  *  pIpDev,  char  *  url,  int  urlCnt  );


//
typedef  struct  __webcamInfo_t		{
				 int				index_obj;
				 //
				 TCHAR				aName[256];
				 TCHAR				vName[256];
				 //
				 TCHAR				cusName[128];
				 unsigned  char		ucbUnresizable;
				 //
				 unsigned  char		ucbAutoOpenOnStartup;

}		 WEBCAM_info;


//
int  getWebcamInfo(  unsigned  int  uiObjType,  int  index_obj,  WEBCAM_info  *  pWebcamInfo  );



#endif  //  }


