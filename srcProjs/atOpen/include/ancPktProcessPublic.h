
#ifndef  __anc_pkt_process_public_h__
#define  __anc_pkt_process_public_h__	//  {


//
#define		CONST_nWhere_playVideo					1
#define		CONST_nWhere_postToDraw					2
//
#define		CONST_nWhere_vpp						10
//
#define		CONST_nWhere_vpp2_beforeEnc				12

//
#define		CONST_nWhere_smplYUVReader				15

//
#define		CONST_nWhere_resize						20


///////////////////////////////////

//  这个地方还不能调用dbgMsg_tad, 因为数据还没解密.
//#define		CONST_nWhere_postMsg2CliInfo_inputQ			100

//
#define		CONST_nWhere_mtMgr_processSelf_msgr			110

//
#define		CONST_nWhere_th_doMisMgr_sendFinished		120




//
typedef  struct  __param_bPktSkipped_t {
				 int  last_mql;
				 int  mql_ok;
				 //
				 bool  bDbg;
				 TCHAR	tBuf[128];
				 //
}		 Param_bPktSkipped;


//
extern  "C"  __declspec(dllexport) bool bPktSkipped(Param_bPktSkipped* pParam, int nWhere, int fps_expected, int fps_real, int nQNodes, int totalPkts, int nPkts_left, bool b4k, int* piTotalPkts_lastOk, unsigned  __int64* pnFactor);







//
//
typedef  struct  __tmp_fps_info_t {
	int											iCount;											//  帧数.2014/07/02.用d3d的get_fps( )来得到player的fps.然后计算帧间隔，限制各时间在realInterval - 3, realInterval + 3间。fps放在player里，在playList里显示出来	
	//
	DWORD											unused_curTimeInMs;
	//
	DWORD											lastTimeInMs;
	unsigned  int									uiSampleTimeInMs_startToCnt;
	//
	float											fps_real;
	//
	DWORD											avgTimePerFrameInMs;
	//
	DWORD											avgTimePerFrameInMs_real1;						//  2015/09/10

}		 TMP_fps_info;


//

//  2015/09/05
#define		CONST_nInMs_toGetFps				1000	//  2015/09/05	//  1000

//
#define	MIN_fps_pts								5		//	2015/09/10	//  7		//  2015/06/20	//  10	
#define	MIN_realFps_pts							5		//  2015/09/10	//  7		//  2015/06/20	//  10	


//
typedef  struct  __param_getFps_t {

				 //
				 unsigned  char  ucbShowToDrawStatus;
	
				 //
}		 Param_getFps;


extern  "C"  __declspec(dllexport)  int  player_get_fps(Param_getFps* pParam, __int64 pIdInfo, unsigned  short  usFps_expected, unsigned  int  uiSampleTimeInMs, TMP_fps_info* pFpsInfo, TCHAR* pHint);

//
//
#if  0
typedef  bool (*PF_bPktSkipped)(Param_bPktSkipped* pParam, int nWhere, int fps_expected, int fps_real, int nQNodes1, int totalPkts, int nPkts_left, bool b4k, int* piTotalPkts_lastOk, unsigned  __int64* pnFactor);
typedef  int  (  *PF_player_get_fps  )(Param_getFps* pParam, __int64 pIdInfo, unsigned  short  usFps_expected, unsigned  int  uiSampleTimeInMs, TMP_fps_info* pFpsInfo, TCHAR* pHint);
#endif 




//
#endif  //  }


