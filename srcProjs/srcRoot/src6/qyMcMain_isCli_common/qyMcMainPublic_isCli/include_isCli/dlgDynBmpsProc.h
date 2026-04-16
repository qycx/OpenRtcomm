

#ifndef  __dlgDynBmpsProc_h__
#define  __dlgDynBmpsProc_h__	//  {


//
#include	"gpsCommProc.h"
#include	"qmcObjVarInfo.h"


//
#define		DEFAULT_uiInitW_wall_800	800		//1024  +  30  +  32
#define		DEFAULT_uiInitH_wall_600	600		//768  +  30  +  32
//
#define		DEFAULT_uiInitW_wall_1024	1024	//1024  +  30  +  32
#define		DEFAULT_uiInitH_wall_768	768		//768  +  30  +  32



//  2012/05/08
typedef  struct  __wallGpsMgrMem_t				{
				 HWND							hMem;
				 int							iIndex_shadow;

				 //
				 myGPS_POSITION					gpsPos;

				 //
				 int							x,  y,  iW,  iH;
				 UINT							uFlags;

}		 WALL_gps_mgrMem;

typedef  struct									{
			    DWORD							dwTickCnt_lastRefreshed;
				//				
				BOOL							bMoving;
				//
				WALL_gps_mgrMem					mems[350];
}		 WALL_gps_mgr;


//
typedef  struct  __dlgDynBmpsVar_t				{
				 MACRO_objVarData_commonMems

				 //  2015/11/21
				 int							iIndex_objVarInfo;

				 //
				 TCHAR							title[128  +  1];

				 MIS_CNT				*		pMisCnt;
				 
				 //  2017/06/14
				 BOOL							bAvConsole;
				 				 
				 //
				 unsigned  char					ucbLocalAv;							//  
				 unsigned  char					ucbAutoSize1;						//  2009/10/02
				 unsigned  char					ucbAutoClip;						//  2014/04/06

				 unsigned  char					ucbEditable;						//  2009/10/04
				 unsigned  char					ucbShowRules;						//  2009/10/04

				 //
				 struct							{									//  2017/01/10
					 unsigned  char				ucbOn;
					 int						iTries;
				 }								quickToRetrieveImg;
				 //
				 unsigned  char					ucbNoBar;							//  2017/01/10
				 
				 //
				 struct							{
						 unsigned  char			ucbVideoConference;					//  2009/10/14

						 //
						 HWND					hDlgTalk_mgr;						//  2017/09/25

						 //
						 HWND					hWnd_avRes;							//  2018/06/23

						 //
						 QY_MESSENGER_ID		idInfo;								//  2009/09/03
						 unsigned  int			uiObjType;							//  2009/09/03
						 unsigned  short		usIndex_obj;
						 TCHAR					cusName[32];
						 
						 //  2015/05/09
						 TCHAR					fileName[MAX_PATH  +  1];
						 SHARE_dyn_bmp		*	pShareDynBmp_toPlayFile;
						 
						 //
						 unsigned  int			uiTranNo_spObj;
				
						 //
						 QY_MESSENGER_ID		idInfo_grp_avStream;				//  2018/12/18. 只在这个组内看AVSTREAM。所以需要先启动会议


						 //  2012/04/24
						 struct					{
							 int				zoom;
							 POINT				origin;
						 }						coord;

						 //
				 }								vWall;
				 				 
				 //
				 CQyVWall				*		pWall;

				 //  2012/04/02
				 ZONE_objs				*		pZoneObjs;
				 void					*		pZoneObjsInfo_talkers;					//  ZONE_objs_info. 在globalVWall里,未指定的talker都放置在这里. 


				 //
				 UINT							nElapseInMs;
				 UINT_PTR						nTimerId;

				 int							nCtrls;

				 TCHAR							tHint[256];
				 VW_ruleU						rule_sel;

				 //
				 unsigned  char					ucbNeedToChkRules;					//  2012/04/29. 在stopedit后,用这个标志位来促使立即刷新策略. 只触发一次

				 //  2012/05/08
				 CAP_subWnds					subWnds;

				 //  2012/05/08
				 WALL_gps_mgr					wallGpsMgr;

				 //
				 MIS_MSGU				*		pMsgBuf_doWnd_guiMsgArrive;			//  2009/12/08

				 BOOL							bInited;
	
				 //
				 BOOL							bLocked_toQuitDlg1;					//  2012/05/08

				 //  2017/09/22
				 unsigned  short										usCnt_zoneParams;
				 ZONE_PARAM										*		pZoneParams;					 



}		DLG_dynBmps_var;	




#endif  //  }


