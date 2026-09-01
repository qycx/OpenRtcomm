
#include	"stdafx.h"
#include	"ctxQmcWt.h"

#include	"policyAvParams.h"
#include	"qyMcMainCommon.h"

//
#include	"myDb.h"
#include <qisNameDefs.h>
#include <vtShmFunc.h>




//
CCtxQmcWt::CCtxQmcWt(  )
{
	//  2015/02/08
	this->m_iCtxType  = CONST_ctxType_wgcTool;

	memset(  &m_var,  0,  sizeof(  m_var  )  );
	//
	safeTcsnCpy(  _T(  "wt"  ),  this->who_showInfo,  mycountof(  this->who_showInfo  )  );
}


CCtxQmcWt::~CCtxQmcWt(  )
{
}


	RW_lock_param  *  CCtxQmcWt::get_qyMc_rwLockParam(  )  
	{
		return  &m_var.qyMc_cfg.rwLockParam;
	}
	//

	TCHAR  *  CCtxQmcWt::get_appObjPrefix(  )
	{
		CCtxQyMc* pQyMc = g_pQyMc;
		//
		return  pQyMc->appParams.appObjPrefix;
	}


	void  *  CCtxQmcWt::get_qmc_cfg(  )
	{
		return  &m_var.cfg;
	}

	QNM_CUSRES_INFO  *  CCtxQmcWt::get_qyMc_cusRes(  )  
	{
		//  not finished
		return  NULL;
	}

	QMC_status  *  CCtxQmcWt::get_qmc_status(  )  
	{
		//  
		return  &m_var.status;
	}

	QMC_debugStatusInfo*  CCtxQmcWt::get_qmc_debugStatusInfo()
	{
		//
		return  NULL;
	}


	QY_sharedObj_sync  *  CCtxQmcWt::getSharedObjSyncByIndex(  int  index  )  
	{
		return  &m_var.sharedObjSync;
	}
	

	CAP_procInfo_bmpU  *  CCtxQmcWt::getCapBmpBySth(  int  index,  unsigned  int  uiCapType  )  
	{
		return  &m_var.capBmp;
	}

	CAP_procInfo_audioU  *  CCtxQmcWt::getCapAudioBySth(  int  index,  unsigned  int  uiCapType  )  
	{
		return  NULL;
	}

	//	
	int  CCtxQmcWt::newShmCmdIndex(  int  iIndex_sharedObj  )
	{
		return  -1;
	}

	//	
	void  *  CCtxQmcWt::getQmShmCmdByIndex(  int  iIndex  )
	{
		return  NULL;
	}


	//
	MIS_CNT  *  CCtxQmcWt::getMisCntByName(  LPCTSTR  misServName  )  
	{
		//
		return  NULL;
	}

	//
	MIS_CNT  *  CCtxQmcWt::getMisCntByIndex(  int  iIndex  )  
	{
		//
		return  NULL;
	}

	//
	HWND  CCtxQmcWt::get_hMainWnd(  )  
	{
		//
		return  NULL;
	}


	//
	void  *  CCtxQmcWt::getPolicyAvParams(  )  
	{	
		//
		return  m_var.p_gAvParams;
	}

	void  *  CCtxQmcWt::getCusModules(  )  
	{
		QY_MC  *  pQyMc  =  (  QY_MC  *  )this->pQyMc;	
		if  (  !pQyMc  )  return  NULL;
		
		return  &pQyMc->cusModules;
	}


	//
	int  CCtxQmcWt::setQmDbFuncs(  int  iDbType,  QM_dbFuncs  *  pDbFuncs  )
	{
		return  -1;
	}


	//
	int  qyMc_setQmDbFuncs(int  iDbType, QM_dbFuncs* pDbFuncs)
	{
		return  ::setQmDbFuncs_qm(iDbType, pDbFuncs);
	}


	BOOL  CCtxQmcWt::qyMc_bQuit(  )  
	{
		//
		return  FALSE;
	}



	BOOL  CCtxQmcWt::bWebcamUsing(  unsigned  int  uiCamCapType,  void  *  pMoniker_v,  LPCTSTR  camName,  int  *  piIndex_capBmp,  int  *  piIndex_sharedObj  )
	{
		return  FALSE;
	}



	BOOL  CCtxQmcWt::bMediaTaskExists(  int  iTaskId  )
	{
		return  FALSE;
	}



	BOOL  CCtxQmcWt::bAudioChannelReady(  )
	{
		return  TRUE;
	}

	BOOL  CCtxQmcWt::bVideoChannelReady(  )
	{
		return  TRUE;
	}


