

#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>

//#include <d3dx9.h>

#include	"DXUT/Core/DXUT.h"
#include	"DXUT/Optional/DXUTgui.h"
#include	"DXUT/Optional/SDKmisc.h"


#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qySyncCommProc.h"
#include	"qmcVideoCapture_isCli.h"


#include	"isCliD3dCommon.h"
#include	"dlgD3dWall.h"

//
#include	"isCliHelpPublic.h"

//
#include	"cuboidTool.h"

#include	"isCmdConst.h"
#include	"qyCusResTemp.h"
#include	"imgProcessPublic.h"
#include	"qmcMosaic.h"
#include	"ctxMcThread.h"


#include	<DirectXMath.h>

using  namespace DirectX;

//
int  tmp_postPkt(  QMC_mosaic_maker  *  pMosaic,  MOSAIC_rtt_info  *  pRtt,  BOOL  bResource,  myDRAW_VIDEO_DATA  *  pPkt,  BOOL  *  pbPktRedirected  );
//
extern  "C" int  readRtt_toMemory(  D3D_wallMem_sync  *  pWallMemSync,  QMC_mosaic_maker  *  pMosaic,  int index_mosaic,  MOSAIC_rtt_info  *  pRtt  );
extern  "C" int  readRtt_sharedTex(  D3D_wallMem_sync  *  pWallMemSync,  QMC_mosaic_maker  *  pMosaic,  int  index_mosaic,  MOSAIC_rtt_info  *  pRtt  );


 //
 //  2015/10/22
 extern  "C" int  readRtt(  D3D_wallMem_sync  *  pWallMemSync,  QMC_mosaic_maker  *  pMosaic,  int  index_mosaic  )
{
	int					iErr	=	-1;
	
	//CQySyncCnt			syncCnt;
	
	QY_MC			*	pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo  =  QY_GET_procInfo_isCli(  );

	D3D_context		*  pCtx  =  g_pD3dContext;
	GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pCtx->pGBuf_d3d_isCli;
	HRESULT				hr;
	int					i;
	

#if  0
	D3D_wallMem_sync  *  pWallMemSync  =  (  D3D_wallMem_sync  *  )getD3dWallMemSyncByIndex(  pCtx,  wallMemIndex  );	
	if  (  !pWallMemSync  )  goto  errLabel;
		
	if  (  syncMtCnt_rLock(  &pWallMemSync->m_syncMtCnt,  &syncCnt,  NULL  )  )  goto  errLabel;
#endif

	//
	CWallMem  *  pWmObj  =  wmInfoSync_getWmObj(  pWallMemSync  );
	if  (  !pWmObj  )  goto  errLabel;
	WALLMem_u  *  pWallMem  =  (  WALLMem_u  *  )pWmObj->get_pm_wallMemU(  );
	if  (  !pWallMem  )  goto  errLabel;

	if  (  pWallMem->uiType  !=  CONST_wallMemType_talker  )  goto  errLabel;

	WALLMem_talker  *  pTalker  =  &pWallMem->talker;  

	//  2016/01/23. need sync between render and this
	if  (  !pTalker->frm.talkerFrmMosaics[index_mosaic].bInited_mosaic  )  goto  errLabel;

	//
	MOSAIC_rtt_info  *  pRtt  =  &pTalker->frm.talkerFrmMosaics[index_mosaic].mosaicRtt;

	//
	if (0) {
		TCHAR  tBuf[128];
		_sntprintf(  tBuf,  mycountof( tBuf),  _T("89.readRtt. mosaicRttType %d"),  pRtt->iMosaicRttType);
		showInfo_open0(0, 0, tBuf);
	}
#if 0
	if (index_mosaic) {
		int  ii = 0;
		showInfo_open0(0, 0, _T("readRtt 1"));
	}
	else {
		int  ii = 0;
		showInfo_open0(0, 0, _T("readRtt 0"));
	}
#endif

	//
	switch  (  pRtt->iMosaicRttType  )  {
			case  CONST_mosaicRttType_null:
				  readRtt_toMemory(  pWallMemSync,  pMosaic,  index_mosaic,  pRtt  );
				  break;
			case  CONST_mosaicRttType_sharedTex:
				  readRtt_sharedTex(  pWallMemSync,  pMosaic,  index_mosaic,  pRtt  );
				  break;
			default:
					showInfo_open0(  0,  0,  _T(  "readRtt: unprocessed rttType"  )  );
					goto  errLabel;
	}



	iErr  =  0;
errLabel:

	return  iErr;
 }



 int  tmp_postPkt_sharedTex(  QMC_mosaic_maker  *  pMosaic,  MOSAIC_rtt_info  *  pRtt,  BOOL  bResource,  myDRAW_VIDEO_DATA  *  pPkt  )
 {
	 int  iErr  =  -1;

	 if  (  !pPkt  )  return  -1;
	 myDRAW_VIDEO_DATA  &  pkt  =  *pPkt;

	 
				 CQyMalloc  mallocObj;

				 MACRO_qyAssert(  !pkt.memory.m_pBuf,  _T(  "pkt is not null"  )  );

				 //
#if 0
				 showInfo_open0(0, 0, _T("124.tmp_postPkt_sharedTex"));
#endif



				 //
				 myDRAW_VIDEO_DATA  *  p  =  &pkt;

				 unsigned  int  uiSize_dec  =  0;
				 
				 //  2011/12/06
				 unsigned  int  uiSize_enc  =  sizeof(  TRANSFER_VIDEO_DATA  );
				 		
				 //
				 p->head.uiLen  =  uiSize_dec  +  uiSize_enc;		//  pBmpInfo_input->bmiHeader.biSizeImage;	
				 //
				 p->uiSize_dec  =  uiSize_dec;

				 char  *  pData  =  mallocObj.mallocf(  0,  p->head.uiLen  );
				 if  (  !pData  )  {
					 showInfo_open0(  0, 0,  _T(  "readRtt: malloc failed"  )  );
					 goto  errLabel;
				 }
				 if  (  mallocObj.get(  &p->memory  )  )  goto  errLabel;


		 	     #if  1
					p->debugInfo.dwTickCnt_start  =  GetTickCount(  );
					//M_pkt_setNo(  m_var.tn_pktNo,  m_var.lLastPktNo,  *p  );
				 #endif
				 //
				 dyn_M_set_pktId_alloc(  p  );

				 
				 //			
				 BOOL  bPktRedirected  =  FALSE;					  
				 //
				 tmp_postPkt(  pMosaic,  pRtt,  bResource,  &pkt,  &bPktRedirected  );							  			
				 //
				 if  (  bPktRedirected  )  {
					 mallocObj.detach(  );
				 }

				 iErr  =  0;

errLabel:
				 return  iErr;
		  
 }



