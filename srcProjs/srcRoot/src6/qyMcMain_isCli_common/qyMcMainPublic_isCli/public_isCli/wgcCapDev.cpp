

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"wgcCapDev.h"
#include	<qisPipe_open.h>
//
#include	"CtxQmc.h"
#include	<qisNameDefs.h>
#include	<vtShmFunc.h>
//
#include	"funcsForIsCliHelp.h"



WgcCapDev::WgcCapDev()
{
	memset(&m_var, 0, sizeof(m_var));
	//
	
	//
	return;
}


WgcCapDev::~WgcCapDev()
{
	//
	

	//
	return;
}


//
#if  0
1. cli先建管道.
2. 启动wgcTool
3. wgcTool 连接管道
4. wgcTool 建立共享内存。从管道通知cli
5. cli收到指令，打开共享内存。
6. 初始化完毕》
#endif 


//
int  wgc_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
{
	int  iErr = false;
	unsigned  int    dwByte = msgLen;
	//
	WgcCapDev* pWgcCapDev = (WgcCapDev*)p0;
	//  p1
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;

	//	
	if (dwByte < sizeof(OnvifMsg_common)) {
		showInfo_open0(0, 0, _T("shareDynBmps_qisPipe_onRead err: read too small bytes < sizeof(  Onvif_msg_common  )"));
		return  -1;
	}
	//
	OnvifMsg_common* pMsgCommon = (OnvifMsg_common*)pMsg;


	if (pMsgCommon->uiType != CONST_qisMsgType_onvif)  return  -1;

	//
	TCHAR  tBuf[128];

	//
	switch (pMsgCommon->iSubtype) {
	case  CONST_onvifMsg_subtype_dbg: {
		OnvifMsg_dbg* pDbg = (OnvifMsg_dbg*)pMsgCommon;
		//
		traceLog((TCHAR*)_T("recvd: %S"), pDbg->buf);
		//
	}
									break;
	case  CONST_wgcMsg_subtype_shmOk: {
		WgcMsg_shmOk* pShmOk = (WgcMsg_shmOk*)pMsgCommon;
		//
		traceLog((TCHAR*)_T("shmOk"));
		//
		pWgcCapDev->m_var.status.w = pShmOk->w;
		pWgcCapDev->m_var.status.h = pShmOk->h;
		//
		pWgcCapDev->m_var.status.wt_bShmOk = true;
		//
		makeBmpInfoHeader_rgb(24, pWgcCapDev->m_var.status.w, pWgcCapDev->m_var.status.h, &pWgcCapDev->m_var.bih_dec);
		
		//
		}
		break;
	case  CONST_wgcMsg_subtype_pkt: {
		WgcMsg_pkt* pPkt = (WgcMsg_pkt*)pMsgCommon;
		//
		if (pProcInfo->cfg.pDebugStatusInfo->bDbgDetail_wgc) {
			if (0) {
				_sntprintf(tBuf, mycountof(tBuf), _T("pkt: index_toRead %d"), pPkt->index_toRead);
				showInfo_open(0, 0, 0, tBuf);
			}
		}

		//
		if (1) {
			QY_shm* pShm = &pWgcCapDev->m_var.dataShm;
			if (!pShm->pBuf) {
				break;
			}
			VT_shm_content* pShmContent = (VT_shm_content*)pShm->pBuf;

			//
			if (pShmContent->bih_dec.biWidth != pWgcCapDev->m_var.bih_dec.biWidth
				|| pShmContent->bih_dec.biHeight != pWgcCapDev->m_var.bih_dec.biHeight)
			{
				break;
			}


			//
			pWgcCapDev->readShmPkt( pShmContent, pPkt->index_toRead);

			//
			int  tickCnt; 
			tickCnt = myGetTickCount(mynull);
			int  iDiffInMs;
			iDiffInMs = tickCnt - pWgcCapDev->m_var.status.dwLastTickCnt_sndPktResp;
			//
			if  (  abs(iDiffInMs  )  >  2000)
			{
				pWgcCapDev->m_var.status.dwLastTickCnt_sndPktResp = tickCnt;

				//
				OnvifMsg_common  resp;
				resp.uiType = pPkt->uiType;
				resp.iSubtype = pPkt->iSubtype;
				resp.ucbResp = true;
				//
				qisPipe_writeMsg(&resp, sizeof(resp), pQisPipe);
				//
			}
		}
	}
		break;
	default:
		//
		traceLog((TCHAR*)_T("unprocessed wgcMsg_subtype"));
		//
		break;
	}


	//
#ifdef  __DEBUG__

#endif



	//
	iErr = true;
errLabel:

	//
	return  iErr;

}


