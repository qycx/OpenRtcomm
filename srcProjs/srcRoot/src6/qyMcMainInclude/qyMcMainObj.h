
#ifndef  __QYMCOBJ_H__
#define  __QYMCOBJ_H__  /*  {  */

//
#include	"qyGuiCommon.h"
#include	"qyMcMainDefs.h"
#include	"qyMcDlgBarCfg.h"
#include	"qyOpenGuiCommon.h"
#include	"qisGuiPublic_public.h"

//



//
typedef  struct  __qyMcWeb_t								{		
				 char										url[QIM_MAXURLLOGLEN + 1];
}		 QY_MC_WEB;


typedef  struct  __qyMcSite_t								{	//	siteUrl¾ö¶¨Ò»¸öÕ¾µã£¬idÎª0Ê±±íÃ÷¸ÃÖµÎ´Éè¡£
				 char										url[QIM_MAXURLLOGLEN  +  1];
				 int										id;
}		 QY_MC_SITE;


typedef  struct  __qyMcBtnCfg_t								{
				 unsigned  short							horOffset;
				 unsigned  short							verOffset;
				 unsigned  short							topOffset;
				 unsigned  short							bottomOffset;
				 unsigned  short							width;
				 unsigned  short							height;
}		 QY_MC_BTNCFG;


#define		DEFAULT_HOR_OFFSET								15
#define		DEFAULT_VER_OFFSET								8
#define		DEFAULT_TOP_OFFSET								8
#define		DEFAULT_BOTTOM_OFFSET							8
#define		DEFAULT_BTN_WIDTH								80
#define		DEFAULT_BTN_HEIGHT								23
	

#define		DEFAULT_QY_MC_MENU_ITEM_NAME_LEN				64


typedef  struct  __qnmImageSet_t							{

				 unsigned  short							nImage_unknown;
				 unsigned  short							nImage_router;
				 unsigned  short							nImage_switcher3;
				 unsigned  short							nImage_switcher2;
				 unsigned  short							nImage_pcNormal;
				 unsigned  short							nImage_pcAdminDown;
				 unsigned  short							nImage_pcWait;

}		  QNM_IMAGE_SET;
				 


// Í¼±êÅäÖÃ
typedef  struct  __qyMcImageCfg_t							{
				 
				 QNM_IMAGE_SET								normal,  offline,  directConn,  secureConn,  normalWarn,  offlineWarn;

				 unsigned  short							nImage_portUp;
				 unsigned  short							nImage_portAdminDown;
				 unsigned  short							nImage_portWait;
				 unsigned  short							nImage_connectedDev;
				 
				 unsigned  short							nImage_folder,  nImage_selectedFolder;
				 unsigned  short							nImage_col2,  nImage_selectedCol2;  
				 unsigned  short							nImage_col3,  nImage_selectedCol3;
				 unsigned  short							nImage_col4,  nImage_selectedCol4;
				 unsigned  short							nImage_unRegPc,  nImage_selectedUnRegPc;

				 //
				 unsigned  short							nImage_pcUsrInfo,  nImage_selectedPcUsrInfo;			//	2006/08/14
				 unsigned  short							nImage_pcStatus,  nImage_selectedPcStatus;				//	2006/08/14
				 unsigned  short							nImage_pcOpNode,  nImage_selectedPcOpNode;				//	2006/08/14
				 unsigned  short							nImage_os,  nImage_selectedOs;
				 //
				 unsigned  short							nImage_info,  nImage_selectedInfo;						//  2006/08/14, ÆÕÍ¨ÐÅÏ¢
				 //
				 unsigned  short							nImage_pcSoftwareEnv,  nImage_selectedPcSoftwareEnv;
				 unsigned  short							nImage_pcHardwareEnv,  nImage_selectedPcHardwareEnv;
 				 unsigned  short							nImage_pcRegistry,  nImage_selectedPcRegistry;			//  2006/06/012
				 unsigned  short							nImage_hardware,  nImage_software;
				 //
				 unsigned  short							nImage_sp;			

				 //  2007/05/12
				 unsigned  short							nImage_messenger,  nImage_selectedMessenger;
				 unsigned  short							nImage_me,  nImage_selectedMe;
				 unsigned  short							nImage_imGrps,  nImage_selectedImGrps;
				 unsigned  short							nImage_imGrp,  nImage_selectedImGrp;
				 //
				 unsigned  short							nImage_activeMem,  nImage_requestingMem, nImage_interruptedSpeakingMem;	//  2009/02/24

				 //  2018/06/28
				 unsigned  short							nImage_screen,  nImage_webcam;
				 //  2018/12/27
				 unsigned  short							nImage_mic;


}		 QY_MC_IMAGECFG;	