#if 0
   //  2015/10/22
 extern  "C" int  old_readRtt_sharedTex(  D3D_wallMem_sync  *  pWallMemSync,  QMC_mosaic_maker  *  pMosaic,  int  index_mosaic,  MOSAIC_rtt_info  *  pRtt  )
 {
	 int  iErr  =  -1;
	 
	 //
	 CWallMem  *  pWmObj  =  wmInfoSync_getWmObj(  pWallMemSync  );
	 if  (  !pWmObj  )  return  -1;
	 WALLMem_u  *  pWallMem  =  (  WALLMem_u*  )pWmObj->get_pm_wallMemU(  );
	 if  (  !pWallMem  )  return  -1;

	 if  (  pWallMem->uiType  !=  CONST_wallMemType_talker  )  {
		 showInfo_open0(  0,  0,  _T(  "readRtt_sharedTex failed, not wallMem_talker"  )  );
		 return  -1;
	 }

	 //
	 unsigned  char  ucCnt_pkts  =  pRtt->ucCnt;
	 if  (  !ucCnt_pkts  ||  ucCnt_pkts  >  mycountof(  pRtt->sharedTex.rttPktSharedTexes  )  )  {
		 goto  errLabel;
	 }

	 //
	 unsigned  int  uiSeqNo_lastCopied  =  pRtt->sharedTex.uiSeqNo_lastCopied;
	 unsigned  int  uiSeqNo_newSharedTex  =  pRtt->sharedTex.uiSeqNo_newSharedTex;
	 if  (  pRtt->sharedTex.uiCnt_read  >  uiSeqNo_newSharedTex  )  {
		 pRtt->sharedTex.uiCnt_read  =  uiSeqNo_newSharedTex;
		showInfo_open0(  0,  0,  _T(  "readRtt_sharedTex err, uiCnt_rend > uiCnt_filled, adjusted"  )  );
	 }

	 //
	 BOOL  bPktSent  =  FALSE;

	 //
	 int  i;
	 for  (  i  =  pRtt->sharedTex.uiCnt_read;  i  <  uiSeqNo_newSharedTex;  i  ++,  pRtt->sharedTex.uiCnt_read  ++  )  {
		  int  index_toRead  =  i  %  ucCnt_pkts;
		  RTT_pkt_sharedTex  *  pRttPktSharedTex  =  &pRtt->sharedTex.rttPktSharedTexes[index_toRead];
		  if  (  !pRttPktSharedTex->bDataReady  )  {
			  showInfo_open0(  0,  0,  _T(  "Err: sharedTex.bDataReady is false"  )  );
			  continue;
		  }
		  		
		  //			
		  bPktSent  =  TRUE;
		  			
		  //			
		  myDRAW_VIDEO_DATA  pkt;			
		  memset(  &pkt,  0,  sizeof(  pkt  )  );				
		  //
		  pkt.usPktResType  =  CONST_pktResType_sharedTex;	//  2015/10/27			
		  //
		  pkt.sharedTex.pktSharedTexInfo.dwProcessId  =  pRtt->sharedTex.dwProcessId;			
		  pkt.sharedTex.pktSharedTexInfo.tn  =  pRtt->sharedTex.tn_sharedTex;				
		  //
		  pkt.sharedTex.pktSharedTexInfo.uiSeqNo  =  pRttPktSharedTex->tex.uiSeqNo;			
		  pkt.sharedTex.pktSharedTexInfo.ucMaxCnt_sharedTexes  =  pRtt->ucCnt;						
		  //
		  pkt.sharedTex.pktSharedTexInfo.bTexShared  =  TRUE;
			
		  //
		  pkt.input.tStartTran  =  pRttPktSharedTex->render.tStartTran_pkt_input;
		  pkt.bih  =  pRttPktSharedTex->render.bih;
		  pkt.head.uiSampleTimeInMs  =  pRttPktSharedTex->render.uiSampleTimeInMs;
		  pkt.iTaskId  =  pRttPktSharedTex->render.iTaskId;


		  //
		  tmp_postPkt_sharedTex(  pMosaic,  pRtt,  pWallMem->talker.data.cur.talkerMosaicCfg.mosaicCfgs[0].bResource,  &pkt  );		  
		  
		  //
		  pRttPktSharedTex->bDataReady  =  FALSE;
		  		  
		  //
		  continue;
	 }

	 //  try to send a old pkt, in order to trigger evt
	 if  (  !bPktSent  )  {
		 DWORD  dwTickCnt  =  GetTickCount(  );
		 int  iDiffInMs  =  dwTickCnt  -  pRtt->sharedTex.dwLastTickCnt_sendOldPkt;
		 if  (  abs(  iDiffInMs  )  >  200  )  {
			 pRtt->sharedTex.dwLastTickCnt_sendOldPkt  =  dwTickCnt;

			    myDRAW_VIDEO_DATA  pkt;
				memset(  &pkt,  0,  sizeof(  pkt  )  );
				//
				pkt.usPktResType  =  CONST_pktResType_sharedTex;	//  2015/10/27
				//
				pkt.sharedTex.pktSharedTexInfo.dwProcessId  =  pRtt->sharedTex.dwProcessId;
				pkt.sharedTex.pktSharedTexInfo.tn  =  pRtt->sharedTex.tn_sharedTex;
				//
				pkt.sharedTex.pktSharedTexInfo.uiSeqNo  =  uiSeqNo_lastCopied;
				pkt.sharedTex.pktSharedTexInfo.ucMaxCnt_sharedTexes  =  pRtt->ucCnt;		
				

				//
				makeBmpInfoHeader_rgb(  24,  pRtt->param.iW,  pRtt->param.iH,  &pkt.bih  );


				//  2015/11/01
				TCHAR  tBuf[128];
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "readRtt_sharedTex: bPktSent false, postPkt. sn_lastCopied %d"  ),  uiSeqNo_lastCopied  );
				showInfo_open0(  0,  0,  tBuf  );

				//
				tmp_postPkt_sharedTex(  pMosaic,  pRtt,  pWallMem->talker.data.cur.talkerMosaicCfg.mosaicCfgs[0].bResource,  &pkt  );  
		 }
	 }

	 //
	 iErr  =  0;

