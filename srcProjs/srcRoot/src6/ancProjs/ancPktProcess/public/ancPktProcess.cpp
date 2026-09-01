
//
#include	"stdafx.h"
#include	<tchar.h>
//

#include	"ancPktProcessPublic.h"

#include	"ancPktProcess.h"
#include	"showInfo_open.h"
#include	<corecrt_math.h>
#include	"tmpDefs_open.h"
#include	"qyDefs_open.h"
#include	"ctxQmThread.h"




//
//  这里的参数十分敏感，可以在release和debug各定一套。使性能足够又丢包最少
//  totalPkts是指从开始读取到现在一共顺序到多少个包
//  nPkts_lef是指这一批还剩多少个包。从而能计算出，待播放的是nPkts_left  +  nQNodes
//
extern  "C"  __declspec(dllexport) bool bPktSkipped(Param_bPktSkipped* pParam, int nWhere, int fps_expected, int fps_real, int nQNodes1, int totalPkts, int nPkts_left, bool b4k, int* piTotalPkts_lastOk, unsigned  __int64* pnFactor)
{
	//
	if (!pParam) {
		return  false;
	}

	//
#if  0
	if (nWhere != CONST_nWhere_resize) {
		if (!b4k) {
			return  false;
		}
	}
#endif 

	//
	bool  bSkip_pkt = false;
	TCHAR  tBuf[128];
	unsigned  __int64 nFactor = 0;

	//
	if (!fps_expected) {
		showInfo_open(0, 0, 0,_T("bPktSkipped failed, fps_expected is 0"));
		return false;
	}


	//
	if (nPkts_left < 0) {
		int  ii = 0;
	}

	//
	int nQNodes = nQNodes1 + nPkts_left;

	//
	do {

		//
		if (fps_expected < 30) {
			//
			int ii = 0;
			if (0) {
				_sntprintf(tBuf, mycountof(tBuf), _T("Warn: bPktSkipped: fps_expected %d < 30"), fps_expected);
				showInfo_open(0, 0, 0,tBuf);
			}
		}

		//
		if (nWhere != CONST_nWhere_resize) {
			if (fps_expected < 30) {
				//
				break;
			}
		}

		//
		if (piTotalPkts_lastOk) {
			int iDiff = totalPkts - *piTotalPkts_lastOk;
			if (abs(iDiff) > 10) {	//  保证每10个必通过一个
				break;
			}
		}


		//
		unsigned  __int64 n_nQNodes = 4;// 120;
		//
		int min_nQNodes_left = 3;			//  因为这里除了nQNodes外，nPkts还有包。所以，要播放的是nQNodes+npkts,所以nQNodes只要有一个就说明有很多数据包等待播放了
		//
		int n_totalPkts_0 = 4;
		int n_totalPkts_1 = 4;
		int n_totalPkts_2 = 1;
		int n_totalPkts_3 = 1;
		int n_totalPkts_4 = 1;

		//
		int maxVal_0 = 1;
		int maxVal_1 = 2;
		int maxVal_2 = 3;
		int maxVal_3 = 4;
		int maxVal_4 = 50;




		//
		if (fps_expected == 30) {
			n_nQNodes = 4;
			//
			n_totalPkts_0 = 12;
			n_totalPkts_1 = 12;
			n_totalPkts_2 = 4;
			n_totalPkts_3 = 3;
			n_totalPkts_4 = 2;

		}
		else {
			//  60fps
			min_nQNodes_left = 6;

		}

		//
		if (nQNodes <= min_nQNodes_left) {
			//return false;
			break;
		}

		//
		if (nWhere == CONST_nWhere_vpp)
		{
			//
#ifdef  _DEBUG
			//
			if (0) {
				_sntprintf(tBuf, mycountof(tBuf), _T("bPktSkipped: vpp. fps_expected %d"), fps_expected);
				showInfo_open(0, 0, 0, tBuf);
			}
#endif 

			//
			if (fps_expected == 30) {
				n_nQNodes = 4;
				//
				n_totalPkts_0 = 6;
				n_totalPkts_1 = 6;
				n_totalPkts_2 = 4;
				n_totalPkts_3 = 2;
				n_totalPkts_4 = 1;

			}
			else {
			}

		}
		else  if (nWhere == CONST_nWhere_playVideo)
		{
			//  这里似乎不用处理，因为已经有一个消减多余包的机制了
			if (!b4k) {
				if (fps_expected == 30) {

					//
					if (pParam->last_mql <= pParam->mql_ok)  break;
					//
					int  n = pParam->last_mql - pParam->mql_ok;
					int  nn = fps_expected / n;
					if (nn < 1) {
						bSkip_pkt = true;;
						//
						if (pParam->bDbg) {
							_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("去掉的包太多，nn<1. skip"));
						}
						//
						break;
					}
					if (nn == 1) {
						int kk = fps_expected - n;
						if (!kk) {
							//
							if (pParam->bDbg) {
								_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("去掉的包很多，n==1, kk 0. ok"));
							}
							//
							break;
						}
						//
						nn = fps_expected / kk;
						if (nn < 1) {
							//
							if (pParam->bDbg) {
								_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("去掉的包很多，n==1, nn<1. ok"));
							}
							//
							break;
						}
						//
						if ((totalPkts % nn)) {
							bSkip_pkt = true;
							//
							if (pParam->bDbg) {
								_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("去掉的包很多。去掉kk包，剩下来的为有效。 skip"));
							}
							//
							break;
						}

						//
						if (pParam->bDbg) {
							_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("去掉的包很多。去掉kk包，剩下来的为有效. ok"));
						}

						//
						break;
					}

					if (!(totalPkts % nn)) {
						bSkip_pkt = true;
						//
						if (pParam->bDbg) {
							_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("去掉的包很少。nn %d, skip"), nn);
						}
						//
						break;
					}
					//
					if (pParam->bDbg) {
						_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("去掉的包很少。ok"));
					}

					//
					break;



					//
					break;

				}
				else {


					//
					if (pParam->last_mql <= pParam->mql_ok)  break;
					//
					int  n = pParam->last_mql - pParam->mql_ok;
					int  nn = fps_expected / n;
					if (nn < 1) {
						bSkip_pkt = true;;
						//
						if (pParam->bDbg) {
							_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("去掉的包太多，nn<1. skip"));
						}
						//
						break;
					}
					if (nn == 1) {
						int kk = fps_expected - n;
						if (!kk) {
							//
							if (pParam->bDbg) {
								_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("去掉的包很多，n==1, kk 0. ok"));
							}
							//
							break;
						}
						//
						nn = fps_expected / kk;
						if (nn < 1) {
							//
							if (pParam->bDbg) {
								_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("去掉的包很多，n==1, nn<1. ok"));
							}
							//
							break;
						}
						//
						if ((totalPkts % nn)) {
							bSkip_pkt = true;
							//
							if (pParam->bDbg) {
								_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("去掉的包很多。去掉kk包，剩下来的为有效。 skip"));
							}
							//
							break;
						}

						//
						if (pParam->bDbg) {
							_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("去掉的包很多。去掉kk包，剩下来的为有效. ok"));
						}

						//
						break;
					}

					if (!(totalPkts % nn)) {
						bSkip_pkt = true;
						//
						if (pParam->bDbg) {
							_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("去掉的包很少。nn %d, skip"), nn);
						}
						//
						break;
					}
					//
					if (pParam->bDbg) {
						_sntprintf(pParam->tBuf, mycountof(pParam->tBuf), _T("去掉的包很少。ok"));
					}

					//
					break;


				}
			}
			else {
				if (fps_expected == 30) {
					//
					if (pParam->last_mql <= pParam->mql_ok)  break;
					//
					int  n = pParam->last_mql - pParam->mql_ok;
					int  nn = fps_expected / n;
					if (nn <= 1) {
						bSkip_pkt = true;
						break;
					}
					if (!(totalPkts % nn)) {
						bSkip_pkt = true;
						break;
					}

					//
					break;
				}
				else {  //  
					//n_nQNodes = 8192  *  8  +  8192  *  8  * 2  *  2  *  2  *  4  *  4  *  4  *  8  *  4  *  1.99;	// 800;	// 480;	// 320;// 256;// 80;	// 16;
					 //n_nQNodes = 8192  *  8  +  8192  *  8  * 2  *  2  *  2  *  4  *  4  *  4  *  8  *  4  *  2.18;	// 800;	// 480;	// 320;// 256;// 80;	// 16;
					 //n_nQNodes = 8192  *  8  +  8192  *  8  * 2  *  2  *  2  *  4  *  4  *  4  *  8  *  4  *  2.3;	// 800;	// 480;	// 320;// 256;// 80;	// 16;
					 //n_nQNodes = 8192  *  8  +  8192  *  8  * 2  *  2  *  2  *  4  *  4  *  4  *  8  *  4  *  5.0;	// 800;	// 480;	// 320;// 256;// 80;	// 16;
					//n_nQNodes = 8192 * 8 + 8192 * 8 * 2 * 2 * 2 * 4 * 4 * 4 * 8 * 4 * 9.0;	// 800;	// 480;	// 320;// 256;// 80;	// 16;						
					n_nQNodes = 8192 * 8 + 8192 * 8 * 2 * 2 * 2 * 4 * 4 * 4 * 8 * 4 * 13.0;	// 800;	// 480;	// 320;// 256;// 80;	// 16;						
					n_nQNodes = 8192;
					//
					//
					n_totalPkts_0 = 9;
					n_totalPkts_1 = 7;
					n_totalPkts_2 = 4;
					n_totalPkts_3 = 3;
					n_totalPkts_4 = 2;

					//
					maxVal_0 = 1;// 1000000000;
					maxVal_1 = 20;	// 3060101100;
					maxVal_2 = 30;	// 6060101100;
					maxVal_3 = 40;	// 8879792300;
					maxVal_4 = 50;	// 70989899800;

				}
			}
		}
		else  if (nWhere == CONST_nWhere_postToDraw) {
			if (fps_expected == 30) {
			}
			else {
				n_nQNodes = 4;// 120;
				//
				n_totalPkts_0 = 4;
				n_totalPkts_1 = 4;
				n_totalPkts_2 = 1;
				n_totalPkts_3 = 1;
				n_totalPkts_4 = 1;

			}
		}
		else if (nWhere == CONST_nWhere_resize) {
			if (fps_expected == 30) {
			}
			else {
				n_nQNodes = 3;// 120;
				//
				n_totalPkts_0 = 3;
				n_totalPkts_1 = 2;
				n_totalPkts_2 = 1;
				n_totalPkts_3 = 1;
				n_totalPkts_4 = 1;

			}

		}
		else {
		}




		//
