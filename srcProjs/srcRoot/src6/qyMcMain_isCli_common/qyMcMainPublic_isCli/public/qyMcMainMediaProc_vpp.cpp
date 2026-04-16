

#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"
#include	"tmpCeLib.h"
#include	"qmcVideoCapture.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#include	"qmcCmdProc.h"


#include	"vppProc.h"
#include	"qmcCfg.h"
//#include	"tmpFfmpegPublic.h"
#include <hgCommProc.h>
#include	"imgFunc_open.h"
#include <tmpFfmpegPublic.h>
#include <dynFuncs.h>


//
void  CTX_vpp_free(  CTX_vpp  *  pCtx  )
{
	//  2015/05/07
	int  i;
	for  (  i  =  0;  i  <  pCtx->ucCnt_vppHelpInfos;  i  ++  )  {
		 VPP_helpInfo  *  pMem  =  &pCtx->pVppHelpInfos[i];
		 MACRO_safeFree(  pMem->pBuf  );
	}
	MACRO_safeFree(  pCtx->pVppHelpInfos  );

	//  2013/03/11
	 CTX_addTxt_free(  &pCtx->addTxt  );
	 //  2014/04/24
	 MACRO_safeFree(  pCtx->resize.pBuf  );

	 MACRO_safeFree(  pCtx->vpp.pVppBuf  );

	 //
	 if  (  pCtx->qoi_decMJPG.var.pObj  )  {
		 qdcExitDecompressVideo_ffmpeg(  &pCtx->qoi_decMJPG  );
	 }

	 //
	 MACRO_safeFree(pCtx->fakePic.pBuf);

	 //
	 return;
}


//
int  chkResizeBuf(  CTX_vpp  *  pCtx,  CAP_procInfo_bmpCommon  *  pCapBmp  )
{
	int  iErr  =  -1;

	if  (  !pCtx->resize.pBuf  ||  pCtx->resize.bih_rgb.biWidth  !=  pCapBmp->compressVideo.vh_decompress.bih.biWidth  ||  pCtx->resize.bih_rgb.biHeight  !=  pCapBmp->compressVideo.vh_decompress.bih.biHeight  )  {							
		MACRO_safeFree(  pCtx->resize.pBuf  );
		makeBmpInfoHeader_rgb(  24,  pCapBmp->compressVideo.vh_decompress.bih.biWidth,  pCapBmp->compressVideo.vh_decompress.bih.biHeight,  &pCtx->resize.bih_rgb  );
		pCtx->resize.uibufSize  =  pCtx->resize.bih_rgb.biSizeImage;
		pCtx->resize.pBuf  =  (  char  *  )mymalloc(  pCtx->resize.uibufSize  );
		if  (  !pCtx->resize.pBuf  )  goto  errLabel;															   								  							
	}

	//
	iErr  =  0;
errLabel:
	return  iErr;
}



//  2014/07/21
int  chkVppBuf(  CTX_vpp  *  pCtx,  CAP_procInfo_bmpCommon  *  pCapBmp,  int  iW_vpp,  int  iH_vpp,  BOOL  bNeedVppBuf,  int  iFourcc  )
{
	int  iErr  =  -1;

	if  (  !iW_vpp  ||  !iH_vpp  )  return  -1;

	//	
	if  (  bNeedVppBuf  )				  
	{
		if  (  !pCtx->vpp.pVppBuf  ||  pCtx->vpp.bih_vpp.biWidth  !=  iW_vpp  ||  pCtx->vpp.bih_vpp.biHeight  !=  iH_vpp  )  {	
			MACRO_safeFree(  pCtx->vpp.pVppBuf  );			
			//
			switch  (  iFourcc  )  {
					case  CONST_fourcc_YV12:
						  makeBmpInfoHeader_yv12(  12,  iW_vpp,  iH_vpp,  &pCtx->vpp.bih_vpp  );
						  break;
					case  CONST_fourcc_I420:						
						  makeBmpInfoHeader_i420(  12,  iW_vpp,  iH_vpp,  &pCtx->vpp.bih_vpp  );
						  break;
					case  CONST_fourcc_NV12:
						  makeBmpInfoHeader_nv12(12, iW_vpp, iH_vpp, &pCtx->vpp.bih_vpp);
						  break;
					default:
							goto  errLabel;
			}

			
			//
			pCtx->vpp.iVppBufSize  =  pCtx->vpp.bih_vpp.biSizeImage;
			pCtx->vpp.pVppBuf  =  (  char  *  )mymalloc(  pCtx->vpp.iVppBufSize  );
			if  (  !pCtx->vpp.pVppBuf  )  goto  errLabel;					  
		}				  
		}
	else  {
		  MACRO_safeFree(  pCtx->vpp.pVppBuf  );
	}

	iErr  =  0;
errLabel:
	return  iErr;
}