errLabel:

	 return  iErr;
 }
#endif


 //  2015/10/22
 extern  "C" int  readRtt_sharedTex(D3D_wallMem_sync * pWallMemSync, QMC_mosaic_maker * pMosaic, int  index_mosaic, MOSAIC_rtt_info * pRtt)
 {
	 int  iErr = -1;

	 //
	 CWallMem* pWmObj = wmInfoSync_getWmObj(pWallMemSync);
	 if (!pWmObj)  return  -1;
	 WALLMem_u* pWallMem = (WALLMem_u*)pWmObj->get_pm_wallMemU();
	 if (!pWallMem)  return  -1;

	 if (pWallMem->uiType != CONST_wallMemType_talker) {
		 showInfo_open0(0, 0, _T("readRtt_sharedTex failed, not wallMem_talker"));
		 return  -1;
	 }

	 //
	 unsigned  char  ucCnt_pkts = pRtt->ucCnt;
	 if (!ucCnt_pkts || ucCnt_pkts > mycountof(pRtt->sharedTex.rttPktSharedTexes)) {
		 goto  errLabel;
	 }


	 //
	 BOOL  bPktSent = FALSE;

	 //
#if 0
	 showInfo_open0(0, 0, _T("323.readRtt_sharedTex"));
#endif
	 if (index_mosaic) {
		 int  ii = 0;
	 }

	 //
	 int  i;
	 //for (i = pRtt->sharedTex.uiCnt_read; i < uiSeqNo_newSharedTex; i++, pRtt->sharedTex.uiCnt_read++) 
	 {
		 int  index_toRead = 0;// i% ucCnt_pkts;
		 RTT_pkt_sharedTex* pRttPktSharedTex = &pRtt->sharedTex.rttPktSharedTexes[index_toRead];

		 if (pRtt->sharedTex.n_waitToEnc == pRtt->sharedTex.n_post) {
			 goto  errLabel;
		 }
		 pRtt->sharedTex.n_post = pRtt->sharedTex.n_waitToEnc;

		 //
		 if (index_mosaic) {
			 int  ii = 0;
		 }
		 else {
			 int ii = 0;
		 }
#if 0
		 if (!pRttPktSharedTex->bDataReady) {
			 showInfo_open0(0, 0, _T("Err: sharedTex.bDataReady is false"));
			 continue;
		 }
#endif

		 //			
		 bPktSent = TRUE;

		 //			
		 myDRAW_VIDEO_DATA  pkt;
		 memset(&pkt, 0, sizeof(pkt));
		 //
		 pkt.usPktResType = CONST_pktResType_sharedTex;	//  2015/10/27			
		 //
		 pkt.sharedTex.pktSharedTexInfo.dwProcessId = pRtt->sharedTex.dwProcessId;
		 //
		 pkt.sharedTex.pktSharedTexInfo.index_mosaic = index_mosaic;
		 if (index_mosaic) {
			 int  ii = 0;
		 }
		 //  这里只用了第一个成员的handle. 可能需要更进一步的设计. 2023/12/02
		 pkt.sharedTex.pktSharedTexInfo.m_sharedHandle_HW = pRtt->sharedTex.rttPktSharedTexes[0].tex.g_sharedTex_handle;
		 if (!isHandleValid(pkt.sharedTex.pktSharedTexInfo.m_sharedHandle_HW)) {
			 showInfo_open0(0, 0, _T("readRtt_sharedTex failed: m_sharedHande_hw is not valid"));
			 goto  errLabel;
		 }
		 //
		 pkt.sharedTex.pktSharedTexInfo.tn = pRtt->sharedTex.tn_sharedTex;
		 //
		 pkt.sharedTex.pktSharedTexInfo.uiSeqNo = pRttPktSharedTex->tex.uiSeqNo;
		 pkt.sharedTex.pktSharedTexInfo.ucMaxCnt_sharedTexes = pRtt->ucCnt;
		 //
		 pkt.sharedTex.pktSharedTexInfo.bTexShared = TRUE;

		 //
		 pkt.input.tStartTran = pRttPktSharedTex->render.tStartTran_pkt_input;
		 pkt.bih = pRttPktSharedTex->render.bih;
		 pkt.head.uiSampleTimeInMs = pRttPktSharedTex->render.uiSampleTimeInMs;
		 pkt.iTaskId = pRttPktSharedTex->render.iTaskId;


		 //
		 tmp_postPkt_sharedTex(pMosaic, pRtt, pWallMem->talker.data.cur.talkerMosaicCfg.mosaicCfgs[index_mosaic].bResource, &pkt);

		 //
		 pRttPktSharedTex->bDataReady = FALSE;

		 //
		 //continue;
	 }

	

	 //
	 iErr = 0;

 errLabel:

	 return  iErr;
 }





  //  2015/10/22
 extern  "C" int  readRtt_toMemory(  D3D_wallMem_sync  *  pWallMemSync,  QMC_mosaic_maker  *  pMosaic,  int  index_mosaic,  MOSAIC_rtt_info  *  pRtt  )
{
	int					iErr	=	-1;
	
	//CQySyncCnt			syncCnt;
	
	QY_MC			*	pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo  =  QY_GET_procInfo_isCli(  );

	D3D_context		*  pCtx  =  g_pD3dContext;
	GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pCtx->pGBuf_d3d_isCli;
	HRESULT				hr;
	int					i;


	//
	RTT_pkt  *  pRttPkt  =  NULL;
	
	//  pRttPkt->tex.

	//
#ifdef  __DEBUG__
	if (index_mosaic == 1) {
		int  ii = 0;
	}
#endif


	//traceLog(  _T(  "readRtt here. mosaicThreads[%d]"  ),  index_mosaicThread  );

	int  bits  =  24;
	int  imgSize  =  M_sizeImage_open(  bits,  pRtt->param.iW,  pRtt->param.iH  );

	//  2015/11/18
	int  iTaskId  =  pMosaic->param.iTaskId; 

	//
#if 0
	TCHAR  mutexName[64];
	M_getMutexName_mosaic(  iTaskId,  index_mosaic,  mutexName,  mycountof(  mutexName  )  );
#endif

	//  2015/01/03
	unsigned  char  ucCnt_pkts  =  pRtt->ucCnt;
	if  (  !ucCnt_pkts  ||  ucCnt_pkts  >  mycountof(  pRtt->mems1  )  )  {
		showInfo_open0(  0,  0,  _T(  "readRtt: ucCnt_pkts err"  )  );
		goto  errLabel;			
	}
	unsigned  int  uiCnt_waitToPost  =  pRtt->status_render.uiCnt_waitToPost;
	int  index_waitToPost  =  uiCnt_waitToPost  %  ucCnt_pkts;

	//
	BOOL  bNeedSend  =  FALSE;
	//if  (  !pRtt->status_readRtt.sync_bSending  )  
	{
		RTT_pkt  *  pRttPkt  =  getRttPktByIndex(  pRtt,  index_waitToPost  );
		if  (  !pRttPkt  )  goto  errLabel;		
		//
		if  (  pRttPkt->render.bMapped_tex_cpu
			&&  !pRttPkt->readRtt.bProcessed  )  
		{			
			bNeedSend  =  TRUE;
		}
	}
	if  (  bNeedSend  )  {
#if 0
		CQySyncFlg	syncFlg;
		{
			CQySyncObj	syncObj;	
			if  (  syncObj.sync(  mutexName  )  )  goto  errLabel;

			if  (  syncFlg.sync(  &pRtt->status_readRtt.sync_bSending  )  )  goto  errLabel;
		}
#endif

		//
		int  err_lastRead_sampleTimeInMs  =  0;
		//BOOL  bOk_lastRead_sampleTimeInMs  =  FALSE;
		DWORD  dwTickCnt_beforeMalloc = 0;
		DWORD  dwTickCnt_afterMalloc = 0;
		DWORD  dwTickCnt_end = 0;


		//
		for  (  ;  !pMosaic->bQuit  ;  )  {
			//
			int  iNextIndex_toRead  =  uiCnt_waitToPost  %  ucCnt_pkts;
			//
			pRttPkt  =  getRttPktByIndex(  pRtt,  iNextIndex_toRead  );	//  &pRtt->mems[pRtt->status_readRtt.iNextIndex_toRead];
			if  (  !pRttPkt  )  goto  errLabel;
			//
			if  (  !pRttPkt->render.bMapped_tex_cpu
				||  pRttPkt->readRtt.bProcessed  )  
			{
				break;
			}
						
			//
			BOOL  bErr_nElapseInMs  =  FALSE;			
			int  nElapseInMs_sm  =  0;//  pRttPkt->render.uiSampleTimeInMs  -  pRtt->status_readRtt.lastRead_sampleTimeInMs;
			if  (  pRtt->status_readRtt.lastRead_sampleTimeInMs  )  {
				nElapseInMs_sm  =  pRttPkt->render.uiSampleTimeInMs  -  pRtt->status_readRtt.lastRead_sampleTimeInMs;
				if  (  nElapseInMs_sm  <=  0  )  {
					bErr_nElapseInMs  =  TRUE;
				}
			}

			//
			if (pProcInfo->cfg.debugStatusInfo.ucbPrint_rtt) {
				dwTickCnt_beforeMalloc = myGetTickCount(null);
			}

			//
			if  (  pRttPkt->render.bMapped_tex_cpu  )  {
				myDRAW_VIDEO_DATA  pkt;
				memset(  &pkt,  0,  sizeof(  pkt  )  );

				{
					CQyMalloc  mallocObj;

					MACRO_qyAssert(!pkt.memory.m_pBuf, _T("pkt is not null"));

					//
					myDRAW_VIDEO_DATA* p = &pkt;

					unsigned  int  uiSize_dec = imgSize;

					//  2011/12/06
					unsigned  int  uiSize_enc = sizeof(TRANSFER_VIDEO_DATA);

					//
					p->head.uiLen = uiSize_dec + uiSize_enc;		//  pBmpInfo_input->bmiHeader.biSizeImage;	
					//
					p->uiSize_dec = uiSize_dec;

					char* pData = mallocObj.mallocf(0, p->head.uiLen);
					if (!pData) {
						showInfo_open0(0, 0, _T("readRtt: malloc failed"));
						goto  errLabel;
					}

#if  1
					p->debugInfo.dwTickCnt_start = GetTickCount();
					//M_pkt_setNo(  m_var.tn_pktNo,  m_var.lLastPktNo,  *p  );
#endif
//
					dyn_M_set_pktId_alloc(p);

					//
					if (mallocObj.get(&pkt.memory))  goto  errLabel;
					mallocObj.detach();
				}

				//
				if (pProcInfo->cfg.debugStatusInfo.ucbPrint_rtt) {
					dwTickCnt_afterMalloc = myGetTickCount(null);
				}


				//					
				UCHAR  *  pTextureBuffer  =  (  UCHAR  *  )pRttPkt->mappedResource.pData;							
				int    nTexturePitch = pRttPkt->mappedResource.RowPitch;
				int  iW  =  pRttPkt->render.bih.biWidth;
				int  iH  =  pRttPkt->render.bih.biHeight;
				BYTE  *  pData  =  (  BYTE  *  )pkt.memory.m_pBuf;
				//
				BITMAPINFOHEADER  *  pBih  =  &pRttPkt->render.bih;
				int				rgbIncrement_dst	=	pBih->biBitCount  /  8;		
				int				lineBytes_dst		=	M_lineBytes_rgb(  pBih->biBitCount,  iW  );

			
				//
				if (pProcInfo->bUse_dx11()) {

					//	
					for (int row = 0; row < iH; row++) {

						BYTE* pSrc = pTextureBuffer + (iH - row - 1) * nTexturePitch;
						BYTE* pDest = pData + row * lineBytes_dst;
						for (int col = 0; col < iW; col++) {

							//							
							pDest[0] = pSrc[2];			//  r
							pDest[1] = pSrc[1];			//	g
							pDest[2] = pSrc[0];			//	b

							//
							pSrc += 4;
							pDest += rgbIncrement_dst;
						}


					}
				}
				else {
					 //traceLog(_T("not finished: readRtt_toMemory: get imgData from texture"));
					 if (pRttPkt->bMapped12) {
						 int bmpW = pRtt->myReadStaging.bmpW;
						 int bmpH = pRtt->myReadStaging.bmpH;
						 int dstRowPitch = pRtt->myReadStaging.dstRowPitch;
						 int rowPitch = pRtt->myReadStaging.rowPitch;
						 int rowCount = pRtt->myReadStaging.rowCount;
						 int bits = pBih->biBitCount;
						 char* rgbData = (char*)pData;
						 int rgbDataSize = pkt.memory.uiBufSize;
						 //
						 if (bmpW != pRtt->param.iW
							 || bmpH != pRtt->param.iH)
						 {
							 showInfo_open0(0, 0, _T("readRtt_toMemory err: bmpW != rtt.W  ||  bmpH  != rtt.H"));
						 }
						 else {
							 mySaveTextureToBmp_do(_T("c:\\tttbbb\\111\\kk.dds"), (char*)pRttPkt->pMappedData12, bmpW, bmpH, dstRowPitch, rowPitch, rowCount,bits,rgbData,rgbDataSize);
						 }
					 }
				}
		  
				

				//
				//if  (  nElapseInMs  <=  0  )  
				if  (  bErr_nElapseInMs  )  {  //    =  TRUE;
					err_lastRead_sampleTimeInMs  =  pRttPkt->render.uiSampleTimeInMs;
					}
				else  {
					  pRtt->status_readRtt.lastRead_sampleTimeInMs  =  pRttPkt->render.uiSampleTimeInMs;
					  //bOk_lastRead_sampleTimeInMs  =  TRUE;
				}

				//
				pkt.input.tStartTran  =  pRttPkt->render.tStartTran_pkt_input;
				pkt.bih  =  pRttPkt->render.bih;
				pkt.head.uiSampleTimeInMs  =  pRttPkt->render.uiSampleTimeInMs;
				pkt.iTaskId  =  pRttPkt->render.iTaskId;

				//
				pkt.mosaic_n_waitToPost = uiCnt_waitToPost;
				pkt.mosaic_index_thisSecond = pRttPkt->render.index_ok_thisSecond;

				//
				BOOL  bPktRedirected  =  FALSE;
				//
				tmp_postPkt(  pMosaic,  pRtt,  pRttPkt->render.bResource,  &pkt,  &bPktRedirected  );												
				//
				if  (  bPktRedirected  )  {
					memset(  &pkt,  0,  sizeof(  pkt  )  );
					}
				else  {  
					  freeMemory(  &pkt.memory  );
				}
			
				//
				//pRttPkt->readRtt.bPktAlloced  =  FALSE;				//  只有这里是设置false的
				pRttPkt->readRtt.bProcessed  =  TRUE;
						
			}

			//			
			uiCnt_waitToPost  ++  ;

			//
			bool  bPrint_rtt = false;
#ifdef  __DEBUG__
			//bPrint_rtt = true;
#endif

			//			
			if (bErr_nElapseInMs || bPrint_rtt) {
				//
				dwTickCnt_end = myGetTickCount(null);
				int int_malloc = dwTickCnt_afterMalloc - dwTickCnt_beforeMalloc;
				int int_post = dwTickCnt_end - dwTickCnt_beforeMalloc;
				//
				TCHAR  tBuf[128] = _T("readRtt");
				_sntprintf(tBuf, mycountof(tBuf), _T("read rtt[%d]: pkts, nElapse_sm %dms. "),	index_mosaic, nElapseInMs_sm);
				//_sntprintf(tBuf, mycountof(tBuf), _T("%s i_malloc % d, i_post% d, n_waitToPost% d,"), tBuf, int_malloc, int_post, uiCnt_waitToPost);
				if (pRtt) {
					_sntprintf(tBuf, mycountof(tBuf), _T("%s %dx%d"), tBuf, pRtt->param.iW, pRtt->param.iH);
				}
				_sntprintf(tBuf,mycountof(tBuf),_T("%s ind_ok_thisSec %d"  ),  tBuf,  pRttPkt->render.index_ok_thisSecond  );
				showInfo_open0(0, 0, tBuf);
			}

			//
			continue;
		}

	}



	iErr  =  0;
errLabel:

	return  iErr;
 }





 //
