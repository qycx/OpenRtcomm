
#ifndef  __QYGUICOMMPROC_H__
#define  __QYGUICOMMPROC_H__	//  {


//  2017/09/28
#include	"ctxQmThread.h"
#include	"qytimestamp.h"


//
//  #define		CONST_maxCapImages									16
//  #define		CONST_maxCapImages									32							//  2014/10/12
//#define		CONST_maxCapImages									20							//  2017/09/26
#define		CONST_maxCapImages										50							//  2017/09/26


//
typedef  struct  __capImage_t									{

				 //
				 unsigned  int									iW_org,  iH_org;			//  原始大小,这是为了等比例缩放.
				 
				 //
				 unsigned  int									iW_i,  iH_i;				//  2014/04/12. 中间值，必须和org等比例，并能被共同单位整除

				 //  
				 int											iX_src_i,  iY_src_i;		//  2014/04/06. 从中间图像中iX_src_i,iY_src_i->iX_dst,iY_dst,iW_dst,iH_dst
				 
				 //
				 int											iX_dst,  iY_dst;			//  因为希望是等比例缩放, 所以图形的大小和位置也要计算
				 unsigned  int									iW_dst,  iH_dst;

				 //
				 QY_MESSENGER_ID								idInfo_sender;				//  idInfo_sender  +  uiTranNo_openAvDev  +  iTaskId  +  usIndex_activeMems_from 确定了一个独立处理的图象源.
				 //
				 unsigned  int									uiTranNo_openAvDev;			//  tn_v
				 //
				 unsigned  int									tn_a;						//  这个结构扩展到可以代表只有音频没有图像的流。所以idInfo_sender  +  tn_v  +  tv_a  +  iTaskId确定了一个独立的源

				 //
				 int											iTaskId;
				 unsigned  short								usIndex_activeMems_from;	//  2015/10/01. usIndex;

				 //  2015/11/10
				 unsigned  char									ucbUnresizable_srcInfo;		//  2015/11/10. 

				 //  2013/07/17
				 //  int										iIndex_player;				//  2013/07/17
				 PLAYER_ID										playerId;					//  2016/02/19
				 //  2015/10/01
				 unsigned  short								usPktResType;				//  2015/10/01
				 
				 //
				 DWORD											dwTickCnt_lastDrawing;		//  2009/09/10
				 				 
				 //
				 HWND											hWnd_remoteAv;				//  双击视频,可弹出独立窗口来显示的更清晰一点

				 //
				 HDRAWDIB										hDib;

				 //
				 HDC											hOffscreenDc;				//  2014/04/11
				 HBITMAP										hBitmap;
				 HBITMAP										hOldBitmap;

				 //
				 BOOL											bNeedUpdated_doPost_drawCapImages;				//  2014/04/12

				 //
				 BOOL											bResized;					//  此视频大小有变



}		 CAP_IMAGE,  CAP_image;


//
typedef  struct  __capImagesHead_t								{
				 BOOL											bResized;													//  此标志位表明需要全部重新排版。
				 //
				 int											cnt_needUpdated;											//  2014/04/12
				 HWND											hWnd_src;													//  capImage的坐标窗口
				 HWND											hWnd_notifyToDraw;
				 long											lUserData;													//  2014/04/12. 一个随意的参数
				 
				 //
				 //DWORD										dwModifiedTickCnt_images;									//  2014/11/29
				 QY_timestamp									ts_images;													//  2017/10/17

				 //
				 unsigned  short								usCnt;														//  2012/05/22. 特别注意: usCnt不标明mems的前n个有效.但是表示所有的mems里,有n个有效.所以,当枚举有效的mem时, 要(i=0;i<mycountof( mems); i++)

}		 CAP_images_head;



//  2014/10/19
typedef  struct  __capImages_t									{
				 CAP_images_head								head;
				 //
				 CAP_IMAGE										mems[CONST_maxCapImages];
}		 CAP_IMAGES,  CAP_images;


//
typedef  struct  __capImageLocation_t							{
				 CAP_RECT										rect;
}		 CAP_image_location;



//
#define		DEFAULT_usMaxCnt_capSubWnds							32

