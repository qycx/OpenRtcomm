

#ifndef  __DLGTALKPROC_H__	
#define  __DLGTALKPROC_H__	//  {

//
#include	"qySyncCommProc.h"
//
#include	"gpsCommProc.h"
#include	"qmcVWall.h"
//
#include	"qmcMosaic.h"
//
#include	"subtitles.h"
#include	"dlgTalkPublic.h"
#include	"qmcObjVarInfo.h"
#include	"qisD3dDefs.h"

//
#include	"qmcTaskInfo.h"

//
#include	"isCliHelpPublic.h"



//
#define		CONST_bkColor_meDesc				RGB(  200,  210,  226  )


//  2012/04/09
#define		M_BeginDeferWindowPos(  nNumWindows)													BeginDeferWindowPos(  nNumWindows);  int  tmp_n_deferWindowPos;	tmp_n_deferWindowPos  =  nNumWindows;
#define		M_DeferWindowPos(  hWinPosInfo,  hWnd,  hWndInsertAfter,  x,  y,  cx,  cy,  uFlags)		{  DeferWindowPos(  hWinPosInfo,  hWnd,  hWndInsertAfter,  x,  y,  cx,  cy,  uFlags);  tmp_n_deferWindowPos  --  ;  }
#define		M_EndDeferWindowPos(  hWinPosInfo);														MACRO_qyAssert(  !tmp_n_deferWindowPos,  _T(  "deferWindow err"  )  );	EndDeferWindowPos(  hWinPosInfo  );



//
#define		DEFAULT_fontSize_talk				"10pt"  					//"11pt"  					 					

#define		CONST_cssTag1						"St1"
#define		CONST_cssTag2						"St2"

#define		CONST_paddingRight					_T(  "10px"  )


//
#define		CONST_iW_memberList					150							//  
#define		CONST_iW_subject					118
#define		CONST_iW_contacter					65
#define		CONST_iW_shortTime					60
#define		CONST_iH_dlgDesc					15
//
#define		CONST_iH_static_peerInfo			15							//  2017/08/21

//  
#define		MIN_iW_status						150
#define		CONST_iH_status						15							//  2017/10/02

//
#define		CONST_maxRowIdStrLen				64							//  16
//
#define		CONST_rowIdStr_cur					_T(  "rowIdStr_cur"  )		//  2007/07/22
#define		CONST_iStatus_cur					_T(  "iStatus_cur"  )		//  2007/07/23
//
#define		CONST_nSubItem_rowId_cur			2							//  taskList
#define		CONST_nSubItem_iStatus_cur			3
#define		CONST_nSubItem_uiTaskType			5
#define		CONST_nSubItem_status				6							//  2007/07/17


#define		CONST_rowType_null					0
#define		CONST_rowType_who					1
#define		CONST_rowType_content				2
#define		CONST_rowType_sendFile				3

#ifndef  __WINCE__
		 //  #define	CONST_maxCnt_content				2048
		 #define		CONST_maxCnt_content				16  *  1024
		 #define		CONST_maxCnt_txtContent				1024									//  2007/08/12
#else
		 #define		CONST_maxCnt_content				1  *  1024
		 #define		CONST_maxCnt_txtContent				1										//  2007/08/12
#endif

typedef  struct  __paramProcRow_t				{
				 long							lRowIndex;
				 //  unsigned  int					uiTranNo;
				 int							iTaskId;
				 QY_MESSENGER_ID				idInfo_talker;
				 TCHAR							talker[256];
				 unsigned  short				usOp;												//  
				 int							iStatus;
				 char							timeBuf[CONST_qyTimeLen  +  1];

				 TCHAR							rowIdStr[CONST_maxRowIdStrLen  +  1];				//  
				 //
 				 TCHAR							content[CONST_maxCnt_content];						//  2010/12/05
				 TCHAR							txtContent[CONST_maxCnt_txtContent];				//  2010/12/05

				 //
				 PF_commonHandler				pf;
				 int							iCol;

				 long							lRowIndex_who_gotByRowId;							  
				 //
				 BOOL							bAddOnRowIndex;										//  2007/07/13
				 BOOL							bFollowingRows;										//  
				 
				 int							nItem;

				 // 
				 BOOL							bScrollIntoView;									//  
				 long							lColor;												//  

				 BOOL							bNewMsg;											//  2007/08/13
				 
				 unsigned  char					ucbNeedAsk;											//  cancelTasks(  )
				 unsigned  char					ucbAsked;											//  
				 BOOL							bAutoCancel;										//  2014/07/30
				 //
				 int							iRetVal_id_messageBox;								//  2016/02/03

				 //
				 long							scrollTop_body,  clientHeight_body;
				 long							lRowIndex_top;										//  
				 long							lRowIndex_bottom;

				 BOOL							bMsgNeedRemoved;									//  2009/09/07

				 //
				 unsigned  int					nMsgTalks_processed_inProcessQ;						//  2012/05/20

				 //
				 HWND							hListCtrl;											//  2017/06/25

				 //  2017/08/08
				 unsigned  char  				ucbNoMe;

}		 PARAM_PROC_ROW;



#define		CONST_html_input					"<html><head><style type=\"text/css\">"					\
												"<!-- "													\
												"body {font-size:"  DEFAULT_fontSize_talk  "}"			\
												" --> "													\
												"</style>"												\
												"<title>input</title></head><body scroll=\"auto\" leftmargin=\"1\" topmargin=\"0\"></body></html>"
//




#define		CONST_html_recentMsgList			"<html><head><style type=\"text/css\">"					\
												"<!-- "													\
												" --> "													\
												"</style>"												\
												"<title>recentMsgList</title></head><body scroll=\"auto\" leftmargin=\"1\" topmargin=\"0\"><font size=1><table cols=8 border=0 cellpadding=0 cellspacing=0 width=100%><colgroup><col style=\"display:none\"><col style=\"display:none\"><col><col><col><col><col><col></colgroup><tbody></tbody></table></font></body></html>"




//
//  ÄÚ²¿´¦ÀíµÄ¸ñÊ½Îª http://CONST_qmInternalUrl_root/taskId/rowIdStr/opStr/paramStr/default.htm, 
//
#define		CONST_qmInternalUrl_root		_T(  "http://2007qm.qycx.com/"  )



typedef  struct  __taskDisplay_t				{
        		 int							id;
				 TCHAR							rowIdStr[CONST_maxRowIdStrLen  +  1];
				 TCHAR							typeStr[256];
				 TCHAR							subject[256];
				 time_t							tEndTime;
				 int							iStatus;
				 //  QY_MESSENGER_ID				idInfo_send;
				 TCHAR							displayName_sender[32];
				 time_t							tSendTime;
				 time_t							tRecvTime;
}		TASK_DISPLAY;




#define		CONST_htmlEditType_null								0
#define		CONST_htmlEditType_input							1
#define		CONST_htmlEditType_recentMsgList					2



//
typedef  struct  __dlgTalkAv_t				{
				//
				CAP_RECT					peerCapRect,  meCapRect;
				//
				CAP_IMAGES					peerImages, meImages;
				
				//
				int							iIndex_sharedObj_localAv;				//  2009/12/28
				unsigned  char				ucbGot_iIndex_sharedObj_localAv;		//  2009/08/16

				//
				//  2009/02/20
				struct						{
					BOOL					bTaskExists;
					int						iTaskId;
					int						iIndex_sharedObj;
					QY_MESSENGER_ID			idInfo_starter;
					unsigned  char			ucbVideoConferenceStarter;

					unsigned  int			uiInitW;
					unsigned  int			uiInitH;
					
					HWND					hWnd_remoteAv;

					time_t					tStartTime_org;							//  ÇëÇó·¢ÆðµÄÊ±¼ä, ÕâÊÇÎªÁËÈ·¶¨ÊÇÄÄ¸öÈÎÎñ±»µÃµ½ÁËÔÊÐí
					unsigned  int			uiTranNo_org;							//
					//  unsigned  int			uiSerialNo_org;						//  Ã»Ê²Ã´ÓÃ
					unsigned  int			uiContentType_org;

				}							taskInfo;

}		DLG_TALK_av;

 typedef  struct  __dynMenu_t				{
				  struct					{
					  int					nID;
					  TCHAR					str[128];
				  }							mems[10];
 }		  myDYN_MENU;	