typedef  struct  __qyMcLogonCfg_t							{
				 unsigned  short							usMinPasswdLen;
				 unsigned  short							usMaxInvalidLogonAttempts;
}		 QY_MC_logonCfg;


// ×ÜÅäÖÃ
typedef  struct  __qyMcCfg_t								{

				 TCHAR										rootKey[QY_MAXKEYLEN + 1];
				 WCHAR										installDir[QY_MAXPATHLEN + 1];
				 WCHAR										appDataDir[CONST_qyMaxPathLen  +  1];		//  applicationData\\qycx\\·
				 WCHAR										workDir[QY_MAXPATHLEN + 1];
				 WCHAR										cusModuleDir[CONST_qyMaxPathLen  +  1];		//  
				 WCHAR										singleInstanceStr[32  +  1];
				 
				 QY_MC_BTNCFG								btn;
				 QY_MC_IMAGECFG								image;
				 UINT										nIdToolBar;
				 QNM_SYSCFG_INFO					*		pSysCfg;									//  2007/03/11
				 QNM_GUICFG_INFO					*		pGuiCfg;

				 //  
				 BOOL										bGetPolicyFromIni;							//  2010/07/27. especially for winCe

				 //
				 QNM_MODULES_LOADEDINFO						modulesLoadedInfo;							//  2004/08/16
				 //
				 unsigned  char								ucbThinkPad;								//  
				 unsigned  char								ucbBhqj;									//  2005/04/20
				 unsigned  char								ucbHaveDj;									//  2005/08/27
				 unsigned  char								ucbAdvancedOptionEnabled;					//  2005/11/18
				 unsigned  char								ucbAutoLogonSupported;						//  2006/03/08£¬__SUPPORT_AUTOLOGON__
				 unsigned  char								ucbRemoteDesktopSupported;					//  2006/03/08£¬__NOTSUPPORT_REMOTEDESKTOP__
				 unsigned  char								ucbPcMonSupported;							//  2006/03/08£¬__NOTSUPPORT_PCMON__
				 unsigned  char								ucbFileMonSupported;						//  2006/03/25
				 unsigned  char								ucbRasControlNotSupported;					//  2009/03/05
				 //


				 //  2011/03/26
				 unsigned  char								ucbNotSupported_dblClk;						//  在触摸屏时，最好不支持双击。

				 //
				 unsigned  char								ucbUseTrayIcon;								//  
				 int										iIDR_TRAY;
				 //
				 BOOL										bUseDxSurface;								//  2009/08/05
				 //
				 unsigned  char								ucbDsnless;									//  DNSLESS2007/06/13
				 TCHAR										defaultDbName[MAX_PATH  +  1];				//  ACCESS DSN

				 TCHAR										name[QIM_MAXNAMELEN + 1];
				 unsigned int								mutexTimeout;

				 QNM_DB_CFG									db;											//  


				 SOCK_TIMEOUT								to;
				 int										iTimeoutInMs_channelIdle_others;			//  2009/02/25
				 //  int										iTimeoutInMs_channelIdle_recv_others;		//  2011/01/31
				 int										iTimeoutInMs_channelIdle_recv_talk;			//  2011/01/31
				 
				 unsigned  short							usDelayInMsToViewToolbar;					//  2010/09/02

				 //
				 RW_lock_param								rwLockParam;								//  2009/05/13

				 //  
				 unsigned  char								ucbStartRegScan;
				 
				 //
				 int										iType_qnmTmpTab;

				 WCHAR										cfgFullFileName[CONST_qyMaxPathLen  +  1];	//  added on 2003/09/19. 不提供给用户编辑 
				 WCHAR										iniFullFileName[CONST_qyMaxPathLen  +  1];	//  2009/07/29。提供给用户编辑
				 //
				 WCHAR										qyMcTitle[256  +  1];
				 WCHAR										qyMcTitle_part0[64];
				 WCHAR										qyMcTitle_part1[64];


				 //
				 unsigned  char								ucbAdvancedVer;								//  2005/08/30

				 QNM_CUSTOM_COMM							custom;

				 unsigned  short							usMaxDisplayedElemsPerWnd;					//  2007/06/09
				 unsigned  short							usMaxDisplayedWnds;							//
				 //
				 unsigned  short							usMaxDisplayedTasksInDlgTalk;				//  2007/06/25

				 //
				 QWM_DYN_CFG								dynCfg;										//  2007/06/16
				 char										seqNo[64  +  1];
				 int										iSystemId_wanted;							//  ÎªÈ·±£ÏµÍ³Éú³ÉµÄÕýÈ·ÐÔ£¬¼ÓÈëÁË¶ÔiSystemIdµÄºË¶Ô

				 //  2009/03/05
				 QY_MC_logonCfg								logon;

				 //
				 struct										{
                     TCHAR									mutexName[64  +  1];
				 	 unsigned  int							uiInitCnt_sema;
				 	 unsigned  int							uiMaxCnt_sema;
					 //
					 unsigned  int							uiMilliSeconds_mutex_r;
					 unsigned  int							uiMilliSeconds_sema_r;
					 unsigned  int							uiMilliSeconds_mutex_w;
					 unsigned  int							uiMilliSeconds_sema_w;

				 }											cusModules;

				 //
				 TCHAR										tmInitFile[256];
				 TCHAR										smCfgFile[256];
				 TCHAR										smTmpLogFile[256];
				 //
				 TCHAR										hkPortStatusFile[256];
				 //
				 TCHAR										qmcLogFile[256];

				 //
				 TCHAR										ipcProcInitFile[256];
				 TCHAR										shareProcInitFile[256];

				 //
}		 QY_MC_CFG;


