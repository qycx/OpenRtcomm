

#ifndef  __qmcProc_h__
#define  __qmcProc_h__		//  {

//
#include <qmcStruct_defs.h>






//  2015/08/03
__declspec(dllexport)  int  sndProcOfflineResReq_qmc(MIS_CNT* pMisCnt, BOOL  bNeedProgress, unsigned  int* puiTranNo);
__declspec(dllexport)  int  sndProcOfflineResToMsgr_qmc(MIS_CNT* pMisCnt, BOOL  bNeedProgress, void* pPROC_offlineRes_u, QY_MESSENGER_ID* pIdInfo_dst, unsigned  int* puiTranNo);





//
#endif  //  }