typedef  struct  __taskAutoAnswer_t			{
				 unsigned  int				uiCmd_autoAnswer;						//  2010/11/28
				 struct						{
					 BOOL					bTaskNeedAutoAnswered;					//  2010/09/07				
					 int					iTaskId;
					 int					iTaskStatus;
				 }							task;
}		 TASK_autoAnswer;


//  2010/12/21
#define		DEFAULT_usLayoutType			CONST_usLayoutType_dialog

//  2012/04/25
//  #define		MAX_talker_viewDynBmps			4  +  3	
//  #define		MAX_talker_viewDynBmps			CONST_vwRuleMessengerCmd_dynBmps		//  2014/05/31

//
#define		CONST_edge_l_dlgTalk_wall										0
#define		CONST_iX_spacing_dlgTalk_wall									0
#define		CONST_iY_spacing_dlgTalk_wall									0
//
#define		CONST_edge_l_dlgTalk_desktop									0
#define		CONST_edge_t_dlgTalk_desktop									0
#define		CONST_edge_b_dlgTalk_desktop									0
#define		CONST_iX_spacing_dlgTalk_desktop								0
#define		CONST_iY_spacing_dlgTalk_desktop								3


//  2011/10/02
typedef  struct  __dlgLayoutParam_t											{
	
				 int														iEdge_l;					//	=	10;
				 int														iEdge_t;					//	=	10;
				 int														iEdge_r;					//	=	10;
				 int														iEdge_b;					//	=	10;
				 //
				 int														iX_spacing;					//	=	10;			//  Á½¸ö¿Ø¼þ¼äµÄºáÏò¼ä¸ô
				 int														iY_spacing;					//	=	10;
				 //
				 int														iW_btn;						//	=	10;
				 int														iH_btn;						//	=	10;
				 //
				 int														iH_static;					//	=	30;			//  ºÍpicÏà¹ØµÄ±êÇ©µÄ¸ß¶È£¬¹Ì¶¨
				 //
				 int														iY_spacing_pic_static;		//	=	2;			//  Á½¸ö¿Ø¼þ¼äµÄ×ÝÏò¼ä¸ô
				 int														iY_spacing_static_pic;		//	=	4;			
				 //
				 int														iY_spacing_static_btn;		//	=	10;


}		 DLG_layout_param;



//  2013/02/26
typedef  struct  __dlgScrollInfo_t											{
				 // 2008/11/06. 			
				 BOOL														bScrollBarEnabled;
				 BOOL														notOnOffScrollBar;			//  2009/10/08
				 
				 int														m_nCurWidth;			
				 int														m_nScrollPos_h;
				 int														m_nCurHeight;
				 int														m_nScrollPos_v;
				
				 //  			
				 CAP_RECT													mems_org[1];
				 CAP_RECT													mems[1];					//  2012/05/04
				 
				 //				
				 RECT														m_rect;					

}		 DLG_scroll_info;

//  2014/01/25
typedef  struct  __msgToolCommon_t											{
				//
#ifndef  __MYHTMLEDITCTRL_H__
	#define	LP_MyHtmlEditCtrl		void  *
#endif

			LP_MyHtmlEditCtrl												m_pHtmlEdit_recentMsgList;
			LP_MyHtmlEditCtrl												m_pHtmlEdit_input;
	
			//
			int																idcList_task;
			QY_COLUMNINFO											*		pColumns_task;
			
			//
			TCHAR															tmp_desc[128];

}		 MSG_tool_common;


//  2014/11/16
typedef  struct  __dlgTalkMosaicTransStatus_t								{
				 unsigned  int												uiTranNo_openAvDev_confMosaic_video;
				 unsigned  int												uiTranNo_openAvDev_confMosaic_resource;

				 //
				 unsigned  char												ucb2Streams;

				 //
				 BOOL														bDisplayResource;				
				 int														iW_resource;
				 int														iH_resource;					
}		 DLG_talk_mosaicTransStatus;



//  2016/03/15
//  2014/08/04
typedef  struct  __talkerThreadProcInfo_t									{
				 MACRO_qyQThreadProcInfo_common

				 //
				 HWND														hDlgTalk_mgr;
				 void												*		pMgrVarParam;

				 //  2015/05/19
				 //  2014/09/07
				 struct														{
				 }															status;

}		 TALKER_threadProcInfo;





//
//
#define		CONST_avBtnStatus_av											1
#define		CONST_avBtnStatus_cancel										2
#define		CONST_avBtnStatus_re_accept										3

//
#define		CONST_intervalInMs_task_av_re_accept							2000
#define		CONST_intervalInMs_task_screenAndMediaFile_re_accept			5000


//
#define		MAX_grpMemStatuses												300

//
//
 typedef  struct  __grpMemStatus_t											{
				  QY_MESSENGER_ID											idInfo;
				  //
				  unsigned  short											usState;
				  //
				  int														nImage;
 }		  GrpMem_status;

 //
 typedef  struct  __grpMemListStatus_t										{
				  unsigned  short											usCnt;
				  GrpMem_status												mems[MAX_grpMemStatuses];
				  //
				  DWORD														dwTickCnt_lastRefreshed;
 }		  GrpMemList_status;

 
 //
 typedef  struct  __grpMemStatus_index_t									{
				  QY_MESSENGER_ID											idInfo;
				  int														index;
}		  GrpMem_status_index;


 //
 typedef  struct  __grpMemStatusIndexes_t									{
				  unsigned  short											usCnt;
				  GrpMem_status_index										mems[MAX_grpMemStatuses];
 }		  GrpMem_status_indexes;