// ViewµÄ¹ÜÀí½á¹¹
typedef  struct  __qyMcMgrViewStruct_t						{
				 int										index;
				 BOOL										bStopDaemonRefresh;
				 int										iViewType;
}		QY_MC_MGRVIEWSTRUCT;









typedef  struct  __qyMcQuery_t								{

				 int										type;

				 int										iDsnIndex;						//  2006/12/31

				 TCHAR										selectPart[CONST_qyMaxSqlBufLen  +  1];
				 TCHAR										fromPart[MAX_SQLCLAUSELEN  +  1];
				 TCHAR										wherePart[MAX_SQLCLAUSELEN  +  1];
				 TCHAR										groupPart[CONST_qyMaxSqlClauseLen  +  1];
				 TCHAR										sortPart[MAX_SQLCLAUSELEN  +  1];
				 
				 TCHAR										preDocName[CONST_qyMaxPreDocNameLen + 1];
				 TCHAR										docName[CONST_qyMaxDocNameLen  +  1];
				 TCHAR										postDocName[CONST_qyMaxPostDocNameLen + 1];

				 unsigned  short							nSqlFields;
				 QY_COLUMNINFO								sqlColumns[CONST_qyMaxQueryCols  +  1];		//  sqlÓï¾äÖÐµÄÁÐÊôÐÔ
				 unsigned  short							nFields;				 
				 QY_COLUMNINFO								columns[CONST_qyMaxQueryCols  +  1];		//  ListViewÖÐµÄÁÐÊôÐÔ
				 
				 PF_qyLvConvrtProc							data2DisplayProc;
				 PF_qyLvConvrtProc							display2DataProc;

				 BAR_CFG				*					pBarCfg;

				 PF_commonHandler							pfProcEvent;
				 PF_commonHandler							pfProcEvent_new;							//  和pcProcEvent的区别是第2个参数不是pDoc, 而是pDocStruct;

				 UINT										uPopupMenuId;
				 int										nSubMenuPos;
				 int										nSubMenuPos_multiSel;						//  2007/08/24, ¶àÑ¡µ¯³ö²Ëµ¥
				 int										nSubMenuPos_notSel;							//  2006/04/16, µ±µã»÷ÁÐ±í¿Õ°×´¦Ê±£¬µ¯³öµÄ×Ó²Ëµ¥
				 unsigned  int								uiDefaultCmd;								//  2004/04/17¼Ó, µ±Ë«»÷Ê±£¬¼¤·¢µÄÃüÁî
				 //
				 unsigned  char								ucbMultiSel;								//  2007/08/24, ÊÇ·ñ¿É¶àÑ¡

				 //
				 HWND										hFrame;										//  2009/09/03

				 //
				 int										curnItem;
				 QY_ITEMCONTENT								curItemContent;


}		 QY_MC_QUERY;



typedef  struct  __qyWmBufGetSelInfo_t						{
				 MACRO_qyWmBuf_commHead
	
				 int										iSel;
				 QY_ITEMCONTENT								itemContent;
}		 QY_WMBUF_GETSELINFO;


