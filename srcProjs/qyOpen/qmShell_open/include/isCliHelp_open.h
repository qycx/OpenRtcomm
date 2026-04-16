
#ifndef  __isCliHelp_open_h__
#define  __isCliHelp_open_h__	//  {



// common 
__declspec(  dllexport  )  int  isCliHelp_initShowInfo(  void  **  ppCtx_showInfo  );
__declspec(  dllexport  )  void  isCliHelp_exitShowInfo(  void  **  ppCtx_showInfo  );
  //
__declspec(  dllexport  )  int  isCliHelp_showInfo(  void  *  pCtx_showInfo,  LPCTSTR  hint  );


   //
   //  for rtspCliHelp
 __declspec(  dllexport  )  int  isCliHelp_streamDataQ_init(  int  tn,  void  *  pGBUF_rtspCliHelp  );
 __declspec(  dllexport  )  int  isCliHelp_streamDataQ_exit(  void  *  pGBUF_rtspCliHelp  );
 //
 __declspec(  dllexport  )  int  isCliHelp_streamDataQ_qPostMsg(  void  *  pQElem,  unsigned  int  size,  void  *  pGENERIC_Q  );
 __declspec(  dllexport  )  int  isCliHelp_tmpHandler_readData_forSpl(  void  *  pQDC_spl_info,  void  *  p1,  void  *  pMEDIA_data_forSpl  );
 __declspec(  dllexport  )  int  isCliHelp_streamDataQ_qNodes(  void  *  pStreamDataQ,  void  *  p1,  void  *  p2  );

 //
 __declspec(  dllexport  )  int  isCliHelp_streamDataQ_debug(  void  *  pGENERIC_Q  );


#endif  //  }