//
typedef  struct  __dlgTalkVar_t												{
				 MACRO_objVarData_commonMems
					 
				 //  2015/11/12	
				 int														iIndex_talkerInfo;						//  2015/11/12

				 //
				 HWND														m_hParent;	
				 BOOL														bIncludeACap;						//  2013/03/19
				 
				 //
				 QY_MC* pQyMc;

				 //				
				 BOOL														bInitFailed;				//  2007/09/04
				 
				 //				
				 DWORD														dwTickCnt_created;						//  2014/02/04
							
				 //			
				 BOOL														bUseDirectX;				//  2009/08/06		
				 unsigned  char												ucbUseHtmlEdit;				//  2012/05/17. 只有需要输入的窗口才使用HtmlEdit, 主窗口和墙上的小talk窗口都不需要使用
				 unsigned  char												ucbAutoClip;				//  2014/04/06
				 unsigned  char												ucbAutoClip_me;				//  2016/02/17


				 //
				 #ifndef  __WINCE__
						  void										*		pm_LargeImageList;			//  CImageList
						  void										*		pm_SmallImageList;
				 #endif


				 //
				 MIS_CNT											*		pMisCnt;					//  misServName
				 
				 int														loopCtrl_timer;				//  2009/10/18
				 
				 //
				 int														iTaskId_activated;			//  2007/08/11, iTaskId_activated Îª0Ê±²»²Ù×÷¡£²»Îª0Ê±£¬±íÃ÷Òª¼¤»îÕâ¸öÈÎÎñ¡£ 2007/08/11
				 unsigned  char												ucbTaskIdSet;				//  2007/08/11
				 
				 //
				 unsigned  short											usMaxDisplayedTasks;		//  2007/06/26
			
				 //
				 MSGR_ADDR													addr;		
				 //
				 unsigned  char												ucbGuest;					//  			
				 //
				 unsigned  char												ucbTmpMsgr;					//  2012/05/23. 是否临时msgr, 是的话主要为非同分组成员.但是有授权的vieeviewDynBmp服务.
				 //
				 TCHAR														displayName[64  +  1];
				 TCHAR														talkerDesc[64  +  1];
				 //
				 WCHAR														wLocation[64  +  1];		//  2007/12/23
				 
				 //
				 int														iTalkUsage;

				 //
				 int														iTalkerSubType;				//  2012/04/30
						
				 //  		
				 HWND														hFore;						//  2007/09/09, 
				 
				 //
				 GENERIC_Q													tmpGrpMemQ;					//  2008/01/22
				 BOOL														bTmpGrpMemQInited;
				 //
				 int														iLvType_memList;			//  
				 unsigned  int												uiDefaultCmd_memList;		//  2004/04/17
			 
				 //
				 MC_CTX_DISPLAYEDWND										displayCtx;
				 BOOL														bDisplayCtxInited;
	
				 //	
				 GENERIC_Q											*		m_pProcessQ;					//  
				 
				 //  2017/07/01
				 int														idc_talkerList;
				 QY_COLUMNINFO										*		pColumns_talkers;
				 //
				 struct														{
					 int													iSelectItem;
				 }															talkerList;

				 //
				 int														idcList_members;
				 QY_COLUMNINFO										*		pColumns_members;
				 struct														{
					 int													iSelectItem;
				 }															listMembers;
				 

				 //
				 int														iRowId_internal;									//  
				 
				 int														iCol_content;							//  2007/07/02
				 //
				 int														nSubItem_status;						//  2007/07/17
				 
				 //
				 unsigned  __int64											curr_idinfo;							//2023/12/23
				 bool														is_curr;

				 //  
				 long														lColor_org;
				 long														lColor_active;
				 TCHAR														rowIdStr_active[64  +  1];
				 //
				 BOOL														bCellActivated;
				 
				 //
				 HMENU														hMenu;									//  2012/04/09
				 			
				 //
				 void												*		pCapStuff;								//  2009/08/19
				 //
				 int														iMenuId_selectedAudio;					//  2011/10/25
				 int														iMenuId_selectedVideo;
				 
				 //  2011/12/25
				 struct														{
					 struct													{
						 TCHAR												name_aDev[128];
						 TCHAR												name_vDev[128];			
					 }														recentDevs[1];
				 }															shareMediaDevice;
				 
				 //  2012/05/20
				 unsigned  int												nMsgTalks_processed_inProcessQ;
				 				 
				 //  2013/02/26
				 DLG_talk_layout											m_layout;
				 DLG_scroll_info											m_scrollInfo;
			
				 //  2011/10/02			
				 DLG_layout_param											m_layoutParam;
				 //
				 WINDOWPLACEMENT											m_oldWndPlacement;
				 struct														{
					 HMENU													hOldMenu;								//  2012/07/07
					 long													lOldStyle;								//  2012/07/07
				 }															m_fullScreenInfo;			
				 //
				 BOOL														m_bFullScreen;
				 RECT														m_fullScreenRect;
				 DLG_layout_param											m_oldLayoutParam;
				 //
				 BOOL														bDone_endFullscreen;					//  此标志位在点击一次endFullscreen设置, 2011/10/16
				 		
				 //  2007/12/22
				 unsigned  int												uiTimerId;

				 //
				 unsigned  int												uiTimerId_guiMsgArrive;
				 //
				 LPARAM														last_lParam_guiMsgArrive;
				 DWORD														lastTickCnt_guiMsgArrive;
				 				 
				 //  2012/04/03
				 unsigned  char												ucbOnGlobalVWall;						//  是否在GlobalVWall上
				 
				 //
				 struct														{
					 //
					 int													idc_peer,  idc_other,  idc_me,  idc_bgWall_conf;					//  2013/02/24
					 HWND													hCtrl_peer, hCtrl_other, hCtrl_me, hCtrl_bgWall_conf, hCtrl_RemoteVideo;
					 HWND													hWnd_dst_peer, hWnd_dst_RemoteVideo;		//  画在哪个窗口上
					 HDC													hDc_peer,  hDc_other,  hDc_me,  hDc_bgWall_conf, hDc_RemoteVideo;					//  2013/02/22
					 //
					 myZONE													peerZone,  otherZone,  meZone, remoteVideoZone;				//  2017/09/26
					 //
					 //
					 #ifdef  __DEBUG__
							 //CAP_IMAGES		  bgWallImages;			//  2014/10/01
					 #endif
					 SUB_V_WALL												bgWall;			//  2017/09/25
				
					 //  2012/05/05				
					 unsigned  short										usCnt_zoneParams;
					 ZONE_PARAM										*		pZoneParams;					 
					 //
					 ZONE_PARAM												zoneParams_localOnPeer[CONST_maxCapImages];
					 ZONE_PARAM												zoneParam_meOnBgWall;
					 
					 //
					 int													iIndex_sharedObj_localAv;				//  2009/12/28
					 int													iIndex_usr_localAv;						//  2010/09/06
					 unsigned  char											ucbGot_iIndex_sharedObj_localAv;		//  2009/08/16
				 				

					 //  2016/03/15
					 SYNC_mt_cnt											syncMtCnt_taskInfo;
					 
					 //  2009/02/20
					 struct													{
						 BOOL												bTaskExists;
						 int												iTaskId;
						 //
						 DWORD												dwTickCnt_start;
						 //
						 QMC_mosaic_maker									mosaicMaker;											//  2014/11/01					
						 //
						 struct      										{
							 BOOL											bExists_confMosaic;
							 //
							 //unsigned  int									uiTranNo_openAvDev_confMosaic_video;
							 //unsigned  int									uiTranNo_openAvDev_confMosaic_resource;
							 
							 //  2014/11/16
							 DLG_talk_mosaicTransStatus						status;
						 }													mosaicTrans;
					
						 //
						 QY_MESSENGER_ID									idInfo_starter;
						 unsigned  char										ucbStarter;										//  2010/08/31
						 unsigned  char										ucbVideoConference;								//  2010/08/31
						 //
						 unsigned  short									usConfType;										//  2017/08/25
						 
						 //
						 QY_MESSENGER_ID									idInfo_initiator;

						 //
						 QY_MESSENGER_ID									unused_idInfo_compere;							//  暂时不用，先用HgZcrs
						 //
						 //HgZcrs												zcrs;										//  下面的hgInfo里已经有了这个信息了

						 //
						 CONF_hg_info										hgInfo;

						 //
						 unsigned  int										uiInitW;
						 unsigned  int										uiInitH;
						 
						 time_t												tStartTime_org;									//  
						 unsigned  int										uiTranNo_org;									//
						 //  unsigned  int									uiSerialNo_org;									//  
						 unsigned  int										uiContentType_org;
					
						 //  					
						 AV_stream_simple									local_avStream;									//  2015/02/17
										
						 //					
						 int												iIndex_taskInfo;								//  2014/09/25
										
						 //					
						 //BOOL												bEnableToSpeak;									//  2010/12/29
						 
						 //
						 BOOL												bTaskInited;									//  2010/08/31
						 
						 //  
						 unsigned  short									usLayoutType_starter;							//  2010/12/21
						 						 
						 //
						 DWORD												dwLastTickCnt_confStarter_sendReq_toStopSending;				//  2014/10/09
				
						 //  2017/07/03
						 unsigned  char										ucbConfCtrl;

						 //
						 ConfMem_confCtrl									confMem_confCtrl;

						 //
						 struct												{
							 int											nTimes_vChannel_notReady;
						 }													confStarterInfo;

						 //  2017/09/17
						 struct												{
							 
							 //
							 unsigned  int									uiTranNo_retrieveAll;
							 unsigned  short								usSeqNo_retrievePart;
							 
							 //
							 DWORD											dwTickCnt_sent;
							 //
							 unsigned  char									ucbNeed_sendAll;

							 //
							 int											iW_conf;
							 int											iH_conf;
							 unsigned  short								usMaxFps;

						 }													confState;

						 //
						 #ifdef  __DEBUG__
								 BOOL  bDbgFlg;
						 #endif
								 						
						 //
						 bool												bNeedShowMeDesc;

						 //
						  //
						 struct
						 {
							 OneBigLayoutParam										oneBigLayoutParam;
						 }															tmpLayoutInfo;


					 }														taskInfo;
					 //
					 DWORD													dwTickCnt_closeTaskAv;   //  2017/10/03

					 //  2019/02/23
					 HWND													hWall;

					 //
					 //	2017/08/30			 
					 CONF_KEY												videoConferenceStatus;				

				 }															av;


				 //				
				 struct														{
							 //
							 QY_MESSENGER_ID								idInfo_sel;							 
					
				 }															confMgr_talkerListInfo;

				 //					
				 struct														{
							 //
							 QY_MESSENGER_ID								idInfo_sel;
							 //
							 QY_MESSENGER_ID								idInfo_talkTo;					
				 }															confMgr_grpMemListInfo;
						 

				 //  2017/09/07
				 struct														{
					 //
					 GrpMemList_status										grpMemListStatus;
					 //
					 GrpMem_status_indexes									indexes;
					 //
				 }															grpMemList;

				 //				 
				 //  2016/03/15
				 TALKER_threadProcInfo										talkerThreadInfo;
				 
				 //  2015/11/15			
				 D3D_talkerData_cfg											d3d_talkerData_cfg;
				 
				 //  2009/02/22
				 //DLG_TALK_videoConference									videoConference;
				 
				 //  2015/08/05
				 //  2014/12/09
				 struct														{
					BOOL													bTaskExists;
					//
					//
					BOOL													bInProgress_autoAnswer;			
				 }															autoAnswer;

				

				 //  2015/08/08
				 struct														{				
					 //  2014/12/08
					 BOOL													bNeedChkRecvdTasks;
				 }															needChkTasks;
				 
				 //
				 void										*				pShadowInfo;							//  2012/04/24
				 
				 //
				 HWND														hWnd_instantAssistant;					//  2009/02/18

				 //  2014/01/24
				 struct														{
					 RECT													rc;				//  相对窗口的坐标
					 HWND													hWnd_msgTool;
					 //
					 DWORD													dwModifiedTickCnt_showMsgTalk;			//  2016/03/25
					 //
				 }															msgTool;
				 
				 //
				 struct														{
					 PTZ_control_mem										cfg;
					 TCHAR													tHint[255  +  1];
					 //
					 HWND													hWnd_ptzControl;						//  2012/08/01
				 }															ptzControl;

				 //
				 BOOL														bSwapMouse;								//  2008/11/16
				 //  
				 struct														{										//  2017/08/23					 
					 //  
					 DWORD													dwTickCnt_sendLastMouseMove;		//  200811/22
					 //
					 struct													{		 			
						 int												x;
						 int												y;
						 UINT												nFlags;
						 BOOL												bMouseMove;		
					 }														lastMouseEvent;		
					 BOOL													bNeedSend_lastMouseEvent;			//  是否需要发送

				 }															remoteAssist;

				 //
				 struct														{
					 HWND													hWnd_subtitles;							//  2013/04/05
				 }															subtitles;
				 
				 //  2015/08/01
				 struct														{
					 HWND													hTool_offlineRes;
				 }															offlineRes;
				 
				 //  2014/12/23
				 struct														{
					 TCHAR													tHint[128];
				 }															promptToClose;
				 
				 //
				 struct {
					 int													nTimes_noConf;
				 }															chkConfStatus;

				 //	
				 CAP_subWnds												subWnds;
				 
				 //
				 TCHAR														tHint[256];
				 MIS_MSGU											*		pMsgBuf_doWnd_guiMsgArrive;				//  2009/12/08
				 			
				 //
				 DLG_guiData_talk											guiData;								//  2010/07/14
				
				 //  2012/05/18
				 DWORD														dwTickCnt_start_noShadow;
				 
				 //
				 BOOL														bCancelTasks;							//  2011/02/03
				 
				 //  2017/09/23
				 BOOL														bShouldQuit1;

				 //
				 DLG_syncFlgs												syncFlgs;

				 //
				 int														m_iCmd;
				 int														m_index_taskInfo_unused;


				 //
				 int														m_moveOperation;//窗口红色边框焦点的移动操作，上(0)、下(1)、左(2)、右(3)
				 //
				 int														m_bEnlarge1;
				 int														x, y;//手机放大指令的坐标
				 //  2026/04/13
				 struct {
					 //
					 QY_MESSENGER_ID										idInfo_enlarged;

				 }															mouseSel_3d;				 
				 //
				 QY_MESSENGER_ID											idInfo_requester;



				 //
}			DLG_TALK_var,  DLG_talk_var;



