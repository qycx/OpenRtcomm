

#ifndef  __isCliD3dPublic_h__
#define  __isCliD3dPublic_h__	//  {

//
#include	"qisD3dDefs_open.h"
#include	"qisD3dDefs.h"

//
#include	"dlgTalkPublic.h"


//  2016/09/08
#include	"qmcStruct_defs.h"
//
#include	"dyn_isCliD3d_public.h"


//  2013/09/06
#define		CONST_d3dMenu_null										0
#define		CONST_d3dMenu_welcome									1
//
#define		CONST_d3dMenu_talker_start								10
#define		CONST_d3dMenu_talker_start_wait							11					
#define		CONST_d3dMenu_talker_av									12

//  2014/02/04
#define		CONST_d3dMenu_talker_msgGrp								20


//  2016/02/25
#define		CONST_d3dMenu_dynBmp									100

//
#define		CONST_d3dMenu_list										110


//
#define		CONST_d3dMenu_enlarge									120				//  2017/12/14



//  2014/11/17
#define		CONST_addTxtCfgIndex_note								0
#define		CONST_addTxtCfgIndex_menu								1
#define		CONST_addTxtCfgIndex_importantNote						2
#define		CONST_addTxtCfgIndex_warning_mosaic						3				//  2014/12/08

#define		CONST_addTxtCfgIndex_prop_wall							4				//  2016/01/03
#define		CONST_addTxtCfgIndex_menu_wall							5				//  2016/01/03

#define		CONST_addTxtCfgIndex_title								6				//  2016/02/05

//
#define		CONST_addTxtCfgIndex_tool_title							7				//  2016/02/28
#define		CONST_addTxtCfgIndex_tool_item							8				//  2016/02/28

//
#define		CONST_addTxtCfgIndex_peerImgTag							9				//  2017/07/11




//  2014/10/31
#if  0
#define		MIN_iW_mosaic											160
#define		MIN_iH_mosaic											120
#endif
//
#define		MIN_iW_mosaic											16
#define		MIN_iH_mosaic											12

//
#define		MAX_iW_mosaic											1024  *  8
#define		MAX_iH_mosaic											768  *  8

//
#define		DEFAULT_iW_mosaic_qcif									CONST_w_256x144		//256				//  
#define		DEFAULT_iH_mosaic_qcif									CONST_h_256x144		//144	//128	//144				//  

//  2014/12/13
#define		DEFAULT_iW_mosaic_ld									424				//  
#define		DEFAULT_iH_mosaic_ld									240				//  
//
#define		DEFAULT_iW_mosaic_sd									848				//  
#define		DEFAULT_iH_mosaic_sd									480				//  
//
#define		DEFAULT_iW_mosaic_hd									1280			//  
#define		DEFAULT_iH_mosaic_hd									720				//  
//
#define		DEFAULT_iW_mosaic_fullHd								1920			//  
#define		DEFAULT_iH_mosaic_fullHd								1080			//  
//
#define		DEFAULT_iW_mosaic_video4k								1920  *  2
#define		DEFAULT_iH_mosaic_video4k								1080  *  2



//
struct  __d3dImage_t {
	CAP_IMAGE										img;
	BOOL											bQuit;

	//
	DWORD											dwTickCnt_init_start;
	DWORD											nIntervalInMs_init;

	//
	DWORD											dwTickCnt_exit_start;
	DWORD											nIntervalInMs_exit;

	//
	TCHAR											talkerDesc[128];
	TCHAR											displayName[128];

};


//
#define			MAX_d3dImages									CONST_maxCapImages		//  2017/09/26		//  32


//
#define			CONST_d3dImagesType_null						0
#define			CONST_d3dImagesType_peer						1
#define			CONST_d3dImagesType_me							2
#define			CONST_d3dImagesType_other						3



//
typedef  struct  __d3dImages_t									{
				 CAP_images_head								head;
				 //
				 int											iType_forDbg;
				 //
				 D3D_image										mems[MAX_d3dImages];
}		 D3D_images;


//  2014/01/14
typedef  struct  __wmNote_t										{
				 TCHAR											tBuf[256];
				 //
				 TCHAR											tImportant[256];
				 //
				 TCHAR											tWhere[128];		//  2017/07/07
				 //
}		 WM_note;


//  2014/12/07
typedef  struct  __wmWarning_t									{
				 TCHAR											tBuf[128];
				 DWORD											dwModifiedTickCnt;
}		 WM_warning;


//  2014/02/05
typedef  struct  __wmDescInfo_t									{
				 TCHAR											tShortName[64];
				 TCHAR											tName[64];
				 //
				 //DWORD											dwModifiedTickCnt;
}		 WM_desc_info;