//
int  WgcCapDev::initDev(void** ppCapStuff, AUDIO_COMPRESSOR_cfgCommon* pAudioCompressor, BITMAPINFOHEADER* pBih_suggested, HWND  hWnd_notify, LONG_PTR lInstanceData, void** ppShareMediaDeviceParam)
{
	int  iErr = -1;
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	
	//
	int  index_sharedObj = (int)lInstanceData;
	QY_SHARED_OBJ* pSharedObj = (QY_SHARED_OBJ*)pProcInfo->getSharedObjSyncByIndex(index_sharedObj);
	if (!pSharedObj) {
		showInfo_open(0, 0, 0, _T("wgc.initDev failed, pSharedObj is null"));
		return  -1;
	}
	m_var.index_sharedObj = index_sharedObj;
	m_var.index_capBmp = pSharedObj->iIndex_capBmp;

	//
	do {
		try {

			//
			if (!m_var.pQisPipe) {


				//
				m_var.pQisPipe = qisPipeNew();
				//
				if (!m_var.pQisPipe) {
					break;
				}
				//
				GENERIC_Q_CFG  qCfg = { 0 };
				TCHAR   pipeName[128] = _T("");
				//
				//
				_sntprintf(qCfg.name, mycountof(qCfg.name), _T("wgcPipe"));
				_sntprintf(qCfg.mutexName_prefix, mycountof(qCfg.mutexName_prefix), _T("wgcPipe"));
				qCfg.uiMaxQNodes = CONST_uiMaxQNodes_outputQ_256;

				//		  		  
				M_get_pipeName(CONST_wgcPipePrefix, _T(""), CONST_wgcPipe_tn, pipeName);

				//
				PARAM_initQisPipe  param = { 0 };
				param.pf_onRead = wgc_qisPipe_onRead;
				param.p0 = this;
				//
				if (initQisPipe(&qCfg, pipeName, TRUE, _T("wgcPipeStarter"), &param, m_var.pQisPipe)) {
					//goto  errLabel;7//
					break;
				}
				//
				showInfo_open(0, 0, 0, _T("wgcCapDev.initDev: initQisPipe ok"));

				//
				if (createVt(pProcInfo, CONST_vtType_wgcTool, m_var.tn_cliPipe, 0, &m_var.vtProcess, _T(""))) {
					break;
				}
				showInfo_open(0, 0, 0, _T("wgcCapDev.initDev: createVt ok"));

				// 这里等待bShmOk指令. 要有超时处理
				int  i = 0;
				int maxCnt = 40;
				//
#ifdef  __DEBUG__
				maxCnt = 2000;
#endif 
				//
				for (  i  =0; i  <  maxCnt ;  i  ++ ) {
					//
					if (m_var.status.wt_bShmOk) {
						break;
					}
					//
					Sleep(100);
					traceLog((TCHAR*)_T("after sleep"));
				}
				if (i == maxCnt) {
					showInfo_open(0, 0, 0, _T("wgcCapDev.initDev failed, shmOk not waited"));
					break;
				}
				//  打开shm
				{

					QY_shm* pShm = &m_var.dataShm;

					//
					_sntprintf(pShm->shmName, mycountof(pShm->shmName), _T("Local\\%s%s%d"), CQyString(pQyMc->appParams.appObjPrefix), CONST_shmName_qm_wgc, m_var.tn_cliPipe);						// name of mapping object 

					//
					pShm->hMap = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, 0, pShm->shmName);
					if (!pShm->hMap) {
						qyDisplayLastError((char*)"OpenFileMapping");
						break;
					}
					//
					pShm->pBuf = (char*)MapViewOfFile(pShm->hMap,   // handle to map object
						FILE_MAP_ALL_ACCESS,			// read/write permission
						0,
						0,
						pShm->uiBufSize_pBuf);
					if (!pShm->pBuf) {
						break;
					}

					

					//  2016/04/12
					VT_shm_content* pShmContent = (VT_shm_content*)pShm->pBuf;
					//
#if 0
					_sntprintf(pProcInfo->who_showInfo, mycountof(pProcInfo->who_showInfo), _T("dvt%s"), pShmContent->cfg.name);
					set_who_showInfo(pProcInfo->who_showInfo);
#endif 

				}

				//
				showInfo_open(0, 0, 0, _T("send shmOk to wt"));

				//
				//  发送指令给wt, shm ok. 然后wt开始往shm里填数据.
				//
				WgcMsg_shmOk  m = { 0 };
				m.uiType = CONST_qisMsgType_onvif;
				m.iSubtype = CONST_wgcMsg_subtype_shmOk;
				safeStrnCpy((char*)"hello", m.buf, mycountof(m.buf));
				//
				if (qisPipe_writeMsg(&m, sizeof(m), m_var.pQisPipe)) {
					break;
				}

				//
#if  0
				if (1) {
					for (; ;) {
						Sleep(1000);
						traceLog((TCHAR*)_T("initDev: Sleep"));
					}
				}
#endif 
			}

		}
		catch (...) {
			showInfo_open(0, 0, 0, _T("WgcCapDev.initDev. new WgcCapture except"));
			break;
		}

		
		//
		iErr = 0;
	} while (false);


	//
	if (iErr) {
		exitDev(mynull);
	}


	//
	return  iErr;
}

