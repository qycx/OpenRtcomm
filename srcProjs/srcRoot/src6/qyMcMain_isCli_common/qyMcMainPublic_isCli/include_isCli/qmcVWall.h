

#ifndef  __QMCVWALL_H__
#define  __QMCVWALL_H__		//  {

//
#include	"qyTimestamp.h"
//
#include	"sp.h"
//
#include	"d3dWallMemIa.h"


//  
#define		MAX_subWallZones							128											//  2011/10/16
#define		MAX_qySubVWalls								8


////////////////
//  2012/04/02
#define		CONST_vwRuleType_null						0
#define		CONST_vwRuleType_dynBmp						1
#define		CONST_vwRuleType_conference_imGrp			2
#define		CONST_vwRuleType_conference_imGrpMem		3
//
#define		CONST_vwRuleType_bgMemVideo					5			//  2017/09/19
//
#define		CONST_vwRuleType_talkers					10
#define		CONST_vwRuleType_messenger					11
//
#define		CONST_vwRuleType_walls						20			//  2016/06/01


//
#define		MACRO_vwRuleCommon							unsigned  int  uiType;	\
														unsigned  int  uiTranNo_spObj;


typedef  struct  __vwRule_dynBmp_t						{
				 MACRO_vwRuleCommon

				 //
				 DYN_BMP_rule							ruleDynBmp;					//  2014/08/04
				 
				 //
				 HWND									hTalkerShadowMgr;			//  2012/05/05

				 //
				 //  int									iTaskId;

}		 VW_rule_dynBmp;


//
typedef  struct  __vwRule_conference_imGrp_t			{
				 MACRO_vwRuleCommon

				 QY_MESSENGER_ID						idInfo;

}		 VW_rule_conference_imGrp,  VW_rule_conference_imGrpMem;



typedef  struct  __vwRule_messenger_t					{
				 MACRO_vwRuleCommon

				 QY_MESSENGER_ID						idInfo;

				 //
				 HWND									hTalkerShadowMgr;			//  2012/04/29
				 HWND									hTalkerShadow;				//  2012/04/20

				 //
				 VW_rule_messengerCmd					cmd;

}		 VW_rule_messenger;


//  2017/09/21
typedef  struct  __vwRule_bgMemVideo_t					{
				 MACRO_vwRuleCommon

				 QY_MESSENGER_ID						idInfo;

}		 VW_rule_bgMemVideo;


//
typedef  union  __vwRuleU_t								{
				struct									{
					MACRO_vwRuleCommon
				}										common;
				VW_rule_dynBmp							dynBmp;
				VW_rule_conference_imGrp				conference_imGrp;
				VW_rule_conference_imGrpMem				conference_imGrpMem;
				VW_rule_messenger						messenger;
				//
				VW_rule_bgMemVideo						bgMemVideo;
				//
}		 VW_ruleU;


//
typedef  struct  __myStreamInfo_t						{

				 int									iHkStatus;

}  myStreamInfo;


//
typedef  struct  __myZone_t								{

				 //
				 int									iX_org,  iY_org;			
				 unsigned  int							iW_org,  iH_org;

				 int									iX,  iY;					
				 unsigned  int							iW,  iH;

				 unsigned  int							uiTranNo_spObj;

				 //
				 int									idcStatic_desc;			//  2019/01/23

				 //  2015/11/24
				 VW_ruleU								rule;

				 //  2017/10/05
				 QY_timestamp							ts_zone;

				 //  2016/08/07
				 //D3D_wallMem_ia							cfgIa1;

				 //
				 CAP_IMAGES								images;

				 //  2023/05/04
				 myStreamInfo							streamInfos[CONST_maxCapImages];

}		 myZONE;


//
typedef  struct  __subVWall_t				{
				 int						idc;
				 int						idcHint;									//  2009/10/09
				 HWND						hWnd_subWall;

				 void				*		pSp;
				 BOOL						bSpInited;

				 GENERIC_Q			*		pRuleQ;

				 //
				 int						iX_org,  iY_org;							//  2009/10/06
				 unsigned  int				iW_org,  iH_org;

				 int						iX,  iY;					
				 unsigned  int				iW,  iH;

				 //  2012/04/24. 由于窗口的缩放,为了图形不变形,而计算出的画图位置
				 int						iX_image,  iY_image;
				 unsigned  int				iW_image,  iH_image;

				 //
				 //
				 HWND						hWnd_dst;									//  2013/03/02
				 HDC						hDc_dst;

				 //
				 TCHAR						fileName_background[MAX_PATH  +  1];		//  2009/10/07
				 HBITMAP					hBmp_background;							//  2009/10/05

				 unsigned  short			usCnt;
				 myZONE						mems[MAX_subWallZones];

}		 SUB_V_WALL;