#define		DEFAULT_QY_MC_MON_ITEM_LEN						128			// ×î´óÌõÄ¿³¤¶È
#define		MAX_QY_MC_MON_ITEMS								36			// ×î´ó¼àÊÓÌõÄ¿Êý
#define		MAX_QY_MC_MON_WINDOWS							100			// ×î´ó¼àÊÓ´°ÊýÄ¿
#define		QY_MC_TOTAL_DAEMON_THREADS						10			// ºóÌ¨Ïß³ÌÊý
#define		DEFAULT_MAX_MON_CLASS_CNT						5			// ×î´ó¹Ø¼ü×Ö¼àÊÓÀà±ð


#define		DEFAULT_QY_MC_MUTEX								"qyMcMtx"
#define		DEFAULT_QY_MC_MUTEX_TIMEOUT						2000


// ÒÔÏÂÖ÷ÒªÓÃÓÚÒÔListViewÐÎÊ½ÏÔÊ¾µÄÇÐ»»ÌõÄ¿µÄÃû³ÆºÍid, ÄÚÈÝ²»°üº¬ÔÚÄÚ
typedef  struct  __qyMcItem_t								{
				 char			*							name;
				 int										id;
}		 QY_MC_ITEM;


// ÒÔÏÂÎª¹ý³Ì
//		È«¿Õ												Free
//		bGuiStateÎªQY_MC_STATE_INITED						guiÒÔÉêÇëÊ¹ÓÃ´Ë×ÊÔ´£¬µ«ÉÐÎ´×¼±¸Íê±Ï¡£
//															½«ÔÚ³õÊ¼ÏÔÊ¾Ö®ºó½øÈëUSED
//		bGuiStateÎªQY_MC_STATE_USED							guiÕýÇëÇóºóÌ¨Ë¢ÐÂ	
//		bDaemonStateÎªQY_MC_STATE_USED						daemonÕýË¢ÐÂ
//		bDaemonStateÎªQY_MC_STATE_FREE						daemonÃ»ÓÐË¢ÐÂ
//		bGuiStateÎªQY_MC_STATE_STOPDAEMONREFRESH			Í£Ö¹ºóÌ¨Ë¢ÐÂ
//															¿ÉÒÔÖØÐÂ½øÈëUSED
//		bGuiStateÎªQY_MC_STATE_UNUSE						guiÇëÇóÊÍ·Å

#define		QY_MC_STATE_FREE								0
#define		QY_MC_STATE_INITED								1
#define		QY_MC_STATE_USED								2
#define		QY_MC_STATE_STOPDAEMONREFRESH					3
#define		QY_MC_STATE_UNUSE								4

// ÊÓµÄÀàÐÍ.
#define		QY_VIEWTYPE_MCROOTTREE							10
#define		QY_VIEWTYPE_MCROOTLIST							20
#define		QY_VIEWTYPE_MCSITELEFT							80
#define		QY_VIEWTYPE_MCSITERIGHT							90


#define		CONST_qySelType_mcRootTree						0
#define		CONST_qySelType_mcRootList						10
#define		QY_SELTYPE_MCROOTTREE							CONST_qySelType_mcRootTree
#define		QY_SELTYPE_MCROOTLIST							CONST_qySelType_mcRootList
#define		QY_SELTYPE_MCBARLOG								40
#define		QY_SELTYPE_MCSITELEFT							50
//  #define		QY_SELTYPE_MCQUERY								CONST_qySelType_mcQuery
#define		CONST_qySelType_mcQuery							60
#define		CONST_qySelType_mcView							70
#define		CONST_qySelType_mcDlgLv							75

//	
//  Ñ¡ÔñÐÅÏ¢½á¹¹