typedef  struct  __CAP_subWnd_t									{												//  2009/09/06  		
					 HWND										hWnd;
					 int										iWndContentType;
					 int										iWndContentSubType;								//  2012/04/29
					 //
					 int										iTaskId;
					 //
					 QY_MESSENGER_ID							idInfo;
					 unsigned  int								uiObjType;
					 unsigned  short							usIndex_obj;
}		 CAP_subWnd;


typedef  struct  __CAP_subWnds_t								{												//  2012/05/08
				 unsigned  short								usMaxCnt;
				 CAP_subWnd								*		pMems;
}		 CAP_subWnds;


//
typedef  struct  __zoneParam_t									{
				 int											index_subWall;									//  2009/10/04
				 int											index_zone;
				 unsigned  int									uiTranNo_zone;
				 //
				 int											index_capImage;
				 //
				 int											nRulePriority;									//  nPriority of the rule to get zoneParam

}		 ZONE_PARAM;



//
//  2014/10/02
typedef  struct  __bgWallLayoutCfg_t							{
				 //
				 unsigned  short								usRows_bg;										//  2014/10/01
				 unsigned  short								usCols_bg;										//  2014/10/01

				 //int											iW_bgWallMem;									//  2014/10/03
				 //int											iH_bgWallMem;									//  2014/10/03
								 
}		 BG_wall_layout_cfg;




//  2014/10/02
typedef  struct  __bgWallLayout_t								{
				 //
				 //unsigned  short								usRows_bg;										//  2014/10/01
				 //unsigned  short								usCols_bg;										//  2014/10/01

				 int											iW_bgWallMem;									//  2014/10/03
				 int											iH_bgWallMem;									//  2014/10/03
								 
}		 BG_wall_layout;


//
//  2017/11/02
typedef  struct  __bgWallCfg_t									{
				 //
				 unsigned  char									useBgWall;
				 //
				 unsigned  char									ucbAddBgWallToConf;
				 //
				 unsigned  char									ucbJoinInBgWall;
				 			
				 //
				 unsigned  char									ucbNeverJoinInBgWall;

				 //
				 unsigned  char									ucbAutoLayout;
				 TCHAR											bgWallFileName[256];
				 
				 //  2017/11/03
				 BG_wall_layout_cfg								bgWallLayoutCfg;
				 //
				 unsigned  short								usPollingIntervalInS;


}		 BgWall_cfg;




//
#define		DEFAULT_usPollingIntervalInS						10



//
//
//
typedef  struct  __param_getCapImages_t							{
				 //
				 BOOL											bNew;
				 //
				 ConfLayoutParam						*		pConfLayoutParam;
				 //
				 int											ii;
				 //
}		 PARAM_getCapImages;



//  2013/02/27. 
typedef  struct  __param_dcDraw_t								{				 
				 //

				 //
				 BOOL											bDlgHidden;

				 //
				 unsigned  char									ucbFixedSize;

				 //
				 BOOL											bUseDxSurface;  

				 //
				 BOOL											bModified_capImg;		//  2015/10/01	//  bModified_iIndex_player;						//  2013/07/20

				 //  2014/10/02
				 BOOL											bBgWall;
				 BG_wall_layout									bgWallLayout;
				 unsigned  short								usIndex_active;

				 //  2017/10/02
				 PARAM_getCapImages								param_getCapImages;

				 //
				 struct											{
					 unsigned  char								ucbDbgImgs;
				 }												dbgInfo;

}		 PARAM_dc_draw;

//  2013/02/17
typedef  struct  __dlgSyncFlgs_t								{
				 long											lCnt_getDlgVar;									//  2013/07/15
				 //
				 //  BOOL										bSubWndExists;									//  2011/03/28
				 BOOL											bInSequence;									//  2013/07/15
				 //

				 //  BOOL										bLocked_bQuitDlg;								//  2012/05/09				
}		 DLG_syncFlgs;


//  2012/05/08
int  initCapSubWnds(  unsigned  short  usMaxCnt,  CAP_subWnds  *  p  );
void  exitCapSubWnds(  CAP_subWnds  *  p  );


//  int  registerSubWnd(  HWND  hWnd,  int  iWndContentType,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex,  CAP_subWnds  *  p,  int  *  pIndex_subWnd  );
int  registerSubWnd(  HWND  hWnd,  int  iWndContentType,  int  iWndContentSubType,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex_obj,  CAP_subWnds  *  p,  int  *  pIndex_subWnd  );
int  closeSubWnds(  CAP_subWnds  *  p  );
HWND  findSubWnd(  CAP_subWnds  *  p,  int  iWndContentType,  int  iWndContentSubType  );
BOOL  bExists_capSubWnd(  CAP_subWnds  *  p  );

