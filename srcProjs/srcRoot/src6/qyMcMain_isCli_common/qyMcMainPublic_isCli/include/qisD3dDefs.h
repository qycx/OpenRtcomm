


#ifndef  __qisD3dDefs_h__
#define  __qisD3dDefs_h__	//  {


//
//
#define		CONST_wallMemType_null									0
//
#define		CONST_wallMemType_img									10
//
#define		CONST_wallMemType_talker								101
#define		CONST_wallMemType_talkers								103
//
#define		CONST_wallMemType_talker_bgWall							110				//  200				//  2016/03/17

//
#define		CONST_wallMemType_dynBmp								200				//  102

//
#define		CONST_wallMemType_wall									300				//  refer to general wall
#define		CONST_wallMemType_walls									305				//  2016/06/02. only having general walls
//
#define		CONST_wallMemType_noWall								400				//  110
//
#define		CONST_wallMemType_enlarge								500				//  111

//  2016/02/22
#define		CONST_wallMemType_list									600				//  120
#define		CONST_wallMemType_msgList								601				//  121
#define		CONST_wallMemType_control								602				//  122


//
#define		CONST_wallMemType_menu									700				//  150




//
#define		CONST_wmSubtype_null									0
#define		CONST_wmSubtype_prop									1
#define		CONST_wmSubtype_menu									2
#define		CONST_wmSubtype_messageBox								3

//
#define		CONST_wmSubtype_bgWallMem								20
//
#define		CONST_wmSubtype_talkerBgZone							24				//  2017/10/04
#define		CONST_wmSubtype_talkerBgWall							25

//
#define		CONST_wmSubtype_talkers_talker							30				//  2017/10/27

//
#define		CONST_wmSubtype_edit									50

//  2016/03/24
#define		CONST_wmContentType_null								0
//
#define		CONST_wmContentType_msgList								9
#define		CONST_wmContentType_taskList							10



//
extern  QY_DMITEM  CONST_wmGrpTypeTable[];
extern  QY_DMITEM  CONST_wallMemTypeTable[];
extern  QY_DMITEM  CONST_wmSubtypeTable[];



//  2015/12/17
#define		CONST_wmGrpType_null									0
#define		CONST_wmGrpType_gZone									1
#define		CONST_wmGrpType_noWall									2
#define		CONST_wmGrpType_confWall								3
//
#define		CONST_wmGrpType_generalWall								20			//  2016/06/03
//
#define		CONST_wmGrpType_enlarge									30			//  2016/06/03	//  10
//
#define		CONST_wmGrpType_modelessDlg								50			//  20
//
#define		CONST_wmGrpType_modeDlg									55			//  25

//
#define		CONST_wmGrpType_prop									60			//  50
#define		CONST_wmGrpType_menu									61			//  51
//
#define		CONST_wmGrpType_messageBox								70			//  60


//
#define		CONST_wmGrpType_internal								150			//  2017/10/19


//
//  2016/01/29
typedef  struct  __wm_id_t											{
				 int												index_d3dWnd;			//  2016/05/28
				 //
				 int												iGrpType;
				 int												index_wm;				 				
				 //
				 unsigned  int										uiTranNo_wm;
}		 WM_ID;

//
//  2016/01/04
#define  isSame_wmId(  pWM_ID1,  pWM_ID2  )		(  (  pWM_ID1  )			\
												&&  (  pWM_ID2  )			\
												&&  (  pWM_ID1  )->index_d3dWnd  ==  (  pWM_ID2  )->index_d3dWnd	\
												&&  (  pWM_ID1  )->iGrpType  ==  (  pWM_ID2  )->iGrpType			\
												&&  (  pWM_ID1  )->index_wm  ==  (  pWM_ID2  )->index_wm			\
												&&  (  pWM_ID1  )->uiTranNo_wm  ==  (  pWM_ID2  )->uiTranNo_wm  )
//
#define  isNULL_wmId(  pWM_ID  )	(  !(  pWM_ID  )  ||  (  !(  pWM_ID  )->index_d3dWnd  &&  !(  pWM_ID  )->iGrpType  &&  !(  pWM_ID  )->index_wm  &&  !(  pWM_ID  )->uiTranNo_wm  )  )



//  2015/10/06
typedef  struct  __tex2Props_t										{
				 BOOL												bAvail;
				 //
				 unsigned  int										uiSeqNo_lastRender;
				 //
				 unsigned  int										uiXql_player;	//  2016/04/14

}		 TEX2_props;


//
			//
typedef  struct  __ctx_fillData_d3d_t {
	char* pImgDataBuf;
	int					sizeof_pImgDataBuf;

	//
	int					index_player;

}		 Ctx_fillData_d3d;


//
typedef  struct  __param_renderTxt_t {
				 int  vp_iW;
				 int  vp_iH;

				 //
				 bool	bEnlarge;

				 bool	bEnlargeVideo;

}  Param_renderTxt;





#endif  //  }

