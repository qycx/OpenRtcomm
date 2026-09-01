


#ifndef  __qmcFunc_h__
#define  __qmcFunc_h__	//  {

//
#include	"qmcStruct_defs.h"

	  //
   extern  "C"  __declspec(  dllexport  )  BOOL  bRecordRunning(  void  *  pCAP_procInfo_recordSound  );
   extern  "C"  __declspec(  dllexport  )  BOOL  bCameraRunning(  void  *  pCAP_procInfo_bmp  );

   //
   int  initChannel(MIS_CNT* pMisCnt, int  index, MIS_CHANNEL* pChannel);
   int  exitChannel(MIS_CHANNEL* pChannel);



   //
#endif  //  }


