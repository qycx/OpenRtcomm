
#ifndef  __dynFuncs_h__
#define  __dynFuncs_h__		//  {


QY_OBJ_DB  *  dyn_getProcedObjDb(  void  *  p0,  int  iDsnIndex  );

//  2016/06/24
int  dyn_tmpHandler_showMsg(  void  *  hDlgTalkParam,  void  *  p1, void  *  pMsgParam  );


#if  0
extern  "C"  bool dyn_bPktSkipped(Param_bPktSkipped* pParam, int nWhere, int fps_expected, int fps_real, int nQNodes1, int totalPkts, int nPkts_left, bool b4k, int* piTotalPkts_lastOk, unsigned  __int64* pnFactor);

extern "C" int  dyn_player_get_fps(Param_getFps* pParam, __int64 pIdInfo, unsigned  short  usFps_expected, unsigned  int  uiSampleTimeInMs, TMP_fps_info* pFpsInfo, TCHAR* pHint);
#endif 






#endif  //  }