//
#include	"help_getDlgTalkVar.h"



//  2012/04/24
#define		isTalkerShadowMgr(  addr  )			(  !(  addr  ).uiTranNo_shadow  )

//  2012/05/14
#define		isInvisibleMgr(  m_var  )			(  isTalkerShadowMgr(  (  m_var  ).addr  )  &&  (  m_var  ).guiData.param.bNeedNotShowWnd  )  


//
typedef  struct  __talkerShadowMgrMem_t			{
					 HWND						hWall;
					 int						iWndContentType_wall;
					 //
					 WM_ID						wdId;								//  2016/01/30
					 //
					 unsigned  int				uiVwRuleType;
					 //
					 unsigned					uiTranNo_spObj;
					 //
					 int						iTalkerSubType;
					 HWND						hShadow;
					 //
					 VW_rule_messengerCmd		vwRuleCmd;
					 //
					 DWORD						dwTickCnt_lastRefreshed;

					 //
}		 TALKER_shadow_mgrMem;					


//  2015/07/30
typedef  struct  __confMgrInfo_t				{
				 unsigned  short				usCnt;
				 struct							{
					 QY_MESSENGER_ID			idInfo;
				 }								mems[20];
}		 CONF_mgr_info;

				 

//  2015/08/02
typedef  struct  __procOfflineRes_mem_t			{
				 QY_MESSENGER_ID				idInfo_req;
				 HWND							hTool_offlineRes;
				 unsigned  int					uiTranNo_progress_tool;	
				 //
				 unsigned  int					uiTranNo_real;
				 //
}		  PROC_offlineRes_mem;



//  2017/06/25
//
typedef  struct  __grpMemConfCtrl_t				{
				 QY_MESSENGER_ID				idInfo;		
				 //
				 int							id_imGrpMem;
				 //
				 TCHAR							displayName[65];
				 TCHAR							talkerDesc[128  +  1];

				 //  2017/08/30
				 TCHAR							ksName[32];
				 TCHAR							ysName[32];


				 //
				 struct							{
					 unsigned  char				ucbPermitToSpeak;					
				 }								m_var;

				 //
}		  GrpMem_confCtrl;

	 
//
typedef  struct  __grpConfCtrl_t				{
				 unsigned  short				usMaxCnt;
				 unsigned  short				usCnt;				
				 GrpMem_confCtrl			*	pMems;
}		 GRP_confCtrl;