int  tmp_postPkt(  QMC_mosaic_maker  *  pMosaic,  MOSAIC_rtt_info  *  pRtt,  BOOL  bResource,  myDRAW_VIDEO_DATA  *  pPkt,  BOOL  *  pbPktRedirected  )
 {
	 int  iErr  =  -1;
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 
	 if  (  !pbPktRedirected  )  return  -1;

	 //
#if 0
	 if (bResource) {
		 int  ii = 0;
		 showInfo_open0(0, 0, _T("tmp_postPkt. bResource"));
	 }
	 else {
		 int  ii = 0;
		 showInfo_open0(0, 0, _T("tmp_postPkt. 0"));
	 }
#endif

	 //	
	 //BOOL  bResource  =  pRttPkt->render.bResource;		
	 int  iIndex_sharedObj  =  !bResource  ?  pMosaic->video.var.iIndex_sharedObj  :  pMosaic->resource.var.iIndex_sharedObj;			
	 //
	 QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );		
	 if  (  !pSharedObj  )  goto  errLabel;	 
			
	 int  iIndex_capBmp  =  pSharedObj->iIndex_capBmp;
	 CAP_procInfo_bmpU  *  pCapBmp  =  getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );
	 if  (  !pCapBmp  )  goto  errLabel;

	 //