//
 int  rgb24ToVppBuf(  unsigned  char  *  rgb,  unsigned  char  *  yuv,  int  width,  int  height,  BOOL  bFlipImg,  int  iFourcc  )
 {
	 QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();

	 switch  (  iFourcc  )  {
			 case  CONST_fourcc_YV12:
				   return  pQyMc->rgb24ToYv12(  rgb,  yuv,  width,  height,  bFlipImg  );
				   break;
			 case  CONST_fourcc_I420:
				   return  pQyMc->rgb24ToI420(  rgb,  yuv,  width,  height,  bFlipImg  );
				   break;
			 case  CONST_fourcc_NV12:
				 return  bgr24ToNv12(rgb, yuv, width, height,bFlipImg);
				   break;

			 default:
					break;
	 }
	 return  -1;
}


 


 //
 int do_fakePic(CTX_vpp* pCtx, int iW_int, int iH_int, int  iFourcc_dst, char* imgBuf_dst, int  impBufSize_dst)
 {
	 int  iErr = -1;

	 CCtxQyMc* pQyMc = g_pQyMc;


	 do {
		 BOOL  bLegal = true;
		 MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
		 //如果是非法用户   也需要关闭摄像头
		 if (pQyMc->appParams.bSmZy) {

			 if (
				 pProcInfo->legal_info.isOk &&
				 !pProcInfo->legal_info.bLegal)
			 {
				 //
				 bLegal = false;

			 }
		 }

	
		 
		 
		 //
		 if (!pCtx->fakePic.bDone
			 || iW_int != pCtx->fakePic.iW_fake
			 || iH_int != pCtx->fakePic.iH_fake
			 ||  bLegal  !=  pCtx->fakePic.bLegal
			 )
		 {
			 MACRO_safeFree(pCtx->fakePic.pBuf);

			 //
			 int bits_int = 24;
			 int imgSize = M_sizeImage_open(bits_int, iW_int, iH_int);
			 pCtx->fakePic.pBuf = (char*)mymalloc(imgSize);
			 if (!pCtx->fakePic.pBuf) continue;

			 //
			 showInfo_open0(0, 0, _T("do_fakePic.malloc"));

			 //
			 char* rgb_int = pCtx->fakePic.pBuf;
			 //
			 TCHAR  fakePicFileName[MAX_PATH];
			 TCHAR* CONST_fakePic = (TCHAR*)_T("fakePic.bmp");
			 if (!bLegal)  CONST_fakePic = (TCHAR*)_T("illegal.bmp");
			 //
			 _sntprintf(fakePicFileName, mycountof(fakePicFileName), _T("%s\\%s\\%s"), pQyMc->cfg.installDir, _T(CONST_qyResSubDir), CONST_fakePic);
			 //  c:\\tttbbb\\test\\k.bmp
			 //
			 if (getFakePic(fakePicFileName, bits_int, iW_int, iH_int, rgb_int, imgSize)) {
				 showInfo_open0(0, 0, _T("vpp: getFakePic failed"));
				 break;
			 }
			 //
			 pCtx->fakePic.iW_fake = iW_int;
			 pCtx->fakePic.iH_fake = iH_int;
			 pCtx->fakePic.bLegal = bLegal;
			 pCtx->fakePic.bufSize = imgSize;
			 pCtx->fakePic.bDone = true;
		 }

		 //
#ifdef  __DEBUG__
		 if (0) {
			 BITMAPINFOHEADER  bih;
			 makeBmpInfoHeader_rgb(24, iW_int, iH_int, &bih);
			 //mySaveBitmap(&bih, pCtx->fakePic.pBuf, false, _T("c:\\tttbbb\\test\\test.bmp"));
		 }
#endif

		 switch  (  iFourcc_dst  )  {
				 case  CONST_fourcc_I420:		 
					   //		 
					   rgb24ToI420((unsigned  char*)pCtx->fakePic.pBuf, (unsigned  char*)imgBuf_dst, iW_int, iH_int, false);
					   break;
				 case  0:
						memcpy(imgBuf_dst, pCtx->fakePic.pBuf, pCtx->fakePic.bufSize);
						break;
				 default:
					    showInfo_open0(0, 0, _T("do_fakePic failed, unprocessed iFourcc_dst "));
						goto  errLabel;
						break;
						
		 }

		 //
#ifdef  __DEBUG__
		 if (0) {
			 //mySaveYv12(iW_int, iH_int, imgBuf_dst, false, _T("c:\\tttbbb\\test\\testyv.bmp"));
		 }
#endif

		 //
		 iErr = 0;

	 } while (false);


 errLabel:


	 return  iErr;
 }