//
typedef  struct  __talkerShadowMgr_t									{


				 //  2014/07/14
				 unsigned  char											ucbNewMsgArrives;

				 //  2014/12/23
				 struct													{
					 SUBTITLE_msgs										msgs;
				 }														msg;

				 //  2013/02/28
				 struct													{
					 //
					 CONF_mgr_info										confMgrInfo;
					 //  2015/07/29
					 unsigned  char										ucbMeConfMgr;

					 //
					 unsigned  short									usLayoutType_local;						//  2010/12/21. if usLayoutType_local is 0, usLayoutType_starter is adopted.

					 //  2016/03/27
					 struct												{
						 int											idcRet_joinInBgWall;								//  2014/10/07
						 //
						 //unsigned  char								ucbNeedToAsk_willingTo_joinInBgWall;				//  2017/11/01
						
					 }													joinInBgWall;

				 }														av;

				 //  2017/08/24
				 struct													{
						 BOOL											bTaskExists_recvd_screenAndMediaFile;					
						 //
						 INFO_recvResource								info_recv;
						 
						 //  2017/08/24
						 INFO_sendResource								info_send;

				 }														resourcesInfo;
				 
				 //  2014/11/12
				 struct													{
					 unsigned  char  									ucbExists_localScreenSharing;
				 }														shareScreen;

				 //  2012/04/20
				 struct													{
					 int												iTaskId;

					 DWORD												dwTickCnt_lastRecvd;

					 //
					 myGPS_POSITION										gpsPos;
				 }														viewGps;

				 //  2013/03/03
				 struct													{
					 HWND												hWnd_ptzControl;
				 }														ptz;

				 //  2013/04/05
				 struct													{
					 HWND												hWnd_subtitles;							//  2013/04/05
					 //
					 SUBTITLES_cfg										d3dConf;								//  2014/12/16
				 }														subtitles;

				 //  2015/08/01
				 struct													{
					 HWND												hTool_offlineRes;
				 }														offlineRes;
				 
				 //  2013/11/18
				 struct													{
					 HWND												hWnd_remoteAssist;
					 int												iTaskId;
				 }														remoteAssist;

				 //  2014/09/04
				 struct													{
					 unsigned  int										uiTranNo;
				 }														selectRemoteVideo;

				 //  2012/04/23
				 TALKER_shadow_mgrMem									shadows[8];
				 				
				 //  2014/05/30
				 unsigned  char											ucbNotAutoStopViewing;					//  2012/04/25			
				 
				 //  手工设置查看远程视频的指令.
				 VW_rule_messengerCmd									vwRuleCmd_manual;						//  2013/02/13
		 
				 //
				 unsigned  char											ucbShowGpsData;							//  2012/05/07
				 
				 //				 
				 VW_rule_messengerCmd									vwRuleCmd;
				 
				 //  2012/04/25
				 TALKER_dynBmp											talkerDynBmps[CONST_vwRuleMessengerCmd_dynBmps];					//  2014/09/03
				
				 				 
				 //  2015/08/04
				 struct													{
					 //
					 DWORD												dwLastModifiedTickCnt_taskStatus;				
					 //
					 unsigned  short 									usTimes_noFileTask;

				 }														fileTaskInfo;
				 
				 //  2015/08/03
				 struct													{				
					 //
					 PROC_offlineRes_mem								mems[10];
				 }														procOfflineRes_mgr;			//  对应idInfo_res的窗口要负责各talker的资源读写请求的完成，然后还需要把结果告诉各talker

				 //
				 //  2015/07/30
				 //unsigned  char											ucbNotAutoHide_instantAssistant;

				 //
				 struct													{							//  2017/01/10
					unsigned  char										ucbOn;
				 }														quickToRetrieveImg;

				 
				 //  2017/06/25
				 struct													{
					 //
					 GRP_confCtrl										grpConfCtrl;
				 }														confCtrl;

				 //  2017/09/19
				 struct													{
					 //
					 BgWall_cfg											bgWallCfg;						//  2017/11/02
					 //
					 HWND												hTool_cfg;						//  2017/11/02
					 //
					 HWND												hBgWall;
					 int												iWndContentType_hBgWall;
				 }														bgWall;
				 
				 //
#if  0
				 struct													{
					 HWND												hWnd_dlgVideos;
				 }														secondView;
#endif

}		 TALKER_shadow_mgr;


//
typedef  struct  __talkerShadow_t				{
				 HWND							hMgr;
				 //
				 struct							{
					 DWORD						dwTickCnt_lastRecvd;

			 
					 //
					 POINT						point_xy;
					 POINT						point;

					 DWORD						dwTickCnt_lastRefreshed;
				 }								viewGps;

				 //
				 HWND							hEnlargedWnd;


}		 TALKER_shadow;


//
#ifdef  __WINCE__
		#define		MACRO_CDlgTalk		CDlgTalk_ce
#else
		#define		MACRO_CDlgTalk		CDlgTalk
#endif

//
typedef  struct  __param_dlgVideos_t		{
					 //
					 int				iTaskId;
					 //  unsigned  int		uiTaskType;				//  2009/08/05
					 QY_MESSENGER_ID	idInfo_sender;				//  2009/10/13
					 unsigned  int		uiTranNo_openAvDev;			//  2009/10/13

					 BOOL				bMeImage;
					 CAP_IMAGES		*	pImgs;
					 int				iIndex_capImage;

					 unsigned  short	usCnt_monPics_row;
					 unsigned  short	usCnt_monPics_col;
					 unsigned  int		uiInitW;
					 unsigned  int		uiInitH;

					 BOOL				bScrollBarEnabled;
				
					 BOOL				bVideoConference;

					 BOOL				bRemoteAssist;
				
					 BOOL				bInstantAssistant;			//  2010/12/24

					 BOOL				bMediaControl;
					 int				iIndex_capBmp;
					 int				iIndex_capAudio;

					 BOOL				bFreeCapImages;				//  2010/12/23
					 
					 //
					 //HWND				hParent;					//  2010/12/25

					 //
					 BOOL				bLocalAvWnd;				//  2011/03/13

					 //  2014/10/11
					 BOOL				bBgWallImage;
					 QY_MESSENGER_ID	idInfo_sel_bgWall;

					 //
					BOOL				bEnlageFromDynBmps;			//  2018/07/07

}		 PARAM_dlgVideos;

//
//
typedef  struct  __param_taskInfo_t				{
				 QMC_TASK_INFO				*  pTaskInfo;
				 QMC_taskData_conf			*  pTaskData;
}		 PARAM_task_info;






#ifndef  __WINCE__
CQyString  getCellId(  void  *  pIHTMLElement  );
CQyString  getCellText(  void  *  pIHTMLElement  );
CQyString  getIElemHtml(  void  *  pIHTMLElement  );
#endif

//  int  getlRowIndex(  void  *  p0,  PARAM_PROC_ROW  *  pParam,  void  *  pIHTMLTableRow  );
//  int  modifyRow(  void  *  p0,  PARAM_PROC_ROW  *  pParam,  void  *  pIHTMLTableRow  );

int  doDoc(  void  *  pIHtmlDocument2,  PF_commonHandler  pf_doTable,  void  *  p0,  void  *  pParam  );
//
int  doTable_insertRow_once(  void  *  p0,  PARAM_PROC_ROW  *  pParam,  void  *  pIHTMLTable  );
int  doTable_byRowId(  void  *  p0,  PARAM_PROC_ROW  *  pParam,  void  *  pIHTMLTable  );
int  doTable_getLastRowIdStr(  void  *  p0,  PARAM_PROC_ROW  *  pParam,  void  *  pIHTMLTable  );
int  doTable_print(  void  *  p0,  void  *  p1,  void  *  pIHTMLTable  );
//
int  doRow(  void  *  pIHTMLTableRow,  PF_commonHandler  pf,  void  *  p0  );
//

#ifndef  __WINCE__
__declspec(dllexport) CQyString		getNextRowIdStr(  HWND  hDlgTalk  );  
#endif

//
int  chkResources(  HWND  hDlgTalk,  BOOL  bFreeCapImages  );

//
int refreshMosaicTransStatus(HWND  hDlg, DLG_TALK_var* pDlgMgrVar);

//
int  dlgTalk_chkAutoAnswer(  HWND hDlgTalk  );


//  2013/02/15
__declspec(  dllexport  )  int  chkTalkerRules(  HWND  hDlgTalk,  void  *  pDLG_TALK_var  );

//
__declspec(  dllexport  )  int  chkToViewDynBmp(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  int  talkerRuleIndex,  BOOL  bNeedProgress,  BOOL  *  pbImgRestarted  );

//
int  confStarter_chkToViewDynBmp(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  DYN_BMP_rule  *  pRuleDynBmp,  TALKER_dynBmp		*	pObjElem,  BOOL  bNeedProgress,  BOOL  *  pbImgRestarted  );
//
__declspec(  dllexport  )  int  confMem_procReq_transferAvInfo(  HWND  hWnd_task,  int  iIndex_sharedObj_localAv,  MIS_MSGU  *  pMsg  );