//  2014/11/01
typedef  struct  __d3dMosaicVideoCfg_t							{
				 int											iW;
				 int											iH;				 
}		 D3D_mosaicVideo_cfg;


typedef  struct  __d3dMosaicCfg_t								{

				 struct											{
					 int										iTaskId;
				 }												param;

				 //
				 D3D_mosaicVideo_cfg							cfg;

				 //
				 unsigned  int									uiObjType;

				 //  2014/11/13
				 BOOL											bResource;

				 //
				 BOOL											bSupported_pktResType_sharedTex1;			//  2015/10/21

				 //
				 unsigned  short								usMaxFps_toShareBmp;					//  2015/10/21


}		 D3D_mosaic_cfg;





//  2023/01/24
typedef  struct  __d3dTalkerMosaicCfg_t							{
				 unsigned  char									ucb2Streams;
				 //
				 D3D_mosaic_cfg									mosaicCfgs[MAX_talkerMosaic_streams];
}		 D3DTalkerMosaicCfg;




//  2015/12/27
typedef  struct  __WMData_cur_common_t							{
				 //
				 //DWORD										dwModifiedTickCnt_layout;
				 QY_timestamp									ts_layout;								//  2017/10/17
					 
				 //					
				 D3D_image										bgD3dImage;								//  2013/10/05
				 DWORD											dwModifiedTickCnt_bgD3dImage;

}		 WMData_cur_common;





//
#define		MAX_d3dWallMems_noWall								1							//  2015/12/12
//
#define		MAX_d3dWallMems_gZone								MAX_zoneObjs				//  16
//
#define		MAX_d3dWallMems_confWall							128							//  2015/12/16
//
#define		MAX_d3dWallMems_generalWall							MAX_zoneObjs				//  2016/06/03
//
#define		MAX_d3dWallMems_enlarge								12							//  2015/12/16
//
#define		MAX_d3dWallMems_modelessDlg							10							//  2015/12/16
//
#define		MAX_d3dWallMems_modeDlg								1							//  2015/12/16
//
#define		MAX_d3dWallMems_prop								4							//  2015/12/16
#define		MAX_d3dWallMems_menu								4							//  2015/12/16
//
#define		MAX_d3dWallMems_messageBox							1							//  2016/01/26
//
#define		MAX_d3dWallMems_internal							1024						//  2017/10/19


//
#define		MAX_d3dWallMems_talkerBgWall						MAX_subWallZones			//  2017/10/05


//



//  2016/01/29
struct  __param_wmCmd_t {
	WM_ID											wmId_target;

	//  2016/02/28
	struct {
		int							sx, sy;
	}												mouse;

	//
	RECT											menuRc_event;
	//
	int											iTaskId;
	//
	struct {
		int										iParam0;				//  2016/05/24
		int										iParam1;
	}												menuItem_param;
	//
};

//
#define		isIdcOk(  idc  )									(  idc  ==  IDOK  ||  idc  ==  ID_qyOk  )

//
struct  __d3d_wnd_mgr_t;

//
typedef  struct  __gBuf_d3d_isCli_t								{

				 HWND											hWall_d3d;
				 //
				 BOOL											bStartInitialization_d3d;
				 BOOL											bInited_d3d;
				 
				 //  
				 int											i3dType;

				 //
				 struct  __d3d_wnd_mgr_t 				*		pD3dWndMgr;			//  2016/05/27
				 

				 //
				 long											lStyle_org;

				 //
				 UINT_PTR										timerId;			//  2015/06/03

				 //
				 //BOOL											m_bWindowed;		//  2013/09/08
				 
				 //
				 BOOL											m_bActive;			//  2014/04/28

				 
				 //
				 unsigned  char  								ucbChkD3dWall;
				 DWORD											dwTickCnt_chkD3dWall;	//  2014/02/04

				 
				 //
				 struct											{				//  当需要确认时,先设置bExists. 然后设置dwTickCnt_start. 如果超过10秒,自动取消.
																				//  如果点确定,就触发idc
																				//  对菜单显示,当messageBox.bExists为true时,显示messageBox
																				
					 BOOL										bExists;
					 //
					 int										idc;
					 PARAM_wmCmd								param_wmCmd;
					 //
					 DWORD										dwTickCnt_start;
					 TCHAR										tHint[128];
					 //
					 //BOOL										bOk;
					 int										iRetVal_id_messageBox;

					 //

				 }												messageBox;

				 //
#if  0
				 struct											{
					 //TCHAR										tBuf[128];				
					 //
					 unsigned  char								ucbChanged;
				 }												hint;
#endif
				 //  2016/08/12
				 TCHAR											defaultWelcomeMsg[128];  
				 //
				 TCHAR											tWhere[128];				//  2016/10/16

				 //
				 bool											bDraw3dFps;					//  2019/07/21


}		 GBuf_d3d_isCli;