#ifndef  __DEBUG__
		//
		if (nWhere == CONST_nWhere_resize) {
			_sntprintf(tBuf, mycountof(tBuf), _T("fps_expected %d, fps_real %d"), (int)fps_expected, (int)fps_real);
			showInfo_open(0, 0, 0,tBuf);

		}
#endif

		//
		if (!n_nQNodes
			|| !min_nQNodes_left
			|| !n_totalPkts_0
			|| !n_totalPkts_1
			|| !n_totalPkts_2
			|| !n_totalPkts_3
			|| !n_totalPkts_4
			)
		{
			showInfo_open(0, 0, 0,_T("bPktSkipped: param err"));
			//return false;
			break;
		}



			//
			unsigned  __int64 nQNodes_real = nQNodes + nPkts_left;
			unsigned  __int64 l64;
			l64 = nQNodes_real;
			l64 = l64 * l64 * n_nQNodes;
			nFactor = l64 / fps_expected;

			//
			if (nWhere == CONST_nWhere_resize) {
				if (fps_expected == 10 && fps_real <= 30 && fps_real > 25) {  //  当30fps处理
					if (nQNodes_real < 5) {
						if (0 != (totalPkts % 3)) {
							bSkip_pkt = true;
						}
						//
						break;
					}
				}
			}

			//
			if (nFactor) {
				//  
				if (nFactor < maxVal_0) {
					if (!(totalPkts % n_totalPkts_0)) {		//  2
						bSkip_pkt = true;
					}
				}
				else if (nFactor < maxVal_1) {
					if (!(totalPkts % n_totalPkts_1)) {		//  2
						bSkip_pkt = true;
					}
				}
				else  if (nFactor < maxVal_2) {
					if (!(totalPkts % n_totalPkts_2)) {
						bSkip_pkt = true;
					}
				}
				else if (nFactor < maxVal_3) {
					if (!(totalPkts % n_totalPkts_3)) {
						bSkip_pkt = true;
					}
				}
				else if (nFactor < maxVal_4) {
					if (!(totalPkts % n_totalPkts_4)) {
						bSkip_pkt = true;
					}
				}
				else {
					bSkip_pkt = true;
				}


			}
		

	} while (false);

	//
	if (pnFactor)*pnFactor = nFactor;
	if (!bSkip_pkt) {
		if (piTotalPkts_lastOk) {
			*piTotalPkts_lastOk = totalPkts;
		}
	}


	//
	if (bSkip_pkt) {
		int  ii = 0;
	}

	//
	return  bSkip_pkt;

}