//  2014/09/05
__declspec(  dllexport  ) int  chkIfDynBmpRuleUnmatched(  HWND  hDlgTalk,  void  *  pDLG_TALK_var, DYN_BMP_rule  *  pRuleDynBmp,  TALKER_dynBmp  *	pObjElem  );
__declspec(  dllexport  ) BOOL  bActive_talkerDynBmp(  time_t  tNow,  CAP_IMAGES  *  pImgs,  TALKER_dynBmp  *  pTalkerDynBmp  );
__declspec(  dllexport  ) int  sndViewDynBmpReq(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  BOOL  bNeedProgress,  BOOL  *  pbImgRestarted,  TALKER_dynBmp		*	pObjElem,  QY_MESSENGER_ID  *  p_content_idInfo_logicalPeer  );
__declspec(  dllexport  ) int  tryToFindSameRule_sndViewDynBmpReq(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  BOOL  bNeedProgress,  BOOL  *  pbImgRestarted,  int  talkerRuleIndex  );

//
__declspec(  dllexport  )  BOOL  bTaskImgActive(  HWND  hDlgTalk,  DLG_TALK_var  *  pm_var,  MIS_MSG_TASK  *  pMsgTask  );
 



__declspec(  dllexport  )  int  dlgTalk_re_acceptTask(  HWND  hDlgTalk_mgr,  int  iTaskId  );
//
__declspec(  dllexport  )  int  dlgTalk_doCmd_joinInBgWall(  HWND  hTalkerMgr  );
__declspec(  dllexport  )  BOOL  canJoinInBgWall(  HWND  hTalkerMgr,  void  *  pDLG_TALK_var  );


//
//  2014/02/10
__declspec(  dllexport  )  int  dlgTalk_loadGrpMems(  HWND  hCurTalk,  DLG_TALK_var  *  pCurTalkVar,  LPCTSTR  tFilter  );	//  2014/02/10

//
__declspec(  dllexport  )  int  refreshGrpMemListStatus(  HWND  hCurTalk  );



//
__declspec(  dllexport  )  int  dlgTalk_qPostMsg(  HWND  hDlgTalk,  Q_ELEM_T  *  pQElem,  unsigned  int  size  );

__declspec(  dllexport  )  int  dlgTalk_findWndForPrompt(  HWND  hDlgTalk_mgr,  void  *  pDLG_TALK_var,  HWND  *  phWnd_forPrompt,  int  *  piWndContentType_forPrompt  );

//
__declspec(  dllexport  )  int  dlgTalk_chkShadows(  HWND  hDlgTalk,  DLG_TALK_var  *  pDlgTalkVar_mgr  );
 __declspec(  dllexport  ) int  dlgTalk_doApplyForTalkerShadow_qmc(  HWND  hDlg,  MIS_MSG_applyForTalkerShadow_qmc  *  pMsg_applyForTalkerShadow_qmc  );

//
int  activateWnd(  HWND  hDlgTalk,  DLG_TALK_var  &  m_var  );

//
__declspec(dllexport) BOOL  dlgTalk_bSetDlgInfo(  HWND  hDlgTalk,  DLG_TALK_var  &  m_var,  MSGR_ADDR  *  pAddr,  GENERIC_Q  *  pTmpGrpMemQ,  int  iTalkUsage,  int  iTalkerSubType,  BOOL  bNeedNotShowWnd,  HWND  hFore  );

//
int  dlgTalk_cancelTasks(  HWND  hDlg,  void  *  pDLG_TALK_var,  int  iTaskId,  BOOL  bAutoCancel  );
int  dlgTalk_toChkTask(  HWND  hDlg,  DLG_TALK_var  &m_var,  QY_WMBUF_COMM  *  pComm  );

int  dlgTalk_displayAvStatus(  HWND  hDlg,  DLG_TALK_var  &  m_var,  int  iTaskId,  int  iStatus,  LPCTSTR  statusDesc  );

//
int  dlgTalk_make_capStuff(  HWND  hDlgTalk,  DLG_TALK_var  *  pm_var  );

//
bool  dlgTalk_bConfInitiator(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo);
bool  dlgTalk_bIAmConfInitiator(HWND  hDlgTalk);

bool  dlgTalk_bConfCompere(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo);
bool  dlgTalk_bIAmConfCompere(HWND  hDlgTalk);

//
QY_MESSENGER_ID  dlgTalk_get_idInfo_starter(HWND  hDlgTalk);
QY_MESSENGER_ID  unused_dlgTalk_get_idInfo_compere(HWND  hDlgTalk);


//
int  dlgTalk_OnInitDialog(  HWND  hDlgTalk,  void  *  pDLG_TALK_var  );
int  dlgTalk_OnDestroy(  HWND  hDlg,  void  *  pDLG_TALK_var  );
int  dlgTalk_OnQyComm(  HWND  hDlg,  void  *  pDLG_TALK_var,  WPARAM  wParam,  LPARAM  lParam  );
int  dlgTalk_OnQyPostComm(  HWND  pDlg,  void  *  pDLG_TALK_var,  WPARAM  wParam,  LPARAM  lParam  );

//
int  dlgTalk_closeTask(  HWND  hDlgTalk,  int  iTaskId  );
int  dlgTalk_closeTaskAv(  HWND  hDlgTalk,  DLG_TALK_var  &  m_var  );


//
__declspec(  dllexport  )  int  dlgTalk_freeCapImageBySth_bgWall(  HWND  hDlgTalk,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo  );
//
__declspec(  dllexport  )  int  dlgTalk_freeCapImageBySth(  HWND  hDlgTalk,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo  );


//
int  dlgTalk_init_respInfo(  HWND  hDlgTalk_mgr,  DLG_TALK_var  *  pMgrVar,  unsigned  char  ucbVideoConference  );



//
__declspec(  dllexport  )  int  dlgTalk_calculateLayout(  HWND  hCurTalk,  DLG_TALK_var  *  pCurVar,  RECT  *  pCliRc,  DLG_talk_layout  *  pLayout  );


//
int  confCli_doCmd_startAvCall(  HWND  hParent,  HWND  hCurTalk,  int  level,  BOOL  b3D,  unsigned  char  ucbAvConsole,  PARAM_startAvCall  *  pParam  );

//
int  doCmd_startShareScreen(  QY_MC  *  pQyMc,  HWND  hDlg,  DLG_TALK_var  *  pm_var  );

/*
#define CONST_FILE_FILTER_TEXT \
    TEXT("Video Files (*.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v)\0*.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v\0")\
    TEXT("Audio files (*.wav; *.mpa; *.mp2; *.mp3; *.au; *.aif; *.aiff; *.snd)\0*.wav; *.mpa; *.mp2; *.mp3; *.au; *.aif; *.aiff; *.snd\0")\
    TEXT("MIDI Files (*.mid, *.midi, *.rmi)\0*.mid; *.midi; *.rmi\0") \
    TEXT("Image Files (*.jpg, *.bmp, *.gif, *.tga)\0*.jpg; *.bmp; *.gif; *.tga\0") \
    TEXT("All Files (*.*)\0*.*;\0\0")
*/
#define CONST_FILE_FILTER_TEXT \
    TEXT("Video Files ( *.wmv; *.asf)\0 *.wmv; *.asf \0")\
    TEXT("All Files (*.*)\0*.*;\0\0")

#define CONST_FILE_FILTER_allFiles \
    TEXT("All Files (*.*)\0*.*;\0\0")


int  doCmd_startShareMediaFile(  QY_MC  *  pQyMc,  HWND  hDlg,  int  iWndContentType,  int  level,  LPCTSTR  pathCStr,  int  *piIndex_sharedObj,  int  *piIndex_sharedObjUsr  );



//  2011/12/25
//int  doCmd_startShareMediaDevice(  HWND  hDlg,  void  *  pDLG_TALK_var,  int  level,  void  **  ppCapStuff  );
int  doCmd_startShareMediaDevice(  QY_MC  *  pQyMc,  HWND  hDlg,  void  *  pDLG_TALK_var,  unsigned  int  uiSubCapType,  int  level,  void  **  ppCapStuff  );