//
extern  "C" __declspec(dllexport)  int   set_g_pQyMc_isCliD3d(  void  *  pQyMc  );


//
extern  "C" __declspec(  dllexport  )  int  dllInit_d3d_isCli(  );
extern  "C" __declspec(  dllexport  )  int  dllExit_d3d_isCli(  );



//
extern  "C" __declspec(  dllexport  )  void  *  GBuf_d3d_isCli_new(  );
extern  "C" __declspec(  dllexport  )  void  GBuf_d3d_isCli_free(  void  **  ppGBuf_d3d_isCli  );


//  2014/11/04
//extern  "C"  __declspec(  dllexport  )  void  *  get_g_D3D_context(  );
extern  "C"  __declspec(  dllexport  )  unsigned  int  getMaxCnt_wallMems(  int  iGrpType  );
extern  "C"  __declspec(  dllexport  )  void  *  getWallMemByIndex(  void  *  pD3D_context,  int  iGrpType,  int  index  );
extern  "C"  __declspec(  dllexport  )  void  *  getD3dTalkerData(  void  *  pWallMemParam  );

//


//
extern  "C" __declspec(  dllexport  )  BOOL  bD3dUsing(  BOOL  *  pm_bActive  );
extern  "C" __declspec(  dllexport  )  BOOL  bFullScreen_d3dWnd(  HWND  hD3dWnd  );



extern  "C" __declspec(  dllexport  )  int  createConsoleWall(  void  *  pGBuf_d3d  );
extern  "C" __declspec(  dllexport  )  int  closeConsoleWall(  void  *  pGBuf_d3d  );


//
extern  "C"  __declspec(  dllexport  )  int  getVal_bWmTalkerShadowExists(  WM_ID  *  pWmId_talker,  BOOL  *  pbExists  );
 

//
extern  "C"  __declspec(  dllexport  )  int  d3dWall_closeDlgTalk_noHint(  HWND  hWall_d3d,  HWND  hDlgTalk_mgr  );


extern  "C"  __declspec(  dllexport  )  int  d3dWall_askToRefreshMenu(  );
extern  "C"  __declspec(  dllexport  )  int  d3dWall_askToRefreshIa(  );

//
extern  "C"  __declspec(  dllexport  )  int  d3dWall_askToRefreshTaskList(  );

 
 //
extern  "C"  __declspec(  dllexport  )  int  d3dWall_refreshWallMemInfo(  void  *  pWALLMem_common  );
 

 //
extern  "C"  __declspec(  dllexport  )  int  d3dWall_refreshImgs(  HWND  hDlgTalk_mgr,  TCHAR  *  hint  );
 //
extern  "C"   __declspec(  dllexport  )  int  d3dWall_refreshWallMemByTalker(  HWND  hDlgTalk  );


extern  "C"  __declspec(  dllexport  )  int  d3dWall_refreshAllWallMems(  );


//
extern "C"  __declspec(  dllexport  ) int  d3dWall_askToRefreshBg(  );
  

//
extern  "C"  __declspec(dllexport  )  int  d3dWall_enlargeWall(int  wallMemIndex);

//
int chkToEnlarge(int index_zoneObj);



//
extern  "C"  __declspec(  dllexport  )  int  refreshDlgTalkSubtitleMsgs_d3dWall(  HWND  hMgr  );
extern  "C"  __declspec(  dllexport  )  int  refreshDlgTalkSubtitlesCfg_d3dWall(  HWND  hMgr  );




///
extern  "C" __declspec(  dllexport  )  void  myRender();






//  2015/10/05
extern  "C" __declspec(  dllexport  )  int  getTex2Props(  void  *  p0,  int  iIndex_player,  TEX2_props  *  pProps  );


//
extern  "C" __declspec(  dllexport  )  int  fillData_d3d(  Ctx_fillData_d3d  *  pCtx,  myDRAW_VIDEO_DATA  *  pPkt,  int  iIndex_player,  PARAM_fillD3d  *  pParam,  BOOL  *  pbFilled  );
extern  "C" __declspec(  dllexport  )  int  fillData_d3d_setDataReady(  myDRAW_VIDEO_DATA  *  pPkt,  int  iIndex_player  );



//
extern  "C"  __declspec(  dllexport  )  void  *  getZoneObjsInfo_d3dWall(  HWND  hDlgWalls,  int  iWndContentType,  int  iZoneObjsType  );