//
extern  "C"  __declspec(dllexport)  int  player_get_fps( Param_getFps  *  pParam,  __int64 pIdInfo, unsigned  short  usFps_expected, unsigned  int  uiSampleTimeInMs, TMP_fps_info* pFpsInfo, TCHAR* pHint)
{
	if (!pIdInfo)  return  -1;

	if (!pHint)  pHint = (TCHAR*)_T("");

	pFpsInfo->iCount++;

	DWORD  curTimeInMs = myGetTickCount(NULL);  //
	int  iDiffInMs = curTimeInMs - pFpsInfo->lastTimeInMs;
	//
	if (iDiffInMs > CONST_nInMs_toGetFps)
	{
		int  iDiffInMs_st = uiSampleTimeInMs - pFpsInfo->uiSampleTimeInMs_startToCnt;
		if (iDiffInMs_st) {
			pFpsInfo->fps_real = (float)pFpsInfo->iCount * 1000 / (iDiffInMs_st);
		}
		else {
			pFpsInfo->fps_real = (float)pFpsInfo->iCount * 1000 / (iDiffInMs);
		}

		//
		if ((int)pFpsInfo->fps_real) {
			pFpsInfo->avgTimePerFrameInMs_real1 = (1000.) / pFpsInfo->fps_real;
		}
		//
		if (pFpsInfo->avgTimePerFrameInMs_real1 > 200)  pFpsInfo->avgTimePerFrameInMs_real1 = 200;
		else  if (pFpsInfo->avgTimePerFrameInMs_real1 < 5)  pFpsInfo->avgTimePerFrameInMs_real1 = 5;
		//
		//
		if (usFps_expected > MIN_fps_pts) {
			pFpsInfo->avgTimePerFrameInMs = 1000 / usFps_expected;
		}
		else  pFpsInfo->avgTimePerFrameInMs = pFpsInfo->avgTimePerFrameInMs_real1;


		//
#ifdef  __DEBUG__
		//traceLog((TCHAR*)  _T(  "player_get_fps: %f. avgTimePerFrameInMs %dms"  ),  pFpsInfo->fps,  pFpsInfo->avgTimePerFrameInMs   );
#endif
		//MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();//
		//if (pProcInfo->cfg.debugStatusInfo.ucbShowToDrawStatus) 
		{
			TCHAR  tBuf[256];
			_sntprintf(tBuf, mycountof(tBuf), _T("player_get_fps: %I64u, real %f, expected_avg %dms. real_avg %dms. cnt %d, iDiff_calc %dms, iDiff_st %dms, %s"), pIdInfo, pFpsInfo->fps_real, pFpsInfo->avgTimePerFrameInMs, pFpsInfo->avgTimePerFrameInMs_real1,
				pFpsInfo->iCount,
				iDiffInMs, iDiffInMs_st,
				pHint);
			showInfo_open(0, 0, 0,tBuf);
		}

		//
		pFpsInfo->lastTimeInMs = curTimeInMs;
		pFpsInfo->iCount = 0;
		pFpsInfo->uiSampleTimeInMs_startToCnt = uiSampleTimeInMs;

	}

	return  0;
}