//  rootTree Ñ¡ÔñÐÅÏ¢½á¹¹
typedef  struct  __qyMcRootTreeSel_t						{
				 
				 int										type;				//  ¾ö¶¨ÊÇÊ²Ã´Ê÷

				 int										iDsnIndex;			//  2007/01/01

				 TCHAR										wherePart[MAX_SQLCLAUSELEN  +  1];
				 //  char										selectedIp[CONST_qyMaxIpLen  +  1];
				 char										selectedSwitchMac[CONST_qyMacLen  +  1];
				 char										selectedMac[CONST_qyMacLen  +  1];

				 TCHAR										preDocName[32 + 1];
				 TCHAR										docName[CONST_qyMaxDocNameLen  +  1];
				 TCHAR										postDocName[32 + 1];


				 //  ÏÂÃæµÄ³ÉÔ±£¬Ö»ÔÚÎÄµ²ÖÐ´æÔÚ
				 PF_commonHandler							pfProcTreeSel;			//  È¡Òª´¦ÀíµÄÐÅÏ¢
				 PF_commonHandler							pfProcListSel;			//  Èç¹ûÓÐListView, Ôò´Ëº¯ÊýÎªListViewÈ¡Òª´¦ÀíµÄListViewµÄÏîµÄÐÅÏ¢£¬ÒòÎªtreeViewÊÇ·¢ÆðÕß£¬ËùÒÔ½«º¯ÊýÉèÖÃ·ÅÔÚÕâÀï
				 PF_commonHandler							pfProcEvent;
				 PF_commonHandler							pfDisplayContent;		//  ÏÔÊ¾¾ä±ú
				 PF_commonHandler							pfRefreshItem;			//  Ë¢ÐÂ½Úµã¾ä±ú
				 PF_commonHandler							pfDisplayListContent;	//  ÏÔÊ¾ÓÒ±ßµÄlistView, 2004/07/27


				 //  ÏÂÃæÊÇ²Ù×÷ÐÅÏ¢
				 HTREEITEM									hItem;
				 BOOL										bRoot;
				 int										iHelpId;
				 QY_OBJINDEX_RCD							objIndex;
				 unsigned  char								ucbSetFocusOnRightView;
				 union										{
					 QY_SWITCHPORT_RCD						switchPort;
					 //
					 IM_GRP_INFO							imGrpInfo;		//  2017/07/29
					 //
				 }											u;
				 
}		 QY_MCROOTTREE_SEL;


typedef  struct  __qyMcRootListSel_t						{
				 int										type;
				 int										curnItem;
				 QY_MCROOTTREE_SEL							leftTreeSel;
				 QY_COLUMNINFO								columns[CONST_qyMaxQueryCols  +  1];		//  ListViewÖÐµÄÁÐÊôÐÔ
}		 QY_MCROOTLIST_SEL;


typedef  struct  __qyMcSiteLeftSel							{
				 int										itemId;
}		 QY_MCSITELEFT_SEL;


typedef  struct  __qyMcBarLogSel_t							{
				 char										url[1024];
}		 QY_MCBARLOG_SEL;			//  ÎªÊ¹±àÒëÍ¨¹ýÁÙÊ±±àµÄ½á¹¹, 2003/10/02






typedef  struct  __qyMcDlgLvSel_t							{
				 int										type;

				 int										iDsnIndex;									//  2007/01/01

				 unsigned  int								uiDefaultCmd;								//  2004/04/17¼Ó£¬µ±Ë«»÷Ê±£¬¼¤·¢µÄÃüÁî

}		 QY_MCDLGLV_SEL;



//  Ñ¡Ôñ²Ù×÷µÄÐÅÏ¢½á¹¹
typedef  struct  __qyMcSel_t								{
				 int										type;		
				 unsigned  char								ucbUniqueView;								//  ÊÇ·ñµ¥Ò»´°¿ÚÏÔÊ¾£¨²»ÄÜ´ò¿ª¶à¸öView£©, 2003/09/24
				 unsigned  char								reserved[3];								//  2003/09/24
				 //
				 void								*		pWnd;										//  2018/11/15
				 //
				 union										{
								QY_MCROOTTREE_SEL			rootTree;
								QY_MCROOTLIST_SEL			rootList;
								QY_MCBARLOG_SEL				barLog;
								QY_MCSITELEFT_SEL			siteLeft;
								QY_MC_QUERY					query;
								QY_MCVIEW_SEL				mcView;										//  2006/12/24
								QY_MCDLGLV_SEL				mcDlgLv;
				 }											u;
}		 QY_MC_SEL;



//  ÏµÍ³µÄÏÔÊ¾ÅäÖÃÍ¨ÓÃ½á¹¹
typedef  struct  __qyMcDisplayCfg_t							{
				 int										m_iDocType;					
				 int										m_iViewType;
				 
}		QY_MC_DISPLAYCFG;



typedef  struct  __qyMcDocInfo_t							{
				int											iDocType;
				union										{
					QY_MC_WEB								web;
					QY_MC_SITE								site;
					QY_MC_QUERY								query;
				}											u;
}		QY_MC_DOCINFO;