int  WgcCapDev::exitDev(void** ppShareMediaDeviceParam)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	//
	stopDev(mynull);

	//  close shm
	//
	QY_shm* pShm = &m_var.dataShm;
	if (pShm->pBuf) {
		UnmapViewOfFile(pShm->pBuf);
		pShm->pBuf = NULL;
	}
	if (pShm->hMap) {
		CloseHandle(pShm->hMap);  pShm->hMap = NULL;
	}
	//
	showInfo_open(0, 0, 0, _T("wgcCapDev.exitDev: close shm ok"));

	//
	closeVt(pProcInfo, m_var.tn_cliPipe, &m_var.vtProcess);
	showInfo_open(0, 0, 0, _T("wgcCapDev.exitDev: closeVt ok"));

	//
	if (m_var.pQisPipe) {
		qisPipeFree(&m_var.pQisPipe);
	}
	showInfo_open(0, 0, 0, _T("wgcCapDev.exitDev: qisPipeFree ok"));

	//
	if (ppShareMediaDeviceParam) {
		*ppShareMediaDeviceParam = mynull;
	}
	
	//
	return  0;
 }



//
BOOL  WgcCapDev::bGetCapturePara(CCtxQmc* pProcInfo, int  iIndex_capAudio, int  iIndex_capBmp, void* pShareMediaDevice, WAVEFORMATEX* pWf_org, QY_VIDEO_HEADER* pVh_org, SAMPLE_grabberCb_cache* pCache)
{
	bool  bRet = false;
	int  i;
	int maxCnt = 20;
	//
#ifdef  __DEBUG__
		maxCnt = 2000;
#endif 
		do {
			//
			for (i = 0; i < maxCnt; i++) {
				if (m_var.status.wt_bShmOk) {
					break;
				}
				Sleep(100);
				continue;
			}
			if (i == maxCnt) {
				break;
			}

			//
			makeBmpInfoHeader_rgb(24, m_var.status.w, m_var.status.h, &pVh_org->bih);

			//
			bRet = true;
		} while (false);

	//
	return  bRet;
}

int  WgcCapDev::runDev(void* pShareMediaDeviceParam)
{
	
	//
	return  0;
}

int  WgcCapDev::stopDev(void* pShareMediaDeviceParam)
{
	

	//
	return  0;
 }


