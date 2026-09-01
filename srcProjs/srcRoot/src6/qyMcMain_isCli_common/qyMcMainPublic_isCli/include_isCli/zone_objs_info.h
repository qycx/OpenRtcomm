

#ifndef  __zone_objs_info_h__
#define  __zone_objs_info_h__	//  {


//
#define  CONST_zoneObjsType_null			0
#define  CONST_zoneObjsType_talkers			1
#define  CONST_zoneObjsType_walls			2



//
typedef  struct  __dlgGuiData_wall_t					{
				 BOOL									bInited;
				 BOOL									bCreated;	

				 int									iIDC_BUTTON_contact;
				 int									iIDC_BUTTON_group;
				 int									iIDC_BUTTON_customerServiceOfficer0;
				 int									iIDC_BUTTON_bar;
				 //

				 //
				 int									w_org,  h_org;
				 RECT									rcIDC_BUTTON_contact;	
				 RECT									rcIDC_BUTTON_group;
				 RECT									rcIDC_BUTTON_customerServiceOfficer0;
				 RECT									rcIDC_BUTTON_bar;

				 unsigned  char							ucbHideBar;

}		 DLG_guiData_wall;


//
typedef  struct  __paramLayoutDlgWall_t					{
}		 PARAM_layout_dlgWall;





//
typedef  struct  __zoneObjInfo_t						{
				 //HWND									hWndWallMem;
				 CAP_RECT								rect;
				 //
				 BOOL									bSmallest;
				 
				 //
				 int									tn_to_get_zoneObjs_layoutInfo_d3d;		//  for help

}		 ZONE_obj_info;


//
#define		CONST_zoneLayoutType_null					0
#define		CONST_zoneLayoutType_6X1					1
#define		CONST_zoneLayoutType_1_2X2_1_v				2
#define		CONST_zoneLayoutType_1_2X1_1X3				3
#define		CONST_zoneLayoutType_1_2X2_1_h				4
#define		CONST_zoneLayoutType_1X6					5



//
typedef  struct  __zoneObjsInfo_t						{
				 DLG_guiData_wall						guiData;

				 struct									{

					 int								iEdge_t;
					 int								iEdge_l;

					 int								iW_btn,  iH_btn;
			
					 int								iX_spacing;
					 int								iY_spacing;

				 }										oldLayout;

				 //
				 HWND									m_hParent;

				 //  2016/02/08
				 struct									{
					 int								zone_w;
					 int								zone_h;
					 //
					 unsigned  int						layoutType;
					 //
					 CAP_RECT							crs[6];
					 
					 //
					 int								tn_to_get_zoneObjs_layoutInfo_d3d;		//  for help
					 
					 //
					 #define		MAX_bigZoneObjs		2
					 #define		MAX_recentZoneObjs	2					 

					 //
					 unsigned  int						startIndex_toBeBig;
					 DWORD								dwLastModifiedTickCnt_startIndex_toBeBig;
					 unsigned  int						index_bigs[MAX_bigZoneObjs];
					 int								cnt_bigs;
					 
					 //
					 unsigned  int						index_recents[MAX_recentZoneObjs];
					 int								cnt_recents;

				 }										d3d;

				 //
				 ZONE_obj_info							mems[MAX_zoneObjs];
				 //int									iIndex_enlarged;			//  被放大的index. 
				 int									iIndex_selected;			//  被选中的index. 2011/03/23

				 //
				 PARAM_layout_dlgWall					layoutParam;		

				 //
				 WINDOWPLACEMENT						m_oldWndPlacement;
				 struct									{
					 HMENU								hOldMenu;								//  2012/07/07
					 long								lOldStyle;								//  2012/07/07
				 }										m_fullScreenInfo;
				 //
				 BOOL									m_bFullScreen;
				 RECT									m_fullScreenRect;
				 PARAM_layout_dlgWall					m_oldLayoutParam;

				 //
				 unsigned  int							uiTimerId;

				 DWORD									dwTickCnt_lastMouseMove;
				 DWORD									dwTickCnt_hide_bar;

				 struct									{
					 int								xPos_screen;
					 int								yPos_screen;
					 //
					 RECT								rc_zone;
				 }										param_viewMenu;
				 struct									{
					 int								xPos_screen;
					 int								yPos_screen;
					 //
				 }										param_viewBar;

				 //  2012/04/06
				 HWND									hBar;
				 int									iBarType;			//  2018/06/25
				 //
				 HWND									hMenu;

}		 ZONE_objs_info;

#endif  //  }