int  CCtxQmcWt::drawVideoData(  myDRAW_VIDEO_DATA  *  pkts,  int  pktsLen,  BOOL  *  pbPktsRedirected,  void  *  pQY_TRANSFORM  )
{
	return  -1;
}



int  CCtxQmcWt::playAudioData(  int  iSampleTimeInMs,  unsigned  int  uiPts,  BYTE  *  pInput,  unsigned  int  inputLen,  int  iIndex_player  )
{
	return  -1;
}



int  CCtxQmcWt::showNotification(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  LPCTSTR  hint  )
{
	return  -1;
}


	
int  CCtxQmcWt::qisChkTasks_gui(  )			//  2009/09/10
{
	return  -1;
}


int  CCtxQmcWt::applyForRemovingInvalidTasks(  unsigned  int  uiChannelType  )
{
	return  -1;
}



int  CCtxQmcWt::removeInvalidTasks(  unsigned  int  uiChannelType  )			//  2009/09/10
{
	return  -1;
}



//  2015/10/04
#if  0
unsigned  short  CCtxQmcWt::get_pktResType_suggested(  int  pktUsage,  unsigned  int  uiModuleType  )
{
	return  this->m_var.cmdLine.usPktResType_suggested;
}
#endif

//
int  CCtxQmcWt::get_deced_pktResType(  unsigned  int  uiModuleType,  int  iFourcc,  unsigned  short  *  pusPktResType_o  )				//  2015/10/04
{
	CCtxQyMc* pQyMc = g_pQyMc;
	if (!pQyMc)  return  -1;

	//
	if  (  pusPktResType_o  )  {
		*pusPktResType_o  =  pQyMc->appParams.usPktResType_suggested;
	}
	return  0;
}

//
int  CCtxQmcWt::get_pktResType_toEnc(  unsigned  short  usPktResType_src,  unsigned  int  uiModuleType,  int  iFourcc,  unsigned  short  *  pusPktResType_i  )				//  2015/10/04
{
	return  -1;
}




//
void  *  dvt_qoi_getPtrProperty(  void  *  pQdcObjInfoParam,  int  propertyId  );


//
int  CCtxQmcWt::set_qoi_funcs(  MY_qoi  *  pMyQoi  )
{
	//
	pMyQoi->common.pf_qoi_getPtrProperty  =  dvt_qoi_getPtrProperty;


	return  0;
}