//
__declspec(  dllexport  )  int  myGetImageInfo(	unsigned  char  ucbFixedSize,					//  
					    unsigned  char	ucbAutoClip,											//  根据目标矩形自动裁剪，使目标矩形被充满
						unsigned  char  ucb3d,													//  3d显示用， 2014/11/14
						int  iW_org,  int  iH_org,  
						int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH,  
						unsigned  int  *  piW_i,  unsigned  int  *  piH_i,
						int  *  piX_src_i,  int  *  piY_src_i,  
						int  *  piX_dst,  int  *  piY_dst,  unsigned  int  *  piW_dst,  unsigned  int  *  piH_dst  );

//
__declspec(  dllexport  )  int  myGetImageInfo_2d(	unsigned  char  ucbFixedSize,				//  
					    unsigned  char	ucbAutoClip,											//  根据目标矩形自动裁剪，使目标矩形被充满
						int  iW_org,  int  iH_org,  
						int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH,  
						unsigned  int  *  piW_i,  unsigned  int  *  piH_i,
						int  *  piX_src_i,  int  *  piY_src_i,  
						int  *  piX_dst,  int  *  piY_dst,  unsigned  int  *  piW_dst,  unsigned  int  *  piH_dst  );



//
bool  bCapImgOk(CAP_IMAGE* pImg);
//
int getCnt_imgs(CAP_images* pImgs);


//
__declspec(  dllexport  )  int  getCapImagesFunc(  unsigned  char  ucbAutoClip,  unsigned  char  ucb3d,  int  iX_desc,  int  iY_desc,  int  iW_desc,  int  iH_desc,  PARAM_getCapImages  *  pParam,  CAP_images_head  *  pImgsHead,  CAP_IMAGE  *  pImgMems,  int  uiSize_pImgMem,  unsigned  int  uiMaxCnt_imgMems  );
//
__declspec(  dllexport  )  int  new_getCapImagesFunc(  unsigned  char  ucbAutoClip,  unsigned  char  ucb3d,  int  iX_desc,  int  iY_desc,  int  iW_desc,  int  iH_desc,  PARAM_getCapImages  *  pParam,  CAP_images_head  *  pImgsHead,  CAP_IMAGE  *  pImgMems,  int  uiSize_pImgMem,  unsigned  int  uiMaxCnt_imgMems  );

//
bool  isSame_capImages(CAP_IMAGES* pImgs1, CAP_IMAGES* pImgs1_int, CAP_IMAGES* pImgs2, bool  bBreakIfNotSame);

//
typedef  struct  __tmp_CapImgs_t {
				 CAP_IMAGES		imgs;
}		 tmp_CAP_IMAGES;


//
//bool  isSame_layoutCapImages_forD3d(CAP_IMAGES* pImgs1, CAP_IMAGES* pImgs1_int, CAP_IMAGES* pImgs2, bool  bBreakIfNotSame);
bool  isSame_layoutCapImages_forD3d(CAP_IMAGES* pImgs1, tmp_CAP_IMAGES* pImgs1_int, CAP_IMAGES* pImgs2, bool  bBreakIfNotSame,LPCTSTR  hint);
int refreshLayoutCapImages_forD3d(MIS_MSG_procVideo_qmc* pMsg, CAP_IMAGES* pImgs, bool* pbNeedRefreshImgs);


//
int  getCapImages(  unsigned  int  ucbAutoClip,  int  iX_desc,  int  iY_desc,  int  iW_desc,  int  iH_desc,  PARAM_getCapImages  *  pParam,  CAP_IMAGES  *  pImages  );
//
int  getCapImages_bgWall(  HWND  hCurTalk,  void  *  pCurDLG_TALK_var,  unsigned  int  ucbAutoClip,  int  iX_desc,  int  iY_desc,  int  iW_desc,  int  iH_desc,  BG_wall_layout_cfg  *  pCfg,  BG_wall_layout  *  pConfBgLayout  );


//
int  redrawImage(  HWND    hDlg,  int  idc,  int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH  );