//
 //  2011/07/15, 每次读取若干包然后一次性压缩
 DWORD WINAPI mcThreadProc_vpp( LPVOID lpParameter )
{
	 int							iIndex_sharedObj			=	(  int  )lpParameter;

	 QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();
	 if  (  !pQyMc  )  {
		 return  -1;
	 }
	 CCtxQmc				*	pProcInfo					=	(CCtxQmc*)pQyMc->get_pProcInfo(  );
	 if (  !pProcInfo  )  return  -1;
	 QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	 if  (  !pQmcCfg  )  return  -1;

	 QY_SHARED_OBJ				*	pSharedObj					=	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	 if  (  !pSharedObj  )  return  -1;

	 CAP_procInfo_bmpCommon		*	pCapProcInfo				=  (  CAP_procInfo_bmpCommon  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
	 if  (  !pCapProcInfo  )  return  -1;

	 //  2013/03/10
	 CTX_vpp						ctx_vpp;
	 memset(  &ctx_vpp,  0,  sizeof(  ctx_vpp  )  );
	 ctx_vpp.iIndex_sharedObj  =  iIndex_sharedObj;

	 //
#ifdef  __DEBUG__
		#if  0
			ctx_vpp.ucbSingleThread_vpp  =  TRUE;
			traceLog((TCHAR*)  _T(  "TEST: singThread_vpp is true"  )  );
		#endif
#endif

	 //
	 CTX_vpp  *  pCtx  =  &ctx_vpp;

	 //  2010/12/28
	 pCapProcInfo->compressVideo.debugInfo.nStep  =  101;

	 //  2009/12/24
#if  0
	 QM_SHM_CMD					*	pShmCmd						=	NULL;
	 QM_SHM_DATA				*	pShmData					=	NULL;
	 TCHAR							mutexName_syncShmData[64]	=	_T(  ""  );
	 //pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pSharedObj->iIndex_shmCmd  );
	 pShmCmd  =  (  QM_SHM_CMD  *  )pProcInfo->getQmShmCmdByIndex(  pSharedObj->iIndex_shmCmd  );
	 if  (  !pShmCmd  )  {
		 return  -1;
	 }
	 pShmData  =  (  QM_SHM_DATA  *  )pSharedObj->dataShm.pBuf;
	 _sntprintf(  mutexName_syncShmData,  mycountof(  mutexName_syncShmData  ),  _T(  "%s%u"  ),  CONST_mutexName_qm_syncData_v,  pSharedObj->uiTranNo  );
#endif

	 //
	 DWORD							dwThreadId					=	GetCurrentThreadId(  );

	 myDRAW_VIDEO_DATA				pkts[CONST_pkts_vpp];
	 unsigned  int					uiLens[CONST_pkts_vpp];		//  要增加一个qGetMsgs，将pPkts和pktLens作为参数输入。2011/07/15
	 int							nLens						=	mycountof(  uiLens  );		//  一次最多处理的包数。
	 int							i;
	 int							nPkts;						//								pPkts[]中有几个包是有效的。 2011/07/15

	 MIS_CNT					*	pMisCnt						=	(  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );
	 if  (  !pMisCnt  )  return  -1;	 	 

	 CQyMalloc						mallocObj_pMsgBuf;
	 MIS_MSGU					*	pMsgBuf						=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsgBuf  )  return  -1;


	 DWORD							dwTickCnt;

	 //  2010/09/18
	 //  int							tmpiRet;
	 BOOL							tmpbErr;
	 TCHAR							tBuf[128];


	 //
#ifdef  __DEBUG__
	 traceLogA(  (char*)  "mcThreadProc_vpp %S enters",  pCapProcInfo->vppThread.q2.cfg.name  );
#endif

	 //
	 pCapProcInfo->vppThread.bQuit  =  FALSE;
	 pCapProcInfo->vppThread.bRunning  =  TRUE;


	 //  2015/05/07
	 pCtx->ucCnt_vppHelpInfos  =  MAX_vpp_helpInfos;  
	 int  size  =  pCtx->ucCnt_vppHelpInfos  *  sizeof(  VPP_helpInfo  );
	 pCtx->pVppHelpInfos  =  (  VPP_helpInfo  *  )mymalloc(  size  );
	 if  (  !pCtx->pVppHelpInfos  )  goto  errLabel;
	 memset(  pCtx->pVppHelpInfos,  0,  size  );




	 ////////////////
	 //  2015/05/06
	 GENERIC_Q_CFG  tmpCfg;
	 TCHAR  tName[128];
	 CAP_procInfo_bmpU* pCapBmp; pCapBmp = (CAP_procInfo_bmpU*)pCapProcInfo;
	 GENERIC_Q_cfgEx  qCfgEx;
	 DWORD  dwThreadDaemonId;

		  //		
		  memcpy(  &tmpCfg,  &pQmcCfg->vppQ,  sizeof(  tmpCfg  )  );
		  _sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s1-%d"  ),  tmpCfg.name,  pSharedObj->uiTranNo  );
		  _sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s1-%d"  ),  tmpCfg.mutexName_prefix,  pSharedObj->uiTranNo  );
		  _sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s1-%u"  ),  CONST_evtName_qm_vpp,  pSharedObj->uiTranNo  );
		  if  (  ctx_vpp.vppThread1_proc.bQInited  )  {
			  traceLog((TCHAR*)  _T(  "startQThreadToShareAv failed, vppThread1_proc.bQInited is  already true."  )  );
			  goto  errLabel;
		  }
		  //  if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapBmp->vppThread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myDRAW_VIDEO_DATA,  &pCapBmp->vppThread.q2  )  )  goto  errLabel;
		  memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );
		  memcpy(  &qCfgEx.common,  &tmpCfg,  sizeof(  qCfgEx.common  )  );
		  qCfgEx.pfQElemNewEx  =  mallocMemory;
		  qCfgEx.pfQElemNew  =  mymalloc;
		  qCfgEx.pfQElemFreeEx  =  freeMemory;
		  qCfgEx.pfQElemFree  =  myfree;
		  qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_myDRAW_VIDEO_DATA;
		  if  (  initQyQ2(  &qCfgEx,  &pQyMc->cfg.rwLockParam,  mycountof(  ctx_vpp.vppThread1_proc.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  &ctx_vpp.vppThread1_proc.q2  )  )  goto  errLabel;
		  ctx_vpp.vppThread1_proc.bQInited  =  TRUE;
		  
		  //  2015/05/06
		  memcpy(  &tmpCfg,  &pQmcCfg->vppQ,  sizeof(  tmpCfg  )  );
		  _sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s2-%d"  ),  tmpCfg.name,  pSharedObj->uiTranNo  );
		  _sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s2-%d"  ),  tmpCfg.mutexName_prefix,  pSharedObj->uiTranNo  );
		  _sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s2-%u"  ),  CONST_evtName_qm_vpp,  pSharedObj->uiTranNo  );
		  if  (  ctx_vpp.vppThread2_beforeEnc.bQInited  )  {
			  traceLog((TCHAR*)  _T(  "startQThreadToShareAv failed, vppThread2_beforeEnc.bQInited is  already true."  )  );
			  goto  errLabel;
		  }
		  //  if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pCapBmp->vppThread.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myDRAW_VIDEO_DATA,  &pCapBmp->vppThread.q2  )  )  goto  errLabel;
		  memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );
		  memcpy(  &qCfgEx.common,  &tmpCfg,  sizeof(  qCfgEx.common  )  );
		  qCfgEx.pfQElemNewEx  =  mallocMemory;
		  qCfgEx.pfQElemNew  =  mymalloc;
		  qCfgEx.pfQElemFreeEx  =  freeMemory;
		  qCfgEx.pfQElemFree  =  myfree;
		  qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_myDRAW_VIDEO_DATA;
		  if  (  initQyQ2(  &qCfgEx,  &pQyMc->cfg.rwLockParam,  mycountof(  ctx_vpp.vppThread2_beforeEnc.q2.hEvents  ),  CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName,  &ctx_vpp.vppThread2_beforeEnc.q2  )  )  goto  errLabel;
		  ctx_vpp.vppThread2_beforeEnc.bQInited  =  TRUE;



		  //  2015/05/06
		  if  (  !ctx_vpp.vppThread1_proc.hThread  )  {
			  //
			  ctx_vpp.vppThread1_proc.bQuit  =  FALSE;			
			  ctx_vpp.vppThread1_proc.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_vpp1_proc,  (  LPVOID  )&ctx_vpp,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
			  if  (  !ctx_vpp.vppThread1_proc.hThread  )  goto  errLabel;					
			  ctx_vpp.vppThread1_proc.dwThreadId  =  dwThreadDaemonId;			
			  if  (  ResumeThread(  ctx_vpp.vppThread1_proc.hThread  )  ==  -1  )  goto  errLabel;									 
		  }
		  
		  //  2015/05/06
		  if  (  !ctx_vpp.vppThread2_beforeEnc.hThread  )  {
			  //
			  ctx_vpp.vppThread2_beforeEnc.bQuit  =  FALSE;			
			  ctx_vpp.vppThread2_beforeEnc.hThread  =  CreateThread(  NULL,  0,  mcThreadProc_vpp2_beforeEnc,  (  LPVOID  )&ctx_vpp,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
			  if  (  !ctx_vpp.vppThread2_beforeEnc.hThread  )  goto  errLabel;					
			  ctx_vpp.vppThread2_beforeEnc.dwThreadId  =  dwThreadDaemonId;			
			  if  (  ResumeThread(  ctx_vpp.vppThread2_beforeEnc.hThread  )  ==  -1  )  goto  errLabel;									 
		  }



	 //  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s, %I64u starts"  ),  pPlay->q2.cfg.name,  pPlayer->idInfo_recorder.ui64Id  );
	 
	 //	
	 //	
		  int totalPkts; totalPkts = 0;
		  int totalPkts_lastOk; totalPkts_lastOk = 0;


	 /////////////////

	 for  (  ;  !pCapProcInfo->vppThread.bQuit;  )  {
		  
		  //  2010/12/28
		  pCapProcInfo->compressVideo.debugInfo.nStep  =  105;

		  //
		  DWORD  dwEvt  =  MsgWaitForMultipleObjects(
							pCapProcInfo->vppThread.q2.cfg.usCnt_hEvents,	//  mycountof(  pPlay->hEvents  ),				// Number of events.
							 pCapProcInfo->vppThread.q2.hEvents,							// Location of handles.
                             FALSE,										// Wait for all?
                             5000,									// How long to wait?
                             0  );										// Any message is an 
																		// event.
		  if  (  dwEvt  ==  WAIT_FAILED  )  goto  errLabel;
	      //
		  dwTickCnt  =  GetTickCount(  );

		  if  (  dwEvt  !=  WAIT_TIMEOUT  )  {
			  dwEvt -= WAIT_OBJECT_0;
			  switch  (  dwEvt  )  {
					  case  0:
						     //  dwTickCnt_lastData  =  dwTickCnt;		//  audio data received
						       //  traceLogA(  (char*)  "mcThreadProcInfo_vpp: event 0."  );
							 break;
					  case  1:
						     traceLogA(  (char*)  "mcThreadProcInfo_vpp: event 1."  );
							 break;
					  default:
						     traceLogA(  (char*)  "unknown event"  );	
		  					 goto  errLabel;
							 break;
			  }
		  }

		  //
#ifdef   __DEBUG__
#endif


		  //
		  for  (  ;  !pCapProcInfo->vppThread.bQuit;  )  {

			   //  2011/07/15, 先将pkts清空,nPkts 赋 0
			   nPkts  =  0;
			  {
				  CQyMalloc		mallocObj_tmpPkts[CONST_pkts_vpp];

				  if  (  !isQ2Empty(  &pCapProcInfo->vppThread.q2  )  )  {		//  这里要将 qGetMsg 改成 qGetMsgs...

					  //  pktLen  =  uiBufSize;  
					  nLens  =  mycountof(  uiLens  );
					  //  2014/04/10
					  if  (  q2GetMsgPkg(  &pCapProcInfo->vppThread.q2,  (  void  *  )pkts,  sizeof(  pkts  ),  (  unsigned  int  *  )uiLens,  (  unsigned  int  *  )&nLens,  _T(  "vpp"  ))) {
						  break;			   						  
					  }

					  for  (  i  =  0;  i  <  nLens;  i  ++  )  {
						   nPkts  +=  uiLens[i]  /  sizeof(  pkts[0]  );
						   if  (  uiLens[i]  %  sizeof(  pkts[0]  )  )  {
							   #ifdef  __DEBUG__
									   traceLog((TCHAR*)  _T(  "vpp: uiLen err"  )  );
									   assert(  0  );
							   #endif
						   }
					  }
					  
					  tmpbErr  =  FALSE;	//  注意：这里如果attach出错，要继续attach, 但是最后要continue. 以防止pPkts[i]没有机会释放内存
					  for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
						   if  (  pkts[i].memory.m_pBuf  )  {
							   if  (  mallocObj_tmpPkts[i].attach(  &pkts[i].memory  )  )  {
								   traceLogA(  (char*)  "mcThreadProc_vpp: mallocObj.attach failed"  );
								   freeMemory(  &pkts[i].memory  );  
								   tmpbErr  =  TRUE;			   
							   }					  
						   }
					  }
					  if  (  tmpbErr  )  continue;

					  
				  }

				  //
				  if  (  !nPkts  )  {
					  #ifdef  __DEBUG__
							  //assert(  0  );			//  应该不能运行到这里
							  //traceLog((TCHAR*)  _T(  "mcThreadProc_vpp: no pkts read."  )  );
					  #endif
					  break;
				  }

				  //  traceLogA(  (char*)  "playVideo: msg reaved, pktLen %d, dataLen %d",  pktLen,  pPkt->head.uiLen  );
				  #ifdef  __DEBUG__
						  #if  0
							  TCHAR  tBuf[128];
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "vpp: nPkts %d. %s"  ),  nPkts,  pCapProcInfo->vppThread.q2.cfg.name  );
							  showInfo_open0(  0,  0,  tBuf  );
						  #endif
				  #endif

				  //
				  tmpbErr  =  FALSE;
				  //
				  if (0) {
					  for (i = 0; i < nPkts; i++) {
						  //
						  //
						  if (pkts[i].uiSize_dec < pCapProcInfo->compressVideo.vh_decompress.bih.biSizeImage) {
#ifdef  __DEBUG__
							  traceLogA((char*)("mcThreadProc_vpp err: pkt.uiSize_dec %d <  sizeImage %d. skipped"), pkts[i].uiSize_dec, pCapProcInfo->compressVideo.vh_decompress.bih.biSizeImage);
#endif
							  qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("mcThreadProc_vpp err: pkt.uiSize_dec %d !=  sizeImage %d. skipped"), pkts[i].uiSize_dec, pCapProcInfo->compressVideo.vh_decompress.bih.biSizeImage);
							  tmpbErr = TRUE;
							  break;
						  }
					  }
				  }
				  //
				  if  (  tmpbErr  )  continue;

				  //
				   #ifdef  __DEBUG__
						   #if  10
								//  traceLogA(  (char*)  "mcThreadProc_vpp: pkt.SampleTime %d",  pPkt->head.uiSampleTimeInMs  );				  
								//  traceLog((TCHAR*)  _T(  "mcThreadProc_vpp: nLens %d,  nPkts %d"  ),  nLens,  nPkts  );
								M_pkts_showNo_vpp(  pkts,  nPkts  );
								//
								if  (  pSharedObj->bSlave  )  {
									int  i;
									i  =  0;
								}
								//
								#if  0
								TCHAR  tBuf[128];
								for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
									_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "thread_vpp: pkt %d"  ),  pkts[i].head.uiSampleTimeInMs  );
									showInfo_open0(  0,  0,  tBuf  );
								}
								#endif
								//
						   #endif
				   #endif


				   //
				   
				   //  
				   for  (  i  =  0;  i  <  nPkts;  i  ++  )  {

					   //
					   totalPkts++;


					   //  2016/04/27
					   if  (  pSharedObj->bSlave  )  {
						   //
						   TCHAR  ttBuf[128]  =  _T(  ""  );

						   //
						   if  (  setPktInputInfo(  pProcInfo,  &ctx_vpp.inputInfo,  pCapProcInfo->compressVideo.usFrames_perSecond_expected,  FALSE,  NULL,  mynull,  NULL  )  )  {
							   //
							   #ifdef  __DEBUG__	//  2016/04/27
								   #if  0
										_sntprintf(  ttBuf,  mycountof(  ttBuf  ),  _T(  "slave pkt skipped"  )  );					   
										showInfo_open0(  0,  0,  ttBuf  );
								   #endif
							   #endif
							   //
							   continue;
						   }

						   }
					   else {

						   //
						   unsigned  short  usFps = pCapProcInfo->compressVideo.usFrames_perSecond_expected;
						   //
						   int  nQNodes_vpp = getQ2Nodes(&pCapProcInfo->vppThread.q2);
						   //
#if 0
						   if (nQNodes_vpp > usFps)  usFps = usFps / 6;
						   else  if (nQNodes_vpp > usFps * 3 / 2)  usFps = usFps / 3;
						   else  if (nQNodes_vpp > usFps / 3)  usFps = usFps / 2;
#endif
						   //
						   if (!usFps)  usFps = 1;
						   //
#if 0
						   _sntprintf(tBuf, mycountof(tBuf), _T("vpp: %s. nQNodes_vpp %d. fps %d. nPkts %d. %dx%d"), pCapProcInfo->vppThread.q2.cfg.name, nQNodes_vpp, (int)usFps, nPkts, pCapProcInfo->vh_org.bih.biWidth, pCapProcInfo->vh_org.bih.biHeight);
						   //
						   bool  bNoSkip;
						   bNoSkip = false;
						   if (pCapBmp->common.uiType == CONST_capType_mosaic) {
							   bNoSkip = true;
						   }
						   //
						   Param_setPktInputInfo  param;
						   memset(&param, 0, sizeof(param));
						   param.uiCapType = pCapBmp->common.uiType;
						   param.uiCapSubtype = pCapBmp->common.uiSubtype;
						   //
						   if (setPktInputInfo(pProcInfo, &ctx_vpp.inputInfo, usFps, bNoSkip, &pkts[i], &param, tBuf)) {
							   //
							   if (pCapBmp->common.uiType == CONST_capType_mosaic) {
								   int  ii = 0;
								   TCHAR  ttBuf[128];
								   //
								   _sntprintf(ttBuf, mycountof(ttBuf), _T("vpp: pkt skipped"));
								   showInfo_open0(0, 0, ttBuf);
							   }
							   //
							   continue;
						   }
#endif
						   //
#ifdef  __DEBUG__
						   if (pProcInfo->cfg.debugStatusInfo.ucbPrint_lPktId_alloc) {
							   _sntprintf(tBuf, mycountof(tBuf), _T("vpp.l656: pkt.lAlloc %d. nQNodes_vpp %d"), pkts[i].lPktId_alloc, nQNodes_vpp);
							   showInfo_open(0, 0, 0, tBuf);
						   }
#endif 
						   //
						   Param_bPktSkipped  param = { 0 };
						   //
						   int nPkts_left = nPkts - i;
						   bool b4k = is4k(pkts[0].bih.biWidth, pkts[0].bih.biHeight);
						   unsigned  __int64 nFactor = 0;
						   if (bPktSkipped(&param,  CONST_nWhere_vpp,  usFps, 0, nQNodes_vpp, totalPkts, nPkts_left,  b4k,  &totalPkts_lastOk,  &nFactor)) {
							   //
							   if (0) {
								   _sntprintf(tBuf, mycountof(tBuf), _T("vpp: fps %d, totalPkts %d, nFactor %I64u, nQNodes %d, skipped"), (int)usFps, totalPkts, nFactor, nQNodes_vpp);
								   showInfo_open0(0, 0, tBuf);
							   }
							   //
							   continue;
						   }

						   //
						   int nQNodes_encQ = getQ2Nodes(&pCapProcInfo->thread.q2);
						   if (nQNodes_encQ > 10) {
							   nFactor = 0;
							   _sntprintf(tBuf, mycountof(tBuf), _T("vpp.encQ: fps %d, nQNodes %d"), (int)usFps, nQNodes_encQ);
							   if (0) {
								   showInfo_open0(0, 0, tBuf);
							   }
						   }					     
					   }


					   //  
					   tmpbErr  =  FALSE;
					   //					   
					    if  (  pCtx->ucbSingleThread_vpp  )  {
						    if  (  old_doVpp(  pProcInfo,  &ctx_vpp,  pSharedObj,  pCapProcInfo,  &pkts[i],  sizeof(  pkts[i]  )  )  )  {
								#ifdef  __DEBUG__
										traceLog((TCHAR*)  _T(  "doVpp failed"  )  );
								#endif
								tmpbErr  =  TRUE;
								break;
							}
							//
							}
						else  {  //  把数据格式转成rgb.
						      if  (  doVpp0(  pProcInfo,  &ctx_vpp,  pSharedObj,  pCapProcInfo,  &pkts[i],  sizeof(  pkts[i]  )  )  )  {
								  #ifdef  __DEBUG__
										traceLog((TCHAR*)  _T(  "doVpp failed"  )  );
								  #endif
								  tmpbErr  =  TRUE;					
								  break;
							  }						
						}
						//				   
					   if  (  tmpbErr  )  {
						   //
						   showInfo_open0(  0,  0,  _T(  "doVpp0 failed, skipped. l705"  )  );
						   //
						   continue;
					   }

					   //
					   if (pProcInfo->av.hk.portStatus.bDisable_hdmiIn_vga) {
						   if (pCapBmp->common.uiType == CONST_capType_mediaDevice) {
							   //  skipped
							   continue;
						   }
					   }
					   if (pProcInfo->av.hk.portStatus.bDisable_usb_sxt_usb1) {
						   if (pCapBmp->common.uiType == CONST_capType_av) {
							   // skipped
							   continue;
						   }
					   }

					   //
					   BOOL  bPktsRedirected  =  FALSE;
					   //
#if  0
					   if  (  pCapProcInfo->vh_org.bih.biCompression  ==  CONST_fourcc_MJPG  )  {
						   //
						   if (pkts[i].bih.biCompression  ==  CONST_fourcc_MJPG) {
							   continue;
						   }

						   //
						   if  (  bNeedFakePic()  ) {
							   int iFourcc_dst = CONST_fourcc_I420;
							   if (do_fakePic(pCtx, pkts[i].bih.biWidth,pkts[i].bih.biHeight,iFourcc_dst,  pkts[i].memory.m_pBuf,pkts[i].memory.uiBufSize)) {
								   continue;
							   }
						   }
							
						   //						 
						   if  (  !q2PostMsgAndTrigger(  &pkts[i],  1  *  sizeof(  pkts[0]  ),  &pCapProcInfo->thread.q2,  _T(  "vpp"))) {
							   bPktsRedirected  =  TRUE;						 
						   }
						   //					   
						   }
					   else
						   //
#endif 
					   {

						   //
						   if  (  pCtx->ucbSingleThread_vpp  )  {
							   if  (  !q2PostMsgAndTrigger(  &pkts[i],  1  *  sizeof(  pkts[0]  ),  &pCapProcInfo->thread.q2,  _T(  "vpp1"))) {
								   bPktsRedirected  =  TRUE;
							   }
							   //
							   }
						   else  {  //  2015/05/07. 送给vpp1
							     if  (  !q2PostMsgAndTrigger(  &pkts[i],  1  *  sizeof(  pkts[0]  ),  &pCtx->vppThread1_proc.q2,  _T(  "vpp2"  ))) {
									 bPktsRedirected  =  TRUE;					   
								 }
						   }
					   }
					   //
					   if  (  bPktsRedirected  )  {
							mallocObj_tmpPkts[i].detach(    );
					   }

						#ifdef  __DEBUG__
							if  (  !bPktsRedirected  )  {
								M_pkts_showNo(  pkts,  nPkts,  _T(  "vpp free"  )  );
							}
						#endif

			   
						//
						continue;
					}

			   }

			   continue;
		  }

		  continue;
	 }