//
int  CCtxQmcWt::initForWriteFrame(int iFmt, int w_org, int h_org, Param_initForWriteFrame* pParam)
{
	int  iErr = -1;
	QY_shm* pShm = &m_var.dataShm;

	//
	if (!w_org || !h_org)  return  -1;

	//
	do {
		unsigned  short  usPktResType = 0;

		//
		makeBmpInfoHeader_rgb(12, w_org, h_org, &m_var.bih_org);

		//
		m_var.w_o = 1920;
		m_var.h_o = 1080;
		makeBmpInfoHeader_rgb(24, m_var.w_o, m_var.h_o, &m_var.bih_o);
		m_var.pBuf_o = (char*)mymalloc(m_var.bih_o.biSizeImage);
		if (!m_var.pBuf_o) {
			showInfo_open(0, 0, 0, _T("initForWriteFrame. pBuf_o malloc failed"));
			break;
		}


		//
		unsigned  char  ucCnt_shmPktBufs = MAX_shmPktBufs_wgc;
		unsigned  int  uiBufSize_pBuf = offsetof(VT_shm_content, buf) + m_var.bih_o.biSizeImage * ucCnt_shmPktBufs;
		//
		//
		if (usPktResType == CONST_pktResType_sharedTex) {
			ucCnt_shmPktBufs = MAX_shmPktBufs;
			uiBufSize_pBuf = offsetof(VT_shm_content, buf);
		}
		//
		pShm->uiBufSize_pBuf = uiBufSize_pBuf;	//  offsetof(  VT_shm_content,  buf  )  +  pResp->bih_dec.biSizeImage  *  ucCnt_shmPktBufs;
		if (!pShm->uiBufSize_pBuf) {
			break;
		}
		//
		_sntprintf(pShm->shmName, mycountof(pShm->shmName), _T("Local\\%s%s%d"), CQyString(pQyMc->appParams.appObjPrefix), CONST_shmName_qm_wgc, m_var.tn_rtspCliPipe);						// name of mapping object 
		//
		pShm->hMap = CreateFileMapping(
			INVALID_HANDLE_VALUE,						// use paging file
			NULL,										// default security 
			PAGE_READWRITE,							// read/write access                 
			0,											// max. object size 
			pShm->uiBufSize_pBuf,				// buffer size  
			pShm->shmName);						// name of mapping object 	 
		if (pShm->hMap == NULL) {
			traceLogA((char*)"Could not create file mapping object (%d).\n", GetLastError());
			break;
		}
		pShm->pBuf = (char*)MapViewOfFile(pShm->hMap,   // handle to map object
			FILE_MAP_ALL_ACCESS,			// read/write permission
			0,
			0,
			pShm->uiBufSize_pBuf);
		if (!pShm->pBuf) {
			break;
		}
		

		//
		VT_shm_content* pShmContent;
		pShmContent = (VT_shm_content*)pShm->pBuf;
		//
		memset(pShmContent, 0, offsetof(VT_shm_content, buf));
		//
		pShmContent->bih_dec = m_var.bih_o;// pResp->bih_dec;
		//  2015/02/19
		pShmContent->ucCnt_shmPktBufs = ucCnt_shmPktBufs;

		//  2016/04/12
		//_sntprintf(pShmContent->cfg.name, mycountof(pShmContent->cfg.name), _T("%I64u"), pFrom->idInfo.ui64Id);

		
		//
		showInfo_open(0, 0, 0, _T("send shmOk to cli"));

		// 在共享内存建立后，发一个指令给cli		
		//
		WgcMsg_shmOk  m = { 0 };
		m.uiType = CONST_qisMsgType_onvif;
		m.iSubtype = CONST_wgcMsg_subtype_shmOk;
		m.w = m_var.w_o;
		m.h = m_var.h_o;
		//
		safeStrnCpy("hello", m.buf, mycountof(m.buf));
		//
		if (qisPipe_writeMsg(&m, sizeof(m), m_var.pQisPipe)) {
			break;
		}


		//
		//  等待cli打开共享内存后，发指令过来.
		//
		int  i;
		int  maxCnt = 40;
		//
#ifdef  __DEBUG__
		//maxCnt = 2000;
#endif 
		//
		for (i = 0;i< maxCnt ;i++ ) {
			//
			if (m_var.wtStatus.cli_bShmOk) {
				break;
			}
			//
			Sleep(100);
			//
			traceLog(_T("kkkk"));
		}
		if (i == maxCnt) {
			//
			showInfo_open(0, 0, 0, _T("initForWriteFrame failed, cli_bShmOk not waited"));
			//
			if (pParam) {
				pParam->bNeedQuit = true;
			}
			//
			break;
		}
		//
		showInfo_open(0, 0, 0, _T("initForWriteFrame, cli_bShmOk "));

	
		//
		iErr = 0;

	} while (false);

	//
	if (iErr) {
		exitForWriteFrame();
	}

	//
	return  iErr;
}


