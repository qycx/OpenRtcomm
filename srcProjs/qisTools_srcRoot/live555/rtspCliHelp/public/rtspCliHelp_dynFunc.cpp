

#include	"stdafx.h"
#include	<Windows.h>
#include	<stdlib.h>
#include	<tchar.h>
#include	<stddef.h>
#include	<mmsystem.h>

#include	"rtspCliHelpCommon.h"



int  dyn_isCliHelp_initShowInfo(  void  **  ppCtx_showInfo  )
{
	return  isCliHelp_initShowInfo(  ppCtx_showInfo  );
}


void  dyn_isCliHelp_exitShowInfo(  void  **  ppCtx_showInfo  )
{
	isCliHelp_exitShowInfo(  ppCtx_showInfo  );
}

 int  dyn_isCliHelp_showInfo(  void  *  pCtx_showInfo,  LPCTSTR  hint  )
{
	//  qyShowInfo1(  
	isCliHelp_showInfo(  pCtx_showInfo,  hint  );
	return  0;
 }



   //
   //  for rtspCliHelp
 __declspec(  dllexport  )  int  isCliHelp_streamDataQ_init(  int  tn,  void  *  pGBUF_rtspCliHelp  );
 __declspec(  dllexport  )  int  isCliHelp_streamDataQ_exit(  void  *  pGBUF_rtspCliHelp  );
 //
 __declspec(  dllexport  )  int  isCliHelp_qPostMsg(  void  *  pQElem,  unsigned  int  size,  void  *  pGENERIC_Q  );
 __declspec(  dllexport  )  int  isCliHelp_debug(  void  *  pGENERIC_Q  );


  __declspec(  dllexport  )  int  isCliHelp_tmpHandler_readData_forSpl(  void  *  pQDC_spl_info,  void  *  p1,  void  *  pMEDIA_data_forSpl  );
  __declspec(  dllexport  )  int  isCliHelp_get_qNodes_streamDataQ(  void  *  pStreamDataQ,  void  *  p1,  void  *  p2  );
