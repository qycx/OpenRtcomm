


#ifndef  __dlgTalkPublic_h__
#define  __dlgTalkPublic_h__  //  {

//
#include	"qyTimestamp.h"		//  2017/10/17
#include	"d3dWallMemIa.h"
#include	"qmcSharedObj.h"
#include	"ctxQmc.h"


//
typedef  struct  __talkerTaskInfo_t								{

						struct									{
							BOOL								bTaskExists1;							//  2014/11/30
							unsigned  char						ucbStarter;
							unsigned  char						ucbVideoConference;						//  2010/08/31
							//
							int									iTaskId;

							//
							unsigned  char						ucb2Streams;

							//
							//BITMAPINFOHEADER					bih_mosaic_video;
							struct								{										//  2015/10/21
								BITMAPINFOHEADER				bih;
								BOOL							bSupported_pktResType_sharedTex2;
								unsigned  short					usMaxFps_toShareBmp;					//  2015/10/21
								//
								unsigned  int					uiTranNo_openAvDev;						//  2017/09/02
								//
							}									mosaicVideo;


							//
							//  BITMAPINFOHEADER					bih_mosaic_resource;
							struct								{										//  2015/10/21
								BITMAPINFOHEADER				bih;
								BOOL							bSupported_pktResType_sharedTex2;
								unsigned  short					usMaxFps_toShareBmp;					//  2015/10/21
								//
								unsigned  int					uiTranNo_openAvDev;						//  2017/09/02
								//
							}									mosaicResource;
							
						}										av;

						struct 									{					
							BOOL								bExists_resource;
							//
							int									nScreens;
							int									nMediaFiles;
							int									iW_screen;
							int									iH_screen;
						}										recvdResource;
					
						struct									{
							BOOL								bExists_resource1;
							//
							int									nScreens;
							int									nMediaFiles;
							//
						}										sendingResource;

}		 TALKER_task_info;


//  2016/02/26
typedef  struct  __taskListMem_t								{
				 int											iTaskId;
				 unsigned  int									uiTaskType;
				 QY_MESSENGER_ID								idInfo_sender;
				 int											iStatus;
				 //
				 BOOL											bWaitingTo_beRe_accepted;
}		 TASK_list_mem;

//
typedef  struct  __talkerTaskList_t								{

				 //
				 DWORD											dwModifiedTickCnt_taskList;									//  2014/11/29

				 //
				 unsigned  short								usCnt;
				 TASK_list_mem									mems[32];
}		 TALKER_task_list;



//  2013/02/26
typedef  struct  __dlgTalkLayout_t								{
		
				 //
				 unsigned  short								usCnt_row;					//  
				 unsigned  short								usCnt_col;					//  

				 //
				 unsigned  int									uiW_pic;
				 unsigned  int									uiH_pic;

				 //				
				 unsigned  short								usLayoutType_cur;			//  2010/12/29

				 //
				 unsigned  char									ucbExists_localScreenSharing;			//  2015/11/14

				//
				unsigned  char									ucbShowDlgDesc;
				unsigned  char									ucbShowPeerDesc;
				unsigned  char									ucbShowMeDesc;
				unsigned  char									ucbShowOtherDesc;
				unsigned  char									ucbShow_peer_tool;			//  2017/08/21

				//
				int												iH_dlgDesc;
				int												iW_memberList;
				int												iW_taskList;
				int												iW_ptz;
				int												iW_subtitles;				//  2013/04/05
				int												iW_offlineRes;				//  2015/08/01
				//
				int												iW_peerInfo;				//  2017/08/21
				int												iH_staticPeerInfo;
				int												iH_peerInfo;
				int												iH_shareScreen;

				//
				int												iW_meDesc;					//  2008/03/27
				int												iH_meDesc;
				
				//
#if  0
				unsigned  char									ucbShowBgWall_starter;		//  2014/10/01
				unsigned  char									ucbShowBgWall_confMem;		//  2014/10/08
				unsigned  char									ucbNeverJoinInBgWall;		//  2014/10/08
#endif
				//  2017/11/03
				unsigned  char									ucbShowBgWall;
				//
				BG_wall_layout_cfg								bgWallLayoutCfg;			//  2017/11/03
				//
				BG_wall_layout									bgWallLayout;				//  2014/10/01
				//unsigned  short									usPollingIntervalInS1;		//  2014/10/06

}		 DLG_talk_layout;