//
int  CCtxQmcWt::exitForWriteFrame()
{
	//  close(shm)
	QY_shm* pShm = &m_var.dataShm;
	if (pShm->pBuf) {
		UnmapViewOfFile(pShm->pBuf);
		pShm->pBuf = NULL;
	}
	if (pShm->hMap) {
		CloseHandle(pShm->hMap);  pShm->hMap = NULL;
	}

	//
	showInfo_open0(0, 0, _T("wgcTool: shm closed. before rtspCliCommon_exit"));


	//
	MACRO_safeFree(m_var.pBuf_o);


	//
	return  0;
}

#include <stdint.h>
#include <algorithm>
#include <cstring>

//
#if  0
void iiBGRA2BGRCrop(
	const uint8_t* src,
	int srcStride,      // 每行字节数，例如 D3D11_MAPPED_SUBRESOURCE.RowPitch
	int w_i,
	int h_i,
	uint8_t* dst,
	int dstStride,      // 每行字节数，通常为 w_o * 3
	int w_o,
	int h_o)
{
	memset(dst, 0, dstStride * h_o);

	const int copy_w = min(w_i, w_o);
	const int copy_h = min(h_i, h_o);

	for (int y = 0; y < copy_h; ++y)
	{
		const uint8_t* s = src + y * srcStride;
		uint8_t* d = dst + y * dstStride;

		for (int x = 0; x < copy_w; ++x)
		{
			d[0] = s[0];
			d[1] = s[1];
			d[2] = s[2];

			s += 4;
			d += 3;
		}
	}
}
#endif 
//
#include <stdint.h>
#include <algorithm>
#include <cstring>

void BGRA2BGRCrop(
	const uint8_t* src,
	int srcStride,      // 输入每行字节数
	int w_i,
	int h_i,
	uint8_t* dst,
	int dstStride,      // 输出每行字节数
	int w_o,
	int h_o,
	bool flip)          // true: 上下翻转
{
	if (w_o > w_i || h_o > h_i)
		memset(dst, 0, dstStride * h_o);

	const int copy_w = min(w_i, w_o);
	const int copy_h = min(h_i, h_o);

	for (int y = 0; y < copy_h; ++y)
	{
		const uint8_t* s = src + y * srcStride;

		uint8_t* d;
		if (flip)
			d = dst + (copy_h - 1 - y) * dstStride;
		else
			d = dst + y * dstStride;

		const uint8_t* end = s + copy_w * 4;

		while (s < end)
		{
			*(uint16_t*)d = *(const uint16_t*)s; // B G
			d[2] = s[2];                         // R

			s += 4;
			d += 3;
		}
	}
}