#include  "qyMcMainCommonObj.h"

//  2015/12/08
#include	"ctxQmThread.h"


//
typedef  struct  __qyMcGui_t									{
	
				 //  2015/12/08
				 CTX_qm_thread									ctx_gui_thread;

				 //
				 void								*			pDb;
				 HANDLE											hMutex_singleInstance;

				 QY_LOG_CTX										logCtx;
				 
				 //  
				 HMENU											hMenuChildFrm;

				 HANDLE											hProcessStatusTool;
				 
				 //
				 unsigned  char									ucbMainHooked;						//  2005/10/01
				 unsigned  char									ucbNotSplashed;						//  2005/11/06

				 //
				 GENERIC_Q										processQ;							//  
				 unsigned  char									ucbProcessQInited;					//  2007/06/01

				 //
				 BOOL											bWait_reposted_guiMsgArrive;		//  2009/06/03
				 DWORD											dwTickCnt_reposted_guiMsgArrive;	//  2009/06/03

				 //
				 HWND											hMainWnd;							//  2009/03/25

				 //  2017/01/05
				 HWND											hGuiWnd;
				 int											iWndContentType_hGuiWnd;
				 //
				 //
				 HWND											hWnd_popupTool;												//  2011/03/04
				 HWND											hWnd_menu;													//  2011/03/18
				 HWND											hWnd_modal;							//  2016/09/12.	2011/03/30				 
				 HWND											hWnd_fileDialog;											//  2013/02/22				 
				 DWORD											dwStartTickCnt_fileDialog;

				 //
				 QY_PROGRESS									progress;

				 //
}		 QY_MC_GUI;


//  #define		CONST_maxServiceGuis							10
#define		CONST_maxServiceGuis							1									//  2009/12/21
//
typedef  struct  __qyServiceGuiCfg_t						{
				 int										iServiceId;

				 //  2015/01/20
				 PF_commonHandler							pfNewVar;							//  2015/01/20
				 PF_commonHandler							pfFreeVar;

				 //
				 unsigned  int								uiVarSize;							//  
				 PF_commonHandler							pfInitVar;
				 PF_commonHandler							pfInit_afterLogon;					//  201003/10
				 PF_commonHandler							pfExitVar;							//

				 //
				 int										iDbType;							//  Obsolete

}		 QY_SERVICEGUI_CFG;


typedef  struct  __qyServiceGuiInfo_t						{
				 QY_SERVICEGUI_CFG							cfg;
				 //
				 TCHAR										name[32  +  1];
				 //
				 void							*			pParent;			//  2016/09/19Ö¸Ïòdaemon
				 //
				 void							*			pVar;
				 unsigned  char								ucbVarInited;
				 //

}		 QY_SERVICEGUI_INFO;


typedef  struct  __mcCtx_displayedWnd_t					{
				 int									iType;
				 HWND									hWnd;
				 TCHAR									wndName[32  +  1];
				 //
				 GENERIC_Q								displayedElemQ;							//  
				 BOOL									bQInited;
				 void							**		ppDisplayedElems_sortedByKey;			//
}		 MC_CTX_DISPLAYEDWND;

//
int  getCountryCode(  char  *  countryCode,  unsigned  int  size  );

//  
int  initMcCtxDisplayedWnd( CCtxQyMc  *  pQyMc, HWND  hWnd,  LPCTSTR  wndName,  MC_CTX_DISPLAYEDWND  *  pCtx  );
void  exitMcCtxDisplayedWnd(  CCtxQyMc  *  pQyMc,  HWND  hWnd,  MC_CTX_DISPLAYEDWND  *  pCtx );




QY_OBJ_DB  *  getProcedObjDbs(  QY_MC  *  pQyMc  );
unsigned  int  getProcedObjDbsMaxCnt(  QY_MC  *  pQyMc  );
QY_OBJ_DB  *  getProcedObjDb(  QY_MC  *  pQyMc,  void  *  p0,  int  iDsnIndex  );
//
QY_OBJ_DB  *  selectObjDb(  void  *  p0,  void  *  p1,  void  *  p2  );
//
int  exitProcedObjDbs(  QY_MC  *  pQyMc  );

//
int  getProcedObjsCfg(  QY_MC  *  pQyMc  );


//
__declspec(  dllexport  )  int viewDlgListView_db(  HWND  hParent,  int  iWndContentType,  void  *  pSelParam  );
 

#endif  /*  }  */

