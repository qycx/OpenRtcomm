

#ifndef  __RTSPCLIHELPCOMMON_H__
#define  __RTSPCLIHELPCOMMON_H__	//  {


#include	"qdcOpenCommon.h"


//
#define		CONST_qNodes_toInitSpl		5


extern  GBUF_rtspCliHelp	gBuf_rtspCliHelp;

extern "C" DWORD WINAPI mcThreadProc_spl( LPVOID lpParameter );
int  doSpl(  CTX_spl  *  pCtx  );

//
extern "C" DWORD WINAPI mcThreadProc_cmdProc( LPVOID lpParameter );


//
int  dyn_isCliHelp_initShowInfo(  void  **  ppCtx_showInfo  );
 void  dyn_isCliHelp_exitShowInfo(  void  **  ppCtx_showInfo  );

 int  dyn_isCliHelp_showInfo(  void  *  pCtx_showInfo,  LPCTSTR  hint  );


#endif  //  }