//
int  CCtxQmcWt::procWgsCaptureFrame(int  iFmt, unsigned  char* data, int  w, int  h)
{
	int  iErr = -1;
	CCtxQmcTmpl* pBase = this;
	TCHAR  tBuf[128];

	//
	if (!pBase->wgsWriteFrame_m_bInited) {
		return  -1;
	}

	//
	int  w_o = m_var.w_o;
	int  h_o = m_var.h_o;
	//
	char* data_o  =  m_var.pBuf_o;

	//
	int srcStride = w * 4;
	int dstStride = w_o * 3;
	BGRA2BGRCrop(data, srcStride, w, h, (uint8_t*)data_o, dstStride, w_o, h_o,true);
	
	//
	static  int  iCtrl = 0;
	iCtrl++;
	


	//
	int  total_nPkts = 0;

	//
	do {
		//
		//if  (  )

		//		
		QY_shm* pShm = &m_var.dataShm;
		if (!pShm->pBuf)  return  -1;
		VT_shm_content* pShmContent = (VT_shm_content*)pShm->pBuf;
		BITMAPINFOHEADER	bih_shm = m_var.bih_o;// m_var.bih_org;
		//
		int  nPkts = 1;
		int i;

		//
		int  ucCnt_shmPkts = pShmContent->ucCnt_shmPktBufs;
		if (!ucCnt_shmPkts || ucCnt_shmPkts > mycountof(pShmContent->mems)) {
			break;
		}
		//				  
		int  index_toWrite = pShmContent->status.writeShm.uiCnt_writeShm % ucCnt_shmPkts;
		if (pShmContent->mems[index_toWrite].bDataReady) {
			//
							//
			WgcMsg_pkt  m = { 0 };
			m.uiType = CONST_qisMsgType_onvif;
			m.iSubtype = CONST_wgcMsg_subtype_pkt;
			m.index_toRead = index_toWrite;
			//
			if (qisPipe_writeMsg(&m, sizeof(m), m_var.pQisPipe)) {
				showInfo_open(0, 0, 0, _T("writeMsg pkt failed"));
				break;
			}

			//showInfo_open(0, 0, 0, _T("resend pkt. index_toWrite"));

			//
			if (pShmContent->u.dvt.i.ucbShowPostDecVStatus)
			{
				_sntprintf(tBuf, mycountof(tBuf), _T("writeShm failed: shm.mems[%d].bDataReady is true. cnt_writeShm %d, cnt_readShm %d. try to wait"), index_toWrite, pShmContent->status.writeShm.uiCnt_writeShm, pShmContent->status.readShm.uiCnt_readShm);
				showInfo_open0(0, 0, tBuf);
			}
			//
			break;
		}


		//
		int  nWritten = 0;
		for (i = 0; i < nPkts; i++) {
			//  2015/02/18
			total_nPkts++;
			//

			index_toWrite = pShmContent->status.writeShm.uiCnt_writeShm % ucCnt_shmPkts;
			if (pShmContent->mems[index_toWrite].bDataReady) {
				if (pShmContent->u.dvt.i.ucbShowPostDecVStatus)
				{
					_sntprintf(tBuf, mycountof(tBuf), _T("writeShm failed: shm.mems[%d].bDataReady is true. cnt_writeShm %d, cnt_readShm %d. try to wait"), index_toWrite, pShmContent->status.writeShm.uiCnt_writeShm, pShmContent->status.readShm.uiCnt_readShm);
					showInfo_open0(0, 0, tBuf);
				}
				break;
			}
			//
			myDRAW_VIDEO_DATA pkt; memset(&pkt, 0, sizeof(pkt));
			pkt.bih = bih_shm;

			//
			//
			if (iCtrl < 100) {
				TCHAR  fn[128];
				_sntprintf(fn, mycountof(fn), _T("d:\\tttbbb\\123\\bgr.%d.bmp"), iCtrl);
				mySaveBitmap(&m_var.bih_o, data_o, true, fn);
			}

			//
			if (writeShmPkt(&pkt, (char*)data_o, pShmContent, &bih_shm, ucCnt_shmPkts, index_toWrite)) {
				showInfo_open0(0, 0, _T("writeShm err, writeShmPkt failed"));
			}
			else {
				pShmContent->status.writeShm.uiCnt_writeShm++;
				//
				nWritten++;

				//
				WgcMsg_pkt  m = { 0 };
				m.uiType = CONST_qisMsgType_onvif;
				m.iSubtype = CONST_wgcMsg_subtype_pkt;
				m.index_toRead = index_toWrite;
				//
				if (qisPipe_writeMsg(&m, sizeof(m), m_var.pQisPipe)) {
					showInfo_open(0, 0, 0, _T("writeMsg pkt failed"));
					break;
				}


			}
		}
		//
		if (nWritten) {  //  Note: nPkts
			//SetEvent(pDvt_decV->writeShm.hEvent_syncR);
		}




		iErr = 0;
	} while (false);


	//
	return  iErr;
}
