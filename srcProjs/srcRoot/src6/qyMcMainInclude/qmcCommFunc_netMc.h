
#ifndef  __QMCCOMMFUNC_NETMC_H__
#define	 __QMCCOMMFUNC_NETMC_H__	//  {


typedef  struct  __monedDesktop_t			{
				 char						mac0[CONST_qyMacLen  +  1];
				 WCHAR						wUsrDomain[128  +  1];
				 //
				 TCHAR						displayName[MAX_PATH  +  1];
				 //
}		 MONED_DESKTOP;


#define		CONST_maxMonedDesktops			16		//  这个值跟在资源文件里的picture的个数有关．所以，不要轻易修改这个值


typedef  struct  __mcVar_netMc_t			{

				 struct						{
					 TCHAR					mutexName_syncGuiTalk[64  +  1];
					 //
				 }							cfg;

				 HWND						hDlgDesktopsMon;
				 MONED_DESKTOP				monedDesktops[CONST_maxMonedDesktops];
				 unsigned  short			usCnt_monPcs;
				 
}		 MC_VAR_netMc;




 unsigned  int  getVarSize_netMc(  void  *  pQyMc  );

 int  initVar_netMcGui(  void  *  p0,  void  *  p1,  void  *  p2  );
 int  exitVar_netMcGui(  void  *  p0,  void  *  p1,  void  *  p2  );


 int  viewRemoteDesktop(  void  *  pDb,  void  *  p1,  char  *  mac0,  unsigned  char  ucbMonDesktop  );
 int  cancelRemoteDesktop(  void  *  pDb,  void  *  p1,  char  *  mac0,  unsigned  char  ucbMonDesktop  );

 int  getMonPicsCfg(  unsigned  short  *  pusCnt_monPics_row,  unsigned  short  *  pusCnt_monPics_col  );
 int  startDesktopMon(  void  *  p0,  char  *  mac0,  LPCTSTR  displayName  );
 int  stopDesktopMon(  void  *  p0,  char  *  mac0,  void  *  p2  );

 int  threadRefreshMonedDesktops(  );

 int  qnmTellPolicyChangedEx_netMc(  void  *  p0,  myREFRESHED_PCOPCMD  *  pPcOpCmd  );
 


#endif  //  }


