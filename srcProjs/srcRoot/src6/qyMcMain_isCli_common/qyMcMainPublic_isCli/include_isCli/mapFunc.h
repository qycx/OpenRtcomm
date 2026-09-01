
#ifndef  __mapFunc_h__
#define  __mapFunc_h__		//  {

//
#include	"qmcStruct_defs.h"


//
__declspec(dllexport)  int  ancSndProcLocReq(MIS_CNT* pMisCnt, unsigned  int* puiTranNo);
__declspec(dllexport)  int ancSndLocation(void* p0, char* locStr, __int64 imGrp_related_ui64Id);
//
__declspec(dllexport) int ancSndTransferLocData(void* p0, void  *  pTransferLocData, __int64 imGrp_related_ui64Id, __int64  ui64Id_dst);


__declspec(dllexport)  int ancRequestAFile(int loopCtrl);

__declspec(dllexport)  int ancSndMark(char* markStr);


//
#endif  //  }