//
//  int  sizeAllControls_dlgTalk(  HWND  hDlg,  DLG_TALK_var  &  m_var,  RECT  *  pRect  );

//  DLG_TALK_var  *  getDlgTalkVar(  HWND  hDlgTalk  );

//
BOOL  bAutoAccepted_avCall(  HWND  hDlgTalk,  QY_imObj_rules  *  pRules,  unsigned  int  uiTaskType  );


//
int  tmpHandler_showMsg(  void  *  pDlgTalkParam,  void  *  p1, void  *  pMsgParam  );

//
int  tmpHandler_showMsg_task_taskInteractionReq(void* hDlgTalkParam, DLG_TALK_var& m_var, void* p1, void* pMsgParam,
	IM_CONTENTU* pContent);
int  tmpHandler_showMsg_task_confKey(void* hDlgTalkParam, DLG_TALK_var& m_var, void* p1, void* pMsgParam,
	IM_CONTENTU* pContent);
int  tmpHandler_showMsg_task_statusConfLayoutParam(void* hDlgTalkParam, DLG_TALK_var& m_var, void* p1, void* pMsgParam,
	IM_CONTENTU* pContent);
int  doSelIpc_local(IpcParam* pIpcParam, HWND  hTalk_mgr);
int  dlgTalk_proc_recvd_confState(HWND  hDlgTalk_mgr, DLG_TALK_var* pMgrVar, MIS_MSG_TASK* pMsgTask, CONF_state* pConfState);
int  dlgTalk_proc_recvd_confCtrlState(HWND  hDlgTalk_mgr, DLG_TALK_var* pMgrVar, MIS_MSG_TASK* pMsgTask, CONF_ctrl_state* pConfCtrlState);
int  tmpHandler_showMsg_displayTask(HWND  hDlgTalk, DLG_TALK_var* pDlgTalkVar, PARAM_PROC_ROW* pParam, MIS_MSGU* pMsg);


//
 int  removeFrom_requestingMems_from(  DLG_TALK_videoConference  *  pVc,  QY_MESSENGER_ID  *  pIdInfo  );

 //
 int  confOthers_sendStreamInfo();



//
int  confOthers_requestToSpeak(  HWND  hDlgTalk,  int  index_sharedObj,  RES_obj_simple  *  pRos_toStop,  BOOL  bRequestToSpeak  );

int  confMgr_requestToSpeak(  HWND  hDlgTalk,  QY_MESSENGER_ID  *  pIdInfo_speaker,  BOOL  bRequestToSpeak  );

//
int  confMgr_permitToSpeak(  HWND  hDlgTalk_mgr,  QY_MESSENGER_ID  *  pIdInfo_speaker,  BOOL  bPermitToSpeak  );
//
int  confCompere_pleaseSpeak(HWND  hDlgTalk_mgr, QY_MESSENGER_ID* pIdInfo_speaker, BOOL  bSpeak);

//
__declspec(  dllexport  )  int  requestToControlDesktop_yz(  HWND  hDlgTalk_mgr,  QY_MESSENGER_ID  *  pIdInfo_speaker,  BOOL  bStart  );

//
int  requestToRefreshActiveMems_videoConferenceOthers(  HWND  hDlgTalk  );

//
int  getConfKey(  HWND  hDlgTalk,  int  iTaskId,  CONF_KEY  *  pStatus,  LPCTSTR  hint  );

//
//int  sendConfKey(  HWND  hDlgTalk,  QY_MESSENGER_ID    idInfo_to,  LPCTSTR  hint  );

//
 int  sendStatusConfLayoutParam(HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint);
//
int  getStatusConfLayoutParam(HWND  hDlgTalk, int  iTaskId, StatusConfLayoutParam* pStatus, LPCTSTR  hint);



//
int  sendConfLayout(unsigned char ucbResp,  unsigned  short  usLayoutType, unsigned  short  usOp, ConfLayoutParam* pParam, QY_MESSENGER_ID  idInfo_imGrp_related, QY_MESSENGER_ID  idInfo_requester, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint);

__declspec(dllexport) int  sendConfNvrInfo(NvrInfo* pNvrInfo, unsigned  char  ucbResp, QY_MESSENGER_ID idInfo_imGrp_related, QY_MESSENGER_ID idInfo_requester, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint);
//
int  sendConfCtrlState(HWND  hDlgTalk_mgr, QY_MESSENGER_ID  idInfo_to, LPCTSTR  hint);


//
//int  sendConfReq(  void  *  p,  HWND  hDlgTalk,  QY_MESSENGER_ID  idInfo_conf,  unsigned  short  usOp,  unsigned  short  usAvLevel,  int  conf_iFourcc,  unsigned  short  conf_usMaxSpeakers  );
int  sendConfReq(void* p, HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_conf, unsigned  short  usOp, unsigned  short  usAvLevel, unsigned  short  conf_usMaxSpeakers,TALKER_policy * pTalkerPolicy, CONF_hg_info * pHgInfo);




//
int  set_doConf(  CONF_req  *  pConfReq,  LPCTSTR  hint  ); 
int  clear_doConf(  QY_MESSENGER_ID  idInfo_conf,  LPCTSTR  hint  );

//  
int  refreshTaskAv_videoConferenceStarter(  HWND    hDlgTalk,  void  *  pMsgTask  );
int  refreshTaskAv_videoConferenceOthers(  HWND  hDlg  );

//
int refreshConfLayout(int index_taskInfo);
int refreshConfStreamInfos(int  iTaskId);

//
int clearSpeakState(  LPCTSTR  hint  );

//
int  dlgTalk_requestToSpeak(  HWND  hDlgTalk_mgr,  BOOL  bEnable,  bool  bSaveState  =  true  );
int  dlgTalk_requestToOp(HWND  hDlgTalk_mgr, int op, int  bSaveState = true);

//
#ifdef  __DEBUG__
 int  printDlgTalkVideoConference(  DLG_TALK_videoConference  *  p  );
#endif


 //  2014/09/25
 __declspec(  dllexport  )  BOOL  confStarter_bTaskInBgWall(  HWND  hDlgTalk,  void  *  pDLG_talk_var,  int  iTaskId,  QIS_res_obj  *  pDynBmp_o,  unsigned  short  *  pusIndex_active  );
 __declspec(  dllexport  )  BOOL  confStarter_bMeOnBgWall(  HWND  hDlgTalk,  void  *  pDLG_talk_var,  QIS_res_obj  *  pDynBmp_o,  unsigned  short  *  pusIndex_active  );


 __declspec(  dllexport  )  int  confMem_sndRetrieveDynBmpsRespToMsgr(  HWND  hDlgTalk,  void  *  pDLG_talk_var,  MIS_MSGU  *  pMsg  );
 __declspec(  dllexport  )  int  confStarter_procRetrieveDynBmpsResp(  HWND  hDlgTalk,  void  *  pDLG_talk_var,  MIS_MSGU  *  pMsg  );

 //
 __declspec(  dllexport  )  int  confStarter_stopConfWall(  HWND  hDlgTalk,  DLG_TALK_var  *  pm_var  );
 


 //
 int  send_confState_retrieveAll_req(  HWND  hDlgTalk_mgr,  DLG_TALK_var  *  pMgrVar,  LPCTSTR  hint  );


//
int  tmpMakeHtmlStr(  QY_MC  *  pQyMc,  MIS_MSGU  *  pMsg,  int  iStatus,  BOOL  bIncludeUrl,  LPCTSTR  rowIdStr,  LPCTSTR  paramStrBuf,  QY_MESSENGER_ID  *  pIdInfo_talker,  TCHAR  *  tBuf,  unsigned  int  cnt  );

//
int  dlgTalk_procTask_htmlEdit(  HWND  hParent,  int  iWndContentType_hParent,  LPCTSTR  url  );


//  
int  dlgTalk_procTask1(  HWND  hCurDlgTalk,  int  iTaskId_param,  unsigned  short  usOp_param,  LPCTSTR  paramStrBuf,  PARAM_dlgTalk_procTask  *  pParam  );
 __declspec(  dllexport  )  int  dlgTalk_procCmd(  HWND  hCurTalk,  int  wID,  int  iTaskId,  unsigned  short  usOp,  LPCTSTR  paramStrBuf,  PARAM_dlgTalk_procTask  *  pParam  );