//
extern  "C"  __declspec(  dllexport  )  void  *  qisWallsCfgNew(  unsigned  short  usMaxCnt  );
extern  "C"  __declspec(  dllexport  )  void  qisWallsCfgFree(  void  **  ppQIS_walls_cfg  );
//
extern  "C"  __declspec(  dllexport  )  int  addQisWallCfg(  void  *  pQIS_walls_cfg,  unsigned  int  uiType,  LPCTSTR  fileName,  int  *  piIndex  );
extern  "C"  __declspec(  dllexport  )  int  setCurQisWallCfg(  int  curIndex,  void  *  pQIS_walls_cfg  );


//  2014/10/31
extern  "C"  __declspec(  dllexport  )  int  removeMosaicFromD3dWall(  int  iIndex_sharedObj  );
extern  "C"  __declspec(  dllexport  )  int  getVal_bExists_mosaic(  int  iIndex_sharedObj,  BOOL  *  pbExists  );

//
extern  "C"  __declspec(  dllexport  )  int  tryToTalkToMessenger_d3dWall(  QY_MESSENGER_ID  *  pIdInfo,  int  iTalkUsage,  BOOL  bNeedExist_hWnd,  HWND  *  phWnd_mgr  );



 //
 //
int  dyn_set_g_pQyMc_isCliD3d(  void  *  pQyMc  );

int  dyn_dllInit_d3d_isCli(  );
int  dyn_dllExit_d3d_isCli(  );

void  *  dyn_GBuf_d3d_isCli_new(  );
void  dyn_GBuf_d3d_isCli_free(  void  **  ppGBuf_d3d_isCli  );

unsigned  int  dyn_getMaxCnt_wallMems(  int  iGrpType  );
void  *  dyn_getWallMemByIndex(  void  *  pD3D_context,  int  iGrpType,  int  index  );
//void  *  dyn_getD3dTalkerData(  void  *  pWallMemParam  );



//
int  dyn_createConsoleWall(  void  *  pGBuf_d3d  );
int dyn_createGeneralWall(HINSTANCE hInstance, LPCTSTR  szTitle, HICON  hIcon,  HMENU  hMenu,  int  x,  int  y);

//
void  dyn_myRender();

//
int  dyn_getTex2Props(  void  *  p0,  int  iIndex_player,  TEX2_props  *  pProps  );

//
int  dyn_fillData_d3d(Ctx_fillData_d3d  *  pCtx,  myDRAW_VIDEO_DATA  *  pPkt,  int  iIndex_player,  PARAM_fillD3d  *  pParam,  BOOL  *  pbFilled  );
int  dyn_fillData_d3d_setDataReady(  myDRAW_VIDEO_DATA  *  pPkt,  int  iIndex_player  );

//
void  *  dyn_getZoneObjsInfo_d3dWall(  CCtxQmc  *  pProcInfo,  HWND  hDlgWalls,  int  iWndContentType,  int  iZoneObjsType  );

//
void  *  dyn_qisWallsCfgNew(  unsigned  short  usMaxCnt  );
void  dyn_qisWallsCfgFree(  void  **  ppQIS_walls_cfg  );

int  dyn_addQisWallCfg(  void  *  pQIS_walls_cfg,  unsigned  int  uiType,  LPCTSTR  fileName,  int  *  piIndex  );
int  dyn_setCurQisWallCfg(  int  curIndex,  void  *  pQIS_walls_cfg  );


//
int  dyn_d3dWall_askToRefreshMenu(  );
int  dyn_d3dWall_askToRefreshIa(  );

//
int  dyn_getVal_bWmTalkerShadowExists(  WM_ID  *  pWmId,  BOOL  *  pbExists  );

//
int  dyn_refreshDlgTalkSubtitlesCfg_d3dWall(  HWND  hMgr  );
int  dyn_refreshDlgTalkSubtitleMsgs_d3dWall(  HWND  hMgr  );


 //
 int  dyn_d3dWall_refreshAllWallMems(  );
 int  dyn_d3dWall_refreshWallMemByTalker(  HWND  hDlgTalk  );
 int  dyn_d3dWall_refreshImgs(  HWND  hDlgTalk_mgr,  TCHAR  *  hint  );
 

 //
 extern  "C"  __declspec(  dllexport  )  BOOL createGeneralWall(HINSTANCE hInstance, LPCTSTR  szTitle, HICON  hIcon,  HMENU  hMenu,  int  x,  int  y);


 //
 //
extern  "C"  __declspec(dllexport) int  createConsoleWall_dx12(void* pGBuf_d3d);
extern  "C"  __declspec(dllexport) int  closeConsoleWall_dx12(void* pGBuf_d3d);

//
extern  "C"  __declspec(dllexport)  int  tryToChkD3dWall(D3D_context * pCtx);



#endif  //  }