//  2014/12/09
typedef  struct  __param_dlgTalk_procTask_t						{
				 BOOL											av_autoAnswer_av_task_bTaskNeedAutoAnswered;
				 //
				 BOOL											bManualCmd;			//  2017/02/12
				 HWND											hParent;
}		 PARAM_dlgTalk_procTask;



//  2014/12/23
typedef  struct  __subtitleMsg_t								{
				 DWORD											dwTickCnt_recvd;
				 QY_MESSENGER_ID								idInfo_sender;
				 TCHAR											talkerDesc[32];
				 TCHAR											tBuf[128];
}		 SUBTITLE_msg;

typedef  struct  __subtitleMsgs_t								{
				 SUBTITLE_msg									mems[2];		//  5  //  2016/06/08

				 //  2015/02/16
				 SUBTITLE_msg									notifications[3];
				 BOOL											bExists_notifications;

				 //
				 DWORD											dwModifiedTickCnt_any_start;
				 DWORD											dwModifiedTickCnt_any_end;

}		 SUBTITLE_msgs;



//
typedef  struct  __msgList_ia_t									{
				 DWORD											dwModifiedTickCnt_msgList;
}		 MSG_list_ia;


//  2016/02/28
typedef  struct  __task_ia_t									{
				 DWORD											dwModifiedTickCnt_taskList;
				 //
				 int											iTaskId;
}		 TASK_ia;


//  2015/11/15				
//
typedef  struct													{
					
					//
					//DWORD										dwModifiedTickCnt_taskInfo;
					QY_timestamp								ts_taskInfo;							//  2017/10/17

					//
					DLG_talk_layout								layout;
					//
					//DWORD										dwModifiedTickCnt_layout;				//  2014/11/27
					QY_timestamp								ts_layout;								//  2017/10/17
					
					//
					//ConfLayoutParam								confLayoutParam;						//  2023/10/13

					//
					CAP_image									bgImage;								//  2013/10/05
					DWORD										dwModifiedTickCnt_bgImage;

					//
					CAP_IMAGES									peerImages;
					//
					CAP_IMAGES									meImages;								//  2013/08/30
					//
					CAP_IMAGES									otherImages;

					//  2014/11/01
					//DWORD										dwModifiedTickCnt_mosaic;
					QY_timestamp								ts_mosaic;

					//
					DWORD										dwModifiedTickCnt_subtitlesCfg;			//  2014/12/16

					//  2014/12/23
					DWORD										dwModifiedTickCnt_subtitleMsgs;			//  2014/12/23

					
					//
					D3D_wallMem_ia								cfgIa;

					//  2016/02/26
					TALKER_task_list							taskList;

				
}		D3D_talkerData_cfg;






//
int  calc_me_bgWall_rect(  DLG_talk_layout  *  pLayout,  int  iW_wallMem,  int  iH_wallMem,  int  *  piW_meDesc,  int  *  piH_meDesc,  int  *  piW_bgWall,  int  *  piH_bgWall  );
int  calc_other_rect(DLG_talk_layout* pLayout, float fZoomFactor, int  iW_wallMem, int  iH_wallMem, int* piW_otherDesc, int* piH_otherDesc);

//
int  snprintRoute(  ROUTE_sendLocalAv  *  pRoute,  TCHAR  *  tOutput,  unsigned  int  cnt  );
int  snprintCapImages(  LPCTSTR  hint,  CAP_images_head  *  pImgsHead,  CAP_image  *  pImgMems, int  uiSize_pImgMem,  unsigned  int  uiMaxCnt_imgMems,  TCHAR  *  tOutput,  unsigned int  cnt  );

//
 D3D_talkerData_cfg  *  get_D3D_talkerData_cfg(  MC_VAR_common  *  pProcInfo,  int  iIndex_talkerInfo,  CQySyncCnt  *  pSyncCnt  );
 //
 void  *  getQmcObjVarDataByIndex(  MC_VAR_common  *  pProcInfo,  int  iIndex_objVarInfo,  CQySyncCnt  *  pSyncCnt,  int  objVarDataType,  LPCTSTR  hint  );


#endif  //  }





