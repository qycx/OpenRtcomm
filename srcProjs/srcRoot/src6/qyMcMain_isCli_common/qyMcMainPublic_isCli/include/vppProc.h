
#ifndef  __vppProc_h__
#define  __vppProc_h__	//  {

//
#include	"addTxt.h"

//
typedef  struct  __vppHelpInfo_t				{
				 //
				 char						*	pBuf;
				 unsigned  int					uiBufSize;
				 
				 //
				 struct							{
					 BOOL						bProcessed_step0;
					 BOOL						bProcessed_step1;
					 BOOL						bProcessed_step2;
				 }								procFlgs;
				 //
				 unsigned  int					uiCnt_vpp0;
				 
				 //
#ifdef  __DEBUG__
				 char  buf[100];
#endif

}		 VPP_helpInfo;

//
#define		M_getMutexName_vpp( tMutexName, cntof_tMutexName,pSharedObj,  index  )  \
	_sntprintf(tMutexName, cntof_tMutexName, _T("%s%s%d-%d"), pQyMc->appParams.appObjPrefix, CONST_mutexNamePrefix_syncVpp, pSharedObj->index_sharedObj,  index);



//
#define		MAX_vpp_helpInfos					24

//
typedef  struct  __ctx_vpp_t					{
				 //
				 unsigned  char					ucbSingleThread_vpp;

				 //
				 CTX_addTxt						addTxt;
				 //
				 struct							{
					 BITMAPINFOHEADER			bih_rgb;
					 char					*	pBuf;
					 unsigned  int				uibufSize;
				 }								resize;
				 //
				 struct							{
					 //  2011/12/05
					 BITMAPINFOHEADER			bih_vpp;
					 int						iVppBufSize;
					 char					*	pVppBuf;
				 }								vpp;

				 //  2015/05/07
				 QY_qThreadProcInfo_common		vppThread1_proc;			
				 QY_qThreadProcInfo_common		vppThread2_beforeEnc;		

				 //
				 int							iIndex_sharedObj;

				 //
				 unsigned  char					ucCnt_vppHelpInfos;
				 VPP_helpInfo				*	pVppHelpInfos;

				 //
				 unsigned  int					uiCnt_vpp0;
				 unsigned  int					uiCnt_vpp1;
				 unsigned  int					uiCnt_vpp2;

				 //
				 QDC_OBJ_INFO					qoi_decMJPG;

				 //
				 VIDEO_input_info1				inputInfo;

				 //
				 struct							{
					 int						iW_fake;
					 int						iH_fake;
					 bool						bLegal;
					 //
					 int						iFourcc_fake;
					 //
					 char					*	pBuf;
					 int						bufSize;

					 //
					 bool						bDone;

				 }								fakePic;

				 //
}		 CTX_vpp;

//
#define		CONST_mutexNamePrefix_syncVpp		_T(  "mtxSyncVpp"  )

//
 int  old_doVpp(  MC_VAR_common  *  pProcInfo,  CTX_vpp  *  pCtx,  QY_SHARED_OBJ  *  pSharedObj,  CAP_procInfo_bmpCommon  *  pCapBmp,  myDRAW_VIDEO_DATA  *  p,  int  pktLen  );
 int  chkVppBuf(  CTX_vpp  *  pCtx,  CAP_procInfo_bmpCommon  *  pCapBmp,  int  iW_vpp,  int  iH_vpp,  BOOL  bNeedVppBuf,  int  iFourcc  );
  int  rgb24ToVppBuf(  unsigned  char  *  rgb,  unsigned  char  *  yuv,  int  width,  int  height,  BOOL  bFlipImg,  int  iFourcc  );
  int  chkResizeBuf(  CTX_vpp  *  pCtx,  CAP_procInfo_bmpCommon  *  pCapBmp  );

//
int  doVpp0(  MC_VAR_common  *  pProcInfo,  CTX_vpp  *  pCtx,  QY_SHARED_OBJ  *  pSharedObj,  CAP_procInfo_bmpCommon  *  pCapBmp,  myDRAW_VIDEO_DATA  *  p,  int  pktLen  );
int  doVpp1(  MC_VAR_common  *  pProcInfo,  CTX_vpp  *  pCtx,  QY_SHARED_OBJ  *  pSharedObj,  CAP_procInfo_bmpCommon  *  pCapBmp,  myDRAW_VIDEO_DATA  *  p,  int  pktLen  );
int  doVpp2(  MC_VAR_common  *  pProcInfo,  CTX_vpp  *  pCtx,  QY_SHARED_OBJ  *  pSharedObj,  CAP_procInfo_bmpCommon  *  pCapBmp,  myDRAW_VIDEO_DATA  *  p,  int  pktLen  );

//
int  addTxtToPic(  QY_MC  *  pQyMc,  CTX_addTxt  *  pCtx,  unsigned  char  ucbDaemonDemo,  LPCTSTR  videoHint,  DWORD  dwTickCnt_start,  QY_SHARED_OBJ  *  pSharedObj,  COMPRESS_VIDEO  *  pCompressVideo,  BITMAPINFO  *  pBmi_pic,  char  *  pPicBuf  );
//int  addTxtToPic_screen(  void  *  pCTX_addTxt,  unsigned  char  ucbDaemonDemo,  int  iW_pic,  int  iH_pic,  HDC  hMemDC  );

//
int do_fakePic(CTX_vpp* pCtx, int iW_int, int iH_int, int  iFourcc_dst,  char* imgBuf_dst, int  impBufSize_dst);


#endif  //  }



