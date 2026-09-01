
#ifndef  __DLGWALLSPROC_H__
#define  __DLGWALLSPROC_H__		//  {


#define		CONST_bkColor_fullScreen_walls				RGB(  0,  0,  0  )

//  2015/12/04
#include	"zone_objs.h"


#include	"zone_objs_info.h"



//  void  *  getDlgWallsVar(  HWND  hDlgWalls  );
__declspec(  dllexport  )  int  addToWalls(  HWND  hDlgTalk,  HWND  hDlgWalls,  int  iWndContentType,  int  *  piIndex_wall  );

//  2014/01/01
 int  getWallMemInfo(  ZONE_objs  *  pZoneObjs,  HWND  hDlgTalk,  BOOL  *  pbEnlared  );


int  closeWallMems(  HWND  hDlgWalls,  int  iWndContentType  );
BOOL  bExists_wallMem(  HWND  hDlgWalls,  int  iWndContentType  );

//
//int  enlargeWall(  HWND  hDlgWall  );
int  selectWall(  HWND  hDlgWall  );

//
BOOL  isWallEnlarged(  HWND  hDlgWall  );
BOOL  isWallSelected(  HWND  hDlgWall  );

//  int  setWallsBarPos(  HWND  hDlgWalls,  HWND  hBar  );

__declspec(  dllexport  )  int  viewWallsBar_ts(  HWND  hWndEvent,  int  iWndContentType,  int  xPos_screen,  int  yPos_screen,  HWND  hDlgWalls,  int  iWndContentType_hDlgWalls,  BOOL  bNoDelayToView  );
__declspec(  dllexport  )  int  viewWallsMenu(  int  xPos_screen,  int  yPos_screen,  HWND  hDlgWalls,  int  iWndContentType,  BOOL  bNoDelayToView,  RECT  *  pRect_zone,  void  *  pVwRuleU  );
__declspec(  dllexport  )  int  setWallsMenuPos(  HWND  hDlgWalls,  HWND  hMenu,  RECT  *  pRect_zone  );

__declspec(  dllexport  )  int  sizeAllControls_dlgWalls(  HWND  hDlg,  int  iWndContentType,  ZONE_objs_info  *  pVar  );

int  dlgWalls_Onfullscreen(  HWND  hDlgWalls  );

//  int    getRect_talkers(  HWND  hDlgWalls,  RECT  *  pRc  );	//  2012/04/03
//  int    getRect_idcHint(  HWND  hDlgWalls,  RECT  *  pRc  );




int  layoutWalls(  HWND  hDlgWalls,  int  iWndContentType  );
int  qisChkWalls(  );

int  dlgDynBmps_findZoneParam(  HWND  hDlgDynBmps,  MIS_MSG_procVideo_qmc  *  pMsg,  ZONE_PARAM  *  pParam  );
int  tmpHandler_chkVWallRule_dlgDynBmps(  void  *  p0,  void  *  p1,  void  *  p2  );

//
int  dlgShareDynBmps_refreshShareStatus_gps(  QY_MC  *  pQyMc, HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  );

int  dlgShareDynBmps_refreshShareStatus(  QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType  );


LRESULT  dlgShareDynBmps_OnQyComm( QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  WPARAM wParam, LPARAM lParam );

LRESULT  dlgShareDynBmps_OnQyPostComm( QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  WPARAM wParam, LPARAM lParam );

int  dlgShareDynBmps_chkTask(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  iTaskId  );

int  dlgShareDynBmps_toShareDynBmp( QY_MC  *  pQyMc, HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  int  index_pShare_mem,  void  **  ppCapStuff,  AV_COMPRESSOR_CFG  *  pCompressor_suggested,  TASK_av_props  *  pTaskAvProps  );


//
int  dlgShareDynBmps_toShareGps(  QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var);
int  dlgShareDynBmps_closeTaskAv(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  int  index_pShare_mem  );
int  dlgShareDynBmps_chkShareGps(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  );


int  dlgShareDynBmps_sndDynBmpsInfo(   HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  );

//  2014/06/06
int dlgShareDynBmps_testRtspUrl(  QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  short  usIndex_obj,  unsigned  short  usHelp_subIndex  );



//  int  shareDynBmpMem_internalProcess(  HWND  m_hWnd,  DLG_shareDynBmps_var  *  pm_var,  SHARE_dyn_bmp  *  pDynBmpMem  )

int  dlgShareDynBmps_internalProcess(  QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  );


//
int  dlgShareDynBmps_toShareScreen_func(  HWND  hDlg_shareDynBmps,  int  index_pShare_mem  );


//
BOOL  dlgShareDynBmps_bShared(  HWND  hDlg_shareDynBmps,  unsigned int  uiObjType,  int  index_obj  );

int  dlgShareDynBmps_toShareWebcam_func(  HWND  hDlg_shareDynBmps,  unsigned  int  uiObjType,  int  index_pShare_mem,  void  **  ppCapStuff,  int  iMenuId_v,  BOOL  bUnresizable  );



#endif  //  }