//
typedef  struct  __qyVWall_t				{

				 HWND						hWnd;
				 HWND						hWnd_spToolbox;

				 //
				 TCHAR						title[128];

				 unsigned  short			curSpIndex;

				 unsigned  short			usCnt;
				 SUB_V_WALL			*		memPtrs[MAX_qySubVWalls];
}		 QY_V_WALL;


//
class  CQyVWall								{
 
public:
		QY_V_WALL							m_var;

 public:
	    CQyVWall(  );
		~CQyVWall(  );

		int				addSubWall(  int  idc,  int  idcHint  );
		SUB_V_WALL  *	getSubWall(  int  index  );
		void			removeSubWall(  int  index  );
		void			removeAllSubWalls(  );
		void			resetSubWall(  int  index  );

		SUB_V_WALL  *  	getCurSubWall(  );
		void		*	getCurSp(  );

		int				setBitmap(  LPCTSTR  pathName,  int  index  );
		int				resetBitmap(  int  index  );

};

////////////////////


 //  2009/10/07
 #define		CONST_qvwVer_is							"010101"

 #define		CONST_qyFileObjName_subWall				"subWall"
 #define		CONST_qyFileObj_rect_org				"rect_org"
 #define		CONST_qyFileObj_rect					"rect"

 
 #define		CONST_qyFileObjName_cad					"cad"
 #define		CONST_qyFileObj_cadObj					"cadObj"

 #define		CONST_qyFileObjName_vwRules				"vwRules"
 #define		CONST_qyFileObj_vwRule					"vwRule"

#define			CONST_qyPropType_null					0
#define			CONST_qyPropType_pos					1
#define			CONST_qyPropType_dep					2
#define			CONST_qyPropType_horz					3
#define			CONST_qyPropType_vert					4
//
#define			CONST_qyPropType_save					100		//  2014/08/08
//
#define			CONST_qyPropType_dynBmp					256
#define			CONST_qyPropType_imGrp					257
#define			CONST_qyPropType_messenger				258

extern  QY_DMITEM  CONST_qyPropTypeTable[];




 //  int  viewVWall(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  int  iSubType,  BOOL  bNewVirtualWall,  HWND  *  phWnd  );
 int  viewGpsVWall(  HWND  hParent,  LPCTSTR  misServName  );
 int  viewGlobalVWall(  HWND  hParent,  LPCTSTR  misServName,  LPCTSTR  init_qvwFile,  BOOL  bNeedNotShowWnd  );
 int  viewGlobalGpsVWall(  HWND  hParent,  LPCTSTR  misServName  );
 

 //  int  viewToolbox_sketchpad(  void  *  pDlgParent  );
 __declspec(  dllexport  )  int  viewToolbox_sketchpad(  HWND  hDlgParent,  void  *  pDLG_dynBmps_var  );

 //  2018/06/23
  __declspec(  dllexport  )  int viewDlgAvRes(  HWND  hWndEvent,  int  iWndContentType,  int  xPos_screen,  int  yPos_screen,  HWND  hDlgDynBmps,  void  *  pDLG_wall_var,  BOOL  bNoDelayToView  );
  __declspec(  dllexport  )  int  hideDlgAvRes(  HWND  hWnd    );

  int  avRes_proc_applyForOrgReq(  HWND  hBar,  IM_GRP_EX  *  p,  QY_MESSENGER_ID  *  pIdInfo_from  );
   int  refreshAvResGrpInfo(  HWND  hBar,  IM_GRP_EX  *  p  );
 int  refreshAvResConfAccepted(  HWND  hBar  );


 //
 typedef  struct  __qyPropMem_t				{
				unsigned  int				uiType;
				union						{
					struct					{
						SP_RECT_COORD		coord;
					}						pos;
					struct					{
						unsigned  short		usCnt;
						unsigned  int		uiTranNo_spObjs[12];
					}						dep;
					struct					{
						BOOL				bVal;
					}						horz;
					struct					{
						BOOL				bVal;
					}						vert;
					struct					{
						QY_MESSENGER_ID		idInfo;
						unsigned  int		uiObjType;
						unsigned  short		usIndex_obj;
					}						dynBmp;
					struct					{
						QY_MESSENGER_ID		idInfo;
					}						imGrp;
					struct					{
						QY_MESSENGER_ID		idInfo;
					}						messenger;
				}							u;

}		 QY_propMem;

typedef  struct  __qyProps_t				{
				 unsigned  short			usCnt;
				 QY_propMem					mems[16];
}		 QY_props;

 //
 __declspec(  dllexport  )  BOOL  bQisExportVWall(  void  *  pCQyVWall,  void  *  pQY_IMEXPORTINFO  );
 __declspec(  dllexport  )  BOOL  bQisImportVWall(  void  *  pQY_IMEXPORTINFO,  void  *  pCQyVWall  );


 //
 void * vw_getCurSp(  void  *  pCQyVWall  );


   extern  QY_DMITEM  CONST_rulePriorityTable[];
   extern  QY_DMITEM  CONST_vwRuleTypeTable[];


#endif  //  }