//
//
int WgcCapDev::readShmPkt( VT_shm_content* pShmContent, int  index_toRead)
{
	int  iErr = -1;
	TCHAR  tBuf[128];
	int  total_nPkts = 0;

	//
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
	FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);

	//
	do {

		//
		int  ucCnt_shmPktBufs = pShmContent->ucCnt_shmPktBufs;
		if (!ucCnt_shmPktBufs || ucCnt_shmPktBufs > mycountof(pShmContent->mems)) {
			break;
		}

		if (index_toRead < 0 || index_toRead >= ucCnt_shmPktBufs) {
			showInfo_open(0, 0, 0, _T("readShmPkt failed, index_toRead err"));
			break;
		}

		//
		//int  index_toRead = pShmContent->status.readShm.uiCnt_readShm % ucCnt_shmPktBufs;
		//
		if (!pShmContent->mems[index_toRead].bDataReady) {
			_sntprintf(tBuf, mycountof(tBuf), _T("readShm failed: shm.mems[%d].bDataReady is false. uiCnt_read %d, uiCnt_write %d"), index_toRead, pShmContent->status.readShm.uiCnt_readShm, pShmContent->status.writeShm.uiCnt_writeShm);
			showInfo_open0(0, 0, tBuf);
		}
		else {
			//
			BYTE* pImg = NULL;
			PF_img_to_yuv  pf_img_to_yuv = shm_img_to_yuv;

			//
			BITMAPINFOHEADER  bih_shm = pShmContent->bih_dec;

			//
			if (pShmContent->mems[index_toRead].usPktResType == CONST_pktResType_sharedTex) {
#if  0
				yuvWriter.outputInfo.usPktResType = pShmContent->mems[index_toRead].usPktResType;
				//yuvWriter.outputInfo.pktSharedTexInfo  =  pShmContent->mems[index_toRead].pktSharedTexInfo;
				yuvWriter.outputInfo.pkts_sharedTexInfo.mems[0] = pShmContent->mems[index_toRead].pktSharedTexInfo;
				yuvWriter.outputInfo.pkts_sharedTexInfo.ucCnt = 1;
#endif 
				//
			}
			else {
				//
				pImg = (BYTE*)pShmContent->buf + index_toRead * bih_shm.biSizeImage;


				//memcpy(pBuf, pImg, bih_shm.biSizeImage);
				//*pLen = bih_shm.biSizeImage;

				//
				//
				SAMPLE_grabberCb_var	var;
				memset(&var, 0, sizeof(var));
				//				
				//pkts[0].head.uiSampleTimeInMs = timeGetTime();
				int  uiSampleTimeInMs = timeGetTime();
				//
				pFuncs->pf_BufferCB_av(pProcInfo, m_var.index_capBmp, &var, uiSampleTimeInMs, (BYTE*)pImg, bih_shm.biSizeImage);

			}

			//
#ifdef  __DEBUG__
#if  0
			TCHAR  fn[128];
			static  int  ii = 0;  ii++;
			_sntprintf(fn, mycountof(fn), _T("d:\\tttbbb\\dd\\kkk%d.bmp"), ii);
			//
			mySaveBitmap( &bih_shm, pImg, FALSE,fn);
#endif
#endif 

			//
			total_nPkts++;
			//

			//	
#ifdef  __DEBUG__
#if  0
//if  (  pShmContent->cfg.ucbShowPostDecVStatus  )  
			{
				//_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "readShm: shmPkts[%d], uiCnt_toWrite %d, uiCnt_toRead %d. | nQNodes %d, total_nPkts %d, maxQNodes %d"  ),  index_toRead,  pShmContent->status_writeShm.uiCnt_writeShm,  pShmContent->status_readShm.uiCnt_readShm,  nQNodes,  total_nPkts,  maxQNodes  );
				if (pShmContent->mems[index_toRead].usPktResType == CONST_pktResType_sharedTex) {
					_sntprintf(tBuf, mycountof(tBuf), _T("dvtCli: readShm: shmPkts[%d], sn %d"), index_toRead, pShmContent->mems[index_toRead].pktSharedTexInfo.uiSeqNo);
					showInfo_open0(0, 0, tBuf);
				}
			}
#endif
#endif

			//						
			//smplYUVWriter_WriteNextFrame_all(pQdcObjInfo, &obj_trans, bih_shm.biCompression, &yuvWriter, pImg, bih_shm.biWidth, bih_shm.biHeight, 0, pf_img_to_yuv, 0, _T("readShm"));
			//  2016/03/29
			//pDvtCli->status.dwLastTickCnt_decDataGot = GetTickCount();


			//  2014/02/10
			pShmContent->mems[index_toRead].bDataReady = FALSE;
		}



		//
		pShmContent->status.readShm.uiCnt_readShm++;
		//SetEvent(pDvtCli->readShm.hEvent_syncW);	//  2015/02/19

		iErr = 0;

	} while (false);


	return  iErr;

}