#if  0  //  2015/10/21
	 if  (  pCapBmp->common.compressVideo.usFrames_perSecond_expected  !=  pRtt->usFrames_perSecond_expected  )  {
		 pRtt->usFrames_perSecond_expected  =  pCapBmp->common.compressVideo.usFrames_perSecond_expected;
	 }
#endif
	 //  2015/11/01
	 switch  (  pCapBmp->common.compressVideo.compressor.common.ucCompressors  )  {
			 case  CONST_videoCompressors_vcm:
			 case  CONST_videoCompressors_dmo:
				   break;
			 default:
					 QDC_OBJ_INFO  *  pQdcObjInfo  =  &pCapBmp->common.compressVideo.u.qoi.myQoi.common;
					 if  (  pRtt->sharedTex.uiSeqNo_lastRender  !=  pQdcObjInfo->var.sharedTex.uiSeqNo_lastRender  )  {
						 pRtt->sharedTex.uiSeqNo_lastRender  =  pQdcObjInfo->var.sharedTex.uiSeqNo_lastRender;
					 }
					 break;
	 }

	 //
	 pPkt->input.bMosaicResource = bResource;


	 //
#if    0  //  def  __DEBUG__
	 if  (  0  )  {			
				static  int  no  =  0;  no  ++  ;
				 
				 TCHAR  fileName[MAX_PATH];			
				 _sntprintf(  fileName,  mycountof(  fileName  ),  _T(  "c:\\tttbbb\\3\\kk%d.bmp"  ),  no  );
				 			
				 mySaveBitmap(  fileName,  &pRttPkt->pkt.bih,  pRttPkt->pkt.memory.m_pBuf,  FALSE  );
			
	 }
