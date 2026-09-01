
#ifndef  __isCliSaveAvPublic_h__
#define  __isCliSaveAvPublic_h__	//  {

//
#include	"saveAvProc_open.h"



//
extern  "C"  __declspec(  dllexport  )  int  dyn_doSaveAv(  SAVE_av_procInfo  *  pSave,  SAVE_av_pktU  *  pSp,  BOOL  *  pbExists_pSvp,  void  *  pCTX_mc_saveAv  );



#endif  //  }


