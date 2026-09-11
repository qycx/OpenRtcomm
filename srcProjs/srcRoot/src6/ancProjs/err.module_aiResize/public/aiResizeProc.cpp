
#include	"stdafx.h"


#include<iostream>
#include<string>
#include<string.h>
//
//#pragma comment(lib,"C:/Users/qycx1/Desktop/resize_demo/build/Debug/resize_lib.lib")
//
//#pragma comment(lib,"../../atPublic/resize_lib/resize_lib.lib" )
//#pragma comment(lib,"D:/tttbbb/resize_lib/resize_lib.lib" )

//
#define		__USE_aiResize__



//
#ifdef  __USE_aiResize__
#include"resize.h"
#else

#include	<vector>

#endif 


#include	"stdafx.h"
#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<windef.h>
#include	<lmcons.h>
#ifndef  __WINCE__
#include	<Winternl.h>
#include	<lmshare.h>
#endif
#include	<tlhelp32.h>
#include	<iphlpapi.h>



#include	"qyCommon.h"
#include	"qwmDynFunc.h"

//
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>


#include	"qyMcMainCommon.h"


#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"
#include	"tmpCeLib.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"
#include	"qmcSound_dx.h"

#include	"qmcVideoCapture_isCli.h"

#include	"qmcPlayVideo.h"
#include	"qyTick.h"

#include	"isCliD3dPublic.h"
#include	"imgProcessPublic.h"

#include	"qmcCommFunc_isCli.h"
#include	"imgFunc_open.h"
#include	"funcsForIsCliHelp.h"

//