//
__declspec(  dllexport  )  int  dlgTalk_drawItem_bgWall(   HWND  hCurTalk,  void  *  pDLG_TALK_var,  HDC  hDc  );
__declspec(  dllexport  )  int  dlgTalk_getBgWallMemInfo(  HWND  hCurTalk,  void  *  pDLG_TALK_var,  int  index_rect,  QY_MESSENGER_ID  *  pIdInfo_o  );

//  2014/09/23
int  makeSlaveStream(  QY_MC  *  pQyMc,  HWND  hDlg,  int  iIndex_sharedObj_master,  int  level,  int  iFourcc_suggested  );

//
 extern "C" DWORD WINAPI mcThreadProc_readRtt( LPVOID lpParameter );


//
int  dlgTalk_gpsMsgArrive(  void  *  pProcInfoParam,  int  iIndex_player_gps,  HWND  hWnd,  DLG_TALK_var  &  m_var,  BOOL  bForce_displayAllFrames,  MIS_MSGU  *  pMsg  );


BOOL  setMsgToolPos(  HWND  hCurTalker  );
//
 __declspec(  dllexport  )  int  refreshTalkToInfo(  HWND  hCurTalk  );
__declspec(  dllexport  )  int  refreshTalkToInfo_mgr(  HWND  hDlgTalk  );
 
 __declspec(dllexport) int  dlgTalk_procTask_display_op(  HWND  hDlgTalk,  int  iTaskId,  unsigned  short  usOp,  MIS_MSG_TASK  *  pMsgTask,  IM_TASK_RCD  &  rcd,  int  iStatus_old,  int  iStatus,  LPCTSTR  paramStrBuf  );
  __declspec(dllexport) int  dlgTalk_procTask_display_op_mgr(  HWND  hDlgTalk_mgr,  int  iTaskId,  unsigned  short  usOp,  MIS_MSG_TASK  *  pMsgTask,  IM_TASK_RCD  &  rcd,  int  iStatus_old,  int  iStatus,  LPCTSTR  paramStrBuf  );



//
BOOL  setRemotePtzPos(  HWND  hCurTalker  );
BOOL  setSubtitlesPos_talk(  HWND  hCurTalker  );
BOOL  setOfflineResPos_talk(  HWND  hCurTalker  );
//  
int  dlgTalk_refresh_usLayoutType_cur(  HWND  hDlgTalk,  BOOL  *  pbModified  );

//
int  get_idInfo_peer_yz(  DLG_TALK_var  *  pMgrVar,  QY_MESSENGER_ID  *  pIdInfo_peer  );
BOOL  bStarted_remoteAssist(  TALKER_shadow_mgr  *  pShadowMgr,  QY_MESSENGER_ID  *  pIdInfo  );



//
__declspec(  dllexport  )  BOOL  dlgTalk_bShowMsgBox1(  HWND  hCurTalker  );
//
BOOL  dlgTalk_bMsgBoxShown(  HWND  hCurTalker  );
BOOL  dlgTalk_bPtzShown(  HWND  hCurTalker  );
BOOL  dlgTalk_bSubtitlesShown(  HWND  hCurTalker  );
BOOL  dlgTalk_bShowBgWall(  HWND  hCurTalker  );
BOOL  dlgTalk_bOfflineResShown(  HWND  hCurTalker  );
//
BOOL  dlgTalk_bShowPeerTool(  HWND  hCurTalker  );


//  2014/07/14
__declspec(  dllexport  ) int  dlgTalk_set_newMsgArrives(  HWND  hDlgTalk,  DLG_TALK_var  *  pm_var,  BOOL  bOn  );
__declspec(  dllexport  ) BOOL  dlgTalk_bNewMsgArrives(  HWND  hDlgTalk,  DLG_TALK_var  *  pm_var  );


//
void  *  TALKER_shadow_new(  BOOL  bMgr  );
void  TALKER_shadow_free(  BOOL  bMgr,  void  *  pShadowInfo  );


//
__declspec(  dllexport  ) int  dlgTalk_freeCapImageBySth_mgr(  HWND  hDlgTalk,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo  );
 

//
__declspec(  dllexport  )  int  closeInstantAssistant_mgr(  HWND  hDlgTalk  );


 //
 int  dlgTalk_freeCapImageByTaskId_me_mgr(  HWND    hDlgTalk,  int  idc,  int  iTaskId  );
 __declspec(  dllexport  )  int  dlgTalk_freeCapImageBySth_bgWall_mgr(  HWND  hDlgTalk,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo  );
 //
 int  dlgTalk_freeCapImages_bgWall_mgr(  HWND    hDlgTalk,  int  idc  );

 //
 void  chooseAvDevice_mgr(  void  *  pCapParam,  HWND  hDlgTalk,  HWND  hWndStatus,  int  iMenuId  );

 BOOL  InvalidateRect_mgr(  HWND hDlgTalk, int  idc,  CONST RECT *lpRect, BOOL bErase  );
 __declspec(  dllexport  )  int  askToRefreshLayout_mgr(  HWND  hDlgTalk  );
 __declspec(  dllexport  )  int  askToRefreshSize_mgr(  HWND  hDlgTalk  );
 //
 __declspec(dllexport)  int  talk_refreshLayout_mgr(HWND  hDlgTalk_mgr);

 //
 __declspec(  dllexport  )  int  resetTalkerList_mgr(  HWND  hDlgTalk_mgr  );

 //
 int  fillTalkerList_func_mgr(  HWND  hDlgTalk_mgr,  HWND  hTool,  void  *  pVIDEO_CONFERENCE_STATUS,  int  idcList  );

 //
 __declspec(  dllexport  )  int  refreshTalkerList(  HWND  hDlgTalk  );

 

 __declspec(  dllexport  )  int  getnGrpMems_isCli(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_ID  *  pIdInfo_grp  );
__declspec(  dllexport  )   int  enumGrpMems_isCli(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_ID  *  pIdInfo_grp,  PF_commonHandler  pf,  void  *  p0,  void  *  p1  );

//
//
int getPath_fileServer(  QY_MC  *  pQyMc,  QY_MESSENGER_ID  *  pIdInfo_send,  QY_MESSENGER_ID  *  pIdInfo_recv,  TCHAR  *	pFilePath,  int  len  );
int  getFilePrefix_fileServer(  time_t  t,  char  *  filePrefix,  unsigned  int  cnt  );


//
int  getAvBtnStatus(  DLG_TALK_var  *  pMgrVar  );


//
__declspec(  dllexport  )  int  initTalkerThread(  MC_VAR_common  *  pProcInfo,  HWND  hDlgTalk_mgr,  DLG_TALK_var  *  pMgrVar,  TALKER_threadProcInfo  *  p  );
__declspec(  dllexport  )  int  exitTalkerThread(  MC_VAR_common  *  pProcInfo,  TALKER_threadProcInfo	*	p  );

//
int  syncToGetTaskInfo(  DLG_TALK_var  *  pm_var,  CQySyncCnt  &  syncCnt,  PARAM_task_info  &  param  );

//
__declspec(  dllexport  )  void  dlgTalk_OnIsCmd_noSync(  HWND  m_hWnd,  DLG_TALK_var  *  pm_var,  UINT  iMenuId,  QY_wmBuf_command  *  pWmBuf  );

//
__declspec(dllexport) int  dlgTalk_shareMediaDevice(HWND  hDlg, int  iMenuId, unsigned  int  uiSubCapType,  LPCTSTR  dev_sel  );

//
CAP_images* getLayoutPeerImages_forD3d(DLG_TALK_var* pMgrVar);
CAP_images* getLayoutOtherImages_forD3d(DLG_TALK_var* pMgrVar);

//
int  conf_chkAvDev(HWND  hTalk, void  *  pDLG_TALK_var);




#endif  //  }