//  
int  drawCapImages(  QY_MC  *  pQyMc,  HWND    hWnd_src,  unsigned  char  ucbAutoClip,  MIS_MSG_procVideo_qmc  *  pMsg,  int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH,  CAP_subWnds  *  pSubWnds,  ZONE_PARAM  *  pZoneParam,  CAP_IMAGES  *  pImgs,  HWND  hWnd_dst,  HDC  *  phDc_dst,  PARAM_dc_draw  *  pDcDrawParam  );

//
int  doPost_drawCapImages(  HWND  hWnd_dst,  HDC  hDc_dst,  LPARAM  lParam,  CAP_IMAGES  *  pImages  );

//  2013/03/02
#define		old_M_GetDlgItem(  hDlg,  idc  )	idc  ?  ::GetDlgItem(  hDlg,  idc  )  :  hDlg
#define		M_GetDlgItem(hDlg,hCtrl)			hCtrl  ?  hCtrl : hDlg

//
//  int  freeCapImage(  HWND    hDlg,  int  idc,  CAP_IMAGE  *  pImg  );
//  int  freeCapImageByTaskId(  HWND    hDlg,  int  idc,  int  iTaskId,  CAP_IMAGES  *  pImgs  );
//  int  freeCapImageBySth(  HWND    hDlg,  int  idc,  int  iTaskId,  QY_MESSENGER_ID	*	pIdInfo,  CAP_IMAGES  *  pImgs  );
//  int  freeCapImages(  HWND    hDlg,  int  idc,  HDC  *  phDc,  CAP_IMAGES  *  pImgs  );

int  old_freeCapImage(  HWND    hDlg,  int  idc,  CAP_IMAGE  *  pImg,  HWND  hWnd_dst,  LPCTSTR  hint  );	//  2013/03/02
int  old_freeCapImage(HWND    hDlg, HWND hWndIDC, CAP_IMAGE* pImg, HWND  hWnd_dst, LPCTSTR  hint);
int  old_freeCapImageByTaskId(  HWND    hDlg,  int  idc,  int  iTaskId,  CAP_IMAGES  *  pImgs,  HWND  hWnd_dst  );
int  old_freeCapImageBySth(  CTX_qm_thread  *  pCqt,  HWND    hDlg,  int  idc,  int  iTaskId,  QY_MESSENGER_ID	*	pIdInfo,  CAP_IMAGES  *  pImgs,  HWND  hWnd_dst  );
int  old_freeCapImages(  HWND    hDlg,  int  idc,  CAP_IMAGES  *  pImgs,  HWND  hWnd_dst,  HDC  *  phDc_dst,  LPCTSTR  hint  );
int  old_freeCapImages(HWND    hDlg, HWND  hWndIDC, CAP_IMAGES* pImgs, HWND  hWnd_dst, HDC* phDc_dst, LPCTSTR  hint);

//
int  freeCapImageByTaskId(HWND    hDlg, HWND  hCtrl, int  iTaskId, CAP_IMAGES* pImgs, HWND  hWnd_dst);

//
int  freeCapImageBySth(CTX_qm_thread* pCqt, HWND    hDlg, HWND  hCtrl, int  iTaskId, QY_MESSENGER_ID* pIdInfo, CAP_IMAGES* pImgs, HWND  hWnd_dst);

//
int  freeCapImage(HWND    hDlg, HWND  hCtrl, CAP_IMAGE* pImg, HWND  hWnd_dst);
//
//
int  freeCapImages(HWND    hDlg, HWND  hCtrl, CAP_IMAGES* pImgs, HWND  hWnd_dst, HDC* phDc_dst);





//
int  doWnd_guiMsgArrive(  void  *  pProcInfoParam,  int  index_player,  HWND  hWnd,  BOOL  bForce_displayAllFrames,  MIS_MSGU  *  pMsgBuf  );
int  doMainWnd_procVideo(  void  *  pQyMcParam,  MIS_MSG_procVideo_qmc  *  pMsg  );

//
typedef  struct  __param_getScreenRes_t		{
				 bool						bService;
}		 PARAM_getScreenRes;


//  2017/10/10
int  getScreenRes(  PARAM_getScreenRes  *  p0,  unsigned  int  *  puixScreen,  unsigned  int  *  puiyScreen  );

//
int  brushDc(  COLORREF  color,  HDC  hDc,  int  x,  int  y,  int  iW,  int  iH  );





#endif  //  }