//
extern "C" __declspec(dllexport) DWORD doPre_toPlayVideo(LPVOID pPlayerParam, bool bEnable_resize)
{
	showInfo_open0(0, _T("doPre_toPlayVideo"), _T("in"));

	QY_PLAYER* pPlayer = (QY_PLAYER*)pPlayerParam;
	QY_MC* pQyMc = g_pQyMc;
	if (!pQyMc)  return  -1;
	MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return  -1;

	//
	DYN_LIB_DX* pDynLib = (DYN_LIB_DX*)((QY_DYN_LIBS*)pQyMc->env.pDynLibs)->pLib_dx;

	//QY_PLAYER* pPlayer = NULL;
	PLAY_VIDEO_procInfo* pPlay = &pPlayer->video;

	//
	PLAYER_ID						playerId;
	memset(&playerId, 0, sizeof(playerId));

	//
	DWORD							dwThreadId = GetCurrentThreadId();

	//
	CQyTick						tickObj;
	DWORD							dwTgt_lastData = M_GetTgt_video(tickObj);;						// 

	//
	myDRAW_VIDEO_DATA				pkts[CONST_pkts_playVideo];
	unsigned  int					uiLens[CONST_pkts_playVideo];		//  要增加一个qGetMsgs，将pPkts和pktLens作为参数输入。2011/07/15
	int							nLens = mycountof(uiLens);		//  一次最多处理的包数。

	//int							len_pkts;
	int							nPkts;

	MIS_CNT* pMisCnt = getMisCntByName(pProcInfo, _T(""));
	if (!pMisCnt)  return  -1;

	//  2011/12/05
	CQyMalloc	mallocObj_tmpRgbBuf;
	char* tmpRgbBuf = NULL;

	//
	Ctx_fillData_d3d  ctx_fillData_d3d;
	memset(&ctx_fillData_d3d, 0, sizeof(ctx_fillData_d3d));

	//
	//  #define		DEFAULT_dwToInMs_playVideo		200
	//#define		DEFAULT_dwToInMs_playVideo			210
	//#define		DEFAULT_dwToInMs_playVideo			100
#define		DEFAULT_dwToInMs_playVideo			16
//
#define		CONST_video_skippedInterval			0	//  
#define		CONST_video_ahead					0	//  			//  提前量

	DWORD							dwToInMs = DEFAULT_dwToInMs_playVideo;

	DWORD							dwTgt_internal;
	DWORD							dwTgt_internal_toPlay;
	DWORD							dwTickCnt_syncAv_now;

	BOOL							bPktRedirected = FALSE;

	unsigned  int					uiSampleTimeInMs_audio = 0;
	DWORD							dwTickCnt_syncAv_audio = 0;

	//
	//  2015/03/12. 本地视频没有做pts,是错的。不过，现在先暂时伪造一个，以便用pts来改善播放效果
	unsigned  int					tmp_localV_pts_faked = 0;
	//
	TCHAR  tBuf[128];

	//
	int							totalPkts = 0;
	int							totalPkts_lastOk = 0;
	int							nPkts_left = 0;
	bool							bExists_skipped = false;


	//
	TMP_fps_info fpsInfo;
	memset(&fpsInfo, 0, sizeof(fpsInfo));


	//
	std::vector<std::pair<int, int>>pairs;
#ifdef  __USE_aiResize__
	std::vector<SRTensorRT*>p_sr_engine_v;
	SRTensorRT* p_sr_engine = NULL;
#endif 

	//
	playerId = pPlayer->playerId;

	//
#ifdef  __DEBUG__
	traceLogA((char*)"playVideo %S enters", pPlay->q2.cfg.name);
#endif

	//  2014/07/03
	//  TMP_fps_info					fpsInfo  =  {0,};	
	TMP_fps_info fpsInfo1;  // = pPlay->m_var.status.fpsInfo;
	memset(&fpsInfo1, 0, sizeof(fpsInfo1));
	//  2015/09/13
	//BOOL  &  bNeedAdjust  =  pPlay->m_var.lowLatency.bNeedAdjust;

	//
	switch (pPlayer->video.vh.bih.biCompression) {
	case  BI_RGB:
	case  CONST_fourcc_YV12:
	case  CONST_fourcc_I420:	//  2014/07/21
		break;
	default:
#ifdef  __DEBUG__
		char  buf[128];
		traceLogA((char*)"playVideo: %s failed. only support play rgb or yv12. ", iFourcc2Str(pPlayer->video.vh.bih.biCompression, buf, mycountof(buf)));
#endif
		goto  errLabel;
	}

	BITMAPINFOHEADER	bih;
	makeBmpInfoHeader_rgb(24, pPlayer->video.vh.bih.biWidth, pPlayer->video.vh.bih.biHeight, &bih);
	if (memcmp(&bih, &pPlayer->video.vh.bih, sizeof(bih)))  memcpy(&pPlayer->video.vh.bih, &bih, sizeof(pPlayer->video.vh.bih));

	//  2011/12/05
	tmpRgbBuf = mallocObj_tmpRgbBuf.mallocf(bih.biSizeImage);
	if (!tmpRgbBuf) {
		TCHAR  tBuf[128];
		_sntprintf(tBuf, mycountof(tBuf), _T("playVideo failed: tmpRgbBuf.malloc returns null, bih.biSizeImage %d"), bih.biSizeImage);
		showInfo_open0(0, 0, tBuf);
		goto  errLabel;
	}

	//
	bool  bEnable_aiResize;
	bEnable_aiResize = bEnable_resize;
	//
	showInfo_open0(0, 0, bEnable_aiResize ? _T("aiResize true") : _T("aiResize false"));


	/////////////////
	emptyQ2(&pPlay->doPre_toPlayVideo.q2);

	//  2015/09/14
	//pPlay->m_var.lowLatency.mql.max_ql_ok_avg_100  =  pPlayer->video.usFps  /  2  *  100;

	//
	for (; !pPlay->doPre_toPlayVideo.bQuit; ) {

		//  2015/09/12
		dwToInMs = DEFAULT_dwToInMs_playVideo;
		int  iFps = (int)fpsInfo.fps_real;
		//
		dwToInMs = 16;

		//

		//
#ifdef  __DEBUG__
#endif

		//
		DWORD  dwEvt = MsgWaitForMultipleObjects(
			pPlay->doPre_toPlayVideo.q2.cfg.usCnt_hEvents,	//  mycountof(  pPlay->hEvents  ),				// Number of events.
			pPlay->doPre_toPlayVideo.q2.hEvents,							// Location of handles.
			FALSE,										// Wait for all?
			dwToInMs,									// How long to wait?
			0);										// Any message is an 
		// event.
		if (dwEvt == WAIT_FAILED)  goto  errLabel;



		//
		for (; !pPlayer->video.doPre_toPlayVideo.bQuit; ) {
			//  traceLogA(  (char*)  "playVideo: msg reaved"  );
			//
			nPkts = 0;
			int i;
			//
#ifdef  __DEBUG__
			DWORD  dwTickCnt_beforeGetMsg = myGetTickCount(nullptr);
#endif

			// 					  //  pktLen  =  uiBufSize;  
			nLens = mycountof(uiLens);
			//  2014/04/10
			if (q2GetMsgPkg(&pPlay->doPre_toPlayVideo.q2, (void*)pkts, sizeof(pkts), (unsigned  int*)uiLens, (unsigned  int*)&nLens, _T("playVideo"))) {
				break;
			}

			for (i = 0; i < nLens; i++) {
				nPkts += uiLens[i] / sizeof(pkts[0]);
				if (uiLens[i] % sizeof(pkts[0])) {
#ifdef  __DEBUG__
					traceLog((TCHAR*)_T("vpp: uiLen err"));
					assert(0);
#endif
				}
			}

			//  注意：在上面qGetMsg和下面的attach之间，不要添加代码，否则，内存就失去管理了

#ifdef  __DEBUG__
		//  traceLogA(  (char*)  "playVideo: pkt.SampleTime %d, pktLen %d",  pPkt->head.uiSampleTimeInMs,  pktLen  );
		// //
			if (0) {
				//if (pPlayer->idInfo_recorder.ui64Id) 
				{
					int  n = getQ2Nodes(&pPlay->q2);
					traceLog((TCHAR*)_T("playVideo: %I64u, nQNodes %d"), pPlayer->idInfo_recorder.ui64Id, n);
				}
			}

			//
#endif

			{
				CQyMalloc		mallocObj_tmpPkts[CONST_pkts_playVideo];


				BOOL  tmpbErr = FALSE;	//  注意：这里如果attach出错，要继续attach, 但是最后要continue. 以防止pPkts[i]没有机会释放内存
				//
				//nPkts  =  len_pkts  /  sizeof(  pkts[0]  );
				for (int i = 0; i < nPkts; i++) {
					myDRAW_VIDEO_DATA* pPkt = &pkts[i];
					if (pPkt->memory.m_pBuf) {
						if (mallocObj_tmpPkts[i].attach(&pPkt->memory)) {
#ifdef  __DEBUG__
							traceLogA((char*)"mcThreadProc_playVideo: mallocObj.attach failed");
#endif
							clean_myDRAW_VIDEO_DATA(pPkt, _T("playVideo"));
							tmpbErr = TRUE;
							continue;
						}
					}
				}

				if (tmpbErr)  continue;

				//
				short usFps_expected;
				usFps_expected = 10;


				//
				for (int iIndex = 0; iIndex < nPkts; iIndex++) {
					myDRAW_VIDEO_DATA* pPkt = &pkts[iIndex];
					//int						pktLen = sizeof(pkts[0]);

					//  2015/03/12. 对本地视频，伪造一个pts. 等回头在包生成处产生pts才对
					if (!pPlayer->idInfo_recorder.ui64Id) {
						if (!pPkt->head.uiPts) {
							pPkt->head.uiPts = tmp_localV_pts_faked;
							tmp_localV_pts_faked++;
						}
					}

					//
					totalPkts++;
					//
					player_get_fps(mynull, pPlayer->idInfo_recorder.ui64Id, usFps_expected, pPkt->head.uiSampleTimeInMs, &fpsInfo, (TCHAR*)_T("l339"));


					//  2015/10/04
					if (pPkt->usPktResType != CONST_pktResType_sharedTex) {
						//
						if (pPkt->head.uiLen < pPlay->vh.bih.biSizeImage) {
#ifdef  __DEBUG__
							traceLogA((char*)("playVideo err: pkt.head.uiLen %d <  sizeImage %d. skipped"), pPkt->head.uiLen, pPlay->vh.bih.biSizeImage);
#endif
							qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("playVideo err: pkt.head.uiLen %d <  sizeImage %d. skipped"), pPkt->head.uiLen, pPlay->vh.bih.biSizeImage);
							continue;
						}

						//
						Param_bPktSkipped  param = { 0 };
						param.last_mql = pPlay->m_var.lowLatency.mql.mql_3s.last_mql;
						param.mql_ok = pPlay->m_var.lowLatency.mql.mql_ok;
#ifdef  __DEBUG__
						//param.bDbg = true;
#endif
							//
							//
						int nQNodes = getQ2Nodes(&pPlayer->video.q2);
						//
						nPkts_left = nPkts - iIndex;
						//
						bool  b4k = is4k(pPlayer->video.vh.bih.biWidth, pPlayer->video.vh.bih.biHeight);
						unsigned  __int64 nFactor = 0;


						//
						if (bPktSkipped(&param, CONST_nWhere_resize, usFps_expected, fpsInfo.fps_real,  nQNodes, totalPkts, nPkts_left, b4k, &totalPkts_lastOk, &nFactor)) {
							if (10) {
								_sntprintf(tBuf, mycountof(tBuf), _T("resize: fps %d, totalPkts %d, nFactor %I64u, nQNodes %d, skipped"), (int)usFps_expected, totalPkts, nFactor, nQNodes);
								traceLog((TCHAR*)tBuf);
								//
								showInfo_open0(0, 0, tBuf);
							}
							//
							continue;
						}

						//
						if (bExists_skipped) {
							bExists_skipped = false;
							//
							//pPlay->m_var.lowLatency.bNeedAdjust3 = true;
						}

					}

					//  2011/12/05
					if (pPkt->bih.biWidth != pPlay->vh.bih.biWidth
						|| pPkt->bih.biHeight != pPlay->vh.bih.biHeight
						|| !pPkt->bih.biSizeImage)
					{
#ifdef  __DEBUG__
						traceLog((TCHAR*)_T("playVideo err: pkt %d,%d !=  player %d,%d. skipped"), (int)pPkt->bih.biWidth, (int)pPkt->bih.biHeight, (int)pPlay->vh.bih.biWidth, (int)pPlay->vh.bih.biHeight);
#endif
						qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("playVideo err: pkt %d,%d !=  player %d,%d. skipped"), (int)pPkt->bih.biWidth, (int)pPkt->bih.biHeight, (int)pPlay->vh.bih.biWidth, (int)pPlay->vh.bih.biHeight);
						continue;
					}


					//
					DWORD	dwTickCnt_beforeYv12 = myGetTickCount(mynull);
					//
					if (pPkt->usPktResType != CONST_pktResType_sharedTex) {
						if (pPkt->bih.biCompression != BI_RGB) {
#if  0
							if (pPkt->bih.biCompression != CONST_fourcc_YV12) {
#ifdef  __DEBUG__
								traceLog((TCHAR*)_T("playVideo err: pPkt->bih err"));
#endif
								continue;
							}
#endif
							if (pPkt->bih.biSizeImage > bih.biSizeImage) {
#ifdef  __DEBUG__
								assert(0);
#endif
								continue;
							}
							memcpy(tmpRgbBuf, pPkt->memory.m_pBuf, pPkt->bih.biSizeImage);
							//
#ifdef  __DEBUG__
							if (0) {
								//pPkt->bih.biCompression = CONST_fourcc_NV12;
							}
#endif 
							//
							switch (pPkt->bih.biCompression) {
							case  CONST_fourcc_YV12:
								pQyMc->yv12ToRgb24((BYTE*)tmpRgbBuf, (BYTE*)pPkt->memory.m_pBuf, pPkt->bih.biWidth, pPkt->bih.biHeight, 0);//pPlayer->video.ucbFlippedImg  );								 
								break;
							case  CONST_fourcc_I420:
								i420ToRgb24((BYTE*)tmpRgbBuf, (BYTE*)pPkt->memory.m_pBuf, pPkt->bih.biWidth, pPkt->bih.biHeight, 0); //pPlayer->video.ucbFlippedImg  );								 										
								break;
							case  CONST_fourcc_NV12:
							{
#if 0
								static FILE* fp = null;
								static int cnt = 0;
								cnt++;
								if (!fp) {
									fp = fopen("c:\\codecSdk\\out\\kk.nv12", "wb");
								}
								if (fp) {
									fwrite(tmpRgbBuf, pPkt->bih.biSizeImage, 1, fp);
								}
								if (cnt > 300) {
									if (fp) {
										fclose(fp);
										fp = null;
									}
								}
#endif



								//
								nv12ToRgb24((unsigned  char*)tmpRgbBuf, (unsigned  char*)pPkt->memory.m_pBuf, pPkt->bih.biWidth, pPkt->bih.biHeight,false);

							}
							break;
							default:
#ifdef  __DEBUG__
								traceLog((TCHAR*)_T("playVideo err: pPkt->bih err"));
#endif
								continue;
								break;
							}
							//
							memcpy(&pPkt->bih, &pPlay->vh.bih, sizeof(pPkt->bih));
							pPkt->uiSize_dec = pPlay->vh.bih.biSizeImage;

						}
						else {
						}
					}

					//
					if (0) {
						int INPUT_W = pPkt->bih.biWidth;//  256;
						int INPUT_H = pPkt->bih.biHeight;// 144;
						BITMAPINFOHEADER bih;
						makeBmpInfoHeader_rgb(24, INPUT_W, INPUT_H, &bih);
						mySaveBitmap(&bih, pPkt->memory.m_pBuf, false, _T("d:\\tttbbb\\kk-999.bmp"));

					}


					//// 这里模拟了一个把480p的图像放大4倍的处理.
					//if (pPkt->bih.biHeight == 480) {
					//	pPkt->bih.biWidth *= 2;
					//	pPkt->bih.biHeight *= 2;
					//	makeBmpInfoHeader_rgb(24, pPkt->bih.biWidth, pPkt->bih.biHeight, &pPkt->bih);
					//	//
					//	int bits = 24;
					//	int  iW_int = pPkt->bih.biWidth;
					//	int iH_int = pPkt->bih.biHeight;

					//	//pPkt->uiSize_dec = M_sizeImage(bits，iW, iH);

					//	int bits_int = 24;
					//	int imgSize = M_sizeImage_open(bits_int, iW_int, iH_int);
					//	pPkt->uiSize_dec = imgSize;
					//	//
					//	pPkt->bResizeToPlay = true;

					//}
					 //--- 定义文件和尺寸参数 ---
					//
					if (bEnable_aiResize) {
						//
						// 输入：4x 缩放 (256x144)
						int INPUT_W = pPkt->bih.biWidth;//  256;
						int INPUT_H = pPkt->bih.biHeight;// 144;
						// 输出：4x 还是2x自己设置 (512x288/1024x576)
						const int OUTPUT_W = INPUT_W * 4;
						const int OUTPUT_H = INPUT_H * 4;
						if (0) {
							BITMAPINFOHEADER bih;
							makeBmpInfoHeader_rgb(24, INPUT_W, INPUT_H, &bih);
							mySaveBitmap(&bih, pPkt->memory.m_pBuf, false, _T("d:\\tttbbb\\kk451.bmp"));

						}


						//
						if (1) {

#ifdef  __USE_aiResize__

							if (!p_sr_engine) {
								p_sr_engine = new SRTensorRT();
								std::string ENGINE_FILE = "../models/resize.engine";
								//std::string ENGINE_FILE = "../models/resize_848_480.engine";
								//
								ENGINE_FILE = "D:/models/realesrgan-x4_256_144.engine";


								//
								p_sr_engine->aiResize_init(ENGINE_FILE, INPUT_W, INPUT_H, OUTPUT_W, OUTPUT_H);
								//first = 0;
							}
							//
							if (0) {
								BITMAPINFOHEADER bih;
								makeBmpInfoHeader_rgb(24, INPUT_W, INPUT_H, &bih);
								mySaveBitmap(&bih, pPkt->memory.m_pBuf, false, _T("d:\\tttbbb\\kk0.bmp"));

							}



							//
							int out_w, out_h;
							uchar* out_buf = new uchar[OUTPUT_W * OUTPUT_H * 3];

							//
							int  tickCnt0 = myGetTickCount(mynull);

							//
							int  nQNodes = getQ2Nodes(&pPlay->doPre_toPlayVideo.q2);
							_sntprintf(tBuf, mycountof(tBuf), _T("aiResize_do: qNodes %d"), nQNodes);
							showInfo_open0(0, _T("doPre_toPlayVideo"), tBuf);
							//
							p_sr_engine->aiResize_do(pPkt->bih.biWidth, pPkt->bih.biHeight, (uchar*)pPkt->memory.m_pBuf, out_w, out_h, out_buf);

							//
							int tickCnt1 = myGetTickCount(mynull);
							int  iDiffInMs = tickCnt1 - tickCnt0;
							traceLog((TCHAR*)_T("aiResize costs %dms"), iDiffInMs);


							//
							BITMAPINFOHEADER bih;
							makeBmpInfoHeader_rgb(24, out_w, out_h, &bih);
							if (0) {
								mySaveBitmap(&bih, out_buf, false, _T("d:\\tttbbb\\out_buf.bmp"));
							}

							//
							memcpy(pPkt->memory.m_pBuf, out_buf, bih.biSizeImage);

							//
							delete[]out_buf;
							//sr_engine.aiResize_exit();


							pPkt->bih.biWidth = out_w;
							pPkt->bih.biHeight = out_h;
							makeBmpInfoHeader_rgb(24, pPkt->bih.biWidth, pPkt->bih.biHeight, &pPkt->bih);
							//
							int bits = 24;
							int  iW_int = pPkt->bih.biWidth;
							int iH_int = pPkt->bih.biHeight;

							//pPkt->uiSize_dec = M_sizeImage(bits，iW, iH);

							int bits_int = 24;
							int imgSize = M_sizeImage_open(bits_int, iW_int, iH_int);
							pPkt->uiSize_dec = imgSize;
							//	//
							pPkt->bResizeToPlay = true;

							//
#endif 

						}
					}

 



					//
					int						pktLen = sizeof(pkts[0]);
					int  tmpiRet;
					tmpiRet = q2PostMsgAndTrigger(pPkt, pktLen, &pPlayer->video.q2, _T("doPre_toPlayVideo 1"));
					if (!tmpiRet) {
						mallocObj_tmpPkts[iIndex].detach();
					}
					//
					if (tmpiRet) {
						traceLog((TCHAR*)_T("q2PostMsg failed"));
					}



				}







				//
#ifdef  __DEBUG__
				for (int i = 0; i < nPkts; i++) {
					QY_MEMORY	memory;
					if (mallocObj_tmpPkts[i].get(&memory))  continue;
					if (memory.m_pBuf && memory.uiBufSize) {
						M_pkt_showNo(pkts[i], _T("playVideo . free"));
					}
				}
#endif

			}  //

			//
			continue;
		}

		//
		continue;
	}

	//
	traceLogA((char*)"mcThreadProc_doPre_toPlayVideo will quit");

errLabel:

#ifdef  __USE_aiResize__
	if (p_sr_engine) {
		delete  p_sr_engine;
	}
#endif 



	//
	//qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("%s, %I64u ends."), pPlayer->video.q2.cfg.name, pPlayer->idInfo_recorder.ui64Id);

	traceLogA((char*)"doPre_toPlayVideo %S leaves", pPlay->q2.cfg.name);

	//
	return  0;

}