#endif

	 //
	 myDRAW_VIDEO_DATA  *  p  =  pPkt;
	 int  len  =  sizeof(  *p  );
	
	 //  2015/10/27
	 QY_Q2  *  pQ2  =  &pCapBmp->common.vppThread.q2;
	 //  2015/10/27
	 if  (  p->usPktResType  ==  CONST_pktResType_sharedTex  )  {
		 pQ2  =  &pCapBmp->common.thread.q2;
	 }

	 //
	 if  (  q2PostMsgAndTrigger(  p,  len,  pQ2,  _T(  "tmp_postPkt"  )))  goto  errLabel;
	 *pbPktRedirected  =  TRUE;
	 
errLabel:
	 return  iErr;
 }

  ///////////////////
 extern "C" __declspec(  dllexport  )  DWORD doProc_readRtt( LPVOID lpParameter )
{
	 QMC_mosaic_maker  *  pMosaic  =  (  QMC_mosaic_maker  *  )lpParameter;
	 QY_MC						*		pQyMc							=	QY_GET_GBUF(  );
	 MC_VAR_isCli				*		pProcInfo						=	QY_GET_procInfo_isCli(  );
	 int								loopCtrl						=	0;
	 int								i;
	 DWORD								dwThreadId						=	GetCurrentThreadId(  );
	 CQyMalloc							mallocObj;
	 MIS_MSGU					*		pMsg							=	NULL;
	 unsigned  int						len;
	 DWORD								dwRet;
	 //  long								lPrev;
	 //
	 CTX_MC_THREAD						ctx;
	 CQyMalloc							mallocObj_pMsgInputBuf;
	 CQyMalloc							mallocObj_pMsgBuf;
	 //
	 //  CWnd						*		pMainWnd						=	AfxGetApp(  )->m_pMainWnd;
	 //
	 unsigned  int						uiChannelType					=	CONST_channelType_realTimeMedia;
	 //
	 //int								index_mosaicThread				=	0;
	 int								wallMemIndex					=	0;

	 //
	 HANDLE								hEvent_syncRtt					=	NULL;

	 //
	 int  index_mosaic = -1;

	 //
#ifdef  __DEBUG__
	 traceLogA(  "mcThreadProc_mis_readRtt:  enters"  );
#endif

	 memset(  &ctx,  0,  sizeof(  ctx  )  );
	 
	 //
	 DWORD  dwCurThreadId  =  GetCurrentThreadId(  );
	 for  (  i  =  0;  i  <  pMosaic->ucCnt_threads;  i  ++  )  {
		  if  (  pMosaic->threads[i].dwThreadId  ==  dwCurThreadId  )  {
			  break;
		  }
	 }
	 if  (  i  ==  pMosaic->ucCnt_threads  )  goto  errLabel;
	 index_mosaic  =  i;
	 QMC_mosaic_thread* pMosaicThread = &pMosaic->threads[i];
		 
	 //
	 D3D_context  *  pCtx  =  (  D3D_context  *  )g_pD3dContext;//get_g_D3D_context(  );
	 int  iGrpType  =  CONST_wmGrpType_gZone;

	 int  maxCnt_wallMems  =  getMaxCnt_wallMems(  iGrpType  );

	 //  2015/11/18	   
	 int  iTaskId  =  pMosaic->param.iTaskId;
	 //
#if  10
	TCHAR tName[64]  =  _T(  ""  );
	
	M_getEvtName_mosaic(  iTaskId,  index_mosaic,  tName,  mycountof(  tName  )  );
	hEvent_syncRtt  =  CreateEvent(  NULL,  FALSE,  FALSE,  tName  );
	if  (  !hEvent_syncRtt  )  goto  errLabel;
#endif

	HANDLE  hEvents[2];
	hEvents[0]  =  pMosaicThread->hEvent_syncQuit;
	hEvents[1]  =  hEvent_syncRtt;

	//
	switch (index_mosaic) {
			case  0:
				break;
			default:
				int  ii = 0;
				break;
	}

	 //
	 for  (  ;  !pQyMc->bQuit;  loopCtrl  ++  )  {

		  int iWaitTimeInMs = 33;
		  dwRet  =  WaitForMultipleObjects(  mycountof(  hEvents  ),  hEvents,  FALSE,  iWaitTimeInMs  );
		  if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
		  
		  if  (  pMosaic->bQuit  )  goto  errLabel;

		  //
		  BOOL  bFound  =  FALSE;

		  //
		  int  index_d3dWnd  =  0;
		  //		  
		  WM_grp_sync  *  pGrp  =  getWmGrpSync(  index_d3dWnd,  iGrpType,  _T(  "doProc_readRtt"  )  );
		  if  (  pGrp  )  {
			  CQySyncCnt  syncCnt;
			  if  (  syncMtCnt_rLock(  &pGrp->syncMtCnt,  &syncCnt,  _T(  ""  )  )  )  continue;
			  if  (  pGrp->m_var.iGrpType  !=  iGrpType  )  continue;
			  
			  //				
			  D3D_wallMem_sync  *  pWallMemSync  =  (  D3D_wallMem_sync  *  )getWmInfoSyncByIndex(  pCtx,  pGrp,  wallMemIndex  );					
			  if  (  pWallMemSync  )  {
					  CRLock_wmInfoSync  rl;

					  if  (  !rl.rLock(  pWallMemSync,  _T(  "readRtt"  )  )  )  {
						  CWallMem  *  pWmObj  =  wmInfoSync_getWmObj(  pWallMemSync  );
						  if  (  pWmObj  )  {
							  WALLMem_u  *  pWallMem  =  (  WALLMem_u  *  )pWmObj->get_pm_wallMemU(  );
							  if  (  pWallMem  )  {
								  if  (  pWallMem->uiType  ==  CONST_wallMemType_talker  )  {					
									  if  (  pWallMem->talker.data.cur.talkerMosaicCfg.mosaicCfgs[index_mosaic].param.iTaskId  ==  pMosaic->param.iTaskId  )  {
										   bFound  =  TRUE;
										   //  traceLog(  _T(  "readRtt here. mosaicThreads[%d]"  ),  index_mosaicThread  );
										   //
										   readRtt(  pWallMemSync,  pMosaic,  index_mosaic  );
									   }
								  }
							  }
						  }
					  }				  
			  }
			  				  
			  //				
			  if  (  bFound  )  continue;
			  				
			  //				
			  for  (  i =  0;  i  <  maxCnt_wallMems  &&  !bFound;  i  ++  )  {		  									
				   if  (  pQyMc->bQuit  ||  pMosaic->bQuit  )  goto  errLabel;
			   
				   D3D_wallMem_sync  *  pWallMemSync  =  (  D3D_wallMem_sync  *  )getWmInfoSyncByIndex(  pCtx,  pGrp,  i  );			   							 
				   if  (  pWallMemSync  )  {
					   CRLock_wmInfoSync  rl;	
					   if  (  !rl.rLock(  pWallMemSync,  NULL  )  )  {					   
						   //
						   CWallMem  *  pWmObj  =  wmInfoSync_getWmObj(  pWallMemSync  );
						   if  (  pWmObj  )  {
							   WALLMem_u  *  pWallMem  =  (  WALLMem_u*  )pWmObj->get_pm_wallMemU(  );
							   if  (  pWallMem  )  {
								   if  (  pWallMem->uiType  ==  CONST_wallMemType_talker  )  {					
									   if  (  pWallMem->talker.data.cur.talkerMosaicCfg.mosaicCfgs[index_mosaic].param.iTaskId  ==  pMosaic->param.iTaskId  )  {
										   bFound  =  TRUE;									   
										   //
										   wallMemIndex  =  i;									   
										   //
										   readRtt(  pWallMemSync,  pMosaic,  index_mosaic  );																   
										   //
										   break;					   										
									   }							   
								   }						   
							   }					   
						   }				   
					   }			   
				   }	
		  
			  }			  
	 
		  }

		  //
		  continue;
	 }


errLabel:

	 //
#ifdef  __DEBUG__
	    switch  (  index_mosaic) {
				case  0:
					    break;
				default:
						int  ii  =  0;
						break;
		}
#endif

	 //
	 if  (  hEvent_syncRtt  )  {
		 CloseHandle(  hEvent_syncRtt  );  hEvent_syncRtt  =  NULL;
	 }


#ifdef  __DEBUG__
	 traceLogA(  "mcThreadProc_mis_readRtt:  leaves"  );
#endif

	 return  0;
}

