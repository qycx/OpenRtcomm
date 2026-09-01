
#ifndef  __qisWallsProc_h__
#define  __qisWallsProc_h__


//
#define		CONST_wallType_null				0
#define		CONST_wallType_conf				1				//  default
#define		CONST_wallType_confWall			2
#define		CONST_wallType_enlarge			3				//  2016/05/28


//  2015/11/16
#define		MAX_qisWallCfgs					5				//  3


//
typedef  struct  __qisWallCfg_t				{
				 unsigned  int				uiType;
				 //
				 TCHAR						wallFilePath[MAX_PATH];

}		 QIS_wall_cfg;

//
typedef  struct  __qisWallsCfg_t			{
				 unsigned  short			usCnt;
				 QIS_wall_cfg			*	pMems;				 

				 //
				 int						curIndex_activeWallCfg;

				 //
				 DWORD						dwModifiedTickCnt_qisWallCfg;

}		 QIS_walls_cfg;



#endif

