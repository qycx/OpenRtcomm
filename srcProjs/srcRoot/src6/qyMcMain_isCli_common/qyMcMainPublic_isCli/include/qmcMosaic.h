

#ifndef  __qmcMosaic_h__
#define  __qmcMosaic_h__	//  {


#include	"qmcShareDynBmp.h"
#include	"isCliD3dDefs.h"



//
typedef  struct {
				HANDLE						hThread;
				DWORD						dwThreadId;
	
	
				//
				HANDLE						hEvent_syncQuit;

				//
}		 QMC_mosaic_thread;


typedef  struct  __qmcMosaicMaker_t			{
				 struct 					{
					 int					iTaskId;	
				 }							param;
				 
				 //
				 SHARE_dyn_bmp				video;
				 SHARE_dyn_bmp				resource;	
				 //
				 BOOL						bQuit;				//  让readRtt线程退出标志
				 //
				 //HANDLE						hEvent_syncQuit;
				 //
				 unsigned  char				ucCnt_threads;
				 QMC_mosaic_thread			threads[MAX_talkerMosaic_threads];

				 //
				 struct   					{

				 }							status;

				 //  2016/02/14
				 BOOL						bInited;

}		 QMC_mosaic_maker;


//
//  2015/11/18
#define		M_getEvtName_mosaic(  iTaskId,  index_mosaic,  evtName,  evtNameCnt  )					_sntprintf(  evtName,  evtNameCnt,  _T(  "%s%s%d-%d"  ),  pQyMc->appParams.appObjPrefix,  _T(  "MosaicEvt"  ),  iTaskId,  index_mosaic  )
//#define		M_getMutexName_mosaic(  iTaskId,  index_mosaic,  mutexName,  mutexNameCnt  )			_sntprintf(  mutexName,  mutexNameCnt,  _T(  "%s%s%d-%d"  ),  pQyMc->appParams.appObjPrefix,  _T(  "MosaicMtx"  ),  iTaskId,  index_mosaic  )

//
//
int  stopMosaicThreads(  QMC_mosaic_maker  *  pMosaic  );
int  setFlg_inConfMosaic(  HWND  hDlg,  int  iWndContentType,  int  iIndex_sharedObj,  int  iIndex_sharedObjUsr  );
//
//  2014/10/30
int  makeMosaicStream(  HWND  hDlg,  int  iTaskId,  int  level,  AV_COMPRESSOR_CFG  *  pCompressor_conf,  AV_COMPRESSOR_CFG  *  pCompressor_resource,  int  iFourcc_resource,  QMC_mosaic_maker  *  pMosaic  );

//




//
#endif  //  }