#ifdef  __DEBUG__
	 traceLogA(  (char*)  "mcThreadProc_vpp will quit"  );
#endif

errLabel:

	 //  2010/12/28
	 pCapProcInfo->compressVideo.debugInfo.nStep  =  199;

	 //
	 pCapProcInfo->vppThread.bRunning  =  FALSE;


	 //
	 LPCTSTR  tHint  =  _T(  ""  );
	 stopQThread(  &ctx_vpp.vppThread1_proc,  tHint  );	//  2015/05/06		
	 stopQThread(  &ctx_vpp.vppThread2_beforeEnc,  tHint  );	//  2015/05/06
	 
	 //  2015/05/06	
	 if  (  ctx_vpp.vppThread1_proc.bQInited  )  {					
		 exitQyQ2(  &ctx_vpp.vppThread1_proc.q2  );  ctx_vpp.vppThread1_proc.bQInited  =  FALSE;				 
	 }				 
	 if  (  ctx_vpp.vppThread2_beforeEnc.bQInited  )  {		
		 exitQyQ2(  &ctx_vpp.vppThread2_beforeEnc.q2  );  ctx_vpp.vppThread2_beforeEnc.bQInited  =  FALSE;				 
	 }



#if 0
	 //  2013/03/11
	 CTX_addTxt_free(  &ctx_vpp.addTxt  );
	 //  2014/04/24
	 MACRO_safeFree(  ctx_vpp.resize.pBuf  );
#endif
	 CTX_vpp_free(  &ctx_vpp  );

	 //
#ifdef  __DEBUG__
	 traceLogA(  (char*)  "mcThreadProc_vpp %S leaves",  pCapProcInfo->vppThread.q2.cfg.name  );
#endif
	
	 //
	 return  0;

}

